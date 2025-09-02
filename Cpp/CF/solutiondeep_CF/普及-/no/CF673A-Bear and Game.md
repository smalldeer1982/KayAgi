# 题目信息

# Bear and Game

## 题目描述

Bear Limak likes watching sports on TV. He is going to watch a game today. The game lasts $ 90 $ minutes and there are no breaks.

Each minute can be either interesting or boring. If $ 15 $ consecutive minutes are boring then Limak immediately turns TV off.

You know that there will be $ n $ interesting minutes $ t_{1},t_{2},...,t_{n} $ . Your task is to calculate for how many minutes Limak will watch the game.

## 说明/提示

In the first sample, minutes $ 21,22,...,35 $ are all boring and thus Limak will turn TV off immediately after the $ 35 $ -th minute. So, he would watch the game for $ 35 $ minutes.

In the second sample, the first $ 15 $ minutes are boring.

In the third sample, there are no consecutive $ 15 $ boring minutes. So, Limak will watch the whole game.

## 样例 #1

### 输入

```
3
7 20 88
```

### 输出

```
35
```

## 样例 #2

### 输入

```
9
16 20 30 40 50 60 70 80 90
```

### 输出

```
15
```

## 样例 #3

### 输入

```
9
15 20 30 40 50 60 70 80 90
```

### 输出

```
90
```

# AI分析结果

### 题目翻译
# 熊与比赛

## 题目描述
熊利马克喜欢在电视上看体育节目。他今天打算看一场比赛。这场比赛持续 90 分钟，且中间没有休息。

每分钟要么有趣，要么无聊。如果连续 15 分钟都很无聊，那么利马克会立即关掉电视。

你知道将会有 $n$ 个有趣的分钟 $t_{1},t_{2},\cdots,t_{n}$。你的任务是计算利马克会看这场比赛多少分钟。

## 说明/提示
在第一个样例中，第 21、22、……、35 分钟都很无聊，因此利马克会在第 35 分钟后立即关掉电视。所以，他会看 35 分钟的比赛。

在第二个样例中，前 15 分钟都很无聊。

在第三个样例中，没有连续 15 分钟的无聊时间。所以，利马克会看完整个比赛。

## 样例 #1
### 输入
```
3
7 20 88
```
### 输出
```
35
```

## 样例 #2
### 输入
```
9
16 20 30 40 50 60 70 80 90
```
### 输出
```
15
```

## 样例 #3
### 输入
```
9
15 20 30 40 50 60 70 80 90
```
### 输出
```
90
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟利马克观看比赛的过程，根据连续无聊分钟数是否达到 15 分钟来判断是否关闭电视。各题解的不同在于实现方式：
- **标记法**：用数组标记有趣的分钟，然后遍历每分钟，统计连续无聊分钟数。
- **时间比较法**：直接比较相邻有趣分钟的时间间隔，判断是否会因为连续无聊 15 分钟而关闭电视。

### 题解列表
- **作者：江山_远方（4星）**
  - **关键亮点**：思路清晰，通过标记有趣分钟，枚举每分钟判断是否无聊，逻辑简单易懂。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,x;
int b[100];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        b[x]=1;
    }
    x=0;
    for(int i=1;i<=90;i++)
    {
        if(!b[i])x++;
        else x=0;
        s++;
        if(x>=15)break;
    }
    cout<<s;
    return 0;
}
```
- **作者：applese（4星）**
  - **关键亮点**：代码简洁，通过比较相邻有趣分钟的时间间隔，直接更新可观看的时间，减少不必要的遍历。
  - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n , k=15 , a;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin >> a;
        if(a <= k)
            k = a + 15;
        else
            break;
        if(k > 90)
        {
            k = 90;
            break;
        }
    }
    cout<<k;
    return 0;
}
```
- **作者：时律（4星）**
  - **关键亮点**：使用快读快写优化输入输出，提高效率，同时也是通过标记有趣分钟来模拟观看过程。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[105];
int r()
{
    char c=getchar();int u=0,s=1;
    while(c<'0' or c>'9'){if(c=='-') s=-1;c=getchar();}
    while(c>='0' and c<='9'){u=(u<<3)+(u<<1)+(c^48);c=getchar();}
    return u*s;
}
void p(int n)
{
    if(n<0){putchar('-');n=-n;}
    if(n>9) p(n/10);
    putchar(n%10+'0');
}
int main()
{
    int a=r(),b=0;
    for(int i=1;i<=a;i++)
        x[r()]=1;
    for(int i=1;i<=90;i++)
        if(x[i]==0)
        {
            b++;
            if(b==15)
            {
                p(i);
                return 0;
            }
        }
        else
            b=0;
    p(90);
}
```

### 最优关键思路或技巧
- **标记法**：用数组标记有趣的分钟，方便后续判断每分钟是否无聊。
- **时间比较法**：直接比较相邻有趣分钟的时间间隔，避免不必要的遍历，提高效率。

### 拓展思路
同类型题通常是模拟某个过程，根据特定条件进行判断和操作。类似算法套路包括模拟游戏过程、模拟事件发生顺序等，关键在于理清逻辑，准确实现条件判断。

### 推荐洛谷题目
- P1046 陶陶摘苹果
- P1427 小鱼的数字游戏
- P1001 A+B Problem

### 个人心得
无

---
处理用时：31.90秒