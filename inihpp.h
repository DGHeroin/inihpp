#ifndef __INIHPP_H__
#define __INIHPP_H__

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

class inihpp {
    // trim from start
    static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }
    // trim from end
    static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }
    // trim from both ends
    static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
    }
public:
    struct section {
        section(std::string name) {
            this->name = name;
        }
        std::vector<std::string>                     keys;
        std::string                                  name;
        std::unordered_map<std::string, std::string> values;
    };
public:
    ~inihpp() {
        for(std::vector<section*>::iterator it = section_list.begin();
            it != section_list.end();
            it++) {
            delete *it;
        }
        section_list.clear();
        sections.clear();
    }
    bool parse(const std::string file) {
        using namespace std;
        std::ifstream infile(file);
        std::string line;
        string section_name("");
        section *cur_section = new section(section_name);
        sections[section_name] = cur_section;
        section_list.push_back(cur_section);
        while (std::getline(infile, line)) {
            std::size_t found_comment = line.find(';');
            std::size_t found_string = line.find('"');
            if (found_comment != std::string::npos)
                if (found_string > found_comment)
                    line = line.substr(0, found_comment);
            // is new section
            std::size_t found_symbol_section_start = line.find('[');
            std::size_t found_symbol_section_end   = line.find(']');
            if (found_symbol_section_start != std::string::npos) {
                if (found_symbol_section_end == std::string::npos) continue; // error section format

                section_name = line.substr(found_symbol_section_start + 1, found_symbol_section_end - found_symbol_section_start - 1);
                section_name = trim(section_name);
                cur_section = new section(section_name);
                sections[section_name] = cur_section;
                section_list.push_back(cur_section);
            }
            // is assign
            std::size_t found_symbol_eq = line.find('=');
            if (found_symbol_eq == std::string::npos) continue; // error assignment format error
            string key   = line.substr(0, found_symbol_eq);
            string value = line.substr(found_symbol_eq + 1, line.size() - found_symbol_eq - 1);
            key   = trim(key);
            value = trim(value);
            cur_section->keys.push_back(key);
            cur_section->values[key] = value;
        }
        return true;
    }

    void save(std::string file) {
        using namespace std;
        std::ofstream out(file, std::ios_base::trunc);
        out.close();
        for(std::vector<section*>::iterator it = section_list.begin();
            it != section_list.end();
            it++) {
            section *sec = *it;
            std::ofstream outfile;
            outfile.open(file, std::ios_base::app);
            if (sec->name != "")
                outfile << "[" << sec->name << "]\n";
            for(std::vector<std::string>::iterator sit = sec->keys.begin();
                sit != sec->keys.end();
                sit++) {
                outfile << *sit << " = " << sec->values[*sit] << "\n";
            }
        }
    }

    std::string get(std::string section_name, std::string key) {
        return sections[section_name] == NULL ? "" : sections[section_name]->values[key];
    }

    void set(std::string section_name, std::string key, std::string value) {
        if (sections[section_name] == NULL)
            sections[section_name] = new section(section_name);
        sections[section_name]->values[key] = value;
        sections[section_name]->keys.push_back(key);
    }

private:
    std::vector<section*> section_list;
    std::unordered_map<std::string, section*> sections;
};

#endif // __INIHPP_H__
