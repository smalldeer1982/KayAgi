# [ABC320E] Somen Nagashi

## 题目描述

现有 $N$ 个人排成一队，编号从 $1$ 到 $N$，玩一个叫做“流水面条”的游戏，该游戏共有 $M$ 个事件，每个事件含三个变量 $T_i,W_i,S_i$，事件的规则如下：

- 在 $T_i$ 时刻，有 $W_i$ 根面条流了下来，队头的人拿走这些面条，并离开队列，然后于第 $T_i+S_i$ 时刻返回队列，然后返回他的原始位置。

若队列为空，则该事件忽略。

注意：若他于第 $X$ 时刻返回队列，则视为他第 $X$ 时刻在队列。

一开始每个人都有 $0$ 根面条，现要你求出这 $N$ 个人每个人获得了多少面条。

## 说明/提示

#### 样例#1说明：
第 $1$ 个人于 $1$ 时刻拿走 $1$ 根面条，将于 $4$ 时刻返回队列。

第 $2$ 个人于 $2$ 时刻拿走 $10$ 根面条，将于 $102$ 时刻返回队列。

第 $1$ 个人于 $4$ 时刻归队，返回第 $1$ 位，此时他处于队头，然后拿走 $100$ 根面条，将于 $10004$ 时刻返回队列。

第 $3$ 个人于 $10$ 时刻拿走 $1000$ 根面条，将于第 $1000000010$ 时刻归队。

第 $100$ 时刻，队内无人。

最终，这 $3$ 个人分别有 $101,10,1000$ 根面条。

## 样例 #1

### 输入

```
3 5
1 1 3
2 10 100
4 100 10000
10 1000 1000000000
100 1000000000 1```

### 输出

```
101
10
1000```

## 样例 #2

### 输入

```
3 1
1 1 1```

### 输出

```
1
0
0```

## 样例 #3

### 输入

```
1 8
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
8 8 8```

### 输出

```
15```

# 题解

## 作者：robertuu (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_e)

大！暴！力！（好久没见到 E 题出大暴力了）

用两个优先队列维护。第一个优先队列维护事件（包括出现物品和人归队两种），排序方式是时间，同一时间归队优先。另一个优先队列维护人的队列（编号从小到大，归队会原位），按照编号从小到大排序，第一个人就是队首。

