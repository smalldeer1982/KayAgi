# Graph Coloring

## 题目描述

You are given an undirected graph without self-loops or multiple edges which consists of $ n $ vertices and $ m $ edges. Also you are given three integers $ n_1 $ , $ n_2 $ and $ n_3 $ .

Can you label each vertex with one of three numbers 1, 2 or 3 in such way, that:

1. Each vertex should be labeled by exactly one number 1, 2 or 3;
2. The total number of vertices with label 1 should be equal to $ n_1 $ ;
3. The total number of vertices with label 2 should be equal to $ n_2 $ ;
4. The total number of vertices with label 3 should be equal to $ n_3 $ ;
5. $ |col_u - col_v| = 1 $ for each edge $ (u, v) $ , where $ col_x $ is the label of vertex $ x $ .

If there are multiple valid labelings, print any of them.

## 样例 #1

### 输入

```
6 3
2 2 2
3 1
5 4
2 5```

### 输出

```
YES
112323```

## 样例 #2

### 输入

```
5 9
0 2 3
1 2
1 3
1 5
2 3
2 4
2 5
3 4
3 5
4 5```

### 输出

```
NO```

# 题解

## 作者：kouylan (赞：7)

## 题解 CF1354E 【Graph Coloring】

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1354E)

[Codeforces题面传送门](https://codeforces.com/contest/1354/problem/E)

### 【题意】

给你一张图，要求给每个点填上 {$1,2,3$} 中的一个，使得相邻两点上数字的差为 $1$，问是否可行 + 构造方案。

### 【分析】

显然，$2$ 只能跟 $1,3$ 填在一起，$1,3$ 不能填在一起。根据这个性质，我们就可以知道合法的图一定是二分图。换句话说，不是二分图的直接输出 $\mathrm{NO}$ 即可。

但是，如果是二分图，一定合法吗？显然不是。在每一个连通块内，所有黑点或白点都必须为 $2$（想一下我们是如何推出这是二分图的），否则不合法。所以我们首先要记录一下每一个连通块内黑点和白点分别有哪些，记为 $bl_i$ 和 $wh_i$，用 $\mathrm{vector}$ 解决。

判断是否合法时，我们就需要 $\mathrm{dp}$。设 $f_{i,j}$ 表示考虑到第 $i$ 连通块，共选取了 $j$ 个点填 $2$ 是否可行。所以初始化就是 $f_{0,0}=1$。转移方程就是：

$$f_{i,j}=f_{i-1,j-bl_i.size()}|f_{i-1,j-wh_i.size()}$$

记连通块个数为 $cnt$，则如果 $f_{cnt,n2}=1$，输出 $\mathrm{YES}$，否则输出 $\mathrm{NO}$。

接下来，构造方案就简单了。我们从 $f_{cnt,n2}$ 逆推，并且记录每一步的方案。最后在相应的方案下填 $2$，余下的格子填 $1,3$即可。

总结一下，这道题的代码分为这样几个部分：

1. 判断是否为二分图；

1. $\mathrm{dp}$ 判断 $2$ 的个数是否可行；

1. 逆推求出方案。

下面是 AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,m,n1,n2,n3;
int ee,h[100005],nex[100005<<1],to[100005<<1];
int c[5005],vis[5005],cnt;
int col[5005],f[5005][5005],c2[5005];
vector<int> bl[5005],wh[5005];

void addedge(int x,int y)
{
	nex[++ee] = h[x];
	to[ee] = y;
	h[x] = ee;
}

void bgraph(int x)
{
	for(int i=h[x];i;i=nex[i])
		if(!c[to[i]])
		{
			c[to[i]] = (c[x]==1 ? 2 : 1);
			bgraph(to[i]);
		}
		else if(c[to[i]]==c[x])
			puts("NO"), exit(0);
}

void dfs(int x)
{
	vis[x] = true;
	if(c[x]==1)
		bl[cnt].push_back(x);
	else
		wh[cnt].push_back(x);
	for(int i=h[x];i;i=nex[i])
		if(!vis[to[i]])
			dfs(to[i]);
}

signed main()
{
	cin>>n>>m>>n1>>n2>>n3;
	for(int i=1,x,y;i<=m&&scanf("%lld%lld",&x,&y);i++)
		addedge(x,y), addedge(y,x);
	for(int i=1;i<=n;i++)
		if(!c[i])
			c[i] = 1, bgraph(i);
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cnt++;
			dfs(i);
		}
	f[0][0] = 1;
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<=n;j++)
		{
			if(bl[i].size()<=j)
				f[i][j] |= f[i-1][j-bl[i].size()];
			if(wh[i].size()<=j)
				f[i][j] |= f[i-1][j-wh[i].size()];
		}
	if(!f[cnt][n2])
		return puts("NO"), 0;
	puts("YES");
	int now=n2;
	for(int i=cnt;i>=1;i--)
	{
		if(f[i-1][now-bl[i].size()])
			c2[i] = 1, now -= bl[i].size();
		else if(f[i-1][now-wh[i].size()])
			c2[i] = 2, now -= wh[i].size();
	}
