# 买还是建 Buy or Build

## 题目描述

万维网（WWN）是一家运营大型电信网络的领先公司。 WWN希望在Borduria建立一个新的网络，您需要帮助WWN确定如何以最低的总成本设置其网络。有几个本地公司运营着一些小型网络（以下称为子网），部分覆盖了Borduria的n个最大城市。 WWN希望建立一个连接所有n个城市的网络。 要实现这一目标，它可以从头开始在城市之间建设网络，也可以从本地公司购买一个或多个子网。 您需要帮助WWN决定如何以最低的总成本建设其网络。

1、所有n个城市都给出其二维坐标

2、存在q个子网。 如果q≥1,给出每个子网中连接的城市。（不用关心连接的形状）

3、每个子网只能购买，不能被分割

4、连接两个不相通的城市，必须建立一个边，其建设成本是城市之间欧几里德距离的平方。

您的任务是决定购买哪些现有网络以及建设哪些边，使得总成本最低。

## 样例 #1

### 输入

```
1
7 3
2 4 1 2
3 3 3 6 7
3 9 2 4 5
0 2
4 0
2 0
4 2
1 3
0 5
4 4
```

### 输出

```
17
```

# 题解

## 作者：Maktub (赞：23)

思路和紫书上是一样的，不过代码是我自己的代码（只有读入和输出看了下代码仓库, ~~瞄了两眼题解~~）， 咳咳。

不太喜欢用vector，而且自己写的不一样的Kruskal函数。。。

好吧，让我自己写是肯定写不出来的，下面我深入解释一下这道题的做法。

# 进入正题

紫书的思路： 先求一次最小生成树， 然后枚举套餐的所有组合，再求最小生成树，所有方案中取最优值。

这个方法的正确性紫书上已经证明， 下面重点是如何实现。

**希望大家先自己想， 感觉有点卡就看看下面的实现思路， 实在没办法再看代码。毕竟做法已经给出，不同的人有不同的实现方法**

- 首先是要读入了， ~~UVA好多毒瘤读入~~， PDF里说每组数据输入时用一个空行隔开， 其实用不用getline吃空行都一样。

 然后就是输出了，注意每组输出数据要用空行隔开（不然会WA）。

 输入套餐时是给你个size， 和花费， 然后输入点。

- 然后是连边了，边输入边连就好，边全并不是两点间的距离，而是两点间距离的平方（也就是不用sqrt（）直接返回就好，又一个坑）

- 连完边跑一次最小生成树，把生成树中的边记录下来，其他边就可以丢掉了，剩下的边成为新图中的边。

 以后跑最小生成树也是不用排序的，这是很显然的事情。
 
- 相信以上步骤是很轻松就能完成的。下面进入重点。

 首先是枚举套餐组合， 最方便的方法就是用状压（~~学完状压DP感觉哪里都能用状压~~）。。 具体方法就不介绍了，实在不懂建议先学学状压， 这里用的状压还是相当简单的。 
 
 难点到了（对于我来说），如何将套餐中的点用与建最小生成树呢？
 
 ~~我想了一会没思路，打开了题解。~~（就这里喵了两眼）
 
 方法是，先把费用加上，然后用套餐中的点先建树，然后再用新图中的边建树， 再比较一下费用，取最优解。
 
- 最后输出就完了，注意输出的空行哦。
 
下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<map>
#include<queue>
#include<vector>
#include<set>
#include<cmath>
#include<sstream>
using namespace std;
#define ll long long

const int mx = 1111;

struct edge{
	int u, v, w;
}a[mx * mx], nw[mx*3];
int edge_size; // a为原边， nw为筛出来的边。原边个数需要记录，新边当然是n-1条。 



int T, n, m;
string line; 
int x[mx], y[mx];//题目条件 

int st[11][mx], size[11], mon[11];//套餐 

int fat[mx];//并查集 
inline int find(int x) { return fat[x] == x ? x : fat[x] = find(fat[x]); }
inline void reset() { for(int i = 1; i <= n; i++)fat[i] = i; }

//建图 
inline int diss(int i, int j) { return  (x[i]-x[j]) * (x[i]-x[j]) + (y[i]-y[j]) * (y[i]-y[j]); }
inline void addedge(int k){
	for(int i = 1; i < k; i++) {
		edge_size++;
		a[edge_size].u = i; a[edge_size].v = k; a[edge_size].w = diss(i, k);
	}
}

inline int cmp(edge x, edge y){
	return x.w < y.w;
}

//返回花费，tot为已经有了多少边,cnt为要处理的边集合的数量，op为处理旧图还是新图,cost为已经花了多少钱。 
inline int Kruskal(int tot, int cnt, int op, int cost){
	
	int sum = cost;
	if(op){
		for(int i = 1; i <= cnt; i++){
		int fu = find(a[i].u), fv = find(a[i].v);
		if(fu != fv){
			fat[fu] = fv;
			tot++;
			sum += a[i].w;
			if(op)nw[tot] = a[i];
			if(tot == n-1)break;
		}
	}
	}
	else{
		for(int i = 1; i <= cnt; i++){
		int fu = find(nw[i].u), fv = find(nw[i].v);
		if(fu != fv){
			fat[fu] = fv;
			tot++;
			sum += nw[i].w;
			if(tot == n-1)break;
		}
	}
	}
	return sum;
	
}

inline int solve(int cost){
	
	int ans = cost;
    
	for(int S = 0; S < (1<<m); S++){
		
		reset();
		
		int tot = 0;
		int need = 0;
		for(int q = 1; q <= m; q++){
			if(S & (1<<(q-1))){
			
			need += mon[q];
			for(int i = 1; i < size[q]; i++){
				for(int j = i+1; j <= size[q]; j++){
					
					int u = find(st[q][i]), v = find(st[q][j]);
					if(u != v){
						fat[u] = v;
						tot++;
					}
				}
			}
		}
		}
		ans = min(ans, Kruskal(tot, n-1, 0, need));
		
		
	}
	return ans;
}

