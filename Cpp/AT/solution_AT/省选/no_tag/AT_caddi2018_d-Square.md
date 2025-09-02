# Square

## 题目描述

[problemUrl]: https://atcoder.jp/contests/caddi2018/tasks/caddi2018_d

高橋君は、$ N $ 行 $ N $ 列のマス目を持っています。マス目の上から $ i $ 番目、左から $ j $ 番目のマスは $ (i,j) $ で表されます。 特に、マス目の左上のマスは $ (1,1) $ であり、右下のマスは $ (N,N) $ です。

高橋君の持っているマス目のうち $ M $ 個のマスには、$ 0 $ または $ 1 $ の整数が書き込まれています。 整数が書き込まれたマスのうち $ i $ 番目のマスの情報は $ 3 $ つの整数 $ a_i,b_i,c_i $ で表され、マス $ (a_i,b_i) $ に整数 $ c_i $ が書き込まれていることを表します。

高橋君は、以下の条件を満たすように残りのマスに $ 0 $ または $ 1 $ の整数を書き込むことにしました。 書き込み方としてありうるものの個数を $ 998244353 $ で割ったあまりを求めてください。

- 任意の $ 1\leq\ i\ <\ j\leq\ N $ に対し、$ (i,i) $ を左上のマスとし $ (j,j) $ を右下のマスとするような正方形領域に書き込まれた $ 1 $ の個数が偶数である

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ min(5\ \times\ 10^4,N^2) $
- $ 1\ \leq\ a_i,b_i\ \leq\ N(1\leq\ i\leq\ M) $
- $ 0\ \leq\ c_i\ \leq\ 1(1\leq\ i\leq\ M) $
- $ i\ \neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $ である
- 入力はすべて整数である

### Sample Explanation 1

例えば、以下のような書き込み方が条件を満たします。 ``` 101 111 011 111 000 011 ```

## 样例 #1

### 输入

```
3 3
1 1 1
3 1 0
2 3 1```

### 输出

```
8```

## 样例 #2

### 输入

```
4 5
1 3 1
2 4 0
2 3 1
4 2 1
4 4 1```

### 输出

```
32```

## 样例 #3

### 输入

```
3 5
1 3 1
3 3 0
3 1 0
2 3 1
3 2 1```

### 输出

```
0```

## 样例 #4

### 输入

```
4 8
1 1 1
1 2 0
3 2 1
1 4 0
2 1 1
1 3 0
3 4 1
4 4 1```

### 输出

```
4```

## 样例 #5

### 输入

```
100000 0```

### 输出

```
342016343```

# 题解

## 作者：Lynkcat (赞：3)

简单计数题。

注意到一件事，我们选取一个在主对角线上边长大于等于 $4$ 的正方形，那么这个正方形的左下角和右上角的颜色必须一样，证明考虑两个边长为 $3$ 的正方形中间重叠着一个边长为 $2$ 的，偶数+偶数-偶数=偶数。因此如果一个点与沿主对角线对称的点组成的正方形边长大于等于 $4$，那么这两个点就锁死了。先统计这些点的染色方案数，统计是容易的。

接下来再看边长为 $2$ 的。注意到四个点异或值要为偶数，所以限制相当于要么没有限制，要么用对角线限制左下角或右上角，要么用左下角和右上角两个的值限制主对角线上相邻颜色的异或值。先记录下来对主对角线的限制。

最后处理边长为 $3$ 的，我们直接枚举主对角线上的点再枚举合法的颜色，然后去考虑 $(i-1,i+1)$ 和 $(i+1,i-1)$ 对这三个点染色的限制。用 $f_{i,j}$ 记录下主对角线上前 $i$ 个点，第 $i$ 个点染 $j$ 的方案数，然后转移一下就没了。

