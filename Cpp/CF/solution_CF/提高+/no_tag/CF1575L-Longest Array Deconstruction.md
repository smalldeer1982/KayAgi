# Longest Array Deconstruction

## 题目描述

Mr. Chanek gives you a sequence $ a $ indexed from $ 1 $ to $ n $ . Define $ f(a) $ as the number of indices where $ a_i = i $ .

You can pick an element from the current sequence and remove it, then concatenate the remaining elements together. For example, if you remove the $ 3 $ -rd element from the sequence $ [4, 2, 3, 1] $ , the resulting sequence will be $ [4, 2, 1] $ .

You want to remove some elements from $ a $ in order to maximize $ f(a) $ , using zero or more operations. Find the largest possible $ f(a) $ .

## 说明/提示

In the first example, $ f(A) = 3 $ by doing the following operations.

 $ [2,1,\textbf{4},2,5,3,7] \rightarrow [\textbf{2},1,2,5,3,7] \rightarrow [1,2,5,3,\textbf{7}] \rightarrow [1,2,\textbf{5},3] \rightarrow [1,2,3] $

In the second example, $ f(A) = 2 $ and no additional operation is needed.

## 样例 #1

### 输入

```
7
2 1 4 2 5 3 7```

### 输出

```
3```

## 样例 #2

### 输入

```
4
4 2 3 1```

### 输出

```
2```

# 题解

## 作者：BlankAo (赞：13)

**CF1575L Longest Array Deconstruction / [原题链接](https://www.luogu.com.cn/problem/CF1575L)**

其实这道题不用高级数据结构 2333

## 题意

如果将 $a_i$ 移动到 $i$，那么需要 $a_i\le i$。

考虑两个相邻的位置 $p,q$，如果想让它们都有让答案加一的可能，要有：
$$
a_p<a_q\\p-a_p\le q-a_q
$$
而且发现这两个不等式同时也保证了 $p<q$。

对于不相邻的 $p,q$，会依次考虑 $p,p+1,p+2...q-1,q$，从而保证不会出错。

于是就相当于求 $(i-a_i,a_i)$ 的 LIS。用 lower_bound 计算即可。

时间复杂度 $O(nlogn)$。

## 代码

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
const int n7=201234;
struct dino{int x,y;}a[n7];
int n,b[n7],cnt,poi;

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) )fu|=(ch=='-'),ch=getchar();
	while( isdigit(ch) )shu=shu*10+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

bool cmp(dino p,dino q){return p.x==q.x?p.y<q.y:p.x<q.x;}

int main(){
	n=rd();
	rep(i,1,n){
		int w=rd();
		if(i-w>=0)cnt++,a[cnt]=(dino){i-w,w};
	}
	if(!cnt){puts("0");return 0;}
	sort(a+1,a+cnt+1,cmp);
	poi=1,b[1]=a[1].y;
	rep(i,2,cnt){
		if(a[i].y>b[poi])poi++,b[poi]=a[i].y;
		else b[lower_bound(b+1,b+poi+1,a[i].y)-b]=a[i].y;
	}
	printf("%d",poi);
	return 0;
}

