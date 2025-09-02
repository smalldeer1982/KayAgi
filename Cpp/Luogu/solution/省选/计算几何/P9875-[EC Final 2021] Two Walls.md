# [EC Final 2021] Two Walls

## 题目描述

庞教授买了一个人形清洁机器人来清理他的院子。这个机器人并不十分复杂，它可以前进或改变方向，这一切都由庞教授的控制器控制。

庞教授的院子是一个二维平面。机器人需要从当前位置 $A$ 移动到目的地 $B$，以满足庞教授的一些“清洁”需求。然而，庞教授的院子里有两堵直墙 $CD$ 和 $EF$。由于机器人笨拙，如果它碰到任何一堵墙（即使是端点），它就会摔倒。

由于庞教授很懒，他希望尽量减少机器人改变方向的次数。你能帮他吗？

## 说明/提示

以下是第一个样例和第三个样例的示意图。

![](https://cdn.luogu.com.cn/upload/image_hosting/nuyvzg7a.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/diy78yex.png)

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
0 0
1 1
2 2 3 3
4 4 5 5
0 0
1 1
2 2 3 3
2 2 3 3
0 0
10 10
10 0 0 10
1 1 2 2```

### 输出

```
0
0
1```

# 题解

## 作者：Siegerkranz_2735 (赞：1)

首先可以尝试一下，可以发现答案只有三种：$0,1,2$。但是不知道应该怎么证明。下面我们分别来讨论几种情况：

#### 两个墙没有相交（包括有部分重合）：

显然他最多拐一次，只需要判断线段 $ab$ 是否经过墙就可以了。

#### 两个墙相交：

先看这个：对于一个点和一个墙，绿色部分是不能走的。

![](https://cdn.luogu.com.cn/upload/image_hosting/lhdkf5z4.png)

所以两堵墙不能走的区域就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/9oamxao2.png)

可以发现，只要两个点可以到达的区域有交集就只拐一次就可以了，否则就需要拐两次。

这两个区域有交集可以转化为 $a$ 与 $b$ 分别与同侧的墙的端点的射线是否有交点，具体的话可以看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lxulyezw.png)

具体可以这样，先判断 $a$ 和 $b$ 分别在两个线段分割的四个区域的那个部分，然后枚举 $a$ 和 $b$ 连对应区域的墙的两个点射线有没有交点，有就是 $1$，没有就是 $2$。

所以判断的顺序可以是这样：
- $ab$ 线段上正好有墙的一头（$c,d,e,f$）：输出 $1$。
- 线段ab不经过线段cd和线段ef ：输出 $0$。
- 两个墙不相交：输出 $1$。 
- 如果两个点可以到达的区域有交集：输出 $1$。
- 否则输出 $2$。

------------

思路已经很清楚了，还有一些细节的实现：


先给几个前置的知识：

- $\text{sng}(x) = \begin{cases}
  -1 & x<0 \\
  0 & x=0 \\
  1 & x>0
\end{cases}$

```cpp
int sgn(__int128_t x){return x==0?0:(x<0?-1:1);}//sgn函数，只取符号 
```


- 已知 $A(x_1,y_1),B(x_2,y_2)$ 那么 $\vec{AB}=(x_2-x_1,y_2-y_1)$。

```cpp
struct point{
	__int128_t x,y;
	point operator -(const point & p)const{return {x-p.x,y-p.y};}//求向量 
}
```

- 已知 $\vec{AB}=(x_1,y_1),\vec{CD}=(x_2,y_2)$ 那么 $\vec{AB}\times \vec{AC}=x_1\cdot y_2-x_2\cdot y_1$。

```cpp
__int128_t cross(point a,point b){return a.x*b.y-a.y*b.x;}//向量叉乘 
```

- 向量叉乘几何意义是：$\vec{AB}\times \vec{AC}$ 的结果为负值，表明 $B,C$ 两点是按顺时针方向移动；$\vec{AB}\times \vec{AC}$的结果为正值，表明 $B,C$ 两点是按逆时针方向移动。

```cpp
int F(point a,point b,point c){return sgn(cross(b-a,c-a));}//判断c在ab的哪一侧 
```

#### 怎么判断两个线段是否相交

若两线段 $a,b$ 相交，$b$ 线段的两个端点一定分布在 $a$ 线段所在直线两侧，同时 $a$ 线段的两个端点一定分布在 $b$ 线段所在直线两侧。我们可以直接判断一条线段的两个端点相对于另一线段所在直线的位置关系。

```cpp
bool jiao(point a,point b,point c,point d){
	if(F(a,b,c)*F(a,b,d)>=0)return 0;//cd在ab同侧 
	if(F(c,d,a)*F(c,d,b)>=0)return 0;//ab在cd同侧 
	return 1;//ab与cd相交 
}
```

#### 两个射线是否相交

提前在给参数的时候把射线的方向规定好就行了，最后返回那部分那个正负必须这样规定，不然交点会在射线另一侧。

```cpp
bool jiao2(point a,point b,point c,point d){
	int sg=sgn(cross(b-a,d-c));//向量ab和cd叉乘 
	if(sg==0)return 0;//平行 
	return F(c,d,a)==sg && F(a,b,c)==-sg;//类似于零点存在性的证明，一个在他下面一个在他上面，而且连续所以相交。
}
```



#### 怎么判断一个点是否在一个线段上

首先要保证点的 $x$ 在线段的定义域，$y$ 在线段的值域上，并且点在线段所在的直线上就可以保证点在线段上。

```cpp
bool onLine(point a,point b,point c){//判断c是否在线段ab上 
	if(c.x<min(a.x,b.x)||c.x>max(a.x,b.x))return 0;//c的x属于线段ab的x的范围 
	if(c.y<min(a.y,b.y)||c.y>max(a.y,b.y))return 0;//c的y属于线段ab的y的范围 
	return cross(c-a,c-b)==0;//c在直线ab上 
}
```


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{
	__int128_t x,y;
	point operator -(const point & p)const{return {x-p.x,y-p.y};}//求向量 
}a,b,c,d,e,f;
void read(point &a){//读入 
	int x,y;
	scanf("%d%d",&x,&y);
	a.x=x,a.y=y;
}
__int128_t cross(point a,point b){return a.x*b.y-a.y*b.x;}//向量叉乘 
int sgn(__int128_t x){return x==0?0:(x<0?-1:1);}//sgn函数，只取符号 
int F(point a,point b,point c){return sgn(cross(b-a,c-a));}//判断c在ab的哪一侧 
bool jiao(point a,point b,point c,point d){
	if(F(a,b,c)*F(a,b,d)>=0)return 0;//cd在ab同侧 
	if(F(c,d,a)*F(c,d,b)>=0)return 0;//ab在cd同侧 
	return 1;//ab与cd相交 
}
bool jiao2(point a,point b,point c,point d){
	int sg=sgn(cross(b-a,d-c));//向量ab和cd叉乘 
	if(sg==0)return 0;//平行 
	return F(c,d,a)==sg && F(a,b,c)==-sg;//类似于零点存在性的证明，一个在他下面一个在他上面，而且连续所以相交 
}
bool onLine(point a,point b,point c){//判断c是否在线段ab上 
	if(c.x<min(a.x,b.x)||c.x>max(a.x,b.x))return 0;//c的x属于线段ab的x的范围 
	if(c.y<min(a.y,b.y)||c.y>max(a.y,b.y))return 0;//c的y属于线段ab的y的范围 
	return cross(c-a,c-b)==0;//c在直线ab上 
}
int work(){
	vector<point>X,Y;
	if(onLine(a,b,c)||onLine(a,b,d)||onLine(a,b,e)||onLine(a,b,f))return 1;//ab线段上正好有墙的一头 
	if(!jiao(a,b,c,d)&&!jiao(a,b,e,f))return 0;//线段ab不经过线段cd和线段ef 
	if(!jiao(c,d,e,f))return 1;//两个墙不相交 
	for(point p:{c,d}){//判断a和b分别在两个线段分割的四个区域的那个部分
		if(!jiao(a,p,e,f))X.push_back(p);
		if(!jiao(b,p,e,f))Y.push_back(p);
	}
	for(point p:{e,f}){
		if(!jiao(a,p,c,d))X.push_back(p);
		if(!jiao(b,p,c,d))Y.push_back(p);
	}//看射线是否相交
	for(auto i:X)for(auto j:Y)if(jiao2(a,i,b,j))return 1;
	return 2;
}
int main(){
	int T;
	for(scanf("%d",&T);T--;printf("%d\n",work()))read(a),read(b),read(c),read(d),read(e),read(f);
	return 0;
}
```

附记：从一月末就开始写这篇题解了，拖到现在才写完，2735你不能这样颓废了。

---

## 作者：Diaоsi (赞：1)

[Two Walls](https://www.luogu.com.cn/problem/P9875)

阴间计算几何。

观察到答案至多为 $2$，先判断 $A$ 和 $B$ 之间有几堵墙。

若没有墙则答案为 $0$，若只有一堵墙或有两堵墙但其中任意一堵墙为端点阻拦，则答案为 $1$。

图为一种端点阻拦的情况

![端点阻拦](https://cdn.luogu.com.cn/upload/image_hosting/x56ksddm.png)

否则一定是一个类似于交叉的结构且 $A$ 和 $B$ 分别在两侧，将四个点按照在线段 $AB$ 的左 $/$ 右边分成两类，每边各两个，然后用叉乘判断 $A$ 和 $B$ 两个点分别与同侧的点引出的射线能否相交即可，若能相交则答案为 $1$，否则答案为 $2$。

![答案为1](https://cdn.luogu.com.cn/upload/image_hosting/3bl34rhf.png)

![答案为2](https://cdn.luogu.com.cn/upload/image_hosting/oq18vqa9.png)

注意精度问题，在判断两个线段有无交点时要使用叉乘。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N=110,M=1010,INF=1e9+7;
ll T,n,tot;
struct node{
	ll x,y;
	void read(){
		ll xx,yy;
		scanf("%lld%lld",&xx,&yy);
		x=xx;y=yy;
	}
	node(ll xx=0,ll yy=0){x=xx,y=yy;}
}p[N],A,B,C,D,E,F;

ll max(ll x,ll y){return x>y?x:y;}
ll min(ll x,ll y){return x<y?x:y;}
node operator +(node a, node b){return {a.x+b.x,a.y+b.y};}
node operator -(node a, node b){return {a.x-b.x,a.y-b.y};}

ll operator *(node a,node b){return a.x*b.x+a.y*b.y;}
ll operator ^(node a,node b){return a.x*b.y-a.y*b.x;}

bool check(node a,node b,node c,node d){
    if(max(a.x,b.x)<min(c.x,d.x)||max(a.y,b.y)<min(c.y,d.y)||
        max(c.x,d.x)<min(a.x,b.x)||max(c.y,d.y)<min(a.y,b.y))return 0;
    return 1;
}
bool judge(node p,node a,node b){return ((b-a)^(p-a))>0;}

int inter(node a,node b,node c,node d){
    if (!check(a,b,c,d))return 0;
    node cd=d-c,ca=a-c,cb=b-c;
    ll x=cd^ca,y=cd^cb;
    if(x>0&&y>0)return 0;
    if(x<0&&y<0)return 0;
    node ab=b-a,ac=c-a,ad=d-a;
    x=ab^ac,y=ab^ad;
    if(x>0&&y>0)return 0;
    if(x<0&&y<0)return 0;
    if(x==0||y==0)return 1;
    return 2;
}
void solve(){
	tot=0;
	A.read();B.read();
	C.read();D.read();
	E.read();F.read();
	
	tot=inter(A,B,C,D)+inter(A,B,E,F);
	if(tot==0){
		puts("0");
		return;
	}
	else if(tot!=4){
		puts("1");
		return;
	}
	else{
		node l1=C,r1=D,l2=E,r2=F;
		if(judge(r1,A,B))swap(l1,r1);
		if(judge(r2,A,B))swap(l2,r2);
		if((((l1-A)^(l2-B))>0&&((l2-A)^(l1-B))>0)||
			(((r1-B)^(r2-A))>0&&((r2-B)^(r1-A))>0)){
			puts("1");
			return;
		}
	}
	puts("2");
}
int main(){
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```

---

