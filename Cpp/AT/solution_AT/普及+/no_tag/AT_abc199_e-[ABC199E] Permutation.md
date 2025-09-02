# [ABC199E] Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc199/tasks/abc199_e

$ (1,\ 2,\ 3,\ \dots,\ N) $ を並び替えてできる数列 $ a $ であって、以下の条件を満たすものの数を出力してください。

- $ 1\ \le\ i\ \le\ M $ を満たす全ての整数 $ i $ について、$ a_1,\ a_2,\ a_3,\ \dots,\ a_{X_i} $ の中に $ Y_i $ 以下の数は $ Z_i $ 個以下しか存在しない

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 18 $
- $ 0\ \le\ M\ \le\ 100 $
- $ 1\ \le\ X_i\ \lt\ N $
- $ 1\ \le\ Y_i\ \lt\ N $
- $ 0\ \le\ Z_i\ \lt\ N $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

条件を満たす $ a $ は以下の $ 4 $ つです。 - $ (1,\ 3,\ 2) $ - $ (2,\ 3,\ 1) $ - $ (3,\ 1,\ 2) $ - $ (3,\ 2,\ 1) $ $ (1,\ 2,\ 3) $ や $ (2,\ 1,\ 3) $ は、$ a_1,\ a_2 $ の中に $ 2 $ 以下の数が $ 2 $ つあるため条件を満たしません。

## 样例 #1

### 输入

```
3 1
2 2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2
3 3 2
4 4 3```

### 输出

```
90```

## 样例 #3

### 输入

```
18 0```

### 输出

```
6402373705728000```

# 题解

## 作者：lfxxx (赞：4)

考虑状压。

设计状态 $dp_{i,j}$ 表示考虑 $i$ 个数，每个数的使用情况的二进制压缩表示为 $j$ 的情况下的方案数。

然后去正常转移。

唯一特殊的是将限制放在点上，假若这个点转移时不满足限制直接让其的方案数为 $0$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 20;
const int maxv = 1e6+114;
int dp[maxn][maxv];
int n,m;
vector< pair<int,int> >imp[maxn];
void check(int i,int j){//假若状态不合法直接 pass
	for(pair<int,int> now:imp[i+1]){
		int cnt=0;
		for(int pos=0;pos<n;pos++){
			if(j&(1<<pos)){
				if((pos+1)<=now.first) cnt++;
			}
		}
		if(cnt>now.second){
			dp[i][j]=0;	
		} 
	}
} 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		imp[x].push_back(make_pair(y,z));
	}	
	for(int i=0;i<n;i++) dp[0][1<<i]=1,check(0,1<<i);
	for(int i=1;i<n;i++){
		for(int j=0;j<(1<<n);j++){
			for(int k=0;k<n;k++){
				if(j&(1<<k)){
					dp[i][j]+=dp[i-1][j^(1<<k)];
				}
			} 
			check(i,j);
		}
	}
	cout<<dp[n-1][(1<<n)-1];
}
```


---

## 作者：Light_Star_RPmax_AFO (赞：1)

## 前言

为了纪念长沙市一中第二次思维训练。

[传送门](https://www.luogu.com.cn/problem/AT_abc199_e)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-at-abc199-e)


### 题目翻译

给出一个数 $N$，和一个制约条件个数 $M$，接下来给出 $M$ 个制约条件 $X_i,Y_i,Z_i$，要求为在 $N$ 中选 $N$ 个数，要满足选的前 $X_i$ 个数中，小于 $Y_i$，的数不高于 $Z_i$ 个，求总共有多少种方案。

思路——状压 dp。

一看数据范围 $N \le 18$ 就可以想到**状压 dp**。

以 $i$ 为状态，状态转移方程如下。

$$\left\{\begin{matrix}
f_0=0
\\f_i=\sum[i \mathop{\mathrm{and}} (1 \mathop{\mathrm{lsh}} (j - 1))]{f_j} 
\end{matrix}\right.
$$

### 判断

如何判断 $i$ 无法满足条件呢？

我们使用 $\operatorname{sum}$ 记录一个数在 **二进制** 下的 $1$ 的个数。

如果 $sum(i\mathop{\mathrm{and}} (1 \mathop{\mathrm{lsh}} y_j)-1)\ge z_j$ 就跳过。

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,m,x[101],y[101],z[101];
int f[1 << 19];

int sum(int x){
	int sums=0;
	while(x){
		++sums;
		x &= (x - 1); 
	}
	return sums;
}

signed main(){
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d", x+i, y+i, z+i);
	}
	f[0] = 1;
	for(int i = 0;i < (1 << n);i++){
		bool can=0;
		for(int j = 1;j <= m;j++){
			if(sum(i) <= x[j] && sum(i & ((1 << y[j]) - 1)) > z[j]){
				can = 1;
				break; 
			}
		}
		if(can)
			continue;
		for(int j = 1;j <= n;j++){
			if(i & (1 << (j - 1))){
				f[i] += f[i ^ (1 << (j - 1))];
			}
		}
	}
	cout<<f[(1 << n) - 1];
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

首先考虑没有限制的情况怎么做。

因为有 $ N \leq 18 $，不难想到状压。

设 $ dp_0=1,dp_{i}=\sum{dp_j}(j \subseteq i,\left| i \setminus j \right|=1) $，代表初始状态，表示没有限制的情况。

然后在转移的时候，每次枚举下一位要填的数，检查是否满足限制条件，如果满足条件类似上面的方程转移即可，否则不合法，不累计答案。

这样总时间复杂度 $ \mathcal{O}(2^n \times n) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int x[105],y[105],z[105];
bitset<2000020>vis;
int f[1<<20];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	cin>>x[i]>>y[i]>>z[i];
	for(int i=1;i<1<<n;i++)
		for(int j=1;j<=m;j++)
			if(__builtin_popcountll(i)<=x[j] and __builtin_popcountll(i&((1<<y[j])-1))>z[j])
				vis[i]=1;
	f[0]=1;
	for(int i=1;i<1<<n;i++)
	{
		if(vis[i])
		continue;
		for(int j=1;j<=n;j++)
			if(i&(1<<j-1))
				f[i]+=f[i-(1<<j-1)];
	}
	cout<<f[(1<<n)-1];
}
```


