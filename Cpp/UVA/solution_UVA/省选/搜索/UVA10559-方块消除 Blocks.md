# 方块消除 Blocks

## 题目描述

有 $n$ 个带有颜色的方块，没消除一段长度为x的连续的相同颜色的方块可以得到 $x^2$ 的分数，让你用一种最优的顺序消除所有方块使得得分最多。

## 样例 #1

### 输入

```
2
9
1 2 2 2 2 3 3 3 1
1
1```

### 输出

```
Case 1: 29
Case 2: 1```

# 题解

## 作者：BackSlashDelta (赞：75)

# [❮UVA10559❯](/problem/UVA10559)

## ➤ 闲言

奈何本人愚笨，愣是被这道题卡了近一天。看过了大佬们的题解之后还是不能太理解。最后还不得不结合了[这里](https://www.programmersought.com/article/72662101294/)才终于算是理解了怎么做和为什么这么做。所以写篇题解加深印象，顺便帮助他人理解。

**须知**：缩进级以内的内容为辅助理解内容，不是必要的，理解了可以跳过。本题解讲的较为详细，需要耐心阅读。标题仅仅表示段落内的主要内容，为理解通透建议联系上下段或通读全文。标题前面的特殊符号没有任何其他意思，仅仅用于区分标题等级。本人 $\LaTeX$ 技巧不行，只能使用图片来弥补，还请见谅。

## ➤ 题面

给定一个序列，序列上的每个格子都有（且只有）一种颜色。连续的具有相同颜色的格子可以被消去，并获得消去的子区间长度的平方的贡献。且被消去的子区间两端的子区间会被连接。求最大贡献。多组数据。

> ![Sample](https://cdn.luogu.com.cn/upload/image_hosting/u4va6z0k.png)

## ➤ 题解

### ❖ 升维

首先不难发现：贪心的策略是错误的。因为我们可以先消除一些不符合贪心策略的区间来使得一些小区间合并成大区间并获取更多的贡献。因此，考虑**区间 DP**。

依照传统思维，我们使用 ``dp[begin][end]`` 来表示消去子区间 ``a[begin]`` 到 ``a[end]`` 的最大贡献。但是如果你有尝试推导，你就会发现——贡献不是简单相加或者相乘，而是乘方相加，且乘方随长度改变而改变。这大大提升了转移的难度。（至少我没做出来，我不知道有没有人可以二维转移）。因此我们考虑：**加入维度**。

### ❖ 方程

思考：如果我们找到了一段颜色相同且连续的区间，我们可以：（一）**消去它**，获得贡献，并连接它两边的区间（二）**保留它**，等待它两边的区间被消去以和其他相同颜色的区间合并成更大的区间。考虑第二种情况：我们保留当前区间（假定当前区间颜色唯一），并找到当前区间右边的、和当前区间颜色相同且不与当前区间连续的另一个区间（假定存在），我们**消去这两个区间夹住的区间，合并两个目标区间**并消除以获得贡献。

> 于是刚才这么大段话应该长这样：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/2nhdbzfz.png)

那我们多开两维来记录下标吗？可以，但没必要。而且我们可能会和多个不连续的区间合并以得到更大的贡献。观察到贡献与位置无关，而且记录下标的目的就是为了计算长度，我们考虑：**新增一维，用于记录我们在当前区间右侧保留的准备和当前区间一起消除的区间的长度**。表示为：``dp[begin][end][rExt]``

考虑到区间内可能并**不一定颜色唯一**，我们**以** ``a[end]`` **为“标准“**。也就是说：我们用 ``dp[begin][end][rExt]`` 表示对于当前区间 ``a[begin]`` 至 ``a[end]``，在该区间右侧（不包括 ``end``）有数量为 ``rExt`` 的与 ``a[end]`` 颜色相同的格子会和 ``a[end]`` 一起消除。所以状态  ``dp[begin][end][rExt = 5]`` 长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/rr2okjxo.png)

> 当然，上面的只是一个例子。在那个例子中，后面还有两个 ``4`` 没有被状态包含（也就是我们不合并那两个 ``4``），所以还会肯定还有状态 ``dp[begin][end][rExt = 7]``，长这样：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/iltyan6n.png)
>
> 相应的，状态 ``dp[begin][end][rExt = 0]`` 表示仅仅消除当前区间，不涉及后面的任何东西。长这样：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/hu8lhl7v.png)

### ❖ 转移

还记得我们的两种选择吗？是的，**保留**或**消除**。于是我们猜想：也会有保留和消除的**两种转移**。

#### ✜ 消除

依然是考虑到区间内可能并**不一定颜色唯一**，既然之前以 ``a[end]`` 为“标准”，不妨就消去 ``a[end]``。但是想想就知道，单纯的消去 ``a[end]`` 这一个位置一定不会更优，那我们就消除一个区间。区间都是有个长度的，上面我们已经处理完了“标准”右侧的事情，那么看看左边。我们以 ``a[end]`` 向左蔓延，令 ``lExt`` 表示 ``a[end]`` 向左蔓延能找到的**最“远”的、不超过左端点** ``begin`` **的点**。

> 举几个例子：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/qs5a16gj.png)
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/leym342d.png)

我们有了标准点（``a[end]``）、标准点左端长度（``lExt``）和标准点右端长度（``rExt``），整个准备消除的区间的长度就可以计算了——贡献也能计算了。但是**贡献的出现一定意味着状态的变化**。消除完这个区间后，这个区间就不复存在了（``rExt`` 只要有值，就意味着会消除夹在两目标区间中的所有值，这个在定义中已经讲明。关于这个的转移会在接下来的  ✜ 保留  中讲到），因此**剩下的区间就是** ``a[begin]`` **到** ``a[lExt - 1]``。那么转移就出来了：（``Sqr(x)`` 表示 ``x`` 的平方，即 ``x * x``）

```cpp
dp[begin][end][rExt] <={ dp[begin][lExt - 1][0] + Sqr((end - lExt + 1) + rExt) }
```

#### ✜ 保留

相应的，我们也要考虑如果保留这段区间我们的贡献从何而来。既然保留这一段区间，我们肯定需要在当前区间内**找到一个和“标准”同色的来进行转移**，因为只有这样才有可能**合并区间以使得答案更优**。不然为什么不直接执行刚才消除的操作呢？反正留到最后也没有使它的贡献变大，留着干啥？同时为了保证答案更优，且转移次数更少，我们在找到了同色区间的最右端点时再转移。于是我们找到了保留的转移的限制条件。

```cpp
If (a[brkp] == a[end] && a[brkp] != a[brkp + 1])
```

既然是找到了一个同色的，那我们就以该点为断点（``brkp``），将序列分割为两部分：从 ``a[begin]`` 到 ``a[brkp]``、从 ``a[brkp + 1]`` 到 ``a[lExt - 1]``（因为我们已经确定 ``lExt`` 是和右边一起消去的，所以不必枚举到更右边的位置）。因为是保留，所以没有额外贡献，于是转移出来了：

```cpp
                      /{ dp[begin, brkp, end - lExt + 1 + rExt] }
dp[begin][end][rExt] <={                    +                   }
                      \{        dp[brkp + 1, lExt - 1, 0]       }
```

### ❖ 实现

> 为了方便，我使用了记忆化搜索的架构。

```cpp
inline int DDFS(int begin, int end, int rExt) {
  if (begin > end) {  // 不合法区间，
    return 0;         // 返回一个不影响答案的 0
  }
  if (dp[begin][end][rExt]) {     // 该区间已经有值了，
    return dp[begin][end][rExt];  // 返回该值，不必再算
  }
  int lExt = end;                               // 游标准备，
  while (begin <= lExt && a[lExt] == a[end]) {  // 向左蔓延！
    lExt--;
  }
  lExt++;  // 回弹一格，因为肯定是不合法时才弹出的
  dp[begin][end][rExt] = DDFS(begin, lExt - 1, 0) + Sqr(end - lExt + 1 + rExt);  // “消除”转移
  for (int brkp = begin; brkp < lExt; brkp++) {  // 枚举断点
    if (a[brkp] == a[end] && a[brkp] != a[brkp + 1]) {  // “保留”的限制与转移
      dp[begin][end][rExt] = std::max(dp[begin][end][rExt], 
                                      DDFS(begin, brkp, end - lExt + 1 + rExt)
                                      + DDFS(brkp + 1, lExt - 1, 0));
    }
  }
  return dp[begin][end][rExt];  // 返回答案
}
```

至于答案，应该不用我说。

> 状态 ``dp[1][n][0]`` 表示对于区间 ``1~n``，右端不保留（~~你也没法保留~~）的最大贡献。



---

## 作者：eternal风度 (赞：30)

## 区间dp

很好的一道**区间dp**的题目(别问我怎么想到的)

