# 题目信息

# Number of Subsequences

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters "a", "b" and "c" and question marks "?".

Let the number of question marks in the string $ s $ be $ k $ . Let's replace each question mark with one of the letters "a", "b" and "c". Here we can obtain all $ 3^{k} $ possible strings consisting only of letters "a", "b" and "c". For example, if $ s =  $ "ac?b?c" then we can obtain the following strings: $ [ $ "acabac", "acabbc", "acabcc", "acbbac", "acbbbc", "acbbcc", "accbac", "accbbc", "accbcc" $ ] $ .

Your task is to count the total number of subsequences "abc" in all resulting strings. Since the answer can be very large, print it modulo $ 10^{9} + 7 $ .

A subsequence of the string $ t $ is such a sequence that can be derived from the string $ t $ after removing some (possibly, zero) number of letters without changing the order of remaining letters. For example, the string "baacbc" contains two subsequences "abc" — a subsequence consisting of letters at positions $ (2, 5, 6) $ and a subsequence consisting of letters at positions $ (3, 5, 6) $ .

## 说明/提示

In the first example, we can obtain $ 9 $ strings:

- "acabac" — there are $ 2 $ subsequences "abc",
- "acabbc" — there are $ 4 $ subsequences "abc",
- "acabcc" — there are $ 4 $ subsequences "abc",
- "acbbac" — there are $ 2 $ subsequences "abc",
- "acbbbc" — there are $ 3 $ subsequences "abc",
- "acbbcc" — there are $ 4 $ subsequences "abc",
- "accbac" — there is $ 1 $ subsequence "abc",
- "accbbc" — there are $ 2 $ subsequences "abc",
- "accbcc" — there are $ 2 $ subsequences "abc".

So, there are $ 2 + 4 + 4 + 2 + 3 + 4 + 1 + 2 + 2 = 24 $ subsequences "abc" in total.

## 样例 #1

### 输入

```
6
ac?b?c```

### 输出

```
24```

## 样例 #2

### 输入

```
7
???????```

### 输出

```
2835```

## 样例 #3

### 输入

```
9
cccbbbaaa```

### 输出

```
0```

## 样例 #4

### 输入

```
5
a???c```

### 输出

```
46```

# AI分析结果

### 题目内容（中文重写）
# 子序列的数量

## 题目描述
给定一个由小写拉丁字母 "a"、"b"、"c" 和问号 "?" 组成的字符串 $s$。

设字符串 $s$ 中问号的数量为 $k$。我们将每个问号替换为字母 "a"、"b" 或 "c" 中的一个，这样可以得到 $3^{k}$ 种仅由字母 "a"、"b"、"c" 组成的可能字符串。例如，如果 $s =$ "ac?b?c"，那么我们可以得到以下字符串：$[$ "acabac", "acabbc", "acabcc", "acbbac", "acbbbc", "acbbcc", "accbac", "accbbc", "accbcc" $]$。

你的任务是计算所有得到的字符串中子序列 "abc" 的总数。由于答案可能非常大，请将结果对 $10^{9} + 7$ 取模。

字符串 $t$ 的子序列是指从字符串 $t$ 中删除一些（可能为零个）字母后，剩余字母顺序不变所得到的序列。例如，字符串 "baacbc" 包含两个子序列 "abc"，一个由位置 $(2, 5, 6)$ 的字母组成，另一个由位置 $(3, 5, 6)$ 的字母组成。

## 说明/提示
在第一个样例中，我们可以得到 $9$ 个字符串：
- "acabac" — 有 $2$ 个子序列 "abc"；
- "acabbc" — 有 $4$ 个子序列 "abc"；
- "acabcc" — 有 $4$ 个子序列 "abc"；
- "acbbac" — 有 $2$ 个子序列 "abc"；
- "acbbbc" — 有 $3$ 个子序列 "abc"；
- "acbbcc" — 有 $4$ 个子序列 "abc"；
- "accbac" — 有 $1$ 个子序列 "abc"；
- "accbbc" — 有 $2$ 个子序列 "abc"；
- "accbcc" — 有 $2$ 个子序列 "abc"。

所以，总共有 $2 + 4 + 4 + 2 + 3 + 4 + 1 + 2 + 2 = 24$ 个子序列 "abc"。

## 样例 #1
### 输入
```
6
ac?b?c
```
### 输出
```
24
```

## 样例 #2
### 输入
```
7
???????
```
### 输出
```
2835
```

## 样例 #3
### 输入
```
9
cccbbbaaa
```
### 输出
```
0
```

## 样例 #4
### 输入
```
5
a???c
```
### 输出
```
46
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何计算将问号替换后所有字符串中子序列 "abc" 的总数展开。大部分题解采用动态规划的思路，通过定义不同的状态数组和状态转移方程来解决问题。部分题解也从组合数学的角度，通过计算不同组合的方案数来求解。

难点在于处理问号的不确定性，不同题解采用了不同的方式来应对，如考虑问号不同的替换情况、利用前缀和后缀信息、通过数学推导得出通用公式等。

### 所选题解
- **作者：灵茶山艾府 (赞：17)，4星**
    - **关键亮点**：思路清晰，通过遍历字符串，在每个 "b" 或 "?" 处计算答案，将组成 "abc" 的情况分为四种，分别计算方案数并累加，代码实现简洁易懂。
- **作者：tommymio (赞：14)，4星**
    - **关键亮点**：非常套路的计数 DP 题解，定义状态数组 $f[i,0/1/2]$ 表示前 $i$ 个字符构成的分别以 "a"、"b"、"c" 结尾的子序列的个数，通过不同情况的状态转移方程求解，思路明确。
- **作者：Karry5307 (赞：10)，4星**
    - **关键亮点**：从类似于期望的角度思考，设 $f_{i,j}$ 表示所有 $3^m$ 个字符串的前 $i$ 个字符中，子序列 "a"、"ab"、"abc" 的数量之和，通过不同字符的转移方程求解，还提到了加强版的思路。

### 重点代码
#### 灵茶山艾府的代码
```go
package main

