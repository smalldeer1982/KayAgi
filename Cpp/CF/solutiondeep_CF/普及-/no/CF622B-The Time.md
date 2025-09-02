# 题目信息

# The Time

## 题目描述

You are given the current time in $ 24 $ -hour format hh:mm. Find and print the time after $ a $ minutes.

Note that you should find only the time after $ a $ minutes, see the examples to clarify the problem statement.

You can read more about $ 24 $ -hour format here [https://en.wikipedia.org/wiki/24-hour\_clock](https://en.wikipedia.org/wiki/24-hour_clock).

## 样例 #1

### 输入

```
23:59
10
```

### 输出

```
00:09
```

## 样例 #2

### 输入

```
20:20
121
```

### 输出

```
22:21
```

## 样例 #3

### 输入

```
10:10
0
```

### 输出

```
10:10
```

# AI分析结果

### 题目翻译
# 时间

## 题目描述
给定当前时间，格式为 24 小时制的 hh:mm。请找出并输出经过 a 分钟后的时间。

请注意，你只需找出经过 a 分钟后的时间，查看示例以明确问题描述。

你可以在 [https://en.wikipedia.org/wiki/24-hour_clock](https://en.wikipedia.org/wiki/24-hour_clock) 上了解更多关于 24 小时制的信息。

## 样例 #1
### 输入
```
23:59
10
```
### 输出
```
00:09
```

## 样例 #2
### 输入
```
20:20
121
```
### 输出
```
22:21
```

## 样例 #3
### 输入
```
10:10
0
```
### 输出
```
10:10
```

### 算法分类
模拟

### 综合分析与结论
这些题解的整体思路都是先从输入中分离出小时和分钟，然后将经过的分钟数加到当前分钟上，处理分钟和小时的进位，最后处理输出时的前导零。不同题解在输入处理、代码结构和细节实现上存在差异。

### 所选题解
- **xzllll07（4星）**
    - **关键亮点**：思路清晰，将输入、计算和输出分别封装成函数，代码结构清晰，易于理解和维护。
    - **核心代码**：
```cpp
void in()
{
    a=getchar(),b=getchar(),c=getchar(),d=getchar(),e=getchar();
    hour=(a-'0')*10+(b-'0');
    min=(d-'0')*10+(e-'0');
}
void calc()
{
    scanf("%d",&n);
    min+=n;
    hour+=(min/60);
    min%=60;
    hour%=24;
}
void out()
{
    if (hour<10) printf("0");
    printf("%d:",hour);
    if (min<10) printf("0");
    printf("%d",min);
}
int main()
{	
    in();
    calc(); 
    out();
    return 0;
}
```
    - **核心实现思想**：`in` 函数负责从输入中提取小时和分钟，`calc` 函数处理时间的计算，`out` 函数处理输出时的前导零。

- **UKE自动稽（4星）**
    - **关键亮点**：代码简洁，直接使用 `scanf` 读取时间，利用格式化输出 `%02d` 处理前导零。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int h, m;
    scanf("%d:%d", &h,&m);
    int n;
    scanf("%d",&n);
    m += n; h += m / 60;
    h %= 24;
    m %= 60;
    printf("%02d:%02d\n", h, m);
    return 0;
}
```
    - **核心实现思想**：使用 `scanf` 读取时间，将经过的分钟数加到当前分钟上，处理进位和取余，最后使用 `printf` 格式化输出。

- **Dimly_dust（4星）**
    - **关键亮点**：使用字符串读取时间，通过字符运算分离出小时和分钟，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string n;
    cin>>n;
    int a=(n[0]-'0')*10+n[1]-'0',b=(n[3]-'0')*10+n[4]-'0';
    int s;
    cin>>s;
    b+=s;
    a=(a+(b/60))%24;
    b%=60;
    if(a<10) cout<<0;
    cout<<a<<":";
    if(b<10) cout<<0;
    cout<<b;
    return 0;
}
```
    - **核心实现思想**：读取字符串形式的时间，将字符转换为数字，处理时间计算和进位，最后处理前导零输出。

### 最优关键思路或技巧
- 利用取余运算处理小时和分钟的进位，确保时间在 24 小时制和 60 分钟制的范围内。
- 使用格式化输出或条件判断处理输出时的前导零。

### 拓展思路
同类型题目可能会涉及到更复杂的时间计算，如计算两个时间之间的差值、处理不同时区的时间转换等。类似算法套路是先将时间拆分为小时、分钟等基本单位，然后根据具体问题进行计算和处理。

### 推荐洛谷题目
- P1423 小玉在游泳：涉及时间和距离的简单计算，与本题的时间计算有一定相似性。
- P1089 津津的储蓄计划：需要处理每月的收支和时间的推移，类似于本题的时间模拟。
- P1909 买铅笔：虽然主要是贪心算法，但也涉及到数量和价格的计算，与本题的计算逻辑有一定的类比性。

### 个人心得摘录与总结
- **七夜**：提到使用快读读取整数时在输入字符串时出过问题，所以只用快读读入 `int` 类型的整数，提醒我们在使用输入方式时要注意适用性。

---
处理用时：32.25秒