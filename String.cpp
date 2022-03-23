
/** read bytes until EOF */
char b;
while(cin.read(&b, 1))
{
  // process byte b
}

/** read lines until EOF */
string line;
while (getline(cin, line))
{
    // TODO do something
}

/** to_lower / to_upper */

void to_lower(string &str) {
    for (size_t loop = 0; loop < str.size(); loop++) {
      str[loop] = tolower(str[loop]);
    }
}

inline string to_lower_copy(const string &str) {
    string res = str;
    to_lower(res);
    return res;
}

void to_upper(string &str) {
    for (size_t loop = 0; loop < str.size(); loop++) {
      str[loop] = toupper(str[loop]);
    }
}

/** start_with end_with */
inline bool starts_with(const string &heystack, const string &needle) {
    return heystack.rfind(needle, 0) == 0;
}

inline bool ends_with(const string &heystack, const string &needle) {
    return heystack.find(needle, heystack.length() - needle.length()) != string::npos;
}

/** replace replaceAll (both inplace) */
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


/** trim */

// trim from end of string (right)
inline void trim_right(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
}

// trim from beginning of string (left)
inline void trim_left(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
}

// trim from both ends of string (right then left)
inline void trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    trim_right(s, t);
    trim_left(s, t);
}

/** only has spaces / whitespaces */
inline bool has_only_spaces(const string &str) {
    return str.find_first_not_of(' ') == std::string::npos;
}

inline bool has_only_ws(const string &str) {
    return str.find_first_not_of(" \t\n\v\f\r") == std::string::npos;
}
