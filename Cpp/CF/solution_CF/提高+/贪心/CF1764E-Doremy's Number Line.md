# Doremy's Number Line

## 题目描述

Doremy has two arrays $ a $ and $ b $ of $ n $ integers each, and an integer $ k $ .

Initially, she has a number line where no integers are colored. She chooses a permutation $ p $ of $ [1,2,\ldots,n] $ then performs $ n $ moves. On the $ i $ -th move she does the following:

- Pick an uncolored integer $ x $ on the number line such that either: 
  - $ x \leq a_{p_i} $ ; or
  - there exists a colored integer $ y $ such that $ y \leq a_{p_i} $ and $ x \leq y+b_{p_i} $ .
- Color integer $ x $ with color $ p_i $ .

Determine if the integer $ k $ can be colored with color $ 1 $ .

## 说明/提示

For the first test case, it is impossible to color point $ 16 $ with color $ 1 $ .

For the second test case, $ p=[2,1,3,4] $ is one possible choice, the detail is shown below.

- On the first move, pick $ x=8 $ and color it with color $ 2 $ since $ x=8 $ is uncolored and $ x \le a_2 $ .
- On the second move, pick $ x=16 $ and color it with color $ 1 $ since there exists a colored point $ y=8 $ such that $ y\le a_1 $ and $ x \le y + b_1 $ .
- On the third move, pick $ x=0 $ and color it with color $ 3 $ since $ x=0 $ is uncolored and $ x \le a_3 $ .
- On the forth move, pick $ x=-2 $ and color it with color $ 4 $ since $ x=-2 $ is uncolored and $ x \le a_4 $ .
- In the end, point $ -2,0,8,16 $ are colored with color $ 4,3,2,1 $ , respectively.

For the third test case, $ p=[2,1,4,3] $ is one possible choice.

For the fourth test case, $ p=[2,3,4,1] $ is one possible choice.

## 样例 #1

### 输入

```
6
4 16
5 3
8 12
10 7
15 1
4 16
8 12
10 7
15 1
5 3
4 16
10 7
15 1
5 3
8 12
4 16
15 1
5 3
8 12
10 7
1 1000000000
500000000 500000000
2 1000000000
1 999999999
1 1```

### 输出

```
NO
YES
YES
YES
NO
YES```

# 题解

## 作者：Leasier (赞：7)

~~这个东西可以视为斑羚飞渡。~~

首先判掉 $n = 1$、可以直接跳到以及无论怎么做都跳不到的情况。

当 $n > 1$，最优策略一定为**先通过若干 $2 \sim n$ 的操作到达一个尽可能远的 $x$，再看看能不能通过最后一次两段跳到达 $k$**。

考虑按 $a$ 升序排序，接下来 dp，设 $dp_i$ 表示通过**排序后** $2 \sim i$ 的操作可以到达的最右端。对于每一个 $i$，我们有如下决策：

1. 直接走到 $a_i$

此时令 $dp_i \leftarrow \max(dp_i, a_i)$。

2. 走到某一个 $a_j \leq a_i$，再跳 $b_j$ 步

此时令 $dp_i \leftarrow \max(dp_i, a_j + b_j)$。这个转移可以通过前缀 $\max$ 优化。

3. 走到某一个 $\min(dp_{i - 1}, a_i)$，再跳 $b_i$ 步

此时令 $dp_i \leftarrow \max(dp_i, \min(dp_{i - 1}, a_i) + b_i)$。

最终判断 $dp_n + b_1$ 与 $k$ 的关系即可。

注意 dp 完判断时中要开 long long。

现在我们来证明这样排序是最优的。

首先，在最优方案中**我们一定不会走环**，所以说一定存在某种使得答案最优的排序方式。

对于 $a_i = a_{i - 1}, b_i \neq b_{i - 1}$，因为第一、二种转移显然无影响，而对于第三种转移，离开这个 $a_i$ 相同的连续段时其贡献总为 $a_i + \max b_i$，所以说也无影响。

