# Multidimensional Queries

## 题目描述

给定一个 $n$ 个点的数组 $a$，每个点位于 $k$ 维空间中。两点 $a_x$ 和 $a_y$ 之间的距离定义为 $ \sum\limits_{i=1}^{k} |a_{x,i} - a_{y,i}| $（即曼哈顿距离）。

你需要处理 $q$ 个如下两种类型的操作：

- $1\ i\ b_1\ b_2\ \dots\ b_k$ —— 将第 $i$ 个点的坐标设为 $(b_1, b_2, \dots, b_k)$；
- $2\ l\ r$ —— 查询区间 $[l, r]$ 内任意两点 $a_i$ 和 $a_j$ 之间的最大距离（$l \leq i, j \leq r$）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
4 5
5 6
7
2 1 5
2 1 3
2 3 5
1 5 -1 -2
2 1 5
1 4 -1 -2
2 1 5
```

### 输出

```
8
4
4
12
10
```

# 题解

## 作者：LJC00118 (赞：11)

习惯性的把曼哈顿距离的绝对值拆出来，用二进制表示

$ 31 $ 的二进制表示是 $ 11111 $，表示 $ 5 $ 维的一个点的坐标加入的正负情况都为正（即 $ x[1] - y[1] + x[2] - y[2] + x[3] - y[3] + x[4] - y[4] + x[5] - y[5] $

$ 29 $ 的二进制表示是 $ 11101 $，表示 $ x[1] - y[1] + x[2] - y[2] + x[3] - y[3] - x[4] + y[4] + x[5] - y[5] $ （注意 $ x[4] $ 和 $ y[4] $ 的符号变化

那么我们要求的就是 $ max\ \{f[0] + f[31], f[1] + f[30], f[2] + f[29]...\} $

用线段树维护即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
   print(x); putchar(t);
}

const int N = 2e5 + 5;

struct ele { int f[32]; };

struct Node {
    int l, r; ele val;
}p[N << 2];

int t[N][5];
int n, m, k;

ele merge(ele a, ele b) {
    for(register int i = 0; i < (1 << k); i++) a.f[i] = max(a.f[i], b.f[i]);
    return a;
}

void build(int u, int l, int r) {
    p[u].l = l; p[u].r = r;
    if(l == r) {
        for(register int i = 0; i < (1 << k); i++) {
            p[u].val.f[i] = 0;
            for(register int j = 0; j < k; j++) {
                if(i & (1 << j)) p[u].val.f[i] += t[l][j];
                else p[u].val.f[i] -= t[l][j];
            }
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
    p[u].val = merge(p[u << 1].val, p[u << 1 | 1].val);
}

void change(int u, int l) {
    if(p[u].l == p[u].r) {
        for(register int i = 0; i < (1 << k); i++) {
            p[u].val.f[i] = 0;
            for(register int j = 0; j < k; j++) {
                if(i & (1 << j)) p[u].val.f[i] += t[l][j];
                else p[u].val.f[i] -= t[l][j];
            }
        }
        return;
    }
    int mid = (p[u].l + p[u].r) >> 1;
    if(mid >= l) change(u << 1, l); else change(u << 1 | 1, l);
    p[u].val = merge(p[u << 1].val, p[u << 1 | 1].val);
}

ele query(int u, int l, int r) {
    if(p[u].l >= l && p[u].r <= r) return p[u].val;
    int mid = (p[u].l + p[u].r) >> 1;
    if(mid >= l && mid + 1 <= r) return merge(query(u << 1, l, r), query(u << 1 | 1, l, r));
    else if(mid >= l) return query(u << 1, l, r); return query(u << 1 | 1, l, r);
}

int main() {
    read(n); read(k);
    for(register int i = 1; i <= n; i++) {
        for(register int j = 0; j < k; j++) {
            read(t[i][j]);
        }
    }
    build(1, 1, n); read(m);
    while(m--) {
        int opt; read(opt);
        if(opt == 1) {
            int i; read(i);
//			cout << i << " " << k << endl;
            for(register int j = 0; j < k; j++) read(t[i][j]);
            change(1, i);
        }
        if(opt == 2) {
            int l, r; read(l); read(r);
            ele res = query(1, l, r); int ans = 0;
            for(register int i = 0; i < (1 << (k - 1)); i++) ans = max(ans, res.f[i] + res.f[(1 << k) - 1 - i]);
            print(ans, '\n');
        }
    }
    return 0;
}
```

