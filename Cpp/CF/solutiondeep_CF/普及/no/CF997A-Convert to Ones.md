# 题目信息

# Convert to Ones

## 题目描述

You've got a string $ a_1, a_2, \dots, a_n $ , consisting of zeros and ones.

Let's call a sequence of consecutive elements $ a_i, a_{i + 1}, \ldots, a_j $ ( $ 1\leq i\leq j\leq n $ ) a substring of string $ a $ .

You can apply the following operations any number of times:

- Choose some substring of string $ a $ (for example, you can choose entire string) and reverse it, paying $ x $ coins for it (for example, «0101101» $ \to $ «0111001»);
- Choose some substring of string $ a $ (for example, you can choose entire string or just one symbol) and replace each symbol to the opposite one (zeros are replaced by ones, and ones — by zeros), paying $ y $ coins for it (for example, «0101101» $ \to $ «0110001»).

You can apply these operations in any order. It is allowed to apply the operations multiple times to the same substring.

What is the minimum number of coins you need to spend to get a string consisting only of ones?

## 说明/提示

In the first sample, at first you need to reverse substring $ [1 \dots 2] $ , and then you need to invert substring $ [2 \dots 5] $ .

Then the string was changed as follows:

«01000» $ \to $ «10000» $ \to $ «11111».

The total cost of operations is $ 1 + 10 = 11 $ .

In the second sample, at first you need to invert substring $ [1 \dots 1] $ , and then you need to invert substring $ [3 \dots 5] $ .

Then the string was changed as follows:

«01000» $ \to $ «11000» $ \to $ «11111».

The overall cost is $ 1 + 1 = 2 $ .

In the third example, string already consists only of ones, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 1 10
01000
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 10 1
01000
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7 2 3
1111111
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写
**题目描述**

你有一个由0和1组成的字符串 $a_1, a_2, \dots, a_n$。

我们称连续的元素序列 $a_i, a_{i+1}, \ldots, a_j$（$1 \leq i \leq j \leq n$）为字符串 $a$ 的子串。

你可以多次应用以下操作：

- 选择字符串 $a$ 的某个子串（例如，可以选择整个字符串）并反转它，花费 $x$ 个硬币（例如，«0101101» $ \to $ «0111001»）；
- 选择字符串 $a$ 的某个子串（例如，可以选择整个字符串或单个字符）并将每个字符替换为其相反的值（0替换为1，1替换为0），花费 $y$ 个硬币（例如，«0101101» $ \to $ «0110001»）。

你可以以任意顺序应用这些操作。允许对同一个子串多次应用操作。

你需要花费最少的硬币，将字符串转换为只包含1的字符串。

**说明/提示**

在第一个样例中，首先你需要反转子串 $[1 \dots 2]$，然后你需要反转子串 $[2 \dots 5]$。

然后字符串的变化如下：

«01000» $ \to $ «10000» $ \to $ «11111».

总操作花费为 $1 + 10 = 11$。

在第二个样例中，首先你需要反转子串 $[1 \dots 1]$，然后你需要反转子串 $[3 \dots 5]$。

然后字符串的变化如下：

«01000» $ \to $ «11000» $ \to $ «11111».

总花费为 $1 + 1 = 2$。

在第三个样例中，字符串已经只包含1，所以答案为 $0$。

**样例 #1**

输入：
```
5 1 10
01000
```

输出：
```
11
```

**样例 #2**

输入：
```
5 10 1
01000
```

输出：
```
2
```

**样例 #3**

输入：
```
7 2 3
1111111
```

输出：
```
0
```

### 算法分类
贪心

### 综合分析与结论
这道题的核心思路是通过贪心策略，选择最小花费的操作将字符串中的所有0转换为1。大多数题解都采用了统计0的段数，然后根据操作1和操作2的花费选择最优的操作顺序。具体来说，操作1可以将两段0合并为一段，而操作2可以直接将一段0转换为1。因此，最终的花费公式为 `min(x, y) * (cnt - 1) + y`，其中 `cnt` 是0的段数。

### 所选题解
#### 题解1：作者：torque (赞：5)
**星级：5星**
**关键亮点：**
- 清晰解释了贪心策略，通过统计0的段数来最小化花费。
- 代码简洁，逻辑清晰，直接计算最小花费。

**代码核心实现思想：**
```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 400001
#define ll long long
#define rnt register int
using namespace std;
char s[N];
ll n,x,y,cnt;
int main(){
    cin>>n>>x>>y;
    scanf("%s",s+1);s[0]='1';
    for(rnt i=1;i<=n;i=-~i) if(s[i]=='0' && s[i-1]=='1') cnt=-~cnt;
    if(!cnt) cout<<"0";
    else cout<<y+(cnt-1)*min(x,y);
    return 0;
}
```

#### 题解2：作者：如履薄冰 (赞：3)
**星级：4星**
**关键亮点：**
- 提供了两种可能的解法，并比较了它们的优劣。
- 详细解释了如何通过压缩字符串来简化问题。

**代码核心实现思想：**
```cpp
#include<iostream>
#include<string>
using namespace std;
long long cnt,n,x,y;
string edit;
int main(){
    cin>>n>>x>>y;
    cin>>edit;
    for(int i=0;i<edit.size();i++){
        if(edit[i]=='0'&&edit[i+1]=='1'){
            cnt++;
        }
    }
    if(edit[edit.size()-1]=='0'){
        cnt++;
    }
    if(cnt==0){
        cout<<0;
    }else{
        cout<<min(cnt*y,(cnt-1)*x+y);
    }
    return 0;
}
```

#### 题解3：作者：Laoda_Bryant (赞：1)
**星级：4星**
**关键亮点：**
- 通过图示解释了操作1和操作2的等价性。
- 提供了清晰的思路和公式推导。

**代码核心实现思想：**
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n,x,y,sum=0;
int main(){
    cin>>n>>x>>y;
    cin>>s;
    s[n]='1';
    for(int i=0;i<n;i++){
        if(s[i]=='0'&&s[i+1]=='1') sum++;
    }
    if(sum==0) cout<<0;
    else cout<<(sum-1)*min(x,y)+y;
    return 0;
}
```

### 最优关键思路或技巧
1. **贪心策略**：通过统计0的段数，选择最小花费的操作顺序。
2. **公式推导**：最终花费公式为 `min(x, y) * (cnt - 1) + y`，其中 `cnt` 是0的段数。
3. **字符串压缩**：将连续的相同字符压缩成一个字符，简化问题。

### 可拓展之处
- 类似的问题可以扩展到其他字符转换问题，如将字符串中的所有1转换为0。
- 可以进一步优化操作顺序，考虑更复杂的操作组合。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：36.04秒