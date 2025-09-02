# [ABC314F] A Certain Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc314/tasks/abc314_f

とあるゲームの大会に、プレイヤー $ 1 $ 、プレイヤー $ 2 $ 、$ \ldots $ 、プレイヤー $ N $ の $ N $ 人のプレイヤーが参加します。 大会の開始直前、各プレイヤーはそれぞれ $ 1 $ 人のみからなるチームをなし、全部で $ N $ 個のチームがあります。

大会では全部で $ N−1 $ 回の試合があり、各試合では $ 2 $ つの異なるチームが選ばれ、一方が先攻を、もう一方が後攻を受け持って対戦し、その結果ちょうど一方のチームが勝ちます。 具体的には、$ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について $ i $ 回目の試合は下記の通りに進行します。

- プレイヤー $ p_i $ の属するチームが先攻、プレイヤー $ q_i $ の属するチームが後攻として、対戦を行う。
- その結果、先攻チームの人数を $ a $ 、後攻チームの人数を $ b $ として、$ \frac{a}{a+b} $ の確率で先攻のチームが、$ \frac{b}{a+b} $ の確率で後攻のチームが勝つ。
- その後、勝負した $ 2 $ チームは $ 1 $ つのチームに併合される。

なお、各試合の対戦結果は他の試合の対戦結果とは独立です。

$ N $ 人のプレイヤーそれぞれについて、大会全体で自分が所属するチームが勝つという出来事が起こる回数の期待値 $ \text{mod\ }\ 998244353 $ を出力してください。

 期待値 $ \text{mod\ }\ 998244353 $ の定義この問題で求める期待値は必ず有理数になることが証明できます。 また、この問題の制約下では、求める期待値を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ p_i,\ q_i\ \leq\ N $
- $ i $ 回目の試合の直前、プレイヤー $ p_i $ が属するチームとプレイヤー $ q_i $ が属するチームは異なる。
- 入力はすべて整数

### Sample Explanation 1

チームに所属するプレイヤーの番号が $ x_1,\ x_2,\ \ldots,\ x_k $ であるチームを、チーム $ \lbrace\ x_1,\ x_2,\ \ldots,\ x_k\ \rbrace $ と呼びます。 - $ 1 $ 回目の試合では、プレイヤー $ 1 $ が所属するチーム $ \lbrace\ 1\ \rbrace $ とプレイヤー $ 2 $ が所属するチーム $ \lbrace\ 2\ \rbrace $ が対戦し、 $ \frac{1}{2} $ の確率でチーム $ \lbrace\ 1\ \rbrace $ が、$ \frac{1}{2} $ の確率でチーム $ \lbrace\ 2\ \rbrace $ が勝ちます。 その後、$ 2 $ つのチームは併合され、$ 1 $ つのチーム $ \lbrace\ 1,\ 2\ \rbrace $ になります。 - $ 2 $ 回目の試合では、プレイヤー $ 4 $ が所属するチーム $ \lbrace\ 4\ \rbrace $ とプレイヤー $ 3 $ が所属するチーム $ \lbrace\ 3\ \rbrace $ が対戦し、 $ \frac{1}{2} $ の確率でチーム $ \lbrace\ 4\ \rbrace $ が、$ \frac{1}{2} $ の確率でチーム $ \lbrace\ 3\ \rbrace $ が勝ちます。 その後、$ 2 $ つのチームは併合され、$ 1 $ つのチーム $ \lbrace\ 3,\ 4\ \rbrace $ になります。 - $ 3 $ 回目の試合では、プレイヤー $ 5 $ が所属するチーム $ \lbrace\ 5\ \rbrace $ とプレイヤー $ 3 $ が所属するチーム $ \lbrace\ 3,\ 4\ \rbrace $ が対戦し、 $ \frac{1}{3} $ の確率でチーム $ \lbrace\ 5\ \rbrace $ が、$ \frac{2}{3} $ の確率でチーム $ \lbrace\ 3,\ 4\ \rbrace $ が勝ちます。 その後、$ 2 $ つのチームは併合され、$ 1 $ つのチーム $ \lbrace\ 3,\ 4,\ 5\ \rbrace $ になります。 - $ 4 $ 回目の試合では、プレイヤー $ 1 $ が所属するチーム $ \lbrace\ 1,\ 2\ \rbrace $ とプレイヤー $ 4 $ が所属するチーム $ \lbrace\ 3,\ 4,\ 5\ \rbrace $ が対戦し、 $ \frac{2}{5} $ の確率でチーム $ \lbrace\ 1,\ 2\ \rbrace $ が、$ \frac{3}{5} $ の確率でチーム $ \lbrace\ 3,\ 4,\ 5\ \rbrace $ が勝ちます。 その後、$ 2 $ つのチームは併合され、$ 1 $ つのチーム $ \lbrace\ 1,\ 2,\ 3,\ 4,\ 5\ \rbrace $ になります。 プレイヤー $ 1,\ 2,\ 3,\ 4,\ 5 $ それぞれの、大会全体で自分が所属するチームが勝つという出来事が起こる回数の期待値 $ E_1,\ E_2,\ E_3,\ E_4,\ E_5 $ は、それぞれ $ \frac{9}{10},\ \frac{9}{10},\ \frac{53}{30},\ \frac{53}{30},\ \frac{14}{15} $ です。

## 样例 #1

### 输入

```
5
1 2
4 3
5 3
1 4```

### 输出

```
698771048 698771048 964969543 964969543 133099248```

## 样例 #2

### 输入

```
15
9 2
8 10
13 6
12 11
7 10
4 10
14 2
5 4
1 15
15 2
6 9
8 11
6 3
2 8```

