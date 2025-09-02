# Ray Tracing

## 题目描述

在一个$n\times m$的矩形房间里有$k$个传感器，第$i$个传感器位于$(x_i,y_i)$，所有的传感器位置互不相同

房间的一对对角位于$(0,0)$和$(n,m)$，房间的墙壁与坐标轴平行

在时刻$0$，有一束光线从$(0,0)$出发，向$(1,1)$的方向释放，这束光线以$\sqrt{2}m/s$的速度传播，因此，光线将在出发后恰好$1s$时到达点$(1,1)$

当光线碰到墙壁时，它将遵循反射角等于入射角的规则进行反射，当它碰到$4$个角中的任意一个时，就会立刻停止

对于每一个传感器，你需要计算光线第一次到达这个传感器所在点的时刻，如果光纤永远不会经过这个传感器，那么输出$-1$

## 说明/提示

在第一组样例中，光线将依次通过点$(0,0)\ (1,1)\ (2,2)\ (3,3)$。他将在$3s$后在$(3,3)$停下

第二组样例，光纤将会依次穿过如下的点：$(0,0)\ (1,1)\ (2,2)\ (3,3)\ (2,4)\ (1,3)\ (0,2)\ (1,1)\ (2,0)\ (3,1)\ (2,2)\ (1,3)\ (0,4)$。光线将在$12s$后在$(0,4)$停下，分别在点$(3,3)\ (2,4)\ (0,2)\ (2,0)\ (3,1)$处进行一次反射

## 样例 #1

### 输入

```
3 3 4
1 1
1 2
2 1
2 2
```

### 输出

```
1
-1
-1
2
```

## 样例 #2

### 输入

```
3 4 6
1 1
2 1
1 2
2 2
1 3
2 3
```

### 输出

```
1
-1
-1
2
5
-1
```

## 样例 #3

### 输入

```
7 4 5
1 3
2 2
5 1
5 3
4 3
```

### 输出

```
13
2
9
5
-1
```

# 题解

## 作者：Siyuan (赞：15)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-724C-Ray-Tracing/)

---

## Description