这样做法就很简单了（可以看出 STL 有多么的好用）。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct noddle {int t,w,s;};
bool operator <(noddle x,noddle y)
{
	if(x.t != y.t) return x.t > y.t;
	return x.s > y.s; // 投机取巧，归队事件的 s 设为 0
}
priority_queue<noddle> q;
priority_queue<int,vector<int>,greater<int>> l;
long long ans[200001];
int main()
{
	int n,m,t,w,s;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d%d",&t,&w,&s);
		q.push((noddle){t,w,s});
	}
	for(int i = 1;i <= n;i++) l.push(i);
	while(!q.empty())
	{
		noddle tmp = q.top();
		q.pop();
		if(tmp.s == 0) l.push(tmp.w); // 归队
		else if(!l.empty()) // 出现物品
		{
			ans[l.top()] += tmp.w;
			q.push((noddle){tmp.t+tmp.s,l.top(),0});
			l.pop();
		}
	}
	for(int i = 1;i <= n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：zengziqvan (赞：7)

## 题意简述

给定 $n$ 个人与 $m$ 次操作，每次操作会给出三个数 $t,c,w$。

若队列为空，则无视此操作，否则：

- 在队列的第一个人拿到的米的数量 $+c$。

- 在队列里的第一个人出队，并在 $w$ 秒后重新加入队列。

$t$ 表示的是当前的时刻，并且在队列中，编号较小的人在前面。

现在需要你输出所有人获得的米的数量。

## 题目分析

本题是一道很清新的模拟题，只需开两个 `set`，一个存队列，一个存每个人的时间，再开一个 `map`，用来映射第二个 `set` 中的时间对应的人，当然，有时时间会重复，所以要开 `multiset` 与 `multimap`。

时间复杂度 $O(n\log n+m\log m)$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
const int INF=2147483647;
multiset<ll>s1,s2;
multimap<ll,int>mp;
ll a[200010];
int n,m;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;++i) s1.insert(i);
	for(int i=1;i<=m;++i) {
		int t,c,w;
		cin>>t>>c>>w;
		while(t>=*s2.begin()&&s2.size()) {
			s1.insert(mp.find(*s2.begin())->second);
			mp.erase(mp.find(*s2.begin()));
			s2.erase(s2.begin());
		}
		if(s1.empty()) continue;
		a[*s1.begin()]+=c;
		mp.insert(make_pair(w+t,*s1.begin()));
		s1.erase(s1.begin());
		s2.insert(w+t);
	}
	for(int i=1;i<=n;++i) cout<<a[i]<<"\n";
	return 0;
}
```

---

## 作者：fcy20180201 (赞：4)

## 题意
$N$ 个人排队，从队头到队尾分别标号为 $1,2,3,\cdots,N$。

现在有 $M$ 个时刻，第 $i$ 个时刻时间为第 $T_i$ 秒。每个时刻天上都会掉下一团面，重量为 $W_i$，站在队首的人接到这团面（若队列为空则无人接到），接到后立即离开，在 $S_i$ 秒后回到队列的某个位置，使得队列保持编号越小的站的越前，且站回队列的时刻这个人也在队列里。

问每个人各接到多重的面。
## 解法
$O(N\log N)$ 能过，那就直接用 priority_queue 暴力（priority_queue 要变为小编号在前）。

首先把所有人离开和人回来的事件记录下来按时间离散化，按时间顺序依次查看每个事件：若是面掉下来（即人离开），则 priority_queue 队首元素接到面（记得判断队是否为空），并将记录他回来时间的结构体里记录他的编号（vector 即可）；若是人回来，则将所有要回来的人全 push 进 priority_queue。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m,cnt;
ll ans[200005];
vector<int>emp;
struct TTT{//记录所有事件
	bool por;
	int t,s;
	ll w;
  	vector<int>rp;
}evt0[400005];

bool operator <(const TTT &a,const TTT &b){//排序和 lower_bound 需要
	return a.t==b.t?a.por<b.por:a.t<b.t;
}
bool operator ==(const TTT &a,const TTT &b){//unique 需要
	return a.t==b.t && a.s==b.s && a.por==b.por && a.w==b.w && a.rp==b.rp;
}

priority_queue<int, vector<int>, greater<int>>q;//小编号在前的 priority_queue
int main(){
  	scanf("%d%d",&n,&m);
  	for(int i=1;i<=n;i++)q.push(i);
  	while(m--){
    	int t,s;ll w;
    	scanf("%d%lld%d",&t,&w,&s);
    	evt0[cnt++]=(TTT){1,t,s,w,emp},evt0[cnt++]=(TTT){0,t+s,0,0,emp};//记录人离开和回来的两个事件
 	}
   //离散化
  	sort(evt0,evt0+cnt);
  	cnt=unique(evt0,evt0+cnt)-evt0;
  	for(int i=0;i<cnt;i++){
    	if(evt0[i].por){//若人离开
    		if(q.empty())continue;
      		int x=q.top();q.pop();
      		ans[x]+=evt0[i].w;
			evt0[lower_bound(evt0,evt0+cnt,(TTT){false,evt0[i].t+evt0[i].s,0,0,emp})-evt0].rp.push_back(x);//在记录他回来的时间的结构体里加上他的编号
    	}
    	else{for(int x:evt0[i].rp)q.push(x);}
  	}
  	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
  	return 0;
}
```
## 提醒
unique 结构体一定要重载 $==$ ！！！

---

## 作者：Mr_Biantainne (赞：3)

## 题外话
~~刚考完 CSP 就考这个，似乎有点压力太大了。~~
## 题意简述
$n$ 个人编号 $1...n$ 在排队，第 $t$ 秒会有 $w$ 的面掉下来，队伍最前面的人会接到面，随后离开队伍去吃面，在 $t + s$ 秒会回来继续接面。**队伍时刻保证编号小的人在编号大的人前面。**
## 解法介绍
### 做法
用两个优先队列来维护。

第一个优先队列按照时间来排序，为了知道编号，所以可以做一个结构体。

