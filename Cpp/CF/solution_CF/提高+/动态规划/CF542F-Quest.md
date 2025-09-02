# Quest

## 题目描述

Polycarp is making a quest for his friends. He has already made $ n $ tasks, for each task the boy evaluated how interesting it is as an integer $ q_{i} $ , and the time $ t_{i} $ in minutes needed to complete the task.

An interesting feature of his quest is: each participant should get the task that is best suited for him, depending on his preferences. The task is chosen based on an interactive quiz that consists of some questions. The player should answer these questions with "yes" or "no". Depending on the answer to the question, the participant either moves to another question or goes to one of the tasks that are in the quest. In other words, the quest is a binary tree, its nodes contain questions and its leaves contain tasks.

We know that answering any of the questions that are asked before getting a task takes exactly one minute from the quest player. Polycarp knows that his friends are busy people and they can't participate in the quest for more than $ T $ minutes. Polycarp wants to choose some of the $ n $ tasks he made, invent the corresponding set of questions for them and use them to form an interactive quiz as a binary tree so that no matter how the player answers quiz questions, he spends at most $ T $ minutes on completing the whole quest (that is, answering all the questions and completing the task). Specifically, the quest can contain zero questions and go straight to the task. Each task can only be used once (i.e., the people who give different answers to questions should get different tasks).

Polycarp wants the total "interest" value of the tasks involved in the quest to be as large as possible. Help him determine the maximum possible total interest value of the task considering that the quest should be completed in $ T $ minutes at any variant of answering questions.

## 说明/提示

In the first sample test all the five tasks can be complemented with four questions and joined into one quest.

In the second sample test it is impossible to use all the five tasks, but you can take two of them, the most interesting ones.

In the third sample test the optimal strategy is to include only the second task into the quest.

Here is the picture that illustrates the answers to the sample tests. The blue circles represent the questions, the two arrows that go from every circle represent where a person goes depending on his answer to that question. The tasks are the red ovals.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542F/36ecc7c1e696b10017232771921b21126dc31b0b.png)

## 样例 #1

### 输入

```
5 5
1 1
1 1
2 2
3 3
4 4
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 5
4 1
4 2
4 3
4 4
4 5
```

### 输出

```
9
```

## 样例 #3

### 输入

```
2 2
1 1
2 10
```

### 输出

```
10
```

# 题解

## 作者：YT0104 (赞：1)

# [CF542F-Quest](https://www.luogu.com.cn/problem/CF542F)

## 思路：

这道题目首先上来可以知道是要求构造一个完全二叉树，然后可以发现，这道题是不用给出方案的，所以可以想到 $dp$ 。

同时我们可以发掘一些显然的结论：

#### 1. $( T - t_i )$ 就是当前节点的深度。

因为当前节点可以放在 $0\sim ( T - t_i )$ 层之间，又因为如果放在当前的点还想让它有贡献就意味着它不能有子节点，所以肯定放在它的下界最优。

#### 2. 对于某一层肯定是优先选择 $q_i$ 最大的。

显然。

然后我们就可以设 $f[i][j]$ 表示在第 $i$ 层，占用了 $j$ 个节点（包括用于向下拓展和进行贡献的叶子节点）的最大价值。

再考虑转移，正着转移也不是不行，但是我们可以用一种更简单的方法：**倒着转移**：

因为当前一层占用了 $j$ 个点则上一层至少被占用了 $\lceil \frac{j}{2} \rceil$ 个点用于拓展，然后上一层的点还可以再占用 $k$ 个来用于贡献，所以：

$$ f[i-1][ \ \lceil \frac{j}{2}\rceil + k ] = \max ( f[i][j] + \sum_{i=1}^k q_i ,  f[i-1][ \ \lceil \frac{j}{2}\rceil + k ] ) $$

$\sum_{i=1}^k q_i$ 可以使用前缀和。

So：

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T;
vector<int>d[105],s[105];
int f[105][1005];
int main()
{
	cin>>n>>T;
	for(int i=1,t,q;i<=n;i++)
	{
		cin>>t>>q;
		d[T-t].push_back((-q));
	}
	for(int i=0;i<=101;i++)
	{
		sort(d[i].begin(),d[i].end());
		s[i].push_back(0);
		for(int j=1;j<=d[i].size();j++)
			s[i].push_back((s[i][j-1]-d[i][j-1]));
	}
	for(int i=T+1;i>=1;i--)
		for(int j=0;j<=n;j++)
			for(int k=0;k<s[i-1].size();k++)
				f[i-1][(j+1)/2+k]=max(f[i][j]+s[i-1][k],f[i-1][(j+1)/2+k]);
	cout<<f[0][1]<<'\n';
	return 0;
}
```

---

## 作者：Zhddd_ (赞：0)

来分析一下题目的性质：

1. 对于某一深度的任务，一定会优先选取 $q_i$ 最大的任务。

2. 如果某一深度 $i$ 占用了 $j$ 个节点，那么更浅的一层 $i-1$ 层，一定有至少 $\lceil j/2\rceil$ 个节点不能选任务。

设深度 $i$ 的任务分别为 $w_{i,1\sim k}$，且每个深度内按 $q$ 从大到小排序。

状态 $f_{i,j}$ 表示在深度 $i$ 占用了 $j$ 个节点的最大值，那么有状态转移：

$$f_{i-1,\lceil j/2\rceil+k}\gets\max\limits_{k=1}(f_{i,j}+\sum\limits_{p=1}^k w_{i-1,p})$$

初始时所有状态为 $0$，最终答案为 $f_{0,1}$。时间复杂度 $O(n^2T)$。

代码与上述内容基本保持一致，但 $k$ 的下标从 $0$ 开始，用 $s$ 来记录前缀和。

```cpp
int n, T, f[210][2010];
vector<int> w[110];
int main() {
	cin >> n >> T;
	for (int i = 1, a, b; i <= n; i++) {
		cin >> a >> b;
		w[T - a].push_back(-b); // 因为不想写 cmp，所以存负值。
	}
	for (int i = 0; i <= 100; i++) sort(w[i].begin(), w[i].end());
	for (int i = 101; i; i--) {
		for (int j = 0; j <= 1000; j++) {
			int s = 0;
			f[i - 1][(j + 1) / 2] = max(f[i - 1][(j + 1) / 2], f[i][j]);
			for (int k = 0; k < (int)w[i - 1].size(); k++) {
				s += w[i - 1][k];
				f[i - 1][(j + 1) / 2 + k + 1] = max(f[i - 1][(j + 1) / 2 + k + 1], f[i][j] - s);
			}
		}
	}
	cout << f[0][1] << '\n';
	return 0;
}
```

---

