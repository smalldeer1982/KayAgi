# [ABC402F] Path to Integer

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc402/tasks/abc402_f

有一个 $N$ 行 $N$ 列的网格。从上往下第 $i$ 行、从左往右第 $j$ 列的格子记作格子 $(i,j)$。每个格子上都写有 `1` 到 `9` 的数字，格子 $(i,j)$ 上写的数字是 $A_{i,j}$。

初始时，棋子位于格子 $(1,1)$。同时，设 $S$ 为空字符串，接下来进行 $2N-1$ 次操作：

1. 将当前棋子所在格子的数字追加到 $S$ 的末尾。
2. 将棋子向右或向下移动一格（第 $2N-1$ 次操作时不移动）。

$2N-1$ 次操作后，棋子将位于格子 $(N,N)$，且 $S$ 的长度为 $2N-1$。

将最终得到的字符串 $S$ 视为整数，其值对 $M$ 取模的结果即为得分。

请计算可以获得的最高得分。

## 说明/提示

### 约束条件

- $1 \leq N \leq 20$
- $2 \leq M \leq 10^9$
- $1 \leq A_{i,j} \leq 9$
- 输入中的所有数值均为整数

### 样例解释 1

棋子的移动方式有以下两种：
1. 按 $(1,1)\rightarrow(1,2)\rightarrow(2,2)$ 的顺序移动。此时 $S=$ `121`，得分为 $121 \bmod 7 = 2$。
2. 按 $(1,1)\rightarrow(2,1)\rightarrow(2,2)$ 的顺序移动。此时 $S=$ `131`，得分为 $131 \bmod 7 = 5$。

最高得分为 5，因此输出 5。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2 7
1 2
3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
3 100000
1 2 3
3 5 8
7 1 2```

### 输出

```
13712```

## 样例 #3

### 输入

```
5 402
8 1 3 8 9
8 2 4 1 8
4 1 8 5 9
6 2 1 6 7
6 6 7 7 6```

### 输出

```
384```

# 题解

## 作者：_qumingnan_ (赞：4)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc402_f)

# 正文开始

## 阅读理解

有一个 $n$ 行 $n$ 列的的矩阵，位置为 $(i,j)$ 的值为 $a_{i,j}$（$0\le a_{i,j}\le9$，$a_{i,j}\in\Z$，$0\le i,j\le n$），现在需要你从 $(1,1)$ 走到 $(n,n)$，每遇到一个点将它加入数的末尾，求 $sum \mod m$ 的最大值。 

## 思路

可以看到，$n$ 不超过 $20$，但就算如此，$O(2^{2n-1})$ 的时间复杂度还是要炸，所以暴力搜索是不可能的……吗？

既然 $O(2^{2n-1})$ 要爆炸，那为什么不砍个半呢？我们可以把整个图沿 $(1,n)$ 到 $(n,1)$ 的这条对角线切一半，于是我们就得到了两个图，在这两个图上分别搜索，再将两个图上搜到的答案进行整合，寻找到最优的解不就是了。

那现在问题就变成了如何将这两个答案进行整合。

首先，我们可以发现一个明显的性质：位置为 $(i,j)$ 的数统计答案时的贡献一定是 $a_{i,j}\times10^{\lvert 2n-i-j\rvert}$，所以我们就可以先算出来每个数最后的贡献取模后的值再进行搜索，当搜索到 $i+j=n+1$ 的地方时就说明在对角线上，于是我们将这条路径的值存在这个点上。

统计答案时，很明显需要两个图（设第一个图答案为 $x$，第二个为 $y$）的答案相加，但如果一个一个枚举，也需要花很多时间。注意到要对 $m$ 取模，那么由于 $x<m$，$y<m$，所以 $x+y<m-1$，于是我们就可以分成两种情况：

- $x+y>m$，这种情况就直接取 $y$ 的最大值就好了。
- $x+y<m$，这也需要 $y$ 尽可能大，那么就找到第一个 $x+y<m$ 的 $y$ 就好了。

于是在排序后，由于 $x$ 是单调不下降的，那么所取 $y$ 就一定是单调不上升的，于是用一个双指针就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int b[405];
int ans;
int d[25][25];
int a[25][25];
int c[3][25][1000006],cnt[25][1000006];
inline void dfs(int i,int x,int y,int s){
	if(x+y==n+1){
		if(i)s=(s+a[x][y])%m;
		c[i][x][++cnt[i][x]]=s;return ;
	}
	s=(s+a[x][y])%m;
	if(i){
		dfs(i,x-1,y,s);
		dfs(i,x,y-1,s);
	}
	else {
		dfs(i,x+1,y,s);
		dfs(i,x,y+1,s);
	}
	
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int N=2*n-1;b[1]=1;
	for(int i=2;i<=N;i++)b[i]=(b[i-1]*10)%m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>d[i][j],a[i][j]=((d[i][j]%m)*(b[N-i-j+2]%m))%m;
	dfs(0,1,1,0);//从（1，1）开始 
	dfs(1,n,n,0);//从（n，n）开始 
	for(int i=1;i<=n;i++){
		sort(c[0][i]+1,c[0][i]+cnt[0][i]+1);
		sort(c[1][i]+1,c[1][i]+cnt[1][i]+1);
	}
	for(int i=1;i<=n;i++){
		int k=cnt[1][i];
		for(int j=1;j<=cnt[0][i];j++){
			ans=max(ans,(c[0][i][j]+c[1][i][cnt[1][i]])%m);
			for(;k;k--)
				if(c[0][i][j]+c[1][i][k]<m)break;
			if(!k)continue;
			ans=max(ans,(c[0][i][j]+c[1][i][k])%m);
		}
	}
	int s=ans;
	cout<<s;
	return 0;
}
```

