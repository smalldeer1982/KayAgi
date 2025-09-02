# 题目信息

# Nick and Array

## 题目描述

Nick had received an awesome array of integers $ a=[a_1, a_2, \dots, a_n] $ as a gift for his $ 5 $ birthday from his mother. He was already going to explore its various properties but after unpacking he was disappointed a lot because the product $ a_1 \cdot a_2 \cdot \dots a_n $ of its elements seemed to him not large enough.

He was ready to throw out the array, but his mother reassured him. She told him, that array would not be spoiled after the following operation: choose any index $ i $ ( $ 1 \le i \le n $ ) and do $ a_i := -a_i - 1 $ .

For example, he can change array $ [3, -1, -4, 1] $ to an array $ [-4, -1, 3, 1] $ after applying this operation to elements with indices $ i=1 $ and $ i=3 $ .

Kolya had immediately understood that sometimes it's possible to increase the product of integers of the array a lot. Now he has decided that he wants to get an array with the maximal possible product of integers using only this operation with its elements (possibly zero, one or more times, as many as he wants), it is not forbidden to do this operation several times for the same index.

Help Kolya and print the array with the maximal possible product of elements $ a_1 \cdot a_2 \cdot \dots a_n $ which can be received using only this operation in some order.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
2 2 2 2
```

### 输出

```
-3 -3 -3 -3 ```

## 样例 #2

### 输入

```
1
0
```

### 输出

```
0 ```

## 样例 #3

### 输入

```
3
-3 -3 2
```

### 输出

```
-3 -3 2 ```

# AI分析结果



### 题目翻译：Nick and Array

#### 题目描述  
Nick 在 5 岁生日时收到了一个整数数组 $a=[a_1, a_2, \dots, a_n]$。他希望通过操作使数组元素的乘积最大化。操作规则为：选择任意下标 $i$，将 $a_i$ 变为 $-a_i -1$（可多次操作同一元素）。输出最终能得到最大乘积的数组（若有多个解，输出任意一个）。

#### 样例  
**样例 #1**  
输入：  
```
4
2 2 2 2  
```  
输出：  
```
-3 -3 -3 -3  
```  

**样例 #2**  
输入：  
```
1
0  
```  
输出：  
```
0  
```  

**样例 #3**  
输入：  
```
3  
-3 -3 2  
```  
输出：  
```
-3 -3 2  
```  

---

### 题解综合分析与结论  
**核心思路**：  
1. **贪心策略**：将所有正数转换为负数（操作后绝对值更大）。  
2. **奇偶处理**：若数组长度 $n$ 为奇数，需将绝对值最大的负数（即最小的数）转回正数，使总乘积为正且最大。  

**关键技巧**：  
- 绝对值的最大化优先于符号的调整。  
- 奇偶性决定是否需要反转一个元素。  

---

### 精选题解  
#### 1. 作者：wucstdio（⭐⭐⭐⭐⭐）  
**亮点**：  
- 代码简洁高效，时间复杂度 $O(n)$。  
- 明确分步处理正数转换和奇偶调整。  
**核心代码**：  
```cpp
for(int i=1;i<=n;i++) {
    if(a[i]>=0) a[i]=-a[i]-1;
    maxx = min(maxx, a[i]); // 记录最小值（绝对值最大）
}
if(n&1) {
    // 反转绝对值最大的负数
    for(int i=1;i<=n;i++) {
        if(a[i]==maxx) {
            a[i]=-a[i]-1;
            break;
        }
    }
}
```

#### 2. 作者：Fislett（⭐⭐⭐⭐）  
**亮点**：  
- 变量命名清晰，逻辑与 wucstdio 一致。  
- 代码中 `minn` 用于跟踪最小值，与 `maxx` 思路相同。  
**个人心得**：  
> "显然，偶数个负数乘积为正，奇数时需调整一个数。"

#### 3. 作者：Stars_visitor_tyw（⭐⭐⭐⭐）  
**亮点**：  
- 代码结构清晰，注释明确。  
- 使用 `mini` 变量记录最小值的位置。  

---

### 相似题目推荐  
1. [CF1180B](https://www.luogu.com.cn/problem/CF1180B)（本题）  
2. [P1018 乘积最大](https://www.luogu.com.cn/problem/P1018)（贪心+动态规划）  
3. [P1246 编码问题](https://www.luogu.com.cn/problem/P1246)（绝对值与排列组合）  
4. [P1809 过河问题](https://www.luogu.com.cn/problem/P1809)（贪心策略优化）

---
处理用时：41.21秒