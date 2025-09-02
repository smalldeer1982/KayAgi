# [ABC325F] Sensor Optimization Dilemma

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc325/tasks/abc325_f

キーエンスの工場長であるあなたは、ベルトコンベア上のいくつかの区間をセンサーによって監視したいと考えています。 あなたが監視したい区間は全部で $ N $ 個あり、$ i $ 個目の区間の長さは $ D_i $ メートルです。

センサーには $ 2 $ 種類の候補があり、それぞれのセンサーに関する情報は以下の通りです。

- センサー $ j\ (1\leq\ j\ \leq\ 2) $ : 長さ $ L_j $ メートルの区間を監視できる。 価格は $ 1 $ 個あたり $ C_j $ であり、全体で最大 $ K_j $ 個まで使用することができる。

$ 1 $ つの区間をいくつかの区間に分割して監視することもできます。 また、センサーが監視する区間が重なっていたり、監視したい区間の長さより余分に監視していたりしても問題はありません。 例えば、$ L_1=4,L_2=2 $ であるとき、センサー $ 1 $ を $ 1 $ つ使って長さ $ 3 $ メートルの区間を監視したり、センサー $ 1,2 $ を $ 1 $ つずつ使って長さ $ 5 $ メートルの区間を監視したりすることが可能です。

$ N $ 個の区画をすべて監視することが可能であるか判定し、可能ならば必要なセンサーの価格の総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 100 $
- $ 1\leq\ D_i,L_j\ \leq\ 10^5 $
- $ 1\leq\ C_j\ \leq\ 10^9 $
- $ 1\leq\ K_j\ \leq\ 10^3 $
- 入力は全て整数

### Sample Explanation 1

以下のようにすることで、センサー $ 1 $ を $ 3 $ つ、センサー $ 2 $ を $ 4 $ つ使ってすべての区間を監視できます。 - センサー $ 1 $ を $ 1 $ つ使って $ 1 $ 個目の区間を監視する。 - センサー $ 1,2 $ を $ 1 $ つずつ使って $ 2 $ 個目の区間を監視する。 - センサー $ 1 $ を $ 1 $ つ、センサー $ 2 $ を $ 3 $ つ使って $ 3 $ 個目の区間を監視する。 このとき、必要なセンサーの価格の総和は $ 3\times\ 3\ +\ 2\times\ 4\ =\ 17 $ であり、これが最小です。

### Sample Explanation 3

$ 1 $ つも使わない種類のセンサーがあっても構いません。

## 样例 #1

### 输入

```
3
3 5 10
4 3 3
2 2 6```

### 输出

```
17```

## 样例 #2

### 输入

```
3
3 5 10
4 3 3
2 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
2
4 8
3 1 100
4 10000 100```

### 输出

```
5```

# 题解

## 作者：___OccDreamer___ (赞：7)

提供两种非 $O(nk^2)$ 做法，思路来自 AT 题解。

## $O(nk)$

### $\text{Solution}$

在 $O(nk^2)$ 的基础上优化。

$f_{i,j}$ 表示前 $i$ 个区间，用 $j$ 个一号物品的基础上，最少用多少二号物品。

$$
f_{i,j}=\min_{0\leq k\leq j}\{f_{i-1,j-k}+\left\lceil\frac{\max(d_i-kL_1,0)}{L_2}\right\rceil\}
$$

等价于

$$
f_{i,j}=\min_{0\leq k\leq j}\{f_{i-1,k}+\left\lceil\frac{\max(d_i-(j-k)L_1,0)}{L_2}\right\rceil\}
$$

取 $\max$ 不好处理，进行一个分讨，

$$
f_{i,j}= \min
\begin{cases}
f_{i-1,k}+\left\lceil\frac{d_i-(j-k)L_1}{L_2}\right\rceil & d_i-(j-k)L_1\geq0 \\
f_{i-1,k} &d_i-(j-k)L1<0
\end{cases} 
$$

