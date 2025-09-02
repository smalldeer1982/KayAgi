# Multithreading

## 题目描述

You are given the following concurrent program. There are $ N $ processes and the $ i $ -th process has the following pseudocode:

`repeat  $ n_{i} $  times<br></br>     $ y_{i} $  :=  $ y $ <br></br>     $ y $  :=  $ y_{i}+1 $ <br></br>end repeat<br></br>`Here $ y $ is a shared variable. Everything else is local for the process. All actions on a given row are atomic, i.e. when the process starts executing a row it is never interrupted. Beyond that all interleavings are possible, i.e. every process that has yet work to do can be granted the rights to execute its next row. In the beginning $ y=0 $ . You will be given an integer $ W $ and $ n_{i} $ , for $ i=1,...\ ,N $ . Determine if it is possible that after all processes terminate, $ y=W $ , and if it is possible output an arbitrary schedule that will produce this final value.

## 说明/提示

For simplicity, assume that there is no repeat statement in the code of the processes, but the code from the loop is written the correct amount of times. The processes are numbered starting from 1. The list of integers represent which process works on its next instruction at a given step. For example, consider the schedule 1 2 2 1 3. First process 1 executes its first instruction, then process 2 executes its first two instructions, after that process 1 executes its second instruction, and finally process 3 executes its first instruction. The list must consists of exactly $ 2·Σ\ _{i=1...N}n_{i} $ numbers.

## 样例 #1

### 输入

```
1 10
11
```

### 输出

```
No
```

## 样例 #2

### 输入

```
2 3
4 4
```

### 输出

```
Yes
1 1 2 1 2 2 2 2 2 1 2 1 1 1 1 2
```

## 样例 #3

### 输入

```
3 6
1 2 3
```

### 输出

```
Yes
1 1 2 2 2 2 3 3 3 3 3 3
```

# 题解

## 作者：leozhang (赞：1)

一道很有趣的题...难度并不是很大，基本可以接受

显然这是一个构造问题

我们分成几类进行讨论：

首先，如果目标是非正数，那一定是不可能的（显而易见）

然后，如果目标比允许操作的和还要大，那也是不可能的

剩下的情况就不那么显然了，我们先假设有解再进行讨论

（插播一句：强烈建议食用样例！！！对正解有很大启发！！！）

首先，如果需要构造的值比所有操作数中的最小值还要小（如样例2），怎么办？

样例2给出了较为明确的思想：

我们记录两个位置，一个是最小操作数的位置，另一个随意

我们的目标是用最小操作数的位置来构造出答案

我们在第二个位置上先记录一下一开始的值，然后把剩余所有位置上多余的部分全跑完，但是把最小操作数的位置上保留足够构造出答案的操作数

然后在第二个位置上再点一次，这样就把yy更新回了1

然后在最小值的位置上记录下当前yy的值，再把第二个位置多余的操作跑完

再在最小值位置点完，就能成功构造出目标了

可是这里有一个问题：如果目标是1呢？这样做出来能构造出的目标至少是2啊！

所以如果目标是11，却没有任何一个操作数是1，那么就是无解的！

如果有呢？

那种可以和下一种情况合并

下一种情况自然就是需要构造的值比最小值要大

这样的话，最小值即使跑满也不会超标

因此我们在最小值的位置上先记录下yy，然后把别的多余的部分跑满，最后利用原来记录的位置把yy改回去，然后跑满即构造出了答案

这样就结束了

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
int num[105];
int n,w;
int sum=0,minv=0x3f3f3f3f;
int main()
{
    freopen("brand.in","r",stdin);
    freopen("brand.out","w",stdout);
    scanf("%d%d",&n,&w);
    int posi=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
        sum+=num[i];
        if(minv>num[i])minv=num[i],posi=i;
    }
    if(w<=0||sum<w){printf("Toushui\n");return 0;}
    if(w<minv)
    {
        if(w==1){printf("Toushui\n");return 0;}
        int pp=0;
        for(int i=1;i<=n;i++)if(i!=posi&&num[i]){pp=i;num[i]--;break;}
        if(!pp){printf("Toushui\n");return 0;}
        printf("Yuyue\n");
        printf("%d ",pp);
        while(num[posi]+1>w)printf("%d %d ",posi,posi),num[posi]--;
        for(int i=1;i<=n;i++)
        {
            if(i==pp||i==posi)continue;
            while(num[i])printf("%d %d ",i,i),num[i]--;
        }
        printf("%d %d ",pp,posi);
        while(num[pp])printf("%d %d ",pp,pp),num[pp]--;
        printf("%d ",posi),num[posi]--;
        while(num[posi])printf("%d %d ",posi,posi),num[posi]--;
        printf("\n");
    }else 
    {
        printf("Yuyue\n");
        printf("%d ",posi);
        int res=sum-w;
        for(int i=1;i<=n;i++)
        {
            if(i==posi)continue;
            while(num[i])
            {
                if(res)printf("%d %d ",i,i),res--,num[i]--;
                if(!res)break;
            }
            if(!res)break;
        }
        printf("%d ",posi);
        num[posi]--;
        for(int i=1;i<=n;i++)while(num[i])printf("%d %d ",i,i),num[i]--;
        printf("\n");
    }
    return 0;
}
```


---

