# [ARC001D] レースゲーム

## 题目描述

![](https://cdn.luogu.org/upload/pic/36289.png)


高桥正在尝试玩赛车游戏。 比赛从 $(x,y)=(start,0)$ 处开始，向 $(x,y)=(goal,N)$ 处的目标前进。

对于 $0 \le y \le n$，我们给出了路径的左端和右端，这条路径就是依次连接这些区间两端的直线的内侧。

![](https://atcoder.jp/img/arc/001/4_1.png)

上图为输入 1 示例。红圈为起点，蓝圈为终点， 棕色区域为赛道。

赛车不能在赛道以外的任何地方行驶。此外，汽车能够在瞬间改变方向，而且汽车的宽度和长度必须可以忽略不计。

高桥希望找到从起点到目标的最短路径，从而征服这款赛车游戏。

## 说明/提示

- N 为整数，满足 $1 \le N \le 200,000$。

- $l_i$ 和 $r_i$ 为整数，满足 $0 \le li < ri \le 1,000,000$。

- $start$ 是整数，满足 $l_0 \le start \le r_0$。

- $goal$ 是整数，且满足 $l_N \le goal \le r_N$。

## 样例 #1

### 输入

```
7
3 3
2 5
4 6
2 3
3 6
3 4
4 6
2 5
1 5
```

### 输出

```
8.22677276241436
```

## 样例 #2

### 输入

```
5
3 3
0 5
0 5
0 5
0 5
0 5
0 5
```

### 输出

```
5
```

# 题解

## 作者：qqvq (赞：9)

感觉另一篇题解啥都没讲，，，样例的路径还画错了，，，，，，

大致思路是用两条直线维护当前点能不拐弯直接到达的最左和最右边界（左边界的直线只往右转，右边界的直线只往左转）。

将纵坐标相同称为"在同一层"，枚举所有可能拐弯的楼层。从当前层开始向上走，如果某一层更新两条直线后 “左边界的直线” 在 “右边界的直线” 左侧（只有在当前层的区间完全在能直接到达的区间左/右侧才会出现这种情况），如果当前层区间完全在左边，就把“当前点”移到当前层的左端点，否则移到右端点。

可以证明这样是最优的。

拿样例来说， $O$ 是 “当前点”（ $O$ 在第 $0$ 层）， $OA,OB$ 是维护可达区间的两条直线。在遍历到第二层时，发现 第二层的合法区间 完全在 $OA, OB$ 与第二层交点的区间 左侧，可以发现对于第二层的任意合法点 $C$ 和任意点 $D\in AB$ ，$OD+DC \leq OA + AC$ , 即不管想要到达第二层的哪一个点，第一层的拐点选 $A$ 都是最优的。

基于这个贪心策略就可以 $O(n)$ 通过此题了。

![](https://cdn.luogu.com.cn/upload/image_hosting/prvjg461.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**看代码前请熟悉最基本的向量运算。**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
double ans;
int s, t, n;
struct Vec {
  int x, y;
  Vec(int xx, int yy) : x(xx), y(yy) {}
  Vec() {}
  Vec operator - (Vec rhs) const {
    return Vec(x - rhs.x, y - rhs.y);
  }
  void operator += (Vec rhs) {x += rhs.x, y += rhs.y;}
  long long operator * (Vec rhs) const {
    return x * 1ll * rhs.y - y * 1ll * rhs.x;
  }
  double d() {
    return sqrt(x * 1ll * x + y * 1ll * y);
  }
} l[N], r[N];

int main() {
  scanf("%d%d%d", &n, &s, &t);
  for (int i = 0; i <= n; ++i) {
    scanf("%d%d", &l[i].x, &r[i].x);
    l[i].y = r[i].y = i;
  }
  l[0].x = r[0].x = s, l[n].x = r[n].x = t;
  Vec cur(s, 0), le, ri;
  int i, j = 0;
  while (j <= n) {
    i = cur.y + 1, j = i + 1;
    le = l[i] - cur, ri = r[i] - cur;
    while (j <= n) {
      bool f = 0, f1 = 0;
      if (ri * (r[j] - cur) > 0) ri = r[j] - cur, f = 1;
      if (le * (l[j] - cur) < 0) le = l[j] - cur, f1 = 1;
      if (le * ri > 0) {
        if (f) ans += le.d(), cur += le;
        else ans += ri.d(), cur += ri;
        break;
      }
      ++j;
    }
  }
  ans += (r[n] - cur).d();
  printf("%.15f", ans);
  return 0;
}
```

---

## 作者：Doveqise (赞：4)

这道题 一道大概暴力能过的样子  
具体思路就是向上走，然后在每个点找到能到达的倾斜角 最小 和 最大 的点  
然后判断哪一个点更优  
然后记录答案  
然后这样一直到终点  
最后的路径大概就像这样（图中红线）  
![AT48题解图](https://cdn.luogu.com.cn/upload/pic/61694.png)   
然后再介绍一下hypot()函数  
这个函数是算两点欧式几何距离哒  
大概就和代码中的getdis()效果相同  
不多说下面贴代码↓  
```cpp
#include <bits/stdc++.h>
using namespace std;
const double dis_max = 1e17;
const int maxn = 2e5 + 5;
int n, s, e;
int l[maxn], r[maxn];
double ans = 0;
double getdis(double a, double b)
{
    return sqrt(a * a + b * b);
}
void solve()
{
    l[n] = r[n] = e;
    int nowy = 0;
    double nowx = s;
    while (nowy < n)
    {
        double zuoarc = -dis_max, youarc = dis_max;
        int ly = nowy, ry = nowy;
        for (int y = nowy + 1; y <= n; y++)
        {
            double larc = (l[y] - nowx) / (y - nowy), rarc = (r[y] - nowx) / (y - nowy);
            if (larc > zuoarc)
            {
                zuoarc = larc;
                ly = y;
            }
            if (rarc < youarc)
            {
                youarc = rarc;
                ry = y;
            }
            if (zuoarc >= youarc)
            {
                if (ly < ry)
                {
                    ans += hypot/*getdis*/(l[ly] - nowx, ly - nowy);
                    nowy = ly;
                    nowx = l[ly];
                }
                else
                {
                    ans += hypot/*getdis*/(r[ry] - nowx, ry - nowy);
                    nowy = ry;
                    nowx = r[ry];
                }
                break;
            }
        }
    }
    return;
}

signed main()
{
    scanf("%d%d%d", &n, &s, &e);
    for (int i = 0; i <= n; i++)
        scanf("%d%d", &l[i], &r[i]);
    solve();
    printf("%0.14lf", ans);
    return 0;
}

```



---

## 作者：skyskyCCC (赞：2)

## 前言。
远古 ARC 题，通过数这么少的第四题我还是第一次见。这道题就是一个思维题。

题意简述：在网格图中给出起点和终点，求从起点到终点最短的距离，但是你必须在跑道上跑，给出 $2n$ 个点限制跑道的位置。然后你要从第 $0$ 层（就是最下面）跑到第 $n$ 层（最上面），每次只能在两点之间跑。就是需要算欧几里得距离的最小值。
## 分析。
显然我们知道两点之间线段最短。所以我们考虑以起点为起始点，建立两条直线，各维护两个端点，即维护两条线段 $l$ 和 $r$ 然后 $l$ 和 $r$ 的终点分别是能以跑直线的方式，可以到达跑道端点的最左端点和最右端点，注意到这里的左右端点并不是最终的左右端点，而是当前的最优的**能到达的**左右端点。

即想象把 $l$ 和 $r$ 两条直线固定起始点，然后一直往跑道的两边倾斜，碰到跑道边上的任意一点就停下。然后，一层层地往下找，如果到了某一层，这两条线交叉了，说明到达的当前的这一层，直线 $l$ 必然在右边的跑道上有交点，所以右边跑道的端点在当前的 $l$ 线的左侧，那么如果端点在左侧，那么让当前过原点的直线上下手。我们将在这个交点下面的直线保留，再将原点加上 $l$ 从而改变当前原点的位置，移动到上面去是最优的。

为什么是最优的？如果你折返然后往中间走，或者另外走直线 $r$ 都是多走路，这一点可以用将军饮马问题的相同思路，然后考虑三角形三边关系证明。那么如果走弯曲的路径的话，显然不会更优。

但是还有一种情况就是到达的当前层，左跑道的端点在当前的 $r$ 线的右侧，同理我们让原点加上截取的线段 $r$ 然后更新原点。

答案就是每次更新时所加的线段的长度，而这些线段就是最短路径。在遍历前，需要改变一下终点坐标限制，因为有可能我们在最后一层仍然需要改变原点，所以左右端点都改成 $\left(goal,n+1\right)$ 即可。

那么这样一定能接起来，成为通路吗？答案是肯定的。因为只能向着终点走，所以我们其中维护的端点相当于中转站，对于整个的路径没有影响。这就好比从 $A$ 地到 $B$ 地，我们只关心的是如何到达，而在这条路上我们经过的加油站只是加上油然后继续前进，所以对于整个的路径没有影响。综上所述，遍历结束后当前点一定是可以直接可以和终点相连，所以直接加上所有的长度即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int n,start,goal;
double ans;
int i_in,j_in;
struct vvector{//定义一个向量。 
	double x,y;
	vvector(int xx,int yy):x(xx),y(yy){}
	vvector(){};  
	double operator*(vvector k)const{
		return x*k.y-y*k.x;
	}
	vvector operator+(vvector k)const{
		return vvector(x+k.x,y+k.y);
	}
	vvector operator-(vvector k)const{
		return vvector(x-k.x,y-k.y);
	}//上面就是定义向量的一些运算。 
	double far(){
		return sqrt(x*x+y*y);
	}//欧几里得距离。 
}l[2000005],r[2000005];
int main(){
	cin>>n>>start>>goal;
	vvector ve(start,0),fir,sed;
	for (int i=0;i<=n;i++){
		cin>>l[i].x>>r[i].x;
		l[i].y=(double)i;
		r[i].y=(double)i;//注意统一单位。 
	}
	l[n].x=r[n].x=goal;//终点的要特殊改一下。 
	while(j_in+1<=n){
		j_in=ve.y+1;
		i_in=ve.y+2;
		fir=l[j_in]-ve,sed=r[j_in]-ve;//记录需要维护的l和r这两条线。 
		while(j_in+1<=n){
			int flag=0;
			if(fir*(l[i_in]-ve)<0){
			    fir=l[i_in]-ve;
				flag=1;
			}
			if(sed*(r[i_in]-ve)>0){
			    sed=r[i_in]-ve;
			}
			//上面的两个判断是在模拟l线和r线向两边互相逼近的过程。 
			if(fir*sed>0){//看看有没有偏航
				if(flag){
					ans+=sed.far();
					ve=ve+sed;
				}
				else{
					ans+=fir.far();
					ve=ve+fir;
				}
				break;
			}
			i_in++;
			j_in++;//注意相互逼近下，需要前进。 
		}
	}	
	ans+=(ve-l[n]).far();//最后加上所有的答案 
	printf("%.14lf\n",ans);
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：David_Mercury (赞：0)

题解区里都缺少对时间复杂度的证明，本份题解仅仅作为对此的一个补充。

可以发现所有题解都不约而同地包含了一个双重循环，第一层枚举上一个拐点，第二层枚举当前拐点在只走直线的情况下所能到达的最远层。直接看上去，复杂度是 $O(n^2)$ 的。

考虑在什么情况下复杂度能够取得最大值。

一个想法是构造一组满足直线斜率完全相同，但是在最后一层拐到一个极端的位置（例子见下）。~~然后你就惊喜地发现这样叉掉了题解区的全部三篇题解。~~

```
n=200000, s=0, t=0
0 1
1 2
2 3
3 4
...
199997 199998
199998 199999
1 2
0 1
```

但实际这个错误很容易修正。我们只需要在判定直线是否内拐时取等即可。

再考虑在进行了这个修正以后该怎么将复杂度卡满。可以发现我们应尽量构造点，使得关于斜率的最长上升子序列（严格单增）尽量长。大概形如下图（以后都默认起点为 $(0, 0)$）：

![qwq](https://cdn.luogu.com.cn/upload/image_hosting/gdizrn0d.png)

因为斜率上升和斜率下降的构造是等价的，为了方便起见，我们考虑斜率下降的构造。

可以证明：最优的构造一定形如 $(1, 1), (2, 1+2), (3, 1+2+3), \dots, (i, 1+2+\cdots+i)$。因为我们需要尽量节省横坐标的开销，所以上面的结论显然。

因此，最多的点数 $k$ 满足 $k(k+1)/2 = W$（$W$ 为值域），故 $k \approx \sqrt{W}$。故复杂度最劣为 $O(k^2) = O(W)$。

但还没有完。我们完全可以再重复放 $\dfrac{n}{k}$ 个相同的序列。此时就有复杂度为 $O(\dfrac{n}{k} * k^2) = O(n \sqrt{W})$，依旧能够通过。

为了便于理解，这里放一个极限数据的生成器：


```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;
int n, w = 1e6, s, t, k, l[MAXN], r[MAXN];

int main(){
//	freopen("qwq.in", "w", stdout);
	n = 2e5, s = t = 0, k = 2e3;
	l[0] = 0, r[0] = 1;
	for(int i = 1, j = k; i <= n; i++){
		--j;
		l[i] = l[i-1]+j, r[i] = w;
		if(l[i] > w)	l[i] = 0, r[i] = 1, j = k;
	}
	cout<<n<<" "<<s<<" "<<t<<endl;
	for(int i = 1; i <= n; i++)	cout<<l[i]<<" "<<r[i]<<endl;
	
	return 0;
}
```

下面是标程：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 2e5+5;
int n, m, s, t;
double ans;

struct Point{
	int x, y;
	
	Point operator - (const Point &tmp)const{
		return (Point){x-tmp.x, y-tmp.y};
	}
	
	Point operator + (const Point &tmp)const{
		return (Point){x+tmp.x, y+tmp.y};
	}
	
	ll operator * (const Point &tmp)const{
		return 1ll*x*tmp.y-1ll*y*tmp.x;
	}
	
	inline double Len(){
		return sqrt(1ll*x*x+1ll*y*y);
	}
	
	inline void Output(){
		printf("(%d,%d)", x, y);
		return;
	}
} l[MAXN], r[MAXN];

int main(){
//	freopen("qwq.in", "r", stdin);
	scanf("%d%d%d", &n, &s, &t);
	for(int i = 0; i <= n; i++)	scanf("%d%d", &l[i].x, &r[i].x), l[i].y = r[i].y = i;
	l[n].x = r[n].x = t;
	Point cur = (Point){s, 0};
	int i = 0;
//	int cnt = 0;
	while(i < n){
		++i;
		Point L = l[i]-cur, R = r[i]-cur;
//		cur.Output(); puts("");
		while(i < n){
//			++cnt;
			++i;
			if(L*(l[i]-cur) <= 0){//这里尽量取等复杂度才是正确的。 
				L = l[i]-cur;
				if(L*R > 0){
					cur = cur+R, i = cur.y;
					ans += R.Len();
					break;
				}
			}
			if(R*(r[i]-cur) >= 0){
				R = r[i]-cur;
				if(L*R > 0){
					cur = cur+L, i = cur.y;
					ans += L.Len();
					break;
				}
			}
		}
	}
//	cout<<cnt<<endl;
	ans += (r[n]-cur).Len();
	printf("%.10lf", ans);
	
	return 0;
}
```

另外说一句，似乎 AtCoder 上是有标准的 $O(n)$ 做法的，但我并没有看懂……希望以后能够有哪位童鞋看懂并且发在这里吧 qwq [link](https://atcoder.jp/contests/arc001/tasks/arc001_4/editorial)

---

