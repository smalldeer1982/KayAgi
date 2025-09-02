# [ABC197E] Traveler

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc197/tasks/abc197_e

数直線上にボール $ 1 $ からボール $ N $ までの $ N $ 個のボールがあります。  
 ボール $ i $ は座標 $ X_i $ にあります。  
 各ボールには $ 1 $ 以上 $ N $ 以下の整数で表される色がついていて、ボール $ i $ の色は整数 $ C_i $ で表されます。  
 今座標 $ 0 $ にいるあなたは、毎秒 $ 1 $ の速さで数直線上を動き、全てのボールを回収してから再び座標 $ 0 $ に戻ります。  
 このとき、ボールの色を表す整数を回収順に並べた時に広義単調増加となっている必要があります。  
 ボールを回収するにはボールと同じ座標にいる必要がありますが、ボールを回収できる時に必ずしも回収する必要はありません。  
 座標 $ 0 $ を出発してから、全てのボールを回収して再び座標 $ 0 $ に戻るまでにかかる時間の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ |X_i|\ \le\ 10^9 $
- $ X_i\ \neq\ X_j\ (i\ \neq\ j) $
- $ X_i\ \neq\ 0 $
- $ 1\ \le\ C_i\ \le\ N $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

以下のように行動するのが最適です。 - $ 3 $ 秒かけて座標 $ 3 $ に移動し、ボール $ 2 $ を回収する - $ 1 $ 秒かけて座標 $ 2 $ に移動し、ボール $ 1 $ を回収する - $ 2 $ 秒かけて座標 $ 4 $ に移動し、ボール $ 4 $ を回収する - $ 1 $ 秒かけて座標 $ 5 $ に移動し、ボール $ 5 $ を回収する - $ 4 $ 秒かけて座標 $ 1 $ に移動し、ボール $ 3 $ を回収する - $ 1 $ 秒かけて座標 $ 0 $ に戻る ボールの色を表す整数を回収順に並べると $ 1,\ 2,\ 2,\ 3,\ 3 $ と広義単調増加になっています。

## 样例 #1

### 输入

```
5
2 2
3 1
1 3
4 2
5 3```

### 输出

```
12```

## 样例 #2

### 输入

```
9
5 5
-4 4
4 3
6 3
-5 5
-3 2
2 2
3 3
1 4```

### 输出

```
38```

# 题解

## 作者：ycy1124 (赞：1)

### 题意
题意很简单，这里不多讲。
### 思路
发现这是一道很裸的 dp 题。我们发现，每次取某个编号的所有点的策略一定是从当前点这些点中最左或最右的任意一个然后在走到另一个。至于为什么要这样做，我们考虑往左走到一半往右走，由于还是要回来取最左边的点的，所以会导致回头的这一段比上述方案至少多走一次，肯定是不优的。于是我们可以设 $dp_{i,0/1}$ 表示走到所有编号为 $i$ 的点后停在最左边的点和最右边的点所需的最小时间。每次只需要从上次的两端转移即可。具体转移方程见代码，需要注意的是最后要回到 $0$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,dp[200005][2],l[200005],r[200005],las;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		l[i]=1e18;
		r[i]=-1e18;
	}
	for(int i=1;i<=n;i++){
		int x,c;
		cin>>x>>c;
		l[c]=min(l[c],x);
		r[c]=max(r[c],x);
	}
	for(int i=1;i<=n;i++){
		if(l[i]==1e18||r[i]==-1e18){
			continue;
		}
		dp[i][0]=min(dp[las][1]+abs(r[i]-l[i])+abs(r[las]-r[i]),dp[las][0]+abs(l[las]-r[i])+abs(r[i]-l[i]));
		dp[i][1]=min(dp[las][1]+abs(l[i]-r[i])+abs(l[i]-r[las]),dp[las][0]+abs(l[i]-r[i])+abs(l[i]-l[las]));//最终要走到右端，所以肯定先从上一个位置走到左端，再走到右端。最终走到左端同理。
		las=i;//记录上一个编号
	} 
	cout<<min(dp[las][0]+abs(l[las]),dp[las][1]+abs(r[las]));
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/206680606)。

---

## 作者：Lcm_simida (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc197_e)

很明显，只要经过同一编号最左的点和最右的点即可经过此编号的所有点，无需证明。由此我们可以将题目转换成有 $m$ 个区间，需要依次经过每个区间，求出最小的时间代价。

