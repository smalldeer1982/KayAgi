# Moonwalk challenge

## 题目描述

自从 BubbleCup XI 任务的宇航员们完成了他们在月球上的任务后，作为著名歌手的粉丝，他们决定在返回地球前玩一会儿，于是创造了一个名为“月球漫步挑战”的游戏。

宇航员们被分成若干小队，每队会获得一张月球陨石坑的地图，以及一些可以安全“月球漫步”的双向直达路径。每条直达路径都有一种颜色，并且任意两个陨石坑之间有且仅有一条唯一的路径。游戏的目标是找到一对陨石坑，使得给定的颜色数组在这两点之间的路径上作为连续子数组出现的次数最多（重叠出现也要计数）。

为了帮助你喜欢的队伍获胜，你需要编写一个程序，给定地图后，回答如下类型的查询：对于两个陨石坑和一个颜色数组，回答该颜色数组作为连续子数组在这两点之间的路径上出现了多少次（重叠出现也要计数）。

颜色用小写英文字母表示。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
2 3 g
3 4 n
5 3 o
6 1 n
1 2 d
7
1 6 n
6 4 dg
6 4 n
2 5 og
1 2 d
6 5 go
2 3 g
```

### 输出

```
1
1
2
0
1
1
1
```

# 题解

## 作者：Sampson_YW (赞：4)

由于 $|S|\leq 100$，所以可以对每种长度 $L$ 求答案。

求出每个点向上长度为 $L$ 的字符串哈希值，然后相当于是查询路径上等于某个值的点权数量。但是跨过 LCA 的 $2L$ 个字符串要特判，因此让 $x,y$ 分别向上跳到和 $lca$ 距离为 $L$ 的点上，暴力求这 $2L$ 个字符串的哈希值就行。

至于查询路径上等于某个值的点权数量，差分变成到根的两条链，然后 DFS 一遍，用哈希表存一下每个数的出现次数就行。

复杂度 $O((n+q)(|S|+\log n))$。[code](https://codeforces.com/contest/1045/submission/234683790)

---

## 作者：sgl654321 (赞：2)

## 闲话
被 @[Hoks](https://www.luogu.com.cn/user/551100) 推荐了这一题作为两百紫，听说之前是黑题降紫了的，代码工程量很大。被折磨了两天终于弄出来了。

这篇题解参考了 @[lzyqwq](https://www.luogu.com.cn/article/2706tohk) 的思路，同时省去了一些不必要的部分。因此代码会**精简**一些。

闲话少叙，正片开始。由于题目大意已经很清楚了因此不再赘述。

## 解题思路

### 基本思路
树上链查询问题，考虑树链剖分。字符串问题，考虑字符串哈希。边上有边权，考虑边转点。

通过如上的操作，我们就可以轻易的知道，在一条**重链内部**，从 $x$ 点向上或向下跳 $k$ 步，所构成的字符串的哈希值。这个可以 $O(1)$ 完成。

我们把一条链转化成多条重链的并集，那么就可以知道**任意的** $x$ 点向上跳 $k$ 步，所构成的字符串及其反串的哈希值，这可以 $O(\log n)$ 完成。
  
### 询问处理思想
我们可以把一个询问的链分成两段，分别是不经过 LCA（即不拐弯）的情况，和经过 LCA 的情况。

同时为了在处理不经过 LCA 的情况时更加方便，我们考虑**离线询问**，统一处理 $|S|$ 相同时的情况。具体会在后面阐述。

### 处理经过 LCA
这个比较容易，由于 $|S|\le 100$，非常小，我们可以直接考虑枚举 LCA 两端分别有多长，然后通过哈希值拼接，与 $S$ 的哈希值比较是否相等即可。这里是 $O(|S|\log n)$ 的。$q$ 次询问，总共 $O(q|S|\log n)$。

### 处理不经过 LCA

#### 1. 离散化树上哈希值
我们在统一处理 $|S| = k$ 的询问之前，先弄出每个点 $x$ 向上走 $k$ 步所组成的字符串（记作**正串**）及其**反串**的哈希值 $hs$。

对这些哈希值进行离散化，我们就可以知道：

- 哈希值为 $hs$ 的正串出现在了哪些 $x$ 上。把这些 $dfn_x$ （注意要套上一层 dfs 序！）存储在类型为 `vector` 的 `ve1[hs]` 里面，然后对所有 `ve1[hs]` 进行排序。

- 哈希值为 $hs$ 的反串出现在了哪些 $x$ 上。把这些 $dfn_x$ （注意要套上一层 dfs 序！）存储在类型为 `vector` 的 `ve2[hs]` 里面，然后对所有 `ve2[hs]` 进行排序。

这里复杂度我们考虑对所有询问统一分析，可知是 $O(n|S|\log n)$ 的。

#### 2. 询问时在 vector 里二分
接着我们考虑对于每个询问，$S$ 的哈希值为 $h$。

我们可以把 $x$ 向上跳到 LCA 拆分成很多条重链。重链内部的 dfs 序是连续的，因此我们可以直接在 `ve1[h]` 中进行二分（`lower_bound` 或者 `upper_bound`），看看有没有起点 $s$ 在这条重链内的正串。

这里有个注意点，就是你不能跳太过了。不能让 $s$ 往上跳，跳到 LCA 的祖先去了。

类似的，我们可以把 LCA 向下跳到 $y$ 拆分成很多条重链，直接在 `ve2[h]` 中进行二分，看看有没有起点 $s$ 在这条重链内的反串。同样注意不能跳到 LCA 的祖先去了。

分析复杂度：重链总数 $O(\log n)$，二分 $O(\log n)$。询问有 $q$ 次，所以是 $O(q\log^2n)$ 的。

综上，我们就处理完询问了。

对比 lzy 的题解，我这个不需要分开处理跨不跨过重链，复杂度仍然正确。总共是 $O(n|S|\log n+ q|S|\log n +q\log^2n)$ 的。

## 注意点
1. 本题该做法代码普遍较长，~~除一些极强的板子仙人外~~，写的时候一定要仔细分析，每一部分保证写对。

2. 哈希值处理我们采用前缀和方式，注意树剖的 dfs 序编号和实际树中编号的映射关系，应当是 $hash[i] = hash[i-1] \times base + a[rnk[i]]$。

3. 本题没有卡哈希自然溢出！直接 `unsigned long long` 启动！

4. 对哈希值的离散化请不要使用 `map`，多一只 $\log$ 导致第九个点超时。也请不要使用 `unordered_map`，巨大常数导致第十一个点超时。可以使用 `gp_hash_table`。

5. 我们会把离散化后的哈希值存入 `ve1[p],ve2[p]` 中。注意，这两个 `vector` 数组的大小要开到 $2 \times n$，因为你对于每个点，处理了正反两类哈希值。

6. `vector` 上二分的时候，注意边界情况。

7. 在讲思路的时候说过了，不跨 LCA 的询问，要仔细判断有没有向上跳到 LCA 的祖先去了。

8. 边转点的 LCA 不算。离线询问记得清空数组。

可以看出这题还是很考验大家的代码能力的。属于上上上上位紫题。

## 参考代码
[在这里嘞！](https://codeforces.com/contest/1045/submission/252735166)

---

## 作者：lzyqwq (赞：2)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17813543.html)**

这题怎么才 $\color{red}*2600$ 啊，我觉得有 $\color{maroon} *3000+ $，太菜了 /ll。

明天期中考试了，来一个官方题解做法涨涨 rp，复杂度更劣还要离线，被爆了 /ll。~~题解区大佬说哈希狗都不写。~~

**[洛谷](https://www.luogu.com.cn/problem/CF1045J) [CF](https://codeforces.com/problemset/problem/1045/J)**

> - 给出一棵 $n$ 个点的树，边上有字母。$q$ 次询问，每次给出一条路径 $u\rightsquigarrow v$ 和一个字符串 $s_i$，询问 $s_i$ 在 $u\rightsquigarrow v$ 的路径边上字母顺次拼接构成的字符串中出现了几次。
>
> - $n,q\le 10^5$，记 $S=\max\limits_{i=1}^q|s_i|$，$\color{red}\boldsymbol{S\le 100}$。

看到这题，我的第一反应是 [CF1608G Alphabetic Tree](https://codeforces.com/problemset/problem/1608/G)，两题难度虽然差的有点多，做法的相似之处也不是很大，但是都是十分恐怖的重工业题。

进入正题，我们发现询问串的长度很小，考虑分别处理每一种长度的询问，记当前正在处理的长度为 $len$。

先对树进行重链剖分、边转点，则路径由 $\mathcal{O}(\log n)$ 条重链组成。对于每一个询问，可以将字符串的出现位置分为**完全在重链内**以及**跨越重链**两类。

- 对于完全在重链内的位置：

> - 先处理出每条重链**自上而下**以及**自下而上**的**前缀**哈希值，这样就可以求出重链内任意一条子路径、任意一种方向的哈希值。
>
> - 求出每个点向上走 $len$ 条边，向上、向下的哈希值 $vu_i,vd_i$，并将它们离散化。对于每一种离散化值维护一个 `std::vector` 按顺序从小到大存放哈希值离散化后为该值的点的 $dfn$。
>
> - 则跳链的时候，设当前的链底的点为 $x$，则问题可以变成：
>
>     > 查询在区间 $[dfn_{top_x}+len-1,dfn_x]$ 内，有多少点的权值为给定的值。
>
> - 类似 [P5838](https://www.luogu.com.cn/problem/P5838) 一样，在 `std::vector` 上二分得到左右端点求区间长度即可。
>
> - 若当前重链在 $u\rightsquigarrow \text{LCA}$ 的链上，则查询向上的哈希值，否则查询向下的哈希值。

- 对于跨越重链的位置：

> - 在处理“完全在重链内的位置”时，用 `std::vector` 存下每一条重链的顶部、$dfn$ 区间和方向。
>
> - 枚举起始的重链，则出现位置一定是起始重链长度为 $len$ 的后缀（若不足则全部选，下同），以及该重链结尾位置再往后走 $len$ 条边构成的字符串中（不然出现的起始位置要么没有跨越重链，要么不在起始重链内）。
>
> - 暴力找出这条路径并记录其构成的字符串，进行哈希 / KMP 与询问串进行匹配。注意要保证跨越重链及起始位置在起始重链内。

做法大概就这样，~~好像也不是 too hard~~。接下来算复杂度。

> - 输入以及重链剖分的预处理部分时间复杂度为 $\mathcal{O}(n+qS)$。
>
> - 对于枚举 $len$，预处理每个点向上 / 向下的哈希值并离散化的部分，一个点计算一次时间复杂度为 $\mathcal{O}(\log n)$，要排序的元素一共有 $\mathcal{O}(nS+q)$ 个，总时间复杂度是 $\mathcal{O}((nS+q)\log (n+q))$。
>
> - 对于一个询问，处理“完全在重链内”的位置的时间复杂度为 $\mathcal{O}(\log^2 n)$；处理“跨越重链的位置”时，枚举重链的时间复杂度为 $\mathcal{O}(\log n)$，找出路径以及字符串匹配的时间复杂度为 $\mathcal{O}(S)$。所以一次询问的时间复杂度为 $\mathcal{O}(\log n(\log n+S))$，总时间复杂度是 $\mathcal{O}(q\log n(\log n +S))$。
>
> - 综上，该算法的时间复杂度为 $\mathcal{O}((nS+q)\log (n+q)+q\log n(\log n+S))$，常数有点大。配合 $6\text{ s}$ 的时限还算能够接受。精细实现后跑得很快。~~我人傻常数大。~~
>
> - 空间复杂度显然为 $\mathcal{O}(n+q)$。

至此这题基本上解决了。完结撒花！

**[提交记录（含 $\bold{8.9\,\text{KB}}$ 抽象代码）](https://codeforces.com/contest/1045/submission/231558867)**

---

## 作者：hater (赞：1)

（小清新数据结构 适合解压 ） 

数据范围中 字符串长度 $ <= 100 $ 

可以考虑从这上面入手 

树剖一手 一条重链上离线询问 重链之间暴力匹配 

更具体的 ： 

重链上的询问标记 按长度分类做 

假设现在正在处理长度为 $l$ 的询问 

一个点的权值就是它向上 $l$ 步形成字符串的hash值 

询问就是 $logn$ 个区间询问 $ ( l , r , s ) $ $l$到$r$区间值为$s$的个数 

离散化一遍 差分一下就OK

然后你会发现这个东西大概常数大 时间复杂度大且丑 根本不想写 （ 鸽鸽们教教 /kel ） 

我们考虑更简单的解法 

对树建 $SAM$ 线段树维护$endpos$的$dfn$序 

询问串匹配后 用树剖拆成若干个询问

在 LCA 处跑匹配 KMP Hash都可以 

之后就不需要什么 $ S <= 100 $ 的条件 

时间复杂的是 两个 log 和 字符集的长度 比较优秀 

（ 广义 SAM 建树是假的 ? /yiw 不管 它能够过题 ） 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )  
#define ls lson[k] 
#define rs rson[k] 
using namespace std ; 
const int N = 1e5+10 , M = 5e6 , L = 205 ;  
int kmp[L] ; 
int n , pi[N] , a[N] ;  
vector <int> v[N] , edge[N] ; 
int in_li[N] , in_tr[N] , top[N] , pre[N] , son[N] , sz[N] , dep[N] , tot1 ; 
struct sam { 
  int tr[N*3][27] , fail[N*3] , len[N*3] , tot , tot2 ; 
  int rt[N*3] , s[M] , lson[M] , rson[M] ; 
  vector <int> vf[N*3] ; int val[N*3] ;  
  void prep( ) { tot = pi[1] = 1 ; tot2 = 0 ; }  
  void ins( int ax , int las , int x ) { 
    int u = ++tot , p = las ;  
    len[u] = len[las] + 1 ; 
    for( ; p && !tr[p][x] ; p = fail[p] ) tr[p][x] = u ; 
    if( !p ) fail[u] = 1 ; 
    else { 
      int q = tr[p][x] ;  
      if( len[q] == len[p] + 1 ) fail[u] = q ; 
	  else { 
	    int cq = ++tot ; 
	    fail[cq] = fail[q] ; len[cq] = len[p] + 1 ; 
	    fail[u] = fail[q] = cq ; 
	    memcpy( tr[cq] , tr[q] , sizeof(tr[cq]) ) ; 
	    for( ; p && tr[p][x] == q ; p = fail[p] ) tr[p][x] = cq ;  
	  } 
	} 
	pi[ax] = u ; val[u] = ax ; 
  } 
  void upd( int &k , int l , int r , int x ) { 
    int tk = ++tot2 ; 
	lson[tk] = ls ; rson[tk] = rs ; k = tk ; 
    if( l == r ) { s[k] = 1 ; return ; } 
    int mid=l+r>>1 ; 
    if( x<=mid ) upd( ls , l , mid , x ) ; 
    else upd( rs , mid+1 , r , x ) ; 
    s[k] = s[ls] + s[rs] ; 
  } 
  int merge( int x , int y ) { 
    if( !x || !y ) return x + y ; 
	int k = ++tot2 ; 
	ls = merge( lson[x] , lson[y] ) ; 
	rs = merge( rson[x] , rson[y] ) ; 
	s[k] = s[ls] + s[rs] ; return k ; 
  } 
  int query( int k , int l , int r , int x , int y ) { 
    if( !k || x > y ) return 0 ; 
    if( x <= l && r <= y ) return s[k] ; 
    int mid=l+r>>1 , tp=0 ; 
    if( x<=mid ) tp += query( ls , l , mid , x , y ) ; 
    if( mid<y ) tp += query( rs , mid+1 , r , x , y ) ; 
    return tp ; 
  } 
  void dfs( int x ) { 
    int l = vf[x].size() , y ; 
    fp( i , 0 , l-1 ) { 
      y = vf[x][i] ; dfs( y ) ; 
      rt[x] = merge( rt[x] , rt[y] ) ; 
	} 
	if( val[x] ) upd( rt[x] , 1 , n , in_li[val[x]] ) ;  
  } 
  void build( ) { 
    fp( i , 1 , tot ) vf[fail[i]].push_back(i) ; dfs( 1 ) ; 
  } 
} sa ; 
void add( int x , int y , int z ) { 
  v[x].push_back(y) ; edge[x].push_back(z) ; 
} 
void dfs1( int x , int _fa ) { 
  pre[x] = _fa ; 
  sz[x] = 1 ; 
  dep[x] = dep[_fa] + 1 ; 
  int l = v[x].size() , y , z ;  
  fp( i , 0 , l-1 ) { 
    y = v[x][i] ; z = edge[x][i] ; 
    if( y == _fa ) continue ; 
    a[y] = z ; sa.ins( y , pi[x] , z ) ; 
    dfs1( y , x ) ;   
    sz[x] += sz[y] ; 
    if( sz[son[x]] < sz[y] ) 
      son[x] = y ; 
  } 
} 
void dfs2( int x ) { 
  if( son[x] ) { 
    in_li[son[x]] = ++tot1 ; 
    in_tr[tot1] = son[x] ; 
    top[son[x]] = top[x] ; 
    dfs2( son[x] ) ; 
  } 
  int l = v[x].size() , y ; 
  fp( i , 0 , l-1 ) { 
    y = v[x][i] ; 
    if( y == pre[x] || y == son[x] ) continue ; 
	in_li[y] = ++tot1 ; 
	in_tr[tot1] = y ; top[y] = y ; 
	dfs2( y ) ;  
  } 
} 
int lca( int x , int y ) { 
  int fx = top[x] , fy = top[y] ; 
  while( fx != fy ) { 
    if( dep[fx] < dep[fy] ) swap( x , y ) , swap( fx , fy ) ; 
    x = pre[fx] ; fx = top[x] ; 
  }  
  return ( dep[x] < dep[y] ? x : y ) ; 
} 
int ask_d( int x , int z , int d ) { 
  if( dep[x] - dep[z] + 1 <= d ) return -1 ; 
  int fx = top[x] ; 
  while( fx != top[z] ) {  
    if( dep[fx] <= d + dep[z] ) break ; 
    x = pre[fx] ; fx = top[x] ; 
  } 
  return in_tr[ in_li[fx] + (d-dep[fx]+dep[z]) ] ; 
} 
int ask( int x , int z , int p ) { 
  if( z == -1 ) return 0 ;  
  int fx = top[x] , ans = 0 ;  
  while( fx != top[z] ) { 
    ans += sa.query( p , 1 , n , in_li[fx] , in_li[x] ) ; 
	x = pre[fx] ; fx = top[x] ;  
  } 
  ans += sa.query( p , 1 , n , in_li[z] , in_li[x] ) ; 
  return ans ; 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n ; 
  int x , y ; string z , tp , tp1 , tp2 ;  
  fp( i , 1 , n-1 ) { 
    cin >> x >> y >> z ; 
    add( x , y , z[0]-'a' ) ; add( y , x , z[0]-'a' ) ; 
  } 
  sa.prep( ) ; 
  dfs1( 1 , 0 ) ; 
  in_li[1] = in_tr[1] = top[1] = tot1 = 1 ; 
  dfs2( 1 ) ; 
  sa.build( ) ; 
  int q ; cin >> q ; 
  while( q -- ) { 
    cin >> x >> y >> z ; 
    int ans = 0 , l1 = z.length() , c = lca( x , y ) ; 
    int fx = ask_d( x , c , l1 ) , fy = ask_d( y , c , l1 ) ; 
    int px = 1 , py = 1 ; 
    fq( i , 0 , l1-1 ) px = sa.tr[px][z[i]-'a'] ; 
    fp( i , 0 , l1-1 ) py = sa.tr[py][z[i]-'a'] ; 
	ans = ask( x , fx , sa.rt[px] ) + ask( y , fy , sa.rt[py] ) ; 
	x = ( fx == -1 ? x : pre[fx] ) ; y = ( fy == -1 ? y : pre[fy] ) ; 
	tp1 = "" ; tp2 = "" ; 
	for( ; x != c ; x = pre[x] ) tp1 += (char)(a[x]+'a'); 
	for( ; y != c ; y = pre[y] ) tp2 += (char)(a[y]+'a') ; 
	int l2 = tp2.length() ; 
	fp( i , 1 , l2/2 ) swap( tp2[i-1] , tp2[l2-i] ) ; 
	tp = tp1 + tp2 ; int tl = tp.length() ; 
	tp = " " + tp ; z = " " + z ; 
	int j = 0 ; 
	fp( i , 2 , l1 ) { 
	  while( j && z[j+1] != z[i] ) j = kmp[j] ; 
	  if( z[j+1] == z[i] ) j ++ ; kmp[i] = j ;    
	} 
	j = 0 ; 
	fp( i , 1 , tl ) { 
	  while( j && z[j+1] != tp[i] ) j = kmp[j] ; 
	  if( z[j+1] == tp[i] ) j ++ ; 
	  if( j == l1 ) { ans ++ ; j = kmp[j] ; }  
	} 
	cout << ans << '\n' ; 
  } 
  return 0 ; 
} 
```


