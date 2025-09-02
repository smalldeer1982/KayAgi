# Two Paths

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Once archaeologists found $ m $ mysterious papers, each of which had a pair of integers written on them. Ancient people were known to like writing down the indexes of the roads they walked along, as « $ a $ $ b $ » or « $ b $ $ a $ », where $ a,b $ are the indexes of two different cities joint by the road . It is also known that the mysterious papers are pages of two travel journals (those days a new journal was written for every new journey).

During one journey the traveler could walk along one and the same road several times in one or several directions but in that case he wrote a new entry for each time in his journal. Besides, the archaeologists think that the direction the traveler took on a road had no effect upon the entry: the entry that looks like « $ a $ $ b $ » could refer to the road from $ a $ to $ b $ as well as to the road from $ b $ to $ a $ .

The archaeologists want to put the pages in the right order and reconstruct the two travel paths but unfortunately, they are bad at programming. That’s where you come in. Go help them!

## 样例 #1

### 输入

```
2
4 5
4 3
```

### 输出

```
1
2 
1
1
```

## 样例 #2

### 输入

```
1
1 2
```

### 输出

```
-1
```

# 题解

## 作者：chenxia25 (赞：9)

如果只选一条路径的话，那就是个欧拉路 / 欧拉回路问题。

考虑两条路径，也就是给定的图一定要是两个欧拉图的并。一个欧拉图可以有 $0/2$ 个奇点，那么不难得到这个并可以有 $0/2/4$ 个奇点。对连通性，（注意一定要不考虑孤立点）一个欧拉图必须连通，那么这个并最多有两个连通分量。接下来分类讨论：

1. 两个连通分量。那么一定是两个各是一个欧拉图就可以了，这个非常简单；

2. 一个连通分量。

   1. $0/2$ 个奇点。那么直接求欧拉路就好了，但是注意到 $L_1,L_2>0$ 这个限制，如果边数为 $1$ 的话就不可能了，否则可以把最后一条边拆出来；

   2. $4$ 个奇点。这个是重头戏（对我来说）。那么拆出来的两个并它的欧拉图，一定是各取了这 $4$ 个中的两个。初步考虑枚举这个分布，对其中一对先找到它们间任意一条路径，方便起见找简单路（一定存在）。那么不难知道，剩下来的一定只有那另两个点是奇点。但是！！连通性不能保证！！！

      这时候不要自闭。我们假设，把这条路径删去后剩下来被拆成若干个连通分量。其中有两个点是奇点，有两种情况，可能是分散在不同连通分量，也有可能在同一个连通分量。但是前者是不可能的！！！有个结论，一个图的奇个数一定是偶数！证明异常简单，每条边会贡献两个度数，于是总度数是偶数，那么所有奇点的度数和也是偶数，那么奇点一定是偶数个。也就是说，拆除来若干个连通分量中一定有一个是包含两个奇点，其它都没有。那么不难想到，对这个连通分量求欧拉路，然后把其它连通分量给嵌到这条简单路中（一定可行，因为无奇点的图的欧拉路起终点（同一个）任意）。

      但是这样做太麻烦了，我写到一半放弃了（小雾）。发现有一种很简单的方法，直接在任意两个奇点之间连虚拟边，然后跑欧拉路，然后再断开。这种以退为进的思想，是我所想不到的了。

实现也需要注意注意。一开始仗着数据范围水就想用 `map` 存邻接矩阵，但由于重边的存在，反而没有邻接表好写。。。

