# 题目信息

# Dreamoon and Stairs

## 题目描述

Dreamoon wants to climb up a stair of $ n $ steps. He can climb $ 1 $ or $ 2 $ steps at each move. Dreamoon wants the number of moves to be a multiple of an integer $ m $ .

What is the minimal number of moves making him climb to the top of the stairs that satisfies his condition?

## 说明/提示

For the first sample, Dreamoon could climb in 6 moves with following sequence of steps: {2, 2, 2, 2, 1, 1}.

For the second sample, there are only three valid sequence of steps {2, 1}, {1, 2}, {1, 1, 1} with 2, 2, and 3 steps respectively. All these numbers are not multiples of 5.

## 样例 #1

### 输入

```
10 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
# Dreamoon 爬楼梯

## 题目描述
Dreamoon 想要爬上一个有 $n$ 级台阶的楼梯。他每次可以爬 $1$ 级或 $2$ 级台阶。Dreamoon 希望他爬楼梯的步数是整数 $m$ 的倍数。

满足他这个条件的情况下，爬上楼梯的最少步数是多少？

## 说明/提示
对于第一个样例，Dreamoon 可以用 6 步爬完楼梯，步数序列为：{2, 2, 2, 2, 1, 1}。

对于第二个样例，只有三种有效的步数序列 {2, 1}、{1, 2}、{1, 1, 1}，步数分别为 2、2 和 3。这些步数都不是 5 的倍数。

## 样例 #1
### 输入
```
10 2
```
### 输出
```
6
```

## 样例 #2
### 输入
```
3 5
```
### 输出
```
-1
```

### 综合分析与结论
这些题解的核心思路基本一致，都是先确定爬楼梯步数的范围，再在这个范围内找出最小的能被 $m$ 整除的步数。确定步数范围时，最少步数在 $n$ 为偶数时是 $\frac{n}{2}$，$n$ 为奇数时是 $\frac{n}{2}+1$；最多步数是 $n$。

算法要点在于明确步数范围并进行枚举判断。难点在于理解为什么步数范围是连续可实现的，实际上通过将两个一步变为一个两步或反之，就能走出该区间内所有连续的自然数。

### 所选题解
- **作者：ahawzlc（5星）**
    - **关键亮点**：思路清晰，代码简洁，变量名虽随意但不影响理解，对奇数情况的处理使用位运算提高效率。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,m,x,ccf=0;
    cin>>n>>m;
    if(n&1) ccf=1;
    int mn=n/2+ccf,mx=n;
    for(int i=mn;i<=mx;i++) {
        if(i%m==0) {
            cout<<i<<endl;
            return 0;
        }
    }
    puts("-1");
    return 0;
}
```
核心实现思想：先根据 $n$ 的奇偶性确定最少步数，再从最少步数到最多步数进行枚举，找到第一个能被 $m$ 整除的步数输出，若未找到则输出 -1。

- **作者：「已注销」（4星）**
    - **关键亮点**：不采用枚举，直接计算出第一个比 $\lceil\frac{n}{2}\rceil$ 大的 $m$ 的倍数，时间复杂度更低。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int n,m,l;
int main(){
    cin>>n>>m;
    l=n+1>>1;
    if(n/m*m<l)cout<<-1;
    else cout<<l+(m-l%m)%m;
}
```
核心实现思想：先计算出最少步数 $l$，然后判断 $n$ 范围内是否存在 $m$ 的倍数大于等于 $l$，若存在则计算并输出该倍数，不存在则输出 -1。

- **作者：Register（4星）**
    - **关键亮点**：思路清晰，对步数范围的解释详细，自定义了向上取整函数，代码可读性高。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int ceil2(int x){
    return x%2?x/2+1:x/2;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=ceil2(n);i<=n;i++)
        if(i%m==0) {cout<<i<<endl;return 0;}
    cout<<-1<<endl;
    return 0;
}
```
核心实现思想：通过自定义函数计算最少步数，然后从最少步数到最多步数进行枚举，找到第一个能被 $m$ 整除的步数输出，若未找到则输出 -1。

### 最优关键思路或技巧
- 确定步数范围：最少步数根据 $n$ 的奇偶性确定，最多步数为 $n$，在该范围内枚举或直接计算满足条件的步数。
- 位运算：使用 `n&1` 判断 $n$ 的奇偶性，提高效率。
- 向上取整技巧：如 `n/2+n%2` 或自定义向上取整函数实现 $n/2$ 向上取整。

### 拓展思路
同类型题可能会改变每次走的步数选择，如可以走 1、2、3 步等，或者增加其他限制条件，如某些台阶不能走等。解题思路依然是先确定步数范围，再根据条件进行枚举或计算。

### 推荐洛谷题目
- P1216 [USACO1.5] 数字三角形 Number Triangles
- P1048 [NOIP2005 普及组] 采药
- P1616 疯狂的采药

### 个人心得摘录与总结
- **LucasXu80**：提到了向上取整的小技巧 `n/2+n%2`，可以避免使用 if 语句，简化代码。总结就是在编程中可以多积累一些小技巧来优化代码。

---
处理用时：28.59秒