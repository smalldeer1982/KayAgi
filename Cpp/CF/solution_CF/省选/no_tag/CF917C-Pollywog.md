# Pollywog

## 题目描述

As we all know, Dart is some kind of creature from Upside Down world. For simplicity, we call their kind pollywogs. Dart and $ x-1 $ other pollywogs are playing a game. There are $ n $ stones in a row, numbered from $ 1 $ through $ n $ from left to right. At most $ 1 $ pollywog may be sitting on each stone at a time. Initially, the pollywogs are sitting on the first $ x $ stones (one pollywog on each stone).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917C/a0a82f5f6337291f52388ae32f43260aec71496f.png)Dart and his friends want to end up on the last $ x $ stones. At each second, the leftmost pollywog should jump to the right. A pollywog can jump at most $ k $ stones; more specifically, a pollywog can jump from stone number $ i $ to stones $ i+1,i+2,...\ i+k $ . A pollywog can't jump on an occupied stone. Jumping a distance $ i $ takes $ c_{i} $ amounts of energy from the pollywog.

Also, $ q $ stones are special Each time landing on a special stone $ p $ , takes $ w_{p} $ amounts of energy (in addition to the energy for jump) from the pollywog. $ w_{p} $ could be negative, in this case, it means the pollywog absorbs $ |w_{p}| $ amounts of energy.

Pollywogs want to spend as little energy as possible (this value could be negative).

They're just pollywogs, so they asked for your help. Tell them the total change in their energy, in case they move optimally.

## 样例 #1

### 输入

```
2 3 10 2
1 2 3
5 -10
6 1000
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 7 85 3
17 5 28 4 52 46 6
59 -76
33 -69
19 2018
```

### 输出

```
135
```

# 题解

## 作者：ysy20021208 (赞：8)

# C. Pollywog

### 题目描述

　　原题题目链接。题目大意为：有$x$只蝌蚪，在$n$个石头中的最左端的$x$个石头上，这$n$个石头是在同一直线上的。每一次只能最左边的一个蝌蚪进行跳跃，并且只能跳$1$至$k$步，跳$i$步要花费$c_i$的体力。在蝌蚪跳跃时，是不能跳到已有蝌蚪的石头上。在这$n$个石头里面有$q$个石头是特殊的石头，跳上这$q$个石头中的第$p$个要额外花费$w_p$的体力值。问当所有蝌蚪跳到最右边的$x$个石头时的最小体力值。

### 思路

　　首先，根据题意我们能知道所有的蝌蚪都一定在连续的$k$块石头上。现在进行一个小小的证明：假设这些蝌蚪不在连续的$k$块石头上，则最左边的蝌蚪在跳跃时一定会跳在最右边的蝌蚪的左边，不会使最右端点向右移动，但是因为最左边的蝌蚪跳动了，所以最左端点会向右移动，这样的话，区间就会缩短。知道当最左边的蝌蚪和最右边的蝌蚪的距离小于$k$时，才能在向右跳跃时将最右端点向右移动，又因为开始的时候所有的蝌蚪都在最左边的$x$个石头上，所以不会使区间大于$k$。

　　因此我们就可以处理出来长度为$k$的所有的情况之间的转移。我们定义一个单位元矩阵，$num[i][j]$表示状态为$i$的石头转移成为状态为$j$的石头的花费。什么是状态为$i$的石头呢？？？我们将$i$转成二进制，这样我们就得到了一个$01$串，在这个$01$串中，$0$表示这个石头上没有蝌蚪，反之$1$表示有蝌蚪。因为我们一共就只需要枚举$k$块石头，并且只有$x$只青蛙，且$k,x \le 8$，所以最多就只有$C_8^4$种情况，将二进制串离散一下就好了。这就是预处理。

