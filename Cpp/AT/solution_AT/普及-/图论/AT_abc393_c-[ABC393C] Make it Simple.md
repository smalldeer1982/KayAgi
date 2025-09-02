# [ABC393C] Make it Simple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc393/tasks/abc393_c

给定一个包含 $ N $ 个顶点和 $ M $ 条边的无向图，顶点编号为 $ 1 $ 到 $ N $，边编号为 $ 1 $ 到 $ M $。边 $ i $ 连接顶点 $ u_i $ 和顶点 $ v_i $。  
为了使图变为简单图（即不包含自环和多重边的图），至少需要移除多少条边？

## 说明/提示

### 约束条件

- $ 1 \leq N \leq 2 \times 10^5 $
- $ 0 \leq M \leq 5 \times 10^5 $
- $ 1 \leq u_i \leq N $
- $ 1 \leq v_i \leq N $
- 输入中所有值均为整数

### 样例解释 1

移除边 $ 3 $ 和边 $ 5 $ 后，图将变为简单图。这是移除边数最小的方案之一，因此答案为 $ 2 $。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 5
1 2
2 3
3 2
3 1
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
6 10
6 2
4 1
5 1
6 6
5 3
5 1
1 4
6 4
4 2
5 6```

### 输出

```
3```

# 题解

## 作者：Zskioaert1106 (赞：4)

题目传送门：[AT_abc393_c [ABC393C] Make it Simple](https://www.luogu.com.cn/problem/AT_abc393_c)

### 题意翻译

给你一个 $N$ 个顶点和 $M$ 条边的无向图，求删掉多少边能使图变成简单图（没有重边和自环）。

### 题目分析

删掉重边和自环即可变成简单。对于自环我们判断一下边的起终点是否相同即可。对于重边我们可以将每个点的边排下序，如果该边与上一条边相同就将答案加 $1$。

因为所有的边数不超过 $5\times 10^5$，所以排序 $O(M \log M)$ 的复杂度可以过。

### 警示后人

注意到无向图中每个边会被加入两次，所以答案要除以 $2$。

### 最终代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,ans=0;
vector<int>a[200001];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		a[u].push_back(v),a[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		sort(a[i].begin(),a[i].end());
		int p=0;
		for(int j:a[i]){
			if(j==i||j==p)ans++;
			p=j;
		}
	}
	cout<<ans/2;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/204032377)。

---

## 作者：chinazhanghaoxun (赞：3)

## 题目大意
给定一个无向不简单图，求出至少需要删除几条边才可以使此图变成简单图。
## 分析
首先，我们需要了解一下简单图的定义：
> 无向简单图是由一组顶点和一组无序的边组成的图，其中每条边连接两个不同的顶点，并且任意两个顶点之间最多有一条边。

简而言之，就是使一个简单图中不含重边和自环。

那么，我们就需要一个能够进行去重操作的容器，以便支持我们去掉重边，而只保留其中一条。对于处理自环就会很简单了，如果 $u=v$ 我们直接跳过即可。容易想到，可以使用 `set<pair<int,int> >` 完成目标，记录其大小 $e$ 就可以。最后的答案 $ans=m-e$。

我们已经解决了主要问题，还有一个小问题没有考虑到，就是本题中的边是无向边。我们就需要特定的存储方式。如每次都以编号小的为起点。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
set<pair<int,int> > e;
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		if(u==v)
			continue; 
		if(u>v)
			swap(u,v);
		e.insert({u,v});
	}
	cout<<m-e.size();
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

简单模拟题。

题目要求无重边无自环，那么不妨用 map 记录当前哪些点之间有连边，对于给定的每条边 $x$ 到 $y$，如果 $x,y$ 之间本身就有连边或者 $x=y$ 则这条边不能用。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int, int>q[200005];

int main() {
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if (q[u][v] || u == v)
			ans++;
		q[u][v] = q[v][u] = 1;
	}
	cout << ans;
}
```

---

## 作者：Tomwsc (赞：1)

# AT_abc393_c [ABC393C] Make it Simple 题解