求出 $m$ 个区间的左右端点，再线性动规即可。

每次只需取上个编号的左端点和右端点转移过来的最小值即可。
## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,num=0,dp[200005][2];//0:左，1：右 
struct node{
	long long l,r;
}a[200005],c[200005];
bool cmp(node x,node y){
	return x.r<y.r||(x.r==y.r&&x.l<y.l);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	for(long long i=1;i<=n;i++) cin>>c[i].l>>c[i].r;
	sort(c+1,c+n+1,cmp);
	for(long long i=1;i<=n;i++){
		if(c[i].r!=c[i-1].r){a[++num].l=c[i].l;a[num].r=c[i].l;}
		a[num].r=max(a[num].r,c[i].l);
	}
	dp[1][0]=abs(a[1].r)+abs(a[1].r-a[1].l);
	dp[1][1]=abs(a[1].l)+abs(a[1].l-a[1].r);
	for(long long i=2;i<=num;i++){
		dp[i][0]=min(dp[i-1][0]+abs(a[i-1].l-a[i].r)+abs(a[i].r-a[i].l),dp[i-1][1]+abs(a[i-1].r-a[i].r)+abs(a[i].r-a[i].l));
		dp[i][1]=min(dp[i-1][0]+abs(a[i-1].l-a[i].l)+abs(a[i].l-a[i].r),dp[i-1][1]+abs(a[i-1].r-a[i].l)+abs(a[i].l-a[i].r));
	}
	cout<<min(dp[num][0]+abs(a[num].l),dp[num][1]+abs(a[num].r));
	return 0;
}
```

---

## 作者：dangerous_DZR (赞：0)

# AT_abc197_e [ABC197E] Traveler 题解
## 分析
### 题意
在一条数轴上有 $n$ 个节点，按优先级分为一些区间，需求出从原点出发按优先级轮流经过每段区间后回到原点的最短距离。
### 前置结论
当下一步要走的区间包含上一步终点时，最优策略必然为先左后右或先右后左。
#### 证明
设上一步终点为 $x$，当前经过的区间中节点按升序在点 $x$ 两侧分别为 $a_l$ 至 $a_m$ 和 $a_{m + 1}$ 至 $a_r$。则大致有三种策略:  
- 从点 $x$ 走至点 $a_l$ 后再到点 $a_r$，总路程为：

$$(x - a_l) + (a_r - a_l) = x + a_r - 2 \times a_l$$

- 从点 $x$ 走至点 $a_r$ 后再到点 $a_l$，总路程为：

$$(a_r - x) + (a_r - a_l) = 2 \times a_r - x - a_l$$

- 从点 $x$ 开始，在点 $x$ 两边反复横跳，总路程为：

$$(x - a_m) + (a_{m + 1} - a_m) + (a_{m + 1} - a_{m - 1}) + (a_{m + 2} - a_{m - 1}) + ... + (a_{r - 1} - a_l) + (a_r - a_l)$$

易得，前两种策略最优。
## 解题思路
由题意得：
- 每段区间的最小路程必然是总最小路程的一部分，满足最优子结构性质。
- 每段区间的终点都是下一段区间新的起点，求当前区间的最短路程不需要知道之前的起点和路径，满足无后效性。

——所以，我们可以通过动态规划求解！

设 $f_{i, 0}$ 表示前 $i - 1$ 段区间中终点为区间左端点时的最短路径 $f_{i, 1}$ 表示前 $i - 1$ 段区间中终点为区间右端点时的最短路径 $nowl_i$ 和 $nowr_i$ 分别表示第 $i$ 段区间中节点的左右端点。

思考一下可以得到转移：

- $$f_{i, 0} = \min(f_{i - 1, 0} + \left|nowl_{i - 1} - nowr_i\right| + \left|nowl_i - nowr_i\right|, f_{i - 1, 1} + \left|nowr_i - nowr_{i - 1}\right| + \left|nowl_i - nowr_i\right|)$$
- $$f_{i, 1} = \min(f_{i - 1, 0} + \left|nowl_{i - 1} - nowl_i\right| + \left|nowl_i - nowr_i\right|, f_{i - 1, 1} + \left|nowl_i - nowr_{i - 1}\right| + \left|nowl_i - nowr_i\right|)$$

## 代码（压行有点猛）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, sum, f[200010][3];
vector<int> now[200010];
pair<int, int> a[200010];
signed main(){
	cin >> n;
	for (int i = 1; i <= n; i ++)cin >> a[i].second >> a[i].first;
	sort(a + 1, a + n + 1);//按优先级排序
	for (int i = 1; i <= n; i ++)sum += (a[i].first != a[i - 1].first), now[sum].push_back(a[i].second);//按优先级划分区间
	f[0][1] = f[0][0] = 0, now[0].push_back(0);//初始化，从原点出发
	for (int i = 1; i <= sum; i ++){
		sort(now[i].begin(), now[i].end());//区间内节点升序排序
		f[i][0] = min(f[i - 1][0] + abs(now[i - 1][0] - now[i][now[i].size() - 1]) + abs(now[i][0] - now[i][now[i].size() - 1]), f[i - 1][1] + abs(now[i][now[i].size() - 1] - now[i - 1][now[i - 1].size() - 1]) + abs(now[i][0] - now[i][now[i].size() - 1])), f[i][1] = min(f[i - 1][0] + abs(now[i - 1][0] - now[i][0]) + abs(now[i][0] - now[i][now[i].size() - 1]), f[i - 1][1] + abs(now[i][0] - now[i - 1][now[i - 1].size() - 1]) + abs(now[i][0] - now[i][now[i].size() - 1]));
        //转移如上
	}
	cout << min(f[sum][0] + abs(now[sum][0]), f[sum][1] + abs(now[sum][now[sum].size() - 1]));
    //别忘了回到原点
	return 0;
}
```
完结撒花（如有错误还请不吝指出）！

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
挺水的一道 dp 题。

