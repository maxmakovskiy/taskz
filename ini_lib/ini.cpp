#include "ini.h"

namespace Ini {

Section&
Document::AddSection
(std::string name)
{
    if (sections.find(name) != sections.end()) {
        return sections[name];
    }

    sections[name] = {};
    return sections[name];
}

const Section&
Document::GetSection
(const std::string& name) const
{
    return sections.at(name);
}

size_t
Document::SectionCount() 
const
{
    return sections.size();
}

Document
Load
(std::istream& input)
{
    Document doc;

    Section* section = nullptr;
    for(std::string line; std::getline(input, line); )
    {
        if (line.empty()) {
            section = nullptr;
            continue;
        }

        if (line[0] == '[') {
            // add title
            std::string title = line.substr(1, line.size()-2);  
            section = &doc.AddSection(title);
            continue;
        }

        if (section != nullptr) 
        {
            // add key-value pair
            auto [key, value] = Split(line);
            section->insert({std::string(key), std::string(value)});
        }
    }

    return doc;
}

std::pair<std::string_view, std::string_view>
Split
(const std::string_view source)
{ // key1=value1
    size_t pos = source.find('=');
    return {source.substr(0, pos), source.substr(pos+1)};
}

}
