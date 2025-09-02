# [KSN2021] Delivering Balls

## 题目描述

给定一个长度为 $N$ 的序列 $H$ 和 $Q$ 次询问。

第 $i$ 次询问中，你初始在第 $S_i$ 列 $H_{S_i}$ 行，想要到第 $T_i$ 列第 $H_{T_i}$ 行。

你可以进行若干次移动。每次移动你可以选择以下两种参数：

* 列 $-1$，列不变，列 $+1$。
* 行 $-1$，行不变，行 $+1$。

如果你选择行 $-1$，消耗 $1$ 体力，如果你选择行不变，消耗 $2$ 体力，如果你选择行 $+1$，消耗 $4$ 体力。

你需要保证每次移动后，你的列数 $x$ 在 $[1,N]$ 之间，且你的行数 $y$ 不小于 $H_x$。

对于每个询问，你需要求出你消耗体力的最小值。

## 说明/提示

**【样例解释】**

以下为第一个样例中两个询问的图示：

![](https://sandalphon.tlx.toki.id/api/v2/problems/JIDPROG92Su7ScrLh6DkhILekKA/render/roket-q-1.png) ![](https://sandalphon.tlx.toki.id/api/v2/problems/JIDPROG92Su7ScrLh6DkhILekKA/render/roket-q-2.png)

**【数据范围】**

- Subtask 1（7 points）：只存在一组数据，满足 $N=8$，$Q=4$，$H=[,9,3,3,5,4,8,2]$，$(S_i,T_i)$ 依次为 $(1,8)$，$(3,6)$，$(6,4)$ 和 $(7,2)$。
- Subtask 2（5 points）：$S_i+1=T_i$。
- Subtask 3（6 points）：$H_i=i$。
- Subtask 4（18 points）：$N,Q,H_i\leq 100$。
- Subtask 5（24 points）：$N,Q\leq 1000$。
- Subtask 6（13 points）：$S_i=1$。
- Subtask 7（27 points）：无特殊限制。

对于所有数据，$2\leq N\leq 2\times 10^5$，$H_i\leq 10^9$，$Q\leq 2\times 10^5$，$1\leq S_i,T_i\leq N$。

## 样例 #1

### 输入

```
4
9 1 8 2
2
1 3
4 2```

### 输出

```
3
31```

## 样例 #2

### 输入

```
9
1 2 3 2 1 2 3 2 1
4
1 9
4 6
2 6
5 2```

### 输出

```
18
4
9
9```

# 题解

## 作者：Math_rad_round (赞：15)


**我们把这道题直观化。**

可以将数列想象成二维地图，$h_i$ 就是在 $i$ 位置上的山的高度。自然我们到不了山里（你的行数 $y$ 不小于 $H_x$）。

向左上、正上、右上花费 $4$；向左，右花费 $2$；左下、正下、右下花费  $1$ 。

样例说明这幅图就挺合适。

![](https://cdn.luogu.com.cn/upload/image_hosting/yo1usqmc.png)

对于一个询问，我们可以先认为 $s<t$。

这样，我们水平移动的次数就决定好了，因此我们应当尽量的利用水平移动的步数向上（向下）走。

对于 $s$ 来说，我们让他尽量向右上走，这样它的轨迹就是一条斜率为 $1$ 的直线（下图红色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/i1tgskaw.png)（紫色的是山）

显然我们可以发现，等到撞上墙了再往上升，不如再起点处就向上。（绿+灰）

那我们要预先向上多少个呢？根据上图，我们可以看出这个值是：

$\max(h_i-(h_s+(i-s))) ,i\in[s,t]$ 即：

$\max(h_i-i)-(h_s-s) ,i\in[s,t]$ 

因此我们只需要维护一个 $\max(h_i-i)$ 的 $i$ 即可得到答案。

从 $t$ 开始向左也是类似，维护 $\max(h_j+j)$。

但是，这并没有结束，如下图所示，显然不能从 $S$ 一路向右走到 $T$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vxzstvv9.png)

因此我们在得到 $i,j$ 以后，还要知道 $max(h_l) , l\in [s,t]$（可以发现 $l \in [i,j]$ ）。

然后我们就可以知道路径了。

