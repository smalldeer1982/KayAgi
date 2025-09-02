# Earnest Matrix Complement

## 题目背景

3, 2, 1, ... 我们是 —— RiOI 团队！

—— Felix & All, [特别感谢 3](https://www.luogu.com.cn/problem/T351681)

- Peter: 好消息，我的题目 T311013 已获批！
- $ \delta $: 幸好我的电脑没电，不然我可能参加了 wyrqwq 的比赛并得到负分。
- Felix: \[点赞\] 关于一首被删除歌曲的题目陈述！
- Aquawave: 我该为我的化学课感到悲伤吗？
- E.Space: 啊？
- Trine: 面包。
- Iris: 为什么总是我来测试题目？

时光走过，未来我们会再遇见。回首往事，大家都过上了各自想要的生活。

## 题目描述



Aquawave 有一个大小为 $ n \times m $ 的矩阵 $ A $，其中的元素只允许是 $ [1, k] $ 区间内的整数。矩阵中的一些位置已被填上整数，其余位置用 $ -1 $ 表示，代表尚未填充。

你的任务是将矩阵 $ A $ 填满所有空白位置，接着定义 $ c_{u,i} $ 为第 $ i $ 行中数字 $ u $ 出现的次数。Aquawave 将矩阵的美丽定义为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1}. $$

请找出在最佳填充方案下的矩阵 $ A $ 的最大美丽值。

## 说明/提示

在第一个测试用例中，矩阵 $ A $ 已经确定，其美丽值为：

$$ \sum_{u=1}^k \sum_{i=1}^{n-1} c_{u,i} \cdot c_{u,i+1} = c_{1,1} \cdot c_{1,2} + c_{1,2} \cdot c_{1,3} + c_{2,1} \cdot c_{2,2} + c_{2,2} \cdot c_{2,3} + c_{3,1} \cdot c_{3,2} + c_{3,2} \cdot c_{3,3} = 1 \cdot 1 + 1 \cdot 1 + 2 \cdot 0 + 0 \cdot 1 + 0 \cdot 2 + 2 \cdot 1 = 4。$$

在第二个测试用例中，可以这样填充矩阵：

$$ \begin{bmatrix} 2 & 3 & 3 \\ 2 & 2 & 3 \end{bmatrix}, $$

得到的美丽值为 $ 4 $。这可以被证明是最大的可能值。

在第三个测试用例中，以下为一种可能的最优填充方案：

$$ \begin{bmatrix} 1 & 1 & 1 \\ 1 & 2 & 1 \\ 1 & 1 & 4 \end{bmatrix}. $$

在第四个测试用例中，下面是一种可能的最优配置：

$$ \begin{bmatrix} 1 & 3 & 2 & 3 \\ 1 & 3 & 2 & 1 \\ 3 & 1 & 5 & 1 \end{bmatrix}. $$

在第五个测试用例中，以下是一种可能的最优填充：

