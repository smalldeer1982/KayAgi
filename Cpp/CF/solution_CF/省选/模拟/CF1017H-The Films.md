# The Films

## 题目描述

在《高堡奇人》的世界中，有 $m$ 种不同的电影结局。

Abendsen 拥有一个仓库和一个书架。起初，他的书架上有 $n$ 部有序的电影。在第 $i$ 个月，他会进行如下操作：

1. 清空仓库。
2. 向仓库中放入 $k_i \cdot m$ 部电影，每种结局各放 $k_i$ 部。
3. 他会思考这样一个问题：如果他将书架上的所有电影都放入仓库，然后从仓库中随机取出 $n$ 部电影并重新排列到书架上，那么书架上区间 $[l_i, r_i]$ 的结局序列是否不会改变的概率是多少？注意，他只是思考这个问题，书架实际不会发生变化。

请回答 Abendsen 的所有问题。

设该概率为分数 $P_i$。假设对于第 $i$ 个月，从仓库中取出 $n$ 部电影的总方案数为 $A_i$，则 $P_i \cdot A_i$ 总是整数。请输出每个月的 $P_i \cdot A_i \bmod{998244353}$。

$998244353$ 是一个质数，等于 $119 \cdot 2^{23} + 1$。

保证 $k$ 的不同取值不超过 $100$ 个。

## 说明/提示

在第一个样例的第二个询问中，向仓库中加入 $2 \cdot m$ 部电影后，仓库中的电影为：$\{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4\}$。

共有 $26730$ 种方式选择电影，使得 $e_l, e_{l+1}, \ldots, e_r$ 的顺序不变，例如 $[1, 2, 3, 2, 2]$ 和 $[1, 2, 3, 4, 3]$ 都是这样的方式。

