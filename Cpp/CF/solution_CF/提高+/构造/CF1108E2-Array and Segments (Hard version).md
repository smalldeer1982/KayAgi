# Array and Segments (Hard version)

## 题目描述

给定你一个长度为 $n$ 的数组 $a$ ，再给定你 $m$ 对数字 $[l_i,r_i]$ 。你可以选择其中的几对数字作为两个端点，再将数组 $a$ 中的两个端点内的数字全部减一。（例如现有一对 $[l_i,r_i]$ 为 $[1,3]$ ，而数组 $a$ 为 ```1 2 3 4 5``` ，若使用这对 $[l_i,r_i]$ 数组就会变成 ``` 0 1 2 4 5 ```）

现在请你求出怎样使得数组 $a$ 中的最大值减去最小值最大。

## 样例 #1

### 输入

```
5 4
2 -2 3 1 2
1 3
4 5
2 5
1 3
```

### 输出

```
6
2
4 1 
```

## 样例 #2

### 输入

```
5 4
2 -2 3 1 4
3 5
3 4
2 4
2 5
```

### 输出

```
7
2
3 2 
```

## 样例 #3

### 输入

```
1 0
1000000
```

### 输出

```
0
0

```

# 题解

## 作者：whiteqwq (赞：3)

[CF1108E1 Array and Segments (Easy version)](https://www.luogu.com.cn/problem/CF1108E1)&[CF1108E2 Array and Segments (Hard version)](https://www.luogu.com.cn/problem/CF1108E2)解题报告:

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1766551)

## 题意
- 给定一个长度为$n$的序列$a$,你可以进行$m$次操作中的任意一些操作,每个操作为$[l,r]$,表示让区间$[l,r]$减一,求使得序列极差最大的操作方案.
- Easy Version:$1\leqslant n\leqslant 300,0\leqslant m\leqslant 300$.
- Hard Version:$1\leqslant n\leqslant 10^5,0\leqslant m\leqslant 300$.

## 分析
首先,因为极差=最大值-最小值,而一个同时包含最大值和最小值的区间如果不改变最大值和最小值的位置,是不会对极差造成影响的,因此我们有一个初步的想法:

我们枚举最大值位置,然后进行所有不包含最大值位置的操作,并得到最小值,最后将所有的极差取$\max$.

这样做的复杂度是$O(nq\log n)$的,可以通过Easy Version.

优化也很简单,我们发现上述算法枚举的操作区间或起来都不是全集(要给最大值留位置),很容易想到枚举没有进行的操作,因为操作区间或不是全集,因此没有进行的操作区间与起来不为空集,这样至少会有一个位置没有操作过,可以成为最大值.

我们先加入所有区间,然后枚举每一个位置,先撤销以这个位置开始的操作,求得一个极差,然后再重新进行以这个位置结束的操作,这样我们就能保证求极差时撤销的区间都包含当前位置.

只需要写一个区间加,区间$\min/\max$的线段树就好了.

时间复杂度:$O(n+m\log n)$,可以通过Hard Version.

