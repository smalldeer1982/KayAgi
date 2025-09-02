# Even Split

## 题目描述

A revolution has recently happened in Segmentland. The new government is committed to equality, and they hired you to help with land redistribution in the country.

Segmentland is a segment of length $ l $ kilometers, with the capital in one of its ends. There are $ n $ citizens in Segmentland, the home of $ i $ -th citizen is located at the point $ a_i $ kilometers from the capital. No two homes are located at the same point. Each citizen should receive a segment of positive length with ends at integer distances from the capital that contains her home. The union of these segments should be the whole of Segmentland, and they should not have common points besides their ends. To ensure equality, the difference between the lengths of the longest and the shortest segments should be as small as possible.

## 说明/提示

In the first example, it is possible to make all segments equal. Viva la revolucion!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666E/ebc3505f8c3c8786f0534e1e2096e45f0a6d83b4.png)In the second example, citizens live close to the capital, so the length of the shortest segment is 2 and the length of the longest segment is 8.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666E/f5172aa3d9343b9ef6923515224c875f543253cd.png)

## 样例 #1

### 输入

```
6 3
1 3 5```

### 输出

```
0 2
2 4
4 6```

## 样例 #2

### 输入

```
10 2
1 2```

### 输出

```
0 2
2 10```

# 题解

## 作者：hyman00 (赞：7)


# CF1666E

## 思路

注意到本题满足单调性，所以可以二分最大值和最小值的差。

```c++
	cin>>k>>n;
	rep(i,n){
		int x;
		cin>>x;
		p.pb(x);
	}
	p.pb(INF);
	int l=0,r=k+1;
	while(l<r){
		int m=(l+r)/2;
		if(chk2(m))
			r=m;
		else
			l=m+1;
	}
```

此时，我们只知道差，并不知道最小值和最大值。

可以先康康知道最小值和最大值后怎样判断是否合法。

```c++
int chk(int l,int r){
	int ll=0,rr=0;
	rep(i,n){
		if(ll+l>p[i+1]||rr+r<p[i])
			re 0;
		ll=max(ll+l,p[i]);
		rr=min(rr+r,p[i+1]);
	}
	if(ll<=k&&k<=rr)
		re 1;
   re 0;
}
```

这个函数里 `ll` 和 `rr` 分别为放完当前段后右端点可能的取值区间。

就可以发现稍微改一改就可以判断不合法是大了还是小了。

```c++
int chk(int l,int r){
	int ll=0,rr=0;
	rep(i,n){
		if(ll+l>p[i+1])
			re 1;
		if(rr+r<p[i])
			re -1;
		ll=max(ll+l,p[i]);
		rr=min(rr+r,p[i+1]);
	}
	if(rr<k)
		re -1;
	if(ll<=k&&k<=rr)
		re 0;
	if(ll>k)
		re 1;
}
```

观察发现这个也满足单调性，可以二分！

最后还要还原答案。

```c++
void chk3(int ans){
	int l=0,r=k+1,tot=-1;
	while(l<=r){
		int m=(l+r)/2;
		int cur=chk(m,m+ans);
		if(cur==0){
			tot=m;
			break;
		}
		if(cur<0)
			l=m+1;
		if(cur>0)
			r=m-1;
	}
	assert(tot>=0);
	l=tot,r=tot+ans;
	int ll=0,rr=0;
	vector<pii>ps;
	rep(i,n){
		ps.pb({ll,rr});
		ll=max(ll+l,p[i]);
		rr=min(rr+r,p[i+1]);
	}
	int cur=k;
	vi siz;
	for(int i=n-1;i>=0;i--){
		ll=ps[i].F,rr=ps[i].S;
		if(l<=cur-ll&&cur-ll<=r)getnum(cur-ll);
		else if(l<=cur-rr&&cur-rr<=r)getnum(cur-rr);
		else if(ll<=cur-l&&cur-l<=rr)getnum(l);
		else getnum(r);
	}
	assert(cur==0);
	assert(sz(siz)==n);
	reverse(all(siz));
	rep(i,n)
		cout<<cur<<" "<<cur+siz[i]<<"\n",cur+=siz[i];
	assert(cur==k);
}
```