从仓库中取出 $n$ 部电影的总方案数为 $2162160$，所以你需要输出 $(\frac{26730}{2162160} \cdot 2162160) \bmod 998244353 = 26730$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 4 4
1 2 3 4 4 4
1 4 0
1 3 2
1 4 2
1 5 2
```

### 输出

```
6
26730
12150
4860
```

## 样例 #2

### 输入

```
5 5 3
1 2 3 4 5
1 2 100000
1 4 4
3 5 5
```

### 输出

```
494942218
13125
151632
```

# 题解

## 作者：周子衡 (赞：6)

我们先考虑怎么求单次询问的答案。

设颜色 $i$ 在原序列中总共出现了 $s_i$ 次，在给定的区间里出现了 $c_i$ 次。我们先把区间内的位置填好，这需要我们保持前后颜色一致，有 $\prod_{i=1}^m (s_i+k)^{\underline {c_i}}$ 种方案；接着区间外的位置可以随便填，一共是 $(mk+n-(r-l+1))^{\underline{n-(r-l+1)}}$ 种方案。两边相乘即可得到答案。

（$x^{\underline a}$ 表示 $x$ 的 $a$ 次下降幂，$x^{\underline a}=x(x-1)\cdots (x-a+1)$。）

下面的复杂度分析中用 $K$ 表示不同的 $k$ 的个数。由于 $K\leq 100$，一个很自然的想法是对每个 $k$ 的询问都分开处理，跑一遍莫队。总复杂度 $O(n\sqrt {qK})$，已经足以通过此题了。

另一个做法需要更多的观察。首先我们可以发现，$s_i$ 的不同非 $0$ 值不超过 $2\sqrt n$。这是因为 $\sum_{i=1}^ms_i=n$，若要出现 $x$ 个不同的非 $0$ 值则必有 $\sum_{i=1}^xi=\dfrac{x(x+1)}{2}\leq n$。进一步地，我们还可以发现如下结论：

- 对于每个询问区间 $[l,r]$，不同的 $(s_i,c_i)$ 的数对的数量不超过 $O(n^{2/3})$。

证明可以这么考虑：我们利用 $\sum s_i=n$，$\sum c_i=r-l+1\leq n$。若出现了 $t$ 对不同的 $(s,c)$，那么最优情况一定是按 $s+c$ 排序而优先选较小的。我们暂且不考虑 $c \leq s$，那么 $s+c=x$ 的 $(s,c)$ 数量恰有 $x$ 种。令 $k=\lfloor \sqrt n\rfloor$，那么可知

$$
\sum_{i=1}^k i^2\leq 2n
$$

我们知道左式 $=\dfrac{k(k-1)(2k-1)}{3}$，故得 $k=O(n^{1/3})$，所以 $t=O(n^{2/3})$，即证出原命题。

有了这个性质后事情变简单了。我们仍旧考虑莫队，用哈希表维护所有出现过的 $(s,c)$ 对的出现次数即可。对每组询问，我们暴力计算每个 $(s,c)$ 对的贡献，可以通过预处理阶乘及其逆元来完成计算。中间还要计算快速幂，总时间复杂度 $O(Kn+n\sqrt q+qn^{2/3}\log m)$。理论上这个复杂度较直接莫队优，但似乎由于常数问题并没有直接莫队快。

直接莫队的代码：

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

const long long MOD=998244353;
long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}
long long inv[500000];

int a[200000],cnt[200000],sum[200000];long long pre[200000];

struct query
{
	int l,r,k,id;
}Q[200000];
const int SZ=300;

bool operator<(query A,query B)
{
	if(A.k!=B.k)return A.k<B.k;
	if(A.l/SZ!=B.l/SZ)return A.l<B.l;return A.r<B.r;
}

long long ret[200000];

int main()
{
	for(int i=1;i<=450000;i++)inv[i]=INV(i);
	int n=0,m=0,q=0;scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[a[i]]++;
	for(int i=1;i<=q;i++)scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].k),Q[i].id=i;
	sort(Q+1,Q+q+1);
	long long ans=1;
	for(int i=1,l=1,r=0;i<=q;i++)
	{
		if(i==1||Q[i].k!=Q[i-1].k)
		{
			l=1,r=0,ans=1;for(int j=1;j<=m;j++)cnt[j]=0;
			pre[0]=1;long long p=(long long)m*Q[i].k%MOD;for(int j=1;j<=n;j++)pre[j]=pre[j-1]*(p+j)%MOD;
		}
		while(r<Q[i].r){r++;cnt[a[r]]++;ans=ans*(sum[a[r]]+Q[i].k-cnt[a[r]]+1)%MOD;}
		while(l>Q[i].l){l--;cnt[a[l]]++;ans=ans*(sum[a[l]]+Q[i].k-cnt[a[l]]+1)%MOD;}
		while(l<Q[i].l){ans=ans*inv[(sum[a[l]]+Q[i].k-cnt[a[l]]+1)]%MOD;cnt[a[l]]--;l++;}
		while(r>Q[i].r){ans=ans*inv[(sum[a[r]]+Q[i].k-cnt[a[r]]+1)]%MOD;cnt[a[r]]--;r--;}
		ret[Q[i].id]=ans*pre[n-(Q[i].r-Q[i].l+1)]%MOD;
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ret[i]);
}
```

---

## 作者：AsunderSquall (赞：2)

## 前言  

