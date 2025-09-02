# Legen...

## 题目描述

Barney was hanging out with Nora for a while and now he thinks he may have feelings for her. Barney wants to send her a cheesy text message and wants to make her as happy as possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696D/5ab3ea47563ae6400cc578e63bb9e0de4cf3a082.png)Initially, happiness level of Nora is $ 0 $ . Nora loves some pickup lines like "I'm falling for you" and stuff. Totally, she knows $ n $ pickup lines, each consisting only of lowercase English letters, also some of them may be equal (in writing, but different in pronouncing or meaning though). Every time Nora sees $ i $ -th pickup line as a consecutive subsequence of Barney's text message her happiness level increases by $ a_{i} $ . These substrings may overlap, for example, Nora will see the pickup line aa twice and the pickup line ab once in text message aaab.

Due to texting app limits, Barney's text may have up to $ l $ characters.

Barney asked you to help him make Nora as much happy as possible, it's gonna be legen...

## 说明/提示

An optimal answer for the first sample case is hearth containing each pickup line exactly once.

An optimal answer for the second sample case is artart.

## 样例 #1

### 输入

```
3 6
3 2 1
heart
earth
art
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 6
3 2 8
heart
earth
art
```

### 输出

```
16
```

# 题解

## 作者：Hoks (赞：5)

## 前言
最近写了几道有关于**串串与矩阵优化 dp** 的题，感觉挺有感觉的。

广告：[串串博客](https://www.luogu.com.cn/article/dv6dig1o)。

类似题目：

[P3502 [POI2010] CHO-Hamsters](https://www.luogu.com.cn/problem/P3502)。

[SP1676 GEN - Text Generator](https://www.luogu.com.cn/problem/SP1676)。
## 思路分析
首先看到题目是多模式串，首先想到 ACAM。

接着仔细看题，发现是让我们构造一个长度为 $l$ 的字符串使得其中包含的串的权值和最大。

想到 dp，设计 $dp_{i,j}$ 表示填到第 $i$ 位的字符串，ACAM 上为 $j$ 状态的最大权值和。

那么转移方程式即为：
$$dp_{i+1,\delta(j,c)}=\max(dp_{i,j}+val_{\delta(j,c)})$$
其中 $\delta(j,c)$ 表示状态 $j$ 经过字符 $c$ 转移到的状态，而 $val_j$ 表示 $j$ 状态的权值。

首先可以在建 fail 指针的时候把后缀权值加上去，得到 $val_j$。

接着看到了令人寒心的数据范围：$l\le10^{14}$。

直接寄飞喽。

接着来考虑其意义，这个 dp，所表示的就相当于是 ACAM 上从一个状态走一步。

那么想到了什么？

**矩阵优化！**

因为状态互相转化可以看做在图上走。

把图用邻接矩阵 $base$ 存起来，那就是走一步走到的权值和。

那么 $base^l$ 即为走 $m$ 步得到的最大权值和。

是吗？

显然不是，矩阵乘法和最大和有什么关系啊。

所以考虑广义矩阵乘，将普通的**乘加**改为**加取最大值**。

接着再给初始状态以其他状态作为结束状态的权值和取个最大值即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=210,INF=0x3f3f3f3f3f3f3f3f;
int n,m,l,a[N];char s[N];
struct node{int a[N][N],n,m;node(){memset(a,-0x3f,sizeof(a));n=m=0;}}base,ans;
struct ACAM
{
	struct node{int nxt,ed,v[26];}t[N];int tot=0;
	inline void insert(const char s[],int n,int id)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		t[u].ed+=id;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0].v[i]) t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();t[u].ed+=t[t[u].nxt].ed;
			for(int i=0;i<26;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
		base.n=base.m=tot;ans.m=tot;ans.a[0][0]=0;ans.n=0;
		for(int i=0;i<=tot;i++) for(int j=0;j<26;j++) base.a[i][t[i].v[j]]=t[t[i].v[j]].ed;
	}
}ac;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)&&fc!=-1){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)&&fc!=-1) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        if(fc==-1) exit(0);return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
node mul(const node &x,const node &y)
{
	node res;res.n=x.n;res.m=y.m;
	for(int i=0;i<=x.n;i++)
		for(int j=0;j<=y.m;j++)
			for(int k=0;k<=x.m;k++)
				res.a[i][j]=max(res.a[i][j],x.a[i][k]+y.a[k][j]);
	return res;
}
inline node ksm(node x,int y)
{
	node res;res.n=res.m=x.n;for(int i=0;i<=x.n;i++) res.a[i][i]=0;
	while(y)
	{
		if(y&1) res=mul(res,x);
		x=mul(x,x);y>>=1;
	}
	return res;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) l=0,rd(s,l),ac.insert(s,l,a[i]);
	ac.build();ans=mul(ans,ksm(base,m));int res=0;
	for(int i=0;i<=ac.tot;i++) res=max(res,ans.a[0][i]);
	print(res);return 0;
}
```

---

## 作者：crashed (赞：4)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF696D)看题目。  
# 分析  
&emsp;&emsp;首先对于模式串建立 AC 自动机，并且计算出每个状态$p$的贡献总和$con(p)$。  
&emsp;&emsp;考虑一个朴素的 DP ：  
&emsp;&emsp;$f(i,p)$：当前串长度为$i$，匹配到$p$上的最大答案。  
&emsp;&emsp;设在$p$后加入字符$c$会转移到$t(p,c)$， DP 的转移如下：  
$$f(i+1,t(p,c))=\max\{f(i,p)+con(t(p,c))\}$$  
&emsp;&emsp;如何表示这种转移？ 我们可以尝试一下矩阵：  
$$
T_{i,j}=
\begin{cases}
      con(j)&\exists c, t(i,c)=j\\
      -\infty& otherwise
\end{cases}
$$  
&emsp;&emsp;并且可以再定义一种矩阵上的新运算 ' $\cdot$ ' ：  
$$C=A\cdot B\Leftrightarrow C_{i,j}=\max\{A_{i,k}+B_{k,j}\}$$  
&emsp;&emsp;那么我们对$T$进行$L$次$T\cdot T$，再与初始向量$\boldsymbol v$积起来，即是答案。也就是说，答案为：  
$$\boldsymbol v\cdot T^L$$    
&emsp;&emsp;本质理解：  
&emsp;&emsp;我们的 DP 是在做什么？你会发现，我们实际上是在 AC 自动机的有向图上面做了一个从根出发走$l$步的最长路。   
&emsp;&emsp;那么$T$实际上是一个邻接矩阵，而 ' $\cdot$ ' 的本质是枚举中转点计算出下一步的最长路。  
&emsp;&emsp;其实一次“乘法”就像是做了一次 Floyd ，我们是做了基于 Floyd 的快速幂运算！   
# 代码
```cpp
#include <cstdio>
#include <cstring>

