# Optimizer

## 题目描述

A process RAM is a sequence of bytes that are indexed from 1 to $ n $ . Polycarpus's program contains such instructions as "memset", that is, the operations of filling memory cells on a segment with some value. The details are: the code only contains $ m $ instructions that look like "set13 a\_i l\_i". Instruction $ i $ fills a continuous memory segment of length $ l_{i} $ , starting from cell number $ a_{i} $ , (that it cells with numbers $ a_{i},a_{i}+1,...,a_{i+li}-1 $ ) with values 13.

In Polycarpus's code, the optimizer's task is to remove the maximum number of instructions from his code in such a way that the remaining instructions set value 13 in all the memory bytes that got this value from the code before the optimization. Also, the value 13 should be set only in the memory bytes that got this value from the code before the optimization. Your task is to implement the optimizer for such program.

## 样例 #1

### 输入

```
10 4
3 3
3 1
4 1
9 2
```

### 输出

```
2
2 3 ```

## 样例 #2

### 输入

```
1 1
1 1
```

### 输出

```
0
```

# 题解

## 作者：ztxtjz (赞：3)

## 【题意】
有$n$个数，$m$个操作，尽可能多地删去操作使最终结果不变。输出删去操作个数和对应操作的序号，有多组解输出任意一组即可。
## 【思路】
#### 算法：贪心
将每一个区间看作一条线段，将线段的左端点坐标从小到大排序，若左端点位置相同则右端点坐标从大到小排序。因为数据范围不大，我用优先队列来实现。

首先选取左端点最靠左的一条线段，范围为$l$ $-$ $r$。在$l$ $-$ $r$若存在线段左端点，比较这条线段的右端点的位置与maxr（初始化为r），若大于则更新maxr并记录线段序号。循环结束后更新线段重复上述操作。

更详情参见代码。
## 【代码】
```cpp
#include <cstdio>
#include <queue>
int n,m,ans,a[200005],b[200005];
bool vis[2000005],first;
std::priority_queue<int> q[2000005];  //从大到小排序
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a[i],&b[i]),q[a[i]].push(a[i]+b[i]);  //a[i]为左端点位置，a[i]+b[i]为右端点位置
	for(int i=1;i<=n;i++)
	{
		if(!first)  //第一次操作选取左端点最靠左的一条线段
		{
			for(;q[i].empty();i++);
			first=1;
		}
		int maxr=q[i].top(),k;  //若当前左端点开始有多条线段，q[i].top（）选出右端点最靠右的那条线段
		for(int j=i+1;j<=q[i].top()&&j<=n;j++)  //从左端点向右寻找下一线段的左端点
		{
			if(!q[j].empty())
			{
				if(q[j].top()>maxr)  //若下一线段的右端点＞maxr，更新maxr和序号k
				{
					k=j;
					maxr=q[j].top();
				}
			}
		}
		vis[i]=1;  //当前线段左端点已使用过
		ans++;  //使用操作加一
		if(maxr>q[i].top())  //如果循环中更新过，即在当前线段的范围中存在一条不被完全包含的线段
		{
			i=k-1;
		}
		else  //从当前线端右端点寻找下一条线段，因为循环中i<=n+1，没有下一条线段会退出所有循环
		{
			for(i=q[i].top()+1;q[i].empty()&&i<=n+1;i++);
			i--;
		}
	}
	printf("%d\n",m-ans);  //总操作数减去已使用操作数
	for(int i=1;i<=m;i++)
	{
		if(vis[a[i]])  //当前线段的左端点被使用过
		{
			if(a[i]+b[i]!=q[a[i]].top())  //不是那条被使用过的线段
				printf("%d ",i);
			else
				vis[a[i]]=0;  //防止相同操作的存在
		}
		else printf("%d ",i);  //没有使用过
	}
	return 0;
}
```


---

## 作者：ZolaWatle (赞：1)

## CF306B 题解

### 题目大意

给你一个长为 $n$，初始都为 $0$ 的数组。有 $m$ 次操作，每次操作将从 $a$ 开始，长度为 $l$ 的区间覆盖（即使区间上的所有数变为 $1$），为了方便，我们把这样的操作记为 $(a,l)$ 。你需要求出 $m$ 次操作中的所有“多余操作”。我们定义“多余操作”是指取消该次操作后使最终操作结果不变的操作。输出时，输出“多余操作”的数量及它们的编号，要求升序输出。

