# Variable Damage

## 题目描述

Monocarp is gathering an army to fight a dragon in a videogame.

The army consists of two parts: the heroes and the defensive artifacts. Each hero has one parameter — his health. Each defensive artifact also has one parameter — its durability.

Before the battle begins, Monocarp distributes artifacts to the heroes so that each hero receives at most one artifact.

The battle consists of rounds that proceed as follows:

- first, the dragon deals damage equal to $ \frac{1}{a + b} $ (a real number without rounding) to each hero, where $ a $ is the number of heroes alive and $ b $ is the number of active artifacts;
- after that, all heroes with health $ 0 $ or less die;
- finally, some artifacts are deactivated. An artifact with durability $ x $ is deactivated when one of the following occurs: the hero holding the artifact either dies or receives $ x $ total damage (from the start of the battle). If an artifact is not held by any hero, it is inactive from the beginning of the battle.

The battle ends when there are no heroes left alive.

Initially, the army is empty. There are $ q $ queries: add a hero with health $ x $ or an artifact with durability $ y $ to the army. After each query, determine the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 说明/提示

Let's consider the first example.

- An artifact with durability $ 5 $ is added. Since there are no heroes yet, the battle ends immediately.
- A hero with health $ 4 $ is added. Monocarp can give him an artifact with durability $ 5 $ . First, there are rounds in which the hero takes $ \frac{1}{1 + 1} = \frac{1}{2} $ damage. After $ 8 $ such rounds, a total of $ 4 $ damage will have been dealt, and the hero will die, while the artifact will deactivate. There are no more heroes alive, so the battle ends after $ 8 $ rounds.
- A hero with health $ 10 $ is added. Now let the artifact with durability $ 5 $ be with this hero. Then, in the first $ 12 $ rounds, the heroes will take $ 12 \cdot \frac{1}{2 + 1} = 4 $ damage, and the first hero will die. The second hero has $ 6 $ health left, and the artifact has $ 1 $ durability. Now the damage is $ \frac{1}{2} $ , so after another $ 2 $ rounds, the artifact will deactivate. The second hero has $ 5 $ health left. After another $ 5 $ rounds, the second hero will die. Therefore, the answer is $ 12 + 2 + 5 = 19 $ .

## 样例 #1

### 输入

```
3
2 5
1 4
1 10```

### 输出

```
0
8
19```

## 样例 #2

### 输入

```
10
1 9
1 6
2 4
1 8
1 3
2 10
1 3
1 6
1 10
2 6```

### 输出

```
9
15
19
27
30
39
42
48
59
65```

# 题解

## 作者：xiezheyuan (赞：1)

## 简要题意

有一个游戏，这个游戏中有若干个英雄和若干个道具，每个英雄存在生命值，每一个道具存在耐久度，每个英雄最多持有一件道具。

游戏开始时，你需要给每一个英雄分配一个道具（可能存在英雄没有道具或道具没有英雄），然后销毁未被分配的道具。

接下来有若干轮，每轮令每个英雄的生命值和每个道具的耐久度减去 $(a+b)^{-1}$，其中 $a$ 表示存活的英雄数量，$b$ 表示存在的道具数量，当英雄生命值小于等于 $0$ 时即死亡，当道具耐久度小于等于 $0$ 时，或持有它的英雄死亡时即销毁。当没有英雄存活时，游戏结束。你需要最大化游戏的轮数。

初始时，没有英雄和道具，有 $n$ 次操作，每次操作可以增加一个指定生命值的英雄，或增加一个指定耐久度的道具，然后你需要输出若此时进行一次游戏，游戏的轮数最大值。

$1\leq n\leq 3\times 10^5$。

## 思路

为什么我觉得这道题不套路？是我见的套路太少了吗？

### Part 1

