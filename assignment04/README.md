The problem I chose to solve is password security. It has become a very important problem recently because of advanced hacking and password phishing. I started with an outline:
1. Have users create an account with a master password they can remember
2. allow a user to create records including: the account associated with the login (i.e. facebook account or google account), the username for that account   and the password for that account.
3. allow users to view their records when signed into their account

I started by building my database. I used one table to store user information such as username and master password. The password in this case uses an md5 hash for user security. My other tables are created by my application each time a new user creates an account. Each user table contains all of their records. In these tables, I couldn't use an md5 hash because I needed to be able to display the passwords to the user. Instead, I used a simple cipher key to encrypt the passwords. In the database, the passwords are encrypted while the user can view them without any encryption.

For the user interface, I use three html pages, one is a login page(login-page.html), one is for incorrect passwords(incorrect-login.html) and is the same as login-page.html except for an invalid login message, and the other is a homepage(homepage.html). In the login page and incorrect login page, the user can either create an account or login. In the homepage the user can either add a record to their database or view their record.

For my application layer, I use 4 CGI scripts. One for adding accounts(account.cgi), one for processing logins(login.cgi), one for adding records(records.cgi) and one for retrieving records from a user database(db.cgi). account.cgi processes a POST request from a form on login-page.html and then connects to the database to add the username and hashed password, after adding the query, the script redirects back to login-page.html so the user can use their new login. login.cgi processes the login form on login-page.html and checks to see if the username and password match a row in the database. If the query matches a row, the script redirects to homepage.html but if not, it redirects to incorrect-login.html. records.cgi proceses a form on homepage.html and adds a record to the database of the user logged in. record.cgi also encrypts the password before data entry, this script automatically redirects back to homepage.html. Lastly, db.cgi processes a form where the user enters their username and then it retrieves all rows from their database. After this, the script decrupts all of their passwords and displays them in a table to the user.

Some things I want to add to my project in the future are:
1. adding the ability to lock certain passwords with a code for more security
2. a more advanced encryption and decryption method
3. a way to keep the user logged on throughout each html page so they don't need to keep entering their username
