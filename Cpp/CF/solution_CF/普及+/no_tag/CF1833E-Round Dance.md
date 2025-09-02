# Round Dance

## 题目描述

$ n $ people came to the festival and decided to dance a few round dances. There are at least $ 2 $ people in the round dance and each person has exactly two neighbors. If there are $ 2 $ people in the round dance then they have the same neighbor on each side.

You decided to find out exactly how many dances there were. But each participant of the holiday remembered exactly one neighbor. Your task is to determine what the minimum and maximum number of round dances could be.

For example, if there were $ 6 $ people at the holiday, and the numbers of the neighbors they remembered are equal $ [2, 1, 4, 3, 6, 5] $ , then the minimum number of round dances is $ 1 $ :

- $ 1 - 2 - 3 - 4 - 5 - 6 - 1 $

 and the maximum is $ 3 $ : - $ 1 - 2 - 1 $
- $ 3 - 4 - 3 $
- $ 5 - 6 - 5 $

## 样例 #1

### 输入

```
10
6
2 1 4 3 6 5
6
2 3 1 5 6 4
9
2 3 2 5 6 5 8 9 8
2
2 1
4
4 3 2 1
5
2 3 4 5 1
6
5 3 4 1 1 2
5
3 5 4 1 2
6
6 3 2 5 4 3
6
5 1 4 3 4 2```

### 输出

```
1 3
2 2
1 3
1 1
1 2
1 1
1 1
2 2
1 2
1 1```

# 题解

## 作者：guanyf (赞：10)

### 题意
- 有 $n$ 个人在连成若干快跳舞，每个人只知道左边或右边的一个人。现在要求出块的最小值与最大值。

- $2 \le n \le 2 \times 10^5$

### 思路
看到块我们就可以联想到一种数据结构：并查集。对于每个相邻的人建一条边，连成一块。最终块的数量 $sz$ 就是块的最大值。用 $cnt$ 记录度为 $1$ 的点的数量。由于每两个度为 $1$ 的点都可以合成一块，最终还剩下一块，并且 $cnt$ 还可能等于 $0$，因此块最少的数量就是 $\min(sz,sz-\frac{cnt}{2}+1)$。

#### 代码
```cpp
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, a[MAXN], fa[MAXN], du[MAXN], cnt;
set<int> st;
map<pair<int, int>, bool> vis;
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    cin >> n, st.clear(), cnt = 0, vis.clear();
    for (int i = 1; i <= n; i++) {
      cin >> a[i], fa[i] = i, du[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      int u = i, v = a[i];
      fa[find(u)] = find(v);
      !vis[{u, v}] && (du[u]++, du[v]++);
      vis[{u, v}] = vis[{v, u}] = 1;
    }
    for (int i = 1; i <= n; i++) {
      st.insert(find(i));
      cnt += (du[i] == 1);
    }
    cout << min(st.size(), st.size() - cnt / 2 + 1) << ' ' << st.size() << '\n';
  }

  return 0;
}
```


---

## 作者：sz_jinzikai (赞：6)

