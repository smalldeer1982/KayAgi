# 『MdOI R4』Balance

## 题目背景

可怜的 $\rm\textcolor {grey}{JohnVictor}$ 玩的卡组在平衡性调整中被削弱了，现在他掉了很多杯，他想知道什么样的一个世界才是真正平衡的。

于是就有了这题。

## 题目描述

给定长度为 $n$ 的，由整数构成的数组 $a,b,p,q$，并定义函数 $f(i,j)=\dfrac{a_i+b_j}{p_i+q_j}(1\le i,j\le n)$。

再给定两个整数 $x,y$，你需要求出一对 $(i,j)$，使得 $f(i,j)$ 在所有 $f(i,t)(t=1,2,\cdots,n)$ 中是第 $x$ 小的，在所有 $f(s,j)(s=1,2,\cdots,n)$ 中是第 $y$ 小的。 

在本题中，我们称一个数 $x$ 在序列 $c_{1\ldots n}$ 中是第 $k$ 小的，当且仅当在 $c$ 中有且仅有 $\alpha$ 个数 $y$ 满足 $y<x$，且有且仅有 $\beta$ 个数 $y$ 满足 $y\le x$，同时 $\alpha<k\le \beta$。

如果不存在这样的 $(i,j)$，请输出 `0 0`。

如果有多组这样的 $(i,j)$，输出任意一组即可。

由于平衡性的问题不是一次就能问清楚的，所以出题人会问你多次。

## 说明/提示

【样例解释 #1】
- $f(1,1)=1.2;f(1,2)=1.2;f(1,3)=1.25$。
- $f(2,1)=2;f(2,2)=2;f(2,3)=2\frac{1}{6}$。
- $f(3,1)=1;f(3,2)=1;f(3,3)=1$。

$f(1,3)$ 在 $f(1,1),f(1,2),f(1,3)$ 中是第 $3$ 小的，$f(1,3)$ 在 $f(1,3),f(2,3),f(3,3)$ 中是第 $2$ 小的。

【数据规模与约定】

**本题采用捆绑测试**

| 子任务编号 | $\sum n\le$         | $\vert a_i\vert ,\vert b_i\vert ,p_i,q_i\le$ | $(x,y)= $  | 分值  |
| ---------- | -------------- | -------------------- | ---------- | ----- |
| $1$        | $5\times 10^3$ | 无特殊限制           | 无特殊限制 | $10$  |
| $2$        | 无特殊限制     | $3$                  | 无特殊限制 | $10$  |
| $3$        | $10^5$         | 无特殊限制           | $(1,n)$        | $30 $ |
| $4$        | $10^5$         | 无特殊限制           | 无特殊限制 | $20$  |
| $5$        | 无特殊限制     | 无特殊限制           | 无特殊限制 | $30$  |

对于 $100\%$ 的数据，$1 \le x,y \le n \le 5 \times 10^5$，$\sum n \le 5 \times 10^5$，$|a_i|,|b_i|\le 10^9$，$0<p_i,q_i\le 10^9$，其中 $\sum n $ 表示所有数据中 $n$ 的和。

【提示与帮助】

本题读入量较大，请选手选择较快的读入方式。

## 样例 #1

### 输入

```
1
3 3 2
2 4 1 4
10 4 3 4
1 3 1 3
```

### 输出

```
1 3
```

# 题解

## 作者：JohnVictor (赞：7)

$n^2$ 的暴力不说了。

根据计算几何能够想到一个乱搞，但是他经过一天的努力被卡掉了。

先考虑这样一个问题：如何刻画所有 $f(i,j)\ge z$ 的 $(i,j)$。

分数规划后，令 $x_i=a_i-zp_i,y_i=b_i-zq_i$，那么刻画的就是所有 $x_i+y_j\ge 0$ 的 $(i,j)$。

如果 $x,y$ 数组经过了排序，并且在 $n\times n$ 的方格表中染黑那些 $f(i,j)\ge z$ 的 $(i,j)$，那么黑色的格子和白色的格子被一条路径分割。

现在，将 $z$ 从 $\infty$ 连续变化到 $-\infty$，始终保持 $x,y$ 数组是排好序的，如果有反超的情况直接交换这两列（行），反超的那一刻那两列（行）是完全一样的。

那么会发现方格表中依次有格子被染黑，并且黑白格子被一条路径分割的事实始终保持着。

我们找到格子 $(u,v)$ 第一次被染黑的时刻，那么它对应的 $f$ 值是一行中第 $u$ 大的，一列中第 $v$ 大的。

这时候证明了这样的数对一定存在。

要找到这个数对当然不用维护整个过程，二分 $z$，直接判断对应的 $(u,v)$ 是否非负，同时不会有任何精度问题。

使用 `nth_element` 就能做到 $O(nw)$ 的复杂度。
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct node{int pl;int a,p;long double curr;}x[500010],y[500010];
bool cmp(node x,node y){return x.curr<y.curr;}
int n,s,t;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	int T;cin>>T;while(T--){
	cin>>n>>t>>s;rep(i,1,n)cin>>x[i].a>>y[i].a>>x[i].p>>y[i].p,x[i].pl=y[i].pl=i;
	long double l=-2e7,r=2e7,mid=0;
	rep(i,1,50){
		mid=(l+r)/2;
		rep(i,1,n)x[i].curr=1.0*x[i].a-mid*x[i].p,y[i].curr=1.0*y[i].a-mid*y[i].p;
		nth_element(x+1,x+s,x+n+1,cmp),nth_element(y+1,y+t,y+n+1,cmp);
		if(x[s].curr+y[t].curr>0)l=mid;else r=mid;
	}
	cout<<x[s].pl<<" "<<y[t].pl<<endl;}
}

