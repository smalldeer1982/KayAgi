# Pebbles and Beads

## 题目描述

这里有两种货币：鹅卵石和珠子。最初你有 $a$ 颗鹅卵石和 $b$ 个珠子。

一共有 $n$ 天，每天你可以按照某个汇率将一种货币兑换成另一种货币。

在第 $i$ 天，你可以通过交换 $-p_i \leq x \leq p_i$ 来获得 $-q_i \leq y \leq q_i$ 的珠子或者相反。允许不进行任何交换。同时，如果你进行了交换，必须满足比例 $x \cdot q_i =-y\cdot p_i$。允许进行小数交换。

你一天只能进行一次这样的交换。你拥有的鹅卵石和珠子的数量必须始终保持非负。

请解决以下 $n$ 个问题：对于第 $i$ 天，输出在进行最优交换后，第 $i$ 天结束时你可以拥有的最大鹅卵石数量。

### **简明题意**

你初始有 $a$ 个鹅卵石和 $b$ 个珠子。对于给定的 $n$ 天的汇率，请求出每天结束后能拥有的最大鹅卵石数量。

## 样例 #1

### 输入

```
3
2 6 0
2 3
4 2
3 0 6
4 2 10
2 3 10
1 10 10
33
1000```

### 输出

```
6
8
4
6
9.000000
10.33```

# 题解

## 作者：djwj223 (赞：10)

赛时没时间开这个题，大悲。

首先注意到这题是两种物品个数之间的转换，很自然的把每一个状态映射到笛卡尔坐标系中的点上，横坐标表示第一种物品个数，纵坐标表示第二种物品的个数。于是我们便是需要维护第一象限中的凸壳，每次把这个凸壳向一个方向移动 $\sqrt{p^2+q^2}$，也向反方向移动 $\sqrt{p^2+q^2}$，下一次可以取到的状态就是这个凸壳滑动过程中覆盖到过的所有面积，每次的答案即为凸壳与 $x$ 轴的交点的横坐标。开始的凸壳是顶点为 $(0,0),(0,q),(p,0),(p,q)$ 的长方形。

一眼闵可夫斯基和但是这里完全不需要，开一个 $\operatorname{multiset}$ 扔进去斜率和长度表示凸壳上的每一条边，因为是凸壳所有边的顺序就是斜率从小到大的顺序。如何做到只维护第一象限呢？记录你当前第一象限凸壳中的两个交点：与 $x$ 轴的和与 $y$ 轴的。每次加入一条边两个点会相应的移动：移动到第二象限和第四象限。从两个头开始一条一条删边使最后留下的两段的两条边与 $x$ 轴 $y$ 轴有交点。截断之，还是使两个顶点回到 $x$ 轴和 $y$ 轴上。总复杂度 $O(n\log n)$。

还有不懂的可以看代码：

```cpp
#include<bits/stdc++.h>
#define ld long double
#define Eps 1e-9
#define fi first
#define se second
using namespace std;
const int M=3e5+7;
multiset<pair<ld,ld> > ms;
ld sx,sy,tx,ty;
int n,x,y,p[M],q[M];
int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&x,&y);
		sx=tx=x,sy=ty=y,ms.clear();
		for(int i=1;i<=n;i++) scanf("%d",&p[i]);
		for(int i=1;i<=n;i++) scanf("%d",&q[i]);
		if(x==0 && y==0){
			for(int i=1;i<=n;i++) puts("0");
			continue;
		}
		for(int i=1;i<=n;i++){
			ld np=p[i],nq=q[i];
			sx-=np,sy+=nq,tx+=np,ty-=nq;
			ms.insert({nq/np,np*2});
			while(sx<-Eps){
				auto it=ms.begin();
				ms.erase(it);
				ld k=it->fi,xx=it->se;
				if(sx+xx>0){
					ld X=sx+xx; xx-=X;
					ms.insert({k,X});
				}
				sx+=xx,sy-=xx*k;
			}
			while(ty<-Eps){
				auto it=ms.end();
				it--,ms.erase(it);
				ld k=it->fi,xx=it->se;
				if(ty+xx*k>0){
					ld X=ty/k+xx; xx-=X;
					ms.insert({k,X});
				}
				tx-=xx,ty+=xx*k;
			}
			printf("%.9Lf\n",tx);
		}
	}
	return 0;
}
```

---

