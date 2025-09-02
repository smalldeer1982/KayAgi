# [POI 2008] POD-Subdivision of Kingdom

## 题目背景

[English Edition](/paste/eu7u3hqg)

## 题目描述

给出一张有 $n$ 个点 $m$ 条边的无向图，你需要求出一组合法的方案，使得图被划分为点数均为 $\frac n2$ 的两个集合，且两个端点在不同集合中的边数最少。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 26$，$1\le a,b\le n$，且 $n$ 为偶数。保证没有重边。

## 样例 #1

### 输入

```
6 8
1 2
1 6
2 3
2 5
2 6
3 4
4 5
5 6
```

### 输出

```
1 2 6
```

# 题解

## 作者：hongzy (赞：10)

对于这题，首先，预处理出每个二进制数中1的个数.但是$2^{26}$的时间复杂度稍高，可以只处理到$2^{13}$，每次求的时候分成前13位和后13位分别处理.

dfs时，首先让集合S1为空，集合S2为所有点。从S2里选$\frac{n}{2}$个点加到S1里.每次选一个点$i$加入S1时，减去原S1与$i$连的边数，加上$i$与新S2连的边数.

上述过程均使用位运算实现，二进制存储一个点的相连的点，使用按位与(&)运算，配合上述求二进制1个数的方法，就可以计算贡献.

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 27;

int n, m, ans(N * N), s;
int e[N], cnt1[(1 << (N / 2)) + 10];

int Count1(int x) {
	return cnt1[x >> (N/2)] + cnt1[x - ((x >> N/2) << N/2)];
}

void dfs(int pos, int k, int sum, int s1, int s2) {
	if(k == n / 2) {
		if(sum < ans) s = s1, ans = sum;
		return ;
	}
	for(int i=pos+1, ns2; i<=n; i++) {
		ns2 = s2 ^ (1 << i-1);
		dfs(i, k+1, sum - Count1(e[i] & s1) + Count1(e[i] & ns2), s1 | (1 << i-1), ns2);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<1<<(N/2); i++)
		cnt1[i] = cnt1[i>>1] + (i & 1);
	for(int i=1, u, v; i<=m; i++) {
		scanf("%d%d", &u, &v);
		e[u] |= (1 << v-1);
		e[v] |= (1 << u-1);
	}
	dfs(0, 0, 0, 0, (1<<n)-1);

	for(int i=1; i<=n; i++)
		if(s >> i-1 & 1) printf("%d ", i);
	printf("\n");
	return 0;
}
```

---

## 作者：kczno1 (赞：7)

${26 \choose 13}$只有$10^7$，所以直接搜索出所有情况即可。


加入一个点时，通过位运算直接算出他的贡献。


($bzoj$上$ac$,洛谷貌似没$spj$)

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=26,U=1<<13;
int n,m;
ui lk[N];
int cnt[U];
int ans,ansu;

int Cnt1(ui x)
{
    return cnt[x&U-1]+cnt[x>>13];
}
void dfs(int x,ui u1,ui u2,int c1,int c2,int sum)
{
    if(x==n)
    {
        if(sum>ans){ans=sum;ansu=u1;}
        return ;
    }
    if(c1<m)dfs(x+1,u1+(1<<x),u2,c1+1,c2,sum+Cnt1(lk[x]&u1));
    if(c2<m)dfs(x+1,u1,u2+(1<<x),c1,c2+1,sum+Cnt1(lk[x]&u2));
}

int main()
{
    freopen("1.in","r",stdin);
    cin>>n>>m;
    if(n==2)
    {
        printf("%d",1);
        exit(0);
    }
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        --x;--y;
        lk[x]|=1<<y;lk[y]|=1<<x;
    }
    rep(i,1,U-1)cnt[i]=cnt[i-(i&-i)]+1;
    ans=-1;m=n/2;
    dfs(1,1,0,1,0,0);
    rep(i,1,n)
    if(ansu&(1<<i-1))printf("%d ",i);
}
```

