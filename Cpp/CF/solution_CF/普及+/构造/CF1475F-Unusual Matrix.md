# Unusual Matrix

## 题目描述

给你两个 $n\times n$ 的01矩阵，你可以进行如下两种操作：

- 垂直xor：选中一列，将这一列的每个元素分别进行xor
- 水平xor：选中一行，将这一行的每个元素分别进行xor

给定 $a,b$ 两个矩阵，问你 $a$ 是否可以在进行有限次操作后变为 $b$

例如：
$$
a=\begin{pmatrix} 1 & 1 & 0 \\ 0 & 0 & 1 \\ 1 & 1 & 0 \end{pmatrix},b=\begin{pmatrix} 0 & 0 & 0 \\ 0 & 0 & 0 \\ 0 & 0 & 0 \end{pmatrix}
$$
先使第一行进行水平xor：
$$
a=\begin{pmatrix} 0 & 0 & 1 \\ 0 & 0 & 1 \\ 1 & 1 & 0 \end{pmatrix}
$$
再使第三行进行水平xor：
$$
a=\begin{pmatrix} 0 & 0 & 1 \\ 0 & 0 & 1 \\ 0 & 0 & 1 \end{pmatrix}
$$
最后使第三列进行垂直xor即可

## 样例 #1

### 输入

```
3
3
110
001
110

000
000
000
3
101
010
101

010
101
010
2
01
11

10
10```

### 输出

```
YES
YES
NO```

# 题解

## 作者：Cutest_Junior (赞：7)

## 题解 CF1475F 【Unusual Matrix】

### 题意

+ 给出两个 $n\times n$ 的 01 矩阵；
+ 每次可以对第一个矩阵某一行或某一列全部元素异或，判断多次操作后是否能使之变为第二个矩阵。
+ 多组数据，$n\le1000$。

### 解法

首先想到两个矩阵异或，题目就变成把一个新矩阵改为全是 $0$ 的矩阵。

考虑先把第 $2$ 行到第 $n$ 行水平异或，全部改到和第 $1$ 行一样，然后垂直异或。

对于任意一行，能水平异或到和第 $1$ 行一样，当且仅当原来就一样或水平异或一次后一样（水平异或两次相当于没有操作，更多次同理）。

思维难度不高，代码也很好写，我 Virtual participation 的时候就过了。

### 代码

```cpp
#include <cstdio>
 
using namespace std;
 
const int N = 1005;
 
char map1[N][N];
char map2[N][N];
 
int arr[N][N];
 
void run() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", map1[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%s", map2[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			arr[i][j] = (map1[i][j] - '0') ^ (map2[i][j] - '0');
		}
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= n; ++j) {
			if ((arr[i][j] ^ arr[1][j]) != (arr[i][1] ^ arr[1][1])) {
				printf("NO\n");
				return;
			}
		}
	}
	printf("YES\n");
	
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：jianhe (赞：4)

很容易想到，若要求转化成一个全为 $0$ 的矩阵会简单很多。只要将每一行转化成与第一行一样即可。

因此我们考虑到异或的性质：**两个相同的数异或后得 $0$。**

因此问题可以转化为：使两个矩阵异或后，元素全为 $0$。

然后就可以做了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1010;
ll T,n,p[N][N];
string a[N],b[N];
bool flag;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;flag=1;
		for(int i=1;i<=n;i++) cin>>a[i],a[i]=" "+a[i];
		for(int i=1;i<=n;i++) cin>>b[i],b[i]=" "+b[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				p[i][j]=(a[i][j]-'0')^(b[i][j]-'0');
		for(int i=2;i<=n&&flag;i++)
			for(int j=2;j<=n&&flag;j++)
				if((p[1][j]^p[i][j])!=(p[1][1]^p[i][1])) cout<<"NO\n",flag=0;
		if(flag) cout<<"YES\n";
	}
	return 0;
}

```

---

## 作者：Aisaka_Taiga (赞：3)

发现从 A 矩阵到 B 矩阵的步骤，就相当于把 A 和 B 两个矩阵对应的两个数异或起来得到的新矩阵全变成 $0$。

因为要把 A 变成 B，此时 A 和 B 对应的两个数异或起来得到的数全是 $0$，所以可以把未改变的两个矩阵对应的两个数异或得到的新矩阵全通过行列变化成为 $0$，也就相当于使 A 矩阵变化成 B 矩阵了。

