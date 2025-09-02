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

### 题目内容中文重写
# 最小单词

## 题目描述
IA的冰箱上有好多五颜六色的磁铁！每块磁铁上恰好写着一个字母，要么是 'a' 要么是 'b'。她喜欢把所有磁铁排成一排来玩。然而，这个女孩很快就玩腻了，通常会思考如何让她的玩法更有趣。

今天，当IA看着冰箱时，她注意到由磁铁组成的单词看起来很杂乱。“如果我交换其中一些磁铁，它会好看得多！”——女孩心想——“但该怎么做呢？” 过了一会儿，她有了一个主意。IA会查看从长度为 1 到单词长度的所有前缀，对于每个前缀，她要么反转这个前缀，要么保持原样。她会按照固定的顺序考虑这些前缀：从最短的到最长的。她想在考虑完所有前缀后得到字典序最小的单词。你能帮她指出哪些前缀应该被反转吗？

如果且仅当以下条件之一成立时，字符串 $a$ 的字典序小于字符串 $b$：
- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 不同的第一个位置上，字符串 $a$ 中的字母在字母表中比 $b$ 中对应的字母出现得更早。

## 说明/提示
在第一个示例中，IA 可以反转第二个和第三个前缀，得到字符串 "abbb"。她无法得到更好的结果，因为这也是通过排列初始字符串的字符可以得到的字典序最小的字符串。

在第二个示例中，她可以反转任意子集的前缀——因为所有字母都是 'a'。

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

### 综合分析与结论
- **思路对比**：各题解思路一致，都认为要得到字典序最小的字符串，应使字符串前面都是 'a'，后面都是 'b'，实现方式是找到相邻不同字符的位置（即 'a' 和 'b' 的交界线）进行前缀反转，若最后一个字符是 'a' 则还需反转整个字符串。
- **算法要点**：遍历字符串，判断相邻字符是否不同，不同则标记该位置需要反转；最后判断最后一个字符是否为 'a'，若是则标记最后一个位置需要反转。
- **解决难点**：理解如何通过反转前缀得到字典序最小的字符串，关键在于发现 'a' 和 'b' 交界线与反转操作的关系，以及对最后一个字符为 'a' 的特殊处理。

### 所选题解
- **作者：引领天下 (4星)**
  - **关键亮点**：使用 Python 的 `zip` 函数简洁实现，代码短小精悍。
  - **个人心得**：无
- **作者：liuyz11 (4星)**
  - **关键亮点**：通过模拟字符串反转过程，详细解释了算法的原理，思路清晰。
  - **个人心得**：因最后一位是 'a' 时未特判导致 WA 一次，提醒要注意边界情况。
- **作者：ImNot6Dora (4星)**
  - **关键亮点**：代码简洁，逻辑清晰，直接实现了算法思路。
  - **个人心得**：无

### 重点代码
#### 引领天下（Python）
```python
s=input()
print(*(int(x!=y)for x,y in zip(s,s[1:]+'b')))
```
**核心实现思想**：使用 `zip` 函数将字符串 $s$ 与 $s$ 去掉首字符后再在末尾添加 'b' 的字符串进行元素配对，若对应元素不同则输出 1，否则输出 0。

#### liuyz11（C++）
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
        if(st[i] != st[i + 1]) flag[i] = 1;
    if(st[len] == 'a') flag[len] = 1;
    rep(i, 1, len) printf("%d ", flag[i]);
    puts("");   
    return 0;
}
```
**核心实现思想**：遍历字符串，若相邻字符不同则标记该位置需要反转，最后判断最后一个字符是否为 'a'，若是则标记最后一个位置需要反转，最后输出标记结果。

#### ImNot6Dora（C++）
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
**核心实现思想**：遍历字符串，根据相邻字符是否不同以及最后一个字符是否为 'a' 输出 1 或 0。

### 最优关键思路或技巧
- **思维方式**：通过模拟字符串操作过程，发现 'a' 和 'b' 交界线与反转操作的关系，从而简化问题。
- **代码实现技巧**：Python 中使用 `zip` 函数可以简洁地处理相邻元素的比较。

### 可拓展之处
同类型题或类似算法套路：对于字符串操作问题，通常可以通过模拟操作过程，寻找规律来简化问题；对于边界情况要特别注意，需要单独处理。

### 推荐洛谷题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)

### 个人心得总结
liuyz11 提到因最后一位是 'a' 时未特判导致 WA 一次，提醒我们在处理字符串问题时，一定要注意边界情况，对特殊情况进行单独处理，避免因细节问题导致错误。

---
处理用时：50.49秒