#define Tour( c ) for( int c = 0 ; c < 26 ; c ++ )

typedef long long LL;

const int MAXN = 205, MAXL = 205;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct matrix
{
	LL mat[MAXL][MAXL];
	int n, m;
	matrix() { m = n = 0, memset( mat, 0xc0, sizeof mat ); }
	matrix( const int N, const int M ) { n = N, m = M, memset( mat, 0xc0, sizeof mat ); }
	LL* operator [] ( const int indx ) { return mat[indx]; }
	
	matrix operator * ( matrix b ) 
	{
		matrix ret = matrix( n, b.m );
		for( int i = 1 ; i <= ret.n ; i ++ )
			for( int j = 1 ; j <= ret.m ; j ++ )
				for( int k = 1 ; k <= m ; k ++ )
					ret[i][j] = MAX( ret[i][j], mat[i][k] + b[k][j] );
		return ret;
	}
	
	void operator *= ( matrix b ) { *this = *this * b; }
};

int ch[MAXL][26], fail[MAXL], con[MAXL], q[MAXL];
int a[MAXN];
int N, cnt; LL L;
char S[MAXL];

matrix I( const int n ) { matrix ret = matrix( n, n ); for( int i = 1 ; i <= n ; i ++ ) ret[i][i] = 0; return ret; }

void insert( const int contri )
{
	int p = 0, id;
	for( int i = 1 ; S[i] ; i ++ )
	{
		id = S[i] - 'a';
		if( ! ch[p][id] ) ch[p][id] = ++ cnt;
		p = ch[p][id];
	}
	con[p] += contri;
}

void init()
{
	int h = 1, t = 0, u, v;
	Tour( i ) if( ch[0][i] ) q[++ t] = ch[0][i];
	while( h <= t )
	{
		u = q[h ++];
		Tour( i )
		{
			if( v = ch[u][i] ) fail[v] = ch[fail[u]][i], q[++ t] = v;
			else ch[u][i] = ch[fail[u]][i];
		}
		con[u] += con[fail[u]];
	}
}

matrix qkpow( matrix base, LL indx )
{
	matrix ret = I( base.n );
	while( indx )
	{
		if( indx & 1 ) ret *= base;
		base *= base, indx >>= 1;
	}
	return ret;
}

int main()
{
	read( N ), read( L );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] );
	for( int i = 1 ; i <= N ; i ++ ) scanf( "%s", S + 1 ), insert( a[i] );
	init();
	matrix A = matrix( 1, cnt + 1 ), B = matrix( cnt + 1, cnt + 1 );
	for( int p = 0 ; p <= cnt ; p ++ )
		Tour( c )
			B[p + 1][ch[p][c] + 1] = MAX( B[p + 1][ch[p][c] + 1], ( LL ) con[ch[p][c]] );
	A[1][1] = 0;
	A *= qkpow( B, L );
	LL ans = 0;
	for( int p = 1 ; p <= cnt + 1 ; p ++ ) ans = MAX( ans, A[1][p] );
	write( ans ), putchar( '\n' );
	return 0;
}
```

---

## 作者：SDqwq (赞：2)

## 思路

多串匹配，考虑建出 $\texttt{AC}$ 自动机。

接下来考虑 $\texttt{dp}$。

套路地，设 $f_{i,j}$ 表示已经填了 $i$ 个字符，当前在 $\texttt{AC}$ 自动机中的状态 $j$。那么新的贡献是可以匹配上当前后缀的模式串的权值和。

$\texttt{AC}$ 自动机一个结点到根结点的路径上都是该结点的后缀，所以当前新增的贡献为 $ed_j$。其中 $ed_i$ 表示 $i$ 在 $\texttt{fail}$ 树上到根结点的路径总和。

于是有转移：

$$
f_{i,j}+ed_{go_{j,k}}\to f_{i+1,go_{j,k}}
$$

其中 $k$ 是枚举的新添加的字符。

显然这样转移会超时。发现每次都是从 $i$ 转移到 $i+1$，且第二维转移与第一维无关，取 $\texttt{max}$ 的操作也是满足矩阵乘法的，所以考虑矩阵快速幂优化。

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#define ll long long
using namespace std;
const int N = 205, S = 26;

ll a[N];
string s;

int idx, go[N][S], fa[N];
ll ed[N];
void ins(string s, ll val) {
	int u = 0;
	for (auto i : s) {
		int c = i - 'a';
		if (!go[u][c]) go[u][c] = ++idx;
		u = go[u][c];
	}
	ed[u] += val;
}
void build() {
	queue<int> q;
	for (int i = 0; i < S; i++)
		if (go[0][i]) q.push(go[0][i]);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ed[u] += ed[fa[u]];
		for (int i = 0; i < S; i++) {
			if (go[u][i]) fa[go[u][i]] = go[fa[u]][i], q.push(go[u][i]);
			else go[u][i] = go[fa[u]][i];
		}
	}
}

struct matrix {
	int n, m;
	ll a[N][N];
	
	matrix() {memset(a, -0x3f3f, sizeof(a));}
} base, ans;
matrix operator * (matrix x, matrix y) {
	matrix z;
	z.n = x.n;
	z.m = y.m;
	for (int k = 0; k <= x.m; k++)
		for (int i = 0; i <= x.n; i++)
			for (int j = 0; j <= y.m; j++) z.a[i][j] = max(z.a[i][j], x.a[i][k] + y.a[k][j]);
	return z;
}
matrix quick_pow(matrix a, ll k) {
	matrix res;
	res.n = res.m = a.n;
	for (int i = 0; i <= a.n; i++) res.a[i][i] = 0;
	while (k) {
		if (k & 1) res = res * a;
		a = a * a;
		k >>= 1;
	}
	return res;
}
void init_base() {
	base.n = base.m = idx;
	for (int i = 0; i <= idx; i++)
		for (int j = 0; j < S; j++) base.a[i][go[i][j]] = ed[go[i][j]];
}
void init_ans() {
	ans.n = 0;
	ans.m = idx;
	ans.a[0][0] = 0;
}

int main() {
	int n;
	ll L, mx = 0;
	scanf("%d %lld", &n, &L);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) cin >> s, ins(s, a[i]);
	build();
	init_base();
	init_ans();
	ans = ans * quick_pow(base, L);
	for (int i = 0; i <= idx; i++) mx = max(mx, ans.a[0][i]);
	printf("%lld", mx);
	return 0;
}
```

