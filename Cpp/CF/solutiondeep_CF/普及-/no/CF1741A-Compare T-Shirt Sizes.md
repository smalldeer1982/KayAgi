# 题目信息

# Compare T-Shirt Sizes

## 题目描述

Two T-shirt sizes are given: $ a $ and $ b $ . The T-shirt size is either a string M or a string consisting of several (possibly zero) characters X and one of the characters S or L.

For example, strings M, XXL, S, XXXXXXXS could be the size of some T-shirts. And the strings XM, LL, SX are not sizes.

The letter M stands for medium, S for small, L for large. The letter X refers to the degree of size (from eXtra). For example, XXL is extra-extra-large (bigger than XL, and smaller than XXXL).

You need to compare two given sizes of T-shirts $ a $ and $ b $ .

The T-shirts are compared as follows:

- any small size (no matter how many letters X) is smaller than the medium size and any large size;
- any large size (regardless of the number of letters X) is larger than the medium size and any small size;
- the more letters X before S, the smaller the size;
- the more letters X in front of L, the larger the size.

For example:

- XXXS &lt; XS
- XXXL &gt; XL
- XL &gt; M
- XXL = XXL
- XXXXXS &lt; M
- XL &gt; XXXS

## 样例 #1

### 输入

```
6
XXXS XS
XXXL XL
XL M
XXL XXL
XXXXXS M
L M```

### 输出

```
<
>
>
=
<
>
```

# AI分析结果

### 题目内容
# 比较T恤尺码

## 题目描述
给定两个T恤尺码：$a$ 和 $b$ 。T恤尺码要么是字符串 “M”，要么是由几个（可能为零个）字符 “X” 和字符 “S” 或 “L” 中的一个组成的字符串。

例如，字符串 “M”、“XXL”、“S”、“XXXXXXXS” 可能是某些T恤的尺码。而字符串 “XM”、“LL”、“SX” 则不是尺码。

字母 “M” 代表中码，“S” 代表小码，“L” 代表大码。字母 “X” 表示尺码的程度（来自 “extra”）。例如，“XXL” 是特大号（比 “XL” 大，比 “XXXL” 小）。

你需要比较给定的两个T恤尺码 $a$ 和 $b$ 。

T恤的比较规则如下：
- 任何小码（无论有多少个字母 “X”）都小于中码和任何大码；
- 任何大码（无论有多少个字母 “X”）都大于中码和任何小码；
- “S” 前面的字母 “X” 越多，尺码越小；
- “L” 前面的字母 “X” 越多，尺码越大。

例如：
- “XXXS” < “XS”
- “XXXL” > “XL”
- “XL” > “M”
- “XXL” = “XXL”
- “XXXXXS” < “M”
- “XL” > “XXXS”

## 样例 #1
### 输入
```
6
XXXS XS
XXXL XL
XL M
XXL XXL
XXXXXS M
L M
```
### 输出
```
<
>
>
=
<
>
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是依据题目给定的比较规则对两个T恤尺码进行比较。主要区别在于实现方式和代码结构。
1. **思路方面**：多数题解先判断两个尺码的最后一个字符，若相同，再根据是 “S” 还是 “L” 来比较前面 “X” 的数量（通过字符串长度体现）；若不同，则直接按 “S<M<L” 的规则判断。flying_man 的题解则是通过给每个尺码赋予一个数值来比较大小。
2. **算法要点**：重点在于准确理解并实现题目中的比较规则，处理好不同类型尺码（“S”、“M”、“L” 结尾）的比较逻辑。
3. **解决难点**：难点在于清晰梳理各种情况，避免遗漏或混淆比较规则，尤其是在处理同类尺码（如都是 “S” 结尾或都是 “L” 结尾）时对 “X” 数量的比较。

### 所选的题解
- **作者：flying_man (5星)**
    - **关键亮点**：思路独特，通过给每个尺码赋予一个数值来简化比较过程，代码简洁明了，逻辑清晰。
    - **重点代码核心实现思想**：根据尺码的最后一个字符确定数值的正负（“M” 为0，“S” 为负，“L” 为正），字符串长度决定数值的绝对值，最后比较两个数值大小。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,z1,z2;
char s1[105],s2[105];
int main(){
    cin >> t;
    while(t--){
        cin >> s1 >> s2;
        int len1 = strlen(s1),len2 = strlen(s2);
        if(s1[len1-1] == 'M') z1 = 0;
        if(s1[len1-1] == 'S') z1 = -len1;
        if(s1[len1-1] == 'L') z1 = len1;
        if(s2[len2-1] == 'M') z2 = 0;
        if(s2[len2-1] == 'S') z2 = -len2;
        if(s2[len2-1] == 'L') z2 = len2;
        if(z1 < z2) printf("<\n");
        if(z1 == z2) printf("=\n");
        if(z1 > z2) printf(">\n");
    }
    return 0;
}
```
- **作者：Dry_ice (4星)**
    - **关键亮点**：将尺码分类为 “S”、“M”、“L” 三类，先判断是否为同类尺码，再分别处理异类和同类的比较情况，思路清晰，代码结构较为合理。
    - **重点代码核心实现思想**：先根据最后一个字符判断是否为同类尺码，异类尺码直接比较末字符所指向的类别；同类尺码则通过比较字符串长度（即 “X” 的数量）来确定大小。
