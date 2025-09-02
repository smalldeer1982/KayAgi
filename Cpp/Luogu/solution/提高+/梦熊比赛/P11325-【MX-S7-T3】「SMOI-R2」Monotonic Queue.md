# 【MX-S7-T3】「SMOI-R2」Monotonic Queue

## 题目背景

原题链接：<https://oier.team/problems/S7C>。

## 题目描述

给定一个正整数 $n$ 和 $n$ 个整数 $c_1, \ldots, c_n$（这些数可能为负），以及一个 $1 \sim n$ 的排列 $(a_1, \ldots, a_n)$。

为了考验朋友小 L 的能力，你设计了一道这样一道题目：

> 给定 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$，它们满足以下条件：  
> - $1 \leq l_i \leq r_i \leq n$；  
> - $l_1 \leq l_2 \leq \dots \leq l_n$；  
> - $r_1 \leq r_2 \leq \dots \leq r_n$。  
>
> 对于每个区间 $[l_i, r_i]$，小 L 需要求出 $a_{l_i \sim r_i}$ 中最大值的位置，记为 $b_i$。

小 L 准备使用**单调队列**来高效地完成这个题目。他的算法核心伪代码如下：

---

![](https://cdn.luogu.com.cn/upload/image_hosting/15a9sbx6.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

---

对应的 C++ 实现代码如下：

```cpp
deque<int> Q;
l[0] = r[0] = sum = 0;
for (int i = 1; i <= n; i++) {
    for (int j = r[i - 1] + 1; j <= r[i]; j++) {
        while (!Q.empty() && a[Q.back()] < a[j]) {
            sum = sum + c[Q.back()];
            Q.pop_back();
        }
        Q.push_back(j);
    }
    while (Q.front() < l[i]) Q.pop_front();
    b[i] = Q.front();
}
```

你发现小 L 一遍就通过了这道题目，但是你突然对 `sum` 的值非常感兴趣。现在你想知道，在所有满足条件的 $n$ 个区间的组合中，算法结束后 `sum` 的最大值是多少。

## 说明/提示

**【样例解释 #1】**

若所有区间都为 $[5,5]$，则算法结束后 `sum` 的值为 $308$。可以证明没有使 `sum` 更大的方案。

**【样例解释 #2】**

若所有区间都为 $[1,1]$，则算法结束后 `sum` 的值为 $0$。可以证明没有使 `sum` 更大的方案。

**【样例解释 #3】**

若 $5$ 个区间分别为 $[2,2]$、$[2,2]$、$[2,4]$、$[2,4]$、$[2,4]$，则算法结束后 `sum` 的值为 $396$。可以证明没有使 `sum` 更大的方案。

**【样例 #4】**

见附件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该组样例满足测试点 $2\sim 5$ 的约束条件。

**【样例 #5】**

见附件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该组样例满足测试点 $8\sim 12$ 的约束条件。

**【样例 #6】**

见附件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该组样例满足测试点 $15\sim 16$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$2\le n\le 5\times 10^5$，$\lvert c_i \rvert\le 10^9$，$1 \le a_i \le n$，$(a_1, \ldots, a_n)$ 为 $1\sim n$ 的排列。

|测试点编号|$n\le $|特殊性质|
|:-:|:-:|:-:|
|$1$|$6$|无|
|$2\sim 5$|$15$|无|
|$6\sim 7$|$5\times 10^5$|A|
|$8\sim 12$|$5000$|无|
|$13\sim 14$|$2\times 10^5$|B|
|$15\sim 16$|$2\times 10^5$|C|
|$17\sim 19$|$10^5$|无|
|$20\sim 25$|$5\times 10^5$|无|

- 特殊性质 A：满足 $c_i > 0$ 的 $i$ 不超过 $1$ 个。
- 特殊性质 B：满足 $c_i < 0$ 的 $i$ 不超过 $2$ 个。
- 特殊性质 C：满足 $c_i < 0$ 的 $i$ 不超过 $10$ 个。

## 样例 #1

### 输入

```
5
-190 133 210 155 -442
1 3 2 4 5```

### 输出

```
308```

## 样例 #2

### 输入

```
10
-205 -268 -487 -112 -82 -330 153 133 -219 -157
5 6 7 9 2 1 4 10 3 8```

### 输出

```
0```

## 样例 #3

### 输入

```
5
-288 479 205 -310 -66
1 3 2 4 5```

### 输出

```
396```

# 题解

## 作者：cff_0102 (赞：28)

赛时思路。

不难发现前一个区间的 $l$ 可以且仅可以做到约束在做后一个区间时踢队尾最多踢到哪里（因为这是上一次踢队头踢到的位置），这样就可以通过上一个 $l$ 来控制当前踢队尾踢到最优处就停下。而对于第一个区间，程序必须从序列的**最左端**开始加数。下文中区间的左端点指的是踢队尾应该踢到哪里。

考虑 dp。设 $dp_{i,0/1}$ 表示最后一个区间右端点选到 $i$，这个区间的左端点有（$0$）或没有（$1$）要求必须是 $1$ 的时候（或者说，是否是第一个区间）的最大答案。

转移时模拟一个单调栈（或者说不踢队头的单调队列），每次从单调栈（队尾）踢出一个数之后就可以用区间左端点取到这里，右端点取到 $i$ 的答案拿来更新 $dp_{i,1}$。最后再用左边第一个大于 $a_i$ 的数的答案更新 $dp_{i,0/1}$。记得 $dp_{i,0}$ 只能从 $dp_{j,0}$ 转移，而 $dp_{i,1}$ 则可以从 $dp_{j,0}$ 和 $dp_{j,1}$ 转移。答案是所有 $dp_{i,1}$ 的最大值。代码里有具体的转移式，结合代码更好理解。

注意初始化的问题：$dp_{i,1}$ 刚开始必须从 $dp_{j,0}$ 转移过来才是有效的，所以没有从 $dp_{j,0}$ 转移而来的 $dp_{i,1}$ 刚开始应该设为无穷小。

因为转移过程是模拟一个单调栈，所以复杂度是 $O(n)$ 的。

赛时代码加注释：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int a[N],c[N],s[N];
int dp[N][2];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i],s[i]=s[i-1]+c[i];
	for(int i=1;i<=n;i++)cin>>a[i];
	deque<int>q;//exactly a monotonic stack 
	for(int i=1;i<=n;i++){
		dp[i][1]=-1e18;
		while(!q.empty()&&a[q.back()]<a[i]){
			dp[i][1]=max(dp[i][1],s[i-1]-s[q.back()-1]+max(dp[q.back()][0],dp[q.back()][1]));
			//s[i-1]-s[q.back()-1]：从 i-1 踢到 q.back()，要把这里面的所有 c 加起来
			//max(dp[q.back()][0],dp[q.back()][1]))：左端点设到了 q.back()，这样才会踢到这里停下来；上一个右端点选择 q.back()，因为它不能小于 q.back()，而后面的点全部已经转移或者踢完了
			q.pop_back();
		}
		if(!q.empty())dp[i][1]=max(dp[i][1],s[i-1]-s[q.back()]+max(dp[q.back()][0],dp[q.back()][1]));
		if(!q.empty())dp[i][0]=s[i-1]-s[q.back()]+dp[q.back()][0];//中间踢的加起来，前面的转移过来
		else dp[i][0]=s[i-1];//一直踢到开头
		dp[i][1]=max(dp[i][1],dp[i][0]);//没有要求必须选最左边 ≠ 我不选最左边
		q.emplace_back(i);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i][1]);
	}
	cout<<ans;
	return 0;
}
```

---

上面是赛时的思路，而实际上本题的 dp 可以优化到不开两倍空间。

把 $dp_{i,0}$ 去掉。$dp_{i}$ 仍然需要初始化为无穷小，这样可以保证 $dp_i$ 在取最大值的时候只会从前面左端点到达 $1$ 的状态转移，因为刚开始有且只有 $dp_0=0$。这样，中间的主体代码就可以优化到更短。

另外，将 $a_0$ 改为 $n+1$ 并在一开始将 $0$ 放进 $q$ 中就可以避免对 $q$ 是否为空的判断，使代码更加简短。

```cpp
a[0]=n+1;q.emplace_back(0);
int ans=0;
for(int i=1;i<=n;i++){
	dp[i]=-1e18;
	while(a[q.back()]<a[i]){
		dp[i]=max(dp[i],s[i-1]-s[q.back()-1]+dp[q.back()]);
		q.pop_back();
	}
	dp[i]=max(dp[i],s[i-1]-s[q.back()]+dp[q.back()]);
	q.emplace_back(i);
    ans=max(ans,dp[i]);
}
cout<<ans;
```

---

## 作者：Leo_SZ (赞：12)

树形 DP。

对于排列中的某一个位置 $y$，我们设 $x$ 是最大的满足 $x \lt y$ 且 $a_x \gt a_y$ 的位置。特别的，如果不存在这样的 $x$，则令 $x$ 为 $0$。$x$ 容易用单调栈求出。

容易发现，如果 $x$ 被从单调队列的队尾弹出，而不是队头，那么 $y$ 也一定是被从单调队列的队尾弹出。

然后，我们把 $y$ 在树上的父亲设为 $x$，就得到了一棵 $n+1$ 个节点的树。

例如，对于样例 $2$，我们建出来的树长这样：

![这里是图片](https://cdn.luogu.com.cn/upload/image_hosting/trekvjdd.png)

这棵树存在这样的性质：如果某个点对答案造成了贡献，则以该点为根的子树里的所有的点都对答案造成了贡献。

但是，叶节点是特殊的。首先，由题可知，单调队列一旦被从队尾删空，就一定会加入一个新的点，使得队列非空。另外，类似样例 $2$，并不是所有的点都会被加入单调队列，只有一个前缀会被加入。

根据以上两点，叶节点对答案造成的贡献有这样的规则：存在一个整数 $k$，所有编号小于等于 $k$ 的叶节点都对答案造成贡献，所有编号大于 $k$ 的叶节点都不对答案造成贡献。

此外，最右侧的链由于到结束也还在单调队列中，也没法对答案造成贡献。

例如对于上图，可能的对答案造成贡献的组合只有以下几种：

```cpp
1
1 2
1 2 3
1 2 3 6 5
1 2 3 6 5 7 4
1 2 3 6 5 7 4 9
1 2 3 6 5 7
1 2 3 6 5 7 9
1 2 3 6
1 2 3 6 7
1 2 3 6 7 9
```

于是，我们有了一个树形 DP。

设 $f_x$ 为以 $x$ 为根的子树，叶节点必须都选的最大的 $c$ 之和，$g_x$ 为以 $x$ 为根的子树，有一半叶节点选则，有一半叶节点不选的最大的 $c$ 之和。

如果不选 $x$，对于 $x$ 的每个子节点 $y$，有转移 $\begin{cases}g_x \gets \max \{g_x, f_x + g_y \} \\ f_x \gets \max \{f_x, f_x + f_y \} \end{cases}$。
注意有先后顺序。

如果选 $x$，则有 $\begin{cases}g_x \gets \max \{g_x, \sum_{y \in \texttt{subtree}_x} c_y \} \\ f_x \gets \max \{f_x, \sum_{y \in \texttt{subtree}_x} c_y \} \end{cases}$。

时间复杂度 $O(n)$。

代码很短：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Maxn 500005
using namespace std;
int n,a[Maxn],c[Maxn];
stack<int> q;
vector<int> e[Maxn];
LL f[Maxn],g[Maxn],all[Maxn];

void dfs(int x){
	all[x] = c[x];
	if(e[x].empty()){
		f[x] = c[x];
		g[x] = max(0, c[x]);
		return;
	}
	for(int y : e[x]){
		dfs(y);
		all[x] += all[y];
		g[x] = max(g[x], f[x] + g[y]);
		f[x] += f[y];
	}
	f[x] = max(f[x], all[x]);
	g[x] = max(g[x], all[x]);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",c+i);
	for(int i=1; i<=n; i++) scanf("%d",a+i);
	
	q.emplace(0);
	for(int i=1; i<=n; i++){
		while(q.size() > 1 && a[q.top()] <= a[i]){
			q.pop();
		}
		e[q.top()].emplace_back(i);
		q.emplace(i);
	}
	while(!q.empty()){
		c[q.top()] = 0; q.pop();
	}
	
	dfs(0);
	printf("%lld\n", g[0]);
	return 0;
}
```