　　我们得到了一个转移的邻接矩阵，我们就可以用这个矩阵来进行矩乘，先不考虑特殊的石头，所以就计算这个矩阵的$n-x$次幂就可以，$n-x$次幂的意思是，每一次都将当前$k$块石头向右进行移动一块石头，这样移动$n-x$次就是答案，但是特殊的石头要更改答案，所以我们到达一块特殊的石头，就停下来暴力就可以了。我们知道一块特殊的石头只能对$k$个转移带来影响。所以我们暴力停下来转移是可以的，时间复杂的是$O(k^2 \times q \times C_k^x)$。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define inf 1e18
#define N 10
int x,k,n,q,cnt;long long num[N];int bel[1<<10];
struct Square
{
	long long num[71][71];
	Square()
	{for(int i=1;i<=70;i++) {for(int j=1;j<=70;j++) num[i][j]=inf;num[i][i]=0;}}
	Square operator * (const Square &a) const
	{
		Square tmp;
		for(int i=1;i<=cnt;i++)
			tmp.num[i][i]=inf;
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
				for(int k=1;k<=cnt;k++)
					tmp.num[i][j]=min(tmp.num[i][j],num[i][k]+a.num[k][j]);
		return tmp;
	}
	Square operator ^ (const int &x) 
	{
		if(!x) return Square();
		Square tmp,tmp1;int times=x;
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++) tmp1.num[i][j]=num[i][j];
		while(times) {if(times&1) tmp=tmp*tmp1;times>>=1;tmp1=tmp1*tmp1;}
		return tmp;
	}
}one;
struct Stone
{int place;long long val;}stone[30];
bool calc(int tmp)
{
	int many=0;
	for(int i=1;i<=8;i++) if(tmp&(1<<(i-1))) many++;
	return many==x;
}
bool cmp(const Stone &a,const Stone &b)
{return a.place<b.place;}
int main()
{
	scanf("%d%d%d%d",&x,&k,&n,&q);
	for(int i=0;i<=(1<<k)-1;i++) if(calc(i)) bel[i]=++cnt;
	for(int i=1;i<=k;i++) scanf("%lld",&num[i]);
	for(int i=1;i<=q;i++) scanf("%d%lld",&stone[i].place,&stone[i].val);
	sort(stone+1,stone+q+1,cmp);
	for(int i=1;i<=cnt;i++) one.num[i][i]=inf;
	for(int i=1;i<=(1<<k)-1;i++)
	{
		if(!bel[i]) continue;
		if(i&1)
		{for(int j=1;j<=k;j++)
			{if(!((1<<j)&i)) one.num[bel[i]][bel[((1<<j)|i)>>1]]=num[j];}}
		else one.num[bel[i]][bel[i>>1]]=0;
	}
	int now=1;long long sum=0;Square ans;
	for(int i=1;i<=q;i++)
	{
		if(stone[i].place>n-x) {sum+=stone[i].val;continue;}
		ans=ans*(one^(stone[i].place-now)),now=stone[i].place;
		for(int j=1;j<=(1<<k)-1;j+=2)
			if(bel[j])
				for(int k=1;k<=cnt;k++)
					ans.num[k][bel[j]]+=stone[i].val;
	}
	ans=ans*(one^(n-x+1-now));
	printf("%lld",ans.num[1][1]+sum);
}
```

---

## 作者：tzc_wk (赞：7)

UPD 2021.4.9：修了个 typo

[Codeforces 题目传送门](https://codeforces.com/contest/917/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF917C)

~~这是一道 *2900 的 D1C，不过还是被我想出来了~~

~~u1s1 大概是这题用到的几个套路我都见过罢~~

首先注意到 $k$ 很小，故考虑状压 $dp$，$dp_{i,s}$ 表示当前所有 pollywog 都在编号 $[i-k+1,i]$ 范围内的石头上，并且有且仅有编号 $i-x+1,x\in s$ 的石头上有 pollywog。

转移还是比较显然的，如果 $k\in s$，那么我们必须强制让这个当前位于 $i-k+1$ 位置的 pollywog 跳 $k$ 步，否则我们可以枚举一个青蛙并让它跳到编号为 $i+1$ 的石头上，或者干脆 $i+1$ 位置上不放 pollywog，也就是说：

- $dp_{i+1,s'}\leftarrow dp_{i,s}+c_k+a_{i+1},s'=\{x+1|x\in s\land x\ne k\}\cup\{1\}(k\in s)$
- $dp_{i+1,s'}\leftarrow dp_{i,s}+c_d+a_{i+1},s'=\{x+1|x\in s\land x\ne d\}\cup\{1\}(k\notin s,d\in s)$
- $dp_{i+1,s'}\leftarrow dp_{i,s}+c_k,s'=\{x+1|x\in s\}(k\notin s)$

其中 $c_i$ 为跳 $i$ 格所需消耗的体力，$a_i$ 为 $i$ 所在的特殊格所额外消耗的体力（如果 $i$ 不是特殊格则 $a_i=0$）。

初始 $dp_{x,\{1,2,\dots,x\}}=0$，答案为 $dp_{n,\{1,2,\dots,x\}}$。

考虑优化，注意到这个 $n$ 很大但是这个转移呈规律性。故考虑矩阵优化 $dp$，我们把转移方程用矩阵的形式表示出来，即我们总能找到一个矩阵 $A$ 使得 $A\times\begin{bmatrix}dp_{i,0}\\dp_{i,1}\\\dots\\dp_{i,2^k-1}\end{bmatrix}=\begin{bmatrix}dp_{i+1,0}\\dp_{i+1,1}\\\dots\\dp_{i+1,2^k-1}\end{bmatrix}$（其中两个大小分别为 $n\times m,m\times k$ 的矩阵 $A,B$ 乘法得到的矩阵 $C$ 为 $n\times k$ 的矩阵，且 $C_{i,j}=\min\limits_{l=1}^mA_{i,l}+B_{l,j}$）。那么如果没有什么特殊格子的限制的话，直接一遍矩阵快速幂就行了。

接下来考虑有特殊格子的情况，我们按照 CF576D 的套路将所有特殊格子按坐标排个序，显然一个特殊格子 $(x,y)$ 对 $dp$ 值产生的影响就是令 $\forall 1\in S,dp_{x,S}\leftarrow dp_{x,S}+y$。故可以直接矩阵快速幂求出 $dp_x$，然后就直接在 $dp_x$ 上修改贡献即可。

这个算法的复杂度  $\omega^3p\log n$ 的，其中 $\omega=2^k$，无法通过。

考虑优化，注意到这个转移矩阵 $A$ 是不会发生变化的，故考虑借鉴 P6772 的套路，而我们矩阵快速幂求出 $dp_x$ 实质上是矩阵乘向量，单次乘法复杂度为 $\omega^2$，故考虑预处理出 $A^{2^k}$，这样可实现 $\omega^3\log n$ 预处理，$\omega^2p\log n$ 矩阵快速幂。 

可是这样还是会炸啊……

这里还有第三个套路，就是对于合法的 $dp_{i,S}$ 一定有 $|S|=x$，故合法的状态最多 $\binom{8}{4}=70$ 种，于是可以把所有合法的状态压缩成一个 $[1,70]$ 内的整数，这样矩阵大小就降到了 $70$ 了。

时间复杂度 $\omega^3\log n+\omega^2p\log n+\log p$，目前最优解 rk1

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXK=8;
const int MAXP=25;
const int MAX_SIZ=70;
const int LOG_N=28;
const ll INF=0x3f3f3f3f3f3f3f3fll;
int x,k,n,p,c[MAXK+2];pii t[MAXP+2];
int st[MAX_SIZ+5],st_n=0,id[1<<MAXK];
struct mat{
	int n,m;ll a[MAX_SIZ+5][MAX_SIZ+5];
	mat(){}
	mat(int _n,int _m){
		n=_n;m=_m;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
			a[i][j]=INF;
	}
	mat operator *(const mat &rhs){
		assert(m==rhs.n);mat res(n,rhs.m);
		for(int i=1;i<=n;i++) for(int j=1;j<=rhs.m;j++)
			for(int l=1;l<=m;l++) chkmin(res.a[i][j],a[i][l]+rhs.a[l][j]);
		return res;
	}
};
mat pw[LOG_N+2];
int main(){
	scanf("%d%d%d%d",&x,&k,&n,&p);
	for(int i=1;i<=k;i++) scanf("%d",&c[i]);
	for(int i=1;i<=p;i++) scanf("%d%d",&t[i].fi,&t[i].se);
	sort(t+1,t+p+1);
	for(int i=0;i<(1<<k);i++) if(__builtin_popcount(i)==x){
		st[++st_n]=i;id[i]=st_n;//printf("%d\n",i);
	} mat trs(st_n,st_n);
	for(int i=1;i<=st_n;i++){
		if(st[i]>>(k-1)&1){
			trs.a[id[((st[i]^(1<<(k-1)))<<1)|1]][i]=c[k];
		} else {
			for(int j=0;j<k;j++) if(st[i]>>j&1)
				trs.a[id[((st[i]^(1<<j))<<1)|1]][i]=c[j+1];
			trs.a[id[st[i]<<1]][i]=0;
		}
	}
//	for(int i=1;i<=st_n;i++) for(int j=1;j<=st_n;j++)
//		printf("%lld%c",trs.a[i][j],(j==st_n)?'\n':' ');
	pw[0]=trs;
	for(int i=1;i<=LOG_N;i++) pw[i]=pw[i-1]*pw[i-1];
	int pre=x,init_msk=0;mat cur(st_n,1);
	for(int i=0;i<x;i++) init_msk|=1<<i;
	cur.a[id[init_msk]][1]=0;
	for(int i=1;i<=p;i++){
		int dif=t[i].fi-pre;
		for(int j=LOG_N;~j;j--) if(dif>>j&1) cur=pw[j]*cur;
		for(int j=1;j<=st_n;j++) if(st[j]&1) cur.a[j][1]+=t[i].se;
		pre=t[i].fi;
	}
	int dif=n-pre;
	for(int j=LOG_N;~j;j--) if(dif>>j&1) cur=pw[j]*cur;
	printf("%lld\n",cur.a[id[init_msk]][1]);
//	for(int i=1;i<=st_n;i++) printf("%d %lld\n",st[i],cur.a[i][1]);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：4)

> F. [CF917C Pollywog](https://www.luogu.com.cn/problem/CF917C) *2900

注意到 $x$ 和 $k$ 很小而 $n$ 很大，同时所有青蛙之间的距离必然不超过 $k$（因为每次只能跳最左边的青蛙），以及这 $q$ 个奇奇怪怪的限制（联想到 “美食家” 这题），矩阵快速幂没得跑了。

预处理转移矩阵 $A$ 的幂，在断点处特殊考虑，每次矩阵快速幂时只需向量乘矩阵，时间复杂度为 $\mathcal{O}((q + |A|)|A| ^ 2\log n)$（这里 $|A|$ 表示 $A$ 的规模而不是行列式啊喂）。

这题唯一有技术含量的地方在于状态的设计。

我们有两条路，一是设 $f_{i, j}$ 表示最左边的青蛙在 $i$ 处，剩下来的青蛙状态为 $j$ 时最小体力花费。这样由于每次跳动最多会让 $i$ 增加 $k - x + 1$，所以共需要记录 $(k - x + 1)\dbinom {k - 1} {x - 1}$ 个状态，算一下当 $x = 4$，$k = 8$ 时共有 $170$ 个状态，即 $|A| = 170$，勉强可以通过。

另一种是设 $f_{i, j}$ 表示当前的 **视野** 在 $i\sim i + k - 1$ 处，以这样的视野观察到青蛙的状态为 $j$ 时的最小体力花费。具体地，$j$ 的第 $p$ 位为 $1$ 当且仅当 $i + p$ 处有青蛙。这样一来，若 $2\mid j$ 即 $i$ 处没有青蛙时，转移到 $i + 1$ 只需给 $j$ 除以 $2$ 而非跳最左边的青蛙。因此只需记录 $\dbinom k x$ 个状态，当 $x = 4$，$k = 8$ 时只有 $70$ 个状态，稳稳通过。

所以说有的时候巧妙的状态设计是很重要的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 70 + 5;
void cmin(long long &x, long long y) {x = x < y ? x : y;}
map <int, int> mp;
int x, k, n, q, sz, c[N], lab[1 << 8], msk[N];
struct mat {
	long long a[N][N];
	mat() {memset(a, 0x3f, sizeof(a));}
	mat operator * (mat x) {
		mat y;
		for(int i = 1; i <= sz; i++)
			for(int j = 1; j <= sz; j++)
				for(int k = 1; k <= sz; k++)
					cmin(y.a[i][k], a[i][j] + x.a[j][k]);
		return y;
	}
	mat operator / (mat x) {
		mat y;
		for(int i = 1; i <= sz; i++)
			for(int j = 1; j <= sz; j++)
				cmin(y.a[1][j], a[1][i] + x.a[i][j]);
		return y;
	}
} tr, pw[27], I;
struct stone {
	int p, w;
	bool operator < (const stone &v) const {return p < v.p;}
} s[N];
int main() {
	// freopen("1.in", "r", stdin);
	cin >> x >> k >> n >> q;
	for(int i = 0; i < 1 << k; i++) if(__builtin_popcount(i) == x) msk[lab[i] = ++sz] = i;
	for(int i = 1; i <= k; i++) cin >> c[i];
	for(int i = 0; i < 1 << k; i++) {
		if(!lab[i]) continue;
		if(i & 1 ^ 1) {tr.a[lab[i]][lab[i >> 1]] = 0; continue;}
		for(int p = 1; p <= k; p++) {
			if(i >> p & 1) continue;
			tr.a[lab[i]][lab[(i | 1 << p) >> 1]] = c[p];
		}
	}
	pw[0] = tr;
	for(int i = 1; 1 << i < n; i++) pw[i] = pw[i - 1] * pw[i - 1];
	for(int i = 1; i <= q; i++) cin >> s[i].p >> s[i].w, mp[s[i].p] = s[i].w;
	sort(s + 1, s + q + 1);
	if(s[q].p < n) s[++q] = {n};
	I.a[1][1] = 0;
	for(int i = 1, cur = 1; i <= q; i++) {
		int to = min(n - x + 1, s[i].p);
		for(int j = 26; ~j; j--) {
			if(cur + (1 << j) > to - k) continue;
			cur += 1 << j, I = I / pw[j];
		}
		while(cur < to) {
			mat nxt;
			memset(nxt.a, 0x3f, sizeof(nxt.a));
			for(int i = 1; i <= sz; i++) {
				int S = msk[i];
				if(S & 1 ^ 1) {cmin(nxt.a[1][lab[S >> 1]], I.a[1][i]); continue;}
				for(int p = 1; p <= k; p++) {
					if(S >> p & 1) continue;
					long long nv = I.a[1][i] + c[p] + (mp.find(cur + p) == mp.end() ? 0 : mp[cur + p]);
					cmin(nxt.a[1][lab[(S | 1 << p) >> 1]], nv);
				}
			}
			cur++, I = nxt;
		}
	}
	cout << I.a[1][1] << endl;
	return 0;
}

/*
2022/4/28
start thinking at ??:??

这题我做过.jpg.

start coding at 20:40
finish debugging at 21:10
*/
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

不怎么难的一道大套路题，用到的套路在 dp 中还是比较常见的。

# Part 2：正文

第一个观察是，$x$ 只青蛙任意时刻一定都在连续的 $k$ 块石头上。证明可以考虑归纳，即任意时刻最左边的青蛙跳走以后其在原位置向右的第一只青蛙离最右边的青蛙距离不超过 $k$，可以分其是否成为最右边第一只青蛙简单证明。

那么我们现在可以考虑用一个状态 $S$ 表示当前青蛙的分布状况。具体而言，令 $f(i,S)$ 表示所有青蛙分布在 $[i-k+1,i]$ 上，且分布状态为 $S$ 的答案。考虑如何由 $f(i,*)$ 转移到 $f(i+1,*)$。考虑枚举最左边的一只青蛙跳到哪里。分情况讨论，若第 $i-k+1$ 个石头上有青蛙则其必须向后跳走，否则考虑枚举最靠左的青蛙跳到哪里，分跳和不跳考虑，转移到对应的 $f(i+1,*)$，时间复杂度 $O(nk2^k)$。

然后考虑如何对于 $n$ 做快速转移，注意到在不考虑特殊格子的情况下，我们每一步的转移系数都是固定的，即对于一个固定的 $S$，其总是以一个相同的系数转移到固定的后继集合 $T$。这启发我们构造一个方阵 $M$，使得把 $f(i+1)$ 和 $f(i)$ 看成列向量后，总有 $f(i)\times M=f(i+1)$。预处理该方阵后，在不考虑特殊格子的情况下，我们直接对 $M$ 做一遍矩阵快速幂即可。加上特殊格子后，注意到对于一个特殊格子 $x$ 其有影响的位置只有 $[x-k+1,x]$ 个。那么我们对于特殊格子跑暴力，中间的非特殊段跑矩阵快速幂即可，时间复杂度 $O(q(2^k)^3\log n+q2^kk^2)$。

但是这个复杂度仍然无法接受。我们冷静一下，不难发现第二维状态中只有 $\mathrm{popcount}(S)=x$ 的数是有用的，在 $x=4,k=8$ 时取最大值 $70$。令其为 $s$，我们的复杂度降为 $O(qs^3\log n+qsk^2)$，可以通过。



# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
constexpr ll inf=1e18;
struct Matrix{
	vector<vector<ll>>mar;
	vector<ll>& operator[](int i){return mar[i];}
	Matrix(ll v=inf){mar.swap(*new vector<vector<ll>>(70,vector<ll>(70,inf)));rep(i,0,69)mar[i][i]=v;}
	void chk(ll &x,ll y){x=(x<y)?x:y;}
	Matrix operator *(Matrix rhs){
		Matrix res;
		rep(i,0,69)rep(k,0,69)rep(j,0,69)chk(res[i][j],(*this)[i][k]+rhs[k][j]);
		return res;
	}
	Matrix pow(int x){
		Matrix res(0),tmp=*this;
		for(;x;x>>=1,tmp=tmp*tmp)if(x&1)res=res*tmp;
		return res;
	}
};
int main(){
	int x,k,n,q;read(x,k,n,q);
	vector<int>c(k+1);
	vector<pair<int,int>>s(q);
	for(int i=1;i<=k;i++)read(c[i]);
	for(auto &[p,w]:s)read(p,w);
	sort(s.begin(),s.end());
	int full=(1<<k),cnt=-1;
	vector<int>idx(full,-1);
	rep(i,0,full-1)if(__builtin_popcount(i)==x)idx[i]=++cnt;
	
	Matrix trans;
	rep(i,0,full-1){
		if(__builtin_popcount(i)!=x)continue;
		if(i&1){rep(j,1,k)if(((i>>j)&1)^1)trans[idx[i]][idx[(i|(1<<j))>>1]]=c[j];}
		else trans[idx[i]][idx[i>>1]]=0;
	}
	
	// rep(i,0,full-1)if(idx[i]!=-1){
	// 	rep(j,0,full-1)if(idx[j]!=-1)
	// 		Debug("%lld ",trans[idx[i]][idx[j]]);
	// 	Debug("\n");
	// }
	
	int pre=1;
	Matrix ans(0);
	ll rem=0;
	for(auto [p,w]:s){
		// Debug("%d %d\n",p,w);
		if(p+x>n){rem+=w;continue;}
		ans=ans*trans.pow(p-pre);pre=p;
		rep(i,0,full-1)if((i&1)&&idx[i]!=-1)rep(l,0,cnt)ans[l][idx[i]]+=w;
		// rep(i,0,full-1)if(idx[i]!=-1){
		// 	rep(j,0,full-1)if(idx[j]!=-1)
		// 		Debug("%lld ",ans[idx[i]][idx[j]]);
		// 	Debug("\n");
		// }
	}
	ans=ans*trans.pow(n-x+1-pre);
	printf("%lld\n",ans[0][0]+rem);
	return 0;
}

```