同步发表于[Blocks题解(我的博客里)](https://www.cnblogs.com/cjoierljl/p/9685927.html)

可以去我的博客逛一逛的。。。[eternal风度的博客](https://www.cnblogs.com/cjoierljl/)

### dp状态

其实这个题最难的地方是这道题目的状态怎么设

- 首先既然是区间dp，那肯定最先想到的状态是
 
 > $dp[i][j]$表示消掉区间$[i,j]$上所有的块的最大分数
 
- 突然发现这个状态会受区间外和$i$或$j$颜色相同的块的影响
  
  并且转移也并不好转移=_=

- 所以我们考虑换一种状态。。。
  
  既然说会受到外面的块的影响？那考虑一种方法来解决
  
 > $dp[i][j][k]$表示消掉区间$[i,j]$并且区间$[i,j]$右边还有k个和j颜色相同的块（除此之外，这个序列没有别的块了），消掉这些所有的块的最大分数
 
  有点抽象，再来感性理解一下：
  >  当前处理的子问题$dp[i][j][k]$主体由区间$[i,j]$组成，然后与$j$相同有$k$块接在后面，这$k$块之间的其他块已经全部消完了
  
- 如果实在还不明白，先看转移吧。。。
  然后可以根据我们前面的错误状态自己思考为什么加上这一维
  
### 转移

$dp[i][j][k]$:显然有两种转移

我这里是用记忆化搜索实现的

> 1. 消掉j和后面的k块
```
	dp[i][j][k]=max(dp[i][j][k],Dfs(i,j-1,0)+(k+1)*(k+1));
```

> 2. 对于区间$[i,j]$，中间可能有和$j$颜色相同的块，假设位置为$p$，我们可以选择消掉区间$[p+1,j-1]$中所有的块使颜色拼起来，当然这是个子问题，所以前面讲了用记忆化搜索实现

> 	PS: 下面代码的$nxt[p]$是预处理的在$p$前面第一个和$p$颜色相同的块的位置

```
	for(int p=nxt[j];p>=i;p=nxt[p])//枚举p
		dp[i][j][k]=max(dp[i][j][k],Dfs(i,p,k+1)+Dfs(p+1,j-1,0));
```

### 汇总

讲完这些整个程序的实现就不难了

那我直接放上代码，~~不好意思，没有注释~~

```
#include<bits/stdc++.h>
#define lst long long
#define ldb double
#define N 250
using namespace std;
const int Inf=1e9;
int read()
{
	int s=0,m=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')m=1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}

int n;
int col[N],nxt[N],hd[N];
lst dp[N][N][N];//消掉[i,j]区间和[i,j]右边和j颜色一样的连续k个方块的最大分数

lst Dfs(int i,int j,int k)
{
	if(i>j)return 0;
	if(dp[i][j][k])return dp[i][j][k];
	dp[i][j][k]=max(dp[i][j][k],Dfs(i,j-1,0)+(k+1)*(k+1));
	for(int p=nxt[j];p>=i;p=nxt[p])
		dp[i][j][k]=max(dp[i][j][k],Dfs(i,p,k+1)+Dfs(p+1,j-1,0));
	return dp[i][j][k];
}

int main()
{
	int T=read();
	for(int tt=1;tt<=T;++tt)
	{
		n=read();
		memset(hd,0,sizeof(hd));
		memset(dp,0,sizeof(dp));
		memset(nxt,0,sizeof(nxt));
		for(int i=1;i<=n;++i)
		{
			col[i]=read();
			nxt[i]=hd[col[i]];
			hd[col[i]]=i;
		}
		printf("Case %d: %lld\n",tt,Dfs(1,n,0));
	}
	return 0;
}

```

---

## 作者：Froranzen (赞：12)

### [题目传送门](https://www.luogu.com.cn/problem/UVA10559)

------------
## 思路

------------
求一个区间内分数的最大值，我们容易想到用**区间dp**来做这道题。

首先，我们来定义一下数组： 

$dp[l][r]$ 表示 将 $l$~$r$ 这段区间消除得到的最大分数值。   
$color[l]$ 表示 $l$ 这段区间的颜色。  
$len[l]$ 表示 $l$ 这段区间的长度。

我们要在输入时预处理一下各个数组。

------------

```cpp
	cnt = 0; 
	for (register int i(1); i <= n; ++i) {
		_now = read (); //读入当前颜色
		if (_now == last) {  //和上一个颜色相同
			len[cnt]++;  //区间长度+1
		}
		else {
			color[++cnt] = _now;  //否则，新开一个区间
			len[cnt]++;  //区间长度+1
		}
		last = _now;  //更新
	}
```
------------


但是在写代码时，我们发现：如果在 $r$ 后面有一段长度为 $k$ 的区间颜色和 $r$ 区间 一样，那么在消除 $l$~$r$ 区间时，会顺带着把 $k$ 区间也消除了。所以我们就加上一维数组来维护这个 $k$ ：

$dp[l][r][k]$ 表示 **消除 $l$~$r$ 这段区间且在 $r$区间 后有 $k$ 个与 $r$ 区间颜色相同的方块的最大分数值**。

接下来我们考虑**状态的转移**。

1. 首先，我们可以直接消除 $r$ 这一段区间，再加上消除 $l$ ~ $r-1$ 区间的最大值，那么转移方程就为：
	$$dp[l][r][k] = dp[l][r-1][0] + (len[r] + k)^2$$
2. 其次，我们可以枚举 $l$~$r$ 间的一段区间 $i$，使 $i$ 区间的颜色与 $r$ 区间的颜色相同，然后我们可以先消除 $i+1$ ~ $r-1$ 区间。这样的话， 就可以将 $r$ 和 $i$ 两个区间合并成一个颜色相同的区间，然后再计算消除 $l$~$i$ 区间的最大值，那么转移方程就为： 
	$$dp[l][r][k] = max (dp[l][i][len[r] + k] + dp[i +1][r -1][0])$$
3. 当然，$l == r$ 时，我们直接返回 $(len[r]+k) ^2$ 即可。

------------

## 代码

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

inline char nc () {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 100000, stdin), p1 == p2) ? EOF :*p1++;
}

inline int read () {
	register int x(0), f(1);
	char ch = nc ();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = ~f +1;
		ch = nc ();
	}
	while (ch <= '9' && ch >= '0') {
		x = (x << 3) + (x << 1) + (ch ^48);
		ch = nc ();
	}
	return x *f;
}
 
inline int max (int a, int b) {
	return a > b ? a :b;
}

int n;
int color[205];
int len[205];
int qwq[205][205][555];
int _now, last;
int cnt;

int dfs (int l, int r, int k) {
	if (qwq[l][r][k]) return qwq[l][r][k];
	if (l == r) return (len[r] + k) * (len[r] + k);
	qwq[l][r][k] = dfs (l, r - 1, 0) + (len[r] + k) * (len[r] + k);
	for (register int i(l); i < r - 1; ++i)
		if (color[i] == color[r])
			qwq[l][r][k] = max (qwq[l][r][k], dfs (l, i, len[r] + k) + dfs (i + 1, r - 1, 0));
	return qwq[l][r][k];
}

int t;

int main () {
	t = read ();
	for (register int a(1); a <= t; ++a) {
		n = read ();
		memset (qwq, 0, sizeof (qwq));
		memset (color, 0, sizeof (color));
		memset (len, 0, sizeof (len));
		cnt = 0;
		last = -1;
		for (register int i(1); i <= n; ++i) {
			_now = read ();
			if (_now == last) {
				len[cnt]++;
			}
			else {
				color[++cnt] = _now;
				len[cnt]++;
			}
			last = _now;
		}
		printf ("Case %d: %d\n", a, dfs (1, cnt, 0));
	}
	return 0;
}
```

------------
（悄悄[要个关注](https://www.luogu.com.cn/user/361432)不过分吧, qwq）


---

## 作者：Itst (赞：10)

### DP好题，~~方程NB~~，上午还是蓝色下午就变紫了
### 看完题就知道是区间DP，设状态为$f_{i,j}$，然后考虑转移的时候发现：中间可能有一部分零散的和两端相同颜色的块，转移十分麻烦
### 于是考虑~~神奇~~状态：$f_{i,j,k}$，其中$i,j$同上，$k$表示 _在块$j$之后有且仅有$k$个与块$j$相同颜色的块_
### 考虑转移：分两种情况
### $a.$把最后$k+1$个一起消掉，由$f_{i,j-1,0}+(k+1)^2$转移
### $b.$在$[i,j-1]$中取一个块$m$满足$color_m=color_j$，将它们中间的元素消掉，也就是由$f_{m+1,j-1,0}+f_{i,m,k_1}$转移
### 将以上转移取$max$即可
### ~~关于为什么是对的就感性理解一下吧~~
### 一定要注意转移顺序啊$qwq$
### 时间复杂度是$O(n^4)$竟然$100ms$跑过了
```
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return a;
}

