# [ABC293G] Triple Index

## 题目描述

给定一个长度为 $N$ 的正整数序列 $(A_1,\ A_2,\ \ldots,\ A_N)$，以及关于该序列的 $Q$ 个查询。

对于每个 $q = 1, 2, \ldots, Q$，第 $q$ 个查询给出一对整数 $(l_q,\ r_q)$，请输出满足以下两个条件的整数三元组 $(i,\ j,\ k)$ 的个数：

- $l_q \leq i < j < k \leq r_q$
- $A_i = A_j = A_k$

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq A_i \leq 2 \times 10^5$
- $1 \leq l_q \leq r_q \leq N$
- 所有输入均为整数

## 样例解释 1

对于第 $1$ 个查询，满足题目中两个条件的三元组 $(i,\ j,\ k)$ 有 $(1, 5, 9),\ (4, 6, 8),\ (4, 6, 10),\ (4, 8, 10),\ (6, 8, 10)$ 共 $5$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10 4
2 7 1 8 2 8 1 8 2 8
1 10
1 9
2 10
5 5```

### 输出

```
5
2
4
0```

## 样例 #2

### 输入

```
20 10
2 2 2 2 1 1 2 2 1 1 1 2 1 2 1 2 2 1 2 1
12 16
17 18
12 18
4 9
13 13
2 5
6 13
2 14
7 14
8 12```

### 输出

```
1
0
5
2
0
1
11
55
8
1```

# 题解

## 作者：Light_az (赞：7)

## 莫队模板题

题目问我们能在 $[l,r]$ 区间内选出多少组 $3$ 个数 $a_i,a_j,a_k$ 使 $a_i=a_j=a_k$ 并且 $l< j< k$，观察数据范围我们采用莫队算法来解决此问题。

我们先使用桶数组记录目前区间每个数出现个数，然后考虑影响：如果 $x$ 出现次数大于等于 $3$，那么它对答案的影响是 $\frac{(x-1)  (x-2) }{2} $，因为我们优先固定 $a_k$ 的位置，然后选择 $a_j$，发现有 $x-1$ 种方案，再次选择 $a_i$，发现有 $x-2$ 种方案，但是由于 $i <j$ 的限制，因此总方案数要减少一半，最后套上莫队模板即可通过此题。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define B(i,j,n) for(int i=j;i>=n;i--)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,ans=0,t=0,l,r,len,T;
ll mn=INT_MAX,mx=0,Mod,id=1;
string s1,s2;
ll a[N],cnt[N],num[N];
struct Node{
	ll l,r,id;
}b[N];
bool cmp(Node a,Node b){
	if((a.l-1)/len==(b.l-1)/len) return a.r<b.r;
	return a.l/len<b.l/len;
}
void add(ll id){
	cnt[a[id]]++;
	if(cnt[a[id]]>=3) ans+=(cnt[a[id]]-1)*(cnt[a[id]]-2)/2;//增加答案贡献
}
void del(ll id){
	if(cnt[a[id]]>=3) ans-=(cnt[a[id]]-1)*(cnt[a[id]]-2)/2;//减少贡献
	cnt[a[id]]--;
}
int main(){
	cin>>n>>m;
	len=sqrt(n);
	F(i,1,n) cin>>a[i];
	F(i,1,m){
		cin>>b[i].l>>b[i].r;
		b[i].id=i;
	} 
	sort(b+1,b+1+m,cmp);//莫队排序
	l=1,r=0;
	F(i,1,m){
		while(r<b[i].r) add(++r);
		while(r>b[i].r) del(r--);
		while(l<b[i].l) del(l++);
		while(l>b[i].l) add(--l);
		num[b[i].id]=ans;//记录答案
	}
	F(i,1,m) cout<<num[i]<<"\n";
	return 0;
}

```


---

## 作者：FFTotoro (赞：4)

本题需要使用**莫队**思想。

考虑加入一个数会对答案造成什么影响：

