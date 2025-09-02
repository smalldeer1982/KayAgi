# 题目信息

# Little Elephant and Bits

## 题目描述

The Little Elephant has an integer $ a $ , written in the binary notation. He wants to write this number on a piece of paper.

To make sure that the number $ a $ fits on the piece of paper, the Little Elephant ought to delete exactly one any digit from number $ a $ in the binary record. At that a new number appears. It consists of the remaining binary digits, written in the corresponding order (possible, with leading zeroes).

The Little Elephant wants the number he is going to write on the paper to be as large as possible. Help him find the maximum number that he can obtain after deleting exactly one binary digit and print it in the binary notation.

## 说明/提示

In the first sample the best strategy is to delete the second digit. That results in number $ 11_{2}=3_{10} $ .

In the second sample the best strategy is to delete the third or fourth digits — that results in number $ 11010_{2}=26_{10} $ .

## 样例 #1

### 输入

```
101
```

### 输出

```
11
```

## 样例 #2

### 输入

```
110010
```

### 输出

```
11010
```

# AI分析结果

### 题目内容
# 小象与二进制位

## 题目描述
小象有一个用二进制表示的整数 $a$ 。它想把这个数写在一张纸上。
为了确保数字 $a$ 能写在纸上，小象必须从数字 $a$ 的二进制表示中恰好删除任意一位。这样就会出现一个新数字。这个新数字由剩余的二进制位按相应顺序组成（可能有前导零）。
小象希望写在纸上的数字尽可能大。帮助它找出删除恰好一位二进制位后能得到的最大数字，并以二进制表示打印出来。

## 说明/提示
在第一个样例中，最佳策略是删除第二位。结果数字为 $11_{2}=3_{10}$ 。
在第二个样例中，最佳策略是删除第三位或第四位——结果数字为 $11010_{2}=26_{10}$ 。

## 样例 #1
### 输入
```
101
```
### 输出
```
11
```

## 样例 #2
### 输入
```
110010
```
### 输出
```
11010
```

### 算法分类
贪心

### 综合分析与结论
所有题解的核心思路均为贪心策略，即通过删除二进制数中的某一位来获取最大数。要点在于若二进制数中存在0，删除第一个0可使剩余数字最大；若全为1，则删除最后一位（或任意一位）。解决的难点在于理解为何删除第一个0（或全1时删除最后一位）能使结果最大，这基于对二进制数权值的理解。

### 所选的题解
- **作者：159号程序员 (5星)**
    - **关键亮点**：思路清晰，先阐述原理，即删除数位最大且是0的数能使左边1移位后最大，再给出代码实现，通过遍历字符串找到第一个0并删除，同时考虑全1字符串的特判。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '0' || i == s.length() - 1) 
        {
            s.erase(i, 1); 
            break;
        }
    }
    cout << s;
    return 0;
}
```
核心实现思想：遍历字符串，若找到0或到达字符串末尾，删除当前位置字符并结束循环，输出结果。
- **作者：DPseud (4星)**
    - **关键亮点**：简洁明了，直接阐述题目意思和贪心思路，即删除最高位的0，利用string的find函数查找0，代码简洁高效。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    getline(cin,s);
    if(s.find('0')!=-1)s.erase(s.find('0'),1);
    else s.erase(s.length()-1,1);
    cout<<s;
    return 0;
}
```
核心实现思想：使用find函数查找0，若找到则删除该位置0，否则删除最后一位，输出结果。
- **作者：Yukinoshita_Yukino (4星)**
    - **关键亮点**：详细分析有0和全1两种情况的贪心策略原理，同时指出使用字符数组和`strlen`函数可能导致TLE，推荐使用string和其成员函数的AC代码。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int f=0;
int main()
{
    cin>>str;
    for(int i=0;i<str.length();i++) if((i==str.length()-1||str[i]=='0')&&f==0) str.erase(i,1),f=1;
    cout<<str;
    return 0;
}
```
核心实现思想：遍历字符串，若找到0或到达末尾且未删除过字符，删除当前位置字符并标记已处理，输出结果。

### 最优关键思路或技巧
理解二进制数权值，采用贪心策略，优先删除最高位的0（全1时删除任意一位）。在代码实现上，使用string类及其成员函数（如`find`、`erase`）可使代码简洁高效。

### 可拓展之处
同类型题通常围绕数字操作，通过删除、添加或修改数位来获取最值。类似算法套路是基于数制的权值特点进行贪心选择。

### 推荐题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：给定一个高精度正整数，删除指定个数数字后求最小数，同样运用贪心策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对皇后属性排序，运用贪心策略解决问题，与本题思路类似。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：根据左右大臣的乘积排序，利用贪心思想求出最小数。 

---
处理用时：42.56秒