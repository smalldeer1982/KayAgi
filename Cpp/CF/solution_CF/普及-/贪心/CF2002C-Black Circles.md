# Black Circles

## 题目描述

在一个二维平面上有 $n$ 个圆。第 $i$ 个圆的圆心位于 $(x_i, y_i)$。最初，所有圆的半径都是 $0$。

这些圆的半径以每秒 $1$ 单位的速度增长。

你现在的位置是 $(x_s, y_s)$，你的目标是到达 $(x_t, y_t)$，并且在这个运动过程中不能碰到任何一个圆的边缘（包括你到达 $(x_t, y_t)$ 的那一刻）。你可以向任意方向移动。然而，你的速度被限制在每秒 $1$ 单位。

请判断是否有可能实现这一目标。

## 说明/提示

在第一个测试用例中，一种可行的移动方式如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2002C/e91b557a5335aaaa3689cd6df137ea06f9152e48.png)

## 样例 #1

### 输入

```
7
3
2 5
2 14
10 13
4 9 9 7
3
10 11
6 9
12 12
14 13 4 8
1
5 7
12 6 11 13
2
1000000000 2
2 1000000000
1 1 2 2
1
999999998 1000000000
999999999 999999999 1 1
1
1000000000 1
1 1000000000 1 1
10
989237121 2397081
206669655 527238537
522705783 380636165
532545346 320061691
207818728 199485303
884520552 315781807
992311437 802563521
205138355 324818663
223575704 395073023
281560523 236279118
216941610 572010615 323956540 794523071```

### 输出

```
YES
NO
YES
YES
YES
NO
YES```

# 题解

## 作者：3Luby3 (赞：4)

本蒟蒻的第一篇题解，感谢支持。
## 题目大意

起初在 $(x_i,y_i)$ 的 $n$ 个圆半径都为 $0$，然后每秒半径增长 $1$ 个单位。我们要从 $(x_s,y_s)$ 移动到 $(x_t,y_t)$，在此之间不能碰到任何一个圆的边缘，判断能否到达目标。

## 解题思路

**本题算法：贪心。**

本题我们可以把圆心存在一个结构体里，大小开 ${10}^{5}$，不会爆。

我们知道**两点之间直线最短**，所以这道题我们从 $(x_s,y_s)$ 到 $(x_t,y_t)$ 时要走直线才是最短、最快的。

那要如何求两个点之间的距离呢？

**公式如下：**

$$
\sqrt{{(x_2-x_1)}^{2}+({y_2-y_1})^{2}}
$$

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/tds86dre.png)

（图可能不太严谨，见谅）

这里的 $(x_2,y_2)$ 为 $(5,5)$，$(x_1,y_1)$ 为 $(1,1)$，代入公式，他们的距离就为 $\sqrt{{(5-1)}^{2}+({5-1})^{2}}$，算出来就是 $\sqrt{32}$。

公式说完再回到思路。我们利用这个公式就可以判断走的是不是最短的路线，如果是就输出 `Yes`，否则输出 `No`。

## 温馨提示

- 本题是多组样例，所以如果用了标记就一定要归为 $0$。
- 由于我的公式总结是写的 $y_1$ 可能会误导大家开一个叫 $y1$ 的变量，这是不行的，应为 $y1$ 是一个 C++ 函数，交上去会 WA。
- （优化提示）这道题目的公式可以不用开根，因为本题不是输出确切的距离，只是利用距离帮助去求最短的路线，所以可以不用开根号。

## 代码