观察到每一种颜色取完之后的位置一定在这个颜色的左右两端点上，考虑证明：

如果取完之后的位置在左右两端点之间，那么对其分讨：
- 如果接下来往左走，那么就可以转化为是从其右端点走过来的，这样答案不会改变，因为最右端你总得取，所以是可行的。
- 往右走也同理。

那么之后就很好做了，直接线性 dp 每种颜色一步步推下来即可。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 400005
using namespace std; 
int n;
struct node{
	ll x,c;
}e[N];
bool cmp(node x,node y){
	if(x.c==y.c) return x.x<y.x;
	else return x.c<y.c;
}
ll dp[N][2];
int pos[N][2];
int col[N],cnt;
main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>e[i].x>>e[i].c;
	}
	++n;
	e[n].x=0,e[n].c=n;
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(e[i].c!=e[i-1].c){
			pos[e[i].c][0]=e[i].x;
			pos[e[i-1].c][1]=e[i-1].x;
			col[++cnt]=e[i].c;
		}
	}
	pos[0][0]=0;
	pos[e[n].c][1]=e[n].x;
	for(int i=1;i<=cnt;i++){
		int v=col[i],u=col[i-1];
		dp[v][0]=min(dp[u][0]+abs(pos[v][1]-pos[u][0])+pos[v][1]-pos[v][0],dp[u][1]+abs(pos[v][1]-pos[u][1])+pos[v][1]-pos[v][0]);
		dp[v][1]=min(dp[u][0]+abs(pos[v][0]-pos[u][0])+pos[v][1]-pos[v][0],dp[u][1]+abs(pos[v][0]-pos[u][1])+pos[v][1]-pos[v][0]);
	}
	cout<<dp[col[cnt]][1];
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

## 前言：
刷 dp 题时发现这道题还能交题解，写一发。
## 题目分析：
刚开始想了一手贪心，但是分讨太多，还假了，那么顺势考虑 dp。

考虑对于一段相同颜色的区间来说，移动的距离实际上只用关注左右端点即可，由此设计状态 $dp[i][0/1]$ 表示扫完 $i$ 颜色后所停在左端点还是右端点。

延续贪心的思路，考虑对于当前颜色和下一个颜色所覆盖的区间以及左右端点之间的距离关系，分讨转移即可（由于作者画图软件似了，就先不贴图了，以后有机会再补。）这段在代码中有详细说明，故不再解释。