---

## 作者：双管荧光灯 (赞：6)

我们发现这个分式很像一个斜率，但是后面是正号，而斜率是 $\frac{y1-y2}{x1-x2}$ ，因此我们对b和q数组取它们的相反数，我们就得到了 $2n$ 个点。

我们把一半染红，坐标 $(p_i,a_i)$ ，另一半我们染蓝， 坐标 $(-q_i,-b_i)$ ，$(i,j)$ 的值就可以被描述为红点 $i$ 和 蓝点 $j$ 之间的斜率了。而 $(i,j)$ 的排名可以根据 $(i,j)$ 这条直线上方的蓝点数，与这条直线下方的红点数算出。

于是我们找这条直线即可，我们设其截距为 $z$ ，如果我们知道截距，那么就能找到逆时针方向第 $y$ 个红点，它一定是这条直线上的点，于是这条直线就确定下来了。我们发现 $(0,z)$ 与第 $y$ 个红点的连线上方的蓝点数随着 $z$ 的增大是单调不升的。于是我们可以二分 $z$ 进行判断。

找第 $y$ 个红点可以使用 nth_element ，这样复杂度就是 $O(n\log(eps^{-1}))$ 。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1000005,M=998244353,E=262144;
#define __float128 long double
__float128 eps=0.000000002;
int r,i,n,ans,p,j,k,f[N],x,y,t;
__float128 C;
struct str{
	int x,y,id;
}a[N],b[N];
bool flag;
bool cmp(str a,str b)
{
	return a.x*(b.y-C)-(a.y-C)*b.x>0;
}
__float128 Fabs(__float128 M)
{
	return M<0?-M:M;
}
int check(__float128 m)
{
	C=m;
	nth_element(a+1,a+y,a+1+n,cmp);
	int s1=0,s2=0;
	for(i=1;i<=n;++i)
		if(Fabs(a[y].x*(b[i].y-C)-(a[y].y-C)*b[i].x)/max(a[i].x,a[i].y)<eps)
			++s2;
		else
			if(a[y].x*(b[i].y-C)-(a[y].y-C)*b[i].x>0)
				++s1;
	if(s1<x&&s1+s2>=x)
	{
		flag=true;
		for(i=1;i<=n;++i)
			if(Fabs(a[y].x*(b[i].y-C)-(a[y].y-C)*b[i].x)/max(a[i].x,a[i].y)<eps)
			{
				printf("%d %d\n",a[y].id,i);
				break;
			}
	}
	return s1;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&n,&x,&y);
		for(i=1;i<=n;++i)
		{
			scanf("%d %d %d %d",&a[i].y,&b[i].y,&a[i].x,&b[i].x);
			b[i].x=-b[i].x,b[i].y=-b[i].y;
			a[i].id=i,b[i].id=i;
		}
		flag=false;
		__float128 l=-1000000000,r=1000000000;
		while(r-l>0.0000000002)
		{
			__float128 mid=(l+r)/2;
			if(check(mid)<x)
				r=mid;
			else
				l=mid;
			if(flag)
				break;
		}
		if(!flag)
			puts("0 0");
	}
}

```

---

## 作者：VinstaG173 (赞：3)

作为验题人感觉这是一道思路非常妙的题。JV yyds！orzorz

首先这样的形式容易想到维护分数值来将 $i,j$ 独立出来。于是我们想到维护值 $z$，通过 $a_i-zp_i$ 与 $b_j-zq_j$ 之和的符号来刻画分数值与 $z$ 的大小关系。容易发现在 $z$ 连续变化的过程中 $a_i-zp_i$ 和 $b_j-zq_j$ 都是连续变化的。所以我们将它们分别从小到大排序按行列列表，每个位置记录对固定的 $z$ 其值是否非负。每一维的排序分别是在相邻两项之间进行变换的。因此一定有一个临界点使 $x,y$ 恰好非负，那么我们二分找到这个时刻，显然当前的 $x,y$ 对应回输入的编号就是答案。

同时这题解是一定存在的，所以 `0 0` 骗不到分（

Code:
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using std::nth_element;
int t,n,x,y,u,v;
long double l,r,m;
struct node
{
	int a,p,id;
	long double vl;
}tx[500003],ty[500003];
inline bool cmp(node xx,node yy)
{
	return xx.vl<yy.vl;
}
int main()
{
    scanf(" %d",&t);
    while(t--)
    {
    	scanf(" %d %d %d",&n,&y,&x);l=-1e14;r=1e14;u=v=0;
    	for(int i=1;i<=n;++i)scanf(" %d %d %d %d",&tx[i].a,&ty[i].a,&tx[i].p,&ty[i].p),tx[i].id=ty[i].id=i;
    	while(r-l>1e-14)
    	{
    		m=(l+r)/2;
    		for(int i=1;i<=n;++i)tx[i].vl=tx[i].a-tx[i].p*m,ty[i].vl=ty[i].a-ty[i].p*m;
    		nth_element(tx+1,tx+x,tx+n+1,cmp);
    		nth_element(ty+1,ty+y,ty+n+1,cmp);
    		if(tx[x].vl+ty[y].vl>=0)l=m,u=tx[x].id,v=ty[y].id;
    		else r=m;
    	}
    	printf("%d %d\n",u,v);
    }
	return 0;
}
```

---

