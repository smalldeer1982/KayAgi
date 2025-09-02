# Personalized Cup

## 题目描述

At many competitions that have a word «cup» in its official name the winner is presented with an actual cup. This time the organizers of one unusual programming competition have decided to please the winner even more and to add a nameplate to the cup with the handle of the winner.

The nameplate is to be rectangular and the text on it will be printed as a table of several rows and columns. Having some measurements done, the organizers have found out that the number $ a $ of rows cannot be greater than $ 5 $ while the number $ b $ of columns cannot exceed $ 20 $ . Every cell of the table will contain either an asterisk («\*») or a letter of user's handle.

Furthermore, the organizers want the rows of the table to be uniform, which means that the number of asterisks used in different rows should differ by at most one (i.e. you can't have two asterisks in the first row and none in the second). The main goal, however, is to obtain the winner's handle precisely when reading the table from top to bottom and from left to right in every row (skipping asterisks).

The organizers want for the nameplate to have as few rows as possible and among all valid tables with the minimum number of rows they want to choose the one that has the minimum number of columns.

The winner is not yet determined so your task is to write a program that, given a certain handle, generates the necessary table.

## 样例 #1

### 输入

```
tourist
```

### 输出

```
1 7
tourist
```

## 样例 #2

### 输入

```
MyNameIsLifeIAmForeverByYourSideMyNameIsLife
```

### 输出

```
3 15
MyNameIsLifeIAm
ForeverByYourSi
deMyNameIsL*ife
```

# 题解

## 作者：Tenshi (赞：2)

这是一篇入门级都能看懂的题解~

正如楼下说的一样，这道题看起来不难，但还是~~很恶心的~~

WA了三发qwq（~~有一次交的还是调试的代码~~）

**进入正题：**

分析：

字符串的范围并不大，所以我们可以直接进行讨论，分成：

```cpp
if(len<=20)

else if(len>20 && len<=40)
                          
else if(len>40 && len<=60)                 
                          
else if(len>60 && len<=80)
          
else if(len>80 && len<=100)
```

这五种情况讨论

第一种直接输出

第二到第五种注意对取模进行分类，比如对于第三种情况：

```cpp
else if(len>40 && len<=60)
	{
		if(len%3==0)
		{
			cout<<3<<' '<<len/3<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		}
		else if(len%3==1)
		{
			cout<<3<<' '<<len/3 + 1<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			puts("*");
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			puts("*");
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		} 
		else if(len%3==2)
		{
			cout<<3<<' '<<len/3 + 1<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			puts("*");
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		} 
	}
```

我们就要算好对于每种取模情况输出*的位置（如果算不好可以自己造一个串进去调调，这样挺稳的）。

虽然只要输入的s长一点都会使讨论无法进行，但在这道题目中暴力还是适用的，~~而且能AC~~

那么我就在这里发上最暴力的题解吧！

code：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef unsigned long long ll;
typedef double db;
string s;
int main(){
	cin>>s;
	int len=s.length();
	if(len<=20)
	{
		cout<<1<<' '<<len<<endl;
		cout<<s; 
	}
	else if(len>20 && len<=40)
	{
		if(len%2==0)
		{
			cout<<2<<' '<<len/2<<endl;
			for(int i=0;i<len/2;i++)cout<<s[i];
			cout<<endl;
			for(int i=len/2;i<len;i++)cout<<s[i];
		}
		else
		{
			cout<<2<<' '<<len/2 + 1<<endl;
			for(int i=0;i<len/2;i++)cout<<s[i];
			puts("*");
			for(int i=len/2;i<len;i++)cout<<s[i];
		}
	}
	else if(len>40 && len<=60)
	{
		if(len%3==0)
		{
			cout<<3<<' '<<len/3<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		}
		else if(len%3==1)
		{
			cout<<3<<' '<<len/3 + 1<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			puts("*");
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			puts("*");
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		} 
		else if(len%3==2)
		{
			cout<<3<<' '<<len/3 + 1<<endl;
			for(int i=0;i<len/3;i++)cout<<s[i];
			puts("*");
			for(int i=len/3;i<len*2/3;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/3;i<len;i++)cout<<s[i];
		} 
	}
	else if(len>60 && len<=80)
	{
		if(len%4==0)
		{
			cout<<4<<' '<<len/4<<endl;
			for(int i=0;i<len/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len/4;i<len*2/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/4;i<len*3/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*3/4;i<len;i++)cout<<s[i];
		}
		else if(len%4==1)
		{
			cout<<4<<' '<<len/4 + 1<<endl;
			for(int i=0;i<len/4;i++)cout<<s[i];
			puts("*");
			for(int i=len/4;i<len*2/4;i++)cout<<s[i];
			puts("*");
			for(int i=len*2/4;i<len*3/4;i++)cout<<s[i];
			puts("*");
			for(int i=len*3/4;i<len;i++)cout<<s[i];
		}
		else if(len%4==2)
		{
			cout<<4<<' '<<len/4 + 1<<endl;
			for(int i=0;i<len/4;i++)cout<<s[i];
			puts("*");
			for(int i=len/4;i<len*2/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/4;i<len*3/4;i++)cout<<s[i];
			puts("*");
			for(int i=len*3/4;i<len;i++)cout<<s[i];
		}
		else if(len%4==3)
		{
			cout<<4<<' '<<len/4 + 1<<endl;
			for(int i=0;i<len/4;i++)cout<<s[i];
			puts("*");
			for(int i=len/4;i<len*2/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/4;i<len*3/4;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*3/4;i<len;i++)cout<<s[i];
		}
	}
	else if(len>80 && len<=100)
	{
		if(len%5==0)
		{
			cout<<5<<' '<<len/5<<endl;
			for(int i=0;i<len/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len/5;i<len*2/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/5;i<len*3/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*3/5;i<len*4/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*4/5;i<len;i++)cout<<s[i];
		}
		else if(len%5==1)
		{
			cout<<5<<' '<<len/5 + 1<<endl;
			for(int i=0;i<len/5;i++)cout<<s[i];
			puts("*");
			for(int i=len/5;i<len*2/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*2/5;i<len*3/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*3/5;i<len*4/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*4/5;i<len;i++)cout<<s[i];
		}
		else if(len%5==2)
		{
			cout<<5<<' '<<len/5 + 1<<endl;
			for(int i=0;i<len/5;i++)cout<<s[i];
			puts("*");
			for(int i=len/5;i<len*2/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*2/5;i<len*3/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*3/5;i<len*4/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*4/5;i<len;i++)cout<<s[i];
		}
		else if(len%5==3)
		{
			cout<<5<<' '<<len/5 + 1<<endl;
			for(int i=0;i<len/5;i++)cout<<s[i];
			puts("*");
			for(int i=len/5;i<len*2/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/5;i<len*3/5;i++)cout<<s[i];
			puts("*");
			for(int i=len*3/5;i<len*4/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*4/5;i<len;i++)cout<<s[i];
		}
		else if(len%5==4)
		{
			cout<<5<<' '<<len/5 + 1<<endl;
			for(int i=0;i<len/5;i++)cout<<s[i];
			puts("*");
			for(int i=len/5;i<len*2/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*2/5;i<len*3/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*3/5;i<len*4/5;i++)cout<<s[i];
			cout<<endl;
			for(int i=len*4/5;i<len;i++)cout<<s[i];
		}
	}		
	return 0;
}
```
后记：

顺便说一下，这道题目的翻译是有一点问题的：

原题题面中提及应该满足行数最小，但翻译中没有说到，导致希望全部用五行处理的做法会WA掉：

```cpp
if(len%5==0)
	{
		cout<<5<<' '<<len/5<<endl;
		for(int i=1;i<=len;i++)
		{
			cout<<str[i-1];
			if(i%(len/5)==0)cout<<endl;
		}
		return 0;
	}
	else
	{
		cout<<5<<' '<<len/5 + 1<<endl;
		int rec=len%5;
		int cnt=0;
		for(int i=1;i<=rec;i++)
		{
			for(int j=1;j<=len/5 + 1;j++)
			{
				cout<<str[cnt];
				cnt++;
			}
			cout<<endl;
		} 
		for(int i=rec+1;i<=5;i++)
		{
			for(int j=1;j<=len/5;j++)
			{
				cout<<str[cnt];
				cnt++;
			}
			puts("*");
		}
	}
```


---

## 作者：sqrt404 (赞：1)

## 题面描述：

一个字符串，分行输出，输出的过程中添加 “*” 号实现每行长度一样。

## 思路：

先算每行长度与一共的行数，之后在每行一次一次的输出，注意要与计算的每行长度少输出一个，然后判断是否要输出星星，如果要，输出 “*” 号并星星数减一，否则直接将一开始少输出的那个字符输出。

## 参考代码：

```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int len/*字符串长度*/ = s.size(), line/*行数*/ = len / 20/*先除以20*/ + bool(len % 20)/*然后进行判断*/, now/*字符串当前位置*/ = 0, noww/*每行行数的替身*/, star/*星星数*/ = 0, weight/*每行长度*/;
	while((star + len) % line != 0) star++; // 观察可得，星星数+字符串长度模行数必须为0 
	weight = (star + len) / line; // 计算行数 
	noww = weight; // 生成替身，后面重置 
	cout << line << " " << weight << endl;
	for(int i = 1; i <= line; i++)
	{
		noww--; // 先减一，后面进行判断 
		while(noww--){cout << s[now]; now++;}
		if(star){cout << "*"; star--;} // 判断 
		else{cout << s[now]; now++;}
		noww = weight; // 重置每行长度 
		cout << endl;
	}
	return 0; 
}
```

---

## 作者：LITFLYR (赞：1)

# CF1032B — 题解
### 题意
给定一个字符串，你需要通过在其中添加 `*` 将其分成等长的字符串，但字符串数量 $a\le 5$，字符串长度 $b\le 20$。且每个字符串中最多出现一个 `*`，问现在应当如何划分。
### 基本思路
首先记录字符串的长度，然后从一行开始进行枚举，因为要保证行数最少，所以如果发现在某个行数下可以保证列数不大于数据范围，就直接输出行列数并记录就好了。代码如下：
```cpp
for(int i=1;i<=5;i++){
		if(x/i>20) continue;
		if(x/i==20&&x%i!=0) continue;//这两句是判断行数
		cout << i << " ";//直接输出最小的行数
		a=i;
		if(x%i==0) {
			cout << x/i << endl;
			b=x/i;
			break;//如果能整除，不需要“*”
		}
		else {
			cout << x/i+1 << endl;
			cnt=a-x%a;//如果不能整除，记录需要几个“*”
			b=x/i+1;
			break;
		}
	}
