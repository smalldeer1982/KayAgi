# 题目信息

# Seating On Bus

## 题目描述

Consider $ 2n $ rows of the seats in a bus. $ n $ rows of the seats on the left and $ n $ rows of the seats on the right. Each row can be filled by two people. So the total capacity of the bus is $ 4n $ .

Consider that $ m $ ( $ m<=4n $ ) people occupy the seats in the bus. The passengers entering the bus are numbered from $ 1 $ to $ m $ (in the order of their entering the bus). The pattern of the seat occupation is as below:

 $ 1 $ -st row left window seat, $ 1 $ -st row right window seat, $ 2 $ -nd row left window seat, $ 2 $ -nd row right window seat, ... , $ n $ -th row left window seat, $ n $ -th row right window seat.

After occupying all the window seats (for $ m&gt;2n $ ) the non-window seats are occupied:

 $ 1 $ -st row left non-window seat, $ 1 $ -st row right non-window seat, ... , $ n $ -th row left non-window seat, $ n $ -th row right non-window seat.

All the passengers go to a single final destination. In the final destination, the passengers get off in the given order.

 $ 1 $ -st row left non-window seat, $ 1 $ -st row left window seat, $ 1 $ -st row right non-window seat, $ 1 $ -st row right window seat, ... , $ n $ -th row left non-window seat, $ n $ -th row left window seat, $ n $ -th row right non-window seat, $ n $ -th row right window seat.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF660B/1bcb7084db323b1a8f04b6bcb377a8cb09279f9d.png)The seating for $ n=9 $ and $ m=36 $ .You are given the values $ n $ and $ m $ . Output $ m $ numbers from $ 1 $ to $ m $ , the order in which the passengers will get off the bus.

## 样例 #1

### 输入

```
2 7
```

### 输出

```
5 1 6 2 7 3 4
```

## 样例 #2

### 输入

```
9 36
```

### 输出

```
19 1 20 2 21 3 22 4 23 5 24 6 25 7 26 8 27 9 28 10 29 11 30 12 31 13 32 14 33 15 34 16 35 17 36 18
```

# AI分析结果

### 题目翻译
## 公交车座位安排

### 题目描述
假设有一辆公交车，它有 $2n$ 排座位，其中左边有 $n$ 排，右边也有 $n$ 排，每排可坐两人，所以公交车的总载客量为 $4n$ 人。

现有 $m$（$m \leq 4n$）个人乘坐这辆公交车，乘客按照从 $1$ 到 $m$ 的顺序上车，座位分配规则如下：
先从第 $1$ 排左边靠窗的座位开始，接着是第 $1$ 排右边靠窗的座位，然后是第 $2$ 排左边靠窗的座位，第 $2$ 排右边靠窗的座位，以此类推，直到第 $n$ 排左边靠窗的座位，第 $n$ 排右边靠窗的座位。当靠窗的座位都坐满（即 $m > 2n$）后，开始安排非靠窗的座位，顺序是从第 $1$ 排左边非靠窗的座位开始，接着是第 $1$ 排右边非靠窗的座位，依此类推，直到第 $n$ 排左边非靠窗的座位，第 $n$ 排右边非靠窗的座位。

所有乘客都前往同一个终点站，到达终点站后，乘客下车的顺序为：第 $1$ 排左边非靠窗的座位的乘客先下车，接着是第 $1$ 排左边靠窗的座位的乘客，然后是第 $1$ 排右边非靠窗的座位的乘客，第 $1$ 排右边靠窗的座位的乘客，以此类推，直到第 $n$ 排左边非靠窗的座位的乘客，第 $n$ 排左边靠窗的座位的乘客，第 $n$ 排右边非靠窗的座位的乘客，第 $n$ 排右边靠窗的座位的乘客。

![公交车座位图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF660B/1bcb7084db323b1a8f04b6bcb377a8cb09279f9d.png)
这是 $n = 9$ 且 $m = 36$ 时的座位安排图。

给定 $n$ 和 $m$ 的值，输出从 $1$ 到 $m$ 的 $m$ 个数字，表示乘客下车的顺序。

### 样例 #1
#### 输入
```
2 7
```
#### 输出
```
5 1 6 2 7 3 4
```

