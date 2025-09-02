# [EC Final 2020] Rooks

## 题目描述

庞教授与他的对手寿教授下棋。他们是游戏中仅有的两位玩家。棋盘非常大，可以看作是一个二维平面。庞教授放置了 $n_1$ 个车，寿教授放置了 $n_2$ 个车。每个车在棋盘上是一个具有整数坐标的点。如果一个车满足以下所有条件，则被另一个车「攻击」：

- 它们由不同的玩家放置。
- 它们具有相同的 $x$ 坐标或 $y$ 坐标。
- 在它们之间的线段上没有其他车。

帮助庞教授和寿教授判断哪些车被攻击。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 2
0 0
0 1
1 0
0 -1
-1 0```

### 输出

```
100
11```

# 题解

## 作者：fkxr (赞：10)

这题是一题签到题。

题目大意是在一个二维平面中有 $n_1$ 个第一阵营的车和 $n_2$ 个第二阵营的车，求每个车是否会被攻击，一个车会被另一个车攻击的条件是：

1. 属于不同阵营；
2. $x$ 坐标相等或 $y$ 坐标相等
3. 他们中间没有其他车

我们可以建立结构体出存每个车的 $x$ 坐标、$y$ 坐标、所属阵营、序号，然后对他们的 $x$ 坐标排序，如果 $x$ 坐标相同，就对相同 $x$ 坐标的车的 $y$ 坐标进行排序，这样做可以让我们只用比较这个车的信息和上一个车的信息，看看他们可不可以互相攻击，反之亦然。

最终代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool ok[400005];

struct node {
	int x, y;
	int id;
	int z;
} a[400005];

bool cmp(node a1, node a2) {
	if (a1.x != a2.x) {
		return a1.x < a2.x;
	}
	return a1.y < a2.y;
}

bool cmpp(node a1, node a2) {
	if (a1.y != a2.y) {
		return a1.y < a2.y;
	}
	return a1.x < a2.x;
}

signed main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		a[i].id = i;
		a[i].z = 0;
	}
	for (int i = n; i < n + m; i++) {
		cin >> a[i].x >> a[i].y;
		a[i].id = i;
		a[i].z = 1;
	}
	sort(a, a + n + m, cmp);
	for (int i = 1; i < n + m; i++) {
		if (a[i - 1].x == a[i].x && a[i].z != a[i - 1].z) {
			ok[a[i].id] = 1;
			ok[a[i - 1].id] = 1;
		}
	}
	sort(a, a + n + m, cmpp);
	for (int i = 1; i < n + m; i++) {
		if (a[i - 1].y == a[i].y && a[i].z != a[i - 1].z) {
			ok[a[i].id] = 1;
			ok[a[i - 1].id] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ok[i];
	}
	cout << "\n";
	for (int i = n; i < m + n; i++) {
		cout << ok[i];
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/169226650)

---

## 作者：BestInW (赞：2)

## 思路分析
题目中有两位玩家在一个平面上放车，并判断是否有车会被另一辆车攻击。发生攻击一定满足以下条件：

这两辆车的阵营不同。

这两辆车的横坐标或纵坐标相同。

这两车之间没有其他车阻挡。

代码通过结构体存储棋子信息，利用排序和对比坐标来判断棋子是否被攻击。先按横坐标排序，检查相同横坐标且不同玩家的棋子；再按纵坐标排序重复检查。通过数组记录棋子状态，最后输出结果。解题关键在于巧妙运用排序和条件判断。下面是详细注释的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

// 存储棋子状态的数组
bool statusArray[400005];

// 定义结构体表示棋子信息
struct DataNode {
    int xValue;    // 棋子的 x 坐标
    int yValue;    // 棋子的 y 坐标
    int nodeId;    // 棋子的编号
    int playerIndicator; // 表示棋子所属玩家的标识
};

// 定义棋子数组
DataNode dataArray[400005];

// 比较函数 1，按照 x 坐标升序排列，若 x 相同则按 y 坐标升序排列
bool compareFunc1(DataNode node1, DataNode node2) {
    if (node1.xValue!= node2.xValue) {
        return node1.xValue < node2.xValue;
    }
    return node1.yValue < node2.yValue;
}

// 比较函数 2，按照 y 坐标升序排列，若 y 相同则按 x 坐标升序排列
bool compareFunc2(DataNode node1, DataNode node2) {
    if (node1.yValue!= node2.yValue) {
        return node1.yValue < node2.yValue;
    }
    return node1.xValue < node2.xValue;
}

signed main() {
    int num1, num2;
    cin >> num1 >> num2;
    // 输入第一个玩家的棋子信息
    for (int i = 0; i < num1; i++) {
        cin >> dataArray[i].xValue >> dataArray[i].yValue;
        dataArray[i].nodeId = i;
        dataArray[i].playerIndicator = 0; // 标识为第一个玩家
    }
    // 输入第二个玩家的棋子信息
    for (int i = num1; i < num1 + num2; i++) {
        cin >> dataArray[i].xValue >> dataArray[i].yValue;
        dataArray[i].nodeId = i;
        dataArray[i].playerIndicator = 1; // 标识为第二个玩家
    }
    // 按照 x 坐标和 y 坐标升序排序
    sort(dataArray, dataArray + num1 + num2, compareFunc1);
    // 检查在 x 坐标相同且不同玩家的棋子是否相互攻击
    for (int i = 1; i < num1 + num2; i++) {
        if (dataArray[i - 1].xValue == dataArray[i].xValue && dataArray[i].playerIndicator!= dataArray[i - 1].playerIndicator) {
            statusArray[dataArray[i].nodeId] = 1;
            statusArray[dataArray[i - 1].nodeId] = 1;
        }
    }
    // 按照 y 坐标和 x 坐标升序排序
    sort(dataArray, dataArray + num1 + num2, compareFunc2);
    // 检查在 y 坐标相同且不同玩家的棋子是否相互攻击
    for (int i = 1; i < num1 + num2; i++) {
        if (dataArray[i - 1].yValue == dataArray[i].yValue && dataArray[i].playerIndicator!= dataArray[i - 1].playerIndicator) {
            statusArray[dataArray[i].nodeId] = 1;
            statusArray[dataArray[i - 1].nodeId] = 1;
        }
    }
    // 输出第一个玩家的棋子状态
    for (int i = 0; i < num1; i++) {
        cout << statusArray[i];
    }
    cout << endl;
    // 输出第二个玩家的棋子状态
    for (int i = num1; i < num1 + num2; i++) {
        cout << statusArray[i];
    }
    return 0;
}
```
谢谢观看本蒟蒻写的题解，再次感谢。

