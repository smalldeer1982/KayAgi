# [ABC170E] Smart Infants

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc170/tasks/abc170_e

AtCoder に参加している幼児が $ N $ 人おり、$ 1 $ から $ N $ の番号が付けられています。また、幼稚園が $ 2\times\ 10^5 $ 校あり、$ 1 $ から $ 2\times\ 10^5 $ の番号が付けられています。 幼児 $ i $ のレートは $ A_i $ であり、はじめ幼稚園 $ B_i $ に所属しています。

これから $ Q $ 回にわたって、転園が行われます。 $ j $ 回目の転園では、幼児 $ C_j $ の所属を幼稚園 $ D_j $ に変更します。

ここで、「平等さ」を、AtCoderに参加している幼児が一人以上いるような幼稚園それぞれについて園内で最もレートの高い幼児のレートを求め、その最小値として得られる値とします。

$ Q $ 回それぞれの転園後の平等さを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ C_j\ \leq\ N $
- $ 1\ \leq\ B_i,D_j\ \leq\ 2\ \times\ 10^5 $
- 入力はすべて整数である。
- $ j $ 回目の転園の前後で幼児 $ C_j $ の所属は異なる。

### Sample Explanation 1

はじめ、幼稚園 $ 1 $ には幼児 $ 1,\ 4 $、幼稚園 $ 2 $ には幼児 $ 2,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 6 $ が所属しています。 $ 1 $ 回目の転園で幼児 $ 4 $ の所属を幼稚園 $ 3 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 1 $、幼稚園 $ 2 $ には幼児 $ 2,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 8 $、幼稚園 $ 2 $ では $ 6 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 6 $ であるので、$ 1 $ 行目には $ 6 $ を出力します。 $ 2 $ 回目の転園で $ 2 $ 番目の幼児の所属を幼稚園 $ 1 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 1,\ 2 $、幼稚園 $ 2 $ には幼児 $ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 8 $、幼稚園 $ 2 $ では $ 2 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 2 $ であるので、$ 2 $ 行目には $ 2 $ を出力します。 $ 3 $ 回目の転園で $ 1 $ 番目の幼児の所属を幼稚園 $ 2 $ に変更すると、幼稚園 $ 1 $ には幼児 $ 2 $、幼稚園 $ 2 $ には幼児 $ 1,\ 5 $、幼稚園 $ 3 $ には幼児 $ 3,\ 4,\ 6 $ が所属している状態になります。幼稚園 $ 1 $ で最もレートの高い幼児のレートは $ 6 $、幼稚園 $ 2 $ では $ 8 $、幼稚園 $ 3 $ では $ 9 $ です。これらの最小値は $ 6 $ であるので、$ 3 $ 行目には $ 6 $ を出力します。

## 样例 #1

### 输入

```
6 3
8 1
6 2
9 3
1 1
2 2
1 3
4 3
2 1
1 2```

### 输出

```
6
2
6```

## 样例 #2

### 输入

```
2 2
4208 1234
3056 5678
1 2020
2 2020```

### 输出

```
3056
4208```

# 题解

## 作者：Tmbcan (赞：2)

## [[ABC170E] Smart Infants](https://www.luogu.com.cn/problem/AT_abc170_e)

### 题目描述
有 $N$ 个婴儿，初始时 Rating 为 $A_i$，位于 $B_i$ 幼儿园。$Q$ 次操作，每次会有一个婴儿“转园”。求每次操作后，每个幼儿园中婴儿最大 Rating 的最小的值。

### 思路
我们考虑对每一个幼儿园中婴儿的 Rating 都维护一个 `multiset`，再对每个幼儿园中婴儿的最大 Rating 维护一个 `multiset`。

