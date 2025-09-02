# 题目信息

# Sasha and One More Name

## 题目描述

Reading books is one of Sasha's passions. Once while he was reading one book, he became acquainted with an unusual character. The character told about himself like that: "Many are my names in many countries. Mithrandir among the Elves, Tharkûn to the Dwarves, Olórin I was in my youth in the West that is forgotten, in the South Incánus, in the North Gandalf; to the East I go not."

And at that moment Sasha thought, how would that character be called in the East? In the East all names are palindromes. A string is a palindrome if it reads the same backward as forward. For example, such strings as "kazak", "oo" and "r" are palindromes, but strings "abb" and "ij" are not.

Sasha believed that the hero would be named after one of the gods of the East. As long as there couldn't be two equal names, so in the East people did the following: they wrote the original name as a string on a piece of paper, then cut the paper minimum number of times $ k $ , so they got $ k+1 $ pieces of paper with substrings of the initial string, and then unite those pieces together to get a new string. Pieces couldn't be turned over, they could be shuffled.

In this way, it's possible to achive a string abcdefg from the string f|de|abc|g using $ 3 $ cuts (by swapping papers with substrings f and abc). The string cbadefg can't be received using the same cuts.

More formally, Sasha wants for the given palindrome $ s $ find such minimum $ k $ , that you can cut this string into $ k + 1 $ parts, and then unite them in such a way that the final string will be a palindrome and it won't be equal to the initial string $ s $ . It there is no answer, then print "Impossible" (without quotes).

## 说明/提示

In the first example, you can cut the string in those positions: no|l|on, and then unite them as follows on|l|no. It can be shown that there is no solution with one cut.

In the second example, you can cut the string right in the middle, and swap peaces, so you get toot.

In the third example, you can't make a string, that won't be equal to the initial one.

In the fourth example, you can cut the suffix nik and add it to the beginning, so you get nikkinnikkin.

## 样例 #1

### 输入

```
nolon
```

### 输出

```
2
```

## 样例 #2

### 输入

```
otto
```

### 输出

```
1
```

## 样例 #3

### 输入

```
qqqq
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
kinnikkinnik
```

### 输出

```
1
```

# AI分析结果

### 题目翻译
# 萨沙和另一个名字

## 题目描述
读书是萨沙的爱好之一。有一次，当他在读一本书时，他结识了一个不同寻常的角色。这个角色这样介绍自己：“在许多国家，我有许多名字。在精灵中我叫米斯兰迪尔，在矮人那里我叫萨昆，在被遗忘的西方，我年轻时叫奥洛林，在南方叫因卡努斯，在北方叫甘道夫；我不去东方。”

就在那一刻，萨沙想，这个角色在东方会被叫做什么呢？在东方，所有的名字都是回文串。如果一个字符串从后往前读和从前往后读是一样的，那么它就是回文串。例如，“kazak”、“oo” 和 “r” 这样的字符串是回文串，但 “abb” 和 “ij” 这样的字符串不是。

萨沙相信这个英雄会以东方的某个神的名字命名。由于不能有两个相同的名字，所以在东方，人们会这样做：他们把原来的名字写在一张纸上，然后把纸最少切 $k$ 次，这样他们就得到了 $k + 1$ 张写有原字符串子串的纸，然后把这些纸拼在一起得到一个新的字符串。这些纸不能翻面，可以打乱顺序。

通过这种方式，使用 3 次切割（交换包含子串 f 和 abc 的纸），可以从字符串 f|de|abc|g 得到字符串 abcdefg。使用同样的切割方式无法得到字符串 cbadefg。

更正式地说，萨沙想为给定的回文串 $s$ 找到最小的 $k$，使得可以把这个字符串切成 $k + 1$ 部分，然后把它们组合起来，使得最终的字符串是回文串，并且它不等于原来的字符串 $s$。如果没有答案，则输出 “Impossible”（不含引号）。

## 说明/提示
在第一个样例中，可以在这些位置切割字符串：no|l|on，然后按如下方式组合：on|l|no。可以证明，切一次是没有解决方案的。

在第二个样例中，可以正好在字符串中间切割，然后交换两部分，这样就得到了 toot。

在第三个样例中，无法得到一个与原字符串不同的字符串。

在第四个样例中，可以切掉后缀 nik 并把它添加到开头，这样就得到了 nikkinnikkin。

## 样例 #1
### 输入
```
nolon
```
### 输出
```
2
```

## 样例 #2
### 输入
```
otto
```
### 输出
```
1
```

## 样例 #3
### 输入
```
qqqq
```
### 输出
```
Impossible
```