第二个优先队列按照编号来排序，找到队首的人。
### 使用方法
当面掉下来的时候，先把第一个队列中的所有时间 $\le t$ 来到的人找出来，一个个弹出来，把编号放进第二个队列里。由于第一个队列已经按时间排过序了，所以直接从第一个开始找，找到 $> t$ 来到的人就停下来。

接下来在第二个队列里找到编号最小的人（即队首的人，因为已经按照编号排序），他接到了面，把他拿到的面量更新，随后把他的时间设置为 $t + s$，重新加入第一个队列。
## 特殊判断
第一个优先队列把人弹出来时要判断里面还有没有人！

第二个优先队列要看看是有人在等面，还是一个人都没有！
## 代码（附注释）
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#define ll long long
using namespace std;
ll n, m, t, w, s, rec[200005]; //rec表示拿到的面条量
struct person //一个人的信息
{
    ll idex, tms;
}tmp; //临时存储用变量
priority_queue <person> pq; //一个优先队列记录编号和时间，时间优先
priority_queue <ll, vector <ll>, greater <ll>> pq2; //另一个优先队列记录编号，小的排前面
bool operator < (person ta, person tb) //重载
{
    return ta.tms > tb.tms; //优先队列的比较是反的
}
inline ll read() //快读板子
{
    char c = getchar();
    ll x = 0, f = 1;
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar())
        x = x * 10 + c - 48;
    return x * f;
}
inline void write(ll x) //快写板子
{
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    n = read(), m = read();
    for (ll i = 1; i <= n; i++) //预处理，原来大家都在队里
    {
        tmp.idex = i;
        tmp.tms = 0;
        pq.push(tmp);
    }
    for (ll i = 1; i <= m; i++)
    {
        t = read(), w = read(), s = read();
        while (pq.size()) //把已经到达的人找出来，同时要判断队列是否为空
        {
            tmp = pq.top();
            if (tmp.tms > t) break; //超过时间了
            pq.pop();
            pq2.push(tmp.idex); //放入第二个队列，找编号最小的
        }
        if (pq2.size()) //防止空队
        {
            //cout << pq2.top() << " got the noodles\n";
            rec[pq2.top()] += w; //记录拿到的面
            tmp.idex = pq2.top();
            pq2.pop();
            tmp.tms = t + s; //出去吃面
            pq.push(tmp); //重新排时间
        }
    }
    for (ll i = 1; i <= n; i++) write(rec[i]), puts(""); //输出每个人拿到的面量
}
```

---

## 作者：zhizhi_c (赞：1)

此题不难，但不好调，我比赛结束后才调出来。

我们先维护一个优先队列 $\text{pq}$，用它来存储当前队列，元素是编号，为什么要用优先队列呢？因为题目里说了，返回队列是返回他的原始位置，所以编号越小排的越靠前。再维护另一个优先队列 $\text{pq2}$，用来存储离开队列的人的编号和返回时间。队列 $\text{pq2}$ 里所有返回时间小于等于 $T_i$ 的人都要出队并将编号入队 $\text{pq}$。而 $\text{pq}$ 的队头所对应的人获得这 $W_i$ 根面条并出队，并将该人返回时间的编号入队 $\text{pq2}$。

时间复杂度为 $O(M\log N)$。
### AC代码：
```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

struct node {int t, w, s;} a[200005];
priority_queue<int, vector<int>, greater<int> > pq;
priority_queue<pii, vector<pii>, greater<pii> > pq2;
int n, m;
long long val[200005]; //1e9 * 2e5 = 2e14，不开long long见祖宗

signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) pq.push(i); //初始入队
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].t, &a[i].w, &a[i].s);
	for (int i = 1; i <= m; i++) {
		while (!pq2.empty() && pq2.top().first <= a[i].t) {
			pq.push(pq2.top().second);
			pq2.pop();
		} //将所有入队时间小于等于T[i]全部入队pq
		if (pq.empty()) continue; //若pq为空跳过
		int u = pq.top();
		pq.pop();
		val[u] += a[i].w;
		pq2.push(make_pair(a[i].t + a[i].s, u)); //将归队时间和编号入队pq2
	}
	for (int i = 1; i <= n; i++) printf("%lld\n", val[i]);
	return 0;
}
```

---

## 作者：OIerBoy (赞：1)

# Sol
水题一道。

需要两个优先队列：

- 因为每一次是队首的人拿到面条，即队列中编号最小的拿面条，就用一个优先队列用来维护当前队列中的编号最小的人。

- 由于每一次拿了面条后再回到队列中的时间有所不同，用一个优先队列维护回到队列时间最早的人，以及编号。

这样，这道题就已经做完了。时间复杂度 $O(n \log n + m \log m)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define FO(i,j,k) for(int i=j;i;i=k)
#define PB(i) push_back(i)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(long long i=j;i<=k;++i)
#define FoR(i,j,k) for(long long i=j;i^k;++i)
#define FOR(i,j,k) for(long long i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}
struct Node{
	int t,w,s;
}tt[N];
int n,m;
int a[N];
priority_queue<int,vector<int>,greater<int>>q;
struct TT{
    int x,y;
    TT(){}
    TT(int x,int y):x(x),y(y){}
    bool operator< (const TT &a)const {
        return x < a.x;
    }
};
struct cmp1{
    bool operator()(const TT &a,const TT &b){
        return a.y > b.y;
    }
};
priority_queue<TT,vector<TT>,cmp1 > k;
bool cmp(Node a,Node b){
	return a.t<b.t;
}
int ans[N];
signed main(){
    cin>>n>>m;
    For(i,1,n+1)q.push(i);
    For(i,1,m){
    	int t,w,s;
    	cin>>t>>w>>s;
    	tt[i].t=t;
    	tt[i].w=w;
    	tt[i].s=s;
	}
	sort(tt+1,tt+1+m,cmp);
    For(i,1,m){
    	int t=tt[i].t,w=tt[i].w,s=tt[i].s;
    	while(!k.empty()&&k.top().y<=t){
    		q.push(k.top().x);
    		k.pop();
		}
    	if(q.top()==n+1)continue;
    	ans[q.top()]+=w;
//    	cout<<q.top()<<' '<<w<<endl<<endl;
    	k.push((TT){q.top(),t+s});q.pop();
	}
	For(i,1,n)cout<<ans[i]<<endl;
	return 0;
} 
```


---

## 作者：Zkl21 (赞：1)

