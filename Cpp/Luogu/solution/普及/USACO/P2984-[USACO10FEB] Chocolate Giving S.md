# [USACO10FEB] Chocolate Giving S

## 题目描述

FJ 有 $B$ 头奶牛 $(1\le B\le 25000)$，有 $N(2\times B\le N\le 50000)$ 个农场，编号 $1$ 到 $N$，有 $M(N-1\le M\le 100000)$ 条双向边，第 $i$ 条边连接农场 $R_i$ 和 $S_i(1\le R_i\le N, 1\le S_i\le N)$，该边的长度是 $L_i(1\le L_i\le 2000)$。居住在农场 $P_i$ 的奶牛 A $(1\le P_i\le N)$，想送一份新年礼物给居住在农场 $Q_i(1\le Q_i\le N)$ 的奶牛 B，但是奶牛 A 必须先到 FJ（居住在编号 $1$ 的农场）那里取礼物，然后再送给奶牛 B。你的任务是：奶牛 A 至少需要走多远的路程？

## 样例 #1

### 输入

```
6 7 3 
1 2 3 
5 4 3 
3 1 1 
6 1 9 
3 4 2 
1 4 4 
3 2 2 
2 4 
5 1 
3 6 
```

### 输出

```
6 
6 
10 
```

# 题解

## 作者：封禁用户 (赞：75)

# ~~关于Floyd，它太慢了~~
# ~~关于spfa,它死了~~
# 关于dijkstra，还是用它吧

**步入正题：**

这道题，千万不要被题面所误导

题目大意：点u到点1的最短路+点1到点v的最短路

**但是**，您要是照着这个思路写代码的话，只能拿到50分，T了5个点

显然，这个做法不够优秀

进一步，我们发现，**在第i头奶牛的行动中，肯定会经过1号点**

所以，只要跑一边dijkstra就好了，把起点设为1

每当进行一次询问，就输出d[u]+d[v] （d[]记录最短距离）

//注释都在代码里了

**上代码：（vector存图+dijkstra+堆优化）**
```cpp
//代码重在实用，不在华丽的操作 
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,t,d[50010],ans;
//n个节点，m条边，t次询问，d[]存最短距离，ans为每次询问的答案 
struct edge
{
	int to,cost;
};
vector<edge>G[50010];//vector存图 
typedef pair<int,int>P;//定义一个pair类型的P（只是为了写起来简单一点） 
void dijkstra(int s)//s为起点，在这道题里就是1 
{
	priority_queue<P,vector<P>,greater<P> >q;
	//一个P类型（pair）类型的优先队列  
	for(int i=1;i<=n;i++) d[i]=1e9;//赋初值1e9 
	d[s]=0;//自己到自己的距离是0 
	q.push(P{0,s});//加入队列等待处理 
	while(!q.empty())
	{
		P p=q.top();//取队首 
		q.pop();
		//声明一下：p.first代表的是一个距离，而p.second代表的是一个点， 
		//Tell一个不为人知的秘密， 
		//若把p.first设为一个点，而把p.second设为一个距离，
		//程序的速度就没有第一个优秀（亲测） 
		int v=p.second;//也是为了写起来简便一点， 
		if(d[v]<p.first) continue;//如果已经是一个最短距离了，continue； 
		for(int i=0;i<G[v].size();i++)//循环点v连接的所有点 
		{
			edge e=G[v][i]; 
			if(d[e.to]>d[v]+e.cost)//松弛操作，贪心思想 
			{
				d[e.to]=d[v]+e.cost;//更新d[e.to]的值 
				q.push(P{d[e.to],e.to});//重新加入到队列等待处理 
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	while(m--)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(edge{v,w});//注意，这个图是一个无向图 
		G[v].push_back(edge{u,w});
	}
	dijkstra(1);
	//以1号点为起点进行dijkstra()，便可获得1号点到其它任意一点的最短距离 
	while(t--)
	{
		ans=0;
		int u,v;
		scanf("%d%d",&u,&v);
		ans=d[u]+d[v];//直接输出答案 
		printf("%d\n",ans);
	}
	return 0;//养成良好习惯 
}
```
这世界上不缺少什么水题，而是缺少发现水题的眼睛

看我写的这么认真，是否可以点个赞再走呢？

---

## 作者：L_Y_T (赞：23)

交了九九八十一遍，最后终于过了！这道题唯一的难点就是开的数据规模，然后就是一个裸的~~spfa~~最短路，下面见我这81次~~(其实没这么多)~~交的代码
------------


------------
```cpp
1. 具体思路就是：让一只奶牛跑到FJ那边，然后再跑回p_i那里。
细心的朋友都发现了，这样太慢！！！而且常量开这么大跑两遍确实非常勉强
于是就爆零了！
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std ;
const int inf = 0x7fffffff;
const int maxn = 30000001 ;//这里是不是太大了！！
int n,m,t,k,s,e;
int dis[maxn] , vis[maxn] , head[maxn] ;
struct dy{
    int x , y , z ,next;
}a[maxn];
void add(int x , int y , int z)//加边
{
    a[t].x = x ;
    a[t].y = y ;
    a[t].z = z ;
    a[t].next = head[x] ;
    head[x] = t ++ ;
}
void spfa(int s)
{
    queue<int>q ;
    for(int i = 1 ; i <= n ; i ++) dis[i] = inf ;
    memset(vis , false , sizeof(vis)) ;
    q.push(s) ;
    dis[s] = 0 ;
    while(!q.empty())
    {
        int u = q.front() ;
        q.pop() ;
        vis[u] = 0 ;
        for(int i = head[u] ; i != -1 ; i = a[i].next )
        {
            int v = a[i].y ;
            if(dis[v] > dis[u] + a[i].z)
            {
                dis[v] = dis[u] + a[i].z ;
                if(!vis[v])
                {
                    vis[v] = true ;
                    q.push(v) ;
                }
            }
        }
    }
}
int p ;
int main()
{
    cin >> n >> m >> p ;
    memset(head , -1 , sizeof(head)) ;
    while(m --)//建图
    {
        int x , y , z ;
        cin >> x >> y >> z ;
        add(x , y , z ) ;
        add(y , x , z) ;
    }
    while( p --)//两遍SPFA
    {
        cin >> s >> e ;
        spfa(s) ;
        int w = dis[1] ;//先跑到FJ那里
        spfa(1) ;
        cout << w + dis[e] <<"\n";//再跑回P_I
    }
 } 
```


