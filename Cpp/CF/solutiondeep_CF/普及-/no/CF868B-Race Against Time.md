# 题目信息

# Race Against Time

## 题目描述

Have you ever tried to explain to the coordinator, why it is eight hours to the contest and not a single problem has been prepared yet? Misha had. And this time he has a really strong excuse: he faced a space-time paradox! Space and time replaced each other.

The entire universe turned into an enormous clock face with three hands — hour, minute, and second. Time froze, and clocks now show the time $ h $ hours, $ m $ minutes, $ s $ seconds.

Last time Misha talked with the coordinator at $ t_{1} $ o'clock, so now he stands on the number $ t_{1} $ on the clock face. The contest should be ready by $ t_{2} $ o'clock. In the terms of paradox it means that Misha has to go to number $ t_{2} $ somehow. Note that he doesn't have to move forward only: in these circumstances time has no direction.

Clock hands are very long, and Misha cannot get round them. He also cannot step over as it leads to the collapse of space-time. That is, if hour clock points 12 and Misha stands at 11 then he cannot move to 1 along the top arc. He has to follow all the way round the clock center (of course, if there are no other hands on his way).

Given the hands' positions, $ t_{1} $ , and $ t_{2} $ , find if Misha can prepare the contest on time (or should we say on space?). That is, find if he can move from $ t_{1} $ to $ t_{2} $ by the clock face.

## 说明/提示

The three examples are shown on the pictures below from left to right. The starting position of Misha is shown with green, the ending position is shown with pink. Note that the positions of the hands on the pictures are not exact, but are close to the exact and the answer is the same.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF868B/a67db32a4530841b7d57b21ea225d21a83f385f3.png)

## 样例 #1

### 输入

```
12 30 45 3 11
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
12 0 1 12 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3 47 0 4 9
```

### 输出

```
YES
```

# AI分析结果

### 题目中文重写
# 与时间赛跑

## 题目描述
你有没有试过向比赛协调员解释，为什么距离比赛开始还有八个小时，却一道题目都还没准备好？米沙就试过。而这次他有一个非常有力的借口：他遭遇了时空悖论！空间和时间互换了。

整个宇宙变成了一个巨大的钟面，上面有三根指针——时针、分针和秒针。时间静止了，现在时钟显示的时间是 $h$ 小时、$m$ 分钟、$s$ 秒。

米沙上一次和协调员交谈是在 $t_{1}$ 点，所以现在他站在钟面上的数字 $t_{1}$ 处。比赛应该在 $t_{2}$ 点准备好。在这个悖论的情境下，这意味着米沙必须想办法到达数字 $t_{2}$ 处。需要注意的是，他不一定要只向前移动：在这种情况下，时间是没有方向的。

时钟的指针非常长，米沙无法绕过它们。他也不能跨过去，因为这会导致时空崩塌。也就是说，如果时针指向 12，而米沙站在 11 处，那么他就不能沿着顶部弧线移动到 1 处。他必须绕着时钟中心走完整的一圈（当然，如果途中没有其他指针阻挡的话）。

给定指针的位置、$t_{1}$ 和 $t_{2}$，判断米沙是否能按时（或者应该说按空间）准备好比赛。也就是说，判断他是否能沿着钟面从 $t_{1}$ 移动到 $t_{2}$。

## 说明/提示
三个样例分别如下面的图片所示，从左到右。米沙的起始位置用绿色表示，结束位置用粉色表示。请注意，图片中指针的位置并不精确，但接近精确位置，且答案是相同的。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF868B/a67db32a4530841b7d57b21ea225d21a83f385f3.png)

## 样例 #1

### 输入
```
12 30 45 3 11
```

### 输出
```
NO
```

## 样例 #2

### 输入
```
12 0 1 12 1
```

### 输出
```
YES
```

## 样例 #3

### 输入
```
3 47 0 4 9
```

### 输出
```
YES
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路大多是先将时针、分针、秒针以及起点和终点的位置进行统一单位的处理，然后对这些位置进行排序，最后根据排序后的位置关系来判断是否能从起点到达终点。

不同题解的算法要点和解决难点的方式各有不同：
- 部分题解自己实现排序函数，避免 `sort` 对浮点数排序可能出现的问题。
- 有些题解通过判断两个位置是否相邻来确定能否到达。
- 还有题解考虑了指针跨越 0 点位置的情况，分情况进行判断。
- 部分题解为了处理指针和端点重合的情况，给指针位置加一个小偏移量。
- 有的题解通过自定义分数结构体来解决精度问题。

### 所选题解
- 作者：王熙文 (赞：2)，4星
  - 关键亮点：思路清晰，详细解释了题意和判断的两种情况，考虑了指针共线的特判情况，代码简洁易懂。
  - 个人心得：提到这道题堆在尝试过的题目里很久，今天终于 AC，强调了题目的细节非常多，并给出了两个 WA 过的测试数据来帮助理解题意。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;

bool check(int a,int b,int c,int d) // 检查 c 点到 d 点是否能在 a~b 这段走
{
    if(a>b) // 跨越 0
    {
        if((c<=b || c>a) && (d<=b || d>a)) // 是否在两段内
        {
            return 1;
        }
        else return 0;
    }
    else // 不跨越
    {
        if(c>a && d<=b) return 1; // 是否在一段内
        else return 0;
    }
}

int main()
{
    int a,b,c,d,e;
    cin>>a>>b>>c>>d>>e;
    a*=5,d*=5,e*=5; // 注意 a,d,e 要 *5
    if(a>b) swap(a,b); // 排序
    if(b>c) swap(b,c);
    if(a>b) swap(a,b);
    if(d>e) swap(d,e);
    if(a==b && b==c) cout<<"YES"; // 特判三点共线的情况
    else if(check(a,b,d,e) || check(b,c,d,e) || check(c,a,d,e))
    { // 对于每两针都检查
        cout<<"YES";
    }
    else cout<<"NO";
    return 0;
}
```
**核心实现思想**：首先将输入的时针、起点和终点位置乘以 5 进行单位统一，然后对三根指针的位置和起点终点位置分别进行排序。定义 `check` 函数来判断两个点是否能在两根指针之间移动，分指针跨越 0 点和不跨越 0 点两种情况进行判断。最后对每两根指针之间的情况进行检查，如果存在一种情况可以到达则输出 `YES`，否则输出 `NO`，同时特判了三根指针共线的情况。

### 关键思路或技巧
- 统一单位：将时针、分针、秒针以及起点和终点的位置统一到相同的度量单位，方便后续的比较和判断。
- 排序：对所有位置进行排序，以便更清晰地判断它们之间的相对位置关系。
- 分情况讨论：考虑指针跨越 0 点和不跨越 0 点的情况，以及指针共线的特殊情况，使判断更加准确。

### 可拓展之处
同类型题可能会增加指针的数量或者改变移动规则，类似算法套路仍然是先统一单位、排序，然后根据位置关系进行判断。

### 推荐题目
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得总结
王熙文提到这道题细节很多，通过给出两个 WA 过的测试数据，强调了在处理指针和端点重合情况时需要考虑指针的运动方向，避免因忽略这些细节而导致错误。 

---
处理用时：44.28秒