//	for(int i=1;i<=cnt;i++)cout<<c2[i]<<' ';cout<<endl;
	for(int i=1;i<=cnt;i++)
		if(c2[i]==1)
		{
			for(int j=0;j<bl[i].size();j++)
				col[bl[i][j]] = 2;
		}
		else
		{
			for(int j=0;j<wh[i].size();j++)
				col[wh[i][j]] = 2;
		}
	int s1=0;
	for(int i=1;i<=n;i++)
		if(!col[i])
		{
			if(s1<n1)
				col[i] = 1, s1++;
			else
				col[i] = 3;
		}
	for(int i=1;i<=n;i++)
		cout<<col[i];
	
	return puts(""), 0;
}
/*
10 1
0 1 9
2 7
*/
```

祝大家 AC 愉快！

---

## 作者：皎月半洒花 (赞：4)

这题还是很签的。

考虑颜色 $1,3$ 之间不能连边，$2$ 不能和自己连边这个性质十分二分图。然后就考虑二分图染色判断合法性。之后考虑由于原图可能是许多连通块，每个连通块都需要可以二染色，即每个连通块的左右部，其中一部是 $1,3$，另一部是 $2$。于是考虑怎么分配这个东西，发现就是一个背包，$f_{i,j}$ 表示前 $i$ 个连通块能否找出 $j$ 个染了 $2$ 的。记录一下路径就可以知道每个连通块怎么分配的左右部。之后把染 $1,3$ 的根据 $n_1,n_3$ 分配一下就好了。

复杂度瓶颈在背包。总复杂度 $O(n^2+m)$。

```cpp
int tot ;
int n, m ;
vint E[N] ;
vint V[N][3] ;
int fa[N] ;
int rev[N] ;
int ans[N] ;
int coo[N] ;
int vis[N] ;
int col[N] ;
int f[N][N] ;
int pre[N][N] ;
int biii[N][3] ;
int n1, n2, n3 ;
 
void dfs(int x, int s){
    col[x] = s ;
//    cout << x << '\n' ;
    for (auto k : E[x]){
        if (!col[k])
            dfs(k, s == 1 ? 2 : 1) ;
        else if (col[k] == col[x]){
            cout << "NO" ; exit(0) ;
        }
    }
}
int find(int x){
    if (x == fa[x]) return x ;
    return fa[x] = find(fa[x]) ;
}
void merge(int x, int y){
    int f1 = find(x) ;
    int f2 = find(y) ;
    if (f1 != f2)
        fa[f1] = f2 ;
}
int main(){
    int x, y ;
    cin >> n >> m ;
    cin >> n1 >> n2 >> n3 ;
    for (int i = 1 ; i <= n ; ++ i) fa[i] = i ;
    for (int i = 1 ; i <= m ; ++ i)
        x = qr(), y = qr(), merge(x, y), E[y].p_b(x), E[x].p_b(y) ;
    for (int i = 1 ; i <= n ; ++ i)
        if (!col[i]) dfs(i, 1) ;
//    debug(col, 1, n) ;
    for (int i = 1 ; i <= n ; ++ i){
        biii[find(i)][col[i]] ++ ;
        if (find(i) == i)
            rev[++ tot] = i ;
        V[find(i)][col[i]].p_b(i) ;
    }
    f[0][0] = 1 ; //cout << tot << '\n' ;
    for (int i = 1 ; i <= tot ; ++ i){
        int x = rev[i] ;
//        cout << biii[x][1] << " " << biii[x][2] << '\n' ;
        for (int j = n2 ; j >= biii[x][1] ; -- j){
            if (!pre[i][j]) pre[i][j] = pre[i - 1][j] ;
            if (!f[i][j] && f[i - 1][j - biii[x][1]]){
                pre[i][j] = i ; f[i][j] = 1 ;
//                cout << i << " " << j << " " << j - biii[i][1] << "\n" ;
            }
        }
        for (int j = n2 ; j >= biii[x][2] ; -- j){
            if (!pre[i][j]) pre[i][j] = pre[i - 1][j] ;
            if (!f[i][j] && f[i - 1][j - biii[x][2]]){
                pre[i][j] = i + n ; f[i][j] = 1 ;
//                cout << i << " " << j << " " << j - biii[i][2] << " " << f[i][j] << "\n" ;
            }
        }
    }
    /*
    debug(rev, 1, tot) ;
    for (int i = 1 ; i <= tot ; ++ i){
        int x = rev[i] ; cout << x << '\n' ;
        for (auto k : V[x][1]) cout << k << " " ; puts("") ;
        for (auto k : V[x][2]) cout << k << " " ; puts("- - - - - - - - ") ;
    }
    */
//    cout << tot << " " << n2 << "\n" ;
    if (!f[tot][n2]) return puts("NO"), 0 ;
    int p = tot, q = n2 ;
    while (p){
        int x = rev[p] ;
//        cout << p << " " << q << " " << pre[p][q] << '\n' ;
        if (pre[p][q] <= n){
            coo[p] = 0 ;// used 1
            p --, q -= biii[x][1] ;
        }
        else {
            coo[p] = 1 ;// used 2
            p --, q -= biii[x][2] ;
        }
    }
    puts("YES") ;
//    for (int i = 1 ; i <= tot ; ++ i)
//        cout << coo[i] << '\n' ;
    for (int i = 1 ; i <= tot ; ++ i){
        int x = rev[i] ;
       // cout << V[x][1].size() << " " << V[x][2].size() << '\n' ;
        if (!coo[i]){
            int t = 0 ; int x = rev[i];
            for (auto k : V[x][1]) ans[k] = 2 ;
            for (int k = 0 ; k < V[x][2].size() && n1 ; ++ k, t = k)
                ans[V[x][2][k]] = 1, n1 -- ;
            if (t <= V[x][2].size() - 1 && !V[x][2].empty())
                for (int k = t ; k < V[x][2].size() ; ++ k)
                    ans[V[x][2][k]] = 3 ;
        }
        else {
            int t = 0 ; int x = rev[i] ;
            for (auto k : V[x][2]) ans[k] = 2 ;
            for (int k = 0 ; k < V[x][1].size() && n1 ; ++ k, t = k)
                ans[V[x][1][k]] = 1, n1 -- ;
            if (t <= V[x][1].size() - 1 && !V[x][1].empty())
                for (int k = t ; k < V[x][1].size() ; ++ k)
                    ans[V[x][1][k]] = 3 ;
 
        }
//        debug(ans, 1, n) ;
    }
    for (int i = 1 ; i <= n ; ++ i)
        printf("%d", ans[i]) ;
    return 0 ;
}
```

---

## 作者：Eibon (赞：2)

发现染色为 $1$ 的点一定不与染色为 $3$ 的点连边，相同染色的不能自己连边。

所以 $1$ 和 $3$ 可以归为一体，$2$ 被单独归一起。

这样就构成了二分图，然后黑白染色判断合法性。

显然，黑白是交替出现的，我们只需要知道 $2$ 怎么涂就行了，而在一个联通块内，其要么为黑色，要么为白色。

将每个联通块视为一个组，组内包含白点和黑点的数量，进行分组背包即可。最后只需回溯并重新染色每个联通块即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int mod=1e9+7;
int T,n,m,n1,n2,n3,u,v,tot,flag,cnt;
int a[maxn],head[maxn],w[maxn],rt[maxn];
int dp[5005][5005],W[maxn],num[maxn],vis[maxn];
struct edge
{
	int to,nxt;
};
edge e[maxn<<1];
void add(int u,int v)
{
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,bool op)
{
	w[u]=op;
	num[cnt]++;
	W[cnt]+=w[u];
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]){
			if(w[v]!=(w[u]^1)){
				flag=1;
				return;
			}
		}
		else{
			dfs(v,w[u]^1);
		}
	}
}
void dfs2(int u,bool op)
{
	w[u]=op;
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			dfs2(v,op^1);
		}
	}
}
void solve()
{
	scanf("%d%d%d%d%d",&n,&m,&n1,&n2,&n3);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			w[i]=1;
			rt[++cnt]=i;
			dfs(i,1);
		}
		if(flag){
			puts("NO");
			return;
		}
	}
	dp[0][0]=1;
	for(int i=1;i<=cnt;i++){
		for(int j=n2;j>=0;j--){
			if(j>=W[i]&&dp[i-1][j-W[i]]){
				dp[i][j]=1;
			}
			int k=num[i]-W[i];
			if(j>=k&&dp[i-1][j-k]){
				dp[i][j]=1;
			}
		}
	}
	if(!dp[cnt][n2]){
		puts("NO");
		return;
	}
	puts("YES");
	memset(w,0,sizeof w);
	memset(vis,0,sizeof vis);
	int now=n2;
	for(int i=cnt;i;i--){
		if(now>=W[i]&&dp[i-1][now-W[i]]){
			dfs2(rt[i],1);
			now-=W[i];
		}
		else{
			dfs2(rt[i],0);
			int k=num[i]-W[i];
			now-=k;
		}
	}
	for(int i=1;i<=n;i++){
		if(!w[i]){
			if(n1){
				putchar('1');
				n1--;
			}
			else{
				putchar('3');
			}
		}
		else{
			putchar('2');
		}
	}
}
signed main()
{
	solve();
    return 0;
}
//dyyyyds
```

