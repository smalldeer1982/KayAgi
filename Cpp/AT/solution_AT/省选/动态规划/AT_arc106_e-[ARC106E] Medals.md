# [ARC106E] Medals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc106/tasks/arc106_e

あなたは $ N $ 人の従業員を持つ店の店長です。 各従業員は一定の周期で出勤します。 より正確には、$ i $ 番目の従業員は今日から「$ A_i $ 日連続で働いた後 $ A_i $ 日連続で休む」ことを繰り返します。

あなたは今日から毎日出勤し、その日に出勤している従業員の中から $ 1 $ 人選び、メダルを $ 1 $ 枚配ります。（その日に出勤している従業員が $ 1 $ 人もいなければ何もしません）

全ての従業員に $ K $ 枚以上のメダルを配るためには、最短で何日かかるでしょうか。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 18 $
- $ 1\ \le\ K\ \le\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^5 $

### Sample Explanation 1

例えば、以下のようにメダルを配ることができます。 - $ 1 $ 番目の従業員には、$ 1,\ 5,\ 9 $ 日目にメダルを配る - $ 2 $ 番目の従業員には、$ 2,\ 6,\ 10 $ 日目にメダルを配る - $ 3 $ 番目の従業員には、$ 3,\ 7,\ 8 $ 日目にメダルを配る $ 4 $ 日目には出勤している従業員が $ 1 $ 人もいないため、これは最短となる配り方の $ 1 $ つです。

## 样例 #1

### 输入

```
3 3
1 2 3```

### 输出

```
10```

## 样例 #2

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1```

### 输出

```
199```

## 样例 #3

### 输入

```
2 5
1234 5678```

### 输出

```
10```

# 题解

## 作者：Jsxts_ (赞：13)

题意：

你有 $N$ 个朋友，他们会来你家玩，第 $i$ 个人 $1\dots A_i$
  天来玩，然后 $A_i+1\dots 2A_i$ 天不来，然后 $2A_i+1\dots 3A_i$ 天又会来，以此类推。

每天你会选一个来玩的人，给他颁个奖，如果没人来玩，你就不颁奖。

你要给每个人都颁 $K$ 个奖，问至少需要多少天。

题解：

有教育意义的题。

首先证明一个结论：答案不超过 $2\times N \times K$。考虑先给第一个朋友颁奖，颁完再给第二个，以此类推。颁完一个人的天数不超过 $2K$，那 $N$ 个人就不超过 $2NK$。

考虑二分答案，二分完了以后就是一个网络流模型：把每个人拆成 $K$ 个点，向对应来你家的天表示的点连边，跑二分图即可，但是过不了。

$\text{Hall}$ 定理：一个二分图有完美匹配，当且仅当二分图其中一个点集的子集向另外一个点集连边，任意这样的子集所能连到的对应的节点集合大小大于等于当前集合。

对于这题，我们可以先预处理出每一天来你家的朋友的状态，然后考虑一天在 $i$ 这个子集里有边，当且仅当这一天代表的子集和 $i$ 有交。那么只要知道与 $i$ 没有交的子集（即 $i$ 的补集）对应的天数，再用总天数（二分的 $mid$）减掉，剩下的就是与 $i$ 有交的天数。判断这个天数是否大于等于 $popcount(i)\times K$ 即可（因为每一个朋友对应 $K$ 个点）。设 $f_i$ 表示 $i$ 的子集代表的朋友匹配的天数。这个可以用高维前缀和来求。时间复杂度 $O(N2^N\log K)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,m,k,a[20],ans[20],s,st[3600010],f[1<<18];
bool check(int mid) {
	for (int i = 0;i < s;i ++ ) f[i] = 0;
	for (int i = 1;i <= mid;i ++ ) f[st[i]] ++;
	for (int i = 0;i < n;i ++ )
		for (int j = 0;j < s;j ++ )
			if (!(j >> i & 1)) f[j | (1 << i)] += f[j];
	for (int i = 0;i < s;i ++ )
		if (mid - f[s - i - 1] < __builtin_popcount(i) * k) return 0;
	return 1;
}
int main() {
	n = read(), k = read(), m = n * 2 * k, s = 1 << n;
	int mn = 0;
	for (int i = 1;i <= n;i ++ ) a[i] = read();
	for (int i = 1;i <= m;i ++ )
		for (int j = 1;j <= n;j ++ ) {
			if ((i + a[j] - 1) / a[j] % 2 != 0) st[i] |= (1 << j-1);
		}
	int l = 1,r = m;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```


---

## 作者：Albert_van (赞：6)

二分答案 $m$（上界稍后讨论），不难想到网络流，每一天向来上班的人连边即可。似乎没有优化空间，考虑把每个人拆成 $k$ 个点，二分图，左部（$nk$ 个点）向右部（天）连边，要求左部点被全部匹配。

