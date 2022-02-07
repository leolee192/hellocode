
void to_lower(string &str) {
    for (unsigned short loop = 0; loop < str.size(); loop++) {
      str[loop] = tolower(str[loop]);
    }
}

void to_upper(string &str) {
    for (unsigned short loop = 0; loop < str.size(); loop++) {
      str[loop] = toupper(str[loop]);
    }
}
