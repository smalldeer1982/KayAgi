# [USACO24OPEN] Walking Along a Fence B

## 题目描述

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^5$）每头都喜欢日常沿围着牧场的栅栏散步。

栅栏由 $P$ 根柱子组成（$4\le P\le 2\cdot 10^5$，$P$ 为偶数），每根柱子的位置是 FJ 农场地图上的一个不同的二维坐标点 $(x,y)$（$0\le x,y\le 1000$）。每根柱子通过垂直或水平线段的栅栏连接到两根相邻的柱子，因此整个栅栏可以被视为各边平行于 $x$ 轴或 $y$ 轴的一个多边形（最后一根柱子连回第一根柱子，确保围栏形成一个包围牧场的闭环）。栅栏多边形是「规则的」，体现在栅栏段仅可能在其端点处重合，每根柱子恰好属于两个栅栏段，同时每两个在端点处相交的栅栏段都是垂直的。

每头奶牛的日常散步都有一个偏好的起始和结束位置，均为沿栅栏的某个点（可能在柱子处，也可能不在）。每头奶牛日常散步时沿着栅栏行走，从起始位置开始，到结束位置结束。由于栅栏形成闭环，奶牛有两条路线可以选择。由于奶牛是一种有点懒的生物，每头奶牛都会选择距离较短的方向沿栅栏行走（如果并列，奶牛可以选择任一方向）。

求每头奶牛行走的距离。 

## 说明/提示

### 样例解释

第一头奶牛可以直接从 $(0,0)$ 走到 $(0,2)$。

第二头奶牛可以从 $(0,2)$ 走到 $(0,0)$，然后走到 $(1,0)$。

第四头奶牛有两条长度相等的可能路线：$(1,0)\to (0,0)\to (0,2)\to (1,2)$ 和 $(1,0)\to (2,0)\to (2,2)\to (1,2)$。

### 测试点性质

- 测试点 $2-6$：$0\le x,y\le 100$ 且 $N\le 100$。
- 测试点 $7-11$：没有额外限制。

## 样例 #1

### 输入

```
5 4
0 0
2 0
2 2
0 2
0 0 0 2
0 2 1 0
2 1 0 2
1 0 1 2
1 2 1 0```

### 输出

```
2
3
3
4
4```

# 题解

## 作者：cff_0102 (赞：9)

发现 $x,y$ 小于等于 $1000$，可以直接把每个点前的第一个柱子位置和编号存下来。再用一个前缀和数组记录下每两个柱子之间的距离，即代码中的 `dis`。

要求出两个点之间的距离，可以先找到对应的栅栏的起始点，然后计算它们之间的距离 $d$，即 `dis[y]-dis[x]`（如果 $y$ 在 $x$ 前面则需要交换这两个点），再分别计算这两个点到栅栏起始点的距离 $dis_1,dis_2$，距离就是 $d-dis_1+dis_2$。

