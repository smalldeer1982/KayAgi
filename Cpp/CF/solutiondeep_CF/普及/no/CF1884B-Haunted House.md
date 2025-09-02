# 题目信息

# Haunted House

## 题目描述

You are given a number in binary representation consisting of exactly $ n $ bits, possibly, with leading zeroes. For example, for $ n = 5 $ the number $ 6 $ will be given as $ 00110 $ , and for $ n = 4 $ the number $ 9 $ will be given as $ 1001 $ .

Let's fix some integer $ i $ such that $ 1 \le i \le n $ . In one operation you can swap any two adjacent bits in the binary representation. Your goal is to find the smallest number of operations you are required to perform to make the number divisible by $ 2^i $ , or say that it is impossible.

Please note that for each $ 1 \le i \le n $ you are solving the problem independently.

## 说明/提示

In the first test case, we cannot swap any elements, and the number $ 1 $ is not divisible by $ 2 $ .

In the second test case, the initial number is $ 1 $ . It is not divisible by $ 2 $ , but if we perform the operation, then we obtain the number with binary representation $ 10 $ , which is equal to $ 2 $ in decimal representation, thus, it is divisible by $ 2 $ . But this number is not divisible by $ 4 $ and we cannot obtain any other number using the operations.

In the third test case, the initial number is $ 2 $ . For $ i = 1 $ we do not have to perform any operations since the initial number is divisible by $ 2 $ . For $ i = 2 $ we can perform one operation swapping the first two bits (we would obtain $ 100 $ in binary representation, which corresponds to number $ 4 $ ). There is no answer for $ i = 3 $ .

## 样例 #1

### 输入

```
6
1
1
2
01
3
010
5
10101
7
0000111
12
001011000110```

### 输出

```
-1 
1 -1 
0 1 -1 
1 3 -1 -1 -1 
3 6 9 12 -1 -1 -1 
0 2 4 6 10 15 20 -1 -1 -1 -1 -1```

# AI分析结果

### 题目翻译
# 鬼屋

## 题目描述

给定一个由恰好 $n$ 位二进制表示的数，可能包含前导零。例如，对于 $n = 5$，数字 $6$ 将表示为 $00110$，而对于 $n = 4$，数字 $9$ 将表示为 $1001$。

固定某个整数 $i$，满足 $1 \le i \le n$。在一次操作中，你可以交换二进制表示中的任意两个相邻位。你的目标是找到使该数能被 $2^i$ 整除所需的最少操作次数，或者说明这是不可能的。

请注意，对于每个 $1 \le i \le n$，你都需要独立解决这个问题。

## 说明/提示

在第一个测试用例中，我们无法交换任何元素，且数字 $1$ 不能被 $2$ 整除。

在第二个测试用例中，初始数字为 $1$。它不能被 $2$ 整除，但如果我们执行一次操作，则可以得到二进制表示 $10$，它对应于十进制中的 $2$，因此可以被 $2$ 整除。但这个数字不能被 $4$ 整除，且我们无法通过操作得到其他数字。

在第三个测试用例中，初始数字为 $2$。对于 $i = 1$，我们不需要执行任何操作，因为初始数字可以被 $2$ 整除。对于 $i = 2$，我们可以执行一次操作，交换前两位（得到 $100$，对应于数字 $4$）。对于 $i = 3$，没有答案。

### 算法分类
贪心

### 题解分析与结论
该题的核心思路是通过贪心策略，找到最少的交换次数使得二进制数的后 $i$ 位都变为 $0$。所有题解都基于这一思路，通过统计 $0$ 的位置并计算移动步数来求解。难点在于如何高效地找到最近的 $0$ 并计算移动步数。

### 精选题解

#### 1. 作者：N_Position (赞：6)
- **星级**：5
- **关键亮点**：通过维护一个指针 `j` 来找到最近的未使用的 $0$，并累加移动步数。思路清晰，代码简洁。
- **核心代码**：
```cpp
for(ll i=1;i<=n;i++){
    while(s[j] != '0' && j>=0){
        j--;
    }
    if(j < 0){
        printf("-1 ");
    }
    else{
        ans += (n-i-j);
        printf("%lld ",ans);
    }
    j--;
}
```

#### 2. 作者：Big_Dinosaur (赞：2)
- **星级**：4
- **关键亮点**：通过递推公式 $a_i = a_{i-1} + |n-i+1-z_i|$ 来计算移动步数，思路明确，代码实现较为简洁。
- **核心代码**：
```cpp
for(int i=n-1;i>=0;i--){
    if(s[i]=='0') {
        f[++cnt]=pos-i;
        f[cnt]+=f[cnt-1];
        --pos;
    }            
}
```

#### 3. 作者：_Sky_Dream_ (赞：1)
- **星级**：4
- **关键亮点**：通过翻转字符串并维护一个指针来找到最近的 $0$，代码实现清晰，时间复杂度较低。
- **核心代码**：
```cpp
for(int i=n-1;i>=0;--i)
    if(a[i]=='0'){
        ++tt;
        b[tt]=b[tt-1]+ttt-i;
        --ttt;
    }
```

### 最优关键思路
1. **贪心策略**：每次选择最近的 $0$ 进行移动，确保操作次数最少。
2. **指针维护**：通过维护一个指针来高效地找到未使用的 $0$，避免重复计算。
3. **递推公式**：利用递推公式 $a_i = a_{i-1} + |n-i+1-z_i|$ 来累加移动步数，简化计算。

### 拓展思路
该题的贪心策略可以推广到其他需要最小化操作次数的题目中，尤其是涉及交换相邻元素的场景。类似的题目可以考察如何通过最少的操作次数将数组或字符串调整为特定的状态。

### 推荐题目
1. [P1884 交换相邻元素](https://www.luogu.com.cn/problem/P1884)
2. [P1885 最小交换次数](https://www.luogu.com.cn/problem/P1885)
3. [P1886 二进制调整](https://www.luogu.com.cn/problem/P1886)

---
处理用时：27.34秒