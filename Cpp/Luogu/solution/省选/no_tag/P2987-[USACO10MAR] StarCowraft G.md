# [USACO10MAR] StarCowraft G

## 题目描述

The beta version of StarCowraft II is ready! Farmer John and Bessie are testing it, trying different strategies in one-on-one battles against each other's armies. The goal in StarCowraft II is to defeat your opponent's army in a battle.

Each player's army fights in a battle. An army comprises as many as three different types of 'units' with respective strengths denoted by constant positive real numbers unknown to the players: cattlebruisers with strength S1, cow templars with strength S2, and ultracows with strength S3. The only given bounding information is that no unit is more than 100 times as strong as any another unit.

An army's total strength is the sum of the individual strengths of each of its units. An army that has, among others units, 23

cattlebruisers would gain 23\*S1 strength just from the cattlebruisers.

When two opposing armies fight in a battle, the army with a higher total strength value wins.  If the armies have exactly equal strength values, one of the players randomly wins.

Farmer John and Bessie played N (0 <= N <= 300) 'test battles'. In the i-th test battle, FJ's army had J1\_i cattlebruisers, J2\_i cow templars, and J3\_i ultracows (0 <= J1\_i + J2\_i + J3\_i <= 1,000). Similarly, Bessie's army had B1\_i cattlebruisers, B2\_i cow templars, and B3\_i ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000). After their armies fought against each other, FJ and Bessie recorded the winner as a single 'victory letter' V\_i: 'J' if Farm John won the battle; 'B' if Bessie won.

Although these victory results are the only information that they have, they hope to predict some of the results of additional battles if they are given the unit compositions of two opposing armies. For some battles, though, they know it might not be possible to determine the winner with certainty.

Given the results of the N test battles that Farmer John and Bessie already played, write a program that decides the winner (if possible) for M (1 <= M <= 2,000) new battles.

The results reported for the test battles are correct; there exists at least one set of strength values which are consistent with the results.

For purposes of demonstrating the army strength evaluation functions, consider these test battles fought in a game where we (but neither FJ nor Bessie) know that S1=9.0, S2=7.0, and S3=4.0:

```cpp
---- Farmer John ----    ------- Bessie ------    Battle 
J1  J2  J3 J_Strength    B1  B2  B3 B_Strength   Outcome 
6   5   4    105         5   4   7    101          J 
5   4   2     81         3   5   5     82          B 
9   0  10    121         8   2   7    114          J 
```
These results connote the following deduced results for the reasons shown:

---- Farmer John ----    ------- Bessie ------    Battle

J1  J2  J3 J\_Strength    B1  B2  B3 B\_Strength   Outcome

6   6   4    112         5   4   7    101          J

FJ's army is even stronger than in test battle 1 9   0  10    121         8   2   6    110          J

Bessie's army is even weaker than in test battle 3

《星际争霸2》全面公测啦！Farmer John和Bessie正在测试中——在1v1的战役中使用一些不同的策略来对抗对方的部队。《星际争霸2》的游戏目标就是在战役中打败你对手的军队。

每个选手的军队都在战役中拼杀。一支军队由若干3种不同类型的单位所组成，不同单位有着不同的由正实数表示的，且不被选手所知道的力量值：cattlebruisers 的力量是S1，cow templars 的力量是S2，ultracows的力量是S3。唯一提供的信息是，没有一个单位的力量值超过另一个单位力量值的100倍。

一支军队的总力量值，是其中各自单独的单位的力量值的总和。比如一支军队除了其他单位有23个cattlebruisers，那么这支军队单独从cattlebruisers就能获得23\*S1的力量值。

当两支对立的军队在战役中厮杀，有着更高力量值的军队将获得胜利。如果两支军队的力量值恰好相同，那么将随机产生一个获胜方。

Farmer John 和 Bessie 进行了 N (0 <= N <= 300) 局的“测试战役”。在第 i 局测试战役中，Farmer John 有 J1\_i 个 cattlebruisers，J2\_i 个 cow templars 以及 J3\_i 个 ultracows(0 <= J1\_i + J2\_i + J3\_i <= 1,000)。相似的，Bessie的军队有 B1\_i 个 cattlebruisers，B2\_i 个 cow templars 以及 B3\_i 个 ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000)。当他们的军队战斗结束后，FJ 和 Bessie 将胜者以一个单独的“胜利字母” V\_i 记录下来："J"表示 Farmer John 赢得了战役；"B" 表示 Bessie 获胜了。

