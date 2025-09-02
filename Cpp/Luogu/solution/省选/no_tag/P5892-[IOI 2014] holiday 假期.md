# [IOI 2014] holiday 假期

## 题目描述

健佳正在制定下个假期去台湾的游玩计划。在这个假期，健佳将会在城市之间奔波，并且参观这些城市的景点。

在台湾共有 $n$ 个城市，它们全部位于一条高速公路上。这些城市连续地编号为 $0$ 到 $n-1$。

对于城市 $i$（$0 < i < n-1$）而言，与其相邻的城市是 $i-1$ 和 $i+1$。但是对于城市 $0$，唯一与其相邻的是城市 $1$。而对于城市 $n-1$，唯一与其相邻的是城市 $n-2$。

每个城市都有若干景点。健佳有 $d$ 天假期并且打算要参观尽量多的景点。健佳已经选择了假期开始要到访的第一个城市。在假期的每一天，健佳可以选择去一个相邻的城市，或者参观所在城市的所有景点，但是不能同时进行。即使健佳在同一个城市停留多次，他也不会去重复参观该城市的景点。请帮助健佳策划这个假期，以便能让他参观尽可能多的景点。

## 说明/提示

**子任务**

在所有的子任务中，有 $0 \le d \le 2n+\lfloor\frac n2\rfloor$。而且，每个城市中的景点数都是非负整数。

| 子任务 | 分值 | $n$ | 各城市景点数的最大值 | 起点城市 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $7$ | $2 \le n \le 20$ | $10^9$ | 无限制 |
| $2$ | $23$ | $2 \le n \le 10^5$ | $100$ | 城市 $0$ |
| $3$ | $17$ | $2 \le n \le 3 \times 10 ^3$ | $10^9$ |无限制  |
| $4$ | $53$ | $2 \le n \le 10^5$ | $10^9$ | 无限制 |

## 样例 #1

### 输入

```
5 2 7
10 2 20 30 1
```

### 输出

```
60
```

# 题解

## 作者：lhm_ (赞：11)

发现最优情况一定是一直向一个方向走或先走一段后再回来往回走一段。向左和向右是一样的，只需翻转就能转化为同一个问题了。

考虑枚举走的区间，设走完整个区间后的剩余天数为 $k$，那么对于该区间的最优答案一定是参观区间内权值前 $k$ 大的城市，用主席树实现可以做到 $O(n^2 \log n)$ 的复杂度。

发现随着左端点的变大，其对应的最优的右端点一定是不降的，也就是其具有决策单调性。因为之前的最优的右端点的城市一定是参观的，所以将右端点移出区间是不优的。

