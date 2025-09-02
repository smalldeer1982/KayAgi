# [COCI 2024/2025 #2] 流明 / Blistavost

## 题目背景

译自 [COCI 2024/2025 #2](https://hsin.hr/coci/) T4。$\texttt{4s,1G}$。满分为 $120$。

## 题目描述


数轴的正半轴的整数点上布满了璀璨的水晶灯。起初，它们都是点亮的。

初始时，时刻为 $0$，守卫在原点处。每单位时间，她可以选择向左或者向右移动一单位长度，也**可以待在原地**。

当守卫在一盏水晶灯所在的位置时，可以选择熄灭这盏水晶灯。**熄灭不消耗时间。**


有 $n$ 个要求，每个要求形如三元组 $(l_i,r_i,t_i)$，表示：村民需要熄灭区间 $[l_i,r_i]$ 内的水晶灯，而且必须在时刻${}\ge t_i$ 时才能熄灭这个区间内的水晶灯（也就是说，时刻 $\lt t_i$ 时不能熄灭这个区间内**任意一盏**水晶灯）。

请你计算守卫至少需要多少单位时间才能满足村民的全部要求。


## 说明/提示


#### 样例解释

样例 $2$ 解释：

时刻 $3$ 时走到 $x=3$ 处，停留一单位时间。

时刻 $4$ 时，熄灭 $x=3$ 的水晶灯。

时刻 $5$ 时，走到 $x=2$ 并熄灭上面的水晶灯。

时刻 $6$ 时，走到 $x=1$ 并熄灭上面的水晶灯。

耗时 $6$ 单位时间。

#### 提示

对于 $100\%$ 的数据，保证：

- $1\le n\le 5\, 000$；    
- $1\le l_i\le r_i\le 10^{18}$；
- $1\le t_i\le 10^{18}$。


| 子任务编号 | $n\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $18$ | A |   $ 20 $   |  
| $ 2 $    | $5\, 000$ | B  |  $ 25 $   |  
| $ 3 $    | $5\, 000$ | A  |  $ 55 $   |  
| $ 4 $    | $5\, 000$ |  |  $ 20 $   |  

- 特殊性质 A：$l_i=r_i$。
- 特殊性质 B：$l_i=1$。



## 样例 #1

### 输入

```
3
1 1 1
3 3 5
5 5 3```

### 输出

```
7```

## 样例 #2

### 输入

```
3
1 2 1
1 1 5
1 3 4```

### 输出

```
6```

## 样例 #3

### 输入

```
3
6 6 6
8 8 7
9 9 9```

### 输出

```
9```

# 题解

## 作者：Hell0_W0rld (赞：5)

## P11432 [COCI 2024/2025 #2] Blistavost
非常好的一道反向关路灯+挖掘性质的区间 dp 题。
### 题目大意
$N$ 个任务，每个任务要求 $[l_i,r_i]$ 的水晶灯只能在 $\geq t_i$ 的时刻操作，且要被全部熄灭。你需要完成所有任务。你移动一单位的时间是 $1$。你初始在 $0$。

### 解题思路

#### Subtask 1
显然你不可能在一个没有任务的点折返，这样你还不如不折返往前走或者待在你来到这个点的地方。把关键点 $t_i$ 提取出来。

于是我们可以 $dp_{S,i}$ 表示你完成了 $S$ 状态下的任务，停留在 $t_i$ 的位置。

时间复杂度 $O(n^2\times 2^n)$。
#### 正解
首先我们注意到你从中间开始关还不如你在左右两端等到 $t_i$ 时刻开始一个个关。所以如果两端 $l_i,r_i$ 的水晶灯都被关掉了，这个任务必然已经完成了。

其次我们可以从 Subtask 1 的代码中寻找最优决策——我们可以发现其中必然有一个最优解是每次仅有一个**坐标**区间内的所有关键点都没有关掉，其他关键点都关掉了。

> 感性理解一下：
>
> 如果不是这样的话，我们考虑一个点深入开着的水晶灯的坐标区间。
>
> 如果从两侧到达该点的路径上所有点都可以关掉，我们可以顺路关完，显然更优。
>
> 否则我们可以等外面的开始，然后一路操作进来，这个点在**必须要走的连通区间两端点的路径上**，可以被顺路操作，没必要特地跑进来关灯。

所以我们可以设计出 dp 状态：$f[l][r][0/1]$ 表示还剩下 $[x_l,x_r)$ 或 $(x_l,x_r]$ 的坐标区间内所有点都亮着，我正在 $l$ 或者 $r$ 的最短时间。

转移是平凡的。
### 代码
```cpp
#include<bits/stdc++.h>
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);}
cll N=10009;
ll f[N][2],tmp[N][2];
vector<pair<ll,ll>>vc; 
ll x[N],t[N];
int main(){
	ll n;cin>>n;
	while(n--){
		ll a,b,t;cin>>a>>b>>t;
		vc.emplace_back(a,t);
		vc.emplace_back(b,t);
	}
	sort(all(vc));
	for(auto _:vc)x[++n]=_.first,t[n]=_.second;
	f[1][0]=max(x[1],t[1]);
	f[1][1]=max(x[n],t[n]);
	ll ans=4e18;
	Rep(len,1,n-1){
		rep(i,1,n)tmp[i][0]=tmp[i][1]=4e18;
		rep(l,1,n-len+1){
			ll r=l+len-1;
			ll &g0=tmp[l][0],&g1=tmp[l][1];
			if(l>1){
				g0=min(g0,f[l-1][0]+x[l]-x[l-1]);
				g1=min(g1,f[l-1][0]+x[r]-x[l-1]);
			}
			if(r<n){
				g0=min(g0,f[l][1]+x[r+1]-x[l]);
				g1=min(g1,f[l][1]+x[r+1]-x[r]);
			}
			g0=max(g0,t[l]);
			g1=max(g1,t[r]);
			if(len==1)ans=min(ans,g0);
		}
		swap(f,tmp);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：4)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-p11432.html)

这题真难吧，机房一车人没一个会做？？

## 思路

首先你如果不对这个题进行什么深入挖掘，八成是想不出任何多项式做法的啊，然后注意到这个数据范围，在不存在可行的贪心策略的情况下，基本就是让你去设计一个 $\mathcal{O(n^2)}$ 的 dp 没跑了。

但他这个关灯的轨迹看起来非常的神秘，无规律可循，怎么才能把它转化成一个便于 dp 的形式呢？

发现一个事情：我们的起点是最左边，如果从一开始没有一路关到底的话，中间没有被关的灯迟早还是需要再折返回来关一次。

然后看到题目里给的限制是必须在 $\geq t$ 的时刻关掉区间里的灯，因此拖到折返的时候再关被空出来的地方后面的灯就是更划算的。那么你现在已经关掉了前缀的一段灯，如果从某个位置开始停止关闭前缀的灯，还需要向右走吗？那必然是需要的，否则直接从头关到尾不就好了吗（感觉像废话文学 T T）。那么此时向右走的目标就很明确了，即走到最右边去关闭后缀的一串灯，后面的过程与刚开始的时候类似。

由此我们便描绘出了本题的重要结论：任意时刻场上未被关闭的灯一定构成一段连续区间。到这里设计 dp 就变得不那么无从下手了。
  
设 $f_{l,r,0}$ 为关掉了除 $(l,r]$ 以外的所有灯、当前位置为 $l$ 所需的最小时间，$f_{l,r,1}$ 为关掉了 $[l,r)$ 外的所有灯，当前位置在 $r$ 所需的最小时间。于是有转移：

$$f_{l,r,0}=\max(\min(f_{l-1,r,0}+\operatorname{dis}(l-1,l),f_{l,r+1,1}+\operatorname{dis}(r+1,l)),t_l)$$

$$f_{l,r,1}=\max(\min(f_{l,r+1,1}+\operatorname{dis}(r+1,r),f_{l-1,r,0}+\operatorname{dis}(l-1,r)),t_r)$$

其中 $\operatorname{dis}(i,j)$ 代表从 $i$ 走到 $j$ 的距离，$t_x$ 代表允许关掉第 $x$ 个灯的最晚时间。解释一下式子的意义：以当前在 $l$ 即这一步关掉了 $l$ 处的灯的情况为例，则上一步要么是从 $l-1$ 顺着走过来，要么就是关完 $r+1$ 后折返回来。

具体实现上先把所有关键点离散化一下，然后暴力对所有区间的限制取 max，因为有 $10^4$ 个点，两维 dp 数组可能开不太下，由于 $l,r$ 的转移只与 $l-1,r$ 和 $l,r+1$ 的状态有关，可以倒着枚举 $r$ 然后滚动数组一下。由于关灯过程一定在一个地方结束，答案就是所有 $f_{i,i,0/1}$ 取 min。

时间复杂度 $\mathcal{O}(n^2)$。

---

## 作者：sc6666f (赞：3)

# P11432 [COCI 2024/2025 #2] 流明 / Blistavost


### 思路：


首先要挖掘性质，模拟一下关灯的过程可以发现关一个区间中的灯时，首尾的灯一定是要被关掉的，也就是说当首尾的灯被关掉之后，区间中的所有灯都可以被关掉。那么就可以把区间中的无数盏灯关闭的问题转化成关闭区间首尾的灯的问题。

那么可以将这些首尾灯单独拎出来，按照坐标大小排序。

然后可以想到，如果说 $[l,r]$ 中的 $l,r$ 都没有被关，（$l,r$ 是灯在坐标数组中的下标），是需要把$[l,r]$中所有的点都再跑一遍，这样才能关掉 $l,r$ 两盏灯的，那么跑这一趟其实完全可以等价于只关 $l,r$，保持剩下的所有灯全部亮着，也就是 $(l,r)$ 为一段亮着的灯的连续区间，由此可以想出状态的定义：

设 $f_{i,j,0}$ 表示 $(i,j]$ 中全为亮灯且剩余灯全部被关闭的最小时间，$f_{i,j,1}$ 表示 $[i,j)$ 中全为亮灯且剩余灯全部被关闭的最小时间。

则有：
$$
\begin{cases}
f_{i,j,0}=\min\{\max\{f_{i-1,j,0}+\operatorname{dis}(i-1,i),t_i\},\max\{f_{i,j+1,1}+\operatorname{dis}(j+1,i),t_i\}\}\\
f_{i,j,1}=\min\{\max\{f_{i-1,j,0}+\operatorname{dis}(i-1,j),t_j\},\max\{f_{i,j+1,1}+\operatorname{dis}(j,j+1),t_j\}\}
\end{cases}
$$


然后空间就爆炸了。

若固定 $i$ 时，$j$ 和 $len$ 成正比，那么把 $j$ 全部换成 $len$，然后可以发现 $f_{i,len,{0/1}}$ 仅和 $f_{i,len+1,0/1}$ 有关，再滚动一下就可以了。

code:

~~~c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+100;
struct light{
	int pos,t,id;
	friend bool operator<(light a,light b){
		return a.pos<b.pos;
	}
}a[N];
int ans=4e18,tot,f[N][2][2],n;
inline int dis(int x,int y){
	return abs(a[x].pos-a[y].pos);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int l,r,t;
		cin>>l>>r>>t;
		a[++tot]=light{l,t,tot};
		a[++tot]=light{r,t,tot};
	}
	memset(f,0x6f,sizeof(f));
	sort(a+1,a+1+tot);
	f[1][tot%2][1]=max(a[tot].t,a[tot].pos);//[1,n)
	f[1][tot%2][0]=max(a[1].t,a[1].pos);
	for(int len=tot-1;len>=1;len--){
		for(int i=1;i+len-1<=tot;i++){
			int j=i+len-1;
			f[i][len%2][0]=f[i][len%2][1]=4e18;
			if(i-1){
				f[i][len%2][0]=min(f[i][len%2][0],max(f[i-1][(len+1)%2][0]+dis(i-1,i),a[i].t));
				f[i][len%2][1]=min(f[i][len%2][1],max(f[i-1][(len+1)%2][0]+dis(i-1,j),a[j].t));
			}
			if(j+1<=tot){
				f[i][len%2][0]=min(f[i][len%2][0],max(f[i][(len+1)%2][1]+dis(i,j+1),a[i].t));
				f[i][len%2][1]=min(f[i][len%2][1],max(f[i][(len+1)%2][1]+dis(j,j+1),a[j].t));
			}
			if(len==1){
				ans=min(ans,f[i][len%2][0]);
				ans=min(ans,f[i][len%2][1]);
			}
		}
	}
	cout<<ans;
	
	return 0;
}
~~~

---

## 作者：huangzixi071018 (赞：2)

# 题目大意:
需要我们在特定的时间后熄灭 $l$ 到 $r$ 盏灯，初始时在原点上。

# 思路:
有一个特别难想的做法，可以将区间拆解为两个点在 $t$ 这个时刻之前这两盏灯不能熄灭，所以可以先对它进行排序。然后设计区间 $DP$。$dp_{i,j,0/1}$ 表示除了 $i$ 和 $j$ 之间的灯是亮的其他都熄灭了且当前在区间的最左边或最右边。每一种情况都可以由 $i-1$ 和 $j+1$ 转移过来（详细转移请看代码），但是要和时间取一个最大值，因为没到时间不能熄灭。最后因为空间会爆，所以要记录上一个长度的 $dp$ 数组，来消掉一维。

# 三维代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5005;
const ll inf=LONG_LONG_MAX;
ll dp[2*N][2*N][2];
struct node{
	ll x,t;
}a[2*N];
bool cmp(node x,node y){
	if(x.x==y.x){
		return x.t<y.t;
	}
	return x.x<y.x;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll n,ans=inf;
	cin>>n;
	for(int i=1;i<=n;i++){
		ll l,r,t;
		cin>>l>>r>>t;
		a[i*2-1]={l,t};
		a[i*2]={r,t};
	}
	n=n*2;
	sort(a+1,a+1+n,cmp);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			dp[i][j][0]=inf;
			dp[i][j][1]=inf;
		}
	}
	dp[1][n][0]=max(a[1].x,a[1].t);
	dp[1][n][1]=max(a[n].x,a[n].t);
	for(int len=n;len>=1;len--){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(i-1>=1){
				dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][0]+a[i].x-a[i-1].x);
				dp[i][j][1]=min(dp[i][j][1],dp[i-1][j][0]+a[j].x-a[i-1].x);
			}
			if(j+1<=n){
				dp[i][j][1]=min(dp[i][j][1],dp[i][j+1][1]+a[j+1].x-a[j].x);
				dp[i][j][0]=min(dp[i][j][0],dp[i][j+1][1]+a[j+1].x-a[i].x);
			}
			dp[i][j][0]=max(dp[i][j][0],a[i].t);
			dp[i][j][1]=max(dp[i][j][1],a[j].t);
			if(len==1){
				ans=min(ans,min(dp[i][j][1],dp[i][j][0]));
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
# 正解代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5005;
const ll inf=LONG_LONG_MAX;
ll dp[2*N][2],p[2*N][2];
struct node{
	ll x,t;
}a[2*N];
bool cmp(node x,node y){
	if(x.x==y.x){
		return x.t<y.t;
	}
	return x.x<y.x;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll n,ans=inf;
	cin>>n;
	for(int i=1;i<=n;i++){
		ll l,r,t;
		cin>>l>>r>>t;
		a[i*2-1]={l,t};
		a[i*2]={r,t};
	}
	n=n*2;
	sort(a+1,a+1+n,cmp);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			dp[i][0]=inf;
			dp[i][1]=inf;
		}
	}
	dp[1][0]=max(a[1].x,a[1].t);
	dp[1][1]=max(a[n].x,a[n].t);
	for(int len=n;len>=1;len--){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(i-1>=1){
				dp[i][0]=min(dp[i][0],p[i-1][0]+a[i].x-a[i-1].x);
				dp[i][1]=min(dp[i][1],p[i-1][0]+a[j].x-a[i-1].x);
			}
			if(j+1<=n){
				dp[i][1]=min(dp[i][1],p[i][1]+a[j+1].x-a[j].x);
				dp[i][0]=min(dp[i][0],p[i][1]+a[j+1].x-a[i].x);
			}
			dp[i][0]=max(dp[i][0],a[i].t);
			dp[i][1]=max(dp[i][1],a[j].t);
			if(len==1){
				ans=min(ans,min(dp[i][1],dp[i][0]));
			}
		}
		for(int i=1;i<=n;i++){
			p[i][0]=dp[i][0];
			p[i][1]=dp[i][1];
			dp[i][0]=inf;
			dp[i][1]=inf;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：huhangqi (赞：1)

直接处理并不方便，尝试找一些性质。

首先，我们需要关闭的是一段区间，而无论我们从这个区间左边右边还是中间开始处理，都是在左端点或者右端点结束。

由于关灯不需要时间，那么可以将这些区间简化为只存在左右端点的灯。

那么这样我们只需要处理这些端点的灯就可以了。

继续观察可以发现，只要两个端点的灯还亮着，那么我们只需要在关闭这两个灯时，把中间亮着的灯都关了就好了，所以我们只需要管目前剩余的左右两端的灯。

那么我们就容易想到设置状态 $dp_{l,r,0/1}$ 分别表示最左端的灯的位置和最右端的灯的位置以及自己目前在哪一端。

转移只需要选择去关掉左边还是关掉右边即可。

转移过后还需要看看想关掉的灯是否可以关了，如果不行，那么需要等待到这个时间，直接和关灯时间取较大值即可完成。

具体转移直接看代码即可。

但是这样空间不够，空间不够的 dp 题目最常见的就是滚动数组优化。

这道题目明显可以使用滚动数组优化，直接优化即可。

剩下的内容就是朴素区间 dp 了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt,dp[2][10005][2],ans;
struct P{
	int x,t;
}a[10005];
bool cmp(P a,P b){
	return a.x<b.x;
}
signed main(){
	cin>>n;
	for(int i=1,l,r,t;i<=n;i++){
		cin>>l>>r>>t;
		a[++cnt]={l,t},a[++cnt]={r,t};
	}
	sort(a+1,a+cnt+1,cmp);
	memset(dp,0x3f,sizeof(dp));
	ans=8e18;
	dp[0][1][0]=max(a[1].x,a[1].t);
	dp[0][1][1]=max(a[cnt].x,a[cnt].t);
	for(int len=cnt-1,id=0;len>=1;len--){
		id^=1;
		memset(dp[id],0x3f,sizeof(dp[id]));
		for(int l=1;l+len-1<=cnt;l++){
			int r=l+len-1;
			if(l>1){
				dp[id][l][0]=min(dp[id][l][0],dp[id^1][l-1][0]+a[l].x-a[l-1].x);
				dp[id][l][1]=min(dp[id][l][1],dp[id^1][l-1][0]+a[r].x-a[l-1].x);
			}
			if(r<cnt){
				dp[id][l][0]=min(dp[id][l][0],dp[id^1][l][1]+a[r+1].x-a[l].x);
				dp[id][l][1]=min(dp[id][l][1],dp[id^1][l][1]+a[r+1].x-a[r].x);
			}
			dp[id][l][0]=max(dp[id][l][0],a[l].t);
			dp[id][l][1]=max(dp[id][l][1],a[r].t);
			if(len==1)ans=min(ans,min(dp[id][l][0],dp[id][l][0]));
		}
	}
	cout<<ans;
	return 0;
}
``````

---

## 作者：Kingna (赞：1)

首先一个区间 $[l_i,r_i]$ 关灯，不可能从中间开始关，则一定是以一个端点开始一个个关。那么只需要存储 $l_i$ 和 $r_i$ 这两盏灯，因为若这两盏灯都关了，那么整个区间也随之关闭。

同时探讨关灯轨迹。首先是关一段前缀的灯，然后绕开中间部分去关后缀的灯。总的来说，未被关的灯是一段区间。

那么这样就很好 dp 了，定义 $f_{i,j,0/1}$ 表示还有 $[i,j]$ 的灯未被关闭，当前在 $i$ 或者 $j$。复杂度 $O(n^2)$。

同时发现这样空间复杂度较高，可以滚动一维，我们将区间 $(i,j)$ 的状态替换为 $(i,j-i+1)$，也就是变成区间长度。因为区间 dp 的区间长度是逐渐增加，则可以滚动。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 10005;

int n, tot, f[2][N][2], INF = 4e18, res = INF;

struct edge {
  int x, t;
}ed[N];

int dist(int l, int r) {
  return abs(ed[l].x - ed[r].x);
}

signed main() {
  cin >> n;
  _for(i, 1, n) {
    int l, r, t;
    cin >> l >> r >> t;
    ed[++tot] = {l, t};   
    ed[++tot] = {r, t}; 
  }
  sort(ed + 1, ed + tot + 1, [](edge x, edge y) { return x.x < y.x; });
  f[tot & 1][1][0] = max(ed[1].x, ed[1].t);
  f[tot & 1][1][1] = max(ed[tot].x, ed[tot].t);
  _pfor(len, tot - 1, 1) {  
    _for(l, 1, tot - len + 1) {
      int r = l + len - 1; 
      f[len & 1][l][0] = min(((l >= 2) ? max(f[(len + 1) & 1][l - 1][0] + dist(l - 1, l), ed[l].t) : INF), 
        ((r + 1 <= tot) ? max(f[(len + 1) & 1][l][1] + dist(r + 1, l), ed[l].t) : INF));
      f[len & 1][l][1] = min(((l >= 2) ? max(f[(len + 1) & 1][l - 1][0] + dist(l - 1, r), ed[r].t) : INF), 
        ((r + 1 <= tot) ? max(f[(len + 1) & 1][l][1] + dist(r + 1, r), ed[r].t) : INF)); 
      if (len == 1) res = min(res, min(f[len & 1][l][1], f[len & 1][l][0])); 
    }
  }
  cout << res << endl;
}
```

---

## 作者：qwer6 (赞：1)

## 1. Description

在一条数轴的每个整数点上有一盏点亮的灯

有若干个要求，每个要求形如 $(l,r,t)$，表示需要熄灭 $[l,r]$ 区间内的所有灯，且在 $t$ 时刻之前不能熄灭这个区间内的任意一盏灯。

在初始时刻，你在原点处，在每个时刻，可以选择向左移动一个单位，向右移动一个单位，或者在原地不动，当你与一盏点亮的灯重合时，可以不消耗任何时间关掉这盏灯，问最少需要多少时间来满足所有要求。

## 2. Solution

首先熄灭 $[l,r]$ 这个区间内的所有灯显然是诈骗的条件，你不可能走到中间才开始关灯，因为这样一定不如在 $l$ 或 $r$ 等到 $t$ 时刻在顺着关过去优，所以可以将要求转换为在 $t$ 时刻及以后熄灭 $l$ 和 $r$ 两盏灯。

这样转换以后，这个问题就类似于[这道题](https://www.luogu.com.cn/problem/P1220)了，那么我们参照这道题，定义状态为 $f_{l,r,0/1}$，表示剩下 $[l,r]$ 的灯没关，现在在 $l$ 或 $r$，需要的最少时间。

转移是显然的：
$$
f_{l,r,0}=\max(t_l,f_{l-1,r,0}+1,f_{l,r+1,1}+r+1-l)\\
f_{l,r,1}=\max(t_r,f_{l-1,r,0}+r-l+1,f_{l,r+1,1}+1)
$$
其中 $t_x$ 表示可以关闭 $x$ 这盏灯的最早时间。

但是我们发现 $l,r$ 的值域很大，需要离散化，所以转移对应就变成了：
$$
f_{l,r,0}=\max(t_l,f_{l-1,r,0}+x_l-x_{l-1},f_{l,r+1,1}+x_{r+1}-x_l)\\
f_{l,r,1}=\max(t_r,f_{l-1,r,0}+x_r-x_{l-1},f_{l,r+1,1}+x_{r+1}-x_r)
$$
其中 $x_i$ 表示离散化后 $i$ 对应的值。

这样的空间复杂度是 $O(n^2)$，但是有 $8$ 倍的常数，所以会 MLE，考虑优化空间。

我们发现长度为 $len$ 的状态都是从长度为 $len+1$ 的状态转移过来的，因此使用滚动数组优化空间，而由于长度是枚举得出的，所以状态只需要记录左端点即可，那么空间复杂度就是 $O(n)$ 的了。  

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=5005;
int n,tot,ans;
int x[N<<1],t[N],tmp[N<<1],val[N<<1],f[N<<1][2],g[N<<1][2];
signed main(){
	read(n);
	for(int i=1;i<=n;i++)
		tmp[i]=read(x[i]),tmp[i+n]=read(x[i+n]),read(t[i]);
	sort(tmp+1,tmp+2*n+1);
	tot=unique(tmp+1,tmp+2*n+1)-tmp-1;
	for(int i=1,p;i<=2*n;i++){
		p=lower_bound(tmp+1,tmp+tot+1,x[i])-tmp;
		tomax(val[p],i>n?t[i-n]:t[i]);
	}
	g[1][0]=max(val[1],tmp[1]);;
	g[1][1]=max(val[n],tmp[tot]);
	for(int i=tot-1;i>=1;i--){
		for(int l=1,r=i;r<=tot;l++,r++){
			f[l][0]=f[l][1]=8e18; 
			if(l>1){
				tomin(f[l][0],max(val[l],g[l-1][0]+tmp[l]-tmp[l-1]));
				tomin(f[l][1],max(val[r],g[l-1][0]+tmp[r]-tmp[l-1]));
			}
			if(r<tot){
				tomin(f[l][0],max(val[r],g[l][1]+tmp[r+1]-tmp[l]));
				tomin(f[l][1],max(val[r],g[l][1]+tmp[r+1]-tmp[r]));
			}
		}
		for(int l=1,r=i;r<=tot;l++,r++)
			g[l][0]=f[l][0],g[l][1]=f[l][1];
	}
	ans=8e18;
	for(int i=1;i<=tot;i++)
		tomin(ans,min(f[i][0],f[i][1]));
	write(ans);
}
```

---