### 输出

```
43970290 310168785 806914186 501498951 950708909 272140427 335124893 168750835 310168785 168750835 280459129 280459129 272140427 476542843 43970290```

# 题解

## 作者：Fire_flame (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc314_f)

关于我模数写错调了 $15$ 分钟这件事，警钟敲烂。

## $\mathtt{Solution}$

一个 `kruskal` 重构树和并查集的做法。

令 $num_i$ 为节点 $i$ 子树 $1\sim n$ 节点的个数，$fa_i$ 为 $i$ 的祖先，$find(i)$ 为 $i$ 子树的根。

$p_i$ 和 $q_i$ 的队伍对战以后，发现 $find(p_i)$ 和 $find(q_i)$ 的子树内部都要加上相应的概率。

于是给 $find(p_i)$ 和 $find(q_i)$ 分别打上标记，然后创建一个新的节点，将两颗树合并到这个节点上面。

最后，从整棵树的根节点出发，将所有标记下放即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MOD = 998244353, MAXN = 5e5 + 5;
int n, fa[MAXN], num[MAXN], p[MAXN], q[MAXN], cnt, ls[MAXN], rs[MAXN], ans[MAXN], res[MAXN];
int find(int x){
	if(fa[x] == x)return x;
	return fa[x] = find(fa[x]);
}
int fpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1)res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
void dfs(int x, int p){
	res[x] = (ans[x] + p) % MOD;
	if(ls[x])dfs(ls[x], (p + ans[x]) % MOD);
	if(rs[x])dfs(rs[x], (p + ans[x]) % MOD);
//	printf("%lld %lld\n", x, p);
}
signed main(){
	n = read(), cnt = n;
	for(int i = 1;i <= n;i ++)num[i] = 1;
	for(int i = 1;i < MAXN;i ++)fa[i] = i;
	for(int i = 1;i < n;i ++){
		p[i] = read(), q[i] = read();
		int x = find(p[i]), y = find(q[i]);
		ls[++ cnt] = x, rs[cnt] = y;
		fa[x] = fa[y] = cnt;
		num[cnt] = num[x] + num[y];
		ans[x] = num[x] * fpow(num[cnt], MOD - 2) % MOD;
		ans[y] = num[y] * fpow(num[cnt], MOD - 2) % MOD;
//		printf("%lld %lld %lld %lld %lld\n", x, y, num[x], num[y], cnt);
	}
	dfs(cnt, 0);
	for(int i = 1;i <= n;i ++)
		printf("%lld ", res[i]);
	
	return 0;
}

