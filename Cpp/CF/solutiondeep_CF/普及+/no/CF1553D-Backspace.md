# 题目信息

# Backspace

## 题目描述

You are given two strings $ s $ and $ t $ , both consisting of lowercase English letters. You are going to type the string $ s $ character by character, from the first character to the last one.

When typing a character, instead of pressing the button corresponding to it, you can press the "Backspace" button. It deletes the last character you have typed among those that aren't deleted yet (or does nothing if there are no characters in the current string). For example, if $ s $ is "abcbd" and you press Backspace instead of typing the first and the fourth characters, you will get the string "bd" (the first press of Backspace deletes no character, and the second press deletes the character 'c'). Another example, if $ s $ is "abcaa" and you press Backspace instead of the last two letters, then the resulting text is "a".

Your task is to determine whether you can obtain the string $ t $ , if you type the string $ s $ and press "Backspace" instead of typing several (maybe zero) characters of $ s $ .

## 说明/提示

Consider the example test from the statement.

In order to obtain "ba" from "ababa", you may press Backspace instead of typing the first and the fourth characters.

There's no way to obtain "bb" while typing "ababa".

There's no way to obtain "aaaa" while typing "aaa".

In order to obtain "ababa" while typing "aababa", you have to press Backspace instead of typing the first character, then type all the remaining characters.

## 样例 #1

### 输入

```
4
ababa
ba
ababa
bb
aaa
aaaa
aababa
ababa```

### 输出

```
YES
NO
NO
YES```

# AI分析结果

### 题目内容（中文重写）
# 退格

## 题目描述
给定两个字符串 $s$ 和 $t$，它们均由小写英文字母组成。你将逐个字符地输入字符串 $s$，从第一个字符到最后一个字符。

在输入字符时，你可以不按对应字符的按键，而是按“退格”键。退格键会删除你输入的尚未被删除的最后一个字符（如果当前字符串中没有字符，则不执行任何操作）。例如，如果 $s$ 是 "abcbd"，并且你在输入第一个和第四个字符时按下退格键，你将得到字符串 "bd"（第一次按退格键不删除任何字符，第二次按退格键删除字符 'c'）。另一个例子，如果 $s$ 是 "abcaa"，并且你在输入最后两个字母时按下退格键，那么最终的文本是 "a"。

你的任务是确定，在输入字符串 $s$ 并在输入 $s$ 的若干（可能为零）个字符时按下“退格”键的情况下，是否可以得到字符串 $t$。

## 说明/提示
考虑题目陈述中的示例测试。

为了从 "ababa" 得到 "ba"，你可以在输入第一个和第四个字符时按下退格键。

在输入 "ababa" 时，无法得到 "bb"。

在输入 "aaa" 时，无法得到 "aaaa"。

为了从 "aababa" 得到 "ababa"，你必须在输入第一个字符时按下退格键，然后输入其余所有字符。

## 样例 #1

### 输入
```
4
ababa
ba
ababa
bb
aaa
aaaa
aababa
ababa
```

### 输出
```
YES
NO
NO
YES
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何判断能否通过对字符串 $s$ 进行退格操作得到字符串 $t$ 展开。多数题解采用贪心策略，其中正序和倒序贪心是两种常见思路。正序贪心需要考虑字符串长度奇偶性不同时的特殊情况；倒序贪心则更简洁，直接从后往前匹配，遇到不匹配就跳过两个字符。部分题解还运用了动态规划等方法，但相对复杂。

### 所选题解
- **江户川·萝卜（4星）**
  - 关键亮点：思路清晰，详细分析了退格操作的实质作用，先判断字符串长度奇偶性，再用贪心从前往后匹配，代码简洁易懂。
- **Alex_Wei（4星）**
  - 关键亮点：采用倒序贪心的方法，巧妙地证明了若干个连续退格等价于若干个不连续退格，使贪心算法的正确性得到保证，代码简洁高效。
- **wheneveright（4星）**
  - 关键亮点：反向考虑问题，将退格操作理解为消除连续两个字符或第一个字符，简化了问题，代码实现简洁。

### 重点代码
#### 江户川·萝卜
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s,t;
        cin>>s;
        cin>>t;
        int sl=s.length(),tl=t.length();
        string ss="";int j=0,k=0;
        if(sl%2!=tl%2) j=1;
        for(int i=j;i<sl;i++){
            if(s[i]==t[k]) k++;
            else i++;
            if(k>=tl) break;
        }
        if(k<tl) puts("NO");
        else puts("YES");
    }
    return 0;
}
```
核心实现思想：先判断 $s$ 和 $t$ 长度奇偶性是否不同，若不同则从 $s$ 的第二个字符开始匹配。从前往后遍历 $s$，若当前字符与 $t$ 的当前字符相等，则 $t$ 的指针后移；否则跳过 $s$ 的下一个字符。最后判断是否匹配完 $t$。

#### Alex_Wei
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int T=1; cin>>T;
    while(T--){
        string s,t; cin>>s>>t;
        int p=t.size()-1;
        for(int i=s.size()-1;i>=0;i--)~p&&s[i]==t[p]?p--:i--;
        puts(~p?"NO":"YES");
    }
    return 0;
}
```
核心实现思想：从后往前遍历 $s$，若当前字符与 $t$ 的最后一个字符相等，则 $t$ 的指针前移；否则跳过 $s$ 的前一个字符。最后判断 $t$ 的指针是否为 -1。

#### wheneveright
```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, M;
string a, b;

int main () {
    cin >> T;
    while (T--) {
        cin >> a >> b;
        N = a.size (); a = "0" + a;
        M = b.size (); b = "0" + b;
        while (N >= 0) {
            if (a[N] == b[M] && M >= 1) N--, M--;
            else N -= 2;
        }
        puts (M >= 1 ? "NO" : "YES");
    }
    return 0;
}
```
核心实现思想：反向考虑，从后往前遍历 $a$，若当前字符与 $b$ 的当前字符相等，则 $a$ 和 $b$ 的指针都前移；否则 $a$ 的指针前移两位。最后判断 $b$ 的指针是否小于等于 0。

### 最优关键思路或技巧
- **倒序贪心**：多数高星题解采用倒序贪心的方法，从后往前匹配字符串，避免了正序贪心需要考虑的复杂情况，使代码更简洁，逻辑更清晰。
- **奇偶性判断**：在正序贪心时，通过判断字符串长度的奇偶性，处理特殊情况，简化匹配过程。

### 拓展思路
同类型题可能会增加更多的操作规则，如增加不同功能的按键，或者对字符串的长度、字符范围有更多限制。类似算法套路可以应用在字符串匹配、编辑距离等问题中，通过贪心或动态规划的方法，根据操作规则进行状态转移和判断。

### 推荐题目
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：涉及递推和动态规划，与字符串匹配中的状态转移有相似之处。
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：可以用贪心或动态规划的思想解决，锻炼对问题的分析和处理能力。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划问题，有助于理解状态转移和最优解的求解。

### 个人心得摘录与总结
- **do_while_true**：提到看到字符串就害怕，说明字符串问题可能会给人带来一定的心理压力，但通过合理的分析和算法设计可以解决。该题解通过子序列自动机和 dp 来处理问题，展示了复杂问题的解决思路。 

---
处理用时：53.86秒