#pragma once
#ifndef OUTPUT_STR
#define OUTPUT_STR
const char *Welcome =
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
const char *about_info = R"(
       iTravel v0.11
==========================
Developers:
	Wonyeaweat
	zyounan
	shizia_047
Build Date:
	2019/5/25
)";
const char *cTitle = "iTravel v0.11";
const char *currentPath = ".\\", *userDataFileName = ".\\userData.dat",
*favFilename = ".\\myFav.dat", *feedFilename = ".\\Feedback.dat",*BackFilename=".\\Back.dat";
const char *tUser = "�û�:", *tInvaildUser = "�û��������ڣ�����������",
*tPass = "����", *tWrongPass = "�����������������:", *tSuccessLogin = "��¼�ɹ�!";
const wchar_t *tPhone = L"�ֻ�����:", *tRegister = L"ע��", *tInputUser = L"�������û�����",
*tUsernameInvaild = L"���û����ѱ�ע�ᣬ����������", *tInputPhone = L"������绰����:",
*tInvaildPhone = L"���볤���������֤����������", *tInputPassword = L"���������룺",
*tPasswordAgain = L"���ٴ��������룺", *tFailedCheckPassword = L"������������벻��ͬ,�ٴ��������룺",
*tRegisterSuccess = L"ע��ɹ���";
const wchar_t *reviseInfo = L"�޸ĸ�����Ϣ", *tRemaining = L"ʣ�����:", *tChangeSuccess = L"�޸ĳɹ���";
const wchar_t *FailedTOOMANY = L"���������������֤ʧ�ܣ�", *AuthFailed = L"��֤ʧ�ܣ�";
const wchar_t *tInputOrigin = L"������ԭ����:";

#endif