```


---

## 作者：xlpg0713 (赞：7)

## 题意：
有 $n$ 名球员，进行 $n-1$ 场比赛。对于每场比赛，给定信息 $p,q$。那么这场比赛的参赛方为编号为 $p, q$ 的球员所在的队伍，设为 $a,b$ 队，分别有 $|a|,|b|$ 人。那么 $a$ 队与 $b$ 对的获胜概率分别为 $\dfrac{|a|}{|a|+|b|}$ 与 $\dfrac{|b|}{|a|+|b|}$。每场比赛后参赛两队将合并为一支新的队伍。现请求出拥有第 $i$ 号球员的队伍的获胜概率的期望。对 $998244353$ 取模。

## 分析：
对于每一个点，我们需要维护他所属的队伍与他的队伍的获胜信息，考虑使用并查集维护所属集合和路径上的信息。具体操作为：对于 $p, q$ 查他在并查集上的祖先 $f_p, f_q$。计算概率并将 $tag$ 打在祖先上。这样对于每一个点，我们只需要一直查他的祖先，并将路径上的 $tag$ 值加起来，则得到一个点的答案。

由于需要路径上的信息，不建议使用路径压缩。但是看一眼数据范围，暴力是过不了的，因此使用按秩合并。数据范围不需要我们线性地求逆元，只需要快速幂即可。

注意：在合并 $x, y$ 两个集合时（例如：将 $x$ 集并在 $y$ 集上），由于合并前 $y$ 集的信息不应包含 $x$ 集。因此在合并时应给 $tag_x$ 减上 $tag_y$ 这样能保证查出来的数据是正确的。

## 代码：
```
#include<bits/stdc++.h>
#define int long long //没把握就define全局long long
using namespace std;
int n, p, q; const int mod = 998244353;
int siz[200005], fa[200005], tag[200005];//并查集数组
inline int find(int x){ //查祖先
    if(x == fa[x]) return x;
    return find(fa[x]);
}
inline void merge(int x, int y){ //合并
    if(siz[x] <= siz[y]){ //按秩合并
        fa[x] = y;
        siz[y] += siz[x];
        tag[x] = (tag[x] - tag[y] + mod) % mod; //记得减tag和取模
    }
    else{
        fa[y] = x;
        siz[x] += siz[y];
        tag[y] = (tag[y] - tag[x] + mod) % mod;
    }
} 
inline int qpow(int a, int b){
    int res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        b >>= 1; a = a * a % mod;
    }return res;
}
inline int cacl(int p){ //计数
    int res = 0;
    while(p != fa[p]) res = (res + tag[p]) % mod, p = fa[p];
    return (res + tag[p])%mod; //别忘了加根
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cin >> n;//一定注意要读入（麻赛时没读入wa了两发最后也没调出来）
    for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1; //初始化
    for(int i = 1 && cin >> p >> q; i < n; i++ && cin >> p >> q){ //顺带读入
        int x = find(p), y = find(q);
        int sum = siz[x] + siz[y]; int inv = qpow(sum, mod - 2); //逆元
        tag[x] = (tag[x] + siz[x] * inv) % mod;
        tag[y] = (tag[y] + siz[y] * inv) % mod; //打tag
        merge(x, y); //合并
    }
    for(int i = 1; i <= n; i++){
        cout << cacl(i) << ' ';
    }return 0;
}
```

---

## 作者：ダ月 (赞：6)

### 题意概要

给定 $n$ 个集合，每个集合初始有 $1$ 个元素 $0$。现进行 $n-1$ 次操作，每次给定 $x,y$，记 $sz_x$ 为 $x$ 所在集合元素数量，$sz_y$ 所在集合元素数量，将 $x$ 所在集合中所有元素加上 $\frac{sz_x}{sz_x+sz_y}$，将 $y$ 所在集合中所有元素加上 $\frac{sz_y}{sz_x+sz_y}$，然后将两个集合进行合并。问操作完后，所有元素的值是多少。答案对 $998244353$ 取模，同时保证，合并前的两个元素在不同集合。

### 题目分析

合并集合，计算集合元素大小，这个事好办，我们可以并查集来维护。

但是要对集合内所有元素修改，这不能用原版的并查集来修改。显然，如果集合内元素一个一个修改，肯定超时，我们需要一个懒标记来维护集合元素大小。

但是这个懒标记打到哪里呢，打到 $x$ 所指向的父亲上面？显然不行，因为并查集儿子走父亲简单，父亲走儿子困难。

这时我想到了 kruskal 重构树的那个并查集使用。就是每次合并两个集合时，我们创建一个虚结点，将 $x,y$ 的父亲指向这个虚点，这样，我们打标记可以直接在这个虚点上打。最后所有操作完后，显然这会构成一棵树。然后我们遍历一遍这棵树来下放标记（我的代码写的是标记永久化）。

[code](https://atcoder.jp/contests/abc314/submissions/44521457)。

---

## 作者：缪凌锴_Mathew (赞：4)

### 解题思路
很容易想到并查集可以维护集合合并，每一个集合用 vector 存储集合中的元素，并记录集合大小 $siz$。

对于每一次集合 $x,y$ 的比赛，集合 $x$ 中所有元素的获胜期望增加 $\dfrac{siz_x}{siz_x+siz_y}$，集合 $y$ 中所有元素的获胜期望增加 $\dfrac{siz_y}{siz_x+siz_y}$。

每一次合并集合 $x$ 和 $y$，暴力将 $y$ 中所有元素加入 $x$，更新 $siz_x=siz_x+siz_y$。

对于每一个人，他打多少次比赛就更新多少次答案，所以复杂度最劣情况为 $O(n^2)$。

考虑优化，发现可以给集合打 tag 更新，最后所有元素加上最终集合 tag。

每个集合维护一个 $sum$。合并集合 $x$ 和 $y$ 时，$sum_x=sum_x+\dfrac{siz_x}{siz_x+siz_y}$，$sum_y=sum_y+\dfrac{siz_x}{siz_x+siz_y}$。

将 $y$ 中答案合并到 $x$ 中时，原本答案在最后应 $+sum_y$，但直接合并最后就变成 $+sum_x$，因此合并答案时应将答案 $+sum_y-sum_x$。

打了 tag 后，合并复杂度为 $O(siz_y)$，总复杂度卡到最劣还是 $O(n^2)$。发现已经可以按秩合并（将 $siz$ 小集合的合并到大的集合中），按秩合并总复杂度 $O(n\log n)$。

复杂度证明：对于每一个人，他所在的集合合并时若将这个人暴力合并，集合大小至少 $\times2$，集合大小最大为 $n$，每个人最多暴力合并 $\log n$ 次。

### 代码

```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
const int N=2e5;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
const int mod=998244353;
int n;
int pre[MAXN],siz[MAXN];
int inv[MAXN];
int Ans[MAXN];
int find(int x){
    if(pre[x]==x){
        return x;
    }
    pre[x]=find(pre[x]);
    return pre[x];
}
vector <int> vec[MAXN];
vector <int> ans[MAXN];
int sum[MAXN];
void join(int x,int y){
    for(int i=0;i<siz[y];i++)//暴力将y中的元素合并到x中
    {
        vec[x].push_back(vec[y][i]);
        ans[x].push_back((1ll*ans[y][i]+mod+sum[y]-sum[x])%mod);
    }
    siz[x]+=siz[y];
    pre[y]=x;
}
void init(){
    inv[1]=1;
    for(int i=2;i<=n;i++)//预处理逆元
    {
        inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
    }
    for(int i=1;i<=n;i++)
    {
        vec[i].push_back(i);
        ans[i].push_back(0);
        pre[i]=i;
        siz[i]=1;
    }
}
signed main(){
    scanf("%d",&n);
    init();
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=find(x);
        y=find(y);
        if(siz[x]<siz[y]){//按秩合并优化
            swap(x,y);
        }
        //更新sum
        sum[x]+=1ll*siz[x]*inv[siz[x]+siz[y]]%mod;
        sum[x]%=mod;
        sum[y]+=1ll*siz[y]*inv[siz[x]+siz[y]]%mod;
        sum[y]%=mod;
        join(x,y);
    }
    int tot=find(1);//最终集合
    for(int i=0;i<n;i++)
    {
        Ans[vec[tot][i]]=(ans[tot][i]+sum[tot])%mod;
    }
    for(int i=1;i<=n;i++)
    {
        printf("%d ",Ans[i]);
    }
    return 0;
}
```

---

## 作者：zhangjiting (赞：3)

## 思路

整个过程如下图：

![](https://img.atcoder.jp/abc314/98f0c3212584232f0fda47c6f40ae1bf.png)

上面的有根树对应于样例 $1$。

每个节点都对应比赛中某一时刻的一支球队；尤其是，每片叶子都对应（仅由）一名球员组成的球队。我们将对应于球队 $A$ 的节点简单地称为节点 $A$。

具体来说，$T$ 是通过以下程序构建的。

- 首先，从有 $N$ 个节点 $0$ 条边的图 $T$ 开始。
    
- 然后，按以下方式，依次更新 $i$ 中的 $T$。
    
    - 设 $A$ 和 $B$ 是参与比赛 $i$ 的球队。添加节点 $(A \cup B)$，并让节点 $A$ 和节点 $B$ 成为节点 $(A \cup B)$ 的子节点。
    - 连接节点 $(A \cup B) $和节点 $A$ 的边的权重设为节点 $A$ 赢得比赛 $i$ 的概率 $|A|/(|A|+|B|)$；同样，节点 $(A \cup B)$ 和节点 $B$ 之间的边的权重设为 $|B|/(|A|+|B|)$，即球队 $B$ 的胜率。

我们可以使用**并查集**来模拟上述过程，从而构建一棵有根树 $T$。

时间复杂度为 $O(n)$。

## 代码

还没写。

---

## 作者：FFTotoro (赞：3)

考虑合并队伍的性质，显然一路合并上去这个结构是个树。用启发式合并的思想，每次先把 $p_i,q_i$ 找个并查集里面的祖先，然后把大小比较小的那个集合向大集合连边（大集合的祖先现在变成小集合的祖先的父亲）。

最后对于每个点跳父亲查找、累加贡献即可。记得每次合并两个集合的时候大集合要减去小集合的贡献，因为跳父亲的时候会被算一次而它本来不该被算进去。

实现借助了 AtCoder Library 的并查集和 `modint`。

放代码：

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using mint=atcoder::modint998244353;
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<int> p(n,-1);
  vector<mint> c(n);
  atcoder::dsu d(n);
  for(int i=1;i<n;i++){
    int u,v; cin>>u>>v; u--,v--;
    u=d.leader(u),v=d.leader(v);
    int a=d.size(u),b=d.size(v);
    if(u!=d.merge(u,v))swap(u,v),swap(a,b);
    c[u]+=mint(a)/(a+b),c[v]+=mint(b)/(a+b)-c[u],p[v]=u;
  } // 连边过程
  vector<bool> b(n);
  function<void(int)> dfs=[&](int u){
    if(!b[u])if(b[u]=true;~p[u])dfs(p[u]),c[u]+=c[p[u]];
  }; // 继承父亲
  for(int i=0;i<n;i++)
    dfs(i),cout<<c[i].val()<<' ';
  return 0;
}
```

