# Lunch Menu

## 题目描述

[problemUrl]: https://atcoder.jp/contests/s8pc-5/tasks/s8pc_5_f

AtCoder カフェでは $ N $ 個の食事があり, 番号が $ 1 $ から $ N $ までつけられている. 食事 $ i\ (1\ \leq\ i\ \leq\ N) $ のおいしさは $ a_i $ である.  
 square1001 君は, $ Q $ 日間 AtCoder カフェで食事をする. $ i\ (1\ \leq\ i\ \leq\ Q) $ 日目の食事では, 番号が $ l_i $ 以上 $ r_i $ 以下の食事の中から最もおいしさの値が大きいものを選ぶ. また, そのような食事がない場合は食事をせずに帰る.

あなたは悪魔であり, 魔力で $ N $ 個中 $ M $ 個の食事をメニューからかき消して選べないようにすることができる. あなたの目的は square1001 君の選ぶ食事のおいしさの合計を最小化することである.  
 square1001 君の選ぶ食事のおいしさの合計の最小値を求めなさい.

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 50 $ 以下の整数.
- $ M $ は $ 0 $ 以上 $ N $ 以下の整数.
- $ Q $ は $ 1 $ 以上 $ 50 $ 以下の整数.
- $ a_i\ (1\ \leq\ i\ \leq\ N) $ は $ 1 $ 以上 $ 1\ 000\ 000\ 000 $ 以下の整数.
- $ l_i,\ r_i $ は $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ N $ を満たす整数.

### 小課題

小課題 $ 1 $ \[$ 60 $ 点\]

- $ N\ \leq\ 15 $.
- $ Q\ =\ 1 $.

小課題 $ 2 $ \[$ 60 $ 点\]

- $ N\ \leq\ 15 $.

小課題 $ 3 $ \[$ 250 $ 点\]

- すべての $ i\ (1\ \leq\ i\ \leq\ N) $ に対して, $ a_i\ =\ 1 $.

小課題 $ 4 $ \[$ 630 $ 点\]

- 追加の制約はない.

### Sample Explanation 1

もしあなたが番号 $ 2 $, $ 3 $ の食事を消すと, それぞれの日の美味しさの最大値は $ 4 $, $ 3 $, $ 8 $, $ 4 $, $ 8 $ となり, 合計が $ 27 $ となる.

## 样例 #1

### 输入

```
5 2 5
4 9 6 3 8
1 3
2 4
3 5
1 4
2 5```

### 输出

```
27```

## 样例 #2

### 输入

```
5 0 4
8 6 9 1 2
1 3
4 5
2 5
4 4```

### 输出

```
21```

## 样例 #3

### 输入

```
8 5 3
1 1 1 1 1 1 1 1
2 5
1 3
6 8```

### 输出

```
1```

# 题解

## 作者：Eric998 (赞：2)

咋没有乱搞题解。太不牛了。

我们充分发扬人类智慧。初始钦定前 $m$ 个为 $0$，退火每次随机还原期望 $3$ 个并把 $3$ 个改为 $0$。

注意到 ```subtask4``` 是用脚造的，能用朴素 SA 冲过去。```subtask3``` 有几个点卡人，拼个贪心上去就过了。

至此，我们实现了 $0+0=1$。注意计算答案要做到 $n\log n$，否则过不去。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 55
#define int long long
int a[N],z[N],n,m,k,ans=0x3f3f3f3f3f3f3f3fll;
vector<int> q[N],zer;
void add(int u,int v){
	while(u<N)
		z[u]=max(z[u],v),u+=u&(-u);
}
int que(int u){
	int val=0;
	while(u)
		val=max(val,z[u]),u-=u&(-u);
	return val;
}
int wktm,cktm;
int calc(vector<int>& ZER){
	memset(z,0,sizeof(z)),cktm++;
	int res=0;
	for(int i=1;i<=n;i++){
		if(!ZER[i])
			add(N-i,a[i]);
		for(int it:q[i])
			res+=que(N-it);
	}
	ans=min(ans,res);
	return res;
}
double delta=0.997,temp;
double RndDouble(){
	int v=rand();
	v%=1000000000;
	double res=1e-9*v;
	return res;
}

