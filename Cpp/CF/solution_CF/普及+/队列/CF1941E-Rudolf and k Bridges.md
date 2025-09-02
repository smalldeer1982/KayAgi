# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0```

### 输出

```
4
8
4
15
14```

# 题解

## 作者：luobotianle (赞：10)

## 分析

由于每一座桥都是独立的，所以我们可以一座一座来分析，然后维护一个前缀和数组，最后求出连续 $k$ 座桥的最小代价。

对于每一行的最小代价可以用 DP 解决，设 $f[i]$ 表示搭建到第 $i$ 个位置，且第 $i$ 个位置放桥墩时的最小代价，$c[i]$ 表示在第 $i$ 个位置建桥的代价，则有状态转移方程 $:$

$f[i] =\min \ ( \ f[i] \ , \ f[j]+c[i] \ ) \ , \ i-d-1 \le j < i$ 。

这样做的复杂度是 $O(T \cdot nmd)$ ，显然超时，考虑单调队列优化。

单调队列采用了 deque 的写法，最终复杂度 $O(T \cdot nm)$ 。

细节都放在代码里了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,k,T,d;
int a[105][N];
ll f[N];//记得开 long long,实测不开会 Wrong answer on test 7
ll ans[N],anss;
int main(){
	ios::sync_with_stdio(0);//cin加速 
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k>>d;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];//读入数据 
			}
		}
		for(int j=1;j<=n;j++){
			deque<ll> q;//单调队列 
			q.clear();
			f[1]=a[j][1]+1;//每次都可以用同一个 f 数组
			q.push_back(1);
			for(register int i=2;i<=m;i++){
				if(!q.empty()&&i-q.front()>d+1)q.pop_front();//老队员退役 
				f[i]=f[q.front()]+a[j][i]+1;
				while(!q.empty()&&f[q.back()]>f[i])q.pop_back();//比新生弱的当场退役 
				q.push_back(i);
			}
			ans[j]=ans[j-1]+f[m];//更新前缀和 ans 数组 
		}
		ll anss=ans[k];
		for(int i=k+1;i<=n;i++){
			anss=min(anss,ans[i]-ans[i-k]);//更新答案 
		}
		cout<<anss<<endl;
	}
	return 0;//AC
}
```

---

## 作者：2huk (赞：8)

有一条 $n \times m$ 的河。第 $i$ 行第 $j$ 列的深度为 $a_{i, j}$。保证 $a_{i, 1} = a_{i, m} = 0$。

如果在第 $i$ 行第 $j$ 列安置桥墩，所需代价为 $a_{i, j} + 1$。

你需要选择连续的 $k$ 行，每行都要架起若干个桥墩，并满足以下条件：

1.  每行的第 $1$ 列必须架桥墩；
2.  每行的第 $m$ 列必须架桥墩；
3.  每行的相邻两个桥墩的距离不超过 $d$。其中 $(i, j_1)$ 和 $(i, j_2)$ 之间的距离为 $|j_1 - j_2| - 1$。

求最小代价和。

---

行与行之间架桥墩并无关系。我们可以求出第 $i$ 行所需的最小代价 $g(i)$，那么 $\min_{i=1}^{n-k+1}\sum_{j=i}^{i+k-1}g(j)$ 即为答案。

对于每一行分别 DP，当前是第 $r$ 行。设状态 $f(i)$ 表示若只考虑前 $i$ 列，且第 $i$ 列一定架桥，所需的最小代价和。转移枚举上一个桥墩的位置，即：
$$
f(i) = a_{r, i} + 1 + \min_{j=i-k-1}^{i - 1} f(j)
$$
发现后面的 $\min_{j=i-k-1}^{i - 1} f(j)$ 可以非常容易地用数据结构维护，例如单调队列或线段树。

总时间复杂度为 $\Theta(nm\log m)$，用线段树实现的。

<https://codeforces.com/contest/1941/submission/251199109>

---

## 作者：wsx248 (赞：7)

读完题目不难想到只需先求出每一行的最优建桥消耗，再依次以每一行为起点求长为 $k$ 的最小连续和即可。

第一步，求每一行的最优建桥消耗。显然可以 $dp$。

设 $dp_i$ 表示在位置 $i$ 上建桥的最小消耗，易得转移方程：$dp_i=\min(dp_j+a_i+1)$，其中 $a_i$ 指每个位置的水深，$j$ 从 $\max(1,i-d+1)$ 取到 $i-1$。代码如下：

```cpp
dp[1] = 1;
for(int i=2;i<=m;i++)
{
	for(int j=max(1, i-d-1);j<i;j++)
		dp[i] = min(dp[i], dp[j]+a[i]+1);
}
```

这样转移的时间复杂度是 $O(md)$ 的，需要优化。

内层循环是在一个固定长度的区间内寻找最小值，套用单调队列优化即可，每次转移时直接取队头，入队时将所有劣于当前 $dp_i$ 的位置从队尾出队。

```cpp
void solve(long long a[], long long dp[])
{
	dp[1] = 1;
	deque<int> q;
	q.push_back(1);
	for(int i=2;i<=m;i++)
	{
		if(q.size() && q.front()<i-d-1)
			q.pop_front();
		dp[i] = dp[q.front()] + a[i] + 1;
		while(q.size() && dp[q.back()]>=dp[i])
			q.pop_back();
		q.push_back(i);
	}
}
```

第二步，以每一行为起点求长为 $k$ 的最小连续和。

因为 $n$ 比较小，直接暴力枚举就行；也可以把每一行的 $dp_m$ 保存下来做前缀和，然后用前缀和优化区间和的求取。

---

## 作者：luqyou (赞：3)

# 思路

显然每座桥是独立的，所以考虑在 $i$ 行建桥的代价。

我们令 $dp_{i}$ 为这一行以 $j$ 为终点建桥的最小代价，$c_{i}$ 为在该行位置 $i$ 的地方建桥的代价，则有 $dp_{i}=\min\limits_{j=i-d-1}\limits^{i-1} dp_{j}+c_i$。

这么做显然是 $O(n^2m)$ 的，考虑优化。

不难想到每次算出 $dp$ 值的时候将其插入一个 set 中，过期时再删除即可。时间复杂度 $O(nm \log n)$。

# code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=2e5+10;
int n,m,k,d;
vector<int> a[101],dp[101];
multiset<int> s;
void Erase(int x){
	s.erase(s.find(x));
}
void solve(){
	cin>>n>>m>>k>>d;
	priority_queue<int> q;
	for(int i=1;i<=n;i++){
		a[i].resize(m+1);
		dp[i].resize(m+1);
		s.clear();
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			a[i][j]++;
		}
		dp[i][1]=a[i][1];
		s.insert(dp[i][1]); 
//		cout<<dp[i][1]<<" ";
		for(int j=2;j<=m;j++){
			dp[i][j]=*s.begin()+a[i][j];
//			cout<<dp[i][j]<<" ";
			s.insert(dp[i][j]);
			if(j>d+1){
				Erase(dp[i][j-d-1]);
			}
		}
//		cout<<endl;
	}
	int ans=LLONG_MAX,res=0;
	for(int i=1;i<k;i++){
		res+=dp[i][m];
	} 
	for(int i=k;i<=n;i++){
		res+=dp[i][m];
		ans=min(ans,res);
		res-=dp[i-k+1][m]; 
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：OPEC (赞：1)

# [CF1941E Rudolf and k Bridges](https://www.luogu.com.cn/problem/CF1941E)
这道题只需要算出每一行最少要花多少，再用前缀和统计即可。

但如果暴力遍历每一个数的话时间复杂度是 $O(nm^2)$ 会超时。

我们需要更省时间的算法。定义 $i$ 为第 $i$ 行，$j$ 为前 $j$ 列，$f_j$ 为到前 $j$ 列。则 $f_j=a_{i,j}+\min(f_{i-k-1}\sim f_{i-1})+1$，最小值可以用[线段树](https://www.luogu.com.cn/article/4e8rrz12) $O(nm\log n)$ 或[单调队列](https://www.luogu.com.cn/article/81dr677c)维护 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e2+10,M=2e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int n,m,k,d,t;
int a[N][M];
int f[M];
struct Node //线段树
{
	int l,r;
	double v;
}tr[4000005];
#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)
void pushup(int rt)
{
	tr[rt].v=min(tr[lson].v,tr[rson].v);
}
void build(int rt,int l,int r)
{
	tr[rt]={l,r,0};
	if(l==r)
	{
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(rt);
}
void update(int rt,int p,double v)
{
	int l=tr[rt].l;
	int r=tr[rt].r;
	if(l==r)
	{
		tr[rt].v=v;
		return;
	}
	if(p<=mid)
		update(lson,p,v);
	if(p>mid)
	{
		update(rson,p,v);
	}
	pushup(rt);
}
Node query(int rt,int sp,int ep)
{
	int l=tr[rt].l;
	int r=tr[rt].r;
	if(sp<=l&&r<=ep)
	{
		return tr[rt];
	}
	if(ep<=mid)
		return query(lson,sp,ep);
	if(sp>mid)
		return query(rson,sp,ep);
	Node L=query(lson,sp,ep);
	Node R=query(rson,sp,ep);
	Node res;
	res.v=min(L.v,R.v);
	return res; 
}
#undef lson
#undef rson
#undef mid
void solve()
{
	int s[N]={};
	cin>>n>>m>>k>>d;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
//	for(int i=1;i<=n;i++)
//	{
//		build(1,1,m);
//		f[1]=a[i][1]+1;
//		update(1,1,f[1]);
//		for(int j=2;j<=m;j++)
//		{
//			f[j]=a[i][j]+query(1,max((int)1,j-d-1),j-1)+1;//按式子//按式子
//			update(1,j,f[j]);//将这个数放入
//		}
//		s[i]=s[i-1]+f[m];//前缀和统计
//	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[j]=0;
		}
		f[1]=1;
		deque<int> dq;
		dq.push_back(1);
		for(int j=2;j<=m;j++)
		{
			while(!dq.empty()&&dq.front()<j-d-1)
			{
				dq.pop_front();//把不在区间内的删掉
			}
			f[j]=f[dq.front()]+a[i][j]+1;//按式子
			while(!dq.empty()&&f[dq.back()]>=f[j])
			{
				dq.pop_back();//把不在优秀的剔除
			}
			dq.push_back(j);
		}
		s[i]=s[i-1]+f[m];//前缀和统计
	}
	int mn=INF;
	for(int i=k;i<=n;i++)
	{
		mn=min(mn,s[i]-s[i-k]);//求1+i至i+k+1的和中的最小值
	}
	cout<<mn<<'/n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：yhylivedream (赞：1)

## 分析

先考虑只有一行的情况：

设状态 $dp_i$ 表示建一座 $1$ 到 $i$ 的桥并在 $i$ 处建桥墩的最小代价。
 
状态转移方程：

$dp_i=\displaystyle\min_{i-d \le j \le i-1}\{dp_j\}+a_i$。

朴素的转移是 $O(md)$ 的，发现求最小值可以用单调队列优化，时间复杂度：$O(m)$。

再扩展到多行的情况：由于是连续 $k$ 行建桥，很容易想到用前缀和，具体看代码。

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long//要开long long

using namespace std;

const int N = 5e5 + 5;
int T, n, m, k, d, a[N], dp[N], pre[N];

int solve () {
  deque <int> q;
  memset(dp, 0x3f, sizeof dp), dp[1] = 1;
  q.push_back(1);
  for (int i = 2; i <= m; i ++) {
    dp[i] = min (dp[i], dp[q.front()] + a[i]);
    for (; q.size() && dp[i] <= dp[q.back()]; q.pop_back()) {}
    q.push_back(i);
    for (; q.size() && q.back() - q.front() > d; q.pop_front()) {}
  }
  return dp[m];
}

signed main () {
  for (cin >> T; T; T --) {
    cin >> n >> m >> k >> d;
    for (int i = 1; i <= n; i ++) {
      for (int i = 1; i <= m; i ++) {
        cin >> a[i]; a[i] ++;
      }
      pre[i] = pre[i - 1] + solve ();
    }
    int minv = 1e18;
    for (int i = k; i <= n; i ++) {
      minv = min (minv, pre[i] - pre[i - k]);
    }
    cout << minv << '\n';
  }
  return 0;
}
```

