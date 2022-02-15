#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;


void printfile(string filename){
    ifstream file(filename);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            cout<<line<<endl;
        }
        file.close();

    }
    else{
        cout<<"Error";
        
    }
}

/*void readwords(string filename){
    ifstream file(filename);
    string word;
    if(file.is_open()){
        while(file >> word){
            if(word[word.length()-1]=='.'){
                word.erase(word.end()-1);
        }
            cout<<word<<endl;
        }
        file.close();

    }
    else{
        cout<<"Error";
        
    }
}*/
void insertValue(map<string, set<int> >& myMap,
                 string const& key,
                 int const& value)
{
   // Check whether there is already a set given the key.
   // If so, insert to the existing set.
   // Otherwise, create a set and add it to the map.
   map<string, set<int> >::iterator found = myMap.find(key);
   if ( found != myMap.end() )
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


int main(){
    string line, filename;
    
    map<string,set<int> > invertedIndex;
    map<string,set<int> >::const_iterator pos;
    set<int>::iterator set_pos;
    int it=0;
    

    cout<<"input filename: "<<endl;
    cin>>filename;
    printfile(filename);
    
    /////////////show each file's context in match index with file////////////
    ifstream file(filename);
    if(file.is_open()){
        while(getline(file, line)){
            cout<<line<<endl;
            printfile(line);
            //readwords(line);
            ifstream words(line);
            string word;
            if(words.is_open()){
                while(words >> word){
                    if(word[word.length()-1]=='.'){
                        word.erase(word.end()-1);
                }
                    
                    insertValue(invertedIndex,word,it);

        }
            words.close();

    }
    else{
        cout<<"Error";
        
    }


            
            
            it++;

    }
        
        file.close();
    }
    
    for (pos=invertedIndex.begin(); pos!=invertedIndex.end(); pos++){
        cout<<pos->first<<": ";
        for(set_pos=pos->second.begin();set_pos!=pos->second.end();set_pos++){
            cout<<*set_pos<<" ";
        
        }
        cout<<endl;

    }
    ///////////////////////////////////////////////
    
    return 0;
}