虽然这些结果是他们唯一所拥有的信息，但是他们希望预测一些额外的战役的结果——如果告知他们两支对立军队的组成。尽管，可能对于一些比赛他们是无法确定到底哪一方一定能获胜的。

给出已经结束的 N 场测试战役的结果，写一个程序来确定(如果可能的话)M (1 <=M <=2,000)场额外战役的获胜方。

所有给出的测试战役的结果都是正确的。至少存在一种合法的力量值的取值符合这些结果。


## 说明/提示

First two games correspond to the examples in the description. The result of the last game cannot be determined with only the information that Farmer John and Bessie currently have. Specifically, both S\_1=9.0, S\_2=7.0, S\_3=4.0 and S\_1=12.0, S\_2=20.0, S\_3=10.0 are consistent with the &quot;test battles,&quot; but they give different results when plugged in the third &quot;new battle.&quot;


## 样例 #1

### 输入

```
3 3 
J 6 5 4 5 4 7 
B 5 4 2 3 5 5 
J 9 0 10 8 2 7 
6 6 4 5 4 7 
9 0 10 8 2 6 
3 4 8 4 4 6 
```

### 输出

```
J 
J 
U 
```

# 题解

## 作者：_2022gdgzby01 (赞：2)

# 思路
首先我们发现，我们能够把三种单位的战斗力同时乘以一个数而不改变结果。因此，不妨设第三种单位的战斗力 $S_3=1$，出于方便，不妨设 $x=S_1,y=S_2$。

对于一场比赛，我们能够写出一个类似这样的式子：$j_1x+j_2y+j_3\le b_1x+b_2y+b_3$。

整理后得到一个类似这样的式子：$ax+by\le c$ 。

这就是半平面，所以做法就很简单了：对所有测试点的半平面求交，其交集是一个凸多边形。将其所有顶点求出。在试图判断一次新的战斗时，显然该场战斗对应于一条直线，如果凸多边形人所有顶点均在直线一侧，那么该战斗的结果是确定的，否则不定。

注意，那个“单位之差不超过 $100$ 倍”的条件也是要写出来的。

---

## 作者：dingyichen (赞：2)

随机摇到这道题，做完之后发现没有题解，虽然我的方法不太好，为了方便后人，还是来写一篇。

把三种军队的战力记为 $x,y,z$，接下来要处理的问题是：已知关于 $x,y,z$ 的若干不等式，怎么求含 $x,y,z$ 的表达式的取值范围？

考虑到不等式是齐次的，且未知数为正数，可以考虑除以 $x$ 将三元不等式转化为二元，同时有一个常数。又考虑到高中数学技巧，已知 $ax+by$ 和 $cx+dy$ 的范围求 $ex+fy$ 的范围，可以通过配凑的办法，将已知式分别乘上两个系数，使之和为所求式。也就是

- 已知 $ax+by\le g$ 且 $cx+dy\le h$，求 $ex+fy\le ?$
- 找到 $u,v>0$ 使得 $au+cv=e$ 且 $bu+dv=f$
- 则 $ex+fy\le ug+vh$

所以可以使用这种办法来求二元式的取值范围。

考虑实现方式，将已知战况用不等式表示（注意化成标准式），然后对于每一个询问（$q$），枚举每一对已知式（$i,j$），求解根据这一对已知式得到的范围，尝试是否能做出胜负判断。即是否能根据 $i,j$ 推出 $q>0$ 或 $q<0$（也可以表示为 $-q>0$）。

考虑细节。为了体现 $x,y,z>0$ 手动加入这几个不等式作为已知式；为了满足题目描述的“战力差距不超过 100 倍”，可以手动加入 $100x-y>0$ 等类似不等式作为已知。

考虑时间优化。由于理论时间复杂度为 $N^2\times M$ 量级，有一点点超标，我的程序中初步排除了已知式信息冗余，但根据运行结果看可能不必要，总用时只有 $110ms$

以下是蹩脚的代码：