具体来讲，假设有以下操作：$ (3,3)\ (3,1)\ (4,1)\ (6,4)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/b3rlmg80.png)

从图中我们可以看出，操作二和操作三是“多余操作”。首先，由操作一和操作二可以看出，有两次操作 $x$ 和 $y$， **如果 $a_x=a_y$ 并且 $l_x<l_y$**，那么操作 $x$ 是多余操作。或者说，如果一个操作完全覆盖了其他若干个操作，那么其他的所有操作都是“多余操作”。

### 解题思路

首先考虑暴力一下。对于每一次操作，看其是否被其他操作中的某一次操作完全覆盖。这种做法的复杂度肯定不能接受。我们考虑优化。

这里我介绍一种复杂度为 $ \text{O(n)} $ 的算法。

我们令 $a_i$ 为操作 $i$ 覆盖区间的左端点，$b_i$ 是右端点右边的第一个点，$l_i$ 是区间长度。由于我们读入的是 $a$ 和 $l$，所以 $b$ 的值需要计算：$b_i=a_i+l_i$。

设 $mx_i$ 是以 $i$ 为起点，最远等到达的 $b_j, j\in \{ j|a_j=i \}$。什么意思呢？举个例子。有三个操作：$ (3,3)\ (3,1)\ (4,1)$，那么 $mx_3=6, mx_4=5$。

我们考虑依次枚举区间的左端点，记为 $i$。如果没有以这个点为左端点的操作区间，则直接跳过。如果有，我们把这个点标记为“已使用”，然后枚举从 $i+1$ 枚举到 $maxs$（初始为 $mx_i$，意为可以覆盖到的最远节点的右边的第一个点），把枚举的点记为 $j$，如果 $j$ 满足以下两个条件：

- 存在以点 $j$ 为左端点的操作区间。
- $mx_j>maxs$

我们就将 $maxs$ 更新为 $mx_j$，继续向右扩展。同时，我们记录一个点 $k=j$，表示接下来我们应该去到的左端点的后面第一个点是 $k$。这样就用一个贪心的逻辑，不去使用中间“多余操作”区间的左端点了。

如果 $j$ 已经被枚举完了，但是依然没有出现更新操作，那么说明所有以 $i$ 为左端点的操作区间均没有完全覆盖其他任何区间，那么就莫得想法，继续枚举。

枚举完所有左端点后，我们得到了所有左端点是否被使用的情况，接下来，我们枚举每一次操作。如果操作 $i$ 的左端点被使用过，有两种可能：

- 如果 $b_i\neq mx_{a_i}$，说明这次操作的操作区间被完全覆盖了，即此操作为“多余操作”，我们直接输出。
- 如果 $b_i \neq mx_{a_i}$，则说明这次操作区间并没有被完全覆盖。接下来就是我个人认为全题最坑的点：有可能会有**重复操作**。显然，重复的操作只需要留下一次，其他的操作都可以删去。为了避免这种错误，我们在第一次遇到“必要操作”时将标记在端点 $a_i$ 上的标记去除。这样一来，下次扫描到一模一样的操作时，程序就会判断它是“多余操作”了。

如果操作 $i$ 的左端点没有被使用过，那么它一定就是“多余操作”，直接输出即可。

更多细节实现请看完整代码。

### 完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N=2e6+1,M=2e5+1;
int n,m,cnt,hav,a[M],b[M],l[M],used[N],siz[N],mx[N];

inline int rint()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}