像决策单调性的 $DP$ 一样分治解决即可，复杂度为 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxm 3000010
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,s,d,cnt,tot;
ll ans;
int rt[maxn],ls[maxm],rs[maxm];
ll a[maxn],b[maxn],siz[maxm],sum[maxm];
void insert(int l,int r,int pos,int &cur)
{
    int x=++tot;
    ls[x]=ls[cur],rs[x]=rs[cur];
    siz[x]=siz[cur]+1,sum[x]=sum[cur]+b[pos],cur=x;
    if(l==r) return;
    if(pos<=mid) insert(l,mid,pos,ls[cur]);
    else insert(mid+1,r,pos,rs[cur]);
}
ll query(int l,int r,int k,int x,int y)
{
    if(k<=0) return 0;
    if(k>siz[y]-siz[x]) return sum[y]-sum[x];
    if(l==r) return b[l]*k;
    if(k<=siz[rs[y]]-siz[rs[x]]) return query(mid+1,r,k,rs[x],rs[y]);
    return query(l,mid,k-siz[rs[y]]+siz[rs[x]],ls[x],ls[y])+sum[rs[y]]-sum[rs[x]];
}
ll calc(int l,int r)
{
    return query(1,cnt,d-(2*(r-s)+s-l),rt[l-1],rt[r]);
}
void solve(int l,int r,int L,int R)
{
    if(l>r) return;
    if(L==R)
    {
        for(int i=l;i<=r;++i) ans=max(ans,calc(i,L));
        return;
    }
    ll pos=L,mx=calc(mid,L);
    for(int i=L+1;i<=R;++i)
    {
        ll v=calc(mid,i);
        if(v>mx) mx=v,pos=i;
    }
    ans=max(ans,mx),solve(l,mid-1,L,pos),solve(mid+1,r,pos,R);
}
void clear()
{
    for(int i=1;i<=n;++i) rt[i]=0;
    for(int i=1;i<=tot;++i) ls[i]=rs[i]=siz[i]=sum[i]=0;
    tot=0;
}
void work()
{
    clear();
    for(int i=1;i<=n;++i) rt[i]=rt[i-1],insert(1,cnt,a[i],rt[i]);
    for(int i=1;i<=s;++i) ans=max(ans,calc(i,s));
    solve(1,s-1,s+1,n);
}
int main()
{
    read(n),read(s),read(d),s++;
    for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
    sort(b+1,b+n+1),cnt=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
    work(),s=n-s+1,reverse(a+1,a+n+1),work(),printf("%lld",ans);
    return 0;
}
```

---

## 作者：C3H5ClO (赞：5)

首先，健佳的移动路线一定是下列4种中的一种：

1.一直向左走

2.一直向右走

3.向左走一定距离后折返，经过起点后向右

4.向右走一定距离后折返，经过起点后向左

途中还可能会停下来参观景点。

那么，我们可以求出4个数组：

$fl[i]:$向左走，花费$i$时间得到的最大价值

$fr[i]:$向右走，花费$i$时间得到的最大价值

$gl[i]:$走一步花费两天（相当于折返），向左走，花费$i$时间得到的最大价值

$gr[i]:$走一步花费两天，向右走，花费$i$时间得到的最大价值

已知这4个数组就可以求出每种情况的答案。这4个数组求的方法差不多，就讲讲$fr[i]$怎么求。设起点为$s$。

假设$d[i]$是使$fr[i]$最大的向右走的距离（如果有多个，取最大的），则$d[i]$关于$i$单调不降，满足决策单调，可以分治解决。

那么为什么决策单调呢？4个数组证明方法类似，下面给出$fr$的证明。

假设$d[x+1]<d[x]$。那么，我们需要证明存在一种距离为$d'[x+1]\ge d[x]$的方案，使$fr[x+1]$不比距离为$d[x+1]$时劣。

我们先从$[s,s+d[x+1]]$中去掉景点数第$x-d[x+1]$多的城市$c$。这时，由于$fr[x]$在距离为$d[x]$时不劣于距离为$d[x+1]<d[x]$时，因此将距离改为$d[x]$不会更劣。此时，选取的是景点数前$x-d[x]$多的城市，我们再把去掉的1个城市再加一个回去，加的是$[s,s+d[x]]$中第$x-d[x]+1$多的城市$c'$。由于$[s,s+d[x+1]]\subseteq[s,s+d[x]],x-d[x]+1\le x-d[x+1]$，必定有$a[c']\ge a[c]$，这样就构造出了一种距离为$d[x]$，并且$fr[x+1]$不劣于距离为$d[x+1]$时的方案，假设不成立。

因此，$d[x+1]\ge d[x]$，决策单调性成立。

代码：
```cpp
//#include"holiday.h"
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,b,a) for(int i=(b);i>=(a);i--)
#define pb(x) push_back(x)
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define ld long double
#define pii pair<int,int>
#define pli pair<ll,int>
#define wln putchar('\n')
#define clr(a) memset(a,0,sizeof(a))
template<class T> void chkmax(T &x,T y){if(x<y)x=y;}
template<class T> void chkmin(T &x,T y){if(y<x)x=y;}
void pia(int a[],int l){for(int i=1;i<=l;i++)printf("%d ",a[i]);}
const int N=100005,V=2000005;
int rt[N],aa[N],lenaa,n,s;
ll fl[N<<2],fr[N<<2],gl[N<<2],gr[N<<2],ans;
struct presidenttree
{
    int v0[V],ls[V],rs[V],vcnt;
    ll v1[V];
    int copynode(int id)
    {
        vcnt++;
        v0[vcnt]=v0[id];
        v1[vcnt]=v1[id];
        ls[vcnt]=ls[id];
        rs[vcnt]=rs[id];
        return vcnt;
    }
    void pushup(int id)
    {
        v0[id]=v0[ls[id]]+v0[rs[id]];
        v1[id]=v1[ls[id]]+v1[rs[id]];
    }
    void ddxg(int &id,int l,int r,int x)
    {
        id=copynode(id);
        if(l==r){v0[id]++; v1[id]+=aa[x]; return;}
        int mid=l+r>>1;
        if(x<=mid)ddxg(ls[id],l,mid,x);
        else ddxg(rs[id],mid+1,r,x);
        pushup(id);
    }
    ll qjcx(int id1,int id2,int l,int r,int k)
    {
        if(l==r)return 1ll*aa[l]*min(v0[id2]-v0[id1],k);
        int mid=l+r>>1,t=v0[rs[id2]]-v0[rs[id1]];
        if(k<=t)return qjcx(rs[id1],rs[id2],mid+1,r,k);
        else return v1[rs[id2]]-v1[rs[id1]]+qjcx(ls[id1],ls[id2],l,mid,k-t);
    }
}T;
void solve1(int l,int r,int dl,int dr)
{
	if(l>r)return;
    int mid=l+r>>1,dmid=dl;
	ll x;
    for(int i=dl;i<=min({dr,mid,n-s});i++)
    {
        x=T.qjcx(rt[s-1],rt[s+i],0,lenaa-1,mid-i);
        if(x>fr[mid])fr[mid]=x,dmid=i;
    }
    solve1(l,mid-1,dl,dmid);
    solve1(mid+1,r,dmid,dr);
}
void solve2(int l,int r,int dl,int dr)
{
	if(l>r)return;
    int mid=l+r>>1,dmid=dl;
	ll x;
    for(int i=dl;i<=min({dr,mid/2,n-s});i++)
    {
        x=T.qjcx(rt[s-1],rt[s+i],0,lenaa-1,mid-i*2);
        if(x>gr[mid])gr[mid]=x,dmid=i;
    }
    solve2(l,mid-1,dl,dmid);
    solve2(mid+1,r,dmid,dr);
}
void solve3(int l,int r,int dl,int dr)
{
	if(l>r)return;
    int mid=l+r>>1,dmid=dl;
	ll x;
    for(int i=dl;i<=min({dr,mid,s-1});i++)
    {
        x=T.qjcx(rt[s-i-1],rt[s-1],0,lenaa-1,mid-i);
        if(x>fl[mid])fl[mid]=x,dmid=i;
    }
    solve3(l,mid-1,dl,dmid);
    solve3(mid+1,r,dmid,dr);
}
void solve4(int l,int r,int dl,int dr)
{
	if(l>r)return;
    int mid=l+r>>1,dmid=dl;
	ll x;
    for(int i=dl;i<=min({dr,mid/2,s-1});i++)
    {
        x=T.qjcx(rt[s-i-1],rt[s-1],0,lenaa-1,mid-i*2);
        if(x>gl[mid])gl[mid]=x,dmid=i;
    }
    solve4(l,mid-1,dl,dmid);
    solve4(mid+1,r,dmid,dr);
}
ll findMaxAttraction(int in_n, int in_s, int d, int a[]) {
    n=in_n; s=in_s+1;
    for(int i=0;i<n;i++)aa[lenaa++]=a[i];
    sort(aa,aa+lenaa);
    lenaa=unique(aa,aa+lenaa)-aa;
    for(int i=n;i;i--)a[i]=lower_bound(aa,aa+lenaa,a[i-1])-aa;
    for(int i=1;i<=n;i++)T.ddxg(rt[i]=rt[i-1],0,lenaa-1,a[i]);
    solve1(1,d,0,n-s);
    solve2(1,d,0,n-s);
    solve3(1,d,0,s-1);
    solve4(1,d,0,s-1);
	for(int i=0;i<=d;i++)ans=max({ans,fl[i]+gr[d-i],gl[i]+fr[d-i]});
	return ans;
}
int main() {
    int n, start, d;
    int attraction[100000];
    int i, n_s;
    n_s = scanf("%d %d %d", &n, &start, &d);
    for (i = 0 ; i < n; ++i) {
	n_s = scanf("%d", &attraction[i]);
    }
    printf("%lld\n", findMaxAttraction(n, start, d,  attraction));
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：3)

