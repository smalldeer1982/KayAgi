# [JRKSJ R1] 吊打

## 题目描述

给出一个长为 $n$ 的正整数序列 $a_{1\sim n}$。接下来有两种操作共 $m$ 次：
- `1 l r`，表示将 $a_{l\sim r}$ 开方并下取整，即令 $\forall i\in [l,r],a_i\gets\lfloor\sqrt{a_i}\rfloor$；
- `2 l r`，表示将 $a_{l\sim r}$ 平方，即令 $\forall i\in [l,r],a_i\gets a_i^2$。

在所有操作结束后，请你输出 $\displaystyle\sum_{i=1}^na_i$。

由于答案可能很大，你只需要输出其对 $998244353$ 取模的结果即可。

## 说明/提示

### 数据规模与约定

| 测试点 | 特殊限制 |
| :----------: | :----------: |
| $1$ | $n,m\le 10$ |
| $2$ | 保证一次 `1 l r` 操作上一步是 `2 l r` |
| $3$ | 保证只有 `1` 操作 |
| $4$ | 保证只有 `2` 操作 |
| $5$ | 保证所有的 $l=1$，$r=n$ |
| $6$ | $n,m\le 10^3$ |
| $7\sim 20$ | 无特殊限制 |


对于所有数据，保证 $1\le n,m\le2\times10^5$，$1\le a_i\le 10^9$。


## 样例 #1

### 输入

```
1 1
1
1 1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
4 2
1 2 3 4
1 2 4
2 1 4```

### 输出

```
7```

## 样例 #3

### 输入

```
5 5
10 8 10 11 12
2 1 5
1 1 5
1 1 4
2 4 5
1 1 5```

### 输出

```
18```

# 题解

## 作者：Ryo_Yamada (赞：16)

区间操作首先想到线段树。

- 区间开方下取整

