# Permutation Graph

## 题目描述

给出一个 $1$ 到 $n$ 的排列 $ [a_1,a_2,\dots,a_n] $ 。对于 $1\le i < j\le n$ ，记 $ \operatorname{mn}(i,j) $ 为 $\min\limits_{k=i}^j a_k$ ，记  $ \operatorname{mx}(i,j) $ 为 $ \max\limits_{k=i}^j a_k $ 。

有一张 $n$ 个点的无向图，点的编号为 $1$ 到 $n$ 。对于每一对整数 $ 1\le i<j\le n $ ，如果同时满足 $ \operatorname{mn}(i,j)=a_i $ 且 $ \operatorname{mx}(i,j)=a_j $ ，或同时满足 $ \operatorname{mn}(i,j)=a_j $ 和 $ \operatorname{mx}(i,j)=a_i $ ，那么就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。

询问这张图中从 $1$ 到 $n$ 的最短路的长度。可以证明 $1$ 和 $n$ 总是连通，所以最短路总是存在。

## 样例 #1

### 输入

```
5
1
1
2
1 2
5
1 4 2 3 5
5
2 1 5 3 4
10
7 4 8 1 6 10 3 5 2 9```

### 输出

```
0
1
1
4
6```

# 题解

## 作者：lg_zhou (赞：11)

很显然，全局最大值和全局最小值之间必走一次。因为任意一次不可能跨越全局最小或全局最大。若设全局最大在全局最小前面，那么我们前面最多一次性跨越到全局最大，下一步一次跳到全局最小一定是最优的。

那我们预处理出 st 表，这里用 `pair` 可以很方便的求出最大值最小值位置。然后分治处理。

$\operatorname{solve}(l,r)=\operatorname{solve}(l,p1)+\operatorname{solve}(p2,r)+1$，$p1,p2$ 为最大值最小值的位置，如果 $p2$ 小， `swap` 一下即可。


```cpp
#include<iostream>
#include<cmath>
#include<algorithm>

#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N = 2.5e5+5;

int T,n;
int a[N];

pii mx[N][20], mn[N][20]; 


void mul(){
	for (int i = 1; i <= 20; i++){
		for (int j = 1; j+(1<<i-1) <= n; j++){
			mx[j][i] = max(mx[j][i-1],mx[j+(1<<i-1)][i-1]);
			mn[j][i] = min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
		}
	}
}
pii getmx(int l, int r){
	int lg = log2(r-l+1);
	return max(mx[l][lg],mx[r-(1<<lg)+1][lg]);
}
pii getmn(int l, int r){
	int lg = log2(r-l+1);
	return min(mn[l][lg],mn[r-(1<<lg)+1][lg]);
}

int solve(int l, int r){
	if (r == l) return 0;
	int p1 = getmx(l,r).se, p2 = getmn(l,r).se;
	if (p1 > p2) swap(p1,p2);
	return solve(l,p1)+1+solve(p2,r);
}
int main(){
//	freopen("a.in","r",stdin);
	cin >> T;
	while(T--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			mx[i][0].fi = mn[i][0].fi = a[i];
			mx[i][0].se = mn[i][0].se = i;
		}
		mul();
		cout << solve(1,n) << endl;
	}
	
	return 0;
}
```


---

## 作者：lenlen (赞：9)

提供一种 ST 表 + 二分的做法，时间复杂度 $O(n \log n)$。

### Problem

题目大意：给定一个序列 $a$，每次你可以从 $l$ 跳到 $r$，$l,r$ 满足 $\min\limits_{i=l}^r a_i=a_l,\max\limits_{i=l}^r a_i=a_r$ 或者 $\min\limits_{i=l}^r a_i=a_r,\max\limits_{i=l}^r a_i=a_l$，求 $1,n$之间的最短路。

数据范围： $\sum n \leq 5 \times 10^5,t \leq 5 \times 10^4,a_i \leq n$。

### Solution

首先我们要证明一个东西，就是最短路必定不会往回跳。

证明：我们假设当前我们在 $i$ 点，我们要跳到 $j$ 点去，而最优方法是往回跳到 $k$ 再跳到 $j$。

我们假设 $a_i>a_j$，那么我们可以把 $k$ 跳到 $j$ 路径上的点标出来，可以发现该路径上在 $[i,j]$ 的点不管是由小跳到大还是大跳到小的任何一点，都可以被 $i$ 直接跳到，而 $k$ 即使路径上的点都在 $[i,j]$ 内，也会比 $i$ 跳到 $j$ 多跳一次 $(i \Rightarrow k)$，假设不成立。证毕。

所以我们只需要尽量往右跳就可以了。

因为不会往回跳，所以跳得尽量远是优的，所以我们可以枚举 $i$，找出以 $a_i$ 为最大值能到达的最远路径和以 $a_i$ 为最小值能跳到的最远路径。

