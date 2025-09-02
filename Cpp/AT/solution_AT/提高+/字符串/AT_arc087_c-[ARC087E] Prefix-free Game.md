# [ARC087E] Prefix-free Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc087/tasks/arc087_c

文字列 $ s $, $ t $ について、$ s $ が $ t $ の prefix でなく、$ t $ が $ s $ の prefix でないとき、$ s $, $ t $ は prefix-free であると言います。

$ L $ を正の整数とします。 文字列集合 $ S $ が **良い文字列集合** であるとは、次の条件が成り立つことです。

- $ S $ の各文字列は、長さ $ 1 $ 以上 $ L $ 以下であり、文字 `0`, `1` のみからなる。
- $ S $ の相異なる $ 2 $ つの文字列のペアはいずれも prefix-free である。

良い文字列集合 $ S\ =\ \{\ s_1,\ s_2,\ ...,\ s_N\ \} $ があります。 Alice と Bob が次のゲームで勝負します。 二人は交互に次の操作を行います。 Alice が先手です。

- $ S $ に新しい文字列をひとつ追加する。 ただし、追加後の $ S $ は良い文字列集合のままでなければならない。

先に操作を行えなくなった方が負けです。 二人が最適に行動するとき、どちらが勝つか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ L\ \leq\ 10^{18} $
- $ s_1 $, $ s_2 $, ..., $ s_N $ はすべて相異なる。
- $ \{\ s_1,\ s_2,\ ...,\ s_N\ \} $ は良い文字列集合である。
- $ |s_1|\ +\ |s_2|\ +\ ...\ +\ |s_N|\ \leq\ 10^5 $

### Sample Explanation 1

Alice が `1` を追加すると、Bob は新たに文字列を追加できなくなります。

### Sample Explanation 2

初手で Alice が追加できる文字列は `01`, `10` の $ 2 $ 通りです。 初手で Alice が `01` を追加した場合は、Bob が `10` を追加すると、Alice は新たに文字列を追加できなくなります。 初手で Alice が `10` を追加した場合も、Bob が `01` を追加すると、Alice は新たに文字列を追加できなくなります。

### Sample Explanation 3

Alice が `111` を追加すると、Bob は新たに文字列を追加できなくなります。

### Sample Explanation 4

初手で Alice は新たに文字列を追加できません。

## 样例 #1

### 输入

```
2 2
00
01```

### 输出

```
Alice```

## 样例 #2

### 输入

```
2 2
00
11```

### 输出

```
Bob```

## 样例 #3

### 输入

```
3 3
0
10
110```

### 输出

```
Alice```

## 样例 #4

### 输入

```
2 1
0
1```

### 输出

```
Bob```

## 样例 #5

### 输入

```
1 2
11```

### 输出

```
Alice```

## 样例 #6

### 输入

```
2 3
101
11```

### 输出

```
Bob```

# 题解

## 作者：AsunderSquall (赞：4)


**题意**  

有一个 `01` 串集合 $S$，使得里面的任意两个 `01` 串没有前缀关系。现在两个人轮流往里面加 `01` 串，使得操作完之后 $S$ 仍然满足上述关系，先不能操作者输。

**题解**

首先我们建出一个 01-trie，容易发现选择一个字符串之后，它的子树和到根节点的链上的节点都不能再选了。  

仔细观察一下，发现剩下的树实际上是若干个满二叉树，那么我们要求这些满二叉树的 sg 函数。  
对于一棵深度为 $x$ 的满二叉树，大眼观察一下，我们发现：  
- 如果选择根节点，那么操作完后的树没了，即变成先手必败。  
- 如果选择深度为 $1$ 的节点，那么还剩下一棵深度为 $x-1$ 的满二叉树。  
- 如果选择深度为 $2$ 的节点，那么还剩下深度分别为 $x-1$ 和 $x-2$ 的两棵满二叉树。  
- ……  
- 如果选择深度为 $x$ 的节点，那么还剩下深度为 $1,2,3 \cdots x-1$ 的 $x-1$ 棵满二叉树。  