我们得到新矩阵后目标是全变成 $0$，而异或一个数偶数次就相当于没有异或，奇数次就相当于只异或一次，所以我们考虑 2-SAT。

我们设 $i$ 表示第 $i$ 行进行变化，$i+n$ 表示第 $i$ 列变化，$i+2n$ 表示第 $i$ 行不变化，$i+3n$ 表示第 $i$ 列不变化。

1. 如果新矩阵当前点是 $0$ 说明不需要异或，只能行列都变化或者都不变化，所以连 $i\to j+n,j+n\to i,i+2n\to j+3n,j+3n\to i+2n$。

2. 如果新矩阵当前点是 $1$ 说明行列只能变化一个，所以连 $i\to j+3n,j+3n\to i,i+2n\to j+n,j+n\to i+2n$。

然后跑一遍 tarjan 判一下是否有解输出即可。

code:

```cpp
#include<bits/stdc++.h>
#define N 4000100
#define M 1100 
#define endl '\n' 
using namespace std;
string a[M],b[M];
struct sb{int u,v,next;}e[N];
int n,t,low[N],dfn[N],tim,sd[N],vis[N],cnt,head[N],stk[N],top,flag;
inline void add(int u,int v){e[++cnt].v=v;e[cnt].next=head[u];head[u]=cnt;} 
inline void qk(){flag=cnt=tim=0;for(int i=1;i<=4*n;i++)head[i]=low[i]=dfn[i]=vis[i]=sd[i]=0;}
inline void tarjan(int x)
{
	low[x]=dfn[x]=++tim;vis[x]=1;stk[++top]=x;
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].v;
		if(!dfn[v])tarjan(v),low[x]=min(low[x],low[v]);
		else if(vis[v])low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x])
	{
		int y;
		while(1)
		{
			y=stk[top--];
			sd[y]=x;
			vis[y]=0;
			if(x==y)break;
		}
	}
}
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		qk();
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		for(int i=1;i<=n;i++)
		{
		    for(int j=1;j<=n;j++)
		    {
		    	int c=(a[i][j-1]-'0')^(b[i][j-1]-'0');
		    	if(c==1)
		    	{
		    		add(i,j+3*n);//i行^,i+2n行不^,j+n列^,j+3n不^ 
		    		add(j+3*n,i);
		    		add(i+2*n,j+n);
		    		add(j+n,i+2*n);
				}
				else 
				{
					add(i,j+n);
					add(j+n,i);
					add(i+2*n,j+3*n);
					add(j+3*n,i+2*n);
				}
		    }
		}
		for(int i=1;i<=4*n;i++)if(!dfn[i])tarjan(i);
		for(int i=1;i<=2*n;i++)if(sd[i]==sd[i+2*n]){flag=1;break;}
		if(flag)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```

---

## 作者：yi_fan0305 (赞：3)

题目中要求将 $A$ 通过异或操作改成 $B$，那么可以看作将 $A$ 异或上一个 $C$ 让它变成 $B$，如果这个 $C$ 可以通过异或操作来变成一个全 $0$ 矩阵，那么就说明有解，否则无解，$C$ 可以由 $A$ 和 $B$ 异或得到。

每行每列最多只能异或一次，当 $C(i, j) = 1$ 时，要么第 $i$ 行异或，第 $j$ 列不异或，要么第 $j$ 列异或，第 $i$ 行不异或；若 $C(i, j) = 0$，则要么第 $i$ 行、第 $j$ 列都异或，要么都不异或，由此可以建边，转化成 2-SAT 问题，判断即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;

int T, n, cnt, tim, scc;
int a[N][N], b[N][N], c[N][N], x[N][2], y[N][2];
int dfn[N << 2], low[N << 2], lt[N << 2];
vector<int> son[N << 2], Stack;

void init() { // 初始化、标号
	cnt = tim = scc = 0;
	for (int i = 1; i <= n; ++ i) {
		x[i][1] = ++ cnt;
		son[cnt].clear();
		dfn[cnt] = lt[cnt] = 0;
	}
	for (int i = 1; i <= n; ++ i) {
		x[i][0] = ++ cnt;
		son[cnt].clear();
		dfn[cnt] = lt[cnt] = 0;
	}
	for (int i = 1; i <= n; ++ i) {
		y[i][1] = ++ cnt;
		son[cnt].clear();
		dfn[cnt] = lt[cnt] = 0;
	}
	for (int i = 1; i <= n; ++ i) {
		y[i][0] = ++ cnt;
		son[cnt].clear();
		dfn[cnt] = lt[cnt] = 0;
	}
}

