# 题目信息

# Peculiar apple-tree

## 题目描述

In Arcady's garden there grows a peculiar apple-tree that fruits one time per year. Its peculiarity can be explained in following way: there are $ n $ inflorescences, numbered from $ 1 $ to $ n $ . Inflorescence number $ 1 $ is situated near base of tree and any other inflorescence with number $ i $ ( $ i&gt;1 $ ) is situated at the top of branch, which bottom is $ p_{i} $ -th inflorescence and $ p_{i}&lt;i $ .

Once tree starts fruiting, there appears exactly one apple in each inflorescence. The same moment as apples appear, they start to roll down along branches to the very base of tree. Each second all apples, except ones in first inflorescence simultaneously roll down one branch closer to tree base, e.g. apple in $ a $ -th inflorescence gets to $ p_{a} $ -th inflorescence. Apples that end up in first inflorescence are gathered by Arcady in exactly the same moment. Second peculiarity of this tree is that once two apples are in same inflorescence they annihilate. This happens with each pair of apples, e.g. if there are $ 5 $ apples in same inflorescence in same time, only one will not be annihilated and if there are $ 8 $ apples, all apples will be annihilated. Thus, there can be no more than one apple in each inflorescence in each moment of time.

Help Arcady with counting number of apples he will be able to collect from first inflorescence during one harvest.

## 说明/提示

In first example Arcady will be able to collect only one apple, initially situated in $ 1 $ st inflorescence. In next second apples from $ 2 $ nd and $ 3 $ rd inflorescences will roll down and annihilate, and Arcady won't be able to collect them.

In the second example Arcady will be able to collect 3 apples. First one is one initially situated in first inflorescence. In a second apple from $ 2 $ nd inflorescence will roll down to $ 1 $ st (Arcady will collect it) and apples from $ 3 $ rd, $ 4 $ th, $ 5 $ th inflorescences will roll down to $ 2 $ nd. Two of them will annihilate and one not annihilated will roll down from $ 2 $ -nd inflorescence to $ 1 $ st one in the next second and Arcady will collect it.

## 样例 #1

### 输入

```
3
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
18
1 1 1 4 4 3 2 2 2 10 8 9 9 9 10 10 4
```

### 输出

```
4
```

# AI分析结果



# Peculiar apple-tree

## 题目描述

在 Arcady 的花园里有一棵奇特的苹果树，每年结果一次。它的奇特之处可以这样描述：树上有 $n$ 个花序，编号从 $1$ 到 $n$。编号为 $1$ 的花序位于树的基部，其他编号为 $i$（$i>1$）的花序都位于某个枝条的顶端，该枝条的基部连接着第 $p_i$ 个花序，其中 $p_i < i$。

当苹果树开始结果时，每个花序上都会出现一个苹果。苹果出现的瞬间就会沿着枝条向下滚动到树的基部。每一秒钟，所有不在第一个花序的苹果会同时向基部移动一步（即位于 $a$ 号花序的苹果会移动到 $p_a$ 号花序）。当苹果到达第一个花序时，Arcady 会立即收集它们。第二个奇特之处是：当两个苹果同时出现在同一个花序时，它们会成对湮灭。例如，若有 5 个苹果在同一花序相遇，最终会剩 1 个；若有 8 个则全部消失。因此，任何时刻每个花序最多只能有一个苹果。

请帮助 Arcady 计算一次收获中他能收集到多少个苹果。

## 说明/提示

第一个样例中，Arcady 只能收集到最初在 1 号花序的苹果。第二秒时 2 号、3 号花序的苹果会移动到 1 号并湮灭。

第二个样例中，Arcady 总共能收集 3 个苹果：初始 1 号苹果，第二秒 2 号苹果到达，第三秒来自 3、4、5 号花序的苹果（湮灭后剩 1 个）到达。

## 样例 #1

### 输入
```
3
1 1
```

### 输出
```
1
```

## 样例 #2

### 输入
```
5
1 2 2 2
```

### 输出
```
3
```

---

**算法分类**：树、数学（奇偶性分析）

---

### 题解综合分析

所有题解均基于关键观察：**同一深度的苹果会同时到达根节点**。通过统计每个深度的苹果数量奇偶性即可求解。主要差异在于实现方式（直接遍历父链计算深度 vs DFS）。

#### 关键思路
1. **深度等价时间**：苹果的移动时间等于其所在节点的深度（根节点深度为1）
2. **奇偶性法则**：同一时刻到达根节点的苹果数若为奇数则贡献1，偶数则贡献0
3. **延迟湮灭**：苹果湮灭的效果可以等效延迟到根节点处理

---

### 精选题解（评分≥4⭐）

#### 1. installb（5⭐）
**核心亮点**：  
- 最简洁的线性遍历实现，O(n)时间复杂度  
- 直接通过父节点递推计算深度  
- 代码可读性极强，无冗余操作  

**代码核心**：
```cpp
cin >> n;
cnt[1] = 1; dep[1] = 1; 
for(LL i = 2;i <= n;i ++){
    cin >> f[i];
    dep[i] = dep[f[i]] + 1; // 递推计算深度
    cnt[dep[i]] ++;
}
for(LL i = 1;i <= n;i ++) if(cnt[i] & 1) ans ++;
```

#### 2. Rosemary_dream（4⭐）
**核心亮点**：  
- 图文结合说明延迟湮灭思想  
- 引入树形结构图示辅助理解  

**代码核心**：
```cpp
for(int i=2;i<=n;i++) {
    scanf("%d",&a);
    dep[i] = dep[a] + 1; // 父节点深度+1
    sum[dep[i]]++; 
}
for(int i=1;i<=n;i++) ans += sum[i]%2;
```

#### 3. Noby_Glds（4⭐）
**核心亮点**：  
- 使用位运算优化奇偶性判断  
- 数组初始值处理更简洁  

**代码核心**：
```cpp
for(int i=2;i<=n;i++) {
    cin >> a;
    dep[i] = dep[a]+1;
    sum[dep[i]] ^= 1; // 异或实现奇偶翻转
}
ans = 1; // 根节点初始苹果
for(int i=1;i<=n;i++) ans += sum[i];
```

---

### 关键技巧总结
1. **深度等价时间**：将苹果移动时间转化为树节点深度计算  
2. **奇偶性统计**：用位运算或模2运算快速判断剩余苹果数  
3. **递推代替递归**：通过父节点直接计算深度，避免DFS的栈开销  

---

### 同类题目推荐
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)（树形结构+距离分析）  
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)（树形DP）  
3. [P1087 FBI树](https://www.luogu.com.cn/problem/P1087)（树结构+后序遍历）

---
处理用时：65.80秒