$<0$ 记下前缀 $\min$ 即可。现在只考虑 $\geq 0$ 时怎么优化。设 $s$ 表示最小的 $k$ 使得 $d_i-(j-k)L_1\geq0$。

把向上取整拿出去，

$$
f_{i,j}= \left\lceil\min_{s\leq k\leq j}\{ f_{i-1,k}+\frac{d_i-(j-k)L_1}{L_2}\}\right\rceil
$$

把与 $k$ 无关的项拿到 $\min$ 外面，

$$
f_{i,j}= \left\lceil\frac{d_i-jL_1}{L_2}+\min_{s\leq k\leq j}\{ f_{i-1,k}+\frac{kL_1}{L_2}\}\right\rceil
$$

单调队列优化即可。

### $\text{Code}$

```cpp
int main()
{
	n=read();
	for(int i=1;i<=n;i++) d[i]=read();
	a.l=read(),a.c=read(),a.k=read();
	b.l=read(),b.c=read(),b.k=read();
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++) {
		hd=1,tl=0;
		ll minn=inf;
		for(int j=0;j<=a.k;j++) {
			int s=max(0LL,(j*a.l-d[i]+a.l-1)/a.l);
			while(hd<=tl&&q[hd]<s) minn=min(minn,1LL*f[i-1][q[hd]]),hd++;
			while(hd<=tl&&1LL*f[i-1][q[tl]]*b.l+q[tl]*a.l>=1LL*f[i-1][j]*b.l+j*a.l) tl--;
			q[++tl]=j;
			f[i][j]=min(minn,(1LL*f[i-1][q[hd]]*b.l+q[hd]*a.l+d[i]-j*a.l+b.l-1)/b.l);
		}
	}
	ans=inf;
	for(int i=0;i<=a.k;i++) {
		if(f[n][i]>b.k) continue;
		ans=min(ans,1LL*i*a.c+1LL*f[n][i]*b.c);
	}
	if(ans==inf) puts("-1");
	else printf("%lld",ans);
	return 0;
}
```

## $O(k^2)$

### $\text{Solution}$

因为 $k$ 较小，可以直接枚举用了多少一号物品，多少二号物品。问题是如何判断是否合法。

设 $f_{i,j}=(k,l)$ 表示用了 $i$ 个一号物品，$j$ 个二号物品，最多覆盖到第 $k$ 个区间的前 $l$ 的位置。注意这个状态是表示一个二元组。

转移时如果 $l>d_k$，$(k,l)\to(k+1,0)$。

### $\text{Code}$

