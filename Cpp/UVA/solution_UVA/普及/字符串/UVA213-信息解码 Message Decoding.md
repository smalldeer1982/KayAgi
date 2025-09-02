# 信息解码 Message Decoding

## 题目描述

考虑下面的01串序列：
```
0，00，01，10，000，001，010，011，100，101，110，0000，0001，···，1101，1110，00000，···
```
首先是长度为1的串，然后是长度为2的串，依此类推。如果看成二进制，相同长度的后一个串等于前一个串加1。注意上述序列中不存在全为1的串。你的任务是是编写一个解码程序。

## 样例 #1

### 输入

```
TNM AEIOU 
0010101100011 
1010001001110110011 
11000 
$#**\ 
0100000101101100011100101000```

### 输出

```
TAN ME 
##*\$```

# 题解

## 作者：baiABC (赞：17)

## 我的做法
1. 用了一个 $read$ 函数来读取 $n$ 个 $0$ 或 $1$ 组成二进制数并转化成十进制；
1. 长度为 $x$ 数值为 $y$ 的编码对应编码头第 $2^x-x-1+y$ 个字符（从 $0$ 开始计数）。
1. $2^x$ 可以表示为 $(1<<x)$。
### code：
```cpp
#include <cstdio>
void read(int n, int &x)
{
    x = 0;
    for(char c; n--; x = (c == '1') + x * 2)
        scanf(" %c", &c); // 读入一位数字0或1
}
int main()
{
    char s[1000];
    for(;;)
    {
        scanf(" "); // 过滤本行前的空白字符
        
        if(fgets(s, 999, stdin) == NULL) return 0;
/** 样例说明编码头是可以有空格的，所以不能用 scanf("%s", s)。**/
        int a, b, c, x, y;
        while(read(3, x), x)
        {
            const int z = (1<<x)-x-1;
            while(read(x, y), y != (1 << x) - 1)
                putchar(s[z+y]);
        }
        puts(""); // 换行
    }
}
```
[AC 记录（20ms）](https://www.luogu.com.cn/record/43870188)



---

## 作者：Maktub (赞：9)

这个题样例说明了一个问题，编码头是可以有空格的，相信大家都是从刘汝佳神犇那里看到的这个题，那个题解抄过来以后样例过不了。需要加几个字母，就是特判一下空格。希望注意。

```
inline int readchar() {
    while (1) {
        int ch = getchar();
        if( ch != '\n' && ch != '\r'&&ch!=' ') return ch ;
    }
}
```

---

## 作者：张鑫杰 (赞：5)

这是一道坑很多的模拟题,很需要仔细的调试.我给出一个与刘汝佳不同的方法,也算是集思广益了.
```cpp
inline string binaryAdd(string &input) {
	input[input.size() - 1] = input[input.size() - 1] + 1;
	bool carry = false;
	for (int i = input.size() - 1; i >= 0; i--) {
		if (carry) {
			input[i]++;
			carry = false;
		}
		if (input[i] == '2') {
			input[i] = '0';
			carry = true;
		}
	}
	if (carry) {
		input = input + "1";
	}
	bool flag = true;
	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] != '1')
			flag = false;
	}
	if (flag)
		input = string(input.size() + 1, '0');
	return input;
}
```
这个函数对一个string进行操作,模拟0,00,01,000,001.........之类的变化
```cpp
map<string, char> code;
```
使一个个字符与0,00,01,000,001类的编码能够以映射的形式一一对应.
```cpp
inline void decode(string codeHeader, string codeString) {
	string tmp;
	for (unsigned int i = 0; i < codeString.size(); i++) {
		if (codeString[i] != ' '&&codeString[i] != '\n'&&codeString[i] != '\r') {
			tmp = tmp + codeString[i];
		}
	}
	codeString = tmp;
	string nowCode = "0";
	for (unsigned int i = 0; i < codeHeader.size(); i++, binaryAdd(nowCode))
		code[nowCode] = codeHeader[i];
	string binaryNum = codeString.substr(0, 3);
	int digitNum = binaryToDigit(binaryNum);
	for (unsigned int i = 3; i < codeString.size(); i += digitNum) {
		nowCode = codeString.substr(i, digitNum);
		bool flag = true;
		for (unsigned int i = 0; i < nowCode.size(); i++) {
			if (nowCode[i] != '1')
				flag = false;
		}
		if (flag) {
			binaryNum = codeString.substr(i + digitNum, 3);
			if (binaryNum == "000") {
				printf("\n");
				return;
			}
			i += 3 + digitNum;
			digitNum = binaryToDigit(binaryNum);
			i -= digitNum;
			continue;
		}
		printf("%c", code[nowCode]);
	}

}
```
这一个函数对信息进行解码,其中第一个for循环是为了去除空格,第二个for循环是为了建立映射关系,最后才进入解码的循环.
以下为全部源码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<sstream>
#include<vector>
#include<cstring>
#include<cmath>
#include<set>
#include<stack>
#include<algorithm>
#include<map>
#define ini(x) memset(x,false,sizeof(x))
#define ALL(x) x.begin(),x.end()
using namespace std;
const int MAXN = 220;
const int INF = -0x3f3f3f3f;
map<string, char> code;
inline int binaryToDigit(string binary) {
	int k = 0, num = 0;
	for (int i = binary.size() - 1; i >= 0; i--, k++) {
		num += static_cast<int>((binary[i] - '0')*pow(2, k));
	}
	return num;
}
inline string binaryAdd(string &input) {
	input[input.size() - 1] = input[input.size() - 1] + 1;
	bool carry = false;
	for (int i = input.size() - 1; i >= 0; i--) {
		if (carry) {
			input[i]++;
			carry = false;
		}
		if (input[i] == '2') {
			input[i] = '0';
			carry = true;
		}
	}
	if (carry) {
		input = input + "1";
	}
	bool flag = true;
	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] != '1')
			flag = false;
	}
	if (flag)
		input = string(input.size() + 1, '0');
	return input;
}
inline void decode(string codeHeader, string codeString) {
	string tmp;
	for (unsigned int i = 0; i < codeString.size(); i++) {
		if (codeString[i] != ' '&&codeString[i] != '\n'&&codeString[i] != '\r') {
			tmp = tmp + codeString[i];
		}
	}
	codeString = tmp;
	//tmp.~string();注意:不删去这句会玄学WA
	string nowCode = "0";
	for (unsigned int i = 0; i < codeHeader.size(); i++, binaryAdd(nowCode))
		code[nowCode] = codeHeader[i];
	string binaryNum = codeString.substr(0, 3);
	int digitNum = binaryToDigit(binaryNum);
	for (unsigned int i = 3; i < codeString.size(); i += digitNum) {
		nowCode = codeString.substr(i, digitNum);
		bool flag = true;
		for (unsigned int i = 0; i < nowCode.size(); i++) {
			if (nowCode[i] != '1')
				flag = false;
		}
		if (flag) {
			binaryNum = codeString.substr(i + digitNum, 3);
			if (binaryNum == "000") {
				printf("\n");
				return;
			}
			i += 3 + digitNum;
			digitNum = binaryToDigit(binaryNum);
			i -= digitNum;
			continue;
		}
		printf("%c", code[nowCode]);
	}

}
int main() {
	vector<string> allCode;
	string codeHeader, codeString;
	while (getline(cin, codeHeader)&&codeHeader!="EOF") {
		allCode.push_back(codeHeader);
	}
	codeHeader.clear();
	for (auto &i : allCode) {
		if (i[0] != '0' && i[0] != '1') {
			if (!codeHeader.empty()) {
				decode(codeHeader, codeString);
			}
			codeString.clear();
			codeHeader = i;

		}
		else {
			codeString = codeString + i;
		}
	}
	decode(codeHeader, codeString);
	return 0;
}
```

---

## 作者：Snowlanuck (赞：2)

从紫书来的,没看题解直接上手,第一次就AC了,开心~!

一开始卡在了读取数据上面... 后来不做动态输入输出了 老实地存数据

第二个难点是生成 01字符串 与 编码头 的一一对应,首选思路用map存储,问题就是怎么生成了,这里我有一个想法 先生成长度为1的 比如0 然后长度为2,例如 00 01 10,
然后长度为3,000 001 011... 直到生成完毕,判断生成的个数是否到达最后即可,思路用的是深搜生成,当然你有其他方法也行,用循环调用深搜即可,第一次生成长度为1,第二次生成长度为2 以此类推即可

以及不需要判断末尾是否为000 直接把字符串长度减3即可,000照样判断,直接无视该条件

代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;

//二进制转十进制
int BinToDec(string value)
{
	int Res = 0;
	for (size_t i = 0, Length = value.length(); i < Length; i++)
		if (value[Length - i - 1] == '1')
			Res += pow(2, i);
	return Res;
}
//判断是否为段落结束(全为1)
bool isEnd(string value)
{
	for (size_t i = 0; i < value.length(); i++)
		if (value[i] == '0')
			return false;
	return true;
}

//生成01字符串(深搜)
char datas[1000];
bool Generate_Flag = false;//标记是否结束
void Generate(int Step, string Dir, int Dir_Length, int Length, int &Index, map<string, char> &m_chars)
{
	if (Index >= Dir_Length)
	{
		Generate_Flag = true;
		return;
	}
	if (Step == Length)
	{
		//拼接字符串
		string str = "";
		for (size_t i = 0; i < Length; i++) { str += datas[i]; }
		if (isEnd(str)) { return; }
		m_chars[str] = Dir[Index];
		Index++;
		return;
	}
	for (size_t i = 0; i < 2; i++)
	{
		datas[Step] = ('0' + i);
		Generate(Step + 1, Dir, Dir_Length, Length, Index, m_chars);
	}
}

int main()
{
	vector<string> Dir, Input;
	string temp;
	while (true)
	{//读取数据
		getline(cin, temp);
		if (temp == "") { break; }
		if (temp[0] == '0' || temp[0] == '1')
		{
			size_t Input_Size = Input.size() - 1;
			for (size_t i = 0; i < temp.size(); i++)
				if (temp[i] != ' ')
					Input[Input_Size] += temp[i];
			//Input[Input.size() - 1] += temp;
		}
		else
		{
			Input.push_back("");
			Dir.push_back(temp);
		}
	}

	for (size_t i = 0; i < Dir.size(); i++)
	{
		//根据编码头生成字典
		map<string, char> m_chars;
		int Index = 0;
		Generate_Flag = false;
		for (int j = 1; (!Generate_Flag); j++)
			Generate(0, Dir[i], Dir[i].length(), j, Index, m_chars);

		for (size_t j = 0; j < Input[i].size() - 3; )
		{
			//读取段落各字符长度
			int part_Length = BinToDec(Input[i].substr(j, 3));
			j += 3;
			string value;
			while (true)
			{
				//010 00 00 10 11 011 000 111 001 0 1 000
				value = Input[i].substr(j, part_Length);
				if (isEnd(value)) { break; }
				j += part_Length;
				cout << m_chars[value];
			}

			j += part_Length;
		}
		cout << endl;
	}

	return 0;
}
```