---

## 作者：Lgx_Q (赞：11)

### $n\le 6$

考虑爆搜 $l_{1\dots n},r_{1\dots n}$ 的取值方案，期望得分 $\mathtt {4pts}$。

### $n\le 15$

注意到队列相当于一个 $1\sim n$ 的数字集合，设 $f_{i, S}$ 表示考虑了 $l_{1\dots i}, r_{1\dots i}$ 的取值，队列里数的集合为 $S$ 的答案。

注意到 $r_i = \max\limits_{x\in S} x$，所以 $r_{i + 1}$ 的下界是确定的。而 $l_{i + 1}$ 相当于是从队列前面删掉若干个数，枚举 $l_{i + 1}, r_{i + 1}$ 即可转移。

时间复杂度 $\mathcal O(n^3 2^n)$，期望得分 $\mathtt {20pts}$。

### 特殊性质 A

设 $p$ 为唯一一个 $c_p > 0$ 的位置。如果 $c_p$ 没有贡献，令所有区间都取 $[1,1]$，答案为 $0$。

设 $R_i$ 为 $a$ 中 $a_i$ 右边第一个大于它的数的位置，若不存在则 $R_i = n + 1$。发现 $c_p$ 有贡献当且仅当存在一个 $i$ 满足 $l_i \le p$ 且 $r_{i + 1} \ge R_p$，我们容易设计出区间组合方案：$[1,2],[2,3],[3,4],\dots,[p - 1, p],[p, p], [p + 1, R_p], [p + 2, R_p], \dots , [R_p, R_p] ,[R_p, R_p], [R_p, R_p],\dots$

时间复杂度 $\mathcal O(n)$，期望得分 $\mathtt {28pts}$。

### $n\le 5000$

延续特殊性质 A 的做法，$c_i$ 对答案有贡献当且仅当存在一个 $j$ 满足 $l_j\le i$ 且 $R_i \le r_{j + 1}$。

注意到若存在一个 $i$ 满足 $l_i = l_{i + 1}$，那么区间 $[l_{i + 1}, r_{i + 1}]$ 是没有用的，可以去掉。所以可以钦定所有区间满足 $l_i = i$。

此时 $c_i$ 有贡献的条件变为 $R_i \le r_{i + 1}$，不妨设 $r'_i = r_{i + 1}$，可以发现满足以下条件的 $r'_{1\dots n - 1}$ 都是可以取到的：

+ 对于所有 $i(1\le i\le n - 1)$ 满足 $i + 1\le r'_i\le n$；

+ $r'_1\le r'_2 \le \dots \le r'_{n - 1}$。

设 $f_{i, j}$ 表示考虑了 $r'_{1\dots i}$ 的取值，且 $r'_i = j$ 的最优答案，转移：$f_{i, j} = [j\ge R_i]c_i + \max\limits_{k = i} ^ j f_{i - 1, k}$。

注意我们不一定要考虑所有数，所以答案应为 $\max\limits_{i = 1} ^ {n - 1} f_{i, i + 1}$。

时间复杂度 $\mathcal O(n ^ 2)$，期望得分 $\mathtt {48pts}$。

### 特殊性质 C

注意到若 $c_i \ge 0$，那么可以直接取 $r'_i=r'_{i + 1}$。

所以 $r'_{1\dots n - 1}$ 的相同连续段数量 $\le 10$，可以直接 DP。

时间复杂度 $\mathcal O(Dn)$，其中 $D = 10$，期望得分 $\mathtt {64pts}$。

### $n\le 10^5$

考虑使用线段树维护 $f_{i,\_}$ 数组。由于需要前缀 max 优化，所以我们实时维护其前缀 max 数组。

考虑贡献的更新，每次相当于对位置 $[R_i, n]$ 进行区间加 $c_i$。

当 $c_i$ 为负数时，需要重新维护单调性，考虑在 $[R_i, n]$ 中二分出第一个 $\ge f_{i, R_i - 1}$ 的位置 $p$，然后将 $[R_i, p - 1]$ 覆盖成 $f_{i, R_i - 1}$。

每次二分都单点查询一次，时间复杂度 $\mathcal O(n\log ^ 2n)$，期望得分 $\mathtt {76pts}$。

### $n\le 5\times 10^5$

考虑在线段树上二分，区间 $[R_i, n]$ 会在线段树上划分为若干个小区间，其中只会有一个小区间需要继续二分下去，其他小区间可以直接更新并返回。继续二分也至多会进行 $\mathcal O(\log n)$ 次，所以总时间复杂度为 $\mathcal O(n\log n)$，期望得分 $\mathtt {100pts}$。

### $\mathcal O(n)$ 做法

场上有人爆标了，特地来补充一下。

考虑对于 $i(1\le i\le n)$，设所有 $R_j = i$ 的 $j$ 分别为 $j_1, j_2, \dots, j_k$，那么会有一个分界点 $x(1\le x\le k)$ 满足 $r'_{j_{x - 1}} < i$ 且 $r'_{j_x} \ge i$。由于 $r'$ 不降，所以 $r'_{j_x \dots i}$ 都 $\ge i$。

发现 $R_{j_x}, R_{j_x + 1}, \dots R_{i - 1}$ 都不超过 $i$，所以 $j_x \sim i - 1$ 这一段都是有贡献的。

设 $f_i$ 表示考虑了前 $i$ 个数中 $R_j\le i$ 的所有 $j$ 的答案。

