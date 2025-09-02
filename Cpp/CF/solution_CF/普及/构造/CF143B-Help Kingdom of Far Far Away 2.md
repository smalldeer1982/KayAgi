# Help Kingdom of Far Far Away 2

## 题目描述

For some time the program of rounding numbers that had been developed by the Codeforces participants during one of the previous rounds, helped the citizens of Far Far Away to convert numbers into a more easily readable format. However, as time went by, the economy of the Far Far Away developed and the scale of operations grew. So the King ordered to found the Bank of Far Far Away and very soon even the rounding didn't help to quickly determine even the order of the numbers involved in operations. Besides, rounding a number to an integer wasn't very convenient as a bank needed to operate with all numbers with accuracy of up to $ 0.01 $ , and not up to an integer.

The King issued yet another order: to introduce financial format to represent numbers denoting amounts of money. The formal rules of storing a number in the financial format are as follows:

- A number contains the integer part and the fractional part. The two parts are separated with a character "." (decimal point).
- To make digits in the integer part of a number easier to read, they are split into groups of three digits, starting from the least significant ones. The groups are separated with the character "," (comma). For example, if the integer part of a number equals 12345678, then it will be stored in the financial format as 12,345,678
- In the financial format a number's fractional part should contain exactly two digits. So, if the initial number (the number that is converted into the financial format) contains less than two digits in the fractional part (or contains no digits at all), it is complemented with zeros until its length equals 2. If the fractional part contains more than two digits, the extra digits are simply discarded (they are not rounded: see sample tests).
- When a number is stored in the financial format, the minus sign is not written. Instead, if the initial number had the minus sign, the result is written in round brackets.
- Please keep in mind that the bank of Far Far Away operates using an exotic foreign currency — snakes ($), that's why right before the number in the financial format we should put the sign "$". If the number should be written in the brackets, then the snake sign should also be inside the brackets.

For example, by the above given rules number 2012 will be stored in the financial format as "$2,012.00" and number -12345678.9 will be stored as "($12,345,678.90)".

The merchants of Far Far Away visited you again and expressed much hope that you supply them with the program that can convert arbitrary numbers to the financial format. Can you help them?

## 说明/提示

Pay attention to the second and third sample tests. They show that the sign of a number in the financial format (and consequently, the presence or absence of brackets) is determined solely by the sign of the initial number. It does not depend on the sign of the number you got after translating the number to the financial format.

## 样例 #1

### 输入

```
2012
```

### 输出

```
$2,012.00```

## 样例 #2

### 输入

```
0.000
```

### 输出

```
$0.00```

## 样例 #3

### 输入

```
-0.00987654321
```

### 输出

```
($0.00)```

## 样例 #4

### 输入

```
-12345678.9
```

### 输出

```
($12,345,678.90)```

# 题解

## 作者：cyffff (赞：4)

# CF143B Help Kingdom of Far Far Away 2
#### [_传送门_](https://www.luogu.com.cn/problem/CF143B)
## 题意
给出一个数，对这个数做以下操作：

- 加上一个字符（加上它$\LaTeX$就会炸掉，自己看题面吧）；

- 小数点前，从个位开始，每三位分一段，用```','```隔开；

- 保留两位小数，超过省去，不足补零；

- 如果这个数是负数，将它取绝对值并用括号括起来。

## 思路
这道题是一道不错的字符串模拟~~水~~题。
#### 一、处理输入
由于位数问题与处理困难，所以我们用```string```或```char```数组存储就行了（以下用```a```表示这个输入的字符串，```len```表示它的长度）。
#### 二、负数
这点也比较简单，直接判断```a[0]```就可以了（字符串下标从 $0$ 开始）。
#### 三、小数
首先判断小数，从 $0$ 循环到 $len-1$，判断每一位是不是```'.'```就行了。
```cpp
for(int i=len-1;i>=0;i--){
	if(a[i]=='.'){
		dot=true;
		len=i;
		break;
	}
}
```
然后是处理保留小数的问题。

如果这个数不是小数，直接输出```.00```就行了。

否则，从找到小数的地方（这里我把```len```设为了小数点位置的下标，见上面的代码）开始，循环到 $min(strlen(a),len+3)$ （有可能这个小数只有一位，循环到 $len+3$ 会溢出），每次输出这个下标上的字符。再有一次补位循环，从 $strlen(a)-len$ 循环到 $2$，每次都输出一个```'0'```。
```cpp
if(dot){
	for(int i=len;i<min(l,len+3);i++){
		putchar(a[i]); 
	}
	for(int i=l-len;i<=2;i++){
		putchar('0');
	}
}else{
	printf(".00");
}
```
#### 四、分段
从第一个数字字符循环到 $len-1$，每次循环输出自己，再做一次判断，如果 $(len-i-1)mod\enspace3==0$并且$i!=len-1$ （$i$ 为循环的数）,就要输出一个逗号。
```cpp
for(int i=0+neg;i<len;i++){
	putchar(a[i]);
	if((len-i-1)%3==0&&i!=len-1){
		putchar(',');
	}
}
```