## 代码
```
#include<stdio.h>
#include<vector>
#define inf 1000000000
using namespace std;
const int maxn=100005,maxk=maxn<<2;
int n,m,ans,pos,cnt;
int a[maxn],lc[maxk],rc[maxk],maxx[maxk],minn[maxk],lazy[maxk],xx[maxn],yy[maxn];
vector<int>l[maxn],r[maxn];
inline void pushup(int now){
	maxx[now]=max(maxx[lc[now]],maxx[rc[now]]);
	minn[now]=min(minn[lc[now]],minn[rc[now]]);
}
inline void getlazy(int now,int v){
	maxx[now]+=v,minn[now]+=v,lazy[now]+=v;
}
inline void pushdown(int now){
	if(lazy[now]==0)
		return ;
	getlazy(lc[now],lazy[now]),getlazy(rc[now],lazy[now]);
	lazy[now]=0;
}
void build(int l,int r,int now){
	if(l==r){
		maxx[now]=minn[now]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	lc[now]=now<<1,rc[now]=now<<1|1;
	build(l,mid,lc[now]),build(mid+1,r,rc[now]);
	pushup(now);
}
void update(int l,int r,int now,int L,int R,int v){
	if(L<=l&&r<=R){
		getlazy(now,v);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(now);
	if(L<=mid)
		update(l,mid,lc[now],L,R,v);
	if(mid<R)
		update(mid+1,r,rc[now],L,R,v);
	pushup(now);
}
int main(){
	maxx[0]=-inf,minn[0]=inf;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		xx[i]=x,yy[i]=y;
		l[x].push_back(y),r[y].push_back(x);
		update(1,n,1,x,y,-1);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<l[i].size();j++)
			update(1,n,1,i,l[i][j],1);
		if(maxx[1]-minn[1]>ans)
			ans=maxx[1]-minn[1],pos=i;
		for(int j=0;j<r[i].size();j++)
			update(1,n,1,r[i][j],i,-1);
	}
	printf("%d\n",ans);
	for(int i=1;i<=m;i++)
		if(xx[i]>pos||yy[i]<pos)
			cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=m;i++)
		if(xx[i]>pos||yy[i]<pos)
			printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：KυρωVixen (赞：1)

# CF1108E Easy & Hard Ver. 题解

## 题意：
给你一个长 $n$ 的序列 $a$ 和 $m$ 个区间，你可以选择若干个区间，对于每个区间令其中的数都减一，最大化极差（最大值和最小值的差）并构造任意一个最优方案。

对于困难版 $1\le n\le 10^5,1\le m\le 300$，对于简单版还有 $1\le n\le 300$。

## 解法：

### 暴力：

对于这种求极差的问题，有一个很自然的思路就是先考虑某个操作分别对最大值和最小值的贡献。

发现直接算出来任意一个操作对答案的影响是不可能的，于是我们再考虑钦定一个最值，在这题里钦定最大最小值皆可，我们只考虑钦定最大值的情况，钦定最小值的情况留给读者思考。

假设我们已经钦定了 $a_i$ 作为计算答案（用 $ans$ 表示）时的最大值，那么对于每一个不包含 $i$ 的区间，选取它都可能使最小值更小，同时不改变最大值，从而增大 $ans$，我们就先贪心地选取所有这样的区间。

对于任意包含 $a_i$ 的区间，选取它对 $ans$ 的贡献分两种情况：

1. 这个区间可以使目前的最小值减一，从而使 $ans\gets ans+1$。
2. 这个区间不可以使目前的最小值减一。

除此之外，因为这个区间还包含了 $a_i$ 这个最大值，所以会在一开始令 $ans\gets ans-1$，综合来看选取它一定不优。

那么我们的贪心策略就是：不选包含 $a_i$ 的区间，同时选取其他所有区间。

所以我们就挨个钦定每一个 $a_i$ 为最大值然后计算答案比较大小即可，同时这个贪心策略也给出了构造方案，时间复杂度 $O(n^2m)$。

### 优化：

以上解法时间复杂度过高，无法通过困难版。

可以发现对于每个 $i$ 我们的程序遍历所有的区间进行一次次区间加减，十分缓慢。

对于 $i\gets i+1$ 的情况，需要改变是否选择的区间只有以 $i$ 为右端点的区间（再次选择）和以 $i+1$ 为左端点的区间（暂时取消选择），我们事先存下这样的区间，只修改他们的贡献即可。

对于 $i=0$ 的情况，没有区间包含 $0$，所以一开始要假定所有区间都被选了。 

每个区间只会更新两次，一开始还要全部更新一次，也就是说我们只会更新 $3m$ 次区间的选择情况，时间复杂度变成了 $O(nm)$。

还可以使用各种数据结构进一步让速度变快，比如作者的代码使用了线段树，时间复杂度为 $O(n+m\log n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define fi first
#define sc second
using namespace std;
using pii=pair<int,int>;
const int N=1e5+5;
int n,m,ans,dot,a[N];
pii b[N];
vector<pii>vec[N];
#define lf p*2
#define rt p*2+1
struct seg{
    int mx,mn,tg;
}t[N*4];
void pushup(int p){
    t[p].mx=max(t[lf].mx,t[rt].mx);
    t[p].mn=min(t[lf].mn,t[rt].mn);
}
void mtag(int p,int x){
    t[p].mx+=x; t[p].mn+=x; t[p].tg+=x;
}
void pushdown(int p){
    if(t[p].tg==0) return;
    mtag(lf,t[p].tg); mtag(rt,t[p].tg);
    t[p].tg=0;
}
void change(int p,int l,int r,int ql,int qr,int v){
    if(ql<=l&&r<=qr) {mtag(p,v); return;}
    pushdown(p); int mid=(l+r)/2;
    if(ql<=mid) change(lf,l,mid,ql,qr,v);
    if(qr>mid) change(rt,mid+1,r,ql,qr,v);
    pushup(p);
}
void build(int p,int l,int r){
    if(l==r){
        t[p].mn=t[p].mx=a[l]; return;
    }
    int mid=(l+r)/2;
    build(lf,l,mid); build(rt,mid+1,r);
    pushup(p);
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    rep(i,1,n) cin>>a[i];
    build(1,1,n);
    rep(i,1,m){
        pii x; cin>>x.fi>>x.sc; b[i]=x;
        change(1,1,n,x.fi,x.sc,-1);
        vec[x.fi].push_back(x);
        vec[x.sc+1].push_back(x);
    }
    rep(i,1,n){
        for(auto p:vec[i]){
            if(p.fi==i) change(1,1,n,p.fi,p.sc,1);
            if(p.sc+1==i) change(1,1,n,p.fi,p.sc,-1);
        }
        if(t[1].mx-t[1].mn>ans){
            ans=t[1].mx-t[1].mn; dot=i;
        }
    }
    cout<<ans<<endl;
    vector<int>tmp;
    rep(i,1,m) if(!(b[i].fi<=dot&&dot<=b[i].sc)) tmp.push_back(i);
    cout<<tmp.size()<<endl;
    for(int x:tmp) cout<<x<<" "; cout<<endl;
}
```