```
是不是非常简单？继续往下看

接下来需要解决输出的问题，我的思路是将 `*` 放在最前面几行的第一个，这时每行就需要少输出一个字符，代码如下：
```cpp
for(int i=0;i<cnt;i++){
		cout << "*" ;
		for(int j=0;j<b-1;j++){
			cout << s[i*(b-1)+j];//自行推导一下，每行 b-1 个字符，在目前输出的这一行之前还有 i 行，这是这行的第 j 个。
		}
		cout << endl;
	}
```
然后就是正常输出的行数：
```cpp
int f=cnt*(b-1);//记录目前应该输出字符串的第几位字符
	for(int i=cnt;i<a;i++){
		for(int j=0;j<b;j++){
			cout << s[f];
			f++;//每次输出完加一
		}
		cout << endl;
	}
```
好啦好啦接下来是完整的代码
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,b,cnt;
int main(){
	cin >> s;
	int x=s.length();
	for(int i=1;i<=5;i++){
		if(x/i>20) continue;
		if(x/i==20&&x%i!=0) continue;
		cout << i << " ";
		a=i;
		if(x%i==0) {
			cout << x/i << endl;
			b=x/i;
			break;
		}
		else {
			cout << x/i+1 << endl;
			cnt=a-x%a;
			b=x/i+1;
			break;
		}
	}
	for(int i=0;i<cnt;i++){
		cout << "*" ;
		for(int j=0;j<b-1;j++){
			cout << s[i*(b-1)+j];
		}
		cout << endl;
	}
	int f=cnt*(b-1);
	for(int i=cnt;i<a;i++){
		for(int j=0;j<b;j++){
			cout << s[f];
			f++;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以采用**分类讨论**的思路：

- 由于字符串长度 $len\leq 100$，所以只需要讨论 $1$ 到 $5$ 行的情况

- 在讨论每种行数中，按照字符数 $len$ 模以 $line$ 所得余数用星星进行补齐，记录好星星数量 $star$ ，最多补 $line-1$ 个星星，最少补 $1$ 个星星，所以一行最多 $1$ 个星星，最少 $0$ 个星星，满足题意。

- 同时，将列数设置为 $\lceil len \div line \rceil$。

- 确定好这些条件，总共要输出 $len+star$ 个字符。

- 输出时单独记录每次输出哪个字符，星星在哪输出都可以，那我们就优先输出。
 
 ## CODE
 
~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=105;
char str[N];
int len/*长度*/,line/*行数*/,row/*列数*/,star/*星星数量*/,num,cnt/*已输出字符数量*/;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>str;
    len=strlen(str);//求长度
    if(len<=20)
    {
        line=1;
        row=len;
    }//一行
    else if(len<=40)
    {
        line=2;
        if(len%2==0)
        {
            row=len/2;
        }
        else
        {
            row=len/2+1;
            star=1;
        }//讨论列数,星星数
    }//两行
    else if(len<=60)
    {
        line=3;
        if(len%3==0)
        {
            row=len/3;
        }
        else if(len%3==1)
        {
            row=len/3+1;
            star=2; 
        }
        else
        {
            row=len/3+1;
            star=1;
        }
    }//三行
    else if(len<=80)
    {
        line=4;
        if(len%4==0)
        {
            row=len/4;
        }
        else if(len%4==1)
        {
            row=len/4+1;
            star=3;
        }
        else if(len%4==2)
        {
            row=len/4+1;
            star=2;
        }
        else
        {
            row=len/4+1;
            star=1;
        }
    }//四行
    else
    {
        line=5;
        if(len%5==0)
        {
            row=len/5;
        }
        else if(len%5==1)
        {
            row=len/5+1;
            star=4;
        }
        else if(len%5==2)
        {
            row=len/5+1;
            star=3;
        }
        else if(len%5==3)
        {
            row=len/5+1;
            star=2;
        }
        else
        {
            row=len/5+1;
            star=1;
        }
    }//五行
    cout<<line<<" "<<row<<"\n";
    num=len+star;//防止出现变化，找替身
    for(int i=1;i<=line;i++)
    {
        if(star>0)
        {
            for(int j=0;j<row-1;j++)//需要输出星星
            {
                cout<<str[cnt];
                cnt++;
            }
            cout<<"*\n";
            star--;//记得-1
        }
        else
        {
            for(int j=0;j<row;j++)//不需要输出星星
            {
                cout<<str[cnt];
                cnt++;
            }
            cout<<"\n";
        }
    }
    return 0;
}


---

## 作者：liuandwang (赞：0)

[CF1032B](https://www.luogu.com.cn/problem/CF1032B)


------------


**做题前我们需要思考几个点：**

1. 需要几行几列

2. ```*``` 的分配

------------
### 问题1：
（$size$ 为字符串长度，$line$ 行数，$average$ 为列数，$star$ 为```*```个数）

如果 $line\le20$ 分成 $1$ 行。

如果 $20<line\le40$ 分成 $2$ 行。

如果 $40<line\le60$ 分成 $3$ 行。

如果 $60<line\le80$ 分成 $4$ 行。

如果 $80<line\le100$ 分成 $5$ 行。

那么可以写出如下代码：
```cpp
if(size<=20){
	line=1;
}else if(size<=40){
	line=2;
}else if(size<=60){
	line=3;
}else if(size<=80){
	line=4;
}else{
	line=5;
}
```
行数确定了，那么每行的长度就可以定为 $average=ceil(1.0\times size\div line)$。

同时也可以得出需要 ```*``` 的个数 $star=average\times line-size$。

------------
### 问题2

因为 ```*``` 的个数肯定不会超过行数，所以在 $star\ne0$ 时 $1$ 行 $1$ 个就可以了。

------------
问题都解决后就可以输出了，我将 ```*``` 的输出放在最后。
```cpp
int flag=0;
for(int i=0;i<line;i++,cout<<endl){
	for(int j=0;j<average-1;j++){
		cout<<x[flag];
		flag++;
	}
	if(star!=0){
		cout<<'*';
		star--;
   }
	else{
		cout<<x[flag];
		flag++;
	}
}
```
最后献上代码

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string x;
	cin>>x;
	int size=x.size();
	int line; 
	if(size<=20){
		line=1;
	}else if(size<=40){
		line=2;
	}else if(size<=60){
		line=3;
	}else if(size<=80){
		line=4;
	}else{
		line=5;
	}
	int average=ceil(1.0*size/line);
	int star=average*line-size;
	cout<<line<<" "<<average<<endl;
	int flag=0;
	for(int i=0;i<line;i++,cout<<endl){
		for(int j=0;j<average-1;j++){
			cout<<x[flag];
			flag++;
		}
		if(star!=0){
			cout<<'*';
			star--;
		}
		else{
			cout<<x[flag];
			flag++;
		}
	}
	return 0;
}
```