---

## 作者：Milkshakefairytale (赞：1)

## 思路分析

首先这道题是不能用二维数组的，因为这个数据范围有点小大而且还会存在负数的情况。

但是好在 $ n_{1} $，$ n_{2} $ 的范围还算可以，我们可以用结构体来做这一道题。

但很明显我们还是不能使用暴力搜索的方法来写这道题目，这样子肯定会 TLE，所以我们要想如何只用一重循环循环就能搞定。

但是这一重循环很明显是要用于搜索的，而不能用于判断条件，但是第三个条件在常规情况下很难不用循环来做。

我们可以尝试进行一个操作，分别按照 x 坐标的大小排序和 y 坐标的大小排序，各搜索一遍，每次都与后面的那一个进行查找是否会互相攻击。
 
这样做我们不用判断出现两颗棋子之间有其它棋子的情况了，我们每次只需要根据排序的结果查找后一颗棋子是否会互相攻击就行了，每次只需要用一个 if 语句就可以了。

 ## AC 代码
 ```cmp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5; 
inline int read()//快读函数 
{
    int s = 0, f = 1;
    char ch = getchar();
    while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while ('0' <= ch && ch <= '9') {s = (s << 3) + (s << 1) + ch - 48; ch = getchar();}
    return s * f;
}
inline void write(int x)//快写函数 
{
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)
		write(x/10);
    putchar(x%10+'0');
}
struct node{
	int team;//所属的阵营，如果属于Prof就是1，如果属于Shou就是2
	int uid;//阵营中的第几个
	int x,y;//坐标 
}a[2*MAXN];
bool cmpX(node xx,node yy)//通过x坐标排序,如果有不懂的那就可以上网自学一下。 
{
	if(xx.x!=yy.x)
	{
		return xx.x<yy.x;
	}
	else
	{
		return xx.y<yy.y;
	}
		
}
bool cmpY(node xx,node yy)//通过y坐标排序 
{
	if(xx.y!=yy.y)
	{
		return xx.y<yy.y;
	}
	else
	{
		return xx.x<yy.x;
	}
}
int ans1[MAXN],ans2[MAXN];//输出字符串 
int n1,n2;
int main()
{
	//读入数据 
	n1=read();
	n2=read();
	for(int i=1;i<=n1;i++)
	{
		a[i].team=1;
		a[i].uid=i;
		a[i].x=read();
		a[i].y=read();
	}
	for(int i=1;i<=n2;i++)
	{
		a[n1+i].team=2;
		a[n1+i].uid=i;
		a[n1+i].x=read();
		a[n1+i].y=read();
	}
	//根据行来排列
	sort(a+1,a+n1+n2+1,cmpX);
	//搜索 
	for(int i=1;i<n1+n2;i++)
	{
		if(a[i].team != a[i+1].team && (a[i].x==a[i+1].x || a[i].y==a[i+1].y))//因为排序的原因，不会出现两颗棋子之间有其它棋子的情况
		{
			//说明两颗棋子之间会相互攻击，那我们需要打上标记
			if(a[i].team==1)
			{
				ans1[a[i].uid]=1;
				ans2[a[i+1].uid]=1;
			}
			else
			{
				ans2[a[i].uid]=1;
				ans1[a[i+1].uid]=1;
			}
		}
	} 
	//再来一遍！这次是根据列来排列 
	sort(a+1,a+n1+n2+1,cmpY);
	//再来搜索！代码和上一次搜索的是一样的 
	for(int i=1;i<n1+n2;i++)
	{
		if(a[i].team != a[i+1].team && (a[i].x==a[i+1].x || a[i].y==a[i+1].y))//因为排序的原因，不会出现两颗棋子之间有其它棋子的情况
		{
			//说明两颗棋子之间会相互攻击，那我们需要打上标记
			if(a[i].team==1)
			{
				ans1[a[i].uid]=1;
				ans2[a[i+1].uid]=1;
			}
			else
			{
				ans2[a[i].uid]=1;
				ans1[a[i+1].uid]=1;
			}	
		}
	} 
	//大功告成，输出！
	for(int i=1;i<=n1;i++)
	{
		write(ans1[i]);
	} 
	printf("\n");
	for(int i=1;i<=n2;i++)
	{
		write(ans2[i]);
	} 
	printf("\n");
	return 0;
}
```

