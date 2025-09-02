# 【MX-X3-T7】「RiOI-4」Re：End of a Dream

## 题目背景

原题链接：<https://oier.team/problems/X3H>。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/dwohziu8.png)

（图片来自 phigros 曲绘，侵删。）

还是来谈点现实的吧。

身边的同学 NOI 拿了 Ag，APIO 捧了杯，省选啥的也比小 $\iiint$ 好。小 $\iiint$ 说，他的时间花在游戏上了。可看看隔壁提前招进高中的，florr 号里都有 Super Ant Egg 了。小 $\iiint$ 说，他网不好，实力发挥不出来。可再看隔壁 i wanna 大神，都开始速通 i wanna be the guy 了。小 $\iiint$ 争道，他也没打多久游戏，只是在专心文化课。但是成绩一拉出来，成了信竞班垫底。小 $\iiint$ 又说，可能是时间花在社交上了吧。大家都觉得他很幽默，因为他在班里一个朋友都没有。

小 $\iiint$ 不明白为什么会这样。

今年对于小 $\iiint$ 来说，可能就是他 OI 生涯的最后一年了。一年太短，能补救多少？能挽回多少？当年他刚学 OI 时，就暗暗地下定决心，要成为大家口中的“神犇”。三年过去，前途仍是一片昏暗。

