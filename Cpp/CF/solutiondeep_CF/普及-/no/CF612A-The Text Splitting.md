# 题目信息

# The Text Splitting

## 题目描述

You are given the string $ s $ of length $ n $ and the numbers $ p,q $ . Split the string $ s $ to pieces of length $ p $ and $ q $ .

For example, the string "Hello" for $ p=2 $ , $ q=3 $ can be split to the two strings "Hel" and "lo" or to the two strings "He" and "llo".

Note it is allowed to split the string $ s $ to the strings only of length $ p $ or to the strings only of length $ q $ (see the second sample test).

## 样例 #1

### 输入

```
5 2 3
Hello
```

### 输出

```
2
He
llo
```

## 样例 #2

### 输入

```
10 9 5
Codeforces
```

### 输出

```
2
Codef
orces
```

## 样例 #3

### 输入

```
6 4 5
Privet
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
8 1 1
abacabac
```

### 输出

```
8
a
b
a
c
a
b
a
c
```

# AI分析结果

### 题目内容（中文重写）
# 文本分割

## 题目描述
给定长度为 $n$ 的字符串 $s$ 以及数字 $p$、$q$ ，将字符串 $s$ 分割成长度为 $p$ 和 $q$ 的片段。

例如，对于字符串 "Hello"，当 $p = 2$，$q = 3$ 时，可以分割成两个字符串 "Hel" 和 "lo"，也可以分割成两个字符串 "He" 和 "llo"。

注意，允许将字符串 $s$ 仅分割成长度为 $p$ 的字符串，或者仅分割成长度为 $q$ 的字符串（见第二个样例测试）。

## 样例 #1
### 输入
```
5 2 3
Hello
```
### 输出
```
2
He
llo
```

## 样例 #2
### 输入
```
10 9 5
Codeforces
```
### 输出
```
2
Codef
orces
```

## 样例 #3
### 输入
```
6 4 5
Privet
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
8 1 1
abacabac
```
### 输出
```
8
a
b
a
c
a
b
a
c
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举来找到满足条件的分割方案，即找到非负整数 $x$ 和 $y$，使得 $xp + yq = n$，其中 $x$ 表示长度为 $p$ 的子串个数，$y$ 表示长度为 $q$ 的子串个数。

- **思路对比**：大部分题解是枚举长度为 $p$ 的子串个数 $i$，然后判断剩余长度是否能被 $q$ 整除；djh233 的题解是双重枚举长度为 $p$ 和 $q$ 的子串个数。
- **算法要点**：枚举过程中，一旦找到满足条件的 $x$ 和 $y$，就可以按照对应的长度进行字符串的分割和输出；若枚举完都没有找到，则输出 -1。
- **解决难点**：主要难点在于换行的处理，不同题解采用了不同的方式来确保输出格式正确。

### 题解评分
- linyihdfj：4星。思路清晰，代码简洁，对换行的处理有提示。
- Otue：3星。提供了两种实现方式，但代码结构稍显复杂。
- i_dont_know_who_am_i：3星。思路明确，代码有注释，但部分变量命名可优化。
- hxhhxh：3星。使用字符数组存储字符串，实现了基本功能。
- djh233：2星。思路有波折，时间复杂度较高，代码较复杂。

### 所选题解
- linyihdfj（4星）
  - 关键亮点：思路清晰，代码简洁，对换行处理有提示。
  - 个人心得：无

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,p,q,l = -1,r = -1;
    string s;
    cin>>n>>p>>q;
    cin>>s;
    for(int i=0; i<=n; i++){
        if(n >= i * p && (n - i * p) % q == 0){
            l = i;
            r = (n - l * p) / q;
            break;
        }
    } 
    if(l == -1 || r == -1){
        cout<<-1<<endl;
        return 0;
    }
    printf("%d\n",l + r);
    bool flag = false;
    for(int i=0; i<l * p; i++){
        if(i % p == 0 && i != 0)
            printf("\n");
        cout<<s[i];
        flag = true;
    }
    if(flag)
        cout<<endl;
    for(int i=0; i<r * q; i++){
        if(i % q == 0 && i != 0)
            cout<<endl;
        cout<<s[i + l * p];
    }
    return 0;
}
```
**核心实现思想**：先枚举长度为 $p$ 的子串个数 $i$，找到满足条件的 $i$ 后计算出长度为 $q$ 的子串个数 $r$。若能找到则按要求输出分割后的子串，否则输出 -1。

### 可拓展之处
同类型题可能会增加更多的限制条件，如要求分割方案的数量、找到字典序最小的分割方案等。类似算法套路就是通过枚举来解决不定方程的非负整数解问题，然后根据解来进行相应的构造或计算。

### 推荐洛谷题目
1. P1036 选数：通过枚举组合来解决问题。
2. P1157 组合的输出：枚举所有组合情况。
3. P2089 烤鸡：通过枚举各种配料的选择情况来得到所有方案。

### 个人心得摘录与总结
djh233：一开始想用扩欧判断是否有解并求 $px + qy = n$ 的一组解，但没考虑到会有负解的情况，后来对负解进行魔改也过不了，最后发现数据范围小，直接暴力枚举。总结是做题时不能鲁莽，要充分考虑数据范围，避免使用复杂且不适用的算法。 

---
处理用时：32.87秒