于是我们列出式子：  
$$sg(x)=\mathop{\operatorname{mex}} \limits_{i=1}^x [\mathop{\bigoplus} \limits_{j=i}^{x-1} sg(j)] $$

然后我们稍微手玩一下：  
$sg(0)=0$。   
$sg(1)=\operatorname{mex}\{0\}=1$。  
$sg(2)=\operatorname{mex}\{0,1\}=2$。  
$sg(3)=\operatorname{mex}\{0,2,3\}=1$。  
$sg(4)=\operatorname{mex}\{0,1,3,2\}=4$。  
$sg(5)=\operatorname{mex}\{0,4,5,7,6\}=1$。  
$sg(6)=\operatorname{mex}\{0,1,5,4,6,7\}=2$。    
我们发现，有 $sg(x)=\operatorname{lowbit}(x)$。  
证明可以用归纳法。  

**代码**  
```cpp
#include<bits/stdc++.h>
#define int long long
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define rd(x) x=read()
#define wt(x) write(x)
#define pos(x) (((x)-1)/SZ+1)
using namespace std;
const int N=1e7+5;
const int M=70;
const int SZ=450;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}
int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
int inv[N],fac[N],ifc[N]; 
void Init(int n)
{
    inv[1]=1;for (int i=2;i<=n;i++) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    fac[0]=1;for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifc[0]=1;for (int i=1;i<=n;i++) ifc[i]=ifc[i-1]*inv[i]%mod;
}
int C(int n,int m){if (m<0 || m>n) return 0;return fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
void add(int &x,int y) {x+=y;if (x>=mod) x-=mod;}
int n,k,ans,l,idx=1;
char s[N];
int son[N][2],dep[N],vis[N];
void insert()
{
    k=strlen(s+1);int u=1;
    for (int i=1;i<=k;i++)
    {
        int x=s[i]-'0';
        if (!son[u][0]) son[u][0]=++idx,dep[idx]=dep[u]+1;
        if (!son[u][1]) son[u][1]=++idx,dep[idx]=dep[u]+1;
        u=son[u][x];
        vis[u]=1;
    }
}
int sg(int x){return x&-x;}
signed main()
{
    rd(n);rd(l);vis[1]=1;
    for (int i=1;i<=n;i++) scanf("%s",s+1),insert();
    for (int i=1;i<=idx;i++) if (!vis[i]) ans^=sg(l-dep[i]+1);
    if (ans==0) puts("Bob");else puts("Alice");

}
```

---

## 作者：Leasier (赞：2)

首先，注意到这道题中填入新 01 字符串的限制跟前后缀有关，考虑抓出一棵高度为 $l + 1$ 的完全 01-Trie（因为还有根这个表示空字符串的东西）。

现在我们有 01-Trie 上的 $n$ 个**被标记的**节点，分别对应输入的 $n$ 个字符串。

每次我们新添加的字符串要满足什么呢？

- 不在任意一个被标记节点到根的链上。
- 不在任意一个被标记节点的子树内。

每次我们选出这样一个字符串后就在 01-Trie 上**标记**对应节点。

不妨考虑一下对于每个状态，我们可以在 01-Trie 上的哪些位置填字符串？

- 所有到链的路径上没有标记且子树内没有标记的点。

然后你注意到这玩意其实就是 01-Trie 上的若干完全二叉子树！

设 $SG(x)$ 表示深度为 $x$ 的完全 01-Trie 的 SG 值，我们只需要 dfs 一遍求出所有满足条件的子树的 SG 值的异或即可判断谁必胜。

考虑枚举当前选的子树深度，有：$SG(x) = \operatorname{mex}_{i = 1}^x \operatorname{xor}_{j = i}^{x - 1} SG(j)$。