```


---

## 作者：云浅知处 (赞：7)



dp：设 $F(i)$ 表示在前 $i$ 个数中，强制令 $a_i$ 位于 $a_i$ 位置上的最大 $f$ 值。

那么考虑枚举 $a_i$ 删到位置 $a_i$ 上后，离它最近的一个满足 $a_j=j$ 的数是哪个。这样就得到了一个类似 $F(i)=\max\{F(j)+1\}$ 的形式。

思考一下发现这个 $j$  需要满足以下两个条件：

- 由于删完之后 $a_j$ 在 $a_i$ 前面，因此要有 $a_j<a_i$。
- 由于把 $a_i$ 移到 $a_i$ 位置上需要删 $i-a_i$ 个数，把 $a_j$ 移动 $a_j$ 位置上需要删 $j-a_j$ 个数，而 $a_j$ 在 $a_i$ 前面，因此在 $a_j$ 前面删的数必然会算进 $a_i$ 前面删的数里面。因此必须要有 $j-a_j\le i-a_i$，不难发现这也是充分条件。
- 注意到前两条移项一下就等价于 $j\le i+a_j-a_i<i$，因此也保证了 $j<i$。很妙。

因此转移方程就是：
$$
F(i)=\max\{F(j)+1|a_j<a_i,j-a_j\le i-a_i,\}
$$
这个形式直接转移是 $O(n^2)$ 的。~~[加了一些阴间乱搞过了 CF 的官方数据](https://codeforces.com/contest/1575/submission/141645261)~~

优化其实很好想。。这是个典型的二维偏序形式，因此按照其中一维排序然后从前往后用一个线段树维护一下前缀最大值就行了。

代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

#define lson(o) (o<<1)
#define rson(o) (o<<1|1)

const int MN=2e5+5;
const int INF=1e9;
int a[MN],n,dp[MN];

struct SegTree{
	int d[MN<<2];
	
	inline void pushup(int o){
		d[o]=max(d[lson(o)],d[rson(o)]);
	}
	
	inline void clear(){
		memset(d,0,sizeof(d));
	}
	
	inline int query(int l,int r,int ql,int qr,int o){
		if(l>r)return 0;
		if(l<=ql&&qr<=r)return d[o];
		int mid=(ql+qr)>>1,ans=0;
		if(l<=mid)ans=max(ans,query(l,r,ql,mid,lson(o)));
		if(r>mid)ans=max(ans,query(l,r,mid+1,qr,rson(o)));
		return ans; 
	}
	
	inline void modify(int pos,int k,int ql,int qr,int o){
		if(ql==qr){d[o]=max(d[o],k);return ;}
		int mid=(ql+qr)>>1;
		if(pos<=mid)modify(pos,k,ql,mid,lson(o));
		if(pos>mid)modify(pos,k,mid+1,qr,rson(o));
		pushup(o);
	}
}tree;

pair<int,int>val[MN];

#define fi first
#define se second
#define mk make_pair

signed main(void){
	
	n=read();int cnt=0,ans=0;
	for(int i=1;i<=n;i++){
		a[i]=read(),dp[i]=-INF;
		if(a[i]<=i)val[++cnt]=mk(i-a[i],a[i]);
	}
	sort(val+1,val+cnt+1);tree.clear();
	for(int i=1;i<=cnt;i++){
		dp[i]=tree.query(1,val[i].se-1,1,n,1)+1;
		tree.modify(val[i].se,dp[i],1,n,1),ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;

    return 0;
}
```



---

## 作者：xixike (赞：6)

