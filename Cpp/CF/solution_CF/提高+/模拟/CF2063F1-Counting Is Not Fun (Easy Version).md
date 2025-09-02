# Counting Is Not Fun (Easy Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，此版本对 $t$ 和 $n$ 的限制更小。仅当解决所有版本的问题时方可进行 hack。

小 John 现在很富有，终于买得起能容纳自己和最喜爱括号序列的大房子了。但不知为何，他得到了大量括号！沮丧之下，他用"佛掌"击穿了天花板。一个括号序列被称为平衡的，当且仅当其可以通过以下形式文法构造：

1. 空序列 $\varnothing$ 是平衡的。
2. 若括号序列 $A$ 是平衡的，则 $\mathtt{(}A\mathtt{)}$ 也是平衡的。
3. 若括号序列 $A$ 和 $B$ 是平衡的，则拼接序列 $AB$ 也是平衡的。

例如，序列 "(())()"、"()"、"(()(()))" 和空序列是平衡的，而 "(()" 和 "(()))(" 则不是。

给定一个平衡括号序列 $s$，当满足以下条件时，索引对 $(i,j)$（$i<j$）被称为好对：$s_i$ 是 '('，$s_j$ 是 ')'，且这两个括号是在构造序列 $s$ 时通过规则 2 同时添加的。例如，序列 "(())()" 有三个不同的好对：$(1,4)$、$(2,3)$ 和 $(5,6)$。可以证明，任何包含 $2n$ 个括号的平衡括号序列恰好有 $n$ 个不同的好对，且无论用何种规则顺序构造同一括号序列，得到的好对集合都相同。

Emily 将与 John 进行括号猜谜游戏。游戏规则如下：

初始时，John 有一个包含 $n$ 个不同好对的平衡括号序列 $s$，但 Emily 不知道其内容。John 告诉 Emily $n$ 的值，并要求 Emily 猜测该序列。

在 $n$ 轮中，John 每轮给出如下形式的线索：
- $l\;r$：序列 $s$ 包含好对 $(l,r)$。

John 给出的线索互不相同且互不矛盾。

在某个时刻，Emily 可以确定满足当前所有线索的平衡括号序列是唯一的。例如，假设 Emily 知道 $s$ 有 $3$ 个好对，并包含好对 $(2,5)$。在 $5$ 个有 $3$ 个好对的平衡括号序列中，只有序列 "((()))" 包含好对 $(2,5)$。因此，可以看出 Emily 并不总是需要 $n$ 轮才能猜出 $s$。

为了尽早确定 $s$ 的内容，Emily 希望知道每轮线索后符合条件的平衡括号序列数量。显然这对 Emily 来说并非易事，尤其当存在大量好对时。现在轮到你来帮助 Emily。给定所有线索，你需要在每轮前后输出答案。由于答案可能很大，请对 $998\,244\,353$ 取模。

## 说明/提示

样例中的第一个测试用例已在题目描述中解释。

