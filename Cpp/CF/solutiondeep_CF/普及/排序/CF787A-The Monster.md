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

### 题目中文重写
## 怪物

### 题目描述
在另一个星球上，一个怪物正在追逐瑞克和莫蒂。他们非常害怕，以至于有时会尖叫。更准确地说，瑞克在时刻 $b, b + a, b + 2a, b + 3a, \cdots$ 尖叫，而莫蒂在时刻 $d, d + c, d + 2c, d + 3c, \cdots$ 尖叫。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)

如果在任何时刻他们同时尖叫，怪物就会抓住他们，所以怪物想知道它什么时候会抓住他们（他们第一次同时尖叫的时刻），或者他们永远不会同时尖叫。

### 说明/提示
在第一个样例测试用例中，瑞克的第 5 次尖叫和莫蒂的第 8 次尖叫都在时刻 82。

在第二个样例测试用例中，瑞克的所有尖叫时刻都是奇数，而莫蒂的所有尖叫时刻都是偶数，所以他们永远不会同时尖叫。

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
这些题解主要围绕寻找瑞克和莫蒂第一次同时尖叫的时刻展开，若不存在则输出 -1。思路可分为暴力枚举和数论求解两类。
- **暴力枚举**：通过双重循环枚举瑞克和莫蒂尖叫的时刻，判断是否相等。该方法简单直接，但时间复杂度较高，受循环次数限制，可能存在超时或精度问题。
- **数论求解**：将问题转化为线性方程 $b + ax = d + cy$，利用贝祖定理判断方程是否有解，有解时再通过模拟或扩展欧几里得算法求解。这种方法理论性较强，但效率较高。

### 题解评分与选择
|作者|思路清晰度|代码可读性|优化程度|评分|
| ---- | ---- | ---- | ---- | ---- |
|Alex_Wei|清晰，先证明方程有解条件，再模拟求解|高，代码简洁|高，先判断解的存在性|5星|
|xujian|清晰，直接说明双重循环模拟思路|高，代码简洁易懂|低，循环次数固定|3星|
|_Empty|清晰，使用双重循环嵌套|一般，代码包含不必要的头文件|低，循环次数过大|2星|
|Cutest_Junior|清晰，给出枚举范围并说明原因|高，代码简洁|中，合理确定枚举范围|4星|
|耶耶小朋友|清晰，明确说明模拟思路|高，代码结构清晰|低，循环次数固定|3星|
|肖恩Sean|较复杂，涉及扩展欧几里得算法|一般，代码包含较多模板|高，使用数论方法求解|4星|
|OdtreePrince|清晰，采用模拟并排序|一般，数组存储结果再排序较冗余|低，循环次数大且排序耗时|2星|
|李至擎|清晰，说明暴力枚举思路|高，代码简洁|低，循环次数固定|3星|
|sodak|清晰，先判断解的存在性再模拟|一般，代码包含较多自定义宏|高，结合数论和模拟|4星|
|happybob|清晰，解释两层循环原因|高，代码注释详细|中，合理确定循环次数|3星|
|Contemptuous|清晰，说明暴力判断思路|高，代码简洁|低，循环次数固定|3星|
|Thomas_Cat|清晰，强调暴力循环|高，代码形象|低，循环次数固定|3星|

选择评分较高（≥4星）的题解如下：
- **Alex_Wei（5星）**
    - **关键亮点**：先利用贝祖定理判断方程 $b + ax = d + cy$ 是否有解，避免不必要的模拟，提高效率。
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
- **Cutest_Junior（4星）**
    - **关键亮点**：合理确定枚举范围，避免无限枚举，时间复杂度可控。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = max(b, d); i <= 10000; ++i) {
        if (i % a == b % a && i % c == d % c) {
            printf("%d", i);
            return 0;
        }
    }
    printf("-1");
}
```
- **肖恩Sean（4星）**
    - **关键亮点**：使用扩展欧几里得算法将同余方程合并求解，理论性强，适用于更复杂的情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define ReFor(i,l,r) for(int i=(l);i>=(r);--i)
using namespace std;
int a1,a2,r1,r2,tmp;
int read(){/* 省略 */}
int exgcd(int a,int b,int &x,int &y){/* 省略 */}
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

### 最优关键思路或技巧
- **数论判断解的存在性**：利用贝祖定理判断线性方程 $ax - cy = d - b$ 是否有解，避免无效的模拟，提高效率。
- **合理确定枚举范围**：根据题目条件和数据范围，确定合理的枚举范围，减少不必要的计算。

### 可拓展之处
本题可拓展到更复杂的同余方程组求解问题，例如多个不同周期的尖叫时刻判断是否有同时尖叫的情况，可使用中国剩余定理等数论方法求解。

### 洛谷相似题目推荐
1. [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察扩展欧几里得算法求解同余方程。
2. [P3868 [TJOI2009]猜数字](https://www.luogu.com.cn/problem/P3868)：涉及中国剩余定理求解同余方程组。
3. [P2421 荒岛野人](https://www.luogu.com.cn/problem/P2421)：需要判断多个同余方程是否有解，与本题思路类似。

### 个人心得摘录与总结
- **happybob**：因想不出公式，采用两层循环暴力求解。解释了两层循环的原因，并根据时间限制和数据范围确定循环次数，体现了在没有理论方法时，根据题目条件合理设计算法的思路。
- **sodak**：意识到可以用扩展欧几里得算法求最小非负解，但因懒而采用暴力模拟，说明在实际解题中，可根据自身情况选择合适的方法。 

---
处理用时：63.02秒