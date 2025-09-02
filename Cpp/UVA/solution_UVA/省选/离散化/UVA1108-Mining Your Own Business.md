# Mining Your Own Business

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3549

[PDF](https://uva.onlinejudge.org/external/11/p1108.pdf)

# 题解

## 作者：luckydrawbox (赞：17)

[$\text{Link}$](https://www.luogu.com.cn/problem/UVA1108)

一定要看到最后哦！

## 题意

>在一个无向图上选择尽量少的点涂黑，使得删除任意一个点后，每个连通分量里都至少有一个黑点。

## 分析

看到删除任意一个点和连通分量，不难想到先求无向图的点双连通分量并缩点。缩点之后，无向图就变成了一颗树（题目保证图是连通的）。

接下来我们对于每个缩成点后的点双联通分量进行分类讨论，此时原图变成了新图，设一个缩点包含的点集为 $S$。

-  $S$ 没有边与别的点相连。

显然，此时整个图是一个点双连通分量，我们可以把其中任意两个点（至少有两个点，因为题目保证 $n$ 是正整数）染成黑色，如果一个点被删了，显然连通分量中还是有黑点的。故此时最少的个数为 $2$，$S$ 的方案数为 $\frac{|S|\times (|S|-1)}{2}$。

- $S$ 只有一条边与别的点相连。

此时如果删掉这条边对面的点（易知对面的点为割点），$S$ 会从无向图中分裂出去，因此 $S$ 中至少有一个点被染黑；如果删掉 $S$ 中的黑点，则 $S$ 可与沿着该边到达的包含黑点的点集连通。

故最少的个数需要加上 $1$，$S$ 的方案数为 $|S|-1$，减去 $1$ 是因为 $S$ 中包含一个割点，把割点染黑是没有用处的，所以要减去。

- $S$ 有多条边与别的点相连。

此时无论删除哪一个点，$S$ 都可与沿着这些边到达的包含黑点的点集连通，所以 $S$ 中不需要染黑点，最少的个数只要加上 $0$，$S$ 的方案数为 $1$，相当于对答案没有任何影响。

综上所述，第一问的答案就是上面三种情况的最少个数之和，第二问的答案就是上面三种情况的方案数之积。

到了这里，你已经可以 AC 此题了，然而这还不够，你会发现这样好像过不了 [AcWing](https://www.acwing.com/problem/content/398/) 上的数据，原来 AcWing 上的点不保证全部都出现一遍，所以我们再开个数组 $v$ 表示每个点是否出现过，再计个数 $mx$ 表示出现过的最大点，对于每个点 $i(1\le i\le mx)$，如果出现过，则按照之前的方式处理，否则只会使第一问的答案增加 $1$。

## 代码

时间复杂度 $O(TN)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
int t,n,mx;
ll ans,sum;
int head[N],nxt[N<<1],ver[N<<1],tot;
int hc[N],nc[N<<1],vc[N<<1],tc;
int root,num,dfn[N],low[N];
int top,stak[N];
int cnt,new_id[N],c[N];
vector<int>v_dcc[N];
bool cut[N],v[N];
void add(int x,int y){
	ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
}
void add_c(int x,int y){
	vc[++tc]=y,nc[tc]=hc[x],hc[x]=tc;
} 
void tarjan_v_dcc(int x){
	dfn[x]=low[x]=++num;
	stak[++top]=x;
	int flag=0;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan_v_dcc(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				flag++;
				if(x!=root||flag>1)
					cut[x]=1;
				cnt++;
				int z;
				do{
					z=stak[top--];
					v_dcc[cnt].push_back(z);
				}while(z!=y);
				v_dcc[cnt].push_back(x);
			}
		}
		else
			low[x]=min(low[x],dfn[y]);
	} 
}
void work_v_dcc(){
	for(int i=1;i<=mx;i++)
		if(v[i]&&!dfn[i])
			root=i,tarjan_v_dcc(i);
}
void sh_v_dcc(){
	num=cnt;
	for(int i=1;i<=mx;i++)
		if(cut[i])
			new_id[i]=++num;
	tc=1;
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<v_dcc[i].size();j++){
			int x=v_dcc[i][j];
			if(cut[x]){
				add_c(i,new_id[x]);
				add_c(new_id[x],i);
			}
			else
				c[x]=i;
		}
}
int main(){
	while(n=read()){
		printf("Case %d: ",++t);
		cnt=top=num=mx=0;//初始化 
		tot=1;
		memset(head,0,sizeof(head));
		memset(hc,0,sizeof(hc)); 
		memset(cut,0,sizeof(cut)); 
		memset(dfn,0,sizeof(dfn)); 
		memset(low,0,sizeof(low)); 
		memset(stak,0,sizeof(stak));
		memset(v,0,sizeof(v));
		sum=0;ans=1;
		for(int i=1,x,y;i<=n;i++){//读入 
			x=read();y=read();
			add(x,y);add(y,x);
			v[x]=v[y]=1;
            mx=max(mx,max(x,y));
		}
		for(int i=1;i<=mx;i++)
			v_dcc[i].clear();
		work_v_dcc();//求点双连通分量 
		sh_v_dcc();//缩点建图 
		for(int i=1;i<=cnt;i++){//分类求答案 
			if(!hc[i]){//第一种 
				sum+=2;
				ans*=(ll)v_dcc[i].size()*(v_dcc[i].size()-1)/2;
			}
			else if(!nc[hc[i]]){//第二种 
				sum++;
				ans*=(ll)(v_dcc[i].size()-1);
			}
		}
        for(int i=1;i<=mx;i++)
            if(!v[i])
                sum++;
		printf("%lld %lld\n",sum,ans);
	}
	return 0;
}
```

别急着走哦！

## 突然

一位面带微笑的老伯伯（非作者）在你面前的屏幕中出现。

「小伙子，我看你在 $@$[$\color{Red}\text{chenjunxiu}$](https://www.luogu.com.cn/user/419144)[$\color{Blue}\surd$](https://www.luogu.com.cn/discuss/show/142324) 的题解前待很久了，是不是丢了什么东西？你丢的是这个金色的$\color{Gold}\text{经验}$，还是这个银色的$\color{Silver}\text{经验}$呢？」

“老伯伯，我没有丢东西呀，我刚才只是在抄，呸，借鉴 Ta 的题解而已。”

「哦，真是个诚实的孩子，老夫决定把这两个[$\color{Gold}\text{经}$](https://www.luogu.com.cn/problem/P3225)[$\color{Silver}\text{验}$](https://www.luogu.com.cn/problem/SP16185)都送给你！」

“az，谢谢老伯伯，不过，那几个有色字和两个带色的链接……您是怎样说出来的呢？”

「嗯……好问题，不过你得先点赞加关注，我才能告诉你哦。」

“……”

---

## 作者：STA_Morlin (赞：10)

[UVA1108 Mining Your Own Business の 题目传送门。](https://www.luogu.com.cn/problem/UVA1108)

## 题目简述
 - 有一边数为 $m$ 的无向图。
 - 要求标记一些点，使得删除任意一点后所有点仍与标记点连接，求最少标记点数和方案总数。
 - 多组数据。

## 题目分析

模板题。

从 ~~P3225的题目标签~~ 要求删除点很容易就能看出是 tarjan。

然后可以发现此题求的是类似于联通块，又和点有关，经过一些玄学思考就可以发现是 v-dcc。

在进行完基本的 v-dcc 缩点之后，就到了关键的步骤：找到修建的地方。

（以下所述的点与边是缩点完成之后的图里的。）

### 标记点

进行分讨：

- 割点被删除。  
那么被分开的两部分就只能往两边跑，可以跑到叶子。

- 叶子被删除。  
可以跑到另一边的叶子。

- 其他点被删除。  
不重要。

综上，修建在叶子上最合适，且每个叶子都需要修建。

### 标记方案

由于每个叶子都标记，所以遇到叶子就要增加方案数。

小学奥数：这里使用乘法。

---
## 代码实现

叶子的特点是只有一个度，所以在建新图的时候就应该标记上度。

进行分讨：

- 是叶子（度为 $1$）  
标记数 $+1$，方案数乘连通块大小 $-1$（与割点连的那个点不能用来修建）。

- 是环（度为 $0$）
标记数为 $2$ 或连通块的大小取 $\min$（至少标记两处，因为标记点可能被删除，但是如果连通块大小为 $1$，就只能建一个（但是由于这是连通图且至少有一条边且无自环，所以不写也行））。

# _CODE_
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int man = 5e4+10;
class Graph {
public:
    int hed[man], len = 1;
    int nxt[man<<1], ver[man<<1];
    void Ins (int u, int v) {
        ver[++len] = v;
        nxt[len] = hed[u];
        hed[u] = len;
        return ;
    } 
    void DIns (int u, int v) {
        Ins(u, v), Ins(v, u);
        return ;
    } 
} G, Gs;

int n, m;
int dfn[man], low[man], c[man];
bool cut[man];
vector <int> vdcc[man];
stack <int> stk;
void tarjan (int) ;
void build () ;
int main () {
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    (void)scanf("%d", &m);
    while (1) {
        for (int u, v, i = 1; i <= m; ++ i) {
            (void)scanf("%d%d", &u, &v);
            G.DIns(u, v);
            n = max({n, u, v});
        } for (int i = 1; i <= n; ++ i) if (!dfn[i]) rt = i, tarjan(i);
        build();
        for (int i = 1; i <= vnt; ++ i) {
            if (!ino[i]) ans += min(2, int(vdcc[i].size())), res *= (vdcc[i].size()*(vdcc[i].size()-1))>>1;
            if (ino[i] == 1) ++ ans, res *= (vdcc[i].size()-1);//, cout << vdcc[i].size() << i;
            // if (ino[i] == 1) ++ res;
        } printf("Case %d: %d %lld\n", ++ x, ans, res);
        // for (int i = 1; i <= n; ++ i) printf("%d ", cut[i]);
        // for (int i = 2; i < Gs.len; i += 2) {
        //     printf("%d: %d - %d", i>>1, Gs.ver[i], Gs.ver[i^1]);
        //     // for (int j = Gs.hed[i]; j; j = Gs.nxt[j]) printf("%d ", Gs.ver[j]);
        //     puts("");
        // }
        // for (int i = 1; i <= vnt; ++ i) {
        //     printf("%d: ", i);
        //     for (int a: vdcc[i]) printf("%d ", a);
        //     puts("");
        // }
        (void)scanf("%d", &m);
        if (!m) return 0;
        memset(dfn, 0, sizeof(dfn)), cnt = 0;
        memset(low, 0, sizeof(low)), vnt = 0;
        memset(cut, 0, sizeof(cut)), ans = 0;
        memset(ino, 0, sizeof(ino)), res = 1;
        G.clear(), Gs.clear(), n = 0;
        while (stk.size()) stk.pop();
        for (int i = 1; i <= m; ++ i) vdcc[i].clear();
    } return 0;
}

void tarjan (int x) {
    int son = 0;
    stk.push(x);
    dfn[x] = low[x] = ++ cnt;
    for (int i = G.hed[x]; i; i = G.nxt[i]) {
        int v = G.ver[i];
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
            if (low[v] >= dfn[x]) {
                if ((x!=rt || ++ son>1) && !cut[x]) cut[x] = 1;
                ++ vnt; int p;
                do {
                    p = stk.top(), stk.pop();
                    vdcc[vnt].push_back(p);
                } while (p != v);
                vdcc[vnt].push_back(x);
            }
        } else low[x] = min(low[x], dfn[v]);
    } return ;
}
void build () {
    cnt = vnt;
    for (int i = 1; i <= n; ++ i) if (cut[i]) c[i] = ++cnt; // 割点单独属于一个缩进的点
    // printf("%d %d\n", cnt, vnt);
    for (int i = 1; i <= vnt; ++ i) // 第几个 v-dcc
        for (int a: vdcc[i]) {
            if (cut[a]) {
                Gs.DIns(i, c[a]);
                ++ ino[i], ++ ino[c[a]];
                // if (x == 1) printf("KKK%d %d\n", i, c[a]);
                //  printf("%d %d\n", i, c[a]);
            }
            else c[a] = i;
        }
    return ;
}
```
# E.N.D.

