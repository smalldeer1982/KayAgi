# [USACO23DEC] Cowntact Tracing P

## 题目描述

Farmer John 有依次编号为 $1\dots N$ 的 $N$（$2\le N \le 10^5$）头奶牛，奶牛间的关系可以用树结构描述。不幸的是，有一种疾病正在传播。

最初，有一些奶牛被感染。每到夜晚，被感染的奶牛会将疾病传播给它的邻居。一旦奶牛被感染，她就会持续处于感染状态。经过一些晚上，Farmer John 意识到这样的情况，因此他对奶牛进行了检测以确定哪些奶牛感染了疾病。

你将得到 $Q$（$1\le Q \le 20$）个不同的夜晚数，每个都是 $[0,N]$ 范围内的整数。对于每个夜晚数，请找出最少有多少头奶牛最初可能感染了这种疾病，或者报告夜晚数与给出的信息不符。

## 说明/提示

### 样例解释 1

对于前四个询问，一种可能是只有 $3$ 号奶牛一开始被感染。对于第五组询问（$1$ 晚），一种可能是 $2,4$ 号奶牛一开始被感染。对于第六组询问（$0$ 晚），一种可能是所有的五只奶牛在一开始都被感染。

### 样例解释 2

对于第一组询问（$0$ 晚），一种可能是所有的十只奶牛一开始都被感染。对于第二组询问（$1$ 晚），一种可能是 $2,7,9$ 号奶牛一开始被感染。对于第三组询问（$2$ 晚），一种可能是 $2,9$ 号奶牛一开始被感染。对于第四至第十一组询问，一种可能是只有 $7$ 号奶牛一开始被感染。

### 样例解释 3

对于第一组询问（$0$ 晚），一种可能是 $1,2,3$ 号奶牛一开始被感染。对于第二组询问（$1$ 晚），一种可能是只有 $2$ 号奶牛一开始被感染。对于第三组询问（$2$ 晚），一种可能是只有 $1$ 号奶牛一开始被感染。对于第四至第六组询问，不可能满足题给条件。

### 测试点性质

- 测试点 $4-5$ 满足 $N \le 10$。
- 测试点 $6-8$ 满足所有奶牛都被感染。
- 测试点 $9-11$ 满足 $N \le 400$。
- 测试点 $12-23$ 没有额外限制。

## 样例 #1

### 输入

```
5
11111
1 2
2 3
3 4
4 5
6
5
4
3
2
1
0```

### 输出

```
1
1
1
1
2
5```

## 样例 #2

### 输入

```
10
1111111111
1 2
2 3
2 4
2 5
2 6
6 7
7 8
8 9
9 10
11
0
1
2
3
4
5
6
7
8
9
10```

### 输出

```
10
3
2
1
1
1
1
1
1
1
1```

## 样例 #3

### 输入

```
5
11100
1 2
2 3
3 4
4 5
6
0
1
2
3
4
5```

### 输出

```
3
1
1
-1
-1
-1```

# 题解

## 作者：Wuyanru (赞：9)

开场不到 2h 过了这题，虽然复杂度比正解大点，但是没有关系。

好像是这次铂金组的最难题？但是我不会这次的 T3 啊。