有一种东西叫 Hall 定理，讲的是：左部点集合 $L$，右部点 $R$，那么 $L$ 全部能匹配的充要条件是：
$$
\forall S\subseteq L,\exists T\subseteq R:|T|\ge |S|,T\text{中所有点均与}S\text{有连边}
$$
考虑直接枚举 $S$ 进行判定。显然，这个条件在最严格的时候，$S$ 中每个人对应的 $k$ 个点，要么全部不取，要么都取。这是因为这 $k$ 个点的邻接点是一样的。于是需要判定的 $S$ 只有 $2^n$ 种。对于一个 $S$，设它涉及到人的集合为 $A$，我们要求：
$$
|\{x|x\le m,\exists p\in A:p\text{在第}x\text{天上班}\}|\ge |A|
$$
即 $x$ 的邻接点与 $A$ 有交，这个很难处理。正难则反地，
$$
|\{x|x\le m,\not\exists p\in A:p\text{在第}x\text{天上班}\}|\le m-|A|
$$
等价于 $x$ 的邻接点 $\subseteq \complement_{[1,n]}A$。判定 $p$ 是否在第 $x$ 天上班是简单的，于是这就是一个 SOS。

关于 $m$ 的上界，观察样例可知它是 $2nk$。在这 $2nk$ 天中，每个人至少会来工作 $nk$ 天。因此每天任意颁奖就能满足要求，极端情况是每个人的工作天数重合。

复杂度 $\mathcal O((n^2k+n2^n)\log k)$。精细实现把 $n^2k$ 提到外面。

```cpp
#include <cstdio>
#include <cstring>
#pragma GCC target("popcnt")

int su[231231+31231],a[31];

int main()
{
	int n,k;scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	int l=n*k,r=l<<1,U=(1<<n)-1;
	int ans=114514;while(l<=r){
		memset(su,0,sizeof(su));
		int m=l+r>>1;for(int p=1;p<=m;++p){
			int s=0;for(int i=0;i<n;++i) if((p-1)%(a[i]<<1)<a[i]) s|=1<<i;
			++su[s];
		}
		for(int i=0;i<n;++i) for(int s=1;s<1<<n;++s) if(s&(1<<i)) su[s]+=su[s^(1<<i)];
		bool flg=1;for(int s=1;s<1<<n;++s) flg&=(su[U^s]<=m-__builtin_popcount(s)*k);
		flg?(ans=m,r=m-1):(l=m+1);
	}
	printf("%d",ans);
}
```



---

## 作者：Purslane (赞：6)

# Solution

今天模拟赛的最后一道题，~~也是我过的两道题之一~~。

正解要用二分图，但我有一种不用二分图的做法。

首先，我们发现 $n$ 很小，那么大抵要状压。而且我们可以发现，对于任意一个人，就算运气再被，也可以在 $200000$ 的连续时间内找到 $100000$ 个工作日。这说明一共就 $200000n$ 天就一定能解决问题，因此我们可以枚举每一天的情况。

对于每一天，我们可以记录上班的人的集合 $S$。因此对于 $2^n$ 种集合，我们可以二分答案之后找到前 $m$ 天每种集合出现的次数。

那么问题变为给定你 $2^n$ 个集合，每个集合有 $cnt_S$ 个礼物。你要把每个集合的礼物分给集合中某一个元素，使得每个元素的礼物总和都大于等于 $k$。

这个可以转化为网络流问题。建立一个二分图（我说不用二分图是因为没用到二分图的性质），左部点表示集合，右部点表示人。左部点对应的集合向对应的人连容量为正无穷的边。源点向左部点连容量为二分的时间内这个集合出现的次数的边，右部点向汇点连容量为 $k$ 的边。看最大流是否是 $nk$ 即可。

但是 Dinic 的复杂度很高，不足以通过有 $2^n$ 个点和边规模的问题。

我们可以考虑最大流等于最小割，这种有特殊结构的图用最小割会很简单。

很显然左右之间的连边不会出现在最小割之中，那么枚举右部集合中没有被割掉的边。那么和这些点有连边的左部点与源点的连边都要割掉。而这样的左部点构成的集合就是全集去掉不能到达右部给定点的集合。这用一个高维前缀和就可以解决问题。

