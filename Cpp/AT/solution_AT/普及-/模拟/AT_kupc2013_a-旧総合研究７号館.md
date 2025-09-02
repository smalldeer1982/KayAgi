# 旧総合研究７号館

## 题目描述

有一个宿舍，最初名字叫 `kogakubu10gokan`，这个宿舍修改了 $n$ 次名字，第 $i$ 次修改名字在第 $a_i$ 年，名字改为了 $s_i$。现在请你查询第 $x$ 年宿舍的名字。

## 说明/提示

对于 $100\%$ 的数据：$1\le n,x\le50$，$2\le a_i\le50$，$1\le|s_i|\le30$。

# 题解

## 作者：zjyqwq (赞：7)

### AT643题解

Pascal题解来一发！！


------------

本题思路很简单，但是题面令人很疑惑，建议大家戳一[戳](https://atcoder.jp/contests/kupc2013/tasks/kupc2013_a)。



------------
#### 思路
思路很简单，暴力即可。

单判一下大于等于 $n$ 的情况，然后再用循环将整个桶数组赋值一遍，桶数组的下标就是年份。

------------
#### 注意
还是那句老话：输出要换行！！！


------------
#### 代码
```Pascal
var
n,q,i,j:longint;
a:array[0..55]of longint;
s,sum:array[0..55]of string;//定义
 begin
  readln(n,q);
  for i:=1 to n do 
   begin
    readln(a[i],s[i]);//输入
    delete(s[i],1,1);
   end;
  a[0]:=1;
  s[0]:='kogakubu10gokan';//基本操作，赋初值，方便后面运行
  if q>=a[n] then  begin writeln(s[n]);halt;end;//单判大于等于n的情况
  for i:=1 to n do
   for j:=a[i-1] to a[i]-1 do
    sum[j]:=s[i-1];//跑一遍，都赋好值
  writeln(sum[q]);//输出
 end.
```
结束了！！！

---

## 作者：Core (赞：4)

大意：就是给定修改校名的次数即每次修改的名称，然后让你找第X年时校名是啥。

其实这道题没啥好说的，主要就是分类讨论：

（1）若给定想查询的年数小于第一次修改校名的时间，那么直接输出“kogakubu10gokan”。

（2）若给定想查询的年数在修改校名之中，那么输出修改后的校名。

（3）若给定想查询的年数大于最后一次修改校名的时间，那么直接输出最后一次修改的校名。

Code当中说：

```
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct schoolname
{
	int year;
	string name;
}Schoolname[55];     //定义结构体，储存修改的年份及修改的校名
int main()
{
	int n,p;
	cin>>n>>p;       //n次修改，求p年时的校名
	for(int i=1;i<=n;i++) cin>>Schoolname[i].year>>Schoolname[i].name;   //输入修改的年份及修改的校名
	if(p<Schoolname[1].year)
	{
		cout<<"kogakubu10gokan"<<endl;
		return 0;
	}           //若给定想查询的年数小于第一次修改校名的时间，那么直接输出“kogakubu10gokan”
	for(int i=1;i<n;i++)
	{
		if(Schoolname[i].year<=p&&Schoolname[i+1].year>p)
		{
			cout<<Schoolname[i].name<<endl;
			return 0;
		}
	}        //从1到n-1判断如果p在两次中间就输出
	if(Schoolname[n].year<=p)
	{
		cout<<Schoolname[n].name<<endl;
		return 0;
	}       //若给定想查询的年数大于最后一次修改校名的时间，那么直接输出最后一次修改的校名。
	return 0;     //程序结束
}
```

---

## 作者：StObOtZ (赞：1)

## AT643题解

看不懂题意的戳这[原题](https://atcoder.jp/contests/kupc2013/tasks/kupc2013_a)

#### 思路：

暴力，枚举查询的时间的区间，并输出该区间所对应的名字。

还有就是要特判查询时间在第一次修改前和最后一次修改后。如果是第一次修改前的话就输出`kogakubu10gokan`，
如果在最后一次修改后就输出 $a_n$。（$a_n$ 为最后一次修改的名字）。

# AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,y,a[105];
string b[105];
inline int read(){
	int x=0,m=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') m=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}

signed main(){
	n=read(),y=read();
	for (int i=1;i<=n;i++)	a[i]=read(),cin>>b[i];
	if (y<a[1])	puts("kogakubu10gokan");
	else 
		if (y>=a[n])	cout<<b[n]<<endl;
	else 
	for (int i=1;i<n;i++) 
		if (y>=a[i]&&y<a[i+1])	cout<<b[i]<<endl;
}
```


---

## 作者：大头leo (赞：0)

首先拿到这题，因为输入输出格式啥也没有，大家一般还是很蒙的，我先将题意大概整理一下

### 题意：
有一个宿舍，一开始它就有一个名字，叫 _kogakubu10gokan_ 但是这个宿舍喜欢改名字，一共改了 _n_ 次，题目会给你每次改的年份及改成的名字，让你编程查找第 _y_ 年此宿舍是什么名字。

### 思路:
首先，这题应该需要一个结构体来存放每次改名字的年份及新名字。

那么，怎么判断在第y年此宿舍是什么名字呢？

我们设每次更改名字时都是一个更改点，只需要找出以第y年往前数的第一个更改点的名字就是第y年此宿舍的名字了（当然会有特殊情况，我将在注意点上详细讲）。

也就是说，一般情况下，我们从头开始查找，一旦发现有一个更改点的年份超过了y，那么上一个更改点所更改的名字就是第y年的名字了。

### 注意点：
- 如果y小于第一次更改点的时间，那么第y年的名字就是初始名字：_kogakubu10gokan_。、

- 如果y大于或等于最后一次更改点以我们的思路是判断不出来的，所以特判一下，第y年的名字也就是最后一个更改点的名字。

- at的题都需要加换行，否则会爆零。

### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,y; 
struct sushe		//结构体 
{
	string name;
	int year;
}c[10001];
int main()
{
	cin>>n>>y;
	for(int i=1;i<=n;i++)
		cin>>c[i].year>>c[i].name;
	if(y<c[1].year){	cout<<"kogakubu10gokan"<<endl;	return 0;}	//注意点1特判 
	if(y>=c[n].year){	cout<<c[n].name<<endl;	return 0;}			//注意点2特判 
	for(int i=1;i<=n;i++)
	{
		if(c[i].year>y)		//如果找出大于y的年份 
		{	
			cout<<c[i-1].name<<endl;		//输出上一个更改点的名字。 
			return 0;						//return 0一定要有否则会重复判断 
		}
	}
}

```


---

## 作者：lzxhdxx (赞：0)

### 题解AT643 旧総合研究７号館

### 思路
定义有两个成员tim和name的结构体school，输入（以下均为从school[1]开始读入），然后分成以下三个步骤

（1）如果school[1]>Y大，输出“kogakubu10gokan”

（2）否则循环找到第一个比Y大的年份，输出他的前一个年份修改成的名字

（3）如果在步骤（2）中没有找到，输出school[N].name

我们会发现，“kogakubu10gokan”是初始名字，其实就是第0年改的名字，我们就把结构体中的字符串都初始化为“kogakubu10gokan”，如果school[1]>Y，就输出school[0].name，即为我们初始化的“kogakubu10gokan”

这样，我们就成功地把一，二步合并了

整理后的思路如下~~其实就是刚才的二三步~~：

（1）循环找到第一个比Y大的年份，输出他的前一个年份修改成的名字

（2）如果在步骤（2）中没有找到，输出school[N].name

根据思路得出代码：

```cpp
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

struct School
{
	char name[110] = "kogakubu10gokan";//全都初始化成初始名字
	int tim;//时间
	bool operator<(const School& sch)const//重载运算符，升序排序用
	{
		return tim < sch.tim;
	}
}school[100010];

int N, Y;

int main()
{
	scanf("%d%d", &N, &Y);//依次输入改名次数，要求查找的年份
	for (int i = 1; i <= N; i++)//依次输入N个时间和修改的名字
		scanf("%d%s", &school[i].tim, school[i].name);
	sort(school + 1, school + N + 1);//排序（之前的大佬没用排序，但题面貌似没说按顺序给出数据，于是我就排了一遍序）
	for (int i = 1; i <= N; i++)
		if (school[i].tim > Y)//找到第一个比Y大的
		{
			printf("%s\n", school[i - 1].name);//输出他前一次修改修改成的名字
			return 0;//找到就直接结束
		}
	printf("%s\n", school[N].name);//如果一直没结束，那就直接输出最后一个
	return 0;
}
```
感谢各位阅读！！求管理大大给过吧

---

## 作者：cjZYZtcl (赞：0)

## ~~水题~~
模拟，判断查询的年份在哪个区间内，然后输出所在区间对应的名字即可。

可以单判一下在第一段区间之前和改了 $n$ 次名字之后的情况。
## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[10005];
string b[10005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), y = read();
	char ch;
	for(int i = 1; i <= n; i++){
		a[i] = read();
		cin>>b[i];
	}
	if(y < a[1]){
		puts("kogakubu10gokan");
		return 0;
	}
	if(y >= a[n]){
		cout<<b[n]<<endl;
		return 0;
	}
	for(int i = 1; i < n; i++){
		if(y >= a[i] && y < a[i + 1]){
			cout<<b[i]<<endl;
			return 0;
		}
	}
}
```


---

## 作者：CrTsIr400 (赞：0)

这是一道二分查找都不用的入门题。

简单来说，要查询第 $y$ 年，可以分 $3$ 种情况而定：

+ $y< year_1$ 。这种情况之下，直接输出 $\texttt{kogakubu10gokan}$ 即可。

+ $y>year_n$ 。直接输出最后一个名字即可。

+ $y\ge year_i $ 并且 $y< year_{i+1}  (1\le i<n)$ 。这样的话输出第 $i$ 个名字即可。

然后就是比较容易实现的程序。

```cpp

#include<bits/stdc++.h>
using namespace std;
int N,Q;
int ChangeYear,NextYear;
char ChangeName[30];
int main()
{
	scanf("%d %d ",&N,&Q);
	scanf("%d %s",&ChangeYear,ChangeName);
	if(ChangeYear>Q)return printf("kogakubu10gokan\n"),0;
	for(int i=2;i<=N;++i)
	{
		scanf("%d ",&NextYear);
		if(ChangeYear<=Q&&Q<NextYear)return puts(ChangeName),0;
		scanf("%s",ChangeName);
		ChangeYear=NextYear;
	}
	return puts(ChangeName),0;
}
//BY SegmentTreeJuruo

```

---

