/** Precompiled header(미리 컴파일된 헤더): 모든 cpp 파일들은 이 파일을 참조해야 합니다.
* define.h: 프로그램에서 사용할 상수와 매크로를 정의하는 헤더 파일입니다.
* windows.h: Windows API를 사용하기 위한 헤더 파일입니다.
* vector : 동적 배열을 나타내는 템플릿 클래스입니다.
* map : 키 - 값 쌍을 저장하고 관리하는 템플릿 클래스입니다.
* string : 문자열을 나타내는 클래스입니다.
* cassert : 디버깅 목적으로 사용되는 단언(assertion) 관련 헤더 파일입니다.
* unordered_map : 해시맵을 구현하는 템플릿 클래스입니다.
* Msimg32.lib : TransparentBlt 함수를 사용하기 위한 라이브러리입니다.
*/
#pragma once

#include <windows.h>

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::make_pair;

#include <string>
using std::string;
using std::wstring;

#include <cassert>
#include <unordered_map>
#include <cmath>
#include <crtdbg.h>

#pragma comment(lib, "Msimg32.lib")
#include <ole2.h>
#include <gdiplus.h> //gdi+ 라이브러리
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

#include <random>


#include "define.h"
#include "function.h"