从 $s$ 向上；然后一路斜上至 $i$，斜上到与 $l$ 平高；向右经过 $l$ 到一个合适的位置；向右下经过 $j$ 一直斜下 $t$ 那一列；向下到 $t$。
![](https://cdn.luogu.com.cn/upload/image_hosting/g2s0z766.png)

至于具体长度我相信各位看懂上一幅图也不会有难度。

剩余的就是细节问题了，对于 $t>s$ 可以先交换 $s,t$，然后把上升和下降的费用对调。同时注意本题必须开 $long\ long$。

用ST表实现最大值维护的话时间复杂度 $O(n \log n+q)$，空间 $O(n\log n)$。

### 代码：

```cpp
#include<iostream>
int n;
#define he(i,j) (h[st[i][j]]+st[i][j])
#define eh(i,j) (h[ts[i][j]]+n-ts[i][j])
#define hh(i,j) (h[tt[i][j]])
#define ll long long
using namespace std;


ll st[300000][20];
ll ts[300000][20];
ll tt[300000][20];
ll d[300000];
ll h[300000];
ll maxnn(ll a,ll b){
	if(a==b)return ts[a][0];
	ll le=b-a+1;ll o=(b-(1<<d[le]))+1;
	if(he(a,d[le])>he(o,d[le])){
		return st[a][d[le]];
	}else return st[o][d[le]];
}
ll maxn(ll a,ll b){
	if(a==b)return st[a][0];
	ll le=b-a+1;ll o=b-(1<<d[le])+1;
	if(eh(a,d[le])>eh(o,d[le])){
		return ts[a][d[le]];
	}else return ts[o][d[le]];
}
ll maxt(ll a,ll b){
	if(a==b)return tt[a][0];
	ll le=b-a+1;ll o=b-(1<<d[le])+1;
	if(hh(a,d[le])>hh(o,d[le])){
		return tt[a][d[le]];
	}else return tt[o][d[le]];
}
ll len(ll a,ll b,ll f){//这里我是直接分别求这四段的路径长度 
	if(a==b)return 0;//和题解不同 
	ll ans=0;
	ans+=(b-a)*2;
	if(h[a]<h[b]){
		ans+=(h[b]-h[a])*(2-3*f);
		if(h[b]-h[a]>b-a)ans+=(h[b]-h[a]-(b-a))*1LL*2;
	}else{
		ans+=(h[a]-h[b])*(-1+3*f);
		if(h[a]-h[b]>b-a)ans+=(h[a]-h[b]-(b-a))*1LL*2;	
	} 
	return ans;
}
int main(){
	ll q;
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>h[i];
		st[i][0]=ts[i][0]=tt[i][0]=i;
	}
	for(ll i=1;i<=19;i++){//三个ST表 
		ll le=1<<(i-1);
		for(ll j=1;j+le*2-1<=n;j++){
			if(he(j,i-1)>he(j+le,i-1)){
				st[j][i]=st[j][i-1];
			}else st[j][i]=st[j+le][i-1];
			if(eh(j,i-1)>eh(j+le,i-1)){
				ts[j][i]=ts[j][i-1];
			}else ts[j][i]=ts[j+le][i-1];
			if(hh(j,i-1)>hh(j+le,i-1)){
				tt[j][i]=tt[j][i-1];
			}else tt[j][i]=tt[j+le][i-1];
		}
	}
	ll le=0,g=1;
	for(ll i=1;i<=n;i++){//预处理对数 
		if(2*g<i){
			le++;g*=2;
		}d[i]=le;
	}cin>>q;
	for(ll i=1;i<=q;i++){
		ll a,b;cin>>a>>b;
		ll lo=0;
		if(a>b){
			swap(a,b);lo=1;
		}
		ll yg=maxnn(a,b),zg=maxn(a,b);
		ll zz=maxt(zg,yg);
	//	cout<<a<<" "<<zg<<" "<<zz<<" "<<yg<<" "<<b<<endl;
		ll ans=0;
		ans+=len(a,zg,lo);
		ans+=len(zg,zz,lo);
		ans+=len(zz,yg,lo);
		ans+=len(yg,b,lo);
		cout<<ans<<endl;
	}
	return 0;
}
```




---

## 作者：minVan (赞：2)

**解题思路**

首先可以确保每一次列的方向一定不会与 $s$ 到 $t$ 的方向相反。

不妨设 $l=\min\{s,t\}$，$r=\max\{s,t\}$。

对于每次移动，所花体力值如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ixykemgr.png?x-oss-process=image/resize,m_lfit,h_300,w_325)

