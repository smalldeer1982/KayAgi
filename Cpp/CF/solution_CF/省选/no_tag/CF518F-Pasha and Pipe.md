# Pasha and Pipe

## 题目描述

On a certain meeting of a ruling party "A" minister Pavel suggested to improve the sewer system and to create a new pipe in the city.

The city is an $ n×m $ rectangular squared field. Each square of the field is either empty (then the pipe can go in it), or occupied (the pipe cannot go in such square). Empty squares are denoted by character ' $ . $ ', occupied squares are denoted by character ' $ # $ '.

The pipe must meet the following criteria:

- the pipe is a polyline of width $ 1 $ ,
- the pipe goes in empty squares,
- the pipe starts from the edge of the field, but not from a corner square,
- the pipe ends at the edge of the field but not in a corner square,
- the pipe has at most $ 2 $ turns ( $ 90 $ degrees),
- the border squares of the field must share exactly two squares with the pipe,
- if the pipe looks like a single segment, then the end points of the pipe must lie on distinct edges of the field,
- for each non-border square of the pipe there are exacly two side-adjacent squares that also belong to the pipe,
- for each border square of the pipe there is exactly one side-adjacent cell that also belongs to the pipe.

Here are some samples of allowed piping routes:

`<br></br>           ....#            ....#            .*..#<br></br>           *****            ****.            .***.<br></br>           ..#..            ..#*.            ..#*.<br></br>           #...#            #..*#            #..*#<br></br>           .....            ...*.            ...*.<br></br>`Here are some samples of forbidden piping routes:

`<br></br>           .**.#            *...#            .*.*#<br></br>           .....            ****.            .*.*.<br></br>           ..#..            ..#*.            .*#*.<br></br>           #...#            #..*#            #*.*#<br></br>           .....            ...*.            .***.<br></br>`In these samples the pipes are represented by characters ' $ * $ '.

You were asked to write a program that calculates the number of distinct ways to make exactly one pipe in the city.

The two ways to make a pipe are considered distinct if they are distinct in at least one square.

## 说明/提示

In the first sample there are 3 ways to make a pipe (the squares of the pipe are marked by characters ' $ * $ '):

`<br></br>       .*.        .*.        ...<br></br>       .*#        **#        **#<br></br>       .*.        ...        .*.<br></br>`

## 样例 #1

### 输入

```
3 3
...
..#
...
```

### 输出

```
3```

## 样例 #2

### 输入

```
4 2
..
..
..
..
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 5
#...#
#...#
###.#
###.#
```

### 输出

```
4```

# 题解

## 作者：Hooch (赞：2)

