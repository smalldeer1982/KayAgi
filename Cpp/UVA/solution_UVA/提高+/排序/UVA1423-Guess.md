# Guess

## 题目描述

给定一个数组： $a_1,a_2,a_3,\dots ,a_n$ 。

我们定义一个符号矩阵 $S_{i,j},i\le j$ ，代表 $a_i+a_{i+1}+\dots +a_j$ 的符号为 $+,-,0$ 三个中的一种。

你需要写一个程序，输入这个 $n\times n$ 的半矩阵，输出原来的数列。如果有多解，输出一组即可。

数据总共有T组。

## 说明/提示

$1\le n \le 10$ 

 $-10\le a_i \le 10$ 

Translated by @dblark

# 题解

## 作者：reyik (赞：10)

开门见山。这道题，是一道拓扑排序。

拓扑排序的关键是找出节点和有向边。

经过分析，节点就是$1$~$n$个数的前缀和，有向边就是前缀和之间的大小关系。

主要问题是，如何建起这条有向边？

我们的方法是：

如果当前的这个点为负号，那么他所对应的行列$i$,$j$,就建起一条节点为$i-1$,$j$的有向边。

如果当前的这个点为正号，那么他所对应的行列$i$,$j$,就建起一条节点为$j$,$i-1$的有向边。

然后就是前缀和预处理+最经典的拓扑排序

最后就是代码：

```
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
bool vis[205];
int head[205],degree[205]//入度数组;
int cnt,num,n,t;
int a[205],sum[205]//前缀和;
string s;
struct edgenode
{
    int to,next;
} edge[205];//边
void init()//初始化
{
    cnt=0;
    memset(vis,false,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(degree,0,sizeof(degree));
    for(int i=0;i<=n;i++)
        sum[i]=10;
}
void add(int u,int v)//邻接表存储
{
    degree[v]++;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void topu(int n)//经典的拓扑排序，每次找入度为0的,不用多解释
{
    queue<int>q;
    num=0;
    for(int i=0;i<=n;i++)
    {
        if(!degree[i]&&!vis[i])
            {
                q.push(i);
                vis[i]=1;
            }
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int k=head[u];k!=-1;k=edge[k].next)
        {
            degree[edge[k].to]--;
            sum[edge[k].to]=sum[u]-1;
            if(!degree[edge[k].to])
                {
                    q.push(edge[k].to);
                    vis[edge[k].to]=1;
                }
        }
    }
}
int main()
{
    cin>>t;
    while(t--)
    {
        init();
        memset(a,0,sizeof(a));
        cin>>n;
        cin>>s;
        int k=0;
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)//建边，详见上文
        {
            if(s[k]=='+')
                add(j,i-1);
            else if(s[k]=='-')
                add(i-1,j);
            k++;
        }
        topu(n);
        for(int i=1;i<=n;i++)
            a[i]=sum[i]-sum[i-1];
       for(int i=1;i<n;i++)
        cout<<a[i]<<" ";
       cout<<a[n]<<endl;
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：6)

这道题是一道很明显的拓扑排序。

不过，首先需要对此题进行预处理。

通过用前缀和算出每个位置的sum值。然后，用queue进行经典的拓扑排序。

下附代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>//头文件
using namespace std;
int T,n,a[20],sum[20];
char s[100];
bool map[20][20];
inline void top()
{
	queue <int> q;
	for(int i=0; i<=n; i++) if (!sum[i]) q.push(i);//入度为0，则加入队列
	int cnt=0;
	while(!q.empty())
	{
		int tmp=q.front();
		q.pop();
		cnt++;
		for(int i=0; i<=n; i++)
			if (map[tmp][i])//去掉与此点有联系的边
			{
				sum[i]--;
				if (!sum[i])
				{
					q.push(i);
					a[i]=cnt;
				}
			}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(sum,0,sizeof(sum));
		memset(map,0,sizeof(map));
		memset(a,0,sizeof(a));//初始化
		scanf("%d",&n);
		scanf("%s",s);
		int cnt=0;
		for(int i=1; i<=n; i++)
		{
			for(int j=i; j<=n; j++)
			{
				if (s[cnt]=='+')
				{
					map[i-1][j]=1;
					sum[j]++;
				}
				if (s[cnt]=='-')
				{
					map[j][i-1]=1;
					sum[i-1]++;
				}
				cnt++;
			}
		}//预处理
		top();//拓扑
		for(int i=1; i<n; i++)
		{
			printf("%d ",a[i]-a[i-1]);
		}//输出
		printf("%d\n",a[n]-a[n-1]);
	}
	return 0;
}
```