------------
```cpp
2.发现问题就要解决问题：上面说到常数太大的问题，于是便改吧！略微的超过一点数据范围，但是本蒟蒻有忽视了一个常识性问题：这是一个无向图！数组是要开两倍多一点的！
50分！
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std ;
const int inf = 0x7ffffff;
const int maxn = 50010 ;//更改在此处！
int n,m,t,k,s,e;
int dis[maxn] , vis[maxn] , head[maxn] ;//注意这里！应优化为maxn*2+1
struct dy{
    int x , y , z ,next;
}a[maxn];
void add(int x , int y , int z)//加边
{
    a[t].x = x ;
    a[t].y = y ;
    a[t].z = z ;
    a[t].next = head[x] ;
    head[x] = t ++ ;
}
void spfa(int s)
{
    queue<int>q ;
    for(int i = 1 ; i <= n ; i ++) dis[i] = inf ;
    memset(vis , false , sizeof(vis)) ;
    q.push(s) ;
    dis[s] = 0 ;
    while(!q.empty())
    {
        int u = q.front() ;
        q.pop() ;
        vis[u] = 0 ;
        for(int i = head[u] ; i != -1 ; i = a[i].next )
        {
            int v = a[i].y ;
            if(dis[v] > dis[u] + a[i].z)
            {
                dis[v] = dis[u] + a[i].z ;
                if(!vis[v])
                {
                    vis[v] = true ;
                    q.push(v) ;
                }
            }
        }
    }
}
int p ;
int main()
{
    cin >> n >> m >> p ;
    memset(head , -1 , sizeof(head)) ;
    while(m --)
    {
        int x , y , z ;
        cin >> x >> y >> z ;
        add(x , y , z ) ;
        add(y , x , z) ;
    }
    while( p --)//打死不改的两遍spfa
    {
        cin >> s >> e ;
        spfa(s) ;
        int w = dis[1] ;
        spfa(1) ;
        cout << w + dis[e] <<"\n";
    }
 } 
```


------------
```cpp
3.改进：const 开大了一点，且maxn*2+1了，但是还是RE了一个点(而且吸氧还没用呢！)加上改进了算法：从奶牛到FJ的距离其实就和从FJ到奶牛的距离相等
所以只要求FJ到P_I和Q_I的距离之和就好了！！
90分！
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std ;
const int inf = 0x7ffffff;
const int maxn = 60010 ;
int n,m,t,k,s,e;
int dis[maxn*2+1] , vis[maxn*2+1] , head[maxn*2+1] ;
struct dy{
    int x , y , z ,next;
}a[maxn*2+1];
void add(int x , int y , int z)
{
    a[t].x = x ;
    a[t].y = y ;
    a[t].z = z ;
    a[t].next = head[x] ;
    head[x] = t ++ ;
}
void spfa(int s)
{
    queue<int>q ;
    for(int i = 1 ; i <= n ; i ++) dis[i] = inf ;
    memset(vis , false , sizeof(vis)) ;
    q.push(s) ;
    dis[s] = 0 ;
    while(!q.empty())
    {
        int u = q.front() ;
        q.pop() ;
        vis[u] = 0 ;
        for(int i = head[u] ; i != -1 ; i = a[i].next )
        {
            int v = a[i].y ;
            if(dis[v] > dis[u] + a[i].z)
            {
                dis[v] = dis[u] + a[i].z ;
                if(!vis[v])
                {
                    vis[v] = true ;
                    q.push(v) ;
                }
            }
        }
    }
}
int p ;
int main()
{
    cin >> n >> m >> p ;
    memset(head , -1 , sizeof(head)) ;
    while(m --)
    {
        int x , y , z ;
        cin >> x >> y >> z ;
        add(x , y , z ) ;
        add(y , x , z) ;
    } 
    spfa(1) ;
    while( p --)//改为一遍spfa
    {
        cin >> s >> e ;
        cout <<dis[s] + dis[e] <<"\n";
    }
 } 
```


------------
```cpp
4.AC！
这么久了终于过了吗！long long 吗？我感觉和这个没什么大关系；我个人认为是我又把常数扩大了10倍的原因；
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>

using namespace std ;
#define ll long long 
const ll inf = 0x7ffffff;
const ll maxn = 1000010 ;//这里扩大了10倍
ll n,m,t,k,s,e;
ll dis[maxn] , vis[maxn] , head[maxn] ;
struct dy{
    ll x , y , z ,next;
}a[maxn];
void add(ll x , ll y , ll z)
{
    a[t].x = x ;
    a[t].y = y ;
    a[t].z = z ;
    a[t].next = head[x] ;
    head[x] = t ++ ;
}
void spfa(ll s)
{
    queue<ll>q ;
    for(ll i = 1 ; i <= n ; i ++) dis[i] = inf ;
    memset(vis , false , sizeof(vis)) ;
    q.push(s) ;
    dis[s] = 0 ;
    while(!q.empty())
    {
        ll u = q.front() ;
        q.pop() ;
        vis[u] = 0 ;
        for(ll i = head[u] ; i != -1 ; i = a[i].next )
        {
            ll v = a[i].y ;
            if(dis[v] > dis[u] + a[i].z)
            {
                dis[v] = dis[u] + a[i].z ;
                if(!vis[v])
                {
                    vis[v] = true ;
                    q.push(v) ;
                }
            }
        }
    }
}
int p ;
int main()
{
    cin >> n >> m >> p ;
    memset(head , -1 , sizeof(head)) ;
    while(m --)
    {
        ll x , y , z ;
        cin >> x >> y >> z ;
        add(x , y , z ) ;
        add(y , x , z) ;
    } 
    spfa(1) ;
    while( p --)//改为一遍spfa
    {
        cin >> s >> e ;
        cout <<dis[s] + dis[e] <<"\n";
    }
 } 
```


---

## 作者：小糯米 (赞：15)

这是一篇比较玄学的题了……开始看见这个题，我的想法：

### 哎呀！不就是一道最短路模板水题吗！

于是乎兴冲冲的用Dijskra写了一下代码：
```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e5 + 1;
int n, m, b, dis[N], cnt, hed[N], rdis[N], rhed[N];
bool vis[N], rvis[N];
struct edge
{
    int to, next, dis;

};
edge a[N], ra[N];
struct node
{
    int dis, pos;
    bool operator<(const node &a) const
    {
        return a.dis < dis;

    }
};
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void bud(int u, int v, int d)
{
    a[++cnt].to = v;
    a[cnt].next = hed[u];
    a[cnt].dis = d;
    hed[u] = cnt;
}
void stl()
{
    priority_queue<node> q;
    memset(dis, 0x3f, sizeof(dis));

    dis[1] = 0;
    q.push((node){0, 1});
    while (!q.empty())
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;

        if (vis[x])
            continue;
        vis[x] = 0;
        for (int i = hed[x]; i; i = a[i].next)
        {
            int y = a[i].to;
            if (dis[y] > dis[x] + a[i].dis)

            {
                dis[y] = dis[x] + a[i].dis;

                if (!vis[y])
                    q.push((node){vis[y], y});
            }
        }
    }
}
int main()
{
    n = read();
    m = read();
    b = read();
    for (int i = 1; i <= m; ++i)
    {
        int u, v, d;
        u = read();
        v = read();
        d = read();
        bud(u, v, d);
        bud(v, u, d);
    }
    stl();
    for (int i = 1; i <= b; ++i)
    {
        int ai, bi;

        ai = read();
        bi = read();
        printf("%d\n", dis[ai] + dis[bi]);

    }
    return 0;
}
```
然后交上去,90分。最后一个点成功的TLE。

