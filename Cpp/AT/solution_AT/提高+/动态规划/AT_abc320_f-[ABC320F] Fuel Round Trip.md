# [ABC320F] Fuel Round Trip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc320/tasks/abc320_f

数直線上の座標 $ 0 $ から座標 $ X_N $ まで行き、折り返して座標 $ 0 $ まで帰ってくる計画を立てています。ただし、往路では正の方向、復路では負の方向にしか進めません。  
 移動は車で行います。車は距離 $ 1 $ 進むごとに $ 1 $ リットルの燃料を消費します。燃料は $ H $ リットルまで所持することができ、燃料を所持していない状態で進むことはできません。  
 各 $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、座標 $ X_i $ にはガソリンスタンドがあり、$ P_i $ 円払うと $ F_i $ リットルの燃料が得られます。ただし、$ H $ リットルを超えて燃料を所持することはできません。より厳密には、$ x $ リットルの燃料を持っているときに座標 $ X_i $ にあるガソリンスタンドを使うと $ P_i $ 円を払う必要があり、持っている燃料は $ \min(x\ +\ F_i,\ H) $ リットルとなります。 各ガソリンスタンドは、**往路と復路で合わせて** $ 1 $ 回までしか使うことができません。  
 はじめに燃料を $ H $ リットル所持しているとき、この計画を達成することができるか判定し、可能ならば必要な金額の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ H\ \leq\ 300 $
- $ 0\ <\ X_1\ <\ X_2\ <\ \ldots\ <\ X_N\ \leq\ 10^5 $
- $ 1\ \leq\ P_i\ \leq\ 10^5 $
- $ 1\ \leq\ F_i\ \leq\ H $
- 入力される数値はすべて整数
 
### Sample Explanation 1

往路で座標 $ 5 $ の、復路で座標 $ 9 $ のガソリンスタンドを用いることにより合計 $ 9 $ 円払うことで計画を達成することができます。 計画を達成するためにかかる金額を $ 8 $ 円以下にすることはできません。往路と復路で同じガソリンスタンドを使うことができないことに注意してください。

## 样例 #1

### 输入

```
4 10
2 5 9 11
8 10
5 8
4 9```

### 输出

```
9```

## 样例 #2

### 输入

