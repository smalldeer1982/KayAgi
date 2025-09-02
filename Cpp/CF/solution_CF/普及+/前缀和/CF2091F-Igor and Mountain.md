# Igor and Mountain

## 题目描述

IT Campus "NEIMARK" 的访客不仅是优秀的程序员，更是体魄强健的运动爱好者！有人练习游泳，有人划船，还有人进行攀岩！

Igor 大师是当地攀岩界的知名人物。某天，他前往山区攀登一座山峰。作为经验丰富的攀岩者，Igor 决定不沿既有路线，而是利用自己的技巧严格垂直攀登。

Igor 找到了一块垂直的矩形山体区域，并将其在脑海中划分为 $n$ 个水平层。随后他将每层用垂直隔板分割为 $m$ 个区段。观察这些区段时，Igor 发现了可供抓握的凸起（以下称为支点）。因此，所选山体区域可表示为 $n \times m$ 的矩形，其中某些单元格包含支点。

作为资深程序员，Igor 决定计算有效路线的数量。路线被定义为由不同支点组成的序列。当满足以下条件时，路线被视为有效：

- 路线中第一个支点位于最底层（第 $n$ 行）；
- 路线中最后一个支点位于最顶层（第 $1$ 行）；
- 每个后续支点不低于前一个支点；
- 每层（即矩形的每一行）至少使用一个支点；
- 每层最多使用两个支点（因 Igor 只有双手）；
- 当相邻支点对应区段中心点的欧氏距离不超过 Igor 的臂展时，才能从当前支点移动到下一个支点。

Igor 的臂展为 $d$，这意味着当两个支点对应区段中心点的欧氏距离不超过 $d$ 时可进行移动。区段 $(i_1, j_1)$ 与 $(i_2, j_2)$ 之间的距离计算公式为 $\sqrt{(i_1 - i_2)^2 + (j_1 - j_2)^2}$。

请计算不同有效路线的数量。若两条路线使用的支点列表或访问顺序不同，则视为不同的路线。

## 说明/提示

第一个样例中的可能路线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/e87023b4f4a219144271b82b78cb035704abe051.png)  
第二个样例中 Igor 的臂展增大，因此新路线可用，例如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/af93e08d9fa412dbf0403f4084f2c8743d449017.png)  
第三个样例中底层没有支点，因此不存在有效路线。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3 4 1
XX#X
#XX#
#X#X
3 4 2
XX#X
#XX#
#X#X
3 1 3
X
X
#```

### 输出

```
2
60
0```

# 题解

## 作者：wangyizhi (赞：5)

**题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF2091F) || [CodeForces](https://codeforces.com/contest/2091/problem/F)**

提供一种和官解稍微不同一点的做法。

## 题目分析

考虑 DP。记 $f_{i,j}$ 表示当前在 $(i,j)$ **且在第 $i$ 层已经走完**的方案数。

在第 $n$ 层的方案数显然。考虑如何转移。

先假设只走 $1$ 次。则可以从这一格下面一层左右 $\lfloor\sqrt{d^2-1}\rfloor=d-1$ 格走过来。故此时有 

$$$f_{i,j}=\sum_{k=j-(d-1)}^{j+(d-1)}f_{i+1,k}$$$

考虑走两次的情况。方便起见，记只走一次的方案数为 $f'_{i,j}$。此时有

$$$f_{i,j}=\left(\sum_{k=j-d}^{j+d}f'_{i,k}\right)-f'_{i,j}$$$

首先，两个式子都可以用前后缀优化。其次，注意到我们不需要开两个数组。对每一行，我们先用第一个式子跑一遍，然后记录前缀和；再借助前缀和直接跑第二个式子，由于我们的 dp 状态是这一层走了 $1$ 个或 $2$ 个，因此最后也不需要减去只走 $1$ 个格子的方案数了。最后在前缀和一遍就行了。

## AC Code

记得多测要清空啊！！！

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
//bool Mst;
const int N=2e3+5,mod=998244353;
int to[N][N],dp[N][N],pre[N][N];
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,m,d,dd;
		cin>>n>>m>>d,dd=d-1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				char ch;
				cin>>ch;
				if(ch=='X') to[i][j]=1;
				else to[i][j]=0;
			}
		auto s=[&](int c,int l,int r)
		{
			l=max(l,1),r=min(r,m);
			return (pre[c][r]+mod-pre[c][l-1])%mod;
		};
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[i][j]=0;
		for(int i=1;i<=m;i++) if(to[n][i]) dp[n][i]=1;
		for(int i=1;i<=m;i++) pre[n][i]=(pre[n][i-1]+dp[n][i])%mod;
		for(int i=1;i<=m;i++) if(to[n][i]) dp[n][i]=s(n,i-d,i+d);
		for(int i=1;i<=m;i++) pre[n][i]=(pre[n][i-1]+dp[n][i])%mod;
		for(int i=n-1;i>=1;i--)
		{
			for(int j=1;j<=m;j++) if(to[i][j]) dp[i][j]=s(i+1,j-dd,j+dd);
			for(int j=1;j<=m;j++) pre[i][j]=(pre[i][j-1]+dp[i][j])%mod;
			for(int j=1;j<=m;j++) if(to[i][j]) dp[i][j]=s(i,j-d,j+d);
			for(int j=1;j<=m;j++) pre[i][j]=(pre[i][j-1]+dp[i][j])%mod;
		}
		cout<<s(1,1,m)<<"\n";
	}
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：4)