---

## 作者：Strelitzia (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1354E)

---

太艰难了，思路对了，调了一小时。

我们可以发现，其实 $\text{1}$ 和 $\text{3}$ 没有什么区别，都只能连 $\text{2}$，都不能和自己相连，

所以我们可以把 $1$ 和 $3$，看成一种点，就变成二分图染色简单题了。

我们需要一个 $\operatorname {dp}$ 来判断可行性。

由于它不一定是联通的，对于每个联通块都需要分别判断。

```cpp
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}


const int maxn = 5e3 + 5;
const int maxm = 1e5 + 5;

int nxt[maxm << 2],ver[maxm << 2],head[maxn],tot;
void addEdge(int u,int v) {
	nxt[++ tot] = head[u];ver[tot] = v;head[u] = tot;
}

int n,m,n1,n2,n3,dp[maxn][maxn],col[maxn],num2[maxn],block[maxn],total[maxn],vis[maxn],cnt;

void dfs(int u,int color) {
	num2[cnt] += color;
	total[cnt] ++;
	col[u] = color;
	vis[u] = 1;
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (!vis[v]) dfs(v,color ^ 1);
		else if (col[v] == col[u]) {
			puts("NO");
			exit(0);
		}
	}
}

void dfs2(int u,int color) {
	col[u] = color;
	vis[u] = 1;
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (!vis[v]) dfs2(v,color ^ 1);
	}
}

int main () {
	read(n);read(m);
	read(n1);read(n2);read(n3);
	int u,v;
	for (int i = 1 ; i <= m ; ++ i) {
		read(u);read(v);
		addEdge(u,v);addEdge(v,u);
	}
	for (int i = 1 ; i <= n ; ++ i) {
		if (vis[i] == 0) {
			block[++ cnt] = i;
			dfs(i,1);
		}
	}
	dp[0][0] = 1;
	for (int i = 1 ; i <= cnt ; ++ i) {
		for (int j = n2 ; j >= 0 ; -- j) {
			if (j >= num2[i] && dp[i - 1][j - num2[i]]) dp[i][j] = 1;
			if (j >= total[i] - num2[i] && dp[i - 1][j - total[i] + num2[i]]) dp[i][j] = 1;
		}
	}
	if (!dp[cnt][n2]) {
		printf("NO");
		return 0;
	}
	puts("YES");
	memset(vis,0,sizeof vis);
	memset(col,0,sizeof col);
	int tmp = n2;
	for (int i = cnt ; i >= 1 ; -- i) {
		if (tmp >= num2[i] && dp[i - 1][tmp - num2[i]]) {
			dfs2(block[i],1);
			tmp -= num2[i];
		}
		else {	
			dfs2(block[i],0);
			tmp -= (total[i] - num2[i]);
		}
	}
	for (int i = 1 ; i <= n ; ++ i) {
		if (col[i] == 0) {
			if (n1) putchar('1'),n1 --;
			else putchar('3');
		}
		else putchar('2');	
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

拉低了我对 $2100$ 的题的认知。。

------------

显然 $1$ 和 $3$ 不能相连，可以归为一类，这样就变成了一个二分图。

对于每个联通块染色分成两组，显然我们需要从每个联通块中选一组使得总共有 $n_2$ 个点。

简单背包好了，然后倒推求出染色方案。

$1$ 和 $3$ 没有本质区别，于是从非 $2$ 的中任意分成 $n_1$ 个和 $n_3$ 个即可。

复杂度 $\operatorname{O}(\frac{n^2}{w})$。虽然没有必要，还是用了 bitset。

------------

代码不长。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+84,maxm=2e5+84;
int n,m,x,y,cntt,cnt[4],col[maxn],cntp[maxn][2],ans[maxn];
namespace Sherry_Graph{
    struct Edge{
        int to,ne;
    }e[maxm];
    int ecnt=1,head[maxn];
    inline void add(int u,int v){
        e[ecnt]={v,head[u]};
        head[u]=ecnt++;
        return ;
    }
}
using namespace Sherry_Graph;
vector<int> p[maxn][2];
inline bool dfs(int x,bool c,int frm){
    col[x]=c;
    p[frm][c].push_back(x);
    cntp[frm][c]++;
    for(int i=head[x];i;i=e[i].ne){
        if(col[e[i].to]==col[x])
            return 0;
        if(col[e[i].to]==-1&&!dfs(e[i].to,c^1,frm))
            return 0;
    }
    return 1;
}
bitset<maxn> f[maxn];
inline void dfs_ans(int cnt,int sum){
    if(!cnt)
        return ;
    if(sum>=cntp[cnt][0]&&f[cnt-1][sum-cntp[cnt][0]]){
        for(int i:p[cnt][0])
            ans[i]=2;
        dfs_ans(cnt-1,sum-cntp[cnt][0]);
        return ;
    }
    if(sum>=cntp[cnt][1]&&f[cnt-1][sum-cntp[cnt][1]]){
        for(int i:p[cnt][1])
            ans[i]=2;
        dfs_ans(cnt-1,sum-cntp[cnt][1]);
        return ;
    }
    return ;
}
int main(){
    memset(col,-1,sizeof(col));
    scanf("%d%d%d%d%d",&n,&m,&cnt[1],&cnt[2],&cnt[3]);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++)
        if(col[i]==-1&&!dfs(i,0,++cntt))
            goto No;
    f[0][0]=1;
    for(int i=1;i<=cntt;i++)
        f[i]=(f[i-1]<<cntp[i][0])|(f[i-1]<<cntp[i][1]);
    if(!f[cntt][cnt[2]])
        goto No;
    dfs_ans(cntt,cnt[2]);
    puts("YES");
    for(int i=1;i<=n;i++){
        if(ans[i])
            putchar('2');
        else if(cnt[0]<cnt[1]){
            putchar('1');
            cnt[0]++;
        }
        else
            putchar('3');
    }
    return 0;
    No:puts("NO");
    return 0;
}
```