这或许就是，$\color{#CD0000}\overset{\text{End of a Dream}}{\text{梦\ 的\ 终\ 结}}$。

也许，**梦是反着的吧。**

……

但是这里是梦熊周赛题目，不是出题人拿来写批话的地方，所以小 $\iiint$ 需要你做一道计数题。

## 题目描述

给定 $n,q$。现有一个初始为 $0$ 的整数 $m$。你需要支持以下操作：

- `0 x`：将 $m$ 加上 $2^x$。
- `1 x`：将 $m$ 减去 $2^x$。若 $m<2^x$，则忽略此操作。
- `2`：查询有多少长度为 $n$、每个数都在 $1\sim m$ 中的严格递增正整数序列，使得其前缀异或和与后缀异或和均严格递增。答案对 $998\,244\,353$ 取模。

其中，一个序列 $a_1,a_2,\cdots,a_n$ 的**前缀异或和**是指序列 $s_1,s_2,\cdots,s_n$，满足 $s_i=\begin{cases}a_1&i=1\\a_{i}\oplus s_{i-1}&i\ge2\end{cases}$，而其**后缀异或和**是指序列 $t_1,t_2,\cdots,t_n$，满足 $t_i=\begin{cases}a_n&i=1\\a_{n-i+1}\oplus t_{i-1}&i\ge2\end{cases}$，其中 $x\oplus y$ 表示 $x$ 与 $y$ 的按位异或。

## 说明/提示

**【样例解释 #1】**

查询时 $m=7$，满足要求的序列为 $\{1,2,4\}$ 和 $\{1,3,5\}$，可以证明不存在其他解。

注意，序列 $\{1,3,1\}$ 是不满足要求的，尽管其前、后缀异或和均为严格递增数列 $\{1,2,3\}$，该序列本身并不满足严格递增的限制。

**【数据范围】**

**本题开启捆绑测试。**

|子任务|分数|$n\le$|$q\le$|$x\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$5$|$5$|$10$|$10$||
|$2$|$10$|$10^3$|$10^3$|$10^3$||
|$3$|$11$|$10^3$|$2\times10^5$|$10^5$|AB|
|$4$|$14$|$10^5$|$2\times10^5$|$10^5$|AB|
|$5$|$16$|$10^7$|$10^2$|$10^7$|B|
|$6$|$19$|$10^7$|$2\times10^5$|$10^7$|B|
|$7$|$25$|$10^7$|$2\times10^5$|$10^7$||

特殊性质 A：仅有最后一次操作为 `2` 操作。  
特殊性质 B：不包含 `1` 操作。

对于 $100\%$ 的数据，$3\le n\le 10^7$，$1\le q\le 2\times10^5$，$0\le x\le 10^7$。

## 样例 #1

### 输入

```
3 4
0 0
0 1
0 2
2```

### 输出

```
2```

## 样例 #2

### 输入

```
20 15
0 1
0 2
0 21
0 5
2
0 15
1 18
0 7
0 8
0 25
2
1 22
0 12
0 13
2```

### 输出

```
313288290
39181640
134388812```

# 题解

## 作者：Register_int (赞：13)

异或就是个很烦的东西，所以第一步是把异或处理掉。来拆一下条件：

- 递增且前缀异或和递增。说明异或的过程中最高位只能不断增加，所以最高位的位置严格递增。
- 后缀异或和递增。说明异或时不会有任何一个数的最高位被异或为 $0$。

于是可以得到等价充要条件：

> 一个数列是好的，当且仅当这些数的最高位所在的位单调递增，且这些位上均存在奇数个 $1$。

这个条件的形式已经足够简洁，可以支持我们对此进行计数。下文 $m\gets m+1$ 将限制变为 $<m$。

显然对于任意正整数 $n$，有 $\sum_{2\mid i}\binom ni=\sum_{2\nmid i}\binom ni=2^{n-1}$。相信这个大家都会证明。假设我们已经将所有最高位填完了，设 $a_i=2^{b_i}$，那么再往里面填 $1$ 的方案数是多少呢？可以发现：

> 若这一层有某个数的最高位，则这一行只能再偶数个。
> 否则，这一行可以随便填。

容易发现，当我们拆位后，每一位上填的方案数是好算的。设填之前 $0$ 的个数为 $c_0$，$1$ 的个数为 $c_1$，则方案数是 $2^{c_0-c_1}$。全部乘起来，特判下最后一个数的最高位，得到答案为 $2^{\sum b_i-n+1}$。  
考虑单次询问怎么做。将 $m$ 拆成若干个值域段。设 $m=2^{k_1}+2^{k_2}+\cdots+2^{k_t}$，其中 $k_1>k_2>\cdots>k_t\ge0$，则拆成：

$$[0,2^{k_1}),[2^{k_1},2^{k_1}+2^{k_2}),\cdots,[m-2^{k_t},m)$$

这样 $m$ 的低位都在 $[0,2^k)$ 的范围内滑动。继续看倒数第二个数的最高位能在哪。假设当前枚举的值域段到了 $m$ 从高往低的第 $i$ 个 $1$：

- 最高位可以是 $m$ 已经被固定的 $0$。
- 最高位可以在 $a_i$，然后最后一个数的这一位不能是 $1$。

第二类情况恰好扣除一半，直接按照前面的公式计算。问题变成快速计算下面这个东西：

> 定义整数序列 $a$ 的权值为 $2^{\sum a_i}$，求所有递增且值域为 $[1,m]$ 的序列 $a$ 的权值和。

显然能暴力 dp，时间复杂度 $O(n^2)$，可以通过前 $2$ 个子任务，搭配数据结构维护可以通过前 $3$ 个子任务。

继续优化。严格递增是坏的，所以考虑 $a'_i=a_i-i$ 变成非严格递增，就能转化为格路计数问题。将 $a'$ 与 $n\times(m-n)$ 的网格上的格路建立映射：在第 $i$ 格前先向上走到 $a'_i$ 的位置。问题变为所有从左下到右上的路径右下部分面积的 $2$ 次幂之和。

对面积拆贡献。若在高度为 $h$ 的位置有一条向右走的边，那么这条边会对面积贡献 $h$，而 $h$ 的值其实就是这条边之前向上的边数。考虑把格路转化为 $0/1$ 串将向上的边标为 $1$，向右的边标为 $0$，则面积为该序列的逆序对个数。  

可重串的逆序对是难以刻画的，但是我们可以用排列的逆序对来刻画 $0/1$ 串的逆序对。具体地，假设长度为 $K$ 的排列权值为 $f(K)$，那么对于一个长度为 $N+M$，$0,1$ 数量各为 $N,M$ 的 $0/1$ 串，其权值可以通过“将其视作排列的权值”除去 $0,1$ 内部的贡献来计算，也即 $\frac{f(N+M)}{f(N)f(M)}$。

对于长度为 $K$ 的排列，我们可以考虑递推。我们在序列末尾插入数时，可以不考虑在排列的某个位置插入，而是在值域上插入一个数。那么插入 $0,1,\cdots,K$ 会产生的逆序对数就与之前的排列无关了，为 $K,K-1,\cdots,0$。所以造成的贡献为 $2^K+2^{K-1}+\cdots+2^0=2^{K+1}-1$，即 $f(K+1)=(2^{K+1}-1)f(K)$。

化简至此容易做到 $O(n)-O(1)$，可以通过前 $4$ 个子任务，实现精细可以通过前 $5$ 个子任务。

接下来考虑如何处理多组询问。将 $m$ 划分成若干个 $0/1$ 段，每次操作都只会造成 $O(1)$ 个段的改动。然后对于连续 $0$ 段和 $1$ 段，都可以计算其贡献，$0$ 对其后的 $1$ 贡献，$1$ 对前面的 $0$ 贡献。考虑拿两个平衡树，分别维护 $0$ 与 $1$ 的连续段。段内求和都是好算的，段外只要实现前、后缀和即可。

总的时间复杂度是 $O(n+q\log q)$，常数取决于你怎么维护。可以通过所有子任务。想清楚的话实现还是较为简单的。

当然也可以用线段树维护，不过笔者并没有考虑到线段树做法。如果空间被卡的出题人在这谢罪了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define dIO_USE_BUFFER
struct IO{
#ifdef dIO_USE_BUFFER
const static int BUFSIZE=1<<20;char ibuf[BUFSIZE],obuf[BUFSIZE],*p1,*p2,*pp;inline int getchar(){return(p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,BUFSIZE,stdin),p1==p2)?EOF:*p1++);}inline int putchar(char x){return((pp-obuf==BUFSIZE&&(fwrite(obuf,1,BUFSIZE,stdout),pp=obuf)),*pp=x,pp++),x;}inline IO&flush(){return fwrite(obuf,1,pp-obuf,stdout),pp=obuf,fflush(stdout),*this;}IO(){p1=p2=ibuf,pp=obuf;}~IO(){flush();}
#else
int(*getchar)()=&::getchar;int(*putchar)(int)=&::putchar;inline IO&flush(){return fflush(stdout),*this;}
#endif
string _sep=" ";int k=2;template<typename Tp,typename enable_if<is_integral<Tp>::value||is_same<Tp,__int128_t>::value>::type* =nullptr>inline int read(Tp&s){int f=1,ch=getchar();s=0;while(!isdigit(ch)&&ch!=EOF)f=(ch=='-'?-1:1),ch=getchar();if(ch==EOF)return false;while(ch=='0')ch=getchar();while(isdigit(ch))s=s*10+(ch^48),ch=getchar();s*=f;return true;}template<typename Tp,typename enable_if<is_floating_point<Tp>::value>::type* =nullptr>inline int read(Tp&s){int f=1,ch=getchar();s=0;while(!isdigit(ch)&&ch!='.'&&ch!=EOF)f=(ch=='-'?-1:1),ch=getchar();if(ch==EOF)return false;while(isdigit(ch))s=s*10+(ch^48),ch=getchar();if(ch=='.'){Tp eps=0.1;ch=getchar();while(isdigit(ch))s=s+(ch^48)*eps,ch=getchar(),eps/=10;}s*=f;return true;}inline int read(char&ch){ch=getchar();while(isspace(ch)&&ch!=EOF)ch=getchar();return ch!=EOF;}inline int read(char*c){char ch=getchar(),*s=c;while(isspace(ch)&&ch!=EOF)ch=getchar();while(!isspace(ch)&&ch!=EOF)*(c++)=ch,ch=getchar();*c='\0';return s!=c;}inline int read(string&s){s.clear();char ch=getchar();while(isspace(ch)&&ch!=EOF)ch=getchar();while(!isspace(ch)&&ch!=EOF)s+=ch,ch=getchar();return s.size()>0;}template<typename Tp=int>inline Tp read(){Tp x;read(x);return x;}template<typename Tp,typename...Ts>inline int read(Tp&x,Ts&...val){return read(x)&&read(val...);}inline int getline(char*c,const char&ed='\n'){char ch=getchar(),*s=c;while(ch!=ed&&ch!=EOF)*(c++)=ch,ch=getchar();*c='\0';return s!=c;}inline int getline(string&s,const char&ed='\n'){s.clear();char ch=getchar();while(ch!=ed&&ch!=EOF)s+=ch,ch=getchar();return s.size()>0;}template<typename Tp,typename enable_if<is_integral<Tp>::value||is_same<Tp,__int128_t>::value>::type* =nullptr>inline IO&write(Tp x){if(x<0)putchar('-'),x=-x;static char sta[41];int top=0;do sta[top++]=x%10^48,x/=10;while(x);while(top)putchar(sta[--top]);return*this;}inline IO&write(const string&str){for(char ch:str)putchar(ch);return*this;}inline IO&write(const char*str){while(*str!='\0')putchar(*(str++));return*this;}inline IO&write(char*str){return write((const char*)str);}inline IO&write(const char&ch){return putchar(ch),*this;}template<typename Tp,typename enable_if<is_floating_point<Tp>::value>::type* =nullptr>inline IO&write(Tp x){if(x>1e18||x<-1e18){write("[Floating point overflow]");throw;}if(x<0)putchar('-'),x=-x;const static long long pow10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,10000000000000000,100000000000000000,100000000000000000,100000000000000000};const auto&n=pow10[k];long long whole=x;double tmp=(x-whole)*n;long long frac=tmp;double diff=tmp-frac;if(diff>0.5){++frac;if(frac>=n)frac=0,++whole;}else if(diff==0.5&&((frac==0U)||(frac&1U)))++frac;write(whole);if(k==0U){diff=x-whole;if((!(diff<0.5)||(diff>0.5))&&(whole&1))++whole;}else{putchar('.');static char sta[21];int count=k,top=0;while(frac){sta[top++]=frac%10^48;frac/=10,count--;}while(count--)putchar('0');while(top)putchar(sta[--top]);}return*this;}template<typename Tp,typename...Ts>inline IO&write(Tp x,Ts...val){return write(x),write(_sep),write(val...),*this;}template<typename...Ts>inline IO&writeln(Ts...val){return write(val...),putchar('\n'),*this;}template<typename...Ts>inline IO&writesp(Ts...val){return write(val...),putchar(' '),*this;}inline IO&writeln(void){return putchar('\n'),*this;}inline IO&sep(const string&s=" "){return _sep=s,*this;}inline IO&prec(const int&K=2){return k=K,*this;}}io;

