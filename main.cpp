#include <iostream>
#include <fstream>
#include<string>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <filesystem>
namespace fsystem = std::filesystem;
using std::vector;

using namespace std;



int find_files()
{
    std::string path("data/");
    std::string ext(".txt");
    for (auto &p : fsystem::recursive_directory_iterator(path))
    {
        if (p.path().extension() == ext)
            std::cout << p.path().stem().string() << '\n';
    }
    return 0;
}


class EncryptDecrypt {
public:
    string encrypt(string str) {
        for (int i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] + 2; //the key for encryption is 3 that is added to ASCII value

        cout << "\nEncrypted string: " << str << endl;
        return str;
    }
public:
    string decrypt(string str) {
        for (int i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value
        return str;
    }
};


std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{

    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;

    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

// Comparator function to sort pairs
// according to second value
bool cmp(pair<string, string>& a,
         pair<string, string>& b)
{
    return a.second < b.second;
}

// Function to sort the map according
// to value in a (key-value) pairs
vector<string> sort(map<string, string>& M)
{
    vector<string> returns;
    // Declare vector of pairs
    vector<pair<string, string> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto& it : A) {
        returns.push_back(it.first);
        //cout << it.first << ':'
        //     << it.second << endl;
    }
    return returns;
}


vector<string> slicing(vector<string>& words,
                    int X, int Y)
{

    // Starting and Ending iterators
    auto start = words.begin() + X;
    auto end = words.begin() + Y + 1;

    // To store the sliced vector
    vector<string> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}

int main() {
    //map <string, string(*)[2]> mapOfLoginAndPassword; // пример  vector<string>
    //map <string, string(*)[2]> mapOfLoginAndPassword;
    //string log_and_pass[2] = {"hohol", "12345"};
    map <string, vector<string>> mapOfLoginAndPassword;
    map <string, string> mapOfPasswords;
    vector <string> sorted_passwords;
    EncryptDecrypt encrypt_decrypt;
    //vector<string> words;
    int size_t, pos;
    size_t, pos = 0;
    //2vector<string> log_and_pass = {"hohol", "12345"};
    //vector<string> words{};
    //mapOfLoginAndPassword.insert(std::pair<string,vector<string>>("www.zopa.com",&log_and_pass));
    //mapOfLoginAndPassword.insert(std::pair<string,string(*)[2]>("www.zopa.com",&log_and_pass));
    //mapOfLoginAndPassword["www.zopa.com"] = log_and_pass;


    string path = "data/sport.txt";//путь
    ofstream fs;//обьект класа для ззаписи

    fs.exceptions(ifstream::badbit | ifstream::failbit);//для трай кетч

    try {
        fs.open(path, ofstream::app );//открітие или создание файла
        cout << "File is open" << endl;
        // fs << "bebra\n"<<endl;//запись в файл

    }
    catch(const ifstream::failure & ex){
        cout << ex.what() << endl;
        return 0;
    }

    ifstream fin;

    try {
        fin.open(path);//открітие или создание файла
        cout << "File is open" << endl;
        // fs << "bebra\n"<<endl;//запись в файл
    }
    catch (const ifstream::failure& ex) {
        cout << ex.what() << endl;
        return 0;
    }





    int number;
    string className, firstPass, lastPass;
    string youAdress, text;
    string sitename;
    string data;
    cout << "Press 1 for writing a new password:" << endl;
    cout << "Press 2 for show password" << endl;
    cout << "Press2 3 for sorting of passwords" << endl;
    cin >> number;



    switch (number)
    {
        case 1:
            find_files();
            cout << "Enter class for you password" << endl;
            cin >> className;
            cout << "Enter site adress" << endl;
            cin >> youAdress;
            cout << "Enter your password" << endl;
            cin >> firstPass;
            cout << "Confirm your password " << endl;
            cin >> lastPass ;
            if (firstPass == lastPass) {

                time_t result = time(nullptr);
                data = encrypt_decrypt.encrypt(className +  "|" + youAdress + "|" + firstPass +"|" + asctime(localtime(&result)));
                fs << data << endl;
                cout << "Add new password!)" << endl;
            }
            else cout << "Don't add new password!)" << endl;

            break;
        case 2:
            cout << "Enter site for which you want know login and password" << endl;
            cin >> sitename;


            while (!fin.eof()){
                vector<string> words;
                text = " ";
                //string [2] words;
                getline(fin, text);
                //cout << "text" << text << "text" << endl;
                text = encrypt_decrypt.decrypt(text);
                words = split(text, "|");

                //cout <<words.at(0)<<endl<<words.at(1)<<endl<<words.at(2)<<endl<<words.at(3)<<endl;
                mapOfLoginAndPassword[words[0]] = slicing(words, 1, 3);


            }
            //cout << "ok4";
            cout << mapOfLoginAndPassword[sitename][0]<<endl;
            cout << mapOfLoginAndPassword[sitename][1]<<endl;
            cout << mapOfLoginAndPassword[sitename][2]<<endl;

            break;
        case 3:

            while (!fin.eof()){


                vector<string> words;
                text = " ";
                //string [2] words;
                getline(fin, text);
                text = encrypt_decrypt.decrypt(text);
                //cout << "text" << text << "text" << endl;
                words = split(text, "|");

                //cout <<words.at(0)<<endl<<words.at(1)<<endl<<words.at(2)<<endl<<words.at(3)<<endl;
                mapOfLoginAndPassword[words[0]] = slicing(words, 1, 3);


            }

            for (auto const& x : mapOfLoginAndPassword)
            {
                mapOfPasswords[x.first] = x.second[0];
            }
            sorted_passwords =  sort(mapOfPasswords);

            for (int i = 0; i < sorted_passwords.size(); i++) {
                //cout << sorted_passwords[i] + " " << endl;




                //cout << "i = " << i << endl;
                cout << sorted_passwords[i] << " ";
                cout << mapOfLoginAndPassword[sorted_passwords[i]][0] << " ";
                cout << mapOfLoginAndPassword[sorted_passwords[i]][1]<< " ";
                cout << mapOfLoginAndPassword[sorted_passwords[i]][2] << endl;
            }

            break;

        default:
            break;
    }



    fs.close();
    fin.close();

    return 0;
}


void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already
        // in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

}








// Driver Code
/*
int main()
{

    // Declare Map
    map<string, string> M;

    // Given Map
    M = { { "GfG", "aaa" },
          { "To", "ccc" },
          { "Welcome", "AAA" } };

    // Function Call
    sort(M);
    return 0;ssss
}
fdfdfd */
