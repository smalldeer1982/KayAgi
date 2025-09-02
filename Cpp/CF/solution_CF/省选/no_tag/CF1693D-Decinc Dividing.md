# Decinc Dividing

## 题目描述

定义一个序列 $a$ 是好的，仅当可以通过删除 $a$ 的一个单调递减子序列（可以为空）使得 $a$ 单调递增。  
给定一个 $1\sim n$ 的排列 $p$，你需要求出 $p$ 有多少子段是好的。

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
6
4 5 2 6 1 3```

### 输出

```
19```

## 样例 #3

### 输入

```
10
7 10 1 8 3 9 2 4 6 5```

### 输出

```
39```

# 题解

## 作者：Chen_jr (赞：37)

一个有神奇性质的 $ DP $ 题

考虑如何

首先给出一个很别扭的定义

 $ \mathit{dp_{i,0}} $  为第 $ i $ 个元素在 **递增** 序列中时， **递减** 序列最后一个元素的 **最大值** 

 $ \mathit{dp_{i,1}} $  为第 $ i $ 个元素在 **递减** 序列中时， **递増** 序列最后一个元素的 **最小值** 

初始时候所有 $ \mathit{dp_{i,0}}=- \infty $   $ \mathit{dp_{i,1}}= \infty $ 

 $ \mathit{dp_{1,0}}= \infty $  $ \mathit{dp_{1,1}}= - \infty $ 

怎么转移？

枚举第 $ (i-1) $ 个元素是在递增序列还是递减序列，然后尝试更新 $ \mathit{dp_{i,1,0}} $ ，~~其实就是分类讨论~~

只要 $ \mathit{dp_{n,0}} \neq - \infty $ 或者 $ \mathit{dp_{n,1}} \neq \infty $ 那么就存在合法方案

```cpp
bool check(int l,int r){
    for(int i=l;i<=r;++i)dp[i][0]=-inf;dp[l][0]=inf;
    for(int i=l;i<=r;++i)dp[i][1]=inf;dp[l][1]=-inf;
    for(int i=l;i<=r;++i){
        if(dp[i-1][0]!=-inf){//a[i-1]能在递增末尾
            if(a[i]>a[i-1])dp[i][0]=max(dp[i][0],dp[i-1][0]);//a[i]接在递增末尾
            if(a[i]<dp[i-1][0])dp[i][1]=min(dp[i][1],a[i-1]);//a[i]接在递减末尾
        }
        if(dp[i-1][1]!=inf){//a[i-1]能在递减末尾
            if(a[i]<a[i-1])dp[i][1]=min(dp[i][1],dp[i-1][1]);//a[i]接在递减末尾
            if(a[i]>dp[i-1][1])dp[i][0]=max(dp[i][0],a[i-1]);//a[i]接在递增末尾
        }
    }
    if(dp[r][0]!=-inf||dp[r][1]!=inf)return true;
    return false;
}
```

这个时候我们有了 $ n^3 $ 做法：枚举所有区间然后判断


然后考虑如何优化这个东西

如果我们枚举区间左端点，尝试扩展到最远的右端点，然后统计答案是能写到 $ n^2 $ 的

进一步，我们从大到小枚举左端点

考虑在更新过程中

要么在有限次操作内新的 $ \mathit{dp_{k,1,0}} $ 将与原来的相同，这时再往后将与原来完全一致，可以直接使用上次记录的最远点

要么在某个位置发现无法更新下去了，这个时候更新最远点即可

这貌似只是个常数优化？不，其实我们可以证明对于任意一个 $ f_{i} $ ，它最多被更新 $ 7 $ 次，所以这样就能切掉这个题了

下面是~~比较严谨的~~证明

在 $ i $ 之前找到一个最大的 $ j $ ，使得 $ a_{j} > a_{j+1} $ ，那么 $ a_{j} $   $ a_{j+1} $ 不能同时处于递增序列中， $ \mathit{dp_{i,0}} $ 必然为 $ a_j,a_{j+1} - \infty $ 中的一个

如果不存在这样的 $ j $ ，那么 $ \mathit{dp_{i,0}}= \infty $ 

所以 $ \mathit{dp_{i,0}} $ 只有 $ 4 $ 种取值

同理，我们可以证明 $ \mathit{dp_{i,1}} $ 也只有四种取值

每次更新至少有一个值不同，一共 $ 8 $ 个取值，所以对于任意一个 $ f_i $ ，它最多被更新 $ 7 $ 次，复杂度是 $ O(n) $ 的

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f;
const int maxn=2e5+15;
int a[maxn],n,dp[maxn][2],last;
long long ans=0;
void work(int l){
    dp[l][0]=inf;dp[l][1]=-inf;
    for(int i=l+1;i<=n;++i){
        int w0=-inf,w1=inf;
        if(dp[i-1][0]!=-inf){
            if(a[i]>a[i-1])w0=max(w0,dp[i-1][0]);
            if(a[i]<dp[i-1][0])w1=min(w1,a[i-1]);
        }
        if(dp[i-1][1]!=inf){
            if(a[i]<a[i-1])w1=min(w1,dp[i-1][1]);
            if(a[i]>dp[i-1][1])w0=max(w0,a[i-1]);
        }
        if(dp[i][1]==w1&&dp[i][0]==w0)break;
        else{dp[i][1]=w1;dp[i][0]=w0;}
        if(dp[i][0]==-inf&&dp[i][1]==inf){last=i-1;break;}
    }
    ans+=last-l+1;
}
int main(){
    scanf("%d",&n);last=n;
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=n;i>=1;--i)work(i);
    printf("%lld\n",ans);
    return 0;
}
```

$ LATEX $ 已修改 $\times$ 2

---

## 作者：dottle (赞：27)

## 思路

要把一个数列划分成一个降序的和一个升序的序列。

你考虑这个限制其实是很严格的。对于一对数，如果 $i<j,a_i<a_j$，那肯定他们不能同时放到降序序列里面，那肯定就是要么都放到升序序列，要么一边放一个，总之就是至少有一个在升序序列里。那如果有这种东西：`3 4 1 2
`。

