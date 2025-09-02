# Frog Fights

## 题目描述

Ostap Bender recently visited frog farm and was inspired to create his own frog game.

Number of frogs are places on a cyclic gameboard, divided into $ m $ cells. Cells are numbered from $ 1 $ to $ m $ , but the board is cyclic, so cell number $ 1 $ goes right after the cell number $ m $ in the direction of movement. $ i $ -th frog during its turn can jump for $ a_{i} $ cells.

Frogs move in turns, game starts with a move by frog $ 1 $ . On its turn $ i $ -th frog moves $ a_{i} $ cells forward, knocking out all the frogs on its way. If there is a frog in the last cell of the path of the $ i $ -th frog, that frog is also knocked out. After this the value $ a_{i} $ is decreased by the number of frogs that were knocked out during this turn. If $ a_{i} $ is zero or goes negative, then $ i $ -th frog doesn't make moves anymore.

After frog number $ 1 $ finishes its turn, frog number $ 2 $ starts to move, then frog number $ 3 $ and so on. After the frog number $ n $ makes its move, frog $ 1 $ starts to move again, then frog $ 2 $ and so on this process goes forever. If some frog was already knocked out from the board, we consider that it skips all its moves.

Help Ostap to identify, what frogs will stay on the board at the end of a game?

## 说明/提示

In the first sample first frog jumps $ 1 $ cell and finishes in cell number $ 3 $ . Second frog jumps for $ 3 $ cells and finishes on cell number $ 3 $ , knocking out frog number $ 1 $ . Current jump length for frog number $ 2 $ is now $ 2 $ . Third frog jumps to cell $ 2 $ , then second frog jumps to cell $ 5 $ . Third frog in turn finishes in cell $ 5 $ and removes frog $ 2 $ from the gameboard. Now, it's the only remaining frog in the game.

In the second sample first frog jumps $ 2 $ cells and knocks out frogs in cells $ 2 $ and $ 3 $ . Its value $ a_{i} $ is now $ 0 $ . Then fourth frog jumps and knocks out fifth frog and its $ a_{i} $ is now $ 0 $ too. These two frogs will remains on the gameboard forever.

## 样例 #1

### 输入

```
3 5
2 1
5 3
4 3
```

### 输出

```
1
3 ```

## 样例 #2

### 输入

```
5 6
1 2
3 4
2 5
5 1
6 1
```

### 输出

```
2
1 4 ```

# 题解

## 作者：yizhiming (赞：3)

另一篇题解的做法放了别的链接，感觉怪怪的。

### 题目大意

$n$ 个青蛙，在大小为 $m$ 的环上走，给定初始位置 $p_i$，每次跳跃的大小 $a_i$，每次按照编号从小到大依次行动，并循环若干轮，第 $i$ 个青蛙向前跳 $a_i$ 的距离，并撞翻路上的所有青蛙，包括终点，每撞飞一个 $a_i$ 就减少 $1$，问最后不能再撞飞时活下来哪些青蛙，若 $a_i<0$ 则不能行动。

$1\leq n\leq 10^5,1\leq m \leq 10^9,n\leq m,1\leq a_i,p_i \leq m$。

保证初始青蛙位置不同。

### 题目分析

首先考虑若此时有一只青蛙撞到了它前面的那只青蛙身上，那么对于此时其它青蛙的相对位置并不会发生改变，原因是按照编号行动，那么这个青蛙行动前所有人位置互不相同，行动后只会影响其撞飞所有能撞飞的青蛙后，他前面和后面的两只青蛙，同理可以得出每个青蛙一定会先撞飞它面前的青蛙，才可能撞飞别的青蛙。

所以我们可以维护出所有青蛙撞到它下家的时间，每次求出最小的直接模拟撞击即可，然后时间相同选择编号较小的即可，维护一个双端链表，用来维护相对关系，那么每次只需要重构三个点的相对关系即可，初始时将所有点按照位置从小到大排序，连成一个环，每个点求下家贡献即可。

可以使用堆或者平衡树等轻易维护。

### Code