先用单调栈求出 $j_1, j_2, \dots, j_k$，然后枚举分界点 $x$，有转移：$f_i = \min\limits_x\{f_{j_x} + \sum\limits_{p = j_x} ^ i c_p\}$。

时间复杂度 $\mathcal O(n)$。

---

## 作者：yuanruiqi (赞：10)

考虑特殊性质 A，令 $c_x\gt 0$，目标则是希望在得到 $c_x$ 的贡献的同时尽量减少 $c_i(i\ne x)$ 的影响，策略为从 $1$ 到 $x$ 加入一个同时删除上一个，当队列有且仅有 $x$ 一个位置，这时只加入不删除，直到第一个位置 $a_i\gt a_x,i\gt x$ 出现，它会将 $[x,i)$ 内所有还在队列的位置弹出并计入答案。

这个过程启发我们关注队列中只有一个元素的时刻，令队列有且仅有 $i$ 的最优代价为 $f_i$。则转移分为两种：

- $c_i$ 不贡献到答案，可以在加入 $i+1$ 时直接删除 $i$，即 $f_i\to f_{i+1}$。要求 $a_{i+1}\lt a_i$。

- $c_i$ 贡献到答案，这时至少要等到 $i$ 右侧第一个 $a_j\gt a_i$ 才能移动左端点，令这个位置为 $j=nxt_i$。事实上 $a_j$ 一定为 $\max_{x\in[i,j]}a_x$，所以队列会弹出直到只存在 $j$。有转移 $f_i\to f_j$。

