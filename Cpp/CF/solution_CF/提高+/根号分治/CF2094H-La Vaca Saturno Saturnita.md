# La Vaca Saturno Saturnita

## 题目描述

Saturnita 的情绪取决于一个长度为 $n$ 的数组 $a$（只有他知道其含义）以及一个函数 $f(k, a, l, r)$（只有他知道如何计算）。以下是该函数的伪代码实现：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

给定 $q$ 个查询，每个查询包含整数 $k$、$l$ 和 $r$。对于每个查询，请输出 $f(k,a,l,r)$ 的值。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
2 3 5 7 11
2 1 5
2 2 4
2310 1 5
4 3
18 12 8 9
216 1 2
48 2 4
82944 1 4```

### 输出

```
5
6
1629
13
12
520```

# 题解

## 作者：bluewindde (赞：4)

注意到每次 $k$ 除以一个大于 $1$ 的数至少减半，所以一次查询中 $k$ 至多变化 $\log V$ 次。

把相同的 $k$ 一起处理，重新描述 `f(k, a, l, r)`：

- 设当前位置为 $x$，初始 $x = l$；
- 每次移动到最小的 $x < y \leqslant r$，使得 $a_y \mid k, a_y \ne 1$，如果不存在则规定 $y = r + 1$；
- 向答案贡献 $k \cdot (y - x)$；
- $x \leftarrow y$，重复上述操作直到 $x > r$。

只需要快速求出 $y$，根号分治，设阈值 $B$，考虑 $x$ 的约数 $d$：

- 若 $d \leqslant B$，预处理 $nxt_{i, j}$ 表示 $i$ 之后第一个 $j$ 的位置即可；
- 若 $d > B$，预处理 $pos_x$ 表示 $x$ 的所有这样的约数在数组中出现过的位置，二分即可。

时间复杂度 $O(\frac {nV} B + q \log V (B + \log n))$，常数极小。$B = \frac n {\sqrt{q \log n}}$ 时取到最小值 $O(n \sqrt{q \log V} + q \log n \log V)$。实际上 $B$ 稍微取大一点更优。

@[modfisher](https://www.luogu.com.cn/user/605226) 大神指出可以离线避免二分。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long i64;

const int lim = 1e5;
const int B = 200;

vector<int> divs[lim + 5];

int n, q;
int a[100005];
vector<int> pos[100005];
int nxt[100005][B + 5];

static inline void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > B)
            for (int j = a[i]; j <= lim; j += a[i])
                pos[j].push_back(i);
    }
    for (int i = 1; i <= B; ++i)
        nxt[n + 1][i] = n + 1;
    for (int i = n; i; --i) {
        for (int j = 1; j <= B; ++j)
            nxt[i][j] = nxt[i + 1][j];
        if (a[i] <= B)
            nxt[i][a[i]] = i;
    }
    while (q--) {
        int k, l, r;
        cin >> k >> l >> r;
        i64 ans = 0;
        for (int x = l;;) {
            int to = r + 1;
            for (auto d : divs[k]) {
                if (d > B)
                    break;
                to = min(to, nxt[x][d]);
            }
            auto it = lower_bound(pos[k].begin(), pos[k].end(), x);
            if (it != pos[k].end())
                to = min(to, *it);
            ans += 1ll * (to - x) * k;
            // cerr << "  " << k << " jump " << x << " -> " << to << " | gain " << (to - x) * k << endl;
            x = to;
            if (x > r)
                break;
            while (k % a[x] == 0)
                k /= a[x];
        }
        cout << ans << '\n';
    }
    for (int i = 1; i <= n; ++i)
        if (a[i] > B)
            for (int j = a[i]; j <= lim; j += a[i])
                pos[j].clear();
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for (int i = 2; i <= lim; ++i)
        for (int j = i; j <= lim; j += i)
            divs[j].push_back(i);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：ctzm (赞：2)

VP 时想到的诡异非根号分治但通过做法。其实已经想了一个根号分治了，但感觉 Div.4 放根号分治有点遥遥领先了，所以没敢写。

---

题意简述：给定长度为 $n$ 的正整数数列 $a$，模拟以下伪代码函数：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

函数调用 $q$ 次，每次给出参数 $k,l,r$，回答结果。

$n,k,a_i \le 10^5,q \le 5 \times 10^4$。

---

本题考查敢写。VP 时感觉此做法过于诡异，不敢写，费劲优化才逐渐信任此做法。

注意到 $k$ 一旦除以其他数，至少减半，所以实际次数为 $\log$ 量级。并且除以某个数后会直接把 $k$ 潜在的因子全部榨干（以后再遇到这个数就不会触发除了），实际上是不重复的，最坏是 $8! = 40320$，共 $7$ 次（$1$ 不算在内）。

这意味着实际上很多的遍历到的 $a_i$ 并不对 $k$ 产生影响，考虑如何快速找到使得一个 $k$ 降低的位置，就可以计算一段区间的贡献（$k$ 不变的一段），这个位置就是在 $l$ 后面最近的 $i$ 使得 $a_i | k$。这样子 $f(k,a,l,r)$ 就变成了 $k \times (i-l) + k_{new} + f(k_{new},a,i+1,r)$。

显然你不能开 $10^{10}$ 的空间，注意到 $10^5$ 以内的数因数个数肯定不会很多（实际最多为 $128$ 个），我们直接枚举其因数，然后用二分求最近的 $i$ 即可。

笔者 VP 时怕 TLE，改写成了一个奇奇怪怪的离线 + 队列，就没有二分的 $\log$ 了，交上去还不到时限的十分之一。

尽可能添加了自认为较为详细的注释，辅助代码理解可能会更好一些。~~（当然也可能需要更多的精力来理解我的丑陋代码）~~

运算量为 $50000 \times 128 \times 7 = 44800000$，足以通过本题（[389 ms	144900 KB](https://codeforces.com/contest/2094/submission/323763339)）。本题甚至开了 4s 时限。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int t,n,q,a[100010];
long long ans[50050];
vector<int> f[100010];//f[i] i的因子    不包括 1
struct qu{
	int id,k,r;
};
queue<qu> b[100010];//离线查询 下标就是l 
queue<int> c[100010];//O(1)求最近i的队列 
void init(){//预处理因子 
	for(int i=2;i<=N;i++){
		for(int j=i;j<=N;j+=i)f[j].push_back(i);
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	cin>>t;
	init();
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			c[a[i]].push(i);
		}
		for(int i=1;i<=q;i++){
			int k,l,r;
			cin>>k>>l>>r;
			b[l].push({i,k,r});
		}
		for(int i=1;i<=n;i++){
			while(!b[i].empty()){
				qu _=b[i].front();
				b[i].pop();
				int new_l=_.r+1;//找最近的i，添加完贡献后就变成了另一个函数
				//由于函数的l转化后单调递增 所以队列就以l为下标 循环里也是i从小到大 
				for(int j:f[_.k]){
					while(!c[j].empty()&&c[j].front()<i)c[j].pop();
					if(!c[j].empty())new_l=min(new_l,c[j].front());
				}
				if(new_l>_.r)ans[_.id]+=1ll*(_.r-i+1)*_.k;//找不到的话就结束 
				else{
					ans[_.id]+=1ll*(new_l-i)*_.k;//添加贡献 
					while(_.k%a[new_l]==0)_.k/=a[new_l];
					ans[_.id]+=_.k; //添加贡献 
					if(new_l+1<=n)b[new_l+1].push(_);
				}
			}
		}
		for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
		
		//下面都是多测清空 保险全清了 
		for(int i=1;i<=q;i++)ans[i]=0;
		for(int i=1;i<=n;i++){
			while(!c[a[i]].empty())c[a[i]].pop();
			while(!b[i].empty())b[i].pop();
			a[i]=0;
		}
	}





	return 0;
}


// 50000 * 128 * 7 = 44800000 
// https://codeforces.com/contest/2094/submission/323763339
```

