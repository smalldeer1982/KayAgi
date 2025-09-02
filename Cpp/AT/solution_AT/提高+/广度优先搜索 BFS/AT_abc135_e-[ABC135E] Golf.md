# [ABC135E] Golf

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc135/tasks/abc135_e

無限に広がる二次元格子があります。ジャンボ高橋君はこの上でゴルフをすることにしました。

ボールははじめ原点 $ (0,\ 0) $ にあり、ゴールは格子点(座標がいずれも整数である点) $ (X,\ Y) $ です。ジャンボ高橋君は $ 1 $ 打ごとに、次の操作を行えます。

- その時点でボールがある点とのマンハッタン距離が $ K $ であるような格子点を $ 1 $ つ選び、その点にボールを飛ばす。

ゴールと同じ座標にボールが来た時点でクリアとなり、それまでの打数がスコアとなります。ジャンボ高橋君はできるだけ少ないスコアでクリアしたいと思っています。

クリアが可能かどうか判定し、可能ならばスコアが最小となるボールの動かし方を $ 1 $ つ求めてください。

マンハッタン距離の説明$ 2 $ つの座標 $ (x_1,\ y_1),\ (x_2,\ y_2) $ に対するマンハッタン距離は、$ |x_1-x_2|+|y_1-y_2| $ と定義されます。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ -10^5\ \leq\ X,\ Y\ \leq\ 10^5 $
- $ (X,\ Y)\ \neq\ (0,\ 0) $

### Sample Explanation 1

\- $ (0,\ 0),\ (7,\ 4) $ のマンハッタン距離は $ |0-7|+|0-4|=11 $。 - $ (7,\ 4),\ (2,\ 10) $ のマンハッタン距離は $ |7-2|+|4-10|=11 $。 - $ (2,\ 10),\ (-1,\ 2) $ のマンハッタン距離は $ |2-(-1)|+|10-2|=11 $。 以上より、このボールの動かし方は正しいです。 また、$ 3 $ 打より少なくクリアする方法は存在しません。

## 样例 #1

### 输入

```
11
-1 2```

### 输出

```
3
7 4
2 10
-1 2```

## 样例 #2

### 输入

```
4600
52 149```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
9 9```

### 输出

```
5
1 3
4 2
4 6
6 8
9 9```

# 题解

## 作者：蒟酱 (赞：8)

[一道](https://atcoder.jp/contests/abc135/tasks/abc135_e)~~还行的~~构造题。  
题目大意：一开始你在初始点 $(0,0)$，每次可以跳的曼哈顿距离为 $k$，输出抵达 $(x,y)$ 跳的最少次数并且输出方案。  
首先发现 $x$ 和 $y$ 可正可负，不如把 $x$ 和 $y$ 都取绝对值，在之后输出时携带符号输出即可。  
因为每次的操作相当于把 $k$ 瓜分成 $x$ 和 $y$。先考虑如果 $k$ 是奇数那么只能拆成奇数和偶数，可以通过调控 $k$ 的数量来构造答案。如果 $k$ 是偶数 $x+y$ 是偶数，只要把 $k$ 拆成两个偶数或者奇数也是能做到的。只有 $k$ 是偶数并且 $x+y$ 是奇数时无解。  
设答案为 $n$，在 $x$ 轴和 $y$ 轴上的正向移动距离为 $a$，反向移动距离为 $b$，那么 $x+y\le n\times k$ 且 $(n\times k-x-y)\mod2=0$，这个不好解，但是 $x$ 和 $y$ 值域不大所以直接枚举 $n$ 的值就行。$a+b=n\times k$，$a-b=x+y$ 解出 $a=\dfrac{n\times k+x+y}2$，$b=\dfrac{n\times k-x-y}2$。
那就直接考虑在前进时的 $3$ 个情况即可：（这里的 $b$ 会随着逆向移动的距离而减小）
- $b\gt k$，选择 $x$ 和 $y$ 里当前位置距离最终位置比较近的一个，逆向移动 $k$。
- $b\leq k$，选择 $x$ 和 $y$ 里当前位置距离最终位置比较近的一个，逆向移动 $b$，另一个移动 $k-b$。
- $b=0$，任意把 $x$ 和 $y$ 推进，最艰难的时候过去了，可以随便放保证了。

放个代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) x.begin(),x.end()
using std::cin;using std::cout;
using loli=long long;
using venti=__int128_t;
using pii=std::pair<int,int>;
int n=2,k,x,y;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>k>>x>>y;
	int opx=x/abs(x),opy=y/abs(y);x*=opx,y*=opy;
	if(x+y==k)return cout<<"1\n"<<x*opx<<' '<<y*opy,0;
	if(k%2==0&&(x+y)%2==1)return cout<<"-1",0;
	for(;n*k<x+y||(n*k-x-y)%2;)n++;
	cout<<n<<'\n';
	int b=(n*k-x-y)/2;
	for(int nx=0,ny=0;n--;cout<<nx*opx<<' '<<ny*opy<<'\n')
		if(b){
			if(b>=k){if(x-nx<y-ny)nx-=k;else ny-=k;b-=k;}
			else{if(x-nx<y-ny)nx-=b,ny+=k-b;else ny-=b,nx+=k-b;b=0;}
		}else{if(nx<x){if(x-nx>=k)nx+=k;else ny+=k-x+nx,nx=x;}else ny+=k;}
	return 0;
}
```

