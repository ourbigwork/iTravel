#pragma once
#ifndef Console_H_ZYN
#define Console_H_ZYN
#include "pch.h"
#include <gdiplus.h>
//#include "constStr.h"
#pragma comment(lib,"Gdiplus.lib")
//	CConsole Class 
/*
											CConsole
																	By:zyounan
	-------------------------------------------------------------------------------------------
	����̨UI.ʵ�ָ߼�����̨��ʾ����.
	1.	����λ����ʾͼƬ
	2.	������������λ��Ϊ�ײ����룻������ɫ
	3.	(TODO)PrettyPrint
	-------------------------------------------------------------------------------------------
	��飺
		ά����������Ļ����������Ϊǰ��(foreground)�ͱ���(background)��.���ʱ������ı������������ݵ�������
	֮������ǰ�������ѱ���������ǰ��λ�ã�ͬʱ�ٹ���һ���µı���.
		����ͼƬ�Ĳ���ʹ����gdiplus��Ϊ���ܹ���ͼƬ������ʾ������ͬʱά����һ���̸߳��𲻶���ǰ���ϻ���ָ����
	ͼƬ.
		���������֧�֣�Ϊ�˸����޶ȵؼ���ostream��ʹ�÷��������Բ�ͬ�������������������������.�������ǻ�
	������һ������ostream��Ա����ָ��ĺ�����ʹ��std::ostream::endl.
	-------------------------------------------------------------------------------------------
	ʹ��˵����
		���캯�������µĴ��ڱ��⣻ͬʱ��ʼ��gdiplus.���ʧ�ܣ������׳�std::runtime_error�쳣
		����ʹ��init()��ʼ�����������ǰ��ɫ�ͱ���ɫ��Ĭ�����װ���

	-------------------------------------------------------------------------------------------
	����˵����
	getCurrentWindowInfo()		���ص�ǰ���ڵľ�����Ϣ
	stopDrawingThread()			ֹͣ��ǰ�Ļ�ͼ�߳�
	makeColorfulInput()			�����ʼ���������򣻼����һ��>���ź󣬲���һ�����Ϊָ������ɫ
	updateScreen()				�ñ����滻ǰ��
	WriteText()					�����ڵ�ǰ��괦���һ���ı�
	ClearOutputBuffer()			��յ�ǰ�����������
	getCurrentConsoleHandle()	����ǰ����Ļ���
	getCurrentCursor()			����ָ��ǰ���λ�õ�nowx,nowy
	putCursor()					���ù��λ��
	putCursorToEnd()			���ù�굽��ĩ�����ŵ���������
	__displayImageThread()		�ڲ��̣߳����ڻ���ͼƬ
	displayImage()				�ṩ��ʾͼƬ�Ľӿ�
	ResizeWindow()				���µ�������/��������С�����������Ҳ�Ĺ�����
	__string2wstring()			��խ�ַ���ת������
	__wstring2string()			��խ�ַ���ת������
	operator<<()				���������͸�ʽ��Ϊ�ַ��������WriteText()
*/
namespace std{
	class CConsole {
	public:
		using WinHandle = HWND;
		using Handle = HANDLE;
		using WinRect = tagRECT;
	private:
		//���̲߳���
		void __displayImageThread(HWND hwnd);
		std::condition_variable flag;
		std::mutex lockk;
		std::unique_lock<std::mutex> tlock;
		std::thread drawThread;
		bool tContinueDrawing = true,
			isLastThreadRunning = false;
		//gdiplus
		ULONG_PTR token;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		std::wstring ImgFilename;
		COORD WhereTodraw{ 0,0 };
		//���������
		HANDLE __createNewScreen();
		std::string output_buffer;
		HANDLE hConsole = nullptr,
			background, foreground = nullptr;
		//����
		static const short window_width = 300, window_len = 500;
		short nowx = 0, nowy = 0;
		std::string ConsoleTitle;
		short RectAttr = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		short InputBackground = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		//���װ���
		//��խ�ַ�ת��
		std::wstring __string2wstring(const std::string&);
		std::string __wstring2string(const std::wstring&);
		void __setDefaultColor();

		void __WriteText(const std::string&);
	public:
		std::wstring string2wstring(const std::string& str) {
			return __string2wstring(str);
		}
		std::string wstring2string(const std::wstring& wstr) {
			return __wstring2string(wstr);
		}
		using WinHandle = HWND;
		using WinRect = tagRECT;
		CConsole(const std::string&);
		CConsole() = delete;
		CConsole(const CConsole&) = delete;
		CConsole(const CConsole&&) = delete;
		CConsole& operator=(const CConsole&) = delete;
		CConsole& operator=(const CConsole&&) = delete;
		void init(short, short);
		~CConsole() = default;
		void displayImage(const std::wstring&, const COORD& where);
		void putCursor(COORD);
		void putCursor(COORD, HANDLE);
		void Dialog(const std::string &,const COORD&,const COORD&);
		void putCursorToEnd();
		COORD DrawRectangle(const COORD&, const COORD&);
		void setRectangleAttribute(short = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, short = BACKGROUND_BLUE);
		void stopDrawingThread();
		//void putCursorToBegin();
		void getCurrentCursor();
		void getCurrentCursor(HANDLE);
		bool ResizeWindow();
		void updateScreen();
		//void ResumeDefaultFontColor();
		void setColorInput(short = 0, short = 0);
		void makeColorfulInput();
		void ClearOutputBuffer();
		void ClearScreen();
		void WriteText(const std::string&);
		void WriteText(const std::wstring&);
		std::string InputPassword(const char = '*', const size_t = 16);
		CConsole& operator<<(const std::string&);
		CConsole& operator<<(const std::wstring &);
		CConsole& operator<<(const int);
		CConsole& operator<<(const double);
		CConsole& operator<<(const long long);
		CConsole& operator<<(const size_t);
		//����ostream��endl
		CConsole& operator<<(std::ostream& (*)(std::ostream&));
		tagRECT getCurrentWindowInfo();
		HANDLE getCurrentConsoleHandle();
		std::string UTF82ANSI(const std::string&);
	};
	extern CConsole console;
}
#endif