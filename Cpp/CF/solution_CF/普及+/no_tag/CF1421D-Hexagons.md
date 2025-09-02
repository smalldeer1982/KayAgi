# Hexagons

## 题目描述

Lindsey Buckingham told Stevie Nicks ["Go your own way"](https://www.youtube.com/watch?v=6ul-cZyuYq4). Nicks is now sad and wants to go away as quickly as possible, but she lives in a 2D hexagonal world.

Consider a hexagonal tiling of the plane as on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/d7b83f7c1945491e0c5eb4d61bc10fb5c2e2d62e.png)Nicks wishes to go from the cell marked $ (0, 0) $ to a certain cell given by the coordinates. She may go from a hexagon to any of its six neighbors you want, but there is a cost associated with each of them. The costs depend only on the direction in which you travel. Going from $ (0, 0) $ to $ (1, 1) $ will take the exact same cost as going from $ (-2, -1) $ to $ (-1, 0) $ . The costs are given in the input in the order $ c_1 $ , $ c_2 $ , $ c_3 $ , $ c_4 $ , $ c_5 $ , $ c_6 $ as in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/5520c3b497776aedfe7eabfa13d5468fdc04c261.png)Print the smallest cost of a path from the origin which has coordinates $ (0, 0) $ to the given cell.

## 说明/提示

The picture below shows the solution for the first sample. The cost $ 18 $ is reached by taking $ c_3 $ 3 times and $ c_2 $ once, amounting to $ 5+5+5+3=18 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/0ec113af8e20d4052a5764c227b25383ee56e47d.png)

## 样例 #1

### 输入

```
2
-3 1
1 3 5 7 9 11
1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
18
1000000000000000000```

# 题解

## 作者：_ztyqwq (赞：5)

多好的一道题啊 ~~（没错那个场上 8min 一血的就是我）~~

