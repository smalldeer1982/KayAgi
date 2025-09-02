# Color Rows and Columns

## 题目描述

你有 $n$ 个矩形，第 $i$ 个矩形的宽度为 $a_i$，高度为 $b_i$。

你可以无限次地执行这个操作：

选择其中的一个矩形并为其矩形内的一个单元格着色。

当每次有任意一个矩形内的一行或一列被完全着色，你都可以获得 $1$ 分。你的任务是去用尽量少的操作次数来获得至少 $k$ 的得分

假设有一个宽度为 $6$，高度为 $3$ 的矩形，你可以对矩形中的任意四列着色，从而使用 $12$ 次操作，获得 $4$ 分

## 样例 #1

### 输入

```
7
1 4
6 3
1 5
4 4
5 10
1 1
1 1
1 1
1 1
1 1
2 100
1 2
5 6
3 11
2 2
3 3
4 4
3 25
9 2
4 3
8 10
4 18
5 4
8 5
8 3
6 2```

### 输出

```
12
14
5
-1
17
80
35```

# 题解

## 作者：doumingze (赞：4)

你说的对，但是 $n$ 有 $1000$，不会写，那就先考虑一下 $n = 1$ 的情况（也就是只有一个矩形的情况）。

就拿 $a = 6, b = 3, k = 2$ 举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/vumu888l.png)

当 $k = 2$ 时，可以看到红线的染色方案是优于绿线的染色方案（红线共占 $6$ 格，绿线共占 $8$ 格）。

为什么绿线就比红线格子多呢？~~（有点废话）~~

当我们去掉图中第 $1$ 竖列之后，剩下的矩形是一个 $3 \times 5$ 的矩形。显然一列的长度是小于一行的长度的。红线占领了长度更小的一整列，所以显然是更优的。

是不是有点贪心的感觉？那就设计一个贪心策略：每次选择一列/一行中长度最小的，将行/列染色后删除，对剩余矩形再次做如上操作，直到上述操作执行次数达到 $k$ 次。

证明：假设染色若干次之后剩余矩形大小为 $n \times m$ 并不妨令 $n \ge m$（相等可以看做任选长短边），第一种方案是长边先染色一次，代价为 $n$，第二种方案是短边先染色一次，代价为 $m$。而染色长边则短边的宽度会减少 $1$，所以之后再染 $t$ 次色（保证每次染色之后仍然满足 $n \ge m$），第一种方案花费 $n + t \times (m - 1)$，第二种方案花费 $t \times m$。显然易证 $n + t \times (m - 1) \ge t \times m$（展开并移项一下）。那么，我们在每次染色时尽量都选染色短边，一定是不会更劣的。证毕。

---

上面是 $n = 1$ 的情况，但是 $n > 1$（物品有多个）怎么办？肯定是要从每个矩形中选出一部分进行染色。换言之就是把 $k$ 分配到每一个矩形中，若给每个矩形分配不同的 $k$，每个矩形的染色格子数量也会不同。

就是说，每个矩形里面，有几种不同的收益，每种收益有相应的代价。

那么根据上面那句话稍加联想一下，就可以想到这是一个分组背包的模型。把 $k$ 看做一个物品的价值，那么每一个矩形内，不同的价值对应的代价可以按照 $n = 1$ 的方法计算。但是在每一个矩形内，只能选一个物品（一个矩形只确定一个 $k$，组内互相冲突）。

那么解法就显然了：第 $i$ 个矩形内，把获得 $1 \dots \min(k, a_i + b_i)$ 的得分一共需要的染色格数先处理出来，然后就做一遍分组背包就行。注意到答案是获得某个价值需要的最小代价，那么 dp 的时候就把价值设计为状态，把代价设计为目标函数且属性为最小值即可。

注意，有一些细节部分需要考虑，具体可以看代码的注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 1010, M = 210;
int v[N][M], w[N][M], f[110], s[N];
 
