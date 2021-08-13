/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#pragma once

#include <string>
#if (WIN32) || (_WIN32)
#include <filesystem>
#elif (__linux__) || (__linux)
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <fstream>
#include <sstream>

namespace UtilFile {
    static std::string getDir(const std::string& path)
    {
        auto directory_end = path.find_last_of(":/\\");
        if (directory_end == std::string::npos)
        {
            directory_end = 0;
        }
        else
        {
            directory_end += 1;
        }
        return path.substr(0, directory_end);
    }

    bool tryOpen(std::fstream& stream, const std::string& inputPath, int mode)
    {
#if WIN32
        std::string dir = getDir(inputPath);
        // TODO check dir before create
        std::experimental::filesystem::create_directories(dir);
        std::wstring inputPathW;
        try
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
            inputPathW = utf8_conv.from_bytes(inputPath);
        }
        catch (const std::exception &)
        {
            inputPathW.clear();
        }

        if (inputPathW.size() > 0)
        {
            stream.open(inputPathW, mode);
        }
        else
        {
            stream.open(inputPath, mode);
        }
#else
        std::string dir = cybertron::UtilPath::getDir(inputPath);
        std::string cmd("mkdir -p ");
        system(cmd.append(dir).c_str());
        stream.open(inputPath, (std::ios_base::openmode)mode);
#endif
        return stream.good();
    }

    std::string readUTF8StringFromFile(const std::string& inputPath)
    {
        std::fstream file;
        if (!tryOpen(file, inputPath, std::ios::in))
        {
            printf("Failed to open file: [%s]", inputPath.c_str());
            throw std::runtime_error(u8"FileError");
        }

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
}
