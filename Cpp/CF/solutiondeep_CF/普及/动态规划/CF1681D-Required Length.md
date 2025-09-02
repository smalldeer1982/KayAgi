# 题目信息

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
4```

## 样例 #3

### 输入

```
13 42```

### 输出

```
12```

# AI分析结果

### 题目内容重写

给定两个整数 $n$ 和 $x$。你可以对 $x$ 进行多次操作，每次操作如下：选择 $x$ 的十进制表示中出现的任意一个数字 $y$，并将 $x$ 替换为 $x \cdot y$。你的目标是使 $x$ 的十进制表示的长度（不含前导零）等于 $n$。问最少需要多少次操作才能实现这一目标？

### 说明/提示

在第二个样例中，可以通过以下操作序列实现目标：

1. 将 $x$ 乘以 $2$，得到 $x = 2 \cdot 2 = 4$；
2. 将 $x$ 乘以 $4$，得到 $x = 4 \cdot 4 = 16$；
3. 将 $x$ 乘以 $6$，得到 $x = 16 \cdot 6 = 96$；
4. 将 $x$ 乘以 $9$，得到 $x = 96 \cdot 9 = 864$。

### 样例 #1

#### 输入

```
2 1
```

#### 输出

```
-1
```

### 样例 #2

#### 输入

```
3 2
```

#### 输出

```
4
```

### 样例 #3

#### 输入

```
13 42
```

#### 输出

```
12
```

---

### 题解分析与结论

本题的核心是通过广度优先搜索（BFS）或深度优先搜索（DFS）来找到最少的操作次数。由于直接暴力搜索会导致超时，因此需要引入剪枝策略或记忆化来优化搜索过程。以下是几条较为优秀的题解：

---

### 题解1：litachloveyou (★★★★★)

**关键亮点**：
- 使用BFS进行搜索，并引入剪枝策略。
- 通过计算当前数位与目标数位的差值，提前剪枝，避免无效搜索。
- 从高到低选择数字进行乘法操作，优先选择较大的数字以快速增加数位。

**核心代码**：
```cpp
void bfs(ll x,ll c) {
    if(n+c-leg(x)>=ans)return; // 最优情况剪枝
    if(leg(x)==n) {
        ans=c; // 更新答案
        que=true;
        return;
    }
    vector<int>a(10);
    ll k=x;
    while(k) {
        a[k%10]++;
        k=k/10;
    }
    for(int i=9;i>1;i--) { // 从9开始
        if(a[i]>=1) {
            bfs(x*i,c+1);
        }
    }
}
```

---

### 题解2：dbxxx (★★★★☆)

**关键亮点**：
- 使用BFS，并通过`set`进行记忆化，避免重复访问。
- 利用数学性质，将操作结果表示为 $x \times 2^a \times 3^b \times 5^c \times 7^d$，减少状态数。
- 通过计算目标数位的上下界，提前判断是否达到目标。

**核心代码**：
```cpp
while (!q.empty()) {
    int x = q.front().first, step = q.front().second;
    q.pop();
    if (x >= l) {
        printf("%llu\n", step);
        return 0;
    }
    std :: memset(hav, false, sizeof(hav));
    int t = x;
    while (t) {
        hav[t % 10] = true;
        t /= 10;
    }
    for (int i = 2; i <= 9; ++i) if (hav[i]) {
        if (vis.count(x * i)) continue;
        q.emplace(x * i, step + 1);
        vis.insert(x * i);
    }
}
```

---

### 题解3：CWzwz (★★★★☆)

**关键亮点**：
- 使用动态规划（DP）进行状态转移，将状态压缩为四维数组。
- 通过分解质因数，将操作结果表示为 $x \times 2^a \times 3^b \times 5^c \times 7^d$，减少状态数。
- 利用刷表法进行状态转移，避免重复计算。

**核心代码**：
```cpp
for(int a = 0; a < 64; a++) {
    for(int b = 0; b < 40; b++) {
        for(int c = 0; c < 28; c++) {
            for(int d = 0; d < 23; d++) {
                ll now = num(a, b, c, d);
                if(now == -1) break;  // 超出范围不管
                ll set = 0, tmp = now; 
                while(tmp) set |= (1 << (tmp % 10)), tmp /= 10; // 压 set_now
                for(int k = __builtin_ctz(set); set; set -= set & -set, k = __builtin_ctz(set)) { // 枚二进制位
                    if(k == 0 || k == 1) continue; 
                    if(now * k > max) break;
                    if(k == 2 || k == 3 || k == 5 || k == 7) {
                        f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)] = std::min(f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)], f[a][b][c][d] + 1);
                    } else if(k == 4) {
                        f[a + 2][b][c][d] = std::min(f[a + 2][b][c][d], f[a][b][c][d] + 1);
                    } else if(k == 6) {
                        f[a + 1][b + 1][c][d] = std::min(f[a + 1][b + 1][c][d], f[a][b][c][d] + 1);
                    } else if(k == 8) {
                        f[a + 3][b][c][d] = std::min(f[a + 3][b][c][d], f[a][b][c][d] + 1);
                    } else if(k == 9) {
                        f[a][b + 2][c][d] = std::min(f[a][b + 2][c][d], f[a][b][c][d] + 1);
                    } // 刷表 
                }
                if(now >= min) ans = std::min(ans, f[a][b][c][d]); 
            }
        }
    }
}
```

---

### 最优关键思路与技巧

1. **剪枝策略**：通过计算当前数位与目标数位的差值，提前剪枝，避免无效搜索。
2. **记忆化**：使用`set`或`map`进行记忆化，避免重复访问相同状态。
3. **状态压缩**：将操作结果表示为 $x \times 2^a \times 3^b \times 5^c \times 7^d$，减少状态数。
4. **优先选择较大数字**：从高到低选择数字进行乘法操作，优先选择较大的数字以快速增加数位。

---

### 拓展与举一反三

类似题目：
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

这些题目都涉及到搜索与剪枝策略，适合进一步练习相关技巧。

---
处理用时：54.94秒