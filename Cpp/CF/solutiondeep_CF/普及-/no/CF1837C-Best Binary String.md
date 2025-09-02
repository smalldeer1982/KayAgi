# 题目信息

# Best Binary String

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1 and/or ?. Let's call it a pattern.

Let's say that the binary string (a string where each character is either 0 or 1) matches the pattern if you can replace each character ? with 0 or 1 (for each character, the choice is independent) so that the strings become equal. For example, 0010 matches ?01?, but 010 doesn't match 1??, ??, or ????.

Let's define the cost of the binary string as the minimum number of operations of the form "reverse an arbitrary contiguous substring of the string" required to sort the string in non-descending order.

You have to find a binary string with the minimum possible cost among those that match the given pattern. If there are multiple answers, print any of them.

## 说明/提示

In the first test case of the example, the cost of the resulting string is $ 0 $ .

In the second test case, the cost of the resulting string is $ 2 $ : we can reverse the substring from the $ 1 $ -st character to the $ 5 $ -th character, and we obtain the string 00101. Then we reverse the substring from the $ 3 $ -rd to the $ 4 $ -th character, and we obtain the string 00011, which is sorted in non-descending order.

## 样例 #1

### 输入

```
4
??01?
10100
1??10?
0?1?10?10```

### 输出

```
00011
10100
111101
011110010```

# AI分析结果

### 题目翻译
## 最佳二进制字符串

### 题目描述
给定一个由字符 0、1 和/或 ? 组成的字符串 $s$，我们称其为一个模式。

如果一个二进制字符串（每个字符要么是 0 要么是 1 的字符串）可以通过将模式中的每个 ? 独立地替换为 0 或 1，使得两个字符串相等，那么就称这个二进制字符串与该模式匹配。例如，0010 与 ?01? 匹配，但 010 与 1??、?? 或 ???? 不匹配。

我们将二进制字符串的代价定义为将该字符串按非降序排序所需的最少“反转任意连续子字符串”操作的次数。

你需要找到一个与给定模式匹配且代价最小的二进制字符串。如果有多个答案，输出其中任意一个即可。

### 说明/提示
在示例的第一个测试用例中，结果字符串的代价为 0。

在第二个测试用例中，结果字符串的代价为 2：我们可以反转从第 1 个字符到第 5 个字符的子字符串，得到字符串 00101。然后反转从第 3 个到第 4 个字符的子字符串，得到字符串 00011，该字符串按非降序排序。

### 样例 #1
#### 输入
```
4
??01?
10100
1??10?
0?1?10?10
```
#### 输出
```
00011
10100
111101
011110010
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过构造的方法来解决问题，目标是让构造出的二进制字符串经过最少的反转操作就能变为升序。具体做法是将问号字符进行填充，若问号在字符串开头则填充为 0，若不在开头则填充为前一个字符。不同题解的差异主要体现在证明思路和代码实现细节上。部分题解通过具体例子来辅助理解，部分题解则从理论上进行证明。

### 所选的题解
- **Iniaugoty（4星）**
  - 关键亮点：思路清晰，先给出结论再进行证明，代码简洁易懂。
  - 证明过程逻辑清晰，从不同情况分析了填充字符对答案的影响。
- **WA_sir（4星）**
  - 关键亮点：通过具体例子分析，使读者更容易理解如何通过减少连续相同字符块的数量来减少反转操作次数，同时给出了代码实现时的注意事项。
- **FinderHT（4星）**
  - 关键亮点：提出了把相邻的 0 和 1 看做段的思路，通过计算段数来分析反转次数，并给出了从左往右的贪心策略，代码实现有小技巧。

### 重点代码
#### Iniaugoty 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
string str;
signed main(){
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>str;
        if(str[0]=='?') str[0]='0';
        for(int i=1;i<str.size();i++)
            if(str[i]=='?')
                str[i]=str[i-1];
        cout<<str<<"\n";
    }
    return 0;
}
```
核心实现思想：先判断字符串的第一个字符是否为问号，若是则将其置为 0，然后遍历字符串，若遇到问号则将其置为前一个字符。

#### WA_sir 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>s;
        char a='0';
        for(int i=0;i<s.size();i++) s[i]=='?'?s[i]=a:a=s[i];
        cout<<s<<endl;
    }
    return 0;
}
```
核心实现思想：使用一个字符变量 `a` 记录前一个字符，遍历字符串，若当前字符为问号则将其置为 `a`，否则更新 `a` 为当前字符。

#### FinderHT 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void solve(){
    string s;
    cin>>s;
    int l=s.size();
    s="0"+s;
    for(int i=1;i<=l;i++)
        if(s[i]=='?') s[i]=s[i-1];
    for(int i=1;i<=l;i++) putchar(s[i]);
    putchar('\n');
}
signed main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
```
核心实现思想：在字符串前添加一个 0，方便处理第一个字符为问号的情况，然后遍历字符串，若遇到问号则将其置为前一个字符。

### 关键思路或技巧
- **贪心构造**：通过贪心的思想，将问号字符填充为前一个字符（第一个问号填充为 0），使得字符串中的 0 和 1 尽可能连续，从而减少反转操作的次数。
- **连续字符块的处理**：将连续的相同字符看作一个整体，通过减少连续字符块的数量来减少反转操作次数。

### 可拓展之处
同类型的题目可能会改变操作规则，例如改变反转操作的定义，或者增加其他操作，也可能会对字符串的约束条件进行修改。解题的关键思路仍然是通过合理的构造来满足题目要求，减少操作次数。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)：通过巧妙的思维转换来解决问题，与本题的构造思路有相似之处。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：运用贪心算法来优化结果，与本题的贪心思想类似。
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略来减少操作次数，与本题的目标一致。

### 个人心得
题解中未包含个人心得。

---
处理用时：39.97秒