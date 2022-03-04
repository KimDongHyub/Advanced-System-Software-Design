#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void insertValue(map<string, set<int> > &myMap,
                 string const &key,
                 int const &value)
{
    // Check whether there is already a set given the key.
    // If so, insert to the existing set.
    // Otherwise, create a set and add it to the map.
    map<string, set<int> >::iterator found = myMap.find(key);
    if (found != myMap.end())
    {

        found->second.insert(value);
    }
    else
    {

        set<int> temp;
        temp.insert(value);
        myMap.insert(make_pair(key, temp));
    }
}
int main(int argc, char* argv[])   //argv 는 터미널 실행 시 실행 커맨드 뒤에 붙는 문자열을 받아준다. ex) ./inverter inputs.txt
{
    string line, filename, word, microword;

    map<string, set<int> > invertedIndex;
    map<string, set<int> >::const_iterator pos; // iterator for loop of map
    set<int>::iterator set_pos;                 // iterator for loop of index of file
    int it = 0;
    int i;
    filename=argv[1];  // 받아준 문자열을 넘겨준다
    //cin >> filename;

    /////////////show each file's context in match index with file////////////
    ifstream file(filename);
    if (file.is_open())
    {
        while (getline(file, line))
        {

            ifstream words(line);
            if (words.is_open())
            {
                while (words >> word)
                {
                    for (i = 0; word[i] != '\0'; i++)
                    {
                        if ((word[i] < 'A' || word[i] > 'Z') && (word[i] < 'a' || word[i] > 'z'))
                        {
                            word.replace(i, 1, " "); // replace everything except alphabet with space. so string stream can separate it with space
                        }
                    }

                    stringstream ss(word);   //without this section word like t2is cannot be separated 
                    ss.str(word);
                    while (ss >> microword)
                    {
                        insertValue(invertedIndex, microword, it);
                    }
                }
                words.close();
            }
            else
            {
                cout << "";
            }
            it++;
        }
        file.close();
    }
    for (pos = invertedIndex.begin(); pos != invertedIndex.end(); pos++)
    {
        cout << pos->first << ": ";
        for (set_pos = pos->second.begin(); set_pos != pos->second.end(); set_pos++)
        {
            cout << *set_pos << " ";
        }
        cout << endl;
    }
    return 0;
}
