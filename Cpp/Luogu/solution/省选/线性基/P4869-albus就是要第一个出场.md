# albus就是要第一个出场

## 题目描述

已知一个长度为 $n$ 的正整数序列 $A$（下标从 $1$ 开始），令 $S = \{ x | 1 \le x \le n \}$，$S$ 的幂集 $2^S$ 定义为 $S$ 所有子集构成的集合。定义映射 $f : 2^S \to Z,f(\emptyset) = 0,f(T) = \mathrm{XOR}\{A_t\}, (t \in T)$。

现在 albus 把 $2^S$ 中每个集合的 $f$ 值计算出来，从小到大排成一行，记为序列 $B$（下标从 $1$ 开始）。 

给定一个数，那么这个数在序列 $B$ 中第 $1$ 次出现时的下标是多少呢？

## 说明/提示


【样例解释】  

$N = 3,A = [1,2,3]$  
$S = \{1,2,3\}$  
$2^S = \{\emptyset,\{1\},\{2\},\{3\},\{1,2\},\{1,3\},\{2,3\},\{1,2,3\}\}$  
$f(\emptyset) = 0$  
$f({1}) = 1$  
$f({2}) = 2$  
$f({3}) = 3$  
$f({1, 2}) = 1 \operatorname{xor} 2 = 3$  
$f({1, 3}) = 1 \operatorname{xor} 3 = 2$  
$f({2, 3}) = 2 \operatorname{xor} 3 = 1$  
$f({1, 2, 3}) = 0$  
所以  
$B = [0,0,1,1,2,2,3,3]$

【数据范围】

$1 \leq N \leq 10,0000$  
其他所有输入均不超过 $10^9$

## 样例 #1

### 输入

```
3
1 2 3
1```

### 输出

```
3```

# 题解

## 作者：Kinandra (赞：37)

.标签：线性基.

.首先求出$V$的线性基 $\mathfrak{B}$.

.如果去除序列$B$中重复的数, 使用线性基, 根据$Q$的二进制位便可以确定$Q$的排名, 可是如果不去重, 怎么才能知道每个数出现多少次呢?

.结论: 每个数都出现一样的次数, 且这个次数为$2^{n - \vert\mathfrak{B}\vert}$.

证明：所有不在线性基中的数的个数为$n-\vert\mathfrak{B}\vert$, 我们任意选择它的一个子集$S$.

$\because\forall v \in S$, 有唯一的方式表达为$\mathfrak {B}$中向量的线性组合, 即$\mathfrak {B}$有唯一子集使得该子集中的向量异或和与$v$异或得$0$.

$\therefore\forall x\in B$, 我们都能找到$2^{n - \vert \mathfrak{B}\vert}$种不同的选择方案, 使得异或值为$x$.

又$\because$对于每个子集$S$, 选择线性基中的向量的方案是唯一的.

$\therefore$方案数的上界也是$2^{n - \vert \mathfrak{B}\vert}$.

有理有据, 令人信服

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

int b[102];
int cnt = 1, mod = 10086;
void ist(int tmp) {
    for (int i = 30; i >= 0; --i) {
        if (!((1 << i) & tmp)) continue;
        if (!b[i]) {
            b[i] = tmp;
            break;
        }
        tmp ^= b[i];
        if (tmp == 0) {
            (cnt <<= 1) %= mod;
            break;
        }
    }
}