$$ \begin{bmatrix} 5 & 5 & 2 \\ 1 & 8 & 5 \\ 7 & 5 & 6 \\ 7 & 7 & 4 \\ 4 & 4 & 4 \end{bmatrix}. $$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
9
3 3 3
1 2 2
3 1 3
3 2 1
2 3 3
-1 3 3
2 2 -1
3 3 6
-1 -1 1
1 2 -1
-1 -1 4
3 4 5
1 3 2 3
-1 -1 2 -1
3 1 5 1
5 3 8
5 -1 2
1 8 -1
-1 5 6
7 7 -1
4 4 4
6 6 5
-1 -1 5 -1 -1 -1
-1 -1 -1 -1 2 -1
-1 1 3 3 -1 -1
-1 1 -1 -1 -1 4
4 2 -1 -1 -1 4
-1 -1 1 2 -1 -1
6 6 4
-1 -1 -1 -1 1 -1
3 -1 2 2 4 -1
3 1 2 2 -1 -1
3 3 3 3 -1 2
-1 3 3 -1 1 3
3 -1 2 2 3 -1
5 5 3
1 1 3 -1 1
2 2 -1 -1 3
-1 -1 -1 2 -1
3 -1 -1 -1 2
-1 1 2 3 -1
6 2 7
-1 7
-1 6
7 -1
-1 -1
-1 -1
2 2```

### 输出

```
4
4
10
10
8
102
93
58
13```

# 题解

## 作者：IvanZhang2009 (赞：6)

本题最关键的结论是：每一行只会填一种数。考虑用调整法证明，设一行填了两种数，则考虑这两种数在上下两行中的出现次数，如果不一样则显然填一种可以更优；若一样则填一种等价。

于是可以设计最简单的 dp：$f_{i,j}$ 表示第 $i$ 行的 $-1$ 全部填成 $j$ 的最大贡献。此时把贡献如此拆：两行中都不是 $-1$ 的提前算出来；设上下两行中出现 $j$ 的次数为 $co_j$，上一行和本行的问号个数为 $c_0,c_1$，则在 $f_{i,j}$ 转移时加入 $co_j\times c_1$；两行都是 $-1$ 的贡献在转移中记为 $c_0c_1$。转移为 $f_{i,j}=co_jc_1+\max f_{i-1,k}+[j=k]c_0c_1$。注意到可以提前处理出 $\max f_{i-1,k}$ 做到 $O(1)$ 转移，时间复杂度 $O(nk)$，无法通过。

我们考虑维护整个 dp 数组的变化。注意到这玩意可以变成三个可以接受的操作：

- 全局加 $c_0c_1$。

- 全局对 $\max f_{i-1,k}$ 取 $\max$。
- 对于所有有值的 $co_j$，单点加 $co_jc_1$。

按顺序做这三个操作，并实时维护 $\max$ 即可。注意到大部分操作是全局操作，我们设计一个标记 $(a_{1,\dots n},x,y)$，表示此时 $f_{j}=\max(a_j+x,y)$。考虑三种操作，全局加 $z$ 即让 $x,y$ 都加 $z$；全局对 $z$ 取 $\max$ 即令 $y$ 对 $z$ 取 $\max$。单点加的时候只需要求出当前的单点值，设做单点加后值为 $z$，注意到一定有 $z>y$，我们直接令 $a_j\leftarrow z-x$ 即可。$\max$ 与这三种操作同时维护即可。时间复杂度 $O(nm+k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
int n,m,t;
int f[4000005],X,Y,g[1000005],c[1000005];
void Main() {
	cin>>n>>m>>t;
	vector<vector<int>>a(n, vector<int>(m));
	vector<int>cnt(n);
	REP(i,0,n){
		cnt[i]=0;
		vector<int>b;
		REP(j,0,m){
			int x;cin>>x;
			if(x>0)b.pb(x-1);
			else ++cnt[i];
		}
		reverse(all(b));REP(j,0,cnt[i])b.pb(-1);
		reverse(all(b));a[i]=b;
	}
	if(n==1)over(0)
	REP(i,0,t)f[i]=0;
	int ans=0;
	REP(i,0,n-1){
		REP(j,cnt[i],m)++f[a[i][j]];
		REP(j,cnt[i+1],m)ans+=f[a[i+1][j]];
		REP(j,cnt[i],m)--f[a[i][j]];
	}
	REP(j,cnt[1],m)f[a[1][j]]+=cnt[0];
	X=Y=0;int mx=0;
	REP(i,0,t)mx=max(mx,f[i]);
	REP(i,1,n){
        vector<int>T;
        REP(j,cnt[i-1],m)T.pb(a[i-1][j]);
        if(i<n-1)REP(j,cnt[i+1],m)T.pb(a[i+1][j]);
        for(auto j:T)c[j]=0;
        for(auto j:T)++c[j];
        int co=cnt[i]*cnt[i-1];
        X+=co;Y=max(Y+co,mx);mx+=co;
        for(auto j:T)if(c[j]){
            f[j]=max(X+f[j],Y)+c[j]*cnt[i];
            mx=max(mx,f[j]);
            f[j]-=X;c[j]=0;
        }
	}
	mx=0;
	REP(j,0,t)mx=max(mx,max(f[j]+X,Y));
	over(mx+ans)
}
void TC() {
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
/*
1. CLEAR the arrays (ESPECIALLY multitests)
2. DELETE useless output
 */

```

---

## 作者：Gold14526 (赞：6)

