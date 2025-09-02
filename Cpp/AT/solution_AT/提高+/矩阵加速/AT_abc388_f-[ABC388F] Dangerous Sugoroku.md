# [ABC388F] Dangerous Sugoroku

## 题目描述

有 $N$ 个格子排成一行，依次编号为 $1, 2, \ldots, N$。

给定 $M$ 个整数对 $(L_1, R_1), (L_2, R_2), \ldots, (L_M, R_M)$。

如果对于某个 $i$，格子 $j$ 满足 $L_i \leq j \leq R_i$，那么且仅当这种情况成立时，格子 $j$ 被定义为**坏格子**。

请判断是否可以通过以下操作从格子 $1$ 移动到格子 $N$：

- 当前所在格子为 $x$。选择一个整数 $i$，使得以下所有条件都成立，然后移动到格子 $x + i$：
  - $A \leq i \leq B$
  - $x + i \leq N$
  - 格子 $x + i$ 不是坏格子

## 说明/提示

### 限制条件

- $2 \leq N \leq 10^{12}$
- $0 \leq M \leq 2 \times 10^4$
- $1 \leq A \leq B \leq 20$
- $1 < L_i \leq R_i < N\ (1 \leq i \leq M)$
- $R_i < L_{i+1}\ (1 \leq i \leq M-1)$
- 所有输入的值均为整数

### 样例解释 1

可以按 $1 \to 6 \to 9 \to 12 \to 16 \to 21 \to 24$ 这样的方式移动到格子 $N$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
24 2 3 5
7 8
17 20```

### 输出

```
Yes```

## 样例 #2

### 输入

```
30 1 5 8
4 24```

### 输出

```
No```

## 样例 #3

### 输入

```
100 4 10 11
16 18
39 42
50 55
93 99```

### 输出

```
Yes```

# 题解

## 作者：sunkuangzheng (赞：16)

设 $dp_i$ 表示能否到达 $i$，有转移 $dp_i = \operatorname{OR}_{j=a}^b dp_{i-j}$ 且 $i$ 不是坏的。

直接矩阵快速幂优化即可，压位实现矩乘后总复杂度 $\mathcal O(mb^2 \log n)$。[code](https://atcoder.jp/contests/abc388/submissions/61577060)。

---

## 作者：Laisira (赞：9)

### 思路
赛时想到同余最短路没打出来，就交一发矩乘的题解。

对于每个 $[l,r]$，显然前后 $b-(r-l+1)$（相当于 $20$）个位置是可以暴力转移的，考虑两个区块中间的区域 $x$ 能跳到的是 $x+i\ (a \leq i \leq b)$。于是一个位置是否可以到达（$f_x = 0/1$）的转移方程是：

$$f_x = \bigvee_{j=a}^{\min(b,x-1)} f_{x-j}$$

可以用矩阵快速幂，时间复杂度是 $O(mV^3\log n)$ 的，于是预处理矩阵 $2^k$ 的状态，时间复杂度 $O(mV^2\log n)$，$V=b-a+1$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Mx 25 
using namespace std;
struct mat {
	int a[Mx][Mx];
	mat() {memset(a,0,sizeof a);}
	mat operator*(const mat&x)
	const {
		mat res;
		for(int i=0;i<=20;i++)
			for(int k=0;k<=20;k++) {
				unsigned long long cnt = a[i][k];
				for(int j=0;j<=20;j++) {
					res.a[i][j] |= (cnt&x.a[k][j]);
				}
			}
		return res;
	}
} fac[45],fac0[45];
struct line {
	int a[Mx];
	line() {memset(a,0,sizeof a);}
	line operator*(const mat&x)
	const {
		line res;
		for(int k=0;k<=20;k++) {
			unsigned long long cnt = a[k];
			for(int j=0;j<=20;j++) {
				res.a[j] |= (cnt&x.a[k][j]);
			}
		}
		return res; 
	}
} S;
void fsp(int x) {
	for(int i=0;i<45;i++)
		if(x&(1ll<<i))S = S*fac[i];
}
void fsp0(int x) {
	for(int i=0;i<45;i++)
		if(x&(1ll<<i))S = S*fac0[i];
}
signed main()
{
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	for(int i=1;i<=19;i++)
		fac[0].a[i+1][i] = fac0[0].a[i+1][i] = 1;
	for(int i=20-b+1;i<=20-a+1;i++)
		fac[0].a[i][20] = 1;
	S.a[20] = 1;
	for(int i=1;i<45;i++)
		fac[i] = fac[i-1]*fac[i-1],
		fac0[i] = fac0[i-1]*fac0[i-1];
	int lst = 1;
	for(int i=1;i<=m;i++) {
		int l,r; cin>>l>>r;
		if(r-l+1 >= 21||l == 1)
			return cout<<"No",0;
		if(l-lst-1 > 0)fsp(l-lst-1);
		if(r-l+1 > 0)fsp0(r-l+1);
		lst = r;
	}
	if(n-lst > 0)fsp(n-lst);
	if(S.a[20])cout<<"Yes";
	else cout<<"No";
	return 0;
 }
```

---

## 作者：tis00 (赞：6)

简单题。赛时没判 $a=b$，悲。

首先，如果 $(r+1)-(l-1)>b$，那么无解。

**引理：** 对于任意两个正整数 $a$ 和 $b$，如果 $(a,b)=1$，那么对于任意 $c\ge (a-1)(b-1)$，都存在两个非负数 $x$ 和 $y$，满足 $ax+by=c$。

于是乎，如果 $a<b$，那么设 $p=(a-1)a+2(b-1)$，则对于一长度大于 $p$ 的空白段，必然可以把长度缩成 $p$，而不影响结果。

小 trick：缩的时候可以用 $pos$ 表示偏移量，好写好调。

最后暴力 DP 即可。

如果 $a=b$，路线必为 $1\rightarrow a+1\rightarrow...\rightarrow n$，记得判 $a\mid (n-1)$。