---

## 作者：lyas145 (赞：1)

题目在[这里](https://www.luogu.com.cn/problem/P10821)。

## 解题思路

如果第 $i$ 辆车能攻击到第 $j$ 辆车，那么第 $j$ 辆车也能攻击到第 $i$ 辆车，所以它们就可以互相攻击，这应该很好理解。

然后来看题，车既然只能攻击同一行或同一列上的车，那么我们可以先考虑同一行上能互相攻击到的车，由于一辆车不能跨过其他车来攻击另一辆车，所以一辆车在同一行里只能攻击到**纵坐标比它小且最大的车和纵坐标比它大且最小的车**。看到这里，你应该能想到排序吧？

于是，我们可以以横坐标作为第一关键字，以纵坐标作为第二关键字，把彭教授和寿教授放置的车的坐标放在一块排序。然后从 $1$ 到 $n_1+n_2$ 扫一遍。若此时我们在处理第 $i$ 辆车，那么我们可以看看第 $i-1$ 辆车与第 $i$ 辆车是否在同一行，如果是，并且这两辆车不是同一个人放的，那么它们就可以互相攻击了，然后就记录答案，第 $i+1$ 辆车的处理方式也是一样的。

同一行的搞完了，那么同一列的也不难了，把行和列交换一下就行了。

代码里也有些注释。

### 码儿

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2e5+5,INF=0x3f3f3f3f;
int n1,n2;
char ans[5][N];
struct Node{
	int x,y,id,who;
/*x 和 y 表示横纵坐标，id 表示这是某人放置的第几辆车，
who 表示是谁放的，1 表示彭教授，2 表示寿教授。*/
}c[N<<1];  //这里一定要乘 2！！！因为是把两个教授放置的车放在一起排序
bool cmp1(Node a,Node b) {  //以横坐标为第一关键字、纵坐标为第二关键字排序。
	if (a.x==b.x) {return a.y<b.y;}
	return a.x<b.x;
}
bool cmp2(Node a,Node b) {  //以纵坐标为第一关键字、横坐标为第二关键字排序。
	if (a.y==b.y) {return a.x<b.x;}
	return a.y<b.y;
}
int main() {
	scanf("%d%d",&n1,&n2);
	memset(ans,'0',sizeof ans);  //初始化答案数组。
	for (int i=1;i<=n1;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		c[i]={x,y,i,1};
	}
	for (int i=1;i<=n2;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		c[n1+i]={x,y,i,2};
        //不加 n1 的话彭教授的车的信息就被覆盖了
	}
	c[0].x=c[0].y=INF;
	c[n1+n2+1].x=c[n1+n2+1].y=INF;
    //处理边界，一辆车的横坐标或纵坐标也可能是 0。
    //以横坐标为第一关键字、纵坐标为第二关键字排序。
	sort(c+1,c+1+n1+n2,cmp1);
	for (int i=1;i<=n1+n2;i++) {
		if (c[i-1].x==c[i].x && c[i-1].who!=c[i].who) {
			ans[c[i-1].who][c[i-1].id]=ans[c[i].who][c[i].id]='1';
            //可以互相攻击，记录答案。
		}
		if (c[i].x==c[i+1].x && c[i].who!=c[i+1].who) {
			ans[c[i].who][c[i].id]=ans[c[i+1].who][c[i+1].id]='1';
            //同上
		}
	}
    //以纵坐标为第一关键字、横坐标为第二关键字排序。
	sort(c+1,c+1+n1+n2,cmp2);
	for (int i=1;i<=n1+n2;i++) {
		if (c[i-1].y==c[i].y && c[i-1].who!=c[i].who) {
			ans[c[i-1].who][c[i-1].id]=ans[c[i].who][c[i].id]='1';
		}
		if (c[i].y==c[i+1].y && c[i].who!=c[i+1].who) {
			ans[c[i].who][c[i].id]=ans[c[i+1].who][c[i+1].id]='1';
		}
	}
	for (int i=1;i<=n1;i++) {putchar(ans[1][i]);}
	puts("");
	for (int i=1;i<=n2;i++) {putchar(ans[2][i]);}
	puts("");
	return 0;
}
```

Thanks for reading！

---

## 作者：Little_Raccoon (赞：1)

这是本蒟蒻的第一篇题解，有不足还请大佬指出。
#### 题目大意

二人在一个二维平面上放置车，并判断是否有车会被另一辆车攻击。在以下条件同时成立时，一辆车会被另一辆攻击：

1. 这两辆车不在同一阵营。
2. 这两辆车在同一行或同一列。
3. 这辆车之间没有其他车。

#### 解题思路

我们构建结构体数组，在当中存入每一辆车的横坐标 $x$、纵坐标 $y$、所属阵营 $k$、编号 $idx$。接下来分别把 $x$ 和 $y$ 作为第一关键字进行排序。我们按 $x$ 从小到大排序，如果 $x$ 相等，则按 $y$ 从小到大排序。这样我们就只需要比较当前车辆的信息与排在它之前的车辆的信息就行了，判断他们是否可以互相攻击。再按 $y$ 从小到大排序，如果 $y$ 相等，则按 $x$ 从小到大排序。接着做同样的操作。将两次答案结合起来，前 $n$ 个数是第一行答案，后 $m$ 个数是第二行答案。

#### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[400010];
struct node{
	long long x,y,k,idx;
}a[400010];
bool cmp1(node s,node t){
	if(s.x!=t.x){
		return s.x<t.x;
	}
	else{
		return s.y<t.y;
	}
}
bool cmp2(node s,node t){
	if (s.y!=t.y){
		return s.y<t.y;
	}
	return s.x<t.x;
}
int main(){
	long long n,m;
	cin>>n>>m;
	for(long long i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].idx=i;
		a[i].k=1;
	}
	for(long long i=n+1;i<=n+m;i++){
		cin>>a[i].x>>a[i].y;
		a[i].idx=i;
		a[i].k=2;
	}
	sort(a+1,a+1+n+m,cmp1);
	for(long long i=2;i<=n+m;i++){
		if(a[i-1].x==a[i].x&&a[i].k!=a[i-1].k){
			vis[a[i].idx]=1;
			vis[a[i-1].idx]=1;
		}
	}
	sort(a+1,a+1+n+m,cmp2);
	for(long long i=2;i<=n+m;i++){
		if(a[i-1].y==a[i].y&&a[i].k!=a[i-1].k){
			vis[a[i].idx]=1;
			vis[a[i-1].idx]=1;
		}
	}
	for(long long i=1;i<=n;i++){
		cout<<vis[i];
	}
	cout<<endl;
	for(long long i=n+1;i<=m+n;i++){
		cout<<vis[i];
	}
	return 0;
}
```

---

## 作者：_Hzx_ (赞：1)

【**题目大意**】

有 $n_1$ 个第一阵营的车，$n_2$ 个第二阵营的车。问每个车是否会被攻击。

当满足以下条件时，一个车就会被另一个车攻击。

- 所在阵营不同。

- 在这个平面上的 $x$ 或 $y$ 坐标其中至少一个相等。

- 两个车之间没有其他的车。

---

【**解法**】

按照 $x$ 坐标将每个车排序。实现方法使用结构体加上写比较函数即可。$x$ 相同就对 $y$ 坐标排序。因为排完序后每辆车的坐标从左往右看都是有单调性的。那么就可以两个车两个车的看，然后判断就行。这样做比 $O(n^2)$ 的做法优化了的地方就在于进行了排序，然后就可以将很多不必要的判断省去了。

---

【**核心代码**】

其实会写比较函数的代码这题就会了。

```cpp
bool cmp1(const Info &a, const Info &b) {
	if (a.x != b.x) 
		return a.x < b.x;
	return a.y < b.y;
}

bool cmp2(const Info &a, const Info &b) {
	if (a.y != b.y) 
		return a.y < b.y;
	return a.x < b.x;
}
```

---

## 作者：luckyqwq (赞：1)

# P10821 [EC Final 2020] Rooks 题解

### 大致思路：

这题就是按照题意模拟，有 $n_1$ 辆阵营 $1$ 的车，有 $n_2$ 辆阵营 $2$ 的车，问每辆车是否会被攻击到，首先看到数据范围，第一反应就是离散化，建两个数组 $x, y$，用来存每辆车的坐标，对其进行排序和离散化，根据题意的条件，判断是否会被攻击，对于已经会被攻击的车进行标记，最后统计被标记的数量即可。

### 代码实现：

```
#include <bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
struct node
{
    int id, op, pos;
};
int n, m, x[N], y[N], xx[N], yy[N];
int cnt1, cnt2;
int b1[N << 1], b2[N << 1];
vector<node> X[N], Y[N];
int max_x, max_y;
bool cmp(node x, node y)
{
    return x.pos < y.pos;
}
bool vis1[N], vis2[N];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        b1[++cnt1] = x[i];
        b2[++cnt2] = y[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> xx[i] >> yy[i];
        b1[++cnt1] = xx[i];
        b2[++cnt2] = yy[i];
    }
    sort(b1 + 1, b1 + cnt1 + 1);
    sort(b2 + 1, b2 + cnt2 + 1);
    cnt1 = unique(b1 + 1, b1 + cnt1 + 1) - b1 - 1;
    cnt2 = unique(b2 + 1, b2 + cnt2 + 1) - b2 - 1;
    for (int i = 1; i <= n; i++)
    {
        x[i] = lower_bound(b1 + 1, b1 + cnt1 + 1, x[i]) - b1;
        y[i] = lower_bound(b2 + 1, b2 + cnt2 + 1, y[i]) - b2;
        max_x = max(max_x, x[i]);
        max_y = max(max_y, y[i]);
        X[x[i]].push_back({i, 0, y[i]});
        Y[y[i]].push_back({i, 0, x[i]});
    }
    for (int i = 1; i <= m; i++)
    {
        xx[i] = lower_bound(b1 + 1, b1 + cnt1 + 1, xx[i]) - b1;
        yy[i] = lower_bound(b2 + 1, b2 + cnt2 + 1, yy[i]) - b2;
        max_x = max(max_x, xx[i]);
        max_y = max(max_y, yy[i]);
        X[xx[i]].push_back({i, 1, yy[i]});
        Y[yy[i]].push_back({i, 1, xx[i]});
    }
    for (int i = 1; i <= max_x; i++)
    {
        if (X[i].size() == 0)
            continue;
        sort(X[i].begin(), X[i].end(), cmp);
        int len = X[i].size();
        for (int j = 1; j < len; j++)
        {
            if (X[i][j].op != X[i][j - 1].op)
            {
                if (X[i][j].op)
                    vis2[X[i][j].id] = 1;
                else
                    vis1[X[i][j].id] = 1;
                if (X[i][j - 1].op)
                    vis2[X[i][j - 1].id] = 1;
                else
                    vis1[X[i][j - 1].id] = 1;
            }
        }
    }
    for (int i = 1; i <= max_y; i++)
    {
        if (Y[i].size() == 0)
            continue;
        sort(Y[i].begin(), Y[i].end(), cmp);
        int len = Y[i].size();
        for (int j = 1; j < len; j++)
        {
            if (Y[i][j].op != Y[i][j - 1].op)
            {
                if (Y[i][j].op)
                    vis2[Y[i][j].id] = 1;
                else
                    vis1[Y[i][j].id] = 1;
                if (Y[i][j - 1].op)
                    vis2[Y[i][j - 1].id] = 1;
                else
                    vis1[Y[i][j - 1].id] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << vis1[i];
    }
    cout << "\n";
    for (int i = 1; i <= m; i++)
    {
        cout << vis2[i];
    }
    return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：__O_v_O__ (赞：1)

此题为签到题。

显然，我们需要分别按照 $x$ 坐标和 $y$ 坐标排序，然后处理答案。

下面以 $x$ 坐标为例。

按 $x$ 坐标排序后，依次枚举每一个棋子。如果当前棋子和上一个或下一个棋子 $x$ 或 $y$ 坐标相同，且它们是敌对棋子，则当前棋子被攻击，将答案数组的这一位置为 1。

注意：这里之所以没有考虑有棋子夹在两棋子中间的情况，是因为我们枚举的是相邻棋子，$x$ 坐标和 $y$ 坐标中间都不可能有棋子。

至此，本题结束。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n1,n2,an1[200001],an2[200001];
struct A{bool fl;int id,x,y;};
vector<A>v1,v2;//v1,v2分别存按x,y坐标排序的结果
bool c1(A a,A b){//按x坐标排序
	if(a.x!=b.x)return a.x<b.x;
	else return a.y<b.y;
}bool c2(A a,A b){//按y坐标排序
	if(a.y!=b.y)return a.y<b.y;
	else return a.x<b.x;
}bool pd1(int x,int y){//判断是否x或y坐标相同
	if(v1[x].x==v1[y].x||v1[x].y==v1[y].y)return 1;
	return 0;
}bool pd2(int x,int y){
	if(v2[x].x==v2[y].x||v2[x].y==v2[y].y)return 1;
	return 0;
}signed main(){
	ios::sync_with_stdio(0),cin>>n1>>n2;
	for(int i=1;i<=n1;i++){
		int x,y;cin>>x>>y;
		v1.push_back({0,i,x,y});//存储
		v2.push_back({0,i,x,y});
	}for(int i=1;i<=n2;i++){
		int x,y;cin>>x>>y;
		v1.push_back({1,i,x,y});
		v2.push_back({1,i,x,y});
	}sort(v1.begin(),v1.end(),c1);//排序
	sort(v2.begin(),v2.end(),c2);
	for(int i=0;i<v1.size();i++){
		if(i>0){
			if(v1[i-1].fl!=v1[i].fl&&pd1(i,i-1)){//判断是否是敌对棋子和是否被攻击
				if(v1[i].fl==0)an1[v1[i].id]=1;//记录答案
				else an2[v1[i].id]=1;
			}
		}if(i<v1.size()-1){
			if(v1[i+1].fl!=v1[i].fl&&pd1(i,i+1)){
				if(v1[i].fl==0)an1[v1[i].id]=1;
				else an2[v1[i].id]=1;
			}
		}
	}for(int i=0;i<v2.size();i++){
		if(i>0){
			if(v2[i-1].fl!=v2[i].fl&&pd2(i,i-1)){
				if(v2[i].fl==0)an1[v2[i].id]=1;
				else an2[v2[i].id]=1;
			}
		}if(i<v2.size()-1){
			if(v2[i+1].fl!=v2[i].fl&&pd2(i,i+1)){
				if(v2[i].fl==0)an1[v2[i].id]=1;
				else an2[v2[i].id]=1;
			}
		}
	}for(int i=1;i<=n1;i++)cout<<an1[i];
	cout<<'\n';
	for(int i=1;i<=n2;i++)cout<<an2[i];
	return 0;
}
```

---

## 作者：_Mount_ (赞：0)

本蒟蒻又来交题解了。  
### 1.分析
1. 首先输入并标记棋子的各项信息（横坐标、纵坐标、阵营和序号）。  
2. 然后根据横坐标和纵坐标分别排序，这样就满足了“它们之间的线段上没有别的棋子”的条件。  
3. 接着看相邻的两枚棋子符不符合“它们在一条线上”和“它们在不同的阵营”这两个条件，用标记数组标记符合条件的棋子。  
4. 最后按照要求输出即可。
### 2.实现
程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200000+10;
int n,m;
struct node{
	int x,y,id;
	string op;
}a[N*2];
unordered_map<int,bool>mp;//map代替标记数组

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1;i <= n;i ++) { cin >> a[i].x >> a[i].y;a[i].op = "orz",a[i].id = i; }
	for(int i = 1;i <= m;i ++) { cin >> a[n+i].x >> a[n+i].y;a[n+i].op = "sto",a[n+i].id = n+i; }
	sort(a+1,a+1+n+m,[=](node a,node b)->bool{if(a.x != b.x) return a.x < b.x; else return a.y < b.y;});//Lambda表达式
	for(int i = 2;i <= n+m;i ++){
		if(a[i-1].x == a[i].x && a[i-1].op != a[i].op){
			mp[a[i-1].id] = true,mp[a[i].id] = true;
		}
	}
	sort(a+1,a+1+n+m,[=](node a,node b)->bool{if(a.y != b.y) return a.y < b.y; else return a.x < b.x;});
	for(int i = 2;i <= n+m;i ++){
		if(a[i-1].y == a[i].y && a[i-1].op != a[i].op){
			mp[a[i-1].id] = true,mp[a[i].id] = true;
		}
	}
	for(int i = 1;i <= n;i ++){
		if(mp[i]) putchar('1');//putchar速度更佳
		else putchar('0');
	}
	putchar('\n');
	for(int i = 1;i <= m;i ++){
		if(mp[i+n]) putchar('1');
		else putchar('0');
	}
	return 0;
}
```

---

## 作者：_LTC_Augenstern_ (赞：0)

对于题目，我们可以进行以下推导：
1. 如果在同一行，我们按照$~x~$从小到大排序，那么在同一行的几个数一定在一起，并且在同一行且中间没有间隔其他数的两个坐标在排序后的序列里一定相邻；
2. 若果在同一列：我们按照$~y~$从小到大排序，那么在同一列的几个数一定在一起，并且在同一列且中间没有间隔其他数的两个坐标在排序后的序列里一定相邻；

那么，我们就可以进行如下操作：
1. 输入时记录阵营在输入顺序中的位置
2. 先按$~x~$进行排序，排序后判断相邻的两个元素是否可以互相攻击，如果可以，那么记录在答案数组中；
3. 按$~y~$进行排序，排序后判断相邻的两个元素是否可以互相攻击，如果可以，那么记录在答案数组中；

具体实现：
```cpp
#include <bits/stdc++.h>
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
struct node 
{
	int x, y, num, pos;
};
node nums[4000010];
bool vis1[4000010], vis2[4000010];
bool cmp1(node x, node y) 
{
	if (x.x == y.x) return x.y < y.y;
	else return x.x < y.x;
}
bool cmp2(node x, node y) 
{
	if (x.y == y.y) return x.x < y.x;
	else return x.y < y.y;
}
signed main() 
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) cin >> nums[i].x >> nums[i].y, nums[i].num = 1, nums[i].pos = i;
	for (int i = 1; i <= m; i ++) cin >> nums[i + n].x >> nums[i + n].y, nums[i + n].num = 2, nums[i + n].pos = i;
	sort(nums + 1, nums + n + m + 1, cmp1);
	for (int i = 1; i < n + m; i ++) 
	{
		if (nums[i].x == nums[i + 1].x)
		{
			if (nums[i].num != nums[i + 1].num && nums[i].num == 1) vis1[nums[i].pos] = 1, vis2[nums[i + 1].pos] = 1;
			if (nums[i].num != nums[i + 1].num && nums[i].num == 2) vis2[nums[i].pos] = 1, vis1[nums[i + 1].pos] = 1;
		}			
	}
	sort(nums + 1, nums + n + m + 1, cmp2);
	for (int i = 1; i < n + m; i++) 
	{
		if (nums[i].y == nums[i + 1].y)
		{
			if (nums[i].num != nums[i + 1].num && nums[i].num == 1) vis1[nums[i].pos] = 1, vis2[nums[i + 1].pos] = 1;
			if (nums[i].num != nums[i + 1].num && nums[i].num == 2) vis2[nums[i].pos] = 1, vis1[nums[i + 1].pos] = 1;			
		}			
	}
	for (int i = 1; i <= n; i++) cout << vis1[i];
	cout << endl;
	for (int i = 1; i <= m; i++) cout << vis2[i];
	return 0;
}
```

---

## 作者：M1KuM3yusQAQ (赞：0)

## EC Final 2020 Rooks 题解

四年前的签到题，也是我为数不多能写的水题。

### 题意

Pang 和 Shou 玩游戏。Pang 有 $n_1$ 个棋子，Shou 有 $n_2$ 个棋子。每个棋子在棋盘上的位置都可以用数对 $(x, y)$ 表示（$-10_9 \le x, y \le 10_9$）。

当以下三个条件满足时我们称两个棋子可以互相攻击：

- 两个棋子分别被 Pang 和 Shou 放置。
- 两个棋子在同一列或同一行上（当然，两个棋子不会在同一格上）。
- 两个棋子之间没有其它棋子。

输出两个 01 串来表示 Pang 和 Shou 的每个棋子是否被攻击。

### 思路

$x$ 和 $y$ 能取负数且范围很大，存棋盘用不了二维数组。

易证当同一行的棋子按列升序排列时，相邻两个棋子之间必没有其他棋子。同理，当同一列的棋子按行升序排列时，相邻两个棋子之间必没有其他棋子。

所以我们用结构体存储每个棋子的放置玩家、编号和位置，然后进行按行和按列排序，按顺序两两判断两个棋子是否来自于不同玩家即可。若是，两个棋子就可以互相攻击。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int owner, id;
	int px, py;
} a[400005];

bool cmpByX(Node x, Node y) {
	if (x.px != y.px)
		return x.px < y.px;
	else
		return x.py < y.py;
}

bool cmpByY(Node x, Node y) {
	if (x.py != y.py)
		return x.py < y.py;
	else
		return x.px < y.px;
}

bool res1[200005], res2[200005];
int n1, n2;
int n;

int main() {
	ios::sync_with_stdio(false);
	cin >> n1 >> n2;
	n = n1 + n2;

	for (int i = 1; i <= n1; i++) {
		a[i].owner = 1;
		a[i].id = i;
		cin >> a[i].px >> a[i].py;
	}

	for (int i = n1 + 1; i <= n1 + n2; i++) {
		a[i].owner = 2;
		a[i].id = i - n1;
		cin >> a[i].px >> a[i].py;
	}

	sort(a + 1, a + n + 1, cmpByX);
	for (int i = 1; i <= n - 1; i++) {
		if (a[i].owner != a[i + 1].owner && (a[i].px == a[i + 1].px || a[i].py == a[i + 1].py)) {
			if (a[i].owner == 1)
				res1[a[i].id] = true;
			else
				res2[a[i].id] = true;
			if (a[i + 1].owner == 1)
				res1[a[i + 1].id] = true;
			else
				res2[a[i + 1].id] = true;
		}
	}

	sort(a + 1, a + n + 1, cmpByY);
	for (int i = 1; i <= n - 1; i++) {
		if (a[i].owner != a[i + 1].owner && (a[i].px == a[i + 1].px || a[i].py == a[i + 1].py)) {
			if (a[i].owner == 1)
				res1[a[i].id] = true;
			else
				res2[a[i].id] = true;
			if (a[i + 1].owner == 1)
				res1[a[i + 1].id] = true;
			else
				res2[a[i + 1].id] = true;
		}
	}

	for (int i = 1; i <= n1; i++) {
		if (res1[i])
			cout << 1;
		else
			cout << 0;

	}
	cout << endl;

	for (int i = 1; i <= n2; i++) {
		if (res2[i])
			cout << 1;
		else
			cout << 0;
	}


	return 0;
}

```