记 $x$ 在目前扫描的区间中出现了 $c_x$ 次，再加入一个 $x$，因为可以从原来的 $c_x$（这里 $c_x$ 指还未加入新的 $x$ 时的 $x$ 的数量）中选择 $2$ 个和 $x$ 组成一个三元组，所以能形成的三元组数量应该增加 $\dfrac{c_x(c_x-1)}{2}$，而后 $c_x\leftarrow c_x+1$。删除也是类似的思想。

然后就是莫队板子了，先把所有询问离线下来，可以使用奇偶性排序优化。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef tuple<int,int,int> tpi;
int t,c[200001];
void add(int p){
  if(++c[p]==3)t++;
  if(c[p]==4)t+=3;
  if(c[p]>4)t+=(c[p]-1)*(c[p]-2)>>1;
} // 加入一个数
void del(int p){
  if(--c[p]==2)t--;
  if(c[p]==3)t-=3;
  if(c[p]>3)t-=c[p]*(c[p]-1)>>1;
} // 删除一个数
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,q,L=0,R=-1,sq; cin>>n>>q; sq=sqrt(n);
  vector<int> a(n),s(q);
  vector<tpi> w(q);
  for(auto &i:a)cin>>i;
  for(int i=0;i<q;i++)
    cin>>get<0>(w[i])>>get<1>(w[i]),get<2>(w[i])=i;
  sort(w.begin(),w.end(),[&](tpi x,tpi y){
    if(get<0>(x)/sq!=get<0>(y)/sq)return get<0>(x)<get<0>(y);
    return get<0>(x)/sq&1?get<1>(x)<get<1>(y):get<1>(x)>get<1>(y);
    }); // 奇偶性排序
  for(auto &[l,r,x]:w){
    l--,r--;
    while(L<l)del(a[L++]);
    while(L>l)add(a[--L]);
    while(R<r)add(a[++R]);
    while(R>r)del(a[R--]);
    s[x]=t;
  } // L 和 R 扫描
  for(int i:s)cout<<i<<endl;
  return 0;
}
```

---

## 作者：DengDuck (赞：3)

最近在学习莫队，感觉这道题和 SPOJ DQUERY 比小 Z 的袜子更适合作模板题。

首先简单分析问题，貌似并没有可加性，所以分块和线段树肯定寄了。

但是本题中相邻区间转移是 $O(1)$：

- 对于增加元素，设原有此元素 $n$ 个，则增加三元组 $\dfrac 1 2n(n-1)$ 个。
- 对于删除元素，设减去该元素后有此元素 $n$ 个，则减少三元组 $\dfrac 1 2n(n-1)$ 个。

于是用莫队就可以在 $O(n\sqrt n)$ 的时间复杂度解决了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
struct node
{
	LL l,r,id;
}b[N];
LL n,q,B,a[N],cnt[N],ans[N],sum;
bool cmp(node x,node y)
{
	if(x.l/B==y.l/B)
	{
		if((x.l/B)&1)return x.r<y.r;
		return x.r>y.r;
	}
	return x.l/B<y.l/B;
}
void del(LL x)
{
	cnt[a[x]]--;
	sum-=cnt[a[x]]*(cnt[a[x]]-1)/2;
}
void ins(LL x)
{
	sum+=cnt[a[x]]*(cnt[a[x]]-1)/2;
	cnt[a[x]]++;
}
int main()
{
	scanf("%lld%lld",&n,&q);
	B=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld",&b[i].l,&b[i].r);
		b[i].id=i;
	}
	sort(b+1,b+q+1,cmp);
	LL l=1,r=0,sl,sr;
	for(int i=1;i<=q;i++)
	{
		sl=b[i].l,sr=b[i].r;
		while(l<sl)del(l++);
		while(sl<l)ins(--l);
		while(r<sr)ins(++r);
		while(sr<r)del(r--);
		ans[b[i].id]=sum;
	}
	for(int i=1;i<=q;i++)
	{
		printf("%lld\n",ans[i]);
	}
}
```

---

## 作者：qzhwlzy (赞：2)

## 题目大意

给定一个长度为 $n$ 的序列 $a$，现要回答 $Q$ 组询问，每次询问如下：给定 $l,r$，求满足 $l\le i<j<k\le r$ 且 $a_i = a_j = a_k$ 的有序数对 $(i,j,k)$ 的对数。