那肯定寄了。究其原理就是第一对中的数比第二对的都大，也都前，而你必须从每一对中选一个数放到升序序列里面，就寄了。那一猜就感觉这个是充要的。随便写点啥维护就可以了。然后对于 `2 1 4 3` 这种也考虑一下就可以。


## 题解

结论：对于一个子区间 $[l,r]$，有解的充要条件是：

- 不存在 $l\le a<b<c<d\le  r$，使得 $p_b>p_a>p_d>p_c$ 或 $p_b<p_a<p_d<p_c$。（$\star$）

证明： 必要性显然，可以参考“思路”。

考虑充分性，直接取出区间的 LIS，剩下的序列一定是下降序列。反证，不妨假设剩下的序列中存在 $i<j,a_i<a_j$。为什么他俩不在 LIS 中呢，肯定满足两个条件之一：

1. 他们都小于 LIS 中他们前面的部分，且他们前面至少有两个数
2. 他们都大于 LIS 中他们后面的部分，且他们后面至少有两个数。

否则，我们一定可以把这两个数调进 LIS。但以上两个条件与（$\star$）矛盾。

实现部分的说明由 @_RSY_ 书写。感谢他。 

这两种情况是相反的，可以用完全一致的方式处理，具体而言可以对于所有 $i$ 维护出 $f_i$ 表示以 $i$ 为左端点的相对大小为上述关系的子序列的最小右端点，这样只需要将两次计算出的 $f$ 取个 max 后就可以计算答案。以 3 4 1 2 为例，对于 3，只需要考虑最近的 4，因此可以在每个 4 的位置枚举 3 计算答案，同时在右侧找到这个 3 对应的最近的 2。实现时可以先对于每个 2 先找到最靠近的 1，在 1 加入时更新 2 的位置；再对于每个 3 找到最靠近的 4，在 4 加入时枚举 3 查询最近的 2 。需要用数据结构维护小于某一个值的最小位置，不难用树状数组处理。

```cpp
# include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], min_r[N], fen[N];
long long ans;
stack <int> sk;
vector <int> vec[2][N];

void mofen(int pos, int val){
	for (pos += 5; pos < N; pos += pos & - pos)
		fen[pos] = min(fen[pos], val);
}
int gefen(int pos){
	int res = n + 1;
	for (pos += 5; 0 < pos; pos -= pos & - pos)
		res = min(res, fen[pos]);
	return res;
}

void find_3412(){
	fill(fen, fen + n + 10, n + 1);
	while (!sk.empty())
		sk.pop();
	for (int i = 1; i <= n; ++ i){
		while (!sk.empty() && a[i] < a[sk.top()])
			sk.pop();
		if (!sk.empty())
			vec[0][sk.top()].push_back(i);
		sk.push(i);
	}
	while (!sk.empty())
		sk.pop();
	for (int i = n; 1 <= i; -- i){
		while (!sk.empty() && a[sk.top()] < a[i])
			sk.pop();
		if (!sk.empty())
			vec[1][sk.top()].push_back(i);
		sk.push(i);
	}
	for (int i = n; 1 <= i; -- i){
		for (int ind : vec[0][i])
			mofen(a[ind], ind);
		for (int ind : vec[1][i])
			min_r[ind] = min(min_r[ind], gefen(a[ind] - 1));
		vec[0][i].clear(), vec[1][i].clear();
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i];
	fill(min_r, min_r + n + 2, n + 1);
	find_3412();
	for (int i = 1; i <= n; ++ i)
		a[i] = n + 1 - a[i];
	find_3412();
	for (int i = n; 1 <= i; -- i){
		min_r[i] = min(min_r[i], min_r[i + 1]);
		ans += min_r[i] - i;
	}
	cout << ans << '\n';

	return 0;
}
```

---

## 作者：FZzzz (赞：9)

考虑如何判断一个序列是否 Decinc。记 $f_i$ 为前 $i$ 个元素中，第 $i$ 个元素属于递增序列，则递减序列的最后一个元素的最大可能值；$g_i$ 为前 $i$ 个元素中，第 $i$ 个元素属于递减序列，则递增序列的最后一个元素的最小可能值。当然这两个值可以为正负无穷。一个长度为 $n$ 的序列 Decinc 就相当于 $f_n$ 为负无穷且 $g_n$ 为正无穷。

考虑移动左端点，维护每个右端点的 dp 值，那么答案可以通过双指针或者随便什么方法计算。我们知道某个位置的 dp 值只与它左边位置的 dp 值与这个位置上的值有关，那么某次移动左端点时，若某个点的 dp 值不变，它后面的点的 dp 值一定也不变。所以会被更新的一定是一个前缀，直接往右更新直到不需要更新即可，这样时间开销与此次被更新的 dp 值数同阶。

又由于某个点的 dp 值随着左端点的移动是单调的，故我们只需要保证所有点的 dp 值的所有可能取值数量即可以保证时间复杂度。只讨论 $f$，对于某个点 $i$，令 $j$ 为最大的 $j<i$ 使得 $a_j>a_{j+1}$，我们断言 $f_i$ 的取值只可能是 $a_j$，$a_{j+1}$ 和正负无穷四种（不存在 $j$ 的情况平凡）。证明很简单，考虑 $a_j$ 和 $a_{j+1}$ 必有至少一个属于递减序列，而 $j+1$ 之后的数属于递减序列是不优的。

