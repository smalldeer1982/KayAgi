# Social Network

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/bd782248ee184d971343d4489aa3f05723b81f9f.png)William arrived at a conference dedicated to cryptocurrencies. Networking, meeting new people, and using friends' connections are essential to stay up to date with the latest news from the world of cryptocurrencies.

The conference has $ n $ participants, who are initially unfamiliar with each other. William can introduce any two people, $ a $ and $ b $ , who were not familiar before, to each other.

William has $ d $ conditions, $ i $ 'th of which requires person $ x_i $ to have a connection to person $ y_i $ . Formally, two people $ x $ and $ y $ have a connection if there is such a chain $ p_1=x, p_2, p_3, \dots, p_k=y $ for which for all $ i $ from $ 1 $ to $ k - 1 $ it's true that two people with numbers $ p_i $ and $ p_{i + 1} $ know each other.

For every $ i $ ( $ 1 \le i \le d $ ) William wants you to calculate the maximal number of acquaintances one person can have, assuming that William satisfied all conditions from $ 1 $ and up to and including $ i $ and performed exactly $ i $ introductions. The conditions are being checked after William performed $ i $ introductions. The answer for each $ i $ must be calculated independently. It means that when you compute an answer for $ i $ , you should assume that no two people have been introduced to each other yet.

## 说明/提示

The explanation for the first test case:

In this explanation, the circles and the numbers in them denote a person with the corresponding number. The line denotes that William introduced two connected people. The person marked with red has the most acquaintances. These are not the only correct ways to introduce people.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/a4c52dc40d0c621cc37cb8aa412551d28349b4ab.png)

## 样例 #1

### 输入

```
7 6
1 2
3 4
2 4
7 6
6 5
1 7```

### 输出

```
1
1
3
3
3
6```

## 样例 #2

### 输入

```
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4```

### 输出

```
1
2
3
4
5
5
6
8```

# 题解

## 作者：智子 (赞：6)

## 题意

给定 $n$ 个点，$d$ 条规定，每条规定有两个参数 $x_i,y_i$，表示 $x_i$ 和 $y_i$ 必须连通。

$\forall i\in[1,d]$，求在满足 $[1,i]$ 的规定的前提下恰好连 $i$ 条边的无向图中，度数最大的点的度数。

## 思路

首先吐槽翻译，一句话的差别让答案完全不一样了，一个点的最大度数是联通块的大小 -1……

如果按照题目中的要求依次连边，你会发现有一些边是重复的，即 $x_i$ 和 $y_i$ 已经连通了，这时这条边的“名额”就可以用来连接两个联通块，将其变成同一个联通块。（Warning：不是让你真的把他们连起来！）

形式化地说，如果在连接第 $i$ 条边时有 $k$ 条边重复了，那么答案就是所有联通块中最大的 $k + 1$ 个联通块的大小的总和 -1。因为 $n \leq 10^3$，所以直接枚举每个联通块即可，至于重复边的数目可以在连边时维护。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<functional>
using namespace std;

const int MAXN = 1000 + 5;

int f[MAXN], sum[MAXN];
int n, d, cnt = 0;

int find(int k) {
    return k == f[k] ? k : f[k] = find(f[k]);
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    if(x == y) {
        cnt++;
        return;
    }
    f[x] = y;
    sum[y] += sum[x];
}

int main() {
    scanf("%d%d", &n, &d);
    for(int i = 1; i <= n; i++) {
        f[i] = i;
        sum[i] = 1;
    }
    for(int i = 1; i <= d; i++) {
        vector<int> v;
        int x, y;

        scanf("%d%d", &x, &y);
        merge(x, y);
        for(int j = 1; j <= n; j++) {
            if(j == find(j)) {
                v.push_back(sum[j]);
            }
        }
        sort(v.begin(), v.end(), greater<int>());
        int ans = 0;
        for(int j = 0; j < v.size() && j <= cnt; j++) {
            ans += v[j];
        }
        ans--;
        printf("%d\n", ans);
    }

    return 0;
}