## 题解：CF2091F Igor and Mountain

### 解题思路

考虑 DP。

定义数组 $u_{i , j}$ 为从上一层到这一层有多少能够到达终点的路径；$p_{i , j}$ 为在这一层上横向攀爬一次后能到达终点的路径的数量。

则有：

$$u_{i , j} = \sum_{k = \max(j - d + 1 , 1)}^{\min(j + d - 1 , m)} p_{i - 1 , k}$$
$$p_{i , j} = \sum_{k = \max(j - d , 1)}^{\min(j + d , m)} u_{i , k}$$

因为在不同层，能够够到的点是**臂展长度 $- 1$**，而在相同层，能够够到的点是**臂展长度**。

而在相同层不经过跳跃直接往上爬的方案，为了使代码实现更简单，我们可以假定是**在原地爬了一下**。

每个点的统计可以**用前缀和快速统计**。

时间复杂度：$O(n , m)$。

**注意：取模有很多细节要注意，作者在赛时因为取模问题错了两发。**

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
const long long mod = 998244353;
long long t , n , m , d , u[2005][2005] , p[2005][2005] , qzhu[2005][2005] , qzhp[2005][2005];
char mp[2005][2005];
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> m >> d;
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= m ; j++)
			{
				cin >> mp[i][j];
			}
		}
		for(int i = 0 ; i <= n ; i++)
		{
			for(int j = 0 ; j <= m + 1 ; j++)
			{
				u[i][j] = p[i][j] = qzhu[i][j] = qzhp[i][j] = 0;
			}
		}
		for(int j = 1 ; j <= m ; j++)
		{
			if(mp[1][j] == 'X')
			{
				u[1][j] = 1;
			}
		}
		for(int j = 1 ; j <= m ; j++)
		{
			qzhu[1][j] = (qzhu[1][j - 1] + u[1][j] + mod) % mod;
		}
		for(int j = 1 ; j <= m ; j++)
		{
			if(mp[1][j] == 'X')
			{
				p[1][j] = (qzhu[1][min(j + d , m)] - qzhu[1][max(j - d - 1 , 0ll)] + mod) % mod; 
			}
		}
		for(int j = 1 ; j <= m ; j++)
		{
			qzhp[1][j] = (qzhp[1][j - 1] + p[1][j] + mod) % mod;
		}
		for(int i = 2 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= m ; j++)
			{
				if(mp[i][j] == 'X')
				{
					u[i][j] = (qzhp[i - 1][min(j + d - 1 , m)] - qzhp[i - 1][max(j - d , 0ll)] + mod) % mod;
				}
			}
			for(int j = 1 ; j <= m ; j++)
			{
				qzhu[i][j] = (qzhu[i][j - 1] + u[i][j] + mod) % mod;
			}
			for(int j = 1 ; j <= m ; j++)
			{
				if(mp[i][j] == 'X')
				{
					p[i][j] = (qzhu[i][min(j + d , m)] - qzhu[i][max(j - d - 1 , 0ll)] + mod) % mod; 
				}
			}
			for(int j = 1 ; j <= m ; j++)
			{
				qzhp[i][j] = (qzhp[i][j - 1] + p[i][j] + mod) % mod;
			}
		}
		cout << qzhp[n][m] << '\n';
	}
	return 0;
}
```

---

## 作者：caizihan925 (赞：3)

## Igor and Mountain 题解

[题目传送门](https://www.luogu.com.cn/problem/CF2091F)

### 题目描述

有一个 $N \cdot M$ 的且只包含字符 `#` 和 `X` 的字符矩阵，还有一个给定的数组 $d$，求从下到上，只经过 `X` 且满足一下限制的方案数量。

- $1 \leq$ 第 $i$ 行经过的 `X` 的数量 $\leq 2 \ (1\leq i \leq n)$
- 每一个经过的 `X` 需要与同行、上一行、下一行经过的 `X` 的欧氏距离不超过 $d$。

### 思路

考虑一种状态：

$dp_{i,j,0/1}$ 表示走到格子 $(i,j)$；第 $i$ 层经过了 $1$ 个格子 $/$ 第 $i$ 层经过了**至多** $2$ 个格子。

为什么是至多 $2$ 个格子呢？请看转移。

$dp_{i,j,1} = \sum_{k=j-d}^{j+d}dp_{i,k,0}$