对于 $a_i \neq a_{i - 1}$，考虑邻项交换法。不妨设 $a_{i - 1} < a_i$，$T = \displaystyle\max_{j = 1}^{i - 2} (a_j + b_j)$。

1. 当 $a_{i - 1}$ 在 $a_i$ 前面

此时 $dp_i = \max(a_i, \max(T, a_{i - 1} + b_{i - 1}), \min(\max(a_{i - 1}, T, \min(dp_{i - 2}, a_{i - 1}) + b_{i - 1}), a_i) + b_i)$。

暴力拆开可得：

- $a_i$
- $T$
- $a_{i - 1} + b_{i - 1}$
- $a_{i - 1} + b_i$
- $\min(a_i, T) + b_i$
- $\min(\min(dp_{i - 2}, a_{i - 1}) + b_{i - 1}, a_i) + b_i$

2. 当 $a_i$ 在 $a_{i - 1}$ 前面

此时 $dp_i = \max(a_{i - 1}, \max(T, a_i + b_i), \min(\max(a_i, T, \min(dp_{i - 2}, a_i) + b_i), a_{i - 1}) + b_{i - 1})$。

- $a_{i - 1}$
- $T$
- $a_i + b_i$
- $a_i + b_{i - 1}$
- $\min(a_{i - 1}, T) + b_{i - 1}$
- $\min(\min(dp_{i - 2}, a_i) + b_i, a_{i - 1}) + b_{i - 1}$

对于第一、三、四项，情况 $1$ 显然更优。

对于第二项，两者相等。

对于情况 $2$ 的第五项，情况 $1$ 的第三项不劣于它。

对于情况 $2$ 的第六项，情况 $2$ 的第四项不劣于它。

于是我们成功证明了这个排序的正确性。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef struct {
	int a;
	int b;
} Color;

int dp[100007];
Color color[100007];

bool operator <(const Color a, const Color b){
	return a.a < b.a;
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, k;
		cin >> n >> k;
		for (int j = 1; j <= n; j++){
			cin >> color[j].a >> color[j].b;
		}
		if (color[1].a >= k){
			cout << "YES" << endl;
			continue;
		}
		if (n == 1 || color[1].a + color[1].b < k){
			cout << "NO" << endl;
			continue;
		}
		int pre = 0;
		sort(color + 2, color + n + 1);
		for (int j = 2; j <= n; j++){
			dp[j] = color[j].a;
			if (j > 2) dp[j] = max(dp[j], max(pre, min(dp[j - 1], color[j].a) + color[j].b));
			pre = max(pre, color[j].a + color[j].b);
		}
		if ((ll)dp[n] + color[1].b >= k){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：6)

$$\texttt{Preface}$$

赛场上被 $D$ 数数题卡死了，没时间看这题了…… ![](https://啧.tk/ll)

$$\texttt{Description}$$

[Doremy's Number Line](https://www.luogu.com.cn/problem/CF1764E)

$$\texttt{Solution}$$

一个数 $x$ 能被染成颜色 $i$，当且仅当 $x \le a_i$ 或存在一个数 $y$ 已经被染色，$y \le a_i$ 并且 $x \le y + b_i$。

我们需要把数字 $k$ 染成颜色 $1$，所以如果 $k > a_1 + b_1$ 就可以判无解了。

其次如果 $k \le a_1$ 那么肯定有解。

考虑接下来的情况：

我们将问题抽象为在数轴上，$\forall i \in (1, n]$，可以任选一个数 $a_i$ 作为起点，这样就有 $n - 2$ 条线段 $\forall j \in (1, n], j \ne i, [x, x + b_j], x \le a_j$，问能否用这些线段将区间 $[a_i, k]$ 覆盖。

注：这里对于同一个 $j$，只能选择一个 $x \le a_j$，然后加入线段 $[x, x + b_j]$。

如果能覆盖，假设线段分别为 $[x_1, y_1], [x_2, y_2], \cdots, [x_m, y_m]$。

我们依次对 $a_i, x_1, x_2, \cdots, x_m, k$ 进行染色，明显是合法的。

这就是一个比较经典的问题了。

我们先将 $2 \sim n$ 的所有数按照 $a_i$ 从大到小排序，然后设一个数 $num$ 表示从 $k$ 开始左端点最左能到哪里。

每次首先判断以当前点为起点能否与线段 $[num, k]$ 接上，可以设一个数组 $Max$ 存后缀的 $a_i + b_i$ 最大值，假设当前处理到 $i$，则如果 $a_i \ge num$ 或者 $Max_{i + 1} \ge num$，就能够接上，即有解了。

如果循环结束后仍然不能接上，则无解。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

#define N 100005
#define pa pair <int, int>
#define mp make_pair
#define fi first
#define se second

using namespace std;

int n, k, Max[N];
pa a[N];

void solve() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].fi >> a[i].se;
	}
	sort(a + 2, a + n + 1, greater <pa> ());
	if (k > a[1].fi + a[1].se) return cout << "No\n", void();
	if (k <= a[1].fi) return cout << "Yes\n", void();
	Max[ n + 1 ] = 0;
	for (int i = n; i; --i) Max[i] = max(Max[ i + 1 ], a[i].fi + a[i].se);
	k -= a[1].se;
	for (int i = 2; i <= n; ++i) {
		if (Max[ i + 1 ] >= k or a[i].fi >= k) return cout << "Yes\n", void();
		if (a[i].fi + a[i].se >= k) k -= a[i].se;
	}
	cout << "No\n";
}

