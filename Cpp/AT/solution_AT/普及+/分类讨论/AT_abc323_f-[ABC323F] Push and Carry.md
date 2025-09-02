# [ABC323F] Push and Carry

## 题目描述

在坐标平面上有高桥君和一个行李。

高桥君现在位于 $(X_A, Y_A)$，行李位于 $(X_B, Y_B)$。高桥君想要把行李运送到 $(X_C, Y_C)$。

当高桥君处于 $(x, y)$ 时，每次行动可以选择以下任意一种移动方式：

- 移动到 $(x+1, y)$。如果移动前行李正好在 $(x+1, y)$，则行李会被推到 $(x+2, y)$。
- 移动到 $(x-1, y)$。如果移动前行李正好在 $(x-1, y)$，则行李会被推到 $(x-2, y)$。
- 移动到 $(x, y+1)$。如果移动前行李正好在 $(x, y+1)$，则行李会被推到 $(x, y+2)$。
- 移动到 $(x, y-1)$。如果移动前行李正好在 $(x, y-1)$，则行李会被推到 $(x, y-2)$。

请你求出将行李移动到 $(X_C, Y_C)$ 所需的最小行动次数。

## 说明/提示

## 限制条件

- $-10^{17} \leq X_A, Y_A, X_B, Y_B, X_C, Y_C \leq 10^{17}$
- $(X_A, Y_A) \neq (X_B, Y_B)$
- $(X_B, Y_B) \neq (X_C, Y_C)$
- 输入均为整数

## 样例解释 1

高桥君可以按如下方式在 $9$ 步内将行李运送到 $(0, 5)$：

- 移动到 $(2, 2)$。
- 移动到 $(3, 2)$。
- 移动到 $(3, 3)$。行李被推到 $(3, 4)$。
- 移动到 $(3, 4)$。行李被推到 $(3, 5)$。
- 移动到 $(4, 4)$。
- 移动到 $(4, 5)$。
- 移动到 $(3, 5)$。行李被推到 $(2, 5)$。
- 移动到 $(2, 5)$。行李被推到 $(1, 5)$。
- 移动到 $(1, 5)$。行李被推到 $(0, 5)$。

无法在 $8$ 步或更少的步数内将行李运送到 $(0, 5)$，因此输出 $9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 2 3 3 0 5```

### 输出

```
9```

## 样例 #2

### 输入

```
0 0 1 0 -1 0```

### 输出

```
6```

## 样例 #3

### 输入

```
-100000000000000000 -100000000000000000 100000000000000000 100000000000000000 -100000000000000000 -100000000000000000```

### 输出

```
800000000000000003```

# 题解

## 作者：robertuu (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc323_f)

简单的无障碍推箱子问题。赛时 $15$ 分钟秒了，发现洛谷上的大佬题解居然全是八种甚至十六种的大分讨，我就来了个三种的。

显然，把箱子调头是无意义的，箱子走的肯定是距离一定是 $(X_B,Y_B)$ 和 $(X_C,Y_C)$ 曼哈顿距离。

如果 $(X_B,Y_B)$ 和 $(X_C,Y_C)$ 不在同一条坐标轴上，人就需要花两步才能从横向推箱子变为纵向推箱子。

由于先横向和先纵向人初始需要去推箱子的位置不同。可以通过变量 $X$ 和 $Y$ 来保存目标点是在当前点的左或右、前或后，其实也是指示人应该站在性子的哪边推。

$X = -1$ 表示目标点在当前点的下方。

$X = 1$ 表示目标点在当前点的上方。

$Y = -1$ 表示目标点在当前点的右侧。

$Y = 1$ 表示目标点在当前点的左侧。

之后要处理的就是走到出发点（开始推箱子的点）。由于不能从箱子上走过，所以如果出发点、人、箱子横坐标或纵坐标一致，并且箱子在人和出发点之间，人就需要多走 $2$ 步绕开箱子，其他情况就是曼哈顿距离。可以通过函数完成。

```cpp
long long dist(long long xa,long long ya,long long xb,long long yb,long long xc,long long yc)
{
	long long res = abs(xa-xb)+abs(ya-yb);
	if(xa == xb && xb == xc && (ya < yc && yb > yc || ya > yc && yb < yc)) res += 2;
	if(ya == yb && yb == yc && (xa < xc && xb > xc || xa > xc && xb < xc)) res += 2;
	return res;
}
```

所以代码也很好写，分成横、纵、横纵都有就行了。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dist(long long xa,long long ya,long long xb,long long yb,long long xc,long long yc)
{
	long long res = abs(xa-xb)+abs(ya-yb);
	if(xa == xb && xb == xc && (ya < yc && yb > yc || ya > yc && yb < yc)) res += 2;
	if(ya == yb && yb == yc && (xa < xc && xb > xc || xa > xc && xb < xc)) res += 2;
	return res;
}
int main()
{
	long long xa,ya,xb,yb,xc,yc;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	int X = 0,Y = 0;
	if(xc > xb) X = -1;
	if(xc < xb) X = 1;
	if(yc > yb) Y = -1;
	if(yc < yb) Y = 1;
	if(X == 0) cout << dist(xa,ya,xb,yb+Y,xb,yb)+abs(yb-yc);
	else if(Y == 0) cout << dist(xa,ya,xb+X,yb,xb,yb)+abs(xb-xc);
	else cout << min(dist(xa,ya,xb,yb+Y,xb,yb),dist(xa,ya,xb+X,yb,xb,yb))+abs(yb-yc)+abs(xb-xc)+2;
	return 0;
}
```


