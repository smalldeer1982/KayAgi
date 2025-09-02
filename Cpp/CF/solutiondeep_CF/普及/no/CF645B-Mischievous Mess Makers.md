# 题目信息

# Mischievous Mess Makers

## 题目描述

It is a balmy spring afternoon, and Farmer John's $ n $ cows are ruminating about link-cut cacti in their stalls. The cows, labeled $ 1 $ through $ n $ , are arranged so that the $ i $ -th cow occupies the $ i $ -th stall from the left. However, Elsie, after realizing that she will forever live in the shadows beyond Bessie's limelight, has formed the Mischievous Mess Makers and is plotting to disrupt this beautiful pastoral rhythm. While Farmer John takes his $ k $ minute long nap, Elsie and the Mess Makers plan to repeatedly choose two distinct stalls and swap the cows occupying those stalls, making no more than one swap each minute.

Being the meticulous pranksters that they are, the Mischievous Mess Makers would like to know the maximum messiness attainable in the $ k $ minutes that they have. We denote as $ p_{i} $ the label of the cow in the $ i $ -th stall. The messiness of an arrangement of cows is defined as the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

## 说明/提示

In the first sample, the Mischievous Mess Makers can swap the cows in the stalls $ 1 $ and $ 5 $ during the first minute, then the cows in stalls $ 2 $ and $ 4 $ during the second minute. This reverses the arrangement of cows, giving us a total messiness of $ 10 $ .

In the second sample, there is only one cow, so the maximum possible messiness is $ 0 $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
1 10
```

### 输出

```
0
```

# AI分析结果



# 中文翻译

## 题目名称：恶作剧制造者

### 题目描述  
在一个温暖的春日午后，农夫约翰的 $n$ 头奶牛正在牛棚里反刍。这些奶牛被编号为 $1$ 到 $n$，其中第 $i$ 头奶牛位于从左数第 $i$ 个牛棚。然而，艾尔西（Elsie）意识到自己将永远活在贝西（Bessie）的光环之外后，成立了“恶作剧制造者”组织，计划在农夫约翰小睡的 $k$ 分钟内反复交换两头奶牛的位置（每分钟最多交换一次），以制造最大的混乱。混乱度定义为排列中逆序对的数量，即满足 $i<j$ 且 $p_i > p_j$ 的 $(i,j)$ 对数。

### 输入格式  
输入两个整数 $n$ 和 $k$，分别表示奶牛数量和可交换次数。

### 输出格式  
输出最大可能的逆序对数。

### 样例  
#### 输入  
```
5 2
```
#### 输出  
```
10
```
#### 样例解释  
交换位置 1 和 5，再交换位置 2 和 4，最终排列为 [5,4,3,2,1]，逆序对数为 10。

---

**算法分类**：贪心

---

## 题解分析与结论

### 核心思路  
所有最优解法均基于贪心策略：每次交换尽可能使两端元素互换。具体操作是，第 $i$ 次交换将位置 $i$ 和 $n-i+1$ 的元素交换。每次交换后，新增的逆序对数为 $2(n-2i)+1$。最多执行 $\min(k, \lfloor n/2 \rfloor)$ 次有效交换，超过后无法增加逆序对。

### 最优题解（评分≥4星）

1. **AstaSunch_ 的题解（4星）**  
   **亮点**：代码简洁，直接计算每次交换的贡献，公式清晰。  
   **代码核心**：
   ```cpp
   for(int i=1; i*2<=n && i<k; i++)
       sum += 2*(n-2*i)+1;
   ```
   **思路**：每次交换两端元素，总贡献为等差数列求和。

2. **saixingzhe 的题解（4星）**  
   **亮点**：明确循环终止条件，避免多余交换。  
   **代码核心**：
   ```cpp
   for(int i=1; i*2<=n; i++) {
       if(i > k) break;
       ans += 2*(n-2*i)+1;
   }
   ```

3. **MurataHimeko 的题解（4星）**  
   **亮点**：详细推导交换贡献的计算过程。  
   **关键步骤**：
   ```cpp
   ans += (n-2i) + (n-2i+1); // 等价于 2*(n-2i)+1
   ```

---

### 关键技巧总结  
- **贪心选择**：每次交换两端元素以最大化单次贡献。  
- **数学推导**：推导出每次交换新增的逆序对数公式 $2(n-2i)+1$。  
- **边界处理**：交换次数不超过 $\lfloor n/2 \rfloor$，避免无效或反向操作。

---

### 拓展与相似题目  
1. **P1969 积木大赛**（贪心策略）  
2. **P1223 排队接水**（贪心排序）  
3. **P1908 逆序对**（归并排序/树状数组）  

---

### 个人心得摘录  
- **AstaSunch_**：超过 $\lfloor n/2 \rfloor$ 次交换会导致更小数前移，逆序对减少。  
- **MurataHimeko**：需注意交换操作的对称性，确保每次交换有效贡献最大。

---
处理用时：148.19秒