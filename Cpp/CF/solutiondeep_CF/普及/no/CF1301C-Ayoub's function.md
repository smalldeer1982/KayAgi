# 题目信息

# Ayoub's function

## 题目描述

Ayoub thinks that he is a very smart person, so he created a function $ f(s) $ , where $ s $ is a binary string (a string which contains only symbols "0" and "1"). The function $ f(s) $ is equal to the number of substrings in the string $ s $ that contains at least one symbol, that is equal to "1".

More formally, $ f(s) $ is equal to the number of pairs of integers $ (l, r) $ , such that $ 1 \leq l \leq r \leq |s| $ (where $ |s| $ is equal to the length of string $ s $ ), such that at least one of the symbols $ s_l, s_{l+1}, \ldots, s_r $ is equal to "1".

For example, if $ s =  $ "01010" then $ f(s) = 12 $ , because there are $ 12 $ such pairs $ (l, r) $ : $ (1, 2), (1, 3), (1, 4), (1, 5), (2, 2), (2, 3), (2, 4), (2, 5), (3, 4), (3, 5), (4, 4), (4, 5) $ .

Ayoub also thinks that he is smarter than Mahmoud so he gave him two integers $ n $ and $ m $ and asked him this problem. For all binary strings $ s $ of length $ n $ which contains exactly $ m $ symbols equal to "1", find the maximum value of $ f(s) $ .

Mahmoud couldn't solve the problem so he asked you for help. Can you help him?

## 说明/提示

In the first test case, there exists only $ 3 $ strings of length $ 3 $ , which has exactly $ 1 $ symbol, equal to "1". These strings are: $ s_1 =  $ "100", $ s_2 =  $ "010", $ s_3 =  $ "001". The values of $ f $ for them are: $ f(s_1) = 3, f(s_2) = 4, f(s_3) = 3 $ , so the maximum value is $ 4 $ and the answer is $ 4 $ .

In the second test case, the string $ s $ with the maximum value is "101".

In the third test case, the string $ s $ with the maximum value is "111".

In the fourth test case, the only string $ s $ of length $ 4 $ , which has exactly $ 0 $ symbols, equal to "1" is "0000" and the value of $ f $ for that string is $ 0 $ , so the answer is $ 0 $ .

In the fifth test case, the string $ s $ with the maximum value is "01010" and it is described as an example in the problem statement.

## 样例 #1

### 输入

```
5
3 1
3 2
3 3
4 0
5 2```

### 输出

```
4
5
6
0
12```

# AI分析结果

### 题目内容重写

#### 题目描述

Ayoub 认为他非常聪明，因此他创建了一个函数 $f(s)$，其中 $s$ 是一个二进制字符串（仅包含符号 "0" 和 "1"）。函数 $f(s)$ 等于字符串 $s$ 中包含至少一个 "1" 的子串的数量。

更正式地，$f(s)$ 等于整数对 $(l, r)$ 的数量，使得 $1 \leq l \leq r \leq |s|$（其中 $|s|$ 是字符串 $s$ 的长度），并且至少有一个符号 $s_l, s_{l+1}, \ldots, s_r$ 等于 "1"。

例如，如果 $s = $ "01010"，那么 $f(s) = 12$，因为有 $12$ 个这样的对 $(l, r)$：$(1, 2), (1, 3), (1, 4), (1, 5), (2, 2), (2, 3), (2, 4), (2, 5), (3, 4), (3, 5), (4, 4), (4, 5)$。

Ayoub 还认为他比 Mahmoud 更聪明，因此他给了 Mahmoud 两个整数 $n$ 和 $m$，并问他这个问题。对于所有长度为 $n$ 且恰好包含 $m$ 个 "1" 的二进制字符串 $s$，找出 $f(s)$ 的最大值。

Mahmoud 无法解决这个问题，因此他向你求助。你能帮助他吗？

#### 说明/提示

在第一个测试用例中，存在 $3$ 个长度为 $3$ 且恰好包含 $1$ 个 "1" 的字符串。这些字符串是：$s_1 = $ "100"，$s_2 = $ "010"，$s_3 = $ "001"。它们的 $f$ 值分别为：$f(s_1) = 3$，$f(s_2) = 4$，$f(s_3) = 3$，因此最大值为 $4$，答案为 $4$。

在第二个测试用例中，具有最大值的字符串 $s$ 是 "101"。

在第三个测试用例中，具有最大值的字符串 $s$ 是 "111"。