---

## 作者：Mr_Avalan (赞：1)

题目要求多串匹配，容易想到 AC 自动机，原问题就是在 AC 自动机上跑 dp，首先 AC 自动机上一个节点的权值就是这个节点到根节点的路径权值和，设计状态 $f_{i,j}$ 表示长度为 $i$，在 AC 自动机上的节点 $j$ 时的最大权值，可以得到转移 $f_{i,j}+val_{j,ch_{j,k}}\rightarrow f_{i+1,ch[j][k]}$。

但是注意到时间复杂度里带个 $l$，难以接受。

考虑优化，中间的转移有大量的重复，而且每次只会从 $i$ 转移到 $i+1$，所以可以用矩乘优化。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define ULL unsigned long long
#define err printf("qwq\n");
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define int long long

inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return f*x;
}

const int N=205;

int n,l,cnt,ans;
int ch[N][26],fa[N],ed[N],val[N];
char s[N];

inline void insert(char *s,int len,int val){
	int now=0;
	for(int i=1;i<=len;i++){
		if(!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++cnt;
		now=ch[now][s[i]-'a'];
	}
	ed[now]+=val;
}

inline void get_fa(){
	queue<int> q;
	for(int i=0;i<26;i++) if(ch[0][i]) fa[ch[0][i]]=0,q.push(ch[0][i]);
	while(!q.empty()){
		int u=q.front(); q.pop();
		ed[u]+=ed[fa[u]];
		for(int i=0;i<26;i++){
			if(ch[u][i]) fa[ch[u][i]]=ch[fa[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fa[u]][i];
		}
	}
}

struct matrix{
	int a[N][N];

	inline void init(){ memset(a,-0x3f,sizeof(a));}
	inline void init1(){ memset(a,0,sizeof(a));}

	inline matrix friend operator *(const matrix &x,const matrix &y){
		matrix z; z.init();
		for(int k=0;k<=cnt;k++) for(int i=0;i<=cnt;i++) for(int j=0;j<=cnt;j++) z.a[i][j]=max(z.a[i][j],x.a[i][k]+y.a[k][j]);
		return z;
	}
}a;

inline matrix qpow(matrix x,int y){
	matrix res=x; y--;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}

signed main(){
	#ifdef Mr_Avalan
	freopen("_.in","r",stdin);
	freopen("_.out","w",stdout);
	#endif

	n=read();l=read();
	for(int i=1;i<=n;i++) val[i]=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		insert(s,strlen(s+1),val[i]);
	}
	get_fa();
	a.init();
	for(int i=0;i<=cnt;i++) for(int j=0;j<26;j++) a.a[i][ch[i][j]]=ed[ch[i][j]];
	matrix v=qpow(a,l);
	for(int i=0;i<=cnt;i++) ans=max(ans,v.a[0][i]);
	printf("%lld",ans);

	#ifdef Mr_Avalan
	printf("\n%lldms\n",(LL)(1.0*clock()/CLOCKS_PER_SEC*1000));
	#endif
	return 0;
}
```

---

## 作者：LiveZoom (赞：1)

## Description

[link](https://www.luogu.com.cn/problem/CF696D)

## Solution

首先肯定要把 AC 自动机板子敲了。

先看一下已知短信内容，求答案的过程：

```cpp
int query(string s) {
  int ret = 0, cur = 0;
  for (int i = 0; i < s.size(); ++i) {
    cur = trie[cur][s[i] - 'a'];
    ret += sum[j];
  }
  return ret;
}
```

这里的 `sum` 就是当前节点到 fail 树根节点路径上的权值和，这时就可以发现如果知道了所有长度为 $i$ 的答案，就能推出长度为 $i+1$ 的答案。

形象化的讲就是这样：设 $f[i,j]$ 表示当前的 `cur` 是 $i$，长度为 $j$ 的答案，那么 $f[trie[j,k],j+1]=\max\big\{f[i,j]+sum[trie[i,k]](k=0,1,...,25)\big\}$。

利用这个东西就可以做到 $O(26\times l\times \sum|s|)$。

但是这里的 $l$ 非常大，所以要优化。

注意到长度为 $i+1$ 的答案只会跟长度为 $i$ 的有关，所以就可以利用类似动态 dp 的矩乘优化了。（怎么矩乘就不说了）

时间复杂度：$O((\sum|s|)^3\log l)$，还有个巨大常数，因为 $sum$ 数组也要搞到矩阵里面。

（这些东西包括代码我在赛时都写完了，但是就因为重载运算符时忘记加了个取址符一直玄学 RE，虽然改了还是有个小地方写错了）

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

#define int long long

using namespace std;

const int kMaxN = 505;

// 矩阵乘法 Begin

struct Matrix {
  int n, m, a[kMaxN][kMaxN];

  void inf() {
    memset(a, 0xcf, sizeof(a));
  }

  void set(int _n, int _m) { n = _n, m = _m; }

  void print() {
    for (int i = 1; i <= n; ++i, cerr << '\n') {
      for (int j = 1; j <= m; ++j, cerr << ' ')
        cerr << a[i][j];
    }
  }
} M, S;

Matrix operator *(const Matrix &a, const Matrix &b) {
  assert(a.m == b.n);
  // cerr << "dfaksdflasd " << a.n << ' ' << a.m << '\n';
  Matrix c;
  c.set(a.n, b.m);
  for (int i = 1; i <= c.n; ++i) {
    for (int j = 1; j <= c.m; ++j) {
      c.a[i][j] = -1e18;
      for (int k = 1; k <= a.m; ++k) {
        c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
      }
    }
  }
  return c;
}

Matrix qpow(Matrix bs, int idx) {
  // cerr  << "kkksc03\n";
  Matrix ret = bs;
  --idx;
  // cerr  << "kkksc03\n";
  for (; idx; idx >>= 1, bs = bs * bs) {
    if (idx & 1)
      ret = ret * bs;
  }
  return ret;
}

// 矩阵乘法 End

int n, l;
int a[kMaxN];
string s[kMaxN];
vector<int> G[kMaxN];

// AC自动机 Begin

int tot, trie[kMaxN][26], fail[kMaxN], sum[kMaxN], g[kMaxN];

void ins(string s, int idx) {
  int cur = 0;
  for (int i = 0; i < s.size(); ++i) {
    int k = s[i] - 'a';
    if (!trie[cur][k])
      trie[cur][k] = ++tot;
    cur = trie[cur][k];
  }
  sum[cur] += a[idx];
}

void getfail() {
  queue<int> q;
  for (int i = 0; i < 26; ++i) {
    if (trie[0][i]) {
      q.emplace(trie[0][i]);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      if (trie[u][i]) {
        fail[trie[u][i]] = trie[fail[u]][i];
        q.emplace(trie[u][i]);
      } else {
        trie[u][i] = trie[fail[u]][i];
      }
    }
  }
}

void dfs(int u) {
  for (auto v : G[u]) {
    g[v] = g[u] + sum[v];
    dfs(v);
  }
}

void getg() {
  for (int i = 1; i <= tot; ++i)
    G[fail[i]].emplace_back(i);
  dfs(0);
  for (int i = 1; i <= tot; ++i)
    cerr << g[i] << ' ';
  cerr << '\n';
}

// AC自动机 End

int getpos_f(int x) {
  return x + 1;
}

int getpos_g(int x) {
  return x + tot + 2;
}

void build_matrix() {
  M.set(2 * tot + 2, 2 * tot + 2), S.set(1, 2 * tot + 2);
  M.inf(), S.inf();
  S.a[1][1] = 0;
  for (int i = 0; i <= tot; ++i) {
    int pos = getpos_g(i);
    S.a[1][pos] = g[i];
    // cerr << "***" << g[i] << '\n';
  }
  for (int i = 0; i <= tot; ++i) {
    auto pos_i = getpos_f(i);
    for (int j = 0; j < 26; ++j) {
      int k = trie[i][j];
      auto pos_k = getpos_f(k);
      M.a[pos_i][pos_k] = g[k];
    }
    int pp_i = getpos_g(i);
    M.a[pp_i][pp_i] = 0;
  }
}

void bf() {
  int f[205][205];
  memset(f, 0xcf, sizeof(f));
  f[0][0] = 0;
  for (int i = 0; i < l; ++i) {
    for (int j = 0; j <= tot; ++j) {
      for (int k = 0; k < 26; ++k)
        f[i + 1][trie[j][k]] = max(f[i + 1][trie[j][k]], f[i][j] + g[trie[j][k]]);
    }
  }
  int ans = 0;
  for (int i = 0; i <= tot; ++i)
    ans = max(ans, f[l][i]);
  cout << ans << '\n';
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> l;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> s[i];
    ins(s[i], i);
  }
  getfail();
  getg();
  // bf();
  build_matrix();
  auto rr = qpow(M, l);
  // cerr << rr.n << ' ' << rr.m << '\n' << S.n << ' ' << S.m << '\n';
  Matrix res = S * rr;
  // cerr << "kkk\n";
  int ans = 0;
  for (int i = 1; i <= tot + 1; ++i)
    ans = max(ans, res.a[1][i]);
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：MikukuOvO (赞：1)

考虑建出$AC$自动机，不难想到朴素的$dp$，定义$f[i][j]$表示考虑前$i$个字符，在$AC$自动机上$j$号点的最大权值

$f[i][j]=max_{k->j}f[i-1][k]+val[j]$

发现这个可以矩乘优化，复杂度$n^3log(l)$

```cpp
const int N=205;
const int S=26;

ll n,m,tot;
char a[N];
ll val[N],endpos[N];
int ch[N][S],fail[N];

struct mat
{
    ll c[N][N];
    mat(){memset(c,-LINF,sizeof(c));}
    mat operator*(const mat &x)const
    {
        mat res;
        for(int k=0;k<=tot;++k)
            for(int i=0;i<=tot;++i)
                for(int j=0;j<=tot;++j)
                    res.c[i][j]=max(res.c[i][j],c[i][k]+x.c[k][j]);
        return res;
    }
}base;
void insert(char *s,ll z)
{
    int cur=0,len=strlen(s+1);
    for(int i=1;i<=len;++i)
    {
        int c=s[i]-'a';
        if(!ch[cur][c]) ch[cur][c]=++tot;
        cur=ch[cur][c];
    }
    endpos[cur]+=z;
}
void build()
{
    queue<int>q;
    for(int i=0;i<26;++i)
    {
        int v=ch[0][i];
        if(v) q.push(v);
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        endpos[u]+=endpos[fail[u]];
        for(int i=0;i<26;++i)
        {
            int v=ch[u][i];
            if(v) fail[v]=ch[fail[u]][i],q.push(v);
            else ch[u][i]=ch[fail[u]][i];
        }
    }
}
void init()
{
    for(int i=0;i<=tot;++i)
    {
        for(int j=0;j<26;++j)
        {
            int cur=ch[i][j];
            base.c[i][cur]=endpos[cur];
        }
    }
}
mat qpow(mat x,ll y)
{
    mat res;
    for(int i=0;i<=tot;++i) res.c[i][i]=0;
    while(y)
    {
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}
int main()
{
    fio();
    gi(n,m);
    for(int i=1;i<=n;++i) gi(val[i]);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a+1);
        insert(a,val[i]);
    }
    build();
    init();
    base=qpow(base,m);
    ll ans=0;
    for(int i=0;i<=tot;++i) ans=max(ans,base.c[0][i]);
    print(ans);
    end();
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Tomori0505/p/18860131)

