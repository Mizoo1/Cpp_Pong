// Muaaz Bdear,  Nour Ahmed
// Matrikal-Nr.: 5194038 , 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      sqlit.h
 * @author    Muaaz Bdear, Nour Ahmed
 * @email     nahmed@stud.hs-bremen.de, mbdear@stud.hs-bremen.deedaabase
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/
#ifndef MYPONG_SQLITEDATABASE_H
#define MYPONG_SQLITEDATABASE_H

#include "userinfo.h"

#include <sqlite3.h>

#include <cassert>
#include <exception>
#include <iostream>
#include <string>

namespace myPong {

/**
 * @brief Implementation of of own class to manage a SQLite Database Connection.
 *
 * A Database object manage a list of all SQLite Statements associated with the
 * underlying SQLite 3 database connection.
 */
class SQLiteDatabase {
  sqlite3 *DB;
  std::string dbFileName;
  std::string db_status_message;
  int db_status;
  std::string sql;

  // hold info for all users
  std::vector<UserInfo> users;

public:
  /*=========================================================================*
   *                         Constructors                                    *
   *=========================================================================*/
  /**
   * @brief default constructor with empty initialization
   *
   * This constructor is ommitted as database can nnot be created without a file
   * name.
   */
  SQLiteDatabase() = delete;

  /**
   * @brief Open the provided database filename.
   *
   * Uses sqlite3_open_v2() with SQLITE_OPEN_READWRITE flag, which is the
   * opposite behavior of the old sqlite3_open() function (READWRITE+CREATE).
   * This makes sense as it prevents creation of a void file when a required DB
   * file is missing.
   *
   * Exception is thrown in case of error, then the Database object is NOT
   * constructed.
   *
   * @param[in] fileName  path/uri to the database file ("filename" sqlite3
   * parameter)
   *
   * @throw SQLite::Exception in case of error
   */
  explicit SQLiteDatabase(const std::string& fileName) : dbFileName(fileName) {
    /*
     * Open the database for read and write.
     * The database file must pre-exist or an error will be given.
     */
    db_status = sqlite3_open_v2(dbFileName.c_str(), &DB, SQLITE_OPEN_READWRITE, NULL);

    if (db_status != SQLITE_OK) {
      // db_status_message = "Error open DB [" + std::to_string(db_status) + "]
      // " + sqlite3_errmsg(DB);
      db_status_message =
          "in\n" + std::string(__FILE__) + "\n" + __func__ + " : " +
          std::to_string(__LINE__) + " for sqlite3_open_v2() with:\ncode:[" +
          std::to_string(db_status) + "] message: " + sqlite3_errmsg(DB);

      // std::cerr << db_status_message<<std::endl;
      //throw db_status_message;
    } else {
      db_status_message = "Opened Database Successfully!";
    }
  }

  /*=========================================================================*
   *                         Destructor                                      *
   *=========================================================================*/
  /** Destructor to do the final cleanup and memory deallocation */
  ~SQLiteDatabase() {
    db_status = sqlite3_close(DB); // Calling sqlite3_close() with a nullptr
                                   // argument is a harmless no-op.

    // Only case of error is SQLITE_BUSY: "database is locked" (some statements
    // are not finalized) Never throw an exception in a destructor :
    if (!(SQLITE_OK == db_status)) {
      // Print a message to the standard error output stream, and abort the
      // program.
      std::cerr << __FILE__ << ":" << __LINE__ << ":"
                << " error: assertion failed (sqlite3_close()) in " << __func__
                << "() with message: database is locked\n";
      assert(SQLITE_OK == db_status);
      // std::abort();
    }
  }

  /**
   * @brief get a status description of the database
   *
   * @return string with the status of the database and/or the last command
   *  executed on it
   */
  std::string get_db_status() { return db_status_message; }

