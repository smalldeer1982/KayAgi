# [ABC157D] Friend Suggestions

## 题目描述

### 题目大意

某平台上有 $N$ 名用户，其中，有 $M$ 对用户是互相关注的，有 $K$ 对用户是互相拉黑的。

当用户 $i$ 和用户 $j$ 满足以下条件时，用户 $j$ 就是用户 $i$ 的“推荐用户”：

+ 用户 $i$ 可以与 用户 $j$ 通过若干对用户的互相关注关系连接起来。（比如用户 1 与用户 2，用户 2 与用户 3 都互相关注，则用户 1 和 用户 3 就可以通过他们的关系连接起来）
+ 用户 $i$ 与用户 $j$ 没有互相关注或互相拉黑。

求每位用户的“推荐用户”的数量。

数据保证不会存在一对用户既互相关注又互相拉黑。

## 说明/提示

$2 \le N \le 10^5, 0 \le M,K \le 10^5$。

翻译 by @CarroT1212

## 样例 #1

### 输入

```
4 4 1
2 1
1 3
3 2
3 4
4 1```

### 输出

```
0 1 0 1```

## 样例 #2

### 输入

```
5 10 0
1 2
1 3
1 4
1 5
3 2
2 4
2 5
4 3
5 3
4 5```

### 输出

```
0 0 0 0 0```

## 样例 #3

### 输入

```
10 9 3
10 1
6 7
8 2
2 5
8 4
7 3
10 9
6 4
5 8
2 6
7 5
3 1```

### 输出

```
1 3 5 4 3 3 3 3 1 0```

# 题解

## 作者：Crasole (赞：3)

## 题意

在某平台上有 $n$ 个用户，其中，有 $m$ 名用户是互关的，有 $k$ 名用户是相互拉黑的。

我们定义用户 $i$ 是用户 $j$ 的推荐用户：

- 用户 $i$ 与用户 $j$ 是通过若干的用户之间的关注关系连接起来的，不能是直接互关。

- 用户 $i$ 与用户 $j$ 并不是互相拉黑的。

现在给你 $m$ 个互关关系和 $k$ 互相拉黑的关系，请输出每个人的推荐用户的个数。

## 思路

这道题目非常明显是使用并查集的。

我们只需统计与用户 $i$ 是共同祖先的用户的个数，再减去与用户 $i$ 是共同祖先的且是被用户 $i$ 关注过或拉黑过的人的个数，就是用户 $i$ 的推荐用户的个数。

### 并查集基本操作

-----

并查集实现为一个森林，有如下几种基本操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/vka7bxj4.png)

注：并查集。

- 初始化：我们在开始先假设 $n$ 个家族每个家族的祖先都是自己。

代码：

```cpp
for(int i=1;i<=n;i++)
		f[i]=i;//假设每个个家族每个家族的祖先都是自己
```

- 查询祖先：查询祖先，我们需要一层层递归上去。但是有可能多次查询同一个点，每一次都重新递归没有必要，所以可以加路径压缩。每一次找到祖先了，就直接把自己的父亲设为祖先。