显然，从 $l$ 到 $r$，一定要翻过 $[l,r]$ 间最高的一个，区间最大我们毫不犹豫地选择 ST 表，然后我们思考一下，令 $h_x=\max\limits_{i\in[l,r]}\{h_i\}$，那么从 $(l,h_l)$ 到 $(x,h_x)$，一定至少花费 $4\times\max\limits_{i\in[l,r]}\left\{h_i-(h_l+i-l)\right\}=4\times(\max\limits_{i\in[l,r]}\{h_i-i\}-(h_l-l))$ 体力值，所以再用一个 ST 表维护 $h_i-i$ 的区间最大值。

同理，从 $(r,h_r)$ 至 $(x,h_x)$ 也需要用一个 ST 表维护 $h_i+i$ 的区间最大值。

令 $a$ 为 $\max\limits_{i\in[l,r]}\{h_i\}$，$b$ 为 $\max\limits_{i\in[l,r]}\{h_i-i\}$，$c$ 为 $\max\limits_{i\in[l,r]}\{h_i+i\}$，则最后的答案为为 $a - 4\times h_s - h_t + 2 \times (b + c)$，注意是 $s,t$，不是 $l,r$！！！（因为如果是 $l,r$ 则询问 $s,t$ 与 $t,s$ 所得到的答案是一样的，但显然不同）

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N], f[N][20][3];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		f[i][0][0] = a[i];
		f[i][0][1] = a[i] - i;
		f[i][0][2] = a[i] + i;
	}
	for(int i = 1; i <= 19; i++) {
		for(int j = 1; j + (1 << (i - 1)) <= n; j++) {
			f[j][i][0] = max(f[j][i - 1][0], f[j + (1 << (i - 1))][i - 1][0]);
			f[j][i][1] = max(f[j][i - 1][1], f[j + (1 << (i - 1))][i - 1][1]);
			f[j][i][2] = max(f[j][i - 1][2], f[j + (1 << (i - 1))][i - 1][2]);
		}
	}
	int q;
	cin >> q;
	while(q--) {
		int s, t, s1, t1;
		cin >> s >> t;
		s1 = s, t1 = t;
		if(s > t) {
			swap(s, t);
		}
		int k = log2(t - s + 1);
		int a1 = max(f[s][k][0], f[t - (1 << k) + 1][k][0]);
		int b1 = max(f[s][k][1], f[t - (1 << k) + 1][k][1]);
		int c1 = max(f[s][k][2], f[t - (1 << k) + 1][k][2]);
		cout << a1 - 4 * a[s1] - a[t1] + 2 * (b1 + c1) << '\n';
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：2)

**下次静态区间最大值再也不用线段树了！！！**

---

给出一种神奇的做法：使用 ST 表求出区间 $[s,t]$ 的最大值 $a_i$。可以贪心地想到：在 $i$ 之前的操作一定不是下降，在 $i$ 之后的操作一定不是上升。但因为中间会有遮挡，所以可以分别**二分**向左和向右平着走的长度（可以证明：上升、平着走、下降的策略一定更优，且平着走的一段一定经过 $i$），然后这道题就完成了，时间复杂度 $O(n\log n)$。

---

代码：

