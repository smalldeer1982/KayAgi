# Boring Card Game

## 题目描述

When they are bored, Federico and Giada often play the following card game with a deck containing $ 6n $ cards.

Each card contains one number between $ 1 $ and $ 6n $ and each number appears on exactly one card. Initially the deck is sorted, so the first card contains the number $ 1 $ , the second card contains the number $ 2 $ , $ \dots $ , and the last one contains the number $ 6n $ .

Federico and Giada take turns, alternating; Federico starts.

In his turn, the player takes $ 3 $ contiguous cards from the deck and puts them in his pocket. The order of the cards remaining in the deck is not changed. They play until the deck is empty (after exactly $ 2n $ turns). At the end of the game both Federico and Giada have $ 3n $ cards in their pockets.

You are given the cards in Federico's pocket at the end of the game. Describe a sequence of moves that produces that set of cards in Federico's pocket.

## 说明/提示

Explanation of the first testcase: Initially the deck has $ 12 = 2\cdot 6 $ sorted cards, so the deck is $ [1\ 2\ 3\ 4\ 5\ 6\ 7\ 8\ 9\ 10\ 11\ 12] $ .

- During turn $ 1 $ , Federico takes the three cards $ [9\ 10\ 11] $ . After his move, the deck is $ [1\ 2\ 3\ 4\ 5\ 6\ 7\ 8\ 12] $ .
- During turn $ 2 $ , Giada takes the three cards $ [6\ 7\ 8] $ . After her move, the deck is $ [1\ 2\ 3\ 4\ 5\ 12] $ .
- During turn $ 3 $ , Federico takes the three cards $ [2\ 3\ 4] $ . After his move, the deck is $ [1\ 5\ 12] $ .
- During turn $ 4 $ , Giada takes the three cards $ [1\ 5\ 12] $ . After her move, the deck is empty.

 At the end of the game, the cards in Federico's pocket are $ [2\ 3\ 4\ 9\ 10\ 11] $ and the cards in Giada's pocket are $ [1\ 5\ 6\ 7\ 8\ 12] $ .

## 样例 #1

### 输入

```
2
2 3 4 9 10 11```

### 输出

```
9 10 11
6 7 8
2 3 4
1 5 12```

## 样例 #2

### 输入

```
5
1 2 3 4 5 9 11 12 13 18 19 20 21 22 23```

### 输出

```
19 20 21
24 25 26
11 12 13
27 28 29
1 2 3
14 15 16
18 22 23
6 7 8
4 5 9
10 17 30```

# 题解

## 作者：Terminus_Est (赞：9)

### 【CF1427F】Boring Card Game 解题报告

#### 题意

$6n$ 张牌，**顺序排列**，两人轮流操作，每次操作可以选择**连续**的三张牌放入自己的口袋中，给出第一个人**最后**得到的牌，构造合法的**操作顺序**，使得第一个人最后得到的牌为输入给定的牌。保证有解。

#### Solution

首先我们考虑一种弱化版的问题，即不考虑两个人轮流操作，构造一种方案满足题目条件。

设被第一个人拿走的卡牌的颜色是 $1$，被第二个人拿走的卡牌的颜色是 $0$，不难想到一个贪心的做法：将未被匹配的卡牌放入栈中，如果栈顶出现三个连续的颜色相同的卡牌就弹出栈。按照出栈的逆序进行操作。这样就可以得到一个不考虑顺序的构造方案。因为原题必然有解，所以一定有这样一个方案。

我们再考虑把每组被拿走的卡牌的左端和右端的卡牌想象成左括号和右括号，这样我们的过程可以被看成一个括号匹配。我们像如下结构建树：