第三个测试用例的解释如下：可以证明存在 $132$ 个有 $6$ 个好对的平衡括号序列。每接收一条线索后的答案如下：
1. 收到好对 $(2,3)$ 后，存在 $42$ 个符合条件的序列。
2. 收到好对 $(1,6)$ 后，存在 $5$ 个同时包含 $(2,3)$ 和 $(1,6)$ 的序列。
3. 收到好对 $(7,8)$ 后，存在 $2$ 个满足三个好对的序列，分别为 "(()())()(())" 和 "(()())()()()"。
4. 收到好对 $(9,12)$ 后，仅剩 $1$ 个满足四个好对的序列，即 "(()())()(())"。
之后的第五、第六条线索接收后答案均为 $1$，因为此时已确定唯一序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
2 5
1 6
3 4
4
1 6
7 8
2 3
4 5
6
2 3
1 6
7 8
9 12
10 11
4 5```

### 输出

```
5 1 1 1
14 2 2 1 1
132 42 5 2 1 1 1```

# 题解

## 作者：TTpandaS (赞：5)

长度为 $2n$ 的合法字符串共有 $f(n)$ 种不同的方案，其中 $f$ 为卡特兰数。

每一对括号能贡献的空位为内部未被其余合法字符串包含的位置数量。新增一对括号，考虑对答案的影响。答案会乘上其内部的贡献，但是对于其第一对包含它的括号（不妨称为外包括号），外包括号的贡献会减少其内部的贡献即可。找到右侧第一个失配的右括号即为外包括号。

由于 F1 $n \leq 5000$，所以可以对于每对新增括号 $O(n)$ 计算贡献，$O(n)$ 寻找第一对外包括号。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005,mod=998244353;
int T;
int dp[N],inv[N];
int qpow(int x,int p){
	int res=1;
	while(p){
		if(p&1){
			res=res*x%mod; 
		}
		x=x*x%mod;
		p>>=1;
	}
	return res;
}
int n,l[N],r[N];
int f[N*2],c[N*2];
void solve(){
	cin>>n;
	for(int i=1;i<=n*2+1;i++){
		f[i]=c[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
	}
	cout<<dp[n]<<' ';
	int ans=dp[n];
	f[2*n+1]=n;
	c[2*n+1]=-1;
	for(int i=1;i<=n;i++){
		c[l[i]]=1,c[r[i]]=-1;
		stack<int> S;
		int tot=r[i]-l[i]-1;
		for(int j=l[i]+1;j<r[i];j++){
			if(c[j]==1){
				S.push(j);
			}
			if(c[j]==-1){
				int L=S.top(),R=j;
				S.pop();
				if(S.empty()){
					tot-=(R-L+1);
				}
			}
		}
//		cerr<<i<<':'<<tot<<endl;
		int d=tot/2;
		f[r[i]]=d;
		ans=ans*dp[d]%mod;
		stack<int> s;
		for(int j=r[i]+1;j<=2*n+1;j++){
			if(c[j]==-1){
				if(s.empty()){
					ans=ans*inv[f[j]]%mod;
					f[j]-=d+1;
					ans=ans*dp[f[j]]%mod;
					break;
				}
				else{
					s.pop();
				}
			}
			if(c[j]==1){
				s.push(j);
			}
		}
		cout<<ans<<' ';
	}
	cout<<endl;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	dp[0]=dp[1]=inv[0]=inv[1]=1; 
	for(int i=2;i<=5000;i++){
		for(int j=1;j<=i;j++){
			dp[i]=(dp[i]+dp[j-1]*dp[i-j]%mod)%mod;
		}
		inv[i]=qpow(dp[i],mod-2);
	}
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：D0000 (赞：5)

### 题意

有一个长度为 $2n$ 的括号序列，依次告诉你 $n$ 对匹配的括号，需要在每次告诉你之前和之后回答随便填没告诉你的位置，能构成多少个合法的括号序列。

### 解法

#### F1
首先 $n$ 对括号组成的合法的括号序列是 Catalan 数，这里记作 $H_n$。

可以假设外面套了一个括号把整个串包起来。

对于每个括号，如果它中间未被里面的括号串包含（直接包含）的空位置个数为 $k$，则这 $k$ 个位置需要成为一个合法的括号串，有 $H_k$ 种。而答案应当是 $H_k$ 的乘积。

比如对于括号序列 `((..)...(....(....)..).)` 最大的括号直接包含 $4$ 个空位置，其他几个括号直接包含 $2,6,4$ 个空位置，因此总共有 $H_2H_1H_3H_2$ 种方案。

证明也很简单，一对匹配的括号中的括号需要满足左括号数等于右括号数，且任意前缀左括号数不应当小于右括号数，这与括号串没有本质区别。

Catalan 数能够预处理。新加入的括号只会改变最小的一个包含它的括号对答案的贡献。只需要每次加括号时改变最小的一个包含它的括号的 $k$ 值，以及通过枚举所有它包含的位置来计算这个新括号对的 $k$ 值。能够 $O(n^2)$ 解决。这样，可以通过 F1。
#### F2
注意到时间复杂度的瓶颈是枚举一个括号包含的位置有没有其他括号。

用线段树可以找最小的包含一个括号的括号对。对于每个 $l,r$ 括号对，在 $l$ 处插入 $r$，用 MAX 线段树，每次查询的就是 $[0,l]$ 中最后一个大于 $r$ 的位置。

同样可以用线段树找区间中已经被更小的括号对包含的位置。对于每个位置，最小的一个包含它的括号对右边的一个是 $r$，则在 $r$ 处加 $1$。这样查询 $[l,r]$ 的和即可，因为给定的括号对是合法的。如果查询的值是 $s$。那么在线段树 $r$ 位置加上 $r-l-1-s$ 即完成了对线段树的维护。

时间复杂度 $O(n\log n)$。

### 代码
```cpp

