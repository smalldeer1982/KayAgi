# Tree of Life

## 题目描述

在一个古老王国的中心，生长着传奇的生命之树——这是独一无二的存在，也是整个世界魔法力量的源泉。该树由 $ n $ 个节点组成，树的每个节点都是一个魔法源，通过魔法通道（边）连接到其他这样的源。树中总共有 $ n-1 $ 条通道，第 $ i $ 条通道连接节点 $ v_i $ 和 $ u_i $。此外，树中任意两个节点之间存在一条唯一的简单路径。

然而，这些通道中流动的魔法能量必须保持平衡；否则，生命之树的力量可能扰乱自然秩序，造成灾难性的后果。王国的智者们发现，当两条魔法通道汇聚到一个节点时，会在它们之间产生一种危险的“魔法共振振动”。为了保护生命之树并维持其平衡，必须选择几条路径并沿着它们进行特殊的仪式。路径是一个由不同节点 $ v_1, v_2, \ldots, v_k $ 组成的序列，其中每一对相邻节点 $ v_i $ 和 $ v_{i+1} $ 由一条通道连接。当智者们沿着这样的路径进行仪式时，对于每个 $ 1 \leq i \leq k - 2 $，通道 $ (v_i, v_{i+1}) $ 和 $ (v_{i+1}, v_{i+2}) $ 之间的共振振动会被阻断。

智者们的任务是选择最少数量的路径，并沿着它们进行仪式，以阻止所有的共振振动。这意味着，对于从单个节点发出的每一对通道，必须至少存在一条选定的路径包含这两条通道。

帮助智者们找到最少数量的路径，以确保生命之树的魔法平衡得以保持，其力量继续滋养整个世界！

## 说明/提示

在第一个测试用例中，有两个从单个节点发出的通道对：$ (1, 2) $ 和 $ (2, 3) ， (2, 3) $ 和 $ (3, 4) $。在路径 $ 1-2-3-4 $ 上进行仪式是足够的。因此，答案是 $ 1 $。

在第二个测试用例中，从单个节点发出的通道没有对，因此答案是 $ 0 $。

在第三个测试用例中，仪式可以沿着路径 $ 2-1-3 ， 2-1-4 $ 和 $ 3-1-4 $ 进行。

## 样例 #1

### 输入

```
5
4
1 2
2 3
3 4
2
1 2
4
1 2
1 3
1 4
8
3 7
2 4
1 2
2 5
3 6
1 3
3 8
6
2 3
1 2
3 6
1 5
1 4```

### 输出

```
1
0
3
7
3```

# 题解

## 作者：chenxi2009 (赞：16)

## 思路
OI 赛制模拟赛把这个切了，遂写一篇题解“昭告天下”。

这是一个没有特殊定根、没有反悔贪心的做法。

如果一个点的度数是 $d$，这个点的每两条边都要共用一条路径，那么显然经过这个点的路径条数至少有 $\frac{d(d-1)}{2}$。

从上往下做显然不可行，考虑从下往上，如果儿子的度数是 $x$，那么儿子处的路径至少有 $x-1$ 条用了儿子和父亲连接的边，这些路径可以传上去给父亲用，如果父亲的度数是 $y$，那么父亲要拿这条边和其他边连接共 $y-1$ 条路径，所以这样做可以节省最多 $y-1$ 条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/6kqifnp0.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

如上图，围绕 $2$ 号点应有 $3$ 条路径，围绕 $4$ 号点应有 $10$ 条路径，但是 $5\to 4\to 2$、$6\to4\to2$ 等围绕 $4$ 的路径是可以和 $4\to 2\to 1$、$4\to 2\to 3$ 合并的，可以节省两条路径，实际答案为 $3+10-2=11$。

仅此而已吗？

并非。注意到如果一个儿子给父亲传上来了一条路径，另一个儿子也给父亲传上来了一条路径，那么这两条路径可以在父亲处接在一起，节省了一条路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ng3iatl.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

