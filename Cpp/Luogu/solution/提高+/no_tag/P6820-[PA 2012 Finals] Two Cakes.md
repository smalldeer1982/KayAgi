# [PA 2012 Finals] Two Cakes

## 题目描述

你有两个 $1\sim n$ 的排列。你用左手和右手分别从左到右写两个排列，每只手每写一个数需要 $1$ 单位时间，两只手可以同时工作。若你两只手不能同时写同一个数，那你至少需要多久写完这两个排列呢？

## 说明/提示

**样例解释**

第一单位时间：左手写 $1$，右手写 $3$。

第二单位时间：左手写 $2$。

第三单位时间：右手写 $2$。

第四单位时间：左手写 $3$，右手写 $1$。

**数据范围**

对于 $100\%$ 的数据，$1\le n\le 10^6$。

## 样例 #1

### 输入

```
3
1 2 3
3 2 1```

### 输出

```
4```

# 题解

## 作者：LYY_yyyy (赞：11)

首先考虑 $O(n^2)$ 的 dp。记录 $f_{i,j}$ 表示完成第一个数列中的前 $i$ 位和第二个数列中的前 $j$ 位的最小代价。转移：

若 $a_i=b_j$，$f_{i,j}=\min(f_{i-1,j},f_{i,j-1})+1$

否则，$f_{i,j}=f_{i-1,j-1}+1$

然后我们注意到两个数列都是排列。这就意味着，对于每一个 $i$，只会有一个 $j$ 进行第一个转移。然后我们又注意到第二个转移形如一个平移的形式，这就启发我们将空间压成一维，每次维护一个平移操作以及一个单点修改的操作。具体地，我们只需要完成平移、全局加一、单点修改操作即可。这可以通过将数组倍长，维护全局增量解决。之后再在数组上修改 $i$ 对应的 $j$ 的位置即可。时空复杂度 $O(n)$。代码很短，不到 500B。实现的时候注意上一版和这一版中全局增量的统一。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010],p[1000010];
int dp[2000010];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;int op;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>op,p[op]=i;
	for(int i=n;i<=2*n;i++) dp[i]=i-n;
	for(int i=1;i<=n;i++)
	{
		int l=n-i;
		dp[p[a[i]]+l]=min(dp[p[a[i]]+l+1],dp[p[a[i]]+l-1]+1);
	}cout<<dp[n]+n;
	return 0;
}
```


---

## 作者：Leasier (赞：10)

设 $dp_{i, j}$ 表示 $a$ 匹配到第 $i$ 个，$b$ 匹配到第 $j$ 个时至少需要多少时间。

1. 当 $a_i = b_j$

$dp_{i, j} = \min(dp_{i, j - 1}, dp_{i - 1, j}) + 1$

2. 当 $a_i \neq b_j$

$dp_{i, j} = dp_{i - 1, j - 1} + 1$

但这样做是 $O(n^2)$ 的，需要优化。

由于 $a, b$ 为排列，我们发现第一种转移的情况仅有 $n$ 种，且对于每个 $i$ 唯一。

考虑记忆化搜索，对于 $a_i = b_j$ 的情况，记忆化搜索；否则，考虑找到一个尽量大的 $k$，使对于任意 $0 \leq l \leq k$，$a_{i - l} \neq b_{i - l}$，此时直接令 $dp_{i, j} = dp_{i - k - 1, j - k - 1} + k$。这里可以对于值相同的位置的下标差开 vector 记录，查询时二分即可。

时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

int a[1000007], pos[1000007], b[1000007], dp[1000007];
bool vis[1000007];
vector<int> v[2000007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int dfs(int n, int m, int k){
	if (a[n] == b[m]){
		if (vis[n]) return dp[n];
		vis[n] = true;
		return dp[n] = min(dfs(n, m - 1, k), dfs(n - 1, m, k)) + 1;
	}
	int pos, t = n - m + k;
	pos = lower_bound(v[t].begin(), v[t].end(), n) - v[t].begin();
	if (pos == 0) return max(n, m);
	pos = v[t][pos - 1];
	return dfs(pos, m - (n - pos), k) + (n - pos);
}

int main(){
	int n = read(), m = n * 2 - 1;
	for (int i = 1; i <= n; i++){
		a[i] = read();
		pos[a[i]] = i;
	}
	for (int i = 1; i <= n; i++){
		b[i] = read();
		v[pos[b[i]] - i + n].push_back(pos[b[i]]);
	}
	for (int i = 0; i <= m; i++){
		sort(v[i].begin(), v[i].end());
	}
	cout << dfs(n, n, n);
	return 0;
}
```

---

## 作者：2huk (赞：7)

