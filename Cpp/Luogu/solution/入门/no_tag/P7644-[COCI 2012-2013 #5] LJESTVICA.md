# [COCI 2012/2013 #5] LJESTVICA

## 题目背景

Veronica 在音乐学院上学，她拿到了一张只有音符的乐谱，并且需要识别其所使用的音阶。

## 题目描述

在这个问题中，我们只考虑 A 小调和 C 大调。其中 A 小调音阶为 $\{ A,B,C,D,E,F,G \}$，C 大调音阶为 $\{ C,D,E,F,G,A,B \}$。

称每个音阶的第一个、第四个和第五个音为主调，你需要判断给定的乐谱是 A 小调或是 C 大调。

判断方法：

判断此乐谱中每个小节的第一个音符，是 A 小调的主调或是 C 大调的主调，最后判断哪个音阶的主音个数更多。

如果两者个数一样多，取整个乐谱的最后一个音符。如果最后一个音符为 A 则属于 A 小调，否则属于 C 大调。

## 说明/提示

**【样例解释#1】**

两个小节的第一个音符分别为 `A` 和 `C`，由于两个音阶的主调个数相同，取后出现的 `C`，即 C 大调。


------------

**【数据范围】**

对于 $100\%$ 的数据，保证 $5\le$ 乐谱长度 $\le100$，且给出的乐谱合法。


------------

**【说明】**

本题分值按 COCI 原题设置，满分 $50$。

题目译自 [COCI2012~2013](https://hsin.hr/coci/archive/2012_2013/) [CONTEST #5](https://hsin.hr/coci/archive/2012_2013/contest5_tasks.pdf) _**T1 LJESTVICA**_ 。

## 样例 #1

### 输入

```
AEB|C```

### 输出

```
C-dur```

## 样例 #2

### 输入

```
CD|EC|CD|EC|EF|G|EF|G|GAGF|EC|GAGF|EC|CG|C|CG|C```

### 输出

```
C-dur```

# 题解

## 作者：sid_shi1 (赞：7)

题目：[P7644 [COCI2012-2013#5] LJESTVICA ](https://www.luogu.com.cn/problem/P7644)

思路：

本题只需将字符串从头到尾跑一遍即可，判断每个小节的第一个字符是哪种音节的主调(从题目中可知），然后再将那个音节的计数的变量上加 $1$ 即可。

最后输出主调个数多的音阶。若相等，则查看字符串的最后一个字符，是什么字母就输出什么音阶。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a;
	cin>>a;
	int n=a.size(),x=0,y=0;//x计C调主调的个数，y计A调主调的个数
	for(int i=0;i<=n-1;i++){
		if(i==0 || a[i-1]=='|'){//判断是不是每个小节的第一个，注意a[0]也是
			if(a[i]=='C' || a[i]=='F' || a[i]=='G') x++;//C调主调
			if(a[i]=='A' || a[i]=='D' || a[i]=='E') y++;//A调主调
		}
	}
	if(x>y) cout<<"C-dur";
	if(x<y) cout<<"A-mol";
	if(x==y){//若主调个数相等
		//查看最后一个字符
		if(a[n-1]=='C') cout<<"C-dur";
		else cout<<"A-mol";
	}
	return 0;
}
```


---

## 作者：Leo2020 (赞：4)

```
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int main(){
	int a=0,c=0;
	string n;//输入字符串 
	cin >> n;
	if(n[0]=='A'||n[0]=='D'||n[0]=='E') a++;//因为第一个小节的前面没有 | 判断第一个小节 
	if(n[0]=='C'||n[0]=='F'||n[0]=='G') c++;
	for(int i=1;i<n.size();i++){
		if(n[i]=='|'){//除了第一个小节，每一个小节的前面都有| 
			int j=i+1;
			if(n[j]=='A'||n[j]=='D'||n[j]=='E')a++;//判断A调 
			if(n[j]=='C'||n[j]=='F'||n[j]=='G')c++;//判断C调 
		}
	}
	if(a>c)cout<<"A-mol"<<endl;//判断 
	if(c>a)cout<<"C-dur"<<endl;
	if(a==c){
		if(n[n.size()-1]=='A'||n[n.size()-1]=='D'||n[n.size()-1]=='E') cout<<"A-mol"<<endl;//判断最后一个 
		else cout<<"C-dur"<<endl;
	}
	return 0;
}//结束 
```
注意满分50分

---

## 作者：Nygglatho (赞：2)

我们发现，A 小调主调为 $\{A, D, E\}$，而 C 大调主调为 $\{C, F, G\}$，所以我们直接枚举，如果是小节第一个，即第一个音调以及`|`后面一个就判断，如果是 A 小调主调就让统计 A 小调个数的 $ansA$ 增加 $1$，否则就将统计 C 大调个数的 $ansB$ 增加 $1$。

最后判断时，只要判断 $ansA$ 与 $ansB$ 就行了。

注意：如果相等是判断**最后**一个音符的，同时也只需要判断是不是`A`，不需要判断是不是`D`或`E`。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int ansA, ansB;
int main() {
	string st;
	cin >> st;
	for (int i = 0; i < st.size(); i++) {
		if ((i == 0) || st[i - 1] == '|') {	
			if (st[i] == 'A' || st[i] == 'D' || st[i] == 'E') ansA++;
			else if (st[i] == 'C' || st[i] == 'F' || st[i] == 'G') ansB++;
		}
	}
	if (ansA > ansB) puts("A-mol");
	else if (ansA == ansB) {
		if (st[st.size() - 1] == 'A') puts("A-mol");
		else puts("C-dur"); 
	} else puts("C-dur");
} 
```

---

## 作者：LIANZHENG_SCHOOL (赞：1)

这道题只用看第一个音节，其实就是除第一个音符外，判断分隔号后面的第一位。

如果一样，就再判一次。
```cpp
#include <iostream> 
#include <cstring>
using namespace std;
int main() {
	char s[101];
	cin>>s;
	int amol=0,cdur=0;
	switch(s[0]) {	//第一个音符特判
    		//三种a小调的主调
		case 'A':
		case 'D':
		case 'E':
			amol++;
			break;
           	//三种C大调的主调
		case 'C':
		case 'F':
		case 'G':
			cdur++;
			break;
            	//其它的不理它
		default:
			break;
	}
	for(int i=0 ;i<strlen(s) ;i++) {
		if(s[i]=='|') {
        		//跟在分隔号后面的音符，就是下一个音节的第一个音符
			switch(s[i+1]) {
				case 'A':
				case 'D':
				case 'E':
					amol++;
					break;
				case 'C':
				case 'F':
				case 'G':
					cdur++;
					break;
				default:
					break;
			}
		}
	}
	if(amol>cdur) {
		cout<<"A-mol";
	} else if(amol<cdur) {
		cout<<"C-dur";
	} else {
    		//一样就特判最后一个
		switch(s[strlen(s)-1]) {
			case 'A':
			case 'D':
			case 'E':
				cout<<"A-mol";
				break;
			case 'C':
			case 'F':
			case 'G':
				cout<<"C-dur";
				break;
			default:
				break;
		}
	}
	return 0;
}
```

---

## 作者：int127 (赞：1)

### 前言

不自觉想起了 UVA 的一道音乐素养题……

### 思路

$\operatorname{A} $ 小调的主调是 $\operatorname{A,D,E}$ 。

$\operatorname{C} $ 大调的主调是 $\operatorname{C,F,G}$ 。

每一个字符一次存储判断即可。

### 代码

```cpp
/*
AUTH: July in Xin Chou
LANG: C++
REID: R52109583
ANCH: On
DIFF: Easy
ACED: Yes
*/
int a, c;
char s[201];
//读入
cin>>s+1;
int n=strlen(s+1);
s[0]='丨';
fr(i,1,n,1){
	if(s[i-1]=='丨'){
		if(s[i]=='A'||s[i]=='D'||s[i]=='E') ++a;
		if(s[i]=='C'||s[i]=='F'||s[i]=='G') ++c;
	}
}
//处理
if(a>c) puts("A-mol");
else if(a<c) puts("C-dur");
else{
	if(s[n]=='A') puts("A-mol");
	else puts("C-dur");
}
```
求赞求关注求评论求顶！

---

## 作者：封禁用户 (赞：1)

## P7644 LJESTVICA
[原题链接](https://www.luogu.com.cn/problem/P7644)
## 分析
读题可得：(A , D , E) 为 A 小调主调，(C , F , G)为 C 大调主调。将字符串中每个小节首字母进行判断，计数累加，最后判断即可。

## 思路
从字符串头部开始枚举，当找到分隔符后下一位既是首字母，枚举到字符串最后一位时标记是否为 A 方便判断。


## Code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int ans1,ans2;
string s;
bool tail;
int main(){
	cin>>s;s='|'+s; //字符串首位加'|'，方便判断第一小节首字母
	int k=s.size()-1;
	for(int i=0;i<=k;i++){
		if(s[i]=='|'){ //i位置为分隔符，则i+1位置为小节首字母
			if(s[i+1]=='A'||s[i+1]=='D'||s[i+1]=='E') ans1++;
			if(s[i+1]=='C'||s[i+1]=='F'||s[i+1]=='G') ans2++;
		}
		if(i==k){ //扫到字符串末位，标记备用
			if(s[i]=='A') tail=true;
		}
	}
	
	if(ans1>ans2) cout<<"A-mol"; 
	if(ans1<ans2) cout<<"C-dur";
	if(ans1==ans2){
		if(tail){ //主音一样多，用bool判断
			cout<<"A-mol";
		}else cout<<"C-dur";
	}	
	return 0; //end
}
```


---

