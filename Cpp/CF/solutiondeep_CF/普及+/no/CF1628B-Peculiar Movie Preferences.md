# 题目信息

# Peculiar Movie Preferences

## 题目描述

给定一个含有$n$个字符串的序列，序列中的每个字符串长度均不超过$3$，判断能否从中选出一个非零子段（可以不连续），使得子段中的字符串按照在序列中的顺序首尾相连构成一个回文串。如果能，输出"YES"，否则输出"NO"。

## 样例 #1

### 输入

```
6
5
zx
ab
cc
zx
ba
2
ab
bad
4
co
def
orc
es
3
a
b
c
3
ab
cd
cba
2
ab
ab```

### 输出

```
YES
NO
NO
YES
YES
NO```

# AI分析结果

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先判断是否存在单个字符串本身就是回文串，若不存在，则重点考虑两个字符串拼接成回文串的情况。各题解的主要区别在于实现方式和数据结构的选择。

- **思路对比**：多数题解都证明了若存在回文子序列，必然存在由 $1$ 个或 $2$ 个字符串组成的回文串，然后分情况讨论长度为 $2$ 和 $3$ 的字符串的匹配情况。
- **算法要点**：大部分题解使用了 `map` 或类似的哈希结构来存储字符串及其出现位置，方便快速查找。
- **解决难点**：关键在于判断不同长度字符串之间的匹配关系，以及处理多组数据时的初始化问题。

### 所选题解
- **liu_chen_hao（5星）**
    - **关键亮点**：思路清晰，代码结构简洁，详细分情况讨论了各种可能构成回文串的情况，且对多组数据的处理有明确的注释。
- **baoziwu2（4星）**
    - **关键亮点**：先证明了只需要判断 $1$ 个或 $2$ 个字符串拼接的情况，然后使用 `std::map` 和 `std::string` 实现，代码简洁明了。
- **清烛（4星）**
    - **关键亮点**：同样证明了回文子序列可由 $1$ 或 $2$ 个串扩展而来，使用 `std::set` 维护字符串，实现简单易懂。

### 重点代码
#### liu_chen_hao 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int t,n,f;
string s[N],p;
map<string,int> hs;

int main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1; i<=n; i++) cin>>s[i];
        
        // 注意多测清空 
        hs.clear();
        f=0;
        
        // 判断有没有本身就是回文串的 
        for(int i=1; i<=n; i++)
            if(s[i].size()==1 || (s[i].size()==2 && s[i][0]==s[i][1]) || (s[i].size()==3 && s[i][0]==s[i][2]))
            {
                f=1;
                puts("YES");
                break;
            }
        if(f) continue;
        
        // 存到map里 
        for(int i=1; i<=n; i++)
            if(hs.find(s[i])==hs.end()) hs[s[i]]=i;
        
        // 依次扫描 
        for(int i=1; i<=n; i++)
        {
            // 对于长度为2的 
            if(s[i].size()==2)
            {
                p="";
                p+=s[i][1];
                p+=s[i][0];
                if(hs.find(p)!=hs.end())
                {
                    f=1;
                    puts("YES");
                    break;
                }
            }
            // 其余的必为长度为3的 
            else
            {
                // 存在他本身的倒序串 
                p="";
                p+=s[i][2];
                p+=s[i][1];
                p+=s[i][0];
                if(hs.find(p)!=hs.end())
                {
                    f=1;
                    puts("YES");
                    break;
                }
                
                // 它前两位的倒序串
                p="";
                p+=(s[i][1]);
                p+=(s[i][0]);
                if(hs.find(p)!=hs.end() && hs[p]>i)
                {
                    f=1;
                    puts("YES");
                    break;
                }
                
                // 它后两位的倒序串
                p="";
                p+=s[i][2];
                p+=s[i][1];
                if(hs.find(p)!=hs.end() && hs[p]<i)
                {
                    f=1;
                    puts("YES");
                    break;
                }
            }
        }
        if(!f) puts("NO");
    }

    return 0;
}
```
**核心实现思想**：先判断是否存在单个回文串，若不存在则将所有字符串存入 `map` 中，再依次扫描每个字符串，分长度为 $2$ 和 $3$ 两种情况讨论其是否能与其他字符串构成回文串。

#### baoziwu2 的代码
```C++
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
const int N = 100010;

