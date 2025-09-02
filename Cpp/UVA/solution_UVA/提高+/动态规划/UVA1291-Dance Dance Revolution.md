# Dance Dance Revolution

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=4037

[PDF](https://uva.onlinejudge.org/external/12/p1291.pdf)

# 题解

## 作者：我打 (赞：2)

博客链接：https://www.cnblogs.com/Laoli-2020/p/13907130.html

注意本题为多组输入输出，直到输入单个零而止(题面有点小问题)


很明显，此题为一道动态规划题（请不要妄想用贪心算法过这题，尽管你可能可以过样例，但是应将你的依然是WA），首先要存一个cost数组，用于存储从i号点到j号点的花费，存储过程如下


```cpp
int cost[5][5];
void cost_put()
{
    for(int i=0;i<=4;i++)cost[i][i]=1;
    for(int i=1;i<=3;i++)cost[i][i+1]=cost[i+1][i]=3;
    cost[4][1]=cost[1][4]=3,cost[3][1]=cost[1][3]=cost[2][4]=cost[4][2]=4;
    for(int i=1;i<=4;i++)cost[0][i]=cost[i][0]=2;
}
```

存储完后，就该想想状态的描述，很显然，我们不仅需要描述他左脚和右脚的位置，还需要描述已经踩到了第几个音符。
因此要开一个三维的dp数组，$dp[i][j][k]$表示踩完第i个后，左脚在i号点，右脚在j号点，所需的最小花费。

想好了状态后，接着初始化，过程如下

```cpp
    scanf("%d",&x);
    for(int i=1;i<=100000;i++)
        for(int j=0;j<=4;j++)
            for(int k=0;k<=4;k++)
                dp[i][j][k]=1e9;
    dp[0][0][0]=0;dp[1][x][0]=dp[1][0][x]=2;
```

该想转移方程了，在纸上画一画，很容易想到如下的转移方程（注意以下两个方程的细微差别）
```cpp
dp[tot][x][i]=min(dp[tot-1][j][i]+cost[x][j],dp[tot][x][i]);
//正准备踩第i个，此时左脚踩到要踩的点，右脚踩在i号点上，所需的最小花费
dp[tot][i][x]=min(dp[tot-1][i][j]+cost[x][j],dp[tot][i][x]);
//正准备踩第i个，此时右脚踩到要踩的点，左脚踩在i号点上，所需的最小花费
```
想到这里已经没有什么可以难倒你了，但是有以下几点要注意：
2.$dp$数组和$ans$变量的初始值一定要设成极大值，因为要取最小值（算最小的花费值当然是取最小值）
3.最后$ans$一定取值时要在除去$dp[tot][0][0],dp[tot][1][1],dp[tot][2][2],dp[tot][3][3],dp[tot][4][4]$（$tot$为歌曲总长度）这几个状态的答案，这些状态违反了题目中两脚不可以同时踩在同一点的规则


完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,cost[5][5],dp[100010][5][5],tot=1,ans=1e9;
void cost_put()
{
    for(int i=0;i<=4;i++)cost[i][i]=1;
    for(int i=1;i<=3;i++)cost[i][i+1]=cost[i+1][i]=3;
    cost[4][1]=cost[1][4]=3,cost[3][1]=cost[1][3]=cost[2][4]=cost[4][2]=4;
    for(int i=1;i<=4;i++)cost[0][i]=cost[i][0]=2;
}
int main()
{
    cost_put();
    while(true)
	{
		scanf("%d",&x);
		if(x==0)break;
		tot=1;ans=1e9;
	    for(int i=1;i<=100000;i++)
	        for(int j=0;j<=4;j++)
	            for(int k=0;k<=4;k++)
	                dp[i][j][k]=1e9;
	    dp[0][0][0]=0;dp[1][x][0]=dp[1][0][x]=2;
	    //初始化 
	    while(x!=0)
	    {
	        scanf("%d",&x);
	        tot++;
	        for(int i=0;i<=4;i++)
	            for(int j=0;j<=4;j++)
	                 dp[tot][x][i]=min(dp[tot-1][j][i]+cost[x][j],dp[tot][x][i]);
	        for(int i=0;i<=4;i++)
	            for(int j=0;j<=4;j++)
	                dp[tot][i][x]=min(dp[tot-1][i][j]+cost[x][j],dp[tot][i][x]);
	    }
	    //转移 
	    tot--;
	    for(int i=0;i<=4;i++)
	        for(int j=0;j<=4;j++)
	            if(i!=j)ans=min(ans,dp[tot][i][j]);
	    //统计答案 
	    printf("%d\n",ans);
	}
     
    return 0;
}
```

---

## 作者：EllinY (赞：0)

## 题目翻译中的错误及补充
[discuss 969715](https://www.luogu.com.cn/discuss/969715)
$\\$ 箭头的布局应为：$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/emxphb8w.png)
## 思路
容易看出是 `dp`。用 $dp_{i,j}(j\in\{0,1,2,3,4\})$ 表示到了第 $i$ 个箭头，除了踩在 $a_i$（箭头所示位置）上的脚之外另一只脚踩在 $j$ 的位置。转移时分类讨论（用 $i$ 更新 $i+1$）：
1. 踩在 $a_i$ 上的脚刚好在 $a_{i+1}$ 上，再踩一次，耗费 $1$ 点体力。
2. 踩在 $j$ 上的脚刚好在 $a_{i+1}$ 上，再踩一次，耗费 $1$ 点体力。
3. 移动踩在 $a_i$ 上的脚去踩 $a_{i+1}$。
4. 移动踩在 $j$ 上的脚去踩 $a_{i+1}$。

为了计算一个位置到另一个位置的体力耗费，我使用了 `cal` 函数计算，`cal` 同样要分类讨论：
1. 从 $0$ 到其他位置：$2$。
2. 从 $x$ 到 $x+1$ 或者从 $4$ 到 $1$，从 $1$ 到 $4$：$3$。
3. 其他情况：$4$。

转移方程：$\\$
$\begin{cases}
dp_{i+1,j}=\min(dp_{i+1,j},dp_{i,j}+1) \quad a_i=a_{i+1}\\
dp_{i+1,a_i}=\min(dp_{i+1,a_i},dp_{i,j}+1)\quad j=a_{i+1}\\
dp_{i+1,j}=\min(dp_{i+1,j},dp_{i,j}+cal(a_i,a_{i+1})),dp_{i+1,a_i}=\min(dp_{i+1,a_i},dp_{i,j}+cal(j,a_{i+1}))\quad a_i\neq a_{i+1} \text{且} j\neq a_{i+1}
\end{cases}$ $\\$ 边界情况：$dp_{0,0}=0,a_0=0$。这样就把初始状态设为了站在 $0,0$。$\\$ 答案：$\min dp_{tot,i}(i\in\{0,1,2,3,4\})$，$tot$ 表示箭头个数。$\\$ 注意：每组数据要把 $dp_{i,j}$ 重新设为 `0x3f3f3f3f`；$tot$ 设为 $0$，重新开始统计箭头个数。
## 代码
在思路中几乎已经把代码搬上去了，建议自行编写。[AC Code](https://www.luogu.com.cn/paste/zljkh1bp)

---

