# [ABC347E] Set Add Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_e

全ての要素が $ 0 $ で初期化された長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,A_N) $ があります。また、集合 $ S $ があります。はじめ $ S $ は空です。

以下の $ Q $ 個のクエリを順に行います。$ Q $ 個のクエリを全て処理した後の数列 $ A $ の各要素の値を求めてください。 $ i $ 番目のクエリは以下の形式です。

- 整数 $ x_i $ が与えられる。整数 $ x_i $ が $ S $ に含まれる場合、$ S $ から $ x_i $ を削除する。そうでない場合、$ S $ に $ x_i $ を追加する。次に、$ j=1,2,\ldots,N $ について、$ j\in\ S $ ならば $ A_j $ に $ |S| $ を加算する。

なお、$ |S| $ は集合 $ S $ の要素数を意味します。例えば $ S=\lbrace\ 3,4,7\rbrace $ のとき、$ |S|=3 $ です。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\leq\ 2\times10^5 $
- $ 1\leq\ x_i\leq\ N $
- 入力される数値は全て整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは、$ S $ に $ 1 $ を追加し、$ S=\lbrace\ 1\rbrace $ となります。その後、$ A_1 $ に $ |S|=1 $ を加算します。$ A=(1,0,0) $ となります。 $ 2 $ 番目のクエリでは、$ S $ に $ 3 $ を追加し、$ S=\lbrace\ 1,3\rbrace $ となります。その後、$ A_1,A_3 $ に $ |S|=2 $ を加算します。$ A=(3,0,2) $ となります。 $ 3 $ 番目のクエリでは、$ S $ から $ 3 $ を削除し、$ S=\lbrace\ 1\rbrace $ となります。その後、$ A_1 $ に $ |S|=1 $ を加算します。$ A=(4,0,2) $ となります。 $ 4 $ 番目のクエリでは、$ S $ に $ 2 $ を追加し、$ S=\lbrace\ 1,2\rbrace $ となります。その後、$ A_1,A_2 $ に $ |S|=2 $ を加算します。$ A=(6,2,2) $ となります。 最終的に、$ A=(6,2,2) $ となります。

## 样例 #1

### 输入

```
3 4
1 3 3 2```

### 输出

```
6 2 2```

## 样例 #2

### 输入

```
4 6
1 2 3 2 4 2```

### 输出

```
15 9 12 7```

# 题解

## 作者：fedoralxy (赞：11)

显然直接模拟是不可行的，考虑用桶和前缀和。

对于每一次操作，如果 $x$ 不在桶中，就将他放进去，记录当前字符串的长度，将 $x$ 的左端点记为当前操作的步数。若他不在桶中，我们就利用前缀和，将当前操作步数视为右端点，进行累加。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#define ll unsigned long long
using namespace std;
const int N=1e6+10;
ll n,q,len;
ll val[N];
bool t[N];
struct node{
	ll l,v;
}ans[N];
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i)ans[i].l=-1;
	for(int step=1;step<=q;++step){
		ll x;
		cin>>x;
		if(!t[x]){
			ans[x].l=step;
			t[x]=1;
			++len;
		}
		else{
			ans[x].v+=val[step-1]-val[ans[x].l-1];
			ans[x].l=-1;
			--len;
			t[x]=0;
		}
		val[step]=val[step-1]+len;
	}
	for(int i=1;i<=n;++i){
		if(ans[i].l!=-1){
			ans[i].v+=val[q]-val[ans[i].l-1];
		}
	}
	for(int i=1;i<=n;++i){
		cout<<ans[i].v<<" ";
	}
	return 0;
} 
```

---

## 作者：DGH_Didi (赞：9)

### 题目大意

有一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\ldots,A_N)$，其中所有元素的初始值都设为 $0$。此外，还有一个初始为空的集合 $S$。

依次执行以下 $Q$ 查询。在处理完所有 $Q$ 查询后，找出序列 $A$ 中每个元素的值。

- 给出一个整数 $x_i$。如果 $S$ 中包含整数 $x_i$，则从 $S$ 中删除 $x_i$。否则，在 $S$ 中插入 $x_i$。然后，如果 $j\in S$ 包含 $j=1,2,\ldots,N$，则将 $|S|$ 添加到 $A_j$ 中。

这里，$|S|$ 表示集合 $S$ 中元素的个数。例如，如果是 $S=\lbrace 3,4,7\rbrace$，那么就是 $|S|=3$。

-  $1\leq N,Q\leq 2\times10^5$
-  $1\leq x_i\leq N$

### 解题思路
考虑用 `std::set` 进行集合查询插入删除操作，记录每次询问后的集合大小，记录每个数字入集合出集合的时间点。对于每个数字而言显然可以单独计算，贡献即为在集合的时间内集合的大小之和，用前缀和处理即可。

### 示例代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;
int n, q;
int a[N], siz[N];
i64 sum[N];
set<int> s;
vector<int> his[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> q;
    
    for (int i = 1; i <= q; i++) {
        cin >> a[i];
        if (s.find(a[i]) == s.end()) {
            s.insert(a[i]);
        } else {
            s.erase(a[i]);
        }
        his[a[i]].push_back(i);
        siz[i] = s.size();
        sum[i] = sum[i - 1] + siz[i];
    }

    for (auto i : s) {
        his[i].push_back(q + 1);
    }

    for (int i = 1; i <= n; i++) {
        i64 ans = 0;
        for (int j = 0; j < his[i].size(); j += 2) {
            ans += sum[his[i][j + 1] - 1] - sum[his[i][j] - 1];
        }
        cout << ans << " ";
    }
    return 0;
}
```

---

## 作者：lilong (赞：4)

### 题意

给定你一个长度为 $n$ 且初始全部为 $0$ 的序列 $A$，以及一个空集 $S$。接下来有 $T$ 次操作，每次给定一个 $x$，若 $x \in S$ 则将 $x$ 删除，否则将 $x$ 加入 $S$。在每次操作之后，对于 $j=1,2,\cdots,n$，若 $j \in S$，则给 $a_j$ 加上 $\left| S \right|$，其中 $\left| S \right|$ 定义为 $S$ 的元素个数。所有操作完成后，求 $A$ 的每一个元素的值。

