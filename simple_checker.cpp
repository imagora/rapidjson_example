#include "simple_checker.h"
#include <iostream>


void SimpleChecker::CheckValue() {
  JsonCheckList check_list = {
    {"bool1", JSON_BOOL_VALUE},
    {"bool2", JSON_INT_VALUE},
    {"bool3", JSON_UINT_VALUE},

    {"int1", JSON_INT_VALUE},
    {"int2", JSON_INT64_VALUE},
    {"int3", JSON_UINT_VALUE},
    {"int4", JSON_UINT64_VALUE},

    {"double1", JSON_REAL_VALUE},
    {"double2", JSON_INT_VALUE},
    {"double3", JSON_UINT_VALUE},
  };

  rapidjson::Document root;
  root.SetObject();

  auto &allocator = root.GetAllocator();
  root.AddMember<bool>(rapidjson::StringRef("bool1"), true, allocator);
  root.AddMember<bool>(rapidjson::StringRef("bool2"), false, allocator);
  root.AddMember<bool>(rapidjson::StringRef("bool3"), true, allocator);

  root.AddMember<int>(rapidjson::StringRef("int1"), -1, allocator);
  root.AddMember<int>(rapidjson::StringRef("int2"), 1, allocator);
  root.AddMember<int>(rapidjson::StringRef("int3"), 2, allocator);
  root.AddMember<int>(rapidjson::StringRef("int4"), 3, allocator);

  root.AddMember<double>(rapidjson::StringRef("double1"), 1, allocator);
  root.AddMember<double>(rapidjson::StringRef("double2"), 1.0, allocator);
  root.AddMember<double>(rapidjson::StringRef("double3"), 2, allocator);

//  const rapidjson::Value &v = root.GetObject();
  auto result = CheckJsonValue(root.GetObject(), check_list);
  while (!result.first) {
    std::cout << result.second << " check failed" << std::endl;
    check_list.erase(result.second);
    result = CheckJsonValue(root.GetObject(), check_list);
  }

  std::cout << "check success" << std::endl;
}


JsonCheckResult SimpleChecker::CheckJsonValue(const rapidjson::Value &val, const JsonCheckList &check_list) {
  JsonValueKey error_key;
  return std::make_pair(
    std::find_if(check_list.begin(), check_list.end(), [&](const JsonCheckList::value_type &check_item) {
        auto rule_iter = kCheckRule.find(check_item.second);
        if (rule_iter == kCheckRule.end()) {
          return true;
        }

        auto iter = val.MemberBegin();
        if (iter == val.MemberEnd()) {
          std::cout << "error" << std::endl;
        }

        for (; iter != val.MemberEnd(); ++iter) {
          std::cout << iter->name.GetString() << std::endl;
        }

        const rapidjson::Value &v = val[check_item.first.c_str()];
        if (!(v.*(rule_iter->second))()) {
          error_key = check_item.first;
          return true;
        }
        return false;
    }) == check_list.end(),
    error_key);
}
