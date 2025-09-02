# 题目信息

# String Mark

## 题目描述

At the Byteland State University marks are strings of the same length. Mark $ x $ is considered better than $ y $ if string $ y $ is lexicographically smaller than $ x $ .

Recently at the BSU was an important test work on which Vasya recived the mark $ a $ . It is very hard for the teacher to remember the exact mark of every student, but he knows the mark $ b $ , such that every student recieved mark strictly smaller than $ b $ .

Vasya isn't satisfied with his mark so he decided to improve it. He can swap characters in the string corresponding to his mark as many times as he like. Now he want to know only the number of different ways to improve his mark so that his teacher didn't notice something suspicious.

More formally: you are given two strings $ a $ , $ b $ of the same length and you need to figure out the number of different strings $ c $ such that:

1\) $ c $ can be obtained from $ a $ by swapping some characters, in other words $ c $ is a permutation of $ a $ .

2\) String $ a $ is lexicographically smaller than $ c $ .

3\) String $ c $ is lexicographically smaller than $ b $ .

For two strings $ x $ and $ y $ of the same length it is true that $ x $ is lexicographically smaller than $ y $ if there exists such $ i $ , that $ x_{1}=y_{1},x_{2}=y_{2},...,x_{i-1}=y_{i-1},x_{i}<y_{i} $ .

Since the answer can be very large, you need to find answer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample from string $ abc $ can be obtained strings $ acb,bac,bca,cab,cba $ , all of them are larger than $ abc $ , but smaller than $ ddd $ . So the answer is $ 5 $ .

In second sample any string obtained from $ abcdef $ is larger than $ abcdeg $ . So the answer is $ 0 $ .

## 样例 #1

### 输入

```
abc
ddd
```

### 输出

```
5
```

## 样例 #2

### 输入

```
abcdef
abcdeg
```

### 输出

```
0
```

## 样例 #3

### 输入

```
abacaba
ubuduba
```

### 输出

```
64
```

# AI分析结果

### 题目内容
# 字符串分数

## 题目描述
在比特兰德州立大学，分数是长度相同的字符串。如果字符串 $y$ 在字典序上小于 $x$，则认为分数 $x$ 优于 $y$。

最近在BSU进行了一次重要的测试作业，瓦夏得到了分数 $a$。老师很难记住每个学生的确切分数，但他知道分数 $b$，每个学生得到的分数都严格小于 $b$。

瓦夏对自己的分数不满意，所以他决定提高分数。他可以随意多次交换与他分数对应的字符串中的字符。现在他只想知道，在不引起老师怀疑的情况下提高分数的不同方法的数量。

更正式地说：给定两个长度相同的字符串 $a$ 和 $b$，你需要找出满足以下条件的不同字符串 $c$ 的数量：
1. $c$ 可以通过交换 $a$ 中的某些字符得到，换句话说，$c$ 是 $a$ 的一个排列。
2. 字符串 $a$ 在字典序上小于 $c$。
3. 字符串 $c$ 在字典序上小于 $b$。

对于两个长度相同的字符串 $x$ 和 $y$，如果存在这样的 $i$，使得 $x_1 = y_1, x_2 = y_2, \cdots, x_{i - 1} = y_{i - 1}, x_i < y_i$，则称 $x$ 在字典序上小于 $y$。

由于答案可能非常大，你需要求出答案对 $10^9 + 7$ 取模的结果。

## 说明/提示
在第一个样例中，从字符串 $abc$ 可以得到字符串 $acb, bac, bca, cab, cba$，它们都大于 $abc$，但小于 $ddd$。所以答案是 $5$。

在第二个样例中，从 $abcdef$ 得到的任何字符串都大于 $abcdeg$。所以答案是 $0$。

## 样例 #1
### 输入
```
abc
ddd
```
### 输出
```
5
```
## 样例 #2
### 输入
```
abcdef
abcdeg
```
### 输出
```
0
```
## 样例 #3
### 输入
```
abacaba
ubuduba
```
### 输出
```
64
```

### 算法分类
组合数学

### 综合分析与结论
该题解的核心思路是将原问题转化为求用已有字符构建的字符串在字典序上小于给定字符串的个数问题。通过维护当前可用字符生成的不同字符串个数，利用组合数学的知识，结合逆元计算，分别求出字典序小于 $b$ 和小于 $a$ 的字符串个数，二者相减再减 $1$ 得到最终结果。其难点在于理解如何通过字典序变化点和字符集的枚举来计算满足条件的字符串个数，以及逆元在计算中的运用。

### 题解
- **作者：fisheep (星级：4星)**
  - **关键亮点**：巧妙地将原问题转化为计算字典序小于给定字符串的字符串个数问题，通过维护中间变量 $cur$ 简化计算过程，利用逆元解决组合数计算中的取模问题。
  - **个人心得**：吐槽翻译未明确给出 $mod$。
  - **核心代码片段**：
```cpp
int f1(char *s){
    memcpy(c,cnt,sizeof c);
    int cur=f[n];
    for(int i=0;i<26;i++){
        if(c[i])
            cur=1ll*cur*rf[c[i]]%mod;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int x=0;x<s[i]-'a';x++){
            if(c[x]){
                int now=cur;
                now=1ll*now*sr[n-i+1]%mod;
                now=1ll*now*c[x]%mod;
                ans=(ans+now)%mod;
            }
        }
        if(c[s[i]-'a']){
            cur=(ll)cur*sr[n-i+1]%mod;
            cur=(ll)cur*c[s[i]-'a']%mod;
            c[s[i]-'a']--;
        }else{
            break;
        }
    }
    return ans;
}

int rev(int a){
    int ret=1;
    for(int b=mod-2;b;b>>=1,a=(ll)a*a%mod)
        if(b&1)
            ret=(ll)ret*a%mod;
    return ret;
}
```
核心实现思想：`f1` 函数用于计算字典序小于字符串 `s` 的字符串个数。首先初始化 `cur` 为所有字符全排列的个数，然后通过双重循环，外层循环枚举字符串位置，内层循环枚举比当前位置字符小的字符，计算满足条件的字符串个数并累加到 `ans` 中。`rev` 函数用于计算逆元，在组合数计算中用于取模运算。

### 最优关键思路或技巧
1. **问题转化**：将原问题转化为计算字典序小于给定字符串的字符串个数，简化了对字典序条件的处理。
2. **逆元计算**：在组合数计算中，通过计算逆元解决取模运算问题，保证结果的正确性。

### 可拓展之处
同类型题通常围绕字符串的排列组合以及字典序相关条件展开。类似算法套路包括利用组合数学知识解决字符串排列相关问题，在计算过程中合理使用逆元处理取模运算。

### 洛谷相似题目
1. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)
2. [P2615 [NOIP2015 提高组] 神奇的幻方](https://www.luogu.com.cn/problem/P2615)
3. [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)

---
处理用时：44.90秒