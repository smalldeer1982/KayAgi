# BareLee

## 题目描述

（以下内容并非逐字翻译，但并不影响做题）

Lee 习惯于用一种新奇的方式结束他的故事，比如和 Ice Bear 玩一个叫做 Critic 的游戏。

游戏规则是这样的：这是一个 1V1 的游戏，有且仅有 $t$ 轮。对于每一轮，有且仅有两个双方均已知的，不会更改的整数 $s_i$ , $e_i$ 。其中 $s_i$ 被写在了黑板上。

现在，两名玩家同时上场，有两种操作，他/它只能并且必须选择一种操作：

* 将黑板上的数 $a$ 改写为 $a+1$

* 将黑板上的数 $a$ 改写为 $2 \times a$

最终，写上的 $a$ 大于这一轮的 $e_i$ 的人输掉该轮比赛。每一轮的失败者就是下一轮的起始者（首先上去写数的人）。整场比赛的输赢取决于最后一轮的输赢。

求出，如果 Lee 是第一轮比赛的起始者，他是否有必赢，必输策略。

## 样例 #1

### 输入

```
3
5 8
1 4
3 10```

### 输出

```
1 1```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
4 5```

### 输出

```
0 0```

## 样例 #3

### 输入

```
1
1 1```

### 输出

```
0 1```

## 样例 #4

### 输入

```
2
1 9
4 5```

### 输出

```
0 0```

## 样例 #5

### 输入

```
2
1 2
2 8```

### 输出

```
1 0```

## 样例 #6

### 输入

```
6
216986951114298167 235031205335543871
148302405431848579 455670351549314242
506251128322958430 575521452907339082
1 768614336404564650
189336074809158272 622104412002885672
588320087414024192 662540324268197150```

### 输出

```
1 0```

# 题解

## 作者：Para (赞：6)

## 思路

总共有 $T$ 轮游戏，每一轮的先手为上一轮的失败者，非常明显的导向 dp。

定义 $f_{i,0/1}$ 表示第 $i$ 轮的先手在最后是否有必败/必胜方案。转移的时候考虑先手在本轮是否有必败/必胜态，推出第 $i + 1$ 轮的先手是谁，逆序 dp 即可。

难点在于如何求解一轮中先手是否有必败/必胜态。设起始数字为 $s$，上届为 $t$。不妨先分情况考虑是否有必胜态。
- $t$ 为奇数。由于对于一个奇数 $x$ 而言，无论进行何种操作都只能将其变为偶数，所以拿到偶数的一方只需要将当前数加一，就一定必胜。$s$ 为偶数必胜，反之必败。

- $t$ 为偶数。我们逆向的来考虑这个问题。对于 $s \in (t / 2, t]$ ，$s$ 为偶数必败。所以在 $s \in (t/4, t/2]$ 进行一次 $\times 2$ 操作就会必胜。对于 $s \le t/4$，其实是谁先跨过 $t / 4$ 谁失败，即转换为一个 $(s, t / 4)$ 的子问题。

对于先手是否有必败态，可以转换为求解是否有 $(s, t / 2)$ 的必胜态，因为一旦一方跨过了 $t/2$，另一方进行 $\times 2$ 操作必败。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define inf 1e9
#define pii pair <int, int>
const int mod = 1e9 + 7;
int read () {
	int x = 0, f = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar ();
	}
	return x * f;
}
void write (int x) {
	if (x < 0) x = -x, putchar ('-');
	if (x >= 10) write (x / 10);
	putchar (x % 10 + '0');
}
int ch(int s, int t) {
    if (s > t) return 1;
    if (s == t) return 0;
    if (t & 1) return !(s & 1);
    if (s * 2 > t) return s & 1;
    if (s * 4 > t) return 1;
    return ch(s, t >> 2);
}
pii get_ans(int s, int t) {
    return mp(ch(s, t), ch(s, t >> 1));
} 
pii a[100005];
int b[100005][2];
signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    int n = read();
    for (int i = 1; i <= n; i++) {
        int s = read(), t = read();
        a[i] = get_ans(s, t);
    }
    b[n][0] = a[n].second, b[n][1] = a[n].first;
    for (int i = n - 1; i >= 1; i--) {
        b[i][1] = ((a[i].second && b[i+1][1]) | (a[i].first && !b[i+1][1]));
        b[i][0] = ((a[i].second && b[i+1][0]) | (a[i].first && !b[i+1][0]));
    }
    write(b[1][1]), putchar(' '), write(b[1][0]), putchar('\n');
	return 0;
}
/*
*/
```