大家好我喜欢暴力所以我用暴力艹过了这道题。  
不过话说这道题本来的 tag 就是暴力来着？  
![](https://cdn.luogu.com.cn/upload/image_hosting/j7dr5nte.png)  

## 题意  
[较复杂，建议去看原题面](https://www.luogu.com.cn/problem/CF1017H)  

## 题解  

### 做法

> 保证不同的 $k$ 只有 $100$ 种。

于是想到把每种询问按照 $k$ 分组。  

我们先求出这个状态下，可重集 $S$ 中每种不同的数有几个，设 $x$ 出现了 $b[x]$ 次。  
然后我们考虑，假如一个区间中一个数 $x$ 出现了 $c[x]$ 次，那么我们需要在 $b[x]$ 中选 $c[x]$ 个进行排列，也就是 $b[x]^{\underline{c[x]}}$ 次。这个在 $c[x]$ 加一或者减一的时候可以 $O(1)$ 维护出来。  

于是我们想到用莫队。  
```cpp
void add(int x){res=1LL*res*(b[x]-c[x])%mod;c[x]++;}
void del(int x){c[x]--;res=1LL*res*inv[b[x]-c[x]]%mod;}
```
接下来还有一个问题就是，我们求得是钦定了 $[l,r]$ 区间内选的数的方案数，还有剩下随机排列的方案数要乘上去。  
令 $A=n+mk,L=r-l+1$。  
那么实际上要求的就是 $(A-L)^{\underline{n-L}}= \prod _{i=A-n+1}^{A-L} i$。这个可以对于每种 $k$ 预处理出来。  

### 复杂度分析  
为了方便我们设有 $K$ 种不同的 $k$，那么有 $K\le 100$。  
首先其他部分都是不超过 $O((n+m)k+q\log K)$ 的（求出现了哪些 $k$ 我用了 `set`），重点在于莫队的复杂度分析。  
  
假设对于每种 $k$，这样的询问共有 $q_1,q_2,\cdots q_K$ 个。  
莫队的复杂度为 $O(n \sqrt {q})$，因此总复杂度为 $O(n \sum_i \sqrt {q_i})$。  
有 $\sum_{q_i} =q$，显然所有 $q_i$ 相等复杂度最高，证明可以用权方和不等式，或者调整法感性理解。  
此时的复杂度为 $O(nK \sqrt { \frac q K})=O(n\sqrt {qK} )$，总复杂度为 $O(q\log K+(n+m)K+n \sqrt {qK})$，时限 5s 非常稳。  


### 代码  

稍微卡了下常数以后跑得飞快，甚至是 CF 上的最优解。  
<https://codeforces.com/contest/1017/submission/128020315>

```cpp

#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define rd(x) x=read()
#define wt(x) write(x)
#define pos(x) (((x)-1)/SZ+1)
#define endl "\n"
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define ls (rt<<1)
#define rs (rt<<1|1)
#define y1 _________
using namespace std;
const int N=2e5+5;
const int M=1e5+5;
int SZ=450;
const int mod=998244353;
int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}
int inv[N]; 
int n,m,q,ans[M],res;
int a[M],b[M],c[M],s[M];
struct query{int l,r,k,id;}Q[M];
set<int> K;
vector<query> p;
bool cmp(query x,query y){if (pos(x.l)!=pos(y.l)) return x.l<y.l;return pos(x.l)&1?x.r<y.r:x.r>y.r;}
void add(int x){res=1LL*res*(b[x]-c[x])%mod;c[x]++;}
void del(int x){c[x]--;res=1LL*res*inv[b[x]-c[x]]%mod;}
signed main()
{
    inv[1]=1;for (int i=2;i<N;i++) inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
    rd(n);rd(m);rd(q);
    for (int i=1;i<=n;i++) rd(a[i]);
    for (int i=1;i<=q;i++) rd(Q[i].l),rd(Q[i].r),rd(Q[i].k),Q[i].id=i,K.insert(Q[i].k);
    for (int k:K)
    {
        p.clear();for (int i=1;i<=q;i++) if (Q[i].k==k) p.push_back(Q[i]);
        memset(b,0,sizeof(b));memset(c,0,sizeof(c));for (int i=1;i<=n;i++) b[a[i]]++;for (int i=1;i<=m;i++) b[i]+=k;
        SZ=n/sqrt(p.size());SZ=max(SZ,3);
        sort(p.begin(),p.end(),cmp);
        int l=1,r=0;res=1;
        long long A=n+1LL*m*k;
        s[n]=1;for (int i=n-1;i>=0;i--) s[i]=1LL*s[i+1]*((A-i)%mod)%mod;
        for (query x:p)
        {
            while (l>x.l) add(a[--l]);
            while (l<x.l) del(a[l++]);
            while (r>x.r) del(a[r--]);
            while (r<x.r) add(a[++r]);
            int L=x.r-x.l+1;
            ans[x.id]=1LL*res*s[L]%mod;
        }
    }
    for (int i=1;i<=q;i++) cout<<ans[i]<<"\n";
}
```

---

## 作者：未来姚班zyl (赞：1)

- 设 $n,m,q$ 同阶，本题解复杂度为 $O(nK+n\sqrt{n\log n})$，应该算是爆标了。

我们先定义 $C_x$ 表示 $x$ 在 $a$ 中的出现次数，考虑如何计算答案。

首先，对于每个值 $x$，首先要在 $[l_i,r_i]$ 中找到它的出现次数 $ct_x$，把这些位置填满的方案数为 $\frac{(k+C_x)!}{(k+C_x-ct_x)!}$。

剩下的数随便填，设 $res_i=n-(r_i-l_i+1)$，则这一部分的方案数为 $\frac{(km+res_i)!}{(km)!}$。

所以总方案数 $ans_i$ 的表达式如下：

$$ans_i=\frac{(km+res_i)!}{(km)!}\prod\limits_{x=1}^m \frac{(k+C_x)!}{(k+C_x-ct_x)!}\\ =\frac{(km+res_i)!\prod\limits_{x=1}^m(k+C_x)!}{(km)!\prod\limits_{x=1}^m(k+C_x-ct_x)!} $$

容易发现除了右下角的那个求积式以外的部分，都可以对于每个 $k$ 预处理，做到 $O(nK)$，接下来我们来求右下角的式子：

$$W=\prod\limits_{x=1}^m(k+C_x-ct_x)!$$

和出现次数有关，我们考虑根号分治，设阈值为 $B$。

- $C_x\ge B$

则这样的 $x$ 个数 $\le \frac{n}{B}$，暴力前缀和求出 $ct_x$ 即可做到 $O(\frac{n^2}{B})$。

- $C_x<B$

则 $C_x-ct_x<B$，我们考虑对于每个 $w<B$ 求出有多少个 $ct_x=w$。

用一个链表结构记录对于每个位置 $i$，在它之前的第 $C_x-w$ 个 $a_i$ 出现的位置 $Pre_i$，在 $w$ 从 $0$ 枚举到 $B-1$ 的过程中，$Pre_i$ 均可借助链表 $O(1)$ 更新。设 $pre_i$ 和 $nxt_i$ 表示 $i$ 的前驱和后继（即相邻 $a_i$ 出现的位置）。

则每个位置 $x$ 会修改 $l_i\in(pre_{Pre_x},pre_x],r_i\in [x,nxt_x)$ 的询问，扫描线树状数组维护即可，复杂度 $O(nB\log n)$。

特别的，当 $w=C_x$ 的时候需要特殊处理，相当于 $ct_x=0$，贡献的形式也是二维数点，复杂度也和上面一样。

总复杂度 $O(nK+\frac{n^2}{B}+nB\log n)$，当 $B$ 取 $\sqrt\frac{n}{\log n}$ 时，有最优复杂度 $O(nK+n\sqrt{n\log n})$，空间精细实现可以 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,m
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=1e5+5,M=2e5+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
bool St;
int n,m,q,a[N],out[N],iv[M],ct[N];
struct node{
	int l,r,id;
}d[N];
vector<node>p[N],qs[N];
int exk[M],exl[M],fac[M],Iv[M];
const int B=80;
inline void solve(int k){
	int K=1;
	rep(i,1,k)Mul(K,i);
	exk[0]=K;
	repn(i)Mul(K,i+k),exk[i]=K;
	int Nw=Add(mul(k,m),1),S=1;
	exl[n]=S;
	repn(i)Mul(S,Nw),add(Nw,1),exl[n-i]=S;
	int W=1;
	repm(i)if(ct[i])Mul(W,exk[ct[i]]);
	for(auto nw:p[k])Mul(out[nw.id],mul(W,exl[nw.r-nw.l+1]));
}
int pr[N];
int st[105],tp,pre[N],Nw[N],ps[N],nxt[N],Tot[N],tot,fir[N];
bool Ed;
int t[N];
inline void ad(int x,int k){while(x<=n)t[x]+=k,x+=x&-x;}
inline int query(int x){int ans=0;while(x)ans+=t[x],x-=x&-x;return ans;}
inline void Solve(int x,int k){
	if(!x)return;
	if(Nw[x]<=0)return;
	if(Nw[x]>x)return;
	int le=pre[Nw[x]]+1,re=Nw[x];
	ad(le,k),ad(re+1,-k);
}
inline int getnx(int col,int w){
	if(w<-1)return w+1;
	if(w==-1)return fir[col];
	return nxt[w];
}
inline void Main(){
	fac[0]=1;
	rep(i,1,M-5)iv[i]=INV(i),fac[i]=mul(fac[i-1],i);
	Iv[M-5]=INV(fac[M-5]);
	per(i,M-6,0)Iv[i]=mul(Iv[i+1],i+1);
	n=read(),m=read(),q=read();
	repn(i)a[i]=read(),ct[a[i]]++;
	rep(i,1,q){
		int l=read(),r=read(),k=read();
		d[i]={l,r,k};
		p[k].pb({l,r,i}),out[i]=1,qs[r].pb({l,k,i});
	}
	repn(i)pre[i]=ps[a[i]],ps[a[i]]=i,Nw[i]=i;
	repm(i)ps[i]=n+1;
	per(i,n,1)nxt[i]=ps[a[i]],ps[a[i]]=i,fir[a[i]]=i;
	repm(x)if(ct[x]>=B){
		repn(i)pr[i]=pr[i-1]+(a[i]==x);
		rep(i,1,q){
			int l=d[i].l,r=d[i].r,k=d[i].id;
			Mul(out[i],Iv[k+ct[x]-(pr[r]-pr[l-1])]);
		}
	}else tot++;
	rep(w,0,100000)if(!p[w].empty())solve(w);
	repn(i){
		int p=pre[i];
		if(!p){
			if(ct[a[i]]==1)Nw[i]=i;
			else Nw[i]=-ct[a[i]]+1;
		}
		else Nw[i]=getnx(a[i],Nw[p]);
	}
	rep(c,0,B-1){
		repn(i)t[i]=0;
		repn(x){
			if(ct[a[x]]<B)Solve(pre[x],-1),Solve(x,1);
			for(auto nw:qs[x]){
				int l=nw.l,k=nw.r,id=nw.id,Ct=query(l);
				Mul(out[id],qp(Iv[k+c],Ct));
			}
		}
		repn(i)Nw[i]=getnx(a[i],Nw[i]);
	}
	
	rep(c,1,B-1){
		repn(i)t[i]=0;
		int Cnt=0;
		repm(i)if(ct[i]==c)ad(1,1),ad(fir[i],-1),Cnt++;
		repn(x){
			if(ct[a[x]]==c)ad(pre[x]+1,-1),ad(x,1);
			if(x>1&&ct[a[x-1]]==c)ad(x,1),ad(nxt[x-1],-1);
			for(auto nw:qs[x]){
				int l=nw.l,k=nw.r,id=nw.id,Ct=query(l);
				tot-=Ct;
				Mul(out[id],qp(Iv[k+c],Ct));
			}
		}
	}
	rep(i,1,q)pf(out[i]),puts("");
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

考虑令 $c_i$ 表示序列中 $i$ 元素的出现次数，对于一次询问 $l,r$，令 $d_i$ 表示 $a_l,a_{l+1},\cdots,a_r$ 中 $i$ 元素的出现次数。令 $A_n^m=\frac{n!}{(n-m)!}=n^{\underline{m}}$ 为从 $n$ 个数中选出 $m$ 个组成排列的方案数，那么 $[l,r]$ 询问的答案为：

$$\left(\prod\limits_{i=1}^mA_{k+c_i}^{d_i}\right)A_{n+mk-(r-l+1)}^{n-(r-l+1)}$$

我们发现对于相同的 $k$，排列数底下的数是相同的，并且括号右边乘上的排列数显然只和 $r-l+1$ 及询问区间长度有关。

注意到 $k$ 不超过 $100$ 种，这启示我们将询问按照 $k$ 分类。对于 $k$ 一定的询问，右边的部分可以 $O(n)$ 预处理出来。并且对于任意的 $i\in [1,m]$，$d_i\gets d_i+1$ 或者 $d_i\gets d_{i}-1$ 时，括号内的答案是好计算的。所以可以直接跑莫队，取两部分求乘积即可。

我们分析一下复杂度，设 $t$ 为 $k$ 的个数，$q_i(1\le i\le t)$ 表示第 $i$ 种 $k$ 的询问的个数，则 $\sum\limits_{i=1}^tq_i=q$。对于第 $i$ 个 $k$ 的询问我们取块长 $\frac{n}{\sqrt{q_i}}$ ，这部分的复杂度为 $O(n\sqrt{q_i})$，则我们关心 $\sum\limits_{i=1}^t\sqrt{q_i}$ 的**最大值**，而根据卡尔松不等式：

$$\begin{matrix}\underbrace{(1+1+\cdots +1)}\\t\end{matrix}\left(\sum\limits_{i=1}^tq_i\right)\ge \left(\sum\limits_{i=1}^t\sqrt{q_i}\right)^2$$

则 $\sum\limits_{i=1}^t \sqrt{q_i}\le \sqrt{t\left(\sum\limits_{i=1}^tq_i\right)}=\sqrt{tq}$，所以复杂度是 $O(n\sqrt{tq})$ 的，但是常数不大所以直接冲过去了。

（应该没有人和我一样唐到块长不小心取到了 $0$ 吧。）

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 3e5 + 100;
const int P = 998244353;

int n, m, q, len, t1, sum;
int t2[N], a[N], c[N], ct[N], ans[N], inv[N];

struct qry {
	int l, r, id;
	qry () { }
	qry (int _l, int _r, int _id) : l(_l), r(_r), id(_id) { }
	bool operator < (const qry &rhs) const {
		return l / len == rhs.l / len ? (((l / len) & 1) ? (r < rhs.r) : (r > rhs.r)) : l < rhs.l;
	}
};

vector<qry> qr[N];

int qpow(int p, int q) {
	int res = 1;
	for (; q; q >>= 1, p = 1ll * p * p % P)
		if (q & 1) res = 1ll * res * p % P;
	return res;
}

void init(int lim) {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= lim; i++)
		inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
}

void add(int id) { t1 = 1ll * t1 * (c[a[id]] - ct[a[id]]) % P, ct[a[id]]++; }
void del(int id) { ct[a[id]]--, t1 = 1ll * t1 * inv[c[a[id]] - ct[a[id]]] % P; }

int main() {
	n = rd(), m = rd(), q = rd(), init(3e5);
	for (int i = 1; i <= n; i++) a[i] = rd();
    for (int i = 1, l, r, k; i <= q; i++) {
    	l = rd(), r = rd(), k = rd();
    	qr[k].pb(qry(l, r, i));
    }
    for (int i = 0; i <= 2e5; i++) {
    	if (!qr[i].size()) continue;
    	memset(c, 0, sizeof(int) * (m + 10)), sum = 0;
    	for (int j = 1; j <= n; j++) c[a[j]]++;
    	for (int j = 1; j <= m; j++) c[j] += i, ct[j] = 0;
    	t2[n] = 1, sum = (n + 1ll * m * i % P) % P;
    	for (int j = n - 1, k = (sum - j + P) % P; j; j--, k = (k + 1) % P) 
    		t2[j] = 1ll * t2[j + 1] * k % P;
    	len = ceil(n / sqrt(qr[i].size()));
    	sort(qr[i].begin(), qr[i].end());
    	int l = t1 = 1, r = 0;
    	for (qry j : qr[i]) {
    		while (l > j.l) add(--l);
    		while (r < j.r) add(++r);
    		while (l < j.l) del(l++);
    		while (r > j.r) del(r--);
    		ans[j.id] = 1ll * t1 * t2[r - l + 1] % P;
    	}
    }
    for (int i = 1; i <= q; i++)
    	wr(ans[i]), pc('\n');
    return 0;
}
```

---