### 样例 #2
#### 输入
```
9 36
```
#### 输出
```
19 1 20 2 21 3 22 4 23 5 24 6 25 7 26 8 27 9 28 10 29 11 30 12 31 13 32 14 33 15 34 16 35 17 36 18
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕模拟公交车乘客的上车和下车过程展开。不同题解的思路和实现方式各有不同，有的通过找规律直接输出结果，有的则通过数组模拟座位的占用情况，再按下车顺序输出。

### 所选题解
- **cqbztz2（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接根据规律输出结果，时间复杂度低。
    - **个人心得**：提到英语题面差点劝退，说明读懂题面对于解题的重要性。
- **_Agave_（4星）**
    - **关键亮点**：通过函数分别模拟上车和下车过程，代码结构清晰，易于理解。
    - **个人心得**：无。
- **dbodb（4星）**
    - **关键亮点**：详细解释了题意和思路，通过数组模拟座位情况，处理边界条件时添加判断，逻辑严谨。
    - **个人心得**：认为题目评分虚高，普及 - 难度较为合适。

### 重点代码
#### cqbztz2
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=2*n;i++){
        if(2*n+i<=m){
            cout<<2*n+i<<" ";
        }
        if(i<=m){
            cout<<i<<" ";
        }
    }
    return 0;
}
```
**核心实现思想**：根据下车顺序的规律，先输出大于 $2n$ 的数，再输出小于等于 $2n$ 的数。

#### _Agave_
```cpp
#include <bits/stdc++.h>
using namespace std;
int seat[10][205],n,m,r=1; 
//模拟上车
void push(){
    //1、4列
    for(int i=1;i<=n;i++){
        if(r==m+1)return ;
        seat[1][i]=r;
        r++;
        if(r==m+1)return ;
        seat[4][i]=r;
        r++;
    }
    //2、3列
    for(int i=1;i<=n;i++){
        if(r==m+1)return ;
        seat[2][i]=r;
        r++;
        if(r==m+1)return ;
        seat[3][i]=r;
        r++;
    }
}
//模拟下车
void out(){
    for(int i=1;i<=n;i++){
        //模拟每一行
        if(seat[2][i]!=0)printf("%d ",seat[2][i]);
        if(seat[1][i]!=0)printf("%d ",seat[1][i]);
        if(seat[3][i]!=0)printf("%d ",seat[3][i]);
        if(seat[4][i]!=0)printf("%d ",seat[4][i]);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    push();
    out();
    return 0;
}
```
**核心实现思想**：通过 `push` 函数模拟乘客上车过程，将乘客编号存入数组 `seat` 中；通过 `out` 函数模拟乘客下车过程，按顺序输出数组中的乘客编号。

#### dbodb
```c++
#include<bits/stdc++.h>
using namespace std;
int a[105][5];
int main()
{
    int n,m;
    cin>>n>>m;
    int shun=0;
    for(int i=1;m>=0&&i<=n;i++)
    {
        if(m-1>=0)
            a[i][1]=++shun,m--;
        if(m-1>=0)
            a[i][4]=++shun,m--;
    }
    for(int i=1;m>=0&&i<=n;i++)
    {
        if(m-1>=0)
            a[i][2]=++shun,m--;
        if(m-1>=0)
            a[i][3]=++shun,m--;
    }
    for(int i=1;i<=n;i++)
    {   
        if(a[i][2])
            cout<<a[i][2]<<" ";
        if(a[i][1])
            cout<<a[i][1]<<" ";
        if(a[i][3])
            cout<<a[i][3]<<" ";
        if(a[i][4])
            cout<<a[i][4]<<" ";
    }
    return 0;
}
```
**核心实现思想**：使用数组 `a` 模拟座位情况，先按上车规则填充数组，再按下车规则输出数组中不为 $0$ 的元素。

### 最优关键思路或技巧
- 对于此类有规律的模拟题，可以先通过具体例子找规律，直接根据规律输出结果，避免复杂的模拟过程。
- 使用数组模拟座位情况时，要注意处理边界条件，确保程序的正确性。

### 可拓展之处
同类型题可能会改变座位的排列方式、上车和下车的规则等，但解题思路仍然是模拟整个过程。类似算法套路包括模拟游戏过程、模拟事件发生顺序等。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)

---
处理用时：45.88秒