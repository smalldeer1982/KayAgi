# [ABC225E] フ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc225/tasks/abc225_e

二次元平面上の第一象限上に $ N $ 個のフの字があります。

$ i\ (1\ \leq\ i\ \leq\ N) $ 個目のフの字は、$ (x_i-1,y_i) $ と $ (x_i,y_i) $ を結ぶ線分と $ (x_i,y_i-1) $ と $ (x_i,y_i) $ を結ぶ線分の $ 2 $ つを組み合わせた図形です。

あなたは、$ N $ 個のフの字から $ 0 $ 個以上を選び、削除することができます。

適切に削除するフの字を選んだとき、原点から全体が見えるフの字の個数は最大でいくつになりますか？

ここで、原点からあるフの字（便宜上 $ i $ 個目のフの字とする）の全体が見える必要十分条件は、以下の通りです。

- 原点、$ (x_i-1,y_i) $、$ (x_i,y_i) $、$ (x_i,y_i-1) $ の $ 4 $ 点を頂点とする四角形の内部（境界を除く）と他のフの字が共通部分を持たない。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i,y_i\ \leq\ 10^9 $
- $ (x_i,y_i)\ \neq\ (x_j,y_j)\ (i\ \neq\ j) $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 個目のフの字を削除したとき原点からは $ 2 $ 個目のフの字と $ 3 $ 個目のフの字の $ 2 $ つが見えるようになり、これが最大です。 $ 1 $ つのフの字も削除しない場合、原点からは $ 1 $ 個目のフの字のみしか見えません。

### Sample Explanation 2

すべてのフの字を削除せずに残すのが最善です。

## 样例 #1

### 输入

```
3
1 1
2 1
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
10
414598724 87552841
252911401 309688555
623249116 421714323
605059493 227199170
410455266 373748111
861647548 916369023
527772558 682124751
356101507 249887028
292258775 110762985
850583108 796044319```

### 输出

```
10```

# 题解

## 作者：Symbolize (赞：2)

