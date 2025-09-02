# 题目信息

# Make a Power of Two

## 题目描述

You are given an integer $ n $ . In $ 1 $ move, you can do one of the following actions:

- erase any digit of the number (it's acceptable that the number before the operation has exactly one digit and after the operation, it is "empty");
- add one digit to the right.

The actions may be performed in any order any number of times.

Note that if, after deleting some digit from a number, it will contain leading zeroes, they will not be deleted. E.g. if you delete from the number $ 301 $ the digit $ 3 $ , the result is the number $ 01 $ (not $ 1 $ ).

You need to perform the minimum number of actions to make the number any power of $ 2 $ (i.e. there's an integer $ k $ ( $ k \ge 0 $ ) such that the resulting number is equal to $ 2^k $ ). The resulting number must not have leading zeroes.

E.g. consider $ n=1052 $ . The answer is equal to $ 2 $ . First, let's add to the right one digit $ 4 $ (the result will be $ 10524 $ ). Then let's erase the digit $ 5 $ , so the result will be $ 1024 $ which is a power of $ 2 $ .

E.g. consider $ n=8888 $ . The answer is equal to $ 3 $ . Let's erase any of the digits $ 8 $ three times. The result will be $ 8 $ which is a power of $ 2 $ .

## 说明/提示

The answer for the first test case was considered above.

The answer for the second test case was considered above.

In the third test case, it's enough to add to the right the digit $ 4 $ — the number $ 6 $ will turn into $ 64 $ .

In the fourth test case, let's add to the right the digit $ 8 $ and then erase $ 7 $ and $ 5 $ — the taken number will turn into $ 8 $ .

The numbers of the fifth and the sixth test cases are already powers of two so there's no need to make any move.

In the seventh test case, you can delete first of all the digit $ 3 $ (the result is $ 01 $ ) and then the digit $ 0 $ (the result is $ 1 $ ).

## 样例 #1

### 输入

```
12
1052
8888
6
75
128
1
301
12048
1504
6656
1000000000
687194767```

### 输出

```
2
3
1
3
0
0
2
1
3
4
9
2```

# AI分析结果

### 题目内容重写
给定一个整数 $n$。在每次操作中，你可以执行以下两种操作之一：
- 删除该数的任意一位数字（如果该数只有一位，操作后可以为空）；
- 在该数的右侧添加一位数字。

操作可以以任意顺序执行任意次数。注意，如果删除某些数字后，该数包含前导零，则前导零不会被删除。例如，从数字 $301$ 中删除数字 $3$ 后，结果为 $01$（而不是 $1$）。

你需要执行最少的操作次数，使得该数变为 $2$ 的某个幂次方（即存在一个整数 $k$（$k \ge 0$），使得最终结果等于 $2^k$）。最终结果不能包含前导零。

### 算法分类
枚举、字符串

### 题解分析与结论
该题的核心思路是通过枚举所有可能的 $2$ 的幂次方，然后计算将给定数字 $n$ 转换为这些幂次方所需的最小操作次数。操作包括删除和添加数字，最终目标是找到与 $2^k$ 最接近的数字形式。

### 所选高分题解
#### 1. 作者：MikeC (赞：4)
**星级：5星**
**关键亮点：**
- 预处理了所有可能的 $2$ 的幂次方，并将其存储在字符串数组中。
- 通过计算原始字符串与目标字符串的最长公共前缀子序列，快速得出最小操作次数。
- 代码简洁高效，时间复杂度为 $O(1)$。

**核心代码：**
```cpp
inline int work(int x){
    int sum=0;
    int n=strlen(a),m=strlen(str[x]);
    for(int i=0;i<n;i++){
        if(a[i]==str[x][sum])sum++;
    }
    ans=min(ans,n+m-2*sum);
}
```

#### 2. 作者：Shirο (赞：1)
**星级：4星**
**关键亮点：**
- 通过贪心策略最大化利用匹配的数字，计算最小操作次数。
- 使用指针维护两串的相同数字个数，优化了匹配过程。
- 代码清晰，逻辑简单。

**核心代码：**
```cpp
int wk(string s,string t){
    int tp=0,sp=0,x=0;
    while(sp<s.length() and tp<t.length()){
        if(s[sp]==t[tp]) ++x,++tp;
        sp++;
    }
    return s.length()+t.length()-2*x;
}
```

#### 3. 作者：Computer1828 (赞：1)
**星级：4星**
**关键亮点：**
- 预处理了 $2^0$ 到 $2^{60}$ 的所有幂次方，并将其转换为字符串。
- 通过枚举所有可能的 $2^k$，计算最小操作次数。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
inline int getans(string s,string t){
    int j = 0;
    for(int i = 0;i<s.length()&&j<t.length();++i){
        if(s[i] == t[j]) j++;
    }
    return s.length()+t.length()-j*2;
}
```

### 最优关键思路或技巧
1. **预处理所有可能的 $2$ 的幂次方**：通过预处理，可以快速枚举所有可能的 $2^k$，避免重复计算。
2. **最长公共前缀子序列**：通过计算原始字符串与目标字符串的最长公共前缀子序列，可以快速得出最小操作次数。
3. **贪心策略**：在匹配过程中，尽量保留匹配的数字，减少删除和添加操作。

### 可拓展之处
该题的思路可以拓展到其他类似的字符串匹配问题，例如将数字转换为其他特定形式的数字（如 $3$ 的幂次方、斐波那契数列等）。通过预处理和贪心策略，可以高效解决这类问题。

### 推荐题目
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：28.98秒