# Fib-tree

## 题目描述

Let $ F_k $ denote the $ k $ -th term of Fibonacci sequence, defined as below:

- $ F_0 = F_1 = 1 $
- for any integer $ n \geq 0 $ , $ F_{n+2} = F_{n+1} + F_n $

You are given a tree with $ n $ vertices. Recall that a tree is a connected undirected graph without cycles.

We call a tree a Fib-tree, if its number of vertices equals $ F_k $ for some $ k $ , and at least one of the following conditions holds:

- The tree consists of only $ 1 $ vertex;
- You can divide it into two Fib-trees by removing some edge of the tree.

Determine whether the given tree is a Fib-tree or not.

## 说明/提示

In the first sample, we can cut the edge $ (1, 2) $ , and the tree will be split into $ 2 $ trees of sizes $ 1 $ and $ 2 $ correspondently. Any tree of size $ 2 $ is a Fib-tree, as it can be split into $ 2 $ trees of size $ 1 $ .

In the second sample, no matter what edge we cut, the tree will be split into $ 2 $ trees of sizes $ 1 $ and $ 4 $ . As $ 4 $ isn't $ F_k $ for any $ k $ , it's not Fib-tree.

In the third sample, here is one possible order of cutting the edges so that all the trees in the process are Fib-trees: $ (1, 3), (1, 2), (4, 5), (3, 4) $ .

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5```

### 输出

```
NO```

## 样例 #3

### 输入

```
5
1 3
1 2
4 5
3 4```

### 输出

```
YES```

# 题解

## 作者：serverkiller (赞：9)

这里是这题的官方题解

有关 pretest 的吐槽请上 cf 关于我在 cf 上解释的吐槽请先学英语

另外是我的吐槽 先存个档 现在的评分是绿题:

> 如果 Anton 能看懂 洛谷 评分的话他一定开始生气了

我们约定: $f_i$ 表示第 $i$ 个 fib数

下面开始这题:

首先我们很容易发现 一个大小为 $f_i$ 的树经过一次分割一定会被割成 一棵大小为 $f_{i-1}$ 和 一棵大小为 $f_{i-2}$ 的树

不难发现我们对于一种树 我们可能有两种割法 我将证明这两种割法是等价的

1. 不难证明 $f_3$ 时结论正确
2. 假设 $f_n$ 是我们的结论正确
3. 考虑对于 $f_{n+1}$ 我们有两种割法 我们选取其中一种 另外一条边一定在大小是 $f_n$ 的树内 根据 2 中假设可以得到我们结论正确

所以对于一棵树 我们任选需要割的边即可 类似于点分治的写法 这里不过多阐释了

考虑到 fib数 的增长速度 我们最多只会切 $\mathcal O(\log_\phi n)$ 次 所以最终的复杂度是 $\mathcal O(n\log_{\phi}n)$ 可以通过此题而且非常不卡常 也没什么很特殊的细节

---

## 作者：FutaRimeWoawaSete (赞：5)

如果按照在比赛时算的话被扣了 $300pts$ ，罚时吃饱。         

首先，这道题一来就给人一种很诡异的感觉，不过我们还是可以从中找到一些很显的东西，你看着 fib 在 $2 \times 10 ^ 5$ 以内只有 $26$ 项，就可以感觉在上面做东西。       

我最开始的想法就是想开个 $26$ 位的 bitset，然后一口一口往上传然后做的时候直接去剪就好了，接着就发现这个做法好像不是很好搞，虽然按理来说还是能过题。           

记 $f_i$ 为斐波那契数列的第 $i$ 项。

接着就感觉出题人不会只把 fib 拿出来出一个这么显的性质拿来做题，怎么也得需要一个性质，然后就发现了 $f_{i - 1} \times 2 \geq f_i - 1 , f_{ i - 2} \times 3 \geq f_i - 1$ 的性质，这可以怎么拿来转化呢？如果你对树的重心很有感觉，那么你就会发现这种东西其实就是来限制子树个数的，即，在大小为 $f_i$ 的树中，大小为 $f_{i - 1}$ 的子树至多只会有一个，大小为 $f_{i - 2}$ 的子树至多只会有两个。         

有了这个玩意儿我们就可以想到，当前的割树方法其实是比较有限的，我们直接暴力怼一个数学归纳法上去：       

- 现在对于任意一棵 $f_n$ 子树都有两种割树方法，这里我们可以假设如果有一棵子树大小为 $f_{n - 1}$ ，那么算上根结点后，就有且只剩下一棵 $f_{n - 2}$ 的子树是它的子树，此时有两种割树方法；还有就是不存在 $f_{n - 1}$ 的子树，只有两颗 $f_{n - 2}$ 的子树，此时也只有两种割树方法。综上每棵 $f_n$ 的子树都有两种割树方法。       

- 不过怎么说，这棵子树都只会被割成一棵 $f_{n - 1}$ 和 $f_{n - 2}$的子树，我们现在尝试证明任意两种情况下的割树方法等价。         

- 采用数学归纳法。首先我们假设任意 $f_{n - 1}$ 的子树满足这个性质，那么对于第一种情况，我们先割出去一棵 $f_{n - 1}$ ，然后再把子树里面 $f_{n - 2}$ 的那棵子树割掉，和我们先割 $f_{n - 2}$ ，再把 $f_{n - 1}$ 和 $f_n$ 断开的效果不就是一样的了吗？结论成立。对于第二种情况，我们先割出一棵 $f_{n - 2}$ ，再接着我们把另外一个 $f_{n - 2}$ 在剩下的 $f_{n - 1}$ 里面断开，和先断后一棵 $f_{n - 1}$ 后断前一棵 $f_{n - 1}$ 不就一样了吗？画画图就好了。         

接着我们就可以很暴力的开挂做了，我们每次随便找到一条合法边考虑暴力割掉，先把原树的 $siz$ 都处理一下，然后暴力继续看分出去的两个树是否合法，这个过程很明显是一个递归的过程，看似是一个 $O(2 ^ {26} \times n)$ 的过程，其实时间复杂度只有 $O(26n)$ 。       

这个也很好证明，我们把递归过程当成一棵树，首先这是一棵二叉树（尽管这个性质没用），接着我们在每一个节点都执行了一个递归操作时间复杂度为 $O(siz_x)$ ，而由于我们的每一层节点之和加起来就是一个原树大小，那么我们一层的时间复杂度就是 $O(n)$ ，斐波那契在 $2 \times 10 ^ 5$ 以内拆下来最多 $26$ 层，时间复杂度得证。        

不是一道很难的题，放 $E$ 真的简单了点，只不过刚开始真的被这个证明坑到了（不过这貌似不影响做题……） 。评蓝真的不能再高了。       

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
const int Len = 2e5 + 5;
int n,m,F[31],siz[Len],fa[Len];
vector<int> v[Len];
int flag[Len];
int num;
void add(int from,int to){v[from].push_back(to);}
void dfs(int x,int f)
{
	siz[x] = 1;
	fa[x] = f;
	for(int i = 0 ; i < v[x].size() ; i ++)
	{
		int to = v[x][i];
		if(to == f) continue;
		dfs(to , x);
		siz[x] += siz[to];
	}
}
void DFS(int x,int id)
{
	if(siz[x] == F[id] || siz[x] == F[id - 1]) num = x;
	for(int i = 0 ; i < v[x].size() ; i ++)
	{
		int to = v[x][i];
		if(to == fa[x]) continue;
		DFS(to , id);
	}
} 
bool Check(int x,int id)//当前根是x，Fib数列的第i项 
{
	if(siz[x] <= 1) return true; 
	num = -1;
	DFS(x , id - 1);
	if(num == -1) return false;
	int f = fa[num] , pst = num , val = siz[num];
	vector<int>::iterator itor;
	for(itor = v[f].begin(); itor != v[f].end(); itor ++) if (*itor == num){itor = v[f].erase(itor);break;}
	for(itor = v[num].begin(); itor != v[num].end(); itor ++) if(*itor == f){itor = v[num].erase(itor);break;}
	while(f != x)
	{
		siz[f] -= val;
		f = fa[f];	
	}
	siz[x] -= val;
	if(val == F[id - 1]) return Check(x , id - 2) && Check(pst , id - 1);
	else return Check(x , id - 1) && Check(pst , id - 2);
} 
int main()
{
	F[0] = F[1] = 1;
	flag[1] = 1;
	for(int i = 2 ; i <= 26 ; i ++) 
	{
		F[i] = F[i - 1] + F[i - 2];
		flag[F[i]] = i;
	}
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i ++) 
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
	}
	dfs(1 , 0);
	if(!flag[n]) printf("NO\n");
	else (Check(1 , flag[n])) ? puts("YES") : puts("NO"); 
	return 0;
}
```

