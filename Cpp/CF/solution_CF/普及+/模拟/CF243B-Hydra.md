# Hydra

## 题目描述

One day Petya got a birthday present from his mom: a book called "The Legends and Myths of Graph Theory". From this book Petya learned about a hydra graph.

A non-oriented graph is a hydra, if it has a structure, shown on the figure below. Namely, there are two nodes $ u $ and $ v $ connected by an edge, they are the hydra's chest and stomach, correspondingly. The chest is connected with $ h $ nodes, which are the hydra's heads. The stomach is connected with $ t $ nodes, which are the hydra's tails. Note that the hydra is a tree, consisting of $ h+t+2 $ nodes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/d6e514f088f194e43f02ecd959e99753f276fecc.png)Also, Petya's got a non-directed graph $ G $ , consisting of $ n $ nodes and $ m $ edges. Petya got this graph as a last year birthday present from his mom. Graph $ G $ contains no self-loops or multiple edges.

Now Petya wants to find a hydra in graph $ G $ . Or else, to make sure that the graph doesn't have a hydra.

## 说明/提示

The first sample is depicted on the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF243B/b7fc0e169a7806a7f3ca6b4c9c4c40eca2a230e7.png)

## 样例 #1

### 输入

```
9 12 2 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
8 7
9 1
```

### 输出

```
YES
4 1
5 6 
9 3 2 
```

## 样例 #2

### 输入

```
7 10 3 3
1 2
2 3
1 3
1 4
2 5
4 5
4 6
6 5
6 7
7 5
```

### 输出

```
NO
```

# 题解

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

首先统计出所有的点的所连接的边的数量，然后枚举链接 $u$ 和 $v$ 的那一条边，直接贪心是否可行即可。

具体的贪心思路为：枚举具体哪一个点是多头蛇的胸部，由此确定另一个点为多头蛇的腹部，这样就知道了么一个点需要取多少条边。预先判断不可行，也就是如果与某一个点的边数减一比要求的点还要小，那么一定无解。然后每一次优先取出某一个点独占的一些点，如果不够再去取两个点公用的那些点。

