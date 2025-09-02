# Two Tables

## 题目描述

You have an axis-aligned rectangle room with width $ W $ and height $ H $ , so the lower left corner is in point $ (0, 0) $ and the upper right corner is in $ (W, H) $ .

There is a rectangular table standing in this room. The sides of the table are parallel to the walls, the lower left corner is in $ (x_1, y_1) $ , and the upper right corner in $ (x_2, y_2) $ .

You want to place another rectangular table in this room with width $ w $ and height $ h $ with the width of the table parallel to the width of the room.

The problem is that sometimes there is not enough space to place the second table without intersecting with the first one (there are no problems with tables touching, though).

You can't rotate any of the tables, but you can move the first table inside the room.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1555B/148c3af8c708a59f4665d57c0e4342daba4e07ae.png)Example of how you may move the first table.What is the minimum distance you should move the first table to free enough space for the second one?

## 说明/提示

The configuration of the first test case is shown in the picture. But the movement of the first table is not optimal. One of the optimal movement, for example, is to move the table by $ (0, -1) $ , so the lower left corner will move from $ (2, 1) $ to $ (2, 0) $ . Then you can place the second table at $ (0, 3)-(4, 5) $ .

In the second test case, there is no way to fit both tables in the room without intersecting.

In the third test case, you can move the first table by $ (0, 2) $ , so the lower left corner will move from $ (0, 3) $ to $ (0, 5) $ .

## 样例 #1

### 输入

```
5
8 5
2 1 7 4
4 2
5 4
2 2 5 4
3 3
1 8
0 3 1 6
1 5
8 1
3 0 6 1
5 1
8 10
4 5 7 8
8 5```

### 输出

```
1.000000000
-1
2.000000000
2.000000000
0.000000000```

# 题解

## 作者：iMya_nlgau (赞：3)

最优方案只有四种情况：

- 把新来的矩形放最左面，原来的向右挪；

- 把新来的矩形放最右面，原来的向左挪；

- 把新来的矩形放最上面，原来的向下挪；

- 把新来的矩形放最下面，原来的向上挪；

逐一判断即可，不要忘了判放不下的情况。

#### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=0;char c=getchar();while(c<'0'||c>'9')f|=c=='-',c=getchar();while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return f?-x:x;}
signed main(){
	 int T=1; T=read();
	 while(T--){
		int W=read(),H=read();
		int x1=read(),y1=read(),x2=read(),y2=read();
		int w=read(),h=read();
		int ans=1000000000;
		int le=x2-x1,hi=y2-y1;
		if(w+le<=W){
			ans=min(ans,max(0,w-x1));
			ans=min(ans,max(0,x2-W+w));
		}
		if(h+hi<=H){
			ans=min(ans,max(0,h-y1));
			ans=min(ans,max(0,y2-H+h));
		}
		if(ans==1000000000) puts("-1");
		else printf("%lf\n",1.0*ans); 
				 
	 }
	return 0;
}


```

---

## 作者：baiABC (赞：2)

## 思路：

- 首先判断能否放下第二个桌子。当 $x_2-x_1+w>W$ 且 $y_2-y_1+h>H$ 时一定无解，否则可以将原桌子移到房间右上角、把第二个桌子移到左下角满足条件。

- 其次，如果有解，最优解一定是水平平移或竖直平移。因为，如果斜着平移符合题意，则水平或竖直平移也可以满足题意，且解更优。$O(1)$ 计算即可。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   int t, W, H, x1, y1, x2, y2, w, h, ansx, ansy;
   scanf("%d", &t);
   while(t--)
   {
      scanf("%d%d%d%d%d%d%d%d", &W, &H, &x1, &y1, &x2, &y2, &w, &h);
      if(x2-x1+w > W) ansx = -1;
      else if(x1 >= w || W-x2 >= w) ansx = 0;
      else ansx = min(w-x1, w+x2-W);
      // ansx 如果水平平移不能满足条件值为 -1，否则为水平平移的答案。
      if(y2-y1+h > H) ansy = -1;
      else if(y1 >= h || H-y2 >= h) ansy = 0;
      else ansy = min(h-y1, h+y2-H);
      // ansy 同理
      if(ansx == -1 & ansy == -1) puts("-1");
      else if(ansx == -1) printf("%d\n", ansy);
      else if(ansy == -1) printf("%d\n", ansx);
      else printf("%d\n", min(ansx, ansy));
   }
   return 0;
}
```
$\texttt{upd:}$ 改好了代码缩进。

