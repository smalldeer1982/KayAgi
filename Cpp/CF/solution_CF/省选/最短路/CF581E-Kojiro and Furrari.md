# Kojiro and Furrari

## 题目描述

汽车司机 Kojiro 花了 $10$ 年时间为他最喜欢的汽车品牌法拉利攒钱。终于，Kojiro 的梦想实现了！现在 Kojiro 想去找他的女友 Johanna，向她炫耀他的汽车。

Kojiro 希望赶到他女朋友那里，所以他将沿着一条坐标轴前往。为了方便起见，我们假设 Kojiro 在坐标线上的点 $f$ 处，而 Johanna 在点 $e$ 处。坐标轴上的一些点设有加油站。每个加油站只提供一种类型的燃料：$92$ 号汽油，$95$ 号汽油或 $98$ 号汽油。因此，每个加油站由一对整数 $t_i$ 和 $x_i$ 来描述，$t_i$ 表示燃料类型的编号，$x_i$ 表示加油站的位置。

一升燃料正好可以行驶 $1$ 千米（这个值与燃料类型无关）。三种类型的燃料仅在质量上有所不同，据研究表明，这影响发动机的寿命。一辆法拉利的油箱容量恰好为 $s$ 升（不管燃料类型如何）。在小次郎从点 $f$ 出发时，他的油箱已经完全装满了 $98$ 号汽油。在每个加油站，小次郎可以加满油箱，但当然，油箱中的燃油量在任何时间点都不能超过 $s$ 升。注意，油箱可以同时装有不同类型的燃料。汽车可以向左或向右两个方向移动。

为了延长发动机的使用寿命，Kijiro 主要希望最大限度地减少 $92$ 号汽油的使用量。如果有多种从点 $f$ 到点 $e$ 的方案使用最少量的 $92$ 号汽油，那么需要选择最小化使用 $95$ 号汽油的量的方案。

请编写一个程序，可以对于起始位置 $f_i$ 的 $m$ 个可能位置，首先最小化使用的 $92$ 号汽油的量，其次最小化使用的 $95$ 号汽油的量。

### **简明题意**

对于在坐标轴上的 $m$ 个起点和一个终点，请找出每个起点在所有到终点的方案中，最小化 $92$ 号汽油，其次 $95$ 号汽油的方案。

## 样例 #1

### 输入

```
8 4 1 1
2 4
0
```

### 输出

```
0 4
```

## 样例 #2

### 输入

```
9 3 2 3
2 3
1 6
-1 0 1
```

### 输出

```
-1 -1
3 3
3 2
```

## 样例 #3

### 输入

```
20 9 2 4
1 5
2 10
-1 0 1 2
```

### 输出

```
-1 -1
-1 -1
-1 -1
-1 -1
```

# 题解

## 作者：猪脑子 (赞：2)

我们假设出发点都在终点左边，不难发现在右边的时候也是一样的。

我们从右往左依次考虑每个加油站，在每个加油站的位置构造从当前加油站开始，到达终点的最优方案。

假设我们已经构造出当前加油站的下一个加油站的方案，那么我们就分两种情况考虑：

如果下一个加油站的油质量更高，那么我们只需要加上从当前加油站到达下个加油站所需的油就可以了，因为如果多加了油还不如到达下个加油站的时候加上更好的油。

如果下一个加油站的油质量更低，那么我们除了加上到下一个加油站所需要的油以外，还应当多加一些油，来代替下一个加油站加上的油。假如这个加油站到下一个加油站的距离为$d$km，我们在下一个加油站加入了$c$升的油，那么如果$s<d+c$，说明我们应当在这个加油站加满，然后下一个加油站加入的油就得减少$s-d$。否则，我们会发现，下一个加油站是没有用处的，因为它的油完全可以用当前加油站的油代替，遇到这种情况我们再考虑下一个加油站就可以了。

那么如果下一个加油站的油跟当前加油站的油一样呢？这种情况下，我们可以把下一个加油站的油当做质量更低的，这样对答案并不会有什么影响。

至于实现，我的处理方法是这样的：如果要把一个加油站加的油“退回去”，相当于把加油站的位置向右移动一段距离，使得我们每个加油站加的油都刚好等于这个加油站到下一个加油站的距离。

