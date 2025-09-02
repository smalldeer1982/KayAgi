# [ABC332F] Random Update Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc332/tasks/abc332_f

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。

$ A $ に対して、$ i\ =\ 1,\ 2,\ \ldots,\ M $ の順に下記の操作を行います。

- まず、$ L_i $ 以上 $ R_i $ 以下の整数を等確率でランダムに $ 1 $ 個を選び、それを $ p $ とおく。
- そして、$ A_p $ の値を整数 $ X_i $ に変更する。
 
上記の手順を行った後の最終的な $ A $ における、$ A_i $ の期待値 $ \text{mod\ }\ 998244353 $ を、 各 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について出力してください。

  期待値 $ \text{mod\ }\ 998244353 $ の定義この問題で求める期待値は必ず有理数になることが証明できます。 また、この問題の制約下では、求める期待値を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- 入力される値は全て整数
- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 0\ \leq\ X_i\ \leq\ 10^9 $
 
### Sample Explanation 1

$ A\ =\ (3,\ 1,\ 4,\ 1,\ 5) $ である初期状態からはじめ、下記の通りに $ 2 $ 個の操作が行われます。 - まず、$ 1 $ 個目の操作で、$ A_1 $ と $ A_2 $ のどちらか一方が等確率でランダムに選ばれ、その値が $ 2 $ に変更されます。 - その後、$ 2 $ 個目の操作で、$ A_2,\ A_3,\ A_4 $ のうちいずれか $ 1 $ 個が等確率でランダムに選ばれ、その値が $ 0 $ に変更されます。 その結果、最終的な $ A $ の各要素の期待値は $ (E_1,\ E_2,\ E_3,\ E_4,\ E_5)\ =\ (\frac{5}{2},\ 1,\ \frac{8}{3},\ \frac{2}{3},\ 5) $ です。

## 样例 #1

### 输入

```
5 2
3 1 4 1 5
1 2 2
2 4 0```

### 输出

```
499122179 1 665496238 665496236 5```

## 样例 #2

### 输入

```
2 4
1 2
1 1 3
2 2 4
1 1 5
2 2 6```

### 输出

```
5 6```

## 样例 #3

### 输入

```
20 20
998769066 273215338 827984962 78974225 994243956 791478211 891861897 680427073 993663022 219733184 570206440 43712322 66791680 164318676 209536492 137458233 289158777 461179891 612373851 330908158
12 18 769877494
9 13 689822685
6 13 180913148
2 16 525285434
2 14 98115570
14 17 622616620
8 12 476462455
13 17 872412050
14 15 564176146
7 13 143650548
2 5 180435257
4 10 82903366
1 2 643996562
8 10 262860196
10 14 624081934
11 13 581257775
9 19 381806138
3 12 427930466
6 19 18249485
14 19 682428942```

### 输出

```
821382814 987210378 819486592 142238362 447960587 678128197 687469071 405316549 318941070 457450677 426617745 712263899 939619994 228431878 307695685 196179692 241456697 12668393 685902422 330908158```

# 题解

## 作者：FFTotoro (赞：7)

对于单独一个元素，考虑一次操作的影响是什么：显然它有 $\frac{1}{r-l+1}$ 的概率被修改为 $x$，$\frac{r-l}{r-l+1}$ 的概率不变。所以其期望值的变化为 $E\leftarrow \frac{E(r-l)}{r-l+1}+\frac{x}{r-l+1}$。

对于一个区间上面的操作就是先乘再加，线段树板子。代码中使用 AtCoder Library 实现 `modint` 与线段树。

