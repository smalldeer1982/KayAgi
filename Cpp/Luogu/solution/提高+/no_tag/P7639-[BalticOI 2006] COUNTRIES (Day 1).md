# [BalticOI 2006] COUNTRIES (Day 1)

## 题目背景

任何一个国家都是由弱小而拼搏斗争逐渐强大崛起的。

## 题目描述

考虑地区的二维地图，在这张地图上有 $n$ 个城市。每个城市 $i$ 在地图上都有一个独特的坐标（$x_i$,$y_i$）。每个城市在一个将军的指挥下有 $s_i$ 个士兵。  
城市 $i$ 对另一个位置（$x$,$y$）的威慑为 $s_i$ 除于它和（$x$,$y$）间距离的平方。这就好像城市 $i$ 中的大量士兵对它周围所有地图位置施加了威慑。如果城市 $j$ 对（$x_i$,$y_i$）的城市 $i$ 的威慑超过其士兵数 $s_i$：城市 $j$ 可以派遣足够的士兵前去制服保卫城市 $i$ 的士兵，那么城市 $i$ 就被城市 $j$ 所威胁。如果城市 $i$ 没有受到任何其他城市 $j$ 的威胁，那么心存感激的市民将选出其无敌的将军作为他们的国王，并将他们的城市变成他的王国的首都。  
另一方面，如果一些城市 $j$ 对（$x_i$,$y_i$）的城市 $i$ 的威胁比另一个城市 $k$ 对城市 $i$ 的威胁更具威慑，那么城市 $i$ 的居民别无选择：城市 $i$ 只能向城市 $j$ 投降。从今以后，城市 $i$ 必须服从城市 $j$ 所服从的首都；然而城市 $i$ 的士兵并没有加入城市 $j$ 或其首都的军队。除此之外，城市 $i$ 会因为 $j$ 和 $k$ 两个对它具有同等威胁的城市之间相互防备而得救：如果其中一个城市攻击并征服城市 $i$，那么另一个城市将会前来攻击并战胜先前刚战斗完而疲惫不堪的攻击方士兵。但这种情况下，城市 $i$ 的居民们将不再选举他们的将军为他们的国王，因为他未能履行他的职责保护城市免受威胁。因此，他们必须把他们的城市变成一个民主国家的首都。  
你的任务是编写一个程序，将地图上的城市信息作为输入，并为每个城市 $i$ 输出三种结果之一:  
- 它是一个王国的首都。  
- 它是一个民主国家的首都。  
- 它服从城市 $j$ 作为它的首都。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \le n \le 1000$，$0 \le x_i,y_i,s_i \le 1000$，$1 \le j \le n$。
#### 样例说明  
考虑以下地图，其中每个点代表一个城市，上面给出了它的士兵数量：  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/gmptiqan.png)  
也就是说，位置（$3$,$2$）上的城市 $3$ 是一个王国的首都，它还包括位置（$1$,$1$）上的城市 $4$ 和位置（$2$,$1$）上的城市 $5$。另一方面，位于位置（$2$,$5$）的城市 $1$ 自己形成了一个王国，而位于位置（$2$,$3$）的城市 $2$ 自己形成了一个民主国家。
#### 题目说明  
来源于 [Baltic Olympiad in Informatics 2006](https://www.cs.helsinki.fi/group/boi2006/) 的 [Day 1:Countries](https://www.cs.helsinki.fi/group/boi2006/tasks/countries.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
5
2 5 14
2 3 2
3 2 7
1 1 2
2 1 3```

### 输出

```
K
D
K
3
3```

# 题解

## 作者：Rigel (赞：19)

## 题意

在一个二维平面上有 $n$ 个城市。其中，城市 $i(i\in [1,n],i\in \mathbb{Z})$ 的坐标为 $(x_i,y_i)$，兵力为 $s_i$。

定义城市 $j$ 对城市 $i$ 的威胁值 $t=\displaystyle{\frac{s_j}{(x_i-x_j)^2+(y_i-y_j)^2}}$，若 $t>s_i$，则称城市 $i$ 被城市 $j$ 威胁 $(i \neq j)$。

一个城市的性质有以下三种可能：

1. 一个王国的首都。这个城市不受任何城市的威胁。

2. 一个民主国家的首都。这个城市受到多个城市的威胁，且有多个城市对这个城市的威胁值与这个城市所受最大威胁值相等。

3. 服从于另一个作为首都的城市。这个城市受到多个城市的威胁，且这些城市中**有且仅有**一个对它威胁值最大的城市 $id$，那么这个城市将服从于城市 $id$ 或城市 $id$ 所服从的首都。

请给出每一个城市的性质。

## 思路

对于每一个城市，枚举所有城市，找到所有能对其产生威胁的城市。记录这个城市所受最大威胁值 $mx$、产生最大威胁值的城市编号 $id$、产生最大威胁值的城市个数 $cnt$。

1. 当 $cnt=0$ 时，表示这个城市不受任何城市威胁，这个城市为王国的首都。

2. 当 $cnt=1$ 时，表示这个城市服从于城市 $id$（对它的威胁值为 $mx$）。当出现这种情况时，可使用并查集维护城市之间的服从关系。

3. 当 $cnt\geq 2$ 时，表示这个城市同时受多个威胁值为 $mx$ 的城市威胁，这个城市为民主国家的首都。

时间复杂度为 $\mathcal{O}(n^2)$，对于 $n\leq 10^3$ 可以实现。

## 代码实现

### 1. 城市信息存储

可以使用结构体存储。

```cpp
struct node{
	int x,y,s,fa,f;
}a[maxn];
```

其中，$x$，$y$ 分别表示城市的横纵坐标，$s$ 表示城市的兵力，$fa$ 表示这个城市服从的城市（若为自己则表示这个城市为首都）。若这个城市为首都，则 $f$ 存储这个首都的类型（$1$ 和 $2$ 分别代表王国的首都和民主国家的首都），否则为 $0$。

### 2. 城市对其他城市的威胁值计算

计算城市 $i$ 与城市 $j$ 的距离：

```cpp
double dis(int i,int j){
	return (double)((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
}
```

于是我们得到城市 $j$ 对城市 $i$ 的威胁值：

```cpp
t=(double)a[j].s/dis(i,j); // 城市 j 的兵力除以距离的平方
```

注意这里应该用 double 类型存储威胁值，因为它不一定是一个整数。

### 3. 城市性质的判断

当获得城市 $i$ 受到城市 $j$ 的威胁值 $t$ 之后，首先要判断 $t$ 与 $s_i$ 的关系。若 $t\leq s_i$，直接跳过城市 $j$；否则，应判断 $t$ 与城市 $i$ 所受的最大威胁值 $mx$ 是否相等。若相等，则最大威胁值个数 $cnt\gets cnt+1$；否则更新最大威胁值 $mx$、产生最大威胁值的城市编号 $id$、产生最大威胁值的城市个数 $cnt$（赋值为 $1$）。

由于威胁值用浮点数存储，会产生精度问题。我们需要加一个判断浮点数是否相等的函数。

```cpp
bool check(double x,double y){
	if(_abs(x-y)<=1e-10)return 1; // 若两个浮点数的误差小于一定值，则认为这两个浮点数是相等的
	return 0;
}
```

在得到 $mx$、$id$ 与 $cnt$ 之后，根据 $cnt$ 的值即可判断城市 $i$ 的性质。当 $cnt=1$ 时，应找到城市 $id$ 所服从的城市，并令城市 $i$ 也服从于这个城市。

```cpp
int getfa(int x){
	return (a[x].fa==x)?x:(a[x].fa=getfa(a[x].fa)); // 并查集
}
```

```cpp
for(int i=1;i<=n;i++){
	int id=0,cnt=0; // 产生最大威胁值的城市编号、产生最大威胁值的城市个数
	double mx=0; // 城市 i 所受最大威胁值
	for(int j=1;j<=n;j++){
		if(i==j)continue;
		double t=(double)a[j].s/dis(i,j); // 计算 j 对 i 的威胁值
		if(t<(double)a[i].s||check(t,(double)a[i].s))continue; // 若 t < a[i].s 或 t == a[i].s ，跳过
		if(t>mx&&!check(mx,t))mx=t,id=j,cnt=1; // 若 t > 当前城市 i 所受最大威胁值 mx ，则更新 mx 、 id 与 cnt
		else if(check(t,mx))cnt++; // 若 t == mx ，产生最大威胁值的城市个数加一
	}
	if(!cnt)a[i].f=1; // 城市 i 为王国的首都
	if(cnt>1)a[i].f=2; // 城市 i 为民主国家的首都
	if(cnt==1)a[i].fa=getfa(id); // 城市 i 服从于城市 id
}
```

在此之后，还需要进行：

```cpp
for(int i=1;i<=n;i++)getfa(i);
```

这样可以保证找到每个城市服从的首都。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define _abs(x) ((x)>0?(x):(-(x)))
#define maxn 1010
using namespace std;
int n;
struct node{
	int x,y,s,fa,f;
}a[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
double dis(int i,int j){
	return (double)((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
}
bool check(double x,double y){
	if(_abs(x-y)<=1e-10)return 1;
	return 0;
}
int getfa(int x){
	return (a[x].fa==x)?x:(a[x].fa=getfa(a[x].fa));
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].s=read(),a[i].fa=i;
	for(int i=1;i<=n;i++){
		int id=0,cnt=0;
		double mx=0;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			double t=(double)a[j].s/dis(i,j);
			if(t<(double)a[i].s||check(t,(double)a[i].s))continue;
			if(t>mx&&!check(mx,t))mx=t,id=j,cnt=1;
			else if(check(t,mx))cnt++;
		}
		if(!cnt)a[i].f=1;
		if(cnt>1)a[i].f=2;
		if(cnt==1)a[i].fa=getfa(id);
	}
	for(int i=1;i<=n;i++)getfa(i);
	for(int i=1;i<=n;i++){
		if(a[i].fa==i)printf("%c\n",(a[i].f==1)?'K':'D');
		else printf("%lld\n",a[i].fa);
	}
	return 0;
}
```

---

## 作者：vzcx_host (赞：2)

## 题意
$n$ 座城市，每座城市有一定数量的军队，强大的城市可以威胁弱小的城市，对于一座城市而言若存在**多个具有同样且最大的威胁力度**则他可以形成一个民主国家，求每座城市的类型。
### 详细的样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/gmptiqan.png)

上图中，$(2,5)$ 对 $(2,3)$ 产生的威胁力度为 $14\div(2^2+0^2)=3.5$，$(3,2)$ 对 $(2,3)$ 产生的威胁力度为 $7\div(1^2+1^2)=3.5$，没有点能对 $(2,3)$ 产生更大的威胁，所以 $(2,3)$  是民主国家。

$(2,5)$ 对 $(2,1)$ 产生的威胁力度为 $14\div(4^2+0^2)<1$，对 $(1,1)$ 产生的威胁力度为 $14\div(4^2+1^2)<1$，所以 $(2,5)$ 无法控制 $(2,1)$ 和 $(1,1)$。

$(3,2)$ 对 $(2,1)$ 产生的威胁力度为 $7\div(1^2+1^2)=3.5$，对  $(1,1)$ 产生的威胁力度为 $7\div(1^2+2^2)=1.4$，所以 $(3,2)$ 控制 $(2,1)$，但不控制 $(1,1)$。

$(2,1)$ 对 $(1,1)$ 产生的威胁力度为 $3\div(0^2+1^2)=3$，所以 $(2,1)$ 控制 $(1,1)$，但 $(2,1)$ 被 $(3,2)$ 控制，所以即使 $(3,2)$ 没有控制 $(1,1)$，但 $(1,1)$ 仍然尊 $(3,2)$ 为首都。
## 题解
对~~让人难以理解的题面~~分析可得，数量少的士兵不可能控制数量多的士兵，因此可以将所有城市按照士兵数量从大到小排序，依次判断每座城市的类型。在考虑一座城市 $i$ 时，他可能会对后面的城市 $j$ 产生威胁，记录下城市 $j$ 与对他威胁最大的城市与威胁力度即可。

没有城市控制 $i$ 时 $i$ 为王国首都，$i$ 的最具力度控制者为 $j$ 时 $i$ 尊 $j$ 所认定的首都为首都，$i$ 的最具力度控制者不唯一时 $i$ 为民主国家的首都。

~~此题难点不在思路与代码，在于能否读懂题目（大雾）。~~
## Code
```
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(i!=j&&nu[i]>1ll*nu[j]*((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])))
			kz[i][j]=(long double)nu[i]/((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])),
			bn[j]++;
for(int i=1;i<=n;i++)a[i]=fc[i]=i;
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
	int v=a[i];
	for(int j=1;j<=n;j++)
		if(kz[v][j]>0)
			if(kz[v][j]>kzl[j])
				fc[j]=abs(fc[v]),kzl[j]=kz[v][j];
			else if(kz[v][j]==kzl[j]))
				fc[j]=-j;
}
for(int i=1;i<=n;i++)
	if(fc[i]==i)puts("K");
	else if(fc[i]==-i)puts("D");
	else printf("%d\n",fc[i]);
```

---

## 作者：Mine_King (赞：1)

## Problem

[洛谷 P7639 [BalticOI 2006 Day 1] COUNTRIES](https://www.luogu.com.cn/problem/P7639)

**题目大意：**

在一张网格上，给你 $n$ 个城市的坐标和兵力， 若有城市 $i,j$ 满足 $\dfrac{s_i}{(x_i-x_j)^2+(y_i-y_j)^2}>s_j$，则视为 $i$ 能控制 $j$。一个城市只会被对其威慑度最高的城市控制。若有一个城市不被任何城市控制，则这是一个国家的首都。若一个城市被另一个城市控制，则这个城市的首都为控制其的城市的首都。若一个城市同时被多个城市控制（这些城市对他的威慑度相同），则这是一个自由城市，**自由城市可以威慑其他城市并成为他们的首都**。

给定城市的信息，求每个城市的状态，即首都（输出 `K`），被控制的城市（输出其首都编号）或自由城市（输出 `D`）。

## Solution

首先观察题意可以发现，一个城市只会被 $s$ 比它大的城市控制，所以我们可以将城市按 $s$ 进行排序。观察数据范围发现 $n \le 1000$，可以想到用 $O(n^2)$ 算法。所以我们可以对于每个城市 $i$，逐个枚举他前面的城市 $j$ 并分情况讨论：

- $s_j=s_i$：此时后面的城市都不可能对 $i$ 造成威慑，直接结束。
- $i$ 未被威慑：
  - $j$ 能威慑 $i$：$i$ 被 $j$ 威慑。

- $i$ 被威慑：
  - $j$ 对 $i$ 的威慑度比先前的威慑度更大：$i$ 被 $j$ 威慑。
  - $j$ 对 $i$ 的威慑度和先前一样：$i$ 变为自由城市并保持先前的威慑度不变。


我们还有一个问题：如何处理威慑操作？  
其实只要开一个数组存一下每个城市的首都，威慑操作就变成了简单的赋值。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,ans[1005];//ans记录城市的首都，自由城市视作首都为0
struct city
{
	int x,y,s,id;
}a[1005];
bool cmp(city _x,city _y){return _x.s>_y.s;}
int dis(int _x,int _y)
{return (a[_x].x-a[_y].x)*(a[_x].x-a[_y].x)+(a[_x].y-a[_y].y)*(a[_x].y-a[_y].y);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].s),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		int wdis=6e6,ws=0;//记录威慑他的城市的距离和s，因为可能会有精度损失，所以用十字相乘法比较
		ans[a[i].id]=a[i].id;
		for(int j=1;j<i;j++)
			if(a[j].s==a[i].s) break;
			else if(ans[a[i].id]==a[i].id)
			{
				if(a[j].s>a[i].s*dis(j,i))
					ans[a[i].id]=ans[a[j].id],wdis=dis(j,i),ws=a[j].s;
			}
			else
			{
				if(a[j].s*wdis>ws*dis(j,i))
					ans[a[i].id]=ans[a[j].id],wdis=dis(j,i),ws=a[j].s;
				else if(a[j].s*wdis==ws*dis(j,i))
					ans[a[i].id]=0;
			}
	}
	for(int i=1;i<=n;i++)
		if(ans[i]==i) puts("K");
		else if(ans[i]==0) puts("D");
		else printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：TLE_AK (赞：0)

### 题意
一个二维平面内有 $n$ 个点，每个点都有一个兵力 $s_i$。对于一个点对 $(i,j)$，其威胁值为 $v_{ij}=\frac{s_i}{(x_i-x_j)^2+(y_i-y_j)^2}$，若 $v_{ij}>s_j$，则 $i$ 对 $j$ 产生了威胁。  
对于每个点 $i$，有 $3$ 种状态：  
1. 不受所有点威胁，为一个国家的首都。
2. 受多个威胁值相等且最大的城市威胁，为一个民主国家首都。
3. 受一个威胁值最大的点的影响，其首都为最大点的首都。
## 思路
由于可以暴力枚举，所以考虑将所有点的威胁值求出，随后便可以算出为首都的点。  
可以发现，一个点 $a$ 若受 $b$ 威胁，则 $a$ 一定不受 $b$ 威胁（因为 $v_{ij}>s_j$，$v_{ji}<s_j$，$v_{ij}<s_i$，所以 $s_i>v_{ji}$）。  
考虑用并查集维护每个点的首都，每次询问直接查找即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	int bcj[1010],ans[1010];
	double maxn[1010][4];
	struct node
	{
		double x,y,s;	
	}A[1010]; 
	
	int belong(int x)
	{
		if(bcj[x]!=x)return bcj[x]=belong(bcj[x]);
		return x;
	}

	int main()
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			bcj[i]=i;	
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf",&A[i].x,&A[i].y,&A[i].s);
		}
		for(int i=1;i<=n;i++)//枚举威胁值
		{
			for(int j=1;j<=n;j++)
			{
				if(i==j)continue;
				double ws=A[j].s/((A[i].x-A[j].x)*(A[i].x-A[j].x)+(A[i].y-A[j].y)*(A[i].y-A[j].y));
				if(ws<=A[i].s)continue;
				if(ws-maxn[i][0]>1e-6)//注意精度问题
				{
					maxn[i][0]=ws;//民主首都
					maxn[i][1]=j;
				}
				else if(ws-maxn[i][0]>=0)maxn[i][1]=-1;//首都
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!maxn[i][0]||maxn[i][1]==-1)continue;//首都
			int al=belong(i),bl=belong((int)maxn[i][1]);
			bcj[al]=bl;
		}
		for(int i=1;i<=n;i++)
		{
			if(!maxn[i][0])cout<<"K\n";
			else if(maxn[i][1]==-1)cout<<"D\n";
			else cout<<belong(i)<<'\n';
		}
		return 0;
	}
}

