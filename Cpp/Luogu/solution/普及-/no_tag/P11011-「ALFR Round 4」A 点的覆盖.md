# 「ALFR Round 4」A 点的覆盖

## 题目描述

在平面直角坐标系中，若一个点的横坐标和纵坐标均为整数，则我们称之为整数点。给定一个顶点均为整数点且各边与一条坐标轴平行的矩形 $A$ 和矩形内（可能在其边缘上）的 $n$ 个整数点 $p_1,p_2,p_3,\cdots,p_n$，请问 $A$ 有多少个子矩形满足：

- 顶点均为整数点；

- 四边均与一条坐标轴平行；

- 能全部覆盖（允许在边缘上） $p_1,p_2,p_3,\cdots,p_n$。

本题中矩阵长或宽可以为 $0$。

## 说明/提示

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $n\le10^2$，所有点的坐标小于 $10^2$ |
| $1$ | $20$ | 除 $A$ 的顶点外的所有点的横坐标相等 |
| $2$ | $60$ | - |

对于 $100\%$ 的数据，$1\le n\le10^6$，所有点的坐标为正整数且小于 $10^9$。

## 样例 #1

### 输入

```
3 1 5 6 1
2 3
2 4
4 2```

### 输出

```
24```

# 题解

## 作者：planifolia (赞：6)

## 题目大意

给定 $n$ 个点 $(x_i,y_i)$ 以及矩形 $A$ 的左上端点坐标 $(q_1,p_1)$ 和右下端点坐标 $(q_2,p_2)$，求矩形 $A$ 有几个子矩形可以覆盖这 $n$ 个点。

## 思路分析

对于不存在点在矩形 $A$ 之外的情况，符合要求的最小子矩形的左上端点坐标为 $(\min x,\max y)$，右下端点坐标为 $(\max x,\min y)$。

而符合要求的最大子矩形的左上端点坐标为 $(q_1,p_1)$，右下端点坐标为 $(q_2,p_2)$。

故可以使用乘法原理求得符合要求的子矩形数量：

$$(\min x-q_1+1)(p_1-\max y+1)(q_2-\max x+1)(\min y-p_2+1)$$

## 注意事项

- $(10^9)^2>2^{31}-1$，本题需要开 $\texttt{long long}$。

- 对于存在点在矩形 $A$ 之外的情况，需要特判输出 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int MOD=1e9+7;

int n,q1,p1,q2,p2;
int maxx,maxy;
int minx=INF,miny=INF;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q1>>p1>>q2>>p2;
    for(int i=1;i<=n;i++){
        int px,py;
        cin>>px>>py;
        maxx=max(maxx,px),maxy=max(maxy,py);
        minx=min(minx,px),miny=min(miny,py);
    }
    if(minx<q1||maxy>p1||maxx>q2||miny<p2){
        cout<<0;
        return 0;
    }
    cout<<(long long)(minx-q1+1)%MOD*(p1-maxy+1)%MOD*(q2-maxx+1)%MOD*(miny-p2+1)%MOD;
    return 0;
}
```

---

## 作者：2023gdgz01 (赞：3)

题目中说明了子矩形的必须四边均与一条坐标轴平行，所以确定左上端点和右下端点即可确定唯一的矩形。覆盖 $n$ 个点并不好做，所以先求出 $n$ 个点中最小的横坐标、最大的横坐标、最小的纵坐标、最大的纵坐标，即可确定最小可覆盖 $n$ 个点的矩形，称之为矩形 $B$。问题转化为覆盖矩形 $B$。接下来就很好做了，某一矩形要想覆盖矩形 $B$，则其左上端点必须在 $B$ 的左上端点的左上方，其右下端点必须在 $B$ 的右下端点的右下方，运用乘法原理即可。

代码如下：

```cpp
#include <cstdio>

int n;
long long x, y, ax, bx, ay, by, ans, mod = 1e9 + 7, minx = 1e9, maxx, miny = 1e9, maxy;

inline long long max(long long x, long long y) {
	if (x > y)
		return x;
	return y;
}

inline long long min(long long x, long long y) {
	if (x < y)
		return x;
	return y;
}