int main(){
    cin >> T;
    while(T--){
    	edge_size = 0;
   // 	memset(size, 0, sizeof(size));
    //	memset(fat, 0, sizeof(fat));
    	
    	
    	getline(cin, line);//有没有都行
    	
    	scanf("%d %d", &n, &m);
    	
    	for(int i = 1; i <= m; i++){
    		scanf("%d %d", &size[i], &mon[i]);
    		for(int j = 1; j <= size[i]; j++)scanf("%d", &st[i][j]);
		}
    	for(int i = 1; i <= n; i++){
    		scanf("%d%d", &x[i], &y[i]);
    		addedge(i);
		}
		
		sort(a + 1, a + edge_size + 1, cmp);
		
		reset();
		
		int  cost = Kruskal(0, edge_size, 1, 0);
		
		printf("%d\n", solve(cost));
		if(T)putchar('\n');
	}
	return 0;
}


```

---

## 作者：hulean (赞：10)

## 【题意】

平面上有$n(n<=1000)$个点，你的任务是让所有n个点联通。为此，你可以新建一些边，费用等于两个端点的**欧几里得距离*平方***。另外还有$q(q<=8)$个套餐可以购买，如果你购买了第$i$个套餐，该套餐中的所有结点将变得相互连接。第$i$个套餐的花费为$C_i$。

## 【算法】

$Kruskal$

## 【分析】

最容易想到的算法是：先枚举购买**哪些**套餐，把套餐中包含的权值设为$0$，然后求最小生成树。由于枚举量为$O(2^q)$，给边排序的时间复杂度为$O(n^2logn)$，而排序之后每次$kruskal$算法的时间复杂度为$O(n^2)$，因此总时间复杂度为$O(2^qn^2+n^2logn)$，对于题目来说的规模太大了。

只需一个小小的优化即可降低时间复杂度：先求一次原图 **(不购买任何套餐)** 的最小生成树，得到$n-1$条边，其余的边就没用了。然后枚举买哪些套餐（这里可以用状态压缩的思想），则枚举套餐后再求最小生成树时，图上的边已经寥寥无几。

**为什么可以这样呢？** 大部分题解都没有证明。这里给出**证明过程**

首先回顾一下，在$kruskal$算法中，哪些边不会进入最小生成树。答案是：两端已经属于同一个集合的边。买了套餐后，相当于一些边的边权变成了$0$，而对于不在套餐中的每条边$e$，排序在$e$之前的边一个都没少，反而还多了一些权值为$0$的边，所以在原图$kruskal$时被“扔掉”的边，在后面的枚举套餐中也一样会被扔掉。

## 【代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
const int MAXM=MAXN*MAXN;
int n,q,T,ans=0x3f3f3f3f;
int s[10][MAXN];
int c[10];
struct Node2
{
    int x,y;
}city[MAXN];
struct Node
{
    int u,v,w;
}edge[MAXM],g[MAXM];
int cnt,m;
int fa[MAXN];
int save[MAXN];
inline int read()
{
    int tot=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        tot=tot*10+c-'0';
        c=getchar();
    }
    return tot;
}
inline bool cmp(Node x,Node y)
{
    return x.w<y.w;
}
inline int find(int k)
{
    if(fa[k]==k)return k;
    else return fa[k]=find(fa[k]);
}
inline int init_kruskal()
{
    int tot=0,cc=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=cnt;i++)
    {
        if(fa[find(edge[i].u)]!=fa[find(edge[i].v)])
        {
            fa[find(edge[i].u)]=find(edge[i].v);
            tot++;
            cc+=edge[i].w;
            save[tot]=i;//记录边
        }
        if(tot==n-1)break;
    }
    return cc;
}
inline int kruskal(int tot)
{
    int cc=0,t=tot;
    for(int i=1;i<n;i++)
    {
        if(find(g[i].u)!=find(g[i].v))
        {
            fa[find(g[i].u)]=find(g[i].v);
            t++;
            cc+=g[i].w;
        }
        if(t==n-1)break;
    }
    return cc;
}
inline void solve()
{
    for(int ss=0;ss<(1<<q);ss++)//状压思想，用二进制来表示选还是不选
    {
        for(int i=1;i<=n;i++)
        fa[i]=i;//初始化并查集
        int tot=0;//选中套餐中被连接的点数
        int cc=0;//套餐的钱
        for(int k=1;k<=q;k++)
        {
            if(ss&(1<<(k-1)))//如该套餐被选中
            {
                //cout<<k<<" ";
                cc+=c[k];
                for(int i=1;i<=s[k][0];i++)
                {
                    for(int j=i+1;j<=s[k][0];j++)
                    {
                        //cout<<s[k][0]<<" "<<k<<" "<<s[k][i]<<" "<<s[k][j]<<endl;
                        if(find(s[k][i])!=find(s[k][j]))
                        {
                            fa[find(s[k][i])]=find(s[k][j]);
                            tot++;
                        }
                    }
                }
            }
        }
        //cout<<endl;
        //cout<<cc<<endl;
        //cout<<tot<<" "<<kruskal(tot)<<" "<<cc<<endl;
        ans=min(ans,kruskal(tot)+cc);//更新最小值
    }
}
int main()
{
    T=read();
    while(T--)
    {
        cnt=0;
        n=read();q=read();
        for(int i=1;i<=q;i++)
        {
            s[i][0]=read();c[i]=read();
            for(int j=1;j<=s[i][0];j++)
                s[i][j]=read();//读入套餐
        }
        for(int i=1;i<=n;i++)
            city[i].x=read(),city[i].y=read();
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                edge[++cnt].u=i;
                edge[cnt].v=j;
                edge[cnt].w=(city[i].x-city[j].x)*(city[i].x-city[j].x)+(city[i].y-city[j].y)*(city[i].y-city[j].y);
            }
        }
        sort(edge+1,edge+1+cnt,cmp);
        ans=init_kruskal();//原始图的最小生成树
        //cout<<ans<<endl;
        for(int i=1;i<n;i++)
        {
            g[i].u=edge[save[i]].u;
            g[i].v=edge[save[i]].v;
            g[i].w=edge[save[i]].w;
        }//建一个新图
        /*for(int i=1;i<n;i++)
        {
            cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].w<<endl;
        }
        cout<<endl;*/
        solve();//准备枚举
        cout<<ans<<endl;
        if(T)cout<<endl;//UVA不会省略最后的换行符
    }
    return 0;
}
```

