# Pair Of Lines

## 题目描述

在平面直角坐标系上给出 $n$ 个点，求是否存在两条直线穿过所有点。

## 样例 #1

### 输入

```
5
0 0
0 1
1 1
1 -1
2 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
0 0
1 0
2 1
1 1
2 3
```

### 输出

```
NO
```

# 题解

## 作者：daklqw (赞：7)

判断是否存在两条直线，使得所有点在这两条直线中至少一条上面(两条直线刻意重合)  
假设存在这两条直线，可以发现，**对于任意三个点，其中必有两个在同一条直线上**
所以我们随意取三个点，然后在其中枚举这两个点，把不在这过两个点的直线上的所有点提取出来，判断它们是否共线  

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN 100010
#define LL long long
int n,xs[MAXN],ys[MAXN];

bool ina[MAXN];
inline LL cha(LL x1,LL y1,LL x2,LL y2){
	return x1*y2-x2*y1;
}
bool pd(int a,int b,int c){
	return cha(xs[b]-xs[a],ys[b]-ys[a],xs[c]-xs[b],ys[c]-ys[b])==0;
}
bool judge(int a,int b){
	for(int i=1;i<=n;++i)ina[i]=pd(a,b,i);
	int t1,t2;t1=t2=0;
	for(int i=1;i<=n;++i)
		if(!ina[i]){
			if(!t1)t1=i;
			else if(!t2)t2=i;
			else if(!pd(t1,t2,i))return false;
		}
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&xs[i],&ys[i]);
	if(n<=3)puts("YES");
	else puts(judge(1,2)||judge(2,3)||judge(1,3)?"YES":"NO");
	return 0;
}
```

---

## 作者：离散小波变换° (赞：4)

随机化萌萌题。

## 题解

注意到题目本质上是把点集划分成了两个集合 $A,B$，两个集合分别可用一条直线贯穿。由于两点确定一条直线，所以只要知道 $A$ 或 $B$ 里的任意两个点就能确定对应的直线长啥样。

注意到 $\max \{|A|,|B|\}\ge \dfrac{n}{2}$。我们从全集 $U$ 里随便取两个点 $x,y$，那么这两个点在同一个集合里的概率不小于 $\dfrac{1}{4}$。

当我们知道两个点 $x,y$ 后，就可以确定 $x,y$ 所在那个集合对应的直线 $L$。那么就可以将剩下来所有点进行划分。对于点 $i$，如果 $i$ 在 $L$ 上就贪心地不管，否则说明它在另外一个集合上。当确定了两个不在 $L$ 上的点时，就能确定另外一个集合对应的直线 $L'$ 了。如果找到一个既不在 $L$ 又不在 $L'$ 上的点，那么说明要么 $x,y$ 其实不在一个集合里，要么无解。

假设有解，那么随机一对 $x,y$ 出来进行检查通过的概率不小于 $\dfrac{1}{4}$。进行 $k$ 次检查，通过的概率不小于 $1-\left(\dfrac{3}{4}\right)^k$。取 $k=50$ 时概率不小于 $99.9999\%$。

也就是说，如果检查了 $k=50$ 次后还不合法，就可以直接认为无解了。出错概率不超过 $0.00001\%$。

但是 Hack 数据不讲武德，第 $117$ 个测试点对着使用初始种子的 mt19937 卡。所以需要随机一个值，比如 $114514$，作为初始种子。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 1e5 + 3;
int X[MAXN], Y[MAXN], n;
bool check(int x, int y){
    int x0 = X[x], dx = X[x] - X[y];
    int y0 = Y[x], dy = Y[x] - Y[y];
    int p = 0, q = 0;
    up(1, n, i){
        if(1ll * (X[i] - x0) * dy == 1ll * (Y[i] - y0) * dx) continue; else {
            if(p == 0) p = i; else 
            if(q == 0) q = i; else {
                i64 u = 1ll * (X[i] - X[p]) * (Y[p] - Y[q]);
                i64 v = 1ll * (Y[i] - Y[p]) * (X[p] - X[q]);
                if(u != v) return false;
            }
        }
    }
    return true;
}
int m = 50;
mt19937 MT(114514);
int main(){
    n = qread();
    if(n == 1) puts("YES"), exit(0);
    up(1, n, i) X[i] = qread(), Y[i] = qread();
    uniform_int_distribution <int> U(1, n);
    up(1, m, i){
        int a = U(MT);
        int b = U(MT);
        if(a == b) continue;
        if(check(a, b)){
            puts("YES"); return 0;
        }
    }
    puts("NO");
    return 0;
}
```

---

## 作者：_edge_ (赞：2)

首先，我们先来思考，如果只有一条直线怎么做？

非常简单的用点初中数学判断斜率即可。

即三点共线只需要满足 $\dfrac{y1-y0}{x1-x0}=\dfrac{y2-y1}{x2-x1}$。

然后我们再继续思考，如果可以确定一条直线，那么可以把这条直线上的点都拿掉，这样转化为上面的。

那么如何去拿掉一条直线呢？暴力枚举？恐怕不行吧。

事实上这时候我们就需要用点小技巧了，我们随意取三个点，他们当中有两个点一定在同一条直线上，如果满足的话。

我们可以反向来推导这个结论，如果有两条直线的话，那么根据抽屉原理，有两个点一定在同一条直线上。

于是我们取出前面的三个点，然后暴力枚举两个点，判断直线即可。

注意这里可能会被卡精度，所以我们要把上面的斜率式子改为乘法的。

时间复杂度 $O(n)$。

```cpp
/*
kx0+b=y0
kx1+b=y1

k(x1-x0)=y1-y0
k=(y1-y0)/(x1-x0)
k=
(y2-y1)/(x2-x1)=(y1-y0)/(x1-x0)
(y2-y1)*(x1-x0)=(y1-y0)*(x2-x1)
*/
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int INF=1e5+5;
int xx[INF],yy[INF],vis[INF],n;
namespace S{
	int xx[INF],yy[INF];
	bool check() {
		int tot=0;
		for (int i=1;i<=n;i++)
			if (!::vis[i]) xx[++tot]=::xx[i],yy[tot]=::yy[i];
		if (tot<3) return 1;
		for (int i=3;i<=tot;i++)
			if ((yy[i]-yy[1])*(xx[1]-xx[2])==(yy[1]-yy[2])*(xx[i]-xx[1])) ;
			else return 0;
		return 1;
	}
}
signed main()
{
	cin>>n;
	if (n<5) {cout<<"YES\n";return 0;}
	for (int i=1;i<=n;i++) cin>>xx[i]>>yy[i];
	for (int i=1;i<=3;i++)
		for (int j=1;j<=3;j++) {
			if (i==j) continue;
			for (int k=1;k<=n;k++) vis[k]=0;
			for (int k=1;k<=n;k++) 
				if ((yy[k]-yy[i])*(xx[i]-xx[j])==(yy[i]-yy[j])*(xx[k]-xx[i])) vis[k]=1;
			if (S::check()) {cout<<"YES\n";return 0;}
		}
	cout<<"NO\n";
	return 0;
}
```


---

