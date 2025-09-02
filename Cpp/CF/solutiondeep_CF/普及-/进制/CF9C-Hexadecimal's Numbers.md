# 题目信息

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10
```

### 输出

```
2```

# AI分析结果

### 题目内容翻译
#### 十六进制的数字

### 题目描述
在一个美好的七月清晨，主机里发生了一件可怕的事情：卑鄙的病毒“兆字节”不知怎么地获取了他同样卑鄙的妹妹“十六进制”的内存访问权限。他往里面加载了大量从 1 到 $n$ 的不同自然数，企图完全控制她的能量。

但他的计划失败了。原因很简单：“十六进制”除了二进制格式书写的数字外，无法处理任何信息。这意味着，如果一个十进制表示的数字中包含除 0 和 1 以外的字符，它就不会被存储在内存中。现在“兆字节”想知道，成功加载了多少个数字。

### 说明/提示
当 $n = 10$ 时，答案包含数字 1 和 10。

### 样例 #1
#### 输入
```
10
```
#### 输出
```
2
```

### 综合分析与结论
这些题解主要围绕找出 1 到 $n$ 中各数位只包含 0 和 1 的数的个数这一问题展开，采用了多种不同的思路和算法。
- **思路对比**
    - **递归构造**：通过递归生成符合条件的数，如 `x * 10` 和 `x * 10 + 1` 的形式，不断扩展直到超过 $n$。
    - **打表法**：预先计算出 $10^9$ 内所有符合条件的数，存储在数组中，输入 $n$ 后遍历数组找到第一个大于 $n$ 的数，其索引即为答案。
    - **暴力枚举**：通过多重循环生成所有可能的由 0 和 1 组成的数，再判断是否在 1 到 $n$ 的范围内。
    - **公式计算**：先找出不大于 $n$ 的最大的只由 0 和 1 组成的数，再根据该数的每一位为 1 的情况，利用 $2$ 的幂来计算答案。
- **算法要点对比**
    - **递归构造**：时间复杂度为 $O(2^{lg\ n})$，空间复杂度取决于递归深度。
    - **打表法**：时间复杂度为 $O(1)$ 查找，空间复杂度为 $O(512)$。
    - **暴力枚举**：时间复杂度较高，为 $O(2^{10})$，因为是十重循环。
    - **公式计算**：时间复杂度为 $O(lg\ n)$，需要预处理 $2$ 的幂。
- **解决难点对比**
    - **递归构造**：需要正确设置递归边界，避免无限递归。
    - **打表法**：需要预先计算并存储所有可能的结果，占用一定的空间。
    - **暴力枚举**：代码实现较为繁琐，且效率较低。
    - **公式计算**：需要理解如何找出最大的只由 0 和 1 组成的数，并正确利用 $2$ 的幂计算答案。

### 所选题解
- **作者：char32_t（5 星）**
    - **关键亮点**：思路清晰，提供了递归构造和打表两种方法，代码简洁易懂。
    - **核心代码（递归构造）**：
```cpp
#include<cstdio>
int n;
int count=0;
int binary(int m) {
    if(m>n) return 0;
    else count++;
    binary(m*10);
    binary(m*10+1);
}
int main() {
    scanf("%d", &n);
    binary(1);
    printf("%d", count);
    return 0;
}
```
核心实现思想：从 1 开始递归生成符合条件的数，每次递归有两种扩展方式 `m * 10` 和 `m * 10 + 1`，当生成的数大于 $n$ 时停止递归。
- **作者：test_check（4 星）**
    - **关键亮点**：详细解释了 dfs 的思路和递归调用的原理，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
void dfs(int cur)
{
    if(cur>n) return;
    else ++ans;
    dfs(cur*10+1);
    dfs(cur*10);
}
int main()
{
    n=read();
    dfs(1);
    printf("%d",ans);
    return 0;
}
```
核心实现思想：使用深度优先搜索，从 1 开始递归扩展，每次扩展有两种选择 `cur * 10 + 1` 和 `cur * 10`，当扩展的数大于 $n$ 时停止。
- **作者：damage（4 星）**
    - **关键亮点**：分析了多种方法的复杂度，提供了 dfs 和公式计算两种方法，代码有注释。
    - **核心代码（公式计算）**：
```cpp
#include<string>
#include<iostream>
using namespace std;
int n,two[20],res,sized,digit;
string s;
bool flag;
int main()
{
    ios::sync_with_stdio(false);
    two[0]=1;
    for(register int i=1;i<11;++i) two[i]=two[i-1]<<1;
    cin>>s;
    sized=s.size();
    digit=sized-1;
    for(register int i=0;i<sized;--digit,++i)
    {
        if(s[i]>49) flag=true;
        if(s[i]>48||flag) res+=two[digit];
    }
    cout<<res<<endl;
    return 0;
}
```
核心实现思想：先预处理 $2$ 的幂，将输入的数作为字符串处理，从高位到低位遍历，根据每一位的情况和之前是否出现大于 1 的数字来累加答案。

### 最优关键思路或技巧
递归构造是较为优秀的思路，利用符合条件的数的特性（`x * 10` 和 `x * 10 + 1`）进行递归扩展，避免了不必要的枚举，时间复杂度较低。同时，打表法在数据范围固定且较小的情况下，可以实现 $O(1)$ 的查询。

### 可拓展之处
同类型题可能会要求找出其他特定格式数字的个数，如只包含 2 和 3 的数字，或者在不同进制下的类似问题。类似算法套路可以采用递归构造、打表、枚举等方法，根据具体问题进行调整。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及递归和组合枚举。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：需要对数字的二进制表示进行操作。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：涉及质数判断和回文数的构造。

### 个人心得摘录与总结
- **作者：HiroshiRealm**：深受 #15 测试点 TLE 困扰，决定采用队列的方法解决问题，体现了在遇到性能问题时尝试不同算法的思路。
- **作者：Andysun06**：指出第 15 个测试点有坑，使用打表法时需要特殊处理，提醒我们在做题时要注意边界情况和特殊数据。 

---
处理用时：48.31秒