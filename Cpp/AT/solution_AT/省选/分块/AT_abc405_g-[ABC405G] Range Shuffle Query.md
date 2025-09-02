# [ABC405G] Range Shuffle Query

## 题目描述

给你一个长为 $N$ 的数列 $A=(A_1,A_2,\cdots,A_N)$，你要回答 $Q$ 个询问。

每个询问有三个参数 $(L_i,R_i,X_i)$，你需要回答：

令 $B=(A_{L_i},A_{L_i+1},\cdots,A_{R_i})$，删除 $B$ 中 $\ge X_i$ 的所有元素后，通过重新排列 $B$ 的元素可以形成多少种不同的 $B$？

答案对 $998244353$ 取模。

## 说明/提示

**样例 1 解释**

对于第一个询问，$B$ 的三种可能分别为：$B=(1,1,2),B=(1,2,1),B=(2,1,1)$。\
对于第二个询问，$B$ 的唯一可能为空串。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
5 3
1 2 3 3 1
1 5 3
3 4 1
1 3 4```

### 输出

```
3
1
6```

## 样例 #2

### 输入

```
8 6
6 2 4 1 5 1 8 6
5 6 3
1 5 7
1 4 6
4 7 8
4 8 2
5 8 6```

### 输出

```
1
120
6
3
1
2```

# 题解

## 作者：Milthm (赞：3)

不会 E 但会 G 是什么水平……

___

拿到题，发现是 $q$ 次询问没有修改，结合 $2.5\times 10^5$ 的不明数据范围，启示我们正解可能是莫队。

首先先想如何统计答案，如果区间出现了 $x$ 个比 $X$ 小的数，那么有 $x!$ 种排列方式，但是这样算会算重。具体来说，对于每个数 $i$，如果它出现了 $cnt_i$ 次，则它的 $cnt_i!$ 种不同的排列方式都被统计到了答案里。所以正确的答案是 $\frac{x}{\prod cnt_i}$。

那我们就可以莫队了，用树状数组可以实现 $O(\log n)$ 的维护，但是这样时间复杂度是 $O(n\sqrt n \log n)$，是无法通过的。于是我们再仔细想想我们要干什么：

- 单点修改 $cnt_i$。

- 查询 $1\le i <X$ 的 $cnt_i$ 之积。

- 查询 $1\le i <X$ 的 $cnt_i$ 之和。

注意到这三个操作中，后两个只会执行 $O(n)$ 次（视 $n,q$ 同阶，以下也如此），但第一个会执行 $n\sqrt n$ 次，如果我们都用 $O(\log n)$ 的时间复杂度来执行，那么看起来有些亏。如果我们能有一个可以 $O(1)$ 实现第一个操作，$O(\sqrt n)$ 实现后两个操作的东西就好了。

这个东西当然是有的，它的名字叫分块。具体来说，我们将值域分为 $O(\sqrt n)$ 块，在块上维护块内元素的和以及积。每次单点修改的时候，我们修改单点，并修改整块的和以及积。查询的时候，我们遍历之前的所有块，累计答案，再遍历最后剩下的一点，累计答案。这样就达到了我们的目标。

于是做完了，代码十分好写，但是有点卡常，如果卡不过去可以试试不要 `#define int long long`。


