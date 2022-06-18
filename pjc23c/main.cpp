#include <iostream>
#include <fstream>
#include<string>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <filesystem>
#include <sstream>
#include <stdio.h>
namespace fsystem = std::filesystem;
using std::vector;

using namespace std;


// CPP program for encoding the string
// using classical cipher
#include <iostream>
#include <fstream>
#include<string>
#include <map>
#include <vector>

#include<string>
using namespace std;




class EncryptDecryptByKey {

public:
    string encrypt(string message) {
        char ch;
        int i;
        int key = 3;
        for (i = 0; message[i] != '\0'; ++i) {
            ch = message[i];
            if (ch >= 'a' && ch <= 'z') {
                ch = ch + key;
                if (ch > 'z') {
                    ch = ch - 'z' + 'a' - 1;
                }
                message[i] = ch;
            } else if (ch >= 'A' && ch <= 'Z') {
                ch = ch + key;
                if (ch > 'Z') {
                    ch = ch - 'Z' + 'A' - 1;
                }
                message[i] = ch;
            }
        }
        return message;
    }

public:
    string decrypt(string message) {
        //char message[100], ch;
        char ch;
        int i;
        int key = 3;


        for (i = 0; message[i] != '\0'; ++i) {
            ch = message[i];
            if (ch >= 'a' && ch <= 'z') {
                ch = ch - key;
                if (ch < 'a') {
                    ch = ch + 'z' - 'a' + 1;
                }
                message[i] = ch;
            } else if (ch >= 'A' && ch <= 'Z') {
                ch = ch - key;
                if (ch > 'a') {
                    ch = ch + 'Z' - 'A' + 1;
                }
                message[i] = ch;
            }
        }

        return message;
    }
};














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
    EncryptDecryptByKey en_by_key;
    map<string, string> mapOfPasswords;
    vector<string> sorted_passwords;
    int current_key = 3;

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
    vector<string> find_files() {
        vector <string> files;
        std::string path("data/");
        std::string ext(".txt");

        for (auto &p: fsystem::recursive_directory_iterator(path)) {
            if (p.path().extension() == ext)
                files.push_back(p.path().stem().string());


        }
        return files;
    };


public:
    void fill_map_with_data(int key) {

        while (!fin.eof()) {
            vector<string> words;
            string text = " ";
            getline(fin, text);
            if (current_key != key){

            text = en_by_key.decrypt(text);
            words = split(text, "|");
            }
            else
                text = en_by_key.decrypt(encrypt_decrypt.decrypt(text));
                words = split(text, "|");

            //cout <<words.at(0)<<endl<<words.at(1)<<endl<<words.at(2)<<endl<<words.at(3)<<endl;
            mapOfLoginAndPassword[words[0]] = slicing(words, 1, 3);


        }
    };

public:
     void show(string str) {
        cout << str << " " << endl;
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
        //fs.close();
        ofstream tmp;
        tmp.open("data/tmp.txt", ofstream::app);//открітие или создание файла
        for (auto const &x: mapOfLoginAndPassword)
        {
            data = encrypt_decrypt.encrypt(en_by_key.encrypt(x.first + "|" + x.second[0] + "|" + x.second[1] + "|" + x.second[2]));
            if (count <= 0){
            tmp << data;
            count++;
            }
            else
                tmp << endl << data;

        }

        // delete the original file
        rename("data/sport.txt", "ggg.txt");
        // rename old to new
        rename("data/tmp.txt","data/sport.txt");
        cout << "The password updated!)" << endl;
    };

};




















