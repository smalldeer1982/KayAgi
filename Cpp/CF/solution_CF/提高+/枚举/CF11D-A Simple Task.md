# A Simple Task

## 题目描述

Given a simple graph, output the number of simple cycles in it. A simple cycle is a cycle with no repeated vertices or edges.

## 说明/提示

The example graph is a clique and contains four cycles of length 3 and three cycles of length 4.

## 样例 #1

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
7
```

# 题解

## 作者：灯芯糕 (赞：61)

## $solution:$

思路大家应该都懂：

状压DP：$f[i][j]$，其中 $i$ 这一维是需要状压的，用来记录19个节点每一个是否已经走过（走过为 $1$ ,没走为 $0$ ,用 $2$进制 压缩一下即可）。同时，我们认为状压中已经走过的序号最小的节点为出发节点，$j$ 即数组第二维是路径终点。（当这两个数相同时，说明找到了一个环）。

注：这种方法因为无向图的存在，会出现（同一条路径出现两次）（一条边和两个端点构成非法环）的情况，这只需要在输出答案时 $ans=(ans-m)/2$ 即可！
## $code:$

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define inf 0x7fffffff
#define rg register int

using namespace std;

int n,m,t,u,v;
bool a[19][19]; //存边
ll ans,f[600001][19]; //状压

inline int qr(){ //快读
	char ch;
	while((ch=getchar())<'0'||ch>'9');
	int res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		res=res*10+(ch^48);
	return res;
}

int main(){
	//freopen("hamilton.in","r",stdin);
	//freopen("hamilton.out","w",stdout);
	n=qr(),m=qr();t=1<<n;
	for(rg i=1;i<=m;++i){
		u=qr()-1;v=qr()-1;
		a[u][v]=a[v][u]=1;//加边
	}
	for(rg i=0;i<n;++i)
		f[1<<i][i]=1; //初始化（创建以i为起点的路径）
	for(rg i=1;i<=t;++i){
		for(rg j=0;j<n;++j){
			if(!f[i][j])continue; //加速
			for(rg k=0;k<n;++k){
				if(!a[j][k])continue; //加速
				if((i&-i)>1<<k)continue; //起点不能改！！！（去重）
				if(1<<k&i){ //这个点走过
					if(1<<k==(i&-i)) //起点与终点相同
						ans+=f[i][j];
				}else f[i|1<<k][k]+=f[i][j]; //没走过就走！
			}
		}
	}printf("%lld",(ans-m)/2); //处理之后再输出！
	return 0;
}

```

---

## 作者：plafle (赞：34)

# A Simple Task

## 1.题目描述：

​	给定一个包含$n (n \leq 19)$个点的**简单图**，求这个图中包含的 **简单环（重边构成的二元环不算）**的个数。

- 限制： 2$s$ + 256$MB$.

## 2.解法：

​	考虑状压DP.

​	$f[k][i]$表示当前点为$i$，前面经过的点的状态为$k$的简单路径的条数。

​	注意到**环1，2，3**和**环3，1，2**是同一个环。为了防止这种情况的重复计算，我们重新规定，$f[k][i]$表示当前点为$i$，前面经过的点得状态为$k$，**且经过的的第一个点是经过的所有点中编号最小的一个**的简单路径的条数。

​	我们枚举$i$直接相连的点$j$，如果$j$的编号比前面经过的最小的编号还要小，那么这个$j$是非法的，因为在我们的规定中，$j$不是第一个经过的点，那么它的编号就不能是最小的。

​	如果点$j$是一个还没有经过过的点，那么就可以直接状态转移，往前推一步：
$$
f[k | (1 << j)] = f[k|(1 << j)] + f[k][i]
$$
​	如果点$j$是一个已经经过过的点，那么就会有两种情况：

- $j$是状态$k$中第一个经过的点：

  那么这种情况下就构成了一个环，直接将$ans$加上$f[k][i]$.

- $j$不是状态$k$中第一个经过的点：

  这个时候我们什么操作都不做。因为当前环对答案的贡献会在第一种情况中处理，如果我们现在再加，就会出现一个环重复产生贡献的错误。

​    **最后注意**，我们的这种做法会把重边构成的二元环算进去，同时会把二元以上的环的贡献算两次（顺时针一次，逆时针一次），所以最后需要对答案进行处理。