先不考虑道具和动态插入，考虑下面这个问题：给定 $n$ 个英雄的生命值 $a_1,\cdots,a_n$，输出游戏轮数。直接考虑每个英雄受到的伤害比较复杂，不妨将所有英雄看成一个整体，那么相当于每轮对这个整体造成 $1$ 点伤害，故总游戏轮数就是 $\sum a_i$。

然后我们加入道具，不过假设道具已经配好对了，具体来说第 $i$ 个道具分配给第 $i$ 个英雄，耐久度为 $b_i$。那么道具其实可以看成 $\min(a_i,b_i)$ 生命值的英雄，转换成了前面的问题。

所以现在的问题是需要将 $a,b$ 排序，使得 $\sum \min(a_i,b_i)$ 最大。可以证明，只需要让 $a,b$ 均降序排序即可，为了使本部分内容流畅，我将证明放在了文末。

### Part 2

不过 $\sum\min(a_i,b_i))$ 这个形式似乎很难动态维护。这里我们需要另外一个 trick，将英雄和道具合并到一起，全部降序排序，然后对于一个道具，如果前面存在英雄没有匹配，那么需要匹配前面的一个英雄，贡献是自己的耐久度；对于一个英雄，如果前面存在道具没有匹配，那么需要匹配前面的一个道具，贡献为自己的生命值。

这个形式似乎有一点前途，不妨将“存在英雄没有匹配”改为“前面的英雄数量多于道具的数量”，不难证明这是等价的。

于是我们不妨改为维护每一个位置前（可以包括自己或者不包括自己，这是实现的细节）的英雄数量与道具数量之差，则英雄若产生贡献需要 $<0$（如果在前面你选择的是包括自己，那么应该是 $\leq 0$），道具则需要 $>0$（同理）。

将所有询问离线后对每一个数值离散化（出现多次的数，分配不同的编号），这样就变成了后缀加上或减去 $1$，查询全局 $>0$ 或 $<0$ 的元素的权值之和。

分块，有一个简单的 $O(n\sqrt{n\log n})$ 的做法，无法通过本题。

### Part 3

我们的 $\log$ 来自于查询时整块的二分查找（修改时散块重构时排序的 $\log$ 很容易用归并技巧来消去），如果我们可以直接开桶记录每个数的在序列中出现的位置的权值和，就可以去掉这个 $\log$ 了，由于每次只是 $\pm1$，所以可以用桶，不过这样就需要 $O(n\sqrt{n})$ 的空间。

这时观察我们分块的修改操作的特殊性质，每个后缀只会修改一次，故每个块的值域其实最多为 $[T+1,T+\sqrt{n}]$，只需要在散块重构时将 $T$ 设定为块中最小值减 $1$，就可以让值域变为 $[1,\sqrt{n}]$，这样只需要 $O(n)$ 的空间了。

时间复杂度 $O(n\sqrt{n})$ 空间复杂度 $O(n)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
using namespace std;

using i64 = long long;
const int N = 3e5 + 5, SQRTN = 555;
int m;

struct option{
    int op, v, id, pos;
} a[N];

struct blocking{
    int bl[N], br[N], bel[N], blk;
    int a[N], tag[N], val[N];
    i64 sumt[SQRTN][SQRTN];

    void init(){
        blk = sqrt(m);
        for(int i=1;i<=m/blk;i++) bl[i] = (i - 1) * blk + 1, br[i] = i * blk;
        br[m / blk] = m;
        for(int i=1;i<=m/blk;i++){
            for(int j=bl[i];j<=br[i];j++) bel[j] = i;
        }
    }

    void maintain(int k){
        int tmp = (*min_element(a + bl[k], a + br[k] + 1)) - 1;
        tag[k] += tmp;
        for(int i=1;i<=br[k]-bl[k]+1;i++)  sumt[k][i] = 0;
        for(int i=bl[k];i<=br[k];i++) sumt[k][a[i] -= tmp] += val[i];
        for(int i=1;i<=br[k]-bl[k]+1;i++) sumt[k][i] += sumt[k][i - 1];
    }

