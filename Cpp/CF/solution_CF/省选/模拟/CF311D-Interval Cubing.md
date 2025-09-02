# Interval Cubing

## 题目描述

While learning Computational Geometry, Tiny is simultaneously learning a useful data structure called segment tree or interval tree. He has scarcely grasped it when comes out a strange problem:

Given an integer sequence $ a_{1},a_{2},...,a_{n} $ . You should run $ q $ queries of two types:

1. Given two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ), ask the sum of all elements in the sequence $ a_{l},a_{l+1},...,a_{r} $ .
2. Given two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ), let each element $ x $ in the sequence $ a_{l},a_{l+1},...,a_{r} $ becomes $ x^{3} $ . In other words, apply an assignments $ a_{l}=a_{l}^{3},a_{l+1}=a_{l+1}^{3},...,a_{r}=a_{r}^{3} $ .

For every query of type 1, output the answer to it.

Tiny himself surely cannot work it out, so he asks you for help. In addition, Tiny is a prime lover. He tells you that because the answer may be too huge, you should only output it modulo $ 95542721 $ (this number is a prime number).

## 样例 #1

### 输入

```
8
1 2 3 4 5 6 7 8
5
1 2 5
2 2 5
1 2 5
2 3 6
1 4 7
```

### 输出

```
14
224
2215492
```

# 题解

## 作者：szh_AK_all (赞：3)

在 duel 中通过了此题。

注意到区间修改与区间查询，可以基本判断本题使用线段树解决。

但是区间修改是将区间内的所有数变为其三次方，这是个指数形式，再通过观察模数，不难联想到欧拉定理。也就是说存在一个数 $k$ 使得对于任意自然数 $a,b$ 都满足 $a^{3^b}\equiv a^{3^{b-k}} \pmod {95542721}$，也就是 $3^k\equiv 1 \pmod {\varphi(95542721)}$，而这个 $k$ 即可视为修改操作的“循环节”。通过枚举可知最小的合法 $k$ 为 $48$。

那么线段树上的操作便清晰起来了，我们对于每个 $0\le i\le 48$，维护每个区间 $[l,r]$ 的 $ans_i=\sum_{j=l}^r a_{j}^{3^i}$，在查询区间 $[l,r]$ 时答案即为 $\sum_{i=l}^r a_{i}^{3^0}$，在修改区间 $[l,r]$ 时即令每个子区间的 $ans_i=ans_{(i+1)\bmod 48}$，配套懒标记使用即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 95542721;
 
int qpow(int a, int b, int mod) {
	int ans = 1;
	while (b) {
		if (b % 2)
			ans = ans * a % mod;
		a =  a * a % mod;
		b /= 2;
	}
	return ans;
}
int a[100005], kk = 48;
 
struct node {
	int la, ans[50];
} t[400005];
 
void bu(int d, int l, int r) {
	if (l == r) {
		t[d].ans[0] = a[l];
		for (int i = 1; i <= kk; i++)
			t[d].ans[i] = qpow(t[d].ans[i - 1], 3, mod);
		return;
	}
	int mid = (l + r) / 2;
	bu(d * 2, l, mid);
	bu(d * 2 + 1, mid + 1, r);
	for (int i = 0; i <= kk; i++)
		t[d].ans[i] = t[d * 2].ans[i] + t[d * 2 + 1].ans[i], t[d].ans[i] %= mod;
}
 
void jia(int d, int x) {
	node a = t[d];
	for (int i = x, j = 0; i <= kk; i++, j++)
		t[d].ans[j] = t[d].ans[i];
	for (int i = kk - x, j = 0; i <= kk; i++, j++)
		t[d].ans[i] = a.ans[j];
	t[d].la += x, t[d].la %= kk;
}
 
void pushdown(int d) {
	if (!t[d].la)
		return;
	jia(d * 2, t[d].la);
	jia(d * 2 + 1, t[d].la);
	t[d].la = 0;
}
 
void add(int d, int l, int r, int ll, int rr) {
	if (ll <= l && r <= rr) {
		jia(d, 1);
		return;
	}
	pushdown(d);
	int mid = (l + r) / 2;
	if (ll <= mid)
		add(d * 2, l, mid, ll, rr);
	if (rr > mid)
		add(d * 2 + 1, mid + 1, r, ll, rr);
	for (int i = 0; i <= kk; i++)
		t[d].ans[i] = t[d * 2].ans[i] + t[d * 2 + 1].ans[i], t[d].ans[i] %= mod;
}
 
