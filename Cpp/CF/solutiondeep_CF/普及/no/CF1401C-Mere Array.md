# 题目信息

# Mere Array

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ where all $ a_i $ are integers and greater than $ 0 $ .

 In one operation, you can choose two different indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ). If $ gcd(a_i, a_j) $ is equal to the minimum element of the whole array $ a $ , you can swap $ a_i $ and $ a_j $ . $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

 Now you'd like to make $ a $ non-decreasing using the operation any number of times (possibly zero). Determine if you can do this.

 An array $ a $ is non-decreasing if and only if $ a_1 \le a_2       \le \ldots \le a_n $ .

## 说明/提示

In the first and third sample, the array is already non-decreasing.

 In the second sample, we can swap $ a_1 $ and $ a_3 $ first, and swap $ a_1 $ and $ a_5 $ second to make the array non-decreasing.

 In the forth sample, we cannot the array non-decreasing using the operation.

## 样例 #1

### 输入

```
4
1
8
6
4 3 6 6 2 9
4
4 5 6 7
5
7 5 2 2 4```

### 输出

```
YES
YES
YES
NO```

# AI分析结果

### 题目内容
给定一个数组 $a_1, a_2, \dots, a_n$，其中所有 $a_i$ 都是正整数。在一次操作中，你可以选择两个不同的下标 $i$ 和 $j$（$1 \le i, j \le n$）。如果 $gcd(a_i, a_j)$ 等于整个数组的最小元素，那么你可以交换 $a_i$ 和 $a_j$。$gcd(x, y)$ 表示整数 $x$ 和 $y$ 的最大公约数。

现在，你希望通过任意次数的操作（可能为零次）使得数组 $a$ 非递减。确定你是否能做到这一点。

一个数组 $a$ 是非递减的，当且仅当 $a_1 \le a_2 \le \ldots \le a_n$。

### 算法分类
数学、排序

### 题解分析与结论
题解的核心思路是：通过排序后的数组与原数组进行对比，判断哪些元素需要交换。如果某个元素不在其最终位置且不能被数组的最小元素整除，则无法通过交换操作使其达到目标位置，输出 `NO`；否则输出 `YES`。

### 所选题解
#### 1. 作者：Little09 (4星)
**关键亮点**：提供了详细的证明，解释了为什么只有当元素能被最小元素整除时才能交换，且通过间接交换可以实现任意两个满足条件的元素的交换。
**代码核心思想**：排序后遍历数组，检查每个元素是否在其最终位置或能被最小元素整除。
```cpp
for (int i=1;i<=n;i++) {
    if (a[i]!=b[i]&&a[i]%b[1]!=0) {
        cout << "NO" << endl;
        goto no;
    }
}
```

#### 2. 作者：jun头吉吉 (4星)
**关键亮点**：通过构建集合的概念，解释了所有能被最小元素整除的元素可以通过间接交换实现任意排列，而其他元素无法移动。
**代码核心思想**：排序后检查每个元素是否在其最终位置或能被最小元素整除。
```cpp
for(int i=1;i<=n;i++)
    if(a[i]%mn&&a[i]!=a[i-1]){
        if(flag[a[i]]){
            puts("NO");
            goto loop;
        }
        flag[a[i]]=1;
        if(Rank[a[i]]!=i-1){
            puts("NO");
            goto loop;
        }
    }
```

#### 3. 作者：_Give_up_ (4星)
**关键亮点**：通过遍历数组，检查每个元素是否在其最终位置或能被最小元素整除，简洁明了。
**代码核心思想**：排序后遍历数组，检查每个元素是否在其最终位置或能被最小元素整除。
```cpp
for (int i=1;i<=n;i++) {
    if (a[i]!=b[i] && a[i]%k) {
        cout << "NO" << endl;
        flag = false;
        break;
    }
}
```

### 最优关键思路
1. **间接交换**：通过最小元素作为中介，实现任意两个能被最小元素整除的元素的交换。
2. **排序对比**：通过排序后的数组与原数组进行对比，判断哪些元素需要交换。

### 可拓展之处
类似的问题可以通过间接交换的思路来解决，尤其是在涉及到元素交换和排序的题目中。可以考虑使用类似的方法来处理其他需要交换操作的排序问题。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

---
处理用时：27.02秒