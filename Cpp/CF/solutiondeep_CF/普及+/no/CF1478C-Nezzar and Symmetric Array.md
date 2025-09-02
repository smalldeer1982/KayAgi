# 题目信息

# Nezzar and Symmetric Array

## 题目描述

Long time ago there was a symmetric array $ a_1,a_2,\ldots,a_{2n} $ consisting of $ 2n $ distinct integers. Array $ a_1,a_2,\ldots,a_{2n} $ is called symmetric if for each integer $ 1 \le i \le 2n $ , there exists an integer $ 1 \le j \le 2n $ such that $ a_i = -a_j $ .

For each integer $ 1 \le i \le 2n $ , Nezzar wrote down an integer $ d_i $ equal to the sum of absolute differences from $ a_i $ to all integers in $ a $ , i. e. $ d_i = \sum_{j = 1}^{2n} {|a_i - a_j|} $ .

Now a million years has passed and Nezzar can barely remember the array $ d $ and totally forget $ a $ . Nezzar wonders if there exists any symmetric array $ a $ consisting of $ 2n $ distinct integers that generates the array $ d $ .

## 说明/提示

In the first test case, $ a=[1,-3,-1,3] $ is one possible symmetric array that generates the array $ d=[8,12,8,12] $ .

In the second test case, it can be shown that there is no symmetric array consisting of distinct integers that can generate array $ d $ .

## 样例 #1

### 输入

```
6
2
8 12 8 12
2
7 7 9 11
2
7 11 7 11
1
1 1
4
40 56 48 40 80 56 80 48
6
240 154 210 162 174 154 186 240 174 186 162 210```

### 输出

```
YES
NO
NO
NO
NO
YES```

# AI分析结果

### 题目中文重写
## Nezzar和对称数组

### 题目描述
很久以前，有一个由 $2n$ 个不同整数组成的对称数组 $a_1,a_2,\ldots,a_{2n}$。如果对于每个整数 $1 \le i \le 2n$，都存在一个整数 $1 \le j \le 2n$ 使得 $a_i = -a_j$，则称数组 $a_1,a_2,\ldots,a_{2n}$ 是对称的。

对于每个整数 $1 \le i \le 2n$，Nezzar 写下一个整数 $d_i$，它等于 $a_i$ 到 $a$ 中所有整数的绝对差之和，即 $d_i = \sum_{j = 1}^{2n} {|a_i - a_j|}$。

现在一百万年过去了，Nezzar 几乎记不起数组 $d$，完全忘记了数组 $a$。Nezzar 想知道是否存在任何由 $2n$ 个不同整数组成的对称数组 $a$ 能生成数组 $d$。

### 说明/提示
在第一个测试用例中，$a=[1,-3,-1,3]$ 是一个可能的对称数组，它能生成数组 $d=[8,12,8,12]$。

在第二个测试用例中，可以证明不存在由不同整数组成的对称数组能生成数组 $d$。