inline int max(int a , int b){
    return a > b ? a : b;
}

int ans[201][201][201] , col[201] , dis[201];

int main(){
    int T = read();
    for(int i = 1 ; i <= T ; i++){
        int N = read();
        memset(ans , 0 , sizeof(ans));
        memset(dis , 0 , sizeof(dis));
        for(int j = 1 ; j <= N ; j++)
            col[j] = read();
        for(int j = N ; j ; j--)
            for(int k = j + 1 ; k <= N ; k++)
                if(col[j] == col[k])
                    dis[j]++;
        for(int j = N ; j ; j--)
            for(int k = j ; k <= N ; k++){
                for(int q = j ; q < k ; q++)
                //转移顺序很重要！
                    if(col[q] == col[k])
                        for(int p = 0 ; p <= dis[k] ; p++)
                            ans[j][k][p] = max(ans[j][k][p] , ans[q + 1][k - 1][0] + ans[j][q][p + 1]);
                for(int p = 0 ; p <= dis[k] ; p++)
                    ans[j][k][p] = max(ans[j][k][p] , ans[j][k - 1][0] + (p + 1) * (p + 1));
            }
        printf("Case %d: %d\n" , i , ans[1][N][0]);
    }
    return 0;
}
```

---

## 作者：zfz04 (赞：8)

[[传送门]](https://www.luogu.com.cn/problem/UVA10559)

设$f[i][j][k]$表示区间$[i,j]$ ,$j$右边有**连续**$k$个与$j$相同的色块消除后的最大分数；

**PS:** 这里的连续是指在消除某些方块后的连续；而并非指输入的方块色的连续；所以统计j右边所有与之相同的色块都要统计到；

所以就有两种转移：

1.  将j和j右边的连续的k个一起消掉，则有:

$f[i][j][k]=max(f[i][j][k],f[i][j-1][0]+(k+1))^2$；

1. 在区间$[i,j]$里找到一个色块$p$与色块j的颜色相同，将$j$与$p$之间的色块消除使之连接，然后在将他们一起消除，则有:

$f[i][j][k]=max(f[i][j][k],f[p+1][j-1][0]+f[i][p][k+1])(color(p)==color(j))$；


------------


## code


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,t;
int a[205],sum[4][205],f[205][205][205];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(sum,0,sizeof(sum));
		memset(f,0,sizeof(f));
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum[1][i]=sum[1][i-1];
			sum[2][i]=sum[2][i-1];
			sum[3][i]=sum[3][i-1];
			sum[a[i]][i]++;
		}
		
		for(int i=n;i>=1;i--)
			for(int j=i;j<=n;j++)
			{
				for(int p=i;p<j;++p)
					if(a[p]==a[j])
						for(int k=0;k<=sum[a[j]][n]-sum[a[j]][j];k++)
							f[i][j][k]=max(f[i][j][k],f[i][p][k+1]+f[p+1][j-1][0]);
				for(int k=0;k<=sum[a[j]][n]-sum[a[j]][j];k++)
					f[i][j][k]=max(f[i][j][k],f[i][j-1][0]+(k+1)*(k+1));
			}		
		printf("%d\n",f[1][n][0]);	
	}		
	return 0;
}
```


------------


然而，机房某大佬构造出5个毒瘤数据，虽然n只有105，更小了，但是如果按照这样写的话就会T飞掉；

所以这里把普通for循环的写法该成种记忆化搜索的写法，减少一下不必要的状态，再加个链表；
于是就有了：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=105;
int nex[N],head[N];
int t,n;
ll f[N][N][N];
int a[N];
ll dfs(int i,int j,int k)
{
	if(i>j) return 0;
	if(f[i][j][k]) return f[i][j][k];
	int p=j;
	while(p>=i&&a[p]==a[j]) p--;
	p++;
	f[i][j][k]=max(f[i][j][k],dfs(i,p-1,0)+(j-p+k+1)*(j-p+k+1));
	for(int s=p-1;s>=i;s--)
		if(a[s]!=a[s+1]&&a[s]==a[j])
			f[i][j][k]=max(f[i][j][k],dfs(i,s,j-p+k+1)+dfs(s+1,p-1,0));
	return f[i][j][k];
}
int main()
{
	scanf("%d",&t);
	for(int k=1;k<=t;k++)
	{
		memset(nex,0,sizeof(nex));
		memset(f,0,sizeof(f));
		memset(head,0,sizeof(head));
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			nex[i]=head[a[i]];
			head[a[i]]=i;
		}
		printf("%lld\n",dfs(1,n,0));
	}
	return 0;
}
```


------------

噫，好，就对了一个点，其他还是T飞；

那再考虑优化；

正当我想的焦头烂额的时候，这时又一位机房大佬过来指点我；

对于一串连续（这里的连续就是输入时的连续）的相同色块，可以把它们看成一个色块；这样就可以消除很多冗杂的状态；

于是就有了下面的AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=105;
int nex[N],head[N];
int t,n;
int f[N][N][N];
int a[N];
int dfs(int i,int j,int k)
{
	if(i>j) return 0;
	if(f[i][j][k]) return f[i][j][k];
	int p=j;
	while(p>=i&&a[p]==a[j]) p--;
	p++;
	f[i][j][k]=max(f[i][j][k],dfs(i,p-1,0)+(j-p+k+1)*(j-p+k+1));
	for(int s=nex[p];s>=i;s=nex[s])
		if(a[s]!=a[s+1])
			f[i][j][k]=max(f[i][j][k],dfs(i,s,j-p+k+1)+dfs(s+1,p-1,0));
	return f[i][j][k];
}
int main()
{
	scanf("%d",&t);
	for(int k=1;k<=t;k++)
	{
		memset(nex,0,sizeof(nex));
		memset(f,0,sizeof(f));
		memset(head,0,sizeof(head));
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			nex[i]=head[a[i]];
			head[a[i]]=i;
		}
		printf("%lld\n",dfs(1,n,0));
	}
	return 0;
}
```
嗯，这时三次提交的对比：

