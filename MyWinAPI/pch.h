/** Precompiled header(�̸� �����ϵ� ���): ��� cpp ���ϵ��� �� ������ �����ؾ� �մϴ�.
* define.h: ���α׷����� ����� ����� ��ũ�θ� �����ϴ� ��� �����Դϴ�.
* windows.h: Windows API�� ����ϱ� ���� ��� �����Դϴ�.
* vector : ���� �迭�� ��Ÿ���� ���ø� Ŭ�����Դϴ�.
* map : Ű - �� ���� �����ϰ� �����ϴ� ���ø� Ŭ�����Դϴ�.
* string : ���ڿ��� ��Ÿ���� Ŭ�����Դϴ�.
* cassert : ����� �������� ���Ǵ� �ܾ�(assertion) ���� ��� �����Դϴ�.
* unordered_map : �ؽø��� �����ϴ� ���ø� Ŭ�����Դϴ�.
* Msimg32.lib : TransparentBlt �Լ��� ����ϱ� ���� ���̺귯���Դϴ�.
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
#include <gdiplus.h> //gdi+ ���̺귯��
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

#include <random>


#include "define.h"
#include "function.h"