![ohhhhh](https://i.loli.net/2020/10/31/8QyW69rKzmxIqY3.png)

看起来这像是一个最短路问题，只是如果直接将目标点与 $ 0, 0 $ 之间的点全部建进图中显然是不可能的。我们考虑求出 C1 ~ C6 的**最优值**（其实就是最短路）。

最短路的核心思想就是 `dis[v] = min(dis[v], dis[u] + g[u][v]`，也就是当存在一条路径可以以更小的代价到达 $ v $ 时，更新到达 $ v $ 的最短路。

本题我们也可以采取这样的思想。如果直接走一步和另外走两步可以到达相同的位置，而后者的花费更小，那我们就可以用这两步的花费更新走一步的花费。

具体说明：

![hexagons](https://i.loli.net/2020/10/31/cOoPyE9vI7UthZl.png)

如果沿 C1 方向走一步，到达 $ (1, 1) $，花费为 $ 8 $；而沿 C2 和 C6 方向各走一步，同样到达 $ (1, 1) $，花费为 $ 3 + 4 = 7 $。那我们此时就可以直接将 C1 的值更新为 $ 7 $。

这其中也就是最短路的思想。

此时你可以选择在这 $ 7 $ 个点中直接跑一遍最短路，求出 C1 ~ C6 的最优值（它们也就是这些点最终的 `dis` 值）。也可以简单地模拟最短路： 

回顾 `Bellman-Ford` 求最短路的过程，每一轮循环都将所有的边都尝试松弛一次，即：

```
c1 = min(c1, c6 + c2);
c2 = min(c2, c1 + c3);
c3 = min(c3, c2 + c4);
c4 = min(c4, c3 + c5);
c5 = min(c5, c4 + c6);
c6 = min(c6, c5 + c1);
```

而循环的次数只要 $ \geqslant $ 边数都能得到正确的答案，有时还可以再减小。这里循环次数取 $ 10 $ 亲测可以全部更新出正确答案。

---

求出 C1 ~ C6 最优值后就是一个分类讨论的问题了。具体来说：

- $ x \geqslant 0, y \geqslant 0 $，C1 与 （C2 或 C6） 组合。

- $ x \leqslant 0, y \leqslant 0 $，C4 与 （C3 或 C5） 组合。

- $ x \geqslant 0, y \leqslant 0 $，C6 与 C5 组合。

- $ x \leqslant 0, y \geqslant 0 $，C3 与 C2 组合。

正负等细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
signed main()
{
	int t;
	scanf("%lld", &t);
	while(t--)
	{
		int x, y;
		scanf("%lld %lld", &x, &y);
		int c1, c2, c3, c4, c5, c6;
		scanf("%lld %lld %lld %lld %lld %lld", &c1, &c2, &c3, &c4, &c5, &c6);
		for(int i = 1; i <= 10; i++)
		{
			c1 = min(c1, c6 + c2);
			c2 = min(c2, c1 + c3);
			c3 = min(c3, c2 + c4);
			c4 = min(c4, c3 + c5);
			c5 = min(c5, c4 + c6);
			c6 = min(c6, c5 + c1);
		}
		if(x >= 0 && y >= 0)
		{
			if(x > y)
				printf("%lld\n", y * c1 + (x - y) * c6);
			else
				printf("%lld\n", x * c1 + (y - x) * c2);
		}
		else if(x <= 0 && y <= 0)
		{
			if(x < y)
				printf("%lld\n", -y * c4 - (x - y) * c3);
			else
				printf("%lld\n", -x * c4 - (y - x) * c5);
		}
		else if(x >= 0 && y <= 0)
			printf("%lld\n", x * c6 - y * c5);
		else if(x <= 0 && y >= 0)
			printf("%lld\n", -x * c3 + y * c2);
	}
	return 0;
}
```

---

## 作者：瞬间。。 (赞：4)

我现在要询问最小费用，就说明我的每个步骤都不能多。
大家拿着图看，我不会插入图片 emmm。。。\
c1步骤显然可以使用一次c2,c6代替\
这样我就可以得到每个步骤的最小费用。\
很容易发现一个性质，从起点到终点的最优解其实只由两个步骤组成，那我现在直接枚举这两个步骤就行\
c1操作使得x，y轴坐标都加1，c2使得x坐标加1，根据这样的性质，我就可以直接列一个二元一次方程组求解。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;


int t,xx,yy,ans;
int c[10],x[10],y[10];

int solve(int i,int j)
{
	if(i==1 && j==4)	return -1;
	if(i==2 && j==5)	return -1;
	if(i==3 && j==6)	return -1;
	int a1=x[i],b1=x[j],a2=y[i],b2=y[j],c1=-xx,c2=-yy;
	int a=-1,b=-1;
	if(a1==0)	b=xx/b1;
	else if(a2==0)	b=yy/b2;
	else
	{
		if(a1+a2!=0) b=(xx-yy)/(b1-b2);
		else b=(xx+yy)/(b1+b2);
	}
	if(a1!=0)	a=(xx-b*b1)/a1;
	else a=(yy-b*b2)/a2;
	if(a<0 || b<0)	return -1;
	return a*c[i]+b*c[j];
	
}


signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>xx>>yy;
		for(int i=1;i<=6;i++)	cin>>c[i];
		c[1]=min(c[1],c[2]+c[6]);
		c[2]=min(c[2],c[1]+c[3]);
		c[3]=min(c[3],c[2]+c[4]);
		c[4]=min(c[4],c[3]+c[5]);
		c[5]=min(c[5],c[4]+c[6]);
		c[6]=min(c[6],c[5]+c[1]);
		x[6]=x[1]=1;
		x[3]=x[4]=-1;
		y[4]=y[5]=-1;
		y[1]=y[2]=1;
		ans=1ll<<62;
		for(int i=1;i<=6;i++)
			for(int j=i+1;j<=6;j++)
			{
				if(solve(i,j)<0)	continue;
				ans=min(ans,solve(i,j));
			}
		cout<<ans<<endl;
	}
	
	
}

```
完结撒花



---

## 作者：Chinese_zjc_ (赞：3)

~~调分类讨论调到最后一秒才调出来,结果比赛结束了,掉了52分直接变蓝名.~~

$**$分类讨论题,当然是分四个象限分类讨论喽.

本处为了不用讨论坐标轴上的位置,将各象限边缘的坐标轴部分也算入象限内.

## 第三象限 $x\leq0\&\& y\leq0$

显然是要先用一点 $c[4]$ ,再用一点别的是最优解,或者直接用 $c[3]$ 和 $c[5]$ .

那我们就可以推出三种大致情况.

$c[4]\rightarrow c[3]$ , $c[4]\rightarrow c[5]$ , $c[3]\rightarrow c[5]$ .

显然这三种情况的最小值即为最优解,可以证明没有别的方案比这三种更能更新答案.

## 第四象限 $x\leq0\&\& y\geq0$

类似于第三象限的构造方法,用 $c[1]$ 避免 $c[5]$ 或 $c[6]$ 的使用,或者直接 $c[5]$ 后 $c[6]$ 亦可.

那我们就可以推出三种大致情况.

$c[1]\rightarrow c[5]$ , $c[1]\rightarrow c[6]$ , $c[5]\rightarrow c[6]$ .

显然这三种情况的最小值即为最优解,可以证明没有别的方案比这三种更能更新答案.

剩余两个象限的答案与其关于原点中心对称的象限的答案类似,不再一一赘述.

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
int T, x, y, c[6], ans;
const int xx[6] = {1, 0, -1, -1, 0, 1}, yy[6] = {1, 1, 0, -1, -1, 0};
bool can[6];
signed main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--)
    {
        cin >> y >> x;
        for (int i = 0; i < 6; ++i)
        {
            cin >> c[i];
        }
        ans = INF;
        if (x <= 0 && y <= 0)
        {
            ans = min(ans, c[3] * min(abs(x), abs(y)) + max(abs(x) - abs(y), 0ll) * c[4] + max(abs(y) - abs(x), 0ll) * c[2]);
            ans = min(ans, c[3] * max(abs(x), abs(y)) + max(abs(x) - abs(y), 0ll) * c[5] + max(abs(y) - abs(x), 0ll) * c[1]);
            ans = min(ans, c[2] * abs(y) + c[4] * abs(x));
        }
        if (x <= 0 && y >= 0)
        {
            ans = min(ans, c[0] * abs(y) + c[4] * abs(y - x));
            ans = min(ans, c[3] * abs(x) + c[5] * abs(y - x));
            ans = min(ans, c[4] * abs(x) + c[5] * abs(y));
        }
        if (x >= 0 && y >= 0)
        {
            ans = min(ans, c[0] * min(abs(x), abs(y)) + max(abs(x) - abs(y), 0ll) * c[1] + max(abs(y) - abs(x), 0ll) * c[5]);
            ans = min(ans, c[0] * max(abs(x), abs(y)) + max(abs(x) - abs(y), 0ll) * c[2] + max(abs(y) - abs(x), 0ll) * c[4]);
            ans = min(ans, c[5] * abs(y) + c[1] * abs(x));
        }
        if (x >= 0 && y <= 0)
        {
            ans = min(ans, c[3] * abs(y) + c[1] * abs(y - x));
            ans = min(ans, c[0] * abs(x) + c[2] * abs(y - x));
            ans = min(ans, c[1] * abs(x) + c[2] * abs(y));
        }
        cout << ans << endl;
    }
    return 0;
}
```



---

## 作者：Leap_Frog (赞：1)

### P.S.
这题的 idea 不是笔者提供的（毕竟笔者这么菜）。  
感谢 @[zhouchenyuan005](https://www.luogu.com.cn/user/87416 "神仙") 提供的思路，这篇题解的代码比楼上楼下的都短（目前），主要代码就两行。  

### Discription.
给定一个六边形网格，你每次可以往六个方向运动，每个方向有一个代价。  
求从源点运动到指定点至少需要多少的代价。  

### Solution.
首先，这个六边形看着就很不舒服，那么我们就把它按照题面的坐标强行放到坐标系中去。  
然后我们发现题目就转化成了下图：
```
        Y
        ↑
        |
        |
        |
        c6
        ↑   c1
        | ↗
