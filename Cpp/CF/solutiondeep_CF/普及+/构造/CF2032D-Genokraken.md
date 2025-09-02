# 题目信息

# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7```

# AI分析结果

### 题目内容中文重写
这是一个交互式问题。

在清理完水岸区域后，格蕾特发现了一只名为海怪（Genokraken）的怪物，并将它控制起来进行科学研究。

怪物的神经系统可以构造成一棵包含 $n$ 个节点的树 $^{\dagger}$，节点编号从 $0$ 到 $n - 1$，其中节点 $0$ 为根节点。

格蕾特的目标是了解怪物神经系统的确切结构，更具体地说，她想知道树中 $p_1, p_2, \ldots, p_{n - 1}$ 的值，其中 $p_i$（$0 \leq p_i < i$）是节点 $i$（$1 \leq i \leq n - 1$）的直接父节点。

她并不确切知道节点的具体位置，但知道一些有用的信息：
- 如果移除根节点 $0$ 及其所有相邻边，这棵树将变成一个仅由路径 $^{\ddagger}$ 组成的森林。每个最初与节点 $0$ 相邻的节点都将是某条路径的端点。
- 节点的编号方式使得如果 $1 \leq x \leq y \leq n - 1$，那么 $p_x \leq p_y$。
- 节点 $1$ 恰好有两个相邻节点（包括节点 $0$）。

![不符合条件的树示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)
![不符合条件的树示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)
![不符合条件的树示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)
第一幅图中的树不满足条件，因为如果移除节点 $0$，那么节点 $2$（最初与节点 $0$ 相邻）将不是路径 $4 - 2 - 5$ 的端点。
第二幅图中的树不满足条件，因为必须满足 $p_3 \leq p_4$。
第三幅图中的树不满足条件，因为节点 $1$ 只有一个相邻节点。

格蕾特可以向控制舱进行询问：
- “? a b”（$1 \leq a, b < n$，$a \neq b$）——控制舱将检查节点 $a$ 和 $b$ 之间的简单路径是否包含节点 $0$。

然而，为了避免过度刺激生物而产生意外后果，格蕾特希望询问次数最多为 $2n - 6$ 次。尽管格蕾特很有天赋，但她无法一次性完成所有事情，那么你能帮她一把吗？

$^{\dagger}$ 树是一种连通图，其中每对不同的节点都恰好有一条简单路径相连。

$^{\ddagger}$ 路径是一种树，其顶点可以按 $v_1, v_2, \ldots, v_k$ 的顺序列出，使得边为 $(v_i, v_{i + 1})$（$1 \leq i < k$）。

### 说明/提示
在第一个测试用例中，海怪的神经系统形成了以下树：
![第一个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)
- “? 2 3” 的答案是 $1$。这意味着节点 $2$ 和 $3$ 之间的简单路径包含节点 $0$。

在第二个测试用例中，海怪的神经系统形成了以下树：
![第二个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)
- “? 2 3” 的答案是 $1$。这意味着节点 $2$ 和 $3$ 之间的简单路径包含节点 $0$。
- “? 2 4” 的答案是 $0$。这意味着节点 $2$ 和 $4$ 之间的简单路径不包含节点 $0$。

