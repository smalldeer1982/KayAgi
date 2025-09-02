# [IOI 2016] aliens

## 题目描述

我们的卫星刚刚通过观测一个遥远的星球发现了外星文明。我们也已经获得了该星球的一个正方形区域的低分辨率照片。这个照片上有许多智能生命的迹象。专家们也已经确定了照片上的 $n$ 个兴趣点。这些兴趣点被编号为 $0$ 到 $n−1$。现在我们希望拍摄一些能包含全部 $n$ 个兴趣点的高分辨率照片。

卫星已将低分辨率照片的区域划分成由 $m \times m$ 个单位正方形的小方格组成的网络。网格的行和列被连续地编号为 $0$ 到 $m−1$（从上到下和从左到右）。我们用坐标 $(s,t)$ 来表示第 $s$ 行与第 $t$ 列上的小方格。第 $i$ 个兴趣点位于小方格 $(r_i,c_i)$ 上，每个小方格子上可以包含任意多个兴趣点。

卫星在一个固定的轨道上运行，而它刚好也直接经过这个网格的主对角线的上方。主对角线就是指在网络中连接左上角和右下角的那条线段。卫星能够在任意的区域上拍摄高分辨率的照片，但必须满足以下条件：

- 拍摄的区域必须是正方形。
- 这个正方形的两个对角（注：变通理解为主对角线）全部包含在网格的主对角线中。
- 网格中的每个小方格或者完全在拍摄范围内，或者完全在拍摄范围外。
卫星最多只能拍摄 $k$ 张高分辨率照片。

一旦卫星拍摄完成，它将把每个拍摄区域的高分辨率照片传送到地面基站（无论这些区域是否包含兴趣点）。尽管一个小方格可能会被多次拍摄，但每个被拍摄到的小方格上的数据只会被传送一次。

因此，我们必须选择最多 $k$ 个正方形区域进行拍摄，而且要保证：

- 每个包含至少一个兴趣点的小方格必须被至少拍摄到一次
- 被拍摄到至少一次的小方格数目必须是最小的。

你的任务就是去找出被拍摄到的小方格有可能的最小值。

## 说明/提示

**子任务**

在全部子任务中， $1\le k\le n$。

| 子任务 | 分数 | $n\le$ | $m\le$ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $4$ | $5$ | $100$ |  $k=n$|
| $2$ | $12$ | $500$ | $10^3$ | $r_i=c_i$ |
|  $3$| $9$ | $500$ | $10^3$ | 无 |
|$4$  |$16$  | $4 \times 10^3$ | $10^6$ | 无 |
| $5$ | $19$ | $5\times 10^4$ | $10^6$ | $k \le 100$ |
| $6$ |  $40$| $10^5$ | $10^6$ | 无 |


## 样例 #1

### 输入

```
5 7 2
0 3
4 4
4 6
4 5
4 6
```

### 输出

```
25
```

## 样例 #2

### 输入

```
2 6 2
1 4
4 1
```

### 输出

```
16
```

# 题解

## 作者：Alex_Wei (赞：23)