---

## 作者：Drind (赞：0)

## 题面分析
1. 题面出锅了，分的行数应该保持最小，不能无脑五行写。
2. 每行只需要输出 $0$ 或 $1$ 个星号即可保持最优。


## 代码实现

首先，我们需要计算行数，可以用非常简单的方法实现:

```cpp
int l=(n-1)/20+1;
//其中l为行数，n为字符串长度。
```

其次我们要计算有多少行需要输出星号:

```cpp
int t=l-n%l;
//l,n均在上面定义过,t为有多少行需要输出星号.
```

然后我们需要计算每行字符数量:

```cpp
n/l+bool(n%l);
//若n无法整除l则需要加1，用bool数可以很好的解决，因为所有非0数字bool数将会自动看做1。
```


对于输出字符串的部分，我们可以分类讨论：
```cpp
//输出*的部分

int now=1;//now为目前输出到的位置，是指针。

for(int i=1;i<=t;i++)
{
	for(int j=now;j<k+now;j++)
		cout<<s[j-1];//string类型变量是从0开始存储，记得要-1.
	now+=k;
	cout<<"*\n";
}


//不输出*的部分

for(int i=1;i<=l-t;i++)
{
	for(int j=now;j<k+now+bool(n%l);j++)//这里和后面指针后移都要加上1，注意不要漏了。
		cout<<s[j-1];
	now+=k+bool(n%l);//加一。
	cout<<endl;
}
```