---

## 作者：GenesisCrystal (赞：1)

~~在%你赛做出来的，感觉难度能够有绿~~

## Soulution
肯定是要枚举每一个 $1 \le i \le n$ 做 DP 的，然后用 $ans_i$ 存储第 $i$ 行的答案。

在每一行中 DP，设 $dp_j$ 为第 $j$ 个时的最少支撑数，那么 $dp_j$ 就是 $dp_k+a_{i,j}+(\max\{0, j-d\}\le l\le j-1)$，所以我们就可以使用**单调队列**来优化 DP。

但是要注意，将不合要求的老元素删除要在前面，删去后面的元素要在求 $dp_j$ 后面。

## Code

```cpp
/// @author WUYIXUAN_
#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 1, kMaxM = 101;

deque<ll> q;
ll t, n, m, k, d, a[kMaxM][kMaxN], dp[kMaxN];

int main() {
  ios::sync_with_stdio(0);
#ifdef WUYIXUAN_
  freopen("D.txt", "w", stdout);
#endif
  for (cin >> t; t; t--) {
    cin >> n >> m >> k >> d;
    ll ans[kMaxM] = {};
    for (int i = 1; i <= n; i++) {
      ll sum = 0;
      q.clear();
      fill(dp + 1, dp + m + 1, 0);
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
        while (!q.empty() && j - q.front() - 1 > d) {
          q.pop_front();
        }
        dp[j] = dp[(q.empty() ? 0 : q.front())] + a[i][j] + 1;
        while (!q.empty() && dp[q.back()] >= dp[j]) {
          q.pop_back();
        }
        q.push_back(j);
      }
      ans[i] = dp[m];
    }
    ll sum = 1e18;
    for (int i = 1; i <= n; i++) {
      ans[i] += ans[i - 1];
      if (i >= k) {
        sum = min(sum, ans[i] - ans[i - k]);
      }
    }
    cout << sum << '\n';
  }
  return 0;
}
```

