# [SEERC 2020] Archeologists

## 题目描述

你在玩一个寻宝类游戏，一共有 $n$ 个格子，编号为 $1 \sim n$，你每在 $i$ 号格子上下挖一层便会获得 $p_i$ 的价值，其中你需要保证每个格子相邻的两个格子都与其下挖的深度的差值不超过 $1$（注意此时 $1$ 和 $n$ 号点最多只能挖一层），请最大化总价值。

## 说明/提示

样例一解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/jalyemdz.png)

## 样例 #1

### 输入

```
5
1 3 -4 2 1
```

### 输出

```
8```

## 样例 #2

### 输入

```
4
1 1 -2 3```

### 输出

```
5```

## 样例 #3

### 输入

```
5
-1 -3 0 -5 -4
```

### 输出

```
0```

# 题解

## 作者：xiezheyuan (赞：12)

## 思路

你发现如果要考虑每个点被挖了多少格，那么至少需要 $O(n^2)$ 的时间复杂度，难以通过本题。

我们转而考虑挖的深度的差分数组。按照题意，差分数组的每一项只可能是 $1,-1,0$。我们不妨将 $1$ 看成一个左括号，$-1$ 的前一个位置看成一个右括号，$0$ 要么是不打括号，要么是一个右括号和一个左括号。

那么这些括号必须匹配。因为假如括号不匹配，那么会出现以下两种情况：

- 左括号不匹配，则最后一个位置会出现不合法的情况。
- 右括号不匹配，则会出现一个位置挖了负数格的情况。

然后对 $a$ 求前缀和，就转换成了经典问题。参考 [CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D)。

