# 题目信息

# Reverse

## 题目描述

You are given two positive integers $ x $ and $ y $ . You can perform the following operation with $ x $ : write it in its binary form without leading zeros, add $ 0 $ or $ 1 $ to the right of it, reverse the binary form and turn it into a decimal number which is assigned as the new value of $ x $ .

For example:

- $ 34 $ can be turned into $ 81 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 1 $ , reverse it and remove leading zeros, you will get $ 1010001 $ , which is the binary form of $ 81 $ .
- $ 34 $ can be turned into $ 17 $ via one operation: the binary form of $ 34 $ is $ 100010 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 10001 $ , which is the binary form of $ 17 $ .
- $ 81 $ can be turned into $ 69 $ via one operation: the binary form of $ 81 $ is $ 1010001 $ , if you add $ 0 $ , reverse it and remove leading zeros, you will get $ 1000101 $ , which is the binary form of $ 69 $ .
- $ 34 $ can be turned into $ 69 $ via two operations: first you turn $ 34 $ into $ 81 $ and then $ 81 $ into $ 69 $ .

Your task is to find out whether $ x $ can be turned into $ y $ after a certain number of operations (possibly zero).

## 说明/提示

In the first example, you don't even need to do anything.

The fourth example is described in the statement.

## 样例 #1

### 输入

```
3 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
7 4```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 8```

### 输出

```
NO```

## 样例 #4

### 输入

```
34 69```

### 输出

```
YES```

## 样例 #5

### 输入

```
8935891487501725 71487131900013807```

### 输出

```
YES```

# AI分析结果

【题目内容（中文重写）】
# 反转

## 题目描述
给定两个正整数 $x$ 和 $y$。你可以对 $x$ 执行以下操作：将其写成无前导零的二进制形式，在其右侧添加 $0$ 或 $1$，反转该二进制形式，再将其转换为十进制数，将此十进制数作为 $x$ 的新值。

例如：
- $34$ 可以通过一次操作变为 $81$：$34$ 的二进制形式是 $100010$，若添加 $1$，反转并去除前导零，会得到 $1010001$，这是 $81$ 的二进制形式。
- $34$ 可以通过一次操作变为 $17$：$34$ 的二进制形式是 $100010$，若添加 $0$，反转并去除前导零，会得到 $10001$，这是 $17$ 的二进制形式。
- $81$ 可以通过一次操作变为 $69$：$81$ 的二进制形式是 $1010001$，若添加 $0$，反转并去除前导零，会得到 $1000101$，这是 $69$ 的二进制形式。
- $34$ 可以通过两次操作变为 $69$：先将 $34$ 变为 $81$，再将 $81$ 变为 $69$。

你的任务是找出 $x$ 是否可以经过一定次数的操作（可能为零次）变为 $y$。

## 说明/提示
在第一个样例中，甚至不需要进行任何操作。
第四个样例在题目描述中已有说明。

## 样例 #1
### 输入
```
3 3
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
7 4
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
2 8
```
### 输出
```
NO
```

## 样例 #4
### 输入
```
34 69
```
### 输出
```
YES
```

## 样例 #5
### 输入
```
8935891487501725 71487131900013807
```
### 输出
```
YES
```

【算法分类】
深度优先搜索 DFS

【综合分析与结论】
- **思路对比**：
    - ShmilyTY：通过分析操作性质，将问题转化为判断 $x$ 能否通过在最前面和最后面加 $1$ 以及反转两种操作到达 $y$，具体通过求前缀后缀连续 $1$ 的长度并比较。
    - Fishmaster：先判断 $x$ 是否等于 $y$，然后将题目转化为给定两个 $01$ 串，一次操作可以给一个串的首位前或末位后加上一个 $1$，问能否经过若干次操作将一个串变成另一个串，通过枚举 $x$ 可能的初始状态并检查是否能变成 $y$ 的二进制串。
    - XL4453：直接搜索出所有可能的拓展状态，利用剪枝优化，当翻转超过一次之后如果当前值比目标值大两倍以上就直接退出。
    - 蒟蒻丁：分析操作结果，发现可以随意在数字两端添加 $1$，通过脱去原串和目标串的 $1$ 后比对。
    - Tachibana27：同样是爆搜所有可能，在 $x$ 后加 $0$ 相当于直接翻转，利用剪枝，当前状态是目标状态 $y$ 的 $2$ 倍以上就停止搜索。
- **算法要点**：大多题解都基于对操作性质的分析，将问题转化为对二进制串的操作，部分题解采用深度优先搜索来遍历所有可能的状态。
- **解决难点**：主要难点在于分析操作的性质，如添加 $0$ 和 $1$ 后反转的效果，以及如何避免不必要的搜索，各题解通过不同的方式解决，如剪枝、枚举可能的初始状态等。

【所选题解】
- **ShmilyTY（4星）**：
    - **关键亮点**：思路清晰，通过分析操作本质，将问题转化为对二进制串前缀后缀连续 $1$ 的长度比较，逻辑简洁。
- **XL4453（4星）**：
    - **关键亮点**：采用深度优先搜索并结合剪枝优化，代码实现简洁，能有效减少不必要的搜索。
- **Tachibana27（4星）**：
    - **关键亮点**：同样使用深度优先搜索和剪枝，利用 `unordered_map` 进行状态判重，提高效率。

【重点代码】
- **XL4453的代码**：
```cpp
#include<cstdio>
#include<map>
using namespace std;
#define int unsigned long long
int x,y,len,num[100],flag;
map <int,bool> m;
int rev(int now){
    len=0;
    while(now){
        num[++len]=now%2;
        now/=2;
    }
    for(int i=1;i<=len;i++)
        now=now*2+num[i];
    return now;
}
void dfs(int now){
    if(m[now]==1)return;
    m[now]=1;
    if(now==y)flag=1;
    if(now>y*2)return;
    dfs(rev(now));
    now=now<<1;now+=1;
    dfs(rev(now));
}
signed main(){
    scanf("%I64d%I64d",&x,&y);
    dfs(x);dfs(rev(x));
    if(flag)printf("YES\n");
    else printf("NO\n");
    return 0;
}
```
**核心实现思想**：`rev` 函数用于将一个数的二进制形式反转，`dfs` 函数进行深度优先搜索，利用 `map` 进行状态判重，当当前状态等于目标状态时标记成功，当当前状态大于目标状态的两倍时剪枝，搜索时考虑在后面加 $0$（直接反转）和加 $1$ 再反转两种情况。

【关键思路或技巧】
- 分析操作性质，将问题转化为对二进制串的操作，如添加 $0$ 相当于直接反转。
- 利用剪枝优化搜索过程，当当前状态大于目标状态的两倍时停止搜索。
- 使用 `map` 或 `unordered_map` 进行状态判重，避免重复搜索。

【拓展思路】
同类型题可能会涉及更多复杂的二进制操作或状态转移，类似算法套路可以应用于其他需要搜索所有可能状态的题目，如状态压缩搜索、图的遍历等。

【推荐题目】
- P1162 填涂颜色
- P1443 马的遍历
- P1032 字串变换

【个人心得】
- Fishmaster：“这道题我想了将近 $20$ $\text{min}$，想出来了才发现做法如此的无脑。” 总结：有些题目可能一开始觉得困难，但深入思考后会发现解法并不复杂。

---
处理用时：48.62秒