**_[code](https://www.luogu.com.cn/paste/42c11tot)_**

---

## 作者：Rainybunny (赞：6)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[题目链接](https://www.luogu.org/problem/CF36E).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这道题很考察代码实现及调试能力$www$...  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们对于给定的图分类讨论:  
1. 图有一个连通块.  
- 没有度为奇数的点  
任意选点求出一条欧拉路径, 并任意划分为两段即可.  
- 有两个奇度点  
取一个奇度点求欧拉路径, 并任意划分为两段.  
- 有四个奇度点  
取两个奇度点连边, 再去另外一点求欧拉路径, 并按新边划分为两段.  
- $otherwise$  
无解.  

2. 图有两个连通块.  
对于每个连通块, 若多于两个奇度点, 无解, 否则按上文方法分别求解.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最后, 赠送一大堆$hack$过我的数据.
```cpp
10
1 2
2 3
2 4
2 5
5 6
7 8
8 9
9 7
3 5
4 5
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是两个连通块的情况.

```cpp
4
1 5
2 5
3 5
4 5
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这是菊花图的情况, 利于检查新建边的正确性.

```cpp
3
1 2
2 3
2 4
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;四个奇度点的情况, 可以检查是否输出了新建的并不存在于原图的边.

```cpp
5
1 2
1 3
2 3
3 4
5 6
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;还是两个连通块的情况.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$hack$不易, 所以答案自己手玩吧. 希望这些数据对您有帮助. /滑稽.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;代码比较长, 所以有很多细节, 已加上了详细注释$w$.

```cpp
#include <cstdio>
#include <vector>

#define Int register int

using namespace std;

const int MAXN = 10000, MAXM = 10000;
int m, Cnte = 1, Unic, OddCnt, Head[MAXN + 5] = {}, d[MAXN + 5] = {}, UnicOdd[MAXN + 5] = {}, Visnd[MAXN + 5] = {};
bool IsID[MAXN + 5] = {}, Viseg[MAXM + 5] = {}, Outputed[MAXM + 5] = {};
vector<int> Ans;

/*
以往我经常看不懂其它题解的变量意义, 在这里解释一下:
m, Cnte, Unic, OddCnt: 输入的边, 插头Hash的计数器, 连通块数量, 整个图的奇度点数量.
Head, d, UnicOdd, Visnd: 边的头指针数组, 点的度数, 连通块的奇度点个数, 搜索连通块时的标记.
IsID, Viseg: 是否是一个结点 ( 题目没有对编号的约束 ), 找欧拉路的标记 ( 替代删边操作 ).
Outputed, Ans: 已输出的边 ( 路径有环的情况 ), 路径的顶点序列. 

...好累 
*/

struct Edge {
	int To, _nxt;
} Graph[MAXM * 2 + 5] = {};

inline void Link ( const int From, const int To ) {
	Graph[++ Cnte] = { To, Head[From] };
	Head[From] = Cnte;
}

inline void MarkUnicom ( const int u ) { // 标记连通块, 并统计连通块奇度点, 全图奇度点. 
	Visnd[u] = Unic;
	UnicOdd[Unic] += d[u] & 1, OddCnt += d[u] & 1;
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ! Visnd[v = Graph[i].To] ) {
			MarkUnicom ( v );
		}
	}
}

inline void FindEuler ( const int u ) { // 找欧拉路径 
	if ( ! d[u] ) {
		Ans.push_back ( u );
		return ;
	}
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ! Viseg[i >> 1] ) {
			Viseg[i >> 1] = true, -- d[v = Graph[i].To], -- d[u];
			FindEuler ( v );
		}
	}
	Ans.push_back ( u );
}

inline void Print ( const int l, const int r ) { // 输出Ans数组中下标在[l, r)间的结点连边. 
	for ( Int i = l; i ^ r; ++ i ) {
		for ( Int j = Head[Ans[i]]; j; j = Graph[j]._nxt ) {
			if ( ! Outputed[j >> 1] && j >> 1 <= m && Ans[i + 1] == Graph[j].To ) { // 注意判断是否是加上的边或走过的边. 
				if ( i ^ l ) putchar ( ' ' );
				Outputed[j >> 1] = true;
				printf ( "%d", j >> 1 );
				break;
			}
		}
	}
	puts ( "" );
}

inline void Work () {
	scanf ( "%d", &m );
	for ( Int i = 1, u, v; i <= m; ++ i ) {
		scanf ( "%d %d", &u, &v );
		IsID[u] = IsID[v] = true;
		Link ( u, v ), Link ( v, u ); // 不要习惯性忽略自环. 
		++ d[u], ++ d[v];
	}
	for ( Int i = 1; i <= MAXN; ++ i ) {
		if ( IsID[i] && ! Visnd[i] ) {
			++ Unic;
			MarkUnicom ( i );
		}
	}
	if ( OddCnt > 4 || Unic > 2 ) {
		puts ( "-1" );
		return ;
	}
	if ( Unic == 1 ) { // 只有一个联通块. 
		int ond1 = 0, ond2 = 0, st = 0; // 对于四个奇度点, ond1和ond2是新边的端点, st是欧拉路径的起点. 
		if ( ! OddCnt ) { // 无奇度点. 
			for ( Int i = 1; i <= MAXN; ++ i ) {
				if ( IsID[i] ) {
					FindEuler ( i );
					break;
				}
			}
		} else if ( OddCnt == 2 ) { // 一个奇度点. 
			for ( Int i = 1; i <= MAXN; ++ i ) {
				if ( IsID[i] && d[i] & 1 ) {
					FindEuler ( i );
					break;
				}
			}
		} else { // 两个奇度点. 
			for ( Int i = 1; i <= MAXN && ! st; ++ i ) { // 先找到三个奇度点. 
				if ( IsID[i] && d[i] & 1 ) {
					if ( ! ond1 ) {
						ond1 = i;
					} else if ( ! ond2 ) {
						ond2 = i;
					} else {
						st = i;
					}
				}
			}
			Link ( ond1, ond2 ), Link ( ond2, ond1 );
			++ d[ond1], ++ d[ond2];
			FindEuler ( st ); // 连边, 并从另一个奇度点找欧拉路经. 
		}
		if ( OddCnt ^ 4 ) { 
			if ( Ans.size () <= 2 ) {
				puts ( "-1" );
				return ;
			}
//			printf ( "%d\n%d\n%u\n", 1, Ans[0], Ans.size () - 1 );
			printf ( "%d\n", 1 ); // 第一条边单独输出. 
			Print ( 0, 1 );
			printf ( "%d\n", ( int ) Ans.size () - 2 ); // 输出其余边. 
			Print ( 1, Ans.size () );
		} else {
			int _pre = 0;
//			printf ( "###%d %d\n", ond1, ond2 );
//			for ( int k: Ans ) { printf ( "### %d\n", k ); }
			for ( unsigned int i = 0; i ^ Ans.size (); ++ i ) {
				if ( ( _pre == ond1 && Ans[i] == ond2 ) || ( _pre == ond2 && Ans[i] == ond1 ) ) { // 是新边. 
					printf ( "%d\n", i - 1 );
					Print ( 0, i - 1 );
					printf ( "%d\n", m - i + 1 );
					Print ( i, Ans.size () );
					break; // 如果有与新边等价的边, 会在输出时判断, 不影响答案. 
				}
				_pre = Ans[i];
			}
		}
	} else {
		if ( UnicOdd[1] > 2 || UnicOdd[2] > 2 ) {
			puts ( "-1" );
			return ;
		}
		int VisUnic = 0;
		for ( Int i = 1; i <= MAXN; ++ i ) {
			if ( IsID[i] && ( ! VisUnic || Visnd[i] ^ VisUnic ) && bool ( UnicOdd[Visnd[i]] ) == ( d[i] & 1 ) ) {
				// 如果该连通块奇度点个数不为一, 则必须从奇度点出发. 
				FindEuler ( i );
				printf ( "%d\n", ( int ) Ans.size () - 1 );
				Print ( 0, Ans.size () );
				Ans.clear ();
				if ( VisUnic ) break;
				VisUnic = Visnd[i];
			}
		}
	}
}

int main () {
	freopen ( "input.txt", "r", stdin );
	freopen ( "output.txt", "w", stdout ); // 鬼畜的CF需要freopen ??? 
	Work ();
	return 0;
}
```

---

## 作者：i207M (赞：2)

## 题意

给定一张无向图，求出用两条欧拉路覆盖所有边的方案

## 实现

![](https://cdn.luogu.com.cn/upload/pic/22683.png)

## 注意

可能一个联通块内没有奇度数点，需要特判；

## 蒟蒻的代码

记得freopen

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define gc getchar
#define pb push_back
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
#define N 20010
#define M N<<1
int n, m;
int v[M], u[M], nx[M];
int cnt = 1, head[N];
il void add(int uu, int vv) {
    u[++cnt] = uu, v[cnt] = vv, nx[cnt] = head[uu];
    head[uu] = cnt;
}
int eda[M], edb[M], te, ui[M];
il int getn(int x) {
    return lower_bound(ui + 1, ui + 1 + n, x) - ui;
}
bool vis[N];
vector<int>po[3];
int du[N];
void dfs(int x, int k) {
    vis[x] = 1;
    //printf("V %d\n",x);
    if (du[x] & 1) {
        po[k].pb(x);
    }
    for (ri i = head[x]; i; i = nx[i]) {
        if (vis[v[i]]) continue;
        dfs(v[i], k);
    }
}
int lt;
il void no() {
    puts("-1");
    exit(0);
}
int hvf;
bool us[M];
int s[M], top;
int cut; // del
void dfs2(int x) {
    //vis[x]=1;
    for (ri i = head[x]; i; i = nx[i]) {
        //if(vis[x])
        if (us[i >> 1]) continue;
        us[i >> 1] = 1;
        dfs2(v[i]);
        s[++top] = i >> 1;
        if (((i >> 1) == (cnt >> 1)) && hvf) cut = top;
    }
}
int lt2s;
signed main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    in(m);
    for (ri i = 1, a, b; i <= m; ++i) {
        in(a), in(b);
        eda[i] = a;
        edb[i] = b;
        ui[++te] = a, ui[++te] = b;
    }
    if (m == 1) no();
    sort(ui + 1, ui + 1 + te);
    n = unique(ui + 1, ui + 1 + te) - ui - 1; // may bug
    for (ri i = 1, a, b; i <= m; ++i) {
        add(a = getn(eda[i]), b = getn(edb[i]));
        add(b, a);
        //printf("A %d %d\n",a,b);
        du[a]++, du[b]++;
    }
    for (ri i = 1; i <= n; ++i) {
        if (!vis[i]) {
            lt++;
            if (lt > 2) {
                //cout<<"E"<<i<<endl;;
                no();
            }
            if (hvf) {
                //cout<<"D";
                no();
            }
            dfs(i, lt);
            if (po[lt].size() > 4) {
                //cout<<"C";
                no();
            }
            else if (po[lt].size() == 4) {
                if (lt > 1) {
                    //cout<<"B";
                    no();
                }
                hvf = lt;
            }
            if (lt == 2 && po[2].size() == 0) lt2s = i;
        }
    }
    //cout<<lt;
    mem0(vis);
    if (hvf) {
        add(po[1][0], po[1][1]);
        add(po[1][1], po[1][0]);
        ++m;
        dfs2(po[1][2]);
        if (top != m) no();
        printf("%d\n", cut - 1);
        for (ri i = 1; i < cut; ++i) printf("%d ", s[i]);
        printf("\n%d\n", m - cut);
        for (ri i = cut + 1; i <= top; ++i) printf("%d ", s[i]);
    }
    else {
        if (po[1].size()) dfs2(po[1][0]);
        else dfs2(1);
        if (lt == 2) {
            //cout<<"A";
            cut = top;
            if (po[2].size()) dfs2(po[2][0]);
            else dfs2(lt2s);
            if (top != m) no();
            printf("%d\n", cut);
            for (ri i = 1; i <= cut; ++i) printf("%d ", s[i]);
            printf("\n%d\n", m - cut);
            for (ri i = cut + 1; i <= top; ++i) printf("%d ", s[i]);
        }
        else {
            if (top != m) no();
            printf("%d\n", 1);
            printf("%d ", s[1]);
            printf("\n%d\n", m - 1);
            for (ri i = 2; i <= top; ++i) printf("%d ", s[i]);
        }
    }
    return 0;
}

```

---

## 作者：Chillturtle (赞：2)

# 写在前面的话

也许是本人太蒟了。本人认为本题的代码难度远高于 [CF508D](https://www.luogu.com.cn/problem/CF508D)，但是 CF 的评分只差了 100 分（喜。

# 题意

翻译说得很清楚，这里再重复一下。

给你一张无向图，不保证连通以及可能有重边。让你求两条路径，使其正好能够覆盖所有的边，按边的编号输出答案。

# 思路

首先。这道题与 [CF508D](https://www.luogu.com.cn/problem/CF508D) 的不同点在于这道题要求的是两条路径。于是我们尝试分类讨论。

因为不保证连通。我们首先知道，如果连通块的数量是 1 或者 2 的时候都有解。为什么？这个很显然，如果有大于两个的连通块。那么一定不存在两条路径能够覆盖掉所有的点。于是连通块数量大于 2 时我们可以直接把这个图 ban 掉。

好的现在我们来看连通块为 1 的情况。因为我们要求的路径相当于就是一个欧拉路径。所以在连通块为 1 的情况下度数为奇数的个数就只可能是 0，2 或者 4。其中呢 0 和 2 都比较好处理。只要当路径长度比 2 大就一定可以分成两坨。但是呢 4 就需要想一想了。这里提供一种蒟蒻的想法：我们找到两个没有连边的奇点将它们之间连上一条虚边（不是重链剖分里的那个捏）。跑一遍欧拉路径，然后再把那条虚边给删掉。得到的两个部分就是我们所求的，这里给出一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9z3nv147.png)

输入数据：

```
5
1 2 
1 4 
1 3
1 5
3 6
```

这里我连上了 5 与 6 之间的边。再删掉再删掉红色的边，就得到了点集为 $[1,4,5]$ 与 $[1,2,3,6]$ 的答案。

连通块为 1 的情况看完了。现在来研究连通块数量为 2 的。显然只有在两个连通块的奇点个数都为 0 或者都为 2 时才是有解的。如果有解直接各找一个欧拉路径就可以啦。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace WYL{
	const int N=1e5+10;
	int n,to[N],nxt[N],head[N],tot,du[N],kid[N],kcnt,kminn[N];
	bool mark[N],vis[N];
	vector<int> jidian,path,jidian1,jidian2,path1,path2;
	void add(int u,int v){
		nxt[++tot]=head[u];
		head[u]=tot;
		to[tot]=v;
		return;
	}
	void dfs(int id,int k){
		kid[id]=k;
		for(int i=head[id];i;i=nxt[i]){
			if(kid[to[i]]==0&&du[to[i]]!=0){
				dfs(to[i],k);
			}
		}
		return;
	}
	int find_edge(int x,int y){
		for(int i=head[x];i;i=nxt[i]){
			if(to[i]==y&&!mark[(i+1)/2]){
				return i;
			}
		}
		return -1;
	}
	void Euler(int u,vector<int> &tmp){
		if(du[u]==0){
			tmp.push_back(u); 
			return;
		}
		for(int i=head[u];i;i=nxt[i]){
			// cout<<u<<"->"<<to[i]<<endl;
			if(vis[(i+1)/2]){
				continue;
			}
			vis[(i+1)/2]=true;
			du[to[i]]--;
			du[u]--;
			// cout<<"***"<<u<<"->"<<to[i]<<endl;
			Euler(to[i],tmp);
		}
		tmp.push_back(u);
		return;
	}
	void solve(int l,int r,vector<int> path){
		for(int i=l;i<=r;i++){
			int opt=(find_edge(path[i],path[i+1])+1)/2;
			cout<<opt<<" ";
			mark[opt]=true;
		}
		return;
	}
	int main(){
		cin>>n;
		if(n==1){
			cout<<"-1"<<endl;
			return 0;
		}
		for(int i=1;i<=n;i++){
			int x,y;
			cin>>x>>y;
			du[x]++;
			du[y]++;
			add(x,y);
			add(y,x);
		}
		for(int i=1;i<=10005;i++){
			if(du[i]&&kid[i]==0){
				kminn[kcnt+1]=i;
				dfs(i,++kcnt);
			}
			if(du[i]%2==1){
				jidian.push_back(i);
			}
		}
		if(kcnt>2){
			cout<<"-1"<<endl;
			return 0;
		}
		if(kcnt==1){
			if(jidian.size()==4){
				for(int i=0;i<4;i++){
					for(int j=i+1;j<4;j++){
						if(find_edge(jidian[i],jidian[j])!=-1){
							continue;
						}
						swap(jidian[0],jidian[i]);
						swap(jidian[1],jidian[j]);
						goto end;
					}
				}
				end:
				int x=jidian[0],y=jidian[1];
				du[x]++;
				du[y]++;
				add(x,y);
				add(y,x);
				memset(vis,0,sizeof(vis));
				Euler(jidian[2],path);
				int place=0;
				while((path[place]!=jidian[0]||path[place+1]!=jidian[1])&&(path[place]!=jidian[1]||path[place+1]!=jidian[0])){
					place++;
				}
				cout<<place<<endl;
				solve(0,place-1,path);
				cout<<endl;
				cout<<n-place<<endl;
				solve(place+1,path.size()-2,path);
				return 0;
			}else{
				path.clear();
				if(jidian.size()!=0&&jidian.size()!=2){
					cout<<"-1"<<endl;
					return 0;
				}
				if(jidian.size()==0){
					Euler(kminn[1],path);
				}else if(jidian.size()==2){
					Euler(jidian[0],path);
				}
				cout<<"1"<<endl;
				solve(0,0,path);
				cout<<endl;
				cout<<path.size()-2<<endl;
				solve(1,path.size()-2,path);
				return 0;
			}
		}else if(kcnt==2){
			for(int i=0;i<jidian.size();i++){
				if(kid[jidian[i]]==1){
					jidian1.push_back(jidian[i]);
				}else{
					jidian2.push_back(jidian[i]);
				}
			}
			if(jidian1.size()!=0&&jidian1.size()!=2){
				cout<<"-1"<<endl;
				return 0;
			}
			if(jidian2.size()!=0&&jidian2.size()!=2){
				cout<<"-1"<<endl;
				return 0;
			}
			path1.clear();path2.clear();
			if(jidian1.size()==0){
				int place=1;
				while(kid[place]!=1){
					place++;
				}
				Euler(place,path1);
			}else{
				Euler(jidian1[0],path1);
			}
			cout<<path1.size()-1<<endl;
			solve(0,path1.size()-2,path1);
			cout<<endl;
			if(jidian2.size()==0){
				int place=1;
				while(kid[place]!=2){
					place++;
				}
				Euler(place,path2);
			}else{
				Euler(jidian2[0],path2);
			}
			cout<<path2.size()-1<<endl;
			solve(0,path2.size()-2,path2);
			return 0;
		}
		return 0;
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	WYL::main();
	return 0;
}
/*
 10
 7 4
 7 4
 6 1
 2 3
 2 1
 1 6
 4 2
 8 4
 4 8
 3 5
*/
```

---

## 作者：ThisIsLu (赞：1)

既然有两条路径，则这个图必然是两个半欧拉图合并在一起，所以奇点数最大为 $4$，连通块数最大为 $2$。

然后分情况讨论：

- 1.有两个联通块：分别判断是否是半欧拉图，直接跑欧拉路就行了。

- 2.有一个联通块：在这种情况下，又分为两种情况：
  - 一、奇点数小于 $4$：这种直接跑欧拉路，将最后一条边拆出来即可（注意如果只有一条边则不可行）。
  - 二、奇点数等于 $4$：在两个奇点之间建虚边，跑欧拉路，再根据虚边把路径拆成两段。因为有 $4$ 个奇点，能保证两条路径长度大于 $0$。
  
放上恶臭的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1e4;
struct edge{
    int v,nxt,id;
    edge(){
        v=0,nxt=0;
        id=0;
    }
    edge(int v,int nxt,int id):v(v),nxt(nxt),id(id){}
} e[N*2+5];
int head[N+5],cnt;
int mp[N+5];
void add(int u,int v,int id){
    e[++cnt]=edge(v,head[u],id);
    head[u]=cnt;
}
bool cis[N+5];
bool vis[N+5];
int tail,ans[N+5];
void dfs(int u){
    for(int i=head[u];i;i=e[i].nxt){
        if(!vis[(i+1)>>1]){
            vis[(i+1)>>1]=true;
            dfs(e[i].v);
        }
    }
    ans[++tail]=u;
}
bool ii[N+5];
void euler(int u){
    for(int i=1;i<=m+1;i++) ii[i]=false;
    dfs(u);
    for(int i=tail;i>=2;i--){
        for(int j=head[ans[i]];j;j=e[j].nxt){
            int v=e[j].v;
            if(v==ans[i-1]&&!ii[e[j].id]){
                ii[e[j].id]=true;
                ans[i]=e[j].id;
                break;
            }
        }
    }
    for(int i=1;i<tail;i++){
        ans[i]=ans[i+1];
    }
    tail--;
}
int dep[N+5],opo[N+5][4],lllp[N+5];
int dfs(int u,int id){
    cis[u]=true;
    if(dep[u]){
        if(lllp[id]<4){
            opo[id][++lllp[id]]=u;
        }
    }
    int res=dep[u];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(cis[v]) continue;
        res+=dfs(v,id);
    }
    return res;
}
int lcnt,pops[N+5],ll[N+5];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(mp[u]) u=mp[u];
        else u=mp[u]=++n;
        if(mp[v]) v=mp[v];
        else v=mp[v]=++n;
        add(u,v,i);
        add(v,u,i);
        dep[u]^=1;
        dep[v]^=1;
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        if(!cis[i]){
            lcnt++;
            opo[lcnt][1]=i;
            pops[lcnt]=dfs(i,lcnt);
            ll[lcnt]=i;
            sum+=pops[lcnt];
        }
    }
    if(sum>4||lcnt>2){
        cout<<"-1";
        return 0;
    }
    if(lcnt==2){
        if(pops[1]<=2&&pops[2]<=2){
            euler(opo[1][1]);
            cout<<tail<<"\n";
            for(int i=tail;i>=1;i--) cout<<ans[i]<<" ";
            tail=0;
            euler(opo[2][1]);
            cout<<"\n"<<tail<<"\n";
            for(int i=tail;i>=1;i--) cout<<ans[i]<<" ";
        }
        else cout<<"-1";
    }
    else{
        if(pops[1]<=2){
            euler(opo[1][1]);
            if(m==1){
                cout<<"-1";
                return 0;
            }
            cout<<tail-1<<"\n";
            for(int i=tail;i>=2;i--) cout<<ans[i]<<" ";
            cout<<"\n1\n";
            cout<<ans[1];
        }
        else{
            add(opo[1][1],opo[1][2],m+1);
            add(opo[1][2],opo[1][1],m+1);
            euler(opo[1][3]);
            int pos=0;
            for(int i=tail;i>=1;i--){
                if(ans[i]==m+1){
                    pos=i;
                    break;
                }
            }
            cout<<tail-pos<<"\n";
            for(int i=tail;i>pos;i--){
                cout<<ans[i]<<" ";
            }
            cout<<"\n"<<pos-1<<"\n";
            for(int i=pos-1;i>=1;i--){
                cout<<ans[i]<<" ";
            }
        }
    }
    return 0;
}
```

---

## 作者：⚡凌熙墨⚡ (赞：1)

首先，覆盖所有边恰一次，妥妥的欧拉路模型。

然后就先考虑如何判无解了。怎样无解呢？

1. 有少于$ 2 $条边。（如果不是样例给了，大概很难注意到……）

1. 有超过$ 2 $个连通块。

1. 仅有一个连通块，且连通块中奇点数大于$ 4$。

1. 有两个连通块，且其中某一个块中奇点数大于$ 2$。

那么，是否所有条件都满足，就一定有解呢？

是的。

假如从**欧拉路**的方向考虑，就会非常麻烦，因为你找出的欧拉回路删去后可能使得这张图分成许多不连通的图。

因此，这里有一个很好的思路：在两个奇点间连边，这样就会转换为**欧拉回路**，然后在欧拉回路上断去新加的边就行了。

具体而言，对于两个连通块的情形，显然上述结论正确，因为每个连通块都必然符合条件。

然后，对于仅有一个连通块的情形，其中可能有$ 0 $个，$2$ 个或是 $4$ 个奇点。

$0$ 个奇点就搜出回路然后随便砍两刀断环成链即可。

$2$ 个奇点就在额外连的那条边处砍一刀，然后再随便砍一刀就行。

$4$ 个奇点这两刀必须砍在额外的两条边的位置。这形成的两条链必然非空，因为这两条新边必然无公共端点，即其在欧拉环上必然不相邻。

时间复杂度 $O(m)$。

---

## 作者：喵仔牛奶 (赞：0)

分讨看似多，但是非常好写，半小时就写完了。这篇题解有代码解析。

## Solution

### 思路

显然，如果连通块大于 $3$ 个无解。如果连通块有两个，则每个都有一条欧拉路，可以简单找到。

接下来考虑奇点个数：
- $0/2$ 个：跑出欧拉路，如果长度 $<2$ 无解，否则把第一条边变成单独的路，剩下的作为另一条路。
- $4$ 个：很高明的一种做法是，将其中两个点连一条虚边，跑出欧拉路，然后从虚边断成两条即可。

复杂度线性，我来讲讲实现。

### 实现

首先定义变量、写出找连通块函数、找欧拉路函数。这题有多种情况，再写一个 `prt` 函数来输出路径。
```cpp
int n, m, x, y, dg[N], vs[N], ve[N], rd[N];
vector<pii> G[N]; vector<int> s;
void dfs1(int x, int c) {
  vs[x] = c;
  for (auto [y, i] : G[x])
    if (!vs[y]) dfs1(y, c);
}
void dfs2(int x, vector<int> &s) {
  vs[x] = 1;
  for (int &i = rd[x]; i < SZ(G[x]); ) {
    auto [y, t] = G[x][i ++];
    if (!ve[t]) ve[t] = 1, dfs2(y, s), s.pb(t); 
  }
}
void prt(vector<int> &s) {
	cout << SZ(s) << '\n';
	for (int x : s) cout << x << ' ';
	cout << '\n';
}
```

输入、找连通块：
```cpp
cinn >> m;
REP(i, 1, m) {
	cin >> x >> y, n = max({n, x, y});
	dg[x] ++, dg[y] ++, G[x].pb(y, i), G[y].pb(x, i);
}
int blk = 0; vector<int> od; // od 存奇点
REP(i, 1, n) {
	if (dg[i] & 1) od.pb(i);
	if (dg[i] && !vs[i]) dfs1(i, ++ blk);
}
if (blk > 2) { cout << "-1\n"; return 0; }
```

如果有两个连通块：
```cpp
if (blk == 2) {
	int p = 0, q = 0;
	REP(i, 1, n) {
		if (!vs[i]) continue;
		(vs[i] == 1 ? p : q) += (dg[i] & 1);
	}
	if (p > 2 || q > 2 || (p & 1) || (q & 1)) { cout << "-1\n"; return 0; }
	p = -1, q = -1;
	REP(i, 1, n) {
		if (vs[i] == 1 && (p < 0 || dg[i] & 1)) p = i;
		if (vs[i] == 2 && (q < 0 || dg[i] & 1)) q = i;
	} // p,q 是奇点，如果没有奇点随便找一个点
	dfs2(p, s), prt(s), s.clear();
	dfs2(q, s), prt(s);
	return 0;
}
```

如果有四个奇点，连虚边：
```cpp
int p = -1, chk = 0; // chk 表示是否有四个奇点
if (SZ(od) > 4 || (SZ(od) & 1)) { cout << "-1\n"; return 0; }
if (SZ(od) == 4) {
	int x = od[2], y = od[3];
	G[x].pb(y, ++ m), G[y].pb(x, m), dg[x] ++, dg[y] ++;
	od.pop_back(), od.pop_back(), chk = 1;
}
```

最后一步，跑出欧拉路，然后分割路径：
```cpp
REP(i, 1, n)
	if (vs[i] && (p < 0 || dg[i] & 1)) p = i;
