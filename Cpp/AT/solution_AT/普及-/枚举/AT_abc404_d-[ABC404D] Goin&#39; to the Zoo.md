# [ABC404D] Goin&#39; to the Zoo

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc404/tasks/abc404_d

AtCoder 国には動物園が $ N $ 園あり、$ 1 $ から $ N $ の番号がついています。動物園 $ i $ の入園料は $ C_i $ 円です。

鈴木さんは $ M $ 種類の動物、動物 $ 1,\ldots,M $ が好きです。  
動物 $ i $ は $ K_i $ 園の動物園 $ A_{i,1},\dots,\ A_{i,K_i} $ で見ることができます。

$ M $ 種類の動物全てを $ 2 $ 度以上ずつ見るために必要な入園料の合計の最小値を求めてください。  
なお、同じ動物園を複数回訪れた場合、その動物園の動物は訪れた回数だけ見たとみなします。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 10 $
- $ 1\leq\ M\ \leq\ 100 $
- $ 0\leq\ C_i\ \leq\ 10^9 $
- $ 1\leq\ K_i\ \leq\ N $
- $ 1\ \leq\ A_{i,j}\ \leq\ N $
- $ j\ \neq\ j'\ \Longrightarrow\ A_{i,j}\neq\ A_{i,j'} $
- 入力は全て整数

### Sample Explanation 1

以下のようにすることで、$ 1800 $ 円で動物 $ 1,2,3 $ を $ 2 $ 度以上ずつ見ることができます。 - 動物園 $ 3 $ に行く。入園料 $ 700 $ 円を払い、動物 $ 1,3 $ を見る。 - 動物園 $ 3 $ に行く。入園料 $ 700 $ 円を払い、動物 $ 1,3 $ を見る。 - 動物園 $ 4 $ に行く。入園料 $ 200 $ 円を払い、動物 $ 1,2 $ を見る。 - 動物園 $ 4 $ に行く。入園料 $ 200 $ 円を払い、動物 $ 1,2 $ を見る。

### Sample Explanation 2

動物園 $ 7 $ に $ 2 $ 度行くことで、合計 $ 2000 $ 円で動物 $ 1,2,3,4,5,6 $ を $ 2 $ 度ずつ見ることができます。

## 样例 #1

### 输入

```
4 3
1000 300 700 200
3 1 3 4
3 1 2 4
2 1 3```

### 输出

```
1800```

## 样例 #2

### 输入

```
7 6
500 500 500 500 500 500 1000
3 1 2 7
3 2 3 7
3 3 4 7
3 4 5 7
3 5 6 7
3 6 1 7```

### 输出

```
2000```

# 题解

## 作者：Little_x_starTYJ (赞：8)

### 题目大意
AtCoder 国家有 $N$ 个动物园，编号为 $1$ 至 $N$。动物园 $i$ 的门票是 $C_i$ 日元。

铃木先生喜欢 $M$ 种动物，动物 $1,\dots,M$。  
动物园 $K_i$，即动物园 $A_{i,1},\dots,A_{i,K_i}$ 可以看到动物 $i$。

求观看所有 $M$ 种动物每种至少两次所需的最低门票总额。  
如果你多次游览同一个动物园，那么那里的动物就被视为每次游览都能看到一次。

### 解题思路
注意到 $1\leq n \leq 10$，所以考虑直接爆搜。