```cpp
int main()
{
	n=read();
	for(int i=1;i<=n;i++) d[i]=read();
	a.l=read(),a.c=read(),a.k=read();
	b.l=read(),b.c=read(),b.k=read();
	f[0][0]=make_pair(1,0);
	for(int i=0;i<=a.k;i++) {
		for(int j=0;j<=b.k;j++) {
			if(i==0&&j==0) continue;
			nwa=nwb=make_pair(0,0);
			if(i>0) {
				nwa=f[i-1][j];
				if(nwa.fi!=n+1) {
					nwa.se+=a.l;
					if(nwa.se>=d[nwa.fi]) nwa.se=0,nwa.fi++;
				}
			}
			if(j>0) {
				nwb=f[i][j-1];
				if(nwb.fi!=n+1) {
					nwb.se+=b.l;
					if(nwb.se>=d[nwb.fi]) nwb.se=0,nwb.fi++;
				}
			}
			f[i][j]=max(nwa,nwb);
		}
	}
	ans=inf;
	for(int i=0;i<=a.k;i++) {
		for(int j=0;j<=b.k;j++) {
			if(f[i][j].fi==n+1) ans=min(ans,1LL*i*a.c+1LL*j*b.c);
		}
	}
	if(ans==inf) puts("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：_Ink (赞：4)

## 题解

考虑 dp。

我们实际上只关心满足要求的情况下，1,2 号传感器选择的个数。得知了个数，我们就能够计算出其的花费。

而对于维护某一段区域，如果我们知道了 1 号传感器使用的个数，是能够计算出 2 号传感器的最少使用个数的。

具体来说，维护第 $i$ 段区域时，其长度为 $D_i$，若选择了 $k_1$ 个 1 号传感器，那么 2 号传感器的最少使用个数 $k_2$ 为：

$$k_2 = \bigg\lceil \frac{\max(D_i-k_1L_1, 0)}  {L_2}\bigg\rceil.$$

于是我们就可以设计 dp。

记 $dp[i][j]$ 为：维护前 $i$ 段区域，已经选择了 $j$ 个 1 号传感器时，2 号传感器的最少使用个数。

那么状态转移方程即为：

$$dp[i][j] = \min_{0 \leq k \leq j} \bigg(dp[i-1][j-k] + \Big\lceil \frac{\max(D_i-kL_1,0)}{L_2} \Big\rceil \bigg).$$

意为：枚举 $k$，作为维护第 $i$ 段区域时 1 号传感器使用的个数，然后从已维护好的 $dp[i-1]$ 转移过来。

用 $dp[n]$ 来计算最小花费即可。注意要满足个数的限制，无法满足的话输出 `-1` 即可。

这种做法需进行 $O(nk)$ 次转移，每次转移为 $O(k)$，总复杂度 $O(nk^2)$，足以通过本题。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define maxn 150
#define maxm 500050 
#define endl '\n'
#define ll long long
using namespace std; 

const ll llinf = 1e18 + 9;
const int inf = 0x3f3f3f3f;

int n;
int la, ka, lb, kb;
int d[105];
int dp[105][1005];
ll ans = llinf, ca, cb;

void run()
{
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> d[i];
	cin >> la >> ca >> ka; cin >> lb >> cb >> kb;
	memset(dp, inf, sizeof(dp));
	
	for(int i = 0; i <= ka; i ++)
		dp[1][i] = (max(d[1] - i * la, 0) + (lb - 1)) / lb;
	
	for(int i = 2; i <= n; i ++)
		for(int j = 0; j <= ka; j ++)
			for(int k = 0; k <= j; k ++)
				dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + (max(d[i] - k * la, 0) + (lb - 1)) / lb);
	
	for(int i = 0; i <= ka; i ++)
		if(dp[n][i] <= kb) ans = min(cb * dp[n][i] + ca * i, ans);
//	for(int i = 0; i <= ka; i ++) cout << i << ' ' << dp[n][i] << endl;
	if(ans >= llinf) ans = -1;
	cout << ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int t = 1;
//	cin >> t; 
	while(t --) run();
	
	return 0;
}
/*
dp[i][j]：代表处理前 i 个区域时，用了 j 个 1 号传感器时使用 2 号传感器的最小值。 
dp[i][j] = min(dp[i-1][j-k] + (di-k*l1+(l2-1))/l2, dp[i][j])
*/
```

Extra：这题还可以把 dp 数组的第一维滚掉，用类似背包的方法反向枚举 $j$ 即可。但这样做的优化没有什么实质性，就不再贴代码了。

---

## 作者：forever_nope (赞：2)

Date 20231025：修复手滑公式 $\min$、$\max$ 写反了。

动态规划。类似背包问题。

### 朴素算法

记 $(x,y)$ 表示使用 $x$ 个 (1) 传感器、$y$ 个 (2) 号传感器。

设 $f(t,i,j)$ 表示覆盖前 $t$ 个区间，使用 $(i,j)$ 传感器，是否可行。

枚举第 $t$ 个区间使用 $(p,q)$ 传感器：

$$\boxed{f(t,i,j)=\max\{f(t-1,i-p,j-q)\times[pL_1+qL_2\ge D_i]\}}$$

状态数 $NK_1K_2$，转移量 $K_1K_2$，因此，总时间复杂度为 $\mathcal{O}(N{K_1}^2{K_2}^2)$，大约为 $10^{14}$，不可过。

### 考虑优化

每个状态只记录 $0/1$ 是不是有点浪费呢？

于是就可以考虑一个经典的状态设计优化，将一个状态放在结果里。