---

## 作者：timefinder (赞：5)

考虑如何处理出最少步数，或许对我们有所启发。

先来考虑 $k$ 为奇数。

首先用暴搜打表，以图中中心部分为 $(0,0)$。这里 $k=3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/08qw6bgf.png)

你发现了什么？

如果我们把所有距离为 $2$ 的点用 ```#``` 表示，其余用 ```.```，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7yu70tcg.png)

同上，着重标出 $4$，有：

![](https://cdn.luogu.com.cn/upload/image_hosting/xlnt1v9s.png)

标出 $3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/a0rp3y34.png)

想必大家现在都知道了，$3$ 步到达的点，恰好都是在原点 $3$ 个 $k$ 范围之内，横纵坐标绝对值之和为奇数的点，但要除去 $1$ 步就能到达的那些。

$2n$ 步**之内**就能到达的点，恰好都是在原点 $2n$ 个 $k$ 范围之内，横纵坐标绝对值之和为偶数的；

$2n+1$ 步**之内**就能到达的点，恰好都是在原点 $2n+1$ 个 $k$ 范围之内，横纵坐标绝对值之和为奇数的。

考虑 $k$ 为偶数的情况，也类似。当然此时若横纵坐标绝对值之和为奇数将无法到达，于是即可判断无解。

现在从 $(x,y)$ 逆推回原点。

如果当前位置距离原点较远，在四个水平/垂直方向上一步就跨 $k$ 格，总有一个会是最佳选择之一。