void work(){
	temp=1,wktm++;
	zer.clear(),zer.resize(n+1);
	for(int i=0;i<=n;i++)
		zer[i]=0;
	for(int i=1;i<=m;i++)
		zer[i]=1;
	int las=calc(zer);
	while(temp>1e-6){
		temp*=delta;
		auto cur=zer;
		while(rand()%3)swap(cur[rand()%n+1],cur[rand()%n+1]);
		int v=calc(cur);
		if(v<las || RndDouble()<temp)zer=cur,las=v;
	}
}
void freopen(string f){
	freopen((f+".in").c_str(),"r",stdin),freopen((f+".out").c_str(),"w",stdout);
}
int l[55],r[55],aa[55];
void greedy(){
    int M=m;
    for(int i=0;i<55;i++)aa[i]=a[i];
    while (1) {
        vector<pair<int, int>> vc;
        for (int i = 1; i <= k; i++) {
            int cnt = 0;
            for (int j = l[i]; j <= r[i]; j++)
                cnt += a[j];
            if (cnt) vc.emplace_back(cnt, i);
        }
        sort(vc.begin(), vc.end());
        if (!vc.empty() && m >= vc.front().first) {
            m -= vc.front().first;
            for (int j = l[vc.front().second]; j <= r[vc.front().second]; j++)
                a[j] = 0;
        } else
            break;
    }
    ans = 0;
    for (int i = 1; i <= k; i++) {
        int mx = 0;
        for (int j = l[i]; j <= r[i]; j++)
            mx = max(mx, a[j]);
        ans += mx;
    }
    for(int i=0;i<55;i++)a[i]=aa[i];
    m=M;
}
int cn1;
signed main(){
	srand(time(0));
	freopen("S");
	cin>>n>>m>>k;
	zer.resize(n+1);
	for(int i=1;i<=n;i++)
		cin>>a[i],cn1+=(a[i]^1);
	for(int i=1;i<=k;i++)
		cin>>l[i]>>r[i],q[r[i]].push_back(l[i]);
	if(!m){
		cout<<calc(zer);
		return 0;
	}
	if(!cn1)
        greedy();
	int t=clock();
	while(clock()-t<CLOCKS_PER_SEC*19/10)
		work();
	cout<<ans;//<<' '<<wktm<<' '<<cktm;
}
```

---

## 作者：Add_Catalyst (赞：1)

# AT_s8pc_5_f Lunch Menu 题解

------

## 知识点

区间最值背包 DP ~~，模拟退火（假）~~。

## 题意简述

给定 $N,M,Q$，以及长度为 $N$ 的数组 $\{ a_i \}_1^{N}$，$Q$ 个区间 $\{ [l_i,r_i] \}_1^Q$。

现可以将至多 $M$ 个 $a_i$ 变为 $0$，问 $\sum_{i=1}^Q (\max_{j=l_i}^{r_i} a_j)$ 的最小值。

## 分析

对于单个区间，为了让最大值变小，肯定首先从区间中的最大值开始变为 $0$，扩展到全局也是如此。那么就有一个思路：从最大值开始降序一个个决策是否删除。

假设一开始有一个区间集合 $S$，包含题目给定的 $Q$ 个区间。现在枚举到 $i$。

- 不删除：把 $S$ 中跨越 $i$ 的区间贡献设为它，并加入答案，然后从 $S$ 中删除。
- 删除：直接跳过，然后枚举下一个。

但是这样说很模糊，因为除了爆搜很难提出具体的方案。我们考虑如何让从区间集合中找到和删除跨越它的区间，难道直接压缩然后记在状态里吗？

并不用。把跨越某个点的区间删除之后，这个点就没有任何用处了，我们可以直接把它删掉，然后把 $S$ 分成两个新的 $S’_l，S'_r$，分别放到左边和右边。就像在[笛卡尔树](https://oi-wiki.org/ds/cartesian-tree/)上做分治一样，但是我们这里与笛卡尔树有两个区别：

1. $a_i$ 数值一样的不好处理。
2. 决策时删除对应的**跳过**不好处理。

那又该怎么办呢？注意到数据范围很小，我们可以直接记下当前处理的区间 $[L,R]$，然后就可以做区间 DP。为了方便理解，我们类比笛卡尔树上分治，称其为“分治区间”（不知道笛卡尔树也没关系，这只是个类比），其实就是 $S$ 变成一个包含并且只包含所有满足 $L\le l_i \land r_i \le R$ 的区间的集合，这也是我们选用区间 DP 的原因。

接下来回到决策方面：

- 不删除：把 $S$ 中跨越 $i$ 的区间贡献设为它，并加入答案，然后从 $S$ 中删除。对应的是：从分治区间 $[L,R]$ 下到 $[L,i-1],[i+1,R]$。
- 删除：直接跳过，然后枚举下一个。

然后加上显然的枚举到第几个和还剩几次赋值为 $0$ 的机会两个参数，就可以 DP 了。

设 $f_{i,j,l,r}$ 表示现在枚举到倒数第 $i$ 大的数，还剩 $j$ 次赋值为 $0$ 的机会，当前分治区间为 $[l,r]$ 的最小和；$cnt_{l,r,mid}$ 表示现在分治区间为 $[l,r]$ 的情况下，区间集合 $S$ 内有几个区间跨域点 $mid$；$pos_i,w_i$ 表示倒数第 $i$ 大的数的位置和值。

转移方程：（$a \gets b$ 表示 `tomin(a,b)`，即 $a = \min{(a,b)}$）

- 不删除：
  $$
  f_{i,j,l,r} \gets \min_{k=0}^j {\{f_{i-1,j-k,l,i-1}[l < i] + f_{i-1,k,i+1,r}[i < r] 
  + cnt_{l,r,pos_i} \times w_i \}} \\
  $$

- 删除：
  $$
  f_{i,j,l,r} \gets f_{i,j-1,l,r} \\
  $$

为了方便理解和编码，我们可以选用记忆化搜索来进行 DP。

## 代码

时间复杂度：$O(N^3M^2+N^3Q)$，空间复杂度：$O(N^3M)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define ll long long
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define FOR(i,a,b) for(int i(a); i<=(int)(b); ++i)
#define DOR(i,a,b) for(int i(a); i>=(int)(b); --i)
#define EDGE(g,i,x,y) for(int i(g.h[x]),y(g[i].v); ~i; y=g[i=g[i].nxt].v)
using namespace std;
constexpr int N(50+10);

namespace IOEstream {
    //...快读快写省略
} using namespace IOEstream;

int n,m,Q;
int a[N],l[N],r[N];
int cnt[N][N][N];
ll f[N][N][N][N];
struct node {
	int idx,val;
	friend bool operator <(node a,node b) {
		return a.val<b.val;
	}
} b[N];

ll dp(int u,int rem,int l,int r) {
	if(~f[u][rem][l][r])return f[u][rem][l][r];
	ll &res(f[u][rem][l][r]);
	res=LINF;
	if(!u||l>r)return res=0;
	if(b[u].idx<l||b[u].idx>r)return res=dp(u-1,rem,l,r);
	if(rem)res=dp(u-1,rem-1,l,r);
	FOR(i,0,rem)
	tomin(res,dp(u-1,i,l,b[u].idx-1)+dp(u-1,rem-i,b[u].idx+1,r)+(ll)cnt[l][r][b[u].idx]*b[u].val);
	return res;
}

int main() {
	I(n,m,Q);
	FOR(i,1,n)I(a[i]);
	FOR(i,1,Q)I(l[i],r[i]);
	FOR(i,1,n)b[i]= {i,a[i]};
	sort(b+1,b+n+1),RCL(f,-1,f,1);
	FOR(L,1,n)FOR(R,L,n)FOR(i,1,Q)if(L<=l[i]&&r[i]<=R)FOR(mid,l[i],r[i])++cnt[L][R][mid];
	O(dp(n,m,1,n),'\n');
	return 0;
}
```

