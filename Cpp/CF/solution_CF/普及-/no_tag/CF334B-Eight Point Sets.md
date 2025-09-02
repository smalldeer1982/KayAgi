# Eight Point Sets

## 题目描述

Gerald is very particular to eight point sets. He thinks that any decent eight point set must consist of all pairwise intersections of three distinct integer vertical straight lines and three distinct integer horizontal straight lines, except for the average of these nine points. In other words, there must be three integers $ x_{1},x_{2},x_{3} $ and three more integers $ y_{1},y_{2},y_{3} $ , such that $ x_{1}&lt;x_{2}&lt;x_{3} $ , $ y_{1}&lt;y_{2}&lt;y_{3} $ and the eight point set consists of all points $ (x_{i},y_{j}) $ ( $ 1<=i,j<=3 $ ), except for point $ (x_{2},y_{2}) $ .

You have a set of eight points. Find out if Gerald can use this set?

## 样例 #1

### 输入

```
0 0
0 1
0 2
1 0
1 2
2 0
2 1
2 2
```

### 输出

```
respectable
```

## 样例 #2

### 输入

```
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0
```

### 输出

```
ugly
```

## 样例 #3

### 输入

```
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
```

### 输出

```
ugly
```

# 题解

## 作者：dthythxth_Huge_Brain (赞：5)

## 题目大意

> 给出 $8$ 个点的坐标，求出这 $8$ 个点是否像下面图样：