---

## 作者：CNCAGN (赞：5)

# 题目分析
输入了一些点的坐标信息，然后通过某些操作要以最小代价连接整个图，首先显然点和点之间可以全部建边，然后题干重点在以最小代价连接整个图，可以想到最小生成树。这题特别之处就是增加了一个子网概念，以固定花费连接某些点。

深入分析一下的话，子网的概念可以抽象成花费固定值，将某些点之间建立花费为零的连接，这样的话子网的概念和其他常规边就可以联系起来了，这样就初步有思路了：

外层循环首先枚举购买哪些子网，然后花费先统计一下子网的花费，并把子网要求连接的点连起来，再从所有的边里跑一边最小生成树将剩下没有连接的点连起来并统计费用即可。

但分析一下，最外层最多是 $O(2^q)$ ，里面运行了一遍最大 $O(qn)$ 的子网包含点连接操作和 $O(n^2)$ 的最小生成树，总的时间复杂度有 $O(2^qn^2)$ 肯定会爆。分析一下瓶颈在哪里，是最小生成树操作足足 $O(n^2)$ 。那么怎么优化一下呢？

可以看出，先把那些子网连好的点连好之后，剩下的问题就是把孤立的点和子网连好的部分连接起来，这便是最小生成树作用所在。

这里最关键的是，_这部分进行的操作所连的边_ **⊆** _原图进行一遍最小生成树所连的边_ 。因为我们只可以使用原图中的边进行连接且最优情况依然符合 Kruskal 算法的： _从最短且有效的边开始连_  的策略。

这样就可以进行有效优化了，先把原图跑一边 Kruskal 最小生成树，然后删掉不可能使用的边再解决问题就可以了。（实际上为了便于编码，将可能使用的边单独存储而不是删掉不用的边）

# 一些细节
Kruskal 的边排序时使用的间接排序，简单说就是排序编号不动原数组，大抵可以省下一些常数。 

这题用了很多变量数组，写题时可以随时注释以免忘记作用。

特别要点名 ~~表扬~~ 的是 UVA 的* *输出， _“每组输出之间用一个空行隔开”_ 所以说每输出一个答案还得多空一行（除了最后一个） 。 

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<deque>
#include<map>
#include<unordered_map>
using namespace std;
inline int red() {//fast read
    int op = 1, x = 0;
    char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-')   op = -1;
        ch = getchar();
    }
    while(isdigit(ch)) {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return op * x;
}

const int maxn = 1010, maxm = 1000010;
const int inf = 0x7f7f7f7f;

int n, q, m;
int c[10];//每组花费
int num[10];//每组连接点个数
int contain[10][maxn];//每组连接的点
pair<int, int> posi[maxn];//位置输入数据

int fa[maxn];//并查集
int u[maxm], v[maxm], w[maxm];//完全图
int r[maxm];//间接排序
int uu[maxn], vv[maxn], ww[maxn];//生成树之后的图

int tot = 0;

bool cmp(const int &i, const int &j) {
	return w[i] < w[j];
}
int find(int x) {
	if(fa[x] != x) {
		fa[x] = find(fa[x]);
	}
	return fa[x];
}

int main() {
	int T = red();
	while(T--) {
		n = red(), q = red();
		m = 0;
		for(int i = 0; i < q; ++i) {
			num[i] = red();
			c[i] = red();
			for(int j = 1; j <= num[i]; ++j) {
				contain[i][j] = red();
			}
		}
		for(int i = 1; i <= n; ++i) {
			posi[i].first = red();
			posi[i].second = red();
		}
		for(int i = 1; i <= n; ++i) {
			for(int j = i + 1; j <= n; ++j) {
				u[++m] = i;
				v[m] = j;
				w[m] = (posi[i].first - posi[j].first) * (posi[i].first - posi[j].first) + (posi[i].second - posi[j].second) * (posi[i].second - posi[j].second);
			}
		}
		for(int i = 1; i <= m; ++i) {
			r[i] = i;
		}
		sort(r + 1, r + 1 + m, cmp);
		tot = 0;
		for(int i = 1; i <= n; ++i) {
			fa[i] = i;
		}
		for(int i = 1; i <= m; ++i) {
			int x = find(u[r[i]]), y = find(v[r[i]]);
			if(x != y) {
				fa[x] = y;
				ww[++tot] = w[r[i]];
				uu[tot] = u[r[i]];
				vv[tot] = v[r[i]];
			}
			if(tot == n - 1) {
				break;
			}
		}
		m = n - 1;
		int res = inf;
		int cost;
		for(int i = 0; i < (1 << q); ++i) {
			cost = 0;
			for(int j = 1; j <= n; ++j) {
				fa[j] = j;
			}
			for(int j = 0; j < q; ++j) {
				if(i & (1 << j)) { 
					cost += c[j];
					for(int k = 2; k <= num[j]; ++k) {
						int x = find(contain[j][k - 1]), y = find(contain[j][k]);
						if(x != y) {
							fa[x] = y;
						}
					}
				}
			}
			for(int j = 1; j <= m; ++j) {
				int x = find(uu[j]), y = find(vv[j]);
				if(x != y) {
					fa[x] = y;
					cost += ww[j];
				}
			}
			res = min(res, cost);
		}
		printf("%d\n", res);
		if(T) {
			puts("");//！！
		}
	}
    return 0;
}
```


---

## 作者：小闸蟹 (赞：3)

```cpp
// 这一题考的是最小生成树
// 具体的解释还是看紫书P358比较好
// 我只是代码的搬运工，并且写一点注释供大家参考
// 希望能对大家理解这一题提供一点点的帮助
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

constexpr int MaxN = 1000 + 10;
constexpr int MaxQ = 8;

int n;
std::array<int, MaxN> x{ 0 }, y{ 0 }, p{ 0 };
std::array<int, MaxQ> Cost{ 0 };
std::array<std::vector<int>, MaxQ> SubN;

