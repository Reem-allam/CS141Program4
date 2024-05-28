/**********************************************************
 * Project 4: IMDB
 * Course: CS 141, Fall 2022
 * System: MacOS using Xcode
 * Starter Code Author: Dr. Sara Riazi
 * Student Author: Reem Allam
 **********************************************************/
#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;



/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}
// assigns the different strings needed in titleRecord file
struct TitleRecord{
    string title_id;
    string primaryTitle;
    string startYear;
    string genres;
};

// assigns the different strings needed in nameRecord file
struct NameRecord{
    string name_id;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

// assigns the different strings needed in PrincipalRecord file
struct PrincipalRecord{
    string title_id;
    string name_id;
    string category;
    string character;
};

//reads in titlerecord file
void readTitles(string titlesFile, vector<TitleRecord>& titles){
    string line;
    ifstream reader(titlesFile);
    if (reader.is_open()){
        getline(reader, line);
        while (getline(reader,line)){
            vector<string> items;
            splitString(line, '\t', items);
            TitleRecord t;
            t.title_id = items.at(0);
            t.primaryTitle = items.at(2);
            t.startYear = items.at(5);
            t.genres = items.at(8);
            titles.push_back(t);
        }
        reader.close();
    }
}
//reads in namesRecord file
void readNames (string namesFile, vector<NameRecord>& names){
    string line;
    ifstream reader(namesFile);
    if (reader.is_open()){
        getline(reader,line);
        while(getline(reader,line)){
            vector<string> items;
            splitString(line,'\t',items);
            NameRecord n;
            n.name_id = items.at(0);
            n.primaryName = items.at(1);
            n.birthYear = items.at(2);
            n.deathYear = items.at(3);
            n.primaryProfession = items.at(4);
            names.push_back(n);
        }
        reader.close();
    }
}
//reads in principalRecord file
void readPrincipals (string principalsFile, vector<PrincipalRecord>& principals){
    string line;
    ifstream reader(principalsFile);
    if(reader.is_open()){
        getline(reader, line);
        while(getline(reader,line)){
            vector<string> items;
            splitString(line, '\t',items);
            PrincipalRecord p;
            p.title_id = items.at(0);
            p.name_id = items.at(2);
            p.category = items.at(3);
            p.character = items.at(5);
            principals.push_back(p);
        }
        reader.close();
    }
}

// makes the user input lowercase
bool containsPattern(string text, string pattern){
    if(text.size() < pattern.size())
        return false;

    int i = 0;
    while(i <= (text.size()- pattern.size())){
        char ch1 = text.at(i);
        char ch2 = pattern.at(0);
        if (ch1 >= 65 && ch1 <= 90)
            ch1 = ch1 + 32;

        if(ch2 >= 65 && ch2 <= 90)
            ch2 = ch2 + 32;

       if (ch1 == ch2){
           int j = 0;
           bool contain = true;
           while (j < pattern.size()){
               ch1 = text.at(i + j);
               ch2 = pattern.at(j);
               if (ch1 >= 65 && ch1 <= 90)
                   ch1 = ch1 + 32;

               if (ch2 >= 65 && ch2 <= 90)
                   ch2 = ch2 + 32;

               if (ch1 != ch2){
                   contain = false;
                   break;
               }
               j++;
           }
          if(contain)
              return true;
       }
       i++;
    }
    return false;
}

// prints default for option 1 input
void printResults1 (vector<TitleRecord> const& results){
    cout<< endl;
    for( int i = 0; i < results.size(); i++){
        cout<< i << ":" << endl;
        cout << "Title: " << results.at(i).primaryTitle<< endl;
        cout << "Year: " << results.at(i).startYear << endl;
        cout << "Genre: " << results.at(i).genres << endl;
        vector<string> items;
        splitString(results.at(i).genres, ',', items);

        for(int j = 0; j< items.size(); j++){
            cout << " " << items.at(j);
        }
        cout<< "\n_______________"<< endl;
    }
}
// prints default for option 2 input
void printResults2 (vector<NameRecord> const& results) {
    cout << "---------------" << endl;
    for (int i = 0; i < results.size(); i++) {
        cout << i << ":" << endl;
        cout << results.at(i).primaryName << endl;
        cout << results.at(i).primaryProfession << endl;
        cout << "(" << results.at(i).birthYear << "-" << results.at(i).deathYear << ")" << endl;
        cout << "_______________" << endl;
    }
}
//default menu display
int menuOption() {
    int option = 3;
    do {
        cout << "Select a menu option:" << endl;
        cout << "\t1. Search for movies \n";
        cout << "\t2. Search for actors/actresses \n";
        cout << "\t3. Exit\n";
        cout << "Your choice --> ";
        cin >> option;
        if (cin.fail()) {
            break;
        }
    } while (option < 1 || option > 3);
    {
        return option;
    }
}
    
// goes though user input for first choice and prints out the needed information
    void firstOption(vector<TitleRecord> const& titles, vector<NameRecord> const& names,
                     vector<PrincipalRecord> const& principals) {
        
        string search;
        cout << "Enter search phrase: ";
        cin >> search;
        bool domore = true;
        
        while(domore){
            
            vector<string> items;
            splitString(search, '+', items);
            vector<TitleRecord> results;
            
            for (int j = 0; j < titles.size(); j++) {
                bool contain = true;
                
                for (int i = 0; i < items.size(); i++) {
                    if (!containsPattern(titles.at(j).primaryTitle, items.at(i))) {
                        contain = false;
                        break;
                    }
                }
                if (contain) {
                    results.push_back(titles.at(j));
                }
            }
            if (results.size() > 0) {
                printResults1(results);
                int option;
                cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
                cin >> option;
                
                if (!cin.fail() && option >= 0 && option < results.size()) {
                    vector<PrincipalRecord> details;
                    for (int i = 0; i < principals.size(); i++) {
                        
                        if (principals.at(i).title_id == results.at(option).title_id &&
                            (principals.at(i).category == "actor" || principals.at(i).category == "actress")) {
                            details.push_back(principals.at(i));
                        }
                    }
                    if (details.size() > 0) {
                        for (int i = 0; i < details.size(); i++) {
                            for (int j = 0; j < names.size(); j++) {
                                if (names.at(j).name_id == details.at(i).name_id) {
                                    cout << names.at(j).primaryName << " " << details.at(i).character << endl;
                                    break;
                                }
                            }
                        }
                    }
                }
                cout << "Enter search phrase (type done to go back to the previous menu): ";
                cin >> search;
                
                if (cin.fail()) {
                    domore = false;
                    break;
                }
                if (search == "done") {
                    domore = false;
                }
            } else {
                cout << "No match found! \n" << endl;
                break;
            }
        }
    }

// goes though user input for second choice and prints out the needed information
    void secondOption(vector<TitleRecord> const& titles, vector<NameRecord> const& names,
                      vector<PrincipalRecord> const& principals) {
        string search;
        cout << "Enter search phrase: ";
        cin >> search;
        
        bool domore = true;
        while (domore) {
            vector<string> items;
            splitString(search, '+', items);
            vector<NameRecord> results;
            for (int j = 0; j < names.size(); j++) {
                bool contain = true;
                for (int i = 0; i < items.size(); i++) {
                    if (!containsPattern(names.at(j).primaryName, items.at(i))) {
                        contain = false;
                        break;
                    }
                }
                if (contain) {
                    results.push_back(names.at(j));
                }
            }
            if (results.size() > 0) {
                printResults2(results);
                int option;
                cout << "Select an actors/actress to see movies (-1 to go to the previous menu): ";
                cin >> option;
                
                if (!cin.fail() && option >= 0 && option < results.size()) {
                    vector<PrincipalRecord> details;
                    for (int i = 0; i < principals.size(); i++) {
                        if (principals.at(i).name_id == results.at(option).name_id) {
                            
                            details.push_back(principals.at(i));
                        }
                    }
                    
                    if (details.size() > 0) {
                        for (int i = 0; i < details.size(); i++) {
                            for (int j = 0; j < titles.size(); j++) {
                                if (titles.at(j).title_id == details.at(i).title_id) {
                                    cout << titles.at(j).primaryTitle << " " << titles.at(j).startYear << " "
                                    << details.at(i).character << endl;
                                    break;
                                }
                            }
                        }
                    }
                }
                
                cout << "Enter search phrase (type done to go back to the previous menu: )";
                cin >> search;
                if (cin.fail()) {
                    domore = false;
                    break;
                }
                if (search == "done") {
                    domore = false;
                }
            } else {
                cout << "No match found!" << endl;
                domore = false;
            }
        }
    }
    

    /**********************************************************************************************************/
    
    int run(string titlesFile, string namesFile, string principalsFile) {
        vector<TitleRecord> titles;
        readTitles(titlesFile, titles);
        
        vector<NameRecord> names;
        readNames(namesFile, names);
        
        vector<PrincipalRecord> principals;
        readPrincipals(principalsFile, principals);
        
        int option;
        do {
            option = menuOption();
            if (option == 1) {
                 firstOption(titles, names, principals);
            } else if (option == 2) {
                secondOption(titles, names, principals);
            }
        } while (option != 3);
        return 0;
    }
    
    int main() {
        //Change these addresses according to your local machine
        string titlesFile = "movie.titles.tsv";
        string namesFile = "movie.names.tsv";
        string principalsFile = "movie.principals.tsv";
        
        
        //DO NOT change the main function. The main function will be removed by the autograder
        run(titlesFile, namesFile, principalsFile);
        return 0;
    }
    