void tarjan(int u) {
	dfn[u] = low[u] = ++ tim;
	Stack.push_back(u);
	for (int v : son[u]) {
		if (! dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (! lt[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		lt[u] = ++ scc;
		while (Stack.back() != u) {
			lt[Stack.back()] = scc;
			Stack.pop_back();
		}
		Stack.pop_back();
	}
}

int main() {
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &n);
		init();
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				scanf("%1d", &a[i][j]);
			}
		}
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				scanf("%1d", &b[i][j]);
				c[i][j] = a[i][j] ^ b[i][j];
				if (c[i][j]) { // 如果为1，则行或列异或一个
					son[x[i][1]].push_back(y[j][0]);
					son[y[j][0]].push_back(x[i][1]);
					son[x[i][0]].push_back(y[j][1]);
					son[y[j][1]].push_back(x[i][0]);
				}
				else { // 如果不为1，则行或列都异或或者都不异或
					son[x[i][1]].push_back(y[j][1]);
					son[y[j][1]].push_back(x[i][1]);
					son[x[i][0]].push_back(y[j][0]);
					son[y[j][0]].push_back(x[i][0]);
				}
			}
		}
		for (int i = 1; i <= cnt; ++ i) { // tarjan
			if (! dfn[i]) {
				tarjan(i);
			}
		}
		int fg = 0;
		for (int i = 1; i <= n; ++ i) { // 判断是否有解
			if (lt[x[i][1]] == lt[x[i][0]]) {
				puts("NO");
				fg = 1;
				break;
			}
			if (lt[y[i][1]] == lt[y[i][0]]) {
				puts("NO");
				fg = 1;
				break;
			}
		}
		if (! fg)	puts("YES");
	}
	return 0;
}
```

---

## 作者：ZSH_ZSH (赞：2)

[博客园食用效果更佳](https://www.cnblogs.com/ZHANG-SHENG-HAO/p/14332271.html)

题目大意：给定一个 $n*n$ 的 $01$ 矩阵，每次操作可以选择一行或者一列，整体 $xor$ $1$ ,求经过无限多次操作，能否变为目标矩阵

我们发现，每一行或每一列至多被操作一次，且如果某一列或某一列的操作确定，整个矩阵的操作就确定

所以枚举第一列是否被操作，获得整个矩阵的操作方法，再带回到矩阵中检验即可

代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for (register int i=(a);i<=(b);i++)
#define drep(i,a,b) for (register int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline ll read()
{
	ll sum=0,f=0;char c=getchar();
	while (!isdigit(c)) f|=(c=='-'),c=getchar();
	while (isdigit(c)) sum=(sum<<1)+(sum<<3)+(c^48),c=getchar();
	return f?-sum:sum;
}

const int N=1010;
int n,a[N][N],h[N],w[N];
char c1[N][N],c2[N][N];

inline bool chk1()
{
	memset(h,0,sizeof(h)),memset(w,0,sizeof(w));
	h[1]=1;
	rep(i,1,n) if ((a[i][1]^h[1])==0) w[i]=0;else w[i]=1;
	rep(i,2,n) if ((a[1][i]^w[1])==0) h[i]=0;else h[i]=1;
	
	rep(i,1,n) rep(j,1,n) if ((a[i][j]^h[j]^w[i])==1) return false;
	return true;
}

inline bool chk2()
{
	memset(h,0,sizeof(h)),memset(w,0,sizeof(w));
	h[1]=0;
	rep(i,1,n) if ((a[i][1]^h[1])==0) w[i]=0;else w[i]=1;
	rep(i,2,n) if ((a[1][i]^w[1])==0) h[i]=0;else h[i]=1;
	
	rep(i,1,n) rep(j,1,n) if ((a[i][j]^h[j]^w[i])==1) return false;
	return true;
}

inline void solve()
{
	n=read();
	rep(i,1,n) scanf("%s",c1[i]+1);
	rep(i,1,n) scanf("%s",c2[i]+1);
	rep(i,1,n) rep(j,1,n) a[i][j]=c1[i][j]^c2[i][j];
	
	if (chk1()||chk2()) printf("YES\n");
	else printf("NO\n");
}

int main()
{
	drep(T,read(),1) solve();
}
```