#include<cstdio>
#include<utility>
#include<algorithm>
int n,sgt[4000005],tag[4000005],ans,l,r;
int ak[4000005],mod=998244353,inv[4000005],q[4000005],qv[4000005];
int stt[4000005];
void aa(int x,int v,int l=0,int r=2*n+1,int o=1){
    stt[o]+=v;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)aa(x,v,l,mid,o*2);
    else aa(x,v,mid+1,r,o*2+1);
}
int qq(int ll,int rr,int l=0,int r=2*n+1,int o=1){
    if(ll<=l&&rr>=r)return stt[o];
    int mid=(l+r)>>1;
    if(ll<=mid&&rr>mid)return qq(ll,rr,l,mid,o*2)+qq(ll,rr,mid+1,r,o*2+1);
    if(ll<=mid)return qq(ll,rr,l,mid,o*2);
    return qq(ll,rr,mid+1,r,o*2+1);
}
void build(int l=0,int r=2*n+1,int o=1){
    sgt[o]=tag[o]=0;stt[o]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(l,mid,o*2);
    build(mid+1,r,o*2+1);
}
void add(int ll,int rr,int l=0,int r=2*n+1,int o=1){
    if(rr>sgt[o])sgt[o]=rr,tag[o]=ll;
    if(l==r)return void();
    int mid=(l+r)>>1;
    if(ll<=mid)add(ll,rr,l,mid,o*2);
    else add(ll,rr,mid+1,r,o*2+1);
}
std::pair<int,int>qu(int ll,int rr,int vv,int l=0,int r=2*n+1,int o=1){
	if(sgt[o]<vv)return {-1e9,-1e9};
    if(l==r)return {tag[o],sgt[o]};
    int mid=(l+r)>>1;
    if(ll<=l&&rr>=r){
        if(sgt[o*2+1]>vv)return qu(ll,rr,vv,mid+1,r,o*2+1);
        return qu(ll,rr,vv,l,mid,o*2);
    }
    if(ll<=mid&&rr>mid)return std::max(qu(ll,rr,vv,l,mid,o*2),qu(ll,rr,vv,mid+1,r,o*2+1));
    if(ll<=mid)return qu(ll,rr,vv,l,mid,o*2);
    return qu(ll,rr,vv,mid+1,r,o*2+1);
}
int lto[2000005];
void Main(){
    scanf("%d",&n);ans=q[n],ak[0]=2*n;build();add(0,2*n+1);
    
    printf("%d ",ans);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l,&r);
        std::pair<int,int> x=qu(0,l,r);
		int su=qq(l,r);add(l,r);lto[l]=i;int xx=lto[x.first];
        ak[i]=r-l-1-su;ans=1ll*ans*(q[ak[i]/2])%mod;aa(r,ak[i]+2);aa(x.second,-ak[i]-2);
        ans=1ll*ans*qv[ak[xx]/2]%mod;ak[xx]-=ak[i]+2;ans=1ll*ans*q[ak[xx]/2]%mod;
        printf("%d ",ans);
    }
    puts("");
}
int mul(int a,int x){
    if(!x)return 1;
    int t=mul(a,x/2);
    if(x%2)return 1ll*t*t%mod*a%mod;
    return 1ll*t*t%mod;
}
int main(){
    inv[0]=q[0]=qv[0]=inv[1]=1;
    for(int i=1;i<=5e5;i++)inv[i+1]=mul(i+1,mod-2),q[i]=1ll*q[i-1]*(2*i)%mod*(2*i-1)%mod*inv[i]%mod*inv[i+1]%mod,qv[i]=mul(q[i],mod-2);
    int t;
    scanf("%d",&t);
    while(t--)Main();
}