![](https://cdn.luogu.com.cn/upload/image_hosting/ngzepbkq.png)

注：绿色为递归路线。

![](https://cdn.luogu.com.cn/upload/image_hosting/vop9pnlp.png)

注：路径压缩。

代码：

```cpp
int find(int q){
	if(f[q]==q) return q;//如果这个家族的祖先是自己，那么返回自己
	return f[q]=find(f[q]);//找到自己的祖先
}
```

- 合并：让其中一个家族的祖先的祖先指向另外一个家族的祖先。

![](https://cdn.luogu.com.cn/upload/image_hosting/yplcjw0s.png)

注：合并。

代码：

```cpp
f[find(x)]=find(y);
```

-----

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[100010],fore[100010],lyg[100010];//f[i]代表i的祖先，fore[i]代表以i为祖先的家族的人数，lyg[i]代表i关注的与拉黑的人数
int n,m,k;
int find(int q){
	if(f[q]==q) return q;
	return f[q]=find(f[q]);
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		f[i]=i;
	int x,y;
	while(m--){
		cin>>x>>y;
		f[find(x)]=find(y);
		lyg[x]++,lyg[y]++;//双方的关注数都加1
	}
	for(int i=1;i<=n;i++)
		fore[find(i)]++;
	while(k--){
		cin>>x>>y;
		if(find(x)==find(y)) ++lyg[x],++lyg[y];//如果x与y是同一个家族，那么x与y的拉黑数加1
	}
	for(int i=1;i<=n;i++)
		cout<<fore[find(i)]-lyg[i]-1<<' ';//注意要减1，因为自己也被算进去了
	return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

### 翻译

（翻译已经交上去审核了，晚点应该就会出现在题面里，先扔这儿吧）

（与原题面略有出入，但是不影响理解题意）

某平台上有 $N$ 名用户，其中，有 $M$ 对用户是互相关注的，有 $K$ 对用户是互相拉黑的。

当用户 $i$ 和用户 $j$ 满足以下条件时，用户 $j$ 就是用户 $i$ 的“推荐用户”：

+ 用户 $i$ 可以与 用户 $j$ 通过若干对用户的互相关注关系连接起来。（比如用户 1 与用户 2，用户 2 与用户 3 都互相关注，则用户 1 和 用户 3 就可以通过他们的关系连接起来）
+ 用户 $i$ 与用户 $j$ 没有互相关注或互相拉黑。

求每位用户的“推荐用户”的数量。

数据保证不会存在一对用户既互相关注又互相拉黑。

------------

下面所有的内容都用的是上面的翻译。

楼上有人用并查集，我并查集太菜，就打个 bfs 吧。

很容易想到把每个用户都看做是一个个点，然后有互相关注关系的连边，用搜索扫一遍看看有哪些点是联通的，记录不考虑第二个条件时每个用户的“推荐用户”数量，然后扫一遍互相关注和互相拉黑的人，如果他们是联通的就把他们的“推荐用户”数量都减一，因为这时他们就不满足第二个条件了。最后输出即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rnt register long long
using namespace std;
const ll N=1e5+7;
ll n,a,b,x[N][2],y[N][2],f[N],g[N],gid; //我们将联通的用户分别分在不同的组里面，g[] 就是在搜索时用于记录这个点被分在了第几组。
vector <ll> v[N];
void bfs(ll x) {
	vector <ll> vis;
	queue <ll> q;
	q.push(x);
	while (!q.empty()) {
		ll r1=q.front();
		q.pop();
		if (g[r1]) continue;
		g[r1]=gid;
		vis.push_back(r1); //记录联通的用户数量
		for (auto i:v[r1]) if (!g[i]) q.push(i);
	}
	ll len=vis.size()-1; //“推荐用户”不包含自己，所以要 -1。
	for (auto i:vis) f[i]=len; //记录这时扫到的用户中的“推荐用户”数量
}
int main() {
	cin>>n>>a>>b;
	for (rnt i=1;i<=a;i++) {
		cin>>x[i][0]>>x[i][1];
		v[x[i][0]].push_back(x[i][1]); //连边
		v[x[i][1]].push_back(x[i][0]);
	}
	for (rnt i=1;i<=b;i++) cin>>y[i][0]>>y[i][1];
	for (rnt i=1;i<=n;i++) if (!g[i]) { //如果这个点还没有被搜过
		gid++; //把下面搜到的点分在一个新的组里
		bfs(i);
	}
	for (rnt i=1;i<=a;i++) if (g[x[i][0]]==g[x[i][1]]) f[x[i][0]]--,f[x[i][1]]--; //如果两个人在同一组且互相关注
	for (rnt i=1;i<=b;i++) if (g[y[i][0]]==g[y[i][1]]) f[y[i][0]]--,f[y[i][1]]--; //如果两个人在同一组且互相拉黑
	for (rnt i=1;i<=n;i++) cout<<f[i]<<" ";
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 思路：
很简单的一道并查集的题目，只需要找到每个人关系中，每个人都可以建立关系的那个人设为祖先，将这个人所能关注的人存在数组中。并查集数组中的每个元素出现了公共祖先，就给他的超级用户加一。当两个人互相关注或拉黑，最后算答案的时候就要减去这段关系，最后就可以得出我们的答案。

# code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int ls[N],d[N],fa[N];
int n,m,k;
int find(int x){
	if(x==ls[x]) return x;
	return ls[x]=find(ls[x]);
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) ls[i]=i;//初始化
	int u,v;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		ls[find(u)]=find(v);
		d[u]++,d[v]++;
	} 
	for(int i=1;i<=n;i++){
		fa[find(i)]++;
	}
	for(int i=1;i<=k;i++){
		cin>>u>>v;
		if(find(u)==find(v)) d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++){
		cout<<fa[find(i)]-d[i]+1<<endl;
	}
	return 0;
}
```

---

## 作者：Qiu_chen (赞：0)

## 题目翻译

某平台上有 $N$ 名用户，其中，有 $M$ 对用户是互相关注的，有 $K$ 对用户是互相拉黑的。

当用户 $i$ 和用户 $j$ 满足以下条件时，用户 $j$ 就是用户 $i$ 的“推荐用户”：

- 用户 $i$ 可以与 用户 $j$ 通过若干对用户的互相关注关系连接起来。（比如用户 $1$ 与用户 $2$，用户 $2$ 与用户 $3$ 都互相关注，则用户 $1$ 和 用户 $3$ 就可以通过他们的关系连接起来）

- 用户 $i$ 与用户 $j$ 没有互相关注或互相拉黑。

求每位用户的“推荐用户”的数量。

数据保证不会存在一对用户既互相关注又互相拉黑。

by @[CarroT1212](https://www.luogu.com.cn/user/319803)

## 思路

### 并查集

很明显是并查集和容斥原理。不会的可以先做做 [P1551](https://www.luogu.com.cn/problem/P1551)，这是一道并查集的模板。容斥原理应该不用多说。

我们统计每个人与多少个人有**直接**朋友关系，统计每个人与多少个人**互相拉黑**，再统计每个人与多少个人有**朋友关系**。那么根据容斥原理，

答案就是：

每个人与多少个人有朋友关系 $−$ 每个人与多少个人有直接朋友关系 $−$ 每个人与多少个人**不能**有朋友关系 $-1$，注意，这里减 $1$ 是因为要减去自己。

## 代码

一下为 C++ 参考代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int n,m,k,fa[maxn],d[maxn],num[maxn];
int find (int x){
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}//并查集函数
void join(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
	return ;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		join(x,y);
		d[x]++;
		d[y]++;
	}
	for(int i=1;i<=n;i++) num[find(i)]++;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(find(x)==find(y)){
			d[x]++;
			d[y]++;
		}
	}	
	for(int i=1;i<=n;i++){
		cout<<num[find(i)]-d[i]-1<<" ";
	}
	return 0;
} 
```




---

## 作者：Yashajin_Ai (赞：0)

### 思路
这道题一眼就想到了并查集，在我们处理互相关注时就是普通的并查集，因为求的是推荐人数，所以是有连接的人再减去不可能成为他的推荐用户的人再除去自己，有连接的人此处同样用并查集处理，全部人都在自己祖先这里增加，将自己给到这个连接范围里，让自己成为同样连接到自己祖先的人的推荐名单里，同时我们也需要另开一个数组，存储一下有多少个人不可能成为他的推荐用户。

![](https://cdn.luogu.com.cn/upload/image_hosting/cc1waurm.png)

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,k,u,v,ans;
int f[N],fa[N],d[N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) f[i]=i;
	while(m--){
		cin>>u>>v;
		f[find(u)]=find(v);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++) fa[find(i)]++;
	while(k--){
		cin>>u>>v;
		if(find(u)==find(v)) d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++) cout<<fa[find(i)]-d[i]-1<<" ";
	return 0;
}
```

---

## 作者：_YQY (赞：0)

### 题目大意
某平台上有 $N$ 名用户，其中，有 $M$ 对用户是互相关注的，有 $K$ 对用户是互相拉黑的。

当用户 $i$ 和用户 $j$ 满足以下条件时，用户 $j$ 就是用户 $i$ 的“推荐用户”：

+ 用户 $i$ 可以与 用户 $j$ 通过若干对用户的互相关注关系连接起来。（比如用户 1 与用户 2，用户 2 与用户 3 都互相关注，则用户 1 和 用户 3 就可以通过他们的关系连接起来）
+ 用户 $i$ 与用户 $j$ 没有互相关注或互相拉黑。

求每位用户的“推荐用户”的数量。

数据保证不会存在一对用户既互相关注又互相拉黑。

### 方法
很明显是使用并查集，再加一个容斥原理就行了

我们统计每个人与多少个人有直接朋友关系，统计每个人与多少个人不能有朋友关系，再统计每个人与多少个人有朋友关系。那么根据容斥原理，答案就是不考虑第二个条件时每个用户的“推荐用户”数量，然后扫一遍互相关注和互相拉黑的人，如果他们是联通的就把他们的“推荐用户”数量都减一

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+6;
int n,m,k,fa[maxn],d[maxn],num[maxn];
int find (int x){
	if(x==fa[x])
	return x;
	return fa[x]=find(fa[x]);
}
void join(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
	return ;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		join(x,y);
		d[x]++;
		d[y]++;
	}
	for(int i=1;i<=n;i++) num[find(i)]++;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(find(x)==find(y)){
			d[x]++;
			d[y]++;
		}
	}	
	for(int i=1;i<=n;i++){
		cout<<num[find(i)]-d[i]-1<<" ";
	}	
} 
```




#### 求过 2023/3/25


---

## 作者：scp020 (赞：0)

### 题目大意

共有 $n$ 个用户，给出 $m$ 组互关和 $k$ 组互黑关系，可化为两个图。对于每一个互关关系连通块，原来没有互关的人可以互关，除了两人已经互黑。这样的人成为推荐用户。

求每个人有几个推荐用户。

### 方法

考虑深度优先搜索加上容斥原理的方法。

深度优先搜索求出每个连通块的用户数量 $num_i$，即为用户 $i$，与用户 $i$ 互关的用户，与用户 $i$ 互黑的用户和推荐用户。

可列得式子：
$$\boxed{\text{推荐用户}_i = num_i - \text{与用户}_i \text{互关的人数} - \text{与用户}_i \text{互黑的人数} - 1}$$

现在只要求在一个连通块中与用户 $i$ 互黑的人数即可。

考虑类似并查集做法，记好每个用户属于哪个连通块，然后枚举与用户 $i$ 互黑的用户，如果两个用户在一个连通块里，即可减掉这个假的推荐用户。

### 代码

```cpp
#include<bits/stdc++.h>//dfs+容斥原理做法 
using namespace std;
inline void read(int &x)
{
	int f=1;
	char ch=getchar();
	x=0;
	for(;ch>57 || ch<48;ch=getchar()) if(ch==45) f=-1;
	for(;ch<=57 && ch>=48;ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	x=x*f;
}
int n,m,k,dis[100010],f[100010],fa[100010],cnt,num[100010];
vector<int> at[100010],bl[100010];
inline void search(int pos)
{
	f[pos]=1,fa[pos]=cnt,num[cnt]++;
	bool flag=false;
	for(register int i=0;i<at[pos].size();i++)
		if(!f[at[pos][i]]) search(at[pos][i]),flag=true;
}
int main()
{
	ios::sync_with_stdio(false);
	read(n),read(m),read(k);
	for(register int i=1,x,y;i<=m;i++)read(x),read(y),at[x].push_back(y),at[y].push_back(x);
	for(register int i=1,x,y;i<=k;i++)read(x),read(y),bl[x].push_back(y),bl[y].push_back(x);
	for(register int i=1;i<=n;i++) if(!f[i]) cnt++,search(i);
	for(register int i=1;i<=n;i++) dis[i]=num[fa[i]];
	for(register int i=1;i<=n;i++)
		for(register int j=0;j<bl[i].size();j++) if(fa[i]==fa[bl[i][j]]) dis[i]--;
	for(register int i=1;i<=n;i++) cout<<dis[i]-at[i].size()-1<<' ';
	return 0;
}
```


---

## 作者：Nylch (赞：0)

首先很自然的想到用并查集。

我们统计每个人与多少个人有直接朋友关系，统计每个人与多少个人不能有朋友关系，再统计每个人与多少个人有朋友关系。那么根据容斥原理，答案就是每个人与多少个人有朋友关系 $-$ 每个人与多少个人有直接朋友关系 $-$ 每个人与多少个人不能有朋友关系 $-1$，这里减 $1$ 是因为要减去自己。

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
#define ms(data_name) memset(data_name, 0, sizeof(data_name))
#define msn(data_name, num) memset(data_name, num, sizeof(data_name))
#define For(i, j) for(reg int (i) = 1; (i) <= (j); ++(i))
#define For0(i, j) for(reg int (i) = 0; (i) < (j); ++(i))
#define Forx(i, j, k) for(reg int (i) = (j); (i) <= (k); ++(i))
#define Forstep(i , j, k, st) for(reg int (i) = (j); (i) <= (k); (i) += (st))
#define fOR(i, j) for(reg int (i) = (j); (i) >= 1; (i)--)
#define fOR0(i, j) for(reg int (i) = (j) - 1; (i) >= 0; (i)--)
#define fORx(i, j, k) for(reg int (i) = (k); (i) >= (j); (i)--)
#define tour(i, u) for(reg int (i) = head[(u)]; (i) != -1; (i) = nxt[(i)])
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int rdint() {
  int aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
ll rdll() {
  ll aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int mod = 998244353;
// const int mod = 1e9 + 7;
struct mod_t {
  static int norm(int x) {
    return x + (x >> 31 & mod);
  }
  int x;
  mod_t() {  }
  mod_t(int v) : x(v) {  }
  mod_t(ll v) : x(v) {  }
  mod_t(char v) : x(v) {  }
  mod_t operator +(const mod_t &rhs) const {
    return norm(x + rhs.x - mod);
  }
  mod_t operator -(const mod_t &rhs) const {
    return norm(x - rhs.x);
  }
  mod_t operator *(const mod_t &rhs) const {
    return (ll) x * rhs.x % mod;
  }
};
const int MAXN = 1e5 + 10;
int n, m, k, ans[MAXN], cnt1[MAXN], cnt2[MAXN], cnts[MAXN], f[MAXN];
int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}
inline void work() {
  n = rdint();
  m = rdint();
  k = rdint();
  For(i, n) {
    f[i] = i;
  }
  ms(cnt1);
  ms(cnt2);
  ms(cnts);
  For(i, m) {
    int a = rdint(), b = rdint();
    ++cnt1[a];
    ++cnt1[b];
    if(find(a) != find(b)) {
      f[find(b)] = find(a);
    }
  }
  For(i, n) {
    ++cnts[find(i)];
  }
  For(i, k) {
    int c = rdint(), d = rdint();
    if(find(c) == find(d)) {
      ++cnt2[c];
      ++cnt2[d];
    }
  }
  For(i, n) {
    ans[i] = cnts[find(i)] - cnt1[i] - cnt2[i] - 1;
  }
  For(i, n) {
    printf("%d ", ans[i]);
  }
  printf("\n");
}
int main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