---

## 作者：Eznibuil (赞：5)

模拟赛被队友痛批以后决定记录一下心得。免责声明：不保证算法能通过。

随便设定端点的初始状态，考虑朴素迭代。每轮迭代将每个端点设为两侧相邻端点的平均值，不合法则强行使其合法。发现算法收敛到正确答案很快，迭代 $10$ 次即可通过前 $18$ 个测试点。

但是第 $19$ 个点是非常专业的 Hack，即使跑 $3000$ 次迭代依然无法通过，稍作思考后发现迭代最多需要 $\Theta(n)$ 次，相当糟糕。

于是考场发明了“弹簧算法”，后来才知道是类似 K-means 一维版本的某种东西。

思想如下：观察到被 Hack 的原因是如果有一侧数非常大，需要花很久才能均摊到另一侧。那么能否同时推动另一侧所有端点呢？答案是可以的。

考虑弹簧，在两个相邻端点连一根弹簧，令所有弹簧原长为 $\frac ln$，没有任何限制下应该保持所有弹簧都是原长。考虑在所有端点上一个棍子，并在墙壁上钉上钉子以限制弹簧的端点。无疑，某些情况下棍子会被墙卡住，分摊掉弹簧施加的力。容易发现最后的稳定状态一定是连续的一段弹簧都是同一长度，且左右端卡死在钉子上。此时可以 $O(n^2)$ DP，但显然过不了。

回到迭代，每次弹簧会在两端点施加一个力，而力是可以传递的。不过注意钉子可以一下抵消所有的力。然后只需要扫描两遍，计算出每个端点左右施加的力，并将其移动一段距离即可。可以考虑如退火，移动距离与力的比越来越小；或是更真实一点，考虑速度与加速度，并使用物理公式计算。无论如何，都需要调整好参数。收敛速度，根据一些常识和经验性的估计，大概需要 $O(\sqrt n)$ 轮迭代。可以固定 $2000$ 次迭代，应当可以通过此题。（但是没试过。）

浅浅地放一个跑到了第 $18$ 个点的朴素迭代代码。
```cpp
#include<stdio.h>
int a[1000001],b[1000001],c[1000001];
int main()
{
	int l,n;
	scanf("%d%d",&l,&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int i=0;i<n-1;i++)
		b[i]=a[i]+a[i+1]>>1;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			c[j]=(j?b[j-1]:0)+(j<n-2?b[j+1]:l)>>1;
			if(c[j]<a[j])
				c[j]=a[j];
			else if(c[j]>a[j+1])
				c[j]=a[j+1];
		}
		for(int j=0;j<n-1;j++)
		{
			b[j]=(j?c[j-1]:0)+(j<n-2?c[j+1]:l)+1>>1;
			if(b[j]<a[j])
				b[j]=a[j];
			else if(b[j]>a[j+1])
				b[j]=a[j+1];
		}
	}
	for(int i=0;i<n;i++)
		printf("%d %d\n",i?b[i-1]:0,i<n-1?b[i]:l);
	return 0;
}
```

---

## 作者：toolong114514 (赞：1)

# 题面大意
注意只输出方案，不输出最小极差。
# 解题思路

先记数轴的最右侧点为 $a_{n+1}$。

## 简化问题为求值

不妨先考虑一个弱化的问题：只要求输出最小的线段长度极差，再构造题目要求的方案。

注意到答案具有单调性：在当前极差的限制下，有方案极差小于等于这个值，那么在更大的极差下也可以构造这样的方案。

我们考虑二分找到这样的极差中最小的一个，自然就是所求答案。

接下来考虑如何 check。

直接做不好实现，先进一步弱化 check 内容为钦定的最大最小长是否合法。