## 题意

给定一个图，问要删除多少条边才能使其变成一个简单图。

简单图的定义是没有自环也没有重边的图。

## 解法

- 判断自环只需要判断连接边的两个端点是否相等即可。

- 判断重边只需要用一个 ```map``` 把出现的边保存起来，然后如果出现同样的边，就让答案加一。注意，两个端点的大小顺序是需要保证的。

~~还是很水的~~……

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , m;
map<pair<int , int> , bool>mapp;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	int cnt = 0;
	while(m --) {
		int u , v;
		cin >> u >> v;
    	//保证端点的顺序
		if(u > v)
			swap(u , v);
		if(u == v)
			cnt ++;
		else if(mapp[make_pair(u , v)])
			cnt ++;
		mapp[make_pair(u , v)] = true;
	}
	cout << cnt;
	return 0;
}
```

---

## 作者：天使宝贝 (赞：1)

### 题目大意
有一张无向图，图中有 $n$ 个顶点和 $m$ 条边，顶点的编号为 $1$ 到 $n$ ，边的编号为 $1$ 到 $m$ 。第 $i$ 条边连接顶点 $u_i$ 和 $v_i$ 。

现在要通过删除边使图变得简单，问必须删除的边的最少数目是多少？

### 思路&分析
不难看出，其实就是要找重复建过边的两个节点，或者跟自己连边的节点，那就直接维护一个 set，每回按顺序把 $u_i$ 和 $v_i$ 扔进 set 中，这样就会自动去掉重边了，不过需要注意的是 $u_i$ 不可以等于 $v_i$，最后的答案就是 $m$ 减去 set 的大小。

### CODE
代码也是出奇的短。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
set<pair<int, int>> s;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        if (u != v) s.insert({u, v});
    }
    cout << m - s.size() << endl;
    return 0;
}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc393_c)

### 思路

首先判断自环情况 $u=v$，多余的这条边一定时需要删除的，故将答案增加 $1$ 即可。

然后用一个 `map` 存储所有边，如果存在重复的边。存储完后进行遍历，有多少重边就要删去。

最后输出上述两次的总和即可。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
unordered_map<int,int>mp;
signed main(){
	int n=read(),m=read();
	int sum=0;
	while(m--){
		int u=read(),v=read();
		if(u==v)
			++sum;
		else{
			if(u>v)
				swap(u,v);
			++mp[u*(n+1)+v];
		}
	}
	int ans=0;
	for(auto i:mp)
		ans+=i.second-1;
	printf("%lld\n",ans+sum);
	return 0;
}
```

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc393/tasks/abc393_c)

## 题目简述
给定一个 $N$ 个顶点 $M$ 条边的图，求至少需要去掉几条边才能使这个图无自环和重边。

## 主要思路
判断自环比较好判断，只要 $u = v$ 就将答案加 $1$。判断重边可以维护一个 `map`，键类型为 `pair<int, int>`，值类型为 `int`，表示边的两个顶点分别是 `pair` 中的两个值出现了几次。

每次输入 $u$ 和 $v$ 时，如果不是自环，则让键为 $u$ 和 $v$ 以升序组成的 `pair` 加 $1$，升序是因为要让顶点相同但可能顺序不同的边算为同一条边。最后遍历每个值，如果某个值大于 $1$，则表示出现了重边，将答案增加值减 $1$。

## AC Code
```cpp
#include<map>
#include<cstdio>
#include<iostream>
using namespace std;

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#endif

#define endl '\n'
#define pc putchar
#define gc getchar
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)
void print(int x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
inline int read_int() { int f = 1, x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }return x * f; }
// ----------------------------

// ----------------------------
map<pii, int> mp;
// ----------------------------


int main() {
	int u, v, ans = 0, n = read_int(), m = read_int();
	rep(i, 1, m) {
		u = read_int(), v = read_int();
		if (u == v) ans++;
		else {
			if (u > v) swap(u, v);
			mp[make_pair(u, v)]++;
		}
	}
	// ----------------------------
	for (auto i : mp) ans += i.second - 1;
	// ----------------------------
	print(ans);
	return 0;
}
/*
				 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
			 __.'              ~.   .~              `.__
		   .'//   A    C    之   \./  之    真    理  \`.
		 .'//                     |                     \`.
	   .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \`.
	 .'//.-"                 `-.  |  .-'                 "-.\`.
   .'//______.============-..   \ | /   ..-============.______\`.
 .'______________________________\|/______________________________`.