int main() {
	scanf("%d%lld%lld%lld%lld", &n, &ax, &ay, &bx, &by);
	for (register int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &x, &y);
		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
	}
	printf("%lld", (minx - ax + 1) * (ay - maxy + 1) % mod * (bx - maxx + 1) % mod * (miny - by + 1) % mod);
	return 0;
}
```

时间复杂度为 $O(n)$。[AC 链接](https://www.luogu.com.cn/record/174907936)

---

## 作者：_Supernova (赞：2)

### 一、题意简述。

给定一个矩形和 $n$ 个点，问有多少个子矩形能包含所有 $n$ 个点。矩形左上点为 $(lx,ly)$，右下点为 $(rx,ry)$。

### 二、思路分析。

对于这 $n$ 个点，我们记 $minl$ 表示最左边的位置，$maxr$ 表示最右边的位置，$maxu$ 表示最上边的位置，$mind$ 表示最下边的位置。

具体的，我们用结构体存储 $n$ 个点的信息。

```cpp
struct Point {
	int x, y;
} p[N];
```
则：
$minl$ 为所有 $x$ 的最小值；
$maxr$ 为所有 $x$ 的最大值；
$maxu$ 为所有 $y$ 的最大值；
$mind$ 为所有 $y$ 的最小值。

我们考虑答案贡献。
对于一个子矩形，记左边界为 $l$，右边界为 $r$，上边界为 $u$，下边界为 $d$。

则有 $minl\geq l \geq lx$，$rx\geq r \geq maxr$，$ly\geq u \geq maxu$，$mind\geq d \geq ry$。

于是计算出 $l$ 有 $a_1$ 种取值，$r$ 有 $a_2$ 种取值，$u$ 有 $a_3$ 种取值，$d$ 有 $a_4$ 种取值。

最终答案即为 $a_1 \times a_2 \times a_3 \times a_4$。

记得取模。

---

## 作者：savvsavsaasvav (赞：1)

# 思路
我们只需要算出矩阵左上角的坐标的最大值和右下角的坐标的最小值，这样我们就可以获得最小的矩形。

![思路图解](https://cdn.luogu.com.cn/upload/image_hosting/w4g5r16h.png)

这样我们只需要知道左上角和右下角的面积大小即可，图中蓝色区域。

任选左上角蓝色区域，再任选右下角蓝色区域。所以是乘法原理，相乘即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long//要开 long long。
using namespace std;
const ll Mod=1e9+7;
const int N=1e6+10;
int n,ax,ay,bx,by,x,y,mxx,mxy,mnx=INT_MAX,mny=INT_MAX;
ll calc(ll n){
	return max(0ll,n)%Mod;
}
int main(){
	scanf("%d%d%d%d%d",&n,&ax,&ay,&bx,&by);
	int mx=min(ax,bx),nx=max(ax,bx);
	int my=min(ay,by),ny=max(ay,by);
	ax=mx,ay=my,bx=nx,by=ny;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&x,&y);
		mxx=max(mxx,x),mxy=max(mxy,y);
		mnx=min(mnx,x),mny=min(mny,y);
	}
	ll s1=calc(mnx-ax+1)*calc(mny-ay+1)%Mod;//左上角合法面积。
	ll s2=calc(bx-mxx+1)*calc(by-mxy+1)%Mod;//右下角合法面积。
	printf("%lld",s1*s2%Mod);//别忘了取余。
}
```

---

## 作者：Lovely_Elaina (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/yirw0q5y.png)

在当前矩阵内，枚举上下左右四条边位置求方案数。根据乘法原理，不难发现答案数为 $a\times b\times c\times d$。

```cpp
#include <bits/stdc++.h>
#define int long long
// #define double long double
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define endl '\n' 
using namespace std;
typedef long long ll;
// const int eps = 1e-9;
const int P = 1e9+7;

int n,lx,ly,rx,ry;
int l,r,d,u;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
    
    // freopen("app.in","r",stdin);
    // freopen("app.out","w",stdout);
    
    cin >> n >> lx >> ly >> rx >> ry;

    d = l = 1e9+5;

    int x,y;
    while(n--){
        cin >> x >> y;
        r = max(r,x);
        l = min(l,x);
        u = max(u,y);
        d = min(d,y);
    }

    // cout << l << " " << r << " " << u << " " << d << endl;
    cout << (((((((l-lx+1)*(d-ry+1))%P)*(rx-r+1))%P)*(ly-u+1))%P) << endl;
	return 0; 
}
```

---

## 作者：TemplateClass (赞：1)

注意题目中提到的是平面直角坐标系的坐标，请分清其与二维数组的下标的区别。

---

以样例为例，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v054qdj1.png)

首先确定能包围这些点的最小矩形。

首先考虑该最小矩形的一边，例如左边。显然所有点的 $x$ 坐标都要 $\ge$ 该边所在的 $x$ 坐标。也就是左边所在的坐标要 $\le \min\left\{ x_i \right\}$。

