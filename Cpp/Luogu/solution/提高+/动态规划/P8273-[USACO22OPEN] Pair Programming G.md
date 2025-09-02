# [USACO22OPEN] Pair Programming G

## 题目背景

由于题目数据问题，在本题中，你**无需考虑**非平凡的（都有 0 或者只差若干个 1 或者仅顺序不同时称为平凡的）、两组不同的数乘积一样的情况，例如 $t\times2\times3=t\times6$；或者，你应当把题面中的 $\times 2,3,4,5,6,7,8,9$ 分别视为 $\times 2,3,5,7,11,13,17,19$ 处理。

## 题目描述

一个程序由一系列指令组成，每条指令都具有以下形式之一：

- $\times d$，其中 $d$ 是一个 $[0,9]$ 范围内的一位数；
- $+s$，其中 $s$ 是一个表示变量名称的字符串。一个程序中出现的所有的变量名均不相同。

程序执行的结果定义对表达式 $0$ 依次应用每条指令后得到的表达式。例如，执行程序 $[\times 3,+x,+y,\times 2,+z]$ 得到的结果是表达式 $(0\times 3+x+y)\times 2+z=2 \times x+2\times y+z$。不同的程序执行后可能会得到相同的表达式；例如，执行 $[+w,\times 0,+y,+x,\times 2,+z,\times 1]$ 也会得到表达式 $2\times x+2\times y+z$。

Bessie 和 Elsie 各有一个 $N$（$1\le N\le 2000$）条指令的程序。他们将交错这些程序的指令以制造一个 $2N$ 条指令的新程序。注意有 $\frac{(2N)!}{N!\times N!}$ 种方法可以做到这一点，但并非所有这样的程序在执行后都会得到不同的表达式。

计算执行 Bessie 和 Elsie 的交错程序可能得到的不同表达式的数量，对 $10^9+7$ 取模。

每个测试用例包含 $T$（$1\le T\le 10$）个需要独立求解的子测试用例。输入保证所有子测试用例中的 $N$ 之和不超过 $2000$。

## 说明/提示

【样例解释】

对于第一个子测试用例，两个可以制造的交错程序为 $[\times 1, \times 0]$ 和 $[\times 0,\times 1]$。它们执行后均会得到表达式 $0$。

对于第二个子测试用例，执行 $[\times 1,\times 2, +x]$ 和 $[+y, \times 0,\times 2]$ 的交错程序可以得到表达式 $0$，$x$ 和 $2\times x$ 之一。

【测试点性质】

- 测试点 2 满足 $N\le 6$。
- 测试点 3-5 中，所有 $N$ 之和不超过 $100$。
- 测试点 6-8 中，所有 $N$ 之和不超过 $500$。
- 测试点 9-16 没有额外限制。

## 样例 #1

### 输入

```
4
1
0
1
3
12+
+02
3
0++
++9
4
5+++
+6+1```

### 输出

```
1
3
9
9```

# 题解

## 作者：Usada_Pekora (赞：11)

看到数据范围再考虑到 USACO 从不卡常，可以猜想这应该是个 $O(N^2)$ 的 DP。

首先对输入串做一个处理：如果有乘 $0$ 的操作，那前面就没用了，如果有乘 $1$ 的操作，对答案没有影响，直接舍去。

小学数学里有乘法交换律和加法交换律： $a\cdot b = b \cdot a,a + b = b + a$ ，也就是说，如果两个同类操作放在一起，那么交换它们产生的结果不变。

定义一种对 $(x,y)$ ， 其中 $x$ 是来自 $A$ 的操作， $y$ 是来自 $B$ 的操作，且操作类型相同。

那么答案是不包含这类对 $(x,y)$ 的串的数量，因为出现这种情况的时候把 $x,y$ 交换，直到没有这种对后，表达式的结果不变。

设 $f[i][j][0/1]$ 表示 $A$ 串匹配到 $i$ 位，$B$ 串匹配到 $j$ 位，最后一个是 $A$ 或者 $B$ 的指令的答案。

对于结尾为 $0$ 的情况： $f[i+1][j][0] = f[i][j][0]+f[i][j][1]$ ：因为这些串都合法，所以在后面插入一个新的来自 $A$ 的操作的新串不会不合法。

对于结尾为 $1$ 的情况 ： 如果是 $A_i \neq B_{j+1}$ ，则 $f[i][j+1][1]=f[i][j][0]+f[i][j][1]$ ，否则 $f[i][j+1][1]=f[i][j][1]$ 。  

边界条件： $f[0][0][1] = 1$ ，虽然没有具体意义，但只有最后一维是 $1$ 才能合法的开始转移，或者手推也行（只不过我比较懒）。

