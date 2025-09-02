# [ABC385E] Snowflake Tree

## 题目描述

"雪花树"是通过以下步骤生成的树：

1. 选择正整数 $x,y$。
2. 准备一个顶点。
3. 再准备 $x$ 个顶点，并将它们每个都与步骤 2 中准备的顶点相连。
4. 对于步骤 3 中准备的每个 $x$ 个顶点，为其连接 $y$ 个叶子节点。

下图展示了一个 $x=4,y=2$ 的雪花树。在步骤 2、3、4 中准备的顶点分别用红色、蓝色和绿色表示。

![](https://img.atcoder.jp/abc385/b836ca95b1add288731cbe63816da3b1.png)

给定一个有 $N$ 个顶点的树 $T$。顶点编号从 1 到 $N$，第 $i$ 条边（$i=1,2,\dots,N-1$）连接顶点 $u_i$ 和 $v_i$。

考虑删除 $T$ 中零个或多个顶点及其相邻的边，使得剩余图形成为一个雪花树。求必须删除的最少顶点数。在本题的约束条件下，总是可以将 $T$ 转换为雪花树。

## 说明/提示

- $3 \leq N \leq 3 \times 10^5$
- $1 \leq u_i < v_i \leq N$
- 给定图是一棵树
- 所有输入值均为整数

## 样例 #1

### 输入

```
8
1 3
2 3
3 4
4 5
5 6
5 7
4 8```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2
2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1 3
1 2
5 7
6 10
2 8
1 6
8 9
2 7
1 4```

### 输出

```
3```

# 题解

## 作者：yy0707 (赞：4)

本蒟蒻第一次交题解，求过。

赛时打 D 打了半天，看到 E 一眼就秒了。

首先看到这个题，很容易想到对于每一个点，求出以它为中心点的雪花树最多有多少个节点。

令 $x$ 为该节点的度数，$y$ 为所有出边所连向的点中出边的最小值，$ans$ 就为 $n$ 减去所有的 $x\times(y-1)+x+1$ 中的 $\max$ 值。

但很明显这样是错的，因为不一定要把一个点的出边全部选完。

所以我们我们可以把每一个点的所有出边所指向的点按度数排个序，然后每次把贡献最小的那个点丢掉，然后就可以 AC 啦。

时间复杂度 $\Theta(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
size_t n,ans;
vector<size_t>g[300001];
signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}for(int i=1;i<=n;i++){
		sort(g[i].begin(),g[i].end(),[](int a,int b){return g[a].size()<g[b].size();});
		for(int j=0;j<g[i].size();j++){
			ans=max(ans,(g[g[i][j]].size()-1)*(g[i].size()-j)+(g[i].size()-j)+1);
		}
	}cout<<n-ans;
}
```

---

## 作者：Conan15 (赞：4)

这题非常简单，但我赛时看了一眼觉得不太好写就放一边了。\
干完 D 题之后回来一眼切了，怎么评价。

一个比较显然的做法是**枚举中心点**，这里把它叫做 $u$。\
然后观察到可以枚举 $y$ 是多少，然后确定有多少个 $v$ 满足存在边 $(u,v)$ 并且 $deg_v - 1 \geq y$。\
这里 $deg_v$ 表示 $v$ 的度数。

对于一个确定的 $y$，显然把所有 $deg_v - 1 \geq y$ 的点 $v$ 都加进来是不劣的，假设有 $c$ 个这样的点 $v$，那么雪花树上就有 $1 + c + c \times (deg_v - 1) = 1 + c \times deg_v$（$u$ 本身加上 $v$ 数量加上 $v$ 儿子的数量）这么多个点。

然后发现枚举 $u$ 再枚举 $y$ 显然是不可行的。但是 $\geq y$ 这个东西一眼就很后缀和，树状数组维护就好了。

好像所有学长和学弟都写了一个神秘排序？看不懂，我觉得树状数组挺显然的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 15, M = N << 1;
int n, h[N], e[M], ne[M], idx = 0;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int tr[N], deg[N];
void change(int x, int d) {
    for ( ; x ; x -= x & -x) tr[x] += d;
}
int query(int x) {
    int res = 0;
    for ( ; x < N; x += x & -x) res += tr[x];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) h[i] = -1;
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
        deg[u]++, deg[v]++;
    }
    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            change(deg[v], 1);
        }
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            // if (u == 2) cout << deg[v] << ' ' << query(deg[v]) << ' ' <<  1 + query(deg[v]) * 1ll * deg[v] << endl;
            ans = max(ans, 1 + query(deg[v]) * 1ll * deg[v]);
        }
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            change(deg[v], -1);
        }
    }
    printf("%lld\n", n - ans);
    return 0;
}
```

---

## 作者：hwc2011 (赞：2)

这道题比第四题要简单，第四题真是~~太臭了~~。  
考虑以下情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/k6d4xgre.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250) 
假设我们选择红色点位最终雪花树的根，有四个儿子与他相连，每个儿子有分别有 $2$、$4$、$1$、$3$ 个儿子，则：
1. 如果令 $y = 1$，则 $x$ 的最大值为 $4$，此时需要删除 $6$ 个节点。
2. 如果令 $y = 2$，则 $x$ 的最大值为 $3$，此时需要删除 $5$ 个节点。
3. 如果令 $y = 3$，则 $x$ 的最大值为 $2$，此时需要删除 $6$ 个节点。
4. 如果令 $y = 4$，则 $x$ 的最大值为 $1$，此时需要删除 $9$ 个节点。

所以对于这颗雪花树来说，$x = 3$、$y = 2$ 时最优。同时会发现，$y$ 的值会限制 $x$，所以我们要考虑对当前根的所有儿子的儿子的数量统计进数组，但由于我们还要计算上儿子的数量，所以我们在统计是要加 $1$，这时数组里的数其实就和每个儿子所连的边数相同了。然后再排个序，枚举每一个 $y$，这道题就解决了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005],ans;
vector<int>e[300005]; 
signed main(){
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;i++){
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		int tot=0;
		for(auto j:e[i]) a[++tot]=e[j].size();
		sort(a+1,a+1+tot);
		for(int j=1;j<=tot;j++) ans=max(ans,a[tot-j+1]*j+1); //加1是因为还要算上根
	}
	printf("%lld",n-ans);
}
```

