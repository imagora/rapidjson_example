#pragma once


#include <string>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>


class ReadWrite {
 public:
    void ReadJson();

    void WriteJson();

    void JsonTraversal();

 private:
    void OutputJson(const rapidjson::Value &root, const std::string &pre);
};
