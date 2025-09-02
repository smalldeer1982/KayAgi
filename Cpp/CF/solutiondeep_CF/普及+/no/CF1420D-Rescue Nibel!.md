# 题目信息

# Rescue Nibel!

## 题目描述

Ori and Sein have overcome many difficult challenges. They finally lit the Shrouded Lantern and found Gumon Seal, the key to the Forlorn Ruins. When they tried to open the door to the ruins... nothing happened.

Ori was very surprised, but Sein gave the explanation quickly: clever Gumon decided to make an additional defence for the door.

There are $ n $ lamps with Spirit Tree's light. Sein knows the time of turning on and off for the $ i $ -th lamp — $ l_i $ and $ r_i $ respectively. To open the door you have to choose $ k $ lamps in such a way that there will be a moment of time when they all will be turned on.

While Sein decides which of the $ k $ lamps to pick, Ori is interested: how many ways there are to pick such $ k $ lamps that the door will open? It may happen that Sein may be wrong and there are no such $ k $ lamps. The answer might be large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

In first test case there are nine sets of $ k $ lamps: $ (1, 2, 3) $ , $ (1, 2, 4) $ , $ (1, 2, 5) $ , $ (1, 2, 6) $ , $ (1, 3, 6) $ , $ (1, 4, 6) $ , $ (2, 3, 6) $ , $ (2, 4, 6) $ , $ (2, 6, 7) $ .

In second test case $ k=1 $ , so the answer is 3.

In third test case there are no such pairs of lamps.

In forth test case all lamps are turned on in a time $ 3 $ , so the answer is 1.

In fifth test case there are seven sets of $ k $ lamps: $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , $ (4, 5) $ .

## 样例 #1

### 输入

```
7 3
1 7
3 8
4 5
6 7
1 3
5 10
8 9```

### 输出

```
9```

## 样例 #2

### 输入

```
3 1
1 1
2 2
3 3```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2
1 1
2 2
3 3```

### 输出

```
0```

## 样例 #4

### 输入

```
3 3
1 3
2 3
3 3```

### 输出

```
1```

## 样例 #5

### 输入

```
5 2
1 3
2 4
3 5
4 6
5 7```

### 输出

```
7```

# AI分析结果

### 题目翻译
# 拯救尼贝尔！

## 题目描述
奥里（Ori）和塞恩（Sein）克服了许多艰难的挑战。他们终于点亮了幽影灯笼，找到了古蒙封印，这是通往失落遗迹的钥匙。当他们试图打开遗迹的门时……什么都没发生。

奥里非常惊讶，但塞恩很快给出了解释：聪明的古蒙决定为这扇门增加一道额外的防御。

有 $n$ 盏带有灵树之光的灯。塞恩知道第 $i$ 盏灯的点亮和熄灭时间，分别为 $l_i$ 和 $r_i$。要打开这扇门，你必须选择 $k$ 盏灯，使得存在一个时刻，这 $k$ 盏灯都处于点亮状态。

当塞恩在决定选择哪 $k$ 盏灯时，奥里好奇地想知道：有多少种选择 $k$ 盏灯的方法可以打开这扇门？可能会出现塞恩判断错误，不存在这样的 $k$ 盏灯的情况。答案可能很大，所以请将结果对 $998\,244\,353$ 取模。

## 说明/提示
在第一个测试用例中，有九组 $k$ 盏灯的组合：$(1, 2, 3)$、$(1, 2, 4)$、$(1, 2, 5)$、$(1, 2, 6)$、$(1, 3, 6)$、$(1, 4, 6)$、$(2, 3, 6)$、$(2, 4, 6)$、$(2, 6, 7)$。

在第二个测试用例中，$k = 1$，所以答案是 3。

在第三个测试用例中，不存在这样的灯对。

在第四个测试用例中，所有灯都在时刻 3 点亮，所以答案是 1。

在第五个测试用例中，有七组 $k$ 盏灯的组合：$(1, 2)$、$(1, 3)$、$(2, 3)$、$(2, 4)$、$(3, 4)$、$(3, 5)$、$(4, 5)$。

## 样例 #1
### 输入
```
7 3
1 7
3 8
4 5
6 7
1 3
5 10
8 9
```
### 输出
```
9
```

## 样例 #2
### 输入
```
3 1
1 1
2 2
3 3
```
### 输出
```
3
```

## 样例 #3
### 输入
```
3 2
1 1
2 2
3 3
```
### 输出
```
0
```

## 样例 #4
### 输入
```
3 3
1 3
2 3
3 3
```
### 输出
```
1
```

## 样例 #5
### 输入
```
5 2
1 3
2 4
3 5
4 6
5 7
```
### 输出
```
7
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是围绕从 $n$ 条线段中选出 $k$ 条使其交集不为空的方案数展开。主要的算法要点包括排序、离散化、组合数计算，部分题解使用了树状数组、堆等数据结构来优化计算过程。

不同题解的差异在于实现细节和思路的切入点。有的题解通过枚举线段，利用树状数组维护与当前线段有交集的线段数量；有的题解将区间拆分为左右端点操作，扫描过程中统计贡献；还有的题解通过容斥原理来避免重复计算。