  /**
   * @brief get user info with his logging credentials
   *
   * @param desiredUserName     username to check
   * @param desiredUserPassword user password to check
   * @return true if one (or more) user is found with the given credentials
   */
  bool checkUsers(const std::string& desiredUserName = "",
                 const std::string& desiredUserPassword = "") {
    // delete all previous users inf
    users.clear();

    /* Create SQL statement
      e.g., SELECT * FROM USERS WHERE userName ='abc' AND password ='xyz'
    */
    if (desiredUserName.empty() && desiredUserPassword.empty()) {
      sql = "SELECT * FROM USERS;";
    } else if (desiredUserPassword.empty()) {
      sql = "SELECT * FROM USERS WHERE userName ='" + desiredUserName + "';";
    } else {
      sql = "SELECT * FROM USERS WHERE userName ='" + desiredUserName +
            "' AND password ='" + desiredUserPassword + "';";
    }

    // Execute SQL statement
    char *err = nullptr;
    db_status = sqlite3_exec(
      DB, sql.c_str(),
      [](void *ctx,         /* Data provided in sqlite3_exec() 4th argument*/
          int /*colCount*/, /* The number of columns in row */
          char** rowFields, /* array of strings representing fields in row */
          char** /*colNames*/ /* array of strings representing column names*/
          ) -> int {
        static_cast<std::vector<UserInfo> *>(ctx)->push_back(UserInfo(
            atoi(rowFields[0]), rowFields[1], rowFields[2],
            atoi(rowFields[3]), atoi(rowFields[4]), atoi(rowFields[5]),
            atoi(rowFields[6]), atoi(rowFields[7]), atoi(rowFields[8])));
        return 0;
      },
      &users, &err);

    return !users.empty();
  }

  /**
   * @brief get user info with his logging credentials
   *
   * @param desiredUserName     username to check
   * @param desiredUserPassword user password to check
   * @return true if one (or more) user is found with the given credentials
   */
  bool checkUser(const std::string& desiredUserName,
                 const std::string& desiredUserPassword) {
    // delete all previous users inf
    users.clear();

    /* Create SQL statement
      e.g., SELECT * FROM USERS WHERE userName ='abc' AND password ='xyz'
    */

      sql = "SELECT * FROM USERS WHERE userName ='" + desiredUserName +
            "' AND password ='" + desiredUserPassword + "';";


    // Execute SQL statement
    char *err = nullptr;
    db_status = sqlite3_exec(
      DB, sql.c_str(),
      [](void *ctx,         /* Data provided in sqlite3_exec() 4th argument*/
          int /*colCount*/, /* The number of columns in row */
          char** rowFields, /* array of strings representing fields in row */
          char** /*colNames*/ /* array of strings representing column names*/
          ) -> int {
        static_cast<std::vector<UserInfo> *>(ctx)->push_back(UserInfo(
            atoi(rowFields[0]), rowFields[1], rowFields[2],
            atoi(rowFields[3]), atoi(rowFields[4]), atoi(rowFields[5]),
            atoi(rowFields[6]), atoi(rowFields[7]), atoi(rowFields[8])));
        return 0;
      },
      &users, &err);

    return !users.empty();
  }

bool getFirstUser(UserInfo& user){
  if(users.empty()){
    user=UserInfo(); //if no users return a default one.
    return false;
  }
  user=users[0]; //if one or more users return the first one.
  return true;
}

  /**
   * @brief insert a new user info to the database
   *
   * @param the new user info to be inserted
   */
  void insertNewUser(const std::string& userName,
                     const std::string& password,
                     const int score = 0,
                     const int level = 0,
                     const int ballX = -1,
                     const int ballY = -1,
                     const int leftPaddelY = -1,
                     const int rightPaddelY = -1)
  {
    char *zErrMsg = 0;

    /* Create SQL statement */
    sql = "INSERT INTO USERS "
          "(userName,password,score,level,ballX,ballY,leftPaddelY,rightPaddelY)"
          " VALUES ('" +
          userName + "', '" + password + "', " + std::to_string(score) + "," +
          std::to_string(level) + "," + std::to_string(ballX) + "," +
          std::to_string(ballY) + "," + std::to_string(leftPaddelY) + "," +
          std::to_string(rightPaddelY) + ");";

    /* Execute SQL statement */
    db_status = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &zErrMsg);
    if (db_status != SQLITE_OK) {
      std::cerr << "Error adding new user: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);

      //throw db_status_message;
    } else {
      std::cout << "Adding new user done successfully" << std::endl;
    }
  }

  void throwException(int valueToCheck, char *errMsg, const std::string &op) {
    if (valueToCheck != SQLITE_OK) {
      db_status_message = "in\n" + std::string(__FILE__) + "\n" + __func__ +
                          " : " + std::to_string(__LINE__) + " for " + op +
                          " with:\ncode:[" + std::to_string(valueToCheck) +
                          "] message: " + errMsg;
      sqlite3_free(errMsg);
    } else {
      std::cout << op << " done successfully" << std::endl;
    }
  }
};

} // namespace myPong

#endif /* MYPONG_SQLITEDATABASE_H */
