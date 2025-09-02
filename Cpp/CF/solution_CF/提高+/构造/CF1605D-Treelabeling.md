# Treelabeling

## 题目描述

Eikooc and Sushi play a game.

The game is played on a tree having $ n $ nodes numbered $ 1 $ to $ n $ . Recall that a tree having $ n $ nodes is an undirected, connected graph with $ n-1 $ edges.

They take turns alternately moving a token on the tree. Eikooc makes the first move, placing the token on any node of her choice. Sushi makes the next move, followed by Eikooc, followed by Sushi, and so on. In each turn after the first, a player must move the token to a node $ u $ such that

- $ u $ is adjacent to the node $ v $ the token is currently on
- $ u $ has not been visited before
- $ u \oplus v \leq min(u, v) $

Here $ x \oplus y $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation on integers $ x $ and $ y $ .

Both the players play optimally. The player who is unable to make a move loses.

The following are examples which demonstrate the rules of the game.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1605D/2753cf0e782e13d9057daab27daee25743dde933.png) Suppose Eikooc starts the game by placing the token at node $ 4 $ . Sushi then moves the token to node $ 6 $ , which is unvisited and adjacent to $ 4 $ . It also holds that $ 6 \oplus 4 = 2 \leq min(6, 4) $ . In the next turn, Eikooc moves the token to node $ 5 $ , which is unvisited and adjacent to $ 6 $ . It holds that $ 5 \oplus 6 = 3 \leq min(5, 6) $ . Sushi has no more moves to play, so she loses. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1605D/ac5a33a157c1092415c37820799d7642326e181c.png) Suppose Eikooc starts the game by placing the token at node $ 3 $ . Sushi moves the token to node $ 2 $ , which is unvisited and adjacent to $ 3 $ . It also holds that $ 3 \oplus 2 = 1 \leq min(3, 2) $ . Eikooc cannot move the token to node $ 6 $ since $ 6 \oplus 2 = 4 \nleq min(6, 2) $ . Since Eikooc has no moves to play, she loses.Before the game begins, Eikooc decides to sneakily relabel the nodes of the tree in her favour. Formally, a relabeling is a permutation $ p $ of length $ n $ (sequence of $ n $ integers wherein each integer from $ 1 $ to $ n $ occurs exactly once) where $ p_i $ denotes the new numbering of node $ i $ .

She wants to maximize the number of nodes she can choose in the first turn which will guarantee her a win. Help Eikooc find any relabeling which will help her do so.

## 说明/提示

In the first test case, Eikooc has only one choice. Sushi will have no moves to play after Eikooc chooses this node and Eikooc will win.

In the second test case, $ 1 \oplus 2 = 3 \nleq min(1, 2) $ . Hence, after Eikooc picks either of the nodes, Sushi will have no moves to play and Eikooc will win. Both $ \{1, 2\} $ and $ \{2, 1\} $ are optimal relabelings.

## 样例 #1

### 输入

```
3
1
2
1 2
3
1 2
1 3```

### 输出

```
1
2 1
1 2 3```

# 题解

## 作者：int1 (赞：7)

一句话题解：在某个连通块内操作当且仅当连通块内节点编号最高位 $1$ 位置相同，因此可以证明存在让每个点都一旦在这里放下，都无法移动的构造方案，对树黑白染色，编号二进制分组构造即可。

----

题目给的三个限制条件，前两个都是好理解的，只有第三个相对隐蔽一点，需要我们仔细发掘一下。

**引理：能够在两个相邻节点中发生移动，当且仅当两个节点编号最高位 $1$ 的位置相同。**

证明：前半句显然，后半句当 $u$ 和 $v$ 的节点编号最高位 $1$ 位置相同时，$u \oplus v$ 的这一位上不是 $1$，因此一定满足 $u \oplus v \le \min\{u, v\}$，并且只有这种情况满足条件，因为如果不同，$u \oplus v$ 结果的最高位就会由两数中较大的那一个确定，这时较小的在那一位上没有 $1$。