在第三个测试用例中，海怪的神经系统形成了以下树：
![第三个测试用例的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

### 样例 #1
#### 输入
```
3
4
1
5
1
0
9
```
#### 输出
```
? 2 3
! 0 0 1
? 2 3
? 2 4
! 0 0 1 2
! 0 0 0 1 3 5 6 7
```

### 题解综合分析与结论
这些题解的核心目标都是在不超过 $2n - 6$ 次询问的条件下，还原出给定树的结构。不同题解的思路和实现方法有所不同，但都充分利用了题目中树的特殊性质。
- **思路对比**：
    - 部分题解（如 elpsconr、xiaoyang222）采用从后往前构建树的方式，通过不断询问确定每个节点的父节点。
    - 部分题解（如 tai_chi、arrow_king、gyyyyx、2022dyx）从 $1$ 号节点入手，先确定 $1$ 号节点的子树，再逐步确定其他节点的位置。
    - littlebug 的题解则先求出 $1$ 的子树，再根据节点间的性质确定其他节点的父节点。
- **算法要点**：
    - 利用询问判断两个节点是否在同一条链上，从而确定节点的父节点。
    - 借助双指针、队列、优先队列等数据结构优化询问过程，减少询问次数。
- **解决难点**：
    - 如何在不超过 $2n - 6$ 次询问的限制下确定树的结构是关键难点。不同题解通过合理安排询问顺序和利用树的性质来解决这一问题。

### 评分较高的题解
- **elpsconr（5星）**
    - **关键亮点**：思路清晰，从后往前构建树的方法容易理解，询问次数少，代码简洁易懂。
    - **个人心得**：作者提到赛时受误导从 $1$ 出发正向构建树，后来发现从后往前构建更简单，体现了换个角度思考问题的重要性。
    - **核心代码**：
```cpp
inline void solve(){
  cin>>n;
  rep(i,1,n-1) a[i]=0;
  int l=n-2;
  rep_(i,n-1,1){
    while(l>0&&ask(i,l)) l--;
    a[i]=max(l--,0ll);
  }
  show();
}
```
核心实现思想：从最后一个节点 $n - 1$ 开始，用指针 $l$ 从 $n - 2$ 开始倒着枚举，若节点 $i$ 和 $l$ 之间的路径包含 $0$，则 $l$ 减 $1$，直到不包含 $0$ 时，$l$ 即为 $i$ 的父节点，同时更新 $l$。

- **tai_chi（4星）**
    - **关键亮点**：从 $1$ 号节点入手，思路较为直接，通过双指针移动确定节点的父节点，询问次数符合要求。
    - **核心代码**：
```cpp
void solve()
{
	int n; cin>>n;
	vector<int> p(n+5,0);
	p[1]=0;
	int t=0;
	for(int i=2;i<=n-1;i++)
	{
		int r=ask(1,i);
		if(r==0){t=i; break;}
		else p[i]=0;
	}
	p[t]=1;
	int now=2;
	for(int i=t+1;i<=n-1;i++)
	{
		while(ask(now,i)==1) now++;
		p[i]=now;
		now++;
	}
	cout<<"! ";
	for(int i=1;i<=n-1;i++) cout<<p[i]<<" ";
	cout<<endl;
}
```
核心实现思想：先依次询问 $(1,2),(1,3), \dots,(1,t)$ 直到答案为 $1$，确定 $t$ 为 $1$ 的儿子，且 $[2,t - 1]$ 的父亲都是 $0$。然后用双指针，一个指针 $i$ 从 $t + 1$ 开始遍历，另一个指针 $now$ 从 $2$ 开始，若 $ask(now, i) == 1$ 则 $now$ 加 $1$，直到不满足时，$now$ 即为 $i$ 的父节点。

- **arrow_king（4星）**
    - **关键亮点**：对询问和树结构的分析清晰，利用双指针判定剩余节点，合理利用树的性质减少询问次数。
    - **核心代码**：
```cpp
il void mian() {
	n=read();
	for(int i=2;i<=n;i++) fa[i]=-1;
	for(int i=2,lst=1;i<=n-1;i++) {
		int res=ask(i,1);
		if(!res) {
			fa[i]=lst,lst=i;
			if(!fst) fst=i;
		}
	} 
	for(int i=2;i<fst;i++) fa[i]=0;
	for(int i=fst+1,f=2;i<=n-1;i++) {
		if(fa[i]!=-1) {f=fa[i];continue;}
		while(f<i-1&&ask(f,i)) f++;
		fa[i]=f;
		f++;
	}
	printf("! ");
	for(int i=1;i<=n-1;i++) printf("%d ",fa[i]);putchar('\n');
	fflush(stdout);
	fst=0;
}
```
核心实现思想：先通过询问确定 $1$ 的子树，再确定 $[2,fst - 1]$ 的父亲为 $0$。然后用双指针，一个指针 $i$ 从 $fst + 1$ 开始遍历，另一个指针 $f$ 从 $2$ 开始，若 $ask(f, i) == 1$ 则 $f$ 加 $1$，直到不满足时，$f$ 即为 $i$ 的父节点。

### 最优关键思路或技巧
- **从特殊节点入手**：利用 $1$ 号节点的特殊性质，先确定其相关信息，为后续确定其他节点的位置提供基础。
- **双指针法**：通过两个指针的移动，合理安排询问顺序，减少不必要的询问，从而满足询问次数的限制。
- **逆向思维**：如从后往前构建树，避免了正向构建时可能遇到的复杂情况，简化了问题的解决过程。

### 可拓展之处
同类型题可能会有不同的树结构或询问方式，但核心思路都是利用给定的询问方式和树的性质来还原树的结构。类似算法套路包括利用双指针、队列等数据结构优化询问过程，以及从特殊节点入手逐步确定其他节点的信息。

### 洛谷相似题目推荐
- [P1268 树的重量](https://www.luogu.com.cn/problem/P1268)
- [P2146 [NOI2015] 软件包管理器](https://www.luogu.com.cn/problem/P2146)
- [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 个人心得摘录与总结
- elpsconr 提到赛时受题目误导从 $1$ 出发正向构建树，后来换个角度从后往前构建发现更简单。这提醒我们在解题时不要局限于常规思路，当遇到困难时可以尝试换个方向思考。

---
处理用时：73.87秒