[题目传送门](/problem/CF1833E) &[CF 传送门](//codeforces.com/problemset/problem/1833/E)
# 思路
首先，最大值很好求，我们只要并查集一次，看看有多少连通块即可，我们现在设连通块的个数是 $sum$。算完了最大值，我们看看最小值改怎么求。我们如果想要得到最小值，那就可以把所有不是环的连通块（其实就是链）连成一个环即可。一条链的两端的度肯定是 $1$，所以，我们设 $cnt$ 为所有度为 $1$ 的点的数量，这样，答案就出来了，是 $\min(sum,sum-\frac{cnt}2+1)$。
# 代码
```cpp
//CF1833E
# include <bits/stdc++.h> //万能头 
using namespace std;
typedef pair <int, int> pii; //简写
int t, n, a[200005], f[200005], cnt, du[200005], sum;
map <pii, bool> mp;
int find (int x) { //并查集认爹函数，不用说了吧（
	return x == f[x] ? x : f[x] = find (f[x]);
}
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		cnt = sum = 0, mp.clear (); //多组数据要归零
		for (int i = 1; i <= n; ++ i)
			f[i] = i, du[i] = 0; //还要清空
		for (int i = 1; i <= n; ++ i)
			if (! mp[ {i, a[i]}] && ! mp[ {a[i], i}]) { //判断重边
				f[find (a[i])] = find (i); //并集
				++ du[a[i]], ++ du[i]; //度加 1
				mp[ {i, a[i]}] = mp[ {a[i], i}] = 1; //把这条边标记了
			}
		for (int i = 1; i <= n; ++ i)
			if (find (i) == i) //找到一个自己是自己的爹，就是找到一个新的连通块
				++ sum; //连通块加 1
		for (int i = 1; i <= n; ++ i)
			if (du[i] == 1) //找到度为 1 的点
				++ cnt; //计数器加 1
		cout << min (sum, sum - cnt / 2 + 1) << ' ' << sum << '\n';
	}
	return 0; //结束程序
}
```

---

## 作者：Coffee_zzz (赞：6)

### 分析

首先分析最大值。

想让圆形舞的数量尽可能多，其实就是不添加其他边，直接算连通块的数量。

再来分析最小值。

让圆形舞的数量尽可能少，就是让联通块的数量尽可能少。对于一个环上的所有点，已经不可能再连其他边，此时它必须作为一个单独的连通块。对于不在环上的点，可以组合起来构成一个大的连通块。

若存在不在环上的点，最小值就等于环的数量加 $1$；  
若不存在不在环上的点，最小值就等于环的数量。

于是这题就转化为了求连通块的数量和环的数量，套模板即可。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int N=2e5+5;
int ch[N][3],cnt,pos;
bool vis[N];
bool dfs(int u){
	if(vis[u]) return 0;
	vis[u]=1;
	if(ch[u][1]) dfs(ch[u][1]),dfs(ch[u][0]);
	else if(ch[u][0]) dfs(ch[u][0]);
	return 1;
}
int check(int u,int f,int k){
	if(vis[u]) return -1;
	vis[u]=1;
	if(f==-1){
		if(ch[u][1]==0) return 0;
		return check(ch[u][1],u,u);
	}
	else{
		if(ch[u][1]==0) return 0;
		int p=1;
		if(ch[u][p]==f) p=p^1;
		if(ch[u][p]==k) return 1;
		return check(ch[u][p],u,k);
	}
}
void solve(){
	int n=read(),u,flag,qwq=0;
	cnt=0,pos=0;
	for(int i=1;i<=n;i++){
		u=read();
		if(ch[u][0]!=i&&ch[u][0]) ch[u][1]=i;
		else ch[u][0]=i;
		if(ch[i][0]!=u&&ch[i][0]) ch[i][1]=u;
		else ch[i][0]=u;
	}
	for(int i=1;i<=n;i++) if(dfs(i)) cnt++;
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=n;i++){
		flag=check(i,-1,i);
		if(flag==1) pos++;
		if(flag==0) qwq=1;
	}
	cout<<pos+qwq<<' '<<cnt<<'\n';
	for(int i=1;i<=n;i++) ch[i][0]=ch[i][1]=vis[i]=0;
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1833E)    
一眼出结论的简单题。       
~~我的解法好像是题解里最复杂的。~~
## 题意
$n$ 个人围成若干个环。现在给出每个人两侧其中一个人，求根据这些信息最多和最少能围成多少个环。      
## 解法
我们可以把相邻信息抽象成一个无向图。     
那么，最多的环数显然就是图的连通块个数。    
那么最少的怎么求呢？    
如果需要让环数最少，那么我们需要把环连接起来，如样例中第 $1$ 组：   
这是我们建好的原图：   
![](https://cdn.luogu.com.cn/upload/image_hosting/8ye07yb4.png)    
我们发现，这 $6$ 个点均只能找到一个相邻的点，所以我们可以进一步配对。    
我们先把 $1$ 和 $5$ 连接，再连接 $6$ 和 $3$，那么我们的图变成了这样：   
![](https://cdn.luogu.com.cn/upload/image_hosting/z4c2b48a.png)    
可以发现，我们建好后的图仍然符合题意，所以这就算是一个配对正确的图。   
如果我们一开始连接了 $1$ 和 $6$，又连接了 $6$ 和 $4$，我们的图就变成了：    
![](https://cdn.luogu.com.cn/upload/image_hosting/68ytyn7z.png)     
我们发现，点 $6$ 存在 $3$ 个相邻的点，所以这张图不算是一个配对正确的图。   
我们的第一张图配对是正确的且形成的连通块数量最少，所以结果是 $1$。   
我们观察以上图，发现：    
- 只有度为 $1$ 的点才可以进行配对，且配对时必须两个连通块都至少有 $1$ 个可以进行配对的点。    

那么，我们预处理出每个连通块一共有多少个可进行配对的点，再降序排序配对即可。     
时间复杂度 $O(N\log N)$，$N=\sum n$，瓶颈在排序上。     
[CODE](https://www.luogu.com.cn/paste/xsf1vmr1)

---

## 作者：wuzijie (赞：1)

## 题面解释：
$t$ 组数据，每组有 $n$ 个人，每个人知道自己相邻的人，求圈数量的最大值和最小值。

## 思路分析：
使用并查集，对于已知相邻的人若不在一棵树上则进行合并。

最终合成后所有在一起的人一定是不能分开的，即此时块数为最大值。

关于最小值，我们可以把落单的人和在一起，即把链连成环。我们统计有两个人及以上的块的个数，若还有剩余的人，则再加 $1$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,cnt,rcnt,cnt2,n,a[N],f[N],sz[N];
int find(int x) {return f[x]=(f[x]==x?x:find(f[x]));}
signed main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		cnt=n,rcnt=0;
		for(int i=1; i<=n; i++)
			f[i]=i,a[i]=0,sz[i]=1;
		for(int y=1,x,rx,ry; y<=n; y++) {
			scanf("%d",&x);
			a[x]=y,rx=find(x),ry=find(y);
			if(rx==ry&&(rx==y||ry==x)&&(sz[rx]>2)&&(a[x]!=y||a[y]!=x))rcnt++;
			if(rx!=ry)cnt--,f[rx]=ry,sz[ry]+=sz[rx],sz[rx]=0;
		}
		printf("%d %d\n",rcnt+(rcnt!=cnt),cnt);
	}
	return 0;
}
```

谢谢！

---

## 作者：Zctf1088 (赞：1)

[原题](https://www.luogu.com.cn/problem/CF1833E)

### 思路

可以用 dfs 求出联通块的数量存在 $tot$ 中，并且在 dfs 的过程中顺便用一个 $flag$ 数组标记满足如下条件的联通块：

- 成环且节点数大于 $2$。

然后统计满足如上条件的联通块的数量，存在 $cnt$ 中。

最大值：

就是联通块的数量就是 $tot$。

最小值：

如果 $cnt = tot$，最小值为 $tot$。

如果 $cnt \ne tot$，最小值为 $cnt+1$。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
int n;
int a[N];
vector<int> G[N];
int vis[N];
int flag[N]; 

int tot;
int inn;
void dfs(int last, int x) { // 求联通块的数量 
	vis[x] = tot;
	for (int y : G[x]) {
		if (vis[y] == 0) {
			dfs(x, y);
		}
		if (y != last && y == inn) {
			flag[tot] = 1;
		}
	}
} 

void init() {
	memset(vis, 0, sizeof(vis));
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i < N; i++) {
		G[i].clear();
	}
	tot = 0;
}

int main() {
	int q;
	scanf("%d", &q);
	while (q--) {
		init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]); 
			G[i].push_back(a[i]);
			G[a[i]].push_back(i);
		}
		
		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0) {
				inn = i;
				tot++;
				dfs(0, i);
			}
		}
		
		int cnt = 0; 
		for (int i = 1; i <= tot; i++) {
			if (flag[i] == 1) {
				cnt++;
			}
		}
		
		if (cnt == tot) {
			printf("%d %d\n", tot, tot);
		} else {
			printf("%d %d\n", cnt + 1, tot);
		}
	}
	
	return 0;
}
```


---

## 作者：banned_gutongxing (赞：0)

## 思路分析

一道很好的带权并查集。

记录：$circle_i$ 表示 $i$ 的并查集中是否已经出现了环，$sz_i$ 表示 $i$ 的并查集的大小。

最多的肯定是连通块的数量，最少的只需要让不是环的相连即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+10;
//DSU
int T,n,near[MAXN];
bool circle[MAXN];
int fath[MAXN],sz[MAXN];
int get_father(int x){
	if(fath[x]==x) return x;
	return fath[x] = get_father(fath[x]);
}
void clear(){
	for(int i = 1;i<=n;i++){
		fath[i] = i;
		circle[i] = 0;
		sz[i] = 1;
	}
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		clear();
		for(int i = 1;i<=n;i++){
			scanf("%d",near+i);
		}
		for(int i = 1;i<=n;i++){
			int fn = get_father(near[i]);
			int f = get_father(i);
			if(f!=fn){
				fath[fn] = f;
				circle[f] = circle[f]|circle[fn];
				sz[f] += sz[fn];
			}else{
				if(near[near[i]]!=i) circle[fn] = 1;
			}
		}
		int sum_circle = 0,sum = 0;
		for(int i = 1;i<=n;i++){
			if(get_father(i)==i){
				sum++;
				if(circle[i]&&sz[i]!=2){
					sum_circle++;
				}
			}
		}
		printf("%d %d\n",min(sum,sum_circle+1),sum);
	}
	return 0;
}
```

---

## 作者：BLX32M_10 (赞：0)

### 题目大意

给你一些环和链，你可以将链首尾相接或者连接两条链，求使所有连通块变为环后可能的连通块最小数量或最大数量。

### 题解

这题我一看就知道要求出总环数和总链数。

发现连通块最小数量其实就是将所有链合并后首尾相连形成的大环再加上环的数量。记得判断没有链的时候。

至于连通块最大数量，就是将所有的链都变为独立的环，再加上环的个数。

因为是一条链，蒟蒻认为直接写一个循环就好了，没必要写 `dfs`。

### 警戒后人

但是，学习我这种做法的需要考虑起始点在链中间的情况，于是在寻找完成后需要将整条链都设为遍历过。

`ri` 是环数，`ch` 是链数。

```cpp
#include <bits/stdc++.h>
using namespace std;
set <int> edg[200005];
bool vis[200005];
void cl(int i)
{
    vis[i] = 1;
    for (auto j : edg[i])
        if (!vis[j])
            cl(j);
}
signed main()
{
    int t, n, x, ch, ri;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            edg[i].clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &x);
            edg[x].insert(i);
            edg[i].insert(x);
        }
        memset(vis, 0, n + 2);
        ch = ri = 0;
        int j, lst;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                j = i, lst = 0;
                while (!vis[j])
                {
                    vis[j] = 1;
                    for (auto k : edg[j])
                    {
                        if (k != lst)
                        {
                            lst = j, j = k;
                            break;
                        }
                    }
                }
                if (j == i)
                    ri++;
                else
                    ch++;
                cl(i);
            }
        }
        printf("%d %d\n", (ch > 0) + ri, ch + ri);
    }
    return 0;
}
```

---

## 作者：LengthCheng (赞：0)

# **蒟蒻的第三篇题解**

## [>> CF1833E Round Dance](https://www.luogu.com.cn/problem/CF1833E)

## **题目分析**

考虑在相邻的人之间连一条无向边，不难发现，连出来的图由一个或几个连通块组成。

接下来思考构造出的图对于题目的意义，显然，每个点的度数代表了这个人已经确定的邻居数量。因此，我们不难得到：

+ 若一个连通块内点的度数都为二，即构成一个环，则这个连通块对答案的贡献已经确定为一。

+ 若一个连通块内存在度数为一的点，为了保证每个点度数都为二（即每个人都有两个邻居），它一定要与其它连通块相连。

+ 特别的，若一个连通块内度数为一的点的数量大于一（实际上，一个连通块内最多存在两个这样的点），那么这个连通块可以与自己相连。

结合上述分析，以及贪心的思想，我们可以分别求出可构成环的数量的最大值和最小值：

+ 要使环数尽可能多，应该使所有存在两个度数为一的点的联通块与自己相连，其余不成环的连通块两两相连。

+ 反之，要使环数尽可能少，应该使所有不成环的连通块连成一个大环。

## **代码实现**

在建图过程中预处理出每个点的度数。

需要注意的是，邻居的概念是双向的，这意味着图中不存在重边，计算度数时也不应重复计算。

接着遍历每个连通块，通过连通块中点的度数可以判断每个连通块的性质，并计算答案即可。

ps：**多测不清空，爆零两横泪**

### **code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int f[N];
int ver[N*2],nxt[N*2],head[N],idx;
int dg[N];
bool vst[N];
void add(int x,int y)
{
	ver[++idx]=y;
	nxt[idx]=head[x];
	head[x]=idx;
}
void dfs(int x,int &p)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(vst[y])
		{
			continue;
		}
		vst[y]=1;
		if(dg[y]<2)
		{
			p++;
		}
		dfs(y,p);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--)
	{
		int n,tot=0,minn=0,maxn=0,cp=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			int x;
			scanf("%d",&x);
			f[i]=x;
			if(f[x]==i)
			{
				continue;
			}
			dg[x]++,dg[i]++;
			add(x,i);
			add(i,x);
		}
		for(int i=1;i<=n;++i)
		{
			int p=0;
			if(!vst[i])
			{
				vst[i]=1;
				if(dg[i]<2)
				{
					p++;
				}
				dfs(i,p);
				if(p)
				{
					if(p==2)
					{
						cp++;
						tot++;
					}
					else
					{
						tot++;
					}
				}
				else
				{
					maxn++,minn++;
				}
			}
		}
		maxn+=cp+(tot-cp)/2,minn+=tot==0 ? 0 : 1;
		printf("%d %d\n",minn,maxn);
		for(int i=1;i<=n;++i)
		{
			head[i]=0;
			dg[i]=0;
			vst[i]=0;
			f[i]=0;
		}
	}
}

```

