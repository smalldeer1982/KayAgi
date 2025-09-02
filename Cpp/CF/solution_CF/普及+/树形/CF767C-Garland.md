# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# 题解

## 作者：maniac！ (赞：17)

###  既然还没有题解，那我就滋磁一下QwQ 
大佬们都忙着刷难题，我太蒟了都不会，只能在这悄悄写篇题解（小声bb）

由于一些奇怪的原因，我就不皮了，下面我们直接进入正题ヽ(￣▽￣)و

首先我们来解析题意，这道题其实就是要将一颗树的边分成三棵子树，使每一颗子树的权值和大小相等，输出要断开的边的编号，如果不能构造出合法的子树，就输出-1。

**一句话题意：使拆分出的三棵子树的和分别相等**

那么经过我们的胡乱分析（雾，这题显然就是一道树形动规~~水~~题嘛（逃

好，掌握了，那么我们来看一看代码的实现

先将整棵树读入，在读入的时候我们发现，根据题意，在这棵树中会有一个点不存在，那这个点应该就是他拿着的那个灯泡，所以，我们将其理解为树的根节点（脑补一下）。

这时我们的基本思路是：每个节点的初始值为灯泡亮度，从叶子结点开始向上计算，利用树的一些优美性质，每次更新其父亲结点的权值即为其本身的值与其所有孩子的值，，这是我们可接受的，这时一旦出现有符合整棵树的三分之一的树就先把他割下来，存储答案和答案个数，当割成的树的个数不为3时说明这是一条链，只有两部分（自己画图体会下）所以当cnt<=2时都不符合条件


好的，上代码ヽ(￣▽￣)و
```
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=1000010;
int n,t[maxn],root,cnt,sum,ans[5];
int ver[2*maxn],head[maxn*2],next[maxn*2],tem[maxn],tot;
void add(int x,int y){
	tot++;
	ver[tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int y){
	tem[x]=t[x];
	for(int i=head[x];i;i=next[i]){
		int v=ver[i];
		if(v!=y){
			dfs(v,x);
			tem[x]+=tem[v];
		}
	}
	if(tem[x]==sum) ans[++cnt]=x,tem[x]=0;
}
int main(){
	int a;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d %d",&a,&t[i]);
		if(a) add(a,i),add(i,a);
		else root=i;
		sum+=t[i];
	}
	if(sum%3){
		puts("-1");
		return 0;
	}
	sum/=3;
	dfs(root,0);
	if(cnt<=2) puts("-1");
	else printf("%d %d\n",ans[1],ans[2]);
	return 0;
}
```
其实写完后会发现实际上这道题并没有什么动规的味道，更多的是一种巧妙的想法，不过因为子树和问题常常以动规的形式出现，所以窝就先这么胡乱的分析成了树p，在实现代码后才真正理解（大家不要向我学习）
###### 吼的 大家今天也要加油鸭QwQ

---

## 作者：无咕_ (赞：6)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）

是否吸氧：否

不压行代码长度：44

------------