int Find(int x)
{
    return p[x] != x ? p[x] = Find(p[x]) : x;
}

class Edge
{
public:
    int u, v, d;

    Edge() = default;
    Edge(int u, int v, int d) :
        u(u), v(v), d(d)
    {
    }
};

// cnt：还剩多少个点没有联通
// e：边的集合
// Used：已经联通的边
template <typename T>
int MST(int cnt, const T &e, T &Used)
{
    if (cnt == 1)
    {
        return 0;
    }

    int Ans = 0;
    Used.clear();
    for (std::size_t i = 0; i < e.size(); ++i)  // Kruskal
    {
        int u = Find(e[i].u), v = Find(e[i].v);
        if (u != v)
        {
            p[u] = v;
            Ans += e[i].d;
            Used.push_back(e[i]);   // 在第一次调用Kruskal时，Used被用来求生成树

            if (--cnt == 1)
            {
                break;
            }
        }
    }

    return Ans;
}

// 快读
int Read()
{
    int n = 0, k = 1;
    char ch = getchar();
    while ((ch > '9' || ch < '0') && ch != '-')
        ch = getchar();

    if (ch == '-')
    {
        k = -1;
        ch = getchar();
    }

    while (ch <= '9' && ch >= '0')
    {
        n = n * 10 + ch - '0';
        ch = getchar();
    }

    return n * k;
}

int main()
{
    int T;
    std::cin >> T;  // 共T组数据
    while (T--)
    {
        int q;
        n = Read(); // 有n条边
        q = Read(); // 有q种套餐
        for (int i = 0; i < q; ++i)
        {
            int cnt;    // 这个套餐能连cnt个点
            cnt = Read();
            Cost[i] = Read();   // 该套餐的花费

            SubN[i].clear();    // 因为有多组数据，所以要记得清空
            while (cnt--)
            {
                int u;
                u = Read();
                SubN[i].push_back(u - 1);   // 记录套餐i能连的边
            }
        }
        for (int i = 0; i < n; ++i) // 记录每个点的(x, y)坐标
        {
            x[i] = Read();
            y[i] = Read();
        }

        std::vector<Edge> e;
        for (int i = 0; i < n; ++i) // 生成整张图的点边信息
        {
            for (int j = i + 1; j < n; ++j)
            {
                int c = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                e.emplace_back(i, j, c);
            }
        }
        
        // 排序，为Kruskal做准备
        std::sort(e.begin(), e.end(), [](const Edge &a, const Edge &b)
        {
            return a.d < b.d;
        });

        for (int i = 0; i < n; ++i)
        {
            p[i] = i;
        }
        std::vector<Edge> Need; // 求最小生成树里有什么边
        int Ans = MST(n, e, Need);  // 在没使用套餐之前先求一次最小生成树
        for (int Mask = 0; Mask < (1 << q); ++Mask) // 枚举每个套餐的使用情况
        {                                           // 看不懂位运算的可以先去看一下状压
            for (int i = 0; i < n; ++i) // 每次都重新初始化一次并查集
            {
                p[i] = i;
            }

            int cnt = n, c = 0;
            for (int i = 0; i < q; ++i)
            {
                if (Mask & (1 << i))    // 检验用不用i套餐
                {
                    c += Cost[i];   // c是总经费
                    for (std::size_t j = 1; j < SubN[i].size(); ++j)
                    {
                        // 把该套餐中的边都加入生成树中
                        int u = Find(SubN[i][j]), v = Find(SubN[i][0]);
                        if (u != v)
                        {
                            p[u] = v;
                            --cnt;
                        }
                    }
                }
            }

            std::vector<Edge> Dummy;    // 没什么用的变量
            Ans = std::min(Ans, c + MST(cnt, Need, Dummy));
        }

        std::cout << Ans << std::endl;
        if (T)
        {
            std::putchar('\n');
        }
    }

    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

~~蒟蒻第一次写紫题题解~~

更好的题面翻译见紫书。

[模板题](https://www.luogu.com.cn/problem/P3366)。

## 思路

本题需使用 Kruskal 算法。

对于每组数据

- 先将这些城市两两建边，然后排序（普通 Kruskal 的步骤）。

- 因为 $q\le 8$，所以我们可以使用状压暴力的枚举套餐的使用情况。

- 枚举的过程：

	- 将套餐中的点依次连边；

	- 再把剩下没连完的边从排序的结果取出（普通 Kruskal 的步骤）；
    
   - 将得到的最小生成树的边权与答案取 $\min$。

- 最后输出答案即可。

注意本题**每两组测试数据之间也有一个空白行**。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int F[1005];
int num,sum;
int find(int x){
	if(x==F[x]) return x;
	F[x]=find(F[x]);
	return F[x];
}
void add(int x,int y,int val){
	x=find(x),y=find(y);
	if(x==y) return ;
	F[x]=y;
	sum+=val;
	++num;
}
int s[10],c[10];
int u[10][1005];
int aa[1005],b[1005];
struct Edge{
	int u,v,w;
}a[1000005];
bool cmp(Edge x,Edge y){
	return x.w<y.w;
}
void work(){
	int n,q;
	cin>>n>>q;
	
	for(int i=1;i<=q;++i){
		cin>>s[i]>>c[i];
		for(int j=1;j<=s[i];++j){
			cin>>u[i][j];
		}
	}
	for(int i=1;i<=n;++i){
		cin>>aa[i]>>b[i];
	}
	int tot=0;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			a[++tot].u=i;
			a[tot].v=j;
			a[tot].w=(aa[i]-aa[j])*(aa[i]-aa[j])+(b[i]-b[j])*(b[i]-b[j]);
		}
	}
	int ans=1e18;
	sort(a+1,a+tot+1,cmp);
	for(int sta=0;sta<(1<<q);++sta){
		sum=0;
		num=0;
		for(int i=0;i<=n;++i) F[i]=i;
		for(int i=1;i<=q;++i){
			if((sta>>(i-1))&1){
				sum+=c[i];
				for(int j=1;j<=s[i];++j){
					add(u[i][j],u[i][1],0);
				}
			}
			
		}
		for(int i=1;num<n-1;++i){
			add(a[i].u,a[i].v,a[i].w);
		}
		ans=min(ans,sum);
	}cout<<ans<<endl;
	return ;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		work();
		if(T) cout<<endl;
	}
    return 0;
}
```

---

## 作者：Xiao_Mi (赞：2)

##### 题目大意：平面上有n个点，你的任务是让所有n个点连通，为此，你可以新建一些边，费用等于两个端点的欧几里得距离的平方。另外还有q个套餐，可以购买，如果你购买了第i个套餐，该套餐中的所有结点将变得相互连通，第i个套餐的花费为ci。求最小花费。1 <= n <= 1000; 0 <= q <= 8。
#### 思路：我们发现q非常小，可以去枚举第q个套餐选或不选，然后将q的花费加入ans，并将套餐内的节点并查集一下，如果已经形成最小生成树就退出，没形成的话就跑剩下的边，直到形成最小生成树。
#### 代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
const int Maxn=4000;
const int Maxq=40;
long long las,ans;
int T,lik[Maxq][Maxn],cnt,ls;
int n,q,cost[Maxq],nn,chang[Maxq];
int x[Maxn],y[Maxn],f[Maxn];
struct edge{
	int x,y,w;
}e[Maxn*Maxn];//!!!
int getf(int x){
	return f[x]==x?x:f[x]=getf(f[x]);
}
int cmp(edge a,edge b){
	return a.w<b.w;
}
int main(){
	scanf("%d",&T);
	while(T--){
		las=0x3f3f3f3f;ls=0;//记得初始化
		scanf("%d%d",&n,&q);
		for(int i=1;i<=q;++i){
			scanf("%d%d",&chang[i],&cost[i]);
			for(int j=1;j<=chang[i];++j){
				scanf("%d",&lik[i][j]);
			}
		}
		for(int i=1;i<=n;++i){
			scanf("%d%d",&x[i],&y[i]);
		}
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j){
				int cos=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
				e[++ls].x=i;e[ls].y=j;e[ls].w=cos;
			}
		}
		sort(e+1,e+ls+1,cmp);
		for(int sit=0;sit<=(1<<q)-1;++sit){//枚举第q个套餐选不选
			for(int i=1;i<=n;++i) f[i]=i;
			cnt=0;ans=0;
			for(int i=1;i<=q;++i){
				if(sit&(1<<(i-1))){
					ans+=cost[i];
					for(int j=1;j<=chang[i];++j){//选得话将套餐内节点并在一起
						int fx=getf(lik[i][j]),fy=getf(lik[i][1]);
						if(fx==fy) continue;
						f[fx]=fy;++cnt;
					}
				}
			}
			for(int i=1;cnt<n-1;++i){//如果没形成最小生成树的话继续跑剩下的边
				int fx=getf(e[i].x),fy=getf(e[i].y);
				if(fx==fy) continue;
				ans+=e[i].w;f[fx]=fy;
				++cnt;
			}
			las=min(las,ans);//取个min
		}
		printf("%lld\n",las);//!!!
		if(T) puts("");
	}
	return 0;
}
```
#### 总结：思路很巧妙，代码也不好写，细节比较多。最后注意还UVA的**输出格式！！！