打表可知 $SG(x) = \text{lowbit}(x)$。证明的话可以直接归纳。

然后就做完了。时间复杂度为 $O(\sum |s_i|)$。

代码：
```cpp
#include <stdio.h>
#include <string.h>

typedef long long ll;

typedef struct {
	int nxt[7];
} Node;

int cnt = 1;
char s[100007];
Node tree[100007];

inline void insert(char s[]){
	int len = strlen(&s[1]);
	for (int i = 1, j = 1; i <= len; i++){
		int ch = s[i] - '0';
		if (tree[j].nxt[ch] == 0) tree[j].nxt[ch] = ++cnt;
		j = tree[j].nxt[ch];
	}
}

inline ll lowbit(ll x){
	return x & (-x);
}

ll dfs(int u, ll depth){
	if (depth == 0) return 0;
	if (u == 0) return lowbit(depth);
	return dfs(tree[u].nxt[0], depth - 1) ^ dfs(tree[u].nxt[1], depth - 1);
}

int main(){
	int n;
	ll l;
	scanf("%d %lld", &n, &l);
	for (int i = 1; i <= n; i++){
		scanf("%s", &s[1]);
		insert(s);
	}
	if (dfs(1, l + 1) != 0){
		printf("Alice");
	} else {
		printf("Bob");
	}
	return 0;
}
```

---

## 作者：hater (赞：2)

看到前缀关系  我们先建一颗字典树 

可以发现 当一个点被选过（代表有一个字符串） 

那么它标记了从它到根的路径 和它的子树 

那么剩下的可以选的字符串 

构成了高度不等的的满二叉树 

而且这些二叉树是互不干扰的 我们可以搬出SG函数 

那么问题就是求树高为$L$ 的二叉树的SG函数 

$ SG(L) = mex { 0 , SG(L-1) , SG(L-1)xorSG(L-2) ....  }  $ 

实际上就是选一个深度为x点 后 会把原树分成$L-1$到$x$的满二叉树各一棵 

打表  ~~抄题解~~ 可发现这个$SG(L)=lowbit(L)$ 

之后就没事了 

```cpp
#include<bits/stdc++.h>  
#define rg register 
#define int long long 
#define i60 long long 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )
using namespace std ; 
const int N = 3e5+10 ; 
string s ; i60 ans , L ;  
int tot , ch[N][2] , tg[N] ;  
void ins( ) { 
  int n = s.length() , nw = 1 ; 
  fp( i , 1 , n ) { 
    if( !ch[nw][s[i-1]-'0'] ) ch[nw][s[i-1]-'0'] = ++tot ; 
	nw = ch[nw][s[i-1]-'0'] ;  
  } 
  tg[nw] = 1 ; 
} 
i60 sg( i60 x ) { return x&(-x) ; } 
void dfs( int x , int len ) { 
  if( tg[x] ) return ; 
  if( ch[x][0] ) dfs( ch[x][0] , len+1 ) ; else ans ^= sg( L-len ) ;  
  if( ch[x][1] ) dfs( ch[x][1] , len+1 ) ; else ans ^= sg( L-len ) ;   
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  int n ; tot = 1 ; 
  cin >> n >> L ; 
  fp( i , 1 , n ) cin >> s , ins( ) ; 
  dfs( 1 , 0 ) ; 
  cout << ( ans ? "Alice" : "Bob" ) << '\n' ;   
  return 0 ; 
} 
  
```



---

## 作者：OtterZ (赞：1)