于是乎，本蒟蒻就清醒的意识到：本题开始卡常了。

于是就开始瞎胡了，先写了个快速输出，交上去，TLE……

然后~~吸氧气~~，TLE……

于是蒟蒻想到：

Dijkstra这道题不太行得通。

然后就想起了一个叫做配对堆（Pairing Heap）的玄学数据结构……

以下是两者算法的运行时间比较（以[P4779](https://www.luogu.org/problem/P4779)为例）：

Dijkstra：

![](http://a3.qpic.cn/psb?/V11FgVVT0cwLk0/SmsF4Ty3aOuQm6qxybXboH*ZraVHPF04S.QF8klHQ3s!/c/dL4AAAAAAAAA&ek=1&kp=1&pt=0&bo=DAOXAAAAAAADF6o!&tl=1&vuin=1750562553&tm=1571824800&sce=60-2-2&rf=0-0)

Pairing Heap

![](http://a3.qpic.cn/psb?/V11FgVVT0cwLk0/hp0BqcMrncIILb9cNIn8xC.Kmkk7SVtRxPC*qyBYz1U!/c/dL4AAAAAAAAA&ek=1&kp=1&pt=0&bo=4QKxAAAAAAADF2A!&tl=1&vuin=1750562553&tm=1571824800&sce=60-2-2&rf=0-0)

明显快了一些是不是？（~~不是~~）

如果还觉得不明显的话，遇到[P2984](https://www.luogu.org/problem/P2984)这种~~毒瘤~~就优化的非常明显了，基本上都是120ms内过的……

废话不多说了，放代码！
```cpp
#include <iostream>
#include <cstdio>
#include <vector>

//#define nullptr 0

class UnderflowException
{
};

class IllegalArgumentException
{
};

template <typename T>
class PairingHeap
{
private:
    struct PairNode
    {
        T element;
        PairNode *leftChild, *nextSibling, *prev;

        PairNode(const T &elm)
        {
            element = elm;
            leftChild = nextSibling = prev = nullptr;
        }
    };

    PairNode *root;

    void reclaimMemory(PairNode *t)
    {
        if (t != nullptr)
        {
            reclaimMemory(t->leftChild);
            reclaimMemory(t->nextSibling);
            delete t;
        }
    }

    void compareAndLink(PairNode *&first, PairNode *second)
    {
        if (second == nullptr)
        {
            return;
        }
        if (second->element < first->element)
        {
            second->prev = first->prev;
            first->prev = second;
            first->nextSibling = second->leftChild;
            if (first->nextSibling != nullptr)
            {
                first->nextSibling->prev = first;
            }
            second->leftChild = first;
            first = second;
        }
        else
        {
            second->prev = first;
            first->nextSibling = second->nextSibling;
            if (first->nextSibling != nullptr)
            {
                first->nextSibling->prev = first;
            }
            second->nextSibling = first->leftChild;
            if (second->nextSibling != nullptr)
            {
                second->nextSibling->prev = second;
            }
            first->leftChild = second;
        }
    }

    PairNode *combineSiblings(PairNode *firstSibling)
    {
        if (firstSibling->nextSibling == nullptr)
        {
            return firstSibling;
        }
        static std::vector<PairNode *> treeArray(5);
        long long numSiblings = 0;
        for (; firstSibling != nullptr; ++numSiblings)
        {
            if (numSiblings == treeArray.size())
            {
                treeArray.resize(numSiblings * 2);
            }
            treeArray[numSiblings] = firstSibling;
            firstSibling->prev->nextSibling = nullptr;
            firstSibling = firstSibling->nextSibling;
        }
        if (numSiblings == treeArray.size())
        {
            treeArray.resize(numSiblings + 1);
        }
        treeArray[numSiblings] = nullptr;
        long long i = 0;
        for (; i + 1 < numSiblings; i += 2)
        {
            compareAndLink(treeArray[i], treeArray[i + 1]);
        }
        long long j = i - 2;
        if (j == numSiblings - 3)
        {
            compareAndLink(treeArray[j], treeArray[j + 2]);
        }
        for (; j >= 2; j -= 2)
        {
            compareAndLink(treeArray[j - 2], treeArray[j]);
        }
        return treeArray[0];
    }

public:
    PairingHeap() { root = nullptr; }

    void makeEmpty()
    {
        reclaimMemory(root);
        root = nullptr;
    }

    ~PairingHeap() { makeEmpty(); }

    bool isEmpty() const { return root == nullptr; }

    const T &findMin() const
    {
        if (isEmpty())
        {
            throw UnderflowException{};
        }
        return root->element;
    }

    typedef PairNode *Position;

    Position insert(const T &x)
    {
        PairNode *newNode = new PairNode{x};
        if (root == nullptr)
        {
            root = newNode;
        }
        else
        {
            compareAndLink(root, newNode);
        }
        return newNode;
    }

    void deleteMin()
    {
        if (isEmpty())
        {
            throw UnderflowException{};
        }
        PairNode *oldRoot = root;
        if (root->leftChild == nullptr)
        {
            root = nullptr;
        }
        else
        {
            root = combineSiblings(root->leftChild);
        }
        delete oldRoot;
    }

    void deleteMin(T &minItem)
    {
        minItem = findMin();
        deleteMin();
    }
    void decreaseKey(Position p, const T &newVal)
    {
        if (p->element < newVal)
        {
            throw IllegalArgumentException{};
        }
        p->element = newVal;
        if (p != root)
        {
            if (p->nextSibling != nullptr)
            {
                p->nextSibling->prev = p->prev;
            }
            if (p->prev->leftChild == p)
            {
                p->prev->leftChild = p->nextSibling;
            }
            else
            {
                p->prev->nextSibling = p->nextSibling;
            }
            p->nextSibling = nullptr;
            compareAndLink(root, p);
        }
    }
};

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

using namespace std;

long long n, m, s, d[100001], b;

struct Edge
{
    long long v, w;
};

struct State
{
    long long dis, nid;

    bool operator<(const State &b) const { return dis < b.dis; }
};

vector<Edge> g[100001];

PairingHeap<State>::Position nps[100001];

void dijkstra()
{
    PairingHeap<State> ph;
    for (long long i = 1; i <= n; ++i)
    {
        d[i] = 2147483647;
    }
    d[s] = 0;
    for (long long i = 1; i <= n; ++i)
    {
        nps[i] = ph.insert(State{d[i], i});
    }
    while (!ph.isEmpty())
    {
        State ts;
        ph.deleteMin(ts);
        long long u = ts.nid;
        d[u] = ts.dis;
        nps[u] = nullptr;
        for (long long i = 0; i < g[u].size(); ++i)
        {
            long long v = g[u][i].v, w = g[u][i].w;
            if (d[v] > d[u] + w && nps[v] != nullptr)
            {
                d[v] = d[u] + w;
                ph.decreaseKey(nps[v], State{d[v], v});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    n = read();
    m = read();
    s = 1;
    b = read();
    while (m--)
    {
        long long u, v, w;
        u = read();
        v = read();
        w = read();
        g[u].push_back(Edge{v, w});
        g[v].push_back(Edge{u, w});
    }
    dijkstra();
    while (b--)
    {
        long long p = read(), q = read();
        cout << d[p] + d[q] << endl;
    }
}
```

根据 Data Structures and Algorithm Analysis in C++ (Fourth Edition) 中的配对堆整理得出，在此感谢。

然后就愉快的AC啦~

第一次写题解，代码注释还没来得及搞，等省赛完了再来填坑，~~逃~~

---

## 作者：Star1_3st (赞：7)

设$s$为起点，要从$s$点先走到$a$,再走到$b$。

显然可以看出，最短路是从$s$到$a$跑一遍,再从$a$跑到$b$。开始我陷入了一个莫名其妙的问题，不知路线怎么规划。但后来发现由于是双向边，无论怎么规划路线，从$s$到$a$再到$b$的最短路都等价于$dis[s][a]+dis[s][b]$,因为从$s$到$a$的最短路等于从$a$到$s$。故不用模拟题意真的那么去跑最短路，一遍$SPFA$就够了。

只要思路正确，不跑冤枉路，时间还是充裕的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,s,num,head[20000000],to[20000000],len[20000000],next[20000000],book[20000000],dis[20000000],b[20000000];
void add(long long u,long long v,long long w)
{
    to[++num]=v;
    len[num]=w;
    next[num]=head[u];
    head[u]=num;
}

void spfa(long long s)
{
    long long h=1,t=1;
    for(long long i=1;i<=n;i++)
        dis[i]=2147483647;
    dis[s]=0;
    book[s]=1;
    b[t++]=s;
    while(h<t)
    {
        long long x=b[h++];
        book[x]=0;
        for(long long i=head[x];i;i=next[i])
            if(dis[to[i]]>dis[x]+len[i])
            {
                dis[to[i]]=dis[x]+len[i];
                if(!book[to[i]])
                {
                    b[t++]=to[i];
                    book[to[i]]=1;
                }
            }
    }
}

int main()
{
    cin>>n>>m>>s;
    for(long long i=1;i<=m;i++)
    {
        long long u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);//建图
    }
    
    spfa(1);//从fj家出发跑一遍
	for(int i=1;i<=s;i++)
	{
		int u,v;
		cin>>u>>v;
		cout<<dis[u]+dis[v]<<endl;//输出答案
	}
	
    return 0;
}

```

---

## 作者：VulcanStig (赞：4)

## 题解 P2984 【[USACO10FEB】Chocolate Giving
 
这其实是去年写的题解

不就是个裸的Dijkstra吗？


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define sf scanf
#define pf printf
using namespace std;
typedef pair<int,int>T;
int n,m,b;
int st,ed,len;
int lover1,lover2;
int lsr,first[1000010];
int dist[50001],vis[50001];
struct node{
	int u,v,w,nxt;
}e[1000010];
void add(int u,int v,int w){
    e[++lsr].u=u;e[lsr].v=v;e[lsr].w=w;
    e[lsr].nxt=first[u];first[u]=lsr;
}

void dijkstra(int s){
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f,sizeof(dist));
    dist[s]=0;
    priority_queue<T,vector<T>,greater<T>  >q;
    q.push(make_pair(dist[s],s));
    while(!q.empty()){
		pair<int,int>t=q.top();
        q.pop();
        int d=t.first,u=t.second;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=first[u];i;i=e[i].nxt){
			int v=e[i].v;
            if(d+e[i].w<dist[v]){
                dist[v]=d+e[i].w;
                q.push(make_pair(dist[v],v));
            }
        }
    }
}
int main(){
    cin>>n>>m>>b;
    for(int i=1;i<=m;i++){
        cin>>st>>ed>>len;
        add(st,ed,len);add(ed,st,len);
	}
    dijkstra(1);
    for(int i=1;i<=b;i++){
        int ans=0;
        cin>>lover1>>lover2;
        ans+=dist[lover1]; 
        ans+=dist[lover2];
        cout<<ans<<endl;
      }
}

---

## 作者：ez_lcw (赞：2)

## 最好SPFA，但我任性，用Dijkstra，咋地？

这题一开始我很笨的模拟题目，让奶牛先去FJ那里再去送礼物。，然后TLE了。

然后我开始死命卡，什么快读，记忆化，剪枝优化，都用上了，还是过不去，正在我万分无奈的时候，突然想到了一个办法：~~其实是别人告诉我的~~

仔细想想，就会发现：**其实从某一个牛棚到FJ那里其实就是从FJ那里到牛棚那里，所以只用从FJ出发，用一个$dis$数组把FJ到所有点的最短路都记上，然后比如，牛棚$i$的牛要送给牛棚$j$的牛礼物，那么直接输出$dis[i]+dis[j]$就可以了，不然就会被卡爆（like me）。**

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
 
using namespace std;
 
int m,n,b,r,s,l,p,j,start_,end_;
long long dis[50005];
bool vis[50005];
 
struct data {
    int u,s;
    bool operator < (const data &e) const {//重载运算符
        return s>e.s;
    }
} now;
 
priority_queue<data>q;//优先队列
vector<int>a[50005],g[50005];//记录边和这条边的路程
 
void bfs() {
    for(int i=1; i<=n; i++) {//初始化
        dis[i]=0x7fffffff;
    }
    q.push((data) {1,0});
    while(!q.empty()) {
        now=q.top();
        q.pop();
        if(vis[now.u]) {//已经走过就continue。
            continue;
        }
        vis[now.u]=true;//标记已走过
        dis[now.u]=now.s;//更新dis数组（因为这是优先队列，所以这一定是最短路）
        for(int i=0; i<(int)a[now.u].size(); i++) {
            int u=a[now.u][i];
            int s=g[now.u][i];
            if(!vis[u]&&now.s+s<dis[u]) {//判断走没走过和是否更优
                q.push((data) {u,s+now.s});
            }
        }
    }
}
 
void dfs(int u) {//dfs初始化
    vis[u]=false;
    for(int i=0; i<(int)a[u].size(); i++) {
        if(vis[a[u][i]]) {
            dfs(a[u][i]);
        }
    }
}
 
int main() {
    scanf("%d%d%d",&n,&m,&b);
    for(int i=1; i<=m; i++) {
        scanf("%d%d%d",&r,&s,&l);
        a[r].push_back(s);//存边
        a[s].push_back(r);
        g[r].push_back(l);//存路程
        g[s].push_back(l);
    }
    bfs();
    dfs(1);
    while(!q.empty()) {//初始化队列（虽然没什么卵用）
        q.pop();
    }
    for(int i=1; i<=b; i++) {
        scanf("%d%d",&p,&j);
        printf("%d\n",dis[p]+dis[j]);//输出
    }
    return 0;
}
```

---

## 作者：ws_fuweidong (赞：2)

裸的spfa。。。

求1到两点的距离之和

代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define maxn 50001
#define mm 1000010
#define inf 99999999
using namespace std;
int head[maxn],dis[maxn],vis[maxn];
queue<int> q;
struct edge{
    int next,to,cost;
}e[mm];
int n,m,cnt=0,Q;
void add(int u,int v,int z){
    e[++cnt].next=head[u];
    e[cnt].to=v;
    e[cnt].cost=z;
    head[u]=cnt;
}
void spfa(){
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=n;i++)
    dis[i]=inf;
    q.push(1);
    vis[1]=1;
    dis[1]=0;
    while (!q.empty()){
        int tmp=q.front();
        q.pop();
        vis[tmp]=0;
        for (int i=head[tmp];i;i=e[i].next){
            int to=e[i].to;
            if (dis[to]>dis[tmp]+e[i].cost){
                dis[to]=dis[tmp]+e[i].cost;
                if (!vis[to]){
                    q.push(to);
                    vis[to]=1;
                }
            }
        }
    }
}
int main(){
    memset(head,0,sizeof(head));
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    spfa();
    for (int i=1;i<=Q;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",dis[x]+dis[y]);
    }
    return 0;
}
```

---

## 作者：lzxhdxx (赞：1)

# 题解[P2984](https://www.luogu.com.cn/problem/P2984)

### 题意
输入农场个数n，m条路径和b次询问P_i和Q_i，输出从P_i号农场到1号农场到Q_i号农场的最短路径

### 方法
直接按照题意，先找从P_i到1的最短路，再找1到Q_i的最短路，跑两遍Dijkstra，两遍得出的结果相加得出答案。但是如果我们这么做会TLE。那我们应该怎么做呢？

根据题意，可以发现两次的路径都要经过1号农场，而且**每条边都是双向边**，也就是说，**每个点到1号农场的最短路径等于1号农场到每个点的最短路径**，所以我们直接把起点设置为1号农场，跑1遍Dijkstra，输出时直接输出dist[P_i]+dist[Q_i]即可

### Code：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int Max = 1000010, INF = 1e9;
int n, m, b, cnt = 0, first[Max], dist[Max];
bool vis[Max] = { false };

struct Node
{
	int u, step;
	Node(int a, int sp)
	{
		u = a; step = sp;
	}
	bool operator<(const Node& a)const
	{
		return step > a.step;
	}
};

struct edge
{
	int to, dis, next;
}e[Max];//存路径

void add_edge(int u, int v, int w)//插入新路径
{
	e[++cnt].to = v;
	e[cnt].dis = w;
	e[cnt].next = first[u];
	first[u] = cnt;
}

void add(int u, int v, int w)//双向边两个方向都插一次
{
	add_edge(u, v, w);
	add_edge(v, u, w);
}

void Dijkstra(int st)
{
	priority_queue<Node>Q;//堆优化
	Q.push(Node(st, 0));//起点距离为0
	dist[st] = 0;//起点距离为0
	while (!Q.empty())
	{
		Node it = Q.top(); Q.pop();
		int u = it.u;
		if (vis[u]) continue;//已经找到最短距离
		vis[u] = true;
		for (int i = first[u]; i; i = e[i].next)
		{
			int to = e[i].to, d = e[i].dis;
			if (d + dist[u] < dist[to] && !vis[to])//松弛操作
			{
				dist[to] = d + dist[u];
				Q.push(Node(to, dist[to]));//下一个点
			}
		}
	}
}

int main()
{
	int u, v, w, p, q;
	scanf("%d%d%d", &n, &m, &b);
	for (int i = 1; i <= n; i++) dist[i] = INF;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);//插新路径
	}
	Dijkstra(1);
	while (b--)
	{
		scanf("%d%d", &p, &q);
		printf("%d\n", dist[p] + dist[q]);//直接输出两条最短路径之和
	}
	return 0;
}
```


---

## 作者：Create_Random (赞：1)

本蒟蒻练最短路时做到此题，于是来写一下题解（极为牵强）

本蒟蒻的思路：

既然要先从A点回1点再到B点

就相当于求1点到A点和B点最短路

思路就极其简单了

注意存双向边！！！

本蒟蒻用的堆优化的Dijkstra

~~SPFA被卡怕了~~

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int to,w;
};
vector<node>g[200010];//本蒟蒻只会vector存图
struct point//运算符重载
{
    int d,dis;
    bool operator<(const point b)const {
        return dis>b.dis;
    }
};
int n,m,b;
int dis[200010];
void pri_dij(int s)//堆优化的Dijkstra模板
{
    priority_queue<point>q;
    bool vis[200010]={0};
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push({s,0});
    while(!q.empty())
    {
        point p=q.top();
        q.pop();
        int u=p.d;
        if(vis[u])
        {
            continue;
        }
        vis[u]=1;
        for(int j=0; j<g[u].size();j++)
        {
            int v=g[u][j].to,w=g[u][j].w;
            if(!vis[v]&&dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push({v,dis[v]});
            }
        }
    }
}
int main()
{
	scanf("%d%d%d",&n,&m,&b);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		node tmp;
		tmp.to=v;
		tmp.w=w;
		g[u].push_back(tmp);//
		tmp.to=u;
		g[v].push_back(tmp);//存双向边！！！
	}
	pri_dij(1);//从1开始（分别到x到y）
	for(int i=1;i<=b;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",dis[x]+dis[y]);//从x到1再到y就等于从1分别到x和y
	}
	return 0;
}
```

提交记录：
[325ms 9.11KB](https://www.luogu.org/record/23482359)

---

## 作者：_lcy_ (赞：1)

# 题目描述
---
Farmer John有$B$头奶牛$(1 \leq B \leq 25000)$，有$N(2*B \leq N \leq 50000)$个农场，编号$1 \sim N$，有$M(N-1 \leq M \leq 100000)$条双向边,第$i$条边连接农场$R_i$和$S_i$ $(1 \leq R_i \leq N;1 \leq S_i \leq N)$，该边的长度是$L_i$ $(1 \leq L_i \leq 2000)$。  
居住在农场$P_i$的奶牛$A$ $(1 \leq P_i \leq N)$，它想送一份新年礼物给居住在农场$Q_i$ $(1 \leq Q_i \leq N)$的奶牛$B$，但是奶牛$A$必须先到FJ(居住在编号$1$的农场)那里取礼物，然后再送给奶牛$B$。你的任务是：奶牛$A$至少需要走多远的路程？

# 思路
---
1. $Floyd$(复杂度太高, 舍)
2. 两遍$SPFA$，让牛$A$去到FJ是一次，从FJ到牛$B$再跑一次
于是就有了下面这份代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,B;
vector<pair<int,int> > G[50001];//first是长度，second是终点
queue<int> q;
bool inq[50001];
int d[50001];
void SPFA(int from){//SPFA
	memset(d,0x3f,sizeof(d));
	q.push(from);
	inq[from]=true;
	d[from]=0;
	while(!q.empty()){
		int t=q.front();
		q.pop();
		inq[t]=false;
		for(int i=0;i<G[t].size();i++){
			pair<int,int> t1=G[t][i]
			if(d[t]+t1.c<d[t1.second]){
				d[t1.second]=d[t]+t1.first;
				if(!inq[t1.second]){
					q.push(t1.second);
					inq[t1.second]=true;
				}
			}
		}
	}
	return;
}
int main(){
	scanf("%d%d%d",&N,&M,&B);
    for(int i=1;i<=M;i++){
    	int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back(make_pair(w,v));
        G[v].push_back(make_pair(w,u));//双向边
    }
    for(int i=1;i<=B;i++){
    	int ca,cb;
        scanf("%d%d",&ca,&cb);
        SPFA(ca);//从农场到FJ
        int ans=d[1];
        SPFA(1);//从FJ到农场
        ans+=d[cb];
        printf("%d\n",ans);
    }
	return 0;
}
```
接着你会发现   
![congratulation_TLE.jpg](https://i.loli.net/2019/07/26/5d3a99ea2574128399.jpg)   
你只有60分   

3. 你会发现，对于每个农场$A$,从农场$A$到FJ的距离和从FJ到农场$A$的距离是一样的，所以我们只用一次SPFA就可以。
```cpp
#include<bits/stdc++.h>
using namespace std;
int B,N,M;
vector<pair<int,int> > G[50001];
int d[50001];
bool inq[50001];
queue<int> q;
void spfa(int start){
    memset(d,0x3f,sizeof(d));
    memset(inq,false,sizeof(inq));
    q.push(start);
    d[start]=0;
    while(!q.empty()){
        int t=q.front();
        q.pop();
        inq[t]=false;
        for(int i=0;i<G[t].size();i++){
            int t1=G[t][i].first,t2=G[t][i].second;
            if(d[t1]>d[t]+t2){
            	d[t1]=d[t]+t2;
            	if(!inq[t1]){
            		q.push(t1);
            		inq[t1]=true;
            	}
            }
        }
    }
}
int main() {
	scanf("%d%d%d",&N,&M,&B);
	for(int i=1;i<=M;i++){
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		G[t1].push_back(make_pair(t2,t3));
		G[t2].push_back(make_pair(t1,t3));
	}
	spfa(1);//以FJ为起点SPFA
	for(int i=1;i<=B;i++){
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		printf("%d\n",d[t1]+d[t2]);
	}
    return 0;
}
```
#### 当然把SPFA改成Dijkstra照样能过
---


---

## 作者：聆雨泣 (赞：1)

看完了有些大佬的题解，说实话，有点慢，还是看我的SPFA吧，暴力又快速，优化了反而更慢
#思路：即我们在读完题后发现几个性质：1，此图为无向图。2，奶牛从p点先到一号点取礼物，然后再到q点去送礼物，也就是求p到一号点的最短路，再求一号点到q号点的最短路，相加即可。3，从1,2，两个性质看来，p到一号点的最短路就等于一到p的最短路，则此题变为求1号点到p，q两个点的最短路之和。4，以此类推，不论有几组询问，只从一号点为起点跑一遍最短路即可
#代码如下
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int maxn=50100;
const int maxm=100100;

struct Edge
{
    int to;
    int val;
    int next;
}edge[maxm*2];//邻接表

queue<int> q;//spfa所用
  
int N,M,B;

int dis[maxn],head[maxn];

bool flag[maxn];

int edgenum;

int r,s,l;

int pp,qq;//这就是题目中的p，q

void add(int u,int v,int w)//前向星存图，加边，无向图记得加两次

{

    edge[++edgenum].val=w;
    edge[edgenum].to=v;
    edge[edgenum].next=head[u];
    head[u]=edgenum;
}

void SPFA()//SPFA板子

{

    memset(flag,0,sizeof(flag));
    memset(dis,0x7f,sizeof(dis));
    q.push(1);
    flag[1]=1;
    dis[1]=0;
    while(!q.empty())
    {
        int st=q.front();
        q.pop();
        flag[st]=0;
        for(int i=head[st];i;i=edge[i].next)
        {
            int en=edge[i].to;
            if(dis[en]>dis[st]+edge[i].val)//跑最短路，不断更新
            {
                dis[en]=dis[st]+edge[i].val;
                if(!flag[en])//不在更新数组中就加进去
                {
                    flag[en]=1;
                    q.push(en);
                }
            }
        }
    }
}

int main()
{

    scanf("%d%d%d",&N,&M,&B);
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&r,&s,&l);
        add(r,s,l);
        add(s,r,l); 
    }
    SPFA();
    while(B--)//此处为重点，无向图，一遍计算加边即可
    {
        scanf("%d%d",&pp,&qq);
        printf("%d\n",dis[pp]+dis[qq]);//核心思路，利用无向图的性质，跑一遍最短路的成果
    }
    return 0;
}
```
如上，谢谢

---

## 作者：Zekrom (赞：1)

第一面的题解写了份最短路也太累了吧  
首先看题目是双向边，就不用考虑建反边了  
那么距离很明显就是d[u]+d[v]  
最短路求d数组 
上代码  //93ms  
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 51010
#define M 200010
using namespace std;
int n,m,tot,head[N],d[N],s,t,b;
bool vis[N];
struct Edge{
	int v,u,next,val;
}edge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return  x*f;
}
inline void add(int x,int y ,int z){edge[++tot].v=y;edge[tot].next=head[x];head[x]=tot;edge[tot].val=z;edge[tot].u=x;}
void spfa(int x){
	queue<int>q;
	memset(d,0x3f,sizeof(d));
	q.push(x);d[x]=0;vis[x]=1;
	while(q.size()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z=edge[i].val;
			if(d[v]>d[u]+z){
				d[v]=d[u]+z; 
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int main()
{
	n=read();m=read();b=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z); 
	}
	spfa(1);
	for(int i=1;i<=b;i++){
		int x=read(),y=read();
		printf("%d\n",d[x]+d[y]);
	}
	return 0;
}

```