![](https://cdn.luogu.com.cn/upload/image_hosting/oifgwj8u.png)

这样，原先的卡牌们就变成了一个森林。

同时，我们给每个点赋一个颜色 $0$ 或 $1$ 代表它是先手取走的/后手取走的。不难发现，树上的父子之间颜色都是相反的。并且，我们发现，每个点代表的三张牌如果要被取走，当且仅当它的后代都被取走了。于是我们考虑构造一个操作序列使得满足先手、后手这样的序列，并证明这样的序列一定存在。

1、当先手取的时候，颜色 $0$ 和颜色 $1$ 的数量相同。假设当前没有颜色 $0$ 作为叶子，那么因为父子之间必然不同，所以我们考虑将每个颜色 $0$ 都和它的一个儿子匹配，这样显然没有颜色 $1$ 会作为任何一棵树的根。但是，因为原题有解，所以最后被取走的一定是颜色为 $1$ 的节点，也就是一定有颜色为 $1$ 的节点作为根，矛盾。所以这一步我们任意找一个颜色 $0$ 的叶子节点就可以了。

2、当后手取的时候，颜色 $1$ 的数量比颜色 $0$ 的数量多 1 。分两种情况考虑：颜色为 $1$ 的根只有 1 个/多个。

有多个根：假设没有颜色为 $1$ 的叶子，那么每个 $1$ 和 $0$ 进行匹配，因为 $0$ 少一个，不够玩，矛盾，所以必有一个颜色为 $1$ 的叶子。而且，取走当前叶子并不影响最后至少有一个 $1$ 根的性质，所以随便取即可。

只有一个根：如果这个根有儿子，那么这个根是取不走的，于是同上一种情况取即可；如果没有儿子而且只剩它本身，那么就取它就好了；否则必然有别的根为 $0$ 的树，这个时候的情况和先手取的情况类似。我们这个时候只要取非根的 $1$ 即可。

至此，全部构造完成。

---

## 作者：kiritokazuto (赞：6)

# Boring Card Game

> ~~我愿意称之为最水的黑题。~~

- 一看题目，唉，这不大模拟嘛？然后无脑敲了 200 行左右，维护了五个链表，拿了 10 分？？？

- ~~好了，不是大模拟，那我们就可以好好思考这道题了~~。
- 首先我们可以很明显的发现，每一张牌应该由谁取是已经确定了的，所以我们可以先标记出哪张牌属于谁，然后考虑如何进行处理，让牌能被拿出来。
- 我们记 $1$ 为先手 $0$ 为后手。
- 对于一种情况，例如 $1$ $1$ $0$ $0$ $0$ $1$ 显然我们应该先取完中间的三个零再取这些一，因为这样他们才可以连起来，我们称这样的点具有依赖关系，当然，因为每个人都一次取三个，所以我以三个为一块，那么对于这种依赖关系，我们就将他们所属的块连边，然后跑拓扑，就可以很好地去解决这个问题了。
- 不过我在这里写了一个魔改的拓扑，我是用出度为零跑的，所以我在连边的时候父子关系是相反的，有点别扭，大家可以看代码理解。
- 所以如果这样建图的话，显然我们只有在处理叶子之后才能处理根，也就是一个反着来的拓扑，不过其实本质一样。
- 那么我们可以发现，因为数据保证有解，总数也是一个确定的偶数，那么最后一次一定是后手拿牌，所以如果我们不是最后一次拿牌的话，应时刻保留一个后手作为根的节点(作为根是因为它最后拿，那么应该处理完所有的依赖关系)。
![image](https://cdn.luogu.com.cn/upload/image_hosting/ds9xpouw.png)
  - 例如，我们如果不保留 $4$ 节点这个零，那么显然之后我们会陷入让先手最后取的困境，就无解了，所以我们应该先取完 $3$ 和 $2$ 这两个零节点，最后再取 $4$ 才是有解的。
- 下边我们考虑如何建出这个森林(不一定是一整颗树)。
  - 我们可以维护一个栈，如果这个栈顶元素和我不同，我们就新加入一个块(可以放三个节点那种)，否则，我就放在栈顶元素所在块里，当然，如果栈顶元素所在块够了三个节点，我们可以将这个块弹出，并将它的依赖关系维护一下。
- 我们可以模拟一下这个过程。
  - 例如 $0$ $0$ $1$ $1$ $0$ $1$ $1$ $1$ $0$ $0$ $1$ $0$。从左到右依次编号为 $1 \sim 12$。

  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/izmx00f7.png)
  - 首先我们建了一个新块，放入了 $1$ 和 $2$ 两个点，并且我们记录块 $1$ 是属于 $0$ 的后手。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/mnibf2hk.png)
  - 之后我们又建了一个新块，放入了 $3$ 和 $4$ 两个点，并且我们记录块 $2$ 是属于 $1$ 的先手。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/u5kgjgzo.png)
  - 之后我们又又又建了一个新块，放入了 $5$ 一个点，并且我们记录块 $3$ 是属于 $0$ 的后手。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/vcfpa20l.png)
  - 之后我们又双叒叕建了一个新块，放入了 $6$ $7$ $8$ 三个点，并且我们记录块 $4$ 是属于 $1$ 的先手。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/jzvdrf6o.png)
  - 终于遇到了够三个点的块，所以我们可以开始弹栈了，弹出并建边。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/xcfivadd.png)
  - 此时块 $3$ 也够了，继续弹。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/bklw50in.png)
  - 块 $2$ 够了， 弹。
  - ![image](https://cdn.luogu.com.cn/upload/image_hosting/idqxfdxv.png)
  - 最终块 $1$ 也够了，栈也空了。
- 最后就可以拓扑输出答案了。
- 对于如何进行拓扑，因为我是反着建图的，所以在这里我是跑的出度为零的点，然后把它父亲的度数删掉。
- 这里讲一下最下边那个输出的循环，最外层是现在处理了几个块了，实际上就是用来给我转换每一次需要的卡牌的类型的循环(转换 $now$)，里层的循环是用来找到现在可以输出的块，也就是没有被访问过，同时出度为零并且和我要的类型一样的节点。
- 这里还应该像上文说的一样，如果不是最后一轮(最后一轮就可以将它输出了)，我们应该时刻保证存在一个后手类型的根节点，以保证有解，所以我有一个 `continue` 。
- 剩下就没有了，这个黑题就被切掉了。

- 学校的 ``linux`` 没有画图，~~图全是用 ``wps`` 画的，呜呜呜~~。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define Re register int
#define LD double
#define mes(x, y) memset(x, y, sizeof(x))
#define cpt(x, y) memcpy(x, y, sizeof(x))
#define fuc(x, y) inline x y
#define fr(x, y, z)for(Re x = y; x <= z; x ++)
#define fp(x, y, z)for(Re x = y; x >= z; x --)
#define delfr(x, y, z)for(Re x = y; x < z; x ++)
#define delfp(x, y, z)for(Re x = y; x > z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define ki putchar('\n')
#define fk putchar(' ')
#define WMX aiaiaiai~~
#define pr(x, y) pair<x, y>
#define mk(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define re(x) return x
#define sec second
#define fst first


using namespace std;
namespace kiritokazuto{
    auto read = [](){
        LL x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())){ if (c == '-')f = -1; }
        do{ x = (x << 1) + (x << 3) + (c ^ 48); } while (isdigit(c = getchar()));
        return x * f;
    };
    template  <typename T> fuc(void, write)(T x){
        if (x < 0)putchar('-'), x = -x;
        if (x > 9)write(x / 10); putchar(x % 10 | '0');
    }
}