前置知识：AC 自动机。

### Solution

看到子串出现次数，首先会想到建 AC 自动机，这样我们就处理掉了子串出现次数的问题。

但是它带了一个权值 $val_i$，考虑 dp，记 $f_{i,j}$ 表示当前构造到了长度 $i$，在自动机上以 $j$ 节点结尾的最大价值，记录每个串的结尾 $end$，直接 $end \leftarrow end + val_i$ 就可以更方便得到一个子串的权值，只需要在 $fail$ 树上子树和。

那么我们肯定是从根往子节点一路跳，就有：

$$
f_{i+1,son_{j,x}} \leftarrow \max\{f_{i,j} + val_{son_{j,x}}\}
$$

但是你看到 $l\leq 10^{14}$，这样转移瞬间爆炸。

诶！当我们转移的时候有且仅有 $i \to i + 1$，那么就可以用矩乘快速幂来优化（其实转移跟遍历图差不多，从上一个状态走到下一个）。

为符合转移的运算我们把矩乘重定义为加法然后取 $\max$，初始矩阵 $mat_{i,son_{i,j}} = end_{son_{i,j}}$，想要的答案是 $\max\limits_{i=0}^{N}{mat_{0,i}}$。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define fail(now) Amt[now].fail
#define end(now) Amt[now].end
#define son(now,x) Amt[now].son[x]

