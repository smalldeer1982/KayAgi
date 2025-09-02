# Shortest Cycle

## 题目描述

给定 $n$ 个整数 $a_1,\,a_2,\,\cdots,a_n$ ，考虑一张含有 $n$ 个节点的图，对于任意 $i\ne j$ ，若 $a_i\;\text{and}\;a_j\ne 0$ ，则节点 $i,\,j$ 连通，其中 $\text{and}$ 表示按位与运算

你现在需要求出该图最小环的大小，或确定其不存在环

## 样例 #1

### 输入

```
4
3 6 28 9
```

### 输出

```
4```

## 样例 #2

### 输入

```
5
5 12 9 16 48
```

### 输出

```
3```

## 样例 #3

### 输入

```
4
1 2 4 8
```

### 输出

```
-1```

# 题解

## 作者：寒鸽儿 (赞：10)

[在窝的博客阅读](https://froldh.github.io/2019/08/19/OI/codeforcesPlan/CFR580/)  
[在窝的luogu博客阅读](https://www.luogu.org/blog/oldherd/solution-CF1205B)  
找最小环,常用floyd算法。但是这个图太大,floyd O($n^3$)跑到n = 300就很吃力了。  
要么优化,要么奇技淫巧乱搞。  
观察图的性质,其实连边的概率还是很大的,换言之,图在随机情况下是比较稠密的。  
那么可以考虑,其实很大可能构成三元环,尤其在数字十分多的情况下。  
如果一个2进制位为1的数存在三个及以上,一定有三元环。  
根据抽屉原理,当n >= 128时,至少有1个二进制位满足该位为1的二进制数数目大于等于3,即构成三元环。  
n < 128时跑floyd最小环。  
特殊情况:  
对于$a_i$ = 0, 其实不可能与任何点连边,读入的时候要剔掉。  
```cpp
#include <cstdio> 

using namespace std;

const int sz = 2000000, maxn = 130, inf = 70000000;

char buf[sz], *p1 = buf, *p2 = buf;
inline char gc() { return p1==p2&&(p2=(p1=buf)+fread(buf,1,sz,stdin), p1==p2)?EOF:*p1++; }
inline long long read() {
    long long x = 0;
    int f = 1;
    char ch = gc();
    while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = gc(); }
    while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = gc();
    return x *= f;
}

inline int min(int a, int b) { return a < b ? a : b; }

long long a[maxn];
int f[maxn][maxn], m[maxn][maxn];

int main() {
	int n = (int)read();
	int ans = inf;
	for(int i = 1; i <= n; i++) {
		if(i >= 128) break;
		a[i] = read();
		if(!a[i]) {
			n--; i--;	
		}
	}
	if(n >= 128) {
		printf("3\n");
		return 0;	
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if((a[i] & a[j]) && (i != j))
				f[i][j] = m[i][j] = 1;
			else
				f[i][j] = m[i][j] = inf;
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				if(i == j || j == k || k == i) continue;
				ans = min(ans, f[i][j]+m[i][k]+m[k][j]);
			}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(f[i][j] > f[i][k] + f[k][j])
					f[i][j] = f[i][k] + f[k][j];
	}
	printf("%d\n", ans==inf?-1:ans);	
	return 0;	
}


```

---

## 作者：VinstaG173 (赞：4)

思路：

首先如果有个数是$0$，那么它肯定不在任意一个环里。

如果在某个二进制位上有三个数都是$1$，那么这三个数肯定构成环，答案为$3$。

接着由于最多$64$位，每位最多连到两个数，离散化一下，暴力搜索得出最小环长度就行了。

Code:
```cpp
#include<cstdio>
#define ll long long
int N,M;
ll x;
int cn[131][131];
int c[67][2];
int t[100003];
int d[131];
bool v[131];
int dfs(int u,int f)//暴力找环
{
	v[u]=true;int mn=131;//注意INF设为不可能达到的值（
	for(int i=1;i<=M;++i)
	{
		if(!cn[u][i]||i==f||i==u)continue;
		if(v[i])
		{
			if(mn>d[u]-d[i]+1)mn=d[u]-d[i]+1;
		}
		else
		{
			d[i]=d[u]+1;
			int k=dfs(i,u);
			if(mn>k)mn=k;
		}
	}
	v[u]=false;
	return mn;
}
int main()
{
	scanf(" %d",&N);
	for(int i=1;i<=N;++i)
	{
		scanf(" %I64d",&x);
		if(!x)continue;//x为0,没有影响
		int t=0;
		while(x)
		{
			if(x&1)
			{
				if(c[t][1])//该位上有三个数为1
				{
					printf("3\n");return 0;
				}
				else if(!c[t][0])c[t][0]=i;
				else c[t][1]=i;
			}
			x>>=1,++t;
		}
	}
	for(int i=0;i<64;++i)
	{
		if(!c[i][1])continue;
		int a=c[i][0],b=c[i][1];//离散化，连边
		if(!t[a])t[a]=++M;
		if(!t[b])t[b]=++M;
		cn[t[a]][t[b]]=cn[t[b]][t[a]]=1;
	}
	int mmn=131;//注意INF设为不可能达到的值（
	for(int i=1;i<=M;++i)
	{
		if(!v[i])
		{
			d[i]=0;
			int k=dfs(i,0);
			if(mmn>k)mmn=k;
		}
	}
	if(mmn==131)printf("-1\n");//不存在环
	else printf("%d\n",mmn);
	return 0;
}
```

---

## 作者：_Supernova (赞：3)

# 一、简述题意。

对于一张 $n$ 个点的图，每个点有权值 $a_i$，若两点权值与起来不为 $0$，则两点之间有边，求最小环的大小。

# 二、思路分析。

首先考虑数据范围，注意到 $n\leq10^{5}$，所以大部分算法无法通过，我们需要另寻他路。

根据题目，我们发现环最小长度为 $3$，即三点两两连边，而达到这样的条件便是这三个点的权值在二进制下第 $i$ 位都为 $1$。考虑到图比较稠密，所以这种情况概率很大。

考虑抽屉原理。即当 $n>120$ 时，必定答案为 $3$。

考虑证明：

观察数据范围，位数最多达到 $60$ 位。所以，如果 $n=120$，此时最好的情况便是每一位都有 $2$ 个 $1$，此时再新填一个数，必定答案为 $3$。

插入一句话：抽屉原理的核心就是往最好的方向考虑。

那如果 $n\leq120$ 呢？如何求最小环呢？

方法：Floyd 求最小环。

同学们可以看看这里：

[最小环求法](https://oi-wiki.org/graph/min-cycle/)

我们设 $u$ 与 $v$ 之间的边权为 $val(u,v)$。

最短路为 $dis(u,v)$。

Floyd 算法有一个性质：当外层循环到点 $k$ 时，$dis(u,v)$ 表示的是 $u$ 和 $v$ 在只经过点 $[1,k)$ 时的最短路。

所以，我们令环中最大点为 $p$，它相邻的点为 $u$ 和 $v$，则环的长度为 $dis(u,v)+val(u,p)+val(v,p)$。

枚举即可。

Floyd 基本模板与思路这里不再赘述。

# 三、代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, N_ = 130;
const ll inf = 1e18;
ll n, a[N], ans = inf;
ll val[N_][N_], dis[N_][N_];
int main(void) {
	cin.tie(0),cout.tie(0);
	cin >> n;
	for (ll i = 1; i <= n; ++i) {
		cin >> a[i];
		if (!a[i]) {
			--i, --n;
			continue;
		}
	}
	if (n > 120) {
		printf("3");
		return 0;
	}
	for (ll i = 1; i <= n; ++i) {
		for (ll j = 1; j < i; ++j) {
			val[i][j] = val[j][i] = dis[i][j] = dis[j][i] = inf;
			if (a[i] & a[j]) {
				dis[i][j] = dis[j][i] = val[i][j] = val[j][i] = 1;
			}
		} 
		val[i][i] = dis[i][i] = 0;
	}
	for (ll k = 1; k <= n; ++k) {
		for (ll i = 1; i < k; ++i) {
			for (ll j = i + 1; j < k; ++j) {
				ans = min(ans, dis[i][j] + val[i][k] + val[k][j]);
			}
		}
		for (ll i = 1; i <= n; ++i) {
			for (ll j = 1; j <= n; ++j) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	if (ans == inf) printf("-1");
	else printf("%lld", ans);
    return 0;
}
```

感谢大家与管理员！

---

## 作者：tzc_wk (赞：2)

题意：有$n$个数$a_1,a_2,a_3,\dots,a_n$。已知如果两个数$a_i,a_j (i \neq j)$满足$a_i\ and\ a_j \neq 0$（其中$and$操作为按位与操作），那么在$i$号节点与$j$号节点间连一条边，求所构成的图的最小环的长度。

思路：首先，我们明白，这张图要么没有环，要么最小环的长度大于等于$3$，因此，对于二进制下的每一位，只要有一位在$3$个及以上个数的二进制表示下为$1$，那么答案一定为$3$。

因为每个数都小于$10^{18}$，因此每个数最多有$60$位，因此如果有超过$120$个非零数字，那么必定有一位在$3$个及以上个数的二进制表示下为$1$。

考虑没有任何一位在$3$个及以上个数的二进制表示下为$1$的情况，我们暴力连边，然后跑$Floyd$求最小环。因为最大只有$120$个非零数字，所以时间复杂度最大为$O(120^3)$。

总的时间复杂度$O(n\ log 10^{18}+120^3)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100005],b[100005],dist[130][130],s[130][130],ans=LLONG_MAX,cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=0)		b[++cnt]=a[i];
	}
	for(int i=1;i<=60;i++){
		int cnt=0;
		for(int j=1;j<=n;j++){
			if(a[j]>>(i-1)&1){
				cnt++;
			}
		}
		if(cnt>=3){
			puts("3");
			return 0;
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=cnt;j++){
			if(i!=j&&((b[i]&b[j])!=0))		s[i][j]=1,dist[i][j]=1;
			else							dist[i][j]=s[i][j]=0x3f3f3f3f;
		}
	for(int k=1;k<=cnt;k++){
		for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++)
				ans=min(dist[i][j]+s[i][k]+s[k][j],ans);
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
				dist[i][j]=min(dist[i][k]+dist[k][j],dist[i][j]);
	}
	cout<<((ans>=0x3f3f3f3f)?-1:ans)<<endl;
}
```

---

## 作者：_yang_yi_bo_ (赞：1)

首先，我们根据 `long long` 的二进制位最多只有  $63$ 位（不包括符号位）得知：在数组中不为 $0$ 的数 $\ge 127$ 时，保证最小环长度为 $3$，而数组中的 $0$ 无任何用处，可以省略，于是 $n \le 127$ 时，我们可以用 Floyd 来找最小环。

为什么在数组中不为 $0$ 的数 $\ge 127$ 时，保证最小环长度为 $3$ 呢？最坏情况为数组里的数为 $2^n$，因为 `long long` 的二进制位有 $63$ 位，根据容斥原理，在 $\ge 127$ 时，必然有 $3$ 个数字重复，形成环。

若数组中不为 $0$ 的数 $< 128$ 时，可以用 Floyd 求解，每次都需要加入中转点 $k$，第一个双重循环$ans$ 表示最小环的长度，若 $i \to j$ 联通，$j \to k$ 直接联通且 $k \to i$ 直接联通，肯定存在环，若当前环的大小比 $ans$ 更小，记录最小值，第二个双重循环就是普通的 Floyd 求最短路，因为是找最小的环，需要记录的时最短路。

注意：
1. 不能创建自环，会对答案有影响；
2. 输入的数组不要开大一点，不要大小只开到 $128$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans=2e18;
int a[100005];
int g[130][130];
int dis[130][130];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==0){
			n--;
			i--;
		}
	}if(n>=127){
		cout<<3;
		return 0;
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=1e18;
		}
	}for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j&&(i!=0||j!=0)){
				dis[i][j]=0;
			}else if((a[i]&a[j])!=0){
				dis[i][j]=1;
			}g[i][j]=dis[i][j];
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++){
			for(int j=i+1;j<k;j++){
				ans=min(ans,g[i][k]+g[k][j]+dis[i][j]);
			}
		}for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}cout<<(ans>1e18?-1:ans);
	return 0;
} 
```

---

## 作者：Mystic_dragon (赞：1)

相比普通的最小环题似乎只是增大了点数据。~~还以为又是什么高深莫测的算法。~~

看到这里的数据约束和题面中两数按位与的结果决定连边，可以将每个数二进制拆解，显然可以是 $60$ 位二进制数。对于三个 $60$ 位二进制数，如果他们有其中一位均为 $1$ ，显然他们的按位与值不为 $0$。不难看出根据抽屉原理，如果有多于 $121$ 个非 $0$ 的数，多出来的一个数就能和之前的两个数匹配上，这时的最小环大小为 $3$。特殊的是，对于二进制拆解，可以根据自我习惯决定拆解的位数，只要对应调整边界值，还是没有问题的。

解决完这个后，对于求解最小环，就是常规操作了。不会的看这里：

[P6175 无向图的最小环问题](https://www.luogu.com.cn/problem/P6175)


------------

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
typedef long long i64;
i64 n;
i64 a[500010];
i64 tot;
i64 G[128][128];
i64 dist[128][128];
i64 res=1e18;
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){
        scanf("%lld",&a[i]);
        tot += (!a[i] ? 0 : 1);
        if(!a[i]) --i,--n;
    }
    if(tot>=121){
        printf("3");
        return 0;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=i-1;++j){
            dist[i][j]=dist[j][i]=G[i][j]=G[j][i]=1e18;
            if(!(a[i] & a[j])) continue;
            dist[i][j]=dist[j][i]=G[i][j]=G[j][i]=1;
        }
    }
    for(int k=1;k<=n;++k){
        for(int i=1;i<=k-1;++i){
            for(int j=i+1;j<=k-1;++j){
                res=min(res,dist[i][j]+G[i][k]+G[k][j]);
            }
        }
        //--------------------------------------------------------------
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(i!=j && j!=k && i!=k){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    dist[j][i]=dist[i][j];
                }
            }
        }
    }
    if(res==1e18) printf("-1");
    else printf("%lld",res);
    return 0;
}
/*

*/
```