## 题目大意
题面： [<传送门>](https://www.luogu.com.cn/problem/CF767C)

题意：给棵有根树，有点权，按权三分此树，输出剪掉的边的指向点。

~~术语理解：树形 DP 板子题。~~

## Solution

~~虽然是树形 DP，但无限接近于暴力！~~

我们需要一个数组 `treesum[]`，用于记录权值和（`treesum[i]` 表示以节点 $i$ 为根的子树权值和）。

至于怎么算……这就不需要我说了吧，与计算子树大小一样……

现在我们考虑下如何“剪枝”。首先，我们如果要按权分三份，那我们一定要知道分完后每棵树的权值和。于是，我们需要在读入时累加 $sum$，那么分完之后的每棵树权值和就一定是 $\frac{3}{sum}$ 了（通过此处可以知道，如果 $sum\bmod 3\ne 0$ 则无解）。

我们可以发现，剪完后的树一定是原来树的子树。更严谨地说，当前剪下来的树一定是剪之前的树的子树（因为一刀不可能只剪中间的一条链）。**注意！剪掉一个子树后，一定要减去它的权值！因为它已经不存在于这棵树了！**

那么我们直接在求完权值和后直接判能不能分不就行了？如果剪的次数 $>2$ （因为会剪三次，判的是三分）就输出，CF 自带 SPJ ，大胆做就行。如果剪的次数 $<2$ 那没办法，无解，输出 $-1$ 。

啥？你问我为啥是树形 DP？~~因为题目标签有~~

给你方程（其实就是这个题）：

设 $T$ 为 $i$ 点的儿子集合，长度为 $n$ 。

$$f_i=a_i+\sum^n_{j=0}f_{T_j}$$

对于任意 $f_{u_1},f_{u_2},f_{u_3}$ ，若存在 $f_{u_1}=f_{u_2}=f_{u_3}=\frac{3}{sum}$，则有解（前提是每筛选出一个点 $x$ 使得 $f_x=\frac{3}{sum}$ 时，其父亲 $y$ 要 $f_y-f_x$）

## AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXM=2e6+9,MAXN=1145140;
struct Edge{
    int nxt,to;
}edge[MAXM];
int num_edge=0,head[MAXM];
int sum=0,a[MAXN],root;
int ans[5],num_ans=0;
int treesum[MAXN];
void add_edge(int from,int to){
    edge[++num_edge]=(Edge){head[from],to};
    head[from]=num_edge;
}void dfs(int now,int fa){
    treesum[now]=a[now];
    for(int i=head[now];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==fa)continue;
        dfs(to,now);
        treesum[now]+=treesum[to];
    }if(treesum[now]==sum/3)ans[++num_ans]=now,treesum[now]=0;
}int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int u;
        scanf("%d %d",&u,&a[i]);
        if(u!=0){
            add_edge(u,i);
            add_edge(i,u);
        }else root=i;
        sum+=a[i];
    }if(sum%3!=0){
        printf("-1\n");
        return 0;
    }else{
        dfs(root,0);
        if(num_ans>2)printf("%d %d",ans[1],ans[2]);
        else printf("-1\n");
    }
    return 0;
}
```

AC 记录 [<传送门>](https://www.luogu.com.cn/record/56723406)

## 类似题目

树形 DP [P2014 [CTSC1997]选课](https://www.luogu.com.cn/problem/P2014)



---

## 作者：kenlig (赞：5)

其实这个题的题解很多吧？思路也大概差不多。那我说一下我的好了。
同时，本文也发在了我的cnblogs博客上，（不要以为我是copy的）

考虑存在这么三个子树，那么这个树肯定就能分成这么三个子树，而这个树的点权之和肯定能平均分成三个子树，那么这个树的点权 mod 3 肯定为0.

这是一个显然的剪枝。

言归正传，我们来说说正解。首先这个题的解法当然是树形DP一贯的解法：

# 推。

### 我们从下往上更新，就可以更新到这个子树了。如果我们从下往上获得了一个子树，并且这个子树的权值是树的权值的1/3，那么显然这个子树是符合条件的，切一刀，我们就得到了子树。代码中cnt是切的次数。

ksum这个数组就是子树的大小。

那么本题的解法已经很显然了，就那么遍历就完事了。

代码有注释，方便各位理解。

C++：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define LL long long
#define maxn 1000001
using namespace std;
struct Edge{
	int nxt,to,from;
}edge[maxn*2];//因为这是个树 
int num_edge,head[maxn],a[maxn],n,fa,total,sum,cnt,ans[maxn],ksum[maxn];
inline int qread(){
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void addedge(int from,int to){ //加上from的原因是我们要输出他的from 
	edge[++num_edge].nxt=head[from];
	edge[num_edge].from=from;
	edge[num_edge].to=to;
	head[from]=num_edge;
} 
int dfs(int x,int fath){
	ksum[x]=a[x];
	for(int i=head[x];i;i=edge[i].nxt){//找祖先 
		int y=edge[i].to;
		if(y!=fath){
			dfs(y,x);
			ksum[x]+=ksum[y];
		}
	}
	if(ksum[x]==sum){ //当满足了之后 
		cnt++;
		ans[cnt]=x;
		ksum[x]=0;
	}
}
int main(){
	n=qread();//快读，否则的话大数据卡死 
	for(int i=1;i<=n;i++){
		int x;
		x=qread();
		a[i]=qread();
		if(x!=0) {
			addedge(i,x);
			addedge(x,i);
		}
		else fa=i;
		total+=a[i];
	}
	if(total%3!=0) printf("-1\n");
	else{
		sum=total/3;
		dfs(fa,0);
		if(cnt>=3) printf("%d %d\n",ans[2],ans[1]);
		else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：chihik (赞：4)

首先可以确定的是，如果点权和不为3的倍数，一定不存在合法方案。

记所有点权和为$sum$。

容易想到，令 $dp[u]$ 表示以 $u$ 为根的子树的点权和 ， 则有转移：

$$dp[u]=a[u]+\sum_{v \in son_u}dp[v]$$

然后对于点 $u$ , 有一个儿子 $v$ 使得 $dp[v]=\frac{sum}{3}$,那么我们可以将 $v$ 切开，然后 $dp[u]=dp[u]-dp[v]$ 。

最后看是否有两个切点即可。

```cpp
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 1000000;
int n , root , sum , a[ MAXN + 5 ] , dp[ MAXN + 5 ];
int v1 , v2;
vector< int > Graph[ MAXN + 5 ]; 