可以使用优先队列，同时维护每个点下家到它的距离进行判断，也可以写一个带删除的堆，每次删掉相关的贡献，加入新贡献即可。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5+5;
int n,m;
struct aa{
	int p,a,id;
	bool operator<(const aa&x)const{
		return p<x.p;
	}
}in[N];
struct bb{
	int id,val;
	bool operator<(const bb&x)const{
		if(val==x.val){
			return id>x.id;
		}else{
			return val>x.val;
		}
	}
};
int p[N],a[N],inf = 1e18;
priority_queue<bb>q;
int nxt[N],to[N];
int val[N],t[N],now[N];
int dis(int x,int y){
	if(x==y) return inf;
	int d=(p[y]-p[x]+m)%m;
	if(x>y){
		d=(d+a[y])%m;
	}
	if(d<=a[x]){
		return 1;
	}
	if(a[x]<=a[y]){
		return inf;
	}
	int s=a[x]-a[y];
	return (d-a[y]-1)/s+1;
}
void upd(int x){
	if(x==to[x]){
		return;
	}
	val[x] = dis(x,to[x]);
	q.push((bb){x,val[x]});
}
signed main(){
	n = read();m = read();
	for(int i=1;i<=n;i++){
		p[i] = read();a[i] = read();
		in[i].p = p[i];in[i].a = a[i];in[i].id = i;
		now[i] = p[i];
	}
	sort(in+1,in+1+n);
	in[n+1] = (aa){in[1].p+m,in[1].a,in[1].id};
	for(int i=1;i<=n;i++){
		to[in[i].id] = in[i+1].id;
		nxt[in[i+1].id] = in[i].id;
		val[in[i].id] = dis(in[i].id,in[i+1].id);
		q.push((bb){in[i].id,val[in[i].id]});
	}
	int ans = 0;
	while(!q.empty()){
		int u = q.top().id;int z = q.top().val;
		q.pop();
		if(u==to[u]||z==inf){
			break;
		}
//		cout<<"U:"<<u<<" "<<to[u]<<"\n";
		if(z!=val[u]){
			continue;
		}
//		cout<<"ANS:"<<u<<" "<<to[u]<<"\n";
		ans++;
		val[to[u]] = -1;
		p[u]+=dis(u,to[u]);
		to[u] = to[to[u]];
		nxt[to[u]] = u;
		a[u]--;
		upd(nxt[u]);
		upd(u);
	}
	cout<<n-ans<<"\n";
	for(int i=1;i<=n;i++){
		if(val[i]!=-1){
			cout<<i<<" ";
		}
	}
	return 0;
}

