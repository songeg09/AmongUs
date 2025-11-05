#pragma once
#pragma comment(lib, "msimg32.lib")
#define _USE_MATH_DEFINES //수학 라이브러리의 define 사용 전처리기
#define _CRTDBG_MAP_ALLOC //crt 메모리 누수 define 사용 전처리기
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
#include"framework.h"
#include<vector>
#include<string>
#include<map>
#include<assert.h>
#include<format>
#include<iostream>
#include<functional>
#include<math.h>
#include<format>
#include<time.h>
#include<fstream>
#include <stdlib.h>
#include <crtdbg.h>
#include"define.h"
#include"struct.h"
#include"const.h"