---

## 作者：Adam_123 (赞：4)

### 解题思路

这题乍看上去没什么思路。但是注意到数据范围刚好 $O(2^N)$ 能过，于是可以往这一方面想。

首先，我们发现走到 $(i,j)$ 这个格子时给最终数字带来的收益是 $10^{2N-i-j}$。（在他后面还要走 $2N-i-j$ 个数，它是倒数第 $2N-i-j+1$ 位数）但是，最终结果要对 $M$ 取模，所以收益跟 $10^{2N-i-j}~\text{mod}~ M$ 等价。

我们观察一下任意一条路径：每一条路径前 $N-1$ 步（即前 $N$ 个格子）是可以随便走的，而后面的就有可能被当前是否走到边界而制约。而枚举前 $N-1$ 步时间复杂度是 $O(2^N)$ 的，说明处理剩余步数时必须要很快。由于使总和最大化不是最大化后面的总和，而是通过前面已有的总和进行贪心策略。前面已有的总和种类数很多，所以易知没有比 $O(2^N)$ 更好的策略。

假设前 $N$ 个走到的格子收益为 $p$，剩下格子的收益为 $q$（$p$ 一定，$q$ 不固定），那么我们要最大化 $(p+q)~\text{mod}~M$ 的值。这就相当于让 $(p+q)~\text{mod}~M$ 尽量接近 $M$ 但不超过或等于。同时减去 $p~\text{mod}~M$，得 $q~\text{mod}~M$ 应尽量接近 $M-p~\text{mod}~M$ 但不超过或等于。  
（以上是我的感性认识）