---

## 作者：dcmfqw (赞：4)

upd:感谢评论区老哥提醒，前面两句吐槽已经删掉……

下面用 $F_n$ 表示第 $n$ 个斐波那契数。

我们考虑用分治来解决这个题目。

首先无根树很麻烦，我们就选一个根，把它当作有根树来看。

选哪个根呢？选重心吧，这样选的好处一会就能体现了。

我们会发现，拆掉一条边分出来的两棵树有一棵是原有根树的子树。

而且根据重心的性质，这棵子树的大小一定小于分出来的另一棵树。

然后奶一口 $F_n(n\geq3)$ 只能被分成一对斐波那契数的和，就是 $F_{n-1}$ 和 $F_{n-2}$。

（好像挺显然的，不会的自己去 bdfs 或看官方题解吧……）

显然 $F_{n-2}<F_{n-1}$ ，所以那棵子树的大小一定是 $F_{n-2}$。

会发现整棵树里面最多可能有两棵大小 $F_{n-2}$ 的子树，任选一个分开，然后递归处理即可。

为什么可以任选一个呢？因为反正另外一棵子树在接下来的分治过程中还要分开的。

然后不大于 $2\times10^5$ 的斐波那契数只有 $26$ 个，并且你会发现整个过程中，你遍历的大小同为 $F_i$ 的子树都不会交叉。