## 样例 #4
### 输入
```
kinnikkinnik
```
### 输出
```
1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断无解情况，再根据字符串长度的奇偶性分类讨论得到最小切割次数。
- **思路对比**：多数题解采用分奇偶性讨论的方式，部分题解通过构造合法方案证明答案不超过 2，还有题解用 Manacher 和 KMP 算法判断答案为 1 的情况。
- **算法要点**：主要是判断无解条件，然后分奇偶性找切割方案，部分题解用哈希或字符串库函数判断回文和字符串相等。
- **解决难点**：关键在于找出无解情况和构造出不同的回文串，对于偶数长度字符串的处理相对复杂。

### 高评分题解
- **Celtic（5星）**
    - **关键亮点**：思路清晰，分奇偶性详细讨论，代码中使用 `goto` 简化递归操作。
- **CaiXY06（4星）**
    - **关键亮点**：采用不一样的思路，不依赖分奇偶讨论，用暴力枚举断点结合 Hash 或 `string` 库函数判断，代码简洁。
- **zac2010（4星）**
    - **关键亮点**：用构造法证明结论，使用字符串哈希判断，时间复杂度线性。

### 重点代码
#### Celtic 的核心代码
```cpp
while(t--)
{
    scanf("%s",s+1);
    n=strlen(s+1);
    re bool flag=true;
    for(re int i=2;i<=(n>>1);i++)
        flag&=(s[i]==s[i-1]);
    if(flag)
    {
        puts("Impossible");
        continue;
    }
start:
    flag=true;
    for(re int i=1;(i<<1)<=n;i++)
    {
        if(s[(n>>1)-i+1]!=s[i])
            flag=false;
    }
    if(!flag&&(n&1))
    {
        puts("2");
        continue;
    }
    else if(!flag&&!(n&1))
    {
        puts("1");
        continue;
    }
    else if(flag&&(n&1))
    {
        puts("2");
        continue;
    }
    else if(flag&&!(n&1))
    {
        n>>=1;
        goto start;
    }
}
```
**核心实现思想**：先判断是否所有字符相同，若相同则无解。然后分奇偶性讨论，对于偶数长度且前半部分是回文的情况，递归处理。

#### CaiXY06 的核心代码
```cpp
cin>>s;n=s.size();
for(int i=0;i<n>>1;i++)res+=(s[i]!=s[0]);
if(!res)return puts("Impossible"),0;
for(int i=1;i<=n>>1;i++){
    T=s.substr(i,n)+s.substr(0,i);
    S=T;reverse(S.begin(),S.end());
    if(S==T&&S!=s)return puts("1"),0;
}
puts("2");
```
**核心实现思想**：先判断是否无解，然后暴力枚举断点，将两段字符串颠倒位置后重新拼接，判断新串是否回文且与原串不同。

#### zac2010 的核心代码
```cpp
scanf("%s", str + 1), n = strlen(str + 1), pw[0] = 1; 
FL(i, 1, n) pw[i] = pw[i - 1] * base % p;
FL(i, 1, n) s[0][i] = s[0][i - 1] * base % p + (str[i] - 'a');
FR(i, n, 1) s[1][i] = s[1][i + 1] * base % p + (str[i] - 'a');
FL(i, 2, n){
    ll z = (ch(i, n, 0) * pw[i - 1] + ch(1, i - 1, 0)) % p;
    ll f = (ch(1, i - 1, 1) * pw[n - i + 1] + ch(i, n, 1)) % p;
    if(z == ch(1, n, 0) || z != f) continue;
    printf("1\n"); return 0;
}
FL(i, 2, n / 2) if(str[i] != str[1]){
    printf("2\n"); return 0;
}
printf("Impossible\n");
```
**核心实现思想**：先预处理字符串哈希，然后枚举断点，用哈希判断新串是否回文且与原串不同，若都不满足则判断是否无解。

### 关键思路或技巧
- 先判断无解情况，如所有字符相同或奇数长度时除中间字符外其余相同。
- 分奇偶性讨论，对于奇数长度，答案通常为 2；对于偶数长度，判断前半部分是否为回文来确定答案。
- 可以用哈希或字符串库函数判断回文和字符串相等。

### 拓展思路
同类型题可能会有不同的字符串操作限制或要求构造其他特殊字符串，类似算法套路是先分析特殊情况，再分类讨论找构造方案。

### 推荐题目
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：涉及字符串比较和排序。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串匹配相关。
- [P5733 【深基6.例1】自动修正](https://www.luogu.com.cn/problem/P5733)：简单的字符串处理。

### 个人心得
题解中没有明显的个人心得内容。 

---
处理用时：57.09秒