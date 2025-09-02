# Road Improvement

## 题目描述

给定一棵有 $N$ 个节点的树，你可以使用**两支相邻节点的队伍**来修筑它们之间的道路 且 **每支队伍一天只能工作一次**。问最少需要多少天把所有路修完。输出方最短时间和具体方案。            
$N \le 200000$

## 样例 #1

### 输入

```
4
1 2
3 4
3 2
```

### 输出

```
2
2 2 1
1 3
```

## 样例 #2

### 输入

```
6
3 4
5 4
3 2
1 3
4 6
```

### 输出

```
3
1 1 
2 2 3 
2 4 5 
```

# 题解

## 作者：lizicheng3042 (赞：3)

## 题目思路
首先思考修路最多需要几天。我们发现一个结论：在这棵树上，这个答案应该是这棵树上连边数最多的点的边数（设它为 $i$）。  
证明：因为对于每个点，每天最多修一条连边，所以答案必然是大于等于 $i$ 的。  
我们试图证明上述结论成立。因为一个点最多连了 $i$ 条边，所以与其连边的点有 $i-1$ 天的时间去修建自身的其他边，而这些点所连的边数不会超过 $i$，显然可以建好所有边。据此，不断进行延伸，可知，对于任何一个点，其都可以在 $i$ 天内建好所有边，结论成立。  
然后考虑怎么把每天建的边都写出来。  
显然我们以某个节点为根对整棵树进行遍历，可以用 vector 来存每天建的边。那么对于每个节点，我们首先需要记录与其父节点相连的边的修建天数，当遇到时就将其跳过即可。
## 代码实现
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n,num[300005],ans,ver[300005],now[300005],pl,f[200005],to[400004],nxt[400005],tot,w,e;
vector<int>k[300005];
void add(int x,int y)
{
	nxt[++tot]=f[x];to[f[x]=tot]=y;
	nxt[++tot]=f[y];to[f[y]=tot]=x;
}
void dfs(int u,int fa,int f_b_d/*与父结点相连的边的修建天数*/)
{
	int cou=0;
	for(int a=f[u];a;a=nxt[a])
	{
		if(to[a]==fa)
			continue;
		cou++;
		if(cou==f_b_d)
			cou++;
		k[cou].push_back((a+1)/2);//前向星存边时每条边实际的编号
		dfs(to[a],u,cou);
	}
	ans=max(cou,ans);
}
int main()
{
	scanf("%d",&n);
	for(int a=1;a<n;a++)
	{
		scanf("%d%d",&w,&e);
		num[w]++;num[e]++;
		add(w,e);
	}
	dfs(1,0,0);
	printf("%d",ans);
	for(int a=1;a<=ans;a++)
	{
		printf("\n%d",k[a].size());
		for(int b=0;b<k[a].size();b++)
			printf(" %d",k[a][b]);
	}
	return 0;
}
```


---

## 作者：H6_6Q (赞：3)

[**题目传送门**](https://www.luogu.com.cn/problem/CF638C)    


------------
这是一道**贪心**题。       
- 求出 $k$ 其实很简单，因为每个节点的边每天最多只能修一条，所以答案就是度数最大的节点的度数（也就是边最多的节点的边数）。
- 重点在于怎么求方案。
	1. 因为题目中的树是一颗无根树，所以我们默认 $1$ 号节点为他的根节点。
	1. 接下来我们开 $k$ 个集合，表示第 $i$ 天要修的路的编号（这里可以用 vector 实现）。      
    1. ~~**划重点**~~   然后开始从 $1$ 号节点 dfs ，每走到一个节点，就把 **它与它父亲之间的路** 与 **它与所有儿子间的路** 放在不同的集合中，因为这些边的修筑 **必须都有该节点参与** ，但是由于该节点 **一天只能修一条路** ，所以要放在不同天修。
    1. 就这样遍历完整棵树，然后按要求输出就可以了。      
    
###  Code:     
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
#include<queue>
#include<map>
#include<set>

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const int N=2e5+5;
int n,du[N],head[N],tot,ans;
//du 用来统计节点度数 

vector<int> agg[N];
//用 vector 模拟集合 

struct Edge
{
	int v,ne;
}e[N*2];
//这里要开双倍空间，因为是双向边 

inline void add(int u,int v);
//加边函数 
inline void dfs(int u,int fa,int last);
//dfs 求方案 

int main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		du[u]++,du[v]++;//统计度数 
		add(u,v);
		add(v,u);
		ans=max(ans,max(du[u],du[v]));
		//取度数最大值为答案 
	}
	printf("%d\n",ans);
	//先输出答案 
	dfs(1,-1,0);
	//然后 dfs 求方案 
	for(int i=1;i<=ans;++i)
	{
		printf("%d ",agg[i].size());
		//先输出这一天修的路的数量 
		for(int j=0;j<agg[i].size();++j)
			printf("%d ",agg[i][j]);   //然后输出具体的路的编号 
		printf("\n");
	}
	return 0;
}

inline void add(int u,int v)
{
	e[++tot]=(Edge){v,head[u]};
	head[u]=tot;
}

//u 表示当前节点，fa 表示 u 节点的父亲，last 表示 u 与 fa 间的路所在的集合编号 
inline void dfs(int u,int fa,int last)
{
	int j=1; // j 表示当前枚举到的集合数 
	for(int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if(v==fa) //判断一下，别走回头路 
			continue;
		if(j==last)  //如果当前集合编号是 u 与它父亲间的路所在集合的编号 
			++j;  //那么这个集合不能放这条边，及 ++j; 
		agg[j].push_back((i+1)/2);
		//然后记录答案
		//因为上面存的是双向边，所以不能直接存 i
		//考虑到同一条边在数组中的下表是 x,x+1
		//所以通过 (x+1)/2 可以计算出该边在读入时的编号。 
		dfs(v,u,j);
		//继续递归该节点 
		++j;
		//因为该集合已经放了边，所以 j 要 +1 
	}
	return;
}
```


