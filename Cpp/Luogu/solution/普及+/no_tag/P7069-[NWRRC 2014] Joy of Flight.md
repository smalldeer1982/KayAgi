# [NWRRC 2014] Joy of Flight

## 题目描述

## 简述

大意就是一架飞机要从起点飞到终点，飞机有最大空速，飞行最大时间，给出风速的变化和风如何影响飞机飞行，求出飞机是否能到达终点，如果能就输出飞机的位置变化。


雅各布（Jacob）喜欢玩他的无线电摇制飞机。今天的风很大，雅各布必须小心地计划飞行。他有一个天气预报——飞行计划中每秒钟的风速和风向。

飞机每秒在任何方向的空速最大都可以达到 $v_{max}$ 。风吹动飞机的方式如下：如果飞机的空速是 $(v_x,v_y)$ 并且风速是 $(w_x,w_y)$ ，那么飞机每秒将移动 $(v_x+w_x,v_y+w_y)$ 。

![P7069-1](https://cdn.luogu.com.cn/upload/image_hosting/2uyb1zpd.png)

雅各布（Jacob）有一种刚好能使用$k$秒的燃料，他想知道，飞机是否能在这段时间内从起点飞到终点。如果可能的话，他需要知道飞行计划：每飞行一秒后飞机的位置。

## 说明/提示

时间限制： $2s$ ；内存限制： $256MB$ 

by XYY1411

2020/12/08

## 样例 #1

### 输入

```
1 1 7 4
2 3 10
0 1 2
2 2 0```

### 输出

```
Yes
3 2.5
5 2.5
7 4```

# 题解

## 作者：封禁用户 (赞：3)

>本题是 NWRRC 2014 Problem J。
>
>本题在 CodeForces 上有提交通道：[Gym 100531J](https://codeforces.com/gym/100531)。

~~为什么就连[联合省选](https://www.luogu.com.cn/problem/P10217)都开始搬[原题](https://www.luogu.com.cn/problem/P7069)了啊，这么没素质的吗！~~

很明显，飞机的位移分为两部分：风带来的位移和飞机自身的位移。因此，我们可以先让飞机在无空速的情况下随风移动 $k$ 秒，排除风速的影响。

移动结束后，剩下来的路程就要靠飞机的空速来弥补了。很明显，飞机在 $k$ 秒内最多可以靠空速移动 $k \cdot v_{\max}$ 的距离，因此只需要计算一下剩下来的路程长度，并和 $k \cdot v_{\max}$ 进行比较就可以了。

至于构造……很明显，设剩下来的路程是 $\bm {X}=(a,b)$，那么将每秒的空速都设成 $\dfrac{\bm X}{k}=(\dfrac{a}{k},\dfrac{b}{k})$ 就可以了。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10012],b[10012],c[10012];
int main()
{
    int sx,sy,fx,fy;
    cin>>sx>>sy>>fx>>fy;
    int tx=sx,ty=sy;
    int n,k,v;
    cin>>n>>k>>v;
    for(int i=1;i<=n;i++)
        cin>>a[i]>>b[i]>>c[i];
    a[n+1]=k;
    int p=0;
    for(int i=0;i<=k-1;i++)
    {
        if(a[p+1]==i) p++;
        tx+=b[p],ty+=c[p];
    }
    long double dis=sqrtl(1ll*(fx-tx)*(fx-tx)+1ll*(fy-ty)*(fy-ty));
    if(dis>k*v)
    {
        puts("No");
        return 0;
    }
    puts("Yes");
    long double mx=(fx-tx)/1.0/k,my=(fy-ty)/1.0/k;
    long double ssx=sx,ssy=sy;
    p=0;
    for(int i=0;i<=k-1;i++)
    {
        if(a[p+1]==i) p++;
        ssx+=b[p],ssy+=c[p];
        ssx+=mx,ssy+=my;
        cout<<fixed<<setprecision(50)<<ssx<<' '<<ssy<<endl;
    }
    return 0;
}
```

---

## 作者：Union_Find (赞：0)

~~注意到，这道题比较简单，但是我调了10 min。~~

题目是要让我们在每一秒内移动，使得飞机最终可以到达。

一开始我想的是贪心，在每次操作的时候选择超目标方向移动最远距离。但是很快就想到 hack 了。因为我们有可能你往上走了之后，有一阵风使得你向上走了很远，使得你更远了。所以正解应该是要整体考虑。

注意到，向量的加法具有结合律和交换律。所以我们可以先让飞机走完所有的风，然后再考虑自己飞。假设所有风吹完之后位置是 $(x,y)$，终点是 $(tx,ty)$，那么飞机要在 $k$ 秒内只靠自己飞飞到终点。有解当且仅当 $\sqrt{(tx-x)^2+(ty-y)^2} \le v \times k$。

那如何输出方案呢？很简单，我们可以直接每次自己飞的向量设为 $(\frac{tx-x}{k}, \frac{ty-y}{k})$。这样最后就可以飞到终点了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 1000005
#define f(x) ((x) * (x))
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const long double eps = 1e-12;
ll sx, sy, tx, ty, n, k, v, t[N], wx[N], wy[N], x, y;
int main(){
	sx = rd(), sy = rd(), tx = rd(), ty = rd(), n = rd(), k = rd(), v = rd();
	for (int i = 1; i <= n; i++) t[i] = rd(), wx[i] = rd(), wy[i] = rd();
	t[n + 1] = k;
	x = sx, y = sy;
	for (int i = 0, j = 1; i < k; i++){
		if (t[j + 1] == i) j++;
		x += wx[j], y += wy[j];
	}
	long double dis = sqrt(f(tx - x) + f(ty - y));
	long double ux = sx, uy = sy, px = 1.0 * (tx - x) / k, py = 1.0 * (ty - y) / k;
	if (dis > v * k) return 0 & puts("No");
	else puts("Yes");
	for (int i = 0, j = 1; i < k; i++){
		if (t[j + 1] == i) j++;
		ux += px + wx[j], uy += py + wy[j], printf ("%.50Lf %.50Lf\n", ux, uy);
	}
	return 0;
}

```

---