---

## 作者：HasNoName (赞：2)

### 思路
不难想到树形 DP。

考虑做换根。

对于每一个节点，统计出它一步能走到的点和两步能走到的点的数量。

对于一个节点，如果一个子树下有超过两层，则必须剪掉。

对于两层以内的点，再对于超过一层的点的数量排序，对于每一个节点，计算砍掉几个一层的子树和二层的子树。

求最小值即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
typedef long long ll;
struct T
{
	int ne,to;
}e[2*N];
int he[N],idx,son[N],sson[N];
int ans=1e9,c[N],n;
void add(int x,int y)//加边函数
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	son[x]++;
	he[x]=idx;
}
void dfs(int x,int fa)//树形DP
{
	int sum=n-1-son[x]-sson[x],top=0;
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		c[++top]=son[y]-1;
	}
	sort(c+1,c+top+1);
	int ssum=0,p=0;
	for(int i=1;i<=top;i++)
		ssum+=c[i];
	for(int i=1;i<=top;i++)
	{
		ans=min(ans,sum+ssum-c[i]*(top-i+1)+p);//计算答案
		ssum-=c[i];
		p+=c[i]+1;
	}
	for(int i=he[x];i;i=e[i].ne)
	{
		int y=e[i].to;
		if(y!=fa)dfs(y,x);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x,y;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		for(int j=he[i];j;j=e[j].ne)
			sson[i]+=son[e[j].to]-1;//二层个数
	dfs(1,0);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：kairuigg (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc385_e)
### 题目大意
定义一棵雪花树是可以通过以下操作产生的树：

1. 选择正整数 $x,y$。
2. 准备一个顶点。
3. 准备 $x$ 个顶点并将这 $x$ 个顶点分别连接到 $2$ 操作中准备的顶点中。
4. 再准备 $x\times y$ 个顶点，对于操作 $3$ 中的每个顶点各连接 $y$ 个节点。

下图是一棵 $x=4$，$y=2$ 的雪花树。

![](Https://img.atcoder.jp/abc385/b836ca95b1add288731cbe63816da3b1.png )

题目将给出顶点数为 $N$ 的树 $T$，顶点编号为 $1$ 到 $N$，第 $i$ $(1\le i<N)$ 条边连接顶点 $u_i$ 和 $v_i$。考虑删除一些顶点，使得题目中所给出的树 $T$ 变成一棵雪花树。求所删除的顶点的最少个数。题目保证数据有解。
### 思路
我们发现删除顶点并不好做，所以我们可以考虑删除完后会剩下多少顶点。我们令在步骤 $2$ 中选择的顶点为 $u$，$siz_i$ 表示点 $i$ 周围有多少个点。若选择 $v_1,v_2,\dots,v_x$ 为操作 $3$ 中所选的点，那么这棵雪花树的 $y$ 就为 $\min{\{siz_{v_1},siz_{v_2},\dots,siz_{v_x}}\}-1$，之所以减一是因为要减去操作 $1$中所选的中心节点。那么我们就可以确定这棵树要剩下 $1+x+x\times y$ 个点。则要删除的点的个数就为 $N-(1+x+x\times y)$ 个。到此，我们就可以通过遍历中心节点 $u$ 以及其周围 $x$ 个节点来确定这棵树。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    vector<vector<int>> g(n+1);
    vector<int> siz(n+1);
    int sum=0;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        siz[u]++,siz[v]++;
    }
    int ans=-1e9-5;
    for(int i=1;i<=n;i++){//选中心节点
        vector<int> st;
        for(auto x:g[i]){//他周围的节点x
            st.push_back(siz[x]-1);
        }
        sort(st.begin(),st.end(),greater<int>());
        for(int j=0;j<st.size();j++){
            if(st[j]){
                //j+1为x的周围节点的数量
                //st则是我们所建的这个树y的值
                //ans的值则表示这棵雪花树节点的最大数量
                ans=max(ans,1+(j+1)*(st[j]+1));
            }
        }
    }
    cout<<n-ans;
    return 0;
}
```
对于题解一点问题的修改，求管理大大给过。

---

## 作者：Red_river (赞：1)

### 题目分析
本题给定了一种类似雪花的树，一个顶点有 $x$ 条边，同时每个直接与其连的点都有且仅有 $y$ 条边就满足条件，问最少删几个点。
### 解题思路
代码思路分析：输入连边的时候，要计入**每个点的度数**接着遍历每一个顶点。对于每个顶点，先统计其相邻顶点的度数情况，将相邻顶点的度数存到数组中，然后对数组进行排序，似乎也可以不用。接下来，循环枚举答案。我们不难发现一个符合条件的 $y$ 一定是第一层循环的点所直接连接的点中的到达的**某一个点的度数减一**，似乎有点绕，但实际上就是所循环的点的**第三层中的某一个**点。同时记得减去过去的那条边，这样才能使答案最大。

对于统计答案，由于排好了序，所以如果以一个点为答案，那么前面的点都要删掉，后面的答案都取当前的答案。具体代码理由详细解释。
### CODE
由于枚举答案的顶点和计算过程中用了排序，所以此代码时间复杂度是 $O(n \log n)$ 的。
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 300005
#define NO printf("No\n")
#define YES printf("Yes\n")

using namespace std;

// 顶点数、一些计数变量、数组等的定义
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];

// 读取整数的函数
void read(int &x)
{
    x = 0;
    int ff = 1;
    char ty;
    ty = getchar();
    while(!(ty >= '0' && ty <= '9'))
    {
        if(ty == '-') ff = -1;
        ty = getchar();
    }
    while(ty >= '0' && ty <= '9')
        x = (x << 3) + (x << 1) + ty - '0', ty = getchar();
    x *= ff;
    return;
}

// 输出整数的函数
void write(int x)
{
    if(x == 0){
        putchar('0');
        return;
    }
    if(x < 0){
        x = -x;
        putchar('-');
    }
    char asd[201];
    int ip = 0;
    while(x) asd[++ip] = x % 10 + '0', x /= 10;
    for(int i = ip; i >= 1; i--) putchar(asd[i]);
    return;
}

// 边的结构体定义，用于构建邻接表
struct lenovo{
    int to,nxt,val;
}v[N * 2];

// 添加边的函数，构建邻接表
void add(int x,int y)
{
    v[++cnt].to = y;
    v[cnt].nxt = head[x];
    head[x] = cnt;
}

signed main()
{
    // 读取顶点数。
    read(n);
    int x,y;
    // 读取树的边信息，构建邻接表并统计顶点度数。
    for(int i = 1; i < n; i++){
        read(x),read(y);
        add(x,y),add(y,x);
        dis[x]++,dis[y]++;
    }
    // 遍历每个顶点。
    for(int i = 1; i <= n; i++){
        cnt = 0;
        // 统计当前顶点相邻顶点的度数并存入vis数组。
        for(int j = head[i]; j; j = v[j].nxt)
            vis[++cnt] = dis[v[j].to];
        // 对vis数组排序。
        sort(vis + 1, vis + 1 + cnt);
        // 计算并更新ans。
        for(int j = 1; j <= cnt; j++){
            ans = max(ans,vis[j] * (cnt - j + 1));
        }//枚举答案并更新最大留下的顶点数。
    }
    // 输出需要删除顶点数的最小值。
    wh(n - 1 - ans);
    return 0;
}
```

