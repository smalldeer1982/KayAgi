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

### 题目中文重写
# Jamie与闹钟贪睡功能

## 题目描述
Jamie热爱睡觉。有一天，他决定必须在精确的 $hh:mm$ 时刻醒来。然而，他讨厌醒来，所以他想通过将闹钟设置在一个幸运时间来减轻醒来的痛苦。然后，他会每隔 $x$ 分钟按一次贪睡按钮，直到到达 $hh:mm$ 时刻，只有到那时他才会醒来。他想知道他最少需要按多少次贪睡按钮。

如果一个时间包含数字 '7'，则该时间被视为幸运时间。例如，$13:07$ 和 $17:27$ 是幸运时间，而 $00:48$ 和 $21:34$ 不是幸运时间。

请注意，闹钟设置的时间和醒来的时间不一定在同一天。保证存在一个幸运时间，Jamie可以设置该时间以便在 $hh:mm$ 醒来。

形式上，找到最小的非负整数 $y$，使得 $hh:mm$ 之前 $x·y$ 分钟的时间表示中包含数字 '7'。

Jamie使用24小时制时钟，所以在 $23:59$ 之后是 $00:00$。

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
- **思路对比**：所有题解思路基本一致，均是从目标时间 $hh:mm$ 开始往前倒推，每次倒退 $x$ 分钟，直到遇到幸运时间（包含数字 7），记录倒退次数。
- **算法要点**：核心要点为判断当前时间是否为幸运时间，因小时和分钟的十位不可能为 7，所以仅需判断个位；处理时间倒退时的跨小时和跨天情况。
- **解决难点**：主要难点在于处理时间倒退时的进位问题，如分钟小于 0 时需向小时借位，小时小于 0 时需跨天处理。

### 题解评分
- **HanPi**：5星。思路清晰，代码简洁，注释详细，对关键步骤有明确说明。
- **REAL_曼巴**：4星。思路清晰，代码可读性好，有小建议提示。
- **_Spectator_**：4星。思路和实现方式明确，代码结构清晰。

### 所选题解
- **HanPi（5星）**
    - **关键亮点**：思路清晰，对两种思路进行对比，代码注释详细，关键步骤处理准确。
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
核心思想：从目标时间开始循环，每次倒退 $x$ 分钟，判断是否为幸运时间，若不是则继续倒退并处理进位，直到找到幸运时间。
- **REAL_曼巴（4星）**
    - **关键亮点**：思路清晰，代码简洁，有小建议提示。
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
核心思想：通过死循环不断倒退时间，判断是否为幸运时间，同时处理进位，找到幸运时间后输出答案。
- **_Spectator_（4星）**
    - **关键亮点**：思路和实现方式明确，代码结构清晰。
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
核心思想：使用循环倒退时间，判断是否为幸运时间，处理进位，找到幸运时间后输出倒退次数。

### 最优关键思路或技巧
- **思维方式**：采用逆向思维，从目标时间往前倒推，避免了正向枚举时复杂的时间计算和天数判断。
- **代码实现技巧**：仅判断时间的个位是否为 7，简化了幸运时间的判断逻辑；在处理进位时，通过简单的加减法和条件判断完成跨小时和跨天处理。

### 可拓展之处
同类型题可能会改变幸运时间的定义，如包含特定数字组合或满足某种数学规律；或者改变时间的表示方式，如12小时制。类似算法套路为模拟时间变化，处理进位和边界情况。

### 推荐洛谷题目
- P1042 乒乓球：模拟比赛过程，处理比赛分数和局数的变化。
- P1067 多项式输出：模拟多项式的输出过程，处理系数和指数的不同情况。
- P1098 字符串的展开：模拟字符串的展开过程，处理不同的展开规则。

### 个人心得摘录与总结
无。

---
处理用时：30.92秒