```cpp
// 下次静态最大值再也不用线段树了！！！
#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <set>
#define int long long
using namespace std;

int n,q,cnt;
int a[200005];
int tmp[200005];
int f[200005][20];
int f1[200005][20];
int f2[200005][20];
set<int> s[200005]; // 映射高度为 umap[a[i]] 的数至 s[i]
unordered_map<int,int> umap;

static inline int Max(int l,int r) {
	if(l>r) swap(l,r);
	int k=log2(r-l+1);
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
static inline int Max1(int l,int r) {
	int k=log2(r-l+1);
	return max(f1[l][k],f1[r-(1<<k)+1][k]);
}
static inline int Max2(int l,int r) {
	int k=log2(r-l+1);
	return max(f2[l][k],f2[r-(1<<k)+1][k]);
}

static inline bool check1(int l,int r,int x) {
	return Max1(l,r)<=x;
}
static inline int solve1(int L,int R) {
	int l=0,r=(R-L);
	while(l<r) {
		int mid=l+r>>1;
		if(check1(L,R-mid,a[R]-(R-mid))) r=mid;
		else l=mid+1;
	}
	return r;
}

static inline bool check2(int l,int r,int x) {
	return Max2(l,r)<=x;
}
static inline int solve2(int L,int R) {
	int l=0,r=(R-L);
	while(l<r) {
		int mid=l+r>>1;
		if(check2(L+mid,R,a[L]-(n-(L+mid)+1))) r=mid;
		else l=mid+1;
	}
	return r;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) {
		cin>>a[i];
		tmp[i]=a[i];
		f[i][0]=a[i];
		f1[i][0]=a[i]-i;
		f2[i][0]=a[i]-(n-i+1);
	}
	for(int j=1;1<<j<=n;++j) {
		for(int i=1;i+(1<<j)-1<=n;++i) {
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
			f1[i][j]=max(f1[i][j-1],f1[i+(1<<j-1)][j-1]);
			f2[i][j]=max(f2[i][j-1],f2[i+(1<<j-1)][j-1]);
		}
	}
	sort(tmp+1,tmp+n+1);
	int tot=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=tot;++i) {
		umap[tmp[i]]=++cnt;
	}
	for(int i=1;i<=n;++i) {
		s[umap[a[i]]].insert(i);
	}
	cin>>q;
	while(q--) {
		int l,r;
		cin>>l>>r;
		int maxn=Max(l,r);
		int w1=(maxn-a[r]);
		int w4=(maxn-a[l]);
		int ans=w1+(w4<<2);
		if(l>r) {
			swap(l,r);
		}
		int max_num=*s[umap[maxn]].lower_bound(l);
		cout<<ans+(solve1(l,max_num)<<1)+(solve2(max_num,r)<<1)<<endl;
	}
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：2)

（这题的输入格式有误，应该是输入一个正整数 $N$）

首先我们假设 $S<T$，为了不尽量减少步数消耗即不浪费步数，我们应该在向右位移的同时上下移动。于是乎我们可以进行一个初始化操作，使得只要一直想右上方走就可以越过最高障碍。

可以得出初始化的高度应该为 $\max(H_i-(H_S+(i-S)))$，也就是 $\max((H_i-i)-(H_S-S))$。

于是乎我们只需要维护 $H_i-i$ 的最大值就 OK 了。如果是向左移动，只需要把 $S$ 换成 $T$ 即可，维护 $H_j+j$ 的最大值即可。

除此之外，我们还需要统计一下最高点。这里可以使用解决 RMQ 问题的 ST 表，当到达最高点的时候我们就不需要再增加行了。已知水平位移，利用 $T$ 维护从右至左（即向左移动）的 $\max(H_j+j)$，就可以得到答案了。

主体代码如下：

（ST 表部分）

```cpp
for(int i=1;i<=N;i++) cin>>H[i],f[i][0]=H[i],f1[i][0]=H[i]-i,f2[i][0]=H[i]+i;
logg[0]=-1;
for(int i=1;i<=N;i++) logg[i]=logg[i/2]+1;
for(int j=1;j<=20;++j)
	for(int i=1;i+(1<<j)-1<=N;++i)
		f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]),f1[i][j]=max(f1[i][j-1],f1[i+(1<<(j-1))][j-1]),f2[i][j]=max(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);
