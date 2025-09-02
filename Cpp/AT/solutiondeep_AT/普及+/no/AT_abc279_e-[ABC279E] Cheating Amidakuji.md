# 题目信息

# [ABC279E] Cheating Amidakuji

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_e

<!-- 
$ N $ 本の縦棒と、それらの間を結ぶ $ M $ 本の横棒からなるあみだくじがあります。
各横棒は縦棒と垂直に引かれていて、その高さは相異なります。
縦棒を左から順に $ 1,2,\dots,N $、横棒を上から順に $ 1,2,\dots,M $ としたとき、
横棒 $ i\ (1\ \leq\ i\ \leq\ M) $ は縦棒 $ A_i $ と縦棒 $ A_i+1 $ の間を結んでいます。

縦棒 $ 1 $ の上端からあみだくじを下に辿っていったとき、最終的に到達する縦棒の番号を**スコア**と定義します。

$ i=1,2,\dots,M $ について、以下の質問に答えてください。

- 横棒 $ i $ を消したときのスコアを $ S_i $ と定義する。$ S_i $ を求めよ。

なお、実際には横棒は消さないため、各質問は独立であることに注意してください。

より厳密には、以下の通りです。
-->$ 1 $ 以上 $ N-1 $ 以下の整数からなる長さ $ M $ の数列 $ A=(A_1,A_2,\dots,A_M) $ が与えられます。 $ i=1,2,\dots,M $ について、以下の質問に答えてください。

- 数列 $ B=(B_1,B_2,\dots,B_N) $ がある。最初、各 $ j $ について $ B_j=j $ である。今から、$ k=1,2,\dots,i-1,i+1,\dots,M $ の順に以下の操作を行う （すなわち、$ i $ を除いた $ 1 $ 以上 $ M $ 以下の整数 $ k $ について、昇順に以下の操作を行う）。
  - $ B_{A_k} $ と $ B_{A_k+1} $ の値を入れ替える。
- 全ての操作が終了した段階で、$ B_j=1 $ を満たす $ j $ の値を $ S_i $ と定義する。$ S_i $ を求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N-1\ (1\leq\ i\ \leq\ M) $
- 入力は全て整数
 
### Sample Explanation 1

$ i\ =\ 2 $ のとき、操作によって $ B $ は以下のように変化します。 - 最初、$ B\ =\ (1,2,3,4,5) $ - $ k=1 $ として操作を行う。すなわち $ B_1 $ と $ B_2 $ の値を入れ替えて、$ B\ =\ (2,1,3,4,5) $ - $ k=3 $ として操作を行う。すなわち $ B_3 $ と $ B_4 $ の値を入れ替えて、$ B\ =\ (2,1,4,3,5) $ - $ k=4 $ として操作を行う。すなわち $ B_2 $ と $ B_3 $ の値を入れ替えて、$ B\ =\ (2,4,1,3,5) $ 全ての操作が終了した段階で $ B_3=1 $ であるため、$ S_2\ =\ 3 $ です。 同様に、 - $ i=1 $ のとき：$ k=2,3,4 $ の順に操作を行うと $ B=(1,4,3,2,5) $ になるので、$ S_1=1 $ - $ i=3 $ のとき：$ k=1,2,4 $ の順に操作を行うと $ B=(2,1,3,4,5) $ になるので、$ S_3=2 $ - $ i=4 $ のとき：$ k=1,2,3 $ の順に操作を行うと $ B=(2,3,4,1,5) $ になるので、$ S_4=4 $ です。

## 样例 #1

### 输入

```
5 4

1 2 3 2```

### 输出

```
1

3

2

4```

## 样例 #2

### 输入

```
3 3

2 2 2```

### 输出

```
1

1

1```

## 样例 #3

### 输入

```
10 10

1 1 1 9 4 4 2 1 3 3```

### 输出

```
2

2

2

3

3

3

1

3

4

4```

# AI分析结果

### 题目内容重写

#### [ABC279E] Cheating Amidakuji

**题目描述**

有 $N$ 根垂直的棒子和 $M$ 根水平的棒子组成的“あみだくじ”（一种抽签游戏）。每根水平棒子连接相邻的两根垂直棒子，且高度各不相同。垂直棒子从左到右依次编号为 $1,2,\dots,N$，水平棒子从上到下依次编号为 $1,2,\dots,M$。第 $i$ 根水平棒子连接垂直棒子 $A_i$ 和 $A_i+1$。

定义**分数**为从垂直棒子 $1$ 的顶端开始往下走，最终到达的垂直棒子的编号。

对于 $i=1,2,\dots,M$，回答以下问题：

- 定义 $S_i$ 为去掉第 $i$ 根水平棒子后的分数。求 $S_i$。

注意，实际上水平棒子不会被去掉，因此每个问题都是独立的。

更严格地说，给定一个长度为 $M$ 的数列 $A=(A_1,A_2,\dots,A_M)$，其中 $A_i$ 是 $1$ 到 $N-1$ 之间的整数。对于 $i=1,2,\dots,M$，回答以下问题：