```cpp
#include<bits/stdc++.h>//2024-6-24
using namespace std;//2024-7-29
int n,m;
int a2[330],a3[330],b2[330],b3[330];
double a4[330],b4[330],b1[330],a1[330];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		char v;cin>>v;
		int k=2*(v=='J')-1;
		int t1,t2,t3,t4,t5,t6;
		cin>>t1>>t2>>t3>>t4>>t5>>t6;
		a1[i]=k*(t1-t4);
		a2[i]=k*(t2-t5);
		a3[i]=k*(t3-t6);
		a4[i]=(a2[i]==0)?10000:1.0*a3[i]/a2[i];
	}
	b1[n+7]=1;b4[n+7]=0;
	b3[n+6]=100;b2[n+6]=-1;b4[n+6]=-100;
	b3[n+5]=100;b1[n+5]=-1;b4[n+5]=10000000;
	b2[n+4]=100;b1[n+4]=-1;
	b2[n+3]=100;b3[n+3]=-1;b4[n+3]=10000000;
	b1[n+2]=100;b3[n+2]=-1;b4[n+2]=10000000;
	b1[n+1]=100;b2[n+1]=-1;
//	b2[n+2]=1;b4[n+2]=0;
//	b3[n+1]=1;b4[n+1]=10000000;
	int bq=n;
	for(int i=n;i>=1;i--)
	{
		if((a2[i]|a3[i])==0)continue;
		bool flag=1;
		for(int j=n+7;j>bq;j--)
		{
			for(int k=bq+1;k<j;k++)
			{
												//x=(ed-cf)/(da-cb)
				int t=b3[k]*b2[j]-b2[k]*b3[j];//y=(eb-af)/(bc-ad);
				double x=1.0*(a2[i]*b3[k]-b2[k]*a3[i])/t,y=-1.0*(a2[i]*b3[j]-b2[j]*a3[i])/t;
				if(x<0||y<0)continue;
				if(x==0)
				{
					b1[k]=min(b1[k],a1[i]/y);
					flag=0;
				}
				else if(y==0)
				{
					b1[j]=min(b1[j],a1[i]/x);
					flag=0;
				}
				else if(x*b1[j]+y*b1[k]<=a1[i])
				{
					flag=0;
				}
				if(!flag)break;
			}
			if(!flag)break;
		}
		if(flag)
		{
			b1[bq]=a1[i];
			b2[bq]=a2[i];
			b3[bq]=a3[i];
			b4[bq]=a4[i];
			bq--;
		}
	}
//	cout<<bq<<'\n';
//	cout<<b3[1]<<'\n';
	for(int i=1;i<=m;i++)
	{
		int t1,t2,t3,t4,t5,t6;
		cin>>t1>>t2>>t3>>t4>>t5>>t6;
		int c2=t2-t5,c3=t3-t6;
		double c1=t1-t4,c4=(c2==0)?10000:1.0*c3/c2;
		if(!c2&&!c3)
		{
			if(c1>0)printf("J\n");
			if(c1<0)printf("B\n");
			if(c1==0)printf("U\n");
			continue;
		}
		int flag=2;
		for(int j=n+7;j>bq;j--)
		{
			for(int k=bq+1;k<j;k++)
			{									//x=(ed-cf)/(da-cb)
				int t=b3[k]*b2[j]-b2[k]*b3[j];//y=(eb-af)/(bc-ad);
				double x=1.0*(c2*b3[k]-b2[k]*c3)/t,y=(-1.0)*(c2*b3[j]-b2[j]*c3)/t;
				if(x<0||y<0)continue;
				if(x==0)
				{
					if(b1[k]<c1/y)
					flag=1;
				}
				else if(y==0)
				{
					if(b1[j]<c1/x)
					flag=1;
				}
				else if(x*b1[j]+y*b1[k]<c1)
				{
					flag=1;
				}
				if(flag!=2)
				{
					break;
				}
			}
			if(flag!=2)break;
		}
		if(flag==1)
		{
			printf("J\n");
		}
		else
		{
			c1*=-1;
			c2*=-1;
			c3*=-1;
			for(int j=n+7;j>bq;j--)
			{
				for(int k=bq+1;k<j;k++)
				{									//x=(ed-cf)/(da-cb)
					int t=b3[k]*b2[j]-b2[k]*b3[j];//y=(eb-af)/(bc-ad);
					double x=1.0*(c2*b3[k]-b2[k]*c3)/t,y=-1.0*(c2*b3[j]-b2[j]*c3)/t;
					if(x<0||y<0)continue;
					if(x==0)
					{
						if(b1[k]<c1/y)
						flag=0;
					}
					else if(y==0)
					{
						if(b1[j]<c1/x)
						flag=0;
					}
					else if(x*b1[j]+y*b1[k]<c1)
					{
						flag=0;
					}
					if(flag!=2)break;
				}
				if(flag!=2)break;
			}
			if(flag==0)
			{
				printf("B\n");
			}
			else printf("U\n");
		}
	}
	
return 0;
}
```

---

