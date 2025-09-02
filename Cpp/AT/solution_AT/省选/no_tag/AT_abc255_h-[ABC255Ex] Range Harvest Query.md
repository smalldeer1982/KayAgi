# [ABC255Ex] Range Harvest Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_h

$ N $ 本の木があります。$ 0 $ 日目にはどの木にも実は一つもなっていません。  
 $ 1 $ 日目以降の毎朝、それぞれの $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目の木に $ i $ 個の実が増えます。

高橋君は $ Q $ 回の収穫作業をします。 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 回目の収穫作業は $ D_i $ 日目の夜に行われ、その時点で $ L_i $ 番目から $ R_i $ 番目の木になっているすべての実を収穫します。

$ Q $ 回の収穫作業のそれぞれについて、高橋君が収穫する実の個数を $ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ D_1\ \lt\ D_2\ \lt\ \cdots\ \lt\ D_Q\ \leq\ 10^{18} $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- 入力はすべて整数

### Sample Explanation 1

$ i\ =\ 1,\ 2,\ 3,\ 4,\ 5 $ について、$ i $ 番目の木になっている実の個数を $ A_i $ とし、 それぞれの木になっている実の個数を数列 $ A\ =\ (A_1,\ A_2,\ A_3,\ A_4,\ A_5) $ を用いて表すことにします。 - $ 0 $ 日目、$ A\ =\ (0,\ 0,\ 0,\ 0,\ 0) $ です。 - $ 1 $ 日目の朝、それぞれの木に新たに実がなり、$ A\ =\ (1,\ 2,\ 3,\ 4,\ 5) $ となります。 - $ 2 $ 日目の朝、それぞれの木に新たに実がなり、$ A\ =\ (2,\ 4,\ 6,\ 8,\ 10) $ となります。 - $ 2 $ 日目の夜、高橋君は $ 1 $ 回目の収穫を行います。$ 4\ +\ 6\ =\ 10 $ 個の木の実を収穫し、$ A\ =\ (2,\ 0,\ 0,\ 8,\ 10) $ となります。 - $ 3 $ 日目の朝、それぞれの木に新たに実がなり、$ A\ =\ (3,\ 2,\ 3,\ 12,\ 15) $ となります。 - $ 3 $ 日目の夜、高橋君は $ 2 $ 回目の収穫を行います。$ 3\ +\ 12\ =\ 15 $ 個の木の実を収穫し、$ A\ =\ (3,\ 2,\ 0,\ 0,\ 15) $ となります。 - $ 4 $ 日目の朝、それぞれの木に新たに実がなり、$ A\ =\ (4,\ 4,\ 3,\ 4,\ 20) $となります。 - $ 5 $ 日目の朝、それぞれの木に新たに実がなり、$ A\ =\ (5,\ 6,\ 6,\ 8,\ 25) $となります。 - $ 5 $ 日目の夜、高橋君は $ 3 $ 回目の収穫を行います。$ 5\ +\ 6\ +\ 6\ +\ 8\ +\ 25\ =\ 50 $ 個の木の実を収穫し、$ A\ =\ (0,\ 0,\ 0,\ 0,\ 0) $ となります。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
5 3
2 2 3
3 3 4
5 1 5```

### 输出

```
10
15
50```

## 样例 #2

### 输入

```
711741968710511029 1
82803157126515475 516874290286751784 588060532191410838```

### 输出

```
603657470```

# 题解

## 作者：xkcdjerry (赞：5)

怎么题解区全都是珂朵莉树，这题动态开点线段树完全能过的啊（

看到区间操作，区间询问，巨大值域可以直接考虑动态开点线段树。


因为每次区间清空操作带一个隐式的时间流逝，所以 naive 的想法是用一个类似懒标记的方式对于每个节点记录距离上次访问过去了多久，然后访问到这个点的时候给儿子下推。  
但是每次更新都会全局打时间流逝标记，故每个节点即使立马被清除标记覆盖都必定会下传，会有较大的时间常数影响。

稍稍改变思路，这里考虑对于每个点记录上次更新的时间和当时的总价值，显然通过这两个值结合左右端点能够 $O(1)$ 求出目前的总价值。那么每次 pushup 的时候计算左右儿子当前时间的价值和作为总价值，并将当前时间作为上次更新时间即可。  
注意这样只会在单侧递归时有一次有意义计算，相比时间流逝懒标记的双侧吓退有了代码长度和时间常数上的双重优化。

---

注意到这点之后剩下的部分就很套路了：  
维护一个上次被清空的时间懒标记，递归的时候下推即可。具体清空的方式为设置上次更新时间为目前时间，总价值为 $0$。  

由于每次询问和清空的区间相同这里把两个合并到了一个函数里减小代码复杂度。

如果使用 `modint` 要注意几个细节：  
* 区间端点要使用 `long long`，否则 `/2` 的时候可能会改变相对长度。
* 因为 `modint` 特性，懒标记不存在一个“空”特殊值，可以使用 `long long` 懒标记或者直接额外加一个 `dirty` 变量记录是否有懒标记。
* 因为 `modint` 的除法操作较昂贵可以预处理 $2$ 的逆元减小时间复杂度。


运行时间只有 1.5~2 秒，非常宽裕。  
注意数组开大一些，[第一次提交](https://atcoder.jp/contests/abc255/submissions/50395655)开的 `N*200` 过去了，后面改到 `N*170` 就 RE 了。

此处给出的代码是进行可读性修改后的最终版：
```cpp
#include <cstdio>
#include <atcoder/modint>
#define N 200010
#define ll long long
#define mint atcoder::modint998244353
#define P 998244353
#define INV2 ((P+1)/2)
struct seg
{
    // last,sum: 在时刻last,总和为sum
    // dirty: 若!=0，上次清空时间为tag
    int ls,rs; bool dirty;
    mint tag,last,sum;
}T[N*200]; int cur;
mint calc(mint L,mint R,mint now,int o)
{
    return T[o].sum+(R+L)*(R-L+1)*INV2*(now-T[o].last);
}
void upd(ll L,ll R,mint now,int o)
{
    mint mid=(L+R)/2; T[o].last=now;
    T[o].sum=calc(L,mid,now,T[o].ls)+calc(mid+1,R,now,T[o].rs);
}
void Clear(mint now,int o) {T[o].tag=now, T[o].dirty=1, T[o].last=now, T[o].sum=0;}
void push(int o)
{
    if(T[o].dirty)
    {
        if(!T[o].ls) T[o].ls=++cur;
        if(!T[o].rs) T[o].rs=++cur;
        Clear(T[o].tag,T[o].ls);
        Clear(T[o].tag,T[o].rs);
        T[o].dirty=0;
    }
}
mint clear(ll l,ll r,ll L,ll R,ll now,int &o)
{
    if(!o) o=++cur; // 全0为空点，所以不用初始化
    if(l==L&&r==R)
    {
        mint tmp=calc(L,R,now,o);
        return Clear(now,o),tmp;
    }
    ll mid=(L+R)/2; push(o); mint ans;
    if(r<=mid) ans=clear(l,r,L,mid,now,T[o].ls);
    else if(l>mid) ans=clear(l,r,mid+1,R,now,T[o].rs);
    else ans=clear(l,mid,L,mid,now,T[o].ls)+clear(mid+1,r,mid+1,R,now,T[o].rs);
    upd(L,R,now,o);
    return ans;
}
ll n; int q;
int main()
{
    scanf("%lld%d",&n,&q); int root=0;
    while(q--)
    {
        ll d,l,r; scanf("%lld%lld%lld",&d,&l,&r);
        mint ans=clear(l,r,1,n,d,root);
        printf("%u\n",ans.val());
    }
}
```

---

## 作者：jamesharden666 (赞：5)

## 题目大意

给定一片 $N$ 格的农田，从第 $0$ 天开始，第 $i$ 格农田每天会长出 $i$ 的作物。

给出 $Q$ 个询问，每次询问以 $D,L,R$ 的格式给出，表示询问在第 $D$ 天，收割 $[L,R]$ 的农田，会获得多少作物？答案对 $998244353$ 取模。注意询问相互依赖，即在每一次收割后，$[L,R]$ 的作物应当清零。


## 解题思路

考虑用珂朵莉树来维护当前农田最后一次被割的天数。因为每个农田增长的作物是固定的，所以我们用天数 $\times$ 农田增长的总和，这个用等差数列公式即可。因为数据较大，所以除 $2$ 要改为 $\times2$ 的逆元。



## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,mod=998244353,inv=499122177;
struct node
{
    long long l,r;
    mutable long long v;
    node(long long L,long long R=-1,long long V=0)
    {
        l=L,r=R,v=V;
    }
    bool operator<(const node &a) const
    {
        return l<a.l;
    }
};
set<node> a;
#define at set<node>::iterator
long long read()
{
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
at split(long long pos)
{
    at it=a.lower_bound(pos);
    if(it!=a.end()&&it->l==pos)
        return it;
    it--;
    long long l=it->l;
    long long r=it->r;
    long long v=it->v;
    a.erase(it);
    a.insert(node(l,pos-1,v));
    return a.insert(node(pos,r,v)).first;
}
long long emerge(long long l,long long r,long long k)
{
    at itr=split(r+1);
    at itl=split(l);
    long long ans=0;
    for(at it=itl;it!=itr;++it) 
    {
        ans+=(k-it->v)%mod*((it->l+it->r)%mod)%mod*((it->r-it->l+1)%mod)%mod*inv%mod;
        if(ans>=mod)
            ans-=mod;
    }
    a.erase(itl,itr);
    a.insert(node(l,r,k));
    return ans;
}
int main()
{
    n=read(),q=read();
    a.insert(node(1,n,0));
    for(int i=1;i<=q;++i)
    {
        long long k=read(),l=read(),r=read();
        printf("%lld\n",emerge(l,r,k));
        // for(at it=a.begin();it!=a.end();++it)
        //     cout<<it->l<<" "<<it->r<<" "<<it->v<<"\n";
    }
    return 0;
}
```