我们可以将 $f(t,i,j)$ 的 $j$ 放在结果里。

具体的，设 $f(t,i)$ 表示考虑前 $t$ 个区间，使用 $i$ 个 (1) 传感器，最少要使用的 (2) 传感器数量。

明显的，结果为 $\min\limits_{i=1}^{K_1}\{f(n,i)\}\space(f(n,i)\le K_2)$.

其实这个式子也是有单调性的，但是由于 $K\le10^3$，我们可以不用考虑。

考虑转移，也不复杂，与朴素算法类似，我们枚举第 $t$ 个区间使用 $k$ 个 $(1)$ 传感器，那么给 $(2)$ 号传感器留了 $\max(D_i-kL_1,0)$ 的空间：

$$\boxed{f(i,j)=\min\limits_{k=0}^j\Big\{f(i-1,j-k)+\Big\lceil\dfrac{\max(D_i-kL_1,0)}{L_2}\Big\rceil\Big\}}$$

状态数 $NK_1$，转移量 $K_1$，因此，总时间复杂度为 $\mathcal{O}(N{K_1}^2)$，大约为 $10^8$，可过。

代码：<https://atcoder.jp/contests/abc325/submissions/46898766>


---

## 作者：littlebug (赞：1)

## Solution

注意到 $c_1,c_2$ 是固定的，于是可以先求出来两种传感器的个数，又发现 $k$ 很小，所以考虑如何求出在传感器一个数固定的情况下，传感器二的最小个数。

很自然地想到 dp。

发现每个区段之间是没有影响的，于是可以设 $f_{i,j}$ 为只考虑前 $i$ 个区段，用了 $j$ 个传感器一时，使用传感器二的最小个数。那么转移是容易的，考虑第 $i$ 个区段用了几个传感器一即可，有式子：

$$
f_{i,j} = \min _{0 \le x \le j} \left( f_{i-1,j-x} + \left \lceil \frac {a_i - l_1 \times j} {l_2} \right \rceil \right)
$$

后面那一块是用来计算区段 $i$ 需要用几个传感器二的。

答案即为 $\min \limits _{0 \le i \le k_1} ( i \times c_1 + f_{n,i} \times c_2 )$。

复杂度 $O(nk^2)$，顶多 1e8 完全可过。

## Code

