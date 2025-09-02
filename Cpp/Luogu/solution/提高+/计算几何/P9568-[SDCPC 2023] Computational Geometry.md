# [SDCPC 2023] Computational Geometry

## 题目描述

给定一个有 $n$ 个顶点的凸多边形 $P$，您需要选择 $P$ 的三个顶点，按逆时针顺序记为 $a$，$b$ 和 $c$。要求在 $b$ 沿逆时针方向到 $c$ 之间恰有 $k$ 条边（也就是说，$a$ 不是这 $k$ 条边的端点）。

考虑用线段 $ab$ 和 $ac$ 将 $P$ 割开。将由线段 $ab$，$ac$，以及 $b$ 和 $c$ 之间的 $k$ 条边围成的 $(k + 2)$ 边形记作 $Q$。

求 $Q$ 可能的最大面积。

注意，$ab$ 和 $ac$ 可以与 $P$ 的边重合。

## 样例 #1

### 输入

```
3
3 1
0 0
1 0
0 1
8 3
1 2
3 1
5 1
7 3
8 6
5 8
3 7
1 5
7 2
3 6
1 1
3 1
7 1
8 1
5 6
4 6
```

### 输出

```
0.500000000000
26.500000000000
20.000000000000
```

# 题解

## 作者：scp020 (赞：5)

# P9568 [SDCPC2023] Computational Geometry 题解

感谢战学长的帮助。

## 解法

本题的关键是将多边形 $Q$ 分割为两部分，一部分是由点 $a,b,c$ 组成的三角形，另一部分是由从 $b$ 到 $c$ 这 $k + 1$ 个点组成的凸多边形。注意到这种由 $k + 1$ 个点组成的凸多边形的数量是有限的，为 $n$ 个，而由点 $a,b,c$ 组成的三角形的数量更多，所以我们考虑固定 $k + 1$ 个点的多边形，即固定点 $b,c$，然后查找可以使三角形 $a,b,c$ 面积最大的点 $a$，即点 $a$ 到直线 $bc$ 的垂直距离最大。

考虑所有可被选择为点 $a$ 的点，它们和直线 $bc$ 的距离是一个单峰函数，故可以考虑使用三分法求得函数峰值。

现在我们想到了一个做法：用 $\mathcal{O}(n + k)$ 的时间复杂度预处理所有 $k + 1$ 个点的多边形的面积，用 $\mathcal{O}(n \log n)$ 的时间复杂度求得点 $a$。

预处理多边形面积的方法：先选定一个多边形，将其暴力地拆成 $k-1$ 个三角形，对每个三角形叉积求面积，值得注意的是叉积的模长是平四的有向面积，所以这里求面积时应对叉积的模长取绝对值。这里有个小 trick，就是在计算过程中我们不将面积除以 $2$，而是在最后输出时除以 $2$，防止计算过程中有浮点数的出现。

然后考虑递推转移，如图，目标状态的面积为原有状态的面积加上红色三角形面积减去绿色三角形面积。