---

## 作者：ouuan (赞：5)

> 为了便于扩展到高维，本文中点的坐标统一用 $(x_1,x_2,\cdots,x_k)$ 表示，即使二维也一样。

$\begin{aligned}&\text{两个二维点之间的曼哈顿距离}\\=&|x_1-y_1|+|x_2-y_2|\\=&\max(x_1-y_1,y_1-x_1)+\max(x_2-y_2,y_2-x_2)\\=&\max(x_1-y_1+x_2-y_2,x_1-y_1+y_2-x_2,y_1-x_1+x_2-y_2,y_1-x_1+y_2-x_2)\end{aligned}$

用 $s[x][0]$ 表示 $-x_1-x_2$，$s[x][1]$ 表示 $-x_1+x_2$，$s[x][2]$ 表示 $x_1-x_2$，$s[x][3]$ 表示 $x_1+x_2$，那么 $\text{两个二维点之间的曼哈顿距离}=\max\{s[x][j]-s[y][j]\}(j\in[0,3])$ 。

转换成这样之后，二维平面上一些点之间的最大曼哈顿距离就可以求了：$\max\{\max\{s[a_i][j]\}-\min\{s[a_i][j]\}\}$

上面这个公式的意思是，对于每个 $j$ 把 $s[a_{1..n}][j]$ 求出来，并取最大值和最小值相减，把不同的 $j$ 的“最大值和最小值相减”取 $\max$ 。

至于高维，二进制枚举 $x_i$ 的正负，也就是说 $s[x][j]=\sum_{i=1}^kx_i\times(j\text{ and } 2^{i-1}?1:-1)$，然后按一样的做法就可以了。