```c++
//我耳朵瞎掉拉~~
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 100005
using namespace std;
int n,m,x,y,z;
map<int,int>Mp[N];
int f[N][2];
int g[N];
int vis[N];
int quickPower(int x,int y)
{
	int res=1;
	while (y)
	{
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void BellaKira()
{
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		Mp[x][y]=z;
	}
	int tot=n*(n-1)/2;
	tot-=n-2;
	for (int i=1;i<=n;i++)
		for (auto u:Mp[i])
		{
			if (abs(u.fi-i)<=2) continue;
			if (!Mp[u.fi].count(i)||(Mp[u.fi][i]==u.se)) 
			{
				Mp[u.fi][i]=u.se;
				continue;
			}
			cout<<0<<endl;
			return;
		}
	for (int i=1;i<=n;i++)
		for (auto u:Mp[i])
		{
			if (abs(u.fi-i)<=2) continue;
			if (i<u.fi) tot--;
		}
	f[1][0]=1;
	f[1][1]=1;
	if (Mp[1].count(1)) f[1][Mp[1][1]^1]=0;
	f[n][0]=1;
	f[n][1]=1;
	if (Mp[n].count(n)) f[n][Mp[n][n]^1]=0;
	for (int i=1;i<=n;i++)
		for (auto u:Mp[i])
		{
			if (abs(u.fi-i)!=1) continue;
			if (!Mp[u.fi].count(i)) 
			{
				tot--;
				continue;
			}
			int x=min(u.fi,i);
			if (i>u.fi) continue;
			if (Mp[u.fi].count(i))
			{
				tot--;
				g[x]=Mp[u.fi][i]^u.se;
				vis[x]=1;
			}
		}
	for (int i=2;i<=n;i++)
	{
		if (i!=n)
		{
			for (int j=0;j<=1;j++)
			{
				if (Mp[i].count(i)&&Mp[i][i]!=j) continue;
				int x=0;
				if (!Mp[i+1].count(i-1)) x++;
				if (!Mp[i-1].count(i+1)) x++;
				if (x!=0)
				{
					f[i][j]=quickPower(2,x-1);
				} else
				{
					if ((j^Mp[i+1][i-1]^Mp[i-1][i+1])==0) f[i][j]=1;
					else f[i][j]=0;
				}
			}
		}
		if (vis[i-1])
		{
			for (int j=0;j<=1;j++)
			{
				f[i][j]=f[i][j]*f[i-1][j^g[i-1]]%mod;
			}
		} else
		{
			for (int j=0;j<=1;j++)
			{
				f[i][j]=f[i][j]*(f[i-1][0]+f[i-1][1])%mod;
			}
		}
	}
	cout<<(f[n][0]+f[n][1])%mod*quickPower(2,tot)%mod<<endl;
}
signed main()
{
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}

---

## 作者：DerrickLo (赞：1)

设最终矩阵的第 $i$ 行，第 $j$ 列是 $a_{i,j}$，我们发现对于所有满足 $i-j\ge 4$ 的 $(i,j)$ 都有 $a_{i,j}=a_{j,i}$。为什么呢？因为对于 $k\ge 2$，左上是 $(i-k,i-k)$ 而右下是 $(i,i)$ 的正方形和左上是 $(i-k,i-k)$ 而右下是 $(i-1,i-1)$ 的正方形中都有偶数个 $1$，那么两个正方形差的那一圈中也必然有偶数个 $1$。而又因为对于所有 $k\ge 2$ 都成立，所以把两个圈相减就可以得到 $a_{i,j}$ 与 $a_{j,i}$ 中有偶数个 $1$，也就等价于 $a_{i,j}=a_{j,i}$。

那么记 $f_{i,0/1}$ 表示已经填完了前 $i$ 行 $i$ 列，且 $(i,i)$ 上的数是 $0/1$ 的方案数。

考虑如何转移。我们可以枚举 $(i-1,i-1)$、$(i,i-1)$、$(i,i-2)$、$(i-1,i)$、$(i-2,i)$ 上的数，然后对于这一圈上的其他点对 $(i,j)$ 与 $(j,i)$，只需要分为都填了、填了一个和填了两个这三种情况即可。而这三种情况对应的点对个数都可以使用 `map` 预处理出来。

时间复杂度 $\mathcal O((n+m)\log m)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,m,a[50005],b[50005],c[50005],f[100005][2],cnt[100005],cnt2[100005],pw[100005];
map<pair<int,int>,int>mp,vis;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m,pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i]>>c[i],mp[{a[i],b[i]}]=c[i],vis[{a[i],b[i]}]=1;
		if(abs(a[i]-b[i])>2)cnt[max(a[i],b[i])]++;
	}
	for(int i=1;i<=m;i++)if(abs(a[i]-b[i])>2)if(vis[{a[i],b[i]}]&&vis[{b[i],a[i]}]){
		if(mp[{a[i],b[i]}]!=mp[{b[i],a[i]}])cout<<0,exit(0);
		cnt2[max(a[i],b[i])]++;
	}
	for(int i=1;i<=n;i++)cnt2[i]/=2;
	if(vis[{1,1}])f[1][mp[{1,1}]]=1;
	else f[1][0]=f[1][1]=1;
	for(int i=2;i<=n;i++)for(int j=0;j<2;j++){
		if(vis[{i,i}]&&j!=mp[{i,i}])continue;
		if(i==2){
			for(int k=0;k<2;k++)for(int a=0;a<2;a++)for(int b=0;b<2;b++){
				if(vis[{i,i-1}]&&mp[{i,i-1}]!=a)continue;
				if(vis[{i-1,i}]&&mp[{i-1,i}]!=b)continue;
				if((j+k+a+b)&1)continue;
				f[i][j]+=f[i-1][k],f[i][j]%=mod; 
			}
			continue;
		}
		int x=cnt2[i],y=cnt[i]-cnt2[i]*2,z=i-3-x-y;
		int now=pw[z],flag=0;
		int flag1=vis[{i,i-1}],pos1=mp[{i,i-1}];
		int flag2=vis[{i-1,i}],pos2=mp[{i-1,i}];
		int flag3=vis[{i,i-2}],pos3=mp[{i,i-2}];
		int flag4=vis[{i-2,i}],pos4=mp[{i-2,i}];
		for(int k=0;k<2;k++)for(int a=0;a<2;a++)for(int b=0;b<2;b++)for(int c=0;c<2;c++)for(int d=0;d<2;d++){
			if((j+k+a+b)&1)continue;
			if((j+a+b+c+d)&1)continue;
			if(flag1&&pos1!=a)continue;
			if(flag2&&pos2!=b)continue;
			if(flag3&&pos3!=c)continue;
			if(flag4&&pos4!=d)continue;
			f[i][j]+=f[i-1][k]*now,f[i][j]%=mod;
		}
	}
	cout<<(f[n][0]+f[n][1])%mod;
}
```

