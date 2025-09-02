# 题目信息

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

# AI分析结果

### 题目翻译
## 神秘的礼物

### 题目描述
彼得决定祝他来自澳大利亚的朋友生日快乐，并送给他一张贺卡。为了让他的礼物更神秘，他决定制作一个信封链。这里的信封链是这样一个信封序列 $A$ = { $a_{1},a_{2},...,a_{n}$ }，其中第 $i$ 个信封的宽度和高度分别严格大于第 $(i - 1)$ 个信封的宽度和高度。链的长度就是链中信封的数量。

彼得想从他拥有的信封中制作出最长的链，并且这个链要能装下贺卡。如果贺卡的宽度和高度分别小于链中最小信封的宽度和高度，那么贺卡就能装进这个链。禁止将贺卡和信封旋转。

彼得有很多信封，但时间很少，这项艰巨的任务就交给你了。

### 样例 #1
#### 输入
```
2 1 1
2 2
2 2
```
#### 输出
```
1
1 
```

### 样例 #2
#### 输入
```
3 3 3
5 4
12 11
9 8
```
#### 输出
```
3
1 3 2 
```

### 综合分析与结论
这些题解主要围绕二维最长上升子序列（LIS）问题展开，核心是在满足宽度和高度都严格递增的条件下，找出最长的信封链，并输出链的长度和对应的信封编号。

- **思路对比**：大部分题解采用排序后进行动态规划的方法，先按宽度排序，再在高度上求 LIS；部分题解使用记忆化搜索、拓扑排序等方法。
- **算法要点**：动态规划的状态转移方程通常为 $f_i = \max\{f_j + 1 | j < i, w_j < w_i, h_j < h_i\}$，关键在于排序和状态转移的处理。
- **解决难点**：处理宽度相等但高度递增的情况，避免将不符合严格递增条件的信封计入链中；同时，要正确记录路径以便输出链的编号。

### 所选题解
- **Juanzhang（4星）**
  - **关键亮点**：采用记忆化搜索，避免计算不需要的部分，代码简洁，思路清晰。
  - **个人心得**：无
- **Loner_Knowledge（4星）**
  - **关键亮点**：详细阐述了动态规划的思路，状态转移方程明确，对输出路径的处理清晰。
  - **个人心得**：无
- **Plozia（4星）**
  - **关键亮点**：对状态转移方程的推导和修正过程详细，考虑到了排序和严格递增的细节。
  - **个人心得**：指出直接按照一维 LIS 思路写会出错，原因是物品顺序可调换，且要注意严格递增的条件，避免将宽度相等的情况计入。

### 重点代码
#### Juanzhang 的记忆化搜索代码
```cpp
int dfs(int x) {
    if (~dp[x]) {
        return dp[x];
    }
    dp[x] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].fir.fir > a[x].fir.fir && a[i].fir.sec > a[x].fir.sec && dp[x] < dfs(i)) {
            dp[x] = dp[i], pre[x] = i;
        }
    }
    return ++dp[x];
}
```
**核心思想**：通过递归调用 `dfs` 函数，利用记忆化数组 `dp` 避免重复计算，更新当前状态的最长链长度，并记录前驱节点。

#### Loner_Knowledge 的动态规划代码
```cpp
for(int i=1;i<head;++i) {
    for(int j=0;j<i;++j) {
        if(D[j].w<D[i].w&&D[j].h<D[i].h&&f[j]+1>f[i]) {
            f[i]=f[j]+1;
            from[i]=j;
        }
    }
    if(ans<f[i]) {
        ans=f[i];
        p=i;
    }
}
```
**核心思想**：双重循环遍历所有元素，根据状态转移方程更新 `f` 数组，记录最长链长度和前驱节点。

#### Plozia 的动态规划代码
```cpp
for (int i = 1; i <= cnt; ++i) {
    f[i] = 1;
    for(int j = 1; j < i; ++j) {
        if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
            f[i] = f[j] + 1;
            las[i] = j;
        }
    }
}
```
**核心思想**：同样是双重循环，根据修正后的状态转移方程更新 `f` 数组，记录最长链长度和前驱节点。

### 最优关键思路或技巧
- 先对信封按宽度排序，将二维问题转化为一维的 LIS 问题，简化问题复杂度。
- 在状态转移时，注意严格递增的条件，避免将宽度相等的情况计入。
- 使用记忆化搜索或动态规划记录路径，方便输出最长链的编号。

### 可拓展之处
同类型题如三维偏序问题，可先按第一维排序，再按第二维排序，最后在第三维上进行 LIS 求解。类似算法套路可应用于多维偏序问题，关键在于对每一维的排序和状态转移的处理。

### 推荐洛谷题目
- P1020 [NOIP1999 普及组] 导弹拦截：一维 LIS 问题，可作为基础练习。
- P1439 【模板】最长公共子序列：与 LIS 有一定关联，可加深对动态规划的理解。
- P2782 友好城市：二维偏序问题，与本题思路相似。

---
处理用时：41.10秒