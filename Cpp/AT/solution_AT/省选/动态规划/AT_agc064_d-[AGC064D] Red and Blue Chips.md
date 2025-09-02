# [AGC064D] Red and Blue Chips

## 题目描述

你有 $N$ 个字符串，初始情况下每个字符串只有一个字符，是 $\texttt{R}$ 或  $\texttt{B}$，保证第 $N$ 个字符串是 $\texttt{B}$。

你需要对每个 $i=1,2,\cdots ,n-1$ 执行以下操作：

- 选择一个整数 $j$ 使得 $i< j\le n$，且第 $j$ 个字符串的最后一个字符是 $\texttt{B}$，然后把第 $i$ 个字符串整体拼接在第 $j$ 个字符串的**前面**。

问最后可以得到多少种本质不同的第 $N$ 个字符串，对 $998244353$ 取模。

## 样例 #1

### 输入

```
4
RBRB```

### 输出

```
2```

## 样例 #2

### 输入

```
20
RRBRRRBBRBBBBRBRBRBB```

### 输出

```
92378```

# 题解

## 作者：stntn (赞：10)

upd：修了几个 typo。

遇到此类求本质不同结果的题，先考虑如何 check 一个结果序列合法。

首先显然的是 `R` 和 `B` 的数量必须等于原串的数量，并且末尾字符为 `B`。

然后可以发现，在最后一个 `B` 前面的若干个 `R` 最终只能处于序列最前端。接着加入下一个 `B`，序列会被划分为两段，下一段 `R` 可以选择这两段中任意一段。相当于这两段各自的最前端 `R` 数量之和要大于等于这段 `R` 的数量。之后的情况同理。

考虑如何快速 check 一个序列。考虑我们手里有一个计数器 $x$，初始为结果序列的左边第一段 `R` 的长度。

从右到左扫描原序列，每当扫描到一段极长的 `R` 时我们会做如下操作：

- 从计数器中减去当前 `R` 的长度，若结果为负数则不合法。

- （如果还存在的话）从结果序列中选一段未被选择的 `R`，将 $x$ 增加其长度。

可以发现第二个操作我们应该贪心地做，即每次选最长的合法段。

考虑 DP，我们按照由大到小地顺序加入 `R` 段，使得每次加入后仍然合法（即当前 `R` 总长大于等于应该减去的总长），可以发现这样加入的方案与合法结果序列形成双射。

令 $f_{i,j}$ 表示除了开头段已经加入 $i$ 段，共加入 $j$ 个的方案数，转移是平凡的，复杂度 $O(n^3\ln n)$。

注意第一段不一定大于等于之后加入的段，所以枚举一下第一段的长度即可。

```
#include<bits/stdc++.h>
#define N 310
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
const int mod=998244353;
inline int add(const int &x,const int &y){return x+y>=mod?x+y-mod:x+y;}
inline int dec(const int &x,const int &y){return x-y<0?x+mod-y:x-y;}
inline int qpow(int a,int b=mod-2)
{
	int res=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) res=1ll*a*res%mod;
	return res;
}
int n,cc,fac[N],fav[N],sum[N],f[N][N];
char s[N];
inline int C(int n,int m){return n<0||m<0||n<m?0:1ll*fac[n]*fav[m]%mod*fav[n-m]%mod;}
signed main()
{
	read(n);scanf("%s",s+1);fac[0]=1;
	rep(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
	fav[n]=qpow(fac[n]);
	per(i,n-1,0) fav[i]=1ll*fav[i+1]*(i+1)%mod;
	per(i,n,1)
	{
		if(s[i]=='B') cc++;
		else sum[cc]++;
	}
	rep(i,1,cc) sum[i]+=sum[i-1];
	rep(i,sum[1],sum[cc]) f[0][i]=1;
	per(i,sum[cc],0) per(j,cc-2,0) rep(k,sum[j+1],sum[cc]-i) rep(x,1,min(cc-1-j,i?(sum[cc]-k)/i:n))
	{
		if(sum[j+x+1]<=k+x*i) f[j+x][k+x*i]=add(f[j+x][k+x*i],1ll*f[j][k]*C(j+x,x)%mod);
		else break;
	}
	printf("%d\n",f[cc-1][sum[cc]]);
	return 0;
}
```

---

## 作者：Little09 (赞：7)

考虑判定一个 RB 序列是否可以被得到。从后往前考虑，如果当前位置是 R，它上面放的一定只能是单独的一个 R，所以需要从序列前面拿掉一个 R；如果是 B 的话，它上面放的可以是一堆，但最后一个是 B，所以可以将序列从某个 B 后面分裂。然后如果某次在 R 的时候拿不出 R 就不合法了，否则合法。