## 思路

注意到 $Q$ 组询问都是区间查询，且可以离线处理，于是不难想到用莫队处理。转移时，用一个桶 $b$ 维护区间 $[l,r]$ 中每个数出现的个数，假设 $r+1$ 要加入区间，那么带来的贡献就是 $C_{b_{a[r+1]}}^2$，于是可以 $\mathcal{O}(1)$ 转移。

总时间复杂度 $\mathcal{O}(n\sqrt n)$，~~数据比较水~~。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define maxn 200005
#define ll long long
using namespace std;
int n,T,len,a[maxn],b[maxn],l,r; struct ques{int l,r,id; ll ans;}q[maxn]; ll res;
bool cmp(ques aa,ques bb){if((aa.l-1)/len==(bb.l-1)/len) return aa.r<bb.r; return aa.l<bb.l;}
bool cmp2(ques aa,ques bb){return aa.id<bb.id;}
int main(){
	scanf("%d%d",&n,&T); len=sqrt(n); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=T;i++){scanf("%d%d",&q[i].l,&q[i].r); q[i].id=i;} sort(q+1,q+1+T,cmp);
	for(int i=1;i<=T;i++){
		while(l>q[i].l){b[a[--l]]++; res+=(b[a[l]]>2)*(1LL*(b[a[l]]-1)*(b[a[l]]-2)/2);}
		while(r<q[i].r){b[a[++r]]++; res+=(b[a[r]]>2)*(1LL*(b[a[r]]-1)*(b[a[r]]-2)/2);}
		while(l<q[i].l){res-=(b[a[l]]>2)*(1LL*(b[a[l]]-1)*(b[a[l]]-2)/2); b[a[l++]]--;}
		while(r>q[i].r){res-=(b[a[r]]>2)*(1LL*(b[a[r]]-1)*(b[a[r]]-2)/2); b[a[r--]]--;}
		q[i].ans=res;
	} sort(q+1,q+1+T,cmp2); for(int i=1;i<=T;i++) printf("%lld\n",q[i].ans); return 0;
}

```

---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc293_g)。

## 思路

莫队板题。

我们令 $cnt_i$ 表示在当前询问区间数 $i$ 出现的次数，假设存在一个数 $g$ 在当前询问区间中出现过，那么它对当前询问答案的贡献为 $\dbinom{cnt_g}{3}$，当然我们不能扫一遍区间在统计，考虑当前数字对答案的影响。

- 对于增加元素 $g$，答案将增加 $\dbinom{cnt_g+1}{3}\dbinom{cnt_g}{3}$。

- 对于减少元素 $g$，答案将减少 $\dbinom{cnt_g}{3}-\dbinom{cnt_g-1}{3}$。


可以得到 $\mathcal{O}(1)$ 转移。

## 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=2e5+7;
ll N,Q,a[Maxn],ans[Maxn],res,cnt[Maxn],sq;
ll fac[Maxn],inv[Maxn];
struct ques{
	ll l,r,id;
}q[Maxn];
inline ll C(ll x){
	if(x<3) return 0;
	return (x-2)*(x-1)*x/6;
}
inline void add(ll x){
	res=res-C(cnt[a[x]])+C(cnt[a[x]]+1);
	cnt[a[x]]++;
}
inline void del(ll x){
	res=res-C(cnt[a[x]])+C(cnt[a[x]]-1);
	cnt[a[x]]--;
}
inline bool cmp(ques A,ques B){
	return (A.l/sq==B.l/sq?A.r<B.r:A.l<B.l);
}
int main(){
	scanf("%lld%lld",&N,&Q);
	sq=sqrt(N);
	for(ll i=1;i<=N;i++) scanf("%lld",&a[i]);
	for(ll i=1,l,r;i<=Q;i++) scanf("%lld%lld",&l,&r),q[i].l=l,q[i].r=r,q[i].id=i;
	sort(q+1,q+Q+1,cmp);
	ll l=1,r=0;
	for(ll i=1;i<=Q;i++){
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		ans[q[i].id]=res;
	}
	for(ll i=1;i<=Q;i++) printf("%lld\n",ans[i]);
	return 0;
}

```