同理可得：

- 上边所在的坐标要 $\le \max\left\{ y_i \right\}$。
- 下边所在的坐标要 $\ge \min\left\{ y_i \right\}$。
- 左边所在的坐标要 $\le \min\left\{ x_i \right\}$。
- 右边所在的坐标要 $\ge \max\left\{ x_i \right\}$。

既然是最小，那么这些不等号全部取等即可。写成代码就是：

```cpp
std::cin >> n >> x1 >> y1 >> x2 >> y2;

int up = y2, down = y1, left = x2, right = x1;
for(int i = 1; i <= n; ++i) {
	int x, y; std::cin >> x >> y;
	
	up = std::max(up, y);
	down = std::min(down, y);
	left = std::min(left, x);
	right = std::max(right, x);
}
```

如下图所示，红色矩形即为能包住这些点的最小矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/1x2kilud.png)

其中，$\mathrm{up} = 4$，$\mathrm{down} = 2$，$\mathrm{left} = 2$，$\mathrm{right} = 4$。

设矩形 $A$ 左上角的坐标为 $\left( x_1, y_1 \right)$，右下角的坐标为 $\left( x_2, y_2 \right)$。

接下来我们考虑一共有多少个矩形满足是 $A$ 的子矩形且包含所有的点的。

我们同样是仍然先考虑其中的一边，例如此处的右边。显然，由于题目要求这些矩形必须是 $A$ 的子矩形，所以右边所在的 $x$ 坐标必须 $\le x _ 2$。又由于必须要包含所有的点，所以该边所在的 $x$ 坐标不能够小于最小矩阵的右边所在的 $x$ 坐标，即变量 $\mathrm{right}$。由此我们得到符合要求的矩阵的右边所在的 $x$ 坐标必须在闭区间 $\left[ \mathrm{right}, x_2 \right]$ 之间。

同理，我们得到：

- 矩阵的上边所在的 $y$ 坐标必须在闭区间 $\left[ \mathrm{up}, y_1 \right]$ 之间。
- 矩阵的下边所在的 $y$ 坐标必须在闭区间 $\left[ y_2, \mathrm{down} \right]$ 之间。
- 矩阵的左边所在的 $x$ 坐标必须在闭区间 $\left[ x_1, \mathrm{left} \right]$ 之间。
- 矩阵的右边所在的 $x$ 坐标必须在闭区间 $\left[ \mathrm{right}, x_2 \right]$ 之间。

（当左右端点全是整数时，闭区间 $[a, b]$ 之间的所有整数数量为 $b - a + 1$。）

由于每个边的选择都是一个步骤而并非一个独立的事件，因而适用乘法原理。

所以计算答案的代码即为：

```cpp
unsigned long long ans = 1;
ans = ans * (y1 - up + 1) % MOD;
ans = ans * (down - y2 + 1) % MOD;
ans = ans * (left - x1 + 1) % MOD;
ans = ans * (x2 - right + 1) % MOD;

std::cout << ans;
```

AC 代码就是把上边给出过的代码拼起来，这里就不放了。

---

## 作者：_Weslie_ (赞：0)

你说得对，但是红绿绿紫。

## Idea

怎么样才能在一个以 $(a,b)$ 为左上，$(c,d)$ 为左下的顶点组成的矩形中存在点 $(e,f)$ 呢？显然要满足 $a\le e\le c$ 且 $d\le f\le b$。

怎么样才能在一个以 $(a,b)$ 为左上，$(c,d)$ 为左下的顶点组成的矩形中存在点 $(e,f)$ 和 $(g,h)$ 呢？显然要满足 $a\le \min(e,g)\le \max(e,g)\le c$ 且 $d\le \min(f,h)\le \max(f,h)\le b$。

然后对于本题的每一个点都有这样的条件。

推广一下结论：要满足在一个以 $(a,b)$ 为左上，$(c,d)$ 为左下的顶点组成的矩形中存在点 $(x_1,y_1)(x_2,y_2)\cdots(x_n,y_n)$，则要有 $a\le\min\{x\}\le \max\{x\}\le c$ 且 $d\le \min\{y\}\le \max\{y\}\le b$。

然后因为还要满足以 $(a,b)$ 为左上，$(c,d)$ 为左下的顶点组成的矩形是以 $(p,q)$ 为左上，$(s,t)$ 为左下的顶点组成的矩形的子矩形（其实就是题意），所以要求变为 $p\le a\le\min\{x\}\le \max\{x\}\le c\le s$ 且 $t\le d\le \min\{y\}\le \max\{y\}\le b\le q$。