---

## 作者：Purslane (赞：0)

# Solution

一眼矩阵快速幂优化 $\rm DP$。注意到任意时刻所有青蛙之间的距离不超过 $k-1$，所以可以状压表示青蛙的状态。

注意到在长度为 $k$ 的区间里面，所有可能的青蛙的状态只有 $\dbinom{k}{x} \le 70$，所以可以把它直接压进一个矩阵，并且使用 $(\min,+)$ 的矩阵乘法。

假设当前长度为 $k$ 的区间的左端点在 $l$。那么我们很容易算出它和左端点在 $l+1$ 之间的状态的关系。不过发现，如果 $l+1$ 到 $l+k$ 之间有神奇石头，那么转移矩阵对应的位置要修改。不过这样的 $l$ 只有 $O(qk)$ 个，所以暴力处理。

复杂度 $O(qk\dbinom{k}{x}^3)$。细节主要在于 $l$ 比较小的情况。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXS=71,MAXN=2000+10;
int x,k,n,q,s,tot,c[MAXN],lsh[MAXN],idx,id[MAXN],rev[MAXN];
struct Matrix {int v[MAXS][MAXS];};
Matrix operator *(Matrix A,Matrix B) {
	Matrix res; memset(res.v,0x3f,sizeof(res.v));
	ffor(i,1,s) ffor(j,1,s) ffor(k,1,s) res.v[i][k]=min(res.v[i][k],A.v[i][j]+B.v[j][k]);
	return res;	
}
Matrix operator ^(Matrix A,int n) {
	Matrix res; memset(res.v,0x3f,sizeof(res.v)); ffor(i,1,s) res.v[i][i]=0;
	while(n) {
		if(n&1) res=res*A;
		A=A*A,n>>=1;	
	}
	return res;
}
map<int,int> delta;
Matrix cons(int pos) {
	Matrix res; memset(res.v,0x3f,sizeof(res.v));
	ffor(i,1,s) {
		int op=rev[i];
		if(!(op&1)) {res.v[i][id[op>>1]]=0;continue ;}
		op>>=1;
		ffor(j,pos+1,pos+k) if(!(op&(1<<j-pos-1))) {
			int nop=op|(1<<j-pos-1);
			res.v[i][id[nop]]=c[j-pos];
			if(delta.count(j)) res.v[i][id[nop]]+=delta[j];
		}
	}
	return res;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>x>>k>>n>>q;
	if(n==x) return cout<<0,0;
	ffor(i,1,k) cin>>c[i];
	ffor(i,1,q) {int p,w;cin>>p>>w,delta[p]=w;ffor(j,1,k) if(p-j>0) lsh[++tot]=p-j;}
	lsh[++tot]=n-x,sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,0,(1<<k)-1) if(__builtin_popcountll(i)==x) id[i]=++idx,rev[idx]=i;
	s=idx; Matrix mul=cons(-348649614);
	Matrix ans; memset(ans.v,0x3f,sizeof(ans.v));
	ans.v[1][id[(1<<x)-1]]=0;
	ffor(i,1,tot) {
		if(lsh[i]>n-x) break ;
		ans=ans*(mul^(lsh[i]-lsh[i-1]-1))*cons(lsh[i]);	
	}
	cout<<ans.v[1][id[(1<<x)-1]];
	return 0;
}
//青蛙不簡單！！！青蛙青蛙青蛙青蛙，切 2900 的青蛙。 
```

花絮：为啥做这道题呢？因为这道题题目里面有 $\Huge \color{green}青蛙$。呱呱呱。

---

## 作者：大菜鸡fks (赞：0)

矩阵乘法优化dp

因为每次最多跳k格，并且跳的都是最左边的，所以可以用2^k的状态来表示相对位置。

设dp[i][j]为左端点在i，右边的状态为j的最优方案值

可以发现转移能用矩阵优化。

对于特殊的石子，因为q特别小，所以分段转移。细节较多

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int S=71,INF=1e18;
int cnt;
struct matrix{
	int mat[S][S];
	matrix() {
        for (int i=1;i<=cnt;i++){
            for (int j=1;j<=cnt;j++) {
				mat[i][j]=INF;
			}
            mat[i][i]=0;
        }
    }
	inline void New(){
		for (int i=1;i<=cnt;i++) mat[i][i]=INF;
	}
};
inline matrix operator *(matrix A,matrix B){
	matrix C; C.New(); 
	for (int i=1;i<=cnt;i++){
		for (int j=1;j<=cnt;j++){
			for (int k=1;k<=cnt;k++){
				C.mat[i][j]=min(C.mat[i][j],A.mat[i][k]+B.mat[k][j]);
			}
		}
	}
	return C;
}
inline matrix operator ^(matrix A,int k){
	matrix B;
	if (!k) return matrix();
	for (;k;k>>=1,A=A*A) if (k&1) B=B*A;
	return B;
}
inline int lowbit(int x){
	return x&(-x);
}
inline int calc(int x){
	int cnt=0;
	for (;x;x-=lowbit(x)) cnt++;
	return cnt;
}
struct node{
	int x,y;
}a[30];
int c[10],x,k,n,q,g[1<<8];
inline bool cmp(node A,node B){
	return A.x<B.x;
}
inline void init(){
	x=read(); k=read(); n=read(); q=read();
	for (int i=1;i<=k;i++) {
		c[i]=read();
	}
	for (int i=1;i<=q;i++){
		a[i]=(node){read(),read()};
	}
}
inline void solve(){
	for (int i=0;i<(1<<k);i++){
		if (calc(i)==x) g[i]=++cnt;
	}
	matrix A; A.New();
	for (int i=1;i<(1<<k);i++){
		if (g[i]){
			if (i&1){
				for (int j=1;j<=k;j++){
					if ((1<<j)&i) continue;
					A.mat[g[i]][g[(i|(1<<j))>>1]]=c[j];
				}
			}else{
				A.mat[g[i]][g[i>>1]]=0;
			}
		}
	}
	sort(a+1,a+1+q,cmp);
	matrix ans; int sum=0,las=1;
	for (int i=1;i<=q;i++){
		if (a[i].x>n-x){
			sum+=a[i].y;
			continue;
		}
		ans=ans*(A^(a[i].x-las));
		las=a[i].x;
		for (int j=1;j<(1<<k);j+=2){
			if (g[j]){
				for (int kk=1;kk<=cnt;kk++){
					ans.mat[kk][g[j]]+=a[i].y;
				}
			}
		}
	}
	ans=ans*(A^(n-x+1-las));
	writeln(ans.mat[1][1]+sum);
}
signed main(){
	init(); solve();
	return 0;
}
```

