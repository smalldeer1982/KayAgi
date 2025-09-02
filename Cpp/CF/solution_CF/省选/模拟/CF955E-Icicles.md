# Icicles

## 题目描述

Andrew's favourite Krakozyabra has recenly fled away and now he's eager to bring it back!

At the moment the refugee is inside an icy cave with $ n $ icicles dangling from the ceiling located in integer coordinates numbered from $ 1 $ to $ n $ . The distance between floor and the $ i $ -th icicle is equal to $ a_{i} $ .

Andrew is free to choose an arbitrary integer point $ T $ in range from $ 1 $ to $ n $ inclusive and at time instant $ 0 $ launch a sound wave spreading into both sides (left and right) at the speed of one point per second. Any icicle touched by the wave starts falling at the same speed (that means that in a second the distance from floor to icicle decreases by one but cannot become less that zero). While distance from icicle to floor is more than zero, it is considered passable; as soon as it becomes zero, the icicle blocks the path and prohibits passing.

Krakozyabra is initially (i.e. at time instant $ 0 $ ) is located at point ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/6201067a97da7a97c457211e210f5a8e998bdde9.png) and starts running in the right direction at the speed of one point per second. You can assume that events in a single second happen in the following order: first Krakozyabra changes its position, and only then the sound spreads and icicles fall; in particular, that means that if Krakozyabra is currently at point ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/1c5af17636ba64dd5732c7aa8ec584757d0bd2cf.png) and the falling (i.e. already touched by the sound wave) icicle at point $ i $ is $ 1 $ point from the floor, then Krakozyabra will pass it and find itself at ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/698ff77408e1322df2c02364658180d6abdd0230.png) and only after that the icicle will finally fall and block the path.

Krakozyabra is considered entrapped if there are fallen (i.e. with $ a_{i}=0 $ ) icicles both to the left and to the right of its current position. Help Andrew find the minimum possible time it takes to entrap Krakozyabra by choosing the optimal value of $ T $ or report that this mission is impossible.

## 说明/提示

In sample case one it's optimal to launch the sound wave from point $ 3 $ . Then in two seconds icicles $ 1 $ and $ 5 $ will start falling, and in one more seconds they will block the paths. Krakozyabra will be located at ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/6a876c63f063c77b3b3f7a4894559278a4f9c115.png) at that time. Note that icicle number $ 3 $ will also be fallen, so there will actually be two icicles blocking the path to the left.

In sample case two it is optimal to launch the wave from point $ 2 $ and entrap Krakozyabra in $ 2 $ seconds.

In sample case four the answer is impossible.

## 样例 #1

### 输入

```
5
1 4 3 5 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
2 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
2
1 2
```

### 输出

```
-1
```

# 题解

## 作者：VenusM1nT (赞：2)

考虑在 $T$ 点释放声波，那么第 $i$ 个位置的冰锥会在 $f_T(i)=a_i+|T-i|$ 时刻之后落地，若存在最小的 $j$ 使得 $f_T(j)<j$，那么 Krakozyabra 会在 $j$ 时刻被挡住，然后再等到左侧冰锥落下。考虑到后面可能有冰锥更早落下，可以得到答案为
$$\max\{\min_{1\leq i<j}\{f_T(i)\},\min_{j\leq i\leq n}\{f_T(i)\}\}$$
此时复杂度为 $\text{O}(n^2)$，考虑优化。将 $f_T$ 中的绝对值拆掉，分别为 $f_T(i)=a_i+T-i\ (i\leq T)$，$f_T(i)=a_i-T+i\ (i>T)$，用两个数组 $\text{pre,\ suf}$ 存储。考虑转化 $f_T(i)<i$ 这个不等式，根据前面提到的拆绝对值，若 $i\leq T$，即为 $T<i\times 2-a_i$；若 $i>T$，即为 $a_i<T$。至此，可以通过枚举 $T$，二分 $i$，配合任意一种 rmq 算法得到答案。
```cpp
#include<bits/stdc++.h>
#define N 100000
#define reg register
#define inl inline
#define inf 1e9
using namespace std;
int n,a[N+5],_[N+5],minx[N+5][25],pre[N+5][25],suf[N+5][25];
inl int Query(reg int l,reg int r)
{
	if(l>r) return inf;
	reg int k=_[r-l+1];
	return min(minx[l][k],minx[r-(1<<k)+1][k]);
}
inl int QryP(reg int l,reg int r)
{
	if(l>r) return inf;
	reg int k=_[r-l+1];
	return min(pre[l][k],pre[r-(1<<k)+1][k]);
}
inl int QryS(reg int l,reg int r)
{
	if(l>r) return inf;
	reg int k=_[r-l+1];
	return min(suf[l][k],suf[r-(1<<k)+1][k]);
}
int main()
{
	scanf("%d",&n);
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		minx[i][0]=a[i];
		pre[i][0]=a[i]-i;
		suf[i][0]=a[i]+i;
	}
	for(reg int i=2;i<=n;i++) _[i]=_[i>>1]+1;
	for(reg int j=1;j<=20;j++)
	{
		for(reg int i=1;i<=n-(1<<j)+1;i++)
		{
			minx[i][j]=min(minx[i][j-1],minx[i+(1<<(j-1))][j-1]);
			pre[i][j]=min(pre[i][j-1],pre[i+(1<<(j-1))][j-1]);
			suf[i][j]=min(suf[i][j-1],suf[i+(1<<(j-1))][j-1]);
		}
	}
	reg int now=1,ans=inf;
	for(reg int i=1;i<=n;i++)
	{
		while(now<=i && now*2-a[now]<=i) now++;
		reg int x,y,pos=-1;
		if(now<=i) pos=now;
		else
		{
			reg int l=i,r=n;
			while(l<=r)
			{
				reg int mid=(l+r)>>1;
				if(Query(i,mid)<i)
				{
					pos=mid;
					r=mid-1;
				}
				else l=mid+1;
			}
			if(!~pos) continue;
		}
		if(pos<=i)
		{
			x=QryP(1,pos-1)+i;
			y=min(QryP(pos,i)+i,QryS(i+1,n)-i);
		}
		else
		{
			x=QryS(pos,n)-i;
			y=min(QryP(1,i)+i,QryS(i+1,pos-1)-i);
		}
		ans=min(ans,max(x,y));
	}
	printf("%d\n",ans>=inf/2?-1:ans);
	return 0;
}
```

---