---

## 作者：zythonc (赞：1)

~~**E题中的大水题**~~

## 【题目分析】

读题之后容易发现：
- 相同的数字之间一定不会有边
- $1,3$之间不会有边

所以可以得到以下结论：

- **对于任意一条路径，2是交替出现的**

- **图中是没有奇数个节点的环的**

所以很容易想到模仿**二分图染色**，判断出第一种不满足要求的情况

然后怎么办呢？

容易看出，只要图中**值为二的节点被确定了，那么整个题目的答案也就确定了**

所以染色的时候，对于每个联通块，我们只染 $0,1$ 两种颜色

这样一来，对于每个联通块
>要么颜色为 $0$ 的位置全部是 $2$
>
>要么颜色为 $1$ 的位置全部是 $2$

**这也就转化成了分组背包问题：**
- 物品组数就是联通块的个数
- 每组物品的个数为 $2$，大小分别是联通块内颜色为 $0$ 的节点的个数与颜色为 $1$ 的节点的个数
- **每组的物品内都必须且仅选1个**

**问如何选能使得恰好将背包占满，背包容量即为题面中的$n_2$**

**考虑转化**

**我们将每组的最小值加到一起，然后将每组转化为差值，然后在差值内进行01背包**

如果不能恰好将背包占满，就还是不满足要求