那么，我们把上述内容整理起来，进入
## 完整代码
 _注释中会给出一些操作的目的的解释_ 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int len;
char a[N];
bool neg,dot;
int main(){
	scanf("%s",a);//输入
	if(a[0]=='-'){//判断正负
		neg=true;
	}
	len=strlen(a);
	int l=len;
	for(int i=len-1;i>=0;i--){
		if(a[i]=='.'){
			dot=true;//是小数
			len=i;//保存小数点下标
			break;
		}
	}
	if(neg){//执行负数操作
		printf("(");
	}
	printf("$");
	for(int i=0+neg;i<len;i++){//如果这个数是负数，则第一位'-'不因算进一位，要加一
		putchar(a[i]);
		if((len-i-1)%3==0&&i!=len-1){
			putchar(',');//分段
		}
	}
	if(dot){
		for(int i=len;i<min(l,len+3);i++){//保留两位小数
			putchar(a[i]); 
		}
		for(int i=l-len;i<=2;i++){//补零
			putchar('0');
		}
	}else{
		printf(".00");//直接补两位零
	}
	if(neg){
		printf(")");
	}
	return 0;
}
/*
代码长度：647B
用时：2.59s 
内存：16.00KB 
*/
```
那就再见了qwq

---

## 作者：Jsxts_ (赞：1)

# 题解 CF143B

[原题传送门](https://www.luogu.com.cn/problem/CF143B)

一道还算简单的字符串模拟，在这里整个输出用[栈](https://blog.csdn.net/gzu_zb/article/details/89886114?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160163905519725222462139%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=160163905519725222462139&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v28_p-2-89886114.pc_first_rank_v2_rank_v28_p&utm_term=STL+%E6%A0%88&spm=1018.2118.3001.4187)存储。

按照题面做以下处理：

1、判断是否是负数，如果是就加上括号。（还有别漏了某个字符）

2、处理小数点以后的数位，并判断各种情况。

3、整数部分从后往前枚举，每三位一个逗号，注意最后没有逗号。

整个模拟过程大概是上面那样，剩下的细节部分就在代码里面描述。

# _Code:_

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
string s;
stack<char> st;
int main() {
	cin >> s;
	int f = 0,fl = s.size();
	if (s[0] == '-') {//特判负数 
		putchar('(');//先输出左括号 
		st.push(')');//答案序列压进右括号 
		f = 1;//标记负数 
	}
	putchar('$'); 
	for (int i = 0+f;i < fl;i ++ ) {//找小数点 
		if (s[i] == '.') {
			fl = i;//确定位置 
			if (s.size() - fl > 2) {
				//特判，如果大于2代表有足够两位小数 
				st.push(s[fl+2]);
			}
			else st.push('0');//否则补0 
			st.push(s[fl+1]);//小数点后一位小数 
			st.push('.');//小数点 
			break;
		}
	}
	if (fl == s.size()) {//代表没有找到小数点 
		st.push('0'),st.push('0'),st.push('.');
		//补齐0与小数点 
	}
	int cnt = 0;
	for (int i = fl - 1;i >= 0+f;i -- ) {//处理整数部分 
		cnt ++;//记录有几个数字 
		st.push(s[i]);//进答案序列 
		if (cnt % 3 == 0 && i > 0+f) st.push(',');
		//三位一逗号，特判一开始不能有逗号 
	}
	while (st.size()) putchar(st.top()),st.pop();//直接输出 
	return 0;
}
```

这道题只要逻辑清晰，就是水题。

~~求赞qwq~~

---

## 作者：wzhcsl (赞：1)

字符串，按照题意模拟即可。

我的做法是先判断这个数是不是负数，再找小数点，从小数点往前每隔三位多输出一个“，”即可，小数点后面如果有两位就输出两位，否则补零就可以了。

一些细节的地方需要注意：

1、字符串的下标是从0开始的

2、“，”的位置注意不能取错