我们记录每个婴儿所在的幼儿园，每次“转园”时在 `multiset` 里删加值模拟转园过程即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<set>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T&x){
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 2e5+10;
int id[N],sc[N];
multiset <int> maxn,s[N];//维护两个multiset
int n,T;
inline void add(int tid,int k){//加入
	if(!s[k].empty()){//删空指针就RE了
		auto it = s[k].end();
		it--;
		int mx = *it;
		maxn.erase(maxn.find(mx));
	}
	s[k].insert(id[tid]);
	auto it = s[k].end();
	it--;
	int mx = *it;
	maxn.insert(mx);
} 
inline void del(int tid,int k){//退出
	auto it = s[k].end();
	it--;
	int mx = *it;
	maxn.erase(maxn.find(mx));
	s[k].erase(s[k].find(id[tid]));
	if(!s[k].empty()){
		auto it = s[k].end();
		--it;
		int mx = *it;
		maxn.insert(mx);
	}
}
int main(){
	read(n,T);
	for(int i=1,a,b;i<=n;++i){
		read(a,b);
		id[i] = a;
		sc[i] = b;
		add(i,b);
	} 
	for(int i=1,u,v;i<=T;++i){
		read(u,v);
		del(u,sc[u]);//转园
    	add(u,v);
	    sc[u] = v;
		printf("%d\n",(*maxn.begin()));
	}
	return 0;
}

```

---

## 作者：MarSer020 (赞：2)

不优美的 $\text{STL}$ 史题。

$\Large\text{Solution}$

一眼丁真，鉴定为：$\text{STL}$ 大法好。

显然只需要用 $\text{multiset}$ 维护每个幼儿园里面婴儿的 $\text{Rating}$，再使用一个 $\text{multiset}$ 维护每个幼儿园里面的最大值即可。

每次只需要修改 $3$ 个 $\text{multiset}$ 的值，时间复杂度 $\Theta(n\log q+m)$，其中 $m$ 为幼儿园的个数。

注意到 $\text{multiset}$ 中的 $\text{erase}$ 在传入数值时会移除所有等于该数值的位置，传入指针即可。

注意特判空集。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y;
pair<int,int>id[200005];
multiset<int>a[200005],b;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>x>>y,a[y].emplace(x),id[i]={x,y};
    for(int i=1;i<=200000;i++)
        if(!a[i].empty())
            b.emplace(*a[i].rbegin());
    while(q--){
        cin>>x>>y;
        if(!a[y].empty())
            b.erase(b.find(*a[y].rbegin()));
        b.erase(b.find(*a[id[x].second].rbegin())),a[id[x].second].erase(a[id[x].second].find(id[x].first));
        if(!a[id[x].second].empty())
            b.emplace(*a[id[x].second].rbegin());
        a[y].emplace(id[x].first),b.emplace(*a[y].rbegin()),id[x].second=y,cout<<*b.begin()<<'\n';
    }
    return 0;
}
```

---

## 作者：stripe_python (赞：1)

某知名模拟赛的水 T1。来写篇题解。

使用一种数据结构维护每个组，需要支持：加入、删除、查最大。可以使用 `std::multiset`。接下来可以使用类似的数据结构维护答案，支持加入、删除、查最小即可。

所以本题用 `multiset` 套 `multiset` 即可。复杂度 $O(q \log n)$。

但是本题有一些坑点：

1. 加值删值的时候没有必要分类讨论，直接无脑删完再加就行了。
2. 判空！不然会 RE 的很惨。
3. `std::multiset.erase` 会删除所有值相等的元素！要用 `erase(find(x))` 删！因为这个本蒟蒻挂了 $30$ pts。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

multiset<int> g[N];    // 存储每个组
multiset<int> mx;    // 存储答案
int n, q, a[N], b[N], c, d;

void _main() {
	cin >> n >> q;
	int maxg = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		maxg = max(maxg, b[i]);
		g[b[i]].emplace(a[i]);
	}
	for (int i = 0; i <= maxg; i++) {
		if (!g[i].empty()) mx.emplace(*g[i].rbegin());
	}
	
	while (q--) {
		cin >> c >> d;
		mx.erase(mx.find(*g[b[c]].rbegin()));
		g[b[c]].erase(g[b[c]].find(a[c]));
		if (!g[b[c]].empty()) mx.emplace(*g[b[c]].rbegin());
		
		b[c] = d;
		if (!g[b[c]].empty()) mx.erase(mx.find(*g[b[c]].rbegin()));
		g[b[c]].emplace(a[c]);
		mx.emplace(*g[b[c]].rbegin());
		cout << *mx.begin() << '\n';
	}
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr);
#ifndef SPN_LOCAL
	freopen("work.in", "r", stdin);
	freopen("work.out", "w", stdout);