至此我们知道可以以 $O(n)$ 的时空复杂度解决问题。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n,a[maxn],f[maxn],g[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int r=n;
	ll ans=0;
	for(int i=n;i>0;i--){
		f[i]=n+1;
		for(int j=i+1;j<=n;j++){
			int rf=0,rg=n+1;
			if(a[j]>a[j-1]) rf=max(rf,f[j-1]);
			if(a[j]>g[j-1]) rf=max(rf,a[j-1]);
			if(a[j]<a[j-1]) rg=min(rg,g[j-1]);
			if(a[j]<f[j-1]) rg=min(rg,a[j-1]);
			if(rf==f[j]&&rg==g[j]) break;
			f[j]=rf;
			g[j]=rg;
		}
		while(!f[r]&&g[r]>n) r--;
		ans+=r-i+1;
	}
	printf("%lld\n",ans);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：meyi (赞：8)

提供一个易懂、好写、效率极高的分治做法，思路来自 [Heltion](https://www.luogu.com.cn/user/4407)，但是笔者不知道如何证明其时间复杂度，欢迎指教。

若存在一段合法区间 $[l,r]$，那么 $\forall\ l\le i \le j \le r$，有 $[i,j]$ 是合法区间，这样就证明了答案有单调性，即对于某个位置 $i$，定义 $ans_i$ 是最大的满足 $[i,ans_i]$ 为合法区间的正整数，那么有 $ans_i\ge ans_{i-1}$。

考虑分治，对于区间 $[l,r]$，我们先求出 $ans_l$ 和 $ans_r$，若 $ans_l=ans_r$，则将满足 $l\le i\le r$ 的 $ans_i$ 都赋值为 $ans_l$，否则设 $mid=\lfloor \frac{l+r}{2} \rfloor$ 并递归处理 $[l,mid]$ 和 $[mid,r]$。最后的答案即为 $\sum\limits_{i=1}^n ans_i-\frac{n(n-1)}{2}$。

$ans$ 的求法可以参考 [CF1144G](https://www.luogu.com.cn/problem/CF1144G)。

时间复杂度有一个明显的上界：$O(n^2)$。构造也很简单，将 $ans_i$ 设为 $i+\lfloor \frac{n}{2}\rfloor$ 即可。但是在本题的限制下，笔者未能成功构造出这样的数据，[在 CF 上的提交](https://codeforces.com/contest/1693/submission/161465334) 也仅用了 31ms。欢迎读者证明其复杂度或提供 hack。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri int
typedef long long ll;
const int maxn=2e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int a[maxn],ans[maxn],f[maxn][2],n;
inline void dp(int k){
	f[k][0]=n+1,f[k][1]=0;
	for(ri i=k+1;i<=n;++i){
		f[i][0]=0,f[i][1]=n+1;
		if(a[i-1]<a[i])f[i][0]=f[i-1][0];
		if(a[i-1]>a[i])f[i][1]=f[i-1][1];
		if(f[i-1][1]<a[i])ckmax(f[i][0],a[i-1]);
		if(f[i-1][0]>a[i])ckmin(f[i][1],a[i-1]);
		if(f[i][0]==0&&f[i][1]==n+1){ans[k]=i-1;return;}
	}
	ans[k]=n;
}
void solve(int l,int r){
	if(l+1>=r)return;
	if(ans[l]==ans[r]){for(ri i=l;i<=r;++i)ans[i]=ans[l];return;}
	ri mid=l+r>>1;
	dp(mid);
	solve(l,mid),solve(mid,r);
}
int main(){
	scanf("%d",&n);
	for(ri i=1;i<=n;++i)scanf("%d",a+i);
	dp(1),dp(n);
	solve(1,n);
	printf("%lld",accumulate(ans+1,ans+n+1,0ll)-1ll*n*(n-1)/2);
	return 0;
}
```

---

## 作者：周子衡 (赞：6)

这题做法非常多样，这里只分享一个比较我觉得比较直观的做法。更多做法可以参考官方题解以及洛谷的其他题解。

考虑某个序列 $P$，它可以被划分成上升子序列 $A$ 和下降子序列 $B$。我们把 $P$ 中的所有元素以下标为 $x$ 坐标、值为 $y$ 坐标，画在一个二维平面上，并把 $A$ 中的元素、$B$ 中的元素分别用线段连起来。可以看到，由于两个序列的单调性，它们至多会有一个交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/nkv3lp2h.png)

上面的图中，蓝线 3-7 跨过了黄线 4-5-6，产生了交点。我们称 3~7 是这种划分方式的“交段”。严格来说，我们这样定义交段：

- 交段的左端点 $l$ 是所有满足下面的条件的位置中最靠右的那一个：$l$ 和 $l+1$ 一个属于上升序列，一个属于下降序列，且属于下降序列的元素大于属于上升序列的元素。
- 交段的右端点 $r$ 是所有满足下面的条件的位置中最靠左的那一个：$r$ 和 $r-1$ 一个属于上升序列，一个属于下降序列，且属于下降序列的元素小于属于上升序列的元素。

可以看到，在确定了交段之后，整个序列的划分方式实际上是固定的。我们来考虑：假如固定某个交段，怎么判断这个序列是否是合法的。观察可知，在 $l$ 的左侧，从右往左扫描，每个元素要么比当前下降序列的最左元素大，要么比当前上升序列的最左元素小，否则便不合法。这相当于：把 $1\sim (l+1)$ 的元素排成一排，则每个元素要么是后缀最大值，要么是后缀最小值。$r$ 右侧也同理：把 $(r-1)\sim n$ 的元素排成一排，则每个元素要么是前缀最大值，要么是前缀最小值。而交段内的划分也很固定：由于交段的定义，$(l+1)\sim (r-1)$ 位置的元素要么全部属于 $A$，要么全部属于 $B$。只需判断 $P_l,P_r$ 的大小关系是否符合它们所在序列的限制，以及 $P_{l+1},...,P_{r-1}$ 是否是递增 / 递减的。

我们来研究一个这样的问题：给定某个序列，怎么借助上面的方法判定它是否能划分成一个上升序列和一个下降序列。首先特判它是否能划分成两个序列，使得一个序列的值严格在另一个序列上方（也就是说，按上面的画法把它画到平面上，两条折线没有交点）。这是容易的：看看是否所有元素都是前缀最大值 / 最小值，或者所有元素都是后缀最大值 / 最小值。除了这样的情况，一定存在某个交段。我们枚举交段的左端点 $l$。方便起见，这里假定 $P_l > P_{l+1}$，另一种情况是对称的。此时 $P_l$ 应该在下降序列中，$P_{l+1}$ 在上升序列中。我们首先判断 $1\sim (l+1)$ 是否符合交段左侧的限制。然后一路找，找到最大的 $x$，满足 $P_{l+1} < P_{l+2} < \cdots < P_x$，那么交段的右端点 $r$ 一定是 $x+1$，看看是否有 $P_r < P_l$；最后看 $r$ 右侧是否满足交段右侧的限制。我们可以对每个 $i$ 提前预处理左侧 / 右侧是否满足交段左 / 右的限制，同时预处理最大的 $x$ 满足 $P_i < \cdots < P_x$（以及 $P_i > \cdots > P_x$）。这样就可以 $O(n)$ 判断序列是否合法了。

回到原题。怎么计算一个序列有多少子区间合法呢？我们一样枚举交段左端点 $l$。不同的是，左边我们应该预处理一个位置 $\mathrm{preb}_l$ —— 它是满足 $[x,l+1]$ 是合法左侧的最小的那个 $x$。同理对每个 $r$ 也预处理出 $\mathrm{nxtb}_r$，表示满足 $[r-1,x]$ 是合法右侧的最大 $x$。从 $l$ 找 $r$ 的过程保持不变，依然是枚举 $l+1$ 所在的连续段。那么 $[\mathrm{preb}_l,\mathrm{nxtb}_r]$ 所有子区间都是合法的，可以在这个区间左端点打个标记。最后顺序扫描一遍，找到以每个点为左端点时，最大的合法右端点，就可以求出答案了。

（根据实现的不同，可能还要特别处理没有交段的情形。不过处理完 $\mathrm{preb},\mathrm{nxtb}$ 之后，注意到没交段的区间一定是 $[\mathrm{preb}_i,i+1]$ 或者 $[i-1,\mathrm{nxtb}_i]$ 的子区间，可以不用额外写太多代码。）

总时间复杂度 $O(n)$。

关于如何处理 $\mathrm{preb}_l$：可以顺序扫描所有元素，用单调栈维护所有后缀最小值 / 最大值的位置，并维护最大的在两个栈中都被删去的下标。然后特判栈顶和 $P_{l+1}$ 的大小关系，具体细节可以参考下面代码。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int p[300000];vector<int> maxs,mins;
int preb[300000],nxtb[300000],ansr[300000],upr[300000],downr[300000];
 
int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	
	for(int i=1,lst=0;i<n;i++)
	{
		while(!maxs.empty()&&p[maxs.back()]<p[i]){if(maxs.back()!=i-1)lst=max(lst,maxs.back());maxs.pop_back();}
		while(!mins.empty()&&p[mins.back()]>p[i]){if(mins.back()!=i-1)lst=max(lst,mins.back());mins.pop_back();}
		maxs.push_back(i),mins.push_back(i);
		//printf("%d\n",lst);
		if(p[i+1]>p[i])
		{
			if(maxs.size()>=2&&p[maxs[maxs.size()-2]]<p[i+1])
			{
				preb[i]=max(lst,maxs[maxs.size()-2])+1;
			}
			else preb[i]=lst+1;
		}
		else
		{
			if(mins.size()>=2&&p[mins[mins.size()-2]]>p[i+1])
			{
				preb[i]=max(lst,mins[mins.size()-2])+1;
			}
			else preb[i]=lst+1;
		}
	}
	//for(int i=1;i<=n;i++)printf("%d ",preb[i]);puts("");
	maxs.clear();mins.clear();
	
	for(int i=n,lst=n+1;i>=2;i--)
	{
		while(!maxs.empty()&&p[maxs.back()]<p[i]){if(maxs.back()!=i+1)lst=min(lst,maxs.back());maxs.pop_back();}
		while(!mins.empty()&&p[mins.back()]>p[i]){if(mins.back()!=i+1)lst=min(lst,mins.back());mins.pop_back();}
		maxs.push_back(i),mins.push_back(i);
		if(p[i-1]>p[i])
		{
			if(maxs.size()>=2&&p[maxs[maxs.size()-2]]<p[i-1])
			{
				nxtb[i]=min(lst,maxs[maxs.size()-2])-1;
			}
			else nxtb[i]=lst-1;
		}
		else
		{
			if(mins.size()>=2&&p[mins[mins.size()-2]]>p[i-1])
			{
				nxtb[i]=min(lst,mins[mins.size()-2])-1;
			}
			else nxtb[i]=lst-1;
		}
	}
	//for(int i=1;i<=n;i++)printf("%d ",preb[i]);puts("");
	//for(int i=1;i<=n;i++)printf("%d ",nxtb[i]);puts("");
	
	for(int i=1;i<=n;i++)ansr[i]=i;
	upr[n]=downr[n]=n;for(int i=n-1;i>=1;i--)if(p[i]<p[i+1])upr[i]=upr[i+1],downr[i]=i;else upr[i]=i,downr[i]=downr[i+1];
	for(int i=1;i<n;i++)
	{
		int l=preb[i],r=i+1;
		if(i+1<n)
		{
			
			if(p[i]>p[i+1])
			{
				int t=upr[i+1];r=max(r,t);
				if(t==n)r=n;
				else if(p[t+1]<p[i])r=max(r,nxtb[t+1]);
			}
			else
			{
				int t=downr[i+1];r=max(r,t);
				if(t==n)r=n;
				else if(p[t+1]>p[i])r=max(r,nxtb[t+1]);
			}
		}
		ansr[l]=max(ansr[l],r);
	}
    
	for(int i=2;i<=n;i++)ansr[i]=max(ansr[i],ansr[i-1]);
	long long ans=0;for(int i=1;i<=n;i++)ans+=(ansr[i]-i+1);
	printf("%lld",ans);
}
```

---

## 作者：Tyyyyyy (赞：4)

## CF1693D

### 题意简述
要求你求出一个排列中有多少个子区间，满足能够被不重不漏地划分为一个严格递增序列和一个严格递减序列序列。

$1\leq n\leq 2\times 10^5$。

### 题目分析
CF1144G 是这题子问题，它只要求一个给定的序列能否满足条件。考虑沿用那道题的做法，定义 $f_{i,0/1}$ 表示第 $i$ 个元素作为递增/递减序列的末尾时，另一个序列末尾的最值。转移可以看那道题的题解，这里不再赘述。

但是这个 dp 似乎并没有什么优化的方式，我们考虑观察性质。对于 $f_{i,0}$（第 $i$ 个元素属于递增序列时，递减序列末尾元素的最大值），设 $j$ 为满足 $j<i,a_j>a_{j+1}$ 的最大的 $j$，可以发现 $a_j$ 和 $a_{j+1}$ 中必有一个在递减序列中（因为它们不能同时存在于递增序列中），所以 $f_{i,0}\in\{a_j,a_{j+1},+\inf,-\inf\}$。因此，我们从大到小枚举子区间的左端点 $l$，同时维护 $l\sim n$ 的 dp 值，则每个 dp 值最多改变三次，复杂度为正确的 $O(n)$。对于 $f_{i,1}$ 也有类似结论，读者可以自行验证。

Code：
```cpp
const int N=2e5+10;
int n,p[N],f[N][2],g[N];
void work(int i)
{
	if(i>n)return;
	int mx=0,mn=n+1;
	if(p[i-1]<p[i])mx=max(mx,f[i-1][0]);
	if(f[i-1][1]<p[i])mx=max(mx,p[i-1]);
	if(p[i-1]>p[i])mn=min(mn,f[i-1][1]);
	if(f[i-1][0]>p[i])mn=min(mn,p[i-1]);
	if(f[i][0]==mx&&f[i][1]==mn)return;
	f[i][0]=mx,f[i][1]=mn,g[i]=0;
	if(mx>=1||mn<=n)work(i+1),g[i]=g[i+1]+1;
	return;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)read(p[i]);
	ll ans=0;
	for(int i=n;i;i--)
	{
		f[i][0]=n+1,f[i][1]=0;
		work(i+1);
		ans+=(g[i]=g[i+1]+1);
	}
	write(ans);
	IO::pchar(0);
	return 0;
}
```

---

## 作者：xyin (赞：3)

模拟赛 T4，赛时只拿了 20 分，赛后看了学长的题解[题解链接](https://www.luogu.com.cn/article/8if3fpqo)才过了这道题，想写一写自己的理解。

## 题意简述

把一个子段划分成一个**单调递减**子序列和一个**单调递增**子序列（两者集合的并集是这个子序列的全集，且两者中的元素互异），求序列 $a$ 有多少个这样的子段。

## 思路历程

我们直接看样例，就能得出一些显而易见的结论：

* 当子段只有一个数的时候肯定是合法的（你啥都不用删）。

* 当子段只有两个数的时候肯定也是合法的（此时你可以随便删一个到递减序列中去）。

**解法一**：

首先能想出一个很暴力的方法，每次枚举子段的左端点（$l$），右端点（$r$），同时用 `check` 函数去 `check` 区间是否合法，统计答案。

我们考虑降低 `check` 的复杂度，如果能 $O(n)$ `check` 就好了。

* 设 $dp_{i,0}$ 表示 $i$ 放在**递减**序列时，**递增**序列的**最小值**(设为最小值是为了方便我们贪心转移)。

* 设 $dp_{i,1}$ 表示 $i$ 放在**递增**序列时，**递减**序列的**最大值**(最大值同理)。

初始化：$l$ 为我们的起始端点。

```cpp
for (int i=l;i<=n;i++)
	  dp[i][1]=-INF,dp[i][0]=INF;//后面取 max 和 min
      //只有当我们遍历结束时，dp[i][1] 和 dp[i][0] 还是初始值时，该子段不合法
dp[l][0]=-INF;dp[l][1]=INF;//起始端点当然是合法的
```

转移方程式：

* $i$ 放在递增序列时，此时 $dp_{i,1}$ 的转移为：

1. $i-1$ 也放在递增序列， $dp_{i,1}$ 可由 $dp_{i-1,1}$ 转移过来（条件：$a_{i-1}$ 到 $a_i$ 递增）。

```cpp
if (a[i]>a[i-1]) dp[i][1]=max(dp[i][1],dp[i-1][1]);
```

2. $i-1$ 放在递减序列，此时 $dp_{i,1}$（递减序列的最大值）可由 $a_{i-1}$ 转移（条件：$i$ 能放在递减序列）。

```cpp
if (dp[i-1][0]<a[i]) dp[i][1]=max(dp[i][1],a[i-1]);
```

* $dp_{i,0}$ 的转移同理，建议自己推 $dp$ 方程式。

这时你的枚举为 $O(n^2)$，$dp$ 转移为 $O(n)$，总的时间复杂度为 $O(n^3)$。

**解法二**：

其次我们再探究一下某些其他性质：

* 当我们求出一个“好”区间时，该区间的**所有子段**都是“好”的。

那这时你就可以只用枚举左端点（$l$），每次 $dp$ 转移到不合法为止，此时的位置就是能扩展到的最远的右端点（$r$），这样你就不用再枚举 $r$ 了。

此时你有了一个 $O(n^2)$ 的代码：

```cpp
int n,a[maxn],ans,last;
int dp[maxn][2],fac[maxn];
//dp[i][1] 表示 i 放在递增序列时，递减序列的最大值
//dp[i][0] 表示 i 放在递减序列时，递增序列的最小值 
void init(){//递推求一个“好 ”区间的所有子段数量 
	for (int i=1;i<=n;i++)
	  fac[i]=fac[i-1]+i;
}
int solve(int l){//查询 l 能延伸的最远端点 
	for (int i=l;i<=n;i++)
	  dp[i][1]=-INF,dp[i][0]=INF;
	dp[l][0]=-INF;dp[l][1]=INF;
	for (int i=l+1;i<=n;i++){
		//转移 dp[i][1] 
		if (a[i]>a[i-1]) dp[i][1]=max(dp[i][1],dp[i-1][1]);
		if (dp[i-1][0]<a[i]) dp[i][1]=max(dp[i][1],a[i-1]);
		//转移 dp[i][0] 
		if (a[i]<a[i-1]) dp[i][0]=min(dp[i][0],dp[i-1][0]);
		if (dp[i-1][1]>a[i]) dp[i][0]=min(dp[i][0],a[i-1]);
		//判断是否合法 
		if (dp[i][0]==INF&&dp[i][1]==-INF) return i-1;
	}
	return n;
}
signed main(){
	n=read();init(); 
	for (int i=1;i<=n;i++)
	  a[i]=read();
	for (int l=1;l<=n;l++){ 
		int t=solve(l);
		if (t>last)//如果这次的最远端点 大于 上一次 说明还没累计过答案 
		  ans+=fac[t-l+1]-fac[last-l+1],last=t;
		//新区间的子段数减去重叠区间的子段数，更新 last 
	}
	printf("%lld\n",ans);
	return 0;
}
```

**解法三**：

我们考虑从大到小枚举左端点（因为 $dp$ 转移是向后，从大到小枚举，这样后面的 $dp$ 值是都知道的）。

你在转移时有两种可能：

1. 你此时求出的 $i$ 点的 $dp$ 值与上一次完全相同（指 $dp_{i,0}$ 与 $dp_{i,1}$ 都相同），如果你再往后继续转移，往后所有的 $dp$ 值都会与上一次相同，所以最终停下来的位置也相同（能转移的最远右端点）。我们此时可以直接 `break` 掉，同时累加上一次（设为 $last$）的答案。

2. 你此时求出的 $i$ 点的 $dp$ 值与上一次不同，那你就把 $i$ 位置的 $dp$ 值更新为本次求得的答案，继续转移。当你转移到不合法时，`break`。

这个做法看似是优化的常数，但实际上变成了 $O(n)$ 的。证明参见[这儿](https://www.luogu.com.cn/article/8if3fpqo)。

**code**:

```cpp
int solve(int l){
	dp[l][0]=-INF;dp[l][1]=INF;
	for (int i=l+1;i<=n;i++){
		int ok1=INF,ok2=-INF;//ok1 -> dp[i][0] ok2 -> dp[i][1] (这里相当于初始化 
		if (a[i]>a[i-1]) ok2=max(ok2,dp[i-1][1]);
		if (dp[i-1][0]<a[i]) ok2=max(ok2,a[i-1]);
		if (a[i]<a[i-1]) ok1=min(ok1,dp[i-1][0]);
		if (dp[i-1][1]>a[i]) ok1=min(ok1,a[i-1]);
		if (ok1==dp[i][0]&&ok2==dp[i][1]) return last;
		else dp[i][0]=ok1,dp[i][1]=ok2;
		if (dp[i][0]==INF&&dp[i][1]==-INF) return i-1;
	}
	return n;
}
signed main(){
	n=read();last=n;
	for (int i=1;i<=n;i++)
	  a[i]=read();
	for (int i=n;i>=1;i--){ 
		last=solve(i);
		ans+=last-i+1; 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Schi2oid (赞：2)


### 题意简述

给定一个长度为 $n$ 的排列，求其有多少子区间满足，在其中删去一个单调递减子序列，剩下的序列单调递增。

$n\le 2\times 10^5$。

### 思路分析

首先考虑只需要判定一个给定的序列怎么做。不难发现，如果我们能够将整个序列划分好，那么任意前缀元素都可以划分。同时，我们考虑对于某个前缀，如果确定其末尾元素归入单增序列，那么单降序列的末尾一定是越大越容易进行后续的划分。因此，我们只关心此时单降序列末尾最大值。反之亦然。

自然地，设 dp $f_{i,0}$ 表示考虑到第 $i$ 位，将 $i$ 归入单增子序列，此时单减子序列末尾的最大值。相应地，设 $f_{i,1}$ 表示考虑到第 $i$ 位，将 $i$ 归入单减子序列，此时单增子序列末尾的最小值。考虑转移，枚举 $i-1,i$ 分别归入哪一个子序列即可。时间复杂度容易做到 $O(n)$。

考虑原问题。枚举左端点，直接做上述 dp 可以做到 $O(n^2)$。dp 本身难以优化，考虑观察性质。考虑 $f_{i,0}$ 可能的取值，对于位置 $i$，找到最大的 $j$ 满足 $j<i,a_j>a_{j+1}$，那么 $a_j,a_{j+1}$ 必然有一个位于单减序列中。因此，$f_{i,0}$ 一定只能取 $\{a_j,a_{j+1},\infty,-\infty\}$。其中，$\infty$ 表示空序列，$-\infty$ 表示不存在合法划分。考虑随着左端点右移，在左端点较小时存在的划分方案一定也会在左端点较大时存在，所以 $f_{i,0}$ 的值一定会单调不降地变化。这意味着其值至多会变化 $3$ 次。

继续观察转移性质。容易发现 $f_{i,0/1}$ 的值只基于 $f_{i-1,0/1}$。因此，如果左端点移动后，满足 $f_{i,0}=f'_{i,0},f_{i,1}=f'_{i,1}$，那么后续的更新就不需要再进行了。同时，如果某值变为不合法，其之后也将全部变为不合法，存下当前最右的合法位置即可。

基于上述分析，每次 dp 访问到下标 $i$ 时，一定会修改其 $f_{i,0/1}$ 的值，因此一个下标至多会被访问 $7$ 次。直接暴力更新 dp 数组，复杂度是 $O(n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e18;
int p[200005];
int f[200005][2];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&p[i]);
	int r=n,ans=0;
	for(int l=n;l>=1;l--){
		f[l][0]=INF,f[l][1]=-INF;
		for(int j=l+1;j<=r;j++){
			int v0=-INF,v1=INF;
			if(f[j-1][0]>p[j]) v1=min(v1,p[j-1]);
			if(p[j-1]<p[j]) v0=max(v0,f[j-1][0]);
			if(f[j-1][1]<p[j]) v0=max(v0,p[j-1]);
			if(p[j-1]>p[j]) v1=min(v1,f[j-1][1]);
			if(v0==f[j][0]&&v1==f[j][1]) break;
			if(v0==-INF&&v1==INF){
				r=j-1;
				break;
			}
			f[j][0]=v0,f[j][1]=v1;
		}
		ans+=r-l+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：369Pai (赞：1)

结论：如果一个序列是好的，当且仅当其是 $3412$-avoiding 且 $2143$-avoiding 的。

证明：

必要性：如果一个序列不是 $3412$-avoiding 的，那么对于 $34$，至少有一个要在单调递增序列中，$12$ 也至少有一个要在单调递增序列中；而 $34$ 中任意一个大于 $12$ 中任意一个，所以两者不能同时在单调递增序列中，矛盾；$2143$-avoiding 同理。

充分性：考虑对数组长度 $n$ 进行归纳。任意长度 $\le 3$ 的必定能划分为一个单调递增序列和一个单调递减序列，接下来假设 $n \ge 4$。

考虑根据最大值相对位置讨论。如果最大值右侧没有单调递增序列中的元素，可以直接将其加入单调递增序列，反之亦然。考虑剩下的情况，即右侧有递增序列元素，左侧有递减序列元素。

不妨设最大值位置为 $i$，其右侧**值最大**的递增序列元素位置为 $r$，左侧**值最大**的递减序列元素位置为 $l$。

那么 $p_i,p_r$ 构成了 $2143$ 中的 $43$，即其限制了最大值左侧，不存在值都 $<p_r$ 的递减序列；同理 $p_l,p_i$，构成了 $3412$ 限制的 $34$ 即其限制了最大值右侧，不存在值都 $<p_l$ 的递增序列。

不妨设 $p_l < p_r$，另一种情况是类似的。

![](https://pic.imgdb.cn/item/6657ccb7d9c307b7e9e452a0.png)

（如图，三角为最大值，方形为原递减序列元素，圆形为递增序列元素，其中黑色的为 $p_l,p_r$。红色区域内不能有递减子序列；蓝色区域内不能有递增子序列）

那么不存在递减序列元素 $p_j$，满足 $l < j < i$，因为这样 $p_i > p_r > p_l > p_j$，构成了 $2143$；又因为 $p_l$ 是递减序列中**值最大**的元素，所以也不存在递减序列的元素在 $l$ 左侧。那么递减序列在 $i$ 左侧只有**唯一**一个元素 $p_l$。

实际上，由于 $p_l$ 位于 $p_i,p_r$ 构成的 $2143$ 限制区（红色区域）内，所以其只能和 $i$ 左侧递增序列的元素构成一个递增序列。

而递减序列的其他元素，由于 $<p_l$，只能位于 $3412$ 限制区（蓝色区域）内；递增序列不在蓝色区域内的元素，一定 $>p_l$。

所以可以这样重新排列序列：最大值左侧红色区域中的元素，与右侧蓝色区域以外的元素构成新的递增序列；最大值和右侧蓝色区域内的元素构成新的递减序列。

$p_l > p_r$ 的情况类似讨论即可。证毕。

做法考虑对每个左端点 $i$，计算最大的 $r_i$，满足子序列 $[i,r_i)$ 中不存在 $3412$ 或 $2143$ 的序列，答案即为 $\sum\limits_{i=1}^n r_i-i$。

以 $3412$ 为例，$2143$ 可以直接将值取反再做一遍。

由于主要考虑 $3,2$ 的相对大小，可以先对 $3$ 预处理左侧第一个比其大的元素（即 $4$ 的位置），并将其记录在该位置上；同样对 $2$ 预处理右侧第一个比其小的位置（$1$ 的位置），并将其记录在该位置上，这个可以单调栈。

然后从右到左扫描，对于 $4$，枚举其对应的 $3$，查询 $4$ 左侧第一个小于 $3$ 的位置，这可以用树状数组，维护值为 $v$ 的最小下标，操作是单点修改，前缀取 $\min$；然后对于 $1$，在树状数组中加入其对应的 $2$ 即可。

时间复杂度 $\mathcal{O}(n \log n)$。

---

## 作者：intel_core (赞：1)

$O(n)$ 太神秘，提供一种自然好想的 $O(n\log n)$ 做法。

考虑无解的判定条件，显然如果相对顺序出现 3412 或者 2143 就无解。否则直接贪心构造即可。

现在考虑求对于一个左端点 $i$，最大合法右端点 $f_i$ 的值。

比如考虑 3412 的限制，那么对于 3 和 2 而言，一定是选离自己最近的。这个可以一遍单调栈解决。

设 3 的位置是 x，2 的位置是 y，那么形成 3412 这种结构的条件就是 $a_x>a_y$ 且 $p_x<q_y$，其中 $p_x$ 表示最小的 $k$ 使得 $a_x<a_k$，$q_y$ 类似。

如果 $x,y$ 满足上述两个条件，我们就把 $f_x$ 和 $y-1$ 取 $min$。那么对于每个 $x$，只需要记录 $(a_x,p_x)$，类似的，对于 $y$ 只需要记录 $(a_y,q_y)$，额外记录点权为 $y$。

将问题转化后，相当于二维平面上求一个点右上方所有点点权的最小值。离线树状数组即可，复杂度 $O(n\log n)$。

---

## 作者：Purslane (赞：0)

# Solution

我失败了。尝试使用 DP 套 DP 并且使用数据结构优化，实在难写。（其实只有一大堆分类讨论，但是……）

~~其实是没观察出来一共只有 $8$ 种情况的结论、 /ll~~

考虑给定一个区间，如何判断它能否划分。

设 $f_{i,0/1}$ 表示，考虑前 $i$ 个数，如果最后一个数要放在上升（或下降）的链上，另一个链头的最优值是多少。（如果是下降链，显然链尾值越大越优）

我们还可以设 $\pm \infty$，表示可以接任意数或者这种情况压根不存在。（比如 $i$ 必须放在链的顶端）

转移的时候，只需要枚举几种情况即可。

考虑固定左端点，答案对右端点有单调性，因此可以给出简单的 $O(n^2)$ 做法。

结论：$(f_{i,0},f_{i,1})$，在 $i$ 给定的只有 $O(1)$ 种情况。

有一点我是观察到的：当 $a_{i-1} < a_i$ 时，如果 $i$ 要做**下降链**，另一条链的顶端**必然在 $i-1$ 处**，或者取 $\pm \infty$，也就是一维只有 $3$ 种情况。

这时考虑 $a_t > a_{t+1} < a_{t+2} < \cdots < a_{i-1} < a_i$，则另一维只能在 $\{t,t+1,\pm \infty\}$ 中取。

证明是容易的，显然这个头的位置（如果存在）必然 $\ge t$。如果不是 $\{t,t+1\}$ 中的某个值，假设是 $z$，则 $z+1$ 之后的点都放在上升链中——这时候把它调整到另一条链上去，显然会更优。（同时后方也有人兜底，所以调整是合法的）

因此我们对每个端点暴力往右扫，如果遇到了某个地方的 $(f'_{i,0},f'_{i,1}) = (f_{i,0},f_{i,1})$，则之后所有的 $f$ 都一模一样，没必要被更新，复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,a[MAXN],f[MAXN][2],vis[MAXN]; 
ll ans=0;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	int r=-1;
	ffor(l,1,n) {
		int d1=0,d2=n+1;
		ffor(p,l,n) {
			if(vis[p]&&f[p][0]==d1&&f[p][1]==d2||d1==n+1&&d2==0) break ;	
			vis[p]=1,f[p][0]=d1,f[p][1]=d2,r=max(r,p);
			if(p!=n) {
				int D1=n+1,D2=0;
				if(a[p]<a[p+1]) {
					D2=max(D2,d2);
					if(a[p+1]>d1) D2=max(D2,a[p]);
					if(d2>a[p+1]) D1=min(D1,a[p]);
				}
				else {
					D1=min(D1,d1);
					if(a[p+1]<d2) D1=min(D1,a[p]);
					if(d1<a[p+1]) D2=max(D2,a[p]);	
				}
				d1=D1,d2=D2;
			}
		}
		ans+=r-l+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：aoeiuv (赞：0)

你要统计有多少个 Decinc 数组，首先你要会判断一个数组是不是 Decinc 数组。对于递增数组，我们希望最后一个数越小越好，这样可以填入更多的数，递减数组也是同理。于是可以记 $f_{i,0/1}$ 表示 $a_i$ 放入递增/减数组中，数组最后一个数最小/大可以是多少。转移直接分两类情况讨论从 $f_{i-1,0/1}$ 转移，一种情况就是 $a_i$ 接在 $a_{i-1}$ 后面，另一种情况是 $a_i$ 接在 $f_{i-1,0/1}$ 后面，然后就可以 $\mathcal{O}(n^3)$ 枚举，固定左端点往后扫可以做到 $\mathcal{O}(n^2)$。[](https://codeforces.com/contest/1693/submission/290175034)

单次 DP 已经是 $\mathcal{O}(n)$ 的了，没有优化的空间了，这时候就要观察一下有没有额外的性质？

观察 $f$ 数组的取值规律发现，以 $f_{i,0}$ 为例。假设 $j$ 是满足 $j < i,a_j < a_i,a_j > a_{j+1}$ 的最大的 $j$，那么 $a_j$ 和 $a_{j+1}$ 一定有一个数要被放在递减数组中，那么就有可能成为 $f_{i,0}$ 的取值。所以 $f_{i,0}$ 的取值也只有 $4$ 种： $\{a_j,a_{j+1},+\infty,-\infty\}$，其中 $+\infty$ 是空序列，$-\infty$ 是不合法的序列。既然取值只有 $4$ 种，也就是说只会产生至多 $3$ 次的变化。

由于 $f_{i+1}$ 的取值是基于 $f_{i}$ 得到的，所以如果 $f_i$ 无变化，后面的过程就不必进行下去了。这样时间复杂度是 $\mathcal{O}(n)$ 的。

实现上，可以倒序枚举序列的左端点 $l$ 向右扫，然后扫到无变化或者不合法的就退出。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n,a[N],f[N][2]; // 0 zeng, 1 jian

int main(){
    cin >> n;
    for (int i = 1;i <= n;i++)
        cin >> a[i];
    int r = n; long long ans = 0;
    for (int l = n;l >= 1;l--){
        f[l][0] = 1e9, f[l][1] = 0;
        for (int i = l + 1;i <= r;i++){
            int t0 = 0, t1 = 1e9;
            if (f[i - 1][1] < a[i]) t0 = max(t0,a[i - 1]);
            if (a[i - 1] < a[i]) t0 = max(t0,f[i - 1][0]); 
            if (f[i - 1][0] > a[i]) t1 = min(t1,a[i - 1]);
            if (a[i - 1] > a[i]) t1 = min(t1,f[i - 1][1]);
            if (t0 != 0 || t1 != 1e9){
                if (f[i][0] == t0 && f[i][1] == t1) break;      // 无变化
                f[i][0] = t0, f[i][1] = t1;
            }
            else{                                               // 不合法
                r = i - 1;
                break;
            }
        }
        ans += r - l + 1;
    }
    cout << ans;
    return 0;
}
```

> 2143 和 3412 的 $n\log n$ 做法也很厉害！

- [参考 Schi2oid 的题解](https://www.luogu.com.cn/article/l34uwuuq)
- [参考 dottle 的题解](https://www.luogu.com.cn/article/vg0tlv3o)

---

