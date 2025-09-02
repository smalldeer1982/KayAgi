# Lucky Permutation

## 题目描述

给定整数 $n$ 和一个 $1\sim n$ 的排列 $p$。  
你可以对排列 $p$ 进行下列操作任意次：

- 选择整数 $i,j(1\leq i<j\leq n)$，然后交换 $p_i,p_j$ 的值。

你需要求出至少需要进行上述操作多少次才能使 $p$ 恰有一个逆序对。  
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
4
2
2 1
2
1 2
4
3 4 1 2
4
2 4 3 1```

### 输出

```
0
1
3
1```

# 题解

## 作者：hcywoi (赞：10)

## $\mathcal Solution$
### 【题意】

我们可以交换任意两个数，求最小操作几次能让逆序对变成 $1$。

### 【分析】

如果逆序对为 $1$ 的排列一定是:

- $2, 1,\cdots n$
- $1, 3, 2,\cdots n$
- $1, 2, 4, 3,\cdots n$
- $\cdots$

我们发现这些排列都是由 $1, 2,\cdots n$ 进行一次交换得来的。

则我们先求出排列 $p$ 变成 $1, 2,\cdots n$ 的操作次数。

我们将需要交换的位置连一条边，即 $\forall i(1\le i\le n)$ 连一条 $i\to p_i$ 的边。

那么从 $i$ 出发经过的点为 $i\to p_i\to p_{p_i}\to\cdots\to i$。

对于每个环，需要操作的次数即为 $size-1$，$size$ 表示环中的**不同**点数。

证明：

对于一个环 $\{i, p_i, p_{p_i},\cdots \}$，我们记为 $\{a_1, a_2,\cdots, a_{size}\}$。

**注意：$a_{size}\neq i$。**

则我们 $\operatorname{swap}(a_{size}, a_{size-1}), \operatorname{swap}(a_{size-1},a_{size-2}),\cdots,\operatorname{swap}(a_2, a_1)$，其中 $\operatorname{swap}(a, b)$ 表示交换 $a, b$。这样操作次数是 $size-1$。

也就是说答案为 $n-cnt$，$cnt$ 表示环的数量。

那么我们考虑什么时候是能在变成 $1, 2,\cdots, n$ 之前满足要求。

如果 $i$ 和 $i+1$ 是在一个环中，则可以在这之前满足要求。否则，就不能在之前满足要求。

[代码](https://codeforces.com/contest/1768/submission/188405927)。

---

## 作者：xiaruize (赞：3)

**思路**

考虑最小需要几步可以将原序列排序。

可以建一张图，其中边为 $i \rightarrow P_i$

此时，这张图一定是若干个环，对于每个环，令它有 $m$ 个点，必然至少需要 $m-1$ 步

所以，$最少步数 = n - 环数 = K$

那么，此时再考虑去满足题目条件，再交换任意相邻的两个即可

若相邻的两个在同一个环内，即可少做最后一次操作，需要 $K-1$ 步

否则需要额外的一次操作，需要 $K+1$ 步

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;

// bool st;
int t;
int n;
int a[N];
int vis[N];
// bool en;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        vis[i] = false;
        cin >> a[i];
    }
    bool flag = false;
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        if (!vis[x])
        {
            while (!vis[x])
            {
                res++;
                vis[x] = i;
                x = a[x];
            }
            res--;
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (vis[i] == vis[i + 1])
        {
            flag = true;
            break;
        }
    }
    if (flag)
        res--;
    else
        res++;
    cout << res << endl;
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

## 作者：LaDeX (赞：2)

题意不再简述。

首先题目要求变成逆序对只有一个的排列，也就是说，我们可以先考虑将一个排列通过交换元素变成另一个排列最小的步数，我们可以将两个排列相同位置上的数连边，很显然会形成几个环，若排列长度为 $n$，形成 $t$ 个环，每个环长为 $len_i$，则每个环交换完至少是依次交换，也就是总共需要 $\sum_{i=1}^t (len_i-1)=n-t$。所以求出步数是 $O(n)$ 的。

然后，题目要求变成的目标排列是逆序对只有一个，也就是目标排列是将升序排列中一对相邻元素交换后得到的，显然就有一个 $O(n^2)$ 的算法：枚举交换的相邻元素，计算出步数然后取最小值。

然而这并不能过此题，考虑优化，我们交换操作至多会影响两个环，也就是说，我们先对原序列和生序序列之间处理出环，然后考虑交换的位置，设交换的两个位置是 $i$ 和 $i+1$，通过手玩可以发现：当 $i$ 和 $i+1$ 在同个环内时，交换操作会把这个环一分为二，总步数会减一；反之，当 $i$ 和 $i+1$ 在不同环内时，交换操作会把两个环合二为一，总步数加一。所以我们通过并查集维护是否在同环之内，先预处理出原序列与升序序列之间的环，然后考虑交换操作，$O(1)$ 求出每次交换后总答案，最后取最小值，时间复杂度 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e5 + 10;

int n, A[N], T[N], id[N], bel[N], fa[N], cnt[N];

int Find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}

int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> A[i]; fa[i] = i; cnt[i] = 1;
		}
		for (int i = 1; i <= n; i ++) {
			if (Find(A[i]) != Find(i)) {
				cnt[Find(i)] += cnt[Find(A[i])]; cnt[Find(A[i])] = 0;
				fa[Find(A[i])] = Find(i);
			}
		}
		int S = 0, Ans = 1e9;
		for (int i = 1; i <= n; i ++) 
			if (fa[i] == i) S += cnt[i] - 1;
		for (int i = 1; i < n; i ++) {
			if (Find(i) == Find(i + 1)) Ans = min(Ans, S - 1);
			else Ans = min(Ans, S + 1);
		}
		cout << Ans << "\n";
	}
	return 0;
} 
```

