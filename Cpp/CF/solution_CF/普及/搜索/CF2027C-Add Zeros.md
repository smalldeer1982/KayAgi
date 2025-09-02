# Add Zeros

## 题目描述

You're given an array $ a $ initially containing $ n $ integers. In one operation, you must do the following:

- Choose a position $ i $ such that $ 1 < i \le |a| $ and $ a_i = |a| + 1 - i $ , where $ |a| $ is the current size of the array.
- Append $ i - 1 $ zeros onto the end of $ a $ .

After performing this operation as many times as you want, what is the maximum possible length of the array $ a $ ?

## 说明/提示

In the first test case, we can first choose $ i = 4 $ , since $ a_4 = 5 + 1 - 4 = 2 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0] $ . We can then choose $ i = 3 $ since $ a_3 = 8 + 1 - 3 = 6 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0, 0, 0] $ , which has a length of $ 10 $ . It can be shown that no sequence of operations will make the final array longer.

In the second test case, we can choose $ i=2 $ , then $ i=3 $ , then $ i=4 $ . The final array will be $ [5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0] $ , with a length of $ 11 $ .

## 样例 #1

### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1```

### 输出

```
10
11
10
1```

# 题解

## 作者：Mirage_Insane (赞：6)

观察题目，发现只有当 $a_i = n - i + 1$ 时 $i$ 位置有贡献。所以要让 $i$ 有贡献，就需要在数组末尾增添 $a_i - (n - i + 1)$ 个空位。

考虑 dp。

设 $dp_i$ 为是否存在一种方案能往数组后面增添 $i$ 个空位。注意到值域非常大，所以需要利用记忆化搜索进行转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
map<long long, vector<int> > g;
map<long long, long long> dp;
long long dfs(long long now) {
	if(dp[now]) return dp[now];
	long long ans = now;
	for(int i : g[now]) ans = max(ans, dfs(now + i));
	return dp[now] = ans;
}
int main() {
	int T;
	SF("%d", &T);
	while(T--) {
		g.clear(), dp.clear();
		int n;
		SF("%d", &n);
		long long x;
		for(int i = 1; i <= n; i++) {
			SF("%lld", &x);
			if(i != 1 && x >= n - i + 1) g[x - (n - i + 1)].push_back(i - 1);
		}
		PF("%lld\n", dfs(0) + n);
	}
	return 0;
}
```

---

## 作者：一棉花糖一 (赞：3)

观察式子 

$$a_i= |a| + 1 - i$$

我们不妨将其变形为

$$ |a|=a_i + i - 1 $$

Note that:因为 $|a| \ge 0$，所以当 $a_i=0$ 时，命题为假，同时容易发现 
$$\forall i-1 < |a|(0 \le i-1 \le n-1)$$ 
所以，我们只需要考虑前 $n$ 个位置。
不难发现，对于位置 $i$，使用操作可以使 $|a|+i-1$，我们不妨令 $u_i=|a|=a_i+i-1$，一次操作后我们有 $v_i=u_i + i-1$。

考虑建图后 DFS，具体的，创建一个包含所有 $n$ 的图，从节点 $n$ 开始 DFS，容易得到：

$$ ans=\max\limits_{i \in G}(v_i) $$

注意一下细节，并用 vis 标记数组优化就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace my{
#define ll long long 
const int INF=(1<<31);
#define int long long
ll re ()
{
    ll t;
    cin>>t;
    return t;
}
void solve()
{
    int n=re();
    vector<int>A;
    for(int i=0;i<n;++i)
        A.push_back(re());
    map<int,vector<ll>>adj;
    for(int i=1;i<n;++i)
    {
        int u=A[i]+i;
        int v=u+i;
        adj[u].push_back(v);
    }
    set<int>vis;
    function<void(ll)> dfs=[&](int u)->void 
    {
        if(vis.count(u))
            return;
        vis.insert(u);
        for(auto &i:adj[u])
            dfs(i);
    };
    dfs(n);
    cout<<*vis.rbegin()<<'\n';
}
signed main ()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t=re();
    while(t--)
    {
        solve ();
    }
    return 0;
}
}
signed main ()
{
    return my::main();
}


```

---

## 作者：LEE114514 (赞：2)

## 思路

首先我们发现 $a_i$ 有用当且仅当某个时刻 $|a|=a_i+i-1$。

然后我们令这东西等于 $b_i$，并将它升序排序，排序前对应的 $i$ 记为 $c_i$。

维护集合 $S$，初始只有 $n$，扫描 $b$，如果 $b_i \in S$ 就将 $b_i+c_i-1$ 加入集合 $S$。

集合 $S$ 中最大元素即为答案。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T,n;
const int maxn=3e5+5;
pair<int,int> a[maxn];
void solve(){
	set<int> st;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i].first,a[i].first+=i-1,a[i].second=i;
	sort(a+1,a+n+1);
	st.emplace(n);
	for(int i=1;i<=n;++i) if(st.count(a[i].first)) st.emplace(a[i].first+a[i].second-1);
	cout<<*st.rbegin()<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--) solve();
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

