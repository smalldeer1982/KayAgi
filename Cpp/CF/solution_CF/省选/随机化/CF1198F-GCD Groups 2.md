# GCD Groups 2

## 题目描述

给定一个包含 $n$ 个整数的数组。你需要将所有整数分成两个组，使得第一个组中所有整数的最大公约数等于 $1$，第二个组中所有整数的最大公约数也等于 $1$。

一组整数的最大公约数是能够整除该组所有整数的最大非负整数。

两个组都必须非空。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 3 6 7
```

### 输出

```
YES
2 2 1 1 
```

## 样例 #2

### 输入

```
5
6 15 35 77 22
```

### 输出

```
YES
2 1 2 1 1 
```

## 样例 #3

### 输入

```
5
6 10 15 1000 75
```

### 输出

```
NO
```

# 题解

## 作者：chenxinyang2006 (赞：19)

题解已经写了 114514 种随机化做法，那我不会随机化，又该怎么通过这个题呢？

设 $k$ 为 $a_1 \sim a_n$ 的最大质因子数，本题中 $k \le 9。$

不考虑时间复杂度，有一种想法是钦点 $a_1$ 被放在第一组，枚举 $j$ 从 $2 \sim n$ 使 $a_j$ 属于第二组，然后写一个函数 `solve(1,j,a)` 表示测试将 $a$ 的除了 $a_1,a_j$ 之外的元素划分到两组中，能否让这两组的 $\gcd$ 均为 $1$。

那么这个 `solve` 函数怎么实现呢？注意到两组需要记录的信息只有 $a_1,a_j$ 的每个质因子是否已经在取 $\gcd$ 的过程中被毙掉，于是设 $dp_{i,S,T}$ 表示划分了 $a[1,i]$，$a_1$ 的质因子集合 $S$ 已经被毙掉，$a_j$ 的质因子集合 $T$ 已经被毙掉是否合法，转移直接枚举 $i+1$ 被放到第一组还是第二组，这样 DP 复杂度为 $n4^k。$

怎么优化呢？注意到对于一对 $S,T$，一定存在一个分界点 $p$ 使得 $i \in [1,p],dp_{i,S,T}=1,\forall i \in (p,n],dp_{i,S,T} = 0$，于是直接记录分界点，换句话说设 $dp_{S,T}$ 为 $a$ 的最短前缀使得 $a_1$ 的 $S$ 质因子集合被毙掉，$a_j$ 的 $T$ 质因子集合被毙掉可行。

转移考虑 $S$ 或者 $T$ 第一次被拓展是哪个新的元素被毙掉了。比方说 $S$，枚举新的质因子 $p \notin S$ 被毙掉了，那么选 $a$ 序列中 $dp_{S,T}$ 后第一个不包含因子 $p$ 的 $a_i$ 加入第一组一定最优，注意将这个 $a_i$ 加入第一组不一定只毙掉了质因子 $p。$

这样转移复杂度 $4^k k$，但需要能 $O(1)$ 找到 $a$ 的某个后缀的第一个不包含因子 $p$ 的 $a_i$ 在哪里，不过这个也可以简单 $O(nk)$ 预处理。

但调用 `solve` $n$ 次显然还是太劣了！不过我们注意到对于任意大小大于 $k+1$ 的 $\gcd$ 为 $1$ 的集合，从中总能去掉一个元素使 $\gcd$ 仍为 $1$。任意找一个大小 $\le k+1$ 的 $\gcd$ 为 $1$ 且包含 $a_1$ 的集合，考虑从将这个集合作为第一组调整得到一组合法解。

要么就是根本不调整，也就是剩余集合 $\gcd$ 也为 $1$，这种 case 可以直接判掉。

要么就是把这个集合丢掉几个元素，然后从剩余集合加入几个元素（也可以不加），枚举丢掉了其中的下标 $i$，注意到 $a_1$ 与 $a_i$ 在这种情况下一定分属两组，于是只要对这些 $a_i$ 调用 `solve(1,i,a)` 就可以了！



分析一下复杂度：最坏情况下调用 $k$ 轮 `solve`，一轮 `solve` $O(nk + 4^k k)$，总复杂度是 $(nk^2 + 4^k k^2)$，确定性做法！

当然其实还有一些额外的复杂度，比如一轮 `solve` 过程中需要分解 $a_1,a_j$，这需要 $O(\sqrt V)$ 时间，找到任意一个大小 $\le k+1$ 的 $\gcd$ 为 $1$ 且包含 $a_1$ 的集合可能也需要做一些质因数分解，我的做法是先找到一个大小 $\le \log V$ 的集合（也就是取 $a_1 \sim a_n$ 所有前缀 $\gcd$ 上减小的位置），然后进一步缩减大小。

[代码](https://codeforces.com/contest/1198/submission/223326169)

---

## 作者：zhoukangyang (赞：14)

[来 cnblogs 里来看](https://www.cnblogs.com/zkyJuruo/p/14335884.html)

蒟蒻写了一个十分奇怪的不会证明正确性的随机化，竟然过了？感觉这个东西可以 `hack` 。。。

考虑最朴素的随机，每次 `random_shuffle`，随机取前缀作为第一个集合，剩下为第二个集合。

这个可以贪心来优化，每次 `random_shuffle`，让第一个集合为这个序列的最短的满足 $\gcd$ 为 $1$ 的前缀，第二个集合为剩下的数。

发现这个东西 $\tt WA$ 了。看看数据，发现是很多同样的数导致运行的效率极低！

发现很多个相同的数可以缩成两个数（因为一个在第一个集合，一个在第二个集合，其他都是没用的），然后就 $\tt AC$ 了。。。。

代码：

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long
#define db double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 1e5 + 7;
inline int read() {
	int x = 0, f = 1; char ch=getchar();
	while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x * f; 
}
int n, ans[N], g[N], tot;
struct node {
	int val, id;
} f[N];
vector<int> ve[N];
map<int, int> A, B;
int main() {
	srand(233);
	const db st = clock();
	n = read();
	L(i, 1, n) {
		g[i] = read();
		if(!A[g[i]]) A[g[i]] = i, ++tot, f[tot].id = i, f[tot].val = g[i];
		else if(!B[g[i]]) B[g[i]] = i, ++tot, f[tot].id = i, f[tot].val = g[i];
		else ve[A[g[i]]].push_back(i);
	}
	while((clock() - st) / CLOCKS_PER_SEC < 0.4) {
		random_shuffle(f + 1, f + tot + 1);
		int now = 0, pp = 0, cnt = 0;
		L(i, 1, tot) {
			now = __gcd(now, f[i].val);
			if(now == 1) {
				++cnt;
				if(cnt == 2) {
					L(t, 1, pp) {
						ans[f[t].id] = 1;
						for(int p : ve[t]) ans[p] = 1;
					}
					L(t, pp + 1, n) {
						ans[f[t].id] = 2;
						for(int p : ve[t]) ans[p] = 2;
					}
					puts("YES");
					L(t, 1, n) printf("%d ", ans[t]);
					puts("");
					return 0;
				}
				pp = i, now = 0;
			}
		}
	}
	puts("NO");
	return 0;
} 
```