注意，最后扫完是需要回到 $0$ 端点的，于是可以将两个 $0$ 分别插入左右端点数组中进行处理，这里作者所使用的是 vector 容器。  
另，记得开 long long。
## Code:
```cpp
#include<bits/stdc++.h>
#define starrail main
#define re register
#define il inline
using namespace std;
typedef long long ll;
il ll read(){
	ll w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=(s<<1)+(s<<3)+(ch^48);ch=getchar();}
	return w*s;
}
const ll N=2e5+10,INF=1e18;
int n;
ll dp[N][2],l[N],r[N];
vector<ll>l2,r2;
signed starrail(){
	n=read();
	for(int i=1;i<=n;i++)
		l[i]=INF,r[i]=-INF;
	for(int i=1;i<=n;i++){
		ll x=read(),c=read();
		l[c]=min(l[c],x);
		r[c]=max(r[c],x);
	}
	l2.push_back(0);
	r2.push_back(0);
	for(int i=1;i<=n;i++){
		if(l[i]!=1e18){
			l2.push_back(l[i]);
			r2.push_back(r[i]);
		}
	}
	l2.push_back(0);
	r2.push_back(0);
	n=l2.size();
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=dp[0][1]=0;
	for(int i=0;i<n-1;i++){
		if(l2[i]<=l2[i+1])//没有交叉 
			dp[i+1][1]=min(dp[i+1][1],dp[i][0]+r2[i+1]-l2[i]);
		else if(r2[i+1]<=l2[i])//有交叉 
			dp[i+1][0]=min(dp[i+1][0],dp[i][0]+l2[i]-l2[i+1]);
		else{
			dp[i+1][1]=min(dp[i+1][1],dp[i][0]+l2[i]-l2[i+1]+r2[i+1]-l2[i+1]);
			dp[i+1][0]=min(dp[i+1][0],dp[i][0]+r2[i+1]-l2[i]+r2[i+1]-l2[i+1]);
		}
		if(r2[i]<=l2[i+1])//没有交叉 
			dp[i+1][1]=min(dp[i+1][1],dp[i][1]+r2[i+1]-r2[i]);
		else if(r2[i+1]<=r2[i])//覆盖关系 
			dp[i+1][0]=min(dp[i+1][0],dp[i][1]+r2[i]-l2[i+1]);
		else{
			dp[i+1][1]=min(dp[i+1][1],dp[i][1]+(r2[i]-l2[i+1])+(r2[i+1]-l2[i+1]));
			dp[i+1][0]=min(dp[i+1][0],dp[i][1]+(r2[i+1]-r2[i])+(r2[i+1]-l2[i+1]));
		}
	}
	printf("%lld\n",min(dp[n-1][0],dp[n-1][1]));
	return 0;
}
```

---

## 作者：Charles_with_wkc (赞：0)

# 思路：
**线性 dp**。 
# 线性DP：
$l$ 指代上一次的 $L$。  
$r$ 指代上一次的 $R$。  
$L$ 指本次的 $L$。  
$R$ 指本次的 $R$。  
$last$ 上一次存在是多少。  
$r_n$ 是相同的值的坐标最大的。   
$r_1$ 是相同的值的坐标最小的。   
$dp_{c,0}$ 是算到第 $c$ 中时停留在左边。   
$dp_{c,1}$ 是算到第 $c$ 中时停留在右边。   
$dp_{c,0}=\min \begin{cases} 
dp_{last,0}+ | r_n-l | +r_n-r_1 \\
					dp_{last,1}+ | r_n-r | +r_n-r_1\\
				\end{cases}$    
从上一次的 $l$ 走到这次的 $R$ 在走到本次的 $L$ 和从上一次的 $r$ 走到这次的 $R$ 再走到本次的 $L$ 这两种情况去最小。     
$dp_{c,1}=\min \begin{cases}
				dp_{last,0}+ | r_1-l | +r_n-r_1\\
				dp_{last,1}+ | r_1-r | +r_1-r_1\\
				\end{cases}$  
从上一次的 $l$ 走到这次的 $L$ 在走到本次的 $R$ 和从上一次的 $r$ 走到这次的 $L$ 再走到本次的 $R$ 这两种情况去最小。  
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,l,r,last,x,y;
vector<int>v[N];
int dp[N][2];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;//x:位置 y:值 
		v[y].push_back(x);//分类 
	}
	for(int c=1;c<=n;c++){//题目中说明了不会超过 n
		if(v[c].size()==0) continue;//不存在
		sort(v[c].begin(),v[c].end());//位置排序
		dp[c][0]=dp[c][1]=v[c].back()-v[c].front();//无论如何多要走一段L->R
		dp[c][0]+=min({dp[last][0]+abs(v[c].back()-l),dp[last][1]+abs(v[c].back()-r)});
		dp[c][1]+=min({dp[last][0]+abs(v[c].front()-l),dp[last][1]+abs(v[c].front()-r)});
      	//l-R-L r-R-L l-L-R r-L-R
		l=v[c].front();r=v[c].back();last=c;//更新 
	}
	cout<<min({dp[last][0]+abs(l),dp[last][1]+abs(r)});
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