[题目链接](https://www.luogu.com.cn/problem/P9983)。

## 题意

现在有一棵 $ n $ 个点的树，每一个节点上都有一头牛。

这群牛感染了一种病毒，每一天，若一头未被感染的牛与一头已被感染的牛相邻，这头牛下一天就会被感染。

现在告诉你 $ d $ 天以后哪些牛被感染了，求第 $ 0 $ 天时最少有几头牛被感染，或报告无解。

$ q $ 组询问，所有询问只有时间 $ d $ 不同。

$ 2\le n\le 10^5 $。

$ 0\le d\le n $。

$ 1\le q\le 20 $。

## 题解

发现 $ q $ 很小，所以我们只需要对于每一组询问单独考虑就好，对于每一组询问，我们这样求解：

首先我们对于每一个点 $ i $，求出 $ tim_i $ 表示所有最终未被感染的牛中，与 $ i $ 最近的距离是多少。

那么我们就知道，只有 $ tim_i\ge d $ 的点 $ i $ 初始才有可能是感染的。

所以我们现在的问题是，在所有 $ tim_i\ge d $ 的牛中选出尽可能少的点，使他们恰好可以“覆盖”所有最终被感染的点。

发现整个问题不是很好 dp，所以我们考虑贪心。

考虑如下的贪心过程：

1. 找到当前未被覆盖的点中，深度最大的那个，记作点 $ u $；
2. 找到一个点 $ v $ 满足 $ tim_v\ge d $，并且 $ v $ 可以覆盖 $ u $，再此基础上，我们要求 $ v $ 的深度最小；
3. 令 $ v $ 为最初感染的节点，覆盖所有 $ v $ 可以覆盖的点，并令 $ ans\gets ans+1 $。

考虑这个贪心为什么是正确的。

![](https://cdn.luogu.com.cn/upload/image_hosting/2ezkhkdo.png)

如图，点 $ p $ 为 $ \operatorname{lca}(u,v) $。

因为点 $ v $ 的深度最小，所以选择点 $ v $ 可以覆盖尽可能多的 $ p $ 以上的点。

又因为点 $ u $ 是未被覆盖的点中深度最大的，则 $ p $ 子树内其他未被覆盖点都能被覆盖。

所以我们的贪心策略是正确的。

这样我们就得到了一个 $ O(n^2) $ 的做法，考虑进行优化。

---

不难发现，在如上过程中，寻找点 $ v $ 是困难的，但是寻找点 $ p $ 是简单的，因为点 $ p $ 是点 $ u $ 的祖先。

对于每一个点 $ i $，我们求出 $ b_i=\max\limits_{tim_j\ge d}(dep_i+d-\operatorname{dis}(i,j)) $ 与 $ c_i=\min\limits_{tim_j\ge d}(dep_i-d+\operatorname{dis}(i,j)) $。

首先容易发现 $ b_i,c_i $ 取得最值的 $ j $ 是相同的。

分析可以发现，若存在两个点 $ x,y $ 满足 $ x $ 是 $ y $ 的祖先，则有 $ b_x\le b_y $ 与 $ c_x\le c_y $。

那么点 $ p $ 只需要满足 $ b_p\ge dep_u $ 即可，又因为 $ b_p $ 的单调性，我们容易使用二分找出合法的 $ p $。

我们需要点 $ v $ 深度最小，由于 $ c_p $ 的单调性，这个条件也可以转为 $ c_p $ 最小，进而转化为 $ p $ 深度最小。

通过上面的分析，我们已经可以找出最优的 $ p $，那么我们就可以直接知道对应的 $ v $ 了。

---

我们离正解就剩下了最后一步，维护这棵树上的点。

我们的操作分为两种：

+ 选定一个点 $ v $，覆盖所有满足 $ \operatorname{dis}(u,v)\le d $ 的点 $ u $；
+ 对于一个点 $ u $，查询点 $ u $ 是否已经被覆盖。

考虑询问操作。

显然，对于一个点 $ u $，若有点 $ v $ 覆盖点 $ u $，那么就有两种情况，$ v $ 在 $ u $ 子树内和 $ v $ 不在子树内。

若 $ v $ 在 $ u $ 子树内，则 $ dep_u+d\ge dep_v $，使用树剖容易维护这种情况。

若 $ v $ 不在子树内，设 $ p=\operatorname{lca}(u,v) $，则有 $ dep_u+dep_v-2dep_p\ge d $。

那么对于每一个点 $ i $，使用树剖维护 $ l_i=\max\limits_{j\text{在子树内且已经被操作}}dep_j-2dep_i $。

对于查询操作，我们需要对于所有 $ u $ 的祖先 $ p $ 查询是否有 $ dep_u+l_p\ge d $。

本质为链最值操作，容易使用树剖维护。

对于修改操作，我们需要对于所有 $ v $ 的祖先 $ p $ 更新 $ l_p\gets \max(l_p,dep_v-2dep_p) $。

相当于是一条链对一个等差数列取 $ \operatorname{max} $，注意到等差数列公差为定值 $ 2 $，所以也容易使用树剖维护。

综上所述，我们可以使用树剖维护这两种操作。

---

最终的过程，就是我们每一次找当前最深的点，查询它有没有被覆盖。

如果没有被覆盖，就找到上述的 $ v $ 并进行覆盖操作，直至所有点被覆盖。

时间复杂度 $ O(nq\log^2n) $。由于树剖常数小，可以通过。

更好的解决方案：

1. 对于树上的每一条重链，我们单独开一棵动态开点线段树，可以令树剖常数变小；

2. 由于瓶颈主要在于 $ v $ 不在 $ u $ 子树内的情况，而这一部分只有链操作，所以可以使用全局平衡二叉树换掉树剖，时间复杂度 $ O(nq\log n) $。

   可能是因为我写的屎，所以这种方案应该是没有第 $ 1 $ 种跑的快。

## 代码

由于题解是后来写的，补充了很多细节，所以这份代码和上面讲的有一些细节不同。

代码有点长，挂[这里](https://www.luogu.com.cn/paste/2fpdrg7p)。

感谢观看！

---

## 作者：NoGoshPlease (赞：6)

另一种 $O(qn)$ 做法。

题意相当于选择一些点，标记它们的 $k-$邻域，使得标记的点集和给定相同。

注意到题目中 $q$ 很小，于是可以每次询问单独做。

### 首先考虑什么样的点可能被选择

显然等价于距离最小的 $0-$点 与它的距离 $>k$。

于是可以通过一开始向上向下 dp，求出来距离一个点最近的 $0-$点 距离。

这里不必使用换根的方式去做，因为我们取的是最小值，中间如果重复走一段向上向下的路，那么一定不会成为最优答案。

### 然后考虑怎么选择点

考虑一种贪心，每次选择出最靠下的点，然后取出最多走 $x$ 步能走到的所有点，取那个最浅的点（如果有多个任取一个）。

为什么这是对的？

首先，最靠下的点走 $x$ 步能走到的点中，至少选一个。

那么，因为它是最深的，所以最深的点和你选择的点，这两个点 LCA 的子树内所有点都一定会满足要求。

其次，选择最高的一个点会使得向上方尽可能多满足一些要求。

然后就有了一个 $O(n^2q)$ 的做法。

## 如何优化？

### 如何每次找到深度最大的点？

考虑开一个 vector，里面按照深度从小到大存着所有节点。然后每次取出最末尾的，更新状态的时候惰性删除。

### 如何找到这次选择的点？

考虑每次询问，先 dfs 一遍这棵树，求出来每个子树内最浅的可行操作点。

然后查找时候就可以在向上 $k$ 层中，枚举 LCA，然后找到最浅的点，判断一下两段的距离和是否 $\le k$，更新答案。

如果找不到符合要求的点，那么说明无解。

### 如何快速更新状态？

$k-$邻域 这种东西看起来就不是很能快速做，那么我们考虑均摊实现。

首先，根据上述讨论，选择的点的子树内一定可以被全部干掉，那我们就 dfs 一遍干掉内部的点。

对于外部来说，可能有一些枝杈，走进去并不能更新成功子树里面的所有点，那么这步更新就是无效的（自己画图理解一下，子树里面必须还选择一个，它的更新更有优势）。

所以，我们对选择点的到根链的第 $x(x\le k)$ 级祖先打上 $k-x$ 的标记，代表着从它还能向下满足 $k-x$ 步。

相应地，在找到最深点后，先向上跳 $k$ 步检查一下这个点是否真的未被满足。

如果在第 $x$ 级祖先发现可以被覆盖，那么就把第 $x-1$ 级祖先对应的子树内所有点干掉。

## 复杂度分析？

### 引理：天数为 $k$ 的情况下答案不超过 $O(\frac{n}{k})$ 级别

乍一看好像很有道理，但是严格分析却挺有难度。

我们建出来所有选择的点的虚树，我们称原来树当中不在虚树内的部分为“枝杈”。

一个枝杈显然只有最长长度是重要的，那我们不妨讨论所有枝杈都是链的最劣情况。

一个枝杈如果长在虚树的边中间，那么考虑将它划分到离它最近的被选择点。

对于一个被选择点管辖的所有枝杈，显然也只有最长的有用，那么我们考虑最劣情况，每个被选择点只保留最远的管辖内枝杈。

形象化地，我们在虚树上每个点上都挂一个点，边权是最远的管辖内枝杈的距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/o24p0ql5.png)

我们把原来虚树上的点叫做黑点，新添加的点叫做红点，原来虚树上的边叫做黑边，新边叫红边。

对于上面图中的情况，一定有 $x+y>k, \; x+z>k$，不然两个被选择的点就有替代的情况，答案也就不是最小。

也就是说，一条红色-黑色的两条边组成的拐弯，会带来 $k$ 的代价。

我们能在新的虚树上找出 $ans-1$ 对这样的拐弯，和一个富余出来的红边。

黑边在原树中肯定是实打实的树边，红边在原树中可能通过与黑边共用来减少一点。

对于一个黑点伸出的红边，最多只能省下 $\dfrac{\max(相连黑边长度)}{2}$，所有红边加起来最多能省下的也是 $\sum 黑边长度$ 级别的。

所以新的虚树当中所有边边权和是 $O(n)$ 级别的，一个拐弯代价是 $k$，所以答案就是 $O(\frac{n}{k})$ 级别的。

所以每次上跳 $k$ 步这一操作会使得单次询问复杂度变为 $O(\frac{n}{k}\times k)=O(n)$。

对于最深点判定为已覆盖的部分，会把这个子树全扬掉，所以均摊正确。

于是总复杂度 $O(qn)$。

---

## 作者：_lbw_ (赞：6)

## all cows infected 的部分分。

这是经典问题，即为选若干个点，每个点可以覆盖距离它 $\leq L$ 的点，问使所有点都被覆盖的最小选择点数。

从下到上贪心，记录每个点的状态为其子树 未覆盖完/已经覆盖完/还有剩余，对于 1/3 种状态，需要记录 最远未覆盖的距离/最近选择点的距离。

当 当前点为 $1$ 状态且第二维为 $L$ 时，选择此点。

## all subtasks。

我们会发现有一些点一定不能被覆盖，这可以导出一些点一定不能选，即为从不能被覆盖的点开始多源 BFS，距离 $\leq L$ 的点不能选。

接下来有两种选择，按 all cows infected 的方法 贪心/dp，我选择的是贪心。

困难在于如果当前点刚好不够时，这个点可能不能选。

我们有两种方式解决:

- 整体贪心:

每次将最深的点解决掉，找到距离它 $\leq L$ 且深度最小的点，点分治解决之，时间复杂度 $\mathcal{O}(qn\log n)$。

- 预知未来:

再进行一次多源 BFS，找到每个点到它最近的能选的点的距离 $d_u$。

当 当前点为 $1$ 状态且第二维为 $> L-d_{fa}-1$ 时选择此点。

并且注意这个点有可能不能选，这时选择离这个点最近的点即可。

时间复杂度 $\mathcal{O}(qn)$。

```cpp
#undef ll
#define fi first
#define se second
#include "assert.h"
mt19937_64 rnd(her1);
using i64 = long long;
const int maxn = 1e6+5;
#define pii pair<i64,i64>
IV cmin(i64&x,i64 val){x>val?x=val,0:0;}
i64 n,dis[maxn],L,ans,d2[maxn];pair<i64,i64>val[maxn];
queue<i64>qwq;vector<i64>G[maxn];char s[maxn];bool vis[maxn];
pii merge(pii A,pii B){
	if(!A.fi)return B;
	if(!B.fi)return A;
	if(A.fi==-1)swap(A,B);
	if(A.fi==-1)return{-1,max(A.se,B.se)};
	if(B.fi==-1)return A.se+B.se<=L?A:B;
	return{1,min(A.se,B.se)};
}
IV dfs(i64 u,i64 F){
	val[u]=make_pair(vis[u]?-1:0,0);
	for(i64 v:G[u])if(v^F){
		dfs(v,u);
		if(val[v].fi)val[v].se++;
		val[u]=merge(val[u],val[v]);
	}
	// cout<<u<<' '<<val[u].first<<' '<<val[u].second<<endl;
	if(val[u].fi==-1&&(!F||val[u].se+1+d2[F]>L))
		val[u]={1,d2[u]},ans++;
	// cout<<u<<' '<<val[u].first<<' '<<val[u].second<<endl;
}
IV solve(){
	F(i,1,n)d2[i]=1e9;
	F(i,1,n)if(dis[i]>L)qwq.push(i),d2[i]=0;
	while(!qwq.empty()){
		i64 u=qwq.front();qwq.pop();
		for(i64 v:G[u])if(d2[u]+1<d2[v])
			d2[v]=d2[u]+1,qwq.push(v);
	}
	F(i,1,n)if(vis[i]&&d2[i]>L)return(void)(puts("-1"));
	// F(i,1,n)cout<<(dis[i]>L)<<' ';puts("");
	ans=0;dfs(1,0);printf("%lld\n",ans);
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	n=read();scanf("%s",s+1);
	F(i,1,n)vis[i]=s[i]-'0';
	F(i,1,n-1){
		i64 u=read(),v=read();
		G[u].push_back(v);G[v].push_back(u);
	}
	F(i,1,n)dis[i]=1e9;
	F(i,1,n)if(s[i]=='0')dis[i]=0,qwq.push(i);
	while(!qwq.empty()){
		i64 u=qwq.front();qwq.pop();
		for(i64 v:G[u])if(dis[u]+1<dis[v])
			dis[v]=dis[u]+1,qwq.push(v);
	}
	i64 Q=read();while(Q--)L=read(),solve();return 0;
}
```


---

## 作者：Lynkcat (赞：6)

非正解复杂度。不知道什么复杂度。

考虑一个 dp 做法是 $dp_{i,j}$ 表示 $i$ 子树内选了 $j$ 个点，目前的最优状态是什么。$dp_{i,j}\geq 0$ 则表示最远的没覆盖的点距离是 $dp_{i,j}$，否则表示最近的被选中的点距离是 $-dp_{i,j}+1$。

那么每次转移是树形背包，然后值是取绝对值大的，一样取正数。

然后试着把满足 $j<k,dp_{i,j}\leq dp_{i,k}$ 的状态全去掉就过了。

可能是假的，数据太弱。或者有老哥会证明也可以来教教我。

```c++
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e9
#define mod 998244353
#define sz(x) ((int)((x).size()))
using namespace std;
const int N=100005;
vector<pa>dp[N];
poly G[N];
int n,m,Lim,dis[N];
int chk(int x,int y)
{
    if (x>y) swap(x,y);
    if (x<0&&y>=0)
    {
        if (-x>y) return x;
        return y;
    }
    if (abs(x)>=abs(y)) return x;
    return y;
}
int ans;
void dfs(int k,int fa)
{
    vector<pa>().swap(dp[k]);
    if (dis[k]!=0)
        dp[k].push_back(mp(0,0));
    for (auto u:G[k])
    {
        if (u==fa) continue;
        dfs(u,k);
        if (dis[u]==0) continue;
        if (dis[k]==0)
        {
            if (ans==-1) return;
            int nw=-1;
            for (auto [i,j]:dp[u]) 
                if (j<0)
                {
                    nw=i;
                    break;
                }
            if (nw==-1) ans=-1;
            else ans+=nw;
            continue;
        }
        vector<pa>all;
        for (auto [x,y]:dp[k])
            for (auto [i,j]:dp[u])
            {
                all.push_back(mp(x+i,chk(y,j+1)));
            }
        sort(all.begin(),all.end());
        vector<pa>nxt;
        for (auto [u,v]:all)
            if (nxt.empty()||v<nxt.back().se) nxt.push_back(mp(u,v));
        dp[k].swap(nxt);
    }
    vector<pa>nxt,all;
    for (auto [u,v]:dp[k])
    {
        if (v<Lim)
            nxt.push_back(mp(u,v));
        if (dis[k]>Lim) nxt.push_back(mp(u+1,-Lim-1));
    }
    for (auto [u,v]:nxt)
        if (all.empty()||v<all.back().se) all.push_back(mp(u,v));
    dp[k].swap(all);
    
}
void BellaKira()
{
    cin>>n;
    for (int i=1;i<=n;i++) dis[i]=inf;
    queue<int>q;
    for (int i=1;i<=n;i++)
    {
        char c;
        cin>>c;
        if (c=='0') dis[i]=0,q.push(i);
    }
    for (int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    G[n+1].push_back(1);
    dis[n+1]=0;
    while (!q.empty())
    {
        int u=q.front();q.pop();
        for (auto v:G[u])
            if (dis[v]==inf)
            {
                dis[v]=dis[u]+1;
                q.push(v);
            }
    }
    cin>>m;
    while (m--)
    {
        cin>>Lim;
        ans=0;
        dfs(n+1,0);
        cout<<ans<<'\n';
    }
}
signed main()
{
    IOS;
    cin.tie(0);
    int T=1;
    while (T--)
    {
        BellaKira();
    }
}
/*list:
1.mod 998244353 or 1e9+7 or ???
2.N
3.duipai shuju xingtai duoyidian
...
*/

---

## 作者：Harry27182 (赞：5)

想不到一点/ll 想不到一点/ll

首先考虑全是 1 的情况，不难想出一个贪心策略，每次选择深度最深的需要被覆盖的节点，然后倍增找到他的 $d$ 级祖先，记 $d$ 级祖先为 $p$，操作一次 $p$。容易发现这样一定不劣，因为这个节点一定要被干掉，操作 $p$ 的后代显然不如操作 $p$ 能处理的节点多。我也就只会这些了/ll。

然后看了看题解，发现这个思路是可以拓展的。我们记 $tim_u$ 表示 $u$ 这个节点距离最近的 0 节点的距离，不难发现只有 $tim_x>d$ 的 $x$ 才能被操作。我们考虑仍然是找到深度最深的需要被覆盖的节点 $u$，类比上面，发现最优方案是选择深度最浅的合法的 $v$ 操作。令 $p=lca(u,v)$，不难发现 $dep_v$ 最小的话，$dep_p$ 也会最小，所以 $p$ 子树能够被全部处理，当 $p$ 确定时，$dep_v$ 最小能够让 $p$ 子树外处理的最多，所以选择 $dep_v$ 最小的 $v$ 是最优的。所以我们就有了这样一个贪心的算法，暴力实现是 $O(n^2q)$ 的，结合特殊性质可以获得 $50$ 分。

上面已经说了对于每个 $p$ 要去寻找距离 $p$ 最近的 $v$，这个东西是可以 bfs 一遍预处理出来的。然后我们需要满足的条件就是 $dis(u,v)\leq d$。拆一下式子 $dep_u-dep_p+dis(p,v)\leq d$，也就是 $dep_p+d-dis(p,v)\geq dis_u$。发现前面的一堆东西只和 $p$ 有关，所以可以在 bfs 的过程中顺便预处理出来。然后需要找到满足这个条件的 $dep_p$ 最小的 $p$。设 $b_x=\max(dep_x+d-dis(x,v))$，容易发现 $b_{fa_x}\leq b_x$，因为给 $b_{fa_x}$ 的那个 $v$ 可以给 $x$ 用。所以只需要倍增找到深度最小的合法的 $p$，然后也就找到了需要操作的 $v$。

然后我们需要支持两种操作，把与 $x$ 距离 $\leq d$ 的点涂黑，求一个点是黑还是白。点分治经典问题。建出点分树然后对于每个点维护子树内到这个点距离 $\leq len_x$ 的点已经被涂黑的 $len_x$，修改的时候对于每个点分树上祖先更新 $len_x$，查询的时候查询自己是否会被点分树上每一个祖先所涂黑，时间复杂度 $O(nq\log n)$，常数不大，可以比较轻松地通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct edge{int v,nxt;}e[N<<1];
int h[N],mx[N],siz[N],vis[N],S,rt,cnt,p[N],dep[N],dfn[N],tot,st[20][N<<1],f[N][20];
int n,Log[N<<1],tim[N],a[N],b[N],len[N],dis[N],pos[N],id[N],u,v,q,x;char s[N];
void add(int u,int v){e[++cnt]={v,h[u]};h[u]=cnt;}
void find(int u,int fa)
{
	mx[u]=0;siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		find(v,u);siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],S-siz[u]);
	if(mx[u]<mx[rt])rt=u;
}
int get(int u,int fa)
{
	int res=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		res+=get(v,u);
	}
	return res;
}
void build(int u)
{
	vis[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v])continue;
		mx[rt=0]=0x3f3f3f3f;S=get(v,u);find(v,u);p[rt]=u;build(rt);
	}
}
void init(int u,int fa)
{
	dep[u]=dep[fa]+1;dfn[u]=++tot;st[0][tot]=dep[u];f[u][0]=fa;
	for(int i=1;(1<<i)<=n;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		init(v,u);st[0][++tot]=dep[u];
	}
}
int getdis(int u,int v)
{
	int res=dep[u]+dep[v];
	u=dfn[u];v=dfn[v];if(u>v)swap(u,v);
	int k=Log[v-u+1]; 
	return res-2*min(st[k][u],st[k][v-(1<<k)+1]);
}
void bfs()
{
	queue<int>q;
	for(int i=1;i<=n;i++)tim[i]=0x3f3f3f3f;
	for(int i=1;i<=n;i++)if(!a[i])q.push(i),tim[i]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(tim[v]==0x3f3f3f3f)tim[v]=tim[u]+1,q.push(v);
		}
	}
}
bool cmp(int x,int y){return dep[x]>dep[y];}
int jump(int u,int d)
{
	for(int i=18;i>=0;i--)if(b[f[u][i]]>=d)u=f[u][i];
	return u;
}
void ban(int x,int d)
{
	for(int i=x;i;i=p[i])
	{
		int now=d-getdis(x,i);
		if(now>=0)len[i]=max(len[i],now);
	}
}
int check(int x)
{
	for(int i=x;i;i=p[i])
	{
		int now=getdis(x,i);
		if(now<=len[i])return 1;
	}
	return 0;
}
int solve(int x)
{
	queue<int>q;
	for(int i=1;i<=n;i++)dis[i]=-1,len[i]=-1;
	for(int i=1;i<=n;i++)if(tim[i]>x)q.push(i),dis[i]=0,pos[i]=i;
	if(!q.size())return -1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(dis[v]==-1)dis[v]=dis[u]+1,pos[v]=pos[u],q.push(v);
		}
	}
	for(int i=1;i<=n;i++)b[i]=dep[i]+x-dis[i];
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,cmp);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int u=id[i];
		if(!a[u]||check(u))continue;
		if(b[u]<dep[u])return -1;
		int fa=jump(u,dep[u]),v=pos[fa];
		ban(v,x);ans++;
	}
	return ans;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>(s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	mx[rt=0]=0x3f3f3f3f;S=n;build(1);init(1,0);bfs();
	for(int i=2;i<=tot;i++)Log[i]=Log[i>>1]+1;
	for(int j=1;(1<<j)<=tot;j++)
	{
		for(int i=1;i+(1<<j)-1<=tot;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]); 
	}
	cin>>q;
	while(q--)
	{
		cin>>x;
		cout<<solve(x)<<'\n';
	}
	return 0;
}
```

---

## 作者：Ranya (赞：3)

补充一个点分树写法，写的很丑。

# 题意
给出 $n$ 个点的树和长度为 $n$ 的 01 串。问初始最少有多少个树上的点被染黑（每经过一天，黑点会染黑和它相邻的所有点），经过 $d$ 天后可以使所有点的颜色序列和 01 串一一对应（0：白 1：黑）。

$Q$ 个询问，每次询问给出 $d$。若无解则输出 -1。

$Q\le 20, d\le n\le 10^5$

# 题解

参考了[第一篇题解](https://www.luogu.com.cn/article/z62r22w1)的贪心，用的点分树实现。

设 $tim_i$ 表示 $i$ 到最近的最终没被染黑的点距离，发现只有 $tim_i>d$ 的点可能初始被染黑。

每次贪心考虑当前没被覆盖的最深的最终要被染黑的点 $u$，找到最浅的可以覆盖 $u$ 的满足 $tim_v>d$ 的点 $v$，设 $lca(u,v)=p$。

$u$ 用一个堆维护即可，深度为第一关键字。

$v$ 不好直接找，但可以找 $p$。设 $b_i=\max_{tim_j>d} dep_i+d-dis(i,j)$，则点 $p$ 需要满足 $b_p\ge dep[u]$。可以发现 $b$ 从祖先到儿子非严格递增，所以二分 $p$，深度尽量浅。

得到 $v$ 之后，我们要覆盖所有 $dis(x,v)\le d$ 的点 $x$。这是一个经典问题，可以点分树解决。

具体的，建出点分树后开一个 vector 数组 $a$，$a_i$ 里面存储了 $i$ 的点分树子树的所有点到它的距离，从小到大排列。

点分树具有以下性质：

1. 树高 log
2. 对于任意 $u,v$，他们在点分树上的 $lca$ 一定在原树 u 到 v 的路径上，即 $dis(u,v)=dis(u,lca)+dis(v,lca)$

所以我们要覆盖 $dis(v,x)\le d$ 的点，即 $dis(v,lca)+dis(x,lca)\le d$，所以考虑枚举 $ lca$，也就是 $v$ 在点分树上的所有祖先。枚举到后，会覆盖 $a_{lca}$ 的前缀，对每个点用一个指针记录最远覆盖到的位置即可。

时间 $\mathcal{O}(n\log^2_n+qn\log_n)$

空间 $\mathcal{O}(n\log n)$

# 代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

typedef long long ll;
int read() {
	int x=0; char to=getchar();
	while (!isdigit(to)) to=getchar();
	while (isdigit(to)) x=x*10+to-48, to=getchar();
	return x;
}

const int N=1e5+3, inf=1e9;
int n, tim[N], dep[N], jp[N][17];
vector<int> e[N];
char s[N];

void dfs(const int u, const int dad) {
	dep[u]=dep[dad]+1;
	jp[u][0]=dad;
	for (int i=1; i<17; i++)
		jp[u][i]=jp[jp[u][i-1]][i-1];
	if (s[u]&1) tim[u]=inf;
	for (int v:e[u]) if (v!=dad) {
		dfs(v, u);
		tim[u]=min(tim[u], tim[v]+1);
	}
}
void dfs(const int u, const int dad, int ori, int fi) {
	tim[u]=min(tim[u], fi);
	int se;
	if (s[u]&1) se=inf;
	else se=fi, ori=u, fi=0;
	for (int v:e[u]) if (v!=dad) {
		if (tim[v]+1<fi) se=fi, fi=tim[v]+1, ori=v;
		else if (tim[v]+1<se) se=tim[v]+1;
	}
	for (int v:e[u]) if (v!=dad) {
		if (ori==v) dfs(v, u, u, se+1);
		else dfs(v, u, u, fi+1);
	}
}

int root, rt, all, vis[N], sz[N], mx[N];
struct node {
	int x, w;

	int operator < (node &p) const {
		return w<p.w;
	}
};
vector<node> a[N];
int pt[N], fa[N];
unordered_map<int, int> mp[N];
void init(int u, int dad) {
	sz[u]=1, mx[u]=0;
	for (int v:e[u]) if (v!=dad&&!vis[v]) {
		init(v, u);
		sz[u]+=sz[v];
		mx[u]=max(mx[u], sz[v]);
	}
	mx[u]=max(mx[u], all-sz[u]);
	if (mx[u]<mx[rt]) rt=u;
}
void init(int u, int dad, int dis) {
	sz[u]=1;
	for (int v:e[u]) if (v!=dad&&!vis[v]) {
		a[rt].push_back({v, dis+1});
		mp[v][rt]=dis+1;
		init(v, u, dis+1);
		sz[u]+=sz[v];
	}
}
void build(int u) {
	init(u, 0, 0);
	vis[u]=1;
	for (int v:e[u]) if (!vis[v]) {
		all=sz[v], rt=0;
		init(v, 0), fa[rt]=u;
		build(rt);
	}
}

#define pii pair<int, int> 
int d, tag[N], f[N], mi[N];
priority_queue<pii> q;
void pre(int u, int dad) {
	if (tag[u]) mi[u]=u, f[u]=0;
	else mi[u]=0, f[u]=inf;
	for (int v:e[u]) if (v!=dad) {
		pre(v, u);
		if (f[v]+1<f[u]) mi[u]=mi[v], f[u]=f[v]+1;
	}
}
void pre(int u, int dad, int ori, int fi) {
	int se, o2;
	if (tag[u]) se=fi, o2=ori, ori=u, fi=0;
	else se=inf, o2=0;
	if (fi<f[u]) f[u]=fi, mi[u]=ori;
	for (int v:e[u]) if (v!=dad) {
		if (f[v]+1<fi) o2=ori, se=fi, fi=f[v]+1, ori=v;
		else if (f[v]+1<se) o2=v, se=f[v]+1;
	}
	for (int v:e[u]) if (v!=dad) {
		if (ori==v) pre(v, u, o2, se+1);
		else pre(v, u, ori, fi+1);
	}
}
void solve() {
	while (!q.empty()) q.pop();
	d=read();
	for (int i=1; i<=n; i++) {
		tag[i]=s[i]&(tim[i]>d);
		if (s[i]&1) q.push({dep[i], i});
		pt[i]=0, f[i]=inf, vis[i]=0;
	}
	pre(1, 0), pre(1, 0, 0, inf);
	for (int i=1; i<=n; i++) f[i]=dep[i]+d-f[i];
	int ans=0;
	while (!q.empty()) {
		int u=q.top().second; q.pop();
		if (vis[u]) continue;
		ans++;
		int o=u;
		for (int i=16; i>=0; i--) 
			if (f[jp[o][i]]>=dep[u]) o=jp[o][i];
		if (f[o]<-n) return puts("-1"), void();
		if (o==u&&f[u]<dep[u]) return puts("-1"), void();
		int v=mi[o];
		for (int cur=v; cur; cur=fa[cur]) {
			int w=d-mp[v][cur];
			if (w<0) continue;
			vis[cur]=1;
			for (int &i=pt[cur]; i<a[cur].size(); i++) {
				if (a[cur][i].w<=w) vis[a[cur][i].x]=1;
				else break;
			}
		}
	}
	if (!ans) puts("-1");
	else printf("%d\n", ans);
}

int main() {
	n=read();
	scanf("%s", s+1);
	int flag=1;
	for (int i=1; i<=n; i++) if (s[i]&1) flag=0;
	for (int i=1; i<n; i++) {
		int x=read(), y=read();
		e[x].push_back(y), e[y].push_back(x);
	}
	dfs(1, 0), dfs(1, 0, 0, inf);
	all=n, rt=0, mx[0]=inf;
	init(1, 0), root=rt;
	build(rt);
	for (int i=1; i<=n; i++)
		sort(a[i].begin(), a[i].end());
	f[0]=-inf;
	int Q=read();
	while (Q--) 
		if (flag) puts("0");
		else solve();
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

这个题做法挺多，总结几种我会的。为方便讨论，称**黑点**为被感染的点，**白点**反之，**选点**表示选出一个一开始就被感染的点的过程，**可选点**表示能被选择而不影响白点的点，**覆盖**表示被选择的点经过若干天，传染到某个其他点的过程。

---

#### 解法一：贪心、数据结构

我们把树定一个根，先只关注最深的黑点，此时不妨先选一个点使得其能覆盖到该黑点。若有多个可选点满足此条件怎么办？不难思考到，应当选择对后面帮助最大的点，也就是深度最小的那个。

用点分树维护距离不超过 $k$ 的点集。由于可选点不带修改，用前缀最值维护，可以做到 $O(nq\log{n})$。

对结论的感性理解：若更有的选点其实是在更深处，那么必然是为了覆盖一些其他黑点。但是当前黑点已经是深度最深的了，因此不会出现这样的情况。

#### 解法二：贪心、复杂度分析

题解区已经有人证明日期是 $k$ 时答案量级为 $O(\frac{n}{k})$。

有了这样的结论，我们知道每次直接跳链找点的过程其实是 $O(\frac{n}{k} \times k) = O(n)$ 的。因此点分树可以被省去，取而代之的是在每个树点上打标记，表示当前子树内深度小于某个值的点已经被全部覆盖。

#### 解法三：动规、贪心

树上距离相关问题，看着像 dp，实际上确实可以，只是状态略显复杂。

记录 $f_i = 0/1$ 表示 $i$ 的子树内是可以往外覆盖还是需要外部点覆盖自己，$g_i$ 表示具体的剩余或需要值。不难根据儿子节点的信息计算出当前节点的 $f$ 和 $g$。

难点在于选点。再记录 $dis_i$ 表示 $i$ 距离最近可选点的距离，如果 $f_i = 1$ 且 $g_i < k - dis_{fa} - 1$，就说明不能指望父亲以上的点了，必须依靠子树内的点，这时直接选择，并对应修改 $f$ 和 $g$ 的值。

---

其实三种做法多少都有类似的贪心思想：先覆盖最深的点，再考虑覆盖其他尽量多的点，即不得已时再进行选点。

代码使用第一种较为繁琐的写法，放在这里供对拍用。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
typedef pair < int, int > PII;
int n, m, k, ps[N]; bool s[N]; vector < int > edge[N];

struct query {int num, id;} qu[25]; int ans[25];
inline bool cmp_query(query u, query v) {return u.num > v.num;}

bool ok[N], ls[N]; queue < PII > q;
inline void bfs()
{
	for(int i = 1; i <= n; ++i) ls[i] = ok[i];
	for(int i = 1; i <= n; ++i) ok[i] = true;
	for(int i = 1; i <= n; ++i)
		if(s[i] == 0)
			q.push({i, 0}), ok[i] = false;
	while(!q.empty())
	{
		int now = q.front().first, dis = q.front().second; q.pop();
		if(dis == k) continue;
		for(int to : edge[now])
		{
			if(!ok[to]) continue;
			ok[to] = false;
			q.push({to, dis + 1});
		}
	}
}

struct dy_tree_divide
{
	int fa[N], sz[N];
	
	int seq[N * 2][21], len, dep[N], lft[N];
	inline void init(int now, int prt)
	{
		seq[++len][0] = now, dep[now] = dep[prt] + 1;
		for(int to : edge[now])
		{
			if(to == prt) continue;
			init(to, now);
			seq[++len][0] = now;
		}
	}
	inline void init_LCA()
	{
		for(int i = 1; (1 << i) <= len; ++i)
		{
			for(int j = 1; j + (1 << i) - 1 <= len; ++j)
			{
				if(dep[seq[j][i - 1]] <= dep[seq[j + (1 << (i - 1))][i - 1]])
					seq[j][i] = seq[j][i - 1];
				else seq[j][i] = seq[j + (1 << (i - 1))][i - 1];
			}
		}
		for(int i = len; i >= 1; --i) lft[seq[i][0]] = i;
	}
	inline int LCA(int x, int y)
	{
		if(lft[x] > lft[y]) swap(x, y);
		int k = log2(lft[y] - lft[x] + 1);
		if(dep[seq[lft[x]][k]] <= dep[seq[lft[y] - (1 << k) + 1][k]])
			return seq[lft[x]][k];
		else return seq[lft[y] - (1 << k) + 1][k];
	}
	inline int get_dist(int x, int y)
	{return dep[x] + dep[y] - 2 * dep[LCA(x, y)];}
	
	int sum, siz[N], dp[N], pt, comp; bool ban[N];
	inline void explore(int now, int prt)
	{
		++sum;
		for(int to : edge[now])
		{
			if(to == prt || ban[to]) continue;
			explore(to, now);
		}
	}
	inline void treedp(int now, int prt)
	{
		siz[now] = 1; dp[now] = 0;
		for(int to : edge[now])
		{
			if(to == prt || ban[to]) continue;
			treedp(to, now);
			siz[now] += siz[to];
			dp[now] = max(dp[now], siz[to]);
		}
		dp[now] = max(dp[now], sum - siz[now]);
		if(dp[now] < comp) {comp = dp[now]; pt = now;}
	}
	inline void build(int now)
	{
		sz[now] = 1; ban[now] = true;
		for(int to : edge[now])
		{
			if(ban[to]) continue;
			sum = 0, comp = 1e9; explore(to, 0);
			treedp(to, 0);
			int nx = pt; fa[nx] = now;
			build(nx); sz[now] += sz[nx]; 
		}
	}
	
	vector < int > f[N]; int cov[N];
	inline void insert(int now)
	{
		int pos = now;
		while(pos)
		{
			int d = get_dist(pos, now);
			if(!f[pos][d] || dep[f[pos][d]] > dep[now]) f[pos][d] = now;
			pos = fa[pos];
		}
	}
	inline void cover(int now, int dis)
	{
		int pos = now;
		while(pos)
		{
			int d = get_dist(pos, now);
			cov[pos] = max(cov[pos], dis - d);
			pos = fa[pos];
		}
	}
	inline bool check(int now, int dis)
	{
		int pos = now;
		while(pos)
		{
			if(cov[pos] >= get_dist(pos, now)) return false;
			pos = fa[pos];
		}
		return true;
	}
	inline int find(int now, int dis)
	{
		int pos = now, pt = 0;
		while(pos)
		{
			int d = min(sz[pos], dis - get_dist(now, pos));
			if(d >= 0 && f[pos][d] && (!pt || dep[pt] > dep[f[pos][d]]))
				pt = f[pos][d];
			pos = fa[pos];
		}
		return pt;
	}
	
	inline void reset()
	{
		for(int i = 1; i <= n; ++i) cov[i] = -1;
		for(int i = 1; i <= n; ++i) if(!ls[i] && ok[i]) insert(i);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= sz[i]; ++j)
				if(!f[i][j] || (f[i][j - 1] && dep[f[i][j]] > dep[f[i][j - 1]]))
					f[i][j] = f[i][j - 1];
	}
	inline void setup()
	{
		init(1, 0); init_LCA();
		
		sum = 0, comp = 1e9; explore(1, 0);
		treedp(1, 0); build(pt);
		
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j <= sz[i] + 1; ++j)
				f[i].push_back(0);
	}
}; dy_tree_divide T;

inline bool cmp(int x, int y) {return T.dep[x] > T.dep[y];}
inline long long solve()
{
	bfs();
	T.reset();
	int sig = 0;
	for(int i = 1; i <= n; ++i)
	{
		if(!s[ps[i]]) continue;
		if(!T.check(ps[i], k)) continue;
		int pt = T.find(ps[i], k);
		if(!pt) return -1;
		T.cover(pt, k); ++sig;
	}
	return sig;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		char c; cin >> c;
		s[i] = c - '0';
	}
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	T.setup();
	for(int i = 1; i <= n; ++i) ps[i] = i;
	sort(ps + 1, ps + n + 1, cmp);
	cin >> m;
	for(int i = 1; i <= m; ++i) cin >> qu[i].num, qu[i].id = i;
	sort(qu + 1, qu + m + 1, cmp_query);
	for(int i = 1; i <= m; ++i)
	{
		k = qu[i].num;
		ans[qu[i].id] = solve();
	}
	for(int i = 1; i <= m; ++i) cout << ans[i] << '\n';
	return 0;
}
/*
5
11111
1 2
2 3
3 4
4 5
1
5
*/
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P9983)