---

## 作者：szh_AK_all (赞：2)

定义**有用的操作**为 $k$ 在不断除以某个 $a_i$ 后值改变了，也就是 $a_i$ 是 $k$ 的因子。那么可以发现有用的操作是 log 级别的，因为每次 $k$ 至少除以 $2$。

那么可以找出 $k$ 的所有因子，因子个数是根号级别的，可以接受，然后再记录 $a$ 数组中每个数字出现的位置。每次我们看第一次碰到有用的操作是在哪个位置，也就是对于 $k$ 的每个因子，找出 $a$ 中值刚好为该因子的元素对应的在合法范围内的下标，然后对这些下标取最小值即可。

最后如果 $k$ 不能再操作了要及时中断。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], b[N], vis[N], pri[N], tot;
vector<int>g[N], w[N];
 
signed main() {
	//ios::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);
	g[1].push_back(1);
	for (int i = 2; i <= 1e5; i++) {
		if (!vis[i]) {
			g[i].push_back(i);
			g[i].push_back(1);
			pri[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pri[j] <= 1e5; j++) {
			vis[i * pri[j]] = 1;
			g[i * pri[j]] = g[i];
			for (int x : g[i])
				g[i * pri[j]].push_back(x * pri[j]);
			if (i % pri[j] == 0)
				break;
		}
	}
	int t;
	cin >> t;
	while (t--) {
		int n, q;
		cin >> n >> q;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			w[a[i]].push_back(i);
		}
		int da = 0;
		while (q--) {
			int k, l, r;
			cin >> k >> l >> r;
			int nl = l;
			while (1) {
				int now = 1000000000;
				for (int x : g[k]) {
					int ll = 0, rr = (int)w[x].size() - 1, ans = -1;
					while (ll <= rr) {
						int mid = (ll + rr) / 2;
						if (w[x][mid] < nl)
							ll = mid + 1;
						else if (w[x][mid] > r)
							rr = mid - 1;
						else {
							ans = mid;
							rr = mid - 1;
						}
					}
					if (ans != -1)
						now = min(now, w[x][ans]);
				}
				if (k == 1 || now > 10000000) {
					da += k * (r - nl + 1);
					break;
				}
				da += k * (now - 1 - nl + 1);
				while (k % a[now] == 0)
					k /= a[now];
				da += k;
				nl = now + 1;
				if (nl > r)
					break;
			}
			cout << da << "\n";
			da = 0;
		}
		for (int i = 1; i <= n; i++)
			w[a[i]].clear();
	}
}
```

---

## 作者：biyi_mouse (赞：1)

根号分治题，可惜我没做出来（其实主要还是没想到第二种预处理）。

对于一个询问显然直接循环做没有前途，原因是会遍历很多 `useless` 状态无法改变 $k$。不妨考虑如何快速从一个 `useful` 状态跳到另一个 `useful` 状态。

首先会发现 $k \leq 100000$，这代表所有询问实际上都比较小，所以它们的约数也都比较小。比较自然的有一种类似序列自动机的预处理，设 $ne_{i, j}$ 为 $i$ 及它后面 $j$ 第一次出现的位置。转移是轻松的。

这样做是 $O(nV)$ 的。我们考虑这个做法的瓶颈在于值域 $V$ 太大了，所以我们不妨根号分治。只处理值域 $\leq B$ 的情况。而对于值域 $> B$ 的情况我们可以类似筛法地把求出 $pos_x$ 表示 $x$ 在 $a$ 中的所有因数。

然后对于询问，按照最开始提到的思路做即可。需要注意的是我们每次需要在 $pos$ 中二分，所以还要加个 $\log$。整个时间复杂度是 $O(nB + \frac{nV}{B} + q\log V(\log n + B))$。$B$ 随便取个 $250$ 就跑的很快了。

```cpp
const int N = 100010, B = 250;
int n, q, a[N];
int ne[N][B];
vector<int> divs[N], pos[N];

