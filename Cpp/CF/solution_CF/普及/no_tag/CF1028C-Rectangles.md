# Rectangles

## 题目描述

### 题目大意

在平面直角坐标系中给定$n$个矩形，要求找到一个点$(x,y)$，这个点在至少$n-1$个给定矩形的内部或边界

## 样例 #1

### 输入

```
3
0 0 1 1
1 1 2 2
3 0 4 1
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
3
0 0 1 1
0 1 1 2
1 0 2 1
```

### 输出

```
1 1
```

## 样例 #3

### 输入

```
4
0 0 5 5
0 0 4 4
1 1 4 4
1 1 4 4
```

### 输出

```
1 1
```

## 样例 #4

### 输入

```
5
0 0 10 8
1 2 6 7
2 3 5 6
3 4 4 5
8 1 9 2
```

### 输出

```
3 4
```

# 题解

## 作者：E1_de5truct0r (赞：2)

## 思路

- 如果是 $n$ 个矩形相交，那么我们只需要找到 $\max x_1, \max y_1, \min x_2 $ 以及 $\min y_2$ 这四个值组成的矩形。

	如果您无法理解，可以参考下图：
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/ykodhpfm.png)
    其中，红色的边 $y$ 坐标为 $\min y_2$ ，绿色的边 $x$ 坐标为 $\min x_2$ ，黄色的边 $y$ 坐标为 $\max y_1$ ，蓝色的边 $x$ 坐标为 $\max x_1$ 。
    
    它们将会围成一个**可能存在**的矩形。我们只需要判断矩形存不存在即可知道是否有符合要求的点。

- 现在是 $n - 1$ 个矩形相交，怎么办呢？

	其实，如果含有最大值或最小值的矩形被删去，那么我们**使用 次大/小值 代替 最大/小值 进行计算即可**。
    
   所以，对于每一个坐标，我们只需要维护一个最大/小值和一个次大/小值即可。至于判断，我们需要记录最大值包含在哪个矩形里。最后枚举一遍删去哪一个矩形，判断该矩形是否会影响到最大/小值的使用即可。
   
   我的代码里用了四个一维数组代替变量，因为变量太麻烦了。代码里，$a_1,b_1,c_1,d_1$ 存储最大/小值，$a_2,b_2,c_2,d_2$ 存储次大/小值，$a_4,b_4,c_4,d_4$ 存储每个最大/小值包含在哪一个矩形中（编号）。

这样的话，预处理 $O(n)$，枚举+计算 $O(n)$ ，总复杂度为 $O(n)$ ，$n \leq 132674$ （什么奇怪的数字），可以通过本题。

