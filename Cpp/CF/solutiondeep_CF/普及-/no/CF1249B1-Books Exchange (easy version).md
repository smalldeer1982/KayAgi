# 题目信息

# Books Exchange (easy version)

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

### 题目内容
# 书籍交换（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于数据范围限制。

有\(n\)个孩子，每个孩子都在读一本独特的书。在每一天结束时，第\(i\)个孩子会把他的书给第\(p_i\)个孩子（如果\(i = p_i\)，孩子会把书给自己）。保证所有\(p_i\)的值都是从\(1\)到\(n\)的不同整数（即\(p\)是一个排列）。序列\(p\)每天都不会改变，它是固定的。

例如，如果\(n = 6\)且\(p = [4, 6, 1, 3, 5, 2]\)，那么在第一天结束时，第\(1\)个孩子的书会属于第\(4\)个孩子，第\(2\)个孩子的书会属于第\(6\)个孩子，依此类推。在第二天结束时，第\(1\)个孩子的书会属于第\(3\)个孩子，第\(2\)个孩子的书会属于第\(2\)个孩子，依此类推。

你的任务是确定对于从\(1\)到\(n\)的每个\(i\)，第\(i\)个孩子的书第一次回到他手中是在哪一天。

考虑以下示例：\(p = [5, 1, 2, 4, 3]\)。第\(1\)个孩子的书会传递给以下孩子：
 - 在第\(1\)天后，它会属于第\(5\)个孩子，
 - 在第\(2\)天后，它会属于第\(3\)个孩子，
 - 在第\(3\)天后，它会属于第\(2\)个孩子，
 - 在第\(4\)天后，它会属于第\(1\)个孩子。

所以在第四天之后，第一个孩子的书会回到它的主人手中。第\(4\)个孩子的书会在恰好一天后第一次回到他手中。

你必须回答\(q\)个独立的查询。

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

### 算法分类
并查集（因为多数题解使用并查集解决问题，虽然也有DFS等方法，但并查集解法相对更突出）

### 题解综合分析与结论
这些题解主要围绕找出每个孩子的书回到自己手中所需天数这一核心问题。多数题解利用了数据中存在环的特性。难点在于如何高效地确定每个环的长度。
 - **思路方面**：有的题解使用并查集，将处于同一环的孩子合并到一个集合，通过集合元素个数确定环长；有的题解采用DFS搜索，直接模拟书的传递过程找到环长。
 - **算法要点**：并查集题解关键在于合并操作和查找集合代表元素；DFS题解关键在于递归搜索过程中记录传递次数。
 - **解决难点**：对于并查集，要正确实现合并和查找操作以准确划分环；对于DFS，要注意递归边界条件和传递次数的记录。

### 所选的题解
 - **作者：_Harrisonwhl_ （5星）**
   - **关键亮点**：思路清晰，利用并查集解决问题，代码简洁明了，直接实现并查集的查找、合并操作，并通过统计同一集合元素个数确定环长。
   - **重点代码**：
```cpp
int tf[205];//存没个元素的负责人。
int fd(int x)//查找本元素的负责人。
{
    if (x == tf[x]) return x;
    return tf[x] = fd(tf[x]);
}
void mg(int x,int y)//合并
{
    int a1 = fd(x),a2 = fd(y);
    if (a1!= a2)
        tf[a1] = a2;//更改为同一个负责人，进入一个并查集。
}
```
核心实现思想：`fd`函数实现路径压缩式的查找操作，找到元素所在集合的代表元素；`mg`函数实现合并操作，将两个不同集合合并为一个。
 - **作者：Karry5307 （4星）**
   - **关键亮点**：将排列写成置换形式并拆解成循环，通过DFS记录每个位置所在循环的大小，时间复杂度为\(O(qn)\)，且提到类似题目，拓展了思路。
   - **重点代码**：
```cpp
inline ll dfs(ll cur,ll cnt,ll tot)
{
	if(vis[cur])
	{
		return cnt;
	}
	vis[cur]=1,size[tot]++,bel[cur]=tot;
	return dfs(perm[cur],cnt+1,tot);
}
```
核心实现思想：通过DFS递归搜索，当访问到已访问节点时返回传递次数`cnt`，同时记录每个循环的大小`size`和每个节点所属循环`bel`。
 - **作者：信息学carryHarry （4星）**
   - **关键亮点**：同样采用并查集思路，代码结构清晰，注释详细，对并查集的查找、合并操作有明确实现，便于理解。
   - **重点代码**：
```cpp
int find(int x)//路径压缩
{
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y){//合并
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
	return ;
}
```
核心实现思想：`find`函数实现路径压缩的查找操作，`unionn`函数实现将两个不同集合合并的操作。

### 最优关键思路或技巧
利用并查集来处理环结构数据是本题较优的思路。通过并查集的合并和查找操作，可以高效地将处于同一环的元素归为一个集合，进而通过统计集合元素个数得到环的长度，即书回到原主人手中所需天数。

### 可拓展之处
同类型题通常围绕具有环结构的图数据展开，类似算法套路是在遇到有环的数据结构问题时，考虑使用并查集或DFS来处理环相关的计算。例如在一些涉及元素循环传递、位置循环变换等场景的题目中都可应用。

### 洛谷推荐题目
 - [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：经典的并查集应用题目，通过并查集判断亲戚关系，与本题使用并查集处理元素关系类似。
 - [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)：利用并查集解决带权值的元素关系问题，可拓展对并查集应用的理解。
 - [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：结合图论和并查集，在动态变化的图结构中使用并查集处理连通性问题，与本题处理环结构有一定关联。

### 个人心得摘录与总结
无。 

---
处理用时：71.47秒