考虑最朴素的 DP。设 $f(i, j)$ 表示消除 $a_{1 \dots i},b_{1 \dots j}$ 的代价。转移显然：
$$
f(i, j) = \begin{cases}
\min(f(i-1,j),f(i,j-1))+1 &a_i = b_j \\
\min(f(i-1,j), f(i,j-1),f(i-1,j-1)) + 1 & a_i \ne b_j
\end{cases}
$$
直接做是 $\mathcal O(n^2)$ 的。考虑优化。

注意到 $f(i-1,j-1) \le \min(f(i-1,j), f(i,j-1))$。所以：
$$
f(i, j) = \begin{cases}
\min(f(i-1,j),f(i,j-1))+1 &a_i = b_j \\
f(i-1,j-1) + 1 & a_i \ne b_j
\end{cases}
$$
满足 $a_i = b_j$ 的状态 $f(i, j)$ 只有 $\mathcal O(n)$ 个。我们称这样的状态为特殊状态。

注意到对于非特殊状态（$a_i \ne b_j$），它一定会从 $f(i-1,j-1)$ 转移而来。如果 $f(i-1,j-1)$ 仍不是特殊状态，那么又会从 $f(i-2,j-2)$ 转移过来。发现每次用到的状态都是唯一确定的，而且**两维状态的差固定**。

这个过程会持续到 $f(i', i'+j-i)$。这是一个特殊状态（$a_{i'} = b_{i'+j-i}$），且 $i' < i$ 且 $i'$ 最大。然后 $f(i, j) = f(i', i'+j-i)+i-i'$。求这个 $i'$ 可以预处理+二分。

分析复杂度。一个特殊状态会通过两个非特殊状态转移，而一个非特殊状态会通过一个特殊状态转移。所以总复杂度是特殊状态的数量，即 $\mathcal O(n)$。

```cpp
// Problem: 
//     T541528 左右互搏术
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T541528?contestId=214582
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, a[N], b[N];
int na[N], nb[N];		// a, b 的逆
int g[N];
vector<int> pos[N * 2];		// 每种差的出现位置

int dp(int x, int y) {
	if (!x) return y;
	if (!y) return x;
	if (a[x] == b[y]) {
		if (~g[x]) return g[x];
		return g[x] = min({dp(x - 1, y - 1) + 2, dp(x, y - 1) + 1, dp(x - 1, y) + 1});
	}
  
	auto it = lower_bound(pos[x - y + N].begin(), pos[x - y + N].end(), x);
	if (it == pos[x - y + N].begin()) return max(x, y);
	it -- ;
	return dp(*it, *it + y - x) + x - *it;
}

void solve() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) cin >> a[i], na[a[i]] = i;
	for (int i = 1; i <= n; ++ i ) cin >> b[i], nb[b[i]] = i;
	
	for (int i = 0; i <= n; ++ i ) {
		f[0][i] = f[i][0] = i;
	}
	for (int i = 1; i <= n; ++ i ) {
		pos[na[i] - nb[i] + N].push_back(na[i]);
	}
	for (int i = 0; i < N * 2; ++ i ) {
		sort(pos[i].begin(), pos[i].end());
	}
	memset(g, -1, sizeof g);
	cout << dp(n, n) << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：loveJY (赞：7)

不错的dp题！

首先有一些很能骗分的贪心，因为有个结论就是左右手单独写次数相等，所以我们可以固定在两个序列相等的时候选择某一方多写k次，然后这个k可以枚举几个

因为单独的k可能会因为错位相同而自闭，比如
```
4
4 1 2 3
4 2 3 1

```
正解：

考虑dp，$f_{i,j}$表示a序列匹配了i个b序列匹配了j个的最小次数

转移：

$a_i==a_j$

$$f_{i,j}=min(f_{i-1,j},f_{i,j-1})+1$$

$a_i!=a_j$

$$f_{i,j}=f_{i-t-1,j-t-1}+t$$

其中t是最大的而且$a_{i-t-1}=a_{j-t-1}$

哎？好像第一类状态最多$O(n)$个，而第二类状态的转移又是可以用个什么优化的，并且一定只从第一类的状态中转移而来

也就是说第二类状态可以用第一类的$O(n)$个状态+某个值完备表示

所以可以考虑$f_i$表示$i,j$,其中$a_j==a_i$这个dp状态的值

然后转移的时候我们现场计算$f_{i,j-1}$和$f_{i-1,j}$的值即可

然后直观上求这个值因为是最大的t好像可以二分？

但是你会发现这个东西只和$i,j$两维的差有关。。。所以用一个g数组记录一下就好了

时间复杂度$O(n)$

code：


```cpp


#include<bits/stdc++.h>
#define mkp(x,y) (make_pair(x,y))
#define fi first
#define se second
#define pii pair<int,int>
using namespace std;
const int MAXN=2e6+7;
int n,a[MAXN],b[MAXN],vis[MAXN],f[MAXN];
pii g[MAXN];