在第四个测试用例中，唯一一个长度为 $4$ 且恰好包含 $0$ 个 "1" 的字符串 $s$ 是 "0000"，其 $f$ 值为 $0$，因此答案为 $0$。

在第五个测试用例中，具有最大值的字符串 $s$ 是 "01010"，并且在问题描述中已经作为示例进行了说明。

#### 样例 #1

##### 输入

```
5
3 1
3 2
3 3
4 0
5 2
```

##### 输出

```
4
5
6
0
12
```

### 算法分类

贪心

### 题解分析与结论

本题的核心思路是通过贪心策略最小化全为 "0" 的子串数量，从而最大化包含至少一个 "1" 的子串数量。具体来说，将 "0" 均匀分布在 "1" 之间，使得每段 "0" 的长度尽可能相等，这样可以最小化全为 "0" 的子串数量。

### 所选题解

#### 题解作者：CSP_Sept (赞：3)

**星级：4.5**

**关键亮点：**
- 通过容斥原理将问题转化为最小化全为 "0" 的子串数量。
- 提供了详细的数学证明，说明将 "0" 均匀分布可以最小化全为 "0" 的子串数量。
- 代码简洁明了，处理了余数的情况。

**代码核心思想：**
- 计算总子串数 `tot = n * (n + 1) / 2`。
- 计算每段 "0" 的长度 `p = (n - m) / (m + 1)` 和余数 `r = (n - m) % (m + 1)`。
- 输出结果 `tot - p * (m + 1) * (p + 1) / 2 - (p + 1) * r`。

**代码片段：**
```cpp
void sol(){
    scanf("%lld%lld", &n, &m);
    ll tot, p, r;
    tot = n * (n + 1) / 2;
    p = (n - m) / (m + 1);
    r = (n - m) % (m + 1);
    printf("%lld\n", tot - p * (m + 1) * (p + 1) / 2 - (p + 1) * r);
}
```

#### 题解作者：Limit (赞：2)

**星级：4**

**关键亮点：**
- 将问题分为两部分：点和区间，简化了计算。
- 通过计算每段 "0" 的长度，确保每段 "0" 的长度尽可能相等。
- 代码结构清晰，易于理解。

**代码核心思想：**
- 计算每段 "0" 的长度 `len = (N - M) / (M + 1)` 和余数 `num1 = (N - M - len * (M + 1))`。
- 输出结果 `(N * (N - 1) - len * (len + 1) * num1 - len * (len - 1) * num2) / 2 + M`。

**代码片段：**
```cpp
void work(){
    scanf("%lld%lld",&N,&M);
    long long len=(N-M)/(M+1);
    long long num1=(N-M-len*(M+1));
    long long num2=M+1-num1;
    long long answer=N*(N-1)-len*(len+1)*num1-len*(len-1)*num2;
    answer/=2;
    printf("%lld\n",answer+M);
}
```

#### 题解作者：_Lazy_zhr_ (赞：0)

**星级：4**

**关键亮点：**
- 反向思考，通过最小化全为 "0" 的子串数量来最大化包含至少一个 "1" 的子串数量。
- 代码简洁，处理了特殊情况（如 `m == 0`）。

**代码核心思想：**
- 计算总子串数 `ans = (n + 1) * n / 2`。
- 计算每段 "0" 的长度 `s = a / b` 和余数 `f = a % b`。
- 输出结果 `ans - ((s + 1) * s / 2 * (b - f)) - ((s + 2) * (s + 1) / 2 * f)`。

**代码片段：**
```cpp
void solve(){
    int ans;
    cin>>n>>m;
    if(m==0){
        cout<<"0\n";
        return ;
    }
    ans=(n+1)*n/2;
    int a=n-m,b=m+1;
    int s=a/b,f=a%b;
    ans-=((s+1)*s/2*(b-f));
    ans-=((s+2)*(s+1)/2*f);
    cout<<ans<<"\n";
}
```

### 最优关键思路或技巧

- **贪心策略**：将 "0" 均匀分布在 "1" 之间，使得每段 "0" 的长度尽可能相等，从而最小化全为 "0" 的子串数量。
- **数学计算**：通过容斥原理和数学公式计算总子串数和全为 "0" 的子串数量，简化问题。

### 可拓展之处

- **类似问题**：在其他需要最大化或最小化某种子串数量的问题中，可以考虑类似的贪心策略和数学计算。
- **组合数学**：在处理子串数量问题时，组合数学的方法（如容斥原理）常常能简化计算。

### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：47.48秒