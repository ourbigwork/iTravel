#pragma once
#ifndef OUTPUT_STR
#define OUTPUT_STR
//ע�⣺�����ٿ�һ��cppд�����ˣ����ʹ����C++17����������
//MSVC����ʱ���ڲ��������/std:c++17
inline const char *Welcome =
"�����������������������������������������\n"
"          �~�~�~�~�~     �~�~�~�~�~     �~�~�~�~�~      �~�~�~�~�~\n"
"         ���~�~�~�~�~��    ���~�~�~�~�~��   ���~�~�~�~�~��    ���~�~�~�~�~��\n"
"         �~ �� �~     �~ ӭ �~   �~ ʹ �~     �~ �� �~\n"
"         ���~�~�~�~�~��    ���~�~�~�~�~��   ���~�~�~�~�~��    ���~�~�~�~�~��\n"
"          �~�~�~�~�~     �~�~�~�~�~     �~�~�~�~�~     �~�~�~�~�~  \n"
"        | | | |    | | |    | | |   | | | |   \n"
"\n"
"                               iTravel\n"
"�����������������������������������������\n";
inline const char *about_info = R"(
       iTravel v0.2
==========================
������:
	@YeVII
	@zyounan
	@shizia_047
��������:
	2019/5/29
==========================
)";
inline const char *cTitle = "iTravel v0.2";
inline const char *currentPath = ".\\", *userDataFileName = ".\\userData.dat",
*favFilename = ".\\myFav.dat", *feedFilename = ".\\Feedback.dat", *BackFilename = ".\\Back.dat";
inline const char *tUser = "�û�:", *tInvaildUser = "�û��������ڣ�����������",
*tPass = "����", *tWrongPass = "�����������������:", *tSuccessLogin = "��¼�ɹ�!";
inline const wchar_t *tPhone = L"�ֻ�����:", *tRegister = L"ע��", *tInputUser = L"�������û�����",
*tUsernameInvaild = L"���û����ѱ�ע�ᣬ����������", *tInputPhone = L"������绰����:",
*tInvaildPhone = L"���볤���������֤����������", *tInputPassword = L"���������룺",
*tPasswordAgain = L"���ٴ��������룺", *tFailedCheckPassword = L"������������벻��ͬ,�ٴ��������룺",
*tRegisterSuccess = L"ע��ɹ���";
inline const wchar_t *reviseInfo = L"�޸ĸ�����Ϣ", *tRemaining = L"ʣ�����:", *tChangeSuccess = L"�޸ĳɹ���";
inline const wchar_t *FailedTOOMANY = L"���������������֤ʧ�ܣ�", *AuthFailed = L"��֤ʧ�ܣ�";
inline const wchar_t *tInputOrigin = L"������ԭ����:";
#endif