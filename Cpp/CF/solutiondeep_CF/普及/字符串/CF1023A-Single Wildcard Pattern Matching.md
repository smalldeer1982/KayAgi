# 题目信息

# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 1
v
k
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf
```

### 输出

```
NO
```

# AI分析结果

### 题解综合分析与结论
这些题解主要围绕带单个通配符 `*` 的字符串匹配问题展开，核心思路都是先处理一些特殊情况，再根据 `*` 的位置将字符串分成前后两部分进行匹配。

- **思路对比**：多数题解先特判长度关系和无 `*` 的情况，再对 `*` 前后的字符串分别与目标字符串对应部分匹配；部分题解使用正则表达式，但因性能问题需额外处理。
- **算法要点**：主要涉及字符串的遍历、查找、截取和比较操作，通过循环和条件判断来确定是否匹配。
- **解决难点**：关键在于处理 `*` 可替换任意字符串的情况，通过从前往后和从后往前的扫描来确定匹配范围。

### 所选题解
- **作者：小闸蟹 (赞：2)  4星**
    - **关键亮点**：思路清晰，代码简洁，先特判长度和无 `*` 的情况，再分别从前后扫描匹配，可读性高。
```cpp
#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    if (n > m + 1)  // 特判长度
    {
        std::cout << "NO" << std::endl;
        return 0;
    }

    std::string Str1, Str2;
    std::cin >> Str1 >> Str2;

    auto Pos = Str1.find('*');
    if (Pos == std::string::npos)   // 没有'*'的情况
    {
        if (Str1 == Str2)
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
    else
    {
        auto p = static_cast<int>(Pos);
        for (int i = 0; i < p; ++i) // 从前往后扫
        {
            if (Str1[i] != Str2[i])
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
        for (int i = n - 1, j = m - 1; i > p; --i, --j) // 从后往前扫
        {
            if (Str1[i] != Str2[j])
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }

        std::cout << "YES" << std::endl;
    }

    return 0;
}
```
- **作者：To_Carpe_Diem (赞：1)  4星**
    - **关键亮点**：代码简洁，利用 `find` 和 `substr` 函数处理字符串，逻辑清晰，直接判断前后部分是否匹配。
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    if (s == t) {
        cout << "YES" << endl;
    } else if (s.find('*') != string::npos) {
        int wildcard_pos = s.find('*');
        string s_prefix = s.substr(0, wildcard_pos);
        string s_suffix = s.substr(wildcard_pos+1);
        if (t.length() >= s.length()-1 && t.substr(0, s_prefix.length()) == s_prefix && t.substr(t.length()-s_suffix.length()) == s_suffix) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
```
- **作者：2012zxt (赞：0)  4星**
    - **关键亮点**：思路明确，通过标记 `*` 位置，截取和拼接字符串进行比较，逻辑清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,pos;
string s,t;
bool flag;//flag表示s中有没有星号
int main(){
    cin>>n>>m>>s>>t;
    if(n>m+1){//我的长度比你大两个以上，肯定不行
        cout<<"NO";
        return 0;
    }
    s="#"+s;//让有效下标从1到n
    t="#"+t;
    for(int i=1;i<=n;i++)
        if(s[i]=='*')
            flag=1,pos=i;//出现了！星号！存一下位置
    if(!flag){//没有星号，听天由命
        if(s==t)
            cout<<"YES";
        else cout<<"NO";
        return 0;
    }
    int tmp1=n-pos;//存一下星号后面的字符个数
    string tmp2=t.substr(1,pos-1)+t.substr(m-tmp1+1);//如上拼接。
    s=s.substr(1,pos-1)+s.substr(pos+1);//把星号去掉好比较
    if(s==tmp2)
        cout<<"YES";
    else cout<<"NO";
    return 0;
}
```

### 最优关键思路或技巧
- 先特判长度关系，若 `s` 的长度大于 `t` 的长度加 1，则肯定不匹配。
- 对于无 `*` 的情况，直接比较两个字符串是否相等。
- 对于有 `*` 的情况，记录 `*` 的位置，分别从前往后和从后往前扫描，比较 `*` 前后的字符串是否与目标字符串对应部分相等。

### 可拓展之处
同类型题可能会有多个通配符或不同类型的通配符，类似算法套路是根据通配符的规则将字符串分段处理，通过循环和条件判断来确定匹配情况。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码
- P1598 垂直柱状图
- P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here

### 个人心得摘录与总结
- **happybob**：尝试用正则表达式解题，但因数据量太大出现 `RE` 或 `TLE` 问题，认识到 `STL` 的时间复杂度问题，最终采用 `string` 模拟的方法解决问题。总结为在处理大数据量问题时，要谨慎使用 `STL` 库，优先考虑更高效的算法。 

---
处理用时：49.64秒