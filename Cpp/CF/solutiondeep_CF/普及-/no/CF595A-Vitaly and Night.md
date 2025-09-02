# 题目信息

# Vitaly and Night

## 题目描述

One day Vitaly was going home late at night and wondering: how many people aren't sleeping at that moment? To estimate, Vitaly decided to look which windows are lit in the house he was passing by at that moment.

Vitaly sees a building of $ n $ floors and $ 2·m $ windows on each floor. On each floor there are $ m $ flats numbered from $ 1 $ to $ m $ , and two consecutive windows correspond to each flat. If we number the windows from $ 1 $ to $ 2·m $ from left to right, then the $ j $ -th flat of the $ i $ -th floor has windows $ 2·j-1 $ and $ 2·j $ in the corresponding row of windows (as usual, floors are enumerated from the bottom). Vitaly thinks that people in the flat aren't sleeping at that moment if at least one of the windows corresponding to this flat has lights on.

Given the information about the windows of the given house, your task is to calculate the number of flats where, according to Vitaly, people aren't sleeping.

## 说明/提示

In the first test case the house has two floors, two flats on each floor. That is, in total there are 4 flats. The light isn't on only on the second floor in the left flat. That is, in both rooms of the flat the light is off.

In the second test case the house has one floor and the first floor has three flats. The light is on in the leftmost flat (in both windows) and in the middle flat (in one window). In the right flat the light is off.

## 样例 #1

### 输入

```
2 2
0 0 0 1
1 0 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 3
1 1 0 1 0 0
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
## Vitaly和夜晚

### 题目描述
有一天，Vitaly深夜回家，他想知道：那一刻有多少人还没睡觉？为了估算，Vitaly决定看看他路过的房子里哪些窗户还亮着。

Vitaly看到一栋有 $n$ 层的建筑，每层有 $2·m$ 扇窗户。每层有 $m$ 套公寓，编号从 $1$ 到 $m$，每套公寓对应两扇连续的窗户。如果我们从左到右将窗户编号为 $1$ 到 $2·m$，那么第 $i$ 层的第 $j$ 套公寓在相应的窗户行中有窗户 $2·j - 1$ 和 $2·j$（通常，楼层从下往上编号）。Vitaly认为，如果对应某套公寓的至少一扇窗户亮着，那么这套公寓里的人在那一刻还没睡觉。

给定这栋房子窗户的信息，你的任务是计算根据Vitaly的判断，有多少套公寓里的人还没睡觉。

### 说明/提示
在第一个测试用例中，房子有两层，每层有两套公寓。也就是说，总共有4套公寓。只有二楼左边的公寓灯没亮。也就是说，这套公寓的两个房间灯都关着。

在第二个测试用例中，房子有一层，第一层有三套公寓。最左边的公寓（两扇窗户都亮着）和中间的公寓（一扇窗户亮着）灯是亮着的。右边的公寓灯关着。

### 样例 #1
#### 输入
```
2 2
0 0 0 1
1 0 1 1
```
#### 输出
```
3
```

### 样例 #2
#### 输入
```
1 3
1 1 0 1 0 0
```
#### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟整个统计过程，即逐户检查是否至少有一扇窗户亮着，若有则计数加1。各题解的主要区别在于实现方式，包括是否使用数组存储数据、循环的嵌套方式以及条件判断的写法等。

### 所选的题解
- **MZY666（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对判断条件 `if(left||right)ans++;` 有特别说明，便于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll n,m,i,j,ans=0,left,right;
    scanf("%lld%lld",&n,&m);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%lld%lld",&left,&right);
            if(left||right)ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
- **伟大的王夫子（4星）**
    - **关键亮点**：代码简洁，使用 `ans += x || y;` 进行压行，实现了相同的功能。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, ans;
int main() {
    int n, m;
    cin >> n >> m;
    for (register int i = 1; i <= n * m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        ans += x || y;
    }
    cout << ans;
} 
```
- **k3v1n070828（4星）**
    - **关键亮点**：使用二维数组存储灯的开关情况，通过枚举求解，思路简单直接。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int a[110][210];
int main(){
    int cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m*2;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j*2-1]==1||a[i][j*2]==1)
                cnt++;
    printf("%d\n",cnt);
    return 0;
}
```

### 最优关键思路或技巧
- 对于判断两扇窗户是否至少有一扇亮着，可使用逻辑或运算符 `||` 简化判断条件，无需分别列出多种情况。
- 可以不使用数组存储所有窗户状态，直接在输入时进行判断，减少空间复杂度。

### 可拓展之处
同类型题目可能会改变窗户的数量、楼层和户数的关系，或者增加其他条件，如不同颜色的灯代表不同状态等，但核心思路仍然是模拟和判断。

### 推荐题目
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的输入输出练习，可熟悉基本的代码框架。
- [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)：简单的模拟题，锻炼对问题的模拟和处理能力。
- [P1089 津津的储蓄计划](https://www.luogu.com.cn/problem/P1089)：通过模拟每月的收支情况来解决问题，与本题的模拟思路类似。

### 个人心得
- **MZY666**：提到评测等待时间长，认为洛谷比较好，侧面反映出评测环境对解题体验的影响。 

---
处理用时：34.11秒