和 [GSS4](https://www.luogu.com.cn/problem/SP2713) 一样，可以用相同的方法，记录区间最大值，如果这个最大值 $>1$ 才进入区间修改。$10^9$ 做五次开方操作就会变成 $1$，所以复杂度是有保证的。

- 区间平方

显然，区间平方的和 与 区间和的平方不是一个东西，无法直接修改，要考虑别的做法。平方和开方是相反的操作，平方再开方后原数是不变的，考虑对每个点记录一个 $\text{cnt}_i$ 表示当前这个数 $\text{val}_i$ 被平方了多少次。对于每次开方操作，将 $\text{cnt}_i$ 区间 $+1$。开方时，若 $\text{cnt}_i$ 不为 $0$ 则 $\text{cnt}_i = \text{cnt}_i-1$，否则将原数开方。因为 $1$ 平方和开方后都是 $1$，所以这种做法区间最大值在 $>1$ 上的正确性是有保证的。

但是这样还不足以通过。通过一次平方一次开方的操作可以将这种做法卡到 $O(nm)$。再维护区间 $\text{cnt}_i$ 的最小值，修改时，若这个最小值 $\geq 1$，则直接区间将 $\text{cnt}_i = \text{cnt}_i - 1$。否则进入左右区间修改。

$\text{Code}$：

```cpp
#define ls id << 1
#define rs id << 1 | 1
#define Mid int mid = (l + r) >> 1

def(nn, int, 2e5 + 5)
def(N, int, 8e5 + 5)
def(p, int, 998244353)

int n, q;
int a[nn];
ll val[N], cnt[N], lz[N], mx[N], mnc[N];

void pushup(int id) {
	mx[id] = max(mx[ls], mx[rs]);
	mnc[id] = min(mnc[ls], mnc[rs]);
}

void pushdown(int id) {
	if(lz[id]) {
		cnt[ls] += lz[id];
		cnt[rs] += lz[id];
		mnc[ls] += lz[id];
		mnc[rs] += lz[id];
		lz[ls] += lz[id];
		lz[rs] += lz[id];
		lz[id] = 0;
	}
}

void build(int id, int l, int r) {
	if(l == r) {
		val[id] = mx[id] = a[l];
		return ;
	}
	Mid;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(id);
}

void update(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y && mnc[id] >= 1) {
		--cnt[id], --mnc[id], --lz[id];
		return ;
	}
	if(l == r) {
		if(cnt[id]) --cnt[id], --mnc[id];
		else mx[id] = val[id] = sqrt(val[id]);
		return ;
	}
	pushdown(id);
	Mid;
	if(mx[ls] > 1 && mid >= x) update(ls, l, mid, x, y);
	if(mx[rs] > 1 && mid < y) update(rs, mid + 1, r, x, y);
	pushup(id);
}

void modify(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y) {
		++cnt[id], ++mnc[id], ++lz[id];
		return ;
	}
	pushdown(id);
	Mid;
	if(mid >= x) modify(ls, l, mid, x, y);
	if(mid < y) modify(rs, mid + 1, r, x, y);
	pushup(id);
}

ll query(int id, int l, int r, int x) {
	if(l == r) {
		int pf = qpow(cnt[id], 2, p - 1);
		return qpow(pf, val[id], p);
	}
	pushdown(id);
	Mid;
	if(mid >= x) return query(ls, l, mid, x);
	else return query(rs, mid + 1, r, x);
}

int main() {
	qread(n, q);
	rep(i, 1, n) qread(a[i]);
	build(1, 1, n);
	W(q) {
		int op, l, r;
		qread(op, l, r);
		if(op == 1) {
			update(1, 1, n, l, r);
//			rep(i, l, r) {
//				ll x = query(1, 1, n, i);
//				cout << x << endl;
//			}
		}
		else modify(1, 1, n, l, r);
	}
	ll ans = 0;
	rep(i, 1, n) {
		ll x = query(1, 1, n, i);
		//cout << x << endl;
		(ans += x) %= p;
	}
	printf("%lld\n", ans);
 	return 0;
}
```


---

## 作者：cyffff (赞：13)

[$\text{Link}$](https://www.luogu.com.cn/problem/P7334)

## 题意
给出 $n,m$ 表示长为 $n$ 的序列 $a$，$m$ 次操作，支持两种操作：
- `1 l r`，对所有 $i\in[l,r]$，将 $a_i\gets\left\lfloor\sqrt{a_i}\right\rfloor$。
- `2 l r`，对所有 $i\in[l,r]$，将 $a_i\gets{a_i}^2$。

最后输出 $\displaystyle\left(\sum_{i=1}^na_i\right)\bmod 998244353$。

时间 1s，$n,m\le 2\times10^5$。

## 思路
$\text{Update 2022.4.21}$：重构全文。

发现区间开方直接拍一个分块上去，参考 P4145。

这里不好维护原数，考虑维护 $i$ 位置上的数被平方的次数 $s_i$。

操作 $1$ 为区间加。考虑操作 $2$，散块暴力，整块维护 $s_i$ 最小值。若 $\min s_i\ge1$，直接打区间减 $\text{tag}$，否则若 $\max a_i= 1$，跳过，否则暴力开方或将 $s_i$ 减一。

由势能分析，我们知道这部分是 $O(n\sqrt {n\log\log w})$ 的。

求出 $s_i$ 后考虑得出答案，用欧拉定理降幂，预处理一下 $2^{k}\bmod998244352$,即可在 $O(\log p)$ 时间内求出 $a_i^{2^{s_i}}$，总时间复杂度为 $O(n\sqrt{n\log\log w})$，期望得分 $100$ 分。

我没写代码，$\text{dqstz}$ 写了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx=2e5+5; 
const int mod=998244353;
int a[mx];
int bl[mx],fl[mx],fr[mx];
int s[mx],tag[mx],mn[mx],os[mx];
int pow2[mx];
int n,b,ks;
void init()
{
	int i,j,k,mx;
	b=sqrt(n);
	for(i=1;i-1+b<=n;i+=b)
		fl[++ks]=i,fr[ks]=i-1+b;
	if(i<=n)
		fl[++ks]=i,fr[ks]=n;
	for(i=1;i<=ks;i++)
		for(j=fl[i];j<=fr[i];j++)
			bl[j]=i;
}
int qpow(int a,int p,int mod)
{
	if(p==0) return 1;
	if(p==1) return a;
	long long t=qpow(a,p/2,mod);
	return t*t%mod*qpow(a,p%2,mod)%mod;
}
int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}
void cg(int x)
{
	mn[x]=2e9;
	for(int i=fl[x];i<=fr[x];i++)
		mn[x]=min(mn[x],s[i]+tag[x]);
}
void zk(int x)
{
	for(int i=fl[x];i<=fr[x];i++)
		s[i]+=tag[x];
	tag[x]=0;
}
void add(int l,int r)
{
	if(bl[l]==bl[r])
	{
		zk(bl[l]);
		for(;l<=r;l++)
			s[l]++;
		cg(bl[l-1]);
		return;
	}
	add(l,fr[bl[l]]),add(fl[bl[r]],r);
	int i;
	for(i=bl[l]+1;i<bl[r];i++)
		tag[i]++,mn[i]++;
}
void sqrt(int l,int r)
{
	if(bl[l]==bl[r])
	{
		zk(bl[l]);
		for(;l<=r;l++)
		{
			if(a[l]==1) continue;
			if(s[l]==0) 
			{
				a[l]=sqrt(a[l]);
				os[bl[l]]+=a[l]==1;
			}
			else s[l]--;
		}
		cg(bl[l-1]);	
		return;
	}
	sqrt(l,fr[bl[l]]),sqrt(fl[bl[r]],r);
	for(int i=bl[l]+1;i<bl[r];i++)
	{
		if(os[i]==fr[i]-fl[i]+1) continue;
		if(mn[i]==0)
			sqrt(fl[i],fr[i]);		
		else
			mn[i]--,tag[i]--;	
	}				
}
int main()
{
	int m,i,opt,l,r,sum=0,wz=2e9,qwq;
	n=read(),m=read();
	init();
	pow2[0]=1;
	for(i=1;i<=n;i++)
		a[i]=read();
	for(i=1;i<=m;i++)
	{
		pow2[i]=pow2[i-1]*2;
		if(pow2[i]>=mod-1&&wz==2e9) wz=i;
		pow2[i]%=mod-1;
	}
	while(m--)
	{
		opt=read(),l=read(),r=read();
		if(opt==1) sqrt(l,r);
		else add(l,r);
	}
	for(i=1;i<=ks;i++)
		zk(i);
	for(i=1;i<=n;i++)
	{
		if(a[i]==1)
		{
			sum=(sum+1)%mod;
			continue;
		}
		qwq=pow2[s[i]];
		if(s[i]>=wz) qwq+=mod-1;
		sum=(sum+qpow(a[i],qwq,mod))%mod;	
	}
	cout<<sum%mod;
} 
```
再见 qwq~

---

## 作者：super蒟蒻 (赞：7)

提供另一种线段树做法。

首先把这 $n$ 个数里，每个数一直向下取整涉及到的量存下来。

例如第 $i$ 个位置上的数是 $27$ ，就在第 $i$ 个位置记下： $27,5,2,1$ 。

不难证明这样时间和空间是 $O(n \log a)$ 的。

不妨把开方看作 $-1$ ，平方看作 $+1$ 。

显然最后我们只关心每个位置上当前的值是多少，以及**历史最小值**，这就是为什么上面要把所有情况处理出来。

然后就是[线段树3](https://www.luogu.com.cn/problem/P6242)的超级弱化版了，支持区间加区间减，维护历史最小值。

因为 $998244353$ 是质数，根据费马小定理，算答案的时候指数直接模$998244352$ 即可。

总的时间复杂度 $O(n \log a + m \log n)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	char ch=getchar();
	int x=0,pd=0;
	while(ch<'0'||ch>'9') pd|=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return pd?-x:x;
}
const int maxn=200005;
namespace modular {
const int mod=998244353;
int Add(int x,int y) { return x+y<mod?x+y:x+y-mod; }
int Dec(int x,int y) { return Add(x,mod-y); }
int Mul(int x,int y) { return 1ll*x*y%mod; }
int Pow(int x,int y) {
	int res=1;
	for(;y;y>>=1,x=Mul(x,x))
		if(y&1) res=Mul(res,x);
	return res;
}
int p2[maxn];
void init(int B) {
	p2[0]=1;
	for(int i=1;i<=B;i++) p2[i]=(p2[i-1]+p2[i-1])%998244352;
}
} using namespace modular;
int n,m,a[maxn];
vector<int> b[maxn];
#define ls (o<<1)
#define rs (o<<1|1)
#define lson ls,l,mid
#define rson rs,mid+1,r
int tag[maxn<<2],mn[maxn<<2];
void adt(int o,int x,int y) {
	o[mn]=min(o[mn],o[tag]+y);
	o[tag]+=x;
}
void pd(int o) {
	adt(ls,o[tag],o[mn]),adt(rs,o[tag],o[mn]);
	o[tag]=o[mn]=0;
}
void upd(int o,int l,int r,int L,int R,int x) {
	if(L<=l&&r<=R) { adt(o,x,min(x,0)); return; }
	if(o[tag]||o[mn]) pd(o);
	int mid=(l+r)>>1;
	if(L<=mid) upd(lson,L,R,x);
	if(R>mid) upd(rson,L,R,x);
}
int ans;
void calc(int o,int l,int r) {
	if(l==r) {
		if(-o[mn]>=(int)b[l].size()) ans=Add(ans,1);
		else ans=Add(ans,Pow(b[l][-o[mn]],p2[o[tag]-o[mn]]));
		return;
	}
	if(o[tag]||o[mn]) pd(o);
	int mid=(l+r)>>1;
	calc(lson),calc(rson);
}
int main() {
	#ifdef LOCAL
	freopen("data.in", "r", stdin);
	freopen("pro.out", "w", stdout);
	#endif
	n=read(),m=read();
	init(m);
	for(int i=1;i<=n;i++) {
		int x=read();
		while(x>1) b[i].emplace_back(x),x=sqrt(x);
		b[i].emplace_back(x);
	}
	while(m--) {
		int opt=read(),l=read(),r=read();
		if(opt==1) upd(1,1,n,l,r,-1);
		else upd(1,1,n,l,r,1);
	}
	calc(1,1,n);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Remake_ (赞：7)

大家好，我使用了一种被点名卡的分块过了此题。

![](https://cdn.luogu.com.cn/upload/image_hosting/j0w4817f.png)

这里说一下大概思路吧。

首先，当块内全为 $1$ 时，显然无论是哪个操作都没有用，直接略掉。

然后对于其他不能略去的情况，考虑每个点维护一个 tag ，这个 tag 代表的是这个点经历了多少次二操作，同样的，我们整块也需维护一个 tag 。

显然对于一操作，可以抵消二操作，所以我们在做一操作的时候直接像区间减法一样抵消二操作即可。

需要注意的是，当 tag 为 $0$ 的时候我们需要直接对 $a_i$ 开方而不能将 tag 减为负数，所以我们无法延迟整块 tag ，必须即时重构。

正因如此，在操作 $1$ 时对于每一个整块都需要暴力修改，同时修改完了之后还要判断一下是否块内全为 $1$ 。

以上即为基本思路，经大力卡常后可以通过。

这里分享一下关于这题比较重要的卡常点：

即每次重构时 整块 tag 只拿走一个，为什么这样会优呢？因为在一操作时对于每一个整块暴力是常数瓶颈所在，而如果那个块整块 tag 不为 $0$ 时会直接 $O(1)$ 修改而非暴力一遍，所以这样做不但可以保证重构的有效还可以极大地优化常数。

加上这个东西再卡亿卡常估计就过了/cy

等下似乎忘了说那些 tag 在统计答案的时候如何处理了（

我们知道一个数 $x$ 被平方 $n$ 次后会变成 $x^{2^n}$。

所以对于原数 $a_i$ 以及其对应的 $tag_i$，我们可以将其对应的答案转化为 $a_i^{2^{tag_i}}\pmod {998244353}$

根据拓展欧拉定理，在 $b\ge \varphi(p)$ 时，有 $ a^{b}\equiv a^{b\mod \varphi(p)+\varphi(p)}\pmod p$。

在此题中的模数 $998244353$ 为质数，故 $\varphi(998244353)=998244352$。

如何特判 $2^{tag_i}$ 是否 $<998244352$呢？可以使用对数来判断，即转化为判断：$tag_i \ln2<\ln998244352$ 就可以了qwq。

所以对于每一个位置所对应的答案两个快速幂就出来了awa。
 
然后这题就愉快的做完了。

这道题目综合考察了选手的数论，ds以及卡常功底，出题人太牛逼了！!1

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define inf 0x7fffffff
#define timeused() (double)clock()/CLOCKS_PER_SEC
#define rep(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define repp(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define debug() assert(0)
typedef int ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x){
   T f=1;x=0;char c=getchar();
   for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
   for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
   x*=f;
   return x;
}
ll n,m,a[500005],opt,l,r,siz,L[1005],R[1005],tag[500005],bel[500005],tags[1005],sq[10000005];
long long totans;
bool pd[1005];
ll Sqrt(ll x){return x>=10000000?sqrt(x):sq[x];}
void cg(ll be){
   --tags[be];
   rep(i,L[be],R[be]) ++tag[i];
   return;
}
bool check(ll be){
   rep(i,L[be],R[be]) if(a[i]>1) return 0;
   return 1;
}
void opt1(ll l,ll r){
   bool vis;
   if(bel[l]==bel[r]){
      if(pd[bel[l]]) return;
      vis=0;
      rep(i,l,r){
         if(tags[bel[i]]&&!tag[i]&&!vis){
            cg(bel[l]);
            vis=1;
         }
         if(tag[i]) --tag[i];
         else a[i]=Sqrt(a[i]);
      }
      if(!pd[bel[l]]) pd[bel[l]]=check(bel[l]);
      return;
   }
   ll tmp;
   if(pd[bel[l]]) for(;l!=L[bel[l]];++l);
   else{
      vis=0;
      tmp=bel[l];
      for(;l!=L[bel[l]];++l){
         if(tags[bel[l]]&&!tag[l]&&!vis){
            cg(bel[l]);
            vis=1;
         }
         if(tag[l]) --tag[l];
         else a[l]=Sqrt(a[l]);
      }
      pd[tmp]=check(tmp);
   }
   if(pd[bel[r]]) for(;r!=R[bel[r]];--r);
   else{
      vis=0;
      tmp=bel[r];
      for(;r!=R[bel[r]];--r){
         if(tags[bel[r]]&&!tag[r]&&!vis){
            cg(bel[r]);
            vis=1;
         }
         if(tag[r]) --tag[r];
         else a[r]=Sqrt(a[r]);
      }
      pd[tmp]=check(tmp);
   }
   rep(i,bel[l],bel[r]){
      if(pd[i]) continue;
      if(tags[i]) --tags[i];
      else{
         rep(j,L[i],R[i]){
            if(tag[j]) --tag[j];
            else a[j]=Sqrt(a[j]); 
         }
         pd[i]=check(i);
      }
   }
}
void opt2(ll l,ll r){
   if(bel[l]==bel[r]){
      if(pd[bel[l]]) return;
      rep(i,l,r) ++tag[i];
      return;
   }
   for(;l!=L[bel[l]];++l) ++tag[l];
   for(;r!=R[bel[r]];--r) ++tag[r];
   rep(i,bel[l],bel[r]) ++tags[i];
}
long long qp(long long b,long long p){
   long long base=b,ans=1;
   while(p){
      if(p&1) ans=ans*base%mod;
      base=base*base%mod;
      p>>=1;
   }
   return ans;
}
long long qp2(long long b,long long p){
   long long base=b,ans=1;
   while(p){
      if(p&1) ans=ans*base%(mod-1);
      base=base*base%(mod-1);
      p>>=1;
   }
   return ans;
}
int main(){
   rep(i,1,10000000) sq[i]=sqrt(i);
   rd(n);
   siz=ceil(sqrt(n));
   rd(m);
   rep(i,1,siz){
      L[i]=(i-1)*siz+1;
      R[i]=i*siz;
      rep(j,L[i],R[i]) bel[j]=i;
   }
   rep(i,1,n) rd(a[i]);
   rep(i,1,m){
      rd(opt);
      rd(l);
      rd(r);
      if(opt==1) opt1(l,r);
      else opt2(l,r);
   }
   rep(i,1,n){
      if(log(2)*(tags[bel[i]]+tag[i])<log(mod-1)) totans=(totans+qp(a[i],qp2(2,tags[bel[i]]+tag[i])))%mod;
      else totans=(totans+qp(a[i],mod-1+qp2(2,tags[bel[i]]+tag[i])))%mod;
   }
   printf("%lld",totans);
}
```


---

## 作者：Imiya (赞：6)

看眼输出，发现只需要在最后求一次数列具体的值就行了，那么尝试考虑保留对每个数做的操作并合并，在最后求值。

连续一坨取根号操作可以合并留到最后算，和 [P4145](https://www.luogu.com.cn/problem/P4145) 的思路类似，因为开根号下取整做不了几次就会变成 $1$，所以能够保证复杂度。

连续一坨平方操作也容易合并，假设对 $x$ 进行了 $y$ 次平方操作，那么 $x$ 将变为 $x^{2^y}$，用一下拓展欧拉定理（好像也叫指数循环节定理），可以两次快速幂求出答案。

$$a^b\equiv\begin{cases}
a^{b\bmod \varphi(m)},&\gcd(a,m)=1,\\
a^b,&\gcd(a,m)\not=1,b<\varphi(m),\\
a^{(b\bmod \varphi(m))+\varphi(m)},&\gcd(a,m)\not=1,b\ge \varphi(m).
\end{cases}(\bmod m)$$

先若干根号，后若干平方不太好合并，因为根号取了下去整。但发现先若干平方，后若干根号非常好合并，平方之后一定是完全平方数，开根后变回原样。

具体的，定义一个 tag，$(x,y)$ 表示先做 $x$ 次开根操作然后做 $y$ 次平方操作，可以认为是一个操作集。考虑合并两个操作集 $(x_1,y_1),(x_2,y_2)$，也就是先做一个操作集的操作，然后做另一个操作集的操作。根据前几段的论述，容易发现 
$$(x_1,y_1)+(x_2,y_2)=\begin{cases}
(x_1,y_1-x_2+y_2),&y_1> x_2,\\
(x_1+x_2-y_1,y_2),&y_1\le x_2.
\end{cases}$$
$$=(x_1+x_2-\min(x_2,y_1),y_1+y_2-\min(x_2,y_1))$$
正确性显然。

有了这个就可以把一坨操作合并变成一个 tag，由于题目是区间操作，所以可以随便拿分块、线段树啥的数据结构维护公共 tag，修改内部的时候下传。操作一相当于把区间内所有 tag 和 $(1,0)$ 做一次合并，操作二相当于和 $(0,1)$ 合并。最后所有把所有公共 tag 下传，按照前面讲的方法算最终值即可。

代码（分块）
```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int N=200100,P=998244353,S=500;
#define int long long
#define Pair pair<int,int>
#define p1 first
#define p2 second
inline int read(){
    int i=getchar(),r=0;
    while(i<'0'||i>'9')i=getchar();
    while(i>='0'&&i<='9')r=(r<<1)+(r<<3)+(i^48),i=getchar();
    return r;
}
int n,m,a[N];
Pair tag[N],laz[S];
inline Pair operator+(const Pair&x,const Pair&y){
    int z=min(x.p2,y.p1);
    return make_pair(x.p1+y.p1-z,x.p2+y.p2-z);
}
int siz,L[S],R[S],bel[N];
void init(){
    cin>>n>>m;
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        a[i]=read();
        bel[i]=(i-1)/siz+1;
        if(bel[i]!=bel[i-1])L[bel[i]]=i;
        if(bel[i]!=i/siz+1||i==n)R[bel[i]]=i;
    }
}
inline void push_down(int blk){
    for(int i=L[blk];i<=R[blk];i++)tag[i]=tag[i]+laz[blk];
    laz[blk]=make_pair(0,0);
}
inline void update(int l,int r,Pair opt){
    push_down(bel[l]);
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++)tag[i]=tag[i]+opt;
        return;
    }
    push_down(bel[l]);
    push_down(bel[r]);
    for(int i=l;i<=R[bel[l]];i++)tag[i]=tag[i]+opt;
    for(int i=L[bel[r]];i<=r;i++)tag[i]=tag[i]+opt;
    for(int i=bel[l]+1;i<bel[r];i++)laz[i]=laz[i]+opt;
}
inline int powmod(int a,int b,int p){
    int c=1;
    for(;b;b>>=1,a=a*a%p)if(b&1)c=c*a%p;
    return c;
}
int ans;
signed main(){
    // freopen("read.in","r",stdin);
    init();
    while(m--){
        int opt=read(),l=read(),r=read();
        if(opt==1)update(l,r,make_pair(1,0));
        else update(l,r,make_pair(0,1));
    }
    for(int i=1;i<=bel[n];i++)push_down(i);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=tag[i].p1;j++){
            a[i]=sqrt(a[i]);
            if(a[i]==1)break;
        }
        a[i]=powmod(a[i],powmod(2,tag[i].p2,P-1),P);
        ans+=a[i];
        ans%=P;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：cirnovsky (赞：4)

考虑线段树。

当然不能直接维护序列，我们来维护序列元素的指数。

具体来说，若 $a_i=(c^{2})^{b_i}$，我们维护的就是 $b_i$，当然 $c^2$ 也要维护。

这里不能取一次方，否则 $b_i$ 为奇数时就不能开方了。

开方就是花神的做法，能开就直接开，否则就对指数打减标记。

平方简单，直接对指数打加标记。

最后统计答案就遍历线段树，然后快速幂计算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls (x<<1)
#define rs (x<<1|1)
const int mod=998244353;
int pwr[8000010],val[800010],tag[800010],n,m,a[200010];//,b[200010];
int qkpow(int bas,int fur,int mod){
	int res=1;
	while(fur){
		if(fur&1)res=res*bas%mod;
		bas=bas*bas%mod,fur>>=1;
	}
	return res%mod;
}
void psup(int x){pwr[x]=min(pwr[ls],pwr[rs]),val[x]=max(val[ls],val[rs]);}
void psdn(int x){
	if(tag[x]){
//		int m=(l+r)/2;
		pwr[ls]+=tag[x],pwr[rs]+=tag[x];
		tag[ls]+=tag[x],tag[rs]+=tag[x];
		tag[x]=0;
	}
}
void build(int l,int r,int x){
	if(l==r)return(void)((pwr[x]=0,val[x]=a[l]));
	int m=(l+r)/2;
	build(l,m,ls),build(m+1,r,rs);
	psup(x);
}
void open(int l,int r,int x,int ql,int qr){
	if(val[x]<=1)return;
	if(l>=ql&&r<=qr&&pwr[x]>=1)return void((tag[x]--,pwr[x]--));
	if(l==r) {
		if(pwr[x]) return void(pwr[x] --);
		return void(val[x]=sqrt(val[x]));
	}
	int m=(l+r)/2;psdn(x);
	if(m>=ql)open(l,m,ls,ql,qr);
	if(m<qr)open(m+1,r,rs,ql,qr);
	psup(x);
}
void pinf(int l,int r,int x,int ql,int qr){
	if(val[x]<=1)return;
	if(l>qr||r<ql)return;
	if(l>=ql&&r<=qr)return(void)((tag[x]++,pwr[x]++));
	int m=(l+r)/2;psdn(x);
	if(m>=ql)pinf(l,m,ls,ql,qr);
	if(m<qr)pinf(m+1,r,rs,ql,qr);
	psup(x);
}
//int get(int t){
//	int res=0;
//	if(t==1)return 0;
//	while(1){
//		int tmp=pow(t,0.5);
//		if(tmp*tmp==t)t=tmp,res++;
//		else break;
//	}
//	return res;
//}
int solve(int l,int r,int x){
	if(l==r){
		if(pwr[x]>0)return qkpow(val[x],qkpow(2,pwr[x],mod-1),mod);
		else return val[x];
	}
	int m=(l+r)/2;psdn(x);
	return (solve(l,m,ls)+solve(m+1,r,rs))%mod;
}
signed main(){
	scanf("%lld%lld",&n,&m);
//	memset(pwr,0x7f,sizeof(pwr));
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
//		b[i]=get(a[i]);
//		if(b[i]>0)a[i]=pow(a[i],1.0/(b[i]*2));
	}
	build(1,n,1);
	while(m--){
		int t,l,r;scanf("%lld%lld%lld",&t,&l,&r);
		if(t==1)open(1,n,1,l,r);
		else pinf(1,n,1,l,r);
	}
	printf("%lld\n",solve(1,n,1));
	return 0;
}
//don't forget to mod
```

---

## 作者：EternalEpic (赞：3)

我们可以想到对于一类区间取整开方每次至少减少原数的一半，它至多只能做 $log_2{n}$ 次，所以可以区间全部单点修改，暴力进行。如果最大数小于等于 $1$ 了，就可以忽略。

对于平方操作，可以用线段树区间维护指数。

对于区间指数最小值大于 $1$ 的，可以打标记修改。

这样就可以~~暴打分块了~~(雾)。

```cpp
// Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>

#define lowbit(x) (x & -x)

using namespace std;

inline char gc(void) {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x) {
	T f = 1; x = 0; static char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
	x *= f;
}

inline void readstr(char *s) {
	do *s = gc(); while ((*s == ' ') || (*s == '\n') || (*s == '\r'));
	do *(++s) = gc(); while ((~*s) && (*s != ' ') && (*s != '\n') && (*s != '\r'));
	*s = 0; return;
}

inline void readch(char&x) { while (isspace(x = gc())); }

char pf[100000], *o1 = pf, *o2 = pf + 100000;
#define ot(x) (o1 == o2 ? fwrite(pf, 1, 100000, stdout), *(o1 = pf) ++= x : *o1 ++= x)
template <class T>
inline void println(T x, char c = '\n') {
	if (x < 0) ot(45), x = -x;
	static char s[15], *b; b = s;
	if (!x) *b ++= 48;
	for (; x; * b ++= x % 10 + 48, x /= 10);
	for (; b-- != s; ot(*b)); ot(c);
}

template <class T> inline void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

template <class T> inline void writeln(T x, char c = '\n') { write(x); putchar(c); }
template <class T> inline void chkmax(T &x, const T y) { x > y ? x = x : x = y; }
template <class T> inline void chkmin(T &x, const T y) { x < y ? x = x : x = y; }

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

typedef long long ll;
typedef pair <int, int> pii;

const int mod = 998244353;
inline void inc(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
inline int qpow(int a, int b, int p) {
	int ret = 1;
	for (; b; b >>= 1, a = 1ll * a * a % p)
		if (b & 1) ret = 1ll * ret * a % p;
	return ret;
}

const int Maxn = 2e5 + 5;
int n, m, a[Maxn];
int tmx[Maxn << 2], tmn[Maxn << 2], tag[Maxn << 2];
inline void pushup(int pos) {
	tmx[pos] = max(tmx[pos << 1], tmx[pos << 1 | 1]);
	tmn[pos] = min(tmn[pos << 1], tmn[pos << 1 | 1]);
}

inline void addtag(int pos, int val) { tmn[pos] += val; tag[pos] += val; }
inline void pushdown(int pos) {
	if (tag[pos] != 0) {
		addtag(pos << 1, tag[pos]);
		addtag(pos << 1 | 1, tag[pos]);
		tag[pos] = 0;
	}
}

inline void build(int pos, int l, int r) {
	if (l == r) { tmx[pos] = a[l]; return; }
	int mid = l + r >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	pushup(pos);
}

inline void sqrt(int pos, int l, int r, int L, int R) {
	if (tmx[pos] <= 1) return;
	if (L <= l && R >= r && tmn[pos]) return addtag(pos, -1);
	if (l == r) {
		if (tmn[pos]) --tmn[pos];
		else tmx[pos] = (int) std :: sqrt(tmx[pos]);
		return;
	}
	
	int mid = l + r >> 1; pushdown(pos);
	if (L <= mid) sqrt(pos << 1, l, mid, L, R);
	if (R > mid) sqrt(pos << 1 | 1, mid + 1, r, L, R);
	pushup(pos);
}

inline void sqr(int pos, int l, int r, int L, int R) {
	if (tmx[pos] <= 1) return;
	if (L <= l && R >= r) return addtag(pos, 1);
	int mid = l + r >> 1; pushdown(pos);
	if (L <= mid) sqr(pos << 1, l, mid, L, R);
	if (R > mid) sqr(pos << 1 | 1, mid + 1, r, L, R);
	pushdown(pos);
}

inline int query(int pos, int l, int r) {
	if (l == r) return qpow(tmx[pos], qpow(2, tmn[pos], mod - 1), mod);
	int mid = l + r >> 1, ret; pushdown(pos);
	ret = query(pos << 1, l, mid);
	inc(ret, query(pos << 1 | 1, mid + 1, r));
	return ret;
}

signed main(void) {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	for (int opt, l, r; m; m--) {
		read(opt), read(l), read(r);
		if (opt == 1) sqrt(1, 1, n, l, r);
		else sqr(1, 1, n, l, r);
	} writeln(query(1, 1, n));
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}

/**/

```


---

