# 题目信息

# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())
```

### 输出

```
()()
```

## 样例 #2

### 输入

```
8 8
(()(()))
```

### 输出

```
(()(()))
```

# AI分析结果

### 题目翻译
## 括号子序列

### 题目描述
括号序列是仅包含字符 "(" 和 ")" 的字符串。正则括号序列是可以通过在序列的原始字符之间插入字符 "1" 和 "+" 转换为正确算术表达式的括号序列。例如，括号序列 "()()" 和 "(())" 是正则的（得到的表达式分别为："(1)+(1)" 和 "((1+1)+1)"），而 ")(", "(" 和 ")" 不是。

子序列是可以通过删除另一个序列中的一些元素而不改变其余元素的顺序得到的序列。

给定一个正则括号序列 $ s $ 和一个整数 $ k $。你的任务是找到一个长度恰好为 $ k $ 的正则括号序列，并且它也是 $ s $ 的子序列。

保证这样的序列总是存在。

### 样例 #1
#### 输入
```
6 4
()(())
```
#### 输出
```
()()
```

### 样例 #2
#### 输入
```
8 8
(()(()))
```
#### 输出
```
(()(()))
```

### 综合分析与结论
这些题解大多采用贪心算法解决问题，核心思路是在扫描原括号序列时，根据左、右括号的数量关系和目标长度 $k$ 来决定是否选取当前括号。具体来说，要保证选取的左括号数量不超过 $k/2$，且右括号数量不超过左括号数量且不超过 $k/2$。

各题解的算法要点基本一致，但在代码实现上有所不同，如有的使用字符数组存储结果，有的使用字符串存储；在边界条件判断和代码结构上也存在差异。

解决的难点在于如何在扫描过程中正确判断是否选取当前括号，以保证最终得到的子序列长度为 $k$ 且是合法的括号序列。

### 评分较高的题解
- **作者：__CrossBow_EXE__ （5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，详细说明了每一步的操作和判断条件。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
char a[200005];
int main() {
    int n,k;
    cin>>n>>k;
    for(int i=1; i<=n; i++) {
        cin>>a[i];
    }
    int l=0,r=0;
    for(int i=1;i<=n;i++){
        if(a[i]=='('&&l<k/2){
            l++;
            cout<<'(';
        }
        if(a[i]==')'&&r<l){
            r++;
            cout<<')';
        }
        if((l+r)==k) return 0;
    } 
    return 0;
}
```
核心实现思想：通过两个变量 `l` 和 `r` 分别记录左、右括号的数量，扫描原序列，当遇到左括号且左括号数量小于 $k/2$ 时输出左括号；当遇到右括号且右括号数量小于左括号数量时输出右括号，若输出的括号总数达到 $k$ 则退出程序。

- **作者：_xxxxx_ （4星）**
    - **关键亮点**：对思路的分析详细，代码规范，使用字符串存储结果，便于输出。
    - **核心代码**：
```cpp
#include <iostream>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, k;
string s;
int numl, numr, cnt = 0;
string ans;
signed main()
{
    cin >> n >> k;
    cin >> s;
    for(int i = 0; i < n; i++)
    {
        if(s[i] == '(' && numl < (k / 2)){
            ans += '(';
            numl++;
        }
        else if(s[i] == ')' && numl > numr && numr < (k / 2)){
            ans += ')';
            numr++;
        }
        else if(numl + numr == k){
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
```
核心实现思想：使用 `numl` 和 `numr` 记录左、右括号数量，`ans` 字符串存储结果，扫描原序列，满足条件时将括号添加到 `ans` 中，达到长度 $k$ 则停止。

- **作者：StudyingFather （4星）**
    - **关键亮点**：思路清晰，对算法的正确性进行了简要说明，代码结构合理。
    - **核心代码**：
```cpp
#include <stdio.h>
char s[200005],res[200005];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    scanf("%s",s);
    if(n==k)printf("%s",s);
    else
    {
        int cntl=0,cntr=0,tot=0;
        for(int i=0;i<n;i++)
            if(s[i]=='(')
            {
                if(cntl!=k/2)
                {
                    cntl++;
                    res[tot++]='(';
                }
            }
            else
            {
                if(cntr!=k/2&&cntl>cntr)
                {
                    cntr++;
                    res[tot++]=')';
                }
            }
        printf("%s",res);
    }
    return 0;
}
```
核心实现思想：使用 `cntl` 和 `cntr` 记录左、右括号数量，`res` 数组存储结果，扫描原序列，满足条件时将括号存入 `res` 数组，最后输出结果。

### 最优关键思路或技巧
采用贪心算法，在扫描原括号序列时，优先选取左括号，直到左括号数量达到 $k/2$，对于右括号，只有在右括号数量小于左括号数量时才选取，这样可以保证得到的子序列是合法的括号序列。

### 可拓展之处
同类型题目可能会有不同的约束条件，如要求子序列的字典序最大或最小，或者给定多个括号序列，要求找出满足条件的公共子序列等。解题思路仍然可以基于贪心算法，结合具体的约束条件进行调整。

### 推荐题目
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
3. [P5734 【深基6.例6】文字处理软件](https://www.luogu.com.cn/problem/P5734)

### 个人心得摘录与总结
- **MorsLin**：没初始化 `b` 数组导致 FST，提醒我们在使用数组时要注意初始化，避免因未初始化而产生的错误。

---
处理用时：37.20秒