最大值最小值我们可以用 ST 表维护一下，而我们可以发现，若 $r$ 满足 $\max\limits_{i=l}^r a_i=a_l$，那么显然 $\max\limits_{i=l}^{r-1} a_i=a_l$；同时若 $\max\limits_{i=l}^r a_i>a_l$，那么显然 $\max\limits_{i=l}^{r+1} a_i>a_l$。所以最远距离显然具有单调性，我们可以用二分来查找能跳到的最远的满足条件的地方并更新即可。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+7232,inf=1e9+7;
int t,n;
int lg[N],dp[N];
int f[N][27],ff[N][27],g[N][27],gg[N][27];
//都是快读
const int Mt=1e5;
inline char getc(){
	static char buf[Mt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int r=0,f=1;char c=getc();
	while(!isdigit(c)){if(c=='-')f=-1;c=getc();}
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getc();
	return r*f;
}
//都是快读
int mx(int x,int y)
{
    return x>y?x:y;
}
int mi(int x,int y)
{
    return x>y?y:x;
}
bool check1(int l,int r)
{
    int tmp=lg[r-l+1];
    if(f[l][0]==mx(f[l][tmp],f[r-(1<<tmp)+1][tmp])) return true;
    return false;
}
bool check2(int l,int r)
{
    int tmp=lg[r-l+1];
    if(g[l][0]==mi(g[l][tmp],g[r-(1<<tmp)+1][tmp])) return true;
    return false;
}
int main()
{
	t=read();
    for(int i=2;i<=250000;i++) lg[i]=lg[i>>1]+1;//预处理log2，单个n大小为250000
    while(t--)
    {
        n=read();
        for(int i=2;i<=n;i++) dp[i]=inf;//如果你用memset的话，恭喜你喜提第三点 TLE
        dp[1]=0;
        for(int i=1;i<=n;i++) f[i][0]=read(),ff[i][0]=i,g[i][0]=f[i][0],gg[i][0]=i;
        for(int i=1;i<=lg[n];i++)
        for(int j=1;j+(1<<i-1)<=n;j++)
        {
            //f维护区间最大，ff维护区间最大的位置，g维护区间最小，gg维护区间最小的位置
            if(f[j][i-1]>f[j+(1<<i-1)][i-1]) f[j][i]=f[j][i-1],ff[j][i]=ff[j][i-1];
            else f[j][i]=f[j+(1<<i-1)][i-1],ff[j][i]=ff[j+(1<<i-1)][i-1];
            if(g[j][i-1]<g[j+(1<<i-1)][i-1]) g[j][i]=g[j][i-1],gg[j][i]=gg[j][i-1];
            else g[j][i]=g[j+(1<<i-1)][i-1],gg[j][i]=gg[j+(1<<i-1)][i-1];
        }
        for(int i=1;i<=n;i++)
        {
            int l=i,r=n,sum;
            while(l<=r) //以ai为最大值
            {
                int mid=l+r>>1;
                if(check1(i,mid)) sum=mid,l=mid+1;
                else r=mid-1;
            }
            int tmp=lg[sum-i+1];
            if(g[i][tmp]>g[sum-(1<<tmp)+1][tmp]) dp[gg[sum-(1<<tmp)+1][tmp]]=mi(dp[gg[sum-(1<<tmp)+1][tmp]],dp[i]+1);
            else dp[gg[i][tmp]]=mi(dp[gg[i][tmp]],dp[i]+1);
            l=i,r=n;
            while(l<=r)//以ai为最小值
            {
                int mid=l+r>>1;
                if(check2(i,mid)) sum=mid,l=mid+1;
                else r=mid-1;
            }
            tmp=lg[sum-i+1];
            if(f[i][tmp]<f[sum-(1<<tmp)+1][tmp]) dp[ff[sum-(1<<tmp)+1][tmp]]=mi(dp[ff[sum-(1<<tmp)+1][tmp]],dp[i]+1);
            else dp[ff[i][tmp]]=mi(dp[ff[i][tmp]],dp[i]+1);
        }
        printf("%d\n",dp[n]);
    }
}
```
总复杂度就是 $O(n \log n)$ 的了。

---

## 作者：ReTF (赞：4)

看到题解中没有ST表求最值+分治的做法，我就来水一发。

[~~可能~~更好的阅读体验](https://www.luogu.com.cn/blog/Not-A-Tycoon/cf1696d-ti-xie)

[$\Large\textbf{CF1696D}\ \large\text{Permutation Graph}$](https://www.luogu.com.cn/problem/CF1696D)

这道题目给了我们一个 $1$ 到 $n$ 的排列 $a$。如果在这个排列中，$a_i$ 和 $a_j$ 均为区间 $[i,j]$ 的最值（即同时满足 $ \operatorname{min}(i,j)=a_i $ 且 $ \operatorname{max}(i,j)=a_j $ ，或同时满足 $ \operatorname{min}(i,j)=a_j $ 和 $ \operatorname{max}(i,j)=a_i $ ），就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。询问这张图中从 $1$ 到 $n$ 的最短路的长度。

首先定义一对数 $(i,j)$ 是合法的，当且仅当 $a_i$ 和 $a_j$ 均为区间 $[i,j]$ 的最值。

如果我们使用分治来解决此问题，假设当前递归到了区间 $[l,r]$：
> 如果 $(l,r)$ 是合法的，题目中要求我们找最短路，所以直接从 $l$ 到 $r$ 显然是比经过一些别的点再到 $r$ 优的，无需再递归下去。

> 如果 $(l,r)$ 不是合法的且 $a_l$ 和 $a_r$ 中的一个为 $[l,r]$ 的最值，则必定存在至少一个集合 $b$ 满足 $l<b_1<b_2\dots<b_{|b|}<r$，使得 $(l,b_1)$，$(b_{|b|},r)$，$(b_i,b_{i+1})$ 都是合法的。（这个命题是显然正确的，因为最坏情况下 $|b|=(r-l-1)$。）如果 $[l,r]$ 中的另一个最值为 $a_k$，则 $(l,k)$ 和 $(k,r)$ 中有且仅有一个是合法的并且对于任意 $l\le l'<k,k<r'\le r$，$l',r'$ 一定不是合法的（因为 $a_k$ 是最值），合法的区间可以结束递归（同上所述），不合法的区间继续递归下去。

> 如果 $(l,r)$ 不是合法的且 $a_l$ 和 $a_r$ 中的任意一个均不为 $[l,r]$ 的最值，该区间没有任何意义，放弃递归。

如何查询区间最大/最小值？可以使用ST表（代码中有详细注释）。
```cpp
int lg[inf];//预处理出log2的值（c++内置log2函数较慢）
struct node{int v,p;//v代表排列中位置p上的值
	bool operator < (const node &x)const{return x.v<v;}
	bool operator > (const node &x)const{return x.v>v;}
    //重载了大于小于运算符，方便max函数的调用
};
node f[inf][25],g[inf][25];//f数组存最大值，g数组相反
node max_(node x,node y){return (x>y?x:y);}
//返回两者之间值最大的，最大值的位置随着值一并转移
node min_(node x,node y){return (x>y?y:x);}
void apply(int* v_,int top){//预处理
	for(int i=1;i<=top;i++)
		f[i][0]=g[i][0]={v_[i],i};
}
void ST_Table(int top){//预处理
	for(int i=2;i<=top;i++)
        lg[i]=lg[i>>1]+1;//预处理log2
    for(int j=1;j<=23;j++)
    	for(int i=1;i+(1<<j)<=top+1;i++){
    		f[i][j]=max_(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    		g[i][j]=min_(g[i][j-1],g[i+(1<<(j-1))][j-1]);
//预处理，注意用结构体的一个主要目的就是使最值和最值的位置一并转移
		}
}
node query(int l,int r,bool flag){
//st表查询操作，flag=1表示查询的是区间最大，否则为最小
	int k=lg[r-l+1];
	if(flag)return max_(f[l][k],f[r-(1<<k)+1][k]);
	return min_(g[l][k],g[r-(1<<k)+1][k]);
}
```
然后是分治函数：
```cpp
void divide(int l,int r,bool isl,bool flag){
/*这个flag是重点
我们用一个k来记录[l,r]中的最值。如果l,k都为最值，就递归[k,r];
如果r,k都为最值，就递归[l,k]。注意判断l,r均为最值的操作没有在函数内，
而是递归了一层后才完成的。(l==r)

注意程序可能出现卡在l,l+1死循环的情况。需要特判。
*/
	node k=query(l,r,flag);
	if(l==r)return;
	ans++;
	if(l+1>=r)return;
	if(isl){//isl记录l是否为最值
		divide(k.p,r,1,flag^1);
        //若flag是最大值，则k必为最小；反之同理，所以要异或。
	}else{
		divide(l,k.p,0,flag^1);
	}
}
```
附赠[完整代码](https://www.luogu.com.cn/paste/xzw7k2wi)，大家可以自由查看。

---

## 作者：jiangtaizhe001 (赞：4)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16420709.html)

[题目传送门](https://codeforces.com/problemset/problem/1696/D)

### 题目大意
给定一个长度为 $n$ 排列 $a$。  
定义 $\operatorname{mn}(i,j)=\min\limits_{k=i}^{j}a_k,\operatorname{mx}(i,j)=\max\limits_{k=i}^{j}a_k$。  
然后建立一个 $n$ 个节点图，如果 $\operatorname{mn}(i,j)=a_i ,\operatorname{mx}(i,j)=a_j$ 或者 $\operatorname{mn}(i,j)=a_j ,\operatorname{mx}(i,j)=a_i$，那么就在 $i,j$ 之间连一条无向边。  
求 $1$ 号点到 $n$ 号点的最短路。  
$n\le 10^5$
### 题目解析
首先根据连边的条件我们发现在最短路径中肯定不会往回走。  
并且根据定义，如果 $u<v<w$ $u,v$ 和 $u,w$ 之间有边，那么 $v,w$ 之间也肯定有边，所以每次尽量往编号大的节点走。  
问题就转化为了求与当前点有边相连的编号最大的点。  

考虑利用单调栈预处理出每个节点有边第一个比它大/小的点，然后往右跳，并且用线段树 / ST 表求出这一段的最值来判断当前的左端点是否为这个区间的最值即可。  
时间复杂度 $O(n\log n)$

```cpp
int n,ln,a[maxn],rx[maxn],ry[maxn],st[maxn],top;
int minx[maxn<<2],maxx[maxn<<2],L,R;
void up(int rt){ minx[rt]=mmin(minx[rt<<1],minx[rt<<1|1]); maxx[rt]=mmax(maxx[rt<<1],maxx[rt<<1|1]); }
void build(int l,int r,int rt){
	if(l==r){ minx[rt]=maxx[rt]=a[l]; return; } int mid=(l+r)>>1;
	build(l,mid,rt<<1); build(mid+1,r,rt<<1|1); up(rt); return;
}
int findmin(int l,int r,int rt){
	if(L<=l&&r<=R) return minx[rt]; int mid=(l+r)>>1,res=INF;
	if(mid>=L) res=mmin(res,findmin(l,mid,rt<<1));
	if(mid<R) res=mmin(res,findmin(mid+1,r,rt<<1|1));
	return res;
}
int findmax(int l,int r,int rt){
	if(L<=l&&r<=R) return maxx[rt]; int mid=(l+r)>>1,res=-1;
	if(mid>=L) res=mmax(res,findmax(l,mid,rt<<1));
	if(mid<R) res=mmax(res,findmax(mid+1,r,rt<<1|1));
	return res;
}
void work(){
	n=read(); ln=ceil(log2(n)); int i; for(i=1;i<=n;i++) a[i]=read(),rx[i]=ry[i]=0; build(1,n,1);
	top=1; st[top]=1; for(i=2;i<=n;i++){ while(a[st[top]]<a[i]&&top) rx[st[top]]=i,top--; st[++top]=i; }
	top=1; st[top]=1; for(i=2;i<=n;i++){ while(a[st[top]]>a[i]&&top) ry[st[top]]=i,top--; st[++top]=i; }
	int now=1,ri=1,cnt=0;
	while(1){
		now=ri; if(ri==n) break; ri=now+1; cnt++;
		if(a[now]<a[ri]) while(rx[ri]){ L=now; R=rx[ri]; if(findmin(1,n,1)!=a[now]) break; ri=rx[ri]; }
		else while(ry[ri]){ L=now; R=ry[ri]; if(findmax(1,n,1)!=a[now]) break; ri=ry[ri]; }
	} print(cnt),pc('\n');
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen(".out","w",stdout)
	int T=read(); while(T--) work(); return 0;
}
```

---

## 作者：happybob (赞：3)

## 题意

给定一个 $n$ 个数的 **排列** $a$，需要我们构造一张图，两点 $i, j(i < j)$ 相连当且仅当 $a_i$ 和 $a_j$ 为 $a_i, a_{i+1}, \cdots, a_r$ 中的最大值和最小值或最小值和最大值。问 $1$ 号点和 $n$ 号点间的最短路，有边相连的边权为 $1$。

~~赛时就过了 AB，结果第二天 CD 都 $20$ 分钟不到过了。~~

## 解法

考虑贪心。

我们设 $a_i = n$，那么 $a_i$ 就是整个排列的最大值。如果 $i \neq 1$ 且 $i \neq n$，那么从 $1$ 号点到 $n$ 号店显然必须通过点 $i$。

题目转化成处理 $(1, i)$ 和 $(i, n)$ 的最短路之和。而处理这两个显然是等价的，所以先考虑 $(1, i)$。

假设在 $(1, i)$ 中存在 $j(1 < j < i)$ 满足 $j = \min_{k=1}^i a_i$。那么从 $1$ 到 $i$ 一定需要经过点 $j$。那么转化成求 $(1, j)$ 和 $(j, i)$ 的最短路。可以发现 $a_j$ 最小，$a_i$ 最大，所以 $j$ 和 $i$ 一定连边。处理 $(1, j)$ 即可。而处理 $(i, n)$ 同理。显然最大值最小值直接前缀后缀 $O(n)$ 预处理即可。

注意到每次递归，最多只会产生一个分叉，所以总复杂度 $O(\sum n)$，单次 $O(n)$。

官方题解还给了一个数据结构的做法，是 $O(n \log n)$ 的，但我觉得这个贪心更好理解。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const int N = 3e5 + 5;

int t, n, a[N], premax[N], premin[N], sufmax[N], sufmin[N];
int maxp[N], minp[N], smax[N], smin[N];

int ans = 0;

void getans(int x, int y, bool f) // dis(x, y), f为true：最大值，f为false，最小值
{
	if (x == 1)
	{
		if ((premax[y] == a[y] && premin[y] == a[x]) || (premax[y] == a[x] && premin[y] == a[y]))
		{
			ans++;
			return;
		}
	}
	if (y == n)
	{
		if ((sufmax[x] == a[x] && sufmin[x] == a[y]) || (sufmax[x] == a[y] && sufmin[x] == a[x]))
		{
			ans++;
			return;
		}
	}
	if (y == n && x == 1)
	{
		if (premax[y] == a[y])
		{
			getans(1, minp[y], 1);
			ans++;
		}
		else if (premax[y] == a[x])
		{
			getans(minp[y], y, 1);
			ans++;
		}
		else
		{
			getans(1, maxp[y], 0);
			getans(maxp[y], y, 0);
		}
	}
	else
	{
		if (f)
		{
			if (x == 1)
			{
				int place = maxp[y];
				ans++;
				getans(1, place, 0);
			}
			else if (y == n)
			{
				int place = smax[x];
				ans++;
				getans(place, y, 0);
			}
		}
		else
		{
			if (x == 1)
			{
				int place = minp[y];
				ans++;
				getans(1, place, 1);
			}
			else if (y == n)
			{
				int place = smin[x];
				ans++;
				getans(place, y, 1);
			}
		}
	}
}

int main()
{
	memset(premin, 0x3f, sizeof premin);
	memset(sufmin, 0x3f, sizeof sufmin);
	scanf("%d", &t);
	while (t--)
	{
		ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if (n == 1)
		{
			printf("0\n");
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			if (a[i] > premax[i - 1])
			{
				premax[i] = a[i];
				maxp[i] = i;
			}
			else
			{
				premax[i] = premax[i - 1];
				maxp[i] = maxp[i - 1];
			}
			if (a[i] < premin[i - 1])
			{
				premin[i] = a[i];
				minp[i] = i;
			}
			else
			{
				premin[i] = premin[i - 1];
				minp[i] = minp[i - 1];
			}
		}
		for (int i = n; i >= 1; i--)
		{
			if (a[i] > sufmax[i + 1])
			{
				sufmax[i] = a[i];
				smax[i] = i;
			}
			else
			{
				sufmax[i] = sufmax[i + 1];
				smax[i] = smax[i + 1];
			}
			if (a[i] < sufmin[i + 1])
			{
				sufmin[i] = a[i];
				smin[i] = i;
			}
			else
			{
				sufmin[i] = sufmin[i + 1];
				smin[i] = smin[i + 1];
			}
		}
		getans(1, n, 1);
		printf("%d\n", ans);
		for (int i = 1; i <= n + 1; i++)
		{
			premax[i] = sufmax[i] = 0;
			premin[i] = sufmin[i] = 2e9;
			maxp[i] = minp[i] = smax[i] = smin[i] = 0;
		}
	}
	return 0;
}
```


---

## 作者：Morgen_Kornblume (赞：3)

赛时寄了，然后本人很气愤，于是写下此篇题解。

~~（没关系，这可是 ${\color{black}j}{\color{red}iangly}$ 江老板都没有做出来的绝世大好题啊！！！）~~

然而看过题解之后 $O(n)$ 算法还是一概不会，于是只能思维不够 DS 来凑，然而 D 题撑死也不会有什么奇葩东西，所以就选择了线段树板子来做区间最大和最小值的查询（甚至是静态不带修）（然而是线段树板子打太多导致现在不是很能在静态情况下考虑使用更简单的 ST 表）。

言归正传：我们考虑何时能够连边，题意告诉我们，只有最大值和最小值分别分布在区间两端点处时才可以连边，所以说我们假设 $a_i=n$ 的位置 $i$ 不在整个序列的两端，那么我们发现 $i$ 这个位置把整个序列就好像一道天堑一样划成了两部分，两部分之间可以发现总是无法连边的，而从一部分到另一部分总要经过 $i$ 这个位置。

我们于是把 $i$ 这样必经的位置称为“枢纽点”。

我们再考察 $i$ 左右两边的部分，以左边为例，左边的最小值所在位置同样是一个“枢纽点”，它的两边无法连边，从一边到另一边必须经过“枢纽点”，而且，还有一件重要的事情是，这个最小值的“枢纽点”恰好（而且是一定）可以和 $n$ 的“枢纽点”连边。

所以最小值“枢纽点”的右半部分就不用再考虑了，显然走到它里面的节点会使答案更劣。

所以我们可以以此类推下去，从 $n$ 对应的的枢纽点出发，找其左半部分的最小值，作为新的“枢纽点”，连边（答案 +1 ），然后再在最小值对应的“枢纽点”左边找一个最大值……再找一个最小值……，如此往复循环下去，直到位置 1 作为最后一个要找的“枢纽点”被连边。

对于 $n$ 对应的的枢纽点的右半部分，处理方式同理。

```cpp
	int a[250010];
	int pos[250010];
	int mx[250010<<2];
	int mn[250010<<2];
	
	void pushup(int x){
		mx[x]=max(mx[x<<1],mx[x<<1|1]);
		mn[x]=min(mn[x<<1],mn[x<<1|1]);
	}
	
	void build(int x,int l,int r){
		if(l==r){
			mx[x]=mn[x]=a[l];
			return;
		}
		//mx[x]=0;mn[x]=0x3f3f3f3f;
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pushup(x);
	}
	
	pii query(int x,int l,int r,int tl,int tr){
		if(tl<=l&&r<=tr){
			return mp(mx[x],mn[x]);
		}
		int mid=(l+r)>>1;
		pii res=mp(0,0x3f3f3f3f);
		if(tl<=mid){
			pii tmp=query(x<<1,l,mid,tl,tr);
			res.first=max(res.first,tmp.first);
			res.second=min(res.second,tmp.second);
		}
		if(mid<tr){
			pii tmp=query(x<<1|1,mid+1,r,tl,tr);
			res.first=max(res.first,tmp.first);
			res.second=min(res.second,tmp.second);
		}
		return res;
	}
	
	int T;
	int n;
	
	void main(){
		cin>>T;
		while(T--){
			cin>>n;
			for(int i=1;i<=n;i++){
				cin>>a[i];
				pos[a[i]]=i;
			}
		
			int ans=0;
			build(1,1,n);
		
			int ps=pos[n]-1,fd=1;
			while(ps){
				ans++;
				pii tmp=query(1,1,n,1,ps);
				ps=(fd)?(pos[tmp.second]-1):(pos[tmp.first]-1);
				fd^=1;
			}
			ps=pos[n]+1,fd=1;
			while(ps<=n){
				ans++;
				pii tmp=query(1,1,n,ps,n);
				ps=(fd)?(pos[tmp.second]+1):(pos[tmp.first]+1);
				fd^=1;
			}
			cout<<ans<<endl;
		}
	}
```


---

## 作者：GalwayGirl (赞：2)

## 闲话
考场上心态不好，B 题 C 题 全看错题目，导致我没时间切 D 题，~~有时间也切不了。~~ 还剩了十分钟，我就打了个 bfs 暴力。

暴力程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
int t,n,a[N];
struct hh{
    int id,val,cnt;
};
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    queue<hh>q;
    q.push({1,a[1],0});
    while(!q.empty()){
        int now=q.front().id,val=q.front().val,min_=val,max_=val;
        int cnt=q.front().cnt;
        q.pop();
        if(now==n){
            printf("%d\n",cnt);
            return ;
        }
        for(int i=now+1;i<=n;i++){
            min_=min(min_,a[i]);
            max_=max(max_,a[i]);
            if(val==min_||val==max_){
                if(val==min_&&a[i]==max_)q.push({i,a[i],cnt+1});
                if(val==max_&&a[i]==min_)q.push({i,a[i],cnt+1});
            }
            else break;
        }
    }
}
int main(){
    scanf("%d",&t);
    while(t--)solve();
}
```
~~就过了样例，其它全 T 飞了。~~

## Solution
赛后看这题其实也不难，贪心地去思考，能跳多远就肯定跳多远，那么什么情况下它会跳不了呢？假设现在的点为最大值，那么当跳到后面区间的最小值就已经是最远距离了，接下来肯定又会跳到后面区间的最大值，循环往复，跳到终点为止。如果该点为最小值也是一样的道理。

这样，极值到终点的区间处理完了，那么起点到极值呢？我们可以与上面类比一下，把起点看成极值点，极值点看成终点，其实是一样的道理。所以我们只需找到全局极值点，然后往前和往后去遍历即可。

看其他题解都是用的 ST 表和线段树，我怕麻烦就记了个前缀后缀最大最小，~~感觉更麻烦了。~~

具体见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
int t,n,cnt,premin[N],premax[N],sufmin[N],sufmax[N];
int a[N],preminn[N],premaxn[N],sufminn[N],sufmaxn[N];
void pre(){
    for(int i=0;i<=n+1;i++)premin[i]=1e9,premax[i]=-1e9,sufmin[i]=1e9,sufmax[i]=-1e9;
    for(int i=1;i<=n;i++){
        if(a[i]>=premax[i-1])premax[i]=a[i],premaxn[i]=i;
        else premax[i]=premax[i-1],premaxn[i]=premaxn[i-1];
        if(a[i]<=premin[i-1])premin[i]=a[i],preminn[i]=i;
        else premin[i]=premin[i-1],preminn[i]=preminn[i-1];
    }    
    for(int i=n;i>=1;i--){
        if(a[i]>=sufmax[i+1])sufmax[i]=a[i],sufmaxn[i]=i;
        else sufmax[i]=sufmax[i+1],sufmaxn[i]=sufmaxn[i+1];
        if(a[i]<=sufmin[i+1])sufmin[i]=a[i],sufminn[i]=i;
        else sufmin[i]=sufmin[i+1],sufminn[i]=sufminn[i+1];
    }
}
void left(int now,int type){
    while(now!=1){
        cnt++;
        if(type)now=preminn[now-1];
        else now=premaxn[now-1];
        type^=1;
    }
}
void right(int now,int type){
     while(now!=n){
        cnt++;
        if(type)now=sufminn[now+1];
        else now=sufmaxn[now+1];
        type^=1;
    }   
}
void solve(){
    int min_=1e9;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    pre();
    right(premaxn[n],1);
    left(premaxn[n],1);
    min_=cnt;
    cnt=0;
    right(preminn[n],0);
    left(preminn[n],0);
    printf("%d\n",min(min_,cnt));
}
int main(){
    scanf("%d",&t);
    while(t--)solve();
}
```


---

## 作者：Sellaris (赞：2)

- 考虑全局最小和全局最大是一步通过。于是考虑把数组从全局最值处切开，从最前面到全局最值看成一个新的数组，然后发现这样一直递归处理就好了。于是维护前后缀最值，每次递归到最值就调另一个最值的位置。

- 感性理解：当划分为一个全局最值为两端的数组时只需要一步是最优的，于是向上递归；当划分为一个最值在一边一个最值在中间时最优的是两个最值在一边的合并起来的，再向上每个子问题发现不管最值的位置如何变化，我们从底层的一步向上合并，每次合并一定都是最优的。

- 严谨一点证明也不难：每次我们按最远的跳。假设当前为区间最大，往回跳到任意一个一个区间最小。那么以那个最小值的能跳的点都不超过那个跳回来的最大值的位置，因为我们跳过去的时候跳的是最远的。所以只要贪心一直跳就行。同理这也是为什么不跳到一个区间内的值再往后跳，即不跳最远的肯定不比跳最远的优，因为不跳最远的你还是不能直接跨过最远的点。

- 给出的是递归做法。也有贪心化的单调栈做法。这两种时间都是线性的。而直接套其他数据结构就没有那么优美了。


```cpp
///*****Sellaris*****///
//#pragma once
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
using namespace std;
//using namespace __gnu_pbds;
const int maxn=5e5+10;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
int a[maxn];
int n;
int pos[maxn];
int frontmx[maxn],frontmn[maxn];
int backmx[maxn],backmn[maxn]; 

inline int solve1(register int x){
    if(x==1)return 0;
    else return ( frontmx[x]==a[x] ? solve1(pos[frontmn[x]]) : solve1(pos[frontmx[x]]))+1 ;
}
inline int solve2(register int x){
    if(x==n)return 0;
    else return ( backmx[x]==a[x] ? solve2(pos[backmn[x]]) : solve2(pos[backmx[x]]))+1 ;
}

inline void solve(){
    n=read();
	for(int i=1;i<=n;i++) {
		a[i]=read();
		pos[a[i]]=i;//给定一个排列 
	}
	if(n==1) {puts("0");return;}
	else if(pos[n]*pos[1]==n && pos[1]+pos[n]==n+1) {puts("1");return;}
	
	frontmn[1]=frontmx[1]=a[1];
	
	for(int i=2;i<=n;i++) 
		frontmn[i]=min(a[i],frontmn[i-1]),
		frontmx[i]=max(a[i],frontmx[i-1]);
		
	backmn[n]=backmx[n]=a[n];
	
	for(int i=n-1;i>=1;i--)
		backmn[i]=min(a[i],backmn[i+1]),
		backmx[i]=max(a[i],backmx[i+1]);

	if(pos[n]>1 && pos[n]<n) printf("%lld\n",solve1(pos[n])+solve2(pos[n]));
	else if(pos[1]>1 && pos[1]<n) printf("%lld\n",solve1(pos[1])+solve2(pos[1]));
	return ;
}
signed main(){
    //std::ios::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t=read();
	while(t--){
		solve();
	}
    return 0;
}




```


---

## 作者：XFlypig (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1696D)

首先发现直接建图不现实，那么这种题要考我们的就是建边条件的性质。

一个直观想法是不会向前走，这个其他人的代码都有证明而且感性理解很简单，这里就略过了。

所以我们就是向后疯狂的冲就是了，很有贪心的味道。

但直接贪心最坏可能是 $O(n^2)$ 的，做法就是从一号点出发，向右枚举满足条件的最靠右的右端点，并直接跳到那里，它长[这样](https://www.luogu.com.cn/record/147959769)。

卡他的数据也挺好造，就是从一号点开始，进行 $+1, -2, + 3, -4\cdots$，这样相对关系就有了，再整体加偏移量使其满足一个排列就行了。

这里可以不疯狂的向右跳，用 DP 也是一样的，代码中注释的部分就是 DP 写法。

现在我们证明一下疯狂向右跳的贪心是正确的，~~要不是 A 了，鬼知道他是正确的~~。

不妨设 $a_i < a_j < a_k$，这样从 $i$ 既可以跳到 $j$ 也可以跳到 $k$，那么我们来看看下一步怎么跳，假设 $j$ 最远跳到 $l$，则有 $a_k < a_l$，$k$ 也可以跳到，而如果 $a_k > a_l$，$k$ 可能跳到，但 $j$ 不能跳到，所以疯狂的向右跳是正确的。

所以我们考虑预处理一下从 $i$ 出发能跳到的最靠右的右端点，这样贪心过程就是 $O(n)$ 了。

条件就是区间两个端点分别是最大值和最小值就可以建边，那我们不妨从后向前枚举左端点为最小值或最大值。以当前枚举的左端点 $i$ 为最小值为例，那么我们找到他右边第一个小于他的点 $j$，则 $i$ 最远就跳到 $k, i \le k < j, a_k = \max_{[i,j-1]}$，$k$ 就是 $i$ 到 $j - 1$ 的最大值的下标，这是一个经典的单调栈题目，找出每一个数右边第一个小于或大于他的数，于是我们用单调栈解决。

那区间极值呢，放到单调栈里一起维护就行，具体说，单调栈不变，其中每个元素改成 `pair`，另一个元素存的是从当前枚举的点一直到这个栈中元素的区间的极值，注意这个不能实时维护，但我们可以只维护栈顶，弹出时向新的栈顶更新即可，因为先进栈的一定是更靠后的元素。

最后疯狂的向右跳的时候，两种情况取个最大值即可，DP 写法注释在旁边了。

总复杂度 $O(n)$，放代码喽！

偷偷说一句，我没看官方题解，听说是 $O(n)$，如有雷同，纯属巧合，还有，代码里的快读是从%%%[大佬的代码](https://www.luogu.com.cn/record/126634116)里搞过来的。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 250010;

int n;
int w[N];
PII stk[N], mn[N], mx[N];

char buf[1<<21],*p1=buf,*p2=buf;
inline char Getc(){if(p1==p2){p2=(p1=buf)+fread(buf,1,1<<21,stdin);if(p1==p2) return EOF;}return *p1++;}
inline int read()
{
	static char ch;
	while(ch=Getc(),ch<'0'||ch>'9');
	int x=ch^'0';
	while(ch=Getc(),'0'<=ch&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');
	return x;
}

inline int Max(int a, int b)
{
    return w[a] > w[b] ? a : b;
}

inline int Min(int a, int b)
{
    return w[a] < w[b] ? a : b;
}

int main()
{
    int T;
    T = read();
    while (T -- )
    {
        n = read();
        for (int i = 1; i <= n; i ++ ) w[i] = read();
        
        int tt = 0;
        stk[ ++ tt] = {n + 1, n + 1};
        w[n + 1] = 0;
        for (int i = n; i; i -- )
        {
            while (w[stk[tt].y] > w[i])
                stk[tt - 1].x = Max(stk[tt - 1].x, stk[tt].x), tt -- ;
            mn[i] = stk[tt];
            stk[ ++ tt] = {i, i};
        }
        
        stk[tt = 1] = {n + 1, n + 1};
        w[n + 1] = n + 1;
        for (int i = n; i; i -- )
        {
            while (w[stk[tt].y] < w[i])
                stk[tt - 1].x = Min(stk[tt - 1].x, stk[tt].x), tt -- ;
            mx[i] = stk[tt];
            stk[ ++ tt] = {i, i};
        }
        
        int pos = 1, cnt = 0;
        while (pos < n) pos = max(mn[pos].x, mx[pos].x), cnt ++ ;
        printf("%d\n", cnt);
        
        // for (int i = 1; i <= n; i ++ ) dp[i] = 1e9;
        // dp[1] = 0;
        // for (int i = 1, t; i <= n; i ++ )
        // {
        //     t = mn[i].x;
        //     dp[t] = min(dp[t], dp[i] + 1);
        //     t = mx[i].x;
        //     dp[t] = min(dp[t], dp[i] + 1);
        // }
        // printf("%d\n", dp[n]);
    }
    
    return 0;
}
```

---

## 作者：Masna_Kimoyo (赞：0)

其实跟图没关系啊没关系

选完了之后最后就长成 $a_{b_i},a_{b_i-1},...,a_{b_k}$ 这种

我们的目标就是找到这些端点

## Solution

采取一个分治算法。每次找到一个区间的最大值和最小值的位置。

当然了为了方便操作，我们默认最小值在最大值左边，如果不是就交换一下

找到之后你会发现，在左端左边的那些点，是肯定没法向左端右边的点连边的，因为整个区间的最小值已经找到，右边没有点能做除了端点外的最小值了。左边同理。所以我们发现，这已经满足了分治的性质，左边右边中间互不影响，直接再拆成子区间往下分即可。

而中间那段，一定是对答案有贡献的。在此证明一下。

- 由于中间那段把三段都隔开了，也就是说，左部，右部和中部都无边相连。而产生答案的又是一堆相连的点，不存在断开的情况。所以唯一能维持不断开的此时就只有中间那段，中间那段必须取。（必要性）

- 这时又要考虑一个很简单的贪心，为什么中间那段取了一定是最优的？因为里面的点没法和左部右部的点连接，只能和内部的点连，连来连去还是只能把首尾连上，并花费了更大代价，这是不优的。所以只取首尾即可（充分性）

分治很好写，如果要查找一个区间的最值，有很多手段，我选了最容易的线段树。

其他的细节没什么好说的，记得分到左右相等区间直接 `return 0`，这是不符合题意的。要不然按照我的写法会一直递归，最后寄掉。

## code:

```cpp
#include<bits/stdc++.h>
#define printlf(x) print(x),putchar('\n')
#define printsp(x) print(x),putchar(' ')
using namespace std;
inline int read(){
    int x=0;
    bool w=0;
    char c=getchar();
    while(!isdigit(c))  w|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void print(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar('0'+x%10);
}
const int N=3e5+5,INF=INT_MAX;
int a[N],seq[N];
int maxx[N*3],minn[N*3];
int n;
#define ls(x) x<<1
#define rs(x) x<<1|1
inline void push_up(int p){
    maxx[p]=max(maxx[ls(p)],maxx[rs(p)]);
    minn[p]=min(minn[ls(p)],minn[rs(p)]);
}
inline void Build(int p,int l,int r){
    if(l==r){
        maxx[p]=a[l];
        minn[p]=a[l];
        return ;
    }
    int mid=l+r>>1;
    Build(ls(p),l,mid);
    Build(rs(p),mid+1,r);
    push_up(p);
}
inline int get_max(int p,int l,int r,int pl,int pr){
    if(l>=pl && r<=pr)  return maxx[p];
    int mid=l+r>>1,res=-INF;
    if(pl<=mid) res=max(res,get_max(ls(p),l,mid,pl,pr));
    if(pr>mid)  res=max(res,get_max(rs(p),mid+1,r,pl,pr));
    return res;
}
inline int get_min(int p,int l,int r,int pl,int pr){
    if(l>=pl && r<=pr)   return minn[p];
    int mid=l+r>>1,res=INF;
    if(pl<=mid) res=min(res,get_min(ls(p),l,mid,pl,pr));
    if(pr>mid)  res=min(res,get_min(rs(p),mid+1,r,pl,pr));
    return res;
}
inline int Search(int l,int r){
    //cout<<l<<' '<<r<<' '<<get_min(1,1,n,l,r)<<' '<<get_max(1,1,n,l,r)<<" lalalaal\n";
    if(l==r)    return 0;
    int pos1=seq[get_min(1,1,n,l,r)],pos2=seq[get_max(1,1,n,l,r)];
    if(pos1>pos2)   swap(pos1,pos2);
    if(pos1==l && pos2==r)  return 1;
    int res=1;
    res+=Search(l,pos1);
    res+=Search(pos2,r);
    return res;
}
inline int Solve(){
    n=read();
    for(register int i=1;i<=n;++i)  a[i]=read(),seq[a[i]]=i;
    Build(1,1,n);
    return Search(1,n);
}
signed main(){
    int T=read();
    while(T--){
        printlf(Solve());
    }
    return 0;
}

```

---