```



---

## 作者：xukuan (赞：3)

翻译（由于我被禁言，只能如此贡献翻译）

hjf的翻译不用再发了，我已经厚颜无耻的（划掉）把它拉走了


问题描述：

给定一个含m个格子的环形游戏圆盘，格子顺时针依次编号为1到m，第1个格子和第n个格子相邻。有n只青蛙，每次可以跳a[i]个格子。

青蛙按编号依次轮流跳，编号为1的青蛙先跳。当轮到第i只青蛙跳的时候，他可以跳a[i]个格子，在他跃过的青蛙都会被撞出游戏盘，如果在他跳到的最后一个格子里有青蛙，那么这个格子里的青蛙也会被撞出游戏盘。第i只青蛙的跳跃距离a[i]
会减少，减少的数量刚好是被他撞出游戏盘的青蛙的只数。当a[i]变为小于或者等于0，这只青蛙就不能在跳了，当然他也不会在被其他青蛙撞出游戏盘。

当第1只青蛙跳完后，轮到第2只青蛙跳，然后是第3只......。当最后一只青蛙跳完后，又从第1只青蛙重新开始跳。已经被撞出游戏盘的青蛙不再参与到游戏中。

请计算，最后有多少只青蛙留在游戏盘上。

输入数据：
第11行，两个整数n和m，1≤n≤100000,1≤m≤10,n≤m),分别表示青蛙的数量和游戏盘的格子数量。

接下来n行，每行两个整数p[i]和a[i] (1≤p[i],a[i]≤m)。分别表示第i只青蛙的的初始所在的格子编号和初始的跳跃格子数。

输出数据

第1行，一个整数，表示剩余的青蛙数量。

接下来1行，从小到大表示剩下的青蛙的编号。


样例输入1
```cpp
3 5
2 1
5 3
4 3
```

样例输出1
```cpp
1
3
```

样例输入2:
```cpp
5 6
1 2
3 4
2 5
5 1
6 1
```

样例输出2：
```cpp
2
1 4
```
——————————————————————————————————————————————————————

题解正文：

这题的难度我给了紫色（省选/NOI-）据老师说，当时CF（不要理解成TX的游戏）在比赛时无人AC

简直就是[猪国杀](https://www.luogu.org/problemnew/show/P2482)的翻版

代码有参考[https://blog.csdn.net/ME495/article/details/50751315?locationNum=2&fps=1](https://blog.csdn.net/ME495/article/details/50751315?locationNum=2&fps=1)

常规的模拟肯定会TLE，所以要有优化

关键就是满世界的集合（set），指针（* 与&）和链表。
make_pair()可以用强制类型转换来操作

别的，就不用说了，参考的文章说的很清楚


代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<set>//集合的函数
#define ll long long
#define INF 2147483647
using namespace std;

ll n,m,p[100010],a[100010],x[100010],Next[100010],Prev[100010];

set<pair<ll,ll> > Set;
//这里不能写成set<pair<ll,ll>> Set; 因为>>是位运算符

inline ll read(){
    ll tmp=1,x=0;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
   
    while(isdigit(ch)){
        x=x*10+ch-48;
        ch=getchar();
    }
    return tmp*x;
}//读入优化

ll dis(ll x,ll y){//求x到y的最小距离，如追不到则返回INF（2147483647）
	if(x==y) return INF;
	ll d=(p[y]-p[x]+m)%m;
	if(x>y) d=(d+a[y])%m;
	if(d<=a[x]) return 1;
	if(a[x]<=a[y]) return INF;
	ll s=a[x]-a[y];
	return (d-a[y]-1)/s+1;
}

bool cmp(ll x,ll y){
	return p[x]<p[y];
}

int main(){
	n=read(); m=read();
	for(ll i=1; i<=n; i++){
		p[i]=read();
		a[i]=read();
		x[i]=i;
	}
	sort(x+1,x+1+n,cmp);
	
	for(ll i=1; i<=n; i++){
		if(i<n) Next[x[i]]=x[i+1];
		else Next[x[i]]=x[1];
		Prev[Next[x[i]]]=x[i];
	}//链表
	
	for(ll i=1; i<=n; i++){
		Set.insert(make_pair(dis(i,Next[i]),i));
	}//往集合中插入元素
	
	while(!Set.empty()){//当集合内有元素时
		set<pair<ll,ll> >::iterator it=Set.begin();//定义指针变量it
		if((*it).first==INF) break;//追不上则退出
		ll i=(*it).second;
		Set.erase(it);	Set.erase(make_pair(dis(Next[i],Next[Next[i]]),Next[i]));
		Set.erase(make_pair(dis(Prev[i],i),Prev[i]));
        //删去三个元素
		p[i]+=dis(i,Next[i]);
		a[i]--;
		Next[i]=Next[Next[i]];
		Prev[Next[i]]=i;
        //链表内元素移位
		Set.insert(make_pair(dis(Prev[i],i),Prev[i]));
		Set.insert(make_pair(dis(i,Next[i]),i));
        //插入两个元素
	}
	cout<<Set.size()<<endl;//输出总数
	for(set<pair<ll,ll> >::iterator it=Set.begin(); it!=Set.end(); it++){
		cout<<(*it).second<<' ';//输出个数
	}
	return 0;
}
```

---

## 作者：LinkWish (赞：2)

不容易发现每次相撞的一定是相邻的两个青蛙！

