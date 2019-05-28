#include "pch.h"
#include "CConsole.h"
HANDLE CConsole::__createNewScreen() {
	return CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
}
CConsole::CConsole(const std::string& consoleTitle) :tlock(lockk), ConsoleTitle(consoleTitle) {
	using Gdiplus::Status;
	Status res = GdiplusStartup(&token, &gdiplusStartupInput, nullptr);
	if (res != Status::Ok)
		throw std::runtime_error("Failed to initialize Gdiplus!");
}
void CConsole::init(short inputbackgroundColor = BACKGROUND_BLUE, short inputforegroundColor = 0) {
	background = __createNewScreen(),
		foreground = __createNewScreen();
	SetConsoleTitleA(ConsoleTitle.c_str());
	SetConsoleActiveScreenBuffer(foreground);
	ResizeWindow();
	putCursorToEnd();
	setColorInput(inputbackgroundColor, inputforegroundColor);
	makeColorfulInput();
	WriteConsoleA(foreground, ">", 1, nullptr, nullptr);
}
tagRECT CConsole::getCurrentWindowInfo() {
	HWND hwnd = GetConsoleWindow();
	tagRECT rect;
	GetWindowRect(hwnd, &rect);
	return rect;
}
void CConsole::stopDrawingThread() {
	tContinueDrawing = false;
	if (isLastThreadRunning)
		flag.wait(tlock);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return;
}
void CConsole::setColorInput(short newColorForeground, short newColorBackground) {
	InputBackground = newColorForeground | newColorBackground;
}
void CConsole::__setDefaultColor() {
	InputBackground = 0;
}
void CConsole::makeColorfulInput() {
	setColorInput(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, BACKGROUND_BLUE);
	using std::string;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(foreground, &info);
	int t = info.srWindow.Right - info.srWindow.Left - 1;
	string tmp(" ");
	tmp.append(t, ' ');
	SetConsoleTextAttribute(foreground, InputBackground);
	WriteConsoleA(foreground, tmp.c_str(), tmp.length(), nullptr, nullptr);
	putCursorToEnd();
}
void CConsole::updateScreen() {
	SetConsoleActiveScreenBuffer(background);
	ResizeWindow();
	CloseHandle(foreground);
	foreground = background;

	__setDefaultColor();

	background = __createNewScreen();
	putCursorToEnd();
	makeColorfulInput();
	WriteConsoleA(foreground, ">", 1, nullptr, nullptr);
}
void CConsole::WriteText(const std::string & out) {
	output_buffer += out;
	WriteConsoleA(background, output_buffer.c_str(), output_buffer.length(), nullptr, nullptr);
	updateScreen();
}
//��ˢ����Ļ
void CConsole::__WriteText(const std::string & out) {
	output_buffer += out;
	WriteConsoleA(background, output_buffer.c_str(), output_buffer.length(), nullptr, nullptr);
}
void CConsole::ClearOutputBuffer() {
	output_buffer.clear();
}
HANDLE CConsole::getCurrentConsoleHandle() {
	return foreground;
}
void CConsole::getCurrentCursor() {
	getCurrentCursor(foreground);
}
void CConsole::getCurrentCursor(HANDLE n) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hConsole = getCurrentConsoleHandle();
	GetConsoleScreenBufferInfo(n, &info);
	nowx = info.dwCursorPosition.X,
		nowy = info.dwCursorPosition.Y;
}
void CConsole::putCursor(COORD where) {
	bool ans =
		SetConsoleCursorPosition(foreground, where);
	int t;
	if (!ans)
		t = GetLastError();
}
void CConsole::putCursor(COORD where, HANDLE which) {
	bool ans =
		SetConsoleCursorPosition(which, where);
}
void CConsole::putCursorToEnd() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(foreground, &info);
	//��û���������
	COORD x;
	x.X = 0, x.Y = info.srWindow.Bottom;
	putCursor(x);
	return;
}
void CConsole::__displayImageThread(HWND hwnd) {
	Gdiplus::Image img(ImgFilename.c_str());
	Gdiplus::Graphics gp(GetDC(hwnd));
	isLastThreadRunning = true;
	do {
		if (!tContinueDrawing)
			break;
		gp.DrawImage(&img, WhereTodraw.X, WhereTodraw.Y, img.GetWidth(), img.GetHeight());
		::Sleep(500);
	} while (tContinueDrawing);
	updateScreen();
	ImgFilename.clear();
	isLastThreadRunning = false;
	//����ϸ��߳̽�����
	flag.notify_all();
	//���ѵȴ����������߳�
	drawThread.detach();
	//�������û�����̳߳أ�
	return;
	//�߳̽���
}
void CConsole::displayImage(const std::wstring& Filename, const COORD& where) {
	using std::wstring;
	using std::thread;
	tContinueDrawing = false;
	updateScreen();
	if (isLastThreadRunning)
		flag.wait(tlock);
	//��ֹͣ���ڽ��еĻ�ͼ�̣߳��������һ�������������ڵȴ��߳̽���
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	tContinueDrawing = true;

	WhereTodraw = where;
	ImgFilename = Filename;
	HWND hwnd = GetConsoleWindow();
	drawThread = thread(&CConsole::__displayImageThread, this, hwnd);
	//���߳�
}
bool CConsole::ResizeWindow() {
	tagRECT tNow_Window_Size = getCurrentWindowInfo();
	SMALL_RECT sNow_Win_size;
	CONSOLE_SCREEN_BUFFER_INFOEX scri;
	GetConsoleScreenBufferInfoEx(foreground, &scri);
	//�����Ҳ������
	scri.dwMaximumWindowSize.Y = tNow_Window_Size.bottom - tNow_Window_Size.top;
	SetConsoleScreenBufferInfoEx(foreground, &scri);
	sNow_Win_size.Left = tNow_Window_Size.left;
	sNow_Win_size.Right = tNow_Window_Size.left + window_len;
	sNow_Win_size.Top = tNow_Window_Size.top;
	sNow_Win_size.Bottom = tNow_Window_Size.top + window_width;
	SetConsoleWindowInfo(foreground, false, &(sNow_Win_size));
	return !GetLastError();
}
std::wstring CConsole::__string2wstring(const std::string& str) {
	//խ�ַ�ת���ַ�
	using std::wstring;
	using std::string;
	wstring result;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), nullptr, 0);
	//����ֱ������WINAPI��Ϊת������
	TCHAR* buffer = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}