令 $a$ 数组下标从 $0$ 开始。

当 $a_i+i=|a|$ 时会往 $a$ 末尾添 $i$ 个 $0$，即当数组长度为 $a_i+i$ 时可将长度改为 $a_i+2i$。将这个关系建图，答案为 $n$ 能到达的点中最大的编号。由于无环，直接记忆化搜索复杂度是 $O(n)$ 的。

---

## 作者：Him_shu (赞：0)

## 题意

给你一个数组 $a$，初始包含 $n$ 个整数，你可以进行如下操作：

- 选择一个 $i$ 使得 $1 < i \le \lvert a \rvert$ 且 $a_i = \lvert a \rvert + 1 - i$，其中 $\lvert a \rvert$ 是数组的**实时**长度
- 把 $i - 1$ 个 $0$ 加入到 $a$ 的末尾

在任意地进行该操作后，$a$ 可能的最大长度是多少？

## 分析

由 $a_i = \lvert a \rvert + 1 - i$ 可得要使 $a_i$ 可以做贡献，那么 $\lvert a \rvert =a_i+i-1$。

贡献的长度 $=i-1$。

那么可以发现一个结论，就是一个 $a_i$ 要做贡献，那么必须是一个小于 $a_i$ 在的一个 $a_j$ 在加上 $a_j$ 做的贡献 $j-1$ 达到的。~~（听起来没有用，但是是一个重要的结论）~~

那么就可以对其 $a_i+i-1$（可以做贡献的长度）进行排序。

那么就可以线性去记录当前点可不可以做贡献。（因为 $1 \le a_i \le 10^{12}$ 所有可以用 set 和 map 等 STL 解决）

到此问题解决。（不懂看代码的注释）

[**提交记录**](https://codeforces.com/contest/2027/submission/296288024)

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5,M=105,inf=1e14;//记得开的3e5不然会炸
struct info{
	int av,ad;
}a[N];//用结构体储存   av是可以做贡献的长度    ad是贡献的长度
int cmp(info x,info y){
	return x.av<y.av;
}//结构体的排序    对可以做贡献的长度从小到大排序
int t;
int n;
set<int>ss;//记录是否开放了
signed main(){
	cin>>t;
	while(t--){
		ss.clear();//清空，不清空两行泪
		cin>>n;
		ss.insert(n);//一开始时，可以做贡献的长度为N的已经开放
		for(int i=1,x;i<=n;i++){
			cin>>x;
			a[i].ad=i-1;
			a[i].av=x-1+i;//用数学得出可以做贡献的长度
		}
		sort(a+1,a+n+1,cmp);//排序
		int ans=n;//在没有时，答案是N
		for(int i=1;i<=n;i++){
//			cout<<a[i].av<<" "<<a[i].ad<<"\n";//调试
			if(ss.find(a[i].av)==ss.end()){continue;}//没有开放就没法做贡献
			ans=max(ans,a[i].av+a[i].ad);//更新答案
			ss.insert(a[i].av+a[i].ad);//做贡献并开放新的
		}
//		cout<<"ans=";
		cout<<ans<<"\n";
	}
	return 0;
}
```

## 感受

只因开小了，超时了好多发。![](https://qqemoji.heyc.eu.org/56x56/fn.gif)

---

## 作者：FurippuWRY (赞：0)

容易发现，对于 $a_i$，当 $|a| = a_i + i - 1$ 时，才能往数组末添加 $0$（因为添加的是 $0$，显然这些数不会参与到后面对数组的修改中，那么不考虑这些数），于是可以对于 $a_i$，将其能修改数组时的 $|a|$ 与修改完后新的 $|a|$ 存入一个 `set` 中（元素类型为 `pair<long long, long long>`，因 `set` 可以去重和排序，故使用 `set`）。定义 $ans = |a|$，接下来对每一个能到达的 $|a|$ 标记（在枚举前就对最初的 $|a|$ 标记）：枚举 `set` 中的元素 $i$，若 $i_{first}$ 被标记，则能修改数组，此时新的 $|a|$ 即为 $i_{second}$，并对 $i_{second}$ 标记，更新 $ans=\max(ans, i_{second})$，继续枚举，最后输出 $ans$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 998244353;

int t, n, a;
set<pair<int, int>> r;
map<int, bool> p; 

signed main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	while (t--) {
		r.clear();
		p.clear();
		cin >> n;
		int ans = n;
		for (int i = 1; i <= n; ++i) {
			cin >> a;
			int k = a - 1 + i;
			r.insert({k, k + i - 1});
		}
		p[n] = 1;
		for (auto i : r) {
			if (p[i.first] == 1) {
				ans = max(ans, i.second);
				p[i.second] = 1;
			}
		}
		cout << ans << '\n';
	}
	
	return 0;
}
```

---