---

## 作者：IGA_Indigo (赞：1)

## 题目大意
就是让你在 $n\times m$ 的河上按照规定建桥墩，有一个参数 $a_{i,j}$，每一座在 $a_{i,j}$ 上的桥墩所需要的代价都是 $a_{i,j}+1$。

题目输入输出格式都没有翻译，为了避免有人不会英语（雾），这里简单介绍一下。

### 输入格式
第一行一个整数 $t$（$1\le t\le 10^3$），表示 $t$ 组数据。

每组中第一行，四个整数分别为 $n$、$m$、$k$ 和 $d$。

接下来 $n$ 行，每行 $m$ 个正整数，第 $i$ 行第 $j$ 列表示 $a_{i,j}$。
### 输出格式
一个正整数，表示最小代价和。
## 大体思路
是一个典型的 DP 问题。
### 状态设置
$f_{i,j}$ 表示处理到第 $i$ 行第 $j$ 列的最小代价，我们滚动优化一下就可以设为 $f_{i}$ 为处理到当前行第 $i$ 列的最小代价。
### 状态转移
$f_i=\min(f_{i},f_k+a_{j,i})$（$i-d-1\le k\le i$）

这样的话显然会超时，我们需要优化，用单调队列优化，用单调队列维护最小的 $f$ 的下标，代码中有详细解析。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][200005];
long long f[200005],sum[200005];
deque<long long> q;//用双端队列模拟单调队列比较好模拟出队入队 
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k,d;
		cin>>n>>m>>k>>d;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			f[1]=a[i][1]+1; 
			q.push_back(1);//说什么也得有个f[1] 
			for(int j=2;j<=m;j++){
				if(!q.empty()&&j-q.front()-1>d){//超过两个桥墩的最大距离 
					q.pop_front();//队头出队 
				}
				f[j]=f[q.front()]+a[i][j]+1;//状态转移 
				while(!q.empty()&&f[q.back()]>f[j]){
					q.pop_back();//保证队头永远是最小的那个的下标 
				}
				q.push_back(j);
			}
			sum[i]=sum[i-1]+f[m];//前缀和 
			q.clear();//处理完之后清空队列
		}
		long long ans=LLONG_MAX;
		for(int i=k;i<=n;i++){
			ans=min(ans,sum[i]-sum[i-k]);
		}//找到最小值输出即可 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：haokee (赞：1)