std::string CConsole::__wstring2string(const std::wstring& wstr) {
	using std::string;
	using std::wstring;
	string result;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
	char* buffer = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, nullptr, nullptr);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}
//��֧��endl�������Ĳ�֧��
CConsole& CConsole::operator<<(std::ostream& (*p)(std::ostream&)) {
	WriteText("\n");
	return *this;
}
CConsole& CConsole::operator<<(const std::string & text) {
	WriteText(text);
	return *this;
}
CConsole& CConsole::operator<<(const int x) {
	char buffer[128]{ 0 };
	sprintf_s(buffer, "%d", x);
	WriteText(buffer);
	return *this;
}
CConsole& CConsole::operator<<(const double x) {
	char buffer[128]{ 0 };
	sprintf_s(buffer, "%f", x);
	WriteText(buffer);
	return *this;
}
CConsole& CConsole::operator<<(const long long x) {
	char buffer[128]{ 0 };
	sprintf_s(buffer, "%lld", x);
	WriteText(buffer);
	return *this;
}
//������������ĺ���.ʵ��*�ڸ����룻���Զ����ڸǷ��ţ���󳤶ȣ����ؽ��յ�������
std::string CConsole::InputPassword(const char star, const size_t maxsize) {
	char p = '\0', buffer[5]{ 0 };
	buffer[0] = star;
	std::string password;
	while (password.length() <= maxsize) {
		p = _getch();
		//�����հ��Զ�ֹͣ����
		if (p != '\n' && p != '\t' && p != '\r' && p != ' ')
			password += p;
		else break;
		if (p == '\b') {
			//�����˸��
			password.pop_back();
			if (!password.empty()) {
			//���������ַ���һ�����˸���һ������Ҫɾ�����ַ�
			//�������һλ
				password.pop_back();
				WriteConsoleA(foreground, "\b", 1, nullptr, nullptr);
				getCurrentCursor();
				DWORD x;
				FillConsoleOutputCharacterA(foreground, ' ', 1, COORD{ nowx,nowy }, &x);
				//�����һ���հ�,��ɾ�������*����
			}

		}
		else
	   //����*����
			WriteConsoleA(foreground, buffer, 1, nullptr, nullptr);
	}
	return password;
}
void CConsole::ClearScreen() {
	//��յ�ǰ��Ļ��������
	stopDrawingThread();
	ClearOutputBuffer();
	updateScreen();
}
void CConsole::Dialog(const std::string& text) {
	ClearScreen();
	setRectangleAttribute();
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(foreground, &info);
	//��û���������
	COORD x{ 5,4 }, y{ 5 + ((info.srWindow.Right - 10) >> 1),4 + ((info.srWindow.Bottom - 8) >> 1) };
	x = DrawRectangle(x, y);
	putCursor(x, background);
	//setColorInput();
	__WriteText(text);
	updateScreen();
}
void CConsole::setRectangleAttribute(short FontColor, short BackColor) {
	RectAttr = FontColor | BackColor;
}
COORD CConsole::DrawRectangle(const COORD& left_up, const COORD& right_down) {

	COORD ans{ 0,0 };
	short width = right_down.X - left_up.X,
		height = right_down.Y - left_up.Y;
	putCursor(left_up, background);

	WriteConsoleA(background, "+", 1, nullptr, nullptr);
	for (short i = 1; i <= width - 1; ++i)
		WriteConsoleA(background, "-", 1, nullptr, nullptr);

	WriteConsoleA(background, "+", 1, nullptr, nullptr);

	getCurrentCursor(background);

	short ox = left_up.X;
	putCursor(COORD{ right_down.X,nowy + 1 }, background);

	for (short i = 1; i <= height - 2; ++i) {
		WriteConsoleA(background, "|", 1, nullptr, nullptr);
		getCurrentCursor(background);
		putCursor(COORD{ right_down.X,nowy + 1 }, background);
	}
	WriteConsoleA(background, "+", 1, nullptr, nullptr);
	putCursor(COORD{ left_up.X,left_up.Y + 1 }, background);

	ox = left_up.X;
	for (short i = 1; i <= height - 2; ++i) {
		WriteConsoleA(background, "|", 1, nullptr, nullptr);
		getCurrentCursor(background);
		putCursor(COORD{ ox,nowy + 1 }, background);
	}
	WriteConsoleA(background, "+", 1, nullptr, nullptr);
	for (short i = 1; i <= width - 1; ++i)
		WriteConsoleA(background, "-", 1, nullptr, nullptr);
	ans = COORD{ left_up.X + 2,left_up.Y + 2 };
	//updateScreen();
	return ans;
}