这样，根据引理 1，问题就转化为了将树划分为若干个连通块，可以在这些连通块内操作，最大化必胜态点数。

但是，单纯连通块的性质的话做这个貌似还是比较困难，其实有更强的性质，我们注意到原图是一棵树。

**事实 1：$2^{k - 1} - 1 > \lfloor\dfrac{2^k - 1}{2}\rfloor$，$k$ 为任意正整数。**

**推论：在二分图上本题模型存在每个点都无法再移动的构造方案。**

证明：将二分图黑白染色，设二分图总点数为 $n$，$k$ 为满足 $n < 2^x$ 的最小的 $x$，即 $n$ 的二进制最高位 $1$ 位置，则黑点和白点中数目较小的一个一定不大于 $\lfloor\dfrac{2^k - 1}{2}\rfloor$，而 $1 \sim n$ 中二进制最高位低于 $k$ 的数有恰好 $2^{k - 1} - 1$，我们知道一个数存在唯一的二进制表示，因此一定能用这些数把较小的这一种点的个数表示出来。

**事实 2：树是二分图，** 黑白染色法易证。

由推论和事实 2 即得题解开头所述解法的正确性。

---

## 作者：JCLinux (赞：6)

## 题目大意：

E 和 S 在玩博弈游戏， E 先手 S 后手。

给一个 $n$ 个节点的树，节点的值包含 $[1,n]$ 中的每一个值。

E 先随便选择一个点，占领它（点  u ）， S 只能选择与这个点相邻的，没有被占领的点（点 v ）且这两个点满足 $u⊕v≤\min(u,v)$

$⊕$ 是异或操作

现在把树给 E 了， E 想要重新排列节点的值（树的形状不变，只是调换结点的值）来达到这个目的：

最大化第一轮能够选择的点的数量，在选了这个点之后，E 必赢。

赢：对手无路可走，你就算赢

## 思路：

E 和 S 交替进行，怎么感觉有点像二分图呢，我就是用的二分图来做的，但这个题仅仅用二分图还不够，还需要发现异或操作的一个性质，从而进行构造。

为了让对手无路可走，要么是~~真正意义上的~~无路可走（你把叶节点占领了），要么是对手无法满足 $ u⊕v≤ \min(u,v)$ 

后者就是解题的关键

先不必管第一种，这个题是构造，只要你能构造出来最大情况，有些东西是不必考虑的。

#### 现在让我们看看神奇的异或操作

当两个数（u,v）的二进制最高位数相等时，它俩的异或结果**一定比  $\min(u,v)$ 小**

因为最高位在异或之后变成了 0

相反，如果两个数的二进制最高位不相等，异或结果永远比最小的那个大，因为最高位的二进制位被保留。

我们就可以把 $[1,n] $ 的整数按照最高位进行划分了。

（1） ; （2,3） ; （4,5,6,7） ; （8,9,10,11,12,13,14,15） ; ……

不同的划分块之间不通（不满足约束条件）

树我们用bfs把它变成二分图，任意一边的节点数量小于等于 $n/2$ ，我们可以用划分块来填充二分图的两边，而划分块的大小刚好是2的整数次方，岂不美哉。

举个例子：假设 $n=7$ ,二分图左边大小是 3 ，右边大小是 4 ，我们先填充 3  这边

3 的二进制是 11 ，所以我们选择第一个划分块和第二个划分块（划分块的大小和二进制权重是相对应的，所以划分块里面的元素刚刚好被用完）来填充二分图的左边，剩下的自然就填充到右边。