### 样例 #1
#### 输入
```
6
2
8 12 8 12
2
7 7 9 11
2
7 11 7 11
1
1 1
4
40 56 48 40 80 56 80 48
6
240 154 210 162 174 154 186 240 174 186 162 210
```
#### 输出
```
YES
NO
NO
NO
NO
YES
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学推导，利用对称数组的性质和 $d$ 数组的定义来判断是否能构造出满足条件的 $a$ 数组。
- **思路对比**：大部分题解先对 $d$ 数组排序，根据对称数组的特点判断 $d$ 数组中元素是否成对相等。然后通过数学公式递推计算出可能的 $a$ 数组元素，检查计算过程中是否满足整数、正数、元素不重复等条件。不同题解在推导数学公式时的方式略有不同，有的从绝对值运算性质出发，有的借助数轴分析。
- **算法要点**：排序是为了方便后续处理，利用对称数组性质判断 $d$ 数组的合法性，通过递推公式计算 $a$ 数组元素，最后检查计算结果的合法性。
- **解决难点**：关键在于推导出合适的数学公式来计算 $a$ 数组元素，以及处理计算过程中可能出现的不合法情况，如不能整除、元素重复、非正数等。

### 题解评分
| 作者 | 评分 | 理由 |
| --- | --- | --- |
| 胖头鱼学员 | 4星 | 思路清晰，结合初中数学知识推导公式，代码结构清晰，注释较完整。 |
| zjz2333 | 3星 | 思路较清晰，通过维护后缀和计算 $a$ 数组元素，但代码注释较少。 |
| _Anchor | 3星 | 借助数轴分析 $d$ 数组的性质，思路有一定创新性，但代码中自定义输入输出函数增加了复杂度。 |
| FutaRimeWoawaSete | 3星 | 思路简洁，直接指出关键性质和判断条件，但代码注释不足。 |
| fanfansann | 3星 | 从特殊到一般推导公式，考虑了卡常问题，但代码中使用 `unordered_map` 增加了空间复杂度。 |
| RyexAwl | 3星 | 通过差分和前缀和计算 $a$ 数组元素，思路较复杂，代码冗长。 |
| Meaninglessness | 3星 | 借助数轴分析规律，推导出递推公式，但代码未给出，仅提供链接。 |

### 高评分题解
- **胖头鱼学员（4星）**
  - **关键亮点**：结合初中数学知识 $|x - y| + |x + y| = 2 \cdot \max(|x|, |y|)$ 推导公式，思路清晰，代码结构清晰，注释较完整。
  - **个人心得**：无

### 重点代码（胖头鱼学员）
```cpp
# include <algorithm>
# include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;
long long T, n, d[kMaxN];

bool Check() {
  for (int i = 1; i <= n * 2; i += 2) {
    if (d[i] != d[i + 1]) {
      return 1;
    }
  }
  return 0;
}

string Solve() {
  scanf("%lld", &n);
  for (int i = 1; i <= n * 2; i++) {
    scanf("%lld", &d[i]);
  }
  sort(d + 1, d + 2 * n + 1);
  if (Check() == 1) {
    return "NO\n";
  }
  long long id = 2 * n, flag = 1, num = 2 * n, sum = 0, last = 0;
  while (id) {
    if ((d[id] - 2 * sum) % num != 0 || (d[id] - 2 * sum) / num <= 0) {
      return "NO\n";
    } else {
      if (last != 0 && last <= ((d[id] - 2 * sum) / num)) {
        return "NO\n";
      }
      last = ((d[id] - 2 * sum) / num);
      sum += ((d[id] - 2 * sum) / num), id -= 2, num -= 2;
    }
  }
  return "YES\n";
}

int main() {
  scanf("%lld", &T);
  while (T--) {
    cout << Solve();
  }
  return 0;
}
```
**核心实现思想**：先对 $d$ 数组排序，检查 $d$ 数组中元素是否成对相等。然后从最大的 $d$ 元素开始，利用递推公式计算可能的 $a$ 数组元素，检查计算过程中是否满足整除、正数、元素不重复等条件，若不满足则返回 `NO`，否则返回 `YES`。

### 最优关键思路或技巧
- **数学推导**：通过数学公式建立 $d$ 数组和 $a$ 数组之间的联系，利用对称数组的性质简化计算。
- **排序处理**：对 $d$ 数组排序，方便后续处理和判断元素是否成对相等。
- **合法性检查**：在计算 $a$ 数组元素的过程中，及时检查是否满足整数、正数、元素不重复等条件，避免无效计算。

### 可拓展之处
同类型题目可能会改变数组的性质或条件，如数组元素的范围、对称条件的变化等，但解题思路仍然是通过数学推导建立数组之间的联系，然后进行合法性检查。类似算法套路包括利用数学公式递推计算、排序处理和合法性检查等。

### 洛谷相似题目推荐
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：涉及数组操作和条件判断。
- [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)：需要对数组进行遍历和分析。
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及数组排序和去重。

### 个人心得摘录与总结
- **FutaRimeWoawaSete**：自己推的时候没上数轴，强行表达式法推错了一个性质。总结：在处理涉及绝对值和数组关系的问题时，借助数轴等工具可以更直观地分析问题，减少推导错误。

---
处理用时：62.09秒