    void update(int p, int v){
        if(p > m) return;
        for(int i=p;i<=br[bel[p]];i++) a[i] += v;
        maintain(bel[p]);
        for(int i=bel[p]+1;i<=bel[m];i++) tag[i] += v;
    }

    i64 query(bool op){ // op = 0: < 0, op = 1: > 0
        i64 ans = 0;
        for(int i=1;i<=bel[m];i++){
            int bd = -tag[i] + (op ? 1 : -1);
            if(!op) ans += sumt[i][max(min(bd, br[i] - bl[i] + 1), 0)];
            else ans += sumt[i][br[i] - bl[i] + 1] - sumt[i][min(max(bd - 1, 0), br[i] - bl[i] + 1)];
        }
        return ans;
    }

    void add(int p, int v){ val[p] = v,  maintain(bel[p]); }
} heroes, artifacts;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> m;
    for(int i=1;i<=m;i++) cin >> a[i].op >> a[i].v, a[i].id = i;
    sort(a + 1, a + m + 1, [](auto x, auto y){ return x.v > y.v; });
    for(int i=1;i<=m;i++) a[i].pos = i;
    sort(a + 1, a + m + 1, [](auto x, auto y){ return x.id < y.id; });
    heroes.init(), artifacts.init(); i64 all = 0;
    for(int i=1;i<=m;i++){
        int op = a[i].op, v = a[i].v, pos = a[i].pos, tag = op == 1 ? 1 : -1;
        (op == 1 ? heroes : artifacts).add(pos, v);
        if(op == 1) all += v;
        heroes.update(pos + 1, tag), artifacts.update(pos + 1, tag);
        cout << heroes.query(0) + artifacts.query(1) + all << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

## 附：对于文中贪心的证明

> 所以现在的问题是需要将 $a,b$ 排序，使得 $\sum \min(a_i,b_i)$ 最大。

这个形式很像 exchange argument，所以可以考虑邻项交换模型，假如交换 $(i,j)$，若 $i$ 更优，则：

$$
\min(a_i,b_i)+\min(a_j,b_j)\geq \min(a_i,b_j)+\min(a_j,b_i)
$$

首先若 $a_i=a_j$ 或 $b_i=b_j$，则可以随意交换，故下面不考虑。

变形得：

$$
\min(a_i+a_j,b_i+b_j,a_i+b_j,a_j+b_i)\geq \min(a_i+a_j,b_i+b_j,a_i+b_i,a_j+b_j)
$$

由于 $\min$ 中四个和大小关系难以确定，而两边都有 $a_i+a_j,b_i+b_j$，为了保证恒成立，则有：

$$
\min(a_i+b_j,a_j+b_i)\geq \min(a_i+b_i,a_j+b_j)
$$

考虑在何时这个式子恒成立。我们下面证明，最小值不会同时为括号中的第一个值或第二个值。

不妨反证法，假如均取到第一个值（第二个值是类似的），则有 $a_i+b_j\leq a_j+b_i,a_i+b_i\leq a_j+b_j$，稍作变形得到 $a_i-a_j\leq b_i-b_j,a_i-a_j\leq b_j-b_i$，由于 $b_i\neq b_j$，故得证。

然后当 $a_i>a_j,b_i>b_j$，此时 $a_i+b_j>a_j+b_j$，$a_j+b_i<a_i+b_i$，讨论若左边最小值为 $a_i+b_j$，则不等式成立，若最小值为 $a_j+b_i$，又有 $a_j+b_i>a_j+b_j$，所以不等式恒定成立，故换成 $a_i>a_j,b_i>b_j$一定是不劣的，这就是正文中的贪心策略。

---

## 作者：ForgotMe (赞：1)

比较套路的题。

首先考虑对于固定的 $a$ 和 $b$ 该怎么做。注意到这个扣血机制非常的怪异，像是故意凑出来的一样。考虑对每一个时刻统计答案（称一个时刻为将所有英雄和装备都打掉一滴血）。
设 $f(x)$ 表示已经将所有英雄/装备都打掉 $x$ 滴血后，再打掉一滴血需要的次数。设第 $i$ 个英雄配的装备强度为 $b_i$（没装备视为 $0$），那么可以快速列出 $f(x)=\sum_{i=1}^n [x\ge a_i]+[x\ge \min(a_i,b_i)]$。
答案就是 $\sum_x f(x)=\sum_{i=1}^n a_i+\min(a_i,b_i)$。

于是问题转化为让装备和英雄配对，让上式的值最大。一个贪心策略是将 $a,b$ 都从大到小排序，然后挨着配对，实际上这确实是对的。证明可以使用 exchange argument，非常好证，留给读者。

考虑动态情况下怎么做，注意到这个不断的插入一个元素是很难处理的。于是可以想到用 $-1/1$ 的技巧去刻画这个匹配过程（先让 $a,b$ 的元素都互不相同，这可以通过离散化实现），具体来讲就是把英雄当成 $1$，让 $s_{a_i}$ 加上 $1$，武器当成 $-1$，让 $s_{b_i}$ 减去 $1$，那么一个血量为 $a_i$ 的英雄会造成贡献（即比与其匹配的武器的 $b$ 小）当且仅当 $\sum_{k=a_i}^{\infty} s_k\le 0$，同样的，一个强度为 $b_i$ 的装备会造成贡献当且仅当 $\sum_{k=b_i}^{\infty} s_k\ge 0$。

想到了这一步转化就很简单了，现在要去维护 $s$ 的后缀和数组 $f$，然后要查询 $f$ 上所有 $\le/ \ge 0$ 的位置对应的权值和，修改就是区间 $-/+ 1$。

使用分块就可以很轻松的做到上述两种操作，注意不需要使用 map 去存每个块对应 $f$ 值的数量，因为块内任意两个 $f$ 值的之差的绝对值小于等于块的长度 $B$，那么只需要随便选取该块的一个值作为标准值，用一个桶存 $f$ 值减去该标准值所对应的值的数量即可，这样子空间复杂度就是线性了。

时间复杂度 $\mathcal{O}(q\sqrt{q})$。

代码：https://www.luogu.com.cn/paste/b3yp7s7l

---

## 作者：Otomachi_Una_ (赞：0)

水题解/se

首先你发现，把一个盾的生命力定义为其防御值和持有者生命值的最小值，那么会进行的游戏轮数刚好是所有英雄的血量加上盾的生命力。

英雄的生命值容易提前预处理。然后显然的贪心是生命值大的英雄配备防御值大的盾。这里已经做到 $O(q^2)$ 了。

考虑加速这个过程。首先我们可以离散化，把英雄和盾从大到小排序放到一个序列上。然后相当于从后往前维护把前面未匹配的英雄或者盾匹配给当前扫描到的英雄或者盾的过程。

我们容易通过一个 $s$ 表示这个前缀的英雄减盾的个数，那么对每个 $i=1,2,\dots,n$ 如果第 $i$ 个英雄（或者盾）已经加入了队伍：

- 如果是英雄且 $s<0$ 那么，$ans\leftarrow ans+val_i$；
- 如果是盾且 $s>0$ 那么，$ans\leftarrow ans+val_i$。

这玩意不太好 polylog 做。考虑分块。对每个块维护一下当这个块前置的 $s=i$ 时，这个块能题供的贡献 $C_{b,i}$。

不难发现当 $i>|B|$ 时直接把 $i$ 调整至 $i=|B|$ 答案时相同的。所以说一个块只需要维护大小为 $2B$ 的信息。

考虑如何快速维护 $C$。当加入一个元素时，暴力查找这个块前面的英雄数减去盾牌数，暴力在 $C$ 上面改即可。对后面被这个元素影响的位置，只会对 $C$ 有恰好一个修改，在上面暴力改就行了。

然后查询也很简单，维护每个块的 $S$，查询一下这个块的答案即可。

时间复杂度：$O(q\sqrt q)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2025G)