首先我们考虑路径应该是先往一个方向走一段，再往另一个方向走一段，走多于 $1$ 次重复路径一定不优。

那么我们将路径分为向右走，向左走，向右走再折返，向左走再折返。

这几种路径本质上差不多，这里只以向左走为例讲解。

设计状态 $f_i$ 表示花费 $i$ 天向左走所可以参观的景点数量最大值，那么我们把过程中移动和参观的花费分开计算，假定我们走到第 $j$ 的城市，那么我们会花费 $start - j$ 的时间移动，剩下的时间则一定是参观区间 $[j,start]$ 中景点最多的 $i - start + j$ 个城市，这一个过程可以用主席树维护，而不难发现 $f_i$ 具有决策单调性，因此考虑分治优化即可在 $O(n \log^2 n)$ 的时间内解决问题。

另外本题较为卡空间，需要将 $a_i$ 离散化。

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
const int maxn = 3e5+114;
int top;
long long f[maxn],g[maxn],f1[maxn],g1[maxn];
int root[maxn];
__gnu_pbds::gp_hash_table<int,int> F,G;
int n,d; 
int a[maxn],s;
struct Node{
    int sum,ls,rs;
	long long val;
}tr[maxn*20];
int tot;
long long mx,p;
inline long long kth(int lt,int rt,int L,int R,int k){
	k=min(k,tr[R].sum-tr[L].sum);
    if(lt==rt){
    	return 1ll*k*G[lt];
	}
	if(k<1) return 0;
    int mid=(lt+rt)>>1;
    if((tr[tr[R].rs].sum-tr[tr[L].rs].sum)>=k){
        return kth(mid+1,rt,tr[L].rs,tr[R].rs,k);
    }
    else{
        return (tr[tr[R].rs].val-tr[tr[L].rs].val)+kth(lt,mid,tr[L].ls,tr[R].ls,k-(1ll*tr[tr[R].rs].sum-1ll*tr[tr[L].rs].sum));
    }
}
inline void add(int cur,int lst,int lt,int rt,long long pos){
    tr[cur].sum=tr[lst].sum+1;
    tr[cur].val=tr[lst].val+G[pos];
    if(lt==rt){
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid){
        tr[cur].rs=tr[lst].rs;
        tr[cur].ls=++tot;
        add(tr[cur].ls,tr[lst].ls,lt,mid,pos);
    }
    else{
        tr[cur].ls=tr[lst].ls;
        tr[cur].rs=++tot;
        add(tr[cur].rs,tr[lst].rs,mid+1,rt,pos);
    }
}
void solve1(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	mx=0,p=R;
	for(int i=L;i<=R;i++){
		if(kth(1,top,root[i-1],root[s-1],mid-(s-i))>mx){
			mx=kth(1,top,root[i-1],root[s-1],mid-(s-i));
			p=i;
		}
	}
	f[mid]=mx;
	solve1(l,mid-1,p,R);
	solve1(mid+1,r,L,p);
}
void solve2(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	mx=0,p=L;
	for(int i=L;i<=R;i++){
		if(kth(1,top,root[s],root[i],mid-(i-s))>mx){
			mx=kth(1,top,root[s],root[i],mid-(i-s));
			p=i;
		}
	}
	g[mid]=mx;
	solve2(l,mid-1,L,p);
	solve2(mid+1,r,p,R);
}
void solve3(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	mx=0,p=R;
	for(int i=L;i<=R;i++){
		if(kth(1,top,root[i-1],root[s-1],mid-(s-i)*2)>mx){
			mx=kth(1,top,root[i-1],root[s-1],mid-(s-i)*2);
			p=i;
		}
	}
	f1[mid]=mx;
	solve3(l,mid-1,p,R);
	solve3(mid+1,r,L,p);
} 
void solve4(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	mx=0,p=L;
	for(int i=L;i<=R;i++){
		if(kth(1,top,root[s],root[i],mid-(i-s)*2)>mx){
			mx=kth(1,top,root[s],root[i],mid-(i-s)*2);
			p=i;
		}
	}
	g1[mid]=mx;
	solve4(l,mid-1,L,p);
	solve4(mid+1,r,p,R);
}
int b[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s>>d;
	s++;//我比较习惯标号从 1 开始
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		F[b[i]]=i;
		G[i]=b[i];
	}
	top=n+10;
	for(int i=1;i<=n;i++){
		root[i]=++tot;
		add(root[i],root[i-1],1,top,F[a[i]]);
	}
	solve1(0,d,1,s-1);
	solve2(0,d,s+1,n);
	solve3(0,d,1,s-1);
	solve4(0,d,s+1,n);
	long long ans=0;
	for(int i=0;i<=d;i++) ans=max(max(ans,g1[i]+f[d-i]),f1[i]+g[d-i]);
	for(int i=1;i<=d;i++) ans=max(max(ans,g1[i-1]+f[d-i]+a[s]),f1[i-1]+g[d-i]+a[s]);
	cout<<ans<<'\n'; 
}
```


---

## 作者：LingHusama (赞：2)

## P5892 holiday 假期题解

###  前言：
如果您想要过这一道题，需要的前置条件：
1. 知道什么是决策单调性。
2. 知道可持久化线段树怎么找前 $k$ 大。
3. 有耐心看很多文字。

对于第二点，如果您不会的话，可以参考我的学习笔记（专门为过这道题做的）。

链接：https://i.cnblogs.com/posts/edit;postId=17697328

参考博客链接：https://www.luogu.com.cn/blog/hl666/solution-p5892
### 正解：
注释：若下面的任何一步通过看大佬的题解已经明白的，可以跳过。
1. 四种走法：我们发现最终有可能成为答案的走法只有四种，一直向左走，一直向右走，先左走并最终走到右侧，先右走并且最终走到左侧。前两种走法我就不再解释了。对于后两种走法其中一个方面是因为你可能走到最左侧或者最右侧还有很多剩余步数可供消耗，可以用于一些折返。至于其他的走的方式，也很容易举出反例或者利用贪心证明其不是最优。

2. 四种方程：上文可知，我们有四种走的方式，因此肯定是四种。

3. 最初的状态的设计以及转移的思想：我们可以用 $f_i$来表示从起点走到最远的点是 $i$ 点的最佳答案。因为是最远的点，此时花费的时间最多为 $2\times dis_{start,i}$。那么我们显然可以枚举这个花费的时间，假设为 $cost$，那么我们用于参观的时间就有 $cost-dis_{start,i}$ 这么长，而这个就相当于我在区间 $[ i,start ]$ 中（假设 $i$ 小于 $start$），选择这么多个景点让我参观，贪心一点，我们肯定选前几个是吧。于是就可以用可持久化线段树来找就好。但是我们会发现时间复杂度不太对，在 $n^2\times\log n$ 这样。不仅如此，还会发现就这样设计状态的话，对于后两种很难表示（我个人认为）。

4. 优化状态设计。换一个状态，用 $f_i$ 表示用时 $i$ 能有的最佳答案，然后再枚举最远走到的地方，而主要思想并没有变化，至于时间上的问题，可以看第五点理解。
5. 优化：其实，仔细看看上面的第三点可以发现，我根本就没有什么转移方程，感觉像暴力一样！但实际上，我们发现，随着你分配的时间更多，我肯定是走的比上一次远更好一些。用类似整体二分的思想分治，二分时间，然后枚举决策点区间找最优，根据当前决策点依单调性保证去除没用的点就好。
6. 详细理解优化：如果上面没看懂，可以康康这一点。让我们假设在做先向左再向右的这个情况，此时左侧折返顶点为 $X$，右侧最终到达点为 $Y$，决策单调性保证 $X$ 左侧移动时 $Y$ 也向左侧移动。要是我们已经知道左侧顶点取值范围为 $[L,R]$，我们可以分治他在 $MID$，接着用 $n$ 的时间来看 $Y$ 的位置，并在这段区间不同的前 $k$ 大中找出最有答案，然后接着二分就好啦！最后扫一遍得到答案即可。 
7. 简化代码（可跳过），发现其实正着做一遍两个转移，反着做一遍同样的两个转移是一样的涅，但是我懒得写新的主席树的函数，就不想这么做涅。

### 代码：
其实感觉和其他大佬的代码没啥大的区别，关键还是要靠理解啊！
```c
#include<bits/stdc++.h>
using namespace std;
int num[250005];
int lsh[250005];
int buc[250005];
int cnt=0;
vector<int>root;
struct node{
	int rs;
	int ls;
	long long sum;
	int val;
}tree[2000005];
inline int addnode(int x){
	int ret=++cnt;
	tree[ret]=tree[x];
	return ret;
}
inline void pushup(int rt){
	tree[rt].val=tree[tree[rt].ls].val+tree[tree[rt].rs].val;
	tree[rt].sum=tree[tree[rt].ls].sum+tree[tree[rt].rs].sum;
}
inline void build(int rt,int l,int r){
	if(l==r){
		tree[rt].val=0;
		return;
	}
	tree[rt].ls=++cnt;
	tree[rt].rs=++cnt;
	int mid=(l+r)>>1;
	build(tree[rt].ls,l,mid);
	build(tree[rt].rs,mid+1,r);
	
}
inline int change(int rt,int x,int val,int L,int R){
	int now=addnode(rt);
	int le=L;
	int ri=R;
	if(le==ri){
		tree[now].val=val;
		tree[now].sum=1ll*val*lsh[x];
		return now;
	}
	int mid=(le+ri)>>1;
	if(x<=mid){
		tree[now].ls=change(tree[now].ls,x,val,L,mid);
	}
	else{
		tree[now].rs=change(tree[now].rs,x,val,mid+1,R);
	}
	pushup(now);
	return now;
}
inline long long get(int Lrt,int Rrt,int k,int L,int R){//求前k大的和 
	int le=L;
	int ri=R;
	if(le==ri){
		return 1ll*lsh[le]*k;
	}
	int Lls=tree[Lrt].ls;
	int Lrs=tree[Lrt].rs;
	int Rls=tree[Rrt].ls;
	int Rrs=tree[Rrt].rs;
	int rsum=tree[Rrs].val-tree[Lrs].val;
	int mid=(L+R)>>1;
	if(rsum<k){
		return 1ll*(tree[Rrs].sum-tree[Lrs].sum+get(Lls,Rls,k-rsum,L,mid));
	}
	else{
		return 1ll*get(Lrs,Rrs,k,mid+1,R);
	}
}
int n,s,d;
inline long long findkth(int le,int ri,int k){
	if(k==0||le>ri){
		return 0;
	}
	k=min(k,ri-le+1);
	return 1ll*get(root[le-1],root[ri],k,1,n);
}
//----------------------------------------以上是打的可持久化线段树 
int pos[250005];
long long f1[250005],f2[250005],f3[250005],f4[250005];