**Thank you for watching!**

---

## 作者：_edge_ (赞：1)

提供一种较为简单的 $O(nm)$ 的做法。

首先，把所有区间的端点以及他加一全都离散化下来。

然后会发现每次操作和具体数值无关了，只和两个点之间的最小值有关，我们可以通过预处理处理出两个端点的之间的最小值。

接下来需要用到一个结论，假设我们确定了一个点作为最大值，那么他所在的区间都是不能被选中的。

很容易证明，如果选择了的话，最多只会给最小值 $-1$，但是最大值是一定会 $-1$ 的，因此不做才是比较好的想法。

然后我们枚举一个点作为最大值，对其他不包含他的区间都进行操作，这样操作完成之后我们只需要找出最小值即可。

很容易通过差分来做，但是直接做的复杂度是 $O(n^2+nm)$ 的，我们把端点离散化了之后可以用他们之间的最小值来更新答案，因为其他的值比他大一定不会产生任何贡献。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define pb push_back
using namespace std;
const int INF=1e5+5;
const int INFN=305;
struct _node_data{
	int l,r;
}aa[INFN];
int n,m,a[INF],bb[INF],L[INF],cnt[INF],ff[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	cnt[++cnt[0]]=1;cnt[++cnt[0]]=n+1;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=m;i++) {
		cin>>aa[i].l>>aa[i].r;
		cnt[++cnt[0]]=aa[i].l;
		cnt[++cnt[0]]=aa[i].r+1;
	}
	sort(cnt+1,cnt+1+cnt[0]);
	int res=unique(cnt+1,cnt+1+cnt[0])-cnt-1;
	cnt[0]=res;
	for (int i=1;i<=cnt[0];i++) L[cnt[i]]=i;
	for (int i=2;i<=cnt[0];i++) {
		bb[i]=1e9;
		for (int j=cnt[i-1];j<cnt[i];j++)
			bb[i]=min(bb[i],a[j]);
	}
	vector <int> ans;
	res=0;int res1=0;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if (aa[j].l<=i && i<=aa[j].r) continue;
			else ff[L[aa[j].l]]--,ff[L[aa[j].r+1]]++;
		}
		for (int j=1;j<=cnt[0];j++) ff[j]+=ff[j-1];
		int Ans=1e9;
		for (int j=1;j<cnt[0];j++) {
			Ans=min(Ans,bb[j+1]+ff[j]);
		}