```cpp
int n,a[MAXN],l1,c1,k1,l2,c2,k2,f[MAXN][MAXN];

signed main()
{
    read(n),_::r(a,n),read(l1,c1,k1,l2,c2,k2);
    
    auto calc=[](int i,int j){return max((a[i]-l1*j+l2-1)/l2,0ll);};
    
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    rep(i,1,n) rep(j,0,k1) rep(x,0,j) f[i][j]=min(f[i][j],f[i-1][j-x]+calc(i,x));
    
    int ans=inf; rep(i,0,k1) f[n][i]<=k2 && (ans=min(ans,i*c1+f[n][i]*c2));
    write(ans==inf ? -1ll : ans);

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：xpz0525 (赞：1)

### [ABC325F] Sensor Optimization Dilemma题解
首先容易想到一个直接的 DP ， $dp_{i,j,k}$ 代表监视了前 $i$ 段，用了 $j$ 个 Type-1 传感器，$k$ 个 Type-2 传感器。转移时只要枚举如何使用 1 , 2 类传感器覆盖当前段即可。但这样复杂度很高，无法承受。 

考虑我们是如何判断覆盖当前段的，容易发现其实我们只需要记录用了多少个 Type-1 传感器即可，因为 $i,j$ 确定后，$k$ 也随之确定。 那么就可以得到以下转移式：

$$
dp_{i,j}+m \cdot C_1 + \lceil \frac{D_{i+1}-m \cdot L_1}{C_2} \rceil \rightarrow dp_{i+1,j+m},while(m-1) \cdot L_1 \lt D_{i+1}
$$

AC代码：
```
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll n,d[1005],l[115],c[115],K[5],dp[1005][1005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	for(int i=1;i<=2;i++){
		cin>>l[i]>>c[i]>>K[i];
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<=n;i++) for(int j=0;j<=K[1];j++) for(int m=0;j+m<=K[1]&&(m-1)*l[1]<d[i+1];m++) dp[i+1][j+m]=min(dp[i+1][j+m],dp[i][j]+c[1]*m+(d[i+1]-m*l[1]+l[2]-1)/l[2]*c[2]);
	ll ans=LONG_LONG_MAX;
	for(int i=0;i<=K[1];i++){
		if((dp[n][i]-i*c[1])/c[2]>K[2]){
			continue;
		}
		ans=min(ans,dp[n][i]);
	}
	if(ans==LONG_LONG_MAX){
		puts("-1");
	}else{
		cout<<ans<<endl;
	}
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：AT_abc325_f [ABC325F] Sensor Optimization Dilemma
[传送门](https://www.luogu.com.cn/problem/AT_abc325_f)
## 题意
有 $N$ 段区间，第 $i$ 段长度为 $D_i$。还有 $2$ 种区间覆盖方法，第 $i$ 种可覆盖长度为 $L_i$ 的区间，有 $C_i$ 的成本，最多用 $K_i$ 个。

求覆盖所有 $N$ 段区间最小成本，或报告无解。
## 思路 1
大大的暴力。

使用搜索，记录当前到覆盖了哪一段、当前区间拼了多长、用了几个一型传感器、用了几个二型传感器。

得分：$10$ 分。
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e2 + 12;
const ll INF = 1e18 + 19;

int n;
ll ans = INF;
int d[MAXN], l[3], c[3], k[3];

void dfs(int i/*当前覆盖到了哪一段*/, int s/*当前区间覆盖了多长*/, int c1, int c2/*使用了多少个1,2型传感器*/) {
	if(c1 > k[1] || c2 > k[2])return; //当前选择非法
	if(i == n + 1) { //全部覆盖完毕
		ans = min(ans, 1LL * c1 * c[1] + 1LL * c2 * c[2]);
		return;
	}
	if(s >= d[i]){ //这一段覆盖完毕
		dfs(i + 1, 0, c1, c2);
		return;
	}
	dfs(i, s + l[1], c1 + 1, c2); //使用传感器1
	dfs(i, s + l[2], c1, c2 + 1); //使用传感器2
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	for(int i = 1; i <= 2; i++) {
		cin >> l[i] >> c[i] >> k[i];
	}
	dfs(1, 0, 0, 0);
	cout << (ans == INF ? -1 : ans);
	return 0;
}
```
## 思路 2
上一个思路，我们每次只使用了一个传感器，导致效率低下。

我们可以以区间为对象，枚举使用多少个一型传感器，就可以直接算出还需要多少个二型传感器，这样子就可以提高效率。

假设当前区间长度为 $D$，那么如果我们使用 $c1$ 个一型传感器，那么就还需要 $\lceil\frac{D - L_1 \times c1}{L_2}\rceil$ 个二型传感器。

得分：$12$ 分。
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e2 + 12, INF = 1e9 + 19;

int n, ans = INF;
int d[MAXN], l[3], c[3], k[3];

void dfs(int i/*当前覆盖到了哪一段*/, int c1, int c2/*使用了多少个1,2型传感器*/) {
	if(i == n + 1) { //全部覆盖完毕
		ans = min(ans, 1LL * c1 * c[1] + 1LL * c2 * c[2]);
		return;
	}
	for(int n1 = 0; n1 + c1 <= k[1]; n1++) { //枚举使用多少个一型传感器
		int n2 = (d[i] - n1 * l[1] + l[2] - 1) / l[2];
		if(n2 < 0)break;
		if(n2 + c2 > k[2])continue;
		dfs(i + 1, n1 + c1, n2 + c2);
	}
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	for(int i = 1; i <= 2; i++) {
		cin >> l[i] >> c[i] >> k[i];
	}
	dfs(1, 0, 0);
	cout << (ans == INF ? -1 : ans);
	return 0;
}
```
## 思路 3
上一思路中，搜索进行了很多重复计算。于是我们可以将其转变为 dp 减少重复计算次数。

而此时，我们发现，对于覆盖了相同个区间，且使用一型传感器个数相同的情况下，二型传感器使用个数越小越便宜。

所以，我们可以将二型传感器使用个数作为最优化属性。

最终成功 AC ！！！
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1e2 + 12, MAXK = 1e3 + 13; 
const ll INF = 1e18 + 19;

int n;
int D[MAXN], L[2], C[2], K[2];
ll dp[MAXN][MAXK];

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> D[i];
	}
	for(int i = 1; i <= 2; i++) {
		cin >> L[i] >> C[i] >> K[i];
	}
	for(int i = 1; i <= n; i++) { //当前覆盖到了哪一段
		for(int j = 0; j <= K[1]; j++) { //使用了多少个1型传感器
			dp[i][j] = INF;
			for(int k = 0; k <= j; k++) { //枚举使用多少个一型传感器
				if((D[i] - L[1] * k + L[2] - 1) / L[2] < 0)break; //如果非法则跳出循环
				dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + (D[i] - L[1] * k + L[2] - 1) / L[2]); //二型传感器使用个数越小越便宜
			}
		}
	}
	ll ans = INF;
	for(int i = 0; i <= K[1]; i++) {
		if(dp[n][i] <= K[2])ans = min(ans, 1LL * C[2] * dp[n][i] + 1LL * C[1] * i);
	}
	cout << (ans == INF ? -1 : ans);
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

