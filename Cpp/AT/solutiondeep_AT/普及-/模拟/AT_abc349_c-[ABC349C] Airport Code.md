# 题目信息

# [ABC349C] Airport Code

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_c

英大文字からなる長さ $ 3 $ の文字列 $ T $ が、英小文字からなる文字列 $ S $ の **空港コード** であるとは、 $ T $ が $ S $ から次のいずれかの方法により得られることとします。

- $ S $ の長さ $ 3 $ の（連続とは限らない）部分列をとり、それを英大文字に変換したものを $ T $ とする
- $ S $ の長さ $ 2 $ の（連続とは限らない）部分列をとり、それを英大文字に変換したものの末尾に `X` を追加したものを $ T $ とする
 
文字列 $ S $, $ T $ が与えられるので、 $ T $ が $ S $ の空港コードであるか判定してください。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 3 $ 以上 $ 10^5 $ 以下の文字列
- $ T $ は英大文字からなる長さ $ 3 $ の文字列
 
### Sample Explanation 1

`narita` の部分列 `nrt` を英大文字に変換した文字列 `NRT` は、 `narita` の空港コードです。

### Sample Explanation 2

`losangeles` の部分列 `la` を英大文字に変換した文字列 `LA` の末尾に `X` を追加したもの `LAX` は、 `losangeles` の空港コードです。

## 样例 #1

### 输入

```
narita

NRT```

### 输出

```
Yes```

## 样例 #2

### 输入

```
losangeles

LAX```

### 输出

```
Yes```

## 样例 #3

### 输入

```
snuke

RNG```

### 输出

```
No```

# AI分析结果

### 题目中文重写
# [ABC349C] 机场代码

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_c

由大写英文字母组成的长度为 $3$ 的字符串 $T$ 是由小写英文字母组成的字符串 $S$ 的 **机场代码**，是指 $T$ 可以通过以下任意一种方法从 $S$ 得到：
- 取 $S$ 的长度为 $3$ 的（不一定连续的）子序列，将其转换为大写字母，得到 $T$。
- 取 $S$ 的长度为 $2$ 的（不一定连续的）子序列，将其转换为大写字母，在末尾添加 `X`，得到 $T$。

给定字符串 $S$ 和 $T$，请判断 $T$ 是否是 $S$ 的机场代码。

## 说明/提示

### 约束条件
- $S$ 是由小写英文字母组成的长度在 $3$ 到 $10^5$ 之间（包含 $3$ 和 $10^5$）的字符串。
- $T$ 是由大写英文字母组成的长度为 $3$ 的字符串。

### 示例解释 1
`narita` 的子序列 `nrt` 转换为大写字母后的字符串 `NRT` 是 `narita` 的机场代码。

### 示例解释 2
`losangeles` 的子序列 `la` 转换为大写字母后的字符串 `LA`，在末尾添加 `X` 得到的 `LAX` 是 `losangeles` 的机场代码。

## 样例 #1

### 输入
```
narita
NRT
```

### 输出
```
Yes
```

## 样例 #2

### 输入
```
losangeles
LAX
```

### 输出
```
Yes
```

## 样例 #3

### 输入
```
snuke
RNG
```

### 输出
```
No
```

### 综合分析与结论
这些题解的核心思路都是模拟判断 $T$ 是否是 $S$ 的机场代码，主要围绕两种情况展开：一是 $T$ 完全是 $S$ 的长度为 $3$ 的子序列转换而来；二是 $T$ 的前两个字符是 $S$ 的长度为 $2$ 的子序列转换而来，最后一个字符为 `X`。

- **思路**：大多题解先统一 $S$ 和 $T$ 的大小写，然后遍历 $S$，判断是否能按顺序找到 $T$ 中的字符。对于 $T$ 最后一个字符为 `X` 的情况进行特判。
- **算法要点**：主要是通过循环遍历字符串，利用下标或标记来记录匹配情况。部分题解使用了 `find` 函数来查找字符位置。
- **解决难点**：关键在于处理子序列不一定连续的情况，以及正确判断 $T$ 最后一个字符为 `X` 的特殊情况。