## 3.代码

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const int maxn = 1e2 + 5;
int n,m,x,y;
int first[maxn],last[maxn],dx[maxn << 1],nxt[maxn << 1],xb;
long long f[1 << 20][20],cnt; //注意答案很大，这里要用long long.

void build(int x,int y) {
	dx[++xb] = y;
	if (!first[x])
		first[x] = xb; else
		nxt[last[x]] = xb;
	last[x] = xb;	
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		scanf("%d%d",&x,&y);
		x--;
		y--;
		build(x,y);
		build(y,x);
	}
	for (int i=0; i<n; i++)
		f[1 << i][i] = 1;   //初始化
		
	for (int k=1; k < (1 << n); ++k)
		for (int i=0; i<n; ++i) {
			if (!f[k][i])
				continue;        //如果这种状态不存在，就跳过。
			for (int j=first[i]; j; j = nxt[j]) {
				int y = dx[j];   //枚举与i直接相连的点y
				if ((k & (-k)) > (1 << y))
					continue;   //枚举到的y不合法
				if (k & (1 << y)) {    //如果点y是一个经过过的点
					if ((k & (-k)) == (1 << y))  
						cnt += f[k][i];  //第一种情况，y是第一个经过的点
				} else
					f[k | (1 << y)][y] += f[k][i]; //y没有经过过，直接转移
			}
		}
	printf("%lld\n",(cnt - m) / 2); //最后对答案的处理
	return 0;
}
```



  


---

## 作者：Kelin (赞：22)

状压$DP,f[u][s][v]$为$u->v$的环经过路径状态为s的路径数


这样会有重复,所以直接设$f[s][u]$表示$s$中最小的点到u的路径数


为了避免重复计算,回到的点为$s$中最小的点(这是一个优化,少了枚举最小点这个循环)


如果$v$是$s$中最小的点那么$ans+=f[s][u]$


如果$v$不在$s$中那么$f[s|1<<v][v]+=f[s][u]$


然后一个环会被记两次还有原来的$m$条双向边也是环,减掉就好了


然后这里有一个讲得比较好的[blog](http://blog.csdn.net/fangzhenpeng/article/details/49078233)


---

## 作者：Lily_White (赞：11)

状压DP。

设$dp[s][j]$表示经过了集合$s$中的点，现在在$j$的方案数。我们把$lowbit(s)$看作起点。转移时，枚举$i$点，如果$i \in s$枚举$j$， 如果$(i,j) \in E$就把$j$加入集合进行扩展。时间复杂度为$O(2^nn^2)$。注意到这样一个环会被算两次，除以$2$即可。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int N = 20;
int d[N][N]; LL dp[lsh(N - 1)][N]; int  n, m;
int lowbit(int x) {
	rep(i, 20) if (lsh(i) & x) return i;
}
int main() {
	cin >> n >> m;
	rep(i, m) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		d[u][v] = d[v][u] = 1;
	}
	rep(i, n) dp[lsh(i)][i] = 1;
	rep(s, lsh(n))
		rep(i, n)
			if (dp[s][i])
				for (int j = lowbit(s) + 1; j < n; j++) {
					if (d[i][j] && !(s & lsh(j))) dp[s | lsh(j)][j] += dp[s][i];
				}
	LL ans = 0;
	rep(s, lsh(n))
		if (__builtin_popcount(s) >= 3)
			rep(i, n) 
				if (d[i][lowbit(s)])
					ans += dp[s][i];
	cout << ans / 2 << endl;
	return 0;
}
```


---

## 作者：_lbw_ (赞：10)

CF11D:

大水题，直接状压选过的点的集合

设 $f_{i,j}$ 表示 每个节点是否选过与现在到了那个点

转移 $f_{i∪k}=\sum\limits_{}f_{i,j}$，$k,j$ 之间
有边

复杂度 $O(m2^n)$