> 题目链接：[Codeforces 724C](https://codeforces.com/contest/724/problem/C)

有一个 $n\times m$ 的矩形，四周有围墙围起来，其左上角和右下角的坐标分别为 $(0,0)$ 和 $(n,m)$。从 $(0,0)$ 开始以 $\sqrt 2$ 个单位每秒的速度向 $(1,1)$ 的方向发射一束光线，每次遇到墙都正常反射（符合物理的反射），光线射到顶点会被吸收。在这个矩形内有 $k$ 个点，坐标分别为 $(x_i,y_i)$，求每个点第一次被光线经过的时刻。

数据范围：$2\le n,m\le 10^5$，$1\le k\le 10^5$，$1\le x_i<n$，$1\le y_i<m$

------

## Solution

对于这类矩形内上的反射问题，我们可以将矩形**无限展开**，那么相当于我们把点按照矩形边界**对称**，光线也就边成了**一条直线**。

我们考虑对称后的点的坐标是什么。如果原来的坐标为 $(x,y)$，那么按照第 $k$ 条横轴展开的坐标为 $(x,2km-y)$，按照第 $k$ 条纵轴展开的左边为 $(kn-x,y)$。因此，如果我们沿着若干条轴展开后，坐标一定可以写成 $(k_1n\pm x,k_2m\pm y)$ 的形式。

由于我们知道了展开后的坐标，那么有如下方程：
$$k_1n\pm x=k_2m\pm y\Longrightarrow k_1n-k_2m=\pm x\pm y$$
发现这是一个**丢番图方程**，我们可以直接解出 $(k_1,k_2)$ 的通解。

但是，题目中规定光线在矩形顶点位置会被吸收，那么我们就要保证**坐标的绝对值小于等于 $\operatorname{lcm}(n,m)$**，否则光线一定会经过 $\operatorname{lcm}(n,m)$ 这个点而被吸收。

因此，我们对 $4$ 种情况分别求解，找到一组解使得 $k_1n\pm x$ 的值尽量小且大于 $0$。形象地说，就是使得 $k_1n\pm x$ 最小并满足 $0<k_1n\pm x<\operatorname{lcm}(n,m)$。

这个最小的符合条件的解就是答案。

**时间复杂度**：$O(k\log n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
typedef long long LL;

const LL INF=1LL<<60;
int n,m,k;
LL mx;

int gcd(int a,int b) {
	return b?gcd(b,a%b):a;
}
int exgcd(int a,int b,int &x,int &y) {
	if(!b) {x=1,y=0;return a;}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x; return d;
}
LL solve(int dx,int dy) {
	int a=2*n,b=-2*m,c=dy-dx,x,y;
	int d=exgcd(a,b,x,y);
	if(c%d) return INF;
	a/=d,b/=d,c/=d,b=std::abs(b),x=(x*c%b+b)%b;
	LL ans=2LL*n*x+dx;
	if(ans<=0||ans>=mx) return INF;
	return ans;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	mx=1LL*n*m/gcd(n,m);
	while(k--) {
		int x0,y0;
		scanf("%d%d",&x0,&y0);
		LL ans=INF;
		ans=std::min(ans,solve(+x0,+y0));
		ans=std::min(ans,solve(+x0,-y0));
		ans=std::min(ans,solve(-x0,+y0));
		ans=std::min(ans,solve(-x0,-y0));
		printf("%lld\n",ans==INF?-1:ans);
	}
	return 0;
}
```





---

## 作者：Acoipp (赞：3)

## 解题思路

首先，我们单独看 $x$ 坐标，当光线没有碰到右边的墙时，不管 $y$ 如何变化，$x$ 总是每次加 $1$；当光线碰到右边的墙反射回来后，$x$ 坐标会依次减 $1$，直到再次碰到左边的墙，反射后就又开始了一次先加后减的坐标变化。

$y$ 坐标同理，只不过是先碰到上边的墙，然后再反射到下边的墙，它也有先依次加 $1$，然后依次减 $1$ 的规律。

我们发现，对于 $x$ 坐标，变化周期是 $2n$ 次一个，每个周期的每个坐标依次都是 $0,1,2,...,n,n-1,n-2,...,1$，我们把它们存到 $a$ 数组里（下标从 $0$ 开始）。

对于 $y$ 坐标，变化周期是 $2m$ 次一个，每个周期的每个坐标依次都是 $0,1,2,...,m,m-1,m-2,...,1$，同样地，把它们存到 $b$ 数组里（下标从 $0$ 开始）。

这样，题目的初始化就完成了，思路也基本上捋清楚了，接下来就是进行公式推导，进一步求解这道题。

## 公式推导

因为题目告诉了我们一个坐标 $x,y$（即各个传感器），询问这个坐标会不会被光线经过，需要求出一个经过的最小时间，所以我们设这个最小时间为 $t$，则
$$
a_{t \bmod 2n}=x,b_{t \bmod 2m}=y
$$
因为我们知道在 $a$ 和 $b$ 数组中哪些数是等于 $x,y$ 的，设这些数的下标为 $x_1,y_1$，所以此方程就可以变为：
$$
x_1 \equiv t\pmod {2n},y_1 \equiv t\pmod {2m}
$$

我们就可以用解一个 **同余方程组** 的方法来解这两个方程。

但是，单单这样解，我们需要用到 **扩展中国剩余定理**，为了确保用到的知识点足够简单，那么我们可以从另一个角度来思考，把这个方程组拆成两个方程，先看第一个方程：
$$
x_1 \equiv t\pmod {2n}
$$
容易得知这个方程的一个解就是 $t=x_1$，那么我们表示第一个方程的通解就为：$x_1+2pn(p \in \mathbb{Z})$，接下来看第二个方程：
$$
y_1 \equiv t\pmod {2m}
$$
把第一个方程的通解代入第二个方程，就为：
$$
x_1+2pn\equiv y_1 \pmod {2m}
$$
其中 $p$ 未知，可以根据同余的相关定义再次转化方程：
$$
2pn+2qm=y_1-x_1
$$
其中，$p,q$ 是未知数，那么方程变成了一个 $ax+by=c$ 的模式，我们这时就可以只用 **扩展欧几里得** 来求解，但是在 $a,b$ 数组中，同一个 $x,y$ 可能对应不同的下标 $x_1,y_1$，我们就要对这些下标进行枚举，然后取所有枚举出来的答案的最小值。

## 时间复杂度：

为了表述方便，此处默认为 $n,m$ 同阶。单次扩展欧几里得算法的时间复杂度是 $O(\log n)$ 的，因为 $k$ 个传感器需要 $k$ 次枚举求值，所以时间复杂度一共是 $O(k\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k,x,y,l[100005][2],i,j,cnt,ans,r[100005][2];
//扩展欧几里得模板
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	ll temp = exgcd(b,a%b,x,y);
	ll z = x;
	x = y,y = z-y*(a/b);
	return temp;
}
//按照上面的公式进行传参，推导，求值
ll solve(ll a,ll b,ll c,ll d){
	ll a1 = c,b1 = d,c1 = b-a,x,y;
	ll d1 = exgcd(a1,b1,x,y);
	if(c1%d1!=0) return -1;
	ll x0 = a+c*(x*(c1/d1)),y0 = c/__gcd(c,d)*d;
	return (x0%y0+y0)%y0;      //通过取模取最小值
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;     
	//此处是分别记录每个x,y值有多少对应的下标
	for(i=0;i<=n;i++){
		if(i==0) l[i][0]=l[i][1]=0;
		else if(i==n) l[i][0]=l[i][1]=n;
		else l[i][0] = i,l[i][1] = 2*n-i;
	}
	for(i=0;i<=m;i++){
		if(i==0) r[i][0]=r[i][1]=0;
		else if(i==m) r[i][0]=r[i][1]=m;
		else r[i][0] = i,r[i][1] = 2*m-i;
	}
	//此处是枚举答案，取最小，然后输出
	while(k--){
		ans=LLONG_MAX;     //先赋一个很大的值
		cin>>x>>y;
		for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				cnt=solve(l[x][i],r[y][j],2*n,2*m);     //枚举，配对，取最小
				if(cnt!=-1) ans=min(ans,cnt);
			}
		}
		if(ans==LLONG_MAX) cout<<"-1\n";    //无解
		else cout<<ans<<endl;               //有解
	}
}
```

---

## 作者：Louis_lxy (赞：2)

## 题目翻译

给一个矩形，上面有一些点，求一条从 $(0,0)$ 出发的，经过 $(1,1)$ 的一条射线，求这条射线在反射后会经过哪些点，射线在进入死角时停止反射。

## 思路

易得反射其实就是将这个矩形翻转，然后原射线不变。所以整张图就变成了一个由若干矩形组成的图形。

然后我们来想想什么时候停下。由此射线过点 $(0,0)$ 和 $(1,1)$ 可知，无论何时，它的纵坐标一定等于横坐标，而翻转本质是给长（或宽）加上 $n$（或 $m$）。因此这个最终的图形一定为 $nx\times my$。因此最终一定停在 $(\operatorname{lcm}(n,m),\operatorname{lcm}(n,m))$。

那我们接着考虑是否能遇见。如果我们设一个点的最初坐标为 $(x,y)$。那么进行 $a$ 次横轴翻转和 $b$ 次纵轴翻转后的坐标就是 $(an\pm x,bm\pm y)$。但是这个仍旧不好求，因此考虑展开，$an\pm x=bm\pm y\Rightarrow an-bm=\pm x\pm y$，这个方程就可以算了，明显是个[丢番图方程](https://blog.csdn.net/m0_69478345/article/details/128756042)。然后直接用[扩展欧几里得算法](https://blog.csdn.net/destiny1507/article/details/81750874)，就可以求了，记得要枚举四种情况。

## 代码

其实代码还是很好写的，但是由于我太蒻了，所以一直写挂，最终按照@[Siyuan](https://www.luogu.com.cn/user/49725) 巨佬的代码写的（不是抄袭）。不过我感觉我的代码很丑，就不全部贴了，~~我还无聊的全部开 `long long`。~~

求丢番图方程（其实有更简单的方法但是我写挂了）。

```cpp
long long solve(long long dx, long long dy)
{
	long long a = 2 * n, b = -2 * m, c = dy - dx, x, y;
	long long d = exgcd(a, b, x, y);
	if (c % d)
		return LLONG_MAX;
	a /= d, b /= d, c /= d, b = abs(b);
	x = (x * c % b + b) % b;
	long long ans = 2 * n * x + dx;
	if (ans <= 0 || ans >= _lcm)
		return LLONG_MAX;
	return ans;
}
```

其它都很简单就不贴了。

## 后记

其实我最初的时候是用另一种方式化简，然后直接变成类似 $ax+by=c$ 的形式，但是后来发现可能会有实数，然后就求不了了，有实数的原因是我不是直接求结果，进行了转换。

---

## 作者：Lonelyhacker (赞：1)

## 题意

在一个 $n \times m$ 的网格图中，有一束光从 $(0, 0)$ 开始向点 $(1, 1)$ 的方向射出，每秒移动 $\sqrt{2}$ 米，即沿着直线 $y = x$ 的方向运动，碰到边界时遵循光的反射规律反射。给你 $k$ 个传感器，当光束**第一次**经过传感器时记录运动的时间，若从未被经过则标记为 $-1$。当光束运动至 $4$ 个角的任意一个时停止运动。顺序输出 $k$ 个传感器被经过的时间。

## 题解

此题疑似是奇妙数论题，但是这里提供一个简单的思路。  
很显然，每次反射后的光线都垂直于反射前的光线，因此这两条直线的斜率相乘等于 $-1$，即 $k_1 \cdot k_2 = -1$。有了斜率和反射的点的坐标，我们就可以求出新的直线的解析式。  
那么此题就做完了，很简单的模拟题。只要检查每个检查点是否都在这条直线上后记录时间即可。

## 代码

记录答案的数组以及时间戳记得开 `long long`。   
如果真要模拟，一定谨记在草稿纸上模拟一下，~~别写着写着自己给自己绕晕了，最后无力地看着自己写成的屎山代码。~~
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int V = 2e5+5, N = 1e5+5;
vector <int> sum[V], diff[V];
int n, m, k, posx[N], posy[N];
ll ans[N];
int main(){
	memset(ans, -1, sizeof(ans));
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++){
		cin >> posx[i] >> posy[i];
		sum[posx[i]+posy[i]].push_back(i);
		diff[posy[i]-posx[i]+(N-5)].push_back(i);
	}
	int x = 0, y = 0, dx = -111, dy = -111, b = 0, status = 1;
	ll timer = 0;
	// status表示直线的方向是由斜向右上(1)，斜向右下(2)，斜向左下(3)，斜向左上(4) 
	// 当status == 1 or 3时，k = 1, status == 2 or 4, k = -1 
	while (true){
		if ((dx == 0 || dx == n) && (dy == 0 || dy == m)) break;
		if (status == 1){        // y = x + b
			dy = n+b;
			dx = m-b;
			if (dy < m) dx = n, status = 4;
			else dy = m, status = 2;
			for (auto i : diff[b+(N-5)])
				if (ans[i] == -1)
					ans[i] = timer+abs(x-posx[i]);
			b = dx+dy;
			timer += abs(dx-x);
			x = dx, y = dy;
		} else if (status == 2){ // y = -x + b
			dy = -n+b;
			dx = b;
			if (0 < dy) dx = n, status = 3;
			else dy = 0, status = 1;
			for (auto i : sum[b]) 
				if (ans[i] == -1)
					ans[i] = timer+abs(x-posx[i]);
			b = dy-dx;
			timer += abs(dx-x);
			x = dx, y = dy;
		} else if (status == 3){ // y = x + b
			dy = b; 
			dx = -b;
			if (0 < dy) dx = 0, status = 2;
			else dy = 0, status = 4;
			for (auto i : diff[b+(N-5)]) 
				if (ans[i] == -1)
					ans[i] = timer+abs(x-posx[i]);
			b = dx+dy;
			timer += abs(dx-x);
			x = dx, y = dy;
		} else if (status == 4){ // y = -x + b
			dy = b;
			dx = b-m;
			if (dy < m) dx = 0, status = 1;
			else dy = m, status = 3;
			for (auto i : sum[b])
				if (ans[i] == -1)
					ans[i] = timer+abs(x-posx[i]);
			b = dy-dx;
			timer += abs(dx-x);
			x = dx, y = dy;
		} else exit(0);
	}
	for (int i = 1; i <= k; i++) cout << ans[i] << '\n';
	
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：1)

联系物理学模型，可以将问题转化为：一个点要经过多少次横向翻折、多少次纵向翻折处于直线 $y=x$ 上（详情见图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/8idj10hu.png)

设：在 $k_1$ 次横向翻折，$k_2$ 次纵向翻折后，符合条件。

显然可以列出方程：

$$2n\lfloor \frac{k_1+1}{2} \rfloor+(-1)^{k_1}x=2m\lfloor \frac{k_2+1}{2} \rfloor+(-1)^{k_2}x$$

分类讨论可以得到一系列方程组，这是平凡的，此处不进行列出，详情见代码。

这些方程组都形如 $nx-my=c$，使用扩展欧几里德定理解出即可。注意到等式左侧系数一定，可以只进行一次运算，然后再根据 $c$ 进行调整，使得时间复杂度为 $O(\log N+q)$，但为了方便实现，我使用了二分进行调整（要是考场上直接写二分就好了，分讨写炸了）。

```cpp
#include<bits/stdc++.h>
using ll=long long;
using namespace std;
const ll INF=0x3f3f3f3f3f3f3f3f;
ll n,m,q,x,y,k1,k2,ans,del,gcd;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){x=1;y=0;return a;}
    ll gcd=exgcd(b,a%b,x,y);
    ll p=x;x=y;y=p-a/b*y;
    return gcd;
}
bool solve(ll a,ll b,ll &x,ll &y,ll c){
    ll gcd=exgcd(a,b,x,y);
    if(c%gcd)return 0;c/=gcd;a/=gcd;b/=gcd;
    x*=c;y*=-c;
    ll l=-1e9,r=1e9,mid,ans;
    while(l<=r){
        mid=l+r>>1;
        if(mid*a+y>=0&&mid*b+x>=0)ans=mid,r=mid-1;
        else l=mid+1;
    }
    x+=ans*b;y+=ans*a;
    return 1;
}
int main(){
    // freopen("physics.in","r",stdin);
    // freopen("physics.out","w",stdout);
    ios::sync_with_stdio(cin.tie(cout.tie(0)));
    cin>>n>>m>>q;
    while(q--){
        cin>>x>>y;ans=INF;
        //1.k1,k2%2==0:
        if(solve(n,m,k1,k2,y-x))
            if(k1%2==0&&k2%2==0)ans=min(ans,k1*n+x);
        //2.k1%2==0,k2%2!=0:
        if(solve(n,m,k1,k2,-x-y+m))
            if(k1%2==0&&k2%2!=0)ans=min(ans,k1*n+x);
        //3.k1%2!=0,k2%2==0:
        if(solve(n,m,k1,k2,x+y-n))
            if(k1%2!=0&&k2%2==0)ans=min(ans,k2*m+y);
        //4.k1%2!=0,k%2!=0:
        if(solve(n,m,k1,k2,x-y-n+m))
            if(k1%2!=0&&k2%2!=0)ans=min(ans,k1*n+n-x);
        printf("%lld\n",ans==INF?-1:ans);
    }   
    return 0;
}
```


---

## 作者：yzh_Error404 (赞：1)

对于光线反射类的题目，第一个想到的就是将反射转化为进入一个坐标相对称的矩形，这样就可以将经过的路径转化为一条直线，更好做。

所以可以将这个矩形扩展到整个第二象限，路径则为函数 $y=x$，现在询问一个点就等同于在询问路径上的点。

根据观察，相邻四个矩形（不是每四个相邻，是从零点开始四个一组计数）都是关于中心那个点对称的（换一种说法，也就是每有相邻边的两个矩形，坐标都是关于这条边对称的），所以可以通过分讨来看这四个点是否在路径上。

若原来的点为 $(x,y)$，那么最初的四个点分别为 $(x,y)$，$(x,2m-y)$，$(2n-x,y)$，$(2n-x,2m-y)$。

以点 $(x,2m-y)$ 举例，所有这样的点可以表示为 $(x+2k_1n,2m-y+2k_2m)(k_1,k_2\in\mathbb{N})$，那么就可以列出如下的方程：

$$ 
2k_1n-2k_2m=2m-y-x
$$

显然是一元二次方程的形式，用扩展欧几里得解出最小自然数解即可。

然后将四类点全部解一遍，找出最小值就做完了。

复杂度为 $O(k\log n)$，默认 $n,m$ 同阶。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q;
inline void exgcd(int a,int b,int &x,int &y)
{
    if(!b)return x=1,y=0,void();
    exgcd(b,a%b,x,y);
    int p=x;x=y;y=p-(a/b)*y;
}
inline int calc(int a,int b,int k)
{
    int g=__gcd(a,b);
    if(k%g!=0)return 1e18;
    a/=g;b/=g;k/=g;
    int x=0,y=0;
    exgcd(a,b,x,y);
    x*=k,y*=k;y=-y;
    if(b<=0)b=-b,a=-a;
    if(x>=0)
    {
        int cnt=x/b;
        x%=b;y+=cnt*a;
        if(y>=0)return x;
        else return 1e18;
    }
    else
    {
        int cnt=(-x)/b;
        x+=cnt*b;y+=cnt*a;
        if(x<0)x+=b,y+=a;
        if(y>=0)return x;
        else return 1e18;
    }
    return 1e18;
}
signed main()
{
    // freopen("physics.in","r",stdin);
    // freopen("physics.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&q);
    for(register int i=1;i<=q;i++)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        int mn=1e18;
        int tmp;
        tmp=calc(2*n,2*m,y-x);
        if(tmp!=1e18&&x+2*n*tmp>=0)mn=min(mn,x+2*n*tmp);
        tmp=calc(2*n,2*m,2*m-y-x);
        if(tmp!=1e18&&x+2*n*tmp>=0)mn=min(mn,x+2*n*tmp);
        tmp=calc(2*n,2*m,y-2*n+x);
        if(tmp!=1e18&&2*n-x+2*n*tmp>=0)mn=min(mn,2*n-x+2*n*tmp);
        tmp=calc(2*n,2*m,2*m-y-2*n+x);
        if(tmp!=1e18&&2*n-x+2*n*tmp>=0)mn=min(mn,2*n-x+2*n*tmp);
        printf("%lld\n",mn==1e18?-1:mn);
    }
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

有一个左下角是原点，$n\times m$ 的矩阵框架，一个动点点从原点出发，朝直线 $y=x$ 方向每个单位时间移动 $\sqrt{2}$ 的距离，碰到框架时会反射。如果运动到某个顶点则立刻结束运动。给你 $k$ 个坐标，判断它们是否被经过，如果被经过，第一次被经过时动点运动了多少秒。

## 题目分析

模拟赛中这道题以部分分的形式出现，通过将 $n$ 调至 $10^9$ 的方式强制要求了复杂度为 $O(k\log n)$ 的方法作为正解。但这题还是有无脑的 $O(n)$ 模拟做法的（当然，需要配备 $O(1)$ 的哈希表）。

显然边框上的点只有 $O(n)$ 个，每个点出发的方向也只有两种，由于不会循环，我们只需要模拟这个运动过程即可。

运动的方向可以抽象成两类直线 $y=x+k,y=-x+k$ 上的两种方向运动，共四类，每一类用哈希表存 $k$ 对应的出发点，查询直接四类取 $\min$ 即可，复杂度 $O(n)$。

难过，因为这题被拉爆了，去补 $O(k\log n)$ 做法了嘤嘤嘤。

$O(n)$ 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,M=4e5+5,inf=(1LL<<31)-1;
const ll llf=3e18;
int n,m,q;
#include<bits/extc++.h>
using namespace __gnu_pbds;
gp_hash_table<int,ll>P[5];
inline void insert(int ty,int k,ll w){
	if(P[ty].find(k)==P[ty].end())P[ty][k]=w;
}
inline void solve(int x,int y,int ty,ll tm){
	if(ty==1){
		//y=x+k
		int k=y-x;
		insert(1,k,x-tm);
		int ny=n+k;
		if(ny==m)return;
		if(ny>0&&ny<m)solve(n,ny,2,tm+n-x);
		else solve(m-k,m,4,tm+m-y);
	}
	if(ty==2){
		//y+x=k
		int k=x+y;
		insert(2,k,x+tm);
		int ny=k;
		if(ny==m)return;
		if(ny>0&&ny<m)solve(0,ny,1,tm+x);
		else solve(k-m,m,3,tm+m-y); 
	}
	if(ty==3){
		//y=x+k;
		int k=y-x;
		insert(3,k,x+tm);
		int ny=k;
		if(ny==0)return;
		if(ny>0&&ny<m)solve(0,ny,4,tm+x);
		else solve(-k,0,2,tm+y);
	}
	if(ty==4){
		//y+x=k
		int k=x+y;
		insert(4,k,tm-x);
		int ny=k-n;
		if(ny==0)return;
		if(ny>0&&ny<m)solve(n,ny,3,tm+n-x);
		else solve(k,0,1,tm+y);
	}
}

inline void Main(){
	n=read(),m=read(),q=read();
	solve(0,0,1,0);
	rep(i,1,q){
		int x=read(),y=read();
		ll ans=llf;
		if(P[1].find(y-x)!=P[1].end())ans=min(ans,x-P[1][y-x]);
		if(P[2].find(y+x)!=P[2].end())ans=min(ans,P[2][x+y]-x);
		if(P[3].find(y-x)!=P[3].end())ans=min(ans,P[3][y-x]-x);
		if(P[4].find(y+x)!=P[4].end())ans=min(ans,P[4][x+y]+x);
		if(ans==llf)cout <<"-1\n";
		else cout <<ans<<'\n';
	}
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```


---

## 作者：__XU__ (赞：0)

# CF724C 题解

### 题目大意：

给你多组坐标，判断这多组坐标是否在 $y=x$ 在未经过四边形端点的反弹路径上。

### 做法：

如图，如果模拟一个在四边形内反弹的过程是非常麻烦的而且不好做。

![](https://cdn.luogu.com.cn/upload/image_hosting/k96jut78.png)

但仔细观察后发现，如果把四边形沿着 $y=x$ 这条直线展开，直到碰见另一个端点为止。这样我们就只需判断点 $(x,y)$ 关于 $y=km$ 与 $y=kn$ 的对称点是否在 $y=x$ 上即可。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e1yy5otf.png)

我们设解析式一边坐标为 $(x,y)$ 则其关于 $y=km$ 的对称点就为 $(x,2km \pm\ y)$（中点公式可得）。同理关于 $y=kn$ 的对称点即为 $(2kn \pm\ x,y)$。整理一下得坐标 $(kn \pm\ x,km \pm\ y)$。即得到一个不定方程，然后用 exgcd 求解即可。（分 $x,y$ 的四种情况取最小值即可）。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=0x3f3f3f3f3f;
int n,m,k;
int read(){
	char ch=0;
	int x=0,w=1;
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*w;
}
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int ans=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ans;
}
int level=0;
int search(int x_1,int y_1) {
	int a=2*n,b=-2*m;//构造函数解析式 
	int c=y_1-x_1;
	int x_2=0,y_2=0;
	int d=exgcd(a,b,x_2,y_2);
	if(c%d){
		return maxn;	
	}
	a/=d;
	b/=d;
	c/=d;
	b=abs(b);
	x_2=(x_2*c%b+b)%b;
	int ans=2ll*n*x_2+x_1;
	if(ans<=0 or ans>=level){
		return maxn;
	}
	return ans;
}
signed main(){
	n=read();
	m=read();
	k=read();
	level=1LL*n*m/__gcd(n,m);
	for(int i=1;i<=k;i++){
		int x,y;
		x=read();
		y=read();
		int sum=maxn;
		sum=min(sum,search(x,y));
//		cout<<"level  "<<mx<<'\n';
		sum=min(sum,search(x,y-2*y));
		sum=min(sum,search(x-2*x,y));
		sum=min(sum,search(x-2*x,y-2*y));
		if(sum==maxn){
			cout<<-1<<'\n';
		}
		else{
			cout<<sum<<'\n';
		}
	}
	
	return 0;
}
```

谢谢观看。

---