---

## 作者：Juan_feng (赞：5)

## 小蒟蒻来水一篇退火题解

一看点这么少， 直接就上退火了qaq  稍微调了调参就过了qwqwq

做法就是先直接把点分成两份， 统计一下答案。  然后每次随机两个点交换， 在比较一下新答案和旧答案拿个更优， 以此来决定是直接接受还是概率性接受。 就没啥了？

另外有一点： 更新答案的时候， 我是直接扫了一遍所有的边，这样很明显效率不够高， 但是足以通过本题（最优解第一页）  那就留给大家作为思考内容吧qaq

那么代码如下：
```
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define maxn 101
#define maxm 2002
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, t, x, y, z, mid, ans;
int a[maxn], b[maxn][maxm], pl[maxn], ss[maxn], l[maxm], r[maxm]; 
double delta = 0.996;

int pd(int x) {
    return pl[x] > mid;
}

void SA() {
    double t = 1926.0;
    while(t > 1e-14) {
        int qwq = rand()%mid+1;
        int qaq = rand()%mid+mid+1;

        swap(pl[a[qwq]], pl[a[qaq]]);
        swap(a[qwq], a[qaq]);
        
        int nans = 0;
        
        FOR(i, 1, m) {
            if(pd(l[i]) ^ pd(r[i]))
          	  ++nans;
        }
        int de = nans - ans;
        if(de < 0) {
            ans = nans;
            FOR(i, 1, mid)
              ss[i] = a[i];
        }
        else if(exp(-de/t)*RAND_MAX <= rand()){
            swap(pl[a[qwq]], pl[a[qaq]]);
            swap(a[qwq], a[qaq]);
        }
        t *= delta;
    }
}

int main() {
    srand(71806291);
    srand(rand());
    srand(rand());
    scanf("%d%d", &n, &m);
    mid = n/2;
    FOR(i, 1, n)
      a[i] = i, pl[i] = i;
    //pl代表编号为i的点的位置   a代表i位置的点的编号 
    FOR(i, 1, n/2)
      ss[i] = i;
    FOR(i, 1, m) {
        scanf("%d%d", &l[i], &r[i]);
        if(pd(l[i]) ^ pd(r[i]))
          ++ans;
    }

    int st = 25;
    while(st--) {
        SA();
    }
    
    FOR(i, 1, n/2)
      printf("%d ", ss[i]);
}
```

---

## 作者：shight (赞：3)

看到题解区的大佬们要么退火要么状压，本蒟蒻觉得有点懵，于是果断掏出了永恒不灭的真理：

### 暴力dfs

首先我们知道由于 n = 26 ，我们可选的方案总数并不多。（实测大概在 1e7 左右。）

那么我们只需要搞一手爆搜统计所有方案的答案就可以轻松解决问题。

但这里需要注意的一点是，我们应在 dfs 的过程中，每放入一个数就计算它的贡献。这样可以做到最优性剪枝并减少一定常数。

（本蒟蒻觉得最后统一结算贡献的话就不能搞最优性剪枝了所以应该过不了，但有兴趣的大佬可以去试试这样能不能过。）