首先每一行需要花费的成本是不变的，而这里是选择连续的 $k$ 行，因此可以使用前缀和优化。那么我们就需要对每一行求解。

假设当前行的数组为 $a$，那么设 $dp_i$ 表示为修桥修到 $i$ 的成本，这个值就等于所有距离小于等于 $d$ 的 $j$，当中 $dp_j$ 的最小值加上 $a_i+1$。但是这题 $d\le 2\times 10^5$，因此我们需要使用单调队列优化。由于好渴鹅懒得写单调队列，因此直接使用优先队列。

时间复杂度 $\mathcal O(n\times m\log_2 d)$。

```cpp
#include <iostream>
#include <utility>
#include <queue>

using namespace std;
using LL = long long;

const LL kMaxN = 105, kMaxM = 2e5 + 5;

LL a[kMaxN][kMaxM], dp[kMaxM], p[kMaxN], t, n, m, k, d, ans;
priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<>> q;

void solve(LL x) {
  for (; q.size(); q.pop()) { }
  q.emplace(a[x][1] + 1, 1);
  for (LL i = 2; i <= m; i++) {
    for (; q.top().second < i - d - 1; q.pop()) { }
    q.emplace(q.top().first + a[x][i] + 1, i);
  }
  for (; q.top().second != m; q.pop()) { }
  p[x] = q.top().first;
}

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> m >> k >> d;
    ans = 1e18;
    for (LL i = 1; i <= n; i++) {
      for (LL j = 1; j <= m; j++) {
        cin >> a[i][j];
      }
    }
    for (LL i = 1; i <= n; i++) {
      solve(i);
      p[i] += p[i - 1];
    }
    for (LL i = k; i <= n; i++) {
      ans = min(ans, p[i] - p[i - k]);
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1941e-rudolf-and-k-bridges-de-ti-jie/)
## 题目大意
在第 $(i,j)$ 个格子修建一个桥墩需要 $a_{i,j}+1$ 的花费而且要求 $(i,0)$ 与 $(i,m)$ 必须修建桥墩并且桥墩之间的距离不得大于 $d$。现在需要求见 $k$ 个**连续**的桥，求最小代价。

其中 $1\le k\le n \le 100,3\le m\le 2\cdot 10,1\le d\le m$。
## 思路
因为每一座桥修建的代价与其他桥是否修建无关，所以我们可以将每一座桥的修建代价求解出来，最终求出连续 $k$ 座桥全部修建的最小值。

假设 $f_i$ 表示在第 $i$ 个位置修建桥墩而且 $1$ 至 $i-1$ 在修建则桥墩之后全部可以修桥的最小花费。

因为在第 $i$ 个位置修建桥墩前，从 $i-d-1$ 到 $i-1$ 只要有一个修建桥墩就可以，所以状态转移方程如下：
$$f_i= \min_{j=i-d-1}^{i-1} f_j$$
这样写的时间复杂度为 $O(T\cdot nmd)$ 无法通过此题，可以考虑使用单点修改区间最小值查询线段树进行维护，这样时间复杂度就变成了 $O(T\cdot nm \log d)$。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,INF=0x3f3f3f3f3f3f3f3f;
int n,m,num,d,a[N],f[N],s[N<<2],ans[N];
void change(int k,int l,int r,int x,int v) {
	if(l==r&&l==x) {
        s[k]=v;
		return;
	}
	if(x<l||x>r) return;
	int mid=(l+r)/2;
	if(l<=x&&x<=mid) change(k*2,l,mid,x,v);
	if(mid+1<=x&&x<=r) change(k*2+1,mid+1,r,x,v);
	s[k]=min(s[k*2],s[k*2+1]);
}
int ask(int k,int l,int r,int x,int y) {
	if(y<l||x>r) return INF;
	if(x<=l&&r<=y) return s[k];
	int mid=(l+r)/2;
	return min(ask(k*2,l,mid,x,y),ask(k*2+1,mid+1,r,x,y));
}
void go(int number){
	for(int i=1;i<=m;i++) cin>>a[i];
	f[1]=1;
	change(1,1,m,1,1);
	for(int i=2;i<=m;i++){
		f[i]=ask(1,1,m,max(i-d-1,1ll),max(i-1,1ll))+a[i]+1;
		change(1,1,m,i,f[i]);
	}
	ans[number]=f[m];
}
void solve(){
	cin>>n>>m>>num>>d;
	for(int i=1;i<=n;i++) go(i);
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
	int sum=INF;
	for(int i=1;i+num-1<=n;i++) sum=min(sum,ans[i+num-1]-ans[i-1]);
	cout<<sum<<'\n';
}signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[CF1941E](https://www.luogu.com.cn/problem/CF1941E)。

~~明天要考试了，今天赶紧恶补 dp……~~

## 题意

有一个 $n \times m$ 的数组，第 $i$ 行 $j$ 列的元素为 $a_{i,j}+1$。在数组中选连续 $k$ 行，每行要保证：

1. 第一列、第 $m$ 列必须取；
1. 取的相邻两个元素 $a_x$ 和 $a_y$（$x<y$），满足 $y-x -1  \le d$。

求取的数之和的最小值。

## 思路

首先不同的行之间互不影响，所以考虑求出每行的最小代价后，对行做个前缀和，这样就能知道连续 $k$ 行的答案。

显然有一个暴力 dp：设 $f_{i}$ 表示到了第 $i$ 列，并且强制取第 $i$ 列的数的答案。

显然有 $ f_{i} \gets \min\limits_{j-d-1 \leq j<i} \{f_{j}\}+a_i+1$。

然后那个区间最小值可以用单调队列维护。维护单调递增的队列，对每个 $i$，先从队首转移，再把它也扔到队列里面。

## 代码

本人码风：用 $(l,r]$ 表示队列。

```cpp
#include<cstdio>
using namespace std;
int t,n,m,q[200000],l,r,a,k,d;
long long f[200001],s[101],ans;
long long min(long long x,long long y){return x>y?y:x;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&n,&m,&k,&d),ans=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;++i){
			l=r=-1,scanf("%*d"),f[1]=q[++r]=1;
			for(int j=2;j<=m;++j){
				scanf("%d",&a);
				while(l<r&&q[l+1]<j-d-1)++l;
				f[j]=f[q[l+1]]+a+1;
				while(l<r&&f[q[r]]>f[j])--r;
				q[++r]=j;
			}s[i]=s[i-1]+f[m];
		}for(int i=k;i<=n;++i)ans=min(ans,s[i]-s[i-k]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：crz_qwq (赞：0)

### Part 1 : 暴力
设 $f_{i,j}$ 为第 $i$ 条河前 $j$ 个单元格的最小成本，则有初始状态 $f_{i,1}=1$ ，由于每次可以取 $d$ 个，所以状态转移方程就是 $f_{i,j}=\operatorname{min}(f_{i,j-k}+a_i+1)$\
其中 $k$ 的范围是 $\operatorname{max}(1,j-d-1) \le k \le i-1$\
可以得出答案是 $\operatorname{min}(\sum_{j=i}^{i+K-1}f_{j,m})$\
其中 $i$ 的范围是 $1 \le i+K-1 \le n $。

时间复杂度：$O(Tnm^2)$。

### Part 2 : 优化
上述算法时间复杂度过大，显然面对 $m \le 2\times 10^5$ 的数据范围是力不从心的，所以考虑优化。
明显，对于动态规划的转移，可以使用比暴力更快的线段树维护，这样时间复杂度就降到了 $O(Tnm \log m)$，明显可以通过此题。

### Part 3 : 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=0x3f3f3f3f3f3f3f3f;
int tree[N<<2];
int ls(int p){return p<<1;}
int rs(int p){return p<<1|1;}
void pushup(int p){tree[p]=min(tree[ls(p)],tree[rs(p)]);}
void build(int p,int pl,int pr)
{
    if(pl==pr)
    {
        tree[p]=inf;
        return ;
    }
    int mid=pl+pr>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    pushup(p);
}
void update(int p,int pl,int pr,int x,int d)
{
    if(pl==x&&pr==x)
    {
        tree[p]=d;
        return ;
    }
    if(pr<x||x<pl)
        return ;
    int mid=pl+pr>>1;
    update(ls(p),pl,mid,x,d);
    update(rs(p),mid+1,pr,x,d);
    pushup(p);
}
int query(int p,int pl,int pr,int L,int R)
{
    if(L<=pl&&pr<=R)
        return tree[p];
    if(pr<L||R<pl)
        return inf;
    int mid=pl+pr>>1;
    return min(query(ls(p),pl,mid,L,R),query(rs(p),mid+1,pr,L,R));
}//dp数组
int a[N],ans[N]; 
void solve()
{
    memset(ans,0,sizeof ans);
    int n,m,K,d;
    cin>>n>>m>>K>>d;
    for(int k=1;k<=n;++k)
    {
        for(int i=1;i<=m;++i)
            cin>>a[i];
        build(1,1,m);
        update(1,1,m,1,1);//dp[1]=1;
        for(int i=2;i<=m;++i)
        {
            //dp[i]=min(dp[i-j]+a[i]+1) max(i-K,1)<=j<=i-1
            update(1,1,m,i,query(1,1,m,max(1LL,i-d-1),i-1)+a[i]+1);            
        }
        ans[k]=query(1,1,m,m,m);
    }
    int res=inf;
    for(int i=1;i+K-1<=n;++i)
    {
        int sum=0;
        for(int j=i;j<=i+K-1;++j)
            sum+=ans[j];
        res=min(res,sum);
    }
    cout<<res<<'\n';
}

signed main()
{
    int T;
    for(cin>>T;T;--T)
        solve();
}
```

---

## 作者：wangxinyi2010 (赞：0)

### Solution
本题难度：CF：1600，洛谷上对应绿题。CF 上的标签是二分查找，数据结构，动态规划，双指针。

由于各行可以独立计算代价，这道题的状态转移方程很简单，在某一行中，假设在第 $i$ 格上建造柱子，则：
$$dp_i=\underset{i-d-1\leq j \leq i-1}{\min}\:dp_j+a_i+1$$
其中 $j$ 为上一个建造柱子的格子。

但这样会导致时间复杂度达到 $\Omicron (n^2m)$，导致 TLE。

因此我们可以使用单调队列进行优化，在单调队列中插入 $j$，及时清除队尾过大的数与队头失效的数，则队列头即为我们想要的 $j$。

看到上一个用单调队列优化的大佬使用了`include <deque>`，我这个蒟蒻还是手打单调队列吧……

由于河岸的柱子建造成本总为 1，因此本蒟蒻设`dp[1]=2`，把两侧河岸全计算上，这样就不用考虑河岸了。
（然而最后发现要比较从 $dp_{\max(1,m-d-1)}$ 到  $dp_{m-1}$ 的最小值【悲】）

另外，当计算完所有行的建桥成本时，最好使用前缀和计算最小总成本，不仅速度快还可以少打代码。

### tips
1. 手打单调队列要注意开始时在队列里留一个数，即 `head=tail=0`。
2. 先删掉单调队列头失效的元素，再赋值 $dp_i$！
3. 养成好习惯，使用 `memset` 进行清空。（用完一次一定要清空 $dp$,$ans$ 等数组）
4. **开 long long!!!!!!!!!!!!!!!!!!!!!!!!!**

### AC Code
```cpp
#include<iostream> 
#include<cstring>
#define maxn 105
#define maxm 300005
using namespace std;
int t,n,m,k1,d,head,tail,q[maxm];
long long dp[maxm],ans[maxn],sum[maxn];
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>m>>k1>>d;
		memset(ans,0,sizeof(ans));
		memset(sum,0,sizeof(sum));
		for(int j=1;j<=n;j++){
			head=0,tail=0;
			memset(q,0,sizeof(q));
			memset(dp,0,sizeof(dp));
			dp[1]=2;
			long long x;
			cin>>x;
			q[tail]=1;
			for(int k=2;k<m;k++){
				cin>>x;
				if(k-q[head]>d+1) head++;
				dp[k]=dp[q[head]]+x+1; 
				while(head<=tail&&dp[q[tail]]>=dp[k]) tail--;
				q[++tail]=k;
			}
			ans[j]=dp[m-1];
			for(int k=m-2;k>=max(m-d-1,1);k--) ans[j]=min(ans[j],dp[k]);//【悲】
			cin>>x;
		}
		for(int j=1;j<=n;j++) sum[j]=sum[j-1]+ans[j];
		long long minans=sum[k1];
		for(int j=k1+1;j<=n;j++) minans=min(minans,sum[j]-sum[j-k1]);
		cout<<minans<<"\n";
	}
	return 0;
}
```

---

## 作者：Lily_White (赞：0)

## 分析
本题实际上是相对比较独立的两个子问题。第一个子问题是对某一行的分析，求出某一行的最小花费后，再利用前缀和解决选哪个连续区间的问题，就可以求出最终的答案。

怎么求某一行的最小花费呢？这可以用单调队列和 DP 来解决。具体地，我们令 `dp[x]` 表示考虑到 $x$ 及之前时的最小花费。转移时，我们直接考虑前 $x-d-1$ 个的 `dp` 值，并取其中最小者进行转移。而这个问题本质上就是动态求滑动窗口的最小值，是单调队列的模板题。

在本题中，维护单调队列时，只需要注意两点：

- 距离大于 $d$ 的需要出队
- “比我小还比我强的人会使我退役”：如果一个数目前在队列内且大于当前 `dp` 值，则它无论如何都会比现在先出队，不可能被选中，因此需要出队。

实际上，由于本题不大的数据，用 `std::multiset` 实现单调队列也是可行的，这一做法可以参考官方题解。

## 代码
```cpp
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repr(i, m, n) for (int i = (int)m; i <= (int)n; i++)
void Main() {
    int n, m, k, d;
    rd(n, m, k, d);
    vll ans(n);
    rep(i, n) {
        vll dp(m);
        deque<ll> dq;
        dq.push_back(0);
        dp[0] = 1;
        int _;
        rd(_);
        repn(x, m - 1) {
            int cur;
            while (!dq.empty() && dq.front() < x - d - 1) {
                dq.pop_front();
            }
            rd(cur);
            dp[x] = dp[dq.front()] + cur + 1;
            while (!dq.empty() && dp[dq.back()] >= dp[x]) {
                dq.pop_back();
            }
            dq.push_back(x);
        }
        ans[i] = dp[m - 1];
    }
    
    repn(i, n - 1) ans[i] += ans[i - 1];
    ll mn = ans[k - 1];
    repr(i, k, n - 1) {
        chmin(mn, ans[i] - ans[i - k]);
    }
    cout << mn << endl;
}
```

---

## 作者：Special_Tony (赞：0)

纪念一下蒟蒻第一次不看题解独立 AC 单调队列优化 dp。
# 思路
这题其实和 P1725 琪露诺很类似，这题的 $dp_i$ 可以从 $dp_{i-d-1}\sim dp_{i-1}$ 转移过来，然后当然选最小的，所以 $dp_i=a_i+1+\min\limits_{j=i-d-1}^{i-1}dp_j$，然后这个最小值可以用单调队列维护。为了省时，我用了不带 $\log$ 的手写单调队列。

最后因为要求**连续的** $k$ 行，所以可以用前缀和维护。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const ll inf = 1e18;
int t, n, m, x, k, d;
ll dp[200005], s[200005], minx;
deque <int> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m >> k >> d;
		++ d;
		for (int i = 1; i <= n; ++ i) {
			q.clear ();
			for (int j = 1; j <= m; ++ j) {
				cin >> x;
				++ x;
				while (! q.empty () && q.front () < j - d)
					q.pop_front (); //过期了，删掉
				dp[j] = q.empty () ? x : dp[q.front ()] + x;
				while (! q.empty () && dp[q.back ()] >= dp[j])
					q.pop_back (); //把 >= dp[j] 的全部单调队列了（删了）
				q.push_back (j); //在队尾插入
			}
			s[i] = s[i - 1] + dp[m]; //前缀和
		}
		minx = inf;
		for (int i = k; i <= n; ++ i)
			minx = min (minx, s[i] - s[i - k]);
		cout << minx << '\n';
	}
	return 0;
}
```

