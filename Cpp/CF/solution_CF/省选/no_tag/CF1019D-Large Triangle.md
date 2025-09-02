# Large Triangle

## 题目描述

有一个奇特的现象：如果你将 Rostov、Taganrog 和 Shakhty 三个城市连接起来，会奇妙地得到一个三角形。

“不可思议但真实”

来自俄罗斯各地及国外的学生来到夏季信息学学校。你在地图上标记了 SIS 参与者的家乡。

现在你决定基于这张地图制作一份有趣的信息图。你选择做的第一件事是，在这张地图上找到三个城市，使它们组成一个面积为 $S$ 的三角形。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 7
0 0
3 0
0 4
```

### 输出

```
No
```

## 样例 #2

### 输入

```
4 3
0 0
2 0
1 2
1 3
```

### 输出

```
Yes
0 0
1 3
2 0
```

# 题解

## 作者：AuCloud (赞：5)

考虑显然过不了的$n^3$暴力——枚举三个点并判断面积是否为S

想拿二分砍掉一个n，变成$n^2logn$，但问题是没有单调性

于是问题就转化为如何将这么多点变成对于给定直线的距离具有单调性

由`平面最近点对加强版`的第一篇题解~~善用人类的智慧~~启发，考虑枚举线段并把它转成竖直的（水平的也行）

然后按照点到线段的距离排序就行

但是如果就这样裸排序时间还会凭空多一个log…

所以就去想想如何优化排序过程

我们先按x把点排序

如果让这个顺序每次只动一个就好了

画几个图直观感受一下，发现对于一对点a,b，只有在选择的直线斜率与两点连出的直线斜率大小关系发生变化时，a,b的相对排名才会改变

所以$n^2$处理出每两个点之间连线再进行极角排序，就可以保证每次只需要将当前枚举到的直线上两点swap一下就能保证对于下条直线点顺序的正确性

然后就可以愉快的二分了（

时间复杂度：直线排序$O(N^2logN)$+枚举直线和二分$O(N^2logN)$，可过

输出比较麻烦，因为点的顺序会变，所以还要拿一个pos数组记录当前点在第几。

//另：如果选择用向量叉积表示面积的话别忘了把三角形面积乘以2（我绝对不会告诉你我卡了好长时间的QAQ

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct hehe{//一结构体两用，表达点和向量通用（
	int x, y;
}a[2001];
struct haha{
	int a, b;
	hehe p;
}e[4000001];
int pos[2001], rk[2001];
bool cmp1(hehe x, hehe y)
{
	return x.x == y.x ? x.y < y.y : x.x < y.x;
}
bool cmp2(haha x, haha y)
{
	return x.p.x * y.p.y - x.p.y * y.p.x > 0;
}
hehe xl(hehe x, hehe y)
{
	hehe ret;
	ret.x = x.x - y.x;
	ret.y = x.y - y.y;
	return ret;
}
int cj(hehe x, hehe y)
{
	return x.x * y.y - x.y * y.x;
}
signed main()
{
	int n, cnt = 0, s;
	cin >> n >> s;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	sort(a + 1, a + n + 1, cmp1);
	s *= 2;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
		{
			hehe qwq;
			qwq.x = a[i].x - a[j].x;
			qwq.y = a[i].y - a[j].y;
			e[++cnt].a = j;
			e[cnt].b = i;
			e[cnt].p = qwq;
		}
	}
	sort(e + 1, e + cnt + 1, cmp2);
	for(int i = 1; i <= n; i++) rk[i] = pos[i] = i;
	for(int i = 1; i <= cnt; i++)
	{
		hehe p = e[i].p;
		int x = e[i].a, y = e[i].b;
		if(rk[x] > rk[y]) swap(x, y);
		int l = 1, r = rk[x] - 1;
		// cout << "qwq" << x << ' ' << y << ' ' << r << endl;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			int si = abs(cj(p, xl(a[pos[mid]], a[pos[rk[x]]])));
			// cout << si << ' ' << l << ' ' << r << endl;
			if(si == s)
			{
				cout << "Yes" << endl << a[x].x << ' ' << a[x].y << endl << a[y].x << ' ' << a[y].y << endl << a[pos[mid]].x << ' ' << a[pos[mid]].y;
				exit(0);
			}
			else if(si > s) l = mid + 1;
			else r = mid - 1;
		}
		swap(rk[x], rk[y]);
		swap(pos[rk[x]], pos[rk[y]]);
	}
	cout << "No" << endl;
	return 0;
}

```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定 $n$ 个平面上的点，求是否存在 $3$ 个点使得它们组成的三角形面积为 $S$。需要输出三个点的坐标。
>
> $n\le2000$。

## 解法