代码如下：
```cpp
//Talking to the moon
#include <bits/stdc++.h>
#define N 1000010
#define M 2000010
#define int long long
#define int_edge int to[M],val[M],nxt[M],head[N],cnt=0;
using namespace std;
int n,m,q1[101],q2[101],p[101],e[101][101],ans=2147483647;
//q1:集合1中的点 q2:集合2中的点 p：存答案点 ans：当前最小答案 e：邻接矩阵存边（这里不用邻接表的原因一是没必要，二是如果使用邻接表那么将很难动态维护新点贡献） 
int read(){
	int fu=1,ret=0;char ch;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')fu*=-1;
	for(;isdigit(ch);ch=getchar())ret=(ret<<1)+(ret<<3)+ch-'0';
	return ret*fu;
}
void dfs(int nw,int l1,int l2,int sum){//nw:当前要把第几个点放入集合 l1：集合1的数的个数 l2:集合2的数的个数 sum：当前跨集合的边 
	if(sum>=ans)return;//最优性剪枝 
	if(nw>n){//更新答案 
		for(int i=1;i<=l1;i++)p[i]=q1[i];
		ans=sum;
		return;
	}
	if(l1<n/2){//动态统计放入集合1时的贡献 
		int tmp=0;q1[l1+1]=nw;
		for(int i=1;i<=l2;i++)
			if(e[nw][q2[i]])tmp++;
		dfs(nw+1,l1+1,l2,sum+tmp);
	}
	if(l2<n/2){//动态统计放入集合2时的贡献
		int tmp=0;q2[l2+1]=nw;
		for(int i=1;i<=l1;i++)
			if(e[nw][q1[i]])tmp++;
		dfs(nw+1,l1,l2+1,sum+tmp);
	}
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		e[x][y]=e[y][x]=1;
	}
	dfs(1,0,0,0);
	for(int i=1;i<=n/2;i++)printf("%lld ",p[i]);
	return 0;
}

```


---

## 作者：Mine_King (赞：2)

这题我们首先考虑将所有点都放在一个集合里，然后取出 $\frac{n}{2}$ 个点放入另一个集合。这一步骤可以用 dfs 来实现。  

**先不考虑时间**，我们可以想到做 $\dfrac{n}{2}$ 次，每次取出一个在原集合中的点放入第二个集合中，然后计算贡献，贡献为取出的这个点与原集合的点的连边数减去与另一个集合的点的连边数。  
但是这个算法太慢了，无法通过此题。

考虑优化上面的那个算法，从数据范围入手，发现 $n \le 26$，可以使用状压，将点 $i$ 的连边压缩成一个二进制数 $g_i$，第 $j$ 位为 $1$ 代表 $i$ 与 $j$ 有边。我们再将两个集合压缩成二进制数 $S_1$ 和 $S_2$，第 $i$ 位为 $1$ 代表点 $i$ 在集合中。  
可以发现的，$g_i$ 与 S_1 做 `&` 操作得到的结果就是点 $i$ 与 $S1$ 中的点的连边数，$g_i$ 与 $S_2$ 同理。  
如果我们能预处理出所有需要用到的数在二进制下 $1$ 的个数，则可以大大优化这个算法。  
可惜，这个数最大有 $2^{26}=67108864$，太大了，预处理不来。  
但是我们可以分段，将它分为前 $13$ 位和后 $13$ 位，那么只需要预处理出 $2^{13}=8192$ 即可。

但是出题人太毒瘤了，这样优化后依然会大面积 TLE，我们还需要对 dfs 进行剪枝。  
如果上一个取出的数是 $i$，那么如果再去取 $1$~$i-1$ 中的数，与之前取 $1$~$i-1$ 中的数，再取 $i$是同一个方案。也就是说，取数的顺序不会影响结果。那么，若前一次取 $x$，则下一次只要在 $x+1$~$n$ 中取，可以砍掉许多无用的方案。

