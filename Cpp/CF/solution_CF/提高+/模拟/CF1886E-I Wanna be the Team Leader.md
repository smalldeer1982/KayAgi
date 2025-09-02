# I Wanna be the Team Leader

## 题目描述

Monocarp是一家大型IT公司的团队负责人。

他的编程团队需要完成 $ m $ 个项目，编号从 $ 1 $ 到 $ m $ 。第 $ i $ 个项目的难度级别为 $ b_i $ 。

团队中有 $ n $ 名程序员，编号从 $ 1 $ 到 $ n $ 。第 $ j $ 名程序员具有应对压力的能力水平 $ a_j $ 。

Monocarp希望以以下方式分配程序员到项目中：

- 每个程序员最多只能分配给一个项目；
- 每个项目至少有一个程序员被分配；
- 假设有 $ k $ 名程序员被分配到第 $ i $ 个项目；那么所有被分配的程序员的应对压力水平必须大于或等于 $ \frac{b_i}{k} $ 。

帮助Monocarp找到一个有效的分配方案。如果存在多个答案，随意输出一个即可。

## 样例 #1

### 输入

```
5 3
4 6 100 5 1
50 1 12```

### 输出

```
YES
1 3
1 5
3 2 4 1```

## 样例 #2

### 输入

```
5 3
3 6 100 5 1
50 1 12```

### 输出

```
NO```

## 样例 #3

### 输入

```
5 3
2 2 2 2 4
3 5 1```

### 输出

```
YES
1 5
3 1 2 3
1 4```

## 样例 #4

### 输入

```
5 1
10 20 30 40 50
4```

### 输出

```
YES
1 4```

# 题解

## 作者：EuphoricStar (赞：8)

把题意抽象成，给你长为 $n$ 的序列 $a$ 和长为 $m$ 的序列 $b$，初始有 $m$ 个空集合（可重集），$a$ 中的每个元素至多被分到 $m$ 个集合中的一个。要求最后第 $i$ 个集合 $T_i$ 不为空，且 $\forall x \in T_i, x \ge \frac{b_i}{|T|}$。要求构造方案或报告无解。

先把 $a$ 从大到小排序。发现最后每个集合分到的一定是在排序后序列的一段区间。因为 $11121222$ 显然比 $11112222$ 劣。

然后考虑一个从前往后分配集合元素的可行性 dp。设 $f_{i, S}$ 为当前 $a$ 中 $[1, i]$ 的元素被分配完了，$S$ 为已经考虑完的集合的编号集合为 $S$。转移枚举下一段的右端点 $j$，枚举 $[i + 1, j]$ 被分到第 $k$ 个集合，有 $f_{j, S \cup \{k\}} \gets f_{i, S}$。要求 $a_j \ge \frac{b_k}{j - i}$。

发现这个 dp 太蠢了。考虑直接把第一维塞进 dp 值中。重新设 $f_S$ 为已经考虑完的集合的编号集合为 $S$，若 $[1, i]$ 被分配完了，$i$ 的**最小值**。预处理出 $g_{i, j}$ 表示最小的 $k$ 使得 $a_k \ge \frac{b_i}{k - j}$，转移考虑枚举下一个集合是第 $k$ 个，有 $f_{S \cup \{k\}} \gets g_{k, f_S + 1}$。

求 $g$ 可以双指针，因为 $g_{i, j}$ 随 $j$ 增大而不降。所以整个的复杂度就是 $O((n + 2^m) m + n \log n)$。