但是这道题剩余部分虽然和 Buy Low Sell High 一样，但是思考起来更容易。我们发现可以打左括号的地方一定可以打右括号，要不然的话括号匹配就会出锅。所以我们维护一个堆，每次将合法的左括号丢到堆里面去，然后看这里打一个右括号是否更优即可。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2.5e5 + 5;
int n, ans, qzh[N], a[N];
priority_queue<int, vector<int>, greater<int> > pq;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) qzh[i] = qzh[i - 1] + a[i];
    for(int i=1;i<=n;i++){
        pq.push(qzh[i - 1]);
        if(qzh[i] - pq.top() > 0){
            ans += qzh[i] - pq.top();
            pq.pop();
            pq.push(qzh[i]);
        }
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：AC_Lover (赞：6)

考虑将原问题转化为区间覆盖问题。

我们将挖格子看作用若干个区间去覆盖这些格子。

下面定义的区间是没有与其他区间相接的，即不会同时有 $[l,k]$ 和 $[k+1,r]$ 存在，这两个区间会合并成 $[l,r]$。

我们将第 $i$ 个格子下挖的深度看成这个格子被多少个区间覆盖，于是我们考虑要满足什么条件下挖的深度才能满足要求。

我们发现，每个点只会作为区间的左端点至多 $1$ 次，作为区间的右端点至多 $1$ 次。

> 反证法：
> ![HH.png](https://s2.loli.net/2025/02/07/ornN1qUk8YS5Qzl.png)
> 假设一个点被作为左端点或右端点大于 $1$ 次，那么覆盖的次数的差就会大于 $1$。根据区间的定义，此时区间无法调平覆盖次数的差，于是就不满足条件，命题得证。

所以我们完成了转化，相当于要选出若干个区间，使得每个格子只会作为区间的左端点或右端点至多一次。

假设一个覆盖区间为 $[l,r]$，那么其贡献就是 $\sum_{i=l}^{r}p_i$。

相当于要使得选出的区间和最大化。

记 $sum$ 为 $p$ 的前缀和数组，那么一段区间的和就可以用 $sum_r-sum_l$ 的形式表示，考虑反悔贪心，每次将选为区间左端点的 $sum$ 值放入小根堆中，对于 $sum_i$，从小根堆中找出最小的 $sum$，判断与之匹配是否更优，反悔贪心即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N=250010;
typedef long long ll;
int n;
int w[N];
ll sum[N];
priority_queue<ll,vector<ll>,greater<ll> > q;

int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> w[i];
		sum[i]=sum[i-1]+w[i];
	}
	
	ll res=0;
	q.push(0); //记得加入sum[0]
	for (int i=1;i<=n;i++)
	{
		if (!q.empty() && sum[i]-q.top()>0)
		{
			res+=sum[i]-q.top();
			q.pop();
			q.push(sum[i]); //反悔 
		}
		q.push(sum[i]);
	}
	cout << res << "\n";
		
	return 0;
}
```

---

## 作者：Reunite (赞：2)

先列出朴素 dp 转移，设 $f_{i,j}$ 为到了 $i$ 列要挖 $j$ 个，则有：

$$f_{i,j}=\max(f_{i-1,j-1},f_{i-1,j},f_{i-1,j+1})+a_i\times i$$

我们发现这个 dp 对于任意 $i$，$j$ 这一维都是可以带平台的单峰的，简单归纳证明一下：对于 $f_{1,0},f_{1,1}$，要么是平台，要么是下降，要么是上升，是单峰。对于 $\forall_{i>1}$，峰顶左边的取 $\max$ 都会往峰顶方向取一个，峰顶右边的亦然，而峰顶则会被左右三个位置取到 $\max$。此时仍然是单峰的。那么我们拉出它的差分数组，一定是一段前缀 $\ge 0$，剩下的后缀 $<0$，显然叠加上一个一次函数后，相当于对差分数组整体加，仍然满足单峰性质。

那就做完了，维护一个平衡树动态维护差分，每次就删掉第一个元素，裂出峰顶，在峰顶右边插入两个差分为 $0$ 的元素，最后再把非第一个元素的差分整体加上 $a_i$ 即可。注意要讨论第一个点就是峰顶的情况，此时只需要在峰顶右边插入一个 $0$。分析模拟一下会发现还是比较简单的。

复杂度 $O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>
#define int long long
using namespace std;

int n,tot,root;
int a[500005];
int lc[500005];
int rc[500005];
int vl[500005];
int tg[500005];
int sz[500005];
int wei[500005];
mt19937 rnd(time(NULL));

inline void in(int &n){
	n=0;
	char c=getchar();bool ok=c=='-';
	while(c<'0' || c>'9') c=getchar(),ok|=c=='-';
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	n=ok?-n:n;
	return ;
}

inline int newnode(int x){
	tot++;
	sz[tot]=1;
	wei[tot]=rnd();
	vl[tot]=x;
	return tot;
}

inline void pushup(int u){sz[u]=sz[lc[u]]+sz[rc[u]]+1;return ;}

inline void down(int u,int x){tg[u]+=x;vl[u]+=x;return ;}

inline void pushdown(int u){
	if(!tg[u]) return ;
	if(lc[u]) down(lc[u],tg[u]);
	if(rc[u]) down(rc[u],tg[u]);
	tg[u]=0;
	return ;
}

inline int merge(int p,int q){
	if(!p||!q) return p|q;
	if(wei[p]<wei[q]){
		pushdown(p);
		rc[p]=merge(rc[p],q);
		pushup(p);
		return p;
	}
	else{
		pushdown(q);
		lc[q]=merge(p,lc[q]);
		pushup(q);
		return q;
	}
}

inline void split(int u,int &l,int &r){
	if(!u) l=r=0;
	else{
		pushdown(u);
		if(vl[u]>=0) l=u,split(rc[u],rc[u],r);
		else r=u,split(lc[u],l,lc[u]);
		pushup(u);
	}
	return ;
}

inline void split2(int u,int k,int &l,int &r){
	if(!u) l=r=0;
	else{
		pushdown(u);
		if(sz[lc[u]]<k) l=u,split2(rc[u],k-sz[lc[u]]-1,rc[u],r);
		else r=u,split2(lc[u],k,l,lc[u]);
		pushup(u);
	}
	return ;
}

signed main(){
	in(n);
	for(int i=1;i<=n;i++) in(a[i]);
	root=merge(newnode(0),newnode(a[1]));
	for(int i=2;i<=n;i++){
		int x,y,z;
		split(root,x,y);
		if(sz[x]<=1){
			y=merge(newnode(0),y);
			down(y,a[i]);
			root=merge(x,y);
			continue;
		}
		root=merge(x,y);
		split2(root,1,x,y);
		root=y;
		z=vl[x];
		split2(root,1,x,y);
		down(x,z);
		root=merge(x,y);
		split(root,x,y);
		root=merge(merge(x,newnode(0)),merge(newnode(0),y));
		split2(root,1,x,y);
		down(y,a[i]);
		root=merge(x,y);
	}
	int x,y;
	split2(root,2,x,y);
	split2(x,1,x,y);
	printf("%lld\n",max(vl[x],vl[x]+vl[y]));

	return 0;
}
```