所以就直接想怎么维护所有青蛙中最早相撞的一对。可以按初始坐标排序，把每一个青蛙看成一个函数 $f(x) = k \left\lfloor \frac{x-r}{n} \right\rfloor + b$，其中的 $x$ 不表示操作轮数，表示操作次数。$r$ 在最开始则是这只青蛙的编号，$b$ 是这只青蛙的初始位置，$k$ 是这只青蛙一次跳的格子数。这一类函数与一次函数的性质差别不大，可以直接使用 KTT 维护最小相交时间。需要处理一些细节，这些细节大部分在 push_up 函数中。为了处理跨过 $m$ 的情况，可以将树组倍长，后半部分的位置恒等于前半部分对应位置 $+m$。

但是在这个过程中每个函数会发生变化，但是斜率是一直在下降的。我不太会证复杂度，但是如果能够沿用 KTT 本身的复杂度分析的话，本体的复杂度也是 $O(n \log^3 n)$ 的，常数很小，可以通过。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define endl '\n'
#define si inline
#define fi first
#define se second
using namespace std;typedef long long ll;typedef __int128 li;
typedef pair<int,int> pii;typedef pair<ll,ll> pll;typedef const int ci;
typedef const ll cl;const int iinf=INT_MAX;const ll linf=1e18;
template<typename T>si bool gmax(T &x,const T y){if(x<y)return x=y,1;return 0;}
template<typename T>si bool gmin(T &x,const T y){if(y<x)return x=y,1;return 0;}

namespace LinkWish{

	ci N=200005;

	int n,m,K;
	int note[N];
	
	struct T{
		int x,v,id;
		si bool operator < (const T obj){return x<obj.x;}
	}a[N];

	si ll getr(ll x){return x%n==0?n:x%n;}

	ll X;
	si ll Next(int r){
		if(X%n<=r)return X/n*n+r;
		return (X/n+1)*n+r;
	}
	struct func{
		int k;ll r;li b;
		si li calc(ll x)const{
			if(x<r)return b;
			return (li)k*((x-r)/n+1)+b;
		}
		si bool operator < (const func obj)const{return calc(X)<obj.calc(X);}
	}org[N];
	struct Hoshino{
		func mx,mn;ll tim;
		bool emp;
	}t[N<<2];
	si int ls(int x){return x<<1;}
	si int rs(int x){return x<<1|1;}
	ll tot;
	si void push_up(int x){
		tot++;
		if(t[rs(x)].emp)return t[x]=t[ls(x)],void();
		if(t[ls(x)].emp)return t[x]=t[rs(x)],void();
		t[x].mx=max(t[ls(x)].mx,t[rs(x)].mx);
		t[x].mn=min(t[ls(x)].mn,t[rs(x)].mn);
		t[x].tim=min(t[ls(x)].tim,t[rs(x)].tim);
		func p=t[ls(x)].mx,q=t[rs(x)].mn;
		if(p.calc(X)>=q.calc(X))t[x].tim=X;
		else{
			ll nxt=Next(p.r%n);
			if(p.calc(nxt)>=q.calc(nxt))gmin(t[x].tim,nxt);
			else if(p.k>q.k){
				ll res=(q.calc(nxt)-p.calc(nxt))/(p.k-q.k);
				for(;p.calc(nxt+res*n)<q.calc(nxt+res*n);res++);
				gmin(t[x].tim,nxt+res*n);
			}
		}
	}
	void build(int x,int l,int r){
		if(l==r){
			t[x].tim=linf,t[x].mn=t[x].mx=org[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(ls(x),l,mid),build(rs(x),mid+1,r);
		push_up(x);
	}
	void update(int x,int l,int r,li &pre,vector<int> &del){
		if(t[x].emp||(t[x].tim>X&&t[x].mn.calc(X)>pre)){
			gmax(pre,t[x].mx.calc(X));
			return ;
		}
		if(l==r){
			if(t[x].mx.calc(X)<=pre){
				if(l>n)del.push_back(l-n);
				else del.push_back(l);
			}
			return ;
		}
		int mid=(l+r)>>1;
		update(ls(x),l,mid,pre,del);
		update(rs(x),mid+1,r,pre,del);
		push_up(x);
		gmax(pre,t[x].mx.calc(X));
	}
	void modify(int x,int l,int r,int goal){
		if(l==r){
			t[x].emp=(org[l].b==-iinf),t[x].mn=t[x].mx=org[l],t[x].tim=linf;
			return ;
		}
		int mid=(l+r)>>1;
		if(goal<=mid)modify(ls(x),l,mid,goal);
		else modify(rs(x),mid+1,r,goal);
		push_up(x);
	}

	si void solve(){
		cin>>n>>m,K=2*n;
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].v,a[i].id=i;
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			note[a[i].id]=i;
			org[i].k=org[i+n].k=a[i].v;
			org[i].b=a[i].x,org[i+n].b=a[i].x+m;
			org[i].r=org[i+n].r=a[i].id;
		}
		build(1,1,K);
		for(int rd=0;t[1].tim!=linf;rd++){
			X=t[1].tim;

			vector<int> del;
			li tp=0;
			update(1,1,K,tp,del);
			int id=X%n;
			if(id==0)id=n;

			sort(del.begin(),del.end());
			del.erase(unique(del.begin(),del.end()),del.end());
			for(int i:del){
				org[i].k=org[i+n].k=0;
				org[i].b=org[i+n].b=-iinf;
				org[i].r=org[i+n].r=0;
				modify(1,1,K,i),modify(1,1,K,i+n);
			}

			id=note[id];
			int s=max(0,org[id].k-(int)del.size());
			org[id].b=org[id].calc(X),org[id+n].b=org[id+n].calc(X);
			org[id].r=org[id+n].r=X+n;
			org[id].k=org[id+n].k=s;
			modify(1,1,K,id),modify(1,1,K,id+n);
		}

		vector<int> ans;
		for(int i=1;i<=n;i++)if(org[i].b!=-iinf)ans.push_back(getr(org[i].r));
		sort(ans.begin(),ans.end());

		cout<<ans.size()<<endl;
		for(int i:ans)cout<<i<<' ';
		cout<<endl;
	}

