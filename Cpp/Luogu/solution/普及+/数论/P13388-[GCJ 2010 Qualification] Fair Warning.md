# [GCJ 2010 Qualification] Fair Warning

## 题目描述

在我们的星球 Jamcode IX 上，曾经发生过三次伟大的事件。它们分别发生在 $26000$、$11000$ 和 $6000$ 个 slarbosecond 之前。再过 $4000$ 个 slarbosecond，从这些事件到那时的时间都将是 $5000$ 的倍数，这是可能的最大倍数……而世界末日也将在那时到来。

幸运的是，你现在生活在 Jamcode X！Jamcode IX 的世界末日发生在不到一年前。但 Jamcode X 有一个令人担忧的预言：“在清算时刻之后，在 $N$ 个伟大事件的第一个最优周年纪念日，世界末日将会到来。64 位整数也无法拯救你。你已被警告。”

Jamcode X 的人们非常担心这个预言。所有伟大事件都已经发生，并且它们的时间都被精确测量到了最近的 slarbosecond；但没有人知道它们的最优周年纪念日会在什么时候。科学家们在研究了 Jamcode IX 一位科学家的日记后，提出了一个理论：

清算时刻就是现在，也就是你正在解决这个问题的时刻。在某个距离现在 $y \geqslant 0$ 个 slarbosecond 的时刻，从每个伟大事件到那时的时间都将能被某个最大整数 $T$ 整除。如果你能找到使这个最大 $T$ 成立的最小 $y$，那么这个 $y$ 就是世界末日到来的最优周年纪念日。

例如，在 Jamcode IX 上，有 3 个伟大事件，分别发生在 $26000$、$11000$ 和 $6000$ 个 slarbosecond 之前。再过 $4000$ 个 slarbosecond，每个事件到那时的时间都是 $T=5000$ 的倍数，于是世界末日到来了。

你的任务是计算距离世界末日还有多少时间。但请记住预言：尽管 Jamcode X 的人们已经解决问题两年了，并且 64 位整数一直都足够，但现在或将来可能就不够用了。

## 说明/提示

**数据范围**

- $1 \leqslant C \leqslant 100$。
- 存在某些 $i, j$ 使得 $t_{i} \neq t_{j}$。

**小数据集（10 分，测试集 1 - 可见）**

- $2 \leqslant N \leqslant 3$。
- $1 \leqslant t_{i} \leqslant 10^{8}$。

**大数据集（23 分，测试集 2 - 隐藏）**

- $2 \leqslant N \leqslant 1000$。
- $1 \leqslant t_{i} \leqslant 10^{50}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 26000000 11000000 6000000
3 1 10 11
2 800000000000000000001 900000000000000000001```

### 输出

```
Case #1: 4000000
Case #2: 0
Case #3: 99999999999999999999```

# 题解

## 作者：Mike_666 (赞：1)

#### 解题思路

+ 观察：记 $\gcd(a_i+y,a_2+y,\cdots,a_n+y)=g_y$，则 $g_y\mid(a_i-a_j),1\leq i,j\leq n$。

+ 所以，答案最大为 $g=\gcd\limits_{1\leq i,j\leq n\land i\neq j}(a_i-a_j)$。

+ 想要答案达到最大，发现 $a_i\equiv t\pmod g,1\leq i\leq n$，则让所有数加上 $-t\bmod g$ 即可。

+ 快速计算 $g$：直接算 $g=\gcd\limits_{1\leq i\leq n-1}(a_{i+1}-a_i)$。

#### 代码实现

+ 需要实现高精度，`c++` 高精度 $\gcd$ 写了很久还没写出来，于是使用 `Python`。

::::success[代码]
```python
import sys, math

def main():
    data = list(map(int, sys.stdin.read().split()))
    ptr = 0
    T = data[ptr]
    ptr += 1
    for case in range(1, T+1):
        n = data[ptr]
        ptr += 1
        g = 0
        l = 0
        for i in range(n):
            a = data[ptr]
            ptr += 1
            if i > 0:
                d = a - l
                g = math.gcd(g, d)
            l = a
        if g < 0:
            g = -g
        if g == 0:
            res = 0
        else:
            res = ((-a) % g + g) % g
        print(f"Case #{case}: {res}")

if __name__ == "__main__":
    main()
```
::::

---