UPDATE ：去了 `memset` 以后，跑的飞快，一发卡进最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005, mod = 1e9 + 7;
int n, f[N][N][2], lena, lenb, T;
char str[N], a[N], b[N];
inline void read(char s[], int &slen) {
	slen = 0;
	cin >> str;
	int len = strlen(str);
	for(int i = 0; i < len; i++) {
		if(str[i] == '0') slen = 0;
		else if(str[i] == '1') continue;
		if(str[i] != '+') str[i] = '*';
		s[++slen] = str[i];
	}
}
inline int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}
signed main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--) {
		cin >> n;
		read(a, lena), read(b, lenb);
		f[0][0][1] = 1;
		for(int i = 0; i <= lena; i++) {
			for(int j = 0; j <= lenb; j++) {
				if(i < lena) f[i + 1][j][0] = add(f[i][j][0], f[i][j][1]);
				if(j < lenb) f[i][j + 1][1] = f[i][j][1];
				if(i > 0 && j < lenb && a[i] != b[j + 1]) f[i][j + 1][1] = add(f[i][j + 1][1], f[i][j][0]);
			}
		}
		printf("%d\n", add(f[lena][lenb][0], f[lena][lenb][1]));
	}
	return 0;
}
```


---

## 作者：耶梦加得 (赞：8)

~~根据数据范围~~容易想到此题应该是一个 $O(n^2)$ 的 DP。

令 $dp_{i,j}$ 表示 Bessie 的程序（下称为 a 字符串）写入了前 $i$ 个字符，且 Elsie 的程序（下称为 b 字符串）写入了前 $j$ 个字符时有多少个不同的结果。边界条件为 $dp_{i,0} = dp_{0,i} = 1$。

~~易知~~ $dp_{i,j}$ 由 $dp_{i,j-1}$ 和 $dp_{i-1,j}$ 转移而来。分别表示最后一个字符是 $b_j$ 和 $a_i$ 产生的结果。

先不考虑 $0$，经过思考，可以发现以下情况下，这两者会产生重复：

1. 其中有至少一个字符是 '1'（易知）。
2. 两个字符都是数字或者都是 '+'。

在这两种情况下，容易发现若最后两位由这两个字符构成（此时 $a_{1\cdots i-1}$ 和 $b_{1 \cdots j-1}$ 已经固定），这两个字符的顺序不会影响结果。
换而言之我们多算了 $2dp_{i-1,j-1} - dp_{i-1,j-1}$， 亦即$dp_{i-1,j-1}$ 这么多。

最后考虑 $0$，若两个字符都是 $0$ 直接令 $dp_{i,j} = 1$	即可，否则不妨设 $a_i$ 为 '0'。

首先，易知把 ‘0’ 置于末尾可以得到 $0$ 的结果。

若最后一位是 $b_j$（对应$dp_{i,j-1}$），我们需要考虑这些结果中是否有 $0$ 的存在。不难发现倒数第二位可以放上 $a_i$，即 '0'。那么能否产生 $0$ 的最终结果，仅取决于 $b_j$ 是否是数字。

~~我就是为了说不需要辅助数组写的这篇题解。~~

完整的转移方程~~情况太多请读者自行整合~~可以参考代码。

```
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
const int mod = 1000000007;
int T;
int n;
char a[2007], b[2007];
int dp[2007][2007];
signed main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        scanf("%s", a + 1); scanf("%s", b + 1);
        for(int i = 0; i <= n; ++i) {
            dp[i][0] = dp[0][i] = 1;
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(a[i] == '0' && b[j] == '0') {
                    dp[i][j] = 1;
                    continue;
                }
                if(a[i] == '0') {
                    dp[i][j] = (dp[i][j - 1] + 1 - isdigit(b[j])) % mod;
                    continue;
                }
                if(b[j] == '0') {
                    dp[i][j] = (dp[i - 1][j] + 1 - isdigit(a[i])) % mod;
                    continue;
                }
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
                if(a[i] == '1' || b[j] == '1') (dp[i][j] += mod - dp[i - 1][j - 1]) %= mod;
                else if(isdigit(a[i]) && isdigit(b[j])) (dp[i][j] += mod - dp[i - 1][j - 1]) %= mod;
                else if(a[i] == '+' && b[j] == '+') (dp[i][j] += mod - dp[i - 1][j - 1]) %= mod;
            }
        }
        printf("%d\n", dp[n][n]);
    }
}