int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：VinstaG173 (赞：2)

~~fk u corner case.~~

贪心+分类讨论。鸣谢 Spasmodic 的 hack 数据帮我找到原贪心的错误点。

对于一个数 $x$，如果我们想要将它染色 $i$，则考虑以下情况：

1. $x\le a_i$，此时直接染色即可；
2. $x>a_i+b_i$，此时一定无法染色；
3. $a_i<x\le b_i$，此时只要有其他点被染色即可；
4. $b_i<x\le a_i+b_i$，此时要先将一个不小于 $x-b_i$ 的数染成任意颜色。

注意到染色方法中所有限制条件都是不超过某个数即可染色，则对于“期望染成任意颜色”的点，若 $x$ 能染色，则不大于 $x$ 的所有点均能染色。因此 4 可改写为：

4. $b_i<x\le a_i+b_i$，此时要先将 $x-b_i$ 染成任意颜色。

接下来考虑 $k$ 能否染色 $1$ 由哪些因素决定。若对 $x=k,i=1$ 符合情况 1 或 2，则可以直接判定。若符合情况 3，则可以由除 $1$ 外是否有其他颜色直接判定。事实上即当且仅当 $n>1$ 时可以染色。

对于情况 4，此时只要将 $k-b_1$ 染成除 $1$ 外的任意颜色。我们看作是“花费一种颜色 $i$，将想要的 $k$ 减去 $b_i$”的一种操作。这种操作只有在 $b_i<k\le a_i+b_i$ 时才能进行。我们将每次遇到情况 4 时进行这个操作的 $i$ 记录下来，直到遇见情况 1,2,3 为止。考虑这个操作序列的性质。

注意到 $b_i\ge1$，且随着 $k$ 的减小能操作的颜色数不减，因此对于能够操作的 $i$，花费颜色 $i$ 减小 $k$ 一定不劣于不减小 $k$。因此我们认为有贪心策略：一旦存在颜色 $i$ 能够操作，就一定操作之。

发现某时刻能够操作的颜色在 $k$ 减小后依然能够操作，且将操作过的若干颜色 $i_1,i_2,\dots,i_m$ 操作顺序重排（在操作依然合法的情况下）后 $k$ 的最终值 $k-\sum\limits_{j=1}^mb_{i_j}$ 不变，因此我们可以进行合理的重排。不妨将操作序列以 $a_i+b_i$ 从大到小的顺序排序。显然这样排序后所有操作必定合法。

