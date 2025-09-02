# 题目信息

# Swap Dilemma

## 题目描述

Given two arrays of distinct positive integers $ a $ and $ b $ of length $ n $ , we would like to make both the arrays the same. Two arrays $ x $ and $ y $ of length $ k $ are said to be the same when for all $ 1 \le i \le k $ , $ x_i = y_i $ .

Now in one move, you can choose some index $ l $ and $ r $ in $ a $ ( $ l \le r $ ) and swap $ a_l $ and $ a_r $ , then choose some $ p $ and $ q $ ( $ p \le q $ ) in $ b $ such that $ r-l=q-p $ and swap $ b_p $ and $ b_q $ .

Is it possible to make both arrays the same?

## 说明/提示

In the first testcase, you don't need to perform any operations since the arrays are same.

In the second testcase, it can be proven there exists no way to make the arrays same.

In the third testcase, one of the ways to make the arrays same is to first choose $ l=1 $ , $ r=3 $ , $ p=1 $ , $ q=3 $ then choose $ l=1 $ , $ r=2 $ , $ p=3 $ , $ q=4 $ .

## 样例 #1

### 输入

```
6
4
1 2 3 4
1 2 3 4
5
1 3 4 2 5
7 1 2 5 4
4
1 2 3 4
4 3 2 1
3
1 2 3
1 3 2
5
1 5 7 1000 4
4 1 7 5 1000
3
1 4 2
1 3 2```

### 输出

```
YES
NO
YES
NO
NO
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

给定两个长度为 $n$ 的由互不相同的正整数组成的数组 $a$ 和 $b$，我们希望通过若干次操作使得这两个数组相同。每次操作可以选择数组 $a$ 中的两个下标 $l$ 和 $r$（$l \le r$），交换 $a_l$ 和 $a_r$，同时选择数组 $b$ 中的两个下标 $p$ 和 $q$（$p \le q$），交换 $b_p$ 和 $b_q$，且要求 $r - l = q - p$。

问是否可以通过若干次操作使得 $a$ 和 $b$ 相同？

#### 说明/提示

- 在第一个测试用例中，数组已经相同，无需操作。
- 在第二个测试用例中，无法通过任何操作使数组相同。
- 在第三个测试用例中，可以通过两次操作使数组相同。

#### 样例

##### 输入
```
6
4
1 2 3 4
1 2 3 4
5
1 3 4 2 5
7 1 2 5 4
4
1 2 3 4
4 3 2 1
3
1 2 3
1 3 2
5
1 5 7 1000 4
4 1 7 5 1000
3
1 4 2
1 3 2
```

##### 输出
```
YES
NO
YES
NO
NO
NO
```

### 算法分类
排序、逆序对、数学

### 题解分析与结论

本题的核心思路是通过分析数组的逆序对奇偶性来判断是否可以通过操作使两个数组相同。大多数题解都基于以下两个关键点：
1. **逆序对奇偶性**：两个数组的逆序对数的奇偶性必须相同，才能通过操作使它们相同。
2. **排序与逆序对**：通过排序和计算逆序对，可以判断两个数组是否可以通过操作变得相同。

### 精选题解

#### 题解1：作者：TTpandaS (赞：14)
- **星级**：5星
- **关键亮点**：简洁明了地指出了逆序对奇偶性的重要性，并通过冒泡排序的思路解释了为什么奇偶性相同时可以使得数组相同。
- **代码核心**：
  ```cpp
  // 计算逆序对数的奇偶性
  if (inv_a % 2 == inv_b % 2) {
      cout << "YES";
  } else {
      cout << "NO";
  }
  ```

#### 题解2：作者：Diaоsi (赞：7)
- **星级**：4星
- **关键亮点**：详细证明了逆序对奇偶性与环数的关系，进一步加深了对问题的理解。
- **代码核心**：
  ```cpp
  // 通过树状数组计算逆序对数
  int get() {
      int res = 0;
      for (int i = 1; i <= n; i++) {
          res += i - 1 - query(pos[i]);
          update(pos[i], 1);
      }
      return res;
  }
  ```

#### 题解3：作者：Special_Tony (赞：2)
- **星级**：4星
- **关键亮点**：通过归并排序计算逆序对数，代码实现清晰，易于理解。
- **代码核心**：
  ```cpp
  void mergesort(int l, int r, int a[], ll& ans) {
      if (l >= r) return;
      int mid = (l + r) / 2;
      mergesort(l, mid, a, ans);
      mergesort(mid + 1, r, a, ans);
      int i = l, j = mid + 1, k = l;
      while (i <= mid && j <= r) {
          if (a[i] > a[j]) {
              c[k++] = a[j++];
              ans += mid - i + 1;
          } else {
              c[k++] = a[i++];
          }
      }
      while (i <= mid) c[k++] = a[i++];
      while (j <= r) c[k++] = a[j++];
      for (int i = l; i <= r; i++) a[i] = c[i];
  }
  ```

### 最优关键思路
1. **逆序对奇偶性**：通过计算两个数组的逆序对数，判断其奇偶性是否相同，这是判断是否可以通过操作使数组相同的关键。
2. **排序与逆序对**：通过排序和计算逆序对，可以有效地判断两个数组是否可以通过操作变得相同。

### 可拓展之处
- **类似问题**：类似的问题可以通过分析逆序对或排列的奇偶性来解决，如判断两个排列是否可以通过交换相邻元素变得相同。
- **算法优化**：可以使用树状数组或归并排序来高效计算逆序对数。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)
3. [P1774 最接近神的人](https://www.luogu.com.cn/problem/P1774)

---
处理用时：41.63秒