---

## 作者：xz001 (赞：0)

首先我们知道每列是一个单独的答案，不受其他列影响，所以对于每列用 dp 求出最小代价即可。

设立 $f_i$ 表示河的第 $i$ 个位置设置支架所花费的最小代价，则转移为：

$$
f_i=(\min_{j=\max(1, i-d-1)}^{i-1}f_j)+a_i+1
$$

前面这一部分可以用线段树优化，时间复杂度即为 $O(nm\log m)$。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

using namespace std;

const int N = 2e5 + 5;

struct node {
	int l, r, minn;
};

node t[4 * N];

void push_up (int p) {
	t[p].minn = min(t[ls(p)].minn, t[rs(p)].minn);
	return;
}

void build (int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		
		return;
	}
	int mid = (l + r) >> 1;
	build (l, mid, ls(p));
	build (mid + 1, r, rs(p));
	push_up(p);
	return;
}

void update (int x, int p, int d) {
	if (t[p].l == t[p].r) {
		t[p].minn = d;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) update (x, ls(p), d);
	if (x >  mid) update (x, rs(p), d);
	push_up(p);
	return;
}

int query (int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].minn;
	}
	int mid = (t[p].l + t[p].r) >> 1, sum = 1e18;
	if (l <= mid) sum = min(sum, query (l, r, ls(p)));
	if (r >  mid) sum = min(sum, query (l, r, rs(p)));
	return sum;
}

int tt, n, m, k, d, a[105][200005], sum[N], f[200005];

signed main() {
    cin >> tt;
    while (tt -- ) {
        cin >> n >> m >> k >> d;
        for (int i = 1; i <= n; ++ i )
            for (int j = 1; j <= m; ++ j )
                cin >> a[i][j];
                
        for (int i = 1; i <= n; ++ i ) {
        	build (1, m, 1);
        	f[1] = 1;
        	update (1, 1, 1);
        	for (int j = 2; j <= m; ++ j ) {
        		f[j] = query (max(1ll, j - d - 1), j - 1, 1) + a[i][j] + 1;
        		update (j, 1, f[j]);
			}
			sum[i] = f[m];
		}
		for (int i = 1; i <= n; ++ i ) sum[i] += sum[i - 1];
		int ans = 1e18;
		for (int i = 1; i <= n - k + 1; ++ i ) {
			ans = min(ans, sum[i + k - 1] - sum[i - 1]);
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