int main()
{
	n=rint(),m=rint();
	for(int i=1;i<=m;i++)
	{
		a[i]=rint(),l[i]=rint();
		b[i]=a[i]+l[i];
		siz[a[i]]++;  //这个记录的是以a[i]为左端点的操作的个数，如果siz=0，则代表没有操作 
		mx[a[i]]=max(mx[a[i]],a[i]+l[i]);
	}
		
	for(int i=1;i<=n;i++)
	{
		if(!hav) 
		{
			while(!siz[i])
				i++;
			hav=1;
		}//找到第一个有操作的左端点 
		
		used[i]=1;
		cnt++;  //做标记，记录“必要操作”的个数 
		
		int r,k=0,flg=0;
		r=mx[i];  //最远能扩展到的点最初是以i为左端点最远能覆盖到的点 
		for(int j=i+1;j<=mx[i]&&j<=n;j++)  //我们还要防止越界 
			if(siz[j]&&mx[j]>r)  //有操作且能更新右端点 
			{
				k=j;
				r=mx[j];
				flg=1;  //记录已被更新过 
			}
		
		if(flg)  //如果被更新过 
			i=k-1;  //由于存的是右端点右边的第一个点，需要-1得到新的左端点 
		else
		{
			i=mx[i]+1;
			while(!siz[i]&&i<=n+1)  //这里也是跳过没有操作的节点 
				i++;
			i--;  //+1-1的理由同上述 
		}
	}
	
	printf("%d\n",m-cnt);  //多余操作=总操作-必要操作 
	for(int i=1;i<=m;i++)
	{
		if(used[a[i]])
		{
			if(b[i]!=mx[a[i]])
				printf("%d ",i);
			else
				used[a[i]]=0;
		}
		else
			printf("%d ",i);
	}
	
	return 0;
}
```

------------

感谢阅读。

---

## 作者：UperFicial (赞：0)

题解做法是真麻烦啊。

我们对于每个左端点，保存这个点对应的最大右端点 $mx_l$。

从小到大考虑每个左端点，左端点相同优先考虑右端点较大者。

那么显然，第一条线段肯定会被保留，不妨这条线段的右端点为 $R$，那么考虑 $R$ 之后第一个被线段覆盖的点 $i$，那么我们就需要保留一条覆盖 $i$ 的线段，由于 $(R,i)$ 之间都是没有被覆盖的，那么贪心考虑，我们只需要让这条线段右端点尽量大即可。

这个就非常好实现了，我们不去枚举线段，而是枚举每个端点，在枚举端点 $i$ 的过程中，记录 $mx_i$ 的最大值 $maxr$，当遇到第一个 $i>R$ 并且 $i$ 被线段覆盖过，那么我们就保留 $maxr$ 对应的端点即可，那么显然，我们只需要继续考虑第一个大于 $i$ 的被覆盖过的端点即可，这个和上面是一样，直接将 $R$ 改成 $maxr$ 即可。

那么我们将选的线段打上标记之后，没打过标记的线段就是要剔除的。

复杂度 $O(n+m)$。

```cpp
int main()
{
	n=read(),m=read();
	rep(i,1,m)
	{
		int l=read(),x=read();
		int r=x+l-1;
		if(mx[l]<r) mx[l]=r,id[l]=i; 
		d[l]++,d[r+1]--;
	}
	rep(i,1,n) d[i]+=d[i-1];
	int maxr=0,R=0,p=0;
	rep(i,1,n)
	{
		if(maxr<mx[i]) maxr=mx[i],p=id[i];
		if(d[i]&&i>R) flag[p]=true,R=maxr;
	}
	rep(i,1,m) if(!flag[i]) G.push_back(i);
	printf("%d\n",(int)G.size());
	for(auto x:G) printf("%d ",x);
	return 0;
}
```


---

## 作者：CrTsIr400 (赞：0)

# 0.前置知识

排序，贪心思想。

# 1.思路推导

看到是多个区间，我们不妨想到贪心中有一类东西：**区间覆盖问题。**

+ 结论1：按照 $l$ 排序，如果 $l$ 相同，就选 $r$ 最大的。
+ 结论2：下一个区间的左端点要在 $(l,r+1]$ 之间，取右端点最大的。

推导：

可以发现，如果 $[l1,r1]$ 包含 $[l2,r2]$ 即 $l1\le l2\le r2\le r1$ ，那么只选 $[l1,r1]$ 会更优。

所以，如果 $l$ 相同，那取 $r$ 最大的一定不会被包含。所以取 $r$ 最大的 **一定是最优解。**

再深入具体一点，假设我们确定了 $[l,r]$ ，现在要选一个能转移答案的点，那么这个点的左端点一定 $>l,<=r+1$ （因为这是覆盖数列）。按照 结论1 的推导过程，我们发现 **左端点不一定重要，但是右端点的位置才是最重要的**，所以，**右端点越大越好**。

整合一下结论：

+ 按照左端点排序，如果 $l$ 相同 $r$ 大的优先
+ 确定了第一个区间 $[x,y]$ 之后，寻找 **拥有最大的 $r$ 的区间** $i$ 使得 $l<=y+1$ ，把 $[x,y]$ 转移到 $[l,r]$ ，标记 $i$ 。

按照该结论模拟即可得出代码。

---

