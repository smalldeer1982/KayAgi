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

### 题目翻译
#### 单通配符模式匹配

#### 题目描述
给定两个小写英文单词 $s$ 和 $t$，其中 $s$ 包含不超过一个的 `*`。$s$ 的长度为 $n$，$t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s$ 和 $t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu`、`lugu`、`luooooogu` 都是匹配的，但与字符串 `lougu`、`log`、`lu^_^gu`、`lu114514gu` 都是不匹配的。

如果给定的 $s$ 和 $t$ 是匹配的，输出 `YES`，否则输出 `NO`。

#### 说明/提示
对于 $100\%$ 的数据，$1 \leq n, m \leq 2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

#### 样例 #1
##### 输入
```
6 10
code*s
codeforces
```
##### 输出
```
YES
```

#### 样例 #2
##### 输入
```
6 5
vk*cup
vkcup
```
##### 输出
```
YES
```

#### 样例 #3
##### 输入
```
1 1
v
k
```
##### 输出
```
NO
```

#### 样例 #4
##### 输入
```
9 6
gfgf*gfgf
gfgfgf
```
##### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是围绕字符串匹配展开，根据字符串 $s$ 中是否有 `*` 进行分类讨论。对于有 `*` 的情况，通常是先比较 `*` 前面的部分，再比较 `*` 后面的部分。

#### 算法要点对比
- **特判长度**：多数题解都先判断 $n$ 和 $m$ 的关系，若 $n > m + 1$ 则直接判定不匹配。
- **无 `*` 情况**：直接比较两个字符串是否相等。
- **有 `*` 情况**：
    - 从前往后比较 `*` 前的部分。
    - 从后往前比较 `*` 后的部分。

#### 难点解决对比
- **`*` 匹配问题**：通过分别处理 `*` 前后的字符串来解决，确保前后部分分别匹配。
- **边界情况**：如 `*` 在开头、结尾等情况，不同题解有不同的处理方式，但核心都是保证前后部分匹配。

### 评分较高的题解
1. **作者：小闸蟹（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `std::string` 的 `find` 和 `substr` 方法，提高了代码的可读性和可维护性。
    - **核心代码**：
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
            if (Str1[i]!= Str2[i])
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
        for (int i = n - 1, j = m - 1; i > p; --i, --j) // 从后往前扫
        {
            if (Str1[i]!= Str2[j])
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
核心实现思想：先特判长度，再判断是否有 `*`。若没有 `*` 则直接比较两个字符串；若有 `*` 则分别从前往后和从后往前比较 `*` 前后的部分。

2. **作者：To_Carpe_Diem（4星）**
    - **关键亮点**：同样使用 `std::string` 的方法，代码简洁易懂，逻辑清晰。
    - **核心代码**：
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
    } else if (s.find('*')!= string::npos) {
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
核心实现思想：先判断两个字符串是否相等，若不相等则判断是否有 `*`。若有 `*` 则截取 `*` 前后的部分，与 $t$ 对应部分比较。

3. **作者：2012zxt（4星）**
    - **关键亮点**：利用字符串库函数进行拼接和比较，思路清晰。
    - **核心代码**：
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
核心实现思想：先特判长度，再判断是否有 `*`。若没有 `*` 则直接比较；若有 `*` 则拼接 $t$ 中 `*` 前后的部分，与去掉 `*` 的 $s$ 比较。

### 最优关键思路或技巧
- 使用 `std::string` 的 `find` 和 `substr` 方法，方便处理字符串的查找和截取。
- 先特判长度和是否有 `*`，减少不必要的比较。

### 拓展思路
同类型题可能会增加通配符的数量或种类，或者对匹配规则进行更复杂的定义。类似算法套路可以是分情况讨论，分别处理不同部分的匹配。

### 推荐题目
1. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
3. [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

### 个人心得摘录与总结
- **作者：happybob**：尝试用正则表达式解题，但因数据量太大出现 `RE` 或 `TLE` 问题，最终改用 `string` 模拟。总结是正则表达式虽然可以解决问题，但在处理大数据时可能存在时间复杂度问题，本题正解是 `string` 模拟。

---
处理用时：50.87秒