显然最终答案为 $\max f_i$。$nxt_i$ 可以用一次单调栈预处理出来，总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 500000 + 10;
i64 c[maxn], a[maxn], g[maxn];
i64 f[maxn];
int s[maxn], p[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i=1;i<=n;++i) cin >> c[i];
    for (int i=1;i<=n;++i) cin >> a[i];
    memset(f, 0xcf, sizeof(f));
    f[1] = 0;
    i64 ans = 0;
    for (int i=n,top=0;i>=1;--i)
    {
        while (top && a[s[top]] < a[i]) --top;
        if (top) p[i] = s[top];
        s[++top] = i;
    }
    for (int i=1;i<=n;++i) g[i] = c[i] + g[i - 1];
    for (int i=1;i<=n;++i)
    {
        ans = max(ans, f[i]);
        f[i + 1] = max(f[i + 1], f[i] + (a[i + 1] > a[i] ? c[i] : 0));
        if (p[i]) f[p[i]] = max(f[p[i]], f[i] + g[p[i] - 1] - g[i - 1]);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：chenly8128 (赞：4)

## 简要题意

求区间 $\left [ l,r \right ]$ 的 $\sum_{i = l}^r c_i \times [\sum_{j = i+1}^r [a_i < a_j] > 0]$ 最大值。

## 题解
### 一个很重要的规律

如果加入一个区间 $\left [ l,l \right ]$，且 $a_l < a_{l-1}$ 那么可以清空“单调队列”，前面的答案对后面的答案没有影响。
所以 $a_{l-1} > a_l$ 时可以用后面的答案和前面答案的总和来更新总答案。

### 暴力做法

枚举右边界 $r$，然后从右往左枚举左边界 $l$，记录目前经过的 $a$ 的最大值。然后判断每一个值是否小于最大值，累加就能算出目前的答案。如果 $a_{i-1} > a_i$，就更新答案。
时间复杂度 $O(n^2)$，预期 45 pts。

### 优化
~~题目里面都告诉你了，~~ 单调队列优化。
模拟单调队列入队的过程，记录每一个数删除的数字的 $c$ 值总和。然后通过这个总和的累加快速更新当前答案。如果 $a_{i-1} > a_i$，就更新总的答案。

复杂度 $O(n)$。

### 代码
不懂都看代码吧，动态规划计算过程很清楚。

```cpp

// Author: chenly8128
// Created: 2024-11-24 12:15:52

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
const int MAXN = 5e5+10;
int n,a[MAXN];
ll c[MAXN],dp[MAXN];
ll res[MAXN];  // 记录每一个数删除的数字的 c 值总和
deque <int> d;  // 模拟单调队列
bool b[MAXN];
int main (void) {
	n = read();
	for (int i = 1;i <= n;i++)
		c[i] = read();
	for (int i = 1;i <= n;i++)
		a[i] = read();
	ll ans = 0;
	for (int i = 1;i <= n;i++) {
		dp[i] = -1e17;
		ll sum = 0;
		if (a[i] < a[i-1]) b[i] = true;
		while (!d.empty() && a[i] > a[d.back()]) {
			sum += c[d.back()];
			if (b[d.back()]) {
				b[i] = true;
				dp[i] = max(dp[i],sum + dp[d.back()]);  // 转移
			}
			sum += res[d.back()];
			d.pop_back();
		}
		res[i] = sum;
		dp[i] = max(dp[i],sum + (!d.empty() ? dp[d.back()] : 0));  // 转移
		ans = max(dp[i],ans);
		d.push_back(i);
	}
	printf ("%lld\n",ans);
	return 0;
}
```

---

## 作者：hxhhxh (赞：2)

怎么大家都是 dp，来一个贪心（？）题解。

## 题意

有点复杂，自己看题面。

最终 `sum` 是所有通过右边弹出的元素的 $c$ 的和。

## 思路

下文中，称 `deque` 的 `front` 为左边/前面。

观察题面中的代码，发现其实不需要管具体的 $l_i,r_i$，而是可以理解为有若干次操作，每次让 $r\gets r+1$ 或 $l\gets l+1$，要求 $l\leq r$，然后做单调栈的 push_back（可能带有 pop_back） 或者 pop_front。

再做转化，变成选择一个 $1\leq p \leq n$，指定一组不降的 $a_{1\sim p}$，然后重复 $p$ 次，每次令 $r\gets r+1$，然后令 $l\gets a_r$。这里的 $l\gets l+1$ 和 $r\gets r+1$ 同样也做单调栈操作。

先考虑如何算 $a_i=1$ 的贡献。发现这样的话没有 pop_front 操作，直接做一遍单调栈即可，答案是每个前缀的 $\max$。

然后观察 pop_front 操作起到了什么作用。发现它相当于每次 push 完后，删去单调栈的一个前缀（不能删空）。那么我们可以直接把这个操作放到 push 操作的弹栈过程中，每次从后面弹出时（除了每轮弹出的第一个元素，这是因为不能删空），你可以放弃这次弹出，改为直接把栈删空。

此后由于不存在 pop_front 操作，直接称 pop_back 为弹出。

之后我们可以开始贪了。每次弹出一个元素（设之为 $x$）的时候，如果 $c_x$ 非负，我们直接弹出它一定不亏。否则 $c_x$ 是负的，此时如果我们**只**弹出 $x$ 肯定时亏的，我们选择弹出它**只**可能因为在未来的某一时刻（不一定是这一次 $r\gets r+1$ 导致的弹出）还要弹出**此时**的单调栈更左的元素，也就一定会弹出前一个元素（设之为 $y$，如果不存在 $y$ 那么弹 $x$ 肯定亏）。那么我们可以直接令 $c_y\gets c_y+c_x$，意思是如果需要弹出 $y$，那么弹出 $x$，否则不弹出 $x$。在不弹出 $y$ 的情况下，不弹出 $x$ 和删空栈是等价的，所以这样写和原问题是等价的。

模拟这个过程即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,c[500005],ans,a[500005],s;
deque<int>q;//用 stack 就行了 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		int op=0;
		while(q.size()&&a[q.back()]<a[i]){
			int x=q.back();
			q.pop_back(); 
			if(op){
				if(c[x]>0) s+=c[x];//一定赚
				else if(q.size()) c[q.back()]+=c[x];//如果弹出 q.back()，那么弹出 x，否则清空。 
			}
			else s+=c[x],op=1;// 这是第一次弹出 
		}
		q.push_back(i);
		ans=max(ans,s);
	}
	cout<<ans;
}
```

---

## 作者：Themooncake (赞：1)

我们注意到，题目给出的这个代码只会在尾部退队的时候才会把 $c_i$ 统计到 $sum$ 里面，并且会从 $0$ 开始到 $r$ 把所有元素遍历一遍，因此 $r$ 可以决定哪些数可以被退掉。

但与此同时，我们还会注意到，$l$ 可以让底部的一些元素提前出队，因此考虑维护一个单调栈，枚举 $r$，找最优的一个到栈顶的连续区段，使得用 $r$ 去退栈时答案最优，因为如果设我要退的位置为 $x$，我可以用区间 $[x,x]$ 直接把 $x$ 之前的数全部从队首退掉而不加入 $sum$。

但特别的，如果当前枚举的这个 $r$ 无法使得单调栈退栈，应当直接继承上一位的答案。

同时，我们还会发现，如果我要退掉单调栈中的数 $x$，那么在 $x$ 上方**出现**过的所有数都会被计入 $sum$，因为用 $l$ 退队是自下而上退的，$x$ 一旦存在其上方的数也一定存在，故上方的数不是被更上方的数退掉就是被 $r$ 退掉，而这都会计入贡献，因此每向单调栈中加入一个数 $y$，栈内所有答案都要加上一个对应的 $c$。

因此，我们需要维护单调栈内每一个元素的权值 $a_i$ 以及从栈顶退到该元素时的 $sum$，还要能够二分找到自底到顶第一个权值 $a_i<a_r$，并查询区间的最大 $sum$，因此用线段树维护。
# Code
```
#include<bits/stdc++.h>
/*
	注意到 sum 只有在尾部退队的时候才会被 + 到
	我们尝试模拟一下这个过程
	如果没有这个 l 就是在从左往右做单调栈过程中模拟一遍记录历史最大值就好了 
	但是有了 l 我们可以通过 l 来控制 一些位置不被加到 
	所以相当于 找到单调栈中最底部的位置 选择一个到栈顶的连续区段来 +
	然后正常单调栈删除末尾
	但是 要删除一个数 在这个数上方的数都一定被删了 所以要动态的把这些数的贡献弄进答案里 
	如果一个数都退不掉 那么我们同时记录一个 lasans 来表示上一次操作的答案 继承它即可
	因此我们需要一个数据结构实现以下操作：
	1.区间加 2.二分 3.区间覆盖 4.单点插入
	显然线段树 
*/
using LL=long long;
LL read()
{
	char ch=getchar();
	LL x=0;
	int f=0;
	while(ch<'0'||ch>'9')
		f=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?~x+1:x;
}
const int N=5e5+5;
const LL inf=1e18;
int n,a[N];
LL c[N];
struct node{
	int mnA,clr;
	LL val,plus;
	void add(LL x)
	{
		val+=x;
		plus+=x;
	}
	void clear()
	{
		clr=1;
		plus=val=mnA=0;
	}
};
#define lson rt<<1
#define rson rt<<1|1
node tree[N<<2];
void pushdown(int rt)
{
	if(tree[rt].clr)
	{
		tree[lson].clear();
		tree[rson].clear();
		tree[rt].clr=0;
	}
	if(tree[rt].plus)
	{
		tree[lson].add(tree[rt].plus);
		tree[rson].add(tree[rt].plus);
		tree[rt].plus=0;
	}
}
void update(int rt)
{
	tree[rt].mnA=std::min(tree[lson].mnA,tree[rson].mnA);
	tree[rt].val=std::max(tree[lson].val,tree[rson].val);
}
void add(int rt,int l,int r,int L,int R,LL x)
{
	if(l>R||r<L)
		return;
	if(L<=l&&r<=R)
	{
		tree[rt].add(x);
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	add(lson,l,mid,L,R,x);
	add(rson,mid+1,r,L,R,x);
	update(rt);
}
void clear(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)
		return;
	if(L<=l&&r<=R)
	{
		tree[rt].clear();
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	clear(lson,l,mid,L,R);
	clear(rson,mid+1,r,L,R);
	update(rt);
}
void insert(int rt,int l,int r,int Tar,int AA,LL V)
{
	if(l>Tar||r<Tar)
		return;
	if(l==r)
	{
		tree[rt].mnA=AA;
		tree[rt].val=V;
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	insert(lson,l,mid,Tar,AA,V);
	insert(rson,mid+1,r,Tar,AA,V);
	update(rt);
}
int get_Lbound(int rt,int l,int r,int AA)
{
	if(tree[rt].mnA>AA)
		return -1;
	if(l==r)
		return l;
	int mid=l+r>>1;
	pushdown(rt);
	if(tree[lson].mnA<=AA)
		return get_Lbound(lson,l,mid,AA);
	else
		return get_Lbound(rson,mid+1,r,AA);
}
LL max(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)
		return -inf;
	if(L<=l&&r<=R)
		return tree[rt].val;
	pushdown(rt);
	int mid=l+r>>1;
	return std::max(max(lson,l,mid,L,R),max(rson,mid+1,r,L,R));
}
int top;
LL lasans,ans=-inf,tmp;
int main()
{
//	freopen("queue.in","r",stdin);
//	freopen("queue.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
		c[i]=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i)
	{
		int pos=get_Lbound(1,1,n,a[i]);
		if(pos>top)//单调栈内一个也退不掉 
			++top;
		else//最少要吃到一位 不可能清空 
		{
			lasans=max(1,1,n,pos,top);
			clear(1,1,n,pos,top);
			top=pos;
		}
		ans=std::max(ans,lasans);
		insert(1,1,n,top,a[i],lasans);
		add(1,1,n,1,top,c[i]);
	}
	printf("%lld",ans);
}
```

---

## 作者：FanMingxuan (赞：1)

这篇题解提供一个比较好想的线段树优化方法。
## 基础的转移方程

不难发现答案的累加只可能在右端点移动处发生，这启示我们关注本次选取的右端点。

设 $f_r$ 表示最后一个区间**选取了**右端点为 $r$ 的最大贡献（注意：因为是**选取了** $r$，导致 $f_r$ 可能为负数）。

考虑转移。我们枚举上一次的右端点 $k$，那么从 $k$ 到 $r$ 的部分都会被单调栈累加贡献，设 $k$ 到 $r$ 的单调栈贡献为 $g_{k,r}$，则有：

$$
f_r = \max_{k = 1}^{r - 1} \{ f_k + g_{k,r} \}
$$

这个时间复杂度是 $O(n ^ 2)$ 的，无法通过。
## 考虑优化转移

出题人题解里面用到了线段树二分来优化他的 DP 式子。

但是我们观察刚刚得到的转移方程，我们发现转移后面的一项 $g_{k,r}$ 在 $r$ 的移动时不断变化。

但是我们从单调栈的性质出发，我们发现一个位置 $i$ 在被 $r$ 弹出单调栈的时候，对于任意的 $l \le i$ 都会让 $g_{l,r}$ 加上 $c_r$。

那这个时候就可以朴素的线段树优化了。

具体的，我们维护线段树每个位置表示对于位置 $i$，$f_i + g_{i,r}$ 是多少。

当一个 $i$ 被弹出的时候，在线段树上的区间 $[1,i]$ 区间加上 $c_i$。

更新 $f_r$ 的时候我们直接区间查询线段树上面 $[1,r - 1]$ 节点的最大值即可。

时间复杂度 $O(n \log n)$，可以通过本题。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500005;
const int INF = 0x3f3f3f3f3f3f3f3f;
int a[N],w[N],f[N],st[N],top = 0;

namespace SegTree{
	#define l(p) t[(p)].l
	#define r(p) t[(p)].r
	#define dat(p) t[(p)].dat
	#define add(p) t[(p)].add
	#define lc(p) ((p) << 1)
	#define rc(p) ((p) << 1 | 1)
	struct node{
		int l;
		int r;
		int dat;
		int add;
	}t[N << 2];
	
	inline void do_cover(int p,int d){
		dat(p) += d;
		add(p) += d;
	}
	
	inline void push_down(int p){
		if(add(p)){
			do_cover(lc(p),add(p));
			do_cover(rc(p),add(p));
			add(p) = 0;
		}
	}
	
	inline void push_up(int p){
		dat(p) = max(dat(lc(p)),dat(rc(p)));
	}
	
	inline void build(int p,int l,int r){
		l(p) = l;
		r(p) = r;
		if(l == r){
			dat(p) = -INF;
			return;
		}
		int mid = (l + r) >> 1;
		build(lc(p),l,mid);
		build(rc(p),mid + 1,r);
		push_up(p);
	}
	
	inline void change(int p,int x,int v){
		if(l(p) == r(p)){
			dat(p) = v;
			return;
		}
		push_down(p);
		int mid = (l(p) + r(p)) >> 1;
		if(x <= mid) change(lc(p),x,v);
		else change(rc(p),x,v);
		push_up(p);
	}
	
	inline void change2(int p,int l,int r,int d){
		if(l <= l(p) && r >= r(p)){
			do_cover(p,d);
			return;
		}
		push_down(p);
		int mid = (l(p) + r(p)) >> 1;
		if(l <= mid) change2(lc(p),l,r,d);
		if(r > mid) change2(rc(p),l,r,d);
		push_up(p);
	}
	
	inline int query(int p,int l,int r){
		if(l <= l(p) && r >= r(p)) return dat(p);
		push_down(p);
		int mid = (l(p) + r(p)) >> 1;
		int ans = -INF;
		if(l <= mid) ans = max(ans,query(lc(p),l,r));
		if(r > mid) ans = max(ans,query(rc(p),l,r));
		return ans;
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i = 1;i <= n;++ i) cin>>w[i];
	for(int i = 1;i <= n;++ i) cin>>a[i];
	for(int i = 1;i <= n;++ i) f[i] = -INF;
	f[1] = 0;
	SegTree::build(1,1,n);
	SegTree::change(1,1,0);
	int ans = 0;
	st[++ top] = 1;
	for(int r = 2;r <= n;++ r){
		while(top && a[st[top]] < a[r]){
			int x = st[top];
			top --;
			SegTree::change2(1,1,x,w[x]);
		}
		st[++ top] = r;
		f[r] = SegTree::query(1,1,r - 1);
		ans = max(ans,f[r]);
		SegTree::change(1,r,f[r]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lizihan250 (赞：1)

# P11325 【MX-S7-T3】「SMOI-R2」Monotonic Queue

提供一种基于单调栈的 $O(n)$ 做法。

这次 NOIP 模拟赛没发挥好，赛时这题的最后一部分没想清楚，挂到 $4$ 分。只能希望 NOIP 时不要这样吧。

## 题意简述

给定一个 $n$ 个按序排列的二元组，第 $i$ 个二元组为 $(c_i,a_i)$。所有的 $a$ 可构成一个 $1 \sim n$ 的排列。现在有一单调队列，有一左指针 $l$ 和一右指针 $r$（初始位置位于 $0$），一计数器 $sum$，执行 $n$ 轮如下操作：

- 不断向右移动右指针直至到达某个目标位置。每次向后移动一位到达新位置后，将单调队列里所有的满足 $a_i<a_r$ 的二元组 $(c_i,a_i)$ 移除，$sum \gets sum+c_i$，再加入二元组 $(c_r,a_r)$。
- 不断向右移动左指针直至到达某个目标位置。每次向后移动一位到达新位置前，若指针所指的二元组仍然在单调队列中，则将其移除。

现在，要求分别指定 $n$ 轮左指针、右指针的目标位置，使得算法结束后 $sum$ 尽可能大。请求出 $sum$ 的最大值。

## 解题思路

首先，显然的一点是，若指定 $l=1,r=1$，那么什么都不会发生。因此，我们可以指定任意数量的不超过 $n$ 次的左指针、右指针目标位置，在方案前补上若干 $l=1,r=1$ 即可。

由于要先移动右指针，再移动左指针，我们可以说明：若存在 $1 \le i < n$，使得 $a_i < a_{i+1}$，且 $i+1 \le r_n$，则 $c_i$ 一定对 $sum$ 产生贡献。

显然，若在第 $k$ 次操作时，右指针的目标位置第一次达到 $i+1$，则第 $k$ 次操作前，有 $l_{k-1} \le r_{k-1} < i+1$（规定 $l_0 = r_0 = 0$）。因此，在此次操作前，$(c_i,a_i)$ 不会因为信息过时而离开单调队列。因此，它一定会因为 $a_i <a_{i+1}$ 离开单调队列，并对 $sum$ 产生贡献。

因此，对于每个 $i$，考虑当 $r_n = i$ 时的答案，取最大值即可。我们可以对所有二元组分成多块，每块内的二元组的 $a$ 单调递增。除了每块右端点的二元组，所有二元组都强制产生贡献。因此我们只考虑每块右端点的二元组的选取情况。（如下图绿点，左右关系反映二元组的先后顺序，高度反映二元组的 $a$ 的高度。）

![Monotonic Queue 图示 1](https://cdn.luogu.com.cn/upload/image_hosting/bkvlcab8.png)

对于每个二元组，它会且只会将在它**之前**的**连续**的 $a$ 的值比它小的二元组从单调队列中移除。同时，我们可以通过指定 $l$ 的目标位置，使得只有位于 $[l,r)$ 的块的右端点对 $sum$ 产生贡献。由于我们可以进行至多 $n$ 次这样的操作，而每个节点最多指定一次，因此不用考虑次数限制。

分开考虑如图的黑点与绿点。考虑绿点贡献。一个部分是在比这个二元组的 $a$ 大的二元组及以前的部分，另一个部分是这之后的部分。我们要最大化后一部分贡献，于是就形成了一个类似最大子段和的问题。不过这里的右端点是固定的。

直接转移显然会 TLE。我们考虑如何优化。我们希望用利用数据的特殊性，使用单调栈维护所有的块右端点（即图中绿点）。

![Monotonic Queue 图示 2](https://cdn.luogu.com.cn/upload/image_hosting/q9roak4l.png)

如上图所示，假定处理到从左往右第 $6$ 个绿点时，最大化的贡献用浅蓝色线段表示，弹出的所有二元组的 $c$ 之和用橙色线段表示。

在后续的处理中，若要使从左往右第 $3$ 个绿点产生贡献，必定会选上橙色线段标出的绿点。因此，我们将这部分贡献直接加到第 $3$ 个绿点的贡献。

考虑用全局变量 $sum$ 表示在 $r_n$ 为某一状态下的全局贡献最大值。显然，此处应让 $sum$ 加上浅蓝色线段表示的贡献。但为了在下次计算时，统计其前一个绿点时不重复计算这一段贡献（图中橙色线段与浅蓝色线段重合处），我们还要将图中第 $3$ 个绿点的贡献减去这个值。

每个绿点最多一次进栈，一次出栈，时间复杂度 $O(n)$。代码也很好写。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=500000;
int n,a[Maxn+100],c[Maxn+100];
long long ans=0,sum=0,tp=0,sumstk,nans;
struct pp
{
    int p;
    long long x;
}stk[Maxn+100];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",c+i);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<=n;i++)
    {
        sumstk=nans=0;
        while(tp>0&&stk[tp].p<a[i])
        {
            sumstk+=stk[tp].x;
            nans=max(nans,sumstk);
            tp--;
        }
        stk[tp].x+=sumstk-nans;
        ans=max(ans,sum+nans);
        sum+=nans;
        if(a[i]<a[i+1]) sum+=c[i];
        else
        {
            tp++;
            stk[tp].p=a[i];
            stk[tp].x=c[i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：CarroT1212 (赞：0)

一个跟官解不太一样且个人认为更显然的维护方式。题意即求题目代码中被右端点单调队列掉的位置的 $c_i$ 之和。

---

首先相邻 $r_i$ 相同的情况感觉很多余，不如直接令 $r_i=i$，然后答案变成，操作 $n$ 个区间 $[l_i,i]$ 的**前若干个**得到的最大答案（这里取前若干个是因为可以让 $n$ 个区间的一段后缀全部相同，使得序列中在最后一个 $r_i$ 后面的数一次都不进队列）。

现在相当于每次往队列里加一个数，考虑左端点 $l_i$ 需要如何取最优。

左端点的作用是，求 $[l_i,i]$ 区间的单调队列时，如果有原序列中位于 $[l_{i-1},l_i-1]$ 的元素出现在了前一个区间（$[l_{i-1},i-1]$）的单调队列中，并且在加入第 $i$ 个数（右端点右移一位）时没有直接被 $a_i$ 弹掉，那么它就会在左端点从 $l_{i-1}$ 右移到 $l_i$ 时被弹掉，不计入贡献。

这里定睛一想可以注意到一个事实：**弹掉某个数的数是固定的**。即，$a_x$ 后第一个大于它的数 $a_y$，就是将 $a_x$ 弹掉的数，前提是 $a_x$ 没有先从左边出去。

换到序列中元素的角度思考，设不考虑左端点的情况下，第 $i$ 位数会在右端点到第 $nxt_i$ 位被弹出去。$nxt_i$ 可以直接单调栈求得。那么 $c_i$ 被计入的条件就是 $[i,nxt_i-1]$ 的所有 $l_j$ 都 $\le i$，即在没到 $a_{nxt_i}$ 之前左端点一直在 $a_i$ 左边。又因为 $l$ 递增，所以实际上这个限制就是 $l_{nxt_i-1}\le i$。

换句话说，对于每一个存在 $nxt_i$ 的 $i$，如果 $l_{nxt_i-1}\le i$，答案就会加上 $c_i$。（此外 $l$ 还有 $l_i\le l_{i+1}$ 和 $l_i\le i$）

把这些限制标记到 $nxt_i-1$ 上，直接设个 $dp_{i,j}$ 表示前 $i$ 位中 $l_i=j$ 时的最大答案即可 $O(n^2)$ 地转移。形如这样的限制只有 $O(n)$ 个，考虑让处理次数和限制挂钩。

实际上只处理 $dp_{0,1}$ 和每个 $i$ 对应的 $dp_{nxt_i-1,i+1}$ 就一定可以获得最优答案。因为最优情况下使 $l_j>l_{j-1}$ 的唯一可能就是我们尝试**通过增加 $l$ 来躲掉 $j$ 这一位上存在的一个会使答案减小的限制**。但是 $l$ 增加的太多同样意味着我们更不容易吃到后面使答案增大的限制，所以增加到恰好能躲过这一位上的限制是最优的，即 $l_{nxt_i-1}=i+1$。

这可以使用线段树优化，具体实现就是按第一维递增做，只在每个 $dp_{nxt_i-1,i+1}$ 处求一次前缀 $\min$ 和单点赋值，并对于每个限制做前缀加。每做一位尝试让答案取最大值。

$O(n\log)$。

```cpp
const ll J=1e18,N=5e5+7;
ll n,c[N],a[N],nxt[N],ans;
ll st[N],tp;
vector<pll> v[N];
struct sgt {
	ll t[N<<2],tg[N<<2];
	void pdn(ll p) {
		if (tg[p])
			t[p<<1]+=tg[p],tg[p<<1]+=tg[p],t[p<<1|1]+=tg[p],tg[p<<1|1]+=tg[p],tg[p]=0;
	}
	void pup(ll p) { t[p]=max(t[p<<1],t[p<<1|1]); }
	void add(ll x,ll y,ll z,ll p=1,ll l=1,ll r=n) {
		if (x<=l&&r<=y) return t[p]+=z,tg[p]+=z,void();
		ll mid=l+r>>1; pdn(p);
		if (x<=mid) add(x,y,z,p<<1,l,mid);
		if (y>mid) add(x,y,z,p<<1|1,mid+1,r);
		pup(p);
	}
	void chn(ll x,ll z,ll p=1,ll l=1,ll r=n) {
		if (l==r) return t[p]=max(t[p],z),void();
		ll mid=l+r>>1; pdn(p);
		if (x<=mid) chn(x,z,p<<1,l,mid);
		else chn(x,z,p<<1|1,mid+1,r);
		pup(p);
	}
	ll que(ll x,ll y,ll p=1,ll l=1,ll r=n) {
		if (x<=l&&r<=y) return t[p];
		ll mid=l+r>>1,ret=-J; pdn(p);
		if (x<=mid) ret=que(x,y,p<<1,l,mid);
		if (y>mid) ret=max(ret,que(x,y,p<<1|1,mid+1,r));
		return ret;
	}
} T;
void mian() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) scanf("%lld",&c[i]);
	for (ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (ll i=n;i;i--) {
		while (tp&&a[st[tp]]<a[i]) tp--;
		nxt[i]=st[tp],st[++tp]=i;
		if (nxt[i]) v[nxt[i]-1].pb({i,c[i]});
	}
	T.add(1,n,-J),T.chn(1,0);
	for (ll i=1;i<=n;i++) {
		for (pll j:v[i]) if (j.fi<i) T.chn(j.fi+1,T.que(1,j.fi));
		for (pll j:v[i]) T.add(1,j.fi,j.se);
		ans=max(ans,T.t[1]);
	}
	cout<<ans;
}
```

---

## 作者：SamHJD (赞：0)

观察到若 $l_i=l_{i+1}$ 则第 $i+1$ 个区间是无用的，因为处理第 $i$ 到 $i+2$ 个区间时删去第 $i+1$ 个区间不会对左右端点的移动造成影响。于是可以钦定 $l_i=i$。

处理出每个位置 $i$ 后面第一个比他大的位置 $nxt_i$，显然只有 $nxt_i$ 可以将 $i$ 在队尾弹出，且条件为 $r_{i+1}\ge nxt_i$。

设 $f_{i,j}$ 为考虑前 $i$ 个数，定下了 $r_{1\dots i+1}$，且 $r_{i+1}=j$ 的最大答案。枚举 $r_i$ 的取值并判断 $i$ 是否能在队尾弹出，有转移：$f_{i,j}=\max\limits_{k=i}^{j} f_{i-1,k}+[nxt_i\le j]c_i$。由于 $f_{i,j},j\le i$ 为不合法的状态，将其赋值为负无穷，上式的 $k$ 的枚举范围左边界可以设到 $1$，于是可用前缀和优化至 $O(n^2)$。

$f_i$ 从 $f_{i-1}$ 转移来，可以滚掉这一维，尝试用线段树维护 $f_j$。由于使用前缀和优化，当前的 $f_j$ 需为真实的 $f_{1\dots j}$ 的最大值，进行转移时先将 $f_{nxt_i\dots n}$ 加上 $c_i$，不过可能会出现 $[nxt_i,n]$ 中的 $f$ 比 $f_{nxt_i-1}$ 小的情况，但因为 $[1,nxt_i),[nxt_i,n]$ 都是递增的，于是线段树上二分出最后一个 $p$ 满足 $f_p<f_{nxt_i-1}$ 并用 $f_{nxt_i-1}$ 的值推平 $[nxt_i,p]$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=5e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,c[N],a[N],st[N],top,nxt[N],sum[N];
vector<int> v[N];
namespace SGT{
    #define ls x*2
    #define rs x*2+1
	int tg1[4*N],tg2[4*N];
	int f[4*N];
    void init(){
        memset(tg1,0x3f,sizeof(tg1));
        memset(tg2,0,sizeof(tg2));
    }
	void pushup(int x){
		f[x]=max(f[ls],f[ls]);
	}
	void updtg(int x,int t1,int t2){
	    if(t1!=INF) tg1[x]=t1,tg2[x]=0,f[x]=t1;
		if(t2) tg2[x]+=t2,f[x]+=t2;
	}
	void pushdown(int x){
		updtg(ls,tg1[x],tg2[x]);
		updtg(rs,tg1[x],tg2[x]);
		tg1[x]=INF,tg2[x]=0;
	}
	void upd(int x,int l,int r,int s,int t,int t1,int t2){
		if(l>=s && r<=t) return updtg(x,t1,t2);
		int mid=(l+r)>>1;
		pushdown(x);
		if(s<=mid) upd(ls,l,mid,s,t,t1,t2);
		if(t>mid) upd(rs,mid+1,r,s,t,t1,t2);
		return pushup(x);
	}
    int get(int x,int l,int r,int s,int val){
        int mid=(l+r)>>1;
        if(l==r) return l;
        pushdown(x);
        if(s>mid) return get(rs,mid+1,r,s,val);
        if(f[rs]<=val) return get(rs,mid+1,r,s,val);
        else return get(ls,l,mid,s,val);
    }
	int query(int x,int l,int r,int s){
		if(l==r) return f[x];
		int mid=(l+r)>>1;
		pushdown(x);
		if(s<=mid) return query(ls,l,mid,s);
		else return query(rs,mid+1,r,s);
	}
}
signed main(){
	read(n);
    rep(i,1,n) read(c[i]),sum[i]=sum[i-1]+c[i];
    rep(i,1,n) read(a[i]);
    st[0]=n+1;
    per(i,n,1){
        while(top&&a[st[top]]<a[i]) top--;
        nxt[i]=st[top];st[++top]=i;
    }
    int ans=-INF;
    SGT::init();
    SGT::upd(1,1,n,1,1,INF,-INF);
    rep(i,1,n){
        SGT::upd(1,1,n,nxt[i],n,INF,c[i]);
        int val=SGT::query(1,1,n,nxt[i]-1);
        int pos=SGT::get(1,1,n,nxt[i]-1,val);
        SGT::upd(1,1,n,nxt[i],pos,val,0);
        ans=max(ans,SGT::query(1,1,n,i+1));
        SGT::upd(1,1,n,i+1,i+1,INF,-INF);
    } 
    printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：arrow_king (赞：0)

仔细看一看题目给的代码片段：

```cpp
deque<int> Q;
l[0] = r[0] = sum = 0;
for (int i = 1; i <= n; i++) {
    for (int j = r[i - 1] + 1; j <= r[i]; j++) {
        while (!Q.empty() && a[Q.back()] < a[j]) {
            sum = sum + c[Q.back()];
            Q.pop_back();
        }
        Q.push_back(j);
    }
    while (Q.front() < l[i]) Q.pop_front();
    b[i] = Q.front();
}
```

可以发现，一个元素的 $c$ 被统计上当且仅当它后面有一个比它大的元素把它 pop 出去了（从前面 pop 没有贡献）。

我们记 $nxt_i$ 表示 $i$ 后面第一个 $a_j>a_i$ 的 $j$。那么当且仅当 $nxt_i$ 在 $i$ 离开队列前进入队列时 $i$ 会有 $c_i$ 的贡献。

我们发现 popback 是优先于 popfront 的。所以如果存在一个 $p$ 使得 $l_p\le i$ 且 $nxt_i\le r_{p+1}$ 那么 $i$ 的贡献就会被计入答案中，因为在向下一个区间转移时 $nxt_i$ 会加入队列中并把 $i$ pop 掉。

我们注意到如果有一个 $i$ 是的 $l_i=l_{i+1}$，那么区间 $[l_i,r_i]$ 没有任何贡献，可以删除。因此我们强制使得 $l_i=i$。

考虑设计动态规划状态 $dp_{i,j}$ 表示考虑前 $i$ 个区间且 $r_{i+1}=j$。那么有转移
$$
dp_{i,j}=\max_{i\le k\le j}dp_{i-1,k}+[nxt_i\le j]c_i
$$
最后的答案是 $\max dp_{i,i+1}$。

这样的复杂度是 $O(n^2)$ 的，考虑优化。由于转移中有前缀 $\max$，所以我们维护所有 dp 状态的前缀 $\max$。

后面的常数项可以被看做区间加，因此给区间 $[nxt_i,n]$ 加一个 $c_i$ 即可，用线段树实现。

接下来求前缀 $\max$，我们考虑找到最后一个 $pos\ge nxt_i$ 使得 $dp_{i,pos}<dp_{i,nxt_i-1}$，然后给区间 $[nxt_i,pos]$ 统一赋值为 $dp_{i,nxt_i-1}$。

这样做有个小小的问题，当 $nxt_i=i+1$ 时，$dp_{i,i}$ 没有意义（$r_{i+1}\ge l_{i+1}=i+1$），因此在这种情况下要找 $dp_{i,i+1}$。

区间覆盖和加一个定值的复杂度是 $O(\log n)$，使用线段树上二分可以将查找 $p$ 的复杂度优化为 $O(\log n)$。因此总时间复杂度是 $(n\log n)$。

**一个有用的调数据结构优化 dp 的方法**：每过一步转移就输出一下你的 dp 数组，和暴力转移的 dp 数组比较一下，看看哪里修改错了。

```cpp
il ll binary(int L,int l,int r,int now,ll val) {
	if(r<L) return -1;
	if(l==r) {
		if(tr[now].maxn>=val) return l;
		return -1;
	}
	push_down(now);//这个是下传标记喵
	if(tr[now].maxn<val) return -1;
	if(r<L) return -1;
	ll mid=(l+r)>>1;
	ll res=binary(L,l,mid,lc(now),val);
	if(res!=-1) return res;
	return binary(L,mid+1,r,rc(now),val);
}//线段树上二分，固定左端点下界
int main() {
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=1;i<=n;i++) nxt[i]=n+1;
	for(int i=1;i<=n;i++) {
		while(top&&p[st[top]]<p[i]) nxt[st[top--]]=i;
		st[++top]=i;
	}
	build(1,1,n);ll ans=0;
	for(int i=1;i<=n;i++) {
		if(nxt[i]>n) {
			ans=max(ans,query(i+1,i+1,1,n,1));
			continue;
		}
		modify(nxt[i],n,1,n,1,a[i]);
		ll now=query(max(i+1,nxt[i]-1),max(i+1,nxt[i]-1),1,n,1);
		int pos=binary(nxt[i],1,n,1,now);
		if(pos!=-1) cover(nxt[i],pos-1,1,n,1,now);
		else cover(nxt[i],n,1,n,1,now);
		ans=max(ans,query(i+1,i+1,1,n,1));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：bunH2O (赞：0)

似乎比 std 要牛。

这个题求的东西比较奇怪，先来分析一下性质。

首先区间个数限制为 $n$ 非常难受，猜测没有用。发现对于每个 $l$，只有最大的 $r$ 是有意义的，所以区间个数限制无用。

随后你考虑一个东西他对答案有贡献的条件是什么。他得在从后面滚出来之前被前面弹出去。也就是说得存在 $l_i\leq x \land nxt\leq r_{i+1}$，其中 $nxt$ 是 $x$ 右边第一个比 $a_x$ 大的位置。

进一步地，我们考虑怎样的贡献方案是合法的。由于牵扯到求 $nxt$，我们把问题转移到笛卡尔树上考虑。注意题中算法只遍历到 $r_n$，故 $r_n$ 的大小会影响 $nxt$。我们暂且只考虑 $r_n=n$ 的情况。

假如我们钦定一个位置有贡献，那么首先要存在 $nxt$，也即 $x$ 不在右链上；其次，我们需构造 $l_i\leq x\land r_{i+1}\geq nxt$，也即 $x$ 的右子树都应有贡献。

假如我们钦定一个位置无贡献，刨去与上文本质相同的内容，我们注意到当 $nxt=x+1$ 也即 $x$ 为非右链上叶子节点时，必然存在 $l_i\leq x\land r_{i+1}>x$，其余情况均可达到。

因此我们得到了一组贡献合法的判定条件：右链必不选，叶子必选，其余节点若选则其右子树均需选。写成 $dp$ 形式如下：

$dp_x=\begin{cases}dp_{ls}+dp_{rs}&x\,\texttt{在右链}\\c_x&x\;\texttt{是叶子}\\\max(dp_{ls}+dp_{rs},dp_{ls}+c_x+sum_{rs})&\texttt{其余情况}\end{cases}$

所以我们在 $\Omicron(n)$ 的时间内解决了 $r_n$ 固定的情况。接下来考虑 $r_n$ 从 $1$ 到 $n$ 移动。

动态维护笛卡尔树右链，对于 $r_n$ 和被弹出右链的节点，我们依照上式求出其 $dp$ 值。对于仍在右链的节点，其 $dp$ 值不涉及决策，可以轻松打标记维护。

在扫描线的过程中将答案与 $dp_{rt}$ 作 $\text{chkmax}$ 即可，时空复杂度均为 $\Omicron(n)$。

---

## 作者：Imiya (赞：0)

提供一种使用笛卡尔树的线性做法。

首先恰好 $n$ 个区间是一个无效条件，每一次右端点向右移动一位后调整左端点即能涵盖所有情况。所以我们现在只考虑随着右端点的右移，如何控制左端点使 $sum$ 最大。

以 $a:{2,7,1,3,4,6,5,9,8,10}$ 为例

其大根笛卡尔树如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3rvct65o.png)

