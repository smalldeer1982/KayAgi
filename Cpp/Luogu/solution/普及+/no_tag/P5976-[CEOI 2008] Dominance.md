# [CEOI 2008] Dominance

## 题目描述

给出一个宽为 $W$，高为 $H$ 的矩形 。
 
在它上面有两种点， $black$ 及 $white$。 每个点都有自己的辐射范围。对于其它的点如果它受到白点的辐射多于黑色的，则为白点，反之亦然，如果相同的话则中立。

现给出白点及黑色的坐标及各自的辐射范围，问最后白色点一共有多少个，黑色点共有多少个 。

## 说明/提示

对于 $100\%$ 的数据，$1 \le  W,H \le 10^9$，$0 \le  N \le  3\times 10^3$。


-----

### 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/hfu3bgfx.png)

## 样例 #1

### 输入

```
10 10
3
W 3 6 3
B 6 4 2
W 3 3 2```

### 输出

```
30 9```

# 题解

## 作者：Azazеl (赞：1)

## 「CEOI2008」Dominance 题解

$~~~~$ [或许好一点的阅读体验](https://www.cnblogs.com/Azazel/p/14791920.html)

### 废话

$~~~~$ 成功抢到一血，发篇题解纪念一下（顺便吐槽一下国内居然都没有这题题解，就只有[CEOI官方](https://www.ceoi2008.de/files/short-spoiler.pdf)有英文）  

$~~~~$ ~~所以这篇题解基本以搬运为主~~

$~~~~$ Update:2021/7/15 给代码增加了注释，并对文字稍作润色

### 题意

> $~~~~$ 给出一个矩形。在它上面有两种点共 $n$ 个，分别为黑和白。每个点都有自己的辐射范围。对于某个格子如果它受到白点的辐射多于黑色的，则为白格，反之亦然，如果相同的话则中立.现给出白点和黑点的坐标及各自的辐射范围（用曼哈顿距离表示），问最后白色格子一共有多少个，黑色格子共有多少个。
>
> $~~~~$ 坐标系最远的坐标为 $10^9$，$1\leq n\leq 300$。

### 题解

$~~~~$ 一开始看到这道题以为很简单，但考虑到坐标系大小直接放弃。

$~~~~$ 但有一部分思路是可以沿用的。首先，由于**曼哈顿距离**的影响范围是斜放的正方形，显然很难用数据结构维护斜着的坐标系，因此我们把它转为**切比雪夫距离**。这部分的具体见 [**洛谷日报#182 常用距离算法详解**](https://www.luogu.org/blog/xuxing/Distance-Algorithm) 。这里仅提一下结论：

$~~~~$ 将坐标 $(x,y)$ 变为 $(x+y,x-y)$ （或 $(x-y,x+y)$ 亦可，本文选用前者 ），则原先点之间的曼哈顿距离与变换后点之间的切比雪夫距离是相等的。

$~~~~$ 这样做就可以把正方形的四边变为平行于坐标轴的线段，方便之后的维护。但要注意，变换后坐标系内的某些整点不一定有原先的整点与之对应。更具体来看，我们可以把 **还原** 这个过程视作解二元一次方程，则变换后坐标 $(x,y)$ 是由 $(\frac{x+y}{2},\frac{x-y}{2})$ 变换而来的，由此我们可以知道 **变换后坐标之和为偶数的点**有原先整点与之对应，进而把变换后的点分为两类：**横纵坐标均为奇数** 和 **横纵坐标均为偶数** 。

$~~~~$ 下一部分，考虑之前我们为什么觉得困难，是因为坐标系过大，因此我们必须转换视角，从每个点上入手。~~看到一堆矩形可以自然而然地想到扫描线~~。 由于在复杂度不与坐标轴大小相关的情况下必须对点进行离散化，而本题离散化后处理并不方便，因此我们选择不用离散化的扫描线。

$~~~~$ 若不考虑坐标轴内有无用点（即不能被统计进入的点）的话，这的确是一道扫描线裸题，那么考虑用上文提到的将点分为两类，分别维护横纵线上的奇线和偶线则可维护矩形内分别有多少奇点和偶点，由于 $n$ 并不大，因此用不着线段树一类的高级算法，$n^2$ 处理即可。

### 代码  

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll Coord[6005],Tag[6005];
//Coord 记录所有水平方向线的高度，Tag记录当前两条线之间黑 (-1) 或白 (1) 的数量
char Col[5];
struct Square{
	ll odd,even;
	Square(){}
	Square(ll O,ll E){odd=O,even=E;}
	#define Square_OPERATOR(op) Square operator op (const Square &t){return Square(odd op t.odd,even op t.even);}//对应相加、乘 
    Square_OPERATOR(+=);
    Square_OPERATOR(-=);
    Square_OPERATOR(*);
}W,B,AnsW,AnsB,Squ;

struct UpRight{
	ll x,l,r,Type;
	UpRight(){}
	UpRight(ll X,ll L,ll R,ll T){x=X,l=L,r=R,Type=T;}
}Up[6005];
bool cmpUp(UpRight x,UpRight y){return x.x<y.x;}

Square Get(ll l,ll r)//一维线中有多少奇、偶线
{
	Square ret=Square((r-l)>>1,(r-l)>>1);
	if((r-l)&1) (r&1)?ret.odd++:ret.even++;
	return ret;
}  
int main() {
	ll n,m,p;
	scanf("%lld %lld %lld",&n,&m,&p);
	ll U=0,C=0;
	for(ll i=1,x,y,d;i<=p;i++)
	{
		scanf("%s %lld %lld %lld",Col+1,&x,&y,&d);
		x=x+y; y=x-2*y;
		ll Type=((Col[1]=='W')?1:-1);
		Up[++U]=UpRight(x-d-1,y-d-1,y+d,Type);//依次为该竖直线所在的横坐标、纵坐标的范围和种类
		Up[++U]=UpRight(x+d,  y-d-1,y+d,-Type);
		Coord[++C]=y-d-1;
		Coord[++C]=y+d;
	}
	sort(Up+1,Up+1+U,cmpUp);
	sort(Coord+1,Coord+1+C); C=unique(Coord+1,Coord+1+C)-Coord-1;
	
	ll Last=Up[1].x;
	for(int i=1;i<=U;i++)
	{
		Squ=Get(Last,Up[i].x);//得到从上一条竖直线到这一条的奇和偶的竖直线个数
		AnsW+=Squ*W; AnsB+=Squ*B;//水平 × 竖直 线即为点的个数
		Last=Up[i].x;
		
		ll l,r,col=Up[i].Type;
		l=lower_bound(Coord+1,Coord+1+C,Up[i].l)-Coord+1;
		r=lower_bound(Coord+1,Coord+1+C,Up[i].r)-Coord;
		
		for(int j=l;j<=r;j++)
		{
			Squ=Get(Coord[j-1],Coord[j]);//得到当前枚举的竖直线内所有水平线之间的奇、偶线个数
			if(Tag[j]==0&&col==1)  W+=Squ;
			if(Tag[j]==0&&col==-1) B+=Squ;
			if(Tag[j]==1&&col==-1) W-=Squ;
			if(Tag[j]==-1&&col==1) B-=Squ;
			Tag[j]+=col;
			//根据情况维护当前枚举的竖直线到下一条之间的水平线的奇、偶个数
		}
	}
	printf("%lld %lld\n",AnsW.odd+AnsW.even,AnsB.odd+AnsB.even);
	return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

摘抄自[我的博客](https://www.luogu.com.cn/article/ur9n70t7)

曼哈顿距离转换成切比雪夫距离，那么辐射范围变成了一个矩形，我们可以轻易地用 $O(n^2)$ 的扫描线进行解答。但是因为这道题坐标是整点，而转换会出现小数，我们考虑如何避免小数。

对于转换后的的点 $(x,y)$，它在转换前是 $(\frac{x+y}{2},\frac{x-y}{2})$，我们们发现有些点虽然可能在转换后是整点，但转换前不是，只有转换后奇偶性相同的点转换前才是整点。

所以我们要单独维护转换后 $x,y$ 同为奇数或同为偶数的点的数量。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e3;
int n, m, p;
int cl;
struct line {
    int x, y1, y2, d;
} a[MAXN * 2 + 5];
int recnt, re[MAXN * 2 + 5];
struct node {
    int o, e;
};
node get(int l, int r) {
    return {(r - l + 1) / 2 + (((r - l + 1) & 1) & (r & 1)), (r - l + 1) / 2 + (((r - l + 1) & 1) & !(r & 1))};
}
int b[MAXN + 5];
node W, B, answ, ansb;
int find(int x) {
    return lower_bound(re + 1, re + 1 + recnt, x) - re;
}
signed main() {
    scanf("%lld%lld%lld", &n, &m, &p);
    for (int i = 1; i <= p; i ++) {
        char ch; cin >> ch;
        int x, y, d; scanf("%lld%lld%lld", &x, &y, &d);
        x = x + y; y = x - 2 * y;
        a[++ cl] = {x - d, y - d, y + d + 1, (ch == 'W') ? 1 : -1};
		a[++ cl] = {x + d + 1, y - d, y + d + 1, (ch == 'W') ? -1 : 1};
        re[++ recnt] = y - d;
        re[++ recnt] = y + d + 1;
    }
    sort(re + 1, re + 1 + recnt); recnt = unique(re + 1, re + 1 + recnt) - re - 1;
    sort(a + 1, a + 1 + cl, [](line a, line b) {return a.x < b.x; });
    for (int i = 1; i <= cl; i ++) {
        node cur = get(a[i - 1].x, a[i].x - 1);
        answ.e += cur.e * W.e, answ.o += cur.o * W.o;
        ansb.e += cur.e * B.e, ansb.o += cur.o * B.o;
        int Y1 = find(a[i].y1), Y2 = find(a[i].y2);
        for (int j = Y1; j < Y2; j ++) {
            cur = get(re[j], re[j + 1] - 1);
            if (b[j] == 0 && a[i].d == -1) B.e += cur.e, B.o += cur.o;
            if (b[j] == 0 && a[i].d == 1) W.e += cur.e, W.o += cur.o;
            if (b[j] == 1 && a[i].d == -1) W.e -= cur.e, W.o -= cur.o;
            if (b[j] == -1 && a[i].d == 1) B.e -= cur.e, B.o -= cur.o;
            b[j] += a[i].d;
        }
    }
    printf("%lld %lld", answ.e + answ.o, ansb.e + ansb.o);
    return 0;
}
```

####

---