加上上面两个优化，即可通过此题。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,ans=1e9;
int S,S1,S2,g[30];
int one[1<<13];
int Calc(int _S)
{
	return one[_S>>13]+one[_S^((_S>>13)<<13)];
}
void dfs(int p,int now,int sum)
//p是上一个取的点，now是当前S2中点的个数，sum为贡献
{
	if(now==n/2+1)
	{
		if(sum<ans) ans=sum,S=S1;
		return ;
	}
	for(int i=p+1;i<=n;i++)
		if(S1&(1<<(i-1)))
		{
			S1^=1<<(i-1);
			S2|=1<<(i-1);
			dfs(i,now+1,sum+Calc(g[i]&S1)-Calc(g[i]&S2));
			S1|=1<<(i-1);
			S2^=1<<(i-1);
		}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<(1<<13);i++)
		one[i]=one[i>>1]+(i&1);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u]|=1<<(v-1);
		g[v]|=1<<(u-1);
	}
	S1=(1<<n)-1;
	dfs(0,1,0);
	for(int i=1;i<=n;i++)
		if(S&(1<<(i-1))) printf("%d ",i);
	return 0;
}
```

这里稍微提一下，有一种错误的方法是 dfs 每次枚举一个点选获不选，然后去抉择下一个点，这样的复杂度是 $O(2^n)$ 的，是无法通过此题的。

---

## 作者：堇墨浮华 (赞：2)

在绞尽脑汁地思索转移方程无果后果断使用DFS。。。

预处理出每个集合及成员个数，然后用DFS进行搜索，用s1和s2表示两个子集，每次把现在正在处理的这个点加入到s1里，再从s2中删去。

dfs记录现在所在结点，已经加入s1集合的点数，以及两个子集之间的连边数，当点数==n/2时，比较连边数和ans的大小，用print记录下现在（当连边数<ans时）的s1

最后输出时看一下print是否包含结点1

开数组时小心点，别~~傻乎乎地~~开[1<<26]，那样会爆哒，只要开[1<<13]就够啦

接下来是~~可爱的~~代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int edge[30],ans,print,s1,s2;
int cnt[(1<<13)+10];
int get(int x){
	return cnt[x>>13]+cnt[x-((x>>13)<<13)];
}//向外连的边数 
void dfs(int id,int all,int sum){//DFS大法好 
	if (all==n/2){
		if (sum<ans){
			ans=sum;
			print=s1;
		}//更新答案 
		return;
	}
	for (int i=id+1;i<=n;i++){
		int get1=get(edge[i]|s1),get2=get(edge[i]|s2);//运算或,统计向外连接的边数 
		s1|=(1<<(i-1));//添加到集合s1
		s2^=(1<<(i-1));//把这个结点从集合s2删除 
		dfs(i,all+1,sum+get1-get2);
		s1^=(1<<(i-1)); 
		s2|=(1<<(i-1));//回溯 
	}
}
int main(){
	scanf ("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int x,y;
		scanf ("%d%d",&x,&y);
		edge[x]|=(1<<(y-1));
		edge[y]|=(1<<(x-1));
	}
	for (int i=0;i<=1<<13;i++)
		for (int j=13;j>=0;j--)
			if (i&(1<<j))
				cnt[i]++;//预处理出1的个数(也就是集合内成员个数)
	dfs(0,0,0);
	if (print&(1<<1)){
		for (int i=1;i<=n;i++)
			if (print&(1<<(i-1)))
				printf ("%d ",i);
	}
	else {
		for (int i=1;i<=n;i++)
			if (!(print&(1<<(i-1))))
				printf ("%d ",i);
	}//输出~ 
	return 0;
}

```

---

## 作者：andyli (赞：1)

除了 dfs 枚举状态外，还可以直接循环利用 `__builtin_popcount` 枚举 $\left[0, 2^n\right)$ 中二进制下 $1$ 的个数为 $\dfrac{n}{2}$ 的状态，此时 $S$ 中的 $1$ 表示一个集合中的点，$\sim S$ 中前 $n$ 位的 $1$ 表示另一集合中的点，对于每个点 $u$ 计算与 $u$ 有边连接的点集和 $S$ 或 $\sim S$ （取决于 $u$ 是否在 $S$ 中）按位与后 $1$ 的个数，累加计算贡献。

```cpp
int main() {
    dR(int, n, m);
    std::vector<int> e(n);
    while (m--) {
        dR(int, u, v), u--, v--;
        e[u] |= 1 << v;
        e[v] |= 1 << u;
    }
    int ans = 0, v = 1e9;
    for (int S = 0; S < (1 << n); S++)
        if (__builtin_popcount(S) == n >> 1) {
            int c = 0;
            for (int i = 0; i < n; i++)
                if (S & (1 << i))
                    c += __builtin_popcount(~S & e[i]);
                else
                    c += __builtin_popcount(S & e[i]);
            if (c < v)
                v = c, ans = S;
        }
    std::vector<int> a;
    for (int i = 0; i < n; i++)
        if (ans & (1 << i))
            a.push_back(i + 1);
    io.displayArray(a);
    return 0;
}
```