```

（处理部分）

```cpp
maxh=max(f[l][len],f[r-(1<<len)+1][len]);
maxs=max(f1[l][len],f1[r-(1<<len)+1][len]);
maxt=max(f2[l][len],f2[r-(1<<len)+1][len]);
maxs-=H[l]-l;
maxt-=H[r]+r;
if(S>T) swap(maxs,maxt);
```

---

## 作者：DDF_ (赞：1)

## 题面

在一个二维平面中有 $n$ 个山峰，第 $i$ 个山峰高度为 $h_i$。

向左上，右上或上移动的代价为 $4$，向左或右移动的代价为 $2$，向左下，右下或下的代价为 $1$。

有 $q$ 次询问，对于每次询问，求从第 $x$ 个山峰爬到第 $y$ 个山峰的最小代价。

## 题解

首先，从贪心的思路考虑，人从 $x$ 爬到 $y$ 的路线可以简化为从 $x$ 先上升到 $x$ 和 $y$ 间最高的山峰，然后再从最高的山峰下降到 $y$。

因为假设在没到最高山峰前就下降，那遇到更高的山峰又要上升，约等于同一段路走了两遍，肯定是不优的。

其次，继续从贪心的思路想，斜着走肯定是比直上直下直左直右的代价更低的。

因为假设说要从 $(x,y)$ 移动到 $(x+1,y+1)$，走斜着走就直接一步走到，代价为 $4$，横平竖直地走就要走两步，代价为 $6$，其他情况也类似。

所以，最优的情况就是一直斜着走，然后到最高山峰平着走，接着再斜下去，形似下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w4jq1k1h.png)

所以，假设最高山峰为 $z$，则答案中一定有 $4 \times (h_{z} - h_{x}) + (h_{z} - h_{y})$。

但是，不是所有情况都是最优的，总会有些山峰挡住前进的路线，使得有几段变得直上直下，增加上面这段平着走的代价。

对于一个山峰 $y$，且 $y>x$，它要想挡住从山峰 $x$ 出发的人，使其不能继续斜着走，那么就有 $h_{y} - h_{x}> y - x$，所以就有 $h_{y}-y > h_{x} -x$。

这个式子很好理解，就是因为斜着走肯定横坐标和纵坐标会同时进行加减 $1$，所以斜着走路线的斜率总为 $1$ 或 $-1$，当要上升的高度大于横着走的高度，那么就会挡住。

同理，对于一个山峰 $y$，且 $y<x$，若 $y$ 要挡住 $x$，则有 $h_{y} +y> h_{x}+x$。

所以对于上行和下行路线，都可以直接找最后一个挡住它的山峰，然后更新横着走的答案，也就是两个山峰的距离，减去最高山峰的高度和最后一个挡住的山峰的高度之差。

找这个最后挡住的山峰，就是要求从最高山峰到右端点 $h_{i}+i$ 和从左端点到最高山峰 $h_{i}-i$ 的最大值。

所以要维护三个最大值，维护最大值，很容易想到 ST 表，直接打三个 ST 表维护即可。

预处理复杂度 $O(n \times \log (n))$，查询复杂度 $O(1)$，总复杂度 $O(n \times \log (n) + m)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+2;
int n,m;
int mx[N][22],mx1[N][22],mx2[N][22];
ll ans,h[N];
void st() {
	for(int i=1;i<=n;i++) mx[i][0]=mx1[i][0]=mx2[i][0]=i;
	for(int j=1;(1<<j)<=n;j++) {
		for(int i=1;i+(1<<j)-1<=n;i++) {
			if(h[mx[i][j-1]]>h[mx[i+(1<<(j-1))][j-1]]) mx[i][j]=mx[i][j-1];
			else mx[i][j]=mx[i+(1<<(j-1))][j-1];
			if(h[mx1[i][j-1]]-mx1[i][j-1]>h[mx1[i+(1<<(j-1))][j-1]]-mx1[i+(1<<(j-1))][j-1]) mx1[i][j]=mx1[i][j-1];
			else mx1[i][j]=mx1[i+(1<<(j-1))][j-1];
			if(h[mx2[i][j-1]]+mx2[i][j-1]>h[mx2[i+(1<<(j-1))][j-1]]+mx2[i+(1<<(j-1))][j-1]) mx2[i][j]=mx2[i][j-1];
			else mx2[i][j]=mx2[i+(1<<(j-1))][j-1];
		}
	}
	return;
}
int rmq(int l,int r) {
	int k=log2(r-l+1);
	if(h[mx[l][k]]==h[mx[r-(1<<k)+1][k]]) return min(mx[l][k],mx[r-(1<<k)+1][k]);
	if(h[mx[l][k]]>h[mx[r-(1<<k)+1][k]]) return mx[l][k];
	return mx[r-(1<<k)+1][k];
}
int rmq1(int l,int r) {
	int k=log2(r-l+1);
	if(h[mx1[l][k]]-mx1[l][k]==h[mx1[r-(1<<k)+1][k]]-mx1[r-(1<<k)+1][k]) return min(mx1[l][k],mx1[r-(1<<k)+1][k]);
	if(h[mx1[l][k]]-mx1[l][k]>h[mx1[r-(1<<k)+1][k]]-mx1[r-(1<<k)+1][k]) return mx1[l][k];
	return mx1[r-(1<<k)+1][k];
}
int rmq2(int l,int r) {
	int k=log2(r-l+1);
	if(h[mx2[l][k]]+mx2[l][k]==h[mx2[r-(1<<k)+1][k]]+mx2[r-(1<<k)+1][k]) return max(mx2[l][k],mx2[r-(1<<k)+1][k]);
	if(h[mx2[l][k]]+mx2[l][k]>h[mx2[r-(1<<k)+1][k]]+mx2[r-(1<<k)+1][k]) return mx2[l][k];
	return mx2[r-(1<<k)+1][k];
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[i]);
	scanf("%d",&m);
	st();
	while(m--) {
		int l,r,s,k;
		scanf("%d%d",&l,&r);
		s=rmq(min(l,r),max(l,r)); //s为最高山峰
		ans=(h[s]-h[l])*4ll+(h[s]-h[r]); //上升和下降的贡献
		k=rmq2(s,max(l,r));
		if(h[s]-h[k]<k-s) ans+=(k-s-(h[s]-h[k]))*2ll;
		//找从最高山峰到右端点最后一个挡住的山峰，更新横着走的贡献
		k=rmq1(min(l,r),s);
		if(h[s]-h[k]<s-k) ans+=(s-k-(h[s]-h[k]))*2ll;
		//找从左端点到最高山峰最后一个挡住的山峰，更新横着走的贡献
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zhouyuhang (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/fqi35kq1.png)

不妨设 $s<t$，其路线必然形如上图。其中红色的上升段仅有 右 / 正上 / 右上，黄色的平行段仅有 右，蓝色的下降段仅有 右 / 正下 / 右下。分界点即为最大值最靠左和最靠右的位置。

贪心地选择，必然在红色和蓝色段尽量多的选择 右下 和 右上，因为这可以减少总的移动次数。怎样能做到尽量多的选择？以红色段为例，我们考虑在最开始的时候抬升到一个位置，使得其可以持续向右上走直到达到黄色段的高度。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hyhaspsi.png)

由于不希望浪费步数，最优策略一定会如上图一样，使得这条斜线恰好切到某座山，那么抬升的高度即为 过这些点斜线的截距最大值 减去 过起点斜线的截距，也即 $\left(\max\limits_{i=s}^p(H_i-i)\right)-(H_s-s)$，其中 $p$ 为分界点位置。仔细思考，由于过分界点后的点斜线的截距一定变小，因此无需知道分界点位置。剩余的都可以据抬升高度计算。用 ST 表维护，复杂度 ${\mathcal O}(n\log n+Q)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10; 

int n, Q, h[N];
int st0[N][20], st1[N][20], st2[N][20];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
    cin >> n;
    for (int i = 1; i <= n; ++i) {
    	cin >> h[i];
    	st0[i][0] = h[i], st1[i][0] = h[i] - i, st2[i][0] = h[i] + i;
	}
	
	for (int i = 1, h = 1; i <= 18; ++i, h *= 2) {	
		for (int j = 1; j + h <= n; ++j) {
			st0[j][i] = max(st0[j][i - 1], st0[j + h][i - 1]);
			st1[j][i] = max(st1[j][i - 1], st1[j + h][i - 1]);
			st2[j][i] = max(st2[j][i - 1], st2[j + h][i - 1]);
		}
	}
	
	cin >> Q;
	while (Q--) {
		int s, t;
		cin >> s >> t;
		int l = min(s, t), r = max(s, t), g = log2(r - l + 1);
		int a = max(st0[l][g], st0[r - (1 << g) + 1][g]);
		int b = max(st1[l][g], st1[r - (1 << g) + 1][g]);
		int c = max(st2[l][g], st2[r - (1 << g) + 1][g]);
		cout << a - 4LL * h[s] - h[t] + 2LL * (b + c) << '\n';
	}
	
    return 0;
}
```