inline int getdp(int x,int y) {
	//边界特判一下。。 
	if(g[x-y+n].fi==0)return max(x,y);
	return g[x-y+n].se+x-g[x-y+n].fi;
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; ++i) {
		scanf("%d",&b[i]);
		vis[b[i]]=i;
	}
	for(int i=1; i<=n; ++i) {
		f[i]=min(getdp(i-1,vis[a[i]]),getdp(i,vis[a[i]]-1))+1;
		g[i-vis[a[i]]+n]=mkp(i,f[i]);
	}
	printf("%d\n",getdp(n,n));
	return 0;
}



```

---

## 作者：囧仙 (赞：4)

## 题解

这是一道不错的 $\textsf{dp}$ +贪心题。

由于题面上是两个全排列，与数字的大小无关，仅与数字是否相同有关，因此为了降低本题讨论的复杂程度，我们**钦定**第一个数列就是 $1,2,3\cdots n$ 而对第二个数列重新标号。具体而言，假如数字 $i$ 在第一个数列中在 $pos$ 处，那么第二个数列的 $i$ 就修改为 $pos$ 。同时，我们记录第二个数列修改后数字 $i$ 出现的位置 $P_i$ 。

很容易得到一种贪心的想法：倘若左右手上的数字不同，显然两只手同时取。那么什么时候需要我们停下来考虑呢？显然，这种情况会发生，当且仅当左右手上的数字相同。

因此设 $dp_i$ 表示，当前左右手**都恰好**在数字 $i$ **前面**时，取完所有数字花费的次数的最小值。由于我们对数字重新标号了，所以此时左手恰好在第 $i$ 个数前面，右手在第 $P_i$ 个数前面（不妨设 $j=P_i$）。显然，我们有两种情况要考虑：

- $1.$ 先取左手上的数。此时 $(i,j)\gets(i+1,j)$ 。根据贪心思路，在直到左右手数字相同前，我们会不断同时取数。因此我们求出下一个最近的 $t$ ，使得 $t-(i+1)=P_t-P_i$ 。特别地，若不存在这样的 $t$ ，这种情况下到终点的最小花费就是 $\max\{n-i,n-j+1\}+1$ 。

- $2.$ 先取右手上的数。此时 $(i,j)\gets(i,j+1)$ 。由于这种情况和情形 $1$ 基本类似，因此不再赘述。

对于两种策略，为了转移，我们都要求出这样的 $t$ 。其实它很好求：比如情形 $1$ ，由于 $t-(i+1)=P_t-P_i\iff t-P_t=(i+1)-P_i$ ，因此开一个数组 $U$ ，其中 $U_x$ 表示 **满足** $\bm{(t-P_t=x)}$ **的** $\bm t$ **的位置**。从后往前计算 $dp_i$ 时，我们能够顺便维护 $U$ ，此时 $U_{i-j+1}$ 就是情形 $1$ 中当前枚举到的 $i$ 后面最近的 $t$ 的值（特别地，若 $U_x=0$ ，则不存在这样的 $t$）。

然后我们就能得到转移方程：

$$\begin{aligned}
dp_i=\min\{& \cr
&\begin{cases}
dp_t+t-i & \text{存在这样的 } t=U_{i-j+1}\cr
1+\max\{n-i,n-j+1\} & \text{不存在这样的 } t \cr
\end{cases} \cr
&, \cr
&\begin{cases}
1+dp_t+t-i & \text{存在这样的 } t=U_{i-j-1}\cr
1+\max\{n-i+1,n-j\} & \text{不存在这样的 } t \cr
\end{cases} \cr
\}
\end{aligned}$$

一些细节：

- 最后答案是什么呢？事实上我们只要从头开始贪心，碰到第一个 $i=P_i$ ，然后拿 $(i-1+dp_i)$ 更新答案就行了。特别地，若不存在这样的 $i$ ，答案就是 $n$ 。

- 由于 $U_x$ 可能出现负数下标，而这在 C++ 中是不被允许的，因此我们将下标统一加上一个数（比如 $n+3$）来使下标恒非负。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e6+3;
int n,A[MAXN],B[MAXN],F[MAXN],U[MAXN*2];
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(); up(1,n,i) A[qread()]=i; up(1,n,i) B[i]=A[qread()]; up(1,n,i) A[B[i]]=i;
    dn(n,1,i){
        int j=A[i],t; F[i]=INF;
        if(t=U[3+n+i-j+1]) F[i]=min(F[i],  F[t]+t-i); else F[i]=min(F[i],1+max(n-i,n-j+1));
        if(t=U[3+n+i-j-1]) F[i]=min(F[i],1+F[t]+t-i); else F[i]=min(F[i],1+max(n-i+1,n-j));
        U[3+n+i-j]=i;
    }
    up(1,n,i) if(i==A[i]) printf("%d\n",F[i]+i-1),exit(0);
    return 0;
}
```

