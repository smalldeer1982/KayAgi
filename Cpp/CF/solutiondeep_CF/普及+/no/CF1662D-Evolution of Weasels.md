# 题目信息

# Evolution of Weasels

## 题目描述

A wild basilisk just appeared at your doorstep. You are not entirely sure what a basilisk is and you wonder whether it evolved from your favorite animal, the weasel.

How can you find out whether basilisks evolved from weasels? Certainly, a good first step is to sequence both of their DNAs. Then you can try to check whether there is a sequence of possible mutations from the DNA of the weasel to the DNA of the basilisk.

Your friend Ron is a talented alchemist and has studied DNA sequences in many of his experiments. He has found out that DNA strings consist of the letters A, B and C and that single mutations can only remove or add substrings at any position in the string (a substring is a contiguous sequence of characters). The substrings that can be removed or added by a mutation are AA, BB, CC, ABAB or BCBC. During a sequence of mutations a DNA string may even become empty.

Ron has agreed to sequence the DNA of the weasel and the basilisk for you, but finding out whether there is a sequence of possible mutations that leads from one to the other is too difficult for him, so you have to do it on your own.

## 样例 #1

### 输入

```
8
A
B
B
C
C
A
AA
BB
BB
CC
CC
AA
ABAB
BCBC
ABC
CBA```

### 输出

```
NO
NO
NO
YES
YES
YES
YES
NO```

# AI分析结果

### 题目中文重写
# 黄鼠狼的进化

## 题目描述
一只野生的蛇怪突然出现在你的家门口。你不太确定蛇怪是什么，你想知道它是否是从你最喜欢的动物——黄鼠狼进化而来的。

你如何才能知道蛇怪是否是从黄鼠狼进化而来的呢？当然，第一步是对它们的 DNA 进行测序。然后你可以尝试检查是否存在从黄鼠狼的 DNA 到蛇怪的 DNA 的一系列可能的突变。

你的朋友罗恩是一位有才华的炼金术士，他在许多实验中研究过 DNA 序列。他发现 DNA 字符串由字母 A、B 和 C 组成，并且单个突变只能在字符串的任何位置移除或添加子字符串（子字符串是连续的字符序列）。可以通过突变移除或添加的子字符串是 AA、BB、CC、ABAB 或 BCBC。在一系列突变过程中，DNA 字符串甚至可能变为空。

罗恩已经同意为你对黄鼠狼和蛇怪的 DNA 进行测序，但找出是否存在从一个到另一个的一系列可能的突变对他来说太难了，所以你必须自己完成。

## 样例 #1

### 输入
```
8
A
B
B
C
C
A
AA
BB
BB
CC
CC
AA
ABAB
BCBC
ABC
CBA
```

### 输出
```
NO
NO
NO
YES
YES
YES
YES
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先利用给定的变换规则，将所有的 `B` 移到字符串末尾并处理 `B` 的数量奇偶性，再对剩余由 `A` 和 `C` 组成的部分使用栈来贪心删除 `AA` 和 `CC` 子串，最后判断两个处理后的字符串是否相等。

- **思路对比**：各位作者都先发现了 `AB` 与 `BA`、`BC` 与 `CB` 可相互转化的规律，从而得出可以将 `B` 移到字符串末尾的结论，并且都提到了根据 `B` 的数量奇偶性进行初步判断。
- **算法要点**：均使用栈来模拟删除 `AA` 和 `CC` 子串的过程，类似于括号匹配的思路。
- **解决难点**：主要难点在于发现变换规则的规律，以及如何利用这些规律简化问题，各位作者都通过合理的推理和分析解决了这些问题。

### 题解评分与选择
- **enucai（4星）**：
    - **关键亮点**：思路清晰，有详细的引理证明，代码结构清晰，注释规范。
- **hgcnxn（3星）**：
    - **关键亮点**：思路简洁明了，代码实现较为常规。
- **Wings_of_liberty（3星）**：
    - **关键亮点**：对性质的描述较为详细，代码实现中使用了字符串模拟栈的操作。
- **wheneveright（3星）**：
    - **关键亮点**：对变换规则的分析较为深入，但代码未给出具体实现。

选择 enucai 的题解。

### 重点代码及核心实现思想
```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
int n,m,top;
char s[210],t[210],stk[210];
void work(){
    cin>>(s+1)>>(t+1);
    n=strlen(s+1),m=strlen(t+1);
    int cnt1=0,cnt2=0;
    // 统计两个字符串中 B 的数量
    For(i,1,n) if(s[i]=='B') cnt1++;
    For(i,1,m) if(t[i]=='B') cnt2++;
    // 如果 B 的数量奇偶性不同，直接输出 NO
    if(cnt1%2!=cnt2%2) {cout<<"NO\n";return;}
    string S="",T="";
    top=0;
    // 处理第一个字符串，用栈删除 AA 和 CC 子串
    For(i,1,n) if(s[i]!='B'){
        if(top&&stk[top]==s[i]) top--;
        else stk[++top]=s[i];
    }
    while(top) S+=stk[top--];
    top=0;
    // 处理第二个字符串，用栈删除 AA 和 CC 子串
    For(i,1,m) if(t[i]!='B'){
        if(top&&stk[top]==t[i]) top--;
        else stk[++top]=t[i];
    }
    while(top) T+=stk[top--];
    // 判断处理后的两个字符串是否相等
    if(S==T) cout<<"YES\n";
    else cout<<"NO\n";
}
signed main(){
    int T;cin>>T;
    while(T--) work();
}
```
核心实现思想：先统计两个字符串中 `B` 的数量，判断其奇偶性是否相同。若不同，直接输出 `NO`；若相同，将 `B` 忽略，对剩余的 `A` 和 `C` 组成的部分使用栈来删除 `AA` 和 `CC` 子串，最后比较处理后的两个字符串是否相等。

### 关键思路或技巧
- **规律发现**：通过对变换规则的分析，发现 `AB` 与 `BA`、`BC` 与 `CB` 可相互转化，从而可以将所有的 `B` 移到字符串末尾。
- **栈的应用**：使用栈来模拟删除 `AA` 和 `CC` 子串的过程，类似于括号匹配的思路，简化了处理过程。

### 拓展思路
同类型题目可能会给出不同的变换规则或字符集，解题的关键在于发现变换规则的规律，并利用这些规律简化问题。类似的算法套路包括利用栈来处理字符串的匹配问题，以及根据某些特征进行初步判断和分类讨论。

### 推荐洛谷题目
- P1057 传球游戏：涉及字符串的变换和递推思想。
- P1067 多项式输出：需要对字符串进行处理和模拟。
- P1071 潜伏者：考查字符串的匹配和替换。

---
处理用时：37.81秒