---

## 作者：Most_Goodlooking (赞：0)

**看到这题首先第一个想法就是跑两遍，从Pi跑一次Qi跑一次，但时间复杂度
~~GG~~**

我们可以换一种思维方式，因为无向，奶牛从**Pi跑到1点等同于从1点跑到Q点**，

所以我们只需要从**1点开始SPFA遍历****一遍(是的，你没看错，一遍就行)**。然后对应的Pi在图中的数据+Qi即可。
时间比较赶，代码两三天后补。

这题只要脑子转得过弯来其实很水。

```cpp
#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct node
{
    int to;
    int walk;
};//存图
bool vis[100005]={};//是否访问
long long int out[100005];//图中最短路数据
vector<node> line[100005];
int cow1,cow2;
queue<int> que;
inline int read(){
    int res=0;char c=getchar();
    while(c>'9'||c<'0'){c=getchar();};
    while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+c-'0';c=getchar();};
    return res;
}//快读
int main(void){
    memset(out,0x3f,sizeof(out));
    int n=read(),m=read(),b=read(),u,v,w;
    for (int i = 0; i < m; i++)
    {
        u=read();v=read();w=read();
        line[u].push_back((node){v,w});
        line[v].push_back((node){u,w});
    }//建图
    vis[1]=1;
    out[1]=0;
    que.push(1);//打标记
    while (!que.empty())
    {
        int now=que.front();
        que.pop();
        vis[now]=0;
        for (int i = 0; i < line[now].size(); i++)
        {
            if (out[now]+line[now][i].walk<out[line[now][i].to])
            {
                out[line[now][i].to]=out[now]+line[now][i].walk;
                if (!vis[line[now][i].to])
                {
                    vis[line[now][i].to]=1;//记住这个标记不能忘，否则80，90分。
                    que.push(line[now][i].to);
                }
            }
        }
    }
    for (int i = 0; i < b; i++)
    {
        cow1=read();cow2=read();//输出
        printf("%lli\n",out[cow1]+out[cow2]);//第一个数为Pi到1号点最短路，第二个数为1号点到Qi点的最短路。
    }
    return 0;
}
```


