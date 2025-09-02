# 题目信息

# Make Them Equal

## 题目描述

Theofanis has a string $ s_1 s_2 \dots s_n $ and a character $ c $ . He wants to make all characters of the string equal to $ c $ using the minimum number of operations.

In one operation he can choose a number $ x $ ( $ 1 \le x \le n $ ) and for every position $ i $ , where $ i $ is not divisible by $ x $ , replace $ s_i $ with $ c $ .

Find the minimum number of operations required to make all the characters equal to $ c $ and the $ x $ -s that he should use in his operations.

## 说明/提示

Let's describe what happens in the third test case:

1. $ x_1 = 2 $ : we choose all positions that are not divisible by $ 2 $ and replace them, i. e. bzyx $ \rightarrow $ bzbx;
2. $ x_2 = 3 $ : we choose all positions that are not divisible by $ 3 $ and replace them, i. e. bzbx $ \rightarrow $ bbbb.

## 样例 #1

### 输入

```
3
4 a
aaaa
4 a
baaa
4 b
bzyx```

### 输出

```
0
1
2
2 
2 3```

# AI分析结果

### 题目翻译

**题目描述**

Theofanis 有一个字符串 $s_1 s_2 \dots s_n$ 和一个字符 $c$。他希望用最少的操作次数将字符串中的所有字符变为 $c$。

在每次操作中，他可以选择一个数 $x$（$1 \le x \le n$），然后将所有下标 $i$ 不能被 $x$ 整除的字符 $s_i$ 替换为 $c$。

请找出将字符串中的所有字符变为 $c$ 所需的最少操作次数，并输出所使用的 $x$ 值。

**说明/提示**

让我们描述第三个测试用例的操作过程：

1. $x_1 = 2$：选择所有不能被 $2$ 整除的位置并替换它们，即 bzyx $\rightarrow$ bzbx；
2. $x_2 = 3$：选择所有不能被 $3$ 整除的位置并替换它们，即 bzbx $\rightarrow$ bbbb。

**样例 #1**

### 输入

```
3
4 a
aaaa
4 a
baaa
4 b
bzyx
```

### 输出

```
0
1
2
2 
2 3
```

### 算法分类
构造

### 题解分析与结论

本题的核心思路是通过构造操作序列，使得字符串中的所有字符变为目标字符 $c$。所有题解都基于一个关键观察：答案最多为 $2$，因为选择 $x = n$ 和 $x = n-1$ 可以覆盖所有字符。因此，题解的主要任务是判断是否可以通过一次操作完成目标，否则输出两次操作。

### 精选题解

#### 1. 作者：智子 (4星)
**关键亮点**：
- 简洁明了地提出了答案最多为 $2$ 的结论。
- 通过枚举 $x$ 来判断是否可以通过一次操作完成目标，复杂度为 $O(n \ln n)$。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    bool flag = true;
    for(int j = i; j <= n; j += i) {
        if(s[j] != c) {
            flag = false;
        }
    }
    if(flag) {
        ans = i;
        p = true;
        break;
    }
}
```
**实现思想**：枚举每个可能的 $x$，检查其倍数位置是否已经为 $c$，如果是，则可以通过一次操作完成目标。

#### 2. 作者：Huami360 (4星)
**关键亮点**：
- 通过将所有需要变的位置放入数组，进一步优化了判断过程。
- 复杂度为 $O(n \log n)$，代码结构清晰。

**核心代码**：
```cpp
int judge(int x){
    for(int i = x; i <= n; i += x)
        if(f[i] == dfn) 
            return 0;
    return 1;
}
```
**实现思想**：通过标记需要变的位置，判断是否存在一个 $x$，使得其倍数位置不需要变化，从而通过一次操作完成目标。

#### 3. 作者：清烛 (4星)
**关键亮点**：
- 通过调和级数的复杂度判断是否存在一次操作的可能性。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for (ans = 2; ans <= n; ++ans) {
    bool now = 1;
    for (int j = ans; j <= n; j += ans) if (s[j] != c) {now = 0; break;}
    if (now) {flag = 1; break;}
}
```
**实现思想**：枚举每个可能的 $x$，检查其倍数位置是否已经为 $c$，如果是，则可以通过一次操作完成目标。

### 最优关键思路
- **关键思路**：通过枚举 $x$ 并检查其倍数位置是否已经为 $c$，判断是否可以通过一次操作完成目标。如果不行，则选择 $x = n$ 和 $x = n-1$ 进行两次操作。
- **优化技巧**：利用调和级数的复杂度进行枚举，确保在合理时间内完成判断。

### 拓展思路
- 类似问题：可以通过枚举和调和级数复杂度解决的问题，如某些字符串匹配或构造问题。
- 推荐题目：
  1. [CF1594C - Make Them Equal](https://www.luogu.com.cn/problem/CF1594C)
  2. [CF1594D - Make Them Equal](https://www.luogu.com.cn/problem/CF1594D)
  3. [CF1594E - Make Them Equal](https://www.luogu.com.cn/problem/CF1594E)

---
处理用时：30.60秒