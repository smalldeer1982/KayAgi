# 题目信息

# Fixing a Binary String

## 题目描述

You are given a binary string $ s $ of length $ n $ , consisting of zeros and ones. You can perform the following operation exactly once:

1. Choose an integer $ p $ ( $ 1 \le p \le n $ ).
2. Reverse the substring $ s_1 s_2 \ldots s_p $ . After this step, the string $ s_1 s_2 \ldots s_n $ will become $ s_p s_{p-1} \ldots s_1 s_{p+1} s_{p+2} \ldots s_n $ .
3. Then, perform a cyclic shift of the string $ s $ to the left $ p $ times. After this step, the initial string $ s_1s_2 \ldots s_n $ will become $ s_{p+1}s_{p+2} \ldots s_n s_p s_{p-1} \ldots s_1 $ .

For example, if you apply the operation to the string 110001100110 with $ p=3 $ , after the second step, the string will become 011001100110, and after the third step, it will become 001100110011.

A string $ s $ is called  $ k $ -proper if two conditions are met:

- $ s_1=s_2=\ldots=s_k $ ;
- $ s_{i+k} \neq s_i $ for any $ i $ ( $ 1 \le i \le n - k $ ).

For example, with $ k=3 $ , the strings 000, 111000111, and 111000 are $ k $ -proper, while the strings 000000, 001100, and 1110000 are not.

You are given an integer $ k $ , which is a divisor of $ n $ . Find an integer $ p $ ( $ 1 \le p \le n $ ) such that after performing the operation, the string $ s $ becomes $ k $ -proper, or determine that it is impossible. Note that if the string is initially $ k $ -proper, you still need to apply exactly one operation to it.

## 说明/提示

In the first test case, if you apply the operation with $ p=3 $ , after the second step of the operation, the string becomes 11100001, and after the third step, it becomes 00001111. This string is $ 4 $ -proper.

In the second test case, it can be shown that there is no operation after which the string becomes $ 2 $ -proper.

In the third test case, if you apply the operation with $ p=7 $ , after the second step of the operation, the string becomes 100011100011, and after the third step, it becomes 000111000111. This string is $ 3 $ -proper.

In the fourth test case, after the operation with any $ p $ , the string becomes $ 5 $ -proper.

## 样例 #1

### 输入

```
7
8 4
11100001
4 2
1110
12 3
111000100011
5 5
00000
6 1
101001
8 4
01110001
12 2
110001100110```

### 输出

```
3
-1
7
5
4
-1
3```

# AI分析结果



### 算法分类
字符串哈希、构造

### 题解思路、算法要点与解决难点
1. **构造目标字符串**：合法的k-proper字符串只有两种模式，即k个0和k个1交替出现的形式。分别构造这两种目标字符串。
2. **哈希预处理**：计算原字符串的前缀哈希和反转后的前缀哈希，便于快速拼接操作后的字符串哈希。
3. **操作后的哈希计算**：对于每个可能的p，操作后的字符串由原字符串的p+1到n部分和反转后的前p部分拼接而成。通过前缀哈希和反转哈希的组合，快速计算哈希值。
4. **哈希比较**：将操作后的哈希与目标字符串的哈希匹配，找到符合条件的p。

**难点**：正确计算反转部分的哈希。反转后的前p部分需与原字符串的前p部分反转后的哈希一致，需通过预处理实现高效计算。

### 最优思路或技巧提炼
- **目标模式构造**：仅需两种目标模式，避免遍历所有可能。
- **哈希拼接公式**：利用前缀哈希和反转哈希的组合，快速生成操作后的哈希。
- **线性时间复杂度**：预处理和遍历均为O(n)，适合大规模数据。

### 题解评分（≥4星）
1. **Engulf的题解（4星）**  
   使用哈希预处理和拼接，思路清晰。但存在反转哈希处理可能不准确的问题，需注意边界条件。
2. **ZhongYuLin的题解（4星）**  
   使用线段树维护哈希，灵活处理反转部分，代码复杂度较高但正确性有保障。
3. **cjh20090318的题解（4星）**  
   随机双哈希避免碰撞，预处理自然溢出哈希，处理反转部分更严谨。

### 代码片段（核心逻辑）
```cpp
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const int N = 1e5 + 5;
ull base = 233, pw[N], pre[N], suf_rev[N];
char s[N], target1[N], target2[N];
int n, k;

void init_hashes() {
    // 预处理原字符串前缀哈希和反转后的前缀哈希
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i-1] * base + s[i];
        suf_rev[i] = suf_rev[i-1] + s[i] * pw[i-1]; // 反转哈希
    }
}

ull get_operated_hash(int p) {
    ull part1 = (pre[n] - pre[p] * pw[n-p]) * pw[p];
    ull part2 = suf_rev[p];
    return part1 + part2;
}

int main() {
    // 初始化pw数组
    pw[0] = 1;
    for (int i = 1; i < N; ++i) pw[i] = pw[i-1] * base;

    // 构造目标哈希
    // target1和target2的构造略...
    ull hash1 = compute_hash(target1);
    ull hash2 = compute_hash(target2);

    // 处理每个测试用例
    int T; cin >> T;
    while (T--) {
        cin >> n >> k >> (s+1);
        init_hashes();
        int ans = -1;
        for (int p = 1; p <= n; ++p) {
            ull current = get_operated_hash(p);
            if (current == hash1 || current == hash2) {
                ans = p; break;
            }
        }
        cout << ans << endl;
    }
}
```

### 可视化与算法演示
1. **动画设计**：
   - **分步展示**：高亮当前p值，显示操作后的字符串结构（原后缀+反转前缀）。
   - **哈希计算**：动态展示部分哈希值的计算过程，如乘法与加法。
   - **颜色标记**：目标哈希匹配时高亮绿色，否则红色。

2. **复古像素风格**：
   - **8位网格**：用像素块表示字符，0为蓝色方块，1为黄色。
   - **音效**：匹配成功时播放胜利音效，失败时低沉音效。
   - **自动演示**：AI自动遍历p值，快速定位解。

### 同类型题与推荐题目
1. **洛谷P3370**（字符串哈希基础）
2. **CF535D**（哈希与模式匹配）
3. **LeetCode 686**（循环哈希匹配）

### 个人心得摘录
- **哈希方向**：反转部分的哈希处理需特别注意方向，避免预处理错误。
- **边界测试**：尤其关注k整除n的情况和全同字符的特殊情况。

---
处理用时：290.49秒