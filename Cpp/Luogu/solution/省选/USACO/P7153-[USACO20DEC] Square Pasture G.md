# [USACO20DEC] Square Pasture G

## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤200$）。

Farmer John 想要建造一个可以包围一块正方形区域的栅栏；这个正方形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 

## 说明/提示

 - 测试点 1-5 中，所有奶牛所在的方格的坐标均小于 20 。
 - 测试点 6-10 中，$N≤20$。
 - 测试点 11-20 没有额外限制。

供题：Benjamin Qi 


## 样例 #1

### 输入

```
4
0 2
2 3
3 1
1 0
```

### 输出

```
14```

## 样例 #2

### 输入

```
16
17 4
16 13
0 15
1 19
7 11
3 17
6 16
18 9
15 6
11 7
10 8
2 1
12 0
5 18
14 5
13 2```

### 输出

```
420```

# 题解

## 作者：__gcd (赞：11)

标签：平面坐标+双指针

~~思考+调试总共耗时7h，写篇题解纪念一下。~~

### 基本思路

* 第一种情况，空集或者只包含一个点。

显然，答案为 $n+1$。

* 第二种情况，包含两个及以上的点。

枚举正方形最左和最右的两个点 $i,j(i<j)$，满足 $|x_i-x_j|\geq |y_i-y_j|$，则正方形的边长 $side=|x_i-x_j|$。对于 $|x_i-x_j|\leq |y_i-y_j|$ 的情况，可以通过交换每个点的 $x,y$ 坐标再通过相同的方式得到答案，这里就不再讨论。

对所有坐标以 $x$ 坐标为第一关键字，$y$ 坐标为第二关键字排序。排序之后，正方形中所有点的下标必定在 $[i,j]$ 之间，$x$ 坐标必定在 $[x_i,x_j]$ 之间。

考虑 $y$ 坐标，不妨将下标在 $[i,j]$ 之间的点的 $y$ 坐标排序后放在一个长度为 $j-i+1$ 的数组 $v$ 中。这样，正方形中的点的 $y$ 坐标一定属于数组 $v$ 的一个连续区间。问题转变为了求出这个区间的两端点 $l,r$ 有多少种组合方式。因为 $v$ 数组有序，所以可以使用双指针来解决这个问题。

### 双指针的具体实现

这里的双指针类似于滑动一个长度为 $side$ 的窗口。

首先确定 $v_l$ 和 $v_r$ 的范围。因为正方形必须包含 $i,j$ 两点，所以设 $mini=\max(y_i,y_j)-side$，$maxi=\min(y_i,y_j)$，那么正方形的下边界 $lower\in[mini,maxi]$，上边界 $upper\in[mini+side,maxi+side]$。

**注**：上边界和下边界并不代表 $v_l$ 和 $v_r$。

接下来讨论什么样的 $[l,r]$ 是合法的。需要满足以下两个条件。

* 正方形必须能同时包含 $v_l$ 和 $v_r$ 两个坐标，即 $v_l\leq v_r-side$。

* 正方形不能包括 $v_{r+1}$，同样不能包括 $v_{l-1}$。
	
    这个条件的讨论有一些复杂。不妨固定右端点 $r$，去寻找可行的左端点。
    
    包含 $v_r$ 且不包含 $v_{r+1}$，正方形的上边界需要满足 $upper\in[v_r,v_{r+1}-1]$，对应到下边界就是 $lower\in[v_r-side,v_{r+1}-1-side]$。要使 $l$ 合法，则需 $\exists lower[v_r-side,v_{r+1}-1-side]$，使得 $lower>v_{l-1}$。那么只要使 $lower$ 的最大值 $v_{r+1}-1-side>v_{l-1}$ 即可。
    
    所以只要满足 $v_{r+1}-1-side>v_{l}$ 便可将指针 $l$ 向右移动一位，即 $l\gets l+1$。
    
最后还有 $|x_i-x_j|\geq |y_i-y_j|$ 和 $|x_i-x_j|\leq |y_i-y_j|$ 出现重复的问题。如果在统计的时候出现 $v_r-v_l=side$ 的情况，那么当 $l,r$ 对应的下标成为下一轮枚举的 $i,j$ 时，这个正方形中包含的子集会被再统计一次，减去即可。