```
1 1
100000```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 20
4 13 16 18 23
1 16
2 8
4 11
8 13```

### 输出

```
13```

# 题解

## 作者：Zi_Gao (赞：21)

## 前言

纪念一下第一次做出 AT 评分 2000 的题，还有名字水色。

## 正文

### 0x00 题目分析

题意很简单就是要在从 $0$ 位置走到 $X_N$ 位置，然后倒回来回到 $0$ 位置。并且每走一格需要 $1$ 的油，油箱最多携带 $H$ 的油，途中有一些**只能使用一次的**加油站，选择加油只能强制花费 $P_i$ 元加入 $F_i$ 的油，装不下只能抛弃。现在问你从 $0$ 开始有 $H$ 的油，走一个来回最小要多少钱。

可以发现这个题有两个难点：

1. 需要返回 $0$ 点，那么意味着来去选择的加油站会互相影响。

2. 由于第一点引出了第二点加油站只能使用一次，那么很难设计一个 DP 状态，第一反应只是状压。

但是同时可以发现 $H,N$ 都极小，默认为同阶，考虑近 $\mathcal{O}\left(N^3\right)$ 的算法。

对于这样的题可以先考虑去掉一些限制条件加上观察性质，找到一个大致的思路。

### 0x01 弱化版问题

假如不考虑需要返回 $0$ 这样的条件，只考虑走到 $X_N$，我们考虑设计 DP 状态，可以设计为 $dp_{i,j}$ 表示走到 $i$ 这个点，剩了 $j$ 的油需要的最小花费，这个 DP 设计显然是容易转移的，在每个加油站考虑加还是不加，这样一个状态只会转移到 $\mathcal{O}\left(1\right)$ 个状态，时间复杂度 $\mathcal{O}\left(n^2\right)$。观察时间复杂度都知道由于减少了限制条件，我们并没有发挥出这个算法的最大价值，而且考虑把这个算法修改为完全限制条件下的算法，可以利用的空间还有 $\mathcal{O}\left(n\right)$ 可以霍霍。

这里需要动一下脑筋，读者可以先想一下。

### 0x02 重新强化回去

观察到若只是需要走到 $X_N$ 那么状态就是从 $1$ 到 $i$ 的最小花费。那么这里有返回就不妨定义为从 $i$ 到 $N$ 然后返回 $i$ 的最小花费，这里发现状态定义不完全，无法确定返回 $i$ 时的油，直接大力升维即可。最终 DP 状态定义为 $dp_{i,j,k}$ 表示从 $i$ 到 $N$ 然后返回 $i$ 的最小花费，并且第一次来到 $i$ 的时候有 $j$ 的油，返回 $i$ 的时候有 $k$ 的油。考虑倒序转移，分 $3$ 个转移方式：

1. 第 $i$ 个加油站来时和返回时都不加油。

2. 第 $i$ 个加油站来时加油。

3. 第 $i$ 个加油站返回时加油。

转移方程显然。

### 0x03 代码实现

考虑刷表法，考虑 $dp_{i+1,j,k}$ 可以转移到那去，倒着 DP 即可。需要特别注意的是，可以选择性的抛弃一些油来达到更优的策略，那么做一个前缀 $\min$ 即可。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

long long p[310],f[310],x[310],dp[310][310][310];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,j,k;
    register long long dis,tmp;
    int n=read();
    long long h=read(),res=0x3f3f3f3f3f3f3f3fll;

    memset(dp,0x3f,sizeof(dp));
    for(i=1;i<=n;++i) x[i]=read();
    for(i=1;i<=n-1;++i) p[i]=read(),f[i]=read();
    for(i=0;i<=h;++i)
        dp[n][i][i]=0;

    for(i=n-1;~i;--i){
        for(j=0;j<=h;++j)
            for(k=0;k<=h;++k){
                dis=x[i+1]-x[i];
                if(j+dis>h) continue;
                if(k<dis) continue;
                tmp=dp[i+1][j][k];
                //case 0
                dp[i][j+dis][k-dis]=std::min(dp[i][j+dis][k-dis],tmp);
                //case 1
                dp[i][std::max(j+dis-f[i],0ll)][k-dis]=std::min(dp[i][j+dis-f[i]][k-dis],tmp+p[i]);
                //cass 2
                dp[i][j+dis][std::min(k-dis+f[i],h)]=std::min(dp[i][j+dis][std::min(k-dis+f[i],h)],tmp+p[i]);
            }
        for(j=1;j<=h;++j)
            for(k=h;k;--k)
                dp[i][j][k]=std::min({dp[i][j][k],dp[i][j-1][k+1],dp[i][j][k+1],dp[i][j-1][k]});
    }

    for(i=0;i<=h;++i)
        res=std::min(res,dp[0][h][i]);

    print(res==0x3f3f3f3f3f3f3f3fll?-1:res);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

这样的题需要加深对 DP 的理解，不能死板的套用常规 DP 的方式，而要根据题目要求具体分析设计状态。并且需要具备对问题的拆解、组合能力，把大问题简化，找到大问题和小问题之间的关联，往往能提供一个正确的大方向。

---

## 作者：LCat90 (赞：8)

注意到 $n$ 和 $h$ 同阶。

普通的 dp 会有很强的后效性导致不可做，于是状态的定义极为重要。

设 $dp_{i,j,k}$ 表示从 $1$ 到 $i$ 的时候还有 $j$ 点油，回来到 $i$ 还剩 $k$ 点油的最小花费。

这样我们只着眼于 $[1,i]$ 这个单独阶段，无影响。

具体地，讨论不加油/来时加油/去时加油三种情况转移。

初始值 $dp_{0,h,0}=0$，答案为 $\min _ {0\le j\le i\le h}dp_{n,i,j}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 305;
int n, h, dp[N][N][N]; // [1,i]
int a[N], p[N], f[N], ans = 1e18;
signed main() {
	cin >> n >> h;
	for(int i = 1;i <= n; ++i) scanf("%lld", &a[i]);
	for(int i = 1;i < n; ++i) scanf("%lld %lld", &p[i], &f[i]);
	memset(dp, 0x3f, sizeof dp);
	dp[0][h][0] = 0;
	for(int i = 1;i <= n; ++i) {
		int dis = a[i] - a[i - 1];
		for(int j = 0;j <= h; ++j)
	 		for(int k = 0;k <= h; ++k) {
	 			int nj = j - dis, nk = k + dis;
	 			if(nj < 0 or nk > h) continue ;
	 			
				dp[i][nj][nk] = min(dp[i - 1][j][k], dp[i][nj][nk]); // never here
                
				dp[i][min(h, nj + f[i])][nk] = min(dp[i][min(h, nj + f[i])][nk], dp[i - 1][j][k] + p[i]);
				// first 
                
				dp[i][nj][max(0ll, nk - f[i])] = min(dp[i][nj][max(0ll, nk - f[i])], dp[i - 1][j][k] + p[i]);
				// second here
			}
	}
	
	for(int i = 0;i <= h; ++i) 
		for(int j = 0;j <= h; ++j)
			if(j <= i) ans = min(ans, dp[n][i][j]); 

	if(ans == 1e18) puts("-1");
	else cout << ans; 
    return 0;
}
```