inline void clear(){
	memset(pos,0,sizeof(pos));
}
inline void solveleft(int begin,int ed,int l,int r){//看英文名应该懂我在干啥吧 
	if (l>r){
		return; 
	}
	int mid=(l+r)>>1;
	for(int i=begin;i<=ed;i++){
	 	if (mid-(i-s)>=0){
			long long ret=findkth(s,i,mid-(i-s));
			
			if (!pos[mid]||ret>f1[mid]){
				f1[mid]=ret;
				pos[mid]=i;
			} 
		}
	}

	solveleft(begin,pos[mid],l,mid-1);
	solveleft(pos[mid],ed,mid+1,r);
}
inline void solverl(int begin,int ed,int l,int r){
	if (l>r){
		return; 
	}
	int mid=(l+r)>>1;
	for(int i=begin;i<=ed;i++){
	 	if (mid-((i-s)*2)>=0){
			long long ret=findkth(s,i,mid-(i-s)*2);
			if (!pos[mid]||ret>f2[mid]){
				f2[mid]=ret;
				pos[mid]=i;
			} 
		}
	}

	solverl(begin,pos[mid],l,mid-1);
	solverl(pos[mid],ed,mid+1,r);
}
inline void solveright(int begin,int ed,int l,int r){

	if (l>r){
		return; 
	}
	int mid=(l+r)>>1;
	for(int i=begin;i<=ed;i++){
		
	 	if (mid-((s-i))>=0){
			long long ret=findkth(i,s-1,mid-(s-i));
//			cout<<"TEST"<<i<<" "<<s-1<<" "<<mid-(s-i)<<" "<<ret<<endl;
			if (!pos[mid]||ret>f3[mid]){
				f3[mid]=ret;
				pos[mid]=i;
			} 
		}
	}
	solveright(pos[mid],ed,l,mid-1);
	solveright(begin,pos[mid],mid+1,r);
	
} 
inline void solvelr(int begin,int ed,int l,int r){
	if (l>r){
		return; 
	}
	int mid=(l+r)>>1;
	for(int i=begin;i<=ed;i++){
	 	if (mid-((s-i)*2)>=0){
			long long ret=findkth(i,s-1,mid-(s-i)*2);
			if (!pos[mid]||ret>f4[mid]){
				f4[mid]=ret;
				pos[mid]=i;
			} 
		}
	}
	solvelr(pos[mid],ed,l,mid-1);
	solvelr(begin,pos[mid],mid+1,r);
}
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(long long x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}