---

## 作者：Invisible_Blade (赞：0)

由于题目中说点数N达到25000，所以用邻接矩阵肯定存不下，要用邻接表(链式前向星)。
题目的目的是求A到1再到B的最短路。因为是无向图，所以只要走一遍SPFA就知道1到i(1<=i<=n)的最短路了。如果是有向图，则要建反向图，跑两次SPFA，显然这里不需要。
接下来介绍SPFA与邻接表。


------------
**SPFA：**

即用队列优化对Bellman Ford算法的优化。时间复杂度O(VE)。
设立一个先进先出的队列用来保存待优化的结点，优化时每次取出队首结点u，并且用u点当前的最短路径估计值对离开u点所指向的结点v进行松弛操作，如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。这样不断从队列中取出结点来进行松弛操作，直至队列空为止。
定理：只要最短路径存在，上述SPFA算法必定能求出最小值。证明：每次将点放入队尾，都是经过松弛操作达到的。换言之，每次的优化将会有某个点v的最短路径估计值dis[v]变小。所以算法的执行会使dis越来越小。由于我们假定图中不存在负权回路，所以每个结点都有最短路径值。因此，算法不会无限执行下去，随着dis值的逐渐变小，直到到达最短路径值时，算法结束，这时的最短路径估计值就是对应结点的最短路径值。