```

---

## 作者：Kingna (赞：2)

## [CF2063F1+F2 Counting Is Not Fun](https://www.luogu.com.cn/problem/CF2063F1)

### 题目大意

现在有一个隐藏的长度恰好为 $2n$ 的『合法括号串』$s$。依次有 $n$ 条信息，每条信息给出 $l,r$ 表示 $s_l=\texttt{(},s_r=\texttt{)}$ 且 $s_l,s_r$ 是可以直接匹配的。回答 $n+1$ 个问题：

- 第一个问题回答没有给定任何信息时 $s$ 的所有可能情况。
- 第 $i+1$ 个问题回答给定前 $i$ 条信息时 $s$ 的所有可能情况。

答案对 $998244353$ 取模。

### 题目思路

先将 $H_n$ 记为 $n$ 对括号组成的合法的括号序列个数，是 Catalan 数。如果对于每一个括号，如果它中间未被里面括号包含的空位置个数为 $k$，那么这 $k$ 个位置则是一个合法的括号串，方案数为 $H_k$。答案就是 $H_k$ 的乘积。用栈来模拟，如果遇到了右括号，那么弹出栈顶直到遇到了左括号。弹出栈的元素数量就是这对括号未被里面括号包含的空位置个数。

F1 只需要将这些操作模拟一遍，复杂度 $O(n^2)$。F2 则需要用数据结构来维护。

---


考虑加入一对括号后，将本来的 $H_x$ 分裂成 $H_y$ 和 $H_{x-y-1}$。这样做并不好做，考虑倒着操作。

最开始先将所有括号加入，再依次将括号对删除。假设其父亲节点对应的空位置为 $x$ 个，自己对应的空位置为 $y$ 个，则合并之后答案会将 $H_x$ 和 $H_y$ 除掉，再乘上新的 $H_{x+y+1}$。同时，父亲节点的空位置个数累计上 $y$。因为是倒着操作，则最开始每个括号对所对应的父亲括号对已经完全确定了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 6e5 + 5, mod = 998244353;

int T, n, fac[N], invfac[N], ans[N], a[N], fa[N], val[N];

int qpow(int a, int k, int p) {
	int res = 1;
	while (k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

void init() {
	fac[0] = 1;
	_for(i, 1, N - 5) fac[i] = fac[i - 1] * i % mod;
	invfac[N - 5] = qpow(fac[N - 5], mod - 2, mod);
	_pfor(i, N - 6, 0) invfac[i] = invfac[i + 1] * (i + 1) % mod; 
}

int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * invfac[n - m] % mod * invfac[m] % mod;
}

int calc(int x) {
	x /= 2;
	return (C(2 * x, x) - C(2 * x, x + 1) + mod) % mod;
}

int p[N];

int find(int x) {
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}


signed main() {
	cin >> T; init(); 
	while (T--) {
		cin >> n;
		_for(i, 0, n) p[i] = i, val[i] = 0;
		_for(i, 1, n) {
			int l, r;
			cin >> l >> r;
			a[l] = a[r] = i;
		}
		stack<int> stk; stk.push(0); 
		_for(i, 1, 2 * n) {
			if (a[i] != stk.top()) stk.push(a[i]);
			else stk.pop(), fa[a[i]] = stk.top(); // 处理父亲括号
		}
		int res = 1;
		_for(i, 0, n) res = res * calc(val[i]) % mod;
		ans[n + 1] = res; 
		_pfor(i, n, 1) {
			int t = find(fa[i]); p[i] = t;
			res = res * qpow(calc(val[i]), mod - 2, mod) % mod * qpow(calc(val[t]), mod - 2, mod) % mod;
			val[t] += val[i] + 2;
			res = res * calc(val[t]) % mod;
			ans[i] = res;
		}
		_for(i, 1, n + 1) cout << ans[i] << ' ';
		puts("");
	}
}
```

---

## 作者：zhangxy__hp (赞：1)

考虑初始的答案，显然为卡特兰数 $H(n)$。

考虑加入一对括号 $(l,r)$ 时对答案的贡献。（$(l,r)$ 表示有一对括号，左括号在 $l$，右括号在 $r$。）

我们默认一开始有一对括号 $(0,n+1)$。当出现一对括号 $(l,r)$ 时，首先要加上 $(l,r)$ 中的贡献，然后最小的包含了 $(l,r)$ 的括号要减去 $(l,r)$ 之间的贡献。具体地，可以用 $hp_i$ 表示以 $i$ 为右括号的括号中还有多少个空位，则这一对括号的贡献即为 $H(hp_i)$。预处理卡特兰数，时间复杂度为 $O(n^2)$。

