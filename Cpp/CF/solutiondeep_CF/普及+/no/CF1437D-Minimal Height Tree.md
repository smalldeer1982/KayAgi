# 题目信息

# Minimal Height Tree

## 题目描述

Monocarp had a tree which consisted of $ n $ vertices and was rooted at vertex $ 1 $ . He decided to study BFS ([Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)), so he ran BFS on his tree, starting from the root. BFS can be described by the following pseudocode:

```
a = [] # the order in which vertices were processed
q = Queue()
q.put(1) # place the root at the end of the queue
while not q.empty():
    k = q.pop() # retrieve the first vertex from the queue
    a.append(k) # append k to the end of the sequence in which vertices were visited
    for y in g[k]: # g[k] is the list of all children of vertex k, sorted in ascending order
        q.put(y)
```
Monocarp was fascinated by BFS so much that, in the end, he lost his tree. Fortunately, he still has a sequence of vertices, in which order vertices were visited by the BFS algorithm (the array a from the pseudocode). Monocarp knows that each vertex was visited exactly once (since they were put and taken from the queue exactly once). Also, he knows that all children of each vertex were viewed in ascending order.

Monocarp knows that there are many trees (in the general case) with the same visiting order $ a $ , so he doesn't hope to restore his tree. Monocarp is okay with any tree that has minimum height.

The height of a tree is the maximum depth of the tree's vertices, and the depth of a vertex is the number of edges in the path from the root to it. For example, the depth of vertex $ 1 $ is $ 0 $ , since it's the root, and the depth of all root's children are $ 1 $ .

Help Monocarp to find any tree with given visiting order $ a $ and minimum height.

## 说明/提示

In the first test case, there is only one tree with the given visiting order:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/410231d5450c97d8a337f65673d6193fef7ef91a.png)In the second test case, there is only one tree with the given visiting order as well:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/7a0ba94b1eb3ad4817eb8aa8e139c5ce715f4da2.png)In the third test case, an optimal tree with the given visiting order is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/aa50643bf81bba2c4eca6a0d6c99c8ba0b01c205.png)

## 样例 #1

### 输入

```
3
4
1 4 3 2
2
1 2
3
1 2 3```

### 输出

```
3
1
1```

# AI分析结果

### 题目翻译
# 最小高度树

## 题目描述
Monocarp 有一棵由 $n$ 个顶点组成的树，根节点为顶点 $1$。他决定研究广度优先搜索（BFS，[Breadth - first search](https://en.wikipedia.org/wiki/Breadth - first_search)），于是他从根节点开始，对他的树进行了 BFS 遍历。BFS 可以用以下伪代码描述：
```
a = [] # 顶点被处理的顺序
q = Queue()
q.put(1) # 将根节点放入队列尾部
while not q.empty():
    k = q.pop() # 从队列头部取出第一个顶点
    a.append(k) # 将 k 追加到访问顶点的序列末尾
    for y in g[k]: # g[k] 是顶点 k 的所有子节点列表，按升序排列
        q.put(y)
```
Monocarp 对 BFS 非常着迷，最后他弄丢了他的树。幸运的是，他仍然有一个 BFS 算法访问顶点的顺序序列（伪代码中的数组 a）。Monocarp 知道每个顶点只被访问一次（因为它们只被放入和取出队列一次）。此外，他知道每个顶点的所有子节点都是按升序查看的。

Monocarp 知道（一般情况下）有很多树具有相同的访问顺序 $a$，所以他不指望恢复他的树。Monocarp 对任何具有最小高度的树都能接受。

树的高度是树中顶点的最大深度，顶点的深度是从根节点到该顶点的路径中的边数。例如，顶点 $1$ 的深度为 $0$，因为它是根节点，而所有根节点的子节点的深度为 $1$。

帮助 Monocarp 找到任何具有给定访问顺序 $a$ 且高度最小的树。

## 说明/提示
在第一个测试用例中，只有一棵具有给定访问顺序的树：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/410231d5450c97d8a337f65673d6193fef7ef91a.png)
在第二个测试用例中，同样只有一棵具有给定访问顺序的树：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/7a0ba94b1eb3ad4817eb8aa8e139c5ce715f4da2.png)
在第三个测试用例中，具有给定访问顺序的最优树如下所示：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1437D/aa50643bf81bba2c4eca6a0d6c99c8ba0b01c205.png)