$\rm Problem:$[Earnest Matrix Complement](https://www.luogu.com.cn/problem/CF2053F)

### 题意

给定一个 $n\times m$ 的矩阵 $A$，每个数在 $[1,k]$ 间，其中有一些数待填。

定义该矩阵的权值为：

$$\sum_x\sum_{i=1}^{n-1}cnt_{x,i}cnt_{x,i+1}$$

其中 $cnt_{x,i}$ 表示 $x$ 在第 $i$ 行出现的次数。

求填完数后该矩阵权值最大值。

$1\le n,m\le2\times10^5,1\le k\le n\times m\le6\times10^5$。

### 做法

首先发现每行只会填一种数，否则替换成上下两行出现次数总和最多的数一定不劣。

先把已知的数的贡献算出来，然后只需要考虑填的数造成的影响。

不难得到朴素 dp 方式：

设 $f_{i,j}$ 表示考虑前 $i$ 行，第 $i$ 行填的数是 $j$ 的方案数。

不难发现 $f_{i,j}$ 只会从 $f_{i-1,j}$ 或 $f_{i-1}$ 中的最大值转移过来，设这个最大值是 $mx_{i-1}$，第 $i$ 行的待填数有 $emp_i$ 个，那么可以得到转移式：

$$f_{i,j}=\max(f_{i-1,j}+emp_iemp_{i-1},mx_{i-1})+emp_i(cnt_{i-1,j}+cnt_{i+1,j})$$

（这里的 $cnt_{i,j}$ 表示在输入给出的已知数中，$j$ 在第 $i$ 行出现的次数）

式子可能有点长，我们拆成两步看：

$$f_{i,j}=\max(f_{i-1,j}+emp_iemp_{i-1},mx_{i-1})$$

$$f_{i,j}:=f_{i,j}+emp_i(cnt_{i-1,j}+cnt_{i+1,j})$$

发现第一步转移对所有的 $j$ 都一样，可以直接全局加，全局取 $\max$。

第二步总转移次数是上下两行出现数字个数之和，也就是一共 $O(nm)$ 次单点加。

所以只要维护一个能支持全局加，全局取 $\max$，单点加，求全局 $\max$ 的东西就可以了，可以用线段树之类的东西实现，不过打个全局标记就可以了，这样每次就是 $O(1)$ 的，具体可以看代码。

### 代码

一个能支持全局加，全局取 $\max$，单点加，求全局 $\max$ 的东西：

```cpp
namespace A{
	ll addtag,maxtag;
	ll a[600001];
	ll mx;
	void clear()
	{
		for(int i=1;i<=k;++i)a[i]=0;
		addtag=maxtag=mx=0;
	}
	void alladd(cll x)
	{
		addtag+=x;
		maxtag+=x;
	}
	void allmax(cll x)
	{
		maxtag=max(maxtag,x);
	}
	void add(cint x,cll y)
	{
		a[x]=max(a[x],maxtag-addtag);
		a[x]+=y;
		mx=max(mx,a[x]);
	}
	ll ask()
	{
		return max(maxtag,mx+addtag);
	}
}
```

dp 部分：

```cpp
for(int i=1;i<=n;++i)
{
	cll lstans=A::ask();
	A::alladd(1ll*emp[i]*emp[i-1]);
	A::allmax(lstans);
	for(int x:a[i-1])
	{
		if(x==-1)continue;
		A::add(x,emp[i]);
	}
	if(i<n)
	{
		for(int x:a[i+1])
		{
			if(x==-1)continue;
			A::add(x,emp[i]);
		}
	}
}
```

提交记录：

[submission](https://codeforces.com/contest/2053/submission/298883196)

---

## 作者：littlebug (赞：4)

我们注意力惊人。

## Solution

显然有一个显然的结论：一行只能填同一种数，因为对于一个位置，填上一行加下一行出现次数最多的数一定不比填别的数更劣。

先不管复杂度，列出一个朴素的方程，设 $f_{i,j}$ 为只考虑前 $i$ 行，第 $i$ 行填 $j$ 的答案，则考虑上一行填的数是否与这一行相同，设 $c_{i,j}$ 为第 $i$ 行已经确定的数中 $j$ 的个数，$d_i$ 为第 $i$ 行空位的个数，则有：

$$f_{i,j} = \max _x (f_{i-1,x} + [x=j] \times d_i d_{i-1}) + d_i \times (c_{i-1,j} + c_{i+1,j})$$

但是这样复杂度 $O(nk)$ 是爆炸的，我们注意到（？）可以只维护 $f_j$，用某种方式进行 $i-1 \to i$ 的转移。

我们再次注意到（！），上面的式子可以拆成三个操作：

1. $\forall j : f_{i,j} \gets f_{i-1,j} + d_i d_{i-1}$。
2. $\forall j : f_{i,j} \gets \max \limits _j (f_{i-1,j})$。
3. $\forall a_{i \pm 1,j} \ne -1 : f_{a_{i \pm 1,j}} \gets f_{a_{i \pm 1,j}} + d_i$。

可以直接线段树，但是我们讨厌 ds，于是我们再再次注意到（……），操作一可以维护全局加法 tag，操作二可以维护全局最大值 tag，操作三需要支持单点加，可以直接用关于加法 tag 的偏移量解决。最后最大值为**全局最大值 tag** 和**每一次单点加后的最大值**的最大值。

## Code

```cpp
int n,m,k;
vector < vector<int> > a;
int d[MAXN],c[MAXN];

class segtree
{
public:
    int f[MAXN],maxtag=0,addtag=0,mx=0;

    il void clr()
    {
        rep(i,0,k+1) f[i]=0;
        maxtag=addtag=mx=0;
    }

    il void alladd(int k)
    {
        maxtag+=k,addtag+=k;
    }

    il void allmax(int k)
    {
        maxtag=max(maxtag,k);
    }

    il void add(int p,int k)
    {
        f[p]=max(f[p],maxtag-addtag)+k;
        mx=max(mx,f[p]);
    }

    il int q()
    {
        return max(mx+addtag,maxtag);
    }
} tr;

il void solve(int __Ti)
{
    clr(a);

    read(n,m,k);

    tr.clr();
    rep(i,0,max(n,k)+1) d[i]=c[i]=0;
    
    a.resize(n+5);
    rep(i,0,n+1) a[i].resize(m+5);
    rep(i,1,n) rep(j,1,m) read(a[i][j]),a[i][j]==-1 && (++d[i]);

    int ans=0;
    rep(i,1,n)
    {
        rep(j,1,m) a[i][j]!=-1 && (c[a[i][j]]=0);
        rep(j,1,m) i-1>=1 && a[i-1][j]!=-1 && (++c[a[i-1][j]]);
        rep(j,1,m) a[i][j]!=-1 && (ans+=c[a[i][j]]);
    }

    int qwq;
    rep(i,1,n)
    {
        qwq=tr.q();
        tr.alladd(d[i-1]*d[i]);
        tr.allmax(qwq);

        rep(j,1,m)
        {
            i-1>=1 && a[i-1][j]!=-1 && (tr.add(a[i-1][j],d[i]),1);
            i+1<=n && a[i+1][j]!=-1 && (tr.add(a[i+1][j],d[i]),1);
        }
    }

    write(ans+tr.q(),'\n');
}
```

但是呢，由于我们注意力惊人，所以直接输出「华风夏韵 洛水天依」~~不~~可以 AC 此题。

---

## 作者：Temp113 (赞：3)

## Solution

结论：对于每一行，都存在一个最优解，使新填入的数字相同。

证明：固定第 $i-1$ 和第 $i+1$ 行，一个新数字 $u$ 会带来 $c_{u,i-1}+c_{u,i+1}$ 的贡献，任意一行都是如此。

考虑 dp。设 $f_{i,j}$ 表示第 $i$ 行的 $-1$ 变成 $j$ 时，前 $i$ 行能达到的最大贡献（忽略初始贡献），$c_i$ 表示第 $i$ 行中 $-1$ 的个数，$d_{i,j}$ 表示最初第 $i$ 行中 $j$ 的个数。

转移方程如下：

$f_{i, j} = \max(\max\limits_{1 \leq w \leq k}(f_{i-1, w} + c_i \cdot d_{i-1, w} + c_{i-1} \cdot d_{i-1, j}), f_{i-1, j} + (d_{i, j} + c_i) \cdot (d_{i-1, j} + c_{i-1}) - d_{i, j}d_{i-1, j})$

此方法稍加优化，就可在 $\mathcal O(nk)$ 内解决。

对于相同的 $i$，只有 $\mathcal O(m)$ 个 $j$ 使 $d_{i,j} \neq 0$。

如果 $d_{i,j}=0$，且 $d_{i-1,j}=0$，则转移方程可变作：

$f_{i,j} = \max(\max\limits_{1 \leq w \leq k}(f_{i-1, w}), f_{i-1, j} + c_i \cdot c_{i-1})$

这可以看作 $x \gets \max(a, x + b)$ 的全局修改，可以 $\mathcal O(1)$ 求出。否则，更新 $\mathcal O(m)$ 个位置的新 $dp_j$。

因此，可在 $\mathcal O(nm)$ 内解决。 

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, K = 6e5 + 5;
int t, n, m, k, a[N], b[N], dp[K], res1, res2, tmp1[K], tmp2, x, y, z, maxx, vis[K], ans, cnt;
vector<int> cnt1(K + 5), cnt2(K + 5);
inline int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
inline int get(int aa){
	return ((~aa) ? aa : 0);
}
void read_2(){
	for(int i = 1; i <= m; i++) cnt2[get(b[i])]--;
	for(int i = 1; i <= m; i++){
		cin >> b[i];
		cnt2[get(b[i])]++;
	}
	res2 = cnt2[0];
	return ;
}
void roll(){
	for(int i = 1; i <= m; i++){
		tmp1[i] = b[i];
		b[i] = a[i];
		a[i] = tmp1[i];
	}
	swap(cnt1, cnt2);
	tmp2 = res2;
	res2 = res1;
	res1 = tmp2;
	return ;
}
void solve(){
	cnt++;
	cin >> n >> m >> k;
	for(int i = 0; i <= k; i++) dp[i] = cnt1[i] = cnt2[i] = vis[i] = 0;
	for(int i = 1; i <= m; i++) a[i] = b[i] = 0;
	res1 = res2 = x = y = z = maxx = ans = 0;
	cnt1[0] = cnt2[0] = m;
	read_2();
	roll();
	for(int i = 2; i <= n; i++){
		read_2();
		maxx = max_(x, y + z);
		for(int j = 1; j <= m; j++){
			if(~a[j]) maxx = max_(maxx, max_(x, dp[a[j]] + z) + res1 * cnt2[a[j]]);
			if(~b[j]) maxx = max_(maxx, max_(x, dp[b[j]] + z) + res1 * cnt2[b[j]]);
		}
		for(int j = 1; j <= m; j++){
			if((~a[j]) && vis[a[j]] != i){
				vis[a[j]] = i;
				ans += cnt1[a[j]] * cnt2[a[j]];
				dp[a[j]] = max_(x, dp[a[j]] + z) + res1 * cnt2[a[j]] + res2 * cnt1[a[j]] - z;
				dp[a[j]] = max_(dp[a[j]], maxx - res1 * res2 + res2 * cnt1[a[j]] - z);
				y = max_(y, dp[a[j]]);
			}
		}
		for(int j = 1; j <= m; j++){
			if((~b[j]) && vis[b[j]] != i){
				vis[b[j]] = i;
				dp[b[j]] = max_(x, dp[b[j]] + z) + res1 * cnt2[b[j]] + res2 * cnt1[b[j]] - z;
				dp[b[j]] = max_(dp[b[j]], maxx - res1 * res2 + res2 * cnt1[b[j]] - z);
				y = max_(y, dp[b[j]]);
			}
		}
		x = max_(maxx, x + res1 * res2);
		z += res1 * res2;
		roll();
	}
	cout << max_(x, y + z) + ans << '\n';
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cin >> t;
	for(int kk = 1; kk <= t; kk++) solve();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

对于每一行的 $-1$，显然只会填一种数字，因此可以得出一种比较朴素的 DP。设 $f_{i,j}$ 表示考虑前 $i$ 行，第 $i$ 行的 $-1$ 变为 $j$ 时的最大值，再设 $d_{i,j}$ 表示第 $i$ 行数字 $j$ 的个数，则可列出转移方程：

$$
f_{i,j} = \max \limits _{o = 1} ^ k\{f_{i - 1,o} + d_{i - 1,-1} \times d_{i,o} + d_{i - 1,-1} \times d_{i,-1}\} + d_{i - 1,j} \times d_{i,j} + d_{i - 1,j} \times d_{i,-1}
$$

由于 $d$ 数组可以预处理获得，于是就得到了 $O(nk)$ 的算法。

进一步观察这个方程，发现方程中与 $j$ 无关的量可以直接用线段树区间加处理，与 $j$ 相关的直接单点加（每一行最多只需要 $O(m)$ 次）。于是可以用有区间加，单点加，单点取最大值，最后维护区间最大值的数据结构实现。这里用两个懒标记的线段树去实现，每一次标记下传的时候，加法的懒标记直接累加，而最大值的懒标记需要先作加法后再取最值。最后我们就能得到 $O(nm \log (k))$ 的算法：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 6e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
map <ll,ll> mp[2];
ll tree[MAX << 2],tmp[MAX << 2],mx[MAX << 2];
int t,n,m,k;
void modify (int cur,int l,int r,int x,int y,pair <ll,ll> p);
void pushdown (int cur);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();m = read ();k = read ();mp[0].clear ();
		vector <vector <ll> > a (n + 5, vector <ll> (m + 5));
		for (int i = 1;i <= n;++i)
			for (int j = 1;j <= m;++j) a[i][j] = read ();
		for (int i = 1;i <= n;++i)
		{
			for (int j = 1;j <= m;++j) ++mp[1][a[i][j]];
			for (auto v : mp[1]) 
				if (v.first != -1) modify (1,1,k,v.first,v.first,{mp[0][-1] * v.second,0});
			int mx = tree[1];
			modify (1,1,k,1,k,{mp[0][-1] * mp[1][-1],0});
			modify (1,1,k,1,k,{0,mx});
			for (auto v : mp[1]) 
				if (v.first != -1) modify (1,1,k,1,k,{mp[0][v.first] * mp[1][v.first],0});
			for (auto v : mp[0]) 
				if (v.first != -1) modify (1,1,k,v.first,v.first,{mp[1][-1] * v.second,0});
			mp[0].clear (); 
			for (auto v : mp[1]) mp[0][v.first] = v.second;
			mp[1].clear ();
		}
		printf ("%lld\n",tree[1]);
		for (int i = 0;i <= 4 * k;++i) tree[i] = tmp[i] = mx[i] = 0;
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void pushdown (int cur) // 注意是先作加法后取 max
{
	tree[cur << 1] = max (tree[cur << 1] + tmp[cur],mx[cur]);
	tree[cur << 1 | 1] = max (tree[cur << 1 | 1] + tmp[cur],mx[cur]);
	tmp[cur << 1] += tmp[cur],tmp[cur << 1 | 1] += tmp[cur];
	mx[cur << 1] = max (mx[cur << 1] + tmp[cur],mx[cur]);mx[cur << 1 | 1] = max (mx[cur << 1 | 1] + tmp[cur],mx[cur]);
	tmp[cur] = mx[cur] = 0;
} 
void modify (int cur,int l,int r,int x,int y,pair <ll,ll> p)
{
	if (x <= l && y >= r)
	{
		tmp[cur] += p.first;mx[cur] = max (mx[cur] + p.first,p.second);
		tree[cur] = max (tree[cur] + p.first,p.second);
		return ;	
	}
	int mid = (l + r) >> 1;
	pushdown (cur);
	if (x <= mid) modify (cur << 1,l,mid,x,y,p);
	if (y > mid) modify (cur << 1 | 1,mid + 1,r,x,y,p);
	tree[cur] = max (tree[cur << 1],tree[cur << 1 | 1]);
}
```

---

## 作者：Enoch006 (赞：1)

一篇使用线段树的套路题解。

首先，一个结论是一定有一个最优解满足**每一行新填入的数字全部相同**。

感性理解的话就是在上一行和下一行固定时，这一行一定能找到一个数使贡献最大。

接着，对于每一行定义 $f_i$ 表示这一行全填 $i$ 这个数，这一行前的最大值；$c_i$ 表示这一行原有的每个数的数量；$sum$ 表示这一行 $-1$ 的个数。

对于上一行我们也类似地定义 $lastf_i$，$lastc_i$，$lastsum$。

最后，我们定义 $basic$ 表示这一行与上一行之间原本有的数之间的贡献。

现在，你可以获得一个 $O(nk^2)$ 的状态转移方程：

$$f_{i}=basic+\begin{cases}lf_{i}+c_i\cdot lsum+lc_i\cdot sum+lsum\cdot sum\\lf_{j}+c_j\cdot lsum+lc_i\cdot sum&\end{cases}$$

可以提出 $lc_i\cdot sum$ 状态转移方程变为：

$$f_{i}=basic+lc_i\cdot sum+\begin{cases}lf_{i}+c_i\cdot lsum+lsum\cdot sum\\lf_{j}+c_j\cdot lsum&\end{cases}$$

预处理 $lf_j+c_j\cdot lsum$，时间复杂度优化为 $\mathcal{O}(nk)$，但仍然不能通过此题。

注意到如果这一行与上一行都没有的一个数 $i$，那么状态转移方程变为：

$$f_{i}=basic+\begin{cases}lf_{i}+lsum\cdot sum\\lf_{j}+c_j\cdot lsum&\end{cases}$$

也就是说，在这种情况下，方程只需要进行两种操作：

1. 全局加。
2. 全局取 $\max$。
3. 全局查 $\max$。

而对于这一行或上一行有的数，可以直接 $\mathcal{O}(m)$ 暴力修改。

对于值域上的 DP，我们套路地考虑使用线段树优化。

可以将原本的条件强化为：

1. 区间加。
2. 区间取 $\max$。
3. 区间查 $\max$。

当然你可以使用 Beats 去维护，这里提供一种二元懒标记维护的方法。

---

考虑维护二元懒标记 $(a,b)$ 表示 $x\to \max(x+a,b)$。

1. 如何合并懒标记：

设原有懒标记 $(a,b)$，现在有新的懒标记 $(c,d)$，考虑对于原来的数 $x$ 发生了什么变化：

$x\to \max(x+a,b)\to\max(\max(x+a,b)+c,d)$

化简最后的式子：

$\max(\max(x+a,b)+c,d)=\max(\max(x+a+c,b+d),d)=\max(x+a+c,\max(b+c,d))$

合并后 $x\to\max(x+a+c,\max(b+c,d))$，因此，懒标记变为 $(a+c,\max(b+c,d))$。

2. 区间加 $x$：

在线段树对应区间加入懒标记 $(x,0)$ 即可。

3. 区间 chkmax $x$：

在线段树对应区间加入懒标记 $(0,x)$ 即可。

最后的最后，代码：


```cpp
#include <bits/stdc++.h>
#define int long long 
#define um map
#define maxm 600005
#define maxn 1005
#define inf 0x3f3f3f3f
using namespace std;
int T,n,m,k,ans;
um<int,int>c,lc,tmp;
#define pii pair<int,int>
#define mp make_pair 
#define fi first
#define se second
struct Seg{
    int l,r,mx;
    pii lz;
}t[maxm<<2];
#define ls k<<1
#define rs k<<1|1
void Pushup(int k){t[k].mx=max(t[ls].mx,t[rs].mx);}
void Pushtag(pii &x,pii y){
	x.fi+=y.fi;
	x.se=max(x.se+y.fi,y.se);
} 
void Pushdown(int k){
	t[ls].mx=max(t[ls].mx+t[k].lz.fi,t[k].lz.se);
	t[rs].mx=max(t[rs].mx+t[k].lz.fi,t[k].lz.se);
	Pushtag(t[ls].lz,t[k].lz);
	Pushtag(t[rs].lz,t[k].lz);
	t[k].lz=mp(0,0);
}
void Build(int k,int l,int r){
    t[k]=(Seg){l,r,0,mp(0,0)};
    if(l==r)return;
    int mid=l+r>>1;
    Build(ls,l,mid);
    Build(rs,mid+1,r);
}
void Modify(int k,int l,int r,pii x){
    if(t[k].l>r||t[k].r<l)return;
    if(t[k].l>=l&&t[k].r<=r){
		Pushtag(t[k].lz,x);
		t[k].mx=max(t[k].mx+x.fi,x.se);
		return;
	}
    Pushdown(k);
    Modify(ls,l,r,x);
    Modify(rs,l,r,x);
    Pushup(k);
}
int Ask(int k,int l,int r){
    if(t[k].l>r||t[k].r<l)return -inf;
    if(t[k].l>=l&&t[k].r<=r)return t[k].mx;
    Pushdown(k);
    int mx=max(Ask(ls,l,r),Ask(rs,l,r));
    Pushup(k);
    return mx;
}
vector<int>s;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;ans=0;
        int lsum=0,sum=0;
        Build(1,1,k);
        um<int,int>().swap(lc);
        for(int i=1;i<=n;i++){
            sum=0;s.clear();
            um<int,int>().swap(c);
            um<int,int>().swap(tmp);
            for(int j=1;j<=m;j++){
                int x;cin>>x;
                if(x==-1)sum++;
                else c[x]++,s.push_back(x); 
            }
            int basic=0,mx=t[1].mx;
            for(auto f:c){
                int i=f.fi;basic+=c[i]*lc[i];
                mx=max(mx,Ask(1,i,i)+c[i]*lsum);
            }
            for(auto f:c){
                int i=f.fi;
                tmp[i]=basic+lc[i]*sum+max(mx,
                Ask(1,i,i)+(sum+c[i])*lsum);
            }
            for(auto f:lc){
                int i=f.fi;
                tmp[i]=basic+lc[i]*sum+max(mx,
                Ask(1,i,i)+(sum+c[i])*lsum);
            }
            Modify(1,1,k,mp(lsum*sum,0));
            Modify(1,1,k,mp(0,mx));
            Modify(1,1,k,mp(basic,0));
            for(auto f:c){
                int i=f.fi;
                Modify(1,i,i,mp(0,tmp[i]));
            }
            for(auto f:lc){
                int i=f.fi;
                Modify(1,i,i,mp(0,tmp[i]));
            }
            um<int,int>().swap(lc);
            for(int x:s)lc[x]++;
			lsum=sum;
        }
        cout<<t[1].mx<<"\n";
    }
    return 0;
}
```

---

## 作者：luanyanjia (赞：1)

~~我也不知道显不显然~~，有一个重要性质是：一定存在一种最优方案，使得每一行的 $-1$ 填的都是同一个数。

证明的话直接调整即可，假设现在我们有一个最优方案，并且第 $i$ 行填着不同的数，我们将每一种颜色 $u$，按 $c_{u,i-1} + c_{u,i+1}$ 排个序，意思就是每多一个颜色 $u$ 都会加上面的贡献，将其他颜色都调整为一个 $c_{u,i-1} + c_{u,i+1}$ 最大的颜色，答案一定不会变小。

这样就好办了。设 $f_{i,j}$ 为第 $i$ 行中所有空位填的都是颜色 $j$ 的最大权值。直接列出转移方程：

设 $a_i$ 为第 $i$ 行中 $-1$ 的数量，$b_{i,j}$ 为第 $i$ 行中颜色 $j$ 的数量。

 $$ f_{i,j} = \max_{c=1}^{k}(f_{i-1,c} + b_{i,c} \times a_{i-1} + a_i \times a_{i-1}[j = c]) + b_{i-1,j} \times a_i $$

简单研究一下这个式子，发现其中只有 $O(m)$ 次单点加，全局加和全局取 $\max$。然后维护全局 $\max$。此时我的大脑已经停转了，直接上线段树维护即可，时间复杂度 $O(nm\log{k})$。

### 代码

```cpp
#include<bits/stdc++.h>
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	int ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
#define pii std::pair<int,int>
#define fir first
#define sec second
typedef long long ll;
const int N=6e5+5;
int T,n,m,k;
std::map<int,int> mp[N];
struct node{ll val,tg,mx;}t[N<<2];
inline void Addtag(int i,ll tg,ll mx){
	t[i].val=std::max(t[i].val,mx)+tg;
	t[i].mx=std::max(t[i].mx,mx-t[i].tg);
	t[i].tg+=tg;
}
inline void PushDown(int i){
	if(t[i].tg||t[i].mx){
		Addtag(i*2,t[i].tg,t[i].mx);
		Addtag(i*2+1,t[i].tg,t[i].mx);
		t[i].tg=t[i].mx=0;
	}
}
inline void PushUp(int i){
	t[i].val=std::max(t[i*2].val,t[i*2+1].val);
}
void Build(int i,int l,int r){
	t[i].tg=t[i].mx=t[i].val=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	Build(i*2,l,mid);Build(i*2+1,mid+1,r);
}
void Update(int i,int l,int r,int x,ll v){
	if(l==r)return t[i].val+=v,void();
	int mid=(l+r)>>1;PushDown(i);
	if(x<=mid)Update(i*2,l,mid,x,v);
	else Update(i*2+1,mid+1,r,x,v);
	PushUp(i);
}
inline void Solve(){
	rd(n,m,k);
	Build(1,1,k);
	for(int i=1;i<=n;i++){
		mp[i].clear();
		for(int j=1;j<=m;j++){
			int x;rd(x);
			++mp[i][x];
		}
		if(i==1)continue;
		for(pii p:mp[i]){
			if(p.fir<0)continue;
			Addtag(1,1ll*p.sec*mp[i-1][p.fir],0);
			Update(1,1,k,p.fir,1ll*p.sec*mp[i-1][-1]);
		}
		ll tmp=t[1].val;
		Addtag(1,1ll*mp[i][-1]*mp[i-1][-1],0);
		Addtag(1,0,tmp);
		for(pii p:mp[i-1]){
			if(p.fir<0)continue;
			Update(1,1,k,p.fir,1ll*p.sec*mp[i][-1]);
		}
	}
	printf("%lld\n",t[1].val);
}
signed main(){
	rd(T);
	while(T--)Solve();
	return 0;
}
```

---

## 作者：_lmh_ (赞：0)

引理：存在一组最优解使得每一行行内填的数都相等。

证明：考虑调整法。每次选一个不满足要求的行，将里面的数全部改成两边序列拼一起的众数，这样所有数就相等了，且显然不劣。

然后你发现直接做是没有前途的，考虑 dp。令 $f_{i,j}$ 为前 $i$ 行已经填完了，第 $i$ 行全部是 $j$，已经确定的部分的最大答案。

用线段树维护。每次转移需要做三件事：

$f_{i-1,j}\to f_{i,j}$：全局加上 $i-1,i$ 行内空位数量乘积。

$f_{i-1,j}\to f_{i,k}$：记录 $f_{i-1}$ 中最大值，全局取 $\max$。

算出初始确定的位置和刚才填的位置相等带来的贡献：枚举上下两行所有确定的数，单点修改。

然后这个数据结构需要支持全局取 $\max$ 全局加单点修改，代码里使用了线段树，实际上可以用一个数组做。不同实现的复杂度介于 $O(nm)$ 和 $O(nm\log nm)$ 之间。

讲一下（线段树的）实现细节吧。看到取 $\max$ 和区间修改第一印象可能是 Segment Tree Beats，细看一下发现根本没有区间求和，只有全局查询最大值。

那就很好做了，开三个变量记录最大值，$\max$ 懒标记和加法懒标记（注意先取 $\max$ 再加），然后区间取 $\max$ 打标记的时候记得把这个值减去加法懒标记，更多细节可参考代码。把这个东西优化到用数组直接做的话需要记录每个节点完成了多少标记，读者可以自行实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=600007;
ll T,n,m,k,ans,rem[N],val[N<<2],taga[N<<2],tagm[N<<2];
map<ll,ll> mp[N];
void add(int u,ll v){val[u]+=v;taga[u]+=v;}
void chmax(int u,ll v){val[u]=max(val[u],v);tagm[u]=max(tagm[u],v-taga[u]);}
void pushdown(int u){
	if (tagm[u]){
		chmax(lson,tagm[u]);chmax(rson,tagm[u]);tagm[u]=0;
	}
	if (taga[u]){
		add(lson,taga[u]);add(rson,taga[u]);taga[u]=0;
	}
}
void build(int u,int l,int r){
	val[u]=taga[u]=tagm[u]=0;
	if (l==r) return;
	int mid=l+r>>1;
	build(lson,l,mid);build(rson,mid+1,r);
}
void modify(int u,int l,int r,int x,int v){
	if (l==r){val[u]+=v;return;}
	int mid=l+r>>1;pushdown(u);
	if (x<=mid) modify(lson,l,mid,x,v);
	else modify(rson,mid+1,r,x,v);
	val[u]=max(val[lson],val[rson]);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k;ans=0;
		for (int i=1,a;i<=n;++i){
			rem[i]=0;
			for (int j=1;j<=m;++j){
				cin>>a;
				if (~a) ++mp[i][a];
				else ++rem[i];
			}
		}
		build(1,1,k);
		for (auto p:mp[2]) modify(1,1,k,p.first,rem[1]*p.second);
		for (int i=2;i<=n;++i){
			ll v=val[1];
			add(1,rem[i-1]*rem[i]);
			chmax(1,v);
			for (auto p:mp[i-1]) modify(1,1,k,p.first,rem[i]*p.second);
			for (auto p:mp[i+1]) modify(1,1,k,p.first,rem[i]*p.second);
			for (auto p:mp[i]) if (mp[i-1].find(p.first)!=mp[i-1].end()) ans+=p.second*mp[i-1][p.first];
		}
		cout<<ans+val[1]<<'\n';
		for (int i=1;i<=n;++i) mp[i].clear();
	}
	return 0;
}
```

---

## 作者：Erine (赞：0)

As a tester,

Tags: greedy, dp. *2300.

考虑一件事：对于一行的所有 $-1$，显然都要填成同一个数。原因是我一定可以选择把某个不同的数修改为已经存在的数更优。

把已经存在的数的贡献先算了，后面默认不统计。设第 $i$ 行有 $b_i$ 个 $-1$，$cnt_{i,c}$ 个 $c$。

发现剩下的没有什么可以贪的性质，直接硬上 dp，$f_{i,c}$ 表示第 $i$ 行填的颜色是 $c$ 的最大答案，转移枚举上一行填了 $d$。如果 $c\neq d$，造成的贡献是 $cnt_{i,d}b_{i-1}+cnt_{i-1,c}b_i$；否则贡献还要额外加上 $b_{i-1}b_i$。

这是一个 $\Theta(nk^2)$，写出来发现 $c\neq d$ 的转移形式相同，而且缩放到全部 $c$ 也不会产生影响（因为 $c=d$ 贡献更小），所以可以优化做到 $\Theta(nk)$。然后观察每行的转移在 $c$ 这一维上实际上干了什么：

- $\Theta(m)$ 次单点加
- 求全局 $\max$
- 全局加
- 全局对某个数取 $\max$
- $\Theta(m)$ 次单点加

发现使用 segbeats 可以解决，贺一个最假女选手就过了、。复杂度 $\Theta(nm\log k)$。

---