放代码：

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using M=atcoder::modint998244353;
struct S{M a; int s;};
struct F{M a,b;};
S o(S l,S r){return S{l.a+r.a,l.s+r.s};}
S e(){return S{0,0};}
S m(F l,S r){return S{r.a*l.a+r.s*l.b,r.s};}
F c(F l,F r){return F{l.a*r.a,r.b*l.a+l.b};}
F id(){return F{1,0};}
int main(){
  ios::sync_with_stdio(false);
  int n,q; cin>>n>>q;
  vector<S> d(n);
  for(auto &i:d){
    int x; cin>>x; i=S{x,1};
  } // 输入
  atcoder::lazy_segtree<S,o,e,F,m,c,id> t(d);
  while(q--){
    int l,r,x; cin>>l>>r>>x;
    t.apply(l-1,r,F{M(r-l)/M(r-l+1),M(x)/M(r-l+1)});
  } // 更新
  for(int i=0;i<n;i++)
    cout<<t.get(i).a.val()<<' '; // 输出
  cout<<endl;
  return 0;
}
```

---

## 作者：Milthm (赞：5)

当时，我打开了 D：好难写，不想写……

当时，我打开了 E：这怎么写，不会……

就在我以为我会掉大分时，我看到了站在光明中的 F……

_____

这题你只需要结合样例：

```
5 2
3 1 4 1 5
1 2 2
2 4 0
```
我们先看看，把 $[1,2]$ 改成了 $2$，此时 $1$ 号点的答案是 $3$ 的概率是这次修改改的是 $2$ 的概率，也就是 $\frac{1}{2}$。同样，这个点答案是 $2$ 的概率是此时改的是 $1$ 的概率，也就是 $\frac{1}{2}$
。二号点也基本同理。

再看第二个操作，此时我们着重看 $2$ 号点，这个点此时是 $0$ 的概率为 $\frac{1}{3}$，是 $2$ 的概率就是这个点没被这次操作覆盖的概率 $\frac{2}{3}$ 乘上上次修改覆盖了它的概率 $\frac{1}{2}$，是 $1$ 的概率就是这两次修改都没有修改它的概率，也就是 $\frac{2}{3}\times\frac{1}{2}$。结合这几个，就可以快速算出期望了。

发现了吗？假设当前进行的是第 $i$ 次操作，这个点此时是第 $j$ 次操作的修改的数的概率，就是这次修改的概率 $\frac{1}{r_j-l_j+1}$ 乘上对于所有的 $j+1\le k\le i$，$\frac{r_k-l_k}{r_k-l_k+1}$ 的值。

所以知道概率，推一下就可以得出期望值。如果当前该点的期望值为 $w$，经过第 $i$ 次操作之后，期望值就会变成 $\frac{w(r_i-l_i)}{r_i-l_i+1}+\frac{x_i}{r_i-l_i+1}$。

但这只是对于单点，直接暴力改会超时。但我们发现，这个除法可以通过逆元转换为乘法，然后就变成一个区间乘，区间加，单点查询的线段树板子了。

### AC code

```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define N 200005
using namespace std;
const int m=998244353;
int n,q,b[N],a[N*4],add[N*4],mul[N*4];
void build(int x,int l,int r){
	mul[x]=1;add[x]=0;
	if(l==r){
		a[x]=b[l]%m;return;
	}
	int mid=(l+r)>>1;
	build(x*2,l,mid);build(x*2+1,mid+1,r);
	a[x]=(a[x*2]+a[x*2+1])%m;
}
void pushdown(int x,int l,int r,int mid){
	a[x*2]=(a[x*2]*mul[x]+(mid-l+1)*add[x])%m,a[x*2+1]=(a[x*2+1]*mul[x]+(r-mid)*add[x])%m;
	mul[x*2]*=mul[x],mul[x*2+1]*=mul[x];
	add[x*2]=(add[x*2]*mul[x]+add[x])%m,add[x*2+1]=(add[x*2+1]*mul[x]+add[x])%m;
	mul[x]=1;add[x]=0;mul[x*2]%=m,mul[x*2+1]%=m;
}
void update(int x,int l,int r,int ql,int qr,int k,int op){
	if(ql<=l&&r<=qr){
		if(op==1)a[x]=a[x]*k%m,add[x]=add[x]*k%m,mul[x]=mul[x]*k%m;
		else a[x]=(a[x]+(r-l+1)*k)%m,add[x]=(add[x]+k)%m;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r,mid);
	if(ql<=mid)update(x*2,l,mid,ql,qr,k,op);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,k,op);
	a[x]=(a[x*2]+a[x*2+1])%m;
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return a[x];
	int mid=(l+r)>>1,sum=0;
	pushdown(x,l,r,mid);
	if(ql<=mid)sum=(sum+query(x*2,l,mid,ql,qr))%m;
	if(qr>mid)sum=(sum+query(x*2+1,mid+1,r,ql,qr))%m;
	return sum;
}
int qpow(int x,int y){
	int ans=1;x%=m;
	while(y){
		if(y&1)ans=ans*x%m;
		x=x*x%m;
		y>>=1;
	}
	return ans;
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i)scanf("%lld",&b[i]);
	build(1,1,n);
	while(q--){
		int x,l,r;
		scanf("%lld%lld%lld",&l,&r,&x);
		update(1,1,n,l,r,((r-l)*qpow(r-l+1,m-2))%m,1);
		update(1,1,n,l,r,x*qpow(r-l+1,m-2),0);
	}
	for(int i=1;i<=n;++i)printf("%lld ",query(1,1,n,i,i));
	return 0;
}
```




---

## 作者：yshpdyt (赞：4)

## 题意
长度为 $n$ 的序列 $a_i$，$m$ 次操作，每次操作选取一个区间 $[l,r]$，等概率的随机挑选区间内一个幸运元素更改为 $x$，求所有更改后每个元素的期望值。

## Sol
注：公式可能写出来比较复杂，感性理解一下。

众所周知，$E(X)=\sum P(X_i)\times X_i$，在该题中表现为该元素最终为 $X$ ，与最终结果为 $X$ 的概率 $P(X)$ 相乘，再把所有可能最终值的情况加起来。考虑如何计算一个值的被保留到最后的概率。

对于一次修改，区间内每个元素被更改的概率为 $\large{\frac{1}{r-l+1}}$，如果后续存在一次可能对该元素的修改操作，又有 $\large{\frac{1}{r'-l'+1}}$ 的概率被覆盖掉，则有 $\large{\frac{1}{r-l+1}} \times (\Large{\frac{r'-l'}{r'-l'+1}}) $ 的概率不会被覆盖掉，假设第 $j$ 次操作中元素 $i$ 可能被更新为 $x_j$，则该元素最终被保留的概率为：
$$\frac{1}{r_j-l_j+1}\times \prod _{k=j+1} ^m \frac{r_k-l_k}{r_k-l_k+1}\times[l_k\le i \le r_k]$$

单次修改期望为:
$$\frac{x_j}{r_j-l_j+1}\times \prod _{k=j+1} ^m \frac{r_k-l_k}{r_k-l_k+1}\times[l_k\le i \le r_k]$$

最后对于 $i$ 即求（注意到 $a_i$ 有一个初始值，可以认为是对区间$[i,i]$进行一次修改操作，设这次操作为第 $0$ 次操作）：

$$\large{\sum^m _{j=0}} \ \ [l_j\le i \le r_j]\times \frac{x_j}{r_j-l_j+1}\times \prod _{k=j+1} ^m \frac{r_k-l_k}{r_k-l_k+1}\times[l_k\le i \le r_k] $$

好像是用公式写出来是一坨复杂的式子，尝试变成方便维护的形式，为了方便表示，我们默认 $i$ 一定会被修改：
$$\frac{x_m}{r_m-l_m+1}+\frac{r_m-l_m}{r_m-l_m+1} \times \left( {\sum^{m-1} _{j=0}} \ \frac{x_j}{r_j-l_j+1}\times \prod _{k=j+1} ^{m-1} \frac{r_k-l_k}{r_k-l_k+1}\right) $$

看出什么规律了吗？如果没有，我们令 $\large{p_j=\frac{x_j}{r_j-l_j+1}}$，$\large{q_j=\frac{r_j-l_j}{r_j-l_j+1}}$ 并再次提出一个公因式：
$$p_m+q_m \times \left( 
p_{m-1}+q_{m-1}\times \left(
{\sum^{m-2} _{j=0}} \ \ p_j\times \prod _{k=j+1} ^{m-2}q_k\right)\right) $$

形式化一些，我们令 $f(j)$ 为 $j$ 次修改后的值，则 $f(j)=p_j+q_j\times f(j-1)$，发现每次修改都是在上一次的值后乘上一个东西，再加上一个东西。再回到我们的题目当中，对于修改一段区间，区间内的每个元素在这次操作中的的 $p_j$ 和 $q_j$ 都一样，那么我们可以维护一颗线段树，支持区间加和区间乘，以及单点查询。

每次修改，先给区间乘 $q_j$，然后再加 $p_j$，到最后每个元素单独输出即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 800005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll n,m;
ll c(ll x,ll y){//求逆元
    ll ans=1;
    while(y){
        if(y&1)ans=ans%mod*x%mod;
        y>>=1;
        x=x%mod*x%mod;
    }
    return ans;
}
namespace tr{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll f[N],lzy[N],lzt[N];
    // f 区间值
    // lzy 加法懒标记
    // lzt 乘法懒标记
    void lt(ll p,ll x,ll y,ll len){
        lzy[p]=lzy[p]*y+x;
        lzy[p]%=mod;
        lzt[p]*=y;
        lzt[p]%=mod;
        f[p]=(f[p]*y+x*len)%mod;
    }
    void pushdown(ll p,ll l,ll r){
        lt(ls,lzy[p],lzt[p],mid-l+1);
        lt(rs,lzy[p],lzt[p],r-mid);
        lzy[p]=0;
        lzt[p]=1;
    }
     void update1(ll p,ll l,ll r,ll le,ll ri,ll x){//加法
        if(ri>=r&&le<=l){
            lt(p,x,1,r-l+1);// *1+x;
            return ;
        }
        pushdown(p,l,r);
        if(le<=mid)update1(ls,l,mid,le,ri,x);
        if(ri>mid)update1(rs,mid+1,r,le,ri,x);
    }
    void update2(ll p,ll l,ll r,ll le,ll ri,ll x){//乘法
        if(ri>=r&&le<=l){
            lt(p,0,x,r-l+1);// *x+0
            return ;
        }
        pushdown(p,l,r);
        if(le<=mid)update2(ls,l,mid,le,ri,x);
        if(ri>mid)update2(rs,mid+1,r,le,ri,x);
    }
    ll ask(ll p,ll l,ll r,ll x){
        if(l==r)return f[p]%mod;
        pushdown(p,l,r);
        if(x<=mid)return ask(ls,l,mid,x)%mod;
        return ask(rs,mid+1,r,x)%mod;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    ll ct=0;
    for(int i=1;i<=n;i++){
        ll x;
        cin>>x;
        tr::update1(1,1,n,i,i,x);
    }
    for(int i=1;i<=m;i++){
        ll l,r,z;
        cin>>l>>r>>z;
        tr::update2(1,1,n,l,r,r-l);
        tr::update2(1,1,n,l,r,c(r-l+1,mod-2)%mod);
        tr::update1(1,1,n,l,r,z*c(r-l+1,mod-2)%mod);
    }
    for(int i=1;i<=n;i++)cout<<tr::ask(1,1,n,i)<<" ";

    return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

[整场题解](https://www.luogu.com.cn/blog/556362/abc-332-post)

题意：一个序列 $a$，每次 $l,r,x$ 表示从 $[l,r]$ 中随机选择一个数把它改成 $x$，求最后每个 $a_i$ 的期望。

简单题。容易想到不变的概率是 $\dfrac{r-l}{r-l+1}$，变的概率是 $\dfrac{1}{r-l+1}$，令原值为 $val$，答案就是 $val\times\dfrac{r-l}{r-l+1}+x\times\dfrac{1}{r-l+1}$，打棵线段树维护一下区间乘和区间加就行了。

最后注意一下，输出答案的时候不能直接输出叶子的值，因为标记会下放。

$O(M\log N)$。


---

## 作者：cjh20090318 (赞：1)

相对于过往比赛的 F 应该算正常难度，但是这个概率与期望相对于 E 的状态压缩动态规划要略简单一点。

## 题意

题意翻译很清楚。

## 分析

根据[期望的定义](https://oi-wiki.org/math/probability/exp-var/#期望)，$EX=\sum x_ip_i$。

对于第 $i$ 个数，第 $j$ 次操作，对于任意的 $L_j \le i \le R_j$，那么这一次操作选中一个数赋值的概率是 $P_j=\dfrac{1}{R_j-L_j+1}$，所以 $E_i = E_i(1-P_j)+X_jP_j$。

关注到这是一个区间加乘的操作，所以直接复制 [P2023 [AHOI2009] 维护序列](https://www.luogu.com.cn/problem/P2023) 的线段树模板就行。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define M(s) (s)%=p 
using namespace std;
typedef long long LL;
const LL p=998244353;
int n,m;
LL qpow(LL a,LL b){
	LL ret=1;
	for(;b;b>>=1,a=a*a%p)if(b&1)ret=ret*a%p;
	return ret%p;
}
LL a[200002],sum[800008];
LL add[800008],mul[800008];
void build(int rt,int l,int r){
	if(l==r){
		sum[rt]=a[l];
		mul[rt]=1;
		return;
	}
	int m=(l+r)/2;
	build(rt*2,l,m);
	build(rt*2+1,m+1,r);
	sum[rt]=sum[rt*2]+sum[rt*2+1];
	mul[rt]=mul[rt*2]=mul[rt*2+1]=1;
}
void push_down(int rt,int l,int r){
	int m=(l+r)/2;
	sum[rt*2]*=mul[rt];M(sum[rt*2]);
	sum[rt*2]+=add[rt]*(m-l+1);M(sum[rt*2]);
	add[rt*2]*=mul[rt];M(add[rt*2]);
	add[rt*2]+=add[rt];M(add[rt*2]);
	mul[rt*2]*=mul[rt];M(mul[rt*2]);
	sum[rt*2+1]*=mul[rt];M(sum[rt*2+1]);
	sum[rt*2+1]+=add[rt]*(r-m);M(sum[rt*2+1]);
	add[rt*2+1]*=mul[rt];M(add[rt*2+1]);
	add[rt*2+1]+=add[rt];M(add[rt*2+1]);
	mul[rt*2+1]*=mul[rt];M(mul[rt*2+1]);
	mul[rt]=1,add[rt]=0; 
}
void update(int rt,int l,int r,int L,int R,LL val,int op){
	if(L<=l && r<=R){
		if(op==0){
			sum[rt]+=val*(r-l+1);M(sum[rt]);
			add[rt]+=val;M(add[rt]);
		}
		else{
			sum[rt]*=val;M(sum[rt]);
			add[rt]*=val;M(add[rt]);
			mul[rt]*=val;M(mul[rt]);
		}
		return;
	}
	push_down(rt,l,r);
	int m=(l+r)/2;
	if(m>=L) update(rt*2,l,m,L,R,val,op);
	if(m<R) update(rt*2+1,m+1,r,L,R,val,op);
	sum[rt]=sum[rt*2]%p+sum[rt*2+1]%p;
	sum[rt]%=p;
}
LL query(int rt,int l,int r,int L,int R){
	if(L<=l && r<=R) return sum[rt];
	push_down(rt,l,r);
	int m=(l+r)/2;
	LL ret=0;
	if(L<=m){ret+=query(rt*2,l,m,L,R);M(ret);}
	if(m<R){ret+=query(rt*2+1,m+1,r,L,R);M(ret);}
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	for(int l,r,x;m--;){
		scanf("%d%d%d",&l,&r,&x);
		int len=r-l+1,inv=qpow(len,p-2);//求出 1/(r-l+1)。
		update(1,1,n,l,r,(LL)(len-1)*inv%p,1);//区间乘。
		update(1,1,n,l,r,(LL)x*inv%p,0);//区间加。
	}
	for(int i=1;i<=n;i++) printf("%lld ",query(1,1,n,i,i));
	return 0;
}
```