本题解做法可推广至其他结论题，无需高级的 `sg` 函数，利好算法小白。
# 题意
给定 $n$ 个 `01` 串的集合和长度 $L$，玩游戏，每次向集合中加入一个长不大于 $L$ 的 `01` 串，要求所有时刻集合内任意两串互不为前缀，无法加入则输掉游戏，问先手或后手谁有必胜策略。
# 1.字典树
通过字典树我们可以找出所有可加入字符串的情况，对于度数为 $1$ 的节点，其没有边的字符处可以加入对应字符串。对于一个位置，如果对应的前缀长为 $x$，可以加入的字符串中长度为 $L$ 的有 $2^{L - x - 1}$ 个，我们若加入一个长为 $y(y > x)$ 的字符串，会形成 $(y - x)$ 组，第 $i$ 组对应 $2^{L - i - x - 1}$ 个长为 $L$ 的串，至此这道题变成了二进制问题。
# 2.结论：两个匹配的大小相同的组各不影响胜负
可以发现，两个匹配相同大小的组是对称的，去掉两组后，可以发现：

1. 如果去掉后当前手必胜时不会动这两组。
2. 如果去掉后当前手必败，那么他如果对任意一组操作，对手可以向另一组做同样操作，仍然无法挽回局面。

# 3.基于结论的状压动规与最终结论
我们可以跟据如上结论设计状压动规，代码如下：


```cpp
#include<cstdio>
#include<iostream>
#include<bitset>
using namespace std;
int dp[(1 << 16)];
int main(){
	dp[0] = 0;
	for(int i = 1; i < (1 << 16); i ++){
		for(int j = 1; j <= 16; j ++){
			if((i >> j - 1) & 1){
				int o = 0;
				for(int k = j; k > 0; k --){
					o = o | (1 << k - 1);
					dp[i] = dp[i] || ((!dp[i ^ o]) & 1);
				}
			}
		}
	}
}
```