---

## 作者：Rnfmabj (赞：4)

## ABC255Ex

*2430

思路较为简单。

调了一下午加一早上，发现是人眼做 $10^{18}$ 级整数比大小判错了，抬走。

### 题意

给定一片 $N$ 格的农田，从第 $0$ 天开始，第 $i$ 格农田每天会长出 $i$ 的作物。

给出 $Q$ 个询问，每次询问以 $D,L,R$ 的格式给出，表示询问在第 $D$ 天，收割 $[L,R]$ 的农田，会获得多少作物？答案对 $998244353$ 取模。注意询问相互依赖，即在每一次收割后，$[L,R]$ 的作物应当清零。

$1\le l_i \le r_i\le n \le 10^{18}$

$1\le q \le 2×10^5$

$1< d_1 < d_2<...< d_q≤10^{18}$

### 题解

值域很大，传统的线段树无法维护。动态开点线段树根据实现的好坏，需要不同程度的卡常。

考虑使用 `std::set` 维护操作过的区间。假设一次操作 $(d,l,r)$ 所操作的区间先前未被操作过，则根据等差数列求和公式，本次操作的答案为 $\frac{d·(r+l)·(r-l+1)}{2}$。

注意到对于一个相同的区间 $[l,r]$，在操作 $(d,l,r)$ 前有操作 $(d_0,l,r)$，则 $(d,l,r)$ 的答案是 $\frac{(d-d_0)·(r+l)·(r-l+1)}{2}$，其后 $d_0$ 不再影响接下来的操作，$d$ 取而代之。

