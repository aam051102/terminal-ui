#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <vector>

namespace TUI {
    class StringHelper {
    public:
        /*
        Source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        */
        static std::vector<std::string> Split(const std::string& s, const std::string& delimiter, int max = -1) {
            size_t pos_start = 0, pos_end, delim_len = delimiter.length();
            std::string token;
            std::vector<std::string> res;

            while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
                token = s.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back(token);

                if (max != -1 && res.size() == max) {
                    break;
                }
            }

            res.push_back(s.substr(pos_start));
            return res;
        }

        static bool IsNumber(const std::string& s) {
            std::string::const_iterator it = s.begin();

            while (it != s.end() && std::isdigit(*it)) {
                it++;
            }

            return !s.empty() && it == s.end();
        }

        static std::string Trim(const std::string& s) {
            const int len = s.length();

            int start = 0;
            int end = len - 1;
            bool foundStartOrEnd = false;

            for (int i = 0; i < len; i++) {
                if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    start = i;
                    foundStartOrEnd = true;
                    break;
                }
            }

            for (int i = len - 1; i >= start; i--) {
                if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    end = i;
                    foundStartOrEnd = true;
                    break;
                }
            }

            if (!foundStartOrEnd) return "";

            std::string newStr = "";

            for (int i = start; i <= end; i++) {
                newStr += s[i];
            }

            return newStr;
        }

        static std::string Replace(std::string s, const std::string& oldSubstr, const std::string& newSubstr) {
            size_t pos = 0;

            while ((pos = s.find(oldSubstr, pos)) != std::string::npos) {
                s.replace(s.begin() + pos, s.begin() + pos + oldSubstr.size(), newSubstr.c_str());
                pos += newSubstr.size();
            }

            return s;
        }
    };
}

#endif