int main() {
    setlocale(LC_ALL, "");
    map<string, vector<string>> mapOfLoginAndPassword;
    map<string, string> mapOfPasswords;
    vector<string> sorted_passwords;
    EncryptDecrypt encrypt_decrypt;
    EncryptDecryptByKey ed_by_key;
    FileManadger fm;
    string category;

    int current_key = 3;
    int key;
    string key_string;
    cout << "Enter key for dectypt files\n";
    cin >> key_string;
    key = key_string.length();


    string path = "data/sport.txt";//путь
    fm.open_file(path);
    fm.read_file(path);


    int number;
    string className, firstPass, lastPass;
    string youAdress, text;
    string sitename;
    string data;
    int number_for_additing_chose;
    int count = 0;

    vector <string> files;
    int count_files;
    map<int, string> dict_of_categories;
    int category_num;
    //string category_to_removing;
    ofstream fstmp;



    while (true) {
            cout << "Press 1 for writing a new password:\n" << endl;
            cout << "Press 2 for show password by his site:\n" << endl;
            cout << "Press 3 for sorting of passwords:\n" << endl;
            cout << "Press 4 for editing of data:\n" << endl;
            cout << "Press 5 for removing of password:\n" << endl;
            cout << "Press 6 for create/remove category:\n" << endl;
            cout << "Press 7 for show data by category:\n" << endl;
            cin >> number;



            switch (number) {
                case 1:
                    cout << "Chose category: " << endl;
                    files = fm.find_files();
                    for (auto & element : files) {
                        cout << count_files << ": " <<  element << endl;
                        dict_of_categories[count_files] = element;
                        count_files++;
                    }
                    cin >> category_num;

                    cout << "Enter site address" << endl;
                    cin >> className;
                    cout << "Enter your login" << endl;
                    cin >> youAdress;
                    cout << "Enter your password" << endl;
                    cin >> firstPass;
                    cout << "Confirm your password " << endl;
                    cin >> lastPass;
                    if (firstPass == lastPass) {

                        time_t result = time(nullptr);
                        data = encrypt_decrypt.encrypt(ed_by_key.encrypt(
                                className + "|" + youAdress + "|" + firstPass + "|" + asctime(localtime(&result))));
                        if (count <= 0) {
                            fm.fs << data;
                            count++;
                        } else {
                            fm.fs << endl << data;
                        }
                        cout << "Add new password!)" << endl;
                    } else cout << "Don't add new password!)" << endl;
                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
                case 2:
                    cout << "Enter site for which you want know login and password" << endl;
                    cin >> sitename;


                    fm.fill_map_with_data(key);


                    fm.show(sitename);
                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
                case 3:
                    fm.fill_map_with_data(key);


                    fm.sorting();

                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
                case 4:

                    cout << "Enter site for which you want change the password" << endl;
                    cin >> sitename;
                    fm.fill_map_with_data(key);
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

                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;

                case 5:
                    cout << "Enter your site for which you want to delete password" << endl;
                    cin >> sitename;

                    fm.fill_map_with_data(key);

                    fm.mapOfLoginAndPassword.erase(sitename);
                    fm.update_file();
                    cout << "Succes!!!";
                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
                case 6:


                    count_files = 0;
                    cout << "Create/Delete category:" << endl;
                    cout << "Chose option for category:" << endl;
                    cout << "Enter 1 for creating category:" << endl;
                    cout << "Enter 0 for deleting category:" << endl;

                    cin >> number;
                    if (number == 0){

                        cout << "Enter category which you want removing:" << endl;
                        files = fm.find_files();
                        for (auto & element : files) {
                           cout << count_files << ": " <<  element << endl;
                           dict_of_categories[count_files] = element;
                           count_files++;
                        }
                        cin >> category_num;
                        //string category_to_removing;

                        string tmp = "data/" + dict_of_categories[category_num] + ".txt";

                        //cout << category_to_removing;
                        remove(tmp.c_str());

                       // rename("temp.txt", file_name);
                       break;
                    }
                   else
                        cout << "Enter name of new category:" << endl;
                        cin >> sitename;
                        fstmp.open("data/" + sitename + ".txt", ofstream::app);//открітие или создание файла
                        fstmp.close();
                    //fm.show()
                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
                case 7:
                    fm.fill_map_with_data(key);
                    for (auto const &x: fm.mapOfLoginAndPassword) {
                        fm.show(x.first);
                    }

                    cout << "If you want continue press 1" << endl;
                    cout << "if not, press 0";
                    cin >> number_for_additing_chose;
                    if (number_for_additing_chose == 0){
                        break;
                    }
                    continue;
               default:
                    break;
    }

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