在预先判断完之后，如果存在一个点的边数减一要比 $h+t$ 大，则一定有解，所以可能参与多次判断的一定只有那些没有 $h+t$ 大的那些边。这样的话每一次的枚举一定不超过 $h+t$ 次，而可能的边的数量也只有 $m\le 10^5$ 条，总复杂度 $O(m(h+t))$ 完全可以接受。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=200005;
int n,m,h,t,head[MAXN],nxt[MAXN],num[MAXN],tot,st[MAXN],x[MAXN],y[MAXN];
int ans1[MAXN],ans2[MAXN],u,v,cnt1,cnt2,tt[MAXN];
void add(int x,int y){
	nxt[++tot]=head[x];head[x]=tot;num[tot]=y;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&h,&t);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x[i],&y[i]);
		tt[x[i]]++;tt[y[i]]++;
		add(x[i],y[i]);add(y[i],x[i]);
	}
	for(int i=1;i<=n;i++)tt[i]--;
	for(int l=1;l<=m;l++){
		if(tt[x[l]]<h||tt[y[l]]<t)continue;
		cnt1=cnt2=0;
		for(int i=head[x[l]];i;i=nxt[i])if(num[i]!=y[l])st[num[i]]++;
		for(int i=head[y[l]];i;i=nxt[i])if(num[i]!=x[l])st[num[i]]++;
		cnt1=cnt2=0;
		
		for(int i=head[x[l]];i;i=nxt[i]){
			if(st[num[i]]==1)ans1[++cnt1]=num[i];
			if(cnt1>=h)break;	
		}
		for(int i=head[x[l]];i;i=nxt[i]){
			if(st[num[i]]==2&&cnt1<h)ans1[++cnt1]=num[i],st[num[i]]=3;
			if(cnt1>=h)break;
		}
		
		for(int i=head[y[l]];i;i=nxt[i]){
			if(st[num[i]]==1)ans2[++cnt2]=num[i];
			if(cnt2>=t)break;
		}
		for(int i=head[y[l]];i;i=nxt[i]){
			if(st[num[i]]==2&&cnt2<t)ans2[++cnt2]=num[i],st[num[i]]=3;
			if(cnt2>=t)break;
		}
		
		if(cnt1>=h&&cnt2>=t){
			printf("YES\n");
			printf("%d %d\n",x[l],y[l]);
			for(int i=1;i<=h;i++)printf("%d ",ans1[i]);printf("\n");
			for(int i=1;i<=t;i++)printf("%d ",ans2[i]);printf("\n");
			return 0;
		}
		
		for(int i=head[x[l]];i;i=nxt[i])st[num[i]]=0;
		for(int i=head[y[l]];i;i=nxt[i])st[num[i]]=0;
	}
	
	for(int l=1;l<=m;l++){
		cnt1=cnt2=0;
		if(tt[x[l]]<t||tt[y[l]]<h)continue;
		for(int i=head[x[l]];i;i=nxt[i])if(num[i]!=y[l])st[num[i]]++;
		for(int i=head[y[l]];i;i=nxt[i])if(num[i]!=x[l])st[num[i]]++;
		cnt1=cnt2=0;
		
		for(int i=head[x[l]];i;i=nxt[i]){
			if(st[num[i]]==1)ans1[++cnt1]=num[i];
			if(cnt1>=t)break;	
		}
		for(int i=head[x[l]];i;i=nxt[i]){
			if(st[num[i]]==2&&cnt1<t)ans1[++cnt1]=num[i],st[num[i]]=3;
			if(cnt1>=t)break;
		}
		
		for(int i=head[y[l]];i;i=nxt[i]){
			if(st[num[i]]==1)ans2[++cnt2]=num[i];
			if(cnt2>=h)break;
		}
		for(int i=head[y[l]];i;i=nxt[i]){
			if(st[num[i]]==2&&cnt2<h)ans2[++cnt2]=num[i],st[num[i]]=3;
			if(cnt2>=h)break;
		}
		
		
		if(cnt1>=t&&cnt2>=h){
			printf("YES\n");
			printf("%d %d\n",y[l],x[l]);
			for(int i=1;i<=h;i++)printf("%d ",ans2[i]);printf("\n");
			for(int i=1;i<=t;i++)printf("%d ",ans1[i]);printf("\n");
			return 0;
		}
		
		for(int i=head[x[l]];i;i=nxt[i])st[num[i]]=0;
		for(int i=head[y[l]];i;i=nxt[i])st[num[i]]=0;
	}
	printf("NO\n");
	return 0;
}
```


---

## 作者：ConstantModerato (赞：0)

**题意：给定一个无向图，判断是否有两个节点，分别有 $h$，$t$ 个不相交的节点。**

首先肯定是要枚举两个相邻的节点，时间复杂度 $O(m)$。然后判断是否有 $h$，$t$ 个相邻的节点。

显然我们在判断的时候，需要把两个节点的共同有连边的点集找出来，然后对于两个节点的出度和入度进行判断。

但是如果我们枚举每一条边，这个时间复杂度最差是 $O(m)$ 的，复杂度就变成 $O(n^2)$，无法通过。

但是我们可以发现 $h,t\le 100$，考虑能否从 $h,t$ 下手。观察到如果有一个节点的度数是大于等于 $h + t$ 的，那么显然这个点是满足要求的。因此我们对于一个点只需要枚举 $h + t$ 条边就行了。

复杂度 $O(mh + mt)$。

```
int n,m,h,t;
struct node{
    int u,v;
}edge[N];
int deg[N],check[N];
vector<int> E[N];
int st[N];
int main(){
    n = read(),m = read(),h = read(),t = read();
    for (int i = 1;i <= m;i++){
        int u = read(),v = read();
        E[u].push_back(v);
        E[v].push_back(u);
        deg[u]++,deg[v]++;
    } 
    for (int i = 1;i <= n;i++){ 
        if (deg[i] <= h) continue;
        int u = i;
        for (auto v : E[i]) st[v]++;// <= 2 * m
        for (auto v1 : E[i]){
            int cnt = 0;
            for (auto v : E[v1]){
                st[v]+=2;
                if (st[v] == 3) check[cnt++] = v;
                if (cnt >= h + t) break;
            }// <= h + t
            if (cnt == h + t){
                puts("YES");
                printf("%d %d\n",u,v1);
                for (int j = 0;j < h;j++) cout << check[j] << " ";
                cout << endl;
                for (int j = h;j < h + t;j++) cout << check[j] << " ";
                cout << endl;
                return 0;
            }
            if (deg[u] > h && deg[v1] > t){
                if (h - (deg[u] - 1 - cnt) + t - (deg[v1] - 1 - cnt) <= cnt){
                    puts("YES");
                    printf("%d %d\n",u,v1);
                    int tmp1 = 0,tmp2 = 0;
                    for (int j = 1;j <= n;j++){
                        if (st[j] == 1 && j != v1) printf("%d ",j),tmp1++;
                        if (tmp1 == h) break;
                    } for (int j = 0;j < h - tmp1;j++) printf("%d ",check[j]);
                    puts("");
                    for (int j = 1;j <= n;j++){
                        if (st[j] == 2 && j != u) printf("%d ",j),tmp2++;
                        if (tmp2 == t) break;
                    } for (int j = h - tmp1;j < h + t - tmp2 - tmp1;j++) 
                        printf("%d ",check[j]);
                    return 0;
                }
            }
            for (auto v : E[v1]) st[v] -= 2;
        } for (auto v : E[i]) st[v]--;
    } puts("NO");
    return 0;
}
```

这里再提供一份榜三 **rng_58** 的代码。他用三个 ```vector``` 分别维护了三个不同的点集。这让输出变得更加容易。代码也更清晰可读。

```

