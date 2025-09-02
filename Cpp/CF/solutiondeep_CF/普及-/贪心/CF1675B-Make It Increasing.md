# 题目信息

# Make It Increasing

## 题目描述

Given $ n $ integers $ a_1, a_2, \dots, a_n $ . You can perform the following operation on them:

- select any element $ a_i $ ( $ 1 \le i \le n $ ) and divide it by $ 2 $ (round down). In other words, you can replace any selected element $ a_i $ with the value $ \left \lfloor \frac{a_i}{2}\right\rfloor $ (where $ \left \lfloor x \right\rfloor $ is – round down the real number $ x $ ).

Output the minimum number of operations that must be done for a sequence of integers to become strictly increasing (that is, for the condition $ a_1 \lt a_2 \lt \dots \lt a_n $ to be satisfied). Or determine that it is impossible to obtain such a sequence. Note that elements cannot be swapped. The only possible operation is described above.

For example, let $ n = 3 $ and a sequence of numbers $ [3, 6, 5] $ be given. Then it is enough to perform two operations on it:

- Write the number $ \left \lfloor \frac{6}{2}\right\rfloor = 3 $ instead of the number $ a_2=6 $ and get the sequence $ [3, 3, 5] $ ;
- Then replace $ a_1=3 $ with $ \left \lfloor \frac{3}{2}\right\rfloor = 1 $ and get the sequence $ [1, 3, 5] $ .

The resulting sequence is strictly increasing because $ 1 \lt 3 \lt 5 $ .

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, it is impossible to obtain a strictly increasing sequence.

In the third test case, the sequence is already strictly increasing.

## 样例 #1

### 输入

```
7
3
3 6 5
4
5 3 2 1
5
1 2 3 4 5
1
1000000000
4
2 8 7 5
5
8 26 5 21 10
2
5 14```

### 输出

```
2
-1
0
0
4
11
0```

# AI分析结果



### 题目重述

# 使序列递增

## 题目描述

给定 $ n $ 个整数 $ a_1, a_2, \dots, a_n $。你可以对它们进行如下操作：

- 选择任意元素 $ a_i $（$ 1 \le i \le n $）并将其除以 $ 2 $（向下取整）。即，将 $ a_i $ 替换为 $ \left\lfloor \frac{a_i}{2} \right\rfloor $。

要求通过最少的操作次数使序列变为严格递增（即 $ a_1 < a_2 < \dots < a_n $）。若无法实现，输出 $-1$。

## 样例

输入输出样例与题面一致，此处省略。

---

### 题解分析与结论

#### 核心思路总结

1. **逆向贪心**：从后往前处理每个元素，确保当前元素小于后一个元素。因最后一个元素无法调整，倒序处理可最大化利用右侧已确定的值。
2. **边界处理**：若某元素变为 $0$ 后仍不满足条件，或处理后相邻元素相等，则判定无解。
3. **最终校验**：处理完成后必须再次遍历整个序列，确保严格递增性（如处理后的相等情况可能被遗漏）。

#### 最优题解

---

##### 题解作者：ztrztr（4星）

**关键亮点**：  
- 倒序贪心处理，代码简洁  
- 最终检查保证严格递增性  
- 利用循环中断条件避免死锁  

```cpp
for (int i = n - 1; i > 0; i--) {
    while (a[i] >= a[i + 1]) {
        if (a[i] == 0) { // 无法进一步缩小
            flag = 0;
            break;
        }
        a[i] /= 2;
        cnt++;
    }
}
// 最终校验所有相邻元素
for (int i = 1; i < n; i++) {
    if (a[i] >= a[i + 1]) flag = 0;
}
```

---

##### 题解作者：Engulf（4星）

**关键亮点**：  
- 处理中即时检查相等性  
- 使用 `goto` 快速跳出多层循环  
- 最终严格递增性验证  

```cpp
for(int i=n;i>=2;i--){
    while(a[i-1]>=a[i]){
        if(a[i-1]==a[i] && a[i]==0) goto qwq; // 相等且为0时无解
        a[i-1]/=2;
        ans++;
    }
}
qwq: // 跳转点
for(int i=2;i<=n;i++){ // 最终校验
    if(a[i-1]>=a[i]) flag=false;
}
```

---

##### 题解作者：ryanright（4星）

**关键亮点**：  
- 清晰的分步操作与校验  
- 处理到 $0$ 时及时终止循环  
- 最终遍历检查所有相邻元素  

```cpp
for (int i = n - 1; i >= 1; i--) {
    while (a[i] >= a[i + 1]) {
        if (!a[i]) break; // 无法继续缩小
        a[i] /= 2;
        cnt++;
    }
}
// 检查是否存在非递增或相等
for (int i = 1; i < n; i++) {
    if (a[i] >= a[i + 1]) flag = 0;
}
```

---

### 关键技巧与拓展

#### 核心技巧

1. **逆向思维**：当末位元素固定时，逆向调整可确保每一步的局部最优导向全局最优。
2. **向下取整特性**：除以 $2$ 的操作最终会使元素趋近于 $0$，需特别处理 $0$ 的边界条件。
3. **最终校验必要性**：操作可能引入相等元素或残留逆序对，必须全序列验证。

#### 相似题目

1. **CF977D Divide by three, multiply by two**（CF977D）  
   - 通过除法与乘法操作构造特定序列，考察逆向思维与操作路径规划。
   
2. **LeetCode 665. 非递减数列**（LeetCode 665）  
   - 允许一次修改操作，判断能否使数组非递减，考察贪心策略与边界处理。

3. **洛谷 P1102 最大递增子序列**  
   - 经典动态规划问题，与序列调整操作有相似的最优子结构分析。

---
处理用时：165.13秒