---

## 作者：feizhu_QWQ (赞：1)

# CF1205B Shortest Cycle 题解

## 前言

其实这道题就是[这道题](https://www.luogu.com.cn/problem/P6175)的加强版，可以先看看那道，再来看这道，就文思泉涌了。\
这道题看到“找图的环”，算法就出来了，所以。

## 解法：Floyd

这道题第一眼看上去就是 Floyd，可问题是 $n$ 太 $big$ 了，所以不能直接套模板。\
所以突破口就在于他的建边要求。\
众所周知，与运算是遇 $0$ 则 $0$ 的，而且这道题是 `long long` 范围，所以我们判断是否有环的标准就是二进制的 $64$ 位中是否有 $3$ 个数这个位是 $0$。\
可光知道这个还没啥用，我们可以发现，但凡他的数超过了 $128$ 个，就一定有一个二进制位有 $3$ 个 $0$。\
所以我们只用判断 $n$ 是否大于 $128$ 就可以了，如果大于，就直接输出 $3$。\
否则直接跑 Floyd，这里的代码和前言说的题目类似，我们细细来讲。

假设我们在 Floyd 里枚举了中转点 $k$，剩余两个要连接的点是 $i$,$j$，那么怎么判断他们是否成环呢？\
当然，只用判断 $i$ 和 $k$，$k$ 和 $j$，$i$ 和 $j$ 是否都连通就行啦。\
此外，我们用一个二维数组记录两点的是否连通，那么我们可以直接加来判断是否连通了。\
为啥这么草率？\
首先，我们一开始把 $dis$ 数组设为了最大值，把他加起来和最优答案打擂台，一定会败。\
其次，我们的二维数组也和 $dis$ 数组一样，照样可以这样判连通。\
这样看来，直接加起来是可以判连通滴。

还没完：一开始你需要把所有的 $0$ 踢掉，因为它和任意一个数按位与都会为 $0$。\
代码就这么出来了。

```cpp
#include<bits/stdc++.h>
#define int long long//孩纸不要忘记开long long哦！
using namespace std;
int n;
int a[1000005];
int dis[155][155],mon[155][155];
int vis[130];
int m,minn=1e18;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==0)
		{
			n--,i--;//处理0的情况
		}
	}
	if(n>128)//判断答案必为3的情况
	{
		cout<<3;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dis[i][j]=1e18;
			if((a[i]&a[j])!=0)
			{
				dis[i][j]=1;
			}
			if(i==j) dis[i][j]=0;
			mon[i][j]=dis[i][j];
		}//初始化
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<k;i++)
		{
			for(int j=i+1;j<k;j++)
			{
				minn=min(minn,dis[i][j]+mon[i][k]+mon[k][j]);//上面说的直接做加法来判连通
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//经典Floyd
			}
		}
	}
	if(minn==1e18) cout<<-1;//不要忘记判-1!
	else cout<<minn;
	return 0;
}
```

~~说实话这道蓝题挺水的~~

---

## 作者：Dregen_Yor (赞：0)

### [更好的阅读体验](https://dregen-yor.eu.org/2022/11/23/cf1205b/)。

~~个人认为这道题评不到蓝。~~

# 思路

根据题目中建图的性质，我们可以考虑对一个数转化成二进制的形式，并记录每一位的 $1$ 的个数，若在某一位上，有至少 $3$ 个点这一位为 $1$，那么这三个点之间都有一条边，也就是形成了一个三元环，根据数据范围，把所有数转化成二进制后最多有 $64$ 位，根据抽屉原理，当 $n> 128$ 时，一定存在一位，该位为 $1$ 的点的个数超过 $3$，对于其他的情况，因为 $n\le128$，我们直接用 floyd 判最小环即可。

注意，$a_i$ 可能存在为 $0$ 的情况，我们要排除所有为 $0$ 的点，用非 $0$ 的点的个数作为 $n$ 进行判断。

# 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,a[100010],sum[70];
int G[200][200],dis[200][200],cnt;
char s[70];
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        if(a[i]!=0){
            cnt++;
        }
    }if(cnt>150){
        puts("3");
        return 0;
    }
    sort(a+1,a+1+n,greater<int>());
    
    for(int i=0;i<=150;i++){
        for(int j=0;j<=150;j++){
            dis[i][j]=G[i][j]=1e9;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<i;j++){
            if(a[i]&a[j]){
                dis[i][j]=dis[j][i]=G[i][j]=G[j][i]=1;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         printf("%d ",G[i][j]);
    //     }
    //     putchar('\n');
    // }
    int ans=1e9+1;
    for(int k=1;k<=cnt;k++){
        for(int i=1;i<k;i++){
            for(int j=i+1;j<=k;j++){
                //if(i!=j&&j!=k&&i!=k)
                ans=min(ans,G[i][j]+dis[i][k]+dis[k][j]);
            }
        }
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=cnt;j++){
                //if(i!=j&&j!=k&&i!=k)
                G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
            }
        }
    }  
    if(ans<1e9){
        printf("%lld",ans);
    }
    else{
        puts("-1");
    }
    return 0;
}
```


---

## 作者：V1mnkE (赞：0)

## 思路
先观察一下数据范围，$n\leq 10^5$，光是连边的复杂度都不可以接受，所以要考虑推一下性质。

我们可以试着把每个 $a_i$ 拆成二进制，可以发现如果任意一个二进制位如果有三个 $1$，那最小环必然是 $3$，再看一下数据范围，$a_i\leq 10^{18}\le 2^{64}$，根据鸽巢原理，如果 $n\geq 129$，则必然有一个二进制位的 $1$ 的个数大于等于 $3$。

处理完这种情况后，我们要解决的数据范围变成了 $n\leq 128$，直接暴力连边跑 Floyed 求最小环即可。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x * f;
}
inline void write(int x) {
    static char buf[20];
    static int len = -1;
    if (x < 0) putchar('-'), x = -x;
    do buf[++len] = x % 10, x /= 10;
    while (x);
    while (len >= 0) putchar(buf[len--] + '0');
    putchar('\n');
}
int n, a[100005], f[100005], siz[100005], dis[129][129];
int cnt, head[100005], edge[129][129];
signed main() {
    n = read();
    
    for (int i = 1; i <= n; i++){
    	 a[i] = read();
    	 if(a[i]==0)n--,i--;
	}
    if (n >= 129)cout << 3,exit(0);
    
    int ans = 1e8 + 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            edge[i][j] = edge[j][i] = dis[j][i] = dis[i][j] = 1e8;
            if ((a[i] & a[j]) != 0) {
                // cout << i << ' ' << j << endl;
                edge[i][j] = edge[j][i] = dis[i][j] = dis[j][i] = 1;
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                // cout << ans << ' ' << dis[i][j] + edge[i][k] + edge[k][j] << endl;
                ans = min(ans, dis[i][j] + edge[i][k] + edge[k][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && j != k && k != i) {
                    // ans = min(ans, dis[i][j] + dis[i][k] + dis[k][j]);
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    dis[j][i] = dis[i][j];
                }
            }
        }
    }
    if (ans == 1e8 + 1)
        cout << -1;
    else
        cout << ans;
    // system("PAUSE");
}
```