```cpp
#include<cstdio>
#include<iostream>
#include<stack>
#define ll long long
#define il inline

using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=5e3+5,mod=998244353;
il int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1){
			res=res*1ll*x%mod;
		}
		x=x*1ll*x%mod,y>>=1;
	}
	return res;
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T,*fac=new int[maxn](),*inv=new int[maxn]();
	fac[0]=fac[1]=1;
	for(int i=2;i<=5e3;i++){
		for(int j=1;j<=i;j++){
			(fac[i]+=fac[j-1]*1ll*fac[i-j]%mod)%=mod;
		}
	}
//	for(int i=0;i<=5e3;i++){
//		cout<<fac[i]<<" ";
//	}
//	puts("");
	for(int i=0;i<=5e3;i++){
		inv[i]=qpow(fac[i],mod-2);
	}
//	for(int i=0;i<=5e3;i++){
//		cout<<fac[i]*1ll*inv[i]%mod<<" ";
//	}
//	puts("");
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int *hp=new int[n*2+5](),*f=new int[n*2+5]();
		hp[n<<1|1]=n,f[n<<1|1]=-1;
		int ans=fac[n];
		cout<<ans<<" ";
		for(int i=1,l,r,tot;i<=n;i++){
			cin>>l>>r;
			f[l]=1,f[r]=-1;
			tot=r-l-1;
			stack<int> zhan;
			for(int j=l+1;j<r;j++){
				if(f[j]==1){
					zhan.push(j);
				}
				else if(f[j]==-1){
					int tmp=zhan.top();
					zhan.pop();
					if(zhan.empty()){
						tot-=j-tmp+1;
					}
				}
			}
//			cout<<tot<<"\n";
			tot>>=1;
			ans=ans*1ll*fac[tot]%mod;
			hp[r]=tot;
			for(int j=r+1;j<=(n<<1|1);j++){
				if(f[j]==1){
					zhan.push(j);
				}
				else if(f[j]==-1){
					if(zhan.empty()){
						ans=ans*1ll*inv[hp[j]]%mod;
						hp[j]-=tot+1;
						ans=ans*1ll*fac[hp[j]]%mod;
						break;
					}
					else{
						zhan.pop();
					}
				}
			}
			cout<<ans<<" ";
		}
		cout<<"\n";
		delete[] hp,f;
	}
	delete[] fac,inv;
	return 0;
}
}
int main(){return asbt::main();}
```

---

## 作者：SUNCHAOYI (赞：1)

所有方案数均基于卡特兰数，不妨设 $F(x) = \dfrac{\tbinom{2x}{x}}{x + 1}$ 来表示卡特兰数。

初始时显然答案为 $F(n)$。当有括号加入时，未被添加括号的位置的贡献不会超过最外层已匹配的括号。举个例子，当 $?????? \to \red{(}??\red{)}??$ 时，答案就变化为 $F(3) \to F(1) \times F (1)$。

因此可以先将这 $n$ 对括号进行编号，然后借助栈，当遇到未被添加括号的位置时，将贡献加在栈顶的括号对应的编号上，最后根据乘法原理求解即可。