## 题目简意

现在有 $n$ 个球，每个球的位置在 $x_i$ 上，并且编号为 $c_i$。你现在从 $0$ 出发，并且每秒只能走一步，并且按照编号单调不减的顺序收集所有的球，并且最终回到 $0$。求出最短时间。

## 分析
### $\tt part1$ 初步判断

关注到需要编号单调不降地收球，那么对于同一种颜色的球，最优方案肯定是从左往右，要么从右往左收集，否则肯定会有至少一段被重复经过。

容易想到按顺序分别考虑每个颜色，进行 dp。

### $\tt part2$ 进一步思考

考虑状态怎么设。

我们目前要记录颜色种类、收集方向等状态。不妨设 $f_{i,0/1}$ 表示收集完前 $i$ 种颜色，从左/右开始收集的最小步数。不妨设每种颜色的最左和最右的球的坐标分别为 $l_i,r_i$。

转移方程显然了：

上次从左边收这次从左边收、上次从右边收这次从左边收：

$$f_{i,0}=\min\{f_{i-1,0}+|r_{i-1}-l_i|,f_{i-1,1}+|l_{i-1}-l_i|\}+|r_i-l_i|$$

上次从左边收这次从右边收、上次从右边收这次从右边收：

$$f_{i,1}=\min\{f_{i-1,0}+|r_{i-1}-r_i|,f_{i-1,1}+|l_{i-1}-r_i|\}+|r_i-l_i|$$

### $\tt part3$ 细节处理
- 有些颜色可能没有球。
- 最后要回到原点 $0$。
- 要开 `long long`。

## $\tt code$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int inf = 1e9 + 10;
int n;
int l[N], r[N];
long long f[N][2];
bool fl[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) l[i] = inf, r[i] = -inf;
    for (int i = 1, x, c; i <= n; i++) {
        cin >> x >> c;
        l[c] = min(l[c], x), r[c] = max(r[c], x), fl[c] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!fl[i]) { // 懒得写什么 last 于是直接往后抄一遍（逃
            f[i][0] = f[i - 1][0], f[i][1] = f[i - 1][1];
            l[i] = l[i - 1], r[i] = r[i - 1];
            continue;
        }
        f[i][0] = min(f[i - 1][0] + abs(r[i - 1] - l[i]), f[i - 1][1] + abs(l[i - 1] - l[i])) + r[i] - l[i];
        f[i][1] = min(f[i - 1][0] + abs(r[i - 1] - r[i]), f[i - 1][1] + abs(l[i - 1] - r[i])) + r[i] - l[i];
    }
    cout << min(f[n][0] + abs(r[n]), f[n][1] + abs(l[n]));
}
```

---

## 作者：gxp123 (赞：0)

# abc197 E - Traveler

## 题意

现在有 $n$ 个球，每个球的位置在 $x_i$ 上，并且编号为 $c_i$。

你现在从 $0$ 出发，并且每秒只能走一步，并且单调不减得收集所有的球，现在让你求最短时间。

## 题解

我们先考虑一种编号 $c$ 的球。

一个显然的结论是我捡完所有编号为 $c$ 的球，我结束的位置必然是这些球中的最左边或最右边。

而因为是要捡走所有球，所以我们一定会去捡走最左边和最右边的球。

假设我们此时已经捡完最左边或最右边的球时候，我们需要再去捡最右或最左边的球。

而这个移动的过程中，我们就可以把顺便把所有除了左右两边的球捡走。

所以我们就有 $dp$ 状态 $f_{i,0/1}$ 表示我捡完所有编号为 $i$ 的球，当前停留在它的左边/右边，所需要的最短时间。

我们再记录一个 $xx_{i,0/1}$ 表示最左边/右边的球的编号。

则：


$$
f_{i,0} = \min(f_{l,0} + |xx_{i,1}-xx_{l,0} |,f_{l,1} + |xx_{i,1}-xx_{l,1} |) + xx_{i,1} - xx_{i,0} 
$$
$$
f_{i,1} = \min(f_{l,0} + |xx_{i,0}-xx_{l,0} |,f_{l,1} + |xx_{i,0}-xx_{l,1} |) + xx_{i,1} - xx_{i,0}
$$

$l$ 指离 $i$ 最近的有球的编号。

答案就是：$\min(f_{l,0}+x_{l,0},f_{l,1}+x_{l,1})$。

这里的 $l$ 指编号最大的有球的编号。

因为还要走回 $1$ 节点，所以要加上最后点的坐标。 

## code


```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
const int maxN = 2e5 + 10;
const int inf = (1 << 30);
ll xx[maxN][3];
ll f[maxN][3];
int n;