[原题链接](https://atcoder.jp/contests/abc320/submissions/45640798)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc320_e)
## 题意
略
## 思路
分别维护两个信息：在排队的人中**编号最小的人**和不在排队的人中**最早回来的人**。

每次分配面条前先处理一下**不在排队的人中最早回队的能否在当前时间之前赶回来**，如果能赶回来，就将他重新放在排队的人中，并继续考虑下一个不在排队的人。

最后选排队的人中**编号最小**的拿走当前的面条，并将它放到不在排队的人的集合中。

可以用优先队列或 set 维护上面所说的两个信息，具体实现很好写，时间复杂度
为 $O((n+m)\log n)$ 级别。
[代码](https://atcoder.jp/contests/abc320/submissions/45640798)

---

## 作者：白简 (赞：1)

### 题目大意
有一种面条，每次会被队首的人拿到。

给出每个面条出现的时间，队首的人拿到面条后到队外，到达时间后回到队伍里他原本的位置。

如果来面条的时间和某个人回队的时间相同，那么人先回队，面条再来。如果队内没有人，那么没有人拿到面条。
### 思路
维护两个小根堆，一个维护队内元素，按人的编号排序；另一个维护出队的元素，按照回队的时间排序。

每次来新的面条前，我们先把能回队的人回队，然后队首拿面条。

模拟即可。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 200500;

int n,m;

int t[N],w[N],s[N];

int val[N];

priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > que1;
priority_queue< int,vector<int>,greater<> > que2;

signed main() {
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for(int i = 1;i <= n; i++) {
        que2.emplace(i);
    }
    
    for(int i = 1;i <= m; i++) {
        cin >> t[i] >> w[i] >> s[i];
        
        while(!que1.empty() && que1.top().first <= t[i]) {
            auto const p = que1.top();
            que1.pop();
            que2.push(p.second);
        }

        if(que2.empty())
            continue;
        
        int const x = que2.top();
        std::pair<int, int> tmp;
        que2.pop();

        tmp.second = x;
        tmp.first = t[i] + s[i];
        val[x] += w[i];

        que1.push(tmp);
    }

    for(int i = 1;i <= n; i++)
        cout << val[i] << "\n";
    return 0;
}
```

---

## 作者：Flandres (赞：1)

我们可以把每一个时刻进行的操作分为两类事件：

1. 一个人重新加入到这一排

2. 排在最前面的人拿到面条后离开

我们可以开一个小根堆维护时间轴，并判断当前时刻属于哪一类事件。再开一个小根堆维护当前时刻这一排的人的编号。这样这题就做完了。

注意事件 1 的优先级要高于事件 2。

code：

```cpp
#include<bits/stdc++.h>
using ll=long long;
int n,m,t,w,s;ll ans[200005];
struct node{
	int tim,id,x,y;
	node(int tim,int id,int x,int y):tim(tim),id(id),x(x),y(y){}
	bool operator>(const node &A)const{return tim==A.tim?id>A.id:tim>A.tim;}
};
std::priority_queue<int,std::vector<int>,std::greater<int>> p;
std::priority_queue<node,std::vector<node>,std::greater<node>> q;
int main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin>>n>>m;
	for(int i=1;i<=m;++i){
		std::cin>>t>>w>>s;
		q.push(node(t,1,w,s));
		p.push(i);
	}
	while((q.top().tim)<=t){
		const auto now=q.top();q.pop();
		if(now.id){
			int x=p.top();p.pop();
			ans[x]+=now.x;
			q.push(node(now.tim+now.y,0,x,114514));
		}
		else p.push(now.x);
	}
	for(int i=1;i<=n;++i)std::cout<<ans[i]<<'\n';
	return 0;
}
```



---

## 作者：Coffee_zzz (赞：1)

数据结构学傻之后想到的方法。

分析一下。

我们可以用小根堆实时维护每个元素是否在队列中，每次操作相当于给在队列中的编号最小的元素的值增加 $w_i$。

那么线段树直接维护在队列中的编号最小的元素即可。

这里的线段树只需要支持单点修改。

复杂度 $O(n \log n)$。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,m,t[N],w[N],s[N],val[N<<2];
int ans[N];
void upd(int g){
	val[g]=min(val[g<<1],val[g<<1|1]);
}
void build(int g,int l,int r){
	if(l==r){
		val[g]=l;
		return;
	}
	int mid=l+r>>1;
	build(g<<1,l,mid);
	build(g<<1|1,mid+1,r);
	upd(g);
}
void add(int g,int l,int r,int x){
	if(l==x&&r==x){
		val[g]=x;
		return;
	}
	if(r<x||l>x) return;
	int mid=l+r>>1;
	add(g<<1,l,mid,x);
	add(g<<1|1,mid+1,r,x);
	upd(g);
}
void del(int g,int l,int r,int x){
	if(l==x&&r==x){
		val[g]=inf;
		return;
	}
	if(r<x||l>x) return;
	int mid=l+r>>1;
	del(g<<1,l,mid,x);
	del(g<<1|1,mid+1,r,x);
	upd(g);
}
signed main(){
	priority_queue <pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>t[i]>>w[i]>>s[i];
	build(1,1,n);
	for(int i=1;i<=m;i++){
		while(!q.empty()&&q.top().first<=t[i]){
			int x=q.top().second;
			add(1,1,n,x);
			q.pop();
		}
		if(val[1]==inf) continue;
		ans[val[1]]+=w[i];
		q.push({s[i]+t[i],val[1]});
		del(1,1,n,val[1]);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：rainygame (赞：1)

一眼线段树上二分。但是赛时调了好久。

我们删除时可以不真的删除这个人，而是将他的时间设为 $T_i+S_i$，这样如果某个人的时间大于 $T_i$，那么就代表他被删除了。

那如何判断第一个时间小于等于 $T_i$ 的人呢？我们可以考虑使用线段树维护 $[1,x]$ 的最小值，这样就可以二分答案了！具体地，对于一个 $x$，如果 $[1,x]$ 的最小值小于等于 $T_i$，那么他就可以把区间往左调，否则往右调，直到第一个满足条件的 $x$ 即为答案。

注意判断无人的情况。

另外，这题思路由 CSP-J1 2023 完善程序第一题启发，感谢 CCF！

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001

int n, m, t, w, s, now, l, r, mid;
int ans[MAXN];

struct Node{
	int l, r;
	int minn;
}tree[MAXN<<2];

void push_up(int p){
	tree[p].minn = min(tree[p<<1].minn, tree[p<<1|1].minn);
}

void build(int l, int r, int p){
	tree[p].l = l;
	tree[p].r = r;
	if (l == r) return;
	int mid((l+r)>>1);
	build(l, mid, p<<1);
	build(mid+1, r, p<<1|1);
	push_up(p);
}

void modify(int x, int k, int p){
	if (tree[p].l == tree[p].r){
		tree[p].minn = k;
		return;
	}
	int mid((tree[p].l+tree[p].r)>>1);
	if (x <= mid) modify(x, k, p<<1);
	else modify(x, k, p<<1|1);
	push_up(p);
}

int query(int x, int p){
	if (tree[p].r <= x) return tree[p].minn;
	int res(query(x, p<<1)), mid((tree[p].l+tree[p].r)>>1);
	if (x > mid) res = min(res, query(x, p<<1|1));
	return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    build(1, n, 1);
    while (m--){
    	cin >> t >> w >> s;
    	l = 1;
    	r = n;
    	while (l < r){
    		mid = (l+r)>>1;
    		if (query(mid, 1) <= t) r = mid;
    		else l = mid+1;
		}
		
		if (query(l, 1) <= t){
			modify(l, t+s, 1);
			ans[l] += w;
		}
	}
	
	for (int i(1); i<=n; ++i) cout << ans[i] << '\n';

    return 0;
}

```


---

## 作者：CQ_Bob (赞：0)

## 分析

和 CF1070C 差不多。

按照题目模拟，我们需要在每次有面条的时候求出在排队的编号最小的那个人。用线段树维护就行了，有两种情况：

- $i$ 在排队，则其对应的叶子节点权值为 $i$。

- $i$ 没在排队，则其对应的叶子结点权值为极大值。

对于当前最小编号，就是区间 $[1,n]$ 的最小权值。那么，对于最小权值 $k$，也有两种情况：

- $1 \le k \le n$，则表示 $w_i$ 的面条将被编号为 $k$ 的人得到。

- $k$ 为极大值，则表示这次的面条将不会有人得到，因为没有人在排队。

对于情况 $1$，我们将贡献增加之后用一个二分找到 $k$ 这个人下一次重新排队将会在什么时候。再把这个人的对应叶子结点权值赋成极大值就行了。

注：在每次有面条的时候，我们应该先把刚好在这次重新排队的人加上。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define re register
#define il inline

int n,m;
const int N=1e6+10,inf=1e18;
int ans[N];
int t[N],w[N],s[N];
struct node{
	int l,r,s,mi;
}tr[N];
vector<int> ve[N];
il void up(int now){tr[now].mi=min(tr[now<<1].mi,tr[now<<1|1].mi);}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) tr[now].s=tr[now].mi=l;
	else{
		int mid=l+r>>1;
		build(now<<1,l,mid),build(now<<1|1,mid+1,r);
		up(now);
	}
	return ;
}
il void insert(int now,int l,int k){
	if(tr[now].l==tr[now].r) tr[now].s=tr[now].mi=k;
	else{
		int mid=tr[now].l+tr[now].r>>1;
		if(l<=mid) insert(now<<1,l,k);
		else insert(now<<1|1,l,k);
		up(now);
	}
	return ;
}
il int find(int l,int r,int k){
	int ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(k<=t[mid]) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}