时间复杂度 $O(n^2)$，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5005;
const int MOD = 998244353;
inline int read ();
int t,n,p[MAX << 1],l[MAX],r[MAX],cnt[MAX];ll ans,f[MAX << 1],inv[MAX << 1],inv2[MAX << 1]; 
stack <int> s;
ll qpow (ll x,ll y)
{
	ll res = 1;
	while (y)
	{
		if (y & 1) res = res * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return res;
}
ll catalan (int x) {return f[2 * x] * inv[x] % MOD * inv[x] % MOD * inv2[x + 1] % MOD;} 
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	f[0] = inv[0] = 1;
	for (int i = 1;i <= 10000;++i) f[i] = f[i - 1] * i % MOD,inv2[i] = qpow (i,MOD - 2);
	inv[10000] = qpow (f[10000],MOD - 2);
	for (int i = 9999;i;--i) inv[i] = inv[i + 1] * (i + 1) % MOD;
	s.push (0);//最外层的贡献 
	t = read ();
	while (t--)
	{
		n = read ();
		for (int i = 1;i <= n;++i) l[i] = read (),r[i] = read ();
		for (int i = 1;i <= 2 * n;++i) p[i] = 0;
		for (int o = 0;o <= n;++o)
		{
			for (int i = 0;i <= n;++i) cnt[i] = 0;
			p[l[o]] = o;p[r[o]] = -o;ans = 1;//新添加的括号进行标记
			for (int i = 1;i <= 2 * n;++i)
			{
				if (!p[i]) ++cnt[s.top ()];//未被添加的位置
				else if (p[i] < 0) s.pop ();//已经匹配，弹出即可
				else s.push (p[i]);
			}
			for (int i = 0;i <= n;++i) ans = ans * catalan (cnt[i] / 2) % MOD;//注意左右括号各贡献一次，因此需要除以 2
			printf ("%lld ",ans);
		}
		puts ("");
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

# F2 题解链接

<https://www.luogu.com.cn/article/rfe0h0wu>

# 题目翻译

我们称可以用以下操作生成的括号串为一个『合法括号串』：

1. 空串。
2. 如果串 $A$ 是『合法括号串』，那么 $\texttt{(}A\texttt{)}$ 也是一个『合法括号串』。
3. 如果串 $A$ 和串 $B$ 都是『合法括号串』，那么 $AB$ 也是一个『合法括号串』。

现在有一个隐藏的长度恰好为 $2n$ 的『合法括号串』$s$。依次有 $n$ 条信息，每条信息给出 $l,r$ 表示 $s_l=\texttt{(},s_r=\texttt{)}$ 且 $s_l,s_r$ 是通过操作 2 被**同时**添加的一对括号。

回答 $n+1$ 个问题：

- 第一个问题回答没有给定任何信息时 $s$ 的所有可能情况。
- 第 $i+1$ 个问题回答给定前 $i$ 条信息时 $s$ 的所有可能情况。

答案对 $998244353$ 取模。

**本题为 Easy Version。**

多测。

$1\leq t\leq 10^3$，$2\leq n,\sum n\leq 5000$，$1\leq l_i\lt r_i\leq 2n$。

# 题目思路

以下约定 $\operatorname{Cat}(n)=\binom{2n}{n}-\binom{2n}{n+1}$ 表示卡特兰数第 $n$ 项。

为了方便考虑，我们假定在 $(0,2n+1)$ 的位置初始就有一对括号。这显然不影响答案。

括号串计数优先往卡特兰数上想，恰好样例中答案只有卡特兰数。一个笨笨的猜测是，我们把那些已经确定的括号遮住不看，设剩余了 $2(n-k)$ 个位置，答案是 $\operatorname{Cat}(n-k)$。

但是这样子我们的信息的限制完全不对。例如 $\texttt{(\underline{~}((\underline{~}\underline{~}))\underline{~})}$ 这种情况。实际上由于已经确定的括号“拦”住了，导致填 $\texttt{(}
{\color{red}{\texttt{(}}}
\texttt{((}
{\color{red}{\texttt{)(}}}\texttt{))}{\color{red}{\texttt{)}}}\texttt{)}$ 这样子的括号串虽然是合法的，但是并不满足给定的信息，即 $(4,8)$ 这对括号是通过 2 操作添加的，因为中间的 $\texttt{)(}$ 并不是合法括号串。

之后不难想到，如果我们给括号标层：给每个括号内部区域加上 $1$。也就是对于一对括号 $(l,r)$，我们把左括号位置 $+1$，右括号的下一个位置 $-1$，然后做前缀和。最后左右括号位置的值就是这个括号的层。不难发现左括号和右括号位置的值一定是一样的。

之后我们去刻画这个限制。这个限制相当于说 $[l+1,r-1]$ 是一个『合法括号串』。递归地考虑这个问题，感性理解一下，我们设此时有一个层级为 $k$ 的括号 $(l_k,r_k)$，那么它内部可能会有很多 $(l_{k+1},r_{k+1})$。我们忽略这些 $(l_{k+1},r_{k+1})$ 的部分，设剩下的空白的没有信息的位置有 $x$ 个，这个 $(l_k,r_k)$ 内部的贡献就是 $\operatorname{Cat}(x)$。

最后我们把每层的括号的贡献给乘起来就是最后答案。

这个理解很好理解，相当于是把 $(l_{k+1},r_{k+1})$ 的部分全部扔掉然后在里面填合法括号串。然而在合法括号串的任何位置插入一个合法括号串仍然是合法的。所以这些 $(l_{k+1},r_{k+1})$ 的内部只要填了合法括号串，怎么填是无所谓的。

F1 实现的时候直接每次暴力添加括号然后扫一遍不难统计。但是为了扩展到 F2，我们这样的每次 $\mathcal O(n)$ 扫一遍看起来就没什么前途。

我们继续刻画这个添加一对括号对答案的影响。添加一个括号串相当于是把自己父亲的一点贡献拆给自己。把一个 $\operatorname{Cat}(y)$ 拆成 $\operatorname{Cat}(y-x-1)\operatorname{Cat}(x)$。我们求出这个 $x$ 就好。

但是这个也许有点困难了，至少我尝试实现发现需要维护很多东西。正难则反，我们把添加括号改成拆括号，询问逆序。

逆序之后相当于是一个 $\operatorname{Cat}(x)$ 和一个 $\operatorname{Cat}(y)$ 合并成了 $\operatorname{Cat}(x+y+1)$。这个就很轻松了，我们只需要支持一个事情：查询这对括号的上一层父亲括号。设这对括号层级是 $rk$，父亲括号指包裹他的层级为 $rk-1$ 的那一对括号。

要找父亲括号我们要首先求出这个 $rk$。刚才说括号标层是差分描述的，差分之后前缀和相当于是后缀 $+1$ 或后缀 $-1$，查询单点的值。

之后考虑查父亲括号。父亲括号相当于是某个前缀的最后一个值为 $rk-1$ 的位置并且这个位置被标记成了左括号。

在 F1 我们把这些操作模拟一遍就可以。单次复杂度 $\mathcal O(n)$，总复杂度 $\mathcal O(n^2)$。

# 代码链接

代码里有一段很长的 modint 板子。

[CF submission 302480835](https://codeforces.com/contest/2063/submission/302480835)

---

## 作者：ax_by_c (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/axbyc/articles/18732221)

题意：有一个长度为 $2n$ 的空括号序列，每次加入一对括号，求一开始和每次加入后补全空的部分使得整个括号序列合法且每次加入的括号恰好匹配的方案数，对 $998244353$ 取模，Easy Version $2\le n,\sum n\le5000$，Hard Version $2\le n,\sum n\le3\times 10^5$。

## 卡特兰数

先复习一下卡特兰数。

有一个网格图，你一开始在 $(0,0)$，要走到 $(2n,0)$。设你在 $(x,y)$，那么你下一步可以走到 $(x+1,y-1)$ 和 $(x+1,y+1)$，并且你不能走到直线 $y=0$ 的下方，求方案数 $C_n$。

考虑用 $\binom{2n}{n}$ 减去不符合限制的方案数。如果一个方案不合法，那么一定有一个时刻满足 $y=-1$。将路径中从 $(0,0)$ 走到这个位置的部分关于 $y=-1$ 对称，那么就能得到一条从 $(0,-2)$ 走到 $(2n,0)$ 的路径。

注意到对于任意一条从 $(0,-2)$ 走到 $(2n,0)$ 的路径，也一定有一个时刻满足 $y=-1$。同样将路径中从 $(0,-2)$ 走到这个位置的部分关于 $y=-1$ 对称，那么就能得到一条从 $(0,0)$ 走到 $(2n,0)$ 的不符合限制的路径。也就是说从 $(0,0)$ 走到 $(2n,0)$ 的不合法路径与从 $(0,-2)$ 走到 $(2n,0)$ 的路径一一对应。

于是有关键结论：不合法方案数等于从 $(0,-2)$ 走到 $(2n,0)$ 的方案数。而从 $(0,-2)$ 走到 $(2n,0)$ 的方案数即为 $\binom{2n}{n+1}$，因此 $C_n=\binom{2n}{n}-\binom{2n}{n+1}$。

## F1

为了方便直接在最外面加上一层括号。

加入括号相当于将里面和外面分成两部分，将内部括号包含部分忽略后内部方案数即为卡特兰数。

可以先建出括号结构树，然后每次暴力即可，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int mod=998244353;
const int N=1e4+5;
int ksm(int a,int b,int p){
	a=a%p;
	int r=1;
	while(b){
		if(b&1)r=(ll)r*a%p;
		a=(ll)a*a%p;
		b>>=1;
	}
	return r%p;
}
int fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n;i>=1;i--)inv[i-1]=(ll)inv[i]*i%mod;
}
int C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return (ll)fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int CC(int n){
	return (C(n,n/2)-C(n,n/2+1)+mod)%mod;
}
int n,l[N],r[N],mch[N];
vector<int>g[N];
bool mk[N];
void bld(int l,int r){
	int pos=l+1;
	while(pos<r){
		g[l].push_back(pos);
		bld(pos,mch[pos]);
		pos=mch[pos]+1;
	}
}
pii cal(int l,int r){
	pii res={1,0};
	for(auto v:g[l]){
		pii tmp=cal(v,mch[v]);
		res.first=(ll)res.first*tmp.first%mod;
		res.second+=tmp.second;
	}
	if(mk[l])res.first=(ll)res.first*CC(r-l-1-res.second)%mod,res.second=r-l+1;
	return res;
}
void slv(){
	scanf("%d",&n);
	Init(n*2);
	mch[0]=n*2+1,mch[n*2+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l[i],&r[i]);
		mch[l[i]]=r[i],mch[r[i]]=l[i];
	}
	for(int i=0;i<=n*2+1;i++)g[i].clear(),mk[i]=0;
	bld(0,n*2+1);
	mk[0]=1;
	printf("%d ",cal(0,n*2+1).first);
	for(int i=1;i<=n;i++){
		mk[l[i]]=1;
		printf("%d ",cal(0,n*2+1).first);
	}
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

## F2

加入括号看着就很难做，考虑时光倒流一下变成删除括号，那么只有删除前的实际父亲（忽略删除括号后括号结构树上的父亲）处出现变化，使用并查集维护一下实际父亲即可。

懒得精细实现了，是 $O(n\log n)$ 的，可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int mod=998244353;
const int N=6e5+5;
int ksm(int a,int b,int p){
	a=a%p;
	int r=1;
	while(b){
		if(b&1)r=(ll)r*a%p;
		a=(ll)a*a%p;
		b>>=1;
	}
	return r%p;
}
int fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n;i>=1;i--)inv[i-1]=(ll)inv[i]*i%mod;
}
int C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return (ll)fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int CC(int n){
	return (C(n,n/2)-C(n,n/2+1)+mod)%mod;
}
int n,l[N],r[N],mch[N],fa_[N],fa[N],len[N],res[N],ans,pr[N];
vector<int>g[N];
void bld(int l,int r){
	int pos=l+1;
	while(pos<r){
		g[l].push_back(pos);
		fa_[pos]=l;
		bld(pos,mch[pos]);
		pos=mch[pos]+1;
	}
	len[l]=r-l-1;
}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void rm(int l,int r){
	ans=(ll)ans*ksm(res[l],mod-2,mod)%mod;
	fa[l]=fa_[l];
	ans=(ll)ans*ksm(res[find(l)],mod-2,mod)%mod;
	len[find(l)]-=r-l+1-len[l];
	res[find(l)]=CC(mch[find(l)]-find(l)-1-len[find(l)]);
	ans=(ll)ans*res[find(l)]%mod;
}
void slv(){
	scanf("%d",&n);
	Init(n*2);
	mch[0]=n*2+1,mch[n*2+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l[i],&r[i]);
		mch[l[i]]=r[i],mch[r[i]]=l[i];
	}
	for(int i=0;i<=n*2+1;i++)g[i].clear(),fa_[i]=0,fa[i]=i,len[i]=0,res[i]=1;
	bld(0,n*2+1);
	ans=1;
	for(int i=n;i>=1;i--){
		pr[i]=ans;
		rm(l[i],r[i]);
	}
	pr[0]=ans;
	for(int i=0;i<=n;i++)printf("%d ",pr[i]);
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV1C5fWYoEat?t=3585)

---

