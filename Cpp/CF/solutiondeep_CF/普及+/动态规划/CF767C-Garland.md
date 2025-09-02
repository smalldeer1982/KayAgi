# 题目信息

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写

#### 题目描述

一次在新年时，Dima做了一个梦，梦中他得到了一串仙女灯饰。灯饰由若干灯泡组成，部分灯泡之间通过电线连接。Dima记得，灯饰中的任意两个灯泡都是直接或间接通过电线连接的。此外，电线的数量恰好比灯泡的数量少一个。

这串灯饰有一个特别之处：每个灯泡都有自己的亮度，亮度取决于灯泡的温度。温度可以是正数、负数或零。Dima有两个朋友，因此他决定将灯饰分享给他们。他想要剪断两条不同的电线，使得灯饰被分成三个部分。每个部分的亮度总和应该相等。当然，每个部分都必须是非空的，即每个部分至少包含一个灯泡。

### 样例 #1

#### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

#### 输出

```
1 4
```

### 样例 #2

#### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

#### 输出

```
-1
```

---

### 题解综合分析

本题的核心是将一棵树分成三个子树，且每个子树的权值和相等。题解的主要思路是通过DFS遍历树，计算每个子树的权值和，当某个子树的权值和等于总权值的三分之一时，记录该子树并将其权值清零。最终判断是否找到了至少两个符合条件的子树。

### 精选题解

#### 题解1：作者：无咕_ (赞：6)

**星级：5星**

**关键亮点：**
- 详细解释了树形DP的思路，特别是如何通过DFS计算子树权值和。
- 提供了清晰的剪枝策略，即当总权值不是3的倍数时直接输出-1。
- 代码结构清晰，注释详细，易于理解。

**核心代码：**
```cpp
void dfs(int now,int fa){
    treesum[now]=a[now];
    for(int i=head[now];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==fa)continue;
        dfs(to,now);
        treesum[now]+=treesum[to];
    }if(treesum[now]==sum/3)ans[++num_ans]=now,treesum[now]=0;
}
```

**个人心得：**
- 强调了树形DP的基本思路，即从叶子节点向上更新父节点的权值。
- 通过剪枝策略减少了不必要的计算，提高了代码效率。

#### 题解2：作者：kenlig (赞：5)

**星级：4星**

**关键亮点：**
- 提供了树形DP的详细推导过程，特别是如何通过DFS计算子树权值和。
- 强调了剪枝的重要性，即当总权值不是3的倍数时直接输出-1。
- 代码结构清晰，注释详细，易于理解。

**核心代码：**
```cpp
int dfs(int x,int fath){
	ksum[x]=a[x];
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(y!=fath){
			dfs(y,x);
			ksum[x]+=ksum[y];
		}
	}
	if(ksum[x]==sum){
		cnt++;
		ans[cnt]=x;
		ksum[x]=0;
	}
}
```

**个人心得：**
- 强调了树形DP的基本思路，即从叶子节点向上更新父节点的权值。
- 通过剪枝策略减少了不必要的计算，提高了代码效率。

#### 题解3：作者：chihik (赞：4)

**星级：4星**

**关键亮点：**
- 提供了树形DP的详细推导过程，特别是如何通过DFS计算子树权值和。
- 强调了剪枝的重要性，即当总权值不是3的倍数时直接输出-1。
- 代码结构清晰，注释详细，易于理解。

**核心代码：**
```cpp
void dfs(int u, int fa) {
	dp[u] = a[u];
	for(int v : Graph[u]) {
		if(v == fa) continue;
		dfs(v, u);
		dp[u] += dp[v];
		if(dp[v] == sum / 3) {
			if(!v1) v1 = v;
			else if(!v2) v2 = v;
			dp[u] -= dp[v];
		}
	}
}
```

**个人心得：**
- 强调了树形DP的基本思路，即从叶子节点向上更新父节点的权值。
- 通过剪枝策略减少了不必要的计算，提高了代码效率。

### 最优关键思路

1. **树形DP与DFS结合**：通过DFS遍历树，计算每个子树的权值和，当某个子树的权值和等于总权值的三分之一时，记录该子树并将其权值清零。
2. **剪枝策略**：当总权值不是3的倍数时，直接输出-1，减少不必要的计算。
3. **记录与判断**：通过记录符合条件的子树，最终判断是否找到了至少两个符合条件的子树。

### 拓展思路

- **类似题目**：可以考虑将树分成更多部分，或者要求每部分的权值和满足特定条件。
- **优化技巧**：可以通过预处理或记忆化搜索来进一步优化树形DP的效率。

### 推荐题目

1. [P2014 [CTSC1997]选课](https://www.luogu.com.cn/problem/P2014)
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

---
处理用时：41.79秒