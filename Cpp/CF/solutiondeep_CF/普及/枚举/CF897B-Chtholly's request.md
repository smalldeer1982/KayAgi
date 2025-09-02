# 题目信息

# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100
```

### 输出

```
33
```

## 样例 #2

### 输入

```
5 30
```

### 输出

```
15
```

# AI分析结果

### 题目中文重写
# 珂朵莉的请求

## 题目描述

——非常感谢你今天的陪伴。——我经历了那么多美好的事情。

——你给了我如梦般的回忆……但现在我不得不离开了……

——最后一个请求，你能……

——帮我解决一道Codeforces的题目吗？

—— ......

——什么？

珂朵莉已经为一个问题苦思多日了：

如果一个数是回文数，并且其十进制表示（无前导零）的长度为偶数，我们称它为zcy数。一个数是回文数意味着当用十进制表示时，它没有前导零，并且正读和反读都相同。例如，12321和1221是回文数，而123和12451不是。此外，1221是zcy数，而12321不是。

给定整数 $k$ 和 $p$，计算最小的 $k$ 个zcy数的和，并输出这个和对 $p$ 取模的结果。

不幸的是， Willem 不擅长解决这类问题，所以他向你寻求帮助！

## 说明/提示
在第一个样例中，最小的zcy数是 $11$，第二小的zcy数是 $22$。

在第二个样例中，[此处原文有图片链接但无法查看内容]。

## 样例 #1
### 输入
```
2 100
```
### 输出
```
33
```

## 样例 #2
### 输入
```
5 30
```
### 输出
```
15
```

### 综合分析与结论
这些题解的核心思路都是通过构造的方式生成zcy数，因为zcy数是由一个整数和它的倒序数拼接而成，且按顺序枚举整数生成的zcy数也是从小到大排列的。

### 算法要点对比
- **构造zcy数**：通过循环枚举整数 $i$，将其倒序后与原数拼接得到zcy数。
- **取模运算**：在累加过程中不断对结果取模，避免溢出。

### 难点对比
- **拼接问题**：部分题解提到要注意拼接时的位数问题，不能简单地用 $i$ 和倒序数的位数计算，而应该用 $i$ 的位数。
- **数据类型**：由于zcy数可能很大，需要使用 `long long` 类型。

### 题解评分与选择
- **chengni（8赞）**：★★★★
    - **关键亮点**：思路清晰，代码简洁，有详细的注释和复杂度分析。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    ll tmp=i;
    int k=i;
    while(k){
        tmp=tmp*10+k%10;
        k/=10;
    }
    sum+=tmp;
    sum%=p;
}
```
核心实现思想：通过循环将整数 $i$ 倒序后与原数拼接得到zcy数，然后累加并取模。

- **XL4453（3赞）**：★★★★
    - **关键亮点**：思路简洁明了，代码规范。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    num=i;
    now=i;
    while(now){
        num*=10;
        num+=now%10;
        now/=10;
    }
    ans=(ans+num%MOD)%MOD;
}
```
核心实现思想：与chengni的思路类似，通过循环构造zcy数并累加取模。

- **fjy666（2赞）**：★★★★
    - **关键亮点**：对拼接问题有详细的分析，给出了时间复杂度分析。
    - **核心代码**：
```cpp
int Reverse(int x){
    int ans = 0;
    while(x){
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return ans;
}
int Log10_(int x){
    int ans = 1;
    while(x){
        ans = ans * 10;
        x /= 10;
    }
    return ans;
}
for(int i=1;i<=k;i++)
    ans = ((ll)ans + (ll)i * Log10_(i) + Reverse(i)) % p;
```
核心实现思想：通过 `Reverse` 函数求倒序数，`Log10_` 函数求 $10^{S(i)}$，然后拼接并累加取模。

### 最优关键思路或技巧
- **构造法**：通过构造的方式生成zcy数，避免了暴力枚举的高复杂度。
- **取模运算**：在累加过程中不断取模，避免溢出。

### 拓展思路
同类型题可以考虑不同进制下的回文数构造，或者对回文数的长度、性质有不同要求的题目。类似算法套路就是通过构造的方式生成满足特定条件的数，然后进行相应的计算。

### 推荐题目
1. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1618 三连击（升级版）](https://www.luogu.com.cn/problem/P1618)
3. [P1015 [NOIP1999 普及组] 回文数](https://www.luogu.com.cn/problem/P1015)

### 个人心得摘录与总结
- **Sai0511**：提到此题是较水的珂朵莉题，还给出了30分的暴力算法和100分的构造算法，总结了不同算法的适用情况。
- **Eason_AC**：提醒代码要用C++14及以上语言提交，否则会WA，强调了不同语言版本对代码的影响。 

---
处理用时：35.55秒