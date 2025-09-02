# 题目信息

# Tennis Championship

## 题目描述

Famous Brazil city Rio de Janeiro holds a tennis tournament and Ostap Bender doesn't want to miss this event. There will be $ n $ players participating, and the tournament will follow knockout rules from the very first game. That means, that if someone loses a game he leaves the tournament immediately.

Organizers are still arranging tournament grid (i.e. the order games will happen and who is going to play with whom) but they have already fixed one rule: two players can play against each other only if the number of games one of them has already played differs by no more than one from the number of games the other one has already played. Of course, both players had to win all their games in order to continue participating in the tournament.

Tournament hasn't started yet so the audience is a bit bored. Ostap decided to find out what is the maximum number of games the winner of the tournament can take part in (assuming the rule above is used). However, it is unlikely he can deal with this problem without your help.

## 说明/提示

In all samples we consider that player number $ 1 $ is the winner.

In the first sample, there would be only one game so the answer is $ 1 $ .

In the second sample, player $ 1 $ can consequently beat players $ 2 $ and $ 3 $ .

In the third sample, player $ 1 $ can't play with each other player as after he plays with players $ 2 $ and $ 3 $ he can't play against player $ 4 $ , as he has $ 0 $ games played, while player $ 1 $ already played $ 2 $ . Thus, the answer is $ 2 $ and to achieve we make pairs $ (1,2) $ and $ (3,4) $ and then clash the winners.

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2
```

## 样例 #4

### 输入

```
10
```

### 输出

```
4
```

# AI分析结果

### 题目中文重写
# 网球锦标赛

## 题目描述
著名的巴西城市里约热内卢举办了一场网球锦标赛，奥斯塔普·本德尔不想错过这个赛事。将会有 $n$ 名选手参赛，并且锦标赛从第一场比赛开始就遵循淘汰赛规则。这意味着，如果有人输掉一场比赛，他将立即退出锦标赛。

组织者仍在安排锦标赛的赛程（即比赛的顺序以及谁将与谁对战），但他们已经确定了一条规则：只有当两名选手其中一人已经参加的比赛场数与另一人已经参加的比赛场数相差不超过 1 时，这两名选手才能相互对战。当然，两名选手都必须赢得他们之前的所有比赛才能继续参加锦标赛。

锦标赛尚未开始，所以观众有点无聊。奥斯塔普决定找出锦标赛冠军最多可以参加多少场比赛（假设使用上述规则）。然而，如果没有你的帮助，他不太可能解决这个问题。

## 说明/提示
在所有样例中，我们都认为 1 号选手是冠军。

在第一个样例中，只会有一场比赛，所以答案是 1。

在第二个样例中，1 号选手可以依次击败 2 号和 3 号选手。

在第三个样例中，1 号选手不能与其他每个选手比赛，因为在他与 2 号和 3 号选手比赛后，他不能与 4 号选手对战，因为 4 号选手已经参加了 0 场比赛，而 1 号选手已经参加了 2 场比赛。因此，答案是 2，为了达到这个结果，我们安排对阵 $(1,2)$ 和 $(3,4)$，然后让获胜者进行对决。

## 样例 #1
### 输入
```
2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
```
### 输出
```
2
```

## 样例 #3
### 输入
```
4
```
### 输出
```
2
```

## 样例 #4
### 输入
```
10
```
### 输出
```
4
```

### 综合分析与结论
这些题解主要围绕如何找出在给定规则下锦标赛冠军最多可参加的比赛场数。思路大多是通过找规律发现与斐波那契数列相关，通过递推的方式来解决问题。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Pkixzx | 通过枚举输入和输出的结果找规律，发现结果呈递增状态，通过递推枚举数的个数来求解 | 利用递推公式 `t3 = t1 + t2` 进行枚举 | 找到结果的递增规律 | 4星 |
| Mickey_snow | 定义 $f(x)$ 为安排 $x$ 场比赛所需要的最少参赛者，通过分析得出 $f(n) = f(n - 1) + f(n - 2)$ 的递推关系，进而求解 | 递推 $f$ 函数，边界条件为 $f(0) = f(-1) = 1$ | 推导出 $f$ 函数的递推关系 | 4星 |
| QWQ_123 | 找规律，考虑 $f_i$ 表示深度为 $i$ 所需的最小点数，$s_i$ 表示前 $i$ 个 $dep$ 的最小点数的总和，通过递推公式 $f_i = 2i + s_{i - 3} + s_{i - 4}$ 求解 | 利用递推公式计算 $f_i$ 和 $s_i$ | 找出 $f_i$ 和 $s_i$ 的递推关系 | 3星 |
| gxxjqqiang | 分析得出要让比赛次数最多且符合要求，人数关系符合斐波那契数列，通过递推求解 | 利用斐波那契数列的递推公式 `z = x + y` 进行计算 | 发现人数关系与斐波那契数列的联系 | 4星 |
| fisheep | 通过分析比赛场数和所需人数的关系，得出符合斐波那契数列，通过枚举场数判断参赛人数是否达到要求求解 | 利用斐波那契数列的递推公式 `z = x + y` 进行枚举 | 分析出比赛场数和人数的斐波那契关系 | 4星 |
| __Hacheylight__ | 从场数角度分析，得出赢 $i$ 把所需人数为 $f[i - 1] + f[i - 2]$，通过递推求解 | 利用斐波那契数列的递推公式 `c = a + b` 进行计算 | 分析出赢 $i$ 把所需人数的递推关系 | 4星 |

### 所选题解
- **Pkixzx（4星）**：关键亮点是通过枚举输入输出找规律，思路简单直接。
- **Mickey_snow（4星）**：关键亮点是通过定义函数 $f(x)$ 并推导出递推关系，逻辑清晰。
- **gxxjqqiang（4星）**：关键亮点是直接分析出人数关系与斐波那契数列的联系，简洁明了。

### 重点代码
#### Pkixzx
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,t=1,t1=1,t2=2,t3=3;
    cin>>n;
    while(t3<=n){
        t1=t2;
        t2=t3;
        t3=t1+t2;
        t++;
    }
    cout<<t<<endl;
} 
```
核心实现思想：通过递推公式 `t3 = t1 + t2` 枚举数的个数，直到 `t3` 大于输入的 `n`，此时 `t` 即为冠军最多可参加的比赛场数。