int ask(int d, int l, int r, int ll, int rr) {
	if (ll <= l && r <= rr)
		return t[d].ans[0];
	pushdown(d);
	int mid = (l + r) / 2, ans = 0;
	if (ll <= mid)
		ans += ask(d * 2, l, mid, ll, rr), ans %= mod;
	if (rr > mid)
		ans += ask(d * 2 + 1, mid + 1, r, ll, rr), ans %= mod;
	return ans;
}
 
signed main() {
	/*for (int i = 1;; i++)
		if (qpow(3, i, mod - 1) == 1) {
			cout << i;
			break;
		}48*/
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	bu(1, 1, n);
	int m;
	cin >> m;
	while (m--) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1)
			cout << ask(1, 1, n, l, r) << "\n";
		else
			add(1, 1, n, l, r);
	}
}
```

---

## 作者：LJ07 (赞：3)

简单题。

从特殊模数 $95542721$ 入手，套路地去思考是否存在循环节。

$a^{3^n} \equiv a\ (\bmod\ 95542721)$ 也就是 $3^n \equiv 1(\bmod\ 95542720)$。随便写个程序算一下发现当 $n=48$ 时，上式成立。

那么就容易了，直接用暴力分块维护（基本操作）。两端散块暴力修改，中间整块打标记。查询同理。

注意到修改散块的常数为 $48$，为了平衡散块修改和整块修改的复杂度，选择块长 $50$。（或者你用 $\sqrt \frac{n}{48}$ 也行）

代码挺短的，跑得也比几乎所有线段树做法快。

```cpp
#include <bits/stdc++.h>
#define GC c=getchar()
#define IG isdigit(c)
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
template<class T>void rd(T &x=0,char GC,bool f=1)
{
    for(x=0;!IG;GC)f=c!='-';for(;IG;GC)x=x*10+(c^48);x=f?x:-x;
}
template<class A,class... B>void rd(A& x,B&... y) {rd(x),rd(y...);}
using namespace std;
const int N(1e5+5),P(95542721),B(50);
int n,lab,q,a[N+5],b[50][N+5];
int tot,pos[N+5],L[N/B+5],R[N/B+5],s[50][N/B+5],tag[N+5];

int pw3(int x) {return 1ll*x*x%P*x%P;}
void inc(int &x,int y) {x+=y,x>=P?x-=P:1;}

void build() 
{
	while(R[tot]<n) ++tot,L[tot]=R[tot-1]+1,R[tot]=R[tot-1]+B;
	U(i,1,tot)
		U(j,L[i],R[i])
		{
			pos[j]=i;
			U(z,0,47) inc(s[z][i],b[z][j]),b[z+1][j]=pw3(b[z][j]);
		}
}

#define doit(k) {U(z,0,47) inc(s[z][k],P-b[z][i]),inc(s[z][k],b[z+1][i]),b[z][i]=b[z+1][i];b[48][i]=b[0][i];}

void mdy(int l,int r)
{
	int pl(pos[l]),pr(pos[r]);
	if(pl==pr) 
	{
		U(i,l,r) doit(pl);return ;
	}
	U(i,l,R[pl]) doit(pl);
	U(i,L[pr],r) doit(pr);
	U(i,pl+1,pr-1) ++tag[i];
}