#endif
	
	int t = 1;
	//cin >> t;
	while (t--) _main();
	return 0;
}
```

---

## 作者：yangdezuo (赞：1)

## 思路
根据题目，我们要求每个幼儿园中 Rating 最高的婴儿，他们中最低的 Rating。

因此，使用 STL 大法，用 $\texttt{multiset}$ 来维护维护每个幼儿园里面的最大值。

因为婴儿会转幼儿园，所以我们既要删除在原来幼儿园中的婴儿（删除时会删除这个值的所有位置），也要插入婴儿到新的幼儿园。

#### 时间复杂度
输入初始化，每次插入为 $O(\log n)$，因此为 $O(n \log n)$；

处理 $q$ 次操作，每次删除、插入为 $O(\log n)$，$q$ 个就是 $O(q \log n)$；

综上，时间复杂度为 $O(n \log n + q \log n)$。
## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=256567;
int n,q,a,b,f[N],c[N],p1,p2;
multiset<int>ans,t[N];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){//输入最开始婴儿的rating和位置
		cin>>a>>b;
		f[i]=a;
		c[i]=b;
		t[b].insert(a);//记录每个学生对应的rating
	}
	for(int i=1;i<=2e5;i++){//预处理
		if(t[i].size()==0) continue;//判断是否为空集
		auto it=t[i].end();
		it--;
		ans.insert(*it);
	}
	while(q--){
		cin>>a>>b;
		p1=c[a],p2=b;
		ans.erase(ans.find(*prev(t[p1].end())));
		t[p1].erase(t[p1].find(f[a]));
		if(t[p1].size()>0) ans.insert(*prev(t[p1].end()));
		if(t[p2].size()>0) ans.erase(ans.find(*prev(t[p2].end())));
		t[p2].insert(f[a]);
		ans.insert(*(prev(t[p2].end())));
		c[a]=b;
		cout<<*ans.begin()<<"\n";
	}
}
```

---

## 作者：YuYuanPQ (赞：0)

思考众多数据结构后，我们可以发现使用 `multiset` 较为方便。

这道题还是比较良心的：（只是）单点修改，“区间”查询。

先预处理出各个幼儿园的婴儿最高 Rating，把它们放到 $mx$ 这个 `multiset` 里。\
对于每次修改，则：
- 删除 $mx$ 中，$C_j$ 号婴儿所在幼儿园和 $D_j$ 号幼儿园的最高 Rating 值。（$2$ 个）
- 删除 $C_j$ 号婴儿的 Rating（即 $a_{C_j}$），加入到 $D_j$ 号幼儿园的集合中。
- 把 $C_j$ 号婴儿所在幼儿园和 $D_j$ 号幼儿园的最高 Rating 值加入到 $mx$ 中。

这样就做完了。（虽然看起来有点复杂，但是不用动脑）

**注意**：
- 为了方便得到 $x$ 号婴儿所在的幼儿园编号，可以用 `map` 存。（因为值域小所以我直接开数组了）
- **一定要先判断 `multiset` 是否为空！！！！！！（你猜我代码为啥这么丑）**

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
typedef __int128 int128;
typedef double DB;
typedef long double LDB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))

using namespace std;

const int N=2e5+10;

int n,q;
int a[N],b[N];

multiset<int>st[N],mx;
set<int>hav;
// unordered_map<IT,IT>mp;
int mp[N];