---

## 作者：BFSDFS123 (赞：0)

零智商题。

考虑到将所有的“相邻”关系改为两个点之间连一条边。

画几个图后，不难发现，可以连成的最大值，一定是连通块的个数。

如何证明？如果两个人在一个连通块内，说明他们一定在一个圈里。为了使最大值尽量大，则同一个圈里的人需要尽量少，则只让连通块里的人在一个圈里一定最优。

如何求最小值？

首先为了使围成的圈数为最小值，我们需要尽量将一堆人塞到一个圈里。但是如果有三个及三个以上的人围成了一个环，那他们就必须单独作为一个圈。则可以围成的圈数就是所以已经形成的环加上可以通过连接未成环的人而形成的环的个数（即 $0$ 或 $1$）。

如何计算？

不难发现，我们可以使用并查集。用并查集我们可以轻松求出连通块个数。而且在 merge 的时候，我们只要判断两个点是否已经在同一集合内，就可以判断有几个环了。

记得特判一下两个点互相连的情况。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2e5+10;

int fa[Maxn];
int n;
int cnt=0;
int get(int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	return fa[x]=get(fa[x]);
}
void merge(int x,int y)
{
	int gx=get(x),gy=get(y);
	if(gx!=gy)
	{
		fa[gy]=gx;
	}else{
		cnt++;
	}
}
int Ar[Maxn];
void work()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Ar[i]);
		merge(i,Ar[i]);
	}
	
	int min,max=0;
	for(int i=1;i<=n;i++)
	{
		if(fa[i]==i)
		{
			max++;
		}
	}
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	
	for(int i=1;i<=n;i++)
	{
		if(i==Ar[Ar[i]])
		{
			continue;
		}
		merge(i,Ar[i]);
	}
	if(cnt<max) cnt++;
	cout<<cnt<<" "<<max<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		work();
	}
	return 0;
}