此时就可以解释刚刚的问题了，因为 $dp_{i,k,0}$ 中包含了 $dp_{i,j,0}$，而 $dp_{i,j,0}$ 的定义是：第 $i$ 层经过了 $1$ 个格子。

所有 $dp_{i,j,1}$ 表示：第 $i$ 层经过了**至多** $2$ 个格子。

接下来是另一个转移：

先设 $d2 = \lfloor \sqrt{d^2-1} \rfloor$

$dp_{i,j,0} = \sum_{k=j-d2}^{j+d2}dp_{i-1,k,1}$

观察这两个求和符号，可以发现它们可以通过前缀和优化。因此，每次完成一层的 $dp$ 计算后，可以对其进行前缀和处理，就不会超时了。

### 细节

注意：在计算前缀和时，下标可能会越界，因此需要对下标进行边界检查。

### 时间复杂度

$O(T \cdot N \cdot M)$

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, M = 998244353;

int n, m, d, ans, fa[N], dp[N][N][2];

char a[N][N];

void Solve(){
	cin >> n >> m >> d;
    int tmp = sqrt(d * d - 1);
	for(int i = n; i; i--){
		for(int j = 1; j <= m; j++){
			cin >> a[n - i + 1][j];
		}
	}
	for(int i = 1; i <= m; i++){
		dp[1][i][0] = (a[1][i] == 'X');
		fa[i] = (fa[i - 1] + dp[1][i][0]) % M;
	}
	for(int i = 1; i <= m; i++){
		dp[1][i][1] = (a[1][i] == 'X') * (fa[min(m, i + d)] - fa[max(0, i - d - 1)] + M) % M;
	}
	for(int i = 1; i <= m; i++){
		fa[i] = (fa[i - 1] + dp[1][i][1]) % M;
	}
	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j] != 'X'){
				continue;
			}
			dp[i][j][0] = (fa[min(m, j + tmp)] - fa[max(0, j - tmp - 1)] + M) % M;
		}
		for(int j = 1; j <= m; j++){
			fa[j] = (fa[j - 1] + dp[i][j][0]) % M;
		}
		for(int j = 1; j <= m; j++){
			if(a[i][j] != 'X'){
				continue;
			}
			dp[i][j][1] = (fa[min(m, j + d)] - fa[max(0, j - d - 1)] + M) % M;
		}
		for(int j = 1; j <= m; j++){
			fa[j] = (fa[j - 1] + dp[i][j][1]) % M; 
		}
	}
	for(int i = 1; i <= m; i++){
		ans = (ans + dp[n][i][1]) % M;
	}
	cout << ans << '\n';
    ans = 0;
    fill(fa + 1, fa + n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			dp[i][j][0] = dp[i][j][1] = 0;
		}
	}
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
    int T;
	cin >> T;
	while(T--){
		Solve();
	}
	return 0;
}
```

---

## 作者：Maureen0124 (赞：3)

多测一定要清空，否则连样例都过不了。

一定要把答案取模到正数，否则你会收获 `Wrong answer on test 8`。

~~你猜我是怎么知道的~~。
## 思路
题目要求从山脚（即最后一行），一行一行往上爬，每一行最少用一个支点，最多用两个支点，直到山顶（即第一行）有多少条路线。

这种题应该首先考虑 dp。

容易发现从山脚到山顶和从山顶到山脚没有任何区别，所以可以得到状态 $dp[i][j]$ 表示从山顶到 $(i,j)$ 的路线数量，其中包括行内使用两个支点的路线。

再来想转移。每个点有两种转移方式：

1.  从上一行转移过来。
2.  从同一行转移过来。

考虑到第 2 个操作种转移过来的那个点肯定是从上一行转移下来的，所以对于每一行，先计算该行所有点进行操作 1 后的 dp 值，再计算该行所有点进行操作 2 后的 dp 值。

假设当前位置是 $(i, j)$，那么可以由上一行 $(i - 1, j - (d - 1))$ 到 $(i - 1, j + (d - 1))$ 转移过来。为什么是 $j \pm (d - 1)$，因为 $\lfloor \sqrt{d^2  - 1}\rfloor = d - 1$，可以用下图理解：![](https://cdn.luogu.com.cn/upload/image_hosting/e3jds5la.png)

令 $l = j - (d - 1), r = j + (d - 1)$，有 $dp[i][j] = \sum _ {k = l} ^ {r} dp[i - 1][k]$。如果便利一遍求值的话总时间复杂度会到 $O(nm^2)$，考虑前缀和优化。令 $pre[j]$ 表示第 $i - 1$ 行的 $dp$ 前缀和。

所以有 $dp[i][j] = pre[r] - pre[l - 1]$。

再看第 2 个操作。令 $l = j - d, r = j + d$，有 $dp[i][j] = dp[i][j] + \sum _ {k = l} ^ {r} dp[i][k]$。同理需要前缀和优化。又因为这里的前缀和和上一次使用的前缀和并不会重叠或有冲突，所以可以继续使用数组 $pre[]$，降低空间复杂度。

所以有 $dp[i][j] = dp[i][j] + pre[r] - pre[l - 1]$。

最后输出 $pre[m]$ 即可。

注意需要提前初始化 $dp[1][]$ 和 $pre[]$，因为它们的求法和其它行有稍许不同。

## 代码
~~我自认为写得还是很漂亮的~~。

```cpp
int n, m, d, dp[N][N], pre[N];
vector<int> G[N];

