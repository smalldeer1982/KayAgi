# 题目信息

# 〈 TREEのOI 2022 Spring 〉Counting By Ternary

## 题目背景

黑土地上，一棵小苗破土而出。

几个月里，它吮吸着甘甜的雨露，享受着温暖的阳光，愈发翠绿了起来。

![](https://cdn.pixabay.com/photo/2019/03/05/12/52/plant-4036131_960_720.jpg)

它越长越高，越长越壮，似乎要突破云霄。

它长成了一棵大树，渴望着去天空中，看一看这美丽的世界。

![](https://cdn.pixabay.com/photo/2015/02/24/15/41/wolf-647528_960_720.jpg)

## 题目描述

**请留意本题并不寻常的时空限制。**

给定一个数 $x$，用如下规则建立一棵有根树：

- 根节点为 $\lang0,x\rang$。  

- 对于一个节点 $\lang i,j\rang$，若 $j < 3$，则它是叶子节点，否则它的子节点为对于任意 $1 \le k$ 且 $j$ 的位数 $\ge k$， $\lang j_k, k\rang$，其中 $j_k$ 为它三进制表示从左向右的第 $k$ 位。  

求这棵树的叶子节点的数目。

## 说明/提示



**本题采用 SubTask 捆绑测试。**

| SubTask 编号 | 分值 | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $10$ | $p\le 3^{15}$，$q=1$ |
| $1$ | $10$ | $p\le 3^{35}$，$q=1$ |
| $2$ | $20$ | $p=3$，$q\le 3^{15}$ |
| $3$ | $60$ | $p=3$，$q\le 3^{35}$ |


对于 $100\%$ 的数据，$p^q \le 3^{3^{35}}$（$10^{10^9} \lt 3^{3^{35} } \lt 10^{2.5 \times 10^9}$），保证 $p = 3^l(l\in \mathbb N^+)$。 


## 样例 #1

### 输入

```
9 1```

### 输出

```
4```

## 样例 #2

### 输入

```
27 1```

### 输出

```
6```

# AI分析结果

### 综合分析与结论

本题的核心在于通过三进制分解构建树结构，并计算叶子节点的数量。题解的关键点在于如何高效地计算叶子节点的数量，尤其是在面对极大输入规模时（如 $p^q \le 3^{3^{35}}$）。两位作者都提出了递推公式，并通过优化将时间复杂度从 $O(\log_3{p^q})$ 降低到 $O(\log_3 \log_3 p^q)$，从而解决了问题。

### 所选题解

#### 题解1：过氧化氢_syq0057 (4星)
- **关键亮点**：
  - 通过观察发现 $f_i$ 的值在 $3^{i-1}$ 到 $3^i-1$ 之间是相同的，从而引入 $g_i$ 来优化计算。
  - 通过递推公式 $g_i = \sum_{j=1}^i f_j$ 和 $ans = \sum_{j=1}^{\lfloor \log_3i \rfloor +1} g_j \times (3^j-3^{j-1})$ 高效计算叶子节点数量。
  - 代码结构清晰，优化思路明确。

- **核心代码**：
```cpp
ll Log3(ll s) {
    ll res = 0;
    while (s) {
        s /= 3;
        res++;
    }
    return res - 1;
}

ll ksm(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}

int main() {
    scanf("%lld%lld", &p, &q);
    ll x = q * Log3(p) + 1;
    ll log3x = Log3(q * Log3(p)) + 1;
    f[1] = 1, f[2] = 1;
    for (int i=3; i<=100; i++)
        for (int j=1; j<=Log3(i)+1; j++)
            f[i] += f[j];
    g[1] = 1, g[2] = 2;
    for (ll i=3; i<=log3x; i++)
        for (int j=1; j<=i; j++)
            g[i] += f[j];
    for (int i=1; i<=log3x; i++) {
        if (i == log3x) ans += (x - ksm(3, i - 1) + 1) * g[i];
        else ans += (ksm(3, i) - ksm(3, i - 1)) * g[i];
    }
    printf("%lld\n", ans);
    return 0;
}
```

#### 题解2：Galois_Field_1048576 (4星)
- **关键亮点**：
  - 通过定义 $g$ 为 $f$ 的前缀和，进一步优化了递推公式。
  - 使用 $g_x = \sum_{i = 1}^{\lfloor\log_3x\rfloor} (3^{i} - 3^{i-1}) g_i + Ext$ 来计算叶子节点数量，其中 $Ext$ 处理了边界情况。
  - 代码实现简洁，优化思路清晰。

- **核心代码**：
```cpp
int log3(int mx) {
    return log(mx) / log(3) + eps;
}

int power(int base, int freq) {
    int ans = 1, tmp = base;
    while (freq > 0) {
        if (freq % 2 == 1)
            ans = ans * tmp;
        freq /= 2;
        tmp = tmp * tmp;
    }
    return ans;
}

void generate() {
    log3pq = q * log3(p) + 1;
    log3log3pq = log3(log3pq);
    g[1] = 1;
    g[2] = 2;
    for (int x = 3; x <= log3(log3pq) + 1; x++) {
        ext = (x - power(3, log3(x)) + 1) * g[(int)log3(x) + 1];
        g[x] += ext;
        for (int i = 1; i <= log3(x); i++) {
            g[x] += (power(3, i) - power(3, i - 1)) * g[i];
        }
    }
}

int getans() {
    ext = (log3pq - power(3, log3log3pq) + 1) * g[(int)log3log3pq + 1];
    ans = 0;
    for (int i = 1; i <= log3(log3pq); i++) {
        ans += (power(3, i) - power(3, i - 1)) * g[i];
    }
    return ans + ext;
}
```

### 最优关键思路或技巧

1. **递推公式优化**：通过观察 $f_i$ 的值在 $3^{i-1}$ 到 $3^i-1$ 之间是相同的，引入 $g_i$ 来优化计算。
2. **前缀和的应用**：通过定义 $g$ 为 $f$ 的前缀和，进一步简化了递推公式的计算。
3. **边界处理**：通过 $Ext$ 处理边界情况，确保计算的准确性。

### 可拓展之处

类似的问题可以通过观察数值规律，引入辅助数组或变量来优化递推公式的计算。这种思路在处理大规模数据时尤为有效。

### 推荐题目

1. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 考察递推与栈的应用。
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028) - 考察递推与数论结合。
3. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075) - 考察数论与递推的结合。

### 个人心得

两位作者都通过观察数值规律，成功优化了递推公式，并处理了边界情况。这种通过观察规律来优化算法的思路在处理复杂问题时非常有效。

---
处理用时：40.23秒