int main(){
    // for(int i=1;i<=2e5;i++) st[i].insert(-1);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        st[b[i]].insert(a[i]);
        // mp[a[i]]=b[i];
        mp[i]=b[i];
        hav.insert(b[i]);
    }

    // cout<<"DB:::::::\n";
    for(set<int>::iterator it=hav.begin();it!=hav.end();it++){
        int id=*it;
        // cout<<id<<":\n";
        // for(auto it2=st[id].begin();it2!=st[id].end();it2++) cout<<*it2<<" ";cout<<endl;
        int val=*st[id].rbegin();
        // cout<<"val= "<<val<<endl;
        mx.insert(val);
    }// cout<<endl;

    // cout<<"DB::\n";
    // cout<<"size= "<<mx.size()<<endl;
    // for(multiset<int>::iterator it=mx.begin();it!=mx.end();it++){
    //     cout<<*it<<" ";
    // }cout<<endl;

    // cout<<*mx.lower_bound(6)<<endl;
    // cout<<*mx.find(6)<<endl;
    // return 0;

    while(q--){
        int c,d;
        scanf("%d%d",&c,&d);

        // mx.erase(mx.find(*st[mp[c]].rbegin()));
        // mx.erase(mx.find(*st[d].rbegin()));
        // cout<<"114513\n";
        // cout<<*st[mp[c]].rbegin()<<endl;
        auto t1=mx.lower_bound(*st[mp[c]].rbegin());
        // cout<<"114514-1\n";
        auto t2=t1;
        if(st[d].size()) t2=mx.lower_bound(*st[d].rbegin());
        // cout<<"114514-2\n";
        // cout<<"114514\n";
        // cout<<*t1<<" "<<*t2<<endl;
        mx.erase(t1);
        if(st[d].size()) mx.erase(t2);
        // cout<<"finish1!\n";

        st[mp[c]].erase(st[mp[c]].find(a[c]));
        st[d].insert(a[c]);
        // mp[c]=d;
        // cout<<"finish2!\n";

        if(st[mp[c]].size()) mx.insert(*st[mp[c]].rbegin());
        // cout<<"finish2-2\n";
        mx.insert(*st[d].rbegin());
        // cout<<"finish3!\n";
        mp[c]=d;

        printf("%d\n",*mx.begin());
    }
    return 0;
}
```

[Link](https://atcoder.jp/contests/abc170/submissions/65980674)

---

## 作者：Gapple (赞：0)

对于每个幼儿园维护婴儿 rating 的 `multiset`，再维护这些幼儿园最大 rating 的 `multiset`（设其为 $M$）。

修改时：

- 如果要修改的婴儿 rating 为原来幼儿园中的最大值，就更新 $M$。
- 如果要修改的婴儿 rating 为新的幼儿园中的最大值，也要更新 $M$。

注意判定 `multiset` 是否为空。

```cpp
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
using i64 = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> rating(n), in(n);
    map<int, multiset<int>> children;
    multiset<int> mx;

    for (int i = 0; i < n; ++i) {
        cin >> rating[i] >> in[i];
        children[in[i]].emplace(rating[i]);
    }

    for (const auto& [idx, rate] : children)
        mx.emplace(*rate.rbegin());

    while (q-- > 0) {
        int idx, to;
        cin >> idx >> to;

        int from = in[--idx], rate = rating[idx];
        bool is_max = false;

        if (rate == *children[from].rbegin() && children[from].count(rate) == 1) {
            mx.erase(mx.find(rate));
            is_max = true;
        }

        children[from].erase(children[from].find(rate));

        if (is_max && !children[from].empty())
            mx.emplace(*children[from].rbegin());

        int curr_max = -1;

        if (!children[to].empty())
            curr_max = *children[to].rbegin();

        children[to].emplace(rate);

        if (rate == *children[to].rbegin() && children[to].count(rate) == 1) {
            mx.emplace(rate);

            if (children[to].size() > 1)
                mx.erase(mx.find(curr_max));
        }

        in[idx] = to;
        cout << *mx.begin() << '\n';
    }

    return 0;
}
```

---

## 作者：ylch (赞：0)

题目要快速查找最大最小值，还要快速地插入删除，还要允许重复的元素存在。显然可以用 mulitset 解决。

对每个幼儿园都开一个多重集合，模拟即可（代码中有详细注释）。

有一个细节，multiset 的 `erase()` 函数传值时会把所有值相同的元素都删除，所以考虑先 `find()` 出一个迭代器，然后直接传入迭代器删除，就能每次只删除一个值了。

对于查询操作，考虑再开一个 multiset 维护答案，每次操作时先把两个幼儿园对答案的贡献都删去，操作完后再加回来即可。这样加回来的是更新后的值。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 7;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n + 1);
    vector<multiset<int>> S(maxn, multiset<int>()); // 维护每个幼儿园
    multiset<int> T; // 维护答案
    generate(a.begin() + 1, a.end(), [&S](){
        int a, b; cin >> a >> b; S[b].insert(a); return make_pair(a, b);
    });
    for (auto it : S) {
        if (!it.empty()) {
            T.insert(*it.rbegin()); // 初始化每个幼儿园的最大值
        }
    }
    auto update = [&S, &T](int x, int f) { // 将幼儿园x对答案T的贡献 f=0:删除,f=1:加入
        if (f == 0 && !S[x].empty()) { // 如果不为空
            T.erase(T.find(*S[x].rbegin())); // 先find再删，这样只删一个
        }
        if (f == 1 && !S[x].empty()) {
            T.insert(*S[x].rbegin()); // 重新加入答案
        }
    };
    for (int i = 0; i < q; i ++) {
        int c, d;
        cin >> c >> d;
        update(d, 0); update(a[c].second, 0); // 去除两个人在答案中的贡献
        S[a[c].second].erase(S[a[c].second].find(a[c].first)); // 从原来的幼儿圆中删除
        S[d].insert(a[c].first); // 插入新的幼儿园里
        update(a[c].second, 1); update(d, 1); // 把贡献加回去
        a[c].second = d; // 更新c现在在的幼儿园（注意这一句放在上一句的后面，不然c原来在的幼儿园编号就丢失了）
        cout << *T.begin() << '\n'; // 每次输出最小值
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}

```