il void read(){
	cin>>n>>m;
	return ;
}
il void solve(){
	for(re int i=1;i<=m;++i) cin>>t[i]>>w[i]>>s[i];
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		for(auto j:ve[i]) insert(1,j,j);//把刚好在这次排队的人加上
		int k=tr[1].mi;
		if(k<=n){
			ans[k]+=w[i];
			int wk=t[i]+s[i];
			insert(1,k,inf);//删掉这个人
			int id=find(i+1,m,wk);//二分查找下一次排队的时刻
			ve[id].push_back(k);
		}
	}
	for(re int i=1;i<=n;++i) cout<<ans[i]<<"\n";
	return ;
}

signed main(){
	read(),solve();
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路

我们可以用个类似模拟的思路。

因为我们每次降落面条之前的时候会有人吃完面条回来，那么我们可以记一个优先队列表示目前的队列，另一个队列表示去吃面条的人，这里第二个队列按照返回的时间排序，那么我们对于每一个面条就可以找吃完时间小于等于他的人，然后把他们加入到队列里面，最后取出队首去吃面条。

最后就是代码了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i++)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using i64 = long long;
using namespace std;
const int maxn = 1000000;
int t[maxn], w[maxn], s[maxn];
priority_queue<int, vector<int>, greater<int>> inQ;
priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> UinQ;
i64 ans[maxn];
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    rep(i, 1, n) {
        inQ.push(i);
    }
    rep(i, 1, m) {
        cin >> t[i] >> w[i] >> s[i];
    }
    rep(i, 1, m) {
        while (UinQ.size() && UinQ.top().first <= t[i]) {
            inQ.push(UinQ.top().second);
            UinQ.pop();
        }
        if (inQ.size()) {
            int u = inQ.top();
            inQ.pop();
            ans[u] += w[i];
            UinQ.push({t[i] + s[i], u});
        }
    }
    rep(i, 1, n) {
        cout << ans[i] << "\n";
    }
    return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先我们需要维护队头的元素，但是如果我们每次都去找是需要 $\Theta(n)$ 的复杂度的，所以，我们可以用一个小根堆维护当前在队伍中的人的编号。