---

## 作者：Insouciant21 (赞：1)

## 题意

给出编码头和编码文本，输出解码后的文本。

例：
```
编码头 luogu
01 串序列为 0，00，01，10，000，001，010，011，100
即编码 0 - l ， 00 - u ， 01 - o ， 10 - g ， 000 - u

有一编码文本 010101101100011100101011000111000
将其分解为 
		010 - 10, 11
		011 - 000, 111
		001 - 0, 1
		011 - 000, 111
        
即可得到解码文本 gulu
```

## 做法

这题最关键的地方是读入数据，先将所有输入数据读入。

然后维护两个变量进行数据的定位: `row` ，`col` 。

读入编码头 `header` ，建立编码表 `codes`

------------
- 第一维表示编码长度

- 第二维表示编码的十进制数值

- 因为编码长度只有 $3$ 位，最大为 $111_2$。即 $7_{10}$，此时编码的最大值为 $1111110_2=126_{10}$
------------

读入前三个数字，得到编码长度 `len`。

继续读入，将每 `len ` 个数字组成的二进制数 转换成十进制数 `k` 进行一次解码，直到 $k=2^{len}-1$ 即 `len` 个 $1$ 结束。

当 $len = 0$ 时，进行下一个编码头的处理。

### 读入数据

通过变量 `row` 和 `col` 对当前需要的数据在 `allCodes` 中定位。