---

## 作者：AuCloud (赞：1)

# 模拟退火

蒟蒻的第二道模拟退火题……

思路很简单：每次随机交换mid前和mid后两个点，然后判断是否为最优，是则直接取，否则概率取。

初温T貌似$10^3$到$10^5$都可以（再小没敢试

$ΔT$我喜欢$0.996$

但是，以上还会WA，还要多次退火

~~我绝对不会告诉你我WA了之后直接大力50次就过了的~~

```cpp
#include <bits/stdc++.h>
#define EPS 1e-14
#define pd(x, y) ((pos[(x)] > mid) ^ (pos[(y)] > mid))
using namespace std;
double T, delT = 0.996;
int a[300], pos[300], s[300], fr[3000], to[3000];
int n, m, mid;
int main()
{
    cin >> n >> m;
    mid = n / 2;
    for(int i = 1; i <= n; i++)
        a[i] = pos[i] = i;
    for(int i = 1; i <= n / 2; i++)
        s[i] = i;
    int ans = 0;
    for(int i = 1; i <= m; i++)
    {
        cin >> fr[i] >> to[i];
        if(pd(fr[i], to[i])) ans++;
    }
    srand(time(NULL));
    int tim = 30;
    while(tim--)
    {
        for(T = 100000; T > EPS; T *= delT)
        {
//            printf("%.17f\n", T);
            int x = rand() % mid + 1;
            int y = rand() % mid + mid + 1;
            swap(a[x], a[y]);
            swap(pos[a[x]], pos[a[y]]);
            int now = 0;
            for(int i = 1; i <= m; i++)
            {
                if(pd(fr[i], to[i]))
                    now++;
            }
            if(now < ans)
            {
                ans = now;
                for(int i = 1; i <= n / 2; i++)
                {
                    s[i] = a[i];
                }
            }
            else if(exp((ans - now) / T) * RAND_MAX <= rand())
            {
                swap(a[x], a[y]);
                swap(pos[a[x]], pos[a[y]]);
            }
        }
    }
    sort(s + 1, s + n / 2 + 1);
    for(int i = 1; i <= n / 2; i++)
    {
        cout << s[i] << ' ';
    }
    return 0;
}


```

~~另：代码写累了，把注释那行删掉，运行一遍，看着那个T一点点降到0.0000000000001，还是很解压的~~

---

## 作者：梧桐灯 (赞：1)

juruo的我模拟退火又写错了QAQ

模拟退火虽然不是正解，但是确实这种题的骗分神器，具体来说一次退火的过程如下：

设置初温（我一般2万），末温（我一般1e-14)，温度变化量（我一般0.996）

然后while (T > ET) {…… T*=deltaT;}

过程是随机选两个集合的点并交换，算出新的ans，和原来ans比较。如果更优则更新答案并保存交换，如果不优则一定几率保存更改（一般写为若 exp(-abs (ans - nowans) / T) * MAX_RAND(即32767) <= rand ()则$\red{\text{撤销}}$更改

代码：
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef double D;
const int N = 29;
int n, m, c[N][N];
int a[N], last[N], ans = 1 << 30;

inline int cal () {
	int i, j, s = 0;
	for (i = 1; i <= m; ++i){
		for (j = m + 1; j <= n; ++j) s += c[a[i]][a[j]];
	}
	return s;
}

inline void work () {
	int i; for (i = 1; i <= m; ++i) last[i] = a[i];
	return ;
}

