# 题目信息

# Rock and Lever

## 题目描述

"You must lift the dam. With a lever. I will give it to you.You must block the canal. With a rock. I will not give the rock to you."





Danik urgently needs rock and lever! Obviously, the easiest way to get these things is to ask Hermit Lizard for them.

Hermit Lizard agreed to give Danik the lever. But to get a stone, Danik needs to solve the following task.

You are given a positive integer $ n $ , and an array $ a $ of positive integers. The task is to calculate the number of such pairs $ (i,j) $ that $ i<j $ and $ a_i $ $ \& $ $ a_j \ge a_i \oplus a_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Danik has solved this task. But can you solve it?

## 说明/提示

In the first test case there is only one pair: $ (4,7) $ : for it $ 4 $ $ \& $ $ 7 = 4 $ , and $ 4 \oplus 7 = 3 $ .

In the second test case all pairs are good.

In the third test case there are two pairs: $ (6,5) $ and $ (2,3) $ .

In the fourth test case there are no good pairs.

## 样例 #1

### 输入

```
5
5
1 4 3 7 10
3
1 1 1
4
6 2 5 3
2
2 4
1
1```

### 输出

```
1
3
2
0
0```

# AI分析结果

### 题目重写
**题目描述**

"你必须用杠杆抬起水坝。我会给你杠杆。你必须用石头堵住运河。我不会给你石头。"

Danik 急需石头和杠杆！显然，获得这些东西最简单的方法就是向隐士蜥蜴索要。

隐士蜥蜴同意给 Danik 杠杆。但要获得石头，Danik 需要解决以下任务。

给定一个正整数 $n$ 和一个正整数数组 $a$。任务是计算满足 $i<j$ 且 $a_i \& a_j \ge a_i \oplus a_j$ 的对 $(i,j)$ 的数量，其中 $\&$ 表示按位与操作，$\oplus$ 表示按位异或操作。

Danik 已经解决了这个任务。但你能解决吗？

### 算法分类
位运算

### 题解分析与结论
所有题解都基于位运算的性质，特别是按位与和按位异或操作的最高位分析。核心思路是：当两个数的二进制最高位相同时，按位与的结果大于等于按位异或的结果。因此，统计每个最高位的数的个数，然后计算这些数中任选两个的组合数即可。

### 所选高星题解
#### 题解1：STDquantum (4星)
**关键亮点**
- 清晰解释了按位与和按位异或操作的最高位关系。
- 代码简洁，直接统计每个最高位的数的个数，并计算组合数。

**核心代码**
```cpp
for (int i = 1, x; i <= n; ++i) {
    read(x);
    for (int k = 30; ~k; --k) {
        if (x & (1 << k)) {
            ++num[k];
            break;
        }
    }
}
ans = 0;
for (int i = 0; i <= 30; ++i) {
    ans += (ll)num[i] * (num[i] - 1) / 2;
    num[i] = 0; // 省掉memset
}
```

#### 题解2：Skyjoy (4星)
**关键亮点**
- 详细分析了按位与和按位异或操作的最高位关系。
- 代码中使用了 `lg` 函数来计算最高位，增加了可读性。

**核心代码**
```cpp
for (int i = 1; i <= n; i++) {
    x = read();
    cnt[lg(x)]++;
    maxn = max(maxn, lg(x));
}
for (int i = 1; i <= maxn; i++) ans += 1ll * (cnt[i] - 1) * (cnt[i]) / 2;
```

#### 题解3：nztyz (4星)
**关键亮点**
- 使用了 `get_bit` 函数来判断最高位，代码结构清晰。
- 详细解释了按位与和按位异或操作的最高位关系。

**核心代码**
```cpp
for(int i = 29 ; i >= 0 ; i--){
    if(get_bit(x,i)){
        cnt[i]++;
        break;
    }
}
long long ans = 0;
for(int i = 0 ; i < 30 ; i++){
    ans += cnt[i] * (cnt[i]-1ll) / 2;
}
```

### 最优关键思路
- **最高位分析**：当两个数的二进制最高位相同时，按位与的结果大于等于按位异或的结果。
- **组合数计算**：统计每个最高位的数的个数，然后计算这些数中任选两个的组合数。

### 拓展思路
- **类似题目**：可以考虑其他基于位运算的题目，如求数组中满足某些位运算条件的对数。
- **优化技巧**：在处理位运算问题时，优先考虑最高位的性质，可以简化问题。

### 推荐题目
1. [P1896 [SCOI2005]互不侵犯](https://www.luogu.com.cn/problem/P1896)
2. [P2114 [NOI2014]起床困难综合症](https://www.luogu.com.cn/problem/P2114)
3. [P2320 [HNOI2006]鬼谷子的钱袋](https://www.luogu.com.cn/problem/P2320)

---
处理用时：30.83秒