# [USACO22JAN] Cereal 2 S

## 题目描述

Farmer John 的奶牛们的早餐最爱当然是麦片了！事实上，奶牛们的胃口是如此之大，每头奶牛一顿饭可以吃掉整整一箱麦片。

最近农场收到了一份快递，内有 $M$ 种不同种类的麦片（$2\le M\le 10^5$）。不幸的是，每种麦片只有一箱！$N$ 头奶牛（$1\le N\le 10^5$）中的每头都有她最爱的麦片和第二喜爱的麦片。给定一些可选的麦片，奶牛会执行如下的过程：

- 如果她最爱的麦片还在，取走并离开。

- 否则，如果她第二喜爱的麦片还在，取走并离开。

- 否则，她会失望地哞叫一声然后不带走一片麦片地离开。

当你最优地排列这些奶牛时，求饥饿的奶牛的最小数量。同时，求出任意一个可以达到此最小值的 $N$ 头奶牛的排列。


## 说明/提示

【样例解释】

在这个例子中，有 $8$ 头奶牛和 $10$ 种麦片。

注意我们对前三头奶牛独立于后五头奶牛求解，因为她们没有共同喜欢的麦片。

如果前三头奶牛按顺序 $[1,2,3]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $2$ 会选择麦片 $3$，奶牛 $3$ 会饥饿。

如果前三头奶牛按顺序 $[1,3,2]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $3$ 会选择麦片 $3$，奶牛 $2$ 会选择麦片 $4$；没有奶牛会饥饿。

当然，还存在其他排列使得前三头奶牛均不饥饿。例如，如果前三头奶牛按顺序 $[3,1,2]$ 选择，则奶牛 $3$ 会选择麦片 $2$，奶牛 $1$ 会选择麦片 $1$，奶牛 $2$ 会选择麦片 $3$；同样，奶牛 $[1,2,3]$ 均不会饥饿。

可以证明在后五头奶牛中，至少一头会饥饿。

【数据范围】

- $14$ 个测试点中的 $4$ 个测试点满足 $N,M\le 100$。

- $14$ 个测试点中的 $10$ 个测试点没有额外限制。