---

## 作者：_Supernova (赞：3)

**花了大量时间研究这题，特写题解纪念并阐述思维过程。**

### 朴素 DP 做法

对于 $n\leq10^3$，记 $f_{i,j}$ 表示第一个排列写了 $i$ 个数字，第二个排列写了 $j$ 个数字，所需要的最少时间。

则有状态转移方程：

若 $a_i=b_j$，$f_{i,j}=\min(f_{i-1,j},f_{i,j-1})+1$。

反之，则 $f_{i,j} = f_{i-1,j-1}+1$。

时间复杂度为 $O(n^2)$。

### 优化 DP 做法

注意到对于 $a_i=b_j$ 这种特殊转移情况，仅存在 $n$ 种可能。

于是考虑转换 $f$ 数组定义：记 $f_{i,j}$ 表示第一个排列写了 $i$ 个数字，第二个排列比第一个排列多写了 $j$ 个数字所需的最少时间。（注意 $j$ 可能为负数）

则状态转移方程为：

若 $a_i=b_{i+j}$，$f_{i,j}=\min(f_{i-1,j+1},f_{i,j-1})+1$。（特殊情况）

反之，$f_{i,j}=f_{i-1,j}+1$。

效果便是对于 $f$ 数组，第 $i$ 行与第 $i-1$ 行可以说是除了特殊情况的转移外几乎不变，那我们可以将 $f$ 数组优化成一维数组，每次单点修改即可。

注意到转移方程中 $+1$ 是普遍存在的情况，所以**我们省略 $+1$ 操作，最后将答案整体加上 $n$ 即可**。

同时，因为 $j$ 为负数，所以**将 $f$ 数组整体向右平移 $n$ 位**，方便操作。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+6;
int n, a[N], b[N];
int f[N<<1]; // 数组开 2 倍，方便整体平移 
int p[N]; // p[i] 表示 a[i] 在 b 中的位置
int ans;
int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		p[b[i]] = i;
	}
	for (int j = n; j <= (n<<1); ++j) { // 数组的初始化 
		f[j] = j-n;
	}
	for (int i = 1; i <= n; ++i) {
		int pos = p[a[i]]-i+n; // 需要特殊修改的位置 
		f[pos] = min(f[pos-1]+1, f[pos+1]);
	}
	ans = f[n]+n; // 注意全局需要加的 n！ 
	printf("%d", ans);
	return 0;
}
```

谢谢大家！

---

## 作者：zyb_txdy (赞：3)

题意简述：给定正整数 $n$ 和两个 $1 \sim n$ 的排列 $a$ 和 $b$，定义操作为删除 $a$ 的第一个元素，或删除 $b$ 的第一个元素，或在两个排列的第一个元素不等时，将两者都删除。求将 $a$，$b$ 变空的最少操作次数。

数据范围：$1 \le n \le 10^6$

分析：

感受一下，发现贪心肯定是不太行的。具体的，若我们设两个指针 $p_1$ 和 $p_2$ 分别指向 $a$ 和 $b$ 中已经被删除的最后一个元素，则若 $a_{p_1 + 1} = b_{p_2 + 1}$，则我们并不知道下一步是移动 $p_1$ 还是 $p_2$，而下一步的移动是会对未来的决策产生影响的。

那就可以考虑一下 dp，记 $f_{i,j}$ 表示消除了 $a$ 中的前 $i$ 个元素和 $b$ 中的前 $j$ 个元素所需要的最小操作次数，则：

$\begin{cases} {f_{i,j} = \min\{f_{i - 1,j},f_{i,j - 1}\} + 1} & a_i = b_j \\ {f_{i,j} = \min\{f_{i - 1,j - 1},f_{i - 1,j},f_{i,j - 1}\} + 1} & a_i \ne b_j \end{cases}$

~~于是我们可以把问题转换为一个网格图，图上有 $n$ 个左上到右下的边是不能走的。直观感受一下，从最左上到最右下的最短路径，不会比左上角到右下角的连线偏移太多，具体的最大偏移量大概是 $O(\sqrt{n})$ 的，于是我们得到了一个 $O(n\sqrt{n})$ 的算法。~~

忽略带删除线的部分，上面的那个 dp 的复杂度是 $O(n^2)$ 的，肯定过不了，于是考虑优化。

实际思考过程中，我们能发现 $a_i \ne b_j$ 时的转移式很丑，但是猜一下就可以感觉到，这时的转移式可以写成 $f_{i,j} = f_{i - 1,j - 1} + 1$。

证一下这个东西，也就是性质：**若某一个最优方案中，某一步指向 $a$ 和 $b$ 的指针为 $i$ 和 $j$，且 $a_i \ne b_j$，则必定可以构造另一个最优方案，满足这个最优方案中 $a_i$ 和 $b_j$ 同时删除**。

这个东西是直白的：如果第一个方案中在 $a_i$ 和 $b_j$ 这里执行了一次删除一个数的操作，那必定可以把这次操作放到前面，使得 $a_i$ 和 $b_j$ 被同时删掉。

这个性质看起来是没什么用的，似乎只能把转移方程式变得好看一点，可实际上呢？

考虑 $a_i \ne b_j$ 时 $f_{i,j}$ 的值是怎么转移来的，必定是在 $\{i,j\}$ 之前有 $\{i',j'\}$，满足 $a_{i'} = b_{j'}$，$i' - j' = i - j$ 且 $i'$ 是所有满足要求的 $i'$ 中最大的一个。

抛开实际不谈，我们假设在算 $f_{i,j}$ 的时候已经知道 $i'$ 和 $j'$ 是多少了，那显然就可以一步转移：

$$f_{i,j} = f_{i',j'} + (i - i')$$

再仔细想想，对于所有的 $\{i,j\}$，本质不同的 $\{i',j'\}$ 只有 $n$ 个，其实也就是满足 $a_{i'} = b_{j'}$ 的 $\{i',j'\}$ 的数量。

那就把状态 $f$ 裁剪一下：$f_i$ 表示原先状态的 $f_{i,j}$，其中 $j$ 满足 $a_i = b_j$。当然，对于每个 $i$，$j$ 是唯一的。这样就可以做到 $O(1)$ 转移。

现在的问题是对于任意一个 $\{i,j\}$，如何求出它所对应的 $\{i',j'\}$。容易发现这是好办的，我们拿一个 $g_{i' - j'}$ 存 $i'$，而 $g$ 是可以动态更新的。

实际实现中注意 $i' - j'$ 可能是负数，因此要给它加一个 $n$。

code：

```cpp
//#pragma GCC optimize (2)
#include <bits/stdc++.h>
//#include <windows.h>