## 样例 #1
### 输入
```
3
4
1 4 3 2
2
1 2
3
1 2 3
```
### 输出
```
3
1
1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法，利用 BFS 序中每个节点的子节点按升序排列这一性质，将连续的一段升序序列作为一个节点的子节点，以此来构造最小高度的树。各题解主要通过维护上一层节点个数和当前层节点个数等信息，根据序列中元素的大小关系判断是否需要新开一层，从而计算出树的最小高度。

### 所选题解
- **yu__xuan（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过合理定义变量 `last`（上一层的节点个数）和 `now`（这一层的节点个数），模拟了树的构建过程，能准确计算出最小高度。
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define M 200001

int t, n, a[M];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        if (n == 1) { puts("0"); continue; }
        if (n == 2) { puts("1"); continue; }
        int last = 1, now = 1, ans = 0, k = 1;
        //last 表示上一层的节点个数
        //now 表示这一层的节点个数
        for (int i = 2; i < n; ++i) {
            if (a[i] < a[i + 1]) ++now;//一段连续递增的节点
            else {//不连续递增了 
                if (k == last) ++ans;//新开了一层。
                --last;//占用一个上一层的节点
                if (last == 0) {//上一层的节点都用完了
                    k = last = now, now = 1;
                }
                else ++now;//上一层的节点没用完的话，i + 1 是本层的节点。 
            }
        }
        if (now) {
            if (k == last) ++ans;
            --last;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
- **Tony102（4星）**
    - **关键亮点**：通过模拟 BFS 过程，利用队列存储节点，结合深度数组 `dep` 记录每个节点的深度，最后取最大深度作为树的最小高度，思路直观。
```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int SIZE = 2e5 + 5;
 
int T, n, ans;
int a[SIZE], dep[SIZE];
 
inline int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
	return x * f;
}
 
inline void bfs()
{
    std::queue < int > q;
    memset(dep, 0, sizeof(dep));
    q.push(1);
    int pos = 2;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans = std::max(ans, dep[u]);
        int lst = pos;
        if (pos > n) break;
        while (a[pos + 1] > a[pos] && pos < n) ++ pos;
        for (int i = lst; i <= pos; ++ i) {
            dep[a[i]] = dep[u] + 1;
            q.push(a[i]);
        }
        ++ pos;
    }
}
 
int main()
{
    T = read();
    while (T --) {
        n = read();
        for (int i = 1; i <= n; ++ i) a[i] = read();
        ans = 0;
        bfs();
        for (int i = 1; i <= n; ++ i) ans = std::max(ans, dep[i]);
        printf("%d\n", ans);
    }
    return 0;
}
```
- **chichichichi（4星）**
    - **关键亮点**：对贪心思路的解释详细，通过合理定义变量 `w`（当前层还能容纳的子串个数）、`ans`（树的深度）和 `len`（当前层的结点个数），模拟树的构建过程计算最小高度。
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1123456;
int n,m,t;
int a[maxn];
int main(){
	scanf("%d",&t);
	while(t)
	{
		t--;
		scanf("%d",&n);
		int ans=1,cnt=0,w=0,len=0;
		scanf("%d",&a[1]);
		//w记录当前层还能容纳的子串个数
		//ans记录树的深度
		// len记录当前层的结点个数 
		for(int i=2;i<=n;i++)
		{
			scanf("%d",a+i);
			if(a[i]<a[i-1]&&!w)
			{
				ans++;
				w=len-1;
				len=1;
			}
			else if(a[i]<a[i-1])
			{
				w--;
				len++;
			}
			else{
				len++; 
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

### 最优关键思路或技巧
- 利用贪心思想，将连续的升序序列作为一个节点的子节点，可使树的高度最小。
- 维护上一层节点个数和当前层节点个数等信息，根据序列中元素的大小关系判断是否需要新开一层。

### 拓展思路
同类型题或类似算法套路：
- 给定其他遍历顺序（如 DFS 序），求满足条件的树的最小高度或其他相关性质。
- 对树的结构有其他限制条件（如节点度数限制等），求满足条件的树的最优解。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
- [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
- [P1122 最大子树和](https://www.luogu.com.cn/problem/P1122)

### 个人心得摘录与总结
- **Weekoder**：在实现过程中遇到了很多测试用例不通过的问题，如节点数量统计错误、循环条件错误等，经过不断调试和修正最终 AC。总结为在实现算法时要注意细节，对边界条件和特殊情况要仔细考虑，不能为了偷懒而写错关键逻辑。 

---
处理用时：64.24秒