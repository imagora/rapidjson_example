#pragma once

#include <map>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>


enum JsonType {
    JSON_NULL_VALUE     = 0,
    JSON_INT_VALUE      = 1,
    JSON_INT64_VALUE    = 2,
    JSON_UINT_VALUE     = 3,
    JSON_UINT64_VALUE   = 4,
    JSON_REAL_VALUE     = 5,
    JSON_STRING_VALUE   = 6,
    JSON_BOOL_VALUE     = 7,
    JSON_ARRAY_VALUE    = 8,
    JSON_OBJECT_VALUE   = 9,
};


static const std::map<uint32_t, bool (rapidjson::Value:: *)() const> kCheckRule = {
  {JSON_INT_VALUE,    &rapidjson::Value::IsInt},
  {JSON_INT64_VALUE,  &rapidjson::Value::IsInt64},
  {JSON_UINT_VALUE,   &rapidjson::Value::IsUint},
  {JSON_UINT64_VALUE, &rapidjson::Value::IsUint64},
  {JSON_REAL_VALUE,   &rapidjson::Value::IsDouble},
  {JSON_STRING_VALUE, &rapidjson::Value::IsString},
  {JSON_BOOL_VALUE,   &rapidjson::Value::IsBool},
  {JSON_ARRAY_VALUE,  &rapidjson::Value::IsArray},
  {JSON_OBJECT_VALUE, &rapidjson::Value::IsObject},
};


typedef std::string                       JsonValueKey;
typedef std::map<JsonValueKey, JsonType>  JsonCheckList;
typedef std::pair<bool, JsonValueKey>     JsonCheckResult;


class SimpleChecker {
 public:
  void CheckValue();
 private:
  JsonCheckResult CheckJsonValue(const rapidjson::Value &val, const JsonCheckList &check_list);
};
