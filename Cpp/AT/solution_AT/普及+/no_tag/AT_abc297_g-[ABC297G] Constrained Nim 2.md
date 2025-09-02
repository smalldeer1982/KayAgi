# [ABC297G] Constrained Nim 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc297/tasks/abc297_g

$ N $ 個の石の山があり、はじめ $ i $ 番目の山には石が $ A_i $ 個あります。これらの山を使って先手太郎君と後手次郎君でゲームをします。

先手太郎君と後手次郎君は、先手太郎君が先手で交互に以下の操作を行います。

- 石の山を一つ選び、そこから $ L $ 個以上 $ R $ 個以下の石を取り除く。

操作が行えなくなった方が負けで、負けなかった方が勝ちです。両者が勝ちを目指して最適な行動を取るとき、どちらが勝つか判定してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ L\ \leq\ R\ \leq\ 10^9 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

先手太郎君が最初に $ 1 $ 番目の山の石を $ 2 $ 個取り除くことで、必ず勝つことができます。

## 样例 #1

### 输入

```
3 1 2
2 3 3```

### 输出

```
First```

## 样例 #2

### 输入

```
5 1 1
3 1 4 1 5```

### 输出

```
Second```

## 样例 #3

### 输入

```
7 3 14
10 20 30 40 50 60 70```

### 输出

```
First```

# 题解

## 作者：User_Authorized (赞：5)

## 题意
有 $N$ 堆石子，其中第 $i$ 堆有 $A_i$ 个石子。每次可以选一堆从中取 $\left[L, R\right]$ 个，问判断先手后手胜负。

（$1 \le N \le 2 \times 10^5, 1 \le L \le R \le 10^9, 1 \le A_i \le 10^9$）。

## 题解
考虑子游戏，即只有一堆石子的情况，考虑其 $\operatorname{SG}$ 函数，首先给出结论

$$\operatorname{SG}(X) = \left\lfloor\dfrac{X \bmod \left(L + R\right)}{L}\right\rfloor$$

下面给出证明

### 若 $0 \le X < L + R$

- 如果 $0 \le X < L$，那么显然先手必输，此时 $\operatorname{SG}(X) = 0$；
- 如果 $L \le X < 2 \cdot L$，那么 $X < L + R \Rightarrow X - R < L$，所以此状态可以一步转移到所有 $Y \in \left[X - R, X - L\right)$ 的状态，包含的 $\operatorname{SG}$ 函数值集合为 $\left\{0\right\}$，此时 $\operatorname{SG}(X) = 1$；
- 如果 $2 \cdot L \le X < 3 \cdot L$，那么 $X < L + R \Rightarrow X - R < L$，所以此状态可以一步转移到所有 $Y \in \left[X - R, X - L\right)$ 的状态，包含的 $\operatorname{SG}$ 函数值集合为 $\left\{0, 1\right\}$，此时 $\operatorname{SG}(X) = 2$；
- 如果 $3 \cdot L \le X < 4 \cdot L$，那么 $X < L + R \Rightarrow X - R < L$，所以此状态可以一步转移到所有 $Y \in \left[X - R, X - L\right)$ 的状态，包含的 $\operatorname{SG}$ 函数值集合为 $\left\{0, 1, 2\right\}$，此时 $\operatorname{SG}(X) = 3$。

以此类推，可得 $\operatorname{SG}(X) = \left\lfloor\dfrac{X}{L}\right\rfloor$。

### 若 $L + R \le X < 2 \cdot \left(L + R\right)$

- 如果 $L + R \le X < L + R + L$，那么 $L + R \le X \Rightarrow X - R \ge L$，考虑到 $\operatorname{SG}(L) = 1$，所以此状态无法一步转移到 $\operatorname{SG} = 0$ 的情况，因此此状态 $\operatorname{SG}(X) = 0$；
- 如果 $L + R + L \le X < L + R + 2 \cdot L$，那么 $L + R + L \le X \Rightarrow X - R \ge 2 \cdot L$，所以该状态可以一步转移到的 $\operatorname{SG}$ 函数值集合为 $\left\{0, 2, 3, 4, 5, \cdots, \left\lfloor\dfrac{L + R}{L}\right\rfloor\right\}$，所以此状态 $\operatorname{SG}(X) = 1$。

同样的，对于所有 $L + R \le X < 2 \cdot \left(L + R\right)$，有 $\operatorname{SG}(X) = \left\lfloor\dfrac{X \bmod \left(L + R\right)}{L}\right\rfloor$。

### 若 $2 \cdot \left(L + R\right) \le X$

$\operatorname{SG}(X)$ 的值仅会从 $\operatorname{SG}(X - R), \operatorname{SG}(X - R + 1), \cdots, \operatorname{SG}(X - L)$ 中转移，类似于第二种情况，我们可以得出

$$\operatorname{SG}(X) = \left\lfloor\dfrac{X \bmod \left(L + R\right)}{L}\right\rfloor$$

## Code
```cpp
//AtCode - ABC297 - G
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType N, L, R;

    std::cin >> N >> L >> R;

    valueType SG = 0;

    for (valueType i = 0; i < N; ++i) {
        valueType A;

        std::cin >> A;

        SG ^= (A % (L + R)) / L;
    }

    if (SG > 0)
        std::cout << "First" << std::endl;
    else
        std::cout << "Second" << std::endl;

    return 0;
}
```

---