和点分治类似，整个过程可以看成是近似 $O(n\log n)$ 的，能过就行了。

（聚聚们别 D 我，官方题解说其实是 $O(nlog_\phi n)$）

考场代码有点丑……因为全局变量存返回值出了点锅还 WA 了一发……

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _maxn = 200011;
int t, n, pdif[_maxn], u, v, firs[_maxn], neig[_maxn << 1], arri[_maxn << 1], valu[_maxn << 1], size[_maxn], dcen, rans, dans, tosi[_maxn];
void dfs2(int at, int fa, int fr, int da) {
  size[at] = 1;
  for(int i = firs[at]; i; i = neig[i]) {
    if(valu[i] && arri[i] != fa) {
      dfs2(arri[i], at, i, da);
      size[at] += size[arri[i]];
    }
  }
  if(pdif[size[at]] == da) {
    rans = fr;
    dans = at;
  }
}//找大小为Fn-2的树
void dfs3(int at, int fa, int al) {
  int pd = 1;
  size[at] = 1;
  for(int i = firs[at]; i; i = neig[i]) {
    if(arri[i] != fa && valu[i]) {
      dfs3(arri[i], at, al);
      size[at] += size[arri[i]];
      if(size[arri[i]] * 2 > al) {
        pd = 0;
      }
    }
  }
  if(pd && size[at] * 2 >= al) {
    dcen = at;
  }
}//找重心
int dfs1(int at, int da/*当前子树大小在斐波那契数列中的序号*/) {
  int cp;
  if(da == 1 || da == 2) {
    return 1;
  }
  dfs3(at, 0, tosi[da]);
  at = dcen;
  dans = 0;//存的是大小为 Fn-2 的子树根
  rans = 0;//存的是 dans 指向父亲的边
  dfs2(at, 0, 0, da - 2);
  if(!rans) {
    return 0;
  }
  cp = rans;
  valu[cp] = valu[cp ^ 1] = 0;//valu[i] 为 0 表示 i 被拆了
  if(dfs1(dans, da - 2) && dfs1(arri[cp ^ 1], da - 1)) {
    return 1;
  } else {
    return 0;
  }
}//分治过程
int main() {
  scanf("%d", &n);
  for(int i = 1; i < n; ++i) {
    scanf("%d%d", &u, &v);
    neig[i << 1] = firs[u];
    firs[u] = i << 1;
    arri[i << 1] = v;
    valu[i << 1] = 1;
    neig[i << 1 | 1] = firs[v];
    firs[v] = i << 1 | 1;
    arri[i << 1 | 1] = u;
    valu[i << 1 | 1] = 1;
  }
  for(int a = 1, b = 1, c, i = 1; a <= n; ++i) {
    tosi[pdif[a] = i] = a;
    c = b;
    b = a;
    a = b + c;
  }
  //pdif[i] 表示斐波那契数 i 的序号，i 不是斐波那契数则为 0（设 F2=2）
  //tosi[i] 相反，表示第 i 个斐波那契数
  if(!pdif[n]) {
    printf("NO");
    return 0;
  }
  if(dfs1(1, pdif[n])) {
    printf("YES");
  } else {
    printf("NO");
  }
  return 0;
}
```

欢迎来叉！

---

## 作者：EuphoricStar (赞：3)

## 思路

这道题看上去很棘手。但是思考一会就可以发现一个性质：斐波那契数列是以指数级增长的，因此小于 $n$ 的斐波那契数的级别只是 $\log n$ 的。

所以就诞生了一个暴力做法：每次遍历当前的一整棵树，计算所有子树的 $size$。如果存在 $v$ 使得 $size_v = F_{k-2}$ 或 $size_v = F_{k-1}$，就暴力割断连接 $fa_v,v$ 的边，然后继续递归两棵子树。

因为递归大约 $\log n$ 次 $F_k$ 就会变成 $1$，所以总时间复杂度大约是 $O(n \log n)$。

## 代码

[code](https://pastebin.ubuntu.com/p/dP5WqVFpdk/)

---

## 作者：lfxxx (赞：0)

我们知道斐波那契数增长的速度接近于指数增长，所以假若每次把一个大小为 $\text{fib}_{k}$ 的树暴力分解为大小为 $\text{fib}_{k-1},\text{fib}_{k-2}$ 的数，类似于树分治的分析，时间复杂度为 $O(n \log n)$，但是问题是一个树可能有多种分解方式。

我们猜测，假若存在一种合法分解方式，则所有分解方式均合法，接下来考虑证明。

![](https://cdn.luogu.com.cn/upload/image_hosting/k46m1vl9.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

假若如中红色是一种合法分解方式，那么假若黄色也是一种合法分解方式，说明下面大小为 $\text{fib}_{k-1}$ 的连通块在已经存在一种合法分解的前提下，所有分解（比如黄色代表的分解）均合法，我们发现这个问题被向下归纳了，边界是简单的，于是得证。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int tot=1;
int head[maxn<<1],nxt[maxn<<1],to[maxn<<1];
int vis[maxn<<1];
void add(int u,int v){
	tot++;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int n;
int fib[30];
int cut[2];
int sz[maxn];
void dfs(int u,int lst,int k){
	sz[u]=1;
	for(int v=head[u];v;v=nxt[v]){
		if(v!=(lst^1)&&vis[v]==0){
			dfs(to[v],v,k);
			sz[u]+=sz[to[v]];
		}
	}
	if(sz[u]==fib[k]){
		cut[0]=lst;
	}
	if(sz[u]==fib[k-1]){
		cut[1]=lst;
	}
}
bool solve(int u,int k){
	if(k<=1) return true;	
	cut[0]=cut[1]=0;
	dfs(u,0,k-1);

	if(cut[0]==0&&cut[1]==0) return false;
	if(cut[0]!=0){
		int x=to[cut[0]],y=to[cut[0]^1];
		vis[cut[0]]=vis[cut[0]^1]=1;
		return (solve(x,k-1)&solve(y,k-2));
	}else{
		int x=to[cut[1]],y=to[cut[1]^1];
		vis[cut[1]]=vis[cut[1]^1]=1;
		return (solve(x,k-2)&solve(y,k-1));
	}
	return false;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	fib[0]=fib[1]=1;
	for(int i=2;i<30;i++) fib[i]=fib[i-1]+fib[i-2];
	cin>>n;
	for(int i=0;i<30;i++){
		if(fib[i]==n){
			for(int j=1;j<n;j++){
				int u,v;
				cin>>u>>v;
				add(u,v),add(v,u);
			}
			cout<<(solve(1,i)==true?"YES\n":"NO\n");
			return 0;
		}
	}
	cout<<"NO\n";
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

《大型连续剧之我自己搞不懂自己代码为什么对了》

首先，我们注意到，fibonacci 数列是以 $1.618$ 的倍数增长的，也就是说，我们每次维护当前联通块 $S$，以 $\Theta(S)$ 的时间复杂度找到下一次要分割的联通块，那么根据主定理，我们的总时间复杂度就是 $\Theta(n\log_{1.618}n)$ 的，这足以通过本题。

等一下！为什么我们可以找到唯一的分割点呢？这个分割点显然可能有多个啊，每次选两个进去递归不就全爆了？

事实上，笔者自己写代码的时候并没有意识到这一点，但是“莫名其妙”的 AC 了，给同学讲的时候被打爆了。。。

所以为了证明上述做法的正确性是有的，我们证明一个引理：当一个树有两种分割方式时，任意一种都是可行的。

边界是 trival 的，接下来我们进行归纳。

下令 $\{f\}=\{\text{fib}\}$。

假设 $n=f_n$ 时，原结论正确，则当 $n=f_{n+1}$ 时，我们任取一种分割方式，则另外一条边必定位于 $f_{n}$ 中，此时， 这些边实际上将整个树分成了大小为 $f_{n-1},f_{n-2},f_{n-1} $ 的三个联通块！读者可以自行讨论一下具体是那块不可行，根据归纳假设，即证。

[CF submission](https://codeforces.com/contest/1491/submission/271384973)

---

## 作者：_edge_ (赞：0)

$2400$ 就这？

事实上这题非常简单，不需要任何的高科技，纯粹的暴力。

我们去思考一个问题，一棵树的节点数是 $F_k$ 如果能够被分成两颗子树，那么必定是分解成两颗点数为 $F_{k-1}$ 和 $F_{k-2}$。

然后我们考虑分解一颗树变成两个部分，这两个部分肯定是唯一确定的，或者说我们随便分解一个都是对的。

上述结论我不会证明，但是可以思考一条链的情况，发现他挺对的。

补充证明：

如果一个树的点的个数为 $F_k$，那么一定是 $F_{k-1}$ 和 $F_{k-2}$，因为如果不是的话，那么后面的一定是不够的，可以尝试自己理解一下。

然后我们需要的就是找出一个子树使得他等于 $F_{k-1}$ 或者 $F_{k-2}$，然后这样我们暴力把这个边给断掉，然后就好了。

让我们来严格分析一下这个复杂度，我们把在几颗子树内断一次边就视为一层递归。

由于斐波那契数列是非常优美，$F_{k-1}$ 和 $F_k$ 非常接近，因此断开会使得他变成近似于 $\dfrac{n}{2}$。

然后可得复杂度递推式是 $T(n)=2 \times T(\dfrac{n}{2})+n$，由主定理可得这东西是 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,head[INF],tot,sz[INF],f[INF],y,z,fl,vis[INF],vis1[INF],cnt;
map <int,int> Map;
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
void DFS(int x) {
	if (vis[x]==cnt) return ;
	if (fl) return ;
	vis[x]=cnt;sz[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (vis1[i]) continue;
		if (vis[v]==cnt) continue;
		DFS(v);
		sz[x]+=sz[v];
	}
	return ;
}
void DFS1(int x) {
	if (vis[x]==cnt) return ;
	if (fl) return ;
	vis[x]=cnt;sz[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (vis1[i]) continue;
		if (vis[v]==cnt) continue;
		DFS1(v);
		if (fl) return ;
//		cout<<x<<" "<<v<<" "<<sz[v]<<" "<<y<<" "<<z<<" yiw\n";
		if (sz[v]==y || sz[v]==z) {
			vis1[i]=vis1[i^1]=1;
			fl=1;
			return ;
		}
		sz[x]+=sz[v];
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;tot=1;
	for (int i=1;i<n;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
	}
	f[0]=1;f[1]=1;
	for (int i=2;i<=55;i++) {
		f[i]=f[i-1]+f[i-2];
		Map[f[i]]=i;
	}
	int T=-1;
	while (T--) {
		int K=0;
		for (int i=1;i<=n;i++)
			if (!vis[i]) {
				fl=0;
				cnt++;
				DFS(i);
				if (sz[i]==1) continue;
				K=1;
				int xx=Map[sz[i]];
				if (!xx) {cout<<"NO\n";return 0;}
				y=f[xx-1],z=f[xx-2];fl=0;
				cnt++;
				DFS1(i);
				if (!fl) {cout<<"NO\n";return 0;}
			}
		if (!K) break;
		for (int i=1;i<=n;i++) vis[i]=0;
	}
	cout<<"YES\n";
	return 0;
}
```


---