![图](https://cdn.luogu.com.cn/upload/image_hosting/p01pssuh.png)

这时战学长给我发了个 hint，说有严格线性做法。仔细考虑当线段 $bc$ 逆时针变化时，$a$ 点也是逆时针变化的。所以 $a$ 点的移动是有单调性的，移动次数不超过 $n$ 次，因此可以每次旋转线段 $bc$ 时暴力地移动点 $a$。

时间复杂度 $\mathcal{O}(n + k)$。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	/**
	 * 顾名思义，是快读快写。
	*/
};
using namespace fast_IO;
#define int long long
// considering the issue of accuracy,we can twice the storage surface
int t,n,k,surf[100010],pt,b,c,pres,nxts,ans;
struct point
{
	int x,y;
	inline point(int x=0,int y=0)
	{
		this->x=x,this->y=y;
	}
	inline point operator-(const point &rhs) const
	{
		return point(x-rhs.x,y-rhs.y);
	}
	inline int operator*(const point &rhs)
	{
		return x*rhs.y-y*rhs.x;
	}
};
point a[100010];
inline int calc(const point x,const point y,const point z) // calculate the surface of the triangle we chose
{
	return abs((y-x)*(z-x));
}
signed main()
{
	in>>t;
	while(t--)
	{
		in>>n>>k,ans=0;
		for(int i=1;i<=n;i++) in>>a[i].x>>a[i].y,surf[i]=0;
		b=1,c=k+1,pt=c,pres=0;
		for(int i=2;i<=k;i++) surf[b]+=calc(a[i-1],a[i],a[c]);
		for(int i=2;i<=n;i++)
			surf[i]=
			surf[i-1]+
			calc(a[i+k-1>n?i+k-1-n:i+k-1],a[i+k>n?i+k-n:i+k],a[i])-
			calc(a[i-1],a[i+k-1>n?i+k-1-n:i+k-1],a[i]);
		for(;b<=n;b++,c=b+k>n?b+k-n:b+k)
		{
			pres=calc(a[b],a[c],a[pt]);
			while(pt!=b)
			{
				nxts=calc(a[b],a[c],a[pt+1>n?pt+1-n:pt+1]);
				if(nxts>pres) pres=nxts,pt=pt+1>n?pt+1-n:pt+1;
				else break;
			}
			ans=std::max(ans,surf[b]+pres);
			if(pt==c) pt=pt+1>n?pt+1-n:pt+1;
		}
		out<<ans/2.0<<'\n';
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```


---

## 作者：Diaоsi (赞：3)

[Computational Geometry](https://www.luogu.com.cn/problem/P9568)

枚举 $b$ 的位置，$b$ 确定之后 $c$ 也就随之确定了，接下来就是在剩下半个凸包上找一个点使得 $S_{\triangle abc}$ 最大。

$b$ 移动时 $a$ 的移动一定是单调的，所以可以再用一个指针维护 $a$ 的移动，每次暴力前移直到三角形面积不再增大为止。其实这个过程就是旋转卡壳。

在这个过程中用叉乘维护凸包的面积，取最大即可。

Code:

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
const ld eps=1e-9,inf=1e17;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,k;
ld ans,S;
struct node{
	ll x,y;
	node(ll xx=0,ll yy=0){x=xx,y=yy;}
	void in(){scanf("%lld%lld",&x,&y);}
	void out(){printf("%lld %lld\n",x,y);}
}p[N];

bool operator <(node a,node b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
node operator +(node a,node b){return node(a.x+b.x,a.y+b.y);}
node operator -(node a,node b){return node(a.x-b.x,a.y-b.y);}
ll operator *(node a,node b){return a.x*b.x+a.y*b.y;}
ll operator ^(node a,node b){return a.x*b.y-a.y*b.x;}

ll sqr(node x,node y,node c){return abs((y-x)^(c-x));}

void solve(){
	scanf("%d%d",&n,&k);
	ans=S=0;k++;
	for(int i=1;i<=n;i++)
		p[i].in(),p[i+n]=p[i];
	for(int i=1;i<k;i++)
		S+=p[i]^p[i+1];
	p[2*n+1]=p[1];
	for(int l=1,r=k,i=k+1;r<=2*n;l++,r++){
		while(i<=2*n&&sqr(p[l],p[r],p[i])<=sqr(p[l],p[r],p[i+1]))i++;
		ans=std::max(ans,S+(p[r]^p[i])+(p[i]^p[l]));
		S+=p[l+1]^p[l];S+=p[r]^p[r+1];
	}
	printf("%.10Lf\n",ans/2);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：寄风 (赞：1)

可以发现多边形 $Q$ 其实是由一个三角形 $abc$ 和 $b$、$c$ 以及它们之间的 $k$ 条边构成的。

然后如果我们枚举 $b$ 的位置的话，那么 $c$ 就能被我们确定，所以我们现在只要考虑三角形 $abc$ 的面积。然后发现此时 $b$ 和 $c$ 都是定点，所以我们现在只要考虑 $a$，然后其实 $a$ 可以三分，~~但是我写挂了~~，于是我用的是一种类似于旋转卡壳的方法求的 $a$。

然后不管你是什么方式，搞出 $a$ 了，这题就结束了。

具体实现见代码。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int  x[1000005] , y[10000005] , ans , sum , n , k;
int _get(int a, int b) {
    return x[a + 1] * y[b + 1] - x[b + 1] * y[a + 1];
}
signed main() {
    int t;
    cin >> t;
    while(t--){
        cin >> n >> k;
        for(int i = 1;i <= n;i++){
            cin >> x[i] >> y[i];
        }
        ans = 0 , sum = 0;
        for (int i = 1; i <= k; i++) sum += _get(i - 1 , i);
        int a = k;
        for (int b = 0;b < n;b++) {
            int c = (b + k) % n;
            while(a != b){
                int now = _get(c , a) + _get(a , b) , tmp = _get(c , (a + 1) % n) + _get((a + 1) % n , b);
                if(tmp > now){
                    a = (a + 1) % n;
                }
                else{
                    break;
                }
            }
            ans = max(ans , sum + _get(c , a) + _get(a , b));
            sum += _get(c , (c + 1) % n) - _get(b , (b + 1) % n);
            if(a == c){
                a = (a + 1) % n;
            }
        }
        printf("%.1f\n", ans / 2.0);
    }
    return 0;
}
```


---