如果这样四种方式每一个均不是最佳选择，显然你距离原点已经足够近（$2$ 个 $k$ 范围之内），那么处理出来到该点的那一个"1 步点"即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7,N=3e6+5,T=5+5;
int k,X,Y,tot,ansX[N],ansY[N];
bool akioi;
int D(int x,int y){
	int r=abs(x)+abs(y),t=abs(x-y),dist=(r+k-1)/k,ans=0;
	if(k&1){
		if(r==0) ans=0;
		else if(r==k) ans=1;
		else{
			if(t%2==1){
				if(dist==1) ans=3;
				else ans=dist+!(dist%2);
			}else ans=dist+(dist%2);
		}
	}else{
		if(r==0) ans=0;
		else if(r==k) ans=1;
		else{
			if(t%2==1) ans=INF;
			else{
				if(dist==1) ans=2;
				else ans=dist;
			}
		}
	}
	return ans;
}
int main(){
	scanf("%d%d%d",&k,&X,&Y);
	ansX[++tot]=X,ansY[tot]=Y; 
	if(D(X,Y)==INF) {cout<<-1<<'\n';return 0;}
	while(D(X-k,Y)==D(X,Y)-1) X-=k,ansX[++tot]=X,ansY[tot]=Y;
	while(D(X+k,Y)==D(X,Y)-1) X+=k,ansX[++tot]=X,ansY[tot]=Y;
	while(D(X,Y-k)==D(X,Y)-1) Y-=k,ansX[++tot]=X,ansY[tot]=Y;
	while(D(X,Y+k)==D(X,Y)-1) Y+=k,ansX[++tot]=X,ansY[tot]=Y;
	if(abs(X)+abs(Y)==0) akioi=1;
	else if(abs(X)+abs(Y)==k) ansX[++tot]=0,ansY[tot]=0;
	else{
		if(abs(X)<abs(Y)){
			ansX[++tot]=X+(k-(abs(Y)-k+abs(X)))/2*(X<0?-1:1),ansY[tot]=Y+((k-(abs(Y)-k+abs(X)))/2+(abs(Y)-k+abs(X)))*(Y<0?1:-1);
		}else{
			swap(X,Y);
			ansX[++tot]=Y+((k-(abs(Y)-k+abs(X)))/2+(abs(Y)-k+abs(X)))*(Y<0?1:-1),ansY[tot]=X+(k-(abs(Y)-k+abs(X)))/2*(X<0?-1:1);
		}
		ansX[++tot]=0,ansY[tot]=0;
	}
	printf("%d\n",tot-1);
	for(int i=tot-1;i>=1;i--) printf("%d %d\n",ansX[i],ansY[i]);
}
```

---

## 作者：DiDi123 (赞：3)

# 一、题意
给你一个无限大的二维直角坐标系，你每次可以到达一个曼哈顿距离为 $k$ 的点，求到达 $(x,y)$ 步数最少的方案。

# 二、分析
比较奇怪的做法qwq

首先判断一下无解的情况。可以发现只有当 $x+y$ 为奇数且 $k$ 为偶数时无解（一定要取绝对值，~~我因为这个被卡了好久~~）

首先我们可以在直角坐标系里把所有与原点曼哈顿距离为 $k$ 的点构成的图形画出来（以 $k=3$ 为例）：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/bk6efwbk.png)

然后再从这个图形上再扩展一步：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/pp1emaxc.png)

所以能发现所有走两步能到达的点构成一下这个图形：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/8rfyx76i.png)

然后走三步就会得到一个更大的斜正方形，以此类推。

我们的想法就是先从原点扩展到离目标点最近的一个斜正方形，然后停止扩展，再由目标点扩展出来走一步得到的斜正方形，求出两个正方形的交点，然后跳到交点。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/cbqi389i.png)

特别的，如果两个正方形的交点都非正点，那么我们要先找目标点正方形在原点正方形中的一个角，然后跳到那个角上，再缩小一圈原点正方形，继续跳，由于那个角在阴影中，所以下一回就肯定能找到交点了。

然后如果跳到了原点正方形的交点上，就直接跳回原点就行了。

还有一种情况是目标点在原点走一步正方形之内，这时候我们还是尝试着画两个正方形取交点，如果取不到，就从目标点跳到目标点正方形的一个角上，再继续跳。

# 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000001
typedef long long ll;
ll k,tx,ty,cnt;
ll dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
struct pos
{
	ll x,y;
}path[MAXN];
pos O;
ll dis(pos p,pos q)
{
	return abs(p.x-q.x)+abs(p.y-q.y);
}
ll dd(pos p)
{
	return dis(O,p);
}
pos make_pos(ll xx,ll yy)
{
	pos tp;
	tp.x=xx,tp.y=yy;
	return tp;
}
pos pres;
ll el;
bool conn(pos lx,pos ly,pos rx,pos ry,pos &ans)
{
	double k1=(ly.y-lx.y)/(ly.x-lx.x);
	double k2=(ry.y-rx.y)/(ry.x-rx.x);
	if(k1==k2) return false;
	double ax,ay;
	ax=(lx.x*k1-rx.x*k2+rx.y-lx.y)*1.0/(k1-k2);
	ay=lx.y+k1*(ax-lx.x);
	if(ax!=ll(ax) || ay!=ll(ay)) return false;
	if(dis(make_pos(ll(ax),ll(ay)),pres)>k) return false;
	if(dd(make_pos(ll(ax),ll(ay)))>el) return false;
	ans.x=ll(ax),ans.y=ll(ay);
	return true;
}
void get_path(pos p)
{
	if(p.x==0 && p.y==0) return;
	if(dd(p)==k)
	{
		path[++cnt].x=p.x,path[cnt].y=p.y;
		return;
	}
	if(dd(p)%k==0)
	{
		ll y=dd(p);
		for(ll i=0;i<4;i++)
			if(dd(make_pos(p.x+dx[i]*k,p.y+dy[i]*k))==y-k)
			{
				get_path(make_pos(p.x+dx[i]*k,p.y+dy[i]*k));
				path[++cnt].x=p.x,path[cnt].y=p.y;
				return;
			}
	}
	if(dd(p)<k)
	{
		pos tp;
		for(ll i=0;i<4;i++)
			for(ll j=0;j<4;j++)
			{
				pos lx=make_pos(p.x+dx[i]*k,p.y+dy[i]*k);
				pos ly=make_pos(p.x+dx[(i+1)%4]*k,p.y+dy[(i+1)%4]*k);
				pos rx=make_pos(dx[j]*k,dy[j]*k);
				pos ry=make_pos(dx[(j+1)%4]*k,dy[(j+1)%4]*k);
				pres=p;
				el=k;
				if(conn(lx,ly,rx,ry,tp))
				{
					get_path(tp);
					path[++cnt].x=p.x,path[cnt].y=p.y;
					return;
				}
			}
		for(ll i=0;i<4;i++)
			if(dd(make_pos(p.x+dx[i]*k,p.y+dy[i]*k))<=k)
			{
				get_path(make_pos(p.x+dx[i]*k,p.y+dy[i]*k));
				path[++cnt].x=p.x,path[cnt].y=p.y;
				return;
			}
	}
	ll len=dd(p)/k;
	pos tp;
	for(ll i=0;i<4;i++)
		for(ll j=0;j<4;j++)
		{
			pos lx=make_pos(p.x+dx[i]*k,p.y+dy[i]*k);
			pos ly=make_pos(p.x+dx[(i+1)%4]*k,p.y+dy[(i+1)%4]*k);
			pos rx=make_pos(dx[j]*len*k,dy[j]*len*k);
			pos ry=make_pos(dx[(j+1)%4]*len*k,dy[(j+1)%4]*len*k);
			pres=p;
			el=len*k;
			if(conn(lx,ly,rx,ry,tp))
			{
				get_path(tp);
				path[++cnt].x=p.x,path[cnt].y=p.y;
				return;
			}
		}
	for(ll i=0;i<4;i++)
		if(dd(make_pos(p.x+dx[i]*k,p.y+dy[i]*k))<=len*k)
		{
			get_path(make_pos(p.x+dx[i]*k,p.y+dy[i]*k));
			path[++cnt].x=p.x,path[cnt].y=p.y;
			return;
		}
}
int main()
{
	cin>>k>>tx>>ty;
	if(abs(tx+ty)%2==1 && k%2==0)
	{
		puts("-1");
		return 0;
	}
	O.x=0,O.y=0;
	get_path(make_pos(tx,ty));
	cout<<cnt<<endl;
	for(ll i=1;i<=cnt;i++)
		cout<<path[i].x<<' '<<path[i].y<<endl;
}
```