我们枚举第 $i$ 种动物园游玩 $0,1,2$ 次，然后最后统计每种动物是否都看到了 $2$ 次及以上，与答案取一个最小值即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, c[20], a[110][10], k[110], cnt[110];
int ans = 1e18;
inline void dfs(int step, int x) {
	if (step == n + 1) {
		for (int i = 1; i <= m; i++) {
			int res = 0;
			for (int j = 1; j <= k[i]; j++)
				res += cnt[a[i][j]];
			if (res < 2) {
				return;
			}
		}
		ans = min(ans, x);
		return;
	}
	for (int t = 0; t <= 2; t++) {
		int nc = x + t * c[step];
		if (nc >= ans) {
			return;
		}
		cnt[step] = t;
		dfs(step + 1, nc);
		cnt[step] = 0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> k[i];
		for (int j = 1; j <= k[i]; j++) {
			cin >> a[i][j];
		}
	}
	dfs(1, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：thedyingkai (赞：1)

### 思路
- 每种动物需要被访问两次，也就是同一个动物园访问至多两次之后就没有意义了，枚举每个动物园的访问次数 $\{0,1,2\}$，共 $3^{10}$ 种组合，可以过。
- 检查一下每个动物是否被看到至少两次，更新一下答案最小值就行了，还可以再顺便剪个枝，已经超过最小值后面就不用看了。
### AC code
```cpp
void solve(){
    int n,m;
    cin>>n>>m;
    vector<ll> c(n+1);
    vector<vector<int>> a(m+1,vector<int>(1));
    rep(i,1,n) cin>>c[i];
    rep(i,1,m){
        int k;
        cin>>k;
        a[i].resize(k);
        rep(j,0,k-1) cin>>a[i][j];
    }
    ll ans=LLONG_MAX;
    vector<int> x(n+1);
    auto dfs=[&](int i,ll sum,auto self)->void{
        if(i>n){
            rep(j,1,m){
                int cnt=0;
                for(auto it:a[j]) cnt+=x[it];
                if(cnt<2) return;
            }
            ans=min(ans,sum);
        }
        for(auto it:{0,1,2}){
            ll tem=sum+it*c[i];
            if(tem>=ans) continue;
            x[i]=it;
            self(i+1,tem,self);
        }
    };
    dfs(1,0,dfs);
    cout<<ans<<endl;
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：AT_abc404_d [ABC404D] Goin' to the Zoo
## 思路
很明显，一个动物园要么去 $1$ 次，要么去 $2$ 次，要么不去。

因此可以爆搜，时间复杂度 $O(3 ^ n \times m)$（最终判断有 $O(m)$ 的时间复杂度），足以通过此题。

不过本蒟蒻赛时想到的是状压枚举，时间复杂度是 $O(3 ^ n \times m \times n)$（`check` 函数最多有 $O(m \times n)$ 的时间复杂度），也可以接受。

把两种代码都贴上吧。
## Code
### 爆搜
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 15, MAXM = 1e2 + 12;

int n, m;
ll ans = 1e12;
int c[MAXN];
vector<int>hv[MAXN];
int cnt[MAXM];
ll w;

void check() {
	for(int i = 1; i <= m; i++) {
		if(cnt[i] < 2) {
			return;
		}
	}
	ans = min(ans, w);
}

void dfs(int i) {
	if(i == n + 1) {
		check();
		return;
	}
	dfs(i + 1);
	w += c[i];
	for(int s : hv[i])cnt[s]++;
	dfs(i + 1);
	w += c[i];
	for(int s : hv[i])cnt[s]++;
	dfs(i + 1);
	w -= c[i] * 2;
	for(int s : hv[i])cnt[s] -= 2;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for(int i = 1, sz, k; i <= m; i++) {
		cin >> sz;
		while(sz--){
			cin >> k;
			hv[k].push_back(i);
		}
	}
	dfs(1);
	cout << ans;
	return 0;
}
```
### 状压枚举
```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 25, MAXM = 1e2 + 12;

int n, m;
ll ans = 1e12;
int c[MAXN];
vector<int>hv[MAXN];
int cnt[MAXM];

void check(int s, int k) {
	ll sum = 0;
	for(int i = 1; i <= m; i++) {
		cnt[i] = 0;
	}
	for(int i = 0; i < n; i++) {
		if(s >> i & 1) {
			sum += c[i] * (1 + (k >> i & 1));
			for(int g : hv[i]){
				cnt[g] += 1 + (k >> i & 1);
			}
		}
	}
	for(int i = 1; i <= m; i++) {
		if(cnt[i] < 2) {
			return;
		}
	}
	ans = min(ans, sum);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> c[i];
	}
	for(int i = 1, sz, k; i <= m; i++) {
		cin >> sz;
		while(sz--){
			cin >> k;
			hv[k - 1].push_back(i);
		}
	}
	for(int i = 1; i < (1 << n); i++) {
		for(int j = i; j; j = (j - 1) & i) {
			check(i, j);
		}
		check(i, 0);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

看到 $N\leq10$，直接考虑 DFS。

首先题目描述有点别扭，容易转化成存储每个动物园中有哪些动物的形式。

接下来我们发现一个动物园最多只需要看两次就可以看完该动物园中所有动物两遍，所以每个动物园最多看两次。

考虑枚举每个动物园看几遍，只有 $0,1,2$ 三种情况，暴力枚举，记录每一种动物被看了几遍，枚举完所有动物园之后 $O(n)$ 判断是否都看过至少两遍。总时间复杂度为 $O(3^N\times N)$。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m;
int c[105],b[105],a[105][1005];
int vis[105];
int cnt[105];
int tot[105];
int d[105][1005];
int no;
int ans=1e18;
void dfs(int dep,int cost){
	if(dep>n){
		for(int i=1;i<=m;++i){
			if(cnt[i]<2)return;
		}
		ans=min(ans,cost);
		return;
	}
	dfs(dep+1,cost);
	for(int i=1;i<=tot[dep];++i)++cnt[d[dep][i]];
	dfs(dep+1,cost+c[dep]);
	for(int i=1;i<=tot[dep];++i)++cnt[d[dep][i]];
	dfs(dep+1,cost+c[dep]*2);
	for(int i=1;i<=tot[dep];++i)cnt[d[dep][i]]-=2;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=m;i++){
		cin>>b[i];
		for(int j=1;j<=b[i];j++){
			int x;
			cin>>x;
			d[x][++tot[x]]=i;
		}
	}
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：AnotherDream (赞：0)

# [AT_abc404_d](https://www.luogu.com.cn/problem/AT_abc404_d) 题解
## 题意简述
有一些动物园，每个动物园里有一些动物。问将所有动物看至少两遍的最小花费是多少。
## 思路
很显然每个动物园至多访问 $2$ 次。  
因为你在访问第三遍的时候，动物园里的所有动物都看过至少两遍，这次访问对答案没有贡献。

注意到 $1\leq N \leq 10$ 直接暴搜。  
枚举每个动物园的访问次数然后再统计答案。
## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f; 
const int N = 1e2 + 10;
int siz[N],a[N][N],n,m,c[N],tong[N],ans,res=INF;
//siz是每个动物园动物的数量，a是每个动物园有哪些动物
inline void dfs(int x) {
	if(x==n+1) {
		for(int i=1;i<=m;i++) {
			if(tong[i]<2) return;//没有访问两次
		}
		res=min(res,ans);
		return;
	}
	dfs(x+1);//不访问
	ans+=c[x];
	for(int i=1;i<=siz[x];i++) {
		tong[a[x][i]]++;
	}
	dfs(x+1);//访问一次
	ans+=c[x];
	for(int i=1;i<=siz[x];i++) {
		tong[a[x][i]]++;
	}
	dfs(x+1);//访问两次
	ans-=c[x]*2;
	for(int i=1;i<=siz[x];i++) {
		tong[a[x][i]]-=2;//回溯
	}
}
signed main() {
	fst;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>c[i];
	}
	for(int i=1;i<=m;i++) {
		int k;
		cin>>k;
		for(int j=1;j<=k;j++) {
			int x;
			cin>>x;
			a[x][++siz[x]]=i;//统计动物园动物个数
		}
	}
	dfs(1);
	cout<<res<<endl;
	return 0;
}

```

---

## 作者：wwwidk1234 (赞：0)

## 题目

一共有 $n$ 个动物园，第 $i$ 个动物园有 $k_i$ 种动物，门票价为 $c_i$，一位旅行者想看 $m$ 种动物，每种动物至少看两次。问怎么样访问动物园可以使得门票价总和最少。

## 思路

看到 $n \le 10$ 考虑 DFS。

对于每一个动物园有**三种方案：去 $0,1,2$ 次。**（因为看一个动物两次后就没有必要再去看了，所以去了同一个动物园两次以上等价于去两次。）

暴力搜索每一种方案，然后在搜完 $n$ 个动物园之后**检查一下是否所有动物都被看了至少两次**，如果是的话那就**更新最小值**。

注意可以加一个**最优性剪枝**：如果当前搜到的方案已经比最佳方案差，那么可以直接舍弃该方案。

## 代码

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=17;
constexpr int M=107;
int n,m,k,a;  //a[i][j]:第i个动物可以在a[i][j]动物园看到
ll c[N];
vector<int> z[N];  //z[i]:第i个动物园中含有的动物
int seen[M];
ll ans=1e18;
inline bool check()
{
    for(int i=1;i<=m;i++) if(seen[i]<2) return 0;
    return 1;
}
void dfs(int dep,ll val)
{
    if(val>ans) return ;  //最优性剪枝
    if(dep>n)
    {
        if(check())
        {
            ans=min(ans,val);
            return;
        }
        return;
    }
    for(int cnt=0;cnt<=2;cnt++)
    {
        for(int i:z[dep]) seen[i]+=cnt;
        dfs(dep+1,val+cnt*c[dep]);
        for(int i:z[dep]) seen[i]-=cnt;
    }
}
int main()
{
    //freopen("neuvillette.in","r",stdin);
    //freopen("neuvillette.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=m;i++)
    {
        cin>>k;
        for(int j=1;j<=k;j++)
        {
            cin>>a;
            z[a].push_back(i);
        }
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
/*
每个动物园最多去两次
*/
```

---