------------
**邻接表：**

邻接表，存储方法跟树的孩子链表示法相类似，是一种顺序分配和链式分配相结合的存储结构。如这个表头结点所对应的顶点存在相邻顶点，则把相邻顶点依次存放于表头结点所指向的单向链表中。
邻接表是图的一种最主要存储结构,用来描述图上的每一个点。对图的每个顶点建立一个容器（n个顶点建立n个容器），第i个容器中的结点包含顶点Vi的所有邻接顶点。实际上我们常用的邻接矩阵就是一种未离散化每个点的边集的邻接表。
在有向图中，描述每个点向别的节点连的边（点a->点b这种情况）。
在无向图中，描述每个点所有的边(点a-点b这种情况)


------------
**总算说完了，接下来上code：**


------------
```
#include<bits/stdc++.h>
#define N       1000001	//数据范围
#define inf       1e8+1 //设最大值
#define re register int 
#define read(x) scanf("%d",&x) //简写读入
using namespace std;
struct Edge{
	int to,next,w;
}e[N];					//邻接表结构体,next是第i边的下条边的编号i'
int first[N],dis[N],vis[N];  //first存第i个点的第一条边
int n,m,b,u,v,w,x,y,tot;	//tot指存入了tot条边
void add(int,int,int);		//加边函数
void Spfa();				//SFPA函数
int main(){
	read(n);read(m);read(b);
	for(re i=0;i<m;++i){
		read(u);read(v);read(w);
		add(u,v,w);add(v,u,w);
	}
	Spfa();
	for(re i=0;i<b;++i){
		read(x);read(y);
		printf("%d\n",dis[x]+dis[y]);
	}
	return 0;
}
void add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].w=w;
	e[tot].next=first[u];
	first[u]=tot;
}
void Spfa(){
	queue<int> q;
	for(re i=1;i<=n;++i) dis[i]=inf;
	dis[1]=0,q.push(1),vis[1]=1;
	while(!q.empty()){
		int k=q.front();
		q.pop(),vis[k]=0;
		for(re i=first[k];i;i=e[i].next)
			if(dis[e[i].to]>dis[k]+e[i].w){
				dis[e[i].to]=dis[k]+e[i].w;
				if(!vis[e[i].to]){
					q.push(e[i].to);
					vis[e[i].to]=1;
				}
			}
	}
}
```