最后只需要输出 $\max(d-dis_1+dis_2,dis_n-(d-dis_1+dis_2))$ 即可。

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int cald(int xa,int ya,int xb,int yb){
	return abs(xa-xb+ya-yb);
}
struct point{
	int x,y,n;
}pt[200005],lp[1005][1005];
int dis[200005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,p;cin>>n>>p;
	for(int i=1;i<=p;i++){
		cin>>pt[i].x>>pt[i].y;
		pt[i].n=i;
	}
	pt[0]=pt[p];
	for(int i=1;i<=p;i++){
		int lx=pt[i-1].x,ly=pt[i-1].y,nx=pt[i].x,ny=pt[i].y;
		dis[i]=dis[i-1]+cald(lx,ly,nx,ny);
		if(lx==nx){
			if(ly<ny){
				for(int j=ly;j<ny;j++){
					lp[nx][j].x=lx;
					lp[nx][j].y=ly;
					lp[nx][j].n=i-1;
				}
			}else{
				for(int j=ly;j>ny;j--){
					lp[nx][j].x=lx;
					lp[nx][j].y=ly;
					lp[nx][j].n=i-1;
				}
			}
		}else{
			if(lx<nx){
				for(int j=lx;j<nx;j++){
					lp[j][ny].x=lx;
					lp[j][ny].y=ly;
					lp[j][ny].n=i-1;
				}
			}else{
				for(int j=lx;j>nx;j--){
					lp[j][ny].x=lx;
					lp[j][ny].y=ly;
					lp[j][ny].n=i-1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		int xa,xb,ya,yb;cin>>xa>>ya>>xb>>yb;
		int lxa=lp[xa][ya].x,lxb=lp[xb][yb].x,lya=lp[xa][ya].y,lyb=lp[xb][yb].y;
		int lna=lp[xa][ya].n,lnb=lp[xb][yb].n;
		if(lna>lnb){
			swap(xa,xb);
			swap(ya,yb);
			swap(lxa,lxb);
			swap(lya,lyb);
			swap(lna,lnb);
		}
		int dis1=dis[lnb]-dis[lna];
		int disa=cald(xa,ya,lxa,lya);
		int disb=cald(xb,yb,lxb,lyb);
		int ans=abs(dis1-disa+disb);
		cout<<min(ans,dis[p]-ans)<<endl;
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：6)

需要我来讲一下铜组该怎么通过吗？

本题的不同位置个数是可以接受的，所以可以将轨迹描绘出来。

按读入顺序，从前一个点一格一格地跳到后一个点，将中间的所有点按读入顺序标号。

设总点数个数为 $cnt$，查询时的两点标号差的绝对值为 $k$，考虑到有两种可能的方向，那么答案为 $\min\{k,cnt-k\}$，时间 $O(nm+q)$，空间 $O(nm)$：
```cpp
int T,n,K,b[N],v[1005][1005],cnt,sx,sy;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,v1,v2;
    cin>>T>>n>>sx>>sy;
    x=sx,y=sy;
    for(i=1;i<n;++i){
        cin>>v1>>v2;
        while(x<v1)v[++x][y]=++cnt;
        while(x>v1)v[--x][y]=++cnt;
        while(y<v2)v[x][++y]=++cnt;
        while(y>v2)v[x][--y]=++cnt;
    }
    v1=sx,v2=sy;
    while(x<v1)v[++x][y]=++cnt;
    while(x>v1)v[--x][y]=++cnt;
    while(y<v2)v[x][++y]=++cnt;
    while(y>v2)v[x][--y]=++cnt;
    for(;T--;){
        cin>>x>>y>>l>>r;
        k=abs(v[x][y]-v[l][r]);
        k=min(k,cnt-k);
        printf("%d\n",k);
    }
    return 0;
}
```

---

## 作者：haozige (赞：5)

## 题意概括

给你 $P$ 个栅栏柱点（坐标）（输入时已保证前一个栅栏柱和这个栅栏柱的 $x$ 或 $y$ 相同且这两栅栏柱一定连接），连接所有栅栏柱形成一个闭环（连接线没有斜线），再进行 $N$ 次查询，每次查询给两个坐标（都在闭环上），问这两个坐标点在闭环上的最短路径。

## 思路

首先看到每个栅栏柱的 $x,y \le 10^3$，第一时间就可以想到我们可以建立一个二维数组，从第一个点开始模拟连接，在每个点上记录和第一个栅栏柱的距离，查询时使用已记录的前缀和来算出两点距离，所以题目可以分为两部分：计算前缀和 与 计算与查询。

### 第一部分：计算前缀和

前面我们已经确定了方法，也就是每个点的值为上一个点的值 $+1$，但是现在我们定义一个二维数组之后，就能看出问题了，前面我们用的一维的思路，没有考虑到上一个点的位置到底在这个点的哪个方向，换句话说，在原来的思路中没有考虑到题目中有上下左右的位置关系，不只是前和后（如图）。

![图一](https://cdn.luogu.com.cn/upload/image_hosting/w93rik47.png)

解决方案也很简单，上一个点的方位取决于上一个点和这个点所在的栅栏边的方位，而这个栅栏边的方位又取决于它两端的栅栏柱的位置关系，这意味着我们只要遍历每个栅栏柱点，然后对于每个栅栏柱点，再找到这个栅栏柱点的下一个栅栏柱点，就可以确定在这条边上的点的上一个点的方位了，最后就可以按照原来的思路处理了。

对于这一部分的代码，有三个细节还要注意一下：

1. 在回到第一个点之后（即遍历完毕），最后要定义一个 $cnt$ 变量，值为闭环上的所有点的数量总和，用处之后会说。

2. 最后一个栅栏柱点要特殊处理，它是连接第一个点的。

3. 连接每条边时，分析清楚自己的代码是包括前栅栏柱点还是后栅栏柱点，这两个栅栏柱点不能同时包括，否则会出现栅栏柱点被算两边或变为 $0$ 的情况，我这里建议只包括后栅栏柱点，会更好处理。

下面是我这部分的代码，时间复杂度 $O(闭环上的点的个数)$，（闭环上的点的个数 $\le 10^6$）。

```cpp
//fence数组为前缀和记录，这里建议大家这里写得时候最好写个函数，可读性会高些
for(int i=1;i<=p-1;i++){
		if(x[i]==x[i+1]){
			if(y[i]<y[i+1]){
				for(int j=y[i]+1;j<=y[i+1];j++) fence[x[i]][j]=fence[x[i]][j-1]+1;
			}else{
				for(int j=y[i]-1;j>=y[i+1];j--) fence[x[i]][j]=fence[x[i]][j+1]+1;
			}
		}else{
			if(x[i]<x[i+1]){
				for(int j=x[i]+1;j<=x[i+1];j++) fence[j][y[i]]=fence[j-1][y[i]]+1;
			}else{
				for(int j=x[i]-1;j>=x[i+1];j--) fence[j][y[i]]=fence[j+1][y[i]]+1;
			}
		}
	}
	if(x[p]==x[1]){
		if(y[p]<y[1]){
			for(int j=y[p]+1;j<=y[1];j++) fence[x[p]][j]=fence[x[p]][j-1]+1;
		}else{
			for(int j=y[p]-1;j>=y[1];j--) fence[x[p]][j]=fence[x[p]][j+1]+1;
		}
	}else{
		if(x[p]<x[1]){
			for(int j=x[p]+1;j<=x[1];j++) fence[j][y[p]]=fence[j-1][y[p]]+1;
		}else{
			for(int j=x[p]-1;j>=x[1];j--) fence[j][y[p]]=fence[j+1][y[p]]+1;
		}
	}
```

### 第二部分：计算与查询

第二部分相比于第一部分是简单很多的，因为已经处理好了前缀和，对于每次查询，只要用这两个点的前缀和相减，然后取绝对值就可以得出两点之间距离了，但同样的，这样也会出问题，试试用这种思路带入下面这个测试点：

```cpp
1 4
0 0
2 0
2 2
0 2
0 0 0 2
```
发现问题没，这样做会出现的问题是我们的求出来的距离不一定是最短路线，解决方法非常简单，记得上文的 $cnt$ 吗？这个时候它就有用了，因为对于闭环上的两个点是有两种走法的，所以只要用 $cnt$ 减去前面求出来的距离，然后比较这两个值，取较小值就好了。

下面是这一部分的代码：

```cpp
//这里写了个slove函数可读性更高
void slove(){
	int x1,x2,y1,y2;
	cin>>x1>>y1>>x2>>y2;
	int ans1=abs(fence[x1][y1]-fence[x2][y2]);
	int ans2=cnt-ans1;
	cout<<min(ans1,ans2)<<endl;
}
```

## 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,x[200005],y[200005],fence[1005][1005],cnt;
void slove(){
	int x1,x2,y1,y2;
	cin>>x1>>y1>>x2>>y2;
	int ans1=abs(fence[x1][y1]-fence[x2][y2]);
	int ans2=cnt-ans1;
	cout<<min(ans1,ans2)<<endl;
}
int main(){
	cin>>n>>p;
	for(int i=1;i<=p;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=p-1;i++){
		if(x[i]==x[i+1]){
			if(y[i]<y[i+1]){
				for(int j=y[i]+1;j<=y[i+1];j++) fence[x[i]][j]=fence[x[i]][j-1]+1;
			}else{
				for(int j=y[i]-1;j>=y[i+1];j--) fence[x[i]][j]=fence[x[i]][j+1]+1;
			}
		}else{
			if(x[i]<x[i+1]){
				for(int j=x[i]+1;j<=x[i+1];j++) fence[j][y[i]]=fence[j-1][y[i]]+1;
			}else{
				for(int j=x[i]-1;j>=x[i+1];j--) fence[j][y[i]]=fence[j+1][y[i]]+1;
			}
		}
	}
	if(x[p]==x[1]){
		if(y[p]<y[1]){
			for(int j=y[p]+1;j<=y[1];j++) fence[x[p]][j]=fence[x[p]][j-1]+1;
		}else{
			for(int j=y[p]-1;j>=y[1];j--) fence[x[p]][j]=fence[x[p]][j+1]+1;
		}
	}else{
		if(x[p]<x[1]){
			for(int j=x[p]+1;j<=x[1];j++) fence[j][y[p]]=fence[j-1][y[p]]+1;
		}else{
			for(int j=x[p]-1;j>=x[1];j--) fence[j][y[p]]=fence[j+1][y[p]]+1;
		}
	}
	cnt=fence[x[1]][y[1]];
	for(int i=1;i<=n;i++) slove();
    return 0;
}
```

---

## 作者：Dirge__ (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/P10275)

# 思路

## 一.先标记两点之间的距离
第 $i$ 次（$2 \le i \le p$）从输入的第 $i - 1$ 个点顺逆两个方向一格一格地跳到第 $i$ 点，对沿途的所有点对进行标记。

```cpp
for(int i = 1; i <= n + 1; i++)
{
	if(i < n + 1) cin >> X[i] >> Y[i];
	if(i == 1) continue;
	for(int x = X[i - 1] + 1; x <= X[i]; x++) 
		ans[x][Y[i]] = ans[x - 1][Y[i]] + 1;
	for(int x = X[i - 1] - 1; x >= X[i]; x--) 
		ans[x][Y[i]] = ans[x + 1][Y[i]] + 1;
	for(int y = Y[i - 1] + 1; y <= Y[i]; y++) 
		ans[X[i]][y] = ans[X[i]][y - 1] + 1;
	for(int y = Y[i - 1] - 1; y >= Y[i]; y--) 
		ans[X[i]][y] = ans[X[i]][y + 1] + 1;
}
```
## 二.计算整个路程的长度，并输出
 从 ($x1,y1$) 点到 ($x2,y2$) 点一共有顺时针和逆时针两种走法，
 
顺 $= |ans[x1][y1] - ans[x2][y2]|$;

逆 $= l - |ans[x1][y1] - ans[x2][y2]|$；

```cpp
for(int i = 1; i <= m; i++)
{
	int x,y,u,v;
	cin >> x >> y >> u >> v;
	cout << min(abs(ans[x][y] - ans[u][v]),l - abs(ans[x][y] - ans[u][v])) << endl;
}
```


---

# 代码


```cpp
#include <iostream>
using namespace std;

int ans[1005][1005],X[200005],Y[200005];;

int len(int x,int y,int xx,int yy)
{
	return abs(x - xx) + abs(y - yy);
}

int main()
{
    int n,m;
	cin >> m >> n;
	for(int i = 1; i <= n + 1; i++)
	{
        if(i < n + 1) cin >> X[i] >> Y[i];
		if(i == 1) continue;
		for(int x = X[i - 1] + 1; x <= X[i]; x++) 
			ans[x][Y[i]] = ans[x - 1][Y[i]] + 1;
		for(int x = X[i - 1] - 1; x >= X[i]; x--) 
			ans[x][Y[i]] = ans[x + 1][Y[i]] + 1;
		for(int y = Y[i - 1] + 1; y <= Y[i]; y++) 
			ans[X[i]][y] = ans[X[i]][y - 1] + 1;
		for(int y = Y[i - 1] - 1; y >= Y[i]; y--) 
			ans[X[i]][y] = ans[X[i]][y + 1] + 1;
	}
	int l = ans[X[n]][Y[n]] + len(X[1],Y[1],X[n],Y[n]);
	for(int i = 1; i <= m; i++)
	{
		int x,y,u,v;
		cin >> x >> y >> u >> v;
		cout << min(abs(ans[x][y] - ans[u][v]),l - abs(ans[x][y] - ans[u][v])) << endl;
	}
	return 0;
}
```


---

---

## 作者：chinazhanghaoxun (赞：2)

## 分析

本题的思路其实就是一个简单的模拟，可以在输入过程中循环得到上一个点到这一个点中间经过的所有整数点，然后对它们进行编号就可以了。

举个例子，比如围栏是这样的：
![栅栏的形状](https://cdn.luogu.com.cn/upload/image_hosting/qe1de10n.png)

我要从 3 号点散步到 12 号点，那么我就有如图的两种方式：
![这两种方式](https://cdn.luogu.com.cn/upload/image_hosting/qug3lppf.png)

所以，我们就直接用 $12-3=9$ 得到逆时针散步的距离，接下来和顺时针行走的 $14-9=5$ 进行比较，很明显，顺时针更近，那么就选择顺时针的距离作为答案。
## 代码

这道题根据思路直接模拟即可，代码就不放了。

---

## 作者：ChenYanlin_20 (赞：1)

### 思路：
观察题目发现 $x , y$ 均小于 $1000$，总共点不超过 $1000000$，可以直接在路径上每个点存入顺序编号，查询时编号之差就是距离，由于栅栏是环形，所以有两条路径。

### CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
const int N=2e5+10;
int x[N],y[N];
const int M=1e3+10;
int f[M][M]; 
signed main(){
	int n,p;
	cin>>n>>p;
	int top=0;
	for(int i=1;i<=p;i++){
		cin>>x[i]>>y[i];
		if(i>=2){
			if(x[i]==x[i-1]){
				if(y[i]>y[i-1]){
					for(int j=y[i-1];j<y[i];j++)
						f[x[i]][j]=++top;
				}
				else
					for(int j=y[i-1];j>y[i];j--)
						f[x[i]][j]=++top;
			}
			else{
				if(x[i]>x[i-1]){
					for(int j=x[i-1];j<x[i];j++)
						f[j][y[i]]=++top;
				}
				else
					for(int j=x[i-1];j>x[i];j--)
						f[j][y[i]]=++top;
			}
		}
	}
	
	if(x[1]==x[p]){
		if(y[1]>y[p]){
			for(int j=y[p];j<y[1];j++)
				f[x[1]][j]=++top;
		}
		else
			for(int j=y[p];j>y[1];j--)
				f[x[1]][j]=++top;
	}
	else{
		if(x[1]>x[p]){
			for(int j=x[p];j<x[1];j++)
				f[j][y[1]]=++top;
		}
		else
			for(int j=x[p];j>x[1];j--)
				f[j][y[1]]=++top;
	}
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int ans=abs(f[a][b]-f[c][d]);
//		cout<<ans<<' ';
		cout<<min(ans,top-ans)<<'\n';
	}
	return 0;
}

```

---

## 作者：complete_binary_tree (赞：1)

比 $\text{T1}$ 简单多了。

暴力枚举这些栅栏怎么围成四边形，然后在栅栏经过的点按顺序标号，那么这样我们就能知道两个点之间的一条路径的长度（标号相减）了。然后和另一条路径选小的输出即可。

时间复杂度 $O(|x|^2)$。（$|x|$ 表示 $x$ 最大最小值的差，也就是 $1000$）代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m;

map<pair<int, int>, int> mp;
int cnt = 0;
int lx, ly, x, y, _x, _y;

int main(){
	scanf("%d%d", &n, &m);
	scanf("%d%d", &lx, &ly);
	mp[make_pair(lx, ly)] = ++cnt;
	_x = lx, _y = ly;
	for(int i = 2; i <= m; ++i){
		scanf("%d%d", &x, &y);
      //神秘的寻找方法
		if(lx == x){
			if(y > ly){
				for(int j = ly + 1; j <= y; ++j){
					mp[make_pair(x, j)] = ++cnt;
				}
			}
			else{
				for(int j = ly - 1; j >= y; --j){
					mp[make_pair(x, j)] = ++cnt;
				}
			}
		}
		else if(ly == y){
			if(x > lx){
				for(int j = lx + 1; j <= x; ++j){
					mp[make_pair(j, y)] = ++cnt;
				}
			}
			else{
				for(int j = lx - 1; j >= x; --j){
					mp[make_pair(j, y)] = ++cnt;
				}
			}
		}
		lx = x, ly = y;
	}
	x = _x, y = _y;
	if(lx == x){
		if(y > ly){
			for(int j = ly + 1; j < y; ++j){
				mp[make_pair(x, j)] = ++cnt;
			}
		}
		else{
			for(int j = ly - 1; j > y; --j){
				mp[make_pair(x, j)] = ++cnt;
			}
		}
	}
	else if(ly == y){
		if(x > lx){
			for(int j = lx + 1; j < x; ++j){
				mp[make_pair(j, y)] = ++cnt;
			}
		}
		else{
			for(int j = lx - 1; j > x; --j){
				mp[make_pair(j, y)] = ++cnt;
			}
		}
	}
  //O(1) 处理询问
	for(int i = 1; i <= n; ++i){
		int x, y, xx, yy;
		scanf("%d%d%d%d", &x, &y, &xx, &yy);
		printf("%d\n", min(abs(mp[make_pair(x, y)] - mp[make_pair(xx, yy)]), cnt - abs(mp[make_pair(x, y)] - mp[make_pair(xx, yy)])));
	}
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：1)

~~煎蛋题（煎个鸡蛋就好了）~~

第 $i$ 次 $(2 \leq i \leq P)$ 从输入的第 $i - 1$ 个点一格一格地跳到第 $i$ 个点，对沿途的所有点对进行标记，并从 $1$ 开始依次编号。特别地，输入的第 $P$ 个点还要标记回第 $1$ 个点。

设沿途中总共有 $cnt$ 个点，则从第 $i$ 个点到第 $j$ 个点的最短距离是 $\min(\operatorname{abs}(j - i), cnt - \operatorname{abs}(j - i))$。（正着走和反着走嘛）

代码过丑，不放了（相信大家已经会写代码了，跑路！）

---

## 作者：11514zbs (赞：0)

~~又来水题解喽~~ 

这里给出解题思路，代码请参阅其他题解。

1. 观察题面，不难发现，奶牛只有 $2$ 两条行走路线。

2. 观察数据，我们会发现因为横纵坐标 $x, y$ 满足 $x, y \le 1000$ ，所以我们可以一边输入，一边模拟奶牛的 $2$ 条行走路线。其中，我们模拟的时候要按照输入的顺序把数组 $a$ 的第 $x_i, y_i$ 项分别赋值为第 $1$ 根栅栏按照输入顺序与第 $i$ 根栅栏的距离。

3. 最后，对于每次询问只需要 $O(1)$ 输出即可。

另外，对于计算部分，我们令 $t_1 = |a_{x_1, y_1} - a_{x_2, y_2}|$ 。因为奶牛有两条行走路线，所以我们还要令 $t_2 = |x_{P - 1} - x_P| + |y_{P - 1} - y_P| + a_{x_{P - 1}, y_{P - 1}} - 1 - t_1$ ，我们输出的应为 $\min(t_1, t_2)$ 。

代码的话因为比较好写，所以就不放了。

> 我讲的这么详细你们应该听得懂吧。

 ~~本蒟蒻的第四篇题解awa~~

---

## 作者：HHC883 (赞：0)

# 题目分析
容易发现，栅栏的长度最大为 $1000^2$（因为由数据范围，本题坐标系当中只有这么多个整数点），即栅栏上最多只有 $1000000$ 个点，所以可以让程序从第一个点开始，按顺序“走”一遍这个栅栏，并在沿途中统计按这个顺序（这个顺序取决于输入中点给出的顺序）从第一个点到栅栏上每一个点的距离。接着，令 $dis_1$ 为按这个顺序从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 的距离，$dis_2$ 为按另一个顺序从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 的距离，则 $dis_2$ 就等于栅栏长度减去 $dis_1$，而栅栏长度可以在“走”一遍的过程中得出，$dis_1$ 可以利用类似于前缀和的思路，用从第一个点到 $(x_2,y_2)$ 的距离减去从第一个点到 $(x_1,y_1)$ 的距离，就是从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ 的距离。注意，这个值可能是负数，所以要取绝对值。最后，取 $dis_1$ 和 $dis_2$ 的最小值即可得到答案。

时间复杂度是 $O(\max(x)\max(y)+N)$。所以时间限制完全可以是 $1.00s$，我也搞不明白出题人什么要开到 $2.00s$。
# 参考代码
```cpp
#include<iostream>
using namespace std;
int n,p,dis[1005][1005];
struct{
	int x,y;
} ps[(int)2e5+5];
int sign(int x){return x>0?1:-1;}
int abs_(int x){return x>0?x:-x;}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>p;
	for(int i=1;i<=p;i++) cin>>ps[i].x>>ps[i].y;
	ps[p+1]=ps[1]; //将最后一个点当成第一个点，实现闭环
	for(int i=2;i<=p+1;i++){
		if(ps[i].x==ps[i-1].x){
			int s=sign(ps[i].y-ps[i-1].y);
			for(int j=ps[i-1].y+s;j!=ps[i].y+s;j+=s){
				dis[ps[i].x][j]=dis[ps[i].x][j-s]+1;
			}
		}
		if(ps[i].y==ps[i-1].y){
			int s=sign(ps[i].x-ps[i-1].x);
			for(int j=ps[i-1].x+s;j!=ps[i].x+s;j+=s){
				dis[j][ps[i].y]=dis[j-s][ps[i].y]+1;
			}
		}
	}
	int x0=ps[1].x,y0=ps[1].y; //x0和y0是第一个点的横纵坐标
	int x1,y1,x2,y2,dis1,dis2;
	while(n--){
		cin>>x1>>y1>>x2>>y2;
		dis1=abs_(dis[x1][y1]-dis[x2][y2]),dis2=dis[x0][y0]-dis1; //dis[x0][y0]就是栅栏的长度
		cout<<min(dis1,dis2)<<endl;
	}
	return 0;
}
```

---