此时你会发现，你无论选择哪个点，对手死路一条。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
vector<int>edge[200005];
bool vis[200005];
int ans[200005];
vector<int>Left,Right;//二部图
void bfs(int i,int depth)//奇数在左边，偶数在右边
{
    vis[i]=1;
    if(depth&1) Left.push_back(i);
    else Right.push_back(i);
    for(int j=0; j<(int)edge[i].size(); j++)
    {
        if(!vis[ edge[i][j] ])
        {
            bfs(edge[i][j],depth+1);
        }
    }
}
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i=1; i<=n; i++) edge[i].clear();
        Left.clear();
        Right.clear();
        memset(vis,0,n+2);
        for(int i=1; i<n; i++)
        {
            int u,v;
            cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        bfs(1,1);
        memset(vis,0,n+2);
        int s=Left.size();
        int S=Right.size();
        int base=1;
        if(s<S)
        {
            while(s)
            {
                if(s&1)
                {
                    for(int i= (1 << (base-1)); i<= (1 << base) -1; i++)
                    {
                        ans[Left.back()]=i;
                        Left.pop_back();
                        vis[i]=1;
                    }
                }
                base ++;
                s >>= 1;
            }
            for(int i=1; i<=n; i++)
            {
                if(!vis[i])
                {
                    ans[Right.back()]=i;
                    Right.pop_back();
                }
            }
        }
        else
        {
            while(S)
            {
                if(S&1)
                {
                    for(int i= (1 << (base-1)); i<= (1 << base) -1; i++)
                    {
                        ans[Right.back()]=i;
                        Right.pop_back();
                        vis[i]=1;
                    }
                }
                base ++;
                S >>= 1;
            }
            for(int i=1; i<=n; i++)
            {
                if(!vis[i])
                {
                    ans[Left.back()]=i;
                    Left.pop_back();
                }
            }
        }
        for(int i=1; i<=n; i++) cout << ans[i] << " " ;
        cout << endl;
    }
    return 0;
}
```


---

## 作者：Frevotops (赞：5)

## 1605D [constructive] [bitmasks] [tree]

好题！鼓掌！

这道题我要根据我思考的过程，分四部分讲。

#### 1. 不等式 $u \oplus v \le \min(u,v)$ 也太丑了吧

我们不妨设 $u \le v$，则当 $u$ 和 $v$ 的二进制最高位相同时，这一位异或起来是 $0$，等式恒成立。

不同时，则 $v$ 的最高位对应 $u$ 中是 $0$，$1 \oplus 0 = 1$，容易发现 $u \oplus v > u$，等式恒不成立。

分析完这个性质，我们就可以发现：第一个人选择哪里开始，决定了本局游戏中经过的所有数的最高位。

#### 2. 答案可能是怎样的

我们猜测答案可能是怎样的。

如果答案不是很特别，那么只能 dp 去做，而且这是让你分配一个排列，这就很不可做了。

会不会一定有方案，使得不论选择哪个点，先手必胜？不如往这个方向考虑。

#### 3. 答案又可能是怎样的

即使要让每个点都先手必胜，也难从下手。不如再猜性质：存在方案使得每个点都走不出去！也就是周围的点最高位都不同。

只要找到一个分配方法就行了。

我们已经很接近答案了。

#### 4. 猜了这么多，你构造啊

这就是难点，我想了很久。

我们知道树一定是二分图，因为没有环。额，可是我们的问题不是二分图啊……是否可以**根据最高位分类，将一些数看做黑色，一些数看做白色，最高位相同的两个数一定是同种颜色**？分类完，剩下的就是二分图染色了啊。

我们发现，最高位数为 $1$ 的数有 $1$ 个，为 $2$ 的数有 $2$ 个，为 $x$ 的数有 $2^{x-1} $ 个（最后由于 $n$ 的限制，我们假设剩下了 $p$ 个数）。假设二分图染色后黑色节点的个数是 $k$，我们要用 $\{1,2,4,8,16,...,2^x,p\}$ 凑出 $k$……

相信能看懂到这里的你一定大呼：这不就是二进制吗？显然是一定可以凑出来的，对应着一定能分类，对应着我们的猜测是成功的。

--------------

很多人会问：为什么要作出这样的猜测？很大部分是因为我们如果不去猜性质，这题就无从下手。猜测背后，需要我们的不断模拟样例，以及一点点小自信。

『大胆猜想，小心求证。』

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,u,v,ans[200005]; vector<ll>E[200005],a,b,s1,s2;
bool vis[200005];
void dfs(ll x,ll w,ll fa){
	if(w) a.push_back(x);
	else b.push_back(x);
	for(auto y: E[x]){
		if(y==fa) continue;
		dfs(y,w^1,x);
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n; a.clear(); b.clear(); s1.clear(); s2.clear();
		for(ll i=1;i<=n;i++) E[i].clear(), vis[i]=0;
		for(ll i=1;i<n;i++){
			cin>>u>>v;
			E[u].push_back(v); E[v].push_back(u);
		}
		dfs(1,0,0);
		ll now=a.size(), t=1;
		while(t*2<=n) t*=2;
		if(now>=t){
			for(ll i=t;i<=n;i++) s1.push_back(i), vis[i]=1;
			now-=(n-t+1);
		}
		for(ll i=0;i<=20;i++){
			if(now&(1ll<<i)){
				for(ll j=(1ll<<i);j<(1ll<<(i+1));j++) s1.push_back(j), vis[j]=1;
			}
		}
		for(ll i=1;i<=n;i++)
			if(!vis[i]) s2.push_back(i);
		ll sz=a.size();
		for(ll i=0;i<sz;i++){
			ans[a[i]]=s1[i];
		}
		sz=b.size();
		for(ll i=0;i<sz;i++){
			ans[b[i]]=s2[i];
		}
		for(ll i=1;i<=n;i++) cout<<ans[i]<<" "; cout<<endl;
	}	
	return 0;
}
```