**题目大意**

> 给定一棵 $n$ 个点的树，有一些点是黑色，$q$ 次询问 $x$，求最小的 $|S|$，使得将距离 $S$ 中点 $\le x$ 的点全部染黑后，每个点的着色情况恰好和题目给出的一致。
>
> 数据范围：$n\le 10^5,q\le 20$。

**思路分析**

先考虑所有点是黑色的情况。

从最深的点 $u$ 开始考虑，如果 $u$ 还未被覆盖，我们要选一个点既能覆盖 $u$，对外界的影响又尽可能大。

显然考虑 $u$ 的 $x$ 级祖先 $v$，那么 $v$ 子树内的点都会被覆盖，并且对 $v$ 子树外的影响是最大的。

然后考虑一般的情况，设一个点 $u$ 到未被染色的点的距离为 $p_u$，那么我们只选操作 $p_u>x$ 的点。

还是从最深的点 $u$ 开始考虑，那么我们就是要找到一个 $v$ 使得 $\mathrm{dist}(u,v)\le x,p_v>x$ 且 $u$ 尽可能浅。

这样的 $v$ 并不好维护，因为 $v$ 的信息和 $\mathrm{LCA}(u,v)$ 有关。

不妨尝试找最浅的 $w=\mathrm{LCA}(u,v)$，$w$ 固定时，$\mathrm{dist}(v,w)$ 越浅越容易合法，同时此时 $v$ 深度更浅，那么 $v$ 就是子树内最浅的 $p_v>x$ 的 $v$。

