/** iterate over map */
for(map<Key,Val>::iterator it = myMap.begin(); it != myMap.end(); ++it)
{
    Key k =  it->first;
    Value v = it->second;
}

/** overloaded less-than operator for
 *     default comparison function std::less<Key> **/
struct Key {
  bool operator < (const Key& rhs) const;
};
