# 题目信息

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2 1
16 12
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
## 怪物

### 题目描述
在另一个星球上，一个怪物正在追逐瑞克和莫蒂。他们非常害怕，以至于有时会尖叫。更准确地说，瑞克在时间 $b, b + a, b + 2a, b + 3a, \cdots$ 尖叫，而莫蒂在时间 $d, d + c, d + 2c, d + 3c, \cdots$ 尖叫。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)
如果瑞克和莫蒂在某一时刻同时尖叫，怪物就会抓住他们。所以怪物想知道它什么时候会抓住他们（即他们第一次同时尖叫的时间），或者他们永远不会同时尖叫。

### 说明/提示
在第一个样例测试用例中，瑞克的第 5 次尖叫和莫蒂的第 8 次尖叫发生在时间 82。
在第二个样例测试用例中，瑞克所有的尖叫时间都是奇数，而莫蒂所有的尖叫时间都是偶数，所以他们永远不会同时尖叫。

### 样例 #1
#### 输入
```
20 2
9 19
```
#### 输出
```
82
```

### 样例 #2
#### 输入
```
2 1
16 12
```
#### 输出
```
-1
```

### 题解综合分析与结论
这些题解主要围绕寻找瑞克和莫蒂第一次同时尖叫的时间展开，思路可分为暴力枚举和数论方法两类。
- **暴力枚举**：通过双重循环枚举瑞克和莫蒂尖叫的时间，判断是否相等。该方法思路简单直接，但需要合理控制循环次数，否则可能超时。
- **数论方法**：利用贝祖定理判断方程 $b + ax = d + cy$ 是否有解，若有解再进行模拟；或者将问题转化为一元线性同余方程，用扩展欧几里得算法求解。数论方法效率较高，但需要一定的数学知识。

### 高评分题解
- **Alex_Wei（5星）**
    - **关键亮点**：思路清晰，先利用贝祖定理判断方程是否有解，避免不必要的模拟，代码简洁高效。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int gcd(int i,int j){return!j?i:gcd(j,i%j);}
int main()
{
    cin>>a>>b>>c>>d;
    if((d-b)%gcd(a,c))cout<<-1,exit(0);
    while(b!=d)b<d?b+=a:d+=c;
    cout<<b;
    return 0;
}
```
核心实现思想：先计算 $a$ 和 $c$ 的最大公约数 $k$，判断 $k$ 是否能整除 $d - b$，若不能则无解；若有解，通过不断更新 $b$ 和 $d$ 的值，直到它们相等，此时的值即为第一次同时尖叫的时间。

- **肖恩Sean（4星）**
    - **关键亮点**：运用扩展欧几里得算法求解一元线性同余方程，算法复杂度低，适用于数据范围较大的情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define ReFor(i,l,r) for(int i=(l);i>=(r);--i)
using namespace std;
int a1,a2,r1,r2,tmp;
int read(){/* 读入函数 */}
int exgcd(int a,int b,int &x,int &y){/* 扩展欧几里得算法 */}
int main(){
    a1=read();r1=read();a2=read();r2=read();tmp=max(r1,r2);
    int c=r2-r1,x0,y0,d=exgcd(a1,a2,x0,y0);
    if(c%d){printf("-1\n");return 0;}
    int t=a2/d;
    x0=(x0*(c/d)%t+t)%t;
    r1=a1*x0+r1;
    a1=a1*(a2/d);
    while(r1<tmp) r1+=a1;
    printf("%d\n",r1);
    return 0;
}
```
核心实现思想：将问题转化为一元线性同余方程 $x \equiv b \pmod{a}$ 和 $x \equiv d \pmod{c}$，用扩展欧几里得算法合并为 $x \equiv f \pmod{e}$，然后求出大于 $\max(a, c)$ 的最小解。

### 最优关键思路或技巧
- 利用贝祖定理判断方程是否有解，避免不必要的模拟，提高效率。
- 对于同余方程问题，可使用扩展欧几里得算法求解。

### 拓展思路
同类型题或类似算法套路：
- 求解不定方程的整数解问题，可先利用数论知识判断是否有解，再进行求解。
- 处理多个同余方程的合并问题，可使用扩展欧几里得算法。

### 推荐题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察扩展欧几里得算法求解同余方程。
- [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)：涉及不定方程和同余方程的求解。
- [P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：可使用扩展欧几里得算法求乘法逆元。

### 个人心得摘录与总结
- **xujian**：强调双重循环模拟适合初学者，但要注意控制循环次数，避免超时或精度不够。
- **happybob**：因想不出公式而采用循环方法，解释了两层循环的原因，并根据限时和数据范围确定循环次数。

---
处理用时：33.84秒