#### Mickey_snow
```cpp
using System;

namespace CF767E
{
    class Program 
    {
        static void Main(string[] args) 
        {
            Int64 a = 1, b = 1, ans = 0, max = Convert.ToInt64(Console.ReadLine());

            for(int i = 1; true; i++) {
                ans = a + b;
                if(ans > max) {
                    Console.WriteLine((i - 1).ToString());
                    return;
                }
                a = b;b = ans;
            }
        }
    }
}
```
核心实现思想：定义 $f(x)$ 为安排 $x$ 场比赛所需要的最少参赛者，通过递推公式 `ans = a + b` 计算 $f(x)$，直到 `ans` 大于输入的 `max`，此时 `i - 1` 即为冠军最多可参加的比赛场数。

#### gxxjqqiang
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,x=1,y=2,z=3,cnt=1;
int main(){
    scanf("%lld",&n);
    while(z<=n){x=y;y=z;z=x+y;cnt++;}
    return !printf("%lld",cnt);
}
```
核心实现思想：利用斐波那契数列的递推公式 `z = x + y` 进行计算，直到 `z` 大于输入的 `n`，此时 `cnt` 即为冠军最多可参加的比赛场数。

### 最优关键思路或技巧
这些题解的关键思路都是通过分析比赛规则和人数、场数的关系，发现符合斐波那契数列的规律，然后利用递推的方式求解。在处理大数时，要注意使用 `long long` 类型，避免数据溢出。

### 可拓展之处
同类型题或类似算法套路：可以拓展到其他淘汰赛制的比赛安排问题，或者是需要满足一定条件的递推问题。例如，在不同规则下的比赛场次计算、树形结构的节点数量计算等。

### 推荐洛谷题目
1. [P1720 月落乌啼算钱（斐波那契数列）](https://www.luogu.com.cn/problem/P1720)
2. [P1999 高维正方体](https://www.luogu.com.cn/problem/P1999)
3. [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)

### 个人心得摘录与总结
- **Pkixzx**：初看此题毫无头绪，通过递推找规律解决问题，说明在遇到难题时可以从简单情况入手，通过枚举找规律。
- **gxxjqqiang**：提醒不开 `long long` 见祖宗，强调了在处理大数时要注意数据类型的选择，避免数据溢出。

---
处理用时：58.72秒