---

## 作者：cosf (赞：0)

先观察一下性质。从样例得出，答案应该是 $2$ 的幂，并且，如果 $m = 0$，答案应该是 $2^{\frac{n(n + 1)}{2}}$。

那么，考虑一下，什么性质使得答案是这个呢？

性质一，对于 $i = j - 1$ 的情况，可以直接判断，即 $(i, i), (i + 1, i), (i, i + 1), (i + 1, i + 1)$ 有偶数个黑格（即题中的 $1$）。

性质二，对于 $i = j - 2$ 的情况，由容斥原理，红色部分和蓝色部分的黑格总数是偶数个，那么，剩下的（副对角线）也有偶数个。

![](https://cdn.luogu.com.cn/upload/image_hosting/24phw6n5.png)

性质三，对于 $i \lt j - 2$ 的情况，红色和粉色一共有偶数个，蓝色和粉色也有偶数个，粉色单独有偶数个，因此，两个白色格子应当相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/tb6kj9gt.png)

注意到，这三个性质恰有一个格子在主对角线下，也有在主对角线上，因此，我们可以对主对角线和主对角线上的点任意染色，主对角线下的点可以唯一确定，因此任意染色的点有 $\frac{n(n + 1)}{2}$ 个，答案就是 $2^{\frac{n(n + 1)}{2}}$ 了。

接下来，考虑 $m$ 个限制。