```

---

## 作者：Fislett (赞：2)

# 题意：
题目翻译是有问题的，题目的真正意思其实是 $∀i∈[1,d]$，求在满足 $[1,i]$ 的规定的前提下恰好连 $i$ 条边的无向图中度数最大联通块的大小减 $1$。
# 思路
考虑贪心策略。如果此时读入的 $x_i,y_i$ 已经是连通的了，那么如果我们用这条边连接 $x_i,y_i$ 纯属浪费，倒不如用这条边将最大的那两个连通块连接起来。

所以做法如下：

我们用 $cnt$ 记录目前有多少条这样的边，由于 $cnt$ 条边连接 $cnt + 1$ 个连通块，所以我们只需要将最大的 $cnt + 1$ 个联通块中点的数量累加再减 $1$ 就是答案了。

至于怎么判连通性，用并查集就能愉快的解决了呀！

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, fa[1001], size[1001], cnt;
int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if(fx == fy)
	{
		cnt ++;
		return ;
	}
	fa[fx] = fy;
	size[fy] += size[fx];
	return ;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++) fa[i] = i, size[i] = 1;
	for (int i = 1; i <= m; i ++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		merge(x, y);
		int ans = 0;
		vector<int> g;
		for (int i = 1; i <= n; i ++) if (find(i) == i) g.push_back(size[i]);
		sort(g.begin(), g.end(), greater<int>());
		for (int i = 0; i <= cnt; i ++) ans += g[i];
		printf("%d\n", ans - 1);
	}
}
```


---

## 作者：大宝和小宝 (赞：2)

我们用 $cnt$ 记录目前有多少条这样的边，由于 $cnt$ 条边连接 $cnt+1$ 个连通块，所以我们只需要将最大的 $cnt+1$ 个联通块中点的数量累加再减 $1$ 就是答案了。

至于怎么判连通性，用并查集就能愉快的解决了呀！

