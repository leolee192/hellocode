
/** to_lower / to_upper */

void to_lower(string &str) {
    for (size_t loop = 0; loop < str.size(); loop++) {
      str[loop] = tolower(str[loop]);
    }
}

void to_upper(string &str) {
    for (size_t loop = 0; loop < str.size(); loop++) {
      str[loop] = toupper(str[loop]);
    }
}

/** read lines until EOF */
string line;
while (getline(cin, line))
{
    // TODO do something
}