如果 $|a - b| \gt 2$，则由性质三知 $(a, b)$ 应与 $(b, a)$ 相同。如果 $(a, b)$ 与 $(b, a)$ 均未被唯一确定，则此个限制消耗了一个任意染色次数。

如果 $|a - b| = 2$，令 $(a, b)$ 为 $\texttt{c}$ 点（$a < b$ 同理），则 $\texttt{c}, \texttt{l}, \texttt{r}$ 三点应该有偶数个黑格。如果 $\texttt{l}$ 和 $\texttt{r}$ 中有不足一个唯一确定的点，则此个限制消耗了一个任意染色次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/hfpiuapk.png)

如果 $|a - b| = 1$，令 $(a, b)$ 为 $\texttt{c}$ 点，则 $\texttt{l}, \texttt{u}, \texttt{r}, \texttt{c}$ 中有偶数个黑格。如果其中有至少一者未被唯一确定，则此个限制消耗了一个任意染色次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/we09ajo8.png)

如果 $a = b$，则 $\texttt{c} = (a, b)$ 在主对角线上。那么，$\texttt{d}, \texttt{e}, \texttt{g}, \texttt{c}$ 和 $\texttt{c}, \texttt{h}, \texttt{k}, \texttt{l}$ 满足 $2 \times 2$ 的限制，$\texttt{f}, \texttt{c}, \texttt{j}$ 满足 $3 \times 3$ 的限制。

![](https://cdn.luogu.com.cn/upload/image_hosting/40apevrc.png)

注意，在判断以上过程中，如果将 $\texttt{c}$ 唯一确定后，出现了其它的点被唯一确定（如，$2 \times 2$ 当中唯一确定了三个点），那么，就可以把它当作一个新的限制，只不过无论如何都不会消耗任意染色次数。

这个过程还应当用 dfs 实现。例如下图，假设 $m$ 个性质给定了 $\texttt{a}, \texttt{b}, \texttt{d}, \texttt{e}, \texttt{f}$ 的性质，由于 $\texttt{c}$ 在确定了 $\texttt{a}, \texttt{b}$ 或确定了 $\texttt{d}, \texttt{e}, \texttt{f}$ 之后就唯一确定了，所以这 $m$ 个操作消耗掉的任意染色次数是 $4$ 而不是 $5$。如果用 bfs 就会认为消耗了 $5$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9dzv6xr.png)

至于维护每一个点是否唯一确定，可以使用 map。这是因为，有意义的点只有 $O(m)$ 个。

最终复杂度：$O(m\log m)$。