---

## 作者：lottle1212 (赞：2)

# [Push and Carry](https://www.luogu.com.cn/problem/AT_abc323_f) 题解

## 题目大意

人在 $(x_1, y_1)$，物品在 $(x_2, y_2)$，要把它推到 $(x_3, y_3)$ 的位置，求最小移动次数。

推的定义：人在 $(x, y)$，物品在其相邻位置，推即人移动到物品位置，物品向同样位置移动一格。

## 解题思路

我们可以想，将物品移动到终点位置，可以先让人走到物品背后，推到同一行或同一列之后，转个身，推到终点就可以了。

当然，我们可以先推到同一列，也可以先推到同一行，两种情况都求出答案，求最小即可。

我们还需要考虑一种特殊情况，就比如人要移到物品背后时，最短路径要经过物品，这时我们就需要多走 $2$ 步，绕过去。

细节注意一下，代码还是比较简单的。

代码在[这里](https://atcoder.jp/contests/abc323/submissions/46650569)。

---

## 作者：not_clever_syl (赞：2)

小分讨题。

以下 $dis(a,b)=|X_a-X_b|+|Y_a-Y_b|$。

当货物和目的地连成的直线平行于X轴或Y轴时，高桥只需要走到货物的另一面（开始推动的点），然后推过去就好了，答案为 $dis(a,b)+1+dis(b,c)$。

否则一定有两个货物旁边的点，使高桥走过去一定是较优的。

然后我们可以发现，无论高桥走到哪个点，之后都需要 $dis(b,c)+2$ 步才能推到终点。

答案就是高桥到那两个点的代价取 $\min$ 加上 $dis(b,c)+2$。

小细节：

高桥走到货物旁边开始推动的点的路如果被阻挡了走过去的代价要 $+2$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
long long dis(long long x,long long y,long long tx,long long ty){
	return abs(x-tx)+abs(y-ty);
}
long long gdis(long long x,long long y,long long tx,long long ty,long long xb,long long yb){
	bool fl=false;
	if(x==tx&&xb==x&&min(y,ty)<=yb&&yb<=max(y,ty))fl=true;
	if(y==ty&&yb==y&&min(x,tx)<=xb&&xb<=max(x,tx))fl=true;//细节：可能被货物阻挡
	return abs(x-tx)+abs(y-ty)+(fl?2:0);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	long long xa,ya,xb,yb,xc,yc;
	cin>>xa>>ya>>xb>>yb>>xc>>yc;
	if(xb==xc){
		auto ryb=yb;
		if(yb<yc)--yb;
		else ++yb;
		auto ans=gdis(xa,ya,xb,yb,xb,ryb)+dis(xb,yb,xc,yc)-1;
		cout<<ans;
		return 0;
	}
	if(yb==yc){
		auto rxb=xb;
		if(xb<xc)--xb;
		else ++xb;
		auto ans=gdis(xa,ya,xb,yb,rxb,yb)+dis(xb,yb,xc,yc)-1;
		cout<<ans;
		return 0;
	}
	long long ans1,ans2;
	if(xb<xc)ans1=gdis(xa,ya,xb-1,yb,xb,yb);
	else     ans1=gdis(xa,ya,xb+1,yb,xb,yb);
	if(yb<yc)ans2=gdis(xa,ya,xb,yb-1,xb,yb);
	else     ans2=gdis(xa,ya,xb,yb+1,xb,yb);
	auto t=dis(xb,yb,xc,yc)+2;
	cout<<min(ans1,ans2)+t;
}
```

---

## 作者：无钩七不改名 (赞：2)

我们可以建立一个以点 $B$ 为原点的平面直角坐标系，而 $A,C$ 的坐标为原坐标与 $B$ 点的相对位置。即 $A(x,y)=(X_A-X_B,Y_A-Y_B),B(0,0),C(x,y)=(X_C-X_B,Y_C-Y_B)$。

那么点 $A$ 有三种情况：在横轴上、在纵轴上、在四个象限中。

我们可以直接通过坐标判断情况，分类讨论。

（注：下图中以红线表示单独走，绿线表示推着箱子走。每个很小的段长度为 $1$，可以理解成围着箱子转弯，需要多花费 $2$ 的路程。需要走的长度即为每一段长度之和。）

### 一、在横轴上

以 $A$ 在负半轴为例，一共有八种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/tgojl4r5.png)

$A$ 在正半轴上同理，左右翻转一下,按照在负半轴的情况处理即可（即三点横坐标取反）。

### 二、在纵轴上

其实就是情况一顺时针/逆时针旋转 $90$ 度可以得到，也是可以通过坐标变换得到的。改变坐标后直接按照情况一处理。

### 三、在象限中

以 $A$ 在第二象限为例，八种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/04t9bd6h.png)

第三象限是第二象限上下翻转的情况。

第一象限是第二象限左右翻转的情况。

第四象限是第三象限左右翻转的情况。

也是把坐标转换后按照在第二象限的情况处理即可。

------------


代码就不放了。

别骂，因为我赛时就是这么做的。

---

## 作者：incra (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc323_f)
### 题解

比较麻烦的模拟题。题意就是推箱子游戏。

不难想到，可以先推横向的，再推纵向的，或者反过来，取个最小值就为答案。

对于一下地图：（$P$ 是人的位置，$S$ 是箱子的位置，$E$ 是要推到的位置）
```
......
.S....
.....E
.....P
```
第一种推法：
```
.P....
.S....
.....E
......

......
.P....
.S...E
......

......
......
PS...E
......

......
......
....PS
......
```

另外一种同理，就不展开了。

其实就是这么一个步骤：

1. 把人移到箱子要推的反方向
2. 移动到不用移动位置

第 $1$ 步还要注意不能横穿箱子，所以移动的时候还要注意是否会穿过箱子。

其他没啥好说，挺简单的。

### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
typedef pair <LL,LL> PLL;
istream &operator >> (istream &in,PLL &a) {
	in >> a.x >> a.y;
	return in;
}
PLL a,b,c;
bool check (PLL x,PLL a,PLL b) {
	if (x == a || x == b) return false;
	if (min (a.x,b.x) <= x.x && x.x <= max (a.x,b.x) && min (a.y,b.y) <= x.y && x.y <= max (a.y,b.y)) return true;
	return false;
}
LL get_dis (PLL a,PLL b,PLL c = {-1e17,-1e17}) {
	if (a.x == b.x && a.x == c.x && min (a.y,b.y) <= c.y && c.y <= max (a.y,b.y)) return abs (a.x - b.x) + abs (a.y - b.y) + 2;
	if (a.y == b.y && a.y == c.y && min (a.x,b.x) <= c.x && c.x <= max (a.x,b.x)) return abs (a.x - b.x) + abs (a.y - b.y) + 2;
	return abs (a.x - b.x) + abs (a.y - b.y);
}
int main () {
//	cout << get_dis ({-1e18,-1e18},{1e18,(LL)1e18+},{{1e18,1e18},{-1e18,-1e18}}) << endl;
	cin >> a >> b >> c;
	int dx = b.x == c.x ? 0 : (b.x - c.x) / abs (b.x - c.x),dy = b.y == c.y ? 0 : (b.y - c.y) / abs (b.y - c.y);
	if (!dx) cout << get_dis (a,{b.x,b.y + dy},b) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
	else if (!dy) cout << get_dis (a,{b.x + dx,b.y},b) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
	else cout << min (get_dis (a,{b.x + dx,b.y},b) + (dy ? 2 : 0),
		get_dis (a,{b.x,b.y + dy},b) + (dx ? 2 : 0)) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
	return 0;
}
```

---

## 作者：aaron0919 (赞：1)

# [AT_abc323_f の题解](https://www.luogu.com.cn/problem/AT_abc323_f)

### 题目大意

给你人的坐标，箱子的坐标，还有目标的坐标，让你求将箱子推到目标的最小步数。

### 理性分析

其实总共分三步：

1. 移到箱子旁；
2. 推箱子到与目标水平或平行；
3. 换方向推到目标。

第二个步骤有两种方法，不过只用求一种，另一种将整个地图转一下就行了。

而第一个步骤却要分类讨论。

事实上就两种情况：

1. 先向垂直方向推，则求出初始位置到箱子水平的距离；
2. 先向水平方向推，则求出初始位置到箱子垂直的距离。

也就是求人距离箱子的哈曼顿距离，因为除了箱子别无障碍，两种方式到达指定位置中，必有一种是畅通无阻的。

不过有一种特殊情况，人刚好在箱子的和目标的中间，会被挡住，不是畅通无阻，就需要先挪一步。

### code

[AC 记录](https://atcoder.jp/contests/abc323/submissions/46455758)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//const int INF = 0x3f3f3f3f; 千万别这么开！开小了！！ /_\
const ll INF = 0x3f3f3f3f3f3f3f3f3fll;

ll player[2], box[2], target[2];

int sign(ll x) // 判断符号
{
	if (x == 0)
	{
		return 0;
	}
	else if (x > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

ll dis(ll a[2], ll b[2]) // 哈弗曼顿距离
{
	return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

bool in_middle(ll l, ll m, ll r) // 判断是否在中间
{
	ll L = min(l, r), R = max(l, r);
	return m > L && m < R;
};

ll solve() // 求解
{
	ll ret = dis(box, target);
	int d = sign(box[0] - target[0]);
	if (d == 0)
	{
		return INF;
	}
	ll t1[2];
	t1[0] = box[0] + d;
	t1[1] = box[1];
	ret += dis(player, t1);
	if ((player[0] == t1[0] && player[0] == box[0] &&
	        in_middle(player[1], box[1], t1[1])) ||
	        (player[1] == t1[1] && player[1] == box[1] &&
	         in_middle(player[0], box[0], t1[0]))) // 在中间
	{
		ret += 2;
	}
	if (box[1] != target[1]) // 不在一条线上要两步换方向
	{
		ret += 2;
	}
	return ret;
};

int main()
{
	scanf("%lld%lld%lld%lld%lld%lld", &player[0], &player[1], &box[0], &box[1], &target[0], &target[1]);

	ll ans = solve();
	swap(player[0], player[1]); // 反转
	swap(box[0], box[1]);
	swap(target[0], target[1]);
	ans = min(ans, solve());
	printf("%lld", ans);

	return 0;
}
```

---

## 作者：STAR_czy (赞：1)

# 思路：
一道水题，新手不学任何算法都可以 A 了这题，只是需要注意细节。分两种情况。

### 第一种：终点和箱子横坐标或纵坐标相同：
![](https://cdn.luogu.com.cn/upload/image_hosting/1mr95udm.png)

若横坐标相同，那么，就是走到箱子后面的那个格点。**注意，如果出发点和箱子很横坐标相同，且在箱子的前面，答案要多算两格（如图，橙色部分）**：
```cpp
if(x2==x3){
	int ans=abs(y3-y2);
	if(y2<y3) y2--;//判断后面的格点
	else y2++;
	ans+=abs(x1-x2)+abs(y1-y2);
	if(x1==x2){//判断多算两格的情况
		if(y3<y2&&y1<y2) ans+=2;
		if(y2<y3&&y2<y1) ans+=2;
	}
	write(ans),exit(0);
}
```

纵坐标就交换一下横纵坐标，然后把判断横坐标的代码在复制一下就行了:
```cpp
swap(x1,y1);
swap(x2,y2);
swap(x3,y3);//就只有多加了上面三行，下面和刚刚一样，直接复制即可。
if(x2==x3){
	int ans=abs(y3-y2);
	if(y2<y3) y2--;
	else y2++;
	ans+=abs(x1-x2)+abs(y1-y2);
	if(x1==x2){
		if(y3<y2&&y1<y2) ans+=2;
		if(y2<y3&&y2<y1) ans+=2;
	}
	write(ans),exit(0);
}
```


### 第二种：终点和箱子横坐标或纵坐标不同：
首先，要到达箱子的旁边。此时，有两个点可以到达（如图），取最小值即可。
![](https://cdn.luogu.com.cn/upload/image_hosting/9ji0xpso.png)

然后，推到与箱子横坐标相同了，此时，要多走两步绕道箱子的后方（如图）。
![](https://cdn.luogu.com.cn/upload/image_hosting/kbh4wu53.png)

代码如下：
```cpp
int ans=abs(y3-y2)+abs(x3-x2)+2/*到达箱子后面之后推到目标点*/,tx=x2,ty=y2;
if(ty<y3) ty--;
else ty++;
int tmp=abs(y1-ty)+abs(x1-tx);
ty=y2;
if(tx<x3) tx--;
else tx++;
tmp=min(tmp,abs(y1-ty)+abs(x1-tx));//比较两个后面的点到起点的位置
write(ans+tmp);
```
然后就好了。

# 代码:
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int maxn=1e6+10,mod=998244353;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

signed main(){
	int x1=read(),y1=read()/*注意y1不能定义为全局变量*/,x2=read(),y2=read(),x3=read(),y3=read();
	if(x2==x3){
		int ans=abs(y3-y2);
		if(y2<y3) y2--;
		else y2++;
		ans+=abs(x1-x2)+abs(y1-y2);
		if(x1==x2){
			if(y3<y2&&y1<y2) ans+=2;
			if(y2<y3&&y2<y1) ans+=2;
		}
		write(ans),exit(0);
	}
	swap(x1,y1);
	swap(x2,y2);
	swap(x3,y3);
	if(x2==x3){
		int ans=abs(y3-y2);
		if(y2<y3) y2--;
		else y2++;
		ans+=abs(x1-x2)+abs(y1-y2);
		if(x1==x2){
			if(y3<y2&&y1<y2) ans+=2;
			if(y2<y3&&y2<y1) ans+=2;
		}
		write(ans),exit(0);
	}
	int ans=abs(y3-y2)+abs(x3-x2)+2,tx=x2,ty=y2;
	if(ty<y3) ty--;
	else ty++;
	int tmp=abs(y1-ty)+abs(x1-tx);
	ty=y2;
	if(tx<x3) tx--;
	else tx++;
	tmp=min(tmp,abs(y1-ty)+abs(x1-tx));
	write(ans+tmp);
	return 0;
}
```

---

## 作者：N_Position (赞：1)

~~蒟蒻不会太难的思路，来发一发分类讨论的题解。~~

## 题目翻译
> 推箱子，给定人、箱子和终点的坐标，求人将箱子推到终点最少需要走几步？

## 题目分析
~~既然是 F 题，有很多 `if` 很合理吧！~~

本题主要的思想是分类讨论，只需要把所有情况找出来不就行了！

我们先将问题简化，若过箱子不需要“推”到终点，而是想钥匙一样携带到终点，显然最少步数是 $\left\vert x_2-x_1\right\vert + \left\vert y_2-y_1\right\vert + \left\vert x_2-x_3\right\vert + \left\vert y_2-y_3\right\vert $，其中人、箱子和终点的坐标分别为 $(x_1,y_1)$、$(x_2,y_2)$ 和 $(x_3,y_3)$。

如果箱子是推，则可能会少走几步或多走几步。

多走很显然，是因为每次转弯时，需要绕路。
少走则是如果推的过程中不需要转弯，则会少最后一步，即在到达终点的前一格时，箱子已经被推到了终点。

需要注意的是，对于箱子、人和终点在一条直线上的情况，需要特殊考虑。

理解了这些，我们就可以开始分类讨论了。

我们主要分为以下几种情况：

一、三点都不共线；

二、有两点共线，另外一点不共线；

三、三点呈 L 形状（我在这里卡了十分钟 qwq）；

四、三点共线。

我们以三点不共线为例。
当人于终点在箱子的异侧时，人走的路径如下,由此可见比起直接走多走了一步。
![](https://cdn.luogu.com.cn/upload/image_hosting/tf2fpvhj.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/d3cqbuu2.png)

位于箱子同侧时，路径如下，由此可见比起直接走多走了三步。
![](https://cdn.luogu.com.cn/upload/image_hosting/d5q2ik0j.png)

其他情况类似。

## 代码实现
```cpp
#include<iostream>
#include<cstdio>
typedef long long ll;
ll abs(ll t){
	if(t < 0){
		return -t;
	}
	return t;
}
int main(){
//	freopen("1.txt","r",stdin);
//	freopen("f.out","w",stdout);
	ll x1,y1,x2,y2,x3,y3;
	scanf("%lld%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&x3,&y3);
	ll ans = abs(x2-x1) + abs(y2-y1) + abs(x2-x3) + abs(y2-y3);
	if(x1 != x2 && x2 != x3){
		if(y1 != y2 && y2 != y3){//人与箱，箱与终不在一条直线上 
			if(((x1<x2) == (x3<x2)) && ((y1<y2) == (y3<y2))){
				printf("%lld",ans+3);
				return 0;
			}else{
				printf("%lld",ans+1);
				return 0;
			}
		}
	}
	if(x1 == x2 && y2 == y3){
		printf("%lld",ans+1);
		return 0;
	}
	if(y1 == y2 && x2 == x3){
		printf("%lld",ans+1);
		return 0;
	}
	if(x1 == x2){//人和箱子一条直线 
		if(x1 != x3 && ((y1<y2)==(y3<y2))){
			printf("%lld",ans+3);
			return 0;
		}
		if(x1 != x3 && ((y1<y2)!=(y3<y2))){
			printf("%lld",ans+1);
			return 0;
		}
	}
	if(y1 == y2){//人和箱子一条直线 
		if(y1 != y3 && ((x1<x2)==(x3<x2))){//人终同侧 
			printf("%lld",ans+3);
			return 0;
		}
		if(y1 != y3 && ((x1<x2)!=(x3<x2))){//人终异侧 
			printf("%lld",ans+1);
			return 0;
		}
	}
	if(x3 == x2){//终点和箱子一条直线 
		if(x1 != x3 && ((y1<y2)==(y3<y2))){
			printf("%lld",ans+1);
			return 0;
		}
		if(x1 != x3 && ((y1<y2)!=(y3<y2))){
			printf("%lld",ans-1);
			return 0;
		}
	}
	if(y3 == y2){//终点和箱子一条直线 
		if(y1 != y3 && ((x1<x2)==(x3<x2))){//人终同侧 
			printf("%lld",ans+1);
			return 0;
		}
		if(y1 != y3 && ((x1<x2)!=(x3<x2))){//人终异侧 
			printf("%lld",ans-1);
			return 0;
		}
	}
	if(x1 == x2 && x1 == x3){//三点共线 
		if((y1<y2) == (y2<y3)){//箱子在中间 
			printf("%lld",ans-1);
			return 0;
		}
		else{
			printf("%lld",ans+3);
			return 0;
		} 
	}
	if(y1 == y2 && y1 == y3){//三点共线 
		if((x1<x2) == (x2<x3)){//箱子在中间 
			printf("%lld",ans-1);
			return 0;
		}
		else{
			printf("%lld",ans+3);
			return 0;
		} 
	}
}
```
时间复杂度 $O(1)$。

---

## 作者：jr_inf (赞：0)

不难发现答案的下界为 $|x_b-x_c|+|y_b-y_c|$，这是每步都推箱子的情况。

但很多时候并不能直接开始推箱子，所以人要先移动到箱子的后面（相对于目的地），再把箱子往目的地推。

比如这种情况（B 为箱子，C 为目的地）：
```cpp
B..
...
..C

```
推完箱子的一边后，还要走到另一边：
```cpp
↓
B..   ...  ...
...   ...  ...
..C  →B.C  ..B

```
额外的代价就是人走到箱子边上（下一步开始推）的时间加上换边的时间 $2$（如果有）。

特判掉不用换边的情况后，再计算人到箱子两边的距离的最小值即可。

code：
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int ax,ay,bx,by,cx,cy,ans;
int get(int x,int y,int tx,int ty)
{
	int cnt=abs(x-tx)+abs(y-ty);
	if(x==tx&&x==bx&&min(y,ty)<by&&by<max(y,ty))cnt+=2;//路径被箱子阻挡
	else if(y==ty&&y==by&&min(x,tx)<bx&&bx<max(x,tx))cnt+=2;
	return cnt;
}
signed main()
{
	cin>>ax>>ay>>bx>>by>>cx>>cy;
	ans=abs(bx-cx)+abs(by-cy);
	if(bx==cx)printf("%lld",get(ax,ay,bx,by+(cy<by?1:-1))+ans);
	else if(by==cy)printf("%lld",get(ax,ay,bx+(cx<bx?1:-1),by)+ans);
	else printf("%lld",ans+2+min(get(ax,ay,bx,by+(cy<by?1:-1)),get(ax,ay,bx+(cx<bx?1:-1),by)));//要换边
}
```


---

## 作者：封禁用户 (赞：0)

# 题意
简单来说就是有个人在 $a_{x,y}$， 要把在 $b_{x,y}$ 的东西推到 $c_{x,y}$ 去。地图大小无限。推的方式如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/a5hq6b7n.png)

人必须挨着哈。

# 思路
一道模拟题。

我们讨论每种情况，也就是在左上，左下，右上，右下。

![](https://cdn.luogu.com.cn/upload/image_hosting/7t4oiyu8.png)

这是我讨论的四种情况。这样可以包括所有 $c_{x,y}$ 相对于 $b_{x,y}$ 的位置。

我们首先算出要推动东西的次数。因为要次数最少，不能走回头路，所以只能向我标的那种方式走。

同时，我们可以从两种方向去推。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2u7spjn.png)

找到起点对于这两个位置的最近。但是，要特殊讨论这几种。

![](https://cdn.luogu.com.cn/upload/image_hosting/cjowtrva.png)

他只能走相反方向的那一种，要特殊讨论。

而拐弯的时候也不是直接就拐了，而是要绕一圈。

![](https://cdn.luogu.com.cn/upload/image_hosting/3idgwiod.png)

很明显，要在步数上加 $2$。

然后在上一种特殊情况下（有相同的 $x$ 或 $y$ 时），不用拐弯，自然也不用加 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xdf6m54x.png)

如果在一条线上，且要绕回去（如上），按原来算法就是 $3$ 步，但当到东西那里的时候，东西会移动（被推走），所以要绕一下，加 $2$ 步。

完！

细节多，要仔细。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long xa,ya,xb,yb,xc,yc;
long long jl(long long xb,long long xc,long long yb,int yc){
	return abs(xb-xc)+abs(yb-yc);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>xa>>ya>>xb>>yb>>xc>>yc;
	long long yd=jl(xb,xc,yb,yc);
	//jl(xb,xa,yb,ya)
	if(xc<=xb&&yc>yb){//zuoshang
		long long j1=jl(xb+1,xa,yb,ya);
		long long j2=jl(xb,xa,yb-1,ya);
		if(ya==yb&&xa<xb){
			j1+=2;
		}
		if(xa==xb&&ya>yb){
			j2+=2;
		}
		if(xc==xb){
//			cout<<11<<endl;
			cout<<yd+j2;
			return 0;
		}else{
//			cout<<12<<endl;
			cout<<yd+2+min(j1,j2);
			return 0;
		}
	}else if(xc>xb&&yc>=yb){//youshang
		long long j1=jl(xb-1,xa,yb,ya);
		long long j2=jl(xb,xa,yb-1,ya);
		if(ya==yb&&xa>xb){
			j1+=2;
		}
		if(xa==xb&&ya>yb){
			j2+=2;
		}
		if(yc==yb){
//			cout<<21<<endl;
			cout<<yd+j1;
			return 0;
		}else{
//			cout<<22<<endl;
			cout<<yd+2+min(j1,j2);
			return 0;
		}
		
	}else if(xc>=xb&&yc<yb){//youxia
		long long j1=jl(xb-1,xa,yb,ya);
		long long j2=jl(xb,xa,yb+1,ya);
		if(ya==yb&&xa>xb){
			j1+=2;
		}
		if(xa==xb&&ya<yb){
			j2+=2;
		}
		if(xc==xb){
//			cout<<31<<endl;
			cout<<yd+j2;
			return 0;
		}else{
//			cout<<32<<endl;
			cout<<yd+2+min(j1,j2);
			return 0;
		}
		
	}else{//zuoxia
		long long j1=jl(xb+1,xa,yb,ya);
		long long j2=jl(xb,xa,yb+1,ya);
		if(ya==yb&&xa<xb){
			j1+=2;
		}
		if(xa==xb&&ya<yb){
			j2+=2;
		}
		if(yc==yb){
//			cout<<41<<endl;
			cout<<yd+j1;
			return 0;
		}else{
//			cout<<42<<endl;
			cout<<yd+2+min(j1,j2);
			return 0;
		}
	}
	return 0;
}
```

---