void dfs( int u , int fa ) {
	dp[ u ] = a[ u ];
	for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
		int v = Graph[ u ][ i ];
		if( v == fa ) continue;
		dfs( v , u ); dp[ u ] += dp[ v ]; 
		
		if( dp[ v ] == sum / 3 ) {
			if( !v1 ) v1 = v;
			else if( !v2 ) v2 = v;
			dp[ u ] -= dp[ v ];
		} 
	} 
}

int main( ) {
	scanf("%d",&n);
	for( int i = 1 , v ; i <= n ; i ++ ) {
		scanf("%d %d",&v,&a[ i ]); sum += a[ i ];
		if( !v ) root = i;
		else {
			Graph[ i ].push_back( v );
			Graph[ v ].push_back( i );
		}
	}
	if( sum % 3 ) {
		printf("-1");
		return 0;
	}
	
	dfs( root , 0 );
	if( !v1 || !v2 ) 
		printf("-1");
	else 
		printf("%d %d\n",v1,v2);
	return 0;
}
```


---

## 作者：Kevin_F (赞：1)

这个题我是看着翻译做的，感觉不是很难，很普通的一个树形dp

**题目大意：**

在一棵树上分离出三个子树，使这三个子树的点权和相等。

明确题目意思这个题就简单多了吧。

我们会发现每一棵子树的点权是固定的，因为点权总和固定，设每一部分的大小为W，那么我们就从下往上更新（**因为树形dp的基本做法就是从下向上更新，用儿子更新爸爸**），遇到等于W的子树就切一刀，sz重置成0，这就可以一边遍历子树，一边算sz.

剪枝（额。。好像不能叫剪枝）也挺容易想，如果点权总和不是3的倍数，那么肯定不行（分不出三个相等）

这题细节挺多的，需要注意一条链的情况和和是三的倍数但不能分成几个相等的部分的情况。

最后的那个地方$cnt >= 3$就是想,如果分成了大于等于3个子树，就直接输出两个就行了，否则的话就输出-1，证明我们最多只能找到两个子树权值是整棵树的 $\frac{1}{3}$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000100;

inline int read(){
	char ch = getchar();
	int f = 1 , x = 0;
	while(ch > '9' || ch < '0'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}

int w[maxn],x,y;
int head[maxn],tot;
struct Edge{
	int from,to,val,next;
}edge[maxn<<1];
int n,root,sum,sz[maxn],cnt,ans[10];

void add(int u,int v){
	edge[++tot].from = u;
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}

int dfs(int x,int fa){
	sz[x] = w[x];
	for(int i=head[x];i;i=edge[i].next){
		int v = edge[i].to;
		if(v != fa){
			dfs(v , x);
			sz[x] += sz[v];
		}
	}
	if(sz[x] == sum){
	   ans[++cnt] = x;
	   sz[x] = 0;
	}
}

int main(){
	n = read();
	for(int i=1;i<=n;i++){
		x = read(); y = read();
		if(x != 0)  add(i , x), add(x , i);
		else root = i;
		w[i] = y;
		sum += y;
	}
	if(sum % 3 != 0)  printf("-1\n");
	else {
		sum /= 3;
		dfs(root , 0);
		if(cnt >= 3)  printf("%d %d\n",ans[2],ans[1]);
		else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：ctq1999 (赞：1)

一道想一下就大概知道怎么做的题。

## 题意简述

给定一颗有根点带权的树，求两个节点 $v_1$，$v_2$，使树删除 $(u_1,v_1)$ 和 $(u_2,v_2)$ 这两条边后，树被分成三个权值相等的子树（$u_1$ 和 $u_2$ 的深度分别比 $v_1$ 和 $v_2$ 的深度小）。

## 思路

我看到这题时，想了一会，就想到了一个比较暴力的思路。

遍历一遍树，当以当前节点为根的子树的权值和的三倍是树的总权值时，记录下这个节点，然后 $O(n^2)$ 遍历记录的节点，求出两个合适的节点。

时间复杂度 $O(n^2)$。这解法在 #28 TLE 了。

然后我试着在遍历的时候就直接输出。因为所求的两个节点的取法只有两种可能：

- 在同一颗子树内，即两个点的 LCA 是他们其中一个点。

- 在一个节点的两颗子树内。

然后我在 #8 WA 了，不知道为什么。

然后就瞄了一眼题解，就懂了这个解法。

遍历这棵树，当以当前节点为根的子树的三倍是总权值时，记录这个点，**并把这个子树从树种切掉**。

然后就有一个性质：当遍历完后，如果记录了超过 $3$ 个节点，那么就说明必定有解。

也就是说，如果目前恰好记录了 $3$ 个节点，那么其中任意两个节点都是解，直接输出即可。

再说也没什么意思了，自己想想吧。

遍历完后记录的节点小于等于 $3$，那么就是无解。

时间复杂度 $O(n)$。

## 代码

```
#include<bits/stdc++.h>