---

## 作者：aleph_blanc (赞：2)

私以为，此题可以是一道不错的拓扑排序板题。

题意：给定一个 $n\times n$ 的半矩阵 $S$，矩阵中每个位置的值 $S_{i,j}$ 表示数列 $\text{a}$ 从 $i$ 到 $j$ 的区间和的正负关系，分 $+,-,0$ 三种。

求解一个数列的最简便的方法就是先知道它的前缀和，那么我们把这题转换一下:

$S_{i,j}=+$,则 $sum[j]-sum[i-1]>0$，$sum[j]>sum[i-1]$，可以认为 $j$ 的优先级比 $i-1$ 高，从 $j$ 向 $i-1$ 连一条边，相应地，$i-1$ 入度加一。

$S_{i,j}=-$ 则与上面相反。

$S_{i,j}=0$，则不连边。

这么转换，就可以确定 $1$ 到 $n$ 的前缀和的大小关系，当前入度为零的点优先级一定最大，若有多个则顺着来就行。于是把建出来的图跑一边拓扑排序就可以了。

```cpp
#include <bits/stdc++.h>

#define N 20

using namespace std;

template <typename T>
inline int read (T &a) {
	T x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) {
		(ch == '-') and (f = 0);
		ch = getchar ();
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch xor '0');
		ch = getchar ();
	}
	return a = f ? x : -x;
}
template <typename T, typename ...A>
inline void read (T &t, A &...a) {
	read (t), read (a...);
}
template <typename T>
inline void print (T x) {
	if (x < 0) putchar ('-'), x = -x;
	if (x > 9) print (x / 10);
	putchar (x % 10 + '0');
}

char s[110];
int ind[N], p[N][N], tot; // 入度，存图，当前的矩阵位置
int t, sum[N], ans[N], n;
bool vis[N];

void tops () { // 经典拓扑排序，每次找入度为零的点，
	int num = 10, cnt = 0;
	while (cnt <= n) {
		memset (vis, 0, sizeof vis);
		for (int i = 0; i <= n; i++) {
			if (ind[i]) continue;
			sum[i] = num;
			ind[i]--, cnt++;
			vis[i] = 1;
		} // 找点
		for (int i = 0; i <= n; i++) {
			if (! vis[i]) continue;
			for (int j = 0; j <= n; j++) {
				if (p[i][j]) ind[j]--;
			} // 将与处理了的点相连的点的度数减一
		}
		num--;
	}
}

signed main () {
	read (t);
	while (t--) {
		memset (ind, 0, sizeof ind);
		memset (p, 0, sizeof p);
		read (n), scanf ("%s", s);
		tot = 0;
		for (int i = 1; i <= n; i++) { // 遍历矩阵，建图
			for (int j = i; j <= n; j++) {
				char c = s[tot++];
				if (c == '+') {
					p[j][i - 1] = 1;
					ind[i - 1]++;
				} else if (c == '-') {
					p[i - 1][j] = 1;
					ind[j]++;
				}
			}
		}
		tops ();
		for (int i = 1; i <= n; i++) {
			printf ("%d%c", sum[i] - sum[i - 1], " \n"[i == n]);
		}
	}
}
```



---

## 作者：happybob (赞：1)

## 题意

给定一个半邻接矩阵 $S_{i,j}$，每个 $S_{i,j}$ 表示 $\sum_{x=i}^j a_x$ 的正负性，有正数，负数，$0$ 三种可能，现在给定矩阵 $S$，求任意一个可行的 $a$ 序列，其中 $-10 \le a_i \le 10$。

## 解法

据说正解是拓扑排序，但是注意到 $n \le 10$，那么其实爆搜加剪枝可以过。

考虑如何剪枝，剪枝其实就是判定 $a_i$ 的值时只需要枚举所有 $S_{x,i}$，其中 $x \le i$。因为所有 $S_{x, k}(x <i, k < i)$ 都已经在前面的搜索中判定过。

上代码：

