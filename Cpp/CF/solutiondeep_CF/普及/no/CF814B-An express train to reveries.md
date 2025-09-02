# 题目信息

# An express train to reveries

## 题目描述

Sengoku still remembers the mysterious "colourful meteoroids" she discovered with Lala-chan when they were little. In particular, one of the nights impressed her deeply, giving her the illusion that all her fancies would be realized.

On that night, Sengoku constructed a permutation $ p_{1},p_{2},...,p_{n} $ of integers from $ 1 $ to $ n $ inclusive, with each integer representing a colour, wishing for the colours to see in the coming meteor outburst. Two incredible outbursts then arrived, each with $ n $ meteorids, colours of which being integer sequences $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ respectively. Meteoroids' colours were also between $ 1 $ and $ n $ inclusive, and the two sequences were not identical, that is, at least one $ i $ ( $ 1<=i<=n $ ) exists, such that $ a_{i}≠b_{i} $ holds.

Well, she almost had it all — each of the sequences $ a $ and $ b $ matched exactly $ n-1 $ elements in Sengoku's permutation. In other words, there is exactly one $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}≠p_{i} $ , and exactly one $ j $ ( $ 1<=j<=n $ ) such that $ b_{j}≠p_{j} $ .

For now, Sengoku is able to recover the actual colour sequences $ a $ and $ b $ through astronomical records, but her wishes have been long forgotten. You are to reconstruct any possible permutation Sengoku could have had on that night.

## 说明/提示

In the first sample, both $ 1,2,5,4,3 $ and $ 1,2,3,4,5 $ are acceptable outputs.

In the second sample, $ 5,4,2,3,1 $ is the only permutation to satisfy the constraints.

## 样例 #1

### 输入

```
5
1 2 3 4 3
1 2 5 4 5
```

### 输出

```
1 2 5 4 3
```

## 样例 #2

### 输入

```
5
4 4 2 3 1
5 4 5 3 1
```

### 输出

```
5 4 2 3 1
```

## 样例 #3

### 输入

```
4
1 1 3 4
1 4 3 4
```

### 输出

```
1 2 3 4
```

# AI分析结果



# An express train to reveries

## 题目描述

Sengoku 曾与 Lala-chan 在童年时共同发现神秘的"彩色流星群"。某个特别的夜晚，她构造了一个排列 $ p_{1},p_{2},...,p_{n} $，每个元素代表一种颜色，寄托了对流星爆发的期待。随后出现了两次壮观的爆发，分别对应颜色序列 $ a $ 和 $ b $，满足每个序列与排列 $ p $ 恰好有一个位置不同，且 $ a $ 与 $ b $ 不完全相同。

现需根据已知的 $ a $ 和 $ b $ 重构可能的排列 $ p $。

## 说明/提示

第一个样例中，排列可以是 `1,2,5,4,3` 或 `1,2,3,4,5`。第二个样例唯一解为 `5,4,2,3,1`。

---

**算法分类**：构造

---

## 题解综合分析

### 核心思路
所有题解均采用分类讨论思想：
1. **单差异位点**：直接填入缺失的数字
2. **双差异位点**：尝试两种交叉组合（a的位点1+b的位点2 或 b的位点1+a的位点2），通过哈希表验证合法性

### 最优思路提炼
- **差异位点定位**：记录a与b不同的位置索引
- **公共位直接继承**：相同位置元素必为排列值
- **双差异位处理**：将两个差异位视为组合对，检查两种可能的组合方式是否满足排列不重复性

---

## 高星题解推荐

### 题解作者：wz441135118（4星）
**亮点**：
1. 代码极简，仅用两个变量记录差异位
2. 通过vis数组快速验证候选值合法性
3. 双差异位处理逻辑清晰（仅需两次条件判断）

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
if(i!=x&&i!=y)c[i]=a[i],vis[a[i]]=1;

if(!y) // 单差异位情况
    for(int i=1;i<=n;i++)if(!vis[i])c[x]=i;
else{ // 双差异位情况
    if(!vis[a[x]]&&!vis[b[y]])c[x]=a[x],c[y]=b[y];
    else c[x]=b[x],c[y]=a[y];
}
```

### 题解作者：da32s1da（4星）
**亮点**：
1. 使用opt变量区分单/双差异位
2. 通过预处理公共位快速构造基础排列
3. 差异位处理采用贪心策略

**个人心得**：
"当有两个数不一样时，只需考虑对角线组合的可能性" —— 通过数学归纳简化了组合验证过程

---

## 相似题目推荐
1. [P2894 外星千足虫](https://www.luogu.com.cn/problem/P2894)  
   **考察点**：约束条件下的排列构造
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)  
   **考察点**：排列生成与约束验证
3. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)  
   **考察点**：基本排列生成算法的应用

---
处理用时：70.12秒