如果能，就记录下来路径，**将这条路径上点的值取反**

之后判断，顺序输出即可

## 【代码实现】

```
#include<iostream>
#define N 1000100
using namespace std;
int n,m,n1,n2,n3,num,head[N],fr,to,s[N][2],size,lesst,n2num,b[N],bsize,lu[N],kuai[N],f[N];
bool vis[N],cl[N],no,choose[N],bo;
struct Edge{
	int na,np;
}e[N];
inline void add(int f,int t){
	e[++num].na=head[f];
	e[num].np=t;
	head[f]=num;
}
inline void dfs(int n,bool cl){
	vis[n]=1;::cl[n]=cl;s[size][cl]+=1;kuai[n]=size;
	int to;
	for(int i=head[n];i;i=e[i].na){
		to=e[i].np;
		if(vis[to]){
			if(cl==::cl[to]){no=1;return;}
//染色过程中发现不满足要求
			else continue;
		}
		dfs(to,!cl);
		if(no) return;
	}
}
inline int abs(int a){
	return a>0?a:-a;
}
signed main(){
	ios::sync_with_stdio(0);
	int i,o;
	cin>>n>>m>>n1>>n2>>n3;
	for(i=1;i<=m;i++){
		cin>>fr>>to;
		add(fr,to);add(to,fr);
	}
	for(i=1;i<=n;i++){
		if(!vis[i]){
			size+=1,dfs(i,0);
//size即为联通块的个数
			if(s[size][0]>s[size][1]){
//颜色为0的节点的个数比颜色为1的节点的个数多，我们选择1，然后标记
				n2num+=s[size][1];
				choose[size]=1;
			}
			else{
				n2num+=s[size][0];
			}
			b[++bsize]=abs(s[size][0]-s[size][1]);
		}
	}
	lesst=n2-n2num;
	if(lesst<0||no){
		cout<<"NO";return 0;
	}
	f[0]=-1,lu[0]=-1;
	for(i=1;i<=bsize;i++){
		for(o=lesst;o>=b[i]&&o;o--){
			if(f[o]) continue;
			if(f[o-b[i]]) f[o]=i,lu[o]=o-b[i];
		}
	}
	if(!f[lesst]){
		cout<<"NO";return 0;
	}
//无法恰好占满
	cout<<"YES\n";
	int it=lesst;
	while(f[it]!=-1){
		choose[f[it]]=!choose[f[it]];
		it=lu[it];
	}
//取反，即选0的改选1，反之亦然
	for(i=1;i<=n;i++){
		if(cl[i]==choose[kuai[i]]) cout<<"2";
		else{
			if(n1){
				cout<<"1";n1--;
			}
			else{
				cout<<"3";n3--;
			}
		}
	}
	return 0;
}
```

---

## 作者：囧仙 (赞：1)

## 题目大意

$n$个节点$m$条边的无向图，要求用$\{1,2,3\}$对每个点染色，使得相邻的两个点的权值差**刚好**为$1$。现在需要求出一个方案，使得一共染了$n_1$个$1$,$n_2$个$2$,$n_3$个$3$。无解输出$\rm NO$。

## 题解

观察$1,3$的性质，我们能够发现：

- $1,3$都只能和$2$相邻

- $1,3$不能和自己与对方相邻

那么，假设我们把所有的$3$都当作$1$，可以保证图的性质不变，且$2$的个数不变。这样，原图就变成了一个二分图染色问题。

但是到这里还没有结束。$1,3$可以相互转换，因此可以很方便地处理$n_1,n_3$的限制；但是我们需要**恰好**染了$n_2$个$2$，就得综合考虑每一个二分图应该怎么样染颜色$2$。

事实上，这是一个背包问题。每张二分图染$2$的数量，只有两种情况。假设这张二分图左边的节点数为$a$，右边的为$b$，那么我们可以染$a$或$b$个$2$。于是，我们可以**默认将所有染色图右边染色**，然后考虑哪些二分图需要翻转颜色。这样的好处是，我们将$a,b$中二选一的问题变成了是否选择$a-b$的$01$背包问题。

