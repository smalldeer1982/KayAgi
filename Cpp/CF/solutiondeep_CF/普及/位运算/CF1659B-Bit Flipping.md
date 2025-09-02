# 题目信息

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4```

# AI分析结果

### 题目中文重写
# 位翻转

## 题目描述
给定一个长度为 $n$ 的二进制字符串。你恰好有 $k$ 次移动机会。在一次移动中，你必须选择一个单独的位。除该位之外的所有位的状态将被翻转（$0$ 变为 $1$，$1$ 变为 $0$）。你需要输出在使用完所有 $k$ 次移动后能得到的字典序最大的字符串。同时，输出你选择每个位的次数。如果有多种方法可以做到这一点，你可以输出其中任何一种。

当且仅当满足以下条件时，二进制字符串 $a$ 的字典序大于相同长度的二进制字符串 $b$：
- 在 $a$ 和 $b$ 不同的第一个位置上，字符串 $a$ 包含 $1$，而字符串 $b$ 包含 $0$。

## 说明/提示
以下是第一个测试用例的解释。每一步展示了二进制字符串在一次移动中的变化。
- 选择第 $1$ 位：$ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $。
- 选择第 $4$ 位：$ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $。
- 选择第 $4$ 位：$ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $。

最终字符串是 $111110$，这是我们能得到的字典序最大的字符串。

## 样例 #1
### 输入
```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110
```

### 输出
```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4
```

### 题解综合分析与结论
- **思路对比**：
    - World_Creater：将两次操作合并，转化为花费 $2$ 的代价取反任意两位的问题。对 $k$ 分奇偶情况处理，奇数时先处理多余一次操作，再按偶数情况贪心处理。
    - Tx_Lcy：从前往后考虑，根据当前位是 $1$ 或 $0$ 以及 $k$ 的奇偶性决定是否覆盖该位，剩余 $k$ 加到最后一位。
    - Wsy_flying_forever：将操作分为改变首位和不改变首位两类，根据当前位和 $k$ 的奇偶性花 $0$ 或 $1$ 次操作使 $k$ 满足条件，暴力模拟。
    - Lv_Boxiu：用变量记录前面变化次数进行字符变换，贪心优先保障左侧字符为 $1$，根据当前位和 $k$ 奇偶性调整，剩余次数给最后一个字符。
- **算法要点**：
    - 都采用贪心策略，优先让高位为 $1$。
    - 都考虑了 $k$ 的奇偶性对操作的影响。
    - 都将剩余操作次数处理在最后一位。
- **解决难点**：
    - 处理 $k$ 为奇数时的特殊情况，保证字典序最大。
    - 合理分配操作次数，使最终字符串字典序最大。

### 所选题解
- **World_Creater（5星）**：
    - **关键亮点**：思路清晰，将问题进行转化，分奇偶情况处理，代码实现简洁易懂。
    - **核心代码**：
```cpp
if(k&1) {
    int fi=-1;
    for(int i=0;i<n;i++) {
        if(s[i]=='1') {
            fi=i;
            ans[i]++;
            k--; 
            break;
        }
    }
    if(fi==-1) {
        ans[n-1]++;
        fi=n-1;
        k--;
    }
    for(int i=0;i<n;i++) {
        if(i!=fi) s[i]=s[i]=='0'?'1':'0';
    }
}
for(int i=0;i<n&&k>0;i++) {
    if(s[i]=='0') {
        ans[i]++; 
        k--;
        s[i]='1';
    }
}
ans[n-1]+=k;
if(k&1) {
    s[n-1]=s[n-1]=='0'?'1':'0';
}
```
核心思想：先处理 $k$ 为奇数的特殊情况，找到第一个 $1$ 进行操作，若没有则操作最后一位。然后从左往右贪心将 $0$ 变为 $1$，最后将剩余操作次数加到最后一位。

### 最优关键思路或技巧
- 将两次操作合并为一次操作，转化问题，简化处理。
- 分奇偶情况讨论，针对不同情况采用不同贪心策略。
- 优先保障高位为 $1$，剩余操作次数放在最后一位，减少对字典序的影响。

### 拓展思路
同类型题可考虑不同的操作规则和目标，如操作次数有限制且有不同的操作代价，目标可能是使字符串的某种特征值最大等。类似算法套路为贪心算法，根据题目条件确定贪心策略，优先满足重要条件。

### 推荐洛谷题目
- P1223 排队接水（贪心算法，根据接水时间排序）
- P1094 纪念品分组（贪心算法，合理分组使组数最少）
- P2240 木材加工（二分 + 贪心，确定合适的切割长度）

### 个人心得
无

---
处理用时：32.14秒