int N,A,B;
vector <pair <int, int> > edges;
vector <int> graph[100010];
bool c[100010];

bool check(int a, int b){
    int i;
    int dega = 0, degb = 0, deg = 0;
    
    REP(i,graph[a].size()){
        int x = graph[a][i];
        if(x != b){
            dega++;
            deg++;
            c[x] = true;
        }
    }
    
    REP(i,graph[b].size()){
        int x = graph[b][i];
        if(x != a){
            degb++;
            if(!c[x]) deg++;
        }
    }
    
    REP(i,graph[a].size()){
        int x = graph[a][i];
        if(x != b) c[x] = false;
    }
    
    if(dega >= A && degb >= B && deg >= A + B) return true;
    return false;
}

void print(int a, int b){
    int i;
    
    cout << "YES" << endl;
    cout << a+1 << ' ' << b+1 << endl;
    
    set <int> sa,sb;
    REP(i,graph[a].size()) if(graph[a][i] != b) sa.insert(graph[a][i]);
    REP(i,graph[b].size()) if(graph[b][i] != a) sb.insert(graph[b][i]);
    
    vector <int> va,vb,both;
    foreach(sa,itr){
        int x = (*itr);
        if(sb.find(x) == sb.end()) va.push_back(x+1); else both.push_back(x+1);
    }
    foreach(sb,itr){
        int x = (*itr);
        if(sa.find(x) == sa.end()) vb.push_back(x+1);
    }
    
    while(va.size() > A) va.pop_back();
    while(vb.size() > B) vb.pop_back();
    while(va.size() < A){
        va.push_back(both[both.size()-1]);
        both.pop_back();
    }
    while(vb.size() < B){
        vb.push_back(both[both.size()-1]);
        both.pop_back();
    }
    
    REP(i,A){
        cout << va[i];
        if(i == A-1) cout << endl; else cout << ' ';
    }
    REP(i,B){
        cout << vb[i];
        if(i == B-1) cout << endl; else cout << ' ';
    }
}

int main(void){
    int M,x,y,i;
    
    scanf("%d%d%d%d", &N, &M, &A, &B);
    REP(i,M){
        scanf("%d%d", &x, &y); x--; y--;
        edges.push_back(make_pair(x,y));
        if(graph[x].size() < 210) graph[x].push_back(y);
        if(graph[y].size() < 210) graph[y].push_back(x);
    }
    
    REP(i,edges.size()){
        int a = edges[i].first, b = edges[i].second;
        if(check(a,b)){
            print(a,b);
            return 0;
        }
        if(check(b,a)){
            print(b,a);
            return 0;
        }
    }
    
    cout << "NO" << endl;
    
    return 0;
}