---

## 作者：Phartial (赞：1)

令 $E(A_i)=\displaystyle\sum_{v}P(A_i=v)v$ 表示 $A_i$ 的期望值。考虑一次操作 $(L,R,X)$ 对 $E(A_i)$ 的影响（设 $l=R-L+1$，$A'$ 表示操作前的值）：

- 如果 $i\not\in[L,R]$：显然 $E(A_i)$ 不变；
- 如果 $i\in[L,R]$：则 $A_i$ 有 $\dfrac{1}{l}$ 的概率被修改为 $X$，$\dfrac{l-1}{l}$ 的概率不变。于是有 $E(A_i)=\displaystyle\dfrac{1}{l}\cdot X+\sum_{v}\dfrac{l-1}{l}P(A'_i=v)v=\dfrac{X}{l}+\dfrac{l-1}{l}E(A'_i)$。

注意到这是一个区间乘与区间加的形式，使用线段树维护即可。

赞美 atcoder lib。

```cpp
#include <atcoder/all>
#include <iostream>

using namespace std;
using namespace atcoder;
using LL = modint998244353;
using T = pair<LL, LL>;

LL Pu(LL x, LL y) { return x + y; }
LL E() { return 0; }
LL Pt(T t, LL x) { return x * t.first + t.second; }
T Pa(T x, T y) { return T(x.first * y.first, x.first * y.second + x.second); }
T Id() { return T(1, 0); }

int n, q;
vector<LL> a;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 0, v; i < n; ++i) {
    cin >> v;
    a.push_back(v);
  }
  lazy_segtree<LL, Pu, E, T, Pt, Pa, Id> t(a);
  for (int l, r, x; q--; ) {
    cin >> l >> r >> x;
    LL le = r - l + 1;
    t.apply(l - 1, r, T((le - 1) / le, x / le));
  }
  for (int i = 0; i < n; ++i) {
    cout << t.get(i).val() << ' ';
  }
  return 0;
}
```


