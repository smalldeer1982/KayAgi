# [ABC373G] No Cross Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc373/tasks/abc373_g

$ 2 $ 次元平面上に $ P_1,P_2,\ldots,P_N,\ Q_1,Q_2,\ldots,Q_N $ の $ 2N $ 個の点があります。 $ P_i $ の座標は $ (A_i,B_i) $、$ Q_i $ の座標は $ (C_i,D_i) $ です。 同一直線上に異なる $ 3 $ 点が存在することはありません。

$ (1,2,\ldots,N) $ の順列であるような数列 $ R=(R_1,R_2,\ldots,R_N) $ であって以下の条件を満たすような $ R $ が存在するか判定し、存在する場合は $ 1 $ つ求めてください。

- $ 1 $ 以上 $ N $ 以下のすべての整数 $ i $ について 線分 $ i $ を $ P_i $ と $ Q_{R_i} $ を端点とする線分としたとき、どの線分 $ i $ と線分 $ j $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $ も互いに交差しない。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 0\ \leq\ A_i,B_i,C_i,D_i\ \leq\ 5000 $ $ (1\ \leq\ i\ \leq\ N) $
- $ (A_i,B_i)\ \neq\ (A_j,B_j) $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $
- $ (C_i,D_i)\ \neq\ (C_j,D_j) $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $
- $ (A_i,B_i)\ \neq\ (C_j,D_j) $ $ (1\ \leq\ i,j\ \leq\ N) $
- 同一直線上に異なる $ 3 $ 点が存在することはない
- 入力はすべて整数

### Sample Explanation 1

