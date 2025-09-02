# [ARC124D] Yet Another Sorting Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc124/tasks/arc124_d

$ (1,2\ \ldots,\ N+M) $ を並べ替えて得られる長さ $ N+M $ の数列 $ p $ が与えられます。 $ p $ の $ i $ 番目の数は $ p_i $ です。

あなたは以下の **操作** を何回でも行うことができます。

操作：$ 1 $ 以上 $ N $ 以下の整数 $ n $ と $ 1 $ 以上 $ M $ 以下の整数 $ m $ を選び、$ p_{n} $ と $ p_{N+m} $ を交換する

$ p $ を昇順に並べ替えるために必要な最小の操作回数を求めてください。この問題の制約下で $ p $ を昇順に並べ替えることができることが証明できます。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N,M\ \leq\ 10^5 $
- $ 1\ \leq\ p_i\ \leq\ N+M $
- $ p $ は $ (1,2\ \ldots,\ N+M) $ を並べ替えて得られる

## 样例 #1

### 输入

```
2 3
1 4 2 5 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5 7
9 7 12 6 1 11 2 10 3 8 4 5```

### 输出

```
10```

# 题解

## 作者：Tx_Lcy (赞：7)

本篇题解是对 @Missa 大佬题解的一些浅显易懂的解读与补充。

我们定义前 $n$ 个点为白点，后 $m$ 个点为黑点。

首先要对这些点连边，我们从 $i$ 向 $p_i$ 连一条边，那么我们最终的要求就是整个图所有点都变成孤立点。

画一画图，发现，我们对两个数 $x,y$ 进行操作等价于交换 $x$ 和 $y$ 连向的那个点，再画一画图，发现一个规律：若 $x,y$ 当前不在一个环内，则 $x$ 和 $y$ 被并到了一个环中，否则原来的环在 $x,y$ 两个点被断开，分裂成两个独立的弧。

如果两个异色点 $x$ 与 $y$，且 $p_x=y$，则我们操作 $x,y$，可以使 $p_x=p_y,p_y=p_x=y$，发现 $y$ 变成了一个孤立点，我们成功把 $y$ 分裂出来了。如果此环是非纯色的，则我们一定能找到两个点 $x,y$ 满足以上条件。每次减少一个颜色多于另一色的颜色，就能保证可以把所有点分开。

那么，只要把所有纯色环合并，就能通过 $n+m-cnt$ 次操作分开所有点，其中 $cnt$ 表示环的数量。

贪心地想，环数越多越好。同时，把一对纯异色环合并起来，一次操作能减少两个纯色环，也是很贪心的选择。