---

## 作者：SoyTony (赞：7)

过程一来一回，且要求每个位置来回只能加油一次，那么应当考虑一起 DP。

设 $f(i,j,k)$ 表示当前考虑了前 $i$ 个加油站，其中去程油箱油量 $j$，返程油箱油量 $k$ 的最小代价。这里转移比较奇怪，去程每次是移动消耗油，而返程是倒着做所以移动是增加油。

设 $d=x_{i+1}-x_i$，讨论 $i$ 位置是否加油。

如果不加油，转移有：

$$f(i+1,j-d,k+d)\leftarrow f(i,j,k)$$

如果去程加油，$i+1$ 处油量是 $\min(j+f_i,H)-d$，转移有：

$$f(i+1,\min(j+f_i,H)-d,k+d)\leftarrow f(i,j,k)+p_i$$

如果返程加油，设 $i+1$ 处油量为 $x$，那么有 $\min(x-d+f_i,H)=k$，如果 $k\neq H$，此时 $x=k-f_i+d$，是唯一的，转移有：

$$f(i+1,j-d,k-f_i+d)\leftarrow f(i,j,k)+p_i$$

反之则要求 $x-d+f_i\ge H$，那么 $x\ge H-f_i+d$，对这个范围内的所有 $x$，转移有：

$$f(i+1,j-d,x)\leftarrow f(i,j,k)+p_i$$

由于第四个转移不为 $O(1)$，但只有 $k=H$ 时出现，因此复杂度是 $O(nH^2)$。

初始认为 $f(0,H,k)=0$，而答案应为 $\min_{k=1}^H \{f(n,k,k)\}$。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/abc320/submissions/45655264)

---

## 作者：吴思诚 (赞：7)

# [[ABC320F] Fuel Round Trip](https://www.luogu.com.cn/problem/AT_abc320_f)

这道题我们首先观察数据范围，发现 $n,h\le 300$，于是就可以围绕它想一个三次方的复杂度。

这个数据范围，一般明摆着就是 `DP`，所以我先往 `DP` 方向思考。

首先思考如果只要一趟的情况，发现十分简单，令 $dp_{i,j}$ 表示到达第 $i$ 个油站，加完/不加后剩余的油量为 $j$ 的答案。这个很简单，是一个 $O(nh)$ 的 `DP`。

可是本题有一个往返的限制，但是我们假设回来的时候油站还可以做一次的话，也十分简单，我们只需要做一次简单的对称即可。

对于样例1，我们可以映射成这样：$[0,2,5,9,11,13,17,20,22]$。

其中 $11$ 是中心，然后可以发现往返的答案，就变成了去一次。

此时，若不考虑对称点只能取一对的情况，方法其实和上面完全一样。

于是我们想：是不是能通过增加一维状态就行了呢？

首先不可能状压，那还有什么方法呢？

经过苦思冥想，我们可以发现，我们可以围绕每一对对称点进行 `DP`。

我们初步的状态就有了 $dp_i$ 表示考虑过第 $i$ 对对称点之后的答案（答案就是 $dp_0$）。

显然，这是不够的，我们需要知道初始进去的油量（我定义**不包括**进去吃左侧的油），我们就加一维变成 $dp_{i,h}$。