于是，我们提前预处理出对于每一个位置的 $q$，然后枚举每一个位置和 $p$，用二分计算出该位置的最大收益，然后这样就分两段拼出来了一条经过该位置的路径。答案就是最大收益中的最大值。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 25;
int n, m, a[N][N], pow10[N], ans;
vector <int> ans1[N], ans2[N];
void dfs1(int x, int y, int sum) {
	if (x + y == n + 1) {
		ans1[x].push_back(sum); return;
	}
	dfs1(x, y + 1, (sum + a[x][y]) % m);
	dfs1(x + 1, y, (sum + a[x][y]) % m);
}
void dfs2(int x, int y, int sum) {
	if (x + y == n + 1) {
		ans2[x].push_back(sum); return;
	}
	dfs2(x, y - 1, (sum + a[x][y]) % m);
	dfs2(x - 1, y, (sum + a[x][y]) % m);
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	pow10[0] = 1;
	for (int i = 1; i <= 2 * n - 2; i++)
		pow10[i] = pow10[i - 1] * 10 % m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j]; 
			a[i][j] = pow10[2 * n - i - j] * a[i][j] % m;
		}
	dfs1(1, 1, 0), dfs2(n, n, 0);
	for (int i = 1; i <= n; i++) {
		sort(ans1[i].begin(), ans1[i].end()),
		sort(ans2[i].begin(), ans2[i].end());
		int nsz = ans1[i].size();
		for (int j = 0; j < nsz; j++) {
			int now = ans1[i][j], pos = lower_bound(
			ans2[i].begin(), ans2[i].end(), (2 * m - 
			now - a[i][n + 1 - i]) % m) - ans2[i].begin();
			pos = (pos + nsz - 1) % nsz;
			ans = max(ans, (now + ans2[i][pos] + 
			a[i][n + 1 - i]) % m);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：违规用户名920406 (赞：1)

## 分析
很微妙的折半搜索题。

首先我们发现每经过一个格子后它的贡献是一定的，找规律可知 $A_{i,j}$ 的贡献为 $10^{2n-i-j}A_{i,j}$ ，这就变成了一个方格取数？

但是它要你求取模后的最大值，不过我们发现如果上一格如果是模后最大值，但是下一个格子加上之后就不一定了。不能 dp ，只能爆搜？

$n \leq 20$ ，根据简单的组合计数发现路径最多有 $\tbinom{38}{19}$ 种路径，炸飞。再看数据范围，这明摆着让你搜索，所以要用相对快一点点的方法。怎么办？

考虑折半搜索，Meet in middle。这个东西简单来说就是先将现在要搜索的东西平分成两段，最后再整合信息，输出答案。这题中怎么分？

用矩阵右上到左下的对角线将它分为两半，对于每个对角线上的数，计算起点和终点到它的路径的所有可能结果，分别存入两个 set 。然后整合结果。遍历第一个 set ，也就是起点到中点的路径，再第二个 set 中找中点到终点的路径。设刚才遍历到的值为 $x$ , $0 \leq x < M$ 。并且第二个 set 中只有两个数有可能成为最好路径。第一个是小于 $M-x$ 的最大值，第二个是直接的最大值。想一想，为什么？

## Code
实现中用了 set 中内置的二分函数，用法和普通的 upper_bound 和 lower_bound 差不多。赛时代码有点丑。仅供参考。

```c++
#include <bits\stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[21][21],p[39]={1};
set<int> s[21][21];
void dfs(int x,int y,int X,int Y,int S)
{
	S=(S+a[x][y])%m;//记得取模
	if(x==X&&y==Y)
	{
		s[x][y].insert(S);//加入set
		return;
	}
	if(x<X)	dfs(x+1,y,X,Y,S);
	if(y<Y)	dfs(x,y+1,X,Y,S);
}//从起点到中点的搜索
void dfs2(int x,int y,int X,int Y,int S)
{
	S=(S+a[x][y])%m;
	if(x==X&&y==Y)
	{
		s[x][y].insert(S);//加入set
		return;
	}
	if(x>X)	dfs2(x-1,y,X,Y,S);
	if(y>Y)	dfs2(x,y-1,X,Y,S);
}//从中点到终点的搜索
int main()
{
	cin>>n>>m;
	for(int i=1;i<=2*n-2;i++)	p[i]=10*p[i-1]%m;//预处理10的幂
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			a[i][j]=a[i][j]*p[2*n-i-j]%m;//计算单点贡献
		}
	if(n==1)
	{
		cout<<a[1][1]%m;
		return 0;
	}//记得特判，不然wa两个点
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i+j-1==n)	dfs(1,1,i,j,0);
			if(i+j-1==n+1)
			{
				dfs2(n,n,i,j,0);
				for(auto k:s[i][j])
				{
					if(i>1)//最好判一下边界
					{
						auto p=s[i-1][j].lower_bound(m-k);
						if(p!=s[i-1][j].begin())	ans=max(ans,k+*prev(p));//情况1
						ans=max(ans,k+*s[i-1][j].rbegin()-m);//情况2
					}
					if(j>1)
					{
						auto p=s[i][j-1].lower_bound(m-k);
						if(p!=s[i][j-1].begin())	ans=max(ans,k+*prev(p));//情况1
						ans=max(ans,k+*s[i][j-1].rbegin()-m);//情况2
					}
				}
			}
		}
	cout<<ans;//华丽的输出qwq~
	return 1;
}
```
呼，写完了。看懂记得点赞哦。

---

## 作者：Tairitempest (赞：1)

## [ABC402F] Path to Integer

直接爆搜复杂度是 $C^n_{2n}$，上限可以跑到 $1.3×10^{11}$，一定超时。

注意到本题并没有其他相对高效的做法，且 $N$ 大小并不大，考虑折半搜索——将问题拆成两部分，对这两部分分别进行搜索并记录状态，最后再通过合并状态找到最优解。

具体地，我们可以记录对角线上的每个格子的所有可能从左上角过来的目前的数字值，这个直接搜索，存储所有到达对角线时的贡献值就可以了。

那么从右下角开始搜索要如何在记录的结果中找到最优解，让两个值合并的结果最大呢？对于对角线的每个格子，我们把前半部分对于结果贡献的值 $(s_1×10^{N-1})\bmod M$ 存在这个格子的位置用于结果合并，其中 $s_1$ 是从左上角走到这个格子的时候得到的数字值。对于后半部分的每个搜索结果，即从对角线某格子出发到达右下角的值 $s_2$，我们希望它是不超过 $(M - s_2 - 1) \bmod M$ 的最大值，因此要在到达对角线之后在前面存下来的数字值中二分找最优解，如果没找到那么就只能选择最大值了。记得在搜索和计算的过程中需要用到底数为 $10$ 的幂，需要预处理。

最后在所有搜索结果中选择最大的值就可以了。

时间复杂度 $O(N2^N)$。

## [Code](https://atcoder.jp/contests/abc402/submissions/65036757)

---

## 作者：nbhs23a28 (赞：1)

一道较水（一眼）的 Meet in the middle 搜索题，也是我第一次场切的 F 题。

根据题意，我们需要求出一条路径，使路径上数字构成的数模 $M$ 最大。注意到 $N \le 20$，而路径长仅为 $2N-1$！这意味着我们可以用搜索复杂度通过。显然直接深搜时间会炸，于是我们考虑由双向搜索，到相遇面时会有 $2^N$ 种结果（因为每次有两种独立的选择）。而 $2^{20}$ 是 $10^6$ 级别的，我们便可考虑单方面搜索完成后用 set 维护，另一方向搜索到时用 set 自带的二分查找即可（使取模结果尽可能大）。

Code：（显然深搜更好写。不过赛时写的代码略丑）
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[22][22],p10[45]={1},ans;
set <long long> s[29];
void dfs(int x,int y,long long sum)
{if(x+y-1==n)
 {s[x].insert(((sum*10+a[x][y])%m)*p10[n-1]%m);
  return;
 }
 dfs(x+1,y,(sum*10+a[x][y])%m);
 dfs(x,y+1,(sum*10+a[x][y])%m);
}
void dfs2(int x,int y,long long sum)
{if(x+y-1==n)
 {//cout<<sum<<' ';
  auto it=s[x].lower_bound(m-sum);
  if(it==s[x].begin())
  ans=max(ans,((*(--s[x].end()))+sum)%m);
  else
  ans=max(ans,((*(--it))+sum)%m);
  return;
 }
 dfs2(x-1,y,(sum+a[x][y]*p10[2*n-x-y])%m);
 dfs2(x,y-1,(sum+a[x][y]*p10[2*n-x-y])%m);
}
int main()
{cin>>n>>m;
 for(int i=1;i<=44;i++)
 p10[i]=p10[i-1]*10%m;
 for(int i=1;i<=n;i++)
 {for(int j=1;j<=n;j++)
  cin>>a[i][j];
 }
 dfs(1,1,0);
 dfs2(n,n,0);
 cout<<ans;
}
```

---

## 作者：LittleAcbg (赞：1)

第一，我们发现每个数字在最终形成的数中贡献都是确定的，例如右下角的数字贡献就是它本身，而格子 $(N,N-1)$ 和 $(N-1,N)$ 上的数字贡献就要 $\times10$。

那么，每一个数字的贡献就能拆开来算了。一种想法是维护从左上角到每个点的所有可能贡献和模 $M$ 的值。但这样时间复杂度太大了，由于每一个数字的贡献是独立的，可以考虑 Meet in the middle。

用两次 DFS，分别维护 $(1,1)$ 到 $(x,y)$ 与 $(n,n)$ 到 $(x,y)$ 的两条路可能的贡献。其中 $(x,y)$ 是对角线上的点，即 $x+y=n+1$。

注意到可能贡献值的数量不会超过 $C_{20}^{10}=184756$，所以开 $2\times10^5$ 大小的数组即可存储。

这里还有一个点需要注意，就是 $(x,y)$ 这个点的归属。它可以属于两个部分中的任意一个，也可以分开处理，不过会比较繁琐。我的实现是归在了左上角 $(1,1)$ 的部分。

合并两半的时候，若两半贡献模 $m$ 的值分别为 $b,c$，我们需要最大化 $b+c\bmod m$，可以枚举 $b$ 并对 $c$ 进行二分。若能使 $b+c<m$ 则用其中最大的 $c$，否则使用所有数中最大的 $c$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 30;
const ll T = 2e5; // 对角线上每一位置至多只有不到 2e5 种不同的贡献值
ll n,m,a[N][N],P[N * 2],b[N][T],c[N][T],cb[N],cc[N],ans;
void dfs1(ll x, ll y, ll r) // 左上一部分（包括对角线）
{
	(r += a[x][y]) %= m;
	if (x + y == n + 1)
	{
		b[x][++cb[x]] = r;
		return;
	}
	if (x < n) dfs1(x + 1, y, r);
	if (y < n) dfs1(x, y + 1, r);
}
void dfs2(ll x, ll y, ll r) // 右下一部分（不包括对角线）
{
	if (x + y == n + 1)
	{
		c[x][++cc[x]] = r;
		return;
	}
	(r += a[x][y]) %= m;
	if (x > 1) dfs2(x - 1, y, r);
	if (y > 1) dfs2(x, y - 1, r);
}
int main()
{
	cin >> n >> m;
	for (ll i = 1; i <= n; ++i)
		for (ll j = 1; j <= n; ++j)
			cin >> a[i][j];
	P[0] = 1;
	for (ll i = 1; i <= 2 * n; ++i) P[i] = P[i - 1] * 10 % m;
	for (ll i = 1; i <= n; ++i)
		for (ll j = 1; j <= n; ++j)
			(a[i][j] *= P[2 * n - i - j]) %= m; // 算该数字在这一位的贡献
	dfs1(1, 1, 0);
	dfs2(n, n, 0);
	// 算两边的答案

	for (ll i = 1; i <= n; ++i)
	{
		sort(c[i] + 1, c[i] + cc[i] + 1); // 排序以便二分
		for (ll j = 1; j <= cb[i]; ++j)
		{
			ll x = b[i][j];
			ll pos = lower_bound(c[i] + 1, c[i] + cc[i] + 1, m - x) - c[i]; // 二分，找最小的一个 c 使 b+c>=m
			if (pos >= 2) ans = max(ans, x + c[i][pos - 1]); // 存在 c 使 b+c<m，则用最大的一个
			else ans = max(ans, x + c[i][cc[i]] - m); // 用所有 c 里最大的一个，注意 mod m 此时可以写作 - m
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ACQian (赞：1)

# [ABC402F] Path to Integer 题解

## [ABC402E题解（广告）](https://www.luogu.com.cn/article/8ry16qm0)

## 题意翻译与简述
有一个 $N\times N$ 网格。每个单元格包含一个数码 $A_{i,j}$ 。

设一条从 $(1,1)$ 到达 $(N,N)$ 长达 $2N-1$ 的路径为
$$(x_1,y_1),(x_2,y_2)\cdots,(x_{2N-1},y_{2N-1})$$
其中任意 $i(1\le i\le 2N-1)$ 满足 $x_i+1=x_{i+1}$ 且 $y_i=y_{i+1}$ 或 $x_i=x_{i+1}$ 且 $y_i+1=y_{i+1}$。即 $(x_i,y_i)$ 和 $(x_{i+1},y_{i+1})$ 是相邻单元格。

记 $S$ 为
$$S=\sum_{i=1}^{2n-1}{a_{x_i,y_i}\times 10^{2n-i-1}}$$

求 ${S\bmod M}$ 的最大值。

## 思路
可以发现本题没有一个合适的策略，也不满足最优子结构，所以考虑搜索。

然而，发现从 $(1,1)$ 到 $(N,N)$ 有 $C^{2n}_{n}$ 种路径。对于 $N\le 20$ 的数据范围而言，显然会超时的。   
所以考虑以对角线 $x+y=N+1$ 作为分界线，进行折半搜索。

具体实现为函数 ```dfs1()``` 从 $(1,1)$ 开始进行搜索，直到对角线为止，并把所有结果放入一个 vector 中。   
函数 ```dfs2()``` 从 $(N,N)$ 开始进行逆序搜索，直到对角线为止。查找所有到达该点的 ```dfs1()``` 中的结果，并进行匹配。最后，取最小值作为答案。   

------
预处理时，可以提前计算出 $10^p\bmod M$ 的值，并赋值到 $a_{i,j}$ 中去。
```cpp
    d[2 * n] = 1;
    for(int i = 2 * n - 1;i > 1;i --){
        d[i] = (1LL * d[i + 1] * 10) % m;
    }
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= n;j ++){
            a[i][j] = (1LL * a[i][j] * d[i + j]) % m;
        }
    }