暴力做法：枚举 $3$ 个点，海伦公式判断面积是否相等。复杂度 $O(n^3)$。优化思路即为：对于先枚举的两个点 $A,B$ 组成的连线 $l$，那么第 $3$ 个点 $C$ 就要满足其到这条连线的距离为 $\cfrac{2m}{|l|}$。如果其余点与 $l$ 的距离有序，那么就可以 $O(\log n)$ 的复杂度二分了，分成在 $l$ 之上、之下两个部分。

考虑将所有点进行旋转，使 $l$ 与 $y$ 轴重合。这时候可以发现一个性质：

- 以 $l$ 为纵轴时，对于任意两个点 $X,Y$，它们的横坐标大小关系，只与原图中 $l$ 与 $AB$ 的斜率有关。

然后做法就出来了：先把 $n^2$ 条连线按照斜率从小到大排序，然后从小到大枚举，这样任意两点旋转后的横坐标大小关系恰好会变化一次。枚举连线的过程中每次交换两个端点，再在连线的两侧（正负）进行查找即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005;
#define ll long long
int n, a[maxn + 5];
ll m;
struct Point { 
    int id, x, y;
} p[maxn + 5];
struct Segment {
    int x, y;
    double k;
    bool operator< (const Segment &o) const { // 按照斜率
        return k < o.k; 
    }
} sid[maxn * maxn + 5];
bool cmp(const Point &A, const Point &B) { 
    return A.x < B.x; 
}
ll cal(const Point &u,const Point &v,const Point &w) { // 算出第 3 条边的长度
    return abs(1ll * (u.x - v.x) * (u.y - w.y) - 1ll * (u.x - w.x) * (u.y - v.y));
}
bool ok = false;
// 对于 l 进行左右两侧的二分。
void F1(int l, int r, const Point &A, const Point &B) {  
    while (l <= r) {
        int mid = l + r >> 1; 
        ll S = cal(p[mid], A, B);
        if (S == 2 * m) {
            printf("Yes\n%d %d\n%d %d\n%d %d\n", A.x, A.y, B.x, B.y, p[mid].x, p[mid].y);
            ok = true; return ;
        } else if (S < 2 * m) r = mid - 1;
        else l = mid + 1;
    }
}
void F2(int l, int r, const Point &A, const Point &B) {
    while(l <= r) {
        int mid = l + r >> 1; 
        ll S = cal(p[mid], A, B);
        if (S == 2 * m) {
            printf("Yes\n%d %d\n%d %d\n%d %d\n", A.x, A.y, B.x, B.y, p[mid].x, p[mid].y); 
            ok = true; return ;
        } else if (S < 2 * m) l = mid + 1;
        else r = mid - 1;
    }
}
int tot = 0;
int main() {
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; i ++)
        a[i] = p[i].id = i;
    for (int i = 1; i <= n; i ++)
        for (int j = i + 1; j <= n; ++j)
            sid[++ tot] = Segment{i, j, 1.0 * (p[j].y - p[i].y) / (p[j].x - p[i].x)};
    sort(sid + 1, sid + tot + 1); 
    for (int i = 1; i <= tot; i ++) {
        int mn = min(a[sid[i].x], a[sid[i].y]);
        int mx = max(a[sid[i].x], a[sid[i].y]); 
        swap(p[mn], p[mx]); swap(a[sid[i].x], a[sid[i].y]);
        F1(1, mn - 1, p[a[sid[i].x]], p[a[sid[i].y]]);
        if (ok) return 0;
        F2(mx + 1, n, p[a[sid[i].x]], p[a[sid[i].y]]);
        if (ok) return 0;
    }
    return puts("No"), 0;
}
```

---

## 作者：Presentation_Emitter (赞：0)

暴力寻点 $\Theta(n^3)$。把暴力过程改一下，枚举一条连线 $l$，然后找一个点到这条连线的距离为 $\dfrac{2m}{|l|}$。

因为如果所有点到线的距离有序（此处的距离带符号，点在线下方则符号为负）就能二分，所以维护点的顺序。

直接做是 $\Theta(n^3 \log n)$ 的。考虑对所有连线按斜率排序，然后有一个结论，每次枚举到一个新的连线时，相对顺序变化两个点（这里认为枚举过的点在距离相等时靠右的点比靠左的小），这两个点是之前那条连线的端点。

~~不严谨~~证明：$d_x<d_y \Leftrightarrow k_{x,y}>k_l$，枚举的是所有 $k_{x,y}$，故每次最多变换一种 $k_{x,y}$ 与 $k_l$ 的大小关系，然后保证没有三点共线，于是至多变化两个点（有三点共线也能做，反转区间即可）。

之后根据直线方程直接二分即可。时间复杂度 $\Theta(n^2 \log n)$。

可以先对点排序，之后每条连线的 $\Delta x$ 是非负的，处理的时候会方便一些。

Code:

```cpp
#define ll __int128
ll n,m,t,p[2005],inv[2005];
struct node{ll x,y;il bool opr<(cst node&_)cst{ret (x^_.x)?x<_.x:y<_.y;}}a[2005];
struct slope
{
	int ia,ib;
	il ll dx()cst{ret a[ib].x-a[ia].x;}
	il ll dy()cst{ret a[ib].y-a[ia].y;}
	il ll kc()cst{ret a[ib].x*a[ia].y-a[ia].x*a[ib].y;}
	il bool opr<(cst slope&_)cst{ret dy()*_.dx()<dx()*_.dy();}
}s[4000005];
il bool cmp(ll x,ll y){ret s[1].dx()*a[x].y-a[x].x*s[1].dy()<s[1].dx()*a[y].y-a[y].x*s[1].dy();}
il ll mySearch(ll ka,ll kb,ll kc)
{
	ll l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;ll val=ka*a[p[mid]].x+kb*a[p[mid]].y;
		if(val==kc)ret mid;
		if(val<kc)l=mid+1;else r=mid-1;
	}
	ret -1;
}
il void output(ll x,ll y,ll z)
{
	puts("Yes");
	prt(a[x].x,' ');prt(a[x].y);
	prt(a[y].x,' ');prt(a[y].y);
	prt(a[z].x,' ');prt(a[z].y);
}
int main()
{
	//file(triangle);
	n=rd();m=rd();for(int i=1;i<=n;++i)a[i].x=rd(),a[i].y=rd(),p[i]=i;
	sort(a+1,a+1+n);for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j)s[++t]=(slope){i,j};
	sort(s+1,s+1+t);sort(p+1,p+1+n,cmp);for(int i=1;i<=n;++i)inv[p[i]]=i;
	for(int i=1;i<=t;++i)
	{
		ll ka=-s[i].dy(),kb=s[i].dx(),kc=s[i].kc()+m+m,pos;
		pos=mySearch(ka,kb,kc);
		if(~pos){output(s[i].ia,s[i].ib,p[pos]);ret 0;}
		kc-=m+m;kc-=m+m;
		pos=mySearch(ka,kb,kc);
		if(~pos){output(s[i].ia,s[i].ib,p[pos]);ret 0;}
		swap(p[inv[s[i].ia]],p[inv[s[i].ib]]);
		swap(inv[s[i].ia],inv[s[i].ib]);
		//cerr<<s[i].dy()*1.0/s[i].dx()<<' '<<s[i].ia<<' '<<s[i].ib<<endl;
		//for(int i=1;i<=n;++i)cerr<<p[i]<<" \n"[i==n];
	}
	puts("No");
	ret 0;
}
```

有些人可能不会找点，这里补充一下：

海伦公式显然不适合，考虑使用向量叉乘。两个向量 $(x_1,y_1,0),(x_2,y_2,0)$ 叉乘的结果向量为 $(0,0,x_1y_2-x_2y_1)$，模长为两个向量形成的平行四边形的面积。叉乘满足以下规律：
- $\boldsymbol{a}\times\boldsymbol{b}=-\boldsymbol{b}\times\boldsymbol{a}$；
- $\boldsymbol{a}\times\boldsymbol{a}=\boldsymbol{0}$；
- $\boldsymbol{a}\times(\boldsymbol{b}+\boldsymbol{c})=\boldsymbol{a}\times\boldsymbol{b}+\boldsymbol{a}\times\boldsymbol{c}$。

设 $\overrightarrow{OA}=\boldsymbol{a},\overrightarrow{OB}=\boldsymbol{b},\overrightarrow{OC}=\boldsymbol{c}$，列式：

$$|(\boldsymbol{a}-\boldsymbol{b})\times(\boldsymbol{a}-\boldsymbol{c})|=2m$$
$$|\boldsymbol{a}\times\boldsymbol{a}-\boldsymbol{a}\times\boldsymbol{c}-\boldsymbol{b}\times\boldsymbol{a}+\boldsymbol{b}\times\boldsymbol{c}|=2m$$
$$|\boldsymbol{a}\times\boldsymbol{b}+\boldsymbol{c}\times(\boldsymbol{a}-\boldsymbol{b})|=2m$$

现在枚举的是 $\boldsymbol{a},\boldsymbol{b}$ 然后去找 $\boldsymbol{c}$。因为 $\boldsymbol{a},\boldsymbol{b}$ 都是二维的，所以叉出来的模就等于 $z$ 坐标。于是：

$$|x_ay_b-y_ax_b+x_c(y_a-y_b)-y_c(x_a-x_b)|=2m$$

之后拆绝对值，然后就能得到两条直线方程，然后二分时直接代坐标就行。

---