AC 记录：[link at CF](https://codeforces.com/problemset/submission/2002/286241471)。

```c++
#include<iostream>
#define int long long
using namespace std;
int T,n,x1,y,x2,y2;//一定记得不能用y0或y1做变量名
bool flag=false;//记得定义
struct node{
	int x,y;
}a[1000001];
int juli(int x1,int y,int x2,int y2){//计算两点之间的距离
	return (x2-x1)*(x2-x1)+(y2-y)*(y2-y);//可以不用开根号，具体见「温馨提示」
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;//多组数据
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;//输入圆心坐标
		cin>>x1>>y>>x2>>y2;//输入起点坐标和终点坐标
		flag=false;//多组样例记得重新定义为false
		for(int i=1;i<=n;i++){
			if(juli(a[i].x,a[i].y,x2,y2)<=juli(x1,y,x2,y2)) flag=1;//判断+标记
		}
		if(flag==0) cout<<"Yes"<<endl;//如果是最短的输出Yes
		else cout<<"No"<<endl;//否则输出No
	}
	return 0;
}
```

---

## 作者：ATION001 (赞：3)

## 题目描述
给定起点、终点和 $n$ 个圆的中点的坐标，每秒钟你可以向**任意方向**移动一步，每个圆每秒钟半径都会扩大 $1$。

请问你能不能在不碰到任何圆的边缘的情况下到达终点（包括到达终点的一瞬间）。
## 思路
首先我们要明白一点，**不走直线肯定更劣**。

![](https://cdn.vjudge.net.cn/235d765e20897c623b3ac974eceac134)

题目的示意图可能有一点误导人，而且走曲线不太好想。

走直线的话只需要判断起点距离终点的直线距离是不是最短的就可以了。

求平面上两点之间的距离公式：

$$
\sqrt{(ex-dx)^2+(ey-dy)^2}
$$

其中 $dx$ 代表起点的 $x$ 坐标，$dy$ 代表起点的 $y$ 坐标。$ex$ 代表终点的 $x$ 坐标，$ey$ 代表终点的 $y$ 坐标。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
pair<int,int>a[100005];
int code(int dx,int dy,int ex,int ey){
	return (ex-dx)*(ex-dx)+(ey-dy)*(ey-dy); // 由于每一个数字都需要开根号所以干脆不开根号，可以降低时间复杂度（此题不需要输出距离）
}
int dx,dy,ex,ey;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].first>>a[i].second;
		}
		cin>>dx>>dy>>ex>>ey;
		bool flag=false;
		for(int i=1;i<=n;i++){
			flag|=(code(a[i].first,a[i].second,ex,ey)<=code(dx,dy,ex,ey)); // 一旦有一个不满足 flag 就会是 true
		}
		cout<<(!flag?"Yes":"No")<<'\n'; // flag 的结果为 false 才满足要求
	}
	return 0;
}
```

---

## 作者：Na2PtCl6 (赞：2)

考虑起点 $S$ ，终点 $T$ 和任意一个圆心 $C$ 。

如果走直线，那么 $ST<CT$ 肯定是个必要条件，下面证明充分性。

![](https://cdn.luogu.com.cn/upload/image_hosting/mg54e1zh.png)

如果 $k<1$ ，那么在我们走到垂足点之后，圆扩散的速度是赶不上我们的。

如果 $k>1$，那么根据根据我们假设的 $ST<CT$，即 $ka<x-y$，可以推出矛盾，因为 $a>x-y$。

所以我们证明了 $ST<CT$ 是走得到的充分条件。

然后我们知道 $ST \geq CT$ 的话怎么走也走不到。

所以这个题就是判断是否任意 $C_i(1\leq i \leq n)$ 都满足 $ST<C_iT$

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

显然，当某个点到起点的距离大于等于到任何一个圆心的距离，这个点就不可到达。

考虑把圆心和起点连线作垂直平分线，如果越过了这条线，那么到起点的距离一定大于等于到这圆心的距离。如果终点在这条线对面，那么一定不能到达。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e6 + 10;
ll n, a[MAXN], b[MAXN], xs, ys, xt, yt, T;
void read () {
	cin >> n;
	for (ll i = 1; i <= n; i ++) cin >> a[i] >> b[i];
	cin >> xs >> ys >> xt >> yt;
	ll cun = (xs - xt) * (xs - xt) + (ys - yt) * (ys - yt);
	for (ll i = 1; i <= n; i ++) {
		ll cunn = (a[i] - xt) * (a[i] - xt) + (b[i] - yt) * (b[i] - yt);
		if (cunn <= cun) cout << "NO" << endl;
	}	
	cout << "YES"<< endl;
}
int main () {	
	cin >> T;
	while (T --) read ();
	return 0;
}

```