```

---

## 作者：ForgotDream_CHN (赞：0)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17425890.html)

赛后三分钟做出来的。

## 思路

对于最大值，我们可以用并查集维护连通性，将题目中给出的所有人与其知道的邻居合并起来，那么根据贪心的思想，最大的可能的值就是此时并查集中联通块的个数。

而最小值要麻烦一些。首先对于每个人 $i$，如果他记得的邻居 $j = a_i$ 所记得的邻居 $k = a_j$ 不是他自己的话，那么 $j$ 就是确定的，因为 $j$ 的两个邻居 $i$ 与 $k$ 都已知。

当一个连通块中所有人都已确定时，这个连通块有唯一确定的组成。反之，当一个联通块中存在不确定的人时，一定可以找出一种方法将其与其他的不确定的连通块合并起来，组成一个更大的联通块。

在求最小值时，我们先找出所有不确定的连通块的个数 $cir$，再找出总的连通块个数 $cnt$，那么不难看出最小个数就为 $cnt - cir + 1$。

但是还有一个小坑就是，当 $cir = 0$，即所有连通块都确定时，答案显然为 $cnt$ 而不是 $cnt + 1$。

## 代码

```cpp
int n;
std::cin >> n;

std::vector<int> a(n);
DSU dsu(n);
int cir = 0;
for (int i = 0; i < n; i++) {
  std::cin >> a[i];
  a[i]--;
  dsu.merge(i, a[i]);
}