---

## 作者：Unnamed114514 (赞：2)

\* 2665，但是如果按照这个做法做的话，感觉不止这个难度。

不妨令 $x\gets|x|,y\gets|y|$，否则得到方案后可以对 $x$ 或 $y$ 取反得到 $-x$ 和 $-y$ 的情况。

不妨令 $x\le y$，否则得到方案后交换 $x,y$ 即可。

容易想到一种方案可以在某一次到的点 $(x_1,y_1)$ 变成 $(x_1+1,y_1-1)$，下一次到的点 $(x_2,y_2)$ 变成 $(x_2,y_2-2)$，因此如果我们能到一个点 $(x,y)$ 那么所有 $(x',y')$ 满足 $2\mid((x+y)-(x'+y'))$ 也是可以到的。

因此我们可以得到无解的判定条件：$2\nmid(x+y)$ 且 $2\mid k$，因为此时到的点都满足 $2\mid(x+y)$。

接下来考虑构造方案，虽然这个结论只是充分的，但是如果其它情况都有方案的话，那么它就是充要的了。

有一个显然的下界是 $T=\lceil\dfrac{K}{x+y}\rceil$，但是如果 $x+y<K$ 一次显然不行，所以有其它的下界，因此，我们需要对 $x+y$ 和 $K$ 的关系进行分类讨论。