int main(){
//	ios::sync_with_stdio(false);
	
//	cin >> n >> s >> d;
	n=read();
	s=read();
	d=read();
	s++;
	for(int i=1;i<=n;i++){
		num[i]=read();
		lsh[i]=num[i];
	}
	root.push_back(0);
	build(0,1,n);
	sort(lsh+1,lsh+1+n);
	int cntt=unique(lsh+1,lsh+1+n)-lsh-1;
	for(int i=1;i<=n;i++){
		num[i]=lower_bound(lsh+1,lsh+1+cntt,num[i])-lsh;
		root.push_back(change(root[i-1],num[i],++buc[num[i]],1,n));
	}
	//可持久化线段树模板
	findkth(3,5,4);
	clear();
	solveleft(s,min(s+d,n),1,d);
	clear();
	solverl(s,min(s+(d*2),n),1,d);
	clear();
	solveright(max(1,s-d),s,1,d);
	clear();
	solvelr(max(1,s-d*2),s,1,d);
	long long ans=0;
//	cout<<cnttt<<endl;
//	for(int i=0;i<=d;i++){
//		cout<<f1[i]<<" "<<f2[i]<<" "<<f3[i]<<" "<<f4[i]<<endl;
//	}
	for(int i=0;i<=d;++i){
		ans=max(ans,max(f1[i]+f4[d-i],f2[i]+f3[d-i]));
	}
	cout<<ans;
	
}
```
### 后记：
这道题要算好主席树的大致空间限制，以及要记得由于我们状态和时间有关，应该开到 $n$ 的 $3$ 倍左右比较保险。



---

## 作者：hl666 (赞：2)

首先我们考虑如果起点为端点，只能往一个方向走怎么办，那么很容易想到暴力枚举最远走到哪个点，然后在这个区间内将剩下的前$k$大数之和求出来更新答案，其中$k$是还可以进行的操作数

那么如果起点在中间，那么我们走的方法是怎么样的呢？乍一看好像很复杂，但我们仔细分析一下会发现只有以下四种走法：

1. 从起点开始向右走
2. 从起点开始向右走，并且走回到起点
3. 从起点开始向左走
4. 从起点开始向左走，并且走回到起点

其中$1,4$可以组合起来，$2,3$同理

那么我们容易想到直接DP，用$f1,f2,f3,f4$分别表示上面的走法，其中$f1_i$就表示向右走$i$天最多可以参观多少个景点，其余的同理，那么我们容易想到更新答案：

$$\max_{i=0}^m \max(f1_i+f4_{m-i},f2_i+f3_{m-i})$$

那么现在问题就是如何求出$f1,f2,f3,f4$了，回忆前面的那个暴力的做法，我们发现这个DP有一个明显的决策点，就是最远走到的点

然后再想一下不难发现这个DP满足**决策单调性**，以$f1$为例，设$f1_i$对应的走到最远的点为$pos_i$，那么对于$f1_{i+1}$，其能走到的最远的点$pos_{i+1}\ge pos_i$

然后我们就可以舒舒服服的利用经典的分治法进行处理，那个区间前$k$大和直接主席树维护即可，最终的复杂度就是$O(n\log^2 n)$


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define RI register int
#define CI const int&
#define Ms(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=100005,M=300005;
typedef long long LL;
int n,m,st,a[N],pos[M],rst[N],num; LL f1[M],f2[M],f3[M],f4[M],ans;
// f1:toward right; f2:toward right then return; f3:toward left; f4:toward left then return;
class President_Tree
{
	private:
		struct segment
		{
			int ch[2],size; LL sum;
		}node[N*20]; int rt[N],tot;
		#define lc(x) node[x].ch[0]
		#define rc(x) node[x].ch[1]
		#define sz(x) node[x].size
		#define sum(x) node[x].sum
		#define TN CI l=1,CI r=num
		inline void _insert(CI lst,int& now,CI val,CI rv,TN)
		{
			node[now=++tot]=node[lst]; ++sz(now); sum(now)+=rv;
			if (l==r) return; int mid=l+r>>1;
			if (val<=mid) _insert(lc(lst),lc(now),val,rv,l,mid);
			else _insert(rc(lst),rc(now),val,rv,mid+1,r); 
		}
		inline LL _query(CI x,CI y,CI rk,LL ret=0,TN)
		{
			if (l==r) return ret+1LL*rst[l]*rk; int mid=l+r>>1;
			if (rk<=sz(rc(y))-sz(rc(x))) return _query(rc(x),rc(y),rk,ret,mid+1,r);
			else return _query(lc(x),lc(y),rk-(sz(rc(y))-sz(rc(x))),ret+sum(rc(y))-sum(rc(x)),l,mid);
		}
	public:
		inline void insert(CI pos,CI val,CI rv)
		{
			_insert(rt[pos-1],rt[pos],val,rv);
		}
		inline LL query(CI l,CI r,CI rk)
		{
			if (l>r) return 0; return _query(rt[l-1],rt[r],min(rk,r-l+1));
		}
		#undef lc
		#undef rc
		#undef sz
		#undef sum
		#undef TN
}SEG;
#define Itval CI l=1,CI r=m
inline void solve1(CI beg,CI end,Itval)
{
	if (l>r) return; int mid=l+r>>1;
	for (RI i=beg;i<=end;++i) if (mid-(i-st)>=0)
	{
		LL ret=SEG.query(st,i,mid-(i-st));
		if (!pos[mid]||ret>f1[mid]) f1[mid]=ret,pos[mid]=i;
	}
	solve1(beg,pos[mid],l,mid-1); solve1(pos[mid],end,mid+1,r);
}
inline void solve2(CI beg,CI end,Itval)
{
	if (l>r) return; int mid=l+r>>1;
	for (RI i=beg;i<=end;++i) if (mid-(i-st<<1)>=0)
	{
		LL ret=SEG.query(st,i,mid-(i-st<<1));
		if (!pos[mid]||ret>f2[mid]) f2[mid]=ret,pos[mid]=i;
	}
	solve2(beg,pos[mid],l,mid-1); solve2(pos[mid],end,mid+1,r);
}
inline void solve3(CI beg,CI end,Itval)
{
	if (l>r) return; int mid=l+r>>1;
	for (RI i=beg;i<=end;++i) if (mid-(st-i)>=0)
	{
		LL ret=SEG.query(i,st-1,mid-(st-i));
		if (!pos[mid]||ret>f3[mid]) f3[mid]=ret,pos[mid]=i;
	}
	solve3(pos[mid],end,l,mid-1); solve3(beg,pos[mid],mid+1,r);
}
inline void solve4(CI beg,CI end,Itval)
{
	if (l>r) return; int mid=l+r>>1;
	for (RI i=beg;i<=end;++i) if (mid-(st-i<<1)>=0)
	{
		LL ret=SEG.query(i,st-1,mid-(st-i<<1));
		if (!pos[mid]||ret>f4[mid]) f4[mid]=ret,pos[mid]=i;
	}
	solve4(pos[mid],end,l,mid-1); solve4(beg,pos[mid],mid+1,r);
}
#undef Itval
int main()
{
	RI i; for (scanf("%d%d%d",&n,&st,&m),++st,i=1;i<=n;++i)
	scanf("%d",&a[i]),rst[i]=a[i]; sort(rst+1,rst+n+1);
	for (num=unique(rst+1,rst+n+1)-rst-1,i=1;i<=n;++i)
	a[i]=lower_bound(rst+1,rst+num+1,a[i])-rst,SEG.insert(i,a[i],rst[a[i]]);
	Ms(pos,0); solve1(st,min(st+m,n)); Ms(pos,0); solve2(st,min(st+(m>>1),n));
	Ms(pos,0); solve3(max(1,st-m),st); Ms(pos,0); solve4(max(1,st-(m>>1)),st);
	for (i=0;i<=m;++i) ans=max(ans,max(f1[i]+f4[m-i],f2[i]+f3[m-i]));
	return printf("%lld",ans),0;
}
```