时间复杂度为 $O(n^2k+2^n\log nk)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=19,MAXM=1e7+10;
int n,k,a[MAXN+10],pre[(1<<MAXN)+10],dp[(1<<MAXN)+10],id[(1<<MAXN)+10],popcnt[(1<<MAXN)+10];
vector<pair<int,int>> pos[(1<<MAXN)+10];
int pd(int t,int a) {
	int mod=t%(a+a);
	if(mod&&mod<=a) return 1;
	return 0; 
}
int check(int t) {
	ffor(i,0,(1<<n)-1) {
		auto it=lower_bound(pos[i].begin(),pos[i].end(),make_pair(t+1,0));
		if(it==pos[i].begin()) pre[i]=0;
		else {
			--it;
			pre[i]=it->second;
		}
	}
	ffor(i,1,n) ffor(j,0,(1<<n)-1) if(!(j&(1<<i-1))) pre[j+(1<<i-1)]+=pre[j];
	long long ge=LONG_LONG_MAX;
	ffor(i,0,(1<<n)-1) {
		dp[i]=pre[(1<<n)-1]-pre[(1<<n)-1-i];
		ge=min(ge,1ll*dp[i]+1ll*(n-popcnt[i])*k);
	}
	if(1ll*ge==1ll*n*k) return 1;
	return 0;
}
int bfind(int l,int r) {
	int ans=0;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>a[i];
	double st=clock();
	ffor(i,1,4000000) {
		int st=0;
		ffor(j,1,n) if(pd(i,a[j])) st|=(1<<j-1);
		pos[st].push_back({i,++id[st]});
	}
	ffor(i,1,(1<<n)-1) popcnt[i]=popcnt[i>>1]+(i&1);
	cout<<bfind(1,4000000);
	return 0;	
}
```

UPD : 我这个就是从另一个角度理解了 Hall 定理。

---

## 作者：born_to_sun (赞：3)

大家都是使用 Hall 定理最后用 SOSDP 求解的，我来发个**模拟网络流**的题解。

### 网络流建模
首先将题意转化为二分图匹配问题，左部点为天数，右部点为人，对于天数 $i$，向所有第 $i$ 天可以颁奖的人连容量为 $1$ 的边。

然后假定我们确定了天数 $k$，建出前 $k$ 个左部点，跑一边最大流就能判断是否合法。

但是，显然朴素的进行二分 + Dinic 是过不了的。

### 优化算法
我们枚举天数 $d$，判断是否合法，如果不合法就让 $d$ 增加 $1$，然后在原图上增加一个左部点，设其为 $u$。

考虑模拟 Dinic 寻找增广路的过程，你会发现一条增广路一定是从 $u$ 出发，沿正边走向右部点，沿反边走向左部点，沿正边走向右部点，如此往复，一直走到某个和汇点之间仍有流量的点。这样就找到了一条增广路。

继续观察，我们发现以下性质：
1. 我们这张二分图右部点的数量相当少，只有 $O(n)$ 级别。
2. 一条增广路重复经过了同一个点一定是不优的。
3. 对于一个左部点，它和右部点的连边中至多有 $1$ 条反边存在流量。

考虑建一个只有 $n$ 个点的新图，对于一个左部点 $u$，如果它和一个右部点 $v$ 存在有流量的反边，那么在新图上连边 $v\rightarrow v'$，其中 $v'\neq v$，$v'$ 为和 $u$ 有连边的右部点。

我们在新图上 dfs，如果走到一个在原图上有流量的点，说明找到了一条增广路。然后在回溯时把应该修改的点都修改连边几遍。

具体实现可以使用链表 + 空间回收，否则会 MLE。
### 不同算法复杂度的对照
Hall 定理 + 高维前缀和：$O(2^nn\log(nk))$；

朴素的 Dinic：$O(n^2k\sqrt{nk}\log(nk))$；

模拟网络流：$O(n^3k)$。

可以发现，本题解提供的解法在本题的数据范围下表现的并不优秀，最慢的点用了 $1.6s$。但可以通过诸如 $n=50,k=1000$ 的数据，仍是一种不错的解法。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+5;
const int M=7e7+5;
int n,k;
int a[40],S[N];
int to[N],rs[20];
int f[N][20];
int head[20][20];
struct E{
	int lst,nxt,val;
}e[M];
int sk[M],top;
void add(int id,int v){
	int u=to[id];
	int s=S[id];
	while(s){
		int i=__builtin_ctz(s);
		s-=(1<<i);
		int x=f[id][i];
		if(x){
			if(x==head[u][i]) head[u][i]=e[x].nxt;
			if(e[x].nxt) e[e[x].nxt].lst=e[x].lst;
			if(e[x].lst) e[e[x].lst].nxt=e[x].nxt;
			sk[++top]=x;
		}
		f[id][i]=0;
		if(i!=v){
			int now=sk[top--];
			f[id][i]=now;
			int &h=head[v][i];
			if(h) e[h].lst=now;
			e[now]={0,h,id};
			h=now;
		}
	}
	to[id]=v;
}
int vis[20];
int dfs(int u){
	if(vis[u]) return -1;
	if(rs[u]){rs[u]--;return u;}
	vis[u]=1;
	for(int v=0;v<n;v++){
		if(vis[v]) continue;
		if(head[u][v]&&~dfs(v)){
			int x=e[head[u][v]].val;
			add(x,v);
			return u;
		}
	}
	return -1;
}
void solve(){
	for(int i=1;i<M-5;i++) sk[++top]=i;
	for(int i=0;i<n;i++) rs[i]=k;
	for(int i=1;;i++){
		int s=S[i];
		memset(vis,0,sizeof(vis));
		to[i]=-1;
		for(int j=0;j<n&&to[i]==-1;j++){
			if((s>>j)&1) to[i]=dfs(j);
		}
		if(to[i]!=-1) add(i,to[i]);
		int f0=0;
		for(int i=0;i<n;i++) f0|=rs[i];
		if(!f0){cout<<i;break;}
	}
}
signed main(){
	cin>>n>>k;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++){
		for(int d=1;d<=n*k*2;d+=2*a[i]){
			for(int j=d;j<d+a[i];j++) S[j]|=1<<i;
		}
	}
	solve();
	return 0;
}
```

---

## 作者：syzf2222 (赞：2)

必然是要二分答案的。

我们给 $1$ 到 $mid$ 的每一天分类。设 $f_S$ 表示恰好集合 $S$ 来的天数，$g_S$ 表示集合 $S$ 有人来的天数。

类似霍尔定理的，充要条件为 $g_S\geqslant k|S|$。

注意到答案不会超过 $O(nk)$ 级别。