---

## 作者：A_zjzj (赞：1)

[更好的阅读体验](https://blog.csdn.net/A_zjzj/article/details/119281255)

## 题目大意
在一个长为 $W$，宽为 $H$的房间中（左下角坐标 $(0,0)$，右上角坐标 $(W,H)$），摆放着一张桌子，其左下角和右上角坐标分别为 $(x1,y1),(x2,y2)$，现在还要继续在房间里面放另一张长、宽分别为 $w,h$ 的桌子，问是否可行，如果可行，输出第一张桌子最小的移动距离（欧几里得距离）

## 思路
看到这个题目，首先可以轻松愉快地得出一个结论：

>第一张桌子只能横向或纵向移动

那么这道题就迎刃而解了。

先判断无解的情况，那就是长和宽剩余的大小都容纳不下这张桌子的长和宽了。

其次，分类讨论，要么横向移动，要么纵向移动，对于一种方向上，再分类讨论，是放在左（上）边还是放在右（下）边，然后算出移动距离就好了。

注意判断不用移动的情况就好了。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void read(){}
template<typename _Tp,typename... _Tps>
void read(_Tp &x,_Tps &...Ar){
	x=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9')flag|=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(flag)x=-x;
	read(Ar...);
}
int a,b,x1,x2,y1,y2,a1,b1,a2,b2;
int get(){
	read(a,b,x1,y1,x2,y2,a2,b2);a1=x2-x1;b1=y2-y1;
	if(a1+a2>a&&b1+b2>b)return printf("-1\n"),0;
	int ans=0x3f3f3f3f;
	if(a1+a2<=a){
		if(x1>=a2||x2+a2<=a)ans=0;
		else ans=min(ans,min(a2-x1,x2+a2-a));
	}
	if(b1+b2<=b){
		if(y1>=b2||y2+b2<=b)ans=0;
		else ans=min(ans,min(b2-y1,y2+b2-b));
	}
	return printf("%d.000000000\n",ans),0;
}
int main(){
	int T;read(T);while(T--)get();
	return 0;
}
```

---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1555B)

----------
### 题目大意
给你一个大矩形，两个小矩形，大矩形必须盖住两个小矩形。一个小矩形给出两个对角的坐标，另一个小矩形给出大小。

问第一个小矩形至少移动多少距离才能使其和另一个小矩形没有接触。

---------
### 分析
题目基本无思维难度，在考代码实现。

首先肯定是横着平移或者竖着平移才有可能作为最短距离。

并且第二个小矩形在大矩形四个角的时候才有可能出现最优情况。

枚举判断即可。

---------
### $\texttt{Code}$
```cpp
#include<cstdio>

using namespace std;

inline int min(int x , int y)
{return x > y ? y : x;}

void swap(int &x , int &y)
{int c = y; y = x; x = c;}

inline int max(int x , int y)
{return x > y ? x : y;}

void work()
{
    int W , H; scanf("%d%d",&W,&H);
    int x1 , y1 , x2 , y2;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    int w , h; scanf("%d%d",&w,&h);

    double ans = 2147483647; bool flag = 0;

    int dx = w - x1; int dy = h - y1;
    if(x2 + dx <= W) 
    {flag = 1;ans = min(ans , dx);}
    if(y2 + dy <= H)
    {flag = 1;ans = min(ans , dy);}

    dx = x2 - (W - w); dy = y2 - (H - h);
    if(x1 - dx >= 0) 
    {flag = 1;ans = min(ans , dx);}
    if(y1 - dy >= 0)
    {flag = 1;ans = min(ans , dy);}

    swap(y1 , y2);

    dx = w - x1; dy = y1 - (H - h);
    if(x2 + dx <= W)
    {flag = 1;ans = min(ans , dx);}
    if( y2 - dy >= 0)
    {flag = 1;ans = min(ans , dy);}


    dx = x2 - (W - w); dy = h - y2;
    if(x1 - dx >= 0)
    {flag = 1;ans = min(ans , dx);}
    if(y1 + dy <= H)
    {flag = 1;ans = min(ans , dy);}
    
    ans = max(ans , 0);
    if(flag) printf("%.6lf\n",ans);
    else printf("-1\n");
}

int main()
{
  //  freopen("aa.in","r",stdin);
    int t; scanf("%d",&t);
    while(t--)
        work();
}
```

---

## 作者：齐心协力 (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1555/B)

尝试往上、下、左、右四个方向挪动桌子，使空隙能够放下第二张桌子，且使挪动距离最小即可。别忘了判断放不下的情况。

最优解一定不会是小数。

代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int INF=0x3f3f3f3f;
int T,n,m,x1,y_1,x2,y2,h,l;
int ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		scanf("%d%d%d%d",&x1,&y_1,&x2,&y2);
		scanf("%d%d",&h,&l);
		ans=INF;
		if(h+x2-x1<=n) ans=min(min(max(0,h-(n-x2)),max(0,h-x1)),ans);//上下
		if(l+y2-y_1<=m) ans=min(min(max(l-(m-y2),0),max(0,l-y_1)),ans);//左右
		if(ans==INF) printf("-1\n");
		else printf("%d.000000\n",ans);
	}
	return 0;
}

```

---

## 作者：Aw顿顿 (赞：0)

一个显然的贪心策略是：我们尽可能将新桌子往角落里放。

但是往哪个角落放呢？简单判断一下吧。

显然原来的桌子只能左右或者上下移动，不妨设原桌是 $a_1\times b_1$ 的，新桌子是 $a_2\times b_2$ 的，那么首先有：

$$\begin{cases}a_1=|x_1-x_2|\\b_1=|y_1-y_2|\end{cases}$$

首先如果放不下，也就是 $a_1+a_2>W$ 且 $b_1+b_2>H$ 显然输出 `-1`。

然后考虑有解的情况，答案即为：

$$\min\begin{cases}a_1-x_1\\x_2+a_1-W\\b_1-y_1\\y_2+b_1-H\end{cases}$$

考虑 $y_1$ 不能用作变量名，稍微注意一下很容易写出代码：

```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;
int T,W,H,s1,t1,s2,t2;
int w,h,res,ll,hh;
signed main(){
	 scanf("%d",&T);
	 while(T--){
		scanf("%d%d",&W,&H);
		scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
		scanf("%d%d",&w,&h);
		res=INF;ll=s2-s1,hh=t2-t1;
		if(w+ll<=W){
			res=min(res,max(0,w-s1));
			res=min(res,max(0,s2-W+w));
		}if(h+hh<=H){
			res=min(res,max(0,h-t1));
			res=min(res,max(0,t2-H+h));
		}if(res==INF)puts("-1");
		else printf("%lf\n",1.0*res);
	 }return 0;
}
```

并且这题只有三个测试点。

---

## 作者：JCLinux (赞：0)

新的桌子只可能放在原来桌子的**上下左右**这四种方向，因此分四种情况讨论即可。

1.放在左边或右边时，高度（纵）是不受限的，只需要考虑宽度（横）即可。

2.放在上边或下边时，宽度不受限制，只需要考虑高度即可。

当放在左边时，判断原有的空间是否足够容纳新的桌子，如果能容纳，毫无疑问需要移动的距离为0。否则判断将原有桌子移动到最右边是否能够容纳下新桌子，如果能，计算移动的距离（注意，这不一定是答案，还要和放在上下的情况相比较）如果不能容纳，则放在左边、右边都不行，考虑上下的情况，同理。

你会发现，这个题只有整数，小数是迷惑你的。

计算方法不难，具体见代码。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=100000000;//代表无法容纳
int main(){
	int t;cin >>t;
	while(t--){
		int W,H,w,h,x1,y1,x2,y2;
		cin >>W>>H;//房间大小
		cin >>x1>>y1>>x2>>y2;
		cin >>w>>h;
		int a=inf,b=inf,c=inf,d=inf;
		if(x1>=w) a=0;//左边可以直接容纳
		else if(W-x2+x1>=w){//左边不能容纳，但是移动之后可以容纳
			a=w-x1;
		}
		if(y1>=h) b=0;//下边
		else if(H-y2+y1>=h){
			b=h-y1;
		}
		if(W-x2>=w) c=0;//右边
		else if(W-x2+x1>=w){
			c=x2-W+w;
		}
		if(H-y2>=h) d=0;//上边
		else if(H-y2+y1>=h){
			d=y2-H+h;
		}
		int mmin=min(a,b);
		mmin=min(mmin,c);
		mmin=min(mmin,d);
		if(mmin==inf)cout <<"-1"<<endl;
		else cout <<mmin<<".000000000"<<endl;
	}
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：0)

首先显然 $x_1<x_2,y_1<y_2$（但是代码中没看清于是写了判断）。

设 $w_1=x_2-x_1,h_1=y_2-y_1$，$w_2,h_2$ 是添加进来的矩形的长宽。

容易发现只需要长上让路，或宽上让路就可以。

则若 $w_1+w_2\le W$ 就可以在长上让路；

若 $h_1+h_2\le H$ 就可以在宽上让路。

注意此时虽然答案是整数但仍需要保留 6 位小数。

联系代码食用更佳：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define eps 1e-5
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int W,H,w2,h2,xa,xb,ya,yb;
		scanf("%d%d%d%d%d%d%d%d",&W,&H,&xa,&ya,&xb,&yb,&w2,&h2);
		int w1=abs(xa-xb),h1=abs(ya-yb);
		int ans=1e9;
		if(w1+w2<=W){
			ans=min(ans,max(0,w2+max(xa,xb)-W));
			ans=min(ans,max(0,w2-min(xa,xb)));
		}
		if(h1+h2<=H){
			ans=min(ans,max(0,h2+max(ya,yb)-H));
			ans=min(ans,max(0,h2-min(ya,yb)));
		}
		if(ans>=(int)1e9-1) puts("-1");
		else printf("%d.000000\n",ans);
	}
	return 0;
}
``

---

## 作者：_Clown_ (赞：0)

# B.Two Tables
$\mathtt{Difficulty}$=$\mathtt{1300}$

肯定是横着平移或者竖着平移才有可能作为最短距离

不难发现，我们一定只能把它移到边界上

那么我们不妨枚举 $4$ 条边，然后依次判是否可行

最后再取一下答案即可

然后就不难写出代码了
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,A,B,C,D,E,F,P,Q;
signed main(void)
{
    register int Case;cin>>Case;while(Case--)
    {
        cin>>N>>M>>A>>B>>C>>D>>E>>F;
        register int Ans=1000000000;
        P=abs(A-C),Q=abs(B-D);
        if(P+E<=N)Ans=min(Ans,min(max(0,E-N+max(A,C)),max(0,E-min(A,C))));
        if(Q+F<=M)Ans=min(Ans,min(max(0,F-M+max(B,D)),max(0,F-min(B,D))));
        if(Ans>=99999999)cout<<-1<<endl;
        else cout<<Ans<<".000000"<<endl;
    }
    return 0;
}
```


---