希望能帮到各位，请多指教！orz

---

## 作者：smydahaoren (赞：0)

本题为签到题。

### 题目思路

本题思路是根据题意进行模拟。

输入时，将玩家的阵营，次序，两坐标值数据存储在结构体中。然后对 $x$ 轴坐标和 $y$ 轴坐标分别排序，其中相同的 $x$ 坐标则按照 $y$ 坐标顺次排序，反之亦然。这样可以保证所有相邻的汽车都经过遍历，保证答案的正确性。

具体实现时，当相邻两点的玩家 $\text{p}$ 值不相同时，在该 $\text{id}$ 上的答案变成 $1$。
### AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define antirep(i,a,b) for(int i=a;i>=b;i--)
#define speed ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6;
int n1,n2;
bool ans1[N],ans2[N];
struct spot{
	int id,x,y,p;
}a[N],b[N];
bool cmpx(spot n,spot m){
	if(n.x==m.x) return n.y<m.y;
	return n.x<m.x;
}
bool cmpy(spot n,spot m){
	if(n.y==m.y) return n.x<m.x;
	return n.y<m.y;
}
void print(){
	rep(i,1,n1+n2){
		cout<<a[i].p<<" "<<a[i].x<<" "<<a[i].y<<" "<<a[i].id<<endl;
	}
	rep(i,1,n1+n2){
		cout<<b[i].p<<" "<<b[i].x<<" "<<b[i].y<<" "<<b[i].id<<endl;
	}
}
signed main(){
	speed;
	cin>>n1>>n2;
	rep(i,1,n1){
		int x,y;
		cin>>x>>y;
		a[i].x=x,a[i].y=y,a[i].id=i,a[i].p=1;
		b[i].x=x,b[i].y=y,b[i].id=i,b[i].p=1;
	}
	
	rep(i,n1+1,n2+n1){
		int x,y;
		cin>>x>>y;
		a[i].x=x,a[i].y=y,a[i].id=i-n1,a[i].p=2;
		b[i].x=x,b[i].y=y,b[i].id=i-n1,b[i].p=2;
	}
	sort(a+1,a+1+n1+n2,cmpx);
	sort(b+1,b+1+n1+n2,cmpy);
//	print();
	
	rep(i,1,n1+n2){
		int tmp=a[i].p;
		if(i<n1+n2){
			if(a[i+1].p!=tmp&&(a[i+1].x==a[i].x||a[i+1].y==a[i].y))
				if(tmp==1) ans1[a[i].id]=1;
				else ans2[a[i].id]=1;
		}
		if(i!=1){
			if(a[i-1].p!=tmp&&(a[i-1].x==a[i].x||a[i-1].y==a[i].y))
				if(tmp==1) ans1[a[i].id]=1;
				else ans2[a[i].id]=1;
		}
	}
	rep(i,1,n1+n2){
		int tmp=b[i].p;
		if(i<n1+n2){
			if(b[i+1].p!=tmp&&(b[i+1].x==b[i].x||b[i+1].y==b[i].y))
				if(tmp==1) ans1[b[i].id]=1;
				else ans2[b[i].id]=1;
		}
		if(i!=1){
			if(b[i-1].p!=tmp&&(b[i-1].x==b[i].x||b[i-1].y==b[i].y))
				if(tmp==1) ans1[b[i].id]=1;
				else ans2[b[i].id]=1;
		}
	}
	rep(i,1,n1) if(ans1[i]==1) cout<<"1";else cout<<"0";
	cout<<endl;
	rep(i,1,n2) if(ans2[i]==1) cout<<"1";else cout<<"0";
	return 0;
}