void solve(){
    cin >> n >> m >> d;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            char c; cin >> c;
            if(c == 'X') G[i].push_back(j);
        }
    for(int x : G[1]){
        dp[1][x] = 1;
        auto l = lower_bound(G[1].begin(), G[1].end(), x - d) - G[1].begin();
        auto r = upper_bound(G[1].begin(), G[1].end(), x + d) - G[1].begin();
        (dp[1][x] += r - l - 1) %= MOD;
    }
    for(int i = 1; i <= m; i++) pre[i] = (pre[i - 1] + dp[1][i]) % MOD;
    for(int i = 2; i <= n; i++){
        for(int x : G[i]){
            int l = max(0ll, x - d + 1), r = min(m, x + d - 1);
            (dp[i][x] = pre[r] - pre[l - 1]) %= MOD;
        }
        for(int j = 1; j <= m; j++) pre[j] = (pre[j - 1] + dp[i][j]) % MOD;
        for(int x : G[i]){
            int l = max(0ll, x - d), r = min(m, x + d);
            (dp[i][x] += pre[r] - pre[l - 1] - dp[i][x]) %= MOD;
        }
        for(int j = 1; j <= m; j++) pre[j] = (pre[j - 1] + dp[i][j]) % MOD;
    }
    printf("%lld\n", (pre[m] % MOD + MOD) % MOD);
    memset(dp, 0, sizeof dp);
    for(int i = 1; i <= n; i++) G[i].clear();
}
```

---

## 作者：Exscallop64_ (赞：2)

## 题目简述

给定一个 $n \times m$ 的字符矩阵，$a_{i,j}$ 为第 $i$ 行第 $j$ 列的格子上的记号，为 `X` 或 `#`。

一条有效线称为：

+ 起点在第 $n$ 行且为 `X`，终点在第 $1$ 行且为 `X`。

+ 每行至少停留一个 `X`，至多停留两个 `X`。

+ 对于当前所在的格子，下一个停留的格子必须为 `X` 且所在行小于等于当前格子的行且两个格子之间的欧几里得距离不得超过 $d$。

求有效路径的数量，取模 $998244353$。

## 思路

容易想出暴力 DP，同时令 $dist(x1,y1,x2,y2) = \sqrt{(x1-x2)^2+(y1-y2)^2}$。

令 $dp_{i,j,x}$ 表示最后所在格子 $(i,j)$ 至多经过 $x$ 个格子时的方案数。

则 $dp_{i,j,1} = \sum dp_{i-1,k,2}$，其中 $1 \le k \le m$ 且 $dist(i,j,i-1,k) \le d$。

观察 $dist(i,j,i-1,k) = \sqrt{(i-(i-1))^2+(j-k)^2} = \sqrt{1+(j-k)^2}$。

也就是说，$\sqrt{1+(j-k)^2} \le d$，即 $1+(j-k)^2 \le d^2$，再转换一下 $\vert j-k \vert \le \lfloor \sqrt{d^2-1} \rfloor$。

因此令 $D =  \lfloor \sqrt{d^2-1} \rfloor$，则 $\max(j-D,1) \le k \le \min(j + D,m)$，可以前缀和优化。

$dp_{i,j,2}$ 同理，$dp_{i,j,2} = \sum dp_{i,k,2}$ 其中 $1 \le k \le m$ 且 $dist(i,j,i,k) \le d$。

拆开 $dist(i,j,i,k)$，即 $\vert j - k \vert \le d$，则 $\max(j - d, 1) \le k \le \min(j+d,m)$，也可以前缀和优化。

## 复杂度分析

+ 时间复杂度：$T$ 组数据 $O(\sum nm)$。

+ 空间复杂度：$O(nm)$。

代码中将第三维压掉了。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e3 + 5, MOD = 998244353;

int n, m, d, dp[MAXN][MAXN], pre[MAXN][MAXN];
char a[MAXN][MAXN];

void Solve(){
  cin >> n >> m >> d;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      cin >> a[i][j];
    }
  }
  for(int i = n; i >= 1; i--){
    for(int j = 1; j <= m; j++){
      if(a[i][j] == 'X'){
        if(i == n){
          dp[i][j] = 1;
        }else{
          int len = sqrtl(d * d - 1);
          int l = max(j - len, 1), r = min(j + len, m);
          dp[i][j] = (pre[i + 1][r] - pre[i + 1][l - 1] + MOD) % MOD;
        }
      }else{
        dp[i][j] = 0;
      }
      pre[i][j] = (pre[i][j - 1] + dp[i][j]) % MOD;
    }
    for(int j = 1; j <= m; j++){
      if(a[i][j] == 'X'){
        int l = max(j - d, 1), r = min(j + d, m);
        (dp[i][j] += ((pre[i][r] - pre[i][l - 1] - dp[i][j]) % MOD + MOD) % MOD) %= MOD;
      }
    }
    for(int j = 1; j <= m; j++){
      pre[i][j] = (pre[i][j - 1] + dp[i][j]) % MOD;
    }
  }
  cout << pre[1][m] << "\n";
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  for(cin >> T; T; Solve(), T--){
  }
  return 0;
}
``````