---

## 作者：寒鸽儿 (赞：3)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-uva1108)
### 对于tarjan - d-vcc求法的考察
如果一个建立逃生点的点塌了，那么其他点都不能到哪里去，也不能经过它。  
关于经过不经过，这不就是说有关于双连通的问题吗?在同一个双连通分量中，坍塌任意一个点，原图必然还是连通。因而至多在每个v-dcc中建立一个逃生点。  
还能否再去掉一些点？缩点之后，是一棵树，一个结点的度如果大于1，那么其中一个坍塌还能从另一个中逃跑到其他点之中。v-dcc通过什么与其它v-dcc相连呢？必然是割点，否则不满足分量的极大性。而度数就等价于每个分量中的割点数。  
特殊情况是，如果整个图为v-dcc，那么必须设立2个点，因为不能再跑到其他地方去了。  
方案数容易用数学手段统计得到。
附上代码：
```cpp
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 50010, maxm = 50010;
#define min(x, y) (x) < (y) ? (x) : (y)

int head[maxn], ver[maxm<<1], nex[maxm<<1], tot;
inline void addedge(int u, int v) {
    ver[tot] = v; nex[tot] = head[u]; head[u] = tot++;
}

vector<int> dcc[maxn];
int dfn[maxn], low[maxn], cut[maxn], stack[maxn], st, root, dfs_clock = 1, cc;
inline void tarjan(int cur) {
    stack[st++] = cur;
    dfn[cur] = low[cur] = dfs_clock++;
    if(cur == root && head[cur] == -1) {
        dcc[cc++].push_back(cur);
        return;
    }
    int flag = 0;
    for(int i = head[cur]; i != -1; i = nex[i]) {
        if(!dfn[ver[i]]) {
            tarjan(ver[i]);
            low[cur] = min(low[cur], low[ver[i]]);
            if(dfn[cur] <= low[ver[i]]) {
                flag++;
                if(cur != root || flag == 2) cut[cur] = 1;
                int t;
                do {
                    t = stack[(st--)-1];
                    dcc[cc].push_back(t);
                }while(t != ver[i]);
                dcc[cc++].push_back(cur);
            }
        } else 
            low[cur] = min(low[cur], dfn[ver[i]]);
    }
}



int main() {
    int n, m, u, v, cases = 1;
    while(scanf("%d", &m) == 1 && m) {
        memset(head, -1, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(cut, 0, sizeof(cut)); 
        n = cc = tot = 0;
        while(m--) {
            scanf("%d %d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        n = max(n, u); n = max(n, v);
        for(int i = 1; i <= n; i++)
            if(!dfn[i]) {
                st = 0;
                root = i, tarjan(i);
            }
        if(cc == 1) {
            printf("Case %d: %d %lld\n", cases++, 2, (long long)dcc[0].size() * (dcc[0].size()-1) / 2);
            dcc[0].clear();
            continue;
        }
        long long num = 0, sor = 1;
        for(int i = 0; i < cc; i++) {
            int ncut = 0;
            for(vector<int>::iterator it = dcc[i].begin(); it != dcc[i].end(); it++)
                if(cut[*it]) ncut++;
            if(ncut == 1) {
                num++; sor *= (dcc[i].size()-ncut);
            }
            dcc[i].clear();
        }
        printf("Case %d: %lld %lld\n", cases++, num, sor);
    }	return 0;

}
```
此外，本题三倍经验：SP16185 p3225  
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)

---

## 作者：carp_oier (赞：2)

# advertisement

这位靓仔，你都来我这里看题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17727736.html)看一看呢。

# the description of problem

（我看的是 PDF 里面的原题所以这里描述会和题目不一样，但是大意一致）

给定一个未必连通的无向图，问最少在几个点设置出口，可以保证任意一个点坍塌后，工人们仍然可以从出口逃生，同时问设置最少出口的方案数量。

# thoughts & solution

我们可以知道每个连通块之间是相互独立的，对于每个连通块间的答案，是互不影响的，所以说每个连通块之间的答案是要靠乘法原理维护。

（下面都用 $res$ 来记录我们需要设置的出口数量，$num$ 来表示我们总共的方案数）

这个时候我们考虑每个连通块：

1. 如果这个连通块中没有割点，这个时候我们只需要在这个连通块内部随意放置两个出口就可以保证每个点都能到达出口。我们还需要分类讨论:
	- 如果这个连通块内只有一个点，我们的答案就将变成 
    	$$res \gets res + 1$$ 
	- 我们这个时候记录答案就是（记这个连通块内部有 $cnt$ 个点）
		$$res \gets res + 2, num \gets num * C_{cnt} ^ {2} $$

2. 如果这个连通块中只有一个割点，我们需要对它进行一个缩点的操作，这个时候，我们的一个割点会一分为二，分别到它这个割点所连接的两个连通分量中，这个时候我们只需要保证里面有一个出口就行了，方案数则是这个左右两个分量中个自得数量（记为 $cnt$）
$$res \gets res + 1, num \gets (cnt - 1)  * num$$

3. 如果这个连通块有两个或两个以上得割点，我们这个时候则可以证明它一定能去往别得连通块，所以说不会对结果造成贡献。证明放在后面。

# Proof

1. 如果在割点坍塌，在缩完点之后必定是一棵树，而且我们在每一个之前只有一个割点的连通图里面放置了一个出口，所以，在这棵树的最下面必定会有叶子节点，这个叶子节点就会救活这棵树。

2. 如果是连接了一个割点的 V-DCC 坍塌某一个点，我们在删除这个坍塌的点之后，我们这个图还是连通的，而且因为这个图上面还有一个割点，我们就可以通过这个割点走向另外一个安全的出口。

3. 如果是连接了两个割点的 V-DCC 坍塌了某一个点，我们同样可以让这个图里面的点去到其他出口。

综上，证毕

# CODE TIME

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll

const ll N = 5e4 + 10, M = 1e5 + 10;

ll n, m;

ll tot, ne[M], e[M], h[N];

ll dfn[N], low[N], timestamp;

ll stk[N], top, dcc_cnt, root;

vector<ll> dcc[N];

bool cut[N];

inline void add(ll a, ll b)
{
    ne[++tot] = h[a], h[a] = tot, e[tot] = b;
}

