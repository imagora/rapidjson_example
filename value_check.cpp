#include "value_check.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <iostream>


void ValueCheck::CheckUInt() {
  std::string json = "{\"value\":1}";
  rapidjson::Document root;
  root.Parse(json.c_str());

  if (root.HasParseError()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  if (!root["value"].IsUint() || !root["value"].IsUint64()) {
    std::cout << "CheckUInt failed" << std::endl;
    return;
  }

  try {
    uint64_t v1 = root["value"].GetUint64();
    uint32_t v2 = root["value"].GetUint();
    (void)v1;
    (void)v2;
  } catch (...) {
    std::cout << "CheckUInt failed" << std::endl;
    return;
  }

  std::cout << "CheckUInt success" << std::endl;
}


void ValueCheck::CheckReal() {
  std::string json = "{\"value\":1}";
  rapidjson::Document root;
  root.Parse(json.c_str());

  if (root.HasParseError()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  if (!root["value"].IsDouble() || !root["value"].IsFloat()) {
    std::cout << "CheckReal failed" << std::endl;
    return;
  }

  try {
    double v1 = root["value"].GetDouble();
    float v2 = root["value"].GetFloat();
    (void)v1;
    (void)v2;
  } catch (...) {
    std::cout << "CheckReal failed" << std::endl;
    return;
  }

  std::cout << "CheckReal success" << std::endl;
}


void ValueCheck::CheckBool() {
  std::string json = "{\"value\":false}";
  rapidjson::Document root;
  root.Parse(json.c_str());

  if (root.HasParseError()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  const rapidjson::Value &v = root["value"];
  if (!v.IsUint()) {
    std::cout << "CheckBool not uint success" << std::endl;
  } else {
    uint32_t v1 = v.GetUint();
    (void)v1;
  }

  if (!v.IsBool()) {
    std::cout << "CheckBool failed" << std::endl;
    return;
  }

  bool v2 = v.GetBool();
  (void)v2;

  std::cout << "CheckBool success" << std::endl;
}