---

## 作者：Xuan_qwq (赞：3)

### 一句话题意
$N$ 个人，最开始一人一队，有 $N-1$ 次比赛，每次是 $p_i$ 和 $q_i$ 两人所在的队伍比，每队获胜的概率为该队人数比上两队总人数，比完后两队合并为一队。

求每人期望胜利次数。

---

看到 “合并” 这个词，我们很容易就会想到并查集。我们把一个队伍看作一个节点，那么在合并两个节点的时候，我们就会新建一个节点，把两个节点的父亲设为新节点，同时记录这个新队伍有多少人。这样可以很方便求出一次合并时两队获胜的概率。

但是，概率是求出来了，该怎么传递给每一个人呢？

我们可以借用线段树 pushdown 操作的思想：当父节点要让其子树的所有节点都加 $1$ 时，先给它的左右儿子加 $1$，再让子节点去把这个 $1$ 传下去。

我们先记录每次合并时是由哪两个节点合并成当前节点的。

然后从最终合并出的大节点开始，做 pushdown 操作，将每一个节点获得的期望获胜次数，分别加上它左右儿子在合并时的胜率，再传给它的左右儿子即可。终止条件为到达一个叶子节点，根节点获得的期望获胜次数为 $0$。

![图解](https://cdn.luogu.com.cn/upload/image_hosting/szh3ttsh.png)

图解为样例所对应的树。

最后把所有叶子节点所得到的期望获胜次数输出即可。

### 代码

记得开 long long，血的教训。

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll ksm(ll a,ll q){
	ll ret=1;
	while(q){
		if(q&1)ret=ret*a%mod;
		a=a*a%mod;
		q>>=1;
	}
	return ret;
}
ll siz[400005],l[400005],r[400005],ans[400005],fa[400005];
//节点队伍人数，左儿子，右儿子，期望获胜次数，父节点
ll n;
ll find(int x){//并查集
	if(fa[x]==x)return fa[x];
	return fa[x]=find(fa[x]);
}
void dfs(int now,ll nxt){//pushdown操作
	ans[now]=nxt;
	if(siz[now]==1)return;
	dfs(l[now],(nxt+(siz[l[now]]*ksm(siz[now],mod-2))%mod)%mod);
	dfs(r[now],(nxt+(siz[r[now]]*ksm(siz[now],mod-2))%mod)%mod);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	for(int i=1;i<n;i++){
		int q,p;
		cin>>q>>p;
        //合并
		int a=find(q),b=find(p);
		l[n+i]=a;
		r[n+i]=b;
		siz[n+i]=siz[a]+siz[b];
		fa[a]=n+i;
		fa[b]=n+i;
		fa[n+i]=n+i;
	}
	dfs(2*n-1,0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Keroshi (赞：1)

首先，记录团队的方式肯定是通过并查集的方式实现。   
随后想如何将每次比赛赢的概率进行分配，  
可以想到建二叉树，新合并团队向两个旧团队两条边。  
其中第一个样例建出来的二叉树如下。   
![](https://cdn.luogu.com.cn/upload/image_hosting/uylb339s.png)    
其中第 $9$ 号节点是包括 $1$ 到 $n$ 节点的总团队，把它作为根节点。   
其中一个 $n$ 以上的节点代表了一次比赛和团队合并。  
然后假如一个代表团队的节点会有获得赢得一场比赛的概率，那么这个团队的所有人就应该加上这个概率，   
也就是团队节点的子树的所有叶子节点，  
考虑 dfs 解决。   
将子树能获得的概率递归累加即可。  
```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    REP(i, n - 1) cin >> p[i] >> q[i];
    vector<int> b(n + 1), c(n * 2 + 1); 
    // b 表示一个并查集的首领现在的团队
    // c 表示一个团队的人数
    int cnt = n;
    vector<vector<int>> e(n * 2 + 1);
    DSU f(n);
    // 并查集
    FOR(i, 1, n) {
        c[i] = 1;
        b[i] = i;
    }
    REP(i, n - 1) {
        int u = p[i];
        int v = q[i];
        u = f.find(u);
        v = f.find(v);
        f.conc(v, u);
        int cur = ++cnt;
        e[cur].push_back(b[u]);
        e[cur].push_back(b[v]);
        // 建图
        c[cur] = c[b[u]] + c[b[v]];
        b[u] = cur;
    }
    vector<mint> A(n + 1); // A 表示答案
    func(void(int, mint)) dfs = [&] (int u, mint x) {
        if(u <= n) { // 叶子节点
            A[u] += x;
            return;
        }
        vector<int> ch;
        for(auto v : e[u]) {
            ch.push_back(v);
        }
        // 计算概率
        mint X = mint(c[ch[0]]) / mint(c[u]);
        mint Y = mint(c[ch[1]]) / mint(c[u]);
        dfs(ch[0], x + X);
        dfs(ch[1], x + Y);
    };
    dfs(cnt, 0);
    FOR(i, 1, n) cout << A[i] << " ";
    cout << endl;
}
```

---

## 作者：Supor__Shoep (赞：1)

本蒟蒻非常遗憾啊，有了正确的思路却没有在赛时切掉。。。

由于两个集合会有合并操作，所以不难想到用并查集。但是我们需要思考：两个队伍合并时怎么处理对每个成员的代价。如果是暴力计算一次合并对所有成员产生的代价，那么时间复杂度趋近于 $O(n)$，进行 $n-1$ 次合并就会达到 $O(n^2)$。劣！！！

设第 $i$ 次合并的是 $p_i$ 和 $q_i$ 的所在集合，$p_i$ 在 $A$ 集合，$q_i$ 在 $B$ 集合，那么这一次合并对 $A$ 的所有元素的代价就是 $W_A=\dfrac{|A|}{|A|+|B|}$，对 $B$ 的所有元素的代价就是 $W_B=\dfrac{|B|}{|A|+|B|}$。此时联想一下 $A$ 和 $B$ 用并查集储存时它们的结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/qvbix4nx.png)

并查集的每次合并就相当于两个并查集之间连接了一条边，经过了若干次合并之后**一定就会形成一棵树**，此时并查集中查找的祖先 $find(x)$ 就相当于是根节点。如图所示：黑边组成的就是两棵树，根节点分别为 $1,2$，现在要合并两棵树，就是在两个根节点之间连一条边（即蓝色边）。回到本题，我们上文所计算出的 $W_A$ 的影响范围是就 $A$ 所构成的一棵树中的节点，$W_B$ 则是 **合并后** $B$ 的树中除了 $A$ 以外的所有节点。根据这样的结构我们就可以想到 **树上差分** 了，拿上图举例：我们在 $2$ 节点所代表的差分值增加 $W_B$，然后在 $1$ 节点所代表的差分值增加 $W_A-W_B$。如果我们现在要求每一个节点的答案，我们就从整棵树的根节点**向下求差分值的前缀和**，就可以得到每一个节点的答案了。

值得注意的是，这题要对分数进行取模，原题中介绍的求法是解同余方程，但是我还是推荐逆元求法，如果要求 $\dfrac{x}{y} ~\text{mod}~p$，设 $c$ 为 $b$ 的逆元，我们直接求出 $(a\times c) ~\text{mod}~ p$ 就可以了。而分数的加减法就非常简单了，直接模拟即可，但是要注意取模：如果 $x<0$，那就一定要赋值成 $x+p\times \lceil \dfrac{-x}{p}\rceil$，如果只加上一个 $p$ 可能还是会出现负数。本人就是因为这题奇怪的取模所以没能场切QAQ。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
const int MOD=998244353;
int n;
int quick_pow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)	res=res*x%MOD;
		x=x*x%MOD;
		y>>=1;
	}
	return res;
}
int fa[MAXN],siz[MAXN];
int cf1[MAXN],cf2[MAXN];//由于是分数，所以差分值也拆成了分子分母 
vector<int> vec[MAXN];
int find(int x)
{
	if(fa[x]==x)	return x;
	return fa[x]=find(fa[x]);
}
int gcd(int x,int y){ return !y?x:gcd(y,x%y); }
void add(int &a,int &b,int c,int d)//分数加法（减法可以转换成加法） 
{
	int up=a*d+b*c,down=b*d;
	int G=gcd(up,down);
	up/=G,down/=G;
	a=up,b=down;
	if(a<0)	a+=(-a)/MOD*MOD;
	if(b<0)	b+=(-b)/MOD*MOD;
	a=(a+MOD)%MOD,b=(b+MOD)%MOD;
}
void dfs(int x,int qz,int qm)//求差分值的前缀和 
{
	int len=vec[x].size();
	add(qz,qm,cf1[x],cf2[x]);
	cf1[x]=qz,cf2[x]=qm;
	for(int i=0;i<len;i++)	dfs(vec[x][i],qz,qm);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	fa[i]=i,siz[i]=1,cf2[i]=1;//初始化 
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		x=find(x),y=find(y);
		int p=siz[x],q=siz[x]+siz[y];
		int G=gcd(p,q);
		p/=G,q/=G,add(cf1[x],cf2[x],p,q);
		p=siz[y],q=siz[x]+siz[y];
		G=gcd(p,q);
		p/=G,q/=G,add(cf1[y],cf2[y],p,q);
		if(x!=y)	fa[x]=y,siz[y]+=siz[x],vec[y].push_back(x),add(cf1[x],cf2[x],-cf1[y],cf2[y]);//差分 
	}
	dfs(find(1),0,1);
	for(int i=1;i<=n;i++)	cout<<cf1[i]*quick_pow(cf2[i],MOD-2)%MOD<<" ";//逆元输出答案 
	return 0;
}
```

---

## 作者：rickyxrc (赞：1)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

初始时有 $n$ 个团队，每个团队 $i$ 都只有一个编号为 $i$ 的人，现在有 $n-1$ 场比赛，比赛的胜率通过如下方法得出：

设 $i,j$ 两团队进行比赛，人数分别为 $s_i,s_j$，则双方的胜率分别为 $\frac{s_i}{s_i+s_j},\frac{s_j}{s_i+s_j}$。

在比赛完之后，两个团队的人便会合并成一个团队（不打不相识？），现在要求你输出所有比赛完之后每个人期望赢几场比赛。

保证输入样例合法，不存在同一个团队比赛的情况。

## 解题思路

这个合并操作让我想起了并查集和树。

我们将一个人获胜的期望定义为在这棵并查集森林（当然最后是树）中，自己这个点的和根节点连线的权值和。

权值如何定义呢？自然是比赛时双方的胜率。

但是我们模拟两下就会发现一个问题：这样累计会让下方的节点期望错误地加上上方节点的期望导致偏高，那我们减回去就行了。

至于节点上下的问题，这个其实不重要，但是我写了启发式合并怕被卡。

```cpp
#include <stdio.h>