---

## 作者：caizhetong (赞：1)

[CF1475F  Unusual Matrix](https://www.luogu.com.cn/problem/CF1475F)

### 题目简述
给你两个 $n\times n$ 的 01 矩阵，你可以进行如下两种操作：

- 垂直 xor：选中一列，将这一列的每个元素分别进行 xor。
- 水平 xor：选中一行，将这一行的每个元素分别进行 xor。

给定 $a,b$ 两个矩阵，问你 $a$ 是否可以在进行有限次操作后变为 $b$。

### 简化题意 && 一些性质
用矩阵 $A$ 异或矩阵 $B$ 得到矩阵 $C$，则题目变为矩阵 $C$ 是否能经过若干次操作变成全是 $0$ 的矩阵。

一个点最终变成什么取决于这个点被操作的此数的奇偶，所以在最少操作的情况下每一行和每一列都不可能被操作两次。

### 我的思路
创建 $2n$ 个点 $x_1,x_2,...,x_n$，$x_i$ 的颜色表示第 $i$ 行是否被操作过 $y_1,y_2,...,y_n$，$y_i$ 的颜色表示第 $i$ 列是否被操作过。对于所有的 $x$ 都向所有的 $y$ 建边，若 $C_{i,j}=1$ 则给建的边标记为 $1$ 表示 $x_i$ 和 $y_j$ 只有其中一个是被操作了（也表示 $x_i$ 和 $y_j$ 颜色不同），若 $C_{i,j}=0$ 则给建的边标记为 $0$ 表示 $x_i$ 和 $y_j$ 要么都被操作，要么都不被操作（也表示 $x_i$ 和 $y_j$ 颜色相同），然后对所有点进行黑白染色（黑色和白色分别代表染和不染）。如果没有染色冲突，则输出 `YES` 否则输出 `NO`。

时间复杂度 $O(n^2)$。

这个方法同时也能求出操作的最小次数和操作的方案。

### 参考代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long t,n,ans,cl[1000010];
char z[1010][1010];
char a;
struct bian{
    long long to,tag;
};
vector<bian> g[1000010];
void dfs(long long u)
{
    if(ans==1) return;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i].to,clt;
        if(g[u][i].tag==1) clt=cl[u]%2+1;
        else clt=cl[u];
        if(cl[v]==0)
        {
            cl[v]=clt;
            dfs(v);
        }
        if(cl[v]!=clt)
        {
            ans=1;
            return;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);

    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>n;
        for(int i=1;i<=n*2;i++)
        {
            cl[i]=0;
            g[i].clear();
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cin>>z[i][j];
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cin>>a;
                if(a!=z[i][j])
                {
                    g[i+n].push_back({j,1});
                    g[j].push_back({i+n,1});
                }
                else
                {
                    g[i+n].push_back({j,0});
                    g[j].push_back({i+n,0});
                }
            }
        }
        cl[1]=1;
        dfs(1);
        if(ans==1) cout<<"NO"<<"\n";
        else cout<<"YES"<<"\n";
    }
    return 0;
}
```

---

## 作者：slzx2021zjx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1475F)
## 思路

首先想到**两个矩阵异或**，题目就变成把一个**新矩阵改为全是 $0$ 的矩阵**。考虑先把**第 $2$ 行**到**第 $n$ 行**水平异或，全部改到和第 $1$ 行一样，然后垂直异或。对于任意一行，能水平异或到和第 $1$ 行一样。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
bool k;
int n,m,c[1005][1005],t,l;
char a[1005][1005],b[1005][1005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>a[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>b[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(a[i][j]!=b[i][j])
					c[i][j]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				if(c[i][j]==c[1][j]) l++;
			if(l!=n&&l!=0) k=1;
			l=0;
		}
		if(k==1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
		k=0,l=0;
		memset(c,0,sizeof(c));
	}
	return 0;
}
```

	


---

## 作者：Fairicle (赞：1)

一种奇怪（？）的思路.

考虑将两个矩阵异或，得到一个新矩阵。

问题就等价于将一个全 0 的矩阵变为这个新矩阵。

然后我们发现，对某行或者某列操作可以看作至多 $1$ 次，因为由于异或的性质，操作 $2$ 次等于 $0$ 次。

我们假设 $x_i$ 是第 $i$ 行的操作数，$y_i$ 是第 $i$ 列的操作数。

