# [ICPC 2020 Shanghai R] Traveling in the Grid World

## 题目描述

考虑一个由 $n$ 行和 $m$ 列组成的网格图案。总共有 $(n+1)\times(m+1)$ 个网格点，即 $n+1$ 条水平线和 $m+1$ 条垂直线的交点。我们将水平线从上到下编号为 $0$ 到 $n$。我们将垂直线从左到右编号为 $0$ 到 $m$。水平线 $i$ 和垂直线 $j$ 的交点命名为 $(i, j)$ ($0\le i\le n, 0\le j\le m$)。

在网格世界中旅行时有一些限制。当你位于点 $(x,y)$ 时，你可以选择一个目的地 $(x',y')$ 并沿着 $(x, y)$ 和 $(x', y')$ 之间的线段走过去。我们称这种操作为一次“行走”。如果在它们之间的线段上存在另一个不同于 $(x, y)$ 和 $(x', y')$ 的网格点，则该行走是被禁止的。你可以走任意多次，但两次连续行走的方向不能相同。（具体来说，如果你从 $(x_0, y_0)$ 走到 $(x_1, y_1)$，然后从 $(x_1, y_1)$ 走到 $(x_2, y_2)$，你必须确保 $(x_0-x_1)(y_1-y_2)
eq (x_1-x_2)(y_0-y_1)$。）从 $(x, y)$ 到 $(x', y')$ 的行走长度定义为两个端点之间的欧几里得距离，$\sqrt{(x-x')^2+(y'-y)^2}$。

从 $(0,0)$ 出发，你计划通过几次行走到达 $(n,m)$。由于这些烦人的规则，你可能需要一些转折点来实现你的目标。请找出你的行走的最小总长度。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
2 2
2 3```

### 输出

```
3.236067977499790
3.605551275463989```

# 题解

## 作者：EdenSky (赞：8)

# [P9830 Traveling in the Grid World](https://www.luogu.com.cn/problem/P9830)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/18344028)

## 思路分析

分析样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/oszgvk6u.png)

见红线，长宽各为 2，存在格点；黄线长 2 宽 3，没有格点。

考虑延长黄线使得长 4 宽 6，发现有格点。思考格点，如果长和宽都可以被分成 $p\times l$ 的格式，则存在格点。那么，就能想出：

推论 1：对于 $(0 \ , \ 0)$ 和 $(x \ , \ y)$ 之间没有格点，当且仅当 $\gcd(x \ , \ y )=1$。

> 对推论 1 的证明：
>
> 若存在格点 $A$，其坐标为 $(a \ , \ b)$，由于在同一直线上，斜率 $k$ 相同，则有 $k=\dfrac{a}{b}=\dfrac{x}{y}$，即 $b=\dfrac{a\times y}{x}$。由于 $b$ 为整数，则有 $x \ | \ a\times y$。
>
> 采用反证法，$\gcd(x \ , \ y )=1$ 时存在格点。
>
> 由于互质，$x=\prod\limits_{i=1}^{s1}p_i^{c_i} \ , \ y=\prod\limits_{i=1}^{s2}q_i^{d_i}$，假设 $x \ | \ y$，$y$ 必然有因子 $\prod\limits_{i=1}^{s1}p_i^{c_i}$，而实际上没有，所以 $y$ 对该式没有贡献。即：$x \ | \ a\times y \Longleftrightarrow x \ | \ a $。
>
> 而 $A$ 是线段上一点，有 $a<x$，又由于有 $x \ | \ a \Longrightarrow x \leq a$，冲突，由此可证。

得出推论 1 后，我们就能判断两点之间是否有格点了。那么如何得出最短答案呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/n4zzg90r.png)

（图是随手画的，具体有的性质以下文所述为准。）

见上，假设 $AD$ 之间存在格点（在之后称为不合法），于是我们找到任意一点 $C$ 进行更新。

假设 $C$ 为不合法，以图为例，在 $AC$ 上可以取一格点 $B$，根据三角形定则 $| \  BD \ |>| \ BC \ |+| \ CD \ |$，则 $B$ 更优。假设无法在 $AB$ 和 $BD$ 上取格点，那么 $B$ 的取点是合法的，可以得出：

推论 2：对于任意不合法的取点，必然可以在原线段取到更优的合法方案。

那么就有：

推论 2.1：最优方案必然是合法的。

> 对推论 2.1 的证明：
>
> 假设最优方案不合法，根据推论 2，则有更优方案可以更新，与原有条件冲突，由此可得。

以上是一个转折点的情况，那如果有多个转折点呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/mpbykew9.png)

如图，多个转折点的情况是不需要考虑的，见图，由于三角形定则，红色线的长度小于另外两条边之和。换句话说：

推论 3：最优方案只转折一次或零次。

于是我们只要枚举一个点就可以了，如果在整个 $n\times m$ 的范围枚举，寻找最优方案，但这个时间复杂度显然是不合理的。其实我们只需要枚举线段附近的点就可以，这样复杂度就可以变成 $\mathcal{O}(n)$。

## 代码实现

```cpp
#define by_wanguan
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int t,n,m,y11,y2,y3,g; double dn,dm,nowm,ans,k;
double dis(double a,double b,double x,double y){
  return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}