typedef long long i64;
const i64 mod = 998244353, maxn = 400007;

i64 pow(i64 x, i64 p);

struct modint
{
    i64 x;
    modint(i64 x_ = 0)
    {
        if (x_ < 0)
            x = (x_ % mod + mod) % mod;
        else if (x_ >= mod)
            x = x_ % mod;
        else
            x = x_;
    }
    modint inv() { return pow(x, mod - 2); }
    modint operator+=(modint b);
    modint operator-=(modint b);
    modint operator*=(modint b);
    modint operator/=(modint b);
};

modint operator+(modint a, modint b);
modint operator-(modint a);
modint operator-(modint a, modint b);
modint operator*(modint a, modint b);
modint operator/(modint a, modint b);
modint pow(modint x, i64 p);
bool operator==(modint a, modint b);

int fa[maxn], size[maxn], kzy[maxn];
modint val[maxn];

int findf(int index)
{
    return fa[index] == index ? index : findf(fa[index]);
}

modint tj(int index)
{
    if (fa[index] == index)
        return val[index];
    return tj(fa[index]) + val[index];
}

void merge(int u, int v)
{
    u = findf(u);
    v = findf(v);
    if (size[u] > size[v])
        u ^= v ^= u ^= v;
    val[v] += modint(size[v]) / modint(size[u] + size[v]);
    val[u] -= val[v]; // 像上文说的那样，这里需要减去上面的值，类似于差分的思想
    val[u] += modint(size[u]) / modint(size[u] + size[v]);
    fa[u] = v;
    size[v] += size[u];
}

