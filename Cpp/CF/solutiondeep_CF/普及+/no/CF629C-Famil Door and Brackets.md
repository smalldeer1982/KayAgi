# 题目信息

# Famil Door and Brackets

## 题目描述

As Famil Door’s birthday is coming, some of his friends (like Gabi) decided to buy a present for him. His friends are going to buy a string consisted of round brackets since Famil Door loves string of brackets of length $ n $ more than any other strings!

The sequence of round brackets is called valid if and only if:

1. the total number of opening brackets is equal to the total number of closing brackets;
2. for any prefix of the sequence, the number of opening brackets is greater or equal than the number of closing brackets.

Gabi bought a string $ s $ of length $ m $ ( $ m<=n $ ) and want to complete it to obtain a valid sequence of brackets of length $ n $ . He is going to pick some strings $ p $ and $ q $ consisting of round brackets and merge them in a string $ p+s+q $ , that is add the string $ p $ at the beginning of the string $ s $ and string $ q $ at the end of the string $ s $ .

Now he wonders, how many pairs of strings $ p $ and $ q $ exists, such that the string $ p+s+q $ is a valid sequence of round brackets. As this number may be pretty large, he wants to calculate it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample there are four different valid pairs:

1. $ p= $ "(", $ q= $ "))"
2. $ p= $ "()", $ q= $ ")"
3. $ p= $ "", $ q= $ "())"
4. $ p= $ "", $ q= $ ")()"

In the second sample the only way to obtain a desired string is choose empty $ p $ and $ q $ .

In the third sample there is no way to get a valid sequence of brackets.

## 样例 #1

### 输入

