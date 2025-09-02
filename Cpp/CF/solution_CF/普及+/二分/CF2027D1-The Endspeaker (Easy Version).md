# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1```

### 输出

```
1
-1
2
10
4```

# 题解

## 作者：Yorg (赞：3)

# 算法
题意没什么可以转化的，已经很明确了。

容易发现当 $k$ 确定且要进行移除前缀操作时，一定要尽可能的使前缀更大不然一定不优。

考虑动态规划，令 $dp_i$ 表示移除 $a$ 数组的前 $i$ 项所需的最小总成本。

可以发现 $dp_i$ 可以从 $dp_j, 0 \leq j < i$ 推出来，令 $k$ 表示最大的 $k$ 使得可以移除 $[j + 1, i]$ 这一前缀，如果 $k$ 不存在则跳过这一转移。

但是注意到 $k$ 始终不减，考虑新开一维表示当前的 $k$ ，

$$ dp_{i, k} = \min(dp_{j, k^{\prime}} + m - k) , 0 \leq j < i, k^{\prime} \leq k$$

这个柿子的复杂度是 $\mathcal{O}(n^2m^2 \log m)$ 的，考虑优化。

手动模拟一下可以发现，$k^{\prime} \leq k$ 条件带来了大量的重复计算，事实上，我们完全可以每次仅仅令 $k = k^{\prime} + 1 \ \rm{or} \ k^{\prime}$ 。

现在我们的转移柿子变成了，

$$
dp_{i, k} =
\begin{cases}
\begin{aligned}
& dp_{x, k} + m - k \\
& dp_{y, k - 1} + m - k\\
\end{aligned}
\end{cases}
$$

显而易见的，我们需要尽可能的使得 $x, y$ 尽量小，并且满足 $\rm{Sum} (x + 1, i) , \rm{Sum} (y + 1, i) \leq b_k$ ，二分可以处理。

初始化令 $dp_{0, 1} = 0$ ，答案为 $\displaystyle\min_{i = 1}^{m} {dp}_{n, i}$ ，特别的，当无法转移到答案时，输出 $-1$。

时间复杂度 $\mathcal{O} (nm\log m)$ 。

# 总结
观察题目数据可以大概构想出方程形式，

手动模拟可以找到算法劣在哪里。

---

## 作者：Super_Cube (赞：3)

# Solution

注意到 $nm\le 3\times 10^5$，考虑设计出一份能与 $nm$ 扯上关系的代码。

贪心想不出来就来想 dp。设 $dp_{i,j}$ 表示 $k$ 的值目前为 $i$，$a$ 中剩下的第一个元素下标为 $j$ 的最小代价。枚举状态就是 $O(nm)$ 的，感觉很有前途。从 $j$ 开始往后找到第一个位置 $c$ 满足 $a$ 中 $i\sim c$ 的和大于 $b_j$，有转移：$dp_{i,c}\gets dp_{i,j}+m-i$，因为每次转移一个极大的连续段肯定更优。还有种情况是直接使 $k$ 往后移，即 $dp_{i+1,j}\gets dp_{i,j}$。初始化 $dp_{1,1}=0$，答案为 $\displaystyle\min_{i=1}^m dp_{i,n+1}$。

依据找 $c$ 的实现方法，时间复杂度为 $O(nm\log n)$ 或 $O(nm)$。

# Code

这里给出利用二分找到 $c$ 的代码。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
const ll inf=0x3f3f3f3f3f3f3f3f;
std::vector<std::vector<ll> >dp;
std::vector<ll>a;
std::vector<int>b;
int T,n,m;
ll ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		a.resize(n+1);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),a[i]+=a[i-1];
		b.resize(m+1);
		for(int i=1;i<=m;++i)
			scanf("%d",&b[i]);
		dp.clear();
		dp.resize(m+2,std::vector<ll>(n+2,inf));
		ans=inf;dp[1][1]=0;
		for(int j=1;j<=m;++j){
			for(int i=1,k;i<=n;++i){
				k=std::upper_bound(a.begin()+i,a.begin()+n+1,b[j]+a[i-1])-a.begin();
				if(k>i)dp[j][k]=std::min(dp[j][k],dp[j][i]+m-j);
				dp[j+1][i]=std::min(dp[j+1][i],dp[j][i]); 
			}
			ans=std::min(ans,dp[j][n+1]);
		}
		if(ans==inf)ans=-1;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：灵乌路空 (赞：2)

特别指出了 $n\cdot m\le 3\times 10^5$，看来是非常有用的条件。

发现最优的操作序列一定是交替进行多次操作 1 和操作 2，于是考虑 DP，设使用操作 $1\sim i$，恰好删除了前缀 $1\sim j$ 的最小代价，初始化 $f_{0, 0} = 0$ 则显然有转移：