typedef long long ll;
typedef unsigned uint;

const int MAXN = 1e6 + 10;
const int MAXM = 1e7 + 30;
const int mod = 998244353;

inline int add(int x, int y) { return x += y, x < mod ? x : x - mod; }
inline int del(int x, int y) { return x -= y, x < 0 ? x + mod : x; }

inline 
int qpow(int b, int p) {
	int res = 1;
	for (; p; p >>= 1, b = (ll)b * b % mod) if (p & 1) res = (ll)res * b % mod;
	return res;
}

int p[MAXM], p2[MAXM], pp2[MAXM];

int q_fac[MAXM], q_ifac[MAXM];

inline 
void init(int n) {
	for (int i = 1; i <= n; i++) p[i] = add(p[i - 1], p[i - 1] + 1);
	*p2 = 1;
	for (int i = 1; i <= n; i++) p2[i] = add(p2[i - 1], p2[i - 1]);
	*pp2 = 1;
	for (int i = 1; i <= n; i++) pp2[i] = (ll)pp2[i - 1] * p2[i - 1] % mod;
	*q_fac = 1;
	for (int i = 1; i < n; i++) q_fac[i] = (ll)q_fac[i - 1] * p[i] % mod;
	q_ifac[n - 1] = qpow(q_fac[n - 1], mod - 2);
	for (int i = n - 1; i; i--) q_ifac[i - 1] = (ll)q_ifac[i] * p[i] % mod;
}