c5←-----.------→ c2------------→ X
    ↙  |
c4      ↓
        c3
```
那么我们假设我们要在 $x$ 方向运动 $a_2$ 的距离（向左则为负  
要在 $y$ 方向上运动 $a_3$ 的距离，要在斜线方向上运动 $a_1$ 的距离。  
那么很显然，我们能得到两个方程。  
$$a_2+a_1=X$$
$$a_1-a_3=Y$$
所以，显然地，我们有：  
$$a_2=X-a_1\ ,\ a_3=a_1-Y$$
而最终的答案就是：  
$$k_1\times a_1+k_2\times a_2+k_3\times a_3$$
（$k_1$ $k_2$ $k_3$ 都是常量，就是可能需要分类讨论 $a$ 的正负性。  
于是上面这个函数肯定是关于 $a_1$ 的一次函数。  
由于初中所学，一个套上分类讨论系数的一次函数如果有最小值，那么最小值肯定在分类讨论边界取到。  
而上面的三个分类讨论边界分别就是 $a_1=0$ $a_2=0$ $a_3=0$  
所以我们只需要把 $a_1=0,X,Y$ 时上面的函数取最小值。  
三个分别计算一下就好了（请记住你是 OIer 而不是 MOer。  
### Coding.
```cpp
//愿你有一天能和你重要的人重逢。
#include<bits/stdc++.h>
using namespace std;int T;long long X,Y,c1,c2,c3,c4,c5,c6;
inline long long calc(int x) {int a1=x,a2=Y-a1,a3=a1-X;return (a1>0?c1:-c4)*a1+(a2>0?c2:-c5)*a2+(a3>0?c3:-c6)*a3;}
int main() {for(scanf("%d",&T);T--;) scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&X,&Y,&c1,&c2,&c3,&c4,&c5,&c6),printf("%lld\n",min(calc(0),min(calc(X),calc(Y))));}
```

---

## 作者：MyukiyoMekya (赞：1)

先把他变正常一点

```plain
		c6		c1