```
基本看一下就知道是什么意思了。

注意，我一开始用了 ```map<int,map<int,int> >``` 来存储点对是否连通，但是却遗憾 ```TLE``` 了，还是得少用 ```map```。


---

## 作者：Jerrywang09 (赞：0)

枚举点 $u,v$，或者说枚举边。然后找出 $u,v$ 分别所连的点。

有数组 $st$，结点 $x$ 仅与 $u$ 相邻则 $st[x]=1$，仅与 $v$ 相邻则 $st[x]=2$，与两个点都相邻则 $st[x]=3$。

用数组 $rest$ 记录 $st[x]=3$ 的所有 $x$。先优先选走至多 $h$ 个 $x|st[x]=1$，再选走至多 $t$ 个 $x|st[x]=2$。如果还不够就动用 $rest$ 里面的。这个贪心很显然。

$h,t$ 很小，复杂度可以保证。注意清空 $st$ 不能直接 `memset`。

```cpp
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=100010;
using namespace std;

int n, m, h, t, st[N];
vector<int> g[N];
int rest[N], k;

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%d%d%d%d", &n, &m, &h, &t);
    rep(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rep(u, 1, n) for(int v:g[u])
    {
        if(g[u].size()<=h || g[v].size()<=t) continue;
        for(int x:g[u]) if(x!=v)
            st[x]=1;
        k=0;
        for(int x:g[v]) if(x!=u)
        {
            st[x]+=2;
            if(st[x]==3) rest[++k]=x;
        }
        vector<int> head, tail;
        for(int x:g[u]) if(x!=v && st[x]==1)
        {
            head.push_back(x);
            if(head.size()>=h) break;
        }
        for(int x:g[v]) if(x!=u && st[x]==2)
        {
            tail.push_back(x);
            if(tail.size()>=t) break;
        }
        while(head.size()<h && k)
            head.push_back(rest[k--]);
        while(tail.size()<t && k)
            tail.push_back(rest[k--]);
        if(head.size()>=h && tail.size()>=t)
        {
            puts("YES");
            printf("%d %d\n", u, v);
            for(int x:head) printf("%d ", x);
            puts("");
            for(int x:tail) printf("%d ", x);
            return 0;
        }
        for(int x:g[u]) st[x]=0;
        for(int x:g[v]) st[x]=0;
    }
    puts("NO");
    
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

先枚举每一条边，再判断是否可行。枚举边时需要注意，两个端点可以互换位置。假设当前我们以 $u$ 为胸，以 $v$ 为腹，设 $d_i$ 表示点 $i$ 的度数，如果 $d_u\le h$ 或 $d_v\le t$，那么该情况一定不合法，因为这在不考虑点的交集时已经不可能达成目标了。接下来为了尽可能满足目标，我们要贪心地去取点。具体地，可以先把 $u$ 所连的除 $v$ 的点全放到胸部。然后在把 $v$ 所连的除 $u$ 的点放到腹部的过程中，如果出现一个点已经被放到胸部的情况，就把那个点挪到腹部，腹部可用点数加一，胸部可用点数减一。否则直接加入腹部可用点就行。最后只要看胸腹可用点是否都达到要求就行。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct edge{
	int u,v;
}E[N];
int n,m,h,t,cnt[N];
bool flag[N];
vector<int>e[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();m=read();h=read();t=read();
	for(int i=1;i<=m;i++){
		E[i].u=read();E[i].v=read();cnt[E[i].u]++;cnt[E[i].v]++;
		e[E[i].u].push_back(E[i].v);e[E[i].v].push_back(E[i].u);
	}
	for(int i=1;i<=m;i++){
		int u=E[i].u,v=E[i].v;
		if(cnt[u]<=h||cnt[v]<=t)continue;
		int cnta=cnt[u]-1;
		for(int j=0;j<e[u].size();j++){
			flag[e[u][j]]=1;
		}
		int num=0;
		for(int j=0;j<e[v].size();j++){
			if(e[v][j]==u)continue;
			if(!flag[e[v][j]])num++;
			else if(cnta>h&&flag[e[v][j]]){
				flag[e[v][j]]=0;cnta--;num++;
			}
		}
		if(num>=t){
			puts("YES");
			printf("%d %d\n",u,v);
			int ccc=0;
			for(int j=0;j<e[u].size();j++){
				if(e[u][j]==v||!flag[e[u][j]])continue;
				ccc++;printf("%d ",e[u][j]);
				if(ccc==h){
					putchar('\n');
					break;
				}
			}
			ccc=0;
			for(int j=0;j<e[v].size();j++){
				if(e[v][j]==u||flag[e[v][j]])continue;
				ccc++;printf("%d ",e[v][j]);
				if(ccc==t){
					break;
				}
			}
			return 0;
		}
		for(int j=0;j<e[u].size();j++){
			flag[e[u][j]]=0;
		}
	}
	for(int i=1;i<=m;i++){
		int u=E[i].v,v=E[i].u;
		if(cnt[u]<=h||cnt[v]<=t)continue;
		int cnta=cnt[u]-1;
		for(int j=0;j<e[u].size();j++){
			flag[e[u][j]]=1;
		}
		int num=0;
		for(int j=0;j<e[v].size();j++){
			if(e[v][j]==u)continue;
			if(!flag[e[v][j]])num++;
			else if(cnta>h&&flag[e[v][j]]){
				flag[e[v][j]]=0;cnta--;num++;
			}
		}
		if(num>=t){
			puts("YES");
			printf("%d %d\n",u,v);
			int ccc=0;
			for(int j=0;j<e[u].size();j++){
				if(e[u][j]==v||!flag[e[u][j]])continue;
				ccc++;printf("%d ",e[u][j]);
				if(ccc==h){
					putchar('\n');
					break;
				}
			}
			ccc=0;
			for(int j=0;j<e[v].size();j++){
				if(e[v][j]==u||flag[e[v][j]])continue;
				ccc++;printf("%d ",e[v][j]);
				if(ccc==t){
					break;
				}
			}
			return 0;
		}
		for(int j=0;j<e[u].size();j++){
			flag[e[u][j]]=0;
		}
	}
	puts("NO");
	return 0;
}

```


---

## 作者：_edge_ (赞：0)

我一看这种题目，这不是模拟吗？直接枚举每一条边，然后判断两个点是否是满足头和尾的。

然后我就严重怀疑这个 CF 评分真的是 $2000$ 么 ……

然后，然后看到这个样例之后发现要没有重复的点，这个也挺好办的，就是直接将头所有的点都扔进一个桶里面，然后尾在遍历边的时候，可以直接取出，让头的度数 $-1$，但是要使他能够超过 $h$。

我们发现这个东西，一条边的两个端点可以交换位置，或者换句话说，有两种情况，要么第一个点为头，第二个点为尾，或者是第一个点为尾，第二个点为头，所以要扫两边。

综合起来这个复杂度，好像还挺快的？~~反正能过就行，还管他什么复杂度呢？~~

然后，我相信赛时有一大堆人 FST 了，因为这个模拟东西要有点耐心。

另外，清空桶的时候，不要用 memset 这样复杂度是 $O(m^2)$ 了，可以直接遍历一遍边清空。

在最后的最后，我给大家提个醒，如果你是 $47$ 这个点 WA 了，那么你有可能是没有输出完整答案，就是你的第二行输出的不为 $h$ 个，或者你第三行输出不为 $t$ 个。

这题目要求人细心不能着急。

如有问题还请指出。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2e5+5;
int n,m,h,t,head[INF],tot,xx[INF],yy[INF],in[INF],b[INF],ans[INF],ans1[INF];
struct _node_edge{
    int to_,next_;
}edge[INF<<1];
void add_edge(int x,int y) {
    edge[++tot]=(_node_edge){y,head[x]};
    head[x]=tot;return ;
}
signed main()
{
    scanf("%d %d %d %d",&n,&m,&h,&t);
    for (int i=1;i<=m;i++) {
        int x=0,y=0;scanf("%d %d",&x,&y);
        add_edge(x,y);add_edge(y,x);
        in[x]++;in[y]++;
        xx[i]=x;yy[i]=y;
    }
    int fl=0;
    for (int i=1;i<=m;i++) {
        if (fl) break;
        int x=xx[i],y=yy[i];
        // swap(x,y);
        if (in[x]>h && in[y]>t) {
            ans[0]=ans1[0]=0;
            for (int i=head[x];i;i=edge[i].next_) {
                if (edge[i].to_!=y) {
                    b[edge[i].to_]=1;
                    ans[++ans[0]]=edge[i].to_;
                }
            }
            int sum=0,sum1=0;
            for (int i=head[y];i;i=edge[i].next_,sum++) {
                if (edge[i].to_!=x) {
                    if (b[edge[i].to_]==1) {
                        if (ans[0]-sum1<=h) {sum--;continue;}
                        sum1++;b[edge[i].to_]=0;
                    }
                    ans1[++ans1[0]]=edge[i].to_;
                }
            }
            // cout<<sum<<" break\n";
            if (sum<=t) {
                for (int i=head[x];i;i=edge[i].next_) b[edge[i].to_]=0;
                for (int i=head[y];i;i=edge[i].next_) b[edge[i].to_]=0;
                continue;
            }
            else {
                fl=1;
                cout<<"YES\n";
                cout<<x<<" "<<y<<"\n";
                int kk=0;
                for (int i=1;i<=ans[0];i++) {
                    if (b[ans[i]]==1) {
                        kk++;
                        cout<<ans[i]<<" ";
                    }
                    if (kk==h) break;
                }
                cout<<"\n";kk++;
                for (int i=1;i<=ans1[0];i++) {
                    //if (ans1[i]<0) return 1;
                    cout<<ans1[i]<<" ";
                    if (i==t) break;
                }
                cout<<"\n";
                break;
            }
        }
    }
    for (int i=1;i<=m;i++) {
        if (fl) break;
        int x=xx[i],y=yy[i];
        swap(x,y);
        if (in[x]>h && in[y]>t) {
            ans[0]=ans1[0]=0;
            for (int i=head[x];i;i=edge[i].next_) {
                if (edge[i].to_!=y) {
                    b[edge[i].to_]=1;
                    ans[++ans[0]]=edge[i].to_;
                }
            }
            int sum=0,sum1=0;
            for (int i=head[y];i;i=edge[i].next_,sum++) {
                if (edge[i].to_!=x) {
                    if (b[edge[i].to_]==1) {
                        if (ans[0]-sum1<=h) {sum--;continue;}
                        sum1++;b[edge[i].to_]=0;
                    }
                    b[edge[i].to_]=true;
                    ans1[++ans1[0]]=edge[i].to_;
                }
            }
            if (sum<=t) {
                for (int i=head[x];i;i=edge[i].next_) b[edge[i].to_]=0;
                for (int i=head[y];i;i=edge[i].next_) b[edge[i].to_]=0;
                continue;
            }
            else {
                fl=1;
                cout<<"YES\n";
                cout<<x<<" "<<y<<"\n";
                int kk=0;
                for (int i=1;i<=ans[0];i++) {
                    if (b[ans[i]]==1) {
                        kk++;
                        cout<<ans[i]<<" ";
                    }
                    if (kk==h) break;
                }
                cout<<"\n";kk++;
                for (int i=1;i<=ans1[0];i++) {
                    cout<<ans1[i]<<" ";
                    if (i==t) break;
                }
                cout<<"\n";
                break;
            }
        }
    }
    if (!fl) cout<<"NO\n";
    return 0;
}
```


---

## 作者：Ryo_Yamada (赞：0)

发现 $h$ 和 $t$ 很小，考虑复杂度带 $h/t$ 的做法。

$h$ 和 $t$ 实际上就是要求找的节点个数，而如果复杂度带这玩意，考虑直接暴力。考虑枚举每一条边，因为是双向边所以不妨设当前 $u$ 要找 $h$ 个节点而 $v$ 要找 $t$ 个。

首先发现如果 $u$ 的度数 $\le h$ 或 $v$ 的度数 $\le t$ 则无解。

其次，如果 $u$ 和 $v$ 有一个点的度数 $> h+t$，则一定有解。这样另一个点只需要随便选，而这个点一定能找到合法且足够的点。

否则，这两个点的度数就被限制在了 $(h,h+t]$ 和 $(t,h+t]$，直接暴力查找即可。对于每个点先考虑只与其联通的点，然后再考虑与两个点都联通的点即可。

时间复杂度 $O((h+t)m)$，注意判 $u$ 和 $v$ 不能用。

$\text{Code}$：

```cpp
int n, m, h, t;
vector<int> e[N];
int vis[N];
int ansu[N], ansv[N];

int main() {
	qread(n, m, h, t);
	rep(i, 1, m) {
		int u, v;
		qread(u, v);
		e[u].pb(v), e[v].pb(u);
	}
	rep(u, 1, n) {
		if(e[u].size() <= h) continue;
		for(int v : e[u]) {
			if(e[v].size() <= t) continue;
			if(e[u].size() >= h + t + 1) {
				puts("YES");
				cout << u << ' ' << v << endl;
				vis[v] = 1;
				int siz = t - 1;
				rep(j, 0, siz) if(e[v][j] == u) ++siz; else vis[e[v][j]] = 1;
				int cnt = 0;
				for(int w : e[u]) if(!vis[w]) {
					cout << w << ' ';
					if(++cnt == h) break;
				}
				puts("");
				rep(j, 0, siz) if(e[v][j] != u) cout << e[v][j] << ' ';
				puts("");
				return 0;
			}
			if(e[v].size() >= h + t + 1) {
				puts("YES");
				cout << u << ' ' << v << endl;
				vis[u] = 1;
				int siz = h - 1;
				rep(j, 0, siz) if(e[u][j] == v) ++siz; else cout << e[u][j] << ' ', vis[e[u][j]] = 1;
				puts("");
				int cnt = 0;
				for(int w : e[v]) if(!vis[w]) {
					cout << w << ' ';
					if(++cnt == t) break;
				}
				puts("");
				return 0;
			}
			int cnt = 0, cu = 0, cv = 0;
			for(int w : e[u]) if(w != v) { if(++vis[w] == 1) ++cnt; }
			for(int w : e[v]) if(w != u) { if(++vis[w] == 1) ++cnt; }
			if(cnt < h + t) {
				for(int w : e[u]) vis[w] = 0;
				for(int w : e[v]) vis[w] = 0;
				continue;
			}
			for(int w : e[u]) if(vis[w] == 1 && cu < h) ansu[++cu] = w;
			for(int w : e[v]) if(vis[w] == 1 && cv < t) ansv[++cv] = w;
			for(int w : e[u]) if(vis[w] == 2 && cu < h) vis[w] = 0, ansu[++cu] = w;
			for(int w : e[v]) if(vis[w] == 2 && cv < t) vis[w] = 0, ansv[++cv] = w;
			puts("YES");
			cout << u << ' ' << v << endl;
			rep(j, 1, h) cout << ansu[j] << ' ';
			puts("");
			rep(j, 1, t) cout << ansv[j] << ' ';
			puts("");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
```


---

## 作者：RyexAwl (赞：0)

考虑枚举每一条边看其连接的两个点是否满足条件。

我们发现，只要我们确定了两个点所连的点的交集我们就可以确定这两个点是否可以成为答案。

如果两个点的公共点个数为$\text{same}$个。

假定$\deg(u) \ge \deg(v)$

如果满足$\deg(v) - 1 -\max(0,\deg(x) - \text{same} - 1)\ge t$，那么这两个点一定可以成为答案。

且我们发现如果$\deg(u)-1\le h$或$\deg(v)-1\le t$那么这两个点一定不能成为答案。

并且由上结论我们发现如果满足$\deg(u)\ge h + t + 1,\deg(v)\ge t+1$则一定能成为答案。

那么我们主要对于$h+1\le\deg(u)\le h + t + 1,\deg(v)\ge t+1$的情况遍历一下找出$\text{same}$即可。(每次把相连的点标记一下，在结束$\text{check}$后取消标记。)

因为$\deg(u)\le h + t + 1$，因此复杂度为$\text{O}(m(h+t))$。

~~代码较丑请见谅~~


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
 
namespace wxy{
	#define x first
	#define y second
	const int N = 1e6 + 5;
	typedef std::pair<int,int> PII;
	int h,t,n,m;
	int head[N],edge[N << 1],fail[N << 1],deg[N],tot;
	inline void add(int x,int y){
		edge[++tot] = y;
		fail[tot] = head[x];
		head[x] = tot;
	}
	bool check = false;
	bool vw[N],vis[N],vp[N];
	std::vector<int> ansx;
	std::vector<int> ansy;
	inline bool fuck(bool vis[],int x,int v){
			int same = 0; 
			for (int j = head[v];j;j = fail[j]){
				if(vis[edge[j]]){
					same++;
					vw[edge[j]] = true;
				}
			}
			int cnt = deg[v] - 1 - same;
			int delta = std::max(0,h - (deg[x] - same - 1));
			int pp = same - delta;
			cnt += pp;
			if (cnt >= t){
				std::cout << "YES" << std::endl;
				int p = std::min(h,deg[x] - same - 1),q = delta;
				int ct = 0;
				for (int k = head[x];k;k = fail[k]){
					if (ct < p){
						if (edge[k] != v && !vw[edge[k]]){
							ansx.push_back(edge[k]);
							ct++;
						}
					}else break;
				}
				ct = 0;
				for (int k = head[x];k;k = fail[k]){
					if (ct < q){
						if (edge[k] != v && vw[edge[k]]){
							ansx.push_back(edge[k]);
							vp[edge[k]] = true;
							ct++;
						}
					}else break;
				}
				ct = 0;
				for (int k = head[v];k;k = fail[k]){
					if (ct < t){
						if (edge[k] != x && !vp[edge[k]]){
							ct++;
							ansy.push_back(edge[k]);
						}
					}else break;
				}
				
				return true;
		}
		for (int j = head[v];j;j = fail[j])
			if(vis[edge[j]])vw[edge[j]] = false;
		return false;
	}
	inline bool dfs(int x,int v){
		if (deg[x] - 1 < h || deg[v] < t) return false;
		if (deg[x] - 1 >= h + t && deg[v] - 1 >= t){
				std::cout << "YES" << std::endl;
				int ct = 0;
				for (int i = head[v];i; i = fail[i]){
					if (ct < t && edge[i] != x){
						ansy.push_back(edge[i]);
						vis[edge[i]] = true;
						ct++;
					}
				}
				ct = 0;
				for (int i = head[x];i; i = fail[i]){
					if (ct < h && edge[i] != v  && !vis[edge[i]]){
						ansx.push_back(edge[i]);
						ct++;
					}
				}
				return true;
		}
		for (int i = head[x];i;i = fail[i]) vis[edge[i]] = true;
		if (fuck(vis,x,v)) return true;
		for (int i = head[x];i;i = fail[i]) vis[edge[i]] = false;
		return false;
	}
	PII edg[N];
	inline void main(){
		tot = 0;
		scanf("%d%d%d%d",&n,&m,&h,&t);
		if (h < t){
			check = true;	
			std::swap(h,t);
		}
		for (int i = 0; i < m; i++){
			int a,b;scanf("%d%d",&a,&b);
			add(a,b);add(b,a);
			deg[a]++;deg[b]++;
			edg[i].x = a;edg[i].y = b;
		}
		for (int i = 0; i < m; i++){
			if (edg[i].x < edg[i].y) std::swap(edg[i].x,edg[i].y);
			if (dfs(edg[i].x,edg[i].y)){
				int x = edg[i].x,v = edg[i].y;
				if (check){
					std::cout << v << " " << x;
					puts("");
					for (int i = 0; i < ansy.size(); i++) std::cout << ansy[i] << " ";
					puts("");
					for (int i = 0; i < ansx.size(); i++) std::cout << ansx[i] << " ";
				}else{
					std::cout << x << " " << v;
					puts("");
					for (int i = 0; i < ansx.size(); i++) std::cout << ansx[i] << " ";
					puts("");
					for (int i = 0; i < ansy.size(); i++) std::cout << ansy[i] << " ";
				}
				return;
			}
		}
		std::cout << "NO";
	}
}signed main(){wxy::main();return 0;}
```


---