这道题还有很多的细节，详情请见代码。（当然你问我为什么代码显示不全，是因为代码太宽了233，只需要复制到编辑器里就可以看了）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
inline int read() {
	int x = 0; bool op = false;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int N = 210;
int n, ans, res;
struct Node {
	int x, y;
	bool operator < (const Node &tmp) const {
		if(x ^ tmp.x)return x < tmp.x;
		else return y < tmp.y;
	}
	Node(int x = 0, int y = 0):x(x), y(y){}
}a[N];
set<int> s;
void solve() {
	sort(a + 1, a + 1 + n);
	for(int i = 1; i < n; i++) {
		s.clear(); s.insert(a[i].y);
		for(int j = i + 1; j <= n; j++) {
			s.insert(a[j].y);
			vector<int> vec(s.begin(), s.end()); //从题解里面学到的奇怪操作，相当于把s中的元素复制到了vec里 
			int side = a[j].x - a[i].x;
			int mini = max(a[i].y, a[j].y) - side, maxi = min(a[i].y, a[j].y);
			if(mini > maxi)continue; //如果下界在上界之上，直接跳过 
			int len = vec.size(), l = 0, r = -1;
			while(r + 1 < len && vec[r + 1] < mini + side)r++; 
			//找到最大的r，使得vec[r]<mini+side
			//之所以要这么找，是因为可能存在上界在[mini+side,maxi+side]之中但是vec[r]不在这个区间之中的情况
			//那么包含它且不包含vec[r+1]的条件也有所转变，即上界在[mini+side,vec[r+1]-1]之间。 
			while(l < len && vec[l] < mini)l++; //找到最小的l，使vec[l]>=mini 
			for(; r < len && (r < 0 || vec[r] <= maxi + side); r++) {//我比较喜欢这种双指针的写法，即确定r枚举l 
				if(r < 0)continue; //r<0直接跳过 
				int tl = max(vec[r] - side, mini);
				int tr = min((r + 1 < len) ? vec[r + 1] - side : maxi + 1, maxi + 1) - 1;
				//如果r+1不存在，那么把上界设为maxi+1（因为后面有一个-1所以不能设为maxi）
				//此时正方形下边界的范围为[tl,tr] 
				while(l < len && vec[l] < tl)l++;//首先提出vec[l]在下边界以下的情况 
				if((vec[r] < mini + side && vec[r + 1] > mini + side) || vec[r] >= mini + side)ans++;
				//细节：此时r增加了1，不管l能不能移动，它都是一种新的情况，需要统计答案
				//当然其中也有不合法的答案，比如说vec[r]在下边界一下，但是上边界根本不可能移动到mini+side以上
				//这种情况就是ver[r+1]正好等于mini+side
				if(vec[r] - vec[l] == side)res++; //去重 
				while(l + 1 < len && vec[l] < tr) {ans++; l++; if(vec[r] - vec[l] == side)res++;}//统计答案+去重 
			}
		}
	}
	return ;
}
int main() {
	n = read(); ans = n + 1; 
	for(int i = 1; i <= n; i++) {int x = read(), y = read(); a[i] = Node(x, y);}
	solve(); 
	for(int i = 1; i <= n; i++)swap(a[i].x, a[i].y);
	solve();
	printf("%d", ans - res / 2);
	return 0;
}

```


---

## 作者：编程客 (赞：4)

# P7153 [USACO20DEC] Square Pasture G 题解

注意：这个不是正常做法~~但是能过~~，读者如果想看正解**不要来这里**，但是这篇题解可以成为很好的考场骗分思路。考场上只要能得分的就是好做法，有时候~~甚至能过~~。

## 题意
- 给定 $n$ 个二维平面上的点，x 坐标两两不同，y 坐标两两不同。
- 问用正方形框住平面上的点，能有多少不同的点集，**包括空集**。
- $1\le n\le 200, 0\le x,y\le 1e9$。
## 思路
这里约定，原题中的 $1\times 1$ 的小矩形为一个点。

首先看到这道题，第一反应：~~暴力~~ 我们发现，这个点集一定是**被一个正方形覆完全盖住的**的，也就是说，不会有点在这个正方形中却不在点集中。这样就会导致：就算有一个点集临近，也无法计入答案，因为可能框住这个点集的正方形必须框住其他点，这样这个点集就无法计入答案。

我们先把所有点离散化一下，这样子就变成了 $1\le x,y\le 200$ 的点了，方便处理。然后，**我们枚举所有可能成为答案的点集**，判断是否能够计入答案。也就是说，我们枚举我们想要哪些点成为答案，再判断这些点构成的矩形能否被正方形框住。因为是一个矩形，因此只需要枚举左上角、右下角，总大概在 $n^4$ 的数量级。这时候可能会有人疑惑：这个矩形外面可能还会有空余地方，怎么处理呢？因为题目要求的是**不同点集**的数量，而不是正方形的数量，因此我们只需要考虑点就好了。

但是这样子的话我们必须要保证不计重。这里处理的话可以枚举一下行，然后保证矩形一定要包括最上面和最下面的两个点，在此基础上在枚举列。这样就保证了一个矩形只会被最上面的点以及最下面的点枚举到一次。

接下来我们有了一个点集以及框住这个点集的最小矩阵，我们考虑判断**是否能够通过这个矩阵周围的空余变成一个正方形**。因为这是一个矩形，题目要求的是一个正方形，因此我们需要判断一下。这里有一个很显然的结论：一个矩形如果是扁的，我们就把他拉长；如果是高的，我们就把他往左右扩张。换句话说，只会让矩形水平或者垂直扩张。这样一定是不劣的。因此只需要判断一下，这个矩形比较长的两条边最多能往外扩张多少，判断是否能成为正方形。

为了更好的理解，这里实际操作一下。比如有这样一个点集：
![1](https://s1.ax1x.com/2022/04/03/q7Fage.png)

现在要判断这个点集：

![2](https://s1.ax1x.com/2022/04/03/q7FN9O.png)

那么这个矩形就是覆盖住这个点集的最小矩形。我们现在要判断是否有正方形能够覆盖住这个点集**而不覆盖住别的点**，那么就需要扩张矩形而不碰到其他点。对于这个点集，我们只需要**左右扩张**就足够了，这样一定不劣。那么这个矩形能往外扩张这么多：

![3](https://s1.ax1x.com/2022/04/03/q7FU3D.png)

如图，黄色表示无限。那么如图，两个紫色和红色正方形都是合法方案。

![4](https://s1.ax1x.com/2022/04/03/q7FY4K.png)

能往外扩张多少，这个要看距离这条边最近的点有多远，这中间的距离都是可以取到的。然后我们只需要找到这个点或者判断没有点就好了，没有的话距离就是无限。

为了方便处理，我这里直接是把四个方向能扩张的距离全都求了出来，这样子虽然耗时但可以避免许多分类讨论。求法我这里直接上了二维前缀和加二分，当然应该会有更优的做法。

因此这道题就做完了。整理一下思路：

1. 枚举我们需要的点集，找到围住点集最小的矩形
2. 判断矩形是否能够扩张成为一个正方形，能的话就计入答案贡献。

这样子时间复杂度总共 $O(n^4\log n)$，自然是不对的。但如果实现的好常数小，过掉这道题还是很轻松的。本人考场代码不加 O2 最慢 311ms ，跑的飞快。

这启示我们，只要实现的好，复杂度高也可以接受！

撒花！
## 细节
细节处理自然是很重要的。
1. Inf 一定要设的足够大！否则就会像我一样考场只剩 25 分。。。
2. 记得加上空集的贡献。
3. 在原题中不是点而是一个 $1\times 1$ 的小矩形，因此处理往外扩张多少时边界注意。
4. 一些枚举矩阵的没用状态可以直接判掉，可以让常数小很多。
5. 二分边界注意。

当然，实际处理中还有很多细节，这里就不一一讲述了。写代码自然还是推荐读者明白思路之后自己写，看别人代码会使学习效果没那么高。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;
#define ll long long
#define int long long
#define y1 __
#define abs_(x) max(x,-(x))
const int N=205+2,I=0x3f3f3f3f3f3f3f3f;
int read()
{
	int x=0,y=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') y=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return y?x:-x;
}
struct _N
{
	int x,y;
}a[N];
int n,b1[N],b2[N];
int ans;
vector<int> g[N],v1,v2;
int las[N],nxt[N];
bitset<N> bt;
int b[N][N],s[N][N];
void init()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int y=read(),x=read();
		b1[i]=a[i].x=x;
		b2[i]=a[i].y=y;
	}
	sort(b1+1,b1+n+1);
	for(int i=1;i<=n;i++) a[i].x=lower_bound(b1+1,b1+n+1,a[i].x)-b1;
	sort(b2+1,b2+n+1);
	for(int i=1;i<=n;i++) a[i].y=lower_bound(b2+1,b2+n+1,a[i].y)-b2;
	for(int i=1;i<=n;i++) g[a[i].x].push_back(a[i].y);
	b2[0]=-I,b2[n+1]=I;
	b1[0]=-I,b1[n+1]=I;
	
	for(int i=1;i<=n;i++) b[a[i].x][a[i].y]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+b[i][j];
		}
	}
}
int get(int x1,int y1,int x2,int y2)
{
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
signed main()
{
	init();
	for(int i1=1;i1<=n;i1++)
	{
		bt.reset();
		v1=g[i1];
		bt.set(n+1); 
		for(int i2=i1;i2<=n;i2++)
		{
			for(int j=0;j<g[i2].size();j++) bt.set(g[i2][j]);
			for(int j=1;j<=n+1;j++)
			{
				if(bt[j-1]) las[j]=j-1;
				else las[j]=las[j-1];
			}
			for(int j=n;j>=0;j--)
			{
				if(bt[j+1]) nxt[j]=j+1;
				else nxt[j]=nxt[j+1];
			}
			v2=g[i2];
			for(int j1=nxt[0];j1<=n;j1=nxt[j1])
			{
				if(!bt[j1]) continue;
				int t1=lower_bound(v1.begin(),v1.end(),j1)-v1.begin();
				int t2=lower_bound(v2.begin(),v2.end(),j1)-v2.begin();
				if(t1==(int)v1.size()||t2==(int)v2.size()) break;
				for(int j2=max(v1[t1],v2[t2]);j2<=n;j2=nxt[j2])
				{
					if(!bt[j2]) continue;
					int dn2=b2[j2]-b2[j1]+1,up2=b2[j1]-b2[las[j1]]-1+b2[nxt[j2]]-b2[j2]-1;
					int dn1=b1[i2]-b1[i1]+1;
					int up1=0;
					int l=0,r=i1-1;
					while(l<r)
					{
						int mid=l+r+1>>1;
						if(get(mid,j1,i1-1,j2)) l=mid;
						else r=mid-1;
					}
					up1+=b1[i1]-b1[l]-1;
					l=i2+1,r=n+1;
					while(l<r)
					{
						int mid=l+r>>1;
						if(get(i2+1,j1,mid,j2)) r=mid;
						else l=mid+1;
					}
					up1+=b1[l]-b1[i2]-1;
					up1+=dn1,up2+=dn2;
					if(dn1<=up2&&up1>=dn2||dn2<=up1&&up2>=dn1) ans++;
				}
			} 
		}
	}
	printf("%d\n",ans+1);
	return 0;
}
/*
5
2 1
12 0
5 18
14 5
13 2
*/
```

---

## 作者：zifanwang (赞：3)

[传送门](https://www.luogu.com.cn/problem/P7153)

对于每种集合只考虑包含这些点的最小的正方形，这样就不会多算。对于一个正方形，如果两条邻边上都没有奶牛，那就可以将边长减一。

考虑左边和上面的两条边。

$1.$ 如果两边上都有奶牛：

可以枚举左上角的点，然后对每个能覆盖到的点求出覆盖这个点最短的正方形的边长，最后对这些边长去个重，统计一下有多少个合法即可，时间复杂度 $O(n^3\log n)$。

---

$2.$ 如果两边上只有一边有奶牛：

下面假设是左侧边上没有奶牛，上边没有奶牛的情况类似处理。

那么底边一定也有奶牛，枚举这两条边的纵坐标，那么正方形的边长就知道了。考虑一个左侧边上没有奶牛的正方形，如果向右移一格覆盖到的奶牛集合不变，那这个正方形就不对答案有贡献。

于是可以枚举右侧边的横坐标，其横坐标加一一定是一个点的横坐标，时间复杂度 $O(n^3\log n)$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct node{
	int x,y;
}a[203];
int n,t,ans,d[203],d1[203],d2[203],p1[203],p2[203];
set<int>s;
map<int,bool>mp;
signed main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&a[i].x,&a[i].y),d1[i]=a[i].x,d2[i]=a[i].y;
	sort(d1+1,d1+n+1);
	sort(d2+1,d2+n+1);
	rep(i,1,n){
		p1[lower_bound(d1+1,d1+n+1,a[i].x)-d1]=i;
		p2[lower_bound(d2+1,d2+n+1,a[i].y)-d2]=i;
	}
	rep(i,1,n){
		rep(j,1,n)if(a[p1[i]].y>=d2[j]&&a[p2[j]].x>=d1[i]){
			s.clear();
			rep(k,1,n)if(a[k].x>=d1[i]&&a[k].y>=d2[j])s.insert(max(a[k].x-d1[i],a[k].y-d2[j]));
			for(int k:s)if(k>=max(a[p1[i]].y-d2[j],a[p2[j]].x-d1[i]))ans++;
		}
	}
	d[0]=-2e9;
	rept(i,1,n){
		rep(j,i+1,n){
			int y1=a[p1[i]].y,y2=a[p1[j]].y,ds=d1[j]-d1[i];
			if(y1>y2)swap(y1,y2);
			if(y2-y1>ds)continue;
			t=0;
			mp.clear();
			rep(k,1,n)if(a[p2[k]].x>=d1[i]&&a[p2[k]].x<=d1[j])d[++t]=d2[k],mp[d2[k]]=1;
			int e2=lower_bound(d+1,d+t+1,y2)-d;
			rep(k,e2+1,t){
				if(d[k]-1-ds>=y1)break;
				if(mp.find(d[k]-1-ds)==mp.end())ans++;
			}
		}
	}
	rept(i,1,n){
		rep(j,i+1,n){
			int y1=a[p2[i]].x,y2=a[p2[j]].x,ds=d2[j]-d2[i];
			if(y1>y2)swap(y1,y2);
			if(y2-y1>ds)continue;
			t=0;
			mp.clear();
			rep(k,1,n)if(a[p1[k]].y>=d2[i]&&a[p1[k]].y<=d2[j])d[++t]=d1[k],mp[d1[k]]=1;
			int e2=lower_bound(d+1,d+t+1,y2)-d;
			rep(k,e2+1,t){
				if(d[k]-1-ds>=y1)break;
				if(mp.find(d[k]-1-ds)==mp.end())ans++;
			}
		}
	}
	cout<<ans+1;
	return 0;
}
```

---

## 作者：ybwowen (赞：2)

我们考虑枚举一个正方形中最左边和最右边的点。记它们的坐标分别为$(x_i,y_i)$和$(x_j,y_j)$。那么在这个正方形中的点$k$必须满足$x_k\in[x_i,x_b]$，$y_k\in[y,y+x_j-x_i]$，其中$y\in[\max(y_i,y_j)-(x_j-x_i),\min(y_i,y_j)]$。注意此时我们必须满足$\min(y_i,y_j)\ge \max(y_i,y_j)-(x_j-x_i)$。

我们找出所有满足$x_k\in(x_i,x_b)$的点，将这些点按纵坐标从小到大排序，用two pointers扫一遍统计答案即可。

时间复杂度为$O(n^3 \log n)$。

```c++
#include<bits/stdc++.h>
#define mp make_pair
#define F first
#define S second
#define pb push_back
#define lson k<<1
#define rson k<<1|1
//#define getchar nc
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll INF64 = 1e18;