---

## 作者：yuhong056 (赞：2)

# 题解：CF2091F Igor and Mountain
提供一个很好写，空间也较小的 dp。
## dp 状态
$dp_{i, j, 0}$ 表示该行只抓一只手在 $(i, j)$ 的方案数。

$dp_{i, j, 1}$ 表示该行抓至多两只手，最后一只手在 $(i, j)$ 的方案数。
## dp 转移
当该行只抓一只手，那么他必然从下一行抓到这里。

而他的臂展为 $d$，如果还要下走一格，那么就只能向左右走 $\lfloor\sqrt{d^2 - 1}\rfloor = d - 1$ 格。

设 $td = d - 1$，最终转移为：

$$dp_{i, j, 0} = \sum\limits_{k = j - td}^{j + td}dp_{i - 1, k, 1}$$

而如果他抓至多两只手，那么必然从当前行再抓一只手在当前位置（也有可能只抓一只手在当前位置）。

因此转移为：

$$dp_{i, j, 1} = \sum\limits_{k = j - d}^{j + d}dp_{i, k, 0}$$

很明显，dp 都由一段区间转移而来。

因此可以前缀和。

而通过观察发现，当前行的 $dp_0$ 都从上一行的 $dp_1$ 转移而来，$dp_1$ 都从这一行的 $dp_0$ 转移而来，因此可以直接将前缀和降维。
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e3 + 23, MOD = 998244353;

int n, m, d;

ll dp[MAXN][MAXN][2];
char ch[MAXN][MAXN];
ll sum[MAXN];

ll calc(int l, int r) {
	return (sum[min(r, m)] - sum[max(l - 1, 0)] + MOD) % MOD;
} 

void solve(){
	cin >> n >> m >> d;
	for(int i = n; i; i--) {
		for(int j = 1; j <= m; j++) {
			cin >> ch[i][j];
			dp[i][j][0] = dp[i][j][1] = 0;
		}
	}
	int td = d - 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(ch[i][j] == 'X')dp[i][j][0] = (i == 1 ? 1 : calc(j - td, j + td));
		}
		for(int j = 1; j <= m; j++) {
			sum[j] = (sum[j - 1] + dp[i][j][0]) % MOD;
		}
		for(int j = 1; j <= m; j++) {
			if(ch[i][j] == 'X')dp[i][j][1] = calc(j - d, j + d);
		}
		for(int j = 1; j <= m; j++) {
			sum[j] = (sum[j - 1] + dp[i][j][1]) % MOD;
		}
	}
	cout << sum[m] << '\n';
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int T;
	for(cin >> T; T--; solve());
	return 0;
}
```

---

## 作者：wpl123456wpl (赞：2)

# CodeForces - 2091F

## 题意

有一个 $n \times m$ 的网格，你可以从底端任意一个的石头出发，你有一个臂长 $d$，你能攀附住任意一块与你当前石头的欧几里德距离不超过 $d$ 的石头。请问有多少条攀岩路线？方案数 $\bmod 998244353$。注意有多组数据。

$n, m, d \le 2000, t \le 1 \times 10^3$。

所有数据 $n \times m$ 的总和不超过 $4 \times 10^6$。

### 限制

- 每一行至少攀爬一块石头。
- 下一次到达的石头高度必须不矮于自己当前高度。
- 每一行攀爬最多两个石头。
- 起点必须在最低处。
- 终点必须在最高处。

### 欧几里德距离计算公式

欧几里德距离计算公式为： $\sqrt {(x1 - x2)^2 + (y1 - y2)^2}$。

## 思路

### 算法选择

- 对于当前高度要去爬第一块石头，他的结果是必须由比他矮一层爬一个与爬两个的方案数求解。

- 对于当前高度要去爬第二块石头，他的结果是必须由比他矮一层爬一个与爬两个的方案数与跟他同层但只爬了一个石头的方案数求解。

很明显，对于上述的求解前提要求，**是存在拓扑序的**，拓扑序为高度从矮到高，当前高度攀爬石头个数从小到大，可以选择使用动态规划 $DP$ 求解。

### 状态设计

首先，拓扑序高度与当前高度攀爬的石头个数设为状态，那还需要什么另需状态了？当前的高度的方案数求解跟当前高度的位置有关，需另设状态列。

状态：$(h(当前攀爬高度), pos(当前高度所处位置)，stone(当前高度攀爬石头个数), number(方案数))$。

### 转移

每次转移 **最多只能向上攀一层**，这是个常数级别攀爬。

设 $l1$ 为同层爬的最远横坐标距离，设 $l2$ 为爬一层爬的最远横坐标距离。

$l1 = d, l2 = \lfloor \sqrt {d^2 - 1^2} \rfloor$。

$DP_{h, pos, 2} = \sum_{j = \max(1, pos - l1)}^{\min(m, pos + l1)} DP_{h, j, 1}$。

$DP_{h, pos, 1} = \sum_{j = \max(1, pos - l2)}^{\min(m, pos + l2)} DP_{h-1, j, 2} + DP_{h-1, j, 2}$。

从转移中实际就可以看出对于向上爬一层的状态所有  $stone$ 是都要转移的，而同一层攀爬二块石头可以刚转移完同一层攀爬一块石头的方案数立即转移。所以 **$stone$ 这一维状态是可以省掉的**，我这只是为了方便理解。

- 对于攀爬同一层可以攀爬的范围是一段区间，**收集型可以用前缀和或线段树，扩散性可以用差分与线段树**。
- 对于攀爬高一层可以攀爬的范围也是一段区间，**收集型可以用前缀和或线段树，扩散性可以用差分与线段树**。

**因此转移是可以在规定总时间内完成的。**

## 代码展示


```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e3 + 5, mod = 998244353;

