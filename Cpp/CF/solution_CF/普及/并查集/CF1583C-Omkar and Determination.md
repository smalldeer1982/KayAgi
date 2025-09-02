# Omkar and Determination

## 题目描述

The problem statement looms below, filling you with determination.

Consider a grid in which some cells are empty and some cells are filled. Call a cell in this grid exitable if, starting at that cell, you can exit the grid by moving up and left through only empty cells. This includes the cell itself, so all filled in cells are not exitable. Note that you can exit the grid from any leftmost empty cell (cell in the first column) by going left, and from any topmost empty cell (cell in the first row) by going up.

Let's call a grid determinable if, given only which cells are exitable, we can exactly determine which cells are filled in and which aren't.

You are given a grid $ a $ of dimensions $ n \times m $ , i. e. a grid with $ n $ rows and $ m $ columns. You need to answer $ q $ queries ( $ 1 \leq q \leq 2 \cdot 10^5 $ ). Each query gives two integers $ x_1, x_2 $ ( $ 1 \leq x_1 \leq x_2 \leq m $ ) and asks whether the subgrid of $ a $ consisting of the columns $ x_1, x_1 + 1, \ldots, x_2 - 1, x_2 $ is determinable.

## 说明/提示

For each query of the example, the corresponding subgrid is displayed twice below: first in its input format, then with each cell marked as "E" if it is exitable and "N" otherwise.

For the first query:

```
<pre class="verbatim"><br></br>..X EEN<br></br>... EEE<br></br>... EEE<br></br>... EEE<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the second query:

```
<pre class="verbatim"><br></br>X N<br></br>. E<br></br>. E<br></br>. E<br></br>
```

Note that you can exit the grid by going left from any leftmost cell (or up from any topmost cell); you do not need to reach the top left corner cell to exit the grid.

```
<pre class="verbatim"><br></br><br></br>
```

For the third query:

```
<pre class="verbatim"><br></br>XX NN<br></br>X. NN<br></br>X. NN<br></br>X. NN<br></br>
```

This subgrid cannot be determined only from whether each cell is exitable, because the below grid produces the above "exitability grid" as well:

```
<pre class="verbatim"><br></br>XX<br></br>XX<br></br>XX<br></br>XX<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the fourth query:

```
<pre class="verbatim"><br></br>X N<br></br>. E<br></br>. E<br></br>. E<br></br>
```

```
<pre class="verbatim"><br></br><br></br>
```

For the fifth query:

```
<pre class="verbatim"><br></br>..XXX EENNN<br></br>...X. EEENN<br></br>...X. EEENN<br></br>...X. EEENN<br></br>
```

This query is simply the entire grid. It cannot be determined only from whether each cell is exitable because the below grid produces the above "exitability grid" as well:

```
<pre class="verbatim"><br></br>..XXX<br></br>...XX<br></br>...XX<br></br>...XX<br></br>
```

## 样例 #1

### 输入

```
4 5
..XXX
...X.
...X.
...X.
5
1 3
3 3
4 5
5 5
1 5```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：TsH_GD (赞：2)

## 讲解

题意：

给一个由 $ 0 $ 和 $ 1 $ 组成的图。

$ 0 $ 代表该位置空， $ 1 $ 代表该位置堵塞。

由空的位置出发，如果能通过走上和左走出图外，则该位置能离开。

如果由能离开和不能离开组成的图可以反推原图，则原图是确定的输入 $ x1 $  ， $ x2 $ 。

问 $ x1 $ 列到 $ x2 $ 列的图是不是确定的。

解法：当 $ x1 $ = $ x2 $ 时，全部空的点能往左走出图，所以是 `YES` 。

其他情况：

当出现：

```
01
10
```

时，会导致右下角的 $ 0 $ 无法确定，所以先找到所有的 $ 0110 $ ，记该列（左边的列）为不可确定，最后看给的范围里有没有不可确定的列即可。




