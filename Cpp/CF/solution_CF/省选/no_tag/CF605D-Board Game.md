# Board Game

## 题目描述

You are playing a board card game. In this game the player has two characteristics, $ x $ and $ y $ — the white magic skill and the black magic skill, respectively. There are $ n $ spell cards lying on the table, each of them has four characteristics, $ a_{i} $ , $ b_{i} $ , $ c_{i} $ and $ d_{i} $ . In one move a player can pick one of the cards and cast the spell written on it, but only if first two of it's characteristics meet the requirement $ a_{i}<=x $ and $ b_{i}<=y $ , i.e. if the player has enough magic skill to cast this spell. However, after casting the spell the characteristics of a player change and become equal to $ x=c_{i} $ and $ y=d_{i} $ .

At the beginning of the game both characteristics of a player are equal to zero. The goal of the game is to cast the $ n $ -th spell. Your task is to make it in as few moves as possible. You are allowed to use spell in any order and any number of times (for example, you may not use some spells at all).

## 样例 #1

### 输入

```
4
0 0 3 4
2 2 5 3
4 1 1 7
5 3 8 8
```

### 输出

```
3
1 2 4
```

## 样例 #2

### 输入

```
2
0 0 4 6
5 1 1000000000 1000000000
```

### 输出

```
-1
```

# 题解

## 作者：KazamaRuri (赞：3)

## 题意

给定 $ n $ 张卡片，每张卡片上写有两个点坐标 $ (a,b) $ 和 $ (c,d) $，如果当前所在点坐标为 $ (x,y) $，当 $ x \ge a $ 且 $ y \ge b $ 时，可以使用当前卡片把坐标变为 $ (c,d) $。最开始在 $ (0,0) $ 的位置。

## 分析

边权全为一的最短路问题，考虑用bfs求解。难点在于枚举点时需要 $ O(n) $，会超时。考虑优化，设当前在点 $ (x,y) $ 上，需要快速求出 $ x \ge a $ 且 $ y \ge b $ 的卡片有哪些。这是一个**二维偏序**问题，那我们可以先用权值树状数组或者权值线段树解决掉一维，我用的是树状数组。

