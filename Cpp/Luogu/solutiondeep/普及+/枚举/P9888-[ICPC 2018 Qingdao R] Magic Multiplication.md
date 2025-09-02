# 题目信息

# [ICPC 2018 Qingdao R] Magic Multiplication

## 题目描述

BaoBao 现在正在他的魔法书中学习两个正整数之间的一种新的二进制运算，用 $\otimes$ 表示。这本书告诉他，这种运算的结果是通过将两个整数中每个数字的所有多个结果串联起来计算的。

形式上讲，让第一个整数为 $A=A_1a_2\dots A_n$，其中 $A_i$ 表示 $A$ 中的第 $i$ 位，第二个整数为 $B=B_1b_2\dots B_m$，其中 $B_i$ 表示 $B$ 中的第一位。我们有

$$A \otimes B = \sum\limits_{i=1}^n\sum\limits_{j=1}^m a_ib_j = a_1b_1 + a_1b_2 + \dots + a_1b_m + a_2b_1 + \dots + a_nb_m$$

请注意，$a_ib_j$ 的结果被认为是 $\textbf{string}$（如果 $a_ib_j>0$，则不带前导零，或者如果 $a_ib_j > 0$，则仅包含一个 $0$），而不是正常整数。此外，这里的 sum 表示 $\textbf{string concatenation}$，而不是正常的加法运算。

例如，$23\otimes 45=8101215$。因为 $8=2\times 4$，$10=2\times 5$，$12=3\times 4$ 和 $15=3\times 5$。

BaoBao 很聪明，很快就知道如何做 $\otimes$ 的逆运算。现在，他给出了 $\otimes$ 运算的结果以及两个原始整数中的位数。请帮助他恢复两个原始整数 $A$ 和 $B$。

## 样例 #1

### 输入

```
4
2 2
8101215
3 4
100000001000
2 2
80101215
3 4
1000000010000```

### 输出

```
23 45
101 1000
Impossible
Impossible```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过枚举 $A$ 的首位来确定 $B$ 序列，再由 $B$ 序列反推 $A$ 序列，以此来恢复两个原始整数 $A$ 和 $B$。在枚举过程中，利用两个一位数相乘结果的范围（最小值是 $0$，最大值是 $81$，即乘积长度不超过 $2$）来判断取一位还是两位数字。

各题解的实现细节略有不同，但整体算法框架一致。思路清晰度和代码可读性方面，部分题解存在一些差异，部分题解的注释和变量命名有助于理解，而有些题解则相对缺乏这些辅助信息。

### 所选题解
- **作者：浮光掠影**（4星）
    - **关键亮点**：思路清晰，对判断取一位还是两位数字的逻辑解释详细，代码注释丰富，易于理解。
- **作者：immortal_immortals**（4星）
    - **关键亮点**：思路简洁明了，代码结构清晰，注释能帮助理解关键步骤。
- **作者：zheng_zx**（4星）
    - **关键亮点**：明确指出题目规律，代码实现逻辑清晰，函数模块化程度较高。

### 重点代码
#### 作者：浮光掠影
```cpp
bool getb() {
    int len = strlen(c), pos = 0;
    _for(i, m) {
        if (pos == len) return 0;
        int x = c[pos++] - '0';
        if (pos < len && x && x < a[0]) x = x * 10 + c[pos++] - '0';
        if (x % a[0] || x / a[0] > 9) return 0;
        b[i] = x / a[0];
    }
    _rep(i, 1, n - 1) {
        _for(j, m) {
            if (pos == len) return 0;
            int x = c[pos++] - '0';
            if (pos < len && x && x < b[j]) x = x * 10 + c[pos++] - '0';
            if (x && (b[j] == 0 || j && a[i] == 0)) return 0;
            if (x == 0) {
                if (j && a[i] && b[j]) return 0;
                if (!j) a[i] = 0;
            }
            else {
                if (x % b[j] || j && x / b[j] != a[i] || x / b[j] > 9) return 0;
                a[i] = x / b[j];
            }
        }
    }
    return pos == len;
}
```
**核心实现思想**：该函数用于根据枚举的 $a[0]$ 确定 $B$ 序列，再由 $B$ 序列推导剩余的 $A$ 序列。在推导过程中，根据当前数字与已确定数字的大小关系判断取一位还是两位数字，并进行合法性检查。