### 所选题解
- **tommymio（4星）**
  - **关键亮点**：思路清晰，先对线段按左端点排序，然后对于每条线段计算与其有交集的线段数量，利用树状数组高效维护，最后通过组合数计算方案数。
  - **个人心得**：作者提到打 Div2 时比 C2 先开了这题，自嘲自己太菜。
- **Karry5307（4星）**
  - **关键亮点**：将问题转化为枚举相交线段的左端点，利用容斥原理计算每个位置的方案数，通过开桶的方式实现，代码实现较为巧妙。
  - **个人心得**：提到本题是某题的弱化版，还调侃了一句“所以 Rikka 可爱你们说对不对啊”。
- **STDquantum（4星）**
  - **关键亮点**：将区间拆成左右端点操作，按横坐标排序，扫描过程中统计贡献，避免了离散化，思路简洁，复杂度为 $O(n\log n)$。
  - **个人心得**：感谢 `WanKupi` 大佬。

### 重点代码
#### tommymio
```cpp
// 按左端点排序
inline bool cmp(const Segment &x, const Segment &y) { return x.l != y.l ? x.l < y.l : x.r < y.r; }
// 树状数组更新
inline void add(int x) { for (; x <= num; x += x & (-x)) ++sum[x]; }
// 树状数组查询
inline int ask(int x) { int res = 0; for (; x; x -= x & (-x)) res += sum[x]; return res; } 
// 计算组合数
inline int binom(int n, int m) { return fac[n] * inv[n - m] % mod * inv[m] % mod; }
// 主函数部分
for(register int i = 1; i <= n; ++i) {
    seg[i].l = std::lower_bound(c + 1, c + 1 + num, seg[i].l) - c;
    seg[i].r = std::lower_bound(c + 1, c + 1 + num, seg[i].r) - c;
    int cnt = ask(num) - ask(seg[i].l - 1); add(seg[i].r);
    if (cnt >= k - 1) ans = (ans + binom(cnt, k - 1)) % mod;
}
```
**核心实现思想**：先对线段按左端点排序，对于每条线段，通过树状数组查询有多少条前面的线段的右端点大于等于当前线段的左端点，即与当前线段有交集的线段数量，然后利用组合数计算方案数。

#### Karry5307
```cpp
// 计算组合数
inline ll binom(ll m, ll n) {
    if (m < 0 || n < 0 || m < n) {
        return 0;
    }
    return (li)fact[m] * finv[n] % MOD * finv[m - n] % MOD;
}
// 主函数部分
for(register int i = 1; i <= tot; i++) {
    lst = sm, sm += cntl[i] - cntr[i];
    res = ((li)res + binom(sm, kk) - binom(lst - cntr[i], kk) + MOD) % MOD;
}
```
**核心实现思想**：枚举相交线段的左端点，用 $p$ 表示覆盖该位置的线段数量，$s$ 表示以该位置为左端点的线段数量，利用容斥原理 $\binom{p}{k}-\binom{p - s}{k}$ 计算每个位置的方案数。

#### STDquantum
```cpp
// 定义操作结构体
struct E {
    int x, sgn;
    E(int X = 0, int Sgn = 0) { x = X, sgn = Sgn; }
    inline friend bool operator<(const E &a, const E &b) {
        return a.x == b.x ? a.sgn < b.sgn : a.x < b.x; // 减操作排前面
    }
};
// 计算组合数
inline int C(int n, int m) {
    if (m > n || m < 0 || n < 0) return 0;
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
// 主函数部分
sort(a + 1, a + 2 * n + 1);
int tmp = 0; // 即为题解中的g
for (int i = 1; i <= 2 * n; ++i) {
    if (a[i].sgn == -1) { // 先减后加
        --tmp;
    } else {
        ++tmp;
        (ans += C(tmp, k) - C(tmp - 1, k) + mod) %= mod; // 统计贡献
    }
}
```
**核心实现思想**：将区间拆成左右端点操作，按横坐标排序，扫描过程中统计当前点在多少个区间内，通过组合数的差值计算每个加操作对答案的贡献。

### 最优关键思路或技巧
- **排序与离散化**：对线段按左端点排序可以方便后续的计算，离散化可以将大范围的坐标映射到较小的范围，减少空间复杂度。
- **区间拆分与扫描线**：将区间拆分为左右端点操作，通过扫描线的方式可以高效地统计每个点的区间覆盖情况。
- **容斥原理**：在计算方案数时，利用容斥原理可以避免重复计算。

### 拓展思路
同类型题或类似算法套路：
- 区间覆盖问题：给定多个区间，求满足某种覆盖条件的方案数或最优解。
- 扫描线算法：在处理区间相关问题时，扫描线算法可以将二维问题转化为一维问题，提高计算效率。

### 推荐题目
- [P1904 天际线](https://www.luogu.com.cn/problem/P1904)
- [P2062 分块乘法的烦恼](https://www.luogu.com.cn/problem/P2062)
- [P2577 午餐](https://www.luogu.com.cn/problem/P2577)

### 个人心得总结
- tommymio 提到做题时的状态，反映出比赛时的做题节奏和自我认知。
- Karry5307 的调侃体现出做题时轻松的心态。
- STDquantum 感谢大佬，说明在学习过程中借鉴他人思路的重要性。

---
处理用时：66.66秒