#define ll long long
#define y1 caibictq
#define P pair<int, int>
#define fi first
#define se second

using namespace std;

const int MAXN = 2000010;
const int MAXM = 100010;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, k;
int sum, v, rt, ok;
int tot, cnt, ans;

int read() {
	int f = 1, s = 0;
	char ch = getchar();
	while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while ('0' <= ch && ch <= '9') {s = (s << 1) + (s << 3) + ((int)ch ^ 48); ch = getchar();}
	return s * f;
}

int a[MAXN], head[MAXN];

vector<int> ver;

struct edge {
	int to, next;
}e[MAXN << 1];

void add_edge(int x, int y) {
	e[++tot].next = head[x];
	e[tot].to = y;
	head[x] = tot;
	return;
}

string s;

int dfs(int x, int fa) {
	int tmp = a[x];
	for (int i = head[x]; i; i = e[i].next) {
		int y = e[i].to;
		if (y == fa) continue;
		tmp += dfs(y, x);
	}
	if (tmp * 3 == sum) {
		ver.push_back(x);
		tmp = 0;
	}
	if (ver.size() == 3) {
		for (int i = 0; i < ver.size() - 1; i++) {
			printf("%d ", ver[i]);
		}
		puts(""); exit(0);
	}
	return tmp;
}

int main() {
	int T;
	scanf("%d", &n);
	for (int i = 1, fa; i <= n; i++) {
		scanf("%d%d", &fa, &a[i]);
		sum += a[i];
		add_edge(i, fa); add_edge(fa, i);
		if (!fa) rt = i;
	}
	dfs(rt, 0);
	puts("-1");
	return 0;
}

