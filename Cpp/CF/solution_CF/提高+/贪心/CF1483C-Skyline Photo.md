# Skyline Photo

## 题目描述

[题目链接](https://www.luogu.com.cn/problem/CF1483C)

有 $n$ 栋楼房，每栋楼有一个高度 $a_i$ 和美丽值 $b_i$。  
现在，你需要把这 $n$ 栋楼房划分成若干个连续段，每一个连续段的美丽值为该段中最矮的楼房的美丽值。总的划分美丽值为每个连续段的美丽值之和。

你需要求出最大可能的总划分美丽值。

## 说明/提示

$1 \le n \le 3\cdot 10^5$。  
$a$ 为一个长度为 $n$ 的排列。  
$0 \le |b_i| \le 10^9$。

## 样例 #1

### 输入

```
5
1 2 3 5 4
1 5 3 2 4```

### 输出

```
15```

## 样例 #2

### 输入

```
5
1 4 3 2 5
-3 4 -10 2 7```

### 输出

```
10```

## 样例 #3

### 输入

```
2
2 1
-2 -3```

### 输出

```
-3```

## 样例 #4

### 输入

```
10
4 7 3 2 5 1 9 10 6 8
-4 40 -46 -8 -16 4 -10 41 12 3```

### 输出

```
96```

# 题解

## 作者：Fairicle (赞：20)

单调栈 $O(n)$ 解法。


容易发现朴素的 dp 式子 $f_i=f_j+w(j+1,i)$。这个 $w(j+1,i)$ 事实上就是单调栈更新到 $i$ 时，单调栈中下标大于 $j$ 的第一个数 $k$ 的 $b_k$。

或者换句话说，单调栈中的第 $p$ 个元素 $s_p$ 管辖着 $[s_{p-1}+1,s_p]$ 这个区间，$[s_{p-1}+1,s_p]$ 区间的数隶属于 $p$。

所以就是 $f_i=\max_{k=1}^{top}(\max_{j=s_{k-1}+1}^{s_k}(f_j)+b_{s_k})$

这个容易通过线段树来维护每个数所隶属的元素，做到 $O(nlogn)$。

但是也可以直接维护单调栈上的信息做到 $O(n)$。先上代码。

```cpp
#define ll long long
#define ri register int
#define N 300010
int n,h[N],b[N],top,s[N];
ll val[N],f[N],pre[N];
int main()
{
	n=rd();
	pre[0]=-1e18;
	for(ri i=1;i<=n;++i) h[i]=rd();
	for(ri i=1;i<=n;++i) b[i]=rd();
	for(ri i=1;i<=n;++i){
        ll tmp=f[i-1];
        while(top&&h[i]<h[s[top]]){
            tmp=max(tmp,val[top]);
            top--;
        }
        s[++top]=i,val[top]=tmp;
        f[i]=pre[top]=max(pre[top-1],tmp+b[i]);//two ways to transfer
    }
    cout<<f[n];
    return 0;
}
```

观察我们提出的 dp 式子，我们发现全部和单调栈中的下标相关，所以我们只需要以单调栈的下标来维护一些东西就可以了。

$val$ 数组维护的是 $[s_{i-1}+1,s_i]$ 中 $f$ 的最大值，也就是 $\max_{j=s_{i-1}+1}^{s_i}(f_j)$。

$pre$ 维护的是 $[1,s_i]$ 中 $f+b$ 的前缀最大值。

而 $tmp$ 就是以 $i$ 结尾的这一段的 $f$ 的最大值。

看转移部分，$pre[top-1]$ 表示 $[1,s_{top-1}]$ 这部分答案的最大值，而 $tmp+b[i]$ 则是 $[s_{top-1}+1,s_{top}]$ 这段的答案，两者取 $\max$ 即可。 

---

## 作者：Priori_Incantatem (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1483C)   
[我的Blog](https://blog.csdn.net/Brian_Pan_/article/details/115065320?spm=1001.2014.3001.5501)

感觉这道题跟当晚的ARC E 撞了，虽然并不是完全一样。  
结果我ARC E和这道题都没有在赛时做出来/kk。

这里记 $a_i,b_i$ 为第 $i$ 个楼房的高度和美丽值。
我们设 $f_i$ 为前 $i$ 栋房屋可以得到的最大美丽值，且 $\operatorname{val}(l,r)$ 表示区间 $[l,r]$ 内最矮的楼房的美丽值。
那么显然我们可以得到一个 $\mathcal O(n^2)$ 的转移：  
$f_i=\max\limits_{j=0}^{i-1}\{f_j+\operatorname{val}(j+1,i)\}$。

由于 $f_j$ 转移到 $f_i$ 时，只需要用到他们之间的最矮的楼房，所以我们考虑用单调栈来维护所有可能用到的楼房。

维护一个单调递增的栈 $c$（栈中存的是楼房编号），记 $cnt$ 为 $c$ 的大小，满足 $a_{c_i}<a_{c_{i+1}}\space|\space (1 \le i < cnt)$。  
那么我们继续考虑转移，同时维护单调栈：  
显然，当 $j \in [c_{k-1},c_k-1]\space | \space (1<k \le cnt)$ 时，转移用到的最矮楼房都是 $c_k$。因为根据单调栈的性质，$c_k$ 是 $[c_k,i]$ 中最矮的楼房。

这样，转移方程就变成了 $f_i=\max\limits_{k=2}^{cnt}\{(\max\limits_{j=c_{k-1}}^{c_k-1} f_j) + b_{c_k}\}$。注意在该次转移前已经将单调栈维护到 $i$。  
我们可以发现，在从 $f_j$ 转移到 $f_i$ 时，$f_j$ 后面加上的美丽值 $b$ 只跟他后面的第一个栈内元素有关。并且只要该元素不被弹出栈，$f_j$ 后面加上的美丽值永远不变。

那么，我们考虑用线段树维护每一个点的转移值，也就是 $f_j+b$。  
在维护单调栈时，对于每一个入栈的元素，我们将区间 $[c_{cnt-1},c_{cnt}-1]$ 全部加上 $b_{c_{cnt}}$。同理，在弹出栈的时候，将该区间全部减去 $b_{c_{cnt}}$。  
$f_i$ 的转移就是 $[0,i-1]$ 的区间最小值。  
注意在求出 $f_i$ 之后，要单点更新线段树。  
最后的 $f_n$ 就是我们要求的答案。

总时间复杂度 $\mathcal O(n \log n)$

-----

赛制最后90s码完了这个方法，结果 `WA on pretest 6`。赛后发现没开 `long long` /kk。  
为了美观和方便理解，只给出未开 `long long` 的代码。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
const int Maxn=3e5+10;
const int Maxm=Maxn<<2;
const int inf=(1ll<<60);
int a[Maxn],b[Maxn];
int f[Maxn],c[Maxn];
int maxv[Maxm],add[Maxm];
int n,ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
inline void push_up(int k)
{
    maxv[k]=max(maxv[k<<1],maxv[k<<1|1]);
}
inline void upd(int k,int v)
{
    add[k]+=v;
    maxv[k]+=v;
}
inline void push_down(int k)
{
    if(add[k]==0)return;
    upd(k<<1,add[k]);
    upd(k<<1|1,add[k]);
    add[k]=0;
}
void modify_seq(int k,int l,int r,int x,int y,int v)
{
    if(x<=l && r<=y)return upd(k,v);
    push_down(k);
    int mid=(l+r)>>1;
    if(x<=mid)modify_seq(k<<1,l,mid,x,y,v);
    if(mid<y)modify_seq(k<<1|1,mid+1,r,x,y,v);
    push_up(k);
}
void modify(int k,int l,int r,int pos,int v)
{
    if(l==r)
    {
        maxv[k]=v;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)modify(k<<1,l,mid,pos,v);
    else modify(k<<1|1,mid+1,r,pos,v);
    push_up(k);
}
int query(int k,int l,int r,int x,int y)
{
    if(x<=l && r<=y)return maxv[k];
    int mid=(l+r)>>1,ret=-inf;
    push_down(k);
    if(x<=mid)ret=query(k<<1,l,mid,x,y);
    if(mid<y)ret=max(ret,query(k<<1|1,mid+1,r,x,y));
    return ret;
}
int main()
{
    // freopen("in.txt","r",stdin);
    n=read();
    for(int i=1;i<=n;++i)
    a[i]=read();
    for(int i=1;i<=n;++i)
    b[i]=read();
    a[0]=-1;
    int cnt=1;
    f[1]=0;
    for(int i=1;i<=n;++i)
    {
        while(a[c[cnt]]>=a[i] && cnt)
        {
            modify_seq(1,0,n,c[cnt-1],c[cnt]-1,-b[c[cnt]]);
            --cnt;
        }
        modify_seq(1,0,n,c[cnt],i-1,b[i]);
        f[i]=query(1,0,n,0,i-1);
        modify(1,0,n,i,f[i]);
        c[++cnt]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}
```

---

## 作者：JasonL (赞：4)

### CF1483C Skyline Photo

[题目传送门](https://www.luogu.com.cn/problem/CF1483C)

#### 题目分析

首先有一个暴力的 $O(n^2)$ 写法：

$$f_i=\max\limits_{j<i} f_j+s(j+1,i)$$

其中 $s(l,r)$ 指 $[l,r]$ 区间内 $h_i$ 最小的位置对应的 $b_i$ 的值。

下面我们来考虑如何优化这种做法。

- 单调栈 + 线段树

假如我们对每个位置都算出了 $f_j+s(j+1,i)$ 的值，那么我们只需要在线段树上取 $\max$ 即可得到 $f_i$ 的值。

我们考虑如何从位置 $i$ 转移到 $i+1$。注意到会变化的只有 $s(l,r)$。假定在$i+1$之前第一个满足 $h_j<h_i$ 的位置为 $j$ ，那么对于在$(j,i]$ 这一段区间里的数，它们的 $s$ 函数均变化为 $b_{i+1}$ 。也就是说，我们的线段树需要支持区间覆盖，并维护区间内的 $f_{max}$ （如果一段区间被覆盖为同一个值，那么更优的转移一定是从 $f_i$ 更大的位置转移）。这样我们就可以用线段树完成 $O(n\log n)$ 的算法。而求出 $j$ 只需要一个单调栈即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs ((p<<1)|1)
using namespace std;
typedef long long ll;
const int maxn=601100;
int n,m;
int h[maxn],b[maxn];
ll f[maxn];
ll tag[maxn<<1],fmx[maxn<<1],tmx[maxn<<1];
//区间覆盖的b_i值，区间f_max，区间贡献最大值
bool itag[maxn<<1];
//是否被区间覆盖过
int s[maxn],st;
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
void update(int p){
	fmx[p]=max(fmx[p<<1],fmx[p<<1|1]);
	tmx[p]=max(tmx[p<<1],tmx[p<<1|1]);
}
void pushtag(int p,ll x){
	tag[p]=x;
	tmx[p]=fmx[p]+x;
	itag[p]=true;
}
void pushdown(int p){
	if(itag[p]){
		pushtag(ls,tag[p]);
		pushtag(rs,tag[p]);
		itag[p]=0;
	}
}
void build(int p,int l,int r){
	fmx[p]=tmx[p]=-(1ll<<50);
	if(l==r)return;
	pushdown(p);
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void modify(int p,int lr,int rr,ll x,int l,int r){
	if(lr<=l&&r<=rr){
		pushtag(p,x);
		return;
	}
	if(lr>r||l>rr)return;
	pushdown(p);
	modify(ls,lr,rr,x,l,mid);
	modify(rs,lr,rr,x,mid+1,r);
	update(p);
}
void insert(int p,int x,int l,int r){
	if(l==r){
		fmx[p]=f[x];
		return;
	}
	pushdown(p);
	if(x<=mid)insert(ls,x,l,mid);
	else insert(rs,x,mid+1,r);
	update(p);
}
void process(){
	n=read();
	for(int i=1;i<=n;++i)
		h[i]=read();
	for(int i=1;i<=n;++i)
		b[i]=read();
	build(1,0,n);
   //初始f_0=0
	insert(1,0,0,n);
	for(int i=1;i<=n;++i){
    //用单调栈求前面第一个比它小的位置
		while(st&&h[i]<h[s[st]])--st;
		if(!st)modify(1,0,i-1,b[i],0,n);
		else modify(1,s[st],i-1,b[i],0,n);
		s[++st]=i;
		f[i]=tmx[1];
		insert(1,i,0,n);
	}
	printf("%lld\n",f[n]);
}
int main(){
	int T=1;
	while(T--)process();
	return 0;
}
```

- 单调栈 + multiset

我们也可以用multiset来求最值。那么如何进行区间覆盖呢？

我们令 $sg_i$ 表示当前被 $h_i$ 控制的区间内 $f_i$ 的最大值。当我们在移单调栈的时候，栈顶的 $sg_{top}$ 就会改为被 $h_{i+1}$ 控制，将 $sg_{i+1}$ 与其取最大值即可。再利用multiset进行删除和插入即可完成线段树的操作。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int maxn=601100;
int n,m;
int h[maxn],b[maxn];
long long f[maxn],sg[maxn];
multiset <long long> se;
int s[maxn],st;
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
void process(){
	n=read();
	for(int i=1;i<=n;++i)
		h[i]=read();
	for(int i=1;i<=n;++i)
		b[i]=read();
	s[st=1]=1;
	se.insert(sg[st]+b[s[st]]);
	for(int i=1,p;i<n;++i){
		f[i]=*(--se.end());
		long long psg=f[i];
		while(st&&h[i+1]<h[s[st]]){
			se.erase(se.lower_bound(sg[st]+b[s[st]]));
			if(sg[st]>psg)psg=sg[st];
			--st;
		}
		s[++st]=i+1;
		sg[st]=psg;
		se.insert(psg+b[s[st]]);
	}
	printf("%lld\n",*(--se.end()));
}
int main(){
	int T=1;
	while(T--)process();
	return 0;
}
```


---

## 作者：GGapa (赞：3)

考虑普通的动态规划，定义 $F(i)$ 为 $1 - i$ 的最大值，转移非常显然时间复杂度是 $O(n^2)$ 很显然过不了。考虑使用数据结构优化 DP。

发现会影响转移的一定是比 $h(i)$  要小的元素，考虑使用单调栈维护。

但是这样会产生一个问题，我们在 pop 的时候可能会把一些重要的信息忽略掉，这是不利于转移的，考虑在新开一个数组 $mx(i)$ 记录一下，表示元素 $i$ pop 掉单调栈里面的元素的 $mx$ 的最大值，为啥要这么做呢？

对于样例 2：

```
5
1 4 3 2 5
-3 4 -10 2 7
```

此时的 $F = \{0, -3, 1, -3, 0, 0\}$。

在对 $i = 4$ 进行运算的时候，单调栈内的元素是 $\{1,3\}$ 但是元素 $3$ 曾经将 $2$ pop 过，而此时如果直接用 $F$ 进行转移得到的是 $-3 + 2 = -1$，因为我们忽略掉了 $2$ 所造成的贡献，因此要记录。

代码如下：

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
using LL = long long;
using VI = vector<int>;
const int INF = 1e9;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> h(n + 1), b(n + 1);
    rep(i, 1, n) cin >> h[i];
    rep(i, 1, n) cin >> b[i];
    vector<LL> F(n + 1), mx(n + 1);
    vector<int> stk;
    rep(i, 1, n) {
        LL &t = mx[i] = (stk.empty() ? -INF : F[stk.back()]);
        while(!stk.empty() && h[stk.back()] > h[i]) t = max(t, mx[stk.back()]), stk.pop_back();
        F[i] = max(stk.empty() ? b[i] : F[stk.back()], t + b[i]);
        stk.push_back(i);
    }
    cout << F[n] << '\n';
    return 0;
}
```

---

## 作者：tiger2005 (赞：3)

## 题意：

面前有一排建筑，从左到右每个建筑有一个高度值 $h_i \in [1,n]$ 和一个美丽值 $b_i \in [-10^9,10^9]$。一张照片需要拍下连续的建筑，并且将照片的美丽值定义为最矮的建筑的美丽值。求出正好拍下所有的建筑的照片美丽值之和最大值。

## 解法：

首先可以想到 $O(n^2)\ dp$ 方程：$ans_i=\mathop{\min}\limits_{j<i} ans_j+\operatorname{beauty}(j+1,i)$。考虑优化这个 $dp$ 式子的求法。

我们发现实际上 $\operatorname{beauty}$ 函数的值从右到左，更新的地方只有碰到了一个比之前的高度还要小的建筑。而且每一次更新可以到达的范围会是这个建筑左边第一个比它矮的建筑。我们将 $\operatorname{beauty}$ 的值对应的建筑高度拿出来，可以发现是一个不降数组，而且每次修改都是一个后缀：

```
    _______
    |   # |
    | # # |
    | # # #
  # v # # #
  # # # # #
# # # # # #
1 2 2 5 6 - before
1 2 2 4 4 4 after
```

我们可以很轻松得到上面的结论。

考虑从左到右计算答案。在计算第 $i$ 位的答案 $ans_i$ 的时候，我们假设我们维护好了数组 $B_j$ 表示从 $j+1$ 到 $i-1$ 拍一张照片的美丽值。我们需要获得答案，首先需要将 $B_i$ 进行维护。此时获得这个建筑左边第一个比它矮的建筑地址 $q$，将 $B_{q...i}$ 修改为 $b_i$ 即可。随后根据一开始的 $dp$ 方程，我们可以列出式子：$ans_i=\mathop{\min}\limits_{j<i} ans_j+B_j$，在线段树上维护 $ans_i+B_i$ 的最大值，就可以在 $O(n\log n)$ 的复杂度下解决这个问题。

最后一步考虑如何维护。由于我们在求完 $ans_i$ 之后就不会改变这个值，所以我们可以对 $ans_i$ 的最大值进行维护。在修改的时候，我们在每一个节点下记录 $ans_i+B_i$ 和 $ans_i$ 的最大值，然后将前者变成后者加上需要被覆盖的值（也就是上面的 $b_i$）。

获得一个建筑之前第一个比这个建筑矮的建筑，使用单调栈或者树状数组均可以解决。

我的代码是赛场上写的，其中求解部分稍显复杂，请大家见谅。

```
// Problem      : C. Skyline Photo
// From         : Codeforces - Codeforces Round #709 (Div. 1, based on Technocup 2021 Final Round)
// URL          : https://codeforces.com/contest/1483/problem/C
// Memory Limit : 256 MB
// Time Limit   : 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
int N,A[300010],B[300010];
long long tr[1200010][2];
long long tg[1200010];
const long long INF = -2e17;
void bul(int o,int l,int r){
	tr[o][0]=tr[o][1]=tg[o]=INF;
	if(l==r)	return;
	int m=(l+r)>>1;
	bul(o<<1,l,m);
	bul((o<<1)+1,m+1,r);
}
inline void pd(int o){
	if(tg[o]!=INF){
		tr[o<<1][1]=tr[o<<1][0]+tg[o];
		tr[(o<<1)+1][1]=tr[(o<<1)+1][0]+tg[o];
		tg[o<<1]=tg[(o<<1)+1]=tg[o];
		tg[o]=INF;
	}
}
inline void pu(int o){
	tr[o][0]=max(tr[o<<1][0],tr[(o<<1)+1][0]);
	tr[o][1]=max(tr[o<<1][1],tr[(o<<1)+1][1]);
}
void mdf(int o,int l,int r,int ll,int rr,long long k){
	if(ll>rr)	return;
	if(ll<=l && r<=rr){
		tr[o][1]=tr[o][0]+k;
		tg[o]=k;return;
	}
	pd(o);
	int m=(l+r)>>1;
	if(ll<=m)	mdf(o<<1,l,m,ll,rr,k);
	if(rr>m)	mdf((o<<1)+1,m+1,r,ll,rr,k);
	pu(o);
}
void mdf2(int o,int l,int r,int p,long long k1,long long k2){
	if(l==r){
		tr[o][0]=k1;
		tr[o][1]=k2;
		return;
	}
	pd(o);
	int m=(l+r)>>1;
	if(p<=m)	mdf2(o<<1,l,m,p,k1,k2);
	else mdf2((o<<1)+1,m+1,r,p,k1,k2);
	pu(o);
}
long long que(int o,int l,int r,int ll,int rr,int idx){
	if(ll>rr)	return INF;
	if(ll<=l && r<=rr)	return tr[o][idx];
	int m=(l+r)>>1;long long ret=INF;
	if(ll<=m)	ret=max(ret,que(o<<1,l,m,ll,rr,idx));
	if(rr>m)	ret=max(ret,que((o<<1)+1,m+1,r,ll,rr,idx));
	return ret;
}
long long D[300010];
int trr[300010];
inline int lb(int x){return x & (-x);}
void ad(int a,int x){
	while(a<=N){
		trr[a]=max(trr[a],x);
		a+=lb(a);
	}
}
int qu(int a){
	int ret=0;
	while(a){
		ret=max(ret,trr[a]);
		a-=lb(a);
	}
	return ret;
}
int main(){
	scanf("%d",&N);bul(1,1,N);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=N;i++)
		scanf("%d",&B[i]);
	int p=0;
	for(int i=1;i<=N;i++){
		if(p==0)	p=i;
		else if(A[p]>A[i])	p=i;
		D[i]=p;
	}
	long long curr;
	for(int i=1;i<=N;i++){
		int q=qu(A[i]-1);
		curr=B[D[i]];
		if(q==0){
			curr=max(curr,que(1,1,N,1,i-1,0)+B[i]);
			mdf(1,1,N,1,i-1,B[i]);
		}
		else{
			curr=max(curr,que(1,1,N,1,q-1,1));
			curr=max(curr,que(1,1,N,q,i-1,0)+B[i]);
			mdf(1,1,N,q,i-1,B[i]);
		}
		mdf2(1,1,N,i,curr,curr+B[i+1]);
		ad(A[i],i);
	}
	printf("%lld",curr);
	return 0;
}
```

---

## 作者：zhangyaiwei (赞：2)

## Sol
首先看到这道题，很容易想到一个暴力的dp式子

设 $f_i$ 表示 选到了第 $i$ 栋楼的最优划分

则有 $f_i=\max\limits^{i-1}_{j=0}\left(f_j+b_{\min^{j+1}_{i}a_i}\right)$

这样子做的复杂度是 $\mathcal O(n^3)$ 很明显过不了，就算用 st 表优化掉一个 $n$ 还是过不去

发现这道题的复杂度是可以带一个 $\log$ 的，想一下，带 $\log$ 还可以优化 dp，不就是线段树吗

考虑如果对于 $i$ 我们已经在线段树上维护出了 $f_j+b_{\min^{j+1}_{i}a_i}$（记为 $S_i$） 那我们就只需要用 $\mathcal O(\log n)$ 的复杂度就可以很方便的进行转移，于是考虑如何维护这个数

发现由于我们的 $i$ 是从小到大依次枚举的，所以每次只会有一个数被加入 $b_{\min^{j+1}_{i}a_i}$ 这里。那一个数的影响范围有多大呢？很容易发现就是从上一个小于它的数（位置记为 $lst_i$）后面开始。也就是说每次加入一个 $b_i$ 就是将 $S_{lst_i+1}$ 到 $S_{i-1}$ 的 $b_{\min^{j+1}_{i}a_i}$ 部分变为 $b_i$。而 $lst_i$ 可以用单调栈维护。

可是，如果我们仅在线段树上维护 $S_i$ 的话，上述操作不好进行，所以我们可以把 $S_i$ 拆成 $f_i$ 和 $b_{\min^{j+1}_{i}a_i}$ 两部分存储，`PushUp` 的时候则根据它们的和上传。

然鹅还是有一个问题，如果将 $b_{\min^{j+1}_{i}a_i}$ 部分区间修改后，我们就不知道这一段区间的 $\max S_i$ 是什么了，但是由于整段区间的 $b_{\min^{j+1}_{i}a_i}$ 都被修改成一样的了，所以 $\max S_i$ 应该位于 $\max f_i$ 处，所以我们还要在线段树上记录 $\max f_i$

于是就做完了，复杂度 $\mathcal O(n \log n)$

## Code（码风丑陋）

```cpp
#include<bits/stdc++.h>
#define ls <<1
#define rs <<1|1
#define mid ((l+r)>>1)
#define MID ((L+R)>>1)
#define INF 1145141919810
#define int long long
using namespace std;
struct Xdt{
    int l,r,f,v,mf,t;
}ts[1211111];
void PushUp(int w){
    if(ts[w ls].f+ts[w ls].v>ts[w rs].f+ts[w rs].v){
        ts[w].f=ts[w ls].f;
        ts[w].v=ts[w ls].v;
    }
    else{
        ts[w].f=ts[w rs].f;
        ts[w].v=ts[w rs].v;
    }
    ts[w].mf=max(ts[w ls].mf,ts[w rs].mf);
}
void PushDown(int w){
    if(ts[w].t!=INF){
        ts[w ls].t=ts[w].t;
        ts[w ls].v=ts[w].t;
        ts[w ls].f=ts[w].mf;
        ts[w rs].t=ts[w].t;
        ts[w rs].v=ts[w].t;
        ts[w rs].f=ts[w].mf;
        ts[w].t=INF;
    }
}
void Initt(int l,int r,int w){
    //cout<<"# "<<l<<" "<<r<<endl;
    ts[w].l=l,ts[w].r=r,ts[w].t=INF;
    if(l==r){
        return;
    }
    Initt(l,mid,w ls);
    Initt(mid+1,r,w rs);
    PushUp(w);
}
void Cv(int l,int r,int w,int k){
    int L=ts[w].l,R=ts[w].r;
    if(l<=L&&R<=r){
        ts[w].f=ts[w].mf;
        ts[w].v=k;
        ts[w].t=k;
    }
    else if(l<=R&&L<=r){
        PushDown(w);
        Cv(l,r,w ls,k);
        Cv(l,r,w rs,k);
        PushUp(w);
    }
}
void Cf(int x,int w,int k){
    int L=ts[w].l,R=ts[w].r;
    if(L==R){
        ts[w].f=k;
        ts[w].mf=k;
        return;
    }
    PushDown(w);
    if(x<=MID){
        Cf(x,w ls,k);
    }
    else{
        Cf(x,w rs,k);
    }
    PushUp(w);
}
int Get(int l,int r,int w){
    int L=ts[w].l,R=ts[w].r;
    if(l<=L&&R<=r){
        return ts[w].v+ts[w].f;
    }
    else if(l<=R&&L<=r){
        PushDown(w);
        return max(Get(l,r,w ls),Get(l,r,w rs));
    }
    return -INF;
}
int n,a[311111],b[311111],lst[311111],f[311111];
stack<int> s;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    //单调栈求 lst_i
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]>a[i]){
            s.pop();
        }
        if(!s.empty()) lst[i]=s.top();
        else lst[i]=0;
        s.push(i);
    }
    Initt(0,n,1);
    for(int i=1;i<=n;i++){
        Cv(lst[i],i-1,1,b[i]);
        f[i]=Get(0,i-1,1);
        Cf(i,1,f[i]);
        Cv(i,i,1,b[i+1]);//接下来的b_(min a_i) 部分为 b_{i+1}
    }
    cout<<f[n];
}

```

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1483C)
### 思路分析
自我感觉其他巨佬的 $O(N)$ 写法思路看不懂，~~也许是我太菜了~~，我来分享一下我自己的单调栈优化动归 $O(N)$ 写法。

根据题目易得：在高度 $a_i$ 的位置时，所有的 $a_i<a_j(j<i)$ 都不太有用了，因为如果分段的话，只会采取 $i$ 这个位置的值，所以我们可以通过单调栈维护出前面所有有用的值。

我们可以发现，不太有用并不是没用，若分段分到 $j$ 为止，$j$ 就会造成贡献，所以我们应在 pop 的时候维护出最大能造成的贡献，那么除了这个最大值之外，其余就真的没用了。

但是，如果单调栈没有造成 pop 呢？最大值不就成极小值了吗？那么我们还应该给最后的值与 $dp_{i-1}$ 取个最大值。

我们再想，除了让 $i$ 造成贡献之外，还有没有可能有别的值代替 $i$ 呢？有，那就是分段分到比 $a_i$ 小的数时，那样还得特判取最大值。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5;
int a[N],b[N],dp[N],n,mi[N],v[N],s[N],top=0,l[N];            
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	l[0]=-1145141919810;
	for(int i=1;i<=n;i++){
		int maxi=-1145141919810;
		while(top>=1&&a[s[top]]>a[i]){
			maxi=max(maxi,v[top--]);//可能有用的信息
		}
		maxi=max(maxi,dp[i-1]);//别取成极小值了！！！
		v[++top]=maxi;
		s[top]=i;//入栈
        dp[i]=l[top-1];//当前段最小值取到i之前
		dp[i]=max(dp[i],maxi+b[i]);//当前段最小值是i
		l[top]=dp[i];
	}
	cout<<dp[n];
	return 0;
}  

```

---

## 作者：lsj2009 (赞：1)

### Solution

无脑的线段树优化 dp 做法。

考虑设 $f_i$ 为前 $i$ 个数的最小代价。

我们考虑钦定某个数成为这一段区间中的最小值，则我们用单调栈找出他能成为区间最小值的最远左端点 $l_i$ 和最远右端点 $r_i$，如果说此时 $l_i-1\sim i-1$ 的答案我们已经算好，显然对于 $f_{l_i-1\sim i-1}$ 的任意一个值加上 $b_i$ 都可以转移到 $f_{i\sim r_i}$。

直接暴力做是 $\Theta(n^2)$ 的，我们维护一棵支持区间取 $\max$、区间查 $\max$ 的线段树可以做到 $\Theta(n\log{n})$。


### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=3e5+5;
struct SGT {
    struct node {
        int l,r,val,tag;
    }; node tree[N<<2];
    #define ls(k) (k<<1)
    #define rs(k) (k<<1|1)
    void push_up(int k) {
        tree[k].val=max(tree[ls(k)].val,tree[rs(k)].val);
    }
    void upd(int k,int val) {
        chkmax(tree[k].val,val); 
        chkmax(tree[k].tag,val);
    }
    void push_down(int k) {
        int &t=tree[k].tag;
        if(t!=-INFLL) {
            upd(ls(k),t);
            upd(rs(k),t);
            t=-INFLL;            
        }
    }
    void build(int k,int l,int r) {
        tree[k]={l,r,-INFLL,-INFLL};
        if(l==r)
            return;
        int mid=(l+r)>>1;
        build(ls(k),l,mid);
        build(rs(k),mid+1,r);
        push_up(k);
    }
    void update(int k,int ql,int qr,int val) {
        if(ql<=tree[k].l&&tree[k].r<=qr) {
            upd(k,val);
            return;
        }
        push_down(k);
        if(ql<=tree[ls(k)].r)
            update(ls(k),ql,qr,val);
        if(qr>=tree[rs(k)].l)
            update(rs(k),ql,qr,val);
        push_up(k);
    }
    int query(int k,int ql,int qr) {
        if(ql<=tree[k].l&&tree[k].r<=qr)
            return tree[k].val;
        push_down(k);
        int res=-INFLL;
        if(ql<=tree[ls(k)].r)
            chkmax(res,query(ls(k),ql,qr));
        if(qr>=tree[rs(k)].l)
            chkmax(res,query(rs(k),ql,qr));
        return res;
    }
}; SGT T;
int a[N],b[N],l[N],r[N];
signed main() {
    int n;
    scanf("%lld",&n);
    rep(i,1,n)
        scanf("%lld",&a[i]);
    rep(i,1,n)
        scanf("%lld",&b[i]);
    stack<int> s;
    rep(i,1,n) {
        while(!s.empty()&&a[s.top()]>a[i])
            s.pop();
        l[i]=s.empty()? 0:s.top();
        s.push(i);
    }
    while(!s.empty())
        s.pop();
    per(i,n,1) {
        while(!s.empty()&&a[s.top()]>a[i])
            s.pop();
        r[i]=s.empty()? n:s.top()-1;
        s.push(i);
    }
    T.build(1,0,n);
    T.update(1,0,0,0);
    rep(i,1,n) {
        int val=T.query(1,l[i],i-1);
        T.update(1,i,r[i],val+b[i]);
    }
    printf("%lld\n",T.query(1,n,n));
    return 0;
}

```

---

## 作者：NuoCarter (赞：1)

### 线段树 $O(n \log n)$ 解法

如果我们设 $f_i$ 表示将前 $i$ 个楼房分成若干段的最大价值：

首先有一个很显然的暴力 $O(n^2)$ 转移：

$f_i=\max\bigg(f_{j(j<i)}+min\big(b_{k(k\in[j+1,i])} \big) \bigg )$

这个转移实质上是在枚举最后一段的左端点。

但是经过几次模拟整个转移的过程，

会发现这个转移的关键其实是 $min(b_{k(k\in[j,i-1])})$ 。所以考虑用一个单调栈 ($sta_i$) 维护

将 $i$ 的左边第一个比它小的数，记为 $l_i$，它右边第一个比它小的 $b_j$ 下标记为 $r_i$

对于一个位置 $j$，显然：在转移的过程中： $[l_j,j-1]$ 中的 $min$ 都是 $b_j$，而在 $[j,r_i-1]$ 中的转移的 $min$ 也是 $b_j$。

那么我们考虑用一个线段树来维护区间 $f_{j(j<i)}+min\big(b_{k(k\in[j+1,i])} \big)$ 的最大值。

如果当前单调栈的大小为 $top$ , 那么 $l_i$ 就是将所有不满足的元素弹出后的 $sta_{top}$ ，而 $r_i$ 就是它被弹出栈时的下标。

在线段树维护时，同时维护单调栈（注意单调栈中维护的是下标）：

下面用 $t$ 表示当前栈顶的下标：

入栈时：我们将 $[l_i,i-1]$ 区间加上 $b_i$。出栈时：将区间 $[l_{t},r_{t}-1]$ 减去 $b_t$。

那么 $f_i=Query(0,i)$

注意当转移的 $j$ 为 $0$ 时就是将整个划分为 $1$ 段，所以查找最大值的起点为 $0$ 而不是 $1$。

最后在更新完 $f_i$ 后单点赋值更新线段树就可以了。

参考 [Priori_Incantatem大佬的题解](https://blog.csdn.net/Brian_Pan_/article/details/115065320?spm=1001.2014.3001.5501)

Code（附赠豪华调试版）:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc x<<1
#define rc x<<1|1
const int N=3e5+3,INF=1e15;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void print(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10^48);
}
int a[N],b[N],n;
struct node{
    int l,r,maxn,lazy;
    #define lazy(x) c[x].lazy
    #define l(x)    c[x].l
    #define r(x)    c[x].r
    #define maxn(x) c[x].maxn
}c[N<<2];
int lim[N],dp[N];
inline void Push_up(int x){maxn(x)=max(maxn(lc),maxn(rc));return;}
inline void Change(int x,int d){maxn(x)+=d,lazy(x)+=d;return;}
inline void Push_down(int x){if(lazy(x)){Change(lc,lazy(x)),Change(rc,lazy(x));lazy(x)=0;}return;}
inline void Build(int x,int l,int r){
    l(x)=l,r(x)=r;
    if(l==r){maxn(x)=0;return;}
    int mid=(l+r)>>1;
    Build(lc,l,mid);
    Build(rc,mid+1,r);
}
inline void Modify(int x,int L,int d){
    if(l(x)==r(x)){maxn(x)=d;return;}
    Push_down(x);
    int mid=(l(x)+r(x))>>1;
    if(mid>=L)  Modify(lc,L,d);
    else Modify(rc,L,d);
    Push_up(x);return;
}
inline int Query(int x,int L,int R){
    if(l(x)>=L&&r(x)<=R){return maxn(x);}
    Push_down(x);
    int mid=(l(x)+r(x))>>1,res=-INF;
    if(mid>=L) res=max(res,Query(lc,L,R));
    if(mid<R)  res=max(res,Query(rc,L,R));
    return res;
}
inline void Add(int x,int L,int R,int d){
    if(l(x)>=L&&r(x)<=R){Change(x,d);return;}
    Push_down(x);
    int mid=(l(x)+r(x))>>1;
    if(mid>=L)  Add(lc,L,R,d);
    if(mid<R)   Add(rc,L,R,d);
    Push_up(x);
    return;
}
int sta[N];
signed main(){
    read(n);
    for(register int i=1;i<=n;++i)    read(a[i]);
    for(register int i=1;i<=n;++i)    read(b[i]);
    Build(1,0,n);
    // for(register int i=1;i<=n;++i){
    //     cout<<lim[i]<<" ";
    // }
    int top=1;
    // puts("???");
    for(register int i=1;i<=n;++i){
        while(top&&a[sta[top]]>=a[i]){
            // cout<<sta[top-1]<<" "<<sta[top]-1<<"\n";
            Add(1,sta[top-1],sta[top]-1,-b[sta[top]]);
            top--;
        }
        Add(1,sta[top],i-1,b[i]);
        dp[i]=Query(1,0,i-1);
        Modify(1,i,dp[i]);
        sta[++top]=i;
    }
    // for(register int i=1;i<=n;++i) printf("%3d ",a[i]);
    // puts("");
    // for(register int i=1;i<=n;++i)  printf("%3d ",b[i]);
    // puts("");
    // for(register int i=1;i<=n;++)  printf("%3d ",dp[i]);
    // puts("");
    print(dp[n]);
    return 0;
}

```

---

## 作者：elbissoPtImaerD (赞：0)

先考虑暴力 dp：设 $f_i$ 表示已经划分了 $i$ 前缀的楼房的最大得分。

转移自然有 $f_i = \max\limits_{j \in [1,i)}\{f_j + w(j+1,i)\}$，其中 $w(l,r)$ 表示 $[l,r]$ 中 $a$ 最小值的对应的下标的 $b$ 值。

如何优化？考虑到，求解 $f_i$ 时，很多 $w$ 都是相同的。  
对于这些相同的 $w$ 只需求解最大的 $f$ 即可，我们可以利用单调栈的结构快速求解。

具体地，我们维护一个递增的单调栈 $S$，栈中第 $i$ 个元素存储的区间是 $[S_{i-1},S_i)$。特别地，$S_0=0$。

对于栈中每个元素 $S_i$（将其对应的区间简记为 $[l,r)$） 我们还需维护 $mx_i = \max \limits_{j\in[l,r)} f_j$ 和 $g_i = \max(\max\limits_{j\in[l,r)}\{f_j\}+b_{S_i},g_{i-1})$。

那么我们只需从 $1$ 扫到 $n$，维护对应的单调栈和信息即可 $\mathcal{O(1)}$ 转移，总复杂度 $\mathcal{O(n)}$。

细节看代码。

```cpp
const int N=3e5+3;
int n,a[N],b[N],S[N],*p_S=S;
LL f[N],g[N],mx[N];
il void Solve()
{
  rd(n);
  for(int i=1;i<=n;++i) rd(a[i]);
  for(int i=1;i<=n;++i) rd(b[i]);
  g[0]=LONG_LONG_MIN;
  for(int i=1;i<=n;++i)
  {
    LL mxn=f[*p_S];
    for(;p_S-S&&a[*p_S]>=a[i];--p_S) cx(mxn,mx[p_S-S]);
    *++p_S=i,mx[p_S-S]=sd max(mxn,f[*(p_S-1)]),f[i]=g[p_S-S]=sd max(g[p_S-S-1],b[i]+mx[p_S-S]);
  }
  wrt(f[n]);
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1483/submission/230828838)。

---

## 作者：Hisaishi_Kanade (赞：0)

随机跳 div.2 E 看到的，感觉没有 $2100$ 吧。

首先，由于没有段数限制，显然的想到设 $f(i)$ 表示 $[1,i]$ 划分成若干段之后得到的最大美丽值之和。显然有转移 $f(i)=\max\{f(j)+\omega(j+1,i)\}$，$\omega(j+1,i)$ 表示区间 $(j+1,i]$ 的“”最矮的楼房的美丽值”。

我们直接找到最靠近的左侧的 $j$ 使得 $a_j<a_i$。

因为区间 $(j,i]$ 中，$a$ 都不比 $a_i$ 小，则对于 $j< k\le i$，$w(k,i)=b_i$。而对于 $1\le k\le j$，$\omega(k,i)=\omega (k,i-1)$，因为 $a_{i-1}>a_i>a_j$，所以这些玩意完全就相当于 $\omega(k,j)$。

找 $j$ 的过程可以使用单调栈来维护，但是如何维护最开始那个 $\max$ 呢？

我们如果能维护好 $f(k)+\omega(k+1,i)$ 即可。依据上面的我们只需要修改一下 $\omega$。我们发现一个性质是对于栈内相邻的 $q_x,q_{x+1}$，目前 $[q_x,q_{x+1})$ 的 $\omega$ 都是 $b_{q_x}$。根据这个性质，我们先减掉 $b_{q_x}$，然后加上 $b_i$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define mid (l+r>>1)
using namespace std;
const int N=3e5+5, inf=-(1<<30);
int n, l, r, i;
int tr[N<<2], tag[N<<2];
inline void push_up(int id) {tr[id]=max(tr[lc(id)], tr[rc(id)]); return ;}
inline void push_down(int id)
{
	tr[lc(id)]+=tag[id]; tr[rc(id)]+=tag[id];
	tag[lc(id)]+=tag[id]; tag[rc(id)]+=tag[id];
	tag[id]=0;
	return ;
}
inline void build(int id, int l, int r)
{
	tr[id]=inf;
	if(l==r) return ;
	build(lc(id), l, mid);
	build(rc(id), mid+1, r);
	return ;
}
inline void upd(int id, int ql, int qr, int l, int r, int k)
{
	if(r<ql || qr<l) return ;
	if(ql<=l && r<=qr)
	{
		tr[id]+=k; tag[id]=k;
		return ;
	}
	push_down(id);
	upd(lc(id), ql, qr, l, mid, k);
	upd(rc(id), ql, qr, mid+1, r, k);
	push_up(id);
	return ;
}
inline int query(int id, int ql, int qr, int l, int r)
{
	if(r<ql || qr<l) return inf;
	if(ql<=l && r<=qr) return tr[id];
	push_down(id);
	int ret=max(query(lc(id), ql, qr, l, mid), query(rc(id), ql, qr, mid+1, r)); push_up(id);
	return ret;
}
int a[N], b[N], f[N];
signed main()
{
	scanf("%d", &n); rep(i, 1, n) scanf("%lld", a+i); rep(i, 1, n) scanf("%lld", b+i);//这一行全是读入
	stack <pair<int,int>> q; q.push({inf, 0});
	rep(i, 1, n)
	{
		upd(1, i, i, 1, n, b[i]);//无论如何，w(i, i)=b[i]
		while(!q.empty() && q.top().first>a[i])
		{
			r=q.top().second; q.pop(); l=q.top().second+1;
			upd(1, l, r, 1, n, -b[r]);
			upd(1, l, r, 1, n, b[i]);
		}//向前找，每次将一个区间的 w 更新。
		q.push({a[i], i});//加入栈
		f[i+1]=query(1, 1, i, 1, n); upd(1, i+1, i+1, 1, n, f[i+1]);//进行转移。
	}
	printf("%lld\n", f[n+1]);// n 也要划分进去所以 dp 到 n+1。
	return 0;
}
```

---

## 作者：GaryH (赞：0)

# CF1483C 题解

一.题意简述

给一个序列 $a$，要求将序列分成若干段，并最大化每一段最小值的和。

首先，我们可以写出一个暴力的DP方程：

设 $f_i$ 表示将前 $i$ 个数分成若干段，最后一段的结尾元素是 $a_i$ 的答案。

那么我们有一个转移方程，是：

$f_i = max_{j \in [1,i - 1]}(f_j+min_{k \in [j + 1, i]}(a_k))$ .

我们发现，这样算是 $O(n^3)$ 的，

加上一个静态查询区间最大值的数据结构也是 $O(n^2)$ 的。

那么，我们考虑优化这个转移。

我们考虑，上面转移式中的 $min_{k \in [j + 1, i]}(a_k)$ 在什么地方取到。

我们对每一个 $i$，维护一个单调递增的序列 $b$，

这个序列是序列 $a$ 中前 $i$ 个数的子序列，

且在序列 $b$ 中任意一个不为结尾的位置 $j$ ，都有：

$b_{j}$ 是在序列 $a$ 中第一个小于 $b_{j+1}$ 的元素。

当然，序列 $b$ 的最后一个元素必须是 $a_i$.

实际上，这个序列 $b$ 就是以序列 $a$ 的前 $i$ 个元素建立的单调栈。

那么，我们可以发现，$min_{k \in [j + 1, i]}(a_k)$ 的值就只能在序列 $b$ 中出现，且：

对于某个 $b$ 中的两个相邻元素 $b_x,b_{x+1}$，

我们找到它们在序列 $a$ 中的下标 $p_x,p_{x+1}$，那么：

 $\forall j \in [p_x + 1,p_{x+1}]$，$min_{k \in [j + 1, i]}(a_k) = b_{x + 1}$.

那么，我们定义： $w_i(j) = min_{k \in [j + 1, i]}(a_k)$，我们就可以发现：

对于每个 $i$，我们将原序列 $a[1...i]$ 分成了若干段小区间，

其中每一段小区间的 $w_i$ 值都等于这段小区间的末尾元素。

为了方便下文叙述，我们说这个末尾元素与这段小区间相互对应。

当然，将这些小区间对应的末尾元素抽出来，就可以组成序列 $b$.

这又有什么用呢？

我们发现，我们只需要动态的维护这个序列 $b$ 中 $f_j + w_i(j)$ 的最大值，即：

我们用线段树维护，当考虑到第 $i$ 个数时，线段树上第 $j$ 个位置的值为 $f_j + w_i(j)$ ，

那么我们考虑在前 $i - 1$ 个数对应的线段树上进行一些修改。

我们可以先维护序列 $b$：

把前 $i - 1$ 个数对应的序列 $b$ 的最后若干个大于 $a_i$ 的数删掉，

再把 $a_i$ 加进 $b$ 的末尾。

我们注意到，删掉的所有数对应的小区间，

在线段树上的 $f$ 值不会改变，但 $w_i$ 值会一起改变。

所以我们就可以轻松的维护线段树了：

每从 $b$ 中删掉一个元素 $x$，我们就把线段树上的这个区间整体加上 $a_i - x$，

最后在 $b$ 中放入 $a_i$ 时，

我们在线段树上查询区间 $[1,i - 1]$ 的最大值，作为 $f_i$ 的值。

最后，我们再将 $f_i + a_i$ 插到线段树上的第 $i$ 个位置即可。

因为序列 $b$ 总共只会放入 $n$ 个数，故也最多删除 $n$ 次，那么总复杂度也就是 $O(nlogn)$.

---

