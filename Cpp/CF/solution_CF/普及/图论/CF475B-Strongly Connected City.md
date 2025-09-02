# Strongly Connected City

## 题目描述

Imagine a city with $ n $ horizontal streets crossing $ m $ vertical streets, forming an $ (n-1)×(m-1) $ grid. In order to increase the traffic flow, mayor of the city has decided to make each street one way. This means in each horizontal street, the traffic moves only from west to east or only from east to west. Also, traffic moves only from north to south or only from south to north in each vertical street. It is possible to enter a horizontal street from a vertical street, or vice versa, at their intersection.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475B/7015745b6e36cd9d1741bb00e67e81a4ab310705.png)The mayor has received some street direction patterns. Your task is to check whether it is possible to reach any junction from any other junction in the proposed street direction pattern.

## 说明/提示

The figure above shows street directions in the second sample test case.

## 样例 #1

### 输入

```
3 3
><>
v^v```

### 输出

```
NO
```

## 样例 #2

### 输入

```
4 6
<><>
v^v^v^```

### 输出

```
YES
```

# 题解

## 作者：Hanzire76 (赞：12)

看了楼上大佬的各种Tarjan,蒟蒻瑟瑟发抖QWQ

但是这道题真的这么麻烦吗？？

其实只要稍加思考便可以发现一个这张图的一个特性：**只要边缘的四个点是相连通的，整张图就是联通的。**

根据题意，可以发现，图中的任何一个节点，都可以通过在边缘的四条边中的某个点直接抵达（一溜就到了）。

如果四个顶点相连通，就代表四条边缘的边上的点都可以通过顶点到达，而中间的点只要顺着所处的边的方向走一点可以到边缘，所以所有点都可以到所有点。

相反的，如果有四角上的顶点从相邻的四角上的顶点无法到达，也就意味着所有点都到不了这个顶点（因为只有两条边连着外面）。

因此只要判断四个顶点上的边方向看是否联通即可。

```cpp
#include <iostream>
#include "cstdio"
#include "cstring"
using namespace std;

int n, m, din[22], dim[22];
bool ans = true;
string a, b;

int main(int argc, char const *argv[])
{
    scanf("%d%d",&n,&m);
    cin>>a>>b;
    for (int i = 0; i < n; i++)
        if (a[i]=='>') din[i+1] = 1;
    for (int i = 0; i < m; i++)
        if (b[i]=='^') dim[i+1] = 1;
    if (din[1] != dim[1]) ans = false;
    if (din[1] == dim[m]) ans = false;
    if (din[n] == dim[1]) ans = false;
    if (din[n] != dim[m]) ans = false;
    if (ans) cout<<"YES";
    else cout<<"NO";
    return 0;
}
```


---

## 作者：yuy_ (赞：4)

### 这里介绍本题的tarjan做法。

我们可以按题意连边，
连边后跑一边tarjan记录一下这个强连通分量的大小，这个大小如果是n*m的话那么整张图就是一个强连通图了。

tarjan在这里不做介绍了。

那么就说说这张图怎么连边。

对于样例二来说：
```
4 6
<><>
v^v^v^

```
这张图是这样的

![](https://cdn.luogu.com.cn/upload/pic/62181.png)

#### 那么只要对一条线上相邻的数字建一条单向边就可以实现。

#### 可以看出来一条线上相邻的关系是这样的：
```cpp
//>方向
for (int j=1;j<m;j++){
    add((i-1)*m+j,(i-1)*m+j+1);
}
//反向
add((i-1)*m+j+1,(i-1)*m+j);
```
```cpp
//v方向
for (int j=i;j<=(n-1)*m;j+=m){
   add(j,j+m);
}
//反向
add(j+m,j);
```
### 建完图后跑一次tarjan即可解决问题。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define LL long long
#define Set(s,v) memset(s,v,sizeof(s))
using namespace std;
inline LL read(){
    LL ans=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=(ans<<3)+(ans<<1)+(ch^48);ch=getchar();}
    return ans*f;
}
struct Edge{
    int next,v;
}edge[1005];
int n,m;
char s[25];
int head[405],cnt;
int dfn[405],low[405],tim,sta[405],top,book[405];

