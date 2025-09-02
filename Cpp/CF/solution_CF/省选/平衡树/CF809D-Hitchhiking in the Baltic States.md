# Hitchhiking in the Baltic States

## 题目描述

Leha and Noora decided to go on a trip in the Baltic States. As you know from the previous problem, Leha has lost his car on the parking of the restaurant. Unfortunately, requests to the watchman didn't helped hacker find the car, so friends decided to go hitchhiking.

In total, they intended to visit $ n $ towns. However it turned out that sights in $ i $ -th town are open for visitors only on days from $ l_{i} $ to $ r_{i} $ .

What to do? Leha proposed to choose for each town $ i $ a day, when they will visit this town, i.e any integer $ x_{i} $ in interval $ [l_{i},r_{i}] $ . After that Noora choses some subsequence of towns $ id_{1},id_{2},...,id_{k} $ , which friends are going to visit, that at first they are strictly increasing, i.e $ id_{i}<id_{i+1} $ is for all integers $ i $ from $ 1 $ to $ k-1 $ , but also the dates of the friends visits are strictly increasing, i.e $ x_{idi}<x_{idi+1} $ is true for all integers $ i $ from $ 1 $ to $ k-1 $ .

Please help Leha and Noora in choosing such $ x_{i} $ for each town $ i $ , and such subsequence of towns $ id_{1},id_{2},...,id_{k} $ , so that friends can visit maximal number of towns.

You may assume, that Leha and Noora can start the trip any day.

## 说明/提示

Consider the first example.

Let's take this plan: let's visit the sight in the second town on the first day, in the third town on the third day and in the fifth town on the fourth. That's would be the optimal answer.

## 样例 #1

### 输入

```
5
6 6
1 2
3 4
2 2
1 4
```

### 输出

```
3
```

# 题解

## 作者：Ryo_Yamada (赞：33)

CF *2900 平衡树+dp 神题，补一发题解。

设 $f_j$ 表示长度为 $j$ 的最长上升子序列的最后一位。设当前限制为 $a_i \in [l,\,r]$。

两个转移方程：

- $f_{j-1} < l-1$，$f_j = \min(f_j,\,l)$。
- $l - 1 \leq f_{j-1} \leq r - 1$，$f_j = \min(f_j,\,f_{j-1}+1)$。

暴力转移复杂度是 $O(n^2)$ 的，可以使用平衡树优化。

观察到数组 $f$ 具有单调性，以上的转移可以使用平衡树转化为：

- 找到满足 $l - 1 \leq f_{j} \leq r - 1$ 的最长的一段，将这一段集体 $+1$，然后后移一位（后移使用后面的操作）。
- 因为 $f_0 = -\infty$，一定能找到一个 $j$ 满足 $f_{j} < l-1$，直接在平衡树中插入 $l$。在上面的操作中，$f_j$ 转移后值一定 $<l$，所以这个操作相当于也做到了上面的后移一位。
- 找到最小的 $\geq r$ 的数，如果它存在，将其删除。

最终的答案就是平衡树的大小。