- $x+y=K$

输入输出练习。

- $x+y<K$

显然需要至少两次。

不妨假设需要两次，设中间点为 $(a,b)(a>0,b>0)$，显然我们有 $a>x,b<y$，否则如果 $a<x,b<y$ 就有 $K=a+b<x+y$，与分讨的条件矛盾；如果 $a>x,b>y$ 有 $a-x+b-y<a+b=K$，第二次移动显然没有方案，所以只有 $a>x,b<y$ 才行。

$$\begin{cases}a+b=k\\a-x+y-b=k\end{cases}$$

解出来是 $a=\dfrac{2k+x-y}{2}$，$b$ 的话带到第一个里面解就行了。

注意到若 $2\nmid(x+y)$，$a$ 不为整数，这个做法会挂掉，此时至少需要 $3$ 次且 $2\nmid K$。

考虑调整法。

第一次我们先到 $(x,K-x)$，令 $\Delta=K-x-y$。

然后我们要调整到 $(x,y)$，
因为 $2\nmid K,2\nmid(x+y)$，所以 $2\mid\Delta$，可以考虑判断类似于判断无解的策略调整 $y$，即分成两步操作，在 $y$ 减小的同时使 $x$ 增大，第二次使 $x$ 减小，从而调控 $y$ 的减小量，具体流程即：

$(x,K-x)\to(x+K-\dfrac{\Delta}{2},K-x-\dfrac{\Delta}{2})\to(x,K-x-\Delta)$

次数正好为 $3$，即上文提到的答案至少的值。

- $x+y>K$

可以做类似与上面的调整法。

先把 $x$ 调整到目标值，然后再调整 $y$，得到 $(x,y')(y'\ge y)$，令 $\Delta=y'-y$。

若 $y'=y$，此时直接结束即可，容易发现，这个的判定条件是 $K\mid(x+y)$，此时显然正好取到这个下界。

注意到因为 $x\le y$，所以一定存在两个到达的点 $(x'',y'')$ 满足 $x''=x$。

因为 $y$ 开始调整时 $x$ 已经调整好了，所以证明的话可以可以考虑 $y$ 被调整的次数。

如果 $x\ge 2K$，那么 $y\ge 2K$，显然是被至少调整过两次的。

如果 $K<x<2K$，那么第二次调整后 $y$ 一定被调整到了，又因为 $y>x>K$ 所以一定有剩余，需要再调整一次。

如果 $x=K$ 因为 $K\nmid(x+y)$ 所以 $y>k$，那么 $y$ 一定被至少调整 $2$ 次。

如果 $x<K$ 那么第一次调整一定也调整了 $y$，又因为 $x+y>K$ 所以第一次调整完后一定有剩余，也需要再调整一次。

所以一定存在两个 $x''=x$，证毕。

因为是后调整的 $y$，所以最后两次到的点一定都是 $(x,*)$ 的形式，用类似的做法先让 $x\gets x+\dfrac{\Delta}{2}$，然后再让 $x\gets x-\dfrac{\Delta}{2}$，这样的话我们两次调整 $y$，每次减小 $\dfrac{\Delta}{2}$，每次位移量仍然是 $K$，是正确的。

这时我们没有增加任何一次调整次数，取到了下界 $T$，所以一定是最优的。

但是这样有一个问题，就是若 $2\nmid\Delta$，上述做法是错误的，发现此时一定有 $2\nmid K$。

那么我们调整得到 $(x,y')$ 后，再调整一次得到 $(x,y'+K)$，就能使 $2\mid\Delta$ 了。

但是这样会让我们取不到理想的下界 $T$，但是在最先判无解的时候已经提到过了，每轮到的点 $(X,Y)$，$X+Y$ 的奇偶性是定值，那么无论我们怎么调整都不会改变 $\Delta$ 的奇偶性，又因为 $2\nmid\Delta$，所以 $\Delta\ne 0$，从而 $T$ 次一定不行，需要 $T+1$ 次。

而我们刚才的做法只增加了一次即一共 $T+1$ 次，恰好取到了下界，所以是最优的！

---