inline void SA () {
	D T = 20000, del = 0.996, ET = 1e-14;
	for (int i = 1; i <= n; ++i) a[i] = i;
	while (T > ET) {
		int x = rand () % m + 1;
		int y = m + rand () % (n - m) + 1;
		swap (a[x], a[y]);
		int t = cal ();
		if (t < ans) ans = t, work ();
		else if (exp ((ans - t) / T) * RAND_MAX <= rand ()) swap (a[x], a[y]);
		T *= del;
	}
	return ;
}

int main () {
	srand (多试几次，选适合自己的参数);
	REPEAT K srand (rand ()); K视自己情况而定
	scanf ("%d %d", &n, &m);
	int x, y; while (m--) {
		scanf ("%d %d", &x, &y);
		c[x][y] = c[y][x] = 1;
	}
	m = n >> 1;
	for (int i = 1; i <= n; ++i) a[i] = i, last[i] = i;
	ans = cal (); //初始情况
	int T = 75; while (T--) { //多跑几次SA，增大正确率
		SA ();
	}
	sort (last + 1, last + 1 + m);
	for (int i = 1; i < m; ++i) printf ("%d ", last[i]);
	printf ("%d\n", last[m]);
	return 0;
}
```

---

## 作者：红色OI再临 (赞：1)

给定一个n个点的无向图，要求将点集分成大小相等的两个子集，使两个子集之间的边数最少


因为是分成大小两个大小相等的子集，所以设s1,s2为两个集合

要找到一种情况使得在分成两部分的情况下相连的边数最少

我们可以预处理（总共一半的）每个状态内的 1 的个数

那么 `num[s>>13]+num[s−((s>>13)<<13)]` 即为连边数

那么dfs,每此用

` sum-getnum(s1&p[i])+getnum(s2&p[i])` 

即可得到边数



突然发现枚举子集可以这么写：

```
for(re x=1;x<1<<n;x++)
   s[x]=s[x-lowbit(x)]+1;                   
                      
```



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register int
#define ll long long
#define maxn 26
#define inf 0x3f3f3f3f
using namespace std;
int s1,s2,all;
int n,m,s[1<<maxn],p[maxn],ans=inf;
//p为一个点与之联通的点
int sum;
int ans1;
inline int lowbit(int x){
	return x&(-x);
}
//get边数
int getnum(int now){
	return s[now>>13]+s[now-((now>>13)<<13)];
}
void dfs(int x,int now,int sum){
//当前点，点集，边数总和
	if(now==n/2){
		if(sum<ans)ans=sum,ans1=s1;
		return;
	}
	//当前的总边数更新为sum−该点之前与s1的连边+该点之后与s2 的连边
	for(re i=x+1;i<n;i++){
		int sum1=getnum(p[i]&s1),sum2=getnum(p[i]&s2); //&取公共
		s1|=(1<<i);
		s2^=(1<<i);
		dfs(i,now+1,sum-sum1+sum2);
		s1^=(1<<i);
		s2|=(1<<i);
	}

}
int main(){
	scanf("%d%d",&n,&m);
	for(re i=0;i<1<<13;i++)
	{
		for(re j=0;j<13;j++){
			if(i&(1<<j))s[i]++;
		}
	}
	//for(re i=0;i<1<<13;i++)
	//printf("%d ",s[i]);
	for(re i=1;i<=m;i++){
		int a1,a2;
		scanf("%d%d",&a1,&a2);
		a1--,a2--;
		p[a1]|=(1<<a2);
		p[a2]|=(1<<a1);
	}		
	s2=(1<<n)-1;//先让一个集合等于所有
	dfs(-1,0,0);
	for(re i=0;i<n;i++)
	if(ans1&(1<<i))printf("%d ",i+1);
	return 0;
}
```


---

## 作者：Arghariza (赞：0)