![](https://cdn.luogu.com.cn/upload/image_hosting/sp8eenij.png)

我们只需要先将这 $8$ 个点排序，对于两个点，当横坐标小于另一个点，函数值返回 $1$，否则当横坐标相等时，若纵坐标小于另一个点，也返回 $1$，否则返回 $0$，可以重载运算符：
```cpp
bool operator<(st u,st v){
    if(u.x<v.x)return true;
    else if((u.x==v.x)&&(u.y<v.y))return true;
    return false;
}
```
接下来判断一下是否满足条件，若有两点在同一位置，即不满足条件，接着判断 $8$ 个点是否为三个不同的横坐标和三个不同的纵坐标任意组合而成的 $9$ 个点中的外围 $8$ 个点，即可得出判断函数：
```
void solve(){
	for(int i=1;i<=8;i++)for(int j=1;j<=8;j++)if((i!=j)&&(a[i].x==a[j].x)&&(a[i].y==a[j].y)){
		puts("ugly");
		exit(0);
	}
	if((a[3].y!=a[5].y)||(a[8].y!=a[3].y)||(a[2].y!=a[7].y)||(a[2].y!=a[7].y)||(a[1].x!=a[2].x)||(a[2].x!=a[3].x)||(a[4].x!=a[5].x)||(a[4].x!=a[5].x)||(a[6].x!=a[8].x)||(a[7].x!=a[8].x)||(a[1].y!=a[4].y)||(a[1].y!=a[6].y))puts("ugly");
	else puts("respectable");
}
```
这样就能完美 AC 这题。![](https://cdn.luogu.com.cn/upload/image_hosting/zvfkt0x8.png)

---

## 作者：Alex_Wei (赞：5)

模拟

如果这八个点是 $respectable$ 的，那么这八个点一定长成这样

![](https://cdn.luogu.com.cn/upload/pic/72353.png)

我们把这八个点从上到下，从左到右标号，然后在两两判断是否满足条件即可

$$x_0=x_1,x_1=x_2,x_3=x_4,x_5=x_6,x_6=x_7$$

$$y_0=y_3,y_3=y_5,y_1=y_6,y_2=y_4,y_4=y_7$$

注意还要先计算一下**不同横坐标和纵坐标是否有且只有三个（很重要）**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
}c[8];
bool cmp(node a,node b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
//从上到下，从左到右
int x,y,a[1000002],b[1000002];
int main()
{
	for(int i=0;i<8;i++)
		cin>>c[i].x>>c[i].y;
	for(int i=0;i<8;i++)
		x+=!a[c[i].x],a[c[i].x]++,y+=!b[c[i].y],b[c[i].y]++;//求出不同的纵，横坐标个数
	sort(c,c+8,cmp);//排序（相当于依次编号） 
	if(x==3&&y==3&&c[0].x==c[1].x&&c[1].x==c[2].x&&c[3].x==c[4].x&&c[5].x==c[6].x&&c[6].x==c[7].x&&
	c[0].y==c[3].y&&c[3].y==c[5].y&&c[1].y==c[6].y&&c[2].y==c[4].y&&c[4].y==c[7].y)cout<<"respectable";
	else cout<<"ugly";
	return 0;
}
```


---

## 作者：conti123 (赞：4)

### 分析

题目大意：**很重要！**

杰拉尔德对八分制非常挑剔。他认为，任何像样的八点集都必须由三条不同的整数垂直直线和三条不同整数水平直线的所有成对交集组成，除了这九点的平均值。换句话说必须有三个整数 $x_{1},x_{2},x_{3}$ 和另外三个整数 $y_{1},y_{2},y_{3}$，使得 $x_{1}<x_{2}<x_{3}$ 并且 $y_{1}<y_{2}<y_{3}$，并且八点集合由所有点 $(x_{i},y_{j})$ 除了 $(x_{2},y_{2})$。

你有一套八分。看看 Gerald 能不能用这套？

假设三个 $x$ 分别为 $2,4,7$，三个 $y$ 分别为 $3,5,6$，那么你会得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ev5npd0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其中，红点是合法的，蓝点是不合法的。

而我们的问题就是求给出的 $8$ 个点能否组成如图的红色点。

我们来分析一下 $8$ 个点合法的条件：

1. $8$ 个点不能有重复的（否则就没有 $8$ 个不重复的点了）。

2. **必须由三条不同的整数垂直直线和三条不同整数水平直线的所有成对交集组成。**

可以得出 $8$ 个点组成了一个矩形。

进一步得出 $8$ 个点的坐标值必须满足以下条件：$x$ 或 $y$ 的值是最小的**或** $x$ 或 $y$ 的值是最大的。

3. $x$ 和 $y$ 值的不同的个数必须恰好有 $3$ 个，这样才能满足上图。

了解完这些之后我们就可以打代码了。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int maxx=-1,minx=1e7,maxy=-1,miny=1e7,x[10],y[10];
set<int>countx,county;
set<pair<int,int>>countxy;//set能自动去重 
signed main()
{
	for(int i=1;i<=8;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		maxx=max(maxx,x[i]),maxy=max(maxy,y[i]);
		minx=min(minx,x[i]),miny=min(miny,y[i]);
		countx.insert(x[i]),county.insert(y[i]);
		countxy.insert(make_pair(x[i],y[i]));
	}
	if(countx.size()!=3||county.size()!=3||countxy.size()!=8)
	{
		puts("ugly");
		return 0;
	}
	for(int i=1;i<=8;i++)
		if(x[i]!=minx&&x[i]!=maxx&&y[i]!=miny&&y[i]!=maxy)
		{
			puts("ugly");
			return 0;
		}
	puts("respectable");
}
```

---

## 作者：yutong_Seafloor (赞：2)

# [题目在这里 · Eight Point Sets CF334B](https://www.luogu.com.cn/problem/CF334B)
### 题目简要：
有八个坐标，现在这八个坐标要组成一个四边形，判断能不能组成长方形。

### 题意分析
长方形都见过吧，四个端点四个边，为了能够组成长方形，它必定有四个端点（~~废话~~），剩下的四个点一定在四边上，搬一张图过来（画的不好勿喷）：
![](https://cdn.luogu.com.cn/upload/image_hosting/zr6cdjvu.png)

它的四个端点的坐标是这**八个坐标中横坐标和纵坐标中最大或者最小组成的**，在四边上的点的横纵坐标一定有一个是 $xmax$，$xmin$，$ymax$，$ymin$ 四个中的一个，依照这个我们写代码。
## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int i,j,xmax=-1,ymax=-1,xmin=100010,ymin=100010;
int xz,yz,gx[10],gy[10];
struct yt
{
	int x,y;
}zb[10];
int main()
{
	for(i=1;i<=8;i++)
	{
		cin>>zb[i].x>>zb[i].y;
		xmax=max(xmax,zb[i].x);//四端点坐标 
		ymax=max(ymax,zb[i].y);
		xmin=min(xmin,zb[i].x);
		ymin=min(ymin,zb[i].y);
	}
	for(i=1;i<=8;i++)//判断个数 
	{
		if(gx[zb[i].x]==0)
		xz++,gx[zb[i].x]=1;
		if(gy[zb[i].y]==0)
		yz++,gy[zb[i].y]=1;
	}
	if(xz!=3 || yz!=3)
	{
		cout<<"ugly";
		return 0;
	}
	else
	{
		for(i=1;i<=8;i++) 
		if(zb[i].x==xmax || zb[i].x==xmin || zb[i].y==ymax || zb[i].y==ymin)
		continue;
		else
		{
			cout<<"ugly";
			return 0;
		}	
		cout<<"respectable";
	}
}//by·yutong_Seafloor 
``` 
最后一定要记得数 $x$ 坐标的种数和 $y$ 坐标的种数，不是 $3$ 的就不合题意了。

---

## 作者：Obviathy (赞：1)

## 前言：
~~看到题解区只有一篇题解，好孤独~~

这道题我调了好久，~~大模拟不擅长~~
## 解题思路：
其实思路很简单，照着题意模拟就行。

我们只需要统计不同种类的横纵坐标，如果统计过后的坐标种类数大于 $3$，直接输出 $\texttt{"ugly"}$ 就行。

如果种类数刚好都是三，首先我们要把统计下来的不同种类的横纵坐标排个序（这一步很重要，因为题目中的九个点中最中间的那一个点是不能有的，所以要保证记录的第二个横纵坐标是所有坐标中最中间那个，不然会WA第 $25$ 个点）然后枚举这三种坐标的九种排列方法，如果这个坐标是边缘上的，判断有没有出现过，如果没有就输出 $\texttt{"ugly"}$，如果这个坐标是正中间的的，判断有没有出现过，如果有就输出 $\texttt{"ugly"}$。

最后才输出 $\texttt{"respectable"}$。

## AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[10],y[10],cntx,cnty,tot1,tot2,xx[10],yy[10]; 
bool v1[1000001],v2[1000001];
bool check(int u,int v){
	int a = xx[u],b = yy[v];
	for(int i = 1;i <= 8;i ++)
		if(x[i] == a && y[i] == b)return 1;
	return 0;
}
int main(){
	for(int i = 1;i <= 8;i ++){
		cin >> x[i] >> y[i];
		if(v1[x[i]]!=1){
			cntx++;
			xx[++tot1]=x[i];
		}
		if(v2[y[i]]!=1){
			cnty++;
			yy[++tot2]=y[i];
		}
		v1[x[i]] = 1;
		v2[y[i]] = 1;	
	}
	if(cntx!=3||cnty!=3){
		cout<<"ugly"<<endl;
		return 0;
	}
	sort(xx+1,xx+4);
	sort(yy+1,yy+4);
//	for(int i = 1;i <= 3;i ++){
//		for(int j = 1;j <= 3;j ++){
//			cout<<"("<<xx[i]<<","<<yy[j]<<") ";
//		}
//		cout<<endl;
//	}
	for(int i = 1;i <= 3;i ++){
		for(int j = 1;j <= 3;j ++){
			if(i!=2||j!=2){
				if(!check(i,j)){
					cout<<"ugly"<<endl;
					return 0;
				}
			}else{
				if(check(i,j)){
					cout<<"ugly"<<endl;
					return 0;
				}
			}
		}
	}
	cout<<"respectable"<<endl;
	return 0;
}
```

（抄袭题解可耻！你我共同抵制！）


---

## 作者：ztyo_zysclown (赞：1)

由于此题的只需输入最中间那个点的周围八个点，所以我们可以根据这八个点的坐标画一个矩阵，即
```
1  2  3
4  0  5
6  7  8
```
于是我们可以发现 $1$，$2$，$3$ 这三个点的横坐标是相同的，$6$，$7$，$8$ 这三个点的横坐标是相同的，$4$，$5$ 同理。
$1$，$4$，$6$ 和 $3$，$5$，$8$ 及 $2$，$7$ 的纵坐标是相同的，如果以上条件有任意一个不满足，按照题意输出即可。

下面是代码
```
#include<bits/stdc++.h>
using namespace std;
struct re{
	int x;//横坐标 
	int y;//纵坐标 
}a[15];
bool cmp(re x,re y){
	if(x.x!=y.x){
		return x.x<y.x;
	}
	else{
		return x.y<y.y;
	}
}
int main(){
	for(int i=1;i<=8;i++){
		cin>>a[i].x>>a[i].y;
	} 
	sort(a+1,a+8+1,cmp);
	if(a[1].x!=a[2].x||a[2].x!=a[3].x||a[7].x!=a[8].x||a[4].x!=a[5].x||a[6].x!=a[7].x){
		cout<<"ugly";
		return 0;
	}//判断横坐标是否合法
	if(a[1].y!=a[4].y||a[4].y!=a[6].y||a[2].y!=a[7].y||a[3].y!=a[5].y||a[5].y!=a[8].y){
		cout<<"ugly";
		return 0;
	}//判断纵坐标是否合法
	cout<<"respectable";
	return 0;//完结撒花
}
```


---

## 作者：byft (赞：0)

一道巨水题 ~~为什么我每次看到数据范围不大就想暴搜~~


总共 $3$ 行 $3$ 列，在中间的 $1$ 行 $1$ 列特判，其他看有没有输入即可

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[5],y[5];
int a[10][2];
int main(){
	memset(x,0x3f,sizeof(x));//一次性赋值，将所有元素赋值0x3f3f3f3f
	memset(y,0x3f,sizeof(y));
	for(int i=1;i<=8;i++)
	{
		int X,Y;
		cin>>X>>Y;
		a[i][1]=X;
		a[i][2]=Y;
		for(int j=1;j<=3;j++)
		{
			if(x[j]==0x3f3f3f3f)//如果没有这个坐标
			{x[j]=X;break;}
			if(x[j]==X) break;//如果坐标已经出现
		}
		for(int j=1;j<=3;j++)
		{
			if(y[j]==0x3f3f3f3f)
			{y[j]=Y;break;}
			if(y[j]==Y) break;
		}
	}
	sort(x+1,x+4);//已经懒到3个数都要sort了(
	sort(y+1,y+4);
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			if(i!=2 || j!=2)//特判i=2和j=2
			{
				bool b=1;
				for(int k=1;k<=8;k++)
				{
					if(a[k][1]==x[i] && a[k][2]==y[j])//存在坐标
					{
						b=0;
					}
				}
				if(b) {cout<<"ugly";return 0;}//不存在坐标，输出ugly
			}
		}
	}
	cout<<"respectable";//8个点都存在，输出respectable
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

找个规律即可。

按题目要求，八个点必围成一个圈，设圈在中间的那个点是 $(x, y)$ 那八个点必为 $(x - 1, y - 1)(x - 1, y)(x - 1, y + 1)(x, y - 1)(x, y + 1)(x + 1, y - 1)(x + 1, y)(x + 1, y + 1)$。

我们排个序，会发现 $(1,2,3)$ 的横坐标一样，$(4,5)$ 的横坐标一样，$(7,8,9)$ 的横坐标一样。$(1,4,6)$ 的纵坐标一样，$(2,7)$ 的纵坐标一样，$(3,5,8)$ 的纵坐标一样。

最后模拟即可。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x, y;
}a[15];
bool cmp(node q, node w){
	if(q.x != w.x){
		return q.x < w.x;
	}
	else{
		return q.y < w.y;
	}
}
map<int, int> mp, ap;
int main(){
	for(int i = 1; i <= 8; i++){
		cin >> a[i].x >> a[i].y;
		mp[a[i].x]++;
		ap[a[i].y]++;
	}
	sort(a + 1, a + 9, cmp);
	if(a[1].x != a[2].x || a[2].x != a[3].x || a[4].x != a[5].x || a[6].x != a[7].x || a[7].x != a[8].x){
		cout << "ugly";
		return 0;
	}
	if(a[1].y != a[4].y || a[4].y != a[6].y || a[2].y != a[7].y || a[3].y != a[5].y || a[5].y != a[8].y){
		cout << "ugly";
		return 0;
	}
	cout << "respectable";
	return 0;
} 
```

---