---

## 作者：wangtairan114 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5892)
## 题意
给定长度为 $n$ 的序列 $a_i$，起点 $start$ 和总时间 $d$。每天可以从当前点向左或向右走一步，或者不走，增加 $a_i$ 的权值。每个点的权值只能取一次。求最大化权值和。
## 思路

注意到有四种行走方式：

1. 一直向左
2. 一直向右
3. 先向左走，再向右走
4. 先向右走，再向左走

可以证明，除了这四种行走方式，其它方式都是不优的。

同时，如果移动了 $k$ 步，我们一定取移动范围内权值最大的前 $(d-k)$ 个点权。

前两种走法很好处理，用优先队列维护一下即可。
```
    ll sum=0;
    priority_queue<ll,vector<ll>,greater<ll>> q;
    for (int i=st; i >= 1; i--) {
        q.push(a[i]);
        sum+=a[i];
        int len=abs(i-st);
        while (q.size()&&q.size()+len>d) {
            sum-=q.top();
            q.pop();
        }
        ans=max(ans,sum);
    }
    while (q.size())q.pop();
    sum=0;
    for (int i=st; i <= n; i++) {
        q.push(a[i]);
        sum+=a[i];
        int len=abs(i-st);
        while (q.size()&&q.size()+len>d) {
            sum-=q.top();
            q.pop();
        }
        ans=max(ans,sum);
    }
```
对于后两种走法，显然有决策单调性。记行走区间最左的点为左端点，最右的点为右端点。当左端点向右移动时，右端向左移动显然不优。