int main()
{
	int t, n, k, x, y;
	cin >> t;
	while(t --)
	{
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i ++)
		{
			scanf("%d%d", &x, &y);
			 //计算该矩形内所有的不同价值所需的代价
			 //s: 组内物品数，v: 代价，w: 价值
			v[i][0] = w[i][0] = 0;
			while(x != 1 || y != 1)
			{
				s[i] ++;
				v[i][s[i]] = min(x, y) + v[i][s[i] - 1];
				w[i][s[i]] = w[i][s[i] - 1] + 1;
				if(x < y) y --; //染色短边，长边宽度 -1。
				else x --;
			}
			s[i] ++;
			v[i][s[i]] = 1 + v[i][s[i] - 1];
			w[i][s[i]] = w[i][s[i] - 1] + 2; // +2 是因为 1 * 1 的矩形，染色一次就可以将其一行与一列填满，共得两分。
		}
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = k + 1; j >= 1; j --)
				for(int l = 1; l <= s[i]; l ++)
					if(j >= w[i][l])
						f[j] = min(f[j], f[j - w[i][l]] + v[i][l]);
		int ans = min(f[k], f[k + 1]);
		//上面代码处理 f[k + 1] 是考虑到 1 * 1 的矩形价值为 2 而非为 1，且题目中大于 k 的价值也符合题意
		if(ans != 0x3f3f3f3f) printf("%d\n", ans);
		else puts("-1");
		for(int i = 1; i <= n; i ++) s[i] = 0;
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

设 $dp_{i,j}$ 表示前 $i$ 个矩形得到 $j$ 分的最小代价，转移为 $dp_{i,j}=\displaystyle\min_{k=0}^{\min(a_i,b_i)}dp_{i-1,j-k}+f(i,k)$，其中 $f(i,k)$ 表示在 $i$ 处获得 $k$ 分的最小代价。

$f(i,j)$ 可预处理，考虑 $f(i,j-1)$ 时矩阵 $i$ 剩下的有效双边长，然后取短的那一边来得分，另外一边的有效长度减一。

# Code
```cpp
#include<bits/stdc++.h>
int dp[1005][105];
int a[1005],b[1005];
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%d%d",&a[i],&b[i]);
		memset(dp,63,sizeof(dp));
		dp[0][0]=0;
		for(int i=1;i<=n;++i)
			for(int k=0,res=0,x=a[i],y=b[i];k<=a[i]+b[i];++k){
				for(int j=k;j<=m;++j)
					dp[i][j]=std::min(dp[i][j],dp[i-1][j-k]+res);
				if(x>=y)res+=y,--x;
				else res+=x,--y;
			}
		printf("%d\n",dp[n][m]==0x3f3f3f3f?-1:dp[n][m]);
	}
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：2)

首先我们发现，可以很快计算出每一个长方形达到某一分数需要的最少操作次数（具体实现看代码）。

于是，我们枚举每一个矩形，处理出此矩形达到 $i$ 分，需要的最少操作次数 $sc_i$。

考虑进行动态规划。定义 $f_i$ 表示枚举到当前矩形，达到 $i$ 分需要的最少次数（这里其实使用了滚动数组）。

容易写出状态转移方程（顺推）：$f_i+sc_j\xrightarrow{\min}f_{i+j}$。

至此，这题已经完成。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,f[1001],sc[200001],su;
struct A{int a,b;}a[200001];
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		memset(f,0x3f,sizeof f);
		f[0]=0,su=0;
		for(int i=1;i<=n;i++)
			cin>>a[i].a>>a[i].b;
		for(int i=1;i<=n;i++){
			int no=0,ta=a[i].a,tb=a[i].b,nsc=0;
			while(no<k&&(ta>0||tb>0)){//求出sc数组
				if(ta>tb)swap(ta,tb);
				no++,nsc+=ta,tb--;
				sc[no]=nsc;
			}
			su+=no;
			for(int q=k-1;q>=0;q--){//dp
				for(int j=0;j<=no;j++){
					f[q+j]=min(f[q+j],f[q]+sc[j]);
				}
			}
		}
		if(su<k)cout<<"-1\n";
		else cout<<f[k]<<'\n';
	}
	return 0;
}
```

---

## 作者：conti123 (赞：1)

vp 时一眼贪心，好在最后写出了 dp。

如果直接贪心的话，样例过不了，所以考虑 dp。

设 $f[i][I]$ 表示前 $i$ 个矩形贡献为 $I$ 的最小操作次数，则很明显有暴力转移方程：

```cpp
for(int i=1;i<=n;i++)//枚举第i个数
  for(int j=0;j<=min(k,c[i]+d[i]);j++)//枚举第i个数贡献多少
    for(int I=k;I>=j;I--)//枚举背包容量
      f[i][I]=min(f[i][I],f[i-1][I-j]+g[i][j]);
```

其中 $g[i][j]$ 为第 $i$ 个矩形贡献为 $j$ 时的最小操作次数。

这个也挺好维护的，考虑直接枚举第 $i$ 个矩形，暴力贪心算贡献，具体的，如果行数小就删列，如果列数小就删行。

