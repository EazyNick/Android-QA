#include "pch.h"
#include <iostream>

int input_tap(int x, int y) {

	CString tap;
	tap.Format(_T("adb shell input tap %s %s"),x,y);
	CStringA tap_push(tap);
	system(tap_push);

	return 0;
}

int input_Drag(char move[]) {
	CString tap;
	if (move == "Up") {
		tap.Format(_T("adb shell input swipe 100 100 100 300 500"));
	}
	else if (move == "Down") {
		tap.Format(_T("adb shell input swipe 100 300 100 100 500"));
	}
	else if (move == "Left") {
		tap.Format(_T("adb shell input swipe 300 100 100 100 500"));
	}
	else if (move == "Right") {
		tap.Format(_T("adb shell input swipe 100 100 300 100 500"));
	}
	else {
		std::cout << "Drag 명령어 전달값 종류 : Up, Down, Left, Right" << std::endl;
		system("pause");
	}
	CStringA tap_push(tap);
	system(tap_push);

	return 0;
}