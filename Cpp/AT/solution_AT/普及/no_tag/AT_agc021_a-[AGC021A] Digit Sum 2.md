# [AGC021A] Digit Sum 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc021/tasks/agc021_a

$ N $ 以下の正の整数の $ 10 $ 進法での各桁の和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 10^{16} $
- $ N $ は整数である

### Sample Explanation 1

例えば $ 99 $ の各桁の和は $ 18 $ で、これが求める最大値となります。

### Sample Explanation 2

例えば $ 9989 $ の各桁の和は $ 35 $ で、これが求める最大値となります。

## 样例 #1

### 输入

```
100```

### 输出

```
18```

## 样例 #2

### 输入

```
9995```

### 输出

```
35```

## 样例 #3

### 输入

```
3141592653589793```

### 输出

```
137```

# 题解

## 作者：zjyqwq (赞：5)

### 我也来发题解了！


------------
#### 为甚发题解

看了AKIOI的ZYZ巨佬发的题解，表示太菜了康不懂，做完后准备发一篇详细的。

-----------
#### 题意
给你一个数 $n$ ,求 $1$~$n$ 中各个数位之和的最大值。

这不暴力就行了吗？

于是，我打了这个代码。


------------
#### 代码
```Pascal
var
n,i,x,max,j:longint;
s:string;//定义
 begin
  readln(n);
  for i:=1 to n do//一一枚举
   begin
    str(i,s);
    for j:=1 to length(s) do//计算
     x:=x+ord(s[j])-48;
    if x>max then max:=x;//比较
   end;
  write(max);
 end.
```
------------
但是，远远还没有结束。

可以发现，这个代码会超时, $n$ 太大了。

我们要换思路。

------------
#### 正解

Q: 一个数怎么才能最大？

A: 全都是 $9$ 不就行了？

所以，现在我们要总结一下。

最大情况便是 $n$ 的长度减一个九再加上 $n$ 第一位减一，因为这样才能保证这个数比 $n$ 小。

但是，我们再单判一下 $n$ ，防止出些什么奇奇怪怪的错误。


------------
#### 100代码
```pascal
var
s:string;
i,x1,x2:longint;
function max(x,y:longint):longint;//手写max函数
begin
 if x>y then exit(x);
 exit(y);
end;
 begin
  readln(s);
  for i:=1 to length(s) do x1:=x1+ord(s[i])-48;//单判N的情况
  x2:=ord(s[1])-48-1+(length(s)-1)*9;//判断正常情况
  writeln(max(x1,x2));//输出大的
 end.
```
结束喽！！！

---

## 作者：lsw1 (赞：3)

要想让数字和最大，那么要么是这个数本身，要么是首位减一，其他位取到 $9$ 。

注意“这个数本身”这种情况不能忽略，否则：

hack input:
```cpp
9999
```
wrong output:
```cpp
35（8999）
```
right output:
```cpp
36（9999）
```
- - -
```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int sum = 0;//第一种情况
	for(int i = 0;i < s.size();i++)
	{
		sum += s[i] - '0';
	}
	cout << max(sum,s[0] - '0' - 1 /*首位-1*/ + ((int)s.size() - 1) * 9/*其余全部取9*/);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

读者可以想到，无论如何，所求之数的位数最大值是一定的，必然除了首位外其他全部填 $9$ 最好，但是其他未取到 $9$ 了，首位大概率取不到 $9$ ，除了像 $99\dots99$ 这样的数，我们需要进行特判。

## _Code_
```cpp
#include<iostream>
using namespace std;
const int MAXN=5e5+5;
char a;
int ans1=0,ans2=0;
int main(){
	cin>>a;
	ans1=a-'0'-1;
	ans2=a-'0';
	while(cin>>a){
		ans1+=9;
		ans2+=a-'0';
	}
	cout<<max(ans1,ans2);
}