### 思路

显然，对于 $x \notin S$ 等价于它后面的每一个位置长度都加 $1$，$x \in S$ 等价于后面的每一个位置长度都减 $1$。不难想到用差分来修改，再做一遍前缀和即可得到每一次操作做完后的 $\left| S \right|$。

接下来如何计算答案呢？读题可以发现，对于一个相同的 $x$，其一定在第奇数次出现时加入，第偶数次出现时删除。也就是说，在奇数次出现和偶数次出现这段时间内的 $ \sum \left| S \right|$ 是有效的，应计入答案。其余则无效，因为此时 $x \notin S$。

注意到要求的 $\sum \left| S \right|$ 总是连续的，因此可以在前文的基础上再做一次前缀和，即可快速求得答案。

当然了，最后边界记得要处理。时间复杂度是 $O(n)$ 的。

放上代码方便大家调试：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long

using namespace std;


int n,m,x[1000001],a[1000001],s[1000001],pd[1000001],lst[1000001];

signed main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= m ; i ++ )
	{
		cin >> x[i];
		if( pd[x[i]] ) s[i] --,pd[x[i]] = 0;
		else s[i] ++,pd[x[i]] = 1;
	}
	for( int i = 1 ; i <= m ; i ++ )
		s[i] += s[i - 1];
	for( int i = 1 ; i <= m ; i ++ )
		s[i] += s[i - 1];
	memset( pd , 0 , sizeof( pd ) );
	for( int i = 1 ; i <= m ; i ++ )
	{
		if( pd[x[i]] && lst[x[i]] ) a[x[i]] += s[i - 1] - s[lst[x[i]] - 1],pd[x[i]] = 0;
		else lst[x[i]] = i,pd[x[i]] = 1;
	}
	for( int i = 1 ; i <= m ; i ++ )
		if( pd[x[i]] )
			a[x[i]] += s[m] - s[lst[x[i]] - 1],pd[x[i]] = 0;
	for( int i = 1 ; i <= n ; i ++ )
		cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：Pentiment (赞：4)

### 题目大意

给你一个长度为 $N$ 的、初始元素都为 $0$ 的整数列 $A$ 和一个初始为空的集合 $S$。

按顺序给出 $Q$ 次操作，第 $i$ 次操作给出一个正整数 $x_i$，含义是：

- 如果 $x_i\in S$，则将 $x_i$ 从 $S$ 中删除，否则将 $x_i$ 插入到 $S$ 中。然后对于每个 $1\leq j\leq N$，如果 $j\in S$，则将 $A_j$ 加上 $|S|$（集合 $S$ 的大小）。

在所有操作完成后，输出 $A$ 中每个元素的值。

### Solution

首先，按顺序扫描一遍操作序列，得到第 $i$ 次操作后集合 $S$ 的大小 $|S|_i$ 及其前缀和 $\text{sum}_i$。

然后对于每个 $x_i$，如果之前 $x_i$ 出现了奇数次，上一次出现的位置为 $\text{pre}_{x_i}$，那么就相当于得到了一个新的区间 $[\text{pre}_{x_i},i-1]$，在该区间内 $|S|$ 对 $A_{x_i}$ 的值有贡献，因此将 $A_{x_i}$ 加上 $\text{sum}_{i-1}-\text{sum}_{\text{pre}_{x_i}}$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200005;
int n, m, q[MAXN], s[MAXN], vis[MAXN];
ll sum[MAXN];
vector<pair<int, int> > v[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &q[i]);
		if (!vis[q[i]]) vis[q[i]] = i, s[i] = s[i - 1] + 1;
		else s[i] = s[i - 1] - 1, v[q[i]].push_back({vis[q[i]], i - 1}), vis[q[i]] = 0;
		sum[i] = sum[i - 1] + s[i];
	}
	for (int i = 1; i <= n; i++) {
		if (vis[i]) v[i].push_back({vis[i], m});
	}
	for (int i = 1; i <= n; i++) {
		ll ans = 0;
		for (auto p : v[i]) ans += sum[p.second] - sum[p.first - 1];
		printf("%lld ", ans);
	}
}
```

---

## 作者：FinderHT (赞：2)

### 题面描述

有一个长度为 $N$ 的序列 $A$，其中元素的初始值都为 $0$，还有一个空集 $S$。共有 $Q$ 次操作，每次操作给定整数 $x$，如果 $x$ 在集合 $S$ 中则从集合中将其删除，否则将其添加到集合中。对于 $j=1,2,3,\dots,N$，如果 $j\in S$，把 $A_j$ 加上集合的元素个数。

### 思路分析

暴力显然会超时。注意到只有最后一次查询，我们记录一个值 $cnt$ 表示到目前为止每次操作时集合大小的累加和，并维护一个集合，我们每次查询后将 $cnt$ 加上目前集合的大小。

当一个元素 $x$ 被加入集合中时，要将 $A_x$ 减去当前的 $cnt$，而被删除时则将 $A_x$ 加上更新了若干次后的 $cnt$，不难发现这样能使 $A_x$ 和在每次操作时暴力增加所得到的值是一样的，即删除元素 $x$ 时的 $cnt$ 减上次插入元素 $x$ 时的 $cnt$ 等于元素 $x$ 在集合中时的所有操作给 $A_x$ 加上的值之和。

最后别忘了把集合中剩下的所有元素在序列 $A$ 中的对应值都加上 $cnt$，以算出我们最终的答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
set<int>st;//集合，维护一个set即可
int a[MAXN];
int cnt;
signed main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        int x;
        cin>>x;
        if(st.count(x)){//在集合中找到了元素x，就把它删除
            st.erase(x);
            a[x]+=cnt;
        }
        else{
            st.insert(x);
            a[x]-=cnt;
        }
        cnt+=st.size();//更新cnt
    }
    for(int i=1;i<=n;i++){//找集合中剩下的元素
        if(st.count(i))
            a[i]+=cnt;
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：Vocaloid世末歌者 (赞：2)

很水。

一个 `las` 数组，记录 `a[i]` 这个数上一次被加入是什么时候。

注意，为防误判，在 `a[i]` 被删除的时候，将 `las[a[i]]` 设为 $0$。

你也可以这么理解：`las` 是记录在哪出现的 `visit` 数组。

每次加入一个数的时候，$\left|S\right|$ 就加 $1$，并且使 `las[a[i]]` 等于 `i`。

删除时，$\left|S\right|$ 减 $1$，统计这段区间内的答案，并且使 `las[a[i]]` 等于 $0$。

求一段区间内答案很好做，前缀和。

然后记得最后要看一下哪些数还在，记得也把他们的答案加上。

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void writing(i128 x)
{
	if(x>=10)writing(x/10);
	putchar(x%10+'0');
}
void write(i128 x)
{
	if(x<0)
	{
		cout<<'-';
		x=-x;
	}
	writing(x);
}
LL n,q,a[200010],las[200010],sum[200010],f[200010],ans;
int main()
{
	cin>>n>>q;
	rep(i,1,q,1)
	{
		cin>>a[i];
	}
	rep(i,1,q,1)
	{
		if(las[a[i]])
		{
			ans--;
			f[a[i]]+=sum[i-1]-sum[las[a[i]]-1];
			las[a[i]]=0;
		}
		else
		{
			ans++;
			las[a[i]]=i;
		}
		sum[i]=sum[i-1]+ans;
	}
	rep(i,1,n,1)
	{
		if(las[i])
		{
			f[i]+=sum[q]-sum[las[i]-1];
		}
	}
	rep(i,1,n,1)cout<<f[i]<<' ';
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

考虑记录每次操作时的元素状态和个数。

如果元素在这次操作时没有，标记为有，将这一项操作的时间记录。

如果操作过，将这一项的值增加标记时间到此时时间的元素个数之和，用前缀和记录。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll f[N],a[N];
int he[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m,x,l=0;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x;
        if(he[x])
        {
            a[x]+=f[i-1]-f[he[x]-1];//将这个数的出现时间段的和增加长度
            he[x]=0;
            l--;//出现过，数量减一
        }
        else
        {
            he[x]=i;
            l++;//没出现过，数量加一
        }
        f[i]=f[i-1]+l;//前缀和数组
    }
    for(int i=1;i<=n;i++)
    {
        if(he[i])a[i]+=f[m]-f[he[i]-1];//最后还没清空
    }
    for(int i=1;i<=n;i++)
    {
        cout<<a[i]<<' ';
    }
    cout<<'\n';
    return 0;
}
```