贴代码：

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
	string s, ss; bool f = true, find_dot = false;
	cin >> s;
	if (s[0] == '-') { //如果是负数
		s.erase(0, 1); // 把负号删掉
		f = false;
    }
    if (f == true) cout << "$"; //按题意输出
    else cout << "($";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') { //找到小数点
			find_dot = true;
			for (int j = 0; j < i; j++) { //整数部分
				cout << s[j];
				if ((i - j - 1) % 3 == 0 && j != i - 1) //注意这一步计算
				    cout << ",";
			}
			cout << ".";
			for (int j = i + 1; j <= i + 2; j++) { //小数部分
				if (s[j] >= '0' && s[j] <= '9') 
				    cout << s[j];
				else 
				    cout << "0"; //位数不足就补零
			}
		}
	}
	if (find_dot == false) { //没找到小数点，即是整数
		for (int i = 0; i < s.length(); i++) {
			cout << s[i];
			if ((s.length() - i - 1) % 3 == 0 && i != s.length() - 1)
			    cout << ",";
		}
		cout << ".00"; //小数部分直接输出“.00”
	}
	if (f == false) cout << ")"; //这个不能忘
	return 0;
}
```
~~完结偷偷撒花~~~

---

## 作者：_HiKou_ (赞：0)

简单字符串模拟水题。

思路：

1. 首先判断正负。负号就输出左括号，后面的括号记得输。
2. 输出美元符号。
3. 找小数点位置。如果找不到就返回字符串长度（帮后面的循环做准备）
4. 循环输出。每三个就输出一个逗号。注意如果是负数有一个负号，一定要把循环变量 $t$ 减一。（也就是不算上负号，否则在特殊情况下会多输出一个逗号。)
5. 小数部分分类讨论：没有小数部分就输出 ```.00```，如果小数部分只有一位就补一个 $0$，否则只输出前两位其他的舍去。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int x=s.length(),i;
	if(s[0]=='-')printf("(");//负号
	printf("$");//美元符号
	for(i=0;i<s.length();i++)if(s[i]=='.'){x=i;break;}//找小数点
	int t=x;//变量
	if(s[0]=='-')t--;
	while(t!=0)
	{
		cout<<s[x-t];//从头开始
		if(t%3==1&&t!=1)printf(",");//输出逗号
		t--;
	}
    //小数部分分类讨论
	if(x==s.length())printf(".00");
	else if(x==s.length()-2)cout<<"."<<s[x+1]<<"0";
	else cout<<"."<<s[x+1]<<s[x+2];
	if(s[0]=='-')printf(")");//别忘记
	return 0;
} 
```

---

## 作者：TheSky233 (赞：0)

## Description

给定一个数，按一定格式输出。

- 在数字前加上美元符号。
- 在数字两旁加上括号。
- 整数部分按照三位一个逗号的规则分割。
- 小数部分保留两位小数，不足补全，超出舍去。

## Solution

思路：模拟。

前置知识：栈。

定义一个 STL 中的栈 ```stack<char>stk``` 以及字符串 ```s```，读入```s```。

### 对于小数

查找字符串内有没有小数点，如果没有或者小数点在字符串的末尾，直接在 ```stk.push('0')``` 两遍即可；如果小数点在倒数第二位，先 ```push``` 一个 $0$，再把最后一位 ```push``` 进去；否则直接把小数点后面两位 ```push``` 进去。

别忘了 ```push``` 进一个小数点！

### 对于整数

从小数点前一位往前扫，按题意模拟即可。

### 其余字符

在判小数前判断 ```s[0]``` 是不是符号，是就 ```push``` 进一个右括号，结束时再 ```push``` 进一个左括号。

对于美元符号，直接 ```push``` 进即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int point,cnt;
stack<char> stk;
int _minus;

int main(){
	cin>>s;
	
	_minus=(s[0]=='-')?1:0;
	if(_minus) stk.push(')');
	point=s.find('.');
	if(point==-1 || point==s.length()-1) stk.push('0'),stk.push('0');
	else if(point==s.length()-2) stk.push('0'),stk.push(s[s.length()-1]);
	else stk.push(s[point+2]),stk.push(s[point+1]);
	stk.push('.');
	
	for(int i=(point==-1)?s.length()-1:point-1;i>=_minus;i--){//大于等于负号所在的下标加一
		stk.push(s[i]); cnt++;
		if(cnt==3 && i!=_minus) stk.push(','),cnt=0;//i!=_minus是因为不能扫到负号
	}
	
	stk.push('$');
	if(_minus) stk.push('(');
	
	while(!stk.empty()) putchar(stk.top()),stk.pop();
	return 0; 
}
```

## Conclusion

~~应该是码量最少的 AC 代码之一了~~

---