*/
```

---

## 作者：linjinkun (赞：0)

> 大概评级：橙。

送分题。

题意就是让你统计有多少条边是重边或自环。

设 $u_i$ 表示第 $i$ 条边的左端点，$v_i$ 表示第 $i$ 条边的右端点。

那么如果 $u_i = v_i$，那么第 $i$ 条边为自环，然后我们只需要使用 `map` 记录每一条边是否出现就行了，然后每读入一条边，如果当前边已经出现，那么就说明出现了重边，注意是无向图，所以读入 $u_i,v_i$ 时，要两种方向都标记。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int>mp;
signed main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	int num = 0;
	for(int i = 1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		if(x == y)
		{
			num++;
			continue;
		}
		if(mp.find({x,y})!=mp.end())
		{
			num++;
			continue;
		}
		mp[{x,y}] = 1;
		mp[{y,x}] = 1;
	}
	printf("%d",num);
	return 0;
}
```

---

## 作者：Magus (赞：0)

这怎么还是官解？

### $F_1$
自环只需在读入边的过程中判断 $u_i$ 是否等于 $v_i$ 即可。

如何判断重边呢？最简单的思路就是建图。

然后我们很轻松的就得到了一发法师。

我们把不牛的数组换成伟大的 `map`，这就过了，复杂度 $\Theta(N \log N)$。

[AC 记录。](https://atcoder.jp/contests/abc393/submissions/62779870)


```cpp
#include<bits/stdc++.h>
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
const int maxn=1e6+10,maxm=1e3+10,mod=998244353;
int n,m,x,y,u,v,arr[maxn],fa[maxn];
map<int,map<int,int>>e;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v;
		if(u==v or e[u][v]==1 or e[v][u]==1)
		{
			x++;
		}
		else
		{
			e[u][v]=1;
			e[v][u]=1;
		}
	}
	cout<<x;
	return 0;
}
```

### $F_2$

建一个结构体用来存边。

存完之后将边从小到大排序，重边肯定是都在一起的，自环判 $e_i.x$ 是否等于 $e_i.y$ 即可。

---

## 作者：qjh_2014 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc393_c)

## 思路
我们用一个集合，判断自环可以跳过，重边可以用 ```set``` 去重边，最后保留在集合里的 $k$ 条边，则答案是 $m$ 减去 $k$。

## 代码
强调：
```
set<pair<int ,int> >;//注意这里要空格，不然会报错
```

完整代码
```
#include <bits/stdc++.h>
using namespace std;
void uprint(int x){//输出无符号类型数
  	if(x>9){
    	uprint(x/10);
  	}
  	putchar(x%10^48);
  	return ;
}
void print(int x){//有符号类型，可直接调用这个
  	if(x<0){
    	putchar('-');
    	x=-x;
	}
	uprint(x);
	return ;
}
int read() {//快读
	int x=0, w=1;
	char ch=0;
	while (ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*w;
}
int main(){
    int n=read(),m=read(),ans=0;//定义加输入
    set<pair<int,int> > s;//定义主角 set
	for(int i=1; i<=m; i++){
		int u=read(),v=read();
		if(u==v){
          continue;
        }//判断自环
		if(u>v){
          swap(u,v);
        }
		s.insert({u,v});//插入
	}
	cout<<m-s.size()<<"\n";//at的特性
    return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

为了使图简单，即消除自环和多边，我们需要删除以下两种边：

- 如果存在边 $(u,v)$ 与 $u=v$ 相关：它是一个自环，因此必须始终删除。
- 如果有多个边 $(u,v)$ 与 $u\not=v$ 相关联：它们是多边，所以除了一个之外都必须删除。

因此，我们可以将所有自环计入答案，对于其他边，如果边 $(u,v)$ 出现 $k$ 次，则将 $(k−1)$ 加到答案上。

对于实现，只需计算每种边类型的出现次数，对于这我们可以使用类似于 C++ 中的“字典”数据结构 `std::map` 。其复杂度为 $O(N\log N)$ ，足够快。注意，当 $u\not=v$ 时，必须识别 $(u,v)$ 和 $(v,u)$。

代码：

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int N, M;
  cin >> N >> M;
  int ans = 0;
  map<pair<int, int>, int> m;
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    if (u == v) {
      ans++;
      continue;
    }
    if (u > v) swap(u, v);
    m[{u, v}]++;
  }
  for (auto& [edge, k] : m) ans += k - 1;
  cout << ans << "\n";
}
```

---

## 作者：Alexoip (赞：0)

题意：问最少删除多少边，使得所给的图为简单图。

简单图：不包含重边和自环的图。

做法：可以直接在输入时判断，自环的情况即为 $u=v$ 时；重边的情况即为边 $(u,v)$ 之前出现过，其中规定 $u<v$。发现 $1 \leq N \leq 2 × 10^5$，不可开二维数组判断是否出现过。可以开一个二维 map，用 contains 函数判断以 $u$ 为端点的边中，是否存在另一端点为 $v$ 的情况。

代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using u128 = unsigned __int128;

constexpr int N = 2e5 + 10;

map<int, int> vis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	int ans = 0;
	while (m--) {
		int u, v;
		cin >> u >> v;
		if (u > v) { // 注意我们规定了 u < v
			swap(u, v);
		}
		if (u == v || vis[u].contains(v)) {
			ans++;
		}
		vis[u][v] = 1;
	}
	cout << ans << "\n";
    return 0;
}
```

---

## 作者：lilong (赞：0)

直接按照题意模拟即可。如果输入的边已经存在或构成自环，则直接删去即可。注意需保证 $u,v$ 的大小关系不变，判断边是否存在可使用 map。


```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