## Code:
```
#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
int a[1000015],b[1000015];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t, n,q,k;
	vector<vector<int>>m;
	cin >> n >> k;
	for (int i = 0; i < n + 1; i++)a[i] = 0;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		vector<int>mm;
		for (int j = 0; j < k; j++) {
			if (s[j] == '.')mm.push_back(0);
			else mm.push_back(1);
		}
		m.push_back(mm);
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < k - 1; j++) {
			if ( m[i + 1][j] == 1 && m[i][j + 1] == 1) {
				a[j] = 1;
			}
		}
	}
	int bn = 0;
	cin >> q;
	for (int i = 0; i < k; i++)if (a[i] == 1)b[bn++] = i;
	if(bn==0)b[0] = -1;
	for (int i = 0; i < q; i++) {
		int aa, bb;
		cin >> aa >> bb;
		aa--, bb--;
		if (aa == bb || n == 1 || k == 1||bn==0)cout << "YES" << endl;
		else {
			int cc = lower_bound(b, b + bn, aa) - b;
			if (b[cc] < bb && b[cc] >= aa) {
				cout << "NO" << endl;
			} else cout << "YES" << endl;
		}
	}
	return 0;
}
```

---

## 作者：henrytb (赞：2)

观察题目性质：怎样的“能否逃出去”的情况不能确定一张图？

可以发现，若询问的那些列中出现以下形状的图案（`?` 处随意，即存在一个做下格和右上格均为 `X` 的 $2\times 2$ 矩形），那么一定不能唯一确定。

```
?X
X?
```

因为这样的 $2\times 2$ 矩形的右下角可以是 `.`，可以是 `X`，不管怎样它都是走不出去的，因此不能确定。

那么问题变成了给定的 $l\sim r$ 行中有无上面的图案。那么可以找到每个图案，发现它在哪里，然后用个前缀和维护一下。

我这里大炮打蚊子了用了个 ST 表。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,m;
string s[1000005];
bool f[1000005];
bool st[1000005][21];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    rep(i,1,n) cin>>s[i];
    rep(i,1,n-1) rep(j,1,m-1) {
        if(s[i+1][j-1]=='X'&&s[i][j]=='X') f[j]=1,st[j][0]=1;
    }
    rep(j,1,20) rep(i,1,m-1) {
        if(i+(1<<(j-1))-1>m-1) st[i][j]=st[i][j-1];
        else st[i][j]=st[i][j-1]|st[i+(1<<(j-1))][j-1];
    }
    for(cin>>_;_;--_) {
        int l,r;
        cin>>l>>r;
        if(l==r) {cout<<"YES"<<endl;continue;}
        //l~r-1
        int lg=log2(r-l);
        bool ans=st[l][lg]|st[r-(1<<lg)][lg];
        if(ans) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：1)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1583-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

看了好几遍才看懂题目。

发现如果一个格子的左边和上边都是障碍，那么这个点无法走出且无法判定是否为障碍。

于是预处理找到每一列当中是否有这样的格子，然后对于每一个输入的 $l,r$，判断是否在当中有这样的不可确定格即可。对于维护，考虑使用前缀和。

```cpp
#include<bits/stdc++.h>
#define ok puts("YES")
#define no puts("NO")
using namespace std;
const int maxn=1000010;
int q;
int n,m,l,r;
int sum[maxn];
string s[maxn];
inline void init(){
	cin>>n>>m;
	for(register int i=1;i<=n;++i) cin>>s[i];
}
int main(){
	init();
	for(register int i=2;i<=n;++i){
		for(register int j=1;j<m;++j){
			if(s[i][j-1]=='X'&&s[i-1][j]=='X') sum[j+1]++;
		}
	}
	for(register int i=2;i<=m;++i) sum[i]+=sum[i-1];
	cin>>q;
	while(q--){
		cin>>l>>r;
		if(sum[r]-sum[l]==0) ok;
		else no;
	}
}
```

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个 $n\times m$ 的地图，每次只能向上向左走。$q$ 次询问，每次询问一个区间 $[x_1,x_2]$，问将该部分形成一个新的地图并知道 $x_1$ 到 $x_2$ 列所有位置是否能走出边界，是否能唯一确定所有障碍的位置。
# 题目分析
首先无法唯一确定的情况当且仅当范围内有一个格子左边和上面在原图中都是障碍，这样这个点一定是无法走出，没办法判定是否为障碍。于是就可以提前统计每一列是否有这样的点，做一个前缀和每次判断区间 $[x_1+1,x_2]$ 是否有这样的点。当然 $x_1=x_2$ 一定能够唯一确定。