[代码](https://www.luogu.com.cn/paste/idw7wd5j)

---

## 作者：zimindaada (赞：8)

[题面](https://www.luogu.com.cn/problem/CF11D)

初看一眼，可以由数据范围看出来可以用状压```DP```来做。又因为这一道题是一个在图内求结果的一道题，所以说可以用记忆化搜索+状压。

我们可以想到令$f_{s,i,j}$为遍历过的点集为$s$，初始点为$i$当前点为$j$的路径数。那么答案就是所有的$f_{s,i,i}$。但是，这有个问题：空间会爆炸。$2^{19}×19×19$不管怎么说很明显是塞不进```250MB```的。并且，由于环的初始点可以是环上的任意一点，所以说答案势必偏大，对于每一个$f_s$，答案都要除以点集s内的点个数，也导致了统计答案的困难。所以说，我们至少优化掉一维。~~然后我就在这里卡了30分钟~~。

30分钟过后，我~~看题解~~想到了一种优化：令$f_{s,i}$表示以遍历过的点集为$s$，初始点为$s$最低位，当前点为$i$的路径数。这样子，可行性很容易想出来：这样子就固定了一个环的初始点，不会重复统计，内存也小了很多，~~而且刚好卡的进64M，所以其实n <= 20应该问题不大~~。

那么我们在搜索的过程中，我们该如何转移？我们在遍历当前点的每一个邻节点的时候，如果它在当前点集的时候，并且还恰巧是这个点集的最小的点（也就是开始点），那么就成了环，是一种情况。如果不在当前点集的话，只要保证他比最低位的$1$的位置大（不更改初始点），就可以继续转移了。

此外，这份代码里面有用到```__builtin```系列函数，具体相关可以看[这篇博客](https://www.luogu.com.cn/blog/your-alpha1022/gcc-hei-ke-ji-zhi-builtin-ji-lie-han-shuo)，不想看的话在代码里面解释了一下。剩下的细节在代码里面会写。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define count(x) __builtin_popcountll(x)//求一个数二进制里有多少个1
#define smallest_one(x) __builtin_ffsll(x)//求最小的1在第几位
template<typename T> inline void read(T& t) {
    t=0;short f=1;char ch=getchar();double d = 0.1;
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') t=t*10+ch-'0',ch=getchar();
    if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
    t*=f;
}
#define int long long
const int maxn = 20;
int n, m;

int last[maxn], ecnt;
struct edge{int y, gg;} e[3005];
inline void addedge(int x, int y){
    e[++ecnt].y = y; e[ecnt].gg = last[x];
    last[x] = ecnt;
}

ll f[1<<maxn][maxn];
bool vis[maxn];
ll dfs(int x, int stat){
    vis[x] = 1;//防重
    if(f[stat][x]) return f[stat][x]; //记忆化搜索，搜过就不搜
    for(int i = last[x]; i; i = e[i].gg){
        int y = e[i].y;
        if((1<<(y-1)) & stat){
            if(count(stat) > 2 && y == smallest_one(stat)){
            //关于这个count(stat)为什么要大于2，这是为了保证不会存在一条边两个点的假环，毕竟是无向图，dfs可能会出现
            //其他题解的(ans-m)/2也是这个原因，排除掉一条边两个点的假环
                ++f[stat][x];
            }
        }else{
            if(y > smallest_one(stat)){
                f[stat][x] += dfs(y, stat | (1 << (y - 1)));
            }
        }
    }
    return f[stat][x];
}
signed main(){
    read(n); read(m);
    int xx, yy;
    for(int i = 1; i <= m; ++i){
        read(xx); read(yy);
        addedge(xx,yy); addedge(yy,xx);
    }  
    
    ll ans = 0;
    for(int i = 1; i <= n; ++i){
        ans += dfs(i, 1<<(i-1));
    }
    
    printf("%lld\n", ans/2);
    //为什么要除2呢？一个环可以顺时针和逆时针着搜，所以一个环搜了两边
    return 0;
}
```

[博客推广](https://www.luogu.com.cn/blog/zimindaada/)

---

## 作者：lukelin (赞：5)

### 前言
&ensp; **更好的阅读体验？**  
&ensp;&ensp;&ensp; **[我的博客](https://www.cnblogs.com/linzhengmin/p/11211754.html)**  
&ensp; 有帮助的话就点个赞吧QAQ。  
### 题解
我们从最简单的思路开始考虑，首先看到题目发现$n$非常小，于是很容易想到状态压缩。  
我们考虑比较直觉的状态，f[i][j][k]表示以i为起点，当前在j，之前去过的点状态为k的简单环的方案数。  
仔细思考以后，我们发现这个状态有问题，问题在于，每一个环再环内的每个点都被计算了一次。  
那么怎么避免这种状态呢？我们考虑让每个环仅由其中编号最小的点贡献。  
这样操作了以后，每个环仍然被**计算了两遍**(顺时针一次，逆时针一次)，但是关系不大，最后统计答案的时候除2即可。  
考虑到起点已经是环中最小的点了，于是我们无需再状态里额外记录它。  
于是将状态变换成f[i][j]表示当前在i，之前去过的点状态为j的简单环的方案数。  
那么状态之间如何转移呢？直接DP有些困难，于是我们使用记忆化搜索。  
在记忆化搜索的时候要记录一个值表示当前去过几个点，因为显然数量在2即以下的点构不成简单环，但会被记搜记录答案，特判即可。  
### 代码
```cpp
#include <cstdio>

namespace fast_IO{
    const int IN_LEN = 10000000, OUT_LEN = 10000000;
    char ibuf[IN_LEN], obuf[OUT_LEN], *ih = ibuf + IN_LEN, *oh = obuf, *lastin = ibuf + IN_LEN, *lastout = obuf + OUT_LEN - 1;
    inline char getchar_(){return (ih == lastin) && (lastin = (ih = ibuf) + fread(ibuf, 1, IN_LEN, stdin), ih == lastin) ? EOF : *ih++;}
    inline void putchar_(const char x){if(oh == lastout) fwrite(obuf, 1, oh - obuf, stdout), oh = obuf; *oh ++= x;}
    inline void flush(){fwrite(obuf, 1, oh - obuf, stdout);}
    int read(){
        int x = 0; int zf = 1; char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar_();
        if (ch == '-') zf = -1, ch = getchar_();
        while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar_(); return x * zf;
    }
    void write(long long x){
        if (x < 0) putchar_('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar_(x % 10 + '0');
    }
}

using namespace fast_IO;

struct Edge{
	int to, next;
} edges[1005];

int head[20], edge_num = 0;

inline void addEdge(int from, int to){
	edges[++edge_num] = (Edge){to, head[from]};
	head[from] = edge_num;
}

long long f[20][1048577];
int vis[20];

long long DFS(int frt, int u, int sta, int cnt){
	vis[u] = 1;
	if (f[u][sta])
		return f[u][sta];
	for (int c_e = head[u]; c_e; c_e = edges[c_e].next){
		int v = edges[c_e].to;
		if ((1 << (v - 1)) & sta){
			if (cnt > 2 && v == frt)
				++f[u][sta];
		}
		else
			if (v > frt)
				f[u][sta] += DFS(frt, v, sta | (1 << (v - 1)), cnt + 1);
	}
	return f[u][sta];
}

int main(){
	int n = read(), m = read();
	for (int i = 0; i < m; ++i){
		int u = read(), v = read();
		addEdge(u, v), addEdge(v, u);
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += DFS(i, i, (1 << (i - 1)), 1);
	write(ans / 2); flush();
	return 0;
}
```

---

## 作者：hehelego (赞：4)

# CF11D 简单无向图 的 简单环/圈计数

题目:给定一个没有重边自环的无向图,求简单环的数量,要求边和点均不能自交.两个环不同,当且仅当"旋转"不能使得它们重合,$\vert V\vert \lt 20$.

首先这个题是9年前(2010左右,这个题解写于2019年)的题目,现在估计稍微大一点点比如$n=21$左右可能可以跑过去...  


----


考虑简单环的上界,一个完全图,任何一个排列都可以成环,所以是$\sum_{i=2}^n\binom{n}{i}\frac{i!}{i}$就挺大的emm...就圆排列,一个排列被统计$len$次...写错了别打我,重点是说明答案非常大,即使$O(1)$时间检验排列能不能成环也会TLE.

---

考虑怎么由阶乘降低到指数,我们考虑在图上游走,走到遇到走过了点即找到了环,枚举一个起点,然后开始搜.  这样一个环被统计的次数是$len$(环长)的.更进一步地,如果考虑从环内编号最小的点处断开,那么只会被统计两次..就正向反向走两次呗....


我们进一步观察,这个过程相当于枚举了和编号最小的点相连的边,断开,并且进行一个路径计数,不允许经过编号更小的点,不能允许走重复的点或者边. 这个很好用一个DP来做.

$dp_{s,v}$ 表示经过了s中的点,目前在v处,从start走到这个状态的路径计数.
那么最小编号为start的环数量是$\sum_{(v,start)\in E} dp[s][v]$. 注意一条边也会被计算进来.即产生了"二元环"显然是不需要的.

我们枚举最小编号点,进行DP,求出最小编号为$x$的环的数量\*2+二元环(边数).


```cpp
#include <bits/stdc++.h>
const int N=20;
int n,g[N][N],m,low[1<<N];
typedef long long Int;

inline int lowbit(int x){ return x&(-x); }
inline int popcnt(int x){
	int y=0;
	while(x){
		y++;
		x^=lowbit(x);
	}
	return y;
}

std::string dump(int s){
	std::string ret;
	for(int i=0;i<n;i++) if(s&(1<<i))
		ret=ret+char(i+'0');
	return ret;
}
inline int in(int s,int i){ return (s&(1<<i))>0; }
Int dp[1<<N][N];
bool vis[1<<N][N];
inline void clear(){
	for(int s=0;s<(1<<n);s++) 
		for(int i=0;i<n;i++) dp[s][i]=vis[s][i]=0;
}
int start=0;
// count_path:walk through(s),get x
// 路径计数DP.
Int f(int s,int x){
	if(vis[s][x]) return dp[s][x];
    // 注意递归基
	if(s==lowbit(s)) return s==(1<<start)&&x==start;
	Int ret=0;
    // 不允许经过编号更小的点,故可以修改循环下界.
	for(int i=start;i<n;i++) if(in(s,i)&&g[x][i]){
		ret+=f(s^(1<<x),i);
	}
	vis[s][x]=1;
	return dp[s][x]=ret;
}

int main(){
	std::cin>>n>>m;
	for(int i=0;i<n;i++){
		low[1<<i]=i;
		dp[1<<i][i]=1;
	} low[0]=-1;
	for(int i=2;i<(1<<n);i++) low[i]=low[lowbit(i)];


	for(int i=0,a,b;i<m;i++){
		std::cin>>a>>b; a--;b--;
		g[a][b]=g[b][a]=1;
	}

	Int ans=0;
	for(start=0;start<n;start++){
		// sum(dp[S][i]) where (i->start)
		clear();
		for(int s=0;s<(1<<n);s++) if(low[s]==start&&s>lowbit(s)){
			for(int i=0;i<n;i++) if(in(s,i)&&g[start][i]) ans+=f(s,i);
		}
	}
    
    // 扔掉二元环,每个真环正反计数两次.
	ans=(ans-m)/2;
	std::cout<<ans<<std::endl;
	return 0;
}

```






---

## 作者：cqbzhyf (赞：1)

[题目](https://www.luogu.com.cn/problem/CF11D)

首先这是一道**状压**，因为 $n \le 19$，$n$ 如此小，就可以用二进制表示选择的状态。

首先定义状态：

$dp[i][j]$：最后选择了 $i$ 节点，选择的状态为 $j$.

开始初始化：

```cpp
dp[i][1<<(i-1)]=1;
```

注：因为本处考虑了**自环**，所以最后输出答案要减去！

为了方便去重，我们索性将状态的最后一位（`lowbit`）为环的起点。

于是考虑了两种情况：

![](http://61.186.173.89:2019/2022/03/22/81101b7af4dec.png)

![](http://61.186.173.89:2019/2022/03/22/047cb4d9eb8bf.png)

所以最后答案除以 $2$.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int ch=0,num=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int n,m,dp[20][1<<20],ans;
bool vis[25][25];
inline int lowbit(int x){return x&-x;}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		vis[x][y]=vis[y][x]=1;
	}
	for(int i=1;i<=n;++i)dp[i][1<<(i-1)]=1;
	for(int i=0;i<(1<<n);++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k){
				if(!vis[k][j]||lowbit(i)>1<<(k-1))continue;
				if(1<<(k-1)&i){
					if(1<<(k-1)==lowbit(i))ans+=dp[j][i];
				}else dp[k][i^1<<(k-1)]+=dp[j][i];
			}
		}
	}
	write((ans-m)>>1);
	return 0;
}
```

---