[~~推销~~安利自己的模拟退火笔记![](https://啧.tk/doge)](https://www.cnblogs.com/Ender32k/p/15780847.html)

不会做，模拟退火好了。

一开始左边分一组右边分一组算出当前答案，每次随机两边两个点交换，然后暴力计算新的答案，看看是否转移就行了。能转移就记录当前分组情况，不能转移就给它交换回来，然后最后卡一下时间。

```cpp
#include <bits/stdc++.h>
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const double eps = 1e-14;
const double d = 0.996;
const int maxn = 114514;
int n, m, md, ans, p[maxn], u[maxn], v[maxn], as[maxn], t[maxn];

int chk(int x) { return p[x] > md; }
void solve() {
    double tp = 11451.4;
    while (tp > eps) {
    	// 随记两边的点
        int x = rand() % md + 1;
        int y = rand() % md + md + 1;
        // 交换计算答案
        swap(p[t[x]], p[t[y]]);
        swap(t[x], t[y]);
        int res = 0;
        for (int i = 1; i <= m; i++) res += (chk(u[i]) ^ chk(v[i]));
        if (res < ans) {// 一定能转移，记录答案
            ans = res;
            for (int i = 1; i <= md; i++) as[i] = t[i];
        } else if (exp((ans - res) / tp) < double(rand()) / RAND_MAX) {// 不能转移，去死
            swap(p[t[x]], p[t[y]]);
            swap(t[x], t[y]);
        }
        tp *= d;// 降温
    }
}

int main() {
    srand((unsigned)time(0));
    n = read(), m = read(), md = n / 2;
    // 处理初始情况
    for (int i = 1; i <= n; i++) p[i] = t[i] = i;
    for (int i = 1; i <= md; i++) as[i] = i;
    for (int i = 1; i <= m; i++) {
        u[i] = read(), v[i] = read();
        ans += (chk(u[i]) ^ chk(v[i]));
    }
    while (clock() / (1.0 * CLOCKS_PER_SEC) <= 0.98) solve();// 卡时
    for (int i = 1; i <= md; i++) write(as[i]), putchar(' ');
    return 0;
}
```

---

## 作者：Remake_ (赞：0)

随机化贪心艹过去了，时间卡的很精准。

具体思路就是初始时将$1$ ~ $\frac{n}{2}$的点划分成一个集合，另外的点归为另一个集合，之后每次随机选择这两个集合中的点进行交换。每次交换完了枚举所有边，看看边上的两个点在不在一个集合里，统计所有不在一个集合里的边就行了。最后专门用一个数组ans来统计最优解所对应的状态即可。

需要注意的点：

$1,$这题非常玄学，试了```
srand(19260817);```是过不了的，必须```
srand(rand());```才能过qwq。

$2,$一定要判断随机交换的点在不在一个集合内！如果在一个集合内的话，这次贪心就没啥用，因为答案肯定会和上次贪心的结果一模一样的，会大大增加冗余时间。

$3,$这题贼卡时间，所以我们就跟他硬卡，建议加上```
while ((double)clock() / CLOCKS_PER_SEC <= 0.95)```来保证在不超时的情况下，随机化贪心跑尽可能多的次数。

注意了这些点，不加火车头也能过qwq。

放一下代码awa：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, minn = 0x7fffffff, a[2002], b[2002], ans[15];
bool pos[30];
void tx()
{
    int cnt = 0, tot = 0;
    for (int i = 1; i <= m; i++)
        if (pos[a[i]] != pos[b[i]])
            ++cnt;
    if (cnt < minn)
    {
        minn = cnt;
        for (int i = 1; i <= n; i++)
            if (pos[i] == 1)
                ans[++tot] = i;
    }
}
int main()
{
    srand(rand());
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> a[i] >> b[i];
    for (int i = 1; i <= n / 2; i++)
        pos[i + n / 2] = 1;
    while ((double)clock() / CLOCKS_PER_SEC <= 0.95)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        while (pos[x] == pos[y])
            x = rand() % n + 1, y = rand() % n + 1;
        swap(pos[x], pos[y]);
        tx();
    }
    for (int i = 1; i <= n / 2; i++)
        cout << ans[i] << " ";
}
```


---