## 关于模拟退火

为什么我在模拟退火的后面加了一个“假”呢？

因为按照我在某校 OJ 上看到的题解，这东西还要拼一个贪心过部分分才行，所以并不是一个完全的算法，不过拿来骗分也不失为一种好方法。

### 思路

先把 $M$ 个赋值为 $0$ 的数加进去，然后每次随机三个为 $0$ 的位置和三个不为 $0$ 的位置交换，套上退火模版。

然后写完了发现可能过不了第三个子任务，这时候我们套个贪心设定一下初始时 $M$ 个赋值为 $0$ 的数，然后在退火。

（思路来源于某校 OJ 上看到的题解，没有实现，这里仅仅是提供思路。）

------

---

## 作者：_lmh_ (赞：1)

不妨设 $a_0=a_{n+1}=+\infin$，我们考虑钦定每个区间内的最大值。

令 $f_{l,r,k}$ 为：只考虑被 $[l,r]$ 包含的区间，在其中保留 $k$ 个 $a_i$（其余位置置 $0$），并且所有保留的 $a_i$ 不大于 $\min\{a_{l-1},a_{r+1}\}$ 的最小代价，转移时钦定一个选的位置为最大值，算出该点的贡献之后对两边区间的 $f$ 值做 $(\min,+)$ 卷积即可。最小值不用担心算重的问题。