---

## 作者：Xdl_rp (赞：0)

本题是一道**结论题**

solution
------------

- 如果有 $3$ 个数是可以互相与的，则答案一定是 $3$（这个就没必要说了吧）。那我们考虑什么时候一定有这种情况发生，根据抽屉原理（也就是鸽巢原理）可知，在 $n \ge 128$ 时，至少有一位上（二进制）满足至少有 $3$ 个 $1$，必构成三元环，所以在 $n \ge 128$，我们可以来一个特判。

```cpp
	for (int i = 1; i <= n; i++) {
	    scanf("%lld", &a[i]);
	    if (!a[i]) i--, n--;
	    else cnt++;
	}
	if (cnt >= 128) {
		puts("3");
		return 0;
	}
```

- 剩下的情况直接暴力 `floyd` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define inf 0x3f3f3f3f//定义极大值
int a[1000005];
int edge[2005][2005], dis[2005][2005];

signed main() {
	int n, cnt = 0;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
	    scanf("%lld", &a[i]);
	    if (!a[i]) i--, n--;
	    else cnt++;
	}
	if (cnt >= 128) {
		puts("3");
		return 0;
	}//输入和特判
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if ((a[i] & a[j]) != 0) dis[i][j] = dis[j][i] = edge[i][j] = edge[j][i] = 1;
			else dis[i][j] = dis[j][i] = edge[i][j] = edge[j][i] = inf;
		}
	}//把边权记好
	for (int i = 1; i <= n; i++) dis[i][i] = 0;//初始化
	long long ans = inf;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i < k; i++) {
			if (k == i) continue;
			for (int j = i + 1; j < k; j++) {
				ans = min(ans, dis[i][j] + edge[i][k] + edge[k][j]);
			}
		}//先将答案赋初值
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}//经典Floyd	
	}
	if (ans == inf) {
		puts("-1");
	}//如果没有满足的
	else printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：When (赞：0)

