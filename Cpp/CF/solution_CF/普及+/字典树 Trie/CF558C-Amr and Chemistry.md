# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# 题解

## 作者：IkunTeddy (赞：4)

# 题目分析
将一个数乘 $2$ 等价于将这个数的二进制末尾补了一个 $0$。

将一个数除 $2$ 等价于将这个数的二进制末尾删掉。

这样就可以考虑按位拆分，按位操作我们自然而然就能够想到 01-Trie。接下来我们就是研究放入 01-Trie 的性质。

我们就举这个例子 `3 2 5`。我们就得到下面这颗树。表粗的节点表示这里有个数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/q1l1vjgb.png)

我们可以发现从一个数变到另一个数所用的次数，就是这颗树上**两个数的距离**。真的太神奇了。但是因为末尾只能补 $0$ 所以往下走时只能往左子树走。所以说我们要找到所有所有数字的 LCA 进行换根 dp。我们设 $dp[u]$ 为所有有数字的点走到 $u$ 的总距离，设 $cnt[u]$ 为 $u$ 子树内有数字的点的个数，设 $v$ 为 $u$ 的儿子，设 $n$ 为总数字个数。我们很轻松就能得到转移方程。

$dp[v]=dp[u]-cnt[v]+(n-cnt[v])$。我们轻松就能切了这道题了。芜湖！

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
int a[maxn];
int n;
int l;
struct node{
	int son[2];
	int cnt;
}tree[maxn];
int rt,cnt;
int node[maxn];
int dep[maxn];
void insert(int &v,int x,int p,int id,int d){
	if(!v)v=++cnt;
	dep[v]=d;
	tree[v].cnt++;
	if(!p){
		node[id]=v;
		return ;
	}
	int c=(x>>p-1)&1;
	insert(tree[v].son[c],x,p-1,id,d+1);
}
int dp[maxn];
int ans=0x3f3f3f3f;
void dfs(int u){
	ans=min(ans,dp[u]);
	for(int i=0;i<1;i++){
		int v=tree[u].son[i];
		if(!v)continue;
		dp[v]=dp[u]+n-2*tree[v].cnt;
		dfs(v);
	}
}
int get(int x){
	if(!x)return 0;
	return get(x>>1)+1;
}
int getrt(int v,int f){
	while(1){
		if(tree[v].cnt<n)return f;
		if(tree[v].son[0])f=v,v=tree[v].son[0];
		else f=v,v=tree[v].son[1];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		l=get(a[i]);
		insert(rt,a[i],l,i,0);
	}
	rt=getrt(rt,0);
	for(int i=1;i<=n;i++){
		dp[rt]+=dep[node[i]]-dep[rt];
	}
	dfs(rt);
	printf("%d\n",ans);
	
	return 0;
}


```

---

## 作者：KokiNiwa (赞：4)


有意思。
知识点：
1. 想到进制，反射出$0-1-Trie$
2. $Trie$要记住考虑一个字符串出现多次的情况！！！已经在这里栽了两回了。（上次好像是$loj$上的$key\ word\ search$，名字可能不对）

[Amr and Chemistry](https://codeforces.com/problemset/problem/558/C)

可能我要翻译一下题......

## 题意
给你$n$个数，你可以把一个数$a_i$变为$2a_i$或者$\lfloor \frac{a_i}{2}\rfloor$。求最小操作次数使得所有数变成一个数。$n\le10^5$

## 题解
### 方法1
不够精妙。
可以去[这里](https://www.luogu.org/blog/dennyqi/solution-cf558c)看具体解法。
### 方法2
把每个$a_i$化成$2$进制，再把这些二进制串插入到字典树中。假设每个数都在它的二进制串的末尾处。一次乘法等价于这个数走到它的父亲，一次除法等价于向做儿子走一步。问题变为选一个点，使所有点到它的距离最短。

这个点有限制，只能是从根节点出发，一直往左儿子走，得到的链上的点。因为每个点只能向左儿子走，不能向右儿子走。**那么根一定是$1$嘛？不一定是$1$！**。根应该是所有数的最近公祖先！！！

如何求这个点？把每个链上的点算一遍答案即可。先从根计算答案，随后从根开始换根，得出每个点的答案。

时间复杂度$O(nlog_2n)$，可以优化。

可以采取不建树，编号为$x$的儿子为$2x$与$2x+1$。复杂度做到$O(n)$。

```cpp
#include <cstdio>
#include <iostream>
#define reg register