dfs2(p, s);
if (chk) {
	vector<int> S, T; int i = 0;
	for (; s[i] != m; i ++) S.pb(s[i]);
	for (i ++; i < SZ(s); i ++) T.pb(s[i]);
	if (!SZ(S) || !SZ(T)) { cout << "-1\n"; return 0; }
	prt(S), prt(T);
} else {
	if (SZ(s) < 2) { cout << "-1\n"; return 0; }
	vector<int> t; t.pb(s.back()), s.pop_back();
	prt(s), prt(t);
}
```

然后就写完了~~

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, m, x, y, dg[N], vs[N], ve[N], rd[N];
	vector<pii> G[N]; vector<int> s;
	void dfs1(int x, int c) {
		vs[x] = c;
		for (auto [y, i] : G[x])
			if (!vs[y]) dfs1(y, c);
	}
	void dfs2(int x, vector<int> &s) {
		vs[x] = 1;
		for (int &i = rd[x]; i < SZ(G[x]); ) {
			auto [y, t] = G[x][i ++];
			if (!ve[t]) ve[t] = 1, dfs2(y, s), s.pb(t); 
		}
	}
	void prt(vector<int> &s) {
		cout << SZ(s) << '\n', reverse(ALL(s));
		for (int x : s) cout << x << ' ';
		cout << '\n';
	}
 	int main() {
		cin >> m;
		REP(i, 1, m) {
			cin >> x >> y, n = max({n, x, y});
			dg[x] ++, dg[y] ++, G[x].pb(y, i), G[y].pb(x, i);
		}
		int blk = 0; vector<int> od;
		REP(i, 1, n) {
			if (dg[i] & 1) od.pb(i);
			if (dg[i] && !vs[i]) dfs1(i, ++ blk);
		}
		if (blk > 2) { cout << "-1\n"; return 0; }
		if (blk == 2) {
			int p = 0, q = 0;
			REP(i, 1, n) {
				if (!vs[i]) continue;
				(vs[i] == 1 ? p : q) += (dg[i] & 1);
			}
			if (p > 2 || q > 2 || (p & 1) || (q & 1)) { cout << "-1\n"; return 0; }
			p = -1, q = -1;
			REP(i, 1, n) {
				if (vs[i] == 1 && (p < 0 || dg[i] & 1)) p = i;
				if (vs[i] == 2 && (q < 0 || dg[i] & 1)) q = i;
			}
			dfs2(p, s), prt(s), s.clear();
			dfs2(q, s), prt(s);
			return 0;
		}
		int p = -1, chk = 0;
		if (SZ(od) > 4 || (SZ(od) & 1)) { cout << "-1\n"; return 0; }
		if (SZ(od) == 4) {
			int x = od[2], y = od[3];
			G[x].pb(y, ++ m), G[y].pb(x, m), dg[x] ++, dg[y] ++;
			od.pop_back(), od.pop_back(), chk = 1;
		}
		REP(i, 1, n)
			if (vs[i] && (p < 0 || dg[i] & 1)) p = i;
		dfs2(p, s);
		if (chk) {
			vector<int> S, T; int i = 0;
			for (; s[i] != m; i ++) S.pb(s[i]);
			for (i ++; i < SZ(s); i ++) T.pb(s[i]);
			if (!SZ(S) || !SZ(T)) { cout << "-1\n"; return 0; }
			prt(S), prt(T);
		} else {
			if (SZ(s) < 2) { cout << "-1\n"; return 0; }
			vector<int> t; t.pb(s.back()), s.pop_back();
			prt(s), prt(t);
		}
		return 0;
	}
}
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~超简单的图论题~~！

------------
这道题其实说实话，难度在 CF 中已经算高的了，本人实力有限，部分讲解参考[大佬讲解](https://www.tinymind.net.cn/articles/c0bc5823a0c666)。

------------


## 大致思路：
这道题运用到了欧拉回路的一个经典算法——Hierholzer 算法~~说白了就是小学奥数的一笔画问题~~，就是找 $cnt$（存奇数度点的个数的数组），然后判断是否为 $2$ 或者别的偶数，从中选取 $2$ 个点，跑 dfs 递归找点，最终将答案倒序输出就是**最终结果**（模板上是这样写的）。


------------
## 具体步骤：
1. 输入数据，用 $mp$ 数组存点，然后用 $deg$ 数组存入**每个点**的**入度**与**出度**。


2. 用 $O(n)$ 循环并用 $cnt$ 记录**奇点**数量，同时用 $q$ 数组记录**每个奇点的下标**。


3. 当 $cnt$ 变量为 $2$ 时，直接用 $q$ 数组记录的数据跑 dfs 递归一笔画，直接得出结果，但是前提是这个点没有被用过，就是 $vis$ 数组的这个点为 $0$。


4. 当 $cnt$ 变量为 $4$ 时，就全部~~狂奔~~跑一遍 dfs。然而，一个连通块、$4$ 个奇度数点的情况是在**两个奇度数点**之间连一条边，**跑完欧拉路**后**再断开**！


5. 最后就是输出，输出其实就是先输出两条路径的边数（其实可以改为计算点的数量减去 $1$），然后将原先的点换成边的编号进行输出~~真是麻烦~~。

------------


## 警钟敲烂：
不要直接套模板！！！

不要直接套模板！！！

不要直接套模板！！！

这道题要对模板~~进行外科手术~~大改！！！

------------


## 代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, mp[N], head[N], cjdsum, deg[N], col[N], jdsum;
int sta[N], top, q[N], judge, ct1;
bool use[N], vis[N];
struct Ed
{
    int nxt, to, val;
    Ed(int n = 0, int t = 0, int b = 0) : nxt(n), to(t), val(b) {}
} edge[N << 1];
void add(int u, int v, int w)
{
    edge[++cjdsum].to = v;
    edge[cjdsum].val = w;
    edge[cjdsum].nxt = head[u];
    head[u] = cjdsum;
    edge[++cjdsum].to = u;
    edge[cjdsum].val = w;
    edge[cjdsum].nxt = head[v];
    head[v] = cjdsum;
}
void dfs(int cr)
{
    col[cr] = jdsum;
    if (deg[cr] & 1)
    {
        q[++judge] = cr;
    }
    for (int i = head[cr]; i; i = edge[i].nxt)
    {
        if (!col[edge[i].to])
        {
            dfs(edge[i].to);
        }
    }
}
void dfs(int rt, int cr, int fa)
{
    vis[cr] = 1;
    for (int i = head[cr]; i; i = edge[i].nxt)
    {
        if (!use[edge[i].val])
        {
            use[edge[i].val] = 1;
            dfs(rt, edge[i].to, cr);
            sta[++top] = edge[i].val;
            if (edge[i].val == m + 1)
            {
                ct1 = --top;
            }
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    m = read();
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        x = read();
        y = read();
        if (!mp[x])
        {
            mp[x] = ++n;
        }
        if (!mp[y])
        {
            mp[y] = ++n;
        }
        deg[mp[x]]++;
        deg[mp[y]]++;
        add(mp[x], mp[y], i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!col[i])
        {
            jdsum++;
            dfs(i);
        }
    }
    if (jdsum > 2 || judge > 4 || m == 1)
    {
        cout << -1 << endl;
        return 0;
    }
    if (jdsum == 2 && judge == 4 && col[q[1]] == col[q[2]] == col[q[3]] == col[q[4]])
    {
        cout << -1 << endl;
        return 0;
    }
    memset(vis, 0, sizeof vis);
    if (jdsum == 2)
    {
        if (judge)
        {
            dfs(q[1], q[1], 0);
            ct1 = top;
            if (judge == 2)
            {
                for (int i = 1; i <= n; i++)
                {
                    if (!vis[i])
                    {
                        dfs(i, i, 0);
                        break;
                    }
                }
            }
            else
            {
                for (int i = 1; i <= 4; i++)
                {
                    if (!vis[q[i]])
                    {
                        dfs(q[i], q[i], 0);
                        break;
                    }
                }
            }
        }
        else
        {
            dfs(1, 1, 0);
            ct1 = top;
            for (int i = 1; i <= n; i++)
            {
                if (!vis[i])
                {
                    dfs(i, i, 0);
                    break;
                }
            }
        }
    }
    else
    {
        if (judge)
        {
            if (judge == 4)
            {
                add(q[3], q[4], m + 1);
                dfs(q[1], q[1], 0);
            }
            else
            {
                dfs(q[1], q[1], 0), ct1 = top;
            }
        }
        else
        {
            ct1 = m, dfs(1, 1, 0);
        }
    }
    if (top != m)
    {
        cout << -1;
        return 0;
    } 
    if (ct1 == top)
    {
        cout << 1 << endl << sta[top] << endl;
        cout << ct1 - 1 << endl;
        for (int i = top - 1; i; i--)
        {
            cout << sta[i] << ' ';
        }
        return 0;
    }
    cout << ct1 << '\n';
    for (int i = ct1; i; i--)
    {
        cout << sta[i] << ' ';
    }
    cout << endl;
    cout << top - ct1 << endl;
    for (int i = top; i > ct1; i--)
    {
        cout << sta[i] << ' ';
    }
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/120578281)




---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/notes-EulerPath) & [Problem](//www.luogu.com.cn/problem/CF36E)

## 题目大意

- 给定一个有 $m$ 条无向边，至多有 $10^4$ 个点，可能有重边，不保证联通的图，请在这个图上找出两条路径，使得这两条路径覆盖了图中每一条边仅一次。

- $1\leq m\leq 10^4$

## 解题思路

两条路径产生的奇点数为 $0$ 或 $2$，则两条路径产生的奇点数只能为 $0,\ 2$ 或 $4$。

此外，如果我们能找到一条路径覆盖图中每一条边仅一次，那么只需将这条路径从一个断点处断开即可。

对整个图的连通块数量与奇点数量分类讨论。

- 若整个图连通，

  - 奇点数为 $0$ 或 $2$，则必能找到一条路径覆盖图中每一条边仅一次。此时只需路径长度 $\geq 2$，就可以将其分为两条路径；
  
  - 奇点数为 $4$，此时任取两个没有连边的奇点，将它们连上一条临时边。此时有 $2$ 个奇点，必能找到一条路径覆盖图中每一条边仅一次，由于临时边的端点都变成了偶点，故不可能成为这条路径的第一条边或最后一条边，也就可以从临时边处断开路径，得到答案。
  
- 若整个图分为了两个连通块，只要两个连通块奇点数均为 $0$ 或 $2$，就可以在两个连通块各找到一条路径，即为最终答案。

- 若整个图分为了三个或更多的连通块，显然无解。

由于最后输出的是边的编号，输出时需要对任意相邻两个点找到边的编号。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

void error(){
    //由于此代码用到的地方较多，故封装成一个函数
	printf("-1\n"); exit(0);
}

int n=10000,m;

struct Edge{
	int to,nxt;
}edge[20003];
int head[10001],cntEdge;
inline void addEdge(int u,int v){
	edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int deg[10001]; // 每个点的度

int blockid[10001],blockcnt,blockf[10001];
/* blockid 表示点所在的连通块编号
   blockcnt 表示连通块数目
   blockf 表示点所在连通块中编号最小的点 */
void dfs_block(int id,int block){
	blockid[id]=block;
	for(int i=head[id];i;i=edge[i].nxt)
		if(blockid[edge[i].to]==0&&deg[edge[i].to])
			dfs_block(edge[i].to,block);
}

bool used[10001]; // 这个边输出答案时是否被使用过，可以避免重边情况
int findedge(int u,int v){
    // 找到 u 和 v 之间的边
	for(int i=head[u];i;i=edge[i].nxt)
		if(edge[i].to==v&&!used[i+1>>1])return i;
	return -1;
}

bool vis[10002];
void dfs(int id,vector<int> &tmp){
    // 找欧拉路径，答案存储在 tmp 里
	if(deg[id]==0){
        // 这个点已经没有出边
		tmp.push_back(id); return;
	}
	for(int i=head[id];i;i=edge[i].nxt){
		if(vis[i+1>>1])continue;
		vis[i+1>>1]=true; // 标记走过的边
		deg[edge[i].to]--,deg[id]--;
		dfs(edge[i].to,tmp);
	}
	tmp.push_back(id);
}

void print(vector<int> answer,int l,int r){
	for(int i=l;i<=r;i++){
		int tmp=findedge(answer[i],answer[i+1])+1>>1;
		printf("%d ",tmp),used[tmp]=true;
	}
	printf("\n");
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&m);
	if(m==1)error();
	for(int i=1;i<=m;i++){
		int u,v; scanf("%d%d",&u,&v);
		deg[u]++,deg[v]++;
		addEdge(u,v); addEdge(v,u);
	}
	vector<int>oddid;
	for(int i=1;i<=n;i++){
		if(deg[i]&&blockid[i]==0)
			blockf[blockcnt+1]=i,
			dfs_block(i,++blockcnt);
		if(deg[i]&1)oddid.push_back(i); // 找到一个奇点
	}
	if(blockcnt>2)error(); // 连通块数量超过 2，无解
	if(blockcnt==1){
		if(oddid.size()==4){
			bool flag=false; int t1=0,t2=0;
            // 找没有连边的两个奇点
			for(int i=0;i<4&&!flag;i++)
				for(int j=i+1;j<4&&!flag;j++)
					if(findedge(oddid[i],oddid[j])==-1){
						swap(oddid[0],oddid[i]);
						swap(oddid[1],oddid[j]);
						flag=true;
					}
            // 连边
			addEdge(oddid[0],oddid[1]);
			addEdge(oddid[1],oddid[0]);
			deg[oddid[0]]++,deg[oddid[1]]++;
			vector<int>tmp;
			dfs(oddid[2],tmp);
			int t=0;
            // 找到临时添加的边
			while((tmp[t]!=oddid[0]||tmp[t+1]!=oddid[1])&&
				(tmp[t]!=oddid[1]||tmp[t+1]!=oddid[0]))t++;
			printf("%d\n",t);
			print(tmp,0,t-1);
			printf("%d\n",m-t);
			print(tmp,t+1,tmp.size()-2);
		}
		else{
			vector<int>tmp;
            // 找一条路径遍历整个图
			if(oddid.size()==0)
				dfs(blockf[1],tmp);
			else if(oddid.size()==2)
				dfs(oddid[0],tmp);
			else error();
            // 断开第一条边输出
			printf("1\n");
			print(tmp,0,0);
			printf("%d\n",tmp.size()-2);
			print(tmp,1,tmp.size()-2);
		}
	}
	if(blockcnt==2){
        // 有两个连通块时，分别找路径
		vector<int>odd1,odd2;
		for(int i:oddid)
			if(blockid[i]==1)odd1.push_back(i);
			else odd2.push_back(i);
		if(odd1.size()!=0&&odd1.size()!=2)error();
		if(odd2.size()!=0&&odd2.size()!=2)error();
		vector<int>ans1,ans2;
		if(odd1.size()==0){
			int t=1;
			while(blockid[t]!=1)t++; 
			dfs(t,ans1);
		}
		else dfs(odd1[0],ans1);
		printf("%d\n",ans1.size()-1);
		print(ans1,0,ans1.size()-2);
		if(odd2.size()==0){
			int t2=1;
			while(blockid[t2]!=2)t2++; 
			dfs(t2,ans2);
		}
		else dfs(odd2[0],ans2);
		printf("%d\n",ans2.size()-1);
		print(ans2,0,ans2.size()-2);
	}
	return 0;
} 
```