---

## 作者：eee_hoho (赞：3)

这是Div1F¿我人傻了。

一看到这题完全不会怎么办啊，那就直接随机好了。

先考虑一种贪心思路，加入一个数 $a$ 的时候，加入到一个 $gcd$ 不是 $a$ 的因子的集合，这样子 $\gcd$ 一定变小了，变得很优。

然而这肯定过不去，所以多随机几遍 $a$ 加入的顺序，就能得到解了。

思考一下这样做的正确性，我们注意到 $a$ 的质因子最多只有 $9$ 个，那么什么时候我们这样子做会错误，就是其中一个集合存在一个公共质因子，而 $10^9$ 以内的质数大约有 $5\times 10^7$ 个，所以这样的概率是非常低的，于是就做完了。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 1e5;
const int inf = 1e8;
using namespace std;
int n,a[N + 5],g[3],c[N + 5],id[N + 5];
bool solve()
{
    c[id[1]] = 1;
    g[1] = a[id[1]];
    c[id[2]] = 2;
    g[2] = a[id[2]];
    for (int i = 3;i <= n;i++)
    {
        if (a[id[i]] % g[1] == 0)
        {
            c[id[i]] = 2;
            g[2] = __gcd(g[2],a[id[i]]);
        }
        else
        {
            c[id[i]] = 1;
            g[1] = __gcd(g[1],a[id[i]]);
        }
    }
    return g[1] == 1 && g[2] == 1;
}
int main()
{
    srand(19260817);
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
        scanf("%d",&a[i]),id[i] = i;
    int fl = 0,T = inf / n / 20;
    T = min(T,2000);
    while (T--)
    {
        g[1] = g[2] = 0;
        random_shuffle(id + 1,id + n + 1);
        fl |= solve();
        if (fl)
        {
            cout<<"YES"<<endl;
            for (int i = 1;i <= n;i++)
                printf("%d ",c[i]);
            return 0;
        }
    }
    cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：yuzhechuan (赞：2)

一道div1的F,神他喵居然是道玄学random_shuffle题？？？

然鹅也是需要一些贪心思路的呢，朴素随机wa的概率还是高的呢

---

### 题解：

考虑对打乱后序列正确性的判定及划分

我们注意到如果数$x$是某一组的gcd的倍数，那依照贪心的思路，它肯定不应该被放进那一组，而是放进另一组

于是我们可以做到$O(n)$判定

为什么这么random是对的呢？口胡一下就是一组数gcd=1的概率会随数的增加而呈指数级减小，完整证明可以看[官方的](https://codeforces.com/blog/entry/68812)

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5;
int n,a[N],ans[N],b[N];

inline int gcd(int x,int y){
	if(!y) return x;
	return gcd(y,x%y);
}

signed main(){
	read(n);
    srand(time(NULL));
	for(int i=1;i<=n;i++) read(a[i]),b[i]=i;
	long long begin_time=clock();
	while(clock()-begin_time<CLOCKS_PER_SEC*0.45){ //卡时随机
		random_shuffle(b+1,b+1+n);
		int g1=0,g2=0;
		for(int i=1;i<=n;i++){
			int now=gcd(g1,a[b[i]]);
			if(now^g1){ //能使gcd减小就划进这一组
				g1=now;
				ans[b[i]]=1;
			}
			else{
				g2=gcd(g2,a[b[i]]);
				ans[b[i]]=2;
			}
		}
		if(g1==1&&g2==1){
			puts("YES");
			for(int i=1;i<=n;i++) write(ans[i]),putchar(' ');
			return 0;
		}
	}
	puts("NO");
}
```

---

## 作者：Victory_Defeat (赞：2)

又一道玄学F题

思路（玄学）：

1. 读入

2. 随机打乱（random_shuffle）

3. 每次判断一波，如正解，则输出

4. 重复以上步骤

就是一道暴力，不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef double lf;
namespace IN
{
	const int Max_Input_Number=1000000;
	#define getc()(p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,Max_Input_Number),p1==p2)?EOF:*p1++)
	char buf[Max_Input_Number],*p1,*p2;
	template<typename T>inline int input(T &x)
	{
		static std::streambuf *inbuf=cin.rdbuf();
		x=0;
		register int f=0,flag=1;
		register char ch=getc();
		if(ch==EOF)return EOF;
		while(!std::isdigit(ch))
		{
			if(ch=='-')f=1;
			ch=getc();
		}
		if(std::isdigit(ch))x=x*10+(ch&15),ch=getc(),flag=true;
		while(std::isdigit(ch))
		{
			x=x*10+(ch&15);
			ch=getc();
		}
		x=f?-x:x;
		return ch==EOF?EOF:flag;
	}
	template<typename T,typename ...Args>inline int input(T& a,Args& ...args)
	{
		return input(a)&&input(args...);
	}
	inline int readc(char &ch)
	{
		static std::streambuf *inbuf=cin.rdbuf();
		return (ch=getc())==EOF?EOF:0;
	}
	inline int readst(char *st)
	{
		if(readc(*st)!=EOF&&(*st))while(readc(*(++st))!=EOF&&*st!='\n');
		else return EOF;
		return 0;
	}
}
namespace OUT
{
	template <typename T>inline void output(T x)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		static char stack[21];
		static int top=0;
		if(x<0)
		{
			outbuf->sputc('-');
			x=-x;
		}
		if(!x)
		{
			outbuf->sputc('0');
			outbuf->sputc('\n');
			return;
		}
		while(x)
		{
			stack[++top]=x%10+'0';
			x/=10;
		}
		while(top)
		{
			outbuf->sputc(stack[top]);
			--top;
		}
		outbuf->sputc('\n');
	}
	inline void putc(const char ch)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		outbuf->sputc(ch);
	}
	template<typename T>inline void output(const char ch,T x)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		static char stack[21];
		static int top=0;
		if(x<0)
		{
			outbuf->sputc('-');
			x=-x;
		}
		if(!x)
		{
			outbuf->sputc('0');
			outbuf->sputc(ch);
			return;
		}
		while(x)
		{
			stack[++top]=x%10+'0';
			x/=10;
		}
		while(top)
		{
			outbuf->sputc(stack[top]);
			--top;
		}
		outbuf->sputc(ch);
	}
	template<typename T,typename ...Args>inline void output(T a,Args ...args)
	{
		output(a);output(args...);
	}
	template<typename T,typename ...Args> inline void output(const char ch,T a,Args ...args)
	{
		output(ch,a);output(ch,args...);
	}
	inline void putst(const char *st)
	{
		static std::streambuf *outbuf=cout.rdbuf();
		int _len=strlen(st);
		const char *p=st;
		do{outbuf->sputc(*st);st++;}while(st+1<p+_len);
	}
}
using IN::input;
using IN::readc;
using IN::readst;
using OUT::output;
using OUT::putc;
using OUT::putst;
//自行忽略本注释以上部分
const int N=100010;
int a[N],p[N],ans[N];
int gcd(int a,int b)
{
	int r=a%b;
	while(r)
	{
		a=b;
		b=r;
		r=a%b;
	}
	return b;
}
//gcd
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	srand(19260817);//QAQ
	int n;
	input(n);
	for(int i=1;i<=n;++i)input(a[i]);
	for(int i=1;i<=n;++i)p[i]=i;//顺序
	int t=100;//重复100次
	while(t--)
	{
		random_shuffle(p+1,p+1+n);//打乱顺序
		int x=0,y=0,cnt;
		for(int i=1;i<=n;++i)
		{
			if((x!=1)&&((cnt=gcd(x,a[p[i]]))!=x))x=cnt,ans[p[i]]=1;//如果当前的第一组不是1且两者gcd不是x，更新x，放进第一组
			else y=gcd(y,a[p[i]]),ans[p[i]]=2;//否则进第二组，更新y
		}
		if(x==1&&y==1)//如果本次成功
		{
			putst("YES\n");
			putc('\n');
			for(int i=1;i<=n;++i)output(' ',ans[i]);
			return 0;
		}//结束，由于SPJ，不必担心
	}
	putst("NO\n");//无解
	return 0;
}
```

---

## 作者：Moeebius (赞：1)

## Solution1
来点正常的官方题解。

注意到 $10^9$ 以内的数最多有 $9$ 个素因子！

考虑如下事实：

> 如果有一组解，那么一定可以将每组删到只有 $10$ 个数，并且组内 $\gcd$ 依然为 $1$。

证明：假设把组内第一个数设为「基准数」，容易发现如果删掉一个数后，组内 $\gcd$ 发生变化，一定是这个数「毙掉」了「基准数」的一个素因子。而「基准数」素因子只有 $9$ 个。$\square$

首先特判掉 $n\le 20$ 的情况，这部分直接暴力；

同时可以启发我们随机选两个数 $x,y$，并对他们分解素因数；这样直接状压还「活着」的素因子，在剩下 $n-2$ 个数上跑 DP 就能做到 $O(n2^{2k})$，其中 $k=9$。

考虑优化。发现剩余 $n-2$ 个数中大多数都是没用的；具体地，对于 $x,y$ 的总共 $2k$ 个素因子，每个素因子只需要最多 $k$ 个数就可以毙掉了（当然你也可以保险起见取 2k 个），所以有用的数的个数不超过 $2k^2$。

所以我们直接 $O(nk)$ 扫一遍，预处理出每一个数能毙掉哪些素因子，然后把这 $2k$ 个数拿出来跑状压即可。复杂度 $O(nk+k2^{2k})$。

[Code](https://codeforces.com/contest/1198/submission/232633035)

## Solution2

来点不正常的乱搞做法！

我们每次 `shuffle` 整个数列，然后找到最短的一个前缀满足 $\gcd=1$，此时判断后缀是否合法。

一个著名的优化就是把一堆相同的数压成两个（显然，因为可以一个分第一组，一个分第二组）

---

下面是正确性证明：

~~不会。~~

考虑构造这样的极端情况：

```
223092870 223092870/2 223092870/3 223092870/5 223092870/7 223092870/11 223092870/13 223092870/17 223092870/19 223092870/23
```

将这种状物塞两组，再用 `223092870` 填充剩下的位置。这样已经将解的有效长度卡到了理论上界 $2k+2$，同时单次出解概率是 $\dfrac{10!\cdot10!\cdot2}{20!}$（因为只要关心这有效的 20 个数）。简单计算可知期望下出解次数为 $46189$ 左右（而且很难卡满），加上这个强力优化后可以通过此题。

---

## 作者：_Ch1F4N_ (赞：1)

看到随机化这个标签开始考虑模拟退火。

显然，假若把同一个组放在一起，先求出最小的 $r$ 使得 $[1,r]$ 内的最大公因数为 $1$，在判断 $[r+1,n]$ 内最大公因数是否为 $1$ 即可作出回答。

那么考虑将 $[r+1,n]$ 内最大公因数作为估价函数。

也就是每次随机交换序列内两个值，在用上述方法估价。

不过这个方法为什么是对的呢？

事实上，随机交换数期望会让最大公因数减小，因此当前最大公因数越小也就越容易在若干次交换后满足要求。

但是暴力求区间最大公因数很慢，不能多次退火。

因此我们写一棵线段树，维护区间最大公因数，最小的使得 $[1,r]$ 内的最大公因数为 $1$ 的 $r$ 也可以在线段树上二分求出。

然后再考虑一些黑科技优化：

1. `(double)clock()/CLOCKS_PER_SEC` 卡时。
2. `Binary GCD` 让求最大公因数的常数大大减小。

以及一些乱搞优化：

1. 假若每次交换的两个数相同则跳过。
2. 多跑几次退火。

就能愉快通过了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
double T;
double dt=0.91112;
double eps=1e-10;
pair<int,int> a[maxn];
int anser[maxn];
int n;
int tree[maxn*4];
int gcd(int a, int b) 
{
    int az=__builtin_ctz(a);
    int bz=__builtin_ctz(b);
    int z=min(az, bz);
    b>>=bz;
    while (a) 
    {
        a>>=az;
        int diff=a-b;
        az=__builtin_ctz(diff);
        b=min(a,b);
        a=abs(diff);
    }
    return b<<z;
}
void pushup(int x){
    tree[x]=gcd(tree[x*2],tree[x*2+1]);
}
void build(int x,int l,int r){
    if(l==r){
        tree[x]=a[l].first;
        return ;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void change(int x,int l,int r,int pos,int v){
    if(l>pos||r<pos) return ;
    if(l==r){
        tree[x]=v;
        return ;
    }
    int mid=(l+r)/2;
    change(x*2,l,mid,pos,v);
    change(x*2+1,mid+1,r,pos,v);
    pushup(x);
}
int query(int x,int l,int r,int lt,int rt){
    if(lt<=l&&r<=rt) return tree[x];
    if(l>rt||r<lt) return -1;
    int mid=(l+r)/2;
    int res=-1;
    int lv=query(x*2,l,mid,lt,rt),rv=query(x*2+1,mid+1,r,lt,rt);
    if(lv!=-1){
        if(res==-1) res=lv;
        else res=gcd(res,lv);
    }
    if(rv!=-1){
        if(res==-1) res=rv;
        else res=gcd(res,rv);
    }
    return res;
}
int kth(int x,int l,int r,int last){
    if(l==r) return l;
    int mid=(l+r)/2;
    int v=tree[x*2];
    if(last!=-1) v=gcd(v,last);
    if(v==1) return kth(x*2,l,mid,last);
    else return kth(x*2+1,mid+1,r,(last==-1?tree[x*2]:gcd(tree[x*2],last))); 
}
int ans=INT_MAX;
int f(){
    if(query(1,1,n,1,n)!=1) return 1145141919810;
    int chifan=kth(1,1,n,-1);
    if(chifan==n) return 1145141919810;
    return query(1,1,n,chifan+1,n)-1;
}
void Swap(int A,int B){
    change(1,1,n,A,a[B].first);
    change(1,1,n,B,a[A].first);
    swap(a[A],a[B]);
}
void SA(){
    T=1000000;
    if(f()==0){
        cout<<"YES\n";
        int chifan=kth(1,1,n,-1);
        for(int i=1;i<=chifan;i++) anser[a[i].second]=1;
        for(int i=chifan+1;i<=n;i++) anser[a[i].second]=2;
        for(int i=1;i<=n;i++) cout<<anser[i]<<' ';
        exit(0);
    }
    while(T>eps){
        if((double)clock()/CLOCKS_PER_SEC>=0.498){//时间限制用完直接输出无解
            cout<<"NO";
            exit(0);
        }
        int p1=rand()%n+1;
        int p2=rand()%n+1;
        if(a[p1].first==a[p2].first) continue;
        Swap(p1,p2);
        int nxt=f();
        if(nxt<ans){
            ans=nxt;
        }
        else{
            if(exp((ans-nxt*1.0)/T)*RAND_MAX<rand()){
                Swap(p1,p2);
            }
        }
        T*=dt;
    }
    if(f()==0){
        cout<<"YES\n";
        int chifan=kth(1,1,n,-1);
        for(int i=1;i<=chifan;i++) anser[a[i].second]=1;
        for(int i=chifan+1;i<=n;i++) anser[a[i].second]=2;
        for(int i=1;i<=n;i++) cout<<anser[i]<<' ';
        exit(0);
    }
}
void work(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    build(1,1,n);
    while(1) SA();//一直退火直到跑出答案或者时间限制用完
}
int t;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    work();
}
```


---

## 作者：Lates (赞：1)

看起来很神必的题，一般能想到随机化之类的东西。

就直接 random_shuffle 一下。找到一个前缀 $gcd = 1$。判断后缀可不可行。

值得注意的是，这里使用 random_shuffle 会 WA。可以改成更牛逼的 mt19937 中的 shuffle 函数。这样会直接 AC，不用搞题解中一些乱搞操作。

时间复杂度 $\mathcal{O}($能过$)$。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
using namespace std;
typedef double db;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')ch=getchar();
	while('0'<=ch&&ch<='9')x = x * 10 + (ch & 15),ch=getchar();
	return f?-x:x;
}
const int MAX = 1e5+5;
int n; 
int id[MAX], flag = 0, a[MAX], is[MAX];
int gcd(int a,int b) {
	return b?gcd(b,a%b):a;
}
signed main(){
//	freopen("in.in","r",stdin);
	n=read(); int m = n / 2;
	for(int i=1;i<=n;++i) id[i] = i, a[i] = read();
	mt19937 rnd(20221008);
	while((db) clock() / CLOCKS_PER_SEC < 0.48) {
		shuffle(id+1,id+1+n, rnd);
		int p = -1,q = -1, pos;
		m = 1;
		for(;m<=n;++m) {
			if(p == 1) break;
			if(p == -1) p = a[id[m]];
			else p = gcd(p, a[id[m]]);
		}
		if(m==n+1||p!=1) continue;
		pos = m-1;
		for(;m<=n;++m) {
			if(q == 1) break;
			if(q == -1) q = a[id[m]];
			else q = gcd(q, a[id[m]]);
		}
		if(q != 1) continue;
		for(int i=1;i<=n;++i) is[id[i]] = i;
		flag = 1;
		puts("YES");
		for(int i=1;i<=n;++i) printf("%d ",is[i] <= pos ? 1 : 2);
		puts(""); break;
	}
	if(!flag) return puts("NO"),0;
	return 0;
}


```

---

## 作者：MatrixGroup (赞：0)

## 题意

给定 $n$ 个数 $a_i$，请分为两组，使得每组 $\gcd$ 均为 $1$，或报告无解。

$n\le10^5,a_i\le10^9$。

## 解法

发现两组 $\gcd$ 都从零开始有点难搞。考虑钦定两个数归属不同组，就可以发现在不断向集合内加数的情况下，$\gcd$ 最多只有 $d^2$ 组可能。（其中 $d=1344$ 为值域内最大因子个数）设 $dp_{i,j}$ 表示两组 $\gcd$ 分别为 $i,j$ 的最前只需要多长的前缀。为了转移，我们需要枚举一个不是 $i/j$ 倍数的“下一个数”。可以只对质数幂预处理“下一个数”，然后质因数分解转移即可。设 $\omega=9$ 为值域内最大质因子个数，这样单次钦定复杂度是 $O(d^2(\omega+\log d)+\sqrt{a_i}+n\log a_i+n\log n)$ 的，其中一些 $\log$ 来自质数幂，另一些来自二分查找（使用哈希表可以去掉）。

我们最多需要钦定多少组呢？不妨钦定 $1$ 在第一组，那么注意到一组合法的方案中，最多只有 $\omega$ 个数有用（考虑每个质因子）。因此另一组最多只需要钦定 $\omega+1$ 个不同的数，就可以保证在有解的情况下钦定到一组解。因此复杂度是上面那坨东西乘上一个 $\omega$，是可以通过的。如果注意到 $\gcd=1$ 只和质数而不是质数幂有关，可以把 $d$ 优化成 $2^\omega$，不过在本题中不是必要的。

具体参考[实现](https://codeforces.com/problemset/submission/1198/232690948)。

---