---

## 作者：happybob (赞：1)

不会一点字符串算法，考虑哈希。

注意到一个特殊限制是 $\left| s\right| \leq 100$，于是我们可以简单处理出每个点向上不超过 $100$ 步的哈希值。

考虑询问答案时怎么处理。我们考虑 $s$ 在这个串，只有三种。令 $L=\operatorname{LCA}(u,v)$，则这个串要么在 $u \sim L$ 中，要么在 $L \sim v$ 中，要么跨过 $L$。前两种可以转化成树上一条链的某个数出现次数，考虑离线或者在线用树剖和 `vector` 上二分维护。最后一种，可以注意到 $L$ 到两侧的那段多出来的长度不超过 $\left| s\right| \leq 100$，暴力维护即可。

记得用双哈希并且卡常。

```cpp
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
const long long MOD = 998244853ll, MOD2 = 998244353ll;

int n, q;
vector<pair<int, char>> G[N];
struct Two_Hash
{
	int hs1, hs2;
	Two_Hash() = default;
	Two_Hash(int hs1, int hs2) : hs1(hs1), hs2(hs2) {}
	Two_Hash operator+(const int& x) const
	{
		return Two_Hash((hs1 + x) % MOD, (hs2 + x) % MOD2);
	}
	Two_Hash operator*(const int& x) const
	{
		return Two_Hash((hs1 * 1ll * x) % MOD, (hs2 * 1ll * x) % MOD2);
	}
	Two_Hash operator*(const Two_Hash& x) const
	{
		return Two_Hash((1ll * hs1 * x.hs1) % MOD, (1ll * hs2 * x.hs2) % MOD2);
	}
	Two_Hash operator+(const Two_Hash& x) const
	{
		return Two_Hash((hs1 + x.hs1) % MOD, (hs2 + x.hs2) % MOD2);
	}
	bool operator==(const Two_Hash& x) const
	{
		return hs1 == x.hs1 && hs2 == x.hs2;
	}
	void operator=(const int x)
	{
		hs1 = x;
		hs2 = x;
	}
};

struct Myhash
{
	size_t operator()(const Two_Hash& x) const
	{
		return (1ll * x.hs1 * MOD + x.hs2) % MOD2;
	}
};

Two_Hash f[N][101], g[N][101];

int fa[N], nfa[N][21], dis[N];
Two_Hash powe[N];
int dep[N];

static void dfs(int u, int f)
{
	nfa[u][0] = f;
	fa[u] = f;
	dep[u] = dep[f] + 1;
	for (auto& [j, c] : G[u])
	{
		if (j == f) continue;
		::f[j][1] = c - 'a' + 1;
		::g[j][1] = c - 'a' + 1;
		dis[j] = dis[u] + 1;
		dfs(j, u);
	}
}

inline int LCA(int u, int v)
{
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);
	int k(dep[u] - dep[v]), c = 0;
	while (k)
	{
		if (k & 1) u = nfa[u][c];
		k >>= 1, c++;
	}
	if (u == v) return u;
	for (int i = 16; i >= 0; i--)
	{
		if (nfa[u][i] ^ nfa[v][i]) u = nfa[u][i], v = nfa[v][i];
	}
	return nfa[u][0];
}

int id[N], top[N], sz[N], son[N], idx;

class TreeCut
{
public:
	int pp;
	vector<int> dfn;
	unordered_map<Two_Hash, vector<int>, Myhash> pos;
	inline void dfs1(int u, int f)
	{
		fa[u] = f;
		sz[u] = 1;
		dep[u] = dep[f] + 1;
		for (auto& [j, c] : G[u])
		{
			if (j == f) continue;
			dfs1(j, u);
			sz[u] += sz[j];
			if (sz[son[u]] < sz[j]) son[u] = j;
		}
	}
	inline void dfs2(int u, int f)
	{
		top[u] = f;
		id[u] = ++idx;
		dfn.emplace_back(u);
		pos[::f[u][pp]].emplace_back(idx);
		if (!son[u]) return;
		dfs2(son[u], f);
		for (auto& [j, c] : G[u])
		{
			if ((j ^ fa[u]) and (j ^ son[u])) dfs2(j, j);
		}
	}
	inline int qry(int l, int r, Two_Hash v)
	{
		if (!pos.count(v)) return 0;
		return upper_bound(pos[v].begin(), pos[v].end(), r) - lower_bound(pos[v].begin(), pos[v].end(), l);
	}
	inline int query(int u, int v, Two_Hash c)
	{
		int res = 0;
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			res += qry(id[top[u]], id[u], c);
			u = fa[top[u]];
		}
		if (dep[u] > dep[v]) swap(u, v);
		res += qry(id[u], id[v], c);
		return res;
	}
	inline void build(int g)
	{
		pos.clear();
		pp = g;
		if (g == 1) dfs1(1, 1), dfs2(1, 1);
		else
		{
			for (auto& i : dfn) pos[::f[i][pp]].emplace_back(id[i]);
		}
	}
}tc;

inline Two_Hash gethash(string s)
{
	Two_Hash tw;
	tw.hs1 = tw.hs2 = 0;
	for (auto& i : s)
	{
		tw = (tw * 26ll + (i - 'a' + 1));
	}
	return tw;
}

struct Query
{
	int u, v;
	Two_Hash c;
	int id;
	Query() = default;
	Query(int u, int v, Two_Hash c, int id) :u(u), v(v), c(c), id(id) {}
};

vector<Query> vq[105];
int res[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	powe[0] = 1;
	for (int i = 1; i < N; i++) powe[i] = powe[i - 1] * 26ll;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		char c;
		cin >> u >> v >> c;
		G[u].emplace_back(make_pair(v, c));
		G[v].emplace_back(make_pair(u, c));
	}
	dfs(1, 1);
	for (int j = 1; j <= 16; j++)
	{
		for (int i = 1; i <= n; i++) nfa[i][j] = nfa[nfa[i][j - 1]][j - 1];
	}
	auto get_k_fa = [&](int u, int k) -> int
		{
			int c = 0;
			while (k)
			{
				if (k & 1) u = nfa[u][c];
				c++;
				k >>= 1;
			}
			return u;
		};
	auto get_dis = [&](int u, int v) -> int
		{
			return dis[u] + dis[v] - 2 * dis[LCA(u, v)];
		};
	for (int j = 1; j <= 100; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			int ff = get_k_fa(i, j - 1);
			f[i][j] = (f[ff][1] * powe[j - 1] + f[i][j - 1]);
			g[i][j] = (g[i][j - 1] * 26ll + g[ff][1]);
		}
	}
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		int u, v;
		string s;
		cin >> u >> v >> s;
		int L(LCA(u, v));
		Two_Hash rr(gethash(s));
		// L->v
		int rv = v;
		int ans = 0;
		int dul = get_dis(u, L), dul2 = get_dis(v, L), len = s.size();
		if (dul2 <= len)
		{
			int rd(dul2);
			int dd = dul + dul2;
			vector<int> tot;
			for (; v != L; v = fa[v])
			{
				if (dd < len) break;
				dd--;
				tot.emplace_back(v);
				rd--;
			}
			v = L;
			dd = get_dis(v, u);
			int p, npos;
			if (dd >= len)
			{
				tot.emplace_back(L);
				rd--;
			}
			reverse(tot.begin(), tot.end());
			if (tot.empty()) continue;
			p = len - rd - 1;
			npos = get_k_fa(u, dul - p);
			for (auto& v : tot)
			{
				rd++;
				ans += ((g[npos][len - rd] * powe[rd] + f[v][rd]) == rr);
				npos = fa[npos];
			}
		}
		else
		{
			int lens = get_dis(v, L);
			int pos(get_k_fa(v, lens - len - 1));
			vq[len].emplace_back(Query(pos, v, rr, i));
			v = nfa[pos][0];
			int rd = get_dis(v, L);
			int dd = get_dis(v, u);
			vector<int> tot;
			for (; v != L; v = fa[v])
			{
				if (dd < len) break;
				dd--;
				tot.emplace_back(v);
				rd--;
			}
			v = L;
			dd = get_dis(v, u);
			int p, npos;
			if (dd >= len)
			{
				tot.emplace_back(L);
				rd--;
			}
			reverse(tot.begin(), tot.end());
			if (tot.empty()) continue;
			p = len - rd - 1;
			npos = get_k_fa(u, dul - p);
			for (auto& v : tot)
			{
				rd++;
				ans += ((g[npos][len - rd] * powe[rd] + f[v][rd]) == rr);
				npos = fa[npos];
			}
		}
		// L->u
		reverse(s.begin(), s.end());
		v = rv;
		if (dul > len)
		{
			vq[len].emplace_back(Query(u, get_k_fa(u, dul - len - 1), gethash(s), i));
		}
		res[i] = ans;
	}
	for (int i = 1; i <= 100; i++)
	{
		if (!vq[i].size()) continue;
		tc.build(i);
		for (auto& [u, v, c, id] : vq[i])
		{
			res[id] += tc.query(u, v, c);
		}
	} // 1
	for (int i = 1; i <= q; i++) cout << res[i] << "\n";
	return 0;
}
```