void solve() {
    n = read(), q = read();
    for (int i = 1; i <= n; i ++) a[i] = read();
    for (int i = 1; i <= B; i ++) ne[n + 1][i] = n + 1;
    for (int i = 1; i <= n; i ++) {
        if (a[i] > B) 
            for (int j = a[i]; j <= N - 10; j += a[i])
                pos[j].push_back(i);
    }
    for (int i = n; i >= 1; i --) {
        for (int j = 1; j <= B; j ++) ne[i][j] = ne[i + 1][j];
        if (a[i] <= B) ne[i][a[i]] = i;
    }
    while (q --) {
        int k = read(), l = read(), r = read();
        LL ans = 0;
        for (int p = l; ; ) {
            int R = r + 1;
            for (auto x : divs[k]) 
                if (x <= B) R = min(R, ne[p][x]);
            auto it = lower_bound(pos[k].begin(), pos[k].end(), p);
            if (it != pos[k].end()) R = min(R, *it);
            ans += 1ll * (R - p) * k;
            p = R;
            if (p > r) break;
            while (k % a[p] == 0) k /= a[p];
        }   
        printf("%lld\n", ans);
    }
    for (int i = 1; i <= n; i ++) {
        if (a[i] > B) 
            for (int j = a[i]; j <= N - 10; j += a[i])
                pos[j].clear();
    }
}