---

## 作者：1234567890sjx (赞：1)

令 $f_i$ 表示当前 $a_i$ 值的期望。

一开始显然有 $f_i=a_i$。

如果当前进行的第 $i$ 次操作为 $l_i\sim r_i$ 这一段区间等概率一个数变成 $v_i$，那么对于 $l_i\sim r_i$ 中的每一个 $j$，都有 $f_j=\frac{r_i-l_i+1}{r_i-l_i}\times f_j+\frac{r_i-l_i+1}{1}\times v_i$。

可以线性预处理逆元，时间复杂度 $O(nm)$，但是 $n,m\le 2\times 10^5$。

发现每一次维护的是一个区间，所以用一个可以维护区间加区间乘单点求值的线段树即可。时间复杂度 $O(m\log n)$。

---

## 作者：Vidoliga (赞：0)

赛时无脑做法。

考虑某个区间对一个点的贡献，不包含没贡献，否则在这之后的包含这个点的区间都需要不选择这个点。

从 $m \rightarrow 1$ 动态加点，线段树维护每个点在当前区间之后所有区间没选择当前点的概率。

需要支持的是，区间乘，最后查询单点历史版本乘 $x_i$ 和。

直接矩阵维护，复杂度 $O(n \log n)$。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define ll long long
//#define int ll
using namespace std;
const int N=2e5+20,M=1e6+20,mod=998244353;
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=1ll*res*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}return res;
}
int n,m,A[N],X[N],L[N],R[N];
struct Matrix{
	int g[2][2];
	inline void mem(){memset(g,0,sizeof(g));}
	inline void e(){g[0][0]=g[1][1]=1;g[0][1]=g[1][0]=0;}
	inline bool ise(){return (g[0][0]||g[1][1]||g[1][0]!=1||g[0][1]!=1)?0:1;}
	inline Matrix operator *(Matrix x){
		Matrix res;res.mem();
		for(int k=0;k<2;k++) for(int i=0;i<2;i++) for(int j=0;j<2;j++){
			res.g[i][j]=(res.g[i][j]+1ll*g[i][k]*x.g[k][j]%mod)%mod;
		}return res;
	}
	inline Matrix operator +(Matrix x){
		Matrix res;res.mem();
		for(int i=0;i<2;i++) for(int j=0;j<2;j++){
			res.g[i][j]=(g[i][j]+x.g[i][j])%mod;
		}return res;
	}
};
struct Seg{
	Matrix s[N<<2],tag[N<<2];
	inline void ph(int rt){s[rt]=s[rt<<1]+s[rt<<1|1];}
	inline void ptag(int rt,Matrix v){s[rt]=s[rt]*v;tag[rt]=tag[rt]*v;}
	inline void pd(int rt){
		if(tag[rt].ise()) return ;
		ptag(rt<<1,tag[rt]);ptag(rt<<1|1,tag[rt]);
		tag[rt].e();
	}
	inline void init(){for(int i=0;i<N<<2;i++) s[i].mem(),tag[i].e(),s[i].g[0][0]=1;}
	inline void upd(int rt,int l,int r,int ql,int qr,Matrix v){
		if(ql<=l&&r<=qr) return ptag(rt,v),void();
		int mid=(l+r)>>1;pd(rt);
		if(ql<=mid) upd(rt<<1,l,mid,ql,qr,v);
		if(qr>mid) upd(rt<<1|1,mid+1,r,ql,qr,v);
		ph(rt);
	}
	inline Matrix qry(int rt,int l,int r,int p){
		if(l==r) return s[rt];
		int mid=(l+r)>>1;pd(rt);
		if(p<=mid) return qry(rt<<1,l,mid,p);
		else return qry(rt<<1|1,mid+1,r,p);
	}
}tr;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>A[i];
	for(int i=1;i<=m;i++) cin>>L[i]>>R[i]>>X[i];
	tr.init(); 
	for(int i=m;i;i--){
		Matrix x;x.mem();
		int len=R[i]-L[i]+1;int p=qpow(len,mod-2);
		x.g[0][0]=1;x.g[1][1]=1;x.g[0][1]=1ll*X[i]*p%mod;
		tr.upd(1,1,n,L[i],R[i],x);
		////
		x.g[0][0]=1ll*p*(len-1)%mod;x.g[1][1]=1;x.g[0][1]=0;
		tr.upd(1,1,n,L[i],R[i],x);
//		for(int i=1;i<=n;i++) cout<<tr.qry(1,1,n,i).g[0][0]<<' ';cout<<'\n';
	}
	for(int i=1;i<=n;i++){
		Matrix x;x.mem();
		x.g[0][0]=1;x.g[1][1]=1;x.g[0][1]=A[i]%mod;
		tr.upd(1,1,n,i,i,x);
	}
	for(int i=1;i<=n;i++) cout<<tr.qry(1,1,n,i).g[0][1]<<' ';cout<<'\n';
	return 0;
}
////
```

---

## 作者：Genius_Star (赞：0)

### 思路：

挺简单的一题，大概上位绿左右吧。

定义 $E(i)$ 为第 $i$ 个数的期望，集合 $S_i$ 表示第 $i$ 个数可能的数的集合。

则：

$$E(i)=\sum\limits_{v \in S_i}v \times F(v) \times \neg F(v)$$

其中 $F(v)$ 表示 $v$ 出现的概率，$\neg F(v)$ 表示 $v$ 这个数不被其他数覆盖的概率。

容易知道：（其中 $j$ 表示 $v$ 是第 $j$ 次操作时覆盖的数字）

$$F(v)=\frac{1}{r_j-l_j+1}$$

$$\neg F(v)=\prod\limits_{k=j+1}^m \frac{r_k-l_k}{r_k-l_k+1} (l_k \le i \le r_k)$$

考虑用线段树维护上述这个式子：

- 对于区间 $[l,r]$ 每个数都乘上 $\frac{r_k-l_k}{r_k-l_k+1}$。

- 对于区间 $[l,r]$ 每个数都加上 $\frac{1}{r_j-l_j+1} \times x$。

记录一下加和乘的懒标记即可。

时间复杂度：$O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
struct Node{
	ll l,r,t,v;
	ll data;	
}X[4*N];
ll a[N],n,q,op,l,r,x,y,z,P;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	X[k].v=1;
	if(l==r){
		X[k].data=a[l];
		return ;
	}
	ll mid=(l+r)>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	X[k].data=X[k*2].data+X[k*2+1].data;
}
void down(ll k){
	X[k*2].data=((X[k*2].data*X[k].v)%P+(X[k].t*(X[k*2].r-X[k*2].l+1))%P)%P;
	X[k*2+1].data=((X[k*2+1].data*X[k].v)%P+(X[k].t*(X[k*2+1].r-X[k*2+1].l+1))%P)%P;
	X[k*2].v=(X[k*2].v*X[k].v)%P;
	X[k*2+1].v=(X[k*2+1].v*X[k].v)%P;
	X[k*2].t=((X[k*2].t*X[k].v)%P+X[k].t)%P;
	X[k*2+1].t=((X[k*2+1].t*X[k].v)%P+X[k].t)%P;
	X[k].t=0;
	X[k].v=1;
}
ll qurey(ll k,ll i){
	if(X[k].l==i&&X[k].r==i)
	  return X[k].data%P;
	down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  return qurey(k*2,i)%P;
	else if(i>mid)
	  return qurey(k*2+1,i)%P;
}
void add(ll k,ll l,ll r,ll v,bool f){
	if(X[k].l==l&&X[k].r==r){
		if(!f){
			X[k].data=(X[k].data+v*(X[k].r-X[k].l+1))%P;
			X[k].t=(X[k].t+v)%P;			
		}
		else{
			X[k].data=(X[k].data*v)%P;
			X[k].v=(X[k].v*v)%P;
			X[k].t=(X[k].t*v)%P;
		}
		return ;
	}
	down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  add(k*2,l,r,v,f);
	else if(l>mid)
	  add(k*2+1,l,r,v,f);
	else{
		add(k*2,l,mid,v,f);
		add(k*2+1,mid+1,r,v,f);
	}
	X[k].data=(X[k*2].data+X[k*2+1].data)%P;
}
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%P;
		a=(a*a)%P;
		b>>=1ll;
	}
	return ans;
}
int main(){
	n=read(),q=read(),P=998244353ll;
	for(int i=1;i<=n;i++)
	  a[i]=read()%P;
	build(1,1,n);
	while(q--){
		l=read(),r=read(),z=read();
		add(1,l,r,(qpow(r-l+1,P-2)*(r-l))%P,1);
		add(1,l,r,(qpow(r-l+1,P-2)*z)%P,0);
	}
	for(int i=1;i<=n;i++){
		write(qurey(1,i));
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：qejwdi (赞：0)

我们令 $f_i$ 表示 $A_i$ 最后的期望。

那么考虑一个操作 $(L_i,R_i)$ 对 $f$ 的影响。

因为只更改了 $L_i$ 到 $R_i$ 的数，因此只对这段的 $f$ 有影响。

那么对于 $x \in [L_i,R_i]$，$A_x$ 有 $\frac{1}{R_i-L_i+1}$ 的概率变成 $X_i$，有 $\frac{R_i-L_i}{R_i-L_i+1}$ 的概率不变。即 $f_x=\frac{R_i-L_i}{R_i-L_i+1}f_x+\frac{1}{R_i-L_i+1}X_i$。

那么我们这段区间所有的 $f$ 乘上一个 $\frac{R_i-L_i}{R_i-L_i+1}$，在加上一个 $\frac{1}{R_i-L_i+1}X_i$ 即可。


---

## 作者：xzf_200906 (赞：0)

考虑对于位置 $i$，第 $j$ 个操作被计入答案当且仅当第 $j$ 个操作正好修改到位置 $i$ 且之后所有的操作都没有修改到位置 $i$。记 $len_j=R_j-L_j+1$，那么第 $j$ 次操作修改到某一特定位置的概率为 $\dfrac{1}{len_j}$，未能修改到该位置的概率为 $\dfrac{len_j-1}{len_j}$。则对于 $[L_j,R_j]$ 内的位置 $x$ 的期望值 $E(x) \gets E(x) \times \dfrac{len_j-1}{len_j} + \dfrac{X_j}{len_j}$。于是我们需要一个支持区间乘，区间加，单点查询的数据结构，即[线段树2](https://www.luogu.com.cn/problem/P3373)。

仅供参考的代码：
```c++
#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int qp(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=1ll*ret*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ret;
}
int tree[5000000],add[5000000],mul[5000000];
signed a[5000000];
void dn(int p,int ll,int rr){
    int mid=(ll+rr)>>1;
    mul[(p<<1)]=(mul[(p<<1)]*mul[p])%mod;
    add[(p<<1)]=(add[(p<<1)]*mul[p])%mod;
    tree[(p<<1)]=(tree[(p<<1)]*mul[p])%mod;
    mul[(p<<1)|1]=(mul[(p<<1)|1]*mul[p])%mod;
    add[(p<<1)|1]=(add[(p<<1)|1]*mul[p])%mod;
    tree[(p<<1)|1]=(tree[(p<<1)|1]*mul[p])%mod;
    mul[p]=1;
    add[(p<<1)]=(add[(p<<1)]+add[p])%mod;
    tree[(p<<1)]=(tree[(p<<1)]+add[p]*(mid-ll+1)%mod)%mod;
    add[(p<<1)|1]=(add[(p<<1)|1]+add[p])%mod;
    tree[(p<<1)|1]=(tree[(p<<1)|1]+add[p]*(rr-mid)%mod)%mod;
    add[p]=0;
}
void up(int p){
    tree[p]=(tree[(p<<1)]+tree[(p<<1)|1])%mod;
}
void build(int p,int l,int r){
    mul[p]=1;
    if(l==r){
        tree[p]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build((p<<1),l,mid);
    build((p<<1)|1,mid+1,r);
    up(p);
}
void add_(int p,int ll,int rr,int l,int r,int num){
    dn(p,ll,rr);
    if(l<=ll&&r>=rr){
        tree[p]+=num*(rr-ll+1);
        add[p]+=num;
        return;
    }
    int mid=(ll+rr)>>1;
    if(l<=mid) add_((p<<1),ll,mid,l,r,num);
    if(r>mid) add_((p<<1)|1,mid+1,rr,l,r,num);
    up(p);
}
void mul_(int p,int ll,int rr,int l,int r,int num){
    dn(p,ll,rr);
    if(l<=ll&&r>=rr){
        tree[p]=(tree[p]*num)%mod;
        add[p]=(add[p]*num)%mod;
        mul[p]=(mul[p]*num)%mod;
        return;
    }
    int mid=(ll+rr)>>1;
    if(l<=mid) mul_((p<<1),ll,mid,l,r,num);
    if(r>mid) mul_((p<<1)|1,mid+1,rr,l,r,num);
    up(p);
}
int query(int p,int ll,int rr,int l,int r){
    if(l<=ll&&r>=rr) return tree[p]%mod;
    dn(p,ll,rr);
    int mid=(ll+rr)>>1,res=0;
    if(l<=mid) res+=query((p<<1),ll,mid,l,r);
    if(r>mid) res+=query((p<<1)|1,mid+1,rr,l,r);
    return res%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(m--){
        int l,r,x;
        cin>>l>>r>>x;
        mul_(1,1,n,l,r,(1-qp((r-l+1),mod-2)+mod)%mod);
        add_(1,1,n,l,r,qp((r-l+1),mod-2)*x%mod);
    }
    for(int i=1;i<=n;i++) cout<<query(1,1,n,i,i)<<' ';
    return 0;
}
```

---

## 作者：CWzwz (赞：0)

[ABC332F Random Update Query](https://www.luogu.com.cn/problem/AT_abc332_f) 题解

[AtCoder](https://atcoder.jp/contests/abc332/tasks/abc332_f)

在学校打的，切 ABCF 直接摆烂，D 题暴搜调不出来，很难蚌。

------------

给你一个序列 $a_i$，$m$ 次操作，第 $i$ 次将 $[l_i,r_i]$ 区间内等概率随机的一个数修改为 $x_i$，最后求每个数值的期望。

假定一个元素，当前的期望是 $a$，考虑执行一个参数为 `l r x` 的修改。

那么它有 $\frac{1}{r-l+1}$ 概率被修改为 $x$，有 $\frac{r-l}{r-l+1}$ 概率不变。则新的期望 $\frac{r-l}{r-l+1}\times a+\frac{x}{r-l+1}$。

注意到这相当于乘上 $\frac{r-l}{r-l+1}$ 再加上 $\frac{x}{r-l+1}$，线段树可做，和 [线段树2](https://www.luogu.com.cn/problem/P3373) 本质相同；除法就写 exgcd 求逆元即可。

时间复杂度 $O(n \log n + m \log n)$。只求了 $r-l+1$ 的逆元，所以逆元复杂度是 $O(\log n)$。

------------

```cpp
#include<iostream>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
typedef __int128 ll;
typedef __int128 typ;
const int N = 2e5 + 10;
const ll mod = 998244353;
typ read(){typ x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(typ x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}
char gc(){char c=getchar();while(c==' '||c=='\n')c=getchar();return c;}
void pc(char Char){std::putchar(Char);}

int n, m;
ll a[N];

void exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll x) {
    ll tmp1, tmp2;
    exgcd(x, mod, tmp1, tmp2);
    return tmp1 % mod;
}

struct segt {
	struct node {
		ll s, tg, tg1;
	} t[N << 2];
	void pushup(int u) {    
		t[u].s = (t[u << 1].s + t[u << 1 | 1].s) % mod;
	}
	void pushdown(int u, int l, int r) {
		int mid = l + r >> 1;
		t[u << 1].tg *= t[u].tg1; t[u << 1].tg %= mod;
		t[u << 1].tg1 *= t[u].tg1; t[u << 1].tg1 %= mod;
		t[u << 1 | 1].tg *= t[u].tg1; t[u << 1 | 1].tg %= mod;
		t[u << 1 | 1].tg1 *= t[u].tg1; t[u << 1 | 1].tg1 %= mod;
		t[u << 1].s *= t[u].tg1; t[u << 1].s %= mod;
		t[u << 1 | 1].s *= t[u].tg1; t[u << 1 | 1].s %= mod;
		t[u].tg1 = 1;
		t[u << 1].tg += t[u].tg; t[u << 1].tg %= mod;
		t[u << 1 | 1].tg += t[u].tg; t[u << 1 | 1].tg %= mod;
		t[u << 1].s += (mid - l + 1) * t[u].tg; t[u << 1].s %= mod;
		t[u << 1 | 1].s += (r - mid) * t[u].tg; t[u << 1 | 1].s %= mod;
		t[u].tg = 0;
	}
	void build(int u, int l, int r) {
        t[u].tg1 = 1;
		if(l == r) {
			t[u].s = a[l] % mod;
		} else {
			int mid = l + r >> 1;
			build(u << 1, l, mid);
			build(u << 1 | 1, mid + 1, r);
			pushup(u);
		}
	}
	void update(int u, int l, int r, int L, int R, ll val) { // +
		if(L <= l && r <= R) {
			t[u].tg += val; t[u].tg %= mod;
			t[u].s += val * (r - l + 1); t[u].s %= mod;
		} else {
			pushdown(u, l, r);
			int mid = l + r >> 1;
			if (L <= mid) update(u << 1, l, mid, L, R, val);
			if (mid < R) update(u << 1 | 1, mid + 1, r, L, R, val);
			pushup(u);
		}
	}
	void update1(int u, int l, int r, int L, int R, ll val) { // *
		if(L <= l && r <= R) {
			t[u].tg1 *= val; t[u].tg1 %= mod;
			t[u].tg *= val; t[u].tg %= mod;
			t[u].s *= val; t[u].s %= mod;
		} else {
			pushdown(u, l, r);
			int mid = l + r >> 1;
			if (L <= mid) update1(u << 1, l, mid, L, R, val);
			if (mid < R) update1(u << 1 | 1, mid + 1, r, L, R, val);
			pushup(u);
		}
	}
	ll query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return t[u].s % mod;
		} else {
			pushdown(u, l, r);
			int mid = l + r >> 1;
			ll res = 0;
			if (L <= mid) res += query(u << 1, l, mid, L, R);
			if (mid < R) res += query(u << 1 | 1, mid + 1, r, L, R);
			return res % mod;
		}
	}
} T;