还需要注意的是，如果要用滚动数组优化，$a-b$可能是负数。因此需要根据情况改变枚举的方向。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =5e3+3,MAXM=1e5+3;
int head[MAXN],ver[MAXM*2],nxt[MAXM*2],tot;
void add(int u,int v){
ver[++tot]=v,nxt[tot]=head[u],head[u]=tot;
}
int n,m,cnt,one[MAXN],two[MAXN],del[MAXN],n1,n2,n3;
int col[MAXN],id[MAXN],_dp[MAXN*2],*dp;
bool rev[MAXN];
void dfs(int u){
    if(col[u]==2) ++two[id[u]]; else ++one[id[u]];
    for(int i=head[u];i;i=nxt[i]){
        int v=ver[i]; if(!col[v])
        col[v]=3-col[u],id[v]=id[u],dfs(v);
        else if(col[v]==col[u]) puts("NO"),exit(0);
    }
}
int main(){
    n=qread(),m=qread(),dp=_dp+n;
    n1=qread(),n2=qread(),n3=qread();
    up(1,m,i){
        int u=qread(),v=qread();
        add(u,v),add(v,u);
    }
    up(1,n,i) if(!col[i])
    col[i]=1,id[i]=++cnt,dfs(i),n2-=two[cnt];
    if(n2==0){
        puts("YES");
        up(1,n,i){
            if(rev[id[i]]) col[i]=3-col[i];
            if(col[i]==2) putchar('2'); else{
                if(n1) putchar('1'),--n1;
                else   putchar('3');
            }
        }
        return 0;
    }
    up(1,cnt,i){
        del[i]=one[i]-two[i]; int s=del[i];
        if(s>0) {dn(n,-n,j) if(dp[j]&&!dp[j+s]) dp[j+s]=i;}
        else    {up(-n,n,j) if(dp[j]&&!dp[j+s]) dp[j+s]=i;}
        if(!dp[s]) dp[s]=i;
    }
    if(!dp[n2]) puts("NO"),exit(0); puts("YES");
    for(int p=n2;p;p=p-del[dp[p]]) rev[dp[p]]=true;
    up(1,n,i){
        if(rev[id[i]]) col[i]=3-col[i];
        if(col[i]==2) putchar('2'); else{
            if(n1) putchar('1'),--n1;
            else   putchar('3');
        }
    }
    return 0;
}
```

---

## 作者：LTb_ (赞：1)

[更好的阅读](https://lycltb.github.io/post/solution-cf1354f/)

> [link](<https://codeforces.com/problemset/problem/1354/E>)
>
> 题意简述：懒得简述

我们观察一下连边的条件，发现能连的边只有 $1-2$ 和 $2-3$ 。也就是说 **$1$ 和 $3$ 并没有区别**，于是把 $1$ 和 $3$ 看作同一个颜色。

然后很自然的想到黑白染色，注意要判断有没有颜色冲突。

黑白染色之后，对于每一个连通块，我们得到了其中黑色和白色的个数。显然，要么一个连通块里的黑色点全部染成颜色 $2$ ，白色点染成 $1$ 和 $3$；要么白色点全部染成颜色 $2$ ，黑色点染成 $1$ 和 $3$。

现在我们想要知道把哪些点染成 $2$，哪些点染成 $1$ 或 $3$。于是做一个 $n^2$ 的 dp。和 $01$ 背包一样（好像不太一样 不管了x），设 $dp_{i.j}$ 表示前 $i$ 个连通块中，是否可能染 $j$ 个颜色 $2$。转移也和 $01$ 背包没有太大差异，不再赘述。

最后统计答案的时候按照背包出来的方案分一下，再随意分配一下 $1$ 和 $3$，输出答案。

```cpp
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
const int MAXN=5005;
int n,m;
vector<int> v[MAXN];
int n1,n2,n3;
int cnt[MAXN],total=0;
int c1[MAXN];
bool vis[MAXN];
bool dp[MAXN][MAXN];
int la[MAXN];
bool color[MAXN];
bool flag=true;
int head[MAXN];

void dfs(int p,bool t){
	vis[p]=true;
	c1[total]+=t;
	cnt[total]++;
	color[p]=t;
	for (int i:v[p]){
		if (!vis[i]) dfs(i,t^1);
		else if (color[i]!=(t^1)){
			flag=false;
			return;
		}
	}
}

void coloring(int p,bool t){
	color[p]=t;
	vis[p]=true;
	for (int i:v[p])
		if (!vis[i]) coloring(i,t^1);
}

int main()

