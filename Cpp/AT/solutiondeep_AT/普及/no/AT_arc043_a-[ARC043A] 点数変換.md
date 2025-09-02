# 题目信息

# [ARC043A] 点数変換

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc043/tasks/arc043_a

$ N $ 人がテストを受けた。$ i $ 番目の人の得点は $ S_i $ である。

得点に偏りがあったので、平均が $ A $、最大値と最小値の差が $ B $ となるように得点を変換したい。

得点の変換は適切な実数 $ P,\ Q $ を選んで行う。$ i $ 番目の人の変換後の得点は $ P×S_i\ +\ Q $である。

適切な $ P,Q $ があるかどうか判断し、もしあるならばそれを出力せよ。

## 说明/提示

### Sample Explanation 1

$ P\ =\ 0.5,\ Q=-1 $とすると得点は順に $ 0,\ 1,\ 2,\ 3,\ 4 $ となり平均が $ 2 $, 最大値と最小値の差が $ 4 $になる。

## 样例 #1

### 输入

```
5 2 4

2

4

6

8

10```

### 输出

```
0.5 -1```

## 样例 #2

### 输入

```
13 29 31

3

1

4

1

5

9

2

6

5

3

5

8

9```

### 输出

```
3.875 10.8173076```

## 样例 #3

### 输入

```
5 1 2

34

34

34

34

34```

### 输出

```
-1```

# AI分析结果



# [ARC043A] 点数変換

## 题目描述

$ N $ 人参加了一次测试。第 $ i $ 个人的原始得分为 $ S_i $。现希望通过线性变换 $ P \times S_i + Q $ 调整分数，使得调整后的平均分为 $ A $，且最高分与最低分之差为 $ B $。判断是否存在满足条件的 $ P $ 和 $ Q $，若存在则输出。

**算法分类**：数学

---

### 题解分析与结论

**核心思路**：  
1. **极差处理**：通过原始分数的极差（最大与最小值差）确定缩放比例 $ P $。当原始极差为 $ D $ 时，$ P = B / D $。
2. **均值调整**：利用调整后的均值约束 $ Q = A - P \times \text{原平均分} $。
3. **特判处理**：当原始数据全相同且 $ B \neq 0 $，或要求极差 $ B $ 为负数时，无解。

**关键步骤**：
1. 计算原始最大值、最小值、总和。
2. 若最大值等于最小值：
   - $ B \neq 0 $：无解。
   - $ B = 0 $：任意 $ P $ 均可，取 $ Q = A - P \times \text{平均分}$。
3. 否则，当 $ B \geq 0 $ 时，计算 $ P $ 和 $ Q $；若 $ B < 0 $，无解。

**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    double A, B;
    cin >> N >> A >> B;
    vector<double> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    
    double max_S = *max_element(S.begin(), S.end());
    double min_S = *min_element(S.begin(), S.end());
    double sum_S = accumulate(S.begin(), S.end(), 0.0);
    
    if (max_S == min_S) {
        if (B != 0) cout << -1 << endl;
        else cout << fixed << setprecision(10) << 0.0 << ' ' << A << endl;
    } else {
        if (B < 0) cout << -1 << endl;
        else {
            double D = max_S - min_S;
            double P = B / D;
            double Q = A - P * (sum_S / N);
            cout << fixed << setprecision(10) << P << ' ' << Q << endl;
        }
    }
    return 0;
}
```

**优化技巧**：
- **极差直接计算**：无需遍历所有差值，直接通过最大最小值确定。
- **浮点精度处理**：使用 `fixed` 和 `setprecision` 保证输出精度。

**拓展题目**：
1. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024) - 数学方程的数值解。
2. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055) - 数值转换与验证。
3. [P2181 对角线](https://www.luogu.com.cn/problem/P2181) - 数学公式推导。

---
处理用时：279.41秒