```

---
问题在于，折半后规模 $\frac{n}{2}\le10$，在中间匹配时暴力枚举所有结果时间复杂度高达 $10^{12}$，显然会超时。   
所以可以考虑采用二分查找的方式，对于每个 ```dfs2()``` 的结果找到对应的 vector 中的最大值：
```cpp
lower_bound(ans[x].begin(),ans[x].end(),m - p) - ans[x].begin();
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 40;
int n,m,res;
int a[maxn][maxn];
int d[maxn];
vector<int> ans[maxn];

void dfs1(int x,int y,int p){
    if(x + y == n + 1){
        ans[x].push_back((1LL * p + a[x][y]) % m);
        return;
    }
    if(x < n)   dfs1(x + 1,y,(1LL * p + a[x][y]) % m);
    if(y < n)   dfs1(x,y + 1,(1LL * p + a[x][y]) % m);
}

void dfs2(int x,int y,int p){
    if(x + y == n + 1){
        int i = lower_bound(ans[x].begin(),ans[x].end(),m - p) - ans[x].begin();
        if(i <= 0)   i = ans[x].size() - 1;
        else    i --;
        res = max(1LL * res,(1LL * p + ans[x][i]) % m);
        return;
    }
    if(x > 1)   dfs2(x - 1,y,(1LL * p + a[x][y]) % m);
    if(y > 1)   dfs2(x,y - 1,(1LL * p + a[x][y]) % m);
}