int t, n, m, d, dp[N][N][3], b[N][3];
char c[N][N];

void solve(){
  cin >> n >> m >> d;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      cin >> c[i][j];
      dp[i][j][0] = dp[i][j][1] = 0;
    }
  }
  for(int i = 1; i <= m; i++){
    if(c[n][i] == 'X'){
      dp[n][i][0] = 1;
    }
  }
  int r = 0;
  for(r; r <= m && sqrt(1ll * r * r + 1) <= d; r++){}
  r--;
  for(int i = n; i >= 1; i--){
    for(int j = 1; j <= m; j++){
      if(c[i][j] == 'X' && i != n){
        dp[i][j][0] = (b[min(j + r, m)][0] - b[max(j - r - 1, 0)][0] + mod) % mod;
        (dp[i][j][0] += (b[min(j + r, m)][1] - b[max(j - r - 1, 0)][1] + mod) % mod) %= mod;
      }
    }
    for(int j = 1; j <= m; j++){
      b[j][0] = (b[j - 1][0] + dp[i][j][0]) % mod;
    }
    for(int j = 1; j <= m; j++){
      if(c[i][j] == 'X'){
        dp[i][j][1] = ((b[min(j + d, m)][0] - b[max(j - d - 1, 0)][0] + mod) % mod - dp[i][j][0] + mod) % mod;
      }
    }
    for(int j = 1; j <= m; j++){
      b[j][1] = (b[j - 1][1] + dp[i][j][1]) % mod;
    }
  }
  cout << (b[m][0] + b[m][1]) % mod << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}

```

---

## 作者：postpone (赞：2)

用了一个相当抽象的方法，不知道有没有人和我一样。

转移是比较好想的，因为同一层最多只能选两个，我们就先不转移同层，而是在往上转移时，加上同层中其他合法的位置的答案。

设 $dp_{i, j}$ 表示 $(i, j)$ 的方案数。那么对某一不在第一行的位置 $(i, j)$，有：

$$
dp_{i-1, y} \leftarrow dp_{i-1,y} + \sum_{k = j-d}^{j+d}dp_{i, j}
$$

其中 $y\in[j-\sqrt{d^2-1},j+\sqrt{d^2-1}]$。

我们可以发现，这其实是一个区间对另一个区间的转移，那么就直接上懒标记线段树！每次转移先查询一段的和，再加给上一行的另一端就行了。

复杂度 $O(nm\log m)$，带了一个比较大的常数。

```cpp
struct Tag {
    Z add{};
    void apply(const Tag &t) {
        add += t.add;
    }
};
struct Info {
    Z sum = 0;
    i64 act = 0;
    void apply(const Tag &t) {
        sum += t.add * act;
    }
};
constexpr Info operator+(const Info &a, const Info &b) {
    return {a.sum + b.sum, a.act + b.act};
}

void solve() {
    int n, m, d;
    cin >> n >> m >> d;

    const int e = sqrt(d * d - 1);

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<vector<int>> vec(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'X') {
                vec[i].push_back(j);
            }
        }
    }
    vector dp(n, LazySegmentTree<Info, Tag>(m));
    for (int i = 0; i < n; i++) {
        for (int j : vec[i]) {
            // 能作为攀爬点的位置，区间元素个数为 1，否则为 0。
            // 最后一行的值初始设为 1，其他都是 0
            dp[i].modify(j, Info{Z(i == n - 1), 1});
        }
    }

    Z ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j : vec[i]) {
            Z tem = dp[i].rangeQuery(j - d, j + d + 1).sum;
            if (i) {
                dp[i - 1].rangeApply(j - e, j + e + 1, Tag{tem});
            } else {
                // 如果已经在第一行了，直接统计答案
                ans += tem;
            }
        }
    }
    cout << ans << "\n";
}