于是整体复杂度为 $O(kn^2+n2^n\log nk)$，其中 $n2^n$ 在知 $f$ 求 $g$ 上。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int maxm=5e6+10;
const int N=(1<<18)+5;
int n,m,k,a[maxn],s[maxm],f[N],ppc[N];
inline bool chk(int mid){
	bool flg=true;memset(f,0,sizeof(f));
	for(int i=1;i<=mid;i++)++f[s[i]];
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)if(j>>i&1)f[j^(1<<i)]+=f[j];
	for(int i=0;i<(1<<n);i++)if(ppc[i]&1)f[i]=-f[i];f[0]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)if(j>>i&1)f[j]+=f[j^(1<<i)];
	for(int i=1;i<(1<<n);i++)flg&=(abs(f[i])>=k*ppc[i]);
	return flg;
}
int main(){
	n=read(),k=read();m=2*n*k;
	for(int i=1;i<(1<<n);i++)ppc[i]=ppc[i>>1]+(i&1);
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
		for(int j=0;j<n;j++)
			if((i-1)%(2*a[j])+1<=a[j])s[i]|=(1<<j);
	int l=m/2,r=m,res=r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(chk(mid))r=mid-1,res=mid;
		else l=mid+1;
	}printf("%d\n",res);
	return 0;
}
```

深深地感到自己的渺小。

---

## 作者：liyixin0514 (赞：1)

# [[ARC106E] Medals](https://www.luogu.com.cn/problem/AT_arc106_e)

## 题意

有 $n \le 18$ 个人，每个人会工作 $a_i$ 天，休息 $a_i$ 天，然后又工作 $a_i$ 天，以此类推。每天你可以给至多一个在岗的人发奖。问每个人至少发了 $k$ 个奖至少需要几天。

## 思路

参考了洛谷题解区。自认为写得详细，不需要前置知识也可以看懂~~因为我都不会那些前置知识~~。

首先答案下界显然是 $nk$，上界则是 $2nk$，当你先给第一个人发满 $k$ 个奖，显然最多使用 $2k$ 天，然后再发第二个人，一个一个人发，因此上界是 $2nk$。

求最小答案不好求，考虑二分答案，做判定问题：能否在 $mid$ 天完成发奖。

每天都可以从若干个人中选择一个人发奖，这种无法贪心，感觉没有多项式算法，考虑建二分图。

左部是人，右部是天（笑点解析：右部是天）。每个人和他能上班的天连边。我们把一个人拆成 $k$ 个人（笑点有些密集，以下不做解析）。题目相当于做边覆盖，每个左部点必须覆盖至少一次，每个右部点至多被覆盖一次。判定能否达成。

把右边没有用的点扔掉，相当于问能否做一个完美匹配（即边覆盖满足每个点都恰好覆盖了一次）

有 Hall 定理：一个二分图可以做完美匹配，当且仅当某一部的任意一个点集 $S$，于这个点集的点有连边的右部点集为 $T$，都有 $|T| \ge |S|$。

必要性显然，因为如果不满足 Hall 定理，那么有某一个 $|S| > |T|$，那么 $S$ 里面一定存在点是没有被匹配的。充分性也显然，因为如果满足 Hall 定理但是最大匹配不是完美匹配，那么左部点全集对应的 $|S| < |T|$，矛盾。

因此我们要判定能否存在完美匹配，只需要判断是否对于所有人的子集，都有对应的天的集合大小大于等于人的集合。

因为我们刚刚把一个人拆成了 $k$ 个人，这 $k$ 个人的边是一样的，因此我们不拆他们了。

也就是人的集合是 $S$，对应的天的集合是 $T$，判定是否 $k|S| \le |T|$。

每个人都有 $O(nk)$ 条边连向天。可以预处理每天有哪些人上班，这些上班的人叫做每天的上班集合，时间复杂度 $O(n^2k)$。

求 $|T|$，就是求有多少天的上班集合和 $S$ 是有交的，这个求有交的不好求，不好优化。正难则反，我们该求有多少天的上班集合是和 $S$ 无交的，即有多少天的上班集合是包含于 $S$ 关于 $n$ 个人的补集的。

这个包含于就好求了。可以做个 $n$ 维的高维前缀和，每维只有 $0/1$ 代表这个人上不上班。然后对所有天的上班集合做个前缀和，然后对所有的 $S$，数 $S$ 的补集有多少个天的上班集合包含于它，就直接前缀和 $O(1)$ 查询。

这里求前缀和是 $O(2^nn)$ 的，枚举 $S$ 是 $O(2^n)$ 的，还要二分答案，再加上预处理每天的上班集合，总时间是 $O(n^2k+2^nn \log (nk))$。

## code

代码还是很好写的。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace characteristic {
    constexpr int N=20,K=1e5+7,V=3e5;
    int n,k;
    int a[N];
    int d[2*N*K];
    int s[V];
    int l,r;
    bool check(int m) {
        memset(s,0,sizeof(s));
        rep(i,1,m) s[d[i]]++;
        rep(i,0,n-1) rep(j,0,(1<<n)-1) if((j>>i)&1) s[j]+=s[j^(1<<i)];
        rep(i,0,(1<<n)-1) {
            if(m-s[(1<<n)-1-i]<k*__builtin_popcount(i)) return 0;
        }
        return 1;
    }
    void main() {
        sf("%d%d",&n,&k);
        l=n*k,r=l<<1;
        rep(i,0,n-1) sf("%d",&a[i]);
        rep(i,0,n-1) {
            for(int j=1,op=1;j<=r;j++) {
                d[j]|=(op<<i);
                if(j%a[i]==0) op^=1;
            }
        }
        while(l<r) {
            int mid=(l+r)>>1;
            if(check(mid)) r=mid;
            else l=mid+1;
        }
        pf("%d\n",r);
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    characteristic :: main();
}
```