稍微进行组合，就可以得到完整代码。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string s;//字符串
	cin>>s;
	int n=s.size();//字符串长度
	int l=(n-1)/20+1;//行数
	int k=n/l;//每行实际数量
	int t=l-n%l;//需要输出*的行数
	if(t==l)
		t=0;
	int now=1; //字符串输出到第几位了
	
	cout<<l<<" "<<n/l+bool(n%l)<<endl;
	
	for(int i=1;i<=t;i++)//输出*的部分
	{
		for(int j=now;j<k+now;j++)
			cout<<s[j-1];
		now+=k;//指针后移
		cout<<"*\n";
	}
	for(int i=1;i<=l-t;i++)//不输出*的部分
	{
		for(int j=now;j<k+now+bool(n%l);j++)
			cout<<s[j-1];
		now+=k+bool(n%l);//指针后移，记得加一
		cout<<endl;
	}
}
```

祝您 [AC](https://www.luogu.com.cn/record/75975581)！

---

## 作者：CGDGAD (赞：0)

**这道题看起来不难，其实挺难的，主要是三个大问题：**

- 分成几行几列？
- `*` 的分配问题
- 输出 `*` 的实现方式

### 思路：

首先，分成几行几列，我是这样分的：（假设 $length$ 是输入的字符串的长度）

如果 $len \leq 20$，分成一行。

如果 $20 \lt len \leq 40$，分成两行。

如果 $40 \lt len \leq 60$，分成三行。

如果 $60 \lt len \leq 80$，分成四行。

如果 $80 \lt len \leq 100$，分成五行。

其实很简单。

这样确定完了分成几行以后，分成几列就确定了，用 $len$ 去除以 $1$，$2$，$3$，$4$ 或 $5$，向上取整。

这样， `*` 的个数怎么确定？

举个例子：一个字符串有 $67$ 个字符。

那么显然它要被分配到 $4$ 行上面去。

明显每一行要分配 $ceil(67 \div 4) = 17$ 个字符。

可是 $4 \times 17 = 68 \gt 67$，多出来了一个字符，那么 `*` 就只用一个。

所以个数确定了，是用 **列数 $\times$ 行数 $-$ 总字符数**。这个式子可以化简为 **行数 $-$ ($len$ 除以行数的余数)。**

那么第二个问题来了，怎么分配 `*` 呢？

因为 `*` 的个数肯定不会超过行数，所以顶多一行一个就行了。

**这一部分的实现代码：**

```cpp
const int length = strlen(string);
int lines, width, r;
if (length <= 20) {
    lines = 1;		width = length;		r = 0;
} else if (length <= 40) {
    lines = 2;		width = length / 2;	r = length % 2;
} else if (length <= 60) {
    lines = 3;		width = length / 3;	r = length % 3;
} else if (length <= 80) {
    lines = 4;		width = length / 4;	r = length % 4;
} else {
    lines = 5;		width = length / 5;	r = length % 5;
}
```

大问题搞定了，现在就是输出的问题了。

### 输出：

主要就是输出星号的问题。

```cpp
// 如果有余数  那么width就得加一 （上文中说的向上取整）
printf("%d %d\n", lines, r == 0 ? width : width + 1);
int index = 0;
for (int i = 1; i <= lines; i += 1) { // 遍历每一行
    for (int j = 1; j <= width; j += 1) {  // 遍历每一列
        printf("%c", string[index++]);
    }
    if (r != 0) { // 不能正好分配成几行，有余数，width要加一，得再输出一个字符
        if (i <= r) printf("%c", string[index++]);
        // 这里用了一个特别的方式，
        // 如果 i <= r 就输出字符串的后一个字符
        // 如果 i > r 就输出 *
        // 这样就正好输出了 lines - r 个星号，与上文讲的一样。
        else printf("*");
    }
    printf("\n");
}
```

完整的代码就不给了。就把上面两段拼起来放进 `main` 里加点头文件什么的就差不多了。

---

## 作者：EdenHazard (赞：0)

~~一个月前写的题，既然没人写题解，那蒟蒻就写一篇吧~~
# 基本思路
既然是输出任意一个解，那么*号的位置在那里是没有关系的。我的思路是默认*号在最后面，然后对输入的字符串输出的行数进行分类。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
string s;
void print(int a,int b,int p)//打印结果 
{
    for(int i=1;i<=a;i++)
    {
        for(int j=1;j<=b;j++) printf("%c",s[p++]);
        printf("\n");
    }
}
signed main()
{
    cin>>s;//输入字符串
	//判断 
    if(s.size()%20==0)
    {
        a=s.size()/20, b=20;
        printf("%d %d\n",a,b);
        print(a,b,0);
    }
    else
    {
        a=s.size()/20+1;
        if(s.size()%a==0)
        {
            b=s.size()/a;
            printf("%d %d\n",a,b);
            print(a,b,0);
        }
        else
        {
            b=s.size()/a+1;
            printf("%d %d\n",a,b);
            int cnt=0, flag=0;
            for(int i=1;i<=a;i++)
            {
                if(flag==0 && (s.size()-cnt)%(b-1)==0) b--, flag=1;
                for(int j=1;j<=b;j++) printf("%c",s[cnt++]);
                if(flag) printf("*");
                printf("\n");
            }
        }
    }
    return 0;
}
```
求过

