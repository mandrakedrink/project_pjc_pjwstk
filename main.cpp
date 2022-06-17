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

class EncryptDecrypt {
public:
    string encrypt(string str) {
        for (int i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] + 2; //the key for encryption is 3 that is added to ASCII value

        //cout << "\nEncrypted string: " << str << endl;
        return str;
    };
public:
    string decrypt(string str) {
        for (int i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] - 2; //the key for encryption is 3 that is subtracted to ASCII value
        return str;
    }
};

class FileManadger {
public:
    ofstream fs;
    ifstream fin;
    map<string, vector<string>> mapOfLoginAndPassword;
    EncryptDecrypt encrypt_decrypt;
    map<string, string> mapOfPasswords;
    vector<string> sorted_passwords;

public:
    void open_file(string path) {


        fs.exceptions(ifstream::badbit | ifstream::failbit);//для трай кетч

        try {
            fs.open(path, ofstream::app);//открітие или создание файла
            cout << "File is open" << endl;


        }
        catch (const ifstream::failure &ex) {
            cout << ex.what() << endl;
            cout << "zdrastie2\n";
        }
    };


public:
    void read_file(string path) {


        try {
            fin.open(path);//открітие или создание файла
            cout << "File is open" << endl;
            // fs << "bebra\n"<<endl;//запись в файл
        }
        catch (const ifstream::failure &ex) {
            cout << ex.what() << endl;
            cout << "zdrastie1\n";
        }
    };
public:
    int find_files() {
        std::string path("data/");
        std::string ext(".txt");
        for (auto &p: fsystem::recursive_directory_iterator(path)) {
            if (p.path().extension() == ext)
                cout << p.path().stem().string() << '\n';

        }
        return 0;
    };


public:
    void fill_map_with_data() {


        while (!fin.eof()) {
            vector<string> words;
            string text = " ";
            getline(fin, text);

            text = encrypt_decrypt.decrypt(text);
            words = split(text, "|");

            //cout <<words.at(0)<<endl<<words.at(1)<<endl<<words.at(2)<<endl<<words.at(3)<<endl;
            mapOfLoginAndPassword[words[0]] = slicing(words, 1, 3);


        }
    };

public:
     void show(string str) {
        //cout << str << " ";
        cout << mapOfLoginAndPassword[str][0] << endl;
        cout << mapOfLoginAndPassword[str][1] << endl;
        cout << mapOfLoginAndPassword[str][2] << endl;
    }


public:
    vector<string> slicing(vector<string> &words,
                           int X, int Y) {

        // Starting and Ending iterators
        auto start = words.begin() + X;
        auto end = words.begin() + Y + 1;

        // To store the sliced vector
        vector<string> result(Y - X + 1);

        // Copy vector using copy function()
        copy(start, end, result.begin());

        // Return the final sliced vector
        return result;
    };
public:
    vector<string> split(string str, string token) {
        vector<string> result;
        while (str.size()) {
            int index = str.find(token);
            if (index != string::npos) {
                result.push_back(str.substr(0, index));
                str = str.substr(index + token.size());
                if (str.size() == 0)result.push_back(str);
            } else {
                result.push_back(str);
                str = "";
            }
        }
        return result;
    };

public:
    static bool cmp(pair<string, string> &a,
             pair<string, string> &b) {
        return a.second < b.second;
    };
public:
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
        std::sort(A.begin(), A.end(), cmp);

        // Print the sorted value
        for (auto& it : A) {
            returns.push_back(it.first);
            //cout << it.first << ':'
            //     << it.second << endl;
        }

        return returns;
    }
public:
    void sorting() {

        for (auto const &x: mapOfLoginAndPassword) {
            mapOfPasswords[x.first] = x.second[0];
        }
        sorted_passwords = sort(mapOfPasswords);

        for (int i = 0; i < sorted_passwords.size(); i++) {
            //cout << sorted_passwords[i] + " " << endl;
            show(sorted_passwords[i]);
        }

    };
public:
    void update_file(){
        int count = 0;
        string data;
        fs.close();
        ofstream tmp;
        tmp.open("data/tmp.txt", ofstream::app);//открітие или создание файла
        for (auto const &x: mapOfLoginAndPassword)
        {
            data = encrypt_decrypt.encrypt(x.first + "|" + x.second[0] + "|" + x.second[1] + "|" + x.second[2]);
            if (count <= 0){
            tmp << data;
            count++;
            }
            else
                tmp << endl << data;

        }

        //fin.close();
        //fs.close();

        // delete the original file
        rename("data/sport.txt", "ggg.txt");
        // rename old to new
        rename("data/tmp.txt","data/sport.txt");
        cout << "The password updated!)" << endl;
    };