【说明】

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/hi36jkwh)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或[发帖](https://www.luogu.com.cn/discuss/lists?forumname=P8095)。

## 样例 #1

### 输入

```
8 10
2 1
3 4
2 3
6 5
7 8
6 7
7 5
5 8```

### 输出

```
1
1
3
2
8
4
6
5
7```

# 题解

## 作者：TianyiLemon (赞：20)

有趣的题。

碰到这种二元关系的题，我们通常可以考虑从图论的角度去思考。

具体地说，我们把麦片当作点，把奶牛当作边。

我一开始考虑把奶牛当作有向边，从第一喜欢的麦片指向第二喜欢的麦片，但是有向图没有什么好的性质。

所以我们不妨把奶牛看作无向边，再考虑它是否满足题目条件。

---
考虑每个连通块，设连通块内能够吃到麦片的奶牛数为 $cnt$，连通块点数为 $n$，边数为 $m$。

显然 $cnt\le \min(n,m)$。

通过手玩几组数据，我们不妨大胆猜想 $cnt= \min(n,m)$。

具体地说，如果 $m=n-1$，即连通块是一棵树，则 $cnt=n-1$；否则 $cnt=n$。

接下来我们考虑如何构造。

1. $m=n-1$：

   从连通块内任意一个节点开始 bfs/dfs，按照 bfs/dfs 顺序输出边即可。

   **正确性说明：**

   设一条边为 $(u,v)$，其中 $u$ 是 $v$ 在树上的祖先。

   在访问到这条边的时候，$v$ 一定没有被选择，$u$ 可能被选可能不被选。

	所以不论这条边的指向如何，它都一定能够被满足。

	所以恰好有 $m=n-1$ 条边被满足，方案是正确的。


	

2. $m\ge n$：

	我们考虑建出连通块的一棵搜索树，这时候我们还要使得连通块内的一条后向边（即不在搜索树上的边）被满足。

	所以我们不妨先输出一条后向边，设这时被选择的点（即第一喜欢的麦片）为 $s$。

	以 $s$ 为根对搜索树进行 bfs/dfs，按照顺序输出树上的边。

	最后再输出不能被满足的边即可。


	**正确性说明：**

	依然考虑边 $(u,v)$，其中 $u$ 是 $v$ 在树上的祖先。

	如果 $u=s$，显然只能选择 $v$。

	否则按照数学归纳法，$u$ 一定已经被选择，所以不论 $v$ 是不是第一选择，都只能选择 $v$。

	这时有恰好 $n$ 条边被满足，方案是正确的。

时间复杂度为 $O(n+m)$。


---
```cpp
#include<bits/stdc++.h>
#define N 100009
using namespace std;
int n,m,ans,hd[N],tot,fi[N],c[N],nV[N],nE[N],nC,choose[N];
bool in[N<<1],vst[N];//in代表在不在搜索树内,vst代表有没有被选
struct edge{
	int t,nxt;
} es[N<<1];
//编号为i的边为(i*2)和(i*2+1)
void add(int u,int v){es[++tot]=(edge){v,hd[u]},hd[u]=tot;}
void dfs(int u){
	++nV[c[u]];
	for(int i=hd[u];i;i=es[i].nxt){
		++nE[c[u]];
		int v=es[i].t;
		if(c[v])continue;
		in[i]=in[i^1]=1;
		c[v]=c[u];
		dfs(v);
	}
}
void print(int u,int in_edge){
	for(int i=hd[u];i;i=es[i].nxt)if(in[i]&&i!=(in_edge^1)){
		printf("%d\n",i>>1);vst[i>>1]=1;
		print(es[i].t,i);
	}
}
int main(){
	cin>>n>>m;
	tot=1;
	for(int i=1;i<=n;++i){
		int u,v;scanf("%d%d",&u,&v);fi[i]=u;
		add(u,v),add(v,u);
	}
	for(int i=1;i<=m;++i)
		if(!c[i]){
			c[i]=++nC;
			dfs(i);
		}
	for(int i=1;i<=n;++i)if(!in[i<<1]){//第二种情况(选择一条后向边)
		int id=c[es[i<<1].t];choose[id]=i;
	}
	for(int i=1;i<=m;++i)if(nE[c[i]]==nV[c[i]]*2-2)
		choose[c[i]]=i;//第一种情况（dfs起始点）
	ans=m;
	for(int i=1;i<=nC;++i)
		if(nE[i]==nV[i]*2-2)--ans;
	cout<<n-ans<<endl;
	for(int i=1;i<=nC;++i){
		if(nE[i]==nV[i]*2-2){
			print(choose[i],0);
		}else{
			printf("%d\n",choose[i]);vst[choose[i]]=1;
			print(fi[choose[i]],0);
		}
	}
	for(int i=1;i<=n;++i)
		if(!vst[i])printf("%d\n",i);
	return 0;
}
```

---

## 作者：tzyt (赞：12)

update：2022/4/17 更正了博客地址

前言：题解可能比较啰嗦，因为这题比赛的时候没做出来，所以写题解主要用于整理自己的思路。如果你有思路只是代码打挂了简易直接跳到代码部分。

update@2022/3/13: 感谢[@小木虫](https://www.luogu.com.cn/user/213173)的提醒，**当前的解法不是正解！** 如果USACO的数据够强的话，目前我使用的匈牙利算法因为复杂度是 $O(nm)$，是过不了这道题的。如果想用我这个二分图匹配 + 拓扑的方法实现，可以使用dinic算法求二分图最大匹配（不过写起来会比较麻烦）。本人有时间的时候也会尝试用dinic实现这个解法并且更新题解。

[题目链接](https://www.luogu.com.cn/problem/P8095)

[博客中观看体验更佳](https://ttzytt.com/2022/02/P8095/)

# 1：题意
有 $N$ 头牛，$M$ 种麦片（每种一箱），每头都有第一和第二喜欢的麦片种类（下文简称为一选和二选），牛会优先选择自己最喜欢的麦片，当最喜欢的麦片被占用后会选择第二喜欢的麦片，问：
1. 最少会有多少牛得不到麦片。
2. 能达到此最小值的牛的排列
# 2：分析
## 2.1 第一小问
对于第一个小问，可以发现这是一个标准的二分图最大匹配问题，很容易想到使用匈牙利算法解决（然而这次比赛的时候我并没有想到）。不熟悉匈牙利算法和二分图匹配问题的同学可以参考[模板题](https://www.luogu.com.cn/problem/P3386)里的题解。这篇题解将主要关注第二小问的求解。
## 2.2 第二小问
对于第二小问，我一开始想的是先输出成功匹配到一选的牛，其次是成功匹配到二选的牛，最后输出没有成功匹配的牛。结果[交上去](https://www.luogu.com.cn/record/68553854)只过了样例。经过[@lutongyu](https://www.luogu.com.cn/user/37935)大佬的指导，我终于理解了这个做法的问题。

具体来说，对于成功匹配到一选的奶牛，可以先输出，最后输出没有成功匹配的奶牛也是没有问题的。真正的问题在于二选奶牛的顺序。考虑下面这样的一个数据（如下图）: 

```
1 (cow) -> [1 (fir), 2 (sec)]
2 (cow) -> [1 (fir), 3 (sec)] 
3 (cow) -> [3 (fir), 4 (sec)] 
```
![](https://cdn.luogu.com.cn/upload/image_hosting/63og5ij1.png)

我们可以试着手动模拟一下这个数据

我们首先尝试这个数据下的最优排列 `1 2 3`

1. $\text{Cow}_1$ 会先选择它的一选，也就是麦片 1
2. 因为 $\text{Cow}_2$ 的一选被 $\text{Cow}_1$ 占用了，所以它会选择它的二选，也就是麦片 3
3. $\text{Cow}_3$ 的一选被 $\text{Cow}_2$ 占用了，所以它会选择他的二选，也就是麦片 4

在这样的情况下，每一头奶牛都能吃到麦片

然后我们调换一下 $\text{Cow}_2$ 和 $\text{Cow}_3$ 的顺序，得到`1 3 2` 的顺序，以及下面的模拟过程

1. $\text{Cow}_1$ 会选择它的一选，也就是麦片 1
2. $\text{Cow}_3$ 会选择它的一选，也就是麦片 3
3. $\text{Cow}_2$ 的一选和二选都被占用了（麦片 1 3），它不能吃到麦片

在这样的情况下，$\text{Cow}_2$ 并不能吃到任何麦片

通过这个数据，我们可以发现直接输出匹配到二选的牛是不行的，还需要在输出匹配到二选的牛时做一些处理，保证这个排列能达到最大匹配数。

具体来说，我们可以使用一种类似拓扑排序的算法来解决二选奶牛的冲突问题。

我们首先来考虑当一头奶牛成功匹配到自己的一选，并且它的一选同时也是别的奶牛的一选会发生什么，拿上图中的 $\text{Cow}_1$ 举例子，它会影响到 $\text{Cow}_2$ 的选择（$\text{Cow}_1$ 占用了 $\text{Cow}_2$ 的一选，迫使其选择二选），而 $\text{Cow}_2$ 又会影响到 $\text{Cow}_3$ 的选择（$\text{Cow}_2$ 占用了 $\text{Cow}_3$ 的一选，迫使其选择二选）。通过观察，我们可以发现只要按照这样一个 “影响链” 来输出奶牛，就可以保证达到最大匹配。

# 3：算法过程

这一条链的开始一定是成功匹配到一选，并且迫使别的奶牛选择二选的奶牛（这个奶牛的一选也是别的奶牛的一选）。我们把这样的奶牛全部入队。我们再来考虑被影响的奶牛，为了找出 “影响链” 我们需要把这些被影响到的奶牛也入队（因为这些奶牛只能选择二选，而他们的二选可能会占用别的奶牛的一选，就像上图中的 $\text{Cow}_2$）。

为了找出有哪些牛是可能被影响的，我们可以引入一个 `inv_e[i]` 的动态数组（链式前向星），表示所有把 i 号麦片作为一选的牛（只有一选先被别的牛选了才会被影响）。

比如在上图中 `inv_e[1] = [` $\text{Cow}_1$ `,` $\text{Cow}_2$ `]`

我们知道在实现匈牙利算法的时候会用到 `matched[i]` 数组。它的下标表示右部节点，值表示匹配到这个右部节点的左部节点。在这题中，`matched[i]` 的下标就是麦片的编号，而值是匹配到这个麦片的牛。我们可以引入一个 `inv_match[i]` 数组，它的下标是牛，而值是麦片。通过 `inv_match` 我们可以知道每头牛最终匹配到的麦片是哪个（一选二选或者匹配失败）。

用上图举例子， `inv_match[` $\text{Cow}_2$ `]` 就等于麦片 3 （最终匹配到的是麦片 3）

下面的代码展示了如何找到所有被一选奶牛所影响的奶牛

```cpp
for(int i = 1; i <= n; i++){              //i遍历的是成功匹配到一选的奶牛
    if(invmatched[i] != e[i][0]) continue;//e[i][0]表示i的一选
                                          //invmatched[i] 是i最终匹配到的麦片
                                          //所以这句话的意思是如果不是一选就直接continue
    printf("%d\n",i);//如果是一选直接输出

    for(int cur:inve[e[i][0]]){         //遍历当前成功匹配一选的牛 可能影响的牛
                                        //e[i][0]表示的是i的一选，而i一定是成功匹配一选的牛
                                        //inve[e[i][0]]是所有一选和i的一选相同的奶牛，这些奶牛可能被i影响
        if(invmatched[cur] == e[cur][1])//前文提到了invmatched[cur] 表示的是cur最终匹配到的麦片
                                        //而e[cur][1] 表示的是 cur 的二选
        {                               //所以这句话确保了cur最终选到的是二选（说明这头牛被影响到了，没有选一选，同时也可以防止把i自己入队）
            q.push(cur);
        }
    }
}

```

接下来，对于已经进入队列的奶牛，他们的二选可能会占用别的奶牛的一选，所以我们也可以用相似的方法找出这个 “影响链”

```cpp
while(!q.empty()){
    int cur = q.front();
    printf("%d\n",cur);//队列是先进先出的结构，所以可以先输出在影响链上方的牛（更早被影响到的牛）
    q.pop();
    for(int nex:inve[e[cur][1]]){         //e[cur][1]是编号为cur的牛的二选
                                          //inve[e[cur][1]] 就是所有把 cur 的二选当作一选的牛，也就是可能被 cur 影响到的牛
        if(invmatched[nex] == e[nex][1]) {//最终选到的是二选（说明这头牛被影响到了）
            q.push(nex);
        }
    }
}
```

# 4：代码实现以及细节
最后给出详细代码（有注释解释细节）
```cpp
/*Date: 22 - 02-03 22 19
PROBLEM_NUM: P8095 [USACO22JAN] Cereal 2 S*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int n, m;
vector<int> e[MAXN], inve[MAXN];
queue<int> q;
int vised[MAXN], matched[MAXN];
int invmatched[MAXN];

bool found(int cur){//匈牙利算法
    for(int nex:e[cur]){
        if(vised[nex]) continue;
        vised[nex] = true;
        if(!matched[nex] || found(matched[nex])){
            matched[nex] = cur;
            invmatched[cur] = nex;
            vised[nex] = false;
            return true;
        }
    }
    return false;
}

int main(){
    int match_cnt = 0;
    scanf("%d%d",&n,&m);
    for(int i = 1; i<=n; i++){
        int f,s;
        scanf("%d%d",&f,&s);
        e[i].push_back(f);   //e[i][0]是i的一选
        e[i].push_back(s);   //e[i][1]是i的二选
        inve[f].push_back(i);//inve[f] 表示所有把 f 号麦片作为一选的牛
    }
    for(int i = 1;i <= n; i++){//匈牙利算法部分
        if(found(i)){
            match_cnt++;
        }
    }

    printf("%d\n", n - match_cnt);//饥饿的奶牛 = 所有奶牛 - 吃到麦片的奶牛

    for(int i = 1; i <= n; i++){          //i遍历的是成功匹配到一选的奶牛
    if(invmatched[i] != e[i][0]) continue;//如果不是一选就直接continue
    printf("%d\n",i);                     //如果是一选直接输出

    for(int cur:inve[e[i][0]]){         //遍历当前成功匹配一选的牛 可能影响的牛
                                        //e[i][0]表示的是i的一选，而i一定是成功匹配一选的牛
                                        //inve[e[i][0]]是所有一选和i的一选相同的奶牛，这些奶牛可能被i影响
        if(invmatched[cur] == e[cur][1])//前文提到了invmatched[cur] 表示的是cur最终匹配到的麦片
                                        //而e[cur][1] 表示的是 cur 的二选
            {                           //所以这句话确保了cur最终选到的是二选（说明这头牛被影响到了，没有选一选，同时也可以防止把i自己入队）
                q.push(cur);
            }
        }
    }
    
    while(!q.empty()){
        int cur = q.front();
        printf("%d\n",cur);//队列是先进先出的结构，所以可以先输出在影响链上方的牛（更早被影响到的牛）
        q.pop();
        for(int nex:inve[e[cur][1]]){         //e[cur][1]是编号为cur的牛的二选
                                              //inve[e[cur][1]] 就是所有把 cur 的二选当作一选的牛，也就是可能被 cur 影响到的牛
            if(invmatched[nex] == e[nex][1]) {//最终选到的是二选（说明这头牛被影响到了）
                q.push(nex);
            }
        }
    }

    for(int i = 1; i<=n; i++){//最后输出没有成功匹配到的奶牛
        if(!invmatched[i]){   //invmatched[i] == 0 说明奶牛 i 没有匹配到任何麦片
            printf("%d\n",i);
        }
    }

    system("pause");
}
```

最后，希望这篇题解能帮到你，如果还没看懂或者是发现了题解有问题都可以私信我或者在评论区指出，我会尽量回答或是解决问题。

---

## 作者：Alex_Wei (赞：8)

> [P8095 [USACO22JAN] Cereal 2 S](https://www.luogu.com.cn/problem/P8095)。

趣题！题目的限制很难不让人往二分图匹配方向上想，然后就寄了，因为在选 $s_i$ 的同时必须保证 $f_i$ 在此之前被别人选了，较难处理（不过可能也有办法）。

考虑在 $s_i$ 和 $t_i$ 之间连边。不难发现每个连通块独立，因此单独求解一个连通块 $G = (V, E)$：当 $|E| \geq |V|$ 时，连通块存在环。首先，我们知道最多能满足 $|V|$ 头奶牛，因为只有 $|V|$ 箱麦片。给出一个能够到达该上界的构造：

- 对于一棵树 $T$，如果任意一个节点 $r$ 被选了，那么从根开始 dfs 并把经过的边按顺序加入答案，就是一组合法解。这是因为在加入边 $e = (fa_i, i)$ 时，$fa_i$ 一定已经被选了（否则我们也不可能 dfs 到 $fa_i$），因此 $e$ 这条边对应的奶牛只能选麦片 $i$，导致从 $i$ 继续往下 dfs 到它的儿子 $v\in \mathrm{son}(i)$ 时，$e' = (i, v)$ 对应的奶牛只能选麦片 $v$。使用数学归纳法可以证明方案合法。（或者说加入每一条边 $(fa_i, i)$ 的时候，子节点 $i$ 显然没有被选）
- 因此，找到 $G$ 的任何一棵生成树 $T$，再找到任意 **非树边** $e\notin T$，首先令 $e$ 对应的奶牛选，那么 $f_e$ 被选中。再从 $f_e$ 开始对 $T$ 进行 dfs，并进行上述构造，即可得到一个满足 $|V|$ 头奶牛的达到上界的方案。

当 $|E| < |V|$ 时，$|E| = |V| - 1$，说明整个连通块是一棵树。此时从任意节点开始 dfs（即将任意节点作为根），把遍历到的边依次加入答案。同样的，因为加入每一条边时子节点必然没有被选，故构造合法，且拿到麦片的奶牛数量达到上界 $|V| - 1$。

最后，若一条边没有被选，说明这头奶牛拿不到麦片。剩下来没有被选的边均拿不到麦片，所以在输出完对答案有贡献的奶牛后，直接输出剩下来的边即可。

综上，我们在 $\mathcal{O}(n + m)$ 的时间内解决了该问题。本题的核心思路在于，考虑每头奶牛选了哪箱麦片较困难，由于一箱被选的麦片和一头选了麦片的奶牛 **一一对应**，因此转化为每箱麦片被哪头奶牛选中，即可轻松求解。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e5 + 5;
int n, m, ans, vis[N], buc[N];
int tot, f[N], s[N];
vector <pii> e[N];
vector <int> tr, cp, p;
void find(int id) {
	vis[id] = 1, tot += e[id].size(), cp.push_back(id);
	for(auto it : e[id]) {
		if(vis[it.fi]) continue;
		tr.push_back(it.se), find(it.fi);
	}
}
void dfs(int id, int fa) {
	for(auto it : e[id]) {
		if(!buc[it.se] || it.fi == fa) continue;
		p.push_back(it.se), dfs(it.fi, id);
	}
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &f[i], &s[i]);
		e[f[i]].push_back({s[i], i}), e[s[i]].push_back({f[i], i});
	} for(int i = 1; i <= m; i++) if(!vis[i] && e[i].size()) {
		tot = 0, cp.clear(), tr.clear(), find(i);
		for(int it : tr) buc[it] = 1;
		if(tot < cp.size() << 1) ans += tot >> 1, dfs(i, 0);
		else {
			int out = -1; ans += cp.size();
			for(int id : cp) {
				for(auto it : e[id]) if(!buc[it.se]) {out = it.se; break;}
				if(~out) break;
			} p.push_back(out), dfs(f[out], 0);
		} for(int it : tr) buc[it] = 0;
	} cout << n - ans << endl;
	for(int it : p) cout << it << "\n", buc[it] = 1;
	for(int i = 1; i <= n; i++) if(!buc[i]) cout << i << "\n";
	return 0;
}
```

---

## 作者：GaryH (赞：5)

# P8095 题解

**题意**：

有 $n$ 头牛和 $m$ 种麦片，每种麦片只有一箱，每头牛分别有其最喜欢的和第二喜欢的两种不同的麦片。

需要给所有牛制定一个取麦片的先后顺序，使得没有拿麦片的牛的数量最少。

一头牛取麦片的方式是：如果其最喜欢的麦片还在，就直接拿一箱其最喜欢的，

否则，如果其第二喜欢的还在，就拿一箱其第二喜欢的，否则就一箱也不拿。

输出这个顺序对应的排列和没有拿到麦片的牛数的最小值。

> $n,m\le10^5$。

**做法**：

设没有拿麦片的牛的数量的最小值为 $val$。

则我们将每头牛和其喜欢的麦片连边，设这张二分图的最大匹配数为 $mch$，

则我们一定有 $mch\ge n-val$，

原因是，所有牛所拥有麦片的种类的 $n$ 元组，与图中所有符合的二分图匹配是一一对应的。

当然，也许有可能出现 $mch>n-val$，

出现这件事的条件是，最大匹配对应的那个麦片种类 $n$ 元组，无法通过题意中的取法构造出来。

那这时我们猜测，任何一种牛群拿麦片的方式都可以被构造出来。

也就是说，我们要证明的是，对任何一种匹配 $X$，都能构造出一个排列，使得：

牛群按照这个排列的顺序取麦片，最后所有牛所拥有麦片种类的 $n$ 元组就对应了匹配 $X$。

如果这个猜测成立，那么最后答案就是最大匹配，那我们考虑能否证明这个猜测。

因为最后要求输出排列，故考虑给出构造性证明。

考虑构造的困难之处，在于匹配与题意中吃草顺序的不匹配，

即某头牛在匹配中应该拿走其第二喜欢的麦片，然而实际上，

它可能因为其最喜欢的麦片还在，从而直接拿走其最喜欢的麦片，

甚至，其最喜欢的麦片有可能是另外一头牛在最终匹配方案中所拥有的麦片，

我们要做的事，是尽量地消除这些错位带来的影响。

我们记最终匹配方案中，第 $i$ 头牛拿了第 $t_i$ 种麦片，其最喜欢第 $f_i$ 种麦片，第二喜欢第 $s_i$ 种麦片，

当然，在这里我们不需要考虑没拿麦片的牛，因为我们在排列的最后让这些牛尝试取一次麦片即可。

这里有一个性质，即所有 $t_i$ 互不相同。

我们维护一个当前排列，代表所有已经尝试取过麦片的牛。

首先，我们把所有编号 $i$ 满足 $f_i=t_i$ 的牛加入排列末尾，这样显然一定足够优，

而剩下还需要考虑的牛的编号 $i$，都满足 $s_i=t_i$，设集合 $S$ 包含了所有编号满足 $s_i=t_i$ 的牛。

那么，接下来我们会做若干次操作，直到 $S$ 变成空集。

在每次操作中，我们从 $S$ 中随便取出一头牛并开始检查，设最初取出的牛编号为 $u$，则：

如果此时第 $f_u$ 种麦片已经不存在了，就直接终止检查；

否则，如果 $S$ 中不存在牛 $v$ 满足 $s_v=f_u$，我们也直接终止检查；

否则，此时 $S$ 中一定存在牛 $v$ 满足 $s_v=f_u$，我们将 $(u,v)$ 连边，再对 $v$ 进行上面的检查。

注意，此处的连边与上面牛与麦片连的边无关，只是用来方便叙述的，

也就是说，每次操作中连的边是在一张独立的新图上的，跟其他次操作以及最初的图无关。

那么，我们在这次操作中检查过的所有牛，一定会形成形如一个环接上一条链的样式，

当然，环长和链长可以是 $0$，即可以是纯的一个环或一条链。

考虑此时，我们将所有牛按检查牛顺序的倒序加入排列末尾，并从 $S$ 中删去这些牛，是足够优的。

为什么？因为，如果让牛们按上面这种构造方式里的顺序来尝试取麦片的话，

所有环上的牛都会拿走它们最喜欢的麦片，而所有链上的牛都会拿走它们第二喜欢的麦片。

具体证明就不赘述了，相信这个也不难，画个图手动模拟一下就能理解。

当然，在排列的最后，我们还需要加入所有在匹配中没有拿到麦片的牛。

这样，我们就对任意一个没有特殊性质的匹配 $X$，给出了一种排列顺序，满足：

所有牛按这个顺序去麦片，最后每头牛所拥有的麦片就和 $X$ 对应。

那么，我们对初始图的最大匹配构造出这样的一个排列顺序即可。

最后一个问题，是如何求二分图的最大匹配，因为本题数据较大，故可以使用网络流，

时间复杂度是 $O((n+m)\sqrt{n+m})$，瓶颈在 ```dinic``` 算法跑二分图匹配。

因为构造排列的具体实现可能还有一些细节，故给出代码以便参考，当然最好还是自己写。

**code**：

```
#include <bits/stdc++.h>

#define fi first
#define se second
#define vi vector
#define mp make_pair
#define pb push_back
#define LL long long
#define pii pair < int , int >
#define SZ(x) ((int)(x.size()))
#define ckmax(a, b) ((a) = max((a), (b)))
#define ckmin(a, b) ((a) = min((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define edg(i, v, u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

using namespace std;
inline int read() {
	// 快读
}
const int N (3e5 + 10);
const int INF (2e9 + 10);
struct Edge {
	int fr, to, cp, fl;
};

struct Dinic {
	int n, m;
	int s, t;
	int d[N];
	int cur[N];
	int vis[N];
	vector < Edge > E;
	vector < int > G[N];
	
	void init (int n) {
		E.clear();
		rep (i, 0, n - 1) G[i].clear();
	}
	void adde (int u, int v, int c) {
		E.pb ((Edge) {u, v, c, 0});
		E.pb ((Edge) {v, u, 0, 0});
		int sz = E.size();
		G[u].pb (sz - 2), G[v].pb (sz - 1);
	}
	bool bfs() {
		queue < int > q;
		memset (vis, 0, sizeof (vis));
		q.push (s), d[s] = 0, vis[s] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			rep (i, 0, SZ (G[u]) - 1) {
				Edge& e = E[G[u][i]];
				if (!vis[e.to] && e.cp > e.fl) 
				  d[e.to] = d[u] + (vis[e.to] = 1), q.push (e.to);
			}
		}
		return vis[t];
	}
	int dfs (int u, int flw) {
		if (u == t || !flw) return flw;
		int flow = 0;
		for (int& i = cur[u]; i < SZ (G[u]); i++) {
			Edge& e = E[G[u][i]]; int f = 0;
			if (d[e.to] == d[u] + 1 && (f = dfs (e.to, min (flw, e.cp - e.fl))) > 0) {
				e.fl += f, E[G[u][i] ^ 1].fl -= f, flow += f, flw -= f;
				if (flw == 0) break;
			}
		}
		if (flow == 0) d[u] = 0;
		return flow;
	}
	int mxflow (int s, int t) {
		this -> s = s, this -> t = t;
		int flow = 0;
		while (bfs()) {
			memset (cur, 0, sizeof (cur));
			flow += dfs (s, INF);
		}
		return flow;
	}
} Dinic;

int tot;
int num;
int n, m;
int s, t;
int a[N];
int b[N];
int rb[N];
int res[N];
int buk[N];
int ned[N];

int main() {
	n = read(), m = read();
	memset (rb, -1, sizeof rb);
	rep (i, 1, n) a[i] = read() + n, b[i] = read() + n;
	s = n + m + 1, t = s + 1;
	rep (i, 1, n) {
		Dinic.adde (s, i, 1);
		Dinic.adde (i, a[i], 1);
		Dinic.adde (i, b[i], 1);
	}
	rep (i, 1, m) Dinic.adde (i + n, t, 1);
	int val = n - Dinic.mxflow (s, t);
	printf ("%d\n", val);
	rep (u, 1, n) for (int id : Dinic.G[u]) {
		Edge e = Dinic.E[id];
		if (e.fl != 1 || e.cp == 0) continue;
		if (e.to == a[u]) {
			res[++tot] = u, buk[a[u]] = 1, ned[u] = 1; break;
		}
		rb[b[u]] = u, ned[u] = 2;
	}
	rep (i, 1, n) {
		if (ned[i] != 2) continue;
		int u = i;
		stack < int > stk;
		while (true) {
			if (ned[u] == 1) break;
			stk.push (u);
			if (buk[a[u]] || rb[a[u]] == -1 || rb[a[u]] == i) break;
			ned[u] = 1, u = rb[a[u]];
		}
		while (!stk.empty()) {
			u = stk.top();
			ned[u] = 1;
			if (!buk[a[u]]) buk[a[u]] = 1;
			else buk[b[u]] = 1;
			res[++tot] = u, stk.pop();
		}
	}
	rep (i, 1, n) if (ned[i] != 1) res[++tot] = i;
	rep (i, 1, tot) printf ("%d\n", res[i]);
	return 0;
}
```



---

## 作者：__lyh__ (赞：5)

~~现在连银组都有蓝题了吗？~~

## 思路：

求奶牛的最优排列，不难想在这道题要用到二分图匹配。匹配过程与板子大体相同，只不过加多了一个 $second$。

匹配好以后，剩下的也不难了。

## 算法流程：

1. 二分图匹配，求出一种最优解。对于每一箱麦片，得到它应该被哪头牛吃（或者没被吃），可以使结果最优。

2. 对牛的顺序进行约束，设某头牛编号为 $x$，它的第一喜欢、第二喜欢的麦片编号分别为 $a$，$b$，如果牛 $x$ 吃到的是麦片 $b$，那麦片 $a$ 肯定早就被吃了，此时吃掉麦片 $a$ 的牛 $y$ 一定要排在牛 $x$ 之前，对于这种情况，建一条从 $x$ 到 $y$ 的单向边，表示 $x$ 排在 $y$ 之后。

3. 进行拓扑排序，输出答案。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)){x = x * 10 + ch - 48; ch = getchar();}
	return f * x;
}

int vis[N], n, m, ans;
int fri[N], sec[N], to[N], ind[N];
vector<int> e[N];
inline void add(int x, int y)
{
	e[x].push_back(y);
	ind[y]++;
}

inline bool dfs(int u)//二分图匹配板子
{
    if(!vis[fri[u]])
	{
        vis[fri[u]] = 1;
        if ((!to[fri[u]]) || dfs(to[fri[u]]))
		{
            to[fri[u]] = u;
            vis[fri[u]] = 0;
            return 1;
        }
        vis[fri[u]] = 0;
    }
    if(!vis[sec[u]])
	{
        vis[sec[u]] = 1;
        if((!to[sec[u]]) || dfs(to[sec[u]]))
		{
            to[sec[u]] = u;
            vis[sec[u]] = 0;
            return 1;
        }
        vis[sec[u]] = 0;
    }
    return 0;
}


int main()
{
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
	{
		fri[i] = read();
		sec[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		if(dfs(i))
		{
			ans++;
		}
	}
	memset(vis, 0, sizeof(vis));
	printf("%d\n", n-ans);
	for(int i = 1; i <= m; i++)
	{
        if(i == sec[to[i]])//第 i 个麦片被编号为 to[i] 的牛所吃
		{
            add(to[fri[to[i]]],to[i]);
        }
    }
    int head = 0;
    while(head < n)
	{
        for(int i = 1; i <= n; i++)
		{
            if(vis[i])
                continue;
            if(!ind[i])
			{
                vis[i] = 1;
                printf("%d\n", i);
                head++;
                int l = e[i].size();
                for (int j = 0; j < l; j++)
                {
                	int too = e[i][j];
                	ind[too]--;
				}
            }
        }
    }
}
```


---

## 作者：I_am_Accepted (赞：4)

### Preface

我和许多同学赛后一直讨论这道题，有的说网络流，有的说拓扑，~~有的说不可做~~，而我用了应该是最简单的思路，所以有底气来发题解~~主要是我比较闲~~。

这篇题解写在官方题解出来之前，所以如果官方用了非常巧妙的算法，~~那么请各位抽烟~~那么算我输。

### Analysis

建图：$m$ 个点代表麦片，$n$ 条有向边（代码实现时记得存反向边），$x\to y$ 表示有一个奶牛的第一选择是 $y$，第二选择是 $x$（不要搞反了）。

**请永远记住：边是奶牛，点是麦片，$n$ 是边数，$m$ 是点数。**

当然，由于边要存较多的信息（奶牛的编号，正反方向等），请使用前向星。（我之前写的是 vector，$176$ 行的代码重写 qwq）

算法开始。

我们将每一个连通块（不是强连通分量）分别考虑。现在考察连通块 $A$。计算点数和边数 $V,E$。

#### 情况（一）$E=V-1$

必然是棵树（忽略定向）。$A$ 中绝对没有挨饿的奶牛。

构造（即证明）：

由于 $A$ 是一个 DAG（有向无环图），必然有无入度的点，DFS 选取奶牛即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/95st68ie.png)

#### 情况（二）$E\ge V$

必然有一个基环树（环可能是重边）的子图（忽略定向）。$A$ 中挨饿的奶牛数 $=E-V$（即不在基环树内的边数）。

证明：

由于麦片一共就 $V$ 包，所以挨饿的奶牛数 $\ge E-V$。

接下来 基环树子图上每条边都有对应点 的构造 即证明了挨饿的奶牛数 $\le E-V$，即原命题得证。

构造：

任取一基环树子图 $B$。设基环为 $C$，长度为 $len$。选取任意基环上一条边，在基环上沿着这条边的方向依次满足奶牛。这样基环上的边都有对应点了，且都是基环上的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/lh6wa9pa.png)

然后我们将每个基环上的点为根的子树分别 DFS，类似情况（一）求解。

![](https://cdn.luogu.com.cn/upload/image_hosting/db06xngx.png)

算法结束。

总时间 $O(n+m)$，而常数较大。

### Code

[不带注释 2.27KB 代码提交](https://www.luogu.com.cn/record/68578612)

注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Fe(x,y) for(int x=h[y];x;x=e[x].nxt) //for:edge 跟铁没关系 qwq 
#define N 100100
struct edge{
	int to,nxt,id;
	bool fw;//is it forward?
}e[2*N];//正反都要 
int n,m,tot=1,h[N],sum,f[N];//tot:从 1 开始，方便找反向边 h:前向星的头 sum:该联通块的边数 f[i]:搜索树中 i 的父亲 
bool vis[N],out[N],ban[N],ins[N];//vis[i]:i 所在连通块是否被算过 out[i]:边（奶牛）是否被输出了 ban[i]:点 i DFS 是否被达咩了 ins[i]:是否在搜索树中的祖先集合 
vector<int> v,con,cy;//v:待输出的方案 con:当前连通块 cy:基环上依次的点
pair<int,int> key;//环的两端（环上相邻） 
inline void print(int x){v.pb(x);out[x]=1;}
inline void adde(int x,int y,int id,bool z){e[++tot]={y,h[x],id,z};h[x]=tot;}//加边 
void see(int rt){//查看整个连通块 
	vis[rt]=1;con.pb(rt);
	Fe(i,rt){
		sum++;
		if(!vis[e[i].to]) see(e[i].to);
	}
}
void tree(int rt,int fa){//DFS tree 
	Fe(i,rt){
		int to=e[i].to;
		if(to==fa) continue;
		print(e[i].id);
		tree(to,rt);
	}
}
void solve1(int x){//树（边有向） 
	int root=-1;bool flag;
	for(int i:con){//找无入度的点 
		flag=1;
		Fe(j,i)if(!e[j].fw){flag=0;break;}
		if(flag){root=i;break;}
	}
	tree(root,0);
}
bool dfs(int x,int fr,int fa){//找到一个环（可能是重边，但不能是正向边和对应的反向边） 
	ins[x]=1;f[x]=fa;
	Fe(i,x){
		if((i^fr)==1) continue;//fa来的反向边，达咩 
		if(ins[e[i].to]){
			key=mkp(x,e[i].to);
			return true;
		}
		if(dfs(e[i].to,i,x)) return true;
	}
	ins[x]=0;return false;
}
void subt(int rt){//基环树的子树求解 
	Fe(i,rt){
		if(ban[e[i].to]) continue;
		print(e[i].id);
		ban[e[i].to]=1;
		subt(e[i].to);
	}
}
inline bool fang(int x,int y){Fe(i,x)if(e[i].to==y)return e[i].fw;}//x=>y 的方向 
inline int cow(int x,int y){Fe(i,x)if(e[i].to==y && !out[e[i].id])return e[i].id;}//x=>y 的奶牛编号 
void solve2(int x){//最优秀为基环树（基环可能是重边） 
	cy.clear();
	dfs(x,0,0);//True 
	int tmp=key.fir;
	while(true){
		cy.pb(tmp);
		if(tmp==key.sec) break;
		tmp=f[tmp]; 
	}
	int len=cy.size();
	if(!fang(cy[0],cy[1])){//翻转环（镜像） 
		key=mkp(cy[0],cy[1]);
		For(i,2,len-1) cy[i-2]=cy[i];
		cy[len-2]=key.fir;
		cy[len-1]=key.sec;
		reverse(cy.begin(),cy.end());
	}
	For(i,0,len-1) print(cow(cy[i],cy[(i+1)%len])); //环上解决 
	for(int i:cy) ban[i]=1;
	for(int i:cy) subt(i);//子树解决 
}
signed main(){IOS;
	cin>>n>>m;
	int x,y;
	For(i,1,n){
		cin>>x>>y;
		adde(y,x,i,1);//正向边 (sec->fir)
		adde(x,y,i,0);//反向边 (fir->sec)
	}
	For(i,1,m){
		if(vis[i]) continue;
		sum=0;con.clear();
		see(i);
		sum>>=1;//双向边数量折半 
		if((int)con.size()==sum+1) solve1(i);
		else solve2(i);
	}
	int ans=0;
	For(i,1,n) if(!out[i]) ans++;//饥饿的 
	cout<<ans<<endl;
	for(int i:v) cout<<i<<endl;//输出有的吃了 
	For(i,1,n) if(!out[i]) cout<<i<<endl;//输出挨饿的 
return 0;}
```

---

## 作者：binbin_200811 (赞：3)

# [USACO22JAN] Cereal 2 S 网络流解法

其实很多东西在 tzyt 的题解里已经写得很详细了，主要是网络流的做法输出方案有较大区别。

### part 1 求最小数量

本题直接思路看上去就是二分图最大匹配，即以奶牛为 x 部，以谷物为 y 部，按照每头奶牛向自己最喜欢的谷物连边，最大匹配中的匹配边即连接了奶牛和喜欢吃的谷物。

然后我们就想起了一个熟悉的~~国家~~算法——匈牙利。

接着我们看数据规模

抬走匈牙利

为了应对该数据规模，我们需要使用喜闻乐见的 dinic 算法，本文实现使用的是 isap（dinic 优化常数后的算法）。

dinic 算法在图中边流量均为 $1$ 时，时间复杂度下降为 $O(\sqrt{n}m)$。

中 $n$ 为节点个数，$m$ 为边数。

设立一原点，一汇点，从原点向奶牛连流量为 $1$ 的边，从谷物向汇点连流量为 $1$ 的边，奶牛向喜欢的节点连一条边。

最大流量即为最大匹配。

### part 2 排列方案

在网络流中，如果该边被选，那么该边流量将会为变 $0$。按照这样，我们便可以求出选中一头奶牛的奶牛应该选什么吃。

正常的思路：将选择自己一选谷物的奶牛输出，在将选择二选谷物的奶牛输出。

但是，如果二选奶牛中 $A$ 奶牛的一选是 $B$ 奶牛的二选，且两头奶牛都选择了自己的二选。

这样一来，$A$ 奶牛先输出的话 $B$ 奶牛则无法吃到二选谷物，从而增加了饥饿奶牛数量。

所以我们需要拓扑排序，即若 $A$ 奶牛选择了二选，那么选择了他的一选奶牛 $B$ 要向 $A$ 连一条有向边。输出时先输出入度为 $0$ 的节点，然后将自己的出边删除，即将临接点的入度减小 $1$ 输出。

代码如下：
```cpp
void out(int x) {
    if (x == 0)
        return;
    printf("%d\n", x);
    vis[x] = true;//这个标记该点是否输出
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        rd[v]--;//入度减小1
        out(v);
    }
}
```

实际上每个奶牛最多被一个其他奶牛连接，因为不可能有 $1$ 个谷物被 $2$ 个奶牛吃（即入度最多为 $1$），如果入度为 $0$ 了便可以输出。

结束了吗？

并没有，在匈牙利算法中，我们可以在最大匹配的情况下优先选择自己的一选，但网络流的选择过于迷幻，所以照上文所示方法连边可能出现环。

如：$A$ 的一选被 $B$ 选，$B$ 的一选被 $A$ 选。

为了解决这个问题我们先探究一下环的性质。

1.每头奶牛只有一个入度，也就是说，不会出现重叠的环。

2.且环上的节点可以直接选择自己的一选（只有选了二选才会被连边）而不会减少匹配数量。

3.环上节点可能有多个出度。

总结一下，连出的一个有向图中只可能有一个环，而环上的点可以有多个出度。

正确的环如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wk1ikj5o.png)

错误的环如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/94rpukpf.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/eqd2y72x.png)

我们可以 bfs 判环，判环后*优先输出*环上节点（避免非环上节点抢谷物，因为此时环上点均为选择一选，而原来的建边关系已经改变，不能保证不被抢谷物）。

在依次输出分支。

bfs 代码如图：

```cpp
int bfs1(int x) {
    while (!que.empty()) que.pop();

    que.push(x);
    cis[x] = -1;//起点设为-1，避免后面加入队列导致错误
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!cis[v]) {
                que.push(v);
                cis[v] = u;
            }
            else if(v==x) return u;//连向起点，发现环
        }
    }
    return -1;//未发现环
}
```

也许值得注意的地方：

cis 数组连接的是自己的上一个点（方便输出环上点），此数组在 bfs 不用清 $0$。如果清 $0$，则有可能因为非环节的遍历过多次而导致`TLE`。

输出环上节点后再依次输出非环节点即可。

最后输出无法选择的节点。

### CODE
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;

struct node {
    int to, nxt, val;
} edge[maxn * 2], ed[maxn * 2];

int n, m, s, t, tot = 1;
int deep[maxn], gap[maxn], p[maxn], head[maxn], si[maxn], f[maxn], fp[maxn], rd[maxn], cd[maxn], cis[maxn];

bool vis[maxn];

queue<int> que;
//建边
void add(int x, int y, int z) {
    tot++;
    edge[tot].to = y;
    edge[tot].val = z;
    edge[tot].nxt = head[x];
    head[x] = tot;
}
//网络流部分
void bfs() {
    deep[t]++;
    gap[deep[t]]++;
    que.push(t);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!deep[v])
                deep[v] = deep[u] + 1, que.push(v), gap[deep[v]]++;
        }
    }
}
int dfs(int x, int flow) {
    if (x == t) {
        return flow;
    }
    int usp = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (deep[v] == deep[x] - 1 && edge[i].val) {
            int quan = dfs(v, min(flow - usp, edge[i].val));
            edge[i].val -= quan;
            edge[i ^ 1].val += quan;
            usp += quan;
        }
        if (flow == usp)
            return flow;
    }
    gap[deep[x]]--;
    if (gap[deep[x]] == 0)
        deep[s] = n + m + 1;
    deep[x]++;
    gap[deep[x]]++;
    return usp;
}
int isap() {//dinic 的优化版本
    int mxflow = 0;
    bfs();
    while (deep[s] <= n + m + 1) mxflow += dfs(s, 1000000000);
    return mxflow;
}

int bfs1(int x) {
    while (!que.empty()) que.pop();

    que.push(x);
    cis[x] = -1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!cis[v]) {
                que.push(v);
                cis[v] = u;
            }
            else if(v==x) return u;
        }
    }
    return -1;
}
void out(int x) {
    if (x == 0)
        return;
    printf("%d\n", x);
    vis[x] = true;
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        rd[v]--;
        out(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    s = n + m + 1, t = n + m + 2;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(i, y + n, 1);
        add(y + n, i, 0);
        add(s, i, 1);
        add(i, s, 0);
        add(i, x + n, 1);
        add(x + n, i, 0);
        f[i] = x, si[i] = y;
    }
    for (int i = 1; i <= m; i++) add(i + n, t, 1), add(t, i + n, 0);//二分图转网络流建边

    printf("%d\n", n - isap());

    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j; j = edge[j].nxt) {
            int v = edge[j].to;
            if (v == s)
                continue;
            if (edge[j].val == 0) {
                p[i] = v - n;
                fp[v - n] = i;
                break;//p[i]表示i的选择，fp[i]表示选择谷物i的奶牛编号（后面连有向边）
            }
        }
    }
    memset(head, 0, sizeof(head));//重新建边
    memset(edge, 0, sizeof(edge));
    memset(vis,0,sizeof(vis));
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == si[i]) {
            if (fp[f[i]]) {
                rd[i]++;//rd表示入度
                add(fp[f[i]], i, 0);
            }
        }
    }
    for (int i = 1; i <= n; i++) {//输出无环的有向图
        if (rd[i] == 0 && p[i] && !vis[i])
            out(i);
    }
    for(int i=1;i<=n;i++)//判环+输出环上节点
    {
        if(rd[i]&&!vis[i])
        {
            int u=bfs1(i);
            while(u!=-1)
            {
                printf("%d\n",u);
                vis[u]=true;
                for(int j=head[u];j;j=edge[j].nxt)
                {
                    int v=edge[j].to;
                    rd[v]=0;
                }
                rd[u]=0;
                u=cis[u];
            }
        }
    }
    for (int i = 1; i <= n; i++) {//输出非环节点
        if (rd[i] == 0 && p[i] && !vis[i])
            out(i);
    }

    for (int i = 1; i <= n; i++)
        if (!p[i])
            printf("%d\n", i);
}
```

---

## 作者：lzqy_ (赞：3)

二分图板子题。

考虑将牛作为一个点集，麦片作为一个点集。若奶牛 $A$ 喜欢麦片 $a$，则 $A$ 与 $a$ 连边，这样建出的图显然是一个二分图。奶牛总数减二分图最大匹配数即为饥饿奶牛的最小个数。

注意，由于奶牛优先拿第一喜欢的麦片，所以在二分图匹配的时候，优先匹配第一喜欢的麦片。

至于最后输出的排列，只需要满足以下条件即可：

- 若奶牛 $A$ 第一喜欢麦片 $a$，第二喜欢麦片 $b$，且奶牛 $A$ 拿了麦片 $b$，奶牛 $B$ 拿了麦片 $a$，则 $B$ 在 $A$ 前面。

- 若奶牛 $A$ 第一喜欢麦片 $a$，第二喜欢麦片 $b$，且奶牛 $B,C$ 拿了麦片 $b,c$，则 $B,C$ 在 $A$ 前面。

虽然看上去好像是拓扑，但递归输出就好了。

具体实现看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
inline int read()
{
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
int n,m,ans[maxn];
int a[maxn],b[maxn];
int pp[maxn],vis[maxn];
bool dfs(int x,int t){
	if(vis[x]==t) return 0;
	vis[x]=t;
	if(!pp[a[x]]||dfs(pp[a[x]],t)){
   //优先拿麦片a[x](第一喜欢)
		pp[a[x]]=x,pp[x]=a[x];
		return 1;
	}
	else if(!pp[b[x]]||dfs(pp[b[x]],t)){
 	//再拿麦片b[x](第二喜欢)
		pp[b[x]]=x,pp[x]=b[x];
		return 1;
	}
	return 0;
}
void Print(int x){//输出
	if(vis[x]) return ;
	vis[x]=1;//vis[x]=1:奶牛x已经输出过
	if(!pp[x]){
   //如果奶牛x没有拿走麦片
   //那么拿走它第一/二喜欢的麦片的奶牛要先输出
		Print(pp[a[x]]);
		Print(pp[b[x]]);
		printf("%d\n",x);
		return ; 
	}
	if(pp[x]==b[x]){
	//如果奶牛x拿走的是它第二喜欢的麦片
	//那么拿走它第一喜欢的麦片的奶牛要先输出
		Print(pp[a[x]]);
		printf("%d\n",x);
		return ;
	}
	//否则直接输出
	printf("%d\n",x);
}
int main(){
	int sum=0;
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read()+n,b[i]=read()+n;
	for(int i=1;i<=n;i++) dfs(i,i);//求二分图最大匹配
	for(int i=1;i<=n;i++) sum+=bool(pp[i]);
	printf("%d\n",n-sum);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i]) Print(i);
	return 0;
```



---

## 作者：Little09 (赞：2)

先不考虑第一喜欢和第二喜欢的区别，假设奶牛可以任意选择第一喜欢和第二喜欢。那么可以把奶牛看做无向边，麦片看做是顶点，建出一张无向图。

当然图不一定联通，考虑每个 $x$ 点的联通块：

- 如果是树，那么有 $x-1$ 条边，考虑浪费掉一个点（例如根），每条边选择儿子即可。在有第一喜欢和第二喜欢的情况下，这样做自然也是可行的。

- 如果不是树，那么至少有 $x$ 条边。显然最多只有 $x$ 只奶牛满足。考虑他的生成树（这里拿 DFS 树更方便）包含 $x-1$ 条边，再随便选一条额外的边。我们先选择额外的边，它的第一喜欢的点设为根。其他边按照树做就行了。

于是每个连通块都最大化了，就做好了。

代码不够优美，仅供参考。

```cpp
// By: Little09
// Problem: P8095 [USACO22JAN] Cereal 2 S
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8095
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(x) memset(x,0,sizeof(x))
#define printYes puts("Yes")
#define printYES puts("YES")
#define printNo puts("No")
#define printNO puts("NO")

const ll inf=1000000000000000000; 
//const ll mod=998244353;
//const ll mod=1000000007;

const int N=100005;
int n,m; 
int a[N],b[N];

vector<int>t[N],v[N];
vector<int>g[N],val[N];

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
inline char readchar()
{
	char C=getchar();
    while (C<33||C>126) C=getchar();
    return C;
}
inline int raed(){return read();}
bool vis[N];
int s,num;
int ans[N],cnt;
bool used[N];
void dfs(int x,int fa)
{
	num++;
	vis[x]=1;
	for (int i=0;i<t[x].size();i++)
	{
		if (v[x][i]==fa) continue;
		if (vis[t[x][i]]==1)
		{
			if (s==-1) 
			{
				s=a[v[x][i]];
				ans[++cnt]=v[x][i];
				used[v[x][i]]=1;
			}
			continue;
		}
		g[x].push_back(t[x][i]);
		g[t[x][i]].push_back(x);
		val[x].push_back(v[x][i]);
		val[t[x][i]].push_back(v[x][i]);
		dfs(t[x][i],v[x][i]);
	}
}

void dfs2(int x,int fa)
{
	for (int i=0;i<g[x].size();i++)
	{
		if (val[x][i]==fa) continue;
		ans[++cnt]=val[x][i];
		used[val[x][i]]=1;
		dfs2(g[x][i],val[x][i]);
	}
}

int main()
{
	m=read(),n=raed();
	for (int i=1;i<=m;i++)
	{
		a[i]=read(),b[i]=read();
		t[a[i]].push_back(b[i]);
		t[b[i]].push_back(a[i]);
		v[a[i]].push_back(i);
		v[b[i]].push_back(i);
	}
	int tot=0;
	for (int i=1;i<=n;i++)
	{
		if (vis[i]==1) continue;
		s=-1,num=0;
		dfs(i,-1);
		if (s==-1) tot+=num-1;
		else tot+=num;
		if (s==-1) dfs2(i,-1);
		else dfs2(s,-1);
	}
	for (int i=1;i<=m;i++)
	{
		if (used[i]==0) ans[++cnt]=i;
	}
	cout << m-tot << endl;
	for (int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
	return 0;
}

```


---

## 作者：Mirasycle (赞：1)

显然有一个二分图匹配 $+$ 拓扑排序的做法，这里记录另一个巧妙的贪心线性做法。

考虑经典建图模型，我们对于一头奶牛建立一条边，边的两个端点分别为它最喜欢的麦片和次喜欢的。

每条边要去贪心地匹配其某个端点。多条边可能共端点，所以我们需要对于每个联通块都贪心一下。

对于每个联通块答案都有一个上界就是 $\min(|E|,|V|)$。

下面证明这个上界可以构造出来，要分类讨论一下 $|E|$ 和 $|V|$ 的大小关系。

- 树

此时满足 $|E|<|V|$，也就是说我们需要对于每条边都找到一个点来匹配。可以发现**限制最宽松的地方**是叶子节点向上的那一条边，因为叶子节点只连了一条边，所以没边和这条边抢点，就算其上方端点被抢了，它也总能至少匹配到下方端点。因此我们只需要贪心地让上方边选就行了。dfs 一下，根据遍历到边的顺序将边放入排列即可。

- 图

此时满足 $|E|\ge |V|$。我们需要每个点都能有边被匹配到。还是根据上面的思路，我们要优先满足上方边。一个很直接的思路就是我们随机找一条边，然后去满足这条边的 $f_i$。以 $f_i$ 为根建立 dfs 树（以 $f_i$ 为根的原因是上方点被选择了，不会导致下方边无可选的点，和树的思想一样），在 dfs 树上又能满足 $|V|-1$ 条边，一共就是 $|V|$ 条边达到了上限。可是有一个问题，就是我们第一次选择的边不能出现在后面的那个 dfs 树里，如果我们选择了一条割边，那后续就无法生成 dfs 树了。直接 tarjan 找非割边太麻烦了，可以先随便建立一颗 dfs 树，此时非树边就必然是非割边了，随便抽条非树边出来跑上述算法就行了。

时间复杂度 $O(n+m)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int n,m,A=0,f[maxn],s[maxn];
int vis2[maxn],cur,cnt;
vector<int> ans; int vis[maxn];
vector<pair<int,int> > G[maxn];
void dfs(int u,int fa){
	vis[u]=1; cnt++;
	for(auto z:G[u]){
		int v=z.fi;
		if(v==fa) continue;
		if(vis[v]){ cur=z.se; continue; }
		dfs(v,u);
	}
}
void get(int u){
	vis2[u]=1;
	for(auto z:G[u]){
		int v=z.fi;
		if(z.se==cur||vis2[v]) continue;
		ans.pb(z.se); get(v);
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>f[i]>>s[i];
		G[f[i]].pb(s[i],i);
		G[s[i]].pb(f[i],i);
	}
	for(int i=1;i<=m;i++){
		if(vis[i]) continue;
		cnt=0; cur=0;
		dfs(i,0); A+=cnt;
		if(!cur) get(i),A--;
		else{
			ans.pb(cur);
			get(f[cur]);
		}
	}
	cout<<n-A<<endl;
	memset(vis,0,sizeof(vis));
	for(auto z:ans) cout<<z<<endl,vis[z]=1;
	for(int i=1;i<=n;i++)
		if(!vis[i]) cout<<i<<endl; 
	return 0;
}
```

---

## 作者：Fujxxx (赞：1)

把奶牛视作左部节点，麦片视作右部节点，先不考虑最喜欢和次喜欢，直接建立二分图。

那么第一问的答案就是未匹配的奶牛数。

求最大匹配时，若使用匈牙利算法，时间复杂度为 $O(nm)$。若转化为网络流，使用 Dinic 算法，时间复杂度为 $O(m\sqrt{n})$。

对于操作序列，考虑其限制条件。发现只有选到次喜欢的奶牛有限制，需要在其最喜欢麦片对应奶牛的后面出现，建图拓扑即可，时间复杂度 $O(n)$。

于是本题得解，时间复杂度瓶颈在二分图最大匹配。

按本题数据范围，匈牙利算法应不能通过本题，但如果有常数较小的实现，在实际测试数据下也可以通过。

下面是参考代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
int n,m,ans,tot,f[N],s[N],row[N],in[N];
vector<int> edge[N],e[N];
int mat[N],to[N];
bool vis[N];
bool dfs(int u){
	for(int v: edge[u]){
		if(vis[v]) continue;
		vis[v]=1;
		if(!mat[v]||dfs(mat[v])){
			to[u]=v;
			mat[v]=u;
			return true;
		}
	}return false;
}
void topo(int u){
	row[++tot]=u;
	for(int i: e[u]) topo(i);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		f[i]=read();
		s[i]=read();
		edge[i].push_back(f[i]+n);
		edge[i].push_back(s[i]+n);
	}
	for(int i=1;i<=n;i++) dfs(i),memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) if(!to[i]) ans++;
	cout<<ans<<'\n';
	for(int i=1;i<=n;i++) if(to[i]-n==s[i]) e[mat[f[i]+n]].push_back(i),in[i]++;	
	for(int i=1;i<=n;i++) if(in[i]==0) topo(i);
	for(int i=1;i<=tot;i++) cout<<row[i]<<'\n';
	return 0;
}
/*
8 10
2 1
3 4
2 3
6 5
7 8
6 7
7 5
5 8

*/
```

---

## 作者：Alvintsh (赞：1)

# 贪心 + 拓扑
可以轻松的发现这是一道最大匹配的问题， 那第一个想法就是匈牙利算法。但是这道题的数据范围是 $10^{5}$ 但是匈牙利的时间复杂度是 $O(nm)$, 很明显是会爆时的。 
### 找麦片-奶牛的匹配
1. **建图** 可以把奶牛和食物分别看作一个节点， 在奶牛和它的首选和次选麦片之间建边。我是用的是链式前向星， 再开一个数组存储每个麦片的优先级  

2. **贪心** 我们可以发现一个奶牛和麦片的连通块有三种情况 —— 奶牛 > 麦片， 奶牛 = 麦片， 奶牛 < 麦片(当然是指数量）
- 奶牛 < 麦片： 对于这种情况，不难发现最多多出一个麦片， 我们需要确保只有一个麦片是没有匹配的
- 奶牛 >= 麦片：这种情况下，我们需要确保每一个麦片都能有对应的奶牛    

	那么贪心策略就是找到每一个麦片有多少个奶牛可以选择(度数)，优先把度数最小的麦片匹配一个可行的奶牛， 这样就可以确保麦片没有浪费。这种情况就用小根堆优化。时间复杂度是$O((n+m)logn)$    

3. **拓扑** 我们有了每个奶牛匹配的麦片，但怎么输出顺序呢？我们就可以通过匹配得到奶牛之间的优先关系再建一个图，把这个图的拓扑顺序输出即可。我们可以发现如果一个奶牛占了它的次选，那么它一定在占了它的首选的奶牛之后； 如果一个奶牛没有匹配，那么它就在占了它的两个选择的奶牛之后。 这时就会发现一个问题，这个顺序图可能出现环，拓扑序就输出不了了。所以要在贪心时加上一步：如果麦片可以对应一个奶牛的首选，就优先匹配首选，避免环的出现
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N2 = 110, N3 = 1110, N4 = 1e4 + 10, N5 = 1e5 + 10, N6 = 1e6 + 10;
typedef pair <int, int> PII;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
const int N = 5 * 1e5;
const int INF = 1e5;
int n, m;
int h[N], e[N], ne[N], idx, pr[N], d[N], st[N], match[N];
int first[N], value[N], nex[N], id, duu[N];
//结构体存麦片序号和度数
struct Node
{
    int in, du;
    bool operator> (const Node &a) const{
        return du > a.du;
    }
};
void add(int a, int b, int st){
    idx++, e[idx] = b, pr[idx] = st, ne[idx] = h[a], h[a] = idx;
}
void addtop(int a, int b){
    id++, value[id] = b, nex[id] = first[a], first[a] = id;
}
void topsort(){
    //拓扑
    queue<int> q;
    for (int i = 1; i <= n;i++)
        if (duu[i] == 0)
            q.push(i);
    while(!q.empty()){
        int j = q.front();
        cout << j << endl;
        q.pop();
        for (int i = first[j]; i; i = nex[i])
        {
            int p = value[i];
            duu[p]--;
            if (!duu[p])
                q.push(p);
        }
    }
    for (int i = 1; i <= n; i++)
        if (duu[i])
            cout << i << endl;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        int f, s;
        cin >> f >> s;
        //存边：麦片就是原编号 + 1e5
        add(i, s + 1e5, 2), add(i, f + 1e5, 1);
        add(s + 1e5, i, 2), add(f + 1e5, i, 1);
        d[f + INF]++, d[s + INF]++;
    }
    //匹配
    priority_queue <Node, vector <Node>, greater <Node> > heap;
    for (int i = 1e5 + 1; i <= 1e5 + m; i++)
        if (d[i])
            heap.push({i, d[i]});
    while(!heap.empty()){
        Node j = heap.top();
        heap.pop();
        if (st[j.in])
            continue;
        if (j.du == 0)
        {
            st[j.in] = -1;
            continue;
        }
        //优先选择优先级高的
        int tar = h[j.in], pro = 3;
        for (int i = h[j.in]; i; i = ne[i])
            if (!match[e[i]] && pr[i] < pro)
                tar = i, pro = pr[i];
        
        match[e[tar]] = j.in, st[j.in] = e[tar];
        for (int i = h[e[tar]]; i; i = ne[i])
        {
            if (!st[e[i]]){
                d[e[i]]--;
                heap.push({e[i], d[e[i]]});
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n;i++){
        if (!match[i])
            cnt++;
    }
    cout << cnt << endl;
    
    for (int i = 1; i <= n; i++)
    {
        if (match[i]){
            int fi, si;
            for (int j = h[i]; j; j = ne[j])
                if (pr[j] == 2)
                    si = j;
                else
                    fi = j;
            if (match[i] == e[si] && st[e[fi]] != -1){
                addtop(st[e[fi]], i), duu[i]++;
            }
        }
        else
        {
            int fi, si;
            for (int j = h[i]; j; j = ne[j])
                if (pr[j] == 2)
                    si = j;
                else
                    fi = j;
            addtop(st[e[fi]], i), addtop(st[e[si]], i), duu[i] += 2;

        }
    }
    topsort();
    return 0;
}
```