---

## 作者：Neil_Qian (赞：1)

# [ABC293G] Triple Index 题解

给定 $n$ 个数，有一些询问，询问区间 $[l,r]$ 有多少个值相同无序的三元组。可以离线。

注意到题目可以离线，并且根据每个数的个数就可以计算答案，可以考虑莫队。

我们考虑一下莫队转移即可（其它模板可参见小Z的袜子），而且不带修。设 $i$ 出现了 $cnt_i$ 次。从 $[L,R]$ 转移到 $[L-1,R]$，对于新增的一个 $a_{L-1}$，可以和任意两个和它值相同的组成三元组，因此答案加上 $cnt_{a_{L-1}}\times (cnt_{a_{L-1}}-1)\times \frac{1}{2}$。其它同理。

时间复杂度同莫队， $O(n\times \sqrt{n})$，可能需要略微卡常即可通过。

顺便延申一句，如果 $a_i\le 10^9$，可以用映射，但更好的方法是离散化，时间复杂度还是 $O(n\times \sqrt{n})$。

代码（有一点卡常）：

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const ll N=4e5+2;
ll h,n,q,S,a[N],cnt[N],L=1,R,ans,p[N],pt[18],sz;char c;//变量
struct Node{
	ll l,r,id,w;
	bool operator <(const Node& b){//比cmp函数快
		if(w!=b.w)return w<b.w;
		else return ((w&1)?r<b.r:r>b.r);
	}
}x[N];
inline ll calc(const ll x){return (x>=2?((x*(x-1))>>1):0);}//计算和其它相同元素的值
inline ll read(){//快读快写
	h=0,c=getchar();
	while(!(c>='0'&&c<='9'))c=getchar();
	while(c>='0'&&c<='9')h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h;
}
inline void write(ll x){
	if(x==0){putchar('0');return;}
	sz=0;
	while(x)pt[++sz]=x%10,x/=10;
	for(register int i=sz;i>=1;i--)putchar(pt[i]^48);
}
int main(){
	n=read(),q=read(),S=sqrt(n);
	for(register int i=1;i<=n;i++)a[i]=read();
   //莫队计算权值
	for(register int i=1;i<=q;i++)x[i].l=read(),x[i].r=read(),
		x[i].id=i,x[i].w=(x[i].l-1)/S+1;
	sort(x+1,x+q+1);//排序
	for(register int i=1;i<=q;i++){//回答问题
     //莫队统计新增/减少答案，注意顺序
		while(L>x[i].l)ans+=calc(cnt[a[--L]]),++cnt[a[L]];
		while(R<x[i].r)ans+=calc(cnt[a[++R]]),++cnt[a[R]];
		while(L<x[i].l)--cnt[a[L]],ans-=calc(cnt[a[L++]]);
		while(R>x[i].r)--cnt[a[R]],ans-=calc(cnt[a[R--]]);
		p[x[i].id]=ans;//记录
	}
	for(register int i=1;i<=q;i++)write(p[i]),putchar('\n');//输出
	return 0;
}
```

---

## 作者：ケロシ (赞：1)

## 解题思路

首先观察此题的特点，这道题只有区间查询操作，而且给定的 $n$ 和 $V$ 都在 $2 \times 10^5$ 以内，不难想到用莫队 $O(n\sqrt{n})$ 求解。

随后来写莫队两核心函数：add 和 del。

以 add 函数为例，每次需统计当前的块中每个数出现的次数，其中 $i$ 出现次数为 $s_i$，   
那么如果新增的数字是 $x$，根据题意，答案就要加上旧区间里两数都为 $x$ 的二元组的个数，就等于 $\frac{s_x(s_x-1)}{2}$，并更新 $s_x$，时间复杂度 $O(n\sqrt{n})$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 2e5+5;
int n,q,a[N],s[N];
int maxn;
ll g[N];
struct node{
    int l,r,n;
}f[N];
bool cmp(node x,node y) {
    if(x.l/maxn == y.l/maxn) return x.r < y.r;
    return x.l/maxn < y.l/maxn;
}
ll ans;
int l,r;
void add(int u) {
    ll res = s[a[u]];
    ans += res * (res - 1) / 2;
    s[a[u]]++;
}
void del(int u){
    ll res = s[a[u]] - 1;
    ans -= res * (res - 1) / 2;
    s[a[u]]--;
}
void solve() {
    cin >> n >> q;
    maxn = sqrt(n);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=q;i++){
        cin >> f[i].l >> f[i].r;
        f[i].n = i;
    }
    sort(f + 1,f + 1 + q, cmp);
    l = 1, r = 0;
    for(int i=1;i<=q;i++) {
        int pl = f[i].l;
        int pr = f[i].r;
        while (l > pl) add(--l);
        while (r < pr) add(++r);
            while (l < pl) del(l++);
        while (r > pr) del(r--);
        g[f[i].n] = ans;
    }
    for(int i=1;i<=q;i++) cout << g[i] << endl;
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```