于是我们的代码就出来了，其实跟背包没啥区别。

Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
using namespace std;
const int N=1e3+1,M=5e5+1,mod=1e9+7;
int t,n,m,k,a[M],b[M],c[M],d[M],inf=0x7f7f7f7f;
int g[N][N<<1],f[N][N<<1];
signed main(){
	IOS;
	cin>>t;
	while(t--){
		cin>>n>>k;
		int sum=0;
		memset(g,0,sizeof g);
		for(int i=1;i<=n;i++)
			cin>>a[i]>>b[i],
			c[i]=a[i],d[i]=b[i],sum+=a[i]+b[i];
		if(sum<k){
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++){
			int res=0;
			while(1){
			//	cout<<a[i]<<" "<<b[i]<<"\n";
				res++;
				if(a[i]==1&&b[i]==1){
					g[i][res]=g[i][res+1]=g[i][res-1]+1;
					break;
				}
				int x=min(a[i],b[i]);
				if(a[i]==x){
					g[i][res]=g[i][res-1]+a[i];
					b[i]--;
				}
				else{
					g[i][res]=g[i][res-1]+b[i];
					a[i]--;
				}
			}
		}
		memset(f,inf,sizeof f);
		f[0][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=min(k,c[i]+d[i]);j++){
				for(int I=k;I>=j;I--)
					f[i][I]=min(f[i][I],f[i-1][I-j]+g[i][j]);
			}
		}
		cout<<f[n][k]<<"\n";
	}
	return 0;
}
```

时间复杂度近似于：$O(nk^2)$。

空间复杂度：$O(n^2)$。

---

## 作者：ISTP (赞：0)

## 题意简述

[原题链接：https://www.luogu.com.cn/problem/CF2000F](https://www.luogu.com.cn/problem/CF2000F)

有 $n$ 个由空白方格构成的矩形，第 $i$ 个矩形的长和宽为 $a_i,b_i$。可以用 $1$ 的花费给某个矩形的任意一格空白上色，当某个矩形的某一行或列全部上色时会获得 $1$ 的贡献。求总贡献为 $k$ 的最小花费，无解输出 $-1$。

## 思路

一开始考虑的贪心：优先给 $\min(a_i,b_i)$ 最小的矩形从较短边开始上色。但是假了，可以被样例最后一组 hack 掉。根本原因是矩形最后给一个角的方格上色时会同时填满一行与一列，一次获得 $2$ 的贡献。

贪心不了就考虑 dp，尝试构建状态：

设 $dp_{i,j}$ 表示当前枚举到第 $i$ 个矩形，共获得了 $j$ 的贡献时，需要的最小花费；定义 $f(i,p)$ 表示在第 $i$ 个矩形上赚取 $p$ 的贡献需要的最小花费。

容易写出状态转移方程：

$$dp_{i,j}=\min(dp_{i-1,j-p}+f(i,p))$$

其中 $j\in[0,k]$，$p\in[0,\min(j,a_i+b_i)]$，原因显然。

把 $i$ 那一维滚动数组压掉，任务转为 $O(1)$ 计算出 $f(i,p)$ 的值。

首先可以肯定是一直沿着矩形较短的一边涂色。

那么我们将整个涂色过程分为两部分，以矩形第一次被涂成正方形后**再涂一列**为界限，这样比较方便计算。

设 $a_i$ 是长宽中较短的一条，$b_i$ 是较长的。如果前半部分产生的贡献足够，即 $b_i-(a_i-1) \ge p$，那么显然花费为 $p \times a_i$。

否则先有 $(b_i-(a_i-1)) \times a_i$ 的花费，剩下的花费为如下序列的某个前缀：$x-1,x-1,x-2,x-2,\dots3,3,2,2,1,1$。

可以看出是个每一项出现了两次的，公差为 $-1$ 的等差数列。首项项数总和都已知，随便搞一搞就算出来了。具体看代码。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;

void input();
int t;
int n, k;
int a[maxn], b[maxn];

void solve();

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> t;
	while(t --) solve();
	return 0;
}

const int inf = 0x3f3f3f3f;

int dp[2][200 * maxn];
int cclt(int, int);

void solve(){

	input();

	memset(dp, 0x3f, sizeof dp);
	int x = 0;

	dp[0][0] = 0;

	for(int i = 1; i <= n; i ++){
		x ^= 1;
		for(int j = 0; j <= k; j ++){
			for(int p = 0; p <= min(j, a[i] + b[i]); p ++){
				dp[x][j] = min(dp[x][j], dp[x ^ 1][j - p] + cclt(i, p));
			}
		}
	}

	cout << (dp[x][k] == inf? -1: dp[x][k]) << '\n';
	return ;
}

int cclt(int idx, int cnt){

	int x = a[idx], y = b[idx];
	if(x > y) swap(x, y);
	if(cnt <= y - (x - 1)) return cnt * x;
	int sum = y - (x - 1);
	int tmp = cnt - sum;
	int ed = ((x - 1) * 2 - tmp + 1) / 2;
	int pre;
	if(tmp & 1) pre = (1 + ed) * ed - ed;
	else pre = (1 + ed) * ed;
	int res = sum * x + x * (x - 1) - pre;
	return res;
}

void input(){

	cin >> n >> k;
	for(int i = 1; i <= n; i ++) cin >> a[i] >> b[i];
	return ;
}
```