std::vector<bool> det(n);
for (int i = 0; i < n; i++) {
  if (i != a[a[i]]) {
    det[a[i]] = true;
  }
}

std::vector<bool> used(n);
for (int i = 0; i < n; i++) {
  if (!det[i]) {
    used[dsu.find(i)] = true;
  }
}

cir = std::count(used.begin(), used.end(), true);

int cnt = 0;
for (int i = 0; i < n; i++) {
  if (dsu.find(i) == i) {
    cnt++;
  }
}

std::cout << std::min(cnt, cnt - cir + 1) << " " << cnt << "\n";
```

---

## 作者：arrow_king (赞：0)

## 简要题意

有一张图，由若干（可能为 $0$）个链和若干（可能为 $0$）个环组成。链首尾相连可以组成环。问这张图最多和最少有几个环。

## 思路

~~感觉简要题意就是做法~~

对图做 DFS，计算图中链的数量和环的数量。设链的数量为 $a$，环的数量为 $b$，则最大值就是 $a+b$，最小值就是 $a+\min(b,1)$。

然而原题意和简要题意好像并不是一码事啊。

原题意是有 $n$ 个点组成了若干个环。现在知道每个点旁边的任意一个点，要求这个图中环的数量最大值和最小值，但怎么就变成了一个链呢？为什么不能是别的（比如说，一个树）？

其实显然，因为最后能形成环，所以这个信息不完全的图中只能有环和环的一部分，即链。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,a[200005],vis[200005];
vector<int> g[200005];
map<int,int> mp[200005];
int dfs(int u,int fa) {
	vis[u]=1;
	int ans=0;
	for(int i=0;i<g[u].size();i++) {
		if(g[u][i]==fa) continue;
		if(vis[g[u][i]]==1) return 1;
		int tmp=dfs(g[u][i],u);
		if(tmp==0) continue;
		else ans=1;
	}
	return ans;
}
int main() {
	t=read();
	while(t--) {
		for(int i=1;i<=n;i++) {
			g[i].clear();
			mp[i].clear();
			vis[i]=0;
		}
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			if(!mp[i].count(a[i])) g[i].push_back(a[i]);
			if(!mp[a[i]].count(i)) g[a[i]].push_back(i);
			mp[i][a[i]]=mp[a[i]][i]=1;
		}
		int ctot=0,ltot=0;
		for(int i=1;i<=n;i++) {
			if(!vis[i]) {
				int x=dfs(i,0);
				if(x==1) ctot++;
				else ltot++;
			}
		}
		int ians=ctot,aans=ctot+ltot;
		if(ltot!=0) ians++;
		printf("%d %d\n",ians,aans);
	}
	return 0;
}

```

