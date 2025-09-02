# 题目信息

# Lucky Numbers (easy)

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

Lucky number is super lucky if it's decimal representation contains equal amount of digits $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 7744 $ , $ 474477 $ are super lucky and $ 4 $ , $ 744 $ , $ 467 $ are not.

One day Petya came across a positive integer $ n $ . Help him to find the least super lucky number which is not less than $ n $ .

## 样例 #1

### 输入

```
4500
```

### 输出

```
4747
```

## 样例 #2

### 输入

```
47
```

### 输出

```
47
```

# AI分析结果



### 题目重写
**幸运数字（简单版）**

#### 题目描述  
Petya 喜欢幸运数字。一个正整数被认为是幸运数，当且仅当它的十进制表示仅由数字 $4$ 和 $7$ 组成。例如，$47$、$744$、$4$ 是幸运数，而 $5$、$17$、$467$ 则不是。

超级幸运数则要求其十进制表示中 $4$ 和 $7$ 的数量相等。例如，$47$、$7744$、$474477$ 是超级幸运数，而 $4$、$744$、$467$ 则不是。

给定一个正整数 $n$，请帮助 Petya 找到不小于 $n$ 的最小超级幸运数。

#### 样例  
**输入 1**  
```
4500  
```
**输出 1**  
```
4747  
```
**输入 2**  
```
47  
```
**输出 2**  
```
47  
```

---

### 题解分析与结论  
#### 关键思路总结  
1. **BFS 逐层生成**：通过广度优先搜索，按数字长度逐层生成候选数（每次在末尾添加 4 或 7），保证首次找到的合法解即为最小解。  
2. **结构体优化计数**：在 BFS 过程中跟踪当前数的 4 和 7 的计数差，避免每次检查时重新计算数位。  
3. **打表法**：预先生成所有可能的超级幸运数并排序，直接遍历表查找答案，牺牲空间换时间。  

#### 高分题解推荐  
1. **Vader10 的打表法（★★★★☆）**  
   - **亮点**：通过预处理生成所有超级幸运数，查询时直接遍历表，时间复杂度极低（$O(1)$）。  
   - **适用场景**：问题规模有限，超级幸运数总数可控（如本题最大数仅需 10 位，总候选数约 350 个）。  
   - **代码核心**：  
     ```cpp
     long long ln[350] = {47,74,4477,...}; // 预生成的超级幸运数表
     int main() {
         int n; cin >> n;
         for (int i=0; i<350; i++) {
             if (ln[i] >= n) { cout << ln[i]; return 0; }
         }
     }
     ```

2. **StarryWander 的 BFS 优化版（★★★★☆）**  
   - **亮点**：使用结构体跟踪 4 和 7 的数量差，减少重复计算，提升检查效率。  
   - **关键代码**：  
     ```cpp
     struct node { ll x, stp; }; // stp 记录 4 与 7 的数量差
     queue<node> q;
     q.push({0,0});
     while (!q.empty()) {
         node k = q.front();
         if (k.x >= n && k.stp == 0) { // 直接通过 stp 判断合法性
             cout << k.x; return 0;
         }
         q.push({k.x*10+4, k.stp+1});
         q.push({k.x*10+7, k.stp-1});
     }
     ```

3. **hensier 的基础 BFS（★★★☆☆）**  
   - **亮点**：代码简洁，逐层生成候选数，逻辑清晰。  
   - **核心代码**：  
     ```cpp
     long long q[maxn]; // 队列存储候选数
     while (front <= rear) {
         q[++rear] = q[front]*10+4; // 先扩展 4 保证最小顺序
         check(q[rear]); // 检查是否合法
         q[++rear] = q[front]*10+7;
         check(q[rear]);
         front++;
     }
     ```

---

### 拓展与练习  
#### 类似题目推荐  
1. **P1135 奇怪的电梯**（BFS 求最短路径）  
2. **P1036 选数**（DFS 生成组合数）  
3. **P1706 全排列问题**（next_permutation 的应用）  

#### 关键技巧  
- **BFS 的层序特性**：适用于需要找到最小解的场合，如最短路径、最小操作次数等。  
- **预处理打表**：当候选集有限时，可牺牲空间换时间，显著提升查询效率。  
- **剪枝优化**：通过结构体记录中间状态（如计数差），避免重复计算。  

#### 个人心得摘录  
> "宽搜是逐层搜索，每次增加 4 或 7 作为扩展，保证先找到的合法解一定是最小的。" —— hensier  
> "打表法在竞赛中能快速通过，但需注意不要硬编码过大的表。" —— Vader10

---
处理用时：76.62秒