---

## 作者：Ricardo__mlu (赞：2)

```cpp
我们首先有个朴素的想法，每次在跑最小生成树的时候枚举套餐，但m²*nlogn的复杂段显然接受不了，所以考虑先跑最小生成树来选出每条边的最优情况，再枚举套餐，这样就把复杂度降到m²+nlogn。
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct node
{
	int u,v,w;//u,v,w分别记录每条路的信息。
	bool operator < (node b) const//重载运算符，学一哈；
	{
		return w<b.w;
	}
 }p[1000010];
 int n,m;
 int shu[1010];//记录最小生成树的枝的标号，方便等会更新套餐时判断。
 int f[1010];//并查集。
 int x[1010],y[1010];//记录坐标。
 int k[9][1010];//存套餐。
 int val[9];//存套餐价格。
 int num;
 int sum;
inline void init()
 {
 	for(int i=1;i<=n;i++) f[i]=i;
 	return;
 }
 inline int getf(int v)
 {
 	return f[v]==v? v: f[v]=getf(f[v]);
 }
 inline void move(int v,int u)
 {
 	int ans1=getf(f[v]),ans2=getf(f[u]);
 	if(ans1!=ans2)	f[ans2]=f[ans1];
	 
	 return;
 }
 inline int two(int u)
 {
 	init();
 	int now=0;
 	for(int i=1;i<=m;i++)
 	if(u&(1<<(i-1)))
 	{
 		now+=val[i];
 		for(int j=1;j<k[i][0];j++) move(k[i][j],k[i][j+1]);
		 
	 }
	 for(int i=1;i<=num;i++)
	 {
	 	int ans1=getf(f[p[shu[i]].u]),ans2=getf(f[p[shu[i]].v]);
	 	if(ans1!=ans2)
	 	{
	 		now+=p[shu[i]].w;move(p[shu[i]].u,p[shu[i]].v);
		 }
		 
	 }
	 return now;
 }
 inline int read()
{
	int a=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	
	while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
	
	return a;
}
 int main()
 {
 	int T;
 	T=read();
 	while(T--)
 	{
 		int ans=1;
 		num=0;
 		sum=0;
 		n=read(),m=read();
 		for(int i=1;i<=m;i++)
 		{
 			k[i][0]=read(),val[i]=read();
 			for(int j=1;j<=k[i][0];j++) k[i][j]=read();
			 
		 }
		 for(int i=1;i<=n;i++)
		 {
		 	x[i]=read(),y[i]=read();
		 	f[i]=i;
		 	for(int j=1;j<i;j++)
		 		p[ans].u=i,p[ans].v=j,p[ans].w=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]),ans++;
			 
		 }
		 sort(p+1,p+ans);
		 for(int i=1;i<ans;i++)
		 {
		 	int ans1=getf(f[p[i].u]),ans2=getf(p[i].v);
		 	if(ans1==ans2)continue;
		 	else
		 	{
		 		num++;
		 		shu[num]=i;
		 		sum+=p[i].w;
		 		move(p[i].u,p[i].v);
			 }
			 if(num==n-1)break;
		 }
		 for(int i=1;i<(1<<m);i++)sum=min(sum,two(i));
		 printf("%d\n",sum);
		if(T) printf("\n");
	}
	return 0;
} 
```