/*
6
2 4
0 -1
4 2
2 3
1 2
4 5
*/ 
```




---

## 作者：试试事实上吗 (赞：1)

### Part.1

一开始完全没有思路,想了一下，如果是分成两棵树，那就好做多了，首先想到的是统计一下以当前节点为根的子树的权值和，如果和为$sum\times\frac{1}{2}$，那么我们就找到了一个解。考虑我们也类似地记录一个$siz$表示以当前节点为根的子树的权值和，只要为$sum\times\frac{1}{3}$，它就可能是解的一个。

### Part.2

我们在一遍$dfs$后可以找出可能很多是$sum\times\frac{1}{3}$的解，那么我们应该怎么选择呢？很容易想到，我们应该找到$LCA$不同的两个点，我们就找到了一组解。

### Part.3

上述解法实际上是存在问题的（~~想一想，为什么~~）

我们考虑类似下面的一棵树：

![luoguCF767C图.png](https://i.loli.net/2020/06/06/AbLO9F7wlznCeuf.png)

很显然这棵树上子树权值和为$sum\times\frac{1}{3}$只有三号节点，但我们能不能把他分成三棵树呢？很显然是可以的（每个节点都分成一棵树），我们的解法应进一步考虑。考虑二号节点，它的权值和是$sum\times\frac{2}{3}$，那我们怎么处理呢？难道要把所有的$sum\times\frac{1}{3}$与$sum\times\frac{2}{3}$算出来，然后再一一匹配吗？

我们考虑另一种解法。$dfs$的特点是要在处理完儿子后才会处理当前节点，考虑儿子中有一个$sum\times\frac{1}{3}$，如果我们吧儿子的$sum\times\frac{1}{3}$变成$0$，那么它自身也变成了$sum\times\frac{1}{3}$，我们此时只用一个数组统计为$sum\times\frac{1}{3}$的节点就ok了，那么如果有两个儿子都是$sum\times\frac{1}{3}$呢？我们一定会先处理儿子，那么儿子都被统计了，自然就找到答案了。

我们只用输出找到的前两个答案即可。（这两个答案一定是我们上述提到的两种关系）

最后奉上高清~~无码~~的代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn=1e6+5;

struct edge
{
    int v,nxt;
}e[maxn<<1];
int head[maxn],kt;
int t[maxn],rt,n;
int ans[10],tot;
int sum;
template<typename T>
inline void read(T &x)
{
    char c;int f=1;
    while(!isdigit(c=getchar())) (c=='-')&&(f=-1);
    x=c^48;
    while(isdigit(c=getchar())) x=(x<<1)+(x<<3)+(c^48);
    x*=f;
}

inline void add(int u,int v) {e[++kt]=(edge){v,head[u]};head[u]=kt;}

void dfs(int u,int f)
{
    for(int i=head[u];i;i=e[i].nxt)
    if(e[i].v!=f)
    {
        dfs(e[i].v,u);
        t[u]+=t[e[i].v]; 
    }
    if(t[u]==sum/3)
        ans[++tot]=u,t[u]=0;
}

int main()
{
    int x;
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(x);read(t[i]);
        sum+=t[i];
        if(x) add(x,i),add(i,x);
        else rt=i;
    }
    if(sum%3)
    {
        puts("-1");
        return 0;
    }
    dfs(rt,0);
    if(tot<=2) puts("-1");
    else printf("%d %d\n",ans[1],ans[2]);
    return 0;
}
```

---

## 作者：御前带刀侍卫 (赞：0)

### 0.题目链接