- 有一个数列 $B=(B_1,B_2,\dots,B_N)$。初始时，$B_j=j$。现在，按照 $k=1,2,\dots,i-1,i+1,\dots,M$ 的顺序执行以下操作（即去掉第 $i$ 个操作，按升序执行剩下的操作）：
  - 交换 $B_{A_k}$ 和 $B_{A_k+1}$ 的值。
- 所有操作结束后，定义 $S_i$ 为满足 $B_j=1$ 的 $j$ 的值。求 $S_i$。

**说明/提示**

**约束条件**

- $2 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq A_i \leq N-1$（$1 \leq i \leq M$）
- 输入均为整数

**样例解释**

样例1：

输入：

```
5 4
1 2 3 2
```

输出：

```
1
3
2
4
```

### 算法分类

**模拟**

### 题解分析与结论

本题的核心在于模拟操作过程，并高效地处理每个查询。由于每次查询都是独立的，且需要去掉一个操作，直接暴力模拟会导致时间复杂度过高。因此，各题解主要通过预处理和优化模拟过程来解决这个问题。

### 精选题解

#### 题解1：FFTotoro（★★★★★）

**关键亮点**：
- 通过预处理记录每次操作的影响，避免了重复模拟。
- 利用数组记录最终位置，直接查询结果，时间复杂度为 $O(N+M)$。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[200001],y[200001],b[200001],c[200001];
int main(){
  int n,m; cin>>n>>m;
  vector<int> a(m);
  iota(b+1,b+n+1,1);
  for(int i=0;i<m;i++){
    cin>>a[i]; x[i]=b[a[i]],y[i]=b[a[i]+1];
    swap(b[a[i]],b[a[i]+1]);
  } // 模拟正常操作
  for(int i=1;i<=n;i++)c[b[i]]=i; // 记录 c 数组
  for(int i=0;i<m;i++){
    if(x[i]==1)cout<<c[y[i]]<<endl; // 1 是第一个操作数
    else if(y[i]==1)cout<<c[x[i]]<<endl; // 1 是第二个操作数
    else cout<<c[1]<<endl;
  }
  return 0;
}
```

#### 题解2：Daidly（★★★★☆）

**关键亮点**：
- 通过记录每个数的最终位置，减少了模拟的复杂度。
- 利用轨迹变化的思想，直接推导出结果。

**核心代码**：
```cpp
// Problem: E - Cheating Amidakuji
// Contest: AtCoder - TOYOTA SYSTEMS Programming Contest 2022(AtCoder Beginner Contest 279)
// URL: https://atcoder.jp/contests/abc279/tasks/abc279_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, m, a[N], p[N], pos[N], ans[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void swp(int i) {
	int x = p[i], y = p[i+1];
	swap(p[i], p[i+1]);
	swap(pos[x], pos[y]);
}
void calc(int& i) {i = pos[i];}
void solve(int L, int R, int now) {
	if(L == R) {
		ans[L] = now;
		return;
	}
	int M = (L + R) >> 1;
	{
		solve(L, M, now);
		rep(i, M+1, R) swp(a[i]);
		rep(i, L, M) calc(ans[i]);
		per(i, R, M+1) swp(a[i]);
	}
	{
		rep(i, L, M) swp(a[i]);
		calc(now);
		per(i, M, L) swp(a[i]);
		solve(M+1, R, now);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) scanf("%d", &a[i]);
	rep(i, 1, n) p[i] = pos[i] = i;
	solve(1, m, 1);
	rep(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
```

#### 题解3：OMG_wc（★★★★☆）

**关键亮点**：
- 通过预处理最终位置，简化了查询过程。
- 直接模拟交换过程，减少了不必要的计算。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

int a[N], b[N], p[N];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) b[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        swap(b[a[i]], b[a[i] + 1]);
    }
    for (int i = 1; i <= n; i++) p[b[i]] = i;
    for (int i = 1; i <= n; i++) b[i] = i;
    for (int i = 1; i <= m; i++) {
        int ans = p[1];
        if (b[a[i]] == 1)
            ans = p[b[a[i] + 1]];
        else if (b[a[i] + 1] == 1)
            ans = p[b[a[i]]];
        printf("%d\n", ans);
        swap(b[a[i]], b[a[i] + 1]);
    }
    return 0;
}
```

### 最优关键思路

1. **预处理最终位置**：通过模拟所有操作，记录每个数的最终位置，从而在查询时直接获取结果。
2. **轨迹变化**：通过分析去掉某个操作后对轨迹的影响，直接推导出结果，避免了重复模拟。
3. **分治思想**：利用分治的方法，将问题划分为更小的子问题，分别处理后再合并结果。

### 可拓展之处

类似的问题可以通过预处理和优化模拟过程来解决，特别是在需要处理大量独立查询时。分治和轨迹变化的思想可以应用于其他需要处理操作序列的问题。

### 推荐题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得

- **调试经历**：在模拟过程中，确保每一步操作的正确性非常重要，特别是在处理大量数据时，一个小错误可能导致整个结果出错。
- **顿悟感想**：通过预处理和优化模拟过程，可以显著提高算法的效率，特别是在处理大规模数据时。

---
处理用时：62.18秒