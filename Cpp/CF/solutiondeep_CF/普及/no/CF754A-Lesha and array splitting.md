# 题目信息

# Lesha and array splitting

## 题目描述

One spring day on his way to university Lesha found an array $ A $ . Lesha likes to split arrays into several parts. This time Lesha decided to split the array $ A $ into several, possibly one, new arrays so that the sum of elements in each of the new arrays is not zero. One more condition is that if we place the new arrays one after another they will form the old array $ A $ .

Lesha is tired now so he asked you to split the array. Help Lesha!

## 样例 #1

### 输入

```
3
1 2 -3
```

### 输出

```
YES
2
1 2
3 3
```

## 样例 #2

### 输入

```
8
9 -12 3 4 -4 -10 7 3
```

### 输出

```
YES
2
1 2
3 8
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
1 2 3 -5
```

### 输出

```
YES
4
1 1
2 2
3 3
4 4
```

# AI分析结果



# Lesha 与数组分割

## 题目描述

某天春天，Lesha 在上学路上发现一个数组 $A$。他喜欢将数组分割成若干部分。这次他想将数组 $A$ 分割成若干个（可能一个）新数组，使得每个新数组的元素和不为零。此外，分割后的新数组按顺序连接后必须能还原原数组 $A$。请帮助 Lesha 完成分割。

## 样例 #1

### 输入

```
3
1 2 -3
```

### 输出

```
YES
2
1 2
3 3
```

## 样例 #2

### 输入

```
8
9 -12 3 4 -4 -10 7 3
```

### 输出

```
YES
2
1 2
3 8
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
1 2 3 -5
```

### 输出

```
YES
4
1 1
2 2
3 3
4 4
```

---

## 算法分类
构造

---

## 题解综合分析

**核心思路**：  
1. **总和非零直接分割**：若数组总和非零，整个数组作为唯一子数组即可。
2. **总和为零找分割点**：当总和为零时，找到第一个非零元素的位置，将数组分割为前部分（含该元素）和后部分，两部分和均不为零。
3. **全零数组无解**：所有元素均为零时无法分割。

**解决难点**：  
- 正确处理总和为零时的分割逻辑，需证明分割后的两部分和均非零。
- 避免全零数组的误判。

---

## 精选题解

### 题解作者：_byta（★★★★☆）
**关键亮点**：  
- 逻辑简洁，直接处理两种核心情况。
- 代码短小精悍，无冗余判断。

**核心代码**：
```cpp
if (sum != 0) {
    printf("YES\n1\n1 %d", n);
} else {
    for (int i = 1; i <= n; i++) {
        if (a[i] != 0) {
            printf("YES\n2\n1 %d\n%d %d\n", i, i+1, n);
            return 0;
        }
    }
    printf("NO\n");
}
```

---

### 题解作者：lichenzhen（★★★★☆）
**关键亮点**：  
- 中文注释详细，解释分割数学原理。
- 代码结构清晰，易读性强。

**核心代码**：
```cpp
if (a != 0) {
    cout << "YES\n1\n1 " << n;
} else {
    for (int i = 1; i <= n; i++) {
        if (l[i]) {
            cout << "YES\n2\n1 " << i << "\n" << i+1 << " " << n;
            return 0;
        }
    }
    cout << "NO";
}
```

---

### 题解作者：InversionShadow（★★★★☆）
**关键亮点**：  
- 增加全零数组的显式判断。
- 使用布尔标记优化逻辑流程。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    flag = (a[i] == 0);
    if (!flag) break;
}
if (flag) cout << "NO";
else if (sum) cout << "YES\n1\n1 " << n;
else {
    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            cout << "YES\n2\n1 " << i << "\n" << i+1 << " " << n;
            return 0;
        }
    }
}
```

---

## 关键思路总结
1. **贪心分割策略**：总和非零时直接整体分割，否则寻找第一个非零元素作为分割点。
2. **数学验证**：当总和为零时，前段和为非零值，后段和为该值的相反数，保证两部分均非零。
3. **边界处理**：全零数组需单独判断，避免无效分割。

---

## 拓展应用
- **类似题型**：分割数组满足特定条件的问题，如子段和为正数、子段异或非零等。
- **技巧迁移**：寻找关键分割点的思想可用于其他构造问题（如字符串分割、区间划分）。

---

## 推荐习题
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心分配）
2. [CF1176A Divide it!](https://codeforces.com/problemset/problem/1176/A)（构造操作序列）
3. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209)（贪心选择间隔）

---
处理用时：95.00秒