```cpp
#include<bits/stdc++.h>
#define N 250005
using namespace std;
const int mod=998244353;
int n,m,c[N],siz,sum,cnt[N],f[N],inv[N],ans[N];
struct yhb{
	int l,r,x,id;
}a[N];
int cmp(yhb x,yhb y){
	if(x.l/siz!=y.l/siz)return x.l<y.l;
	return (x.l/siz)&1?x.r<y.r:x.r>y.r;
}
int id(int x){
	return (x-1)/siz+1;
}
struct bl{
	int c[N],f[N];
	bl(){
		for(int i=1;i<N;++i)c[i]=f[i]=1;
	}
	void add(int x,int k){
		c[x]=1ll*c[x]*k%mod;f[id(x)]=1ll*f[id(x)]*k%mod;
	}
	int ask(int x){
		int lim=id(x),ans=1;
		for(int i=1;i<lim;++i)ans=1ll*ans*f[i]%mod;
		for(int i=(lim-1)*siz+1;i<=x;++i)ans=1ll*ans*c[i]%mod;
		return ans;
	}
}A;
struct bl2{
	int c[N],f[N];
	bl2(){
		for(int i=1;i<N;++i)c[i]=f[i]=0;
	}
	void add(int x,int k){
		c[x]+=k;f[id(x)]+=k; 
	}
	int ask(int x){
		int lim=id(x),ans=0;
		for(int i=1;i<lim;++i)ans+=f[i];
		for(int i=(lim-1)*siz+1;i<=x;++i)ans+=c[i];
		return ans;
	}
}B;
void add(int x){
	B.add(x,1);A.add(x,B.c[x]);
}
void del(int x){
	A.add(x,inv[B.c[x]]);B.add(x,-1);
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;siz=sqrt(n);
	for(int i=1;i<=n;++i)cin>>c[i];
	f[0]=inv[1]=1;
	for(int i=1;i<=n;++i)f[i]=1ll*f[i-1]*i%mod;
	for(int i=2;i<=n;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=m;++i)cin>>a[i].l>>a[i].r>>a[i].x,a[i].id=i;
	sort(a+1,a+m+1,cmp);
	int l=2,r=1;
	for(int i=1;i<=m;++i){
		while(l>a[i].l)add(c[--l]);
		while(r<a[i].r)add(c[++r]);
		while(l<a[i].l)del(c[l++]);
		while(r>a[i].r)del(c[r--]);
		ans[a[i].id]=1ll*f[B.ask(a[i].x-1)]*qpow(A.ask(a[i].x-1),mod-2)%mod;
	}
	for(int i=1;i<=m;++i)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：aaron0919 (赞：2)

# ABC405_G の题解

极限 $4$ 发罚时 $96:08$ 时 $\text{AC}$。

歪果仁不怎么擅长莫队，水了个 $\text{Rank}~109$。

## 引入

这题一看就不是什么高级数据结构，没有修改，允许离线。

考虑怎么计算答案，令 $C_i$ 表示数 $i$ 的出现次数。

那么答案就等于：

$$
Ans=\dfrac{\left(\sum_{i=1}^{X-1}C_i\right)!}{\Pi_{i=1}^{X-1}\left(C_i\right)!}
$$

这是显然的，即全排列中去掉相同的元素的排列。

考虑使用莫队，直接维护每种数产生的贡献。

## 实现

首先，在此强调：**莫队的移动指针要求 $O(1)$ 实现**。

其次，在此强调：**莫队的移动指针要求 $O(1)$ 实现**。

最后，在此强调：**莫队的移动指针要求 $O(1)$ 实现**。

由于有 $\sum_{i=1}^{X-1}$ 这种东西，我们需要一个能支持单点修改，区间求和求积的东西。

~~一眼树状数组，[T 飞了](https://atcoder.jp/contests/abc405/submissions/65688853)。~~

我们来看一下复杂度。

因为莫队经过分块，需要 $O(M\sqrt{N})$ 次移动指针，和 $O(M)$ 次查询。

如果我们移动指针不是 $O(1)$ 的话，那么就会炸。

所以我们考虑实现一个这样的数据结构：

- $O(M\sqrt{N})$ 次移动指针：$O(1)$ 修改；
- $O(M)$ 次查询：$O(\sqrt{N})$ 区间求和。

看出来了吗，就是分块。

这样就能平衡复杂度到 $O(M\sqrt{N})$。

## 细节

需要预处理逆元，因为需要 $O(1)$ 修改（因为这个吃了 $3$ 发罚时）。

## Code

赛时乱敲的，精神状态不好，但应该看得懂。

[Link](https://atcoder.jp/contests/abc405/submissions/65691867)。

---

## 作者：Crazyouth (赞：1)

## 分析

一个可重集 $S$ 的不同排列方式是 $\frac{|S|!}{\displaystyle\prod_{i\in S}cnt_i!}$，其中 $cnt_i$ 为 $i$ 在 $S$ 中的数量。也就是我们只需要求出询问区间的小于 $x$ 的数的 $cnt$ 的阶乘之积和它们的数量即可求得答案。发现题目中 $n$ 的范围开根号是整数，考虑根号做法，于是想到了莫队。但是我们发现莫队指针移动要是 $O(1)$ 的，所以我们也需要一个修改 $O(1)$，询问复杂度乘 $q$ 能通过的，发现这不就是分块嘛，所以用分块记录上面说的两个东西，查询的时候暴力跳块就可以，把值域，$n$ 和 $q$ 视为同阶那么复杂度 $O(n\sqrt{n})$。

---

## 作者：Dream_poetry (赞：1)

### 思路：

闲话：首先这是我第一个赛时秒（？）的正常难度的 G 题，但遗憾忘记预处理逆元惨死，引以为戒。

看到感人数据范围和要求，我们大胆猜测莫队，并发现时间复杂度是能过的。

考虑做法：

前面是正常莫队操作，但对于每次的 $x$，启发我们在 ```add()``` 和 ```del()``` 时对加入和删除的元素也做分块处理。

查询时同样充分发扬分块思想，大段直接计入，末尾时再处理小块即可。

总复杂度为 $O(n\sqrt{n})$。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int jc[250005];
int n,m;
int a[250005];
struct node{
	int l,r;
	int x;
	int id;
}e[250005];
int ans[250005];
int len;
int be[250005];
inline int ksm(int a,int x){
	int res=1;
	while (x){
		if (x&1){
			res=res*a%mod;
		}
		a=a*a%mod;
		x>>=1;
	}
	return res;
}

inline bool cmp(node a,node b){
	if (be[a.l]!=be[b.l]) return be[a.l]<be[b.l];
	if (a.r!=b.r) return a.r<b.r;
	return a.x<b.x;
} 

int cnt[250005];

int zy[250005];
int rmax[250005];
int lmin[250005];

int cczy[250005];
int ccinv[250005];
int mny1[250005],mny2[250005];

inline void add(int id){
	cnt[a[id]]++;
	cczy[zy[a[id]]]++;
	ccinv[zy[a[id]]]=(ccinv[zy[a[id]]]*cnt[a[id]])%mod;
}
inline void del(int id){
	ccinv[zy[a[id]]]=(ccinv[zy[a[id]]]*mny2[cnt[a[id]]])%mod;
	cnt[a[id]]--;
	cczy[zy[a[id]]]--;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	cin>>n>>m;
	len=sqrt(n);
	memset(lmin,0x3f,sizeof(lmin));
	jc[0]=1;
	for (int i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%mod;
		mny1[i] = ksm(jc[i],mod-2);
		mny2[i] = ksm(i,mod-2);
		zy[i]=(i-1)/len+1;
		ccinv[i]=1;
		lmin[zy[i]]=min(lmin[zy[i]],i);
		rmax[zy[i]]=max(rmax[zy[i]],i);
	}
	for (int i=1;i<=n;i++){
		cin>>a[i];
		be[i]=(i-1)/len+1;
	}
	for (int i=1;i<=m;i++){
		cin>>e[i].l>>e[i].r>>e[i].x;
		e[i].id=i;	
	}
	sort(e+1,e+m+1,cmp);
	int L=1;
	int R=0;
	for (int i=1;i<=m;i++){
		while (R<e[i].r){
			add(++R);
		}
		while (R>e[i].r){
			del(R--);
		}
		while (L>e[i].l){
			add(--L);
		}
		while (L<e[i].l){
			del(L++);
		}
		
		int Id;
		int C=0;
		int rrr=1;
		if (e[i].x<=len){
			for (int j=1;j<e[i].x;j++){
				C+=cnt[j];
				if (cnt[j]){
					rrr=(rrr*jc[cnt[j]])%mod;	
				}
			}
		}
		else{
			for (Id=1;rmax[Id]<e[i].x;Id++){
				C+=cczy[Id];
				if(ccinv[Id]){
					rrr=(rrr*ccinv[Id])%mod;
				}
			}
			for (int j=lmin[Id];j<e[i].x;j++){
				C+=cnt[j];
				if (cnt[j]){
					rrr=(rrr*jc[cnt[j]])%mod;
				}
			}
		}
		ans[e[i].id]=jc[C]*ksm(rrr,mod-2)%mod;
	}
	for (int i=1;i<=m;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

通过简单的组合数学可得答案是：

$$
\frac{(\sum_{y=1}^xcnt_y)!}{\prod_{y=1}^xcnt_y!}
$$

$cnt_y$ 表示区间内 $y$ 的出现次数。

先用莫队把询问的区间拍在值域上，需要一个支持单点加和查询的数据结构。

很多数据结构都能实现，在莫队中应该使用值域分块，因为单点加的操作次数是 $q\sqrt{n}$，查询次数是 $q$，用值域分块可以平衡复杂度，总复杂度为 $O(q\sqrt{n})$。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cerr<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=2.5e5+5,M=5e2+5,mod=998244353;
struct Que{
	int l,r,k,id;
}q[N];
int n,m,a[N];
int belong[N],rt[M],lt[M],block,tot;
int cnt[N];
int sum[M],ans[N];
int res[N];
int fac[N],inv[N],ifac[N];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;	
}
bool cmp(Que x,Que y){
	return x.l/block!=y.l/block?x.l/block<y.l/block:x.r<y.r;
}
void build(){
	block=(int)sqrt((double)n);
	tot=n/block;
	if(n%block) tot++;
	for(int i=1;i<=tot;i++){
		lt[i]=(i-1)*block+1;
		rt[i]=i*block;
		ans[i]=1;
	}rt[tot]=n;
	for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;
	fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=n;i++) inv[i]=qpow(i,mod-2);
	ifac[0]=1;
	for(int i=1;i<=n;i++) ifac[i]=inv[i]*ifac[i-1]%mod;
}
inline void add(int x){
	cnt[x]++;
	sum[belong[x]]++;
	ans[belong[x]]=ans[belong[x]]*inv[cnt[x]]%mod;
}
inline void del(int x){
	ans[belong[x]]=ans[belong[x]]*cnt[x]%mod;
	sum[belong[x]]--;
	cnt[x]--;
}
int ask(int r){
	int res=0,t=1;
	for(int i=1;i<belong[r];i++) res+=sum[i],t=t*ans[i]%mod;
	for(int i=lt[belong[r]];i<=r;i++) res+=cnt[i],t=t*ifac[cnt[i]]%mod;
	return fac[res]*t%mod;
}
signed main(){
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build();
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r>>q[i].k;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(r>q[i].r) del(a[r--]);
		while(l<q[i].l) del(a[l++]);
		res[q[i].id]=ask(q[i].k-1);
	}
	for(int i=1;i<=m;i++) cout<<res[i]<<endl;
	return 0;
}
```