不难发现 $a$ 的有 $\min\{x\}-p+1$ 种，$b$ 有 $q-\max\{y\}+1$ 种，$c$ 有 $s-\max\{x\}+1$ 种，$d$ 有 $\min\{y\}-t+1$ 种取值，由乘法原理把它们相乘就是答案。

## Code

```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,e,f,g,h;
long long ans;
int main(){
	scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);
	e=-2147483647;
	f=2147483647;
	g=-2147483647;
	h=2147483647;
	for(int i=1,j,k;i<=n;i++){
		scanf("%d%d",&j,&k);
		e=max(e,j);
		f=min(f,j);
		g=max(g,k);
		h=min(h,k);
	}
	ans=1ll*(c-e+1)*(f-a+1)%1000000007;
	ans=ans*(b-g+1)%1000000007;
	ans=ans*(h-d+1)%1000000007;
	printf("%lld\n",ans);
	return 0;
}
````

---

## 作者：nightwatch.ryan (赞：0)

### 思路
设 $A$ 的左上端点的坐标是 $(x1, y1)$，右下端点的坐标是 $(x2, y2)$。

我们要求的是包含 $n$ 个点的 $A$ 的子矩形个数。我们先求出最小的包含了 $n$ 个点的子矩形，称这个矩形是 $B$。

下面设 $xmin$ 是所有点中最小的横坐标，$xmax$ 是所有点中最大的横坐标，$ymin$ 是所有点中最小的纵坐标，$ymax$ 是所有点中最大的纵坐标。

显然，$B$ 的左下角是 $(xmin, ymin)$，右上角是 $(xmax, ymax)$，因为要将 $n$ 个点全部包含进去。

到现在，答案已经很明显了，就是求 $A$ 的子矩形中有多少个包含 $B$。

- 计算矩形 $A$ 的左边界到 $B$ 的左边界之间的距离，所有可能的子矩形左边界的数量。
- 计算矩形 $A$ 的右边界到 $B$ 的右边界之间的距离，所有可能的子矩形右边界的数量。
- 计算矩形 $A$ 的上边界到 $B$ 的上边界之间的距离，所有可能的子矩形上边界的数量。
- 计算矩形 $A$ 的下边界到 $B$ 的下边界之间的距离，所有可能的子矩形下边界的数量。

将这四个式子的结果乘起来就是答案。记得对 $10^9 + 7$ 取模。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

#define P(i, a, b) for(int i = a; i <= b; i++)
#define Q(i, a, b) for(int i = a; i >= b; i--)
const int maxn = 100005;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

mt19937 rnd(chrono::duration_cast<chrono::nanoseconds>
           (chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

signed main(){

    cin.tie(0)->sync_with_stdio(0);
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    int xmin = 1e9, xmax = 0, ymin = 1e9, ymax = 0;
    P(i, 1, n){
        int x, y;
        cin >> x >> y;
        xmin = min(xmin, x), xmax = max(xmax, x);
        ymin = min(ymin, y), ymax = max(ymax, y);
    }
    int ans = (xmin - x1 + 1) % mod *
              (y1 - ymax + 1) % mod *
              (x2 - xmax + 1) % mod *
              (ymin - y2 + 1) % mod;
    cout << ans << endl;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

题意：给 $n$ 个点，再给一个包含这些点的矩形，求矩形中有多少子矩形能包含所有 $n$ 个点。

很简单。输入 $n$ 个点时记录这四个东西：横坐标最小值、横坐标最大值，纵坐标最小值，纵坐标最大值。然后对于每一个方向（上、下、左、右）都可以从给定的矩形边界到这四个东西中对应的一个方向。举例：如果矩形左边横坐标为 $X$，而 $n$ 个点横坐标最小值为 $x$，那么这个方向上能选择的边的个数就是 $X-x+1$ 个。把四个方向的答案乘起来就是最终答案。
```cpp
zuo=you=shang=xia=M;
cin>>n>>Ashangx>>Ashangy>>Axiax>>Axiay;
for(int i=1;i<=n;i++){
  cin>>x>>y;
  zuo=min(zuo,x-Ashangx);
  you=min(you,Axiax-x);
  shang=min(shang,Ashangy-y);
  xia=min(xia,y-Axiay);
}
cout<<(zuo+1)%M*(you+1)%M*(shang+1)%M*(xia+1)%M;
```

---

## 作者：jiayixuan1205 (赞：0)

## 题解：P11011 「ALFR Round 4」A 点的覆盖
### 题意
给出一个矩形，$n$ 个点，询问有多少个子矩形能包含所有的点。
### 分析
首先，我们可以发现，要包含住所有的点，只需要包含住横坐标最大的，横坐标最小的，纵坐标最大的和纵坐标最小的这四个位置即可，因此，我们可以用四个变量 $\text{minx}$ , $\text{miny}$ , $\text{maxx}$ , $\text{maxy}$ 来记录这四个量，输入的时候就可以顺带进行掉这步操作。

然后，我们发现，我们现在获得了一个最小的满足条件的矩形，那么其余满足条件的都是在它的基础上进行扩展，容易想到，扩展只有四个方向：上，下，左，右。根据题中给的条件，我们可以考虑为将子矩形在给定范围内向左上方和右下方拉伸。算出最大可达到的距离，运用乘法原理即可。
### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 1e9+7;
const int inf = 0x7f7f7f7f;
int n,a,b,c,d,x,y,minx,miny,maxx,maxy,ans;

signed main()
{
    cin>>n>>a>>b>>c>>d;
	minx=miny=inf;
    for(int i=1;i<=n;i++) 
    {
        cin>>x>>y;
        minx=min(minx,x);
		maxx=max(maxx,x);
        miny=min(miny,y);
		maxy=max(maxy,y);//记录关键的四个点 
    }
    cout<<(minx-a+1)*(c-maxx+1)%mod*(miny-d+1)%mod*(b-maxy+1)%mod<<endl;//乘法原理 
    return 0;
}
```