为了方便表述，记 $[L_i,R_i]$ 表示 $i$ 子树在原序列上对应的区间，如上例中 $[L_2,R_2]=[1,7]$

设 $f_{i,0}$ 表示【左端点一开始为 $L_i$，右端点从 $L_i$ 开始右移，不超过 $R_i$】$sum$ 的最大值。

$f_{i,1}$ 表示【左端点一开始为 $L_i$，右端点从 $L_i$ 开始右移，最终到达 $R_i+1$】$sum$ 的最大值。

则答案为 $f_{rt,0}$，$rt$ 为笛卡尔树树根。

有如下转移：

$$
\begin{aligned}
f_{i,0}&=\max\{f_{ls,0},f_{ls,1},f_{ls,1}+f_{rs,0}\}\\
f_{i,1}&=f_{ls,1}+\max\{c_i+S_{rs},f_{rs,1}\}
\end{aligned}
$$

其中 $S_x$ 表示 $x$ 的子树内所有点的 $c$ 值之和。

第一个转移的三种情况分别是【右端点没有超过 $R_{ls}$】或者【右端点恰好到 $i$】或者【右端点超过 $i$ 不超过 $R_{rs}$】。注意当右段点到 $i$ 时左儿子就没有用了，可以直接把左端点也移到 $i$。