![](https://cdn.luogu.com.cn/upload/image_hosting/0th92qy3.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9ve520p9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9ddpkyjr.png)

发现时间上快了不止一点点，所以让我们一起来膜拜大佬：

[提出优化的大佬——法老pharaoh420](https://www.luogu.com.cn/user/49777)

[构造毒瘤数据的罪魁祸首——lyyi2003](https://www.luogu.com.cn/user/100806)


---

## 作者：wuzhaoxin (赞：5)

- 设f[i][j][k]表示处理区间[i,j]，且在区间右边还有k个和j同色的方块，消除所有这些的最大分数。考虑转移。
- 1.将右端点和多出的k个一起消掉，分数为f[i][j-1][0]+(k+1)^2
- 2.选一个和右端点同色的点p，消掉[p+1,j-1]使得p、j相邻，分数为f[i][p][k+1]+f[p+1][j-1][0]。
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[201][201][201];
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    for(int t1=1;t1<=t;t1++)
    {
    	memset(dp,0,sizeof(dp));
    	int n;
    	int a[201];
    	cin>>n;
    	for(int i=1;i<=n;i++)
    		cin>>a[i];
    	for(int i=0;i<n;i++)
    		for(int j=i+1;j<=n;j++)
    			for(int k=0;k<=n-j;k++)
    			{
    				dp[j-i][j][k]=max(dp[j-i][j][k],dp[j-i][j-1][0]+(k+1)*(k+1));
    				if(j==3&&i==2)
    					printf("");
    				for(int p=j-i;p<j;p++)
    					if(a[p]==a[j])dp[j-i][j][k]=max(dp[j-i][j][k],dp[j-i][p][k+1]+dp[p+1][j-1][0]);
    			}
    	cout<<"Case "<<t1<<": "<<dp[1][n][0]<<endl;
    }
    return 0;
}
```

---

## 作者：Drimpossible (赞：4)

# UVA10559
题意已经非常明确，不再赘述。

**因为这道题满足可以从小区间到大区间的递推，所以考虑区间 $DP$** 。
### 状态：
 $dp[i][j][k]$ 表示 $[i,j]$ 区间后还有一段长度为 $k$ 与 $j$ 颜色相同的一段所能得到的最大得分。
### 方程：
1.消除 $j~k$ 这一段，即为 $dp[i][j][k]=dp[i][j-1][0]+(b[j]+k)*(b[j]+k)$ 。

2.在 $i~j$ 这一段中找一个与 $j$ 颜色相同的点 $c$ ，先消除 $[c+1,j-1]$ 这一段，再让 $[j,k]$ 这一段接到 $c$ 后面，即为 $dp[i][j][c]=max(dp[i][j][c],dp[i][l][b[j]+c]+dp[l+1][j-1][0])$ 。

答案即为 $dp[1][n][0]$ 。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[501][501][501],a[501],b[501],d[501],n,m,sum[501],t;
signed main(){
	cin>>t;
	int x=1;
	while(t--){
		scanf("%d",&m);
		n=0;
		for(int i=1;i<=m;i++)scanf("%d",&d[i]);
		int cnt=0;
		for(int i=1;i<=m;i++){//将原串处理为颜色和颜色长度，方便DP
			cnt++;
			if(d[i]!=d[i+1]){
				a[++n]=d[i];
				b[n]=cnt;
				cnt=0;
			}
		}
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
		for(int l=0;l<=n;l++){
			for(int i=1;i<=n;i++){
				int j=i+l;
				if(j>n)break;
				for(int k=0;k<=sum[n]-sum[j-1];k++){//情况1赋初始值
					dp[i][j][k]=dp[i][j-1][0]+(b[j]+k)*(b[j]+k);
				}
				for(int k=i;k<j;k++){
					for(int c=0;c<=sum[n]-sum[j-1];c++){情况2 DP
						if(a[k]==a[j])
						dp[i][j][c]=max(dp[i][j][c],dp[i][k][b[j]+c]+dp[k+1][j-1][0]);
					}
				}
			}
		}
		printf("Case %d: %d\n",x,dp[1][n][0]);x++;
	}
	return 0;
}
```

---

## 作者：ltdj (赞：4)

[消除方块 传送门](https://www.luogu.com.cn/problem/UVA10559 "消除方块 传送门")

~~看了看题解区好像没有这样的解法？~~
## 分析



------------

### 状态（重点）

这是一种比较懒癌的解法。(也比较详细

首先来说说看状态， $f_{i,j,k} $ 表示 $[i, j]$ 范围消除完之后，剩余k个颜色为 $color_{i}$ 的最大分数。

~~（大佬看到这应该已经懂了， 这题主要是设状态，后面可以跳过直接代码~~
 
比如 $f_{i,j,0}$ 表示把 $[i, j]$ 完全消除（啥都不剩）的最大分数。


------------

### 转移分析
那么问题来了我们为什么要怎么设呢？

想想看对于每一个块我们只有两种操作， 

一种单独消掉。

一种是和其他块组合起来消掉：比如 $12221$ , 我们可以把 $222$ 消掉，然后让11组合起来。

对，也就是说，当我们要把两个块组合起来时， 一定要把他们之间的所有块先消除， 例如把i, k组合起来，要先把$[i+1, k-1]$这个区间消除掉， 得到分数是 $f_{l+1, k-1, 0}$ 

当我们计算 $f_{i, j, k}$ 时， 假设i是新放进去的块（$[i+1, j]$ 已经计算好了）。

直接消掉i显然为 $1+f_{i+1, j, 0}$ , 进一步考虑组合：

我们枚举 $[i+1, j]$ 中每一个为 $color_{i}$ 的块 $k$，

我们考虑在 $[k, j]$ 中选择若干个块与i合并  分数为 $f_{k,j,x}$ (剩余 $x$ 个用来合并)$[i+1, k-1]$ 直接消掉 $f_{i+1, k-1, 0}$
枚举这个 $x$，ok
（这个地方需要仔细思考）

复杂度 $O(n^4)$


------------


实在不行看看代码？

## 代码
```cpp
for(int i=1; i<=n; i++){
	f[i][i][1] = 0;//直接把这个块保留，不需要消除，所以分数为0 
	f[i][i][0] = 1;//直接消除这一个块, 分数1 
}
for(int j=2; j<=n; j++){
	for(int i=1; i+j-1<=n; i++){
		int l=i, r=i+j-1;
		f[l][r][0] = f[l+1][r][0] + 1;//直接消除i 
		f[l][r][1] = f[l+1][r][0];//直接保留i 

		for(int st=l+1; st<=r; st++){
			if(color[st] != color[l]) continue;//枚举上面的“x” 
			for(int k=1; k<n; k++){//注意边界 
				f[l][r][k+1] = max(f[l][r][k+1], f[l+1][st-1][0] + f[st][r][k]);
				//从st-r中取k个与i合并， 一共k+1个 
				f[l][r][0] = max(f[l][r][0], f[l][r][k+1] + (k+1)*(k+1));
				//考虑把k+1个直接消除， 更新最大分数 
			} 
		}
	}
}
```


---

## 作者：andysk (赞：4)

[Link](https://www.luogu.org/problem/UVA10559)

[Blog](https://tony102.xyz/index.php/2019/11/06/uva10559-blocks%e6%96%b9%e5%9d%97%e6%b6%88%e9%99%a4/)阅读效果更佳

题意很明确了，像这种消除一小块同色的东西获得一些分数，让你使这个分数最大的题目多半可以考虑区间DP

不妨先试：设 $f[l][r]$ 表示从 $l$ 消到 $r$ 可获得的最大分数。枚举一个中间转移的断点 $k$ 

这样设是最直接的状态。最大的问题是这么设中间的颜色非常不好处理，仍然需要再从$l$ 遍历到 $k$ 和从 $k + 1$ 遍历到 $r$，看颜色是否相同，可以消除。那么这么做的复杂度是 $O(n^4)$ 

考虑另一种状态，设 $f[l][r][k]$ 表示从 $l$ 消到 $r$ 并且在 $r$ 后还有 $k$ 个与 $r$ 位置上的方块同色的方块

考虑 $k =0$ 的特殊情况，那么它肯定由右边界的上一个位置 $r-1$ 转移过来，则 $f[l][r][0] = max(f[l][r][0],f[l][r - 1][0] + 1) $

因为 $k=0$ 也可以写成：$f[l][r][0] = max(f[l][r][0],f[l][r - 1][0] + (k+1)^2) $

推广到全部情况，设 $l \leq p < r$ ，则有：$f[l][r][k] = max(f[l][r][k], f[l][p][k+1]+f[p+1][r-1][0])$

实现的时候借鉴了神tst的预处理每一个位置上颜色相同的个数的方法，具体实现见代码。

类似的比较巧妙的区间DP推荐：[P3147 [USACO16OPEN]262144](https://www.luogu.org/problem/P3147)



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 200 + 5;

int T, n;
int a[SIZE], sum[SIZE], f[SIZE][SIZE][SIZE];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline void init()
{
    memset(f, 0, sizeof(f));
    memset(sum, 0, sizeof(sum));
}

int main()
{
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    T = read();
    int ind = 0;
    while (T--) {
        ind++;
        n = read();
        for (int i = 1; i <= n; i++) a[i] = read();
        for (int i = n - 1; i >= 1; i--)
            for (int j = i + 1; j <= n; j++) {
                if (a[i] == a[j]) sum[i]++;
            }
        for (int i = n; i >= 1; i--) 
            for (int j = i; j <= n; j++) {
                for (int k = i; k < j; k++) {
                    if (a[j] == a[k]) {
                        for (int p = 0; p <= sum[k]; p++)
                            f[i][j][p] = std::max(f[i][j][p], f[k + 1][j - 1][0] + f[i][k][p + 1]);
                    }
                }
                for (int k = 0; k <= sum[j]; k++) {
                    f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][0] + (k + 1) * (k + 1));
                }
            }
        std::cout << "Case " << ind << ": " << f[1][n][0] << endl;
        init();
    }
    return 0;
}
```



---

## 作者：JA_yichao (赞：3)

# 题目大意
由$~n~$种方块组成的一排方块，消除一段长度为$~x~$的连续相同方块可以得到$~x^2~$的分数，

求**最大**得分。

(消除之后两端合并)

$(1≤n≤200)$
# 思路
首先依~~标签~~题意可知是在一段一段的区间上操作,数据范围也不大，于是就想到区间DP。

这道题思路很巧妙，一般的区间DP都是设$~f[i][j]~$为$~i~$到$~j~$的最大值

但是这道题你会发现 **$~j~$之后的$~k~$个和$~j~$相同的木块会对答案有贡献**，而你又不能拆成几个区间搞，

所以就多维护一个$~k~$，**设$~f[i][j][k]~$表示,$~i~$到$~j~$区间后面有$~k~$个与$~j~$相同的木块的最高得分**。

然后也要分情况讨论：

⭐首先是我们可以不合并$~j~$与$~k~$, 消除$~[i,j]~$，**把区间$~k~$ 单独消除**.

⭐还有一种情况是我们寻找到一个中转点$~m~$，先消除$~[m+1,j-1]~$，然后把$~[i,m]~$以及$~j~$和$~k~$一起消除。**（$~[m+1,j-1]~$消除了，$~[i,m]~$就和$~j~$并在一起了）**

这样做会发现很像递归,然后就变成记忆化搜索去搞。

你会发现直接40分超时，观察发现，

这个相同的木块一个一个搞很烦，所以就可以**合并成一个木块**搞（就像缩点，带权）。

这样就可以节省一些时间复杂度。

# 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
long long T,n,a,len[10010],c[10010],last,cnt;
long long f[211][211][211];
long long solve(long long l,long long r,long long k)
{
	if(f[l][r][k])
	  return f[l][r][k];   //记忆化
	if(l==r)
	  return (len[l]+k)*(len[l]+k);
	f[l][r][k]=solve(l,r-1,0)+(len[r]+k)*(len[r]+k);  //情况一
	for(long long i=l; i<r-1; i++)    //情况二
	 if(c[i]==c[r])
	   f[l][r][k]=max(f[l][r][k],solve(l,i,len[r]+k)+solve(i+1,r-1,0));
	return f[l][r][k];
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	 {
	 	js=0,la=0;
	 	scanf("%lld",&n);
	 	memset(f,0,sizeof(f));
	 	memset(c,0,sizeof(c));
	 	memset(len,0,sizeof(len));
	 	for(long long i=1; i<=n; i++)
	 	 {
	 	 	scanf("%lld",&a);
	 	 	if(a==last)      //合并相同块
	 	 	  len[js]++;
	 	 	else
	 	 	 {
	 	 	 	c[++js]=a;
	 	 	 	len[js]++;
			 }
			la=a;
		 }
		printf("%lld\n",solve(1,cnt,0));
	 }
	return 0;
}
```
# 题外话
话说这道题跟**P2135	方块消除**差不多，然后[P2135](https://www.luogu.com.cn/problem/P2135)输入已经给你合并了。
~~蓝跟紫就差一个合并~~

---

## 作者：Starlight_Glimmer (赞：3)

My Blog:https://www.cnblogs.com/lyttt/p/14021670.html


[题目链接](https://www.luogu.com.cn/problem/UVA10559)

#### 解析

显然这道题重点在于消掉一些块之后会产生一些新的连续的块可以一起消，这个不能想到别的什么做法，可以考虑区间$dp$。

不过对于一整坨，你要么把他们全部一起消掉，要么就留着等更多的过来一起消掉，你总不可能把一坨分批消掉吧，明显$(x+y)^2>=x^2+y^2$啊

所以刚开始可以把相同颜色的一段块看成一点~~（不过我太懒了，最后没有这么写，当然，这不是重点~~，用$(a,b)$表示有$b$个颜色为$a$的方块相连。

用惯常的思路进行考虑，设$f[i][j]$表示消除区间$[i,j]$的得分。

单独消除的状态是很好转移的：$f[i][j]=max(f[i][j-1]+b_j^2,f[i+1][j]+b_i^2)$。

但如果是保留这一段，然后等着和其它的方块一起消呢？我们发现这个状态难以转移，因为这个区间的得分还与这个区间以外的前面消方块的状态息息相关。如果记录下前面消了哪些，还有哪些，在什么位置之类的相关信息，状态数无疑是巨大的。

类比于之前[小球](https://www.cnblogs.com/lyttt/p/14019547.html)的做法，在之前预先计算得分，我们发现这个似乎也行不通，因为这个得分不再是简单的线性关系，而是二次函数，过去的贡献与现在消去的长度有关。

返回去想到这道题重点在于消掉一些块之后会产生一些新的连续的块可以一起消，对于保留的情况，我们是把$j$留着和之前剩下的一串同色的方块合在一起消，如果这些合并在之前被料到并预先计算了得分，并通过状态转移到现在，那么就可以转移了。

对于状态$f[i][j][k]$考虑假设在未来经过一些消除操作后，有$k$个与$j$同色的方块在右边和$j$拼在了一起，的最大得分。

为啥只需要记录$j$，而不用管$[i,j-1]$呢，是因为：

假设$[i,j-1]$中某点$x$未来会与$p$相连。

1. $p$的位置在$k$左边，即$x<j<p<k$，那是不可能的，因为未来$j$会与$k$相连，而$p$挡道了，所以$p$一定是在$j,k$之间消掉的，没机会往$[i,j-1]$那个区间接触。
2. $p$的位置在$k$右边，即$x<j<k<p$，那么这个状态是个包含关系，$x$和$p$产生的贡献可以通过$f[x][p]$计算，不用这个时候来操心。

所以：对于状态$f[i][j][k]$，无论经过什么操作,$i$到$j-1$之间只能与$i$到$j$之间的区域相连，而区域$j$可以与$j$之后的的区域相连。

最后得到转移方程：

$f[i][j][k]=f[i][j-1][0]+(k+1)^2$（$j$和它后面的$k$个~~同系物~~同色块相消）

$f[i][j][k]=f[i][x][k+1]+f[x+1][j-1][0],i<=x<j,a_x==a_j$（$x$为前面一个和$j$颜色相同的位置，拿掉$[x+1,j-1]$，那么$j$和它右边的小伙伴们和$x$拼成了一个更大的连续一串（这里就是上文说到的“在未来经过一些消除操作后”的“一些操作”））





直接$dp$有点难做，顺序有点乱，所以写成了记搜的样子。

最后答案是$f[1][n][0]$

（好久没写这么长的题解了，好家伙，写了一节课）



参考：《对一类动态规划问题的研究》 徐源盛 

------

#### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 205
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,a[N],pre[N],pos[N];
LL f[N][N][N];//f[i][j][k]表示消去[i,j]区间 且j右边还有k个和j颜色相同的块
/*
主体部分是连续的[i,j]区间 没有动过
然后j右边有颜色相同的k块紧接在j后面 他们之间的方块已经消完 
*/
void Init()
{
	memset(f,0,sizeof(f));
	memset(pre,0,sizeof(pre));
	memset(pos,0,sizeof(pos));
}
LL dp(int i,int j,int k)
{
	if(i>j) return 0;
	if(f[i][j][k]) return f[i][j][k];
	LL res=dp(i,j-1,0)+(k+1)*(k+1);//和右边一整坨一起消掉
	int l=pre[j];
	while(l>=i)
	{
		res=max(res,dp(i,l,k+1)+dp(l+1,j-1,0));//拿掉[l+1,j-1] 相同颜色的又拼到一起了 
		l=pre[l];
	}
	return f[i][j][k]=res; 
}
int main()
{
	int T=rd();
	for(int cas=1;cas<=T;cas++)
	{
		Init();
		n=rd();
		for(int i=1;i<=n;i++)
		{
			a[i]=rd();
			pre[i]=pos[a[i]],pos[a[i]]=i;
		}
		printf("Case %d: %lld\n",cas,dp(1,n,0));
	} 
	return 0;
}
```





---

## 作者：pengyule (赞：3)

#### 某某DP基本步骤（走流程）

0. 识别某某 DP（通常是删掉一个子段能得到价值/代价，删后左右合并，要最优化收益）
1. 观察性质，说出一次可以删的子序列的特征
2. 设 $f[l,r]$ 表示 $[l,r]$ 删完的最优收益
3. 设 $g[l,r][限制条件]$ 表示 $[l,r]$ 删到只剩一个满足限制条件的子序列能得到最优收益。要求：知道限制条件就能直接算得单次收益
4. $f[l,r]=g[l,r][限制条件]+$ 满足限制条件算得的单次收益

注云：这是绝主要脉络，是核心。但题目可能会在边角料上加工，需要通过分类讨论等方式找到这个核心。
*WARNING: dp 的初始值注意设为 `-INF`，可以判定无解。*

## 习题
- [UVA10559 Blocks](https://www.luogu.com.cn/problem/UVA10559)

这道题通过上述讲的方法相信大家都是会的。
> 设 $f[l,r],g[l,r][i]$ 表示 $[l,r]$ 全删完的最大价值；$[l,r]$ 删到只剩 $i$ 个 $a_r$ 的最大收益。
> $$
f[l,r]=\max(g[l,r][i]+i^2)\\
g[l,r][i]=\max_{k\in [l,r)}(g[l,k][i-1]+f[k+1][r-1])
$$

但通过这道题我们可以积累另一个 dp 状态设计方式，那就是**设将来决策，以消除后效性**。
可以设 $f[l,r][i]$ 表示：删完 $[l,r]$ 及从 $r+1$ 往右数 $i$ 个 $a_r$，能得到的最大价值。于是需要考虑我们这一次
- 是直接把 $a_r$ 以及右边那一串 $=a_r$ 的全部“兑现”；
- 还是攒着跟 $[l,r)$ 中的一些 $=a_r$ 的一起消。

转移式分别为
$$
f[l,r][i]=f[l,r-1][0]+(1+i)^2\\
f[l,r][i]=\max_{k\in [l,r)}(f[l,k][1+i]+f[k+1,r-1][0])
$$

Code1:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=205;
const ll INF=0x3f3f3f3f3f3f3f3f;
int n,a[N];
ll f[N][N],g[N][N][N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(f,-0x3f,sizeof(f));
	memset(g,-0x3f,sizeof(g));
	for(int i=1;i<=n;i++)f[i][i]=1,g[i][i][1]=0,f[i][i-1]=0;
	for(int len=2;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
			g[l][r][1]=f[l][r-1];
			for(int i=2;i<=r-l+1;i++)
				for(int k=r-1;k>=l;k--)
					if(a[k]==a[r]&&g[l][k][i-1]>-INF)
						g[l][r][i]=max(g[l][r][i],g[l][k][i-1]+f[k+1][r-1]);
			for(int i=1;i<=r-l+1;i++)
				if(g[l][r][i]>-INF)
					f[l][r]=max(f[l][r],g[l][r][i]+1ll*i*i);
		}
	}
	cout<<f[1][n]<<'\n';
}
int main(){int t;cin>>t;for(int i=1;i<=t;i++)printf("Case %d: ",i),solve();}
```


Code2:

```cpp
#include <bits/stdc++.h>
#define sq(a) (a)*(a)
using namespace std;
typedef long long ll;
const int N=205;
int n,a[N],f[N][N][N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int len=1;len<=n;len++){
		for(int l=1,r=len;r<=n;l++,r++){
			for(int i=0;i<=n-r;i++){
				f[l][r][i]=0;
				f[l][r][i]=max(f[l][r][i],f[l][r-1][0]+sq(1+i));
				for(int k=l;k<r;k++)
					if(a[k]==a[r])
						f[l][r][i]=max(f[l][r][i],f[l][k][1+i]+f[k+1][r-1][0]);
			}
		}
	}
	cout<<f[1][n][0]<<'\n';
}
int main(){
	int t;cin>>t;for(int i=1;i<=t;i++)printf("Case %d: ",i),solve();
}
```

---

## 作者：Narcissusany (赞：2)

这里给一个比较新(坎)颖(坷)的记搜方法。

顺便 hack 了当前最高赞的记搜，可以左转讨论区领取数据。

____


# [UVA10559 Blocks](https://uva.onlinejudge.org/external/105/p10559.pdf)

> 有 $n$ 个带有颜色的方块，没消除一段长度为 $x$ 的连续的相同颜色的方块可以得到 $x^2$ 的分数，让你用一种最优的顺序消除所有方块使得得分最多。
>
> $1\leq n\leq 200$ 。

大概是比较神仙的 $dp$ 了吧…

第一感觉肯定就是 $f_{l,r}$ 嘛，但是这么做的话本质上就变成贪心了，因为可能转移时，$f_{l,k}$ 和 $f_{k,r}$ 是消掉中间一部分，再合并起来的模式。注意到，对于一段 $i,j$，假设 $i<q<j$ 满足 $q\sim j$ 同色，$i<o<p<q$ 满足 $o\sim p$ 与 $q\sim j$ 同色，那么一种决策就是把这两段合并。但是注意到可能还会存在一个区间 $i<s<t<o$ 满足 $s\sim t$ 和 $o\sim p$ 同色~~禁止套娃~~ 。

于是这就启发(个鬼，这怎么可能想得出来)要多记一维状态 $d$，即 $f_{l,r,d}$ 表示 $l\sim r$ 的这段区间内，区间右侧还有 $d$ 个元素和 $r$ 同颜色时的最大得分。这样每次就以「和右端点颜色相同的颜色段」为子决策进行转移。那么需要枚举每次有多少个块和右端点一起删掉，在这基础枚举一个和右端点同色的、靠左的点进行转移，表示右端点所在的同色段暂时先不删，加入继续向左延伸的长同色段的一部分。

复杂度的话，状态是 $O(n^3)$ 的，然后我这种写法好像很迷幻，~~我觉得应该是 $n^5$ 但不知道为什么测出来极限数据(即所有颜色都相同)时运算量在 $n^4$ 量级~~  …剪枝是要剪的，每次只关心和 $r$ 同色的元素就好了。

好的，我又重新写了一下测了一下，觉得应该把访问记忆化结果也算 $1$ 次运算。发现 $100$ 个相同的颜色放在一起，这么写的运算量大概是 $258712510\approx2.6\cdot 10^8$，大概 $1s$ 内是可以跑出来结果的(uoj custom test 900ms左右)。$200$ 个颜色相同的就已经是紫荆花之恋那题跑不出来的程度了(即 $14s$ 以内跑不出来，只能本地测试)，似乎足足要 $1\min+$，大概是 $8136350020\approx8\cdot 10^9$ 的运算量~~中间可执行文件还一度被系统给 kill 掉了~~ 。

然后…然后我就加了一个好像很牛逼的剪枝，大概就是判断一下 $l\sim r$ 这一整段是不是同色，如果是的话就直接算完了返回即可。发现这样之后极端数据就应该是只有两种颜色然后左右交替这种，就可以在 $370\sim400ms$ 左右跑出来~~但似乎应该还是过不了，因为极限可以有15组数据，每组都这个速度肯定跑不进3s鸭~~。

然后发现这个某个区间是否同色可以预处理，然后就预处理了一下，发现一组快的话只需要 $320ms$ 左右了…

然后又改了一下，发现可以稍微贪一下，「枚举每次有多少个块和右端点一起转移走」显然是最大的那个快最好了。但这并没有快…

删了点重复计算和冗杂判断…发现大概是稳定在 $320ms$ 左右了…

…发现自己是个弟弟，如果要把右边和左边合并的话，那肯定是全都一起合并最优。所以现在大概是真正的 $O(n^4)$ 算法了？一组大概是 $200ms$ 左右了…人艰不拆。

```cpp
//版本1 最大点 400ms
bool check(int l, int r){
	for (int i = r, j = lst[r] ; i >= l ; j = lst[j], i = lst[i])
		if (i != j + 1) return 0 ; return 1 ;  
}

int solve(int l, int r, int t){
	if (l > r) return f[l][r][t] = 0 ;
	if (f[l][r][t]) return f[l][r][t] ; 
	if (l == r) return f[l][r][t] = (t + 1) * (t + 1) ;
	if (check(l, r)) return f[l][r][t] = (t + r - l + 1) * (t + r - l + 1) ;//剪枝 1
	for (int i = r ; i >= l && base[i] == base[r] ; -- i){
		chkmax(f[l][r][t], solve(l, i - 1, 0) + (t + r - i + 1) * (t + r - i + 1)) ;
		for (int j = lst[i] ; j >= l ; j = lst[j])
			if (base[j] == base[r]) 
				chkmax(f[l][r][t], solve(j + 1, i - 1, 0) + solve(l, j, r - i + 1 + t)) ; 
	}
	return f[l][r][t] ;
}
```

```cpp
//版本2 最大点 320- ms
int solve(int l, int r, int t){
	if (l > r) return f[l][r][t] = 0 ;
	if (f[l][r][t]) return f[l][r][t] ;
	if (l == r) return f[l][r][t] = (t + 1) * (t + 1) ;
	if (g[r] <= l) return f[l][r][t] = (t + r - l + 1) * (t + r - l + 1) ;
	chkmax(f[l][r][t], solve(l, g[r] - 1, 0) + (t + r - g[r] + 1) * (t + r - g[r] + 1)) ;
	for (int i = r ; i >= g[r] ; -- i){
		register int pq = t + r - i + 1 ; 
		for (int j = lst[i] ; j >= l ; j = lst[j])
			chkmax(f[l][r][t], solve(j + 1, i - 1, 0) + solve(l, j, pq)) ;
	}
	return f[l][r][t] ;
}

int main(){
	cin >> T ; Q = T ;
	while (T --){
		n = qr() ;
		memset(f, 0, sizeof(f)) ;
		memset(buc, 0, sizeof(buc)) ;
		memset(lst, 0, sizeof(lst)) ;
		printf("Case %d: ", Q - T) ;
		for (int i = 1 ; i <= n ; ++ i)
			lst[i] = buc[base[i] = qr()], buc[base[i]] = i ;
		for (int i = 1 ; i <= n ; ++ i)
			for (int j = i ; j >= 1 ; -- j)
				if (base[i] == base[j]) g[i] = j ; else break ; 
		cout << solve(1, n, 0) << '\n' ;
	}
}

```

```cpp
//版本3 200- ms 左右 此时根本不需要判整段是否相同
int solve(int l, int r, int t){
	if (l > r) return f[l][r][t] = 0 ;
	if (f[l][r][t]) return f[l][r][t] ;
	if (l == r) return f[l][r][t] = (t + 1) * (t + 1) ;
	//if (g[r] <= l) return f[l][r][t] = (t + r - l + 1) * (t + r - l + 1) ;
	chkmax(f[l][r][t], solve(l, g[r] - 1, 0) + (t + r - g[r] + 1) * (t + r - g[r] + 1)) ;
	for (int j = lst[g[r]] ; j >= l ; j = lst[j])
		chkmax(f[l][r][t], solve(j + 1, g[r] - 1, 0) + solve(l, j, (t + r - g[r] + 1) )) ;
	return f[l][r][t] ;
}
```





---

## 作者：Z1qqurat (赞：1)

先说清楚，这是一道区间dp。

### 思路

Part 1：状态的定义。

下面对“段”的定义借鉴了[P2135 方块消除](https://www.luogu.com.cn/problem/P2135)。

其实这道题和[Zuma](https://www.luogu.com.cn/problem/P5189)有点像的，仔细观察题面不难发现，它们的状态里都应该有三维，前两维明显表示把区间 $i$ 到 $j$ 的所有方块消除，而后一维记录在第 $i$ 或 $j$ 段后面有多少个与 $i$ 或 $j$ 颜色相同的。（这个想法的来源如果不懂可以看看我的 [Zuma解题报告](https://www.luogu.com.cn/blog/WrasarCJ/solution-p5189)）

于是我们定义状态 $dp[i][j][c]$ 表示消除从 $i$ 到 $j$ 所有方块且在第 $j$ 段右边有 $c$ 段与 $j$ 颜色相同的方块。

Part 2：转移方程的推导。

那么对于状态 $dp[i][j][c]$ ，我们该怎么写式子呢？

考虑两种可能，我们可以直接把能消除的先全部消除，也可以在区间的中间找断点进行消除。

这里用 $len$ 和 $col$ 表示一段的长度和颜色qwq。

```cpp

int num=len[j]+c;
dp[i][j][c]=num*num+dp[i][j-1][0];
for(ri k=i;k<=j-1;k++){
	if(col[k]==col[j])dp[i][j][c]=max(dp[i][j][c],dp[k+1][j-1][0]+dp[i][k][num]);
}

```

Part 3：边界条件要注意。

像Zuma一样，边界条件当然是在区间长度为 $1$ 的时候有的啦。

```cpp

if(i==j)dp[i][j][c]=num*num;


```

Part 4：“段”的预处理。

由于题目不是按照我们的一段一段给的，所以我们需要自己处理。

```cpp

for(ri j=1;j<=n;j++){
	cin>>a;
   if(a==col[cnt])len[cnt]++;
   else{
   	cnt++;
        col[cnt]=a;
        len[cnt]++;
   }
}
        
```

这里用 $cnt$ 记录段的数量，所以输出的时候要注意是 $dp[1][cnt][0]$ 而不是 $dp[1][n][0]$ 。

### 代码实现

代码实现的话，差不多吧。

本人喜欢记忆化搜索。

```cpp

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define ri register int
using namespace std;
const int MAXN=210,inf=0xcfcfcfcf;
int t,n,col[MAXN],len[MAXN],a,dp[MAXN][MAXN][MAXN],cnt;

int DP(int i,int j,int c){
    int num=len[j]+c;
    if(i==j)return num*num;
    if(dp[i][j][c]!=0xcfcfcfcf)return dp[i][j][c];
    dp[i][j][c]=num*num+DP(i,j-1,0);
    for(ri k=i;k<=j-1;k++){
        if(col[k]==col[j])dp[i][j][c]=max(dp[i][j][c],DP(k+1,j-1,0)+DP(i,k,num));
    }
    return dp[i][j][c];
}

int main() {
    ios::sync_with_stdio(false);
    cin>>t;
    for(ri i=1;i<=t;i++){
        memset(dp,0xcf,sizeof(dp));
        memset(col,0,sizeof(col));
        memset(len,0,sizeof(len));
        cnt=0;
        cin>>n;
        for(ri j=1;j<=n;j++){
            cin>>a;
            if(a==col[cnt])len[cnt]++;
            else{
                cnt++;
                col[cnt]=a;
                len[cnt]++;
            }
        }
        //for(ri j=1;j<=cnt;j++)cout<<col[j]<<' '<<len[j]<<"\n";
        cout<<"Case "<<i<<": "<<DP(1,cnt,0)<<"\n";
    }
    return 0;
}

```

$End.$

---

## 作者：glorious_dream (赞：0)

### 题目大意：

 $n$ 个木块排成一列，每个木块有一个颜色，每次，你都可以点击一个木块，这样被点击的木块以及和它相邻并且同色的木块就会被消除。如果一次性消除了 $k$ 个木块，就会得到 ${k^{2}}$ 分，求最高得分。
 

------------


### 算法分析：
首先，会想到贪心，但很容易发现有些最优解是消除了单个木块，让更长的相同颜色木块拼在一起。所以，贪心策略行不通。

于是，想到了**动态规划**。


做过版子题（石子合并）应该会很容易想到：

设 $tot$ 表示原序列分成的颜色段的段数。

$len[i]$ 表示第 $i$ 个颜色段的长度。

$color[i]$ 表示第 $i$ 个颜色段的颜色。

$dp[i][j]$ 表示消除第 $i$ 段到第 $j$ 段之间所有木块的最高得分。

然而，我们发现，如果单纯这么转移的话，当第 $j$ 段后面仍然有和第 $j$ 段前面的颜色段颜色相同的段，无法判断将两个颜色段合并是否更优。

**所以，还需要再加一维。**

设 $dp[i][j][k]$ 表示在第 $j$ 段后面出现 $k$ 个与第 $j$ 段颜色相同的木块，消除第 $i$ 段到第 $j$ 段之间的所有木块所能得到的最高得分。


------------


### 转移方程

考虑转移对于 $r$ 所在的颜色段，有两种情况，可以选择直接消除，或在 $r$ 段前面补上与它颜色相同的木块。

~~什么意思？~~

首先，如果直接消除：将 $r$ 段清除后，变成 $r-1$ 段，$k=0$，再加上清除这一段的得分。
```cpp
dp[l][r][k] = dp[l][r-1][0] + (len[r]+k) * (len[r]+k)
```

再考虑第二种情况，在 $l$ 到 $r$ 中找一段与 $r$ 颜色相同的段，设为 $x$，将这一段与 $r$ 合并，也就是先清除中间的木块，再将合并的段清除。这时的 $k$ 就变为 $len[r]+k$。

```cpp
dp[l][r][k] = max(dp[l][r][k],dp[x+1][r-1][0]+dp[l][x][len[r]+k])
```

### 代码（两种，记忆化搜索和动态规划）

先来看记忆化搜索的。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){ //快读不解释
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 210;
int dp[M][M][M],color[M],len[M],a[M]; //如上文的含义
int T,n,tot;
int dfs(int l,int r,int k){
    if(l==r)return (len[r]+k)*(len[r]+k); //如果搜到一起了，返回此时加的分数
    if(dp[l][r][k]) return dp[l][r][k]; //这就是记忆化，避免了重复搜索
    dp[l][r][k] = dfs(l,r-1,0) + (len[r]+k)*(len[r]+k);//上文的转移式1
    for(register int i(l) ; i<r-1 ; i=-~i){
        if(color[i] == color[r]){ //这两段颜色相同才能转移
            dp[l][r][k] = max(dp[l][r][k],dfs(i+1,r-1,0) + dfs(l,i,len[r]+k)); //转移式2
        }
    }
    return dp[l][r][k]; //最后返回此时能得到的最大得分
}
int main(){
    T=read();
    for(register int cnt(1) ; cnt<=T ; cnt=-~cnt){
        memset(dp,0,sizeof(dp));
        memset(color,0,sizeof(color));
        memset(len,0,sizeof(len));
        tot=0; //一定要清零，要不是你错都不知道怎么错的
        n=read();
        for(register int i(1) ; i<=n ; i=-~i) a[i] = read();
        for(register int i(1) ; i<=n ; i=-~i){
            if(a[i] != a[i-1]){	
                color[++tot] = a[i]; //这一部分先预处理颜色段数和颜色
                len[tot]=1;
            }
            else len[tot]++;
        }
        printf("Case %d: %d\n",cnt,dfs(1,tot,0)); //最后输出就行
    }
    return 0;
}
```


------------


然后放上动态规划的（**一定要注意转移顺序**）

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 210;
int dp[M][M][M],color[M],len[M],a[M],s[M];
int T,n,tot;
int main(){
    T=read();
    for(register int cnt(1) ; cnt<=T ; cnt=-~cnt){
        memset(dp,0,sizeof(dp));
        memset(color,0,sizeof(color));
        memset(len,0,sizeof(len));
        tot=0;
        n=read();
        for(register int i(1) ; i<=n ; i=-~i) a[i] = read();
        for(register int i(1) ; i<=n ; i=-~i){
            if(a[i] != a[i-1]){	
                color[++tot] = a[i];
                len[tot]=1;
            }
            else len[tot]++;
        }
        for(register int i(1) ; i<=n ; i=-~i) s[i] = s[i-1] + len[i]; //前缀和处理，预处理出前面最多有多少段颜色相同的
        for(register int l(0) ; l<=n ; l=-~l){
            for(register int i(1) ; i+l<=n ; i=-~i){ // 注意转移顺序
                int j = l+i;
                for(register int k(0) ; k<=s[n]-s[j-1] ; k=-~k){ //k循环到这就行了，一点点优化
                    dp[i][j][k] = dp[i][j-1][0] + (len[j]+k)*(len[j]+k); //转移式1
                }
                for(register int k(i) ; k<j ; k=-~k){
                    for(register int h(0) ; h<=s[n]-s[j-1] ; h=-~h){
                        if(color[k] == color[j]){
                            dp[i][j][h] = max(dp[i][j][h],dp[k+1][j-1][0] + dp[i][k][len[j]+h]); //转移式2
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n",cnt,dp[1][tot][0]);//颜色段只有tot，不能到n
    }
    return 0;
}

```


---

## 作者：Viktley (赞：0)

**题目大意：**

给出 $n$ 个颜色不一的方块，

每次只能将一部分颜色相同的区间消除，

答案贡献为相同颜色个数的平方为求一种顺序使得最后的贡献最大。

------------

**思路：**

对于每一个区间，要么它自己内部全部消消乐，要么它消一部分，

留一部分和外面的木块合并形成更大的木块。

每一个大区间的内部，又可以分成很多的小区间，

小区间同样即可以自己全部消消乐，

也可以消一部分然后留一部分和大区间内其他的小区间合并成更大木块。

所以可以用递归去解决这个问题。

$f(x,y,cnt)$ 表示现在处理一个 $x$ 到 $y$ 的区间，

右边有 $cnt$ 个和 $y$ 一样颜色的木块等着我的合并（当然我也可以不合并）。

如果我选择第一种玩法：即自己全部消消乐，

那么 $f(x,y,cnt)=f(x,y-1,0)+(cnt+1)*(cnt+1)$。

//意思就是右边先将整块消掉，然后留下左边自己去消，

并且告诉左边——右边没有木块等着你去合并，所以就是 $f(x,y-1,0)$。

如果我选择第二种玩法：即先消掉一部分，然后留一部分和外面合并。

那么我先找到区间中和 $y$ 颜色相同的木块段，

（设其左端点为 $l_1,l_2,l_3......$，其右端点是 $r_1,r_2,r_3......$，

长度分别是 $len_1,len_2,len_3......$)，

以每一个不同的 $s_i$ 为界限，

$s_i$ 左边所有的区间询问 $f(x,l_i,(len_1-1)+cnt)$，

$r_i$ 右边所有的区间询问 $f(r_i+1,y,0)$。

意思是，我先将右边的杂色木块自己消消乐，留下左边的木块。

左边的木块既可以全部自己消消乐，又因为它有与 $y$ 同样颜色的木块，

所以也可以先合并同色木块，然后接着询问剩下来的区间。

但是会超时，

考虑将颜色相同的点进行缩点处理（类似强连通分量的做法），

这样就大大减少了程序在递归中的查询颜色是否相同的时间。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
    char c=getchar();int f=1,s=0;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-'0';c=getchar();}
    return f*s;
}
const int N = 2e2 + 10; 
int t, n, tot, f[N][N][N], a[N], len[N], bac[N], last;

int dis(int x) {return x * x;}

int dfs(int x, int y, int cnt)
{
    if(y < x) return 0;
    int &s = f[x][y][cnt];
    if(s) return s;
    s=dfs(x, y - 1, 0) + dis(len[y] + cnt);
    for(int k = x; k < y; k++)
    {
        if(a[k] != a[y])continue;
        s = max(s, dfs(x, k, len[y] + cnt) + dfs(k + 1, y - 1, 0));
    }
    return s;
}

int main()
{
    t = read();
    for(int tt = 1; tt <= t; tt++)
    {
        n = read();
        memset(f, 0, sizeof(f));
        memset(len, 0, sizeof(len));
        tot = 0, last = -1;
        for(int i = 1; i <= n; i++)
        {
            int x = read();
            if(x != last)
            {
                a[++tot] = x;
                len[tot] = 1;
            }
            else len[tot]++;
            last = x;
        }
        printf("Case %d: %d\n", tt, dfs(1, tot, 0));
    } 
    return 0;
}
```


---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2135)

---

记录~~生活~~学习情况。

资料：[对一类动态规划问题的研究](https://wenku.baidu.com/view/83d0a76925c52cc58bd6bea8)

我们可以发现，定义 $dp_{i,j}$ 表示 $\text{[i,j]}$ 这个区间合并最大值是不行的，因为有颜色的转移。

所以我们要考虑有多少个同色块会连上来。

我们定义 $dp_{i,j,k}$ 表示 $[i,j]$ 这个区间且后面又有 $\text k$ 个与 $a_j$ 同色的块。

这样，我们就可以考虑到后面的新的木块了，转移见代码。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

const int MAXN = 200 + 5;

int T,n,tot,a[MAXN],cnt[MAXN],dp[MAXN][MAXN][MAXN],vis[MAXN][MAXN][MAXN],tag;

int dfs(int l,int r,int k) {
	if (vis[l][r][k] == tag) return dp[l][r][k];
	if (l == r) return (cnt[l] + k) * (cnt[l] + k);
	vis[l][r][k] = tag;
	dp[l][r][k] = dfs(l,r - 1,0) + (cnt[r] + k) * (cnt[r] + k);
	for (int i = l ; i < r ; ++ i) {
		if (a[i] == a[r]) dp[l][r][k] = Max(dp[l][r][k],dfs(l,i,cnt[r] + k) + dfs(i + 1,r - 1,0));
	}
	return dp[l][r][k];
}

int main () {
	read(T);
	int Case = 0;
	while (T --) {
		read(n);
		Case ++;
		register int x;
		tot = 0;
		for (int i = 1 ; i <= n ; ++ i) {
			read(x);
			if (x == a[tot]) cnt[tot] ++;
			else {
				a[++ tot] = x;
				cnt[tot] = 1;
			}
		}
		tag ++;
		printf("Case %d: %d\n",Case,dfs(1,tot,0));
	}
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

[题目](https://www.luogu.com.cn/problem/UVA10559)

[双倍经验](https://www.luogu.com.cn/problem/P2135)

# 进入正题

## 思路：

先预处理出连续相同方块的长度和颜色很容易想到 $dp[i][j]$ 表示消除从$i$ 到 $j$ 的区间的最多得分，但是只靠考虑区间 $[i, j]$ 显然不够全面。所以我们要思考怎么做：

我们可以加上一维，用 $dp[i][j][k]$ 表示消除从$i$ 到 $j$ 的区间且有 $k$ 个和 $j$ 颜色相同的方块接在 $r$ 后的最大得分，这样我们就可以转移了，转移方程为：

1、删掉 $j$ 和后面的 $k$ 块：
$$
dp[i][j][k] = max(dp[i][j][k], dp[i][j][0] + (k + 1)(k + 1))
$$
2、把 $[i, j]$ 分为两段： $[i, p]$ 和 $[p + 1, j]$ 来计算，在把答案加起来：
$$
dp[i][j][k] = \min \limits _ {p = i} ^ {j - 1} (dp[i][j][k], dp[i][p + 1][k + 1] + dp[p + 1][j - 1][0])
$$

## 程序实现：

讲完了思路，程序实现就不难了（主要是 DP，码量小），下面上代码：



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 205;
int t;
signed main()
{
	cin >> t;
	for(int i = 1; i <= t; i++)
	{
		int n = 0, co[N], cnt = 0, num[N], dp[N][N][100], sum[N];
		memset(dp, 0, sizeof(dp));//因为是多组数据，所以要初始化
		memset(co, 0 ,sizeof(co));
		memset(num, 0, sizeof(num));
		memset(sum, 0, sizeof(sum));
		cin >> cnt;
		for(int i = 1; i <= cnt; i++)
		{
			int x;
			cin >> x;
			if(x != co[n])//处理联通块
				co[++n] = x;
			num[n]++;
		}
		for(int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + num[i];//处理前缀和
		for(int len = 1; len <= n; len++)
			for(int l = 1; l <= n; l++)
			{
				int r = l + len - 1;
				if(r > n)
					break;
				for(int s = 0; s <= sum[n] - sum[r]; s++)
					dp[l][r][s] = dp[l][r - 1][0] + (num[r] + s) * (num[r] + s);//初始化
				for(int i = l; i < r; i++)
					for(int s = 0; s <= sum[n] - sum[r]; s++)
						if(co[i] == co[r])//断点必须和r相同，不然消掉[i+1,r]时就没法合并了
							dp[l][r][s] = max(dp[l][r][s], dp[l][i][num[r] + s] + dp[i + 1][r - 1][0]);
			}
		cout << "Case " << i << ": " << dp[1][n][0] << endl;//注意恶心的输出
	}
	return 0;//完美的结束QWQ
}
```



---