int n, u, v;

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        fa[i] = i, size[i] = 1, val[i] = 0;

    for (int i = 1; i < n; i++)
        scanf("%d%d", &u, &v),
            merge(u, v);

    for (int i = 1; i <= n; i++)
        printf("%lld ", tj(i));
    return 0;
}
```


---

## 作者：Ginger_he (赞：0)

~~我不会告诉你我赛场上没想到 kruskal 重构树。~~

合并两个集合，又与集合大小有关，不难想到用按子树大小合并的并查集来维护。

考虑合并两个集合 $x,y$，不妨令 $s_x\ge s_y$，可以先让父亲为 $y$ 的点都加上 $\frac{s_y}{s_x+s_y}$，然后给 $x$ 打个 tag，表示原来父亲就是 $x$ 的点（即 $x$ 的某段前缀）都加上 $\frac{s_x}{s_x+s_y}$，这个差分一下就能解决，然后当 $x$ 被合并到更大的集合时再加上具体数值。

代码是用 vector 实现的。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
const int p=998244353;
int n,x,y,f[N],s[N],ans[N];
vector<int> v[N],c[N];
int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%p;
		b>>=1;
		a=1ll*a*a%p;
	}
	return res;
}
int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		v[i].push_back(i);
		c[i].push_back(0);
		c[i].push_back(0);
		f[i]=i,s[i]=1;
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		x=find(x),y=find(y);
		if(s[x]<s[y]) swap(x,y);
		int res=0,tmp=v[x].size();
		for(int j=0;j<v[y].size();j++)
		{
			int k=v[y][j];
			v[x].push_back(k);
			c[x].push_back(0);
			res=(res+c[y][j])%p;
			ans[k]=(ans[k]+(res+1ll*s[y]*quickpow(s[x]+s[y],p-2)%p)%p)%p;
			f[k]=x;
		}
		res=1ll*s[x]*quickpow(s[x]+s[y],p-2)%p;
		c[x][0]=(c[x][0]+res)%p,c[x][tmp]=((c[x][tmp]-res)%p+p)%p;
		s[x]+=s[y];
	}
	int rt=find(1),res=0;
	for(int i=0;i<v[rt].size();i++)
	{
		int j=v[rt][i];
		res=(res+c[rt][i])%p;
		ans[j]=(ans[j]+res)%p;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：robertuu (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc314_f)

[AT原题传送门](https://atcoder.jp/contests/abc314/tasks/abc314_f)

由于有合并操作，很明显可以想到并查集和二叉树结构。

每次合并时，用分数加法的规则将新的概率 $\frac {sz_x}{sz_x+sz_y}$ 累加到各自根的答案中（相当于所在的整个集合都加了），再为两个点的创建一个公共根（新的节点），公共根的两个儿子是原本两个点的根（方便最后用 `dfs` 算答案）。

并查集合并时仍然用启发式合并，不需要保证树的结构，只需要直到各自的根。树的结构（表示合并过程，包含答案信息）通过每个点左右儿子表示，最终的根会是最后一个添加的公共根。

最后用 `dfs` 计算结果，每一次将父节点的答案累加到子节点上（有点标记下传的感觉），在递归左右儿子（没有儿子直接返回，不可能只有一个儿子）。

分数加法可以很暴力，直接 $\frac{x}{y} + \frac{z}{w} = \frac{xw+yz}{yw}$ 就可以，算的时候乘法必须取模（全程相当于没用除法）。

最后要输出**逆元**，由于取模的模数 $998244353$ 是质数，可以直接用费马小定理求逆元，$\frac{x}{y}$ 对应的答案是 $x \times y^{p-2}$，$p$ 为模数。

AC code（注意开 `long long` 和使用 `1ll`）：
```cpp
#include<iostream>
using namespace std;
const int mod = 998244353;
int qpow(int x,int k)
{
	long long ans = 1;
	while(k)
	{
		if(k&1) ans = (ans*x)%mod;
		x = (1ll*x*x) % mod;
		k >>= 1;
	}
	return ans;
}
int fz[400001],fm[400001],son1[400001],son2[400001];
int fa[400001],sz[400001],N;
int find(int x)
{
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x,int y)
{
	fa[x] = fa[y] = ++N;
	son1[N] = x; son2[N] = y;
	sz[N] = sz[x] + sz[y];
	sz[x] = sz[y] = 0;
}
void dfs(int x)
{
	if(!x) return;
	int p,tmp;
	if(son1[x] != 0)
	{
		p = son1[x]; tmp = fm[p];
		fm[p] = 1ll * fm[p] * fm[x] % mod;
		fz[p] = 1ll * fz[p] * fm[x] % mod + 1ll * fz[x] * tmp % mod;
	}
	if(son2[x] != 0)
	{
		p = son2[x]; tmp = fm[p];
		fm[p] = 1ll * fm[p] * fm[x] % mod;
		fz[p] = 1ll * fz[p] * fm[x] % mod + 1ll * fz[x] * tmp % mod;
	}
	dfs(son1[x]);
	dfs(son2[x]);
}
int main()
{
	int n,p,q;
	scanf("%d",&n);
	N = n;
	for(int i = 1;i <= 2*n;i++)
	{
		fa[i] = i;
		sz[i] = 1;
		fm[i] = 1;
	}
	for(int i = 1;i < n;i++)
	{
		scanf("%d%d",&p,&q);
		p = find(p); q = find(q);
		// p win
		int tmp = fm[p];
		fm[p] = 1ll * fm[p] * (sz[p] + sz[q]) % mod;
		fz[p] = 1ll * fz[p] * (sz[p] + sz[q]) % mod + 1ll * sz[p] * tmp % mod;
		// q win
		tmp = fm[q];
		fm[q] = 1ll * fm[q] * (sz[p] + sz[q]) % mod;
		fz[q] = 1ll * fz[q] * (sz[p] + sz[q]) % mod + 1ll * sz[q] * tmp % mod;

		merge(p,q);
	}
	dfs(N);
	for(int i = 1;i <= n;i++)
		cout << 1ll * fz[i] * qpow(fm[i],mod-2) % mod << " ";
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意
有 $n$ 支队伍初始每队一人，进行 $n-1$ 场比赛，每次比赛按人数分配胜率并合并，求每个人获胜次数的期望。

## 题目分析

大水题，就是要实现并查集的各数加。直接模拟就行，然后将比赛过程建成一棵树，中途维护一个大小以计算胜率，最后便利计算答案就行了。

由于要求逆元，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned long long
#define e(x) for(int i=h[x];i;i=nxt[i])
#define Pi pair<int,int>
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=1e5+5,inf=2147000000;
const ll mod=998244353;
using namespace std;
int n,ans[N],h[N],to[N],nxt[N],cnt,siz[N],f[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
inline ll qp(ll a,ll b){
	if(!b)return 1;
	ll c=qp(a,b>>1);
	c=c*c%mod;
	if(b&1)c=c*a%mod;
	return c;
}
inline void dfs(int x){
	e(x){
		int y=to[i];
		(ans[y]+=ans[x])%=mod;
		dfs(y);
	}
}
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
signed main(){
	n=read();
	rep(i,1,n)siz[i]=1,f[i]=i;
	for(int i=1,x,y;i^n;i++){
		x=read(),y=read();
		int l=find(x),r=find(y),Ll=siz[l],Rr=siz[r];
		int k=qp(Ll+Rr,mod-2);
		int X=Ll*k%mod,Y=Rr*k%mod;
		(ans[l]+=(X-Y-ans[r]+mod+mod)%mod)%=mod,(ans[r]+=Y%mod)%=mod;
		add(r,l),f[l]=r,siz[r]+=siz[l];
	}
	int root=find(1);
	dfs(root);
	rep(i,1,n)pf(ans[i]),putchar(' ');
	
	return 0;
}
```


---

## 作者：flangeborg (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc314_f)

#### 题目大意
原题的翻译已经给得比较清晰，这里不再赘述

### 解题思路

可以发现这题需要使用并查集来求解，但是朴素的并查集对集合中的元素进行加法 的时间复杂度是 $O(n)$ 的，这会导致整体操作的复杂度上升至 $O(n^2)$，所以我们要在并查集的基础上对其存储结构进行优化。

根据题意，每两支进行对战的队伍会合并成为一支新的队伍，容易想到这是一种类似于二叉树的结构。所以，对于对战的两支队伍 $i$ 和 $j$，我们可以新建一个节点 $k$ 来做这两个节点的父亲，然后并查集也进行合并，将 $i$ 和 $j$ 所指向的集合队首改为 $k$，之后的计算就可以直接在 $k$ 中执行，当所有操作结束后，用深搜将计算结果下传至原本的 $n$ 个节点上，取模后输出即可。

```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<stack>
#define ll long long
using namespace std;
const ll Mode = 998244353;
struct js{
	ll s1,s2;
	// 分子 分母 
};
struct node{
	ll l,r,_size;
	js data;
}tree[800005];
ll n,f[800005];
void ex_gcd(ll a,ll b,ll &x,ll &y)
{
	if(a % b == 0) x = 0,y = 1;
	else ex_gcd(b,a % b,y,x),y -= a / b * x;
}
ll __lcm(ll a,ll b)
{
	ll gcd = __gcd(a,b);
	return a / gcd * b;
}
ll find(ll now)
{
	if(f[now] == now) return now;
	return f[now] = find(f[now]);
}
void dfs(ll now)
{
	ll l_son = tree[now].l,r_son = tree[now].r;
	if(!l_son && !r_son) return;
	ll l_s1 = tree[l_son].data.s1,l_s2 = tree[l_son].data.s2;
	ll r_s1 = tree[r_son].data.s1,r_s2 = tree[r_son].data.s2;
	ll lcm_l = __lcm(tree[now].data.s2,l_s2),lcm_r = __lcm(tree[now].data.s2,r_s2);
	ll now_l_s1 = tree[now].data.s1 * (lcm_l / tree[now].data.s2),now_r_s1 = tree[now].data.s1 * (lcm_r / tree[now].data.s2);
	l_s1 *= (lcm_l / l_s2),r_s1 *= (lcm_r / r_s2);
	ll temp_l_s1 = l_s1 + now_l_s1,temp_r_s1 = r_s1 + now_r_s1;
	ll gcd_l = __gcd(temp_l_s1,lcm_l),gcd_r = __gcd(temp_r_s1,lcm_r);
	temp_l_s1 /= gcd_l,lcm_l /= gcd_l,temp_r_s1 /= gcd_r,lcm_r /= gcd_r;
	tree[l_son].data = {temp_l_s1 % Mode,lcm_l % Mode},tree[r_son].data = {temp_r_s1 % Mode,lcm_r % Mode};
	// 结果下传，一定要在过程中进行取模，血的教训
	dfs(l_son),dfs(r_son);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++)
		tree[i]._size = 1,f[i] = i;
	for(int i = n + 1; i <= 3 * n; i++) f[i] = i;
    // 因为要新建节点，数量为 n - 1 个，这里为了防止越界开了三倍，实际上不用
	ll len = n; // 记录新建节点编号
	for(int i = 1; i < n; i++)
	{
		ll p,q;
		cin >> p >> q;
		js x,y;
		ll tot = tree[f[find(p)]]._size + tree[f[find(q)]]._size;
		x.s1 = tree[f[find(p)]]._size,x.s2 = tot;
		y.s1 = tree[f[find(q)]]._size,y.s2 = tot;
		ll gcd_x = __gcd(x.s1,x.s2),gcd_y = __gcd(y.s1,y.s2);
		x.s1 /= gcd_x,x.s2 /= gcd_x,y.s1 /= gcd_y,y.s2 /= gcd_y;
		tree[f[find(p)]].data.s1 = x.s1,tree[f[find(p)]].data.s2 = x.s2;
		tree[f[find(q)]].data.s1 = y.s1,tree[f[find(q)]].data.s2 = y.s2;
		// 计算概率，并赋值
		len++;
		tree[len].l = f[find(p)],tree[len].r = f[find(q)],tree[len]._size = tot;
		f[find(p)] = len,f[find(q)] = len;
		// 新建节点，并查集合并
	}
	dfs(tree[len].l),dfs(tree[len].r);
	// 深搜下传结果
	for(int i = 1; i <= n; i++)
	{
			ll x,y,a,b;
			a = tree[i].data.s2,b = Mode;
			ex_gcd(a,b,x,y);// 扩欧求逆
			// 本题因为模数为 998244353 所以还可以用费马小定理来求逆元
			x = ((x % Mode) + Mode) % Mode; // x 有可能为负数，所以先加再取模
			cout << ((tree[i].data.s1 * x % Mode) + Mode) % Mode << " ";
	}
	return 0;
}
```


---