以下の図のように点が並んでいます。 !\[\](https://img.atcoder.jp/abc373/G-sample.png)$ R=(2,1,3) $ とすることで $ 3 $ 本の線分は互いに交差しません。また、 $ R $ を $ (1,2,3),(1,3,2),(2,3,1),(3,1,2) $ のいずれにしても正しい答えとなります。

## 样例 #1

### 输入

```
3
0 0
2 4
4 2
0 2
2 0
4 4```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
8
59 85
60 57
72 12
3 27
16 58
41 94
77 64
97 20
32 37
7 2
57 94
35 70
38 60
97 100
5 76
38 8```

### 输出

```
3 5 8 2 7 4 6 1```

# 题解

## 作者：RAYMOND_7 (赞：6)

搬一下官方题解的证明

![](https://cdn.luogu.com.cn/upload/image_hosting/p3rpm0eb.png)

手画一下可以发现，交叉一定会导致总距离增大，这样可以转化为求匹配距离和最小，因为交点多距离小总可以**调整**为交点减少距离也变小。

结论是：距离最小的方案一定是要求的合法解之一。

直接跑最小费用流即可，或者偷懒写个调整法，$n \le 300$ 所以能过。

调整法跑的非常快，最大点跑了 $4 \text{ms}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define For(i, l, r) for(int i = l; i <= r; i ++)

const int N = 310;

int n, m, a[N], b[N], c[N], d[N], p[N];

double PF(double x) {return x * x;}

double dis(int i, int j)
{
	return sqrt(PF(a[i] - c[j]) + PF(b[i] - d[j]));
}

int main()
{
	cin >> n;
	For(i, 1, n) cin >> a[i] >> b[i];
	For(i, 1, n) cin >> c[i] >> d[i];
	For(i, 1, n) p[i] = i;
	while(1)
	{
		int oper = 0;
		For(i, 1, n) For(j, 1, i - 1)
		{
			if(dis(i, p[j]) + dis(j, p[i]) < dis(i, p[i]) + dis(j, p[j]))
			{
				oper = 1;
				swap(p[i], p[j]);
			}
		}
		if(!oper) break;
	}
	For(i, 1, n) printf("%d ", p[i]);
	return 0;
}

```

---

## 作者：yemuzhe (赞：4)

[题目传送门](/problem/AT_abc373_g)

### 解题思路

不正经但能暴标的做法。

考虑将所有点按**双关键字排序**（先按 $x$ 坐标排，再按 $y$ 坐标排），我们不妨观察一下排序后第 $1$ 个点要怎么配对。

![](https://cdn.luogu.com.cn/upload/image_hosting/gi9jljgt.png)

就像上图一样，我们以第 $1$ 个点（实心黄点）为原点建立**极坐标系**。

因为题目保证没有三点共线，所以所有点的极坐标均不同。

好了，就来发掘一下与之配对的红点（即第 $1$ 个点的异色点）满足的条件。

**一个红点满足条件当且仅当它与第 $1$ 个点的连线一侧的红点黑点数量相同；另一侧同理。**

显然这样做是对的，因为这样我们就可以把点**分成独立的两部分并分治下去**。红黑数量相同保证可以两两配对。

如何证明一定能找到这样的一个红点？大概相当于把极坐标离散化到 $1 \sim m$ 然后做前缀和，其中黑点权值 $-1$、红点权值 $+ 1$。然后可以发现必有一次操作使前缀和从 $0$ 变成 $1$。

故我们只需要这样分治下去总能找到一组解。

时间复杂度：最坏 $O \left(n ^ 2 \log n\right)$。

### AC Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 605
using namespace std;

int n, ans[N];

struct point {int x, y, id; bool c;} a[N];

void solve (int l, int r)
{
	if (l > r) return ;
	sort (a + l, a + r + 1, [&](point x, point y) -> bool // 双关键字排序
	{
		return x.x != y.x ? x.x < y.x : x.y < y.y;
	});
	sort (a + l + 1, a + r + 1, [&](point x, point y) -> bool // 极坐标排序
	{
		return atan2 (x.y - a[l].y, x.x - a[l].x) < atan2 (y.y - a[l].y, y.x - a[l].x);
	});
	for (int i = l + 1, sum = 0; i <= r; i ++)
	{
		sum += a[i].c != a[l].c ? 1 : -1; // 计算前缀和
		if (sum == 1) // 当前缀和第 1 次变为 1 时，说明此时一定是满足条件的红点
		{
			if (a[l].c) ans[a[i].id] = a[l].id;
			else ans[a[l].id] = a[i].id;
			return solve (l + 1, i - 1), solve (i + 1, r); // 继续分治，然后退出
		}
	}
	return ;
}

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf ("%d%d", &a[i].x, &a[i].y), a[i].id = i, a[i].c = 0;
	}
	for (int i = n + 1; i <= n * 2; i ++)
	{
		scanf ("%d%d", &a[i].x, &a[i].y), a[i].id = i - n, a[i].c = 1;
	}
	solve (1, n * 2);
	for (int i = 1; i <= n; i ++)
	{
		printf ("%d ", ans[i]);
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：2)

一道巧妙的几何相关构造题。


------------


对所有点的纵坐标进行排序，取纵坐标最小的点作为原点，这样就可以保证其他点落在一二象限了。然后再进行极角排序算一下相对位置。

因为要求所有连线不相交，故可以考虑以两点为分界，使得分界线左边刚好两两匹配，右边两两匹配。这样就可以保证左右的线不会跨过分界线了。注意选取分界线的时候要保证分界线左右两边各自的黑白点数量相同。

暴力枚举分界线，然后两侧递归求解即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
struct node{
    int x,y,col,id;
    bool operator < (const node &rhs) const { return y<rhs.y; }
	node operator - (const node &rhs) const { return (node){x-rhs.x,y-rhs.y,col,id}; }
}c[maxn];
int ans[maxn],n;
bool cmp(node a,node b){ return atan2(a.x,a.y)>=atan2(b.x,b.y); }
void solve(int l,int r){
    if(l>=r) return ;
    sort(c+l,c+r+1);
    for(int i=l+1;i<=r;i++) c[i]=c[i]-c[l];
    sort(c+l+1,c+r+1,cmp); int cnt=0;
    for(int i=l+1;i<=r;i++){
        if(cnt==0&&(c[l].col^c[i].col)){
            if(c[l].col) ans[c[i].id]=c[l].id;
			else ans[c[l].id]=c[i].id;
            solve(l+1,i-1); solve(i+1,r);
            return ;
        }
        cnt+=(c[i].col?-1:1);
    }
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    while(cin>>n){
        for(int i=1;i<=2*n;i++){
        	cin>>c[i].x>>c[i].y;
    		c[i].col=((i-1)/n)?1:0; c[i].id=(i-1)%n+1;
		}
        solve(1,2*n);
        for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
        cout<<endl;
	}
    return 0;
}
```

---

## 作者：g1ove (赞：2)

神秘 Trick 题。解法来自官方题解。

结论：所有两两连边的线段之和最短时为一种合法方案。

考虑调整法，若两条线段交叉了，可以将其调整为不相交，**且这两条线段长度之和一定会变小**，将所有相交的线段不断进行调整后，一定会存在一种合法方案。

那么，对于总线段和最小的一种方案，它一定是合法的。

因此，分成两部分点，点之间两两连边表示距离，题目就变成二分图最小权完美匹配，跑最最小费用最大流即可。

[Submission](https://atcoder.jp/contests/abc373/submissions/58254718)

---

## 作者：Eric998 (赞：1)

好题啊。标准的 AT 场上切不掉，模拟赛场上随便切的 Ad-hoc。

我们考察只有两对点的情况的特殊性质，设为红点 $A,B$，蓝点 $C,D$。发现若 $AC,BD$ 有交点 $O$，则 $AD+BC<AO+BO+CO+DO=AC+BD$。所以，当前的方案产生了交点等价于连接方案非最短。

我们考虑在一个已经为最优的点集 $R_1,R_2,\dots,R_n,B_1,B_2,\dots,B_n$ 中加入一对点 $X,Y$。注意到对每对点如上调整，则可以获得新的最优解，并且没有交点。因此，我们归纳地证明了连接总长最短的方案一定合法。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 305
#define int long long
int a[N], b[N], c[N], d[N], p[N], n, opt;
#define dis(l,r) sqrt((a[l]-c[r])*(a[l]-c[r])+(b[l]-d[r])*(b[l]-d[r]))

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	for (int i = 1; i <= n; i++)
		cin >> c[i] >> d[i];
	for (int i = 1; i <= n; i++)
		p[i] = i;
	do {
		opt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (dis(i, p[i]) + dis(j, p[j]) > dis(i, p[j]) + dis(j, p[i]))
					swap(p[i], p[j]), opt++;
	} while (opt);
	for (int i = 1; i <= n; i++)
		cout << p[i] << ' ';
}
```

据上述结论，复杂度 $n^3$。

---

## 作者：happy_dengziyue (赞：1)

### -1 三倍经验

[P5936](https://www.luogu.com.cn/problem/P5936)，[CF958E3](https://www.luogu.com.cn/problem/CF958E3)，[UVA1411](https://www.luogu.com.cn/problem/UVA1411)。

~~能够一次原了这么多题也是有点实力的。~~

### 1 思路

前置提醒：

+ 题目保证不存在三点共线；

+ 以下认为我们会 $\Theta(1)$ 地判断两条线段是否相交，不会的可以自行学习如何利用直线一般式判断；

+ 我们将两种点分别称为“黑点”和“白点”，将连一条线段看作匹配。

我们可以想到一个最暴力的做法：随机给一种匹配方案，然后枚举哪两条线段相交。如果相交了（例如 AB 交 CD），就交换顶点（即变为 AD 和 CB），显然 AD 和 CB 不交。多轮枚举直到不存在相交的线段。

然后就 AC 了（真的可以），~~题解到此结束。~~

考虑证明。显然，如果两线段相交，交换顶点后，所有线段的总长度一定是严格递减的。而线段总长度最小的匹配方案一定是存在的，所以这个匹配方案一定满足线段之间无交。

由此可以证明，本题一定有解，并且这个暴力做法不会陷入死循环。但笔者不会证明这个暴力做法时间复杂度的正确性，欢迎读者补充。

不过存在一个时间复杂度正确的做法：注意到用最小费用最大流即可轻松找出那个线段总长度最小的方案。这个做法甚至不需要判断两线段是否相交。

### 2 代码与记录

[暴力做法](https://atcoder.jp/contests/abc373/submissions/58216316)

By **dengziyue**

---

## 作者：封禁用户 (赞：1)

刚学完 KM，写一发 KM 算法解。顺带一提，你们费用流真不怕被卡？

首先，假如两线段 $P_1Q_1$ 交 $P_2Q_2$ 于 $T$，由于不存在三点共线或者两点重合，很明显据三角形边的关系，$|P_1Q_1|+|P_2Q_2|=|P_1T|+|Q_1T|+|P_2T|+|Q_2T|>|P_1Q_2|+|P_2Q_1|$，也就是说我们可以对于每个存在相交线段的配对，找到一个**线段长度总和**小于它的另一个配对。

反证法易得，线段长度总和最小的配对必然没有相交线段（否则交换其中一组相交线段的配对方法，长度和会减小，矛盾）。于是，不可以总司令会直接 $\text{WA 47}$ 个，我们不用想着判 $-1$ 了，同时问题转化为找到线段长度总和最小的配对。

建立二分图，其中左部 $n$ 个点分别象征 $P_1,\dots,P_n$，右部 $n$ 个点分别象征 $Q_1,\dots,Q_n$，而 $e_{i,j}=B-|P_iQ_j|$，其中 $B$ 为一个相对大的值，不能小于 $5000\sqrt{2}$。然后跑专长最大带权匹配的 KM 即可。时间复杂度 $O(n^3)$。

```cpp
//My AtCoder account is ultvoW_mEden
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T,n,m,edg,pre[505],lnk[505],npy[505],editx[505],edity[505],pt1,ans;
double Xf[505],Yf[505],Xs[505],Ys[505],a[505][505],should_we_split[505],expx[505],expy[505],infn=1e8,eps=1e-12;

void let_us_get_married(int now){
	int nxt;
	while(now){
		nxt=lnk[pre[now]];lnk[pre[now]]=now;
		npy[now]=pre[now];now=nxt;
	}
}

void had_alex_ever_popped_the_question_to_alisa(int ilE){
	queue<int>q;while(!q.empty())q.pop();q.push(ilE);
	for(int j=1;j<=m;j++){
		should_we_split[j]=infn;
	}pt1++;
	while(1){
		while(!q.empty()){
			int now=q.front();q.pop();editx[now]=pt1;
			for(int nxt=1;nxt<=m;nxt++){
				if(edity[nxt]!=pt1){
					double cur=expx[now]+expy[nxt]-a[now][nxt];
					if(cur<should_we_split[nxt]-eps){
						pre[nxt]=now;should_we_split[nxt]=cur;
						if(abs(cur)<eps){
							edity[nxt]=pt1;
							if(npy[nxt])q.push(npy[nxt]);
							else{
								let_us_get_married(nxt);
								return;
							}
						}
					}
				}
			}
		}
		double Delt=infn;
		for(int i=1;i<=m;i++){
			if(edity[i]!=pt1)Delt=min(Delt,should_we_split[i]);
		}
		for(int i=1;i<=n;i++){
			if(editx[i]==pt1)expx[i]-=Delt;
		}
		for(int i=1;i<=m;i++){
			if(edity[i]==pt1)expy[i]+=Delt;
			else should_we_split[i]-=Delt;
		}
		for(int nxt=1;nxt<=m;nxt++){
			if(edity[nxt]!=pt1&&abs(should_we_split[nxt])<eps){
				edity[nxt]=pt1;
				if(npy[nxt])q.push(npy[nxt]);
				else{
					let_us_get_married(nxt);
					return;
				}
			}
		}
	}
}

signed main(){
	cin.tie();ios::sync_with_stdio(0);
	cin>>n;m=n;
	for(int i=1;i<=n;i++){
		cin>>Xf[i]>>Yf[i];
	}
	for(int i=1;i<=m;i++){
		cin>>Xs[i]>>Ys[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			double Dx=Xf[i]-Xs[j],Dy=Yf[i]-Ys[j];
			a[i][j]=1e4-sqrt(Dx*Dx+Dy*Dy);expx[i]=max(expx[i],a[i][j]);
		}
		cout<<endl;
	}
	for(int i=1;i<=n;i++){
		had_alex_ever_popped_the_question_to_alisa(i);
	}
	for(int i=1;i<=n;i++){
		cout<<lnk[i];
		if(i!=n)cout<<' ';
	}
	return 0;
}
```

**后记：正在学 KM 算法的同学可以借鉴别人/我的代码，但是请不要脑子都不过一遍地直接抄袭。**

---

## 作者：lzh0220 (赞：0)

## 题意

给定二维平面上 $n$ 个红点和 $n$ 个黑点，将他们两两匹配形成若干条线段，使得任意两条线段不交，求方案。

## 分析

看到很多大佬用网络流做，但是我不太会。

首先多画几个图就不难发现不会出现无解的情况（一会给出的构造方案也可说明）。

先将未匹配的所有点按 $x$，$y$ 坐标双关键字排序。然后我们可以取 $x$ 坐标最小的点（若有多个，则取 $y$ 坐标最小的点）为特殊点，将其余所有未匹配的点与他连线，按线段斜率大小升序排序。由于不存在三点共线，因此每条线段的斜率均不同。

接着按顺序遍历这些点。当找到一个点使得这个点与特殊点的连线将未匹配的点分为上下两部分，且上下两部分中红黑点数量分别相同时，则连接这条线段，然后将上下两部分递归求解。容易证明这种构造方案一定符合条件。

时间复杂度 $O(n^2\log n)$。

[code](https://www.luogu.com.cn/paste/5eoa3k3q)

---

## 作者：_Kenma_ (赞：0)

## 前言

调整法真是好东西。

推销博客：[here.](https://www.cnblogs.com/kenma)

## 思路分析

如果你网络流题做得比较多的话，应该能感觉出来这道题有点像。

经过若干手摸，发现根本不存在无解的情况。

每次交叉时，我们一定可以将交叉的两条路径分开，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kwkq2ojv.png)

同时，根据四边形不等式，有蓝线段长度之和大于黄线段长度之和。

因此，我们发现，一定存在一种合法方案，使得连线线段长度之和最小。

最小化线段长度之和是二分图最大权匹配，但是 $n=300$ 还是不要写 dinic 的好。

既然担心费用流被卡，那就写调整法吧。

具体地，我们初始设 $p_i=i$，然后每一轮调整，我们枚举所有 $(i,j)$，如果交换更优就交换。

根据二分图增广的相关知识，我们调整的轮数不会超过 $n$，总体复杂度为 $O(n^3)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const long double eps=1e-12;
int n,m,t,p[305],a[305],b[305],x[305],y[305];
long double dis(int i,int j){
	return sqrt(1.0*(x[i]-a[j])*(x[i]-a[j])+1.0*(y[i]-b[j])*(y[i]-b[j]));
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++){
		p[i]=i;
	}
	t=2*n;
	while(t--){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dis(i,p[i])+dis(j,p[j])-eps>dis(i,p[j])+dis(j,p[i])) swap(p[i],p[j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<p[i]<<' ';
	}
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

分享一种神奇的能过的做法。

令 $p_i\rightarrow q_{a_i}$，最初令 $a_i=i$。

考虑一种大乱斗操作：枚举 $i$ 和 $j$，如果 $p_i\rightarrow q_{a_i}$ 和 $p_j\rightarrow q_{a_j}$ 相交，则交换 $a_i$ 和 $a_j$。

显然这样进行完一波之后并不能保证任意两个不交，因此就考虑一直操作直到不存在相交为止。

我随便拍几组就拍出问题了（可能一直卡在同一个状态不变），但是确实能过。。。


```cpp
int qnq=1,cnt=0;
while(qnq){
	qnq=0;
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)
		if(crs(p[i],q[ans[i]],p[j],q[ans[j]]))swap(ans[i],ans[j]),qnq=1;
	++cnt;
}
cerr<<cnt<<"\n";
for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
```

---

## 作者：KMYC (赞：0)

二分图匹配，将 $n^4$ 个交点建出来，然后用链将需要连接的两个点和线上的所有交点全部连起来，并要求交点的流量不超过 $1$，跑普通的二分图匹配。

平面上如果两条线有交点，则我们需要交其调整为没有交点得两条线：

即将图 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ki2j6mh.png)

变为图 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/1b5uy6li.png)

由四边形不等式得：如果现在存在一组匹配，我们可以将其调整使得长度和更小的话，一定可以直接调整，肯定合法。

然后连边，做二分图最大权匹配即可。

---

## 作者：tanzexiaodezhonghao (赞：0)

# 思路
首先提供翻译（[来源](https://www.cnblogs.com/caijianhong/p/18438504/solution-ABC373G)）：
> 年轻的自然主义者比尔在学校里研究蚂蚁。他的蚂蚁以生活在苹果树上的蚜虫为食。每个蚂蚁群需要自己的苹果树来养活自己。比尔有一张地图，上面标有 $n$ 个蚂蚁群和 $n$ 棵苹果树的坐标。他知道蚂蚁从它们的蚂蚁群到它们的取食地点，然后返回蚂蚁群，都是使用化学标记的路线。这些路线不能相交，否则蚂蚁会迷失方向，到达错误的蚂蚁群或树，从而引发蚂蚁群之间的战争。比尔希望将每个蚂蚁群连接到单独的苹果树，使得所有的 $n$ 条路线都是不相交的直线。在这个问题中，这样的连接总是可能的。

接下来可以发现，如果两点线路有交叉会导致距离增大，则交叉数量越多越不优。我们可以尝试费用流。我么不考虑数据卡常问题。那么，最小的距离一定是合法的。然后套距离公式 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define zhouxi2022HZO int
#define genshin ios::sync_with_stdio(0);cin.tie(0);
const zhouxi2022HZO N=114514;
zhouxi2022HZO n,m,flag=1;
ll a[N],b[N],c[N],d[N],f[N];
void init(){
    for(zhouxi2022HZO i=1;i<=n;i++) f[i]=i;
    return ;
}
double dis(zhouxi2022HZO u,zhouxi2022HZO v){return sqrt((a[u]-c[v])*(a[u]-c[v])+(b[u]-d[v])*(b[u]-d[v]));}
int main(){
    genshin;
	cin>>n;
    init();
	for(zhouxi2022HZO i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(zhouxi2022HZO i=1;i<=n;i++) cin>>c[i]>>d[i];
	while(flag!=0){
		flag=0;
		for(zhouxi2022HZO i=1;i<=n;i++){
            for(zhouxi2022HZO j=1;j<i;j++){
                if(dis(i,f[i])+dis(j,f[j])>dis(i,f[j])+dis(j,f[i])){
                    flag=1;
                    swap(f[i],f[j]);
                }
            }
        }
	}
	for(zhouxi2022HZO i=1;i<=n;i++) cout<<f[i]<<" ";
    cout<<"\n";
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

考虑两个线段相交，我们交换一下端点，那么距离肯定会变小。

我们从而想到，如果我们保证了匹配之后两点之间距离最小，那么线段就应该是不相交的（否则两点距离之和可以更小）。

因此我们直接跑 $n$ 轮排序，每轮都找所有的 $i,j(i<j)$ 看看能不能更优就行了。

至于正确性可以考虑一个点换人最多换 $n$ 次。

时间复杂度为 $\mathcal O(n^3)$。


```cpp
#include<bits/stdc++.h>
#define LL long long
#define p pair<LL,LL>
#define X first
#define Y second
using namespace std;
const int N=305;
int n,P[N];
p A[N],B[N];
double D(p A,p B){return sqrt((A.X-B.X)*(A.X-B.X)+(A.Y-B.Y)*(A.Y-B.Y));}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)P[i]=i;
	for(int i=1;i<=n;i++)cin>>A[i].X>>A[i].Y;
	for(int i=1;i<=n;i++)cin>>B[i].X>>B[i].Y;
	for(int T=1;T<=n;T++)
	{
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(D(A[i],B[P[i]])+D(A[j],B[P[j]])>D(A[i],B[P[j]])+D(A[j],B[P[i]]))swap(P[i],P[j]);
		}
	}
	for(int i=1;i<=n;i++)cout<<P[i]<<' ';
}
```

---