那么设 $dis_w$ 表示子树内这样的 $v$ 对应的 $\mathrm{dist}(v,w)$，我们就要求 $dis_w+dep_u-dep_w\le x$ 即 $dep_u\le x+dep_w-dis_w$。

但是此时随着 $w$ 的增加，$dep_w$ 增加，但 $dis_w$ 单调性未知。

但我们发现如果设 $dis_w$ 为所有 $p_v>x$ 的 $v$ 中最小的 $\mathrm{dist}(v,w)$，即去掉子树内限制后，一定有 $|dis_{w}-dis_{fa(w)}|\le 1$.

因此 $w\to fa_w$ 时的变化量一定 $\in[-2,0]$，因此 $x+dep_w-dis_w$ 单调递减，可以倍增出最浅的合法的 $w$。

不难发现此时 $w$ 确实是 $\mathrm{LCA}(u,v)$，因为如果这样的 $v$ 存在，那么 $\mathrm{LCA}(u,v)$ 一定合法，故 $w$ 一定会跳到 $\mathrm{LCA}(u,v)$ 上。

而 $v$ 只要在维护 $dis_w$ 时记录其取值点即可，然后我们要支持覆盖距离 $v$ 不超过 $x$ 的所有点，并查询一个点是否被覆盖，直接点分树维护即可。