$$\begin{cases}
    f_{i, j}\leftarrow f_{i - 1, j}\\
    f_{i, j}\leftarrow \min f_{i, j - k} + m - i &\left(b_i \ge \sum_{j-k< l\le j} a_l\right)
\end{cases}$$

答案即为 $f_{m, n}$，朴素实现时间复杂度 $O(n^2m)$ 级别，空间复杂度 $O(nm)$ 级别，时空双爆炸啊有点呃呃。

考虑优化，发现第一维可以滚动数组优化，空间复杂度变为 $O(m)$ 级别；观察易知对于某个确定的 $i$，当 $j$ 递增时 $f_{i, j}$ 肯定单调不降，则第二种转移的最优决策有单调性，一定会选择在 $b_i \ge \sum_{j-k\le l\le j} a_l$ 的最大的 $k$ 处进行转移，套路地考虑双指针优化即可。

总时间复杂度变为 $O(nm)$ 级别。

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 3e5 + 10;
const LL kInf = 1e18;
//=============================================================
int n, m, a[kN], b[kN];
LL sum[kN], f[2][kN];
//=============================================================
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++ i) std::cin >> a[i], sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= m; ++ i) std::cin >> b[i];
    
    int now = 1;
    for (int i = 1; i <= n; ++ i) f[0][i] = kInf;
    for (int i = 1; i <= m; ++ i, now ^= 1) {
      for (int r = 1, l = 1; r <= n; ++ r) {
        f[now][r] = f[now ^ 1][r];
        while (l <= r && sum[r] - sum[l - 1] > b[i]) ++ l;
        if (l <= r) f[now][r] = std::min(f[now][r], f[now][l - 1] + m - i);
      }
    }
    std::cout << (f[now ^ 1][n] < kInf ? f[now ^ 1][n] : -1) << "\n";
  }
  return 0;
}
```

---

## 作者：program_xwl (赞：0)

## 思路：
动态规划。
### 确定状态：
$dp_{i,j}$ 表示前 $i$ 个元素中上一次至少删除 $j$ 个的最小花费。
### 确定答案：
很显然是 $dp_{n,m}$。
### 状态转移：
从小到大枚举 $i$ 和 $j$，每次转移时用二分找到前缀和 $\ge sum_i-b_i$ 的最靠左的元素编号 $l$，因为在 $j$ 一样的情况下，$i$ 变小 $dp_{i,j}$ 一定不会更大，这是显而易见的。
1. 当 $l<i,sum_i-sum_l \le b_j$ 时，说明当前可以用 $k=j$ 进行转移。尝试转移并得到更优的结果，$dp_{i,j} = \min(dp_{l,j}+(m-j),dp_{i,j-1})$。
2. 当不满足第一种情况的条件时，说明当前不能用 $k=j$ 进行转移。所以，$dp_{i,j}=dp_{i,j-1}$。

### 初始状态：
$dp_{i,0} = \infty(0\le i\le n)$，不删是一种非法情况。

如果没看懂，请看代码注释。
## 代码：
>莫抄袭，棕了你的名，空悲切！——[program_xwl](https://www.luogu.com.cn/user/1202682)
```cpp
#include <bits/stdc++.h>
using namespace std;

long long T,n,m,a[300005],b[300005],sum[300005];
vector<vector<long long> >dp;

int find(long long x)//二分查找
{
	int l = -1,r = n+1;
	while(l+1 < r)
	{
		long long mid = (l+r)/2;
		if(sum[mid] >= x) r = mid;
		else l = mid;
	}
	return r;
}

