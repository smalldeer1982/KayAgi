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
这些题解大多采用贪心算法解决问题。核心思路是利用正则括号序列中左右括号数量相等的特性，在遍历原序列时，尽可能选取左括号直到达到 $k/2$ 个，同时保证右括号数量不超过左括号数量且最终右括号也达到 $k/2$ 个。
- **思路对比**：多数题解思路一致，从左到右遍历原序列，按规则选取左右括号；部分题解如 FutureThx 是通过删除字符来实现，开始新的记忆 是分别从右往左和从左往右删除左右括号。
- **算法要点**：核心要点是控制左右括号的选取数量，确保最终得到长度为 $k$ 的正则括号子序列。
- **解决难点**：难点在于保证选取的括号序列是正则的，即右括号数量不超过左括号数量，且最终左右括号数量都为 $k/2$。

### 所选题解
- **__CrossBow_EXE__（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，详细说明了每一步的操作。
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
核心实现思想：遍历字符数组，遇到左括号且左括号数量小于 $k/2$ 时输出左括号；遇到右括号且右括号数量小于左括号数量时输出右括号；当输出的括号数量达到 $k$ 时退出程序。

- **_xxxxx_（5星）**
    - **关键亮点**：先分析数据范围确定算法复杂度，思路清晰，代码规范。
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
核心实现思想：遍历字符串，遇到左括号且左括号数量小于 $k/2$ 时将左括号加入答案字符串；遇到右括号且右括号数量小于左括号数量且右括号数量小于 $k/2$ 时将右括号加入答案字符串；当答案字符串长度达到 $k$ 时退出循环并输出答案。

- **Sai_t（4星）**
    - **关键亮点**：明确指出贪心思想，代码简洁，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r;
string s,ans;
int main(){
    cin>>n>>k>>s;
    for(int i=0;i<n;i++){
        if(s[i]=='('){
            if(l*2<k){
                ans+='(';
                l++;
            }
        }
        else{
            if(r*2<k&&r<l){
                ans+=')';
                r++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
核心实现思想：遍历字符串，遇到左括号且左括号总数小于 $k$ 时将左括号加入答案字符串；遇到右括号且右括号总数小于 $k$ 且右括号数量小于左括号数量时将右括号加入答案字符串；最后输出答案字符串。

### 最优关键思路或技巧
采用贪心算法，从左到右遍历原序列，优先选取左括号直到达到 $k/2$ 个，同时保证右括号数量不超过左括号数量且最终右括号也达到 $k/2$ 个。

### 可拓展之处
同类型题如判断括号序列是否合法、求最长合法括号子序列等。类似算法套路可用于处理其他需要满足特定条件的子序列问题，如合法的数字序列、合法的字符序列等。

### 推荐题目
- [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)
- [P3310 [SDOI2014] 数数](https://www.luogu.com.cn/problem/P3310)

### 个人心得摘录与总结
- **MorsLin**：没初始化 $b$ 数组，导致 FST（失败测试）。总结：在使用数组时要注意初始化，避免因未初始化导致的错误。 

---
处理用时：47.67秒