---

## 作者：Priestess_SLG (赞：0)

$u\oplus v\le\min(u,v)$ 十分的别扭，于是考虑转换条件。令 $l$ 表示 $u,v$ 二进制最高的 $1$ 位的最大值，则显然若 $u,v$ 在第 $l$ 位上的值相同，则等式成立，否则等式不成立。

因此可以发现，若 $\exist i,s.t.u,v\in[2^i,2^{i+1})$，则 $u,v$ 两个点满足条件，否则不满足条件。因此给 $[2^i,2^{i+1})$ 段内所有元素定义为 $i$ 色。

因为树是二分图，所以考虑给树黑白染色，要求树上相邻两个结点的色必须不同。这是容易构造的，二进制拆分一下即可。于是做完了。

[代码](https://codeforces.com/contest/1605/submission/301725402)。

---

## 作者：shucai (赞：0)

## 1605D

首先思考虑么样的情况能走，什么情况不能走。

以下若 $x$ 与 $y$ 二进制下最高位相同，则称它们同阶。

注意到若 $x$ 与 $y$ 同阶，那么异或后最高为会变成 $0$，一定会小于他们之间较小者；若 $x$ 与 $y$ 不同阶，那么异或后得到的新数最高位为 $x$ 与 $y$ 较大者的最高位，一定大于他们之间较小者。

那么对于书上的一个结点 $u$，若 $u$ 的儿子以及父亲都与 $u$ 不同阶，那么 $u$ 就是一个必胜点。那么我们把这颗树视为二分图形态，对其染色，一边黑色，一边白色，那么我们要做的就是让黑点与白点不同阶对数数量尽可能多。

现在可看做有一些数 $ \left \{  2^0,2^1,2^2{}\dots {}\dots 2^k,n-2^k|2^k \le n\right \} $ 要将他们插入两个集合中。我们发现这就是二进制拆分，一定能实现。故我们设黑点数量为 $p$，对其进行二进制拆分，把位上的点放进黑点集合，剩下放进白点集合，那么这样无论哪个点为将成为必胜点。

---

