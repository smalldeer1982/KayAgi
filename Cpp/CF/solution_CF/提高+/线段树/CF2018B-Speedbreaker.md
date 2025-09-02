# Speedbreaker

## 题目描述

[Djjaner - Speedbreaker](https://soundcloud.com/luciano-ferrari-151560131/speedbreaker)

⠀



There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.

- At time $ 1 $ , you conquer exactly one city, called the starting city.
- At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.

You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

## 说明/提示

In the first test case, cities $ 2 $ , $ 3 $ , and $ 4 $ are good starting cities.

In the second test case, there are no good starting cities.

In the third test case, the only good starting city is city $ 5 $ .

## 样例 #1

### 输入

```
3
6
6 3 3 3 5 5
6
5 6 4 1 4 5
9
8 6 4 2 1 3 5 7 9```

### 输出

```
3
0
1```

# 题解

## 作者：strcmp (赞：13)

**策略 $\text{X}$**：按 $a_i$ 排序，每次选择 $a_i$ 最小的并向它扩展。（CSP-S2023 种树）

这个策略一定是正确的，证明可以考虑交换论证。

解一定是一段区间。

证明：

假设 $x < y < z$ 且 $x,\,z$ 满足条件而 $y$ 不满足条件。不妨设 $u$ 是那个 $y$ 走不到的点。若 $u < y$ 则等到 $z$ 扩展到 $y$ 的时候显然走不到 $u$ 了，否则 $x$ 走不到 $u$。

知道它是一段区间之后已经可以利用策略 $\text{X}$，配合二分端点做完了。

但是这样比较没有水平。

接下来我们给出断言：如果有解，则答案就是 $[i - a_i + 1,\,i + a_i - 1]$ 区间的交。

必要性显然，充分性考虑对其施策略 $\text{X}$，失效当且仅当对于 $a_i$ 相同的点它们的最远距离大于 $a_i$ 了。（这种情况显然无解）

于是无解的情况和答案就讨论好了。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 5e5 + 10, mod = 1e9 + 7;
int T, n; vector<int> e[maxn];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); int l = 1, r = n, L = n + 1, R = 0, fg = 1;
		for (int i = 1, x; i <= n; i++) scanf("%d", &x), l = max(l, i - x + 1), r = min(r, i + x - 1), e[x].pb(i);
		for (int i = 1; i <= n; i++) {
			for (int x : e[i]) L = min(L, x), R = max(R, x); e[i].clear();
			if (R - L + 1 > i) fg = 0;
		}
		if (fg && l <= r) printf("%d\n", r - l + 1);
		else puts("0");
	}
	return 0;
}
```

---

## 作者：PNNNN (赞：7)

介绍一种另解，以下称“征服”为“拓展”。

对于这些需要拓展，且拓展的时间有上界的题，我们通常都会有一个 trick。那就是对于一个点 $x$，用它可以拓展到的点 $y$ 的时间上界把 $x$ 的时间上界继续缩小。用到这种 trick 的题有 [P9755 [CSP-S 2023] 种树](https://www.luogu.com.cn/problem/P9755)、[[ABC304Ex] Constrained Topological Sort](https://www.luogu.com.cn/problem/AT_abc304_h)，以及本题。

关于这个 trick 在本题的具体体现，不妨设 $t_i$ 为点 $i$ 被拓展到的时间，$a_i$ 为点 $i$ 被拓展时间的上界。定义 $L_i$ 为从点 $i$ 拓展到点 $1$，满足 $\forall i\in[1,i],t_i\leq a_i$ 的最大的 $t_i$。则 $L_i$ 的转移式为：
$$L_i=\begin{cases}a_i&i=1\\\min(L_{i-1}-1,a_i)&i>1\end{cases}$$
这是因为从 $i$ 拓展到 $i-1$ 需要 $1$ 的时间，且也要满足 $t_i\leq a_i$。

同理，定义 $R_i$ 为从点 $i$ 拓展到点 $n$，满足 $\forall i\in[i,n],t_i\leq a_i$ 的最大的 $t_i$。则：
$$R_i=\begin{cases}a_i&i=n\\\min(R_{i+1}-1,a_i)&i<n\end{cases}$$

容易发现 $L_i$ 是单调递减的，$R_i$ 是单调递增的。

求出 $L_i$ 和 $R_i$ 有什么用呢？考虑当前枚举了一个起始点 $P$。对于除了 $P$ 外的所有点，设其权值为 
$$val_i=\begin{cases}L_i&i<P\\R_i&i>P\end{cases}$$
贪心的想，要想满足每个点的时间上界，我们可以优先拓展那些 $val$ 值小的点。

那这样思路就很明显了，就像 dijkstra 一样，每次把当前可以拓展的点扔进一个小根堆里，按 $val_i$ 排序，每次从堆顶取出一个点就相当于拓展了这个点，并把时间计数器 $cnt+1$，接着再把这个点可以拓展到且还未被拓展的点扔进堆里。

判无解就是判当一个点被从堆顶取出时，当前的时间计数器是否满足 $cnt\leq val_i$，如果不满足，则说明点 $P$ 不能作为起始点。

[代码](https://codeforces.com/contest/2019/submission/283483682)

但这样做是 $O(n^2\times \log n)$ 的，考虑如何优化。

容易发现，对于一个起始点 $P$，
$$t_i=\begin{cases}P-i+1+\sum\limits_{j=P+1}^{n}[R_j\le L_i]&i<P\\i-P+1+\sum\limits_{j=1}^{P-1}[L_j\le R_i]&i>P\end{cases}$$

这是为什么？考虑 $i<P$ 的情况。对于求和前面的前面那一部分，如果想要拓展到 $i$，则需先将 $[i+1,P+1]$ 的点扩展，因为开始在 $P$ 时间就为 $1$，所以要加 $1$。对于求和的部分，则表示在点 $P$ 右边的需要比 $i$ 先拓展的点的个数，因为 $R_i$ 单调递增的性质，可以发现这些点为以 $P+1$ 为开头的一段前缀，正确性显然。$R_i$ 同理。

但是若是有 $i<P,j>P,L_i=R_j$ 的情况呢？这样的情况放在暴力代码中，$val_i$ 是等于 $val_j$ 的，且它们一定是先拓展一个，再拓展另一个。也就是说，$t_i+1=t_j$ 或者 $t_j+1=t_i$，判断是否可行则是看 $\max(t_i,t_j)$ 是否小于 $val_i$。而在上面的式子中，$t_i$ 和 $t_j$ 都会是 $\max(t_i,t_j)$，而这对可行判断是没有影响的。

有了这个式子，我们如何快速判断可不可行？我们可以将 $val_i$ 减去 $t_i$。若是不可行，则 $\min\limits_{i=1\land i\ne P}^{n}\{val_i-t_i\}<0$，其实就是看存不存在 $t_i>val_i$。

然后用数据结构维护就行了，我这里用了两棵平衡树，一颗维护 $i<P$ 的点，以 $L_i$ 为排序关键字，一颗维护 $i>P$ 的点，以 $R_i$ 为排序关键字，其实就是 $val_i$。设其为 $T_0$，$T_1$。

平衡树的一个节点 $i$ 需要维护它的排序关键字 $val_i$，$val_i-t_i$ 的值，它所在子树的 $\min\limits_{j\in subtree_i} \{val_j-t_j\}$。且平衡树还要支持区间加减。设 $sum_i=val_i-t_i$，$minn_i=\min\limits_{j\in subtree_i} \{val_j-t_j\}$。

枚举 $P$ 时，每次 $P\leftarrow P+1$ 时，将 $P+1$ 从 $T_1$ 中删除，并将 $P$ 加入 $T_0$，同时将 $T_1$ 整棵树的 $sum$ 减 $1$，$T_0$ 整棵树的 $sum$ 加 $1$。还要将 $P+1$ 在 $T_1$ 时对 $T_0$ 的贡献抹去，$P$ 在 $T_0$ 时对 $T_1$ 的贡献加上，具体表现为将 $T_0$ 中 $val$ 大于等于 $R_{P+1}$ 的节点的 $sum$ 加 $1$，$T_1$ 中 $val$ 大于等于 $L_{P}$ 的节点的 $sum$ 减 $1$。最后一边修改一边更新 $minn$。

如此，$P$ 可以成为一个起始点当且仅当此时 $T_0$ 整棵平衡树的 $minn$ 大于等于 $0$，$T_1$ 整棵平衡树的 $minn$ 也大于等于 $0$。

时间复杂度为 $O(n\times \log n)$。

[代码](https://codeforces.com/contest/2019/submission/283402639)

---

## 作者：菲斯斯夫斯基 (赞：5)

其它题解似乎都用到了类似于 [[CSP-S 2023] 种树](/problem/P9755) 的 trick，但是我没想起来。于是用了另一种贪心思路，但是需要线段树来进行维护。

题目的本质就是维护一个区间，然后将区间往左或往右拓展，然后到达每个点的时间有限制。

不难想到枚举一个 $i$，判断这个点是否能为起点。

首先如果 $x+1<i$，那么 $x+1$ 这个点一定比 $x$ 点更先到达，那么我们可以令 $a_{x+1} \gets \min\{a_{x+1},a_x-1\}$。同理，大于 $i$ 的情况也可以处理出来。

接下来考虑什么时候 $i$ 可以作为起点。每个点最晚到达的时间刚才已经预处理完了，那么可以进行贪心。设这个点最晚 $a_x$ 要到达，我们另开一个数组 $f$，每次令 $f_{a_x}\gets f_{a_x}+1$，那么若有某一时刻 $f$ 有一位置的前缀和小于 $0$，则说明这个位置不能为起点。证明是显然的。

直接做的话是 $\mathcal O(n^2)$ 的，用线段树可以做到 $\mathcal O(n\log n)$。

实现的时候可以把 $f_i$ 给赋值为 $i$，每次修改区间 $[a_x,n]$，维护全局最小值即可。

注意 $a_x\le0$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n;
int a[N],l[N],r[N];
struct ccf
{
	int mi,la;
}f[N<<2];
void pushdown(int k)
{
	int &x=f[k].la,l=k*2,r=k*2+1;
	f[l].mi+=x,f[l].la+=x;
	f[r].mi+=x,f[r].la+=x;
	x=0;
}
void build(int k,int l,int r)
{
	if(l==r)return f[k]={l,0},void();
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	f[k].mi=min(f[k*2].mi,f[k*2+1].mi);
}
void add(int k,int l,int r,int x,int y,int z)
{
	if(l>y||r<x)return ;
	if(x<=l&&r<=y)return f[k].mi+=z,f[k].la+=z,void();
	pushdown(k);
	int mid=(l+r)/2;
	add(k*2,l,mid,x,y,z);
	add(k*2+1,mid+1,r,x,y,z);
	f[k].mi=min(f[k*2].mi,f[k*2+1].mi);
}
int main()
{
	cin>>t;
	while(t--)
	{
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],l[i]=r[i]=a[i];
		build(1,1,n);
		for(int i=2;i<=n;i++)
			l[i]=min(l[i],l[i-1]-1);
		for(int i=n-1;i>=1;i--)
			r[i]=min(r[i],r[i+1]-1);
		for(int i=1;i<=n;i++)
			if(r[i]>0)add(1,1,n,r[i],n,-1);
		for(int i=1;i<=n;i++)
		{
			if(l[i]<=0)break;
			add(1,1,n,l[i],n,-1);
			if(r[i]<=0)continue;
			add(1,1,n,r[i],n,1);
			ans+=f[1].mi>=0;
		}
		for(int i=1;i<=(n<<2);i++)
			f[i]={0,0};
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：4)

无法理解为什么 *1900 能评蓝，而且就是个简单推式子题。

首先发现对于一个位置 $i$，如果存在一个位置 $j$ 使得 $a_j < |j - i| + 1$，那么点 $i$ 显然不行，这个十分好维护就不说了。

还有一种情况使点 $i$ 不合法，如果我们能够找到一组 $j$ $k$ 其中 $j < i$ $k > i$，满足 $k - j + 1 > \max (a_j,a_k)$，则点 $i$ 也不合法。

考虑如何维护这个式子，我们发现如果点 $i$ 不合法，那么 $(j,k)$ 中的任何一个位置都不合法，即不合法的点是连续的，于是考虑二分。

枚举左端点 $j$，我们需要找到最远的 $k$ 使得 $k - j + 1 > \max (a_j,a_k)$，$\max$ 不好维护，考虑拆成 $k-j+1>a_j$ 并且 $k-j+1>a_k$。对于第一个式子，发现 $k > a_j + j - 1$；对于第二个式子，变换一下可得 $j-1<k-a_k$，对于每个点算出 $i-a_i$，预处理出后缀最大值即可维护。

时间复杂度 $O(n\log n)$。

---

## 作者：Iniaugoty (赞：4)

### [CF2018B Speedbreaker](https://codeforces.com/contest/2018/problem/B)

这不是种树吗。

类似种树的思路，先满足较小的 $a _ i$ 的限制，就是先走向较小的 $a _ i$，一定是不劣的。

设 $f _ i$ 表示从 $i$ 出发能满足多少个限制。答案即为 $f _ i = n$ 的数量。

不妨反过来，对于每个 $i$，考虑从哪些 $j$ 开始走的时候能满足 $i$ 的限制。

首先对 $f _ i$ 自身加 $1$。

找到满足 $a _ j \le a _ i$ 的第一个和最后一个 $j$，记为 $l, r$。这里不等号取等的原因是，相等的 $a$ 先走哪个都一样的（如果没有更小的 $a$ 在后面影响的话）。

对于 $j < l$，先向右走就是最优的，需要 $i - j + 1$ 步走到 $i$。能满足 $i$ 的限制则意味着 $i - j + 1 \le a _ i$，即 $j \ge i - a _ i + 1$，对 $f$ 的 $[\max(i - a _ i + 1, 1), l - 1]$ 区间加 $1$。

对于 $j > r$ 类似。

对于 $l \le j < i$，若 $a _ l \le a _ r$，会先向左走到 $l$ 然后拐个弯再向右走，需要 $i - l + 1$ 步走到 $i$，于是当 $i - l + 1 \le a _ i$ 时对 $[l, i - 1]$ 区间加 $1$；否则，直接向右走，类似地对 $[\max(i - a _ i + 1, l), i - 1]$ 区间加 $1$。

对于 $i < j \le r$ 类似。

离线区间加，差分维护。时间复杂度 $O(n)$。

[code](https://codeforces.com/contest/2019/submission/283218259)。从出思路到写代码都挺快的啊，怎么当时都没几个人过。

（PS：根据本文的分析间接得到了一些题解的所谓“答案的区间一定在 $[i - a _ i + 1, i + a _ i - 1]$”）

---

## 作者：Linge_Zzzz (赞：3)

首先，如果我们可以自由选择起点，有一个经典的贪心策略是：

> 将所有 $a_i$ 升序排序，按顺序依次攻占这些城市，如果两个 $a_i$ 相同，那么先攻占哪个对于答案没有影响。

正确性显然。现在我们模拟一遍这个过程，如果这个过程能够满足条件，那么答案至少为 $1$，否则答案为 $0$，以下假设答案至少为 $1$。

我们按阶段划分攻占的过程。记 $[L_k,R_k]$ 为攻占所有 $a_i\leq k$ 的城市后所占领的区间。

容易发现，所有的在 $[L_1,R_1]$ 之间的起点，都能满足条件。

现在我们考虑对于起点不属于 $[L_1,R_1]$，怎么把它转化到起点属于 $[L_1,R_1]$ 的情况。

首先，假设要求解的起点为 $s$，那么一定满足 $s\in[L_{a_s},R_{a_s}]$ 且 $i\notin [L_{a_s-1},R_{a_s-1}]$。

假设 $s<L_{a_s-1}$，且从 $s$ 出发能满足条件，那么在从 $[L_{a_s-1},R_{a_s-1}]$ 向 $[L_{a_s},R_{a_s}]$ 转移时，一定存在一个时刻使得 $[s,R_{a_s-1}]$ 在规定时间内被占领，而且只要这个区间能在规定时间内占领，那么他就相当于是“从最小值开始占领的过程”中的一部分，也就等价于从最小值出发。

所以我们只需要从 $s$ 一口气走到 $R_{a_s-1}$ 并判断能否在规定时间内走到，即满足：$\forall i\in[s,R_{a_s-1}],i-s+1\leq a_i$。移项得到 $i-a_i+1\leq s$，ST 表维护 $i-a_i+1$ 的最大值即可。

对于 $s>R_{a_s-1}$ 的部分讨论一下，同理维护即可。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=2e5+10,T=20,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,a[N];
pii p[N];
int L[N],R[N];
int stx[T][N],stm[T][N];
void init(){
	for(int i=1;i<=n;i++)stx[0][i]=i-a[i]+1;
	for(int j=1;j<T;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			stx[j][i]=max(stx[j-1][i],stx[j-1][i+(1<<j-1)]);
		}
	}
	for(int i=1;i<=n;i++)stm[0][i]=a[i]+i-1;
	for(int j=1;j<T;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			stm[j][i]=min(stm[j-1][i],stm[j-1][i+(1<<j-1)]);
		}
	}
}
int qmax(int l,int r){
	int len=__lg(r-l+1);
	return max(stx[len][l],stx[len][r-(1<<len)+1]);
}
int qmin(int l,int r){
	int len=__lg(r-l+1);
	return min(stm[len][l],stm[len][r-(1<<len)+1]);
}
void solve(){
	cin>>n;
	fill(L,L+n+10,INF);
	fill(R,R+n+10,0);
	for(int i=0;i<T;i++)fill(stx[i],stx[i]+n+10,0);
	for(int i=0;i<T;i++)fill(stm[i],stm[i]+n+10,INF);
	for(int i=1;i<=n;i++){
		int t;cin>>t;
		a[i]=t;
		p[i].fi=t,p[i].se=i;
		L[t]=min(L[t],i);
		R[t]=max(R[t],i);
	}
	init();
	sort(p+1,p+1+n);
	int pl=p[1].se,pr=p[1].se,tim=1;
	for(int i=2;i<=n;i++){
		if(pl<=p[i].se&&p[i].se<=pr)continue;
		if(p[i].se<pl){
			tim+=pl-p[i].se;
			pl=p[i].se;
		}
		if(p[i].se>pr){
			tim+=p[i].se-pr;
			pr=p[i].se;
		}
		if(p[i].fi<tim){
			cout<<0<<'\n';
			return;
		}
	}
	for(int i=1;i<=n;i++){
		L[i]=min(L[i],L[i-1]);
		R[i]=max(R[i],R[i-1]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int l=1,r=n;
		while(l<r){
			int m=(l+r)>>1;
			if(L[m]<=i&&i<=R[m])r=m;
			else l=m+1;
		}
		if(l==p[1].fi)ans++;
		else{
			l--;
			if(i<L[l])ans+=i>=qmax(L[l],R[l]);
			if(i>R[l])ans+=i<=qmin(L[l],R[l]);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

题意：初始区间为 $[i,i]$，时间为 $1$，每次可以将区间 $[l,r]$ 扩展为 $[l-1,r]$ 或 $[l,r+1]$，当 $j\in[1,n]$，都有扩展到 $j$ 时的时间 $\le a_j$，则称 $i$ 合法。求 $1\sim n$ 的合法数。

贪心地想，每次肯定是往还没被扩展到且 $a_i$ 最小的点进行扩展，这样一定不劣，因为若先去尝试拓展其他较大的 $a_i$ 而导致这个点没有及时地更新到那就直接不合法了。

结论：若有解则答案必定为 $(i-a_i,i+a_i)$ 的交集。

证明？首先不在交集内的点一定会存在至少一个城市无法到达。假设交集为 $[l,r]$，那么 $\forall i\in[1,n],a_i\ge\max(i-l+1,r-i+1)$（由交集定义推出），也就是说从 $[l,r]$ 中任意点开始都是可以走完所有城市的。

判断无解的条件为 $\exist t\in[1,n],\displaystyle\max_{a_i\le t} i-\min_{a_i\le t} i\ge t$。怎么理解？对于所有时间不超过 $t$ 的城市最坏情况就是卡点扩展完成，这个过程中一共就只能扩展 $t$ 次，如果最大间隔是比 $t$ 大的那一定扩展不完。

# Code

```cpp
#include<bits/stdc++.h>
int l[200005],r[200005];
int T,n,L,R,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		L=0;R=n+1;
		for(int i=1;i<=n;++i)l[i]=0xfffff,r[i]=0;
		for(int i=1,x;i<=n;++i){
			scanf("%d",&x);
			L=std::max(L,std::max(1,i-x+1));
			R=std::min(R,std::min(i+x-1,n));
			if(l[x]==0xfffff)l[x]=i;r[x]=i;
		}
		for(int i=2;i<=n;++i)
			l[i]=std::min(l[i],l[i-1]),r[i]=std::max(r[i],r[i-1]);
		ans=0;
		for(int i=1;i<=n;++i)
			if(l[i]&&r[i]-l[i]+1>i)ans=-1,i=n;
		if(~ans)ans=R-L+1;
		if(ans<0)ans=0; 
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

B>C

先把无解特判掉：对于每个时间 $t$ 如果 $a_i\le t$ 的最左到最右的距离超过了 $t$ 那么无解。

有两种显然正确的策略：

- 一直往左走，直到必须往右走

- 一直往右走，直到必须往左走

在这种策略下，$i$ 时刻到达区间相等的点是等价的。

因此可以发现答案是连续的，否则反证设存在 ans X ans(中间的 X 表示不是答案) 的情况。

因为 X 右边有 ans，所以可以往右扩展，同理可以往左边扩展，所以 X 是可行的，因此可行的区间连续。

注意到对于 $i$，可行点是在 $[i-a_i+1,a_i+i-1]$ 中的，取交即可。

设得到的区间是 $[l,r]$，那么 $l$ 是第一次往右拐的，$r$ 是第一次往左拐的。如果 $l$ 不行的话，那么右边的点到 $l$ 之后也不行，然后 $l$ 左边的就算一直往右右边也有不行的点，$r$ 同理，那么在 $l,r$ 都行的情况下答案就是 $r-l+1$。

---