至于怎么回答每个询问，我们把询问跟加油站放在一起排序。每个询问也都相当于加油站，只是不会对其他询问产生影响。这样我们只需要按照跟上面加油站处理方式一样的方式处理就可以了，代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
//奇怪的名称增加了（
struct Madoka{
	int x,t;
}s[400010];
bool cmp(Madoka a,Madoka b)
{
	return a.x<b.x;
}
int S,N;
bool ok;
int pos[200010];
int tp[200010];
int cnt[4];
void init()
{
	N=1;
	pos[1]=0;
	tp[1]=4;
	ok=true;
}
//加入一个加油站
void insert(int x,int t)
{
	//距离太远
	if(x-pos[N]>S){
		ok=false;
		return ;
	}
	//跳过一些没用的加油站
	while(tp[N]<=t&&x-pos[N-1]<=S)
	{
		cnt[tp[N]]-=pos[N]-pos[N-1];//cnt存储每种汽油加了多少
		N--;
	}
	if(tp[N]<=t){//下一个加油站油的质量更差
		int tpos=x-S;
		cnt[tp[N]]-=pos[N]-tpos;
		pos[N]=tpos;//修改加油站的位置，不难发现这跟退掉一部分油是等价的
		cnt[t]+=S;
	}
	else cnt[t]+=x-pos[N];//下一个加油站油的质量更好，此时只需要加上对应距离所需要的油就好了。
	N++;
	pos[N]=x;
	tp[N]=t;
	return ;
}
//跟插入是一样的过程，但是不产生影响
int tcnt[4];
pair<int,int> virt_insert(int x,int t)
{
	if(x-pos[N]>S){
		ok=false;
		return make_pair(0,0);
	}
	int tN=N;
	for(int i=0;i<4;i++)tcnt[i]=cnt[i];
	while(tp[tN]<=t&&x-pos[tN-1]<=S)
	{
		tcnt[tp[tN]]-=pos[tN]-pos[tN-1];
		tN--;
	}
	if(tp[tN]<=t){
		int tpos=x-S;
		tcnt[tp[tN]]-=pos[tN]-tpos;
		tcnt[t]+=S;
	}
	else tcnt[t]+=x-pos[tN];
	return make_pair(tcnt[1],tcnt[2]);
}
int ansx[200010],ansy[200010];
int main()
{
	int e,n,m;
	scanf("%d %d %d %d",&e,&S,&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&s[i].t,&s[i].x);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&s[n+i].x);
		s[n+i].t=-i;
	}
	sort(s+1,s+n+m+1,cmp);
	int E=0;
	for(int i=1;i<=n+m;i++)
		if(s[i].x<=e)E=i;
	init();
	for(int i=E;i>=1;i--)
		if(s[i].t>0)insert(e-s[i].x,s[i].t);
		else{
			pair<int,int>res=virt_insert(e-s[i].x,3);
			if(!ok)ansx[-s[i].t]=ansy[-s[i].t]=-1;
			else ansx[-s[i].t]=res.first,ansy[-s[i].t]=res.second;
		}
	init();
	for(int i=E+1;i<=n+m;i++)
		if(s[i].t>0)insert(s[i].x-e,s[i].t);
		else{
			pair<int,int>res=virt_insert(s[i].x-e,3);
			if(!ok)ansx[-s[i].t]=ansy[-s[i].t]=-1;
			else ansx[-s[i].t]=res.first,ansy[-s[i].t]=res.second;
		}
	for(int i=1;i<=m;i++)
		printf("%d %d\n",ansx[i],ansy[i]);
	return 0;
}
```
最后一个问题：复杂度为什么是对的？

对于insert()，复杂度显然是线性的，因为每个加油站最多会被加入/删除一次。而virt_insert()呢？这玩意复杂度显然不是均摊的，因为不会产生影响。其实，这玩意每次最多只会修改到3个加油站（思考一下？），所以总复杂度（不考虑排序）依然是线性的。

---

## 作者：SegTree (赞：0)

怎么可以转置算法进行倒退啊，属实没有想到。

提供一个不算二分位置也要 $O(m\log n)$ 的唐龙做法。

如果查询允许 $O(n)$ 的复杂度则模拟即可。具体而言求出 $nxt_i$ 表示下个非 $92$ 汽油的位置。则如果是 $92$ 号汽油，记 $L=x_{i+1}-x_i$，如果当前油量 $S<L$ 则必须用 $L-S$ 量的汽油；如果是 $95$ 号汽油，记 $L=\min(x_{nxt_i}-x_i,s)$，若 $S<L$ 则用 $L-S$ 量的汽油（因为能不用 $92$ 就不用 $92$）；否则加满。

不难发现离线后可以扫描线使用平衡树模拟维护，做到 $O(m\log n)$ 的复杂度。

<https://codeforces.com/problemset/submission/581/321007212>。

---

## 作者：high_sky (赞：0)

# 思路

## 获取思路（这里用原题的翻译）

由于起点是不固定的，我们可以想到：从 $e$ 点开始走，走到起点，一旦预处理完，接下来只是输出问题。

我们考虑 `贪心`，对于一个点，**它们最优的情况就是走到一个油的编号大于等于它的加油站**。

就算不能走到一个编号大于等于它的加油站，要**尽量加满油**。

$f_{0/1/2,i}$ 表示总第 $i$ 个点开始，可用 `92、95、98`，`95、98`，`98` 时，需要用**不符合条件的油的最小数量**。

然后需要使用的 $92$ 号汽油的数量就是 `get(1,side)`，需要使用的 $95$ 号汽油就是，`get(2,side)-get(1,side)` 可以直接用 $f$ 二分求解。

## 部分代码讲解

根据上述思路，我们不难想出把**同一个类型的加油站（指油的编号相同的）放在一个数组里面**，由于所设的 $f_{0/1/2,i}$ 中的 $j$ 表示的编号里面都有加上 `98` 的油，为了最后到达 $e$ 点，我们特殊地认为 $e$ 点是一个 `98` 类型的加油站。当然，那些比 $e$ 还要大的加油站不要。

根据以上思路就有一下代码：

```cpp
for (int i = 1;i <= n;i ++) {
	int t,x;
    cin >> t >> x;
    if (x >= e) continue;
    for (int j = 0;j < t;j ++) d[j].push_back(x);// d 数组即为上述存加油站的数组
}
```

然后如何贪心转移呢？其实可以这么想：设 $i$ 为油的类型，$j$ 为第几个点（这种类型的油站），那么有：
$$
f_{i,j}=f_{i,j+1}+\max\{d_{i,j+1}-d_{i,j}-s,0\}
$$
解释一下，因为是从 $e$ 点往 $f$ 点推，所以说，我当前的情况就变成了**上一个的情况 $+$ 到这里需要的油**

为什么要 $-s$ 呢？理由如下：

当前的 $i$ 所取的加油站的油的类型都是 $\ge i$（即质量不下于他的油），但是在前往 $j+1$ 的点时，其中会有比他差的油站，我们可以此时油站加满，走到尽头的一个油站（质量比他差的），然后再间接走到我的目标点，此时的不符合条件的就为：$d_{i,j+1}-d_{i,j}-s$。

代码就有以下：
```cpp
for (int i = 0;i < 3;i ++) {
    d[i].push_back(e);
    sort(d[i].begin(),d[i].end());
    for (int j = d[i].size() - 2;j >= 0;j --) f[i][j] = f[i][j + 1] + max(d[i][j + 1] - d[i][j] - s, 0);
}
```

如何求答案？

我们可以利用二分求出 $\ge f_i$（这里的 $f_i$ 是题目所给）的加油站，再求出其右边加油站的编号即可用 `贪心转移公式` 解决：

```cpp
int get(int ord,int side){
	int now = lower_bound(d[ord].begin(),d[ord].end(),side) - d[ord].begin();
	return f[ord][now] + max(d[ord][now] - side - s, 0);
}
```

其中 `ord = 0` 时，返回值必须为 $0$，否则就是走不到。

我们也可以同理可得求出需要 `92,95` 的油的数量，即上 `获取思路` 的末篇。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector> 
//#define int long long
using namespace std;
vector<int>d[5];
int e,s,n,m;
long long f[5][200005];
int get(int ord,int side){
	int now = lower_bound(d[ord].begin(),d[ord].end(),side) - d[ord].begin();
	return f[ord][now] + max(d[ord][now] - side - s, 0);
}
signed main(){
	scanf("%d%d%d%d",&e,&s,&n,&m);
	for(int i = 1, t, x;i <= n;i ++){
		scanf("%d%d",&t,&x);
		if(x >= e)continue;
		for(int j = 0;j < t;j ++)d[j].push_back(x);
    }
	for(int i = 0;i < 3;i ++){
		d[i].push_back(e);
		sort(d[i].begin(),d[i].end());
		for(int j = d[i].size()-2;j >= 0;j --)
			f[i][j]=f[i][j + 1] + max(d[i][j+1] - d[i][j] - s,0);
    }
    for(int i = 1;i <= m;i ++){
    	int side;
    	scanf("%d",&side);
    	if(get(0,side))puts("-1 -1");
    	else printf("%d %d\n",get(1,side),get(2,side) - get(1,side));
    }
    return 0;
}
```


---

