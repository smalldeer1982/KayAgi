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

### 题目内容重写

**题目描述**

著名的巴西城市里约热内卢举办了一场网球锦标赛，Ostap Bender不想错过这一盛事。共有 $n$ 名选手参加，比赛从一开始就采用淘汰赛制。这意味着，如果某人在一场比赛中失利，他将立即被淘汰出局。

组织者仍在安排比赛的对阵表（即比赛的顺序以及谁将与谁对战），但他们已经确定了一条规则：两名选手只有在他们之前参加的比赛场次相差不超过1的情况下才能对战。当然，两名选手都必须赢得他们之前的所有比赛才能继续参加比赛。

比赛尚未开始，观众们有些无聊。Ostap决定找出在满足上述规则的情况下，锦标赛冠军最多可以参加多少场比赛。然而，如果没有你的帮助，他很可能无法解决这个问题。

**说明/提示**

在所有样例中，我们假设选手1是冠军。

在第一个样例中，只有一场比赛，因此答案是1。

在第二个样例中，选手1可以连续击败选手2和选手3。

在第三个样例中，选手1不能与每位选手对战，因为在他与选手2和选手3比赛后，他不能与选手4对战，因为选手4已经参加了0场比赛，而选手1已经参加了2场比赛。因此，答案是2，为了达到这个结果，我们让选手1和选手2对战，选手3和选手4对战，然后让胜者对决。

**样例 #1**

**输入**

```
2
```

**输出**

```
1
```

**样例 #2**

**输入**

```
3
```

**输出**

```
2
```

**样例 #3**

**输入**

```
4
```

**输出**

```
2
```

**样例 #4**

**输入**

```
10
```

**输出**

```
4
```

### 题解综合分析与结论

通过对多条题解的分析，可以发现大多数题解都采用了**斐波那契数列**的思路来解决这个问题。具体来说，问题的核心在于如何安排比赛，使得冠军能够参加尽可能多的比赛，同时满足两名选手在比赛前参加的比赛场次相差不超过1的条件。通过观察，可以发现这个问题与斐波那契数列的性质非常相似，因此可以通过递推的方式来解决。

### 所选高星题解

#### 题解1：作者：Pkixzx (赞：3)  
**星级：4星**  
**关键亮点：**  
- 通过观察样例结果，发现结果呈现递增状态，联想到斐波那契数列。
- 使用递推的方式计算最大比赛场次，代码简洁明了。

**核心代码：**
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
**核心思想：** 通过递推计算斐波那契数列，直到数列中的值超过给定的选手数量，输出递推的次数即为最大比赛场次。

#### 题解2：作者：Mickey_snow (赞：2)  
**星级：4星**  
**关键亮点：**  
- 通过定义 $f(x)$ 函数，表示安排 $x$ 场比赛所需的最少参赛者，进一步推导出 $f(n) = f(n-1) + f(n-2)$。
- 使用递推的方式计算最大比赛场次，思路清晰。

**核心代码：**
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
**核心思想：** 通过递推计算斐波那契数列，直到数列中的值超过给定的选手数量，输出递推的次数即为最大比赛场次。

#### 题解3：作者：gxxjqqiang (赞：0)  
**星级：4星**  
**关键亮点：**  
- 通过观察发现，比赛场次的安排与斐波那契数列的性质相似，直接使用斐波那契数列进行递推计算。
- 代码简洁，逻辑清晰。

**核心代码：**
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
**核心思想：** 通过递推计算斐波那契数列，直到数列中的值超过给定的选手数量，输出递推的次数即为最大比赛场次。

### 最优关键思路或技巧

- **斐波那契数列的应用：** 通过观察问题，发现比赛场次的安排与斐波那契数列的性质相似，因此可以通过递推的方式计算最大比赛场次。
- **递推思想：** 通过递推的方式逐步计算斐波那契数列，直到数列中的值超过给定的选手数量，输出递推的次数即为最大比赛场次。

### 可拓展之处

- **类似问题：** 类似的问题可以涉及到其他递推或递归的算法，如爬楼梯问题、斐波那契数列问题等。
- **算法套路：** 对于类似的递推问题，可以通过观察问题的性质，找到与已知数列（如斐波那契数列）的相似之处，从而简化问题的解决过程。

### 推荐题目

1. **洛谷 P1002 过河卒**  
   考察递推和动态规划的思想，与本题的递推思路相似。

2. **洛谷 P1044 栈**  
   考察递推和卡特兰数的应用，与本题的递推思路相似。

3. **洛谷 P1028 数的计算**  
   考察递推和递归的思想，与本题的递推思路相似。

---
处理用时：52.75秒