# [[ABC325F] Sensor Optimization Dilemma](https://www.luogu.com.cn/problem/AT_abc325_f)

很小清新的 dp 题。

设 $dp_{i,j}$ 表示前 $i$ 个数中选出 $j$ 个一号检测器所需的最少的二号检测器的数量。转移为：
$$
dp_{i,j}=\min\limits_{k=0}^{j}\{dp_{i-1,j-k}+\left \lceil \dfrac{\max(0,d_i-kL_1)}{L_2} \right \rceil \}
$$
答案即为 $\min\{i\times c_1 + dp_{n,i}\times c_2\}$，记得判断 $dp_{n,i}\le k_2$。时间复杂度为 $O(nk^2)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e18

using namespace std;

const int N = 1e3 + 10;

int n, d[N], l[2], c[2], K[2], dp[N][N], ans = inf;

int Ceil(int x, int y) {
  return (x - 1 + y) / y;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  For(i,1,n) cin >> d[i];
  For(i,0,1) cin >> l[i] >> c[i] >> K[i];
  memset(dp, 0x3f, sizeof dp);
  dp[0][0] = 0;
  For(i,1,n) {
    For(j,0,K[0]) {
      For(k,0,j) {
        dp[i][j] = min(dp[i][j], dp[i-1][j-k] + Ceil(max(0ll, d[i] - k * l[0]), l[1]));
      }
    }
  }
  For(i,0,K[0]) {
    if(dp[n][i] <= K[1])
    ans = min(ans, i * c[0] + dp[n][i] * c[1]);
  }
  cout << (ans == inf ? -1 : ans) << '\n';
  return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# AT_abc325_f 解题报告

## 前言

感觉是经典的 DP 状态设计优化题，写篇题解强化一下记忆。

## 思路分析

首先肯定是 DP。

类似背包问题，我们可以得到一个朴素 DP。设 $f_{i,j,k}$ 表示前 $i$ 段，用了 $j$ 个 $1$ 监控，$k$ 个监控的最小代价。

转移是自然的：

$$f_{i,j,k}=\min_{a,b}^{l_1\cdot a+l_2\cdot b\ge d_i} f_{i-1,j-a,k-b}+c_1\cdot a+c_2\cdot b$$

因为枚举 $a$，最优的 $b$ 是确定的，所以是 $O(nk^3)$ 的。

考虑优化。

注意到上面的 DP 设计很多余，因为确定 $j,k$ 的值，$f_{i,j,k}$ 的值就是确定的。

考虑将一维状态放到 DP 值里。

具体地，设 $f_{i,j}$ 表示前 $i$ 段，用了 $j$ 个 $1$ 监控，全部覆盖需要的最少的 $2$ 监控的个数。

转移类似：

$$f_{i,j}=\min_{a,b}^{l_1\cdot a+l_2\cdot b\ge d_i} f_{i-1,j-a}+b$$

这样就是 $O(nk^2)$ 的了。

然后统计答案时，需要注意 $i$ 和 $f_{n,i}$ 都不能超出限制。

其实上面的柿子还可以用单调队列优化到 $O(nk)$。但是题目没有要求就不往下推了。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
int n,d[105],l1,c1,k1,l2,c2,k2,ans;
int f[105][1005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	cin>>l1>>c1>>k1>>l2>>c2>>k2;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k1;j++){
			for(int a=0;a<=j;a++){
				f[i][j]=min(f[i][j],f[i-1][j-a]+(d[i]>a*l1?((d[i]-a*l1)/l2+(bool)((d[i]-a*l1)%l2)):0));
			}
		}
	}
	ans=inf;
	for(int i=0;i<=k1;i++){
		if(f[n][i]<=k2){
			ans=min(ans,i*c1+f[n][i]*c2);
		}
	}
	if(ans>=inf) cout<<-1;
	else cout<<ans;
	return 0;
}