---

## 作者：littleKtian (赞：1)

被这题搞了下心态。

------------

把每袋麦片看成点，每头奶牛的 $f_i$ 和 $s_i$ 看成两个点之间的连边，于是原题变成尽可能匹配多的点和边。

每个连通块单独分析。

- 构成图形为一棵树

任意设其中一个点为根，其余点直接和与父亲间的连边匹配即可。

由于 $f_i$ 和 $s_i$ 还有优先级关系，所以我们再枚举所有根的连边，如果某条边的 $f_i$ 为根，那么就将其的匹配点改为根，并将其原本的匹配点设为新的根。

不断递归这个过程，直到找不到这样的边为止。可以发现这个过程相当于从根往下走，所以一定会在搜到叶子时或之前停止。

- 构成图形不为一棵树

任取其中的一棵基环树，把环看成根。对于所有不在环上的边，将其与儿子节点匹配。

对于环上的点，我们任选一个方向按顺序匹配即可，但要注意如果此时环上的边都和其的 $s_i$ 匹配，那么就需要倒转方向匹配。

全部匹配完后根据匹配情况建立有向图（这时奶牛看成点），拓扑排序即可（可以发现此时建立出的图一定是无环的）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int lw[100005],bi[200005][3],bs=1,vi[100005];
int n,m,f[100005],s[100005],ans;
int p[100005],pxh[100005];
void add(int u,int v,int w){bi[++bs][0]=lw[u],bi[lw[u]=bs][1]=v,bi[bs][2]=w;}
int dl[100005],tzz,wzz;
int bxh[100005],it[100005],bn,dxh[100005],tn;
struct edge{
	int to,xh;
};
vector<edge> e[100005];int rd[100005];
int che;
void dfs1(int w,int fa)
{
	for(int i=0,in=e[w].size();i<in;i++)
	{
		edge x=e[w][i];int v=x.to,xh=x.xh;
		if(v!=fa)
		{
			p[abs(xh)]=v,dfs1(v,w);
		}
	}
}
int hxh[100005],hn,hb[100005];
int getans(int x)
{
	bn=0,tn=1;
	tzz=0,dl[wzz=1]=x,vi[x]=1;
	while(tzz<wzz)
	{
		++tzz;int u=dl[tzz];
		for(int o_o=lw[u];o_o;o_o=bi[o_o][0])
		{
			int v=bi[o_o][1];
			if(bi[o_o][2]>0)bxh[++bn]=o_o>>1;
			if(!vi[v])it[o_o>>1]=1,dl[++wzz]=v,vi[v]=1,++tn;
		}
	}
	for(int i=1;i<=bn;i++)if(it[bxh[i]])
	{
		int xh=bxh[i],u=bi[(xh<<1)|1][1],v=bi[xh<<1][1],w=bi[xh<<1][2];
		e[u].push_back((edge){v,w}),e[v].push_back((edge){u,-w}),++rd[u],++rd[v];
	}
	if(bn==tn-1)
	{
		dfs1(x,0);
		int rt=x,fa=0;
		for(;;)
		{
			int jg=0;
			for(int i=0,in=e[rt].size();i<in;i++)
			{
				edge b=e[rt][i];int so=b.to,xh=b.xh;
				if(so!=fa&&xh>0)
				{
					jg=1,p[xh]=rt,fa=rt,rt=so;
					break;
				}
			}
			if(!jg)break;
		}
		return 0;
	}
	else
	{
		int tb=0;
		for(int i=1;i<=bn;i++)if(!it[bxh[i]])
		{
			int xh=bxh[i],u=bi[(xh<<1)|1][1],v=bi[xh<<1][1],w=bi[xh<<1][2];
			e[u].push_back((edge){v,w}),e[v].push_back((edge){u,-w}),++rd[u],++rd[v];
			tb=xh;break;
		}
		for(int i=1;i<=tn;i++)dxh[i]=dl[i];
		tzz=wzz=0;
		for(int i=1;i<=tn;i++)if(rd[dxh[i]]==1)dl[++wzz]=dxh[i];
		while(tzz<wzz)
		{
			++tzz;int u=dl[tzz];
			for(int i=0,in=e[u].size();i<in;i++)
			{
				edge b=e[u][i];int v=b.to,xh=b.xh;
				if(rd[v]!=0)
				{
					p[abs(xh)]=u,--rd[u],--rd[v];
					if(rd[v]==1)dl[++wzz]=v;
				}
			}
		}
		hn=0;
		for(int i=1;i<=tn;i++)if(rd[dxh[i]]!=0)
		{
			hxh[hn=1]=dxh[i];
			int w=dxh[i];
			do
			{
				for(int j=0,jn=e[w].size();j<jn;j++)
				{
					edge b=e[w][j];int v=b.to,xh=b.xh;
					if(rd[v]&&xh!=-hb[hn-1])
					{
						hb[hn]=xh,hxh[++hn]=v,w=v;
						break;
					}
				}
			}while(w!=dxh[i]);
			break;
		}
		--hn,che=0;
		for(int i=1;i<=hn;i++)if(hb[i]>0){che=1;break;}
		if(che)
		{
			for(int i=1;i<=hn;i++)p[abs(hb[i])]=hxh[i];
		}
		else
		{
			for(int i=1;i<=hn;i++)p[abs(hb[i])]=hxh[i+1];
		}
		return bn-tn;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",f+i,s+i);
		add(f[i],s[i],i),add(s[i],f[i],-i);
	}
	for(int i=1;i<=m;i++)if(!vi[i])ans+=getans(i);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)if(p[i])pxh[p[i]]=i;
	for(int i=1;i<=n;i++)e[i].clear(),rd[i]=0;
	for(int i=1;i<=n;i++)
	if(p[i])
	{
		if(p[i]==s[i])
		{
			int u=pxh[f[i]],v=i;
			e[u].push_back((edge){v,0}),++rd[v];
		}
	}
	else
	{
		int u1=pxh[f[i]],u2=pxh[s[i]],v=i;
		e[u1].push_back((edge){v,0}),++rd[v];
		e[u2].push_back((edge){v,0}),++rd[v];
	}
	tzz=wzz=0;
	for(int i=1;i<=n;i++)if(rd[i]==0)dl[++wzz]=i;
	while(tzz<wzz)
	{
		++tzz;int u=dl[tzz];
		printf("%d\n",u);
		for(int i=0,in=e[u].size();i<in;i++)
		{
			int v=e[u][i].to;
			--rd[v];
			if(rd[v]==0)dl[++wzz]=v;
		}
	}
}
```


---

## 作者：liugh_ (赞：0)

一眼最大流。

注意到一个问题：牛会先选第一喜欢，若第一喜欢已经被选才会选第二喜欢，而这如何在最大流中体现？

实际上，我们无需考虑这个问题。记牛 $i$ 的第一第二喜欢分别为 $x_i,y_i$。
- 若牛 $i$ 匹配 $x_i$，显然正确。
- 若牛 $i$ 匹配 $y_i$，
  - 若 $x_i$ 未被匹配，显然能改为匹配 $x_i$。
  - 若 $x_i$ 已被匹配，我们需要先考虑匹配 $x_i$ 的牛 $j$，
    - 若牛 $j$ 匹配 $x_j=x_i$，显然正确。
    - 若牛 $j$ 匹配 $y_j=x_i$，转化为原问题。注意到可能出现无限递归，即进入一个搜索环，显然我们可以将环上所有点的匹配都改成其第一喜欢。

实现上，仅需为所有点记一个数组 $vis$，从每个 $vis_u=0$ 的点 $u$ 开始搜索，每搜到一个点 $i$，令 $vis_i\gets 1$，若匹配第一喜欢或匹配点的 $vis$ 为 $1$ 则回溯。

时间 $\Theta(n+m\sqrt{n})$。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cassert>
#include<set>
#include<map>
#if defined FIO
auto FI=freopen("1.in","r",stdin);
auto FO=freopen("1.out","w",stdout);
#endif
#if defined BUG
#define bug(x...) ({x;({});})
#else
#define bug(x...) ({})
#endif
using namespace std;
// static char _b[1<<20],*_h,*_t;
// #define getchar() (_h==_t&&(_t=(_h=_b)+fread(_b,1,1<<20,stdin),_h==_t)?EOF:*_h++)
// constexpr static void fin(auto&x){signed c=0,f=0;do if(c==45)f=1;while(c=getchar(),c<48||c>57);x=0;do x=(x<<1)+(x<<3)+(c^48);while(c=getchar(),c>=48&&c<=57);if(f)x=-x;}
// constexpr static void fot(auto x){signed d[40],l=-1;if(x<0)x=-x,putchar(45);do d[++l]=(x%10)^48;while(x/=10);do putchar(d[l]);while(~--l);putchar(32);}
#define LL  long long
#define pb  push_back
#define fi  first
#define se  second
#define vec vector
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define tomin(x,y) (x=min(x,y))
#define tomax(x,y) (x=max(x,y))
#define rep(i,l,r) for(decay<decltype(r)>::type i=(l),i##END=(r);i<=i##END;i++)
#define per(i,l,r) for(decay<decltype(r)>::type i=(l),i##END=(r);i>=i##END;i--)

constexpr int maxn=2e5+10,maxm=4e5+10,inf=0x3f3f3f3f;
int n1,n2,n;
int L[maxn],R[maxn];
pii a[maxn];
struct _eg{int pre,v,c;}eg[maxm*2];int ei=1,eh[maxn];
void ea(int u,int v,int c){eg[++ei]={eh[u],v,c};eh[u]=ei;}
void ef(int u,int v,int c){ea(u,v,c),ea(v,u,0);}
int dis[maxn],vis[maxn],cur[maxn],S,T;
bool spfa(){
    fill(dis+1,dis+1+T,inf),fill(vis+1,vis+1+T,0),dis[S]=0;
    for(deque<int> q{S};q.size();){
        int u=q.front();q.pop_front();vis[u]=0;
        for(int e=eh[u];e;e=eg[e].pre)
            if(auto [_,v,c]=eg[e];c>0&&dis[u]+1<dis[v])
                if(dis[v]=dis[u]+1;!vis[v])vis[v]=1,q.pb(v);
    }return dis[T]!=inf;
}
int dfs(int u,int fl){
    if(u==T)return fl;vis[u]=1;
    int sm=0;for(int&e=cur[u];e;e=eg[e].pre)if(auto [_,v,c]=eg[e];!vis[v]&&c>0&&dis[u]+1==dis[v]){
        int cn=dfs(v,min(fl,c));if(cn==0){dis[v]=inf;continue;}
        if(eg[e].c-=cn,eg[e^1].c+=cn,fl-=cn,sm+=cn;fl==0)break;
    }vis[u]=0;return sm;
}
int dinic(){int res=0;while(spfa()){copy(eh,eh+1+T,cur),fill(vis,vis+1+T,0),res+=dfs(S,inf);}return res;}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // signed CSE;cin>>CSE>>ws;while(CSE--)
[&](){
    cin>>n1>>n2;n=n1+n2,S=n+1,T=S+1;
    rep(i,1,n1){
        cin>>a[i].fi>>a[i].se;
        ef(i,n1+a[i].fi,1),ef(i,n1+a[i].se,1),ef(S,i,1);
    }
    rep(i,1,n2)ef(n1+i,T,1);
    cout<<n1-dinic()<<'\n';
    for(int e=3;e<=ei;e+=2)if(eg[e].v<=n1 and eg[e].c){
        L[eg[e^1].v-n1]=eg[e].v;
        R[eg[e].v]=eg[e^1].v-n1;
    }
    fill(vis,vis+1+T,0);
    auto out=[&](auto&&out,int i)->void{
        if(i==0 or vis[i])return;
        vis[i]=1;
        if(R[i]==a[i].se)out(out,L[a[i].fi]);
        cout<<i<<'\n';
    };
    rep(i,1,n1)out(out,i);
}();
}
```

