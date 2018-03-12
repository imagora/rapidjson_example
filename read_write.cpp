#include "read_write.h"
#include <rapidjson/writer.h>
#include <vector>
#include <numeric>
#include <sstream>
#include <iostream>


void ReadWrite::ReadJson() {
  std::string json = "{\"name\":\"Tom\",\"age\":29,\"weight\":65.2,\"height\":175,\"children\":[\"Bob\",\"Alice\"]}";
  rapidjson::Document root;
  root.Parse(json.c_str());

  if (root.HasParseError()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  std::string name    = root["name"].GetString();
  int32_t     age     = root["age"].GetInt();
  double      weight  = root["weight"].GetDouble();
  uint32_t    height  = root["height"].GetUint();

  std::vector<std::string> children_names;
  rapidjson::Value children = root["children"].GetArray();
  if (!children.Empty()) {
    for (uint32_t i = 0; i < children.Size(); ++i) {
      children_names.push_back(children[i].GetString());
    }
  }

  std::cout << "ConvertStringToJson, Name: " << name << ", age: " << age << ", weight: " << weight
            << ", height: " << height << ", children: "
            << std::accumulate(std::next(children_names.begin()), children_names.end(),
                               std::string{*children_names.begin()},
                               [](std::string out, const std::string &in){return out + ", " + in;})
            << std::endl;
}


void ReadWrite::WriteJson() {
  rapidjson::Document root;
  root.SetObject();

  auto &allocator = root.GetAllocator();
  root.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef("Tom"), allocator);
  root.AddMember<int>(rapidjson::StringRef("age"), 29, allocator);
  root.AddMember<double>(rapidjson::StringRef("weight"), 65.2, allocator);
  root.AddMember<uint32_t>(rapidjson::StringRef("height"), 175, allocator);

  rapidjson::Value children(rapidjson::kArrayType);
  children.PushBack(rapidjson::StringRef("Bob"), allocator);
  children.PushBack(rapidjson::StringRef("Alice"), allocator);

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  root.Accept(writer);

  std::cout << "ConvertJsonToString, json: " << buffer.GetString() << std::endl;
}


void ReadWrite::JsonTraversal() {
  rapidjson::Document root;
  root.SetObject();

  auto &allocator = root.GetAllocator();

  root.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef("Tom"), allocator);
  root.AddMember<int>(rapidjson::StringRef("age"), 29, allocator);
  root.AddMember<double>(rapidjson::StringRef("weight"), 65.2, allocator);
  root.AddMember<uint32_t>(rapidjson::StringRef("height"), 175, allocator);

  rapidjson::Value children(rapidjson::kArrayType);

  rapidjson::Value child_bob(rapidjson::kObjectType);
  child_bob.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef("Bob"), allocator);
  child_bob.AddMember<int>(rapidjson::StringRef("age"), 3, allocator);
  children.PushBack(child_bob, allocator);

  rapidjson::Value child_alice(rapidjson::kObjectType);
  child_alice.AddMember(rapidjson::StringRef("name"), rapidjson::StringRef("Alice"), allocator);
  child_alice.AddMember<int>(rapidjson::StringRef("age"), 1, allocator);
  children.PushBack(child_alice, allocator);

  root.AddMember(rapidjson::StringRef("children"), children, allocator);

  OutputJson(root.GetObject(), "");
}


void ReadWrite::OutputJson(const rapidjson::Value &root, const std::string &pre) {
  std::cout << pre << "{\n";

  for (auto iter = root.MemberBegin(); iter != root.MemberEnd(); ++iter) {
    std::cout << pre << "\t\"" << iter->name.GetString() << "(" << iter->value.GetType() << ")\": ";
    if (iter->value.GetType() == rapidjson::kObjectType) {
      OutputJson(iter->value, "\t\t");
    } else if (iter->value.GetType() == rapidjson::kArrayType) {
      std::cout << pre << "[\n";
      for (uint32_t i = 0; i < iter->value.Size(); ++i) {
        OutputJson(iter->value[i], "\t\t");
      }
      std::cout << pre << "\t],\n";
    } else {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      iter->value.Accept(writer);

      std::cout << buffer.GetString() << ",\n";
    }
  }
  std::cout << pre << "},\n";
}