如上图，$2,3$ 号点分别有 $6$ 条路径，各自往其父亲——$1$ 号点处上传了 $3$ 条路径。$1$ 号点原先需要 $1$ 条路径，但消耗了来自 $2,3$ 号点的路径各一条，实际上产生了 $-1$ 条路径（把原先的两条路径拼起来覆盖 $1$ 号点的需求，相当于少了一条）；$2,3$ 号点上传的路径还各自有 $2$ 条，拼凑起来又省了两条。答案为 $1+6+6-2-2=9$。其中前一个 $-2$ 是两个儿子上传到 $1$ 的共两条边满足了父亲的需求，后一个 $-2$ 是两个儿子剩余上传的四条边相互拼凑所节省的路径。

这里有两点需要注意：
- 刚刚的 $1$ 号点初始需求为 $1$，但是我们完成它的需求却造成了 $-2$ 的贡献，这是因为完成需求只需要一条上传路径，而我们另一边的儿子还可以再上传一条路径进行拼凑。**注意每个儿子上传用来进行此类拼凑的路径数量是有限的，上限是前面提到的那个 $y-1$**。**这样的拼凑消耗一条上传路径就可以造成 $-1$ 的贡献，贡献比为 $1$**。
- 若消耗两个儿子上传的边各一条进行原先需求之外的拼凑，则**需要消耗共两条上传路径才能造成 $-1$ 的贡献，贡献比是 $0.5$**。这样的拼凑没有数量上限，但是要求拼凑的两条上传路径不来自同一个子树（来自同一个子树的话就会有相同的边了）。

我们先考虑第二类拼凑的情况，发现有的时候并不是所有上传路径都能用来拼凑的。比如说如果上面那个例子中 $2$ 号点有 $10^5$ 个儿子，当它上传 $10^5$ 条路径的时候 $3$ 号点却只上传了 $3$ 条路径，那么只能拼凑出 $3$ 条（暂不考虑第一类对原有需求的拼凑），贡献只有 $-3$，$2$ 号点剩下的 $10^5-3$ 条路径则毫无用处。**我们把上传上去没有办法进行第二类拼凑的这些 $10^5-3$ 条路径称做限制路径，可以拼凑的则成为自由路径**。

什么情况下会产生限制路径呢？显然是有一个儿子上传的路径数量超过总上传路径数量的一半的时候，设总上传路径数为 $\text{sum}$，最多的儿子上传 $\text{mx}$ 条，产生限制路径当且仅当 $\text{mx}>\text{sum}-\text{mx}$，即其它的子树所有路径拿来和最多的子树拼都拼不完。此时限制路径条数为 $\text{mx}-(\text{sum}-\text{mx})$，剩下的为自由路径。

接着考虑第一类拼凑，度数为 $d$ 的父亲最多拿走每个儿子的 $d-1$ 条上传路径进行第一类拼凑，显然拿儿子限制路径肯定更好，拿完了再拿自由路径。注意到只要能拿就一定会拿，因为第一类拼凑用一条路径就有 $1$ 的贡献，第二类产生相同贡献需要两倍的路径。

等父亲的需求被填满之后，儿子就可以随便进行第二类的拼凑了...吗？

还没完。我们已经知道第一类的拼凑更优了，那么我们还可以拿走儿子剩下来的更多边，传给父亲的父亲，父亲的父亲的父亲...用来完成第一类。这么说被父亲剩下来的路径也不能直接用来做第二类，还要继续保存着。

似乎感觉很难实现，实际上我们只要从下往上做，记录下层有多少个自由路径和限制路径传上来即可，随后一层一层处理，注意下层的限制路径经过上传之后可能变成自由路径（可以和父亲的父亲的...的父亲的另外一个子树的一条路径合并），递归到根之后再把剩下来的自由路径两两配对即可。正确性显然。