using namespace std;
const int MAXN = 210;
const int MAXS = 200010;

int N, M, cnt, ans;
int val[MAXN];
string Style;

struct Amton {
	int son[26];
	int fail, end;
} Amt[MAXS];

struct Matt {
	int mat[MAXN][MAXN];
	
	Matt() { memset (mat, -0x3f, sizeof(mat)); }
	Matt operator * (const Matt &s) const {
		Matt res = Matt();
		for (int k = 0; k <= cnt; k ++) {
			for (int i = 0; i <= cnt; i ++) {
				for (int j = 0; j <= cnt; j ++)
					res.mat[i][j] = max (res.mat[i][j], mat[i][k] + s.mat[k][j]);
			}
		}
		return res;
	}
} base, final;

Matt binpow (Matt x, int p) {
	Matt res = x;
	for (--p; p; p >>= 1) {
		if (p & 1)
			res = res * x;
		x = x * x;
	}
	return res;
}

inline void InsertString (int val) {
	int now = 0, len = Style.length();
	for (int i = 0; i < len; i ++) {
		int chVal = Style[i] - 'a';
		if (!son(now, chVal))
			son(now, chVal) = ++cnt;
		now = son(now, chVal);
	}
	end(now) += val;
}

inline void GetFailPointer() {
	queue<int> q;
	for (int i = 0; i < 26; i ++) {
		if (son(0, i))
			q.emplace (son(0, i));
	}
	while (!q.empty()) {
		int now = q.front(); q.pop();
		end(now) += end(fail(now));
		for (int i = 0; i < 26; i ++) {
			if (!son(now, i))
				son(now, i) = son(fail(now), i);
			else {
				fail(son(now, i)) = son(fail(now), i);
				q.emplace (son(now, i));
			}
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> N >> M, base = Matt();
    for (int i = 1; i <= N; i ++) cin >> val[i];
    for (int i = 1; i <= N; i ++) cin >> Style, InsertString(val[i]);
    GetFailPointer();
    for (int i = 0; i <= cnt; i ++) {
    	for (int j = 0; j < 26; j ++)
    		base.mat[i][son(i, j)] = end(son(i, j));
	}
	final = binpow (base, M);
    ans = -0x7f7f7f7f7f7f;
    for (int i = 0; i <= cnt; i ++)
    	ans = max (ans, final.mat[0][i]);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑假若 $T$ 确定了怎么比较方便地算出贡献。

不难发现可以给所有 $S$ 建立 AC 自动机后在 fail 树上滚一个根路径和，然后把 $T$ 丢到自动机上匹配，每走到一个点就算上这个点的根路径和。

对 $T$ 最优化考虑把这个过程用 dp 描述，不妨 $dp_{i,j}$ 表示走 $i$ 步到 $j$ 的最大贡献，不难发现转移是一个 $\max +$ 的形式，直接使用 $\max +$ 矩阵快速幂优化即可做到 $O((\sum |S_i|)^3 \log l)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 214;
int tr[maxn][26];
int fail[maxn],tot;
int w[maxn];
void ins(string s,int v){
    int u=0;
    for(char c:s){
        if(tr[u][c-'a']==0) tr[u][c-'a']=++tot;
        u=tr[u][c-'a'];
    }
    w[u]+=v;
}
void build(){
    queue<int> q;
    for(int i=0;i<26;i++)
        if(tr[0][i]) q.push(tr[0][i]);
    while(q.size()>0){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
            else tr[u][i]=tr[fail[u]][i];
        }
    }
}
vector<int> e[maxn];
void dfs(int u){
	for(int v:e[u]){
		w[v]+=w[u];
		dfs(v);
	}
}
int n,l;
const int inf = 1e18;
int wei[maxn];
struct matrix{
	int n,m;
	int a[maxn][maxn];
	matrix(int N=0,int M=0){
		n=N,m=M;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++) a[i][j]=-inf;
	}
	matrix operator*(matrix &x){
		matrix res=matrix(n,x.m);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				for(int k=0;k<=x.m;k++) res.a[i][k]=max(res.a[i][k],a[i][j]+x.a[j][k]);
			}
		}
		return res;
	}
}E;
matrix qpow(matrix a,int b){
	if(b==0) return E;
	if(b==1) return a;
	matrix res=qpow(a,b/2);
	res=res*res;
	if(b%2==1) res=res*a;
	return res;
}
signed main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++) cin>>wei[i];
	for(int i=1;i<=n;i++){
		string S;
		cin>>S;
		ins(S,wei[i]);
	}
	build();
	for(int i=1;i<=tot;i++) e[fail[i]].push_back(i);
	dfs(0);
	E=matrix(tot,tot);
	for(int i=0;i<=tot;i++) E.a[i][i]=0;
	matrix base=matrix(tot,tot);
	for(int i=0;i<=tot;i++){
		for(int ch=0;ch<26;ch++) base.a[i][tr[i][ch]]=w[tr[i][ch]];
	}
	matrix t=qpow(0,tot);
	t.a[0][0]=0;
	base=qpow(base,l);
	matrix c=t*base;
	int ans=0;
	for(int i=0;i<=tot;i++) ans=max(ans,c.a[0][i]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析
给定 $n$ 个模式串，求构造一个长度为 $l$ 的字符串满足没出线一次模式串 $i$ 就加上 $a_i$ 权值，求最大权值。

对于多模式串的匹配问题，我们先建出 AC 自动机，然后尝试在上面 dp 一下。设 $f_{i,j}$ 为长度为 $i$ 的字符串最大权值，且在 $j$ 号节点结尾，那么 $f_{i+1,tr_{j,k}}=f_{i,j}+val_{tr_{j,k}}$，我们发现这个方程的第一维都是一个一个递推上去的，所以考虑矩阵快速幂优化。时间复杂度 $O(n^3\log l)$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int M=200+10;

int val[N];

int tr[N][26],cnt;
int fail[N];

void insert(string s,int v){
	int u=0;
	for(int i=0;i<s.size();i++){
		int v=s[i]-'a';
		if(!tr[u][v]) tr[u][v]=++cnt;
		u=tr[u][v];
	}
	val[u]+=v;
}

void build(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(tr[0][i]) q.push(tr[0][i]);
	}
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<26;i++){
			if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i]=tr[fail[u]][i];
		}
		val[u]+=val[fail[u]];
	}
}

