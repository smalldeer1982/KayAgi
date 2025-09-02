# [COTS 2022] 点组 Točkice

## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D2T3。$\texttt{1s,0.5G}$。

## 题目描述

平面上有 $N$ 个点 $(x_i,y_i)$，无三点共线，两个人轮流操作，每次选择两个点连一条线段，要求不与之前的线段在非顶点处相交，无法操作者输，问先手必胜还是后手必胜。

## 说明/提示

对于 $100\%$ 的数据，保证：

- $1\le N\le 10^5$；
- $1\le x_i,y_i\le 10^6$；
- 任意三点不共线。

| 子任务编号 | 分值 | $N\le$ |
|:-----:|:------:|:-------:|
| $1$  | $13$  | $7$  |
| $2$  | $17$  | $300$  |
| $3$  | $21$  | $1\, 000$ |
| $4$  | $49$  | $10^5$ |

## 样例 #1

### 输入

```
4
0 0
0 10
10 0
10 10```

### 输出

```
Alenka```

## 样例 #2

### 输入

```
5
2 1
1 3
6 4
3 5
5 2```

### 输出

```
Alenka```

## 样例 #3

### 输入

```
4
4 2
2 4
2 2
1 1```

### 输出

```
Bara```

# 题解

## 作者：Mine_King (赞：3)

## Problem

