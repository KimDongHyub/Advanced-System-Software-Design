#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void insertValue(map<string, set<int> > &myMap, //맵셋과 단어, 이터레이션값(인덱스)이 인풋으로 들어감
                 string const &key,
                 int const &value)
{
    // Check whether there is already a set given the key.
    // If so, insert to the existing set.
    // Otherwise, create a set and add it to the map.
    map<string, set<int> >::iterator found = myMap.find(key); //맵의 이터레이션 벨류 found는 맵에서 찾는 단어가 위치한 자리이다.
    if (found != myMap.end()) // 데이터를 끝까지 찾지 못했을 경우 맵은 map.end() 를 반환한다. 그러니까 이 경우는 데이터가 그 자리에 있는 경우이다.
    {

        found->second.insert(value);  ///set에 인덱스를 삽입한다
    }
    else
    {

        set<int> temp; // 셋을 새로 선언하고
        temp.insert(value); // 그 셋에 인덱스를 삽입한다
        myMap.insert(make_pair(key, temp)); //만들어진 셋을 맵에 삽입한다. 
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
    ifstream file(filename); // 파일을 읽어서 ifstream 객체 타입으로 선언한다
    if (file.is_open())
    {
        while (getline(file, line)) //getline 함수는 다 읽으면 null을 반환한다. 파일에서 한 줄씩 읽는다
        {

            ifstream words(line); // 한 줄이 또 파일 이름이므로 오브젝트 words로 다시 선언. 그 안의 내용이 들어있을것
            if (words.is_open())
            {
                while (words >> word) ///words 파일의 내용이 띄어쓰기 단위로 들어가다가 이제 더이상 없으면 null 반환
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
        cout << pos->first << ": ";                 //pos가 가리키는 첫번째(단어) 출력
        for (set_pos = pos->second.begin(); set_pos != pos->second.end(); set_pos++)
        {
            cout << *set_pos << " "; //set_pos 이 가리키는곳 모두 출력
        }
        cout << endl;
    }
    return 0;
}