---

## 作者：xvl_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc347_e)

一道前缀和题。

我们设第 $i$ 次操作后集合中的元素有 $sum_i$ 个，这个序列直接模拟求出即可。

我们对 $sum$ 求出前缀和，记 $pre_n = \sum^{n}_{i=1}sum_i$，方便之后快速求出区间和。

如果在第 $i$ 次操作 $x_i$ 被加入集合，即 $cnt_x = 0$，那么标记 $cnt_x=i$；否则，说明 $A_{x_i}$ 在第 $cnt_{x_i}$ 至 $i-1$ 次操作时存在于集合中，此时令 $A_x \rightarrow A_{x_i}+pre_{i-1} - pre_{cnt_{x_i}-1}$，之后令 $cnt_{x_i} \rightarrow 0$。若最终依然存在 $1\le x\le n$，满足 $cnt_x \neq 0$，令 $A_x \rightarrow A_x + pre_q - pre_{cnt_x-1}$。时间复杂度为 $O(n)$。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll n, q;
ll sum[200005], a[200005], pre[200005], ans[200005], cnt[200005];
set <ll> S;
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> q;
	REP(i, 1, q) {
		cin >> a[i];
		if (S.find(a[i]) != S.end()) S.erase(a[i]);
		else S.insert(a[i]);
		sum[i] = S.size();
	}
	REP(i, 1, q) pre[i] = pre[i - 1] + sum[i];
	REP(i, 1, q) {
		if (!cnt[a[i]]) cnt[a[i]] = i;
		else {
			ans[a[i]] += pre[i - 1] - pre[cnt[a[i]] - 1];
			cnt[a[i]] = 0;
		}
	}
	REP(i, 1, n) {
		if (cnt[i]) ans[i] += pre[q] - pre[cnt[i] - 1];
	}
	REP(i, 1, n) cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：WhxStar2024 (赞：2)

## 本题思路：
~~这道题我自认为比 $D$ 还要简单一点……~~

我们这道题可以直接开一个差分数组记录当前时刻有多少个数字在集合之中，这一步操作我们可以用桶来完成数据的删除于加入，就是当当前这个数的桶值为空时加入差分，否则差分数组减减（可以直接开数组存，我赛时没看数据范围，开大了）。