~~好像很对的样子为什么我考场上会这么忐忑呢~~时间复杂度 $O(\sum n)$。具体实现看代码吧。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 600000;
int T,n,u,v;
long long ans;
vector<int>e[N];
pair<ll,ll> sch(int u,int fa){//返回值 first 是 u 子树内的自由路径条数，second 是限制路径条数
	ll rd = 0,mx = 0,sum1 = 0,sum2 = 0,mxf = 0;
	//rd 记录儿子子树被用作满足 u 的需求的路径条数，sum1 记录自由路径条数，sum2 记录限制路径条数
	//mx 记录上传限制路径最多的子树，mxf 记录和 mx 来自同一子树的自由路径数量，mxf 不能和 mx 配对
	ans += 1ll * e[u].size() * (e[u].size() - 1) / 2;//u 的原始需求路径
	for(auto v : e[u]){
		if(v == fa) continue;
		auto [a,b] = sch(v,u);
		if(b < e[u].size()){//限制路径条数不足以满足 u 对 v 度数减一的需求
			if(a + b < e[u].size()) rd += a + b;//限制路径和自由路径加起来都不够，只能全部丢去满足需求了
			else{//限制路径和自由路径加起来足够满足需求，剩余部分的自由路径
				rd += e[u].size() - 1;
				sum1 += a - (e[u].size() - 1 - b);//剩下这么多自由路径
			}
		}
		else{
			sum1 += a,rd += e[u].size() - 1,sum2 += b - (e[u].size() - 1);//自由路径全部剩下，限制路径剩下一部分
			if(b - (e[u].size() - 1) > mx) mx = b - (e[u].size() - 1),mxf = a;//记录限制路径最多的子树
		}
	}
	ans -= rd;//满足需求消耗的路径条数
	sum2 += sum1 - mxf,sum1 = mxf;//把可以配对的自由路径丢到限制路径里，一起尝试与最多的限制路径配对将其转化为自由路径
	if(mx > sum2 - mx) sum1 += 2 * (sum2 - mx),sum2 -= 2 * (sum2 - mx);//还是没有办法全部消灭，只能配出 sum2-mx 对
	else sum1 += sum2,sum2 = 0;//可以全部配对，全部转化为自由路径
	return {sum1,sum2 + e[u].size() - 1};//额外有度数减一条限制路径，来自于 u 的原始需求，别忘了本来就有度数减一条上传路径
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> T;
	while(T --){
		ans = 0;
		cin >> n;
		for(int i = 1;i <= n;i ++) e[i].clear();
		for(int i = 1;i < n;i ++){
			cin >> u >> v;
			e[u].emplace_back(v),e[v].emplace_back(u);
		}
		auto [a,b] = sch(1,0);
		printf("%lld\n",ans - a / 2);//自由路径两两配对
	}
	return 0;
}
```
[招笑赛时代码](https://codeforces.com/contest/2023/submission/329015901)

---

## 作者：_LHF_ (赞：9)

首先假设所有路径长度都要是 $2$，算出一个答案，然后再减去通过连接一些路径能够减少的损失。

通过手玩可以发现。设第 $i$ 个点的度数为 $d_i$，那么相当于往每个连向的点的子树方向设 $d_i-1$ 的匹配，然后要求最大匹配。

该问题可以直接反悔贪心，具体的，记录一下当前子树内向上有多少个能够匹配单位，以及当前子树内有多少个匹配可以拆成两个向上的匹配单位。

（赛时有个地方忘记反悔了，于是 GG 了）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef long long ll;
int T,n,fa[N],f[N],g[N];
vector<int> to[N];
ll ans;
void dfs(int x)
{
	f[x]=g[x]=0;
	int s=to[x].size()-1,sum=0;
	pair<int,int> mx={0,0};
	for(int y:to[x])
		if(fa[x]!=y)
		{
			fa[y]=x,dfs(y);
			int h=f[y];
			if(h<s)
			{
				int w=min(g[y],(s+1-h)/2);
				g[y]-=w,h+=w*2;
			}
			if(h>=s)
			{
				ans-=s,h-=s;
				sum+=h;
				mx=max(mx,{h,g[y]});
			}
			else ans-=h;
			g[x]+=g[y];
		}
	if(mx.first*2>sum)
	{
		int res=g[x]-mx.second;
		g[x]-=res,sum+=res*2;
	}
	int w=min(sum/2,sum-mx.first);
	g[x]+=w,f[x]=s+sum-2*w;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1,x,y;i<n;i++)
			scanf("%d%d",&x,&y),to[x].push_back(y),to[y].push_back(x);
		for(int i=1;i<=n;i++)
		{
			ll s=to[i].size();
			ans+=s*(s-1)/2;
		}
		dfs(1);
		printf("%lld\n",ans-g[1]);
		for(int i=1;i<=n;i++) to[i].clear(),fa[i]=0;
	}
}
```

