# 题目信息

# Ehab the Xorcist

## 题目描述

Given 2 integers $ u $ and $ v $ , find the shortest array such that [bitwise-xor](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of its elements is $ u $ , and the sum of its elements is $ v $ .

## 说明/提示

In the first sample, $ 3\oplus 1 = 2 $ and $ 3 + 1 = 4 $ . There is no valid array of smaller length.

Notice that in the fourth sample the array is empty.

## 样例 #1

### 输入

```
2 4```

### 输出

```
2
3 1```

## 样例 #2

### 输入

```
1 3```

### 输出

```
3
1 1 1```

## 样例 #3

### 输入

```
8 5```

### 输出

```
-1```

## 样例 #4

### 输入

```
0 0```

### 输出

```
0```

# AI分析结果

【题目内容（中文重写）】
# Ehab 与异或运算

## 题目描述
给定两个整数 $u$ 和 $v$，找出最短的数组，使得该数组元素的按位异或和为 $u$，且元素之和为 $v$。

## 说明/提示
在第一个样例中，$3\oplus 1 = 2$ 且 $3 + 1 = 4$。不存在长度更小的有效数组。

注意，在第四个样例中，数组为空。

## 样例 #1
### 输入
```
2 4
```
### 输出
```
2
3 1
```

## 样例 #2
### 输入
```
1 3
```
### 输出
```
3
1 1 1
```

## 样例 #3
### 输入
```
8 5
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
0 0
```
### 输出
```
0
```

【算法分类】
构造

【综合分析与结论】
这些题解主要围绕构造满足异或和为 $u$、数值和为 $v$ 的最短数组展开。思路大多是先判断无解情况，再分情况构造数组。
- **无解判断**：普遍认为当 $u > v$ 或 $u$ 与 $v$ 奇偶性不同时无解，依据是异或和小于等于数值和，且两者奇偶性相同。
- **特殊情况处理**：当 $u = v$ 时，若 $u = v = 0$ 输出 $0$，否则数组为 $[u]$；当 $u \neq v$ 时，尝试构造长度为 2 或 3 的数组。
- **构造方法**：常见方法是将 $\Delta = v - u$ 拆分为两个 $\frac{\Delta}{2}$，构造 $[\frac{\Delta}{2},\frac{\Delta}{2}, u]$，若 $\frac{\Delta}{2} \land u = 0$ 则可优化为 $[\frac{\Delta}{2}, \frac{\Delta}{2} \oplus u]$。

【所选的题解】
- **syksykCCC（5星）**
  - **关键亮点**：思路清晰，先给出两个重要结论，为后续推理提供理论支持，代码简洁明了。
  - **个人心得**：无
- **Limit（4星）**
  - **关键亮点**：分析过程详细，明确指出重要结论，代码逻辑清晰。
  - **个人心得**：无
- **Clever_Jimmy（4星）**
  - **关键亮点**：简洁地分情况讨论，给出清晰的构造方法，还提醒开 `long long`。
  - **个人心得**：无

【重点代码】
```cpp
// syksykCCC 的代码
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
LL u, v;
int main()
{
    ios::sync_with_stdio(false);
    cin >> u >> v;
    LL delta = v - u;
    if(delta < 0 || (delta & 1))
    {
        cout << -1 << endl;
        return 0;
    }
    if(!delta)
    {
        if(!u) cout << 0 << endl;
        else cout << 1 << '\n' << u << endl; 
    }
    else
    {
        LL haf = delta >> 1;
        if((haf & u) == 0) cout << 2 << '\n' << haf << ' ' << (haf ^ u) << endl;
        else cout << 3 << '\n' << haf << ' ' << haf << ' ' << u << endl;
    }
    return 0;
}
```
**核心实现思想**：先计算 $\Delta = v - u$，判断无解情况，再处理特殊情况 $\Delta = 0$，最后根据 $\frac{\Delta}{2} \land u$ 是否为 0 构造长度为 2 或 3 的数组。

【可拓展之处】
同类型题可能会改变条件，如要求构造满足特定条件的数组，或在异或和与数值和的基础上增加其他限制。类似算法套路可用于解决其他构造类问题，关键在于利用数学性质和位运算特点进行推理和构造。

【推荐题目】
1. [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

【个人心得摘录与总结】
- **wind_cross**：考场上最后 10 分钟做出此题，但 C 题没写出来，强调了思维在 CF 比赛中的重要性。
- **Create_Random**：因忘判 $u = v$ 导致 FST，提醒要注意特殊情况的判断。
- **dingcx**：考试栽在这题上，分情况讨论时要注意细节，避免遗漏情况。
- **LJB00131**：比赛时漏看 “最短” 条件，第一次交 Wa on 1，提醒做题时要仔细读题。 

---
处理用时：36.07秒