---

## 作者：Nephren_Sakura (赞：1)

板子题。

闲话：比赛结束前 10min 看到了这题，比赛结束前 15s 切掉了。

首先，看到这种没有修改的问题，而且还允许离线，并且题目给的东西好像不太好维护的样子，就可以先尝试一下莫队。

莫队维护一个 $sum_i$ 表示当前区间内值为 $i$ 的数的出现次数。

那么每次左右端点拓展的时候更新 $sum_i$ 同时更新答案。

现在考虑如何更新答案，设答案为 $ans$：

显然，对于每一个 $i$，它对答案的贡献为 $C_{sum_i}^{3}$，即 $\frac{sum_i \times (sum_i-1) \times (sum_i-2)}{6}$。

那么每一次更改 $sum_i$ 的时候先减去它对答案的贡献，然后改完再加上更改后的它对答案的贡献即可。

下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,a[1000005],sum[1000005],ans,pt[1000005];
struct node{
	int lt,rt,id,zuo,you,kuai;
}qu[1000005];
bool cmp(node x,node y){
	if(x.kuai!=y.kuai)
	    return x.kuai<y.kuai;
	return x.rt<y.rt;
}//莫队排序
int qr(int x){
	return sum[a[x]]*(sum[a[x]]-1)*(sum[a[x]]-2)/6;
}//序列中第 x 个数对答案的贡献，注意我的代码里写的是第 x 个数
void add(int x){
	ans-=qr(x);
	sum[a[x]]++;
	ans+=qr(x);
}//加入
void delet(int x){
	ans-=qr(x);
	sum[a[x]]--;
	ans+=qr(x);
	return;
}//删除
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	int len=sqrt(q);
	for(int i=1; i<=n; i++)
		cin>>a[i];
	for(int i=1; i<=q; i++){
		cin>>qu[i].lt>>qu[i].rt;
		qu[i].id=i;
		qu[i].kuai=(qu[i].lt-1)/len+1;
	}
	sort(qu+1,qu+q+1,cmp);
	int nw_lt=1,nw_rt=1;
	ans=0;
	sum[a[1]]=1;
	for(int i=1; i<=q; i++){
		while(nw_lt>qu[i].lt)
			add(--nw_lt);
		while(nw_rt<qu[i].rt)
			add(++nw_rt);
		while(nw_lt<qu[i].lt)
			delet(nw_lt++);
		while(nw_rt>qu[i].rt)
			delet(nw_rt--);
		pt[qu[i].id]=ans;
	}
	for(int i=1; i<=q; i++)
		cout<<pt[i]<<'\n';
	return 0;
}
```

---

## 作者：sunzz3183 (赞：1)

# [ABC293G] Triple Index 题解

## 题意

给定一个长度为 $n$ 的数组 $a$，给定 $q$ 个询问，每次询问问 $l,r$，之间有多少个元素相等的三元组（即求 $\sum\limits_{i=l}^{r}\sum\limits_{j=i+1}^{r}\sum\limits_{k=j+1}^{r}[a_i=a_i=a_k]$）。

## 分析

显然，每个询问相互独立，又 $1\leq n,q\leq 2\times10^5$，显然可以 $O(n\sqrt{n})$ 莫队。

莫队就是正常的莫队，主要是在处理价值时不同。

我们去统计每个数出现的次数，所以，我们先要对整个 $a$ 进行离散化。然后，去开一个桶 $book$，用来储存出现的次数。

然后，在统计价值的时候，显然当 $book_i\geq 2$ 时，每加一个数，价值为 

$$ C_{book_i}^2 $$

```cpp
inline int solve(int n){return n>=2?n*(n-1)>>1:0;}
```

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=2e5+5;
int n,q,k,sum,a[N],pos[N],ans[N],book[N];
vector<int>v;
struct qwq{
	int l,r,id;
}b[N];
inline int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
bool cmp(qwq x,qwq y){return pos[x.l]==pos[y.l]?x.r<y.r:pos[x.l]<pos[y.l];}
inline int solve(int n){return n>=2?n*(n-1)>>1:0;}
void sub(int x){
	book[a[x]]--;
	sum-=solve(book[a[x]]);
	return;
}
void add(int x){
	sum+=solve(book[a[x]]);
	book[a[x]]++;
	return;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen("a.out","w",stdout);
    n=read();q=read();k=sqrt(n);
    for(int i=1;i<=n;i++)a[i]=read(),pos[i]=(i-1)/k+1,v.push_back(a[i]);
    sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;i++)a[i]=getid(a[i]);
	for(int i=1;i<=q;i++)b[i]={read(),read(),i};
	sort(b+1,b+q+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=q;i++){
		while(l<b[i].l)sub(l++);
		while(l>b[i].l)add(--l);
		while(r>b[i].r)sub(r--);
		while(r<b[i].r)add(++r);
		ans[b[i].id]=sum;
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
    return 0;
}
```