[Luogu_CF767C](https://www.luogu.com.cn/problem/CF767C)

### 1.翻译
这个翻译也太简略了吧，简直就是什么都没说（~~对于我蒟蒻来缩~~）

不过大佬们一定能从样例里看出来，第i行的第一个数字为父亲，第二个数字为权值，父亲为0的点为根节点

### 2.思路

这题是听LYD老师讲的，其实就是一个基本的树上DP求子树重量+贪心

一个题眼在于：既然要分为三份，则每一份均为sum/3

若sum%3!=0则可立即输出-1

即，从叶到根DP求重量，每一到sum/3时，就立即标记并计数，

同时把该子树“剪掉”，即把重量归零

最后判断一下剪了几次，若大于等于3，即可均分。

### 3.代码
```cpp
#include<iostream>
#include<stdio.h>

#define MAXN 1000000
using namespace std;

int n;

int cnt;
int ans[4];			//答案相关 

long long sum;
int val[MAXN+10];	//各点权值 


struct ed{
	int nxt,to;
}edge[MAXN*2+10];

int edge_cnt=0;
int head[MAXN+10];
int weight[MAXN+10];

void add(int ff,int tt){
	edge_cnt++;
	edge[edge_cnt].to=tt;
	edge[edge_cnt].nxt=head[ff];
	head[ff]=edge_cnt;
}								//邻接链表不解释 

void get(int s,int fa){
	weight[s]=val[s];
	for(int i=head[s];i;i=edge[i].nxt){
		int e=edge[i].to;
		if(e==fa){
			continue;
		}
		get(e,s);
		weight[s]+=weight[e];
	}
	if(weight[s]==sum){
		ans[cnt++]=s;weight[s]=0;
	}
}								//DP求重量 

int main(){
	int root;
	scanf("%d",&n);
	for(int a,i=1;i<=n;i++){
		scanf("%d %d",&a,&val[i]);
		sum+=val[i];
		if(a)add(i,a),add(a,i);
		else root=i;			//求根，根不一定为1 
	}	
	if(sum%3){					//提前判断 
		printf("-1\n");
		return 0;
	}	
	sum/=3;						//sum即为应得的重量 
	get(root,0);
	if(cnt>=3){
		printf("%d %d\n",ans[0],ans[1]);
		return 0;
	}
	printf("-1\n");
	return 0;					//吼习惯啊 
}	
```



---

## 作者：寒冰大大 (赞：0)

为啥所有题解都建的无向图，好怪哦。

这道题的做法有点奇怪，需要分析(luan gao)一下

把这棵树权值分成三个，很显然需要对树上点的权值和来判断，如果不是倍数就要输出$-1$

然后我们就用$dfs$求值来满足这个条件的子树，求子树的大小相信大家都会，不过我们还是要来一个处理，就是这个子树如果满足的吧，我们得把这个子树大小看做$0$上传，不然后面就很麻烦

我们把符合条件的点放进一个数组里面，不难发现由于我们处理了后这些点选不选都互不干扰，所以我们找两个出来就行了。

```cpp
#include<touwenjian.h>

using namespace std;

const int maxn=1001000;

struct edge{
	int next,to;
}e[maxn];

int head[maxn],size,n,a[maxn],m,tot;
int ind[maxn],st,sz[maxn];
int p[maxn],c;

inline void addedge(int next,int to)
{
	e[++size].to=to;
	e[size].next=head[next];
	head[next]=size;
}

void dfs(int t)
{
	int i,j;
	sz[t]=a[t];
	for(i=head[t];i;i=e[i].next)
	{
		j=e[i].to;
		dfs(j);
		sz[t]+=sz[j];
	}
	if(sz[t]==tot/3) p[++c]=t,sz[t]=0;
}

int main()
{
	ios::sync_with_stdio(false);
	register int i;
	cin>>n;
	int t1;
	for(i=1;i<=n;i++)
	{
		cin>>t1>>a[i];
		tot+=a[i];
		if(t1==0) continue;
		addedge(t1,i);
		ind[i]++;
	}
	if(tot%3!=0)
	{
		cout<<-1<<endl;
		return 0;
	}
	for(i=1;i<=n;i++) if(!ind[i]) st=i;
	dfs(st);
	if(c<=2)
	{
		cout<<-1<<endl;
		return 0;
	}
	cout<<p[1]<<" "<<p[2];
	
}
```


---

## 作者：良月澪二 (赞：0)

没有用$vector$的么
详细解释在代码
```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <vector>
#include <iomanip>
#define A 1000010
#define B 2010
#define ll long long

using namespace std;
int n, a, b, root, cnt, sum, rem;
int pre[A], size[A], w[A], ans[3], cans;
vector<int> v[A]; //vector存图
void dfs(int fr) {
	size[fr] = w[fr]; //子树权值一开始是这个点的权值
	for (int i = 0; i < v[fr].size(); i++) //遍历相邻的每个点
	  if (v[fr][i] != pre[fr]) { //不是同一个结点
          dfs(v[fr][i]); //继续往下搜
          size[fr] += size[v[fr][i]]; //算上子树大小
	  }
	if (size[fr] == (sum / 3) and pre[fr])
	  ans[++cans] = fr, size[fr] = 0; //算进答案中了就去掉这颗子树
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		cnt++;
		scanf("%d%d", &a, &b);
		if (!a) {
			root = cnt; //记录下根节点
			w[cnt] = b; //点的权值
			pre[cnt] = a; //记录下前驱
			sum += b; //这颗树的点权和
		}
		else {
			w[cnt] = b;
			pre[cnt] = a;
			v[cnt].push_back(a); //双向存图
			v[a].push_back(cnt);
			sum += b;
		}
	}
	if (sum % 3) return puts("-1") & 0; //怎么也分不成三份
	dfs(root);
	if (cans >= 2) printf("%d %d\n", ans[1], ans[2]);
	else puts("-1");
}
```

---