---

## 作者：dead_X (赞：4)

## 前言
2700（迫真）

紫（确信）
## 题意
一个数 $x$，两个人轮流 $\times 2$ 或者 $+1$，让这个数 $>y$ 的人输。

有若干局这种游戏，每局的败者在下局先手，问先手是否有必胜和必败策略。
## 简单的转化
对于第 $i$ 局游戏，我们可以设 $f_{i,FW},f_{i,FL},f_{i,SW},f_{i,SL}$ 为该局游戏先手是否可以必胜，先手是否可以必败，后手是否可以必胜，后手是否可以必败。

显然在求出 $f$ 数组后，我们可以轻松求出答案。
## 思考过程：找部分情况的结论
这个其实挺重要的，虽然这题没啥用，但是还是建议大家看一下（

首先我们尝试对于部分情况搞一个结论。

我们发现如果一个人手里拿着一个偶数，并且 $y$ 是奇数，则他可以一直把 $y$ 弄成奇数然后让对手自生自灭。

然后就不会了…
## 打表技巧
在维数比较低的博弈问题上，我们往往可以打表找规律。

这题同样感觉比较晕，我们打个表，对于一个 $y$ 求出每个 $x$ 的状态。

显然我们可以得到一个复杂度和值域有关的暴力：设 $g(x)$ 为 $(x,y)$ 时先手是否能胜利，我们有

$$g(x)=
\begin{cases}
1& x>y\\
0& x=y\\
(g(x+1)\&g(2x))\oplus 1& x<y\end{cases}$$

以下是 $n=20,22,24$ 时的答案，第 $i$ 位为 $1$ 代表先手在 $x=i,y=n$ 时有必胜策略。 

```
01010111111010101010
0101011111101010101010
011010111111101010101010
```

注意到我们的状态是从后往前推的，我们不妨也把这个东西倒过来看。

```
01010101011111101010
0101010101011111101010
010101010101111111010110
```

我们发现，它的大致规律为 $01$ 和 $1$ 交替出现，我们尝试从 $n=20$ 入手分析它的规律。

考虑第一段 $01$，出现在 $[11,20]$ 之间，它只有一个选择，就是 $+1$。

然后在 $i=[6,10]$ 的时候，$\times 2$ 显然都在 $[11,20]$ 之间，于是它们的两个选择也可以快速计算。

然后在 $i=[3,5]$ 的时候，$\times 2$ 显然都在 $[6,10]$ 之间，于是它们的两个选择也可以快速计算。

然后在 $i=[2,2]$ 的时候，$\times 2$ 显然都在 $[3,5]$ 之间，于是它们的两个选择也可以快速计算。

然后在 $i=[1,1]$ 的时候，$\times 2$ 显然都在 $[2,2]$ 之间，于是它们的两个选择也可以快速计算。

以此类推，我们显然可以将序列分成 $\log $ 段进行递推。

```
20           10      5     2   1
0101010101 | 11111 | 010 | 1 | 0
22            11       5     2   1
01010101010 | 111111 | 010 | 1 | 0
24             12       6     3    1
010101010101 | 111111 | 010 | 11 | 0
40                    20            10      5     2   1
0101010101010101010 | 11111111111 | 01010 | 111 | 0 | 1
50                          25              12       6     3    1
0101010101010101010101010 | 1111111111111 | 010101 | 111 | 01 | 0
```

显然对于每一段，它们 $\times 2$ 的决策结果都是相同的，因此可能的结果只有 $0101\cdots$，$1010\cdots$ 和 $1111\cdots$。

对于必败态，我们显然也可以如法炮制，这里不再赘述。

对于后手的状态，枚举先手的两种选择即可。
## 坑点
千万不要把判断胜利和失败的函数写在一起！！！

注意可以直接将当前的数搞成不合法状态来让自己失败。