[更好地阅读体验](https://www.cnblogs.com/xixike/p/15721272.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/CF1575L)

## Solution

并不需要复杂的 DS（

考虑对于两个点 $x,y\ (x < y)$，什么情况下才能使它们都有贡献。

第一个条件：
$$
a_x < a_y
$$
这个比较显然吧。

第二个条件：
$$
x - a_x \leq y - a_y
$$
解释一下，$x - a_x$ 表示在坐标 $x$ 之前要删掉多少个数才能使 $x = a_x$，显然对于 $x,y\ (x < y)$， $x$ 前删掉的数的个数必须小于等于 $y$ 之前删掉的数的个数。

同时，我们稍微推一下这个不等式，发现它也满足：
$$
x < y
$$
所以 $x < y$ 这个条件我们就不需要处考虑。

然后……等等！这不就是一个二维偏序问题吗！

于是我们就可以愉快的用 `lower_bound` 或 树状数组来解决它啦。

> 注意：
> - 上面的两个条件中一个是**小于**号，另一个是**小于等于**号（其实这样反而更简单了），而我们计算出来的序列中可能会有大量相等的数，具体怎么写见代码吧。
> - 我们计算出的数列中会有许多 0，所以在树状数组的实现过程中要特判。

## Code

（看到楼下的 Dalao 用 `lower_bound` 实现了，这里给出一份树状数组的代码）

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;
struct node{
    int x, y;
    bool operator < (const node &b) const{
        return x != b.x ? x < b.x : y < b.y;
    }
}a[N];
int n, cnt, ans;

struct BIT{
    int c[N];

    inline void add(int x, int y){
        if(x < 0) return;
        for(; x <= n; x += x & (-x)) c[x] = max(c[x], y);
    }

    inline int query(int x){
        if(x <= 0) return 0;
        int res = 0;
        for(; x; x -= x & (-x)) res = max(res, c[x]);
        return res;
    }
}c;

int main(){
    n = read();
    for(int i = 1; i <= n; ++i){
        int t = read();
        if(i - t >= 0) a[++cnt] = (node){i - t, t};
    }
    sort(a + 1, a + 1 + cnt);
    for(int i = 1; i <= cnt; ++i){
        int len = c.query(a[i].y - 1);
        c.add(a[i].y, len + 1);
        ans = max(ans, len + 1);
    }
    write(ans), puts("");
    return 0;
}
```

$$
\_EOF\_
$$



---

## 作者：_SeeleVollerei_ (赞：4)

题意写得很简单清楚了，这里就不再做概述。

这是一道相当简单且模板的紫题。

### 前置芝士：会动态规划，以及任意一种树套树或其他您认为足够强大的数据结构。

序列上操作前后不影响的题想到 $dp$，设两维太难优化了，所以只设一维强制性的 $dp$。（如果有两维优化出来的可以教教我）

设 $f_i$ 表示考虑完前 $i$ 个数，且强制选 $a_i$ 在第 $a_i$ 个位置时的最大答案，考虑转移。

这里先给出转移方程再做解释。

$$f_i=max\{f_j+1\}(j<i,a_j<a_i,i-j+1\ge a_i-a_j+1)$$

其实就是说在选了第 $j$ 个数的基础上，不管中间选了什么，再选第 $i$ 个数。

对于中间的条件，因为 $a_j$ 在 $a_i$ 前面，而在序列上操作若干次后它们的相对顺序不变，所以要满足 $a_j<a_i$。

对于最后一个条件，考虑操作完后的序列上 $a_j$ 与 $a_i$ 之间一共有 $a_i-a_j+1$ 个数（算上 $a_i$ 和 $a_j$ ），那么原序列上 $i$ 和 $j$ 之间也应至少有 $a_i-a_j+1$ 个数，故有 $i-j+1\ge a_i-a_j+1$。

然后就得到了一个很简单的 $O(n^2)$ 的做法，考虑优化。

$j<i$ 的条件跟没有一样，考虑如何处理后面两个条件。

第二个条件很显然了，考虑转化第三个条件，转化一下式子。

$$i-j+1\ge a_i-a_j+1$$

其实也很简单，直接把 $a_i$ 丢到左边，把 $j$ 丢到右边即可。

$$i-a_i+1 \ge j-a_j+1$$

这样一来就很明显了，随便弄一个树套树或者您喜欢的能够维护条件的数据结构进行维护即可，我这里使用的是我认为最简单的树状数组套主席树

具体做法是将 $a_j$ 作为树状数组的下标，将 $j-a_j+1$ 作为主席树的下标，维护 $f_j$ 的最大值即可。

一些其他的细节（其实也没多少）见代码：

```cpp
#include<cstdio>
const int N=2e5+5;
int f[N],n,ans;
inline int Read(){
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
inline int Max(const int x,const int y){
	return x>y?x:y;
}
int root[N],lc[N<<7],rc[N<<7],cnt,maxx[N<<7];
// 主席树。
inline void Change(const int u,const int ll,const int rr,const int p,const int value){
	maxx[u]=Max(maxx[u],value);
	if(ll==rr) return ;
	int mid=ll+rr>>1;
	if(mid>=p){
		if(!lc[u]) lc[u]=++cnt;
		Change(lc[u],ll,mid,p,value);
	}
	else{
		if(!rc[u]) rc[u]=++cnt;
		Change(rc[u],mid+1,rr,p,value);
	}
	return ;
}
inline int Query(const int u,const int ll,const int rr,const int ql,const int qr){
	if(ll>=ql&&rr<=qr) return maxx[u];
	int mid=ll+rr>>1,ss=0;
	if(mid>=ql&&lc[u]) ss=Max(ss,Query(lc[u],ll,mid,ql,qr));
	if(mid<qr&&rc[u]) ss=Max(ss,Query(rc[u],mid+1,rr,ql,qr));
	return ss;
}
// 树状数组。
inline int Lowbit(const int x){
	return x&(-x);
}
inline void Change(const int p,const int q,const int value){
	for(register int i=p;i<=n;i+=Lowbit(i))
		Change(root[i],1,n,q,value);
	return ;
}
inline int Query(const int p,const int q){
	int ss=0;
	for(register int i=p;i;i-=Lowbit(i))
		ss=Max(ss,Query(root[i],1,n,1,q));
	return ss;
}
inline void Work(const int i){
	int x=Read();
	if(i<x) return ;
	// 如果 i<ai 很明显这个位置不可能产生贡献。
	// 因为无论如何都无法将 ai 弄到第 ai 个位置。
	f[i]=Query(x-1,i-x+1)+1;
	ans=Max(ans,f[i]); 
	//每个数都有可能作为最终序列的最后一个数。
	Change(x,i-x+1,f[i]);
	return ;
}
int main(){
	n=Read();
	for(register int i=1;i<=n;i++)
		root[i]=++cnt;
	for(register int i=1;i<=n;i++)
		Work(i);
	printf("%d\n",ans);
	return 0;
}
```

完结撒花

---

## 作者：liangbob (赞：1)

### CF1575L 题解

#### 思路分析

一道挺不错的思维题。

首先，我们定义 $d_i$ 为要操作的次数，即 $i-a_i$（前提是 $i \ge a_i$，否则我们定义 $d_i$ 不存在，即 $d_i$ 必须大于等于零）。那么，当 $a_i$ 与 $a_j$（$i < j$）能通过操作多次使得 $i=a_i$ 且 $j=a_j$ 时，必然满足以下条件（充分必要条件）：

$$\begin{cases}a_i < a_j\\d_i \leq d_j\end{cases}$$

这里我来证明一下这个结论。

证明：设当 $d_i > d_j$ 时，亦能满足 $a_i$ 与 $a_j$（$i < j$）能通过操作多次使得 $i=a_i$ 且 $j=a_j$。

即

$$\begin{cases}i<j\\a_i < a_j \\d_i > d_j \\\end{cases}$$

设有

$$\begin{cases}i+ x = j\\a_i + y = a_j \\\end{cases}$$

（$x,\;y > 0$）

由 $d_i$ 定义，$d_i+d_j \geq 0$，$d_i=i-a_i$，$d_j=j-a_j$。

$$\begin{aligned}d_i+d_j & = i-a_i+j-a_j \\ & = i-a_i + i+x-(a_i+y) \\ & = 2i - 2a_i+x-y\end{aligned}$$

由于 $d_i = i-a_i \geq 0$，所以 $x - y \geq 0$，$x \geq y$。

又 $d_i > d_j$，$d_i-d_j > 0$。

$$\begin{aligned}d_i-d_j & = i-a_i-(j-a_j) \\ & = i-a_i  -[i+x-(a_i+y)] \\ & = y - x \\\end{aligned}$$

即 $y-x>0$，有 $y>x$，即 $x < y$，矛盾。

所以，当且仅当 $d_i \leq d_j$ 时，满足 $a_i$ 与 $a_j$（$i < j$）能通过操作多次使得 $i=a_i$ 且 $j=a_j$。

接着，我们要尽可能多地去满足这两个条件。我们可以先确保满足一条件，再尽可能多地去满足第二个条件。于是，我们可以以 $d_i$ 为第一关键字排序，这样可以先确保满足一条件。接着再求排序后 $a_i$ 的最长上升子序列，这样就可以尽可能多地去满足第二个条件了。

注意到 $d_i \geq 0$，所以要排除 $i < a_i$ 的情况。另外，$n$ 的范围较大，所以要使用快速求最长上升子序列的方法，我这里选用了使用树状数组求最长上升子序列的方法，详细可参考[这篇博文](https://blog.csdn.net/weixin_44178736/article/details/104906816)。

#### 关键代码

```cpp
int c[N], n, cnt; //树状数组，n，排除 i < a_i 后数的个数
struct node //(i-a_i,i) 二元组
{
	int i_ai, ai;	
}; 
node a[N];

int query(int x) //树状数组查询前 x 项的最值
{
	int sum = 0;
	while(x > 0)
	{
		sum = max(sum, c[x]);
		x -= lowbit(x);
	}
	return sum;
}

void update(int x, int p) //树状数组更新
{
	while(x <= n)
	{
		c[x] = max(c[x], p);
		x += lowbit(x);
	}
}

bool cmp(node x, node y) //以 i-a_i 为第一关键字排序的比较函数
{
	if(x.i_ai != y.i_ai) return x.i_ai < y.i_ai;
	return x.ai < y.ai;
}

signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		int t;
		cin >> t;
		if(i >= t) //满足要求
		{
			a[++cnt] = (node){i - t, t}; //插入序列
		}
	}
	int maxv = 0; //最长上升子序列的最长比较变量
	sort(a + 1, a + cnt + 1, cmp); //以 i-a_i 为第一关键字排序
	for(int i = 1;i <= cnt;i++)
	{
        // 使用树状数组求出最长上升子序列
		int y = query(a[i].ai - 1); 
		update(a[i].ai, y + 1);
		maxv = max(maxv, y + 1); //进行比较
	}
	cout << maxv << endl;
	return 0;
}
```



---

## 作者：ECEG (赞：0)

设 $dp_{i,j}$ 表示前 $i$ 个数，选了 $j$ 个数的 $f$。

但是不好优化啊。

你可以只选出有贡献的，满足单调，且 $i-j\ge a_i-a_j$，$i$ 和 $j$ 是相邻两个。

那就可以换一下 dp 了，设 $dp_i$ 表示考虑 $1$ 到 $i$，且 $i$ 一定会选。

dp 转移：$dp_{i}=\max\limits_{i-a_i\ge j-a_j,a_j\lt a_i}\{dp_j\}+1$。

数据结构优化即可。

可以为 cdq。

```cpp
const int maxn=2e5+4;int n,dp[maxn],ans;
#define mid ((l+r)>>1)
struct _{int x,y,id;}a[maxn];
int maxx[maxn<<2];
void change(int k,int l,int r,int x,int y){
	if(x<1)return;//记得判
	if(l==r)return maxx[k]=y,void();
	if(x<=mid)change(k<<1,l,mid,x,y);
	else change(k<<1|1,mid+1,r,x,y);
	maxx[k]=max(maxx[k<<1],maxx[k<<1|1]);
}
int query(int k,int l,int r,int x,int y){
	if(x>y)return -1e9-1;
	if(x<=l&&r<=y)return maxx[k];
	int res=-1e9;
	if(x<=mid)res=max(res,query(k<<1,l,mid,x,y));
	if(y>mid)res=max(res,query(k<<1|1,mid+1,r,x,y));
	return res;
}
void solve(int l,int r){
	if(l==r)return;
	solve(l,mid);
	std::sort(a+l,a+mid+1,[](const _ &x,const _ &y){return x.x<y.x;});
	std::sort(a+mid+1,a+r+1,[](const _ &x,const _ &y){return x.x<y.x;});
	int j=l;
	for(int i=mid+1;i<=r;++i){
		for(;j<=mid&&a[j].x<a[i].x;++j)change(1,1,n,a[j].y,dp[a[j].id]);
		dp[a[i].id]=max(query(1,1,n,1,a[i].y)+1,dp[a[i].id]);ans=max(ans,dp[a[i].id]);
	}
	for(;--j>=l;)change(1,1,n,a[j].y,-1e9);
	std::sort(a+mid+1,a+r+1,[](const _ &x,const _ &y){return x.id<y.id;});
	solve(mid+1,r);
}
signed main(){
	read(n);dp[0]=0;
	for(int i=1,x;i<=n;++i)read(x),a[i]={x,i-x+1,i},dp[i]=-1e9;
	solve(0,n);write(ans);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# CF1575L 解题报告

## 前言

MnZn 刚学会二维偏序，来写篇题解加深印象。

感觉正赛考的还不少。

## 思路分析

首先肯定是 DP。

设 $f_i$ 表示钦定选择 $a_i=i$，在前 $i$ 个数中所能得到的最大的价值。

这样目标为：

$$ans=\max_{i=1}^{n} f_i$$

考虑朴素转移为：

$$f_i=\max_{j=1}^{i-1} f_j+1,a_j<a_i,i-j+1\ge a_i-a_j+1$$

这个柿子等价于：

$$f_i=\max_{j=1}^{n} f_j+1,a_j<a_i,j-a_j\le i-a_i$$

直接算是 $O(n^2)$ 的。考虑数据结构优化转移。

不难发现，对 $j$ 的两个限制构成二维偏序关系。所以可以排序解决一维，然后树状数组解决一维。

注意两个限制一个可以取等，一个不可以。

具体地，我们按 $i-a_i$ 为第一关键字，$a_i$ 为第二关键字从小到大排序，每次在树状数组上查询 $a_j<a_i$ 的 $f_j$ 的最大值，并用 $f_i$ 的值更新 $i$ 位置的值。

注意如果 $i<a_i$，那么 $f_i$ 肯定为 $0$，因为无法通过删数使 $a_i=i$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define lowbit(i) (i&(-i))
using namespace std;
int n,m,a,f[200005],ans;
struct node{
	int a,id;
}h[200005];
bool cmp(node x,node y){
	if(x.id-x.a!=y.id-y.a) return x.id-x.a<y.id-y.a;
	else return x.a<y.a;
}
int c[400005];
void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]=max(c[i],k);
	}
}
int query(int x){
	ans=0;
	for(int i=x;i;i-=lowbit(i)){
		ans=max(ans,c[i]);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(i<a) continue; 
		h[++m].a=a;
		h[m].id=i;
	}
	sort(h+1,h+1+m,cmp);
	for(int i=1;i<=m;i++){
		f[i]=query(h[i].a-1)+1;
		add(h[i].a,f[i]);
	}
	for(int i=1;i<=m;i++){
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}

```

## 后记

比较经典，必须熟练掌握。

---

## 作者：run_away (赞：0)

**[双倍经验](https://www.luogu.com.cn/problem/P6564)**

**如果本文出锅，请评论或私信提醒这个蒟蒻修改！**

## 题意

题目给的很清楚了，不多说。

## 分析

看到题目，~~因为在dp题单里，所以~~一眼是个dp，我们先想朴素算法，可以发现，如果设 $f_{i,j}$ 表示前 $i$ 个数中删掉 $j$ 个所能得到的最大结果，若 $a_i=i$，则 $f_{i,j}=f_{i-1,j}+1$；否则，可以直接从 $f_{i-1,j-1}$ 转移。

可以很快地打出一个 $O(n^2)$ 的暴力。

```c++
f[1][0]=(a[1]==1);
for(ll i=2;i<=n;++i)f[i][0]=f[i-1][0]+(a[i]==i);
for(ll i=1;i<=n;++i){
    for(ll j=1;j<=i;++j){
        f[i][j]=max(f[i-1][j]+(a[i]==i-j),f[i-1][j-1]);
    }
}
```

但是由于 $1\le n\le 2\times 10^5$，所以它会 **TLE**+**MLE**。

第一维的 $i$ 不可能优化掉。

看第二维 $j$，经过思考后可以发现，因为空间复杂度应是 $O(n)$ 级别的，就可以设 $f_{i,0/1}$ 表示第 $i$ 个数是否归到 $a_i$ 的位置上的最大结果。思再想一想，可发现应设 $f_i$ 表示 $i$ **归位的最大结果**，因为求 $f_{i,0}$ 没什么意义。

对此，可得 $f_i=\max(f_j)+1\quad(a_j<a_i,j-a_j\le i-a_i)$，然后可用树状数组维护二维偏序，不会的看[这里](https://www.luogu.com.cn/problem/P1908)(能做这题的应该都会吧)。

## Code

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,a[2000005],c[2000005],m=1e6;
inline ll lowbit(ll x){return x&-x;}
inline void update(ll x,ll val){
    while(x<=m){
        c[x]=max(c[x],val);
        x+=lowbit(x);
    }
}
inline ll ask(ll x){
    ll res=0;
    while(x){
        res=max(res,c[x]);
        x-=lowbit(x);
    }
    return res;
}//树状数组维护二维偏序
vector<ll>cnt[2000005];
signed main(){
    cin>>n;
    for(ll i=1;i<=n;++i){
        cin>>a[i];
        if(i>=a[i]){
            cnt[i-a[i]].push_back(a[i]);//预处理一下可能的i-a[i]
        }
    }
    for(ll i=0;i<=m;++i){
        for(ll j:cnt[i]){
            update(j,ask(j-1)+1);//更新
        }
    }
    cout<<ask(m);
    return 0;
}
```

---

## 作者：Gmt丶FFF (赞：0)

思考一下还是能想出来的。

我们考虑一个数 $x$ 当前位置为 $y$，如果 $x\le y$，那么删除 $x$ 以前的 $y-x$ 个数即可归位。而这样就会对下标大于 $y$ 的一个数 $z$ 也向前移动 $y -x$ 步，而如果这个数 $z$ 要向前移动 $p$ 步，且 $p\ge y-x$，那么 $z$ 就有可能归位。

为什么说是有可能归位，因为如果 $z<x$，那么如果 $x$ 归位了，$z$ 只能在 $x$ 后面，这样就必须删 $x$ 才能使 $z$ 归位，很明显就不能保证 $x,z$ 同时归位。

那么我们就知道了，如果两个数能同时归位，下标大的数一定要更大，且归位需要移动的步数也要大于等于下标小的数需移动的次数。

那么我们就对每一个数设一个二元组 $(x,y)$，$x$ 代表归位需移动的步数，$y$ 代表原数大小，那么如果两个数能同时归位，则这两个二元组 $(x_1,y_1),(x_2,y_2)$ 满足 $x_1\le x_2$ $y_1<y_2$。

那么就是一个二维偏序板题了。

时间复杂度：$O(n\log n)$。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int n,f[N],dp[N];
inline int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int k)
{
	while(x<=n)
	{
		f[x]=max(f[x],k);
		x+=lowbit(x);
	}
}
int search(int x)
{
	int ans=0;
	while(x)
	{
		ans=max(ans,f[x]);
		x-=lowbit(x);
	}
	return ans;
}
struct node
{
	int x,y;
}a[N];
inline bool cmp(node x,node y)
{
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].y),a[i].x=(i-a[i].y);
	sort(a+1,a+1+n,cmp);
	int res=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].x<0)continue;
		dp[i]=search(a[i].y-1)+1;
		update(a[i].y,dp[i]);
		res=max(res,dp[i]);
	}
	printf("%d",res);
	return 0;
}
```


---