---

## 作者：_Ad_Astra_ (赞：0)

首先看到查询是离线的，而且每一个数的影响可以确定，考虑莫队。

而不难想到，每次加上一个数 $a_i$ 时，只需要记录区间内有多少个 $a_j = a_i$ 即可。由于 $1 \le a_i \le 2 \times 10^5$，因此直接开数组就可以存储。若区间内有 $x$ 个数等于 $a_i$，若 $x \lt 2$ 则没有贡献，否则答案的贡献就是 $\frac{x(x-1)}{2}$。删除的情况类似。

时间复杂度 $O(n\sqrt{n})$。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int k;
struct node
{
	int l,r,id;
	bool operator<(node B)const
	{
		if((l-1)/k==(B.l-1)/k)return r<B.r;
		return l/k<B.l/k;
	}
}c[200010];
int a[200010],b[200010],ans[200010],n,m,cnt;
void add(int x)
{
	b[x]++;
	if(b[x]>=3)cnt+=(b[x]-1)*(b[x]-2)/2;
}
void del(int x)
{
	if(b[x]>=3)cnt-=(b[x]-1)*(b[x]-2)/2;
	b[x]--;
}
signed main()
{
	int l,r,ll=1,rr=0;
	cin>>n>>m;
	k=sqrt(n);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>c[i].l>>c[i].r,c[i].id=i;
	sort(c+1,c+m+1);
	for(int i=1;i<=m;i++)
	{
		l=c[i].l,r=c[i].r;
		while(ll>l)add(a[--ll]);
		while(rr<r)add(a[++rr]);
		while(ll<l)del(a[ll++]);
		while(rr>r)del(a[rr--]);
		ans[c[i].id]=cnt;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<endl;
	return 0;
}

---

## 作者：__vector__ (赞：0)

本题解作者赛时由于答案输出部分写挂，删点写挂，没能绝杀。  
## 题解  
没有修改，且不强制在线，而且可以快速处理加点删点对答案的贡献，显然是莫队板子。  
[oiwiki 普通莫队算法](https://oiwiki.org/misc/mo-algo/)  
说一下具体实现。  

考虑加上或删除某个点后，怎么计算贡献。  

可以开一个数组记录每个值在原数组出现次数。  

设加或删的点值为 $val$。  

- 加点  
设 $val$ 在**原来的**数组中出现了 $cnt_{val}$ 次。  
答案将增加 $C_{cnt_{val}+1}^3 -C_{cnt_{val}}^3 = \frac{cnt_{val}(cnt_{val}-1)}{2}$。  
然后更新 $cnt_{val}$ 即可。  
- 删点  
若 $cnt_{val} \le 2$，显然不需要计算。  
否则将答案减少 $C_{cnt_{val}}^{3} - C_{cnt_{val}-1}^{3}$，~~我手懒就不把化简后的式子写上了~~。  
然后更新 $cnt_{val}$ 即可。  

[Atcoder 提交记录](https://atcoder.jp/contests/abc293/submissions/39645868)  


---

## 作者：快乐的大童 (赞：0)

### 题目大意
给你 $n$ 个数 $a_i$，$q$ 次询问两个整数 $l,r$，求区间 $[l,r]$ 内有多少满足 $l\le i<j<k\le r$ 且 $a_i=a_j=a_k$ 的三元组 $(i,j,k)$。

$n,q\le 2\times10^5$，**允许离线**。
### 思路
对于一个数 $k$，选择的 $a_i=a_j=a_k$ 的值为 $k$ 的方案数为 $C^3_{cnt_k}$，其中 $cnt_k$ 为区间 $[l,r]$ 中数字 $k$ 出现的次数。

我们想要快速计算区间内所有数对答案的贡献，再看到 $n\le 2\times10^5$，允许离线等信息，我们不难想到**莫队**。

首先，预处理所有 $C^3_i$ 的值，这可以用组合数递推式实现。

其次，我们每次移动指针时，先减去这个数原先的贡献，再加上当前的贡献，完成移动操作。

然后这道题就变成一道板子了。

~~其实这题本身就是一道板子吧~~
### 代码
```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define int long long
using namespace std;
inline int R(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[70];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);
}
inline void writeln(int x){
	write(x);putchar(10);
}
const int maxn=2e5+5;
int n,m,a[maxn],ans;
int pos[maxn];
int c[maxn][4];
struct query{
	int l,r,num,ans;
	bool operator<(query &x)const{
		if(pos[l]!=pos[x.l]) return l<x.l;
		else return r<x.r;
	}
}q[maxn];
int cnt[maxn];
void add(int x){
	x=a[x];
	if(cnt[x]>=3) ans-=c[cnt[x]][3];
	cnt[x]++;
	if(cnt[x]>=3) ans+=c[cnt[x]][3];
}
void del(int x){
	x=a[x];
	if(cnt[x]>=3) ans-=c[cnt[x]][3];
	cnt[x]--;
	if(cnt[x]>=3) ans+=c[cnt[x]][3];
}
//cnt[x]>=3这个条件是赛时加的，不加也可以
bool cmp(query x,query y){
	return x.num<y.num;
}
signed main(){
	n=R(),m=R();rep(i,1,n)a[i]=R();
	rep(i,1,m)q[i]=(query){R(),R(),i,0};
	c[1][0]=c[1][1]=1;
	rep(i,2,n){
		c[i][0]=1;
		rep(j,1,3) c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	int bz=sqrt(n);
	rep(i,1,n)pos[i]=(i-1)/bz+1;
	sort(q+1,q+m+1);
	int l=1,r=0;
	rep(i,1,m){
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		q[i].ans=ans;
	}
	sort(q+1,q+m+1,cmp);
	rep(i,1,m) writeln(q[i].ans);
}

```


---

## 作者：expnoi (赞：0)

莫队板子。

假设一个数为 $x$，这个数在这个区间的出现次数是 $cntx$，显而易见，此时这个数对这个区间答案的贡献是 $cntx \times (cntx-1) \times (cntx-2)/6$。

从而可以用莫队维护。

分别维护当前答案，用一个数组记录当前区间每个数出现的个数即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return s*w;
}
inline void print(int x)
{
	if(x<0)x=-x,putchar('-');
	if(x>=10)print(x/10);
	putchar(x%10+48);
}
int n=read(),q=read(),a[1000010],bl[1000010],S=sqrt(n),ans[1000010],res,cnt[1000010];
struct node{
	int id,l,r;
}Q[1000010];
inline bool cmp(node a,node b)
{
	if(bl[a.l]==bl[b.l])return a.r<b.r;
	return bl[a.l]<bl[b.l];
}
inline void update(int x,int v)
{
	if(v==1)
	{
		res-=((cnt[a[x]]*(cnt[a[x]]-1)*(cnt[a[x]]-2))/6);
		cnt[a[x]]++;
		res+=((cnt[a[x]]*(cnt[a[x]]-1)*(cnt[a[x]]-2))/6);
	}
	else
	{
		res-=((cnt[a[x]]*(cnt[a[x]]-1)*(cnt[a[x]]-2))/6);
		cnt[a[x]]--;
		res+=((cnt[a[x]]*(cnt[a[x]]-1)*(cnt[a[x]]-2))/6);
	}
}
signed main()
{
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
	{
		bl[i]=(i-1)/S+1;
	}
	for(int i=1;i<=q;i++)
	{
		Q[i]={i,read(),read()};
	}
	sort(Q+1,Q+q+1,cmp);
	for(int i=1,l=1,r=0;i<=q;i++)
	{
		while(l>Q[i].l)update(--l,1);
		while(r<Q[i].r)update(++r,1);
		while(l<Q[i].l)update(l++,-1);
		while(r>Q[i].r)update(r--,-1);
		ans[Q[i].id]=res;
	}
	for(int i=1;i<=q;i++)
	{
		print(ans[i]);
		puts("");
	}
}
```

---

## 作者：rui_er (赞：0)

莫队板子。

类似于 [小 B 的询问](https://www.luogu.com.cn/problem/P2709)，在移动指针过程中，维护每个数出现次数 $cnt_i$，同时维护 $\sum\binom{cnt_i}{3}$ 即可。

取序列分块块长 $B=\frac{n}{\sqrt{m}}$，有最优复杂度 $\mathcal O(n\sqrt{m})$。

在 ABC G 看到过好几次莫队板子，ABC 怎么这么喜欢莫队板子。

```cpp
// Problem: G - Triple Index
// Contest: AtCoder - AtCoder Beginner Contest 293
// URL: https://atcoder.jp/contests/abc293/tasks/abc293_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
	uniform_int_distribution<ll> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e5+5;

ll n, m, a[N], L[N], R[N], pos[N], sz, tot, buc[N], now, ans[N];

struct Query {
	ll l, r, id;
	Query(ll a=0, ll b=0, ll c=0) : l(a), r(b), id(c) {}
	friend bool operator<(const Query& a, const Query& b) {
		if(pos[a.l] != pos[b.l]) return a.l < b.l;
		return (pos[a.l] & 1) ? (a.r < b.r) : (a.r > b.r);
	}
}q[N];

void initBlock() {
	sz = n / sqrt(m);
	chkmax(sz, 1LL);
	chkmin(sz, n);
	while(++tot) {
		L[tot] = R[tot-1] + 1;
		R[tot] = min(sz*tot, n);
		rep(i, L[tot], R[tot]) pos[i] = tot;
		if(R[tot] == n) break;
	}
}

void ins(ll x) {
	now -= buc[x] * (buc[x] - 1) / 2 * (buc[x] - 2) / 3;
	++buc[x];
	now += buc[x] * (buc[x] - 1) / 2 * (buc[x] - 2) / 3;
}

void del(ll x) {
	now -= buc[x] * (buc[x] - 1) / 2 * (buc[x] - 2) / 3;
	--buc[x];
	now += buc[x] * (buc[x] - 1) / 2 * (buc[x] - 2) / 3;
}

int main() {
	scanf("%lld%lld", &n, &m);
	rep(i, 1, n) scanf("%lld", &a[i]);
	initBlock();
	rep(i, 1, m) scanf("%lld%lld", &q[i].l, &q[i].r), q[i].id = i;
	sort(q+1, q+1+m);
	ll l = 1, r = 0;
	rep(i, 1, m) {
		while(l > q[i].l) ins(a[--l]);
		while(r < q[i].r) ins(a[++r]);
		while(l < q[i].l) del(a[l++]);
		while(r > q[i].r) del(a[r--]);
		ans[q[i].id] = now;
	}
	rep(i, 1, m) printf("%lld\n", ans[i]);
	return 0;
}
```

---