---

## 作者：masonxiong (赞：0)

# 题目分析

**千万别把这题想难了**，我们要充分相信 CFDiv2C 是不难的。

此题就纯诈骗题，那个样例解释的动图就是拿来误导你走曲线的。这题的解法非常的简单：

- **向终点直线前进**。若能够在任何一个圆包含终点之前抵达终点，则可以到达，否则不能到达。

下面我们对这个结论进行证明。

---

## 关于不能到达终点的证明

我们要证的是：**若我们向终点直线前进，却仍然不能在任何一个圆包含终点之前抵达终点，则我们无论如何也抵达不了**。

因为两点之间线段最短，所以其他路线的路程肯定比走直线的路程长，又因为速度恒定，所以走其他路线的用时肯定比走直线的用时长。

综上，走直线到不了的话，走其他路线也到不了。

那么判无解的方法就是**比较起点到终点的距离以及每个圆的圆心到终点的距离，若起点到终点的距离不是其中最小的，则无解。**

---

## 关于可以放心走直线的证明

> 不妨假设此时我们已经判掉了无解的情况，那么**任何一个圆到终点的距离都应该比起点到终点的距离要长**。

认为走直线到不了而走曲线能到肯定是想到这样的一种情况：你从起点 $S$ 走在前往终点 $T$ 的路上，一个圆 $O$ 于 $P$ 挡住了直线道路，迫使你转弯。如图：