bool check(void)//判是否无解
{
	for(int i = 1;i <= n;i++) if(a[i] > b[1]) return 0;//如果存在最大的 bi 都无法删除 ai，无解
	return 1;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n >> m;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = 1;i <= m;i++) cin >> b[i];
		if(check() == 0)//提前判无解
		{
			cout << "-1\n";
			continue;
		}
		dp.clear();//这一行不能丢！！！
		dp.resize(n+5);
		for(int i = 0;i < n+5;i++) dp[i].resize(m+5);
		for(int i = 1;i <= n;i++) sum[i] = sum[i-1]+a[i];
		for(int i = 1;i <= n;i++)
		{
			dp[i][0] = 1e18;//非法情况
			for(int j = 1;j <= m;j++)
			{
				int l = find(sum[i]-b[j]);//二分查找到 l
				if(l >= i || sum[i]-sum[l] > b[j]) dp[i][j] = dp[i][j-1];//状态转移，上面分析过了
				else dp[i][j] = min(dp[l][j]+(m-j),dp[i][j-1]);
			}
		}
		cout << dp[n][m] << '\n';
	}
	return 0;
}
```

---

## 作者：z_yq (赞：0)

# 题意
这道题目根本就无需再次翻译了描述的很清楚了，但注意，是前缀，而且贡献答案是 $m - k$。
# 做法
显然而然的，我们看见有一个 $n \times m$ 的最大范围，但是一开始并不需要往这个上面去靠。\
第一步，这个 DP 是很自然的就可以想到了，因为 $b_i$ 有单调性，所以可以想到不是 DP 就是贪心，所以这里的方法就是 DP，据班上的巨佬所说，好像可以用反悔贪心？\
第二步，记录状态，我们想到这个 $k$ 的位置比较难记录，所以我们可以记录一维度，同理，顺理成章地定义 $dp_{i,j}$ 记录已经把前面的 $i-1$ 个数字都吃掉了，现在在考虑 $i$，$k$ 的位置为 $j$ 的情况。\
第三步，状态转移，其实设计出来之后，转移是很简单的，可以想到，每一次能尽可能的往后去跳就往后去跳，所以我们记录 $i$ 后面第一个 $x$ 满足 $s_x - s_{i-1} \leq b_j$，$s_i$ 记录的是前缀和，这个东西每一次可以二分出来，然后转移方程就是 $dp_{x,j} = \min(dp_{x,j},dp_{i,j}+m-j)$ 注意，在末尾的时候还有 $dp_{i,j+1} = dp_{i,j}$ 剩下的很多细节就见代码了。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define Inf 0x3f3f3f3f
using namespace std;
const ll N=3e5+9;
ll n,m,a[N],b[N],s[N];
vector<vector<ll>>dp;
inline void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
    dp.clear();
	dp.resize(m+2,vector<ll>(n+2,Inf));
	dp[1][1]=0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			int lt=j,rt=n,ans=j;
			while(lt<=rt)
			{
				int mid=lt+rt>>1;
				if(s[mid]-s[j-1]>b[i])rt=mid-1;
				else lt=mid+1,ans=mid+1;
			}
			if(a[j]<=b[i])dp[i][ans]=min(dp[i][ans],dp[i][j]+m-i);
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
		}
	ll ans=INT_MAX;
	for(int i=1;i<=m;i++)
		ans=min(ans,dp[i][n+1]);
	if(ans>n*m)cout<<"-1\n";
	else cout<<ans<<endl;
}
int main()
{
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```
# 总结
这是一个很好的题目，做完以后受益匪浅，从一开始到结束的 DP 设计都很巧妙，就算不能算上巧妙，也能积累一种题型，在复习，学习新知时，都是一个很好的选择。

---

## 作者：limingyuan333 (赞：0)

# The Endspeaker (Easy Version)
## 题意：
给出长为 $n$ 的数组 $a$，长为 $m$ 的数组 $b$ 和数字 $k$，$k$ 初始值为 $1$。每次可以执行以下两种操作之一：
1. 当 $k\le m$ 时，$k+1$；
2. 删除 $a$ 前缀和小于等于 $b_k$ 的部分，同时 `cost+=m-k`。