using namespace kiritokazuto;


const int maxn = 2000 + 5, maxm = 6e5+ 5, Mod = 993244853;
const LL Inf = 0x7fffffffffff;

int stk[maxn];
int bel[maxn];//块里点的类型
int top;
int n;
int deg[maxn];
int fa[maxn];
int rem[maxn][4];
int type[maxn];//1 先手 0 后手
int q[maxn], l, r;//topo
int tot[maxn];//一个块里有几个点
int num;//总共有多少块
int now = 1;//现在谁取
int vis[maxn];
signed main() {
	n = read();
	n *= 3;
	fr(i, 1, n) type[read()] = 1;
	n <<= 1;
	fr(i, 1, n) {
		if(!top || bel[stk[top]] != type[i]) {//没块或者与栈顶不同类，加新的
			bel[++num] = type[i];
			stk[++top] = num;
			rem[num][++tot[num]] = i;
		}else {
			rem[stk[top]][++tot[stk[top]]] = i;
			if(tot[stk[top]] == 3){
				fa[stk[top]] = stk[top - 1];
				top--;
			}
		}
	}
	int mach = 0;//以0为根的点有几个
	fr(i, 1, num) {
		if(!fa[i] && !bel[i])mach ++;
		deg[fa[i]]++;//出度
	}
	
	fr(i, 1, num){//我当前处理第几个节点
		fr(j, 1, num) {
			if(!deg[j] && bel[j] == now && !vis[j]) {
				if(i < num && (bel[j] == 0) && mach == 1 && !fa[j])continue;
				//不是最后一个的话我们不能将最后一个作为根的后手取走
				vis[j] = 1;
				deg[fa[j]]--;
				if(!bel[j] && !fa[j])mach--;
				printf("%d %d %d\n", rem[j][1], rem[j][2], rem[j][3]);
				break;
			}
		}
		now ^= 1;
	} 
	re(0);

}