---

## 作者：Soh_paramEEMS (赞：0)

## 题意
有 $n$ 个学生，学号 $1$ 至 $n$。你现在需要把这 $n$ 个学生从左往右排成一行形成队伍，要满足如下所有 $m$ 个条件：

第 $i$ 个条件的格式是 $x,y,z$，表示队伍的前 $x$ 学生当中，学号小于等于 $y$ 的学生不能超过 $z$ 人。

求满足上面所有 $m$ 个条件的队伍有多少种不同的方案。

$2\le n\le 18,\ 1\le m\le 100$

## 思路
看到 $n$ 很小，想到状压 dp。

定义队伍状态 $s$，每一位表示第 $i$ 位学号是否有人。

一个队伍满足所有条件怎么判断，其实时间复杂度已经不成问题。

定义条件数组 $a_{x,y}$ 表示前 $x$ 人，学号小于等于 $y$ 的，最多有多少人，那么每个条件的输入，都有：$$a_{x,y}=\min{z}$$。

一个队伍状态 $s$ 中学生个数就是 $popcnt(s)$ ，表示 $s$ 二进制 $1$ 的个数。

那么只需要 $\Theta(n)$ 扫过去，枚举 $n$ 个学号，$i\in [1,n]$ 看看是否恒有学生个数 $tot\le a_{stu,i}$ 即可。

如果恒有说明是一个可行的状态。

将子集状态并起来相加，就可以算出总贡献了！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=21,inf=0x7f7f7f7f;
ll n,m,a[N][N];//a(x,y):前x人学号在[1,y]最多人数 
ll f[1<<N];
ll popcnt(ll x)
{
	ll ret=0;
	while(x)
	{
		if(x&1)ret++;
		x>>=1;
	}
	return ret;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	memset(a,inf,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		ll x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		a[x][y]=min(a[x][y],z);
	}
	f[0]=1;
	for(int s=0;s<(1<<N);s++)
	{
		ll stu=popcnt(s),tot=0;
		bool flag=1;
		for(int i=1;i<=n;i++)//学号 
		{
			if(s&(1<<(i-1)))tot++;
			if(tot>a[stu][i]){flag=0;break;}
		}
		if(!flag)continue;//非法 
		for(int i=1;i<=n;i++)
		{
			ll sj=(1<<(i-1));
			if(s&sj)f[s]+=f[s^sj];
		}
	}
	printf("%lld",f[(1<<n)-1]);
	return 0;
}
```

---

## 作者：Zirnc (赞：0)

[BLOG](https://blog.chungzh.cn)

[ ABC199E Permutation](https://www.luogu.com.cn/problem/AT_abc199_e)

观察到 $N \le 18$，考虑状压 DP。$O(2^n \times n)$。

设 $f(S)$ 表示 $S$ 的方案数，其中 $S$ 二进制数的某一位为 $1$ 则表示选了这个数，为 $0$ 则表示还没选。转移时枚举每一位，如果为 $1$，就可以加上仅将这位改为 $0$ 的方案数。

在这一过程中，可以通过 `__builtin_popcount` 求出当前状态的 $1$ 的个数，就可以知道已经选了几个数。然后用 `check` 检验一下是否符合规则即可。

记得 $f(0)=1$，开 long long。

记忆化搜索（65ms）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
bool vis[1<<18];
long long f[1<<18];
struct rule {
	int y, z;
};
vector<rule> v[20];
bool check(int S) {
	int pct = __builtin_popcount(S);
	for (int i = 0; i < v[pct].size(); i++) {
		int cnt = 0;
		for (int j = 1; j <= n; j++)
			if (S&(1<<(j-1)))
				if (j <= v[pct][i].y) cnt++;
		if (cnt > v[pct][i].z) return false;
	}
	return true;
}
long long dfs(int S) {
	if (vis[S]) return f[S];
	vis[S] = 1;
	if (!check(S)) return f[S] = 0;
	
	for (int i = 1; i <= n; i++)
		if (S&(1<<(i-1)))
			f[S] += dfs(S^(1<<(i-1)));
			
	return f[S];
}
int main()
{
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		v[x].push_back({y, z});
	}
	
	f[0] = 1;
	vis[0] = 1;
	cout << dfs((1<<n)-1) << endl;
	return 0;
}
```

递推写法（93ms）：

```cpp
	f[0] = 1;
	for (int i = 1; i < (1<<n); i++) {
		if (!check(i)) continue;
		for (int j = 1; j <= n; j++)
			if (i&(1<<(j-1)))
				f[i] += f[i^(1<<(j-1))];
	}
	cout << f[(1<<n)-1] << endl;
```

---