---

## 作者：qwer6 (赞：0)

## Description

有 $n$ 头奶牛，$m$ 种麦片，每头奶牛都有第一喜欢的麦片 $fi$ 和第二喜欢的麦片 $se$，每种麦片只有一箱，当轮到一头奶牛拿麦片的时候，如果 $fi$ 还没有被拿走，那么它就会拿走 $fi$，否则，如果 $se$ 还没有被拿走，那么它就会拿走 $se$，不然这头奶牛就会饥饿。

求当最优排列所有奶牛的时候，饥饿的奶牛最小值并输出一种可能方案。

数据保证 $1\le n\le 10^5,2\le m\le 10^5,fi_i,se_i\le m,fi_i\ne se_i$。

## Solution

~~点开标签知解法。~~

我们发现这道题拿到手之后并没有什么头绪，麦片的种类十分多，显然不可能状压了，贪心看上去似乎也不可行，所以我们考虑一些其他方式求解。

不能动态规划或者贪心，那我们不妨考虑转换为图论问题，由于一头奶牛如果可以吃到麦片，那么要么吃 $fi_i$，要么吃 $se_i$，所以这里只需要在 $fi_i$ 和 $se_i$ 之间连上无向边，然后尝试在图上求解。

样例明示对于不同联通块分开求解，这是显然的，因为当两组奶牛的喜欢的麦片完全没有重合的时候，两组奶牛的顺序不会对另一组产生任何影响。