注意 dp 转移的一些小细节，最好别像我一样不写数组写单个变量，调试起来很痛苦。

注意分段函数的端点和转移的小细节。
## 代码
挺丑的。


```cpp
// Problem: F. BareLee
// Contest: Codeforces - Codeforces Round #652 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1369/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//愿神 zhoukangyang 指引我。
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int a[100003],b[100003];
bool Getwin(int x,int y)
//MatrixCascade win win
{
	if(x>y) return 1;
	if(y&1) return (x&1)^1;
	if(x==y) return 0;
	int g=y>>1,l=g+1,r=y,type=0;
	//type 0 代表 0101
	//type 1 代表 1010
	//type 2 代表 1111
	if(x>=l) return ((r-x)&1)^type;
	while(1)
	{
		int tg=g>>1,tl=tg+1,tr=g,tt;
		if(type==2) tt=0;
		else if(((r-tr*2)&1)^type) 
			tt=(((r-tr)&1)^type);
		else tt=2;
		g=tg,l=tl,r=tr,type=tt;
		if(x>=l) 
		if(type!=2) return ((r-x)&1)^type;
		else return 1;
	}
}
bool Getlose(int x,int y)
//dead_X lose lose
{
	if(x>y) return 0;
	if(x==y) return 1;
	int g=y>>1,l=g+1,r=y,type=2;
	//type 0 代表 0101
	//type 1 代表 1010
	//type 2 代表 1111
	if(x>=l) return 1;
	while(1)
	{
		int tg=g>>1,tl=tg+1,tr=g,tt;
		if(type==2) tt=0;
		else if(((r-tr*2)&1)^type) 
			tt=(((r-tr)&1)^type);
		else tt=2;
		g=tg,l=tl,r=tr,type=tt;
		// cout<<type<<endl;
		if(x>=l) 
		if(type!=2) return ((r-x)&1)^type;
		else return 1;
	}
}
signed main()
{
	int n=read();
	for(int i=1; i<=n; ++i) a[i]=read(),b[i]=read();
	bool Fwin=0,Flose=0,Swin=0,Slose=0;
	for(int i=n; i>=n; --i)
	{
		Fwin=Getwin(a[i],b[i]),Flose=Getlose(a[i],b[i]);
		Swin=Getwin(a[i]+1,b[i])&&Getwin(a[i]<<1,b[i]),
		Slose=Getlose(a[i]+1,b[i])&&Getlose(a[i]<<1,b[i]);
	}
	for(int i=n-1; i>=1; --i)
	{
		bool fwin,flose,swin,slose;
		fwin=Getwin(a[i],b[i]),flose=Getlose(a[i],b[i]);
		swin=Getwin(a[i]+1,b[i])&&Getwin(a[i]<<1,b[i]),
		slose=Getlose(a[i]+1,b[i])&&Getlose(a[i]<<1,b[i]);
		bool tfw,tfl,tsw,tsl;
		tfw=(fwin&&Swin)||(flose&&Fwin)||(Fwin&&Swin),
		tfl=(fwin&&Slose)||(flose&&Flose)||(Flose&&Slose),
		tsw=(swin&&Swin)||(slose&&Fwin)||(Fwin&&Swin),
		tsl=(swin&&Slose)||(slose&&Flose)||(Flose&&Slose),
		Fwin=tfw,Flose=tfl,Swin=tsw,Slose=tsl;
	}
	printf("%d %d\n",(signed)Fwin,(signed)Flose);
    return 0;
}
```

---

## 作者：违规用户名76G!ihcm (赞：3)

### 题意

有 $T$ 轮游戏，每轮有两个参数 $s,e\geq1$，先后手轮流操作，每次给 $s$ $+1$或$\times 2$，但是不许超过 $e$ ，不能操作的算输。每一轮游戏的输家是下一轮的先手，求第一轮的先手最后一轮有没有必胜策略，有没有必败策略。

$s,e \leq 10^{18} , T\leq 10^5$

### 题解

（dbq我可能比较菜，不太会正解，但是找规律做出来了，就说一下找规律的做法，理解正解之后再回来填坑）

(把重要结论和主要思路都标黑了（虽然可能标的不全）)