这个过程显然可以贪心，对于从每个 B 后面分裂的方案会带来一定量的可以拿的 R，所以我们一定会按照这个值排序然后从大到小搞。还需要注意开头的一段连续的 R 是不参与排序的，它们一开始就是可以取出的。

所以我们把每个 B 前面的 R 连续段个数依次记为 $c_1,...,c_k$，那初始序列相当于给定了一个数列 $d_1,...d_k$，需要满足：

- 将 $c_2,...,c_k$ 从大到小排序后，对于任意 $1\le x\le k$，满足 $\sum_{i=1}^xc_i\ge \sum_{i=1}^xd_i$。

符合条件的序列 $c$ 就是我们需要计数的，那么就转化成一个简单的计数问题，考虑 DP。从大到小考虑，维护当前算了几个数，最小的数是多少，选的数的和是多少，容易实现 $O(n^3\log n)$ 或 $O(n^3)$ 计数。第一个位置由于不参与排序，需要处理一下。

```cpp
//jc是阶乘，inv是阶乘的逆元
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	init();
	cin >> n;
	rep(i,1,n) cin >> a[i];
	int s=0,num=0;
	per(i,n,1)
	{
		if (a[i]=='B') c[++cnt]=0,num++;
		else c[cnt]++,s++;
	}
	rep(i,1,cnt) c[i]+=c[i-1];
	rep(i,c[1],s) dp[s+1][1][i]=jc[num-1];
	per(i,s,0)
	{
		rep(j,1,num)
		{
			rep(k,c[j],s)
			{
				for (int o=0;k+o*i<=s&&j+o<=num;o++)
				{
					if (k+o*i<c[j+o]) break;
					(dp[i][j+o][k+o*i]+=dp[i+1][j][k]*inv[o])%=mod;
				}
			}
		}
	}
	cout << dp[0][num][s];
	return 0;
}
```


---

## 作者：dead_X (赞：7)

## 思路
记串中 B 的个数为 $m$。

考虑用 B 当做分隔符来考察每一对相邻 B 之间的 R 个数。

尝试刻画一次操作中 B 的相对位置对应的排列，显然每个 $p_1=m$ 的排列 $p$ 都是可以被取到的，构造方法就是把 $x$ 贴到 $pre(x)$ 后面。

然后再考虑每个 R 可以被丢到哪个位置，假设这个 R 在第 $x$ 个 B 之后，那么我们可以发现此时所有 $nxt(y)>x$ 的位置都仍然可以被贴。

于是问题转化为了一个非负整数序列 $a$ 是好的，当且仅当：

- $|a|=m$，$\sum a_i=n-m$。
- 将 $[a_1,\cdots,a_{m-1}]$ 排序后对 $a$ 做前缀和，记结果为 $b$。
- 统计第 $1,2,\cdots,m$ 个 B 之前的 R 数量，记结果为 $c$。
- $b_i\leq c_i$。