```

---

## 作者：XYQ_102 (赞：0)

## 题目大意
给定 $n$ 个区间长度，有两种操作：
- 区间长度减 $a_1$，成本 $c_1$，最多用 $k_1$ 次。
- 区间长度减 $a_2$，成本 $c_2$，最多用 $k_2$ 次。

问将每个区间长度减成非正的最小成本。

## 思路
考虑搜索的状态，就是 **当前的区间**，**操作一的使用次数**，**操作二的使用次数**，然后枚举当前区间使用的操作一的次数，复杂度 $\Theta(n\times k^3)$。

上述搜索转换成 dp 的形式就是 $dp_{i,j,k}$ 表示前 $i$ 个区间，操作一用了 $j$ 次，操作二用了 $k$ 次，这一状态是否合法（即布尔型，成本从两个操作次数就能算出来），这难免过于浪费，我们可以把一个状态放到 dp 的值里。

即设 $dp_{i,j}$ 表示前 $i$ 个区间，操作一用了 $j$ 次时，操作二使用的最小次数（换句话说就是最小成本），转移同样是枚举当前区间的操作一的次数，时间复杂度是 $\Theta(n\times k^2)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
const int inf = 1e9 + 7;
 
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> d(n);
    for (auto& i : d)
        cin >> i;
    array<int, 2> l{}, c{}, k{};
    for (int i = 0; i < 2; ++i)
        cin >> l[i] >> c[i] >> k[i];
    vector<LL> dp(k[0] + 1, inf);
    dp[0] = 0;
    for (auto& i : d) {
        vector<LL> dp2(k[0] + 1, inf);
        for (int j = 0; j <= k[0]; ++j) {
            for (int u = 0; u <= j; ++u) {
                int v = max(0, (i - u * l[0] + l[1] - 1) / l[1]);
                dp2[j] = min(dp2[j], dp[j - u] + v);
            }
        }
        dp.swap(dp2);
    }
    LL ans = numeric_limits<LL>::max();
    for (int i = 0; i <= k[0]; ++i) {
        if (dp[i] <= k[1])
            ans = min(ans, 1ll * i * c[0] + dp[i] * c[1]);
    }
    if (ans == numeric_limits<LL>::max())
        ans = -1;
    cout << ans << '\n';
 
    return 0;
}
```

---

## 作者：遥遥领先 (赞：0)

# [ABC325F] Sensor Optimization Dilemma 题解

这个题用动态规划来做。

设 $dp[i][j]$ 表示覆盖了前 $i$ 个线段，用了 $j$ 个传感器 1，需要最少多少传感器 2。

