# 题目信息

# Hanging Hearts

## 题目描述

Pak Chanek has $ n $ blank heart-shaped cards. Card $ 1 $ is attached directly to the wall while each of the other cards is hanging onto exactly one other card by a piece of string. Specifically, card $ i $ ( $ i > 1 $ ) is hanging onto card $ p_i $ ( $ p_i < i $ ).

In the very beginning, Pak Chanek must write one integer number on each card. He does this by choosing any permutation $ a $ of $ [1, 2, \dots, n] $ . Then, the number written on card $ i $ is $ a_i $ .

After that, Pak Chanek must do the following operation $ n $ times while maintaining a sequence $ s $ (which is initially empty):

1. Choose a card $ x $ such that no other cards are hanging onto it.
2. Append the number written on card $ x $ to the end of $ s $ .
3. If $ x \neq 1 $ and the number on card $ p_x $ is larger than the number on card $ x $ , replace the number on card $ p_x $ with the number on card $ x $ .
4. Remove card $ x $ .

After that, Pak Chanek will have a sequence $ s $ with $ n $ elements. What is the maximum length of the longest non-decreasing subsequence $ ^\dagger $ of $ s $ at the end if Pak Chanek does all the steps optimally?

 $ ^\dagger $ A sequence $ b $ is a subsequence of a sequence $ c $ if $ b $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements. For example, $ [3,1] $ is a subsequence of $ [3,2,1] $ , $ [4,3,1] $ and $ [3,1] $ , but not $ [1,3,3,7] $ and $ [3,10,4] $ .

## 说明/提示

The following is the structure of the cards in the first example.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1740E/c21952ecb25b67a195586146f9d068b9b7641f10.png)

Pak Chanek can choose the permutation $ a = [1, 5, 4, 3, 2, 6] $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1740E/4127ff7f189221d666c08b1ef78406f618501ae1.png)

Let $ w_i $ be the number written on card $ i $ . Initially, $ w_i = a_i $ . Pak Chanek can do the following operations in order:

1. Select card $ 5 $ . Append $ w_5 = 2 $ to the end of $ s $ . As $ w_4 > w_5 $ , the value of $ w_4 $ becomes $ 2 $ . Remove card $ 5 $ . After this operation, $ s = [2] $ .
2. Select card $ 6 $ . Append $ w_6 = 6 $ to the end of $ s $ . As $ w_2 \leq w_6 $ , the value of $ w_2 $ is left unchanged. Remove card $ 6 $ . After this operation, $ s = [2, 6] $ .
3. Select card $ 4 $ . Append $ w_4 = 2 $ to the end of $ s $ . As $ w_1 \leq w_4 $ , the value of $ w_1 $ is left unchanged. Remove card $ 4 $ . After this operation, $ s = [2, 6, 2] $ .
4. Select card $ 3 $ . Append $ w_3 = 4 $ to the end of $ s $ . As $ w_2 > w_3 $ , the value of $ w_2 $ becomes $ 4 $ . Remove card $ 3 $ . After this operation, $ s = [2, 6, 2, 4] $ .
5. Select card $ 2 $ . Append $ w_2 = 4 $ to the end of $ s $ . As $ w_1 \leq w_2 $ , the value of $ w_1 $ is left unchanged. Remove card $ 2 $ . After this operation, $ s = [2, 6, 2, 4, 4] $ .
6. Select card $ 1 $ . Append $ w_1 = 1 $ to the end of $ s $ . Remove card $ 1 $ . After this operation, $ s = [2, 6, 2, 4, 4, 1] $ .

One of the longest non-decreasing subsequences of $ s = [2, 6, 2, 4, 4, 1] $ is $ [2, 2, 4, 4] $ . Thus, the length of the longest non-decreasing subsequence of $ s $ is $ 4 $ . It can be proven that this is indeed the maximum possible length.

## 样例 #1

### 输入