int main(){
    scanf("%d %d",&n,&m);
    d[2 * n] = 1;
    for(int i = 2 * n - 1;i > 1;i --){
        d[i] = (1LL * d[i + 1] * 10) % m;
    }
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= n;j ++){
            scanf("%d",&a[i][j]);
            a[i][j] = (1LL * a[i][j] * d[i + j]) % m;
        }
    }
    dfs1(1,1,0);
    for(int i = 1;i <= n;i ++){
        sort(ans[i].begin(),ans[i].end());
    }
    dfs2(n,n,0);
    printf("%d",res);
    return 0;
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
题意简单，这里不在赘述。

[不爱看题的赶紧看！！!](https://www.luogu.com.cn/problem/AT_abc402_f)

# 思路
**折半搜索**，沿**对角线**分为两部分，再把结果拼起来。

代码实现分为三个部分。

首先是**预处理**部分。

因为题目要求每次往数的**末尾**加入，所以倒着求出 $10^i$ 存入数组 $d$ 中。再将数组 $a$ 也处理好，方便后续求路径权值。
```cpp
//因为是往末尾加，所以倒着存权值 
d[n<<1]=1;	//n+n=2*n,1+1=2（终点，起点） 
for(int i=(n<<1)-1;i>=2;i--)d[i]=(d[i+1]*10)%mod;
for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=(a[i][j]*d[i+j])%mod;
```
第二是求**上半部分**的答案。

这里使用 `dfs` 来搜索。

搜到对角线后，就记录当前 $x$ 的答案，好与下半部分**匹配链接**。

由于预处理我们是倒着存的，所以直接用旧路径和 $+$ 新数字即可。

例如 $3$，$1$，$6$ 的计算过程就应该是 $300+10+6$，直接相加。    

最后再把得到的答案**排序**，为下半部分的匹配链接做准备。
```cpp
void dfs(int x,int y,int p){
	if(x+y==n+1){	//对角线（右上至左下）
		//根据x就可以得到y  
		ans[x].push_back((p+a[x][y])%mod);
		return;
	}
	if(x<n)dfs(x+1,y,(p+a[x][y])%mod);
	if(y<n)dfs(x,y+1,(p+a[x][y])%mod);
}
```
最后是求**下半部分**的答案以及**匹配链接**的过程。

这里同样用 `dfs` **倒着搜**。

如果搜到对角线了，那么就用二分找到上半部分的最优解，也就是尽可能的和为 $mod-1$。

用`lower_bound`找到 $\ge mod-p$ 的答案，再 $-1$ 就是 $< mod-p$ 的答案，也就是最优解了。

如果没有 $\ge mod-p$ 的答案，那么就取最大的，尽可能的接近 $mod-p-1$。

最后把两部分加起来再更新答案即可。
```cpp
void dfs2(int x,int y,int p){
	if(x+y==n+1){
		//尽可能的p+t=mod-1 
		int t=lower_bound(ans[x].begin(),ans[x].end(),mod-p)-ans[x].begin();	
		//>=-1变为<
		if(t<=0)t=ans[x].size()-1;	//都小于mod-p，选最大的
		else t--; 
		sum=max(sum,(ans[x][t]+p)%mod);	//dfs1已经算了对角线，所以这里不用再加a[x][y] 
		return;
	}
	if(x>1)dfs2(x-1,y,(p+a[x][y])%mod);
	if(y>1)dfs2(x,y-1,(p+a[x][y])%mod);
}
```
# 代码
完整代码，无注释。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
int n,mod,a[25][25];
int d[45],sum=-1;
vector<int> ans[25];
void dfs(int x,int y,int p){
	if(x+y==n+1){	
		ans[x].push_back((p+a[x][y])%mod);
		return;
	}
	if(x<n)dfs(x+1,y,(p+a[x][y])%mod);
	if(y<n)dfs(x,y+1,(p+a[x][y])%mod);
}
void dfs2(int x,int y,int p){
	if(x+y==n+1){
		int t=lower_bound(ans[x].begin(),ans[x].end(),mod-p)-ans[x].begin();	
		if(t<=0)t=ans[x].size()-1;	
		else t--; 
		sum=max(sum,(ans[x][t]+p)%mod);
		return;
	}
	if(x>1)dfs2(x-1,y,(p+a[x][y])%mod);
	if(y>1)dfs2(x,y-1,(p+a[x][y])%mod);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	d[n<<1]=1;	 
	for(int i=(n<<1)-1;i>=2;i--)d[i]=(d[i+1]*10)%mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=(a[i][j]*d[i+j])%mod;
	dfs(1,1,0); 
	for(int i=1;i<=n;i++)sort(ans[i].begin(),ans[i].end());
	dfs2(n,n,0);
	cout<<sum;
	return 0; 
}
```
### 谢谢！

---

## 作者：cheng2010 (赞：0)

## 思路

很好的折半搜索练习题。

考虑暴力枚举路径，是 $O(2^{2n-1})$ 的，显然不行。这时我们考虑折半搜索。

具体地，我们只用从 $(1,1)$ 开始把长度为 $n$ 每一条路径及对应的对 $M$ 取余的值找出来，用 set 存储，再从 $(n,n)$ 遍历每一条长度为 $n-1$ 的路径，到了交汇点便在对应的 set 中二分查找即可。

时间：$O(2^{\frac{n}{2}} \log n)$。

## code

[link](https://atcoder.jp/contests/abc402/submissions/65038201)

---

## 作者：GenesisCrystal (赞：0)

终于能写了！

## Solution

首先我们知道，这是一个矩阵，并且 $n$ 非常小，只有 $20$，于是果断考虑 meet in middle。

我开了 $n \times n$ 个 vector 记录所有在对角线上的可能的模数值（所以只有 $n + 1$ 个用上了的）。这个可以从 $(1, 1)$ 开始搜到 $(x, n + 1 - x)$ 时得到。然后再对 vector 排序。等到从 $(n, n)$ 开始搜的时候只需要二分查找一下就可以了。

综上，复杂度等于 $O(2^n\log n)$。

注意在搜索中的数字的相加方式。

## Code

```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <queue>

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const ll kMaxN = 100, kD[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

ll n, m, k[kMaxN][kMaxN], x, y, l, r, ans, cnt, a[kMaxN][kMaxN], b[kMaxN][kMaxN][kMaxN], c[kMaxN], p[kMaxN];
string s, t;
char ch, op;
double d;
map<ll, ll> mp[kMaxN][kMaxN];
vector<ll> vec[kMaxN][kMaxN];

void Dfs1(int x, int y, ll s) {
  if (x + y == n + 1) {
    (!mp[x][y][s]) && (vec[x][y].push_back(s * l % m), mp[x][y][s] = 1);
    return;
  }
  Dfs1(x + 1, y, (s * 10 + a[x + 1][y]) % m);
  Dfs1(x, y + 1, (s * 10 + a[x][y + 1]) % m);
}

int Rev(int x) {
  string res;
  while (x) {
    res = res + (char)(x % 10 + '0');
    x /= 10;
  }
  return stoi(res);
}

void Dfs2(int x, int y, ll s) {
  if (x + y == n + 1) {
    int pos = upper_bound(b[x][y] + 1, b[x][y] + k[x][y] + 1, m - s - 1) - b[x][y] - 1;
    ans = max(ans, (b[x][y][(pos == 0 ? k[x][y] : pos)] + s) % m);
    return;
  }
  Dfs2(x - 1, y, (s + a[x][y] * p[2 * n - x - y]) % m);
  Dfs2(x, y - 1, (s + a[x][y] * p[2 * n - x - y]) % m);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  l = 1;
  for (int i = 1; i < n; i++) {
    l = l * 10;
    l %= m;
  }
  p[0] = 1;
  for (int i = 1; i <= n * 2; i++) {
    p[i] = p[i - 1] * 10 % m;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  Dfs1(1, 1, a[1][1]);
  for (int x = 1, y = n; x <= n; x++, y--) {
    sort(vec[x][y].begin(), vec[x][y].end());
    k[x][y] = vec[x][y].size();
    for (int i = 1; i <= k[x][y]; i++) {
      b[x][y][i] = vec[x][y][i - 1];
    }
  }
  Dfs2(n, n, 0);
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

我们发现 $O(2^n)$ 附近可以通过本题，但选择有 $2n-1$ 个，直接暴力是 $O(2^{2n-1})$ 会 TLE，所以我们可以想到 meet in the middle，先处理从 $(1,1)$ 走 $n$ 步能到的每个点分别可能模 $m$ 余多少并扔到 set 里面，然后从 $(n,n)$ 倒着走 $n-1$ 步形成另一个整数，题目变成给定集合 $S$，快速求出 $S$ 中选一个数加上给定数 $x$ 模 $m$ 的最大值，考虑到 $S$ 中的数都小于 $m$，$x$ 也是，所以能作为答案的 $y\in S$，要么是最大的不超过 $m-1-x$ 的数（可二分），要么是 $S$ 中的最大值（因为 $S$ 是 set，所以直接求）。时间复杂度 $O(2^n\times n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
set<int> st[30][30];
int n,a[30][30],m,p10[100],ans=0;
void dfs(int x,int y,int now,int step)
{
	if(step==n)
	{
		st[x][y].insert(now*p10[n-1]%m);
		return;
	}
	dfs(x+1,y,(now*10+a[x+1][y])%m,step+1);
	dfs(x,y+1,(now*10+a[x][y+1])%m,step+1);
}
void dfs2(int x,int y,int now,int step)
{
	if(step==n)
	{
		ans=max(ans,(*(--st[x][y].end())+now)%m);
		if(st[x][y].upper_bound(m-now-1)!=st[x][y].begin())
		ans=max(ans,(*(--st[x][y].upper_bound(m-now-1))+now)%m);
		return;
	}
	int nnow=a[x][y]*p10[step-1]%m+now;
	nnow%=m;
	dfs2(x-1,y,nnow,step+1);
	dfs2(x,y-1,nnow,step+1);
}
signed main()
{
	cin>>n>>m;
	p10[0]=1;
	for(int i=1;i<=2*n-1;i++) p10[i]=p10[i-1]*10%m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	cin>>a[i][j];
	dfs(1,1,a[1][1],1);
	dfs2(n,n,0,1);
	cout<<ans;
}

---

## 作者：lovely_qiqi (赞：0)

## 思路

首先注意到本题并没有转移性，DP 是不行的，数据范围又很小，考虑爆搜。直接搜是 $O(2^{39})$ 直接 TLE 但是发现 meet in the middle 非常轻松的就能跑过。于是考虑先搜前一半的路径用 vector 进行存储搜到当前点可能的余数，排序再搜后一半的路径，二分查找最大的余数：设当前搜到的值为 $x$ 模数是 $m$ 则分两种情况：

+ 存在一个 $y$ 使得 $x+y <m$ 那么直接就是 $x+y$。
+ 否则直接找 $y$ 的最大值，答案是 $(x+y) \bmod m$。

取最大值就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,k,ans,f1,f2,l,r,mid,tot,a[25][25],mod[110],dp[25][25];
vector<int> v[25][25];
struct node{
	int x,y,cnt,step;
}tmp;
queue<node> q;
void bfs(){
	q.push({1,1,a[1][1],0});
	while(!q.empty()){
		tmp=q.front();
		q.pop();
		v[tmp.x][tmp.y].push_back(mod[2*n-2-tmp.step]*tmp.cnt%m);
		if(tmp.step>=f1) continue;
		if(tmp.x+1<=n){
			k=(tmp.cnt*10%m+a[tmp.x+1][tmp.y])%m;
			q.push({tmp.x+1,tmp.y,k,tmp.step+1});
		}
		if(tmp.y+1<=n){
			k=(tmp.cnt*10%m+a[tmp.x][tmp.y+1])%m;
			q.push({tmp.x,tmp.y+1,k,tmp.step+1});
		}
	}
}
int find(int x,int sx,int sy){
	l=0,r=v[sx][sy].size()-1,tot=-1;
	if(v[sx][sy].size()==0) return -1;
	while(l<=r){
		mid=(l+r)/2;
		if(v[sx][sy][mid]<m-x){
			l=mid+1;
			tot=mid;
		}
		else r=mid-1;
	}
	if(tot==-1) return (x+v[sx][sy][v[sx][sy].size()-1])%m;
	else return x+v[sx][sy][tot];
}
void bfss(){
	q.push({n,n,0,0});
	while(!q.empty()){
		tmp=q.front();
		q.pop();
		ans=max(ans,find(tmp.cnt,tmp.x,tmp.y));
		tmp.cnt=tmp.cnt+mod[tmp.step]*a[tmp.x][tmp.y]%m;
		tmp.cnt%=m;
//		cout<<tmp.x<<" "<<tmp.y<<":"<<tmp.cnt<<"\n";
		if(tmp.step>=f2) continue;
		if(tmp.x-1>=1){
			q.push({tmp.x-1,tmp.y,tmp.cnt,tmp.step+1});
		}
		if(tmp.y-1>=1){
			q.push({tmp.x,tmp.y-1,tmp.cnt,tmp.step+1});
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	f1=(2*n-1)/2;
	f2=2*n-1-f1;
	mod[0]=1;
	for(int i=1;i<=2*n;i++){
		mod[i]=(mod[i-1]*10)%m;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	bfs();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sort(v[i][j].begin(),v[i][j].end());
//			cout<<i<<" "<<j<<"\n";
//			for(int it:v[i][j]) cout<<it<<" ";
//			cout<<"\n";
		}
	}
	bfss();
	cout<<ans;
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

折半搜索（没想出来……）。

直接搜肯定寄了，发现可以 $\Theta(2^n)$，考虑折半搜索。

把每个格子 $(i,j)$ 的权值乘上 $10^{2n-i-j}$，这样就可以不用拼接，直接求和了。

然后就是直接搜了。

假设右下半部搜到了一个总和 $x$，那么尝试找到左上半部到该格子的权值总和中 $<m-x$ 的最大的那一个，若没有，则找最大的那一个。取个最大值就做完了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int qp(int a,int b,const int m){int s=1;while(b){if(b&1)s=s*a%m;a=a*a%m,b>>=1;}return s;}
int n,m,a[21][21],ans;
set<int>l[21];
void dfsl(int x,int y,int tot,int st){
	tot%=m;
	if(st==n){
		l[x].insert(tot);
		return;
	}
	dfsl(x+1,y,tot+a[x+1][y],st+1);
	dfsl(x,y+1,tot+a[x][y+1],st+1);
}
using IT=set<int>::iterator;
void dfsr(int x,int y,int tot,int st){
	tot%=m;
	if(st==n){
		IT it=l[x].lower_bound(m-tot);
		if(it!=l[x].begin())it--;
		ans=max(ans,(tot+(*it))%m);
		return;
	}
	dfsr(x-1,y,tot+a[x][y],st+1);
	dfsr(x,y-1,tot+a[x][y],st+1);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j],a[i][j]=a[i][j]*qp(10,2*n-i-j,m)%m;
	dfsl(1,1,a[1][1],1);
	dfsr(n,n,0,1);
	cout<<ans;
	return 0;
}
```

---