using namespace std;

const int maxTot = 1e5 + 10;
int totN = 0, maxVal = 0;
int valA[maxTot] = {}, dis[maxTot] = {}, allDis[maxTot] = {}, sze[maxTot] = {}, mark[maxTot] = {};
void dfs(int now) {
	if (now > maxVal) return ;
	int lson = now << 1, rson = now << 1 | 1;
	dfs(lson), dfs(rson);
	sze[now] = mark[now];
	if (lson <= maxVal) sze[now] += sze[lson];
	if (rson <= maxVal) sze[now] += sze[rson];
	return ;
}

int main() {
	scanf("%d\n", &totN);
	for (reg int th = 1; th <= totN; ++th) {
		scanf("%d\n", &valA[th]);
		++mark[valA[th]];
		maxVal = max(maxVal, valA[th]);
	}
	dfs(1);
	int root = 0;
	for (reg int id = maxVal; id >= 1; --id)
		if (sze[id] == totN) { root = id; break; }
	dis[1] = 0;
	for (reg int zhi = 2; zhi <= maxVal; ++zhi)
		dis[zhi] = dis[zhi >> 1] + 1;
	for (reg int nodeI = 1; nodeI <= maxVal; ++nodeI)
		allDis[root] += (dis[nodeI] - dis[root]) * mark[nodeI];	//这里加的是距离，所以dis[1] = 0而非1.
	for (reg int id = root << 1; id <= maxVal; id = id << 1)
		allDis[id] = allDis[id >> 1] + (totN - sze[id]) - sze[id];
	int ans = 0x3f3f3f3f;
	for (reg int id = root; id <= maxVal; id = id << 1)
		ans = min(ans, allDis[id]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Marsrayd (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF558C)

## 题意简述

给定 $n$ 个数，一次操作可以将其中的一个数 $x$ 变为 $
x\times 2$ 或 $\lfloor \frac x 2\rfloor$ 

求让这 $n$ 个数都相等的最少操作次数。

## $\texttt{SOLUTION}$

首先考虑操作的本质：我们建立一棵 $i$ 号节点连向 $i\times 2$ 号节点和 $i\times 2+1$ 号节点的经典二叉树，并且只保留与所给的 $n$ 个数有关的树边，如下图（以[此样例](https://www.luogu.com.cn/paste/zp4bjib0)为例）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ly2tptqf.png)

操作就变为了可以让一个点向上走一步（走到他的父亲），或向左下走一步（走到他的左儿子）。

所求答案就变为了让所有的加粗节点（即表示给定数的节点）走到同一个点上所需的最少步数。

这个非常好求，$\text{换根 dp}$ 即可解决，需要 ```dfs``` 两遍。

```dfs1```：找到根节点（给出的 $n$ 个数中让其他所有数都可以通过往上走走到的数），遍历一遍，求出所有加粗节点（即为给出的 $n$ 个数所表示的点） 往上走到根节点的距离总和 $ans$，以及以任意节点 $u$ 为根子树中 $sz_u$ 加粗节点的个数。

```dfs2```：从根节点开始一直往左儿子（只能往左儿子走）走，计算出所有加粗节点到达沿途节点的步数和 $tmp$，让 $ans=\min(ans,tmp)$。如何计算呢，以上图中的情况从 $1$ 到 $2$ 为例：以 $2$ 为根的子树中的加粗节点都可以少往上走一步，其他加粗节点则要多往下走一步，所以 $tmp=ans-sz_2+(sz_1-sz_2)$。


$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>

const int N=200010;

inline int read()
{
	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int n,a[N],mx;
long long sz[N],ans;
void dfs1(int now)
{
	if(now>mx) return;
	dfs1(now<<1),dfs1(now<<1|1);
	sz[now]+=sz[now<<1]+sz[now<<1|1];
}//为了方便，直接把整棵树遍历了，没用的节点的sz均为0，不影响答案。
void dfs2(int now,long long lst)
{
	if(now>mx) return;
	long long tmp=lst+sz[1]-2*sz[now];
	ans=std::min(ans,tmp);
	dfs2(now<<1,tmp);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),mx=std::max(mx,a[i]);
		sz[a[i]]++;//加粗节点个数++
	}
	dfs1(1);
	int x=a[1];
	while(sz[x]^n) x>>=1;//找出根节点x
	for(int i=1;i<=n;i++) while(a[i]^x) a[i]>>=1,ans=ans+1;//ans也可以不需要通过dfs来计算，因为只要往上走所以直接这样就行了。
	dfs2(x<<1,ans);
	printf("%lld\n",ans);
	return 0;
}
```

欢迎提问or提出我的问题，会改的。

---

## 作者：Mr_Wu (赞：3)

### 前言

本做法由 Aiming_High 与 wenhao801 共同提出，~~我来代述~~，时间复杂度 $O(n+\max a_i)$。

### 题解

考虑一棵完全二叉树（$x$ 的左儿子是 $2x$，右儿子是 $2x+1$），则一次操作变为走到父亲或走到左儿子。

我们考虑枚举所有数最后走到哪个点，可以发现深度最浅的且可能最优的就是它们的 lca。

然后我们只向左儿子走（为什么不向右儿子走？因为左子树的儿子到不了），并换根 dp 记录答案。

举个例子：一开始图如下：（红为给定点，蓝为目标点）

![](https://cdn.luogu.com.cn/upload/image_hosting/5crj7q4w.png)

此时答案为 $dis(3,13)+dis(3,7)+dis(3,15)$

然后我们移动 3 到 6，

![](https://cdn.luogu.com.cn/upload/image_hosting/wc96vz9i.png)

此时 7,15 对答案的贡献 +1，13 对答案的贡献 -1，**因此每次换根更改如下：ans -= siz[x<<1], ans += N - siz[x<<1]** （这里 siz 为子树中红点数）

时间复杂度 $O(n + \max a_i)$。

### 代码

```cpp
#include <cstdio>
#include <climits>

typedef long long ll;
ll min(ll a, ll b) { return a < b ? a : b; }
const int MAXN = 200005;

int N, M = 100000, siz[MAXN], dep[MAXN], a[MAXN], root;
ll ans = LLONG_MAX >> 1, tans;
int vis[MAXN];

void dfs(int u)
{
	if (u > M) return;
	dep[u << 1] = dep[u << 1 | 1] = dep[u] + 1, dfs(u << 1), dfs(u << 1 | 1);
	siz[u] = siz[u << 1] + siz[u << 1 | 1] + vis[u];
}

int main()
{
	scanf("%d", &N); int i;
	for (i = 1; i <= N; ++i) scanf("%d", &a[i]), ++vis[a[i]];
	dfs(1);
	for (root = M; root >= 1; --root) if (siz[root] == N) break; // 找到一开始的根
	for (i = 1; i <= N; ++i) tans += dep[a[i]] - dep[root]; ans = min(ans, tans);
	while ((root << 1) <= M)
	{
		tans += -siz[root << 1] + (N - siz[root << 1]);
		root = root << 1;
		ans = min(ans, tans);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：DennyQi (赞：1)

非常有意思的一道题。

给出$n$个数$a_i$，每个数可以进行任意次`乘2`或`除2`（向下取整）的操作，问总共最少进行多少次操作能够让所有数相等。（$1 \leq n,a_i \leq 10^5$）

我们可以考虑维护出每一个数对应的所有变换状态，最后对所有数的变换状态求一个交集。枚举交集内的每个元素，一一带回去求最小值。

然而`一个数可以除完再乘`，也就是说一个数最多可以对应$\log^2 n$个状态。（每除一个2可以乘若干个2回来）。这样的话，如果我们再利用`set`来维护集合的话实现的复杂度就变成了$O(n \log^3 n)$，行不通。

考虑把$set$换成桶，最后交集中的元素就是被算到$n$次的。可是还有一个问题，这$log^2 n$个状态可能是会重复的，这样就会被计算多次。如何`避免重复`是个问题。

我们发现一个数如果最后一位是0那么除2乘2就会产生重复状态了，所以我们只对所有末尾为1的进行先除再乘的处理。

最后如何统计答案呢？我们假设$cnt_{i,j}$表示第$i$个数达到状态$j$需要几步。假设我们最终枚举到交集的元素为$k$，那答案就是$\sum\limits_{i=1}^ncnt_{i,k}$。这样我们就看出来了，其实不需要$cnt$数组，只需要在用桶记录的时候另外开一个类似桶的数组，累积步数就可以了。

于是$O(n \log^2 n)$解决了。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
using namespace std;
const int N = 100010;
const int P = 998244353;
const int INF = 0x3f3f3f3f;
inline int mul(const int& a, const int& b){ return 1ll*a*b%P; }
inline int add(const int& a, const int& b){ return (a+b>=P)?a+b-P:a+b; }
inline int sub(const int& a, const int& b){ return (a-b<0)?a-b+P:a-b; }
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,lim,ans,x,y,a[N],b[N],sum[N];
int main(){
	n = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		lim = max(lim,a[i]);
	}
	for(int i = 1; i <= n; ++i){
		x = a[i];
		int j = 0, k = 0, las = -1;
		while(x > 0){
			if(las == 0){
				++b[x];
				sum[x] += j;
				las = (x&1);
				x >>= 1;
				++j;
				continue;
			}
			y = x;
			k = 0;
			while(y <= lim){
				++b[y];
				sum[y] += j+k;				
				y <<= 1;
				++k;
			}
			las = (x&1);
			x >>= 1;
			++j;
		}
	}
	ans = INF;
	for(int i = 0; i <= lim; ++i){
		if(b[i] >= n){
			ans = min(ans, sum[i]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：jch123 (赞：0)

## 思路：

把操作放到二进制下看，就是往后面加一个 $0$ 或删除最后一位。

建一个二叉树，节点 $p$ 连向 $p\times2,p\times 2 +1$，将 $a_i$ 放到树上，两种操作变成往上走或往左走。转化成求一个根节点，使所有 $a_i$ 往上移动的步数之和最小。

建树时先记录每棵子树内有多少个 $a_i$，然后找到一个根节点后，开始换根，每次都往左走的同时更新答案。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int a[N],s[N];
int n,maxn,ans;
void build(int p)
{
	if(p>maxn) return;
	build(p*2),build(p*2+1);
	s[p]+=s[p*2]+s[p*2+1];
}
void dfs(int p,int res)
{
	if(p>maxn) return;
    //p下面的点少走一步，其他的点多走一步
	ans=min(ans,res-s[p]+s[1]-s[p]);
	dfs(p*2,res-s[p]+s[1]-s[p]);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i],s[a[i]]++;
		maxn=max(maxn,a[i]);
	}
	build(1);
	int rt=a[1];
	while(s[rt]!=n) rt/=2;
	for(int i=1;i<=n;i++)
	{
		while(a[i]!=rt) 
		{
			a[i]/=2;
			ans++;
		}
	}
	dfs(rt*2,ans);
	cout<<ans;
	return 0;
}
```

#

---

## 作者：汪汪队队长1 (赞：0)

我的思路是贪心，首先观察到操作是把一个数左移一位或右移一位，先把所有数按高位对齐，那么肯定是保留公共前缀最优，那就从高位到低位一位一位扫过去，如果这一位有 $1$ 也有 $0$ 那么肯定要把有 $1$ 的数删（右移）到这个 $1$ 被删掉，那么最后就是每个数都有公共前缀和后面的一串 $0$,那就是通过左移或右移让所有数位数相同。写成式子就是：

$$\sum\limits_{i=1}^{n}|l[i]-x|$$

$x$ 为最后统一的位数，$l[i]$ 为每个数的位数。

那么显然当 $x$ 取 $l[i]$ 中位数时最优，答案加上这部分就行了。

**AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=998244353;
int n,x,a[N][21],l[N],ans,mn=30;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		int t=0;
		while(x){
			a[i][++t]=x&1;
			x>>=1;
		}
		l[i]=t;
		mn=min(mn,t);
		for(int j=1;j*2<=t;j++)
			swap(a[i][j],a[i][t-j+1]);
	}
	for(int i=1;i<=20;i++){
		int f0=0,f1=0;
		for(int j=1;j<=n;j++)
			if(a[j][i])
				f1=1;
			else
				f0=1;
		if(f1&&f0)
			for(int j=1;j<=n;j++)
				if(a[j][i]){
					ans+=l[j]-i+1;
					for(int k=i;k<=l[j];k++)
						a[j][k]=0;
					l[j]=i-1;
				}
	}
	sort(l+1,l+1+n);
	for(int i=1;i<=n;i++)
		ans+=abs(l[i]-l[(n+1)/2]);
	cout<<ans;
	return 0;
}

```

---

## 作者：沉石鱼惊旋 (赞：0)

# 前言

本文是对 [DennyQi](https://www.luogu.com.cn/article/l942y6ye) 题解思想的补充做法。

# 题目翻译

$n$ 个数 $a_i$，每次可以选择 $a_i\gets a_i\times 2$ 或者 $a_i\gets \lfloor\frac{a_i}{2}\rfloor$。

问几次操作后 $a_i$ 全部一样。

$1\leq n\leq 10^5$，$1\leq a_i\leq 10^5$。

# 题目思路

考虑把这个操作对应到二进制上，那么就是删除一位和添加一个 $0$，其实就是位运算中的右移 $1$ 位和左移 $1$ 位。

你不会对这些数进行很多次移位，这样子不如每个数都少移动几位。因此最后这些数的二进制长度也就是 $\log_2 10^5$ 级别左右的，实现的时候可以取到 $18$ 防止一些不必要的判断。

每一个数最多移动 $\log$ 位就会变成 $0$，由于刚才说的，操作之后也是 $\log$ 级别，因此每右移一位都可以左移 $\log$ 位，一个数至多有 $\log^2$ 种可达状态。

但是状态有重复，考虑去重。本身复杂度已经是 $\mathcal O(n \log^2 V)$ 了，去重使用单次 $\mathcal O(\log n)$ 复杂度的数据结构可能过不去，我们需要设计一种单次 $\mathcal O(1)$ 得到重复状态中步数最小的。

那么我们考虑记录 $mn_i,lst_i$ 表示，我们上一次往答案里面扔的数，是 $a_{lst_i}$ 造成的，且对于所有的 $lst_j=lst_i$，他们最小扔进去的是 $mn_i$。

那么如果我们再往里面扔一个 $lst_j=lst_i$ 的方案，直接对于这个 $mn_i$ 判断要不要更新答案和 $mn_i$。如果扔进去的不是 $lst_i$ 造成的贡献，我们直接把 $lst_i,mn_i$ 等重构成目前的信息即可。

说这么多，其实本质就是记录上次修改是不是自己造成的，如果是自己造成的就把修改的数取最优。

实现的时候还要记录每个状态被不同的数贡献了几次，只有恰好贡献 $n$ 次才可能让所有数都变成它。

# 完整代码

[CF submission 273070746](https://codeforces.com/contest/558/submission/273070746)

复杂度 $\mathcal O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
const int LOG = 18;
int n;
int cnt[1 << 20];
int tot[1 << 20];
int lst[1 << 20];
int mn[1 << 20];
int ans = 1e9;
void add(int x, int y, int z) // cnt[y] += x id = z
{
    if (lst[y] == z)
    {
        cnt[y] -= mn[y];
        chkmn(mn[y], x);
        cnt[y] += mn[y];
    }
    else
        mn[y] = x, lst[y] = z, cnt[y] += x, tot[y]++;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        for (int j = 0; j <= LOG; j++)
        {
            int y = x;
            int tmp = 0;
            for (int k = 1; k <= j; k++)
                y >>= 1, tmp++;
            add(tmp, y, i);
            for (int k = 1; k <= LOG && (y << 1) < (1 << 20); k++)
                y <<= 1, tmp++, add(tmp, y, i);
        }
    }
    for (int i = 0; i < 1 << 20; i++)
    {
        if (tot[i] == n)
            chkmn(ans, cnt[i]);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：KυρωVixen (赞：0)

## 题意：
给你一个长 $n$ 的数列 $a$，你可以进行任意次如下操作：

1. 指定 $i$，$a_i \gets 2a_i$。
2. 指定 $i$，$a_i \gets \lfloor \dfrac{a_i}{2} \rfloor$。

求让 $a_1=\ldots=a_n$ 所需要的最少操作数。
## 题解：
提供贪心做法。

我们先将所有数用二进制意义下表示，然后不难发现：

操作 $1$ 相当于末尾补 $0$，操作 $2$ 相当于末尾移除一位。

如果我们要让所有数相等，那么对于单独数一定要先移除末尾若干位，再补若干个 $0$。（这里的“若干”指的是非负。）

先考虑一下，如果只允许操作 $2$ 我们该怎么让所有数相等。有一个显然的结论，令 $ld$ 为一开始所有数二进制串表示下的 LCP（最长公共前缀），对每个数 $a_i$ 进行操作 $2$ 直到 $a_i=ld$ 即可。

有些人认为这可能就是正解了，但是样例 $1$ 就能卡掉这种 naive 的做法，手玩一下可知，答案会大 $1$。

我们将操作 $1$ 引入这个做法作为优化：此时最后的数不一定是 $ld$，还可能是 $ld$ 末尾补上若干个 $0$。所以对于这样的一个数：

![](https://cdn.luogu.com.cn/upload/image_hosting/qxphwmon.png)

贸然将中间 $0000$ 的部分提前删掉可能不优。

所以最终做法就出来了：

先预处理出 $ld$，然后对每个数应用操作 $2$ 直到其为 $ld$ 后接非负个 $0$ 为止。先把这部分的贡献加到答案里。

然后枚举最终相同的数是 $ld$ 后接几个 $0$，再对每个数进行调整（补 $0$ 或去 $0$）。

设 $a_i$ 经过先前预处理末尾比 $ld$ 多出 $cnt_i$ 个 $0$，调整部分的贡献是：

$$ \min_{len=0}^{\lfloor \log \max a \rfloor} |cnt_i-len|$$

最后对两者求和即可。

对于调整部分式子的正确性，我们邀请读者自己在纸上画图来理解。

设 $\max a=V$，则时间复杂度为 $O(n\log^2 V)$，与官方题解没有区别。

## 代码：

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define sc second
#define endl '\n'
//#define int long long
using namespace std;
typedef long long ll;
typedef __int128_t lll;
typedef pair<int,int> pii;
const int N=1e5+5,M=18;
int n,a[N],qz;
int len(int x){
    int res=0;
    while(x){
        res++; x>>=1;
    }
    return res;
}
bool mtch(int x,int y){
    while(y){
        if(x==y) return 1;
        y>>=1;
    }
    return 0;
}
bool mtch_q(int y){
    int x=qz;
    if(x==y) return 1;
    while(x<y){
        x<<=1;
        if(x==y) return 1;
    }
    return 0;
}
int mw0(int x,int cnt0){
    int tmp=0;
    while(!mtch_q(x)) x/=2,tmp++;
    return tmp+abs(cnt0-(len(x/qz)-1));
}
int ans=INF;
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n; rep(i,1,n) cin>>a[i];
    sort(a+1,a+n+1); qz=a[1];
    while(qz){
        bool flag=1;
        rep(i,1,n) if(!mtch(qz,a[i])) flag=0;
        if(flag) break;
        qz>>=1;
    }
    int tmpans=0;
    rep(i,0,M-1){
        tmpans=0;
        rep(j,1,n) tmpans+=mw0(a[j],i);
        ans=min(ans,tmpans);
    }
    cout<<ans<<endl;
}
```

---