---

## 作者：luckyqwq (赞：0)

# CF638C Road Improvement 题解

### 大致思路：

首先第一个问，我们可以通过贪心策略解决，显然 $k$ 是所有点中度数最大的点，因为对于每个点，每天最多修一条边，所以答案必然大于等于最大度数。

后面的问，我们可以定一个节点为根，从根开始遍历，用 vector 存每天建的边，还要记录任意一个节点 $u$ 与它父亲节点建边的天数，遇到时需要跳过，随后输出即可。

### 代码实现：

```cpp
#include<bits/stdc++.h>
const int N = 3e5 + 10;
const int MOD = 1e9 + 7;
using namespace std;
struct Stream {
    enum {
        SIZE = 1000001
    };
    char ibuf[SIZE], *s, *t, obuf[SIZE], *oh;
    bool eof;
 
    Stream() : s(), t(), oh(obuf), eof(false) {}
 
    ~Stream() { fwrite(obuf, 1, oh - obuf, stdout); }
 
    explicit operator bool() const {
        return static_cast<bool>(eof == false);
    }
 
    inline char read() {
        if (s == t) t = (s = ibuf) + fread(ibuf, 1, SIZE, stdin);
        return s == t ? -1 : *s++;
    }
 
    inline Stream &operator>>(char *x) {
        static char c;
        for (c = read(); isspace(c); c = read())
            if (c == -1) {
                eof = true;
                return *this;
            }
        for (; !isspace(c); c = read()) *x = c, ++x;
        *x = 0;
        return *this;
    }
 
    template<typename T>
    inline Stream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) {
                eof = true;
                return *this;
            }
            iosig |= c == '-';
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        if (iosig) x = -x;
        return *this;
    }
 
    inline void print(char c) {
        if (oh == obuf + SIZE) {
            fwrite(obuf, 1, SIZE, stdout);
            oh = obuf;
        }
        *oh++ = c;
    }
 
    template<typename T>
    inline void print(T x) {
        static int buf[40], cnt;
        if (x != 0) {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
            while (cnt) print((char) buf[cnt--]);
        } else print('0');
    }
 
    template<typename T>
    inline Stream &operator<<(const T &x) {
        print(x);
        return *this;
    }
 
    inline void print(const char *x) {
        for (; *x; x++)
            print(*x);
    }
} io;
 
#ifndef DEBUG
#define cin io
#define cout io
#define endl '\n'
#endif
vector < pair < int, int > > f[N];
vector < int > g[N];
int n, dep[N], mx;//dep存度数，通过贪心思想发现k其实就是最大度数，用mx存
void dfs(int d, int x, int fa)
{
    int tmp = 1;
    for(int i = 0;i < f[x].size(); ++ i)
    {
        
        int xx = f[x][i].first;
        int yy = f[x][i].second;
        if(xx == fa) continue;
        if(tmp == d) ++ tmp;//若现在天数到了 u 与父亲相连的天数，则没法再与儿子连
        g[tmp].push_back(yy);
        dfs(tmp ++, xx, x);
    }
}
int main()
{
    cin >> n;
    for(int i = 1;i < n; ++ i)
    {
        int x, y;
        cin >> x >> y;
        f[x].push_back(make_pair(y, i));
        f[y].push_back(make_pair(x, i));
        ++ dep[x]; ++ dep[y];
    }
    for(int i = 1;i <= n; ++ i) mx = max(mx, dep[i]);cout << mx << "\n";
    dfs(0, 1, 0);
    for(int i = 1;i <= mx; ++ i)
    {
        cout << g[i].size() << " ";
        for(int j = 0;j < g[i].size(); ++ j)
        {
            cout << g[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

这样这道题就完成啦！！！

---

## 作者：LiJoQiao (赞：0)

[更好的阅读体验](https://www.cnblogs.com/LiJoQiao/p/18022704)  

我们可以针对一个顶点只能同时修一条边这个条件设计方案。  

由于每条边都要修一遍，同样某天修理的方案放在哪一天修都无所谓，我们采用贪心的策略，在原有的方案上尽可能多地修边。  

根据上面的性质，我们只需要将同一顶点的边放在不同的某天修理的方案中，使方案尽可能的少即可。  
跑一遍 dfs，用 `std::vector<int>` 记录修理的方案就行了。  

上述记录方案的过程中对于一个假定的根节点（根节点为 $1$ 会比较好处理）会将边分别放入一个方案中，在向下遍历的过程中的节点都会有连接父节点的边被放入已有的一个方案中，所以会出现节点最大度数个方案，即最短时间为节点的最大度数。  

代码如下。  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef pair<int,int> pii;
constexpr int MAXN=2e5+10;
int n,deg[MAXN],maxdeg,cnt;
vector<pii> e[MAXN];
vector<int> g[MAXN];
void add(int u,int v,int id){
    e[u].pb({v,id});
}
void dfs(int u,int fa,int gr){
    int p=1;
    for(int i=0;i<e[u].size();++i){
        if(e[u][i].first!=fa){
            if(p==gr)++p;
            g[p].pb(e[u][i].second);
            cnt=max(p,cnt);
            ++p;
            dfs(e[u][i].first,u,p-1);
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;++i){
        scanf("%d%d",&u,&v);
        add(u,v,i);add(v,u,i);++deg[u];++deg[v];
    }
    for(int i=1;i<=n;++i)maxdeg=max(deg[i],maxdeg);
    printf("%d\n",maxdeg);
    dfs(1,0,0);
    for(int i=1;i<=cnt;++i){
        printf("%d ",g[i].size());
        for(int j:g[i]){
            printf("%d ",j);
        }
        puts("");
    }
    return 0;
}
```