inline char nc(){
	static char buf[100005],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	char ch=getchar(); int sum=0; int f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return f?-sum:sum;
}
const int maxn=205;
int n,ans,res;	
struct Node{
	int x,y;
}a[maxn];
set<int>s;
inline bool cmp(const Node &x,const Node &y){
	if(x.x==y.x) return x.y<y.y;
	else return x.x<y.x;
}
inline void work(){
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		s.clear();
		for(int j=i+1;j<=n;j++){
			if(i<j-1) s.insert(a[j-1].y);
			int side=a[j].x-a[i].x;
			int minn=max(a[i].y,a[j].y)-side;
			int maxx=min(a[i].y,a[j].y);
			if(minn>maxx) continue;
			vector<int>vec(s.begin(),s.end());
			int len=vec.size(),l=0,r=-1; 
			while(l<len&&minn>vec[l]) l++;
			while(r+1<len&&minn>=vec[r+1]-side) r++;
			while(true){
				ans++;
				int yl=min(a[i].y,a[j].y),yr=max(a[i].y,a[j].y);
				if(l<=r) yl=min(yl,vec[l]),yr=max(yr,vec[r]);
				if(yr-yl==side) res++;
				int newl=(l<len?vec[l]+1:INF);
				int newr=(r+1<len?vec[r+1]-side:INF);
				int tmp=min(newl,newr);
				if(tmp>maxx) break;
				if(newl==tmp) l++;
				if(newr==tmp) r++;
			}
		}
	}
}
int main(){
	n=read(); ans=n+1;
	for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
	work(); for(int i=1;i<=n;i++) swap(a[i].x,a[i].y); work();
	printf("%d\n",ans-res/2);
	return 0;
}
```



---

## 作者：ClearluvXL (赞：1)

# Square Pasture 方形草场
PZ：感谢题解的一楼大佬的题解提供的思路。
## 思路
   对于空集和只有一个点他本身的情况，肯定是能够满足的。我们最后统计答案时加上 $n+1$ 即可。
   
   那么对于其他的集合情况，因为两点确定一个正方形的大小。(本题已经说明了 $x,y$ 各不相同) 我们先考虑当正方形的边长为两点 $x$ 之差时，(考虑 $y$ 只需后续将 $x,y$ 交换即可)，上下移动正方形能够框住的不同集合。
  
  先将点排序 优先级 $x>y$。
  怎么上下移动正方形呢? 没有动态图真的是太难受了。
  
  我们想象一下，在一个正方形内的点，最远两个的距离肯定小于等于正方形的边长，而正方形外的点，最近两个的肯定大于正方形的边长。
  
  这个图看上去是没什么用的。
  ![](https://cdn.luogu.com.cn/upload/image_hosting/lq30jjag.png)
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/t9cnyqny.png) 
  
  那么我们根据上述讲的，确定两点为框架而构成的正方形中，只需要在他们的 $y$ 中找出可能的集合即可，需要注意以下几个点：
     
  1.   最下端的点和 $\max(y_{i},y_{j})$ 的距离应该 $\leq len$。 
  2.   最上端的点和 $\min(y_{i},y_{j})$ 的距离应该 $\leq len$。
  3.   $y_{r}-y{l}\leq len$ 并且 $y_{r+1}-y_{l-1}>len$。

 我们需要两个指针，来动态维护一个满足上述条件的区间。
 
 我们不需要被集合两个字束缚住了，我们确定了两点为一个框架后，能够出现的点肯定是确定的，那么在移动 $y$ 的指针是，如果出现了一对新的指针，那么不就相当于是出现了一个新的集合了吗？
 
 最后统计答案的时候要注意算重复的集合。什么是算重复的集合呢？详见下图。
 ![](https://cdn.luogu.com.cn/upload/image_hosting/hldqr59s.png)
  
  也就是说，当前左右指针的上界和下界都在边线上，那么在将 $y$ 为第一关键字排序后，也会枚举到这种情况，我们只需要加个特判 (详见代码)。
 ***
  由于代码实现需要诸多细节：此处我将阐述一些变量的意思以及作用。
  
- [ $l,r$ 为指针。]

- [ $maxl,minl,maxr,minr$ 分别表示下界和上界的最大最小值，都是对应的数值而非下标。] 

- [ $tl,tr$ 是在确定了当前的上界之后，也就是必须包含这个 $y$ 的值，并且他为最上面的那一个时，下界的范围。而此时每增加一个新的下界那么答案都可以增加。]  
## 代码
双指针的实现
```c++
#include<bits/stdc++.h>
#define endl '\n'
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=210;