#### 算法

$Floyd$求最小环+推理

#### 思路

看到是无向图最小环，考虑$Floyd$，但是$n^3$的复杂度太高了，怎么办？

观察题面，发现两个数只要与起来是$1$就有边，进而想到只要有一个二进制位有三个以上的数字是$1$，就能构成$3$元环。考虑最坏情况，即每个位都只有两个数为$1$，就有$64 \times 2=128$种，那么只要$n>128$（准确地说是有效的数字$>128$）就肯定能构成$3$元环。而$n\leq 128$的数据就能$n^3$过了。

**然而**，

你会发现 **#16RE了** ，百思不得其解以后点开第十六个点，发现是一堆$0$，而全$0$的情况是不会输出$3$的，因此会爆数组。所以需要在读入的时候把$0
$滤掉。

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 300, maxm = 3e5 + 10;
const int INF = 70000000;
int n;
long long f[maxn][maxn],a[maxn][maxn],val[maxm];

int main(){
    scanf("%d", &n);
    int cnt = 0;
    for(int i = 1; i <= n; ++ i){
        scanf("%lld", &val[i]);
        if(val[i]) cnt ++;
        if(!val[i]) i--, n--;  //把0滤掉
        if(cnt >= 129){ printf("3\n"); return 0;}
    }
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j){
            if((val[i] & val[j]) != 0 && i != j) a[i][j] = f[i][j] = 1;
            else a[i][j] = f[i][j] = INF;
        }
    long long ans = INF;
    for(int k = 1; k <= n; ++ k){
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j)
                if(i != j && j != k && i != k)
                    ans = min(ans, f[i][j] + a[i][k] + a[k][j]);
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    } 
    if(ans == INF) ans = -1;
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：ZigZagKmp (赞：0)