---

## 作者：jjy2023 (赞：0)

# P11011 「ALFR Round 4」A 点的覆盖
觉得评入门低估了这道题，~~至少我在比赛时没做出来~~。
## Description：
给你一个矩形，左上角的点为 $(x_1,y_1)$，右下角的点为 $(x_2,y_2)$，再给你 $n$ 个点，求顶点为整数点、四条边均与一条坐标轴平行且可以覆盖这 $n$ 个点的矩形个数。
## Solution：
先求出这 $n$ 个点中最小的横坐标、最大的横坐标、最小的纵坐标、最大的纵坐标，确定可覆盖这 $n$ 个点的最小矩形，称其为 $A$。因为要覆盖 $n$ 个点，所以必须覆盖矩形 $A$，那么其的左上端点要位于 $A$ 的左上方，右下端点要位于 $A$ 的右下方，在用乘法原理算出个数即可。时间复杂度为 $O(n)$。
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,x,y,ax,bx,ay,by,ans,minx=1e9,maxx=0,miny=1e9,maxy=0;
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>ax>>ay>>bx>>by;
	for(int i=1;i<=n;i++) 
	{
		cin>>x>>y;
		minx=min(minx,x),maxx=max(maxx,x),miny=min(miny,y),maxy=max(maxy,y);
	}
	int gs=(minx-ax+1)*(ay-maxy+1)%mod*(bx-maxx+1)%mod*(miny-by+1)%mod;
	cout<<gs;
	return 0;
}
```

---

## 作者：lilong (赞：0)

首先注意到题目给定的矩形以及要求的子矩形的**顶点坐标均为整数**，**且每条边都平行于一条坐标轴**。可以得知无需考虑矩形旋转一定角度的情况，接下来就不难了。

一个子矩形要把所有点覆盖，则只需要把**最小、最大的横、纵坐标**覆盖即可（显然，其他横、纵坐标在两者之间，因此一定能覆盖）。在此基础上，每条边可以向外延伸一定长度，但是不能超过给定的矩形，因此可以计算出每条边的可伸长量，根据乘法原理，四条边的可伸长量的乘积即为答案。

时间复杂度 $O(n)$，注意乘法时要及时取模防止溢出。


```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define MOD 1000000007

using namespace std;

int n,x1,y1,x2,y2,lx,rx,ly,ry,a,b;

signed main()
{
	cin >> n >> x1 >> y1 >> x2 >> y2;
	cin >> a >> b;
	lx = rx = a;
	ly = ry = b;
	for( int i = 2 ; i <= n ; i ++ )
	{
		cin >> a >> b;
		lx = min( lx , a );
		rx = max( rx , a );
		ly = min( ly , b );
		ry = max( ry , b );
	}
	cout << max( lx - x1 + 1 , 0ll ) * max( x2 - rx + 1 , 0ll ) % MOD * max( ly - y2 + 1 , 0ll ) % MOD * max( y1 - ry + 1 , 0ll ) % MOD;
//与 0 取 max 能够判掉某个坐标的极值超出矩形范围的情况。
	return 0;
}
```

---