```


---

## 作者：Locix_Elaina_Celome (赞：1)

# [CF1427F Boring Card Game](https://www.luogu.com.cn/problem/CF1427F) 题解

## 题意
> $6n(n\le 200)$ 张牌，先后手轮流操作，每次可以选择连续三个牌拿走。已知每张牌是谁拿走的，构造一个合法的操作方案。

## 题解

给每个地方定一个权值，如果是 1 的话表示勒个位置是第一个人拿，0 就是第二个人。

首先得有一个很撇的弄法，每回选最左边连续三个相同的位置拿起走。然后就发现很明显这样是不对头的，因为会造成没有保证两个人轮流选，比如 111000110001。但是楞个可定下来最后哪三个位置是一起拿的，然后可以表示为很多个三元组。同时发现可以维护出一些三元组之间选择的先后关系。

对于每个“三元组 $u$ 必须在 $v$ 后头选”的限制条件，转换为一条边 $(u,v)$。

然后问题斗变成了楞个个问题：有一个黑白交替分层染色的森林，每回选一个叶子扔起跑，要求交替扔黑白颜色。

先考虑现在要扔黑色点（先手）。因为题目保证了肯定有解，所以现在全局的黑白点数肯定是一样哩。仔细考虑一哈就发现这时候随便选一个黑色点都是合法的。

然后看后手。现在黑点应该比白点少一个。又因为最后一次操作是后手，所以说肯定有一个根是白色。我们只需要让这个根是最后选，然后乱选就可以了。

因为黑白点数差不多，所以这个森林不是很密，限制很松，找篇纸画两哈感觉这样问题不大。大概就是因为黑白点数量相同，所以要么是很长的链，要么很多点堆到起一堆然后有很多孤点随便选。

可以做线性，但是我比较懒所以写的个 $O(n^2)$ 的俎法。

## 代码
```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 100005
#define LL long long
#define LD long double
//#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int a[N];
int n;
int bl[N];
vector<int> sn[N];
int st[N],top;
int col[N];
int tot;
int t[N],las[N],fir[N],num=1;
struct st{int a,b,c;}s[N];
int fa[N];
int d[N];
void build(){
	for(int i=1;i<=(n*6);i++){
		if(top>=2&&a[st[top]]==a[st[top-1]]&&a[st[top]]==a[i]){
			bl[i]=bl[st[top]]=bl[st[top-1]]=++tot;
			s[tot]={st[top-1],st[top],i};
			col[tot]=a[i];
			top-=2;
			if(top)sn[st[top]].push_back(tot);
		}else st[++top]=i;
	}
	for(int u=1;u<=n*6;u++)
		for(int v:sn[u])
			fa[v]=bl[u],d[bl[u]]++;
}
void solve(){
	for(int i=1;i<=n*2;i++){
		if((i&1)){
			for(int j=1;j<=tot;j++){
				if(d[j]==0&&col[j]==1){//黑点随便选
					write(s[j].a),putchar(' '),write(s[j].b),putchar(' '),write(s[j].c),puts("");
					d[fa[j]]--;
					d[j]=INF;
					break;
				}
			}
		}
		else{
			int fl=0;
			for(int j=1;j<=tot;j++){
				if(d[j]==0&&col[j]==0&&fa[j]){//优先选择不为根的白点
					write(s[j].a),putchar(' '),write(s[j].b),putchar(' '),write(s[j].c),puts("");
					d[fa[j]]--;
					d[j]=INF;
					fl=1;
					break;
				}
			}
			if(fl)continue;
			for(int j=1;j<=tot;j++){
				if(d[j]==0&&col[j]==0&&!fa[j]){
					write(s[j].a),putchar(' '),write(s[j].b),putchar(' '),write(s[j].c),puts("");
					d[j]=INF;
					break;
				}
			}
		}
	}
}
#undef int
int main(){
//#define int LL
	read(n);
	for(int i=1,x;i<=n*3;i++)read(x),a[x]=1;
	build();
	solve();
	return 0;
#undef int
}
```

---

## 作者：elbissoPtImaerD (赞：0)

先不考虑先后手的限制，即先构造出 $\frac 2n$ 次连续取出三个。  
用一个栈可以简单维护。  
用调整法不难证明这种构造是不会影响后面加入限制的构造的。

再考虑加上先后手的限制。

发现操作之间有先后限制，我们可以将其抽象为一个图论型：

每次连续取出的三个的最左的看作一个左括号，中间看作空，最右看作右括号，按是先手拿还是后手拿对这组括号黑白染色。  

然后建出括号树森林，问题转化为每次能删一个叶子节点，黑白交替删。

显然黑白节点数相同，且没有一条边连接两个同色点。

所以每次优先取一个非根叶子即可。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1427/submission/246762311)

---