## 思路:
发现没有后效性，可以使用动态规划，首先预处理一下前缀和，定义 $dp_{i,j}$ 为删除前 $i$ 个数，当前用的 $k$ 索引为 $j$，取到的最小值即可，然后通过二分的方式找到最前的可以被用的索引，然后直接更新即可。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e5+10;
int n,m,a[MAXN],b[MAXN];
int T;
int sum[MAXN];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	while(T--){
		cin>>n>>m;int maxn=0,mx=0;
		for(int i=1;i<=n;i++)	cin>>a[i],mx=max(mx,a[i]),sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=m;i++)	cin>>b[i],maxn=max(maxn,b[i]);
		if(mx>maxn){
			cout<<-1<<'\n';continue;//当一个一个慢慢删都没办法时当然不行 
		}
		vector<vector<int> >dp(n+1,vector<int>(m+1,LONG_LONG_MAX));
		for(int i=1;i<=m;i++)	dp[0][i]=0; 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(b[j]<a[i])	break;//一个都不符合直接跳 
				int num=0,l=1,r=i;
				while(l<=r){
					int mid=l+r>>1;
					if(sum[i]-sum[mid-1]<=b[j])	r=mid-1,num=mid;//最左的符合要求的 
					else	l=mid+1;
				}
				dp[i][j]=min(dp[i][j],dp[num-1][j]+m-j);//更新 
			}
			for(int j=1;j<=m;j++)	dp[i][j]=min(dp[i][j-1],dp[i][j]);//与前面作比较 
		}
		int ans=LONG_LONG_MAX;
		for(int i=1;i<=m;i++)	ans=min(ans,dp[n][i]);//最小值 
		cout<<ans<<'\n'; 
	}
	return 0;
} 
```

---

## 作者：I_will_AKIOI (赞：0)

首先很容易想到 dp，设状态 $f_{i,j}$ 表示已经删了 $i-1$ 个元素（也就是从第 $i$ 个元素开始删），$k=j$ 需要花费的最小值。转移则根据两种操作分类，这里先考虑操作二。

+ 操作二：发现 $f_{i,j}$ 可以从 $f_{k,j},k\in[1,j-1]\land \sum_{p=k}^{i-1} a_p\le b_j$ 转移而来，所以从 $i-1$ 开始，大到小枚举 $k$，在此过程中记录一下 $sum$ 并转移。

+ 操作一：就是把 $k$ 一直增大，也就是 $f_{i,j}=\min_{k=1}^{j-1} f_{i,k}$。

然后发现操作二的 $sum$ 只增不降，存在单调性，因此可以二分 + 前缀和求出 $k$ 的最大值，这样操作二的转移方程就变成了 $f_{i,j}=\min_{p=k}^{i-1} f_{p,j}$，然后发现这个式子又可以线段树优化，于是上一个单点修改，区间查询最小值的线段树就行，注意由于 $n,m$ 的值不固定，所以数组只能开 vector。

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize("O3")
using namespace std;
struct Data{int l,r,minn;};
int n,m,ans;
void build(vector<Data>&t,int k,int l,int r)
{
	t[k].l=l,t[k].r=r;
	if(l==r)
	{
		t[k].minn=1e18;
		return;
	}
	int mid=l+r>>1;
	build(t,k*2,l,mid),build(t,k*2+1,mid+1,r);
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	return;
}
void update(vector<Data>&t,int k,int l,int x)
{
	if(t[k].l==l&&t[k].r==l)
	{
		t[k].minn=x;
		return;
	}
	int mid=t[k].l+t[k].r>>1;
	if(l<=mid) update(t,k*2,l,x);
	if(l>mid) update(t,k*2+1,l,x);
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	return;
}
int query(vector<Data>&t,int k,int l,int r)
{
	if(l<=t[k].l&&t[k].r<=r) return t[k].minn;
	int mid=t[k].l+t[k].r>>1,res=1e18;
	if(l<=mid) res=min(res,query(t,k*2,l,r));
	if(r>mid) res=min(res,query(t,k*2+1,l,r));
	return res;
}
//单修区查线段树代码
void solve()
{
	cin>>n>>m;
	vector<int>a(n+5,0),b(m+5,0),sum(n+5,0);
	vector<vector<int> >f(n+5);
	vector<vector<Data> >t(m+5);
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];//预处理前缀和
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=0;i<=n+4;i++) f[i].resize(m+5,1e18);
	for(int i=1;i<=m;i++) t[i].resize(n*4+10),build(t[i],1,1,n+1);
	f[1][1]=0;
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int l=1,r=i,mid,k=-1;
			while(l<r)//二分出k
			{
				mid=l+r>>1;
				if(sum[i-1]-sum[mid-1]<=b[j]) r=k=mid;
				else l=mid+1;
			}
			if(k!=-1) f[i][j]=query(t[j],1,k,i-1)+m-j;//操作2的转移方程
		}
		int minn=1e18;
		for(int j=1;j<=m;j++) minn=min(minn,f[i][j]),f[i][j]=min(f[i][j],minn),update(t[j],1,i,f[i][j]);//操作1的转移
	}
	ans=1e18;
	for(int i=1;i<=m;i++) ans=min(ans,f[n+1][i]);//答案是对所有最终情况求min
	if(ans==1e18) cout<<-1<<"\n";
	else cout<<ans<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

提供一个不太一样的转移。

## [The Endspeaker (Easy Version)](https://codeforces.com/contest/2027/problem/D1)

将 $a$ 分成若干段，每段有限制，考虑以段为阶段性的体现来 dp，显然只有两个变量：$a$ 选到哪和 $b$ 选到哪，而 $nm\le 3\cdot 10^5$ 印证了我们的想法，于是设 $f(i,j)$ 为 $a$ 选到 $i$，$b$ 选到 $j$ 时最小花费。记 $s_x=\sum_{i=1}^{x} a_i$，根据定义显然有转移
$$
f(i,j)=\min_{s_i-s_k\le b_j} \min_{h\le j} f(k,h)+m-j
$$
**贪心地，$k$ 越小越好**。$k$ 越大，对于当前状态没有影响，却会使上一个状态的和更大，于是不优。求 $k$ 是容易的，那么方程只剩下一个 $\min$ 需要处理，注意到 $h\le j$，记录前缀 $\min$ 即可，时间复杂度 $O(nm)$ 或 $O(nm\log n)$。

---

