# Gregor and the Odd Cows (Easy)

## 题目描述

This is the easy version of the problem. The only difference from the hard version is that in this version all coordinates are even.

There are $ n $ fence-posts at distinct coordinates on a plane. It is guaranteed that no three fence posts lie on the same line.

There are an infinite number of cows on the plane, one at every point with integer coordinates.

Gregor is a member of the Illuminati, and wants to build a triangular fence, connecting $ 3 $ distinct existing fence posts. A cow strictly inside the fence is said to be enclosed. If there are an odd number of enclosed cows and the area of the fence is an integer, the fence is said to be interesting.

Find the number of interesting fences.

## 说明/提示

In the first example, there is only $ 1 $ fence. That fence is interesting since its area is $ 4 $ and there is $ 1 $ enclosed cow, marked in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548D1/0403ceae6e73450fcff5ed53159c4a8d4ef6577c.png)In the second example, there are $ 3 $ interesting fences.

- $ (0,0) $ — $ (30,14) $ — $ (2,10) $
- $ (2,16) $ — $ (30,14) $ — $ (2,10) $
- $ (30,14) $ — $ (4,6) $ — $ (2,10) $

## 样例 #1

### 输入

```
3
0 0
2 0
0 4```

### 输出

```
1```

## 样例 #2

### 输入

```
5
0 0
2 16
30 14
4 6
2 10```

### 输出

```
3```

# 题解

## 作者：Acc_Robin (赞：6)

D1 这么简单，怎么都 `*2300` ……

首先我们都知道 Pick 定理，对任意简单整点多边形都有

$$
S=A+\frac{B}{2}-1
$$

其中 $A$ 表示内部整点数，$B$ 表示边上整点数， $S$ 表示面积。

D1 中限制了所有点的坐标都是偶数，那么易得 $S$ 一定是偶数。

题目要求 $A$ 是奇数，由此可得 $\frac B2$ 必然是偶数，那么得到 $B \equiv 0 \pmod 4$。

又因为点 $(x_1,y_1)$ 与 点 $(x_2,y_2)$ 之间（含一个端点）的整点数是 $\gcd(|x_1-x_2|,|y_1-y_2|)$，我们就只需要保证选出的三角形三个点的坐标满足

$$
\gcd(x_1-x_2,y_1-y_2)+\gcd(x_1-x_3,y_1-y_3)+\gcd(x_2-x_3,y_2-y_3)\equiv 0\pmod 4
$$

我们发现，可以把点 $(x,y)$ 化作点 $(x\bmod 4,y\bmod 4)$，直接开个桶统计一下即可。

注意统计方式，要不重不漏。

总复杂度 $O(n+(4^2)^3)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	int cnt[4][4],p[4][4],n,i,j,x1,y1,x,y;
	long long r,z;
	//S=A+B/2-1
	//A odd
	//S even
	//B/2 even
	//4|B
	//gcd(x,y)=2 gcd(x/2,y/2) 
	int gcd(int x,int y){return __gcd(abs(x),abs(y));}
	void work(){
		for(cin>>n,i=0;i<n;++i)cin>>x>>y,++cnt[x%4][y%4];
		for(i=0;i<4;++i)for(j=0;j<4;++j)
			for(x1=0;x1<4;++x1)for(y1=0;y1<4;++y1)
				for(x=0;x<4;++x)for(y=0;y<4;++y)
					if((n=gcd(i-x,j-y)+gcd(x1-x,y1-y)+gcd(i-x1,j-y1))%4==0){
						memcpy(p,cnt,sizeof p),z=1;
						z*=p[i][j],--p[i][j],z*=p[x1][y1],--p[x1][y1],z*=p[x][y],--p[x][y];
                        //如果出现不足的情况，z就会乘0而变成0
						r+=z;
					}
		cout<<r/6<<'\n';//一个三角形被统计了 6 次
	}
}
int main(){return Acc::work(),0;}
```

---

## 作者：gyh20 (赞：5)

Pick 定理：

在一个平面直角坐标系内，如果一个多边形的顶点全都在格点上，那么这个图形的面积恰好就等于边界上经过的格点数的一半加上内部所含格点数再减一。

即 $A=i+\dfrac{b}{2}-1$，其中 $A$ 为面积，$i$ 为内点数，$b$ 为边点数。

我们要求的很明显是内部格点数为奇数。

在 Easy Version 中，我们知道，三个坐标都为偶数，写成向量叉积的形式可以明显发现叉积是 $4$ 的倍数，也就是说面积是偶数，那只用管边点数。

可以发现一条断点为 $(0,0)$ 和 $(x,y)$ 的线段交出的整点个数为 $\gcd(x,y)$ 个，此时我们只用管这个 $\gcd \mod 4$ 意义下的值，因为只用管 $/ 2$ 后的奇偶性。

由于不存在三点共线，可以将所有点坐标 $/2$ 后按 $\mod 2$ 分类，然后直接枚举三角形三个点所属的类别，根据写法可能需要带系数，可以看做一个简单的 Burnside。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
struct edge{int to,next;}e[2000002];
int n,a[6002],b[6002],c[6002],d[6002],f[4][4],ans,g[4][4];
inline int C3(re int x){return x*(x-1)*(x-2)/6;};
inline int C2(re int x){return x*(x-1)/2;}
inline int calc(re int A,re int B,re int C,re int D){
	C^=A,D^=B;
	if(C==0&&D==0)return 0;
	return 1;
}
signed main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read()>>1,b[i]=read()>>1,a[i]&=1,b[i]&=1,++f[a[i]][b[i]];
	for(re int A=0;A<=1;++A)
		for(re int B=0;B<=1;++B)
			for(re int C=0;C<=1;++C)
				for(re int D=0;D<=1;++D)
					for(re int E=0;E<=1;++E)
						for(re int F=0;F<=1;++F){
							memset(g,0,sizeof(g));
							re int ss=1;
							re int s=calc(A,B,C,D)+calc(A,B,E,F)+calc(C,D,E,F);
							if(s%2==0){
								++g[A][B],++g[C][D],++g[E][F];
								for(re int i=0;i<=1;++i)for(re int j=0;j<=1;++j)
								if(g[i][j]==1)ss*=f[i][j];
								else if(g[i][j]==2)ss*=C2(f[i][j]),ss*=2;
								else if(g[i][j]==3)ss*=C3(f[i][j]),ss*=6;
								ans+=ss; 
							}
						}
	assert(ans%6==0);
	printf("%lld",ans/6);
}
```


---

