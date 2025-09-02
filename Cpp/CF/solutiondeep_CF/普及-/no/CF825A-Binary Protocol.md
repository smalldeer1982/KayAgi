# 题目信息

# Binary Protocol

## 题目描述

Polycarp has just invented a new binary protocol for data transmission. He is encoding positive integer decimal number to binary string using following algorithm:

- Each digit is represented with number of '1' characters equal to the value of that digit (for 0 it is zero ones).
- Digits are written one by one in order corresponding to number and separated by single '0' character.

Though Polycarp learnt how to encode the numbers, he has no idea how to decode them back. Help him calculate the decoded number.

## 样例 #1

### 输入

```
3
111
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9
110011101
```

### 输出

```
2031
```

# AI分析结果

### 题目翻译
Polycarp刚刚发明了一种新的二进制数据传输协议。他使用以下算法将正整数十进制数编码为二进制字符串：
- 每个数字用等于该数字值的 '1' 字符数量表示（对于 0 则是零个 '1'）。
- 数字按照对应数字的顺序依次写入，并用单个 '0' 字符分隔。

尽管Polycarp学会了如何对数字进行编码，但他不知道如何将它们解码回来。请帮助他计算解码后的数字。

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟解码过程，即遇到 '1' 就计数，遇到 '0' 就输出计数值并清零。各题解的主要区别在于输入方式和代码实现细节。
- **思路**：都是根据输入的 01 串，按照规则模拟解码过程，统计连续 '1' 的个数作为一个数字，遇到 '0' 分隔输出该数字。
- **算法要点**：使用一个变量来记录连续 '1' 的个数，遇到 '0' 时输出该变量的值并将其清零。
- **解决难点**：处理输入和最后一个数字的输出，因为最后一个数字后面可能没有 '0' 分隔。

### 所选题解
- **作者：TRZ_2007 (赞：6)，4星**
  - **关键亮点**：思路清晰，代码简洁，直接按照操作模拟，易于理解。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

char str[N];
int n,sum;

int main()
{
    scanf("%d\n",&n);
    scanf("%s",str+1);
    for(int i=1;i<=strlen(str+1);i++) {
        if(str[i] == '1')
            sum++;
        else {
            printf("%d",sum);
            sum = 0;
        }
    }
    printf("%d\n",sum);
}
```
  - **核心实现思想**：先读取字符串长度和字符串，然后遍历字符串，遇到 '1' 就将计数器 `sum` 加 1，遇到 '0' 就输出 `sum` 并将其清零，最后输出最后一个数字。

- **作者：do_while_true (赞：0)，4星**
  - **关键亮点**：详细解释了题目规则，提供了两种不同输入方式的代码，代码规范。
  - **核心代码（Code1）**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,t;
char ch;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    while(n--)
    {
        cin>>ch;
        if(ch=='0')
        {
            cout<<t;
            t=0;
        }
        else
            t++;
    }
    cout<<t;
    return 0;
}
```
  - **核心实现思想**：使用 `cin` 逐个读取字符，遇到 '1' 就将计数器 `t` 加 1，遇到 '0' 就输出 `t` 并将其清零，最后输出最后一个数字。

- **作者：ProjectRed (赞：0)，4星**
  - **关键亮点**：提供了两种做法，一种是先读取整个字符串再遍历，另一种是边读边处理，代码注释详细。
  - **核心代码（边读边处理）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s;
int main ()
{
    int n;
    scanf ("%d", &n);
    int num = 0;
    getchar ();
    for (int i = 1; i <= n; i++)
    {
        scanf ("%c", &s);
        if (s == '1')
            num++;
        else
            printf ("%d", num), num = 0;
    }
    printf ("%d", num);
    return EXIT_SUCCESS;
}
```
  - **核心实现思想**：先读取字符串长度，使用 `getchar` 吃掉换行符，然后逐个读取字符，遇到 '1' 就将计数器 `num` 加 1，遇到 '0' 就输出 `num` 并将其清零，最后输出最后一个数字。

### 最优关键思路或技巧
- 使用一个变量来记录连续 '1' 的个数，遇到 '0' 时输出该变量的值并将其清零。
- 注意处理最后一个数字的输出，因为最后一个数字后面可能没有 '0' 分隔。

### 可拓展之处
同类型题可能会有不同的编码规则，例如使用不同的分隔符或编码方式，但解题思路仍然是模拟解码过程。类似算法套路可以应用于其他需要按照规则处理字符串的题目。

### 推荐洛谷题目
- P1000 超级玛丽游戏
- P1001 A+B Problem
- P1002 [NOIP2002 普及组] 过河卒

### 个人心得摘录与总结
- **TRZ_2007**：吐槽题目翻译难懂，重新翻译后按照操作模拟解题。
- **Mine_King**：吐槽翻译和恶评，提到可以用 `scanf` 的读入指定长度整型功能，省空间省码量。
- **X_Chao_Bai**：吐槽翻译坑，读懂题目后正常模拟解题。
- **do_while_true**：强调读懂题目的重要性，通过观察样例得出解题方法。
- **ProjectRed**：指出完全不需要输入字串长度，提供了两种做法及优缺点。
- **cbyybccbyybc**：认为题目较水，根据题意模拟解题。

总结：大部分题解作者都吐槽了题目翻译难懂，解题思路都是模拟解码过程，同时分享了一些输入处理和代码实现的技巧。 

---
处理用时：36.78秒