---

## 作者：C20203030 (赞：0)

## 一、题目

**题目**

给你一张可能有重边的不保证联通的无向图，现在要在这个图上找出两条路径，恰好能覆盖所有边一次，根据边的编号输出方案，无解输出-1。

**数据范围**

 $1\leq m\leq 10000,1\leq a,b\leq10000 ,a\not=b$
 
## 二、解法

**思路**

由于组成欧拉路的条件较为单一，我们来分类讨论一下。

（下文将会把度为奇数的点称为奇点）

1、有一个连通块，奇点数为$0,2$，那我们随便选择一条边组成一个路径，另外的边组成另一条路径。

2、有一个连通块，奇点数为$4$，那我们将两个奇数点连一条虚边，等于将图分成两个部分，从一个奇点出发，看能不能形成一条路径(实质上是题意中的两条)。
3、有两个连通块，奇点数取$0,2$，直接跑即可。

**代码**

有很多细节没讲清楚，代码中会有详细注释。


```cpp
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
const int MAXN = 10005;
int read()
{
    int num=0,flag=1;
    char c;
    while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;
    while(c>='0'&&c<='9')num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*flag;
}
int n,m,tot,b=INF,f[MAXN],deg[MAXN],exi[MAXN],cnt,cut,tmp1,tmp2,top,s[MAXN];
vector<int> pr[3];
bool pr4,vis[MAXN],use[MAXN];
struct edge
{
	int v,next,id;
}e[MAXN*2];
void add(int u,int v,int num)
{
    e[++tot]=edge{v,f[u],num},f[u]=tot;
    e[++tot]=edge{u,f[v],num},f[v]=tot;
}
void dfs1(int u)
{
    vis[u]=1;
    if(deg[u]&1) pr[cnt].push_back(u);//把奇数点压入vector 
    for(int i=f[u];i;i=e[i].next) 
        if(!vis[e[i].v])
            dfs1(e[i].v);
}
void dfs2(int u)
{
    for(int i=f[u];i;i=e[i].next)
        if(!use[e[i].id])
        {
            use[e[i].id]=1;
            dfs2(e[i].v);
            //注意这里要倒着编号，原因是要确保顺序是连续的（自己想想吧，作者口胡解释不太清楚） 
            s[++top]=e[i].id;//将编号压入stack 
            if(e[i].id==m && pr4) cut=top;//寻找虚边在栈中的位置 
        }
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    m=read();
    for(int i=1;i<=m;i++)
    {
    	int u=read(),v=read();
    	exi[u]=exi[v]=1;
    	deg[u]++;deg[v]++;
    	add(u,v,i);
    	b=min(b,min(u,v));//编号不一定是联续的，取最小和最大编号 
    	n=max(n,max(u,v));
	}
	if(m==1) {printf("-1\n");return 0;}//特判，只有一条边 
	for(int i=b;i<=n;i++)
		if(exi[i] && !vis[i])//存在且没有被访问过 
        {
            cnt++;//连通块数++ 
            if(cnt>2) {printf("-1\n");return 0;}//有超过两个连通块，-1 
            if(pr4) {printf("-1\n");return 0;}//以前的连通块出现过四个奇点，-1 
            dfs1(i);//直接暴搜 
            if(pr[cnt].size()>4) {printf("-1\n");return 0;}//奇点数大于四个，-1 
            if(pr[cnt].size()==4) 
            {
                if(cnt>1) {printf("-1\n");return 0;}//当前大于一个连通块 
                pr4=1;//存在四个奇点 
            }
            if(cnt==1 && pr[cnt].size()==0) tmp1=i;//设置连通块访问起点 
            if(cnt==2 && pr[cnt].size()==0) tmp2=i;
        }
    if(pr4)
    {
        add(pr[1][0],pr[1][1],++m);//建虚边 
        dfs2(pr[1][2]);
        if(top^m) {printf("-1\n");return 0;}
        printf("%d\n",cut-1);//输出时去除虚边 
        for(int i=1;i<cut;i++) printf("%d ",s[i]);
        printf("\n%d\n",m-cut);
        for(int i=cut+1;i<=m;i++) printf("%d ",s[i]);
    }
    else
    {
        if(pr[1].size()) dfs2(pr[1][0]);//奇点为起点 
        else dfs2(tmp1);//没有奇点，随便找个点 
        if(cnt==2)
        {
            cut=top;
            if(pr[2].size()) dfs2(pr[2][0]);
            else dfs2(tmp2);
            if(top^m) {printf("-1\n");return 0;}
            printf("%d\n",cut);
            for(int i=1;i<=cut;i++) printf("%d ",s[i]);
            printf("\n%d\n",m-cut);
            for(int i=cut+1;i<=m;i++) printf("%d ",s[i]);
        }
        else
        {
            if(top^m) {printf("-1\n");return 0;}
            printf("1\n%d\n%d\n",s[1],m-1);
            for(int i=2;i<=m;i++) printf("%d ",s[i]);
        }
    }
}
```


---