我们对值域维护一棵可持久化线段树，支持查询区间前 $k$ 大之和。将两种走法分别进行分治，统计最大值即可。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3fll
#define IINF 0x3f3f3f3f
#define DINF 10000000
#define ll long long
#define sc scanf
#define pr printf
#define v1 first
#define v2 second
#define lowbit(x) ((x)&(-x))
const int N=1e5+5;
ll a[N];
int son[N<<5][2];
int sz[N<<5];
ll val[N<<5];
#define lson son[k][0],l,mid
#define rson son[k][1],mid+1,r
#define mid ((l+r)>>1)
#define lson2 son[k1][0],son[k2][0],l,mid
#define rson2 son[k1][1],son[k2][1],mid+1,r
int tot=0;
void push_up(int k) {
    sz[k]=sz[son[k][0]]+sz[son[k][1]];
    val[k]=val[son[k][0]]+val[son[k][1]];
}
void modify(int lst,int &k,int l,int r,int lbor,ll va) {
    if (!k)
        k=++tot;
    if (l==r) {val[k]=va;sz[k]=1;return;}
    if (mid>=lbor) {son[k][1]=son[lst][1];modify(son[lst][0],lson,lbor,va);}
    else {son[k][0]=son[lst][0];modify(son[lst][1],rson,lbor,va);}
    push_up(k);
}
ll query(int k1,int k2,int l,int r,int k) {
    if (k<=0)return 0;
    if (l==r)return val[k2]-val[k1];
    if (sz[son[k2][1]]-sz[son[k1][1]]>k)return query(rson2,k);
    return val[son[k2][1]]-val[son[k1][1]]+query(lson2,k-sz[son[k2][1]]+sz[son[k1][1]]);
}
#undef mid
int rt[N];
int loc[N];
int d,st,n;
ll get_val(int lb,int rb,int tp) {
    int ldis=abs(st-lb),rdis=abs(st-rb);
    if(tp)return query(rt[lb-1],rt[rb],1,n,d-ldis*2-rdis);//记录折叠的情况
    return query(rt[lb-1],rt[rb],1,n,d-ldis-rdis*2);
}
ll ans;
void solve(int x,int y,int l,int r,int tp){
    if (l>r||x>y)
        return;
    int mid=(l+r)>>1;
    ll maxn=0;
    int maxpos=0;
    for (int i=x; i <= y; i++) {
        ll res=get_val(i,mid,tp);
        if (res>=maxn) {
            maxn=res;
            maxpos=i;
        }
    }
    ans=max(ans,maxn);
    solve(x,maxpos,l,mid-1,tp);
    solve(maxpos,y,mid+1,r,tp);
}
vector<pair<ll,int>> v;
int main() {
    sc("%d%d%d",&n,&st,&d);
    st++;
    for (int i=1; i <= n; i++) {
        sc("%lld",&a[i]);
        v.push_back({a[i],i});
    }
    sort(v.begin(),v.end());
    for (int i=0; i < v.size(); i++)
        loc[v[i].v2]=i+1;
    for (int i=1; i <= n; i++)
        modify(rt[i-1],rt[i],1,n,loc[i],a[i]);
    ll sum=0;
    priority_queue<ll,vector<ll>,greater<ll>> q;
    for (int i=st; i >= 1; i--) {//走法1，2
        q.push(a[i]);
        sum+=a[i];
        int len=abs(i-st);
        while (q.size()&&q.size()+len>d) {
            sum-=q.top();
            q.pop();
        }
        ans=max(ans,sum);
    }
    while (q.size())q.pop();
    sum=0;
    for (int i=st; i <= n; i++) {
        q.push(a[i]);
        sum+=a[i];
        int len=abs(i-st);
        while (q.size()&&q.size()+len>d) {
            sum-=q.top();
            q.pop();
        }
        ans=max(ans,sum);
    }
    solve(1,st-1,st+1,n,1);//走法3
    solve(1,st-1,st+1,n,0);//走法4
    cout << ans;
    return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 题意简析

给定 $n$ 个点排成一条链，每个点有价值 $ w_i$。你现在在第 $s$ 个点。每天你可以向左/向右移动一步，或获取当前点的价值。对于每个点，你最多只能获取一次价值。

求 $d$ 天内获取点的价值总和最大是多少。

# 思路解析

首先，你要了解什么是决策单调性：

> 决策单调性指的是，对于某些动态规划或优化问题，最优决策点随着状态变量的变化而单调递增或递减。这意味着，如果我们已经知道在某个状态下的最优决策点，那么在相邻状态下，最优决策点不会突然跳跃，而是会沿着一个单调的方向移动。

分析此题，发现只会有：

1. 一直向左
2. 一直向右
3. 先向左再向右
4. 先向右再向左

这四种走法。前两种的答案是显然的。对于后两种情况，两边都只需要算出走 $k$ 步能获得的最大价值，两边分开做。

---

我们定义以下状态：
- $fl[k]$：向左移动 $k$ 步的最大吸引力值。
- $fr[k]$：向右移动 $k$ 步的最大吸引力值。
- $gl[k]$：先向左移动若干步，再折返向右移动，总步数为 $k$ 的最大吸引力值。
- $gr[k]$：先向右移动若干步，再折返向左移动，总步数为 $k$ 的最大吸引力值。

对于 $fr[k]$，其转移方程为：

$$
fr[k] = \max_{0 \leq i \leq \min(k, n-s)} \text{query}(s, s+i, k-i)
$$

其中 $query(l, r, t)$ 表示从区间 $[l, r]$ 中选取前 $t$ 大的吸引力值之和。

---

为什么其具有决策单调性呢？

对于 $fr[k]$，如果 $i$ 是 $fr[k]$ 的最优决策点，那么对于 $fr[k+1]$，最优决策点 $i'$ 满足 $i' \ge i$。

假设对于 $fr[k]$，最优决策点为 $i$，即：

$$
fr[k] = \text{query}(s, s+i, k-i) \geq \text{query}(s, s+j, k-j) \quad \forall j \neq i
$$

对于 $fr[k+1]$，我们需要选择 $i'$ 使得：

$$
fr[k+1] = \text{query}(s, s+i', k+1-i')
$$

假设 $i' < i$，则：

$$
\text{query}(s, s+i', k+1-i') \leq \text{query}(s, s+i, k+1-i)
$$

因为 $i$ 是 $fr[k]$ 的最优决策点，且 $k+1-i > k-i$，所以 $\text{query}(s, s+i', k+1-i')$ 至少包含 $\text{query}(s, s+i', k+1-i')$ 的所有值，可能更多。因此：


$$
\text{query}(s, s+i, k+1-i) \geq \text{query}(s, s+i', k+1-i')
$$

这表明 $i'$ 不能比 $i$ 更优，因此最优决策点 $i'$ 必须满足 $i' \ge i$。

其他走法也是同理。


# 具体实现
由于决策点具有单调性，我们可以使用分治策略，维护一个区间的答案，合并时做不凸序列和凸序列的卷积即可。

将吸引力值离散化，使用主席树（可持久化线段树）进行查询。时间复杂度 $\mathcal{O}(n \log^2 n)$，可以通过此题。

大家的做法大同小异，需要注意的是本题各城市景点数的最大值是 $10^9$，而 $n \le 10^5$。

所以最后引用一句名言：

> 十年 OI 一场空，不开 `long long` 见祖宗！

~~（其实你全部都开，在函数中递归传递数组也会见祖宗，直接 MLE）。~~

---

## 作者：WaterM (赞：0)

更简明，更感性，~~更好猜~~的题解。

走的路是连续的，不妨枚举左端点和右端点。然后他肯定不会来回横跳。最优方案一定是向左走一定路程，再反过来向右走一定路程。（或者先向右，reverse 一下就行）

可以理解成，先一股劲向左走到某个点，再向右一边走一遍参观。  
我们设 $w(l, r)$ 为向左走到 $l$，向右走到 $r$ 的最大收益。走的路需要耗费 $r+st-2l$ 天，留下 $t=d-(r+st-2l)$ 天参观。（如果是参观天数是负的，$w$ 值自然是 $0$）  
对于给定的 $w(l, r)$ 就是在区间 $[l, r]$ 内查前 $t$ 大的和。主席树做到 $O(\log n)$ 的查询。

发现 $w(l, r)$ 在 $l$ 单增的情况下，最优的 $r$ 不减。  
感性理解就是，你少了更左边的一些景点参观不了，但是你多了一些时间向右走。在原来的基础上，要么花点时间参观之前路过没参观的，要么往右看看新的。不可能走得还没原来远。要不然原来为什么不少走一点呢，还省时间。  

接下来就是决策单调性。分治做到 $O(n\log^2 n)$ 的时间复杂度。

---

## 作者：xiao7_Mr_10_ (赞：0)

一个假的 dp 题。

首先，这个人旅游的路程肯定是先从起点往一个方向走，然后再回头走过起点。我们就可以暴力枚举这个人走的区间 $[l,r]$，再考虑参观前 $d-(r-l+1)$ 大的景点，用主席树维护。

我们考虑只往左走的情况，发现左端点 $l$ 向右移动的同时，最优秀的 $r$ 单调不降。这满足了**决策单调性**，我们可以用分治直接计算某个端点的答案。

计算往右走的情况可以直接反转数组，然后需要注意可能能够选取的城市数 $x$ 比区间长度还大，需要特殊处理。

---

