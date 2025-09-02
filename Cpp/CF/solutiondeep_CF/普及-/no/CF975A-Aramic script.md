# 题目信息

# Aramic script

## 题目描述

In Aramic language words can only represent objects.

Words in Aramic have special properties:

- A word is a root if it does not contain the same letter more than once.
- A root and all its permutations represent the same object.
- The root $ x $ of a word $ y $ is the word that contains all letters that appear in $ y $ in a way that each letter appears once. For example, the root of "aaaa", "aa", "aaa" is "a", the root of "aabb", "bab", "baabb", "ab" is "ab".
- Any word in Aramic represents the same object as its root.

You have an ancient script in Aramic. What is the number of different objects mentioned in the script?

## 说明/提示

In the first test, there are two objects mentioned. The roots that represent them are "a","ab".

In the second test, there is only one object, its root is "amer", the other strings are just permutations of "amer".

## 样例 #1

### 输入

```
5
a aa aaa ab abb
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
amer arem mrea
```

### 输出

```
1```

# AI分析结果

### 题目翻译
在阿拉米克语中，单词仅能表示物体。

阿拉米克语的单词具有如下特性：
- 若一个单词中每个字母仅出现一次，那么它就是一个词根。
- 一个词根及其所有排列组合都表示同一个物体。
- 对于一个单词 $y$，其词根 $x$ 是一个包含 $y$ 中所有不同字母且每个字母仅出现一次的单词。例如，“aaaa”、“aa”、“aaa” 的词根是 “a”，“aabb”、“bab”、“baabb”、“ab” 的词根是 “ab”。
- 阿拉米克语中的任何单词都与其词根表示相同的物体。

你拥有一份古老的阿拉米克语文本。请问该文本中提及了多少个不同的物体？

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先将输入的字符串转换为其词根（即按字典序排序并去除重复字符），再统计不同词根的数量。各题解的主要区别在于实现方式，如使用不同的数据结构（`map`、`set`）来判重，以及不同的去重和排序方法。

### 题解列表
- **Eason_AC（4星）**
    - **关键亮点**：思路清晰，详细阐述了每个步骤，代码简洁，使用 `map` 进行判重，利用 `sort` 排序和遍历去重。
    - **重点代码**：
```cpp
int n, ans;
string s;
map<string, int> vis;

int main() {
    getint(n);
    while(n--) {
        cin >> s;
        string root = "";
        sort(s.begin(), s.end());
        int len = s.size();
        _for(i, 0, len - 1)
            if(s[i] != s[i - 1]) root += s[i];
        if(!vis[root]) {ans++, vis[root] = 1;}
    }
    writeint(ans);
    return 0;
}
```
核心实现思想：先对输入的字符串排序，再遍历去除重复字符得到词根，用 `map` 判重，若词根未出现过则答案加1。

- **MattL（4星）**
    - **关键亮点**：详细解释了 `sort` 和 `map` 的使用方法，思路清晰，代码可读性高。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans;
string s,t;
map<string,bool> vis;
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>s;
        sort(s.begin(),s.end());
        t=s[0];
        for(int i=1;i<s.size();i++)
            if(s[i]!=s[i-1])
                t+=s[i];
        if(!vis[t])
        {
            ans++;
            vis[t]=true;
        }
    }
    cout<<ans<<endl;
} 
```
核心实现思想：对输入字符串排序，遍历去重得到词根，用 `map` 判重，未出现过则答案加1。

- **Zxsoul（4星）**
    - **关键亮点**：使用 `set` 自动去重，代码简洁，利用 `unique` 函数去重。
    - **重点代码**：
```c
#include <set>
#include <cstdio>
#include <iostream>
using namespace std;

char a[1009];
set<string> se;
int n;
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>a;
        sort(a,a+strlen(a));
        int len=unique(a,a+strlen(a))-a;
        a[len]='\0';
        se.insert(a);  
    }
    printf("%d",se.size());
}
```
核心实现思想：对输入字符数组排序，用 `unique` 去重，设置结束符，将处理后的字符串插入 `set` 自动去重，最后输出 `set` 大小。

### 最优关键思路或技巧
- **排序**：使用 `sort` 函数对字符串按字典序排序，方便后续去重操作。
- **去重**：可以通过遍历比较相邻字符或使用 `unique` 函数去除重复字符。
- **判重**：使用 `map` 或 `set` 数据结构进行判重，避免手动实现哈希表的复杂性。

### 拓展思路
同类型题目通常涉及字符串的处理，如字符串的排序、去重、匹配等。类似算法套路包括使用 `STL` 中的排序、查找、去重函数，以及利用哈希表、集合等数据结构进行判重。

### 推荐洛谷题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及去重和排序操作。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要对数字进行字符串处理和判断。
- [P1308 [NOIP2011 普及组] 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找和匹配。

### 个人心得摘录
- **TLE自动机**：“不会告诉你们我在打cf的时候wa了两次”，总结为在竞赛中做题可能会出现错误，需要不断调试和修正。 

---
处理用时：33.61秒