对于一个联通块，假设点数，也就是涉及的麦片数为 $node$，边数，也就是包含的奶牛数为 $edge$，我们可以得到一个结论 $node\in[2,edge+1]$，其中最小值是所有边的端点完全重合，最大值是所有边和点成为一棵树。

这里需要分类讨论，是一棵树和不是一棵树的情况。

第一种情况，这个联通块是一棵树。

我们显然可以知道这个联通块中的所有奶牛都可以被满足，构造方式如下：随意选定一个点作为根，然后按照 dfs 顺序记录边的序号。

考虑证明这样做的正确性：对于一棵树的根节点延伸出去的边，如果这条边吃的是根这个点对应的点，那么去掉根之后又是若干个形式相同的子问题，直接递归即可，如果这条边吃的是除了根之外的另一个点，那么对应的子树就会被分成若干个形式相同的子问题，直接递归即可。

第二种情况，这个联通块不是一棵树。

我们知道这个联通块中的可以满足 $node$ 头奶牛，构造方式如下：跑出一棵生成树，然后随意选定一条非树边，将这条非树边对应的 $fi$ 作为根，先记录这条边的序号，然后按照树的方式构造即可。

考虑证明这样做的正确性：由于这条非树边先输出，所以 $fi$ 这个点已经被吃掉，所以生成树相当于被分成若干棵子树，可以直接按照树的情况构造，每一头奶牛吃的都是对应边的儿子节点。