那么，这道题就算是做完啦~

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[6],b[6],c[6],d[6];
signed main()
{
	int n,e,f,g,h; scanf("%lld",&n);
	for(int i=1;i<=2;i++) a[i]=b[i]=-1e9-1,c[i]=d[i]=1e9+1; //记得赋初值！
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&e,&f,&g,&h);
		if(e>=a[2])
			if(e>=a[1]) a[2]=a[1],a[1]=e,a[4]=i;
			else a[2]=e;
		if(f>=b[2])
			if(f>=b[1]) b[2]=b[1],b[1]=f,b[4]=i;
			else b[2]=f;
		if(g<=c[2])
			if(g<=c[1]) c[2]=c[1],c[1]=g,c[4]=i;
			else c[2]=g;
		if(h<=d[2])
			if(h<=d[1]) d[2]=d[1],d[1]=h,d[4]=i;
			else d[2]=h;
		//以上为预处理最大和次大值。
	}
	
	for(int i=1;i<=n;i++)
	{
		int A,B,C,D;
		A=(i==a[4])?a[2]:a[1]; //判断用最大还是次大；
		B=(i==b[4])?b[2]:b[1];
		C=(i==c[4])?c[2]:c[1];
		D=(i==d[4])?d[2]:d[1];
		if(C>=A && D>=B) //判断矩形是否存在
		{
			printf("%lld %lld",A,B);
			return 0;
		}
	}
	return 0;
}
```

$$\text{-------------- The End --------------}$$

$$\text{thx for reading}$$

---

## 作者：npqenqpve (赞：1)

在完成这道题之前先想一个问题，如何求多个矩形的公共部分，不妨思考这个问题在数轴上的版本：如何求多个线段的公共部分，这个问题是显然的，答案为 $[\max\{l_i\},\min\{r_i\}]$ ，那么平面直角坐标系上的也是类似的，
![](https://cdn.luogu.com.cn/upload/image_hosting/w91yj4ba.png?x-oss-process=image/resize,m_lfit,h_1700,w_2205)

如图，显然是 $EH$ ，$DC$ ，$JK$ 中最靠下的边， $HG$ ，$KL$ ，$CB$ 中最靠左的边，以此类推，这些边组成的矩形，那么在这个正方形上的点显然都是满足要求的，但是，这个正方形不一定存在，可以考虑枚举删去的矩形，计算剩下的矩形的公共部分是否存在。

上面的方法需要每次计算公共部分，复杂度太差；

考虑对其进行优化，可以先求出所有最值的前缀和后缀，需要求 $8$ 个，上下左右四个方向各两个，然后对删除第 $i$ 个只需要对 $l[i-1]$ 与 $r[i+1]$ 取 $\min$ 或 $\max$ ，总复杂的 $O(n)$ 。

部分参考同机房大佬[@wz20201136](https://www.luogu.com.cn/user/448159)的方法。

```cpp
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i]>>x[i]>>y[i];
	s13[0]=s14[0]=s23[n+1]=s24[n+1]=INT_MAX;
	s11[0]=s12[0]=s21[n+1]=s22[n+1]=-INT_MAX;
	for(int i=1;i<=n;i++)
	{
		s11[i]=max(s11[i-1],a[i]);
		s12[i]=max(s12[i-1],b[i]);
		s13[i]=min(s13[i-1],x[i]);
		s14[i]=min(s14[i-1],y[i]);
	}
	for(int i=n;i>=1;i--)
	{
		s21[i]=max(s21[i+1],a[i]);
		s22[i]=max(s22[i+1],b[i]);
		s23[i]=min(s23[i+1],x[i]);
		s24[i]=min(s24[i+1],y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		int A=max(s11[i-1],s21[i+1]);
		int B=max(s12[i-1],s22[i+1]);
		int C=min(s13[i-1],s23[i+1]);
		int D=min(s14[i-1],s24[i+1]);
		if(A<=C&&B<=D)
		{
			cout<<A<<' '<<B;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：BLUESKY007 (赞：0)

~~(这道题太简单啦...虽说我锤了一上午都没过...我能说这道题和$CF1029C$算是同一道题吗...）~~  
按照时间顺序来说...$CF1029$在$CF1028$前面(而且$CF1029$还是$Div3$),前后没差多长时间就惊现高相似度题目~~(所以CF是有多迫切想让大家上分)~~  
[CF1029C传送门](https://www.luogu.org/problemnew/show/CF1029C)  
两道题的唯一差别就是一个是一维,一个是二维~~(我是不是应该猜一下$CF1036C$会出一个三维的)~~,都是范围覆盖,和$CF1029C$一样,只需要确定最严格的边界限制,题目要求输出任意一个在至少$n-1$个矩形内的点,也即可以删去一个矩形,输出剩下$n-1$个矩形的交集内的任意点(在此直接选用交集左下角的点)  
根据题目条件,一定存在一些满足条件的点,所以删去的矩形应该是与其他$n-1$个矩形的交集没有公共部分的矩形,所以和$CF1029C$中的处理方式相似,在造成最严格限制的至多四个矩形中枚举删除即可,若删除后剩下的$n-1$个矩形交集不为空即可输出答案(如果$n$个矩形的交集不为空可以不删除)  
下面放代码$\downarrow\downarrow\downarrow$  
```cpp
#include<cstdio>//CF1028C
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;

int n;

struct lborder{
	int x,id;
	bool operator<(const lborder&rhs)const{
		return x<rhs.x;
	}
};

struct rborder{
	int x,id;
	bool operator<(const rborder&rhs)const{
		return x>rhs.x;
	}
};

lborder lbx,lby;rborder rbx,rby;

priority_queue<lborder>ql[2];
priority_queue<rborder>qr[2];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&lbx.x,&lby.x,&rbx.x,&rby.x);
		lbx.id=rbx.id=lby.id=rby.id=i;
		ql[0].push(lbx);
		qr[0].push(rbx);
		ql[1].push(lby);
		qr[1].push(rby);
	}
	int id[2][4],x[2][4];
	id[0][0]=ql[0].top().id;id[0][1]=ql[1].top().id;
	id[0][2]=qr[0].top().id;id[0][3]=qr[1].top().id;
	x[0][0]=ql[0].top().x;x[0][1]=ql[1].top().x;
	x[0][2]=qr[0].top().x;x[0][3]=qr[1].top().x;
	ql[0].pop();qr[0].pop();ql[1].pop();qr[1].pop();
	id[1][0]=ql[0].top().id;id[1][1]=ql[1].top().id;
	id[1][2]=qr[0].top().id;id[1][3]=qr[1].top().id;
	x[1][0]=ql[0].top().x;x[1][1]=ql[1].top().x;
	x[1][2]=qr[0].top().x;x[1][3]=qr[1].top().x;
	int vis[4]={0,0,0,0},bor[4];
	if(x[0][0]<=x[0][2]&&x[0][1]<=x[0][3]){
			printf("%d %d\n",x[0][0],x[0][1]);
			return 0;
		}
	for(int i=0;i<4;i++){
		if(vis[i]){
			continue;
		}
		vis[i]=1;
		for(int j=0;j<4;j++){
			if(j==i){
				bor[j]=x[1][j];
			}
			else{
				bor[j]=x[0][j];
			}
		}
		for(int j=i+1;j<4;j++){
			if(id[0][j]==id[0][i]){
				bor[j]=x[1][j];
				vis[j]=1;
			}
		}
		if(bor[0]>bor[2]||bor[1]>bor[3]){
			continue;
		}
		else{
			printf("%d %d\n",bor[0],bor[1]);
			return 0;
		}
	}
	return 0;
}
```

---