第一层循环枚举已经覆盖前 $i$ 个线段，第二层循环枚举传感器 1 已经用了 $j$ 个，第三层循环枚举用 $p$ 个传感器 1 去覆盖线段，然后定义一个 `x` ，表示现在都使用传感器 1 覆盖剩余多少，接下来，若 `x>0`，那么还需要传感器 2 来覆盖，用 `need` 来存储这个数量。

代码：
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

inline int read()
{
	int ww = 0,ee = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
		{
			ee = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		ww = ww * 10 + ch - '0';
		ch = getchar();
	}
	return ww * ee;
}


void file()
{
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}

int n;

const int N = 110;
int a[N];

const int M = 3;
int l[M],c[M],k[M];

int ret;


const int K = 1010;
int dp[K][K];


signed main()
{
	n = read();
	memset(dp,0x3f,sizeof(dp));
	for (int i = 1;i <= n;i++)
	{
		a[i] = read();
	}
	for (int i = 1;i <= 2;i++)
	{
		l[i] = read();
		c[i] = read();
		k[i] = read();
	}
	dp[0][0] = 0;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= k[1];j++)
		{
			for (int p = 0;p+j <= k[1];p++)
			{
				int need = 0;
				int x = a[i+1] - l[1]*p;
				if (x > 0)
				{
					need = (x-1)/l[2]+1;
				}
				dp[i+1][j+p] = min(dp[i+1][j+p],dp[i][j]+need);
			}
		}
	}
	ret = 1e18;
	for (int i = 0;i <= k[1];i++)
	{
		if (dp[n][i] <= k[2])
		{
			ret = min(ret,c[1]*i+dp[n][i]*c[2]);
		}
	}
	cout << (ret == 1e18 ? -1 : ret);
	return 0;
}
```

码风原因，看起来比较长。

---

## 作者：WaterSun (赞：0)

# 思路

定义 $dp_{i,j,k} = 0/1$ 表示用 $i$ 个 1 号传感器，$j$ 个 2 号传感器 不能/能 监控到前 $i$ 段。

显然有：

$$
dp_{i,j,k} = \max_{0 \leq p \leq j \wedge 0 \leq q \leq k \wedge p \times l_1 + q \times l_2 \geq d_i}\{dp_{i - 1,j - p,k - q}\}
$$

但是这样 $\Theta(nk^4)$ 的复杂度是不优秀的，所以考虑优化。

发现这个状态只能表示一个状态是否可行，太浪费了，于是考虑将 $dp_{i,j,k}$ 的 $k$ 降到结果上。

即定义 $dp_{i,j} = k$ 表示用 $j$ 个 1 号传感器，最少使用 $k$ 个 2 号传感器就可监控到前 $i$ 段。

显然有：

$$
dp_{i,j} = \min_{1 \leq k \leq j}\{dp_{i - 1,j - k} + \lceil \frac{\max(d_i - l_1 \times k,0)}{l_2} \rceil\}
$$

答案显然是：

$$
\min_{dp_{n,i} \leq k_2}\{i \times c_1 + dp_{n,i} \times c_2\}
$$

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 110,M = 1010,inf = 1e18 + 10;
int n,ans = inf;
int arr[N];
int w[2],v[2],l[2];
int dp[N][M];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int up(int a,int b){
	if (a % b == 0) return a / b;
	return a / b + 1;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 0;i <= 1;i++){
		w[i] = read();
		v[i] = read();
		l[i] = read();
	}
	for (re int i = 1;i <= n;i++){
		for (re int j = 0;j <= l[0];j++){
			dp[i][j] = inf;
			for (re int k = 0;k <= j;k++) dp[i][j] = min(dp[i][j],dp[i - 1][j - k] + up(max(arr[i] - k * w[0],0ll),w[1]));
		}
	}
	for (re int i = 0;i <= l[0];i++){
		if (dp[n][i] <= l[1]) ans = min(ans,i * v[0] + dp[n][i] * v[1]);
	}
	if (ans == inf) puts("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