---

## 作者：Jsxts_ (赞：0)

来个 ACAM 的。

首先将一条路径拆成在两条链上的和跨过 lca 的。跨过 lca 的较为简单，由于 $|s_i|\le 100$，直接提取出中间长度为 $O(|s_i|)$ 的一段做 kmp 匹配即可。

现在的问题是如何求一个从上往下的链 $u\to v$ 组成的字符串中 $s_k$ 的出现次数 $occ((u,v),s_k)$。考虑容斥成 $occ((1,v),s_k)-occ((1,u),s_k)$ 再减去左右端点跨过 $u$ 的方案数。这个和上面跨过 lca 的类似。

那么求一条到根链中 $s_k$ 的出现次数可以离线建出 $s$ 的 ACAM，然后 dfs 原树，在 ACAM 上匹配，将走到的节点权值 $+1$，查询就是求 $s_k$ 在 ACAM 上的结束节点的子树权值和，用树状数组维护。发现 $u\to lca$ 这一段是反过来走的，所以还要建出 $s$ 的反串 ACAM，用反串在上面也匹配即可。

然而有一个很严重的问题：空间达到了 $(\sum|s_k|)\times |\sum| \times 2=5.2\times 10^8$，完全开不下。于是我们将询问分批次处理，每 $B$ 个询问重新建树，取 $B=5000$ 即可通过。注意 vector 清空时不能只 clear，要将内存释放出去。