int T, n;
string str[N];
map<string, int> mp;

bool checkPalindrome(string &s) {
    return s.front() == s.back();
}

int main() {
    cin >> T;
    while(T--) {
        mp.clear();
        cin >> n;
        bool flag = false;
        
        for(int i = 1; i <= n; ++ i) {
            cin >> str[i];
            if(!mp[str[i]]) mp[str[i]] = i;
        }
        
        for(int i = 1; i <= n; ++ i) {
            if(flag) break;
            if(checkPalindrome(str[i])) flag = true;
            else if(str[i].length() == 2) {
                string t = str[i];
                reverse(t.begin(), t.end());
                if(mp[t]) flag = true;
            } else if(str[i].length() == 3) {
                string t = str[i]; 
                reverse(t.begin(), t.end());
                if(mp[t]) flag = true;
                
                string t1 = t.substr(1);
                if(mp[t1] and mp[t1] > i) flag = true;
                
                string t2 = t.substr(0, 2);
                if(mp[t2] and mp[t2] < i) flag = true;
            }
        }
        
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```
**核心实现思想**：先将所有字符串存入 `map` 中，然后遍历每个字符串，判断其是否为回文串，若不是则分长度为 $2$ 和 $3$ 两种情况讨论其是否能与其他字符串构成回文串。

#### 清烛的代码
```cpp
set<string> mp, mpl;

bool check(string s) {
    if (s.size() == 1) return 1;
    if (s.front() == s.back()) return 1;
    return 0;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        mp.clear(), mpl.clear();
        bool flg = 0;
        FOR(i, 1, n) {
            string s; cin >> s;
            if (check(s)) flg = 1;
            string ss = s; reverse(ss.begin(), ss.end());
            if (mp.count(ss)) flg = 1;
            if (mpl.count(ss)) flg = 1;
            ss.pop_back();
            if (mp.count(ss)) flg = 1;

            mp.insert(s);
            if (s.size() == 3) s.pop_back(), mpl.insert(s);
        }
        if (flg) print("YES");
        else print("NO");
    }
    return output(), 0;
}
```
**核心实现思想**：使用两个 `std::set` 维护字符串，遍历每个字符串，判断其是否为回文串，若不是则判断其反转串或部分反转串是否在 `set` 中。

### 最优关键思路或技巧
- **利用字符串长度限制**：由于字符串长度不超过 $3$，可以大大减少可能的情况，通过分类讨论长度为 $2$ 和 $3$ 的字符串的匹配关系来解决问题。
- **使用哈希结构**：`map` 或 `set` 等哈希结构可以快速查找字符串，提高算法效率。

### 拓展思路
同类型题可以是判断多个字符串能否拼接成指定类型的字符串，或者判断字符串子序列是否满足某种特定条件。类似算法套路是先分析问题的特殊性质，减少不必要的情况，然后使用合适的数据结构来存储和查找信息。

### 推荐洛谷题目
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P5733 【深基6.例1】自动修正](https://www.luogu.com.cn/problem/P5733)

### 个人心得摘录与总结
- **无钩七不改名**：比赛时想用 $2$ 个字符串拼合骗分，没想到真的可以过，因为根本没必要用到 $3$ 个或 $3$ 个串以上。总结：可以先从简单情况入手尝试，说不定能发现问题的本质。
- **HoshizoraZ**：期末考结束后康复训练，碰到这题刚开始降智了想复杂了不少时间，做题时把 $2 + 3 + 3$ 看作了简单串，写了一堆冗余的情况。总结：做题时要冷静分析，避免把问题复杂化，仔细分析各种情况，避免遗漏或错误判断。

---
处理用时：56.02秒