```

[完整代码](https://codeforces.com/contest/2091/submission/312467111)

---

## 作者：__O_v_O__ (赞：2)

看到题面，首先想到的就应该是 dp。设 $f_{i,j}$ 表示爬到 $(i,j)$ 的方案数。

我们从下往上转移。每次可以从前一行转移来，也可以从同一行转移来（因为一行可以有多个）。分别考虑：

- 若从前一行转移，我们发现，前一行中与当前点欧氏距离小于 $d$ 的点一定是一个连续的区间。$O(1)$ 处理出这个区间，使用前缀和计算即可。

- 若从同一行转移，和第一种情况一样，转移点也是连续的区间，同样使用前缀和。只不过要注意减去当前点的 $f$ 值（自己不能向自己转移）。

于是转移已经完成。考虑边界：显然，第 $n$ 行中有抓握点的位置，$f$ 值就是 $1$。最后答案就是第 $1$ 行中有抓握点的位置的 $f$ 之和。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=998244353;
int T,n,m,d,b[3001][3001],h,c[3001],an;
char a[3001][3001];
inline void qz(int b[],int x,int ha){//处理前缀和
	for(int i=1;i<=x;i++){
		if(a[ha][i]=='#')c[i]=c[i-1];
		else c[i]=(c[i-1]+b[i])%mo;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>d,an=h=0;
		while(h*h+1<=d*d)h++;h--;//处理不同行转移的范围
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)b[i][j]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)cin>>a[i][j];
		for(int i=1;i<=m;i++)
			if(a[n][i]=='X')b[n][i]=1;//边界
		for(int i=n;i>=1;i--){
			if(i<n){
				qz(b[i+1],m,i+1);
				for(int j=1;j<=m;j++){
					if(a[i][j]=='#')continue;
					int L=max(1ll,j-h),R=min(m,j+h);//处理转移区间
					b[i][j]=(b[i][j]+c[R]-c[L-1])%mo;
					b[i][j]=(b[i][j]+mo)%mo;
				}
			}
			qz(b[i],m,i);
			for(int j=1;j<=m;j++){
				if(a[i][j]=='#')continue;
				int L=max(1ll,j-d),R=min(m,j+d);
				int tp=b[i][j];//注意要先存一下，后面减去
				b[i][j]=(b[i][j]+c[R]-c[L-1])%mo;
				b[i][j]=(b[i][j]-tp+mo)%mo;
			}
		}
		for(int i=1;i<=m;i++){
			if(a[1][i]=='#')continue;
			an=(an+b[1][i])%mo;
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

记 $dp_{i,j,0}$ 为第 $i$ 层第一个点选第 $j$ 个位置的方案数，$dp_{i,j,1}$ 为第 $i$ 层第二个点选第 $j$ 个位置的方案数。

那么有

$$
dp_{i,j,0}=\begin{cases}
  0 & s_{i,j}=\texttt{\#} \\
  1 & i=n\land s_{i,j}=\texttt{X}\\
  \sum_{k=1}^m[(j-k)^2+1\le d^2]\times(dp_{i+1,k,0}+dp_{i+1,k,1}) & i<n\land s_{i,j}=\texttt{X}\\
\end{cases}\\
dp_{i,j,1}=\begin{cases}
  0 & s_{i,j}=\texttt{\#} \\
  \sum_{k=1}^m[0<|j-k|\le d]\times dp_{i,k,0} & s_{i,j}=\texttt{X} \\
\end{cases}
$$

其中中括号表示其中的式子是否成立，成立时为 $1$，否则为  $0$。

注意到求和是区间，所以可以~~线段树~~前缀和优化一下。

复杂度 $O(nm)$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,cc),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,m,d;
string s[2005];
int dp[2005][2005][2],sum[2005][2005][2];
const int mod=998244353;
void slv(){
    read3(n,m,d);
    for(int i=1;i<=n;i++)cin>>s[i],s[i]=' '+s[i];
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
            if(s[i][j]!='X')continue;
            if(i==n)dp[i][j][0]=1;
            else dp[i][j][0]=sum[i+1][min(j+d-1,m)][0]-sum[i+1][max(j-d,0ll)][0]+sum[i+1][min(j+d-1,m)][1]-sum[i+1][max(j-d,0ll)][1],dp[i][j][0]%=mod;
        }
        for(int j=1;j<=m;j++)sum[i][j][0]=sum[i][j-1][0]+dp[i][j][0],sum[i][j][0]%=mod;
        for(int j=1;j<=m;j++){
            if(s[i][j]!='X')continue;
            dp[i][j][1]=sum[i][min(j+d,m)][0]-sum[i][max(j-d-1,0ll)][0]-dp[i][j][0],dp[i][j][1]%=mod;
        }
        for(int j=1;j<=m;j++)sum[i][j][1]=sum[i][j-1][1]+dp[i][j][1],sum[i][j][1]%=mod;
    }
    int ans=0;
    cout<<((sum[1][m][0]+sum[1][m][1])%mod+mod)%mod<<endl;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dp[i][j][0]=dp[i][j][1]=sum[i][j][0]=sum[i][j][1]=0;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：Magallan_forever (赞：0)

#### 简要说明题意：

给出一张 $n \times m$ 的地图，标记为 `X` 的位置可走。要求从第 $n$ 层的任意位置走到第 $1$ 层的任意位置并满足以下条件：

1. 每层都必须经过且每层的节点只能经过至多两个。
2. 如果当前处于 $k$ 层，下一次移动后只能处于 $k$ 层或 $k-1$ 层。
3. 一次移动的**欧式距离** $x \leq d$。

求路径方案数，对 $998244353$ 取模。

#### 题目分析：

对于点 $(i,j)$，能到达的同层点为 $\{(i,y)| \max\{1,j-d\} \leq y \leq \min\{j+d,m\}\}$，能到达 $(i,j)$ 的 $i+1$ 层点应该是 $\{(i+1,y)| \max\{1,j-d+1\} \leq y \leq \min\{j+d-1,m\}\}$（因为 $\lfloor\sqrt{d^2-1}\rfloor \space = \space d-1$）。移动的过程可以动态规划，那么考虑一下状态转移方程。

令 $f(x,y)$ 为从第 $n$ 层走到 $(x,y)$ 的方案数，可以得到：

$$ f(x,y)=\sum_{i=\max\{1,y-d\}}^{\min\{y+d,m\}}\sum_{j=\max\{1,i-d+1\}}^{\min\{i+d-1,m\}}f(x+1,j) $$

看着可能很抽象，其实就是先更新从下层走到本层，再更新本层相互走的情况。

初状态是所有第 $n$ 层可走点赋为 $1$。

区间求和我用了树状数组，但其实前缀和足够了;D。时间复杂度是 $O(nm\log_2m)$，前缀和可以把 $\log_2m$ 优化掉，还可以避免调负数取模 ~~WA*2~~。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
const int mod=998244353;
int m;
bool map_[2001][2001];
long long c[2001][2001],f[2001][2001];//这里的c,f都可以滚成两个数组，即当前层和上一层
int lowbit(int v){
    return v&(-v);
}
void modify(long long* c,int x,long long v){
    for(;x<=m;x+=lowbit(x)) (c[x]+=v)%=mod;
}
long long query(long long* c,int l,int r){ //[l,r]
    long long cnt=0ll;
    for(;r;r-=lowbit(r)) cnt+=c[r],cnt%=mod;
    for(--l;l;l-=lowbit(l)) cnt-=c[l],(cnt+=mod)%=mod;
    return cnt%mod;
}
string s;
int main(){
    int T,n,d;
    long long cnt,temp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&d);
        for(int i=1;i<=n;++i){
            cin>>s,fill(c[i]+1,c[i]+1+m,0ll),fill(f[i]+1,f[i]+1+m,0ll);
            for(int j=0;j<m;++j) map_[i][j+1]=(s[j]=='X');
        }
        for(int i=1;i<=m;++i) f[n][i]=map_[n][i],modify(c[n],i,map_[n][i]);
        for(int i=1;i<=m;++i) if(map_[n][i]) f[n][i]=query(c[n],max(1,i-d),min(m,i+d))%mod;
        for(int i=1;i<=m;++i)
            if(map_[n][i]){
                temp=f[n][i]%mod-query(c[n],i,i),(temp+=mod)%=mod;
                modify(c[n],i,temp);
            }
        for(int i=n-1;i;--i){
            for(int j=1;j<=m;++j)
                if(map_[i][j]){
                    f[i][j]=query(c[i+1],max(1,j-d+1),min(m,j+d-1));
                    // printf("i=%d j=%d f[i][j]=%lld\n",i,j,f[i][j]);
                }
            for(int j=1;j<=m;++j)
                if(map_[i][j]){
                    temp=f[i][j]-query(c[i],j,j),(temp+=mod)%=mod;
                    modify(c[i],j,temp);
                }
            for(int j=1;j<=m;++j) if(map_[i][j]) f[i][j]=query(c[i],max(1,j-d),min(m,j+d));
            for(int j=1;j<=m;++j)
                if(map_[i][j]){
                    temp=f[i][j]-query(c[i],j,j),(temp+=mod)%mod;
                    modify(c[i],j,temp);
                }
        }
        cnt=0ll;
        for(int i=1;i<=m;++i) cnt+=f[1][i],cnt%=mod;
        printf("%lld\n",cnt);
        // for(int i=1;i<=n;putchar('\n'),++i) for(int j=1;j<=m;++j) printf("%lld ",f[i][j]);
    }
    return 0;
}
```

---