---

## 作者：bszhangzheng (赞：1)

比 D 简单多了。  
考虑枚举每一个点做为雪花树的中心，再枚举雪花树有多少个点连向中心点。我们预处理出每个点的度数，显然，与中心点连接的点中，我们会优先选度数大的点。把中心点连接的所有点按度数从大到小排序，所以当 $x=i$ 时，雪花树的大小为 $1+i\times a_i$，其中 $a_i$ 表示排序后数组的第 $i$ 个数的度数，答案取最小值即可。时间复杂度 $O(n\log n)$。  
代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,h[N],cnt,rd[N],now[N],s,ans=1e9;
struct node{int next,to;}a[N<<1];
void add(int x,int y){a[++cnt].to=y,a[cnt].next=h[x],rd[x]++,h[x]=cnt;}
bool cmp(int x,int y){return x>y;}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int x,y,i=1;i<n;i++) cin>>x>>y,add(x,y),add(y,x);
	for(int j=1;j<=n;j++)
	{
		s=0;
		for(int i=h[j];i;i=a[i].next)
		{
			int k=a[i].to;
			now[++s]=rd[k];
		}
		sort(now+1,now+s+1,cmp);
		for(int i=1;i<=s;i++) ans=min(ans,n-1-i*now[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ivan422 (赞：1)

赛后 $1$ 分钟通过，都怪 D 题。

这题反而更简单，只有黄。

我们考虑直接大力是贪心。

深搜，我们可以求出每一个点的邻接点数量 $sz_i$。但是我写完题解后，发现可以直接枚举边，代码也修改了一版。

深搜，再来！

我们这一次是真的求解了。

我们考虑每一个点产生的贡献。

设我们考虑的点为 $p$。

$p$ 每一个邻接点 $v$ 的贡献都是 $sz_v$，但是由于 $v$ 的邻接点有 $p$，所以 $v$ 中可以选出 $sz_v-1$ 个点作为雪花的叶子。

而我们求出的这个值就是**每一个第 $2$ 层节点能提供的雪花叶子的个数**。

剩下的其实就是一个求解 $p$ 点能拉出的最大雪花大小，定义这个为 $f_p$，为了方便，我们设 $p$ 的邻接点个数为 $m$。

我们首先对 $sz_v-1$ 排序，为了防止影响，考虑插入一个 `vector`，定义为 $z_p$。

接着，枚举每一个点作为所选序列最小值。让 $i$ 从 $0$ 开始，那么贡献就是 $(z_{p,i}+1)\times(m-i)$。

我们来解析这个式子。$z_{p,i}+1$ 就是 $p$ 的某一个点的邻接节点 $-1$ 再 $+1$。减 $1$ 减掉了 $p$，加 $1$ 加上了自己。

下一项 $m-i$，其实就是 $i$ 到最后一个邻接点的个数。

我们发现，到这里，这题变成了一个贪心！

转移方法：$f_p=\max(f_p,(z_{p,i}+1)\times (m-i))+1$，别忘了 $p$ 还没算。

最后求真正的答案。

因为 $f_p$ 求的是最多选多少点当雪花，所以我们就可以求最少不选多少点，也就是答案 $ans=\min(ans,n-f_i)$。

此题容易，代码：[链接](https://atcoder.jp/contests/abc385/submissions/60998479)。

---

## 作者：linjinkun (赞：1)

E 明显比 D 简单很多。

设节点 $x$ 的度数 $d_x$。

枚举中心 $z$，然后给 $z$ 的儿子按照 $d_{s_{z,i}}$ 从大到小的顺序排序，因为 $y$ 的取值跟 $z$ 的儿子的度数有关，$s_{z,i}$ 指 $z$ 的第 $i$ 个儿子，然后由于 $x$ 最多是 $d_z$ 那么枚举 $x$（这样时间复杂度为 $O(n)$，不会超时），然后 $y$ 最多是 $\min_{i = 1}^{d_z} d_{s_{z,i}}-1$，因为度数是包含 $z$ 的，所以得减一，然后因为是要求最小的删除数，那么 $y$ 肯定越大越好，所以 $y$ 肯定等于最大的 $y$，也就是 $\min_{i = 1}^{d_z} d_{s_{z,i}}-1$。

时间复杂度 $O(n \log n)$，复杂度瓶颈在排序。

然后就没了……

代码比 D 短多了：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
vector<int>a[N];
int dep[N];
int cmp(int x,int y)
{
	return dep[x]>dep[y];
}
int main() 
{
    int n;
    scanf("%d",&n);
    for(int i = 1;i<n;i++)
    {
    	int x,y;
    	scanf("%d %d",&x,&y);
    	a[x].push_back(y);
    	a[y].push_back(x);
    	dep[x]++;
    	dep[y]++;
	}
	int minn = 1e9;
	for(int i = 1;i<=n;i++)
	{
		sort(a[i].begin(),a[i].end(),cmp);
		int x = 0;
		for(int j = 0;j<a[i].size();j++)
		{
			x++;
			int y = dep[a[i][j]]-1;
			minn = min(minn,n-1-x-x*y);
		}
	}
	printf("%d",minn);
    return 0;
}
```

---

## 作者：wangyizhi (赞：1)

**题目传送门：[洛谷](https://www.luogu.com.cn/problem/at_abc385_e) || [AtCoder](https://atcoder.jp/contests/abc385/tasks/abc385_e)**

### 闲话

![什么石粒不用我多说了](https://cdn.luogu.com.cn/upload/image_hosting/clxvyy12.png)

## 题目大意

给定一颗树，删掉一些节点使得剩余的那颗树根节点的子树高度都为 $2$（根节点为 $1$）且同构（就是儿子的儿子数要相同且儿子的儿子没有儿子），求需删去的最少的节点数。节点数 $3\le N\le 3\times10^5$。

## 题目分析

不是 dp 就是贪心。

好像 dp 有点难那我们就贪心。

由题意得我们只用考虑这棵树的三层。考虑令点 $u$ 为根，则问题就变成了让 $u$ 的儿子的儿子个数相同且和最大。首先肯定有一颗子树是不用删的，否则肯定不是最优。如果我们这颗子树不用删，那比它小的要全删掉，比它大的要和它一样大。所以留它答案就是 这颗子树的大小 乘上 大小大于等于它的子树数。这样我们只要`sort`一遍，然后就可以 $O(1)$ 求出每颗子树产生的答案。

最后取最大值就做完了。

枚举根节点的复杂度是 $O(n)$，枚举子树的复杂度的和也是 $O(n)$（因为每条边都只被两边的节点遍历了，而边的条数又是 $O(n)$ 的），`sort`的复杂度和是 $O(n\log n)$，所以总复杂度 $O(n \log n)$。

## AC Code

```cpp
// by wangyizhi(571247)
// link: https://atcoder.jp/contests/abc385/submissions/60992420
// 不要试图复制哦！
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=3e5+1;
vector<int> g[N];
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
	{
		int res=0;
		vector<int> s;
		for(int j:g[i]) s.push_back(g[j].size()-1); // 要去掉根节点算大小
		sort(s.begin(),s.end());
		for(int j=0,l=s.size();j<l;j++)
			res=max(res,l-j+s[j]*(l-j));
		ans=max(ans,res+1);
	}
	cout<<n-ans;
	return 0;
}
```

完结撒花！

---

## 作者：Dtw_ (赞：0)

# 题目大意
定义一棵树，有 $1$ 个根节点，根节点有 $x$ 个儿子，这 $x$ 个儿子都有 $y$ 个孙子。

给你一棵树，求最少删掉多少个节点使得它符合要求。
# Solution
考虑深度为 $3$。

直接枚举根节点是啥，然后把他的所有儿子全跑出来，之后考虑每个儿子有多少儿子，我们要使得删掉的最小，就是留下来的最多，那可以留多少呢？就是按他们的儿子数量排序，然后选他的儿子数量个，比他儿子多的一定可以选，比他少的就不能选。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 3e5 + 10, inf = 0x3f3f3f3f;

int n, a[N], e[N];

vector<int> G[N];

int main()
{
    fst
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) a[i] = G[i].size();
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < G[i].size(); j++) e[++cnt] = a[G[i][j]] - 1;
        sort (e + 1, e + cnt + 1);
        for (int j = 1; j <= cnt; j++)
        {
            if (e[j] == 0) continue;
            res = max(res, 1 + (cnt - j + 1) + (cnt - j + 1) * e[j]);
        }
    }
    cout << n - res;
    return 0;
}
```

---

## 作者：Toorean (赞：0)

题意：给出一个 $N$ 个点的树，求其一个最大深度为 $3$ 的子树，使其所有深度为 $2$ 的节点的子节点数相同。最大化这个子树的点数。

分析：记录每个点的度数，记录为 $deg_i$。枚举所有点 $u$ 作为子树的根节点，然后我们考虑如何快速维护以这个点为根，最大的点数。

假定已经确定子树中第二层的点集为 $S$，由于要求 $S$ 中所连第三层点数相等，故对于每个点最多可以选择 $\min\limits_{x\in S}\{deg_x-1\}$ 个作为第三层点数。如若选择的点数 $k$ 超过这个值，则必存在 $x\in S$，$deg_x-1<k$，不满足题设。

因此，我们在确定子树根节点 $u$ 后，枚举第二层节点个数 $j$，利用贪心，即可更新当前答案。

Code:
```cpp
for (int i = 1; i <= n; i ++) {
    vector <int> t;
    for (auto to : g[i])  t.push_back (cnt[to] - 1);
    sort (t.begin (), t.end ());
    int siz = t.size ();
    for (int j = 1; j <= siz; j ++) 
        ans = min (ans, n - (j + 1 + j * t[siz - j])); 
}
```

时间复杂度分析：$N$ 个节点的树有 $N-1$ 条边，度数和为 $2N-2$，循环相连点为 $\mathcal O(N)$ 级，排序为 $\mathcal O(N\log N)$ 级。故总时间复杂度为 $\mathcal O(N\log N)$。

---