map<int,map<int,int> > pd;

int main()
{
    int n,m,u,v,ans = 0;
    cin >> n >> m;
    while( m -- )
    {
        cin >> u >> v;
        if( u > v ) swap( u , v );
        if( pd[u][v] || u == v ) ans ++;
        else pd[u][v] = 1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC393C] Make it Simple

需要做的事情是给一个无向图，让它不重边。

那只需要排除自环，排除重边就可以了。

我们可以统计不重复的边的数量。为了防止出现类似于 $(u,v)$ 和 $(v,u)$ 的重边，可以在前一个结点编号大于后一个结点编号的时候互换两个结点的编号，这样就可以避免这种情况了。然后将这些边当中不自环的边都扔到 set 里面得到去重后边的数目，然后总的边数减去去重后边的数目就是答案。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,u,v;
set< pair<ll,ll> > edges;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		if(u==v) continue;
		else if(u>v) swap(u,v);
		edges.insert({u,v});
	}
	cout<<m-edges.size()<<endl;
	return 0;
}
```

---

## 作者：yueyan_WZF (赞：0)

这道题其实就是让你判断一下自环和重边。

我们输入时就开始判断：

- 自环：
  
   自环很好判断，就是判断一下读入的起点与终点是否一样，如果一样就可以删掉。

- 重边：

  重边就是判断一下之前这两个端点有没有边，如果没有就打上标记，否则就可以删去。但我们发现： $n\le 2 \times 10^5$ 如果开个二维数组就会爆掉，于是我们可以使用 map。


## code


```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp[200003];
int main(){
	int n,ans=0,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		if(mp[a].count(b)||mp[b].count(a)||a==b){
			ans++; 
		}
		else{
			mp[a][b]=1;
			mp[b][a]=1; //打标记
		}
	}
	cout<<ans;
}
```

---

## 作者：HuangBarry (赞：0)

淼。

给你一个无向图，问你有多少个自环和重边。

自环判断：
- 如果 $u=v$ 即自环。

重边判断：
- 用 `set` 把每条边存进去，如果 `set.size()` 的值每次存后没变，即重边。

- 注意：存边别把自环的边存进去。

代码：


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define stl_priority_queue std::priority_queue
#define pbds_priority_queue __gnu_pbds::priority_queue
#define to_string std::to_string
#define endl '\n'
#define Endl cout<<endl
#define Made return
#define by 0
#define Barry +0
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
int n,m,ans=0;
set<pii>s;
int main(){
    //Freopen("filename");
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        if(u==v){
            ans++;
            continue;
        }
        int x=s.size();
        s.insert(pii(u,v));
        s.insert(pii(v,u));
        ans+=(x==s.size());
    }
    cout<<ans<<endl;
    Made by Barry;
}

```

