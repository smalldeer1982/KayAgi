# Magnets

## 题目描述

Mad scientist Mike entertains himself by arranging rows of dominoes. He doesn't need dominoes, though: he uses rectangular magnets instead. Each magnet has two poles, positive (a "plus") and negative (a "minus"). If two magnets are put together at a close distance, then the like poles will repel each other and the opposite poles will attract each other.

Mike starts by laying one magnet horizontally on the table. During each following step Mike adds one more magnet horizontally to the right end of the row. Depending on how Mike puts the magnet on the table, it is either attracted to the previous one (forming a group of multiple magnets linked together) or repelled by it (then Mike lays this magnet at some distance to the right from the previous one). We assume that a sole magnet not linked to others forms a group of its own.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344A/5ad7b55de90b4c95ae686ce6e02cbb9c5dff4d4e.png)Mike arranged multiple magnets in a row. Determine the number of groups that the magnets formed.

## 说明/提示

The first testcase corresponds to the figure. The testcase has three groups consisting of three, one and two magnets.

The second testcase has two groups, each consisting of two magnets.

## 样例 #1

### 输入

```
6
10
10
10
01
10
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
01
01
10
10
```

### 输出

```
2
```

# 题解

## 作者：Eric周 (赞：2)

###### 蒟蒻的我用了string，不知道占不占内存
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(O2)
#pragma GCC optimize(2)
#pragma GCC optimize(3)//防止卡常手动开了O2
#define h 100005
using namespace std;
string a[h];int j;
int main()
{
	cin>>j;int cnt;cnt=0;
	for(int u=1;u<=j;u++)
		cin>>a[u];
	for(int u=1;u<j;u++)
		if(a[u][1]==a[u+1][0]) cnt++;
	cnt++;
	cout<<cnt;
	return 0;
}
//话说我的代码有些丑陋，占了这么多内存
```

~~大佬说还能用链表？~~

---

## 作者：ACE_ZY (赞：2)

这题其实十分简单

看样例:
6

10

10

10 

01  这里s+1

10  这里s+1

10

最后是1个,也要加1

输出是3

因此,可以得出结论:如果和前面一个不一样,就累加,由于最后单独为1节,所以直接加1

代码(pascal):
```pascal
var
  s,n,i,y,x:longint;
begin
  readln(n);
  readln(x);//读入第一个数
  for i:=2 to n do//单层循环即可
  begin
    readln(y);//分别读入剩下的
    if x<>y then inc(s);//如果不相等,就加1
    x:=y;//这里值得注意,这次输入的数要成为与下一个数比的数
  end;
  writeln(s+1);//最后加1
end.
```

望通过,谢谢了!!!

---

## 作者：judgejudge (赞：2)

# 利用规律！！


------------

首先根据**同性相斥，异性相吸**的法则，我们可以知道只有相同的才会连在一起。

但是我们换一种思路：我们**假设一开始全部相同**，令总数初始值为1，**我们查找不同的，一旦查到总数++**

那么查找不同的方法就是：**判断两个数相加是否等于11！！！**

AC代码就出来了：
```cpp
#include <iostream>
using namespace std;
int a[100001];//因为1<=n<=100000，所以数组得定大点
int main(){
	int i,j,k,n;
	int ans=1;//假设一开始全部相同，令总量为1
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<n;i++)
	if(a[i]+a[i+1]==11)ans++;//一旦发现相加为11，说明不相同，总量++
	cout<<ans;//输出总量
	return 0;
}
```

---

## 作者：一滴小水滴 (赞：0)

这道题还是挺简单的，但是由于有可能输入01，我就把输入改成了char字符串。

我们先定义一个字符x，用来记录字符串的第一个字符，以来判断新输入的字符串是不是不同的。所以我们先输入一次，第一次更改x的值。
```cpp
gets(c);
if(c[0]=='1')x='1';
else x='0';
```
然后再输入剩下的n-1个字符串，并不断更新x和答案ans的值。
```cpp
for(int i=1;i<n;i++)
{
	gets(c);
	if(c[0]!=x)
	{
		ans++;
		if(c[0]=='0')x='0';
		else x='1';
	}   //如果第一个字符和x不相同，说明这是同级，ans++，并更改x的值。
}
```

最后就只需要输出ans就行了，附上AC代码。
```cpp
#include<bits/stdc++.h>  //万能脑袋不说了，不想打辣么多头文件。
using namespace std;
int main()
{
	int n,ans=1;
	char x,c[5];
	cin>>n;
	cin.get();   //一定要记得要加cin.get()，
         	     //不然会把输入n后的换行认为一个字符串，
                     //所以一定要把它加上。
	gets(c);
	if(c[0]=='1')x='1';
	else x='0';
	for(int i=1;i<n;i++)
	{
		gets(c);
		if(c[0]!=x)
		{
			ans++;
			if(c[0]=='0')x='0';
			else x='1';
		}
	}
	cout<<ans<<endl;
	return 0;  //程序完美结束。
}
```

### 这篇题解就结束了，大家一定要注意cin.get()这个细节鸭。

---

## 作者：Jinyeke (赞：0)

#### 题目：有n个条形磁铁排列再桌子上，它们跟普通的磁铁一样，都是同极相斥，异极相吸。现在给定了它们的两极，连续两个磁铁如果方向一致那就会吸引，合并成一条更长的磁铁。现在请问桌上会有几个分开的磁铁？
### 我们可以先把磁铁看成两个部分
### 第一部分和第二部分
### 第一部分用来和前面的比较
### 第二部分用来和后面的比较
### 假设一块磁铁是01
### 那么它的第一部分是0
### 它的第二部分是1
### 大概思路：先全部输入，输完后s先赋值为1，因为至少有1段，再从第i（i初始为2）个磁铁开始判断，如果第i个磁铁的第一部分和第i-1块相同，块数（s）+1。
#### 这句话是核心代码：
### 由于我（作者）输入的是一个整数，所以第一部分就是 div 10（整除10）得到的，第二部分就是 mod 10（求余）得到的。
```pascal
if a[i-1] mod 10=a[i] div 10 then inc(s);