第二个转移表示【右端点到 $i$，然后左端点随即移到 $i$】后，取【左端点保持在 $i$，右端点移到 $R_{i}+1$】和【右端点移到 $L_{rs}$，左端点跟着移到 $L_{rs}$，然后进入 $f_{rs,1}$ 状态】的最大值。

边界情况略。

最终复杂度 $O(n)$。

至于如何想到笛卡尔树，主要是因为笛卡尔树从某种意义上讲可以说是一种可持久化单调栈，于是看到这个题的第一思路就是转化为笛卡尔树上问题。

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑什么时候一个 $c_i$ 才能有贡献，首先找到如果正常使用单调栈在那个位置会被 $i$ 给弹出去，显然是下一个大于 $a_i$ 的数的位置；设为 $nxt_i$；不存在则 $nxt_i = n + 1$。

则需要满足 $l_i \le i$ 且 $nxt_i \le r_{i + 1}$，发现 $l$ 几乎没有什么影响，考虑直接钦定 $l_i = i$。

故只有当 $nxt_i \le r_{i + 1}$ 时才会造成 $c_i$ 的贡献，故考虑动态规划；设 $dp_{i, j}$ 表示当 $r_{i + 1} = j$ 时的最大贡献，有状态转移方程：

$$dp_{i, j} = [nxt_i \le j] c_i + \max\limits_{k = i}^{j} dp_{i - 1, j}$$