### 所选题解
- **MinimumSpanningTree（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接分情况判断 $T$ 是否是 $S$ 的子序列，时间复杂度为 $O(n)$，能轻松通过本题。
- **XXh0919（4星）**
    - **关键亮点**：将判断子序列的逻辑封装成函数，代码结构清晰，通过 `pop_back` 处理 $T$ 最后一个字符为 `X` 的情况，实现简洁。
- **liaoxingrui（4星）**
    - **关键亮点**：详细解释了大小写转换的原理，通过 ASCII 码进行转换，判断子序列的逻辑清晰，注释详细。

### 重点代码及核心实现思想
#### MinimumSpanningTree
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string s,t;
int n,p=0;
bool flag;
int main()
{
    cin>>s>>t;
    n=s.size();
    for(int i=0;i<n;i++) s[i]+='A'-'a';
    if(t[2]=='X')
    {
        for(int i=0;i<n;i++)
        {
            if(p<=1&&s[i]==t[p]) p++;
        }
        if(p>1) flag=true;
    }
    p=0;
    for(int i=0;i<n;i++)
    {
        if(p<=2&&s[i]==t[p]) p++;
    }
    if(p>2) flag=true;
    flag?printf("Yes"):printf("No");
    return 0;
} 
```
**核心实现思想**：先将 $S$ 全部转换为大写字母，对于 $T$ 最后一个字符为 `X` 的情况，只判断前两个字符是否是 $S$ 的子序列；否则判断 $T$ 整体是否是 $S$ 的子序列。

#### XXh0919
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=4e6+15;

string s,t;
bool flag;

bool check(string s,string t){
    int i=0;
    for(auto e:s){
        if(i<t.size()&&e+'A'-'a'==t[i]){
            ++i;	
        }
    }	
    return i==t.size();
}

void solve(){
    cin>>s>>t;
    if(check(s,t))flag=1;
    if(t[2]=='X')
        t.pop_back(),flag|=check(s,t);
    if(flag)puts("Yes");
    else puts("No");
}

signed main(){
    ios::sync_with_stdio(0);
    int T=1;
//  cin>>T;
    while(T--)solve();
    return 0;
}
```
**核心实现思想**：将判断子序列的逻辑封装在 `check` 函数中，对于 $T$ 最后一个字符为 `X` 的情况，先去掉最后一个字符，再判断前两个字符是否是 $S$ 的子序列。

#### liaoxingrui
```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,len;
bool bj;
string s,t;
int main(){
    cin>>s>>t;
    len=s.size();
    for(int i=0;i<3;i++)
        t[i]+=32;
    if(t[2]=='x')
        bj=1;
    for(int i=0;i<len;i++){
        if(s[i]==t[tot])
            tot++;
        if(tot==3-bj){
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
    return 0;
}
```
**核心实现思想**：先将 $T$ 转换为小写字母，对于 $T$ 最后一个字符为 `x` 的情况，只判断前两个字符是否是 $S$ 的子序列；否则判断 $T$ 整体是否是 $S$ 的子序列。

### 最优关键思路或技巧
- **统一大小写**：将 $S$ 和 $T$ 的大小写统一，方便后续比较。
- **特判处理**：对于 $T$ 最后一个字符为 `X` 的情况进行特判，简化判断逻辑。
- **子序列判断**：通过遍历 $S$，按顺序匹配 $T$ 中的字符，利用下标或标记记录匹配情况。

### 可拓展之处
同类型题目可能会改变子序列的长度或规则，或者增加字符串的数量。类似算法套路可以应用于判断一个字符串是否是另一个字符串的子序列，或者在多个字符串中寻找满足特定条件的子序列。

### 推荐洛谷题目
1. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：涉及子序列和递推的思想。
2. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：需要判断是否能组合出特定的结果，与判断子序列有相似之处。
3. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：直接考察子序列的相关知识。

### 个人心得摘录与总结
- **I_Love_DS**：在解题过程中尝试了多种方法，如纯模拟、dfs 等，但都遇到了问题。纯模拟会出现重复标记的问题，dfs 会超时，需要不断优化。总结出在处理子序列问题时要注意避免重复标记，并且要考虑算法的时间复杂度。
- **int_stl**：这道题虽然简单，但坑点很多，吃了 $4$ 罚时。提醒我们在解题时要仔细考虑各种情况，避免遗漏。

---
处理用时：54.90秒