```cpp
#include <iostream>
#include <stack>
#include <map>
using namespace std;

#define MOD 998244353ll

using ll = long long;
using pii = pair<int, int>;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

map<pii, int> mp;

struct Query
{
    int a, b, c, _;
};

ll n, m, p;

int main()
{
    cin >> n >> m;
    p = n * (n + 1) / 2 % (MOD - 1);
    stack<Query> q; // 非递归 dfs
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        q.push({a, b, c + 1, 1});
    }
    while (!q.empty())
    {
        auto [a, b, c, _] = q.top(); // _ 表示是否会消耗任意染色次数。
        q.pop();
        if (mp[{a, b}] && mp[{a, b}] != c)
        {
            cout << 0 << endl;
            return 0;
        }
        else if (mp[{a, b}])
        {
            continue;
        }
        if (abs(a - b) > 2)
        {
            mp[{a, b}] = mp[{b, a}] = c;
            p = (p + MOD - 1 - _) % (MOD - 1);
        }
        else if (abs(a - b) == 1)
        {
            /**
             * |l|u|
             * |c|r|
             */
            int l = mp[{b, b}], r = mp[{a, a}], u = mp[{b, a}];
            if (l && r && u)
            {
                if ((l + r + u + c) % 2 == 1)
                {
                    cout << 0 << endl;
                    return 0;
                }
                else
                {
                    mp[{a, b}] = c;
                }
            }
            else
            {
                mp[{a, b}] = c;
                p = (p + MOD - 1 - _) % (MOD - 1);
                if (r && u)
                {
                    q.push({b, b, (r + u + c + 1) % 2 + 1, 0});
                }
                if (u && l)
                {
                    q.push({a, a, (u + l + c + 1) % 2 + 1, 0});
                }
                if (l && r)
                {
                    q.push({b, a, (l + r + c + 1) % 2 + 1, 0});
                }
            }
        }
        else if (a - b == 2)
        {
            /**
             * | | |r|
             * | |l| |
             * |c| | |
             */
            int l = mp[{a - 1, a - 1}], r = mp[{b, a}];
            if (l && r)
            {
                if ((l + r + c + 1) % 2)
                {
                    cout << 0 << endl;
                    return 0;
                }
                else
                {
                    mp[{a, b}] = c;
                }
            }
            else
            {
                mp[{a, b}] = c;
                p = (p + MOD - 1 - _) % (MOD - 1);
                if (l)
                {
                    q.push({b, a, (l + c) % 2 + 1, 0});
                }
                if (r)
                {
                    q.push({a - 1, a - 1, (r + c) % 2 + 1, 0});
                }
            }
        }
        else if (b - a == 2)
        {
            /**
             * | | |c|
             * | |l| |
             * |r| | |
             */
            int l = mp[{b - 1, b - 1}], r = mp[{b, a}];
            if (l && r)
            {
                if ((l + r + c + 1) % 2)
                {
                    cout << 0 << endl;
                    return 0;
                }
                else
                {
                    mp[{a, b}] = c;
                }
            }
            else
            {
                mp[{a, b}] = c;
                p = (p + MOD - 1 - _) % (MOD - 1);
                if (l)
                {
                    q.push({b, a, (l + c) % 2 + 1, 0});
                }
                if (r)
                {
                    q.push({b - 1, b - 1, (r + c) % 2 + 1, 0});
                }
            }
        }
        else
        {
            /**
             * |d|e|f|
             * |g|c|h|
             * |j|k|l|
             */
            int d = mp[{a - 1, a - 1}], e = mp[{a - 1, a}], g = mp[{a, a - 1}];
            if (d && e && g)
            {
                if ((d + e + g + c) % 2)
                {
                    cout << 0 << endl;
                    return 0;
                }
                _ = 0;
            }
            int f = mp[{a - 1, a + 1}], j = mp[{a + 1, a - 1}];
            if (f && j)
            {
                if ((f + j + c + 1) % 2)
                {
                    cout << 0 << endl;
                    return 0;
                }
                _ = 0;
            }
            int h = mp[{a, a + 1}], k = mp[{a + 1, a}], l = mp[{a + 1, a + 1}];
            if (h && k && l)
            {
                if ((h + k + l + c) % 2)
                {
                    cout << 0 << endl;
                    return 0;
                }
                _ = 0;
            }
            mp[{a, a}] = c;
            p = (p + MOD - 1 - _) % (MOD - 1);
            if (d && e && !g)
            {
                q.push({a, a - 1, (d + e + c + 1) % 2 + 1, 0});
            }
            if (e && g && !d)
            {
                q.push({a - 1, a - 1, (e + g + c + 1) % 2 + 1, 0});
            }
            if (g && d && !e)
            {
                q.push({a - 1, a, (g + d + c + 1) % 2 + 1, 0});
            }
            if (f && !j)
            {
                q.push({a + 1, a - 1, (f + c) % 2 + 1, 0});
            }
            if (j && !f)
            {
                q.push({a - 1, a + 1, (j + c) % 2 + 1, 0});
            }
            if (h && k && !l)
            {
                q.push({a + 1, a + 1, (h + k + c + 1) % 2 + 1, 0});
            }
            if (k && l && !h)
            {
                q.push({a, a + 1, (k + l + c + 1) % 2 + 1, 0});
            }
            if (l && h && !k)
            {
                q.push({a + 1, a, (l + h + c + 1) % 2 + 1, 0});
            }
        }
    }
    cout << pow(2, p, MOD) << endl;
    return 0;
}
```

---