这题没给 $n$ 和 $m$ 的限制，只给了 $n\times m$ 的限制，处理方法很多，但是个人认为用 `vector` 来做最方便。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,q,s[1000001],x,y;
bool f[1000001];
vector< vector<char> >c;
int main()
{
	n=read();
	m=read();
	c.resize(n+1);
	For(i,1,n)
	{
		c[i].resize(m+1);
		For(j,1,m)
			cin>>c[i][j];
	}
	For(i,2,m)
	{
		For(j,2,n)
			if(c[j-1][i]=='X'&&c[j][i-1]=='X')
				f[i]=1;
		s[i]=s[i-1]+f[i];
	}
	q=read();
	while(q--)
	{
		x=read();
		y=read();
		if(x==y)
			puts("YES");
		else
		{
			if(s[y]-s[x])
				puts("NO");
			else
				puts("YES");
		}
	}
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# C.Omkar and Determination
这道题目首先我们会有一个很暴力的想法，

就是假如当前点 $(i,j)$ 和 $(i-1,j+1)$ 都是 `X`，

那么显然本列可以取到。

数组开不下，所以用了滚动。

然后我们发现这个暴力的复杂度显然不过关，

于是我们考虑对它进行优化。

不难发现，我们每次查询 $L$ 到 $R$ 的区间和，

可以预处理前缀和优化掉一维，

这样就将时间复杂度降到了线性。

代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,M,Now,Pre[1000001],Dp[1000001];
string S[2];
int main(void)
{
	BetterIO;
	register int i,j;cin>>N>>M;
	for(i=1;i<=N;i++)
	{
		cin>>S[Now];
		S[Now]=' '+S[Now];
		for(j=1;j<=M;j++)if(S[Now][j]=='X'&&S[1-Now][j+1]=='X')Dp[j]=1;
		Now=1-Now;
	}
	for(i=1;i<=M;i++)Pre[i]=Pre[i-1]+Dp[i];
	register int Ask;cin>>Ask;while(Ask--)
	{
		register int L,R;cin>>L>>R;
		if(L==R){puts("YES");continue;}
		register bool Flag(true);
		if(Pre[R-1]-Pre[L-1]>0)Flag=false;
		if(Flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：0)

> ### *1586C. [Omkar and Determination](https://codeforces.ml/contest/1586/problem/C)

赛时把我送走的题目。

---

**注意到**若整张图存在一个点使得其上方和左侧都是 `X` 则不合法，因为若该点既可能是 `.` 也可能是 `X`，无法确定。充分吗？如果该点上方或右方至少有一个 `.`，那么我们显然可以根据该点的 exitable 情况判断出该点的状态：若为 `Y` 则只能为 `.`，而若为 `N`，由于若该点为 `.` 则必定可以往左边和上边走，矛盾，故只能为 `X`。

把我送走的原因是我只判断了为 `.` 的点被判成 `N` 的情况，而没有注意到题目中 `X` 若为 `N` 且上下都为 `X` 则还可以被判成 `.`。

有了上述结论直接前缀和 + 差分即可，时间复杂度 $\mathcal{O}(nm+q)$。

```cpp
const int N = 1e6 + 5;

int n, m, q, sum[N];
string s[N];
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> s[i];
	for(int i = 2; i <= n; i++)
		for(int j = 1; j < m; j++)
			sum[j + 1] += s[i][j - 1] == 'X' && s[i - 1][j] == 'X';
	for(int i = 2; i <= m; i++) sum[i] += sum[i - 1];
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int x1, x2; cin >> x1 >> x2;
		cout << (sum[x2] - sum[x1] ? "No" : "Yes") << endl;
	} return 0;
}
```

---