---

## 作者：Geoyster (赞：0)

# CF1833E Round Dance

比赛做出来了，但是看别人都是直接跑图，这里提供一种并查集做法。

## 题目大意

$n$ 个人中，若干人（$\geq 2$）组成一个环（或是两个人），现在知道一个人的一条与他人的相邻关系（一般来说有左右两人相邻），问最少和最多有多少组。

## 思路

显然知道相邻关系可以当作图来看待，但是我们只要知道最终的可能组数，不妨考虑并查集。

先当作最多组数考虑。只要将所有相邻关系合并，最后数组数就行了。

再考虑最少组数。即将能和并的尽量合并。那么如何确定一个组能否去合并呢？以下分两种情况

1. 组内人数 $\geq 3$ 当边数等于点数时形成环，在题目背景下即相邻关系数等于组内人数。不能再合并。不形成环则可以。

2. 组内人数 $=2$ 无论如何都可以与其他组合并，应为确定相邻关系至多一条。

然后将能和并的看成一组即为最小组数。

## 实现

[并查集](https://oi-wiki.org/ds/dsu/)，其实基本都是套模板，判断构成环只要看要连接的两点是否已在一个根节点下，是则有环，反之无环。然后重边也要特判一下。关于不可合并组，我是在找到环后就记录，如果这个值比总组数小则必然又可以构成一个可合并的组。

## AC CODE

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct dsu{
	int fa[200005],n;
	void ini(){
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int find(int a){
		return fa[a]==a?a:fa[a]=find(fa[a]);
	}
	int cnt(){
		int res=0;
		for(int i=1;i<=n;i++) if(fa[i]==i) res++;
		return res;
	}
};
void solve(){
	cin>>n;
	dsu d; d.n=n; d.ini();
	int mn=0,mx=n;
	map<pair<int,int>,bool> exist;
	for(int i=1;i<=n;i++){
		int u; cin>>u;
		if(exist[make_pair(u,i)]) continue;
		exist[make_pair(i,u)]=1;
		int t1=d.find(u),t2=d.find(i);
		if(t1==t2) mn++;
		else d.fa[t1]=t2;
	}
	mx=d.cnt();
	if(mx>mn) mn++;
	printf("%d %d\n",mn,mx);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析

**【总体思路】**

这道题就是让你求将一些环（单独一个点也看做环），将能融合的环连起来（也可以不连），最后剩下的不相交的环数量的最大最小值。

最大值很好判断啊，肯定就是原来环的数量，因为一旦有两个环融合，总的个数就会减一。而最小值就和最大值相反，我们需要将能融合的环尽量融合。

**【判断环是否能够融合】**

因为题目要求一个点的出度只能是 $2$，而一个简单环中每个点的出度又恰好是二，所以我们需要将这些环再简化一下。不难发现，任意两个点之间，只要有两条以上的连边，我们都可以将其简化橙一条连边，因为任意一条连边都可以使这两个点连通，即满足跳舞的需求。所以在构建环的时候，我们使用并查集，将最后简化地可能不是环的“环”看做环。那么，判断两个最简“环”是否能够融合，我们只需要看它们是不是真的环即可。如果这个“环”是真正的环，那么简化时候的连边的数量应该是等于这个环中点的数量的。如果有某一个“环”不是真正的环，我们就可以使所有的不是环的“环”融合起来了。

## 代码
```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
const int N=2e5+10;
int fa[N],dian[N],bian[N];
//并查集，环中点的数量，边的数量
int find(int x)
{
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void get(int x,int y)//连边
{
	fa[x]=y;
	if(x!=y)
	dian[y]+=dian[x],dian[x]=0,bian[y]+=bian[x],bian[x]=0;
}
int a[N];
bool vis[N];
map<int,map<int,int> > mp;
signed main()
{
	cin>>t;
	while(t--){
		mp.clear();
		int idx=0;
		memset(vis,0,sizeof(vis));
		cin>>n;
		for(int i=1;i<=n;i++) //初始化fa[i]=i,dian[i]=1,bian[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			int x=find(i),y=find(a[i]);
			if(!mp[a[i]][i]&&!mp[i][a[i]])//如果这两个点之间没有出现过连边，该“环”中的边的数量加一
				mp[a[i]][i]=mp[i][a[i]]=1,bian[y]++;
			get(x,y);
		}
		bool bo=0;//标记是否存在不是环的“环”
		int ans1=0,ans2=0;//最小值，最大值
		for(int i=1;i<=n;i++)
		{
			int x=find(i);
			if(vis[x]) continue;
			else 
			{
				vis[x]=1;
				if(bian[x]==dian[x]) ans1++,ans2++;//是环
				else ans2++,bo=1;//不是环
			}
		}
		if(bo) ans1++;//所有不是环的“环”都可以相互连接起来
		cout<<ans1<<" "<<ans2<<endl;
	}
}
```


---