int n;
pii a[N]; 

int res=0;//重复计算点对计数 
int ans=0;//计算答案 

set<int> s;
 
void solve(){
	for(int i=1;i<n;i++){
		s.clear();
		s.insert(a[i].se);//x,y都各不相同。 
		for(int j=i+1;j<=n;j++){
			s.insert(a[j].se);
			if(abs(a[j].fi-a[i].fi)<abs(a[j].se-a[i].se)) continue;
			
			int len=a[j].fi-a[i].fi;
			
			int maxl=min(a[i].se,a[j].se); 
			int minl=max(a[i].se,a[j].se)-len;
			int minr=max(a[i].se,a[j].se);
			int maxr=min(a[i].se,a[j].se)+len;
			
			//maxy,miny表示的是此时正方形下界的y的移动范围 
			
			vector<int> p(s.begin(),s.end());
			int siz=p.size();
			int l=0,r=-1;
			
			while(r+1<siz&&p[r+1]<minr) r++;
			r++;
			
			while(l<siz&&p[l]<minl) l++;
			
			for(;r<siz&&p[r]<=maxr;r++){
				int tl=max(p[r]-len,minl);
				int tr;
				if(r==siz-1) tr=maxl;
				else tr=min(p[r+1]-len-1,maxl);
				while(l<len&&p[l]<tl) l++;//去掉不可能的下界 
				ans++;//找到了最远的满足条件的下界，答案+1 
				if(p[r]-p[l]==len){
					res++;//去重
					//需要上界下界都在边线上 
				}
				while(l+1<len&&p[l]<tr){
					//这里的上下界绝对不可能在边线上所以无需去重 
					l++;
					ans++;
				}
			}
		}	
	}
}//end

