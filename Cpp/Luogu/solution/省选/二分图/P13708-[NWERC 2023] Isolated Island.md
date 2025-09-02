# [NWERC 2023] Isolated Island

## 题目描述

在一个遥远的小岛上，住着几位与世隔绝的老人。整个小岛被篱笆分割成若干块土地，每位老人拥有一块被篱笆完全包围的土地（所有篱笆外的区域为大海）。每位居民都需要捕鱼为生，而唯一可以捕鱼的地方就是环绕小岛的大海。由于并非每块土地都与大海直接相连，有些老人需要经过他人的土地才能到达大海。老人们每次只能跨越一段篱笆，不能经过篱笆柱或篱笆交点。

不幸的是，这些老人都很贪婪。每当有人想进入他们的土地时，都要交一条鱼。为了尽量少交鱼，每位老人都会选择一条需要交最少鱼的路径到达大海。

多年下来，这导致了老人们之间的矛盾。每位老人都讨厌那些比自己交更少鱼就能到达大海的人。只有当两位老人到达大海所需交的鱼数量相同时，他们才会“喜欢”对方。

现在有一个自然的问题：岛上是否存在一对相邻（即土地仅隔一段篱笆相邻）的老人，他们彼此喜欢？见下图 I.1，展示了前几个样例输入的情况。

|![](https://cdn.luogu.com.cn/upload/image_hosting/e253y5sb.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/8aukzter.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/ea4htdic.png)|
|:---:|:---:|:---:|

:::align{center}
图 I.1：前三个样例输入的示意图。在样例 1 中，每位老人都能直接到达大海，因此他们都彼此喜欢。在样例 2 中，没有一对相邻的老人彼此喜欢，因为中间的老人需要交一条鱼，而他的邻居们都不需要交鱼。在样例 3 中，有六位老人，其中有些是友好的邻居。
:::

现在的问题是：岛上是否存在一对相邻且彼此喜欢的老人？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
-3 -3 0 3
-3 -3 0 0
-3 -3 3 -3
0 0 0 3
0 0 3 -3
0 3 3 -3```

### 输出

```
yes```

## 样例 #2

### 输入

```
 6
-6 -3 0 3
0 3 6 -3
6 -3 -6 -3
-3 0 3 0
3 0 0 -3
0 -3 -3 0```

### 输出

```
no```

## 样例 #3

### 输入

```
8
0 1 2 1
2 2 0 0
1 2 1 0
1 0 2 1
0 0 2 0
1 2 2 2
0 1 0 0
2 2 2 0```

### 输出

```
yes```

## 样例 #4

### 输入

```
4
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0```

### 输出

```
no```

# 题解

## 作者：WuMin4 (赞：2)

## 思路

最气笑的一集。

为方便起见，原图是一个平面图，我们将原图转换为对偶图（将大海看作一个区域，将相邻的区域用边连接）。

首先可以发现相邻两个区域到大海的距离之差不会超过 $1$，假如区域 $a$ 到大海的距离为 $d$，则与 $a$ 相邻的 $b$ 可以先走到 $a$，这样距离就为 $d+1$。

因此两个区域的距离不同时仅当距离的奇偶性不同，这启发我们在对偶图上黑白染色，则当对偶图是二分图时才会满足不存在相邻的区域距离相同。

考虑二分图的等价定义：不存在奇环的图是二分图。观察原图转为对偶图的过程，发现当原图存在度数为奇数的点时，会构造出奇环（如下图），因此仅当原图不存在度数为奇数的点时，对偶图为二分图。

![](https://cdn.luogu.com.cn/upload/image_hosting/nosas2es.png)

喜欢模拟的小朋友~~就是我~~思考到这一步就可以开始写了：求出所有线段的交点，统计交点度数。

## 纯模拟代码

这里给出我堆了一个小时的答芬（复杂度理论是 $O(n^3)$ 的，极有可能被卡，但是我过了）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
const ld eps=1e-14;
struct node{
	ld x,y,xx,yy;
}a[1005];
bool sm(ld x,ld y,ld xx,ld yy){
	return abs(x-xx)<=eps&&abs(y-yy)<=eps;
}
node kx(node x){
	ld xk,xb;
	if(x.x==x.xx)
		xk=1e7,xb=0;
	else
		xk=(x.yy-x.y)*1.0/(x.xx-x.x),xb=x.y-xk*x.x;
	return {xk,xb};
}
node jd(node x,node y){
	ld xk=kx(x).x,yk=kx(y).x,xb=kx(x).y,yb=kx(y).y,jx,jy;;
	if(xk==yk) return {1e7,1e7};
	if(xk==1e7)
		jx=x.x,jy=yk*jx+yb;
	else if(yk==1e7)
		jx=y.x,jy=xk*jx+xb;
	else
		jx=(yb-xb)/(xk-yk),jy=xk*jx+xb;
	if(
		min(x.x,x.xx)-jx<=eps&&jx-max(x.x,x.xx)<=eps&&
		min(x.y,x.yy)-jy<=eps&&jy-max(x.y,x.yy)<=eps&&
		min(y.x,y.xx)-jx<=eps&&jx-max(y.x,y.xx)<=eps&&
		min(y.y,y.yy)-jy<=eps&&jy-max(y.y,y.yy)<=eps
		)
		return {jx,jy};
	else
		return {1e7,1e7};
}
int n;
vector<node> b,c;
bool cmp(node x,node y){
	return abs(x.x-y.x)<=eps?x.y<y.y:x.x<y.x;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y>>a[i].xx>>a[i].yy;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ld jx=jd(a[i],a[j]).x,jy=jd(a[i],a[j]).y;
			if(jx==1e7) continue;
			b.push_back({jx,jy});
		}
	}
	sort(b.begin(),b.end(),cmp);
	for(int i=0;i<b.size();i++)
		if(i==0||!(abs(b[i].x-b[i-1].x)<=eps&&abs(b[i].y-b[i-1].y)<=eps))
			c.push_back(b[i]);
	for(node v:c){
		int cnt=0;
		for(int i=1;i<=n;i++){
			if((abs(a[i].x-v.x)<=eps&&abs(a[i].y-v.y)<=eps)||(abs(a[i].xx-v.x)<=eps&&abs(a[i].yy-v.y)<=eps))
				cnt++;
			else{
				ld xk=kx(a[i]).x,xb=kx(a[i]).y;
				if(abs(xk*v.x+xb-v.y)<=eps)
					cnt+=2;
			}
		}
		if(cnt%2!=0){
			cout<<"yes";
			return 0;
		}
	}
	cout<<"no";
	return 0;
}
```

不过我写完后才发现还有更简单的写法。

发现当一条线段穿过一个交点（即交点不在端点上时）时，交点度数会增加 $2$，不会对奇偶性造成影响，因此我们只需要去考虑每条线段的端点出现次数奇偶性即可，统计是极其简单的。

## 真正的代码

~~堆了一个小时的答芬发现正解不超过 $20$ 行的救赎感~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
map<pair<int,int>,bool> p;
signed main(){
	cin>>n;
	for(int x,y,xx,yy,i=1;i<=n;i++)
		cin>>x>>y>>xx>>yy,p[{x,y}]^=1,p[{xx,yy}]^=1;
	for(pair<pair<int,int>,bool> v:p)
		if(v.second){
			cout<<"yes";
			return 0;
		}
	cout<<"no";
	return 0;
}
```

---