![](https://cdn.luogu.com.cn/upload/image_hosting/px3nf7uc.png)

例如这个情况，首先找到满足 $l - 1 \leq f_{j} \leq r - 1$ 的最长的一段 $[2,\,5]$，将其整体 $+1$ 并后移一位，插入一个 $l$，然后找到最小的 $\geq r$ 的数 $20$，并将其删除。得到的 $f$ 数组变为 $\{-\infty,\,3,\,5,\,8,\,12,\,14,\,18,\,27,\, \ldots\}$。

时间复杂度 $O(n \log n)$。

[Code](https://www.luogu.com.cn/paste/eh20c18x)

---

## 作者：foreverlasting (赞：22)

[题面](https://www.luogu.org/problemnew/show/CF809D)

平衡树+DP。

好神的一题啊，不看题解完全不会。表示这边的题解讲得不是很详细哎，我来分析一下到底为什么可以移一位。

首先，$dp[j]$表示最长上升子序列长度为$j$的最后一位数字。考虑如何转移。

转移方程有三种：（设当前限制为$l$，$r$）

1、$dp[j]=min(dp[j],l)$，当$dp[j-1]<l$时。

2、$dp[j]=min(dp[j],dp[j-1]+1)$，当$dp[j-1]>=l$&&$dp[j-1]<r$时。

3、$dp[j]=dp[j]$，当$dp[j-1]>=r$时。

这样的话，暴力转移是$O(n^2)$的，考虑如何优化。

可以用平衡树优化。

对于第一个转移方程，我们可以去找小于$l$且最大的$dp[j]$去转移到$dp[j+1]$。

对于第二个转移方程，我们可以在区间$[l,r-1]$让每个数加$1$，并且向后移一位，代表转移到$j+1$。

对于第三个转移方程，我们可以去找大于等于$r$且最小的数，然后把它删掉。

而以上的操作都可以用平衡树做到。第二种操作中的后移其实也不用考虑，因为在第一个操作中添加了一个小于$l$的数，所以肯定让所有数向后移了一位。

所以就这么神奇地想出了这题，感觉好神的思想啊。

code:
```
//2018.10.28 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=3e5+10;
namespace MAIN{
    int n;
    struct Treap{
        int son[2],va,pri,siz,laz;
    }tr[N];
    int dp[N];
    int st[N],top,tot;
    int rt;
    inline void pushup(const res &x){
        tr[x].siz=tr[tr[x].son[0]].siz+tr[tr[x].son[1]].siz+1;
    }
    inline int newnode(const res &va){
        res cnt;
        if(top)cnt=st[top--];
        else cnt=++tot;
        tr[cnt].va=va,tr[cnt].son[0]=tr[cnt].son[1]=tr[cnt].laz=0,tr[cnt].siz=1,tr[cnt].pri=rand();
        return cnt;
    }
    inline void change(const res &x,const res &va){
        if(!x)return;
        tr[x].laz+=va,tr[x].va+=va;
    }
    inline void pushdown(const res &x){
        if(!x||!tr[x].laz)return;
        change(tr[x].son[0],tr[x].laz),change(tr[x].son[1],tr[x].laz);
        tr[x].laz=0;
    }
    int merge(const res &x,const res &y){
        if(!x||!y)return x+y;
        pushdown(x),pushdown(y);
        if(tr[x].pri<tr[y].pri){
            tr[x].son[1]=merge(tr[x].son[1],y);
            pushup(x);
            return x;
        }
        else {
            tr[y].son[0]=merge(x,tr[y].son[0]);
            pushup(y);
            return y;
        }
    }
    void split(res now,res k,res &x,res &y){
        if(!now){x=y=0;return;}
        pushdown(now);
        if(tr[now].va<=k)x=now,split(tr[now].son[1],k,tr[now].son[1],y);
        else y=now,split(tr[now].son[0],k,x,tr[now].son[0]);
        pushup(now);
    }
    inline int kth(res now,res k){
        if(!k)return 0;
        while(233){
            if(tr[tr[now].son[0]].siz==k-1)return now;
            if(tr[tr[now].son[0]].siz>=k)now=tr[now].son[0];
            else k-=tr[tr[now].son[0]].siz+1,now=tr[now].son[1];
        }
    }
    inline int pre(const res &va){
        res a,b,ret;
        split(rt,va-1,a,b),ret=kth(a,tr[a].siz),rt=merge(a,b);
        return ret;
    }
    inline int nxt(const res &va){
        res a,b,ret;
        split(rt,va,a,b),ret=kth(b,1),rt=merge(a,b);
        return ret;
    }
    inline void insert(const res &va){
        res a,b;
        split(rt,va,a,b),rt=merge(merge(a,newnode(va)),b);
    }
    inline void del(const res &va){
        res a,b,c,d;
        split(rt,va,a,b),split(a,va-1,c,d),st[++top]=d,d=merge(tr[d].son[0],tr[d].son[1]),rt=merge(merge(c,d),b);
    }
    inline void modify(const res &l,const res &r){
    	res a,b,c,d;
    	split(rt,l-1,a,b),split(b,r,c,d),change(c,1),rt=merge(a,merge(c,d));
	}
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++){
            res l=read(),r=read();
            if(i==1){insert(l);continue;}
            res p=pre(l),q=nxt(r-1);
            modify(l,r-1);
            if(q)del(tr[q].va);
            insert(l);
        }
        if(!rt)puts("0");
        else printf("%d\n",tr[rt].siz);
    }
}
int main(){
    srand((unsigned)time(NULL));
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Night_Bringer (赞：8)

# 前言
[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14810551.html)


惊了，splay 好写还快但题解里没人用。
# 题意
给定 $n$ 个区间 $[l_i,r_i]$ ，请你构造一个序列，每个元素 $a_i$ 满足 $a_i\in[l_i,r_i]$ ，且该序列的最长严格上升子序列最长。
# 思路
$n^2$ 的 DP 都想了半天 QAQ 。

首先在第一维枚举区间。

定义 $dp[i][j]$ ：枚举到第 $i$ 个区间时，长度为 $j$ 的严格上升子序列的结尾的最小值，若不存在，则为极大值。

显然，初值为 $dp[0][0]=0$ ，其余为极大值。最后统计 $dp[i](i\in n)$ 中不等于极大值的有多少。转移方程如下：

$dp[i][j]=
\begin{cases}
min(dp[i-1][j],l),& \text{dp[i-1][j-1]<l,}\\
min(dp[i-1][j],dp[i-1][j-1]+1),& \text{dp[i-1][j-1]>=l,dp[i-1][j-1]<r,}\\
dp[i-1][j],& \text{dp[i-1][j-1]>=r.}
\end{cases}$

可以数组降维，将第一维删去，然后倒着更新。暴力 DP 伪代码：
```cpp
for(int i = 1; i <= n; i++) {
	for(int j = n; j >= 1; j--) {
		if(dp[j - 1] < l[i]) dp[j] = Min(dp[j], l[i]);
		if(l[i] <= dp[j - 1] && dp[j - 1] < r[i]) dp[j] = Min(dp[j], dp[j - 1] + 1);
	}
}
```
在考虑用平衡树优化。

由于是从后往前更新，所以先考虑第二类 dp 的影响。第二类 dp 可以分解为三部：
1. 先删除第一个大于等于 $r$ 的点。
2. 区间 $[l,r)$ 的所有数平移为 $[l+1,r+1)$ 。
3. 最后插入实行第二部前，第一个大于等于 $l$ 的数。

值得注意的是，若区间 $[l,r)$ 没有任何数，则忽略第二步操作。

在执行第一类 dp ，可以发现，它只更新一个数，即第一个大于等于 $l$ 的数。具体分为两步：
1. 先删除第一个大于等于 $l$ 的数。
2. 插入 $l$ 。

可以将其合并为 $3$ 个操作，即第二类 dp 的 $1$ ， $2$ 操作，与第一类 dp 的 $2$ 操作。

由于涉及到区间操作，需要打懒标记。
# Code
```cpp
#include <cstdio>
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
#define INF 0x3f3f3f3f
const int MAXN = 6e5 + 5;
int n, ans;
struct Splay_Node {
	int son[2], fa, val, tag;
	#define ls t[pos].son[0]
	#define rs t[pos].son[1]
};
struct Splay_Tree {
	Splay_Node t[MAXN];
	int root, tot, Top, stk[MAXN];
	int Ident(int pos) { return t[t[pos].fa].son[1] == pos ? 1 : 0; }
	void Connect(int pos, int fa, int flag) { t[fa].son[flag] = pos, t[pos].fa = fa; }
	void Push_Down(int pos) {
		if(!t[pos].tag) return;
		if(ls) { t[ls].val += t[pos].tag, t[ls].tag += t[pos].tag; }
		if(rs) { t[rs].val += t[pos].tag, t[rs].tag += t[pos].tag; }
		t[pos].tag = 0;
	}
	int New(int val, int fa) { t[++tot].fa = fa, t[tot].val = val; return tot; }
	void Build() { root = New(-INF, 0); t[root].son[1] = New(INF, root); }
	void Rotate(int pos) {
		int fa = t[pos].fa, grand = t[fa].fa;
		int flag1 = Ident(pos), flag2 = Ident(fa);
		Connect(pos, grand, flag2);
		Connect(t[pos].son[flag1 ^ 1], fa, flag1);
		Connect(fa, pos, flag1 ^ 1);
	}
	void Splay(int pos, int to) {
		int tmp = pos; Top = 0;
		stk[++Top] = tmp;
		while(tmp) stk[++Top] = tmp = t[tmp].fa;
		while(Top) Push_Down(stk[Top--]);//以上为释放懒标记
		for(int fa = t[pos].fa; t[pos].fa != to; Rotate(pos), fa = t[pos].fa)
			if(t[fa].fa != to) Ident(pos) == Ident(fa) ? Rotate(fa) : Rotate(pos);
		if(!to) root = pos;
	}
	void Insert(int &pos, int val, int fa) {
		if(!pos) { ++ans; pos = New(val, fa); Splay(pos, 0); return; }
		Push_Down(pos);//几乎每个操作都有释放懒标，别忘了
		if(val < t[pos].val) Insert(ls, val, pos);
		else Insert(rs, val, pos);
	}
	void Erase(int pos) {
		Splay(pos, 0);
		int l = ls, r = rs;
		while(t[l].son[1]) l = t[l].son[1];
		while(t[r].son[0]) r = t[r].son[0];
		Splay(l, 0); Splay(r, l);
		t[r].son[0] = 0; --ans;
	}
	int Get_Pre(int val) {//查找第一个小于val的点的编号
		int pos, res, newroot;
		pos = newroot = root;
		while(pos) {
			Push_Down(pos);
			if(t[pos].val < val) { res = pos; pos = rs; }
			else pos = ls;
		}
		Splay(newroot, 0);
		return res;
	}
	int Get_Nxt(int val) {//查找第一个大于val的点的编号
		int pos, res, newroot;
		pos = newroot = root;
		while(pos) {
			Push_Down(pos);
			if(t[pos].val > val) { res = pos; pos = ls; }
			else pos = rs;
		}
		Splay(newroot, 0);
		return res;
	}
	void Move(int l, int r) {//平移区间[l,r)
		int u = Get_Nxt(l - 1), v = Get_Pre(r);
		if(t[u].val > t[v].val) return;//没有数字就跳过
		if(u == v) t[u].val++;
		else if(t[u].val < t[v].val) {
			Splay(u, 0); Splay(v, u);
			int rson = t[v].son[0];
			++t[u].val; ++t[v].val, t[rson].val++;
			if(rson) ++t[rson].tag;
		}
	}
};
Splay_Tree tree;
int main() {
	Read(n); tree.Build();
	tree.Insert(tree.root, 0, 0); ans = 0;
	for(int i = 1, l, r; i <= n; i++) {
		Read(l, r);
		int pos = tree.Get_Nxt(r - 1);
		if(pos && pos != 1 && pos != 2) tree.Erase(pos);
		tree.Move(l, r);
		tree.Insert(tree.root, l, 0);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：CLZY (赞：4)

## 传送门

​	[洛谷](https://www.luogu.com.cn/problem/CF809D)

​	[codeforces](https://codeforces.com/problemset/problem/809/D)

## SOLUTION

​	我们设 $dp[j]$ 表示最长上升子序列长度为 $j$ 时末尾的最小值，初始化为 $inf$ ，那么考虑枚举到了第 $i$ 个区间，对于 $1\leq j \leq n$ 来说

​	$dp[j]=min(dp[j-1],l)$ $(dp[j-1] < l)$

​	$dp[j]=min(dp[j-1]+1,dp[j])$ $(l \le dp[j-1]<r)$

​	$dp[j] = dp[j] $ $(dp[j-1]\ge r)$

​	那么根据以上式子我们可以得到 $n^2$ 的优秀做法。但是由于原题中 $n\le 3*10^5+7$ ，所以说这样肯定不行，考虑优化。

​	我们会发现 $dp$ 过程中的任意时刻，对于每个 $<n$ 的 $j$ ，一定满足：

​	$dp[j] \le dp[j+1]$

​	因此我们可以用平衡树来维护所有的 $dp[j]$ 。

​	再考虑每次扫到一个新的区间时， $dp[j]$ 对 $dp[j+1]$ 的贡献。

​	如果该转移满足第一行式子（即 $dp[j]<l$ ），那么我们一定会有某个 $dp[j+1]$ 是等于 $l$ 的，而转移过去的 $dp[j]$ 一定是小于 $l$ 的最大的一个，那么此时的 $dp[j+1]$ 一定不劣，所以在 $j$ 的后面一个序号处强行添加一个 $l$ 就行了。

​	如果满足第二行式子 $l\le dp[j]<r$ ，我们可以将所有这一部分的 $dp[j]$ 的值 $+1$ ，并且编号 $+1$ ，来代替第二个转移，又因为我们刚刚本来就强行加入了一个，所以只需要值 $+1$ 就行了。

​	如果有 $ dp[j]$ 满足第三行式子，那么此时这些 $dp[j]$ 无法进行任何转移，但是因为之前的 $dp[j]$ 编号 $+1$ ，此时大于等于 $r$ 且最小的 $dp[j]$ 可以被前面的替换掉，实现就行将其删除。

​	具体实现就是每次考虑一个新的区间，把平衡树中值域在 $[l,r-1]$ 之间的点的权值整体 $+1$ ，删除 $r$ 的后继（如果有的话），再加入一个 $l$ 就行了。

## 代码

注意代码中要注意pushdown和旋转的顺序，避免~~像本蒟蒻一样~~炸锅。

特别提醒：写splay的同学一定要注意splay的形态，否则会T惨。

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define req(i,r,l) for(ll i=(r);i>=(l);--i)
#define wif while
const ll inf = INT_MAX , df = 3e5 + 7 ;
ll fa[df] , cnt[df] , sum[df] , ls[df] , rs[df] , val[df] , sta[df] , top , n , root , tag[df] , tot ;
inline ll read()	{
	ll x = 0 , y = 1 ; char ch = getchar() ;
	wif( ch > '9' || ch < '0') 		y = ( ch == '-' ) ? - 1 : 1 , ch = getchar() ;
	wif( ch >= '0' && ch <= '9' )	x = ( x << 3 ) + ( x << 1 ) + ch - '0' , ch = getchar() ;
	return x * y ;	}
void pushup( ll x )	{	sum[x] = sum[ls[x]] * ( ls[x] != 0 ) + sum[rs[x]] * ( rs[x] != 0 ) + cnt[x] ;	}
void pushdown( ll x )	{
	if( ls[x] ) val[ls[x]] += tag[x] , tag[ls[x]] += tag[x] ;
	if( rs[x] )	val[rs[x]] += tag[x] , tag[rs[x]] += tag[x] ;
	tag[x] = 0 ;	return ;	}
void merge( ll x )	{
	ll y = fa[x] , z = fa[y] ;
	fa[x] = z , fa[y] = x ;
	if( ls[z] == y )	ls[z] = x ;	else	rs[z] = x ;
	if( ls[y] == x )	ls[y] = rs[x] , rs[x] = y , fa[ls[y]] = y ;
	else				rs[y] = ls[x] , ls[x] = y , fa[rs[y]] = y ;
	pushup( y ) , pushup( x ) ;	}
void splay( ll x , ll rt )	{
	top = 1 ; sta[top] = x ;
	for( ll y = x ; y != rt ; y = fa[y] )	sta[ ++ top ] = fa[y] ;
	req(i,top,1)	pushdown( sta[i] ) ;
	for( ll y = 0 ; ( y = fa[x] ) != rt ; merge(x) )
		if( fa[y] != rt )	merge( ( ( ls[y] == x ) ^ ( ls[fa[y]] == y ) ) ? x : y ) ;
	if( ! rt )	root = x ;
	return ;	}
ll get_back( ll u , ll x )	{
	ll lst = 0 , ret = 0 ;
	wif(u)	{
		if( x < val[u] )	lst = u , pushdown(u) , u = ls[ ret = u ] ;
		else				lst = u , pushdown(u) , u = rs[u] ;
	}
	splay( lst , 0 ) ;	return ret ;	}
ll get_front( ll u , ll x )	{
	ll lst = 0 , ret = 0 ;
	wif(u)	{
		if( x > val[u] )	lst = u , pushdown(u) , u = rs[ ret = u ] ;
		else				lst = u , pushdown(u) ,  u = ls[u] ;
	}
	splay( lst , 0 ) ;	return ret ;	}
void add( ll u , ll x )	{
	wif( x != val[u] )	{
		pushdown(u);
		if( x < val[u] )	{	if( ! ls[u] )	ls[u] = ++ tot , fa[tot] = u , val[tot] = x ; u = ls[u] ;	}
		else				{	if( ! rs[u] )	rs[u] = ++ tot , fa[tot] = u , val[tot] = x ; u = rs[u] ;	}
	}
	++ cnt[u] , ++ sum[u] ;	splay( u , 0 ) ;	}
void det( ll x )	{
	ll u = get_front( root , x ) , v = get_back( root , x ) ;
	splay( u , 0 ) , splay( v , u ) ;
	if( ! ls[v] )	return ;
	-- cnt[ls[v]] , -- sum[ls[v]] , -- sum[v] , -- sum[u] ;
	if( ! sum[ls[v]] )	{	fa[ls[v]] = 0 ; ls[v] = 0 ;	}
	return ;	}
void modity( ll l , ll r )	{
	ll x = get_front( root , l ) , y = get_back( root , r - 1 ) ;
	splay( x , 0 ) , splay( y , x ) ;
	if( ls[y] )	val[ls[y]] ++ , tag[ls[y]] ++ ;
	return ;	}
int main()	{
	n = read() ;
	add( root , inf ) , add( root , - inf ) ;
	rep( i , 1 , n )	{
		ll l = read() , r = read() ;
		if( i == 1 )	{	add( root , l );	continue ;	}
		ll x = get_back( root , r - 1 ) ;
		modity( l , r ) ;
		if( val[x] < inf )	det( val[x] ) ;
		add( root , l ) ;
		splay( 1 , 0 ) ;
	}
	return printf( "%lld\n" , sum[ root ] - 2 ) , 0 ;
}
```

---

## 作者：RockyYue (赞：2)

# 思路

### Step1: 直接 DP

- 状态定义

$f[i][j]$ 为 $a[1] \rightarrow a[i]$ 中取长度为 $j$ 的严格上升子序列时最后一个数的最小值。

- 状态转移

分三种情况讨论：

1. $f[i-1][j-1]<l$：$f[i][j]=l$；
2. $f[i-1][j-1]	\ge r$：状态不合法，不用转移了；
3. $l \le f[i-1][j-1] < r$：$f[i][j]=f[i-1][j-1]+1$。

### Step2: Splay 优化

- 对于第一种，$f[i-1][j-1]$ 没用，直接赋值即可；
- 对于第三种，比较麻烦，可以先把最靠 $r$ 的 $f$ 删除，再插入一个 $l$，就可以移动整个区间。
- 题目思维很巧妙，但代码比较难实现（


# 代码

常数比较大，卡了挺长时间常才 AC 的（

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
struct node {
    int s[2], fa, v, tag;
} t[N];
#define ls t[id].s[0]
#define rs t[id].s[1]
inline void rotate(int id) {
	int fa = t[id].fa, ffa = t[fa].fa;
	node &pre = t[id], &f1 = t[fa], &f2 = t[ffa];
	bool c = f1.s[1] == id, cc = c ^ 1, c1 = f2.s[1] == fa;
	if (ffa) {
		f2.s[c1] = id;
	}
	int &son = pre.s[cc];
	pre.fa = ffa, f1.s[c] = son;
	if (son) {
		t[son].fa = fa;
	}
	son = fa, f1.fa = id;
}
inline void pushdown(int id) {
	if (!t[id].tag) {
        return ;
    }
    int &tt = t[id].tag;
	if (ls) {
        t[ls].v += tt, t[ls].tag += tt;
    }
	if (rs) {
        t[rs].v += tt, t[rs].tag += tt;
    }
    tt = 0;
}
int root;
void splay(int id, int f) {
	stack<int> S;
	S.push(id);
	for (int i = id; t[i].fa; i = t[i].fa) {
		S.push(t[i].fa);
	}
	while (S.size()) {
		pushdown(S.top()), S.pop();
	}
	while (t[id].fa != f) {
		int fa = t[id].fa, ffa = t[fa].fa;
		if (ffa != f) {
			rotate((t[fa].s[0] == id) == (t[ffa].s[0] == fa) ? fa : id);
		}
		rotate(id);
	}
	if (!f) {
		root = id;
	}
}
int find(int x) {
	int id = root, res = 0;
	while (id) {
		pushdown(id);
		if (t[id].v < x) {
			res = id, id = rs;
		} else {
			id = ls;
		}
	}
	return res;
}
inline int Nxt(int id) {
    splay(id, 0), id = rs;
    while (ls) {
        id = ls;
    }
    return id;
}
inline int Pre(int id) {
    splay(id, 0), id = ls;
    while (rs) {
        id = rs;
    }
    return id;
}
inline void del(int id) {
	int pre = Pre(id), nxt = Nxt(id);
	splay(pre, 0), splay(nxt, pre);
	t[nxt].s[0] = t[id].fa = 0;
}
int k;
void ins(int x) {
	int id = root, fa = 0;
	while (id) {
		pushdown(id);
		fa = id, id = t[id].v > x ? ls : rs;
	}
	id = ++k;
	if (fa) {
		bool tt = t[fa].v <= x;
        t[fa].s[tt] = id;
    }
	t[id].fa = fa, t[id].v = x;
    splay(id, 0);
}
int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    ins(-1e9 - 10), ins(1e9 + 10);
    int n;
    cin >> n;
	int res = n;
    while (n--) {
    	int l, r;
    	cin >> l >> r;
        int u = find(l), v = find(r), nxt = Nxt(v);
        if (u ^ v) {
            splay(u, 0), splay(nxt, u);
            node &nxtt = t[t[nxt].s[0]];
            ++nxtt.v, ++nxtt.tag;
        }
        if (nxt != 2) {
            del(nxt), --res;
        }
        ins(l);
    }
    cout << res << '\n';
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF809D)

平衡树优化 $\tt dp$，好题。来补个题解。

## 朴素 $\tt dp$

维护 $dp_i$ 代表长度为 $i$ 的 $\tt LIS$ 时最后一位的最小值。用每个区间 $l_j,r_j$ 进行转移，转移方程如下：

$$
\begin{cases}
dp_i=\min(l)&dp_{i-1}\lt l&(1)\\
dp_i=\min(dp_{i-1}+1)&dp_{i-1}\in[l,r)&(2)\\
\end{cases}
$$

注意当 $dp_{i-1}\ge r$ 时无法从 $l,r$ 来转移 $dp_i$。$\quad(3)$

这样的转移是 $n^2$ 的，考虑优化。

## 平衡树优化

考虑使用平衡树来动态维护这个 $\tt LIS$，每一次读入一个 $L_i,R_i$ 就删除掉无法对后面决策产生帮助的 $dp$ 值。

+ 由 $(2)$，我们在平衡树里找到最长的一个区间 $I$ 使得 $\forall j\in I,dp_j-1\in[l,r]$，然后将其集体右移。
+ 由 $(1)$，我们在平衡树里插入 $l$，填补至右移多出的空位。
+ 由 $(3)$，我们在平衡树里删除 $r$ 的后继，当然不存在就别管。

## 实现

我写的 $\texttt{FHQ-Treap}$。

[$\tt Code$](https://www.luogu.com.cn/paste/8tu6180c)

---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF809D) & [CodeForces题目页面传送门](https://codeforces.com/contest/809/problem/D)

>题意见洛谷里的翻译。

一脸DP的样，于是考虑DP。

与普通的LIS类似，设$dp_{i,j}$表示考虑到第$i$个数，最后一位为$a_i=j$的LIS长度。显然，第二维是定义在值域$\left[1,10^9\right]$上的，无论如何优化它都会出现在时间/空间复杂度上，受不起。于是考虑一种惯用套路，将DP数组的定义域和值域调换，即设$dp_{i,j}$表示考虑到第$i$个数，长度为$j$的IS的最后一位最小为多少（如果无法实现则为$\infty$）。

边界为$dp_{0,i}=\begin{cases}0&i=0\\\infty&i>0\end{cases}$，目标为$\max\limits_{i\in[1,n],dp_{n,i}<\infty}\{i\}$，状态转移方程为$dp_{i,j}=\min\begin{cases}dp_{i-1,j}\\\max(l_i,dp_{i-1,j-1}+1)&dp_{i-1,j-1}<r\end{cases}$（显然，基于贪心，若选$a_i$，那么在可能情况下$a_i$越小越好）。这样空间复杂度可以用滚动数组压到$\mathrm O(n)$，但时间复杂度是$\mathrm O\!\left(n^2\right)$的。考虑优化。

注意到转移时的最优决策只可能为$dp_{i-1,j},l_i,dp_{i-1,j-1}+1$这$3$种，于是分情况讨论：

1. 转移到$l_i$。当且仅当$\begin{cases}l_i\geq dp_{i-1,j-1}+1\\l_i\leq dp_{i-1,j}\end{cases}$。不难发现，$\forall i\in[0,n]$，$dp_i$不为$\infty$的那部分是严格单调上升的（易证）。于是我们设$las$为最大的$j$使得$dp_{i-1,j}<l_i$。那么$\begin{cases}l_i\geq dp_{i-1,j-1}+1\\l_i\leq dp_{i-1,j}\end{cases}\Rightarrow\begin{cases}j-1\leq las\\j>las\end{cases}\Rightarrow j=las+1$；
2. 转移到$dp_{i-1,j-1}+1$。当且仅当$\begin{cases}dp_{i-1,j-1}+1>l_i\\dp_{i-1,j-1}+1\leq dp_{i-1,j}\\dp_{i-1,j-1}<r\end{cases}$（$dp_{i-1,j-1}+1=l_i$归在情况$1$里）。根据单调性，$dp_{i-1,j-1}+1\leq dp_{i-1,j}$显然恒成立。设$las'$为最大的$j$使得$dp_{i-1,j}<r_i$。那么$\begin{cases}dp_{i-1,j-1}+1>l_i\\dp_{i-1,j-1}<r\end{cases}\Rightarrow\begin{cases}j-1>las\\j-1\leq las'\end{cases}\Rightarrow j\in[las+2,las'+1]$；
3. 转移到$dp_{i-1,j}$。不满足情况$1,2$的条件则为此情况。

我们可以维护$dp_i$这个数列，每此转移即令$dp_i=dp_{i+1}$。不难发现，这样想的话，情况$3$相当于什么也不做~~，正好我们也没分析情况$3$的充要条件~~，于是只需要考虑支持情况$1,2$对应的操作即可。不难想到可以用平衡树维护，这里使用fhq-Treap。情况$1$就是个单点修改；情况$2$可以转化为剖出区间$[las+1,las']$后，删除第$las'+1$个元素并将第$las+1$个元素在原位拷贝一份，然后区间增加$1$。与情况$2$一综合，可以把“单点修改、将第$las+1$个元素在原位拷贝一份”简化成“在第$las+1$个元素的位置添加”~~（当然不简化也没必要）~~。这里面涉及到删除操作，由于本憨憨不想算总共会新建多少个节点，而且正好找个机会练习一下，于是采用垃圾回收，显然任意时刻元素数$\leq|[0,n]|=n+1$。

时间复杂度$\mathrm O(n\log n)$，空间复杂度$\mathrm O(n)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define X first
#define Y second
const int inf=0x3f3f3f3f;
mt19937 rng(20060617/*信仰优化*/);
const int N=300000;
int n;//数的数量 
int l[N+1],r[N+1];//限制区间 
struct fhq_treap{//fhq-Treap 
	int sz/*点数*/,root/*根*/;
	struct node{unsigned key;int lson,rson,sz,v,lz;}nd[N+2];
	#define key(p) nd[p].key
	#define lson(p) nd[p].lson
	#define rson(p) nd[p].rson
	#define sz(p) nd[p].sz
	#define v(p) nd[p].v
	#define lz(p) nd[p].lz
	stack<int> rub;//垃圾栈 
	void recyc(int p){rub.push(p);}//垃圾回收 
	int nwnd(int v){//新建节点 
		int p;
		if(rub.size())p=rub.top(),rub.pop();//垃圾再利用 
		else p=++sz;
		return nd[p]=node({rng(),0,0,1,v,0}),p;
	}
	void sprup(int p){sz(p)=sz(lson(p))+1+sz(rson(p));}//上传 
	void sprdwn(int p){//下传 
		if(lz(p)){
			v(lson(p))+=lz(p);v(rson(p))+=lz(p);
			lz(lson(p))+=lz(p);lz(rson(p))+=lz(p);
			lz(p)=0;
		}
	}
	int bld(int l=0,int r=n){//建树 
		int mid=l+r>>1,p=nwnd(mid?inf:0);
		if(l<=mid-1)lson(p)=bld(l,mid-1);
		if(mid+1<=r)rson(p)=bld(mid+1,r);
		return sprup(p),p;
	}
	void init(){//fhq-Treap初始化 
		nd[sz=0]=node({0,0,0,0,0,0});
		root=bld();
	}
	pair<int,int> split(int x,int p=-1){~p||(p=root);
		if(!x)return mp(0,p);
		pair<int,int> sp;
		sprdwn(p);
		if(x<=sz(lson(p)))return sp=split(x,lson(p)),lson(p)=sp.Y,sprup(p),mp(sp.X,p);
		return sp=split(x-sz(lson(p))-1,rson(p)),rson(p)=sp.X,sprup(p),mp(p,sp.Y);
	}
	int mrg(int p,int q){
		if(!p||!q)return p|q;
		sprdwn(p);sprdwn(q);
		if(key(p)<key(q))return rson(p)=mrg(rson(p),q),sprup(p),p;
		return lson(q)=mrg(p,lson(q)),sprup(q),q;
	}
	int lss(int v,int p=-1)/*以p为根的子树内<v的数的数量*/{~p||(p=root);
		if(!p)return 0;
		sprdwn(p);
		if(v(p)<v)return sz(lson(p))+1+lss(v,rson(p));
		return lss(v,lson(p));
	}
	void trs(int x){//转移 
		pair<int,int> sp=split(lss(l[x]));
		if(!sp.Y)return;
		pair<int,int> sp0=split(lss(r[x],sp.Y),sp.Y); 
		if(sp0.Y){
			pair<int,int> sp1=split(1,sp0.Y);
			recyc(sp1.X);//删除并回收 
			v(sp0.X)++;lz(sp0.X)++;//区间增加 
			root=mrg(mrg(mrg(sp.X,nwnd(l[x])/*添加*/),sp0.X),sp1.Y);
		}
		else{
			pair<int,int> sp1=split(sz(sp0.X)-1,sp0.X);
			recyc(sp1.Y);//删除并回收 
			v(sp1.X)++;lz(sp1.X)++;//区间增加 
			root=mrg(mrg(sp.X,nwnd(l[x])/*添加*/),sp1.X);
		}
	}
	int at(int x,int p=-1)/*第x个元素（0-indexed）*/{~p||(p=root);
		sprdwn(p);
		if(sz(lson(p))+1==x+1)return v(p);
		if(sz(lson(p))>=x+1)return at(x,lson(p));
		return at(x-sz(lson(p))-1,rson(p));
	}
	void dfs(int p=-1)/*调试用*/{~p||(p=root);
		if(!p)return;
		sprdwn(p);
		dfs(lson(p));
		cout<<v(p)<<" ";
		dfs(rson(p));
	}
}dp;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	dp.init();//fhq-Treap初始化 
	for(int i=1;i<=n;i++)dp.trs(i)/*,dp.dfs(),puts("")*/;//转移 
//	for(int i=0;i<=n;i++)cout<<dp.at(i)<<" ";puts("");
	for(int i=n;;i--)if(dp.at(i)<inf)return cout<<i,0;//计算答案 
	return 0;
}
```

---

## 作者：Biscuit46 (赞：1)

# 题面
[原题](http://codeforces.com/problemset/problem/809/D)

# Solution
这是今天做的题目之中思维难度和代码难度最大的一道题.

首先我们考虑DP.

一般的LIS都是设
```cpp
f[i]表示以i结尾的LIS中的最小值.
```
那么不难列出转移方程
```cpp
f[i]=min(f[i],f[i-1]+1);
```
思考一下对于每一个i的限制,必然会对一段区间造成影响:即该段区间中(第一个大于l的位置)的到(第一个大于r的位置-1),这就是可以被影响的区间.

那么考虑如何维护,对于这一段区间,相当于是把这段区间向后平移1位并且把第一个大于l的位置赋值为l,那么动态修改与动态查询不难想到用平衡树维护.

代码如下:

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
inline int gi(){
    int f=1,sum=0;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
int ncnt;
struct Treap{
    Treap *l,*r;
    int val,siz,key,add;
    inline void tain(){//update
        if(add){
            if(l){l->add+=add;l->val+=add;}
            if(r){r->add+=add;r->val+=add;}
            add=0;
        }
    }
    void upt(){siz=(l?l->siz:0)+(r?r->siz:0)+1;}
    Treap(){}
    Treap(int v){
        add=0;val=v;key=rand();l=r=NULL;siz=1;
    }
}pool[600010],*rt;
int a[600010];
inline int size(Treap*x){return x?x->siz:0;}
Treap *Merge(Treap*a,Treap*b){//合并a,b树
    if(a==NULL)return b;
    if(b==NULL)return a;
    a->tain();b->tain();
    if(a->key<b->key){
        a->r=Merge(a->r,b);a->upt();return a;
    }
    else{
        b->l=Merge(a,b->l);b->upt();return b;
    }
}
typedef pair<Treap*,Treap*> DTreap;
DTreap Split(Treap *o,int k){//分离k个节点
    if(!o)return DTreap(NULL,NULL);
    o->tain();
    DTreap y;
    if(size(o->l)>=k){
        y=Split(o->l,k);o->l=y.second;o->upt();y.second=o;
    }
    else{
        y=Split(o->r,k-size(o->l)-1);o->r=y.first;
        o->upt();y.first=o;
    }
    return y;
}
DTreap Split_val(Treap *o,int k){//分离k个节点
    if(!o)return DTreap(NULL,NULL);
    o->tain();
    DTreap y;
    if(o->val>k){
        y=Split_val(o->l,k);o->l=y.second;o->upt();y.second=o;
    }
    else{
        y=Split_val(o->r,k);o->r=y.first;
        o->upt();y.first=o;
    }
    return y;
}
void bianli(Treap *x){
    if(!x)return;
    x->tain();
    bianli(x->l);
    a[++*a]=x->val;
    bianli(x->r);
}
int main(){
    srand(19260817);
    int n=gi();
    pool[++ncnt]=Treap(0); rt=Merge(rt,pool+ncnt);
    for (int i=1;i<=n;i++)
        pool[++ncnt]=Treap((1<<30)+1),rt=Merge(rt,pool+ncnt);
    for (int i=1;i<=n;i++){
        int l=gi(),r=gi();
        DTreap x=Split_val(rt,l-1);
        DTreap y=Split_val(x.second,r-1);
        DTreap z=Split(y.second,1);
        pool[++ncnt]=Treap(l);
        rt=Merge(x.first,pool+ncnt);
        if (y.first) y.first->val++,y.first->add++;
        rt=Merge(rt,y.first);
        rt=Merge(rt,z.second);
    }
    *a=0; bianli(rt);
    int i; for (i=1;i<=n && a[i+1]<1<<30;i++); i--;
    printf("%d\n",i);
    return 0;
}
```

---

