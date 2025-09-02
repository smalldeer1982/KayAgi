# [USACO20FEB] Triangles S

## 题目描述

Farmer John 想要给他的奶牛们建造一个三角形牧场。

有 $N$（$3\leq N\leq 10^5$）个栅栏柱子分别位于农场的二维平面上不同的点 $(X_1,Y_1)\ldots (X_N,Y_N)$。他可以选择其中三个点组成三角形牧场，只要三角形有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。

FJ 可以组成的所有可能的牧场的面积之和等于多少？

## 说明/提示

#### 样例解释：
栅栏木桩 ($0,0$)、($1,0$) 和 ($1,2$) 组成了一个面积为 $1$ 的三角形，($0,0$)、($1,0$) 和 ($0,1$) 组成了一个面积为 $0.5$ 的三角形。所以答案为 $2\times (1+0.5)=3$。

#### 子任务：
- 测试点 $2$ 满足 $N=200$。
- 测试点 $3$-$4$ 满足 $N\leq 5000$。
- 测试点 $5$-$10$ 没有额外限制。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 2```

### 输出

```
3```

# 题解

## 作者：泥土笨笨 (赞：30)

数据量$10^5$，如果依次取枚举三角形的三个顶点，复杂度$O(n^3)$，必然超时。题目中说只关心一条边和x轴重合，另一条边和y轴重合的三角形，那么这两条边组成了一个直角，我们先尝试枚举这个直角，看看以一个点作为直角顶点，能组成的所有三角形面积能否快速求出。

考虑如下图的样子

![图示](https://cdn.luogu.com.cn/upload/image_hosting/cu2g4yk9.png)

X点是我们所求的点，在X的左边还有A，B，C三个点，他们纵坐标相等。在X的下方还有F，E，D三个点，他们横坐标相等。那么此时以X为直角顶点，能组成多少个三角形，他们的面积的二倍的和是多少呢。我们设两点之间的线段长度已经用小写字符标在图上，可以算出，现在的总面积是：

$$(a+b+c)*d+(b+c)*d+c*d+(a+b+c)*(d+e)+(b+c)*(d+e)+c*(d+e)+(a+b+c)*(d+e+f)+(b+c)*(d+e+f)+c*(d+e+f)$$

$$=(a+2*b+3*c)*(f+2*e+3*d)$$

这个点的值，只和与自己横坐标相同的点，和与自己纵坐标相同的点有关。而且有点类似于前缀和，可以开一个数组，去记录每个横纵坐标各自积累的和是多少。当又来了一个新点，则把这个点对应的横坐标位置的和，加上4倍与上一个点之间的距离。纵坐标位置的和同理处理，所以我们发现还需要记录每行每列出现了几个数字了。再来一个新点，就加5倍距离，以此类推。

那么，我们按照x坐标从小到大，y坐标从小到大的顺序，依次去枚举每个点i，去做一下上述处理，然后计算结果出来。但是这个计算方式只对目前我们这种方向的三角形有效，事实上三角形的直角有四个方向，分别是冲着一二三四四个象限的方向。现在我们处理的，是直角在第三象限的情况。不过并不难处理，只要改一下点的排序方式，把同样的事情做4遍就行了。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll MAXN = 100005;
const ll MOD = 1e9 + 7;
const ll DIF = 10005;

struct Point {
    ll x, y;
} points[MAXN];

ll n, sumX[2 * DIF], sumY[2 * DIF], cntX[2 * DIF], cntY[2 * DIF];
ll lastX[2 * DIF], lastY[2 * DIF], ans;

bool cmp1(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool cmp2(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

bool cmp3(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x > b.x;
    return a.y < b.y;
}

bool cmp4(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x > b.x;
    return a.y > b.y;
}

void work() {
    memset(sumX, 0, sizeof(sumX));//sumX数组，存每个x坐标对应的和目前是多少
    memset(sumY, 0, sizeof(sumY));//存每个y坐标对应的和
    memset(cntX, 0, sizeof(cntX));//存每个x坐标出现过多少个数字了
    memset(cntY, 0, sizeof(cntY));
    for (ll i = 0; i < n; ++i) {//依次枚举每个点
        //用x和y记录一下当前点的x和y坐标，下面写起来轻松一点
        ll x = points[i].x, y = points[i].y;
        //当前x方向上的和，加上新点到上次的点的距离，乘以目前点的个数
        sumX[x] = (sumX[x] + abs(y - lastX[x]) * cntX[x]) % MOD;
        cntX[x]++;//多了一个点了
        lastX[x] = y;//记一下当前这个点的y值，下次跟这个来做差
        sumY[y] = (sumY[y] + abs(x - lastY[y]) * cntY[y]) % MOD;
        cntY[y]++;
        lastY[y] = x;
        ans = (ans + sumX[x] * sumY[y]) % MOD;//计算结果
    }
}

int main() {
    freopen("triangles.in","r",stdin);
    freopen("triangles.out","w",stdout);
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld", &points[i].x, &points[i].y);
        points[i].x += DIF;
        points[i].y += DIF;
    }
    //先延x从小到大，y从小到大的顺序排序，计算结果
    sort(points, points + n, cmp1);
    work();
    //其他方向依次处理
    sort(points, points + n, cmp2);
    work();
    sort(points, points + n, cmp3);
    work();
    sort(points, points + n, cmp4);
    work();
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：7KByte (赞：8)

这里提供一个更简单的方法。


首先考虑只统计直角顶点在右上角的三角形。


对于每个点，它的贡献是它正左边的点到该点的长度和乘以正下方的点到该点的长度和。


对于所有的点，按照$X$为第一关键字，$Y$为第二关键字排序。


对于左边的点，开一个桶统计总数。对于下边的点同理。


那么对于直角顶点不在右上角的三角形呢？

我们只用将所有的点绕原点旋转$90$°后再统计即可，总共旋转三次


时间复杂度$\operatorname{O(N)}$


```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100005
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n;
struct node{
	int x,y;
	bool operator<(const node o)const{
		if(x^o.x)return x<o.x;
		return y<o.y;
	}
}a[N];
typedef long long ll;
ll ans=0;const ll P = 1000000007LL;const int bas = 10007;
ll sum[N],cnt[N];
void solve(){
	sort(a+1,a+n+1);
	memset(sum,0,sizeof(sum));
	memset(cnt,0,sizeof(cnt));
	ll now = 0,tot = 0 ;
	//cout<<endl<<endl;
	rep( i , 1 , n ){
		//cout<<a[i].x<<" "<<a[i].y<<endl;
		if(a[i].x != a[i-1].x )now = 0 ,tot = 0 ;
		ans=(ans + ( a[i].x * cnt[a[i].y + bas] - sum[ a[i].y + bas ] )
		    % P * ( a[i].y * tot - now ) % P ) % P;
		tot++;now=(now+a[i].y)%P;
		cnt[a[i].y+bas]++;
		sum[a[i].y+bas]=(a[i].x+sum[a[i].y+bas])%P;
	}
	//cout<<ans<<endl;
}
void rev(){
	rep(i,1,n){
		int x=a[i].x,y=a[i].y;
		a[i].x=y;a[i].y=-x;
	}
}
int main(){
	//freopen("triangles.in","r",stdin);
	//freopen("triangles.out","w",stdout);
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&a[i].x,&a[i].y);
	rep(i,0,3){
		solve();rev();
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：tuxiaobei (赞：7)

### 题意

$N$ 个点，选取任意三个点组成三角形，要求三角形其中一条边平行于 $x$ 轴，另有一条边平行于 $y$ 轴。

求所有可能的三角形的面积之和的两倍，答案对 $10^9+7$ 取模。

### 算法1

暴力枚举三角形的三个顶点，遇到符合条件的三角形就累加答案。

时间复杂度 $O(N^3)$

期望得分：$20$ 分

### 算法2

三角形必定为直角三角形。

设与点 $p$ 的 $x$ 坐标相同的点的集合为 $A$ ，$y$ 坐标相同的点的集合为 $B$ 。

则以点 $p$ 为直角顶点的三角形面积之和的两倍：
$$
2S=\sum_{i \in A}\sum_{j \in B}|(i_y-p_y)(j_x-p_x)|=\sum_{i \in A}|i_y-p_y| \cdot\sum_{j \in B}|j_x-p_x|
$$


即点 $p$ 与所有 $x$ 坐标与其相同的点的距离之和乘所有 $y$ 坐标与其相同的点的距离之和。

对于每个点都 $O(N)$  遍历一遍其他点就可以得到两个距离之和。

总时间复杂度 $O(N^2 )$  ，期望得分 $40$ 分。

### 算法2优化

将所有点分别按 $x$ 坐标和 $y$ 坐标排序，

这样对于每个点，只需要分别在两个排序后的数组中向前向后遍历，直到 $x$ /  $y$ 坐标不相同。

这样就可以避免遍历很多无效点，对于每个点遍历时间复杂度 $O(1) \sim O(N)$  

最坏情况是所有点 $x$ / $y$ 坐标都相同。

整体时间复杂度 $O(N \log N )\sim O(N^2)$

期望得分 $40+$。

### 算法3

**下面讲解求解任意点到所有 $y$ 坐标与其相同的点的距离之和，$x$ 坐标同理。**

我们以 $y$ 坐标为第一关键字，$x$ 坐标为第二关键字从小到大排序。

对于一组 $y$ 坐标相同的点，称为一组，按 $x$ 坐标从小到大依次求解，

我们先通过遍历该组其他点的方式求解第一个点的距离之和，

接下来，我们求解第二个点的时候，考虑把第一个点的答案转移，利用前一个点的答案。

考虑答案的变化，设第二个点离第一个点的距离为 $d$ ，

与第一个点相比，到第一个点的距离增加了 $d$ ，而到该组其他点(包括第二个点)的距离均减少 $d$ 。

------

更一般地，设点 $i(i>1)$ 表示此点为该组第 $i$ 个点(即 $x$ 坐标第 $i$ 小的点)

设该组一共有 $n$ 个点，$s_i$  表示点 $i$ 的距离之和，$d_i$  表示点 $i$ 到点 $i-1$ 的距离。

当从点 $i-1$ 移动至点 $i$ 时，与点 $1 \sim i-1$ 之间的距离均增加 $d$ ，共增加 $(i-1)d$ ，

与点 $i \sim n$ 之间的距离均减少 $d$ ，共减少 $(n-i)d$ 。

合起来距离的变化量为 $(i-1)d-(n-i)d=(2i-n-1)d$

所以 $s_i=s_(i-1)+(2i-n-1)d$

求解所有点距离和时间复杂度 $O(N)$  ,加上排序总时间复杂度为 $O(N \log N)$。

期望得分:$100$ 分。

code:

```cpp
#include <bits/stdc++.h>
#define maxn 150000
using namespace std;
const int mod = 1e9 + 7;
struct point {
	int p, x, y;
}a[maxn], b[maxn];

bool cmp1(const point& a, const point& b) { if (a.x != b.x) return a.x < b.x; return a.y < b.y; }
bool cmp2(const point& a, const point& b) { if (a.y != b.y) return a.y < b.y; return a.x < b.x; }
int p[maxn], q[maxn];
int main()
{
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	int n;
	scanf("%d", &n);
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].p = i;
	}
	memcpy(b, a, sizeof(a));
	sort(a + 1, a + n + 1, cmp1);
	sort(b + 1, b + n + 1, cmp2);
	for (int i = 1; i <= n;) {
		int l = i;
		int sum = 0;
		for (; a[i].x == a[l].x; i++) sum += a[i].y - a[l].y, sum %= mod;
		int r = i;
		int cnt = r - l;
		for (int i = l; i < r; i++) {
			p[a[i].p] = sum;
			long long dis = a[i + 1].y - a[i].y;
			sum = (sum + ((i - l + 1) * 2 - cnt) * dis) % mod;
			if (sum < 0) sum += mod;
		}
	}
	for (int i = 1; i <= n;) {
		int l = i;
		int sum = 0;
		for (; b[i].y == b[l].y; i++) sum += b[i].x - b[l].x, sum %= mod;
		int r = i;
		int cnt = r - l;
		for (int i = l; i < r; i++) {
			q[b[i].p] = sum;
			long long dis = b[i + 1].x - b[i].x;
			sum = (sum + ((i - l + 1) * 2 - cnt) * dis) % mod;
			if (sum < 0) sum += mod;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += ((long long)p[i] * q[i]) % mod;
		ans %= mod;
	}
	printf("%d\n", ans);
}
```

---

## 作者：fanhy (赞：6)

这里提供一种更为简便的方法（指不用对坐标进行处理）

~~主要就是想炫耀一下自己优美的代码~~\[doge]

算法楼下已经讲的很清楚了，简单复述一下：

枚举每一个定点，由于计数时只记录当前顶点为直角定点的Rt三角形，因此计数不会重复。

从横纵坐标两个方向来考虑，分别计算以这个点为一个端点的平行于坐标轴的线段长度和。很容易想到以这个定点为直角定点的Rt三角形面积的2被就是两数乘积。（看不懂的人结合图像细品）

```cpp
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

const int MAXN = 100000 + 5;
struct node { int x, y; long long sumx, sumy; } p[MAXN];
int n, last;
long long usumx[MAXN], usumy[MAXN], dsumx[MAXN], dsumy[MAXN];
//四个数组分别存从左到右到点i的线段长度和、从下到上、从右到左、从上到下
long long ans;

//横坐标优先排序，用于竖直方向的计算
bool cmpx (node a, node b)
{ return a.x == b.x ? a.y < b.y : a.x < b.x; }

//纵坐标优先排序，用于水平方向的计算
bool cmpy (node a, node b)
{ return a.y == b.y ? a.x < b.x : a.y < b.y; }

int main()
{
	scanf("%d", &n);
   //确定上下界
	p[0].x = -1; p[0].y = -1;
	p[n + 1].x = -1, p[n + 1].y = -1;
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	//竖直方向
    sort (p + 1, p + n + 1, cmpx);
	for (int i = 1; i <= n; i++)
	{
		if (p[i].x != p[i - 1].x) last = i;
		else usumy[i] = usumy[i - 1] + (p[i].y - p[i - 1].y) * (i - last); //连加计算线段长度和
	}
	for (int i = n; i >= 1; i--)
	{
		if (p[i].x != p[i + 1].x) last = i;
		else dsumy[i] = dsumy[i + 1] + (p[i + 1].y - p[i].y) * (last - i);
	}
	for (int i = 1; i <= n; i++) p[i].sumy = usumy[i] + dsumy[i]; //竖直方向线段长度和
	//水平方向
   sort (p + 1, p + n + 1, cmpy);
	for (int i = 1; i <= n; i++)
	{
		if (p[i].y != p[i - 1].y) last = i;
		else usumx[i] = usumx[i - 1] + (p[i].x - p[i - 1].x) * (i - last);
	}
	for (int i = n; i >= 1; i--)
	{
		if (p[i].y != p[i + 1].y) last = i;
		else dsumx[i] = dsumx[i + 1] + (p[i + 1].x - p[i].x) * (last - i);
	}
	for (int i = 1; i <= n; i++) p[i].sumx = usumx[i] + dsumx[i]; //水平方向线段长度和
	for (int i = 1; i <= n; i++)
	{
		ans += p[i].sumx * p[i].sumy % MOD; //计算面积*2
		ans %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：jdsb (赞：4)

$update:$有个公式写错了，修正一下。
## 题意
在平面直角坐标系上给出$n$个点，问直角边与$x$轴和$y$轴平行的直角三角形的面积和。
## 分析
首先观察数据，发现$n$为$10^5$，如果是暴力枚举任意三个点的组合时间复杂度为$O(n^3)$，肯定会T。我们就来思考如何在$O(n)$或$O(n\ log\ n)$的时间内求出答案。我们来画个图 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/hzf94b1u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于以$O$点为直角顶点的三角形，假设和它纵坐标相同的点的距离分别为$a_1,a_2,a_3$，和它横坐标相同的点的距离分别为$b_1,b_2,b_3$。则点O对答案的贡献为$\frac{1}{2}*(a_1+a_2+a_3)*(b_1+b_2+b_3)$，所以我们可以发现一个结论，设与当前点的纵坐标相同的点的横坐标为$x_i$，与它横坐标相同的点的纵坐标为$y_j$，则这个点对答案的贡献就为$\sum_i x_i * \sum_j y_j$。但我们其实不能直接枚举每个点与其它点的距离，因为这样的时间复杂度是$n^2$的，我们不能接受，这个时候我们再来看看一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8mjv94zn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果把原来的线段拆开来，那么$a_1+a_2+a_3=3*a+2*b+c$，$b_1+b_2+b_3=3*f+2*e+d$。
这两个东西是等价的，对于$a$这段距离，因为后面有三个点经过，所以它对于总距离来说就提供了$3*a$。

那我们其实就可以根据这个性质来计算我们原来的每个点到其它点的距离和，我们设$rt[i]$表示点$i$到右边的点的距离和，当我们有一组纵坐标相同，横坐标递增的点时，我们记已经进入了$s$个点，则$rt[i]=rt[i+1]+s*(x[i+1]-x[i])$。同理，我们还能求出$up[i]$，表示点$i$到上方的点的距离和。那最后的答案就为$\sum_{i=1}^n up[i]*rt[i]$(不乘$\frac{1}{2}$是因为最后要求的是面积乘$2$的答案)。还要注意，我们现在求的只是直角边朝向上方和右方的三角形的面积，还有其他三个方向的三角形，我们就通过数轴的对称性来把它们转到这个方向。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e5+5,p=1e9+7;
struct pos
{
	int x,y,id;
}a[N],b[N];
bool mycmp1(pos x,pos y)
{
	if(x.x^y.x) return x.x<y.x;
	return x.y<y.y;
}
bool mycmp2(pos x,pos y)
{
	if(x.y^y.y) return x.y<y.y;
	return x.x<y.x;
}
int tot,n;
ll ans,up[N],rt[N];
void solve()
{
	memset(up,0,sizeof(up));
	memset(rt,0,sizeof(rt));
	sort(a+1,a+n+1,mycmp1);
	tot=0;
	b[++tot]=a[1];
	for(int i=2;i<=n;i++)
	{
		if(a[i].x!=a[i-1].x)
		{
			ll s=1;
			for(int j=tot-1;j>=1;j--)
			{
				up[b[j].id]=up[b[j+1].id]+s*(b[j+1].y-b[j].y);
				s++;
			}
			tot=0;
		}
		b[++tot]=a[i];
	}
	ll s=1;
	for(int j=tot-1;j>=1;j--)
	{
		up[b[j].id]=up[b[j+1].id]+s*(b[j+1].y-b[j].y);
		s++;
	}
	sort(a+1,a+n+1,mycmp2);
	tot=0;
	b[++tot]=a[1];
	for(int i=2;i<=n;i++)
	{
		if(a[i].y!=a[i-1].y)
		{
			ll s=1;
			for(int j=tot-1;j>=1;j--)
			{
				rt[b[j].id]=rt[b[j+1].id]+s*(b[j+1].x-b[j].x);
				s++;
			}
			tot=0;
		}
		b[++tot]=a[i];
	}
	s=1;
	for(int j=tot-1;j>=1;j--)
	{
		rt[b[j].id]=rt[b[j+1].id]+s*(b[j+1].x-b[j].x);
		s++;
	}
	for(int i=1;i<=n;i++)
		ans=(ans+rt[i]*up[i])%p;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i;
	}
	solve();
	for(int i=1;i<=n;i++) a[i].x=-a[i].x;
	solve();
	for(int i=1;i<=n;i++) a[i].y=-a[i].y;
	solve();
	for(int i=1;i<=n;i++) a[i].x=-a[i].x;
	solve();
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Justin0779 (赞：2)

说在前面：这道题的细节很多，不过与 [NOIP2022种花](https://www.luogu.com.cn/problem/P8865) 很像，是一道不错的好题。今天在模拟赛上切到，有感遂来一篇题解。

# Solution

我们观察题目，发现有**一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行**这个条件，那么我们很容易得出，只有类似于直角的三个点才有可能作出贡献。但是，处于同一列、同一行的点可能很多，那么我们考虑按 $y$ 坐标排序后升序处理。

此时对于每一个 $y$，我们找到纵坐标为 $y$ 的所有点并按 $x$ 升序排序，并且记录所有可能的竖着的以该点为端点的三角形边的总长，记为 $can_i$，那么设答案为 $ans$，记前面已经扫完了 $1\sim k$ 的点，扫到点 $k+1$ 时有转移：

$$
ans\gets ans+\sum_{i=1}^{k}(x_{k+1}-x_i)\times(can_{k+1}+can_i)
$$

这里直接乘是因为最后答案要为 $2$ 倍，所以直接按矩形处理即可。而 $can_i$ 可以在转移前被 $O(n)$ 预处理完。

上面的式子看起来转移是 $O(n)$ 的，尝试优化。我们把式子拆开，发现有：

$$
\sum_{i=1}^{k}(x_{k+1}-x_i)\times(can_{k+1}+can_i)=k\times x_{k+1} \times can_{k+1} + x_{k+1}\times \sum_{i=1}^{k}can_i  - can_{k+1} \times\sum_{i=1}^{k}x_i - \sum_{i=1}^{k}x_i\times can_i
$$

我们发现我们可以在转移的同时维护：

$$
k，\sum_{i=1}^{k}can_i，\sum_{i=1}^{k}x_i，\sum_{i=1}^{k}x_i\times can_i
$$

这样我们完成了 $O(1)$ 的转移，剩下的就是烦琐的细节了。本题到这里就结束了。

转移并不是瓶颈，瓶颈在于预处理及转移前的排序，时间复杂度 $O(n\log n)$。

# Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e5 + 514;
constexpr ll mod = 1e9 + 7;

namespace Trangle
{
    int n, ep[N];
    ll ans, sumn, xsumx, sumxy, tot, can[N], sum[N];

    struct PT
    {
        int x, y, id;
    } pt[N];

    bool cmpX(PT X, PT Y) {
        if (X.x != Y.x)
            return X.x < Y.x;
        return X.y < Y.y;
    }

    bool cmpY(PT X, PT Y)
    {
        if (X.y != Y.y)
            return X.y < Y.y;
        return X.x < Y.x;
    }

    void init() {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> pt[i].x >> pt[i].y, pt[i].x += 10000, pt[i].y += 10000, pt[i].id = i;

        sort(pt + 1, pt + n + 1, cmpX);
        int it = 1;
        for (int i = 0; i <= 20000; i++)
        {
            sum[0] = 0;
            tot = 0;
            ep[0] = 0;
            while (pt[it].x == i)
            {
                tot++;
                sum[tot] = sum[tot - 1] + pt[it].y;
                ep[tot] = it;
                it++;
            }
            if (tot < 2)
                continue;
            for (int j = 1; j <= tot; j++) {
                if (j == 1) {
                    can[pt[ep[1]].id] = sum[tot] - tot * pt[ep[1]].y;
                    continue;
                }
                can[pt[ep[j]].id] = can[pt[ep[j - 1]].id];
                can[pt[ep[j]].id] += (ll)(pt[ep[j]].y - pt[ep[j - 1]].y) * (j - 1);
                can[pt[ep[j]].id] -= (ll)(pt[ep[j]].y - pt[ep[j - 1]].y) * (tot - j + 1);
            }
        }
        sort(pt + 1, pt + n + 1, cmpY);
        it = 1;
        for (int i = 0; i <= 20000; i++)
        {
            sumn = 0;
            xsumx = 0;
            sumxy = 0;
            tot = 0;
            while (pt[it].y == i)
            {
                ans -= xsumx + sumxy * can[pt[it].id];
                ans += pt[it].x * sumn + (can[pt[it].id] * tot) * pt[it].x;
                ans = ans % mod;
                xsumx += pt[it].x * can[pt[it].id];
                sumxy += pt[it].x;
                tot++;
                sumn += can[pt[it].id];
                it++;
            }
        }
        cout << ans;
    }

} // namespace Trangle

int main() {

    // freopen("main.in", "r", stdin);
    // freopen("main.out", "w", stdout);
    Trangle::init();
    return 0;
}
```

---

## 作者：kczw (赞：2)

# 首先
这道题暴力肯定是不行的（显而易见）。

但是我们可以对其进行优化。

对于每一个点 $(X,Y)$ ，当我们把它当作一个直角三角形的顶点时我们可以先算出所有横坐标等于 $X$ 的点到点 $(X,Y)$ 的距离，同时算出所有纵坐标等于 $Y$ 的点到点 $(X,Y)$ 的距离，最后相乘就可以得出以此点为直角点的所有直角三角形的面积的两倍。以次类推，我们算出每个点作为直角顶点的面积和后，相加即可得出结果。
- 当然，不要忘了求模。

（~~最后只需吸口氧气即可通过~~）
```cpp
#include<iostream>
#include<vector>
#include<math.h>
#define int long long
#define Mod 1000000007
#define N 20005
using namespace std;
vector<pair<int,int> > h[N],s[N];
int ans,n,x[N<<3],y[N<<3];
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        x[i]+=10000;
        y[i]+=10000;
        s[x[i]].push_back({x[i],y[i]});
        h[y[i]].push_back({x[i],y[i]});
    }for(int i=1;i<=n;i++){
        int dh=0,ds=0;
        for(auto p:s[x[i]])dh+=abs(p.second-y[i]);
        for(auto p:h[y[i]])ds+=abs(p.first-x[i]);
        ans=(ans+(dh*ds)%Mod)%Mod;
    }printf("%lld",ans);
    return 0;
}
```


---

## 作者：yxy666 (赞：2)

通过分析右边的这幅图，我们会发现当我们把题目数据画到直角坐标系时，我们只要定下来一个坐标为（$x0$,$y0$) 的点时，它与其他点构成的面积总和为(定义 $x-y$ 为 $x$ 点到 $y$ 点的直线距离)：$(x0-x1)(y0-y1)+(x0-x1)(y0-y2)+(x0-x1)(y0-y3)+(x0-x1)(y0-y4)+$$(x0-x2)(y0-y1)+(x0-x2)(y0-y2)+(x0-x2)(y0-y3)+(x0-x2)(y0-y4)+$$(x0-x3)(y0-y1)+(x0-x3)(y0-y2)+(x0-x3)(y0-y3)+(x0-x3)(y0-y4).$

