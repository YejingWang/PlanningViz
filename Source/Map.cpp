/***************************************************
* Author: YejingWang
* Date: 2021/08/11
****************************************************/

#include "Map.hpp"
#include "Util/UtilJson.hpp"
#include "Util/UtilFile.hpp"

Map::Map(const std::string& mapFile) :
    mWalls(),
    mValid(false)
{
    loadMap(mapFile);
}

std::vector<Wall> Map::walls() const {
    return mWalls;
}

bool Map::loadMap(const std::string& mapFile) {
    std::string mapContent = UtilFile::readUTF8StringFromFile(mapFile);

    nlohmann::json mapJson;
    if (!UtilJson::loadString(mapJson, mapContent)) {
        printf("Failed to load map file");
        return false;
    }

    if (mapJson.find("Walls") != mapJson.end()) {
        const auto& wallsJson = mapJson["Walls"];
        for (const auto& wallJson : wallsJson) {
            if (wallJson.find("x1") != wallJson.end() &&
                wallJson.find("y1") != wallJson.end() &&
                wallJson.find("x2") != wallJson.end() &&
                wallJson.find("y2") != wallJson.end() &&
                wallJson.find("width") != wallJson.end()) {
                mWalls.push_back(Wall(wallJson["x1"], wallJson["y1"], wallJson["x2"], wallJson["y2"], wallJson["width"]));
            }
        }
    }

    return true;
}
