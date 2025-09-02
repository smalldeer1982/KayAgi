# [NWRRC 2021] Anno Domini 2022

## 题目描述

很快我们将迎来 2022 年新年，但这个数字究竟意味着什么呢？你可能知道，这种纪年系统是由 Dionysius Exiguus 在公元 525 年发明的。他选择耶稣基督的诞生作为“主的纪年”（拉丁语为 Anno Domini，简称 AD）的起点。在此之前的所有年份都按倒序计数，被称为“公元前”（简称 BC）。

这个纪年系统的一个有趣细节是：没有公元 0 年——公元前 1 年（1 BC）之后紧接着就是公元 1 年（AD 1）。因此，如果两个日期分别属于不同纪元，计算它们之间的时间差有时会比较棘手。

为了简化这个任务，请编写一个程序，计算输入中给定的两个年份的 1 月 1 日之间相隔了多少年。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 BC
AD 1```

### 输出

```
1```

## 样例 #2

### 输入

```
AD 1
AD 2001```

### 输出

```
2000```

## 样例 #3

### 输入

```
AD 2022
5508 BC```

### 输出

```
7529```

# 题解

## 作者：mcz_WANGXIAO (赞：1)

## 题意
给定两个年份，求出它们的差。
## 思路
分类讨论，不难得到如果两个年份类型相同（都是公元前或公元），它们的差就是两个年份相减的绝对值；如果它们类型不同，则差值为两个年份相加减去一。
## 实现
通过读取字符串来判断年份类型，使用变量标记它们的类型。再通过分类逐为读取字符串存储为整数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string a,b,c,d;
	int n1 = 0,n2 = 0,y1,y2; 
	cin>>a>>b>>c>>d;
	if(a[0] == 'A') {
		for(int i = 0;i < b.length() ;i++) {
			n1 = n1*10+int(b[i]-'0');
		}
		y1 = 1;
	} else {
		for(int i = 0;i < a.length() ;i++) {
			n1 = n1*10+int(a[i]-'0');
		}
		y1 = 2;
	} 
	if(c[0] == 'A') {
		for(int i = 0;i < d.length() ;i++) {
			n2 = n2*10+int(d[i]-'0');
		}
		y2 = 1;
	} else {
		for(int i = 0;i < c.length() ;i++) {
			n2 = n2*10+int(c[i]-'0'); 
		}
		y2 = 2;
	} 
	if(y1 == y2) cout<<abs(n1-n2);
	else cout<<n1+n2-1;
} 
```

---

## 作者：_____Elysia_____ (赞：1)

题目要求计算两个年份的差，难点在于读入年份时要读入两个字符串，如果是公元前则第一个字符串是数字，如果是公元后则第二个字符串是数字。

此时可以这样：如果第一个字符串是数字则说明这是一个公元前年份，反之则是公元后年份。可以使用 `isdigit` 函数判断是否是数字，`stoi` 函数转换字符串为整型。注意没有公元 $0$ 年，所以处理公元前年份时要加 $1$。

最后注意需要计算的是两个年份相隔的年数，不能直接相减（因为这样会得到负数），需要用 `abs` 函数取绝对值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string x,y,z,w;
    int a,b;
    cin>>x>>y>>z>>w;
    if(isdigit(x[0]))a=-stoi(x)+1;
    else a=stoi(y);
    if(isdigit(z[0]))b=-stoi(z)+1;
    else b=stoi(w);
    cout<<abs(b-a);
}
```

---

## 作者：b_donk (赞：0)

### 题目大意

给定一个字符串和数字，表示当前纪元与年份，求两个年份一月一日之间的时间差。

### 题目思路
对于每个输入的年份，判断它是 AD 还是 BC 纪元，并提取相应的数值，计算它们之间的绝对差值。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int py(string s) { // 转换年份的函数
    if (s.find("AD") == 0) {
        int year = stoi(s.substr(3));
        return year;
    } else {
        int pos = s.find(' ');
        int year = stoi(s.substr(0, pos));
        return year*(-1) + 1; // BC纪元的转换
    }
}

main() {
    string year1, year2;
    getline(cin, year1);
    getline(cin, year2);
    int y1 = py(year1);
    int y2 = py(year2);
    cout << abs(y2-y1); // 求两个年份的差值
    return 0;
}
```
希望这篇题解能够帮到你。

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13628)

### 题目分析
我们只需要处理以下两种情况：

1. 对于 `BC`，转换为 $-年份+1$（没有公元 $0$ 年）。
2. 对于 `AD`，直接取年份。

相减即可。

### 代码实现
```cpp
#include <bits/stdc++.h>

using namespace std;

string s1,s2;

int y(string s){
	if(s.find("BC")!=string::npos){//判断是不是 BC
		int pos=s.find(' ');
		int num=stoi(s.substr(0,pos));//取数
		return -num+1;
	}
	else{
		int pos=s.find(' ');
		int num=stoi(s.substr(pos+1));
		return num;
	}
}

signed main()
{
	getline(cin,s1);//整行读入
	getline(cin,s2);
	cout<<abs(y(s1)-y(s2));
	return 0;
}
```

---