直接转移是 $O(N^3)$，前缀预处理下最大值后是 $O(N^2)$；

考虑令：

$$s_{i, j} = \max\limits_{k = i + 1}^j dp_{i, j}$$

则转移相当于将 $s_{i - 1}$ 复制到 $dp_i$，然后给 $[nxt_i, n]$ 加上一个 $c_i$，然后还要清空一下 $dp_{i, i}$。

然后考虑如何求出 $dp_i$ 的 $s_i$，即一个单调增序列给一个后缀加上一个数 $c_i$；若 $c_i > 0$，则 $s_i$ 就是 $dp_i$。

否则找到一个 $j$ 使得 $dp_{i, nxt_i - 1} < dp_{i, j}$；则 $s_i$ 相当于 $dp_i$ 给 $[i + 1, j - 1]$ 赋值为 $dp_{i, nxt_i-1}$。

上述都使用线段树维护即可，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10;
const ll INF = 1e18;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	ll Max;
	ll add;
	ll tag;
}X[N << 2];
ll ans;
int n, top;
int c[N], a[N], nxt[N], T[N];
inline void pushup(int k){
	X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
}
inline void assign(int k, ll v){
	X[k].Max = v;
	X[k].add = 0;
	X[k].tag = v;
}
inline void add(int k, ll v){
	X[k].Max += v;
	X[k].add += v;
}
inline void push_down(int k){
	if(X[k].tag != INF){
		assign(k << 1, X[k].tag);
		assign(k << 1 | 1, X[k].tag);
		X[k].tag = INF;
	}
	if(X[k].add){
		add(k << 1, X[k].add);
		add(k << 1 | 1, X[k].add);
		X[k].add = 0;
	}
} 
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	X[k].tag = INF;
	if(l == r)
	  return ;
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}
inline void update(int k, int l, int r, ll v, bool F){
	if(l > r)
	  return ;
	if(X[k].l == l && r == X[k].r){
		if(F)
		  assign(k, v);
		else
		  add(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v, F);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v, F);
	else{
		update(k << 1, l, mid, v, F);
		update(k << 1 | 1, mid + 1, r, v, F);
	}
	pushup(k);
}
inline ll query(int k, int i){
	if(X[k].l == i && i == X[k].r)
	  return X[k].Max;
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(i <= mid)
	  return query(k << 1, i);
	else
	  return query(k << 1 | 1, i);
}
inline int Ask(int k, ll now){
	if(X[k].l == X[k].r)
	  return X[k].l;
	push_down(k);
	if(X[k << 1].Max >= now)
	  return Ask(k << 1, now);
	else
	  return Ask(k << 1 | 1, now);
}
inline int Ask(int k, int l, int r, ll now){
	if(X[k].l == l && r == X[k].r){
		if(X[k].Max >= now)
		  return Ask(k, now);
		return 0;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return Ask(k << 1, l, r, now);
	else if(l > mid)
	  return Ask(k << 1 | 1, l, r, now);
	else{
		int sum = Ask(k << 1, l, mid, now);
		if(sum)
		  return sum;
		return Ask(k << 1 | 1, mid + 1, r, now);
	}
}
bool End;
int main(){
//	open("A.in", "A.out");
	n = read();
	for(int i = 1; i <= n; ++i)
	  c[i] = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		while(a[i] > a[T[top]] && top){
			nxt[T[top]] = i;
			--top;
		}
		T[++top] = i;
	}
	for(int i = 1; i <= n; ++i)
	  if(!nxt[i])
	    nxt[i] = n + 1;
	build(1, 1, n);
	for(int i = 1; i < n; ++i){
		update(1, i, i, -INF, 1);
		if(nxt[i] == n + 1)
		  continue;
		update(1, nxt[i], n, c[i], 0);
		if(nxt[i] == i + 1 || c[i] >= 0){
			ans = max(ans, query(1, i + 1));
			continue;
		}
		ll now = query(1, nxt[i] - 1);
		int t = Ask(1, nxt[i], n, now);
		if(!t)
		  t = n + 1;
		update(1, nxt[i], t - 1, now, 1);
		ans = max(ans, query(1, i + 1));
	}
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Ratio_Y (赞：0)

找性质题。找到性质之后就是简单线段树优化 dp。


---


## 思路

据 @[Abnormal123](https://www.luogu.com.cn/user/919959) 赛时观察 1h 的结论：我们只选择长度为 1 的区间即可达到最优解。证明主要从**能拿到可能的贡献区间**和**能不选可以避免的负贡献区间**两方面考虑。

按小 L 的操作实现，我们先移动右端点，然后再移动左端点。考虑一段什么样的正贡献区间是可拿到的，如果该区间的最大值小于右端点的下一个值，那么显然是可以在右端点移动过程中获得所有贡献的。我们直接选择一个位于该区间右端点的长度为 1 的区间即可。

考虑什么样的负贡献区间可以避免，如果该区间严格单调不下降，那么所有元素都会存在队列里，可以通过移动左端点来 `pop_back` 掉它们。此时在区间右端点选择一个长度为 1 的区间可以实现。

至于那些不得不吃的负贡献，我们直接忽略掉即可，因为结果是不变的。

那么之后就可以用 dp 求解了。设 $f_i$ 为钦定必须吃到 $i$ 的贡献，即选 $[i,i]$ 这一区间的最大值，容易写出转移式：$f_i=\max_{j=0}^{i-1}f_j+val_{[j,i]}$。$val_{[j,i]}$ 表示 $[j,i]$ 这段区间产生的贡献。

考虑这个 $val$ 怎么求。我们发现一个点 $i$ 若产生贡献，那么一定存在某一次右端点移动包含了 $i$ 和它之后第一个大于它的数。我们记这个第一个大于 $a_i$ 的数的下标为 $nxt_i$，这个求解的方法很多，树状数组或者单调队列均可。容易发现这个 $nxt$ 值是单调不降的，所以我们将所有 $nxt$ 值为 $nxt_i$ 的下标装入 $pre_{nxt_i}$ 中，每当遍历到一个点时，将 $pre_{i}$ 中所有值取出计算贡献即可。

任意包含 $[i,nxt_i]$ 这段区间的区间都会吃到 $i$ 的贡献，这等价于对一个前缀做了一个区间加的操作。所以我们直接上线段树优化，就可以将转移的复杂度优化至 $\mathcal{O(n\log n)}$ 的了。

## 实现

```cpp
#include<bits/stdc++.h>
#define fo(x, y, z) for(int (x) = (y); (x) <= (z); (x)++)
#define fu(x, y, z) for(int (x) = (y); (x) >= (z); (x)--)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define lx ll
inline lx qr()
{
    char ch = getchar(); lx x = 0, f = 1;
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x * f;
}
#undef lx
#define qr qr()
#define pll pair<ll, ll>
#define pii pair<int, int>
#define ppp pair<pii, pii>
#define fi first
#define se second
#define M_P(x, y) make_pair(x, y)
#define P_B(x) push_back(x)
const int Ratio = 0;
const int N = 5e5 + 5;
const int mod = 998244353;
int n, m;
int a[N], c[N], t[N];
ll v[N << 2], lazy[N << 2], f[N];
vector<int> pre[N];
namespace Wisadel
{
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    inline void Wpushup(int rt){v[rt] = max(v[ls], v[rs]);}
    inline void Wpushdown(int rt)
    {
        v[ls] += lazy[rt], v[rs] += lazy[rt];
        lazy[ls] += lazy[rt], lazy[rs] += lazy[rt];
        lazy[rt] = 0;
    }
    inline void Wbuild(int rt, int l, int r)
    {
        if(l == r)
        {
            v[rt] = f[l];
            return ;
        }
        Wbuild(ls, l, mid), Wbuild(rs, mid + 1, r);
        Wpushup(rt);
    }
    inline void Wupd(int rt, int l, int r, int x, ll val)
    {
        if(l == r) return v[rt] = val, void();
        if(lazy[rt]) Wpushdown(rt);
        if(x <= mid) Wupd(ls, l, mid, x, val);
        else Wupd(rs, mid + 1, r, x, val);
        Wpushup(rt);
    }
    inline void Wupd(int rt, int l, int r, int x, int y, ll val)
    {
        if(x <= l && r <= y)
        {
            v[rt] += val, lazy[rt] += val;
            return ;
        }
        if(lazy[rt]) Wpushdown(rt);
        if(x <= mid) Wupd(ls, l, mid, x, y, val);
        if(y > mid) Wupd(rs, mid + 1, r, x, y, val);
        Wpushup(rt);
    }
    inline void Tm(int x, int v){for(; x <= n; x += (x & -x)) t[x] = min(t[x], v);}
    inline int Tq(int x){int res = 2e9; for(; x; x -= (x & -x)) res = min(res, t[x]); return res;}
    short main()
    {
        n = qr;
        fo(i, 1, n) c[i] = qr;
        fo(i, 1, n) a[i] = qr, t[i] = 2e9, f[i] = -2e18;
        fu(i, n, 1)
        {
            int zc = Tq(n - a[i] + 1);
            if(zc <= n) pre[zc].P_B(i);
            Tm(n - a[i] + 1, i);
        }
        Wbuild(1, 0, n);
        ll ans = -2e18;
        fo(i, 1, n)
        {
            for(auto j : pre[i])
                Wupd(1, 0, n, 0, j, c[j]);
            ans = max(ans, v[1]);
            Wupd(1, 0, n, i, v[1]);
        }
        printf("%lld\n", ans);
        return Ratio;
    }
}
signed main(){return Wisadel::main();}
// All talk and never answer
```


---

完结撒花~

---

