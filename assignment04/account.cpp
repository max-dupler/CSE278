// Copyright 2022 <Max Dupler>
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
    
        mysqlpp::Connection conn(false);

        if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
            // insert into user database
            mysqlpp::Query query = conn.query();
            query << "INSERT INTO 01790638Users" <<
                "(username, password)" << 
                "VALUES ('" << username << "', md5('" << password << "'));";
            
            query.parse();

            mysqlpp::SimpleResult result = query.execute();

            // create table to store their info

            // Always check for errors
            if (result) {
                cout << "<meta http-equiv=\"Refresh\" content=\"0; " 
                << "url=\'http://os1.csi.miamioh.edu/~duplermj/" 
                << "assignment4/login-page.html\'\" />";
            } else {
                cerr << "Query error: " << query.error() << endl;
            }

            mysqlpp::Query tableQuery = conn.query();

            tableQuery << "CREATE TABLE 01790638Username_"+username+" (" 
            << "accountName varchar(255), username varchar(255)," 
            <<  "password varchar(255));";

            result = tableQuery.execute();

            if (result) {
                cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'http" 
                << "://os1.csi.miamioh.edu/~duplermj/assignment4" 
                << "/login-page.html\'\" />";
            } else {
                cerr << "Query error: " << query.error() << endl;
            }
        }
        cout << "<p>query success</p>" << endl;
    } else {
        cout << "<p>Fill out the from and press submit</p>" << endl;
    }
    cout << "</head></html>" << endl;
    return(0);
}
