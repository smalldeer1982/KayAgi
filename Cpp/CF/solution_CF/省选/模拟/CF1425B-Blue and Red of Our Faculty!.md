# Blue and Red of Our Faculty!

## 题目描述

It's our faculty's 34th anniversary! To celebrate this great event, the Faculty of Computer Science, University of Indonesia (Fasilkom), held CPC - Coloring Pavements Competition. The gist of CPC is two players color the predetermined routes of Fasilkom in Blue and Red. There are $ N $ Checkpoints and $ M $ undirected predetermined routes. Routes $ i $ connects checkpoint $ U_i $ and $ V_i $ , for $ (1 \le i \le M) $ . It is guaranteed that any pair of checkpoints are connected by using one or more routes.

The rules of CPC is as follows:

- Two players play in each round. One player plays as blue, the other plays as red. For simplicity, let's call these players $ Blue $ and $ Red $ .
- $ Blue $ will color every route in he walks on blue, $ Red $ will color the route he walks on red. Both players start at checkpoint number $ 1 $ . Initially, all routes are gray.
- Each phase, from their current checkpoint, $ Blue $ and $ Red $ select a different gray route and moves to the checkpoint on the other end of the route simultaneously.
- The game ends when $ Blue $ or $ Red $ can no longer move. That is, there is no two distinct gray routes they can choose to continue moving.

Chaneka is interested in participating. However, she does not want to waste much energy. So, She is only interested in the number of final configurations of the routes after each round. Turns out, counting this is also exhausting, so Chaneka asks you to figure this out!

Two final configurations are considered different if there is a route $ U $ in a different color in the two configurations.

## 说明/提示

Every possible final configuration for the example is listed below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1425B/ebea898d61825b68e5285a648bb127c44df665b0.png)The blue-colored numbers give the series of moves $ Blue $ took, and the red-colored numbers give the series of moves $ Red $ took.

## 样例 #1

### 输入

```
5 6
1 2
2 3
3 4
4 1
1 5
5 1```

### 输出

```
8```

# 题解

## 作者：duyi (赞：3)

