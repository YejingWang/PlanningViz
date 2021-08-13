/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#pragma once

#include "nlohmann/json.hpp"

#include <string>

namespace UtilJson {
    bool loadString(
        nlohmann::json& jsonNode,
        const std::string& content)
    {
        try {
            jsonNode = nlohmann::json::parse(content);
            return true;
        }
        catch (nlohmann::json::parse_error& e) {
            std::string s;
            size_t pos1 = (e.byte - 50 < 0 ? 0 : e.byte - 50);
            if (e.byte > 1) {
                s += content.substr(pos1, e.byte - 1 - pos1);
            }
            s += " [[[ " + content.substr(e.byte - 1, 1) + " ]]] ";
            if (e.byte < content.length()) {
                s += content.substr(e.byte);
            }
            printf("Failed to parse json string near the [[[]]] marks: [%s]", s.c_str());
            printf("Error %d: %s", e.id, e.what());
            return false;
        }
        catch (...) {
            printf("Unknown errors when parsing json string [%s]", content.c_str());
            return false;
        }
    }
}
