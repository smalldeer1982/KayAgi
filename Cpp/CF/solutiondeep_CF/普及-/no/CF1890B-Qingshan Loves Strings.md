# 题目信息

# Qingshan Loves Strings

## 题目描述

Qingshan has a string $ s $ , while Daniel has a string $ t $ . Both strings only contain $ \texttt{0} $ and $ \texttt{1} $ .

A string $ a $ of length $ k $ is good if and only if

- $ a_i \ne a_{i+1} $ for all $ i=1,2,\ldots,k-1 $ .

For example, $ \texttt{1} $ , $ \texttt{101} $ , $ \texttt{0101} $ are good, while $ \texttt{11} $ , $ \texttt{1001} $ , $ \texttt{001100} $ are not good.

Qingshan wants to make $ s $ good. To do this, she can do the following operation any number of times (possibly, zero):

- insert $ t $ to any position of $ s $ (getting a new $ s $ ).

Please tell Qingshan if it is possible to make $ s $ good.

## 说明/提示

In the first test case, $ s $ is good initially, so you can get a good $ s $ by doing zero operations.

In the second test case, you can do the following two operations (the inserted string $ t $ is underlined):

1. $ \texttt{1}\underline{\texttt{010}}\texttt{11} $
2. $ \texttt{10101}\underline{\texttt{010}}\texttt{1} $

and get $ s = \texttt{101010101} $ , which is good.

In the third test case, there is no way to make $ s $ good after any number of operations.

## 样例 #1

### 输入

```
5
1 1
1
0
3 3
111
010
3 2
111
00
6 7
101100
1010101
10 2
1001001000
10```

### 输出

```
Yes
Yes
No
No
No```

# AI分析结果

### 题目翻译
# 青山喜欢字符串

## 题目描述
青山有一个字符串 $s$，而丹尼尔有一个字符串 $t$。两个字符串都只包含 `0` 和 `1`。

一个长度为 $k$ 的字符串 $a$ 是好的，当且仅当：
- 对于所有的 $i = 1, 2, \ldots, k - 1$，都有 $a_i \ne a_{i + 1}$。

例如，`1`、`101`、`0101` 是好的，而 `11`、`1001`、`001100` 不是好的。

青山想让 $s$ 变成好的字符串。为此，她可以进行以下操作任意次数（可能为零次）：
- 将 $t$ 插入到 $s$ 的任意位置（得到一个新的 $s$）。

请告诉青山是否有可能让 $s$ 变成好的字符串。

## 说明/提示
在第一个测试用例中，$s$ 最初就是好的，所以你可以通过不进行任何操作来得到一个好的 $s$。

在第二个测试用例中，你可以进行以下两次操作（插入的字符串 $t$ 用下划线标出）：
1. `1`$\underline{\texttt{010}}$`11`
2. `10101`$\underline{\texttt{010}}$`1`

然后得到 $s =$ `101010101`，这是好的。

在第三个测试用例中，无论进行多少次操作，都没有办法让 $s$ 变成好的字符串。

## 样例 #1
### 输入
```
5
1 1
1
0
3 3
111
010
3 2
111
00
6 7
101100
1010101
10 2
1001001000
10
```