**首先如果可以算出每一轮游戏，谁有必胜策略，谁有必败策略，就可以算出最后的答案了。**

具体方法是 $dp[i][0/1]$ 表示后 $i$ 轮先后手分别有没有必胜策略，转移就是

$$dp_{i,w_i}=dp_{i+1,0}$$
$$dp_{i,l_i}=dp_{i+1,1}$$

其中 $w_i$ 和 $l_i$ 分别表示谁有必胜策略，谁有必败策略（先手是 $1$ ，后手是 $0$）。

求有没有必败策略基本和必胜策略相同，就不细说了。

**那么现在问题就变成了要快速的求每一轮游戏先手是否有必胜策略，后手有没有必胜策略。**

首先不考虑复杂度的话，有一个显然的 dp。(以必胜为例）

$dp_{i,j}$ 表示 $s=i , e=j$ 的游戏有没有必胜策略。

转移就是只有在 $dp_{i+1,j}$ 和 $dp_{i\times 2,j}$ 都是 $1$ 的时候 $dp_{i,j}$ 才是 $0$，否则就是 $1$。

~~由于这题是博弈题，所以考虑找规律~~

把所有 $dp_{i,90}$ 打出来：

```cpp
101010000001010101010100000000000000000000000101010101010101010101010101010101010101010101
```

**发现是一段 $1,0$ 交错，一段全 $0$ ，又一段 $1,0$ 交错……**

**而且除了前两段，每一段都是上一段的长度的两倍左右。**

把每个切换的点打出来：

```cpp
5,11,22,45
```

发现是 $\frac{90}{16} , \frac{90}{8} , \frac{90}{4} , \frac{90}{2}$

（如果找不出来的话多打几个就能看出来了，比如把所有 $dp_{i,1000}$ 打出来，但是比较长，就不放到题解里了。）

**假设第一段的长度是 $\frac{n}{2^x}$ ，如果知道 $x$ ，就大概可以求出整个 $dp_{i,n}$ 了**，定义 $f(n)=x$。

所以我们打出 $[1000,1030]$ 里面的所有 $f(n)$ （为了避免精度误差不好确定 $x$ ，$n$ 要大一点。我当时做的时候打到了 $2000$ ，但是放到题解里不方便，所以就放到了 $1030$）

```cpp
1000 7
1001 1
1002 7
1003 1
1004 3
1005 1
1006 3
1007 1
1008 5
1009 1
1010 5
1011 1
1012 3
1013 1
1014 3
1015 1
1016 5
1017 1
1018 5
1019 1
1020 3
1021 1
1022 3
1023 1
1024 11
1025 1
1026 11
1027 1
1028 3
1029 1
1030 3
```

发现对于所有奇数，$f(n)=1$，偶数不太好看出来，所以我们把所有偶数打出来再找找规律。

```cpp
1000 7
1002 7
1004 3
1006 3
1008 5
1010 5
1012 3
1014 3
1016 5
1018 5
1020 3
1022 3
1024 11
1026 11
1028 3
1030 3
1032 11
1034 11
1036 3
1038 3
1040 5
```

发现所有 $\% 4 =2$ 的 $f(n)=f(n-2)$，但是 $4$ 的倍数还是不太好看出来，所以再把 $4$ 的倍数都打出来：

```cpp
1000 7
1004 3
1008 5
1012 3
1016 5
1020 3
1024 11
1028 3
1032 11
1036 3
1040 5
1044 3
1048 5
1052 3
1056 11
1060 3
```

发现所有 $\% 8=4$ 的 $f(n)=3$，然后再把 $8$ 的倍数打出来：

```cpp
1000 7
1008 5
1016 5
1024 11
1032 11
1040 5
1048 5
1056 11
1064 11
1072 5
1080 5
1088 7
1096 7
```

发现所有 $\% 16=8$ 的 $f(n)=f(n-8)$。

**所以我们合理猜测：假设 $n$ 的二进制末尾 $0$ 个数为 $x$，那么：**

 $$f(n)=\begin{cases}x+1&x=1\pmod 2\\f(n-\text{lowbit}(n))&x=0\pmod 2\end{cases}$$
 
**和打表程序拍一下，发现是对的。**

求 $f(x)$ 代码：

```cpp

inline int f(int x)
{
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return f(X-(X&(-X)));
	else return ((int)1<<cnt);
}
```

（我 define int long long了，所以上面的"(int)"就是"(long long)"）

类似的，也可以求出必败策略的 $f_2(x)$ ，和 $f(x)$ 找规律方法类似，结论也类似。

 $$f_2(n)=\begin{cases}x+1&x=0\pmod 2\\f_2(n-\text{lowbit}(n))&x=1\pmod 2\end{cases}$$


代码：

```cpp

inline int f2(int x)
{
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return ((int)1<<cnt);
	else return f2(X-(X&(-X)));
}
```

然后就……死循环了（

发现比如 $x=40$，求 $f(n)$ 的时候，由于 $40$ 末尾有 $3$ 个 $0$ ，所以 $f(40)=f(40-\text{lowbit} (40))=f(32)$，又因为 $32$ 末尾有 $5$ 个 $0$，所以 $f(32)=f(32-\text{lowbit} (32))=f(0)$，然后……就死循环了。

就求不了 $f(n)=f(0)$ 的 $dp$ 值了，所以对于所有 $f(n)=f(0)$ 再单打一个表（雾）

```cpp
2 01
8 01000101
10 0100010101
32 01000101000000000101010101010101
34 0100010100000000010101010101010101
40 0100010101000000000001010101010101010101
42 010001010100000000000101010101010101010101
```

发现一开始 $10$ 交错的长度 $=0$！（其实也很好猜到，因为 $f(0)$ 可以理解为 $=INF$ ，所以一开始 $10$ 交错的长度就 $= \frac{n}{INF}=0$ 了）

就特判一下前两位，后面的就当作 $f(n)=x$ 其中 $x$ 为满足 $2^x >=\frac{n}{2}$ 的最小值就好了。（其实还是找一下规律）

**然后还要特判一下 $n=1$ 的情况**，就过了。

### 上代码（无比丑陋，注释部分是打表程序和调试信息）

```cpp
#include <iostream>
#include <cstring>
#define int long long
using namespace std;
int dp[100005][2];
inline int f2(int x)
{
	if(x==0) return -1;
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return ((int)1<<(int)cnt);
	else return f2(X-((int)1<<(int)cnt));
}
inline int cal2(int y,int x)
{
	int now=f2(x),qwq=1;
	if(x==1) return 0;
	//if(now==-1) cout << "****" << x << "****" << "\n"; 
	if(now==-1&&y==1) return 0;
	if(now==-1&&y==2) return 1;
	int t=1;
	while(x/t>2) t<<=1;
	if(f2(x)==-1) now=t;
	if(y<=x/now) return y&1;
	while(y>x/now) now>>=1,qwq^=1;
//	if(y==now) qwq^=1;
	return (y%2==0)&&qwq;
}
inline int f(int x)
{
	if(x==0) return -1;
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return f(X-((int)1<<(int)cnt));
	else return ((int)1<<(int)cnt);
}
inline int cal(int y,int x)
{
	int now=f(x),qwq=1;
	if(x==1) return 1;
	//if(now==-1) cout << "****" << x << "****" << "\n"; 
	if(now==-1&&y==1) return 0;
	if(now==-1&&y==2) return 1;
	int t=1;
	while(x/t>2) t<<=1;
	if(f(x)==-1) now=t;
	if(y<=x/now) return y&1;
	while(y>x/now) now>>=1,qwq^=1;
//	if(y==now) qwq^=1;
	return (y%2==0)&&qwq;
}
pair <int,int> a[100005],b[100005];
signed main(int argc, char** argv) {
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i].first >> a[i].second;
		b[i]={cal(a[i].first,a[i].second)^1,cal2(a[i].first,a[i].second)^1};
	//	cout << b[i].first << " " << b[i].second << "\n";
	}
	dp[n][b[n].first]=1;
	for(int i=n-1;i>=1;i--)
	{
		dp[i][b[i].first]|=dp[i+1][0];
		dp[i][b[i].second]|=dp[i+1][1];
	}
	cout << dp[1][1] << " ";
	memset(dp,0,sizeof dp);
	dp[n][b[n].second]=1;
	for(int i=n-1;i>=1;i--)
	{
		dp[i][b[i].first]|=dp[i+1][0];
		dp[i][b[i].second]|=dp[i+1][1];
	}
	cout << dp[1][1] << " ";
/*	cout << f(40) << "\n"; 
	int T;
	cin >> T;
	for(int n=1;n<=T;n++)
	{
		memset(dp,0,sizeof dp);
		for(int i=n;i>=1;i--)
		{
			if(dp[i*2]&&dp[i+1]) dp[i]=0;
			else dp[i]=1;
		}
		for(int i=n;i>=1;i--)
		{
			if(dp[i+1]==0&&dp[i+i]==0)
				dp[i]=1;
			else dp[i]=0;
		}
		int mn=1e9;
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			if(dp[i]&&i%2==1) mn=min(mn,n/i);
			if(dp[i]!=cal(i,n))
			{
				cout << i << " " << n << "\n";
				flag=1;
			//	cout << dp[i] << " " << cal2(i,n) << "\n"; 
			}
		//	if(dp[i]) cout << i << "\n";
		}
		if(flag)
		{
			for(int i=1;i<=n;i++)
				cout << dp[i];
			puts("");
			for(int i=1;i<=n;i++)
				cout << cal(i,n);
			puts("");
		}*/
	/*	int lg=0;
		while(mn) mn>>=1,++lg;
		for(int i=10;i>=0;i--)
			cout << !!(n&(1<<i));
		cout << " " << n << " " << " " << f2(n) << " "<< lg-1 << "\n";*/
	//}
	return 0;
}
```

### 无注释版代码：

```cpp
#include <iostream>
#include <cstring>
#define int long long
using namespace std;
int dp[100005][2];
inline int f2(int x)
{
	if(x==0) return -1;
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return ((int)1<<(int)cnt);
	else return f2(X-((int)1<<(int)cnt));
}
inline int cal2(int y,int x)
{
	int now=f2(x),qwq=1;
	if(x==1) return 0;
	if(now==-1&&y==1) return 0;
	if(now==-1&&y==2) return 1;
	int t=1;
	while(x/t>2) t<<=1;
	if(f2(x)==-1) now=t;
	if(y<=x/now) return y&1;
	while(y>x/now) now>>=1,qwq^=1;
	return (y%2==0)&&qwq;
}
inline int f(int x)
{
	if(x==0) return -1;
	int cnt=0,X=x;
	while(x%2==0) x>>=1,++cnt;
	if(cnt&1) return f(X-((int)1<<(int)cnt));
	else return ((int)1<<(int)cnt);
}
inline int cal(int y,int x)
{
	int now=f(x),qwq=1;
	if(x==1) return 1;
	if(now==-1&&y==1) return 0;
	if(now==-1&&y==2) return 1;
	int t=1;
	while(x/t>2) t<<=1;
	if(f(x)==-1) now=t;
	if(y<=x/now) return y&1;
	while(y>x/now) now>>=1,qwq^=1;
	return (y%2==0)&&qwq;
}
pair <int,int> a[100005],b[100005];
signed main(int argc, char** argv) {
	int n;
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i].first >> a[i].second;
		b[i]={cal(a[i].first,a[i].second)^1,cal2(a[i].first,a[i].second)^1};
	}
	dp[n][b[n].first]=1;
	for(int i=n-1;i>=1;i--)
	{
		dp[i][b[i].first]|=dp[i+1][0];
		dp[i][b[i].second]|=dp[i+1][1];
	}
	cout << dp[1][1] << " ";
	memset(dp,0,sizeof dp);
	dp[n][b[n].second]=1;
	for(int i=n-1;i>=1;i--)
	{
		dp[i][b[i].first]|=dp[i+1][0];
		dp[i][b[i].second]|=dp[i+1][1];
	}
	cout << dp[1][1];
	return 0;
}
```

~~总结及反思：~~

~~博弈题如果实在想不出来就要果断找规律~~

### 给洛谷的小建议

1. CF有很多恶意评分的题，CF上的评分相对客观，洛谷上的评分可以参考CF的难度评分。（或者AT）

2. 禁言的用户在有一定的社区贡献后可提前解除禁言（自己的题解不能评论，只能通过题解给洛谷提建议，公开赛有人作弊不能举报，甚至不能问出题人问题真的很难受）

---

## 作者：FiraCode (赞：1)

## 题解思路：
我们有 $T$ 轮，只有最后一轮赢了才是赢了，所以前 $T - 1$ 轮，随便就可以了。

状态：
> 必胜态：上一轮一定要输

> 必败态：上一轮一定要赢

所以我们知道了 $i - 1$ 的状态，那么我们就可以求出第 $i$ 轮的状态。

那么我们只要维护一个赢得状态值和输的状态值就可以得到结果。

难点就在他们怎么计算：

------------$Win$ 数组分割线------------
 
>$Win_{e,e} = 0$，因为 $e \ge 1$，所以不管 $e \times 2$ 或者 $e + 1$ 都是必败态。

>那么我们就可以通过 $Win_{e,e}$ 求出 $Win_{e-1,e}$ 等。


若 $e$ 是奇数：
> $Win_{e,e} = 0$

> $Win_{e - 1, e} = 1$只能加一转换成必胜态

> $Win_{e - 2 , e} = 0$因为他是一个奇数，而奇数只能转移到必胜态，因为两个奇数相加，得偶数；奇数加一，就相当于奇数加奇数。所以只会转移到必胜态，所以他就是必败态。
> $$\vdots$$
> $$\vdots$$
> 以此类推

$s$ 与 $e$ 奇偶性相同时，就会走向一个必败态，否则就会走向一个必胜态。

若 $e$ 是偶数：
> 当 $s$ 是偶数，那么 $s \times 2$ 就是必败态，所以当 $\left \lfloor \frac{e}{4} \right \rfloor < s \le \left \lfloor \frac{e}{2} \right \rfloor$，$s \times 2$ 一定是必胜态。




> 当在 $\left \lfloor \frac{e}{4} \right \rfloor$ 这个点时，他一定是必败态，因为他乘二，就会到 $s$ ~ $\left \lfloor \frac{e}{2} \right \rfloor$，所以一定必败。

那么我们就可以递归去判断： $dfs (s , \frac{e}{4})$。

因为 $\left \lfloor \frac{e}{4} \right \rfloor$ 乘二到这个区间，而比他小的一定超不过这个区间，所以若能到必胜态区间 $\left \lfloor \frac{e}{4} \right \rfloor - 1$ ~ $\left \lfloor \frac{e}{2} \right \rfloor$ 这个区间的数，必定是必败态，当我们可以转到 $\frac{e}{2}$ 就是必胜态。

这就是 $Win$ 数组的求法。

------------$Lost$ 数组分割线------------

也可以类似的分析一下：
> $\left \lfloor \frac{e}{2}  \right \rfloor < s \le e $ 时，他一定是必胜态，那么对于 $\frac{e}{2}$ 一定是必败态，这就很像我们分析 $Win$ 时 $e$ 是偶数的情况，我们就可以直接让他转移到 $Win$ 的情况就可以了。

这样，Win 和 Lost 数组就都求出来了。

虽然我们前面说过要到着来，但是我们正着来就行了，那么当我们这一轮为先手，那么 Win 和 Lost 只有一个为 $1$，那么它就不能改变结果，若 Win 和 Lost 都是 $1$ 那么想输想赢都可以，这样最后的就可以知道了。

**注意：$1 \le s_i,e_i \le 10^{18}$，要开 long long！**

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
bool dfs (ll s , ll e) {
	if (e & 1) {//奇偶性是否相同 
		if (s & 1) return false;
		else return true;
	}
	if (s > e / 2) {
		if (s & 1) return true; 
		else return false;
	}
	if (s > e / 4) return true;//当他大于e/4时，和偶数为必胜态区间范围，所以返回true 
	return dfs (s , e >> 2);//递归 
}
bool check (ll s , ll e) { 
	if (s > e / 2) return true;//奇数里这个区间为必胜态
	return dfs (s , e >> 1);//否则返回和Win的共同部分 
}
int main() {
	int n;
	cin >> n;
	bool cur = false , win , lose;
	for (int i = 0; i < n; ++ i) {
		ll s , e;
		cin >> s >> e;
		win = dfs (s , e);//Win
		lose = check (s , e);//Lost
		win ^= cur;//和是否先手异或一下 
		lose ^= cur;
		if (win == lose) break;//若Lost和Win一样 ，break 
		if (win) cur = 1;//若这一局你赢了，那么下一局你先手 
		else cur = 0;//否则就是后手 
	}
	cout << win << ' ' << lose << endl; 
	return 0;
}
```
码字不易，求赞！

---

## 作者：xcyle (赞：1)

看了一下洛谷的其它题解，貌似都是找规律的...

---

**约定**：以下陈述基于 $t$ 确定的前提。容易发现“下一局的先手必胜”和“下一局的先手必败”这两者可以转化为同一个问题。只需将前者的 $t$ 除以2即可，下述仅考虑后一个问题。设 $f(s)$ 表示 $s$ 的胜负状态，0为先手胜，1位后手胜

**结论1**：可以将 $f(s)$ 按照其 $s$ 的取值划分为若干段，使得每一段的状态为以下两种之一：

- 胜负交替
- 全胜

**结论2**：每一段形如 $[\lfloor \frac{r}{2}\rfloor + 1, r]$，且按照顺序排序后有如下事实：

- 若后一段为全胜，前一段为胜负交替，且先负
- 若后一段为胜负交替且奇数胜，则前一段为全胜
- 若后一段为胜负交替且偶数胜，则前一段为胜负交替

**证明**：

可以发现这样划分后每一段 $\times 2$ 后的值域都会落在后一段上，因此如果胜负交替且奇数胜，前一段可以全选 $\times 2$ 取得胜利。其余证明显然。

关于如何想到的，倒推即可

---

## 作者：LMB_001 (赞：1)

打个表找一下SG函数的规律
```cpp
int main(){
	for(int i=1;i<=100;i++){
		printf("i=%d---------------\n",i);
	/*	f[i]=0;g[i]=1;
		for(int j=i-1;j>=1;j--){
			if(j*2>i) f[j]=(f[j+1]^1);
			else f[j]=((f[j+1]&f[j*2])^1);
			g[j]=(f[j]^1);
		}
	*/
	/*	f[i]=1;
		for(int j=i-1;j>=1;j--){
			if(j*2>i) f[j]=1;
			else f[j]=((f[j*2]&f[j+1])^1);
		}
	*/
		for(int j=1;j<=i;j++) printf("SG[%d]=%d\n",j,f[j]);
	}
	return 0;
}
```
然后dp就行了
```cpp
int main(){
	n=read();
	f[0][0][0]=1;//先手必败
	for(int i=1;i<=n;i++){
		e=readll(),s=readll();
		ll t=s;
		bool f1,f2;//先手必胜和后手必胜
		while(1){
			if(t&1ll){f1=((t-e)&1ll);f2=f1^1;break;}
			ll l=t/2,r=t/4;
			if(e>l){f1=((t-e)&1ll);f2=f1^1;break;}
			else if(e>r){f1=1;f2=0;break;}
			else t=r;
		}
		
		bool g1,g2;//先手必败和后手必败
		if(e>s/2){g1=1;g2=0;}
		else{
			t=s/2;
			while(1){
				if(t&1ll){g1=((t-e)&1ll);g2=g1^1;break;}
				ll l=t/2ll,r=t/4ll;
				if(e>l){g1=((t-e)&1ll);g2=g1^1;break;}
				else if(e>r){g1=1;g2=0;break;}
				else t=r;
			}
		}
		f[i][0][0]=(f[i-1][0][0]|f[i-1][1][0])&g1;//先手必败
		f[i][0][1]=(f[i-1][0][0]|f[i-1][1][0])&f1;//先手必胜
		f[i][1][0]=(f[i-1][0][1]|f[i-1][1][1])&g2;//后手必败
		f[i][1][1]=(f[i-1][0][1]|f[i-1][1][1])&f2;//后手必胜

	}
	printf("%d %d\n",(f[n][0][1]|f[n][1][1]),(f[n][0][0]|f[n][1][0]));
	return 0;
}
```


---