记最小长度为 $x$，最大长度为 $y$。

顺序遍历 $n$ 条线段及其限制，并记当前线段右端点的最左端为 $l$，最右端为 $r$。

对于当前线段要覆盖的点 $i$，我们考虑从上一条线段右端点的取值范围转移过来，判断是否包含 $i$。

上一段的右端点范围是 $[l,r]$，那么现在右端点的取值范围就是 $[l+x,r+y]$。

由于当前点在数轴上的坐标为 $a_i$，只需判断 $a_i\in[l+x,r+y]$ 是否成立即可。

当前右端点的真实值域并不是 $[l+x,r+y]$，因为可能存在一部分包含其它端点或不包含当前端点的的情况。

需要对 $l,r$ 做出如下修改：

$$l\gets \max(a_i,l+x)$$

$$r\gets \min(a_{i+1},r+y)$$

做完后，$[l,r]$ 就是当前线段真实的合法值域。

最后还需要判断最后线段的右端点是否可以成为数轴最右端。

我们接下来思考弱化的 check 与原来的 check 有什么联系。

称当前线段长度的取值区间 $[x,y]$ 小了，当且仅当弱化的 check 中，右端点范围转移时出现 $r+y<a_i$。

称当前线段长度的取值区间 $[x,y]$ 大了，当且仅当弱化的 check 中，右端点范围转移时出现 $l+x>a_i$。

用初中数学可以推出下列两个结论：

- 若一个区间 $[x,y]$ 小了，那么 $[x-1,y-1]$ 肯定也小了。

- 若一个区间 $[x,y]$ 大了，那么 $[x+1,y+1]$ 肯定也大了。

观察到了什么？单调性！

在钦定了极差的情况下，直接二分 $x$ 或 $y$，判断 $[x,y]$ 的大小，直到找出合法解，或者确认没有合法解即可。

综上所述，先二分极差，check 极差时再去二分长度取值区间，找是否有解即可。

二分范围是显然的。
## 根据最小值构造输出
记第 $i$ 条线段的右端点坐标为 $dis_i$，最小极差下最小长度为 $mn$，最大长度为 $mx$。

注意，此时的 $l$ 的含义与上文不同，但与原题意相同。
### 一种有问题的做法
观察到所有右端点的限制都可以大致表示为如下的差分约束：

$$\begin{cases}mn\le dis_i-dis_{i-1}\le mx\\a_i\le dis_-dis_0\le a_{i+1}\\dis_{i+1}\le dis_i\\dis_n=l\end{cases}$$

直接跑 SPFA 就行了。

实现后发现建的图可能产生负环，但实际上有解，而且建的图天然能卡 SPFA（菊花？）。

贴个[代码](https://codeforces.com/problemset/submission/1666/292736197)。

如果发现建图有误或者会实现负权 Dij（最近新出的科技，但是我的链接挂了），可以私信我。
### 贪心正解
易得 $dis_n=l$

首先顺着跑一遍，处理出最左的右边界。

$$dis_i=\max(dis_{i-1}+mn,a_i)$$

所有线段长显然满足 $mn\le dis_i$ 的限制。

然后倒着跑一遍，对于 $dis_i-dis_{i-1}>mx$ 的 $i$（长度过大），强制令 $dis_{i-1}=dis_i-mx$，此时等价于将第 $i-1$ 条线段延长，满足 $mx\le dis_i$ 的限制。

跑完后显然也满足 $dis_i\le mx$ 的限制，因为不合法的区间只会在第 $1$ 条线段出现，但是 $mx,mn$ 是合法的，所以没有。

第 $i$ 条线段的区间显然为 $[dis_{i-1},dis_i]$，直接输出即可。
## 参考代码
### [Code and Status](https://codeforces.com/problemset/submission/1666/292861502)

Writeen by [toolong114514](https://www.luogu.com/user/477821) on 2024/11/23.

---