---

## 作者：kdy20100729 (赞：1)

~~没人？，那我来水一发~~

## 思路：  
我们如果只预处理 $[s,t]$ 区间内 $h_i$ 的大小，假设 $h_i$ 为 $[s,t]$ 中的最高高度  
$\mathtt{H=(h_i-h_s)}$ 为上升高度，  
$\mathtt{D=(h_i-h_t)}$ 为下降高度,  
$\mathtt{M=max \left(0, \left(t-s \right)-H-D \right)}$ 为平移距离。  
然后会发现对于
> 7  
0 99 0 0 100 0 0 99 0  
1  
1 9  

这种数据无法处理，因为，$1$ 到 $9$ 之间下降路径会被挡住。这样会导致我们的平移距离增加，所以我们需要分别预处理 $[s,t]$  
$ms$ 从 $s$ 开始到 $t$ 需要在 $s$ 时上升多少，  
$mt$ 从 $s$ 开始到 $t$ 最后到 $t$ 时需要下降多少。  
如果不考虑 $i$ 和 $s$ 中间有障碍，我们发现 $h_i$ 到 $h_s$ 的提前上升距离是 $ms=h_i-(h_s+(i-s))$。这个公式的意思是 $i$ 的高度减去（$s$ 的高度加上 $s$ 到 $i$ 一直斜着走能产生的高度）。  
分解一下这个式子：  
$ms=(h_i-i)-(h_s-s)$。  
显然 $h_s-s$ 对于区间 $[s,t]$ 是一个常数，所以我们只需要保存这个 $[s,t]$ 区间的最大 $h_i-i$。  
这样就能算出从 $s$ 到 $t$ 需要提前上升的距离。  
计算 $t$ 的时候记得是 $mt=h_i-(h_t+(t-i))$ 所以分解这个式子为 $mt=(h_i+i)-(h_t+t)$。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
int n,q,s,t;
int h[maxn];
int f[maxn][31],f1[maxn][31],f2[maxn][31],log_2[maxn];
int main (){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&h[i]);
    	f[i][0]=h[i];
    	f1[i][0]=h[i]-i;
    	f2[i][0]=h[i]+i;
	}
	for(int i=1;i<=30;i++){
		for(int j=1;j+(1<<i)-1<=n;j++){
			f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
			f1[j][i]=max(f1[j][i-1],f1[j+(1<<(i-1))][i-1]);
			f2[j][i]=max(f2[j][i-1],f2[j+(1<<(i-1))][i-1]);
		}
	}
	for(int i=2;i<=n;i++){
		log_2[i]=log_2[i/2]+1; 
	}
	scanf("%d",&q);
	while(q--){
		int s,t;
		ll mh,ms,mt,ans,cnt;
		scanf("%d%d",&s,&t);
		
		int l=s,r=t;
		if(l>r)swap(l,r);
		int len=log_2[r-l+1];
		
		mh=max(f[l][len],f[r-(1<<len)+1][len]);
		ms=max(f1[l][len],f1[r-(1<<len)+1][len]);
		mt=max(f2[l][len],f2[r-(1<<len)+1][len]);
		ms=ms-(h[l]-l);
		mt=mt-(h[r]+r);
		if(s>t)swap(ms,mt);
		cnt= abs(t-s)-((mh-ms-h[s]) + (mh-mt-h[t])); 
		ans = 4*(mh-h[s]) + (mh-h[t]) + 2*cnt; 
		printf("%lld\n",ans);
	}
    return 0;
}
```

---

## 作者：oyoham (赞：0)

### problem
给定数组 $H$，有如下操作方式：  
- 以 $1$ 的花费从 $(x,y)$ 移到 $(x,y-1),(x-1,y-1),(x+1,y-1)$。
- 以 $2$ 的花费从 $(x,y)$ 移到 $(x-1,y),(x+1,y)$。   
- 以 $4$ 的花费从 $(x,y)$ 移到 $(x,y+1),(x-1,y+1),(x+1,y+1)$。
- 若 $y<H_x$，则不能移到 $(x,y)$。   
每次给你两个整数 $S,T$,求从 $(S,H_S)$ 移到 $(T,H_T)$ 的最小花费。
### Solution
以下设 $S\le T$，若 $S>T$ 可将原序列反转后做。  
设 $S$ 到 $T$ 中最高点为 $p$。  
注意到，$x$ 坐标必定按照 $S\to\dots\to S\to S+1\to\dots\to S+1\to\dots\to T\to\dots\to T$ 变化，此时 $y$ 坐标必定经过 $H_p$（因为经过 $p$ 时 $y$ 坐标不能小于 $H_p$）。考虑如下贪心策略：在走到 $H_p$ 前，若当前可往右上走，就往右上走，否则往上走，从 $T$ 过来也做一遍，然后在两个终点之间往右走，如下（`o` 代表路径，`x` 代表不能走的点，`-` 表示能走但不是路径的点，最下面一排是 $H$）：
```
-----------
---ooooo---
--ox----o--
-oxx-x--xo-
-oxxxx--x-o
oxxxxxx-x-x
12453421412
```
但是这样时间复杂度单次是 $\Theta(n)$ 的，考虑优化。  
发现以下两种情况花费相同：
```
--o-  --o-
-oxo  -oxo
-oxo  o-xo
oxxo  oxxo
oxxx  oxxx
1352  1352
```
考虑将路径分成五部分：向上走，向右上走，向右走，向右下走，向下走。  
注意到向右上走时（设向上走完后在 $(S,k)$），则 $\forall (x,y)(S \le x \& y\le H_p),y=k+x-S\ge H_x,\therefore \forall x,k-S\ge H_x-x$，于是 $k=\max\limits_{i=S}^{p}H_i-i+S$，发现对于 $p\le x\le T$，$H_x-x\le H_p-p\le k-S$，所以同样的 $k=\max\limits_{i=S}^{T}H_i-i+S$，同理可得往右下时（设向下走前后在 $(T,m)$），$m=\max\limits_{i=p}^{T}H_{i}+i-T$。于是答案就很容易算了。  
具体的，设 $l=H_p-k+S=H_p-(\max\limits_{i=S}^{p}i-H_i),r=m-H_p+T=(\max\limits_{i=p}^{T}i+H_{i})-H_p$ 则 $ans=4(H_p-H_S)+2(r-l)+(H_p-H_T)$。  
代码中用 ST 表维护 $ans1=k=\max\limits_{i=S}^{T}H_i,ans2=k=\max\limits_{i=S}^{T}H_i-i,ans3=k=\max\limits_{i=S}^{T}H_i+i$，答案即为 $4(ans1-H_S)+2((ans3-ans1)-(ans1-ans2))+(ans1-H_T)=\bm{ans1+2ans2+2ans3-H_T-H_S}$。
### Code
```cpp
/*省略头文件，快读快写*/
int n=read();
int a[200005];
int st[3][21][200005];
int find(int x,int l,int r){
	int k=__lg(r-l+1);
	return max(st[x][k][l],st[x][k][r-(1<<k)+1]);
}
signed main(){
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		st[0][0][i]=a[i];
		st[1][0][i]=a[i]-i;
		st[2][0][i]=a[i]+i;
	}
	for(int j=1;1<<j<=n;j++){
		for(int i=1;i<=n-(1<<j);i++){
			st[0][j][i]=max(st[0][j-1][i],st[0][j-1][i+(1<<j-1)]);
			st[1][j][i]=max(st[1][j-1][i],st[1][j-1][i+(1<<j-1)]);
			st[2][j][i]=max(st[2][j-1][i],st[2][j-1][i+(1<<j-1)]);
		}
	}
	int m=read();
	while(m--){
		int l=read(),r=read(),tp=find(0,min(l,r),max(l,r)),pr=find(1,min(l,r),max(l,r)),nx=find(2,min(l,r),max(l,r));
		write(tp-a[l]*4-a[r]+(nx+pr<<1));putchar(10);
	}
}
```

---