inline void add(int u,int v){
    cnt++;
    edge[cnt].next=head[u];
    edge[cnt].v=v;
    head[u]=cnt;
    return;
}
void tarjan(int u){
    dfn[u]=low[u]=++tim;
    sta[++top]=u;
    book[u]=1;
    for (int i=head[u];i;i=edge[i].next){
        int v=edge[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(book[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        if(top==n*m){
            while(sta[top+1]!=u){
                top--;
            }
            if(top){
                printf("NO\n");
            }else{
                printf("YES\n");
            }
        }else{
            printf("NO\n");
        }
        exit(0);
    }
    return;
}

int main(){
    n=read(),m=read();
    scanf("%s",s+1);
    for (int i=1;i<=n;i++){
        if(s[i]=='>'){
            for (int j=1;j<m;j++){
                add((i-1)*m+j,(i-1)*m+j+1);
            }
        }else{
            for (int j=1;j<m;j++){
                add((i-1)*m+j+1,(i-1)*m+j);
            }
        }
    }
    scanf("%s",s+1);
    for (int i=1;i<=m;i++){
        if(s[i]=='v'){
            for (int j=i;j<=(n-1)*m;j+=m){
                add(j,j+m);
            }
        }else{
            for (int j=i;j<=(n-1)*m;j+=m){
                add(j+m,j);
            }
        }
    }
    tarjan(1);
    return 0;
}
```
## 如果对你有帮助不妨点个赞。

---

## 作者：smydahaoren (赞：1)

这个题我第一次看是 $\texttt{dfs}$ 的题，仔细看一下发现是结论题。



------------
**题目思路：**

结论：所构成矩形的 $4$ 个顶点是联通的，即可完成要求。

证明：因为所构成矩形的 $4$ 个顶点是联通的，所以任何一个点都可以到达 $4$ 个顶点所相连的 $4$ 个边上。也可以从 $4$ 个顶点所相连的 $4$ 个边上到达任何一个点。

举个例子：

[![pi9icKs.png](https://z1.ax1x.com/2023/10/14/pi9icKs.png)](https://imgse.com/i/pi9icKs)

在蓝色方框的联通环上，可以以如图所示的方式到达所有类似浅绿色在方框内的点。



------------
**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10000009;
int m,n,a[N],b[N];
bool OK(int a,int b,int c,int d){
	int cnt;
	if(a==b+1) cnt++;
	if(b==c+1) cnt++;
	if(c==d+1) cnt++;
	if(d==a+1) cnt++;
	if(cnt==3) return 1;
	else return 0;
}
int main(){
	//freopen(" ","r",stdin);
	//freopen(" ","w",stdout);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		char c;
		cin>>c;
		if(c=='>')
		a[i]=0;
		else
		a[i]=2;
	}
	for(int i=0;i<m;i++){
		char c;
		cin>>c;
		if(c=='v')
		b[i]=1;
		else
		b[i]=3;
	}
	if(OK(a[0],b[0],a[n-1],b[m-1])) cout<<"YES";
	else cout<<"NO";
	return 0;
}

```


---

## 作者：JRzyh (赞：1)

太妙了，我只能说，太妙了

$O(1)$ 做法

------------
先放个结论再解释为什么：

输出 YES 当且仅当四个角可以互相到达。

为什么呢？

首先假如四个角不可以互相到达，那么显然答案是 NO 。

假如四个角可以互相到达，那么对于所有边上的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/2og9etke.png)

就像本图的红点，可以到达一个顶点（图中紫点），被一个顶点到达（图中粉点）。

而所有顶点都能互相到达，可以推出，**所有边上的点都能互相到达。**

于是，对于说有内部的点，

![](https://cdn.luogu.com.cn/upload/image_hosting/7gptne4z.png)

就像本图的红点，可以到达一个边上的点（图中橙点），被一个边上的点到达（图中黄点）。

而所有边上的点都能互相到达。可以推出，**所有点都能互相到达。**

综上，输出 YES 当且仅当四个角可以互相到达。

四个角可以互相到达的情况，稍微用脑子想一想应该能想出来，就是最外层四条边的顺序是顺时针或逆时针转圈的。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s1,s2;
int main()
{
	cin>>n>>m;
	cin>>s1>>s2;
	if(s1[0]=='<'&&s1[n-1]=='>'&&s2[0]=='v'&&s2[m-1]=='^')cout<<"YES"<<endl;
	else if(s1[0]=='>'&&s1[n-1]=='<'&&s2[0]=='^'&&s2[m-1]=='v')cout<<"YES"<<endl;
	else cout<<"NO";
    return 0;
}

```

球赞

---

## 作者：KEBrantily (赞：1)

为什么是蓝题，我不理解。

发现总点数很少，最多只有 $400$ 个，可以考虑用 Floyd 处理传递闭包。

直接按给定方向处理出相邻点之间的联通性，然后上 Folyd 就做完了。

```cpp
int main(){
  n=read();m=read();
  scanf("%s",s1+1);scanf("%s",s2+1);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++) 
      id[i][j]=++cnt,dis[cnt][cnt]=1;
  for(int i=1;i<=n;i++){
    if(s1[i]=='>')
      for(int j=1;j<m;j++) dis[id[i][j]][id[i][j+1]]=1;
    else for(int j=m;j>1;j--) dis[id[i][j]][id[i][j-1]]=1;
  } 
  for(int j=1;j<=m;j++){
    if(s2[j]=='^')
      for(int i=n;i>1;i--) dis[id[i][j]][id[i-1][j]]=1;
    else for(int i=1;i<n;i++) dis[id[i][j]][id[i+1][j]]=1;
  }
  for(int k=1;k<=cnt;k++)
    for(int i=1;i<=cnt;i++)
      for(int j=1;j<=cnt;j++)
        if(dis[i][k]&&dis[k][j]) dis[i][j]=1;
  for(int i=1;i<=cnt;i++)
    for(int j=1;j<=cnt;j++)
      if(!dis[i][j]){puts("NO");return 0;}
  puts("YES");return 0;
}
```

---

## 作者：Fan_Tuan (赞：1)

# 题意
有横向和纵向的街道，每个街道只有一个方向，垂直的街道相交会产生一个节点，这样每个节点都有两个方向，
问是否每一个节点都可以由其他的节点到达。
# 思路
~~爆搜 感觉可以搜， 就搜他~~
dfs每个点，记录每个点被访问的次数。如果搜完每个点都被访问了$n * m$次， 输出$YES$, 否则输出$NO$;
# 代码
```c
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 30;

char s[maxn], ss[maxn];
int n, m, vis[maxn][maxn], tot[maxn][maxn];

void dfs(int i, int j) {
	if (i < 1 || i > n || j < 1 || j > m || vis[i][j]) return;  //考虑边界
	++tot[i][j];
	vis[i][j] = 1;
	if (s[i] == '<') dfs(i, j - 1);
	else dfs(i, j + 1);
	if (ss[j] == 'v') dfs(i + 1, j);
	else dfs(i - 1, j);
}

int main () {
	scanf("%d%d", &n, &m);
	scanf("%s%s", s + 1, ss + 1);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) 
			memset(vis, 0, sizeof vis), dfs(i, j);
	int xx = n * m;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
				if (tot[i][j] != xx) {
					puts("NO");
					return 0;
				}
	puts("YES");
	return 0;
}
```


---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF475B)
# 题意

给定 $n$ 条水平的单向街道和 $m$ 条竖直单向的街道，其交点共有 $n \times m$ 个，问这些交点是否都能互相到达。

# 思路

不难发现，任何两个交点都可以通过四个顶点到达。因此，只需判断四点是否连通即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,f1[1000001],f2[1000001],fl;
char s1[1000001],s2[1000001];
signed main(){
    cin>>n>>m>>s1+1>>s2+1;fl=1;
    for(i=1;i<=n;i++)
        if(s1[i]=='>') f1[i]=1;
    for(i=1;i<=m;i++)
        if(s2[i]=='^') f2[i]=1;
    if(f1[1]==f2[m]||f1[1]!=f2[1]||
    f2[1]==f1[n]||f2[m]!=f1[n]) fl=0;
    if(fl) cout<<"YES";
    else cout<<"NO";
    return 0;
}
```


---

## 作者：Sangber (赞：0)

#### 前言
好像没有写 $\text{Floyd}$ 的？  

----
### 题目描述
在一个网格图中，根据输入数据将在相邻的格子之间连边，判断是否有一个点不能到达至少一个点（单向不连通）  

----
### 大体思路
~~数据还蛮小的？~~  
根据输入连边，然后直接跑 $\text{Floyd}$ 即可。

----
### 细节注意事项
~~好像没什么要注意的~~

----
### 参考代码
```cpp
/*--------------------------------
  Code name: SCC.cpp
  Author: The Ace Bee
  This code is made by The Ace Bee
--------------------------------*/
#include <cstdio>
#include <cstring>
#define rg register
const int MAXN = 410;
inline int read() {
	int s = 0; bool f = false; char c = getchar();
	while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
	return f ? -s : s;
}
char rr[25], cc[25];
int r, c, pos[30][30], f[MAXN][MAXN];
int main() {
	r = read(), c = read();
	for (rg int i = 1; i <= r; ++i)
		for (rg int j = 1; j <= c; ++j)
			pos[i][j] = (i - 1) * c + j;
	char rr[30]; scanf("%s", rr + 1);
	char cc[30]; scanf("%s", cc + 1);
	for (rg int i = 1; i <= r; ++i) {
		if (rr[i] == '>')
			for (rg int j = 1; j < c; ++j) f[pos[i][j]][pos[i][j + 1]] = 1;
		else
			for (rg int j = 1; j < c; ++j) f[pos[i][j + 1]][pos[i][j]] = 1;
	}
	for (rg int j = 1; j <= c; ++j) {
		if (cc[j] == 'v')
			for (rg int i = 1; i < r; ++i) f[pos[i][j]][pos[i + 1][j]] = 1;
		else
			for (rg int i = 1; i < r; ++i) f[pos[i + 1][j]][pos[i][j]] = 1;
	}
	for (rg int k = 1; k <= pos[r][c]; ++k)
		for (rg int i = 1; i <= pos[r][c]; ++i)
			for (rg int j = 1; j <= pos[r][c]; ++j)
				if (i != j && j != k && i != k)
					f[i][j] = f[i][j] | (f[i][k] & f[k][j]);
	for (rg int i = 1; i <= pos[r][c]; ++i)
		for (rg int j = 1; j <= pos[r][c]; ++j)
			if (i != j && !f[i][j]) return puts("NO"), 0;
	puts("YES");
	return 0;
}

```
**完结撒花$qwq$**

---

## 作者：封禁用户 (赞：0)

这道题目。。。就是特判嘛。。。

只用判断最外层是不是回路。如果是，则每两个点之间连通。

这份代码为$891ms,0\rm KB,0.42KB$

```cpp
#include<cstdio>
char a[3][22];
int n,m,i,j;
using namespace std;
int main()
{
    scanf("%d%d",&n,&m);
    getchar();
    for (int i=1;i<=2;i++) scanf("%s",a[i]);
    j=1;
    if (a[1][0]=='<'&&a[2][0]=='^') j=0;
    if (a[1][0]=='>'&&a[2][m-1]=='^') j=0;
    if (a[1][n-1]=='<'&&a[2][0]=='v') j=0;
    if (a[1][n-1]=='>'&&a[2][m-1]=='v') j=0;
    if (j) printf("YES\n"); else printf("NO\n");
    return 0;
}
```

---

## 作者：yizimi远欣 (赞：0)

这道题思路有三种：

#### 1.

我们看到 
	
    2 <= n, m <= 20
    
数据范围不是很大，交点大约400，可以试着每个点dfs一次，然后找是否有一次都能到达其他点

#### 2.

有些大佬会说：

这不就是强联通分量水题吗？

所以可以用Tarjan来求

#### 3.

### 主要思路：瞎搞

怎么瞎搞？？

我们可以仔细考虑一下，如果我们除了最外层的边以外，都可以通过最外层边到达各个边的话，那这个图是不是肯定是强联通的？

那如果最外层都不是互联通的话，就肯定不符合题意。

所以我们只需要判断一下最外层的街道是不是连通的就好了。

~~没看懂自己感性理解下~~

所以我只给出第三种解法的代码：（除输入外时间复杂度O(1)）

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define go(i, j, n, k) for (int i = j; i <= n; i += k)
#define fo(i, j, n, k) for (int i = j; i >= n; i -= k)
#define rep(i, x) for (int i = h[x]; i; i = e[i].nxt)
#define mn 22
#define inf 2147483647
#define ll long long
#define ld long double
#define fi first
#define se second
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define bson l, r, rt
//#define LOCAL
#define mod 
#define Debug(...) fprintf(stderr, __VA_ARGS__)
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
//This is AC head above...
int n, m, heng[mn], shu[mn];
char h[mn << 2], s[mn << 2];
int main(){
    n = read(), m = read();
    scanf("%s", h + 1);
    go(i, 1, n, 1){
        heng[i] = h[i] == '<' ? 0 : 1; // 0 -> zuo 1 -> you
    }
    scanf("%s", s + 1);
    go(i, 1, m, 1) {
        shu[i] = s[i] == '^' ? 0 : 1; // 0 -> shang 1 -> xia
    }
    if((heng[1] == 1 && heng[n] == 0 && shu[1] == 0 && shu[m] == 1) || (heng[1] == 0 && heng[n] == 1 && shu[1] == 1 && shu[m] == 0)) 
    {
        puts("YES");
    }
    else
    {
        puts("NO");
    }
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
    return 0;
}
```

---