---

## 作者：Luxingguang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA1151)

## 一、思路分析
------------

### $O(2^q\times N^2)$ 做法

枚举所有可能的购买方案，对于每种方案，将所有已购子网中各城市之间的费用修改为0，然后求最小生成树，所有方案中最小生成树代价最低的即是答案。共有 $2^q$ 种购买方案，每种求解最小生成树时间复杂度为 $O(N^2)$。所以时间复杂度为 $O(2^q\times N^2)$。

### 正解
当购买某些子网后，重新求解最小生成树，新生成的最小生成树的边集合中不可能包含 $E$ 和 $E'$ 以外的边。所以枚举所有可能的购买方案，用 Kruskal 所法求解即可。

## 二、代码实现
------------

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int N=1005,Q=10;
int p[N];
int find(int x){
	if(x!=p[x]) p[x]=find(p[x]);
	return p[x];
}
struct z{
	int u,v,w;
	bool operator < (const z&rhs)const{
		return w<rhs.w;
	}
}edge;
int n,m,x[N],y[N],weight,ans,q,pr[Q],t;
vector<int> c[Q];
vector<z> e,mst;
int kruskal(int org){
	weight=0;
	sort(e.begin(),e.end());
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=0;i<e.size();i++){
		int x=find(e[i].u),y=find(e[i].v);
		if(x!=y){
			p[y]=x;
			weight+=e[i].w;
			if(org) mst.push_back(e[i]);
		}
	}
	return weight;
}inline int dist(int i,int j){
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		e.clear();mst.clear();
		for(int i=1;i<Q;i++) c[i].clear();
		scanf("%lld%lld",&n,&q);
		int cnt,city;
		for(int i=1;i<=q;i++){
			scanf("%lld%lld",&cnt,&pr[i]);
			for(int j=1;j<=cnt;j++){
				scanf("%lld",&city);
				c[i].push_back(city);
			}
		}for(int i=1;i<=n;i++) scanf("%lld%lld",&x[i],&y[i]);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				e.push_back((z){i,j,dist(i,j)});
			}
		}
		int ans=kruskal(1);
		int ways=1<<q;
		for(int i=1;i<ways;i++){
			e.assign(mst.begin(),mst.end());
			int price=0;
			for(int j=1;j<=q;j++){
				if(i&(1<<(j-1))){
					price+=pr[j];
					for(int k=1;k<c[j].size();k++){
						e.push_back((z){c[j][k-1],c[j][k],0});
					}
				}
			}price+=kruskal(0);
			ans=min(ans,price);
		}if(t!=0) printf("%lld\n\n",ans);
		else printf("%lld\n",ans);
	}
	return 0;
}


```


---

## 作者：lytqwq (赞：1)

~~膨胀到做紫题~~

这题真的有这么难吗？？？

思路：枚举每一个优惠方案，然后求一下最小生成树就行了

代码如下（解释在注释上）：

```cpp
/*
函数有点多，建议从main开始看 
*/

#include<bits/stdc++.h>
using namespace std;

int father[1001],t,n,q,flag1[10];//t,n,q如题目所示，flag1数组存各个优惠方案的状态 
int cost,ans=23333333;//cost为优惠方案所用的钱，ans为最终答案 

struct dl{
	int x,y,co;
	bool operator < (const dl x) const
	{
		return co<x.co;//便于sort 
	}
}b[1000001];//存边 

struct pr{
	int x,y;
}c[1001];//存点 

struct d{
	int x[1001];
	int co,m;
}a[10];//存优惠方案 