```


---

## 作者：BotDand (赞：1)

# $\text{Problems}$
给出 $n$，求小于等于 $n$ 的正整数中用十进制表示各数位数字之和的最大值。
# $\text{Answer}$
分两种情况讨论。

1. $\text{ans=n}$
2. $\text{ans<n}$

第一种情况时，即原数各数位数字之和。

第二种情况时，最高位减 $1$，其余位都为 $9$，不难证明此情况最优。
# $\text{Code}$
代码真的很短
```cpp
#include<bits/stdc++.h>
using namespace std;
__int128 n,m;
__int128 a[22];
inline __int128 read()
{
    __int128 s=0;
    int w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(__int128 x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(__int128 x)
{
    write(x);
    putchar('\n');
}
inline int Max(__int128 a,__int128 b)
{
    if(a>b) return a;
    return b;
}
inline void fen()
{
    while(n)
    {
        m++;
        a[m]=n%10;
        n/=10;
    }
    reverse(a+1,a+m+1);
}
__int128 sum1()
{
    __int128 s=0;
    for(int i=1;i<=m;++i) s+=a[i];
    return s;
}
__int128 sum2()
{
    return a[1]+9*m-10;
}
void input()
{
    n=read();
}
void work()
{
    fen();
}
void output()
{
    write(Max(sum1(),sum2()));
}
int main()
{
    input();
    work();
    output();
    return 0;
}
```

---

## 作者：gi_A (赞：0)

对于一个 $x$ 位数，使其各位数字和最大的一定是 $x$ 个 $9$。

但是这不一定满足 $\le n$ 的限制。然后我们就可以发现，$x-1$ 个 $9$ 一定能够满足，比如：$n$ 的最高位减 $1$，其余为 $9$。

对于一般情况而言，该数是唯一小于等于 $n$ 且有 $x-1$ 个 $9$ 的数。

其他情况：$n$ 本身包含 $x-1$ 个 $9$。

核心代码：

```cpp
long long n;
int x,a[20],ans;
int main()
{
	cin>>n;
	while(n){a[++x]=n%10;n/=10;}
	ans=(x-1)*9;ans+=a[x]-1;
	int s=0;
	for(int i=1;i<=x;i++)s+=a[i];
	ans=max(ans,s);
	cout<<ans;
	return 0;
}
```


---

## 作者：cjZYZtcl (赞：0)

## 来一篇Pascal题解！
这其实是一道数学题

分两种情况：

1. 输入的数的所有数位的和
2. 第一位是输入的数的第一位减一，其他数位都为9，求出数位和。

求出两种情况的最大值即可。

注意：AT输出要换行！！！

### Code：
```pascal
uses math;
var
  s:string;
  x,y:int64;
  i:longint;
begin
  read(s);
  x:=ord(s[1])-49+(length(s)-1)*9;
  for i:=1 to length(s) do y:=y+ord(s[i])-48;
  write(max(x,y));
end.
```


---

## 作者：Doqin07 (赞：0)

### 分两种情况讨论
- 要么是这个数本身，要么把$n$的第一位$-1$其余为9
- 最后取$max$即可
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int max1=0,max2=0;
	for(int i=0;i<s.length();++i){
		if(i==0)max1+=(s[i]-'0'-1);
		else max1+=9;
		max2+=(s[i]-'0');
	}
	printf("%d\n",max(max1,max2));
	return 0;
}
```


---

## 作者：happybob (赞：0)

本题还是很简单的，主要是找到思路

其实只要先把n的位数加起来，然后再把n的第一位减去1的结果加到另外一个变量中，其余为数都为9

输出最大值OK

```cpp
#include <iostream>
#include <cstring>
using namespace std;

#define max(a, b) (a > b ? a : b)//宏定义

string s;

int main()
{
    cin >> s;
    int len = s.length() - 1, x, y;
    x = y = 0;
    for(int i = 0; i <= len; i++)
    {
        if(i == 0)
        {
            x += s[i] - '0' - 1;
        }
        else
        {
            x += 9;
        }
        y += s[i] - '0';
    }
    cout << max(x, y) << endl;
    return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

**[题解 AT3867 【[AGC021A] Digit Sum 2】](https://www.luogu.com.cn/problem/AT3867)**  
由于 AtCoder 的端口 SPFA 了，所以本题解的代码是直接在原 OJ 上提交的，AC记录如下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/8oxtz6v9.png)  
# Solution  
这道题目第一眼觉得是 $\Theta(N)$ 的爆搜，然后一看数据范围……  
于是开始想数学方法。  
我们可以发现，对于任意的一个数 $n$ ，只有两个数可能成为我们想要的答案，第一个是 $n$ 自己，第二个是形如 $a999999\dots999$ 的形式，所以我们把这两个数字的各数位数字之和算出来，比较即可。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int ans1,ans2;	//ans1表示n自己，ans2表示第二种情况

string S;

int main() {
	cin >> S;
	int len = S.size();
	for(int i = 0;i < len;i++) {
		ans1 += S[i] - '0';
		if(i == 0) {	//首位需要少一，不然就比n大了
			ans2 += (S[i] - '0' - 1);
			continue;
		}
		ans2 += 9;	//其他位都是9
	}
	printf("%d\n",max(ans1,ans2));
	return 0;
}
```

---

## 作者：C20210404杜铖昊 (赞：0)

这道题记住要换行

用string类型输入，答案加上（加上string字符串长度减1） * 9，

记住特判（1）：
 
 如果string字符串所有字符都为9

答案再加上一个9就可以了

记住特判（2）：
 如果只有一个字符
 
 直接输出就可以了
 
如果不是特判（1）：

加上第一个字符减‘0’在减1就可以了

如果不是特判（2）：

直接照着前面方法做就可以了

code如下：（~~有一些瑕疵~~）

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
string num;
long long ans;
int main(){
    cin>>num;
    long long sum = num.length()-1,sum1 = num[0] - '0';
    sum1--;
    if(sum == 0){//特判(2) 
    	cout<<num<<endl;
    	return 0;
    }
    ans += sum*9;//答案加上长度减1 再乘9 
    //cout<<ans<<endl;
    int k = 0;
    for(int i = 0;i <num.length();++i){//特判(1) 
    	if(num[i] == '9') k++;
    }
    if(k == num.length()) sum1++;//第一个字符就不用减1了 
    ans += sum1;//加上第一个字符合法的最大值 
    cout<<ans<<endl;//输出 
    return 0;
}
```


---

## 作者：修罗海神王 (赞：0)

###### ~~这道题好像并不很难，弱弱地问一句：“为什么这么少的人做对啊？？？（不吭声了……）”~~


#### 我好像是做出来这道题并且（没有看）~~看了~~题解的，~~真的~~（详见代码）



------一条看似简单却又确实简单的分割线，咳咳，上课啦，敲黑板！------

# 正题（~~废话好多~~）：


    让我们在一段话中一口气一口气说完
    ：“首先输入s，用l存储s的长度，
    然后0--（l-1）去枚举字符串的每一位，
    sum1去算出每一位的总和，
    然后如果这一位是第一位并且这一位=‘1’，
    意味着就是第一个样例的存在：100，
    最大为9+9=18，所以就可以跳过这一位，
    否则，如果他依旧是第一位，sum2加第一位（变为数字）-1，
    并跳过……
    最后所有的位sum2都可以加9，
    最后（两个了），输出sum1和sum2两个里面最大的一个，
    完成啦！！！！！！！……”
    
## A:代码献上：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,sum,sum1;
string s;
int main()
{
	cin>>s;
	l=s.size();
	for(int i=0;i<l;i++)
	{
		sum1+=s[i]-'0';
		if(s[i]=='1'&&i==0) continue;
		  else if(i==0) {sum+=(s[i]-'0'-1);continue;}
		sum2+=9;
	}
	cout<<max(sum1,sum2)<<"\n";
	return 0;
 } 
```

# ヾ(￣▽￣)Bye~Bye~




---

