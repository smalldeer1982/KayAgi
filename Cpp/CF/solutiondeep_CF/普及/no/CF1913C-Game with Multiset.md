# 题目信息

# Game with Multiset

## 题目描述

In this problem, you are initially given an empty multiset. You have to process two types of queries:

1. ADD $ x $ — add an element equal to $ 2^{x} $ to the multiset;
2. GET $ w $ — say whether it is possible to take the sum of some subset of the current multiset and get a value equal to $ w $ .

## 样例 #1

### 输入

```
5
1 0
1 0
1 0
2 3
2 4```

### 输出

```
YES
NO```

## 样例 #2

### 输入

```
7
1 0
1 1
1 2
1 10
2 4
2 6
2 7```

### 输出

```
YES
YES
YES```

# AI分析结果



# Game with Multiset

## 题目描述

你有一个空的多重集，需要处理两种操作：

1. **ADD x**：将元素 $2^x$ 添加到多重集；
2. **GET w**：判断是否存在一个子集，其元素之和等于 $w$。

**样例 #1 输入**  
```
5
1 0
1 0
1 0
2 3
2 4
```

**样例 #1 输出**  
```
YES
NO
```

## 算法分类
贪心、进制处理

---

## 题解分析与结论

### 核心思路对比
1. **高位到低位贪心**：从最大二进制位开始，用二分法确定每个位最多能取多少元素。时间复杂度 $O(30 \log c)$。
2. **进位模拟法**：从低位到高位处理，维护 `sum` 变量表示可用元素总数，处理进位。时间复杂度 $O(30)$，最优解。

### 最优题解

#### [作者：yyrwlj] ⭐⭐⭐⭐⭐
**关键亮点**：  
- 维护 `sum` 变量表示当前可用元素总数，逐位处理并自动进位。
- 无需复制数组或使用二分，时间复杂度稳定 $O(30)$。
- 代码简洁高效，完美利用二进制特性。

**核心代码**：
```cpp
void get(int x) {
    int sum = 0;
    for (int i = 0; i <= 30; i++) {
        sum += S[i];           // 累加当前位的元素数量
        if (x >> i & 1) {      // 检查该位是否需要1
            if (!sum) {        // 无法满足直接返回NO
                puts("NO");
                return;
            }
            sum--;             // 消耗一个元素
        }
        sum >>= 1;             // 进位到高位
    }
    puts("YES");
}
```

#### [作者：harmis_yz] ⭐⭐⭐⭐⭐
**关键亮点**：  
- 与 yyrwlj 思路一致，但代码更精简。
- 通过逐位累加和进位处理，直接判断可行性。

**核心代码**：
```cpp
il void solve() {
    // ...
    for (re int i=1, op, x; i<=n; ++i) {
        cin >> op >> x;
        if (op == 1) ++cnt[x];
        else {
            int len = 0, sum = 0;
            while (x) {
                int k = x % 2;
                sum = sum / 2 + cnt[len];  // 进位处理
                if (sum < k) goto no;       // 无法满足
                sum -= k;                  // 消耗当前位
                x /= 2; len++;
            }
            cout << "YES\n"; continue;
          no: cout << "NO\n";
        }
    }
}
```

---

## 关键思路总结
1. **二进制特性利用**：所有元素为 $2^x$，转化为二进制位处理。
2. **进位模拟**：维护 `sum` 变量，处理低位的剩余元素自动进位到高位。
3. **贪心顺序**：从低位到高位处理，保证进位后高位元素足够。

---

## 拓展与相似题目
1. **二进制拆分问题**：如多重背包的二进制优化（洛谷 P1776）。
2. **进位思维应用**：类似大数加法、高精度运算中的进位处理。
3. **推荐题目**：  
   - [P7072 直播获奖](https://www.luogu.com.cn/problem/P7072)（桶排序+进位思想）  
   - [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)（二进制优化背包）  
   - [P2320 鬼谷子的钱袋](https://www.luogu.com.cn/problem/P2320)（二进制拆分构造）

---
处理用时：106.86秒