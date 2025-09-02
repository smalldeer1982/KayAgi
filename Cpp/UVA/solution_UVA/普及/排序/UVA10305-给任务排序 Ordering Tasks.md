# 给任务排序 Ordering Tasks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1246

[PDF](https://uva.onlinejudge.org/external/103/p10305.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10305/62db82e05a53c8fcb4628f932e511aa228649ae7.png)

## 样例 #1

### 输入

```
5 4
1 2
2 3
1 3
1 5
0 0```

### 输出

```
1 4 2 5 3```

# 题解

## 作者：james1BadCreeper (赞：32)

为防止后人像我一样学拓扑排序用三个小时，本篇题解就此诞生。

前置芝士
- 图的定义及相关
- 存图
- 搜索

---

$\large\text{1.什么是拓扑排序}$

严格意义上来说，拓扑排序**不是**一种排序。是对有向无环图（$DAG$）$\text{G}$，将$\text{G}$中所有顶点排成一个线性序列，使得图中任意一对顶点$u$和$v$，若它们之间存在一条有向边,则$u$在线性序列中出现在$v$之前。

这么干说我可没懂，来上张图看看。

![](https://i.loli.net/2020/01/25/ASlxpdUyn5Kmcqj.png)

这是一只```james1```手绘的奇丑无比的图，可以发现它是一个$DAG$,现在我们要求它的拓扑序。

按照刚才的定义，首先按直觉我们要找终点是该点的边条数（即入度）为零的点（说白了就是遍历图时的起点）。

等等，这个图中有两个啊？

往往一个$DAG$的拓扑序不止一个，所以这里构造出的序列开头是$1$或$4$都可以成立。然后我们把$1$和$4$枪毙，就像这样：

![](https://i.loli.net/2020/01/25/pYZE5KPyJWX2Njz.png)

点和连着的边都要被干掉，目前的拓扑序是```1 4```。

不断地执行上述操作，我们可以把整张图都枪毙掉，可以得到拓扑序，这张图可能的一个拓扑序是```1 4 2 3 5 6 7 8```。

可以证明，若一个图不是$DAG$，则它不存在拓扑序。

---

$\large\text{2.实现拓扑排序}$

仿照刚才的思想，可以得到如下程序大框：

```cpp
while(图里还有入度为0的节点吗?)
{
    输出那个节点;
    干掉那个节点;
}
```

可以借助$bfs$来完成这个过程，返回值为是否存在拓扑排序，拓扑序存在$ans$当中。

```cpp
//采用vector存图(G是图)
inline int topo(void)
{
	queue<int>q;//入度为0节点的队列
	int ans[MAXN],tot=0;
   	//in数组为每个节点的入度
	for(register int i=1;i<=n;i++)
		if(in[i]==0) q.push(i);
	while(!q.empty())
	{
		register int t=q.front();
		q.pop();
		ans[++tot]=t;//记录答案
        //干掉它
		for(register int i=0;i<G[t].size();i++)
		{
			in[G[t][i]]--;
			if(in[G[t][i]]==0) q.push(G[t][i]);
		}
	}
	return tot==n;
}
```

有的题要求输出的拓扑序字典序最小最大什么的，用```priority_queue< int , vector <int> , greater <int> >```或```priority_queue<int>```这种优先队列代替普通队列```queue<int>```即可。

用$dfs$也可以完成拓扑排序，细节留给大家思考。

$\large\text{3.本题题解}$

把每个任务看做一个节点，一条任务之间的关系看做一条有向边，即可发现这就是个拓扑排序的模板。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

namespace The_Future_Diary
{
	using namespace std;
	int __int;
	long long __LL;

	template<typename T>
	inline T read(T p)
	{
		register T x=0;
		register int c=getchar()/*,f=0*/;
		while(!isdigit(c)) c=getchar();/*{if(c=='-')f=1;c=getchar();}*/
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		//return f?-x:x;
		return x;
	}

	int buf[30];
	template<typename T>
	inline void print(T x,char k)
	{
		//if(x<0) putchar('-'),x=-x;
		register int tot=0;
		if(x==0) buf[++tot]=0;
		while(x)
		{
			buf[++tot]=x%10;
			x/=10;
		}
		for(register int i=tot;i>=1;i--)
			putchar(buf[i]+'0');
		putchar(k);
	}
}

using namespace The_Future_Diary;

int n,m,x,y;
int in[105];
pair<int,int>a[10005];
vector<int>G[105];

inline void topo(void)
{
	queue<int>q;
	for(register int i=1;i<=n;i++)
		if(in[i]==0) q.push(i);
	while(!q.empty())
	{
		register int t=q.front();
		q.pop();
		print(t,' ');
		for(register int i=0;i<G[t].size();i++)
		{
			in[G[t][i]]--;
			if(in[G[t][i]]==0) q.push(G[t][i]);
		}
	}
	putchar('\n');
}

int main(void)
{
	while(scanf("%d%d",&n,&m)==2&&n)//这里有坑，千万不要再在「n」后面写上「&&m」
	{
		memset(in,0,sizeof(in));
		memset(a,0,sizeof(a));
		for(register int i=1;i<=n;i++)
			G[i].clear();
     	//并没有保证关系不重复
		for(register int i=1;i<=m;i++)
		{
			x=read(__int),y=read(__int);
			a[i]=make_pair(x,y);
		}
		sort(a+1,a+m+1);
		register int c=unique(a+1,a+m+1)-a;
		for(register int i=1;i<=c;i++)
		{
			G[a[i].first].push_back(a[i].second);
			in[a[i].second]++;
		}
		topo();
	}
	return 0;
}
```

---

## 作者：Snowlanuck (赞：21)

该题主要是考遍历拓扑基础,在题解中有很通俗易懂图文并茂的题解了,所以我只说一下大概的思路

主要是寻找入度数为0的节点(既没人被其他节点指向的节点),去除该节点后,重新计算与该节点相关的节点的入度数,如果为0则继续去除

不过题解里面的代码都比较长,不利于新手学习,下面放出一个简短且易懂的代码

参考代码(bfs遍历):

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;//节点数 边数
	vector<vector<int>> G; //图
	vector<int> in;//入度数

	while (cin >> n >> m)
	{
		if (n == 0 && m == 0) { break; }
		G = vector<vector<int>>(n + 1); //有n个点
		in = vector<int>(n + 1);
		for (int i = 1, a, b; i <= m; i++)
		{
			cin >> a >> b; //生动形象 a>>b a指向b
			G[a].push_back(b); //添加该点指向了什么点
			in[b]++; //该点入度数+1
		}
		queue<int> q; int t;
		for (int i = 1; i <= n; i++)
			if (in[i] == 0) { q.push(i); } //如果入度数为0则添加
		while (!q.empty()) //bfs遍历
		{
			t = q.front(); q.pop();
			cout << t << ' ';
			for (size_t i = 0; i < G[t].size(); i++) //寻找除去该点后还有那些入度数为0的点
			{
				in[G[t][i]]--;
				if (in[G[t][i]] == 0) q.push(G[t][i]);
			}
		}
		cout << endl;
	}

	return 0;
}
```

更新,补上dfs的遍历(参考紫书+题解

递归访问节点指向的节点,直到访问完毕,将其记录到结果中,如果访问过程判定为有向环则终止

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m, t;
vector<vector<int>> G;//图
vector<int> book, topo;//标记,结果

bool dfs(int u)
{
	book[u] = -1; //-1标记为该节点正在访问中
	for (int i = 0; i < (int)G[u].size(); i++) //访问该节点指向了什么节点
	{
		if (book[G[u][i]] == -1) { return false; } //如果该节点中有节点也在访问中 说明是有向环
		//else if (book[G[u][i]] == 0 && !dfs(G[u][i])) { return false; } //原紫书代码 不好理解 换成下面的
		else if (book[G[u][i]] == 0) { dfs(G[u][i]); } //如果该节点指向的节点没被访问过 则对其进行递归访问
	}
	book[u] = 1; topo[--t] = u; //标记该节点访问完毕 并记录到结果中
	return true;
}

bool toposort()
{
	t = n;
	book = vector<int>(n + 1); topo = vector<int>(n + 1);
	for (int i = 1; i <= n; i++)
		if (book[i] == 0) { if (!dfs(i)) { return false; } }
	return true;
}

int main()
{
	while (cin >> n >> m)
	{
		if (n == 0 && m == 0) { break; }
		G = vector<vector<int>>(n + 1);
		for (int i = 0, a, b; i < m; i++)
		{
			cin >> a >> b;
			G[a].push_back(b);
		}
		if (!toposort()) { cout << "-1"; }
		else for (int i = 0; i < n; i++)
			cout << topo[i] << " ";
		cout << endl;
	}

	return 0;
}
```



---

## 作者：塔罗兰 (赞：8)

首先这个题目是在外OJ评测的，使用万能头莫名CE

2019.7.31：经过提醒发现是map和万能头中的容器冲突勒，现已改，阔以用万能头啦

拓扑排序的题目，只需输出一种解好评
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAX 505
using namespace std;
int n,m,v[MAX],a[MAX];
int mapp[MAX][MAX];
inline void lzy()
{
	queue<int> q;
	int l(0);
	while(!q.empty())
	q.pop();//清空上次的队列
	for(int i=1;i<=n;i++)
	if(!v[i])
	q.push(i);//初始0入度值的入队
	int sum(q.front());
	while(!q.empty())
	{
		a[l++]=sum;
		q.pop();//记录并删除
		for(int i=1;i<=n;i++)
		if(mapp[sum][i])
		{
			v[i]--;
			if(!v[i])
			q.push(i);//当前0入度值的入队
		}
		sum=q.front();//将sum的值换成当前队列首的值
	}
	for(int i=0;i<n;i++)
	printf("%d ",a[i]);
	printf("\n");//输出
}
int main()
{
	while(scanf("%d%d",&n,&m)==2&&n!=0)//终止条件
	{
		memset(mapp,0,sizeof(mapp));
		memset(v,0,sizeof(v));//清除上次数据
		for(int i=0;i<m;i++)
		{
			int e,r;
			scanf("%d%d",&e,&r);
			if(!mapp[e][r])
			{
				mapp[e][r]=1;
				v[r]++;//记录入度值
			}
		}
		lzy();
	}
}
```
仅以此题解庆祝进军提高组算法

---

## 作者：rihothy (赞：3)

题目说了，任意输出一个就行，而且数据不大，就100个，直接暴力O(n^3)模拟。
当然了，拓扑排序还是要学的，不能偷懒。
```cpp
#include <iostream>
int n, m, x, y;
int main(void){
	while (std::cin >> n >> m && n){
		bool book[101] = { false }, relevant[101][101] = { false };
		while (m--){
			std::cin >> x >> y;
			relevant[x][y] = true;
		}
		for (int i = 0; i < n; ++i)
			for (int i = 1; i <= n; ++i)
				if (!book[i]){
					for (int j = 1; j <= n; ++j)
						if (relevant[j][i] && !book[j])
							goto out;
					book[i] = true;
					std::cout << i << " ";
					break;
				out:
					continue;
				}
		std::cout << std::endl;
	}
}
```


---

## 作者：zeeeeeeekx (赞：1)

发布一个邻接链表的题解好了

拓扑排序的题目，只需输出一种解好评orz
```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int op=505;
int ind[op],n,m,en=0;
int ans[op],head[op];
struct edge{
	int to,next,w;
}ex[op<<1];
queue<int> q;
inline void add(int x,int y){
	ind[y]++;
	ex[en].to=y;
	ex[en].next=head[x];
	head[x]=en++;
}
//int q[op],qhead=0,qtail=0;

inline void topo(){
	for(int i=1;i<=n;i++){
		if(!ind[i]) q.push(i);}
	int u,v;
	while(!q.empty()){
			u=q.front();q.pop(); printf("%d ",u);
			for(int p=head[u];~p;p=ex[p].next){
				v=ex[p].to;--ind[v];
				if(!ind[v]){
					q.push(v);
				}
				
			}
		}
	
}

int main(){
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	topo();
//	for(int i=1;i<=qtail;i++)
//	printf("%d ",q[i]);
	return 0;
}
```


---

## 作者：我只能爬 (赞：1)

其实主要的楼上都说了，我就来补一个队列版本的好了……
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define maxn 105
#define maxm 10005

namespace Lily {
    struct node {
        int to, nxt;
    }edge[maxm];
    int head[maxn], in[maxn], cnt, n, m, tmpa, tmpb;
    std::queue<int> _;
    
    inline int read() {
        int x = 0, f = 1;
        char c = '\0';
        while(c > '9' || c < '0') {
            if(c == '-') f = -1;
            c = getchar();
        }
        while(c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = getchar();
        }
        return x * f;
    }
    
    void topo() {
        for(register int i = 1; i <= n; ++i)
            if(in[i] == 0) _.push(i);
        while(!_.empty()) {
            int p = _.front(); _.pop();
            std::cout << p << " ";
            for(register int i = head[p]; i; i = edge[i].nxt) {
                in[edge[i].to] --;
                if(in[edge[i].to] == 0)
                    _.push(edge[i].to);
            }
        }
    }
    
    void add(int u, int v) {
        edge[++cnt].to = v;
        edge[cnt].nxt = head[u];
        in[v]++;
        head[u] = cnt;
    }
    
    void main() {
        while(1){
            n = read(); m = read();
            if(n == 0 && m == 0) break;
            memset(head, 0, sizeof(head));
            memset(in, 0, sizeof(in));
            cnt = 0;
            for(register int i = 1; i <= m; ++i) {
                tmpa = read(); tmpb = read();
                add(tmpa, tmpb);
            }
            topo();
            std::cout << std::endl;
        }
    }
}

int main() {
    Lily::main();
    return 0;
}

```

---

## 作者：henry_y (赞：0)

题意：输入n和m，以及m个i和j，求1~n的一个排列使得对于每个(i,j)，i在j的前面

注意：会有多组数据，数据以n=0&&m=0结束

我被样例坑了一波..以为只有一组数据（没仔细看题面系列）

这道题其实就是拓扑排序的模板，数据很小，用邻接矩阵就可以了

P.S:题目并没有说明有环的情况怎么输出，应该是保证有解

拓扑排序不懂的同学自行百度啦qwq

```cpp
#include <cstdio>
#include <cstring>
#define ll int
#define inf 1<<30
#define mt(x,y) memset(x,y,sizeof(x))
#define il inline 
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll abs(ll x){return x>0?x:-x;}
il void swap(ll &x,ll &y){ll t=x;x=y;y=t;}
il void read(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
#define N 1100
ll n,m,f[N][N],c[N];
ll top[N],t;
bool dfs(ll u){
	c[u]=-1;
	for(ll v=1;v<=n;v++){
		if(f[u][v]){
			if(c[v]<0)return false;
			else if(!c[v])dfs(v);
		}
	}
	c[u]=1;top[t--]=u;
	return true;
}
bool topsort(){
	t=n;
	memset(c,0,sizeof(c));
	for(ll u=1;u<=n;u++){
		if(!c[u])if(!dfs(u))return false;
	}
	return true;
}
int main(){
	while(scanf("%d%d",&n,&m)==2&&n){
	    memset(f,0,sizeof(f));
	    ll u,v;
	    for(ll i=1;i<=m;i++){
		    read(u);read(v);
		    f[u][v]=1;
	    }
    	if(!topsort())printf("%d",-1);
		//题目并没有说明有环的情况怎么输出，应该是保证有解 
    	else for(ll i=1;i<=n;i++){
    		printf("%d ",top[i]);
    	}
    	printf("\n");
	}
	return 0;
}
```


---