本文同步于[CF1206总题解](https://www.luogu.org/blog/zhouzikai/cf1206round-580-div2-post)，欢迎各路神仙来踩。

## D Shortest Cycle
### 题意
给定长度为$n$的序列$a$，若有$i,j\in [1,n],a_i\ and\ a_j\ne0$，则$i,j$连边，求建出的图的最小环大小，注意，最小环大小至少为3。
### 解法
1. Part 1 优化建图

$n\le 10^5$，我们显然不能直接建图，那么我们有一个大胆的猜测：是不是$n$比较大的时候答案一定是一个定值？

这个猜测先放在这里，我们来考虑位运算的本质：若$x\ and \ y \ne 0$，则一定存在某一个二进制位$k$，满足$x$的第$k$位和$y$的第$k$位都为$1$。

因此我们把建图的过程分解一下，枚举每一个二进制位$k$，设二进制下这一位为$1$的数属于一个可重集合$S$，那么$S$集合中的数**对应的位置**应该**两两**连边。如果这个集合中的数字个数$\ge 3$，则这一个集合的连边中一定出现大小为$3$的环，显然这应该是本题有解情况下的**最小答案，不会再被更新**，因此我们可以确定答案为3。

如果集合中数字个数$\le 1$，这也不需要连边。

如果集合中数字个数$=2$，只需要将这两个点连一条边即可。

因为$a_i\le 10^{18}$，所以讨论的位数应该不超过$64$，每讨论一位，只有集合大小为2的时候要连$1$条无向边，因此最多连$64$条无向边，这个图最多有$128$个结点。

回到我们的猜测，如果$n>128$，我们可以断定必定存在一个集合的数字个数$\ge 3$，因此这时答案一定是3。

2. Part 2 求解最小环

我们建出来的图的规模是$n\le 128,m\le 64$，因此基本上$O(n^3)$或者更优的求最小环的算法都可以过。

无向图上最小环算法大多数基于最短路（主要是我太菜了不会其他的算法），这里做一个小总结，以纪念我的第一次$FST$。

1.  `Floyd`判最小环

算法原理：讨论每两个点$i,j$，求出$i,j$两个点为端点的不同路径长度之和，即为最小环大小，取最小值即可。

因为我们只确定$i,j$还不能确定它们之间的不同路径，所以我们要再引入一个$k$，让一条路径定死了（必须经过$k$），然后找到一条**不经过k**的路径，这两条路径一定构成一个至少有三个点的环。

答案更新应该是$a[i][k]+a[k][j]+dis[k-1][i][j]$（这里$k-1$表示当前的最短路没有被$k$更新，一般写的时候把统计答案放在更新前面即可省去$k-1$这一维，下面同理）

不过蒟蒻的我有一点疑问：为什么不是用$dis[i][k]+dis[k][j]+dis[i][j]$更新答案呢？$dis[i][k]\le a[i][k]$，虽然说用$a[i][k]$更新不会漏掉最优解，但是用$dis[i][k]$更新会出现答案偏小（错误）的情况吗？请各路神仙在评论区发表高见。

2. 基于~~已死的~~`SPFA`求最小环

这里用`dfs`实现比较好理解。
```cpp
void dfs(int x,int fa,int w){
    vis[x]=1;//已求解联通块标记
    dis[x]=dis[fa]+w;
    for(){//枚举边
    	int y=//边的出点
        int w=//边的长度
        if(y==fa)continue;//两个点不构成环
        if(dis[y])ans=min(ans,dis[x]-dis[y]);//有些求最小环需要有微小修改
        else dfs(y,x,w);
    }
    dis[x]=0;//可以重新走到这个节点来更新最小环
}
```

3. 基于`Dijkstra`求最小环

因为笔者太菜了，暂时不会。

---

## 作者：周子衡 (赞：0)

思路：图论知识+暴力

首先可以发现，如果某个二进制位上有至少$3$个$1$，那么这三个数一定可以构成环，答案即为$3$。

接着考虑每位至多$2$个$1$的情况。这时可以发现图中边数极少，最多$63$条（$2^{63}>10^{18}$）。暴力判断即可。我的代码中采用这样的方法：对于每个点，枚举它的相邻点至少多少步能在**不经过原点**的情况下走到另一个与之相邻的点。

代码：

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

long long a[100010];
vector<int> ed[100010];

int tmp[10];
int dis[100010];
queue<int> q;

int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	for(int i=0;i<=62;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]&(1ll<<i))cnt++;
		}
		if(cnt>=3){printf("3");return 0;}
	}
	for(int i=0;i<=62;i++)
	{
		int t=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]&(1ll<<i)){t++;tmp[t]=j;}
		}
		if(t==2)ed[tmp[1]].push_back(tmp[2]),ed[tmp[2]].push_back(tmp[1]);
	}
	
	int minn=1e9;
	for(int i=1;i<=n;i++)
	{
		if(ed[i].size()>1)
		{
			for(int j=0;j<ed[i].size();j++)
			{
				int x=ed[i][j];
				for(int k=1;k<=n;k++)dis[k]=1e9;dis[i]=dis[x]=0;
				while(!q.empty())q.pop();q.push(x);
				while(!q.empty())
				{
					int t=q.front();q.pop();
					for(int k=0;k<ed[t].size();k++)
					{
						int r=ed[t][k];
						if(dis[r]==1e9){dis[r]=dis[t]+1;q.push(r);}
					}
				}
				int tmp=1e9;
				for(int k=0;k<ed[i].size();k++)
				{
					int t=ed[i][k];
					if(t!=x)tmp=min(tmp,dis[t]);
				}
				minn=min(minn,tmp+2);
			}
		}
	}
	if(minn==1e9)printf("-1");else printf("%d",minn);
	return 0;
}
```

---

## 作者：w1049 (赞：0)

题意：给定一些数，如果$a_i \& a_j
!=0$则$i$与$j$之间有边，求图中的最小环。

不难想到用$Floyd$算法找环，但是$n$的范围很大，明显不能所有的数据都使用$Floyd$。

观察题意，可以发现，只要两个数的二进制表示中有一位均为1，则两数之间有边。

若三个数之间两两有边，就可以知道这是一个三元环。

而数据范围为$a_i\in[1,10^{18}]$，二进制中最多有63位，根据抽屉原理，如果有大于128个数，则必有3个数有公共的$"1"$，也就是一个三元环。

所以：当$n<128$时使用$Floyd$找最小环，$n>=128$时直接输出3。

注意对$0$特判。

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
int n;
int m[128][128], f[128][128], tmN0;
LL a[100001];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), (a[i] == 0) && (i--, n--);
	if (n >= 128) return puts("3"), 0;
    memset(m, 0x3f, sizeof m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++)
            if (a[i] & a[j]) m[i][j] = m[j][i] = 1;
        m[i][i] = 0;
    }
    memcpy(f, m, sizeof m);
    int ans = 0x3f3f3f3f;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++)
            for (int j = 1; j < i; j++) {
                if (i == j || j == k || k == i || m[i][k] == 0x3f3f3f3f || m[k][j] == 0x3f3f3f3f || f[i][j] == 0x3f3f3f3f) continue;
                ans = min(m[i][k] + m[k][j] + f[i][j], ans);
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                    f[i][j] = min(f[i][k] + f[k][j], f[i][j]);
    }
    if (ans == 0x3f3f3f3f) puts("-1");
    else printf("%d\n", ans);
}
```

---