```

---

## 作者：cfkk (赞：0)

签到题。 

首先，我们要知道两个棋子会相互攻击的两个条件：
1. 两个棋子在同一行或同一列。
2. 两个棋子属于不同的阵营。

所以，我们可以分别将棋子的 $x$ 和 $y$ 坐标排序，然后判断两个相邻的棋子是否会相互攻击即可。

```cpp
#define maxn 4444444
#define maxm 2222222
struct node{int x,y,player,id;}a[maxn];
bool vis1[maxm],vis2[maxm];
bool cmp1(node s,node b)
{
    if(s.x==b.x)return s.y<b.y;
    else return s.x<b.x;
}
bool cmp2(node s,node b)
{
    if(s.y==b.y)return s.x<b.x;
    else return s.y<b.y;
}
signed main()
{
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));
    int n1=read(),n2=read();
    for(int i=1;i<=n1;i++)a[i].x=read(),a[i].y=read(),a[i].player=1,a[i].id=i;
    for(int i=1;i<=n2;i++)a[i+n1].x=read(),a[i+n1].y=read(),a[i+n1].player=2,a[i+n1].id=i;
    sort(a+1,a+n1+n2+1,cmp1);
    for(int i=1;i<n1+n2;i++)
    {
        if(a[i].x==a[i+1].x)
            if(a[i].player!=a[i+1].player)
                if(a[i].player==1)vis1[a[i].id]=1,vis2[a[i+1].id]=1;
                else vis2[a[i].id]=1,vis1[a[i+1].id]=1;
    }
    sort(a+1,a+n1+n2+1,cmp2);
    for(int i=1;i<n1+n2;i++)
    {
        if(a[i].y==a[i+1].y)
            if(a[i].player!=a[i+1].player)
                if(a[i].player==1)vis1[a[i].id]=1,vis2[a[i+1].id]=1;
                else vis2[a[i].id]=1,vis1[a[i+1].id]=1;
    }
    for(int i=1;i<=n1;i++)print(vis1[i]);pc(1);
    for(int i=1;i<=n2;i++)print(vis2[i]);
    return 0;
}

```

---