状压 `DP` 是 $\operatorname{O}(L^2 2^L)$，无法解决这道题，但是我们对于 $L \le 9$ 的情况打表，由[数据](https://www.luogu.com.cn/paste/exusyvht)知大部分情况下先手胜，我们试图找后手胜的情况。

我们将[后手胜的情况](https://www.luogu.com.cn/paste/3y2bfl5o)抓出来找规律，借助数据思考知，后手有必胜策略当且仅当对任意 $k \ge 0$，大小为 $2 ^ {u2 ^ k - 1}(u >= 1)$ 的组数为偶数，否则先手胜，验证知是否符合条件的情况中符合条件的状态操作后必然不符合条件，而不符合条件的状态能一步操作变成符合条件的情况，且最终失败状态符合条件，故结论正确。

比如对于先手胜的情况 $1,4,16$，我们一步操作：

1. 去掉 $16$。
2. 对于 $2^4$ 的倍数，原先多了 $16$，为奇数，现在变成了偶数，$2^3$ 同理。
3. 对于 $2^2$，变成了奇数，我们改为操作成 $1,4,12,13,14,15$。
4. 对于 $2^1$，也变成了奇数，改为操作变成 $1,4,10,11,12,13,14,15$。
5. $2^0$ 没问题现在变成了符合对手必输的情况。
6. 我们按类似方法构造，可以验证，甚至证明这个结论。

# 证明
失败时所有余下组可以匹配，显然符合条件。

对于符合条件的情况，我们操作时假设加入在字典树中前缀长为 $z$ 的位置处开始为下一位新建节点，长为 $z + x$ 的字符串,则总可以找到 $k$ 使 $2^k | x$ 但 $2^{k + 1} \nmid x$ 得到大小为 $2 ^ {u2 ^ k - 1}(u >= 1)$ 的组的数量变化了 $\frac{x}{2^k}$，这个数量为奇数，故操作后总是不符合条件。

对于不属于条件的情况，假设 $y = \oplus_{\text{大小为} 2 ^ {u2 ^ k - 1}(u >= 1) \text{的组的数量为奇数}} 2 ^ k$，我们找出 $S$ 使得 $\oplus_{s\in S}\{2^{s + 1} - 1\} == y$，其中对于 $a = \max_{s\in S}s,b = \sum_{s\in S,s != a}s$，存在 $2 ^ {u2 ^ a - 1}(u >= 1,2\nmid u)$，通过加入操作变为 $b$ 个大小为 $2 ^ {u2 ^ a - 1 - i}$ 的组即可使操作后情况符合条件。

故符合条件时一步操作后必不符合条件，不符合条件时可以一步到达符合条件的情况，且失败情况符合条件，故结论正确。
# 效率

我们得到了大小不超过 $\sum |s_i|$ 的字典树,统计时考虑对每一个节点 $v$ 空边，当 $2 ^ k|L - len_v$ 时有一组大小 $2 ^ {2 ^ k - 1}$ 的组，暴力处理不会超过 $\log L$ 次，故为 $\operatorname{O}(\sum {|s_i|} \log v)$，可以通过。

# 代码


```cpp
#include<cstdio>
using namespace std;
int n,cst[63],cnt = 1;
long long L;
struct node{
	int len,ch[2];
	node(int l = 0){
		len = l;
		ch[0] = ch[1] = 0;
	}
}nd[100009];
char c[100009];
void add(int u,int v){
	if(c[v] == '\0')
		return;
	bool p = (c[v] - '0');
	if(nd[u].ch[p] == 0)
		nd[u].ch[p] = ++cnt,nd[cnt].len = v + 1;
	add(nd[u].ch[p],v + 1);
}
void srh(int u){//统计时叶子节点生成两个无效相同大小组，可视作额外两个匹配的组，不影响结果，无需特判 
	if(nd[u].ch[0] == 0){
		int cnt = 0;
		long long o = L - nd[u].len;
	//	printf("%d\n",o);
		if(o > 0){
			cst[0] ^= 1;
			while(!(o & 1)){
				o = o >> 1;
				cnt ++;
				cst[cnt] ^= 1;
			}
		}
	}
	else
		srh(nd[u].ch[0]);
	if(nd[u].ch[1] == 0){ 
		int cnt = 0;
		long long o = L - nd[u].len;
		//printf("%d\n",o);
		if(o > 0){
			cst[0] ^= 1;
			while(!(o & 1)){
				o = o >> 1;
				cnt ++;
				cst[cnt] ^= 1;
			}
		}
	}
	else
		srh(nd[u].ch[1]);
}
int main(){
	scanf("%d %lld",&n,&L);
	for(int i = 1; i <= n; i ++){
		scanf(" %s",c);
		add(1,0);
	}
	srh(1);
	bool flg = false;
	for(int i = 0; i < 63; i ++)//结论 
		flg = flg || cst[i];
	if(flg)
		puts("Alice");
	else
		puts("Bob");
} 

```

$60 \sim 70$ 行确实对初学者友好。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc087_c)

**题目大意**

> 定义一个 01 串集合 $S$ 是好的：
>
> - 所有元素长度在 $[1,m]$ 之间。
> - 对于所有 $s\in S$，$s$ 的所有前缀不属于 $S$。
>
> 给定初始值 $S=S_0$，Alice 和 Bob 轮流往 $S$ 中插入一个字符串，谁不能保持 $S$ 是好的就输了，求赢家。
>
> 数据范围：$L=\sum_{s\in S} |s|\le 10^5,m\le 10^{18}$。

**思路分析**

先建立 Trie 树，那么 Trie 上的点和所有叶子的子树不能选。

那么剩下来的就是一些一度点的空子树，显然这些子树之间的博弈是互不影响的，求出每个子树的 SG 值后异或起来即可。

我们只要求 $sg_n$ 表示深度为 $n$ 的空 Trie 上的博弈的 SG 函数，枚举插入字符串深度得到：
$$
sg_n=\mathrm{mex}\left\{\bigoplus_{k=n-i}^{n-1} sg_k\mid 1\le i\le n\right\}
$$
 打表发现 $sg_n=\mathrm{lowbit}(n)$，可以归纳法证明，直接求值即可。

时间复杂度 $\mathcal O(L)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
int n,tr[MAXN][2],tot=1; ll m,ans=0;
ll lowbit(ll x) { return x&-x; }
void dfs(int u,int d) {
	if(d==m) return ;
	for(int k:{0,1}) {
		if(tr[u][k]) dfs(tr[u][k],d+1);
		else ans^=lowbit(m-d);
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i) {
		string str; cin>>str; int p=1;
		for(char c:str) {
			if(!tr[p][c-'0']) tr[p][c-'0']=++tot;
			p=tr[p][c-'0'];
		}
	}
	dfs(1,0);
	cout<<(ans?"Alice":"Bob")<<"\n";
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

### 题目描述

对于两个字符串 $s, t$ , 如果 $s$ 不是 $t$ 的前缀且 $t$ 不是 $s$ 的前缀，则称他们是 prefix-free 的。

给定一个正整数 $L$，如果一个字符串集合 $S$ 符合下列条件，则我们称它为 good string set：

- $S$ 中的每个字符串的长度都在 $1$ 和 $L$ 之间（包括），并且只包含字符 $0$ 和 $1$；
- $S$ 中的每两个的字符串都是 prefix-free 的。

我们有一个 good string set $S = \{s_1, s_2, \cdots , s_n\}$，Alice 和 Bob 在玩一个游戏，他们轮流向 $S$ 中添加一个新字符串，并使 $S$ 仍是 good string set。

无法进行这个操作的人输掉游戏，假设二人都按最优策略进行游戏，求谁会赢。

$1 \leq N \leq 10^5，1 \leq L \leq 10^{18}，\sum |s| \leq 10^5$。

### 思路

我们将操作转化到 trie 树上，每次新加入一个串 $s$，在 trie 树上位于节点 $u$，那么 $u$ 的祖先节点以及子树内节点都会被删除。

容易发现不管怎样，删完后得到的都是一堆完全二叉树，这启发我们使用 $SG$ 函数找规律。

设 $SG(i)$ 表示对于一棵高为 $i$ 的完全二叉树的 $SG$ 函数，其中高为 $i$ 表示根节点到任意叶子节点的简单路径上有 $i$ 个点（注意：你可以选择根节点然后删完整棵树）。

计算 $SG(i)$ 的方法是枚举第一步策略，假设第一步在第 $j$ 层（$1\leq j\leq i$），那么得到的就是 $\bigoplus_{k=1}^{j-1} SG(i-k)$。

- $SG(0)=0$；   
- $SG(1)=\operatorname{mex}\{0\}=1$；
- $SG(2)=\operatorname{mex}\{0,1\}=2$； 
- $SG(3)=\operatorname{mex}\{0,2,3\}=1$；
- $SG(4)=\operatorname{mex}\{0,1,3,2\}=4$；
- $SG(5)=\operatorname{mex}\{0,4,5,7,6\}=1$；
- $SG(6)=\operatorname{mex}\{0,1,5,4,6,7\}=2$；

发现 $SG(i) = \operatorname{lowbit}(i)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
long long L, ans;
int trie[N][2], mark[N], tot = 1;

long long lowbit(long long x) {
	return x & -x;
}

void dfs(int x, int dep) {
	if (mark[x]) return;
	if (!x) {
		ans ^= lowbit(L - dep + 1);
		return;
	}
	dfs(trie[x][0], dep + 1);
	dfs(trie[x][1], dep + 1);
}

int main() {
	int n;
	scanf("%d%lld", &n, &L);
	for (int i = 1; i <= n; i ++ ) {
		string s;
		cin >> s;
		int p = 1;
		for (int j = 0; j < s.size(); j ++ ) {
			int c = s[j] - 48;
			if (!trie[p][c]) trie[p][c] = ++ tot;
			p = trie[p][c];
		}
		mark[p] = 1;
	}
	dfs(1, 0);
	puts(ans > 0 ? "Alice" : "Bob");
	return 0;
}
```

---