---

## 作者：lzyqwq (赞：0)

> - 给出 $[a_1,\dots,a_n]$，$q$ 次询问 $l,r,x$，查询将 $[a_l,\dots,a_r]$ 中小于 $x$ 的数任意排列，能得到多少个序列。由于任意排列方式得到的序列长度相同，所以两个不同当且仅当存在一个下标上的元素不同。答案对 $998244353$ 取模。
> - $n,q\le 2.5\times 10^5$。

先不考虑 $l,r$。记 $f_x$ 为**小于等于** $x$ 的数答案。假设告诉你每个数的出现次数 $v_i$，$f_x$ 的答案会是多少？

记 $s_x=\sum\limits_{i=1}^xv_i$。考虑递推，$f_x$ 可以看成是先从 $s_x$ 个位置中选出 $v_x$ 个位置放 $x$，剩下的 $s_{x-1}$ 个位置会形成一个由小于等于 $x-1$ 的数构成的序列。而任意选取 $v_x$ 个位置放 $x$，剩余位置放入一个由小于等于 $x-1$ 的数构成的序列后，都会形成一个小于等于 $x$ 的数构成的序列。所以：

$$f_x=f_{x-1}\dbinom{s_x}{v_x}=f_{x-1}\dfrac{s_x!}{v_x!(s_x-v_x)!}$$