inline 
int q_binom(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return (ll)q_fac[n] * q_ifac[m] % mod * q_ifac[n - m] % mod;
}

inline 
int f(int n, int m) {
	return (ll)q_binom(n, m) * pp2[m - 1] % mod;
}

mt19937 eng(time(0));

struct FHQ_treap {
	
	struct node {
		int ls, rs, size; uint w;
		int l, r; int val, sum;
		node(int l = 0, int r = 0, int val = 0) : 
			ls(0), rs(0), size(1), w(eng()), 
			l(l), r(r), val(val), sum(val) {} 
	} t[MAXN]; int cnt = 0, rt = 0;
	
	node operator [] (int k) const { return t[k]; }
	
	inline 
	int create(int l, int r, int val) {
		return t[++cnt] = node(l, r, val), cnt;
	}
	
	inline 
	void pushup(int p) {
		t[p].size = t[t[p].ls].size + t[t[p].rs].size + 1;
		t[p].sum = add(add(t[t[p].ls].sum, t[t[p].rs].sum), t[p].val);
	}
	
	void split(int p, int k, int &x, int &y) {
		if (!p) return x = y = 0, void();
		if (t[p].r <= k) x = p, split(t[p].rs, k, t[p].rs, y);
		else y = p, split(t[p].ls, k, x, t[p].ls); pushup(p);
	}
	
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].w < t[y].w) return t[x].rs = merge(t[x].rs, y), pushup(x), x;
		return t[y].ls = merge(x, t[y].ls), pushup(y), y;
	}
	
	inline 
	void insert(int l, int r, int val) {
		int ls, rs; split(rt, r, ls, rs);
		rt = merge(merge(ls, create(l, r, val)), rs);
	}
	
	inline 
	void erase(int k) {
		int ls, rs, p; split(rt, k, ls, rs), split(ls, k - 1, ls, p);
		rt = merge(merge(ls, merge(t[p].ls, t[p].rs)), rs);
	}
	
	inline 
	int ask(int k, bool f) {
		int ls, rs, ans; split(rt, k, ls, rs);
		ans = f ? t[rs].sum : t[ls].sum, rt = merge(ls, rs);
		return ans;
	}
	
	inline 
	int prev(int k) {
		int ls, rs, p; split(rt, k - 1, ls, rs);
		for (p = ls; t[p].rs; p = t[p].rs);
		return rt = merge(ls, rs), p;
	}
	
	inline 
	int next(int k) {
		int ls, rs, p; split(rt, k, ls, rs);
		for (p = rs; t[p].ls; p = t[p].ls);
		return rt = merge(ls, rs), p;
	}
	
	inline 
	int qmax() {
		int p = rt;
		for (; t[p].rs; p = t[p].rs);
		return t[p].r;
	}
	
};