我们合并同类项后，就得到了 $(x0-x1)(y0-y1+y0-y2+y0-y3+y0-y4)$+$(x0-x2)(y0-y1+y0-y2+y0-y3+y0-y4)$+$(x0-x3)(y0-y1+y0-y2+y0-y3+y0-y4).$ 

我们继续合并同类项，发现就成为了$(3x0-x1-x2-x2)(4y0-y1-y2-y3-y4)$。

而 $-(x1+x2+x3)$ 可以通过前缀和来实现， $-(y1+y2+y3+y4)$ 也可以通过前缀和来实现。那么不就好办了么。$x0$ 和 $y0$ 前面的系数可以通过累加得到。但是有一点还是要注意：对于一个点来说，可不止一个方向，而是四个方向，那我们就旋图后再来处理呗。旋完图后原 $y=-x,x=y$ 。因为我们是九十度旋图，原来负的需要变正。

$code$ :
```cpp
#include<bits/stdc++.h>
#define TT 1000000007
#define r 10000
using namespace std;
const int maxn=200005;

int n;
long long ans,cnt[maxn],sum[maxn];

struct yxy{
	int x,y;bool operator<(const yxy b)const{return x<b.x||(x==b.x&&y<b.y);}
}a[maxn/2];

inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f; 
}

void solve(){
	sort(a+1,a+1+n);
	memset(cnt,0,sizeof cnt);
	memset(sum,0,sizeof sum);
	long long tot=0,now=0;
	for(int i=1;i<=n;i++){
		if(a[i].x!=a[i-1].x)tot=0,now=0;
		ans=(ans+(cnt[a[i].y+r]*a[i].x-sum[a[i].y+r])%TT*(tot*a[i].y-now))%TT;
		cnt[a[i].y+r]++;tot++;now=(now+a[i].y)%TT;sum[a[i].y+r]=(sum[a[i].y+r]+a[i].x)%TT;
	}
}

void turn(){
	int x;
	for(int i=1;i<=n;i++)x=a[i].x,a[i].x=a[i].y,a[i].y=-x;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read();
	for(int i=1;i<=4;i++)solve(),turn();
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Na2PtCl6 (赞：2)

~~USACO的题怎么这么多都可以乱搞啊~~

---
## 分析题目


题目要我们求的是直角坐标系上直角边与 $x$,$y$ 轴平行的所有 $RT\triangle$ 总面积的 2 倍，可以把它转化为求每个点所在**横向线段总长**和**纵向线段总长**的乘积

我们可以把 $x$ 坐标相同的点的 $y$ 坐标记录一下；把 $y$ 坐标相同的点的 $x$ 坐标记录一下，来优化下面的计算。

然后循环每个点。每次循环中，我们利用刚才记录的坐标，计算出这个点所在**横向线段总长**和**纵向线段总长**，并把结果加上**横向线段总长**和**纵向线段总长**的乘积

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=20004,mod=int(1e9+7);
int n;
long long xsum,ysum,res;
struct point{ int x,y;}s[100004]; 
//把x坐标相同的点的y坐标记录一下;把y坐标相同的点的x坐标记录一下 
vector < int > xpos[maxn],ypos[maxn];

inline const int _abs(const int &val){
	return val>0?val:-val;
}

//因为x,y坐标会有负数,要把它变成正的,这样可以当作下标来用 
inline int HASH(const int &x){
	if(x>=0)
		return x;
	return -x+10000;
}

//把处理过的x,y坐标变成原来的数值 
inline int unHASH(const int &x){
	if(x<=10000)
		return x;
	return -(x-10000);
}

inline int read(){
	char f=0,c=getchar();int ret=0;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')
			f=1;
	for(;c>='0'&&c<='9';c=getchar())
	    ret=(ret<<1)+(ret<<3)+c-48;
	return f?-ret:ret;
}

int main(){
	n=read();
	for(int i=0;i<n;i++)
		s[i].x=HASH(read()),s[i].y=HASH(read());
	for(int i=0;i<n;i++){
		xpos[s[i].x].push_back(s[i].y);
		ypos[s[i].y].push_back(s[i].x);
	}
	for(int i=0;i<n;i++){
		point now=s[i];
		int sz1=xpos[now.x].size(),sz2=ypos[now.y].size();
		for(int j=0;j<sz1;j++)
			ysum+=_abs(unHASH(now.y)-unHASH(xpos[now.x][j])); 
		for(int j=0;j<sz2;j++)
			xsum+=_abs(unHASH(now.x)-unHASH(ypos[now.y][j]));
		res=(res+xsum*ysum)%mod;
		xsum=ysum=0;
	}
	printf("%lld",res);
	return 0;
}
```