int ask(int l,int r)
{
	int pl(pos[l]),pr(pos[r]),res(0);
	if(pl==pr)
	{
		U(i,l,r) inc(res,b[tag[pl]%48][i]);return res;
	} 
	U(i,l,R[pl]) inc(res,b[tag[pl]%48][i]);
	U(i,L[pr],r) inc(res,b[tag[pr]%48][i]);
	U(i,pl+1,pr-1) inc(res,s[tag[i]%48][i]);
	return res;
}
signed main()
{
	rd(n);
	U(i,1,n) rd(a[i]),b[0][i]=a[i]%P;
	build(),rd(q);
	while(q--)
	{
		int op,l,r; rd(op,l,r);
		if(op==1) printf("%d\n",ask(l,r));
		else mdy(l,r);
	}
    return 0;
}
```

---

## 作者：peterwuyihong (赞：2)

题意：区间变成自己的三次方，区间求和。

首先你发现这个模数很牛逼，你就开始探究这个模数的特性。。。

你经过不懈的打表，发现 $48$ 一循环，于是你带入验证。

$$a^{3^{48}}≡a \Leftrightarrow \varphi(p)|3^{48}-1$$

你打开 $\text{calc}$ 发现这是对的。

于是你使用线段树维护一波，开一个 $\text{sm}$ 表示区间和，一个 $\text{cnt}$ 表示被操作了几次，然后开 $48$ 棵线段树就行了。

各种忘了取模，大大地降智了。

```cpp
const int p=95542721;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
#define maxn 400010
int n,m,op,l,r;
int sm[maxn][48];
int uu[maxn];//tag
void pushup(int x){
	for(int i=0;i<48;i++)
	sm[x][i]=Add(sm[x<<1][(i+uu[x<<1])%48],sm[x<<1|1][(i+uu[x<<1|1])%48]);
}
void pushdown(int x){
	if(uu[x]){
		uu[x<<1]+=uu[x];
		uu[x<<1|1]+=uu[x];
		uu[x]=0;
		pushup(x);
	}
}
void build(int l,int r,int x=1){
	if(l==r){
		cin>>sm[x][0];sm[x][0]%=p;
		for(int i=1;i<48;i++)sm[x][i]=Mul(sm[x][i-1],Mul(sm[x][i-1],sm[x][i-1]));
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	pushup(x);
}
void change(int x,int y,int l=1,int r=n,int o=1){
	if(x<=l&&r<=y){
		uu[o]++;
		return;
	}
	pushdown(o);
	int mid=(l+r)>>1;
	if(x<=mid)change(x,y,l,mid,o<<1);
	if(y>mid)change(x,y,mid+1,r,o<<1|1);
	pushup(o);
}
int ask(int x,int y,int l=1,int r=n,int o=1){
	if(x<=l&&r<=y)return sm[o][uu[o]%48];
	pushdown(o);
	int mid=(l+r)>>1;
	int ans=0;
	if(x<=mid)add(ans,ask(x,y,l,mid,o<<1));
	if(y>mid)add(ans,ask(x,y,mid+1,r,o<<1|1));
	return ans;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	build(1,n,1);
	cin>>m;
	while(m--){
		cin>>op>>l>>r;
		if(op==1)cout<<ask(l,r)<<endl;
		else change(l,r);
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```

---

## 作者：Yansuan_HCl (赞：1)

每次把一段区间的指数乘 $3$。$p$ 是素数，指数可以对 $\varphi(p)=p-1$ 取膜。取膜之后，有长度为 $48$ 的循环节。

于是可以用分块进行维护。具体地，对每块求出整块操作 $k \in [0, 48)$ 次之后整块的和，散块操作时暴力重构。取块长为 $T$，则有 $48T=n/T$，平衡得到 $T=\sqrt{n/48}$ 时最优。

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF311D Interval Cubing](https://www.luogu.com.cn/problem/CF311D)

# 解题思路

实际上不难。

注意到特殊的模数，考虑是否会出现循环节。

然后打表发现循环节长度为 $48$。

那么我们显然使用分快维护块内乘了几次即可，因为有 $48$ 的极小循环节。

块长取 $50$ 显然是优秀的。

# 参考代码

```cpp
ll n,q;
ll a[100010][50];
ll sq;
ll L[100010],R[100010];
ll b[100010];
ll now[100010];
ll S[100010][50];
ll f(ll x)
{
    x%=mod;
    return x*x%mod*x%mod;
}
ll opt,l,r;
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    forl(i,1,n)
    {
        cin>>a[i][0];
        a[i][0]%=mod;
        forl(j,1,47)
            a[i][j]=f(a[i][j-1]);
    }
    sq=50;
    forl(i,1,n)
    {
        L[i]=R[i-1]+1,
        R[i]=min(n,sq*i);
        now[i]=0;
        forl(j,L[i],R[i])
        {
            b[j]=i;
            forl(k,0,47)
                S[i][k]=(S[i][k]+a[j][k])%mod;
                // cout<<a[j][k]<<'?';
        }
    //    cout<<S[i][0]<<' ';
        if(R[i]==n)
            break;
    }
    cout<<endl;
    // forl(i,1,n)
    //     cout<<b[i]<<' ';
    // cout<<endl;
    cin>>q;
    forl(_,1,q)
    {
        cin>>opt>>l>>r;
        if(opt==2)
        {
            if(b[l]==b[r])
            {
                forl(i,l,r)
                {
                    a[i][0]=f(a[i][0]);
                    forl(j,1,47)
                        a[i][j]=f(a[i][j-1]);
                }
                forl(j,0,47)
                    S[b[l]][j]=0;
                forl(j,L[b[l]],R[b[l]])
                    forl(k,0,47)
                        S[b[l]][k]=(S[b[l]][k]+a[j][k])%mod;
                continue;
            }
            forl(i,l,R[b[l]])
            {
                a[i][0]=f(a[i][0]);
                forl(j,1,47)
                    a[i][j]=f(a[i][j-1]);
            }

            forl(j,0,47)
                S[b[l]][j]=0;
            forl(j,L[b[l]],R[b[l]])
                forl(k,0,47)
                    S[b[l]][k]=(S[b[l]][k]+a[j][k])%mod;
                    
            forl(i,L[b[r]],r)
            {
                a[i][0]=f(a[i][0]);
                forl(j,1,47)
                    a[i][j]=f(a[i][j-1]);
            }
            forl(j,0,47)
                S[b[r]][j]=0;
            forl(j,L[b[r]],R[b[r]])
                forl(k,0,47)
                    S[b[r]][k]=(S[b[r]][k]+a[j][k])%mod;

            forl(i,b[l]+1,b[r]-1)
                now[i]=(now[i]+1)%48;
        }
        else
        {
            if(b[l]==b[r])
            {
                ll sum=0;
                forl(i,l,r)
                    sum=(sum+a[i][now[b[l]]])%mod;
                cout<<sum<<endl;
                continue;
            }
            ll sum=0;
            forl(i,l,R[b[l]])
                sum=(sum+a[i][now[b[l]]])%mod;
                // cout<<a[i][now[b[l]]]<<'>';
            forl(i,L[b[r]],r)
                sum=(sum+a[i][now[b[r]]])%mod;
                // cout<<a[i][now[b[r]]]<<'?';
            forl(i,b[l]+1,b[r]-1)
                sum=(sum+S[i][now[i]])%mod;
                // cout<<S[i][now[i]]<<'&';
            cout<<sum<<endl;
        }
    }
}
```

---

## 作者：xzzduang (赞：0)

[传送门](https://codeforces.com/problemset/problem/311/D)

一般我们见到这种题都会想到取立方操作在剩余系下会有循环节，但是就算找到了每个数的循环节，要用数据结构维护的话是要维护到这些循环节的 $lcm$ 的。

所以我们不妨考虑这个奇怪的 $95542721$ 的性质。

一个数 $a$ ，进行 $k$ 次操作后会变为 $a^{3^k}$ ，根据欧拉定理，如果 $3^k \equiv 1\ (mod\ \varphi(p))$ 就会出现循环节，经过巧妙的计（da）算（biao），得到 $k$ 为 $48$ 就满足了条件。

至于维护循环节，用线段树维护 $48$ 个 $sum$ 即可，具体见代码。

## $Code$
```cpp
#include<iostream>
#include<stdio.h>
#define N 100005
#define mo 95542721
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
struct segment_tree{
	int l,r,sum[50],lazy;
}d[4*N];
int n,a[N],tt[50];
int MOD(int x){return x>=mo?x-mo:x;}
void build(int k,int l,int r){
	d[k].l=l,d[k].r=r;
	if(l==r){
		d[k].sum[0]=a[l];
		for(int i=1;i<48;++i)
			d[k].sum[i]=d[k].sum[i-1]*d[k].sum[i-1]%mo*d[k].sum[i-1]%mo;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	for(int i=0;i<48;++i) d[k].sum[i]=MOD(d[ls].sum[i]+d[rs].sum[i]);
}
inline void rotate(int k,int v){
	for(int i=0;i<v;++i) tt[i]=d[k].sum[i];
	for(int i=v;i<48;++i) d[k].sum[i-v]=d[k].sum[i];
	for(int i=48-v;i<48;++i) d[k].sum[i]=tt[i-(48-v)];
}
inline void pushdown(int k){
	if(!d[k].lazy) return;
	rotate(ls,d[k].lazy),rotate(rs,d[k].lazy);
	d[ls].lazy+=d[k].lazy,d[rs].lazy+=d[k].lazy,d[k].lazy=0;
	if(d[ls].lazy>=48) d[ls].lazy-=48;
	if(d[rs].lazy>=48) d[rs].lazy-=48;
}
void update(int k,int x,int y){
	if(x<=d[k].l && d[k].r<=y){
		rotate(k,1);
		(d[k].lazy+=1)%=48;
		return;
	}
	pushdown(k);
	int mid=d[k].l+d[k].r>>1;
	if(x<=mid) update(ls,x,y);
	if(mid+1<=y) update(rs,x,y);
	for(int i=0;i<48;++i) d[k].sum[i]=MOD(d[ls].sum[i]+d[rs].sum[i]);
}
int query(int k,int x,int y){
	if(x<=d[k].l && d[k].r<=y) return d[k].sum[0];
	pushdown(k);
	int mid=d[k].l+d[k].r>>1,res=0;
	if(x<=mid) (res+=query(ls,x,y))%=mo;
	if(mid+1<=y) (res+=query(rs,x,y))%=mo;
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	build(1,1,n);
	int m=read();
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1) printf("%lld\n",query(1,l,r));
		else update(1,l,r);
	}
	return 0;
}

```


---

## 作者：Mobius127 (赞：0)

[题传](https://www.luogu.com.cn/problem/CF311D)


看到这种单个数值不断进行同一操作的大概率就有循环节了。。。

打表出来发现循环长度 $48$，珂是你还是一筹莫展呢：若把它丢到线段树上，区间立方操作直接打个标记，但是 $sum$ 就无法更新，怎么办？

为了解决这个问题，我们肯定不能只维护一个 $sum$，考虑记 $sum_{k, i}$ 为整个区间在**所有操作完成后**再右移 $i$ 次的区间和，$cnt_k$ 为该区间的右移标记（还未对 $sum_{k}$ 修改），考虑怎么合并：

$$\large sum_{k, i}=sum_{lc, i+cnt_{lc}}+sum_{rc, i+cnt_{rc}}$$

解释：由于 $cnt_{lc}$ 和 $cnt_{rc}$ 都还没下放，所以需要都加上。

那么这样在查询中，我们只需要返回 $sum_{k, cnt_{k}}$ 即可。

注意在 pushdown 后，由于我们在区间立方的时候只对 $cnt$ 进行了修改，没有修改 $sum$，所以需要重新 pushup 一遍。（其实也珂以在区间修改的时候重新 pushup，看个人习惯）

复杂度 $O(48 n \log n)$。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <stdlib.h>
#include <cctype>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mo=95542721;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)) f=(ch=='-'?-1:f), ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0', ch=getchar();
	return x*f;
}
inline int ksm(int a, int b){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%mo)
		if(b&1) ret=1ll*ret*a%mo;
	return ret;
}
const int N=1e5+5;
int n, m, a[N];
#define ls k<<1
#define rs k<<1|1
#define mid (l+r>>1)
int sum[N<<2][48], tag[N<<2];
void pushup(int k){
	for(int i=0; i<48; i++)
		sum[k][i]=(sum[ls][(i+tag[ls])%48]+sum[rs][(i+tag[rs])%48])%mo;
}
void upd(int k, int v){tag[k]=tag[k]+v;}
void pushdown(int k){
	if(!tag[k]) return ;
	upd(ls, tag[k]), upd(rs, tag[k]);
	tag[k]=0;pushup(k);
	return ;
}
void build(int k, int l, int r){
	if(l==r){
		sum[k][0]=a[l&r];
		for(int i=1; i<48; i++)
			sum[k][i]=ksm(sum[k][i-1], 3);
		return ;
	}
	build(ls, l, mid), build(rs, mid+1, r);
	return pushup(k);
}
void modify(int k, int l, int r, int x, int y){
	if(x<=l&&r<=y) return upd(k, 1);pushdown(k);
	if(x<=mid) modify(ls, l, mid, x, y);
	if(mid<y) modify(rs, mid+1, r, x, y);
	return pushup(k);
}
int query(int k, int l, int r, int x, int y){
	if(r<x||l>y) return 0;
	if(x<=l&&r<=y) return sum[k][tag[k]%48];pushdown(k);
	return (query(ls, l, mid, x, y)+query(rs, mid+1, r, x, y))%mo;
}
#undef ls
#undef rs
#undef mid
signed main(){
	n=read();
	for(int i=1; i<=n; i++) a[i]=read();
	build(1, 1, n);m=read();
	for(int i=1; i<=m; i++){
		int opt=read(), l=read(), r=read();
		if(opt&1) printf("%d\n", query(1, 1, n, l, r));
		else modify(1, 1, n, l, r);
	}
	return 0;
}

```


---