---

## 作者：xunzhen (赞：0)

这道题我一看就知道是状压DP，但这题$N$比较大，我不知道怎么快速转移，所以只能去搜其他人的题解，结果百度上没有发现一个人写了这题题解，于是直接在CF上找了一个AC了的代码自己去理解...

不难发现，由于青蛙最多可以跳$k$个石头，所以在任意时刻所有$x$只青蛙都在连续一段长度为$k$的区间里，所以这个长度为$k$的区间最多只有$s (s \leq 70)$种情况，于是我们就可以构造出一个$s \times s$的矩阵来转移状态。

然后，对于特殊的石头，我们可以另外考虑。因为$q$较小，所以我们可以每次矩阵快速转移到特殊石头的位置，加上特殊石头对答案的贡献，然后继续转移即可。

这题~~恶心的~~细节较多，请仔细阅读代码

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define debug(...) printf(__VA_ARGS__), fflush(stdout);

typedef long long LL;
typedef pair<int, int> pii;

const int MAX_STATE = 71;
const LL inf = 1e18;

pii p[30];

int c[10], f[1 << 8];

int x, k, n, q, cnt;

struct matrix {

	LL A[MAX_STATE][MAX_STATE];

	matrix() {
		for (int i = 1; i < MAX_STATE; i++) {
			for (int j = 1; j < MAX_STATE; j++)
				A[i][j] = inf;
			A[i][i] = 0;
		}
	}

