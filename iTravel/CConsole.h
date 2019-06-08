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
	控制台UI.实现高级控制台显示功能.
	1.	任意位置显示图片
	2.	调整命令输入位置为底部输入；调整颜色
	3.	(TODO)PrettyPrint
	-------------------------------------------------------------------------------------------
	简介：
		维护了两个屏幕缓冲区（称为前景(foreground)和背景(background)）.输出时会输出文本缓冲区的内容到背景，
	之后析构前景，并把背景调整到前景位置，同时再构造一个新的背景.
		绘制图片的部分使用了gdiplus；为了能够让图片持续显示，我们同时维护了一个线程负责不断在前景上绘制指定的
	图片.
		对于输出的支持，为了更大限度地兼容ostream的使用风格，我们针对不同的内置类型重载了左移运算符.另外我们还
	重载了一个接受ostream成员函数指针的函数以使用std::ostream::endl.
	-------------------------------------------------------------------------------------------
	使用说明：
		构造函数接受新的窗口标题；同时初始化gdiplus.如果失败，它会抛出std::runtime_error异常
		接着使用init()初始化输入区域的前景色和背景色，默认蓝底白字

	-------------------------------------------------------------------------------------------
	函数说明：
	getCurrentWindowInfo()		返回当前窗口的矩形信息
	stopDrawingThread()			停止当前的绘图线程
	makeColorfulInput()			负责初始化输入区域；即输出一个>符号后，并把一行填充为指定的颜色
	updateScreen()				用背景替换前景
	WriteText()					用于在当前光标处输出一行文本
	ClearOutputBuffer()			清空当前的输出缓冲区
	getCurrentConsoleHandle()	返回前景屏幕句柄
	getCurrentCursor()			更新指向当前光标位置的nowx,nowy
	putCursor()					设置光标位置
	putCursorToEnd()			设置光标到行末；即放到输入栏处
	__displayImageThread()		内部线程，用于绘制图片
	displayImage()				提供显示图片的接口
	ResizeWindow()				重新调整窗口/缓冲区大小，用于隐藏右侧的滚动条
	__string2wstring()			宽窄字符串转换函数
	__wstring2string()			宽窄字符串转换函数
	operator<<()				把其他类型格式化为字符串后调用WriteText()
*/
namespace std{
	class CConsole {
	public:
		using WinHandle = HWND;
		using Handle = HANDLE;
		using WinRect = tagRECT;
	private:
		//多线程部分
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
		//输出缓冲区
		HANDLE __createNewScreen();
		std::string output_buffer;
		HANDLE hConsole = nullptr,
			background, foreground = nullptr;
		//窗口
		static const short window_width = 300, window_len = 500;
		short nowx = 0, nowy = 0;
		std::string ConsoleTitle;
		short RectAttr = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		short InputBackground = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		//蓝底白字
		//宽窄字符转换
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
		//兼容ostream的endl
		CConsole& operator<<(std::ostream& (*)(std::ostream&));
		tagRECT getCurrentWindowInfo();
		HANDLE getCurrentConsoleHandle();
		std::string UTF82ANSI(const std::string&);
	};
	extern CConsole console;
}
#endif