时间复杂度 $O(n^5)$，常数约为 $\frac{1}{120}$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=53;
ll n,m,k,a[N],b[N],id[N],l[N],r[N],f[N][N][N],w[N][N][N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(f,0x3f,sizeof(f));
	cin>>n>>m>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=k;++i) cin>>l[i]>>r[i];
	a[0]=a[n+1]=2e9;
	for (int L=1;L<=n;++L) for (int R=L;R<=n;++R) for (int i=L;i<=R;++i) for (int o=1;o<=k;++o) w[L][R][i]+=(L<=l[o]&&l[o]<=i&&i<=r[o]&&r[o]<=R);
	for (int i=0;i<=n;++i) f[i+1][i][0]=0;
	for (int len=1;len<=n;++len) for (int L=1,R=len;R<=n;++L,++R){
		f[L][R][0]=0;
		for (int k=L;k<=R;++k) if (a[k]<=a[L-1]&&a[k]<=a[R+1]){
			ll tmp=a[k]*w[L][R][k],lenL=k-L,lenR=R-k;
			for (int i=0;i<=lenL;++i) for (int j=0;j<=lenR;++j) f[L][R][i+j+1]=min(f[L][R][i+j+1],f[L][k-1][i]+f[k+1][R][j]+tmp);
		}
	}
	ll ans=1e18;
	for (int i=n-m;i<=n;++i) ans=min(ans,f[1][n][i]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

从大到小考虑 $a_i$ 的贡献。

定义状态 $f(lst,left,l,r)$ 表示上一个选择的数为 $lst$，还剩 $left$ 次选择机会，仅查找区间 $i$ 满足 $l\leq l_i\leq r_i\leq r$ 的答案。

考虑转移分两种情况。

- 选择区间内未选过的最靠左的最大值，设这个位置为 $k$，有转移 $f(lst,left,l,r)\leftarrow f(k,left-1,l,r)$。
- 否则，枚举分给左右两边剩余次数，$f(lst,left,l,r)\leftarrow \min_{i=0}^{left}f(lst,i,l,k-1)+f(lst,left-i,k+1,r)+a_k\times cnt$。其中 $cnt$ 是满足 $l\leq l_i\leq k\leq r_i\leq r$ 的 $i$ 的个数。

令 $a_{n+1}=+\infty$，答案为 $f(n+1,m,1,n)$。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=60;
const ll inf=0x3fffffffff;
ll f[sz][sz][sz][sz],a[sz];
int l[sz],r[sz],n,m,q;
ll dfs(int k,int left,int cl,int cr){
  if(cl>cr)return 0;
  if(f[k][left][cl][cr]!=-1)return f[k][left][cl][cr];
  int pos=0,cnt=0;
  for(int i=cl;i<=cr;i++){
    if(a[i]>a[k]||a[i]<=a[pos])continue;
    if(a[i]<a[k]||i>k)pos=i;
  }
  if(pos==0)return f[k][left][cl][cr]=0;
  for(int i=1;i<=q;i++)
    if(l[i]>=cl&&r[i]<=cr&&pos>=l[i]&&pos<=r[i])cnt++;
  ll res=inf;
  if(pos!=0&&left!=0)res=std::min(res,dfs(pos,left-1,cl,cr));
  for(int i=0;i<=left;i++)
    if(i<=pos-cl&&left-i<=cr-pos)
      res=std::min(res,dfs(k,i,cl,pos-1)+dfs(k,left-i,pos+1,cr)+a[pos]*cnt);
  return f[k][left][cl][cr]=res;
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin>>n>>m>>q;
  for(int i=1;i<=n;i++)std::cin>>a[i];
  for(int i=1;i<=q;i++)std::cin>>l[i]>>r[i];
  a[n+1]=inf;
  for(int i=1;i<=n+1;i++)
    for(int j=0;j<=m;j++)
      for(int l=1;l<=n;l++)
        for(int r=l;r<=n;r++)f[i][j][l][r]=-1;
  std::cout<<dfs(n+1,m,1,n)<<"\n";
  return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## 题意

给你一个 $N$ 个数的数组 $a$，$Q$ 个区间和一个整数 $M$。你最多能选 $M$ 个 $a$ 的数使它变成 $0$，求 $\sum\limits_{i=1}^Q\max\limits_{j=l_i}^{r_i}a_j$ 的最小值。

## 题解

对于每个区间，我们只关注最大值，所以我们从大到小考虑每一个数是否变 $0$。

当一个数保留时，我们可以立即处理跨过这个点的所有区间。那么就能将一个大问题分解成两个小问题。

比如当我们处理 $[l,r]$ 中的问题时，保留这个区间中最大的数 $x$，位置为 $y$。那么就能分解为两个子问题：处理 $[l,y-1]$ 和 $[y+1,r]$，只能保留 $[1,x-1]$ 的数。

维护一下上一次保留哪个数和还剩几次操作次数，然后记忆化搜索即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=55;
int n,m,q,a[N],cnt[N][N][N],b[N];
ll f[N][N][N][N];
ll dfs(int l,int r,int x,int y){
	if(y>=r-l+1||l>r)return 0;
	if(~f[l][r][x][y])return f[l][r][x][y];
	int t=x;
	while(t<=n&&(b[t]<l||r<b[t]))t++;
	if(t>n)return 0;
	f[l][r][x][y]=1e18;
	//save
	for(int i=0;i<=y;i++)f[l][r][x][y]=min(f[l][r][x][y],dfs(l,b[t]-1,x,i)+dfs(b[t]+1,r,x,y-i)+1ll*cnt[b[t]][l][r]*a[b[t]]);
	//delete
	if(y)f[l][r][x][y]=min(f[l][r][x][y],dfs(l,r,t+1,y-1));
	return f[l][r][x][y];
}
bool cmp(int x,int y){return a[x]>a[y];}
int main(){
	memset(f,-1,sizeof(f));
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=i;
	sort(b+1,b+n+1,cmp);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		for(int j=l;j<=r;j++){
			for(int L=1;L<=l;L++){
				for(int R=r;R<=n;R++){
					cnt[j][L][R]++;
				}
			}
		}
	}
	cout<<dfs(1,n,1,m);
}
```

---

## 作者：Petit_Souris (赞：0)

放在 2020 可能是 NOIP 难度 DP 好题，放在 2024 应该很多人都会做了。

假设 $n,m,q$ 同阶。

显然这个区间 max 启发我们建立笛卡尔树，每次处理所有经过当前最大值的询问。

因此区间 dp 是很明显的。设 $f_{l,r,i,0/1}$ 表示目前考虑区间 $[l,r]$，还可以操作 $i$ 次，上一次操作的区间在左边还是在右边（我们建树时取最大值中最靠左的那个，所以这个维度是关键的）。

转移的时候枚举最大值在哪个位置，并对两边做 $(\min,+)$ 卷积即可。复杂度 $\mathcal O(n^6)$，但是发现这个卷积不用重复做，预处理一遍就行了，所以是 $\mathcal O(n^5)$ 的。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=55,INF=1e16;
ll n,m,q,a[N],L[N],R[N],id[N],need[2][N],g[N][N],cross[N];
ll dp[N][N][N][2];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read(),q=read();
    rep(i,1,n)a[i]=read();
    rep(i,1,q)L[i]=read(),R[i]=read();
    a[0]=a[n+1]=2e9;
    rep(i,0,n+1){
        rep(j,0,n+1){
            rep(k,0,m+1){
                rep(l,0,1)dp[i][j][k][l]=INF;
            }
        }
    }
    rep(i,1,n+1){
        rep(j,0,1)dp[i][i-1][0][j]=0;
    }
    rep(len,1,n){
        rep(l,1,n-len+1){
            ll r=l+len-1;
            memset(need,0,sizeof(need));
            rep(x,0,1){
                ll v=(x==0?a[l-1]:a[r+1]),c=0;
                rep(i,l,r){
                    if(a[i]<v||(x==0&&a[i]==v)){
                        c++;
                        rep(j,l,r){
                            if(a[j]<v||(x==0&&a[j]==v)){
                                if(a[j]>a[i]||(a[j]==a[i]&&j<i))need[x][i]++;
                            }
                        }
                    }
                }
                rep(i,c,m)dp[l][r][i][x]=0;
            }
            memset(cross,0,sizeof(cross));
            rep(i,1,q){
                if(l<=L[i]&&R[i]<=r)cross[L[i]]++,cross[R[i]+1]--;
            }
            rep(i,l,r)cross[i]+=cross[i-1];
            rep(i,l,r){
                rep(t,0,m+1)g[i][t]=INF;
            }
            rep(i,l,r){
                rep(p,0,min(m,i-l)){
                    rep(q,0,min(m-p,r-i)){
                        g[i][p+q]=min(g[i][p+q],dp[l][i-1][p][1]+dp[i+1][r][q][0]);
                    }
                }
                rep(p,1,m)g[i][p]=min(g[i][p],g[i][p-1]);
            }
            rep(k,0,min(m,len)){
                rep(x,0,1){
                    ll v=(x==0?a[l-1]:a[r+1]);
                    rep(i,l,r){
                        if(a[i]<v||(x==0&&a[i]==v)){
                            if(k<need[x][i])continue;
                            dp[l][r][k][x]=min(dp[l][r][k][x],g[i][k-need[x][i]]+cross[i]*a[i]);
                        }
                    }
                }
            }
        }
    }
    ll ans=INF;
    rep(i,0,m)ans=min({ans,dp[1][n][i][0],dp[1][n][i][1]});
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