于是在计算答案是可以先计算出不受任何影响的 $\frac{d·(r+l)·(r-l+1)}{2}$，然后再减去与区间 $[l,r]$ 有交的先前操作的影响，最后由于操作的覆盖性质直接去掉这些相交的区间，并覆盖上 $(d,l,r)$ 即可。

实现上，使用 `std::set` 维护保留下的所有区间，按 $l$ 为第一关键字排序，每次操作时找到所有与 $[l,r]$ 有交的操作然后减去先前操作的影响。

对相交的情况分类讨论即可。

发现如此维护区间后，`std::set` 内保留的区间两两不交。共有 $q$ 次询问，每次询问都会插入一个区间，每个区间若导致分裂只会产生 $O(1)$ 个新区间，覆盖其他区间则直接将其删除，而每个块最多被删除一次。总区间数及其操作数仍在 $O(q)$ 级别，单次操作时间复杂度为 $O(\log q)$，故总复杂度为 $O(q\log q)$ ，可以通过本题。

### 代码

```cpp
const ll maxn=2e5+5,mod=998244353,inv=499122177;
struct node{
	ll l,r,d;
	friend bool operator < (const node &x,const node &y){
		return x.l==y.l?x.r<y.r:x.l<y.l;
	}
};
set<node>s;
ll ins(ll l,ll r,ll d){
	ll res=((r+l)%mod*((r-l+1)%mod)%mod)*(d%mod)%mod*inv%mod;//计算原始答案
	auto it=s.lower_bound((node){l,0,d});
	while(it!=s.end()&&it->l<=r){//左端点落在区间内
		if(it->r<=r){//完全被区间包含
			res=(res+mod-((it->r+it->l)%mod*((it->r-it->l+1)%mod)%mod*(it->d%mod)%mod*inv%mod)%mod)%mod;
			s.erase(*it);
		}
		else{//右端点在区间外
			node tmp=*it;
			res=(res+mod-((r+it->l)%mod*((r-it->l+1)%mod)%mod*(it->d%mod)%mod*inv%mod)%mod)%mod;
			s.erase(*it);
			s.insert((node){r+1,tmp.r,tmp.d});
		}
		it=s.lower_bound((node){l,0,d});
	}
	if(it!=s.begin()){
		it--;
		if(it->r>=l){//要求有交
			if(it->r<=r){//左端点在区间外
				node tmp=*it;
				res=(res+mod-((it->r+l)%mod*((it->r-l+1)%mod)%mod*(it->d%mod)%mod*inv%mod)%mod)%mod;
				s.erase(*it);
				s.insert((node){tmp.l,l-1,tmp.d});
			}
			else {//区间完全被包含
				node tmp=*it;
				res=(res+mod-((r+l)%mod*((r-l+1)%mod)%mod*(it->d%mod)%mod*inv%mod)%mod)%mod;
				s.erase(*it);
				s.insert((node){tmp.l,l-1,tmp.d});
				s.insert((node){r+1,tmp.r,tmp.d});
			}
		}
		
	}
	s.insert((node){l,r,d});
	return res;
}
ll n,m;
void solve(){
	n=R,m=R;
	while(m--){
		ll d=R,l=R,r=R;
		we(ins(l,r,d));
	}
	return ;
}
```



