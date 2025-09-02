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
在一个美好的七月早晨，主机里发生了一件可怕的事情：卑鄙的病毒梅加比特不知怎么地访问了他同样卑鄙的妹妹十六进制的内存。他在那里加载了大量从 1 到 $n$ 的不同自然数，以完全控制她的能量。

但他的计划失败了。原因很简单：十六进制除了二进制格式的数字外，无法感知任何信息。这意味着，如果一个十进制表示的数字中包含除 0 和 1 以外的字符，它就不会被存储在内存中。现在梅加比特想知道，有多少个数字被成功加载了。

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
这些题解的核心目标都是找出 1 到 $n$ 中各数位仅包含 0 和 1 的数的个数。主要思路有递归搜索、打表、循环枚举、公式计算等。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|char32_t|递归搜索和打表|递归生成 $n*10$ 或 $n*10 + 1$ 形式的数；打表存储 $10^9$ 内所有符合条件的数|确定递归边界，避免生成超出范围的数|4星|
|test_check|深度优先搜索（DFS）|从 1 开始 DFS，递归生成符合条件的数|确定递归边界和递归调用方式|4星|
|damage|枚举、DFS、公式计算|枚举每个数判断；DFS 生成符合条件的数；根据数字特征用公式计算|优化枚举复杂度，避免 DFS 爆栈|3星|
|BBD186587|十重循环枚举|通过十重循环生成所有可能的数并判断|避免使用系统 `pow` 函数带来的问题|2星|
|HiroshiRealm|队列存储|用队列存储符合条件的数，队头用于生成新数和判断|合理使用队列进行数的生成和判断|3星|
|lixiao189|递归构造和公式计算|递归生成符合条件的数；先找出最大符合条件的数，再用公式计算|找出最大符合条件的数并正确使用公式计算|3星|
|Loser_King|DFS 和 BFS|DFS 递归生成符合条件的数；BFS 用优先队列存储和扩展节点|BFS 中避免队列元素溢出|3星|
|shenzuxin|九重循环枚举|通过九重循环生成所有可能的数并判断|处理特殊数据点|2星|
|LevenKoko|DFS|从 0 开始 DFS，递归生成符合条件的数|处理特殊情况，避免重复计数|2星|
|Andysun06|打表|存储 $10^9$ 内所有符合条件的数，根据输入查找|处理特殊数据点|3星|

### 所选题解
- **char32_t（4星）**
    - 关键亮点：思路清晰，提供了递归和打表两种方法，代码可读性高。
    - 核心代码（递归）：
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
    - 核心实现思想：通过递归生成 $n*10$ 或 $n*10 + 1$ 形式的数，当数超过 $n$ 时停止递归，同时统计符合条件的数的个数。

- **test_check（4星）**
    - 关键亮点：详细解释了 DFS 思路和递归调用方式，代码简洁。
    - 核心代码：
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
    - 核心实现思想：从 1 开始进行 DFS，递归生成符合条件的数，当数超过 $n$ 时停止递归，统计符合条件的数的个数。

### 最优关键思路或技巧
- 递归搜索：利用符合条件的数的特征（$n*10$ 或 $n*10 + 1$），通过递归快速生成并统计符合条件的数，避免了大量不必要的枚举。
- 打表：对于范围较小的情况，提前存储所有符合条件的数，根据输入直接查找，时间复杂度为 $O(1)$。

### 可拓展之处
同类型题可能会改变数字的组成条件，如各数位只包含 2 和 3 等，解题思路仍然可以采用递归搜索或打表。类似算法套路还可用于生成满足特定条件的数字序列，如超级素数等问题。

### 推荐题目
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：涉及递归函数的调用和记忆化搜索。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要使用递归进行组合枚举。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：可以使用深度优先搜索或广度优先搜索解决。

### 个人心得摘录与总结
- HiroshiRealm：深受超时困扰，决定采用队列方法，参考超级素数的做法，用队列存储符合条件的数进行求解。总结：当遇到超时问题时，可以尝试换一种数据结构或算法思路来解决。
- Andysun06：指出第 15 个测试点有坑，需要进行防御处理。总结：在做题时要注意特殊数据点，对可能出现的边界情况进行处理。 

---
处理用时：33.79秒