void solve(){
  k=(double)m/n;//斜率
  if((g=__gcd(n,m))==1)
    {printf("%.15lf\n",dis(0,0,n,m)); return ;}
  dn=n,dm=m;
  for(int i=1;i<n;i++){
    nowm=k*i;
    y11=(int)(nowm),y2=y11+1,y3=y11-1;//x坐标为i时附近的点的y坐标
    if(__gcd(n-i,m-y11)==1&&__gcd(i,y11)==1&&abs(y11-k*i)>1e-10)
    //判断是否合法，abs()是在判断是否为原线段上的点
	  ans=min(ans,dis(i,y11,n,m)+dis(0,0,i,y11));
    if(__gcd(n-i,m-y2)==1&&__gcd(i,y2)==1&&abs(y2-k*i)>1e-10)
      ans=min(ans,dis(i,y2,n,m)+dis(0,0,i,y2));
    if(__gcd(n-i,m-y3)==1&&__gcd(i,y3)==1&&abs(y3-k*i)>1e-10)
      ans=min(ans,dis(i,y3,n,m)+dis(0,0,i,y3));
  }
  printf("%.15lf\n",ans);
}
int main(){
  scanf("%d",&t); while(t--){
  scanf("%d%d",&n,&m);
  ans=1e9;
  solve();
}
} 
```

[喵。](https://www.luogu.com.cn/record/170746019)

---

## 作者：Frozen_Ladybug (赞：2)

### 题目大意

由 $A(0,0)$ 到 $B(n,m)$ 连接一条由线段组成的折线段，且在任意一条线段上不能有其他整点。

比如连接 $(0,0),(2,4)$，这两个点所连成的线段中有一个整点是 $(1,2)$，不满足要求。

### 两个结论

1. 任意一个由两条线段组成的折线路径，如果非端点部分经过了另一个整点，则可以调整为一条更佳路径。

2. 如果存在一条超过两条线段的路径，则可以调整为一条由两条线段组成的路径。

第一条结论的证明：

如图，这是一条不满足要求的直线，其中 $AM$ 上有一整点为 $C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/qmtp1yb8.png)

对于三角形 $BCM$，两边之和大于第三遍，即 $CM+MB>BC$。所以 $A\to C\to B$ 比 $A\to M\to B$ 更佳。

第二条结论的证明：

如图，这条折线上有不止三个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/qk9ne0rq.png)

对于折线上任意一个中间的端点 $M$，且由结论一 $AMB$ 一定不共线。因为两点之间线段最短，所以 $A\to M\to B$ 比原来的折线更佳。

综上，最优解一定仅由两条线段组成；且任意一条线段，除了端点没有别的整点。

### 思路

不妨 $n<m$，遍历 $1\leq i\leq n-1$ 区间。则第 $i$ 行可能的拐点只能是靠 $(0,0)-(n,m)$ 这条线段最近的左右两个整点。

遍历的同时，依次找每一行的最小值，总体取最小值即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int T,n,m;
int gcd(int a,int b){
	if(!b) return a;
	return gcd(b,a%b);
}//取最大公约数
double dis(int x,int y,int nx,int ny){
	return sqrt(1ll*(x-nx)*(x-nx)+1ll*(y-ny)*(y-ny));
}//计算欧几里得距离
double ans;
void solve(int r,int c){//找最优解
	if(r<0||r>n||c<0||c>m) return;//超出范围
	if(1ll*c*n==1ll*m*r) return;//线段上有整点
	if(gcd(r,c)==1&&gcd(n-r,m-c)==1)
		ans=min(ans,dis(0,0,r,c)+dis(r,c,n,m));//最小值即(0,0)和(n,m)到这个点(r,c)的距离
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		if(gcd(n,m)==1){
			printf("%.15f\n",dis(0,0,n,m));
			continue;
		}//(0,0)到(n,m)上没有别的整点
		ans=1e18;
		for(int i=0;i<=n-1;i++){
			int p,t=1ll*(n-i)*m/n;
			p=m-t;//p是在y=i上的任意一个整点（因为两边对称，我取了靠左的那个点）
			solve(i,p);
			solve(i,p+1);
			solve(i,p-1);
		}
		printf("%.15f\n",ans);//输出答案
	}
	return 0;
}
```

---

## 作者：chen_zhe (赞：1)

以下内容转载自官方题解：

如果 $\gcd(m,n)=1$，那么我们可以直接通过去。

有个简单的结论是，如果 $\gcd(m,n)>1$，我们只需转折一次即可。那么如何确定转折点呢？

假设转折点是 $(x,y)$，我们希望 $\sqrt{x^2+y^2}+\sqrt{(m-x)^2+(n-y)^2}$ 最小，同时两端线段的 $\gcd$ 都是等于 $1$ 的。有一个性质表明，假设我们先最优化这个距离和，得到的解一定也是 $\gcd$ 满足要求的。这样的话，我们只需暴力枚举坐标去确定最近的点即可。

一个简要的证明：假设起点是 $A$，终点是 $B$。我们找到不在 $AB$ 连线上的使得 $AC+BC$ 最小的一点 $C$。假如 $AC$ 上有其他整点 $D$，且 $AD+BD$ 小于 $AC+BC$。那么 $AC$ 上没有其他整点，同理 $BC$ 上也没有其他整点。又因为 $AC$ 和 $BC$ 不同向（因为 $C$ 不在 $AB$ 连线上），所以 $C$ 是问题的答案。

---