---

## 作者：oMin0 (赞：2)

## 分析

提供一个暴力做法。

考虑直接进行 DP，设 $f_{i,j}$ 表示考虑前缀 $i$，$i$ 号格子挖 $j$ 层的最大价值，那么有简单转移式 $f_{i,j}=\max\{f_{i-1,j-1},f_{i-1,j},f_{i-1,j+1}\}+p_i\times j$。

这样做显然是 $O(n^2)$ 的，但我们可以打表猜到 DP 数据关于 $j$ 是单峰的，那么前面的 $\max$ 就在 $j\in [0,pos-1],[pos,pos],[pos,i]$ 时分别取到 $j+1,j,j-1$。——事实上也很好归纳证明它是凸的，因为凸函数在峰顶拆成两段并加入平台后还是凸的，并且凸函数叠加一条直线也还是凸的，而这两点是转移的实质。

于是用平衡树维护其差分数组。每次从 $i\rightarrow i+1$ 转移时先找出最大值位置 $pos$，然后分裂成 $[0,pos],[pos+1,i]$ 两部分（你需要把 $[0,0]$ 删去），在中间插入两个 $0$，再把 $p_i$ 的贡献加上去即可。这些维护是简单的。

于是结束了，时间复杂度 $O(n\log n)$。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define ll long long
#define ull unsigned long long
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));

int n,p[250005];

struct fhq
{
	int sz,rd,ls,rs,num,tagadd,sum;
}tree[500005];
int rt,cntd;

#define sz(x) tree[x].sz
#define rd(x) tree[x].rd
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define n(x) tree[x].num
#define tg(x) tree[x].tagadd
#define s(x) tree[x].sum

int getn(int k) {cntd++; sz(cntd)=1,rd(cntd)=rnd(),n(cntd)=s(cntd)=k; return cntd;}
void push_up(int p) {sz(p)=sz(ls(p))+sz(rs(p))+1; s(p)=s(ls(p))+n(p)+s(rs(p));}
void cza(int k,int p) {n(p)+=k; tg(p)+=k; s(p)+=sz(p)*k;}
void push_down(int p) {if(tg(p)) cza(tg(p),ls(p)),cza(tg(p),rs(p)),tg(p)=0;}

void split(int k,int p,int &x,int &y)
{
	if(!p) return x=y=0,void(); push_down(p);
	if(sz(ls(p))>=k) split(k,ls(p),x,ls(y=p));
	else split(k-sz(ls(p))-1,rs(p),rs(x=p),y); push_up(p);
}
int merge(int p,int q)
{
	if(!p||!q) return p+q; push_down(p); push_down(q);
	if(rd(p)<rd(q)) return rs(p)=merge(rs(p),q),push_up(p),p;
	else return ls(q)=merge(p,ls(q)),push_up(q),q;
}
int askwz()
{
	int p=rt,na=0;
	while(p)
	{
		push_down(p);
		if(n(p)<0) p=ls(p);
		else na+=sz(ls(p))+1,p=rs(p);
	}
	return na;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i]; rt=merge(rt,getn(0));
	for(int i=1;i<=n;i++)
	{
		int wz=max(0ll,askwz()-1),rtl=0,rtr=0,rtll=0,rtlm=0,rtlr=0;
	//	cout<<i<<" "<<wz<<" "<<sz(rt)<<" "<<n(rt)<<endl;
		split(wz+1,rt,rtl,rtr); 
		int lmx=s(rtl);
	//	cout<<i<<" "<<wz<<" "<<s(rtl)<<endl;
		if(wz==0)
		{
			rt=merge(getn(0),rtr); cza(p[i],rt); rt=merge(rtl,rt);
		}
		else
		{
			split(1,rtl,rtll,rtlr); split(1,rtlr,rtlm,rtlr); cza(n(rtll),rtlm);
			rtlr=merge(rtlr,getn(0)); rtlr=merge(rtlr,getn(0));
			rt=merge(rtlr,rtr); cza(p[i],rt); rt=merge(rtlm,rt);
		}
	}
	int rtl=0,rtm=0,rtr=0;
	split(1,rt,rtl,rtr); split(1,rtr,rtm,rtr);
	cout<<max(n(rtl),n(rtl)+n(rtm))<<endl;
}//
```

---