```


---

## 作者：yaoxi (赞：5)

[或许会更好的阅读体验](https://yaoxi-std.github.io/2022/03/27/sol-p8273/)

### 题面

[题目链接](https://www.luogu.com.cn/problem/P8273)

### 解法

~~同届的巨佬们已经都通关了 USACO，只有我还在做 Gold 组的蓝题~~

看到 $n \le 2000$，不难想到可能是个 $O(n^2)$ 的 $dp$。

设 $dp[i][j]$ 表示匹配到 Bessie 程序中的第 $i$ 位和 Elsie 程序中的第 $j$ 位。

显然转移的方式应该是 $dp[i][j] = dp[i-1][j] + dp[i][j-1] - \text{某个重复算的东西}$。

不难发现只有在下列情况才会有东西重复算：

- $s1_i$ 和 $s2_j$ 同为数字或同为 `+`
- $s1_i$ 或 $s2_j$ 中有一个是 $1$

重复算的时候，简单容斥下发现需要减去 $dp[i-1][j-1]$。

还有个棘手的问题，就是要处理 $\times 0$ 这种操作，因为其会导致“前功尽弃”。所以可以在 $dp$ 的同时记录下 $f[i][j]$ 表示状态 $(i,j)$ 是否能达到表达式为 $0$ 这种情况。

代码实现的话，我是开了个 `Node` 方便同时进行 $dp$ 和 $f$ 的储存。具体可以看我的代码。

### AC代码

```cpp
/**
 * @file:           T2.cpp
 * @author:         yaoxi-std
 * @url:            
*/
// #pragma GCC optimize ("O2")
// #pragma GCC optimize ("Ofast", "inline", "-ffast-math")
// #pragma GCC target ("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
#define resetIO(x) \
    freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout)
#define debug(fmt, ...) \
    fprintf(stderr, "[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
template <class _Tp>
inline _Tp& read(_Tp& x) {
    bool sign = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) sign |= (ch == '-');
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar((x % 10) ^ 48);
}
bool m_be;
using ll = long long;
const int MAXN = 2e3 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int n;
char s1[MAXN], s2[MAXN];
inline int add(int x, int y) { return (x += y), (x >= MOD ? x - MOD : x); }
inline int sub(int x, int y) { return (x -= y), (x < 0 ? x + MOD : x); }
struct Node {
    int cnt; bool zero; // cnt 除 0 之外的有多少种表达式，zero 是否能使得表达式为 0
    // 两个 Node 相加（合并），cnt 相加，zero 取或，这个不必多说
    Node operator+(const Node& o) const { return {add(cnt, o.cnt), zero || o.zero}; }
    Node& operator+=(const Node& o) { return cnt = add(cnt, o.cnt), zero |= o.zero, *this; }
    // 两个 Node 相减（也就是减去重复的部分容斥），cnt 相减，zero不变
    Node operator-(const Node& o) const { return {sub(cnt, o.cnt), zero}; }
    Node& operator-=(const Node& o) { return cnt = sub(cnt, o.cnt), *this; }
    // 将 Node 后面添加一个操作后更新 cnt 和 zero
    Node extend(char c) const {
        // *0 的操作
        if (c == '0') return {0, 1};
        // *x 的操作
        if (isdigit(c)) return {cnt, zero};
        // 新添加变量
        return {add(cnt, zero), 0};
    }
} dp[MAXN][MAXN];
// 判断两个操作交换顺序后是否等价
inline bool same(char c1, char c2) {
    if (isdigit(c1) == isdigit(c2)) return 1;
    if (c1 == '1' || c2 == '1') return 1;
    return 0;
}
bool m_ed;
signed main() {
    // debug("Mem %.5lfMB.", fabs(&m_ed - &m_be) / 1048576);
    int cas; read(cas);
    while (cas--) {
        scanf("%d%s%s", &n, s1 + 1, s2 + 1);
        for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = {0, 0};
        dp[0][0] = {0, 1};
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (i) dp[i][j] += dp[i - 1][j].extend(s1[i]);
                if (j) dp[i][j] += dp[i][j - 1].extend(s2[j]);
                if (i && j && same(s1[i], s2[j])) dp[i][j] -= dp[i - 1][j - 1].extend(s1[i]).extend(s2[j]);
            }
        }
        write(add(dp[n][n].cnt, dp[n][n].zero)), putchar('\n');
    }
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8273)
## 思路
诈骗题。

其实这题只要想到是 $\verb!DP!$ 就好做了。

设 $f_{i,j}$ 表示第一个字符串到了第 $i$ 位，第二个字符串到了第 $j$ 位的情况种数。

然后就开始分类：