---

## 作者：Filberte (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_arc106_e)

## 思路

先思考答案的范围（感觉其他题解没把这个上界严谨的说清楚）。每天最多颁 $1$ 个奖，$n$ 个人每人想拿 $k$ 个奖，至少需要 $nk$ 天，这是下界。考虑使用网络流构图以勾勒出上界：

- 源点 $s$ 向左部 $D$ 个点每个点连一条边权为 $1$ 的边，代表每天只能颁 $1$ 个奖。
- 右部 $n$ 个点每个点向汇点 $t$ 连一条边权为 $k$ 的边，代表每个人需要 $k$ 个奖。
- 若第 $d$ 天第 $x$ 个人会来上班，则从左部第 $d$ 个点向右部第 $x$ 个点连一条边权为正无穷的边，代表可以在第 $d$ 天把奖颁给第 $x$ 个人。

此时，若此图的最大流是 $nk$，则说明 $D$ 天内可以使得每个人获得 $k$ 个奖。

先考虑 $D = 2nk$ 的分数流构造，根据整数流定理，对于任意一个分数流，只要其总流量为整数，则存在一个整数流。对于左部第 $d$ 个点，若其连接了 $z$ 个右部点，则从 $s$ 向它流 $\dfrac{z}{n}$  的流量，并向它连接的右部点流 $\dfrac{1}{n}$ 的流量。在这个流法下，因为 $z\le n$，所以满足流量限制。而每个右部点在 $2nk$ 天内至少连接了 $nk$ 个左部点，每个左部点为其提供 $\dfrac{1}{n}$ 的流量，最少也会有 $k$ 的流量，所以存在一个满足条件的分数流。

有了上下界，考虑二分答案，现在要解决的问题是如何判定 $D$ 天内是否可以满足题意。

因为每个人需要 $k$ 个奖，可以把每个人拆成 $k$ 个点，在这个 $D$ 个左部点，$nk$ 个右部点的二分图上跑最大匹配，若 $|M| = nk$，说明 $D$ 满足题意，问题是这样做太慢了，无法通过此题。考虑 Hall's 定理（这里我们从右部点出发思考问题），对于右部点的每个子集 $A \subset S$，需要满足 $|N(A)| \ge |A|$。看似有 $nk$ 个点，但其实对于每个人创建的 $k$ 个点，它们的陪集是一样的，所以每个人对应的 $k$ 个点要么都选，要么都不选，这样判定的结果与原来是相同的（你选了某个人对应的一些点和全选上相比，$|N(A)|$ 是不会变的，但全选上可以让 $|A|$ 更大）。因此实际有效的子集只有 $2^{n}$ 个。

对于第 $d$ 天，我们用 $f_d$ 来表示有哪些人在第 $d$ 天上班（采用二进制压缩表示）。如果 $L_d \in |N(A)|$，则必须满足 $d$ 和 $A$ 有交集，即 $d$ 和 $A$ 的二进制与不等于 $0$。问题转化为：对于每个 $A \in[0, {2^n - 1}]$，求出  $\sum\limits_{d = 1}^D [f_d \bigcup A \not= \varnothing]$，并对于每个 $A$ 判断这个式子与 $k|A|$ 的大小关系，考察其是否满足 Hall's 定理的条件。

$f_d \bigcup A \not= \varnothing$ 的个数不好求，但是可以反面考虑，求有多少个 $d$ 满足 $f_d \bigcup A = \varnothing$。假如我们 $\forall d \in [1,D],c_{f_d}$ 增加 $1$，再对 $c$ 数组求一个子集和（这部分如果不明白可以先学下 sosdp），那原式就转化成了判断是否满足 $\forall A,|D| - c_{S - A} \ge k|A|$ ，这可以通过枚举子集简单判断。

总复杂度 $O(\log(nk)(n^2k + n2^n))$，可以通过此题。



## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[20], ply[3600100], f[1000000];
bool check(int days){
    int S = (1 << n) - 1;
    for(int s = 0;s <= S;s++) f[s] = 0;
    for(int i = 1;i <= days;i++) f[ply[i]]++;
    for(int i = 0;i < n;i++) for(int s = 0;s <= S;s++)
        if(!(s >> i & 1)) f[s + (1 << i)] += f[s];
    for(int s = 0;s <= S;s++){
        int ned = __builtin_popcount(s) * k;
        int gt = days - f[S - s];
        if(gt < ned) return 0;
    } 
    return 1;
}
int main(){
    cin >> n >> k;
    int Mx = 2 * n * k;
    for(int i = 0;i < n;i++) cin >> a[i];
    for(int d = 1;d <= Mx;d++){
        for(int i = 0;i < n;i++){
            int rd = d % (2 * a[i]);
            if(rd == 0 || rd > a[i]) continue;
            ply[d] |= (1 << i);
        }
    }
    int L = n * k, R = Mx, res = Mx;
    while(L <= R){
        int Mid = (L + R) >> 1;
        if(check(Mid)) res = Mid, R = Mid - 1;
        else L = Mid + 1;
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：_Cheems (赞：1)

首先二分答案，暴力拆点跑二分图最大匹配，不行会超时，需要优化。

尝试使用 $\rm Hall$ 定理，暴力枚举人集合 $S$，现在的问题是怎么求与 $S$ 相连的奖牌集合大小。

注意到一个重要性质：我们依次给每个人颁奖，那么总天数为 $2nk$。这是答案上界，也就是说天数并不多。

这启示我们从奖牌出发考虑贡献，记 $P_i$ 表示可以获得第 $i$ 天的奖牌的人的集合，那么 $P_i$ 对 $S$ 有贡献，当且仅当 $P_i\cap S\ne \varnothing$。

但是这并不好计算，不妨换个角度，计算 $P_i\cap S=\varnothing$ 的数目，等价于 $P_i\in \bar{S}$。非常简洁优美，直接高维前缀和预处理即可。

注意二分前预处理 $P_i$ 避免超时。复杂度 $O(n2^n\log nk+n^2k)$。
#### 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

const int N = 25, M = 4e6 + 5, MX = 1 << 18;
int n, k, a[N], P[M], f[MX], ppc[MX]; 

inline bool check(int p){
	for(int i = 0; i < MX; ++i) f[i] = 0;
	for(int i = 1; i <= p; ++i)	++f[P[i]];
	for(int i = 0; i < n; ++i)
		for(int S = 0; S < 1 << n; ++S)
			if((S >> i) & 1) f[S] += f[S ^ (1 << i)];
	for(int S = 1; S < 1 << n; ++S){
		int res = p - f[((1 << n) - 1) ^ S];
		if(ppc[S] * k > res) return false;
	}
	return true;
}
signed main(){
	for(int i = 1; i < MX; ++i) ppc[i] = ppc[i ^ (i & -i)] + 1;
	cin >> n >> k;
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= 2 * n * k; ++i)
		for(int j = 0; j < n; ++j){
			int id = i % (2 * a[j]);
			if(id && id <= a[j]) P[i] |= (1 << j); 
		}
	int L = 0, R = 2 * n * k;
	while(L + 1 < R){
		int mid = L + R >> 1;
		if(check(mid)) R = mid;
		else L = mid;
	}
	cout << R; 
	return 0;
}
```

---

## 作者：xxxxxzy (赞：1)

[[ARC106E] Medals](https://www.luogu.com.cn/problem/AT_arc106_e)

题意:你有$n$ 个朋友，他们会来你家玩，第 $i$ 个人 $1...A_i$  天来玩，然后 $A_i+1...2A_i$  天不来，然后 $2A_i+1...3A_i$ 天又会来，以此类推

每天你会选一个来玩的人，给他颁个奖，如果没人来玩，你就不颁奖。你要给每个人都颁 $K$ 个奖，问至少需要多少天。

直接二分答案，转化成判定。

一个人拿 $k$ 次奖，拆成 $k$ 个人拿 $1$ 次奖，就成了一张二分图，但直接跑二分图匹配肯定炸飞。

考虑用 Hall 定理。

这个时候，发现答案最大为 $2nk$，因为一个一个人颁 $k$ 次奖，一个人天数不超过 $2k$，总天数不超过 $2nk$。

 $n$ 很小，所以可以把每天没来的人压成一个二进制数，处理出来每天哪些人来了哪些人没来，然后做高维前缀和求出每一种状态的子集缺少天数之和，然后用二分的值 $mid$ 减去这个数就是邻居集的大小了。然后就可以快乐地用 Hall 定理判断了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define drep(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define pii pair<int,int>
const int inf=1e9+5,N=2e5;
using namespace std;
int now,n,k,a[25],dp[3600005],f[400005],num[400005];
bool check(int mid){
	memset(f,0,sizeof(f));
	rep(i,1,mid) f[dp[i]]++;
	rep(i,0,n-1){
		drep(j,(1<<n)-1,0){
			if(!((j>>i)&1)) f[j]+=f[j^(1<<i)];
		}
	}
	rep(i,1,(1<<n)-1){
		if(mid-f[i]<num[i]*k) return 0;
	}
	return 1;
}
int ask(int l,int r){
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	rep(i,1,n) cin>>a[i];
	rep(i,1,2*n*k){
		dp[i]=now;
		rep(j,1,n){
			if(i%a[j]==0) now^=(1<<(j-1));
		}
	}
	rep(i,1,(1<<n)-1) num[i]=num[i&(i-1)]+1;
	cout<<ask(1,2*n*k);
}
```

---

## 作者：山田リョウ (赞：1)

显而易见天数不超过 $2NK$，所以应当是先二分答案再转为判断二分图是否存在完美匹配。

发现 $n$ 不大故考虑使用 Hall 定理，即每次判断是否对于每个人的集合 $S$ 以及存在这些人出席的天的集合 $T$ 均满足 $K|S|\geq |T|$。

考虑先预处理出每天有哪些人出席，这一步复杂度是 $O(N^2K)$ 的，然后我们每次 check 时关心的是有交的集合数量，容斥，转为计算无交集合数量，即补集的子集和，SOSDP 即可，算上二分总复杂度为 $O(N2^N\log K+N^2K)$，可过。

[code](https://atcoder.jp/contests/arc106/submissions/59502729)。

---

## 作者：Unnamed114514 (赞：0)

显然答案至多为 $2nk$，证明考虑从 $1$ 开始一个一个处理，然后第 $i$ 个只需要 $2k$ 天，因为如果 $a_i>k$ 只需要 $k$ 天，如果 $a_i\le k$ 的话考虑让工作日和休息日配对，这样一定不劣，容易发现 $k$ 对就正好是 $2k$ 天。

在拥有了一个较为清晰的上界后，可以考虑二分。

这是个非常显然的图论模型，把每个位置拆成 $k$ 个点后，容易发现问题变成了二分图匹配。

然后有一边的点必须匹配完，因此是判定完备匹配，因此考虑 Hall 定理。

注意到 $n$ 比较小，所以考虑 $O(2^n)$ 枚举哪些人，然后考虑另一边有多少个点和它们相连。

注意到直接考虑人也许并不好算，因此求出每一天哪些人可以。

然后发现仍然不是很好算，因为子集和超集都可以算到它头上。

考虑取补集，容易发现取补集后就只需要算超集和了，直接 SOS DP 即可。

---

## 作者：BreakPlus (赞：0)

一眼二分答案。关键在于怎么判断上。

想了想没有什么贪心的方法，而且这玩意有点像二分图匹配。试了一下可以建图跑网络流：

+ 由源点 $s$ 连向每一天，流量为 $1$；

+ 由每一天连向这一天来的所有人，流量为 $+\infty$；

+ 将每一个人拆点，两个点之间流量为 $K$，且后一个点连向汇点 $t$。

然后就是我不太会的特殊图网络流问题的一些技巧：

+ 可以强行将图变成二分图。具体地，将每一个人拆成 $K$ 个点，每次连边就将这 $K$ 个点都连一遍，然后跑 Hall 定理：枚举二分图右边的一个子集，看左边有多少个点能连进来。

+ 可以最大流转最小割。若合法则流量必须是 $nK$，即割掉右边全部的 $n$ 条流量为 $K$ 的边。枚举右边强制不割的部分，若通过左边能以更小的代价割掉则不合法。

两种做法都获得了一样的解答。高维前缀和维护即可。

```cpp
ll n,k,a[20],s[1000005];
ll f[(1<<18)+5];
bool check(ll mid){
    memset(f,0,sizeof(f));
    for(ll i=1;i<=mid;i++){
        f[s[i]]++;
    }
    for(ll i=0;i<n;i++){
        for(ll j=0;j<(1<<n);j++){
            if((j>>i)&1) {
                f[j] += f[j ^ (1<<i)];
            }
        }
    }
    for(ll i=0;i<(1<<n);i++){
        ll p1 = popcnt(i)*k;
        ll p2 = mid - f[(1<<n)-1-i];
        if(p2 < p1) return 0;
    }
    return 1;
}
void solve(){
    n=read(),k=read();
    for(ll i=1;i<=n;i++)a[i]=read();
    ll l=1, r=2*n*k, ans=0;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=r;j++){
            if((j-1)%(2*a[i])<a[i]) s[j]|=(1<<i-1);
        }
    }
    while(l<=r){
        ll mid=l+r>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    printf("%lld\n", ans);
}
```

---

## 作者：songhongyi (赞：0)

排除所有对于 $n$ 多项式的高妙做法。

但我们还是考虑一个网络流模型，先二分答案，然后构造一个网络。左部点表示人，右部点表示一天，每条边表示某个人某天在，要求最大流不少于 $kN$。

类比二分图匹配，考虑 Hall 定理，那么你需要的就是对于每个人的集合 $S$，邻域大小至少为 $k\cdot S$。

显然我们容易求出某一天那些人在，即对某个集合 $S$，有多少天邻域恰为这么多。而我们要求的相当于对于某个集合 $S$，求有多少天邻域为 $S$ 子集，SOS 即可。

我们仍需解决答案的上界，以便于二分答案和预处理。不难发现，任意 $2k$ 天，至少有 $k$ 天某个人会来，也就是说，我们最多 $2nk$ 天就可以完成。

总时间复杂度为 $O(n^2k+n2^n\log{nk}+k\log{nk})$。

---

## 作者：User_Unauthorized (赞：0)

## 题意

有一个商店和 $N$ 名员工，其中第 $i$ 名员工在第 $1 \sim A_i$ 天工作，在第 $A_i + 1 \sim 2 \times A_i$ 休息，接下来每 $A_i$ 天改变一次状态。

每一天你都可以选择**一名**来上班的员工并为其颁一个奖，求使得每名员工都获得至少 $K$ 个奖的最小天数。

- $1 \le N \le 18$
- $1 \le K \le 10^5$
- $1 \le A_i \le 10^5$

## 题解

首先考虑二分答案。

现在问题转化为了判定在制定天数内是否可以使得每名员工都获得至少 $K$ 个奖。

考虑转化为二分图模型，将员工视为左部点，天数视为右部点，那么判定成立当且仅当存在一个完美匹配使得每个员工都有 $K$ 条边。

将原图中的每个员工拆为 $K$ 个点，那么判定成立当且仅当对左部图存在一个完美匹配。

考虑应用 Hall 定理，发现对于一个员工拆出的 $K$ 个点，由于与其联通的右部点集合均相同，故对全部 $K$ 个点整体判定强于对部分点进行判定。因此需要判定的点集只有 $2^N$ 个。

考虑如何判定，问题转化为了对于每个点集，求出与其联通的右部点点集大小。

可以发现一个性质，即对于每个点集，与其相邻的右部点数量不少于全体右部点数量的一半。因此可以得出答案上界为 $2 \times N \times K$。因此我们只需要对 $\left[N \cdot K, 2 \times N \times K\right]$ 内的答案进行判定。

根据上述分析可以得出右部点数量是 $\mathcal{O}(NK)$ 级别的，所以我们从右部点的角度来考虑。同样可以发现，对于右部点，与其联通的左部点集合之后 $2^N$ 种，且可以进行预处理。

那么我们可以对于每个左部点集合 $S$，求有多少个右部点的联通集合与其有交，发现难于计算，转化为求有多少个个右部点的联通集合与其不交，发现其数量等于联通集合为 $S$ 的点集的补集的右部点数量。这个是便于处理的，使用高维前缀和即可。

因此我们可以通过对于所有可能的右部点，处理出与其联通的左部点集合，这可以在 $\mathcal{O}(N^2K)$ 的时间内完成。

接下来对于每次判定，对于每个点集 $S$，处理出恰好与这些左部点联通的右部点数量。接下来使用高维前缀和处理出对于每个点集 $S$，与左部点联通集合为其子集的右部点数量。最后枚举所有点集进行判定即可。这部分的复杂度为 $\mathcal{O}(NK + N2^N)$。

总复杂度为 $\mathcal{O}\left(N^2K + \log NK \left(NK + N2^N\right)\right)$，可以通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

valueType popcount(valueType n) {
    return __builtin_popcount(n);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, K;

    std::cin >> N >> K;

    ValueVector A(N);

    for (auto &iter : A)
        std::cin >> iter;

    valueType const V = 2 * N * K, S = 1 << N, FULL = S - 1;

    ValueVector type(V + 1, 0);

    for (valueType i = 1; i <= V; ++i) {
        for (valueType j = 0; j < N; ++j)
            if ((i - 1) / A[j] % 2 == 0)
                type[i] |= 1 << j;
    }

    auto check = [&](valueType lim) -> bool {
        ValueVector F(S, 0);

        for (valueType i = 1; i <= lim; ++i)
            ++F[type[i]];

        for (valueType i = 0; i < N; ++i)
            for (valueType j = 0; j < S; ++j)
                if (j & (1 << i))
                    F[j] += F[j ^ (1 << i)];

        for (valueType i = 0; i < S; ++i)
            if (lim - F[FULL ^ i] < popcount(i) * K)
                return false;

        return true;
    };

    valueType left = 1, right = V, ans = V;

    while (left <= right) {
        valueType const mid = (left + right) / 2;

        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else
            left = mid + 1;
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：lsj2009 (赞：0)

好题捏。

一个比较显然的观察是答案上界不超过 $2nk$，我们考虑对每个人按顺序发即可。

然后发现答案显然有单调性，故考虑二分答案。然后容易想到一个网络流模型：

- $\overset{k}{s\rightarrow i}$。
- $\overset{1}{i\rightarrow j}$。
- $\overset{1}{j\rightarrow t}$。

其中 $s,t$ 分别表示源点和汇点，$i$ 表示人，$j$ 表示天数，第二种边连边时需要保证在第 $j$ 时刻第 $i$ 个人在我家。但是这样子复杂度是 $\Theta(n^2k\sqrt{nk})$，显然跑不过去。

考虑 $\text{Hall}$ 定理：设 $S_u$ 表示与点 $u$ 有连边的点集，则一个二分图有完美匹配，当且仅当二分图其中一个点集的任意一个子集 $V$，满足 $|\bigcup_{u\in V} S_u|\ge |V|$。证明略，网上可自行搜索。

则我们考虑 $\Theta(n^2k)$ 预处理一下与第 $i$ 天有连边的点集，则在二分 ``check`` 时算一个 $f_S$ 表示有多少个时刻来的人是 $S$ 的子集，则 $S$ 向外连边的点数为 $x-f_{U-S}$，其中 $x$ 表示二分的值，$U$ 表示全集。也就是说，所有天数减掉与 $S$ 没有连边的天数。

然后 $f_S$ 直接算是 $\Theta(3^n)$ 的，可以用高维前缀和优化到 $\Theta(n\cdot 2^n)$。

最终复杂度 $\Theta(n^2k+(n\cdot2^n+nk)\log{nk})$。


```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=18,M=4e6+5,S=1<<18;
int g[M],f[S],a[N],m,s,n,k;
bool check(int x) {
    cl(f,0);
    rep(i,1,x)
        ++f[g[i]];
    rep(i,0,n-1) {
        rep(S,0,s) {
            if(!((S>>i)&1))
                f[S^(1<<i)]+=f[S];
        }
    }
    rep(i,0,s) {
        if(x-f[s-i]<__builtin_popcount(i)*k)
            return false;
    }
    return true;
}
signed main() {
    scanf("%d%d",&n,&k);
    rep(i,0,n-1)
        scanf("%d",&a[i]);
    m=2*n*k; s=(1<<n)-1;
    rep(i,1,m) {
        rep(j,0,n-1) {
            if(!(((i-1)/a[j])&1))
                g[i]|=1<<j;
        }
    }
    int l=1,r=m,ans=m;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid-1,ans=mid;
        else
            l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

