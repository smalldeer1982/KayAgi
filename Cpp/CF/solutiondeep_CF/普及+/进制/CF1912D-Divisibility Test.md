# 题目信息

# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0```

# AI分析结果

### 题目内容中文重写
# 整除性测试

## 题目描述
黛西最近学习了整数的整除性规则，她对此非常着迷。她学到的其中一个测试是被 3 整除的测试。你可以求出一个十进制数所有数位的和，然后检查得到的和是否能被 3 整除。此外，得到的数位和与原数对 3 取模同余 —— 对 3 取模的余数保持不变。例如，$75 \equiv 7 + 5 \pmod 3$。黛西对这种保持余数的整除性测试特别感兴趣。

她还学习了十进制整数（以 10 为基数的整数）的其他类似例子：
- 要测试对 11 取模的整除性，求数位的交替和。从最后一位（最低有效位）开始计数，将奇数位置（最后一位、倒数第三位等）的数位相加，减去偶数位置（倒数第二位、倒数第四位等）的数位，得到的和与原数对 11 取模同余。例如，$123 \equiv 1 - 2 + 3 \pmod {11}$。
- 要测试对 4 取模的整除性，保留最后两位。它们的值与原数对 4 取模同余。例如，$876543 \equiv 43 \pmod 4$。
- 要测试对 7 取模的整除性，求三位一组的交替和。例如，$4389328 \equiv 4 - 389 + 328 \pmod 7$。

在其他进制中也可以找到类似的测试。例如，要测试八进制数（以 8 为基数）对 5 取模的整除性，求两位一组的交替和。例如，$1234_8 \equiv -12_8 + 34_8 \pmod 5$。

黛西想为给定的基数 $b$ 找到这样的规则。她对三种整除性规则感兴趣：
- 类型 1 —— 取以 $b$ 为基数的整数的最后 $k$ 位。
- 类型 2 —— 取以 $b$ 为基数的整数的 $k$ 位一组的和。
- 类型 3 —— 取以 $b$ 为基数的整数的 $k$ 位一组的交替和。

并不总是能找到这样的整除性规则。例如，在十进制中，不存在对 6 取模的这样的测试，尽管存在不同的测试被 6 整除的方法。

给定基数 $b$ 和模数 $n$，黛西想知道存在这样的整除性测试的最小组大小 $k$。

## 样例 #1
### 输入
```
6
10 3
10 11
10 4
10 7
8 5
10 6
```
### 输出
```
2 1
3 1
1 2
3 3
3 2
0
```

### 综合分析与结论
这些题解的核心思路都是通过枚举 $k$ 值，依据不同整除性规则对应的数学条件来判断是否存在满足要求的最小 $k$ 值。
- **思路**：均围绕三种整除性规则展开，通过计算 $b^k \bmod n$ 的值，根据其结果判断属于哪种规则，若符合则输出对应结果，若枚举完都不符合则判定无解。
- **算法要点**：关键在于对三种整除性规则的数学条件的运用，即 $b^k\bmod n=0$（取最后 $k$ 位）、$b^k\bmod n=1$（$k$ 位一组求和）、$b^k\bmod n=n - 1$（$k$ 位一组求交叉和）。
- **解决难点**：主要是对三种整除性规则的数学原理的理解和证明，以及在枚举过程中对无解情况的判断。

### 题解评分
- **FFTotoro**：4 星。思路清晰，对三种操作实质有明确阐述和证明，代码简洁易懂。
- **Special_Tony**：3 星。思路合理，但使用 `goto` 语句影响代码可读性，且对判断循环的处理增加了复杂度。
- **OIer_Hhy**：3 星。对三种规则的数学原理有详细推导，但代码整体中规中矩。
- **Robin_kool**：3 星。对三种情况有证明，但自定义输入输出函数增加了代码复杂度。

### 所选题解
- **FFTotoro**：4 星。关键亮点在于思路清晰，对三种操作的实质有明确的阐述和证明，代码简洁，直接枚举 $k$ 值进行判断。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int b,n; cin>>b>>n;
    long long c=1; bool f=false;
    for(int k=1;k<=n&&!f;k++){
      if((c*=b)%=n;!c)cout<<"1 "<<k<<'\n',f=true;
      if(c==1)cout<<"2 "<<k<<'\n',f=true;
      else if(c==n-1)cout<<"3 "<<k<<'\n',f=true;
    }
    if(!f)cout<<"0\n"; // 无解
  }
  return 0;
}
```
**核心实现思想**：通过循环枚举 $k$ 从 1 到 $n$，计算 $b^k \bmod n$ 的值，根据其结果判断是否满足三种整除性规则中的一种，若满足则输出对应结果并标记已找到解，若枚举完都未找到则输出 0 表示无解。

### 最优关键思路或技巧
- 利用数学原理，将三种整除性规则转化为 $b^k \bmod n$ 的不同取值条件，通过枚举 $k$ 值进行判断。
- 由于 $k$ 最大为 $n$，所以可以直接枚举 $k$ 从 1 到 $n$，减少不必要的计算。

### 可拓展之处
同类型题目可能会有更多种类的整除性规则或者不同进制下更复杂的情况。类似算法套路可用于解决其他基于数学规则的判断问题，如判断一个数是否满足特定的数字特征等。

### 推荐洛谷题目
- P1014 [NOIP1999 普及组] Cantor 表
- P1045 [NOIP2003 普及组] 麦森数
- P1069 [NOIP2009 普及组] 细胞分裂

### 个人心得摘录与总结
- **OIer_Hhy**：“又是一道水绿。刚刚小学毕业的数学 idiot——我释怀地笑了”，表达了对题目难度的轻松态度，暗示该题与小学奥数知识相关，做起来比较得心应手。 

---
处理用时：42.36秒