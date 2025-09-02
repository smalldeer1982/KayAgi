# [USACO14JAN] Cow Curling G

## 题目描述

Cow curling is a popular cold-weather sport played in the Moolympics.

Like regular curling, the sport involves two teams, each of which slides N heavy stones (3 <= N <= 50,000) across a sheet of ice.  At the end of the game, there are 2N stones on the ice, each located at a distinct 2D point.

Scoring in the cow version of curling is a bit curious, however.  A stone is said to be "captured" if it is contained inside a triangle whose corners are stones owned by the opponent (a stone on the boundary of such a triangle also counts as being captured).  The score for a team is the number of opponent stones that are captured.

Please help compute the final score of a cow curling match, given the locations of all 2N stones.

有两支队伍在比赛，一队可以一次取出3个点来，所围成的三角形覆盖的区域可以“捕获”对方的点，问两支队伍各能够捕获对方多少个点。


## 说明/提示

Each team owns 4 stones.  Team A has stones at (0,0), (0,2), (2,0), and (2,2), and team B has stones at (1,1), (1,10), (-10,3), and (10,3).


Team A captures their opponent's stone at (1,1).  Team B captures their opponent's stones at (0,2) and (2,2).


## 样例 #1

### 输入

```
4 
0 0 
0 2 
2 0 
2 2 
1 1 
1 10 
-10 3 
10 3 
```

### 输出

```
1 2 
```

# 题解

## 作者：first_fan (赞：3)

本题题意简单：给出两组大小为n的点集，问点集A中任取三点形成的三角形围住点集B中点的数量，以及B包A的数量。

其实题目可以进一步简化：我们来看一幅图（样例解释）

![](https://i.loli.net/2019/09/15/k9uW1PR8hpZ5IfQ.png)

我们可以主观感受一下，红点被蓝点包了一个，蓝点被红点包了俩。

回想一下，我们是怎么判断的呢？一个个三角形枚举吗？$\sf\color{red}\text{并不是！}$

多感受几次，我们发现：如果一个点被异色点围成的一个多边形围住，那么它就被捕了（如下图）。**但是为什么？**

![](https://i.loli.net/2019/09/15/DBA3CNYsJqWprxh.png)

别忘了，当你把所有可能的三角形围出来的时候，就注定把这些点围成的多边形覆盖，因为所有的三角形边中一定包含了这个多边形的边。还是以图举例。

![](https://i.loli.net/2019/09/15/Jx8SYV6XMGznfgp.png)

显然这个五个点围出了五边形（为了美观，有部分三角形未画出）

直入主题，这样的多边形我们称之为$\sf\color{red}\text{凸包}$。那么我们现在需要的就是`判断点是否在凸包内`了。

关于凸包，网上已有详细的讲解，此处不作赘述。

那么此题中，我们采用的是常规的二分判断叉积法判断。

```cpp
//取其中的一个点，他和其他点可以组成n-2个三角形，利用二分判断差积，
//判断他是在当前三角形内，还是在三角形左边，还是在三角形右边，或者是三角形外。
int check(dot b,int n)
{
	int l=1;
	int r=n-2;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		ll cr1=(bor[mid]-bor[0])*(b-bor[0]);
		ll cr2=(bor[mid+1]-bor[0])*(b-bor[0]);//叉积
		if(cr1>=0&&cr2<=0)//也就是说此时该点b在bor[mid]上方或其线上，又在bor[mid+1]下方或其线上
		{
			if((bor[mid+1]-bor[mid])*(b-bor[mid])>0) //bor[mid]->bor[mid+1] 与 bor[mid]->b 的叉积
			{
				return true;
			}//如果此时叉积大于等于0,说明该点b在该三角形内部或者边界上
			//经过卡数据，此题边界点不计入内。
			return false;//点在三角形外部
		}
		else if(cr1<0)  //如果该点在bor[mid]下方，那么把上边界缩小到mid-1
		{
			r=mid-1;
		}
		else //如果该点在bor[mid+1]上方，那么把下边界拉至mid+1
		{
			l=mid+1;
		}
	}
	return false;
}
```

那么有了判断法，我们就先求出AB两点集的凸包，并且用对集的点一个个代入判断即可，这是思维量最小的方式。

* 不得不提的一点：此题的边界不算入内，有一个点恰好点在凸包边界上，不能计入内。

**为不影响阅读，[完整代码请移步此处](https://www.luogu.org/blog/firstfan/code-p3099)**

---