```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
string a, b;
int ch[250];
int main(void) {
    ch['S'] = 0, ch['M'] = 1, ch['L'] = 2;
    int t; for (cin >> t; t--; ) {
        cin >> a >> b; int n = a.length(), m = b.length(); --n, --m;
        if (a[n] == 'M') {
            if (b[m] == 'M') puts("=");
            if (b[m] == 'S') puts(">");
            if (b[m] == 'L') puts("<");
            continue;
        }
        if (a[n] == 'L' && b[m]!= 'L') {
            puts(">"); continue;
        }
        if (a[n] == 'S' && b[m]!= 'S') {
            puts("<"); continue;
        }
        //以上为异类
        //以下为同类
        if (a[n] == 'S') {
            if (n > m) puts("<");
            if (n == m) puts("=");
            if (n < m) puts(">");
            continue;
        }
        if (a[n] == 'L') {
            if (n > m) puts(">");
            if (n == m) puts("=");
            if (n < m) puts("<");
        }
    }
    return 0;
}
```
- **作者：BlackPanda (4星)**
    - **关键亮点**：思路直接，先特判尺码是否相等，然后取出最后一个字符确定尺寸类型，再枚举计算 “X” 的个数，最后按规则分类讨论，代码逻辑较清晰。
    - **重点代码核心实现思想**：先判断两个尺码字符串是否相等，若不相等，取出最后字符确定尺寸类型，统计 “X” 的个数，根据尺寸类型相同与否和 “X” 的个数比较大小。
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s1, s2;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> s1 >> s2;
        if (s1 == s2)
        {
            cout << "=\n";
        }
        else
        {
            char c1 = s1[s1.length()-1];
            char c2 = s2[s2.length()-1];
            int r1=0, r2=0;
            for (int i = 0; i < s1.length(); i ++ )
                if (s1[i] == 'X')   r1 ++ ;
            for (int i = 0; i < s2.length(); i ++ )
                if (s2[i] == 'X')   r2 ++ ;
            if (c1 == c2)
            {
                if (c1 == 'S')
                {
                    if (r1 > r2)    cout << "<\n";
                    else cout << ">\n";
                }
                else
                {
                    if (r1 < r2)    cout << "<\n";
                    else cout << ">\n";
                }
            }
            else
            {
                if ((c1=='M'&&c2=='S')||(c1=='L'&&c2=='M')||(c1=='L'&&c2=='S'))
                    cout << ">\n";
                else   
                    cout << "<\n";
            }
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
flying_man 通过给每个尺码赋予一个数值来比较大小的方法较为巧妙，简化了比较逻辑，减少了分类讨论的复杂度，在代码实现上更为简洁高效。这种思维方式将字符串比较问题转化为数值比较问题，值得借鉴。

### 拓展
此类题目属于简单模拟类型，类似题目通常会给出一些特定规则，要求按照规则对数据进行处理或比较。解题时关键在于准确理解规则，并清晰地梳理各种情况，避免遗漏或错误。

### 推荐洛谷题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：根据特定规则校验ISBN号码，涉及字符串处理和简单计算。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：按照不同包装铅笔的价格和数量，计算购买一定数量铅笔的最小花费，需要根据给定规则进行模拟计算。
- [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)：根据小鱼开始和结束游泳的时间，按照时间计算规则得出游泳时长，属于简单模拟题。 

---
处理用时：68.43秒