接下来我们认为对于 $i_1,i_2$，若 $a_{i_1}+b_{i_1}<a_{i_2}+b_{i_2}$，且 $i_1$ 在操作序列中，则 $i_2$ 必在操作序列中。由于操作 $i_1$ 时 $k\le a_{i_1}+b_{i_1}<a_{i_2}+b_{i_2}$，故只要 $k>b_{i_2}$，$i_2$ 便可以操作。由于可以操作必操作，且操作序列可以按 $a_i+b_i$ 从大到小排序，因此 $i_2$ 必被操作。若 $k\le b_{i_2}$，则此时存在 $i_1$ 尚未操作，已经可以结束染色。

因此最终操作序列必然为 $a_i+b_i$ 最大的若干个 $i$，操作结束后的 $k$ 不再符合情况 4，此时根据情况 1,2,3 即可作出判断。

综上，我们得到贪心策略：

1. 对于颜色 $1$ 判断是否符合情况 1,2,3，若为情况 4 则将 $k$ 变为 $k-b_1$；
2. 将颜色 $2,3,\dots,n$ 按 $a_i+b_i$ 从大到小排序；
3. 对于排序后的序列，每次取出 $a_i+b_i$ 最大且没有操作过的颜色，判断是否符合情况 1,2,3，若为情况 4 则将 $k$ 变为 $k-b_i$，重复进行这一步。

但是很遗憾，这样的贪心策略是错误的。以下是 Spasmodic 提供的 hack 数据：
```plain
3 141
140 1
50 90
99 50
```
对于这组数据，我们直接以 $a_i+b_i$ 排序后得到的颜色序列是 $3,2$，当前 $k=141-1=140$，对于 $i=3$ 符合情况 4。接下来当前 $k=140-50=90$，对于 $i=2$ 符合情况 3，但是此时已经没有其他颜色可以染了，于是我们判断结果为 `NO`。

但是我们发现若先操作颜色 $2$，会将 $k$ 变为 $140-90=50$，此时对于 $i=3$ 符合情况 1，故结果为 `YES`。

分析一下我们会发现问题出在最后的结论：对于 $i_1,i_2$，若 $a_{i_1}+b_{i_1}<a_{i_2}+b_{i_2}$，且 $i_1$ 在操作序列中，则 $i_2$ 必在操作序列中。进而分析发现策略“可以操作必操作”是存在问题的。

事实上这个结论在几乎所有情况下都是正确的，只有在一种情况下会出错，就是只剩下 $i_1,i_2$ 两种颜色未操作时。

这个错误出现的本质原因是情况 4 对于最后一种未染的颜色的后续不是进行操作，而是直接判定为 `NO` 并结束。因此若只剩下两种颜色可染，操作其中一种颜色后另一种颜色将不能被操作，“随着 $k$ 的减小能操作的颜色数不减”变为假命题。

这个错误的解决方案也很简单，由于只剩两种颜色，我们将它们的优先顺序调换后再做一次相同的贪心，只要有一次判定为 `YES` 即成功，否则判定为 `NO`。

时间复杂度瓶颈在排序的 $O(n\log n)$。

Code:
```cpp
int n,k,_k;
int id[100003];
int a[100003],b[100003];
inline int cmp(int x,int y){
	if(a[x]+b[x]==a[y]+b[y])
		return b[x]>=b[y];
	return a[x]+b[x]>a[y]+b[y];
}void solve(){rd(n);rd(k);
	for(rg int i=1;i<=n;++i){
		rd(a[i]);rd(b[i]);id[i]=i;
	}if(k<=a[1]){puts("YES");return;}
	if(k<=b[1]){puts((n>1)?"YES":"NO");return;}
	if(k>a[1]+b[1]){puts("NO");return;}
	k-=b[1];_k=k;sort(id+2,id+n+1,cmp);
	for(rg int _i=2,i;_i<=n;++_i){
		i=id[_i];if(a[i]+b[i]<k)break;
		if(k<=a[i]){puts("YES");return;}
		if(k<=b[i]&&_i<n){puts("YES");return;}
		k-=b[i];
	}if(n>2){id[n-1]^=id[n]^=id[n-1]^=id[n];k=_k;
		for(rg int _i=2,i;_i<=n;++_i){
			i=id[_i];if(a[i]+b[i]<k)break;
			if(k<=a[i]){puts("YES");return;}
			if(k<=b[i]){puts((_i<n)?"YES":"NO");return;}
			k-=b[i];
	}}puts("NO");
}
```