inline void tarjan(ll u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;
    
    if(root == u && h[u] == -1)
    {
        dcc_cnt ++, dcc[dcc_cnt].push_back(u);
        return ;
    }

    ll cnt = 0;
    for(rl i=h[u]; ~i; i = ne[i])
    {
        ll v = e[i];
        if(!dfn[v]) 
        {
            tarjan(v), low[u] = min(low[u], low[v]);
            if(dfn[u] <= low[v])
            {
                cnt ++;
                if(u != root || cnt > 1) cut[u] = true;
                ++ dcc_cnt;
                ll ele;
                do {
                    ele = stk[top --];
                    dcc[dcc_cnt].push_back(ele);
                } while(ele != v);
                dcc[dcc_cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int main()
{
    ll T = 1;
    while(cin >> m, m)
    {
        for(rl i=1; i <= dcc_cnt; ++ i) dcc[i].clear();
        tot = n = timestamp = top = dcc_cnt = 0;
        memset(h, -1, sizeof h), memset(dfn, 0, sizeof dfn), memset(cut, 0, sizeof cut);
        
        while(m -- )
        {
            ll a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            add(a, b), add(b, a);
        }
        
        for(root = 1; root <= n; ++ root)
            if(!dfn[root])
                tarjan(root);
                
        ll res = 0, num = 1;
        
        for(rl i=1; i <= dcc_cnt; ++ i)
        {
            ll cnt = 0;
            for(rl j : dcc[i])
                if(cut[j]) 
                    cnt ++ ;
                
            if(cnt == 0) 
            {
                if(dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                else res ++ ;
            }
            else if(cnt == 1) res ++, num *= dcc[i].size()- 1;
        }
        
        printf("Case %lld: %lld %lld\n", T ++, res, num);
    }
    return 0;
}
```

---

## 作者：Yoimiyamwf (赞：1)

# 题目大意
给定一张连通图，选择其中任意个点涂黑，使得无论删除图中的哪一个点和与之相连的边，剩余的点都与至少一个涂黑的点连通，求所需涂黑的点数和方案数。
# 分析
首先，题目要求“删除一个点和与之相连的边”，由此不难发现本题是一个点双连通分量。

那么，所需涂黑的点数为 $ans$，涂色方案数为 $sum$，缩点后每个分量内的点数为 $|S|$，根据每个连通分量相连的割点数进行分类讨论：

### 无割点

此时这一连通分量孤立，那么只要选择其中任意2个点涂黑，则无论其中哪个点被删除，分量内都必然含有另一个涂黑的点，所以这一情况下， $ans \gets ans+2$。由于选点方式有 $C_{|S|}^{2} =\frac{ (|S|-1)\times|S|}{2}$ 种，则 $sum \gets sum\times\frac{ (|S|-1)\times|S|}{2}$。

### 一个割点

此时只需要涂黑分量内任意一点。分量内部任意未涂黑点被删除后，分量内部仍然连通，则剩余的点仍与被涂黑的点连通；而被涂黑的点被删除后，剩余的点通过割点与相邻的分量连通，因此可以与其他分量内部的黑点连通。所以，这一情况下，$ans \gets ans+1$。由于选点方式有 $|S|$ 种，则 $sum \gets sum×|S|$。

### 两个割点

无论删除分量内的哪一个点，分量仍可通过剩余的割点与其他分量相连。因此，这一情况下不需要在分量内部额外涂黑任何点，故无需更新答案。

另外需要额外注意的一点是，本题答案范围为 $[0,2^{64}]$，需要使用 unsigned long long 记录方案数。

# 代码

```cpp
#include <bits/stdc++.h>
#define in inline
#define rint register int
#define r(a) runtimerror(a)
#define w(a) wronganswer(a)
#define wl(a) wronganswer(a);putchar('\n')
#define ws(a) wronganswer(a);putchar(' ')
using namespace std;
typedef unsigned long long ll;
ll num;
int ans,sum,n,m,u,v,tot,head[100010],root,tmp,dfn[100010],low[100010],dcnt;
bool cut[100010];
stack <int> s;
vector <int> dcc[100010];
void wronganswer(int a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) wronganswer(a/10);
	putchar(a%10^48);
}
template <typename t> in void runtimerror(t &a){
	char ch=getchar();
	t x=1,f=0;
	while(!isdigit(ch)){
		if(ch=='-') x=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		f=(f<<3)+(f<<1)+(ch^48);
		ch=getchar();
	}
	a=x*f;
}
struct Edge{
	int to,nex;
}edge[100010];
in void add_edge(int from,int to){
	edge[++tot]=(Edge){to,head[from]};
	head[from]=tot;
}
void tarjan(int id){ //tarjan缩点
	dfn[id]=low[id]=++tmp;
	s.push(id);
	if(id==root&&!head[id]){
		dcc[++dcnt].push_back(id);
		return;
	}
	int cnt=0;
	for(rint i=head[id];i;i=edge[i].nex){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[id]=min(low[id],low[edge[i].to]);
			if(dfn[id]<=low[edge[i].to]){
				cnt++;
				if(id!=root||cnt>1) cut[id]=true;
				int x;
				dcnt++;
				do{
					x=s.top();
					dcc[dcnt].push_back(x);
					s.pop();
				}while(x!=edge[i].to);
				dcc[dcnt].push_back(id);
				
			}
		}else low[id]=min(low[id],dfn[edge[i].to]);
	}
}
in void clear(){
	memset(dcc,0,sizeof(dcc));
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(cut,0,sizeof(cut));
	tot=tmp=ans=n=dcnt=0;
	num=1;
}
int main(){
	while(r(m),m){
		clear(); //多测不清空，爆零两行泪
		for(rint i=1;i<=m;i++){
			r(u),r(v);
			add_edge(u,v);
			add_edge(v,u);
			n=max(n,max(u,v));
		}
		for(rint i=1;i<=n;i++){
			if(!dfn[i]){
				root=i;
				tarjan(i);
			}
		}
		for(rint i=1;i<=dcnt;i++){ //分情况统计答案
			int answ=0;
			for(rint j=0;j<dcc[i].size();j++){
				if(cut[dcc[i][j]]) answ++;
			}
			if(!answ){
				if(dcc[i].size()>1) ans+=2,num*=dcc[i].size()*(dcc[i].size()-1)/2;
				else ans++;
			}
			else if(answ==1) ans++,num*=dcc[i].size()-1;
		}
		printf("Case %d: %d %llu\n",++sum,ans,num);
	}
	return 0;
}
```


---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA1108)

# 题意
在一个无向图上选择尽量少的点涂黑，使得删除任意一个点后，每个连通分量里都至少有一个黑点（多组数据）。

# 正文

观察题意，发现这是个 Tarjan 求点双连通分量的板子。

考虑在求点双连通分量的时候把割点顺便求出来，令第 $i$ 个点双连通分量的大小为 $size_i$，然后进行分类讨论：

  - 当第 $i$ 个点双连通分量中没有割点时，符合题意则需要涂黑两个点，方案总数增加 $C_{size_i}^2=\frac{size_i!}{{(size_i-2)}!×2!}=\frac{size_i(size_i-1)}{2}$。
  
    - 如图，$(1,2,3,4)$ 为本图的点双连通分量，且没有割点，则在 $(1,2,3,4)$ 中任选两个点涂黑。
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/57gxso7j.png)
    
  - 当第 $i$ 个点双连通分量中有 $1$ 个割点时，若符合题意则需要涂黑一个点（不能将割点涂黑），方案总数增加 $C_{size_i-1}^1=\frac{(size_i-1)!}{{(size_i-2)}!×1!}=size_i-1$。
  
    - 如图，$(1,2,6,3,5),(1,4)$ 为本图的两个点双连通分量，且 $1$ 为本图的割点，则在 $(2,6,3,5),(4)$ 中各任选出一个点涂黑。
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/ayh8dj8x.png)
  - 当第 $i$ 个点双连通分量中的割点个数大于 $1$ 时，不需要涂黑。
  
    - 如图，点双连通分量 $(2,5,6)$ 中有两个割点，则不需要涂黑。
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/ugmiq2pl.png)
    - 证明：当割点删除后，可以通过另一个割点达到其他点双连通分量。
    
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
struct node
{
	ll next,to;
}e[400001];
vector<ll>v_dcc[400001];
stack<ll>s;
ll head[400001],dfn[400001],low[400001],cut[400001],cnt,tot,ans;
void add(ll u,ll v)
{
	cnt++;
	e[cnt].next=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void tarjan(ll x,ll fa)
{
    ll i,k=0,son=0;
    tot++;
    dfn[x]=low[x]=tot;
    s.push(x);
    for(i=head[x];i!=0;i=e[i].next)
    {
        if(dfn[e[i].to]==0)
        {
            tarjan(e[i].to,fa);
            low[x]=min(low[x],low[e[i].to]);
            if(low[e[i].to]>=dfn[x])
            {
                son++;
                if(x!=fa||son>=2)//求割点
                {
                    cut[x]=1;
                }
                ans++;
                v_dcc[ans].clear();//初始化
                v_dcc[ans].push_back(x);
                while(e[i].to!=k)
                {
                    k=s.top();
                    v_dcc[ans].push_back(k);
                    s.pop();
                }                
            }
        }
        else
        {
           low[x]=min(low[x],dfn[e[i].to]);
        }
    }
}
int main()
{
	ll n,m,i,j,u,v,sum=0,num,len,ans1,ans2;
    while(cin>>m)
    {
        if(m==0)
        {
            break;
        }
        else
        {
            n=0;
            sum++;
            tot=ans=cnt=ans1=0;
            ans2=1;
            while(s.empty()==0)
            {
                s.pop();
            }
            memset(e,0,sizeof(e));//多测不清空，爆零两行泪
            memset(low,0,sizeof(low));
            memset(dfn,0,sizeof(dfn));
            memset(cut,0,sizeof(cut));
            memset(head,0,sizeof(head));
            for(i=1;i<=m;i++)
            {
                cin>>u>>v;
                n=max(n,max(u,v));//n的个数需要自己求
                add(u,v);
                add(v,u);
            }
            for(i=1;i<=n;i++)
            {
                if(dfn[i]==0)
                {
                    tarjan(i,i);
                }
            }
            for(i=1;i<=ans;i++)
            {
                num=0;
                len=v_dcc[i].size();
                for(j=0;j<len;j++)
                {
                    if(cut[v_dcc[i][j]]==1)//判断是否是割点
                    {
                        num++;
                    }
                }
                if(num==0)//如果没有割点
                {
                    ans1+=2;
                    ans2*=(len-1)*len/2;
                }
                if(num==1)//如果有一个割点
                {
                    ans1++;
                    ans2*=len-1;
                }
            }
            cout<<"Case "<<sum<<": "<<ans1<<" "<<ans2<<endl;
        }
    }
    return 0;
}
```
___
# 后记
~~三倍经验~~ [luoguP3225 [HNOI2012] 矿场搭建](https://www.luogu.com.cn/problem/P3225) | [SP16185 BUSINESS - Mining your own business](https://www.luogu.com.cn/problem/SP16185) | [UVA1108 Mining Your Own Business](https://www.luogu.com.cn/problem/UVA1108)

---

## 作者：rsdbk_husky (赞：1)

## 零. 安利：

[博客食用效果更佳。](https://rsdbkhusky.github.io/2021/08/18/%E7%9F%BF%E5%9C%BA%E6%90%AD%E5%BB%BA/)

## 一. 思路

#### 0. 前置知识：割点，v-dcc（再说一遍，无向图有的是双连通分量，没有强连通分量一说！）。

这里推荐几道模板题，学习 Tarjan 建议把他们都 A 了：

 1. dcc 割边：[Luogu](https://www.luogu.com.cn/problem/T103481) [Std](https://rsdbkhusky.github.io/2021/07/21/割边/)。

 2. dcc 割点：[Luogu](https://www.luogu.com.cn/problem/P3388) [Std](https://rsdbkhusky.github.io/2021/07/21/割点/)。

 3. e-dcc：[Luogu](https://www.luogu.com.cn/problem/T103489) [Std](https://rsdbkhusky.github.io/2021/07/21/边双连通分量/)。

 4. v-dcc：[Luogu](https://www.luogu.com.cn/problem/T103492) [Std](https://rsdbkhusky.github.io/2021/07/21/点双连通分量/)。

 5. scc：[Luogu](https://www.luogu.com.cn/problem/B3609) [Std](https://rsdbkhusky.github.io/2021/07/21/强连通分量/)。

 6. scc 缩点：[Luogu](https://www.luogu.com.cn/problem/P3387)。

 （没有找到双连通分量的缩点模板，知道的小伙伴欢迎在评论中补充）

　[蓝书](https://baike.baidu.com/item/算法竞赛进阶指南/57610153?fr=aladdin)上这部分讲的很详细。

那么接下来我们以这个图为例讲解此题：

![](https://cdn.luogu.com.cn/upload/image_hosting/q8jw0mzr.png)

命名三个双连通分量为：A，B，C。红色的为割点。

![](https://cdn.luogu.com.cn/upload/image_hosting/4unqjo02.png)

#### 1. 一个包含一个割点的双连通分量（A，C）

1. 非割点坍塌：

    没有关系，比如 A 中 1 号点坍塌，3 号点中的人可以来到割点（2 号点），然后去往其他双连通分量中的出口逃生。

2. 割点坍塌：

     比如 2 号塌了，1 号和 3 号中就必须有一个出口。

综上，对于包含一个割点的双连通分量，需要建 $1$ 个出口，方案数为 $\operatorname{size} - 1$。（$\operatorname{size}$：该 dcc 大小）。


#### 2. 一个包含两个及以上个割点的双连通分量（B）

1. 非割点坍塌：（同 1 - 1）

2. 割点坍塌：

   这次情况不同了，塌了一个割点，还有至少一个割点可以供里面的工人离开这个 dcc。

综上，对于包含两个及以上个割点的双连通分量，根本无需建出口。

看到这里，很多人有 **问题** 了：如果全是包含两个及以上个割点的 dcc，所有人总想着往其他 dcc 跑，其他 dcc 却也没出口怎么办。那么恭喜你，这种情况根本不可能成立。比如有一圈像 B 一样的 dcc 拼在一起：

![](https://cdn.luogu.com.cn/upload/image_hosting/juaesz6o.png)

但再仔细看，一当形成环，割点就直接没有了，也就是说上图 4 个红色点都应该是白色的，这就是第三种情况（待会要讲）。

而如果环不合拢，两端必然存在包含一个割点的 dcc，也就自然能成功逃离：

![](https://cdn.luogu.com.cn/upload/image_hosting/9qprq8pm.png)

#### 3. 环

如果是一个环，看上去建一个出口就行了，但还要考虑出口坍塌的情况！所以需要建 $2$ 个出口。方案数为 $\operatorname{C}^2_{\operatorname{size}} = \dfrac{\operatorname{size} \times (\operatorname{size} - 1)}{2}$。

#### 4. 最终结果

1. 出口数：将所有 dcc 建的出口数相加。
2. 方案数：将所有 dcc 的方案数相乘。（乘法原理）

## 二. 代码

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define re register
#define int long long
const int MAXn = 5e4;
const int MAXm = 3e5;

template <class T>
inline void read(T& a) {
	re char c; while (c = getchar(), c < '0' || c > '9'); re T x(c - '0'); while (c = getchar(), c >= '0' && c <= '9') { x = x * 10 + c - '0'; }a = x;
}

int head[MAXn + 10], cntnex, nex[MAXm * 2 + 10], to[MAXm * 2 + 10];
void Insert(int u, int v) {
	nex[++cntnex] = head[u];
	head[u] = cntnex;
	to[cntnex] = v;
}

int top, stk[MAXn + 10], cntdcc;
vector<int> dcc[MAXn + 10];
bool is[MAXn + 10];
int root, cntdfs, dfs[MAXn + 10], low[MAXn + 10];

void Init() {
	cntnex = top = root = cntdfs = 0;
	memset(head, 0, sizeof(head));
	memset(nex, 0, sizeof(nex));
	memset(to, 0, sizeof(to));
	memset(stk, 0, sizeof(stk));
	memset(is, 0, sizeof(is));
	memset(dfs, 0, sizeof(dfs));
	memset(low, 0, sizeof(low));
	for (re int i = 1; i <= cntdcc; ++i) {
		dcc[i].clear();
	}
	cntdcc = 0;
}

void Tarjan(int cur) {
	int times = 0;
	dfs[cur] = low[cur] = ++cntdfs;
	if (!head[cur]) {
		++cntdcc;
		dcc[cntdcc].push_back(cur);
		return;
	}
	stk[++top] = cur;
	for (re int i = head[cur]; i; i = nex[i]) {
		if (!dfs[to[i]]) {
			Tarjan(to[i]);
			low[cur] = min(low[cur], low[to[i]]);
			if (dfs[cur] <= low[to[i]]) {
				++times;
				if (cur != root || times >= 2) {
					is[cur] = 1;
				}
				++cntdcc;
				int instk;
				do {
					instk = stk[top--];
					dcc[cntdcc].push_back(instk);
				} while (instk != to[i]);
				dcc[cntdcc].push_back(cur);
			}
		}
		else {
			low[cur] = min(low[cur], dfs[to[i]]);
		}
	}
}

int n, m;
signed main() {
	int T = 0;
	while (~scanf("%lld", &m)) {
		if (m == 0) {
			break;
		}
		++T;
		n = 0;
		Init();
		for (re int i = 1, u, v; i <= m; ++i) {
			read(u), read(v);
			n = max(n, u); n = max(n, v);
			if (u == v) {
				continue;
			}
			Insert(u, v); Insert(v, u);
		}
		for (re int i = n; i; --i) {
			if (!dfs[i]) {
				root = i;
				Tarjan(i);
			}
		}
// 除核心以外的都是纯板子
// ---------------核心---------------
		int ans1 = 0, ans2 = 1;
		for (re int i = 1; i <= cntdcc; ++i) {
			int cnt = 0;
			for (re vector<int>::iterator j = dcc[i].begin(); j != dcc[i].end(); ++j) {
				if (is[*j]) {
					++cnt;
				}
			}
			if (cnt == 1) {
				++ans1;
				ans2 *= dcc[i].size() - 1;
			} else if (cnt == 0) {
				ans1 += 2;
				ans2 *= dcc[i].size() * (dcc[i].size() - 1) / 2;
			}
		}
// ---------------核心---------------
		printf("Case %lld: %lld %lld\n", T, ans1, ans2);
	}
}
```

---

## 作者：SUNCHAOYI (赞：1)

将题目进行转化：在图中安装若干个太平井后，使得任意删除一个**点**，每个**点双连通分量**中都之后有一个太平井。

由题意可知，安装太平井，肯定与割点有关。因此，我们先求出无向图中的割点。

```cpp
void dfs (int u,int fa)
{
	low[u] = dfn[u] = ++times;//时间戳 
	int child = 0;
	for (int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if (!dfn[v])
		{
        ++child;
			dfs (v,u);
			low[u] = min (low[u],low[v]);
			if (dfn[u] <= low[v])//为割点 
				iscut[u] = 1;
		}
		else if (v != fa && dfn[v] < dfn[u])//反向边 
			low[u] = min (low[u],dfn[v]);
	}
	if (fa < 0 && child == 1) iscut[u] = 0;//特殊情况 
}
```

把所有边双向存入后，调用 `dfs (1,-1)`，然后根据 `iscut[i]` 的布尔值判断该点是否为割点。

---

点双连通分量与割点数量的关系决定了安装太平井的数量，所以我们在求割点的同时也要**记录每一个点双连通分量**。

这里我们可以使用 `set <int> 变量名`，在记录每一个元素的同时也可以将相同的元素去除。在 `dfs (u,fa)` 函数的基础上修改一下即可，结合注释，代码应该很好理解。

```cpp
void dfs (int u,int fa)
{
	low[u] = dfn[u] = ++times;//时间戳 
	int child = 0;
	for (int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if (!dfn[v])
		{
			++child;
			st.push (i);//加入元素 
			dfs (v,u);
			low[u] = min (low[u],low[v]);
			if (dfn[u] <= low[v])//为割点 
			{
				iscut[u] = 1;
				++bcc_cnt;//点双连通分量的数量 
				while (1)
                {	
                    int x = st.top ();st.pop ();
                    con[bcc_cnt].insert (dis[x]);//两条相邻的边加入其中 
                    con[bcc_cnt].insert (to[x]);
                    if (dis[x] == u && to[x] == v) break;//退出循环的条件        
                }
			}
		}
		else if (v != fa && dfn[v] < dfn[u])//反向边 
		{
			st.push (i);//加入元素 
			low[u] = min (low[u],dfn[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = 0;//特殊情况 
}
```

----

最后就是答案的求解了，对于一个点双连通分量有以下的情况：

- 全部连通，割点数为 $0$。此时若连接点坍塌，需要 $2$ 个太平井才能符合要求。设连通块大小为 $sz$，则任意选择两个点的方案数为 $C_{sz}^{2} = \frac{sz \times (sz - 1)}{2}$。

- 割点数为 $1$。此时若连接点坍塌，只需要 $1$ 个太平井才能符合要求。设连通块大小为 $sz$，则任意选择一个的方案数为 $sz - 1$。

- 割点数大于 $1$。此时易得若缺少一个割点，该点双连通分量仍然联通，因此**不需要安装**。

部分代码如下，**注意需要使用乘法原理，且需要注意变量的类型。**

```cpp
ull ans1 = 0,ans2 = 1;//注意类型 
for (int i = 1;i <= bcc_cnt;++i)
{
	ull num = 0,sz = 0;
	for (set <int> :: iterator j = con[i].begin ();j != con[i].end ();++j)
	{
		++sz;//该连通块的大小 
		if (iscut[*j]) ++num;//割点数量 
	}	
	if (num == 0) ans1 += 2,ans2 *= sz * (sz - 1) / 2;//为 0 的情况 
	else if (num == 1) ++ans1,ans2 *= (sz - 1);//为 1 的情况 
}
```

----

### 写在最后的话：

1. 由于为多组数据，每次得出答案后记得**初始化**。

2. 若有问题，及时提出，记得**点个赞**再走哦qwq！

---

## 作者：ctq1999 (赞：1)

调了有一段时间的题。调到最后发现有个变量没初始化成 $0$。

$\text{P3225}$ 里没说点是连续编号的，但 $\text{pdf}$ 里面说了。

用语可能不太准确或不清楚的，恳请读者指出，谢谢。

## 题意

给定一个有 $m$ 条边，$n$ 个节点的多个点双联通分量。当去掉其中任意一个点时，其他点都需要有一条到逃生口节点的路径。逃生口节点可以是 $n$ 个节点中任意一个。求出最少需要多少个逃生口节点和在最小化逃生口节点时，有多少种选取逃生口节点的方案。

## 思路

先讨论其中一个点双联通分量。

去掉其中一个节点 $x$ 时，只有两种情况：

1. 点双联通分量依然是点双联通分量。

2. 点双联通分量变成多个子点双联通分量。

对于第一种情况，剩下的任意一个点都有到其他任意一个点的路径，剩余的节点需要有一个到逃生口节点的路径。

对于第二种情况，这个去掉的点 $x$ 也叫做 [割点](https://www.luogu.com.cn/problem/P3388)。每个子点双联通分量都要选取一个逃生口节点。

而子联通分量中，也可能存在割点 $y$。所以每个子子联通分量也要选取一个逃生口节点。但有一个子子联通分量是包含 $x$ 这个点的，也就是说，当这个子联通分量中有一个点被去掉后，包含 $x$ 的子子联通分量有到其他子联通分量中的逃生口节点的路径，所以这个子子联通分量就不需要选取逃生口节点了。

那么也就是说，一个点双联通分量的所有割点，会把这个点双联通分量分成多个子联通分量。

1. 当一个子联通分量只包含一个割点时，意味着必须在其中任意选取一个不是割点的点作为逃生口节点。

2. 当一个子联通分量包含若干个割点时，不用选取逃生口节点，因为这个子联通分量任意一个点被去掉，剩下的点都有到其他子联通分量的点的路径。

- 当一个点双联通分量没有割点时，必须选取任意两个点作为逃生口节点，因为一个逃生口节点会被去掉。

那么选取个数的最小值就可求了。

对于方案数，设该子联通分量的节点数为 $size$：

1. $size-1$ 个不同的选取方法。

2. $0$ 个不同的选取方法。

- $\frac{size\times(size-1)}{2}$ 个不同的选取方法。

再利用乘法原理，就可以得到方案数了。

## 实现

割点可以用 $\text{Tarjan}$ 求。不会的可以去[P3388](https://www.luogu.com.cn/problem/P3388) 学习。

然后需要求子联通分量的节点数和包含的割点数。可以用 $\text{dfs}$ 进行遍历。

时间复杂度 $O(Tn)$，$T$ 是数据组数。每个点没被遍历的点要进行 $\text{dfs}$，而 $\text{dfs}$ 每个点只会遍历一遍，所以每组数据的复杂度是 $O(n)$ 的。

## 代码

很多细节参考了 $\text{yyb}$ 的代码，不得不说，你队爷还是你队爷。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define y1 caibictq
#define P pair<int, int>
#define fi first
#define se second

using namespace std;

const int MAXN = 200010;
const int MAXM = 100010;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, k;
int tot, cnt, num, now;
ll ans1, ans2;

int read() {
	int f = 1, s = 0;
	char ch = getchar();
	while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while ('0' <= ch && ch <= '9') {s = (s << 1) + (s << 3) + ((int)ch ^ 48); ch = getchar();}
	return s * f;
}

int a[MAXN], b[MAXN];
int head[MAXN];
int dfn[MAXN], low[MAXN], cut[MAXN];
int vis[MAXN];

void Init() {
	tot = cnt = num = now = ans1 = n = 0;
	ans2 = 1;
	memset(head, 0, sizeof(head));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(cut, 0, sizeof(cut));
	memset(vis, 0, sizeof(vis));
	return;
}


struct edge {
	int to, next;
}e[MAXN << 1];

void add_edge(int u, int v) {
	e[++tot].to = v;
	e[tot].next = head[u];
	head[u] = tot;
	return;
} 

void Tarjan(int u, int rt) {
	dfn[u] = low[u] = ++cnt;
	int son = 0;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (!dfn[v]) {
			Tarjan(v, rt);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != rt) cut[u] = 1;
			if (u == rt) ++son;
		}
		low[u] = min(low[u], dfn[v]);
	}
	if (u == rt && son >= 2) cut[u] = 1;
	return;
}

void dfs(int u) {
	vis[u] = now;
	++num;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (cut[v] && vis[v] != now) {
			++cnt;
			vis[v] = now;
			continue;
		}
		if (!vis[v]) dfs(v);
	}
	return;
}
int main() {
	int T = 0;//就是这个/fn
	while (scanf("%d", &m) && m) {
		++T;
		Init();
		for (int i = 1, u, v; i <= m; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v); add_edge(v, u);
			n = max(n, max(u, v));
		}
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) Tarjan(i, i);
		}
		for (int i = 1; i <= n; i++) {
			if (vis[i] || cut[i]) continue;
			num = 0;
			cnt = 0;
			++now;
			dfs(i);
			if (cnt == 0) {
				ans1 += 2;
				ans2 *= 1ll * num * (num - 1) / 2;
			}
			if (cnt == 1) {
				ans1 += 1;
				ans2 *= num;
			}
		}
		printf("Case %d: %lld %lld\n", T, ans1, ans2);
	}
	return 0;
}

```






---

## 作者：noall (赞：1)

做此题，需要知道点双连通；知道点双连通，就要知道割顶

### 割顶

#### 什么是割点？

> 对于无向图$G$，如果删除某个点$u$后，连通分量数目增加，称$u$为图的关节点或**割顶**。对于连通图，割顶就是删除之后使图不再联通的点。

#### 怎么求？

##### DFS树

学习求割顶之前要先学习dfs树。

dfs树就是将有向连通图转化为搜索树，节点以dfs序排列。

######  树上的一些定义：

>- $dfn$：时间戳，结点被访问的次序。（起点为$1 $，每次搜索$+1$）
>
>- $low$：结点所能到达的最小$dfn$值 。
>
>- 树边：$dfs$树上应有的边，又父节点指向子节点 。
>
>- 返祖边：$dfs$树上不应有的边，且该边由子辈节点指向父辈节点。（注意这里不一定是父子节点） 
>
>- 横叉边：连接的两个点无父子辈关系。（注意横叉边一定由$dfn$值大的节点指向$dfn$值小的节点，否则它是树边）
>-  图中$5$节点的$low$值为$5$而不是$4$，是因为横插边$(5,6)$会被忽略，看不懂的话，等到下面讲到处理横叉边的时候再理解即可。

我要引用**冯巨佬**的一张图，来举例：

![006oZqiLly1g0o78oufhyj30hk0kdjui.jpg](https://img.langlangago.xyz/2019/04/06/5ca88b4dd085e.jpg)

学完大法师树之后，我们就可以学习求割顶了

##### 思路

为了方便叙述，我们只讨论连通图。在这样的情况下，大法师森林一定只有一棵树。那么树根是不是割顶呢？不难发现，**当且仅当它有两个或更多的子节点**时，它才是割顶——无向图只有树边和反向边，不存在跨越两棵子树的边。对于其他点，我们有下面的定理：

> 定理：在无向联通图G的大法师树中，非根节点u是G的割顶当且仅当u存在一个子节点v，使得v及其所有后代都没有反向边连回u的**祖先**。

可以看下图，很容易看出u是一个割点。

![1.jpg](https://img.langlangago.xyz/2019/07/13/5d292b28875c8.jpg)

可以看下图，很容易看出u不是一个割点。

![2.jpg](https://img.langlangago.xyz/2019/07/13/5d292deac708d.jpg)

**综上，很容易看出，若$low_v \ge dfn_u$，则满足定理中的条件，$u$即为割顶。**

如果不知道$dfn$和$low$是什么，就去看看上面的大法师树吧。

如果还是不理解，就多读几遍！

#### 模板code

```cpp
//模板：https://www.luogu.org/problemnew/show/P3388
const……maxn1……
const……maxn2……

struct edge{……}map[maxn2<<1];

int n,m,dfn[maxn1],low[maxn1],tot;bool iscut[maxn1];
int cnt,head[maxn1];

inline int read(){……}

inline void add(int x,int y){……}

void dfs(int x,int fa){//x是当前节点，fa是当前节点的父亲节点。规定树根的父亲节点是0.
    int child=0;//当前点的子节点数
    dfn[x]=low[x]=++cnt;//时间戳更新
    for(int i=head[x];i;i=map[i].next){
        int y=map[i].to;
        if(!dfn[y]){//如果没有访问过
            child++;//子节点数+1
            dfs(y,x);//向下走
            low[x]=std::min(low[x],low[y]);//更新low值
            if(low[y]>=dfn[x]) iscut[x]=true;//如果符合定理，那么x就是割顶
        }
        else if(y!=fa) low[x]=std::min(low[x],dfn[y]);//如果访问过了，更新low值
    }
    if(!fa&&child==1) iscut[x]=false;//当且仅当它有两个或更多的子节点时，树根才是割顶
    return;
}

int main(){
    n=read(),m=read();
    for(register int i=1;i<=m;i++){
        int x=read(),y=read();
        add(x,y),add(y,x);//双向边
    }
    cnt=0;
    for(register int i=1;i<=n;i++)
        if(!dfn[i]) dfs(i,0);//将点全部遍历一遍
    for(register int i=1;i<=n;i++){
        if(iscut[i]) ++tot;//如果是割顶，总数tot++
    }
    printf("%d\n",tot);
    for(register int i=1;i<=n;i++){
        if(iscut[i]) printf("%d ",i);//将是割点的点输出
    }
    return 0;
}
```

### 点双连通分量

来自冯巨佬……

> 学会了求解割顶，求出BCC就在容易不过了。——冯巨佬

维护一个栈，栈内保存每一次走过的边（一定保存边，因为两个不同的双连通子图可能有交点，但一定没有交边但）。每当发现割顶时，出栈，直到发现当前出栈的边恰好是连接割顶与判定它的子节点的边。则出栈的所有边同属一个双连通子图，这些边的端点也同属一个双连通子图。

代码如下：
因为回溯到根的时候，剩余栈内元素一定是一个双连通子图，故先出栈再特判根。

#### 模板code

```cpp
//from 冯巨佬，增加注释
const int CP=1e3+3;
const int CE=CP*CP;

//边表
class fs{
    public:
        int from,to,nxt;
}E[CE];
int hd[CP],cnt=0;
void add(int x,int y){……}

//bcc
int dfn[CP],low[CP];
int idx=0;

int bel[CP],bcnt=0; //每个点所属的bcc编号，为-1则表示该点是割顶（割顶同时属于两个bcc，所以它的bel无意义）
int stack[CE],top=0;

void tarjan(int cur,int prv)
{
    int child = 0; 
    
    dfn[cur] = low[cur] = ++idx; 
    
    for(int k=hd[cur]; k; k=E[k].nxt)
    {
        int to=E[k].to;
        
        if(!dfn[to]) 
        {
            child++;
            stack[++top]=k; //入栈
            tarjan(to,cur); //向下搜索
            
            low[cur] = min(low[cur], low[to]); 
            
            if(low[to] >= dfn[cur]) //是割顶
            {
                  int pos;
                  ++bcnt;
                  while(true)
                  {
                      pos=stack[top--]; //出栈
                      bel[E[pos].from] = bel[E[pos].to] = bcnt;
                      if(E[pos].from==cur && E[pos].to==to) //到达当前的树边
                           break;//直接退出循环
                  }
                bel[cur] = -1; //标记割顶
            }
        }
        else if(to != prv) low[cur] = min(low[cur], dfn[to]); 
    }
    
    if(!prv && child==1) //处理根
        bel[cur] = bcnt;
}

void bcc() //主求解函数
{
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,0);
}
```

### 题目思路

嗯，基本是一个裸的模板题，简化题意：在一个无向图上选择尽量少的点涂黑，使得删除任意一个点后，每个连通分量里都至少有一个黑点。

我们可以求出所有的连通子图，然后判断其中的割点。

若割点为1，则应当将答案+2。为什么？因为，我们应当考虑存在割点的连通块不是点-双连通。就是说，当割点塌陷后，将会分成两个连通块，这两个连通块不能互相到达。

若割点为0，则应当将答案+1。很容易理解。

对于只有一个割顶的连通块，设它的大小为s，则共有s−1种不同的涂黑方案，根据乘法原理将这些s−1相乘即可。
对于没有割顶的连通块，方案数为s∗(s−1)/2，与前面的相乘即可。

### code

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>

#define int long long
const int maxn=1e5+10;

struct edge{
    int from,to,next;
}map[maxn];

int n,m,dfn[maxn],low[maxn],stk[maxn],top,bcnt,ins[maxn],ans1,ans2,idx;
int cnt,head[maxn];
bool iscut[maxn];
std::vector<int>bcc[maxn];

inline void add(int x,int y){
    map[++cnt]=(edge){x,y,head[x]};
    head[x]=cnt;
    return ;
}

inline void init(){
    ans1=bcnt=idx=n=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,false,sizeof(iscut));
    memset(map,0,sizeof(map));
    memset(stk,0,sizeof(stk));
    memset(head,0,sizeof(head));
    memset(ins,0,sizeof(ins));
    return ;
}

void dfs(int x,int fa){
    dfn[x]=low[x]=++idx;
    int child=0;
    for(int i=head[x];i;i=map[i].next){
        int y=map[i].to;
        if(!dfn[y]){
            child++;
            stk[++top]=i;//栈存边
            dfs(y,x);
            low[x]=std::min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                int pos;
                bcnt++;
                bcc[bcnt].clear();//初始化bcc
                while(true){
                    pos=stk[top--];
                    if(!ins[map[pos].from]){//如果它不在任何一个连通块中
                        ins[map[pos].from]=true;
                        bcc[bcnt].push_back(map[pos].from);
                    }
                    if(!ins[map[pos].to]){
                        ins[map[pos].to]=true;
                        bcc[bcnt].push_back(map[pos].to);
                    }
                    if(x==map[pos].from&&y==map[pos].to) break ;
                }
                iscut[x]=true,ins[x]=false;
            }
        }
        else low[x]=std::min(low[x],dfn[y]);
    }
    if(!fa&&child==1) iscut[x]=false;
    return ;
}

inline int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

signed main(){
    int Case=0;
    while(scanf("%lld",&m)&&m){
        init();
        for(register int i=1;i<=m;i++){
            int x=read(),y=read();
            add(x,y),add(y,x);
            n=std::max(n,std::max(x,y));
        }
        for(register int i=1;i<=n;i++){
            if(!dfn[i]) dfs(i,0);
        }
        ans2=1;
        for(int i=1;i<=bcnt;i++){
            int cut=0,sz=bcc[i].size(); 
            for(int j=0;j<sz;j++) if(iscut[bcc[i][j]]) ++cut;//统计割点数
            if(cut==1) ans1+=1,ans2*=(sz-1);
            if(cut==0) ans1+=2,ans2*=(sz*(sz-1))/2;
        }
        printf("Case %lld: %lld %lld\n",++Case,ans1,ans2);
    }
    return 0;
} 
```

---

## 作者：xbx787 (赞：1)

### 题目大意：给定一个图，要在尽量少的点建立逃生通道，使得任意一个点无法到达时都能保证其他的点能够逃生。

### 对于每组数据，输出最少的通道数和可行方案数。

通过一波手玩可以发现，此题与联通分量有关。关于联通分量，可以看看[这篇博客](https://blog.csdn.net/qq_21125183/article/details/80605172)。对于不会Tarjan的同学可以看看[这篇博客](https://www.cnblogs.com/shadowland/p/5872257.html)。

对于一个联通分量，我们可以发现逃生通道的设立与该联通分量中的割点数量相关。为什么？我们知道割点的性质是当这个点无法到达时，图就会变得不连通。也就是说割点可到达时联通分量中的点是可以通过这个点前往其他分量的。

因此我们用联通分量中割点的数量来给他们分类：

1. 无割点：例如环，则需设 $2$ 个，此时无论哪个无法到达都可以走另外一个。

2. 一个割点：若割点无法到达则必须设 $1$ 个。

3. 两个或以上割点：显然无需逃生通道。

最后统计方案时需按乘法原理（小学奥数）。

上我丑陋的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100100;
int dfn[N],low[N],ind,cnt,num,tot,sum,du,ans1,cases,r,top,vis[N],sta[N],head[N],m;
bool cut[N];
struct node{
	int to,next;
}edge[N<<1];
long long ans2;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
void add(int x,int y){
	edge[++num]=(node){y,head[x]};
	head[x]=num;
}
void tarjan(int x,int fa){
	dfn[x]=low[x]=++ind;
	for (int i=head[x];i;i=edge[i].next){
		int v=edge[i].to;
		if(!dfn[v]){
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x]){//统计割点
				if(x==r)du++;
				else cut[x]=1;
			}
		}
		else if(v!=fa)low[x]=min(low[x],dfn[v]);
	}
}
void dfs(int x){
	vis[x]=sum;
	if(cut[x])return;
	cnt++;
	for (int i=head[x];i;i=edge[i].next){
		int v=edge[i].to;
		if(cut[v] && vis[v]!=sum)num++,vis[v]=sum;
		if(!vis[v])dfs(v);
	}
}
signed main(){
	int n,i,j;
	while(1){
		memset(head,0,sizeof head);//初始化
		memset(vis,0,sizeof vis);
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(cut,0,sizeof cut);
		top=cnt=ans1=sum=m=tot=0;ans2=1;
		n=read(); if(!n)break;
		for (i=1;i<=n;i++){
			int x=read(),y=read();
			m=max(m,max(x,y));
			add(x,y); add(y,x);
		}
		for (i=1;i<=m;i++){
			if(!dfn[i])tarjan(r=i,0);
			if(du>=2)cut[r]=1; du=0;
		}
		for (i=1;i<=m;i++)
			if(!vis[i] && !cut[i]){
				sum++; cnt=num=0;
				dfs(i);
				if(!num)ans1+=2,ans2*=cnt*(cnt-1)/2;//运用乘法原理
				if(num==1)ans1++,ans2*=cnt;
			}
		printf("Case %lld: %lld %lld\n",++cases,ans1,ans2);//一定注意输出格式
	}
	return 0;
}
```

觉得可以请留个赞谢谢。。。

---

## 作者：Patronus (赞：0)

先放个三倍经验：

- [SP16185](https://www.luogu.com.cn/problem/SP16185)

- [本题](https://www.luogu.com.cn/problem/UVA1108)

- [P3225](https://www.luogu.com.cn/problem/P3225)


因为只能删去一个点，我们就可以把原问题分成三种情况考虑：

情况一：如果该联通块内没有割点，即原图的联通性不变（原图中联通的点依旧联通），那么我们在剩下的点中必须选两个点作为答案，因为这样无论删去该连通块内的任意点，仍有一个点可涂黑以保证有解。

情况二：若删除的是割点，则会导致原图分裂成多个连通块，记有 $cnt$ 个，那我们至少在每个连通块内都要涂黑一个点。若删除的不是割点，原图依旧联通，答案与删除割点的相同。

情况三：对于一个仅包含一个割点的双连通分量，我们必须在这个双连通分量内涂黑一个点，但对于包含至少两个割点的双连通分量则不需要，因为只能删除一个点，这个双连通分量会被划分到割点未被删除的部分。

最后我们要特判一下只有一个点的连通块。

我们记 $ans1$ 为需要涂黑点的个数，$ans2$ 为方案数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5,M=1e6+5;
int read(){
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c) && c!='-') c=getchar();
    if(c=='-') f=-1,c=getchar();
    while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
int head[N],ver[M],Next[M],tot;
int dfn[N],low[N];
int c[N];
int n,m,num,root;
ll ans1,ans2,cnt,Cut,group;
bool cut[N],app[N];
void add(int x,int y){
    ver[tot]=y; Next[tot]=head[x]; head[x]=tot++;
}
void init(){//多测一定要清干净
    memset(head,-1,sizeof(head)); tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(c,0,sizeof(c));
    memset(app,0,sizeof(app));
    memset(cut,0,sizeof(cut));
    num=0; cnt=0; ans1=0; ans2=1; group=0; n=0;
}
void tarjan(int x){//求割点
    dfn[x]=low[x]=++num;
    int flag=0;
    for(int i=head[x];~i;i=Next[i]){
        int y=ver[i];
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                flag++;
                if(x!=root || flag>1) cut[x]=true;
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
void dfs(int x){
    c[x]=group; cnt++;//划分连通块，记录连通块大小
    for(int i=head[x];~i;i=Next[i]){
        int y=ver[i];
        if(cut[y] && c[y]!=group){
            Cut++; c[y]=group;//求该连通块包含割点的数量
        }
        if(!c[y]) dfs(y);
    }
}
int main(){
    //freopen(Name ".in", "r", stdin);
    //freopen(Name ".out", "w", stdout);
    int Case=1;
    while(scanf("%d",&m) && m){
        init();
        for(int i=1;i<=m;i++){
            int x,y;
            x=read() ;y=read();
            add(x,y); add(y,x);
            n=max(n,max(x,y));
            app[x]=app[y]=true;//判断该点是否出现
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i] && app[i]) root=i,tarjan(i);
        }
        // for(int i=1;i<=n;i++) printf("%d",cut[i]);
        // printf("\n");
        for(int i=1;i<=n;i++){
            if(!app[i]) continue;
            if(!c[i] && !cut[i]){
                ++group; cnt=Cut=0;
                dfs(i);
                //printf("%d %d\n",cnt,Cut);
                if(Cut==0){
                    if(cnt>1) ans1+=2;
                    else ans1++;//特判
                    if(cnt>1) ans2*=(ll)(cnt-1)*cnt/2;//乘法原理，从n个数中选2个
                }
                if(Cut==1){
                    ans1++;
                    ans2*=(ll)cnt;
                }
            }
        }
        printf("Case %d: %lld %lld\n",Case++,ans1,ans2);
    }
    return 0;
}
```


---

## 作者：hly_shen (赞：0)

# 简化题意

尽可能少的选择点涂黑，使得删掉任意点后每个点存在到达一个黑点的路径。

~~插句闲话：双倍经验 P3225~~

# 题目详解

先求原图的点双连通分量，然后分别对每个点双连通分量进行判断：

情况一：一个 V-Dcc 中有 $0$ 个割点

  - 加入两个黑点（一个主要点，一个备用点防止主要点被删）。

情况二：一个 V-Dcc 中有 $1$ 个割点

  - 在非割点的任意位置加入一个黑点（如果删的是这个点其他点也可以通过割点到其他的黑点）。

情况三：一个 V-Dcc 中有 $2$ 个或以上割点

  - 不需加入任何点，任意点被割都有路径通过割点到达其他有黑点的路径。

# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long 
const int N=5e5+10,M=4e6+10;
int stk[N],root;
int n,m,tot=1,top=0,a,b;
bool cut[N],flag[N];
int dfn[N],low[N],tim,cnt,genshin[N],cnt2[N];
vector <int> dcc[N],vet[N];
void tarjan (int x){
    int flag;
    dfn[x]=low[x]=++tot;stk[++top]=x;
    if(x==root&&!vet[x].size()){
        // dcc[++cnt].push_back(x);
        return ;
    }
    flag=0;
    for(int y : vet[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                flag++;
                if(x!=root||flag>1){
                    cut[x]=1;
                }
                ++cnt;int z;
                do{
                    z=stk[top--];
                    dcc[cnt].push_back(z);
                }while(z!=y);
                dcc[cnt].push_back(x);
            }
        }
        else  low[x]=min(low[x],dfn[y]);
    }
}
int max(int a,int b,int c){
    if(a<b)
        a=b;
    if(a<c)
        a=c;
    return a;
}
int t=0;
signed main(){
    while(cin>>m && m){
        ++t;n=0;
        for(int i=1;i<=m;i++)  {
            cin>>a>>b;n=max(n,a,b);
            if(a==b)continue;
            vet[a].push_back(b);
            vet[b].push_back(a);
        }
        for(int i=1;i<=n;i++){
            cut[i]=flag[i]=dfn[i]=low[i]=tim=cnt=top=genshin[i]=cnt2[i]=0;
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) root=i,tarjan(i);
        for(int i=1;i<=cnt;i++)
        {
            for(int z:dcc[i]){
                if(cut[z])cnt2[i]++;
            }
        }
        int ans2=1,ans=0;
        for(int i=1;i<=cnt;i++){
            if(cnt2[i] ==1)
                ans2*=(dcc[i].size()-1),ans++;
            if(cnt2[i]==0)
                ans2*=(dcc[i].size()-1)*dcc[i].size()/2,ans+=2;
        }
        cout<<"Case "<<t<<": "<<ans<<' '<<ans2<<endl;
        for(int i=1;i<=n;i++)
            dcc[i].clear(),vet[i].clear();
    }
    return 0;
}
```

---

## 作者：accomplishment (赞：0)

[传送门 1](https://www.luogu.com.cn/problem/P3225)

[传送门 2](https://www.luogu.com.cn/problem/SP16185)

[传送门 3](https://www.luogu.com.cn/problem/UVA1108)

这是一道标准的点双连通分量的题，建议先做一下 Tarjan 求点双连通分量模板题 [P8435](https://www.luogu.com.cn/problem/P8435)。

首先我们看一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/k75pmyfm.png)

很明显，这个图中有两个点双连通分量（bcc），一个由点 $1, 2, 3, 5, 6$ 组成，一个由点 $1, 4$ 组成，而 $1$ 就是其中的割点。

我们可以通过样例来推测一下，$1$ 号点设为救援出口肯定不是最优的，因为这样如果 $1$ 号点塌陷了就不行了，还得在双连通分量中的其他点再设置一个。

所以我们的理想方案是：在每个双连通分量的除割点外的点设置救援出口，出口数 $+1$，方案数 $\times$ (点总数 $-$ 割点数)。

但是我们看下面这两张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tclicw4q.png)

这是一个环，也就是一个点双连通分量，这里头没有割点，将任意点设置为救援出口都会存在问题，所以至少要设置两个（任意点设置为出口都会塌陷，需要设置两个才能保证能够逃生），因此得出，没有割点的双连通分量需要两个救援出口，方案数 $C_{n}^{2} = n \times (n-1) \div 2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cc1rdmtp.png)

这张图中间的双连通分量（有 $2, 4, 5$ 三个点）按刚才的方法会需要一个救援出口，而无论任意点塌陷，这个双连通分量的矿工都可以逃到其他两个双连通分量逃生，并不需要救援出口，因此我们判断，只要割点数 $> 1$，就不需要单独在双连通分量内设置救援出口，方案数 $1$（不设置）。

然后我们就可以用 Tarjan 写代码啦，以下给出我的程序（不喜勿喷）：

$Code$：

```cpp


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 5e4 + 9;

struct Edge {
	
	int _to;
	int _next;
	
};

int _maxi = 0;
int _edge = 0;
int _tot = 0;
int _case = 0;
Edge _edgeArray[MAXN << 1];
int _headArray[MAXN];
int _preArray[MAXN];
int _lowArray[MAXN];
int _dfsTime = 0;
int _bccCount = 0;
stack<int> _myStack;
bool _cutArray[MAXN];
vector<int> _bccMap[MAXN];
int _res = 0;
long long _num = 1;

void AddEdge (int from, int to) {
	
	_edgeArray[++_tot] = {to, _headArray[from]};
	_headArray[from] = _tot;
	
	_edgeArray[++_tot] = {from, _headArray[to]};
	_headArray[to] = _tot;
	
}

void Clear () {
	
	_tot = _dfsTime = _bccCount = _maxi = _res = 0;
	_num = 1;
	
	memset(_headArray, 0, sizeof(_headArray));
	memset(_preArray, 0, sizeof(_preArray));
	memset(_lowArray, 0, sizeof(_lowArray));
	memset(_cutArray, 0, sizeof(_cutArray));
	
}

void Tarjan (int cur, int father) {
	
	int child = 0;
	
	_preArray[cur] = _lowArray[cur] = ++_dfsTime;
	_myStack.push(cur);
	
	for (int i = _headArray[cur]; i; i = _edgeArray[i]._next) {
		int to = _edgeArray[i]._to;
		
		if (!_preArray[to]) {
			child++;
			Tarjan(to, cur);
			_lowArray[cur] = min(_lowArray[cur], _lowArray[to]);
			
			if (_lowArray[to] > _preArray[cur] - 1) {
				_cutArray[cur] = true;
				_bccCount++;
				_bccMap[_bccCount].clear();
				
				while (true) {
					int top = _myStack.top();
					
					_myStack.pop();
					_bccMap[_bccCount].push_back(top);
					
					if (top == to) {
						break;
					}
				}
				
				_bccMap[_bccCount].push_back(cur);
			}
		}
		
		else if (to != father) {
			_lowArray[cur] = min(_lowArray[cur], _preArray[to]);
		}
	}
	
	if (father == 0 && child == 1) {
		_cutArray[cur] = false;
	}
	
}

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	while (cin >> _edge) {
		if (_edge == 0) {
			break;
		} 
		
		_case++;
		
		Clear();
		
		int from = 0;
		int to = 0;
		
		for (int i = 0; i < _edge; i++) {
			cin >> from >> to;
			
			_maxi = max(_maxi, max(from, to));
			AddEdge(from, to);
		}
		
		for (int i = 1; i < _maxi + 1; i++) {
			if (!_preArray[i]) {
				Tarjan(i, 0);
			}	
		}
		
		for (int i = 1; i < _bccCount + 1; i++) {
			int cut = 0;
			int num = _bccMap[i].size();
			
			for (int m = 0; m < num; m++) {
				if (_cutArray[_bccMap[i][m]]) {
					cut++;
				}
			}
			
			if (!cut) {
				_res += 2;
				_num *= (long long) num * (num - 1) / 2;
			}
			
			if (cut == 1) {
				_res++;
				_num *= (long long) (num - 1);
			}
		}
		
		cout << "Case " << _case << ": ";
		cout << _res << ' ' << _num << '\n';
	}
	
	return 0;
	
}
```


---

## 作者：koishi_offical (赞：0)

首先看到题面，很明显我们要先通过 tarjan 求出每个连通块内的割点。然后我们考虑怎么去求太平井的数量和方案总数。

我们能发现，割点把每个连通块分割成了数个点双，我们把这些点双分为三类

###  点双内不含任何割点

对于这一类的点双，由于任何一点坍塌都要能够逃生，所以我们至少要在这一类的点双内任意挑两个点出来。

### 点双内含一个割点

对于这一类的点双，在割点不坍塌的情况下，其他点可以通过割点进入其他点双的太平井。所以我们需要挑任意一个非割点的点出来

### 点双内含两个及以上割点

对于这一类的点双，由于任意一个点坍塌，都不会影响其他点撤离，所以不需要建太平井

参考程序（照着蓝书打的）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5;
int h[N],e[N],ne[N],idx,cut[N],ans=1,res,stk[N],top,dfn[N],low[N],num,bt,root;
vector<int>block[N];
void add(int a,int b)
  {
      e[++idx]=b;
      ne[idx]=h[a];
      h[a]=idx;
  }
void tarjan(int x)
  {
      dfn[x]=low[x]=++num;
      stk[++top]=x;
      int cnt=0;
      for(int i=h[x];i;i=ne[i])
        {
            if(!dfn[e[i]])
              {
                  cnt++;
                  tarjan(e[i]);
                  low[x]=min(low[x],low[e[i]]);
                  if((x==root&&cnt>1)||(x!=root&&dfn[x]<=low[e[i]]))
                    {
                      cut[x]=1;
                    }
                      if(dfn[x]<=low[e[i]])
                      {
                        ++bt;
                        block[bt].clear();
                        do
                          {
                              block[bt].push_back(stk[top--]);
                          }while(stk[top+1]!=e[i]);
                        block[bt].push_back(x);
                      }
              }
            else 
              low[x]=min(low[x],dfn[e[i]]);
        }
  }
signed main() {
    int n,m,tip=0;
    cin>>m;
    while(m)
      {
          tip++;
          n=0; 
          for(int i=1;i<=m;i++)
            {
              int x,y;
              cin>>x>>y;
              n=max(n,max(x,y));
              add(x,y);
              add(y,x);
            }
          for(int i=1;i<=n;i++)
            if(!dfn[i])
              {
                  root=i;
                  tarjan(i);
              }
           for(int i=1;i<=bt;i++)
             {
                 int g=0;
                 int len=block[i].size();
                 for(int j=0;j<len;j++)
                    if(cut[block[i][j]]) g++;
                 if(g==0)
                   res+=2,ans=ans*(len-1)*len/2;//点双内不含割点
                 else
                    if(g==1) res++,ans=ans*(len-1);//点双内只含一个割点
             }
           cout<<"Case "<<tip<<":"<<" "<<res<<" "<<ans<<endl;
           cin>>m;
           res=0,ans=1;
           top=0,idx=0,num=0,bt=0;
           memset(h,0,sizeof(h));
           memset(dfn,0,sizeof(dfn));
           memset(low,0,sizeof(low));
           memset(cut,0,sizeof(cut));
      }
}
```


---

## 作者：极寒神冰 (赞：0)

分3种情况讨论

**1:** 在一个强联通块中没有割点，此时可以在任意位置建立两个出口便可以保证可以逃脱

**2:** 在一个强连通块中只有一个割点，那么此时可以在除割点任意位置建立一个出口便可以保证可以逃脱

**3:** 在一个强连通块中有两个以上的割点，那么一定可以从其他强连通块中走，就不用建出口了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=200010;
struct edge
{
	int nxt,to;
}e[N];
int head[N],cnt;
int low[N],dfn[N],bel[N],iscut[N],ret,tim;
int n,m,scut,notcut;
inline void init()
{
	n=cnt=ret=tim=0;
	memset(head,-1,sizeof(head));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(bel,0,sizeof(bel));
	memset(iscut,0,sizeof(iscut));
}
inline void add_edge(int u,int v)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline void tarjan(int u,int f) //求割点
{
	dfn[u]=low[u]=++tim;
	int ch=0;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]&&u!=f)
			{
				iscut[u]=1;
			}
			if(u==f) ch++;
		}
		low[u]=min(low[u],dfn[v]);
	}
	if(u==f&&ch>=2) iscut[u]=1;
}
inline void dfs(int u,int f)//dfs一遍找联通块内割点数量
{
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(iscut[v]&&bel[v]!=ret)
		{
			++scut;
			bel[v]=ret;
		}
		if(!bel[v])
		{
			++notcut;
			bel[v]=ret;
			dfs(v,u);	
		}
	}
}
signed main()
{
	int cas=0;
	do
	{	
		m=read();
		if(m==0) return 0;
		init();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add_edge(u,v);
			add_edge(v,u);
			n=max(n,u);
			n=max(n,v);
		}
		for(int i=1;i<=n;i++)
		{
			if(!dfn[i])
			{
				tarjan(i,i);
			}
		}
		/*
		for(int i=1;i<=n;i++)
		{
			cout<<iscut[i]<<" ";
		}
		puts("");
		*/
		int ans1=0,ans2=1;
		for(int i=1;i<=n;i++)
		{
			if(!bel[i]&&!iscut[i])
			{
				++ret;
				notcut=1;
				scut=0;
				bel[i]=ret;
				dfs(i,i);
				if(scut==0)//没有割点
				{	
					//cout<<"1"<<endl;
					ans1+=2;
					ans2*=(notcut-1)*notcut/2;
				}
				if(scut==1)//有一个割点
				{
					//cout<<"2"<<endl;
					ans1+=1;
					ans2*=notcut;
				}
			}
		}
		printf("Case %lld: %lld %lld\n",++cas,ans1,ans2);
	}
	while(1);
}

```


---

## 作者：swiftc (赞：0)

首先```tarjan```求割点和边双联通分量，然后对于每一个边双联通分量:
- 若没有割点

	需要建两个出口，在任意两个位置即可。
- 若有一个割点

	需要建一个出口，不在割点即可。
- 若有两个以上的割点

	无需建出口。
    
__code__:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int head[100001],nxt[100001],to[100001],cnt,cas;
void add(int a,int b){
  nxt[++cnt]=head[a];
  to[cnt]=b;
  head[a]=cnt;
}
int T,dfn[100001],low[100001],is[100001],vis[100001];
void tarjan(int now,int f){
  int flag=0,num=0;
  low[now]=dfn[now]=++T;
  for(int i=head[now];i;i=nxt[i]){
    if(!dfn[to[i]]){
      tarjan(to[i],now);
      low[now]=min(low[now],low[to[i]]);
      if(low[to[i]]>=dfn[now]){
        flag=1;
        num++;
      }
    }
    else if(to[i]!=f){
      low[now]=min(low[now],dfn[to[i]]);
    }
  }
  if((now==f&&num>=2)||(now!=f&&flag)){
    is[now]=1;
  }
}
int num1,num2,bel;
void dfs(int now){
  vis[now]=bel;
  num1++;
  for(int i=head[now];i;i=nxt[i]){
    if(is[to[i]]&&vis[to[i]]!=bel){
      vis[to[i]]=bel;
      num2++;
    }
    if(!vis[to[i]]){
      dfs(to[i]);
    }
  }
}
void clear(){
  memset(is,0,sizeof(is));
  memset(dfn,0,sizeof(dfn));
  cnt=0;
  bel=0;
  memset(head,0,sizeof(head));
  memset(low,0,sizeof(low));
  memset(vis,0,sizeof(vis));
}
signed main(){
  int n,m;
  while(scanf("%lld",&m)!=EOF){
    if(!m)break;
    clear();
    n=0;
    for(int i=1;i<=m;i++){
      int a,b;
      scanf("%lld%lld",&a,&b);
      add(a,b);
      add(b,a);
      n=max(n,max(a,b));
    }
    for(int i=1;i<=n;i++){
      if(!dfn[i]){
        tarjan(i,i);
      }
    }
    int ans1=0,ans2=1;
    for(int i=1;i<=n;i++){
      if(vis[i]==0&&is[i]==0){
        bel++;
        num1=num2=0;
        dfs(i);
        if(num2==0){
          ans1+=2;
          ans2*=(num1-1)*num1/2;
        }
        if(num2==1){
          ans1++;
          ans2*=num1;
        }
      }
    }
    printf("Case %lld: %lld %lld\n",++cas,ans1,ans2);
  }
  return 0;
}

```


---

## 作者：hicc0305 (赞：0)

## 附原题描述：
有一座地下的稀有金属矿由n条隧道和一些连接点组成，其中每条隧道连接两个连接点。任意两个连接点之间最多只有一条隧道。为了降低矿工的危险，你的任务是在一些连接点处安装太平井和相应的逃生装置，使得不管哪个连接点倒塌，不在此连接点的所有矿工都能到达太平井逃生（假定除倒塌的连接点不能通行外，其他隧道和连接点完好无损）。为了节约成本，你应当在尽量少的连接点安装太平井。你还需要计算出在太平井的数目最小时的安装方案总数。

### 输入数据
输入包含多组数据。每组数据第一行为隧道的条数n(n<=50000),一下n行，每行两个整数，即一条隧道两段的连接点的编号(所有连接点从1开始编号)。每组数据的所有连接点保证连通。 
输入以数字0作为结束

### 输出数据
对于每组数据，输出两个整数，即最少需要安装的太平井数目以及对应的方案总数。 
答案保证在64位带符号整数范围以内。


------------


------------

## 题解部分

这道题很明显先要求出各个点双连通分量。但求出了双连通分量又怎么做呢？
求出各个双连通分量的割点。

如果一个双连通分量内有多个割点，就不用安装太平井，因为在这个双连通分量内的点都可以通过割点到达其他连通分量内的太平井

如果只有一个割点，那么在割点坍塌就没有办法到达其他连通分量了，所以需要安装一个太平井，方案数就是连通分量的点数减一

如果整个图都是一个连通分量，那么需要建两个太平井，一个塌了，另一个还能用，若顶点数为n，方案数就是n(n-1)/2

注意，各个连通分量的方案数，根据乘法原理应当乘起来

最后，代码如下：
```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int s[100000];
int n,m,cnt=0,tot=0,num=0,p=0;
int head[101000],nxt[101000],to[101000];
int low[100010],pre[101000],f[101000],l[100100];
int re[101010];
vector <int> vec[100000];
void addedge(int x,int y)
{
    cnt++;
    nxt[cnt]=head[x];
    head[x]=cnt;
    to[cnt]=y;
}
void dfs(int u,int fa)
{
    low[u]=pre[u]=++tot;
    s[++p]=u;
    for(int i=head[u];i!=-1;i=nxt[i])
    {
        int v=to[i];
        if(!pre[v])
        {
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=pre[u])
            {
                num++;
                vec[num].clear();
                while(p)
                {
                    vec[num].push_back(s[p]);
                    l[s[p]]++;
                    if(s[p]==v) break;
                    p--;
                }
                vec[num].push_back(u);
                p--;
                l[u]++;
            }
        }
        else if(pre[v]<pre[u] && v!=fa) low[u]=min(low[u],pre[v]);
    }
}
void Slove()
{
	long long ans1=0,ans2=1;
	for(int i=1;i<=num;i++)
	{
		int res=0;  
        if(vec[i].size()==1 && l[vec[i][0]]>1) continue;
        for(int j=0;j<vec[i].size();j++)  
            if(l[vec[i][j]]>1) res++; //统计割顶个数
        if(res==1) ans1++,ans2*=(long long)vec[i].size()-1;
	}
	if(num==1) ans1=2,ans2=(long long)vec[1].size()*(vec[1].size()-1)/2;//整个图都为一个连通分量需要特判
    printf("%lld %lld\n",ans1,ans2);
}
int main()
{
	int T=0;
	while(1)
	{
		T++; 
	    memset(f,0,sizeof(f));
	    memset(l,0,sizeof(l));
	    memset(re,0,sizeof(re));
	    memset(pre,0,sizeof(pre));
	    memset(low,0,sizeof(low));
	    memset(head,-1,sizeof(head));
	    n=0,cnt=0,tot=0,num=0,p=0;
		scanf("%d",&m);
		if(!m) break;
		for(int i=1;i<=m;i++)
		{
		    int x,y;
		    scanf("%d%d",&x,&y);
		    if(!re[x]) re[x]=++n;//因为题目并没有告诉点的数量，所以做了离散化
		    if(!re[y]) re[y]=++n;
		    addedge(re[x],re[y]);
		    addedge(re[y],re[x]);
		}
		for(int i=1;i<=n;i++)
			if(!pre[i]) dfs(i,0);//tarjan求出连通分量和割顶
		printf("Case %d: ",T);
		Slove();
	}
    return 0;
}
```

---

