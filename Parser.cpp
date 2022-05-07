
/* ----- parser ----- */
enum type_t { WORD, LEFT, RIGHT, COMMA };

struct token_t {
  type_t type;
  string value;
  token_t(type_t type, const string &value) : type(type), value(value) {}
};

vector<token_t> get_tokens(const string& s) {
  vector<token_t> res;

  int i = 0;
  while (i < s.size()) {
    if (isalpha(s[i])) {
      string tmp;
      while (i < s.size() && isalpha(s[i])) {
        tmp += s[i];
        ++i;
      }
      res.push_back(token_t(WORD, tmp));
    } else if (s[i] == '{') {
      res.push_back(token_t(LEFT, "{"));
      ++i;
    } else if (s[i] == '}') {
      res.push_back(token_t(RIGHT, "}"));
      ++i;
    } else if (s[i] == ',') {
      res.push_back(token_t(COMMA, ","));
      ++i;
    } else {
      cerr << s.substr(i) << endl;
      break;
    }
  }
  return res;
}

struct parser_t {
  vector<token_t> tokens;
  parser_t(string &s) {
    tokens = get_tokens(s);
  }

  int p;
  vector<string> parse() { // TODO change return type
    p = 0;

    // recursive logic begin
    vector<string> res = cross();
    set<string> s(res.begin(), res.end());
    res.assign(s.begin(), s.end());
    return res;
    // recursive logic end
  }

  inline string match(type_t type) {
    token_t &token = tokens[p];
    if (token.type == type) {
      ++p;
      return token.value;
    } else {
      stringstream sout;
      sout << type << " expected, got " << token.type;
      throw invalid_argument(sout.str());
    }
  }

  // recursive

  vector<string> cross() {
    vector<string> res;
    while (p < tokens.size()) {
      vector<string> b;
      if (tokens[p].type == WORD) {
        b.push_back(  match(WORD));
      } else if (tokens[p].type == LEFT) {
        b = unionAll();
      } else { // IMPORTANT
        break;
      }

      if (res.empty()) {
        res.assign(b.begin(), b.end());
      } else {
        vector<string> tmp;
        for (int i=0; i<res.size(); ++i) {
          for (int j=0; j<b.size(); ++j) {
            tmp.push_back(res[i] + b[j]);
          }
        }
        res = tmp;
      }
    }
    return res;
  }

  vector<string> unionAll() {
    match(LEFT);

    vector<string> res = cross();

    while (tokens[p].type == COMMA) {
      match(COMMA);
      vector<string> tmp = cross();
      res.insert(res.end(), tmp.begin(), tmp.end());
    }

    match(RIGHT);
    return res;
  }
};

/* ----- end of parser ----- */