int main() {
    for (int i = 2; i <= N - 10; i ++)
        for (int j = i; j <= N - 10; j += i)
            divs[j].push_back(i);
    int T = read(); 
    while (T --) solve();
    return 0;
}
```

---

## 作者：xyvsvg (赞：0)

提供一个无需根号分治的离线做法。

显然每个数至多变化 $O(\omega(k))$ 次（$\omega(k)$ 表示 $k$ 的质因数个数）因此我们算法的主要难点在于如何找到下一个 $i$，使得 $a_i\mid k$。

考虑离线，我们对每个 $i$，维护有关 $i$ 的询问，表示当前某个询问“停留”在 $i$ 上（初始时每个询问在其对应的 $l$ 上）。

每轮操作，我们倒序扫描 $a$，处理每个“停留”在 $i$ 上的询问：先不断令 $k\gets k \div a_i$，直到 $a_i\nmid k$，然后枚举所有因数，找到下一个要“跳”的位置（利用 $nxt$ 数组），加上贡献即可，最后，更新 $nxt_{a_i}=i$，表示最近的 $a_i$ 出现在 $i$ 位置。

由于一个数的质因子个数极少，因此并不会循环多少轮（$10^5$ 的范围下至多 $6$ 轮）。

复杂度为 $O(\max \{\omega(k)\}(n+\sum d(k)))$，$d(k)$ 表示 $k$ 的因数个数。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5;
typedef pair<int,int> P;
typedef array<int,3> A;
typedef long long ll;
int nxt[N+10];
vector<int>dv[N+10];
void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>a(n+10);
    vector<ll>ans(m);
    vector<vector<A> >qs(n+10);
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=0;i<m;++i)
    {
        int k,l,r;
        cin>>k>>l>>r;
        qs[l].push_back({i,k,r});
    }
    for(bool flag=1;flag;)
    {
        vector<vector<A> >tmp(n+10);
        flag=0;
        for(int i=n;i;--i)
        {
            for(auto&[j,k,r]:qs[i])
            {
                while(k%a[i]==0)
                    k/=a[i];
                int mn=r+1;
                for(int d:dv[k])
                    mn=min(mn,nxt[d]);
                ans[j]+=1LL*k*(mn-i);
                if(mn<=r)
                    tmp[mn].push_back({j,k,r}),flag=1;
            }
            nxt[a[i]]=i;
        }
        for(int i=n;i;--i)
            nxt[a[i]]=N+5;
        swap(tmp,qs);
    }
    for(auto x:ans)
        cout<<x<<'\n';
}
int main()
{
    fill(nxt,nxt+N+10,N+5);
    for(int i=1;i<=N;++i)
        for(int j=i;j<=N;j+=i)
            dv[j].push_back(i);
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

发现 $k$ 真正能除以 $a_i$ 的次数不超过 $\log k$ 次，而 $k$ 不变的部分可以直接统计。因此我们需要快速找到下一个 $a_i\mid k$ 的 $i$。

考虑对 $a_i$ 根号分治，我们钦定一个阀值 $B$，在跳的过程中维护一个 $now$ 表示当前位置。

+ 当 $a_i\le B$ 时，$a_i$ 的种类数最多只有 $B$ 个。维护一个 $nxt_{i,j}$ 表示 $i$ 下一个 $j$ 的位置。每次跳的时候枚举当前 $k$ 的因数 $d$，选择最近的一个 $nxt_{now,d}$。

+ 当 $a_i>B$ 时，在 $10^5$ 范围内，$a_i$ 的倍数不超过 $B$ 个。因此对于每个 $k$ 的取值，预处理出满足 $a_i\mid k$ 的位置，放入 vector 中二分查找在 $now$ 后面的位置。和 $a_i\le B$ 的情况取最小值。

由于我的数学素养很差，并不会分析，因此 $B$ 直接取 $\sqrt{10^5}$ 即可通过，跑得还很快。

[submission](https://codeforces.com/contest/2094/submission/319794464)

---