---

## 作者：Dtw_ (赞：0)

# Solution
可以用 `set` 和 `unordered_map` 存储，每次调动的时候，直接暴力改就行，具体看一下代码。

对于查询，我维护了一颗线段树，区间取 $\min$。

但我犯了个错，我线段树维护的时候值域是 $\max b$，但是调动的时候可能超过 $\max b$ 所以就寄了。

解决方案是直接照 $2\times 10^5$ 建就行。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define pii pair<int, int>

#define fi first
#define se second

#define endl '\n'

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int N = 2e5 + 10;

int n, q, a[N], b[N], id[N]; 

set<int> S[N];

int tr[N << 2];

#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define mid (l + r) / 2

inline void push_up(int rt)
{
	tr[rt] = min(tr[lson], tr[rson]);
}

void build(int rt, int l, int r)
{
	tr[rt] = INF;
	if (l == r)
	{
		if (S[l].size() == 0) return;
		tr[rt] = *S[l].rbegin();
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	push_up(rt);
}

void update(int rt, int l, int r, int p, int v)
{
	if (l == r)
	{
		tr[rt] = v;
		return;
	}
	if (p <= mid) update(lson, l, mid, p, v);
	else update(rson, mid + 1, r, p, v);
	push_up(rt);
}

unordered_map<int, int> mp[N];

signed main()
{
//	freopen("work.in", "r", stdin);
//	freopen("work.out", "w", stdout);
	fst
	cin >> n >> q;
	int maxb = 0;
	for (int i=1; i<=n; i++) cin >> a[i] >> b[i], S[b[i]].insert(a[i]), mp[b[i]][a[i]]++, maxb = max(maxb, b[i]);
	build(1, 0, 200000);
	while (q--)
	{
		int c, d;
		cin >> c >> d;
		int o = a[c];
		mp[b[c]][o]--;
		if (mp[b[c]][o] == 0) // 当前组没了，就删掉
		{
			S[b[c]].erase(o); // 删掉后要撤销掉最大值，即直接覆盖
			if (S[b[c]].size() == 0) update(1, 0, 200000, b[c], INF);
			else update(1, 0, 200000, b[c], *S[b[c]].rbegin());
		}
		S[d].insert(a[c]);
		b[c] = d;
		mp[d][a[c]]++;
		update(1, 0, 200000, d, *S[d].rbegin());
		if (tr[1] == INF) cout << 0 << endl;
		else cout << tr[1] << endl;
	}
	return 0;
}

```

---

## 作者：royle_9 (赞：0)

**使用 `set`**

 找出每个幼儿园中 `Rating` 最高以 `Rating` 最高中的最低可以分别用一个 `set` 数组和 `set`，因为 `set` 可以去重也可以自动排序（代码中的 `s[200010]` 和 `smin`）。
 - 调用的时候需要用指针 `set<int>iterator::it`。赋值的时候要先声明，再在下一行进行加 $1$ 或减 $1$ 的操作。
- 由于要记录婴儿的编号和 `Rating`，可以使用 `pair<int,int>` 的数据类型进行存储。访问第一个关键字时用 `->first`，第二个用 `->second`。特别地，该数据类型采用第一关键字排序，因此将 `Rating` 值放在第一关键字。

其他细节见代码。
```cpp
#include<iostream>
#include<set>
using namespace std;
typedef set<pair<int, int> >::iterator sit;
typedef pair<int, int> pii;
#define mp make_pair
int n, q;
int a[200010], b[200010];
set<pii> s[200010];//每个幼儿园中的Rating值（set中最后一项就是最大值，set可以自动按从小到大排序，若有pair时，则按first从小到大排序）
set<pii> smin;
int fa[200010];//编号为i的婴儿的幼儿园
int id[200010];//编号为i的婴儿的Rating值
int main(){
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i] >> b[i];
		s[b[i]].insert(mp(a[i], i));//因为按first，所以把Rating值放在前面
		fa[i] = b[i];
		id[i] = a[i];
	}
	for (int i = 1; i <= 200000; i++){//预处理：将刚开始的所有幼儿园的最大值存进去 
		if(!s[i].empty()){
			sit it = s[i].end();
			it--;
			smin.insert(*it);
		}
	}
	for (int i = 0; i < q; i++){
		int c, d;
		cin >> c >> d;
		sit itt = s[d].end();
		if(!s[d].empty()){
			itt--;
		}//原来d号幼儿园里的rating最大值的地址 
		sit itc = s[fa[c]].end();itc--;//编号为c的婴儿的原来幼儿园的rating最大值的地址 
		if(itc -> second == c){//如果编号为c的婴儿是其原来幼儿园里的最大值 
			smin.erase(mp(id[c], c));//存储每个幼儿园里最大值的set就先将他消除
			if(s[fa[c]].size() > 1){
				itc--;//这里再减1次是因为原来存编号为c的婴儿的set还没更新 
				smin.insert(mp(itc -> first, itc ->second));//消除后需加入编号为c的婴儿的原来幼儿园里的最大值
			}
		}
		s[fa[c]].erase(mp(id[c], c));
		s[d].insert(mp(id[c], c));
		sit it = s[d].end();it--;//现在d号幼儿园里rating最大值的地址
		if(itt != s[d].end()){
			if(it -> second != itt -> second){//如果d号幼儿园里rating最大值的婴儿被新来的打败了
				smin.erase(mp(itt -> first, itt -> second));
				smin.insert(mp(it -> first, it -> second));
			}
		} else {
			smin.insert(mp(id[c], c));
		} 
		sit ans = smin.begin();
		cout << ans -> first << endl;
		fa[c] = d;//更新编号为c的婴儿的幼儿园
	}
	return 0;
}

---