## 3.Code

这里给出一个代码示例。

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=1e5+5;
int n,m,cnt_block,Ans;
int fi[N],se[N],cnt_edge[N],cnt_node[N],ans[N];
bool vis_block[N],vis_tree[N],vis_edge[N];
struct Edge{
	int v,idx;
};
vector<Edge>e[N];
void bfs(int s){
	queue<int>q;
	q.push(s);
	vis_block[s]=1;
	cnt_node[cnt_block]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(Edge tmp:e[u]){
			int v=tmp.v;
			cnt_edge[cnt_block]++;
			if(vis_block[v])continue;
			vis_block[v]=1;
			cnt_node[cnt_block]++;
			q.push(v);
		}
	}
}
void dfs(int u){
	vis_tree[u]=1;
	for(Edge tmp:e[u]){
		int v=tmp.v,idx=tmp.idx;
		if(vis_edge[idx])continue;
		if(vis_tree[v])continue;
		vis_tree[v]=1;
		vis_edge[idx]=1;
		ans[++ans[0]]=idx;
		dfs(v);
	}
}
struct Tree{
	int Not_tree;
	int fa[N];
	bool mark[N],tree[N];
	vector<int>edge;
	void init_dfs(int u){
		mark[u]=1;
		for(Edge tmp:e[u]){
			int v=tmp.v,idx=tmp.idx;
			edge.push_back(idx);
			if(mark[v])continue;
			tree[idx]=1;
			fa[v]=u;
			init_dfs(v);
		}
	}
	void solve(int Rt){
		edge.clear();
		init_dfs(Rt);
		for(int x:edge){
			if(tree[x])continue;
			Not_tree=x;
			break;
		}
		ans[++ans[0]]=Not_tree;
		vis_edge[Not_tree]=1;
		dfs(fi[Not_tree]);
	}
}tree;
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(fi[i]),read(se[i]);
		e[fi[i]].push_back({se[i],i});
		e[se[i]].push_back({fi[i],i});
	}
	for(int i=1,node,edge;i<=m;i++){
		if(vis_block[i])continue;
		cnt_block++;
		bfs(i);
		cnt_edge[cnt_block]>>=1;
		node=cnt_node[cnt_block],edge=cnt_edge[cnt_block];
		if(!edge)continue;
		if(node==edge+1)dfs(i);
		else{
			Ans+=(edge-node);
			tree.solve(i);
		}
	}
	write(Ans),Nxt;
	for(int i=1;i<=ans[0];i++)write(ans[i]),Nxt;
	for(int i=1;i<=n;i++){
		if(vis_edge[i])continue;
		write(i),Nxt;
	}
}
```

附这道题一个可行的 spj 程序。

```c++
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	int write_top,read_f,read_x;
	char read_char;
	int write_st[20];
	inline int read(int &a){
		read_char=getchar();
		read_f=1;
		a=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			a=(a<<1)+(a<<3)+(read_char^48);
			read_char=getchar();
		}
		return a=a*read_f;
	}
	inline int read(){
		read_char=getchar();
		read_f=1;
		read_x=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			read_x=(read_x<<1)+(read_x<<3)+(read_char^48);
			read_char=getchar();
		}
		return read_x*read_f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		write_top=0;
		do{
		   write_st[++write_top]=x%10;
		   x/=10;
		}while(x);
		while(write_top)putchar(write_st[write_top--]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e5+5;
int n,m,ans1,ans2;
int fi[N],se[N];
bool vis[N],mark[N];
signed main(){
	ifstream Myans("1.txt");
	ifstream Correct("2.txt");
	ifstream input("in.txt");
	Myans>>ans1;
	Correct>>ans2;
	if(ans1!=ans2){
		puts("The minimum of hungry cows is wrong!");
		return 1;
	}
	input>>n>>m;
	for(int i=1;i<=n;i++)input>>fi[i]>>se[i];
	int res=0,x;
	while(Myans>>x){
		if(x==0||x>n){
			puts("The wrong cows numbering!");
			return 1;
		}
		if(mark[x]){
			puts("The same cows!");
			return 1;
		}
		mark[x]=1;
		if(vis[fi[x]]&&vis[se[x]])res++;
		else if(vis[fi[x]])vis[se[x]]=1;
		else vis[fi[x]]=1;
	}	
	if(res!=ans1){
		puts("Wrong sorting!the actual number of hungry cows isn't correct!");
		return 1;
	}
	return 0;
	
}
```

---

## 作者：jia_shengyuan (赞：0)

如果每头牛的喜好不分先后，那么这就是个裸的二分图最大匹配，每头牛向喜欢的麦片连边然后流一下就行了。

现在为了让牛优先选择自己最喜欢的，我们给边加费用。第一喜欢的费用为 $0$，第二喜欢的费用为 $1$，这样就不用怕牛在能选最喜欢的麦片的情况下去选第二喜欢的了。

输出方案可以用类似拓扑排序的方式，先把吃到最喜欢麦片的都输出了，对于吃第二喜欢麦片的牛，则要等到它最喜欢的麦片被吃了之后再输出。最后，再输出没得吃的牛。

```cpp
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <queue>

const int maxn = 2e5+9, maxm = maxn<<3;
using namespace std;

struct edge {
    int to,next,flow,cost;
}edges[maxm];

int head[maxn],chead[maxn],dep[maxn],match[maxn],n,m,s,t;
int a[maxn],b[maxn];
bool vis[maxn],printed[maxn],inq[maxn];
vector<int> want[maxn];
queue<int> q;

inline void AddEdge(int u, int v, int f, int c){
    static int tot = 1;
    edges[++tot] = {v,head[u],f,c};
    head[u] = tot;
    edges[++tot] = {u,head[v],0,-c};
    head[v] = tot;
}
void Read(){
    scanf("%d%d",&n,&m);
    s=n+m+1;
    t=s+1;
    for(int i=1; i<=n; i++){
        scanf("%d%d",&a[i],&b[i]);
        want[a[i]].push_back(i);
        want[b[i]].push_back(i);
        AddEdge(s,i,1,0);
        AddEdge(i,n+b[i],1,1);
        AddEdge(i,n+a[i],1,0);
    }
    for(int i=1; i<=m; i++) AddEdge(n+i,t,1,0);
}

bool SPFA(){
    memset(dep,0x7f,sizeof(dep)); dep[s]=0;
    memset(inq,0,sizeof(inq));
    q.push(s);
    while(!q.empty()){
        int now = q.front(); q.pop();
        inq[now] = false;
        chead[now] = head[now];
        for(int i=head[now],to; i; i=edges[i].next){
            if(!edges[i].flow) continue;
            if(dep[now]+edges[i].cost < dep[to=edges[i].to]){
                dep[to] = dep[now]+edges[i].cost;
                if(!inq[to]){
                    q.push(to);
                    inq[to] = true;
                }
            }
        }
    }
    return dep[t]!=dep[0];
}
int Dinic(int now, int in){
    if(now == t) return in;
    int out=0,cur;
    inq[now] = true;
    for(int i=chead[now],to; i&&in; i=edges[i].next){
        chead[now] = i;
        if(!edges[i].flow || inq[to=edges[i].to]) continue;
        if(dep[to] != dep[now]+edges[i].cost) continue;
        cur = Dinic(to,min(in,edges[i].flow));
        in -= cur;
        edges[i].flow -= cur;
        out += cur;
        edges[i^1].flow += cur;
    }
    if(out) inq[now] = false;
    return out;
}

inline void FindMatch(int now){
    for(int i=head[now],to; i; i=edges[i].next){
        to = edges[i].to-n;
        if(to > m) continue;
        if(!edges[i].flow) {
            match[now] = to;
            return;
        }
    }
}
void Dfs(int now){
    printf("%d\n",now);
    vis[match[now]] = 1;
    printed[now] = 1;
    for(int cow : want[match[now]]){
        if(printed[cow] || !match[cow]) continue;
        if(vis[a[cow]]) Dfs(cow);
    }
}

int main(){
    Read();
    int cnt = n;
    while(SPFA()) cnt -= Dinic(s,INT_MAX); 
    printf("%d\n",cnt);
    for(int i=1; i<=n; i++) FindMatch(i);
    for(int i=1; i<=n; i++){
        if(match[i] == a[i]) { //吃到最喜欢的
            printf("%d\n",i);
            printed[i] = true;
            vis[a[i]] = true;
        }
    }
    for(int i=1; i<=n; i++){
        if(!match[i] || printed[i]) continue;
        if(vis[a[i]]) Dfs(i); //最喜欢的已经被吃了
    }
    for(int i=1; i<=n; i++){
        if(!printed[i]) printf("%d\n",i);
    }
    return 0;
}
```


---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/P8095)

## 题目分析

二分图+拓扑排序。

牛和麦片分别为二分图的两部分，第一问即为求二分图最大匹配。

理论上匈牙利算法复杂度为 $O(nm)$，而 `Dinic` 在二分图中复杂度为 $O(m\sqrt{n})$。但由于某种未知原因，本题匈牙利跑得比 `Dinic` 快。

笔者不会匈牙利，于是使用了 `Dinic`。

直接无脑最大流会发现，两种喜欢的麦片没有区别。因此我们对牛指向麦片的边加上边权，使优先级出现差异，然后改用费用流求解即可。

源点流向牛的流量，牛流向麦片的流量和麦片流向汇点的流量均为 $1$。

对于第二问，注意到若牛取走某个麦片，那么连接牛与麦片的剩余流量为 $0$。

因此可以通过遍历边来判断麦片被哪头牛取走，然后建立牛排队顺序的拓扑关系。

对于牛 `A`，若最喜欢的麦片被牛 `B` 取走，则 `B` 在 `A` 前面。若同时次喜欢的麦片被 `C` 取走，则 `C` 也在 `A` 前面。

按照上述关系建立新图并拓扑排序，即可得到合法序列。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1500010
using namespace std;
typedef long long ll;
const int inf = 1e9;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, m, st, ed, head[N], edge_cnt = 1, ans, Head[N], Edge = 1, a[N][2], bel[N], que[N], he = 1, tot, dis[N], cur[N], in[N], vis[N], incf[N], pre[N];
struct edge {int nxt, v, w, c;} e[N], E[N];

inline void add_edge(int u, int v, int w, int c) {e[++edge_cnt].nxt = head[u]; head[u] = edge_cnt; e[edge_cnt].v = v; e[edge_cnt].w = w; e[edge_cnt].c = c;}
inline void Add(int u, int v) {E[++Edge].nxt = Head[u]; Head[u] = Edge; E[Edge].v = v;}

inline bool SPFA()
{
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[st] = 0; q.push(st); vis[st] = 1; incf[st] = inf;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        vis[u] = 0;
        cur[u] = head[u];
        for (rei i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            if (dis[u] + e[i].c < dis[v] && e[i].w)
            {
                dis[v] = dis[u] + e[i].c;
                incf[v] = min(incf[u], e[i].w);
                pre[v] = i;
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return dis[ed] != 1061109567;
}

inline int Dfs(int u, int flow)
{
	if (u == ed) return flow;
	int rest = flow;
	vis[u] = 1;
	for (rei i = cur[u]; i; i = e[i].nxt)
	{
		int v = e[i].v; cur[u] = i;
		if (dis[v] == dis[u] + e[i].c && e[i].w && !vis[v])
		{
			int tmp = Dfs(v, min(rest, e[i].w));
			e[i].w -= tmp;
			e[i ^ 1].w += tmp;
			rest -= tmp;
			if (!rest) break;
		}
	}
	return flow - rest;
}

inline int Dinic()
{
	int ret = 0;
	while (SPFA()) ret += Dfs(st, inf);
	return ret;
}

inline void Toposort()
{
	for (rei i = 1; i <= n; i++)
		if (!in[i]) que[++tot] = i, vis[i] = 1;
	while (he <= tot)
	{
		int u = que[he++];
		for (rei i = Head[u]; i; i = E[i].nxt)
		{
			int v = E[i].v;
			--in[v];
			if (!in[v]) que[++tot] = v, vis[v] = 1;
		}
	}
}

int main()
{
	read(n); read(m); ed = n + m + 1;
	for (rei i = 1; i <= n; i++)
	{
		int x, y; read(x); read(y);
		a[i][0] = x; a[i][1] = y;
		add_edge(i, y + n, 1, 1); add_edge(y + n, i, 0, -1);
		add_edge(i, x + n, 1, 0); add_edge(x + n, i, 0, 0);
	}
	for (rei i = 1; i <= n; i++) add_edge(st, i, 1, 0), add_edge(i, st, 0, 0);
	for (rei i = 1; i <= m; i++) add_edge(i + n, ed, 1, 0), add_edge(ed, i + n, 0, 0); 
	ans = Dinic(); printf("%d\n", n - ans); 
	for (rei i = 1; i <= n; i++) // 麦片被哪只牛拿走 
	{
		for (rei j = head[i]; j; j = e[j].nxt)
		{
			int v = e[j].v;
			if (v <= n || v > m + n) continue;
			if (!e[j].w) bel[v - n] = i;
		}
	}
	for (rei i = 1; i <= n; i++)
	{
		if (bel[a[i][0]] != i && bel[a[i][0]]) Add(bel[a[i][0]], i), ++in[i];  // 最喜欢的被拿了 
		if (bel[a[i][1]] && bel[a[i][1]] != i && bel[a[i][0]] != i) Add(bel[a[i][1]], i), ++in[i]; // 都被拿了 
		if (bel[a[i][0]] == i && bel[a[i][1]] && bel[a[i][1]] != i && a[bel[a[i][1]]][0] != a[i][1]) Add(i, bel[a[i][1]]), ++in[bel[a[i][1]]]; // 第二喜欢被拿但拿到最喜欢的 
	}
	Toposort();
	for (rei i = 1; i <= tot; i++) printf("%d\n", que[i]);
	return 0;
}
```


---