	matrix operator * (matrix B) {
		matrix r;
		for (int i = 1; i <= cnt; i++)
			r.A[i][i] = inf;
		for (int i = 1; i <= cnt; i++)
			for (int j = 1; j <= cnt; j++)
				for (int k = 1; k <= cnt; k++)
					r.A[i][j] = min(r.A[i][j], A[i][k] + B.A[k][j]);
		return r;
	}

	matrix operator ^ (int y) {
		matrix x, r;
		for (int i = 1; i <= cnt; i++)
			for (int j = 1; j <= cnt; j++)
				x.A[i][j] = A[i][j];
		if (!y) return matrix();
		while (y) {
			if (y & 1) r = r * x;
			x = x * x; y >>= 1;
		}
		return r;
	}

};

int calc(int x) {
	int sum = 0;
	while (x) {
		if (x & 1) sum++;
		x >>= 1;
	}
	return sum;
}

int main() {
#ifdef xunzhen
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif

	cin >> x >> k >> n >> q;
	for (int i = 1; i <= k; i++)
		scanf("%d", &c[i]);
	for (int i = 1; i <= q; i++)
		scanf("%d%d", &p[i].first, &p[i].second);

	for (int i = 0; i < (1 << k); i++)
		if (calc(i) == x) f[i] = ++cnt;

	matrix R;
	for (int i = 1; i <= cnt; i++)
		R.A[i][i] = inf;

	for (int i = 1; i < (1 << k); i++) {
		if (!f[i]) continue;
		if (i & 1) {
			for (int j = 1; j <= k; j++) {
				if ((1 << j) & i) continue;
				R.A[f[i]][f[((1 << j) | i) >> 1]] = c[j];
			}
		}else R.A[f[i]][f[i >> 1]] = 0;
	}

	sort(p + 1, p + q + 1);

	matrix ans;
	LL sum = 0; int now = 1;
	for (int i = 1; i <= q; i++) {
		if (p[i].first > n - x) {
			sum += p[i].second;
			continue;
		}
		ans = ans * (R ^ (p[i].first - now));
		now = p[i].first;
		for (int j = 1; j < (1 << k); j += 2)
			if (f[j])
				for (int k = 1; k <= cnt; k++)
					ans.A[k][f[j]] += p[i].second;
	}
	ans = ans * (R ^ (n - x + 1 - now));

	cout << ans.A[1][1] + sum << endl;

	return 0;
}
```

---