请思考，如何用 二分查找 + 前缀和 优化此解法

---

## 作者：LTb_ (赞：2)

[更好的阅读](https://lycltb.github.io/post/solution-usaco2020feb-silver-triangles/)

#### 思路分析

很简单但是（至少对于lyc来说）细节比较多。

首先离散化是必须的。然后先考虑暴力。把某一行/列中的点记在一个```vector```里。枚举每一个点作为三角形的直角顶点，暴力找有哪些点可以与它构成三角形。显然是$\mathcal{O(n^2)}$的。 （考场上居然算错复杂度了~~草~~

然后我们考虑优化查找“与当前枚举的点可以构成三角形的点对”的过程。

为了方便，我们用$(x_i,y_i)$表示第$i$个点的坐标。

我们仍然枚举在三角形中作为直角顶点的点$d$，用$(x_d,y_d)$代表。显然，与当前顶点组成三角形的点对要满足的条件是“点对中一个点与$(x_d,y_d)$的横坐标相同，另一个点与$(x_d,y_d)$纵坐标相同”，~~说人话就是~~也就是当前点所处的行上选一个，所在列选一个。我们设当前**列**有$k1$个点，第$i$个点的编号是$a_i$；当前**行**有$k2$个点，第$i$个点的编号是$b_i$。

那么这些点对为

$(a_1,b_1),(a_1,b_2)\dots(a_1,b_{k2}),(a_2,b_1),(a_2,b_2)\dots (a_{k1},b_{k2})$

我们的答案为$\sum\limits_{i=1}^{k1} \sum\limits_{j=1}^{k2} \left|y_d-y_{a_i} \right| \times \left|x_d-x_{b_j} \right|$

考虑前缀和优化，具体来说就是每一行/列对于**点的原始坐标**排序，然后做前缀和。

然后我们可以通过前缀和在$\mathcal{O(1)}$时间内求出这个式子的值，会在代码说明里具体说明。

然后累加答案就可以了。

已经懂了的就不用看下去了wwww

#### 代码说明

先放代码：

有点乱 将就着看吧wwwwww

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
#define int long long
const int MAXN=100005;
const int MOD=1e9+7;
int n;
int mx,my;
pair<int,int> a[MAXN];
int ls1[MAXN],ls2[MAXN];
int x[MAXN],y[MAXN];
vector<int> vx[MAXN],vy[MAXN];
vector<int> sumx[MAXN],sumy[MAXN];
int ans=0;

signed main()

{
    //读入
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i].first>>a[i].second;
		ls1[i]=a[i].first;
		ls2[i]=a[i].second;
	}

	//离散化
	sort(ls1+1,ls1+1+n);
	sort(ls2+1,ls2+1+n);
	mx=unique(ls1+1,ls1+1+n)-ls1-1;
	my=unique(ls2+1,ls2+1+n)-ls2-1;
	for (int i=1;i<=n;i++)
		x[i]=lower_bound(ls1+1,ls1+1+mx,a[i].first)-ls1;

	for (int i=1;i<=n;i++)
		y[i]=lower_bound(ls2+1,ls2+1+my,a[i].second)-ls2;

	for (int i=1;i<=n;i++){
		vx[x[i]].push_back(y[i]);
		vy[y[i]].push_back(x[i]);
        //注意这里存的是y[i]和x[i]，不是点的编号。
	}

	//处理前缀和 & 排序
	for (int i=1;i<=mx;i++){
		sort(vx[i].begin(),vx[i].end());
		int sum=0;
		sumx[i].push_back(0);
		for (int j=0;j<vx[i].size();j++){
			sum+=ls2[vx[i][j]];
			sumx[i].push_back(sum);
		}
	}

	for (int i=1;i<=my;i++){
		sort(vy[i].begin(),vy[i].end());
		int sum=0;
		sumy[i].push_back(0);
		for (int j=0;j<vy[i].size();j++){
			sum+=ls1[vy[i][j]];
			sumy[i].push_back(sum);
		}
	}

	for (int i=1;i<=n;i++){
		int posx=lower_bound(vx[x[i]].begin(),vx[x[i]].end(),y[i])-vx[x[i]].begin();//点i在x值相同的一列中y值的排名
		int posy=lower_bound(vy[y[i]].begin(),vy[y[i]].end(),x[i])-vy[y[i]].begin();//点i在y值相同的一行中x值的排名
		int sz1=vx[x[i]].size();
		int tmpx=(posx*ls2[y[i]]-sumx[x[i]][posx])%MOD+(sumx[x[i]][sz1]-sumx[x[i]][posx+1]-(sz1-posx-1)*ls2[y[i]])%MOD;

		int sz2=vy[y[i]].size();
		int tmpy=(posy*ls1[x[i]]-sumy[y[i]][posy])%MOD+(sumy[y[i]][sz2]-sumy[y[i]][posy+1]-(sz2-posy-1)*ls1[x[i]])%MOD;
		ans+=tmpx*tmpy;
		ans%=MOD;
	}

	cout<<ans<<endl;
	return 0;
}
```

离散化不用多讲，```x,y```分别存放坐标离散化后的横/纵坐标。

处理前缀和也没啥好讲的wwww，要注意的是在最前面```push_back```一个0以免越界。

然后用```lower_bound```查找当前点在当前行/列的排名，意义见注释。

```sz1,sz2```分别是当前列/行点的个数**+1**（因为前面多了一个0

我们可以把上面的式子写成 $\sum\limits_{i=1}^{k1}  \left|y_d-y_{a_i} \right| \times  \sum\limits_{i=1}^{k2}\left|x_d-x_{b_i} \right|$

然后我们可以分别算出这两个式子的值，也就是代码中的```tmpx,tmpy```。

它们的意义分别是“在当前列的所有点‘与当前点的纵坐标之差’之和”，“在当前行的所有点‘与当前点的横坐标之差’之和”。

可以用前缀和求出，对于位置小于和大于（当然是在当前行/列中）当前点的点分别处理。

乘一下，累加答案，模一下。

做完了

最后说句闲话（？） 抓到bug的话请务必告诉我wwww

毕竟没写过两篇题解（

---

## 作者：信守天下 (赞：2)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6149)
## 思路
每个三⻆形都可以通过直⻆点进⾏唯⼀的确定。

所以我们通过枚举直⻆点，就可以不重复的找到所有的三⻆形。

对于当前直⻆点，它可以任选⼀个同 $x$ 坐标的点和⼀个同 $y$ 坐标的点构成三⻆形。

那么这些三角形的总面积。

应该等于它与所有同 $x$ 点的 $y$ 坐标差之和，乘以它与所有同 $y$ 点的 $x$ 坐标差之和。

为了求出每个点与它同 $x$ 点的 $y$ 坐标差之和，我们可以对点按照先 $x$ 后 $y$ 进行排序。

这样就可以按照 $y$ 顺序取出所有 $x$ 相同的段。

对于每一段，通过对 $y$ 坐标计算前缀和。

就能够快速的求出每个点和其他点的 $y$ 坐标差之和了。

求出同 $y$ 点的 $x$ 坐标差之和同理。
## 复杂度分析
### 时间复杂度
排序 $O (N \log N)$ 。

枚举段并计算总共 $O(N)$ 。

总时间复杂度为 $O (N \log N)$ 。
### 空间复杂度
记录点 $O(N)$ 。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
const int kM = 1e9 + 7;
struct P {  // 点
  long long x, y, sx, sy;
  bool operator<(const P &p) const {  // 先x后y排序
    return x < p.x || (x == p.x && y < p.y);
  }
} p[kMaxN];
int n;
long long ans;
void W() {
  sort(p + 1, p + 1 + n);
  for (int i = 1, j = 1, r = 0; i <= n; i = j) {  // 枚举x相同的段
    for (; p[j].x == p[i].x; j++) {               // 找到段的右边界
      r += p[j].y;                                // 累加后缀和
    }
    for (int k = i, l = 0; k < j; k++) {                                 // 枚举段中的点
      r -= p[k].y;                                                       // 更新后缀和
      p[k].sy = (r - (j - k - 1) * p[k].y + p[k].y * (k - i) - l) % kM;  // 计算线段和
      l += p[k].y;                                                       // 更新前缀和
    }
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].x >> p[i].y;
  }
  W();                            // 统计每个点y方向线段和
  for (int i = 1; i <= n; i++) {  // 交换xy
    swap(p[i].x, p[i].y), swap(p[i].sx, p[i].sy);
  }
  W();                            // 统计每个点x方向线段和
  for (int i = 1; i <= n; i++) {  // 计算答案
    ans = (ans + p[i].sx * p[i].sy) % kM;
  }
  cout << ans;
  return 0;
}
~~~

---

## 作者：kardsOI (赞：0)

# 题目大意
给定平面上 $n$ 个点，可以选择其中三个点组成一个直角三角形且其两直角边分别平行于 $x$ 与 $y$ 轴，求所有此类三角形的面积二倍和模 $10^9+7$。

# 分析

1. 既然要求的是三角形的面积的两倍，那么对于每个三角形直接求出 $x$ 与 $y$ 坐标的极差相乘的积即可，没必要开浮点数。
2. 由提，我们需要找到三个变量使其中两个的 $x$ 坐标相等，还有两个 $y$ 坐标相等。
3. 如果三个三个点枚举的话**稳稳的超时**。所以考虑记录每个变量在同一 $x$ 坐标轴上其他变量与其距离的和与同一 $y$ 坐标轴上其他变量与其距离的和，相乘后再把每个点得出的积相加即可。由乘法分配律可知，这与分别枚举每个三角形求出二倍面积相加得出的和相等。

# 优化做法

首先对每个点的坐标，先以 $x$ 坐标为第一关键字，以 $y$ 坐标为第二关键字进行排序，再从头到尾进行遍历，同时统计之前与其 $x$ 坐标相同的点距离之和，统计到每列末尾（下一个点的 $x$ 坐标与它们不相等）时再循环一次返回来统计每个点之后与其 $x$ 坐标相同的点的坐标之和，然后之前的和与之后的和相加就是每个点与所有同 $x$ 坐标的点距离之和。

接着，对每个点的坐标先以 $y$ 坐标为第一关键字，以 $x$ 坐标为第二关键字进行排序，再进行相似操作统计出每个点与所有同 $x$ 坐标的点距离之和。然后就是把每个点求出的两个值相乘，再把每个点得出的积相加（注意随时求模）的操作。时间复杂度 $O(n)$，包不超时的呀。

# 最后奉上~~码风清奇的~~代码

```cpp
#include<bits/stdc++.h>
#define kafuu return
#define  chino 0;
using namespace std;
struct stick
{
    long x1,y1;
    long dy1,dy2;
    long dx1,dx2;
}a[300100];
int n,po;
long long MOD=1000000007,result;
bool cmp1(stick ax,stick bx)
{
    return ax.x1<bx.x1||(ax.x1==bx.x1&&ax.y1<bx.y1);
}
bool cmp2(stick ax,stick bx)
{
    return ax.y1<bx.y1||(ax.y1==bx.y1&&ax.x1<bx.x1);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x1>>a[i].y1;
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=1;i<=n;i++)
    {
        for(po=i+1;po<=n&&a[po].x1==a[i].x1;po++)
        {
            a[po].dy1=a[po-1].dy1+(a[po].y1-a[po-1].y1)*(po-i);
        }
        po--;
        for(int j=po-1;j>=i;j--)
        {
            a[j].dy2=a[j+1].dy2+(a[j+1].y1-a[j].y1)*(po-j);
        }
        i=po;
    }
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++)
    {
        for(po=i+1;po<=n&&a[po].y1==a[i].y1;po++)
        {
            a[po].dx1=a[po-1].dx1+(a[po].x1-a[po-1].x1)*(po-i);
        }
        po--;
        for(int j=po-1;j>=i;j--)
        {
            a[j].dx2=a[j+1].dx2+(a[j+1].x1-a[j].x1)*(po-j);
        }
        i=po;
    }
    for(int i=1;i<=n;i++)
    {
        result=(result+(a[i].dy1+a[i].dy2)*(a[i].dx1+a[i].dx2))%MOD;
    }
    cout<<result<<'\n';
    kafuu chino
}
```

---