![一个圆挡住了直线道路](https://cdn.luogu.com.cn/upload/image_hosting/46v229ki.png)

因为圆扩张的速度和人走路的速度是一样的，所以 $|OP|=|SP|$（虽然这图画的一点都不像）。

根据三角形性质**两边之差小于第三边**，$|OP|>|OT|-|PT|$，则 $|SP|+|PT|>|OP|$，即 $|ST|>|OP|$，与我们的假设矛盾。

因此这种情况不存在。综上，我们可以放心大胆地走直线。

---

# 题目做法

既然走直线一定最快，那我们就走直线呗。如果直线都到不了，那就无解。

因此，我们只需要**比较起点到终点的距离以及每个圆的圆心到终点的距离，若起点到终点的距离不是其中最小的则无解，否则有解**。

分析一下时空复杂度：

- 时间复杂度：$O(n)$。我们需要分别计算每一个圆到终点的距离。
- 空间复杂度：$O(n)$。我们需要存储每一个圆。

---

# 代码

正规的距离公式是带根号的，但是由于我们比较的是两个距离，不等号左右都非负，所以左右平方之后就可以消掉根号了。


```cpp
#include <bits/stdc++.h>
using namespace std;
 
int T, N;
vector<pair<long long, long long>> circles;
pair<long long, long long> source, destination;
 
long long eDistance(const pair<long long, long long>& x, const pair<long long, long long>& y) {
	return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	for (cin >> T; T--; ) {
		cin >> N;
		circles.resize(N);
		for (auto& i : circles)
			cin >> i.first >> i.second;
		cin >> source.first >> source.second >> destination.first >> destination.second;
		long long minDistance = numeric_limits<long long>::max();
		for (const auto& i : circles)
			minDistance = min(minDistance, eDistance(i, destination));
		cout << (minDistance <= eDistance(source, destination) ? "No\n" : "Yes\n");
	}
	return 0;
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2002C)

### $\texttt{Description}$

在一个二维平面上面有 $n$ 个圆形，第 $i$ 个圆形的圆心的坐标为 $(x_i,y_i)$。这些圆形以 $0$ 的初始半径开始增长，每秒半径会增长 $1$ 个单位。现在问，你能不能在行进过程中，不碰到任何的圆形的边界，从给定的起点走到给定的终点。你的行进速度为 $1$ 单位每秒。

### $\texttt{Solution}$

前置知识：二维平面上两点直线距离公式。我们需要用到勾股定理。

勾股定理的证明方式有很多，我就不在这里赘述了。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dscntg5.png)

我们可以知道，$AB$ 就是那条蓝色的线段，它的长度为：

 $$\sqrt{3^2 + 4^2}=\sqrt{25}=5$$

这就是勾股定理最简单的应用，再放一下公式：$a^2+b^2=c^2$。

那么，我们可以知道下面的结论：

假设有一个二维平面上有两个点 $x,y$，它们的坐标分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$，那么，它们的直线距离为：

$$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$$

由于任何数的平方具有非负性，所以我们不需要考虑坐标的大小关系。

那么这个距离公式在这道题上可以发挥上面用处呢？

其实很简单，我们只要计算出起点到终点的直线距离，然后看看它是不是最短的路径即可，并且不能有任何距离小于对于这个距离。

我们只需要用所有的圆心的坐标去打擂台即可。因为圆形扩大的速度只有 $1$ 个单位每秒。

而且，我们还可以进行优化。

因为我们这题不需要计算真正的距离，只需要去做比较，所以我们不需要在距离函数里开根号，就相当于我们把每个距离的值进行了平方操作，因为将所有值平方之后，它们的相对大小关系是不变的。

本题难度建议为黄色。

### $\texttt{Code}$

代码按照上述思路完成即可。贴出有注释的代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
// 为了简便而写
using namespace std;

typedef pair<int, int> Pair;
const int N = 1e5 + 5;
int n, t;

Pair a[N]; // 我们可以用 pair 存储坐标

int dis(Pair q, Pair h) { 
	return (q.x - h.x) * (q.x - h.x) + (q.y - h.y) * (q.y - h.y);
	// 优化 1，不用 sqrt
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	// 优化 2，关闭同步流
	
	cin >> t;
	
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i].x >> a[i].y;
		}
		// 每个圆心的坐标
		
		Pair st, en; // 起点和终点坐标
		cin >> st.x >> st.y >> en.x >> en.y;
		int d = dis(st, en);
		
		bool flag = false; // 初始为满足条件
		for (int i = 1; i <= n; i++) {
			int d1 = dis(make_pair(a[i].x, a[i].y), en); // 表示当前这个圆心到终点的距离
			// make_pair 函数可以自动将两个值合并成一个 pair 类型
			if (d1 <= d) { // 不是最小距离
				flag = true; // 不符合条件，标记
				cout << "No\n"; // 输出
				break;
				// 优化 3，如果已经不符合条件，那就直接结束循环
			}
		}
		
		if (!flag) cout << "Yes\n"; // 符合条件
	}
	
	return 0;
}
```

---

## 作者：yangzimu0131 (赞：0)

# 题解
考虑贪心，沿着直线走向目标。如果某个圆阻拦住了通路，那么很显然，无论我们怎么走，都无法到达。
# Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100010],b[100010];
signed main()
{
	int T,n,sx,sy,ax,ay,t;
	bool f;
	cin>>T;
	while(T--)
	{
		f=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i]>>b[i];
		cin>>sx>>sy>>ax>>ay;
		t=(sx-ax)*(sx-ax)+(sy-ay)*(sy-ay);
		for(int i=1;i<=n;i++)
		{
			sx=a[i];
			sy=b[i];
			if((sx-ax)*(sx-ax)+(sy-ay)*(sy-ay)<=t)
			{
				cout<<"NO\n";
				f=1;
				break;
			}
		}
		if(!f)
			cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：lzh9 (赞：0)

## 思路

显然，当某个点到起点的距离大于等于到任何一个圆心的距离，这个点就不可到达，因为到这个点时圆必然已经扩展到这个点。考虑把圆心和起点连线作垂直平分线，如果越过了这条线，那么到起点的距离一定大于等于到这圆心的距离。如果终点在这条线对面，那么一定不能到达。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[1000000+5],b[1000000+5];
long long xs,ys,xt,yt;
void sol()
{
	cin>>n;
	for(long long i=1;i<=n;i++) cin>>a[i]>>b[i];
	cin>>xs>>ys>>xt>>yt;
	long long jl=(xs-xt)*(xs-xt)+(ys-yt)*(ys-yt);
	for(long long i=1;i<=n;i++)
	{
		long long jlt=(a[i]-xt)*(a[i]-xt)+(b[i]-yt)*(b[i]-yt);
		if(jlt<=jl)
		{
			cout<<"NO\n";
			return;
		}
	}	
	cout<<"YES\n";
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long t;
	cin>>t;
	while(t--)
	{
		sol();
	}
	return 0;
}
```

---

## 作者：furina_yyds (赞：0)

### 题目传送门
[点这里](https://www.luogu.com.cn/problem/CF2002C)
### 开篇警示
 _**多测不清空，WA 两行泪。**_ 

进入正题
##### 思路
这道题的主旋律是：贪心

我们可以这样想：假如你去上学，然后被几群小混混盯上了，他们以一定的速度去追你，你的第一反应绝对是：拼命往学校跑，跑不死也往死里跑。

那么，这题的思路就有了。
##### 解法
模拟直线向终点跑，看看会不会碰到圆，如果会，那么就是不可能的事情了，如果不会，那么一定可以。
##### 证明
如模拟不会碰到圆，那么一定可以。

如会，除非你往相反方向跑，否则一定无法避开这个圆（因为只有你离开圆心的速度大于等于 $1$，你才能多开，而模拟时躲不掉，则一定躲不掉）


  _**注：本篇不提供代码！！！**_

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](https://codeforces.com/problemset/problem/2002/C)

### 思路
~~为什么 cf 的题都是多测~~

我们发现，如果从起点 $S$ 到任意一个点 $p$ 的距离 $d$ 大于等于 $p$ 到任何一个圆心的距离，那么 $S$ 不可到达 $p$，因为我们的速度和圆的扩展速度是一样的，所以圆扩展到 $p$ 的时候我们未到达 $p$ 点。还有一种情况，当我们与圆周同时到达 $p$ 点，但这种情况是不被允许的。

所以我们可以遍历圆心，每次判断到 $S$ 的直线距离是否大于等于点 $T$ 到目前遍历到的圆心的距离。如果成立，则我们得出点 $S$ 无法到达点 $P$；反之便可以到达点 $P$。

在同一平面内，从点 $a$ 到点 $b$ 的距离为 
$\sqrt{(xa-xb)^2+(ya-yb)^2}$。

并且我们知道，如果 $a\lt b$，那么 $\sqrt{a}\lt \sqrt{b}$。所以我们每次只需得出 
$(xa-xb)^2+(ya-yb)^2$ 并**直接比较**它们的大小即可。

### 代码
```cpp
#include <iostream>
#include <vector>
#define ll long long
using namespace std;
struct Node
{
    ll x, y;
};
vector<Node> a;

ll t;

ll n;
Node X;
Node S, T;

ll dist(ll xa, ll xb, ll ya, ll yb)
{
    return (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb);
}
void solve()
{
    ll dis = dist(S.x, T.x, S.y, T.y);
    a.clear();

    cin >> n;

    for (ll i = 1; i <= n; i++)
        cin >> X.x >> X.y,
        a.push_back(X);
    
    cin >> S.x >> S.y
        >> T.x >> T.y;
    
    dis = dist(S.x, T.x, S.y, T.y);

    for (ll i = 0; i < (ll)a.size(); i++)
        if (dis >= dist(a[i].x, T.x, a[i].y, T.y))
        {
            cout << "No\n";
            return;
        }
    
    cout << "Yes\n";
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
        solve();
    return 0;
}
```

---