---

## 作者：Otomachi_Una_ (赞：7)

水题解/se

首先有个比较显然的贪心，以 $1$ 为根，然后自底向上每个节点计算一下会向父亲延申多少边。当一个节点延申上去的边数量不足是可以多加几条。然后在 $1$ 处进行两两匹配即可。

这玩意正确性有问题。比如 $1$ 的两个儿子一个延申 $3$ 条边另一个延申 $1$ 条就不能两两匹配了。

解决这个问题也很简单，只要定度数最大的点为根。那么返回的边数大概就是不够根节点度数的，所以都要补边。也就不会出现绝对众数的情况。

时间复杂度：$\mathcal O(n)$。

---

## 作者：ForgotMe (赞：7)

不会 1C，破防去看 1E，大战 1.5h 无果，破防*2，下大分。

神秘贪心题，赛时只想对了一半不到。

写这题题解前先安利一道思路比较类似的树上覆盖问题（P7246 手势密码），做完这两道题应该会对这类问题有一定启发？

如何设计一个合理的贪心策略？首先第一个思路肯定是从下往上解决问题，肯定设 $h_u$ 表示使子树 $u$ 中的所有边二元组（注意，需要包括 $u$ 与 $u$ 的父亲这条边）全部被覆盖的最小路径条数。 

不如设现在考虑到了点 $u$，已经求出了其儿子的 $h_{v_1},h_{v_2},...,h_{v_k}$。如何求出 $h_u$？从最简单的情况开始想，首先 $(u,v_1),(u,v_2),...,(u,v_k),(u,fa_u)$ 这些边之间组成的边二元组（称这些边之间组成的边二元组为新的边二元组）是一定要被满足的。满足一个边二元组 $(u,v_i),(u,v_j)$ 有两种方式：

- 新开一个路径。
- 从 $v_i$ 子树中拿出一条向上的路径延长一步与从 $v_j$ 子树中拿出一条向上的路径延长一步拼起来。

自然的，一个新的定义出现了：设 $f_u$ 表示在让 $h_u$ 最小的情况下，最多能拿出多少条向上的路径去帮助其父亲 $fa_u$。

继续考虑如何计算 $h_u$，可以知道的是，首先对于其任意一个儿子 $v$，至少要拿出 $k$ 条路径出来以满足新的边二元组。如果 $f_v\le k$，那就新开 $k-f_v$ 条路径，然后进行合并满足新的边二元组。在这个过程中，$f_u$ 至少会获得 $k$ 条向上的路径，因为要满足 $(u,v_1),(u,fa_u)$，...，$(u,v_k),(u,fa_u)$ 这 $k$ 个新的边二元组，然后对于一个儿子 $v$，如果 $f_v>k$，那么 $f_u$ 又可以多获得 $f_v-k$ 条路径，显然从 $v$ 向上的路径可以往上再延伸一步去帮助 $fa_u$。

这个算法看上去很对，实际上，这是错误的！！！

举个例子，对于一个 $u$ 的两个儿子 $v_i,v_j$，完全可以分别拿出一条向上的路径在 $u$ 处合并，**让使用的路径数量减少 $1$**。这样为什么可以让答案更优呢？因为可能向上帮助的路径不需要那么多。

如何修正这个想法呢？不如考虑先让所有向上的路径在 $u$ 处合并，**需要用的时候再拆开**，这显然是合法的。可以认为这里使用了一个反悔贪心的思想。

可能看到这里你已经晕了。重新书写一下所有的定义：

设 $h_u$ 表示使子树 $u$ 中的所有边二元组（注意，需要包括 $u$ 与 $u$ 的父亲这条边）全部被覆盖的最小路径条数。设 $f_u$ 表示在让 $h_u$ 最小的情况下，**路径合并后**拿出多少条向上的路径（也就是合并不了剩下的路径）去帮助其父亲 $fa_u$。设 $g_u$ 表示在让 $h_u$ 最小的情况下，子树 $u$ 中最多合并出了多少条路径。

考虑如何进行转移，同样地，先考虑解决新的边二元组的问题。