//		cout<<a[i]<<" "<<Ans<<" "<<ff[2]<<" "<<L[3]<<" "<<ff[1]<<" airejiejr\n";
		
		for (int j=0;j<=cnt[0]+1;j++) ff[j]=0;
		if (res<a[i]-Ans) res=a[i]-Ans,res1=i;
	}
	cout<<res<<"\n";
	for (int j=1;j<=m;j++) {
		if (aa[j].l<=res1 && res1<=aa[j].r) continue;
		else ans.pb(j);
	}
	cout<<ans.size()<<"\n";
	int len=ans.size();
	for (int k=0;k<len;k++)
		cout<<ans[k]<<" ";
	cout<<"\n";
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：1)

这是一道不错的暴力题。

------------

给你一个长度为 $ n $ 的数组 $ a $ ，和 $ m $ 个区间修改操作 $ l_i $ , $ r_i $ （ $ 1 \leq i \leq m $ ， $ l_i \leq r_i $ ）。

每个区间修改操作可以让其覆盖的区间减去 $ 1 $ 。

让你选择一些区间操作，使得全部操作完后的区间最大值减最小值最大。

------------

观察数据范围发现 $ 1 \leq m \leq 300 $ ， $ O(m^3) $ 都可以过。

这 $ m $ 个区间修改操作最多把区间分成 $ 2 m $ 个块，使得一个操作覆盖一个或多个连续的块。

枚举最大值和最小值出现在哪（两）个块中，再贪心得选择只包含最小值所在块的操作即可。

------------

代码如下 （~~非常的短~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
const int inf=1e6;
int a[202020];//原数组
int c[202020];//为了寻找每个块
int bl[303],br[303];//操作
int dl[606],dr[606];//每个块的左右端点
int dmax[606],dmin[606];//每个块的最大最小值
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(register int i=1;i<=m;++i){
        scanf("%d %d",&bl[i],&br[i]);
        c[bl[i]-1]=c[br[i]]=1;
    }
    s=0;
    l=1;
    while(l<=n){
        dl[++s]=l;
        while(!c[l] && l<n)++l;
        dr[s]=l++;
    }
    for(register int i=1;i<=s;++i){
        dmax[i]=-inf;
        dmin[i]=inf;
        for(register int j=dl[i];j<=dr[i];++j){
            if(dmax[i]<a[j])dmax[i]=a[j];
            if(a[j]<dmin[i])dmin[i]=a[j];
        }
    }
    int ans=-1,x,y,z;
    for(register int i=1;i<=s;++i){
        for(register int j=1;j<=s;++j){
            l=0;
            for(register int k=1;k<=m;++k)if((bl[k]<=dl[i] && dr[i]<=br[k]) && !(bl[k]<=dl[j] && dr[j]<=br[k]))++l;
            if(ans<dmax[j]-dmin[i]+l)ans=dmax[j]-dmin[i]+l,x=i,y=j,z=l;
        }
    }
    printf("%d\n%d\n",ans,z);
    for(register int k=1;k<=m;++k){
        if((bl[k]<=dl[x] && dr[x]<=br[k]) && !(bl[k]<=dl[y] && dl[y]<=br[k])){
            printf("%d ",k);
        }
    }
    putchar('\n');
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

先思考暴力（E1），我们可以先枚举一个最终序列的最大值可能在的位置，然后贪心地把所有不含该位置的线段全部选上，这样一定不劣（证明不难），复杂度 $O(nm \log n)$。