	void mian(){
		//int TT;cin>>TT;
		int TT=1;
		while(TT--)solve();
	}
}

signed main(){
	#ifndef ONLINE_JUDGE
	assert(freopen("in.in","r",stdin));
	//assert(freopen("out.err","w",stderr));
	assert(freopen("out.out","w",stdout));
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	LinkWish::mian();
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## CF625E

### 题意

有 $n$ 只青蛙在一个长度为 $m$ 的环上打架；每只青蛙有一个初始位置 $p_i$，和一个跳跃数值 $a_i$。从 $1$ 号青蛙开始按序号循环行动，每次若第 $i$ 只青蛙行动，则它会向前跳 $a_i$ 个格子，撞飞它遇见的所有青蛙，包括终点格子上的，之后它的 $a_i$ 减去撞飞的青蛙只数，若 $a_i < 0$，它不会移动。求最后剩下的所有青蛙的编号。

$n \le 10^5, m \le 10^9$，不会有两只青蛙一开始在同一个格子里。

### 标签

模拟，事件驱动模拟，堆

### 做法

注意到如果在某个时刻一只青蛙撞上了另外一只青蛙，因为每只青蛙是按顺序移动的，在这个时刻其他青蛙的相对位置的顺序一定不会发生改变。所以，在任意一个时刻在下一次相撞的一定是相邻的两只青蛙。

于是运用事件驱动模拟，直观的思路就是用链表维护相邻青蛙，算出相邻两只青蛙相撞时间，放到堆里，每次取出最先发生的事件，删掉被撞飞的青蛙后删除与这只被撞飞的青蛙相关的事件。如果下一次发生的事件在无穷远处，那么就说明不会再相撞了，结束模拟并输出答案。

这里最容易写错的部分是算出相邻两只青蛙 $x$ 和 $y$ 的追及时间。首先算出下一只青蛙离这只青蛙的实际距离。

首先这两只青蛙在环上的距离是 $(p_y - p_x) \bmod m$，但别忘了考虑编号小的青蛙先移动，所以如果 $x > y$ 就要再加上 $a_y$，其中 $a_x$ 表示 $x$ 的速度，$p_x$ 表示 $x$ 的位置，$m$ 表示环的长度。

要先特判距离 $d$ 是否小于等于 $a_x$，如果是的话下一刻就可以追上。如果不符合，还要特判被追的青蛙的速度是不是更快，如果更快的话就永远也追不上了。最后的情况就是距离除以相对速度 $\lceil \dfrac {d - a_y} {a_x - a_y} \rceil$。

### 代码

```cpp
#pragma GCC optimize("O2")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
const int N = 100010;
int n, m;
int a[N], p[N];
struct event {
	lld t;
	int u;
};
inline bool operator < (const event &x, const event &y) {
	return (x.t ^ y.t) ? (x.t < y.t) : (x.u < y.u);
}
set<event> evts;
int nxt[N], pre[N];
inline void remove(int u) {
	nxt[pre[u]] = nxt[u];
	pre[nxt[u]] = pre[u];
	pre[u] = nxt[u] = 0;
}
inline lld calc(int x, int y) {
	if (x == y) return 0x3f3f3f3f3f3f3f3fll;
	int dis = (p[y] - p[x] + m + ((x > y) ? a[y] : 0)) % m;
	if (dis <= a[x]) return 1;
	if (a[x] <= a[y]) return 0x3f3f3f3f3f3f3f3fll;
//	printf("(%d, %d) %d, %d %d, %d: %d\n", x, y, a[x], a[y], p[x], p[y], (dis - a[y] - 1) / (a[x] - a[y]) + 1);
	return (dis - a[y] - 1) / (a[x] - a[y]) + 1;
}
int id[N];
inline bool cmp(int x, int y) {
	return p[x] < p[y];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", p + i, a + i);
		id[i] = i;
	}
	sort(id + 1, id + n + 1, cmp);
	for (int i = 1; i <= n; ++ i) {
//		printf("%d\n", id[i]);
		nxt[id[i]] = id[(i < n) ? (i + 1) : 1];
		pre[nxt[id[i]]] = id[i];
	}
	for (int i = 1; i <= n; ++ i) evts.insert(event{calc(i, nxt[i]), i});
	for (; evts.size(); ) {
		auto it = evts.begin();
		if (it->t == 0x3f3f3f3f3f3f3f3fll) break;
		int u = it->u;
		evts.erase(it);
		evts.erase(event{calc(nxt[u], nxt[nxt[u]]), nxt[u]});
		evts.erase(event{calc(pre[u], u), pre[u]});
		p[u] += calc(u, nxt[u]);
		-- a[u];
		remove(nxt[u]);
		evts.insert(event{calc(pre[u], u), pre[u]});
		evts.insert(event{calc(u, nxt[u]), u});
	}
	printf("%d\n", evts.size());
	for (event evt : evts) printf("%d ", evt.u);
}
```

---

## 作者：Jsxts_ (赞：0)

考虑维护目前局面最先相撞的一对，容易发现肯定是相邻的一对。

然后我们对于每个青蛙，维护以下值：

- 上次更新速度时的全局时间 $t$。

- 当前速度 $v$。

- 走过的总路程 $d$。

容易发现，若某个时刻 $d_x-d_y>dis(x,y)$ 代表 $x$ 把 $y$ 撞飞了。

所以我们容易计算出每个青蛙撞飞下一个青蛙的时间（若撞不到设为 $\infty$，注意这里指的是从一开始经过的时间），将它们放进一个堆里，每次取出最小的更新堆，若最小的为 $\infty$ 则结束。最后留在堆内的就是答案。

那么考虑如何计算撞飞时间以及如何更新堆。

先计算出 $d'_x,d'_y$ 为当前时间的 $d$，即 $d'_x=d_x+(now-t_x)\times v_x$。

若 $v_x\le v_y$，若 $x$ 先撞并且一步能到先判掉，否则就撞不到。

否则若 $y$ 先走，由 $d'_x+tv_x-(d'_y+tv_y)>dis(x,y)$ 得 $t>\frac{d'_y-d'_x+dis(x,y)}{v_x-v_y}$，即 $t=\lceil\frac{d'_y-d'_x+dis(x,y)}{v_x-v_y}\rceil$。当 $x$ 先走时类似，得 $t=\lceil\frac{d'_y-d'_x+dis(x,y)-v_x}{v_x-v_y}\rceil+1$。