c5		o		c2
		
c4		c3
```

这是在 x 行 y 列上的六个方向

显然有时候 c2 可以用 c1+c3 代替，所以先建一个 10\*10 的点阵，然后每个点都给他向六个方向连边，权值就是 $c_i$ 然后从中间点跑一遍最短路，然后就能得出所有 c 的最小值。

然后就是直接分象限讨论了，能用 c1 , c4 解决的就尽量用这两个，否则就用其他的。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define mem(x,y) memset(x,y,sizeof x)
#define ln puts("")
#define lsp putchar(32)
#define pb push_back
#define MP make_pair
using namespace std;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool checkmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
const int dir[6][2]={1,1,0,1,-1,0,-1,-1,0,-1,1,0};
#define fi first
#define se second
struct Node
{
	int u,d;
	inline bool operator < (const Node &nt) const
	{
		return nt.d<d;
	}
};
vector<pair<int,int> > E[150];
int dis[150];
bool vis[150];
inline int calc(int x,int y)
{
	x+=5,y+=5;
	return x*11+y; 
}
inline void dijkstra(int s)
{
	priority_queue<Node> Q;
	mem(dis,0x3f),mem(vis,false);
	dis[s]=0;
	Q.push((Node){s,0});
	while(!Q.empty())
	{
		reg int u=Q.top().u;Q.pop();
		if(vis[u])
			continue;
		vis[u]=true;
		for(auto v:E[u])
			if(checkmin(dis[v.fi],dis[u]+v.se))
				Q.push((Node){v.fi,dis[v.fi]});
	}
	return;
}
int c[6];
inline void work()
{
	for(int i=0;i<150;++i)
		E[i].clear();
	int x,y;read(x,y);
	for(int i=0;i<6;++i)
		read(c[i]);
	for(int i=-5;i<=5;++i)
		for(int j=-5;j<=5;++j)
			for(int k=0;k<6;++k)
			{
				reg int nx=i+dir[k][0];
				reg int ny=j+dir[k][1];
				if(nx<-5||nx>5||ny<-5||ny>5)
					continue;
				E[calc(i,j)].pb(MP(calc(nx,ny),c[k]));
			}
	dijkstra(calc(0,0));
	for(int k=0;k<6;++k)
	{
		reg int nx=dir[k][0];
		reg int ny=dir[k][1];
		checkmin(c[k],dis[calc(nx,ny)]);
	}
	if(!x&&!y)
		puts("0");
	else if(!x)
		write(y<0?-c[4]*y:c[1]*y),ln;
	else if(!y)
		write(x<0?-c[2]*x:c[5]*x),ln;
	else if(x>0&&y<0)
		write(c[5]*x-c[4]*y),ln;
	else if(x<0&&y>0)
		write(-c[2]*x+c[1]*y),ln;
	else if(x<0&&y<0)
	{
		reg int t=min(fabs(x),fabs(y));
		x+=t,y+=t;
		write(t*c[3]-c[2]*x-c[4]*y),ln;
	}
	else
	{
		reg int t=min(fabs(x),fabs(y));
		x-=t,y-=t;
		write(t*c[0]+c[5]*x+c[1]*y),ln;
	}
	return;
}
signed main(void)
{
	int t;read(t);
	while(t--)
		work();
	return 0;
}
```



---

## 作者：pldzy (赞：0)

模拟 / 最短路。

# Solution

有三种方法，其中每一种方法我都一定程度上想到了。这里都说说吧。

**Useful Observations and Notice**：首先因为要求代价最小，所以我们不会同时走相反的路径，比如右上和左下；这个六边形显然可以转化成网格，除了四联通之外加上右上左下两个方向；题目问题是在坐标系上进行的，所以上下左右不能直接从网格挪过来，会反；**最终最佳方案一定最多只涉及两种方向**。