FHQ_treap t0, t1; int ans = 0, n;

inline 
int calc_0(int l, int r) {
	return del(f(r + 1, n - 1), f(l, n - 1));
}

inline 
int calc_1_x(int l, int r) {
	return del(p2[r + 1], p2[l]);
}

inline 
int calc_1_y(int l, int r) {
	int res = (ll)p2[r] * f(r + 1, n - 1) % mod;
	if (l) res = del(res, (ll)p2[l - 1] * f(l, n - 1) % mod);
	return res;
}

inline 
void insert_0(int l, int r) {
	int x = calc_0(l, r); ans = add(ans, (ll)x * t1.ask(l - 1, 0) % mod);
	int p = t0.prev(r), q = t0.next(r);
	assert(!p || t0[p].r < l), assert(!q || t0[q].l > r);
	if (p && t0[p].r == l - 1) l = t0[p].l, t0.erase(t0[p].r);
	if (q && t0[q].l == r + 1) r = t0[q].r, t0.erase(t0[q].r);
	t0.insert(l, r, calc_0(l, r));
}

inline 
void erase_0(int l, int r) {
	int x = calc_0(l, r); ans = del(ans, (ll)x * t1.ask(l - 1, 0) % mod);
	int k = t0.next(r - 1);
	int pl = t0[k].l, pr = t0[k].r; t0.erase(pr);
	if (l > pl) t0.insert(pl, l - 1, calc_0(pl, l - 1));
	if (r < pr) t0.insert(r + 1, pr, calc_0(r + 1, pr));
}