int dp[102][3];
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        int tmp = read();
        ist(tmp);
    }

    int tmp = read();
    int rk = 0;
    int tp = 1;
    for (int i = 0; i <= 30; ++i) {
        if (b[i]) {
            if ((tmp >> i) & 1)rk += tp;
            tp <<= 1;
        }
    }
    rk %= mod;
    printf("%d\n", (rk * cnt + 1) % mod);
    return 0;
}
```

---

## 作者：wrpwrp (赞：13)

这题貌似没人给出一个正常的证明，所以给一个比较好理解的证明。

设$n$个数的线性基里面有$k$个数，那就有$n- k$个数不在线性基里面。考虑分类讨论一下。
先说明，对于一个异或和，在外面$n - k$个数中任意取一个数加入异或出这个异或和的数的集合，一定可以通过调整集合内在原本的线性基内的数的组成来使异或和不变。
- 如果从外面加入的这个数可以用除了表示出这个异或和的那些线性基内的数表示出来，那就把那些数也异或进来，那么异或和不变。
- 如果外面加入的数必须用完全属于表示出这个异或和的那些线性基内的数表示出来，那就不选这些数，那异或和还是不变。
- 如果部分属于表示这个集合的数，部分不属于，那就把两个部分拆开，属于的部分不选，不属于的部分选，就把这两个部分都变成了$0$，异或和还是不变。

那么如果从外面$n - k$个数中选多于一个数，那么对于每一个数都按照一个数的操作方法就可以保证异或和不变。所以对于外面的点的任意一个集合都是可以通过调整线性基内的数使得异或和不变。所以同一个异或和出现了$2^{n - k}$次。

代码太丑了就不贴了　~~（其实是我懒得写了~~

---

## 作者：zcxxnqwq (赞：7)


[更多线性基知识戳这里](https://blog.csdn.net/zcxxn/article/details/128518694?spm=1001.2014.3001.5501)

自认为讲得比较清楚的证明 qwq。

一个结论：$n$ 个数组成大小为 $s$ 的线性基，则能构成 $2^s$ 种不同的数，每个数出现 $2^{n-s}$ 次。

证明：首先每个不在线性基中的数都能被唯一地表示成若干线性基中的数异或和的形式。

考虑一个可以被线性基表示的数 $x$，将线性基划分为用来表示 $x$ 的数 $S1$、不用于表示 $x$ 的数 $S2$ 两个集合。那么对于每一个不在线性基中的数 $y$，将其表示为 $S1$ 的一个子集 $s1$ 与 $S2$ 的一个子集 $s2$（均可以为空）的异或和。那么就有选 $s1$（方案 $1$）或选 $s2$ 和 $y$（方案 $2$）两种选法。每个 $y$ 的选择之间相互独立，所以共 $2^{n-s}$ 种选法。

对于相互独立这一点可能存在疑问。比如当 $y_1$ 对应的 $s1$ 和 $y_2$ 对应的 $s1$ 之间有交集时，我们已经钦定了 $y_1$ 选方案 $2$，$y_2$ 对应的 $s1$ 集合就不能被完整选到。看起来有点凉，但是其实 $y_1$ 已经贡献完了交集部分，$y_2$ 只需要把其对应的 $s1$ 集合的不属于交集部分的数选上就可以了，也是能做到的。所以选择相互独立。

然后这道题就差不多做完了。

实现上，我们知道线性基可以通过被改造使得 $\forall_{i<j}\ (p_i\ xor \ p_j>p_i)\land (p_i\ xor\ p_j>p_j)$，且改造后线性基中有值的位置不变，所以可以直接记录每个有值的位置 $pos$ 及线性基中比它小的位置上有值的位置个数 $cnt$，枚举每个满足 $k$ 在二进制第 $pos$ 位有值的位置作为最高的不选位置，剩下更低位随便选，方案数 $2^{cnt}$。这样得到不可重集中 $k$ 的排名就可以知道可重集中 $k$ 的排名了。时间复杂度 $O(n\log V)$，其中 $V$ 为值域。

upd：感谢 @[hxhhxh](https://www.luogu.com.cn/user/429147) 指出最后加一没取模，已修锅。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,s,e) for(int i=(s);i<=(e);++i)
#define Rep(i,s,e) for(int i=(e);i>=(s);--i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+5,mod=10086;
int n,p[35],a[N],k,b[N];
inline void ins(int x){
	Rep(i,0,30) if(x&(1<<i)){
		if(!p[i]) return p[i]=x,void();
		x^=p[i];
	}
}
inline int ksm(int x,int y){
	int res=1;
	for(;y;y>>=1){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
	}
	return res;
}
signed main(){
	n=read();
	rep(i,1,n) a[i]=read(),ins(a[i]);
	int s=0,rk=0;
	rep(i,0,30) if(p[i]) b[s++]=i;
	k=read();
	rep(i,0,s-1) if(k&(1<<b[i])) rk|=(1<<i);
	rk=1ll*ksm(2,n-s)*rk%mod;
	printf("%d\n",(rk+1)%mod);
}
```


---

## 作者：bztMinamoto (赞：7)