------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt;
int father[5010],high[5051];
void init(int n){//初始化函数，把每个点的根存为他自己，树的高度为1 
	for(int i=1;i<=n;i++){
		father[i]=i;
		high[i]=1; 
	}
}
int find(int x){//找跟函数，同时进行路经压缩 
	if(father[x]==x) return x;
	else{
		return father[x]=find(father[x]);
	} 
}
void unite(int x,int y){//合并函数，把x和y所在的树二合一 {
	x=find(x);
	y=find(y);
	if(x==y){
        cnt++;
        return;
    }
	father[x]=y;
	high[y]+=high[x];
    return ;
}
int same(int x,int y){//查询函数，判断x和y是否在一颗树上
	if(find(x)==find(y)){
		return 1;
	} 
	return 0;
}
int main(){
	cin>>n>>m;
	init(n);
	for(int i=1;i<=m;i++){
		int x, y;
		cin>>x>>y;
		unite(x, y);
		int ans=0;
		vector<int> g;
		for(int i=1;i<=n;i++){
            if(find(i)==i){
                g.push_back(high[i]);
            }
        }
		sort(g.begin(),g.end(),greater<int>());
		for (int i=0; i<=cnt;i++){
            ans+=g[i];
        }
		cout<<ans-1<<endl;
	}
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定 $n$ 个点和 $d$ 条规定，每条规定给定两个参数 $x_i,y_i$ 表示 $x_i,y_i$ 必须连通。

$\forall i \in[1, d]$，求在满足 $[1,i]$ 的规定的前提下恰好连 $i$ 条边的无向图最大连通块的大小最大可能是多少。

$2 \leq n \leq 10^{3}, 1 \leq d \leq n-1,1 \leq x_{i}, y_{i} \leq n, x_{i} \neq y_{i}$。

#### 题目分析


------------
然而，题目翻译是存在瑕疵的。

很明显是一道应用并查集求解连通块大小及数量的问题，当我信心满满的交上去的时候却发现死在了第一个点。

翻看题解区的大佬解答才发现原来题目中要求的并非最大连通块的大小，而是度数最大的点的边数。

度数最大的点的边数其实是最大连通块大小减去 $1$，所以只需在原先程序的基础上减去 $1$ 就能轻松通过本题。

#### 解题思路


------------

- 遍历题目给出的连通的条件，如果 $x_i,y_i$ 在之前还未连通那么就将两点连通，否则如果 $x_i,y_i$ 此前已经连通则不需要此时这一连通条件将这两个点连通，所以此时 $x_i,y_i$ 之间的这条边就是一条空闲的边，用 ```cnt``` 表示空闲的边的数量。
- 每次输出的时候，只需要找出前 ```cnt + 1``` 大的连通块，用 ```cnt``` 条空闲的边将他们连通起来，答案即为这些连通块的大小 $-1$。

#### 代码实现


------------
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;
const int N = 10010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int fa[N],sum[N];
int n,d,cnt = 0;
int find(int x){
	if(fa[x] == x){
		return x;
	}
	else return fa[x] = find(fa[x]);
}
void merge(int x,int y){
	x = find(x) , y = find(y);
	if(x == y){
		cnt++;
		return;
	}
	fa[x] = y;
	sum[y] += sum[x];
}
int main(){
	n = read() , d = read();
	for(int i=1;i<=n;i++){
		fa[i] = i;
		sum[i] = 1;
	} 
	for(int i=1;i<=d;i++){
		vector<int> v;
		int x = read(),y = read();
		merge(x,y);
		for(int j=1;j<=n;j++){
			if(j == find(j)){
				v.push_back(sum[j]);
			}
		}
		sort(v.begin(),v.end(),greater<int>());
		int ans = 0;
		for(int j=0;j<v.size() && j <= cnt;j++){
			ans += v[j];
		}
		printf("%lld\n",ans-1);
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

本题的难点其实在于读懂题意。

考虑每一个要求联通的块，若设这个块的大小为 $n$，显然每一块内相连接需要至少 $n-1$ 条边，想要要让某一个点连接的边最大直接将所有的其他点链接上去就行了。

此时如果有一个询问要求了两个已经链接在了一起的点，就意味着有了一条空闲的边，可以用这一条边来连接两个联通块。

到这里思路就很清晰了，用并查集维护当前每一个联通块的大小，并算出当前空闲的边的数量，然后每一次询问直接找出最大的边的数量个联通块，统计总合即可。

我采用的实现方式是维护每一个数量有多少个，每一次从大往小取最大的几个就行了。

复杂度 $O(n^2)$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,m,x,y,fa[10005],fx,fy,cnt[10005],t[10005],ans,CNT;
int find(int now){
	if(fa[now]==now)return now;
	return fa[now]=find(fa[now]);
}
int main(){
	scanf("%d%d",&n,&m);
	CNT=1;
	for(int i=1;i<=n;i++)
	fa[i]=i,cnt[i]=1;
	t[1]=n;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		fx=find(x);fy=find(y);
		if(fx!=fy){
			t[cnt[fx]]--;
			t[cnt[fy]]--;
			cnt[fx]+=cnt[fy];
			t[cnt[fx]]++;
			fa[fy]=fx;
		}
		else CNT++;
		int ans=0,ccnt=CNT;
		for(int j=n;j>=1;j--){
			if(t[j]==0)continue;
			if(t[j]<=ccnt)ans+=t[j]*j,ccnt-=t[j];
			else ans+=j*ccnt,ccnt=0;
			if(ccnt==0)break;
		}
		printf("%d\n",ans-1);
	}
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：1)

### Analysis

以下连通块的大小均指连通块中点的个数。

每次求一个点的最大可能度数等价于**求最大连通块的最大可能点数（再减 $1$）**。

由于 $n$ 个点的连通无环图有且仅有 $n-1$ 条边，所以对于每一个给出条件的前缀，不用考虑加边的顺序。

所以思路如下：

顺序遍历给出的条件（$x$ 和 $y$ 必须连通），如果 $x$ 和 $y$ 已经连通，则将 $cnt$ 加 $1$，代表现在多出一条空闲的边，否则只能将 $x$ 和 $y$ 连边。

对于每次答案的计算，遍历每一个连通块，取前 $cnt+1$ 大的，用那 $cnt$ 条空闲的边将这些连通块连通，答案为这整个连通块的大小 $-1$。

### Detail

取前 $cnt+1$ 大的连通块时用堆维护。

计算答案时不必将连通块真的连起来。

### Code

复杂度 $O(nm\log n)$，实际上跑不满。

```cpp
#define N 1010
int n,m,f[N],sz[N],cnt=0;
bool vis[N];
priority_queue<int,vector<int>,greater<int> > q;
inline int gf(int x){
	return f[x]==x?x:f[x]=gf(f[x]);
}
signed main(){
	IOS;
	cin>>n>>m;
	For(i,1,n) f[i]=i;
	For(i,1,n) sz[i]=1;
	int x,y;
	For(i,1,m){
		cin>>x>>y;
		if(gf(x)!=gf(y)){
			sz[gf(y)]+=sz[gf(x)];
			f[gf(x)]=gf(y);
		}else{
			cnt++;
		}
		For(j,1,n) vis[j]=0;
		For(j,1,n){
			if(vis[gf(j)]) continue;
			vis[gf(j)]=1;
			q.push(sz[gf(j)]);
			if(q.size()>cnt+1) q.pop();
		}
		int ans=0;
		while(!q.empty()){
			ans+=q.top();
			q.pop();
		}
		cout<<ans-1<<endl;
	}
    return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1609D](https://www.luogu.com.cn/problem/CF1609D)

# 思路

我们考虑一个联通块的最大度数，设这个联通块有 $cnt$ 条边，$x$ 条重边。

如果 $x=0$，那么最大度数就是 $cnt-1$。

如果 $x\neq0$，因为连两个点需要 $1$ 条边，所以最大度数是最大的 $x$ 个联通块度数之和减 $1$。

如果需要判连通性，可以使用并查集解决。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,cnt;
int fa[5005],h[5005];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		h[i]=1;
	}
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int i,int j){
	int x=find(i),y=find(j);
	if(x==y){
		cnt++;
		return;
	}
	fa[x]=y;
	h[y]+=h[x];
	return;
}
signed main(){
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		merge(u,v);
		int ans=0;
		vector<int> g;
		for(int j=1;j<=n;j++){
			if(j==find(j)){
				g.push_back(h[j]);
			}
		}
		sort(g.begin(),g.end(),greater<int>());
		for(int j=0;j<=cnt;j++){
			ans+=g[j];
		}
		cout<<ans-1<<endl;
	}
    return 0;
}

```

[提交记录](https://www.luogu.com.cn/record/145941777)

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1609D)
题目给定 $n$ 个点和 $d$ 个规定，每条规定有两个参数 $x_i$ 和 $y_i$，表示 $x_i$ 和 $y_i$ 必须联通。$\forall~i\in\left[1,d\right]$，求在满足 $\left[1,i\right]$ 的规定时恰好连 $i$ 条边的无向图的度数最大的点的度数最大为多少。

显然，当没有重边时，度数最大点的度数为最大联通块的大小 $-1$。

而当有重边时，由于使两个点联通至多需要 $1$ 条边，所以一条重边可以使得最大的两个联通块联通。所以，当有 $x$ 条重边时，度数最大的点的度数最大为最大的 $x$ 个联通块大小之和 $-1$。

使用并查集维护每个联通块以及其大小即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,u,v,fa[1005],sum[1005],ans,cnt;
inline void init(int n){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sum[i]=1;//联通块大小初始化为1
    }
}
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y){
        cnt++;
        return;
    }
    fa[x]=y;
    sum[y]+=sum[x];//维护联通块大小
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>d;
    init(n);
    for(int i=1;i<=d;i++){
        ans=0;
        vector<int>ve;
        cin>>u>>v;
        merge(u,v);
        for(int j=1;j<=n;j++)
            if(j==find(j))
                ve.push_back(sum[j]);
        sort(ve.begin(),ve.end(),greater<int>());//由大到小排序
        for(int j=0;j<ve.size() && j<=cnt;j++)ans+=ve[j];
        cout<<ans-1<<'\n';
    }
    return 0;
}
```

---

## 作者：Engulf (赞：0)

设当前我们要让 $x$ 与 $y$ 联通。

若 $x$ 与 $y$ 不在一个连通块中，我们要把他们连起来。为了让入度最大，显然得把所有点连向一个固定的点，令这个连通块大小为 $k$，则这个连通块最大的入读为 $k-1$。

若 $x$ 与 $y$ 已经在一个连通块中，我们可以随心所欲地把任意两个连通块合并，用一个变量 $t$ 维护这样的边数。

每次查询，我们显然是取前 $t+1$ 大的连通块，设总共有 $k$ 个点，答案即为 $k-1$。

实现上，可以使用并查集和堆维护。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e3 + 5;

int n, m;

int fa[N], siz[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        siz[y] += siz[x];
        fa[x] = y;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    multiset<int, greater<int>> st;
    for (int i = 1; i <= n; i++) {
        fa[i] = i, siz[i] = 1;
        st.insert(siz[i]);
    }
    int free = 0;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        x = find(x), y = find(y);
        if (x == y) {
            free++;
        } else {
            st.erase(st.lower_bound(siz[x]));
            st.erase(st.lower_bound(siz[y]));
            merge(x, y);
            st.insert(siz[y]);
        }
        int ans = 0, cnt = 0;
        for (auto j: st) {
            ans += j;
            cnt++;
            if (free + 1 == cnt) break;
        }
        cout << ans - 1 << "\n";
    }
    return 0;
}
```