---

## 作者：ダ月 (赞：2)

### 题意概要：

给定长度为 $n$ 的排列 $p$（~~这比赛怎么这么喜欢排列~~），可以选择其中任意两个数进行交换，使得操作完的后排列 $p$ 只存在一对逆序对。

### 题意分析：

我们先考虑不存在逆序对的情况，就是序列从小到大排序。

将 $i$ 与 $p_i$ 进行连边，发现整个序列变成了几个大大小小的环。而对于每个长度为 $k$ 的环，我们只需要 $k-1$
次操作就能让序列归位。最后共操作 $ans$ 次就让排列升序。

- 若存在相邻元素在同一环上，当前环就减少一次操作次数，答案就是 $ans-1$。

- 否则升序完在随意交换一组相邻元素，答案就是 $ans+1$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
const int N=2e5+10;
int n;
int f[N];
int c[N];
int dfs(int x,int id){
	c[x]=id;
	if(!c[f[x]]) return dfs(f[x],id)+1;
	else return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&f[i]);
		int ans=0;
		bool flag=false;
		int id=0;
		for(int i=1;i<=n;i++)
			if(!c[i]) ans+=dfs(i,++id);
		for(int i=1;i<n;i++)
			if(c[i]==c[i+1]){
				printf("%d\n",ans-1);
				flag=true;
				break;
			}
		if(!flag) printf("%d\n",ans+1);
		for(int i=1;i<=n;i++) c[i]=0;//不要memset
	}return 0;
}
```


时间复杂度：$O(n)$

---

## 作者：yeshubo_qwq (赞：2)

## Description

给定一个长度为 $n$ 的排列 $a$，一次操作可以交换任意两个位置的数，问最少需要多少次操作可以使排列 $a$ 恰好有 $1$ 个逆序对。

## Solution

首先考虑有 $0$ 个逆序对的情况。

这时排列一定为 $1,2,3\dots n$。

求最少操作数是一个经典的并查集。

现在考虑有 $1$ 个逆序对的情况。

容易发现，此时排列一定是在有 $0$ 个逆序对的情况下交换了任意相邻两个位置。

在有 $0$ 个逆序对的基础上多做一次即可，但不一定是最优解。

因为逆序对两个数的位置一定相邻，所以判断是否存在相邻两个数在同一个环上，如果存在就可以直接在 $0$ 个逆序对的基础上少做一次了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,i,ans,res,a[N],fa[N];
int find(int x){return fa[x]=(fa[x]==x?x:find(fa[x]));}
void merge(int x,int y){fa[find(x)]=find(y);}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>n,ans=0,res=0;
		for (i=1;i<=n;i++) cin>>a[i],fa[i]=i;
		for (i=1;i<=n;i++) merge(a[i],i);
		for (i=1;i<=n;i++) res+=(find(i)==i);
		ans=(res=n-res)+1;
		for (i=1;i<n;i++)
			if (find(a[i])==find(a[i+1])) ans=res-1;
		cout<<ans<<'\n';
	}
	return 0;
}

```


---

## 作者：Rosent (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1768D)

很经典的一类问题。