[CF 提交记录](https://codeforces.com/problemset/submission/2000/290541103)

完结撒花。有解释不到位的地方欢迎评论区提出。

---

## 作者：BrotherCall (赞：0)

这种题乍一看有点复杂，实际上就是一步一步分析性质就出来了。

第一步化繁为简。

如果只有一个矩形，矩形大小为 $n\times m$。

**性质1**：获得的分数区间为 $[0,nm - 2] \cup\{nm\}$。

为什么取不到 $nm - 1$ 呢，因为取到这个需要满足：存在未染色点的行数 $+$ 列数 $=1$。但是如果有一个点未染色，这个数字就已经等于 $2$ 了，有更多的点未染色的话这个数字只增不减。

**性质2**：把给一整条连续的方格染色想成给长或宽裁掉 $1$ 个单位宽度的边，那么每次贪心地沿着短边裁。

前半句话是常见做法模型，后半句话是很常规的贪心，都很显然。

于是我们就可以得到：对于每一个矩形，每个可获得的分数 $i$，需染色的最少点数 $v_i$。

---

到这里就已经化繁为简完了，不难发现题意就被转化为了分组背包，也就是每一组最多拿 $1$ 个的背包。

即把每一个矩形看作一个分组，获得的分数为体积，染色点数为价值。

设 $f_{i,j}$ 代表前 $i$ 个矩形获得 $j$ 分最少的染色点数，按照上面说的转移即可。

时间复杂度 $O(nk^2)$。

[提交记录](https://codeforces.com/contest/2000/submission/282461200)。

---

## 作者：Ke_scholar (赞：0)

# [Color Rows and Columns](https://codeforces.com/contest/2000/problem/F)

## 思路

一个长为 $a$，宽为 $b$ 的矩形可以产生的贡献应该是 $0,1,2,\dots a+b-3,a+b-2,a+b$，诶？$a+b-1$ 呢？试想一下，当矩形中只差一个未涂满的情况下，长和宽分别是 $a-1,b-1$，这个时候产生的贡献为 $a+b-2$，那么当我们填上这一个点，长和宽就会刚好被涂满，从而产生 $a+b$ 的贡献，所以 $a+b-1$ 的情况是不会产生的。

根据以上结论，我们可以处理出每个矩形获得相应点数的代价和贡献，然后从每个矩形中选择一个贡献（不选择以贡献为0的形式展现）出来，然后得到至少为 $k$ 的最小代价。

没错，这就是分组背包典型模板了，值得注意的是题目中要求的是至少为 $k$ 的最小代价，也就是说可能存在分数大于 $k$ 且代价更小的情况，这个时候我们背包的范围就要取大一点，至少也得 $k+1$（不要刚好取 $100$，$k$ 也可以等于$100$）。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {

	int n, k;
	cin >> n >> k;

	vector w(n + 1, vector<array<i64, 2>>());
	vector<array<int, 2>> a(n + 1);
	for (int j = 1, x, y; j <= n; j ++) {
		cin >> x >> y;
		a[j] = {x, y};
		int tx = x, ty = y;
		for (int i = 1, sum = 0; i <= x + y; i ++) {
			if (i == x + y - 1) continue;
			if (i == x + y) {
				w[j].push_back({i, x * y});
			} else {
				sum += min(tx, ty);
				tx > ty ? tx-- : ty--;
				w[j].push_back({i, sum});
			}
		}
	}

	const int N = 114, M = N - 10;
	vector<i64> dp(N, INT_MAX);

	dp[0] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = M; j >= 0; j --) {
			for (auto &[cost , val] : w[i]) {
				if (j < cost) continue;
				dp[j] = min(dp[j], dp[j - cost] + val);
			}
		}
	}

	i64 ans = -1;
	for (int i = k; i <= M; i ++) {
		if (dp[i] != INT_MAX) {
			if (ans == -1) ans = dp[i];
			else ans = min(ans, dp[i]);
		}
	}

	cout << ans << '\n';

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}

```

---

