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



# Nick and Array 中文题面

## 题目描述

尼克收到了一个由整数组成的数组 $ a=[a_1, a_2, \dots, a_n] $ 作为5岁生日礼物。他原本想研究这个数组的各种性质，但当他拆开礼物后非常失望，因为这个数组所有元素的乘积 $ a_1 \cdot a_2 \cdot \dots \cdot a_n $ 看起来不够大。

他正准备扔掉这个数组时，他的母亲告诉他可以通过以下操作来提升数组的乘积：选择任意索引 $ i $（$ 1 \le i \le n $），执行 $ a_i := -a_i - 1 $。

例如，将数组 $ [3, -1, -4, 1] $ 对索引 $ i=1 $ 和 $ i=3 $ 进行操作后，可以得到数组 $ [-4, -1, 3, 1] $。

现在你需要帮助尼克找到通过任意次操作（允许对同一元素多次操作）后，能得到的最大可能乘积的数组。若存在多个答案，输出任意一个。

## 样例 #1

### 输入
```
4
2 2 2 2
```

### 输出
```
-3 -3 -3 -3
```

## 样例 #2

### 输入
```
1
0
```

### 输出
```
0
```

## 样例 #3

### 输入
```
3
-3 -3 2
```

### 输出
```
-3 -3 2
```

---

# 题解分析与结论

## 核心思路
所有题解均基于以下贪心策略：
1. **最大化绝对值**：对每个正数执行一次操作，将其变为绝对值更大的负数
2. **奇偶处理**：若数组长度 $n$ 为奇数，则需要将绝对值最大的负数变回正数，确保乘积为正

## 关键技巧
- **符号转换公式**：$ a_i = -a_i -1 $ 可将正数转为更大绝对值的负数
- **极值选择**：当 $n$ 为奇数时，选择绝对值最大的负数（即最小的负数）进行反转

---

# 优质题解推荐

## 1. 作者：Fislett（4.5星）
**亮点**：变量命名清晰，代码简洁，完整处理边界条件  
**代码核心**：
```cpp
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] >= 0) a[i] = -a[i] - 1;
        minn = min(minn, a[i]); // 记录最小负数（最大绝对值）
    }
    if (n & 1) { // 奇数长度处理
        for (int i = 1; i <= n; i++) {
            if (a[i] == minn) {
                a[i] = -a[i] - 1;
                break;
            }
        }
    }
    // 输出处理后的数组
}
```

## 2. 作者：_Album_（4星）
**亮点**：详细数学推导，强调偶数乘积特性  
**关键思路**：
> "偶数个负数相乘得正，奇数长度下必须牺牲一个绝对值最大的负数来确保整体乘积为正"

## 3. 作者：幽界の冥神（4星）
**代码亮点**：极值初始化优化  
**核心代码**：
```cpp
int mn = 0x3f3f3f3f; // 初始极大值确保首次比较生效
for (int i = 1; i <= n; i++) {
    if (a[i] >= 0) a[i] = -a[i] - 1;
    if (a[i] < mn) { // 动态更新最小负数
        mn = a[i];
        ret = i;     // 记录位置
    }
}
```

---

# 举一反三
## 相似题目推荐
1. [P1018 乘积最大](https://www.luogu.com.cn/problem/P1018) - 动态规划处理数字分割乘积
2. [P1282 多米诺骨牌](https://www.luogu.com.cn/problem/P1282) - 权衡正负差值的最小化
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233) - 贪心策略中的极值选择

## 关键思维拓展
- **符号与绝对值分离**：在涉及乘积优化的问题中，常需要独立分析符号和绝对值
- **奇偶分类讨论**：当操作次数或元素数量与奇偶性相关时，需单独处理边界情况

---
处理用时：125.13秒