# $\tt{Solution}$
首先我们需要做一下问题转化，非常容易发现能被原点直接看到，就意味着以 $(0,0),(x,y-1),(x,y),(x-1,y)$ 为顶点的四边形中不存在别的图形，所以我们可以将问题装化为、以原点为顶点的角的覆盖问题，决定角的是两条线段的斜率，所以可以根据斜率排序，然后使用线段覆盖的方法进行求解。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int n,ans;
struct node
{
    int x,y;
	node(int a=0,int b=0){x=a,y=b;}
	bool operator<(const node &k)const{return x*k.y-y*k.x>0;}
	bool operator<=(const node &k)const{return x*k.y-y*k.x>=0;}
};
pair<node,node> a[N];
signed main()
{
	cin>>n;
	rep1(i,1,n)
	{
	    int x, y;
		cin>>x>>y;
		a[i]=make_pair(node(x-1,y),node(x,y-1));
	}
	sort(a+1,a+1+n);
	node last;
	rep1(i,1,n)
	{
		if(last<=a[i].y) 
		{
		    ++ans;
		    last=a[i].x;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：WaterSun (赞：2)

# 思路

对于每一个 `7`，我们都可以抽象为这样一个图形：

![](https://cdn.luogu.com.cn/upload/image_hosting/44ywm62c.png)

如果有两个 `7`，无论它是否有重合部分，红色部分是不需要判断的，只需要看绿色的部分。

因此，我们的问题就简化为了三角形，而不是四边形。

对于所有的 `7`，都有一个公共顶点：$(0,0)$ 点。

所以，我们可以引出一个叫斜率的概念来判断这些三角形是否有重合部分。

这里我们定义斜率为 $y$ 坐标与 $x$ 坐标的比值。

对于这道题，我们可以先看一下[P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)。

我们可以将这道题的三角形的斜率类比成线段，将绿色三角形的上面的那条边看做线段的左端点，下面的那条边看做线段的右端点。

然后，我们直接按照那题的贪心方法搞就行了。

我们判断两条边是否相交，我们直接判断斜率即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,l,ans;

struct node{
	int x;
	int y;
	int xx;
	int yy;
	bool operator <(const node &t) const{
		return yy * t.xx < t.yy * xx;//判断斜率，原式为：yy / xx < t.yy / t.xx，这里为了避免精度问题，通过移项将除法改变为乘法 
	}
}arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		int a,b;
		a = read();
		b = read();
		arr[i] = {a,b - 1,a - 1,b};//存储两个点的坐标 
	}
	sort(arr + 1,arr + 1 + n);//排序 
	for (re int i = 1;i <= n;i++){
		if (arr[i].y * arr[l].xx >= arr[l].yy * arr[i].x){//判断两个角是否有相交 
			ans++;//更新
			l = i;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wqc2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc225_e)

[题目传送门(AT)](https://atcoder.jp/contests/abc225/tasks/abc225_e)

### 题意
给你 $n$ 个 $7$，你可以删掉任意个 $7$，问你从原点最多可以看到多少个 $7$。

注：$7$ 长这样
![7](https://cdn.luogu.com.cn/upload/image_hosting/gexrlq0h.png)

### 思路
我们可以注意到每一个 $7$ 有一个自己的范围，如下图：

![例子](https://cdn.luogu.com.cn/upload/image_hosting/ptmpup5x.png)

我们发现，如果一个 $7$ 可以被看到，它的范围里是不能有其他的，若把它的范围看作一个区间，这道题就变成了一道简单的区间覆盖问题，利用贪心解决即可。

还有，在实现过程中要注意精度问题。

### 代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
using namespace std;
const int maxn = 200010;
const int inf = 1e9;
//unsigned long long 
//cout << fixed << setprecision(3)
//cout << setw(5) << 
//continue
struct S{
	int x, y, l, r;
}a[maxn];
struct S1{
	int id;
	bool p;
	int x, y;
}f[maxn * 2];
bool cmp(S1 a, S1 b){
	int sum1 = a.y * b.x, sum2 = b.y * a.x;
	if(sum1 != sum2) return sum1 > sum2;
	else {
		if(a.id == b.id) return a.p > b.p;
		return a.p < b.p;
	}
}

/*
y1 / x1
= y1 * x2
y2 / x2
= y2 * x1


*/
bool cmp1(S a, S b){
	if(a.l != b.l) return a.l < b.l;
	return a.r < b.r;
} 
bool vis[maxn];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int n, cnt = 0;
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i].x >> a[i].y;
		cnt++;
		f[cnt].x = a[i].x - 1;
		f[cnt].y = a[i].y;
		f[cnt].id = i;
		f[cnt].p = 1;
		cnt++;
		f[cnt].x = a[i].x;
		f[cnt].y = a[i].y - 1;
		f[cnt].id = i;
	}
	sort(f + 1, f + 1 + cnt, cmp);
	for(int i = 1;i <= cnt;i++){
		if(f[i].p) a[f[i].id].l = i;
		else a[f[i].id].r = i;
	}
	sort(a + 1, a + 1 + n, cmp1);
	int old = 0, ans = 0;
	for(int i = 1;i <= n;i++){
		//cout << i << ' ' << a[i].l << ' ' << a[i].r << endl;
		if(old < a[i].l){
			old = a[i].r;
			ans++;
		}
		if(a[i].r < old){
			old = a[i].r;
		}
	}
	cout << ans;
    return 0;
}
/*
6
1 3
2 4
3 3
4 2
4 4
6 1
*/	
```
感谢阅读。

---

## 作者：DengDuck (赞：1)

考虑两个四边形有重合部分的原因。

根据简单的一次函数知识不难得知，若两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 组成的四边形满足两条边的斜率组成的区间有交，那么两个四边形有重合部分。

那么这就是一个区间覆盖问题，求最多选多少个无交的区间。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL N = 1e6;
const LL inf = 1e18;
struct num 
{
    LL a, b;
} t = { 0, 1 };
struct node 
{
    num l, r;
} a[N];
LL n, ans, x, y;
bool comp(num a, num b) 
{ 
	return a.a * b.b <= b.a * a.b; 
}
bool comp2(num a, num b) 
{ 
	return a.a * b.b < b.a * a.b; 
}
bool cmp(node x, node y) 
{
    return comp2(x.r, y.r);
}
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) 
    {
        scanf("%lld%lld", &x, &y);
        a[i].l = { y - 1, x }, a[i].r = { y, x - 1 };
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) 
    {
        if (comp(t, a[i].l))t = a[i].r, ans++;
    }
    printf("%lld", ans);
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

在平面直角坐标系上有 $n$ 个 7，第 $i$ 个 7 被定义为连接 $(x_i-1,y_i)$ 与 $(x_i,y_i)$，以及 $(x_i,y_i-1)$ 与 $(x_i,y_i)$ 的两条线段。

现在让你删掉当中的一些 7，使得可以从原点完全看到所有的 7，问你最少需要删掉多少个。

完全看到指在 $(0,0)$，$(x_i-1,y_i)$，$(x_i,y_i)$，$(x_i,y_i-1)$ 四个点组成的四边形内部，不存在其它的 7。

**解法分析**

首先可以发现，一个 7 能否被看到，取决于由 $(x_i-1,y_i)$，$(x_i,y_i-1)$，$(0,0)$ 组成的三角形内部是否被其他三角形覆盖。

因为所有的三角形都存在一个公共点 $(0,0)$，所以可以知道，当两个三角形以原点为顶点的角重叠时，两个三角形也会重叠。

问题就转化成了：给定 $n$ 个以原点为顶点的角，选出当中的一些角使得角两两不重叠，问你最多可以选出多少个。

利用三角函数，你可以算出每个角的两条边与坐标轴的夹角。那么就可以以与坐标轴的两个夹角为一个区间，将问题转化为线段覆盖问题。

线段覆盖问题可以参考 [线段覆盖](https://www.luogu.com.cn/problem/P1803)。

**Code**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db long double
using namespace std;
ll n,ans,t;
struct node{db l,r;}a[200005];
bool cmp(node a,node b){return a.r<b.r;}
db f(db x,db y){//计算与 x 轴的夹角
	if(x==0) return 90.0;
	return atan((db)(1.0)*y/x);
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		a[i].l=f(x,y-1);
		a[i].r=f(x-1,y);
	}
	sort(a+1,a+n+1,cmp);
	for(ll i=1;i<=n;i++){//线段覆盖
		if(t==0||a[i].l>=a[t].r) t=i,ans++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

### 题意
在平面直角坐标系上有 $n$ 个 7，第 $i$ 个 7 被定义为连接 $(x_i-1,y_i)$ 与 $(x_i,y_i)$，以及 $(x_i,y_i-1)$ 与 $(x_i,y_i)$ 的两条线段。现在你能删掉任意个 7，求你最多能保留多少个 7，使得剩下的 7 都是能在原点被完全看到的。

第 $i$ 个 7 是能在原点被完全看到的定义为以 $(0,0),(x_i,y_i),(x_i-1,y_i),(x_i,y_i-1)$ 这四个点为顶点组成的四边形的内部（不包括边界）没有其他的 7。
### 思路
首先可以发现，一个 7 是否能在原点被完全看到，取决于以点 $A(x_i-1,y_i)$ 与点 $B(x_i,y_i-1)$ 以及原点 $O$ 组成的 $\angle{AOB}$ 内部是否有其他的 7。为什么与 $(x_i,y_i)$ 无关？因为坐标都是整数，即使碰到了 $(x_i,y_i)$ 也只算做边界。

然后这道题就可以变成：

给你 $n$ 个以原点为顶点的角，问你最多能选出多少个互不重叠的角。

然后我们看到了 [P1803](https://www.luogu.com.cn/problem/P1803)，考虑以相似的算法解决。

以 $n$ 个角的同一边为第一关键字，另一边为第二关键字，按顺时针（或逆时针）排序，按序寻找符合不重合的要求的角即可。

时间复杂度 $\mathcal{O}(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
struct Vector{
	ll x,y;
	Vector(ll _x=0,ll _y=0){
		x=_x,y=_y;
	}
	bool operator<(const Vector &o)const{ //利用叉积判断顺时针还是逆时针还是共线 
		return x*o.y-y*o.x>0;
	}
	bool operator<=(const Vector &o)const{
		return x*o.y-y*o.x>=0;
	}
};
ll n,ans;
pair<Vector,Vector> a[maxn];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	ll x,y;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		a[i]=make_pair(Vector(x-1,y),Vector(x,y-1));
	}
	sort(a+1,a+1+n);
	Vector last;
	for(int i=1;i<=n;i++){
		if(last<=a[i].second) ans++,last=a[i].first;
	}
	cout<<ans;
	return 0;
}
```


---