$0.8B$，$19ms$ 的优质代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e4+5;
const int M=2e7+5;
typedef long long ll;
ll n;
int m,a,b,g;
ll l[N],r[N];
bool can[M],f[M];
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&a,&b),--n;
	for(int i=1;i<=m;i++) scanf("%lld%lld",&l[i],&r[i]),l[i]--,r[i]--;
	for(int i=1;i<=m;i++) if(r[i]-l[i]+2>b) return puts("No")&0;
	if(a==b){
		if(n%a) return puts("No")&0;
		for(int i=1;i<=m;i++) for(ll j=l[i];j<=r[i];j++) if(j%a==0) return puts("No")&0;
		return puts("Yes")&0;
	}
	ll pos=0;
	int p=(a-1)*a+2*b-2;
	for(int i=1;i<=m;i++){
		pos+=max(l[i]-r[i-1]-p,0ll);
		for(ll j=l[i];j<=r[i];j++) can[j-pos]=1;
	}
	pos+=max(n-r[m]-p,0ll);
	int up=n-pos;
	f[0]=1;
	for(int i=0;i<up;i++){
		if(f[i]){
			for(int j=a;j<=b;j++) if(i+j<=up&&!can[i+j]) f[i+j]=1;
		}
	}
	puts(f[up]?"Yes":"No");
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：6)

## 本题思路：
这道题我们知道他的不能到达区间是不相交的，那么我们其实可以把这个长度为 $n$ 的正方形按照合法的分成一些段。在每一段上我们可以用跳楼机一样的想法，同余最短路去求出在模 $l$ 的意义下当前模出来的值最小在哪里可以取到。这时我们就分别把在模 $l$ 意义下的值在当前区间中最大可达位置记录下来，明显只要 $l$ 个，然后暴力跳到后面去，用一个 vector 去记录可达位置。

这样做每一次把跳到位置为障碍的删掉之后一直做同余最短路，最后看在模 $l$ 意义下能否到 $n$ 即可。