[噜啦噜啦咧噜啦噜啦咧的阅读体验！！！](https://www.cnblogs.com/dysyn1314/)


# CF1425B Blue and Red of Our Faculty!


## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1425/B)

给定一张 $n$ 个点 $m$ 条边的无向连通图，保证无自环，**保证除节点 $1$ 外每个点的度数都为 $2$**。

有两人 Red 和 Blue 同时从节点 $1$ 出发。初始时所有边都是灰色。Red 每经过一条边就会将它染成红色，Blue 每经过一条边就会将它染成蓝色。每轮中，每人会选择一条与当前所在节点相连的、灰色的边，并走到边的另一端。同一轮里两人选择的边**不能相同**。

当无法进行下一轮时，整个过程停止。问两人能走出多少种不同的最终局面，答案对 $10^9 + 7$ 取模。两个最终局面不同当且仅当存在一条边，在最终局面下颜色不同。

数据范围：$1\leq n\leq 2000$，$1\leq m\leq 2n$。

## 本题题解

根据“保证除节点 $1$ 外每个点的度数都为 $2$”，可以发现整张图呈一个花瓣状。也就是有若干个环，节点 $1$ 是它们的公共点。我们可以用一个序列（或者说可重集）$\{a_1,a_2,\dots,a_k\}$ 来描述整张图，其中 $a_i$ 表示第 $i$ 个环的大小，$k$ 是环的数量。

考虑结束时两人的位置。可以分为三种情况：

1. 两人都在节点 $1$。此时他们一定经过了所有环（图中没有灰边），且步数相同。方案数就相当于把 $a$ 划分为两个集合，使他们和相等的方案数。
2. 两人都在某个环的某个节点上（不含节点 $1$）。设该环的大小为 $l$，在环上 Red 走了 $x$ ($1\leq x < l$) 步，则 Blue 走了 $l - x$ 步。两人的步数差为 $(l - x) - x = l - 2x$。问题相当于从 $a$ 除当前环外的部分里（即 $a\setminus\{l\}$），选出**两个互不相交的子集**，使他们的和之差为 $l - 2x$。
3. 两人都在某个环上，且相距为 $1$（隔着一条边）。此时又可以分为两种情况：
   - 两人都不在节点 $1$ 上（严格位于环上）。这与情况 2 类似，只不过此时两人的步数差为 $l - 1 - 2x$，且 $1\leq x\leq l - 2$。
   - 其中一人在节点 $1$ 上。此时 $x = 0$ 或 $x = l - 1$。除了两人的步数差为 $l - 1 - 2x$ 外，还需要保证其他环都被走过。也就是选出的两个子集的并为全集（全集，指：$a$ 除去一个 $l$ 外的其他所有元素，即 $a\setminus\{l\}$）。

这三种情况，都可以用同一个 DP 来计算。

先枚举 $l$，从 $a$ 中暂时删掉一个 $l$（如果是计算情况 $1$，则不必删除任何元素）。

设 $\text{dp}(i,j,\text{flag})$ 表示考虑了前 $i$ 个环，当前 【Red 走的步数】$-$【Blue 走的步数】等于 $j$。$\text{flag}$ 是个 $0/1$ 值，表示有没有两人都没走过的环。注意 $j$ 这里，把“朴素地记录两人步数分别是多少”，变成“记录两者之差”，是个设计状态的小套路（CSP2019 d2t1 也有用到）。这么做是因为我们最终只关心它们的差。

转移就考虑当前环，是被 Red 走，还是被 Blue 走，还是两人都不走：

$$
\begin{cases}
\text{dp}(i - 1, j, \text{flag}) \to \text{dp}(i, j + a_i, \text{flag})\\
\text{dp}(i - 1, j, \text{flag}) \to \text{dp}(i, j - a_i, \text{flag})\\
\text{dp}(i - 1, j, \text{flag}) \to \text{dp}(i, j, 0)
\end{cases}
$$
情况 1 的答案是 $\text{dp}(k, 0, 1)$。$k$ 是环的数量。

情况 2 的答案是 $\displaystyle 2\times \sum_{x = 1}^{l - 1}(\text{dp}(k - 1, l - 2x, 0) + \text{dp}(k - 1, l - 2x, 1))$。其中乘以 $2$ 是因为最后一个环，Red 可以从两个方向（顺时针 / 逆时针）之一开始走。

情况 3 的答案是 $\displaystyle 2\times \left(\sum_{x = 1}^{l - 2}\text{dp}(k - 1, l - 1 - 2x,0) + \sum_{x = 0}^{l - 1}\text{dp}(k - 1, l - 1 - 2x,1)\right)$。

一次 DP 的时间复杂度是 $\mathcal{O}(n^2)$。但是外层要枚举 $l$。虽然环的数量可能高达 $\mathcal{O}(n)$ 个，但由于 $\sum\text{环长} = \mathcal{O}(n)$，所以不同的环长 $l$ 只有 $\mathcal{O}(\sqrt{n})$ 种。暴力枚举 $l$ 再做 DP 的总时间复杂度 $\mathcal{O}(n^2\sqrt{n})$，可以通过本题。另有一些优化方法：

- 优化方法1：这是一个缺一背包的模型，所以可以用分治来优化，做到 $\mathcal{O}(n^2\log n)$。
- 优化方法2：仍然暴力枚举 $l$。不对可重集 $a$ 做 DP，而是把 $a$ 缩成若干个二元组 $(\text{元素},\text{出现次数})$，然后类似于做多重背包。单次 DP 的时间复杂度是 $\mathcal{O}(n\sqrt{n})$，总时间复杂度 $\mathcal{O}(n^2)$。

## 参考代码

[勇敢向前进，前进有奖品！！！](https://www.cnblogs.com/dysyn1314/)

---

## 作者：Qing_喵乖乖喵 (赞：3)

[原题链接](https://codeforces.ml/contest/1425/problem/B)

简要翻译：  
有一个连通图，A和B同时从点1出发，沿不同的路径前进。原本，图上的每一条边都是灰色的。A将经过的边涂成红色，B将经过的边涂成蓝色的。每个回合每个人只能走灰色的边。当某个回合中**不存在两条不同的灰色路径**来**同时**移动A和B时，游戏结束。试求**结束时，图上边的涂色情况有多少种**?只要有一条边颜色不同，就视为两种情况。特别的，**对图中除点1外的点，每一个点都有且只有两条边与之相连**。  
数据范围：     
$2\leq N\leq3e5$，$2\leq M\leq 2\times N$  
题解：  
(说是题解，其实更像是思考过程。**想直接看正解的可以下拉到我推导n个环的地方**)
   
显然，我们可以发现，图中**所有的环都只有点1一个公共点**，或者说，**这个图是由以且只以点1为公共点的环构成的**。  

~~边军训边想想了一整天，我决定打开cf看下标签~~  
**Divide and Conquer**  分治算法  
~~好吧没看懂~~  

首先，我们先求出环的数量与每个环中点的数量，复杂度为 $O(N)$ ，简单的遍历即可。  
当然，你也可以一边读入一边利用并查集确定除1外每个点的归属，然后直接统计，这样就省去了建图遍历的过程。  

染色部分只含有1个环时:
* 答案加 $2$ 。(红蓝互换)  

染色部分只含有2个环时:
* 若两个环大小不同，则终点会在较大环里，且由于大小不同，终点不会将环平分，所以终点在环上会有一个对称的位置。再加上红蓝互换，答案加 $4$ 
* 当然，记得加上含有一个环的情况。  
* 此时，总答案为8。这便是样例的情况。  
* 若两个环大小相同，则终点为1。若图上没有别的环了，则答案加 $2$ ，否则答案加 $0$ 。(因为终点为点1，但与点1相连的环还有其他的，可以继续移动)  

当含有3个环时，记这三个环的点数分别为 $a\leq b\leq c$ ：  
* 若 $a+b=c$ ，与上面2个环的情况类似， 当终点在1时，如果只有3个环，答案加 $2$ ，否则答案加 $0$ 。当终点在c上时，若 $a=b$ ，答案加 $2$ ，否则加 $4$ 。  
* 否则若 $a+b<c$ ，显然终点只能出现在第三个环里。当两个小环颜色相同，与两个环的第一种情况同理，答案加 $4$ ；当两个小环颜色不同，若这两个环大小相同，则终点平分第三个环，答案加 $2$ ，否则，答案加 $4$ 。  
* 若 $a+b>c$ ：  
  * 若 $a=b$ ，答案加 $2(终点在c)+4(终点在b)+4(终点在a)$  
  * 若 $a<b$ ，答案加 $4+4+4$    
* 不难发现：当终点所在环两侧环的点数相同时，答案加 $2$ ，否则答案加 $4$   

对于含有n个环的情况下，记这n个环点数分别为 $a_1\leq a_2\leq ...\leq a_n$  
* 我们将这些环分为3个部分，$S_1,S_2,a_k$ ，注意 $S_1,S_2$ 可以为0，我们记终点在 $a_k$ 中，且 $S_1\leq S_2$ ，则 $a_k$ 可以作为终点环，当且仅当 $S_1+a_k>S_2$ 。  
* 若 $S_1=S_2$ ，答案加 $2$ 。否则，答案加 $4$ 。
* 但是，这样的组合会有很多种，枚举显然不能解决问题。
* 若 $S_1+a_k=S_2$ ，且没有更多的环时，答案加 $2$ ，否则答案加 $0$  。

假定我们已经求出n-1个环下的答案，现在让我们尝试推导出n个环的答案  
思路1：
* 对于原有的每个对答案有贡献的情形：
* 注意，此处我们将  $S_1+a_k=S_2$ 的情形也加入讨论
* 假若我们是按大小顺序加入环，对于每个 $S_1+a_k>S_2$ 的情形，如果我们把 $a_k$ 并入 $S_1$ ，新环设为终点环，情况仍然是合法的，即满足 $S_2+a_n>(S_1+a_k)$
* 对于 $a_n<S_2-S_1+a_k$ 的情形，我们将新环并入 $S_1$ 后，有 $S_2+a_k>(S_1+a_n)$ ，情况仍然合法  
* ...
* 下面不再列举出各种情况。但是，我们不难发现，如果我们维护的是各个 $d=S_2-S_1+a_k$ 的数量，在某些情形下，合并后，我们就无法利用 $d$ 计算出 $d'$ ，进而无法更新。如果维护 $d=S_1-S_2+a_k$ ，也有类似的问题。
* 比方说，我们维护的是 $d=S_2-S_1+a_k$ ，对于每个 $S_1+a_k>S_2$ 的情形，我们将新环设为终点环，把 $a_k$ 并入 $S_1$ 之后， $d'=(S_1+a_k)-S_2+a_n$ ，由于符号的改变，我们无法在只知道 $d$ 的情况下推出 $d'$
* 而两个同时维护，复杂度又不允许。
* 也就是说，我们需要更巧妙的维护方式。

在我们上面的分析中，我们都是整个环整个环的操作，并且根据大小关系的合法与否来实现统计和更新，拥有繁琐的判断过程和无法维护的弊端，那么，是否有更为通用的方法呢？  

思路2(正解)：
* 我们发现，无论我们维护的 $d$ 是怎样的形式，$S_1$ 与 $S_2$ 总是相抵的。现在，我们将红色边的数量记为正，蓝边数量记为负，则最终我们希望二者相抵为0。

* 边的变化有两种方式，一是加入整个环，二是将环确认为终点环并加入环中的部分边。

* 我们让 $f[i][j][0]$ 表示考虑到第i个环，边数相抵后的值为j，0表示答案是由**完整的环加减**也就是**还未确定终点环**下得到的，1表示答案是**已经确定了终点环**后得到的。

* 显然，有： $f[i][j][0]=f[i-1][j-a_i][0]+f[i-1][j+a_i][0]+f[i-1][j][0]$ 

* 接下来我们讨论把当前环i作为终点环的情况

* 我们将环平分为两个**非空**的部分，不难发现，以这个环为终点环后其对j值的影响如下：$1-(a_i-1),2-(a_i-2),...,(a_i-1)-1$ 不难发现，影响是从 $2-a_i$ 到 $a_i-2$ 的**间隔为2**的数，我们记这个影响的集合为 $D_1$

* 应有： $f[i][j][1]+=\sum f[i-1][p][0]$ ， $p\in D_1$ 

* 另外，别忘了统计终点环不是i但已经确定终点环的情况： $f[i][j][1]+=f[i-1][j-a_i][1]+f[i-1][j+a_i][1]+f[i-1][j][1]$

* 什么？你以为这样就完了？太天真了。

* 题目可没有保证蓝色和红色最终能到达同一个点。也就是说，可能存在这样的情况：**蓝色和红色的终点在同一个环上某条边的两端**。

* 注意此时跟**上面**的情况有点区别，上面我们要求将环平分为**非空**的两部分，是因为在用上了整个环的情形下，如果红边或蓝边的边数为0，则终点会在1点，而由于1点的特殊性(如果你真的看了我前面的推导思路)，我们**无法在此处判断把共同终点设在1点是否合法**，所以，我们要求两部分非空。

* 但在**现在**，我们在环中**空出了一条边**，不论两部分是否为空，我们都能确定终点(边)在这个环中，所以**可以为空**

* 此时，这个终点环对j的影响如下： $0-(a_i-1),1-(a_i-2),...,(a_i-1)-0$,我们记这个影响的集合为 $D_2$

* 我们发现 $D_1\cup D_2=[1-a_i,a_i-1]$  

* 那么我们自然而然地想到，维护f[i-1][j][0]的前缀和，然后 $f[i][j][1]+=sum[j+a_i-1]-sum[j-a_i]$

* 那么恭喜你，这里还有一个坑。

* 假如我们在环中空出的这条边的**一端为1点**，也就是上面我们分析到的其中一部分为空的情况，需要满足一个前提条件：**用上所有的环**。或着这么表述：**整个图中空下来保持褐色的，只有这条边**，因为如果还有别的环，这个环必然与1相连，那么这两种颜色就可以从1点沿着环继续延伸，这种情况是不合法的。

* 因此，我们在计算空出了边且边与1相连的情况时，有如下调整：

* 统计终点环不是i但已经确定终点环的情况时，不能加上 $f[i-1][j][1]$ ，也就是不能不用这个环。

* 但这就与我们上面的公式相矛盾。

* 因此，我们需要将这种情况同以1为终点的情况一起拿出来单独计算。

* 顺带一提，我们上面算的 $f[i][j][1]$ 的终点环处经过红蓝互换后可以形成新的答案，所以最终答案要乘以2。

最后是代码：
```cpp
#include <cstdio>
#define REG register
#define rep(i,a,b) for(REG int i=a;i<=b;i++)
#define Rep(i,a,b) for(REG int i=a;i>=b;i--)
inline char getc(){
    static char buf[1<<14],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<14,stdin),p1==p2)?EOF:*p1++;
}
inline int scan(){
    REG int x=0; REG char ch=0;
    while(ch<48) ch=getc();
    while(ch>=48) x=x*10+ch-48,ch=getc();
    return x;
}
inline void swap(int &A,int &B){
    REG int x=A; A=B; B=x;
}
inline int max(const int&A,const int&B){
    return A>B?A:B;
}
inline int min(const int&A,const int&B){
    return A<B?A:B;
}
const int MOD=1e9+7;
inline int add(int A,int B){
    //if(B<0) B+=MOD
    return B>MOD-A?A-MOD+B:A+B;
}
const int N=2e3+5,M=4e3+5;
int n,m,fa[N],c[N],a[N],cn,f[2][M<<1][2];
inline int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
    n=scan(); m=scan();
    rep(i,1,n) fa[i]=i,c[i]=1;
    rep(i,1,m){
        REG int u=find(scan()),v=find(scan());
        if(u==1||v==1||u==v) continue;
        fa[v]=u; c[u]+=c[v];
    }
    rep(i,2,n) if(fa[i]==i) a[++cn]=c[i]+1;
    REG int zero=m+1,t=1,ans;
    f[0][zero][0]=1; 
    for(REG int i=1;i<=cn;i++,t^=1){
        //直接继承i-1的答案，是这个环不走的情况
        rep(j,1,(m<<1)+1){
            f[t][j][0]=f[t^1][j][0]; 
            f[t][j][1]=f[t^1][j][1];
        }
        rep(j,1,(m<<1)+1){
            if(j-a[i]>0){
                f[t][j][0]=add(f[t][j][0],f[t^1][j-a[i]][0]);
                f[t][j][1]=add(f[t][j][1],f[t^1][j-a[i]][1]);
            }
            if(j+a[i]<(m+1)<<1){
                f[t][j][0]=add(f[t][j][0],f[t^1][j+a[i]][0]);
                f[t][j][1]=add(f[t][j][1],f[t^1][j+a[i]][1]);
            }
        }
        rep(j,1,(m<<1)+1) f[t^1][j][0]=add(f[t^1][j][0],f[t^1][j-1][0]);
        rep(j,1,(m<<1)+1){
            REG int l=max(1,j-a[i]+2),r=min(j+a[i]-2,(m<<1)+1);
            f[t][j][1]=add(f[t][j][1],add(f[t^1][r][0],MOD-f[t^1][l-1][0]));
        }
    }
    //终点环内红蓝互换(或者说把环镜像翻转)，答案翻倍
    ans=add(f[t^1][zero][1],f[t^1][zero][1]);
    //printf("t1:%d\n",ans);
    rep(j,1,(m<<1)+1) f[t][j][0]=f[t^1][j][0]=f[t][j][1]=f[t^1][j][1]=0;
    f[t^1][zero][0]=1;
    for(REG int i=1;i<=cn;i++,t^=1){
        //想要以1为唯一终点或终点之一，就不能空出任何环
        rep(j,1,(m<<1)+1) f[t][j][0]=f[t][j][1]=0;
        rep(j,1,(m<<1)+1){
            if(j-a[i]>0){
                f[t][j][0]=add(f[t][j][0],f[t^1][j-a[i]][0]);
                f[t][j][1]=add(f[t][j][1],f[t^1][j-a[i]][1]);
            }
            if(j+a[i]<(m+1)<<1){
                f[t][j][0]=add(f[t][j][0],f[t^1][j+a[i]][0]);
                f[t][j][1]=add(f[t][j][1],f[t^1][j+a[i]][1]);
            }
            //统计空出一条边且该边与1相连的情况
            if(j-a[i]+1>0) f[t][j][1]=add(f[t][j][1],f[t^1][j-a[i]+1][0]);
            if(j+a[i]-1<(m+1)<<1) f[t][j][1]=add(f[t][j][1],f[t^1][j+a[i]-1][0]);
        }
    }
    //对于f[i][0][0]也就是以1为唯一终点的情况 红蓝的各种组合在红正蓝负相抵中已经体现了，不需要互换了。
    ans=add(ans,f[t^1][zero][0]);
    //printf("t2:%d\n",ans);
    //对于f[i][0][1]我们镜像翻转 答案翻倍
    ans=add(ans,add(f[t^1][zero][1],f[t^1][zero][1]));
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：睿智的憨憨 (赞：2)

### 题目大意

给定一个简单无向图，并保证除 $1$ 号结点外，其他点的度均为 $2$。所有的边开始都是灰的。

有两名选手 $R$ 和 $B$，$R$ 会把他经过的边涂成红色，$B$ 会把他经过的边涂成蓝色，两名选手初始均在 $1$ 号节点。每一轮，$R$ 和 $B$ 会分别选择一条与当前结点相连的灰边并走到边的另一端，同一轮中不能选择相同的边。

当两名选手无法均无法移动时，比赛结束。请求出结束时不同的图的数量（若两个图有一条边异色，则这两个图不同）。

### 解法分析

画出样例的图，我们可以发现图可以拆分成若干个过 $1$ 号点的环。记环的个数为 $k$，第 $i$ 个环的长度为 $l_i$。比赛结束时的情况可能是以下四种之一。

情况 $1$：两人均在 $1$ 号点，此时所有的环应当都被染上色，否则他们可以再找一个环继续在环上走下去。

情况 $2$：两人同时在环上一个异与 $1$ 号点的点。

情况 $3$：两人分别在环上两个异与 $1$ 号点的点，且这两个点距离为 $1$。

情况 $4$：两人一个在 $1$ 号点，一个离 $1$ 号点的距离为 $1$，且此时只剩它们之间的边没被染过色。

可以证明比赛结束时不存在其他情况，且不会有一种情况同时满足上面四个条件中的两个。我们发现方法数是可以 dp 的。

设红边的数量为 $r$，蓝边的数量为 $b$。由于需要枚举在那个环上相遇，也就是把原来的数组切成两半，所以我们可以设计两个 dp，在最后需要的时候合并起来。$dp1_{i,j,0/1}$ 表示前 $i$ 个环，$r-b=j$，没有 / 有使用全部前 $i$ 条边，$dp2$ 则为后 $i$ 个环。$dp1$ 的转移方程如下，$dp2$ 同理。

+ $dp1_{i - 1,j,f} \Rightarrow dp1_{i,j+l_i,f}$
+ $dp1_{i - 1,j,f} \Rightarrow dp1_{i,j-l_i,f}$
+ $dp1_{i - 1,j,f} \Rightarrow dp1_{i,j,0}$

这里详细说说情况 $2$ 和 $3$，都要枚举相遇时环的长度 $l$，并设 $R$ 在环上走的边数为 $x$。

情况 $2$：$B$ 在环上走的距离为 $l-x$，则 $R$ 和 $B$ 在环上差了 $l-2 \times x$ 条边，在环外需要补回来。

情况 $3$：和情况 $2$ 类似，只是 $B$ 在环上走的距离变为 $l-x-1$。

时间复杂度为 $O(2 \times m \times \sum_{i=1}^k a_i)=O(n \times m)$。

最后别忘了取模！

### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;
int n, m, K, l[2010];
bool vis[2010];
vector<int> e[2010];
void dfs(int u){
	if (u == 1)
		return ;
	vis[u] = true, l[K]++;
	for (int v : e[u])
		if (!vis[v])
			dfs(v);
}
int dp1[2010][8010][2], dp2[2010][8010][2];
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int u : e[1])
		if (!vis[u])
			l[++K] = 1, dfs(u);
	dp1[0][m][1] = dp2[0][m][1] = 1;
	for (int i = 0; i < K; i++){
		for (int j = 0; j <= 2 * m; j++){
			for (int k = 0; k <= 1; k++){
				if (j + l[i + 1] <= 2 * m)
					(dp1[i + 1][j + l[i + 1]][k] += dp1[i][j][k]) %= mod;
				if (j - l[i + 1] >= 0)
					(dp1[i + 1][j - l[i + 1]][k] += dp1[i][j][k]) %= mod;
				(dp1[i + 1][j][0] += dp1[i][j][k]) %= mod;
				if (j + l[K - i] <= 2 * m)
					(dp2[i + 1][j + l[K - i]][k] += dp2[i][j][k]) %= mod;
				if (j - l[K - i] >= 0)
					(dp2[i + 1][j - l[K - i]][k] += dp2[i][j][k]) %= mod;
				(dp2[i + 1][j][0] += dp2[i][j][k]) %= mod;
			}
		}
	}
	ll ans = dp1[K][m][1];
	for (int i = 1; i <= K; i++){
		for (int j = 1; j <= l[i] - 1; j++){
			int nd1 = l[i] - 2 * j, nd2 = l[i] - 2 * j - 1, nd3 = l[i] - 1;
			for (int k = -m; k <= m; k++){
				ll val = (dp1[i - 1][m + k][0] + dp1[i - 1][m + k][1]) % mod;
				if (j < l[i]){
					if (k <= nd1 && nd1 - k <= m)
						ans = (ans + 2 * val * (dp2[K - i][m + nd1 - k][0] + dp2[K - i][m + nd1 - k][1])) % mod;
					if (k > nd1 && k - nd1 <= m)
						ans = (ans + 2 * val * (dp2[K - i][m + k - nd1][0] + dp2[K - i][m + k - nd1][1])) % mod;
				}
				if (j < l[i] - 1){
					if (k <= nd2 && nd2 - k <= m)
						ans = (ans + 2 * val * (dp2[K - i][m + nd2 - k][0] + dp2[K - i][m + nd2 - k][1])) % mod;
					if (k > nd2 && k - nd2 <= m)
						ans = (ans + 2 * val * (dp2[K - i][m + k - nd2][0] + dp2[K - i][m + k - nd2][1])) % mod;
				}
				if (j == l[i] - 1){
					if (k <= nd3 && nd3 - k <= m)
						ans = (ans + 4ll * dp1[i - 1][m + k][1] * dp2[K - i][m + nd3 - k][1]) % mod;
					if (k > nd3 && k - nd3 <= m)
						ans = (ans + 4ll * dp1[i - 1][m + k][1] * dp2[K - i][m + k - nd3][1]) % mod;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

适合给刚学背包问题的小朋友当做背包问题基础练习。

考虑整个图形成一个以 $1$ 为中心的花花的结构，也就是 $1$ 上面挂了很多环。

最后停下来的时候，两个人必定在同一点或者中间间隔一条未访问的边。

如果其中一个人在 $1$ 上，另一个人不在，那么他们中间隔了一条边，且其他所有边都访问过了；如果两个人都在 $1$ 上，那么所有边已经访问。这时候每个环都被一个人完全包揽，因此可以把每个环的权值当做 $\pm len$，做背包问题。（注意可能有一个环的权值是 $\pm (len-1)$。不过没关系，把所有前缀、后缀的背包求出来，最后做一个小小的卷积即可）

如果两个人都不在 $1$ 上，那么和上一种情况基本相同，不过有的环可以完全不访问。

中间那个“卷积”会做 $O(m)$ 次，因此总的复杂度为 $O(nm)$，有较大常数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD=1e9+7;
int n,m,k,vis[MAXN],ad=2000,pre[MAXN][MAXN<<1],suf[MAXN][MAXN<<2],ans;
vector<int> G[MAXN],val;
int nxt(int u,int lst) {return G[u][0]+G[u][1]-lst;}
int calc(int p,int v) {
	int ans=0;
	ffor(j,0,ad+ad) if(v+ad+ad-j>=0&&v+ad+ad-j<=ad+ad) ans=(ans+pre[p-1][j]*suf[p+1][v+ad+ad-j])%MOD;	
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	for(auto u:G[1]) if(!vis[u]) {
		int len=1;
		int tpos=u,lst=1,Lst;
		vis[u]=1;
		while(tpos!=1) Lst=tpos,tpos=nxt(tpos,lst),vis[tpos]=1,lst=Lst,len++;
		val.push_back(len);
	}
	k=val.size();
	suf[k+1][ad]=pre[0][ad]=1;
	ffor(i,1,k) {
		int v=val[i-1];
		ffor(j,0,ad+ad) {
			if(j>=v) pre[i][j]=(pre[i][j]+pre[i-1][j-v])%MOD;
			if(j+v<=ad+ad) pre[i][j]=(pre[i][j]+pre[i-1][j+v])%MOD;
		}
	}
	roff(i,k,1) {
		int v=val[i-1];
		ffor(j,0,ad+ad) {
			if(j>=v) suf[i][j]=(suf[i][j]+suf[i+1][j-v])%MOD;
			if(j+v<=ad+ad) suf[i][j]=(suf[i][j]+suf[i+1][j+v])%MOD;
		}
	}
	if(m%2==0) ans=pre[k][ad];
	else ffor(i,1,k) ans=(ans+4*calc(i,val[i-1]-1))%MOD;
	memset(pre,0,sizeof(pre)),memset(suf,0,sizeof(suf));
	suf[k+1][ad]=pre[0][ad]=1;
	ffor(i,1,k) {
		int v=val[i-1];
		ffor(j,0,ad+ad) {
			pre[i][j]=(pre[i][j]+pre[i-1][j])%MOD;
			if(j>=v) pre[i][j]=(pre[i][j]+pre[i-1][j-v])%MOD;
			if(j+v<=ad+ad) pre[i][j]=(pre[i][j]+pre[i-1][j+v])%MOD;
		}
	}
	roff(i,k,1) {
		int v=val[i-1];
		ffor(j,0,ad+ad) {
			suf[i][j]=(suf[i][j]+suf[i+1][j])%MOD;
			if(j>=v) suf[i][j]=(suf[i][j]+suf[i+1][j-v])%MOD;
			if(j+v<=ad+ad) suf[i][j]=(suf[i][j]+suf[i+1][j+v])%MOD;
		}
	}
	ffor(i,1,k) {
		int v=val[i-1];
		ffor(j,1,v-1) ans=(ans+2*calc(i,v-2*j))%MOD;
		ffor(j,1,v-2) ans=(ans+2*calc(i,v-1-2*j))%MOD;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

下称两人分别为 AA 和 BB。

除 $1$ 外所有点的度数都为 $2$，其实就是在 $1$ 上挂了一些不相交的环。

先把这些环搜出来，设它们的长度分别是 $a_1,\dots,a_k$。

1. 两人最后都回到 $1$

考虑 DP，设 $F'_{i,j}$ 为 $a_1,\dots,a_i$ 每个环都被某个人单独走完且 AA 比 BB 多走了 $j$ 条边的方案数。

转移过于简单，此处不再叙述。

答案即为 $F'_{k,0}$。

2. 两人最后没有都回到 $1$

那么一定是两个人都在某个环上或者某个人在 $1$ 另一个人在某个环上。

考虑直接枚举这个环 $a_p$。

令其他每个环都被某个人单独走完或者不走且 AA 比 BB 多走了 $j$ 条边的方案数为 $F_j$，其他每个环都被某个人单独走完且 AA 比 BB 多走了 $j$ 条边的方案数为 $F'_j$。

不难发现答案即为 $\sum_{\lvert j\rvert<a_p-1}F_j+\sum_{\lvert j\rvert=a_p-1}F'_j$。这里需要分两类是因为如果某个人需要补走到只剩一条边那么需要其他环都被走完，否则还能走。

如果每次都求 $F,F'$ 显然炸了，考虑求出前后缀的 $F,F'$，然后看似要卷积但是可以前缀和优化。

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int mod=1e9+7;
const int N=2005;
const int M=8005;
const int D=4000;
int n,m,a[N],idx,f1[N][M],f2[N][M],f1_[N][M],f2_[N][M];
vector<int>g[N];
bool vis[N];
void dfs(int u,int dis,int pre){
	vis[u]=1;
	bool xs=1;
	for(auto v:g[u]){
		if(v==pre&&xs)xs=0;
		else if(v==1)a[++idx]=dis+1;
		else if(!vis[v])dfs(v,dis+1,u);
	}
}
void slv(){
	scanf("%d %d",&n,&m);
	rep(i,1,m){
		int u,v;
		scanf("%d %d",&u,&v);
		g[u].pb(v),g[v].pb(u);
	}
	dfs(1,0,0);
	f1_[0][0+D]=1;
	rep(i,1,idx)rep(j,-m+a[i],m-a[i]){
		f1_[i][j+a[i]+D]=(f1_[i][j+a[i]+D]+f1_[i-1][j+D])%mod;
		f1_[i][j-a[i]+D]=(f1_[i][j-a[i]+D]+f1_[i-1][j+D])%mod;
	}
	f2_[idx+1][0+D]=1;
	per(i,idx,1)rep(j,-m+a[i],m-a[i]){
		f2_[i][j+a[i]+D]=(f2_[i][j+a[i]+D]+f2_[i+1][j+D])%mod;
		f2_[i][j-a[i]+D]=(f2_[i][j-a[i]+D]+f2_[i+1][j+D])%mod;
	}
	int ans=f1_[idx][0+D];
	f1[0][0+D]=1;
	rep(i,1,idx){
		rep(j,-m,m)f1[i][j+D]=f1[i-1][j+D];
		rep(j,-m+a[i],m-a[i]){
			f1[i][j+a[i]+D]=(f1[i][j+a[i]+D]+f1[i-1][j+D])%mod;
			f1[i][j-a[i]+D]=(f1[i][j-a[i]+D]+f1[i-1][j+D])%mod;
		}
	}
	f2[idx+1][0+D]=1;
	per(i,idx,1){
		rep(j,-m,m)f2[i][j+D]=f2[i+1][j+D];
		rep(j,-m+a[i],m-a[i]){
			f2[i][j+a[i]+D]=(f2[i][j+a[i]+D]+f2[i+1][j+D])%mod;
			f2[i][j-a[i]+D]=(f2[i][j-a[i]+D]+f2[i+1][j+D])%mod;
		}
	}
	rep(i,1,idx+1)rep(j,-m,m)f2[i][j+D]=(f2[i][j+D]+f2[i][j-1+D])%mod;
	rep(i,1,idx)rep(x,-m,m){
		if(-x-a[i]+2<=a[i]-x-2)ans=(ans+(ll)f1[i-1][x+D]*((f2[i+1][a[i]-x-2+D]-f2[i+1][-x-a[i]+1+D]+mod)%mod)%mod*2%mod)%mod;
		if(-m<=a[i]-1-x&&a[i]-1-x<=m)ans=(ans+(ll)f1_[i-1][x+D]*f2_[i+1][a[i]-1-x+D]%mod*2%mod)%mod;
		if(-m<=-x-a[i]+1&&-x-a[i]+1<=m)ans=(ans+(ll)f1_[i-1][x+D]*f2_[i+1][-x-a[i]+1+D]%mod*2%mod)%mod;
	}
	printf("%d\n",ans);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

不难发现这个图是一个若干个环，所有环公共点有且仅有 $1$ 的图。

考虑路径的特点，不难发现肯定是走上一个环就要走回 $1$，或者碰上另一个人后无路可走。

于是路径可以看做若干个单色环以及一个双色环，其中最多有一条边无色，每种颜色边数相等。

考虑什么情况下会结束，一种是两个人在一个环内（除 $1$ 点外）碰上了，一个是除了最多一条 $1$ 周围的边以外所有边都涂上颜色了。

对于第一类，考虑一个 dp 去计算每种颜色目前的数量。转移枚举全归红/蓝，红 $i$ 蓝 $tot-i$ 或 $tot-i-1$ 个，要求 $i$，$tot-i$ 或 $tot-i-1$ 均大于等于 $1$，以及环上无色。

第二类只需转移全归红/蓝即可。

这样直接做是 $O(n^3)$ 的。

考虑不需要记录红/蓝的准确数量，只需要知道他们的差值，这样就可以 $O(n^2)$ 了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7; 
int f[2005],cnt[2005];
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
int a[4005],k,siz;
int dp[2][8005][2];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		if((u-1)&&(v-1)) f[find(u)]=find(v);
	}
	for(int i=1;i<=n;i++) cnt[find(i)]++;
	for(int i=2;i<=n;i++){
		if(cnt[i]>0) a[++k]=cnt[i]+1;
	}
	dp[0][4002][0]=1,siz=0;
	for(int i=1;i<=k;i++){
		memset(dp[i&1],0,sizeof(dp[i&1]));
		for(int j=4002-siz;j<=4002+siz;j++){
			(dp[i&1][j-a[i]][0]+=dp[(i&1)^1][j][0])%=mod;
			(dp[i&1][j][0]+=dp[(i&1)^1][j][0])%=mod;
			(dp[i&1][j+a[i]][0]+=dp[(i&1)^1][j][0])%=mod;
			(dp[i&1][j-a[i]][1]+=dp[(i&1)^1][j][1])%=mod;
			(dp[i&1][j][1]+=dp[(i&1)^1][j][1])%=mod;
			(dp[i&1][j+a[i]][1]+=dp[(i&1)^1][j][1])%=mod;
			for(int t=-a[i]+2;t<=a[i]-2;t++) (dp[i&1][j+t][1]+=dp[(i&1)^1][j][0])%=mod;
		}
		siz+=a[i];
	}
	int ans=dp[k&1][4002][1]*2%mod;
	memset(dp,0,sizeof(dp));
	dp[0][4002][0]=1,siz=0;
	for(int i=1;i<=k;i++){
		memset(dp[i&1],0,sizeof(dp[i&1]));
		for(int j=4002-siz;j<=4002+siz;j++){
			(dp[i&1][j-a[i]][0]+=dp[(i&1)^1][j][0])%=mod;
			(dp[i&1][j+a[i]][0]+=dp[(i&1)^1][j][0])%=mod;
			(dp[i&1][j-a[i]][1]+=dp[(i&1)^1][j][1])%=mod;
			(dp[i&1][j+a[i]][1]+=dp[(i&1)^1][j][1])%=mod;
			(dp[i&1][j+a[i]][1]+=dp[(i&1)^1][j][0])%=mod;
		}
		siz+=a[i];
	}
	(ans+=dp[k&1][4002][0]+dp[k&1][4003][1]*4)%=mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2600}$
---

[$\text{更加 straightforward 的阅读体验}$](https://codeforces.com/blog/entry/83148)

---
### 解题思路：

由于保证了除一号点以外的所有点的度数为 $2$，可以发现整个图就是由若干个包含一号点的环组成的，并且除了一号点其它所有点都只在环中出现一次。于是这里可以先将图用一个序列 $a_i$ 描述，其中每一个位置上的 $a_i$ 表示一个环的长度。

接下来就能较容易地分析移动的规则了。容易根据玩家的位置得出以下三种情况：

1. 红蓝两者恰好在一号点相遇，此时所有的边一定都已经被染色过了，否则一定可以再继续往下走。

2. 红蓝两者在一个环上的一个点或者差一条边相遇了，此时可能存在一些边是灰色的。

3. 红蓝两者一个在一号点，另一个在环上，两者刚好差一条边的

---
容易发现，这里出现的关键信息有两个，一个是两者的位置，另一个是是否所有的环全都被走过，加上一个基础的考虑前若干个环。可以设计出 $f_{i,j,k}$ 表示考虑前 $i$ 个环，其中两者步数相差的绝对值为 $j$ 步，且 $k=1$ 时表示所有的环都被走过，$k=0$ 表示存在环没被走过。

此处为步数差加上绝对值是红蓝对称，最后直接把答案乘上 $2$ 就行。

---
然后考虑转移，容易得出整个转移就是对于某一个环让其由哪一个玩家走，还是干脆放弃这个环，两个都不走。

即 $f_{i,j,1}$ 转移到 $f_{i+1,|j+a_i|,1}$，$f_{i+1,|j-a_i|,1}$ 和 $f_{i-1,j,0}$，以及 $f_{i,j,0}$  转移到 $f_{i+1,|j+a_i|,0}$，$f_{i+1,|j-a_i|,0}$ 和 $f_{i-1,j,0}$。

直接执行这个过程不能要求最后具体在哪一个位置停止，需要先枚举最终在哪一个环上停止了或者是在一号点相遇了。

若最后在环上终止，需要先将当前环去掉，然后设当前枚举出的环的长度为 $l$，则情况二的方案数为 $2\times \sum_{i=0}^{l-2} (f_{n,i,0}+f_{n,i,1})$，情况三的方案数为 $2\times f_{n,l-1,1}$。

如果在一号点终止，则不需要去掉任何环，直接有答案 $f_{n,0,1}$。

---
这样的一次 $\text{DP}$ 的复杂度是 $O(n^2)$ 的，直接枚举环的复杂度为 $O(n^3)$，不能接受。但是容易想到所有环的唯一特征就是长度，长度一样的只要算一遍就好了，由于 $\sum a_i=n$，只有 $\sqrt n$ 个不一样的取值，最终复杂度为 $O(n^{\frac{5}{2}})$。这样就能通过本题了。

---
但其实还能进一步优化到 $O(n^2)$，方法还是利用环的唯一特征就是长度，以及这个 $\text{DP}$ 是无关顺序的。

将所有的长度出现过两次或者两次以上的环预处理出来，由于每一次最多只会删除一个环，可以先将出现次数减一的数量的环直接处理到 $\text{DP}$ 数组中，容易发现这一部分是无论如何都不会变化的。

然后剩下的需要处理的环就只有 $\sqrt n$ 个了，处理复杂度为 $O(n\sqrt n)$，算上枚举的复杂度就是 $O(n^2)$。

两个优化其实非常相似，只是一个处理的是枚举的数，另一个处理的是其它的数。

---
再往下其实还能再优化一次。就是发现每一次缺少的只有一个，其它的都要重做，那就用分治做一个类似于 $\text{CF1442D}$ 的东西，好像是叫缺一背包，复杂度再次降低到 $O(n\sqrt n \log n)$。这个优化纯属没事找事。

---
注意算方案的时候乘法可能会溢出，以及数组不要开小。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=10005,MOD=1000000007;
int n,m,x,y,head[MAXN],nxt[MAXN*2],num[MAXN*2],tot,a[MAXN],cnt,vis[MAXN],f[2][MAXN][2],now;
int CNT[MAXN],NUM[MAXN],N,ans,F_init[MAXN][2];
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void dfs(int now,int fa,int len){
	vis[now]=1;
	if(now==1){
		a[++cnt]=len;
		return;
	}
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa){
			fa=-1;
			continue;
		}
		dfs(num[i],now,len+1);
	}
}
void work(int x){
	for(int i=0;i<=2*n;i++)
	f[now^1][i][0]=f[now^1][i][1]=0;
	for(int i=0;i<=2*n;i++){
		f[now^1][abs(i-x)][1]=(f[now^1][abs(i-x)][1]+f[now][i][1])%MOD;
		f[now^1][abs(i+x)][1]=(f[now^1][abs(i+x)][1]+f[now][i][1])%MOD;
		f[now^1][i][0]=(f[now^1][i][0]+f[now][i][1])%MOD;
		
		f[now^1][abs(i-x)][0]=(f[now^1][abs(i-x)][0]+f[now][i][0])%MOD;
		f[now^1][abs(i+x)][0]=(f[now^1][abs(i+x)][0]+f[now][i][0])%MOD;
		f[now^1][i][0]=(f[now^1][i][0]+f[now][i][0])%MOD;
	}
	now^=1;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=head[1];i;i=nxt[i]){
		if(vis[num[i]])continue;
		dfs(num[i],1,1);
	}
//	for(int i=1;i<=cnt;i++)printf("%d ",a[i]);
	sort(a+1,a+cnt+1);
	f[0][0][1]=1;a[0]=-1;now=0;
	for(int i=1;i<=cnt;i++){
		if(a[i]!=a[i-1]){
			NUM[++N]=a[i];
			CNT[N]=1;
		}
		else{
			work(a[i]);
			CNT[N]++;
		}
	}
	for(int i=0;i<=n;i++)
	F_init[i][0]=f[now][i][0],F_init[i][1]=f[now][i][1];
	for(int del=0;del<=N;del++){
		int l=NUM[del];
		now=0;
		for(int i=0;i<=2*n;i++)f[now][i][0]=F_init[i][0],f[now][i][1]=F_init[i][1];
		for(int i=1;i<=N;i++)
		if(i!=del)work(NUM[i]);
		if(del==0){
			ans=(ans+f[now][0][1])%MOD;
		}
		else{
			for(int i=0;i<=l-2;i++)ans=(ans+CNT[del]*2*(f[now][i][0]+f[now][i][1]))%MOD;
			ans=(ans+CNT[del]*2*f[now][l-1][1])%MOD;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