```cpp
#pragma GCC optimize("-Ofast")
#pragma GCC target("avx,sse,sse2,sse3,sse4")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 15;

int t, n;
char c[N][N];
int a[N];

inline int read()
{
	register char ch = getchar();
	register int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline bool dfs(int dep)
{
	if (dep > n)
	{
		for (register int i = 1; i <= n; i++)
		{
			write(a[i]);
			putchar(' ');
		}
		return true;
	}
	register int sum = 0;
	for (register int i = 1; i < dep; i++) sum += a[i];
	for (register int i = -10; i <= 10; i++)
	{
		a[dep] = i;
		sum += i;
		register int sumx = 0;
		for (register int j = 1; j <= dep; j++)
		{
			register int ex = sum - sumx;
			if ((ex < 0 && c[j][dep] != '-') || (ex == 0 && c[j][dep] != '0') || (ex > 0 && c[j][dep] != '+'))
			{
				goto Nxt;
			}
			sumx += a[j];
		}
		if (dfs(dep + 1)) return true;
	Nxt:
		sum -= i;
	}
	return false;
}

int main()
{
	t = read();
	while (t--)
	{
		n = read();
		for (register int i = 1; i <= n; i++)
		{
			for (register int j = i; j <= n; j++) cin >> c[i][j];
		}
		dfs(1);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

**差分约束大法好！！！**

可维护 $1\le n\le 5\times 10^3$ 的数据。

# 题目大意

有一个长度为 $n$ 的整数数列 $a_1, a_2, \cdots, a_n$。

定义 $s_{i,j} = a_i + a_{i+1} + \cdots + a_j$。

你现在只知道所有 $s_{i,j}$ 的符号，请恢复一个合法的数列，或指出不存在这样的数列。

# 题目分析

维护前缀和数组 $sum[j]$ 表示 $\sum\limits_{i=1}^ja[i]$，因此 $s[i,j]$的正负性可以转换为 $sum[j]-sum[i-1]$ 的正负性。

来分析一下：

当 $sum[j]-sum[i-1]>0$ 时，有 $sum[j]-1\ge sum[i-1]$，所以可以连边 $j\to i-1$，边长为 $-1$。

当 $sum[j]-sum[i-1]<0$ 时，有 $sum[j]\le sum[i-1]-1$，所以可以连边 $i-1\to j$，边长也为 $-1$。

当 $sum[j]-sum[i-1]=0$ 时，有 $sum[j]\ge sum[i-1]$ 或 $sum[j]\le sum[i-1]$，边长为 $0$。

我们再造一个超级源点 $n+1$，连边 $n+1\to i,i\in[0,n]$，边长为 $0$ 即可。

最后按照连出来的边构成的图跑最短路判断负环，一组解即为 $dis_1-dis_0,dis_2-dis_1,\cdots,dis_n-dis_{n-1}$。

# 代码

```cpp
//2022/4/5
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <queue>
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int N = 105;
struct Gragh {
	int v,w,nxt;
} gra[N * N];
int head[N],cnt[N],dis[N];
bool in_que[N];
char a[N][N];
int n,idx;
inline void add(int u,int v,int w) {
	gra[++ idx].v = v,gra[idx].w = w,gra[idx].nxt = head[u],head[u] = idx;
}
inline bool spfa(int st) {
	mst(dis,0x3f),mst(in_que,false),mst(cnt,0);
	queue<int>q;
	q.push(st);
	in_que[st] = true,cnt[st] = 1,dis[st] = 0;
	while (!q.empty()) {
		int u = q.front();q.pop();
		in_que[u] = false;
		for (register int i = head[u];i;i = gra[i].nxt) {
			int v = gra[i].v,w = gra[i].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!in_que[v]) {
					in_que[v] = true,cnt[v] ++;
					q.push(v);
					if (cnt[v] == n + 1) return true;
				}
			}
		}
	}
	return false;
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	int T = read();
	while (T --) {
		scanf("%d",&n);
		for (register int i = 1;i <= n; ++ i) {
			scanf("%s",a[i] + 1);
		}
		idx = 0;
		mst(head,0),mst(gra,0);
		//这里的右边界 j 和上面分析的不同 
		for (register int i = 1;i <= n; ++ i) {
			for (register int j = 1;j <= n - i + 1; ++ j) {
				/*
				sum[i + j - 1] - sum[i - 1] > 0 
				sum[i + j - 1] - 1 >= sum[i - 1]
				i + j - 1 -> i - 1
				*/
				if (a[i][j] == '+') add(i + j - 1,i - 1,-1);
				/*
				sum[i + j - 1] - sum[i - 1] < 0
				sum[i + j - 1] <= sum[i - 1] - 1
				i - 1 -> i + j - 1 
				*/
				else if (a[i][j] == '-') add(i - 1,i + j - 1,-1);
				/*
				sum[i + j - 1] - sum[i - 1] = 0
				sum[i + j - 1] <= sum[i - 1]
				sum[i + j - 1] >= sum[i - 1]
				*/
				else if (a[i][j] == '0') add(i + j - 1,i - 1,0),add(i - 1,i + j - 1,0);
			}
		}
		for (register int i = 0;i <= n; ++ i) add(n + 1,i,0);
		if (spfa(n + 1)) puts("NO");
		else {
			puts("YES");
			for (register int i = 1;i <= n; ++ i) {
				cout << dis[i] - dis[i - 1] << " ";
			}
			enter;
		}
	}
	
	return 0;
}
```

---

## 作者：theStarMaster (赞：0)

## UVA1423 Guess
### 解题历程
- 考试时看完题后第一感觉是没读懂，然后做完其他题（写了暴力）又回来~~仔细研究~~了这个题终于读懂了，然后就认为这是一个构造题，但我直接选择了爆搜，写着写着又看了数据范围发现复杂度完全可以接受。然后就真的切了QAQ。所以不会的时候想想搜索似乎是个明智的做题策略。
### 题意：
- 首先输入的是区间和的正负和零的情况，需要找到一个序列使区间和满足要求。
### 分析
- 通过半矩阵我们可以容易的发现对角线上的符号是单点情况所以我们可以记录下来单点符号值通过乘法完成搜索的一个剪枝。
```cpp
for(int i = 1 ; i <= n ; ++ i)
for(int j = i ; j <= n ; ++ j)
{
            cin >> s[i][j] ;
            if(i == j)
            {
                if(s[i][j] == '-') f[i] = -1 ;
                else if(s[i][j] == '0') f[i] = 0 ;
                else if(s[i][j] == '+') f[i] = 1 ;
            }
}
```
- 接下来便是愉快的搜索过程：  
1.值域范围 $-10 \le a_i \le 10$ 又因为我们已记录了每个点的符号所以我们搜索值域的范围为 $0 \lt x \le 10$（相当于一个剪枝吧QAQ）每次加入一个值后我们必然要判断当前序列是否满足要求的情况，如果不满足了我们可以减去这一枝。如果找到一种满足的长度为 $n$ 的序列输出然后跳出搜索。
```cpp
inline void dfs(int nw , int sum[])
{
            if(flag == 1) return ;
            if(nw == n && check(sum , n))
            {
                for(int i = 1 ; i <= n ; ++ i) cout << sum[i] << ' ' ;
                flag = 1 ;
                return ;
            }
            if(nw == n) return ;
            if(f[nw + 1] == 0) sum[nw + 1] = 0 , dfs(nw + 1 , sum) ;
            else
            for(int i = 1 ; i <= 10 ; ++ i)
            {
                sum[nw + 1] = f[nw + 1] * i ;
                if(check(sum , nw + 1)) dfs(nw + 1 , sum) ; 
            }
}
```
2.对于判断当前序列是否满足情况我们直接 $n^2$ 判断就行。
```cpp
inline bool check(int c[] , int len)
{
            int sum[100] ;
            memset(sum , 0 , sizeof(sum)) ;
            for(int i = 1 ; i <= len ; ++ i) sum[i] = c[i] + sum[i - 1] ; 
            for(int i = 1 ; i <= len ; ++ i)
            for(int j = i + 1 ; j <= len ; ++ j)
            {
                if(s[i][j] == '-' && sum[j] - sum[i - 1] >= 0) return 0 ;
                if(s[i][j] == '+' && sum[j] - sum[i - 1] <= 0) return 0 ;
                if(s[i][j] == '0' && sum[j] - sum[i - 1] != 0) return 0;
            }
            return 1 ;
}
```
### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
inline int read()
{
            int x = 0 , f = 1 ;
            char ch = getchar() ;
            while(ch > '9' || ch < '0')
            {
                if(ch == '-') f = -1 ;
                ch = getchar() ;
            }
            while(ch >= '0' && ch <= '9')
            {
                x = (x << 1) + (x << 3) + (ch ^ 48) ;
                ch = getchar() ;
            }
            return x * f ;
}
char s[1001][1001] ;
int T , n , b[100] , f[100] ;
bool flag = 0 ;
int a[11] = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10} ;
inline bool check(int c[] , int len)
{
            int sum[100] ;
            memset(sum , 0 , sizeof(sum)) ;
            for(int i = 1 ; i <= len ; ++ i) sum[i] = c[i] + sum[i - 1] ; 
            for(int i = 1 ; i <= len ; ++ i)
            for(int j = i + 1 ; j <= len ; ++ j)
            {
                if(s[i][j] == '-' && sum[j] - sum[i - 1] >= 0) return 0 ;
                if(s[i][j] == '+' && sum[j] - sum[i - 1] <= 0) return 0 ;
                if(s[i][j] == '0' && sum[j] - sum[i - 1] != 0) return 0;
            }
            return 1 ;
}
inline void dfs(int nw , int sum[])
{
            if(flag == 1) return ;
            if(nw == n && check(sum , n))
            {
                for(int i = 1 ; i <= n ; ++ i) cout << sum[i] << ' ' ;
                flag = 1 ;
                return ;
            }
            if(nw == n) return ;
            if(f[nw + 1] == 0) sum[nw + 1] = 0 , dfs(nw + 1 , sum) ;
            else
            for(int i = 1 ; i <= 10 ; ++ i)
            {
                sum[nw + 1] = f[nw + 1] * i ;
                if(check(sum , nw + 1)) dfs(nw + 1 , sum) ; 
            }
}
signed main()
{
            freopen("guess.in" , "r" , stdin) ;
            freopen("guess.out" , "w" , stdout) ;
            T = read() ;
            while(T --)
            {
                n = read() ;
                srand(time(0)) ;
                flag = 0 ;
                memset(b , 0 , sizeof(b)) ;
                for(int i = 1 ; i <= n ; ++ i)
                for(int j = i ; j <= n ; ++ j)
                {
                    cin >> s[i][j] ;
                    if(i == j)
                    {
                        if(s[i][j] == '-') f[i] = -1 ;
                        else if(s[i][j] == '0') f[i] = 0 ;
                        else if(s[i][j] == '+') f[i] = 1 ;
                    }
                }
                dfs(0 , b) ;
                cout << '\n' ;
            }
            fclose(stdin) ; fclose(stdout) ;
            return 0 ;
}
```
完结撒花٩(๑>◡<๑)۶