#### 作者：immortal_immortals
```cpp
bool GetB() 
{
    int len=strlen(c),pos=0;
    for(int i=0; i<m; i++) 
    {
        if(pos==len)return 0;
        int x=c[pos++]-'0';
        if(pos<len&&x&&x<a[0])x=x*10+c[pos++]-'0';
        if(x%a[0]||x/a[0]>9)return 0;
        b[i]=x/a[0];
    }
    for(int i=1; i<n; i++)
        for(int j=0; j<m; j++) 
        {
            if(pos==len)return 0;
            int x=c[pos++]-'0';
            if(pos<len&&x&&x<b[j])x=x*10+c[pos++]-'0';
            if(x&&(b[j]==0||(j&&a[i]==0)))return 0;
            if(x==0) 
            {
                if(j&&a[i]&&b[j])return 0;
                if(!j)a[i]=0;
            } else {
                if (x%b[j]||j&&x/b[j]!=a[i]||x/b[j]>9) return 0;
                a[i]=x/b[j];
            }
        }
    return pos==len;
}
```
**核心实现思想**：与浮光掠影的 `getb` 函数功能相同，通过枚举 $a[0]$ 确定 $B$ 序列，再由 $B$ 序列推导 $A$ 序列，同时进行合法性检查。

#### 作者：zheng_zx
```cpp
bool set_(int x) {
    a[0] = x, p = 0;
    for(int i = 0; i < nb; ++i) {
        if(p < nc && c[p] % a[0] == 0 && c[p] / a[0] <= 9)
            b[i] = c[p] / a[0], p += 1;
        else if(p + 1 < nc && (c[p] * 10 + c[p + 1]) % a[0] == 0 && (c[p] * 10 + c[p + 1]) / a[0] <= 9)
            b[i] = (c[p] * 10 + c[p + 1]) / a[0], p += 2;
        else return 0;
    }
    return 1;
}
bool check(){
    for(int i = 1; i < na; ++i) {
        if(p < nc && c[p] % b[0] == 0 && c[p] / b[0] <= 9)
            a[i] = c[p] / b[0], p += 1;
        else if(p + 1 < nc && (c[p] * 10 + c[p + 1]) % b[0] == 0 && (c[p] * 10 + c[p + 1]) / b[0] <= 9)
            a[i] = (c[p] * 10 + c[p + 1]) / b[0], p += 2;
        else return 0;
        for(int j = 1; j < nb; ++j) {
            if(p < nc && a[i] * b[j] == c[p])p += 1;
            else if(p + 1 < nc && a[i] * b[j] == c[p] * 10 + c[p + 1])p += 2;
            else return 0;
        }
    }
    return p == nc;
}
```
**核心实现思想**：`set_` 函数根据枚举的 $a[0]$ 确定 $B$ 序列，`check` 函数根据 $B$ 序列推导 $A$ 序列，并检查是否能用完所有的 $C$ 数字。

### 最优关键思路或技巧
- **枚举策略**：通过枚举 $A$ 的首位来确定 $B$ 序列，再由 $B$ 序列反推 $A$ 序列，减少了枚举的复杂度。
- **数字长度判断**：利用两个一位数相乘结果的范围，判断在枚举过程中取一位还是两位数字，避免了回溯。

### 可拓展之处
同类型题或类似算法套路：涉及数字拆分、组合以及根据运算结果反推原始数字的题目。例如，给定一个数的各位数字经过某种运算后的结果，要求恢复原始数字。解题思路可以参考本题，通过枚举部分数字，利用运算规则和数字范围进行推导。

### 推荐题目
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：涉及数字的组合和比较。
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：需要对数字进行拆分和运算，根据结果判断合法性。
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及大整数运算和数字处理。

### 个人心得
题解中未包含个人心得相关内容。

---
处理用时：52.07秒