如果到这里为止你看懂了，你就可以 AC [P1648 看守](https://www.luogu.org/problemnew/show/P1648) 了。

至于本题，需要支持区间查询、单点修改，套上任何一种支持修改的 RMQ（比如线段树）即可。

但是套有不同的套法，直接放在一棵线段树里，每个节点存 $2^k$ 个最大/最小值，修改/询问时就只用在线段树上查找一次；如果拆成 $32$ 棵线段树，常数就会非常大。

一棵线段树的 $1.1s$ 解法：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF=0x3f3f3f3f;

inline int read()
{
    char c;int out=0,f=1;
    for (c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());if (c=='-'){f=-1;c=getchar();}
    for (;c>='0'&&c<='9';c=getchar()){out=(out<<3)+(out<<1)+c-'0';}return out*f;
}
void write(int x)
{
	if (x<0){putchar('-');write(-x);return;}
    if (x>9){write(x/10);}putchar(x%10+'0');
}

#define now t[cur]
#define ls t[cur<<1]
#define rs t[cur<<1|1]

const int N=200010;

int n,k,q,a[N][5];

struct Val
{
	int maxx[32],minn[32];
	Val()
	{
		int i;
		for (i=0;i<(1<<k);++i)
		{
			maxx[i]=-INF;
			minn[i]=INF;
		}
	}
};

struct Node
{
	int left,right;
	Val val;
} t[N<<2];

void build(int cur,int l,int r);
void mnode(int cur);
void modify(int cur,int p);
Val query(int cur,int l,int r);
Val merge(Val x,Val y);

int main()
{
	int i,j,pos,l,r,ans;
	Val v;
	
	n=read();
	k=read();
	
	for (i=1;i<=n;++i)
	{
		for (j=0;j<k;++j)
		{
			a[i][j]=read();
		}
	}
	
	build(1,1,n+1);
	
	q=read();
	
	while (q--)
	{
		if (read()==1)
		{
			pos=read();
			for (i=0;i<k;++i)
			{
				a[pos][i]=read();
			}
			modify(1,pos);
		}
		else
		{
			ans=0;
			l=read();
			r=read();
			v=query(1,l,r+1);
			for (i=0;i<(1<<k);++i)
			{
				ans=max(ans,v.maxx[i]-v.minn[i]);
			}
			write(ans);
			putchar('\n');
		}
	}
	
	return 0;
}

void mnode(int cur)
{
	int i,j;
	for (i=0;i<(1<<k);++i)
	{
		now.val.maxx[i]=0;
		for (j=0;j<k;++j)
		{
			now.val.maxx[i]+=((i&(1<<j))?1:-1)*a[now.left][j];
		}
		now.val.minn[i]=now.val.maxx[i];
	}
}

void build(int cur,int l,int r)
{
	now.left=l;
	now.right=r;
	if (l==r-1)
	{
		mnode(cur);
	}
	else
	{
		build(cur<<1,l,(l+r)>>1);
		build(cur<<1|1,(l+r)>>1,r);
		now.val=merge(ls.val,rs.val);
	}
}

void modify(int cur,int p)
{
	if (now.left==p&&now.right==p+1)
	{
		mnode(cur);
	}
	else
	{
		if (p<ls.right)
		{
			modify(cur<<1,p);
		}
		else
		{
			modify(cur<<1|1,p);
		}
		now.val=merge(ls.val,rs.val);
	}
}

Val query(int cur,int l,int r)
{
	if (l>=now.right||r<=now.left)
	{
		return Val();
	}
	if (l<=now.left&&r>=now.right)
	{
		return now.val;
	}
	else
	{
		return merge(query(cur<<1,l,r),query(cur<<1|1,l,r));
	}
}

Val merge(Val x,Val y)
{
	Val out;
	int i;
	for (i=0;i<(1<<k);++i)
	{
		out.minn[i]=min(x.minn[i],y.minn[i]);
		out.maxx[i]=max(x.maxx[i],y.maxx[i]);
	}
	return out;
}
```

拆成 $32$ 棵线段树的 $4.2s$ 解法：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF=0x3f3f3f3f;

inline int read()
{
    char c;int out=0,f=1;
    for (c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());if (c=='-'){f=-1;c=getchar();}
    for (;c>='0'&&c<='9';c=getchar()){out=(out<<3)+(out<<1)+c-'0';}return out*f;
}
void write(int x)
{
	if (x<0){putchar('-');write(-x);return;}
    if (x>9){write(x/10);}putchar(x%10+'0');
}

#define now t[cur]
#define ls t[cur<<1]
#define rs t[cur<<1|1]

const int N=200010;

struct Node
{
	int left,right,maxx,minn;
};

int n,k,q,a[N][5];

struct segTree
{
	int b[N];
	Node t[N<<2];
	void build(int cur,int l,int r)
	{
		now.left=l;
		now.right=r;
		if (l==r-1)
		{
			now.maxx=now.minn=b[l];
		}
		else
		{
			build(cur<<1,l,(l+r)>>1);
			build(cur<<1|1,(l+r)>>1,r);
			pushup(cur);
		}
	}
	void modify(int cur,int p,int x)
	{
		if (p==now.left&&p==now.right-1)
		{
			now.minn=now.maxx=x;
		}
		else
		{
			if (p<ls.right)
			{
				modify(cur<<1,p,x);
			}
			else
			{
				modify(cur<<1|1,p,x);
			}
			pushup(cur);
		}
	}
	int qmax(int cur,int l,int r)
	{
		if (l>=now.right||r<=now.left)
		{
			return -INF;
		}
		if (l<=now.left&&r>=now.right)
		{
			return now.maxx;
		}
		else
		{
			return max(qmax(cur<<1,l,r),qmax(cur<<1|1,l,r));
		}
	}
	int qmin(int cur,int l,int r)
	{
		if (l>=now.right||r<=now.left)
		{
			return INF;
		}
		if (l<=now.left&&r>=now.right)
		{
			return now.minn;
		}
		else
		{
			return min(qmin(cur<<1,l,r),qmin(cur<<1|1,l,r));
		}
	}
	void pushup(int cur)
	{
		now.minn=min(ls.minn,rs.minn);
		now.maxx=max(ls.maxx,rs.maxx);
	}
} s[32];

int main()
{
	int i,j,l,r,ans;
	
	n=read();
	k=read();
	
	for (i=1;i<=n;++i)
	{
		for (j=0;j<k;++j)
		{
			a[i][j]=read();
		}
		for (j=0;j<(1<<k);++j)
		{
			for (l=0;l<k;++l)
			{
				if (j&(1<<l))
				{
					s[j].b[i]+=a[i][l];
				}
				else
				{
					s[j].b[i]-=a[i][l];
				}
			}
		}
	}
	
	for (i=0;i<(1<<k);++i)
	{
		s[i].build(1,1,n+1);
	}
	
	q=read();
	
	while (q--)
	{
		if (read()==1)
		{
			i=read();
			for (j=0;j<k;++j)
			{
				a[i][j]=read();
			}
			for (j=0;j<(1<<k);++j)
			{
				s[j].b[i]=0;
				for (l=0;l<k;++l)
				{
					if (j&(1<<l))
					{
						s[j].b[i]+=a[i][l];
					}
					else
					{
						s[j].b[i]-=a[i][l];
					}
				}
				s[j].modify(1,i,s[j].b[i]);
			}
		}
		else
		{
			l=read();
			r=read()+1;
			ans=0;
			for (i=0;i<(1<<k);++i)
			{
				ans=max(ans,s[i].qmax(1,l,r)-s[i].qmin(1,l,r));
			}
			write(ans);
			putchar('\n');
		}
	}
	
	return 0;
}
```

---

## 作者：lukelin (赞：4)

### 前言
**更好的阅读体验**:>[蒟蒻博客的传送门](https://www.cnblogs.com/linzhengmin/p/11351470.html)<  
如果一个点记为$a$，那么在本文中$a_x$表示$a$在第$x$维空间上的坐标值
### 题解
这题的思路珂以说非常巧妙(原谅我又用了这个"珂")，  
我们知道曼哈顿距离是$\sum|a_i-b_i|$，$|a_i-b_i|$其实也珂以看作是$(a_i-b_i)$和$(b_i-a_i)$中较大的那个。  
根据上面的分析曼哈顿距离珂以看作是$\sum max(a_i-b_i,b_i-a_i)$，
继续分析珂以得出，每个点在每一维度上要应用的无非只有两种情况$a_i$，$-a_i$。  
由于区间内取两点求最小值要求每个点都是完整的(就是说一旦选取了该点那么必定会用到该点所有维度上的坐标)，那么也就意味着对于一个点，它最多可能(仅为可能)用到的状态会是$2^k$次方个。  
本题坐标只有5维，电脑不是人脑，那么显然我们珂以枚举解决以上问题。
那么求曼哈顿距离的时候便利所有$a_i$的正负性，显然若$a_i$为正，$b_i$即负；a_i为负，$b_i$为正。
如果用一个二进制状态来压缩，1表示$a_i$为正，0表示$a_i$为负，显然任意一组关于$a$的状态，记为$sta$，  
对应的$b$的装态表示为$(((2^k) - 1) - sta)$也珂以记作$(((2^k) - 1)\ \textbf{xor}\ sta)$。  
那么用一个线段树维护，每一个节点表示对应的区间$[l,r]$内的曼哈顿距离最大值。  
上传标记非常简单就是暴力取两个子节点，然后取对于每一种正负性的珂能，都取max即可。  
```cpp
inline void pushUp(int pos){
	for (int i = 0; i < max_sta; ++i)
		seg[pos].f[i] = max(seg[pos << 1].f[i], seg[pos << 1 | 1].f[i]);
}
```
同理应用于合并query时的左右子树的结果。
#### 例子
如果您没有看懂上面的文字，我们不妨来举一个例子。  
若$k=3$时有两个点$a,b$坐标分别记为$(1,2,3),(-1,2,4)$  
那么对于点a来说有$2^3=8$种状态，  
即$(1,2,3),(1,2,-3),(1,-2,3),(1,-2,-3),$  
&ensp;&ensp;$(-1,2,3),(-1,2,-3),(-1,-2,3),(-1,-2,-3)$  
同理b也有$2^3=8$种状态，对于这$a,b$的$8$种状态两两对应，也就是  
$(1,2,3)$对应$(-(-1),-2,-4)\dots$这些互相对应的状态取max以后也就是 $\sum|a_i-b_i|$啦QAQ     

### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Pos{
	int f[32];
} seg[800005];

int n, k, max_sta;

inline void pushUp(int pos){
	for (int i = 0; i < max_sta; ++i)
		seg[pos].f[i] = max(seg[pos << 1].f[i], seg[pos << 1 | 1].f[i]);
}

int tmppos[5];

void build(int pos, int l, int r){
	if (l == r){
		for (int i = 0; i < k; ++i) scanf("%d", &tmppos[i]);
		for (int i = 0; i < max_sta; ++i){
			seg[pos].f[i] = 0;
			for (int j = 0; j < k; ++j)
				if (i & (1 << j))
					seg[pos].f[i] += tmppos[j];
				else
					seg[pos].f[i] -= tmppos[j];
		}
		return ;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid), build(pos << 1 | 1, mid + 1, r);
	pushUp(pos);
}

inline void mrg(Pos &a, Pos b){
	for (int i = 0; i < max_sta; ++i)
		a.f[i] = max(a.f[i], b.f[i]);
}

Pos query(int pos, int l, int r, int x, int y){
	if (x <= l && r <= y) return seg[pos];
	int mid = (l + r) >> 1;
	Pos res;
	if (x <= mid)
		res = query(pos << 1, l, mid, x, y);
	if (y > mid){
		if (x <= mid)
			mrg(res, query(pos << 1 | 1, mid + 1, r, x, y));
		else
			res = query(pos << 1 | 1, mid + 1, r, x, y);
	}
	return res;
}

void modify(int pos, int l, int r, int x){
	if (l == r){
		for (int i = 0; i < max_sta; ++i){
			seg[pos].f[i] = 0;
			for (int j = 0; j < k; ++j)
				if (i & (1 << j))
					seg[pos].f[i] += tmppos[j];
				else
					seg[pos].f[i] -= tmppos[j];
		}
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify(pos << 1, l, mid, x);
	else modify(pos << 1 | 1, mid + 1, r, x);
	pushUp(pos);
}

int main(){
	scanf("%d %d", &n, &k); max_sta = 1 << k;
	build(1, 1, n);
	int q; scanf("%d", &q);
	while (q--){
		int op; scanf("%d", &op);
		int i;
		if (op == 1){
			scanf("%d", &i);
			for (int j = 0; j < k; ++j)
				scanf("%d", &tmppos[j]);
			modify(1, 1, n, i);
		}
		else if (op == 2){
			int l, r; scanf("%d %d", &l, &r);
			Pos res = query(1, 1, n, l, r);
			int ans = 0;
			for (int i = 0; i < (1 << (k - 1)); ++i)
				ans = max(ans, res.f[i] + res.f[(max_sta - 1) ^ i]);
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：2)

考虑朴素算法。

考虑两个点的曼哈顿距离 $dis(x,y)=\sum\limits_{i=1}^{k}|x_i-y_i|$，显然可以求出某个 $a$ 序列，将其表示成 $\sum\limits_{i=1}^{k}(-1)^{a_i}(x_i-y_i)$ 的形式，其中 $a_i\in \{0,1\}$。

我们发现有个性质，即曼哈顿距离一定是 $a$ 序列 $2^k$ 种方案中最大的，因为是绝对值相加。

所以 $\sum\limits_{i=1}^{k}|x_i-y_i|=\max\limits_{\forall i,a_i\in \{0,1\}}\{\sum\limits_{i=1}^{k}(-1)^{a_i}(x_i-y_i)\}$。

我们发现 $2^k$ 只有 $32$，可以对于每一个 $a$，对每个点计算出 $f(a,x)=\sum\limits_{i=1}^{k}(-1)^{a_i}x_i$，然后两个点的曼哈顿距离就是 $\max\limits_{\forall i,a_i\in \{0,1\}}\{f(a,x)-f(a,y)\}$。

记 $a$ 的补集（每位取反）为 $\overline a$，则 $dis(x,y)=\max\limits_{\forall i,a_i\in \{0,1\}}\{f(a,x)+f(\overline a,y)\}$。

于是我们算出 $f(a,x)$ 后，对每个 $x$ 都取其最大值 $g(a)=\max\limits_{i=l}^{r}\{f(a,i)\}$，然后答案即为 $\max\limits_{\forall i,a_i\in \{0,1\}}\{g(a)+g(\overline a)\}$。

然后不难发现上述过程即**单点修改，区间查询最大值**，线段树维护即可。

复杂度 $O(2^kn\log n)$。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 2e5 + 200;
int n, k, q, tr[maxn << 2][32], t[32];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void pushup(int x) { for (int s = 0; s <= (1 << k) - 1; s++) tr[x][s] = max(tr[ls][s], tr[rs][s]); }
void update(int l, int r, int p, int x) {
	if (l == r) {
		memset(tr[x], 0, sizeof(tr[x]));
		for (int s = 0; s <= (1 << k) - 1; s++) {
			for (int i = 1; i <= k; i++) {
				if ((s >> (i - 1)) & 1) tr[x][s] += t[i];
				else tr[x][s] -= t[i];
			}
		}
		return;
	}
	if (p <= mid) update(l, mid, p, ls);
	else update(mid + 1, r, p, rs);
	pushup(x);
}

void query(int l, int r, int st, int tt, int x) {
	if (st <= l && r <= tt) {
		for (int s = 0; s <= (1 << k) - 1; s++) t[s] = max(t[s], tr[x][s]);
		return;
	}
	if (st <= mid) query(l, mid, st, tt, ls);
	if (tt > mid) query(mid + 1, r, st, tt, rs);
}

int main() {
	n = read(), k = read();
	for (int i = 1; i <= n << 2; i++) {
		for (int j = 0; j <= (1 << k) - 1; j++) {
			tr[i][j] = t[j] = -2e9;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) t[j] = read();
		update(1, n, i, 1);
	}
	q = read();
	while (q--) {
		int op = read();
		if (op == 1) {
			int p = read();
			for (int i = 1; i <= k; i++) t[i] = read();
			update(1, n, p, 1);
		} else {
			int l = read(), r = read();
			memset(t, -0x3f, (1 << k) * sizeof(int));
			query(1, n, l, r, 1);
			int res = 0;
			for (int s = 0; s <= (1 << k) - 1; s++) {
				res = max(res, t[s] + t[((1 << k) - 1) ^ s]);
			}
			write(res);
			puts("");
		}
	}
	return 0;
}

```

---

## 作者：EternalEpic (赞：1)

这道题可以想到用线段树实现。

可是如何处理区间曼哈顿距离最大值呢？

我们可以想到把每一维坐标拆开考虑。因为取绝对值，所以每一维的贡献只可能是正或负，可以用二进制串来表示当前这种取法。

那么相匹配的，如果挑了两个点，他们每一维的坐标状态都是相反叠加的。换言之对于在状态 $S$ 下的点， 只能与 $S$ $xor$ $2^k-1$ 叠加。

那么我们只需用线段树分别维护每一种状态的最大值，然后贪心地匹配叠加即可。

code：

```cpp
const int Maxn = 2e5 + 5;
int n, m, k, s, b[Maxn][5];
struct Node {
	int val[32];
	Node(void) { Ms(val, 0); }
	inline Node operator + (const Node&rhs) const {
		Node ret;
		for (int i = 0; i < s; i++)
			ret.val[i] = max(val[i], rhs.val[i]);
		return ret;
	}
} t[Maxn << 2], qry;

struct SegmentTree {
	inline void pushup(int pos) { t[pos] = t[pos << 1] + t[pos << 1 | 1]; }
	inline void build(int pos, int l, int r) {
		if (l == r) {
			for (int i = 0; i < s; i++)
			for (int j = 0; j < k; j++)
				if (i & (1 << j)) t[pos].val[i] += b[l][j];
				else t[pos].val[i] -= b[l][j];
			return;
		}
		int mid = l + r >> 1;
		build(pos << 1, l, mid);
		build(pos << 1 | 1, mid + 1, r);
		pushup(pos);
	}
	
	inline void update(int pos, int l, int r, int idx) {
		if (l == r) {
			Ms(t[pos].val, 0);
			for (int i = 0; i < s; i++)
			for (int j = 0; j < k; j++)
				if (i & (1 << j)) t[pos].val[i] += b[l][j];
				else t[pos].val[i] -= b[l][j];
			return;
		}
		int mid = l + r >> 1;
		if (idx <= mid) update(pos << 1, l, mid, idx);
		else update(pos << 1 | 1, mid + 1, r, idx);
		pushup(pos);
	}
	
	inline Node query(int pos, int l, int r, int L, int R) {
		if (L <= l && R >= r) return t[pos];
		int mid = l + r >> 1;
		if (L <= mid && R > mid) return query(pos << 1, l, mid, L, R) + query(pos << 1 | 1, mid + 1, r, L, R);
		if (L <= mid) return query(pos << 1, l, mid, L, R);
		if (R > mid) return query(pos << 1 | 1, mid + 1, r, L, R);
	}
} T;

signed main(void) {
	read(n), read(k); s = 1 << k;
	for (int i = 1; i <= n; i++)
	for (int j = 0; j < k; j++) read(b[i][j]);
	T.build(1, 1, n);
	
	read(m);
	for (int opt, l, r; m; m--) {
		read(opt);
		if (opt == 1) {
			read(l);
			for (int i = 0; i < k; i++) read(b[l][i]);
			T.update(1, 1, n, l);
		} else {
			read(l), read(r);
			int ret = 0; qry = T.query(1, 1, n, l, r);
			for (int i = 0; i < s; i++)
				chkmax(ret, qry.val[i] + qry.val[i ^ (s - 1)]);
			writeln(ret);
		}
	}
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}

```


---

## 作者：XG_Zepto (赞：1)

首发于 [个人博客](https://zepto.page/post/codeforces-1093g)。

### 思路

$i,j$ 之间的曼哈顿距离被定义为 $\sum |a_{i,k}-a_{j,k}|$。我们可以把式子拆开，每一维上 $a_i$ 和 $a_j$ 取值的正负性一定是相反的。

考虑到 $k$ 比较小，我们可以枚举每个点的第 $i$ 维在距离计算公式中的正负性。

具体地，我们用集合 $S$ 表示一个点每个维度的正负性。用线段树维护区间内每种可能集合 $S$ 的最大值。也就是说，我们分别计算每个点对不同的集合 $S$ 的贡献。合法答案是所有互补集合对贡献和的最大值。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls (p<<1)
#define rs (p<<1|1)
#define maxn 800010
using namespace std;
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if (ch=='-') flag=-1,ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch-'0'),ch=getchar();
	return x*flag;
}
struct Seg{
	int t[maxn];
	inline void update(int l,int r,int x,int v,int p){
		if (l==r) {t[p]=v;return;}
		int mid=((l+r)>>1);
		if (mid>=x) update(l,mid,x,v,ls);
		else update(mid+1,r,x,v,rs);
		t[p]=max(t[ls],t[rs]);
	}
	inline int query(int l,int r,int L,int R,int p){
		if (L<=l&&r<=R) return t[p];
		int mid=((l+r)>>1);
		if (R<=mid) return query(l,mid,L,R,ls);
  		if (L>=mid+1) return query(mid+1,r,L,R,rs);
		return max(query(l,mid,L,R,ls),query(mid+1,r,L,R,rs));
	}
}mk[32];
int n,k,m,a[6],b[32];
inline void update(int pos){
	for (int j=1;j<=k;++j)
			a[j]=read();
	for (int S=0;S<1<<k;++S){
		int sum=0;
		for (int j=1;j<=k;++j)
			if ((S>>(j-1))&1) sum-=a[j];
			else sum+=a[j];
		mk[S].update(1,n,pos,sum,1);
	}
}
inline void query(int l,int r){
	int res=-INT_MAX;
	for (int S=0;S<1<<k;++S)
		b[S]=mk[S].query(1,n,l,r,1);
	for (int S=0;S<1<<k;++S)
		res=max(res,b[S]+b[((1<<k)-1)-S]);
	printf("%d\n",res);
}
int main(){
	n=read(),k=read();
	for (int S=0;S<1<<k;++S)
		memset(mk[S].t,0x3f,sizeof(mk[S].t));
	for (int i=1;i<=n;++i) update(i);
	m=read();
	for (int i=1,op,pos,l,r;i<=m;++i){
		op=read();
		if (op==1) pos=read(),update(pos);
		if (op==2) l=read(),r=read(),query(l,r);
	}
}
```

---

## 作者：1saunoya (赞：1)

求的是最大两点距离。

$|x - y|$ 的正负考虑，如果最大的话，一定都是正数，所以拆开来 $2^k$ 种情况，直接取最大的就行了。

然后线段树的每个区间表示成这个区间的答案，更新的话考虑取最大值。

代码在路上（

---

## 作者：wrpwrp (赞：0)

   [一刀999](https://www.cnblogs.com/HN-wrp/p/12901331.html)  
这题妙啊。  
学会了一个新$trick$。  
### 题解
$$|x_1 - x_2|+|y_1 - y_2| = \\ max (x_1-x_2+y_1-y_2,x_1-x_2-y_1+y_2,-x_1+x_2+y_1-y2,-x_1+x_2-y_1+y_2) = \\max((x_1+y_1)-(x_2+y_2),(x_1-y_1)-(x_2-y_2),(-x_1+x_2)-(-y_1+y_2),(-x_1-y_1)-(-x_2-y_2))$$
得到两个信息。
+ 两个点的曼哈顿距离$|x_1-x_2|+|y_1-y_2|+|z_1-z_2|+\dots = \sum^{...}_{x,y,z...}max(x_1-x_2,x_2-x_1)$
+ 当$x_1$前为$+$号，$x_2$前必定是$-$号。

由于这个题目里$k <= 5$，可以枚举每一个点的$x,y,z\dots$坐标给答案贡献时前面的符号，可以用二进制来状压。那么对应的，另一个取得的点的状态就是这个点取反。（由第二个性质知道）。所以对每个点分别维护$2^k$个状态下的数值和，用线段树维护即可。最后的答案就是把询问区间的状态取出来，枚举每个状态下最大和再加上它取反的状态下最大和就是最大的答案了。
### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define R register
#define LL long long
const int inf = 0x3f3f3f3f;
const int MAXN = 2e5 + 10;

inline int read() {
	char a = getchar(); int x = 0,f = 1;
	for(; a > '9' || a < '0'; a = getchar()) if(a == '-') f = -1;
	for(; a >= '0' && a <= '9' ;a = getchar()) x = x * 10 + a - '0';
	return x * f;
}

int n, k;
int a[MAXN][5];
int mx[MAXN << 2][32];

struct Node { 
	Node() { memset(s, 0, sizeof(s)); }
	int s[32]; 
};

inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }

inline void update(int x) {
	for(R int S = (1 << k) - 1; S >= 0 ; S --) mx[x][S] = max(mx[ls(x)][S], mx[rs(x)][S]);
}

inline void build(int x, int l, int r) {
	if(l == r) {
		for(R int S = (1 << k) - 1; S >= 0 ; S --) {
			mx[x][S] = 0;
			for(R int i = 0; i < k; i ++)
				if((1 << i) & S) mx[x][S] += a[l][i];
				else mx[x][S] -= a[l][i];
		}
		return ;
	}	
	int mid = l + r; mid >>= 1;
	build(ls(x), l, mid); build(rs(x), mid + 1, r);
	update(x);
}

int st[5];

inline void modify(int x, int l, int r, int ad) {
	if(l == r) {
		for(R int i = 0; i < k; i ++) st[i] = read();
		for(R int S = (1 << k) - 1; S >= 0 ; S --) {
			mx[x][S] = 0;
			for(R int i = 0; i < k; i ++)
				if((1 << i) & S) mx[x][S] += st[i];
				else mx[x][S] -= st[i];
		}
		return ;
	}
	int mid = l + r; mid >>= 1;
	if(ad <= mid) modify(ls(x), l, mid, ad);
	else modify(rs(x), mid + 1, r, ad);
	update(x);
}

inline Node ask(int x, int l, int r, int Le, int Ri) {
	if( Le <= l && r <= Ri ) {
		Node ans;
		for(R int S = (1 << k) - 1; S >= 0 ; S --) {
			ans.s[S]= mx[x][S];
		}
		return ans;
	}
	int mid = l + r; mid >>= 1;
	/*if(Le <= mid) ans = max(ans, ask(ls(x), l, mid, Le, Ri));
	if(Ri > mid) ans = max(ans, ask(rs(x), mid + 1, r, Le, Ri));*/
	if(Ri <= mid) return ask(ls(x), l, mid, Le, Ri);
	if(Le > mid) return ask(rs(x), mid + 1, r, Le, Ri);
	Node la = ask(ls(x), l, mid, Le, Ri);
	Node ra = ask(rs(x), mid + 1, r, Le, Ri);
	for(R int S = ( 1 << k ) - 1; S >= 0; S --) {
		la. s[S] = max(la. s[S], ra. s[S]);
	}
	return la; 
}

int main() {
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	n = read(); k = read();
	for(R int i = 1; i <= n; i ++) {
		for(R int j = 0; j < k; j ++)
			a[i][j] = read();
	}
	build(1, 1, n);
	int q = read();
	while(q --) {
		if(read() == 1) {
			int i = read();
			modify(1, 1, n, i);
		}
		else {
			int l = read(), r = read();
			Node ans = ask(1, 1, n, l, r);
			int res = 0;
			for(R int S = ( 1 << k ) - 1; S >= 0; S --)
				res = max( res, ans.s[S] + ans.s[((1 << k) - 1) ^ S]);
			printf("%d\n",res);
		}
	}
	return 0;	
}
```

---