---

## 作者：maomao9173 (赞：0)

[更好的阅读体验点击这里](https://www.cnblogs.com/maomao9173/p/10761374.html)

评分稍微有一点过分。。不过这个题目确确实实很厉害，对思维训练也非常有帮助。

按照套路，我们把矩阵中的子段和化为前缀和相减的形式。题目就变成了给定一些前缀和之间的大小关系，让你构造一组可行的数据。这个东西显然是传递闭包，但是如果仅仅传递闭包的话我们只能询问两两之间的关系，处理起来比较麻烦。有没有什么办法获取一个完整的顺序序列出来呢？显然是做一个拓扑排序就好啦~

但是问题来了。如果没有相等一切好说，现在有相等该咋玩？

注意到题目保证一定有一组可行解，我们可以先不表示相等的关系。（如果把$<=$的关系和$<$的关系混起来会乱的~环什么的也不好处理）先把不等关系列出来，求出大小顺序的拓扑序列。由于一定有可行解，所以如果两个数相等的话，受到其他条件制约后，它们一定还是相邻的。这里用并查集维护一下相等关系，查一查前后相等不相等就可以了。

我们初始维护的是一个顺着边的方向递增的数量关系，$DF
S$求出的拓扑序列数量关系是递减的。所以处理的时候如果前后$find$一样就赋一样的值，否则就是前面等于后面$+1/$后面等于前面$-1$。求出$Sum$数组之后原数列就有了。

（特判：手推可知不连通的子图不会对答案造成影响。不用特判。）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 10 + 5;

int T, n, sum[N], Set[N], vis[N]; char s[N * N];

vector <int> G[N], topo;

int find (int x) {
	return x == Set[x] ? x : Set[x] = find (Set[x]);
}

void dfs (int u) {
	vis[u] = true;
	for (int i = 0; i < (int)G[u].size (); ++i) {
		int v = G[u][i];
		if (!vis[v]) dfs (v); //题目保证有解 = 无环 
	}
	topo.push_back (u);
}

int main () {
//	freopen ("data.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> s; int k = 0;
		for (int i = 0; i < N; ++i) {
			Set[i] = i, G[i].clear ();
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				if (s[k] == '+') {//sum[j] > sum[i - 1]
					G[i - 1].push_back (j);
				}
				if (s[k] == '-') {//sum[j] < sum[i - 1]
					G[j].push_back (i - 1);
				}
				if (s[k] == '0') {
					Set[find (j)] = find (i - 1);//数值相等 -> 同一个集合中 
				}
				//x -> y : sum[x] < sum[y]
				k = k + 1;
			}
		}
		topo.clear ();
		memset (vis, 0, sizeof (vis));
		memset (sum, 0, sizeof (sum));
		for (int i = 0; i <= n; ++i) {
			if (!vis[i]) dfs (i); //简便的DFS拓扑排序23333 
		} 
		int zero_pos = -1;
		for (int i = 0; i < (int) topo.size (); ++i) {
			if (topo[i] == 0) {zero_pos = i; break;} 
		}
		//找到0，前面是负数后面是正数
		for (int i = zero_pos - 1; i >= 0; --i) {
			if (find (topo[i]) == find (topo[i + 1])) {
				sum[topo[i]] = sum[topo[i + 1]];//如果相等 -> 按照其他约束条件排出来也应该相邻 
			} else {
				sum[topo[i]] = sum[topo[i + 1]] + 1; 
			}
		} 
		for (int i = zero_pos + 1; i <= n; ++i) {
			if (find (topo[i]) == find (topo[i - 1])) {
				sum[topo[i]] = sum[topo[i - 1]];//如果相等 -> 按照其他约束条件排出来也应该相邻 
			} else {
				sum[topo[i]] = sum[topo[i - 1]] - 1; 
			}
		} 
		for (int i = 1; i <= n; ++i) {
			cout << sum[i] - sum[i - 1];
			if (i != n) cout << " ";
		}
		cout << endl;
	}
}
```

---

## 作者：Paolo_Banchero (赞：0)

这道题很容易转化成：
已知s[0],s[1]...s[n]的大小关系，求a[1],a[2]...a[n]的值
不要想直接转化得到数列a的大小关系，那样不好找。而已知s后，可以直接用s[n]-s[n-1]求a[n]；
并且只要让相邻的s相差为1，a的值的绝对值就不会超过10.
然后拓扑排序时先找到所有入度为0的点后，再进行“减度”。

不过要注意我们的s[0]一样也作为图中的一个点来参与计算，不能当做0 。。。

    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    int rd[11],tu[11][11],s[11],aa[11];
    void topu(int n)
    {
        int oo=-10,flag=1;
        while(flag)
        {
            flag=0;
            queue<int>q;
            for(int i=0; i<=n; i++)
                if(rd[i]==0)
                {
                    rd[i]--;
                    flag=1;
                    q.push(i);
                    s[i]=oo;
                }
            oo++;
            while(!q.empty())
            {
                int t=q.front();
                q.pop();
                for(int i=0; i<=n; i++)
                    if(tu[t][i])
                        rd[i]--;
            }
        }
    }

    int main()
    {
        int t;
        scanf("%d",&t);
        while(t--)
        {
            memset(rd,0,sizeof(rd));
            memset(tu,0,sizeof(tu));
            int n;
            scanf("%d",&n);
            for(int i=1; i<=n; i++)
                for(int j=i; j<=n; j++)
                {
                    char a;
                    scanf(" %c",&a);
                    if(a=='+')
                        tu[i-1][j]=1,rd[j]++;
                    else if(a=='-')
                        tu[j][i-1]=1,rd[i-1]++;
                }
            topu(n);
            for(int i=1; i<n; i++)
            {
                aa[i]=s[i]-s[i-1];
                printf("%d ",aa[i]);
            }
            printf("%d\n",s[n]-s[n-1]);
        }
        return 0;
    }


---