```
6
1 2 1 4 2```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1```

### 输出

```
2```

# AI分析结果

### 题目翻译
# 悬挂的心形卡片

## 题目描述
Pak Chanek 有 $n$ 张空白的心形卡片。卡片 1 直接贴在墙上，而其他每张卡片都通过一根绳子挂在另一张卡片上。具体来说，卡片 $i$（$i > 1$）挂在卡片 $p_i$（$p_i < i$）上。

一开始，Pak Chanek 必须在每张卡片上写一个整数。他通过选择 $[1, 2, \dots, n]$ 的任意一个排列 $a$ 来完成这个操作。然后，写在卡片 $i$ 上的数字就是 $a_i$。

之后，Pak Chanek 必须进行 $n$ 次以下操作，同时维护一个序列 $s$（初始为空）：
1. 选择一张没有其他卡片挂在上面的卡片 $x$。
2. 将写在卡片 $x$ 上的数字添加到 $s$ 的末尾。
3. 如果 $x \neq 1$ 且卡片 $p_x$ 上的数字大于卡片 $x$ 上的数字，则将卡片 $p_x$ 上的数字替换为卡片 $x$ 上的数字。
4. 移除卡片 $x$。

之后，Pak Chanek 将得到一个包含 $n$ 个元素的序列 $s$。如果 Pak Chanek 最优地完成所有步骤，那么 $s$ 的最长非递减子序列的最大长度是多少？

注：如果序列 $b$ 可以通过删除序列 $c$ 中的若干（可能为零个或全部）元素得到，那么序列 $b$ 就是序列 $c$ 的子序列。例如，$[3,1]$ 是 $[3,2,1]$、$[4,3,1]$ 和 $[3,1]$ 的子序列，但不是 $[1,3,3,7]$ 和 $[3,10,4]$ 的子序列。

## 说明/提示
以下是第一个样例中卡片的结构。
（此处有图片链接）

Pak Chanek 可以选择排列 $a = [1, 5, 4, 3, 2, 6]$。
（此处有图片链接）

设 $w_i$ 是写在卡片 $i$ 上的数字。一开始，$w_i = a_i$。Pak Chanek 可以按以下顺序进行操作：
1. 选择卡片 5。将 $w_5 = 2$ 添加到 $s$ 的末尾。由于 $w_4 > w_5$，$w_4$ 的值变为 2。移除卡片 5。操作后，$s = [2]$。
2. 选择卡片 6。将 $w_6 = 6$ 添加到 $s$ 的末尾。由于 $w_2 \leq w_6$，$w_2$ 的值保持不变。移除卡片 6。操作后，$s = [2, 6]$。
3. 选择卡片 4。将 $w_4 = 2$ 添加到 $s$ 的末尾。由于 $w_1 \leq w_4$，$w_1$ 的值保持不变。移除卡片 4。操作后，$s = [2, 6, 2]$。
4. 选择卡片 3。将 $w_3 = 4$ 添加到 $s$ 的末尾。由于 $w_2 > w_3$，$w_2$ 的值变为 4。移除卡片 3。操作后，$s = [2, 6, 2, 4]$。
5. 选择卡片 2。将 $w_2 = 4$ 添加到 $s$ 的末尾。由于 $w_1 \leq w_2$，$w_1$ 的值保持不变。移除卡片 2。操作后，$s = [2, 6, 2, 4, 4]$。
6. 选择卡片 1。将 $w_1 = 1$ 添加到 $s$ 的末尾。移除卡片 1。操作后，$s = [2, 6, 2, 4, 4, 1]$。

$s = [2, 6, 2, 4, 4, 1]$ 的一个最长非递减子序列是 $[2, 2, 4, 4]$。因此，$s$ 的最长非递减子序列的长度是 4。可以证明这确实是最大可能的长度。

## 样例 #1
### 输入
```
6
1 2 1 4 2
```
### 输出
```
4
```

## 样例 #2
### 输入
```
2
1
```
### 输出
```
2
```

### 算法分类
动态规划

### 综合分析与结论
这些题解都围绕树形动态规划来解决问题，核心在于分析以每个节点为根的子树对最长非递减子序列长度的贡献。不同题解的思路和状态定义有所差异，但最终都是通过对节点及其子节点的状态转移来求解。
- **思路对比**：
    - lenlen 的题解从子树的最长链和儿子节点的贡献出发，直接得出递推式。
    - Gao_yc 的题解先给出错误做法，再通过分析得到正确的状态定义和转移方程。
    - Daidly 的题解根据子树中最小值的位置来定义状态并转移。
    - RuntimeErr 的题解从子序列是否以当前节点结尾来分析。
    - 5ab_juruo 的题解利用树的 bfs 序进行非递归的树形 dp。
- **算法要点**：
    - 均采用树形动态规划，通过深度优先搜索遍历树。
    - 状态定义和转移方程是关键，不同题解的状态定义有所不同，但都围绕子树的贡献展开。
- **解决难点**：
    - 处理节点和子节点之间的权值更新关系。
    - 确定如何安排点权以得到最长非递减子序列。
    - 处理多个子节点对父节点的影响。

### 所选题解
- **lenlen（5星）**：
    - **关键亮点**：思路清晰，直接从子树的最长链和儿子节点的贡献分析，递推式简洁明了，代码实现简单易懂。
- **Gao_yc（4星）**：
    - **关键亮点**：先给出错误做法并分析，再得到正确的状态定义和转移方程，有助于理解问题的本质。
    - **个人心得**：作者提到这是自己第一道赛时做出的 Div2 E 题，分享了赛时的错误做法和思考过程，有一定的借鉴意义。
- **RuntimeErr（4星）**：
    - **关键亮点**：从子序列是否以当前节点结尾的角度分析，思路独特，代码简洁。

### 重点代码
#### lenlen 的题解
```cpp
void dfs(int x)
{
    for(int i=h[x];i;i=e[i].nxt)
    {
        dfs(e[i].v);
        f[x]=max(f[x],f[e[i].v]+1); // f求链长
        dp[x]+=dp[e[i].v]; // dp先求儿子节点长度的最大值
    }
    if(!f[x]) f[x]=1; // 叶子节点自身大小为1
    dp[x]=max(dp[x],f[x]);
}
```
**核心实现思想**：通过深度优先搜索遍历树，计算以每个节点为根的子树的最长链长度 `f[x]` 和儿子节点的贡献之和 `dp[x]`，最后取两者的最大值。

#### Gao_yc 的题解
```cpp
void dfs(int x){
    f[x][1]=1;
    for(int i=head[x],y;i;i=nxt[i]){
        y=ver[i];
        dfs(y);
        f[x][1]=max(f[x][1],f[y][1]+1);
        f[x][0]+=max(f[y][1],f[y][0]);
    }
}
```
**核心实现思想**：状态 `f[x][1]` 表示点 `x` 被选的最大答案，`f[x][0]` 表示点 `x` 不被选的最大答案。通过深度优先搜索遍历树，根据状态转移方程更新状态。

#### RuntimeErr 的题解
```cpp
void dfs(int u){
    f[u]=0,maxdep[u]=1;
    for(int v:e[u]){ 
        dfs(v);
        maxdep[u]=max(maxdep[u],maxdep[v]+1);
        f[u]+=f[v];
    }
    f[u]=max(maxdep[u],f[u]);
}
```
**核心实现思想**：`maxdep[u]` 表示以 `u` 为根的子树的最大深度，`f[u]` 表示以 `u` 为根的子树构造出的答案。通过深度优先搜索遍历树，更新最大深度和子树的答案，最后取两者的最大值。

### 最优关键思路或技巧
- **树形动态规划**：将问题转化为树形结构上的动态规划问题，通过分析子树的贡献来求解。
- **状态定义**：合理定义状态，如以节点是否被选、子树中最小值的位置等，来表示子树的信息。
- **状态转移**：根据节点和子节点之间的关系，确定状态转移方程。

### 拓展思路
同类型题或类似算法套路：
- 其他树形动态规划问题，如树的最大独立集、树的最小支配集等。
- 涉及子树信息维护和状态转移的问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)

### 个人心得摘录与总结
- **Gao_yc**：作者分享了赛时的错误做法，即猜测答案为儿子数不大于 1 的点数，结果 WA on #6。通过分析错误原因，得到了正确的状态定义和转移方程。这提醒我们在解题时不能盲目猜测结论，要通过严谨的分析和推理来得到正确的解法。

---
处理用时：65.66秒