> *IX. [P5896 [IOI2016]aliens](https://www.luogu.com.cn/problem/P5896)
>
> [DP 优化方法大杂烩](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)，详解 wqs 二分及其注意事项，斜率优化等其它 DP 优化方法。
>
> [更好的阅读体验](https://www.cnblogs.com/alex-wei/p/ohhhhhh_look_Aliens.html)。

**** 团队赛 T6，没想到是 IOI 原题。当时看出来要用 wqs 二分，但是我没学过（经常发生知道要用某种算法但是不会写的情况），因此最近学习了一下 wqs 二分。找题目练手的时候看到了这题，世 界 线 收 束。做题的过程中发现还要用到斜率优化，于是也学了一下。

这算是一道比较套路的题目，但套路并不意味这不是好题，毕竟我从中学到了 wqs 二分和斜率优化两种 DP 优化方法。说它套路其实也不太合适，因为 2016 年 wqs 二分还没有在 OI 界普及，甚至国外将其称之为 “Aliens’ Trick” 就是根据本题的名字而命名的，所以这个 idea 在当时应该比较新颖。

---

不妨对网格图的主对角线所经过的格子从左上到右下依次编号为 $0,1,2,\cdots,m-1$。显然，编号为 $i$ 的格子在原网格图中的坐标为 $(i,i)$。因为正方形的主对角线完全包含于网格图的主对角线，所以为了拍到一个点 $(r_i,c_i)$ 必然要拍到编号为 $l_i,l_i+1,l_i+2,\cdots,r_i$ 的格子，其中 $l_i=\min(r_i,c_i),r_i=\max(r_i,c_i)$。因此，我们可以将题目转化为**线段覆盖问题**：现在有 $n$ 条线段 $[l_i,r_i]$，我们要用最多 $k$ 个区间 $[x_i,y_i]$ 去覆盖它们，使得每条线段至少被一个区间**完全包含**。即 $\forall i,\exist j,s.t. [l_i,r_i]\in [x_j,y_j]$。求以每个区间为对角线形成的所有正方形的面积并的最小值。接下来我们可以挖掘一些性质：

- $\textbf {Observation 1.}$ 如果两条线段 $i,j$ 满足 $[l_i,r_i]\in [l_j,r_j]$，那么线段 $i$ 对最终的答案没有影响。

  正确性显然。根据该性质，我们可以将所有线段按照左端点 $l_i$ 从小到大为第一关键字，右端点 $r_i$ 从大到小为第二关键字排序。然后依次遍历所有线段并记录右端点最大值 $r$。若当前线段 $i$ 的右端点 $r_i\leq r$，则忽略线段 $i$；否则用 $r_i$ 去更新 $r$，即 $r\gets r_i$。最终所有没有被忽略的线段，一定满足**左端点和右端点都单调递增**。读者自证不难。

- $\mathbf{Observation\ 2.}$ 最终所选取的所有区间一定满足 $x_i<x_{i+1},y_i<y_{i+1}\ (1\leq i<k)$。

  读者自证不难。

- $\mathbf{Observation\ 3.}$ 设 $F_i$ 为恰好选取 $i$ 个区间时答案的最小值，那么 $F_i$ 是一个下凸函数。

  读者自证~~不~~很难。感性理解一下即可，严格证明的话应该比较复杂。

有了上述性质，我们可以愉快地进行 DP 了：wqs 二分斜率 $K$，然后设 $f_i$ 表示覆盖第 $i$ 条线段时的最小代价（线段按照左端点从小到大排序。根据性质 $1$ 的结论，右端点也行，因为不影响线段之间的顺序）。显然有转移方程：

$$f_i=\min_{j=0}^{i-1}-K+\begin{cases}f_j+(y_i-x_{j+1}+1)^2-(y_j-x_{j+1}+1)^2&y_j\geq x_{j+1}\land j>0\\f_j+(y_i-x_{j+1}+1)^2&\mathrm{otherwise}\end{cases}$$

这个分情况讨论很讨厌，尝试把它消灭掉：设 $g_i=(y_i-x_{i+1}+1)^2[y_i\geq x_{i+1}\land i>0]$，那么转移方程变为 $f_i=\min_{j=0}^{i-1}f_j+(y_i-x_{j+1}+1)^2-g_j-K$。显然的斜率优化，~~但是我不会~~，所以多讲一点：拆开变成 $f_i=\min_{j=1}^{i-1} f_j+(y_i+1)^2-2(y_i+1)x_{j+1}+x^2_{j+1}-g_j-K$。先将所有 $y_i$ 加上 $1$（不影响单调性），忽略掉 $\min$ 再移移项，写成 $Y=kX+b$ 的形式，$f_j+x^2_{j+1}-g_j-K=2y_ix_{j+1}+(f_i-y_i^2)$。那么 $Y=f_j+x^2_{j+1}-g_j-K$，$k=2y_i$，$X=x_{j+1}$，$b=f_i-y^2_i$。将 $(X_j,Y_j)$ 看做一个点，因为 $k$ 确定了，现在就要找使得 $b$ 最小的 $(X_j,Y_j)$（这样能使得 $f_i$ 最小）。由于 $k,X$ 都是单调递增的，所以单调队列维护下凸包即可。

具体地，记 $k_{i,j}$ 为点 $(X_i,Y_i)$ 与 $(X_j,Y_j)$ 之间的斜率。首先将点 $0$ 加入单调队列，接下来遍历从小到大每个位置 $i$：

- 若单调队列大小不小于 $2$，设 $a,b$ 分别为队首的第一个和第二个点，若 $k_{a,b}\leq k=2y_i$ 则 $b$ 一定不劣于 $a$，弹出队首。重复该操作直到单调队列大小为 $1$ 或 $k_{a,b}>2y_i$。
- 此时队首 $a$ 即为最优决策 $j$，$f_j\to f_i$ 转移并记录选择的区间个数。
- 若单调队列大小不小于 $2$，设 $c,d$ 分别为队尾的倒数第二个和倒数第一个点；若 $k_{c,d}\geq k_{d,i}$ 则 $d$ 一定不在下凸包上，弹出队尾。重复该操作直到单调队列大小为 $1$ 或 $k_{c,d}<k_{d,i}$。
- 将点 $i$ 加入单调队列。

我们需要求出在代价最小的前提下最少的区间个数。不妨设 $num_i$ 为覆盖前 $i$ 条线段且代价最小时最少的区间个数 ，那么因为 $num_i$ 显然有单调性，所以我们每次转移时只需要选择最前面的一个决策点转移即可，即**第一步操作弹出队首时，将条件 $k_{a,b}\leq 2y_i$ 改为 $k_{a,b}<2y_i$，这样就保证了相同优劣的决策点，前者不会被后者所弹出（第三步的条件不需要改，因为是前面的决策点弹出后面的决策点，不影响结果）**。

时间复杂度 $\mathcal{O}(n\log V)$，其中 $V$ 是二分范围，本题中为 $m^2$。浮点数比较建议使用 $eps$。代码倒是不难写。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

const int N=1e5+5;
const ld eps=1e-10;

ll n,m,k,c,ans;
struct seg{
	int l,r;
	bool operator < (const seg &v) const{
		return l!=v.l?l<v.l:r>v.r;
	}
}p[N];

ll K,f[N],g[N],num[N];
ll sq(ll x){return x*x;}
ll Y(int i){return f[i]+sq(p[i+1].l)-g[i]-K;}
ll X(int i){return p[i+1].l;}
ld slope(int i,int j){return (ld)(Y(j)-Y(i))/(X(j)-X(i));}

ll hd,tl,d[N];
bool check(){
	d[hd=tl=1]=0;
	for(int i=1;i<=n;i++){
		while(hd<tl&&slope(d[hd],d[hd+1])+eps<=2*p[i].r)hd++;
		int j=d[hd]; num[i]=num[j]+1,f[i]=f[j]+sq(p[i].r-p[j+1].l)-g[j]-K;
		if(i<n)while(hd<tl&&slope(d[tl-1],d[tl])-eps>=slope(d[tl],i))tl--;
		d[++tl]=i;
	} return num[n]<=k;
}

int main(){
	cin>>n>>m>>k;
	for(int i=1,c,r;i<=n;i++){
		cin>>p[i].l>>p[i].r;
		if(p[i].l>p[i].r)swap(p[i].l,p[i].r);
	} sort(p+1,p+n+1);
	for(int i=1,r=-1;i<=n;i++)if(p[i].r>r)r=p[i].r,p[++c]=p[i]; n=c;
	for(int i=1;i<n;i++)if(p[i].r>=p[i+1].l)g[i]=sq(p[i].r-p[i+1].l+1);
	for(int i=1;i<=n;i++)p[i].r++;
	ll l=-1e12,r=0;
	while(l<r)K=(l+r>>1)+1,check()?(l=K,ans=f[n]+K*k):r=K-1;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zhlzt (赞：20)

这是我第一道不看题解做出正解的黑题！实现细节与所有题解均不同！

:::info[喜提洛谷当前最优解]
精细实现一下抢到了最优解 <https://www.luogu.com.cn/record/228655964>。
:::

:::warning[Hint]{open}
考虑一个正方形可以覆盖一个兴趣点 $(u,v)$ 的充要条件。出于对称性，不妨令 $u\le v$。同时设该正方形的左上角方格为 $(l,l)$，右下角方格为 $(r,r)$，则充要条件为 $l\le u\le v\le r$。

注意到我们所选取的 $(l,r)$ 一定互不包含，同时有 $l\in\{u\} $ 且 $r\in\{v\}$，否则一定不优。

自此，转化为区间覆盖问题。

同时结合题目中对拍摄次数的限制，不难想到是 wqs 二分套斜率优化 DP。
:::

我们令 $p_i=\displaystyle\min_{v=i}(u)$，$dp_i$ 为当前区间右端点为 $i$ 时被拍摄到的小方格数量的最小值，wqs 二分出的斜率为 $\text{mid}$。

则状态转移方程为：

$$dp_i=\text{mid}+\min_{j=0}^{i-1}(dp_j+(i-\min_{k=j+1}^{i}p_k+1)^2-\max(0,j-\min_{k=j+1}^{i}p_k+1)^2)$$

再次利用所选区间互不包含的性质，我们将 $\displaystyle\min_{k=j+1}^{i}p_k$ 改为 $\displaystyle\min_{k=j+1}^{m}p_k$ 并设为 $pos_j$，同时稍作整理：

$$dp_i=\text{mid}+i^2+2i+1+\min_{j=0}^{i-1}(y_j-2i\cdot pos_j)$$

其中 $y_j=dp_j+pos_j^2-2pos_j-\max(0,j-pos_j+1)^2$。

时间复杂度 $\mathcal{O}(m+n\log m)$，空间复杂度 $\mathcal{O}(n+m)$。

:::warning[维护下凸壳时的易错点]{open}
注意到此题中横坐标 $pos_j$ 非降，并不保证单调递增。

所以一定要注意决策点重合的情况。
:::

:::success[[IOI 2016] aliens - P5896.cpp]{open}
```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5,maxm=1e6+5;
int pos[maxm],vis[maxm],sta[maxn],cnt[maxn],n,m,k,top;
ll py[maxn],pre[maxn],dp[maxn];
inline ll squ(ll val){return val*val;}
inline bool check(int u,int v,int w){
    return (py[v]-py[u])*(pos[w]-pos[v])>=(py[w]-py[v])*(pos[v]-pos[u]);
}
inline void solve(ll mid){
	int pl=1,pr=1;
	py[0]=pre[0];
	for(int i=1;i<=top;++i){
		while(pl<pr and (py[sta[pl+1]]-py[sta[pl]])
        <2ll*vis[i]*(pos[sta[pl+1]]-pos[sta[pl]])) ++pl;
        
		dp[i]=py[sta[pl]]-2ll*vis[i]*pos[sta[pl]]+squ(vis[i]+1)+mid;
		cnt[i]=cnt[sta[pl]]+1;
		py[i]=dp[i]+pre[i];
		while(pl<pr and check(sta[pr-1],sta[pr],i)) --pr;
		sta[++pr]=i;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>k;
	int u,v;
	for(int i=0;i<=m;++i) pos[i]=1e9;
	for(int i=1;i<=n;++i){
		cin>>u>>v;
		++u,++v;
		if(u>v) swap(u,v);
		pos[v-1]=min(pos[v-1],u);
		vis[v]=1;
	}
	for(int i=m-1;i>=0;--i) pos[i]=min(pos[i],pos[i+1]);
	for(int i=1;i<=m;i++) if(vis[i]) vis[++top]=i;
	for(int i=0;i<=top;i++){
        pos[i]=pos[vis[i]];
        pre[i]=1ll*pos[i]*pos[i]-2*pos[i]-squ(max(0,vis[i]-pos[i]+1));
    }
	ll l=0,r=1ll*m*m,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		solve(mid);
		if(cnt[top]<=k) res=mid,r=mid-1;
		else l=mid+1;
	} 
	solve(res);
	cout<<(dp[top]-k*res)<<"\n";
	return 0;
}
```
:::

---

## 作者：OrezTsim (赞：10)

终于写了这题！

首先，把题意翻译一下，发现每一个点 $(r,c)$ 相当于要覆盖主对角线上 $[\min\{r,c\},\max\{r,c\}]$ 之间的部分。

那么这个题就转化成了一个区间覆盖问题。

看到区间覆盖的最大次数，想到 wqs 二分。

到这里，可以发现如下性质：

- 我们可以按照需要覆盖的区间的左端点进行排序。
- 如果一段需覆盖的区间被另一段需覆盖的区间包含，那么被包含的区间可以被删掉。

下面用 $[l_i,r_i]$ 表示预处理完后每一个 $(r,c)$ 代表的需要覆盖的区间。


- 结合第一点与第二点，我们发现排序后，需要选择的区间显然满足 $l_{i-1}<l_i,r_{i-1}<r_i$。
- wqs 二分代表的实际上是一个斜率始终 $\le 0$ 的下凸壳。

对于为什么这个东西是一个下凸壳，我们可以感性理解一下。

设 $p_k$ 表示强制选择 $k$ 个区间时的答案。

如果你只能选择 $k=1$ 个区间，那么实际答案最大可以到覆盖全图。

但是如果选择 $k=2$ 个区间，你可以在 $k=1$ 的基础上，把一个右上角的正方形和左下角的正方形（可以为空）去掉，只选择剩下的图形。

且因为 $p_k$ 表示强制选择 $k$ 个区间时的答案，所以此时一定贪心地选择能去掉大小最多的方案。

当然答案也可能不变，此时对于 $k>2$ 的情况答案一定也不变。

考虑到 $p_{k+1}-p_k$ 代表的就是斜率，即斜率单调非降。

那么图象就是个下凸壳了，可以使用 wqs 二分进行求解。

---

假设当前二分的斜率为 $\text{mid}$。

设 $f_i$ 表示覆盖到第 $i$ 条线段的最小代价。

$$f_i=-\text{mid}+\min\limits_{j=0}^{i-1}\begin{cases}f_j+(r_i-l_{j+1}+1)^2-(r_j-l_{j+1}+1)^2 & r_j \ge l_{j+1} \wedge j>0 \\ f_j+(r_i-l_{j+1}+1)^2 & \text{otherwise} \end{cases}$$

若 $r_i \ge l_{i+1}$，可以使用一个 $g_i$ 表示 $(r_i-l_{i+1}+1)^2$；否则 $g_i=0$。

观察到含 $i$ 的项和含 $j$ 的项相乘，考虑斜率优化。

设 $0 \le j_1 < j_2 < i$，且由 $j_2$ 转移过来比 $j_1$ 更优。

那么有。

$$f_{j_2}+(r_i-l_{j_2+1}+1)^2-g_{j_2} \le f_{j_1}+(r_i-l_{j_1+1}+1)^2-g_{j_1}$$

发现这个 $r_i+1$ 很烦人，那么在预处理的时候就把 $r_i$ 加上 $1$。

$$f_{j_2}+(r_i-l_{j_2+1})^2-g_{j_2} \le f_{j_1}+(r_i-l_{j_1+1})^2-g_{j_1}$$

把式子拆开。

$$f_{j_2}+r_i^2-2r_i\times l_{j_2+1}+l_{j_2+1}^2-g_{j_2} \le f_{j_1}+r_i^2-2r_i\times l_{j_1+1}+l_{j_1+1}^2-g_{j_1}$$

抵消后，把含 $i$ 的式子丢到左边，其余丢到右边。

$$2r_i \times (l_{j_1+1}-l_{j_2+1}) \le (f_{j_1}+l_{j_1+1}^2-g_{j_1})-(f_{j_2}+l_{j_2+1}^2-g_{j_2})$$

由于 $l$ 单调递增，故 $l_{j_1+1}-l_{j_2+1}<0$，丢到右边要变号。

$$2r_i \ge \dfrac{(f_{j_1}+l_{j_1+1}^2-g_{j_1})-(f_{j_2}+l_{j_2+1}^2-g_{j_2})}{l_{j_1+1}-l_{j_2+1}}$$

因为 $j_1<j_2$，换成正常的斜率形式。

$$2r_i \ge \dfrac{(f_{j_2}+l_{j_2+1}^2-g_{j_2})-(f_{j_1}+l_{j_1+1}^2-g_{j_1})}{l_{j_2+1}-l_{j_1+1}}$$

由于 $r$ 单调递增，故斜率单调递增，用单调队列维护下凸壳即可。

由于 wqs 二分要记录当前选的区间个数，所以还要在答案最小的情况下，最小化选择的区间个数。此时可以加强判定条件，把弹队头的 $\ge$ 换成 $>$，保证当前答案从更早的地方转移过来，一定更优。

时间复杂度 $\mathcal{O}(n \log v)$，$v$ 表示斜率的值域，即最大答案 $m^2$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int n, m, k, cnt, res, f[N], g[N], q[N], dp[N];

struct Node {
    int l, r;
    inline bool operator <(const Node &X) const {
        if (l == X.l) return r > X.r;
        return l < X.l;
    }
} p[N];

inline int pf(int x) { return x * x; }
inline int getx(int j1, int j2) { return p[j2 + 1].l - p[j1 + 1].l; }
inline int gety(int j1, int j2) {
	int y = f[j1] + pf(p[j1 + 1].l) - g[j1];
    int _y = f[j2] + pf(p[j2 + 1].l) - g[j2];
    return _y - y;
}

inline bool check(int mid) {
    int l, r; q[l = r = 1] = 0;
    for (int i = 1; i <= n; ++i) {
        while (l < r && 2 * getx(q[l], q[l + 1]) * p[i].r > gety(q[l], q[l + 1])) ++l;
        f[i] = f[q[l]] + pf(p[i].r - p[q[l] + 1].l) - g[q[l]] - mid, dp[i] = dp[q[l]] + 1;
        while (l < r && gety(q[r - 1], q[r]) * getx(q[r], i) > gety(q[r], i) * getx(q[r - 1], q[r])) --r;
        q[++r] = i;
    }
    return dp[n] <= k;
}

signed main() {
   	ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
   	cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].l >> p[i].r;
        if (p[i].l > p[i].r) swap(p[i].l, p[i].r);
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1, r = -1; i <= n; ++i)
        if (p[i].r > r) r = p[i].r, p[++cnt] = p[i]; n = cnt;
    for (int i = 1; i < n; ++i) if (p[i].r >= p[i + 1].l)
        g[i] = pf(p[i].r - p[i + 1].l + 1);
    for (int i = 1; i <= n; ++i) ++p[i].r;
    int l = -m * m, r = 0, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) res = f[n] + k * mid, l = mid + 1;
        else r = mid - 1;
    }
    return cout << res << endl, 0;
}
```

---

## 作者：Tweetuzki (赞：8)

首先为了更方便地处理问题，我们先把所有关键点对称地移动到左下方的三角区域中，也就是所有满足 $y \le x$ 的位置 $(x, y)$。由于主对角线上的正方形关于主对角线是对称的，因此这样是没有影响的。这样处理以后，所有关键点都满足了 $x \ge y$。

接下来注意到，如果有两个点 $(x, y)$ 和 $(x', y')$，如果满足 $x \ge x'$ 且 $y \le y'$，那么能覆盖到 $(x, y)$ 的正方形一定能覆盖到 $(x', y')$。所以可以把这样子的 $(x', y')$ 点去掉，同样对答案没有影响。

现在所有有用的关键点的分布就是一个锯齿状了：对于两个关键点 $i, j$ $(i \neq j)$，都有 $(r_i - r_j)(c_i - c_j) > 0$。

这样处理以后，问题简化许多。有一个显然的贪心是：至少存在一种最优方案，使得所有正方形的上边界和左边界一定顶着关键点。因此我们可以直接用一个动态规划解决该问题：设 $f(k)_i$ 表示用了 $k$ 个矩形，覆盖了前 $i$ 行所有关键点，且最后一个正方形的右下角为 $(i, i)$ 的最小花费。特殊地，若这行没有关键点，$f(k)_i = + \infty$。

若设 $nxt_i = \min_{r_j > i} c_j$（这表示了如果想从 $i$ 行转移过来，需要覆盖到的最左端的关键点位置），则有转移式如下：

$$
\begin{aligned}
f(k)_i &= \min_{0 \le j < i} \left( f(k - 1)_j + (i - nxt_j + 1) ^ 2 - \left(\max(0, j - nxt_j + 1)\right) ^ 2 \right) \\
       &= \min_{0 \le j < i} \left( f(k - 1)_j - 2i(nxt_j - 1) + (nxt_j - 1) ^ 2 - \left(\max(0, j - nxt_j + 1)\right) ^ 2 \right) + i ^ 2
\end{aligned}
$$

我们设 $g(k)_i = f(k)_i + (nxt_i - 1) ^ 2 - \left(\max(0, i - nxt_i + 1)\right) ^ 2$，则式子变为 $\displaystyle f(k)_i = \min_{0 \le j < i} \left( g(k - 1)_j - 2i(nxt_j - 1) \right) + i ^ 2$，显然是个斜率优化的形式，单调栈维护一下下凸壳就好了。

这样做的复杂度是 $\mathcal{O}(mk)$ 的。

为了优化复杂度，我们需要摆脱这个 $k$ 的限制。

对于某确定的 $n$ 个关键点，我们设一个关于限制次数 $k$ 的函数 $ans(k)$，表示在输入的 $n$ 个关键点相同的情况下，当限制次数为 $k$ 时最小的花费。我们发现这个 $ans$ 函数是凸的，也就是说，$ans(k - 1) - ans(k)$ 是一定不小于 $ans(k) - ans(k + 1)$ 的。对于这个式子，一种很感性的理解是，随着次数的增多，答案能被优化的空间越来越少。

这就是适用 wqs 二分（这个技巧在国外称为 Aliens' Trick，就得名于这道题目）的充要条件。wqs 二分的一个基本想法是，我们给每次操作添加一个代价 $c$，这样以后，如果出现了某个位置 $k$ 使得 $ans(k - 1) - ans(k) > c > ans(k) - ans(k + 1)$，那么这个时候的 $ans(k)$ 会取代 $ans(+ \infty)$ 成为答案的极值，这样问题就可以被转化为一个找极值的最优化问题。大概是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/1tcx6dge.png)

我们将上述的 DP 转移式加一项 $+ c$，可以用一样的斜率优化去转移它。

由于 $ans$ 函数是凸的，那么随着 $c$ 的单调变化，极值点 $k$ 也会单调地变化。于是我们可以二分代价 $k$，使得极值点刚好不超过题目要求的限制次数，然后再将通过动态规划得到的最大值，减去我们额外增添的代价 $c \times k$ 即可还原出最后答案。

时间复杂度 $\mathcal{O}(m \log m)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int MaxN = 100000 + 5, MaxM = 1000000 + 5;
const int INF = 0x7F7F7F7F;

int N, M, K;
int R[MaxN], C[MaxN];
int Mn[MaxM], Nxt[MaxM];
long long Cost;
std::pair<long long, int> F[MaxM];
long long G[MaxM];

void init() {
  for (int i = 1; i <= N; ++i) if (R[i] < C[i]) std::swap(R[i], C[i]);
  memset(Mn, 0x7F, sizeof Mn);
  for (int i = 1; i <= N; ++i)
    Mn[R[i]] = std::min(Mn[R[i]], C[i]);
  static int stk[MaxN];
  int tp = 0;
  for (int i = 1; i <= M; ++i) {
    if (Mn[i] == INF) continue;
    while (tp > 0 && Mn[stk[tp]] >= Mn[i]) {
      Mn[stk[tp]] = INF;
      tp--;
    }
    stk[++tp] = i;
  }
  while (Mn[M] == INF) M--;
  Mn[0] = 0;
  for (int i = M - 1, j = Mn[M]; i >= 0; --i) {
    if (Mn[i] == INF) continue;
    Nxt[i] = j - 1;
    j = Mn[i];
  }
}

inline void getG(int i) {
  G[i] = F[i].first + 1LL * Nxt[i] * Nxt[i];
  if (i > Nxt[i]) G[i] -= 1LL * (i - Nxt[i]) * (i - Nxt[i]);
}

inline double getK(int i, int j) { return 1.0 * (G[i] - G[j]) / (Nxt[i] - Nxt[j]); }

bool check() {
  static int que[MaxN];
  int head = 1, tail = 0;
  F[0] = std::make_pair(0, 0);
  getG(0);
  que[++tail] = 0;
  for (int i = 1; i <= M; ++i) {
    if (Mn[i] == INF) continue;
    while (head < tail && getK(que[head], que[head + 1]) < 2 * i) head++;
    int j = que[head];
    F[i].first = G[j] - 2LL * Nxt[j] * i + 1LL * i * i + Cost;
    F[i].second = F[j].second + 1;
    getG(i);
    while (head < tail && getK(que[tail - 1], que[tail]) > getK(que[tail], i)) tail--;
    que[++tail] = i;
  }
  return F[M].second <= K;
}

void solve() {
  long long lbound = 0, rbound = 1LL * M * M, ans = 0;
  while (lbound <= rbound) {
    long long mid = (lbound + rbound) >> 1;
    Cost = mid;
    if (check() == false) {
      ans = mid + 1;
      lbound = mid + 1;
    } else rbound = mid - 1;
  }
  Cost = ans;
  check();
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
  N = n; M = m; K = k;
  for (int i = 0; i < N; ++i) R[i + 1] = r[i] + 1;
  for (int i = 0; i < N; ++i) C[i + 1] = c[i] + 1;
  init();
  solve();
  return F[M].first - Cost * K;
}

int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  std::vector<int> r(n), c(n);
  for (int i = 0; i < n; i++) scanf("%d %d", &r[i], &c[i]);
  long long ans = take_photos(n, m, k, r, c);
  printf("%lld\n", ans);
  return 0;
}
```