---

## 作者：Cosine_Func (赞：0)

题意：给定一张无向图，求最少删除多少条边后图中不包括重边和自环。

从定义的角度来考虑这道题目。假设从 $u$ 到 $v$ 的无向边用无序数对 $\left(u,v\right)$ 表示，则自环的定义为 $u=v$，重边的定义为存在 $\left(a,b\right)$ 满足 $a=u \text{ and }b=v$ 或 $a=v \text{ and }b=u$。

显然，直接统计重边和自环的数量即可。可以使用 `set` 维护，时间复杂度 $O(M\log M)$。

[参考代码](https://atcoder.jp/contests/abc393/submissions/62765248)

---

## 作者：lfxxx_ (赞：0)

对于边 $i$，我们这里强制让 $u_i \le v_i$ 成立，如果他是一条自环边，则一定有 $u_i = v_i$，否则我们就在一个 map 中进行查重，如果有和他相同的则这条边为重边，否则将这条边插入 map。

时间复杂度 $O(M \log M)$。

```cpp
//zhouyoyo巨佬保佑我AK
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int>mp;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    int ans=0;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        cin>>x>>y;
        if(x<y)swap(x,y);
        if(x==y)++ans;
        else
        {
            if(mp[make_pair(x,y)])++ans;
            else mp[make_pair(x,y)]=1;
        }
    }
    cout<<ans;
}
```

---

## 作者：FXLIR (赞：0)

### 思路

发现简单图的定义是无重边、无自环的图。

所以在读入所有边的时候记录一下自环边的数量，再开一个 map 用于判重边，答案就是自环边的数量与重边数量之和。

### 代码
```
#include<map>
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+5,INF=1e9;
int n,m,u,v,ans;
map<pair<int,int>,bool > mp;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		ans+=(u==v||mp.count({min(u,v),max(u,v)})),mp[{min(u,v),max(u,v)}]=1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ybclch2026 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc393_c)
### 题意
对于一个图，删去若干边，使得这个图不包含自环或多条边，答案是删除的最小边数。

### 思路
因为这个图不包含自环或多条边，所以在输入时判一下，就可以了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
map<int,int>h[200005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        if(u==v){ans++;continue;}
        if(h[min(u,v)][max(u,v)])ans++;
        h[min(u,v)][max(u,v)]=1;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：jinfanhao (赞：0)

这道题的要求是删掉最少的边用来简化图形。
要求就是没有重边，没有自环。\
那怎么知道那个是重边呢？每回用一个超级桶存下来，后面就可以直接判了。\
那怎么知道那个是自环呢？每回判边的两头是否一样就可以了。\
注意一个边只要删一次不然有些有是重边又是自环就会删两次。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,u,v,sum;
map<pair<int,int>,bool> mp;
signed main(){
    scanf("%lld%lld",&n,&m);
    while(m--){
        scanf("%lld%lld",&u,&v);
        if(u>v)swap(u,v);
        if(u==v){
        	++sum;
        	continue;
		}
		if(mp[{u,v}])++sum;
        mp[{u,v}]=true;
    }
    printf("%lld",sum);
    return 0;
}
```

---