int main() {
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) a[i] = read();
    T.build(1, 1, n);
    for(int i = 1; i <= m; i++) {
        ll l = read(), r = read(), x = read();
        T.update1(1, 1, n, l, r, (r - l) * inv(r - l + 1) % mod);
        T.update(1, 1, n, l, r, x * inv(r - l + 1) % mod);
    }
    for(int i = 1; i <= n; i++) {
        print((T.query(1, 1, n, i, i) + 2 * mod) % mod); pc(' ');
    }
    return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

考虑一次操作对区间内每个数的影响。

对于每个数都有 $\dfrac{R-L}{R-L+1}$ 的概率不变，还有 $\dfrac1{R-L+1}$ 的概率变为为 $X$。

那么期望值就变为 $\text{原来的期望值}\times \dfrac{R-L}{R-L+1}+\dfrac{X}{R-L+1}$。

线段树维护区间乘、区间加即可，时间复杂度 $O(M\log N)$。

# Code
```c++
#include<bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;
const int mod=998244353;
const int N=8e5;
int add[N],mul[N];
int n,m,a[N];

int power(int a,int b)
{
	int ans=1;
	while (b) {
		if (b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return ans;
}
void update(int rt,int l,int r,int x,int y) {
	mul[rt]=1ll*mul[rt]*x%mod,add[rt]=(1ll*add[rt]*x%mod+y)%mod;
}
void pushdown(int rt,int l,int r) {
	update(rt<<1,l,mid,mul[rt],add[rt]);
	update(rt<<1|1,mid+1,r,mul[rt],add[rt]);
	mul[rt]=1,add[rt]=0;
}
void modify(int rt,int l,int r,int s,int t,int x,int y)
{
	if (s<=l&&r<=t) return update(rt,l,r,x,y);
	pushdown(rt,l,r);
	if (s<=mid) modify(rt<<1,l,mid,s,t,x,y);
	if (mid<t) modify(rt<<1|1,mid+1,r,s,t,x,y);
}
void print(int rt,int l,int r) {
	if (l==r) return printf("%d ",(1ll*a[l]*mul[rt]%mod+add[rt])%mod),void();
	pushdown(rt,l,r),print(rt<<1,l,mid),print(rt<<1|1,mid+1,r);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	for (int i=1;i<n<<2;i++) mul[i]=1;
	while (m--) {
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		int inv=power(r-l+1,mod-2);
		modify(1,1,n,l,r,1ll*(r-l)*inv%mod,1ll*x*inv%mod);
	}
	print(1,1,n);
	return 0;
}
```

---