对于每个树状数组的节点 $ t_{i} $，根据树状数组定义，我们存下所有 $ i - lowbit(i) + 1 \le a \le i $ 的卡片的集合（实际用的是vector，因为要排序二分），并且按 $ b $ 排序，查询时就可以用二分找到可以用到第几张卡片，时间复杂度 $ O(n \log^2 n) $。但还是太慢，根据bfs的性质，**一个点被遍历过后就已经求出最短路了，不需要再次遍历**，那我们每次在二分完当前树状数组节点后，就把前面这一段删掉，因为这些节点被遍历过后没用了。当然 vector 的删除很慢而且用以出问题，所以我维护了一个下标表示到第几张卡片没被用过，这样总时间复杂度降为 $ O(n \log n) $。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int N=1e5+5;
typedef pair<int,int> pii;
int n,h[N],cnt,dis[N],r[N],p[N];
struct card{ int a,b,c,d; }a[N];
vector<pii>t[N]; queue<int>q;
inline int lb(int x){ return x&-x; }
int _get(int i,int x){
	if(p[i]==t[i].size()) return p[i]-1;
	int l=p[i],r=t[i].size()-1,mid;
	if(t[i][p[i]].first>x) return p[i]-1;
	while(l<r){
		mid=l+r+1>>1;
		if(t[i][mid].first<=x) l=mid;
		else r=mid-1;
	} return r;
}
void print(int x){
	if(!x) return ;
	print(r[x]);
	printf("%d ",x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&a[i].a,&a[i].b,&a[i].c,&a[i].d),h[++cnt]=a[i].a;
	sort(h+1,h+1+cnt,less<int>());
	cnt=unique(h+1,h+1+cnt)-h-1;
	if(h[1]){ puts("-1"); return 0; }
	for(int i=1;i<=n;i++){
		a[i].a=lower_bound(h+1,h+1+cnt,a[i].a)-h;
		for(int j=a[i].a;j<=cnt;j+=lb(j))
			t[j].push_back({a[i].b,i});
	}
	for(int i=1;i<=cnt;i++)
		sort(t[i].begin(),t[i].end());
	q.push(0);
	while(q.size()){
		int u=q.front(); q.pop();
		if(u==n) break;
		for(int i=upper_bound(h+1,h+1+cnt,a[u].c)-h-1;i;i-=lb(i)){
			int m=_get(i,a[u].d);
			for(int j=p[i];j<=m;j++){
				int v=t[i][j].second;
				if(dis[v]) continue;
				dis[v]=dis[u]+1,r[v]=u;
				q.push(v);
			}
			p[i]=m+1;
		}
	}
	if(!dis[n]){ puts("-1"); return 0; }
	printf("%d\n",dis[n]); print(n);
	
	return 0;
}
```

---

## 作者：Saliеri (赞：3)

~~上天不要惩罚我水题解。~~

___

其实写这篇题解的原因是我看到题解区里面全是 $O(n\log^2n)$ 感到很迷惑。

本篇题解复杂度是 $O(n\log n)$。

原问题可以转化为建图连边跑最短路，不多提。但是问题在于**边数过多**，考虑如何处理这个事情。

首先，显然地，图中所有边权都为 1，所以可以使用 BFS 来代替 Dij 等最短路算法。

观察到，一个点在入队后是不会再次入队的，即，**到达它的边也不会再一次被用到**。

那么我们可以有这样一种想法：维护一个数据结构，BFS，一个点出队时，将所有其能到达的点入队并从数据结构中删除。

这个数据结构处理的是**二维偏序**，所以当然可以直接 树状数组 + set 硬草。

但是因为这个题只有删除，所以可以只维护一维偏序在线段树上，第二维挂在每一个叶子节点的 vector 里。

进行删除操作时及时回溯，复杂度就可均摊为 $O(n\log n)$。

____

Code：

```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using std::min;
const int maxn = 1e5+5;
int n,a[maxn],b[maxn],c[maxn],d[maxn];
int lsh[maxn],M,mn[maxn<<2];
int Erf(int x){return std::upper_bound(lsh+1,lsh+M+1,x)-lsh-1;}
std :: vector <int> pt[maxn];
void ins(int k,int l,int r,int p,int v){
	if(l == r){
		pt[l].push_back(v);
		mn[k] = min(mn[k],b[v]);
		return ;
	}
	int mid = l+r>>1;
	p<=mid?ins(k<<1,l,mid,p,v):ins(k<<1|1,mid+1,r,p,v);
	mn[k] = min(mn[k<<1],mn[k<<1|1]);
}
int dis[maxn],pre[maxn];
std :: queue <int> q;
void chk(int k,int l,int r,int x,int y,int P){
	if(l>x||mn[k]>y)return ;
	if(l == r){
		int id;
		while(pt[l].size() && b[id=*--pt[l].end()] <= y)
			pre[id] = P,dis[id] = dis[P] + 1,q.push(id),pt[l].pop_back();
		mn[k] = pt[l].size()?b[id=*--pt[l].end()]:0x3f3f3f3f;
		return ;
	}
	int mid = l+r>>1;
	chk(k<<1,l,mid,x,y,P),chk(k<<1|1,mid+1,r,x,y,P);
	mn[k] = min(mn[k<<1],mn[k<<1|1]);
}
void groute(int x){
	if(pre[x])groute(pre[x]);
	printf("%d ",x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
	for(int i=1;i<=n;++i)lsh[++M] = a[i];
	std :: sort(lsh+1,lsh+M+1),M = std :: unique(lsh+1,lsh+M+1)-lsh-1;
	for(int i=1;i<=n;++i)a[i] = std :: lower_bound(lsh+1,lsh+M+1,a[i])-lsh,ins(1,1,M,a[i],i);
	for(int i=1;i<=M;++i)sort(pt[i].begin(),pt[i].end(),[](int x,int y){return b[x]>b[y];});
	memset(dis,-1,sizeof(dis)),dis[0] = 0;
	q.push(0);
	while(!q.empty()){
		int u = q.front();
		q.pop(),chk(1,1,M,Erf(c[u]),d[u],u);
	}
	printf("%d\n",dis[n]);if(~dis[n])groute(n);
	return 0;
}
```



---

## 作者：是个汉子 (赞：2)

 [洛谷传送门](https://www.luogu.com.cn/problem/CF605D)	[CF传送门](http://codeforces.com/problemset/problem/605/D)

### Solution

可以想到从 $(0,0)$ 开始BFS，第一次更新某个点即为最小。

但是怎么维护对于每对 $(a,b,c,d)$ 可以选择的点？

肯定要找所有比 $(a,b)$ 小的数，那么就是在一个第一维小于 $a$ 的集合中，找一个第二维小于 $b$ 的集合。

考虑使用树状数组+ $\operatorname{set}$ 来维护。

在一个坐标为 $a$ 的节点储存一个 $\operatorname{set}$ ，其中是所有比 $a$ 小的集合，然后找第二个数的时候，直接用 $\operatorname{set}$ 自带的二分查找即可。

时间复杂度： $O(n\log ^2n)$ 空间复杂度： $O(n\log n)$ 

### Code

```c++
#include<bits/stdc++.h>
#define PII pair<int,int>

using namespace std;
const int N=100010;
bool vis[N<<1];
int n,m,cnt,a[N],b[N],c[N],d[N];
map<int,int> mp;
set<PII> tr[N<<1];
vector<int> vec;

inline int lowbit(int x){
    return x&-x;
}

inline void update(int x,PII val){
    for(;x<=m;x+=lowbit(x)) tr[x].insert(val);
}

vector<int> query(int x,int y){
    vector<int> tmp;
    for(;x;x-=lowbit(x)){
        set<PII>::iterator p=tr[x].upper_bound(make_pair(y,N));
        set<PII>::iterator it;
        for(it=tr[x].begin();it!=p;it++) tmp.push_back(it->second);
        tr[x].erase(tr[x].begin(),p);
    }
    return tmp;
}

int dist[N],from[N],rd[N];
inline void bfs(){
    memset(from,-1,sizeof(from));
    memset(dist,-1,sizeof(dist));
    vector<int> u=query(mp[0],0);
    queue<int> q;
    for(int i=0;i<u.size();i++)
        q.push(u[i]),vis[u[i]]=true,dist[u[i]]=1;
    while(!q.empty()){
        int k=q.front();q.pop();
        vector<int> v=query(mp[c[k]],d[k]);
        for(int i=0;i<v.size();i++){
            if(vis[v[i]]) continue;
            vis[v[i]]=true;
            dist[v[i]]=dist[k]+1;
            from[v[i]]=k;
            q.push(v[i]);
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
        vec.push_back(a[i]),vec.push_back(c[i]);
    }
    sort(vec.begin(),vec.end());
    mp[vec[0]]=++m;
    for(int i=1;i<vec.size();i++)
        if(vec[i]>vec[i-1]) mp[vec[i]]=++m;
    for(int i=1;i<=n;i++)
        update(mp[a[i]],make_pair(b[i],i));
    bfs();
    printf("%d\n",dist[n]);
    if(dist[n]==-1) return 0;
    int pos=n;
    while(pos!=0){
        rd[++cnt]=pos;
        pos=from[pos];
    }
    for(int i=cnt-1;i>=1;i--)
        printf("%d ",rd[i]);
    return 0;
}
```



---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/605/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF605D)

安利个人 blog：https://www.cnblogs.com/ET2006/

事实上是一道非常容易的题

很容易想到如果 $c_i\geq a_j$ 且 $d_i\geq b_j$ 就连一条 $i\to j$ 的边表示用完 $i$ 之后可以用 $j$。然后跑 BFS。

直接跑复杂度是 $n^2$，不过发现一个性质，那就是每个点最多被访问一次，故考虑用数据结构优化 BFS 的过程，具体来说，用树状数组套 `set` 维护所有 $(a_i,b_i)$ 的坐标，当访问到某个 $j$ 时候就直接在树状数组套 `set` 上找出**全部满足** $a_i\leq c_j,b_i\leq d_j$ 的 $i$ 并将其压入队列，并直接将这些点从 `set` 中删除。注意到每个点会恰好被删除一次，故总删除次数是线性的，再加上树状数组套 `set` 本身的 2log，复杂度 $n\log^2n$。

记得之前做过一道什么数据结构优化二分图染色的题来着的？这题思想似乎与那题差不多，都是利用每个点最多被访问一次这个性质，用数据结构优化暴力的过程（不过似乎这题比那题还容易一些）。

上帝不要惩罚我刷水题/kk

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
int n,a[MAXN+5],b[MAXN+5],c[MAXN+5],d[MAXN+5];
int key[MAXN*2+5],cnt=0,uni[MAXN*2+5],num=0;
set<pii> st[MAXN*2+5];
void insert(int x,int y,int z){
	for(int i=x;i<=num;i+=(i&(-i))) st[i].insert(mp(y,z));
}
void del(int x,int y,int z){
	for(int i=x;i<=num;i+=(i&(-i))) st[i].erase(st[i].find(mp(y,z)));
}
vector<int> query(int x,int y){
	vector<int> ret;
	for(int i=x;i;i&=(i-1)){
		set<pii>::iterator t=st[i].lower_bound(mp(y+1,0));
		for(set<pii>::iterator it=st[i].begin();it!=t;++it){
			ret.pb(it->se);
		}
	} return ret;
}
int dis[MAXN+5],from[MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
		key[++cnt]=a[i];key[++cnt]=c[i];
	} key[++cnt]=0;sort(key+1,key+cnt+1);key[0]=-1;
	for(int i=1;i<=cnt;i++) if(key[i]!=key[i-1]) uni[++num]=key[i];
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(uni+1,uni+num+1,a[i])-uni;
		c[i]=lower_bound(uni+1,uni+num+1,c[i])-uni;
	}
	for(int i=1;i<=n;i++) insert(a[i],b[i],i);
	memset(dis,-1,sizeof(dis));queue<int> q;
	vector<int> v=query(1,0);
	for(int i=0;i<v.size();i++) dis[v[i]]=1,q.push(v[i]),del(a[v[i]],b[v[i]],v[i]);
	while(!q.empty()){
		int x=q.front();q.pop();v=query(c[x],d[x]);
		for(int i=0;i<v.size();i++){
			int t=v[i];dis[t]=dis[x]+1;from[t]=x;q.push(t),del(a[t],b[t],t);
		}
	}
	if(dis[n]==-1) printf("-1\n");
	else{
		printf("%d\n",dis[n]);vector<int> v;
		for(int i=n;i;i=from[i]) v.pb(i);
		reverse(v.begin(),v.end());
		for(int i=0;i<v.size();i++) printf("%d ",v[i]);
	}
	return 0;
}
```



---