其中 $f_0=1$，表示空序列。注意到 $s_x-v_x=s_{x-1}$。那么容易发现：

$$f_x=\prod\limits_{i=1}^x\dfrac{s_i!}{v_i!s_{i-1}!}$$

严谨证明可以考虑数学归纳法。

然后不要像我一样愚蠢没有注意到 $s_{1}!,\dots,s_{x-1}!$ 都被约掉了，那么答案为：

$$f_x=\dfrac{s_x!}{\prod_{i=1}^xv_i!}$$

其实有一个更简单的组合意义解释。把 $s_x$ 个数按下标随便排是 $s_x!$ 种方案。而对于一种题目要求的方案，每个数随便排会带来 $v_i!$ 种重复，那么一种方案会重复 $\prod_{i=1}^xv_i!$。除掉她即可。

只需要求出 $v_i$ 的前缀和以及 $v_i!$ 的前缀积即可。

考虑带上多次查询，那么我们要对于区间维护出 $v_i$。容易想到使用莫队。

考虑如何解决 $x$ 这一维限制，容易想到值域分块。维护块内 $v_i$ 和以及 $v_i!$ 积。莫队插入、删除元素就是单点修改 $v_i$ 和所在其块的两个信息。预处理阶乘、阶乘的逆元、每个数的逆元后容易 $\mathcal{O}(1)$ 实现。