---

## 作者：Alex_Wei (赞：2)

显然，当 $a_1 \geq k$ 时有解， $a_1 + b_1 < k$ 时无解。此时有 $a_1 < k$ 且 $a_1 + b_1 \geq k$，则 $p_1$ 不可能为 $1$，我们将 $(a_1, b_1)$ 删去。

首先，因为可以点亮负数，所以 $x$ 必须未点亮这个限制可以当做不存在。

进一步地，如果 $x$ 可以被点亮，则任何小于 $x$ 的位置均可被点亮，这一点根据对 $x$ 的限制容易证明。因此，除了 $p_1$，其它 $p_i$ 对应的 $(a_{p_i}, b_{p_i})$ 都是尽量往数轴右侧扩张，使得可扩张到不小于 $k - b_1$ 的位置，若可以则有解，否则无解。

枚举 $p_1$，设 $c$ 表示当前扩张的位置，则接下来的每个 $(a, b)$ 都相当于 $c\gets \min(a, c) + b$。感性理解我们会先花掉 $a$ 较小的 $(a, b)$ 尽量扩张，使得花较大的 $(a, b)$ 时 $\min(a, c)$ 的限制尽量小。严谨证明直接考虑邻相交换即可。

不妨设 $a_i \leq a_{i + 1}$。

直接做的复杂度为 $\mathcal{O}(n ^ 2)$。但是若 $p_1 = k$，则所有 $j < k$ 的 $(a_j, b_j)$ 都会对 $c$ 产生 $a_j + b_j$ 的贡献。因此从小到大枚举 $k$，维护 $a_j + b_j$ 的前缀 $\max$，即可求出 $p_1 = k$ 时处理前 $k$ 个 $(a, b)$ 之后得到的 $c$。和 $p_1 < k$ 时处理前 $k - 1$ 个 $(a, b)$ 得到的最大的 $c$ 在经过 $(a_k, b_k)$ 更新后的值取 $\max$ 即可，可以看成一种动态规划。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1764/submission/183011552)。

---

## 作者：Komomo (赞：0)

考虑从终点开始贪心，维护一个状态 $sta$ 为目前只要起始坐标 $\ge sta$ 就是合法的，初始 $sta=k$。

然后开始贪心。动态维护目前状态能往前到达的点：如果有没选过的 $sta\le a_i$ 则有解，否则 set 里扔一堆 $sta \in (a_i,a_i+b_i]$ 的编号 $i$。

此时可以证明，贪心选 set 里面 $b$ 最大的就是最优的。

> 令当前 set 维护的编号集合为 $S$，对于 $b$ 最大的编号 $id$：
>
> - 如果 $|S|>1$，则从 $S\backslash \{id\}$ 选一个元素 $p$，因为有 $k\le a_p+b_p$，而 $k-b_{id}\le k-b_p\le a_p$，所以删完 $id$ 之后 $p$ 可以直接操作，有解。
> - 否则 $|S|=1$，此时 $id$ 是唯一可行操作，贪心的必然要进行。
>
> 综上，策略正确。

时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：honglan0301 (赞：0)

## 题意简述
有两个长度为 $n$ 的序列 $a_i,b_i$, 我们可以用一个顺序进行 $i$ 次操作（用排列 $p_i$ 表示）。在每次操作中，可以选择一个未被染色的数 $x\ (x\leq a_{p_i})$, 并将它染成第 $p_i$ 中颜色，或者选择一个已经被染色的数 $x\ (x\leq a_{p_i})$, 并将 $x+b_{p_i}$ 染成第 $p_i$ 中颜色。  