[更好的体验](https://www.cnblogs.com/CTHOOH/p/18157297)

观察到一条管道的拐点数量只有 $3$ 种可能的取值：

+ 没有拐点，即管道呈现一条直线。
+ 有 $1$ 个拐点。
+ 有 $2$ 个拐点。

分别对应了下面三种情况：

```plain
....#           ....#            .*..#
*****           ****.            .***.
..#..           ..#*.            ..#*.
#...#           #..*#            #..*#
.....           ...*.            ...*.
```

***

考虑对这三种情况分别计数，先预处理出来几个辅助数组 （`bool` 类型），$U[i][j], D[i][j], L[i][j], R[i][j]$，$U[i][j]$ 表示从 $(i, j)$ 到 $(1, j)$ 的路上是否**无障碍物**，即从 $(i, j)$ 一直往上走的路径上是否**无障碍物**。$D[i][j], L[i][j], R[i][j]$ 同理，分别表示往下走 $(i, j) \to (n, j)$、往左走 $(i, j) \to (i, 1)$、往右走 $(i, j) \to (i, m)$ 的路上是否**不存在障碍物**。特别地，对于有障碍物的格子 $(i, j)$，有 $U[i][j] = D[i][j] = L[i][j] = R[i][j] = 0$。

分类讨论拐点数量：

+ 对于没有拐点的情况，答案是 $\sum\limits_{i=2}^{n-1}R[i][0]+\sum\limits_{i=2}^{m-1}D[0][i]$。
+ 对于有 $1$ 个拐点的情况，考虑枚举拐点的位置，接着枚举管道通往的方向，并根据对应的 $U, D, L, R$ 数组计算贡献即可。这部分的答案为 $\sum\limits_{i = 2}^{n - 1}\sum\limits_{j = 2}^{m - 1} (L[i][j] + R[i][j]) \times (D[i][j] + U[i][j])$。
+ 对于有 $2$ 个拐点的情况，分成两种子情况：第一种是管道先竖着走再横着走再竖着走；第二种是先横着走再竖着走再横着走。可以发现两种情况类似，下面只讨论第一种情况：

	先枚举横着走的那一行，从左往右扫每一列，记当前行为 $i$，列为 $j$。记录两个值 $toU, toD$，分别表示 $2 \sim (j - \textbf{2})$ 中有多少列能向上走，有多少列能向下走，且第 $i$ 行内第 $j$ 列与这些列之间没有障碍物。考虑贡献答案，先特殊考虑 $j - 1$ 列的贡献 ( 因为 $j$ 列和 $j - 1$ 列不能同时往上或者同时往下 )，再考虑 $2 \sim (j - 2)$ 列，显然这部分对答案贡献为 $(U[i][j] + D[i][j]) \times (toU + toD)$。离开第 $j$ 列时更新一下 $toU$ 和 $toD$ 即可。
    
	第二种情况类似处理出 $toL$ 和 $toR$ 即可。

至此本题解决，复杂度 $O(nm)$。下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

signed main(void) {
    ios :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector <vector <char>> a(n, vector <char> (m));
    vector <vector <int>> u(n, vector <int> (m));
    auto d = u, l = u, r = u;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            u[i][j] = (!i ? 1 : u[i - 1][j]) && (a[i][j] == '.');
            l[i][j] = (!j ? 1 : l[i][j - 1]) && (a[i][j] == '.');
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            d[i][j] = (i + 1 == n ? 1 : d[i + 1][j]) && (a[i][j] == '.');
            r[i][j] = (j + 1 == m ? 1 : r[i][j + 1]) && (a[i][j] == '.');
        }
    }

    i64 ans = 0;
    for (int i = 1; i + 1 < n; ++i)
        ans += r[i][0];
    for (int j = 1; j + 1 < m; ++j)
        ans += d[0][j];

    for (int i = 1; i + 1 < n; ++i)
        for (int j = 1; j + 1 < m; ++j)
            ans += (l[i][j] + r[i][j]) * (d[i][j] + u[i][j]);

    for (int j = 1; j + 1 < m; ++j) {
        int toL = 0, toR = 0;
        for (int i = 1; i + 1 < n; ++i) {
            if (l[i][j])
                ans += toL + toR + (i > 1 && r[i - 1][j]);
            if (r[i][j])
                ans += toL + toR + (i > 1 && l[i - 1][j]);
            if (i > 1) {
                toL += l[i - 1][j];
                toR += r[i - 1][j];
            }
            if (a[i][j] == '#') {
                toL = 0;
                toR = 0;
            }
        }
    }
    for (int i = 1; i + 1 < n; ++i) {
        int toU = 0, toD = 0;
        for (int j = 1; j + 1 < m; ++j) {
            if (u[i][j])
                ans += toU + toD + (j > 1 && d[i][j - 1]);
            if (d[i][j])
                ans += toU + toD + (j > 1 && u[i][j - 1]);
            if (j > 1) {
                toU += u[i][j - 1];
                toD += d[i][j - 1];
            }
            if (a[i][j] == '#') {
                toU = 0;
                toD = 0;
            }
        }
    }

    cout << ans << '\n';
}
```

---

## 作者：LPhang (赞：2)

因为管道直通边缘，首先处理出每个位置能否到达上、下、左、右的边界。

考虑到只能拐弯最多两次，则分情况讨论。

**不拐弯**

直接枚举边缘所在位置，根据实现处理的数组判断即可

**拐 $1$ 次弯**

枚举拐点，判断不同方向即可

**拐 $2$ 次弯**

因为起点与终点最后要么在相对的边界上，要么在同一条边界上，所以交换一下行列，可以将左右的铺设方式也转化成求上下的铺设方式。

接着枚举 $2$ 次拐弯之间那段所在的行，并枚举右端点，记录一个 $num$ 表示左端点有多少可能。

设 $up_{i,j}$ 表示 $(i,j)$ 是否能到达上界，$down_{i,j}$ 表示是否能到达下界，则有如下计算方式
$$
ans=\sum\limits_{i=2}^{n-1}\sum\limits_{j=2}^{m-1}(up_{i,j}+down_{i,j})\times num
$$
但是因为题目限制，管道不能相邻，所以还需要减去相邻的情况，则有
$$
ans=\sum\limits_{i=2}^{n-1}\sum\limits_{j=2}^{m-1}(up_{i,j}+down_{i,j})\times num-(up_{i,j}\land up_{i,j-1} + down_{i,j}\land down_{i,j-1})
$$
最后将这个位置作为左端点的可能性统计进 $num$ 即可

具体实现见代码：

```cpp
#include<bits/stdc++.h>
#define rep1(i, a, b) for(int i = a; i <= b; ++i)
#define rep2(i, a, b) for(int i = a; i >= b; --i)
#define pb push_back
#define pii pair <int, int>
#define ft first
#define sd second
#define ll long long
#define ptc putchar
#define debug puts("-------------------------")
const int N = 2e3 + 10;
using namespace std;
ll ans; bool a[N][N], b[N][N], u[N][N], d[N][N], l[N][N], r[N][N];
void solve(bool a[N][N], int n, int m, int tp) {
	rep1(i, 1, n) rep1(j, 1, m) u[i][j] = u[i - 1][j] | a[i][j];
	rep2(i, n, 1) rep1(j, 1, m) d[i][j] = i == n ? a[i][j] : d[i + 1][j] | a[i][j];
	rep1(i, 1, n) rep1(j, 1, m) l[i][j] = l[i][j - 1] | a[i][j];
	rep1(i, 1, n) rep2(j, m, 1) r[i][j] = j == m ? a[i][j] : r[i][j + 1] | a[i][j];
    \\预处理
	rep1(i, 2, m - 1) ans += !d[1][i]; \\不拐弯
	rep1(i, 2, n - 1) {
		int num = 0;
		rep1(j, 2, m - 1) {
			if(a[i][j]) {num = 0; continue;} \\遇到障碍左边的都没有可能成为左端点
			ans += (!d[i][j] + !u[i][j]) * num; num += !u[i][j] + !d[i][j];
			ans -= (j > 2 && !d[i][j] && !d[i][j - 1]);
			ans -= (j > 2 && !u[i][j] && !u[i][j - 1]);
			if(tp) ans += (!d[i][j] + !u[i][j]) * (!l[i][j] + !r[i][j]); \\拐一次弯
		}
	}
}
int main() {
	int n, m; cin >> n >> m;
	rep1(i, 1, n) rep1(j, 1, m) {
		char c; cin >> c;
		a[i][j] = b[j][i] = (c == '#');
	}
	solve(a, n, m, 1);
	solve(b, m, n, 0); \\行列交换处理
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言

duel 时候碰到的好史，都来吃，一个赞吃一次 CF 旧时代史！

# Solution

一道个人定义为模拟的题目，因为没有使用除了前缀和之外的 dp。

题目对管道有很多要求，看着就头疼，我们先解释一下。

首先，rule 7&8 只是对 rule 1 的简单扩展，防止走一步就转回来这种情况：
```
....
.**.
.**.
.**.
.**.
```
rule 6 防止了边上铺两个这种情况：
```
....
....
....
.**.
```
所以只剩这样四种情况：
```
1.
..*.
..*.
..*.
..*.
2.
.*..
.**.
..*.
..*.
3.
.....
.***.
.*.*.
.*.*.
4.
....
***.
..*.
..*.
```
我们分别计数。

### 第一种

这个最简单，就是判断一条直线上是不是全部没有障碍。

考虑到这个后面可能反复出现，有必要预处理。

我的方法是把障碍当做 $1$，直接二维前缀和然后差分计算。

### 第四种

这个也简单，枚举端点，然后路径是唯一的，直接判断有没有即可。

### 第二、三种

如果还是枚举端点然后计数，那么我们就要维护区间先取或在对结果求总和，这看起来并不是很友好。

考虑换个思路枚举中间的横边，即：
```
.*..
.@@.
..*.
..*.
```
那我们找到中间每一段极长可填段，然后判断一下它能不能朝上下走到底，记为 $up_i,down_i$。

那么答案应该增加

$$\sum\limits _{i=l+1}^{r}up_i(\Sigma_{j<i}down_j+\Sigma_{j<i-1}up_j)+down_i(\Sigma_{j<i}up_j+\Sigma_{j<i-1}down_j)$$

显然可以记录前缀和来达到 $O(nm)$。

注意另一个方向（连接左右）的要重新计数，~~论 `goto` 的重要性~~ 。

## AC code


```cpp
#include<bits/stdc++.h>
using namespace std;
char op;
#define N 2085
int a[N][N],sm[N][N],swa[N][N],sws[N][N],n,m,i,j,up[N],down[N],us[N],ds[N],k;
int ask(int i1,int j1,int i2,int j2)
{
	return sm[i2][j2]-sm[i2][j1-1]-sm[i1-1][j2]+sm[i1-1][j1-1];
}
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		cin>>op,a[i][j]=(op=='#')?1:0;
	if(n==2)
	{
		int ans=0;
		for(i=2;i<m;i++) if(!a[1][i]&&!a[2][i]) ans++;
		cout<<ans;
		return 0;
	}
	if(m==2)
	{
		int ans=0;
		for(i=2;i<n;i++) if(!a[i][1]&&!a[i][2]) ans++;
		cout<<ans;
		return 0;
	}
	long long ans=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			sm[i][j]=a[i][j]+sm[i-1][j]+sm[i][j-1]-sm[i-1][j-1];
	for(i=2;i<n;i++)
	for(j=2;j<m;j++)
	{
		if(!ask(i,1,i,j)&&!ask(1,j,i,j)) ans++;
		if(!ask(i,j,i,m)&&!ask(i,j,n,j)) ans++;
		if(!ask(i,1,i,j)&&!ask(i,j,n,j)) ans++;
		if(!ask(i,j,i,m)&&!ask(1,j,i,j)) ans++;
	}
	int pro=0;
	here:
	for(i=2;i<n;i++)
	{
		if(!ask(i,1,i,m)) ans++;
		int st=2;
		for(j=2;j<=m;j++)
		{
			if(a[i][j]||j==m)
			{
				int ed=j-1;
				if(st>ed) {st=j+1;continue;}
//				cerr<<i<<" "<<st<<" ---> "<<ed<<endl;
				us[st-1]=ds[st-1]=0;
				for(k=st;k<=ed;k++) up[k]=!bool(ask(1,k,i,k)),us[k]=us[k-1]+up[k],down[k]=!bool(ask(i,k,n,k)),ds[k]=ds[k-1]+down[k];//,cout<<k<<" "<<up[k]<<" "<<down[k]<<endl;
				for(k=st+1;k<=ed;k++) ans+=(us[k-2]+ds[k-1])*up[k]+(ds[k-2]+us[k-1])*down[k];
				st=j+1;
			}
		}
	}
	if(pro)
	{
		cout<<ans;
		return 0;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		swa[j][i]=a[i][j],sws[j][i]=sm[i][j];
	swap(n,m);
	memset(a,0,sizeof a);
	memset(sm,0,sizeof sm);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		a[i][j]=swa[i][j],sm[i][j]=sws[i][j];
	pro++;
	goto here;	
}
```

# The End.

---

## 作者：youdu666 (赞：0)

### 思路：模拟、数据结构

套着一个动态规划的外壳，实际上是一个非常阴间的模拟，本人调了一个下午。或许有更简单的动态规划做法？反正蒟蒻我是不会。

考虑把转弯情况分类讨论。

先预处理每一个点左右上下不转弯能到的最远的点，后续有很多操作都要用到。

不转弯的直接从每个边上的点开始往另一个方向走就可以了。

转弯一次的，一定是上下和左右两边匹配，因此暴力算出每个点从左右走到的次数，然后再上下枚举加起来即可。

转弯两次的，还要分讨，第一种是最终不变向的，因为上下和左右做法一样，现在仅考虑上下。开一个树状数组，从上往下走，每一次给横着的能走到的一段区间加一下，然后再从下往上走单点查询，注意特判掉不转弯的方案，会算重。注意用线段树常数太大了，一开始超时了。

第二种则是最终刚好转了一个方向，相当于第三种情况变成了每次更新的时候同步查询。对于四个边都要分开来做，记得把树状数组清空一下。

然后把四种情况的结果加起来就是答案了。其实还是比较简单的，但是码量巨大，而且很难直接用评测数据进行调试。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2005;
int n,m;
char c[N][N];
int go_lft[N][N],go_rgt[N][N],go_ups[N][N],go_dom[N][N],ans,sm[N][N];
bool can_go_straight[N][N];
int t[N][N];//每一行都开一颗BIT
inline void init(void);
inline int max(int x,int y){return x>y?x:y;}
inline void solve_t0(void)
{
	for(int i=2;i<n;i++)
		if(go_rgt[i][1]==m)
			can_go_straight[i][1]=can_go_straight[i][m]=true,
		ans++;
	for(int i=2;i<m;i++)
		if(go_dom[1][i]==n)
			can_go_straight[1][i]=can_go_straight[n][i]=true,
		ans++;
}
int cnt[N][N];
inline void solve_t1(void)
{
	for(int i=2;i<n;i++)//(i,1)，往右冲
	{
		if(c[i][1]=='#')continue;
		for(int j=2;j<m;j++)
		{
			if(c[i][j]=='#')break;
			cnt[i][j]++;
		}
	}
	for(int i=2;i<n;i++)//(i,m)
	{
		if(c[i][m]=='#')continue;
		for(int j=m-1;j>1;j--)
		{
			if(c[i][j]=='#')break;
			cnt[i][j]++;
		}
	}
	for(int i=2;i<m;i++)//(1,i)
	{
		if(c[1][i]=='#')continue;
		for(int j=2;j<n;j++)
		{
			if(c[j][i]=='#')break;
			ans+=cnt[j][i];
		}
	}
	for(int i=2;i<m;i++)//(n,i)
	{
		if(c[n][i]=='#')continue;
		for(int j=n-1;j>1;j--)
		{
			if(c[j][i]=='#')break;
			ans+=cnt[j][i];
		}
	}
}
inline int lowbit(int x){return x&(-x);}
inline void addd(int ip,int x,int v,int lmt)
{
	for(int i=x;i<=lmt;i+=lowbit(i))t[ip][i]+=v;
}
inline void update(int ip,int k,int l,int r,int x,int y,int v)//一开始写的是线段树，超时以后懒得改接口了
{
	if(x>y)return;
	addd(ip,x,v,r);
	addd(ip,y+1,-v,r);
}
int query(int ip,int k,int l,int r,int x)
{
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))res+=t[ip][i];
	return res;
}
inline void solve_t2(void)
{
	for(int i=2;i<n;i++)//(i,1)往右走
	{
		if(c[i][1]=='#')continue;
		for(int j=2;j<=min(go_rgt[i][1],m-1);j++)//走到的是(i,j)
			update(j,1,1,n,go_ups[i][j],go_dom[i][j],1);
	}
	for(int i=2;i<n;i++)//(i,m)往左走
	{
		if(c[i][m]=='#')continue;
		for(int j=m-1;j>=max(go_lft[i][m],2);j--)//走到的是(i,j)
			ans+=query(j,1,1,n,i);
		if(go_rgt[i][1]==m)
			ans-=m-2;
	}
	memset(t,0,sizeof t);
	for(int i=2;i<m;i++)//(1,i)往下走
	{
		if(c[1][i]=='#')continue;
		for(int j=2;j<=min(n-1,go_dom[1][i]);j++)
			update(j,1,1,m,go_lft[j][i],go_rgt[j][i],1);
	}
	for(int i=2;i<m;i++)//(n,i)往上走
	{
		if(c[n][i]=='#')continue;
		for(int j=n-1;j>=max(2,go_ups[n][i]);j--)
			ans+=query(j,1,1,m,i);
		if(go_ups[n][i]==1)
			ans-=n-2;
	}
}
inline void solve_t3(void)//t3其实还挺好写的，不用担心算重
{
	memset(t,0,sizeof t);
	for(int i=2;i<n;i++)//(i,1)出发向右走
	{
		if(c[i][1]=='#')continue;
		for(int j=2;j<=min(m-1,go_rgt[i][1]);j++)
		{
			ans+=query(j,1,1,n,i);
		}
		for(int j=2;j<=min(m-1,go_rgt[i][1]);j++)
		{
			update(j,1,1,n,go_ups[i][j],i-2,1);
			update(j,1,1,n,i+2,go_dom[i][j],1);
		}
	}
	memset(t,0,sizeof t);
	for(int i=2;i<n;i++)//(i,m)出发向左走
	{
		if(c[i][m]=='#')continue;
		for(int j=m-1;j>=max(2,go_lft[i][m]);j--)
		{
			ans+=query(j,1,1,n,i);
		}
		for(int j=m-1;j>=max(2,go_lft[i][m]);j--)
		{
			update(j,1,1,n,go_ups[i][j],i-2,1);
			update(j,1,1,n,i+2,go_dom[i][j],1);
		}
	}
	memset(t,0,sizeof t);
	for(int i=2;i<m;i++)//(1,i)出发向下走
	{
		if(c[1][i]=='#')continue;
		for(int j=2;j<=min(n-1,go_dom[1][i]);j++)
		{
			ans+=query(j,1,1,m,i);
		}
		for(int j=2;j<=min(n-1,go_dom[1][i]);j++)
		{
			update(j,1,1,m,go_lft[j][i],i-2,1);
			update(j,1,1,m,i+2,go_rgt[j][i],1);
		}
	}
	memset(t,0,sizeof t);
	for(int i=2;i<m;i++)//(n,i)出发向上走
	{
		if(c[n][i]=='#')continue;
		for(int j=n-1;j>=max(2,go_ups[n][i]);j--)
		{
			ans+=query(j,1,1,m,i);
		}
		for(int j=n-1;j>=max(2,go_ups[n][i]);j--)
		{
			update(j,1,1,m,go_lft[j][i],i-2,1);
			update(j,1,1,m,i+2,go_rgt[j][i],1);
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	init();
	solve_t0();
	solve_t1();
	solve_t2();
	solve_t3();
	cout<<ans<<"\n";
}
inline void init(void)
{
	for(int i=1;i<=n;i++)//先做go_lgt go_rgt
	{
		int bk=1;
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='#')
			{
				for(int u=bk;u<j;u++)
					go_rgt[i][u]=j-1;
				bk=j+1;
			}
			else go_lft[i][j]=bk;
		}
		for(int u=bk;u<=m;u++)
			go_rgt[i][u]=m;
	}
	for(int i=1;i<=m;i++)
	{
		int bk=1;
		for(int j=1;j<=n;j++)
		{
			if(c[j][i]=='#')
			{
				for(int u=bk;u<j;u++)
					go_dom[u][i]=j-1;
				bk=j+1;
			}
			else go_ups[j][i]=bk;
		}
		for(int u=bk;u<=n;u++)
			go_dom[u][i]=n;
	}
}
```


---