---

## 作者：tcswuzb (赞：0)

### 本蒟蒻就是喜欢DIJKSTRA堆优化

第一次提交 TLE
```cpp
ll u,v;read(u);read(v);
DIJKSTRA(u);ll ans=dis[1];
DIJKSTRA(1);
printf("%lld\n",ans+dis[v])；
```
跑了两次DIJ

后来经楼下dalao提醒 因为是无向图 

所以 dis[i][j]=dis[i][j]
仅需要计算 从一到其他节点的最短路径即可

第二次提交 再次TLE

```cpp
ll u,v;read(u);read(v);
DIJKSTRA(1);
printf("%lld\n",dis[u]+dis[v]);
```

睁大眼睛一看 只要求一次就行了 问一次求一次 闹着玩呀？

~~我还是太蒟蒻了~~

第三次 AC

# CODE：

```cpp
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<stack>
#include<list>
#include<set>
#include<deque>
#include<vector>
#include<ctime>
#define ll long long
#define inf 0x3f3f3f3f
#define N 500008
#define IL inline
#define M 1008611
#define D double
#define ull unsigned long long
#define R register
using namespace std;
template<typename T>void read(T &a)
{
    T x=0,f=1;char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=0;ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';ch=getchar();
    }
    a=f?x:-x;
}
/*-------------OI使我快乐-------------*/
struct Node{
    ll nex,to,wi;
}e[N>>1];
ll n,m,b,tot;
ll dis[N>>1],vis[N>>1],head[N>>1];
IL void add(ll ai,ll bi,ll ci){
    e[++tot].to=bi;
    e[tot].wi=ci;
    e[tot].nex=head[ai];
    head[ai]=tot;
}
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > Q;
IL void DIJKSTRA(ll now){//DIJKSTRA堆优化 模板
    while(!Q.empty()) Q.pop();
    for(R ll i=1;i<=n;++i) dis[i]=inf,vis[i]=0;
    Q.push(make_pair(0,now));dis[now]=0;
    while(!Q.empty())
    {
        ll u=Q.top().second;Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(R ll i=head[u];i;i=e[i].nex)
        {
            ll v=e[i].to;
            if(dis[v]>dis[u]+e[i].wi)
            {
                dis[v]=dis[u]+e[i].wi;
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);read(m);read(b);
    for(R ll i=1;i<=m;++i)
    {
    	ll xi,yi,zi;read(xi);read(yi);read(zi);
    	add(xi,yi,zi);add(yi,xi,zi); 
    }
    DIJKSTRA(1);
    for(R ll i=1;i<=b;++i)
    {
        ll u,v;read(u);read(v);
        
        printf("%lld\n",dis[u]+dis[v]);
    }
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}

```