剩下的部分参见 [Missa 大佬的博客](https://www.luogu.com.cn/blog/purplevine/solution-arc124d)，我认为他讲的很清楚了。

---

## 作者：Missa (赞：2)

题意：给定长度为 $n+m$ 的排列 $p$，其中 $1-n$ 位置为白色，$n+1-n+m$ 位置为黑色，每次交换一个白色位置与一个黑色位置的数，求把 $p$ 变成升序的最少操作次数。

[link to atcoder](https://atcoder.jp/contests/arc124/tasks/arc124_d) | [link to Luogu](https://www.luogu.com.cn/problem/AT_arc124_d)

看到排列，首先想建图。看到变成升序，想到了 thupc2022 那道造计算机，不过那题钦定了 $m=2$。

连边 $i \to p_i$，则一次操作交换两个异色点的指向。容易发现如果二者不在一个环中，则合并至一个环；否则，原环分裂成两个。容易发现总可以把一个环上连续一段“弧”分裂出来，要求两端弧的左端点异色。

如果 $x$ 指向异色点 $y$，对 $x,y$ 做一次操作，$y$ 就会脱离环。非纯色环一定能找到这样的点，每次减少一个颜色多于另一色的颜色，就能保证可以把所有点分开。

那么，只要把所有纯色环合并，就能通过 $n+m-cnt_{\text{环数}}$ 次操作分开所有点。

让环数多一些是好的；同时，把一对纯异色环合并起来，一次操作能减少两个纯色环，也是很贪心的选择。

设原来有 $k$ 个连通块，$a$ 个大小超过 $1$ 的纯白环，$b$ 个大小超过 $1$ 的纯黑环，则开始的合并耗费 $\max\{a,b\}$ 次操作，剩余 $k-\max\{a,b\}$ 个环，最后一步操作 $n+m-(k - \min\{a,b\})$ 次，总共 $n+m-k+2\max\{a,b\}$ 次操作。

还有一些一遍合并一遍分裂的可能最优解，这些等效到先合并再分裂，而由上面的构造能看出这是先合并再分裂时的最优解。

官方题解证明了进行 $i$ 次操作后 $f(i) = i + n + m - k_i + 2 \max\{a_i,b_i\} \geq f(i-1)$，带下标的数字意为操作 $i$ 次后的值。

感觉“先合并再分裂”这里还是比较自然的，最大化连通块的想法也属自然，但是对最优解的证明略繁琐。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int M = 3e5 + 5;
int n, m, p[M], k, a, b; bool col[M], vis[M];
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n+m; i++) scanf("%d", &p[i]);
    for(int i = 1; i <= n; i++) col[i] = 1;
    for(int i = 1; i <= n+m; i++) {
        if(vis[i]) continue;
        int j = i, len = 0, cnt = 0;
        do {
            cnt += col[j]; ++len;
            vis[j] = 1; j = p[j]; 
        } while(j != i);
        ++k;
        if(cnt == 0 && len > 1) ++a;
        else if(cnt == len && len > 1) ++b;
    }
    printf("%d\n", n + m - k + 2*max(a, b));
}
```

---

## 作者：WeWantToRun (赞：1)

设前 $n$ 个点为红色，后 $m$ 个点为蓝色。

观察样例一可以发现，一个大小为 $t$ 的非同色环一定只需要 $t-1$ 次操作即可复原，因为显然可以构造操作序列使得每次交换两个异色点。

然后考虑同色环。一个简单的大小为 $t$ 的同色环显然交换一次之后会变成一个大小为 $t+1$ 的非同色环，因此操作次数是 $t+1$ 次。但是我们可以将两个大小分别为 $x$ 和 $y$ 的异色同色环配对，就只需要进行一次第一个操作，然后形成一个大小为 $x+y$ 的同色环，因此操作次数总计是 $x+y$ 次。

所以总的考虑，非同色环和孤立点操作次数比点数少一次，配对环操作次数等于点数，未配对同色环操作次数比点数多一次，并查集维护环的颜色即可。时间复杂度 $O(n\alpha(n))$。

---

## 作者：Elairin176 (赞：1)

[Link](https://www.luogu.com.cn/problem/AT_arc124_d)   
比较套路。   
## 解法
看到排列，我们直接考虑 $i$ 向 $p_i$ 连边。   
> 注：如果我们这样建边，那么我们容易证明连出来的图由若干个孤立点和环组成。并且，环的点数和边数一致。利用这些性质可以方便地解题。

那么，一次交换操作实际上就对应着图上的两条边 $(u_1,v_1),(u_2,v_2)$ 变为 $(u_1,v_2),(u_2,v_1)$。    
我们给对应的点染上色，并记环的点数为 $size$，分为以下几种情况讨论：   
- 孤立点。这种情况无需考虑，因为已经在正确的位置上了。
- 异色环。（环上两种颜色的点均存在）这时我们易证操作次数最少为 $size-1$。（总能保留一对异色点）
- 同色环。（环上结点同色）这时如果我们直接交换那么操作次数是 $size+1$ 的。但是我们注意到，如果将一对异色的同色环同时操作，那么操作次数就变成了这两个环的 $size$ 之和。所以这时我们的策略如下：导出所有的黑白同色环，贪心地选取 $size$ 大的环合并，剩下的环直接交换。

CODE：     

```cpp
//luogu paste jo5j6ogx
cst int N=2e5;
int n,m,last[N+10],tot,p[N+10];
bool col[N+10];
struct edge{
	int u,nxt;
}a[N+10];
il void add(int u,int v){
	a[++tot].u=v;
	a[tot].nxt=last[u];
	last[u]=tot;
}
int siz[N+10],sum[N+10],cnt,ans;
vector<int>vec[2];
bool vis[N+10];
il void dfs(int u){
	if(vis[u]) ret;
	vis[u]=1;
	sum[cnt]+=col[u];siz[cnt]++;
	for(int i=last[u];i;i=a[i].nxt){
		int v=a[i].u;
		dfs(v);
	}
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();m=read<int>();
	for(int i=1;i<=n+m;i++){
		p[i]=read<int>();
		add(i,p[i]);
		col[i]=(i>n);
	}
	for(int i=1;i<=n+m;i++){
		if(vis[i]) continue;
		cnt++;dfs(i);
		if(siz[cnt]==1) continue;
		if(sum[cnt]==0) vec[0].emplace_back(siz[cnt]);
		else if(sum[cnt]==siz[cnt]) vec[1].emplace_back(siz[cnt]);
		else ans+=siz[cnt]-1;
	}
	sort(vec[0].begin(),vec[0].end(),[](cst int&x,cst int&y){ret x>y;});
	sort(vec[1].begin(),vec[1].end(),[](cst int&x,cst int&y){ret x>y;});
	int s0=vec[0].size(),s1=vec[1].size(),p0,p1;
	for(p0=0,p1=0;p0<s0&&p1<s1;p0++,p1++) ans+=vec[0][p0]+vec[1][p1];
	for(;p0<s0;p0++) ans+=vec[0][p0]+1;
	for(;p1<s1;p1++) ans+=vec[1][p1]+1;
	write(ans);
	ret 0;
}
```
[Record(Atcoder)](https://atcoder.jp/contests/arc124/submissions/62167172)

---

