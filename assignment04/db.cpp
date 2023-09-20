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

string decrypt(char* c);

int main() {
    map<string, string> Get;
    initializePost(Get);
    string lockdownuser;
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><head>" << endl;
    cout << "<meta charset=\"UTF-8\">" << endl;
    cout << "<meta name=\"viewport\" content=\"width=device-width," 
        <<  "initial-scale=1.0\">" << endl;
    cout << "<title>Lockdown</title>" << endl;
    cout << "<link rel=\"stylesheet\" href=\"table.css\">" << endl;

    if (Get.find("lockdownuser") != Get.end()) {
        lockdownuser = Get["lockdownuser"];
    } else {
        cout << "<p>Fill out the from and press submit</p>" << endl;
    }
    cout << "</head><body>" << endl;

    cout << "<h1>Your Records</h1>" << endl;

    mysqlpp::Connection conn(false);

    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
        mysqlpp::Query query = conn.query();
        query << "SELECT * FROM 01790638Username_"+lockdownuser+";";
        
        query.parse();

        mysqlpp::StoreQueryResult result = query.store();

        if (result) {
            cout << "<table class=\"content-table\">" << endl;
            cout << "<tr>" << endl;
            cout << "<th>AccountName</th>" << endl;
            cout << "<th>Username</th>" << endl;
            cout << "<th>Password</th>" << endl;
            cout << "</tr>" << endl;

            // Get each row in result set, and print its contents
            for (int i = 0; i < result.num_rows(); ++i) {
                // decrypt password for each record
                string password(result[i]["password"]);
                char *pword = &(password[0]);
                string decryptedPassword = decrypt(pword);

                // print table and record
                cout << "<tr>" << endl;
                cout << "<td>" << result[i]["accountName"] << "</td>" <<
                "<td>" << result[i]["username"] << "</td>" <<
                "<td>" << decryptedPassword << "</td></tr>" << endl;
            }
        } else {
            cerr << "Query failed: " << query.error() << endl;
            cout << "<meta http-equiv=\"Refresh\" content=\"0; " 
                << "url=\'http://os1.csi.miamioh.edu/~duplermj" 
                << "/assignment4/homepage.html\'\" />";
        }
    } else {
        cerr << "Connection Failed" << conn.error() << endl;
        cout << "<meta http-equiv=\"Refresh\" content=\"0; url=\'http:" 
        << "//os1.csi.miamioh.edu/~duplermj/assignment4/homepage.html\'\" />";
    }

    cout << "</body></html" << endl;
    return(0);
}

string decrypt(char* c) {
    for (int i = 0; c[i] != '\0'; i++) {
        c[i] = c[i] - 5;
    }
    string result(c);

    return result;
}