using namespace std;

#define ll long long
#define mid (l + r >> 1)
#define lowbit(x) (x & -x)

const int N = 1e6 + 5, M = 2e6 + 5;

int n;
int a[N], b[N];
int buc[N], g[M];
// buc[i] 表示数组 b 中值 i 所在的下标
// g[i] 表示数组 a 中，满足 j - buc[a[j]] = i 的下标 j 
int f[N];
// f[i] 表示匹配完 a 数组的第 i 位，b 数组的第 buc[a[i]] 位的 answer

signed main() {
//	freopen("data.in", "r", stdin);
//	freopen("std.out", "w", stdout);
	
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	
	for (int i = 1; i <= n; ++i) buc[b[i]] = i;
	
	for (int i = 1; i <= n; ++i) {
		// 显然，buc[a[i]] 表示题解中 i 对应的 j
		// 这里的计算过程基于 "f[i][buc[a[i]]] = min(f[i - 1][buc[a[i]]], f[i][buc[a[i]] - 1]) + 1"
		// 以下计算 f[i - 1][buc[a[i]]]
		int tmp1, tmp2, cnt1, cnt2;
		tmp1 = n + i - 1 - buc[a[i]];
		if (g[tmp1] > 0 && g[tmp1] <= i - 1) cnt1 = f[g[tmp1]] + (i - 1 - g[tmp1]);
		else cnt1 = max(i - 1, buc[a[i]]);
		// -----
		// 以下计算 f[i][buc[a[i]] - 1]
		tmp2 = n + i - (buc[a[i]] - 1);
		if (g[tmp2] > 0 && g[tmp2] < i) cnt2 = f[g[tmp2]] + (i - g[tmp2]);
		else cnt2 = max(i, buc[a[i]] - 1);
		// -----
		f[i] = min(cnt1, cnt2) + 1;
		g[n + i - buc[a[i]]] = i; // 动态更新 g 
	}
	
	int tmp = 0;
	for (int i = n; i > 0; --i) {
		if (a[i] == b[i]) {
			tmp = i;
			break;
		}
	}
	
	cout << (f[tmp] + (n - tmp)) << endl;
	
	return 0;
}
```

---

## 作者：TMLY114514 (赞：3)

# 题解：P6820 [PA2012] Two Cakes
提供一种简单的实现方式。

本题是经典的双序列匹配模型，套路地设 $f_{i,j}$ 表示写到第一个排列的第 $i$ 个数和第二个排列的第 $j$ 个数的最短时间。

$a_i=b_j$ 时，$f_{i,j}=\min(f_{i-1,j},f_{i,j-1})+1$。

$a_i\ne b_j$ 时，$f_{i,j}=\min(f_{i-1,j},f_{i,j-1},f_{i-1,j-1})+1$。

发现对于确定的 $i$ 或 $j$，$f_{i,j}$ 有单调性。那么 $a_i\ne b_j$ 时的转移等价于 $f_{i,j}=f_{i-1,j-1}+1$。

考虑如何优化这一转移过程。显然第一种转移出现的次数不会超过 $n$ 次。在枚举 $i$ 转移的时候，可以发现，第二种转移可以视为把 $f_{i-1}$ 向右平移，然后全局 $+1$。此时只需再把 $a_i=b_j$ 的 $f_{i,j}$ 修改回第一个转移即可，复杂度是线性的。

## 代码

```cpp
#define N 1000010
int n,a[N],b[N],g[N<<1],*f=g+N,p[N];
int main(){
	read(n);
	for(int i=1;i<=n;++i)read(a[i]);
	for(int i=1;i<=n;++i)read(b[i]),p[b[i]]=i;
	for(int i=1;i<=n;++i)f[i]=i;//f[0][i]=i
	for(int i=1;i<=n;++i){
		--f;//f[i][j]=f[i-1][j-1]
		int j=p[a[i]];
		f[j]=min(f[j-1]+1/*层内转移直接+1*/,f[j+1]/*对应f[i-1][j]*/);
	}
	write(f[n]+n);//全局加了n次
```

---

## 作者：awapwq233 (赞：2)

## P6820 Two Cakes 题解

[题意](https://www.luogu.com.cn/problem/P6820)：两个长为 $n$ 的排列 A 和 B，同时从左往右写，一个时间内不能同时写相同的数，最小化总用时并输出。$n \leq 10^6$。

不可能贪心，直接朴素 dp：设 $f_{i,j}$ 为 A 写完第 $i\sim n$ 位，B 写完第 $j\sim n$ 位的最小用时，显然有转移方程

$$f_{i,j} = \begin{cases}f_{i+1,j+1}+1\quad a_i \neq b_j\\\min\left\{f_{i+1,j}, f_{i,j+1}\right\}+1\quad a_i=b_j\end{cases}$$

显然的，这样的时间复杂度是 $O(n^2)$ 的，必然超时；所以考虑优化。

注意到，占时间复杂度的大头是第一种情况，第二种情况只会出现 $n$ 次（记忆化搜索即可），不是主要优化对象，那么我们考虑能否优化第一种情况？

具体的，我们发现可以找到这样的 $k$，使得 $\forall p \in [i, i + k], q\in [j, j + k]$，有 $ a_p \neq b_q$，这样便可以连续按第一种情况转移 $k$ 次，大大优化了时间复杂度。

于是我们可以记录 $a_i=b_j$ 时下标的差，即 $i-j$，放进 `vector` 后排序序号，转移时二分查找即可找到满足条件的 $k$，总时间复杂度 $O(n\log n)$。

Code
```cpp
int n, a[maxm], b[maxm], pos[maxm], dp[maxm];
vector<int> v[maxm << 1];
int f(int x, int y)
{
    if(x > n) return n - y + 1;
    if(y > n) return n - x + 1;
    if(a[x] == b[y])
        return dp[x] != -1 ? dp[x] : dp[x] = qmin(f(x + 1, y), f(x, y + 1)) + 1;
    int t = n + x - y;
    int pos = lower_bound(v[t].begin(), v[t].end(), x) - v[t].begin();
    if(pos > int(v[t].size()) - 1)
        return qmax(n - x + 1, n - y + 1);
    int k = v[t][pos];
    return f(k, y - x + k) + k - x;
}
signed main()
{
    memset(dp, -1, sizeof(dp));
    F(i, 1, n = readint()) 
        pos[a[i] = readint()] = i;
    F(i, 1, n) 
        v[n + pos[b[i] = readint()] - i].push_back(pos[b[i]]);
    F(i, 1, n << 1)
        sort(v[i].begin(), v[i].end());
    write(f(1, 1));
    return 0;
}
```

---

## 作者：banned_wanyb (赞：2)

[P6820](https://www.luogu.com.cn/problem/P6820)

显然，这是一个 dp 的题，$dp_{i,j}$ 表示左手写第 $i$ 个数，右手写第 $j$ 个数的最短时间。

于是有以下转移方程：

$$dp_{i,j}=
\begin{cases}
\min\{dp_{i,j-1},dp_{i-1,j}\}+1,(a_i=b_j)\\
dp_{i-1,j-1}+1,(a_i \neq b_j)
\end{cases}
$$

但是 $n \le 10^6$ 显然过不了。

这里考虑优化，有两种优化思路，一种是从状态上优化，一种是从转移上优化。

为了转移 $dp_{i,j}$ 我们并没有引入其它的量，所以转移是 $O(1)$ 的，时间都用了枚举状态了。

我们发现其实有很多量求出来是没有用的，就是按照这样下去，一定不能成为最优解，例如，样例一中的 $dp_{3,0}$。

如何省略这样的量的计算呢。

从贪心的角度讲，我们希望两只手同时写尽量多。

即对于 $dp_{i,j}$ 找到尽量大的 $k$ 使得 $a_{i-k-1} \neq b_{i-k-1}$，那么 $dp_{i,j}=dp_{i-k-1,j-k-1}+k$。

也就是，只要按照 $a_i=b_j$ 这样的 ${i,j}$ 划分即可。

如何找到尽量大的 $k$，有一点很重要，就是你无论你 $k$ 有多少，两个下标的差都不变，于是我们可以通过记录差来找到 $k$。

对于一对 $(i,j)$ 满足 $a_i=b_j$，我们定义一个 $g_{x,0}=i,g_{x,1}=f_i$ 其中 $x=i-j+n,f_i=dp_{i,j}$。

于是对于一个 $dp_{r,s}$ 的 $k$ 就是 $r-g_{r-s+n,0}$ 再加上 $g_{r-s+n,1}$，就是 $dp_{r,s}$。 

而 $a_i=b_j$ 这样的数是 $n$ 个，所以时间复杂度是 $O(n)$。


---

## 作者：sodalyghat (赞：1)

### 分析
容易写出一个朴素方程，设 $f_{i,j}$ 代表 $a$ 序列写到第 $i$ 个数，$b$ 序列写到第 $j$ 个数花费的最小代价。当 $a_i=b_j$ 时，$f_{i,j}=\min(f_{i,j-1},f_{i-1,j})+1$，否则 $f_{i,j}=f_{i-1,j-1}+1$。然后这个方程有个特点，就是大部分值都是从上一个版本继承过来的，只有 $n$ 个值需要单独修改，因此可以上整体 DP 做。当然可以用平衡树，但是代码又臭又长，对于这道题，直接用数组维护就可以了，具体实现代码有注释。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 1000005;
	int a[MAXN], b[MAXN], t[MAXN], wz[MAXN];
	//不用平衡树维护，数组倍长一下就好
	int f[MAXN << 1];
	int main(){
		int n;
		scanf("%d", &n);
		for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
		for(int i = 1;i <= n;i++){
			scanf("%d", &b[i]);
			t[b[i]] = i;
		}
		for(int i = 1;i <= n;i++) wz[i] = t[a[i]];
		//f[x][y] = f[x - 1][y - 1] + 1 (a[x] != b[y])
		//	      = min(f[x][y - 1], f[x - 1][y]) + 1; (a[x] == b[y])
		//因为ab都是排列，所以下面的情况总共只有n种
		//所以可以整体DP，每次单独处理一下情况2
		//以x为阶段，下标是y，先处理出x=0的初始情况
		for(int i = n + 1;i <= 2 * n;i++){
			f[i] = i - n;
		}
		//因为情况1和2后面都有一个+1，就不用随时维护真正的f值了，+1当作常数带着就好
		//st是当前x对应的f数组开始的位置，因为每次x+1，st也会跟着变
		int st = n + 1;
		for(int i = 1;i <= n;i++){
			st--;
			f[st] = 0;
			f[wz[i] + st - 1] = min(f[wz[i] + st - 1 - 1] + 1, f[wz[i] + st - 1 + 1]);
		}
		printf("%d", f[n] + n);
		return 0;
	}
}
int main(){
	return Luo_ty::main();
}//International Milan is the best team.
//Why are you beaten by A.C.Milan?
```

---

## 作者：cryozwq (赞：1)

被这道题教育了/kk

首先有个很暴力的想法是设 $f_{i,j}$ 为 $a$ 数列选前 $i$ 个，$b$ 数列选前 $j$ 个所需步数。

显然可得


$f_{i,j}=\min(f_{i-1,j},f_{i,j-1})+1$

特别的如果 $a_i \neq b_j$，则:

$f_{i,j}=\min(f_{i,j},f_{i-1,j-1}+1)$

显然不会在 $a_i \neq b_j$ 的时候按第一项转移，所以此时 $f_{i,j}=f_{i-1,j-1}$。

注意到 $a_i=b_j$ 只存在 $n$ 个，即最多会出现 $n$ 次第一种转移。

那么考虑能不能把第二种转移写成从某个 $a_i=b_j$ 转移过来的状态，这样就可以直接记搜。

事实上是可以的，我们设 $t$ 表示在转移 $f_{i,j}$ 的时候，$i,j$ 之前最后一个 $a_{i-t-1}=b_{j-t-1}$。那么在此之后就会一直选两个，所以可以写成：

$f_{i,j}=f_{i-t-1,j-t-1}+t$。

那么我们只需要计算 $a_i=b_j$ 的 $n$ 个状态和为了计算这 $n$ 个状态所需要计算的 $2n$ 个 $a_i \neq b_j$。这可以使用记搜实现。

然后是如何计算 $t$ ，可以二分，注意到 $i,j$ 确定的时候 $a_k$ 会和 $b_{k-(i-j)}$ 匹配，所以开 $2n$ 个 vector 记录每个差存在的 $a_i=b_j$ 即可二分，复杂度 $O(n \log n)$，当然也可以进一步优化到 $O(n)$ ，具体参考其他题解。

---

## 作者：Yansuan_HCl (赞：0)

考虑每一步分别在两个串写到第 $i$ 和第 $j$ 个字符，每一步的状态记作 $(i,j)$。要从 $(0,0)$ 走到 $(n,n)$。则每次的决策包括：

1. $(i,j)\to(i+1,j+1), s_{i+1} \neq t_{j+1}$；
1. $(i,j)\to(i+1,j)$；
1. $(i,j)\to(i,j+1)$。

只有在 $s_i=t_j$ 时第一种转移不能进行，这样的关键 $(i,j)$ 有 $n$ 个。一种直观的最优情形是，如果能沿着主对角线则答案有最小值 $n$。考虑一点贪心，如果第一种决策能进行，则一定进行第一种操作：如果已经偏离了主对角线，则一定能调整决策使得路径不必在关键点或边界之前提前转弯。

设计 DP $f(i,j)=\max\{f(i-1,j-1)[s_i \neq t_j],f(i,j-1),f(i-1,j)\}+1$。则根据结论，则 $(i,j)$ 不在关键点时一定进行第一种转移，可以把连续的转移缩起来，这样连续的转移在同一条斜线上。只需提出左边界与上边界的点、关键点、被关键点更新的点进行 DP。可以按照所在的反斜线即 $i+j$ 排序转移。

---

## 作者：Rain_chr (赞：0)

一种最短路解法，虽然本质还是优化 DP 罢了。

先写出 DP 状态转移方程，设 $f_{i,j}$ 为第一个序列消到 $i$，第二个序列消到 $j$ 的最小次数。转移方程即为：

若 $a_i=b_j$，则：

$$f_{i,j}=\min\{f_{i,j-1}+1,f_{i-1,j}\}+1$$

否则：

$$f_{i,j}=\min\{f_{i,j-1}+1,f_{i-1,j},f_{i-1,j-1}\}+1$$

观察什么样的状态是特殊的，显然是 $a_i=b_j$ 时的 $f_{i,j}$，因为对于这种状态我们必须考虑是删掉 $a$ 的开头还是 $b$ 的开头，其他情况必然是两个一起删。

以 $a_i=b_j$ 的状态 $(i,j)$ 为点，分别考虑删除 $a$ 的开头和 $b$ 的开头会转移到的状态是哪个，然后向这两个点连边，边权为把序列从当前状态通过不断删除开头删到下一个状态需要的操作数。初始状态设为 $(0,0)$，终止状态设为 $(n+1,n+1)$，跑一个最短路即可。

连边可以到序枚举第一个序列中的位置 $x$，记录对应元素在第二个序列中的位置 $y$，然后可以发现删除 $x$ 之后不断删除开头直到开头相等的位置 $(p,q)$ 满足 $x-y+1=p-q$，这个可以用哈希表维护。删除 $y$ 同理。


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int N=1e6+10;
int a[N],b[N],rk[N];
vector<pair<int,int> > g[N];
int dis[N];
int n;
int w(int x,int y)
{
    x=n-x+1,y=n-y+1;
    return max(x,y);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i],rk[b[i]]=i;
    cc_hash_table<int,int> mp;
    for(int i=n;i;i--)
    {
        //删掉上面的
        int k=i-rk[a[i]];
        if(mp.find(k+1)!=mp.end()) g[a[i]].push_back(make_pair(rk[mp[k+1]]-rk[a[i]]+1,mp[k+1]));
        else g[a[i]].push_back(make_pair(w(i+1,rk[a[i]])+1,n+1));
        if(mp.find(k-1)!=mp.end()) g[a[i]].push_back(make_pair(rk[mp[k-1]]-rk[a[i]],mp[k-1]));
        else g[a[i]].push_back(make_pair(w(i,rk[a[i]]+1)+1,n+1));
        mp[k]=a[i];
    }
    if(mp[0]) g[0].push_back(make_pair(rk[mp[0]]-1,mp[0]));
    else g[0].push_back(make_pair(n,n+1));
    memset(dis,0x3f,sizeof(dis));
    std::priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,0));
    while(q.size())
    {
        pair<int,int> x=q.top();
        q.pop();
        if(dis[x.second]<=x.first) continue;
        dis[x.second]=x.first;
        for(pair<int,int> to:g[x.second]) q.push(make_pair(x.first+to.first,to.second));
    }
    cout<<dis[n+1];
	return 0;
}
```

---