inline 
void insert_1(int l, int r) {
	int x = calc_1_x(l, r), y = calc_1_y(l, r);
	ans = add(ans, add((ll)x * t0.ask(r, 1) % mod, y));
	int p = t1.prev(r), q = t1.next(r);
	assert(!p || t1[p].r < l), assert(!q || t1[q].l > r);
	if (p && t1[p].r == l - 1) l = t1[p].l, t1.erase(t1[p].r);
	if (q && t1[q].l == r + 1) r = t1[q].r, t1.erase(t1[q].r);
	t1.insert(l, r, calc_1_x(l, r));
}

inline 
void erase_1(int l, int r) {
	int x = calc_1_x(l, r), y = calc_1_y(l, r);
	ans = del(ans, add((ll)x * t0.ask(r, 1) % mod, y));
	int k = t1.next(r - 1);
	int pl = t1[k].l, pr = t1[k].r; t1.erase(pr);
	if (l > pl) t1.insert(pl, l - 1, calc_1_x(pl, l - 1));
	if (r < pr) t1.insert(r + 1, pr, calc_1_x(r + 1, pr));
}

inline 
void add(int x) {
	int k0 = t0.next(x - 1), k1 = t1.next(x - 1);
	int l0 = t0[k0].l, r0 = t0[k0].r, l1 = t1[k1].l, r1 = t1[k1].r;
	if (k0 && l0 <= x && x <= r0) erase_0(x, x), insert_1(x, x);
	else if (k1 && l1 <= x && x <= r1) {
		erase_1(x, r1), insert_0(x, r1);
		if (k0) erase_0(r1 + 1, r1 + 1); insert_1(r1 + 1, r1 + 1);
	} else {
		k1 = t1.prev(x), r1 = t1[k1].r;
		insert_1(x, x); if (r1 < x - 1) insert_0(r1 + 1, x - 1);
	}
}

inline 
void del(int x) {
	int k0 = t0.next(x - 1), k1 = t1.next(x - 1);
	int l0 = t0[k0].l, r0 = t0[k0].r, l1 = t1[k1].l, r1 = t1[k1].r;
	if (k1 && l1 <= x && x <= r1) {
		erase_1(x, x), r1 = t1.qmax();
		if (r1 < x - 1) erase_0(r1 + 1, x - 1); else insert_0(x, x); 
	} else if (k0 && l0 <= x && x <= r0) {
		erase_0(x, r0), insert_1(x, r0);
		erase_1(r0 + 1, r0 + 1), r1 = t1.qmax();
		if (r1 > r0) insert_0(r0 + 1, r0 + 1);
	}
}

inline 
int query() {
	int r1 = t1.qmax();
	return add(del(ans, calc_1_y(r1, r1)), f(r1, n));
}

int q;

int main() {
	io.read(n, q), init(1e7 + 30), insert_1(0, 0);
	for (int x, opt; q--;) {
		io.read(opt);
		if (opt == 0) io.read(x), add(x);
		else if (opt == 1) io.read(x), del(x);
		else io.writeln(query());
	}
}
```

其实 $O(n^2)\to O(n)$ 的优化是一个叫做 q-analog 的普及度还算高科技，但是主播在完全不知道这个的情况下研发出了本题做法（甚至是快讲评的时候才知道的），导致完全没料想到这个组合意义会被直接秒……如果影响到大家的比赛体验也在这里磕头了。

---