---

## 作者：封禁用户 (赞：0)

把每一天修建的道路看作一个集合，那么每个节点的邻居的集合应该不同。

那么我们就给每个节点标记顺序好了，构造的顺序从父亲到儿子，儿子之间是可以直接升序标记的，之间跳过父亲与祖父之间边所在的集合即可。

复杂度：$O(n)$。

---

## 作者：Tx_Lcy (赞：0)

简单题，直接大力贪心。
## 思路
我们从点 $\verb!1!$ 开始 $\verb!dfs!$，每次记录上次来的边是在第几次被修理的。假设当前点是点 $\verb!u!$，上次来的边是在第 $\verb!x!$ 次被修理的。显然对于与它连接的点 $\verb!v!$，肯定不能在第 $\verb!x!$ 次被修理。那么问题就十分简单了。我们从第 $\verb!1!$ 次开始枚举，遇到 $\verb!x!$ 就跳掉。最后开一个 $\verb!vector!$ 记录答案即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=2e5+10;
int vis[N],num;
vector<int>a[N],b[N],ans[N];
inline void dfs(int x,int cnt){
	vis[x]=1;int cnti=0,la=cnt;
	if (cnt>1) cnt=0;
	for (rint i=0;i<a[x].size();++i){
		if (vis[a[x][i]]) continue;
		++cnti;
		if (cnt+cnti==la) ++cnti;
		ans[max(1LL,cnt+cnti)].push_back(b[x][i]);
		num=max(num,cnt+cnti);
		dfs(a[x][i],cnt+cnti);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (rint i=1;i<n;++i){
		int u,v;cin>>u>>v;
		a[u].push_back(v),a[v].push_back(u);
		b[u].push_back(i),b[v].push_back(i);
	}
    dfs(1,0);
    cout<<num<<'\n';
    for (rint i=1;i<=num;++i){
    	cout<<ans[i].size()<<' ';
    	for (auto j:ans[i]) cout<<j<<' ';
    	cout<<'\n';
	}
	return 0;
}
```


---

