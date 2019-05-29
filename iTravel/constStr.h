#pragma once
#ifndef OUTPUT_STR
#define OUTPUT_STR
//注意：懒得再开一个cpp写定义了，因此使用了C++17的内联变量
//MSVC编译时请在参数后加上/std:c++17
inline const char *Welcome =
"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n"
"          ▇▇▇▇▇     ▇▇▇▇▇     ▇▇▇▇▇      ▇▇▇▇▇\n"
"         ◢▇▇▇▇▇◣    ◢▇▇▇▇▇◣   ◢▇▇▇▇▇◣    ◢▇▇▇▇▇◣\n"
"         ▇ 欢 ▇     ▇ 迎 ▇   ▇ 使 ▇     ▇ 用 ▇\n"
"         ◥▇▇▇▇▇◤    ◥▇▇▇▇▇◤   ◥▇▇▇▇▇◤    ◥▇▇▇▇▇◤\n"
"          ▇▇▇▇▇     ▇▇▇▇▇     ▇▇▇▇▇     ▇▇▇▇▇  \n"
"        | | | |    | | |    | | |   | | | |   \n"
"\n"
"                               iTravel\n"
"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n";
inline const char *about_info = R"(
       iTravel v0.2
==========================
开发者:
	@YeVII
	@zyounan
	@shizia_047
编译日期:
	2019/5/29
==========================
)";
inline const char *cTitle = "iTravel v0.2";
inline const char *currentPath = ".\\", *userDataFileName = ".\\userData.dat",
*favFilename = ".\\myFav.dat", *feedFilename = ".\\Feedback.dat", *BackFilename = ".\\Back.dat";
inline const char *tUser = "用户:", *tInvaildUser = "用户名不存在，请重新输入",
*tPass = "密码", *tWrongPass = "密码错误，请重新输入:", *tSuccessLogin = "登录成功!";
inline const wchar_t *tPhone = L"手机号码:", *tRegister = L"注册", *tInputUser = L"请输入用户名：",
*tUsernameInvaild = L"该用户名已被注册，请重新输入", *tInputPhone = L"请输入电话号码:",
*tInvaildPhone = L"号码长度有误，请查证后重新输入", *tInputPassword = L"请输入密码：",
*tPasswordAgain = L"请再次输入密码：", *tFailedCheckPassword = L"两次输入的密码不相同,再次输入密码：",
*tRegisterSuccess = L"注册成功！";
inline const wchar_t *reviseInfo = L"修改个人信息", *tRemaining = L"剩余次数:", *tChangeSuccess = L"修改成功！";
inline const wchar_t *FailedTOOMANY = L"密码多次输入错误，验证失败！", *AuthFailed = L"认证失败！";
inline const wchar_t *tInputOrigin = L"请输入原密码:";
#endif