# 题目信息

# Books Exchange (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

There are $ n $ kids, each of them is reading a unique book. At the end of any day, the $ i $ -th kid will give his book to the $ p_i $ -th kid (in case of $ i = p_i $ the kid will give his book to himself). It is guaranteed that all values of $ p_i $ are distinct integers from $ 1 $ to $ n $ (i.e. $ p $ is a permutation). The sequence $ p $ doesn't change from day to day, it is fixed.

For example, if $ n=6 $ and $ p=[4, 6, 1, 3, 5, 2] $ then at the end of the first day the book of the $ 1 $ -st kid will belong to the $ 4 $ -th kid, the $ 2 $ -nd kid will belong to the $ 6 $ -th kid and so on. At the end of the second day the book of the $ 1 $ -st kid will belong to the $ 3 $ -th kid, the $ 2 $ -nd kid will belong to the $ 2 $ -th kid and so on.

Your task is to determine the number of the day the book of the $ i $ -th child is returned back to him for the first time for every $ i $ from $ 1 $ to $ n $ .

Consider the following example: $ p = [5, 1, 2, 4, 3] $ . The book of the $ 1 $ -st kid will be passed to the following kids:

- after the $ 1 $ -st day it will belong to the $ 5 $ -th kid,
- after the $ 2 $ -nd day it will belong to the $ 3 $ -rd kid,
- after the $ 3 $ -rd day it will belong to the $ 2 $ -nd kid,
- after the $ 4 $ -th day it will belong to the $ 1 $ -st kid.

So after the fourth day, the book of the first kid will return to its owner. The book of the fourth kid will return to him for the first time after exactly one day.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
3
2 3 1
6
4 6 2 1 5 3
1
1
4
3 4 1 2
5
5 1 2 4 3
```

### 输出

```
1 1 1 1 1 
3 3 3 
2 3 3 2 1 3 
1 
2 2 2 2 
4 4 4 1 4 
```

# AI分析结果

### 题目内容重写

#### 书籍交换（困难版）

**题目描述**

简单版和困难版的唯一区别在于约束条件。

有 $n$ 个孩子，每个孩子都在读一本独特的书。在每一天结束时，第 $i$ 个孩子会将自己的书交给第 $p_i$ 个孩子（如果 $i = p_i$，则孩子将书交给自己）。保证所有 $p_i$ 的值都是 $1$ 到 $n$ 之间的不同整数（即 $p$ 是一个排列）。序列 $p$ 不会每天改变，它是固定的。

例如，如果 $n=6$ 且 $p=[4, 6, 1, 3, 5, 2]$，那么在第一天结束时，第 $1$ 个孩子的书将属于第 $4$ 个孩子，第 $2$ 个孩子的书将属于第 $6$ 个孩子，依此类推。在第二天结束时，第 $1$ 个孩子的书将属于第 $3$ 个孩子，第 $2$ 个孩子的书将属于第 $2$ 个孩子，依此类推。

你的任务是确定每个孩子的书第一次回到自己手中的天数，对于每个 $i$ 从 $1$ 到 $n$。

考虑以下示例：$p = [5, 1, 2, 4, 3]$。第 $1$ 个孩子的书将传递给以下孩子：

- 第 $1$ 天后，它将属于第 $5$ 个孩子，
- 第 $2$ 天后，它将属于第 $3$ 个孩子，
- 第 $3$ 天后，它将属于第 $2$ 个孩子，
- 第 $4$ 天后，它将属于第 $1$ 个孩子。

因此，在第 $4$ 天后，第 $1$ 个孩子的书将回到其主人手中。第 $4$ 个孩子的书将在第 $1$ 天后第一次回到他手中。

你需要回答 $q$ 个独立的查询。

### 算法分类
并查集、图论

### 题解分析与结论

本题的核心是找出每个孩子所在的环的长度，因为每个孩子最终都会回到自己手中，且这个过程会形成一个或多个循环。题解中主要采用了以下几种方法：

1. **DFS 或 BFS 遍历**：通过深度优先搜索或广度优先搜索遍历每个环，记录环的长度。
2. **并查集**：利用并查集数据结构来维护每个点所在的环，并记录环的大小。
3. **Tarjan 缩点**：通过 Tarjan 算法找到强连通分量，每个强连通分量对应一个环。

### 评分较高的题解

#### 作者：lzy120406 (赞：1)

**星级：4星**

**关键亮点：**
- 使用记忆化搜索的思想，避免了重复遍历，提高了效率。
- 代码简洁明了，易于理解。

**核心代码：**
```cpp
void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		p[i]--; // 转换为0-based
	}
	memset(ans,0,sizeof(ans));
	memset(vis,false,sizeof(vis));
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			vector<int> cyc;
			int cur = i;
			while (!vis[cur]) {
				vis[cur] = true;
				cyc.push_back(cur);
				cur = p[cur];
			}
			int len = cyc.size();
			for (int k : cyc) {
				ans[k] = len;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
}
```

#### 作者：JWRuixi (赞：0)

**星级：4星**

**关键亮点：**
- 直接暴力跳转并打标记，时间复杂度为 $O(n)$，效率高。
- 代码简洁，易于实现。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++) {
	if (vis[i]) continue;
	int len = 0, x = i;
	while (p[x] != i) vis[x] = 1, len++, x = p[x];
	vis[x] = 1, len++, x = i;
	while (p[x] != i) ans[x] = len, x = p[x];
	ans[x] = len;
}
```

#### 作者：scp020 (赞：0)

**星级：4星**

**关键亮点：**
- 使用记忆化搜索，减少了重复搜索的次数，提高了效率。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
inline int search(int pos,int t,int cnt)
{
	f[pos]=1;
	if(t==e[pos]) return ans[pos]=cnt+1;
	else return ans[pos]=search(e[pos],t,cnt+1);
}
```

### 最优关键思路或技巧

1. **记忆化搜索**：通过记录已经遍历过的点，避免重复搜索，提高效率。
2. **并查集**：利用并查集数据结构来维护每个点所在的环，并记录环的大小。
3. **Tarjan 缩点**：通过 Tarjan 算法找到强连通分量，每个强连通分量对应一个环。

### 可拓展之处

本题可以拓展到更复杂的图论问题，如寻找图中的所有环、计算每个环的长度等。类似的题目包括：

1. **P2661 信息传递**：通过并查集或 Tarjan 算法找到图中的最小环。
2. **P2127 序列排序**：通过并查集维护每个点所在的环，并计算环的大小。
3. **P3387 缩点**：通过 Tarjan 算法找到图中的强连通分量，并进行缩点操作。

### 推荐题目
1. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)
2. [P2127 序列排序](https://www.luogu.com.cn/problem/P2127)
3. [P3387 缩点](https://www.luogu.com.cn/problem/P3387)

---
处理用时：37.51秒