double dis(int x,int y)
{
	/*
	我在这个求两点之间距离的地方卡了好久，详细见题中“连接两个不相通的城市，必须建立一个边，其建设成本是城市之间欧几里德距离的平方。” 
	*/
	return (c[x].x-c[y].x)*(c[x].x-c[y].x)+(c[x].y-c[y].y)*(c[x].y-c[y].y);
}
int find(int x)
{
	if(father[x]!=x)
	{
		father[x]=find(father[x]);//路径压缩 
	}
	return father[x];
}
void join(int x,int y)
{
	int fx=find(x),fy=find(y);
	father[fx]=fy;
}
/*
前面两个并查集函数。 
*/
void wyh()//Kruskal算法， 
{
	int ans1=cost;//先算上优惠方案所需的钱 
	for(int i=1,o=0;i<=n*n&&o<n-1;i++)
	{
		int x=b[i].x,y=b[i].y;
		double co=b[i].co;
		if(find(x)!=find(y))
		{
			join(x,y);
			o++;
			ans1+=co;
		}
	}//Kruskal算法，
	
	ans=min(ans,ans1);//算入最小值 
	return ;//结束 
}
void dfs(int x)
{
	if(x==q+1)
	{
		for(int i=1;i<=n;i++)
		{
			father[i]=i;//初始化father[]; 
		}
		for(int i=1;i<=q;i++)
		{
			if(flag1[i]==1)
			{
				for(int o=2;o<=a[i].m;o++)
				{
					join(a[i].x[o],a[i].x[1]);//把加入的优惠方案join 
				}
			}
		}
		wyh();//解决问题（求最小生成树）（函数名是我们机房AK省选的dalao! tql!!!） 
		return ;
	}
	/*
	前面是全枚举完后的解决 
	*/
	dfs(x+1);//不加第x个优惠方案 
	
	cost+=a[x].co;
	flag1[x]=1;
	dfs(x+1);//加第x个优惠方案 
	flag1[x]=0;
	cost-=a[x].co;//回溯 
}
int main()
{
	cin>>t;//多组数据 
	while(t--)
	{
		ans=23333333;//初始化答案为一个很大的数 
		cin>>n>>q;//输入 
		for(int i=1;i<=q;i++)
		{
			flag1[i]=0;
			cin>>a[i].m>>a[i].co;
			for(int o=1;o<=a[i].m;o++)
			{
				cin>>a[i].x[o];//存入优惠方案 
			}
		}
		
		for(int i=1;i<=n;i++)
		{
			cin>>c[i].x>>c[i].y;//输入点 
		}
		
		for(int i=1;i<=n;i++)
		{
			for(int o=1;o<=n;o++)
			{
				b[(i-1)*n+o].x=i;
				b[(i-1)*n+o].y=o;
				b[(i-1)*n+o].co=dis(i,o);//加入边 ，dis为求两点之间的距离 
			}
		}
		
		sort(b+1,b+n*n+1);//排序 
		dfs(1);//dfs枚举优惠方案 
		cout<<ans<<endl;//输出答案 
		if(t!=0)
		{
			cout<<endl;//uva输出机制什么玩意 。。 
		}
	}
}
/*
1

7 3
2 4 1 2
3 3 3 6 7
3 9 2 4 5
0 2
4 0
2 0
4 2
1 3
0 5
4 4

*/
/*
17

*/
```


---

## 作者：Chtholly_Tree (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1151)

## Part 1 思路

如果选择购买子网 $q_i$，那么子网 $q_i$ 所包含的所有城市之间的建设费用都为 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ygw8igge.png)

枚举所有可能的购买方案，对于每种方案，将所有已购子网中各城市之间的费用修改为 $0$，然后求最小生成树，所有方案中最小生成树代价最低的即是答案。

共有 $2^q$ 种购买方案，每种求解最小生成树时间复杂度：$O(n^2)$（本题边数量为 $n^2$，普通 Prim 性能最优），总时间复杂度 $O(2^q \times n^2)$。

下图是不购买任何子网，全自建时的最小生成树，设这种情况下的最小生成树的边集合为 $E$，如果选择购买某些子网，设所购子网内的边集合为 $E'$。

![](https://cdn.luogu.com.cn/upload/image_hosting/1j2gs59e.png)

Q：当购买某些子网后，重新求解最小生成树，新生成的最小生成树的边集合中有没有可能包含 $E$ 和 $E'$ 以外的边？

A：不可能，如果包含 $E$ 和 $E'$ 以外的边，只可能增加最小生成树代价。

枚举所有可能的购买方案，使用 Kruskal 算法在边集合 $E \cup E'$ 中求解最小生成树。

## Part 2 代码

```cpp
#include <bits/stdc++.h>
#define int long long
//#pragma GCC optimize(3, 2, "Ofast")

using namespace std;

const int N = 1005;

int p[N];

int find(int x) {
	if (x != p[x]) p[x] = find(p[x]);
	return p[x];
}

struct node {
	int u, v, w;
	bool operator < (const node &rhs) const {
		return w < rhs.w;
	}
};

int T, n, q, ans, pr[10], x[N], y[N], vis[10];
vector < int > c[10];
vector < node > e, mst;

