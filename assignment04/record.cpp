// Copyright 2022 <Max Dupler>
// cgi for adding an account to the database

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
#include "getpost.h"

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::cerr;

string encrypt(char* c);

int main() {
    map<string, string> Get;
    initializePost(Get);
    string dbname;
    string account;
    string username;
    string password;
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><body>" << endl;

    if (Get.find("account") != Get.end() && Get.find("username") != Get.end() 
        && Get.find("password") != Get.end() 
        && Get.find("lockdownuser") != Get.end()) {
        account = Get["account"];
        username = Get["username"];
        password = Get["password"];
        dbname = Get["lockdownuser"];

        char *pword = &(password[0]);
        password = encrypt(pword);

        // connect to the sql server
        mysqlpp::Connection conn(false);

        if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
            // insert into user database
            mysqlpp::Query query = conn.query();
            query << "INSERT INTO 01790638Username_" << dbname <<
                " (accountName, username, password)" << 
                "VALUES ('" << account << "', '" << username
                << "', '" << password << "');";
            
            query.parse();

            mysqlpp::SimpleResult result = query.execute();

            // Always check for errors
            if (result) {
                cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\"" 
                << "'http://os1.csi.miamioh.edu/~duplermj/assignment4" 
                <<  "/homepage.html\'\" />";
            } else {
                cerr << "Query error: " << query.error() << endl;
                cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'" 
                << "http://os1.csi.miamioh.edu/~duplermj" 
                << "/assignment4/homepage.html\'\" />";
            }
        }
    } else {
        cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'" 
        << "http://os1.csi.miamioh.edu/~duplermj" 
        << "/assignment4/homepage.html\'\" />";
    }
    cout << "</body></html>" << endl;
    return(0);
}

string encrypt(char* c) {
    for (int i = 0; c[i] != '\0'; i++) {
        c[i] = c[i] + 5;
    }
    string result(c);

    return result;
}