查询就统计所有整块的信息，散块信息暴力合并。

认为 $n,q$ 同阶，时间复杂度 $\mathcal{O}(n\sqrt n)$，空间复杂度 $\mathcal{O}(n)$。

https://atcoder.jp/contests/abc405/submissions/65689547

---

## 作者：CJ_Fu (赞：0)

对于一个区间，数字 $i$ 出现次数为 $c_i$，则答案为 $\dfrac{(\sum_{i=1}^{x-1}c_i)!}{\prod_{i=1}^{x-1}(c_i!)}$，~~这部分很典了~~，就是全排列除掉相同数字之间的顺序。

考虑用莫队移动，树状数组维护 $c$ 数组前缀和、前缀积，时间复杂度 $O(n\sqrt q\log n+q\log n)$，直接被卡飞。把树状数组换成 $O(1)-O(\sqrt n)$ 的值域分块就行了（莫队套值域分块也很典了），时间复杂度 $O(n\sqrt q+q\sqrt n)$。注意能预处理的尽量预处理了（比如阶乘和逆元）。还有要注意一点，把莫队的加操作放在减操作之前，不然会访问负数的逆元就爆了。

综上是道典题。代码超级好写。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2.5e5+7;
const int mod=998244353;
int B=501;
int n,q;
int a[maxn],inv[maxn];
struct node{
    int l,r,x,id;
    bool operator<(const node &o)const{
        if(l/B==o.l/B) return r<o.r;
        return l<o.l;
    }
}b[maxn];
#define bl(x) (((x)-1)/B+1)
#define st(x) ((bl(x)-1)*B+1)
#define ed(x) (bl(x)*B)
int ton[maxn],ans[maxn],fac[maxn];
int pre[maxn],prv[maxn],mum[maxn];
void add(int x){
    pre[bl(a[x])]++;
    ton[a[x]]++; 
    prv[bl(a[x])]=prv[bl(a[x])]*ton[a[x]]%mod;
    mum[a[x]]=mum[a[x]]*ton[a[x]]%mod;
}
void del(int x){
    pre[bl(a[x])]--;
    ton[a[x]]--; 
    prv[bl(a[x])]=prv[bl(a[x])]*inv[ton[a[x]]+1]%mod;
    mum[a[x]]=mum[a[x]]*inv[ton[a[x]]+1]%mod;
}
int qpow(int a,int b){
    int res=1;
    for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>q; B=n/sqrt(q);
    inv[1]=1;
    for(int i=2;i<=n+2;i++)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    fac[0]=1;
    for(int i=1;i<=n+2;i++)
        fac[i]=fac[i-1]*i%mod;
    for(int i=0;i<=n+2;i++)
        prv[i]=mum[i]=1;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=q;i++)
        cin>>b[i].l>>b[i].r>>b[i].x, b[i].id=i;
    sort(b+1,b+q+1);
    int l=1,r=0; 
    for(int i=1;i<=q;i++){
        while(l>b[i].l) add(--l);
        while(r<b[i].r) add(++r);
        while(r>b[i].r) del(r--);
        while(l<b[i].l) del(l++);
        int K=0,invf=1;
        for(int j=1;j<bl(b[i].x-1);j++)
            K+=pre[j], invf=invf*prv[j]%mod;
        for(int j=st(b[i].x-1);j<b[i].x;j++)
            K+=ton[j], invf=invf*mum[j]%mod;
        ans[b[i].id]=fac[K]*qpow(invf,mod-2)%mod;
    }
    for(int i=1;i<=q;i++)
        cout<<ans[i]<<'\n';
    return 0;
}
```

泪点解析：出题人专门放了 8 个 anti_fenwick 测试点来卡 log。让我们感谢良心出题人。

---

## 作者：zyn_ (赞：0)

# G - Range Shuffle Query

题目大意：给定一个长为 $n$ 的序列 $\{a_i\}$。有 $q$ 次询问。每次询问给定 $l,r,x$，令所有 $a_{l\dots r}$ 中 $\lt x$ 的项组成序列 $b$，将序列 $b$ 任意重排，求可能得到的不同序列的数量。

接下来我们记询问的答案，也就是「可能得到的不同序列的数量」为 $S$。

## 单次询问

考虑单次询问怎么做。我们发现 $S$ 的值与序列 $b$ 中**重复出现**的数相关。举一些例子：

- 如果 $b=\{1,2,\dots,k\}$，$b$ 中的数两两不同，那么 $S$ 的值为 $k!$；
- 如果 $b=\{1,1,\dots,1\}$，无论有几个 $1$，$S$ 的值总是 $1$；
- 如果 $b=\{1,1,2,3,4,\dots,k-1\}$，那么 $S$ 的值为 $\dfrac{k!}{2}$。

结论：设序列 $b$ 的长度为 $L$，且它由 $c_1$ 个 $w_1$，$c_2$ 个 $w_2$，……，$c_k$ 个 $w_k$ 组成（所有 $w_i$ 互不相同），则

$$
S=\frac{L!}{\prod_{i=1}^k c_i!}
$$

这里 $x!=\prod_{i=1}^x i$ 为阶乘符号。

### 如何证明

> 为了证明这个结论，考虑**将 $b$ 中相同的数编号**（比如将 $c_1$ 个 $w_1$ 分别称作「$1$ 号 $w_1$」、「$2$ 号 $w_1$」、……）。考虑重排后可能得到的任意序列 $b'$。  
> 如果编号不同而值相同的数视为**不同**元素，那么 $b'$ 显然有 $L!$ 种。  
> 如果编号不同而值相同的数视为**相同**元素，对于每个 $i$，都有 $c_i!$ 种方式排布序列中的 $c_i$ 个不同的 $w_i$，从而 $b'$ 可以通过 $P={\prod_{i=1}^k c_i!}$ 种方式被重排出。  
> 现在同一个 $b'$ 被计算了 $P$ 次，这样计算得出共有 $L!$ 个 $b'$。因此实际上不同的 $b'$ 只有 $\dfrac{L!}{P}$ 种。这就证明了结论。

## 多次询问

注意到 $S$ 的值与 $a_{l\dots r}$ 中**每种数**出现的次数相关，这让我们考虑**莫队算法**。

### 如果你不会莫队算法

> 具体地，令 $B=\sqrt{n}$（下取整）。将序列划分成若干块，每块的长度为 $B$（如果 $B\nmid n$ 则最后一块长度不足 $B$）。考虑将所有询问存储下来，并将它们按如下规则排序：  
> 对于两个询问区间 $[l_1,r_1],[l_2,r_2]$：
>
> - 如果 $l_1$ 与 $l_2$ 在同一块内，则将区间右端点小的排在前面；
> - 否则，将区间左端点小的排在前面。
>
> ```cpp
> bool cmp(const query&a,const query&b){
>     return (block[a.l]==block[b.l])
>             ?(a.r<b.r):(a.l<b.l);
> }
> ```
>
> 按照排序后的顺序依次处理询问。每次询问的区间的答案，基于上次询问的区间，通过在区间两端「拓展或收缩」的形式而得到。  
> 具体地，我们只需要维护区间 $[l,r]$ 变为 $[l,r+1],[l,r-1],[l+1,r],[l-1,r]$ 时的答案。  
> 可以证明，这样做，「拓展或收缩」的次数是 $O(n\sqrt n)$ 级别的。

现在我们需要做的是，维护一个可重集合 $D$：

- 操作一：向 $D$ 中加入一个数，或从 $D$ 中删除一个数。这样的操作有 $O(n\sqrt n)$ 次。

- 操作二：将 $D$ 中 $<x$ 的数提取出来组成序列 $b$，询问它对应的

$$
S=\frac{L!}{\prod_{i=1}^k c_i!}
$$

的值。这样的操作有 $q$ 次。

维护数组 $\{t_i\}$，其中 $t_i$ 代表 $i$ 在 $D$ 中的出现次数。在 $D$ 中出现 $0$ 次的数是无关紧要的（可以令 $0!=1$），将 $S$ 重写为：

$$
S=\frac{(\sum_{i=1}^{x-1}t_i)!}{\prod_{i=1}^{x-1} t_i!}
$$

当然，求 $S$ 的值，可以拆分为求 $\sum_{i=1}^{x-1}t_i$ 的值以及求 $\prod_{i=1}^{x-1} t_i!$ 的值。记后面的这个乘积为 $M_x$。

操作一使某个 $t_i$ 加一或减一，并使某个 $t_i!$ 乘以或除以一个数。操作二要求 $t_i$ 的前缀和以及 $t_i!$ 的前缀积。

这显然可以用线段树维护，但是将导致时间复杂度变成 $O(n\sqrt n\log n)$，不是正解。

注意到操作二的次数少于操作一。为了平衡时间复杂度，考虑分块。还是以 $B=\sqrt n$（下取整）为块长。

以维护 $t_i$ 的前缀和为例。记录每块内的 $t_i$ 之和 $s_i$。对于操作一，只需要更新一个 $t_i$ 和一个 $s_i$。对于操作二，要将整块的 $O(\dfrac{n}{B})$ 个 $s_i$ 与散块的 $O(B)$ 个 $t_i$ 加起来。这样，操作一的时间复杂度为 $O(1)$，操作二的时间复杂度为 $O(\sqrt n)$。

对于维护 $t_i!$ 的前缀积也如此做，这样总时间复杂度就是 $O((n+q)\sqrt n)$，即为正解。

---

## 作者：cheng2010 (赞：0)

话说最近 G 是越来越水了。

## 思路

设区间内每个数分别出现 $a_1,a_2,a_3,\dots,a_k$ 次，那么有：

$$
ans=\frac{(\displaystyle \sum_{i=1}^{k} a_i)!}{ \displaystyle \prod_{i=1}^{k} (a_i!)}
$$

意义是把所有的数全排列的方案除去每种相同的数排列的方案。

对于这种奇怪的满足可减性的式子直接上莫队，考虑怎么计算贡献。

为了保证时间复杂度，我们需要一种 $O(1)$ 单点修改，$O(1) \sim O(\sqrt n)$ 区间查询的数据结构，分块刚好满足条件。

具体地，我们值域分块，对于每个块定义 $sum$ 为该块的 $\sum a_i$，$sum2$ 为 $\dfrac{1}{ \prod (a_i!) }$，加上预处理逆元即可，总时间复杂度 $O( n \sqrt n)$，值得注意的是，莫队里面要先扩展区间，再缩小区间，不然每种数字出现次数可能会炸成负数，详见代码。

最后就是注意卡常，这里有几点建议：

- 用 `int`。
- 快读快输。
- 奇偶排序。
- 块长开 $\dfrac{n}{\sqrt m}$。

## code

[link](https://atcoder.jp/contests/abc405/submissions/65731155)

---