考虑新矩阵 $\begin{pmatrix}a_{1,1}&a_{1,2}\\a_{2,1}&a_{2,2}\end{pmatrix}$

则有 

$x_1+y_1=a_{1,1},x_1+y_2=a_{1,2},x_2+y_1=a_{2,1},x_2+y_2=a_{2,2}$

可以发现是 $k$ 元一次方程组，有 $k$ 个方程.

但是我们如果局限 $x_i,y_j,a_{i,j}$ 的范围为 $[0,1]$，就会出现 $x_i,y_j$ 都为 $1$ 而 $a_{i,j}$ 没有 $2$ 的情况。

那么就使异或后得到的 $a_{i,j}=0$ 时，使 $a_{i,j}=0$ 或 $a_{i,j}=2$ 即可。

方程列好了，如何求解？高斯消元显然是不行的，因为等式右边有可能两个取值。我们发现，只要确定一个未知数，其他未知数都能确定了。所以找到某个不等式 $x_i+y_j=a_{i,j}$ 且 $a_{i,j}=1$ 时，讨论 $x_i=0,y_j=1$ 和 $x_i=1,y_j=0$ 两种情况，然后求出其他未知数的值。若不等式矛盾则无解，否则有解。

code：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
int n,t;
#define N 1010
char a[N][N],b[N][N];
int x[N],y[N],c[N][N],d[N][N],xx,yy;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(ri i=1;i<=n;++i) scanf("%s",a[i]+1);
        for(ri i=1;i<=n;++i) scanf("%s",b[i]+1);
        for(ri i=1;i<=n;++i) for(ri j=1;j<=n;++j) c[i][j]=a[i][j]-'0';
        for(ri i=1;i<=n;++i) for(ri j=1;j<=n;++j) d[i][j]=b[i][j]-'0',d[i][j]^=c[i][j];
        int sum=0;
        for(ri i=1;i<=n;++i) for(ri j=1;j<=n;++j) sum+=d[i][j];
        if(!sum) {puts("YES");continue;}
        for(ri i=1;i<=n;++i){
            for(ri j=1;j<=n;++j){
                if(d[i][j]==1) xx=i,yy=j;
            }
        }
        for(ri i=1;i<=n;++i) x[i]=y[i]=-1;
        int ok=1;
        x[xx]=1,y[yy]=0;
        for(ri i=1;i<=n;++i) {if(i==yy) continue;if(d[xx][i]==0) y[i]=(2-x[xx])%2;else y[i]=1-x[xx];}
        for(ri i=1;i<=n;++i) {if(i==xx) continue;if(d[i][yy]==0) x[i]=(2-y[yy])%2;else x[i]=1-y[yy];}
        for(ri i=1;i<=n;++i){
            for(ri j=1;j<=n;++j){
                if(x[i]!=-1&&y[i]!=-1) if((x[i]+y[j])%2!=d[i][j]) ok=0;
            }
        }
        for(ri i=1;i<=n;++i) x[i]=y[i]=-1;
        int ok2=1;
        x[xx]=0,y[yy]=1;
        for(ri i=1;i<=n;++i) {if(i==yy) continue;if(d[xx][i]==0) y[i]=(2-x[xx])%2;else y[i]=1-x[xx];}
        for(ri i=1;i<=n;++i) {if(i==xx) continue;if(d[i][yy]==0) x[i]=(2-y[yy])%2;else x[i]=1-y[yy];}
        for(ri i=1;i<=n;++i){
            for(ri j=1;j<=n;++j){
                if(x[i]!=-1&&y[i]!=-1) if((x[i]+y[j])%2!=d[i][j]) ok2=0;
            }
        }
        if(!ok&&!ok2) puts("NO");
        else puts("YES");
    }
    return 0;
}
```


---

## 作者：SegTree (赞：0)

### 题意

给你两个 $n\times n$ 的 01 矩阵 $A$ 和 $B$，你可以进行如下两种操作：

- 选中一列，将这一列的每个元素分别异或 $1$。

- 选中一行，将这一行的每个元素分别异或 $1$。

询问能否将 $A$ 转化成 $B$。

### 题解

好像和其他题解思路都不一样（？）。

显然可以把 $A$ 和 $B$ 的对应项元素异或在一起为矩阵 $C$，显然问题等价于能否将 $C$ 转化成全 $0$ 矩阵。

显然，如果每行全部相等，那么每一列全 $1$ 的异或 $1$ 即可。

故只需要转化到每行都相等就可以。你发现每个行只有两种情况，不变或者全部异或 $1$。那么如果 $n$ 行每行都能转化成同一种状态，就能转化。

因为要标记每行的状态，不妨考虑哈希。检查一下如果有状态被标记了 $n$ 次，那么 $n$ 行全都能转化成这种状态，则有解，否则，如果所有行都不能转成一种状态，显然无解。

时间复杂度 $O(n^2)$。

[Submission](https://codeforces.com/contest/1475/submission/219742600)。

---

## 作者：lin_rany (赞：0)

## CF1475F Unusual Matrix
题目链接:[CF1475F Unusual Matrix](https://www.luogu.com.cn/problem/CF1475F)

题目大意:给定两个$n*n$大小的$01$数组$a,b$。每次操作可以选择$a$的一行或者一列对$1$进行异或，问是否有可能让$a=b$。

数据范围:$1\le n \le 1000$

题解:采用并查集来求解，我们知道一行$or$一列最多翻转一次。如果$a[i][j]==b[i][j]$意味着第$i$行和第$j$列翻转的次数是相同的，否则两者翻转的次数是不同的。这种关系我们可以使用并查集来维护，只要发现了有矛盾就意味着不成立。如果要求输出操作序列，可以使用$2-sat$来求解。

AC代码:
```cpp
#include<bits/stdc++.h>