对于更新堆，我们维护一个循环双向链表，即要把 $(pre_x,x),(x,nxt_x)$ 更新。但是堆不支持删除，所以使用延迟删除，标记每个数在堆中的最后加入时刻。注意还有一种特殊情况是同时撞飞很多青蛙，在撞飞 $nxt_x$ 后接着往后判断即可。

$O(n\log n)$。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,m,tot,vis[N + 10];
struct node {
	int p,v,id;
}a[N + 10];
int cmp(node x,node y) {
	return x.p < y.p;
}
int pre[N + 10],nxt[N + 10],ans[N + 10],tim[N + 10];
ll dd[N + 10];
int dis(int x,int y) {
	int npx = a[x].p,npy = a[y].p;
	return npx < npy ? npy - npx : m - npx + npy;
}
ll calc(int x,int y,int now) {
	ll ndx = dd[x] + 1ll * a[x].v * (now - tim[x]),ndy = dd[y] + 1ll * a[y].v * (now - tim[y]);
	if (a[x].id < a[y].id && dis(x,y) <= a[x].v) return 1;
	else if (a[x].id < a[y].id && a[x].v > a[y].v) return ceil((dis(x,y) - ndx + ndy - a[x].v) * 1.0 / (a[x].v - a[y].v)) + 1;
	return a[x].v <= a[y].v ? INF : ceil((dis(x,y) - ndx + ndy) * 1.0 / (a[x].v - a[y].v));
}
struct node2 {
	int x,y,v,w;
	bool operator < (const node2 &y) const {
		return v == y.v ? a[x].id > a[y.x].id : v > y.v;
	}
};
void del(int x) {
	pre[nxt[x]] = pre[x];
	nxt[pre[x]] = nxt[x];
	pre[x] = nxt[x] = -1;
}
signed main() {
	n = read();
	m = read();
	for (int i = 1;i <= n;i ++ ) a[i].p = read(), a[i].v = read(), a[i].id = i;
	sort(a + 1,a + n + 1,cmp);
	priority_queue<node2> q;
	for (int i = 1;i <= n;i ++ ) nxt[i] = i % n + 1, pre[i] = (i + n - 2) % n + 1, q.push({i,nxt[i],calc(i,nxt[i],0),vis[nxt[i]] = ++tot});
	while (q.size() > 1) {
		node2 t = q.top();
		if (pre[t.x] < 0 || t.y != nxt[t.x] || vis[t.y] != t.w) {
			q.pop();
			continue;
		}
		if (t.v >= INF) break;q.pop();
		int x = t.x,lsp = a[x].p;
		ll dx = 1ll * (t.v - tim[x]) * a[x].v;
		dd[x] += dx;
		tim[x] = t.v;
		a[x].v --;
		del(nxt[x]);
		while (nxt[x] != x && dd[x] - (dd[nxt[x]] + 1ll * (t.v - tim[nxt[x]] - (a[x].id < a[nxt[x]].id)) * a[nxt[x]].v) >= dis(x,nxt[x])) a[x].v --, del(nxt[x]);
		a[x].v = max(a[x].v,0ll);
		q.push({pre[x],x,t.v + calc(pre[x],x,t.v),vis[x] = ++tot});
		q.push({x,nxt[x],t.v + calc(x,nxt[x],t.v),vis[nxt[x]] = ++tot});
	}
	tot = 0;
	while (!q.empty()) {
		node2 t = q.top();
		if (!(pre[t.x] < 0 || t.y != nxt[t.x] || vis[t.y] != t.w)) ans[++tot] = a[t.x].id;
		q.pop();
	}
	sort(ans + 1,ans + tot + 1);
	printf("%lld\n",tot);
	for (int i = 1;i <= tot;i ++ ) printf("%lld ",ans[i]);
	return 0;
}
```


---