+ 如果 $s1_i$ 和 $s2_i$ 都是 $0$，显然不管怎么操作，结果都是 $0$，此时 $f_{i,j}=0$。
+ 如果 $s1_i$ 是 $0$，那么有两种情况：如果先放 $0$，那么如果 $s2_i$ 是个数字，显然 $0 \times a=0$，所以会产生 $0$，与下面重复了；如果 $s2_i$ 是个字母，那么有 $f_{i,j-1}$ 种情况。如果后放 $0$，不管是啥，结果都变成 $0$。
+ 如果 $s2_i$ 是 $0$，同上。
+ 如果 $s1_i$ 和 $s2_i$ 是一个 $+$，一个数字，那么如果先放 $+$，有 $f_{i,j-1}$ 种情况，先放数字，有 $f_{i-1,j}$ 种情况。
+ 如果 $s1_i$ 和 $s2_i$ 都是 $+$，或都是数字，或者有一个是 $1$。根据乘法交换律/加法交换律，先放什么的答案都是一样的。根据容斥原理，我们先把两种都加起来，为 $f_{i-1,j}+f_{i,j-1}$，再减去 $f_{i-1,j-1}$ 就是最终的答案，放一张图片辅助理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/cvh3ip5r.png)

易知此时 $s1_{i-1},s2_{i-1}$ 先加上绿色块后加上橙色块和先加上橙色块，后加上绿色块的答案是一样的，被多算了一遍，需要减去它，即减去 $f_{i-1,j-1}$。

初始：$f_{0,i}=f_{i,0}=1$。

答案：$f_{n,n}$。

## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e3+10;
int const mod=1e9+7;
int f[N][N]; 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while (T--){
		int n;cin>>n;
		string s1,s2;cin>>s1>>s2;
		s1=" "+s1,s2=" "+s2;
		for (int i=0;i<=n;++i) f[i][0]=f[0][i]=1;
		for (int i=1;i<=n;++i)
		    for (int j=1;j<=n;++j){
		    	if (s1[i]=='0' && s2[j]=='0') f[i][j]=1;
		    	else if (s1[i]=='0'){
		    		if (s2[j]=='+') f[i][j]=f[i][j-1]+1;
		    		else f[i][j]=f[i][j-1];
				}else if (s2[j]=='0'){
					if (s1[i]=='+') f[i][j]=f[i-1][j]+1;
					else f[i][j]=f[i-1][j];
				}else if (s1[i]=='+' && s2[j]=='+' || s1[i]!='+' && s2[j]!='+' || s1[i]=='1' || s2[j]=='1') f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
				else f[i][j]=f[i-1][j]+f[i][j-1];
				f[i][j]=(f[i][j]>=mod)?f[i][j]-mod:f[i][j];
				f[i][j]=(f[i][j]<0)?f[i][j]+mod:f[i][j];
			}
	    cout<<f[n][n]<<'\n';
	}
	return 0;
}
```


---

## 作者：Lgx_Q (赞：0)

这个数据范围容易想到经典平方状态常数转移的 DP。

因为每个加号表示的变量都不一样，画几个样例发现很少出现有两个顺序折成同样的算式。

于是考虑特殊的情况。

1. 对于一段连续的字母或数字，顺序对最终的答案没有影响。

2. 对于 $\times 1$，放在哪都行，不妨直接去掉。

3. 对于 $\times 0$，在此之前的东西全部都消掉，于是前面的东西顺序对答案无关。

设 $f_{i,j}$ 表示第一个程序前 $i$ 条语句与第二个程序前 $j$ 条语句的答案。

预处理，先把所有 $\times 1$ 去掉。

显然，转移分重排后第 $i+j$ 条语句是第一个程序还是第二个程序。如果 $a_i$ 和 $b_j$ 同时是数字或字母（变量），把其内部顺序去掉，类似二维前缀和，容斥减去 $f_{i-1,j-1}$。

如果 $a_i=0$，那么用 $1$ 替换 $f_{i-1,j}$，$b_j=0$ 类似。当在两者其中有 $0$ 的情况进行容斥，不难发现前面 $f_{i-1,j-1}$ 那些东西乘上 $0$ 和另外一个数字，方案数总是 $1$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=2010,mod=1e9+7;
ll t,n,f[maxn][maxn],lena,lenb;
char a[maxn],b[maxn];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%s%s",&n,a+1,b+1);
		lena=lenb=0;
		for(ll i=1;i<=n;i++)
		{
			if(a[i]!='1') a[++lena]=a[i];
			if(b[i]!='1') b[++lenb]=b[i];
		}
		for(ll i=0;i<=lena;i++)
			for(ll j=0;j<=lenb;j++)
			{
				if(!i||!j)
				{
					f[i][j]=1;
					continue;
				}
				f[i][j]=((a[i]!='0'?f[i-1][j]:1)+(b[j]!='0'?f[i][j-1]:1))%mod;
				if(a[i]=='+'&&b[j]=='+'||isdigit(a[i])&&isdigit(b[j]))
					f[i][j]=(f[i][j]-(a[i]!='0'&&b[j]!='0'?f[i-1][j-1]:1)+mod)%mod;
			}
		printf("%lld\n",f[lena][lenb]);
	}
	return 0;
}
```

---