{
	cin>>n>>m;
	cin>>n1>>n2>>n3;
	for (int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}

	for (int i=1;i<=n;i++){
		if (!vis[i]){
			total++;
			head[total]=i;
			dfs(i,true);
			if (!flag){
				cout<<"NO"<<endl;
				return 0;
			}
		}
	}

	dp[0][0]=true;
	for (int i=1;i<=total;i++){
		for (int j=n2;j>=0;j--){
			if (j-c1[i]>=0 && dp[i-1][j-c1[i]])
				dp[i][j]=true;

			int tmp=cnt[i]-c1[i];
			if (j-tmp>=0 && dp[i-1][j-tmp])
				dp[i][j]=true;
		}
	}

	if (!dp[total][n2]){
		cout<<"NO"<<endl;
		return 0;
	}

	cout<<"YES"<<endl;

	memset(vis,false,sizeof(vis));
	memset(color,false,sizeof(color));
	int pos=n2,i=total;
	while (pos>0 && i>0){
		if (pos-c1[i]>=0 && dp[i-1][pos-c1[i]]){
			coloring(head[i],true);
			pos-=c1[i];
		}
		else{
			coloring(head[i],false);
			pos-=(cnt[i]-c1[i]);
		}
		i--;
	}
	
	int xcnt=0;
	for (int i=1;i<=n;i++){
		if (color[i]) cout<<2;
		else{
			if (xcnt<n1){
				cout<<1;
				xcnt++;
			}
			else cout<<3;
		}
	}

	cout<<endl;
	return 0;
}
```



---

## 作者：Kingna (赞：0)

## [CF1354E](https://www.luogu.com.cn/problem/CF1354E)

先对图进行二分图染色。

* 染白色的点填入 $2$，染黑色的点填入 $1/3$。
* 染黑色的点填入 $2$，染白色的点填入 $1/3$

对于一个联通块来说，$2$ 的数量等于黑点数量或者白点数量，二选一。因为总的 $2$ 的数量限制为 $n_2$，定义 $f_{i,j}$ 代表前 $i$ 个联通块，有 $j$ 个 2 是否可行。背包即可。

考虑输出方案。先把每个联通块的 $2$ 填了，这可以根据 dp 值确定。最后剩下的 $1/3$ 直接随便加入即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 5000 + 5, mod = 998244353;

int T, n, m, n1, n2, n3, flg, c[N], t1, t2, res = 1, f[N][N], ans[N];
vector<int> G[N], vb[N], vw[N], all[N];

void dfs(int u, int col, int vv) {
	if (flg) return;
	c[u] = col;
	all[vv].push_back(u);
	if (col == 1) t1++, vb[vv].push_back(u);
	if (col == 2) t2++, vw[vv].push_back(u);
	for (auto v : G[u]) {
		if (c[v] == c[u]) {
			flg = 1;
			return;
		}
		if (c[v]) continue;
		dfs(v, 3 - col, vv);
	}
}

signed main() {
	cin >> n >> m >> n1 >> n2 >> n3;
	_for(i, 1, m) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	flg = 0; res = 1;
	_for(i, 1, n) c[i] = 0;
	int cnt = 0;
	_for(i, 1, n) {
		t1 = t2 = 0;
		if (!c[i]) {
			cnt++;
			dfs(i, 1, cnt);
//			cout << vb[cnt].size() << ' ' << vw[cnt].size() << endl;
		}
	}
//	puts("-----");
	if (flg) puts("NO");
	else {
		f[0][0] = 1;
		_for(i, 1, cnt) {
			_for(j, 0, n2) {
				if (j >= vb[i].size()) f[i][j] |= f[i - 1][j - vb[i].size()];
				if (j >= vw[i].size()) f[i][j] |= f[i - 1][j - vw[i].size()];
			}
		}
		if (f[cnt][n2] == 0) puts("NO");
		else {
			int x = cnt, y = n2;
			while (x >= 1 && y >= 1) {
//				cout << x << ' ' << y << endl;
				if (y >= vb[x].size() && f[x - 1][y - vb[x].size()]) {
					for (auto v : vb[x]) ans[v] = 2;
					x--, y -= vb[x + 1].size();
				}
				else if (y >= vw[x].size() && f[x - 1][y - vw[x].size()]) {
//					cout << "p=" << x - 1 << ' ' << y - vw[x].size() << endl;
					for (auto v : vw[x]) ans[v] = 2;
					x--, y -= vw[x + 1].size();
				}
			}
			_for(i, 1, cnt) {
				for (auto v : all[i]) {
					if (!ans[v]) {
						if (n1) ans[v] = 1, n1--;
						else ans[v] = 3, n2--;
					}
				}
			}
			puts("YES");
			_for(i, 1, n) cout << ans[i];
			puts("");
		}
	}
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1354E Graph Coloring (*2100)](https://www.luogu.com.cn/problem/CF1354E)

# 解题思路

发现这个东西就是类似于二分图染色的东西。

因为 $2$ 只能和 $1,3$ 链接。其余种类的点都不能连接。

不妨把 $1,3$ 都看成同一个点放到最后处理。

那么我们就相当于是要找到一种方案使得选择每个联通快的黑点或白点，使得最终选择的总节点个数为颜色 $2$ 的个数。

这个问题可以轻松用背包来解决。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
ll _t_;
void _clear(){}
ll n,m;
ll k1,k2,k3;
vector<ll>G[5010];
ll col[5010];
ll x,y;
ll k;
ll a[5010],b[5010];
vector<ll>A[5010],B[5010];
ll dp[5010][5010];
ll ans[5010];
void dfs(ll x,ll fa,ll y)
{
    if(y==1)
        a[k]++,
        A[k].pb(x);
    else
        b[k]++,
        B[k].pb(x);
    col[x]=y;
    for(auto i:G[x])
        if(i!=fa)
        {
            if(!col[i])
                dfs(i,x,3^y);
            else if((3^y)!=col[i])
            {
                cfn;
                exit(0);
            }
        }
}
void solve()
{
    _clear();
    cin>>n>>m>>k1>>k2>>k3;
    forl(i,1,m)
        cin>>x>>y,
        G[x].pb(y),
        G[y].pb(x);
    forl(i,1,n)
        if(!col[i])
            k++,
            dfs(i,0,1);
    dp[0][0]=1;
    forl(i,1,k)
    {
        forr(j,k2,a[i])
            dp[i][j]|=dp[i-1][j-a[i]];
        forr(j,k2,b[i])
            dp[i][j]|=dp[i-1][j-b[i]];
    }
    if(dp[k][k2])
    {
        cfy;
        forl(i,1,n)
            ans[i]=1;
        forr(i,k,1)
        {
            if(k2-a[i]>=0 && dp[i-1][k2-a[i]])
            {
                k2-=a[i];
                for(auto j:A[i])
                    ans[j]=2;
            }
            else if(k2-b[i]>=0 && dp[i-1][k2-b[i]])
            {
                k2-=b[i];
                for(auto j:B[i])
                    ans[j]=2;                
            }
            else if(dp[i-1][k2])
                continue;
            else
                exit(-1);
        }
        if(k2>0)
            exit(-1);
        ll num=0;
        forl(i,1,n)
        {
            if(ans[i]==2)
                cout<<2;
            else
            {
                num++;
                if(num<=k1)
                    cout<<1;
                else
                    cout<<3;
            }
        }
        cout<<endl;
    }
    else
        cfn;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
//    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1354E)

## 题目大意

给你一个 $n$ 个节点和 $m$ 条边的无向图，让你将每一个结点写一个数字 $\left\{1,2,3\right\}$ 其中之一,使得相邻的两个点的权值之差都 $1$ ,现在给你 $n1$ , $n2$ 和 $n3$ ,表示是否有一种方案有 $n1$ 个 $1$ , $n2$ 个 $2$ 和  $n3$ 个 $3$ , 并且满足条件，如果有这种方案则输出```YES```和每一个节点所对应的数字,否则没有这种方案则输出```NO```。

我们发现如果一个节点的权值为 $1$ 或 $3$ 这两个数字,则其相邻的数字只能是 $2$ ,所以我们可以大胆的把 $1$ 和 $3$ 视为同一个数字,只需要在输出时分配一下即可。这时这道题就变成了一个**二分图**的问题。

然后考虑由于原图可能是许多个连通块,每个连通块都需要可以二染色,即每个连通块的左右部分,其中一部分是 $1$ 和 $3$ ，另一部分则是 $2$ ，这就需要我们思考如何分配这个问题，我们可以使用背包 $f_i,_j$ 表示前 $i$ 个连通块是否能够找出 $j$ 个 $2$ 的。最后记录一下分配情况即可。

上代码！

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
const int N=5e3+10;
int n,m,n1,n2,n3,cnt,B[N],num[N],tot[N],col[N],dp[N][N];
bool vis[N];
vector<int>e[N];
void dfs(int u,int co)
{
	num[cnt]+=co;
	tot[cnt]++;
	col[u]=co;
	vis[u]=1;
	for(int v:e[u])
	{
		if(!vis[v]) dfs(v,co^1);
		else if(col[v]==col[u])
		{
			printf("NO\n");
			exit(0);
		}
	}
}
void df5(int u,int co)
{
	col[u]=co;
	vis[u]=1;
	for(int v:e[u])
	{
		if(!vis[v]) df5(v,co^1);
	}
 } 
void mem()
{
	memset(vis,0,sizeof(vis));
	memset(col,0,sizeof(col));
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&n1,&n2,&n3);
	_rep(i,1,m)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	_rep(i,1,n)
	{
		if(!vis[i])
		{
			B[++cnt]=i;
			dfs(i,1);
		}
	}
	dp[0][0]=1;
	_rep(i,1,cnt)
	{
		_antirep(j,n2,0)
		{
			if(j>=num[i]&&dp[i-1][j-num[i]]) dp[i][j]=1;
			if(j>=tot[i]-num[i]&&dp[i-1][j-tot[i]+num[i]]) dp[i][j]=1;
		}
	}
	if(!dp[cnt][n2])
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	mem();
	int t=n2;
	_antirep(i,cnt,1)
	{
		if(t>=num[i]&&dp[i-1][t-num[i]])
		{
			df5(B[i],1);
			t-=num[i];	
		}
		else
		{
			df5(B[i],0);
			t-=(tot[i]-num[i]);
		}
	 } 
	 _rep(i,1,n)
	 {
	 	if(col[i]==0)
	 	{
	 		if(n1) printf("1"),n1--;
	 		else printf("3");
		 }
		 else printf("2"); 
	 }
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2100}$

---
### 解题思路：

首先发现将 $1$ 和 $3$ 具体有多少并不重要，考虑任意一个可行方案，交换其中任意的 $1$ 和 $3$ 都不会使其变成不可行方案，另一方面，将不可行方案中的任意 $1$ 和 $3$ 交换同样不会让其变成可行方案。

所以问题就可以转化成将图上的每一个点写上奇数或者偶数，要求奇数和奇数，偶数和偶数之间没有边，且偶数点个数恰好为 $n_2$，奇数点个数恰好为 $n_1+n_3$。

然后就是一个非常经典的二分图黑白染色了，如果图不是二分图一定无解。否则每一个联通块有可能对于偶数点个数贡献黑色点个数或者白色点个数，但是具体为哪个并没有确定。所以需要用 $\text{DP}$ 判断是否可能构造出写上偶数恰好为 $n_2$ 的一组解。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n1,n2,n3,n,m,x,y,head[5005],nxt[200005],num[200005],tot,v[5005],flag;
int cnt[5005][3],pr,f[5005][5005],fr[5005][5005],vis[5005],res[5005],now1,now2;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void dfs(int now,int p){
	if(v[now]!=0||flag!=0)return;
	v[now]=p;
	vis[now]=pr;
	cnt[pr][p]++;
	for(int i=head[now];i;i=nxt[i]){
		if(v[num[i]]==p){
			flag=1;
			return;
		}
		dfs(num[i],p%2+1);
	}
}
void cover(int a,int b){
	for(int i=1;i<=n;i++){
		if(vis[i]==a&&v[i]==b)
		res[i]=2;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d%d",&n1,&n2,&n3);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++)
	if(v[i]==0){
		pr++;
		dfs(i,1);
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	for(int j=0;j<=n;j++)
	if(f[i-1][j]==1){
		f[i][j+cnt[i][2]]=1;
		fr[i][j+cnt[i][2]]=2;
		f[i][j+cnt[i][1]]=1;
		fr[i][j+cnt[i][1]]=1;
	}
	if(f[pr][n2]==0||flag==1){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	now1=pr;now2=n2;
	while(now1>0){
		if(fr[now1][now2]==1)
		cover(now1,1),now2-=cnt[now1][1];
		else
		cover(now1,2),now2-=cnt[now1][2];
		now1--;
	}
	for(int i=1;i<=n;i++){
		if(res[i]==0){
			if(n1>0)printf("1"),n1--;
			else printf("3");
		}
		else printf("2");
	}
	return 0;
}
```


---