---

## 作者：蒟蒻炒扇贝 (赞：0)

本题翻译有误，应该是求最大的连通块大小减一。

考虑一个贪心思路，如果有接下来的一个条件 $(x_i,y_i)$，其中 $x_i$ 和 $y_i$ 已经联通，那么我们与其连接 $x_i$ 和 $y_i$，不如去找目前所有连通块中最大的几块来连。我们称这一种约束条件是没有意义的。设这种无意义的条件数量为 $cnt$，那么上文中“最大的几块”其实就是最大的 $cnt$ 个连通块，算上自己本身，一共 $cnt+1$ 个连通块，由于 $n$ 和 $d$ 较小，我们可以把目前所有连通块的大小记录到一个数组中，然后从大到小排个序，答案就是这个数组前 $cnt+1$ 个元素之和再减一。

连通块用并查集维护即可。

时间复杂度为 $\mathop{O(nd\log n)}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[1005],siz[1005];
int findf(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=findf(fa[x]);
}
int uni(int x,int y)
{
	int xx=findf(x),yy=findf(y);
	if(xx==yy)return false;
	fa[xx]=yy;
	siz[yy]+=siz[xx];
	return true;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	int cnt=0;
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		if(!uni(x,y))cnt++;
		int ans=0;
		vector<int>v;
		for(int i=1;i<=n;i++)
			if(findf(i)==i)v.push_back(siz[i]);
		sort(v.begin(),v.end(),greater<int>());
		for(int i=0;i<=cnt&&i<v.size();i++)ans+=v[i];
		ans--;
		cout<<ans<<endl;
	}
}
```


---

## 作者：enucai (赞：0)

~~**前言：又是一道比C还水的CF题**~~

## 题意简述

有 $d$ 个约束条件，每个约束条件都表示为 $(u,v)$ 的形式，表示 $u$ 号节点与 $v$ 号节点需要在同一个连通块中。

$\forall i\in [1,d]$ ，求在满足 $[1,i]$ 的规定的前提下恰好连 $i$ 条边的无向图最大连通块的大小最大可能是多少。

## 蒟蒻思路

这题思路很好想，~~可能是蒟蒻这场比赛切地最快的一题了~~。

首先肯定是并查集来维护关系，还要记录一个 $R$ 表示满足前面所有条件的情况下，剩下最多还能连多少条边。

当我们要认定 $u$ 与 $v$ 在同一个连通块中时，可以先判断一下他们是否已经在连通块中了。

- 如果在同一个连通块中，那么直接将 $R$ 增加 $1$。

- 如果不是在同一个连通块中，那么将连通块合并。注意合并的时候还要记录一下每个连通块的 $size$：如果这个点是一个连通块的根，那么它的 $size$ 就是连通块大小；否则 $size$ 就是 $0$。

每次操作后，都将 $size$ 数组从大到小拍一下序，求出前 $R+1$（$R$ 条边可以构成 $R+1$ 个连通块）大的值的和减一（自己认识自己不算）即可。

## 蒟蒻代码

**Talk is cheap, show me the code!**

```cpp
int n,d;
int x[1010],y[1010];
int fa[1010],sz[1010];
int rk[1010];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy){
		fa[fy]=fx;
		sz[fx]+=sz[fy];
		sz[fy]=0;
		return true;
	}
	return false;
}
signed main(){
	n=read(),d=read();
	For(i,1,n) fa[i]=i,sz[i]=1;
	For(i,1,d) x[i]=read(),y[i]=read();
	int rest=0;
	For(i,1,d){
		if(!merge(x[i],y[i])) rest++;
		For(i,1,n) rk[i]=sz[i];
		sort(rk+1,rk+n+1);
		int kk=rest+1,pos=n,ans=0;
		while(kk--){
			ans+=rk[pos--];
		}
		cout<<ans-1<<endl;
	}
}
```

---