int main(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; ++i)   xx[i][1] = -(xx[i][0] = inf); 
    for(ll i = 1,c,x ; i <= n ; ++i){
        scanf("%lld%lld",&x,&c);
        xx[c][0] = min(xx[c][0],x);
        xx[c][1] = max(xx[c][1],x);
        xx[c][2] = 1;
    }
    int l = 0;
    xx[0][0] = xx[0][1] = 0;
    for(int i = 1 ; i <= n ; ++i){
        if(!xx[i][2])   continue;
        f[i][0] = min(abs(xx[i][1] - xx[l][0]) + f[l][0],
                abs(xx[i][1] - xx[l][1]) + f[l][1]) + xx[i][1] - xx[i][0];
        f[i][1] = min(abs(xx[i][0] - xx[l][0]) + f[l][0],
                abs(xx[i][0] - xx[l][1]) + f[l][1]) + xx[i][1] - xx[i][0];
        l = i;
    }
    cout << min(f[l][0] + abs(xx[l][0]),f[l][1] + abs(xx[l][1])) << endl;
    return 0;
}
```

---

## 作者：ForgetOIDuck (赞：0)

### 思路
看到选的颜色单调不减，考虑 dp，设 $dp_i$ 表示选完颜色 $i$ 后的最小距离。

接下来我们需要确定选择这些颜色为 $i$ 的球的顺序。

容易发现开始选球时一定是先到最左边再一直向右，或先到最右边再一直向左。这两种选法是最优的。

于是我们输入时记录每种颜色球的最小和最大坐标，分别为 $l_i$ 和 $r_i$。

为了确定起点，我们给 $dp$ 数组再加一维 $0/1$，表示上一轮的终点是左 $/$ 右端点。

对此我们可以写出转移方程：
$$
dp_{i,0}=\min\{dp_{i-1,0}+|l_{i-1}-r_i|,
dp_{i-1,1}+|r_{i-1}-l_i|\}+|l_i-r_i|,\\dp_{i,1}=\min\{dp_{i-1,0}+|l_{i-1}-l_i|,
dp_{i-1,1}+|r_{i-1}-r_i|\}+|l_i-r_i|.
$$

注意点：

- 可能有没有球的颜色。
- 起点是 $0$。
- 最后要回到 $0$。

时间复杂度 $O(n)$。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, dp[200002][2], minn[200002], maxn[200002];
bool f[200002];
int main() {
	cin >> n;
	for (ll i = 1; i <= n; i ++ ) minn[i] = 0x3f3f3f3f, maxn[i] = -0x3f3f3f3f;
	for (ll i = 1, x, y; i <= n; i ++ ) cin >> y >> x, minn[x] = min(minn[x], y), maxn[x] = max(maxn[x], y), f[x] = 1;
	ll t = 1;
	while (! f[t]) t ++;
	dp[t][0] = abs(maxn[t]) + abs(minn[t] - maxn[t]), dp[t][1] = abs(minn[t]) + abs(minn[t] - maxn[t]);
	for (ll i = t + 1; i <= n; i ++ ) if (f[i])
		dp[i][0] = min(dp[t][0] + abs(minn[t] - maxn[i]), dp[t][1] + abs(maxn[t] - maxn[i])) + abs(minn[i] - maxn[i]),
		dp[i][1] = min(dp[t][0] + abs(minn[t] - minn[i]), dp[t][1] + abs(maxn[t] - minn[i])) + abs(minn[i] - maxn[i]),
		t = i;
	cout << min(dp[t][0] + abs(minn[t]), dp[t][1] + abs(maxn[t]));
}
```

---