int tmp[N];

struct matrix{//注意这里的矩阵乘法要改成加法取max，为了满足dp方程
	int mat[M][M];
	int n,m;
	
	friend matrix operator *(matrix a,matrix b){
		matrix tmp; tmp.n=a.n; tmp.m=b.m;
		memset(tmp.mat,0xc0,sizeof tmp.mat);
		for(int i=1;i<=tmp.n;i++){
			for(int j=1;j<=tmp.m;j++){
				for(int k=1;k<=a.m;k++){
					tmp.mat[i][j]=max(tmp.mat[i][j],a.mat[i][k]+b.mat[k][j]);
				}
			}
		}
		return tmp;
	}
};

matrix qpow(matrix a,int index){
	matrix ans; ans.n=ans.m=a.n;
	memset(ans.mat,0xc0,sizeof ans.mat);
	for(int i=1;i<=ans.n;i++) ans.mat[i][i]=0;
	while(index){
		if(index&1) ans=(ans*a);
		a=(a*a); index>>=1;
	}
	return ans;
}

inline void fake_main(){
	int n,l; cin>>n>>l;
	for(int i=1;i<=n;i++) cin>>tmp[i];
	for(int i=1;i<=n;i++){
		string s; cin>>s;
		insert(s,tmp[i]);
	}
	build();
	
	matrix a,b;
	a.n=1; a.m=cnt+1; b.n=b.m=cnt+1;
	memset(a.mat,0xc0,sizeof a.mat);
	memset(b.mat,0xc0,sizeof b.mat);
	for(int i=0;i<=cnt;i++){//建立转移矩阵
		for(int j=0;j<26;j++){
			b.mat[i+1][tr[i][j]+1]=max(b.mat[i+1][tr[i][j]+1],val[tr[i][j]]);
		}
	}
	a.mat[1][1]=0;
	a=a*qpow(b,l);
	int ans=0;
	for(int i=1;i<=cnt+1;i++) ans=max(ans,a.mat[1][i]);
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：QZJ666 (赞：0)

题目是多串匹配，很容易想到 $\texttt{AC}$ 自动机

那么我们每一次到达一个点对答案的贡献就是在fail树上从根节点到这个点上点的权值和，这个在求 $fail$ 的时候可以顺带算出来

现在问题就转化成了在 $\texttt{AC}$ 自动机上跳 $l$ 步可以得到的权值最大值

考虑设一个 $\texttt{dp}$ 状态，$f_{i,j}$ 表示已经跳了 $i$ 步，现在在位置 $j$。很容易列出状态

$f_{i+1,go_{j,k}}=f_{i,j}+sum_{go_{j,k}}$

其中 $k$ 是新添加的字符

答案就是所有 $f_{l,s}$ 求和

因为 $l$ 的范围比较大，这样肯定会超时，但是发现这个状态只有取 $max$ 和求和，于是可以广义矩阵乘法加速，最后时间复杂度 $\mathcal{O}(s^3\log n)$

下面是代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int go[205][26],fail[205],tot,n;
ll ed[205];
void insert(char *s,int len,ll v){
	int now=0;
	for(int i=1;i<=len;i++){
		if(!go[now][s[i]-'a'])go[now][s[i]-'a']=++tot;
		now=go[now][s[i]-'a'];
	}
	ed[now]+=v;
}
void get_fail(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(go[0][i])fail[go[0][i]]=0,q.push(go[0][i]);
	}
	while(!q.empty()){
		int tp=q.front();
		q.pop();
		ed[tp]+=ed[fail[tp]];
		for(int i=0;i<26;i++){
			if(go[tp][i]){
				fail[go[tp][i]]=go[fail[tp]][i],q.push(go[tp][i]);
			}
			else{
				go[tp][i]=go[fail[tp]][i];
			}
		}
	}
}
ll val[205];
ll l;
char s[205];
struct matrix{
	ll arr[205][205];
	void init(){
		memset(arr,-0x3f,sizeof arr);
	}
	void init1(){
		memset(arr,0,sizeof arr);
	}
	void print(){
		for(int i=0;i<=tot;i++){
			for(int j=0;j<=tot;j++)cout<<arr[i][j]<<' ';puts("");
		}
	}
};
matrix mul(matrix a,matrix b){
	matrix c;
	c.init();
	for(int k=0;k<=tot;k++)
		for(int i=0;i<=tot;i++)
			for(int j=0;j<=tot;j++){
				c.arr[i][j]=max(c.arr[i][j],a.arr[i][k]+b.arr[k][j]);
			}
	return c;
}
matrix ksm(matrix a,ll m){
	matrix ans;
	ans=a;
	m--;
	while(m){
		if(m&1ll)ans=mul(ans,a);
		a=mul(a,a);
		m>>=1ll;
	}
	return ans;
}
int main(){
	scanf("%d%lld",&n,&l);
	for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		insert(s,strlen(s+1),val[i]);
	}
	get_fail();
	matrix a,b;
	a.init();
	for(int i=0;i<=tot;i++){
		for(int j=0;j<26;j++)a.arr[i][go[i][j]]=ed[go[i][j]];
	}
	matrix v=ksm(a,l);
	ll ans=0;
	for(int i=0;i<=tot;i++)ans=max(ans,v.arr[0][i]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Acetyl (赞：0)

这一题明显是AC自动机上DP，也很容易想到DP状态：dp[i][j]=考虑到最终字符串的第i个位置，在AC自动机上的第j个点时的最大答案。

不过，很可惜，l是10的14次幂，很明显不能直接DP。

所以需要矩阵快速幂优化。由于j维度最大只有200，所以是可行的。

代码如下：

``` cpp
//头文件省略
#define LL long long
#define pb push_back
#define pob pop_back
#define mp make_pair
#define FILL(a,v) memset((void*)a,v,sizeof(a))
#define FILL0(a) FILL(a,0)
#define FILL1(a) FILL(a,-1)
#define FILLBIG(a) FILL(a,0x3f)
#define ALL(a) (a).begin(),(a).end()
#define Inf ((int)0x3f3f3f3f)
#define INF ((long long)0x3f3f3f3f3f3f3f3f)
#define Mod 1000000007
#define foreach(it,x) for(__typeof(x.begin()) it=x.begin();it!=x.end();it++)
#define FOR(i,x) for(int i=0;i<x;i++)
#define RFOR(i,x) for(int i=x-1;i>=0;i--)
#define FFOR(i,a,b) for(int i=a;i<b;i++)
#define FRFOR(i,a,b) for(int i=a-1;i>=b;i--)
#define SZ(a) ((int)(a).size())
#define FI first
#define SE second
#define OVER(...) return printf(__VA_ARGS__),0
#define fastio ios::sync_with_stdio(0)
#define filei(f) freopen(f,"r",stdin)
#define fileo(f) freopen(f,"w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define MASK(a) (1<<(a))
#define MASKX(x,a) ((x)<<(a))
#define BIT(a,b) (((a)>>(b))&1)
#define cddx(a) priority_queue<a >
#define cxdd(a) priority_queue<a,vector<a >,greater<a > >
#define deval(a) {cerr<<#a<<" = "<<a<<endl;}
#define dearr(be,en) {cerr<<#be;cerr<<" = {";for(auto i=be;i!=en;i++)cerr<<' '<<*i;cerr<<" }\n";}
#define reg register
#define prtime eprintf("\n\nTime used: %dms\n",clock());
#define PI 3.1415926535897932384626
#define TODEG(a) (a*180/PI)
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long UINT;
typedef unsigned int uint;
typedef long long INT;
typedef long double ldouble;
typedef pair<INT,INT> PII;
typedef stringstream sst;
typedef istringstream iss;
typedef vector<int> vint;
typedef vector<INT> VINT;
typedef vector<pii> vpii;
typedef vector<PII> VPII;
typedef priority_queue<int> pqi;
typedef priority_queue<INT> PQI;
typedef priority_queue<pii> pqp;
typedef priority_queue<PII> PQP;
typedef priority_queue<int,vint,greater<int> > xqi;
typedef priority_queue<INT,VINT,greater<INT> > XQI;
typedef priority_queue<pii,vpii,greater<pii> > xqp;
typedef priority_queue<PII,VPII,greater<PII> > XQP;
struct fastIO
{
	inline fastIO operator>>(int& num)
	{
		num=0;
		char c=getchar();
		while(c!='-'&&(c<'0'||c>'9'))c=getchar();
		bool foo=0;
		if(c=='-')
		{
			foo=1;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			num=(num<<3)+(num<<1)+c-'0';
			c=getchar();
		}
		if(foo)num=-num;
		return *this;
	}
	inline fastIO operator>>(INT& num)
	{
		num=0;
		char c=getchar();
		while(c!='-'&&(c<'0'||c>'9'))c=getchar();
		bool foo=0;
		if(c=='-')
		{
			foo=1;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			num=(num<<3)+(num<<1)+c-'0';
			c=getchar();
		}
		if(foo)num=-num;
		return *this;
	}
	inline fastIO operator>>(float& num)
	{
		scanf("%f",&num);
		return *this;
	}
	inline fastIO operator>>(double& num)
	{
		scanf("%lf",&num);
		return *this;
	}
	inline fastIO operator>>(long double& num)
	{
		scanf("%Lf",&num);
		return *this;
	}
	inline fastIO operator>>(char& num)
	{
		num=getchar();
		while(num==' '||num=='\n')num=getchar();
		return *this;
	}
	inline fastIO operator>>(char* num)
	{
		int cnt=0;
		char c=getchar();
		while(c==' '||c=='\n')c=getchar();
		while(c!=' '&&c!='\n')
		{
			num[cnt++]=c;
			c=getchar();
		}
		num[cnt]=0;
		return *this;
	}
	inline fastIO operator>>(string& num)
	{
		cin>>num;
		return *this;
	}
	inline void printInt(const int& num)
	{
		if(num<10)
		{
			putchar(num+'0');
			return;
		}
		printInt(num/10);
		putchar((num%10)+'0');
	}
	inline void printINT(const INT& num)
	{
		if(num<10)
		{
			putchar(num+'0');
			return;
		}
		printINT(num/10);
		putchar((num%10)+'0');
	}
	inline fastIO operator<<(const int& num)
	{
		if(num<0)putchar('-'),printInt(-num);
		else printInt(num);
		return *this;
	}
	inline fastIO operator<<(const INT& num)
	{
		if(num<0)putchar('-'),printINT(-num);
		else printINT(num);
		return *this;
	}
	inline fastIO operator<<(const float& num)
	{
		printf("%.10f",num);
		return *this;
	}
	inline fastIO operator<<(const double& num)
	{
		printf("%.16lf",num);
		return *this;
	}
	inline fastIO operator<<(const long double& num)
	{
		printf("%.20Lf",num);
		return *this;
	}
	inline fastIO operator<<(const char& num)
	{
		putchar(num);
		return *this;
	}
	inline fastIO operator<<(const char* num)
	{
		for(int i=0;num[i];i++)
			putchar(num[i]);
		return *this;
	}
	inline fastIO operator<<(const string& num)
	{
		cout<<num;
		return *this;
	}
}fio;

int nei[205][26];
int fail[205];
string s[205];
int to[205];
int cnt=1;

void add(const string& S){
	int now=0;
	string cur="";
	for(int i=0;i<SZ(S);i++){
		if(!nei[now][S[i]-'a']){
			nei[now][S[i]-'a']=cnt++;
		}
		now=nei[now][S[i]-'a'];
		cur+=S[i];
		s[now]=cur;
	}
}

void build(){
	fail[0]=0;
	queue<int> q;
	for(int i=0;i<26;i++){
		if(nei[0][i]){
			q.push(nei[0][i]);
		}
	}
	while(SZ(q)){
		int x=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(nei[x][i]){
				q.push(nei[x][i]);
				fail[nei[x][i]]=nei[fail[x]][i];
			}else{
				nei[x][i]=nei[fail[x]][i];
			}
		}
	}
}

INT pw[60][205][205],ans[205][205],c[205][205],bg[205][205];
void times(INT a[][205],INT b[][205]){
	for(int i=0;i<cnt;i++){
		for(int j=0;j<cnt;j++){
			c[i][j]=-INF;
		}
	}
	for(int i=0;i<cnt;i++){
		for(int j=0;j<cnt;j++){
			for(int k=0;k<cnt;k++){
				if(a[i][k]>=0){
					c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
				}
			}
		}
	}
}

int n;
INT m;
int ass[205];
string ss[205];

int main(){
	fio>>n>>m;
	for(int i=0;i<n;i++){
		fio>>ass[i];
	}
	for(int i=0;i<n;i++){
		fio>>ss[i];
		add(ss[i]);
	}
	build();//构建AC自动机
	for(int i=0;i<cnt;i++){
		for(int j=0;j<n;j++){
			if(SZ(s[i])>=SZ(ss[j])&&s[i].substr(SZ(s[i])-SZ(ss[j]))==ss[j]){
				to[i]+=ass[j];
			}
		}
	}
	for(int i=0;i<cnt;i++){
		for(int j=0;j<cnt;j++){
			bg[i][j]=ans[i][j]=-INF;
			for(int k=0;k<26;k++){
				if(nei[i][k]==j){
					bg[i][j]=to[j];
				}
			}
		}
	}
	ans[0][0]=0;
	memcpy(pw[0],bg,sizeof(bg));
	for(int i=1;i<60;i++){
		times(pw[i-1],pw[i-1]);
		memcpy(pw[i],c,sizeof(c));
	}
	for(int i=0;i<60;i++){
		if(BIT(m,i)){
			times(ans,pw[i]);//矩阵快速幂计算答案
			memcpy(ans,c,sizeof(c));
		}
	}
	INT Ans=0;
	for(int i=0;i<cnt;i++){
		Ans=max(Ans,ans[0][i]);
	}
	fio<<Ans<<endl;
	return 0;
}
```

---