---

## 作者：weihaozhen2010 (赞：0)

# **思路：**


------------
- 思路：这道题很明显，第一想法暴力枚举行数。

- 因为长度是 $\leq 100$ 的，所以只需要分类讨论 $1$ 到 $5$ 行的情况。

```cpp
if(len<=20)//一行，直接输出
if(len>20&&len<=40)//两行，见下一步
if(len>40&&len<=60)//三行，见下一步
if(len>60&&len<=80)//四行，见下一步
if(len>80&&len<=100)//五行，见下一步
```
- 接着，针对 $2$ 到 $5$ 行的情况，再分类讨论长度 $len$ 除以行数 $line$ 的余数，很明显余数肯定是 $1 \dots (line-1)$ 这几种情况，于是就在恰当的地方补上 $line$ 减去余数个星号数,并且分行输出字符串，具体看代码。

- 注意：每一行最多 $1$ 个星星。

# **参考代码：**


------------

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	char a[105];
	cin>>a;
	int len=strlen(a);
	if(len<=20)
	{
		cout<<"1"<<" "<<len<<"\n";
		for(int i=0;i<len;i++)
		{
			cout<<a[i];	
		} 
	}
	else if(len>20&&len<=40)
	{
		if(len%2==0)
		{
			cout<<"2";
			cout<<" ";
			cout<<len/2;
			cout<<"\n";
			for(int i=0;i<len/2;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len/2;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else
		{
			cout<<"2";
			cout<<" ";
			cout<<len/2+1;
			cout<<"\n";
			for(int i=0;i<len/2;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/2;i<len;i++)
			{
				cout<<a[i];
			}
		}
	}
	else if(len>40&&len<=60)
	{
		if(len%3==0)
		{
			cout<<"3";
			cout<<" ";
			cout<<len/3;
			cout<<"\n";
			for(int i=0;i<len/3;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len/3;i<len*2/3;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/3;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%3==1)
		{
			cout<<"3";
			cout<<" ";
			cout<<len/3+1;
			cout<<"\n";
			for(int i=0;i<len/3;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/3;i<len*2/3;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*2/3;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%3==2)
		{
			cout<<"3";
			cout<<" ";
			cout<<len/3+1;
			cout<<"\n";
			for(int i=0;i<len/3;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/3;i<len*2/3;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/3;i<len;i++)
			{
				cout<<a[i];
			}
		}
	}
	else if(len>60&&len<=80)
	{
		if(len%4==0)
		{
			cout<<"4";
			cout<<" ";
			cout<<len/4;
			cout<<"\n";
			for(int i=0;i<len/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len/4;i<len*2/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/4;i<len*3/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*3/4;i<len;i++)
			{
				cout<<a[i];	
			} 
		}
		else if(len%4==1)
		{
			cout<<"4";
			cout<<" ";
			cout<<len/4+1;
			cout<<"\n";
			for(int i=0;i<len/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/4;i<len*2/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*2/4;i<len*3/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*3/4;i<len;i++)
			{
				cout<<a[i];	
			} 
		}
		else if(len%4==2)
		{
			cout<<"4";
			cout<<" ";
			cout<<len/4+1;
			cout<<"\n";
			for(int i=0;i<len/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/4;i<len*2/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/4;i<len*3/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*3/4;i<len;i++)
			{
				cout<<a[i];	
			} 
		}
		else if(len%4==3)
		{
			cout<<"4";
			cout<<" ";
			cout<<len/4+1;
			cout<<"\n";
			for(int i=0;i<len/4;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/4;i<len*2/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/4;i<len*3/4;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*3/4;i<len;i++)
			{
				cout<<a[i];	
			} 
		}
	}
	else if(len>80&&len<=100)
	{
		if(len%5==0)
		{
			cout<<"5";
			cout<<" ";
			cout<<len/5;
			cout<<"\n";
			for(int i=0;i<len/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len/5;i<len*2/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/5;i<len*3/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*3/5;i<len*4/5;i++)
			{
				cout<<a[i];	
			} 
			cout<<"\n";
			for(int i=len*4/5;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%5==1)
		{
			cout<<"5";
			cout<<" ";
			cout<<len/5+1;
			cout<<"\n";
			for(int i=0;i<len/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/5;i<len*2/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*2/5;i<len*3/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*3/5;i<len*4/5;i++)
			{
				cout<<a[i];	
			} 
			cout<<"*";
			cout<<"\n";
			for(int i=len*4/5;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%5==2)
		{
			cout<<"5";
			cout<<" ";
			cout<<len/5+1;
			cout<<"\n";
			for(int i=0;i<len/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/5;i<len*2/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*2/5;i<len*3/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*3/5;i<len*4/5;i++)
			{
				cout<<a[i];	
			} 
			cout<<"*";
			cout<<"\n";
			for(int i=len*4/5;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%5==3)
		{
			cout<<"5";
			cout<<" ";
			cout<<len/5+1;
			cout<<"\n";
			for(int i=0;i<len/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/5;i<len*2/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/5;i<len*3/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len*3/5;i<len*4/5;i++)
			{
				cout<<a[i];	
			} 
			cout<<"\n";
			for(int i=len*4/5;i<len;i++)
			{
				cout<<a[i];
			}
		}
		else if(len%5==4)
		{
			cout<<"5";
			cout<<" ";
			cout<<len/5+1;
			cout<<"\n";
			for(int i=0;i<len/5;i++)
			{
				cout<<a[i];
			}
			cout<<"*";
			cout<<"\n";
			for(int i=len/5;i<len*2/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*2/5;i<len*3/5;i++)
			{
				cout<<a[i];
			}
			cout<<"\n";
			for(int i=len*3/5;i<len*4/5;i++)
			{
				cout<<a[i];	
			} 
			cout<<"\n";
			for(int i=len*4/5;i<len;i++)
			{
				cout<<a[i];
			}
		}
	}
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
由于字符串的长度不超过 $100$ 位，所以最多只能分成 $5$ 行。

只要对字符串分的行数进行暴力判断，再对列数进行暴力判断，就可以得到结果。字符串的行数为 $\lceil\frac{|s|}{20}\rceil$。

同时，由于有多种情况时，输出行数尽可能少的，所以每行只输出最多一个 `*`。这样，列数就是 $\lceil\frac{|s|}{\lceil\frac{|s|}{20}\rceil}\rceil$。
### 代码：
```cpp
#define MAIN int main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
#define LL long long
#define ULL unsigned long long
#define LD long double
#define STR string
#define EL '\n'
#define BK break
#define CTN continue
#define INF INT_MAX
#define UINF INT_MIN
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
//以上为缺省源
#include <bits/stdc++.h>
USING;
char a[105];
int len,i;
void pr3(char ch1,char ch2)//行数为 3 时的输出函数
{
	OUTL(len / 3 + 1);
	FP(i,0,len / 3)
		OUT(a[i]);
	if(ch1)
		OUTL(ch1);
	else
		OUT(EL);
	FP(i,i,len * 2 / 3)
		OUT(a[i]);
	if(ch2)
		OUTL(ch2);
	else
		OUT(EL);
	FP(i,i,len)
		OUT(a[i]);
}
void pr4(char ch1,char ch2,char ch3)//行数为 4 时的输出函数
{
	OUTL(len / 4 + 1);
	FP(i,0,len >> 2)
		OUT(a[i]);
	if(ch1)
		OUTL(ch1);
	else
		OUT(EL);
	FP(i,i,len >> 1)
		OUT(a[i]);
	if(ch2)
		OUTL(ch2);
	else
		OUT(EL);
	FP(i,i,(len * 3) >> 2)
		OUT(a[i]);
	if(ch3)
		OUTL(ch3);
	else
		OUT(EL);
	FP(i,i,len)
		OUT(a[i]);
}
void pr5(char ch1,char ch2,char ch3,char ch4)//行数为 5 时的输出函数
{
	OUTL(len / 5 + 1);
	FP(i,0,len / 5)
		OUT(a[i]);
	if(ch1)
		OUTL(ch1);
	else
		OUT(EL);
	FP(i,i,len * 2 / 5)
		OUT(a[i]);
	if(ch2)
		OUTL(ch2);
	else
		OUT(EL);
	FP(i,i,len * 3 / 5)
		OUT(a[i]);
	if(ch3) 
		OUTL(ch3);
	else
		OUT(EL);
	FP(i,i,len * 4 / 5)
		OUT(a[i]);
	if(ch4)
		OUTL(ch4);
	else
		OUT(EL);
	FP(i,i,len)
		OUT(a[i]);
}
MAIN
{
	SPEEDUP;
	IN(a);
	len = strlen(a);
	if(len <= 20)//行数为 1 的情况
	{
		OUT("1 ");
		OUTL(len);
		FP(i,0,len)
			OUT(a[i]);
	}
	else if(20 <= len && len <= 40)//行数为 2 的情况
	{
		OUT("2 ");
		if(len % 2)
		{
			OUTL((len >> 1) + 1);
			FP(i,0,len >> 1)
				OUT(a[i]);
			OUTL('*');
			FP(i,i,len)
				OUT(a[i]);
		}
		else
		{
			OUTL((len >> 1));
			FP(i,0,len >> 1)
				OUT(a[i]);
			OUT(EL);
			FP(i,i,len)
				OUT(a[i]);
		}
	}
	else if(40 < len && len <= 60)//行数为 3 的情况
	{
		OUT("3 ");
		if(!(len % 3))
		{
			OUTL(len / 3);
			FP(i,0,len)
			{
				if(!(i % (len / 3)) && i)
					OUT(EL);
				OUT(a[i]);
			}
		}
		else if(len % 3 == 1)
			pr3('*','*');
		else
			pr3('*','\0');
	}
	else if(60 < len && len <= 80)//行数为 4 的情况
	{
		OUT("4 ");
		if(!(len % 4))
		{
			OUTL(len / 4);
			FP(i,0,len)
			{
				if(!(i % (len >> 2)) && i)
					OUT(EL);
				OUT(a[i]);
			}
		}
		else if(len % 4 == 1)
			pr4('*','*','*');
		else if(len % 4 == 2)
			pr4('*','\0','*');
		else
			pr4('*','\0','\0');
	}
	else//行数为 5 的情况
	{
		OUT("5 ");
		if(!(len % 5))
		{
			OUTL(len / 5);
			FP(i,0,len)
			{
				if(!(i % (len / 5)) && i)
					OUT(EL);
				OUT(a[i]);
			}
		}
		else if(len % 5 == 1)
			pr5('*','*','*','*');
		else if(len % 5 == 2)
			pr5('*','*','\0','*');
		else if(len % 5 == 3)
			pr5('*','\0','*','\0');
		else if(len % 5 == 4)
			pr5('*','\0','\0','\0');
	}
	END;
}
```

---