然后，我们可以用一个 `vector v[N]` 维护在 $T_i$ 时间会返回队列的元素编号。

对于每一次一个人得到了 $W_i$ 的贡献后，将会在 $T_i + S_i$ 的时间返回，因为题目满足 $T_i$ 单调，所以用一个二分找到在第几次时当前这个人才能返回队列，并加入到 `vector` 中。

当然，在计算每一次操作时，需要将要在 $T_i$ 时间返回的人加入队列。

时间复杂度 $\Theta(n \log n)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,m;
int t[N],w[N],s[N],ans[N];
vector<int> v[N];
priority_queue< int,vector<int>,greater<int> > q;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++) q.push(i);
	for (re int i = 1;i <= m;i++){
		t[i] = read();
		w[i] = read();
		s[i] = read();
	}
	for (re int i = 1;i <= m;i++){
		for (auto p:v[i]) q.push(p);
		if (q.empty()) continue;
		int tp = q.top();
		q.pop();
		ans[tp] += w[i];
		int tim = lower_bound(t + 1,t + m + 1,t[i] + s[i]) - t;
		v[tim].push_back(tp);
	}
	for (re int i = 1;i <= n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：happybob (赞：0)

感觉别人写的太复杂了。

用 `set`，维护当前在队列中的人。每次操作，如果有人，直接累加答案。

然后考虑怎么在 $t_i+s_i$ 时间回来。只需要离线在 $t$ 里面跑一个 `lower_bound` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7; // Remember to change

int n, m;

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

long long ans[N];
long long t[N], w[N], s[N];
vector<int> rev[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	set<int> nowt;
	for (int i = 1; i <= n; i++) nowt.insert(i);
	for (int i = 1; i <= m; i++)
	{
		cin >> t[i] >> w[i] >> s[i];
	}
	for (int i = 1; i <= m; i++)
	{
		for (auto &j : rev[i]) nowt.insert(j);
		if (nowt.size())
		{
			ans[*nowt.begin()] += w[i];
			int gg = *nowt.begin();
			nowt.erase(nowt.begin());
			long long np = t[i] + s[i];
			int g = lower_bound(t + 1, t + m + 1, np) - t;
			if (g >= 1 && g <= m) 
			{
				rev[g].emplace_back(gg);
			}
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	return 0;
}


```


---

## 作者：LCat90 (赞：0)

双 log 做法。可能只有我的做法这么复杂吧。

首先我们维护一个小根堆，记录暂时在外的有哪些人。

每次到了一个时间，我们就可以把满足 $t_x\le t_i$ 的人还原到队列中。

然后问题就是怎么找到第一个在队中的人。

我采用的方法是二分这个人的位置，找到前缀和第一次为 $1$ 的位置。

但是由于有单点修改，于是前缀和就维护一个树状数组。初始时每个位置都附上 $1$，离开时减去 $1$，回来加上 $1$ 即可。

时间复杂度是 $O(m\log^2  n)$。

然后因为号没了所以代码也找不到了。

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

提供一种奇怪的做法。

我们从每个人的角度去分析，计算每个人能得到哪些面条。用 set 记录下所有面条的出现时间，然后不断用当前这个人回到队伍里的时间去 lower_bound，直到找不到为止。把他吃过的所有面条删掉，再继续找下一个人。

假设 $n,m$ 同阶，时间复杂度 $\mathcal O(n \log n)$。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 8e5+5;
int n,m,a[maxn],b[maxn],c[maxn],ans[maxn],t[maxn];
set<tuple<int,int,int>> s;
signed main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i ++) cin >> a[i] >> b[i] >> c[i],s.insert({a[i],b[i],c[i]});
    for(int i = 1;i <= n;i ++){
        if(s.empty()){cout << "0\n";continue;} 
        int res = 0,t = 0;
        while(s.lower_bound({t,-1,-1}) != s.end()){
            auto [x,y,z] = *s.lower_bound({t,-1,-1});
            res += y,t = x + z;s.erase(s.lower_bound({t-z,-1,-1}));
        }cout << res << "\n";
    }
}
```

---

## 作者：OldDriverTree (赞：0)

第一次赛时自己想出 E 题祭。

# Solution

考虑用两个堆来做。

一个小根堆 $q$ 维护人的编号，按人的编号排序。

一个小根堆 $p$ 维护离队的人和回来的时间，按回来的的时间排序。

每次操作就先把 $p$ 中回来的时间小于等于 $T$ 的加入 $q$ 中。

再把 $q$ 的堆顶获得的面条数量加 $W$，并加入 $p$ 中，回来时间为 $T+S$。

时间复杂度 $O((n+m)\log n)$。

# Code
```c++
#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;
const int N=2e5+1; int n,m; long long a[N];
priority_queue<int,vector<int>,greater<int> > p;
priority_queue<P,vector<P>,greater<P> > q;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) p.push(i);
	while (m--) {
		int t,w,s; scanf("%d%d%d",&t,&w,&s);
		while (!q.empty()&&q.top().first<=t) p.push(q.top().second),q.pop();
		if (!p.empty() ) a[p.top()]+=w,q.push({t+s,p.top()}),p.pop();
	}
	for (int i=1;i<=n;i++)
	printf("%lld\n",a[i]);
	return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_e)

感觉和 P5763 很像。

## $\mathtt{Solution}$

考虑跟 P5763 差不多的做法。

考虑维护两个优先队列（我为了偷懒把发生的事件也记录了一个），一个是等待队列，一个是排队队列。

如果当前等待队列的队首回到排队队列的时间小于等于当前事件发生的时间，把等待队列的队首加入到排队队列。直到等待队列为空或者队首不符要求。

然后排队队列的队首离开，加入等待队列。

注意特判一下排队队列为空即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 3e5 + 5;
struct node{
	int x, y, z, id;
	bool operator < (const node &lyn)const{
		if(x != lyn.x)return x > lyn.x;
		return id > lyn.id;
	}
};
priority_queue<node>pq, pq3;//事件，等待队列
priority_queue<int, vector<int>, greater<int> >pq2;//排队队列
int n, m, ans[MAXN];
signed main(){
	n = read(), m = read();
	for(int i = 1;i <= m;i ++){
		int u = read(), v = read(), w = read();
		pq.push({u, v, w, 0});
	}
	for(int i = 1;i <= n;i ++)pq2.push(i);
	for(int i = 1;i <= m;i ++){
		while(!pq3.empty() && pq3.top().x <= pq.top().x){//等待的人可以回到队列了
			pq2.push(pq3.top().id);
			pq3.pop();
		}
		if(!pq2.empty()){//排队队列非空
			ans[pq2.top()] += pq.top().y;
			pq3.push({pq.top().x + pq.top().z, 0, 0, pq2.top()});//回到等待队列
			pq2.pop();
		}
		pq.pop();
	}
	for(int i = 1;i <= n;i ++)printf("%lld\n", ans[i]);
	return 0;
}

```


---

