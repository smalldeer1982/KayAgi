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

### 题目翻译
# 十六进制的数字

## 题目描述
在一个美好的七月早晨，主机世界发生了一件可怕的事情：邪恶的病毒梅加比特不知怎么地访问了他同样邪恶的妹妹十六进制的内存。他在那里加载了大量从 1 到 $n$ 的不同自然数，试图完全控制她的能量。

但他的计划失败了。原因很简单：十六进制只能处理以二进制格式书写的数字。这意味着，如果一个十进制表示的数字中包含除 0 和 1 之外的字符，它就不会被存储在内存中。现在梅加比特想知道，有多少个数字被成功加载了。

## 说明/提示
当 $n = 10$ 时，答案包括数字 1 和 10。

## 样例 #1
### 输入
```
10
```

### 输出
```
2
```

### 综合分析与结论
这些题解的核心都是找出 1 到 $n$ 中各数位仅包含 0 和 1 的数的个数。思路主要分为以下几类：
1. **递归搜索**：利用递归函数，从 1 开始，通过 `x * 10` 和 `x * 10 + 1` 生成符合条件的数，当数大于 $n$ 时停止递归。
2. **打表法**：预先计算出 $10^9$ 内所有符合条件的数，存储在数组中，输入 $n$ 后遍历数组找到第一个大于 $n$ 的数，其下标即为答案。
3. **暴力枚举**：通过多重循环生成所有可能的由 0 和 1 组成的数，再判断是否在 1 到 $n$ 的范围内。
4. **公式计算**：先找出不大于 $n$ 的最大的只由 0 和 1 组成的数，再通过组合数学的方法计算符合条件的数的个数。

### 所选题解
- **作者：char32_t（5 星）**
    - **关键亮点**：思路清晰，提供了递归和打表两种解法，代码简洁易懂。
    - **核心代码**：
```cpp
// 递归解法
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
核心思想：从 1 开始递归生成符合条件的数，若数小于等于 $n$，计数器加 1，继续递归生成 `m * 10` 和 `m * 10 + 1`。

- **作者：test_check（4 星）**
    - **关键亮点**：详细解释了 DFS 思路，代码规范，使用了快读优化输入。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void dfs(int cur) {
    if(cur>n) return;
    else ++ans;
    dfs(cur*10+1);
    dfs(cur*10);
}
int main() {
    n=read();
    dfs(1);
    printf("%d",ans);
    return 0;
}
```
核心思想：使用 DFS 从 1 开始搜索，若当前数小于等于 $n$，答案加 1，继续搜索 `cur * 10` 和 `cur * 10 + 1`。

- **作者：damage（4 星）**
    - **关键亮点**：提供了三种解法，对每种解法的复杂度进行了分析，思路全面。
    - **核心代码（DFS 解法）**：
```cpp
#include<stdio.h>
int n,res;
void dfs(int x) {
    if(x>n) return ;
    ++res;
    dfs(x*10);
    dfs(x*10+1);
    return ;
}
int main() {
    scanf("%d",&n);
    dfs(1);
    printf("%d\n",res);
    return 0;
}
```
核心思想：与上述 DFS 解法类似，从 1 开始递归生成符合条件的数，统计个数。

### 最优关键思路或技巧
递归搜索是本题的最优思路，利用递归函数生成符合条件的数，避免了不必要的枚举，时间复杂度较低。同时，打表法在数据范围固定时可以快速得到答案，但需要预先计算和存储大量数据。

### 拓展思路
同类型题或类似算法套路：
1. 寻找特定格式的数字，如只包含某些特定数字的数。
2. 递归生成满足条件的组合或排列。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察递归和组合数学。
2. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：考察递归和动态规划。
3. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：考察递归生成排列。

### 个人心得摘录与总结
- **作者：HiroshiRealm**：受第 15 个测试点 TLE 困扰，决定采用队列的方法解题。总结：当遇到超时问题时，可以尝试更换算法或数据结构来优化。
- **作者：Andysun06**：指出第 15 个测试点有坑，使用打表法时需要特殊处理。总结：在做题时要注意特殊测试点，对边界情况进行单独处理。 

---
处理用时：33.23秒