然后我们发现在最大值位置变化的过程中，有很大一部分的线段被重复修改，导致复杂度增加，所以可以减少一点。当最大值位置被定为 $p$ 时，$r<p$ 与 $l>p$ 的线段将被选上；最大值位置修改至 $p+1$ 时，$r<p+1$ 与 $l>p+1$ 的线段将被选上。所以发生变化的线段只有 $r=p$ 和 $l=p+1$ 的线段（前者原本不选后来选，后者原本选后来不选），于是在枚举最大值位置之前就先把所有线段选上，再按照上述括号内的方法进行修改即可（使用线段树）。复杂度 $O(n+m\log m)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],mx[N<<2],mn[N<<2],b[N<<2],n;
struct itv
{
	int l,r,id;
}p[310],pl[310];
void upd(int l,int r,int c,int s=1,int t=n,int p=1)
{
	if(l<=s&&t<=r)
	{
		mx[p]+=c;
		mn[p]+=c;
		b[p]+=c;
		return;
	}
	int m=s+t>>1;
	if(b[p])
	{
		b[p<<1]+=b[p];
		b[p<<1|1]+=b[p];
		mx[p<<1]+=b[p];
		mx[p<<1|1]+=b[p];
		mn[p<<1]+=b[p];
		mn[p<<1|1]+=b[p];
		b[p]=0;
	}
	if(l<=m) upd(l,r,c,s,m,p<<1);
	if(r>m) upd(l,r,c,m+1,t,p<<1|1);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
int main()
{
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],upd(i,i,a[i]);
	for(int i=1;i<=m;i++) cin>>p[i].l>>p[i].r,upd(p[i].l,p[i].r,-1),p[i].id=i,pl[i]=p[i];
	sort(p+1,p+m+1,[](itv x,itv y){return (x.r!=y.r?(x.r<y.r):(x.l<y.l));});
	sort(pl+1,pl+m+1,[](itv x,itv y){return (x.l!=y.l?(x.l<y.l):(x.r<y.r));});
	int hd=1,tl=1;
	int ans=0,mxid=0;
	for(int i=1;i<=n;i++)
	{
		while(hd<=m&&p[hd].r<i)
		{
			upd(p[hd].l,p[hd].r,-1);
			hd++;
		}
		while(tl<=m&&pl[tl].l<=i)
		{
			upd(pl[tl].l,pl[tl].r,1);
			tl++;
		}
		if(mx[1]-mn[1]>ans) mxid=i;
		ans=max(ans,mx[1]-mn[1]);
	}
	cout<<ans<<'\n';
	vector<int> opt;
	for(int i=1;i<=m;i++) if(p[i].l>mxid||p[i].r<mxid) opt.push_back(p[i].id);
	cout<<opt.size()<<'\n';
	for(auto i:opt) cout<<i<<' ';
}

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1108E1（luogu）](https://www.luogu.com.cn/problem/CF1108E1)

[CF1108E2（luogu）](https://www.luogu.com.cn/problem/CF1108E2)

[CF1108E1（codeforces）](https://codeforces.com/problemset/problem/1108/E1)

[CF1108E2（codeforces）](https://codeforces.com/problemset/problem/1108/E2)


# 解题思路

这篇题解分 E1，E2 两个部分来讲。

## E1 sol：

我们发现可以暴力枚举最后经过所有操作之后的最大值，那么显然的，我们将不会做任何经过这个位置的操作，会做不经过这个区间的所有操作。

直接暴力进行操作即可。

时间复杂度 $O(n^2 + nm)$。

## E2 sol：

发现这个暴力的过程可以使用区间加，区间最大值，区间最小值的线段树来维护，此时时间复杂度变为 $O(nm \log n)$，并不能通过此题，那么此时，我们可以再打一个标记表示当前树内是否加过这个区间，由于区间是连续的一段，并且我们枚举的最大值也是连续的一段，因此有一个性质，那就是每个区间至多被操作过两次，此时时间复杂度变为 $O(n + m \log n)$，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll int
#define pb push_back
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define mid ((l+r)>>1)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
/*
0 -4 1 1 2
*/
ll n,m;
ll id;
ll maxn;
ll a[100010],b[100010],c[100010];
ll l[100010],r[100010];
ll vis[510];
struct node{
    ll l,r,minn,maxn,tag;
}tree[400010];
struct nide{
	ll x,id;
}d[100010];
bool cmp(nide x,nide y){
	return x.x<y.x;
}
void pushup(ll x){
    tree[x].minn=min(tree[x*2].minn,tree[x*2+1].minn);
    tree[x].maxn=max(tree[x*2].maxn,tree[x*2+1].maxn);
}
void pushdown(ll x)
{
    tree[x*2].minn+=tree[x].tag;
    tree[x*2+1].minn+=tree[x].tag;
    tree[x*2].tag+=tree[x].tag;
    tree[x*2+1].tag+=tree[x].tag;
    tree[x*2].maxn+=tree[x].tag;
    tree[x*2+1].maxn+=tree[x].tag;
    tree[x].tag=0;
}
void build(ll x,ll l,ll r)
{
    tree[x].l=l,tree[x].r=r;
    if(l==r)
    {
        tree[x].minn=a[l];
        tree[x].maxn=a[l];
        return ;
    }
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void add(ll x,ll l,ll r,ll y)
{
    if(l<=tree[x].l && tree[x].r<=r)
    {
        tree[x].minn+=y;
        tree[x].maxn+=y;
        tree[x].tag+=y;
        return ;
    }
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2;
    if(l<=Mid)
        add(x*2,l,r,y);
    if(Mid<r)
        add(x*2+1,l,r,y);
    pushup(x);
}
ll querymin(ll x,ll l,ll r)
{
    if(l<=tree[x].l && tree[x].r<=r)
        return tree[x].minn;
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2,ans=1e9;
    if(l<=Mid)
        Min(ans,querymin(x*2,l,r));
    if(Mid<r)
        Min(ans,querymin(x*2+1,l,r));
    return ans;
}
ll querymax(ll x,ll l,ll r)
{
    if(l<=tree[x].l && tree[x].r<=r)
        return tree[x].maxn;
    pushdown(x);
    ll Mid=(tree[x].l+tree[x].r)/2,ans=-1e9;
    if(l<=Mid)
        Max(ans,querymax(x*2,l,r));
    if(Mid<r)
        Max(ans,querymax(x*2+1,l,r));
    return ans;
}
ll check(ll x)//x最终为最大值 
{
//	forl(i,0,n+2)
//		c[i]=0;
	forl(i,1,m)
	{
		if(l[i]>x || r[i]<x)
		{
			if(!vis[i])
				add(1,l[i],r[i],-1),vis[i]=1;
		}
		else
		{
			if(vis[i])
				add(1,l[i],r[i],1),vis[i]=0;
		}
	}
			//c[l[i]]--,c[r[i]+1]++;
//	forl(i,1,n)
//		c[i]+=c[i-1];
	ll maxn=-1e9,minn=1e9;
	maxn=querymax(1,1,n),minn=querymin(1,1,n);
//	forl(i,1,n)
//		cout<<querymax(1,i,i)<<' ';
//	cout<<endl;
//	forl(i,1,m)
//		if(l[i]>x || r[i]<x)
//			add(1,l[i],r[i],1);
///	forl(i,1,n)
//		Max(maxn,c[i]+a[i]),
//		Min(minn,c[i]+a[i]);
//		cout<<a[i]+c[i]<<' ';
//	cout<<endl;
//	cout<<"<"<<minn<<' '<<maxn<<endl;
	return maxn-minn;
}
void check2(ll x)//x最终为最大值 
{
	vector<ll>ans;
	forl(i,0,n+2)
		c[i]=0;
	forl(i,1,m)
		if(l[i]>x || r[i]<x)
			ans.pb(i);
	cout<<ans.size()<<endl;
	for(auto i:ans)
		cout<<i<<' ';
//		{
//			cout<<
//		}
//			c[l[i]]--,c[r[i]+1]++;
//	forl(i,1,n)
//		c[i]+=c[i-1];
//	ll maxn=-1e18,minn=1e18;
///	forl(i,1,n)
//		Max(maxn,c[i]+a[i]),
//		Min(minn,c[i]+a[i]);
//		cout<<a[i]+c[i]<<' ';
//	cout<<endl;
//	cout<<minn<<' '<<maxn<<endl;
//	return maxn-minn;
}
void solve()
{
	_clear();
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i];//,d[i].x=a[i],d[i].id=i;
	build(1,1,n);
	forl(i,1,m)
		cin>>l[i]>>r[i];
	maxn=-1e9;
//	check(5);
//	sort(d+1,d+1+n,cmp);
	forl(i,1,n)
		if(Max(maxn,check(i)))
			id=i;
/*	forr(i,n,max(5001,n-5000))
		if(Max(maxn,check(i)))
			id=i;	*/
	cout<<maxn<<endl;
	check2(id);
	
}
int main()
{
//	freopen("tst.txt","r",stdin);
//	freopen("sans.txt","w",stdout);
	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：二叉苹果树 (赞：0)

依次枚举每个点 $i$ 作为最大值，然后操作所有不包含 $i$ 的区间，统计极差。时间复杂度 $\mathcal{O} \left(mn\log n\right)$，可以轻松通过 Easy Version。

区间修改和最值的维护使用线段树即可。

Hard Version 题目中的 $n$ 很大，导致 $\mathcal{O} \left(mn\log n\right)$ 无法接受。显然有很多的区间被重复地来回修改，我们考虑每个区间进行尽可能少的修改。很多位置 $i$ 的操作区间是重合的，我们在某个区间用完以后再将其进行操作即可。

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define lc (x * 2)
#define rc (x * 2 + 1)

int a[maxn], lzy[maxn << 2];
struct node
{
    int val, max, min;
} t[maxn << 2];
void pushup(int x)
{
    t[x].max = std::max(t[lc].max, t[rc].max);
    t[x].min = std::min(t[lc].min, t[rc].min);
}
void build(int x, int l, int r)
{
    if (l == r)
    {
        t[x].val = a[l];
        t[x].max = a[l];
        t[x].min = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(x);
}
void maketag(int x, int len, int k)
{
    t[x].val += len * k;
    t[x].max += k;
    t[x].min += k;
    lzy[x] += k;
}
void pushdown(int x, int l, int r)
{
    int mid = (l + r) >> 1;
    maketag(lc, mid - l + 1, lzy[x]);
    maketag(rc, r - mid, lzy[x]);
    lzy[x] = 0;
}
bool inrange(int l, int r, int L, int R)
{
    return (l >= L && r <= R);
}
bool outrange(int l, int r, int L, int R)
{
    return (l > R || r < L);
}
void update(int x, int l, int r, int L, int R, int k)
{
    if (inrange(l, r, L, R))
        maketag(x, r - l + 1, k);
    else if (!outrange(l, r, L, R))
    {
        int mid = (l + r) >> 1;
        pushdown(x, l, r);
        update(lc, l, mid, L, R, k);
        update(rc, mid + 1, r, L, R, k);
        pushup(x);
    }
}
int l[maxn], r[maxn];
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, p, ans = 0, cnt = 0;
    std::vector<int> pre[maxn], nxt[maxn];
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    build(1 ,1, n);
    for (int i = 1; i <= m; i++)
    {
        std::cin >> l[i] >> r[i];
        update(1, 1, n, l[i], r[i], -1);
        nxt[l[i]].push_back(r[i]);
        pre[r[i]].push_back(l[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < nxt[i].size(); j++)
            update(1, 1, n, i, nxt[i][j], 1);
        if (t[1].max - t[1].min > ans)
            ans = t[1].max - t[1].min, p = i;
        for (int j = 0; j < pre[i].size(); j++)
            update(1, 1, n, pre[i][j], i, -1);
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= m; i++)
        if (outrange(p, p, l[i], r[i]))
            cnt++;
    std::cout << cnt << '\n';
    for (int i = 1; i <= m; i++)
        if (outrange(p, p, l[i], r[i]))
            std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16869461.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1108E2)

## 思路

怎么会有题解是 $O(n^2+nm)$ 的垃圾做法阿，这题可以直接线段树做。

考虑枚举一个点 $i$，假如我们想要 $i$ 点作为最小值，贪心地想，我们如果把所有包含 $i$ 的区间选进去，那么结果一定不劣。

假设最大值位于点 $j$，区间 $k$ 包含了点 $i$。

那么我们可以分类讨论：

+ 区间 $k$ 包含了点 $j$，此时 $a_i,a_j$ 一起减，答案不变。
+ 区间 $k$ 未包含点 $j$，此时仅有 $a_i$ 会减，答案增大 $1$。

总上所述，最有策略是选择所有包含点 $i$ 的区间。

于是仅需一颗支持区间修改的线段树即可。

时间复杂度 $O(n \log n+m \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;
struct Segment_Tree{
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid ((l+r)>>1)
    int minx[N<<2],maxx[N<<2],lazy[N<<2];
    inline void pushdown(int x){
        minx[ls]+=lazy[x];minx[rs]+=lazy[x];
        maxx[ls]+=lazy[x];maxx[rs]+=lazy[x];
        lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
        lazy[x]=0;
    }
    inline void update(int x,int l,int r,int ll,int rr,int v){
        if (ll<=l && r<=rr){minx[x]+=v,maxx[x]+=v,lazy[x]+=v;return;}
        pushdown(x);
        if (ll<=mid) update(ls,l,mid,ll,rr,v);
        if (mid<rr) update(rs,mid+1,r,ll,rr,v);
        minx[x]=min(minx[ls],minx[rs]);
        maxx[x]=max(maxx[ls],maxx[rs]);
    }
}T;
int a[N],xx[N],yy[N];
vector<int>b[N];
priority_queue< pair<int,int>,deque< pair<int,int> >,greater< pair<int,int> > >q;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;int x,y,ans=0,pl=0;
    for (int i=1;i<=n;++i) cin>>a[i],T.update(1,1,n,i,i,a[i]);
    for (int i=1;i<=m;++i) cin>>x>>y,b[x].push_back(y),xx[i]=x,yy[i]=y;
    for (int i=1;i<=n;++i){
        for (auto j:b[i]) T.update(1,1,n,i,j,-1),q.push({j,i});
        while (!q.empty() && q.top().first<i) T.update(1,1,n,q.top().second,q.top().first,1),q.pop();
        if (T.maxx[1]-T.minx[1]>ans) ans=T.maxx[1]-T.minx[1],pl=i;
    }
    cout<<ans<<'\n';
    vector<int>Ans;
    for (int i=1;i<=m;++i)
        if (xx[i]<=pl && yy[i]>=pl) Ans.push_back(i);
    cout<<(int)Ans.size()<<'\n';
    for (auto i:Ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
```


---

## 作者：andyli (赞：0)

考虑枚举最大值不动，执行所有其他操作来获得最小值。注意到 $m$ 较小，可以将区间上的坐标离散化，预处理每段初始的最大/最小值，然后暴力执行操作。时间复杂度 $O(n + m^2)$。

```cpp
int main() {
    dR(int, n, m);
    dRV(int, a, n);
    dRV(pi, b, m);

    vi c{0, n};
    for (auto&& [l, r]: b)
        c.eb(--l), c.eb(r);
    UNIQUE(c);
    for (auto&& [l, r]: b)
        l = LB(c, l), r = LB(c, r);
    vi mn(len(c) - 1, inf<int>);
    vi mx(len(c) - 1, -inf<int>);
    _for (i, n) {
        int t = UB(c, i) - 1;
        chkmin(mn[t], a[i]);
        chkmax(mx[t], a[i]);
    }
    pi ans{-inf<int>, -1};
    _for (i, len(c) - 1) {
        vi new_mn{mn};
        for (auto&& [l, r]: b)
            if (l > i || r <= i)
                _for (j, l, r)
                    new_mn[j]--;
        if (chkmax(ans.first, mx[i] - min(new_mn)))
            ans.second = i;
    }
    print(ans.first);
    vi Ans;
    _for (i, m) {
        auto&& [l, r] = b[i];
        if (l > ans.second || r <= ans.second)
            Ans.eb(i + 1);
    }
    print(len(Ans));
    print(Ans);
    return 0;
}
```

---

