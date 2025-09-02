# 题目信息

# Tanya and Candies

## 题目描述

Tanya has $ n $ candies numbered from $ 1 $ to $ n $ . The $ i $ -th candy has the weight $ a_i $ .

She plans to eat exactly $ n-1 $ candies and give the remaining candy to her dad. Tanya eats candies in order of increasing their numbers, exactly one candy per day.

Your task is to find the number of such candies $ i $ (let's call these candies good) that if dad gets the $ i $ -th candy then the sum of weights of candies Tanya eats in even days will be equal to the sum of weights of candies Tanya eats in odd days. Note that at first, she will give the candy, after it she will eat the remaining candies one by one.

For example, $ n=4 $ and weights are $ [1, 4, 3, 3] $ . Consider all possible cases to give a candy to dad:

- Tanya gives the $ 1 $ -st candy to dad ( $ a_1=1 $ ), the remaining candies are $ [4, 3, 3] $ . She will eat $ a_2=4 $ in the first day, $ a_3=3 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 4+3=7 $ and in even days she will eat $ 3 $ . Since $ 7 \ne 3 $ this case shouldn't be counted to the answer (this candy isn't good).
- Tanya gives the $ 2 $ -nd candy to dad ( $ a_2=4 $ ), the remaining candies are $ [1, 3, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_3=3 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 3 $ . Since $ 4 \ne 3 $ this case shouldn't be counted to the answer (this candy isn't good).
- Tanya gives the $ 3 $ -rd candy to dad ( $ a_3=3 $ ), the remaining candies are $ [1, 4, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_2=4 $ in the second day, $ a_4=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 4 $ . Since $ 4 = 4 $ this case should be counted to the answer (this candy is good).
- Tanya gives the $ 4 $ -th candy to dad ( $ a_4=3 $ ), the remaining candies are $ [1, 4, 3] $ . She will eat $ a_1=1 $ in the first day, $ a_2=4 $ in the second day, $ a_3=3 $ in the third day. So in odd days she will eat $ 1+3=4 $ and in even days she will eat $ 4 $ . Since $ 4 = 4 $ this case should be counted to the answer (this candy is good).

In total there $ 2 $ cases which should counted (these candies are good), so the answer is $ 2 $ .

## 说明/提示

In the first example indices of good candies are $ [1, 2] $ .

In the second example indices of good candies are $ [2, 3] $ .

In the third example indices of good candies are $ [4, 5, 9] $ .

## 样例 #1

### 输入

```
7
5 5 4 5 5 5 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
4 8 8 7 8 4 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 3 4 2 2 3 2 2 4
```

### 输出

```
3
```

# AI分析结果



# Tanya and Candies

## 题目描述

Tanya 有 $ n $ 颗糖果，编号从 $ 1 $ 到 $ n $，第 $ i $ 颗糖果的重量为 $ a_i $。她计划吃掉 $ n-1 $ 颗糖果并将剩下的那颗给爸爸。要求找到所有满足条件的糖果 $ i $，使得当爸爸获得第 $ i $ 颗糖果时，Tanya 在偶数天吃的糖果总重量等于奇数天吃的总重量。

## 算法分类
前缀和

---

## 题解分析与结论

### 核心思路
所有题解均基于前缀和思想，通过预处理奇偶位置的前缀和数组，实现 $ O(1) $ 时间判断每个糖果是否满足条件。关键点在于：
1. **奇偶位置分离**：分别维护奇数位置和偶数位置的前缀和数组。
2. **动态计算差值**：当移除第 $ i $ 个元素时，将前 $ i-1 $ 项的奇偶和与后 $ n-i $ 项的奇偶翻转后的和相加，判断是否相等。

---

## 高分题解推荐

### 1. minVan（★★★★★）
**亮点**：  
- 使用滚动数组动态维护奇偶和，空间复杂度优化为 $ O(1) $。
- 代码简洁高效，仅需两次遍历。

**核心代码**：
```cpp
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i % 2] += a[i];
    }
    for(int i = 1; i <= n; i++) {
        sum[i % 2] -= a[i];
        if(p[0] + sum[1] == p[1] + sum[0]) ans++;
        p[i % 2] += a[i];
    }
    cout << ans;
}
```

### 2. qpzc（★★★★☆）
**亮点**：  
- 显式定义奇偶前缀和数组，逻辑清晰。
- 公式推导直观，便于理解奇偶翻转后的组合方式。

**核心公式**：
```cpp
// 前i-1项奇数位和 + 后n-i项偶数位和
ji[i-1] + (ou[n] - ou[i]) 
// 是否等于 
// 前i-1项偶数位和 + 后n-i项奇数位和
ou[i-1] + (ji[n] - ji[i])
```

### 3. 06ray（★★★★☆）
**亮点**：  
- 明确预处理和后缀翻转的思路。
- 变量命名直观（even/odd数组）。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    int x = odd[n] - odd[i];
    int y = even[n] - even[i];
    if(x + even[i-1] == y + odd[i-1]) ans++;
}
```

---

## 关键技巧总结
1. **奇偶前缀分离**：将奇偶位置的和分别存入两个数组，避免混算。
2. **后缀翻转处理**：移除元素后，后续元素的奇偶性会反转，通过交换奇偶后缀和实现快速计算。
3. **滚动数组优化**：动态维护奇偶和，减少空间占用。

---

## 拓展与相似题目
1. [P1982 小朋友的数字](https://www.luogu.com.cn/problem/P1982)  
   **标签**：前缀和、动态规划  
   **相似点**：利用前缀和与动态性质结合求解极值。

2. [P2671 求和](https://www.luogu.com.cn/problem/P2671)  
   **标签**：数学、奇偶性质  
   **相似点**：奇偶分组后计算组合贡献。

3. [P4440 传球游戏](https://www.luogu.com.cn/problem/P4440)  
   **标签**：递推、奇偶状态  
   **相似点**：通过奇偶状态转移优化递推过程。

---
处理用时：40.90秒