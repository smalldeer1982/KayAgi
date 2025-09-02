# 题目信息

# Drazil and Date

## 题目描述

Someday, Drazil wanted to go on date with Varda. Drazil and Varda live on Cartesian plane. Drazil's home is located in point $ (0,0) $ and Varda's home is located in point $ (a,b) $ . In each step, he can move in a unit distance in horizontal or vertical direction. In other words, from position $ (x,y) $ he can go to positions $ (x+1,y) $ , $ (x-1,y) $ , $ (x,y+1) $ or $ (x,y-1) $ .

Unfortunately, Drazil doesn't have sense of direction. So he randomly chooses the direction he will go to in each step. He may accidentally return back to his house during his travel. Drazil may even not notice that he has arrived to $ (a,b) $ and continue travelling.

Luckily, Drazil arrived to the position $ (a,b) $ successfully. Drazil said to Varda: "It took me exactly $ s $ steps to travel from my house to yours". But Varda is confused about his words, she is not sure that it is possible to get from $ (0,0) $ to $ (a,b) $ in exactly $ s $ steps. Can you find out if it is possible for Varda?

## 说明/提示

In fourth sample case one possible route is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515A/c7eeb592e99c054b70275e1c11760c4bf457a818.png).

## 样例 #1

### 输入

```
5 5 11
```

### 输出

```
No
```

## 样例 #2

### 输入

```
10 15 25
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
0 5 1
```

### 输出

```
No
```

## 样例 #4

### 输入

```
0 0 2
```

### 输出

```
Yes
```

# AI分析结果

### 题目翻译
#### Drazil 和约会

#### 题目描述
有一天，Drazil 想和 Varda 约会。Drazil 和 Varda 生活在笛卡尔平面上。Drazil 的家位于点 $(0,0)$，Varda 的家位于点 $(a,b)$。在每一步中，他可以在水平或垂直方向上移动一个单位距离。换句话说，从位置 $(x,y)$ 他可以移动到位置 $(x + 1,y)$、$(x - 1,y)$、$(x,y + 1)$ 或 $(x,y - 1)$。

不幸的是，Drazil 没有方向感。所以他在每一步中都会随机选择要走的方向。在旅行过程中，他可能会不小心回到自己的家。Drazil 甚至可能没有注意到他已经到达了 $(a,b)$ 并继续旅行。

幸运的是，Drazil 成功到达了位置 $(a,b)$。Drazil 对 Varda 说：“我从家到你家正好走了 $s$ 步”。但 Varda 对他的话感到困惑，她不确定是否有可能正好用 $s$ 步从 $(0,0)$ 走到 $(a,b)$。你能帮 Varda 找出答案吗？

#### 说明/提示
在第四个样例中，一种可能的路线是：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515A/c7eeb592e99c054b70275e1c11760c4bf457a818.png)。

#### 样例 #1
##### 输入
```
5 5 11
```
##### 输出
```
No
```

#### 样例 #2
##### 输入
```
10 15 25
```
##### 输出
```
Yes
```

#### 样例 #3
##### 输入
```
0 5 1
```
##### 输出
```
No
```

#### 样例 #4
##### 输入
```
0 0 2
```
##### 输出
```
Yes
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路基本一致，都是先计算从 $(0,0)$ 到 $(a,b)$ 的最短步数（即曼哈顿距离 $\vert a\vert+\vert b\vert$），然后根据最短步数与给定步数 $s$ 的关系进行判断：
1. 若最短步数大于 $s$，则无法走到，输出 `No`。
2. 若最短步数等于 $s$，则可以走到，输出 `Yes`。
3. 若最短步数小于 $s$，则需要判断 $s$ 与最短步数的差值是否为偶数，若为偶数则可以走到（通过来回走消耗多余步数），输出 `Yes`；否则输出 `No`。

### 所选题解
- **作者：_Haoomff_ (4星)**
    - **关键亮点**：思路清晰，代码简洁，对各种情况的判断逻辑解释详细。
    - **代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,s;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>a>>b>>s;
    c=abs(a)+abs(b);
    if(c==s)cout<<"Yes";
    else if(c<s&&(s-c)%2==0)cout<<"Yes";
    else cout<<"No";
    return 0;
}
```
核心实现思想：先计算曼哈顿距离 `c`，然后根据 `c` 与 `s` 的关系进行判断输出。

- **作者：BrokenStar (4星)**
    - **关键亮点**：思路清晰，对步数的分析和判断逻辑阐述明确，代码简洁。
    - **代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,s;
signed main(){
    cin>>a>>b>>s;
    int d=abs(a)+abs(b);
    if((d-s)%2==0&&d<=s){
        puts("Yes");
    }
    else puts("No");
    return 0;
}
```
核心实现思想：计算曼哈顿距离 `d`，判断 `d` 与 `s` 的关系以及 `d - s` 是否为偶数来输出结果。

- **作者：ZolaWatle (4星)**
    - **关键亮点**：引入曼哈顿距离的概念，对判断过程的分析详细，代码逻辑清晰。
    - **代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define re rgister int
using namespace std;

int a,b,s,dis;

int main()
{
    std::scanf("%d%d%d",&a,&b,&s);
    
    dis=std::abs(a)+std::abs(b);
    
    if(dis==s)
    {
        std::printf("Yes");
        return 0;
    }
    if(dis>s)
    {
        std::printf("No");
        return 0;
    }
    
    dis=s-dis;
    
    if(dis%2==0)
    {
        std::printf("Yes");
        return 0;
    }
    std::printf("No");
    return 0;
}
```
核心实现思想：计算曼哈顿距离 `dis`，根据不同情况判断并输出结果。

### 最优关键思路或技巧
- 利用曼哈顿距离计算从 $(0,0)$ 到 $(a,b)$ 的最短步数。
- 考虑多余步数的奇偶性，因为来回走消耗的步数一定是偶数。

### 可拓展之处
同类型题可能会有不同的移动规则或限制条件，例如限制移动方向、增加障碍物等，但核心思路可能还是先计算最短路径，再根据剩余步数的性质进行判断。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和组合数学知识。
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)：需要运用数学思维和递推方法。
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：可以通过动态规划或递推解决，与本题的路径和步数分析有一定相似性。

### 个人心得摘录与总结
- **ZolaWatle**：第一次写的时候没加绝对值写挂了。总结：在处理坐标问题时，要注意坐标可能为负数，需要取绝对值。 

---
处理用时：37.69秒