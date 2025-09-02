# 题目信息

# Smaller

## 题目描述

Alperen has two strings, $ s $ and $ t $ which are both initially equal to "a".

He will perform $ q $ operations of two types on the given strings:

- $ 1 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ s $ . In other words, $ s := s + \underbrace{x + \dots + x}_{k \text{ times}} $ .
- $ 2 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ t $ . In other words, $ t := t + \underbrace{x + \dots + x}_{k \text{ times}} $ .

After each operation, determine if it is possible to rearrange the characters of $ s $ and $ t $ such that $ s $ is lexicographically smaller $ ^{\dagger} $ than $ t $ .

Note that the strings change after performing each operation and don't go back to their initial states.

 $ ^{\dagger} $ Simply speaking, the lexicographical order is the order in which words are listed in a dictionary. A formal definition is as follows: string $ p $ is lexicographically smaller than string $ q $ if there exists a position $ i $ such that $ p_i < q_i $ , and for all $ j < i $ , $ p_j = q_j $ . If no such $ i $ exists, then $ p $ is lexicographically smaller than $ q $ if the length of $ p $ is less than the length of $ q $ . For example, $ \texttt{abdc} < \texttt{abe} $ and $ \texttt{abc} < \texttt{abcd} $ , where we write $ p < q $ if $ p $ is lexicographically smaller than $ q $ .

## 说明/提示

In the first test case, the strings are initially $ s =  $ "a" and $ t =  $ "a".

After the first operation the string $ t $ becomes "aaa". Since "a" is already lexicographically smaller than "aaa", the answer for this operation should be "YES".

After the second operation string $ s $ becomes "aaa", and since $ t $ is also equal to "aaa", we can't arrange $ s $ in any way such that it is lexicographically smaller than $ t $ , so the answer is "NO".

After the third operation string $ t $ becomes "aaaaaa" and $ s $ is already lexicographically smaller than it so the answer is "YES".

After the fourth operation $ s $ becomes "aaabb" and there is no way to make it lexicographically smaller than "aaaaaa" so the answer is "NO".

After the fifth operation the string $ t $ becomes "aaaaaaabcaabcaabca", and we can rearrange the strings to: "bbaaa" and "caaaaaabcaabcaabaa" so that $ s $ is lexicographically smaller than $ t $ , so we should answer "YES".

## 样例 #1

### 输入

```
3
5
2 1 aa
1 2 a
2 3 a
1 2 b
2 3 abca
2
1 5 mihai
2 2 buiucani
3
1 5 b
2 3 a
2 4 paiu```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
NO
NO
YES```

# AI分析结果

### 题目内容重写
Alperen有两个字符串$s$和$t$，初始时都为"a"。他将对这两个字符串进行$q$次操作，操作分为两种类型：

1. $1 \;\; k \;\; x$ —— 将字符串$x$重复$k$次追加到$s$的末尾。即$s := s + \underbrace{x + \dots + x}_{k \text{ times}}$。
2. $2 \;\; k \;\; x$ —— 将字符串$x$重复$k$次追加到$t$的末尾。即$t := t + \underbrace{x + \dots + x}_{k \text{ times}}$。

每次操作后，判断是否可以通过重新排列$s$和$t$的字符，使得$s$的字典序小于$t$。

### 算法分类
字符串、贪心

### 题解分析与结论
所有题解的核心思路都是基于字符串的字典序比较，特别是利用字符`a`的特殊性质（字典序最小）。主要思路是：
1. 如果$t$中包含非`a`字符，则可以通过将非`a`字符放在$t$的开头，使得$s$的字典序小于$t$。
2. 如果$t$中只有`a`字符，而$s$中包含非`a`字符，则$s$的字典序一定大于$t$。
3. 如果$s$和$t$都只有`a`字符，则比较它们的长度，长度较短的字典序较小。

### 高星题解推荐
#### 1. 作者：_Aniya_ (5星)
- **关键亮点**：思路清晰，代码简洁，通过维护$s$和$t$是否全为`a`的状态，以及它们的长度，快速判断字典序关系。
- **代码核心**：
```cpp
bool doushia(string s) {
    for(ll i=0;i<s.length();i++) {
        if(s[i]!='a') return 0;
    }
    return 1;
}
```
- **核心实现**：通过函数`doushia`判断字符串是否全为`a`，并根据操作类型更新$s$和$t$的状态和长度，最后根据状态和长度输出结果。

#### 2. 作者：what_can_I_do (4星)
- **关键亮点**：逻辑清晰，代码简洁，通过维护$s$和$t$的长度和是否全为`a`的状态，快速判断字典序关系。
- **代码核心**：
```cpp
if(!flag1&&flag2) cout<<"NO"<<endl;
else if(flag1) cout<<"YES"<<endl;
else if(slen<tlen) cout<<"YES"<<endl;
else cout<<"NO"<<endl;
```
- **核心实现**：通过维护$s$和$t$的长度和是否全为`a`的状态，快速判断字典序关系。

#### 3. 作者：HNOIRPplusplus (4星)
- **关键亮点**：思路清晰，代码简洁，通过维护$s$和$t$的长度和是否全为`a`的状态，快速判断字典序关系。
- **代码核心**：
```cpp
if(!ta) { // t 里面有非 a 字符
    cout << "YES\n";
} else if(sa && sl < tl) { // s 和 t 都只有 a，但是 s 更短
    cout << "YES\n";
} else { // 可怜不能成功
    cout << "NO\n";
}
```
- **核心实现**：通过维护$s$和$t$的长度和是否全为`a`的状态，快速判断字典序关系。

### 最优关键思路
1. 利用字符`a`的字典序最小性质，快速判断$s$和$t$的字典序关系。
2. 维护$s$和$t$是否全为`a`的状态，以及它们的长度，避免每次操作后重新计算。

### 可拓展之处
类似的问题可以扩展到其他字典序相关的题目，例如判断两个字符串的字典序关系，或者通过字符替换使得一个字符串的字典序小于另一个字符串。

### 推荐题目
1. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

### 个人心得
在调试过程中，发现维护$s$和$t$是否全为`a`的状态非常重要，可以大大减少计算量，避免超时。同时，利用字符`a`的特殊性质，可以快速判断字典序关系，简化问题。

---
处理用时：35.38秒