[code](https://codeforces.com/contest/1886/submission/227815602)

---

## 作者：LYH_cpp (赞：6)

对于每个 Project，我们只关心参与者的数量 $k$ 和当中最小的 $a_i$。

结合样例玩一玩，不难推出一个性质：

若我们将 $a$ 从大到小排序，每个所选的 Programmers 一定是连续的一段。

注意这里 $a$ 从是大到小排序而不是从小到大，因为 $a_i$ 很小的人我们是可以让他不去的，换句话说如果从小到大排序我们不知道第一段的起点在哪里。

剩下就是考虑每个项目分到第几段和每一段的起止点。

我们尝试每次从已排序的 $a$ 中删去一段前缀，

根据贪心，当考虑到项目 $i$ 时，我们要选所有可行方案中参加人数最少的，因为我们要留出尽可能多的人到后面给 $a_i$ 较小的人当陪衬。

这个 $m\le 20$ 一看就是个状压。

设 $f_S$ 表示分配好的项目集合为 $S$，最少需要多少人。

那么有转移 $f_{S\cup\{i\}}\gets f_S+k,(\frac{b_i}{k} \le a_{f_S+k})$。

但是这里因为是从大到小排序，所以我们不能往后二分求 $k$。

我们设 $k=g_{i,j}$ 表示对于项目 $i$，让其从 $j$ 开始选至少要选到 $k$，我们发现对于  $g_i$，$j$ 是单调递增的，可以双指针预处理。

转移变成 $f_{S\cup\{i\}}\gets g_{i,f_S+1}$。

时间复杂度 $O(n \log_2n+nm+2^m)$。

完结撒花。

[$\texttt{Submission}$](https://codeforces.com/contest/1886/submission/228649806)

---

## 作者：Xy_top (赞：6)

离 E 最近的一次，仅仅是数组开小了。

一道很简单的题，首先有一个很重要的性质就是将输入的程序员按照能力从小到大排序，每个任务分配的人员一定是连续的一段。

证明考虑反证，如果某个任务的完成必须不是连续的一段。

任务 $1$ 由 $[1,3]$ $[6,7]$ 的程序员完成，任务二由 $[4,5]$ 的程序员完成。那么完全可以把 $[6,7]$ 拖到前面来，这样任务 $1$ 就由 $[1,5]$ 完成，任务二是 $[6,7]$。

这样一定是对的，因为数组排好了序，一个任务分给若干个程序员能否完成只与其中能力值最小的程序员有关，这样改变的计划后做任务 $1$ 的能力值最小的没变，长度也没变，做任务 $2$ 的能力值最小的变大，长度也没变。

这个结论就这样大概证完了。

然后看到 $m\leq 20$，容易想到状压，最简单的设 $f_{i,j}$ 为前 $i$ 个数，每个任务分配完了没的状态为 $j$ 时是否可行，暂且不管时间空间，这个方法是行的。

然而时间空间都会爆炸，所以进行状态上的优化把 $i$ 作为 $f$ 的结果这样就成了：$f_j$ 为每个任务分配完了没的状态为 $j$ 时最小的 $i$ 使得将 $1\cdots i$ 的程序员分配给这些任务是可以完成的。

转移时需要预处理一个东西，对于每个任务，每个程序员为起点，完成这个任务最少要分配到后面的哪个程序员，显然可以 $O(n\times m)$，算的时候对于每个程序员考虑他作为能力值最小的往后延若干个完成任务，然后预处理后缀最值。

这样就写完了，对于任务的输出可以对每个状态存储来的位置，以及一些其他必要的信息。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m;
int c[1 << 20];
int f[1 << 20], pre[21];//分配 j 这些任务使得 1 ~ i 的人能够完成任务的最小的 i
int come[1 << 20];
int comee[1 << 20], doo[1 << 20];
int p[21][200005];//对于第 i 个任务，从 j 往后分配程序员，最少到哪里能完成这个任务
pair <int, int> cc[200005];
struct Node {int x, y;}a[200005], b[200005];
bool cmp (Node n1, Node n2) {return n1.x < n2.x;}
vector <int> ans[200005];
void init () {
	For (i, 1, m) {
		memset (c, 0x3f, sizeof c);
		For (j, 1, n) {//枚举开始的任务
			//那么将在 j + [b[i] / a[j]] - 1 的位置完成，更新最值
			//此时将 p[i][1 ~ j] 更新为 
			c[j] = j + (b[i].x - 1) / a[j].x;
			//查 p[i][j] 就查 1 ~ n - j + 1 中最小的
		}
		foR (j, n, 1) c[j] = min (c[j], c[j + 1]);
		For (j, 1, n) p[i][j] = c[j];
	}
}
void solve () {
	For (i, 0, 19) pre[i] = 1 << i;
	memset (f, 0x3f, sizeof f);
	cin >> n >> m;
	if (n < m) {
		cout << "NO";
		return;
	}
	For (i, 1, n) {
		cin >> a[i].x;
		a[i].y = i;
	}
	For (i, 1, m) {
		cin >> b[i].x;
		b[i].y = i;
	}
	sort (a + 1, a + n + 1, cmp);
	sort (b + 1, b + m + 1, cmp);
	init ();
	f[0] = 0;
	For (i, 1, 1 << m) {
		For (j, 0, m - 1) {
			if (i & pre[j]) {
				int k = i ^ pre[j];
				if (f[k] < n && p[j + 1][f[k] + 1] <= n) {
					f[i] = p[j + 1][f[k] + 1];
					come[i] = k;
					cc[i] = mp (f[k] + 1, p[j + 1][f[k] + 1]);
					doo[i] = j + 1;
				}
			}
		}
	}
	if (f[(1 << m) - 1] <= n) cout << "Yes" << '\n';
	else {
		cout << "No";
		return;
	}
	int st = (1 << m) - 1;
	while (st) {
		int len = 0, sum = 0;
		foR (i, cc[st].second, cc[st].first) {
			++ len;
			sum += a[i].x;
			ans[b[doo[st]].y].push_back (a[i].y);
			if (a[i].x * len >= b[doo[st] ].x) break;
		}
		st = come[st];
	}
	For (i, 1, m) {
		cout << ans[i].size () << ' ';
		for (int j : ans[i]) cout << j << ' ';
		cout << '\n';
	}
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
/*
5 3
1 4 5 6 100
1 12 50
*/

```


---

## 作者：gdf_yhm (赞：3)

[CF1886E](https://www.luogu.com.cn/problem/CF1886E)

### 思路

观察发现每个项目只与程序员数量和最小值有关，所以每个项目对应能力值连续的程序员最优。

项目数 $m\le 20$，状压。设 $dp_{i,s}$ 为前 $i$ 个程序员匹配的项目状态为 $s$ 是否可行，无法接受。交换维度，改为 $dp_s$ 表示状态 $s$ 能与前缀 $[1,i]$ 匹配的最小 $i$。

不要求全选程序员，全选不一定优。预处理 $f_{i,s}$ 表示第 $i$ 个项目从 $j$ 开始匹配程序员，最少要匹配到哪里。$f_{i,j}=\min(f_{i,j+1},j+\lceil\frac{b_i}{a_j}\rceil-1)$。

### code

```cpp
int n,m;
pii a[maxn];int b[maxn];
int dp[1<<20],pre[1<<20],f[20][maxn];
pii pos[20];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]={read(),i};
	for(int i=0;i<m;i++)b[i]=read();
	sort(a+1,a+n+1);
	for(int i=0;i<m;i++){
		f[i][n+1]=n+1;
		for(int j=n;j;j--)f[i][j]=min(f[i][j+1],j+(b[i]+a[j].fi-1)/a[j].fi-1);
	}
	mems(dp,0x3f);dp[0]=0;
	for(int s=1;s<(1<<m);s++){
		for(int i=0;i<m;i++)if(s&(1<<i)){
			if(dp[s^(1<<i)]>=n)continue;
			if(f[i][dp[s^(1<<i)]+1]<dp[s])dp[s]=f[i][dp[s^(1<<i)]+1],pre[s]=i;
		}
	}
	if(dp[(1<<m)-1]>n){printf("NO\n");return ;}
	printf("YES\n");
	int s=(1<<m)-1;
	while(s){
		for(int i=dp[s^(1<<(pre[s]))]+1;i<=dp[s];i++)if(f[pre[s]][i]!=f[pre[s]][i+1]){
			pos[pre[s]]={i,dp[s]};
			break;
		}
		s^=(1<<pre[s]);
	}
	for(int i=0;i<m;i++){
		printf("%lld ",pos[i].se-pos[i].fi+1);
		for(int j=pos[i].fi;j<=pos[i].se;j++)printf("%lld ",a[j].se);printf("\n");
	}
}
```

---

## 作者：Helenty (赞：0)

假定我们 $i$ 项目要搞 $k_i$ 个那么我们肯定取不低于 $\dfrac{b_i}{k_i}$ 的 $k_i$ 个。

这意味着最后我们一定可以调整成每个项目是一个压力区间的人。

那么我们按压力从大到小排序，一定是一段前缀被取了。

那么我们直接设 $f_{S}$ 表示 $S$ 内的项目已经搞定需要用的最小前缀。

转移就二分是容易的。

复杂度就是 $O(2^mm\log n)$。

---

