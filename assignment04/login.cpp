// Copyright 2022 <Max Dupler
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include "getpost.h"

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::cerr;

bool authenticate(string username, string password);

void homepage(string username);

int main() {
    map<string, string> Get;
    initializePost(Get);
    string username;
    string password;
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><head>" << endl;

    if (Get.find("username") != Get.end() 
        && Get.find("password") != Get.end()) {
        username = Get["username"];
        password = Get["password"];
        bool validLogin = authenticate(username, password);

        if (validLogin) {
            cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'http://" 
            << "os1.csi.miamioh.edu/~duplermj" 
            << "/assignment4/homepage.html\'\" />";
        } else {
            cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'http:" 
            << "//os1.csi.miamioh.edu/~duplermj" 
            << "/assignment4/incorrect-login.html\'\" />";
        }
    } else {
        cout << "<p>Fill out the from and press submit" << endl;
    }
    cout << "</head></html>" << endl;
    return(0);
}

bool authenticate(string username, string password) {
    // connect to the sql server
    mysqlpp::Connection conn(false);

    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
        mysqlpp::Query query = conn.query();
        query << "SELECT * FROM 01790638Users WHERE password = " 
        << "md5('"+password+"');";
        
        query.parse();

        mysqlpp::StoreQueryResult result = query.store();

        if (result) {
            if (result.num_rows() == 0) {
                return false;
            }
            // check if username matches
            string uname = result[0][0].c_str();
            if (uname == username) {
                return true;
            } else {
                return false;
            }
        } else {
            cerr << "Query failed: " << query.error() << endl;
            return false;
        }
    } else {
        cerr << "Connection Failed" << conn.error() << endl;
        return false;
    }
    return false;
}