#define ld long double
#define ll long long
using namespace std;
template<class T>
void read(T& x)
{
	T res = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')f = -1; c = getchar();
	}
	while (isdigit(c)) {
		res = (res << 3) + (res << 1) + c - '0'; c = getchar();
	}
	x = res * f;
}
const ll N = 2000 + 10;
const int mod = 1e9 + 7;
int f[N * 10];
int t, n, a[N][N], b[N][N];
int find(int x)
{
	return x == f[x] ? f[x] : f[x] = find(f[x]);
}
#define r(x) (x+n)
#define c(x) (x)
#define fm(x) (x+2*n)
int main()
{
	//ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif // ONLINE_JUDGE
	read(t);
	while (t--)
	{
		read(n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%1d", &a[i][j]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%1d", &b[i][j]);
		for (int i = 1; i <= n; i++)
		{
			f[r(i)] = r(i);
			f[fm(r(i))] = fm(r(i));
			f[c(i)] = c(i);
			f[fm(c(i))] = fm(c(i));
		}
		bool isok = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (a[i][j] == b[i][j])
				{
					if (find(r(i)) == find(fm(c(j))) || find(c(j)) == find(fm(r(i))))isok = 0;
					f[find(r(i))] = find(c(j));
					f[find(fm(r(i)))] = find(fm(c(j)));
				}
				else
				{
					if (find(r(i)) == find((c(j))) || find(fm(c(j))) == find(fm(r(i))))isok = 0;
					f[find(r(i))] = find(fm(c(j)));
					f[find(fm(r(i)))] = find(c(j));
				}
			}
		}
		printf("%s\n", isok ? "YES" : "NO");
	}

	return 0;
}

```

---

## 作者：do_while_true (赞：0)

# [F](https://codeforces.com/contest/1475/problem/F)

### $\mathcal{Translate}$

给定两个$n\times n$ 的 $01$矩阵 $A,B$，询问 $A$ 是否能经过一系列变换变成 $B$。变换为选一行或一列各自变成其 $xor 1$。

$1\leq n\leq 1000$

### $\mathcal{Solution}$

把两个矩阵异或一下，那么问题转化为一个矩阵是否能经过一系列变换变成全 $0$。这个变换可以看成每一位各自取反。

考虑两个性质：

1. 一行或一列最多会被取反一次。因为取反偶数次相当于不取反，取反奇数次相当于取反一次。

2. 若一个位置为 $0$，则其当前行和当前列是否取反是相同的，否则相反。这样才能消成 $0$。

考虑性质 $2$，使得每一行和每一列都能连接起一个关系来，那么随便选一行或者一列，确定它是否取反，就能确定整个矩阵是否取反。

两种情况搞下来各检查一遍看是否合法即可。把每一行和每一列都看成一个节点，连成图更好写一些。

### [$\mathcal{Code}$](https://codeforces.com/contest/1475/submission/105842103)


---