---

## 作者：Coffee_zzz (赞：2)

提供一种不需要 ODT，只需要线段树的做法。

首先设 $R_i'=R_i+1$，把每个区间 $[L_i,R_i]$ 转化为 $[L_i,R_i')$。这一步是为了方便离散化。

把所有的 $L_i$ 和 $R_i'$ 离散化。设离散化后共有 $m$ 个数，从小到大依次为 $v_1$ 至 $v_m$。

考虑维护一棵 $m-1$ 个叶子结点的线段树，第 $i$ 个叶子结点对应区间 $[v_i,v_{i+1})$，即 $[v_i,v_{i+1}-1]$，用于记录每段的权值被减去了多少。

每次询问可以用 $\dfrac {(L_i+R_i)(R_i-L_i+1)D_i} 2$ 减去 $[L_i,R_i]$ 中已经被减去的权值之和，之后对 $[L_i,R_i]$ 进行区间赋值即可。

时间复杂度 $\mathcal O(q \log q)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int Q=2e5+5,mod=998244353;
int n,q,d[Q],L[Q],R[Q],l[Q],r[Q],a[Q<<1],v[Q<<1],tot,tag[Q<<3],val[Q<<3];
int count(int x,int y){
	return (x+y)%mod*((y-x+1)%mod)%mod*((mod+1)/2)%mod;
}
void upd(int g){
	val[g]=(val[g<<1]+val[g<<1|1])%mod;
}
void down(int g,int l,int r){
	int m=(l+r)>>1;
	if(tag[g<<1]<tag[g]) tag[g<<1]=tag[g],val[g<<1]=count(v[l],v[m+1]-1)*(tag[g<<1]%mod)%mod;
	if(tag[g<<1|1]<tag[g]) tag[g<<1|1]=tag[g],val[g<<1|1]=count(v[m+1],v[r+1]-1)*(tag[g<<1|1]%mod)%mod;
}
int ask(int g,int l,int r,int x,int y){
	if(x<=l&&r<=y) return val[g];
	if(y<l||r<x) return 0;
	int m=(l+r)>>1;
	down(g,l,r);
	return (ask(g<<1,l,m,x,y)+ask(g<<1|1,m+1,r,x,y))%mod;
}
void modify(int g,int l,int r,int x,int y,int d){
	if(x<=l&&r<=y){
		tag[g]=d;
		val[g]=count(v[l],v[r+1]-1)*(tag[g]%mod)%mod;
		return;
	}
	if(y<l||r<x) return;
	int m=(l+r)>>1;
	down(g,l,r);
	modify(g<<1,l,m,x,y,d);
	modify(g<<1|1,m+1,r,x,y,d);
	upd(g);
}
void solve(){
	cin>>n>>q;
	for(int i=1;i<=q;i++) cin>>d[i]>>L[i]>>R[i],++R[i],a[i*2-1]=L[i],a[i*2]=R[i];
	sort(a+1,a+1+q+q);
	for(int i=1;i<=q+q;i++) if(a[i]!=a[i-1]) v[++tot]=a[i];
	for(int i=1;i<=q;i++) l[i]=lower_bound(v+1,v+1+tot,L[i])-v,r[i]=lower_bound(v+1,v+1+tot,R[i])-v;
	for(int i=1;i<=q;i++){
		cout<<(count(L[i],R[i]-1)*(d[i]%mod)%mod+mod-ask(1,1,tot-1,l[i],r[i]-1))%mod<<endl;
		modify(1,1,tot-1,l[i],r[i]-1,d[i]);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：This_Rrhar (赞：1)

设 $a_i$ 为第 $i$ 格农田最后被割的时间。

当第 $i$ 格在第 $d$ 天被割时，会获得 $i(d-a_i)$ 的作物，同时令 $a_i\gets d$。

用 ODT 维护序列 $a$，把一段连续的 $a_i$ 一起算。由于总段数为 $O(Q)$，所以时间复杂度为 $O(Q\log Q)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		inline char gc(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		inline input _o>>(char&num){do num=gc();while(num==' '||num=='\n'||num=='\r'||num=='\t');_r;}
		template<typename T>inline input _o>>(T&x)
		{
			char c=gc();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=gc();
			while(isdigit(c))x=(x*10)+(c^48),c=gc();
			x*=f;_r;
		}
		input(){}
	}in;
	struct output
	{
		inline void pt(char num){*pp++=num;if(pp-pb==_S)fl();}
		inline output _o<<(char num){pt(num);_r;}
		template<typename T>inline output _o<<(T x)
		{
			if(!x){pt(48);_r;}
			if(x<0)pt('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)pt(s[t--]+48);
			_r;
		}
		inline output _o<<(const char*siz){int num=0;while(siz[num])pt(siz[num++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
	
	int i;int read(){return in>>i,i;}
	long long l;long long readll(){return in>>l,l;}
}
using IO::in;
using IO::out;
using IO::read;
using IO::readll;
using ll=long long;

#define MOD 998244353
ll qpow(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1)(res*=x)%=MOD;
		(x*=x)%=MOD,y>>=1;
	}
	return res;
}
const ll inv2=499122177;

struct node
{
	mutable ll l,r,v;
	node(ll l=0,ll r=0,ll v=0):l(l),r(r),v(v){}
	bool operator<(const node&B)const{return l<B.l;}
};
set<node>odt;
set<node>::iterator split(ll pos)
{
	set<node>::iterator it=odt.lower_bound(node(pos));
	if(it!=odt.end()&&it->l==pos)return it;
	if((--it)->r<pos)return odt.end();
	ll l=it->l,r=it->r,v=it->v;
	return odt.erase(it),odt.insert(node(l,pos-1,v)),odt.insert(node(pos,r,v)).first;
}
ll query(ll l,ll r,ll d)
{
	set<node>::iterator itr=split(r+1),itl=split(l),it=itl;
	ll ans=0;
	while(it!=itr)
		(ans+=(d-it->v)%MOD*((it->l+it->r)%MOD)%MOD*((it->r-it->l+1)%MOD)%MOD*inv2%MOD)%=MOD,it++;
	return odt.erase(itl,itr),odt.insert(node(l,r,d)),ans;
}

ll n,q;

ll l,r,d;

int main()
{
	in>>n>>q,odt.insert(node(1,n,0));
	while(q--)in>>d>>l>>r,out<<query(l,r,d)<<"\n";
}
```

---

## 作者：james1BadCreeper (赞：1)

如果一段的麦子是同时开始生长的，那么容易用等差数列求和直接求出这段的贡献。

珂朵莉树维护麦子上次被收割时间的颜色段，查询的时候直接将颜色段取出暴力统计每段的答案。一次修改会将参与运算的颜色段推平，因此存在颜色段均摊，时间复杂度为 $O(q\log\log q)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const i64 P = 998244353; 
const i64 V = (P + 1) / 2; 

struct Node {
    i64 l, r; mutable i64 v; 
    Node(i64 l = 0, i64 r = 0, i64 v = 0) : l(l), r(r), v(v) {} 
    bool operator< (const Node &a) const { return l < a.l; }
};
set<Node> T;
auto split(i64 p) {
    auto it = T.lower_bound(Node(p)); 
    if (it != T.end() && it->l == p) return it; 
    --it; i64 l = it->l, r = it->r, v = it->v; 
    T.erase(it); T.emplace(l, p - 1, v); 
    return T.emplace(p, r, v).first; 
}
i64 n; int q; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> q; T.emplace(1, n, 0); 
    while (q--) {
        i64 d, l, r, ans = 0; cin >> d >> l >> r; 
        auto R = split(r + 1), L = split(l); 
        for (auto it = L; it != R; ++it) 
            ans = (ans + (__int128)(it->l + it->r) * (it->r - it->l + 1) / 2 % P * (d - it->v) % P) % P; 
        T.erase(L, R); 
        T.emplace(l, r, d); 
        cout << ans << "\n"; 
    }
    return 0; 
}
```

---

## 作者：_7Mr (赞：1)

# 题意
给定一片 $n$ 个的农田，从第 $0$ 天开始，第 $i$ 个农田每天会长出 $i$ 的农作物。

现在有 $q$ 个询问，每次询问有三个参数 $d,l,r$，每个询问你需要回答在第 $d$ 天，收割 $l$ 到 $r$，包含端点的农田，会获得多少农作物？

所有的答案对 $998244353$ 取模。注意每一次收割后，需要将 $l$ 到 $r$，包含端点的农田所有农作物清空。

# 思路
拿到这道题一看珂朵莉树板子题。

什么你还不知道珂朵莉树是什么，不要担心跟着这篇[文章](https://www.luogu.com.cn/blog/602632/ke-duo-li-shi-quan-shi-jie-zui-xing-fu-di-ru-hai)学习吧。

我们可以使用珂朵莉树来维护农田最后一次被收割的时间。由于第 $i$ 个农田每天只会生长出 $i$ 的农作物，因此每个农田的生长农作物就固定下来了，所以我们就能用等差数列快速算出答案了。

这里注意本题的值域是 $10^{18}$ 级别的，所以我们在计算等差数列的时候，$\div 2$ 我们需要换成 $\times 2$ 的逆元。如果你不知道逆元怎么算也可以用 ```__int128``` 这里推荐使用逆元，有些比赛是不准使用 ```__int128``` 的，所以老老实实使用逆元吧，~~逆元其实不难的~~。

更多细节见代码。

# 复杂度分析

一共会覆盖 $q$ 次，我们的珂朵莉树使用 ```set``` 维护，所以总复杂度 $O(q \log \log q)$。关于珂朵莉树更正确更详细的时间复杂度分析可以参考这篇[文章](https://zhuanlan.zhihu.com/p/102786071)。


# ACcode

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int mod=998244353;
int n,q;
int ksm(int a,int b,int p){//求逆元，也可以提前把2的逆元算出来
	int res=1;
	while(b){
		if(b%2) res=res*a%p;
		b/=2;
		a=a*a%p;
	}
	return res;
}
struct node {//珂朵莉树结构体
	int l,r;
	mutable int v;
	node(int L,int R=0,int V=0) : l(L),r(R),v(V) {}
	bool operator < (const node &x) const {
		return l<x.l;
	}
};
set<node> ODT;
set<node>::iterator spilit(int pos) {//珂朵莉树分裂
	set<node>::iterator it=ODT.lower_bound(node(pos,-1,0));
	if(it!=ODT.end() && it->l==pos) return it;
	it--;
	if(it->r<pos) return ODT.end();
	int V=it->v,L=it->l,R=it->r;
	ODT.erase(it);
	ODT.insert(node(L,pos-1,V));
	return ODT.insert(node(pos,R,V)).first;
}
void bulldoze(int l,int r,int x) {//珂朵莉树区间推平虽然这道题用不到
	set<node>::iterator itr=spilit(r+1),itl=spilit(l);
	ODT.erase(itl,itr);
	ODT.insert(node(l,r,x));
}
int sum(int l,int r,int d){//求答案
	set<node>::iterator itr=spilit(r+1),itl=spilit(l);
	int ans=0;
	for(;itl!=itr;itl++){
		ans+=(d-itl->v)%mod*((itl->l+itl->r)%mod)%mod*((itl->r-itl->l+1)%mod)%mod*(ksm(2,mod-2,mod)%mod)%mod;
		ans%=mod;
	}
	itr=spilit(r+1),itl=spilit(l);//注意这里itl在上面已更改，所以要再分裂一次
	ODT.erase(itl,itr);
	ODT.insert(node(l,r,d));
	return ans;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>q;
	ODT.insert(node(1,n,0));//初始化
	while(q--){
		int d,l,r;
		cin>>d>>l>>r;
		cout<<sum(l,r,d)<<endl;//输出答案
	}
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：0)

题意：

给定一片 $n$ 格的农田，从第 $0$ 天开始，第 $i$ 格农田每天会长出 $i$ 的作物。

给出 $q$ 个询问，每次询问以 $d,l,r$ 的格式给出，表示询问在第 $d$ 天，收割 $[l,r]$ 的农田，会获得多少作物？答案对 $998244353$ 取模。注意询问相互依赖，即在每一次收割后，$[l,r]$ 的作物应当清零。

思路：

对于上一次收割天数都是 $d_0$ 的一段 $[l,r]$，若在 $d$ 天收割，则获得的作物是 $(d-d_0)\sum\limits^r_{i=l}i=\frac{(d-d_0)(l+r)(r-l+1)}{2}$。

我们需要维护一个数据结构，支持维护值域（$d$）相同的，连续的一段，以及区间赋值操作。这可以用珂朵莉树来解决。

复杂度分析：覆盖 $q$ 次，最多有 $O(q)$ 级别的块数，所以全局会被其它块给覆盖的块最多也只有 $O(q)$ 的级别，用 `set` 维护，插入删除一个块的复杂度都是 $O(\log q)$，所以总复杂度 $O(q\log q)$。

好暴力啊。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353, inv = 499122177;
struct node {
	ll l, r;
	mutable ll v;
	node(ll _l = -1, ll _r = -1, ll _v = -1) {
		l = _l, r = _r, v = _v;
	}
	bool operator < (const node &o) const {
		return l < o.l;
	}
};
multiset<node> T;
inline auto split(ll pos) {
	auto it = T.lower_bound(node(pos));
	if (it != T.end() && it->l == pos) return it;
	--it;
	node tmp(*it);
	T.erase(it);
	return (T.insert(node(tmp.l, pos - 1, tmp.v)), T.insert(node(pos, tmp.r, tmp.v)));
}
inline ll assign(ll l, ll r, ll v) {
	auto itr = split(r + 1), itl = split(l);
	ll res = 0;
	for (auto it = itl; it != itr; ++it) {
		res += (v - it->v) % mod * ((it->l + it->r) % mod) % mod * ((it->r - it->l + 1) % mod) % mod * inv % mod;
		res >= mod ? res -= mod : 0;
	}
	T.erase(itl, itr);
	T.insert(node(l, r, v));
	return res;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr);
	ll n, q;
	cin >> n >> q;
	T.insert(node(1, n, 0));
	while (q--) {
		ll v, l, r;
		cin >> v >> l >> r;
		cout << assign(l, r, v) << '\n';
	}
	return 0;
}

```

---