如果 $f_v\le k$，应考虑从 $g_v$ 中把一条路径拆成 $2$ 条路径，如果这样子拆完都不够（$f_v+2g_v\le k$），那就只有新开路径了。（这里有一个需要注意的点，如果 $f_v$ 与 $k$ 奇偶性不同，会出现拆完路径后多出一条空余的路径，而这条空余的路径是可以继续向上延伸的！）

在满足新的边二元组后，同样的，有初值 $f_u=k,g_u=0$，设 $f^{'}_v$，$g^{'}_v$ 分别表示在 $v$ 的子树中还剩下多少条向上延伸的路径，$v$ 的子树中还剩下多少条未拆的路径。

显然的，我们的目的是要对这些路径进行拆分重组，使尽量多的路径结合在一起，即让 $g_u$ 最大。

这个问题比较麻烦，因为可以将 $g^{'}_v$ 的路径进行拆分与其他儿子子树中的路径进行配对。

先考虑一个弱化的问题，现在有 $n$ 个数，$a_1,a_2,a_3,...a_n$，每次可以选择两个非零的数同时减去 $1$，问最大操作次数。

结论是：

先假设 $a_1\le a_2\le ...\le a_n$。

- 若 $a_n\ge \sum_{i=1}^{n-1}a_i$，那么最大操作次数是 $\sum_{i=1}^{n-1}a_i$。

- 若 $a_n< \sum_{i=1}^{n-1}a_i$，那么最大操作次数是 $\lfloor \frac{\sum a_i}{2}\rfloor$。

证明其实非常简单，首先第一种情况是显然的，主要证第二种情况，设 $t=\lfloor \frac{\sum a_i}{2}\rfloor$，考虑一个 $t\times 2$ 的矩阵，每一行描述了操作的两个位置，于是只需要按列竖着填就行了，显然这样子填数不会造成一行操作的是两个同样的位置。

这个问题跟本题有什么关系呢？如果所有的 $g^{'}_v$ 都是 $0$，上述问题的操作就相当于路径配对。但是有一个非常烦人的 $g^{'}_v$，怎么处理呢？

不如先形式化一下问题，现在有 $k$ 个二元组 $(f^{'}_i,g^{'}_i)$，对于每一个二元组，可以让 $g^{'}_i\leftarrow g^{'}_i-1，f^{'}_i\leftarrow f^{'}_i+2$，这样的操作可以选择任意次（在保证 $g^{'}_i>0$ 的情况下才能操作）。然后要让最后所有 $f^{'}_i$ 作为上面问题的输入生成的答案加上 $\sum g^{'}_i$ 的和最大。

这看似是一个非常复杂的问题，因为**不清楚**每个二元组中的 $g^{'}_i$ 到底拆多少出来才能更优秀。

不如先对二元组进行一个排序，下面假设 $f^{'}_1\le f^{'}_2\le ... \le f^{'}_k$。

- 先考虑一种简单的情况，若 $f^{'}_k\ge \sum_{i=1}^{k-1} f^{'}_i + 2g^{'}_i$，那么显然最大的操作次数就是 $\sum_{i=1}^{k-1} f^{'}_i + 2g^{'}_i$，也就是 $g_u=(\sum_{i=1}^{k-1} f^{'}_i + 2g^{'}_i)+g^{'}_k$，$f_u=k+f^{'}_k-(\sum_{i=1}^{k-1} f^{'}_i + 2g^{'}_i)$。

若 $f^{'}_k< \sum_{i=1}^{k-1} f^{'}_i + 2g^{'}_i$，这个时候情况比较复杂。如果要说的清楚需要分类讨论。

- 若 $f^{'}_k< \sum_{i=1}^{k-1} f^{'}_i$，这个时候比较简单，不需要进行路径拆分，$g_u=\lfloor\frac{\sum_{i=1}^k f^{'}_i}{2}\rfloor+\sum_{i=1}^k g^{'}_i$，$f_u=k+((\sum_{i=1}^k f^{'}_i)\bmod 2)$。

- 若 $f^{'}_k\ge \sum_{i=1}^{k-1} f^{'}_i$，这个时候需要进行路径拆分，由于保证了拆完路径后一定可以 $> f_k$，那么拆哪个子树的路径本质上是不重要的，甚至拆多少都是不重要的，只要满足拆完后和 $>f^{'}_k$，因为拆路径不会导致 $\sum_{i=1}^{k-1} f^{'}_i$ 的奇偶性发生改变！于是同样可以推出 $g_u=\lfloor\frac{\sum_{i=1}^k f^{'}_i}{2}\rfloor+\sum_{i=1}^k g^{'}_i$，$f_u=k+((\sum_{i=1}^k f^{'}_i)\bmod 2)$。可以看出，**这与上一种情况本质上是一样的**。

那么至此就可以以 $\mathcal{O}{(n)}$ 复杂度算出 $f,g$，在实现时，并不需要去维护这个 $h$，实时计算答案就可以了。

放个代码，由于作者写这题处于红温状态，图方便用了排序，复杂度带了 log，仅供参考。

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<LL,LL>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
//	Invn[0]=Invn[1]=1;
//	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,rt;
LL res,f[500005],g[500005];//f:up g:bouns 
vector<int>G[500005];
vector<pp>buc[500005],Q[500005];
inline bool cmp(pp A,pp B){
	return A.first<B.first; 
}
inline void dfs(int u,int ff){
	int son=0;
	for(auto v:G[u]){
		if(v==ff)continue;
		son++;
		dfs(v,u);
		buc[u].push_back(pp(f[v],g[v]));
	}
	if(!son)return ;
	res-=1ll*son*(son-1)/2;
	if(u==rt)son--;
	for(auto x:buc[u]){
		LL v1=x.first,v2=x.second;
		if(v1<=son){
			LL need=son-v1;
			if(2*v2>=need){
				if(need&1){
					v2-=(need+1)/2;
					res+=(need+1)/2;
					//up-->1 bouns--> v2
					Q[u].push_back(pp(1,v2));
				}else{
					v2-=need/2;
					res+=need/2;
					//up-->0 bouns--> v2
					Q[u].push_back(pp(0,v2));
				} 
			}else{
				//0 0 
				res+=v2; 
				res+=son-v1-v2*2;
			}
		}else{
			v1-=son;
			Q[u].push_back(pp(v1,v2));
		}
	}
	f[u]=son;g[u]=0;
	sort(Q[u].begin(),Q[u].end(),cmp);
	if(Q[u].size()){
		LL mx=0,sum=0;
		for(auto x:Q[u])mx=max(mx,x.first);
		LL sum2=0;
		for(int i=0;i<Q[u].size()-1;i++){
			pp x=Q[u][i];
			res+=x.second;
			sum2+=x.first+2*x.second;
		}
		if(sum2>=mx){
			f[u]+=(sum2+mx)%2;
			res-=(sum2+mx)/2;
				g[u]+=(sum2+mx)/2+Q[u][Q[u].size()-1].second;
		}else{
			f[u]+=mx-sum2;
			res-=sum2;
			g[u]+=sum2+Q[u][Q[u].size()-1].second;
		}
	}
}
inline void solve(){
	gi(n);
	for(int i=1;i<=n;i++)G[i].clear(),buc[i].clear(),Q[i].clear(),f[i]=g[i]=0;
	for(int i=1;i<n;i++){
		int u,v;
		gi(u),gi(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	rt=0;
	for(int i=1;i<=n;i++)if(G[i].size()==1)rt=i;
	res=0;dfs(rt,0);
	pi(res);
}
signed main(){
	srand(time(0));
	gi(t);
	while(t--)solve();
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/CF2023E)

**题目大意**

> 给定 $n$ 棵点的树，选出最少的简单路径，使得每对相邻的边都至少在一条路径中相邻出现过。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

先选出所有长度为 $2$ 的路径，然后可以合并端点相同的一些。

对于每个子树 $u$，我们求出子树内的结果后，应该在保证子树内答案不变的情况下，向上的路径尽可能多，记为 $f_u$。

那么我们的思路就是，对于 $u$ 的每个儿子 $v$，我们可以把 $\min(f_v,\mathrm{deg}_u-1)$ 过 $v\to u$ 的路径合并起来。

如果 $f_v>\mathrm{deg}_u-1$，那么剩余的所有路径提出来，传递到 $f_u$ 中即可。

但是此时我们发现这个做法不一定最优，因为当我们处理完 $f_1$ 后，多余的路径全部浪费了，因此对于有一些路径，在 $u$ 处合并可能更优。

但我们无法在 $u$ 处确定祖先需要多少条链，因此我们先在 $u$ 处合并，然后在祖先的有需要的时候拆开若干条，使得 $f_v\ge \mathrm{deg}_u-1$。

很显然在 $u$ 处合并后，还能随意在祖先处拆开，因此我们只要最大化子树中这样合并的路径个数 $g_u$。

我们已经知道每个子树还有多少条剩余的路径，只要两两匹配即可，当且仅当这些路径数不存在绝对众数时有解。

但如果存在绝对众数，我们依然可以通过拆掉其他子树内的 $g_v$，获得新的两条路径，和绝对众数匹配，那么求出其他子树的 $g_v$ 之和，拆掉最少的链，使得绝对众数不存在即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e5+5;
vector <int> G[MAXN];
ll f[MAXN],g[MAXN],ans;
void dfs(int u,int fz) {
	int s=G[u].size()-1;
	ans+=1ll*s*(s+1)/2;
	array <ll,2> mx={0,0};
	ll p=0;
	for(int v:G[u]) if(v^fz) {
		dfs(v,u);
		if(f[v]<s) {
			ll z=min(g[v],(s-f[v]+1)/2);
			g[v]-=z,f[v]+=2*z;
		}
		if(f[v]>s) {
			ans-=s,f[v]-=s,p+=f[v];
			mx=max(mx,{f[v],g[v]});
		} else ans-=f[v];
		g[u]+=g[v];
	}
	if(p<mx[0]*2) {
		ll z=min(g[u]-mx[1],(mx[0]*2-p+1)/2);
		g[u]-=z,p+=2*z;
	}
	ll z=min(p/2,p-mx[0]);
	f[u]=s+p-2*z,g[u]+=z;
}
void solve() {
	int n;
	scanf("%d",&n),ans=0;
	for(int i=1;i<=n;++i) f[i]=g[i]=0,G[i].clear();
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	dfs(1,0),ans-=g[1],printf("%lld\n",ans);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Acoipp (赞：1)

比赛之后写了一会，发现没有想象中那么难，不过代码调了很久就对了。

考虑直接设 $h_i$ 表示 $i$ 子树内的答案，容易发现只有没有拐点的路径比较重要，考虑设 $g_i$ 表示 $i$ 子树内从 $i$ 开始的路径有 $g_i$ 条（前提是 $i$ 子树内答案最小）。

考虑合并若干棵子树，设我们正在处理 $u$ 节点的答案，那么要保证：

- $u$ 的任意两个儿子之间的两条边同时被某条路径覆盖。
- 如果 $u$ 有父亲，那么 $u$ 的儿子到父亲的两条边同时被某条路径覆盖。

我们发现，从 $u$ 儿子上来的路径条数一定大于等于 $u$ 的度数才有解，于是我们先对不足这个值的补足。然后强制令每两个儿子之间的两条边都被某条路径覆盖即可。

最后需要优化的就是可以通过合并两条路径减少路径条数，于是问题就很经典了，给定 $a_1,a_2,\dots,a_n$，每次可以选择 $a_i,a_j$ 令 $a_i \gets a_i-1,a_j \gets a_j-1$，你需要保证所有数任何时刻都是非负整数，问最多操作的次数。

于是按照这个思路完成即可。

但是你发现这个方法有个小问题，就是如果一棵小子树内合并了两条路径，但是事实上在遍历到祖先的时候把这两条路径拆开再和其他路径拼起来更优，所以再记 $f_i$ 表示 $i$ 子树内合并的路径条数即可。

$f_i$ 可以作用的地方在：

- 对不足 $u$ 度数的儿子向上延申的链补足的时候 $f_i$ 可以拆开一个。
- 最后执行上述小贪心算法的时候，可以对一些 $a_i$ 补一些 $2$，会使答案变小。

大概运用上述整个贪心就是对的了，证明的话可以分类讨论（反证有点困难），此处略。

时空复杂度均为 $O(n)$。

---

