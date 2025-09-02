# 题目信息

# Boboniu and Bit Operations

## 题目描述

Boboniu likes bit operations. He wants to play a game with you.

Boboniu gives you two sequences of non-negative integers $ a_1,a_2,\ldots,a_n $ and $ b_1,b_2,\ldots,b_m $ .

For each $ i $ ( $ 1\le i\le n $ ), you're asked to choose a $ j $ ( $ 1\le j\le m $ ) and let $ c_i=a_i\& b_j $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). Note that you can pick the same $ j $ for different $ i $ 's.

Find the minimum possible $ c_1 | c_2 | \ldots | c_n $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

## 说明/提示

For the first example, we have $ c_1=a_1\& b_2=0 $ , $ c_2=a_2\& b_1=2 $ , $ c_3=a_3\& b_1=0 $ , $ c_4 =       a_4\& b_1=0 $ .Thus $ c_1 | c_2 | c_3 |c_4 =2 $ , and this is the minimal answer we can get.

## 样例 #1

### 输入

```
4 2
2 6 4 0
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4```

### 输出

```
0```

## 样例 #3

### 输入

```
8 5
179 261 432 162 82 43 10 38
379 357 202 184 197```

### 输出

```
147```

# AI分析结果

### 题目翻译
# Boboniu和位运算

## 题目描述
Boboniu喜欢位运算。他想和你玩一个游戏。

Boboniu给你两个非负整数序列 $ a_1,a_2,\ldots,a_n $ 和 $ b_1,b_2,\ldots,b_m $ 。

对于每个 $ i $（ $ 1\le i\le n $ ），你需要选择一个 $ j $（ $ 1\le j\le m $ ），并令 $ c_i=a_i\& b_j $ ，其中 $ \& $ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。注意，你可以为不同的 $ i $ 选择相同的 $ j $ 。

求 $ c_1 | c_2 | \ldots | c_n $ 的最小可能值，其中 $ | $ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

## 说明/提示
对于第一个样例，我们有 $ c_1=a_1\& b_2=0 $ ， $ c_2=a_2\& b_1=2 $ ， $ c_3=a_3\& b_1=0 $ ， $ c_4 = a_4\& b_1=0 $ 。因此 $ c_1 | c_2 | c_3 |c_4 =2 $ ，这就是我们能得到的最小答案。

## 样例 #1
### 输入
```
4 2
2 6 4 0
2 4
```
### 输出
```
2
```

## 样例 #2
### 输入
```
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4
```
### 输出
```
0
```

## 样例 #3
### 输入
```
8 5
179 261 432 162 82 43 10 38
379 357 202 184 197
```
### 输出
```
147
```

### 算法分类
位运算

### 综合分析与结论
这些题解主要围绕如何找出 $ c_1 | c_2 | \ldots | c_n $ 的最小值展开，采用了不同的算法思路。
- **动态规划思路**：通过定义状态 $ f(i,x) $ 表示是否存在一组 $ c $ 满足 $ c_1\operatorname{or}c_2\operatorname{or}...\operatorname{or}c_i=x $ ，然后进行状态转移求解。
- **枚举思路**：直接枚举答案，然后检查答案的可用性。
- **贪心思路**：从答案的二进制高位到低位进行贪心，尽可能让高位为 $ 0 $ 。
- **搜索思路**：通过深度优先搜索遍历所有可能的组合，同时使用记忆化搜索优化。

### 所选题解
- **KellyFrog（5星）**
    - **关键亮点**：思路清晰，使用动态规划的方法解决问题，代码实现简洁明了，复杂度分析准确。
- **5G信号塔报装（4星）**
    - **关键亮点**：指出洛谷题目翻译有误，采用枚举答案并验证的方法，思路简单直接，代码可读性高。
- **Theophania（4星）**
    - **关键亮点**：根据数据范围直接进行暴力枚举，代码中使用了快速读入优化。

### 重点代码
#### KellyFrog的动态规划代码
```cpp
#include <iostream>

using namespace std;

const int MAXN = 205;
const int MAXM = 205;
const int MAXA = (1 << 9) + 5;

int a[MAXN], b[MAXM];
bool f[MAXN][MAXA];

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    f[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x = a[i] & b[j];
            for(int k = 0; k < (1 << 9); k++) {
                f[i][k | x] |= f[i - 1][k];
            }
        }
    }
    for(int i = 0; i < (1 << 9); i++) {
        if(f[n][i]) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
```
**核心实现思想**：定义状态 $ f(i,x) $ ，初始状态 $ f(0,0)=1 $ ，然后通过三重循环进行状态转移，最后找到最小的满足 $ f(n,i)=1 $ 的 $ i $ 即为答案。

#### 5G信号塔报装的枚举代码
```cpp
# include <bits/stdc++.h>
using namespace std;

int n, m, a[100005], b[100005];

bool ojbk(int x) { //check
    for (int i = 1; i <= n; i++) {
        bool flg= false;
        for (int j = 1; j <= m; j++)
            if (((a[i] & b[j]) | x) == x) {
                flg = true; break; 
            }
        if (!flg) return false;
    }
    return true;
}

signed main() {
    puts("5G 赋能未来 | by 5G信号塔报装(三网线路检修员)");
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]); 
    for (int i = 0; i <= 512; i++)
        if (ojbk(i)) { cout << i << endl; break; }
    return 0;
}
```
**核心实现思想**：定义检查函数 `ojbk` 来验证答案 $ x $ 的可用性，然后从 $ 0 $ 到 $ 512 $ 枚举答案，找到第一个可用的答案即为最小答案。

#### Theophania的暴力枚举代码
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}

int a[201], b[201];
signed main()
{
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= m; ++i)
        read(b[i]);
    bool flag;
    int cnt;
    for (int ans = 0; ans < 512; ++ans)
    {
        cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            flag = false;
            for (int j = 1; j <= m; ++j)
                if ((a[i] & b[j] | ans) == ans)
                {
                    flag = true;
                    break;
                }
            if (flag)
                cnt++;
            else
                break;
        }
        if (cnt == n)
        {
            cout << ans << endl;
            return 0;
        }
    }
    return 0;
}
```
**核心实现思想**：从 $ 0 $ 到 $ 512 $ 枚举答案，对于每个答案，检查是否对于每个 $ a_i $ 都能找到一个 $ b_j $ 使得 $ a_i \& b_j | ans=ans $ ，如果满足则输出该答案。

### 最优关键思路或技巧
- 利用位运算的性质，如按位与和按位或的特点来进行状态转移或答案验证。
- 结合数据范围进行优化，如枚举答案的范围限制在 $ 0\sim512 $ 。
- 使用记忆化搜索或动态规划来避免重复计算。

### 拓展思路
同类型题或类似算法套路：
- 涉及位运算的其他优化问题，如位运算的状态压缩动态规划。
- 贪心与位运算结合的问题，通过对二进制位的贪心选择来求解最优解。
- 搜索与位运算结合的问题，在搜索过程中利用位运算进行剪枝。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P2058 海港](https://www.luogu.com.cn/problem/P2058)

### 个人心得摘录与总结
- **5G信号塔报装**：过度压行导致不明错误，提醒我们在编码时要注意代码的可读性，避免因过度追求简洁而引入难以调试的问题。

---
处理用时：55.44秒