### 输出
```
Yes
Yes
No
No
No
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先判断 $s$ 是否本身就是好的字符串，若不是，则判断 $t$ 是否是好的字符串，因为若 $t$ 不是好的，无论如何插入都无法使 $s$ 变好。对于 $s$ 中相邻且相同的字符，需要在中间插入 $t$，且要满足一定条件（$t$ 的两端与相邻相同字符不同）才能使 $s$ 变好。各题解主要区别在于实现细节和判断条件的表达方式。

### 所选题解
- **作者：No_Rest (4星)**
    - **关键亮点**：思路清晰，通过分类讨论详细列出各种情况，代码实现中使用多个标志变量来保存不同状态，逻辑明确，可读性高。
- **作者：BugGod (4星)**
    - **关键亮点**：代码简洁，将判断字符串是否合法的逻辑封装成函数，使主函数逻辑更加清晰，易于理解。
- **作者：lowbit (4星)**
    - **关键亮点**：代码简洁，使用位运算和逻辑与操作，高效地判断插入 $t$ 后是否合法。

### 重点代码
#### No_Rest 的代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int T, n, m;
string s, t;
bool flag0, flag1, f0, f1;
int main(){
    scanf("%d", &T);
    while(T--){
        flag0 = flag1 = f0 = f1 = 0;
        scanf("%d%d", &n, &m);
        cin >> s >> t;
        for(int i = 0; i < s.size() - 1; ++i)
            if(s[i] == s[i + 1] && s[i] == '0') flag0 = f0 = 1;
            else if(s[i] == s[i + 1]) flag0 = f1 = 1;
        for(int i = 0; i < t.size() - 1; ++i)
            if(t[i] == t[i + 1]) flag1 = 1;
        if(!flag0) puts("yes");
        else if(f0 && f1) puts("no");
        else if(flag0 && flag1) puts("no");
        else if(f0 && t[0] == '1' && t[t.size() - 1] == '1') puts("yes");
        else if(f1 && t[0] == '0' && t[t.size() - 1] == '0') puts("yes");
        else puts("no");
    }
    return 0;
}
```
**核心实现思想**：使用 `flag0` 和 `flag1` 分别标记 $s$ 和 $t$ 是否为好的字符串，`f0` 和 `f1` 标记 $s$ 中相邻且相同的字符是 `0` 还是 `1`，然后根据不同情况输出结果。

#### BugGod 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int check(string s)
{
    for(int i=1;i<s.size();i++)
    {
        if(s[i-1]==s[i])return 0;
    }
    return 1;
}
int n,m,tt;
string s,t;
signed main()
{
    cin>>tt;
    while(tt--)
    {
        cin>>n>>m>>s>>t;
        if(check(s)){cout<<"Yes"<<endl;continue;}
        if(!check(t)){cout<<"No"<<endl;continue;}
        int flag=1;
        for(int i=1;i<n;i++)
        {
            if(s[i-1]==s[i])
            {
                if(s[i-1]==t[0]||s[i]==t[m-1])
                {
                    flag=0;
                    break;
                }
            }
        }
        if(flag)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
```
**核心实现思想**：封装 `check` 函数判断字符串是否合法，先判断 $s$ 是否合法，再判断 $t$ 是否合法，若都合法，则检查 $s$ 中相邻相同字符插入 $t$ 后是否合法。

#### lowbit 的代码
```cpp
cin >> n >> m;
scanf("%s%s", s+1, t+1);
int fl=1, p=1;
rep(i, 2, m) fl &= t[i] != t[i-1];
rep(i, 2, n) {
   if(s[i] == s[i-1]) fl &= t[1]!=s[i-1] && t[m]!=s[i], p=0;
}
printf(fl|p ? "Yes":"No");
```
**核心实现思想**：使用 `fl` 标记 $t$ 是否合法，`p` 标记 $s$ 是否本身合法，遍历 $s$ 中相邻相同字符，判断插入 $t$ 后是否合法，最后根据 `fl` 和 `p` 的值输出结果。

### 最优关键思路或技巧
- 分类讨论：将不同情况进行分类，如 $s$ 本身是否好、$t$ 本身是否好、$s$ 中相邻相同字符的情况等，使逻辑更加清晰。
- 标记变量：使用多个标记变量来保存不同状态，方便后续判断。
- 封装函数：将判断字符串是否合法的逻辑封装成函数，提高代码的可读性和可维护性。

### 拓展思路
同类型题目可能会有不同的字符串操作规则，如可以进行替换、删除等操作，或者字符串包含更多字符种类。解题思路仍然是先分析操作规则对字符串合法性的影响，再根据不同情况进行分类讨论。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得
- **hikariyo_**：赛后意识到自己把题目变复杂了。这提醒我们在解题时要尽量简化思路，避免过度复杂化问题。

---
处理用时：48.83秒