int main(){
	
	freopen("genetics.in","r",stdin);
	freopen("genetics.out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin>>n;
	
	ans+=n+1;//空集和只有一个时的情况 
	
	for(int i=1;i<=n;i++) {
		int x,y;
		cin>>x>>y;
		a[i]={x,y};
	}
	
	sort(a+1,a+n+1);
	solve();
	
	for(int i=1;i<=n;i++){
		swap(a[i].fi,a[i].se);
	}
	
	sort(a+1,a+n+1);
	solve();
	
	cout<<ans-res/2<<endl;
	
	return 0;
}//end
```

---

## 作者：DYYqwq (赞：1)

首先，如果说这些正方形包含的都是空集，或只有 $1$ 个点，大家应该都会做吧。这样的子集数量自然是  $n+1$。

然后考虑有 $\ge 2$ 个点的情况。

我们首先进行一个序的排。以 $x$ 坐标为第一关键字。

不妨枚举这个正方形最左点 $i$ 和最右点 $j$。

我们假定 $x$ 坐标差 $\gt  y$ 坐标差。如果不是也无所谓，因为我们要把 $x,y$ 坐标全反转再做一遍。

确定好 $x$ 坐标的上界下界以后发现我们的 $y$ 坐标就好处理了。可以把 $[i,j]$ 之间的点全扔进一个数组 $a$ 中，从大到小排序。由于数组有序了，于是可以双指针一下。

为了方便叙述设正方形边长为 $len=x_j-x_i$。

显然 $y$ 坐标下界为 $\in [\max(y_i,y_j)-len,\min(y_i,y_j)]$，上界的上下界为下界的上下界 $+len$（好绕啊）。

考虑如何判断一组 $l,r$ 是否可行。

- 首先这个正方形不能偏心 $l,r$ 中的一个。即不能只覆盖一个不覆盖另一个。因此 $a_l + len \le a_r$。

- 接着，这个正方形不能出去。即不能包含 $l-1,r+1$。这里我就不会了。但是这种问题有一个 trick，就是固定其中一个端点考虑另外一个是什么情况。我们这里不妨考虑让 $r$ 不动。于是发现正方形 $y$ 轴上边界 $\in [a_r,a_{r+1}-1]$。那下边界就对应 $-len$。然后发现只要 $[a_r-len,a_{r+1}-1-len] \cap (a_{l-1},+ \infty] \ne \emptyset$ 即可。即 $a_{l-1} \lt a_{r+1}-1-len$。

结合起来，我们需要 $a_l + len \le a_r$ 且 $a_{l-1} \lt a_{r+1}-1-len$。

于是 $a_l \lt a_{r+1}-1-len \Longrightarrow l \leftarrow l + 1$。

但是还有一个致命的细节，我们最一开始的时候假定了 $x$ 坐标差 $\gt  y$ 坐标差，并说我们会在下一次的时候反转坐标再做一遍。但实际上可能有 $x$ 坐标差 $=  y$ 坐标差的。特判减去即可。

我代码写成一坨子了，我也不知道写的是啥，就不放码了，不会写的话可以参考第一篇题解的注释，十分详细。

---

## 作者：qwer6 (赞：0)

[Link](https://www.luogu.com.cn/problem/P7153)

## 1. Description

给定 $n$ 个点的坐标，保证每个点的 $x$ 坐标各不相同，$y$ 坐标各不相同，求出所有的正方形可能包含的点集的子集个数。

## 2. Solution

我们尝试利用 $x,y$ 坐标各不相同这个条件来简化求解过程。

想到一个求解过程：首先先将所有点按照 $x$ 坐标排序，枚举 $i,j$，这里要求 $x_i-x_j+1\ge y_i-y_j+1$，第 $i$ 个点在左边界上且第 $j$ 个点在右边界上的所有正方形可能包含的子集个数，然后将所有点按照 $y$ 坐标排序，枚举 $i,j$，这里要求 $y_i-y_j+1\ge x_i-x_j+1$，求第 $i$ 点在下边界上且第 $j$ 个点在上边界上的所有正方形可能包含的子集个数，最后去掉重复的，就可以得到所有可能的子集。

我们先只考虑一次枚举，尝试证明一个结论：不同的 $i,j$ 可以得到的子集是没有交的。显然，因为边界不同，导致不同的 $i,j$ 可以得到的子集必然不同，所以我们在枚举一对 $(i,j)$ 时，去重只需要考虑此时是否有重复的即可。

以第一次循环为例，我们首先将坐标离散化，使用哈希与 set 维护不同的子集，由于左右边界已经确定，令 $minn=\min(y_i,y_j),maxn=\max(y_i,y_j)$，所以我们先枚举下边界 $k\in [1,minn]$，然后二分出上边界，计算当前子集的哈希值，加入集合。这里注意一个可能算漏的地方：由于我们离散化了坐标，所以下边界从 $k$ 移动到 $k+1$ 时，上边界可能从 $up$ 移动到 $up+b$ 的位置，但是中间可能会出现 $k$ 这个 $y$ 坐标对应的奶牛不在集合中，而 $up$ 还没有移动的情况，这样就会漏算，所以我们在计算的时候加入一个上边界为 $y_k+1$  时的情况，注意需要满足 $y_k+1\ne y_{k+1}$。接着枚举上边界 $k\in [maxn,n]$，然后参照上面的方法计算，注意需要加入下边界为 $y_k-1$ 的情况，条件为 $y_k-1\ne y_{k-1}$。这一对 $(i,j)$ 的贡献就是最后 set 的大小。

在第二次循环时，我们需要进行去重，哪些正方形可能会算重呢？就是四边上都有点的正方形，特判掉之后，不要加入集合即可。

## 3. Code

代码写得太丑就不放了，[放一个链接好了](https://www.luogu.com.cn/paste/f0tskq5g)。

---

## 作者：huhangqi (赞：0)

对于在矩形内统计的问题，我们通常可以枚举左右端位置来解决，但是这道题目要求是正方形内，这代表着我们的 $y$ 轴方向的长度是会受到 $x$ 轴上的长度的影响的，但是如果我们再考虑 $x$ 轴的范围，那么实在是太复杂了。

所以这道题目有一个好方法，就是枚举两个点，只处理 $x$ 距离和 $y$ 的距离中比较短的距离进行处理。

那么我们就可以只处理 $x$ 差值更小的，然后再交换 $x$ 和 $y$ 的值，然后注意去重。

我们剩下的就是直接枚举左右，然后按照 $y$ 值排序，由于是反复加入的过程，可以直接插入排序，这样单次操作为 $O(n)$ 的，效率较高，接下来枚举下端点，然后用双指针得到可选取值的范围即可。

去重就是在最高的作为最高点的点和下端距离与 $x$ 相等时的情况，需要减去。

最后由于我们是枚举左右端点来解决的，所以需要加一表示空集的情况。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,tmp,b[205],cnt;
struct P{
	int x,y;
}a[205];
bool cmp(P a,P b){
	return a.x<b.x;
}
void solve(){
	for(int i=1;i<=n;i++){
		cnt=0;
		b[0]=-2e9;
		for(int j=i;j<=n;j++){
			b[++cnt]=a[j].y;
			for(int i=cnt;i>=2;i--){
				if(b[i]<b[i-1])swap(b[i],b[i-1]);
				else break;
			}
			if(a[j].x-a[i].x<abs(a[j].y-a[i].y))continue;
			int up=max(a[i].y,a[j].y),down=min(a[i].y,a[j].y),len=a[j].x-a[i].x;
			int w1=upper_bound(b+1,b+cnt+1,up)-b-1,w2=0;
			for(int k=1;k<=cnt;k++){
				if(b[k]>down||b[k]+len<up)continue;
				while(w1<cnt&&b[k-1]+len+1>=b[w1+1])w1++;
				while(w2<cnt&&b[k]+len>=b[w2+1])w2++;
				ans+=w2-w1+1;
				if(b[w2]-b[k]==len)tmp++;
			}
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	solve();
	for(int i=1;i<=n;i++)swap(a[i].x,a[i].y);
	sort(a+1,a+n+1,cmp);
	solve();
	cout<<ans-tmp/2+1;
	return 0;
}
``````

---

## 作者：vicissitudes (赞：0)

既然双指针难调，为何不用二分呢？

~~虽然二分也一样难调。~~

先按 $x$ 排序，然后枚举正方形的最靠左和最靠右的两个点。那我们就去找这个正方形能包含多少种不停的子集。

记枚举的点为 $i$ 和 $j$。

由于 $i$ 和 $j$ 之间的点 $x$ 坐标都夹在他们之间，我们可以把 $i$ 和 $j$ 之间的点的 $y$ 坐标单独拿出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/fcov14gb.png)

这时，我们发现 $1$ 和 $6$ 围成的图形不一定是个正方形。

方便叙述，我们让 $x_j - x_i \ge \operatorname{abs} (y_i - y_j)$。待会交换 $x$，$y$ 坐标相当于反着做 $x_j - x_i \le \operatorname{abs} (y_i - y_j)$ 即可。

则此时，正方形的边长为 $len = x_j - x_i$，由于宽比长短，所以我们的边界可以上下调。

为了好看特意画歪了点。

![](https://cdn.luogu.com.cn/upload/image_hosting/w6s3odr2.png)

有一个 naive 的想法是，我们去找蓝色正方形(或绿色)中 $y$ 小于 $1$ 号点(或大于 $6$ 号点)的个数。意思是以这些点为正方形的下界(上界)，得到的子集肯定不一样。

但是点一定要在边界上吗？

![](https://cdn.luogu.com.cn/upload/image_hosting/nj6rgto5.png)

例如，红色的正方形能够包含 $4$ 个点，但是你把正方形向下调，也就是蓝色的正方形只包含了三个点，但是点不一定在边界上。

所以我们在求答案时，不应该把一个点作为下界，而是应该作为**最下面的点**。

由于我们在讨论上下界，左右界已经固定。于是对 $y$ 坐标分析。

假设我们已经选定当前最下面的点为 $k$。那么我们的下界是可以放在 $[y_{k  -1} + 1，y_k]$ 处的，对应的，我们的上界就放在 $[y_{k  -1} + 1 + len，y_k + len]$ 处。那么答案就是 $y$ 落在这个区间的点数。相当于就是每个点都可以作为**最上面的点**。

当然，前提是你要满足上界和下界包含你枚举的点。

有特殊情况。

记 $up = \max(y_i,y_j)$。

如果 $y_{k  -1} + 1 + len < up$，那么说明上界的最小值太小了，低于 $up$ 的点你取了，但事实上你**不该取**，而是应该从 $up$ 开始取。也就是上界取值范围的左半括号应该是 $up$。注意上界是个**区间**。

有重复的咋办？可以发现，如果有 $y_b - y_a = len$。那么在交换后枚举到 $a$ 和 $b$ 时，又会加上当前的 $i$ 和 $j$ 的贡献。由于多算了一次，最后减掉即可。

关于实现找范围内点，大部分题解用的双指针。其实没必要，时间复杂度**瓶颈在枚举端点和排序**，并不在找数上。$\operatorname{upperbound}$ 查找即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 210;
int n;
struct node {
	int x, y;
	bool operator< (const node &b) const {
		return x < b.x;
	}
} p[N];

int a[N], cnt;
int ans, t;

void solve() {
	for(int i = 1; i <= n; i ++) {
		cnt = 0; a[0] = -INT_MAX;
		for(int j = i; j <= n; j ++) {
		 
			a[++ cnt] = p[j].y;
			if(p[j].x - p[i].x < abs(p[j].y - p[i].y)) continue;
			
			sort(a + 1, a + cnt + 1);
			
			int up = max(p[i].y, p[j].y), down = min(p[i].y, p[j].y);
			int len = p[j].x - p[i].x;
			
			for(int k = 1; k <= cnt; k ++) {
				if(a[k] > down || a[k] + len < up) continue;
				int pos1, pos2;
				if(a[k - 1] + len + 1 >= up) pos1 = upper_bound(a + 1, a + cnt + 1, a[k - 1] + len + 1) - a - 1;
				else pos1 = upper_bound(a + 1, a + cnt + 1, up) - a - 1;
				pos2 = upper_bound(a + 1, a + cnt + 1, a[k] + len) - a - 1;
				ans += pos2 - pos1 + 1;
				if(a[pos2] - a[k] == len) t ++;
			}
		}
	}
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> p[i].x >> p[i].y;
	}
	sort(p + 1, p + n + 1); 
	solve();
	for(int i = 1; i <= n; i ++) {
		swap(p[i].x, p[i].y);
	}
	sort(p + 1, p + n + 1); 
	solve();
	cout << ans - t / 2 + 1 << endl ;//减去重复的，加上空集
	return 0;
}
```

---