求能否使一个给定的数 $k$, 使其被染成第一种颜色。

## 题目分析
容易发现当 $a_1+b_1<k$ 时一定无解，当 $a_1\geq k$ 时一定有解，当 $b_1+\min(a_1,\max(a_2,...,a_n))$ 时也一定有解。而在对 $a_2,a_3,...,a_n$ 排序后这是可以推广的。当 $a_1+b_1\geq k$ 且 $a_1<k$ 时，我们只需要用其它的 $a_i,b_i$ 凑出来一个 $k-b_1$, 所以考虑递归处理，直到确定了有无解为止。  

## 代码
代码里写的循环，应该比较好理解。  

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t,n,k,a1,b1,maxx[100005];
struct mes
{
	int a;
	int b;
	int bh;
}mes[100005];
bool cmp(struct mes xx,struct mes yy)
{
	return xx.a<yy.a;
}
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		k=read();
		a1=read();
		b1=read();
		bool flag=0;
		for(int i=1;i<=n-1;i++)
		{
			mes[i].a=read();
			mes[i].b=read();
			mes[i].bh=i+1;
		}
		if(a1>=k)
		{
			cout<<"YES"<<endl;
			continue;
		}
		else if(a1+b1<k)
		{
			cout<<"NO"<<endl;
			continue;
		}
		sort(mes+1,mes+n,cmp);
		for(int i=1;i<=n-1;i++)
		{
			maxx[i]=max(maxx[i-1],mes[i].a+mes[i].b);//即满足aj<ai的所有j中，aj+bj的最大值。
		}
		int nowneed=k-b1;
		for(int nownum=n-1;nownum>=1;nownum--)
		{
			if(maxx[nownum-1]>=nowneed)//先用a[nownum]凑出一个足够大的被染色的数,再与之前最大的a+b构成nowneed，一定有解
			{
				flag=1;
				break;
			}
			if(mes[nownum].a>=nowneed)
			{
				flag=1;
				break;
			}
			if(mes[nownum].a+mes[nownum].b<nowneed)
			{
				flag=0;
				break;
			}
			nowneed=nowneed-mes[nownum].b;
		}
		if(flag)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
}
```


---

## 作者：Madefaker (赞：0)

##### CF1764E

【题意】
有 $n$ 个颜料，第 $i$ 个颜料 $c_i$ 有属性 $(a_i,b_i)$。
你可以按任何顺序在数轴上使用这 $n$ 个颜料，使用方式是：
在使用第 $i$ 个颜料的时候，你可以选择：
- 不大于 $a_i$ 的一个数并在上面作画，或者
- 选择一个不大于 $a_i$ 的已经作画的数 $j$ 并在数 $j + b_i$ 上作画。

能否让第 $1$ 个颜料在数 $k$ 上作画？

【分析】
首先如果可以在数 $i$ 上作画，那么也一定能在数 $\le i$ 上作画。因此只需要考虑最大能在哪个数上作画即可。

考虑倒着贪心，令全集 $U$ 为可以选择的颜料集合，$k$ 为目前需要达到的数。

首先最后一步必须使用颜料 $1$，因此如果 $a_1 \geq k$ 那么一定能（**返回 YES**），如果 $a_1 + b_1 < k$ 那么一定不能（**返回 NO**）。排除了这两种情况之后，剩下的是 $a_1 < k$ 且 $a_1 + b_1 \geq k$，这样需要后面的颜料帮助在 $\le k - b_1$ 的位置作画。于是 $k \rightarrow k-b_1$。
此时 $U$ 为 $\{c_i|i \in [2,n]\}$。

然后考虑上一步使用的 $c_i$，它一定要满足 $a_i + b_i \ge k$。设满足这个条件且可用（包含在 $U$ 中）的颜料的集合为 $T$。

注意到，如果存在 $a_j \ge a_i$，那么上上步用 $c_j$ 涂上 $a_i$，然后上一步用 $c_i$ 涂上 $k$，问题就结束了。

考虑若 $T$ 中包含大于等于两个元素，那么选择 $a_i$ 最小的那个 $i$ 即可（**返回 YES**）。若 $T$ 中包含零个元素，那么没法操作，一定不可（**返回 NO**）。故现在唯一要继续讨论下去的情况就是 $T$ 只包含一个元素的情况。

考虑这个时候只能使用这个元素。记这个元素为 $c_x$。若 $a_x \geq k$，可以直接使用 $c_x$ 染色，问题解决（**返回 YES**）。（这个地方容易漏掉，需要发现如果没有这个判断那么最后会出现明明能解决却没有解决的情况）
否则，$k \rightarrow k - b_x, U \rightarrow U \text{\\} c_x$，递归处理即可。

【实现】

需要维护 $T$ 集合，那么我们使用一个 set，把全集的排除 $c_x$ 操作替换成 set 的 erase 操作。并且每次 $k$ 发生变化的时候，我们要检查哪些元素新加进来了。

考虑检查的过程，是检查 $a_i + b_i \geq k$ 是否成立。为了时间复杂度正确，考虑先对 $a_i + b_i$ 从大到小排序，然后利用类似当前弧优化的思想，标记第一个没有满足上一次判断条件的是哪一个 $c$，下一次从这个开始即可。

另外有一个实现细节：使用 set 维护 $c$ 时，有可能遇到 $(a,b)$ 一模一样的两个颜料，set 可能会判断他们两个相等（set 判断相等是 `!(x < y) && !(y < x)`）。这时候我们需要在定义比较函数的时候额外加上一个 index 的比较，代表那两个颜料是不一样的。

注意 set 使用结构体内部比较函数的写法，类型应为 const bool type。
```cpp
bool operator<(const d &that) const {
    if(a != that.a) return a < that.a;
    else return ind < that.ind;
}
```

【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
int n, k; 
void cmax(int &x, int y) {if(x < y) x = y;}
void cmin(int &x, int y) {if(x > y) x = y;}
struct d {
    int a, b;
    int ind;
    bool operator<(const d &that) const {
        if(a != that.a) return a < that.a;
        else return ind < that.ind;
    }
}c[300010];
int cur = 0;
set<d> t;
bool solve(int k) {
    if(t.size() >= 2) return 1;
    else {
        if(t.size() == 0) return 0;
        d x = *(t.begin());
        if(x.a >= k) return 1;
        t.erase(x);
        k -= x.b;
        f(i, cur, n) {
            if(c[i].a + c[i].b >= k) t.insert(c[i]);
            else {
                cur = i;
                break;
            }            
            if(i == n) cur = n + 1;
        }
        return solve(k);
    }
}
bool ab(d x, d y) {return x.a + x.b > y.a + y.b;}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    time_t start = clock();
    //think twice,code once.
    //think once,debug forever.
    int T; cin >> T;
    while(T--) {
        t.clear();
        cur = 2;
        cin >> n >> k;
        f(i, 1, n) cin >> c[i].a >> c[i].b;
        f(i, 1, n) c[i].ind = i;
        sort(c + 2, c + n + 1, ab);
        if(c[1].a >= k) {
            cout << "YES\n";
            continue;
        }
        else if(c[1].a + c[1].b < k) {
            cout << "NO\n";
            continue;
        }
        else {
            k = k - c[1].b;
            f(i, 2, n) {
                if(c[i].a + c[i].b >= k) t.insert(c[i]);
                else {
                    cur = i;
                    break;
                }
                if(i == n) cur = n + 1;
            }
            cout << (solve(k) ? "YES\n": "NO\n");
        }
    }
    time_t finish = clock();
    //cout << "time used: " << (finish-start) * 1.0 / CLOCKS_PER_SEC <<"s"<< endl;
    return 0;
}
```

---