时间复杂度的话是分成的段数乘上每一段跑最短路的时间（因为是在模 $l$ 意义下的最短路，所以最多只会产生 $l \times\log l$ 的贡献），再加上每次区间的跳跃会有的 $l\times(r-l+1)$，综合能过。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{int l,r;}a[200005];
int dis[205],l,r,vis[205],st[205],top;
vector<pair<int,int> >s[205];vector<int>vis1[205];
priority_queue<pair<int,int> >q;
void tiao(int S,int t,int tt){
	int pd=0;
	for(int i=0;i<l;i++){top=0;
		for(int j=0;j<vis1[i].size();j++){int y=vis1[i][j];if(y<S||(y>=t&&y<=tt)) continue;st[++top]=y;}
		sort(st+1,st+1+top);vis1[i].clear();
		for(int j=1;j<=top;j++) vis1[i].push_back(st[j]);
	}
	for(int i=0;i<l;i++){s[i].clear();
		if(vis1[i].size())dis[i]=vis1[i][0];else dis[i]=1e18;
		if(dis[i]<t){q.push(make_pair(-dis[i],i));}vis[i]=0;
		for(int j=l+1;j<=r;j++){s[i].push_back(make_pair((i+j)%l,j));}
	}
	while(q.size()){
		int p=q.top().second;q.pop();if(vis[p]) continue;vis[p]=1;
		for(int i=0;i<s[p].size();i++){
			int y=s[p][i].first,k=s[p][i].second;
			if(dis[y]>dis[p]+k){
				dis[y]=dis[p]+k;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
	for(int i=t-1;i>=S;i--){
		if(i!=t-1&&(i)%l==(t-1)%l) break;
		if(dis[(i)%l]<=i){
			for(int j=l;j<=r;j++){
				if(i+j>tt){vis1[(i+j)%l].push_back(i+j);}
			}
		}
	}
}
signed main(){
	int n,m;cin>>n>>m>>l>>r;
	for(int i=1;i<=m;i++){cin>>a[i].l>>a[i].r;}
//	for(int i=0;i<=l;i++) vis1[i]=1e18;
	vis1[1%l].push_back(1);
	if(m){
		tiao(1,a[1].l,a[1].r);
		for(int i=1;i<m;i++){tiao(a[i].r+1,a[i+1].l,a[i+1].r);}
		for(int i=0;i<l;i++){top=0;
			for(int j=0;j<vis1[i].size();j++){int y=vis1[i][j];if(y<=a[m].r) continue;st[++top]=y;}
			sort(st+1,st+1+top);vis1[i].clear();
			for(int j=1;j<=top;j++) vis1[i].push_back(st[j]);
		}
	}
	for(int i=0;i<l;i++){s[i].clear();
		if(vis1[i].size())dis[i]=vis1[i][0];else dis[i]=1e18;
		if(dis[i]!=1e18){q.push(make_pair(-dis[i],i));}vis[i]=0;
		for(int j=l+1;j<=r;j++){s[i].push_back(make_pair((i+j)%l,j));}
	}
	while(q.size()){
		int p=q.top().second;q.pop();if(vis[p]) continue;vis[p]=1;
		for(int i=0;i<s[p].size();i++){
			int y=s[p][i].first,k=s[p][i].second;
			if(dis[y]>dis[p]+k){
				dis[y]=dis[p]+k;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
	if(dis[n%l]<=n) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：chenxi2009 (赞：4)

**Upd 2025.1.15：修改了一些错误。删去了过于简单的证明。优化复杂度。**
## 思路
暴力复杂度 $O(NB)$。考虑去掉明显不需要计算的位置。\
除去 $A=B$ 的情况外，发现起点后若干号位置后面都是可达的。易证这个位置大约为 $B^2$。\
换句话说如果一个点可达，只要下一个区间离它足够远，那么下一个区间前面一串位置都是可达的。以这个足够远的长度（大约 $460$）把区间分隔成若干个大块，每大块内部暴力求解即可。求出一个格子是否可达复杂度为 $O(B)$，总时间复杂度为 $O(MB^3)$。

细节：
- $A=B$：判断每一个区间内格子与起点的距离是否有 $A$ 的倍数以及 $N$ 与起点的距离是否为 $A$ 的倍数即可。
- 存在大小大于等于 $B$ 的区间时直接输出无解。
- 除去第一个大块之外，每一个大块前面要预留出 $B$ 个可达的位置作为起点。终点同理。
- 注意判断终点是否可达，所以也要把它划进一个大块里。

在暴力求解的时候我们判断一个点前面一个区间内是否有点可达以得出这个点能否到达，那么这可以用一个树状数组去维护。时间复杂度降为 $O(MB^2\log M)$（不过真的有必要么）。
## 代码
口胡的还没写，晚点可能补上。

---

## 作者：Dream_poetry (赞：3)

### 思路：
首先，如果你做过[这道题](https://www.luogu.com.cn/problem/P1052)，那么此题难度就会锐减，所以建议大家先去把这道题看一看。

同样的，我们分别考虑 $a=b$ 和 $a\ne b$ 两种情况。

先说 $a=b$ 时的情况，直接模拟一下就行了，非常好写，不过要注意 $m=0$ 这种毒瘤数据。

我们考虑怎么处理 $a\ne b$ 的情况。

首先我们找出所有可以走的区间，不难发现我们只需要考虑它的前半段和后半段部分能否走过即可，所找出的范围就是新区间的 $l$ 到 $l+b$，$r-b$ 到 $r$。若它的前半部分 $l$ 到 $l+b$ 可以被走到，那么我们直接对后半部分 $r-b$ 到 $r$ 进行类似于**过河**那道题的 $dp$ 处理就可以了。

由于 $A、B$ 在 $20$ 以内，所以我们仿照过河得出的压缩距离可算出是 $342$。

知道压缩距离后真的就仿照过河那道题来做就可以了，预处理出一个点在 $1$ 到 $342$ 步之间可以走到哪些位置就可以了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a,b;
int l[5000005];
int r[5000005];

int ll[5000005];
int rr[5000005];
int tot;
map<int,int>mp;

int f[5000005];

signed main(){
	cin>>n>>m>>a>>b;
	for (int i=1;i<=m;i++){
		cin>>l[i]>>r[i];
	}	
	if (a==b){
		if (n%b!=1%b){
			cout<<"No";
			return 0;
		}
		for (int i=1;i<=m;i++){
			if ((r[i]-l[i]+1)>=b){
				cout<<"No";
				return 0;
			}
			for (int j=l[i];j<=r[i];j++){
				if (j%b==1){
					cout<<"No";
					return 0;
				}
			}
		}
		cout<<"Yes";
		return 0;
	}
	for (int i=1;i<=m;i++){
		ll[++tot]=r[i-1]+1;
		rr[tot]=l[i]-1;
	}
	f[0]=1;
	ll[++tot]=r[m]+1;
	rr[tot]=n;
	for (int i=1;i<=342;i++){
		for (int j=a;j<=b;j++){
			if (i-j<0){
				break;
			}
			f[i]|=f[i-j];
		}
	}
	mp[1]=1;
	for (int i=1;i<=tot;i++){
		for (int pos=ll[i];pos<=min(rr[i],ll[i]+b);pos++){
			for (int j=a;j<=b;j++){
				if (mp[pos-j]){
					mp[pos]=1;
				}
			}
			if (mp[pos]){
				for (int j=max(pos,rr[i]-b);j<=rr[i];j++){
					if (j-pos>=342 || f[j-pos]){
						mp[j]=1;
					}
				}
			}
		}
	}
	if (mp[n]){
		cout<<"Yes";
	}
	else{
		cout<<"No";
	}
	return 0;
}
```

---

## 作者：GoldSpade (赞：3)

### statement

- 在一个数轴上，从点 $1$ 出发，有 $m$ 个区间 $[L_{k},R_k]$ 不能经过。每次可以选择一个 $i\in[a,b] \cap \Z$，使当前位置 $x \gets x+i$。求能不能在若干次操作后到达 $n$。

- $1\le a,b\le 20,1\le n\le2\times10^{14}, 1 \le m \le 2 \times 10^4$。

### solution

用一个 $f_i$ 表示是否能从 $1$ 走到 $i$。转移是显然的：能走到 $i$ 就能走到 $i+x(a\le x\le b)$，走进区间的强制让 $f_i=0$。因为一次走不超过 $20$ 步，$0/1$ 矩阵优化即可。

矩阵的构造方式（将 $\vec{a}_{i}=[f_{i-19},f_{i-18},\dots,f_i]$ 转移至 $\vec{a}_{i+1}$）如下：

- $\forall 0\le i < 19$，$F_{i+1,i}=1$，表示 $f_{i+1}=f_{i+1}$。

- $\forall a\le x \le b$，$F_{19-x+1,19}=1$，表示行走一次。

初始向量最后一位设为 $f_1=1$。向量的最后一位每次使用快速幂转移到 $f_{R_k}$ 并强制让 $f_{L_k},f_{L_k+1},\dots,f_{R_k} = 0$。

具体实现很简单，用 $\text{bitset}$ 优化矩阵即可。总时间复杂度 $\mathcal{O}\left(\dfrac{b^3 m\log_2 n }{\omega}\right)$。实测效率不错。

### code

```cpp
#include <bits/stdc++.h>
#define PII pair<int,int>
#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
using namespace std;
const int N = 20005;
int n, a, b, m;
struct interval { int l, r; } itv[N];
struct matrix {
	bitset<20> bs[20];
	inline friend matrix operator * (const matrix& a, const matrix& b) {
		matrix res;
		rep(k, 0, 19) rep(i, 0, 19) if (a.bs[i][k]) res.bs[i] |= b.bs[k];
		return res;
	}
};
matrix res, mt;
inline void qpow(int b) {
	for (matrix tmp = mt; b; b >>= 1, tmp = tmp*tmp)
		if (b & 1) res = res*tmp;
}
signed main() {
	FASTIO;
	cin >> n >> m >> a >> b;
	rep(i, 1, m) cin >> itv[i].l >> itv[i].r;
	res.bs[0][19] = 1;
	rep(i, 0, 18) mt.bs[i+1][i] = 1; 
	rep(i, a, b) mt.bs[19-i+1][19] = 1;
	itv[0].r = 1;
	rep(i, 1, m) {
		qpow(itv[i].r-itv[i-1].r);
		rep(j, max(itv[i].l, itv[i].r-19), itv[i].r)
			res.bs[0][j-itv[i].r+19] = 0;
	}
	qpow(n-itv[m].r);
	cout << (res.bs[0][19]?"Yes":"No");
	return 0;
}
```

---

## 作者：ZHR100102 (赞：3)

赛时写了矩乘 T 飞了，受到 sunkuangzheng 大佬的启发才知道要状压矩乘。

# 暴力矩乘思路

直接像过河那样写模拟细节非常多，于是考虑像美食家一样的思路，利用矩阵分段加速。

定义 $dp_i$ 表示 $i$ 能否到达，则有如下转移：

$$dp_{i}=\bigvee_{j=i-B}^{i-A}dp_{j}$$

因为 $A,B\le 20$，所以可用状态非常少，就可以用矩阵优化了。

那么很显然就把段拆一下，然后直接跑矩乘就好了。这个做法甚至连 $m=0,l_i-1=r_{i-1}$ 的细节都不用判。

代码如下，如果你真这么写了，会收获 TLE 和 WA 的好成绩！

下面这份暴力中 $dp_i$ 表示 $dp_i$ 的方案数，所以转移有所不同，本质还是和上面一样的。只要 $dp_i>0$ 就能到达。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
struct mat{
	ull a[25][25];
	mat(){memset(a,0,sizeof(a));}
	mat operator*(const mat &x)const{
		mat res;
		for(int i=0;i<=20;i++)
		{
			for(int k=0;k<=20;k++)
			{
				ull l=a[i][k];
				for(int j=0;j<=20;j++)
				{
					res.a[i][j]=(res.a[i][j]+l*x.a[k][j]);
				}
			}
		}
		return res;
	}
}s,dp1,dp2;
mat qpow(mat x,ll k)
{
	mat res;
	for(int i=0;i<=20;i++)res.a[i][i]=1;
	while(k>0)
	{
		if(k&1)res=res*x;
		x=x*x;
		k>>=1;
	}
	return res;
}
ll n,m,a,b,l[200005],r[200005];
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>a>>b;
    s.a[1][20]=1;
    for(int i=1;i<=19;i++)dp1.a[i+1][i]=dp2.a[i+1][i]=1;
    for(int i=20-a+1;i>=20-b+1;i--)dp1.a[i][20]=1;
    r[0]=1;
    for(int i=1;i<=m;i++)
    {
        cin>>l[i]>>r[i];
        if(r[i]-l[i]+1>=21||l[i]==1)
        {
            cout<<"No";
            return 0;
        }
        if(l[i]-r[i-1]-1>0)s=s*qpow(dp1,l[i]-r[i-1]-1);
        if(r[i]-l[i]+1>0)s=s*qpow(dp2,r[i]-l[i]+1);
    }
    if(n+1-r[m]-1>0)s=s*qpow(dp1,n+1-r[m]-1);
    if(s.a[1][20])cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

原因是复杂度为 $O(m\times 20^3 \log n)$，常数又大，无法通过。

# 优化矩乘

因为状态中只有 $0$ 和 $1$，每行每列的数又只有 $20$ 个，考虑用状压与位运算去掉一个 $20$。

我们先看暴力的矩乘代码，再来考虑如何优化它。

```cpp
struct mat{
	ull a[25][25];
	mat(){memset(a,0,sizeof(a));}
	mat operator*(const mat &x)const{
		mat res;
		for(int i=0;i<=20;i++)
		{
			for(int k=0;k<=20;k++)
			{
				for(int j=0;j<=20;j++)
				{
					res.a[i][j]=(res.a[i][j]|(a[i][k]&x.a[k][j]));
				}
			}
		}
		return res;
	}
}
```

可以发现，当 $a_{i,k}=1$ 时，$res_{i,j}$ 取决于 $x_{i,j}$ 是否为 $1$。

因此，就可以省去循环 $j$，当 $a_{i,k}=1$ 时，直接让 $res_i \gets res_i \vee x_k$ 即可。

时间复杂度 $O(m\times 20^2 \log n)$，可以通过。

代码如下：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
struct mat{
	ull a[25];
	mat(){memset(a,0,sizeof(a));}
	mat operator*(const mat &x)const{
		mat res;
		for(int i=0;i<=20;i++)
		{
			for(int k=0;k<=20;k++)
			{
				if((a[i]>>k)&1)res.a[i]=(res.a[i]|x.a[k]);
			}
		}
		return res;
	}
}s,dp1,dp2;
mat qpow(mat x,ll k)
{
	mat res;
	for(int i=0;i<=20;i++)res.a[i]=(1<<i);
	while(k>0)
	{
		if(k&1)res=res*x;
		x=x*x;
		k>>=1;
	}
	return res;
}
ll n,m,a,b,l[200005],r[200005];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>a>>b;
    s.a[1]=(1<<20);
    for(int i=1;i<=19;i++)dp1.a[i+1]=dp2.a[i+1]=(1<<i);
    for(int i=20-a+1;i>=20-b+1;i--)dp1.a[i]|=(1<<20);
    r[0]=1;
    for(int i=1;i<=m;i++)
    {
        cin>>l[i]>>r[i];
        if(r[i]-l[i]+1>=21||l[i]==1)
        {
            cout<<"No";
            return 0;
        }
        if(l[i]-r[i-1]-1>0)s=s*qpow(dp1,l[i]-r[i-1]-1);
        if(r[i]-l[i]+1>0)s=s*qpow(dp2,r[i]-l[i]+1);
    }
    if(n+1-r[m]-1>0)s=s*qpow(dp1,n+1-r[m]-1);
    if((s.a[1]>>20)&1)cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：MaxFwl (赞：2)

考虑到 $m \le 2 \times 10^4$，$n \le 10^{12}$，发现很多坏段之间会空很长一段，这是解决问题的关键。

考虑分治，对于中空段 $>B$ 的情况，令 $f_{i, j}$ 为是否可以走到 $r_i - j$ 并通过一步跳过坏段 $i$，令 $g_{i, j}$ 为是否可以从一个坏段 $i$ 之前的点一步跳到 $r_i + j$，直接根据题意模拟每一步可以跳到位置的上下界，然后转移即可。

对于中空段长度 $\le B $ 的连续多个坏段，令这些坏段的第一个为 $x$，最后一个为 $y$，对 $r_x - B + 1$ 到 $r_y + B - 1$ 这些位置直接 dp，在知道 $f_x$ 的情况下也可以处理出 $g_y$。

预处理和计算答案是简单的，可以看看代码，复杂度精细实现是 $O(m \times B^2)$ 的，笔者偷懒用了个 map，不过也跑得蛮快。

[code。](https://atcoder.jp/contests/abc388/submissions/61625421)

场上没调出来，E 以为是图最大匹配写了个又长又烂的做法，然后 F 没时间做了。

---

## 作者：xzf_200906 (赞：2)

本人赛时因为少了一个特判没能通过此题，发篇题解以示纪念。

先考虑 $a=b$ 的情况，首先有 $n\equiv 1\pmod b$。其次要不存在一个 $j\in [l_i,r_i]$ 满足 $j\equiv 1\pmod b$。若存在一个区间长度大于 $20$ 则直接无解，否则枚举区间中的每一个位置即可。

若 $a<b$，则将合法的位置分成若干连续段。显然我们不可能记录每一段中的每个位置是否可达。但是我们发现我们只关心每一段的最后 $b$ 个位置是否可达。并且若段的长度大于 $500$ 并且这段中存在一个位置可以被到达（显然是前 $b$ 个位置），那么后 $b$ 个位置均一定可达。于是若段的长度大于 $500$ 就只需要记录是否存在一个可达的位置就可以了，则状态数量正确。转移时从左到右枚举每一个段，若段的长度不大于 $500$ 则用前缀和即可做到线性的进行段内转移，再枚举段中最后的 $b$ 个位置以及它会往后跳多少格即可实现段间转移。

Code:
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
vector<bool> canVis[1000000];
const int Bl=500;
struct Zone{
	LL l,r;
	LL len(){
		return r-l+1;
	}
	bool over(){
		return r-l+1>=Bl;
	}
};
vector<Zone> zone;
int sum[1000000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	LL n;
	int m,a,b;
	cin>>n>>m>>a>>b;
	if(a==b){
		if(n%b!=1%b){//xzf 死于此行之下。
			cout<<"No\n";
			return 0;
		}
		for(int i=1;i<=m;i++){
			LL l,r;
			cin>>l>>r;
			if(r-l+1>=Bl){
				cout<<"No\n";
				return 0;
			}
			for(LL i=l;i<=r;i++){
				if(i%b==1){
					cout<<"No\n";
					return 0;
				}
			}
		}
		cout<<"Yes\n";
		return 0;
	}
	LL las=0;
	for(int i=1;i<=m;i++){
		LL l,r;
		cin>>l>>r;
		zone.push_back({las+1,l-1});
		las=r;
	}
	zone.push_back({las+1,n});
	for(int i=0;i<zone.size();i++){
		if(zone[i].over()) canVis[i].resize(1,0);
		else canVis[i].resize(zone[i].len(),0);
	}
	canVis[0][0]=1;
	for(int i=0;i<zone.size();i++){
		if(!zone[i].over()){
			for(int j=0;j<zone[i].len();j++){
				int l=max(0,j-b),r=j-a;
				if(r>=0&&sum[r]-(l?sum[l-1]:0)>0) canVis[i][j]=1;
				sum[j]=canVis[i][j];
				if(j) sum[j]+=sum[j-1];
			}
		}
		LL las=zone[i].r;
		int rp=i+1;
		for(LL pos=max(zone[i].l,zone[i].r-b+1);pos<=zone[i].r;pos++){
			if(zone[i].over()&&!canVis[i][0]) continue;
			if(!zone[i].over()&&!canVis[i][pos-zone[i].l]) continue;
			for(int j=a;j<=b;j++){
				if(pos+j<=las||pos+j>n) continue;
				las=pos+j;
				while(zone[rp].r<pos+j) rp++;
				if(zone[rp].l<=pos+j){
					if(zone[rp].over()) canVis[rp][0]=1;
					else canVis[rp][pos+j-zone[rp].l]=1;
				}
			}
		}
	}
	bool ans;
	if(zone.back().over()) ans=canVis[zone.size()-1][0];
	else ans=canVis[zone.size()-1][n-zone.back().l];
	cout<<(ans?"Yes\n":"No\n");
	return 0;
}
```

---

## 作者：luanyanjia (赞：1)

太幽默了。

显然可以用矩阵快速幂解决，矩阵里维护距离当前点 $B$ 以内的所有点可不可达，转移只需分段，在区间内和不在区间内用不同的转移矩阵即可。复杂度 $O(B^3m\log n)$。

然后你就 T 了。

此时你很急，你现在应该快点卡常来 AK 这场比赛而不是研究其他的做法，于是我们发现快速幂根本不需要，因为有障碍的区间长度 $\le B$，然后没障碍的区间对应的矩阵乘到 $400$ 次方左右就全大于 $0$ 了。可以直接预处理出矩阵的幂。

然后 $A = B$ 时肯定是没有上面那条性质的，需要特判。能走到 $n$ 的条件显然是 $n \bmod B \equiv 1$ 且没有障碍 $\bmod B \equiv 1$。

然后你就 WA 了。

![](https://cdn.luogu.com.cn/upload/image_hosting/y3jtcquf.png)

比赛结束我也没调出来，然后我发现一个重要的事情：

$B$ 可以等于 $1$。

就这样寄了。

代码有点乱。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define pii std::pair<ll,ll>
#define mkp std::make_pair
#define fir first
#define sec second
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	int ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=25;
ll n;int m,A,B;
std::vector<pii> vec;
struct Matrix{
	int m[N][N],n;
	int* operator[](int x){return m[x];}
	Matrix(int _x=0,int _n=B){
		memset(m,0,sizeof m);n=_n;
		for(int i=1;i<=n;i++)m[i][i]=_x;
	}
	Matrix operator*(Matrix b){
		Matrix c=Matrix();
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					(c[i][j]+=m[i][k]*b[k][j]);
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)c[i][j]=(c[i][j]>0);
		}
		return c;
	}
}bas1,bas2,cur,b2[25],b1[405],a1;
signed main(){
	rd(n,m,A,B);
	if(A==B){
		if(B==1)return printf(m?"No":"Yes"),0;
		int flag=(n%B==1ll);
		for(int i=1;i<=m;i++){
			ll l,r;rd(l,r);
			if(r-l+1>=B)flag=0;
			else{
				for(ll j=l;j<=r;j++)if(j%B==1ll)flag=0;
			}
		}
		puts(flag?"Yes":"No");
		return 0;
	}
	ll now=2;
	for(int i=1;i<=m;i++){
		ll l,r;rd(l,r);
		vec.push_back({now,l-1});
		vec.push_back({l,r});
		if(r-l+1>=B){
			puts("No");
			return 0;
		}
		now=r+1;
	}
	vec.push_back({now,n});
	bas1.n=bas2.n=cur.n=B;
	for(int i=2;i<=B;i++)bas2[i][i-1]=bas1[i][i-1]=1;
	for(int i=1;i<=B-A+1;i++)bas1[i][B]=1;
	cur[1][B]=1;
	b2[1]=bas2;b1[1]=bas1;
	for(int i=2;i<=B;i++)b2[i]=b2[i-1]*bas2;
	for(int i=2;i<=400;i++)b1[i]=b1[i-1]*bas1;
	for(int i=1;i<=B;i++){
		for(int j=1;j<=B;j++)a1[i][j]=1;
	}
	int t=0;
	for(auto [l,r]:vec){
		t^=1;
		if(l>r)continue;
		if(t)cur=cur*(r-l+1<=400?b1[r-l+1]:a1);
		else cur=cur*b2[r-l+1];
	}
	printf(cur[1][B]?"Yes":"No");
	return 0;
}

```

---

## 作者：liangbob (赞：1)

## AT_abc388_f 题解

本题解主要侧重于证明（当然有些并不是很严谨），如果您想知道做法可以参考其它题解。

先将不合法段转成合法段。

设从前到后第 $i$ 个合法段为 $[l_i,r_i]$。根据题意以及合法段的定义，可以证明合法段互不相交。

考虑每一个合法段。我们先从下列命题入手。

> **命题 I** 从第 $1$ 到 $x-1$ 个合法段跳到第 $x$ 个合法段，第一次跳到的位置必然在第 $x$ 个合法段的前 $b$ 个位置上。

令 $X=R_{x-1}$，$Y=L_x$，$Z=R_x$。

该命题等价于：设有 $1\le u \le X$，若 $k$ 是满足 $Y \le u+bk \le Z$ 最小的 $k$，则 $Y \le u+bk \le Y+b-1$。

反证法，假设 $Z \ge u+bk \ge Y+b$。

则显然 $Z - b \ge u + b(k-1) \ge Y$, 即 $Z \ge u + b(k-1) \ge Y$。

于是，对于所有的 $u+bk$，都可以找到一个比他小的 $k$ 满足 $Y \le u+bk \le Z$，这与 $k$ 的定义矛盾，于是原命题成立。

> **命题 II** 对于长度大于 $ab+b$ 的合法段，若它的前 $b$ 位中有一位可以被跳到，则它的后 $b$ 位均可以被跳到。

该命题等价于：设有 $1 \le u \le b$ 以及 $m > ab+b$，则对于所有 $m-b+1 \le s \le m$，$u + ax_1 + (a+1)x_2+(a+2)x_3+\ldots+bx_{b-a+1} = s$ 均成立。

命题等价于 $ax_1 + (a+1)x_2+(a+2)x_3+\ldots+bx_{b-a+1} = s - u$ 均成立。

考虑这些数最大的不能表示的数 $M$ 是什么。这里给出一个感性的上限：$ab$。原因可以参考[这篇文章](https://blog.csdn.net/ACdreamers/article/details/18504181)，其中给出了三个数的上限，代入我们的数据可以知道 $M \le ab-a-b-c \le ab$。实际上我们发现，随着数的个数的增加，$M$ 会越来越小，因此 $ab$ 这个上线足够我们得到正确的解。

所以 $s-u > ab$，也就是说 $s > ab + u > ab+b$。所以 $m \ge s > ab+b$。

在实际实现代码的过程中，我们不一定要取 $ab+b$ 这样的上限，而是可以直接开到一个较大的合适的值，使之恒大于 $ab+b$，比如说 $20\times 20+20+30=450$。

不妨设这个上限是 $G$。

> **命题 III** 对于跳到下一个合法段，只需要知道的每一段的后 $b$ 位是否能跳到。

这个命题是显然的。假设一块的右端点是 $x$，则 $x-b$ 最多只能跳到 $x$，无法跳到下一个。所以只能是 $x - b + 1$ 到 $x$ 这段跳。

> **命题 IV** 若从某一段的后 $b$ 位逐位跳 $a$ 到 $b$ 格，那么只需要递增地跳。

“递增地跳”的意思是，如果某一跳跳到的位置比前面一跳跳到的位置要前，那么这一跳就不跳了。

命题依旧平凡，显然不会出现因为递增地跳就漏跳的的情况，因为你是逐次跳的。

-----------

再次考虑命题 II 的成立条件，发现当 $a = b$ 时该命题不成立。于是特判即可。

综合上述命题，我们考虑动态规划。设第 $i$ 段的第 $j$ 个位置是否能跳到为 $f_{i,j}$。

则：

- $f_{i,j}=\lor_{u=a}^b f_{i,j-u}$
- $f_{i,j+k}=f_{i,j+k}\lor f_{i,j}$（$a\le k \le b$）

根据命题 II，可以知道如果第 $i$ 段的长度大于 $G$，那么只需记录是否有位置跳到过这里即可，即数组 $f_i$ 只需开一个空间。否则，开对应区间长度个空间即可。

根据命题 III 和命题 IV，可以知道我们只需要遍历每一段的后 $b$ 位，并逐位跳 $a$ 到 $b$ 格，递增地跳然后更新即可。

---

## 作者：kkxacj (赞：1)

#### 前言

本然在赛后发现判无解写错了，改完就过了，导致掉分。

#### 思路

考虑在没有 $m$ 条限制的时候，直接同余最短路跑就行了，可以参考[这道题](https://www.luogu.com.cn/problem/P3403)。

然后考虑有限制的时候怎么办。

观察到 $1 \le A \le B \le 20$，$m$ 对限制互不相交，对于一对限制 $l,r$，考虑枚举前 $20$ 个，看每一个是否合法，然后将 $l$ 到 $r$ 都赋为无解，最后对于前面 $20$ 个里面所有合法的暴力枚举下一步走几步，转移到后面来，看后看 $20$ 个哪些能到达，记录一下可到达的位置，然后存下来为之后判合法做准备。

在遇到 $r-l+1 > 20$ 的时候，显然是无解的，判掉后每次是 $V^2\log$ 的，其中 $V = 20$，$\log$ 是因为开 `map` 存下标，在所有限制跑完后要判断之后能否到 $n$，最终复杂度为 $mV^2\log$。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 3e5+10;
int n,m,head[N],dis[N],v[N],cnt,A,B,k,ans,o1,l,r,st[N],cnt1,cnt2;
priority_queue<pair<int,int> >p;
map<int,int>mp;
struct w
{
	int to,nxt,z;
}b[N<<1];
inline void add(int x,int y,int z)
{ 
	b[++cnt].nxt = head[x];
	b[cnt].to = y,b[cnt].z = z;
	head[x] = cnt;
} 
void bfs()
{
	while(!p.empty())
	{
		k = p.top().second;p.pop(); v[k] = 0;
		for(int i = head[k];i;i = b[i].nxt)
		{
			if(dis[b[i].to] > dis[k]+b[i].z)
			{
				dis[b[i].to] = dis[k]+b[i].z;
				if(!v[b[i].to]) v[b[i].to] = 1,p.push(make_pair(-dis[b[i].to],b[i].to));
			}
		}
	}
}
signed main()
{
	read(n),read(m),read(A),read(B);
	for(int i = 0;i < A;i++) 
	{
		for(int j = A+1;j <= B;j++)
			add(i,(i+j)%A,j);
		dis[i] = 1e16;
	}
	dis[0] = 0,v[0] = 1,p.push(make_pair(0,0));
	bfs();//同余最短路 
	st[++cnt1] = 1;
	while(m--)
	{
		read(l),read(r);
		if(r-l+1 >= 20)
		{
			printf("No");
			return 0;
		}
		for(int i = l;i >= max(1ll,l-30);i--)
			for(int j = 1;j <= cnt1;j++)
				if(mp[i] == 0 && dis[(i-st[1])%A] <= i-st[j]) mp[i] = 2;
		for(int i = l;i <= r;i++) mp[i] = 1;
		for(int i = max(1ll,l-30);i <= l;i++)
			if(mp[i] == 2)
				for(int j = A;j <= B;j++)
					if(!mp[i+j]) 
						mp[i+j] = 2;
		cnt1 = 0;
		for(int i = r;i <= min(n,r+30);i++)
			if(mp[i] == 2) 
				st[++cnt1] = i;
	}
	cnt2 = 0;
	for(int i = 1;i <= cnt1;i++)
		if(dis[(n-st[i])%A] <= (n-st[i])) cnt2++;
	if(!cnt2)
	{
		printf("No");
		return 0;
	}
	printf("Yes");
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
考虑将每一个 $L_i$ 到 $R_i$ 的块，按 $R_{i-1}+1$ 到 $L_i-1$ 的块重新编号，边界为 $1$ 到 $L_1-1$ 和 $R_M+1$ 到 $n$。

对于每一个 $L_i$ 到 $L_i+B$ 和 $R_i-B$ 到 $R_i$。对于每一个 $L_i$ 到 $L_i+B$，从它减去 $A$ 到 $B$ 的每个值判断是否可行，如果可行则一定可以。如果可以，则从 $R_i-B$ 到 $R_i$ 的每一个值用 [过河](https://www.luogu.com.cn/problem/P1052) 的处理方案，小于等于 $B\times(B-1)-B-(B-1)$ 的值 DP 处理，否则一定可行。

注意要判断 $A=B$ 的情况。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005,B=19*20-19-20+1;
ll f[B+10],l[N],r[N],x[N],y[N];
unordered_map<ll,bool>mp;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n,m,a,b,k=0;
    cin>>n>>m>>a>>b;
    for(int i=1;i<=m;i++)
    {
        cin>>l[i]>>r[i];
        x[++k]=r[i-1]+1;
        y[k]=l[i]-1;
    }
    x[++k]=r[m]+1;
    y[k]=n;
    f[0]=1;
    for(int i=1;i<=B;i++)
    {
        for(int j=a;j<=b;j++)
        {
            if(i-j<0)break;
            f[i]|=f[i-j];
        }
    }
    if(a==b)//特判A=B
    {
        bool flag=1;
        for(int i=1;i<=m;i++)
            if(a==1||l[i]%a==1||(l[i]/a+1)*a+1<=r[i])
                flag=0;
        if(n%a!=1&&a!=1)flag=0;
        if(flag)cout<<"Yes\n";
        else cout<<"No\n";
        return 0;
    }
    mp[1]=1;
    for(int i=1;i<=k;i++)
    {
        for(ll j=x[i];j<=min(x[i]+b,y[i]);j++)
        {
            for(int p=a;p<=b;p++)
                if(mp[j-p])mp[j]=1;
            if(mp[j])
            {
                for(ll p=max(y[i]-b,j);p<=y[i];p++)
                    if(p-j>=B||f[p-j])mp[p]=1;
            }
        }
    }
    if(mp[n])cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
```

---

## 作者：Gordon_Song (赞：0)

有一个 $O(nB)$ 的做法，设 $dp_i$ 表示 $i$ 是否可以到达。

然而，注意到只需要关注每一段区间前的 $B$ 个和后 $B$ 个位置的 $dp$ 状态，其他的都可以用同余最短路找到规律（当然，由于 $B$ 很小，也可以直接暴力）。所以复杂度降为 $O(m B^2)$。

code:
```cpp
const int MAXN=2e4+5;
bool can[MAXN];
ll n,m,a,b,lcm,gcd;
int l[MAXN],r[MAXN];
vector<int>pos;
bool cou(int l,int r){
	if(r<=0||l<=0)return false;
	if(l>r)return false;
	if(r>n)return false;
	int len=r-l;
	if(len%gcd!=0){
		return false;
	}
	if(len>lcm)return true;
	return can[len];
}
bool check(int x){
	for(int i=0;i<pos.size();i++){
		if(cou(pos[i],x)){
			return true;
		}
	}return false;
}
bool check_(int x){
	for(int i=0;i<pos.size();i++){
		if(x-pos[i]>=a&&x-pos[i]<=b){
			return true;
		}
		if(pos[i]==x){
			return true;
		}
	}return false;
}
map<int,bool>mp;
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&a,&b);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&l[i],&r[i]);
		if(l[i]+b<=r[i]){
			printf("No\n");
			return 0;
		}
		for(int j=l[i];j<=r[i];j++){
			mp[j]=true;
		}
	}	
	lcm=a*b/__gcd(a,b);
	gcd=__gcd(a,b);
	can[0]=true;
	for(int i=1;i<=lcm;i++){
		if(i>=a)can[i]|=can[i-a];
		if(i>=b)can[i]|=can[i-b];
	}pos.push_back(1);
	l[m+1]=n+1;
	for(int i=1;i<=m;i++){
		vector<int>t;
		for(int j=0;j<=b;j++){
			if(!mp[l[i]-j]&&check(l[i]-j)){
				t.push_back(l[i]-j);
			}
		}
		for(int j=0;j<pos.size();j++){
			if(pos[j]>r[i]){
				t.push_back(pos[j]);
			}
		}
		pos.clear();
		for(int j=0;j<t.size();j++)pos.push_back(t[j]);
		t.clear();
		for(int j=0;j<=b;j++){
			if(!mp[r[i]+j]&&check_(r[i]+j)){
				pos.push_back(r[i]+j);
				t.push_back(r[i]+j);
			}
		}
		pos.swap(t);
	}
	if(check(n)){
		printf("Yes");
	}else{
		printf("No");
	}
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

**明确位运算记号.** $\land, \lor, \lnot$ 分别表示按位与，按位或，按位非。$\ll, \gg$ 去除其远大于、远小于的本意，转义为按位左移、按位右移。$[\cdot]$ 表示 Iverson 括号。

状压，设 $f(i)$ 为一个 $[0, 2^B)$ 间的整数，使得其第 $k$ 位为 $1$，当且仅当 $i - k$ 可达。这样，对于安全的格子，其转移为：
$$
f(i + 1) = T(f(i)), T(x) = ((x \ll 1) \lor [x \land N \ne 0]) \land M,
$$
其中 $M = 2^B - 1, N = 2^B - 2^{A-1}$。

这样，可以通过倍增维护 $T^{2^k}(x)$，完成对于没有危险格子的处理。对于危险格子，无非把其中的 $1$ 换成 $R - L$。对于一次危险-安全的交替，有如下代码：

```cpp
int update(i64 L, i64 R, i64 lstR, int st, int A, int B, BinaryLift& lift) {
    int M = (1 << B) - 1, N = (1 << B) - (1 << A);
    int q = (lift.query(st, L - lstR - 1) << (R - L)) & M;
    return ((q << 1) | ((q & N) != 0)) & M;
}
```

因此，我们可以得到如下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

#include "atcoder/all"
using namespace atcoder;

struct BinaryLift {
    vector<vector<int>> lift;
    BinaryLift(const vector<int>& v, i64 L) {
        int n = v.size();
        int m = L ? __lg(L - 1) + 1 : 1;
        lift.resize(m, vector<int>(n));
        for (int i = 0; i < n; i++) lift[0][i] = v[i];
        for (int i = 1; i < m; i++)
            for (int j = 0; j < n; j++)
                lift[i][j] = lift[i - 1][lift[i - 1][j]];
    }
    int query(int x, i64 k) {
        if (k == 0) return x;
        i64 i = __lg(k);
        return query(lift[i][x], k - (1ll << i));
    }
};

int update(i64 L, i64 R, i64 lstR, int st, int A, int B, BinaryLift& lift) {
    int M = (1 << B) - 1, N = (1 << B) - (1 << A);
    int q = (lift.query(st, L - lstR - 1) << (R - L)) & M;
    return ((q << 1) | ((q & N) != 0)) & M;
}

tuple<i64, int, int, int, vector<pair<i64, i64>>> input() {
    i64 n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<pair<i64, i64>> intervals;
    for (i64 i = 0, l, r; i < m; i++) {
        cin >> l >> r, l--;
        if (!intervals.empty() && intervals.back().second == l)
            intervals.back().second = r;
        else
            intervals.emplace_back(l, r);
    }
    return {n, intervals.size(), a - 1, b, intervals};
}

int main() {
    auto [n, m, a, b, intervals] = input();
    int M = (1 << b) - 1, N = (1 << b) - (1 << a);
    vector<int> nxt(1 << b);
    for (int i = 0; i < (1 << b); i++) nxt[i] = ((i << 1) | ((i & N) != 0)) & M;
    BinaryLift lift(nxt, n);
    i64 lstR = 0, st = 1;
    for (auto [l, r] : intervals)
        st = update(l, r, lstR, st, a, b, lift), lstR = r;
    st = lift.query(st, n - lstR - 1);
    if (st & 1)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
```

---

## 作者：Le0Chan (赞：0)

设 $dp_i$ 表示能否到达 $i$，有转移 $dp_i=\operatorname{OR}\limits_{⁡j=a}^b dp_{i−j}$ 且 $i$ 不是坏的。

直接矩阵快速幂优化即可，总复杂度 $O(mb^3\log⁡n)$。

套路地注意到初始矩阵是行向量，行向量乘什么玩意都是行向量，所以快速幂时只转移第一行即可。总复杂度 $O(mb^2\log⁡n)$。

在 sunkuangzheng 大佬的提示下注意到矩阵大小只有 $20$ 且值只有 $0/1$，所以可以压位。总复杂度 $O(mb\log n)$。[code](https://atcoder.jp/contests/abc388/submissions/61673267)。

为啥跑的更慢了。

upd: 前两天又学会了点东西。注意到预处理和查询的复杂度不平衡，考虑更换 $\log $ 的底数来平衡复杂度，可以使复杂度进一步更优，复杂度具体是啥要看你取的底数，算算最优的是多少就行了。类似于多叉线段树的思想。

---