**Method 1**：暴力直接贪心分讨。根据第一条性质，我们可以推断最终一定只使用了两种方向去走。比如说当 $x\geq 0,y\geq 0$ 时，有且仅有三种可能产生贡献的方案：横纵各自单独增；横纵同时加到较小值，剩下那个自己加；横纵同时加到较大值，剩下那个自己减。所以直接分四种情况讨论最小值即可，总共 12 条式子，并不是很复杂。[Solution & Code.](https://www.luogu.com.cn/blog/ChinesezjcBlog/cf1421d-solution)


**Method 2**：我们可以根据它在水平方向、竖直方向、斜线方向行走的路程（矢量）列出三者关于 $(x,y)$ 的等式。然后很重要我没想到的一点就是，费用是常量，路程是变量，总费用是三个费用乘以三个路程之和，而三个路程都可以转化成 一个变量 与 常量 运算的等式。所以，总费用的形式是三个一次函数之和，形如 $k_1(a_1+c_1)+k_2(a_1+c_2)+k_3(a_1+c_3)$，其中 $a_1$ 是水平方向上的路程。因为 $a$ 与不同参数运算的正负性可能随着 $a$ 的取值发生改变，所以我们不妨理解为上面这个函数是一条由多个一次函数组合而成的折线。所以极值一定只在端点取到，我们枚举 $a$ 的三个取值 $-c_1,-c_2,-c_3$ 即可。[Solution & Code.](https://www.luogu.com.cn/blog/daniu/solution-cf1421d)


**Method 3**：我一开始也观察出来对于每个方向，使用它是有条件的。比如说右上方向，我们选择它当且仅当其代价小于先右后上的代价和。所以我们可以联系最短路，对于每个方向，我们使用 Bellman-Ford 求最短路的过程让它们自行松弛对方，当次数大于总边数的时候能够保证都松弛到最多解（这里取 10 次）。这样每个方向的代价都是按这个方向走的最小代价。然后就可以直接无脑计算总花费了。[Code.](https://www.luogu.com.cn/paste/4m0xc1kh)

~~代码太丑不放了，前面都贴了链接了~~。

---

## 作者：WZKQWQ (赞：0)

首先是观察一下看看有没有神奇的性质。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/d7b83f7c1945491e0c5eb4d61bc10fb5c2e2d62e.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/5520c3b497776aedfe7eabfa13d5468fdc04c261.png)

就比如一次 $c2$ 操作，相当于先 $c1$ 后 $c3$ 或者先 $c3$ 后 $c1$，再然后，会发现一次操作相当于执行和它相邻的操作。

所以我们可以用第 $i+1$ 个操作的代价和第 $i-1$ 个操作的代价更新第 $i$ 个操作。

根据一点点图论知识我们知道更新最多发生 $5$ 次（有六个操作）

所以我们可以：

```cpp
for(int i = 1;i <= 6;++i)
			for(int j = 1;j <= 6;++j){
				if(j == 1) c[j] = min(c[j],c[6] + c[j + 1]);
				else if(j == 6) c[j] = min(c[j],c[j - 1] + c[1]);
				else c[j] = min(c[j],c[j - 1] + c[j + 1]);
			} 
```

然后就走直线就OK，比如下面这图，从 $(0,0)$ 到 $(-3,1)$，只需要三次 $c3$ 和一次 $c2$。（无关顺序）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1421D/0ec113af8e20d4052a5764c227b25383ee56e47d.png)

最后贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
int T,x,y,c[7];
ll ans;
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans = 0;
		scanf("%lld%lld",&x,&y);
		for(int i = 1;i <= 6;++i) scanf("%lld",&c[i]);
		for(int i = 1;i <= 6;++i)
			for(int j = 1;j <= 6;++j){
				if(j == 1) c[j] = min(c[j],c[6] + c[j + 1]);
				else if(j == 6) c[j] = min(c[j],c[j - 1] + c[1]);
				else c[j] = min(c[j],c[j - 1] + c[j + 1]);
			} 
		if(x < 0 && y < 0){
			int p = max(x,y);
			ans += (ll)-p * c[4];
			x -= p,y -= p;
		} else if(x > 0 && y > 0){
			int p = min(x,y);
			ans += (ll)p * c[1];
			x -= p,y -= p;
		}
		
		if(x <= 0) ans += (ll)-x * c[3];
		else ans += (ll)x * c[6];
		if(y <= 0) ans += (ll)-y * c[5];
		else ans += (ll)y * c[2];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

