# [NOISG 2025 Finals] 震踏

## 题目描述

Bunnyland 有广阔的田野，Bunnyland 矮兔（一种本地兔子物种）在其中自由活动。其中一个田野可以建模为一个 $10^9 \times 10^9$ 的网格单元。网格的行从北到南编号为 $1$ 到 $10^9$，网格的列从西到东编号为 $1$ 到 $10^9$。我们将网格中位于第 $r$ 行、第 $c$ 列的单元格称为单元格 $(r, c)$。

在这片田野中，有 $n$ 只兔子，编号从 $1$ 到 $n$。第 $i$ 只兔子最初位于单元格 $(r[i], c[i])$。**最初没有两只兔子位于同一个单元格**。

当兔子感到烦躁时，它们会抬起后腿并踢打地面，这一动作被称为震踏。这 $n$ 只兔子将执行一系列 $m$ 次震踏。在第 $j$ 秒开始时，编号为 $t[j]$ 的兔子会进行震踏。当一只兔子震踏时，所有其他兔子都会远离震踏的兔子。

![](https://cdn.luogu.com.cn/upload/image_hosting/1auwto2s.png)

具体来说，当兔子 A 震踏时，兔子 B 将按照以下方式移动：

- 如果 A 和 B 之间的行数小于列数，则 B 将在列方向上远离 A 两列。
- 如果 A 和 B 之间的行数等于列数，则 B 将在列方向和行方向各远离 A 一格。
- 如果 A 和 B 之间的行数大于列数，则 B 将在行方向上远离 A 两行。

可以证明，在震踏发生后，兔子的位置仍然是唯一的。

兔子 Benson 在退休后寻找它的同类，但由于震踏的发生，兔子们四散开来。请帮助 Benson 确定在所有震踏发生后 $n$ 只兔子的最终位置！

可以保证，在震踏序列过程中，兔子不会离开网格。你也可以假设，兔子在任何情况下都不会移动，除了震踏。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq n, m \leq 500\,000$
- 对于所有 $1 \leq i \leq n$，有 $1 \leq r[i], c[i] \leq 10^9$
- 对于所有 $1 \leq j \leq m$，有 $1 \leq t[j] \leq n$
- 对于所有 $i \neq j$，有 $(r_i, c_i) \neq (r_j, c_j)$
- 可以保证，在震踏序列过程中，兔子不会离开网格。

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $18$ | $n, m \leq 2000$ |
| $2$ | $21$ | $r[i] = 1$ |
| $3$ | $32$ | $n \leq 2000$ |
| $4$ | $13$ | $n \leq 100\,000$ |
| $5$ | $16$ | 无 |

### 样例 1 解释

此测试用例适用于子任务 $1, 3, 4, 5$。

兔子 $1$ 处于单元格 $(1, 1)$，兔子 $2$ 处于单元格 $(2, 2)$。

由于兔子 $1$ 和兔子 $2$ 之间的行数等于列数，因此当兔子 $1$ 震踏时，兔子 $2$ 会在东南方向各远离一格，最终到达单元格 $(3, 3)$。震踏的兔子 $1$ 位置保持不变。

### 样例 2 解释

此样例适用于子任务 $1, 3, 4, 5$。

题目中的图示对应于此测试用例。蓝色箭头显示了当编号为 $1$ 的兔子（位于单元格 $(7, 7)$）震踏时，其他兔子的移动方式。

### 样例 3 解释

此样例适用于所有子任务。


## 样例 #1

### 输入

```
2 1
1 1
2 2
1```

### 输出

```
1 1
3 3```

## 样例 #2

### 输入

```
13 1
7 7
3 7
4 4
4 10
5 6
6 4
6 8
8 7
8 10
9 3
9 5
9 9
10 6
1```

### 输出

```
7 7
1 7
3 3
3 11
3 6
6 2
5 9
10 7
8 12
9 1
10 4
10 10
12 6```

## 样例 #3

### 输入

```
3 2
1 10
1 20
1 30
1 3```

### 输出

```
1 8
1 20
1 32```

# 题解

## 作者：_zhangcx (赞：5)

# [P12016 [NOISG 2025 Finals] Thumper](https://www.luogu.com.cn/problem/P12016)

题目大意是有 $m$ 个操作，每个操作给定一个点集中的点，其他点按规则远离这个点一次。

~~首先，暴力可以拿到 18 分的高分。~~

不难发现对于任意两个点，其关系是一定的，即：对于一个点 $x$ 和一个点 $y$，每次点 $x$ Thump 时点 $y$ 的运动方向是一定的。

之后考虑方向问题。一个点的横坐标或纵坐标是否改变取决于它相较于这个操作的点在哪个区域。如图，中间的格子是某一操作的点，则在 $y = x$ 或 $y = -x$ 直线上方格上的点会是斜着走一格，其余格子会按区域的箭头方向走两格。（由于工具所限，此图一个方格对应图中四个灰色小方格，请忽略坐标上的灰色数字，下同）

![](https://cdn.luogu.com.cn/upload/image_hosting/hi20ao4z.png)


斜着的区域显然不好处理。注意到每次操作每个点的曼哈顿距离加 2，无法把横坐标和纵坐标分开来处理，把它变回求切比雪夫距离的类似问题似乎会好做一些，考虑将图旋转 45 度。则点 $(x, y)$ 会变成 $(x + y, x - y)$（不会切比雪夫距离的自行百度）

![](https://cdn.luogu.com.cn/upload/image_hosting/hj0ywxph.png?x-oss-process=image/rotate,45)

（似乎这样看着会舒服一些）

改为以浅蓝线为 $x$ 轴，以红线为 $y$ 轴建系。（你没看错，新建的 y 轴是倒着的）发现：对于一个操作，选定的点为 $p$，则所有横坐标严格比 $p$ 小的点，横坐标减 2；所有横坐标严格比 $p$ 大的点，横坐标加 2；纵坐标亦同理。

于是对于 $x$ 轴和 $y$ 轴在值域上维护一个数据结构记录横坐标或纵坐标的偏移量。每次一个询问需要区间加，询问结束后将每个点的横坐标与纵坐标加上其偏移量，最后将坐标转回来，即将点 $(x', y')$ 转回 $(\frac{x' + y'}{2}, \frac{x' - y'}{2})$，需要单点查。此外，由于值域是 $[-10 ^ 9, 10 ^ 9]$（新坐标可能为负），需要离散化一下。

刚开始用的是线段树，但是 TLE 了，于是卡常，改成树状数组维护差分序列就 AC 了。

个人感觉思考及实现起来有些复杂，评绿似乎有点低了？（~~应该是我太菜了罢~~）

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, t[N];
struct node { int x, y; } a[N];
node aa[N]; // 坐标系旋转45°后的坐标

int orix[N], totx, oriy[N], toty;
void init() {
    for (int i = 1; i <= n; i++) orix[++totx] = aa[i].x;
    sort(orix + 1, orix + n + 1);
    totx = unique(orix + 1, orix + 1 + totx) - (orix + 1);
    for (int i = 1; i <= n; i++) oriy[++toty] = aa[i].y;
    sort(oriy + 1, oriy + n + 1);
    toty = unique(oriy + 1, oriy + 1 + toty) - (oriy + 1);
}
int gethashx(int val) { return lower_bound(orix + 1, orix + totx + 1, val) - orix; };
int gethashy(int val) { return lower_bound(oriy + 1, oriy + toty + 1, val) - oriy; };
// 以上是离散化操作

struct DS {
    int c[N];
    void add(int x, int val, int lim) { if (x == 0) x++; for (int i = x; i <= lim; i += i & -i) c[i] += val; }
    int query(int x) { int res = 0; for (int i = x; i; i -= i & -i) res += c[i]; return res; }
    void update(int x, int y, int val, int lim) { add(x, +val, lim), add(y + 1, -val, lim); }
};
DS X, Y; // 旋转后x坐标和y坐标的偏移量
// 以上为维护偏移量的 DS

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    freopen("thumper.in", "r", stdin);
    freopen("thumper.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= m; i++)
        cin >> t[i];

    for (int i = 1; i <= n; i++) {
        aa[i].x = a[i].x + a[i].y;
        aa[i].y = a[i].x - a[i].y;
    }
    init();

    for (int i = 1; i <= n; i++) {
        aa[i].x = gethashx(aa[i].x);
        aa[i].y = gethashy(aa[i].y);
    }

    for (int i = 1; i <= m; i++) {
        int nx = aa[t[i]].x, ny = aa[t[i]].y;
        X.update(1, nx - 1, -2, totx), X.update(nx + 1, totx, +2, totx);
        Y.update(1, ny - 1, -2, toty), Y.update(ny + 1, toty, +2, toty);
    }
    
    for (int i = 1; i <= n; i++) {
        int nx = X.query(aa[i].x) + orix[aa[i].x],
            ny = Y.query(aa[i].y) + oriy[aa[i].y];
        cout << (nx + ny) / 2 << " " << (nx - ny) / 2 << '\n';
    }
    return 0;
}
```

---

## 作者：Shimarin1001 (赞：2)

### 题目性质
---
不难发现，震踏具有以下性质：

- 任何兔子之间的相对位置不会改变，即：若兔子 $a$ 初始位于兔子 $b$ 的左上方，那么兔子 $a$ 一定不会通过若干次操作到达兔子 $b$ 左下、右上或右下角。
---
### 解法
---
注意到对于第 $i(1≤i≤m)$ 次震踏，第 $t_i$ 只兔子所在的两条斜线将整个平面分为了四部分：
![](https://cdn.luogu.com.cn/upload/image_hosting/88kyzsh5.png)

如果将整个平面顺时针旋转 $45°$，不难发现两条斜线形成了一个以兔子 $t_i$ 为原点的平面直角坐标系，其中原平面中斜方向上的一格是该坐标系中的单位长度。

由于原平面中以**上 $\rightarrow$ 下**为 $r$ 方向正方向，以**左 $\rightarrow$ 右**为 $c$ 方向正方向，为了方便叙述，下文将**左上 $\rightarrow$ 右下**称为 $a$ 方向正方向，将**左下 $\rightarrow$ 右上**称为 $b$ 方向正方向。

那么，可以定义兔子 $j(1≤j≤n)$ 的新坐标 $(a_j,b_j)$：

> $a_j = r_j+c_j$
>
> $b_j = 10^9-r_j+c_j$ 

第 $j$ 只兔子的移动可以被拆解为 $a$ 方向和 $b$ 方向上的移动：

1.  $a$ 方向：
  - 若兔子 $j$ 位于兔子 $t_i$ 上方，则 $a_j \gets a_j-1$。
  - 若兔子 $j$ 位于兔子 $t_i$ 下方，则 $a_j \gets a_j+1$。
2.  $b$ 方向：
  - 若兔子 $j$ 位于兔子 $t_i$ 左侧，则 $b_j \gets b_j-1$。
  - 若兔子 $j$ 位于兔子 $t_i$ 右侧，则 $b_j \gets b_j+1$。

很明显，可以用两个**差分**数组分别维护 $a$ 方向和 $b$ 方向上每次震踏的修改操作，所有震踏进行后再对每个差分数组求前缀和，即可求出每只兔子的最终坐标。

由于有相对位置不会改变的性质，可以将兔子 $j$ 的初始坐标 $a_j$ 和坐标 $b_j$ 存在两个数组中并排序，每次震踏时只记录 $\triangle a_j$ 和 $\triangle b_j$。

震踏进行后，需要把每只兔子 $j$ 坐标 $(a_j',b_j')$ 转化回原平面的坐标 $(r_j',c_j')$：

1.  $a$ 坐标：

 $a$ 方向正方向上的移动，实际上是在原图中向右下方移动，因此：
> $r_j \gets r_j+\triangle a_j$
>
> $c_j \gets c_j+\triangle a_j$ 

2.  $b$ 坐标：

 $b$ 方向正方向上的移动，实际上是在原图中向右上方移动，因此：
> $r_j \gets r_j-\triangle b_j$
>
> $c_j \gets c_j+\triangle b_j$ 

---
### 代码
---

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5,INF=1e9;
struct rabbit{int r,c;}r[MAXN];
struct line{
	int k,sp;//k:坐标  sp:兔子编号 
	bool operator<(const line &a)const{return k<a.k;}
	bool operator<=(const line &a)const{return k<=a.k;}
};
int n,m,cfa[MAXN],cfb[MAXN],_a[MAXN],_b[MAXN];
//cfa/cfb:维护a/b坐标变化量的差分数组  _a/_b:最终a/b坐标的变化量 
vector<line> a,b;
//a/b:记录每只兔子初始时的a/b坐标 
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>r[i].r>>r[i].c;
		a.push_back((line){r[i].r+r[i].c,i});
		b.push_back((line){INF-r[i].r+r[i].c,i});
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	for(int i=1,t;i<=m;i++){
		cin>>t;
		int kta=r[t].r+r[t].c,ktb=INF-r[t].r+r[t].c;
		//kta/ktb:第t_i只兔子的a/b坐标 
		int la=lower_bound(a.begin(),a.end(),(line){kta,1})-a.begin(),
		ra=upper_bound(a.begin(),a.end(),(line){kta,1})-a.begin(),
		lb=lower_bound(b.begin(),b.end(),(line){ktb,1})-b.begin(),
		rb=upper_bound(b.begin(),b.end(),(line){ktb,1})-b.begin();
		cfa[0]+=-1,cfa[la]+=1;
		cfa[ra]+=1,cfa[n]+=-1;
		cfb[0]+=-1,cfb[lb]+=1;
		cfb[rb]+=1,cfb[n]+=-1;
	}
	for(int i=0;i<n;i++){
		cfa[i]+=cfa[i-1],cfb[i]+=cfb[i-1];
		_a[a[i].sp]=cfa[i],_b[b[i].sp]=cfb[i];
	}
	for(int i=1;i<=n;i++){
		r[i].r+=_a[i]-_b[i];
		r[i].c+=_a[i]+_b[i];
		cout<<r[i].r<<" "<<r[i].c<<endl; 
	}
}
```
[AC记录](https://www.luogu.com.cn/record/212746166)

---
### 后记
---

作为首批参加NOISG的国内选手，在考场上我维护了两棵线段树，导致了最后一个点超时。提醒各位，**注意常数优化**。

---

## 作者：快斗游鹿 (赞：2)

首先有个关键结论：**无论操作几次，所有点之间的“相对关系”永远不会变**。这里的“相对关系”指的是两点行距和列距的相对大小。证明分讨一下即可。知道这点后，考虑某只兔子发怒会带来的影响，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/strj41x3.png)

这不是很好维护。但是套路地，可以把整个坐标轴转 $45$ 度，然后就可以方便地使用差分分别维护行列变化了。具体地，让 $(x,y)\to (x+y,x-y)$，则 $(x,y)\to(x+1,y+1)$ 的操作会表现为 $(x+y,x-y)\to(x+y+2,x-y)$，其他以此类推。总时间复杂度 $O(n\log n)$，瓶颈在离散化。

---

## 作者：LastKismet (赞：2)

首先我们发现一个性质，一次操作后，所有兔子的相对位置关系不变。所以每个兔子会影响哪些兔子一开始就固定了。我们可以忽略位置变化，这样更新贡献会简单很多。

我们考虑存储所有兔子左右与上下的位移次数，最后一次计算位置即可。

考虑对横轴和纵轴分别开一棵线段树，然后每次操作在线段树上区间修改+单点修改即可。为了方便，我们旋转坐标系（这样只需要分别处理四个象限和坐标轴即可），然后离散化坐标，对坐标建线段树。具体的操作位置影响是繁琐但简单的，这里不做过多解释。

最后每个节点只需要找对应横坐标和纵坐标分别受到了哪些影响，然后在自己原始坐标的基础上移动即可。

---

## 作者：hanyu0722 (赞：1)

### 题目链接    

[P12016 [NOISG 2025 Finals] 震踏](https://www.luogu.com.cn/problem/P12016)

### 闲话

~~学化学学魔怔了读题的时候总念成振荡~~

~~截至我提交题解时我的代码还是最短代码~~

### 题目思路

~~这题根本不用树状数组！~~  
二分大法好！

发现一个性质这题就好做了。   
震踏操作在某种意义上可看作等比例缩放，所以震踏后每只兔子的相对位置不变，这里相对位置指两只兔子行数与列数的关系。  
因此，震踏满足交换律，也就是说即使我们打乱震踏的顺序，答案依然正确。

所以我们可以对于每只兔子，计算震踏对其的影响。由于整个网格被两条**斜线**划分成几个区域，并不好处理，可以将整体旋转45度，兔子的位置由 $(x,y)$ 变为 $(x+y,x-y)$。   
对于旋转之后的图像而言，如果一只兔子右侧（指横坐标大于其横坐标）有一只震踏的兔子，那么它将向左移动一个单位长度。左侧、上方、下方同理。

那该如何判断一只兔子右侧有几只震踏的兔子呢？容易想到，将震踏的兔子的横坐标构建数组并排序，二分求解即可。左侧、上方、下方同理。

注意输出时需将坐标再转换回来。

时间复杂度为 $O(n \log{m} + m \log{m})$。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int xq[500005];
int yq[500005];
struct rabbit{
	int x;
	int y;
} a[500005]; 
signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[i].x=x+y;
		a[i].y=x-y; 
	}
	for (int i=1;i<=m;i++){
		int o;
		cin>>o;
		xq[i]=a[o].x;
		yq[i]=a[o].y;
	}
	sort(xq+1,xq+1+m);
	sort(yq+1,yq+1+m);
	for (int i=1;i<=n;i++){
		int xl=lower_bound(xq+1,xq+1+m,a[i].x)-xq-1;
		int xu=upper_bound(xq+1,xq+1+m,a[i].x)-xq;
		int yl=lower_bound(yq+1,yq+1+m,a[i].y)-yq-1;
		int yu=upper_bound(yq+1,yq+1+m,a[i].y)-yq;
		a[i].x-=(m-xu+1)*2;
		a[i].x+=xl*2;
		a[i].y-=(m-yu+1)*2;
		a[i].y+=yl*2;
	}
	for (int i=1;i<=n;i++){
		printf("%lld %lld\n",(a[i].x+a[i].y)/2,(a[i].x-a[i].y)/2);
	}
	return 0;
}
```

---