**题目大意**

> 游戏里有 $n$ 个人，每个人可以携带一件装备，假设共有 $m$ 件装备，则每个人和装备每秒都会受到 $\dfrac 1{n+m}$ 的伤害。
>
> 每个人和装备都有血量，血量为 $0$ 时会消失，一个人消失的时候他的装备也会消失。
>
> $q$ 次操作，每次加入一个装备或人，动态维护游戏至多能进行多久。
>
> 数据范围：$q\le 3\times 10^5$。

**思路分析**

我们只要统计每个东西能承受多少伤害，一个血量为 $x$ 的人显然能受 $x$ 点伤害，而他的装备血量为 $y$，则能承受 $\min(x,y)$ 点伤害。

那么我们要求的就是最大匹配，先假设每个装备的贡献就是 $y$，然后要求有多少贡献实际达不到，相当于对于每个 $k$，如果设血量 $\ge k$ 的人数为 $a_k$，装备数为 $b_k$，那么要减去的贡献就是 $\sum \max(0,b_k-a_k)$。

因此我们就把这个问题转化为了数据结构问题：前缀加 $\pm 1$，查询全局正数和。

感觉上 $\mathrm{polylog}$ 做法是困难的，因此考虑分块，对于散块修改可以直接重构，整块时打标记。