时间复杂度 $\mathcal O(nq\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,lim,pri[MAXN],dep[MAXN],dfn[MAXN],dcnt,st[MAXN][20],up[MAXN][20];
char op[MAXN];
vector <int> G[MAXN];
void bfs1() {
	queue <int> q;
	memset(pri,0x3f,sizeof(pri));
	for(int i=1;i<=n;++i) if(op[i]=='0') pri[i]=0,q.push(i);
	while(q.size()) {
		int u=q.front(); q.pop();
		for(int v:G[u]) if(pri[v]>pri[u]+1) q.push(v),pri[v]=pri[u]+1;
	}
}
void dfs0(int u,int fz) {
	dfn[u]=++dcnt,dep[u]=dep[fz]+1,st[dcnt][0]=up[u][0]=fz;
	for(int k=1;k<20;++k) up[u][k]=up[up[u][k-1]][k-1];
	for(int v:G[u]) if(v^fz) dfs0(v,u);
}
int bit(int x) { return 1<<x; }
int cmp(int x,int y) { return dfn[x]<dfn[y]?x:y; }
int dist(int x,int y) {
	if(x==y) return 0;
	int l=min(dfn[x],dfn[y])+1,r=max(dfn[x],dfn[y]),k=__lg(r-l+1);
	return dep[x]+dep[y]-2*dep[cmp(st[l][k],st[r-bit(k)+1][k])];
}
int fa[MAXN],siz[MAXN],cur[MAXN];
bool vis[MAXN];
void dfs1(int u) {
	vis[u]=true;
	function<void(int,int)> dfs2=[&](int x,int fz) {
		siz[x]=1;
		for(int y:G[x]) if(y!=fz&&!vis[y]) dfs2(y,x),siz[x]+=siz[y];
	};
	dfs2(u,0);
	for(int v:G[u]) if(!vis[v]) {
		int rt=0;
		function<void(int,int)> dfs3=[&](int x,int fz) {
			cur[x]=siz[v]-siz[x];
			for(int y:G[x]) if(y!=fz&&!vis[y]) dfs3(y,x),cur[x]=max(cur[x],siz[y]);
			if(!rt||cur[rt]>cur[x]) rt=x;
		};
		dfs3(v,u),fa[rt]=u,dfs1(rt);
	}
}
int d[MAXN],ver[MAXN],rd[MAXN];
void bfs2() {
	queue <int> q; memset(d,0x3f,sizeof(d));
	for(int i=1;i<=n;++i) if(pri[i]>lim) d[i]=0,ver[i]=i,q.push(i);
	while(q.size()) {
		int u=q.front(); q.pop();
		for(int v:G[u]) if(d[v]>d[u]+1) ver[v]=ver[u],d[v]=d[u]+1,q.push(v);
	}
}
void upd(int x) { for(int u=x;u;u=fa[u]) rd[u]=max(rd[u],lim-dist(x,u)); }
bool qry(int x) { for(int u=x;u;u=fa[u]) if(rd[u]>=dist(u,x)) return true; return false; }
vector <int> ord;
void solve() {
	scanf("%d",&lim),bfs2();
	memset(rd,-0x3f,sizeof(rd));
	int ans=0;
	for(int u:ord) {
		if(qry(u)) continue;
		if(d[u]>lim) return puts("-1"),void();
		int v=u;
		for(int k=19;~k;--k) if(up[v][k]&&d[up[v][k]]+dep[u]-dep[up[v][k]]<=lim) v=up[v][k];
		upd(ver[v]),++ans;
	}
	printf("%d\n",ans);
}
signed main() {
	int T;
	scanf("%d%s",&n,op+1);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	bfs1(),dfs0(1,0);
	for(int k=1;k<20;++k) for(int i=1;i+bit(k)-1<=n;++i) {
		st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	}
	for(int i=1;i<=n;++i) if(op[i]=='1') ord.push_back(i);
	sort(ord.begin(),ord.end(),[&](int x,int y){ return dep[x]>dep[y]; });
	dfs1(1),scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：critnos (赞：0)

写了差不多 4h。6。

首先可知某些点一定不能选，然后就相当于选一些点，每个点能够覆盖距离他 $\le x$ 的点。

然后进行一个 LJJ 的 dp。设 $f_{x,i}$ 表示子树中还有点没被覆盖，没被覆盖的点的最深深度为 $i$，$g_{x,i}$ 表示子树中的点完全被覆盖了，最浅的选择的点深度为 $i$。注意空子树，可以转移。

具体来说，如果子树中所有的点都被覆盖了，那么显然只有最浅的被选择的点有用。

然后长剖，合并子树的时候要做一些单点修改，求区间最小值，$\forall i \in[l,r],f'_{i}\gets\min(f'_i,f_i+k)$ 的操作

具体的，以将某个子树 $y$ 的 $f$ 合并到长子树 $x$ 的 $f$ 上为例。$f_{x,i}+f_{y,j}\to f'_{x,\max(i,j)}$，枚举 $f_{y,j}$，那么把 $f'_{x,j}$ 用 $\min f_{x,\le j}+f_{y,j}$ 更新，然后 $\forall i>j,f'_{x,i}\gets\min(f'_{x,i},f_{x,i}+f_{y,j})$。其他的操作、$x\gets fa_x$、选择根同理。
 
把第三类操作全部求出来后用 ODT 取个 $\min$ 转区间加，线段树维护即可。极限卡常通过。

[代码](https://www.luogu.com.cn/paste/ojywcpom)

---