```
4 1
(
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
(())
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3
(((
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Famil Door和括号

## 题目描述
由于Famil Door的生日即将到来，他的一些朋友（比如Gabi）决定为他买一份礼物。他的朋友们打算买一个由圆括号组成的字符串，因为Famil Door比起其他任何字符串，都更喜欢长度为 $n$ 的括号字符串！

圆括号序列被称为有效的，当且仅当：
1. 左括号的总数等于右括号的总数；
2. 对于序列的任何前缀，左括号的数量大于或等于右括号的数量。

Gabi买了一个长度为 $m$（$m \leq n$）的字符串 $s$，并希望将其补充完整，以获得一个长度为 $n$ 的有效括号序列。他打算挑选一些由圆括号组成的字符串 $p$ 和 $q$，并将它们合并成字符串 $p + s + q$，即在字符串 $s$ 的开头添加字符串 $p$，在字符串 $s$ 的末尾添加字符串 $q$。

现在他想知道，存在多少对字符串 $p$ 和 $q$，使得字符串 $p + s + q$ 是一个有效的括号序列。由于这个数字可能非常大，他希望计算它对 $10^{9}+7$ 取模的结果。

## 说明/提示
在第一个样例中有四对不同的有效组合：
1. $p =$ "(", $q =$ "))"
2. $p =$ "()", $q =$ ")"
3. $p =$ "", $q =$ "())"
4. $p =$ "", $q =$ ")()"

在第二个样例中，获得所需字符串的唯一方法是选择空的 $p$ 和 $q$。

在第三个样例中，没有办法得到一个有效的括号序列。

## 样例 #1
### 输入
```
4 1
(
```
### 输出
```
4
```

## 样例 #2
### 输入
```
4 4
(())
```
### 输出
```
1
```

## 样例 #3
### 输入
```
4 3
(((
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这几道题解思路大致相同，均利用动态规划求解。由于题目给出 $n - m \leq 2000$，基于此进行状态定义和转移。难点在于理解有效括号序列的条件，并据此确定动态规划的状态转移方程以及如何通过枚举 $P$ 和 $Q$ 的相关参数，利用乘法原理计算方案数。题解们都先预处理出动态规划数组 $f$，再通过枚举 $P$ 的长度和其中左括号与右括号数量差，结合 $S$ 串的情况判断能否构造出合法的 $Q$，进而统计方案数。

### 所选的题解
- **作者：火羽白日生 (5星)**
    - **关键亮点**：思路清晰，对动态规划的状态定义、转移方程及后续枚举计算方案数的过程阐述详细，代码注释丰富，可读性强。
    - **重点代码核心实现思想**：通过 `for` 循环递推计算动态规划数组 $f$，再通过两层 `for` 循环枚举 $P$ 的长度和左括号减右括号的数量，根据条件判断并利用乘法原理统计方案数。
    - **核心代码片段**：
```cpp
for(int i=1;i<=2000;i++){//get f
    f[i][0]=f[i-1][1];
    for(int j=1;j<=i;j++)
        f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%mod;
}
for(int i=0;i<=n-m;i++)//for length of P
    for(int j=0;j<=i;j++)//for delta num['(']-num[')'] of P 
        if(j+minn>=0 && j+cnt<=n-m-i)//be sure that num['('] of P and num[')'] of Q are enough
            ans=(ans+1ll*f[i][j]*f[n-m-i][j+cnt]%mod)%mod;
```
- **作者：Anins (4星)**
    - **关键亮点**：题意阐述清晰，对预处理、动态规划及计算结果的步骤描述详细，代码简洁明了。
    - **重点代码核心实现思想**：与上一题解类似，先递推填充动态规划数组 $f$，然后通过两层 `for` 循环枚举 $P$ 的相关参数，根据条件判断并统计方案数。
    - **核心代码片段**：
```cpp
for (int i = 1; i <= 2000; i++) { //枚举长度，依次增加
    f[i][0] = f[i - 1][1]; //(0-1)<0所以无需计算
    for (int  j = 1; j <= i; j++) //枚举'('与')'之差
        f[i][j] = (f[i - 1][j - 1] + f[i - 1][j + 1]) % mod;
}
for (int i = 0; i <= n - m; i++) //枚举P的长度，其中'n-m'指P和Q的总长度
    for (int  j = 0; j <= i; j++) //枚举在P中'('与')'的差
        if (j + minn >= 0 && j + z <= (n - m - i)) 
        /*使P中'('与')'的差能够满足补齐S中少的'(' 且 使构造的Q能使P+S+Q中'('')'数量相等，即Q的长度不小于P+S中'('与')'的差*/
            ans = (ans + (f[i][j] * f[n - m - i][j + z]) % mod) % mod;
```
- **作者：water_tomato (4星)**
    - **关键亮点**：解析部分对动态规划的思路和条件判断分析到位，代码注释详细，便于理解。
    - **重点代码核心实现思想**：同样先计算动态规划数组 $f$，接着通过两层 `for` 循环枚举 $P$ 的情况，依据条件判断并用乘法原理累加方案数。
    - **核心代码片段**：
```cpp
for(int i=1;i<=2000;i++){//保证前缀和满足的情况下的方案数 
    f[i][0]=f[i-1][1];
    for(int j=1;j<=i;j++){
        f[i][j]=(f[i-1][j-1]+f[i-1][j+1])%mod;
    }
}
for(int i=0;i<=n-m;i++){
    for(int j=0;j<=i;j++){
        if(j+minn>=0&&j+tmp<=n-m-i){//左边及给出的串保证前缀符合且前缀不会大到右边补不回来 
            ans=(ans+(f[i][j]*f[n-m-i][j+tmp])%mod)%mod;//逆向思维 
        }
    }
}
```

### 最优关键思路或技巧
1. **状态定义**：定义 $f_{i,j}$ 表示前 $i$ 个字符中左括号数量减去右括号数量为 $j$ 的方案数，这种状态定义巧妙地结合了有效括号序列的条件，方便进行状态转移。
2. **状态转移**：利用 $f_{i,j}=f_{i - 1,j - 1}+f_{i - 1,j + 1}$ 进行状态转移，简洁明了地体现了括号添加的两种情况。
3. **枚举与判断**：通过枚举 $P$ 的长度和其中左括号与右括号数量差，结合 $S$ 串中左右括号数量差的情况，判断能否构造出合法的 $Q$，利用乘法原理统计方案数。

### 拓展思路
同类型题目通常围绕括号匹配及方案数计算，类似算法套路是根据题目条件定义合适的动态规划状态，通过状态转移方程递推求解，再结合条件枚举相关参数计算结果。例如，可能会改变括号序列的定义或添加其他限制条件，但核心思路仍基于动态规划。

### 洛谷相似题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)：通过栈模拟入栈出栈操作，本质上也是关于括号匹配（入栈为左括号，出栈为右括号）的计数问题，与本题思路类似。
2. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：判断给定括号序列是否合法，并求最少添加括号数使其合法，可通过动态规划解决，与本题对括号序列合法性的处理相关。
3. [P2044 [NOI2012] 随机数生成器](https://www.luogu.com.cn/problem/P2044)：涉及到对序列的操作和计数，虽然不是单纯的括号匹配，但动态规划的思想和本题有相通之处，可锻炼动态规划的思维能力。 

---
处理用时：67.93秒