补充一下小细节就是一篇满分代码拉啦
var
 n,i,s:longint;
 a:array[1..100001] of longint;//注意数据大小
begin
 readln(n);
 for i:=1 to n do readln(a[i]);//输入
 s:=1; //初值不能忘
 for i:=2 to n do 
   if a[i-1] mod 10=a[i] div 10 then inc(s);//核心代码，上面有解释
 write(s);//输出最后的块数
end.
     
```
第一次写这么详细，求过



---

## 作者：return先生 (赞：0)

这题很好（shui），看了一下下面大佬的题解结果看不懂……我用的是模拟，~~真的很好用~~

这是代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
	char a,b,jl;//a和b是输入，jl用于记录上一个磁铁的尾巴。
	int n,ans=1;//n是个数，ans一开始不能设定为0，因为一开始就有磁铁了，也就是至少有一个磁铁。
	cin>>n;//输入
	for(int i=1;i<=n;i++)//循环n次
	{
		cin>>a>>b;//a和b用于记录输入的两个内容。
		if(i==1)//如果他是第一个被输入的磁铁号码，那么久将它jl直接设定为它的尾巴b。
		{
			jl==b;
		}
		else//否则的话……
		if(a==jl)//如果a是上一个记录的话，那么……
		{
			ans++;//数量++
		}
		jl=b;//将b设为他的尾巴。
	}
	cout<<ans;//最后，输出ans。
	return 0;//华丽丽（并不）的结束……
}
```

---

## 作者：Victory_Defeat (赞：0)

这是一道水题，直接统计有**多少组相同的磁铁**即可（注：输入时01会变成1，但并不影响结果）

直接上代码：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
typedef double lf;
typedef unsigned un;
typedef int in;
#define mian main
#define _(a) read(a)
#define non void
#define inf 2147483647
#define bre break
#define con continue
#define prq priority_queue
#define re register
#define bu bool
#define cz char
#define cst const
#define ope operator
#define inl inline
#define upp upper_bound
#define low lower_bound
#define next_pre next_premutation
template<typename T>inl T Max(T a,T b){return a>b?a:b;}
template<typename T>inl T Min(T a,T b){return a<b?a:b;}
template<typename T>inl T Abs(T a){return a<0?-a:a;}
template<typename T>inl non read(T &a){a=0;T k=1;char c=getchar();while(c<'0'||c>'9')k=c=='-'?-1:k,c=getchar();while(c>='0'&&c<='9')a=a*10+(c^48),c=getchar();a*=k;}
template<typename T>non write(T a,cz t=' '){if(a==0){putchar(48),putchar(t);return;}if(a<0){a=-a;putchar('-');}cz c[30];in le=0;while(a){c[++le]=a%10+48;a/=10;}for(re in i=le;i>=1;--i)putchar(c[i]);putchar(t);}
//上面的不用管
in n,a,now,ans=1,sum;
in main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
    //输入
	for(re in i=1;i<=n;++i)
	{
		read(a);
		if(now==0)now=a;
		if(now!=a)now=a,++ans;
	}
    //边读边做，直接统计即可
	write(ans);
    //输出
}
```

---

