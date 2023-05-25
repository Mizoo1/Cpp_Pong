// Muaaz Bdear,  Nour Ahmed
// Matrikal-Nr.: 5194038 , 5200991
// Assignment – Game Implementation

/**========================================================================
 * @file      userinfo.h
 * @author    Muaaz Bdear, Nour Ahmed
 * @email     nahmed@stud.hs-bremen.de, mbdear@stud.hs-bremen.de
 * @createdOn 05.01.2023
 * @version   1.0.0
 *========================================================================**/

#ifndef USERINFO_H
#define USERINFO_H

#include <iostream>
#include <string>
#include <vector>

namespace myPong {
/**
 * @brief Implementation of of struct to manage user data.
 */
struct UserInfo {
  int userID;
  std::string userName;
  std::string password;
  int score;
  int level;
  int ballX;
  int ballY;
  int leftPaddelY;
  int rightPaddelY;

  /*=========================================================================*
   *                         Constructors                                    *
   *=========================================================================*/
  /**
   * @brief default constructor with empty initialization
   */
  UserInfo()
      : userID(-1),
        userName("Nour"),
        password("1"),
        score(0),
        level(0),
        ballX(-1),
        ballY(-1),
        leftPaddelY(-1),
        rightPaddelY(-1) {}

  /**
   * @brief
   * @param[in]
   */
  UserInfo(const int& userID, const std::string& userName, const std::string& password,
           const int& score, const int& level,
           const int& ballX, const int& ballY,
           const int& leftPaddelY, const int& rightPaddelY)
      : userID(userID),
        userName(userName),
        password(password),
        score(score),
        level(level),
        ballX(ballX),
        ballY(ballY),
        leftPaddelY(leftPaddelY),
        rightPaddelY(rightPaddelY) {}

  void print() {
    std::cout << "userID =" << userID << std::endl
              << "userName =" << userName << std::endl
              << "password =" << password << std::endl
              << "score =" << score << std::endl
              << "level =" << level << std::endl
              << "ballX =" << ballX << std::endl
              << "ballY =" << ballY << std::endl
              << "leftPaddelY =" << leftPaddelY << std::endl
              << "rightPaddelY =" << rightPaddelY << std::endl;
  }
};

} // namespace myPong

#endif /* USERINFO_H */