int dis(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int Kruskal(int org) {
	int len = 0;
	for (int i = 1; i <= n; i++) p[i] = i;
	sort(e.begin(), e.end());
	for (int i = 0; i < e.size(); i++) {
		int x = find(e[i].u), y = find(e[i].v);
		if (x != y) {
			p[y] = x;
			len += e[i].w;
			if (org) mst.push_back(e[i]);
		}
	}
	return len;
}

void dfs(int cur) {
	if (cur > q) {
		int price = 0;
		e.clear();
		for (node tmp : mst) e.push_back(tmp);
		for (int i = 1; i <= q; i++) {
			if (vis[i]) {
				price += pr[i];
				for (int j = 0; j < c[i].size() - 1; j++) {
					e.push_back({c[i][j], c[i][j + 1], 0});
				}
			}
		}
		price += Kruskal(0);
		ans = min(ans, price);
		return;
	}
	vis[cur] = 0;
	dfs(cur + 1);
	vis[cur] = 1;
	dfs(cur + 1);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	for (int kkk = 1; kkk <= T; kkk++) {
		e.clear(); mst.clear();
		cin >> n >> q;
		for (int i = 1; i <= q; i++) {
			c[i].clear();
		}
		for (int i = 1; i <= q; i++) {
			int cnt; cin >> cnt >> pr[i];
			for (int j = 1; j <= cnt; j++) {
				int city; cin >> city;
				c[i].push_back(city);
			}
		}
		for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				e.push_back({i, j, dis(i, j)});
			}
		}
		ans = Kruskal(1);
		dfs(1);
		cout << ans << endl;
		if (kkk != T) cout << endl;
	}

	return 0;
}
```

---

## 作者：syLph (赞：0)

#### 一道诡异的 MST。

首先我们求出平面欧几里得最小生成树。
Kruskal 即可。

然后我们发现有用的边只有原图上构成 MST 的边。于是边数从 $m$ 立刻变成 $n-1$。

然后类似于状态压缩的思想，二进制位枚举每个套餐是否被使用，并把合并每个套餐内的所有点，跑 $2^q$ 次 Kruskal 即可。

时间复杂度 O($2^{q} n\log{n}$)。

Code:

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<memory.h>
using namespace std;
const int maxn = 2000010;
inline int read(){
    int x = 0,f = 1; char c = getchar();
    while('0' > c || c > '9') {if(c == '-')f = -1; c = getchar();}
    while('0' <= c && c <= '9') x = x * 10 + c - '0',c = getchar();
    return x * f;
}
typedef struct{int x,y;} pos;
typedef struct{int u,v,w;} edg;
vector<int> t[10];
int n,m,q,k,siz,sizz,fa[1010],cost[10];
edg a[maxn],b[maxn]; pos pl[1010];
bool operator <(edg a,edg b){return a.w < b.w;}
int find(int x){
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
int cal(int x,int y){
    pos a = pl[x],b = pl[y];
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
 main(){
    //freopen("testdata.in","r",stdin);
    k = read();
    for(int kase = 1 ; kase <= k ; kase ++){
        siz = 0,sizz = 0;
        n = read(),q = read();
        for(int i = 0 ; i <= 8 ; i ++) t[i].clear();
        for(int i = 1 ; i <= n ; i ++) fa[i] = i;
        for(int j = 1 ; j <= q ; j ++){
            int u = read(); cost[j] = read();
            for(int i = 1 ; i <= u ; i ++) t[j].push_back(read());
        }
        for(int i = 1 ; i <= n ; i ++) pl[i].x = read(),pl[i].y = read();
        for(int x = 1 ; x <= n ; x ++)
            for(int y = x + 1 ; y <= n ; y ++)
                a[++siz] = {x,y,cal(x,y)};
        sort(a + 1,a + siz + 1);
        for(int i = 1 ; i <= siz ; i ++){
            int u = a[i].u,v = a[i].v,w = a[i].w,x = u,y = v;
            if(find(u) == find(v)) continue;
            u = find(u),v = find(v);
            fa[u] = v;
            b[++sizz] = {x,y,w};
        }
        int ans = 0x3f3f3f3f;
        for(int p = 0 ; p < 2 << q ; p ++){
            int res = 0;
            for(int j = 1 ; j <= n ; j ++) fa[j] = j;
            for(int j = 1 ; j <= q ; j ++){
                if(p & (1 << (j - 1))){
                    for(int i = 0 ; i < t[j].size() - 1 ; i ++){
                        int u = t[j][i],v = t[j][i+1];
                        u = find(u),v = find(v);
                        fa[u] = v;
                    }
                    res += cost[j];
                }
            }
            for(int j = 1 ; j <= sizz ; j ++){
                int u = b[j].u,v = b[j].v,w = b[j].w;
                if(find(u) == find(v)) continue;
                u = find(u),v = find(v);
                fa[u] = v;
                res += w;
            }
            ans = min(ans,res);
        }
        if(kase != k)printf("%d\n\n",ans);
        else printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：AlexandreLea (赞：0)

## 题意简述

给出平面上的 $n(1\le n\le10^3)$ 点，以及 $q(1\le q\le 8)$ 个套餐，其连通 $c_q$ 个点且费用为 $w_q$，而普通的连接任意两点的距离是其直线距离的平方。现在想要连通所有点，求最小的花费。

## 题目思路

由于 $q\le 8$，所以果断状压。先预处理出边的长度。首先，将选取的所有套餐连接起来，并统计花费；随后，用 Kruskal 算法将剩下的边进行连接。时间复杂度为 $\mathcal O(n^2+\log n+2^qn^2)$（天知道我是如何过的）。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,s[10][1010],w[10],x[1010],y[1010],fa[1010],ans=0x3f3f3f3f;
vector<pair<pair<int,int>,int>> gr;
int find(int u){
    return fa[u]=(fa[u]==u?u:find(fa[u]));
}
bool merge(int a,int b){
    a=find(a),b=find(b);
    if(a==b) return 0;
    return (fa[b]=a),1;
}
void solve(){
    gr.clear();
    ans=0x3f3f3f3f;
    cin>>n>>q;
    for(int i=1;i<=q;++i){
        cin>>s[i][0]>>w[i];
        for(int j=1;j<=s[i][0];++j) cin>>s[i][j];
    }
    for(int i=1;i<=n;++i) cin>>x[i]>>y[i];
    for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j){
        int w=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
        gr.push_back(make_pair(make_pair(i,j),w));
    }
    sort(gr.begin(),gr.end(),[](pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)->bool{return a.second<b.second;});
    for(int stat=0;stat<(1<<q);++stat){
        int res=0,du=0;
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int i=1;i<=q;++i){
            if(stat&(1<<(i-1))){
                for(int j=2;j<=s[i][0];++j) merge(s[i][j-1],s[i][j]);
                res+=w[i];
            }
        }
        if(res>ans) continue;
        for(int i=1;i<=n;++i) if(fa[i]==i) ++du;
        for(auto ie:gr){
            if(du==1) break;
            if(merge(ie.first.first,ie.first.second)){
                res+=ie.second;
                --du;
            }
        }
        if(du==1) ans=min(ans,res);
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    int _,h=0;
    cin>>_;
    while(_--){
        if(h!=0) cout<<endl;
        solve();
        h=1;
    }
    return 0;
}
```

**EOF**

---

## 作者：Cure_Wing (赞：0)

[UVA1151 买还是建 Buy or Build](https://www.luogu.com.cn/problem/UVA1151)

### 思路

说到底这道题难度绝对没有紫。

注意到 $q\le8$，我们考虑直接枚举购买哪些子网。在选择完之后，由于 $n\le1000$，所以两点连边不超过 $10^6$ 条。所以我们直接暴力建出每一条边，按照 Kruscal 的思想，每次选长度最小的边，判断连接的两点是否连通。如果不连通则加入答案。

时间复杂度 $O(\sum2^q(q+\sum m_i+n^2\log n^2))$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int Q=9,N=1003,inf=1e9;
int t,n,q,m[Q],w[Q],a[Q][N],x[N],y[N],fa[N],ans,c;
struct A{int u,v,w;}b[N*N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<(t?"\n\n":"\n")){
		cin>>n>>q;ans=inf;c=0;
		for(int i=1;i<=q;++i){
			cin>>m[i]>>w[i];
			for(int j=1;j<=m[i];++j) cin>>a[i][j];
		}
		for(int i=1;i<=n;++i) cin>>x[i]>>y[i];
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				b[++c]=A{i,j,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])};//暴力建边
		std::sort(b+1,b+c+1,[](A a,A b){return a.w<b.w;});
		for(int i=0;i<(1<<q);++i){//枚举选择
			for(int j=1;j<=n;++j) fa[j]=j;
			int sum=0,cnt=0;
			for(int j=1;j<=q;++j){
				if((i>>(j-1))&1){
					sum+=w[j];
					for(int k=1;k<m[j];++k){
						int fu=find(a[j][k]),fv=find(a[j][k+1]);
						if(fu!=fv) fa[fv]=fu;
					}
				}
			}
			for(int j=1;j<=c;++j){
				int fu=find(b[j].u),fv=find(b[j].v);
				if(fu!=fv){fa[fv]=fu;sum+=b[j].w;}
			}
			ans=std::min(ans,sum);//取最小值
		}
	}
	return 0;
}
```

---