[[COTS/CETS 2022] 点组 Točkice](https://www.luogu.com.cn/problem/P10876)

**题目大意：**

平面上有 $n$ 个点，无三点共线，两个人轮流操作，每次选择两个点连一条线段，要求不与之前的线段在非顶点处相交，无法操作者输，问先手必胜还是后手必胜。

## Solution

猜结论题。

首先对于凸包上的边显然不会被其他线段影响，所以可以先把这些边连起来。

然后如果你比较会手玩且比较会猜，那么你可以得到结论：无论如何操作，最终连上的边数都相同。

考虑证明这个东西。以下用 $n$ 表示凸包点数，$m$ 表示凸包内的点数。首先对于凸包，显然最终连起来的是三角剖分，边数永远都是 $n + n - 3 = 2n - 3$。

然后考虑凸包内有恰好一个点的情况，显然他会与凸包上若干个点连边，然后将凸包划分成若干个小凸包，小凸包内部是三角剖分。

![](https://cdn.luogu.com.cn/upload/image_hosting/8sjxgt4r.png)

不妨设连了 $k$ 个点，切出来的每个小凸包的大小分别是 $a_1 + 1, a_2 + 1, \ldots, a_k + 1$，则有 $\sum_{i = 1}^k a_i = n$。

此时边数为：

$$
k + \sum\limits_{i = 1}^k (a_i + 1 + a_i + 1 - 3) = 2n
$$

因此最终边数相同。

对于有更多点的情况，对于任何一种最终状态，任意找一个凸包内的点，找到与之相连的点形成的凸包，把这个凸包的方案改成任意一种三角剖分然后删去这个点，边数 $-3$，一直删点直到只剩凸包为止。因此边数就是 $2n - 3 + 3m$。

所以我们只要求出凸包然后求出 $m$ 即可得到答案。

## Code

```cpp
// 長い夜の終わりを信じながら
// Think twice, code once.
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

int n;
struct Point {
	int x, y;

	Point() = default;
	Point(int _x, int _y): x(_x), y(_y) {}
	Point operator-(const Point &b) const {return Point(x - b.x, y - b.y);}
	long long operator^(const Point &b) const {return (long long)x * b.y - (long long)y * b.x;}
} a[100005];
vector<Point> stk;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1, [](const Point &x, const Point &y) {return x.x != y.x ? x.x < y.x : x.y < y.y;});
	stk.push_back(a[1]);
	for (int i = 2; i <= n; i++) {
		while (stk.size() > 1) {
			Point tmp = stk.back();
			stk.pop_back();
			if (((tmp - stk.back()) ^ (a[i] - tmp)) > 0) {stk.push_back(tmp); break;}
		}
		stk.push_back(a[i]);
	}
	for (int i = n - 1, top = stk.size(); i >= 1; i--) {
		while ((int)stk.size() > top) {
			Point tmp = stk.back();
			stk.pop_back();
			if (((tmp - stk.back()) ^ (a[i] - tmp)) > 0) {stk.push_back(tmp); break;}
		}
		stk.push_back(a[i]);
	}
	stk.pop_back();
	puts((n - stk.size()) % 2 ? "Bara" : "Alenka");
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

特判 $n\le 2$。

如果点都在凸包上，则最终状态恰好会连 $n+(n-3)$ 条线段（凸包加上三角剖分），那么可以通过奇偶性得出谁赢。

否则，再遍历凸包内部的每个点，都向其所在的三角形连三条边。

设凸包上的点数为 $m$，则最终有 $m+(m-3)+3(n-m)$ 条线段，奇数 A 赢，偶数 B 赢。

P.S. 最终状态如果不是三角剖分，则找到一个非三角形一定还能操作。对于本题，由于欧拉公式，任意三角剖分的线段数是相同的。

---

## 作者：qiyichen12 (赞：0)

# 前言
水题...
# 分析
凸包上，会连 $2n-3$ 条线段,凸包内会连 $3n-3-3m$ 个线段奇数先手赢，偶数后手赢。
# ~~完结撒花~~
这当然不是重点，为了那些不会凸包的 OIer 们，我要讲一下凸包。
## Andrew 算法求凸包
首先将所有点排序，横坐标为第一关键字，纵坐标为第二关键字升序排序。
```cpp
bool cmp(Dote a,Dote b)
{
	if (a.x == b.x) return a.y < b.y;
	else return a.x < b.x; 
}
```
可以想见，最大和最小一定在凸包上。

逆时针以最大到最小为**上凸壳**，最小到最大为**下凸壳**。对于可以**下凸壳**建立 $hl$ 为栈，先压入两个初始点既 $Dotes_1$，$Dotes_2$（$Dotes$ 以下简称 $Ds$）判段新点是不是**左拐**，如果是则加入，不是则将前一个点出栈再加入。而遍历完**下凸壳**则反向遍历**上凸壳**使凸包闭合。

```cpp
	int tp = 0;                       
	sort(Ds+1,Ds+n+1,cmp);  
	hl[++tp] = 1;
	for (int i = 2;i <= n;i++) 
	{
		while (tp >= 2&&(Ds[hl[tp]] - Ds[hl[tp - 1]]) * (Ds[i] - Ds[hl[tp]]) <= 0) used[hl[tp--]] = 0;
	  	used[i] = 1;
	  	hl[++tp] = i;
	}
	int tmp = tp;  
	for (int i = n - 1;i > 0;i--)
    {
		if (!used[i]) 
		{
			while (tp > tmp&&(Ds[hl[tp]] - Ds[hl[tp - 1]]) * (Ds[i] - Ds[hl[tp]]) <= 0) used[hl[tp--]] = 0;
		    used[i] = 1;
		    hl[++tp] = i;
		}
    }
	for (int i = 1; i <= tp; ++i) Ns[i] = Ds[hl[i]];
	n = tp;
```

---

## 作者：xiaoliebao1115 (赞：0)

水蓝。
## solution
首先要读对题目，题目当中线段可以在顶点相交，指的不是线段在顶点相交也算相交，而是指线段可以共用同一个顶点，就是顶点相交不算相交。

看到线段相交问题很容易套路性的转化成凸包。

假设凸包上共有 $x$ 个点，凸包内部共有 $y$ 个点。

先考虑凸包上，首先凸包本身有 $x$ 条边，加上中间给他划分三角形的 $x-3$ 条边，总共是 $x\times 2-3$ 条边，划分三角形有点类似于求解任意多边形面积的过程。

因为题目保证了其中任意三点不共线，所以每次遍历内部点，这个内部点一定属于一个三角形，并且三角形内部没有其他点，所以我们向这个三角形三个顶点连边。这样的话数量就是 $x\times 2-3+3\times y$。需要注意的是连向的三个顶点不一定是凸包上的点。

那么我们就不太严谨的证明了两个人的操作次数一定是不变的，因为 Alenka 先手，所以 $x\times 2-3+3\times y$ 是奇数 Alenka 赢，偶数 Bara 赢。

由于涉及到凸包，所以特判 $n\le 2$ 的情况。

最终的情况一定是三角剖分，若不是，一定还能继续连线。根据[欧拉公式](https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E5%85%AC%E5%BC%8F/92066?fr=ge_ala)或[三角剖分](https://baike.baidu.com/item/%E4%B8%89%E8%A7%92%E5%89%96%E5%88%86/10390049?fr=ge_ala)可知一个多面体的三角剖分连边数一定相同，并且面数应该也是相同的。
## code
```cpp
const int nn=1e5+5;
int n,tp;
struct node{
    double x,y;
};
node p[nn],st[nn];
inline bool cmp(node l1,node l2){
    if(l1.x==l2.x) return l1.y<l2.y;
    return l1.x<l2.x;
}
inline double side(node a,node b,node p){
    node aa={b.x-a.x,b.y-a.y};
    node bb={p.x-a.x,p.y-a.y};
    return aa.x*bb.y-aa.y*bb.x;
}
inline double dis(node p1,node p2){
    return sqrt((p1.y-p2.y)*(p1.y-p2.y)+(p1.x-p2.x)*(p1.x-p2.x));
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    if(n==1){
        cout<<"Bara"<<endl;
        return 0;
    }
    if(n==2){
        cout<<"Alenka"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
    sort(p+1,p+n+1,cmp);
    st[0]=p[1],st[1]=p[2];
    tp=1;
    for(int i=3;i<=n;i++){
        while(tp&&side(st[tp-1],st[tp],p[i])<=0) tp--;
        st[++tp]=p[i];
    }
    st[++tp]=p[n-1];
    for(int i=n-2;i>=1;i--){
        while(tp&&side(st[tp-1],st[tp],p[i])<=0) tp--;
        st[++tp]=p[i];
    }
    int x=tp,y=n-tp;
    int s=(x<<1)-3+3*y;
    if(s%2==1) cout<<"Alenka"<<endl;
    else cout<<"Bara"<<endl;
    return 0;
}
```

---