不难发现，对于任意一个序列而言，有且仅有一对逆序对的情况，一定是由一个已排序的序列交换两个相邻元素所得到的。

考虑如何将原序列通过最少次交换变为一个升序序列。不妨将每个元素的位置与其在升序序列位置进行建边操作。该操作会形成若干个环，不难发现，对于大小为 $t$ 的环，最少需要 $t-1$ 次交换操作将其元素转化为升序。换言之，对于一个有 $n$ 个数 $m$ 个环的序列，你最少需要 $n-m$ 次操作使其变成一个升序序列。并查集维护即可。

现在还是有些小问题的。假如说在交换途中就已经满足了有且仅有一对逆序对的条件，这个代码就 WA 了。所以若已经有相邻元素在同一环上，可减少一次操作，答案即为 $n-m-1$；否则需在排序后再交换一对元素，答案即为 $n-m+1$。

附代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define maxn 200020
int a[maxn],index[maxn],fa[maxn];
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		memset(index,0,sizeof(index));
		for(int i=1;i<=n;i++)
			fa[i]=i;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			index[a[i]]=i;
			fa[find(i)]=find(a[i]);
		}
		int cnt=0,flag=0;
		for(int i=1;i<=n;i++)
			if(find(i)==i) cnt++;
		int num=n-cnt;
		for(int i=1;i<n;i++)
		{
			if(find(index[a[i]])==find(index[a[i+1]]))
				flag=1;
		}
		if(flag) 
			cout<<num-1<<endl;
		else
			cout<<num+1<<endl;
	}
	return 0;
}
```


---

## 作者：masonpop (赞：0)

经典好题。

我们发现，只有一个逆序对的排列就是 $1,2,\cdots,n$ 经过一次交换相邻两数产生的东西。因此我们可以先考虑至少交换多少次使其有序。

这是个典题。如果位置 $i$ 上的数需要去位置 $j$，那么将 $i,j$ 之间连有向边，在题目中就是 $i$ 向 $p_i$ 连边。显然所形成的是若干个环。对于一个环内，将这些点归位所需的操作次数是 $\text{环的大小}-1$。因为如果位置集合不变的话，交换完前面的位置后面的那一对就自动归位了。那么，使其变得有序的最少交换次数就是 $n-\text{环的个数}$。可以用并查集维护。那么，答案似乎是这个值加一了。

但是这样不一定是最优解。有可能我们数 $i,i+1$ 进行了一次交换，最后又换回来了，相当于浪费了操作。那么，我们只需要判断相邻两个数同时在环中的情况。这样，我们就可以直接留下这两个数不交换，省去了最后一步的操作。这样，答案就是这个值减一，特判一下即可。

时间复杂度 $O(n\log n)$，即普通并查集的复杂度。[代码](https://codeforces.com/contest/1768/submission/209176374)。

---

## 作者：ExplodingKonjac (赞：0)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1768D)**

## 题目分析

只有一个逆序对的排列就是 $1,2,\dots,n$ 交换一对相邻的数。

考虑变成 $1,2,\dots,n$ 的最小步数。如果位置 $i$ 上的数最后在位置 $j$，那么我们把 $i\to j$ 连边。这样会形成若干个环，对于每一个环，可以发现最小操作次数是 $\text{环长}-1$。总操作次数为所有环操作次数之和，也就是 $n-\text{环数}$。

然后考虑一次交换 $i,i+1$，也就是交换 $i,i+1$ 的入边。如果这两个点在同一个环，环数会 $+1$，否则环数 $-1$。判断一下就可以算出交换后的操作次数。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

int T,n,p[200005],pos[200005],fa[200005],siz[200005];
inline int findFa(int x)
	{ return x!=fa[x]?fa[x]=findFa(fa[x]):x; }
inline void merge(int x,int y)
	{ x=findFa(x),y=findFa(y);if(x!=y)fa[y]=x,siz[x]+=siz[y]; }
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) qin>>p[i],pos[p[i]]=i;
		iota(fa+1,fa+n+1,1),fill(siz+1,siz+n+1,1);
		int ans=1e9;
		for(int i=1;i<=n;i++) merge(i,p[i]);
		for(int i=2;i<=n;i++) ans=min(ans,findFa(pos[i-1])==findFa(pos[i])?-1:1);
		for(int i=1;i<=n;i++) if(findFa(i)==i) ans+=siz[i]-1;
		qout.writeln(ans);
	}
	return 0;
}
```

---