---

## 作者：Neal_lee (赞：7)

[更奇怪的阅读体验](https://www.cnblogs.com/Neal-lee/p/14715497.html)
## 题目链接

[P5896 [IOI2016]aliens](https://www.luogu.com.cn/problem/P5896)

## 题目大意

在一个 $M\times M$ 的正方形网格图上分布着 $N$ 个关键点，你需要选择至多 $K$ 个两端点在主对角线上的正方形去覆盖它们，在这种情况下，求最少要覆盖多少个方格。

$1\leq N \leq 10^5$，$1\leq M\leq 10^6$，$1\leq k\leq N$

![](https://cdn.luogu.com.cn/upload/image_hosting/tcdmwhsd.png)


## 思路

为了方便，我们把点全部翻到主对角线下方（即 $i\geq j$ 的位置），注意到对于点 $x$ 和 $y$ ，若 $r_x\leq r_y$ 且 $c_x\geq c_y$，则当 $y$ 被覆盖后， $x$ 必然在其正方形中，所以 $x$ 是没有考虑的价值的，可以按 $r_i$ 排序后用栈去重。

剩下的点组成了一条单调下降的折线，设 $nxt_i$ 为第 $i$ 个点下面那个点的横坐标，若后来一个正方形要覆盖点 $i$ 以下的一块区域，那么只需要盖到 $nxt_i$ 的地方即可，同时令 $loc_i$ 为第 $i$ 个点的纵坐标。设 $f_{i,k}$ 为用 $k$ 个正方形覆盖前 $i$ 个节点最少需要覆盖的方格数，可以得到转移式：
$$
f_{i,k} = \min_{0\leq j<i}\{f_{j,k-1}+(loc_i-nxt_j+1)^2-\max\{0,loc_j-nxt_j+1\}^2\}
$$
 $(i-nxt_j+1)^2$ 为新添加正方形的大小，$max\{0,j-nxt_j+1\}^2$ 为此正方形和上一个重合的区域。

这个平方带有很强的提示性，展开：
$$
f_{i,k} = \min_{0\leq j<i}\{-2loc_i(nxt_j-1)+(nxt_j-1)^2+f_{j,k-1}-\max\{0,loc_j-
nxt_j+1\}^2\}+loc_i^2
$$
令 $g_{j,k} = (nxt_j-1)^2+f_{j,k}-\max\{0,loc_j-nxt_j+1\}^2$，去掉 $min$ ：
$$
f_{i,k} = \min_{0\leq j<i}\{-2loc_i(nxt_j-1)+g_{j,k-1}\}+loc_i^2\\
g_{j,k-1} = 2loc_i(nxt_j-1)+f_{i,k}-loc_i^2
$$
由于 $nxt_j-1$ 和 $2loc_i$ 都是单调递增的，所以可以直接用队列维护凸包，把 $dp$ 斜率优化到 $O(NK)$ 。

但是这样还是不够快，我们需要摆脱 $K$ 的影响，这里需要使用 $wqs$ 二分优化，不会的可以去 [这里](https://www.cnblogs.com/CreeperLKF/p/9045491.html) 看看。

通过打表（感性理解）可以发现，选 $k$ 个正方形时的答案 $ans_k$ 是一个关于 $k$ 的一个凸性函数，其导数单调递减，直观感受就是当已经选的正方形越多，再给正方形所能做到的优化就越来越小了，这个结论我本身想尝试去证的，但是真的有点难证。。就连官方题解说的都是

![](https://cdn.luogu.com.cn/upload/image_hosting/lfswsz4t.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/t29ts855.png)

有了这个性质就可以 $wqs$ 二分了，我们给添加一个正方形这个操作额外增加一个权值 $C$，当 $C = 0$ 时，函数的最高点的横坐标 $V(C)=N$，当 $C = M^2$ 时，$V(C)=1$，这是二分的下界和上界，我们二分找到最大的 $C$ 使得 $V(C)\leq K$，则答案即为 $f_{tot,K}-K\cdot C$ 。

时间复杂度： $O(N(logN+logM))$

## 一些细节

1. 单调栈去点的时候要注意点在同一行上的情况，如果你用 $pair$ 排序，你会发现这里不是你想要的顺序，需要判断一下。

2. 有一个 $wqs$ 二分初学者容易搞错的地方，二分中的那个凸包是辅助说明其正确性所为，实际实现时不需要考虑，是隐性的。这里找最高点时正常 $dp$ 就可以了，且不需要 $k$ 这一维，转移时记录一下用了几个正方形。

3. 由于不一定能找到最高点恰好是 $K$，但是找不到的情况只发生在 $ans_k$ 于 $k\in[V(C),V(C+1)]$ 之间是等差的情况，这时有
   $$
   f_{tot,V(C)}-C\cdot V(C)=ans_{V(C)}=f_{tot,K}-C\cdot K
   $$
   这是最后一步答案计算的依据，不过要注意的是我们必须找到最小的 ”最大值发生的地方“ 作为 $V(C)$，具体点说就是斜率优化中比较斜率淘汰队头时，条件必须是大于，而不是大于等于。

4. 几乎所有地方都要开long long，本人在二分上下界的地方忘开了。。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<fstream>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define per(i,b,a) for(int i = (b); i <= (a); i++)
#define N 100100
#define ll long long
#define PLL pair<ll, ll>
#define fr first
#define sc second
#define Inf 0x3f3f3f3f
using namespace std;
inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = (s<<3)+(s<<1)+(ch^48), ch = getchar();
    return s*w;
}
ll n, m, k, cnt;
ll nxt[N], g[N], loc[N];
PLL P[N], f[N];
void init(){
    rep(i,1,n) if(P[i].fr < P[i].sc) 
        swap(P[i].fr, P[i].sc);
    sort(P+1, P+n+1);
    stack<PLL> s;
    s.push({-1, -1});
    rep(i,1,n){
        while(!s.empty() && s.top().sc >= P[i].sc) s.pop();
        if(s.top().fr != P[i].fr) s.push(P[i]);
    }
    int lst = Inf;
    while(!s.empty()){
        nxt[cnt] = lst;
        lst = s.top().sc, loc[cnt++] = s.top().fr;
        s.pop();
    }
    reverse(nxt, nxt+cnt), reverse(loc, loc+cnt);
}
void get_G(int i){
    g[i] = (nxt[i]-1)*(nxt[i]-1) + f[i].fr;
    if(loc[i]-nxt[i]+1 > 0) g[i] -= (loc[i]-nxt[i]+1)*(loc[i]-nxt[i]+1);
}
double K(int i, int j){
    return 1.0*(g[i]-g[j])/(nxt[i]-nxt[j]); 
}
int cal(ll Cost){
    static int q[N];
    int l = 0, r = 0;
    q[0] = 0, get_G(0);
    rep(i,1,cnt-1){
        ll x = loc[i];
        while(l < r && K(q[l], q[l+1]) < 2*x) l++;
        f[i].fr = g[q[l]]-2*x*(nxt[q[l]]-1)+x*x + Cost, f[i].sc = f[q[l]].sc+1;
        get_G(i);
        while(l < r && K(q[r-1], q[r]) >= K(q[r], i)) r--;
        q[++r] = i;
    }
    return f[cnt-1].sc;
}  
ll solve(){
    ll l = 0, r = m*m, mid;
    while(l < r){
        mid = (l+r)>>1;
        if(cal(mid) <= k) r = mid;
        else l = mid+1;
    }
    cal(l);
    return f[cnt-1].fr - l*k;
}
ll take_photos(int _n, int _m, int _k, vector<int> r, vector<int> c){
    n = _n, m = _m, k = _k;
    rep(i,0,r.size()-1) P[i+1].fr = r[i], P[i+1].sc = c[i];
    init();
    return solve();
}
int main(){
    cin>>n>>m>>k;
    vector<int> c(n), r(n);
    rep(i,0,n-1) c[i] = read(), r[i] = read();
    cout<<take_photos(n, m, k, r, c)<<endl;
    return 0;
}
```

---

## 作者：takanashi_mifuru (赞：6)

#### 简要题意

给你一个大小为 $m\times m$ 的正方形，上面有 $n$ 个点，你现在需要选出最多 $k$ 个正方形使得这 $k$ 个正方形的对角线与主对角线重合，并且这 $k$ 个正方形能够覆盖所有的点，同时要求正方形的面积并最小。

#### 分析

首先我们考虑把所有点全部对称到主对角线上面，然后我们考虑因为这个题的特殊性，如果一个点在另一个点的左下角，那么这个点一定没有任何贡献，可以直接丢掉，因为如果有一种方案能够覆盖一个点那么这种方案一定会覆盖这个点的所有左下方的点。

然后这个题突然就好玩了起来。

我们把这些废物点丢掉有什么好处呢？

你发现，我们按照 $x$ 来排序后，我们现在一个矩形必须取一段连续的点了！

原因是显然的，因为覆盖了这一段的横坐标，而如果这一段还有比 $lt$ 的纵坐标更大的纵坐标，那么 $lt$ 会在这个点的左下角，那么 $lt$ 就不会存在，就矛盾了。

然后我们考虑如果矩形取了 $[lt,rt]$ 里的所有点，那么这个矩形可以取到右下角的纵坐标为 $rt$ 的纵坐标，左上角的横坐标为 $lt$ 的横坐标，而这个矩形又必须取到对角线上，所以这个矩形的面积应该是 $(y_{rt}-x_{lt}+1)^2$。

![](https://pic.imgdb.cn/item/64fbde6f661c6c8e54dfd94a.jpg)

看看图，感性理解一下！

我们现在知道了一个区间的点全部拿到手需要多大面积的矩形，但是我们要求的是矩形并最小啊，这个还是比较难直接做，我们考虑写一个 dp。

设 $dp_{i,j}$ 表示用 $i$ 个矩形覆盖前 $j$ 个点需要多大的矩形并面积。

那么很明显啊，矩形并的面积就是矩形的面积和减掉矩形交的面积，然后你说这个矩形交的面积怎么维护，实际上并不难维护，我们考虑左端点并没有什么所谓只要右端点在这里右下角的形态就是确定的，而后面的矩形无论怎么猛，都不会比右端点更高，所以只需要关注右端点就行了。

相应的我们也只需要关心我们新加进来的矩形的左端点，可以把左端点拉到多远。

![](https://pic.imgdb.cn/item/64fbdfe7661c6c8e54e041d7.jpg)

大概就是这张图中的黄色矩形，可以清晰地看到，他由两条紫色的线框定范围，那么很明显的，假设我的 $dp_{i,j}$ 想要从 $dp_{i-1,k}$ 更新，他的转移式子就是 $dp_{i,j}=\min(dp_{i-1,k}+(y_{j}-x_{k+1}+1)^2-\max(y_k-x_{k+1}+1,0)^2,dp_{i,j})$。

你直接做是 $n^3$ 的，非常爆笑。

设 $dinner_k=\max(y_k-x_{k+1}+1,0)^2$，很明显对于一个 $k$ 她是一个定值，然后你的式子就变成了 $dp_{i,j}=\min(dp_{i-1,k}-dinner_k+(y_j-x_{k+1}+1)^2,dp_{i,j})$，左边这个式子一看很像一个斜率优化啊，我们把他拆一下。

因为第一维是确定的所以为了后面推斜率优化式子能够简洁些，我们下面推式子的过程假设写 $dp_{j}$ 就是 $dp_{i-1,j}$ 好了。

那么来到斜率优化样板戏。

假设转移 $dp_i$ 时 $k$ 比 $j$ 更优 $(k>j)$。

则 $dp_k-dinner_k+(y_i-x_{k+1}+1)^2<dp_j-dinner_j+(y_i-x_{j+1}+1)^2$。

那把这个式子先拆开，$dp_k-dinner_k+y_i^2+x_{k+1}^2+1^2-2x_{k+1}-2y_ix_{k+1}+2y_i<dp_j-dinner_j+y_i^2+x_{j+1}^2+1^2-2x_{j+1}-2y_ix_{j+1}+2y_i$。

然后你移项一下，$dp_k-dinner_k+x_{k+1}^2-2x_{k+1}-2y_ix_{k+1}<dp_j-dinner_j+x_{j+1}^2-2x_{j+1}-2y_ix_{j+1}$。

你设 $A_i=dp_i-dinner_i+x_{i+1}^2-2x_{i+1}$，设 $B_i=x_{i+1}$，那么式子就被简化成了 $A_k-2y_iB_k<A_j-2y_iB_j$，那我们猛烈地移项就会得到 $A_k-A_j<2y_i(B_k-B_j)$。

再移项得到 $\frac{A_k-A_j}{B_k-B_j}<2y_i$，这是一个非常经典的斜率优化式子，我们直接单调队列维护凸壳即可。

于是我们做到了 $O(n^2)$ 的时间复杂度！！！！！

但是明显还不够，你发现，如果 $k$ 越大那答案肯定是不会再变大的，而且随着 $k$ 的增长这个变慢的速度应该也是越来越慢的（感性理解一下），那你猜这个东西应该是一个凸函数（实际上确实是），凸函数你直接在上面 wqs 二分，把前面 $dp$ 的第一维丢掉，然后转移式子里面加上每选一个矩形的代价 $w$，你需要通过二分这个 $w$ 使得最后使用的矩形数量最少，如果可以小过 $k$，那说明代价还是太高了，我们把他调小一点，否则就调大一点。

然后我们就可以直接 $O(n\log n)$ 解决这个题了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
struct node{
   int x,y;
}a[100005];
bool cmp1(node a,node b){
   return a.y<b.y||a.y==b.y&&a.x>b.x;
}
int A[100005];
int B[100005];
int dinner[100005];
void geta(){
   sort(a+1,a+1+n,cmp1);
   stack<int> stk,S;
   for(int i=1;i<=n;i++){
      while(!stk.empty()&&a[i].x<=a[stk.top()].x){
         stk.pop();
      }
      stk.push(i);
   }
   while(!stk.empty()){
      S.push(stk.top());
      stk.pop();
   }
   n=0;
   while(!S.empty()){
      a[++n]=a[S.top()];
      S.pop();
   }
   sort(a+1,a+1+n,cmp1);
   return;
}
int dq[2000005];
int dp[2000005];
int cnt[2000005];
const double eps=1e-6;
int Tw(int x){
   return x*x;
}
int up(int x,int y){
   return A[y]-A[x];
}
int down(int x,int y){
   return B[y]-B[x];
}
double slope(int x,int y){
   return 1.*up(x,y)/down(x,y);
}
bool check(int mid){
   int rt=0,lt=1;
   dq[++rt]=0;
   A[0]=dp[0]-dinner[0]+Tw(a[0+1].x)-2*a[0+1].x;
   B[0]=a[0+1].x;
   dp[0]=cnt[0]=0;
   for(int i=1;i<=n;i++){
      while(lt<rt&&slope(dq[lt],dq[lt+1])+eps<=2.*a[i].y){
         lt++;
      }
      int j=dq[lt];
      dp[i]=dp[j]-dinner[j]+Tw(a[i].y-a[j+1].x+1)+mid;
      cnt[i]=cnt[j]+1;
      A[i]=dp[i]-dinner[i]+Tw(a[i+1].x)-2*a[i+1].x;
      B[i]=a[i+1].x;
      while(lt<rt&&slope(dq[rt-1],dq[rt])-eps>=slope(dq[rt],i)){
         rt--;
      }
      dq[++rt]=i;
   }
   return cnt[n]<=k;
}
signed main(){
   scanf("%lld%lld%lld",&n,&m,&k);
   for(int i=1;i<=n;i++){
      scanf("%lld%lld",&a[i].x,&a[i].y);
      a[i].x++,a[i].y++;
      if(a[i].x>a[i].y)swap(a[i].x,a[i].y);
   }
   geta();
   for(int i=0;i<n;i++){
      dinner[i]=max(a[i].y-a[i+1].x+1,0ll);
      dinner[i]=Tw(dinner[i]);
   }
   int lt=-1,rt=1e12+1;
   while(lt+1<rt){
      int mid=lt+rt>>1;
      if(check(mid)){
         rt=mid;
      }
      else{
         lt=mid;
      }
   }
   check(rt);
   printf("%lld\n",dp[n]-k*rt);
   return 0;
}
```

---

## 作者：lkytxdy (赞：6)

## P5896 [IOI2016]aliens

> 一个 $m\times m$ 的网格图上有 $n$ 个关键点，要求选至多 $k$ 个对角线为主对角线的正方形去覆盖它们。问这些正方形最少要覆盖多少个方格。
>
> $1\leq k\leq n\leq 10^5$，$1\leq m\leq 10^6$。

考虑 wqs 二分。设 $F(i)$ 用恰好 $i$ 个正方形覆盖关键点，最少覆盖多少小方格。$G(i)\gets F(i)+c\cdot i$，当 $c=0$ 时显然最优的 $i$ 为 $n$。随着 $c$ 的增大，最优的 $i$ 会越来越小。

考虑将左上角为 $(l,l)$ 右下角为 $(r,r)$ 的正方形转化为区间 $[l,r]$。对于一个关键点 $(i,j)$，记 $u=\min(i,j),v=\max(i,j)$，则可以被 $l\leq u\leq v\leq r$ 的区间 $[l,r]$ 覆盖。

类似 P6047 丝之割，若 $(u_i,v_i),(u_j,v_j)$ 满足 $u_i\leq u_j$ 且 $v_i\geq v_j$，那么 $j$ 显然是无用的，因为覆盖 $i$ 的同时一定能覆盖 $j$。将没有的关键点去掉，按 $u$ 排序，$v$ 也单调递增。

设 $f_i$ 表示覆盖前 $i$ 个有用关键点，最少覆盖多少个方格。同时记录用了多少个区间。$f_i=\min\limits_{0\leq j<i}\{f_j+(v_i-u_{j+1}+1)^2-\max(0,v_j-u_{j+1}+1)^2+c\}$，斜率优化：$\underline{f_j+u_{j+1}^2-2u_{j+1}-\max(0,v_j-u_{j+1}+1)^2}_{\ y}=\underline{2v_i}_{\ k}\underline{u_{j+1}}_{\ x}+\underline{f_i-v_i^2-2v_i-1-c}_{\ b}$。

时间复杂度 $\mathcal O(n\log m^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5;
int n,m,k,cnt,g[N],q[N];
ll f[N],ans;
struct seg{int l,r;}a[N];
ll sq(int x){return 1ll*x*x;}
ll get(int i){
	return f[i]+sq(a[i+1].l)-2*a[i+1].l-sq(max(0,a[i].r-a[i+1].l+1));
}
double slope(int i,int j){
	return 1.0*(get(i)-get(j))/(a[i+1].l-a[j+1].l);
}
bool ok(ll c){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		while(l<r&&slope(q[l],q[l+1])<2*a[i].r) l++;
		f[i]=f[q[l]]+sq(a[i].r-a[q[l]+1].l+1)-sq(max(0,a[q[l]].r-a[q[l]+1].l+1))+c,g[i]=g[q[l]]+1;
		while(l<r&&slope(q[r-1],q[r])>=slope(q[r],i)) r--;
		q[++r]=i;
	}
	if(g[n]<=k) ans=f[n]-c*k;
	return g[n]<=k;
}
signed main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
	}
	sort(a+1,a+1+n,[](seg x,seg y){return x.l!=y.l?x.l<y.l:x.r>y.r;});
	for(int i=1,r=-1;i<=n;i++)
		if(a[i].r>r) r=a[i].r,a[++cnt]=a[i];
	n=cnt,a[0].r=-1;
	ll l=0,r=1ll*m*m;
	while(l<=r){
		ll mid=(l+r)/2;
		if(ok(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：jr_zch (赞：2)

# [IOI 2016] Aliens

## 题意转换

原问题太复杂，先做一些简单的转换。

对角线两侧的点本质相同，所以可以将下方的点对称到上方去，不妨把整个图翻转 $45$ 度。

![](https://cdn.luogu.com.cn/upload/image_hosting/a03kdt7k.png)

求能覆盖所有点的恰好 $k$ 个等腰直角三角形的最小面积并。

## 核心思路

考虑 $\text{DP}$，但是并不好设计状态。

应该能够感知到可以把点按某种规则进行排序，然后转化为分 $k$ 段问题。

按 $x$，$y$ 排序显然不行，按 $x+y$ 排序也不一定是连续一段被同一个三角形所覆盖。

我们需要探究一个点会被怎样的三角形所覆盖。

如上图 $3$，覆盖第一个点的最小三角形是以该点作为顶点的等腰直角三角形，发现这个等腰直角三角形对应的是对角线上的一段区间。

由此得出，对角线上的一段区间和任意一个三角形形成双射。

而且若 $[l,r]$ 对应三角形包含了点 $i$，则对于任意的 $[x,y]$ 满足 $x \leq l \leq r \leq y$ 所对应的三角形也包含点 $i$。

于是可以非常自然的**把点映射到对角线上的一段区间**，对于一个被其他区间包含的小区间可以直接删掉，并不影响答案。

**把所有区间按左端点排序后，左右两端点都是单调递增的，这就是我们一直在寻找的排序规则**。将第 $i$ 个区间到第 $j$ 个区间分为一组的代价即为 $(r_j-l_i+1)^2$。

设 $f_{i,j}$ 表示前 $i$ 个区间分了 $j$ 组的最小代价。

$$
f_{i,j}=\min_{k=0}^{i-1}(f_{k,j-1}+(r_i-l_{k+1}+1)^2-\max(r_k-l_{k+1}+1,0)^2)
$$

上述转移方程中后半部分的 $\max$ 很难受，发现是相邻区间的交集，于是：

$$
f_{i,j}=\min_{k=0}^{i-1}(f_{k,j-1}+(r_i-l_{k+1}+1)^2-w_k)
$$

$$
w_i=\max(r_i-l_{i+1}+1,0)^2
$$

直接暴力做时间复杂度为 $O(n^2k)$，发现转移代价类似 $(r-l)^2$，易证满足决策单调性，斜率优化即可做到 $O(nk)$。

题目要求选**至多** $k$ 个，由决策单调性又可以得到凸性，考虑 $\text{wqs}$ 二分优化 $\text{DP}$。

显然，$j$ 关于 $f_{n,j}$ 的函数，除了满足凸性，还单调递减，所以选小于 $k$ 个三角形一定不优，至多 $k$ 个就变为恰好 $k$ 个。

直接套板子，这道题就做完了。

## 实现细节

按照 $\text{wqs}$ 二分的流程，我们要在代价相同时选择段数最小的方案。

令 $g_i$ 表示 $f_i$ 最小时分的最小段数，对于 $i<j$，有 $g_i \leq g_j$。

考虑用反证法证明，如果 $g_i > g_j$，那么可以用 $g_j$ 对应的方案替换 $g_i$ 的方案，与 $g$ 的最优性相悖。

所以代价相同时选择下标最小的方案就可以了。

如果斜率优化的写法是二分单调栈，找最小的切点即可。

如果是单调队列，判断弹出的条件要写 `slope(q[head],q[head+1])<k` 而非 `<= k`。

## $\text{Code}$：

用单调队列实现斜率优化，总时间复杂度 $O(n \log V)$。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e5+7,inf=1e16;
int n,m,k,tot,head,tail;
int f[maxn],g[maxn],w[maxn],q[maxn];
struct node{
	int l,r;
	bool operator <(const node &x) const{
		return l==x.l?r>x.r:l<x.l;
	}
}a[maxn],b[maxn],c[maxn];

inline int sqr(int x){
	return x*x;
}

inline int x(int id){
	return c[id+1].l;
}

inline int y(int id){
	return f[id]-w[id]+c[id+1].l*c[id+1].l;
}

inline bool slope(int l,int r,int lim){
	return y(r)-y(l)<lim*(x(r)-x(l));
}

inline bool slope(int l,int r,int p,int q){
	return (y(r)-y(l))*(x(q)-x(p))<=(y(q)-y(p))*(x(r)-x(l));
}

int check(int val){
	head=1,tail=0;
	for(int i=1;i<=tot;i++) f[i]=g[i]=inf;
	q[++tail]=0;
	f[0]=g[0]=0;
	for(int i=1;i<=tot;i++){
		int slo=2*(c[i].r+1);
		while(tail>head&&slope(q[head],q[head+1],slo)) head++; 
		f[i]=y(q[head])-slo*x(q[head])+sqr(c[i].r+1)-val;
		g[i]=g[q[head]]+1;
		while(tail>head&&slope(q[tail],i,q[tail-1],q[tail])) tail--;
		q[++tail]=i;
	}
	return g[tot];
}

signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&b[i].l,&b[i].r);
		b[i].l++,b[i].r++;
		//将点映射到对角线 
		int len=llabs(b[i].l-b[i].r);
		a[i].l=min(b[i].l,b[i].r);
		a[i].r=a[i].l+len;
	}
	//去除被包含的区间 
	sort(a+1,a+1+n);
	for(int i=1,pre=0;i<=n;i++){
		if(pre<a[i].r){
			c[++tot]=a[i];
			pre=max(pre,a[i].r);
		}
	}
	sort(c+1,c+1+tot);
	for(int i=1;i<tot;i++) if(c[i].r>=c[i+1].l) w[i]=sqr(c[i].r-c[i+1].l+1);
	//wqs 二分 
	int l=-1e12,r=0,ans=0,ansc=0;
	while(l<=r){
		int mid=l+r>>1ll;
		if(check(mid)<=k){
			ans=f[tot];
			ansc=mid;
			l=mid+1;
		}else r=mid-1;
	}
	printf("%lld",ans+k*ansc);
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

#### 前言

非常好的题，故写一篇题解。

#### 思路

首先根据题目要求，我们每次拍摄选的两个点应该是 $\left(i,i\right),\left(j,j\right)$ 同时 $1 \le i,j \le m$，这样所有 $i \le r_z,c_z \le j$ 的兴趣点都会被拍摄到。

考虑一个转化，将 $r_i > c_i$ 的翻转一下，使得每一个兴趣点都是 $r_i < c_i$，相当于沿对角线翻转，显然对答案没影响。

在翻转后，对于每一对 $\left(r_i,c_i\right)$，把所有 $r_i \le r_j,c_i \ge c_j$ 的点都删掉，只留下 $\left(r_i,c_i\right)$，这个很显然，我们画个图就知道了。

![](https://cdn.luogu.com.cn/upload/image_hosting/fz20f5v9.png)

显然，如果要覆盖左下角的点 $i$，那么肯定要覆盖 $r_i \le r_j,c_i \ge c_j$ 的点。

题目就转化为有若干个互相不包含的区间，要覆盖 $k$ 次，要使得每个兴趣点都能找到一对 $l_j,r_j$ 使得 $l_j \le r_i \le c_i \le r_j$，将兴趣点按 $r_i$ 排序，直接设 $f_{i,j}$ 表示前 $i$ 个兴趣点都被覆盖后用了 $j$ 次的最小覆盖点数，转移很容易想到，每次枚举上一次转移的点，然后删掉重复贡献，因为有可能多次覆盖同一段点。

$f_{i,j} = \min\left(f_{i,j},f_{z,j-1} + \left(c_i-r_z+1\right)^2 - g_z\right)$。

$g_i$ 表示 $i$ 和 $i-1$ 的相交区间，没有交就是 $0$。

然后就可以获得 $25$ 分，[点击查看代码](https://www.luogu.com.cn/paste/9o3f328q)。

然后先抛开分 $j$ 段不谈，式子本身是很可优化的，化简出来后可以直接斜率优化搞。

$f_{i,j} = f_{z,j-1}-g_z+r_z^2 - 2\times r_z \times \left(c_i+1\right) + \left(c_i+1\right)^2$，我们令 $B_i =  f_{i,j-1}-g_i+r_i^2,K_i = r_i$，然后设 $i$ 从 $k$ 处转移比 $z$ 更优，同时 $z< k$。

那么最终化简就得到 $2c_i \ge \frac{B_k-B_z}{K_k-K_z}$。

由于 $c_i$ 是单调递增的，所以斜率也是单调递增，直接用单调队列维护下凸壳即可，复杂度降到了 $nk$。

分 $k$ 段易想到 wqs 二分，具体证明比较复杂，可以感性理解一下，我们分的越多，能优化的程度就越小，直接给每分一段额外加一个贡献即可，不过我们转移在值相同时优先选择段数小的，判一下就好了。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 1e6+10;
int n,m,k,x,y,f[N],F[N],g[N],cnt,mx,ans,l,r,mid,o,c[N],L,R;
struct w
{
	int x,y;
}a[N],b[N];
inline bool cmp(w x,w y)
{
	if(x.x == y.x) return x.y > y.y;
	return x.x < y.x;
}
inline int dis(int x){return f[x]+b[x+1].x*b[x+1].x-g[x];}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m),read(k);
	for(int i = 1;i <= n;i++)
	{
		read(a[i].x),read(a[i].y); a[i].x++,a[i].y++;
		if(a[i].x > a[i].y) swap(a[i].x,a[i].y);//翻转 
	}
	sort(a+1,a+1+n,cmp); mx = -1e9;
	for(int i = 1;i <= n;i++)
	{
		if(mx < a[i].y) b[++cnt] = a[i];
		//否则小了说明被完全包含了不要 
		mx = max(mx,a[i].y);
	}
	b[0].y = -1; 
	for(int i = 0;i < cnt;i++) 
		if(b[i].y >= b[i+1].x) g[i] = (b[i].y-b[i+1].x+1)*(b[i].y-b[i+1].x+1);
	ans = 1e15;
	L = -1e11,R = 0;
	while(L <= R)
	{
		mid = ((L+R)>>1); f[0] = F[0] = 0; 
		for(int i = 1;i <= cnt;i++) f[i] = 1e16,F[i] = 0; 
		l = r = 1; c[l] = 0;
		for(int i = 1;i <= cnt;i++)
			{
				while(l < r && ((dis(c[l+1])-dis(c[l]) < 2*(b[i].y+1)*(b[c[l+1]+1].x-b[c[l]+1].x)) || ((dis(c[l+1])-dis(c[l]) == 2*(b[i].y+1)*(b[c[l+1]+1].x-b[c[l]+1].x) && F[c[l+1]] < F[c[l]])))) l++;
				int j = c[l];
				f[i] = dis(j)+(b[i].y+1)*(b[i].y+1)-2*(b[i].y+1)*b[j+1].x-mid,F[i] = F[j]+1;
				while(r > l && (((dis(i)-dis(c[r]))*(b[c[r]+1].x-b[c[r-1]+1].x) < (dis(c[r])-dis(c[r-1]))*(b[i+1].x-b[c[r]+1].x)) || ((dis(i)-dis(c[r]))*(b[c[r]+1].x-b[c[r-1]+1].x) == (dis(c[r])-dis(c[r-1]))*(b[i+1].x-b[c[r]+1].x) && F[i] <= F[c[r]]))) r--;
				c[++r] = i;
			}
		if(F[cnt] <= k) L = mid+1,ans = f[cnt]+mid*k;
		else R = mid-1;
	}
	//多次拍摄的点只算一个
	print(ans); flush();
	return 0;
}
```

---

## 作者：Union_of_Britain (赞：1)

这相当于需要覆盖区间 $[\min(r_i,c_i),\max(r_i,c_i)]$。注意到被包含的区间是不需要考虑的，因此有 $r_i<r_j\iff c_i<c_j$。

把区间按端点排序，问题相当于划分序列为 $k$ 段，每段 $[L,R]$ 的贡献为 $w'(L,R)=(c_R-r_L+1)^2$，可能需要去除两正方形相交的面积，不过这一部分面积只跟每段的 $R$ 有关。若记 $t_j=[c_j\ge r_{j+1}](c_j-r_{j+1}+1)^2$，正确的贡献就是

$$w(L,R)=(c_R-r_{L}+1)^2-t_R$$

这满足四边形不等式性质，即交叉优于包含。$-t_R$ 显然不构成影响，而另外一部分可以由下图看出（这类似于 [ABC355G](https://www.luogu.com.cn/problem/AT_abc355_g)）。

![](https://cdn.luogu.com.cn/upload/image_hosting/wgyb6eso.png?x-oss-process=image/resize,m_lfit,h_1700,w_2205)

如图，$w(a,c)+w(b,d)\le w(b,c)+w(a,d)$。

因此根据某著名结论，可以对划分段数 wqs 二分。

dp 式子变成了：

$$f_i=f_j+w(j+1,i)-M$$

这是可以使用李超树维护的。时间复杂度 $O(n\log^2 V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5,INF=1e18;
int n,m,k,N,vis[maxn];
struct intv{int l,r;}L[maxn];
bool operator <(intv A,intv B){return A.l==B.l?A.r>B.r:A.l<B.l;}
struct line{
	int k,b;
	line(){k=0,b=1e16;}
	line(int a,int B){k=a,b=B;}
	int operator ()(int x){return k*x+b;}
}qsy[maxn];
int f[maxn];
int xds[maxn<<2],cnt[maxn];
#define ls (k<<1)
#define rs (k<<1|1)
#define mid ((l+r)>>1)
int cb(int x){
	int v=f[x]+L[x+1].l*L[x+1].l;
	if(x>0&&L[x].r>=L[x+1].l)v-=(L[x].r-L[x+1].l+1)*(L[x].r-L[x+1].l+1);
	return v;
}
int ck(int x){return -2*L[x+1].l;}
line cl(int x){return line(ck(x),cb(x));}
void modify(int k,int l,int r,int v){
	int &u=xds[k];
	if(qsy[u](mid)>qsy[v](mid))swap(u,v);
	if(l==r)return ;
	if(qsy[u](l)>qsy[v](l))modify(ls,l,mid,v);
	if(qsy[u](r)>qsy[v](r))modify(rs,mid+1,r,v);
}
pair<int,int> calc(int k,int l,int r,int x){
	pair<int,int> res={qsy[xds[k]](x),xds[k]};
	if(l==r)return res;
	if(x<=mid)res=min(res,calc(ls,l,mid,x));
	else res=min(res,calc(rs,mid+1,r,x));
	return res;
}
pair<int,int> solve(int M){
	memset(xds,0,sizeof(xds));
	qsy[0]=cl(0);
	for(int i=1;i<=n;i++){
		auto P=calc(1,1,m+1,L[i].r+1);
		f[i]=(L[i].r+1)*(L[i].r+1)+P.first+M;
		qsy[i]=cl(i);cnt[i]=cnt[P.second]+1;
		modify(1,1,m+1,i);
	}
	return {cnt[n],f[n]};
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>N>>m>>k;
	for(int i=1;i<=N;i++){
		cin>>L[i].l>>L[i].r;L[i].l++,L[i].r++;
		if(L[i].l>L[i].r)swap(L[i].l,L[i].r);
	}
	sort(L+1,L+N+1);int mxr=-1;
	for(int i=1;i<=N;i++){
		if(mxr>=L[i].r)vis[i]=1;
		mxr=max(mxr,L[i].r);
	}
	for(int i=1;i<=N;i++){
		if(vis[i])continue;
		L[++n]=L[i];
	}
	int res=INF,L=0,R=1e12;
	while(L<=R){
		int M=(L+R)/2;
		auto p=solve(M);
		if(p.first<=k){
			res=p.second-k*M;
			R=M-1;
		}else L=M+1;
	}
	cout<<res<<endl;
	return 0;
}

```

---

## 作者：xie_lzh (赞：1)

提供一种比较劣但是不用推式子的做法。

先考虑这样一个转化，首先我们可以把所有在对称轴左下的点对称上来，我们发现某些点是没有作用的，当且仅当其位于另一个点的左下方，因为正包含了其右上的点一定能包含它。


在删去这些无用的点后，我们直接考虑 dp，转移形如 $f_i=\min\{f_j+C(j+1,i)\}$，其中 $C(l,r)$ 表示包含区间内所有点的最小正方形并减去与包含前一个点的正方形的交。

由于正方形的面积是个二次函数，我们发现 $C(l,r)$ 这玩意是有决策单调性的。

直接二分出决策点就行，$10^5$ 的 $\log^2$ 还是随便跑的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
#define ll long long
int n,k,tot,m;
struct node
{
    ll x,y;
}pos[N];
ll f[N],cnt[N];
int q[N],l,r,R[N];
ll C(int l,int r) { return (pos[r].y-pos[l].x+1)*(pos[r].y-pos[l].x+1); }
ll P(int l,int r) { return f[l]+C(l+1,r)-(l!=0)*max(0ll,(pos[l].y-pos[l+1].x+1))*(pos[l].y-pos[l+1].x+1); }
int solve(int x,int y,int w)
{
    int l=y+1,r=tot,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(P(x,mid)+w>=P(y,mid)+w) r=mid-1;
        else l=mid+1;
    }
    return r+1;
}
void check(ll w)
{
    f[0]=0; q[l=r=1]=0; cnt[0]=0;
    for(int i=1;i<=tot;i++)
    {
        while(l<r&&R[l]<=i) l++;
        f[i]=P(q[l],i)+w; cnt[i]=cnt[q[l]]+1;
        while(l<r&&P(i,R[r-1])<P(q[r],R[r-1])) r--;
        R[r]=solve(q[r],i,w);
        q[++r]=i;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>pos[i].x>>pos[i].y;
        if(pos[i].x>pos[i].y) swap(pos[i].x,pos[i].y);
    }
    sort(pos+1,pos+1+n,[](node a,node b){return a.x==b.x?a.y>b.y:a.x<b.x;});
    for(int i=1,maxx=-1;i<=n;i++)
    {
        if(pos[i].y<=maxx) continue;
        maxx=pos[i].y; pos[++tot]=pos[i];
    }
    ll l=1,r=100000000000ll,mid;
    pos[tot+1].x=1e9;
    pos[tot+1].y=1e9;
    while(l<=r)
    {
        mid=(l+r)>>1; check(mid);
        if(cnt[tot]<k) r=mid-1;
        else l=mid+1;
    }
    check(l-1);
    // check(0);
    cout<<f[tot]-1ll*k*(l-1)<<'\n';
}
```

---