public:
    void del_line(const char *file_name, int n)
    {
        ifstream fin(file_name);
        ofstream fout;
        fout.open("temp.txt", ios::out);

        char ch;
        int line = 1;
        while(fin.get(ch))
        {
            if(ch == '\n')
                line++;

            if(line != n)      // content not to be deleted
                fout<<ch;
        }
        fout.close();
        fin.close();
        remove(file_name);
        rename("temp.txt", file_name);
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








int main() {
    //map <string, string(*)[2]> mapOfLoginAndPassword; // пример  vector<string>
    //map <string, string(*)[2]> mapOfLoginAndPassword;
    //string log_and_pass[2] = {"hohol", "12345"};
    setlocale(LC_ALL, "");
    map<string, vector<string>> mapOfLoginAndPassword;
    map<string, string> mapOfPasswords;
    vector<string> sorted_passwords;
    EncryptDecrypt encrypt_decrypt;
    FileManadger fm;

    //vector<string> words;
    //2vector<string> log_and_pass = {"hohol", "12345"};
    //vector<string> words{};
    //mapOfLoginAndPassword.insert(std::pair<string,vector<string>>("www.zopa.com",&log_and_pass));
    //mapOfLoginAndPassword.insert(std::pair<string,string(*)[2]>("www.zopa.com",&log_and_pass));
    //mapOfLoginAndPassword["www.zopa.com"] = log_and_pass;


    string path = "data/sport.txt";//путь
    //ofstream fs;//обьект класа для ззаписи
    fm.open_file(path);
    fm.read_file(path);


    int number;
    string className, firstPass, lastPass;
    string youAdress, text;
    string sitename;
    string data;
    int count = 0;

    while (true) {
            cout << "Press 1 for writing a new password:\n" << endl;
            cout << "Press 2 for show password by his site:\n" << endl;
            cout << "Press 3 for sorting of passwords:\n" << endl;
            cout << "Press 4 for deleting of data:\n" << endl;
            cout << "Press 5 for editing of password:\n" << endl;
            cin >> number;
        
        
            switch (number) {
                case 1:
                    fm.find_files();
                    cout << "Enter site adress" << endl;
                    cin >> className;
                    cout << "Enter login" << endl;
                    cin >> youAdress;
                    cout << "Enter your password" << endl;
                    cin >> firstPass;
                    cout << "Confirm your password " << endl;
                    cin >> lastPass;
                    if (firstPass == lastPass) {
        
                        time_t result = time(nullptr);
                        data = encrypt_decrypt.encrypt(
                                className + "|" + youAdress + "|" + firstPass + "|" + asctime(localtime(&result)));
                        if (count <= 0) {
                            fm.fs << data;
                            count++;
                        } else {
                            fm.fs << endl << data;
                        }
                        cout << "Add new password!)" << endl;
                    } else cout << "Don't add new password!)" << endl;
        
                    continue;
                case 2:
                    cout << "Enter site for which you want know login and password" << endl;
                    cin >> sitename;
        
        
                    fm.fill_map_with_data();
        
        
                    fm.show(sitename);
        
                    continue;
                case 3:
                    fm.fill_map_with_data();
        
        
                    fm.sorting();
        
        
                    continue;
                case 4:
        
                    cout << "Enter site for which you want change the password" << endl;
                    cin >> sitename;
                    fm.fill_map_with_data();
                    cout << "the old values:\n";
                    fm.show(sitename);
                    cout << "Enter your password" << endl;
                    cin >> firstPass;
                    cout << "Confirm your password " << endl;
                    cin >> lastPass;
                    if (firstPass == lastPass) {
        
                        fm.mapOfLoginAndPassword[sitename][1] = firstPass;
                        time_t result = time(nullptr);
                        fm.mapOfLoginAndPassword[sitename][2] = asctime(localtime(&result));
                        cout << "the new values:\n";
                        fm.show(sitename);
        
                        fm.update_file();
        
                    } else
                        cout << "Password dosn't added\n";
        
                    continue;
                case 5:
                    cout << "Enter your site for which you want to delate password" << endl;
                    cin >> sitename;
        
                    fm.fill_map_with_data();
        
                    fm.mapOfLoginAndPassword.erase(sitename);
                    fm.update_file();
                    cout << "Succes!!!";
        
        
                default:
                    break;
    }

            //fm.fs.close();
            //fm.fin.close();

            return 0;
    }
};


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
    return 0;
}
fdfdfd */
