# 题目信息

# Permutation Sum

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

Petya decided to introduce the sum operation on the set of permutations of length $ n $ . Let's assume that we are given two permutations of length $ n $ : $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ . Petya calls the sum of permutations $ a $ and $ b $ such permutation $ c $ of length $ n $ , where $ c_{i}=((a_{i}-1+b_{i}-1)\ mod\ n)+1 $ $ (1<=i<=n) $ .

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Obviously, not for all permutations $ a $ and $ b $ exists permutation $ c $ that is sum of $ a $ and $ b $ . That's why Petya got sad and asked you to do the following: given $ n $ , count the number of such pairs of permutations $ a $ and $ b $ of length $ n $ , that exists permutation $ c $ that is sum of $ a $ and $ b $ . The pair of permutations $ x,y $ $ (x≠y) $ and the pair of permutations $ y,x $ are considered distinct pairs.

As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3
```

### 输出

```
18
```

## 样例 #2

### 输入

```
5
```

### 输出

```
1800
```

# AI分析结果

### 题目内容
# 排列之和

## 题目描述
排列 $p$ 是一个有序的整数集合 $p_{1},p_{2},\cdots,p_{n}$，由 $n$ 个不同的正整数组成，每个整数都不超过 $n$。我们将排列 $p$ 的第 $i$ 个元素记为 $p_{i}$。我们称数字 $n$ 为排列 $p_{1},p_{2},\cdots,p_{n}$ 的大小或长度。

Petya 决定在长度为 $n$ 的排列集合上引入求和运算。假设我们给定两个长度为 $n$ 的排列：$a_{1},a_{2},\cdots,a_{n}$ 和 $b_{1},b_{2},\cdots,b_{n}$。Petya 称排列 $a$ 和 $b$ 的和为这样一个长度为 $n$ 的排列 $c$，其中 $c_{i}=((a_{i}-1 + b_{i}-1)\bmod n)+1$  $(1\leq i\leq n)$。

运算 $\bmod$ 表示取 $x$ 除以 $y$ 的余数。

显然，并非对于所有的排列 $a$ 和 $b$ 都存在排列 $c$ 作为它们的和。这就是为什么 Petya 很伤心，并请你做以下事情：给定 $n$，计算长度为 $n$ 的排列对 $a$ 和 $b$ 的数量，使得存在排列 $c$ 作为 $a$ 和 $b$ 的和。排列对 $x,y$ （$x\neq y$）和排列对 $y,x$ 被视为不同的对。

由于答案可能相当大，请输出它除以 $1000000007$（$10^{9}+7$）的余数。

## 样例 #1
### 输入
```
3
```
### 输出
```
18
```
## 样例 #2
### 输入
```
5
```
### 输出
```
1800
```

### 算法分类
组合数学

### 题解综合分析与结论
这些题解主要围绕排列组合计数问题展开。由于 $n$ 范围较小（$n\leq 16$），大多采用打表方式解题。部分题解利用了 $n$ 为偶数时答案为 $0$ 这一性质减少计算量。不同题解在搜索方式和优化手段上有所差异，有的直接暴力 DFS，有的采用 Meet - in - the - middle 优化搜索。

### 所选的题解
- **作者：huayucaiji（5星）**
  - **关键亮点**：思路清晰，先找出 $C=(1,2,\cdots,n)$ 的方案数再乘以 $n!$ 得到总方案数，利用合理剪枝优化爆搜，还提到可使用 Meet - in - the - middle 进一步优化，虽未详细阐述但点明方向。
  - **个人心得**：无
  - **核心代码片段**：
```cpp
void dfs(int n,int x) {
    if(x==n+1) {
        ans[n]++;
        return ;
    }
    for(int i=1;i<=n;i++) {
        if(!vis[i][0]) {
            int j=(x-1-i+2+n)%n;
            if(!j) {
                j=n;
            }
            if(!vis[j][1]) {
                vis[i][0]=1;
                vis[j][1]=1;
                dfs(n,x+1);
                vis[i][0]=0;
                vis[j][1]=0;
            }
        }
    }
}
```
  - **核心实现思想**：通过深度优先搜索，利用 `vis` 数组记录已使用的数，尝试不同的排列组合，当完成一种合法排列时，方案数 `ans[n]` 增加。
- **作者：ncwzdlsd（4星）**
  - **关键亮点**：先固定排列 $a$ 中的元素从 $0\sim n - 1$，然后通过 DFS 求得排列 $b$，并给出详细打表过程及代码，最后给出利用打表结果的最终代码，步骤清晰。
  - **个人心得**：无
  - **核心代码片段（DFS部分）**：
```cpp
void dfs(int now, int num) 
{
    if(now == num) count++;
    for(int i=0;i<num;i++) 
    {
        if(b[i]) // b[i]已经使用过
            continue;
        int c=(a[now]+i)%num+1;
        if(flag[c])// c不构成全排列，忽略
            continue;
        flag[c]=1;
        b[i]=1;
        dfs(now+1,num);
        flag[c]=0;
        b[i]=0;
    }
}
```
  - **核心实现思想**：以当前位置 `now` 和排列长度 `num` 为参数进行 DFS，遍历未使用过的 `b[i]`，计算对应的 `c`，若 `c` 满足全排列条件则继续递归搜索，若完成一种合法排列则 `count` 增加。
- **作者：panyanppyy（4星）**
  - **关键亮点**：利用 meet - in - the - middle 优化算法，复杂度相对较低，通过开二维数组记录贡献，两次 DFS 统计补集贡献，同时利用 $n$ 为偶数时答案为 $0$ 的性质优化。
  - **个人心得**：无
  - **核心代码片段（第一次 DFS）**：
```cpp
inline void dfs1(int i,int b,int c){
    if(i==n/2)return f[id(b)][id(c)]++,void();
    for(int j=0;j<n;j++)
        if(~b>>j&1&&~c>>((i+j)%n)&1)
            dfs1(i+1,b^1<<j,c^1<<((i+j)%n));
}
```
  - **核心实现思想**：从 `i = 0` 开始，通过位运算判断当前位置是否可用，若可用则更新 `b` 和 `c` 的状态并递归进入下一层，当完成前半部分排列时，记录 `b` 和 `c` 状态对应的贡献。

### 最优关键思路或技巧
1. **利用数学性质优化**：发现 $n$ 为偶数时答案为 $0$，减少一半计算量。
2. **Meet - in - the - middle 优化搜索**：将序列分成两半进行搜索，降低时间复杂度，如 `panyanppyy` 和 `_edge_` 的题解。

### 同类型题或类似算法套路拓展
此类题目通常围绕排列组合计数，关键在于发现问题中的数学性质以简化问题，利用搜索算法（如 DFS）结合剪枝技巧或优化手段（如 Meet - in - the - middle）解决。对于小数据范围问题，打表也是一种有效的策略。

### 洛谷相似题目推荐
1. **P1850 [NOIP2016 提高组] 换教室**：涉及概率与期望，结合动态规划求解排列组合问题。
2. **P3197 [HNOI2008] 越狱**：通过分析对立事件，利用简单的排列组合知识求解。
3. **P4389 付公主的背包**：运用生成函数与组合数学知识解决背包计数问题。 

---
处理用时：61.88秒