查询的时候，设当前块标记为 $x$，我们要求的就是 $\sum\limits_{b_k-a_k\ge -x}b_k-a_k+x$，重构时对 $b_k-a_k$ 开桶，由于每次 $x$ 的变化只有 $\pm1$，因此动态维护后缀和是简单的。

时间复杂度 $\mathcal O(q\sqrt q)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5;
int n,m,a[MAXN],op[MAXN],st[MAXN],w[MAXN];
ll ans[MAXN],f[MAXN<<1],g[MAXN<<1];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>m;
	for(int i=1;i<=m;++i) cin>>op[i]>>a[i],st[++n]=a[i];
	sort(st+1,st+n+1),n=unique(st+1,st+n+1)-st-1;
	for(int i=1;i<=m;++i) a[i]=lower_bound(st+1,st+n+1,a[i])-st;
	for(int i=1;i<=m;++i) ans[i]=ans[i-1]+st[a[i]];
	for(int l=1,r,B=sqrt(n);l<=n;l=r+1) {
		r=min(n,l+B-1);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int j=l;j<=r;++j) {
			f[m-w[j]]+=st[j]-st[j-1];
			g[m-w[j]]+=1ll*(st[j]-st[j-1])*w[j];
		}
		ll cnt=f[m],sum=g[m];
		for(int i=1,tg=0;i<=m;++i) {
			int x=a[i],c=(op[i]==1?-1:1);
			if(x>=r) {
				if(c==1) ++tg,cnt+=f[m+tg],sum+=g[m+tg];
				else cnt-=f[m+tg],sum-=g[m+tg],--tg;
			} else if(x>=l) {
				cnt=0,sum=0;
				for(int j=l;j<=r;++j) f[m-w[j]]=g[m-w[j]]=0;
				for(int j=l;j<=r;++j) {
					w[j]+=tg+(j<=x?c:0);
					if(w[j]>=0) {
						cnt+=st[j]-st[j-1];
						sum+=1ll*(st[j]-st[j-1])*w[j];
					}
					f[m-w[j]]+=st[j]-st[j-1];
					g[m-w[j]]+=1ll*(st[j]-st[j-1])*w[j];
				}
				tg=0;
			}
			ans[i]-=sum+tg*cnt;
		}
	}
	for(int i=1;i<=m;++i) cout<<ans[i]<<"\n";
	return 0;
}
```

---