直接 DP 即可，时间复杂度 $O(n^3\log n)$。
## 代码
```cpp
// Problem: D - Red and Blue Chips
// Contest: AtCoder - AtCoder Grand Contest 064
// URL: https://atcoder.jp/contests/agc064/tasks/agc064_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
mt19937_64 haitang(0520);
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
int fac[1003],ifac[1003];
int f[303][303][303];
int a[1003];
char s[1003];
signed main()
{
	fac[0]=ifac[0]=1;
	for(int i=1; i<=1000; ++i)
		fac[i]=1ll*fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2);
	int n=read(),m=0;
	scanf("%s",s+1);
	for(int i=1,z=0; i<=n; ++i)
		if(s[i]=='R') ++z;
		else a[++m]=z;
	for(int i=0; i<m; ++i) f[0][i][0]=ifac[i];
	for(int i=1; i<=n-m; ++i)
	{
		memcpy(f[i],f[i-1],sizeof(f[i-1]));
		for(int k=1; k<m; ++k)
			for(int l=i; l<=n-m; ++l)
			{
				int kk=k,ll=l,d=0;
				while(kk>=1&&ll>=i)
				{
					if(a[kk]<ll) break;
					--kk,ll-=i,++d;
					f[i][k][l]=(f[i][k][l]+
					1ll*f[i-1][kk][ll]*ifac[d])%p;
				}
			}
	}
	int ans=0;
	for(int i=0; i<=n-m; ++i) ans=(ans+1ll*f[n-m][m-1][i]*fac[m-1])%p;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Eraine (赞：3)

编号：AT_agc064_d  
tag：DP  
难度：$\color{red}{2804}$

有点帅的计数题，但还是有些典了。但是我是唐氏竟然一时半会儿想不出来。

若将移动 $S_i$ 到 $S_j$ 看做是连 $(i,j)$ 的边，则最终连接状态必然是一棵树，且不同的移动方式所对应的树形态不同。

![](https://cdn.luogu.com.cn/upload/image_hosting/hysjnyi1.png)

如上图。将每个元素下标用图上的数字表示。涂红的节点表示 $s_i=\texttt{R}$，涂蓝的节点表示 $s_i=\texttt{B}$。注意到一棵树（考虑左右兄弟顺序）要成为合法的 $\texttt{RB}$ 序列生成树，需要保证下列条件：

- $par_i\lt i$（即这棵树是大根堆）
- 对于兄弟 $v_i,v_j$ 满足 $i\lt j$，$v_i\lt v_j$
- $s_{par_i}=\texttt{B}$

发现对于任意一颗合法的生成树，最终答案是其后序遍历。既然题目要问答案序列的种类，可以注意到只和由 $\texttt{B}$ 切割成的 $sum_{\texttt{B}}$ 段的每段 $\texttt{R}$ 长度有关。我们不妨考虑倒序构建树。发现每出现一个 $\texttt{B}$ 会多出现一个空段（除了 $n$ 否则不会成为新的结尾段），每出现一个 $\texttt{R}$，会在目前的所有出现段中选取一个长度 $+1$。注意到在前 $sum_{\texttt{B}}-1$ 段中，每一段的数量大小和其顺序无关，但是最后形成的一段一定不超过原 $\texttt{RB}$ 序列由 $\texttt{B}$ 切割成的第一段长度，同理最后两段不会超过原 $\texttt{RB}$ 序列由 $\texttt{B}$ 切割成的前两段长度，……由于顺序随机，那么如果将答案序列前 $sum_{\texttt{B}}-1$ 段升序排列 $p$ 和原 $\texttt{RB}$ 序列前 $sum_{\texttt{B}}-1$ 段升序排列 $q$ 满足 $\forall i\in[1,sum_{\texttt{B}}),\sum_{1\le j\le i}p_i\le\sum_{1\le j\le i}q_i$，那么即是一个合法的序列。这提示我们可以转换成求其升序排列方案数。那么注意到可能出现相同元素，所以相同元素同时进行转移。在 DP 的过程中需要维护如下状态：长度和；该段长度；段数。共三维，状态数是 $\Theta(n^3)$ 的。转移需要枚举上一段长度和同样长度连续段绑在一起的数量，均摊 $\Theta(n\ln n)$。上一段长度可以前缀和优化掉，故转移可以优化成 $\Theta(\ln n)$。

$\Theta(n^3\ln n)$。

[submission](https://atcoder.jp/contests/agc064/submissions/57864959)

若有疑问或错误请指出，虚心接受您的意见。

upd:2025.4.25 修改了一处笔误

---

## 作者：_Cheems (赞：2)

将原序列视为 $m$ 个形如：一个 B 前面紧跟着一段极大 R。不妨从左往右依次给予每个 B 编号，不难发现结果序列中 B 的编号是任意排列 $P$ 满足 $P_m=m$。再考虑 R，对于第 $i$ 个 B 前面跟着的每个 R，都可以选择接在第 $j\ge i$ 个 B 前面。

考察结果序列是否可构造，首先不用考虑第 $m$ 个 B，因为前面的 B 都满足了它肯定也满足。然后要给前 $m-1$ 个 B 编号，显然有贪心：优先给跟着的 R 数量较大者较大的编号。于是得出判定条件：

* 记 $a_1\dots a_{m-1}$ 为原序列前 $i$ 段连续 R 的数量、$b_1\dots b_{m-1}$ 则是结果序列的。
* 合法当且仅当 $\forall i,b_i\le a_i$。

直接按数值从小到大 dp，记 $f_{i,j,k}$ 为考虑 $1\dots i$ 的数值，总和为 $j$，选了 $k$ 个的权值和。权值为每种值次数的阶乘逆元之积，用于计算多重排列。答案枚举第 $m$ 个 B 前面接了几个 R 即可。

调和级数，复杂度 $O(n^3\log n)$。

---

## 作者：SunsetGlow95 (赞：2)

写这篇单纯是因为我读到的这题题解没有一篇讲的是俺听得懂的话（捂脸）。感觉是独立很难做的题目。

## 简述题意

有 $n$ 个只含 `RB` 的字符串 $S_i$，一开始每个字符串长度均为 $1$，保证 $S_n$ 是 `B`。对 $i$ 从 $1$ 到 $n-1$ 依次做如下操作：选择一个 $j$ 满足 $i<j\le n$ 且 $S_j$ 末字符为 `B`，然后将 $S_i$ 拼接到 $S_j$ 前面。问可以生成的 $S_n$ 个数 $\bmod\ 998244353$。$2\le n\le 300$。

## 分析

令输入的串为 $S$，生成的串为 $T$，经典的想法是为 $T$ 设计一个判定算法。

显然 $T_n$ 是 `B`。从 $S_1$ 到 $S_{n-1}$ 考虑会感觉每一位都没有一个位置，不如从 $S_{n-1}$ 到 $S_1$，依次考虑填入 $T$。

发现 $S_n$ 之前的一串极长的 `R` 必然成为 $T$ 的一个前缀，因为它们是最后放到 $S_n$ 开头的。然后将会扫到一个 `B`，假设它是 $S_b$，它会填到上述 `R` 前缀的后面、$T_n$ 的前面的某个位置。接下来扫到的一串极长的 `R`，在原来的过程中只有两种选择：放到 $S_b$ 前面或放到 $S_n$ 前面。如果选择的是放到 $S_n$ 前面，那么应该恰好在移动后的 $S_b$ 后面，因为它恰好在 $S_b$ 缀到 $S_n$ 前缀过去，$T$ 形如：

```plain
RRRRR....BRRRR.............B
```

如果选择的是放到 $S_b$ 的最前面，那应该是紧跟在上一次 `R` 的后面，而要在其它缀到 $S_b$ 前面的串之前，$T$ 形如：

```plain
RRR RRRR........B..........B
```

再下一个 `B`（以下为区分标为 `b`），可以填到两个空段的某一处，如：

```plain
RRRRR....b...BRRRRR....b...B
```

再然后的 `R`，类比上述推演可知，必然在以下之一：

- `b` 前面空段的最前；
- 紧随 `b` 之后；
- 剩下那个空段的最前，表示和 `b` 的去向不同。

归纳一下，相当于是 `B` 会插到某个位置，然后 `R` 可以插到最前，也可以紧随任意除了 $S_n$ 以外的 `B` 之后。就像是，每插入一个 `B`，就会把 $T$ 中它后面的一段连续的 `R` 给启用，表示可以往里面填 `R`。如果不能填 `R` 就是方案不合法。

这样的判定还不是 DFA，不够确定。考虑填 `B`，肯定希望接下来能容纳 `R` 的能力尽量强，所以除了第一段 `R` 被动地启用，后面都肯定会挑 $T$ 中一段最长的 `R` 来启用。

那就可以进一步形式化：假设 $S$ 中 `B` 有 $m$ 个，从右往左第 $i+1$ 个 `B` 右边的 `R` 有 $s_i$ 个，并令 $s_m=n-m$；假设把 $T$ 中除了第一段 `R` 以外的 `R` 段从长到短排序，令其长度前缀和为 $t_i$。则判定条件为：$\forall 1\le i\le m,t_i\ge s_i$。

把所有合法的 $t_1$ 都启用，后面的从长到短往里面填，最后要乘上多重集排列，转移有一个阶乘逆的系数，这是显然的分组背包，不讲了。复杂度看起来是 $O(n^3\log n)$，但是不太知道官方题解怎么能分析到 $O(n^3)$，可能是写法不太一样。

## 代码

你都会了，还要代码干嘛，套路卷积而已。

## 思考

这个题的性质太深奥了。上述理解有点暴力，但还是可以做出题的。其他题解有提到树形结构，也许可以帮助你获得更好的直觉，只是我还没悟到/ll。

---

## 作者：FstAutoMaton (赞：2)

## [[AGC064D] Red and Blue Chips](https://www.luogu.com.cn/problem/AT_agc064_d)

神仙找性质数数。感觉题解有些地方没太写清楚，这里稍微补充一些。

考虑校验答案序列的合法性。首先 ```R``` 和 ```B``` 的数量显然要和原串一致，接着考虑反向进行操作，在原串中从后往前遍历，维护当前字符串集合。

从第 $n$ 位开始，如果第 $s_i=$ ```R```，那么直接将当前的所有字符串中找到任意一个开头为 ```R``` 的字符串将开头的字符移除（如果找不到 ```R``` 开头的串就说明该答案串不合法）。否则如果 $s_i=$ ```B```，那么可以将当前的字符串集合中在原串中的任意一个串分成**两个以 ```B``` 结尾的分裂前的串的前缀和后缀**，塞入当前的字符串集合中。

> 考虑模拟对原串为 ```RBBRRB```，答案串为 ```RRBRBB``` 进行如上操作。
>
> $i=6$ 时，原串分裂成 ```RRBRB``` 和 ```B```，由于原串以 ```B``` 为后缀，删除 ```B```。
>
> $i=5$ 时，$s_i=$ ```R```，将 ```RRBRB``` 开头的 ```R``` 删去，此时字符串为 ```RBRB```。
>
> $i=4$ 时，$s_i=$ ```R```，将一个 ```RBRB``` 最开头的 ```R``` 删去，答案串变为 ```BRB```
>
> $i=3$ 时，$s_i=$ ```B```，对字符串分裂成 ```B``` 和 ```RB```，由于原串以 ```RB``` 为后缀，所以删除 ```RB``` 中的 ```B```，变为 ```R```。
>
> $i=2$ 时，$s_i=$ ```B```，删除 ```B```，此时还剩下 ```RB```。
>
> $i=1$ 时，$s_i=$ ```R```，删除字符串 ```R``` 此时，集合为空，说明该答案串合法。

分析一下我们操作的过程，每次遇到 ```R``` 的操作显然删除任意一个开头的 ```R``` 都是一样的，但遇到 ```B``` 的时候分裂的方式会影响最终的结果。由于可以任意进行分裂，而不合法情况是由开头的 ```R``` 决定的，所以分裂时会选择可以分裂出的 ```R``` 最多的方案。

令 $a_i$ 表示答案串中第 $i$ 个极长 ```R``` 连续段的长度，$k$ 表示答案串中有多少极长```R``` 连续段，$b_i$ 表示**将原串 $\operatorname{reverse}$ 后第 $i$ 个极长 ```R``` 连续段的长度**，$v$ 表示原串中的极长 ```R``` 连续段个数。于是在同满足如下条件时合法：

1. $\sum_{i=1}^{k} a_i=\sum_{i=1}^{v} b_i$

2. $a_1\ge b_1$

3. 将 $a_{2},a_3,a_4 \cdots a_k$ 从大到小排序，有：$\forall x,\sum_{i=1}^{x}a_i\ge \sum_{i=1}^{x} b_i$。

这个式子当时想了很久才想明白，所以稍微解释一下。

要从大到小排序是因为每次分裂时可以选择让 ```R``` 的数量尽量的多，但是由于开头的一段最开始就可以取出，所以 $a_1$ 不参与排序。$\forall x,\sum_{i=1}^{x}a_i\ge \sum_{i=1}^{x} b_i$ 是因为每次分裂后开头的 ```R``` 数量只有 $\sum_{i=1}^{x}a_i$ 个，而此时在操作中已经删除了 $\sum_{i=1}^{x}b_i$ 个 ```R```，所以如果答案序列要合法必须要满足当前所有分裂出来的字符串开头的 ```R``` 的数量足够进行操作。

那么现在问题就转化为了对 $a$ 数组计数（下文中的 $a$ 数组如果没有特殊说明指的都是去掉 $a_1$ 后的数组）。

首先对排序后的 $a$ 数组计数是简单的。但是因为可能会有相同的值，所以不能直接乘上 $(k-1)!$。假设去掉 $a_1$ 后有 $m$ 种数，第 $i$ 种数有 $c_i$ 个，那么这个排序后序列所对应的方案数为：

$$\dfrac{(k-1)!}{\prod_{i=1}^m(c_i!)}$$

由于 $(k-1)!$ 是固定，所以考虑对系数进行计算。

设 $f_{i,j,k}$ 表示当前最小值为 $i$，已经确定了 $j$ 个数，所有数的和为 $k$，所有满足该条件的系数之和。

拓扑序为 $i$ 从大到小（因为 $a$ 要从大到小排序）。

假设原串中 ```R``` 的个数为 $cnt$，有转移：

$$f_{i,j+l,k+l\times i}=\sum_{l=1,l\times i+k\le cnt}^{n-j} f_{i+1,j,k}\times \frac{1}{l!}$$

其中在从小到大枚举 $l$ 的过程中如果出现 $l\times i+k<a_{l+j}$ 就要退出循环不再进行转移（具体实现可以参考代码）。

这样做看起来时间复杂度是 $\operatorname{O}(n^4)$ 的，但是 $j,k$ 只有 $n^2$ 对，而 $i,l$ 的对数大概为 $\sum_{i=1}^{n}\frac{n}{i}$，这是调和级数，所以只有 $n\ln n$ 对。

因此总时间复杂度为 $\operatorname{O}(n^3 \ln n)$。

[code](https://atcoder.jp/contests/agc064/submissions/58579523)

---