其次，还是不够的，因为中间的操作会改变流量，我们的代价取决于最终我们希望的流量（我定义**包括**出去吃右侧的油），所以再加一维表示最终的油量，$dp_{i,h,h'}$。

到这里可能是够了的，但是我比较弱，觉得需要处理左右只选一种，于是再加一维 $k\in\{0,1,2\}$（$0$ 表示两边都不选，$1$ 表示选择左侧，$2$ 表示选择右侧）。

到目前为止，最终的状态 $dp_{i,h,h',k\in\{0,1,2\}}$ 似乎已经能够满足需求了。

转移也是麻烦的。

我们考虑枚举从 $i$ 进去时的油量 $w$，若选择了左侧的新油站，那么需要 $w\leftarrow \min(h,w+f_i)$，然后再判断这么多的油是否能到达 $i+1$（即里面的一层），这样我们就能求出里面这一层的到达左边时的油量了。再枚举从 $i+1$ 出去的油量 $v$，据此计算出到达右侧的点 $i$ 时剩余油量，方法与选择了左侧的新油站类似。

# [code](https://atcoder.jp/contests/abc320/submissions/45655600)


---

## 作者：blossom_j (赞：2)

### [ABC320F] Fuel Round Trip

若只考虑单程的，设一个 $dp_{i,j}$ 表示走到第 $i$ 个加油站剩下的油为 $j$ 的最小花费。

但是还需要考虑回来可能也要加油，所以综合考虑，设 $dp_{i,j,k}$ 表示到第 $i$ 个加油站去的途中有 $j$ 的油量，归途有 $k$ 的油量的最小花费。

考虑 $dp_{i,j,k}$ 的转移，设 $d=s_{i+1}-s_{i}$：

若来回都不加，则 $dp_{i+1,j-d,k+d}=\min(dp_{i,j,k})$；

如果去的时候加，则 $dp_{i+1,\min(j+f_i,H)-d,k+d}= \min(dp_{i,j,k}+p_i)$

如果回的时候加，设下一个加油站时回时油量为 $x$，则 $ \min(x-d+f_i,H)=k$ 若 $k<H$ 则 $x=k+len-f_i$，若 $k=H$ 则 $x \ge H+d-f_i$ 转移就是 $dp_{i+1,j-d,x}= \min(dp_{i,j,k}+p_i)$。

注意转移时第二维不要小于零，如果加油，转移的油量一定要大于加的油量。

复杂度 $O(n \times h^2)$。


```
#include<bits/stdc++.h>
using namespace std;
const int N=500;
int s[N];
int p[N],f[N];
int dp[N][N][N];
const int inf=2139062143;
signed main(){
	int n,h;
	scanf("%d%d",&n,&h);
	int ma=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
		ma=max(ma,s[i]-s[i-1]);
	}
	if(ma>h){
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<n;i++) scanf("%d%d",&p[i],&f[i]);
	memset(dp,0x7f,sizeof(dp));
	for(int i=0;i<=h;i++){
		dp[0][h][i]=0;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<=h;j++){
			for(int k=0;k<=h;k++){
				if(dp[i][j][k]==inf) continue;
				int len=s[i+1]-s[i];
				if(j-len>=0 && k+len<=h){
					dp[i+1][j-len][k+len]=min(dp[i+1][j-len][k+len],dp[i][j][k]);
				}
				if(min(j+f[i],h)-len>=0 && k+len<=h){
					dp[i+1][min(j+f[i],h)-len][k+len]=min(dp[i+1][min(j+f[i],h)-len][k+len],dp[i][j][k]+p[i]);
				}
				if(k<h){
					if(j-len>=0 && k-f[i]+len<=h && k>=f[i]){
						dp[i+1][j-len][k-f[i]+len]=min(dp[i+1][j-len][k-f[i]+len],dp[i][j][k]+p[i]);
					}
				}
				else{
					if(j-len>=0 && k>=f[i]){
						for(int e=h+len-f[i];e<=h;e++){
							dp[i+1][j-len][e]=min(dp[i+1][j-len][e],dp[i][j][k]+p[i]);
						}
					}
				}
			}
		}
	}
	int ans=inf;
	for(int i=0;i<=h;i++){
		ans=min(ans,dp[n][i][i]);
	}
	if(ans==inf) cout<<"-1";
	else cout<<ans<<endl;
}
```


---

## 作者：User_Authorized (赞：0)

## 题意

在坐标轴上给定 $N$ 个点，坐标依次为 $X_1, X_2, \cdots, X_N$，你需要从原点前往 $X_N$ 并折返，其中在第 $1$ 个到第 $N - 1$ 个点上有加油站，其中第 $i$ 个加油站可以花费 $P_i$ 购买 $F_i$ 升汽油，汽油持有上限为 $H$ 升，每行驶一单位距离需要花费一升汽油。在全部过程中每个加油站至多使用一次，判断是否可以完成行程并输出最小花费。

（$1 \le N, H \le 300$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ABC320F.html)

考虑 $\tt{DP}$，考虑将反向行驶（$0 \leftarrow X_N$）的过程视为正向行驶（$0 \rightarrow X_N$），那么问题转化为了进行两次正向行驶（$0 \rightarrow X_N$）的行程且不能使用同一个加油站的最小花费，设 $f_{i, j, k}$ 代表行驶到第 $i$ 个加油站，两次行程分别还持有 $j$ 升油和 $k$ 升油的最小花费。

转移是显然的，考虑是否加油，为哪次行程加油即可，有转移

$$\begin{aligned}
f_{i + 1, j, k} &\leftarrow f_{i, j, k} \\
f_{i + 1, \min\left\{j + F_i, H\right\}, k} &\leftarrow f_{i, j, k} + P_i \\
f_{i + 1, j, \min\left\{k + F_i, H\right\}} &\leftarrow f_{i, j, k} + P_i \\
\end{aligned}$$

转移是 $\mathcal{O}(NH^2)$ 的，下面我们考虑合并答案。

我们设在第一次行程到达 $X_N$ 后油箱的剩余油量为 $x$，那么这也就意味着我们的第二次行程开始的起始油量只有 $x$，但是由于在转移中我们是正向考虑的，即从 $0$ 以满邮箱开始转移，那么我们考虑转化起始油量的限制。我们发现，若没有第一次行程的干扰，第二次行程可以视为从满油开始，若第一次行程后邮箱剩余油量为 $x$，这也就意味着在第二次行程开始时有 $H - x$ 升油被扣除无法使用，从正向来说就是从 $0$ 以满油开始，到达后需剩余 $H - x$ 升油以备扣除。那么我们有答案的表达式

$$Ans = \max\limits_{0 \le i \le H, H - i \le j \le H} f_{N, i, j}$$

合并答案的复杂度是 $\mathcal{O}(H^2)$ 的，总复杂度 $\mathcal{O}(NH^2)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<ValueMatrix> ValueCube;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, H;

    std::cin >> N >> H;

    ValueVector X(N + 1, 0), F(N + 1, 0), P(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> X[i];

    for (valueType i = 1; i < N; ++i)
        std::cin >> P[i] >> F[i];

    constexpr valueType MAX = std::numeric_limits<valueType>::max() >> 2;

    ValueCube DP(N + 1, ValueMatrix(H + 1, ValueVector(H + 1, MAX)));

    DP[0][H][H] = 0;

    for (valueType i = 0; i < N; ++i) {
        for (valueType a = 0; a <= H; ++a) {
            for (valueType b = 0; b <= H; ++b) {
                valueType const dist = X[i + 1] - X[i];

                if (a >= dist && b >= dist)
                    DP[i + 1][a - dist][b - dist] = std::min(DP[i + 1][a - dist][b - dist], DP[i][a][b]);

                if (std::min(a + F[i], H) >= dist && b >= dist)
                    DP[i + 1][std::min(a + F[i], H) - dist][b - dist] = std::min(DP[i + 1][std::min(a + F[i], H) - dist][b - dist], DP[i][a][b] + P[i]);

                if (a >= dist && std::min(b + F[i], H) >= dist)
                    DP[i + 1][a - dist][std::min(b + F[i], H) - dist] = std::min(DP[i + 1][a - dist][std::min(b + F[i], H) - dist], DP[i][a][b] + P[i]);
            }
        }
    }

    valueType ans = MAX;

    for (valueType i = 0; i <= H; ++i)
        for (valueType j = 0; j <= H; ++j)
            if (j >= H - i)
                ans = std::min(ans, DP[N][i][j]);

    if (ans == MAX)
        ans = -1;

    std::cout << ans << std::endl;

    return 0;
}
```

---