复杂度：$O(\frac{n^2}{B}\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,q,head[N + 10],cnt,ch[N + 10];
struct edge {
	int v,w,nxt;
}ed[N * 2 + 10];
void add(int u,int v,int w) {
	ed[++cnt] = {v,w,head[u]};
	head[u] = cnt;
}
int dfn[N + 10],tot,dep[N + 10],son[N + 10],sz[N + 10],fa[N + 10],top[N + 10],rnk[N + 10];
void dfs(int x,int f) {
	sz[x] = 1, fa[x] = f;
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == f) continue;
		dep[v] = dep[x] + 1;
		ch[v] = ed[i].w;
		dfs(v,x);
		sz[x] += sz[v];
		if (sz[son[x]] < sz[v]) son[x] = v;
	}
}
void dfs2(int x,int tp) {
	top[x] = tp, dfn[x] = ++tot, rnk[tot] = x;
	if (son[x]) dfs2(son[x],tp);
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == fa[x] || v == son[x]) continue;
		dfs2(v,v);
	} 
}
int LCA(int x,int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
int kth(int x,int k) {
	if (k <= 0) return x;
	while (1) {
		if (k <= dep[x] - dep[top[x]]) return rnk[dfn[x] - k];
		else k -= dep[x] - dep[top[x]] + 1, x = fa[top[x]];
	}
	assert(0);
}
struct KMP {
	int p[N + 10];
	int solve(char *t,char *s) {//occur(t,s)
		int ls = strlen(s),lt = strlen(t);
		if (lt < ls) return 0;
		p[0] = -1;
		for (int i = 1,j = -1;i < ls;i ++ ) {
			while (~j && s[j + 1] != s[i]) j = p[j];
			if (s[j + 1] == s[i]) j ++;
			p[i] = j;
		}
		int res = 0;
		for (int i = 0,j = -1;i < lt;i ++ ) {
			while (~j && s[j + 1] != t[i]) j = p[j];
			if (s[j + 1] == t[i]) j ++;
			if (j == ls - 1) res ++ , j = p[j];
		}
		return res;
	}
}kmp;
int ans[N + 10];
const int B = 20;
const int M = N * 100 / B;
struct ACAM {
	int ch[M + 10][26],End[M + 10],tot;
	void ins(char *s,int id) {
		int l = strlen(s),u = 0;
		for (int i = 0;i < l;i ++ ) {
			int x = s[i] - 'a';
			if (!ch[u][x]) ch[u][x] = ++tot;
			u = ch[u][x];
		}
		End[id] = u;
	}
	int fail[M + 10],tt,dfn[M + 10],low[M + 10];
	int head[M + 10],cnt;
	vector<pair<int,int> > vc[N + 10];
	struct edge {
		int v,nxt;
	}ed[M + 10];
	void add(int u,int v) {
		ed[++cnt] = {v,head[u]};
		head[u] = cnt;
	}
	void dfs(int x) {
		dfn[x] = ++tt;
		for (int i = head[x];i;i = ed[i].nxt) dfs(ed[i].v);
		low[x] = tt;
	}
	int c[M + 10];
	void upd(int x,int s) {
		for (;x <= tot + 1;x += (x & -x)) c[x] += s;
	}
	int getsum(int x) {
		int res = 0;
		for (;x;x -= (x & -x)) res += c[x];
		return res;
	}
	int ask(int x) {
		return getsum(low[End[x]]) - getsum(dfn[End[x]] - 1);
	}
	void build() {
		queue<int> q;
		for (int i = 0;i < 26;i ++ )
			if (ch[0][i]) q.push(ch[0][i]), fail[ch[0][i]] = 0;
		while (!q.empty()) {
			int u = q.front();q.pop();
			for (int i = 0;i < 26;i ++ )
				if (ch[u][i]) fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
				else ch[u][i] = ch[fail[u]][i];
		}
		for (int i = 1;i <= tot;i ++ ) add(fail[i],i);
		dfs(0);
	}
	void init() {
		memset(fail,0,sizeof(int)*(tot+1));
		for (int i = 0;i <= tot;i ++ )
			for (int j = 0;j < 26;j ++ ) ch[i][j] = 0;
		memset(head,0,sizeof(int)*(tot+1));
		tot = cnt = tt = 0;
	}
}T[2];
void dfs3(int x,int u0,int u1) {
	T[0].upd(T[0].dfn[u0],1), T[1].upd(T[1].dfn[u1],1);
	for (auto v : T[0].vc[x]) ans[v.x] += v.y * T[0].ask(v.x);
	for (auto v : T[1].vc[x]) ans[v.x] += v.y * T[1].ask(v.x);
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == fa[x]) continue;
		dfs3(v,T[0].ch[u0][ch[v]],T[1].ch[u1][ch[v]]);
	}
	T[0].upd(T[0].dfn[u0],-1), T[1].upd(T[1].dfn[u1],-1);
}
char s[N + 10],t[N + 10];
int main() {
	n = read();
	for (int i = 1;i < n;i ++ ) {
		int u = read(),v = read();
		char ch[2];scanf("%s",ch);
		add(u,v,ch[0] - 'a'), add(v,u,ch[0] - 'a');
	}
	dfs(1,0), dfs2(1,1);
	q = read();
	for (int i = 1;i <= B;i ++ ) {
		if (q <= (i - 1) * N / B) return 0;
		T[0].init(), T[1].init();
		for (int i = 1;i <= n;i ++ ) {
			T[1].vc[i].clear(), T[0].vc[i].clear();
			T[1].vc[i].shrink_to_fit(), T[0].vc[i].shrink_to_fit();
		}
		for (int j = 1;j <= min(N / B,q - (i - 1) * N / B);j ++ ) {
			int u = read(),v = read();
			scanf("%s",s);
			int l = strlen(s);
			T[0].ins(s,j);
			reverse(s,s + l);
			T[1].ins(s,j);
			int lca = LCA(u,v),tt = 0;
			T[1].vc[u].push_back({j,1});
			if (lca != 1) T[1].vc[lca].push_back({j,-1});
			T[0].vc[v].push_back({j,1});
			if (lca != 1) T[0].vc[lca].push_back({j,-1});
			if (l == 1) continue;
			int p = kth(u,dep[u] - dep[lca] - l + 1),tp = p,q;
			tt = 0;
			for (;tp != 1 && dep[lca] - dep[tp] < l - 1;tp = fa[tp]) t[tt++] = ch[tp] + 'a';
			reverse(t,t + tt);
			t[tt] = '\0';
			ans[j] -= kmp.solve(t,s);
			reverse(s,s + l);
			q = kth(v,dep[v] - dep[lca] - l + 1),tp = q;
			tt = 0;
			for (;tp != 1 && dep[lca] - dep[tp] < l - 1;tp = fa[tp]) t[tt++] = ch[tp] + 'a';
			reverse(t,t + tt);
			t[tt] = '\0';
			ans[j] -= kmp.solve(t,s);
			tt = 0;
			for (tp = p;tp != lca;tp = fa[tp]) t[tt++] = ch[tp] + 'a';
			int tmp = tt;
			for (tp = q;tp != lca;tp = fa[tp]) t[tt++] = ch[tp] + 'a';
			reverse(t + tmp,t + tt);
			t[tt] = '\0';
			ans[j] += kmp.solve(t,s);
		}
		T[0].build(), T[1].build();
		dfs3(1,0,0);
		for (int j = 1;j <= min(N / B,q - (i - 1) * N / B);j ++ ) printf("%d\n",ans[j]), ans[j] = 0;
	}
	return 0;
}
```


---

## 作者：fjy666 (赞：0)

## 题意简述  
给定一棵大小为 $n$ 的树，边有边权，边权为小写字母。  
$q$ 次询问，每次给出 $u,v$ 和一个字符串 $S$，询问 $S$ 在 $u\to v$ 组成的字符串中出现了多少次。

## 做法

给出一个**在线**做法。  
首先很容易把这个字符串在 $u\to v$ 的出现分为三种情况（令 $\operatorname{LCA}(u,v)=l$）：  

1. 在 $u\to l$ 中出现
2. 经过 $l$  
3. 在 $l\to v$ 中出现

最容易考虑的是 $l\to v$。我们直接给整棵树建广义后缀自动机，然后线段树合并维护 $\operatorname{endpos}$ 即可。（实现上线段树维护的 $\operatorname{endpos}$ 是 $\texttt{dfs}$ 序，因为要使用树剖查询）。

然后是经过 $l$ 的。容易发现这一部分总长不超过 $2|S|$，因此暴力 KMP 匹配即可。  

最后是 $u\to l$。相当于把整条路径反转再去和 $S$ 匹配。但我们不会反转。因此我们把 $S$ 反转去和 $u\to l$ 匹配。

时间复杂度 $\mathcal{O}(n(\log ^2n+|S|))$。哈希狗都不写。但是我也不知道为啥我写了 [6.70KB](https://codeforces.com/contest/1045/submission/216686768)。

---