然后我们可以在做一个前缀和，我们知道一个数的答案只会是他出现的奇数次到之后最近偶数次的和，那么就可以用差分数组随便搞了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int>s;
int a[200001],sum[200001],ans[200001];
signed main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>a[i];
		if(s[a[i]]==0){
			s[a[i]]=1;
			sum[i]++;
		}
		else s[a[i]]=0,sum[i]--;
		sum[i]+=sum[i-1];
	}
	for(int i=1;i<=q;i++){sum[i]+=sum[i-1];}
	for(int i=1;i<=n;i++) s[i]=0;
	for(int i=1;i<=q;i++){
		if(s[a[i]]==0) s[a[i]]=i;
		else{
			ans[a[i]]+=sum[i-1]-sum[s[a[i]]-1];
			s[a[i]]=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(s[i]!=0){
			ans[i]+=sum[q]-sum[s[i]-1];
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

# 1 题目大意
给定 $a$ 数组，长度为 $n$，一开始都是 $0$。你有一个集合 $S$，一开始是空集。

你有 $Q$ 次操作，每次操作会给定 $t$，如果 $t$ 在集合中，就把 $t$ 删了，否则把 $t$ 加入集合。

每次操作结束，对于集合中所有的元素 $i$，$a_i = a_i + k$，其中 $k$ 为集合元素数。
# 2 解题思路
## 2-1 暴力
链表统计元素，变量计元素数，插入删除 $O(1)$，更改 $a$ 数组 $O(n)$，时间复杂度 $O(nq)$，过 $9$ 个测试点。
```
#include<bits/stdc++.h>
using namespace std;
int n,q,a,pr[200010],ne[200010],c[200010],l,t;
long long b[200010];
void read(int &a){
	a=0;int flag=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')flag=-1;
		ch=getchar();
	}
	do{a=a*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	a*=flag;
}
int main(){
    read(n),read(q);
    while(q--){
        read(a);
        if(!c[a]){
            c[a]=1,pr[a]=l,ne[l]=a,l=a,t++;
            for(int w=ne[0];w;w=ne[w])b[w]+=t;
        }else{
            if(!ne[a])l=pr[a];
            t--,c[a]=0,ne[pr[a]]=ne[a],pr[ne[a]]=pr[a],ne[a]=pr[a]=0;
            for(int w=ne[0];w;w=ne[w])b[w]+=t;
        }
    }
    for(int w=1;w<=n;w++)printf("%lld ",b[w]);
    return 0;
}
```
## 2-2 前缀和优化
设 $s_i$ 为前 $i$ 次操作结束后，集合的元素数总和，设 $l_i$ 为 $i$ 最后一次加入集合是第几次操作。

如果加入 $i$，更新 $l_i$，否则 $a_i = a_i + s_{i-1} - s_{l_i-1}$。$s_{i-1} - s_{l_i-1}$ 表示这次加入起，到删除前集合元素数量的总和。

别忘了所有操作结束后，对集合中剩下的元素 $i$，$a_i = a_i + s_q - s_{l_i-1}$，道理同上。
# 3 注意事项
**不开 long long 见祖宗！**
# 4 代码展示
```
#include<bits/stdc++.h>
using namespace std;
int n,q,a,c[200010],t,l[200010];
long long s[200010],b[200010];
int main(){
    scanf("%d%d",&n,&q);
    for(int w=1;w<=q;w++){
        scanf("%d",&a);
        if(c[a])c[a]=0,t--,b[a]+=s[w-1]-s[l[a]-1];//前缀和
        else c[a]=1,t++,l[a]=w;//更新
        s[w]=s[w-1]+t;//更新
    }
    for(int w=1;w<=n;w++)if(c[w])b[w]+=s[q]-s[l[w]-1];//别忘了
    for(int w=1;w<=n;w++)printf("%lld ",b[w]);//long long!!!
    return 0;
}
```

---

## 作者：Mu_leaf (赞：1)

平衡树大法好啊。

## [思路]

考虑平衡树维护集合里的值，写个懒标记将平衡树里面的元素加上集合大小即可。

## [细节]
- 注意所以询问完以后再遍历一遍平衡树，重新下放一下懒标记。
- 考虑维护两个值 $val,sum$。表示在下标 $val$ 加了 $sum$。
- 注意 long long。


Code：
---
赛时代码有点丑，维护集合长度我用的 set。

~~脑子抽抽了~~。
```cpp


#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,ind,root,a,b,c,v[N],vis[N]; 
int ans[N];
struct node{
	int ls,rs,val,rnd,siz;
    int sum,lazy;
}tr[N];
void hbsiz(int x){
	int ls=tr[x].ls;
	int rs=tr[x].rs;
	tr[x].siz=tr[ls].siz+tr[rs].siz+1;
    // tr[x].sum=tr[ls].sum+tr[rs].sum+tr[x].sum;
}
void pushdown(int x){
    if(!tr[x].lazy) return;
    int ls=tr[x].ls,rs=tr[x].rs;
    tr[ls].lazy+=tr[x].lazy;
    tr[ls].sum+=tr[x].lazy;
    tr[rs].lazy+=tr[x].lazy;
    tr[rs].sum+=tr[x].lazy;
    tr[x].lazy=0;
}
int nes(int val){
	tr[++ind].val=val;
	tr[ind].rnd=rand();
	tr[ind].siz=1;
	return ind;
}
void merge(int x,int y,int &a){
    pushdown(y);
    pushdown(x);
	if(!x || !y){a=x+y;return;}
	if(tr[x].rnd<tr[y].rnd){
        
		merge(tr[x].rs,y,tr[x].rs);
		a=x;
	}else{
		merge(x,tr[y].ls,tr[y].ls);
		a=y;
	}hbsiz(y);hbsiz(x);
}
void split_val(int x,int val,int &a,int &b){
	if(!x){a=b=0;return;}
    pushdown(x);
	if(tr[x].val<=val){
		split_val(tr[x].rs,val,tr[x].rs,b);
		a=x;
	}else{
		split_val(tr[x].ls,val,a,tr[x].ls);
		b=x;
	}hbsiz(x);
}
int q;
void delet(int id){
    int x,y,z;
    split_val(root,id,x,y);
    split_val(x,id-1,x,z);
    merge(x,y,root);
}
void insert(int id){
    int x,y,z;
    split_val(root,id-1,x,y);
    merge(x,nes(id),z);
    merge(z,y,root);
}
set<int> s;
void dfs(int x){
    if(!x) return;
    pushdown(x);
    // ans[tr[x].val]+=tr[x].sum;
    dfs(tr[x].ls);
    dfs(tr[x].rs);
}
void print(int x){//debug用的
    if(!x) return;
    // pushdown(x);
    print(tr[x].ls);
    cout << tr[x].val <<" ";
    print(tr[x].rs);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	srand(time(0));
	cin >> n >> q;
    for(int i=1;i<=q;i++){
        cin >> v[i];
        if(vis[v[i]]){
            vis[v[i]]=0;
            s.erase(v[i]);
            delet(v[i]);
        }else{
            vis[v[i]]=1;
            s.insert(v[i]);
            insert(v[i]);
        }
        
        tr[root].lazy+=s.size();
        tr[root].sum+=s.size();
        // print(root);
        // puts("");
    }
    dfs(root);
    // cout <<tr[1].val << "\n";
    for(int i=1;i<=ind;i++) ans[tr[i].val]+=tr[i].sum;
    for(int i=1;i<=n;i++) cout << ans[i] << " ";
	return 0 ;
}



```

---

## 作者：Dream_poetry (赞：1)

### 翻译：

有一个长度为 $n$ 的序列 $A$，初始值都为 $0$。还有一个空集合，执行 $q$ 次操作。

若该元素已在集合内，就把它移除，否则加入进去。

每次操作结束后，将集合中的元素作为 $A$ 的下标，把 $A_x$ 加上集合的长度。

### 思路：
暴力必死无疑，考虑优化。

利用前缀和来统计一个点从加入到移除所增加的价值，最后再把没被移除的元素再累加一遍，非常简单。



```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
map<int,int>mp;//是否出现过
map<int,int>cx;//出现时的 i

int ans[500005];
int x;
int len;

int sum[500005];


signed main(){
	cin>>n>>q;
	for (int i=1;i<=q;i++){
		cin>>x;
		if (mp[x]==1){//如果已在集合内
			mp[x]=0;
			len--;
			ans[x]+=(sum[i-1]-sum[cx[x]-1]);//计算价值
		}	
		else{
			mp[x]=1;
			cx[x]=i;
			len++;
		}
		sum[i]=sum[i-1]+len;	//前缀和统计
	}
	for (int i=1;i<=n;i++){
		if (mp[i]==1){ // 结束后仍在集合内
			ans[i]+=(sum[q]-sum[cx[i]-1]);
		}
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

## 作者：Ace_FutureDream (赞：1)

比较好想的一道题目。首先，这道题目肯定是线性的时间复杂度，要么 $O(1)$ 处理每个询问，要么 $O(1)$ 处理每个数字。显然，$O(1)$ 处理每个数字较为容易，通过观察可以发现，最终每个数字的答案，等于那个数字存在时 $S$ 的长度。所以我们可以用前缀和维护某个区间内的区间长度和，再对所有数进行统计即可。

## code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int f[200010],len[200010],nxt[200010],ans[200010],ls[200010];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1,x;i<=q;i++){
		len[i]+=len[i-1];ls[i]+=ls[i-1];		
		cin>>x;
		if(f[x])len[i]--;	
		else len[i]++;
		ls[i]+=len[i];
		//ls为len的前缀和 
		if(f[x]){
			f[x]=0;
			ans[x]+=(ls[i-1]-ls[nxt[x]-1]);
			nxt[x]=-1;		
		}else{
			nxt[x]=i;
			f[x]=1;	
		}		
	}
	for(int i=1;i<=n;i++)
		if(nxt[i]!=-1&&nxt[i]!=0)
			ans[i]+=(ls[q]-ls[nxt[i]-1]);
	//结束时如果还存在那么也要统计一下 
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

史上最水 E 题，一眼看出解法，可以说和 [abc344_e](https://www.luogu.com.cn/problem/AT_abc344_e) 差不多。

首先对于每次循环，我们不能暴力加 $|s|$，复杂度会爆炸。

我们发现每次循环，要么会加上一个数，要么这个数被删去。我们可以对每个数进行考虑，记录他上次出现时的循环次数。然后加上从他出现到他消失时 $|s|$ 的和。

查询区间和就是前缀和板子，在循环之前预处理一下就行了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt,a[200005],sum[200005],v[200005],ans[200005];
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=m;i++)
  {
    cin>>a[i];
    if(v[a[i]]) cnt--,v[a[i]]=0;//出现过
    else cnt++,v[a[i]]=1;//没出现
    sum[i]=sum[i-1]+cnt;//记录前缀和
  }
  memset(v,0,sizeof(v));
  for(int i=1;i<=m;i++)
  {
    if(v[a[i]]) cnt--,ans[a[i]]+=sum[i-1]-sum[v[a[i]]-1],v[a[i]]=0;//出现过，记录区间和
    else v[a[i]]=i;
  }
  for(int i=1;i<=n;i++)//最后可能还有没消掉的数，还要再算一遍
  {
    if(v[i]) ans[i]+=sum[m]-sum[v[i]-1];
    cout<<ans[i]<<" ";
  }
  return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：1)

## 题解
考虑前缀和。

$|s|$ 的值做一个前缀和 $pre$，用一个数组 $mp$ 存储当前这个数上一次出现的位置 $i$。

如果已经出现过，答案就加上将 $pre_i$ 减去之前数组的位置的前缀 $pre_{mp_i-1}$。

记得结束后再统计一次。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;
long long s,pre[500005],ans[500005],a[500005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		if(mp[a[i]]==1)s--,mp[a[i]]--;
		else s++,mp[a[i]]=1;
		pre[i]=s+pre[i-1];
	}
	mp.clear();
	for(int i=1;i<=m;i++)
	{
	    if(mp[a[i]]==0)mp[a[i]]=i;
	    else 
	    {
	    	ans[a[i]]+=pre[i-1]-pre[mp[a[i]]-1];
	    	mp[a[i]]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(mp[i]!=0)ans[i]+=pre[m]-pre[mp[i]-1];
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
```

---

## 作者：wwwwwza (赞：0)

考虑对于每一个数单独维护。

设这个数第奇数次出现在位置 $i$，下一次出现在 $j$。

则贡献为 $\sum\limits^{j-1}_{k=i} \left| S \right|$。

预处理出所有的 $\left| S \right|$，前缀和一下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,q,x[N],len[N],ans[N];
bool mp[N];
vector<int>g[N]; 
signed main(){
	cin >>n>>q;
	for(int i=1;i<=q;i++){
		cin >>x[i];
		if(mp[x[i]]){
			len[i]=len[i-1]-1;
		}else{
			len[i]=len[i-1]+1;
		}
		mp[x[i]]^=1;
		g[x[i]].push_back(i);
	}
	len[0]=0;
	for(int i=1;i<=q+1;i++)len[i]+=len[i-1];
	for(int i=1;i<=n;i++){
		if((int)g[i].size()&1)g[i].push_back(q+1);
		for(int j=0;j<g[i].size();j+=2){
			ans[i]+=(len[g[i][j+1]-1]-len[g[i][j]-1]);
		}
		cout <<ans[i]<<" ";
	}
	return 0;
}

```

---

## 作者：MicroSun (赞：0)

考虑对于每一个数字独立出来会怎么样。

很明显，对于一个数字 $x$，它的值 $a_x$ 为它在集合中时，集合中的元素个数之和。

于是考虑使用前缀和 $s_i$ 记录前 $i$ 个操作时的 $|S|$ 之和。对于每个元素，记录其加入集合的时间，在它离开集合的时候用前缀和作差即可。

时间复杂度 $\Omicron(n)$。

Code:

```cpp
// Problem: E - Set Add Query
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=2e5+10;

ll a[maxn],q[maxn];
int in[maxn],sz;
bool s[maxn];
void solve(){
	int n,q1;
	cin>>n>>q1;
	rep(i,1,q1){
		int x;
		cin>>x;
		if(s[x]){
			a[x]+=q[i-1]-q[in[x]];
			s[x]=0;--sz;
		}
		else{
			s[x]=1;++sz;
			in[x]=i-1;
		}
		q[i]=q[i-1]+sz;
	}
	rep(i,1,n)
		if(s[i])
			a[i]+=q[q1]-q[in[i]];
	rep(i,1,n) cout<<a[i]<<' ';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：FReQuenter (赞：0)

考虑一个数 $x$ 对 $A$ 的贡献就是 $A_x$ 加上 $s_l+s_{l+1}+\cdots+s_{r}$。

其中 $l$ 为加入集合的时间，$r$ 为删除的时间，$s_i$ 表示时刻 $i$ 的集合大小。

显然我们通过一遍预处理可以得到每个时刻的集合大小。之后用前/后缀和维护 $s$ 的区间和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[200005],x[200005],sum[200005];
signed main(){
	cin>>n>>q;
	map<int,bool> mp;
	for(int i=1;i<=q;i++){
		cin>>x[i];
		sum[i]=sum[i-1];
		if(mp[x[i]]) mp[x[i]]=0,sum[i]--;
		else sum[i]++,mp[x[i]]=1;
	}
	for(int i=q;i>=1;i--) sum[i]+=sum[i+1];
	mp.clear();
	for(int i=1;i<=q;i++){
		if(mp[x[i]]) a[x[i]]-=sum[i],mp[x[i]]=0;
		else{
			mp[x[i]]=1;
			a[x[i]]+=sum[i];
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
}
```

---

## 作者：CEFqwq (赞：0)

好一个 $500$ 分题。

考虑维护集合元素前缀和，每次维护每个元素入集合和出集合是第几次操作，在出集合时前缀和作差。最后把所有剩下的元素出集合，前缀和作差统计答案。

具体见代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, q, siz;
int a[200005], x[200005], inq[200005], qz[200005];
set<int> S;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= q; i++){
		cin >> x[i];
		if (S.find(x[i]) != S.end()){//在集合内，出集合
			a[x[i]] += qz[i - 1] - qz[inq[x[i]]];//计算贡献
			S.erase(x[i]);
			siz--;
		}else{
			S.insert(x[i]);
			siz++;
			inq[x[i]] = i - 1;//加入集合，记录当前操作序号
		}
		qz[i] = qz[i - 1] + siz;//前缀和
	}
	for (auto ele : S)
		a[ele] += qz[q] - qz[inq[ele]];//全部出集合
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
}
```

---

## 作者：Walrus (赞：0)

## abc347_e

给定 $n$ 和 $q$，$q$ 次操作，定义一个集合 $S$，一个数组 $A$，长度为 $n$。集合 $S$ 最开始为空，数组 $A$  初始全为 $0$，操作如下：

每次给定一个数 $x$，若：

- $S$ 中包含 $x$，则将 $A_x$ 加上当前集合 $S$ 大小，并从集合 $S$ 中删除 $x$。
- $S$ 中不包含 $x$，将 $x$ 加入集合 $S$。

## 做法

显然不能每次都把集合中的所有元素都一起加上当前贡献，考虑用前缀和记录，当一个数插入集合时，记录其出现位置，当其被删除时，加上其贡献，最后将集合中剩下的元素进行贡献累加即可。

时间复杂度 $O(N \log N)$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

set<int> st;
int n, q, x, a[N], sum[N], pre[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> q;
	for(int i = 1; i <= q; ++i) {
		cin >> x;
		if(!st.count(x))
			pre[x] = i, st.insert(x);
		else
			a[x] += sum[i - 1] - sum[pre[x] - 1], st.erase(x);
		sum[i] = sum[i - 1] + st.size();
	}
	
	for(auto x : st)
		a[x] += sum[q] - sum[pre[x] - 1];
	for(int i = 1; i <= n; ++i)
		cout << a[i] << ' ';
	return 0;
}
```

我认为其难度远低于前两题。

---

## 作者：aaron0919 (赞：0)

# [AT_abc347_e の题解](https://www.luogu.com.cn/problem/AT_abc347_e)

### 理性分析

先考虑暴力，每次插入或删除一个数就全部加，明显时间复杂度为 $O(nq)$。

考虑优化，我们用一个数组来记录集合大小的前缀和，如果删除一个数，就增加加入时的时间戳到上一个时间戳的集合大小的贡献。最后再全部删除即可。

>形象化的代码理解：
>> `lasted[x]` 表示 `x` 加入的时间戳，`cur` 表示当前时间戳，`s` 数组表示结合的大小前缀和。删除 `x` 时应 `a[x] += s[cur - 1] - s[lasted[x] - 1];`。

注意，求前缀和时要注意，同时最大贡献约等于 $(2\times10^5)^2$，要用超长整型。

### code

[AC 记录。](https://atcoder.jp/contests/abc347/submissions/51872633)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, q;
int a[N], b[N];
int lasted[N];
set<int> s;

signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> q;
    for (int x, cur = 1; cur <= q; cur++)
    {
        cin >> x;
        if (lasted[x])
        {
            s.erase(x);
            a[x] += b[cur - 1] - b[lasted[x] - 1];
            lasted[x] = 0;
        }
        else
        {
            lasted[x] = cur;
            s.insert(x);
        }
        b[cur] = b[cur - 1] + s.size();
        // cout << b[cur] << ' ';
    }
    // cout << '\n';
    for (int i = 1; i <= n; i++)
    {
        int x = i, cur = q + 1;
        if (lasted[x])
        {
            s.erase(x);
            a[x] += b[cur - 1] - b[lasted[x] - 1];
            lasted[x] = 0;
        }
        cout << a[i] << ' ';
    }

    return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

给定 $Q$ 次操作，每一次操作都是往集合里添加一个数，如果已存在就删去这个数。每一次操作之后令集合大小为 $|S|$，那么所有 $j\in S$，$A_j$ 都要加上 $|S|$。

## 解法

我们发现，加入一个元素到集合里和删除这个元素使非常迅速的，而拖慢我们暴力思路的元凶是统计答案，如果一个元素一直在这个集合里出现的话我们每一次都要进行相加。

因此我们需要对集合数量做一个前缀和，然后找出每一个元素是什么时候进来、什么时候出去的，方便统计这个元素对答案的贡献，然后加入到答案数组里就行了。

对于元素 $x$，$i$ 时插入进去，$j$ 时删除掉，那么对答案 $a_x$ 的贡献就是 $s_{j-1}-s_{i-1}$。注意有些元素可能最后没有被删除，那么就需要进行特殊处理。

## 代码

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5;

LL idx[kMaxN], s[kMaxN], a[kMaxN], n, q, sz;

int main() {
  cin >> n >> q;
  for (LL i = 1, x; i <= q; i++) {
    cin >> x;
    if (!idx[x]) {                       // 如果没有出现
      idx[x] = i;                        // 记录出现的位置
      sz++;                              // 记录集合大小
    } else {                             // 如果已经出现过
      a[x] += s[i - 1] - s[idx[x] - 1];  // 计算贡献
      idx[x] = 0;                        // 删除这个数
      sz--;                              // 记录集合大小
    }
    s[i] = s[i - 1] + sz;                // 计算前缀和
  }
  for (LL i = 1; i <= n; i++) {          // 输出答案
    cout << a[i] + (idx[i] ? s[q] - s[idx[i] - 1] : 0) << ' ';
  }
  return 0;
}
```

---

## 作者：cdx123456 (赞：0)

给出一个与官方题解不同的线段树做法

### Solution

注意到$i$出现到被删除的过程中 $\left\vert S\right\vert$ 不断变化导致 $A_i$ 每次增加的值不同，但如果对 $A$ 序列逐元素增加复杂度过高。

发现每次操作后 $S$ 只会多出或减少一个元素，大多数元素不变，联想到懒标记。

考虑具体实现，维护一棵线段树，除叶子节点外只维护懒标记信息，叶子节点维护 $i$ 是否在 $S$ 中与 $A_i$ 的值两个信息。每次操作一个 $x_i$ 后，进行单点修改操作，改变其是否属于 $S$ 的状态。然后全局打一个增加 $A_i$ 的懒标记，大小为 $\left\vert S\right\vert$ ，注意对叶子节点增加 $A_i$ 时要判断其是否属于 $S$ 。

注意一个细节，当 $n=1$ 时，线段树只有一个叶子节点，可以换一种标记下传的方式来处理，详见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum[1000010],f[1000010],cnt[1000010],tag[1000010],n,m,x,cntt;
void push_down(int x,int l,int r){
	int mid=(l+r)>>1;
	if(l==r) sum[x]+=tag[x]*cnt[x];
	tag[x<<1]+=tag[x];
	tag[(x<<1)|1]+=tag[x]; 
	tag[x]=0;
}
void add(int x,int l,int r,int y,int z){
	push_down(x,l,r);
	if(l==r){
		cnt[x]+=z;
		return;
	}
	int mid=(l+r)>>1;
	if(y<=mid) add(x<<1,l,mid,y,z);
	else add((x<<1)|1,mid+1,r,y,z);
}
int query(int x,int l,int r,int y){
	push_down(x,l,r);
	if(l==r) return sum[x];
	int mid=(l+r)>>1;
	if(y<=mid) return query(x<<1,l,mid,y);
	else return query((x<<1)|1,mid+1,r,y);	
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x;
		if(f[x]) add(1,1,n,x,-1);
		else add(1,1,n,x,1);	
		if(f[x]) cntt--;
		else cntt++;
		tag[1]+=cntt;
		f[x]^=1;
	}
	for(int i=1;i<=n;i++) cout<<query(1,1,n,i)<<' ';
	cout<<endl;
	return 0;
} 
```

---

## 作者：cppcppcpp3 (赞：0)

[Link](https://atcoder.jp/contests/abc347/tasks/abc347_e)

直接对 set 里每个 $i$ 更新 $A_i$ 是不行的，但是如果这里面的 $i$ 对应了一段区间，就可以方便地维护（差分或支持区间加的数据结构）。既然 $i$ 不连续，就在每个下标在加入/删除时给它一个编号，这样编号区间是连续的，在编号区间上加减操作即可。

具体地，对每个 $i$ 用一个 vector 存下它参与了哪几次加入和删除操作。设当前进行了 $x_1$ 次加入操作，$x_2$ 次删除操作。维护两个数组 $B,C$，初始均为 $0$。则在这 $x_1+x_2$ 次操作后，$\forall i \in [1,x_1],B_i \leftarrow B_i+s$；$\forall i\in[1,x_2],C_i \leftarrow C_i-s$。其中 $s$ 为当前集合大小。

最后，对于 $i$，它参与了第 $k_1,k_2,\cdots,k_t$ 次加入操作和第 $k_1',k_2',\cdots,k_p'$ 次删除操作，那么
$$A_i=\sum_{j=1}^t B_{k_j}+\sum_{j=1}^p C_{k_j'}$$

时间复杂度线性或多一个 $\log$。

[Submission](https://atcoder.jp/contests/abc347/submissions/51867964)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int T=2e5;
const int inf=1e9+7;

static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int wrd(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}

int n,m;
vector<int> v1[N],v2[N];

struct SGT{
	int s[N<<2],lz[N<<2];
	
	#define ls (t<<1)
	#define rs (t<<1|1)
	#define md ((l+r)>>1)
	
	void pu(int t){s[t]=s[ls]+s[rs];}
	void pd(int l,int r,int t){
		if(!lz[t] || l==r) return;
		s[ls]+=(md-l+1)*lz[t],s[rs]+=(r-md)*lz[t];
		lz[ls]+=lz[t],lz[rs]+=lz[t],lz[t]=0;
	}
	void upd(int l,int r,int t,int x,int y,int k){
		if(l>y || r<x) return;
		if(l>=x&&r<=y){
			s[t]+=(r-l+1)*k,lz[t]+=k;
			return;
		}
		pd(l,r,t);
		upd(l,md,ls,x,y,k),upd(md+1,r,rs,x,y,k);
		pu(t);
	}
	int qry(int l,int r,int t,int x){
		if(l==r) return s[t];
		pd(l,r,t);
		return x<=md ? qry(l,md,ls,x) : qry(md+1,r,rs,x);
	}
}s1,s2;

set<int> ss;
int id1,id2;

int mp[N];

signed main(){
	cin >> n >> m;
	while(m--){
		int x=wrd();
		if(ss.count(x)){
			ss.erase(x);
			v2[x].push_back(++id2);
		}else{
			ss.insert(x);
			v1[x].push_back(++id1);
		}
		int cc=ss.size();
		if(id1) s1.upd(1,T,1,1,id1,cc);
		if(id2) s2.upd(1,T,1,1,id2,-cc);
	}
	
	for(int i=1;i<=n;++i){
		int res=0;
		for(int j:v1[i]) res+=s1.qry(1,T,1,j);
		for(int j:v2[i]) res+=s2.qry(1,T,1,j);
		write(res),putchar(' ');
	}
	return 0;
}
```

---

## 作者：KSCD_ (赞：0)

## 题意
初始有一个长度为 $N$，元素均为 $0$ 的数组 $A$ 和一个空集合 $S$。进行 $Q$ 次操作，每次给出一个数 $x$，若其不在 $S$ 中则加入 $S$，否则将其从 $S$ 中删除。之后给 $A$ 中下标在 $S$ 中的元素各加上 $\left|S\right|$，$\left|S\right|$ 为 $S$ 中的元素个数。求最终的 $A$ 数组。
## 思路
如果暴力修改，复杂度为 $O(N^2)$，无法通过本题。

因此考虑分别处理 $A$ 的每一位。对于每一个下标，都会在其第 $(2k-1)$ 次和第 $2k$ 次被操作之间被加上数，那么就可以把最终答案变为若干个区间的和。

那么记录下所有操作时的 $\left|S\right|$ 并求前缀和，对于 $A$ 中每一位分别操作即可。

这样时间复杂度优化至 $O(N)$，可以通过本题。
## 代码
```cpp
#include<iostream>
#include<vector>
#define int long long
const int N=2e5+10;
using namespace std;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1;  ch=getchar();}
	while(ch>='0'&&ch<='9') { s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
int n,Q,cnt,s[N];//cnt为目前S中元素个数，s为前缀和数组 
bool f[N];//每个下标是否在S中 
vector <int> pos[N];//每个下标出现的位置 
signed main()
{
	n=read(),Q=read();
	for(int i=1;i<=Q;i++)
	{
		int t=read();
		if(!f[t]) cnt++,f[t]=1;
		else cnt--,f[t]=0;
		s[i]=s[i-1]+cnt;
		pos[t].push_back(i); 
	} 
	for(int i=1;i<=n;i++)
	{
		int t=0;//分别处理每一位 
		if(pos[i].size()%2) pos[i].push_back(Q+1);//如果出现奇数次，则操作结束时其还在序列中，需要特判 
		for(int j=0;j<pos[i].size();j+=2)
		{
			int l=pos[i][j],r=pos[i][j+1]-1;
			t+=s[r]-s[l-1];
		}//每两次之间都能取得贡献 
		cout<<t<<' ';
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

~~个人认为比C简单，所以来水篇题解~~

## Solution
记录一个数组 $sum_i$ 表示 $\sum \limits_{j = 1}^{i}|S_j|$，其中 $S_j$ 表示第 $j$ 次操作的集合。

在记录六年给一个数组 $lst_i$，表示第 $i$ 个元素被放到 $S$ 里的时间。

对于每一次操作，如果 $x_i$ 已经在 $S$ 里面了，那么 $A_i \gets A_i + \sum \limits_{j = lst_{x_i}}^{i-1}|S_j|$；如果不在 $S$ 里面，那么 $lst_{x_i} \gets i$。

最后输出 $A_1,A_2,\dots,A_{n}$ 即可。

最后注意，要开 long long。

## Code
```cpp
#include <iostream>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 2;

bool in[kMaxN];
ll n, q, x, cnt, a[kMaxN], lst[kMaxN], sum[kMaxN];

int main() {
  cin >> n >> q;
  for (int i = 1; i <= q; i++) {
    cin >> x;
    if (!in[x]) {
      lst[x] = i;
      cnt++;
      sum[i] = sum[i - 1] + cnt;
      in[x] = 1;
    } else {
      sum[i] = sum[i - 1] + cnt - 1;
      cnt--;
      a[x] += sum[i - 1] - sum[lst[x] - 1];
      lst[x] = 0;
      in[x] = 0;
    }
  }
  for (int i = 1; i<= n; i++) {
    if (in[i]) {
      a[i] += sum[q] - sum[lst[i] - 1];
    }
    cout << a[i] << ' ';
  }
  return 0;
}
```

---