每读入一个字符就将 `col` 向右移动直到 `allCodes[row].length()` 

当 `col = allCodes[row].length()` 时将 `row` 向下移动，`col` 重置回 $0$ 即可。


代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

char codes[8][128];

void make_table(string str) {
    int q = 0;
    for (int i = 1; q < str.length(); i++)
        for (int j = 0; j < (1 << i) - 1 && q < str.length(); j++)
            codes[i][j] = str[q++];
}

int main() {
    vector<string> allCodes;
    string temp;
    while (getline(cin, temp) && !temp.empty())
        allCodes.push_back(temp);
    for (int row = 0; row < allCodes.size();) {
        string header = allCodes[row++];
        make_table(header);
        string ans;
        int col = 0;
        while (true) {
            bitset<3> p(0);
            for (int i = 0; i < 3; i++) {
                if (col == allCodes[row].length())
                    row++, col = 0;
                p[2 - i] = allCodes[row][col++] - '0';
            }
            int len = int(p.to_ulong());
            if (len == 0) {
                row++;
                break;
            }
            while (true) {
                bitset<10> c(0);
                for (int i = 0; i < len; i++) {
                    if (col == allCodes[row].length())
                        row++, col = 0;
                    c[len - 1 - i] = allCodes[row][col++] - '0';
                }
                int k = int(c.to_ulong());
                if (k == (1 << len) - 1)
                    break;
                ans += codes[len][k];
            }
        }
        cout << ans << endl;
    }
    return 0;
}

```


---

## 作者：AC基德 (赞：0)

# 函数递归

### 方法：
使用2进制，调用函数进行递归

### 分析：
只需把代码理解成2进制，用数组保存字符。

下面介绍代码框架：

```
#include<cstdio>
#include<cstring> //使用memset
int readchar() {...} //请自己填写
int readchar(int c) {...} //请自己填写

int code[8][1<<8]
int readcodes() {...}//请自己填写

int main() {
	while(readcodes())
	{
		//printcodes();
		for(;;) 
		{
			int len = readint(3);
			if(len == 0) break;
			//printf("len=%d\n", len);
			for(;;)
			{
				int v = readint(len);
				if(v == (1 << len)-1) break;
				putchar(code[len][v]);
			}
		}
		putchar('\n'); 
	}
	return 0;//完结撒花 
}
```

本体很具有代表性，代表：
### 编码文件能有多行组成

本蒟蒻的第2篇题解

请管理员通过。



---