import (
    "bufio"
    . "fmt"
    "os"
    "strings"
)

func main() {
    const mod int64 = 1e9 + 7
    var n int
    var s string
    Fscan(bufio.NewReader(os.Stdin), &n, &s)
    pow3 := make([]int64, n)
    pow3[0] = 1
    for i := 1; i < n; i++ {
        pow3[i] = pow3[i-1] * 3 % mod
    }
    c := int64(strings.Count(s, "c"))
    r := int64(strings.Count(s, "?"))
    var ans, a, l int64
    for _, b := range s {
        if b == 'a' {
            a++
        } else if b == 'c' {
            c--
        } else {
            if b == '?' {
                r--
            }
            ans += a * c % mod * pow3[l+r] % mod
            if l > 0 {
                ans += l * c % mod * pow3[l-1+r] % mod
            }
            if r > 0 {
                ans += a * r % mod * pow3[l+r-1] % mod
            }
            if l > 0 && r > 0 {
                ans += l * r % mod * pow3[l+r-2] % mod
            }
            if b == '?' {
                l++
            }
        }
    }
    Print(ans % mod)
}
```
**核心实现思想**：先预处理出 $3$ 的幂次方数组，然后遍历字符串，记录左边 "a" 和 "?" 的数量以及右边 "c" 和 "?" 的数量，在每个 "b" 或 "?" 处根据四种组合情况计算方案数并累加到答案中。

#### tommymio 的代码
```cpp
#include<cstdio>
#define int ll
typedef long long ll;
const int mod=1e9+7;
int f[200005][3];
char s[200005];
signed main() {
    int n,pw=1;
    scanf("%lld%s",&n,s+1);
    for(register int i=1;i<=n;++i) {
        if(s[i]=='?') {
            f[i][0]=(3*f[i-1][0]%mod+pw)%mod;
            f[i][1]=(3*f[i-1][1]%mod+f[i-1][0])%mod;
            f[i][2]=(3*f[i-1][2]%mod+f[i-1][1])%mod; 
            pw=(ll)pw*3%mod;
        }
        else {
            f[i][0]=f[i-1][0];
            f[i][1]=f[i-1][1];
            f[i][2]=f[i-1][2];
            if(s[i]=='a') f[i][0]=(f[i][0]+pw)%mod;
            else f[i][s[i]-'a']=(f[i][s[i]-'a']+f[i-1][s[i]-'a'-1])%mod;
        }
    }
    printf("%d\n",f[n][2]);
    return 0;
}
```
**核心实现思想**：定义状态数组 $f[i][0/1/2]$，根据当前字符是否为 "?" 进行不同的状态转移，最后输出 $f[n][2]$ 作为答案。

#### Karry5307 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=1e9+7,INV3=333333336;
ll n,m,pw=1;
char ch[MAXN];
ll f[MAXN][3];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
    n=read(),scanf("%s",ch+1);
    for(register int i=1;i<=n;i++)
    {
        ch[i]=='?'?m++,pw=(li)pw*3%MOD:1;
    }
    for(register int i=1;i<=n;i++)
    {
        f[i][1]=f[i-1][1],f[i][2]=f[i-1][2],f[i][3]=f[i-1][3];
        if(ch[i]=='a')
        {
            f[i][1]=(f[i][1]+pw)%MOD;
        }
        if(ch[i]=='b')
        {
            f[i][2]=(f[i][2]+f[i-1][1])%MOD;
        }
        if(ch[i]=='c')
        {
            f[i][3]=(f[i][3]+f[i-1][2])%MOD;
        }
        if(ch[i]=='?')
        {
            f[i][1]=(f[i][1]+(li)pw*INV3%MOD)%MOD;
            f[i][2]=(f[i][2]+(li)f[i-1][1]*INV3)%MOD;
            f[i][3]=(f[i][3]+(li)f[i-1][2]*INV3)%MOD;
        }
    }
    printf("%d\n",f[n][3]);
}
```
**核心实现思想**：先统计问号的数量并预处理 $3$ 的幂次方，然后遍历字符串，根据当前字符的不同进行状态转移，最后输出 $f[n][3]$ 作为答案。

### 最优关键思路或技巧
- 动态规划是解决此类问题的核心思路，通过定义合适的状态数组和状态转移方程，可以有效地处理字符串中问号的不确定性。
- 预处理 $3$ 的幂次方可以避免重复计算，提高效率。
- 从不同的角度思考问题，如组合数学的角度，可以得到不同的解题方法。

### 可拓展之处
同类型题或类似算法套路：
- 计算其他特定子序列的数量，如 "abcd" 等，思路类似，只需增加状态数组的维度和相应的状态转移方程。
- 字符串中包含更多种类的字符和通配符，处理方式类似，需要考虑更多的情况。

### 推荐题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：涉及递推和组合数学的思想。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目。
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：可以用动态规划解决的任务安排问题。

### 个人心得摘录与总结
- tommymio：提到自己因为没开 `long long` 而 `WA` 了好几发，提醒我们在处理可能出现大数的问题时，要注意数据类型的选择。

---
处理用时：77.86秒