NOIP 2018 即将到来

祝愿各位 RP++

---

## 作者：PTC06 (赞：0)

发现楼上全是spfa没有dijkstra赶紧写一波题解233

其实这题和最短路的模板没有多少差别？

这里用的是堆优化的dijkstra。


思路：

读入，很明显邻接矩阵会炸，那么用边表存每一条边的信息。

然后基本和最短路模板一样。

由于题目说到a必须先到1再到b，那么其实这等于（1到A的最短路+1到B的最短路）。

所以，把1当作开始的点来dijkstra，对每一个点找最短路，将1到每一个点的最短路存到dis[]数组里。

然后每次输入a,b时直接输出dis[a]+dis[b]就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=500005,MAXM=1000005;
int n,m,b,i,f,t,d,head[MAXN],dis[MAXN],st,e,j,tot,vis[MAXN];
struct point
{
    int nm;
    int dis;
    bool operator <(const point & other) const
    {
        return this->dis<other.dis;
     } 
};
multiset<point> s;
struct ed
{
    int v;
    int w;
    int next;
} edge[MAXM];
void add(int u,int v,int w)
{
    tot++;
    edge[tot]=(ed){v,w,head[u]};
    head[u]=tot;
}
void Dijkstra(int start)
{
    dis[start]=0;
    s.insert((point){start,0});
    while (!s.empty())
    {
        int now=s.begin()->nm;
        s.erase(s.begin());
        if (vis[now]) continue;
        vis[now]=1;
        for (j=head[now];j!=-1;j=edge[j].next)
        {
            int temp=edge[j].v;
            if (dis[temp]>dis[now]+edge[j].w && !vis[temp])
            {
                dis[temp]=dis[now]+edge[j].w;
                s.insert((point){temp,dis[temp]});
            }
        }
     } 
}
int main()
{
    memset(head,-1,sizeof(head));
    memset(dis,999999,sizeof(dis));
    cin>>n>>m>>b;
    for (i=1;i<=m;i++)
    {
        cin>>f>>t>>d;
        add(f,t,d);
        add(t,f,d);
    }
    Dijkstra(1);
    for (i=1;i<=b;i++)
    {
        cin>>st>>e;
        cout<<dis[st]+dis[e]<<endl;
    }
}
```

---

## 作者：Deny_小田 (赞：0)

用SPFA求最短路。

看了看楼上的代码，发现是用前向星做的，我就直接使用邻接矩阵存了= =

上代码吧：

```cpp
// 先尝试使用 spfa 来求最短路 
#include <cstdio>
#include <queue>
#include <vector>

using namespace std; 

// 由于 n 较大，邻接矩阵容易炸内存，采用 spfa 求最短路 

const int size = 50005, inf = 1 << 26;
int dis[size], inq[size];
vector< pair<int, int> > vi[size];
queue<int> q;
int n, m, b;

#define pb push_back
#define mp make_pair

void init() {
    for(int i = 0; i < size; i++) vi[i].clear();
    for(int i = 0; i < size; i++) dis[i] = inf;
    for(int i = 0; i < size; i++) inq[i] = 0;
}

void SPFA() { 
    q.push(1);
    inq[1] = 1;
    dis[1] = 0;
    
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        inq[now] = 0;
        
        for( int i = 0; i < vi[now].size(); i++) {
            int v = vi[now][i].first;
            
            if(dis[v] > dis[now]+vi[now][i].second){
                dis[v] = dis[now]+vi[now][i].second;
                
                if(inq[v] == 1) continue;
                inq[v] = 1;
                q.push(v); 
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &b);
    init();
    
    for(int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        vi[x].pb( mp(y, z) );
        vi[y].pb( mp(x, z) ); 
    }
    
    SPFA();
    for(int i = 0; i < b; i++) {
        int x1, x2;
        scanf("%d %d", &x1, &x2);
        printf("%d\n", dis[x1]+dis[x2]);
    }
    
    return 0;
}
```

---

## 作者：Drug__Lover (赞：0)

0. 裸SPFA

0. 看代码

- 顺便脑补一下SPFA

```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct Edge
{
    int next;    //下一条边的编号 
    int to;     //这条边到达的点 
    int cost;   //这条边的长度 
}edge[100001];    //数组模拟邻接表 
int head[100001],cnt,n,m,u,v,d;
int vis[100001],dis[100001];    //dis[]记录从起点s到i的最短路径 ，vis[]记录一个点是否现在存在队列中 
int team[100001];   //队列 
void add(int from,int go,int l)  //加入一条从from到to距离为dis的单向边 
{
    edge[++cnt].next=head[from];
    edge[cnt].to=go;
    edge[cnt].cost=l;
    head[from]=cnt;
}
void spfa()
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x7f,sizeof(dis));
    int h=0,t=1;
    dis[1]=0;
    vis[1]=1;
    team[1]=1;//初始化7条 
    while(h<t)
    { 
        h++;         //头指针向下移一位，取出指向的点U 
        u=team[h];    
        vis[u]=0;  //已被取出了队列 
        for(int i=head[u];i!=0;i=edge[i].next)  //用数组模拟邻接表 ，for与u相连的所有点v 
        {
            int to=edge[i].to;          
            if(dis[to]>dis[u]+edge[i].cost)
            {
                dis[to]=dis[u]+edge[i].cost;
                if(vis[to]==0)      //队列中不存在v点，v入队 
                {
                    t++; //指针下移一位，v入队 
                    team[t]=to;
                    vis[to]=1;
                }
            }
        }
    }
}
int N,M,B;
int main()
{
    cin>>N>>M>>B;     //读入点数和边数 
    for(int i=1;i<=M;i++)    
    {
        int x,y,k;     //x，y之间有一条长度为d的边 
        cin>>x>>y>>k;  
        add(x,y,k);  
        add(y,x,k);
    }
    spfa();
    for(int i=1;i<=B;i++)
    {
        int x,y;
        cin>>x>>y;
        cout<<dis[x]+dis[y]<<endl;
    }
    return 0;
}
```

---

