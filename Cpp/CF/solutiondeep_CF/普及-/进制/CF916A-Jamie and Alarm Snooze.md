# 题目信息

# Jamie and Alarm Snooze

## 题目描述

Jamie loves sleeping. One day, he decides that he needs to wake up at exactly $ hh:mm $ . However, he hates waking up, so he wants to make waking up less painful by setting the alarm at a lucky time. He will then press the snooze button every $ x $ minutes until $ hh:mm $ is reached, and only then he will wake up. He wants to know what is the smallest number of times he needs to press the snooze button.

A time is considered lucky if it contains a digit ' $ 7 $ '. For example, $ 13:07 $ and $ 17:27 $ are lucky, while $ 00:48 $ and $ 21:34 $ are not lucky.

Note that it is not necessary that the time set for the alarm and the wake-up time are on the same day. It is guaranteed that there is a lucky time Jamie can set so that he can wake at $ hh:mm $ .

Formally, find the smallest possible non-negative integer $ y $ such that the time representation of the time $ x·y $ minutes before $ hh:mm $ contains the digit ' $ 7 $ '.

Jamie uses 24-hours clock, so after $ 23:59 $ comes $ 00:00 $ .

## 说明/提示

In the first sample, Jamie needs to wake up at 11:23. So, he can set his alarm at 11:17. He would press the snooze button when the alarm rings at 11:17 and at 11:20.

In the second sample, Jamie can set his alarm at exactly at 01:07 which is lucky.

## 样例 #1

### 输入

```
3
11 23
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
01 07
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# Jamie和闹钟贪睡功能

## 题目描述
Jamie喜欢睡觉。有一天，他决定必须在精确的 $hh:mm$ 时刻醒来。然而，他讨厌醒来，所以他想通过将闹钟设置在一个幸运时间来让醒来不那么痛苦。然后他会每隔 $x$ 分钟按一次贪睡按钮，直到 $hh:mm$ 时刻，只有到那时他才会醒来。他想知道他最少需要按多少次贪睡按钮。

如果一个时间包含数字 ' $7$ '，则该时间被认为是幸运时间。例如，$13:07$ 和 $17:27$ 是幸运时间，而 $00:48$ 和 $21:34$ 不是幸运时间。

请注意，闹钟设置的时间和醒来的时间不一定在同一天。保证存在一个幸运时间，Jamie可以设置该时间以便能在 $hh:mm$ 醒来。

形式上，找到最小的非负整数 $y$，使得 $hh:mm$ 之前 $x·y$ 分钟的时间表示中包含数字 ' $7$ '。

Jamie使用24小时制时钟，所以 $23:59$ 之后是 $00:00$。

## 说明/提示
在第一个样例中，Jamie需要在11:23醒来。所以，他可以将闹钟设置在11:17。当闹钟在11:17和11:20响起时，他会按贪睡按钮。

在第二个样例中，Jamie可以将闹钟正好设置在01:07，这是一个幸运时间。

## 样例 #1
### 输入
```
3
11 23
```
### 输出
```
2
```

## 样例 #2
### 输入
```
5
01 07
```
### 输出
```
0
```

### 综合分析与结论
- **思路对比**：大部分题解思路一致，都是从目标时间 $hh:mm$ 开始往前倒推，每次倒退 $x$ 分钟，直到找到幸运时间（包含数字 7）。只有一个思路提到枚举所有可能时间，但因考虑天数复杂未采用。
- **算法要点**：核心是不断减少分钟数，处理跨小时和跨天的情况，判断当前时间是否为幸运时间。判断时利用 $0\leqslant hh<24$ 和 $0\leqslant mm<60$，只判断小时和分钟的个位是否为 7。
- **解决难点**：主要难点在于处理跨小时（分钟为负时小时减 1，分钟加 60）和跨天（小时为负时小时加 24）的情况。不同题解在处理这些情况时代码略有不同，但本质相同。

### 评分情况
- **HanPi**：5星。思路清晰，代码简洁，注释详细，对关键步骤有说明。
- **REAL_曼巴**：4星。思路明确，代码可读性好，有小建议提示。
- **_Spectator_**：4星。思路和代码实现规范，有具体步骤说明。

### 所选题解
- **HanPi（5星）**
    - **关键亮点**：思路清晰，代码简洁，对判断幸运时间的优化有说明。
    - **核心代码**：
```c
#include <stdio.h>

int x, hh, mm, ans;
int main()
{
    scanf("%d%d%d", &x, &hh, &mm);
    while (1)
    {
        if (hh % 10 == 7 || mm % 10 == 7)break;
        ans++;
        mm -= x;
        if (mm < 0)
        {
            hh--;
            mm += 60;
        }
        if (hh < 0)hh += 24;
    }
    printf("%d", ans);
    return 0;
}
```
核心思想：从目标时间开始循环，若不是幸运时间则倒退 $x$ 分钟，处理跨小时和跨天情况，直到找到幸运时间。

- **REAL_曼巴（4星）**
    - **关键亮点**：思路明确，代码可读性好，有小建议提示。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main(){
    int x,a,b,ans=0;
    cin>>x>>a>>b;
    while(1){
        if(a%10==7||b%10==7){
            cout<<ans;
            return 0;
        }
        ans+=1,b-=x;
        if(b<0)a--,b+=60;
        if(a<0)a+=24;
    }
    return 0;
}
```
核心思想：同样从目标时间开始循环，判断是否为幸运时间，倒退时间并处理边界情况。

- **_Spectator_（4星）**
    - **关键亮点**：思路和代码实现规范，有具体步骤说明。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,h,m,ans;
int main()
{　
    cin>>x>>h>>m;　
    while(h%10!=7&&m%10!=7)
    {　
        m-=x,ans++;
        if(m<0)h--,m+=60;
        if(h<0)h=23;
    }　
    cout<<ans;　
    return 0;　
}　
```
核心思想：循环倒退时间，判断幸运时间，处理跨小时和跨天情况。

### 最优关键思路或技巧
- **逆向思维**：从目标时间往前倒推，避免了正向枚举所有可能时间时考虑天数的复杂性。
- **简化判断**：利用时间范围，只判断小时和分钟的个位是否为 7，减少判断复杂度。

### 可拓展之处
同类型题可能会改变幸运时间的定义，或者改变时间的倒退规则，如倒退的时间不是固定的 $x$ 分钟，而是根据某种规律变化。类似算法套路是模拟时间的变化，处理边界情况。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)：模拟比赛过程，处理不同比赛规则下的得分情况。
- [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563)：模拟人物的位置和方向变化，根据指令进行操作。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：模拟购买铅笔的过程，计算不同包装下的花费。

### 个人心得
无明显个人心得摘录。 

---
处理用时：41.63秒