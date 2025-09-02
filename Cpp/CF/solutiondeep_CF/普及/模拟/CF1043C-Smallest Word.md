# 题目信息

# Smallest Word

## 题目描述

IA has so many colorful magnets on her fridge! Exactly one letter is written on each magnet, 'a' or 'b'. She loves to play with them, placing all magnets in a row. However, the girl is quickly bored and usually thinks how to make her entertainment more interesting.

Today, when IA looked at the fridge, she noticed that the word formed by magnets is really messy. "It would look much better when I'll swap some of them!" — thought the girl — "but how to do it?". After a while, she got an idea. IA will look at all prefixes with lengths from $ 1 $ to the length of the word and for each prefix she will either reverse this prefix or leave it as it is. She will consider the prefixes in the fixed order: from the shortest to the largest. She wants to get the lexicographically smallest possible word after she considers all prefixes. Can you help her, telling which prefixes should be chosen for reversing?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first example, IA can reverse the second and the third prefix and get a string "abbb". She cannot get better result, since it is also lexicographically smallest string obtainable by permuting characters of the initial string.

In the second example, she can reverse any subset of prefixes — all letters are 'a'.

## 样例 #1

### 输入

```
bbab
```

### 输出

```
0 1 1 0
```

## 样例 #2

### 输入

```
aaaaa
```

### 输出

```
1 0 0 0 1
```

# AI分析结果

### 题目中文重写
# 最小单词

## 题目描述
IA的冰箱上有很多五颜六色的磁铁！每块磁铁上正好写着一个字母，要么是 'a' 要么是 'b'。她喜欢把所有磁铁排成一排来玩。然而，这个女孩很快就会感到无聊，并且通常会思考如何让她的娱乐活动更有趣。

今天，当IA看着冰箱时，她注意到由磁铁组成的单词非常杂乱。“如果我交换其中一些磁铁，它看起来会好得多！”——女孩想——“但该怎么做呢？”过了一会儿，她有了一个主意。IA会查看从长度为 $1$ 到单词长度的所有前缀，对于每个前缀，她要么反转这个前缀，要么保持原样。她会按照固定的顺序考虑这些前缀：从最短的到最长的。她想在考虑完所有前缀后得到字典序最小的可能单词。你能帮助她，告诉她哪些前缀应该被反转吗？

如果且仅当以下情况之一成立时，字符串 $a$ 在字典序上小于字符串 $b$：
- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 不同的第一个位置，字符串 $a$ 中的字母在字母表中比 $b$ 中相应位置的字母出现得更早。

## 说明/提示
在第一个示例中，IA可以反转第二个和第三个前缀，得到字符串 "abbb"。她无法得到更好的结果，因为这也是通过排列初始字符串的字符可以得到的字典序最小的字符串。

在第二个示例中，她可以反转任意子集的前缀——所有字母都是 'a'。

## 样例 #1
### 输入
```
bbab
```
### 输出
```
0 1 1 0
```

## 样例 #2
### 输入
```
aaaaa
```
### 输出
```
1 0 0 0 1
```

### 题解综合分析与结论
- **思路对比**：所有题解核心思路一致，都认为要使字典序最小，应让字符串前面是 'a' 后面是 'b'，需在 'a' 和 'b' 的交界处翻转前缀，同时若最后一个字符是 'a' 要额外翻转整个字符串。
- **算法要点**：
    - Python 题解利用 `zip` 函数对比相邻字符判断是否翻转。
    - C++ 题解通过遍历字符串，比较相邻字符确定是否翻转，最后特判最后一个字符是否为 'a'。
- **解决难点**：主要难点在于理解为何在 'a' 和 'b' 交界处翻转能得到字典序最小的字符串，以及对最后一个字符为 'a' 的情况进行特判。

### 题解评分
- 引领天下：3星。使用 Python 的 `zip` 函数，代码简洁，但对于不熟悉 Python 的人来说理解有难度，且缺乏思路解释。
- liuyz11：4星。思路清晰，通过模拟过程解释算法，代码可读性高，有必要的注释。
- ImNot6Dora：4星。思路清晰，代码简洁，对思路有简要说明。
- Digital_Sunrise：4星。思路详细，对算法原理有解释，代码实现规范。

### 所选题解
- liuyz11（4星）：关键亮点是通过模拟字符串翻转过程，详细解释了算法的原理，让读者容易理解。
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define INF 1 << 30
#define MAXN 1005
using namespace std;
typedef long long LL;
typedef pair<int,int> par;

char st[MAXN];
bool flag[MAXN];

int main(){
    scanf("%s", st + 1);
    int len = strlen(st + 1);
    rep(i, 1, len - 1)
        if(st[i]!= st[i + 1]) flag[i] = 1;
    if(st[len] == 'a') flag[len] = 1;
    rep(i, 1, len) printf("%d ", flag[i]);
    puts("");   
    return 0;
}
```
核心实现思想：先读取字符串，然后遍历字符串，比较相邻字符，若不同则标记该位置需要翻转，最后判断最后一个字符是否为 'a'，若是则标记最后一个位置需要翻转，最后输出标记结果。

- ImNot6Dora（4星）：关键亮点是代码简洁，思路清晰，直接通过条件判断输出结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
    cin>>s;
    for(int i=0;i<s.length();i++){
        if(s.length()-1!=i&&s[i]!=s[i+1]||i==s.length()-1&&s[i]=='a')cout<<1<<' ';	
        else cout<<0<<' ';
    }
    return 0;
}
```
核心实现思想：读取字符串后，遍历字符串，根据相邻字符是否不同以及最后一个字符是否为 'a' 输出 1 或 0。

- Digital_Sunrise（4星）：关键亮点是对思路和算法原理有详细解释，代码规范。
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

signed main()
{
    cin >> s;
    for(int i = 0;i < s.length();i++)
    {
        if(i == s.length() - 1 and s[i] == 'a')
        {
            putchar('1');
            putchar(' ');
            return 0;
        }
        if(i!= s.length() - 1 and s[i]!= s[i + 1])
        {
            putchar('1');
            putchar(' ');
        }
        else
        {
            putchar('0');
            putchar(' ');
        }
    }
    return 0;
}
```
核心实现思想：读取字符串后，遍历字符串，判断相邻字符是否不同以及最后一个字符是否为 'a'，根据判断结果输出 1 或 0。

### 最优关键思路或技巧
通过分析字典序最小的特点，发现要让 'a' 在前 'b' 在后，只需在 'a' 和 'b' 的交界处翻转前缀，同时对最后一个字符为 'a' 的情况进行特判。

### 可拓展之处
同类型题可能会将字符扩展到更多种类，或者改变操作规则，如可以选择翻转任意子串等。类似算法套路是通过分析目标状态的特点，找到实现目标的关键操作位置。

### 洛谷题目推荐
- P1055 [NOIP2008 普及组] ISBN 号码
- P1047 [NOIP2005 普及组] 校门外的树
- P1009 [NOIP1998 普及组] 阶乘之和

### 个人心得摘录与总结
liuyz11：“还有就是如果最后一位是a就要在最后将整个字符串旋转（我居然因为这个wa了一次……”，总结：在处理字符串问题时，要注意边界情况，避免因边界条件处理不当导致错误。 

---
处理用时：42.54秒