更好的阅读体验：[这里](https://www.cnblogs.com/bztMinamoto/p/9715741.html)

楼下的那位写的真的是线性基么……我太菜了实在看不懂……

线性基居然有这性质我还不知道orz

假设$n$个数的线性基中有$k$个数，那么显然共有$2^k$个不同的异或和，而其中每一个异或和的出现次数都是$2^{n-k}$

感性理解一下的话……就是不在线性基中的每一个数字都可以被线性基中的数字表示出来从而异或之后为0，那么这些数字都可以看做0,

所以每一个异或和都可以异或上0变成自己，那么0有多少种选法呢？加上空集就是$2^{n-k}$种

然后只要算出$q$之前有多少个数就好了……

然后这个东西具体怎么算……看代码好了……
```
//minamoto
#include<iostream>
#include<cstdio>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while((ch=getc())>'9'||ch<'0')
    (ch=='-')&&(flag=true);
    for(res=num;(ch=getc())<='9'&&ch>='0';res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int mod=10086;
int b[35],st[35],top,n,q,rk;
inline int ksm(int x,int y){
    int res=1;
    while(y){
        if(y&1) (res*=x)%=mod;
        (x*=x)%=mod,y>>=1;
    }
    return res;
}
void insert(int x){
    for(int i=30;i>=0;--i)
    if(x>>i&1){
        if(!b[i]) return (void)(b[i]=x);
        x^=b[i];		
    }
}
int main(){
//	freopen("testdata.in","r",stdin);
    n=read();
    for(int i=1,x;i<=n;++i) insert(x=read());
    q=read();
    for(int i=0;i<=30;++i)
    if(b[i]) st[top++]=i;
    for(int i=0;i<top;++i)
    if(q>>st[i]&1) rk+=1<<i;
    printf("%d\n",(1ll*rk*ksm(2,n-top)+1)%mod);
    return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：6)

## 定理
$\textbf{Thm 1 (基扩张定理).}$ 设 $U,V$ 是有限维线性空间，$U$ 是 $V$ 的线性子空间，$\dim U = n, \dim V = m$。$\{\boldsymbol e_1, \boldsymbol e_2, \dots, \boldsymbol e_n\}$ 是 $U$ 的一组基，则必然存在 $\{\boldsymbol f_1, \boldsymbol f_2, \dots, \boldsymbol f_{m-n}\}$ 使得 $\{\boldsymbol e_1, \boldsymbol e_2, \dots, \boldsymbol e_n, \boldsymbol f_1, \boldsymbol f_2, \dots, \boldsymbol f_{m-n}\}$ 是 $V$ 的一组基。  
证明：考虑对 $n-m$ 进行归纳。若 $m-n=0$，显然。否则取取 $V \setminus U$ 中任意元素 $\boldsymbol v$，显然 $\boldsymbol v$ 与整个 $U$ 线性无关。于是 $U' = \operatorname{span} \{U,\boldsymbol v\}$ 线性无关，且 $\dim U' = m+1$。据归纳假设 $n-m+1$ 的情况得证。

$\textbf{Thm 2 (核-像定理)}$ 若 $\boldsymbol f : U \to V$ 是线性映射，则
$$
\dim \ker \boldsymbol f + \dim \operatorname{Im} \boldsymbol f = \dim U.
$$
证明：任取 $\ker \boldsymbol f$ 的一组基 $K = \{\boldsymbol e_1, \dots, \boldsymbol e_{\operatorname {nullity} \boldsymbol f}\}$ 据 $\textbf{Thm 1}$ 得存在 $\overline K = \{\boldsymbol e_1',\dots,\boldsymbol e_{n-\operatorname{nullity} \boldsymbol f}'\}$ 使得 $S = \{\boldsymbol f_1, \dots, \boldsymbol f_{\dim U}\} = K \cup \overline K$ 是 $U$ 的一组基。而对 $\boldsymbol u \in U$，
$$
\begin{aligned}
\boldsymbol f(\boldsymbol u) &= \boldsymbol f \left(\sum_{i=1}^{\dim U} \lambda_i \boldsymbol f_i \right) \\
&= \boldsymbol f \left(\sum_{i=1}^{\operatorname{nullity} \boldsymbol f} \xi_i \boldsymbol e_i \right) + \boldsymbol f \left(\sum_{i=1}^{n-\operatorname{nullity} \boldsymbol f} \mu_i \boldsymbol e_i' \right) \\
&= \boldsymbol f \left(\sum_{i=1}^{n-\operatorname{nullity} \boldsymbol f} \mu_i \boldsymbol e_i' \right).
\end{aligned}
$$
于是 $\boldsymbol f(U) = \boldsymbol f(\operatorname{span} \overline K) \implies \dim \operatorname{Im} \boldsymbol f = \dim \operatorname{span} \overline K$。而 $\overline K$ 是基 $S$ 的子集，线性无关。于是 $\dim \operatorname{Im} \boldsymbol f = |\overline K| = |S \setminus K| = |S| - |K| = \dim U - \dim \ker \boldsymbol f$。

$\textbf{Collary 1}$ 对线性映射 $\boldsymbol f : U \to V$，设 $\boldsymbol f^{-1}(\boldsymbol x) = \{\boldsymbol y \mid \boldsymbol f(\boldsymbol y) = \boldsymbol x\}$，则对任意的 $\boldsymbol x \in V$，都有 $\boldsymbol f^{-1}(\boldsymbol x) + \ker \boldsymbol f = \boldsymbol f^{-1}(\boldsymbol x)$，且 $\boldsymbol f^{-1}(\boldsymbol x) =  \{\boldsymbol y\} + \ker \boldsymbol f$。其中 $S + T = \{s+t \mid s \in S, t \in T\}$ 。

## 题解
对于 $a_0, \dots, a_{n-1} \in \mathbb F_2^{n}$，设 $B = \{2^0,\dots,2^{n-1}\}$，构造如下线性映射:
* $\boldsymbol f$ 是 $\boldsymbol f(2^t) = a_t$ 所确定的唯一线性映射。

有了线性映射这个有力的工具，很多问题迎刃而解：
* 有多少个 $S \subseteq \{a_0, \dots, a_{n-1}\}$ 的异或和为 $0$？  
即计算 $|\ker \boldsymbol f| = 2^{\dim \ker \boldsymbol f} = 2^{n-\dim \operatorname{Im} \boldsymbol f} = 2^{n-\dim \operatorname{span}\{a_0,\dots,a_{n-1}\}}$。使用线性基算法维护 $a_0, \dots, a_{n-1}$ 的极大线性无关组即可。
* 有多少个 $S \subseteq \{a_0, \dots, a_{n-1}\}$ 的异或和为 $x$？  
使用 $\textbf{Collary 1}$ 的结论即可转化为上一个问题。
* 有多少个 $S \subseteq \{a_0, \dots, a_{n-1}\}$ 的异或和小于 $x$？   
只需找到 $x$ 在 $\operatorname{Im} \boldsymbol f$ 的排名 $rk$（二分），则 $rk \times$ 上个问题答案即可。
* 本题该怎么计算？
上个问题加一即可。

## 感想
在 OI 中，线性基算法往往缺乏对线性空间与线性映射的概念的补充，而是以背板子为主。本题解看似很长，可在思维上，若了解序列作为线性映射，及线性映射相关的定理，并对 $x$ 的排名和异或和 $<x$ 进行一个简单的转化，逐一攻破，本题就迎刃而解。

## 贴个代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;
const int N = 64;
struct Lspace {
    u64 a[N];
    void ins(u64 x) {
        if (x == 0) return;
        if (a[__lg(x)] == 0) a[__lg(x)] = x;
        ins(x ^ a[__lg(x)]);
    }
    void remake() {
        for (int i = N - 1; i >= 1; --i)
            for (int j = i - 1; j >= 0; --j)
                if (a[i] & (1ULL << j)) a[i] ^= a[j];
    }
    u64 dim() {
        u64 ans = 0;
        for (int i = 0; i < N; ++i)
            if (a[i] != 0) ans++;
        return ans;
    }
    u64 get(u64 id) {
        u64 ans = 0;
        u64 top = 0;
        for (int i = 0; i < N; ++i) {
            if ((id & (1ull << top))) ans ^= a[i];
            if (a[i] != 0) top++;
        }
        return ans;
    }
    u64 rk(u64 x) {
        u64 ans = 0, kel = 1;
        for (int i = 0; i < N; ++i) {
            if (a[i] != 0) {
                if (x & (1ull << i)) ans += kel;
                kel *= 2;
            }
        }
        return ans;
    }
} b;
u64 qpow(u64 b, u64 p) {
    if (p == 0) return 1;
    if (p == 1) return b;
    return qpow(b * b % 10086, p / 2) * qpow(b, p % 2) % 10086;
}
int main() {
    int n, m;
    cin >> n;
    m = n;
    while (n--) {
        u64 x;
        cin >> x;
        b.ins(x);
    }
    int y;
    cin >> y;
    int ch = m - b.dim();
    u64 tm = qpow(2, ch);
    cout << ((b.rk(y)) * tm + 1) % 10086 << endl;
}

```

## changelog
* $18:22$ 修改了事实性错误。


---

## 作者：Log_x (赞：6)

## Solution
- 建出原序列的线性基。
- 我们知道线性基有如下性质：
1. 线性基中元素的子集异或和的集合和原序列的子集异或和的集合相同。
2. 线性基中的任意元素不属于其它元素的子集异或和的集合。
- 由性质 2 得：在线性基中任选一个子集的异或和都互不相同，若线性基中共有 $k$ 个元素，就共有 $2^k$ 种互不相同的异或和。
- 由性质 1 得：原序列可以看做是线性基中的元素再加上 $n - k$ 个 0，因此每种异或和在原序列中都刚好存在 $2^{n - k}$ 种构造方案。
- 于是问题被转化为：求出线性基中子集异或和小于 $Q$ 的子集个数 $cnt$，答案为 $cnt \times 2^{n - k} + 1$。
- 考虑对线性基中元素进行一些转化（等于 -1表示该位元素不存在）：

```cpp
	for (int i = 0; i <= 30; ++i)
		if (~A.g[i])
		for (int j = i - 1; j >= 0; --j)
			if ((~A.g[j]) && (1 << j & A.g[i]))
				A.g[i] ^= A.g[j];
```

- 相当于线性基中的元素与其它元素异或，得到的仍满足线性基的性质。
- 此时线性基中任一元素都要满足：最高位的 1 在线性基中只出现一次。
- 因此构成 $Q$ 的唯一方案为：$Q$ 的所有为 1 的位在线性基中对应且存在的元素的异或和。
- 考虑小于 $Q$ 的子集至少都要不选取这些元素中的其中一些，我们枚举这些元素中不选取的位数最高的元素（假设为从低到高为第 $i$ 个存在的元素），那么位数更低的元素显然可以随便选，对 $cnt$ 的贡献为 $2^i$。
- 时间复杂度 $O(30n)$。

---
## Code
- 转化后显然对最高位的 1 不影响，实现时可以不写转化的部分。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cstdio>

const int Ss = 1 << 20;
char frd[Ss], *ihead = frd + Ss;
const char *itail = ihead;

inline char nxtChar()
{
    if (ihead == itail)
        fread(frd, 1, Ss, stdin), ihead = frd;
    return *ihead++;
}

template <class T>
inline void read(T &res)
{
    char ch; 
    while (ch = nxtChar(), !isdigit(ch));
    res = ch ^ 48;
    while (ch = nxtChar(), isdigit(ch))
        res = res * 10 + ch - 48;
}

typedef long long ll;
const int mod = 10086;
const int N = 1e5 + 5;
int n, m, ans, top; 
int stk[35];

struct Basis
{
	int g[35];
		
	inline void Clear()
	{
		for (int i = 30; i >= 0; --i)
			g[i] = -1;
	}
	
	inline void Insert(int x)
	{
		for (int i = 30; i >= 0; --i)	
			if (1 << i & x)
			{
				if (g[i] == -1) 
					return (void)(g[i] = x);
				x ^= g[i];
			}
	}
}A;

inline int ksm(int x, int k)
{
	int res = 1;
	while (k)
	{
		if (k & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod; k >>= 1;
	}
	return res;
}

int main()
{
	A.Clear();
	
	read(n);
	for (int i = 1, x; i <= n; ++i)
		read(x), A.Insert(x);

	int Q;
	read(Q);
	for (int i = 0; i <= 30; ++i)
		if (~A.g[i]) stk[top++] = i;
	for (int i = top - 1; i >= 0; --i)
		if (Q >> stk[i] & 1) ans += 1 << i;
	printf("%d\n", (1ll * ans * ksm(2, n - top) + 1) % mod);
}

```

---

## 作者：winxp_qwq (赞：3)

#### 线性基。

首先我们有引理：设 $x,y$ 为 $S$ 中的两个数，则将 $y$ 变成 $y$ $xor$ $x$ 之后的集合$S_1$, 产生的 $B$ 序列与 $S$ 产生的$B$ 序列相同。

证明：

$S$中取$x,y$对应$S_1$中取$y$ $xor$ $x$

$S$中取$x$对应$S_1$中取$x$

$S$中取$y$对应$S_1$中取$y$ $xor$ $x$，$x$

$S$中不取对应$S_1$中不取

所以我们可以搞个线性基，把大多数变成0！

然后就剩一个线性基了...会计算能产生的小于 $Q$ 的数就好啦

我们从大到小走路，由线性基的基本操作，我们可以找到走到某位之后的最大数

走到某位之后，如果该位上没有数，直接向下走

否则先走小的，判断最大值，确定是否要加上剩下所有数随便加的贡献（一个2的幂），以及接下来往哪边走

当然答案要+1

这个应该是$nlog+ log^2$的,$log=log_2(1e9)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define maxn 100009
#define mod 10086
int ji[35]={0};
int n,m;
int mi[maxn]={0};
int ans=1;
int get_max(int x,int cur) {
	if(x>=0) cur=max(cur,cur^ji[x]);
	return x<=0? cur:get_max(x-1,cur);
}
void dfs(int x,int cnt,int cur){
	if(x<0) return;
	if(ji[x]) {
		int a,b,c;
		b=cur^ji[x];
		if(b>=cur) {
			c=get_max(x-1,cur);
			if(c<m) {
				ans=(ans+mi[cnt-1])%mod;
				dfs(x-1,cnt-1,b);
			}
			else dfs(x-1,cnt-1,cur);
		}
		else {
			c=get_max(x-1,b);
			if(c<m) {
				ans=(ans+mi[cnt-1])%mod;
				dfs(x-1,cnt-1,cur);
			}
			else dfs(x-1,cnt-1,b);
		}
	}
	else dfs(x-1,cnt,cur);
}
int main(){
	int a,b,c,i,j;
	scanf("%d",&n);
	for(a=1;a<=n;a++) {
		scanf("%d",&b);
		for(c=31;c>=0;c--) {
			if((1<<c)&b) {
				if(!ji[c]) ji[c]=b;
				b^=ji[c];
			}
		}
	}
	mi[0]=1;
	for(a=1;a<=n;a++) mi[a]=mi[a-1]*2%mod;
	scanf("%d",&m);
	dfs(31,n,0);
	printf("%d\n",ans);
	return 0;
}
```

	

---

## 作者：Mihari (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/P4869)

# 题解

对于这道题，我们有一个十分强大的结论，先给出这个结论，再给出一个比较感性的证明。

>假设我们有一个集合 $A$，其中 $|A|=n$，而 $A$ 的线性基我们记作 $G$，且 $|G|=k$，那么对于 $A$ 所有子集 $S_i(1\le i\le 2^n)$ 的异或和只会有 $2^{k}$ 个值，每个值出现的次数为 $2^{n-k}$ 次。

怎么证明这个结论呢？

我们可以考虑，子集 $S_i$ 一共有 $2^n$ 的异或和，但是由 $G$ 最多可以得出 $2^k$ 个**不同**的值，而由线性基的特性，由 $G$ 得出的值和由 $A$ 得出的值都是一样的，线性基即原集合的压缩，但是我们实际上可以得到 $2^n$ 个值，那么 $2^k$ 和 $2^n$ 这巨大的差值之间，一定代表 $2^n$ 个数会有重复，去重之后就可以得到 $2^k$ 个数，说明每个数重复出现 $2^{n-k}$ 次。

~~是不是十分感性，但是似乎也只能这么说了~~

对于这道题，我们只需要看一下 $Q$ 到底是排名为多少的数，得到其排名 $rk$ 之后，直接输出 $rk\times 2^{n-k}+1$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
#define LL long long
#define ull unsigned long long
#define uint unsigned int
#define pii pair< int,int >
#define Endl putchar('\n')
// #define int long long
// #define int unsigned
// #define int unsigned long long

#define cg (c=getchar())
template<class T>inline void qread(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T qread(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
#undef cg
// template<class T,class... Args>inline void qread(T& x,Args&... args){qread(x),qread(args...);}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int MAXN=1e5;
const int MOD=10086;

template<class T>struct Basic{
    #define MAXSIZE 62
    T f[MAXSIZE+5],g[MAXSIZE+5];
    int flg,siz;
    //flg 记录插入时是否有不能放入的数
    inline void clear(){
        memset(f,0,sizeof f);flg=siz=0;
    }
    inline void insert(T num){
        fep(i,MAXSIZE,0){
            if(!(num>>i))continue;
            if(!f[i]){f[i]=num;++siz;return;}
            num^=f[i];
        }
        ++flg;
    }
    inline T queryMax(T ret){
        fep(i,MAXSIZE,0)if((ret^f[i])>ret)
            ret^=f[i];
        return ret;
    }
    inline T queryMin(){
        if(flg)return 0;
        T ret=(1ll<<MAXSIZE);
        rep(i,0,MAXSIZE)ret=Min(ret,f[i]);
    }
    inline void buildg(){
        rep(i,0,MAXSIZE)g[i]=f[i];
        rep(i,0,MAXSIZE)rep(j,0,i-1)if(g[i]&(1ll<<j))
            g[i]^=g[j];
    }
    inline T queryNum(T k){
    //must build g before use it
        if(flg)--k;
        if(k==0)return 0;
        T ret=0;
        rep(i,0,MAXSIZE)if(g[i]){
            if(k&1)ret^=g[i];
            k>>=1;
        }
        return k?-1:ret;
    }
};
Basic<LL>G;

inline int qkpow(int a,int n,const int mod){
	int ret=1;
	for(;n>0;n>>=1){
		if(n&1)ret=ret*a%mod;
		a=a*a%mod;
	}
	return ret;
}

int pos[MAXSIZE+5],cnt,n;

LL Q,ans;

signed main(){
	n=qread(1);
	rep(i,1,n)G.insert(qread(1ll));
	Q=qread(1ll);
	rep(i,0,62)if(G.f[i])pos[cnt++]=i;
	rep(i,0,cnt-1)if(Q&(1ll<<pos[i]))
		(ans|=(1<<i))%=MOD;
	printf("%lld\n",((ans%MOD*qkpow(2,n-G.siz,MOD))+1)%MOD);
    //不能直接用左移，因为会爆 long long
	return 0;
}
```



---

## 作者：P2441M (赞：1)

## 题意
给出大小为 $n$ 的可重集 $S$ 和一个数 $v$，求 $v$ 在 $S$ 的子集异或和中的排名。$1\leq n\leq 10^5$，$1\leq v,a_i\leq 10^9$。

## 题解
我们指出，对于含 $n$ 个数的可重集 $S$，考虑其线性基 $B$，则 $S$ 的所有子集异或和有 $2^{|B|}$ 种本质不同的数，每个数出现 $2^{n-|B|}$ 次。

**证明**：向 $B$ 中插入数时，有 $k$ 个数插入成功，有 $n-k$ 个数插入失败。我们只需证明，对于每个 $B$ 能表出的数 $x$，选择插入失败的数集的任意子集，都有对应方案选择插入成功的数集的子集，使得这两个子集的异或和为 $x$。设 $B$ 中将 $x$ 表出的子集为 $T$，$R=B\backslash T$，从插入失败的数集中选出的子集异或和为 $v$。首先显然 $v$ 能由 $B$ 表出，设将 $v$ 表出的子集为 $V$，我们对其情况进行分类讨论：

- 若 $V\subseteq R$，在 $B$ 中选择 $T\cup V$ 即可。
- 若 $V\subseteq T$，在 $B$ 中选择 $T\backslash V$ 即可。
- 若 $V$ 既不是 $R$ 的子集也不是 $T$ 的子集，我们结合上面两种做法，把 $V$ 拆成 $V_1\subseteq R$ 和 $V_2\subseteq T$，满足 $V_1\cup V_2=V,V_1\cap V_2=\varnothing$，在 $B$ 中选择 $V_1\cup (T\backslash V_2)$ 即可。

因此对于每个 $B$ 能表出的数 $x$，插入失败的数集的 $2^{n-|B|}$ 个子集中的任何一个都能从插入成功的数集中选择对应数集表示出 $x$。**证毕。**

接下来我们只需求出给定的数 $x$ 在 $B$ 的子集异或和中的排名 $rk$，那么 $2^{n-|B|}rk+1$ 就是它在原可重集的子集异或和中的排名了。我们遍历 $x$ 的二进制 $1$ 位就能确定它在 $B$ 中的表出方案，若 $p_i$ 在表出的子集中就令 $rk\leftarrow rk+2^i$，其中 $p_i$ 表示 $B$ 中第 $i$ 小的数。这样就能求出 $rk$ 了。时间复杂度 $\mathcal{O}(n\log{V})$。

## 代码
```cpp
const int N = 1e5 + 5, B = 31, MOD = 10086;

int add_mod(int x, int y) { int res = x + y; return res >= MOD ? res - MOD : res; }
int sub_mod(int x, int y) { int res = x - y; return res < 0 ? res + MOD : res; }

int n, m, k, rk, a[N], p[B + 5], t[B + 5];

int qpow(int a, ll b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return res;
}

void insert(int x) {
	for (int i = B; ~i; --i) {
		if (!(x >> i & 1)) continue;
		if (!p[i]) { p[i] = x; return; }
		x ^= p[i];
	}
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; ++i) cin >> x, insert(x);
    for (int i = 0; i <= B; ++i) if (p[i]) t[k++] = i;
    cin >> m;
    for (int i = 0; i < k; ++i) if (m >> t[i] & 1) rk |= 1 << i;
    rk = 1ll * rk * qpow(2, n - k) % MOD;
    cout << add_mod(rk, 1);
    return 0;
}
```

---

## 作者：__O_v_O__ (赞：1)

看到异或问题，首先想到线性基，于是先建出原序列的线性基。

乍一看，这题不是做完了吗？根据 $Q$ 的二进制位就能求出他在线性基上的排名，再加一就是序列 $B$ 上的排名......吗？

观察样例，我们发现序列 $B$ 中有重复的数字，这些数使用线性基是统计不到的。但是，样例的 $B$ 中数的重复似乎很有规律：每个数重复的次数都一样。

这启发我们思考：假设线性基大小为 $k$，那么剩下 $n-k$ 个数都能被线性基中的数异或出来，可以看成 $0$。于是对于线性基中能异或出来的每个值，都有 $2^{n-k}$ 种选 $0$ 的方法，使异或值不变，也就是说每个值都会重复 $2^{n-k}$ 次。

有了这个结论，我们只需要把 $Q$ 在线性基上的排名乘上 $2^{n-k}$ 再加一，就是 $Q$ 在 $B$ 中的排名了。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=10086;
int n,x,q,p[1001],cn,su;
void in(int x){
	for(int i=30;i>=0;i--){
		if(!(x>>i&1))continue;
		if(!p[i]){
			p[i]=x;
			break;
		}
		x^=p[i];
	}
}
int pw(int a,int b){
	int an=1;
	while(b){
		if(b&1)an=an*a%mo;
		a=a*a%mo,b>>=1;
	}
	return an;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x,in(x);
	cin>>q;
	for(int i=0;i<=30;i++){
		if(!p[i])continue;
		if(q>>i&1)su+=(1ll<<cn);
		cn++;
	}
	su%=mo;
	cout<<su*pw(2,n-cn)%mo+1;
	return 0;
} 
```

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/P4869)

题意说得很绕，简单来说就是给一个长度为 $n$ 序列，将 $2^n$ 个原序列子集的异或和进行排序，让你求出某个元素在排序后序列里的第一个出现位置。

把这些数依次插入线性基。

假如现在我们找到某个子集的异或和为 $x$。考虑还有什么别的方案使异或和也为 $x$。

我们尝试插入另一个不在线性基里面的元素参与计算，并使异或和不变。

根据线性基的定义，我们插入的这个数一定能够用线性基里面的若干个数异或得到。这些数有一些已经参与计算了，使这些数不参与计算，另外没有参与计算的数则参与计算。这样，异或和仍然为 $x$。

所以对于一个可能的异或和，无论不在线性基里的数怎么选都一定可以达到。

令线性基里有 $cnt$ 个数，那么每个异或和至少有 $2^{n-cnt}$ 中方式凑出来。

而可能的异或和共 $2^{cnt}$ 种，每种 $2^{n-cnt}$ 个，共 $2^n$ 个，恰好等于总数。因此确定了上界。

总结一下，每个元素出现次数一样，出现 $2^{n-cnt}$ 次。

分析 $Q$ 的二进制位就能得到这个元素是第几大的。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100100;
int n,q,s,p[70],a[N];
int cnt,ans;
inline void insert(int x){
    for(int i=63;i>=0;i--){
        if((x>>i)&1ll){
            if(p[i]==0){
                p[i]=x;
                cnt++;
                return;
            }
            x^=p[i];
        }
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        insert(a[i]);
    }
    cin>>q;
    s=1;
    for(int i=1;i<=n-cnt;i++) (s<<=1)%=10086;
    int sum=1;
    for(int i=0;i<=63;i++) {
        if(p[i]){
            if((q>>i)&1ll) ans|=sum;
            sum<<=1ll;
        }
    }
    ans%=10086;
    ans*=s;
    ans%=10086;
    cout<<(ans+1)%10086;
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

考虑这样一个结论：

> 所有子集异或和的数量相同，都为 $2^{n-|B|}$，其中 $|B|$ 是线性基基底的数量。

- 证明考虑我们对于所有的非基底元素都可以选或不选，我们设选出来的异或和为 $y$，显然 $y$ 可由 $x$ 表示。
- 那么线性基可以表示 $y\oplus x$ 吗？显然可以，因为线性基可以表示出 $x$，对于两者都需要的基底我们可以抵消，只有一者需要的基底可以选择。
- 所以对于任意的 $x$ 凑出来的方案不少于 $2^{n-|B|}$ 种。
- 然而线性基表示 $x$ 的方案唯一，因此对于任意的 $x$ 凑出来的方案不多于 $2^{n-|B|}$ 种。
- 证毕。

所以我们就可以把问题放在线性基上了，我们直接求出值在线性基上的排名，就可以反推出在数组中的排名。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=40;
const int Mod=10086;
LL n,B[N+5],Cnt=1,k,Ans;
inline void Ins(LL x)
{
	for(LL i=N;i>=0&&x;i--)
	{
		if(!(x&(1ll<<i)))continue;
		if(!B[i])
		{
			B[i]=x;
			return;
		}
		x^=B[i];
	}
	(Cnt<<=1)%=Mod;
}

int main()
{
	scanf("%lld",&n);
	for(LL i=1,x;i<=n;i++)
	{
		scanf("%lld",&x);
		Ins(x);
	}
	scanf("%lld",&k);
	for(LL i=0,j=1;i<=N;i++)
	{
		if(!B[i])continue;
		if(k&(1ll<<i))(Ans+=j)%=Mod;
		j<<=1;
	}
	printf("%lld\n",(Ans*Cnt+1)%Mod);
}
```

---

## 作者：Liveddd (赞：0)

这里给出一个本题的关键结论的证明，比较好理解。

考虑构造出序列 $A$ 的线性基 $P$，有 $2^{|P|}$ 个不同的异或和，每个不同的异或和出现 $2^{|A|-|P|}$ 次。

证明：

第一条根据线性基的性质得到。设异或和集合为 $B$，出现次数为 $cnt$。

考虑所有没有能够插入线性基的 $|A|-|P|$ 个元素。依次考虑，我们尝试计算当前元素 $x$ 对每个不同的异或和的贡献。$B_i\oplus x=B_j$，那么 $cnt_i\to cnt_j$。

再次根据线性基性质。我们发现这个贡献类似一个置换环的形式。即 $B-i$ 只会对唯一的 $B_j$ 产生贡献，$B_j$ 也只能通过唯一的 $B_i\oplus x$ 得到。所以得到 $\oplus x$ 会让每个异或和的出现次数 $\times 2$。

所以综上，每个不同的异或和出现 $2^{|A|-|P|}$ 次。

剩下的部分就比较简单了，先用线性基求出在不同异或和中的排名，最后乘上出现次数即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e5+10,mod=10086;
template <class T>
inline void read(T &x)
{
	x=0;int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();};
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}
int n,q,ans;
int a[N],p[32];
int power(int x,int k)
{
    int res=1;
    while(k)
    {
        if(k&1)res=res*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return res;
}
void insert(int x)
{
    for(int i=31;~i;i--)
    {
        if(!(x>>i&1))continue;
        if(!p[i])
        {
            p[i]=x;
            return;
        }
        x^=p[i];
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n;i++)read(a[i]),insert(a[i]);
    read(q);
    int rk=0,cnt=0;
    for(int i=0;i<=31;i++)
        if(p[i])
        {
            cnt++;
            if(q>>i&1)rk+=1<<cnt-1;
        }
    rk%=mod;
    printf("%d\n",(rk*power(2,n-cnt)+1)%mod);
    return 0;
}
```

---

## 作者：JPGOJCZX (赞：0)

节选自：[线性代数学习笔记（二）：线性基](https://www.luogu.com.cn/article/nhigvq6h)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18783058)

为什么没有人写简单易懂的二分答案。

先介绍一下如何在线性基中求第 $k$ 大 / 小值。我们记 $w_i$ 表示线性基中二进制位最高位为 $i$ 的那个基。

我们考虑求第 $k$ 小的困难在哪里，就是有些 $w_i$ 会有好几个二进制位相同，异或时会互相干扰，有些时候两个基异或起来会变大，有些时候两个基异或起来会变小。因此不方便统计，如果我们能把基变成如下形式：

$$
(100\dots000)_2 + x_1\\
\,\,\,(10\dots000)_2 + x_2\\
\,\,\,\,\,\,(1\dots000)_2 + x_3\\
\,\,\,\,\,\,\,\,\,\vdots\\
\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,(100)_2 + x_{n - 2}\\
\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,(10)_2 + x_{n - 1}\\
\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,(1)_2 + x_n
$$

（其中 $x_i$ 也为二进制下的数，加号表示把两个二进制数拼在一起）

我们设最后化简出了 $n$ 个基 $w_1 < w_2 < w_3 < \dots < w_{n - 1} < w_n$，此时最小的能被异或出的数就变成了 $w_1$，第二小是 $w_2$，第三小是 $w_1 \operatorname{xor} w_2$（此时的 $\operatorname{xor}$ 不会使两个基异或起来变小这），这时我们发现如果将 $k$ 二进制表示成了 $(b_0b_1b_2\dots b_{x - 1}b_x)$，那么答案就是 $\operatorname{xor}_{0 \leq i \leq x} 2^i [b_i = 1]$。

现在的问题就是要求出这样一组性质优良的基。其实我们可以发现，每个 $w_i$ 都是所有线性基中 $w_i$ 最小的，根据这个特性，可以贪心地变化这组线性基。

我们从小到大枚举先前求出的基 $w_i$，再从大到小枚举 $j > i$，此时若存在 $w_i \operatorname{xor} w_j < w_i$，就直接异或掉。我们利用类似数学归纳法的方式证明其正确性。考虑到如果 $w_i \operatorname{xor} w_j < w_j$，那么一定是 $w_j$ 的某些位与 $w_i$ 相同，如果 $w_i$ 的最高位与 $w_j$ 的这 $1$ 位都是 $1$，那么异或就将 $1$ 消掉了，否则由于 $w_i \operatorname{xor} (w_i \operatorname{xor} w_j) = w_j$，因此这个线性基并未发生变化，但是此时就只有 $w_i$ 在 $i$ 位置有值了，因此我们就构造成功了。

其实，我们可以再简化一下，如果 $j > i$ 且 $j$ 的第 $i$ 位上都有 $1$ 此时直接将 $w_j \operatorname{xor} w_i$ 就可以了。

回到这道题目，我们只需要套一个二分答案就可以了，时间复杂度为 $O(\log^2 D)$（$D$ 为值域）。

注意到这道题目是一个多重集合，由于我们知道线性基中，不存在一组数，使他们的异或和为 $0$，那么可以推出，不存在两组数，使它们的异或和相等。那么，假如有 $tot$ 个数被插入了线性基中，那么插入失败的数就有 $n - tot$ 个。由于这些数全部可以用线性基表示出来，因此可以用 $0$ 来表示。由于多少个 $0$ 异或上一个数还是这个数，因此其实每个数都出现了 $2^{n - tot}$ 次，那么将最终答案乘以 $2^{n - tot}$ 即可。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 59, MOD = 10086;
int n, m;
int w[N], cnt;
int qpow(int a, int b){
	int res = 1;
	while(b > 0){
		if(b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
struct Basis{
	void insert(int x){
		for(int i = 55; i >= 0; --i){
			if((x >> i) & 1){
				if(w[i])
					x ^= w[i];
				else {	 
					w[i] = x;
					break;
				}
			}	
		}
	}
	void build(){
		for(int i = 55; i >= 0; i--){
			if(!w[i])
				continue;
			for(int j = i + 1; j <= 55; j++){
			    if((w[j] >> i) & 1)
			    	w[j] ^= w[i];
			}
		}
		for(int i = 0; i <= 55; i++){
			if(w[i])
				w[cnt++] = w[i];
		}	
		cnt--;
	}
	int query(int x){
		int res = 0;
		for(int i = cnt; i >= 0; i--)
			if((x >> i) & 1)
				res ^= w[i];
		return res;
	}
} b;
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%lld", &x);
		b.insert(x);
	}
	b.build();
	int x;
	scanf("%lld", &x);
	int l = 0, r = (1ll << (cnt + 1)) - 1;//枚举排名
	while(l < r){
		int mid = (l + r + 1) >> 1;
		if(b.query(mid) <= x)
			l = mid;
		else
			r = mid - 1;
	}
	printf("%lld", (qpow(2, n - cnt - 1) * l + 1) % MOD);
	return 0;
}
```

---