int main()
{
	acac::main();
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：有 $n$ 个城市，若一个城市的军队数除以它与另一城市的距离的平方大于另一城市的军队数，则其会对后者施加等同于前一值的影响。求每座城市的受影响状况。

核心思想：暴力枚举

解：

首先用距离公式 $|x|=\sqrt{\Delta x^2+\Delta y^2}$ 求出城市之间两两距离的平方，然后对于每座城市比较受影响的状况：若所有影响都小于本城军队数输出 $K$ ，若有一座影响最大的城市输出该城市的首都，若有多座影响最大的城市输出 $D$ 。

注意预处理时要把城市当前状况赋值成该城本身，并且要按军队数从大到小排序并倒序计算状况（否则会出现输出首都不是最终首都的状况）。

代码：
```
#include <bits/stdc++.h>
using namespace std;
struct city
{
	long long x, y, s, c, n;
}a[1001];//城市信息：坐标，兵力，状况，编号
long long n, temp, d[1001][1001], mx[1001];
bool cmp1(city x, city y)
{
	return x.s<y.s;
}//按兵力排序，方便计算
bool cmp2(city x, city y)
{
	return x.n<y.n;
}//按编号排序，方便输出
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].s;
		a[i].n=i;
		a[i].c=i;
	}
	sort(a+1, a+n+1, cmp1);//预处理
	for(int i=n-1; i>=1; i--)
		for(int j=i+1; j<=n; j++)
			d[i][j]=(a[j].x-a[i].x)*(a[j].x-a[i].x)+(a[j].y-a[i].y)*(a[j].y-a[i].y);//距离计算
	for(int i=n-1; i>=1; i--)
		for(int j=i+1; j<=n; j++)
			if(a[i].c==a[i].n && a[i].s*d[i][j]<a[j].s)
			{
				a[i].c=a[j].c;
				mx[i]=j;
			}
			else if(a[i].c!=a[i].n && a[mx[i]].s*d[i][j]<a[j].s*d[i][mx[i]])
			{
				a[i].c=a[j].c;
				mx[i]=j;
			}
			else if(a[i].c!=a[i].n && a[mx[i]].s*d[i][j]==a[j].s*d[i][mx[i]])
				a[i].c=0;//分类讨论状况
	sort(a+1, a+n+1, cmp2);
	for(int i=1; i<=n; i++)
		if(a[i].c==0)
			cout<<"D"<<endl;
		else if(a[i].c==i)
			cout<<"K"<<endl;
		else
			cout<<a[i].c<<endl;//输出
	return 0;
}
```

---

