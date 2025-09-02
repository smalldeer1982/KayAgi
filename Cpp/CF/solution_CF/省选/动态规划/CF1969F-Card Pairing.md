# Card Pairing

## 题目描述

有一副包含 $n$ 张牌的牌组，每张牌都是 $k$ 种类型中的一种。你会得到序列 $a_1,a_2,\dots,a_n$，从左到右表示牌组中牌的类型。$n$ 和 $k$ 都是偶数。

你用这些牌玩游戏。首先，你从牌组中抽取最上面的 $k$ 张牌。然后，游戏每回合都会遵循以下步骤：

- 首先，你从手上选择两张牌并将它们扔出。如果这两张卡的类型相同，你将获得一枚硬币；
- 如果牌组不是空的，就从中抽出两张最上面的牌；
- 如果你的手和牌组都是空的，游戏结束。否则，开始下一回合。

请计算你在游戏中可以赚取的最大硬币数量。

## 样例 #1

### 输入

```
4 2
1 2 1 2```

### 输出

```
0```

## 样例 #2

### 输入

```
8 2
2 1 2 2 1 2 1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
4 4
1 2 1 2```

### 输出

```
2```

## 样例 #4

### 输入

```
6 4
3 2 3 1 2 1```

### 输出

```
3```

## 样例 #5

### 输入

```
6 4
3 2 3 3 2 1```

### 输出

```
2```

## 样例 #6

### 输入

```
18 6
5 6 1 1 6 5 4 1 5 1 1 6 2 6 2 2 6 3```

### 输出

```
6```

## 样例 #7

### 输入

```
8 4
1 2 3 4 4 3 1 2```

### 输出

```
2```

## 样例 #8

### 输入

```
8 4
1 2 3 4 4 3 3 2```

### 输出

```
3```

# 题解

## 作者：EXODUS (赞：13)

# Part 1：前言

场上怎么不会，哈哈。

# Part 2：正文

题目中有一个特别的信息是，在桌子上空以前，你的手牌数始终为 $k$。这个信息的用处在于，如果你的手牌中不存在两张牌相同，则你的手牌一定为所有类型的牌各一张。我们称这样的局面为复杂局面。场上想到这个的时候我直接猜了结论，如果存在两张牌相同，则消除这两张牌一定不劣。

> 证明：下文我们将单次打出两张牌 $x$ 和 $y$ 记作 $(x,y)$。
>
> 假设在最优解的某一步中，我们现在手里有两张 $x$，但是我们打出了 $(y,z)$。不妨令 $x\neq z,y\neq z$。
>
> - $x=y$。我们令下一次打出 $x$ 的时候打出的是 $(x,w)$，则将 $(x,z),(x,w)$ 换成 $(x,x),(z,w)$ 一定不劣，且不影响其它位置的打出情况
> - $x\neq y$。同样的，记下两次打出 $x$ 的时候打出的是 $(x,w)$ 和 $(x,u)$。则将 $(y,z),(x,w),(x,u)$ 换成 $(x,x),(y,w),(z,u)$ 一定不劣。这里暗含条件 $w\neq x$，否则直接交换 $(x,w)$ 和 $(y,z)$ 的顺序即可。

综上，我们证明了这个结论。

先不考虑桌子上空了以后会怎么样。我们注意到所有的局面都能通过若干次这种消除转化成复杂局面。也就是说我们现在只需要对复杂局面进行决策。而我们每次选择不获得金币的时候一定是在复杂局面里，所以我们可以感知到原问题转为计算复杂局面的最小出现次数状物。而理论最多能获得的金币数是非常容易计算的，其等于 $\sum\limits_{i=0}^k \lfloor\dfrac{c_i}{2}\rfloor$。

场上我选择了直接贪心，也即选择能尽量延后复杂局面的牌对打出，然后 WA on 16，大家有兴趣可以给我叉一下。

复杂局面只有一种，这使得 dp 成为可能。令 $f(i)$ 表示摸到了位置 $i$ 以前的牌，当前是复杂局面，至少出现多少次复杂局面。但是这样实际上出现了一个问题，这个动态规划存在后效性，也即桌子上空了以后的过程我们无法考虑。这也是让我没继续想 dp 的一个原因。

请循其本。最小化复杂局面出现次数本质是最小化损失金币数。如果我们能够把费用提前计算，那么这个问题就解决了。重新观察上面理论最多金币数的贡献式，我们考虑在到达一个复杂局面的时候，计算其后缀所有牌的出现次数。我们设第 $i$ 类牌的出现次数的奇偶性是 $a_i$，则如果 $a_i=1$，当前取掉 $a_i$ 后，后面必定有一个 $a_i$ 要在将来的过程中被舍弃掉。其对损失金币的贡献数是 $1$。否则不会对损失金币产生贡献。

此时我们非常容易写出一个 dp 了。令 $f(i)$ 表示摸到了位置 $i$ 以前的牌，当前是复杂局面，至少损失多少金币。转移时枚举当前丢掉哪两张牌，记作 $(x,y)$，然后向后找到第一个位置 $j$ 使得遵循上述规则后摸到 $j$ 为复杂局面，转移为 $f(j)\leftarrow f(i)+C$。暴力计算 $a$ 数组，根据上面的分析 $C=[a_x=1]+[a_y=1]$。

这样复杂度是 $O(n^4)$ 的。我们考虑优化转移。注意到，如果我们向后枚举摸牌位置 $k$，则 $k$ 的改变至多使一对 $(x,y)$ 变成复杂局面，因此向后会产生复杂局面的只有 $O(n)$ 个，其余的将直接贡献到答案，且不同的贡献只有常数差别。因此我们在转移的时候，将每一种牌分为在后面出现奇数次和偶数次两类，如果在某次转移的时候，发现其一直到最后都不会导致复杂局面，我们直接停止转移，并将答案对 $f(i)+C$ 取最小值即可。

官解给出判断当前是否为复杂局面可以用随机映射后异或哈希。我认为这是一个比较优美的做法。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
    #define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
    #define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
    x=0;T flg=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

// mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 gen(0);
constexpr int N=1e3+7;
int n,k,cnt;
int card[N],f[N],buc[N];
ull key[N],premsk[N],invaildmsk;

bool memed=0;

//=========================================================================================================
// Code here.

void cmin(int& x,int y){x=min(x,y);}

int getnxt(int p,ull targetmsk){
    for(int i=p;i<=n;i+=2)
        if(premsk[i]==targetmsk)
            return i;
    return 0;
}

void solve(){
    read(n,k);
    for(int i=1;i<=n;i++)
        read(card[i]);
    for(int i=1;i<=k;i++)
        key[i]=gen(),invaildmsk^=key[i];
    for(int i=1;i<=n;i++)
        premsk[i]=premsk[i-1]^key[card[i]];
    for(int i=1;i<=n;i++)
        cnt+=buc[card[i]],buc[card[i]]^=1;
    int pos=getnxt(k,invaildmsk);
    int ans=0;
    if(!pos)
        ans=cnt;
    else{
        static constexpr int inf=0x3f3f3f3f;
        memset(f,0x3f,sizeof(f));
        int tot=inf;
        f[pos]=0;
        for(int i=k;i<=n;i+=2){
            if(f[i]==inf)continue;
            memset(buc,0,sizeof(buc));
            for(int j=i+1;j<=n;j++)
                buc[card[j]]^=1;
            vector<int>odd,even;
            for(int j=1;j<=k;j++)
                buc[j]?odd.eb(j):even.eb(j);
            for(int x=0;x<(int)even.size();x++)
                for(int y=0;y<x;y++){
                    int p=getnxt(i+2,premsk[i]^key[even[x]]^key[even[y]]);
                    if(!p){cmin(tot,f[i]);goto there;}
                    else cmin(f[p],f[i]);;
                }
            for(int x=0;x<(int)even.size();x++)
                for(int y=0;y<(int)odd.size();y++){
                    int p=getnxt(i+2,premsk[i]^key[even[x]]^key[odd[y]]);
                    if(!p){cmin(tot,f[i]+1);goto there;}
                    else cmin(f[p],f[i]+1);
                }
            for(int x=0;x<(int)odd.size();x++)
                for(int y=0;y<x;y++){
                    int p=getnxt(i+2,premsk[i]^key[odd[x]]^key[odd[y]]);
                    if(!p){cmin(tot,f[i]+2);goto there;}
                    else cmin(f[p],f[i]+2);
                }
            there:;
        }
        ans=cnt-tot;
    }
    printf("%d\n",ans);
    Debug("%d\n",ans);
    return;
}


//=========================================================================================================

int main(){
    Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
    int timbg=clock();
    int T=1;
    while(T--)solve();
    int timed=clock();
    Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
    fflush(stdout);
    return 0;
}

/*
g++ -O2 -std=c++14 -Wall -Wextra -Wshadow CF1969F.cpp -o CF1969F -DEXODUS -fsanitize=undefined,address
*/
```

---

## 作者：Nine_Suns (赞：7)

简单题。

首先有一个贪心，如果丢牌时手上有两张一样的牌一定丢，成为**好**的局面。由 $a_i\le k$ 可以知道没有两张一样的牌时当且仅当 $k$ 张牌恰好为 $1$ 到 $k$，称为**坏**局面。

坏局面的情况是单一的，考虑对坏局面计数。设 $f_i$ 表示在摸第 $i$ 张牌时是一个坏局面，出现的坏局面的最小次数，此时我们有所有类型的牌。不妨先不丢，继续往下摸牌，数量为偶数的牌实际上相当于没有，用异或的方式处理牌，当有 $2$ 张牌的数量为 $0$ 时，如果我们当时丢弃的是这两张牌（用 `set` 维护），则此时会出现一个新的坏局面，更新贡献 $f_j=\min\{f_j,f_i+1\}$，注意如果在这个局面之前丢这两张牌能出现坏局面，此时不能贡献。

接着考虑当前局面是最后一个坏局面，将其后的所有牌加入，最后所有牌都要丢，我们期望丢掉两张牌后数量为 $1$ 的牌越少越好（由于上面的限制，有些牌对不能丢，否则会出现新的坏局面），考虑算出丢掉两张牌后数量为 $1$ 的牌减少 $2$，不变，增加 $2$ 这三种情况，再将不能丢的牌数对的情况减去，枚举可能的情况即可。

复杂度 $O(n^2\log n)$。

[Code](https://codeforces.com/contest/1969/submission/266778934)

---

## 作者：YeahPotato (赞：6)

好题。考察了找阶段，和对 dp 原理的理解。

下文提及手牌，指的是打牌后、拿牌前的状态。

首先，原问题可以转化成：要求在某些 $a_i=a_j$ 之间连线（显然不会跨相同的数连），使得跨过每个 $a_{2t}$ 与 $a_{2t+1}$ 之间间隙的线的数量 $\le k-2$。这个转化是很直接的，因为连线左端的卡必须保留在手中。有可能产生疑问的一点是：如果一对 $a_{2t-1}$ 和 $a_{2t}$ 均为连线右端，那有一对卡就要顺延到后一轮才能打出，那就在待配对卡的基础上多了一对需要保留的牌啊？但由于这种情况跨 $a_{2t}$ 与 $a_{2t+1}$ 间隙的线的数量必然比跨 $a_{2t-1}$ 与 $a_{2t-1}$ 间隙的少 $2$，故这个间隙不必考虑。实际上就是能打出相同牌的轮，手牌数不变多。因此接下来认为如果拿到两张牌目前均可配对就一次性配掉，即手牌可以 $<k-2$。

处理转化后的问题。首先，如果没有 $\le k-2$ 的限制，就是从左往右扫，发现配对了就连线（下称“贪心”）。由于手牌数不可能为奇（后续不可能配对的牌也要保留在手里），故只有为 $k$ 时会不合法，这时直觉上来说要决策放弃两张牌。但是光这么考虑，总感觉不完备，凭什么只用这种决策方式就一定能覆盖最优解？

从另一个角度看，解的结构可以表述为：强制禁止某几对相同的数连线，然后剩余的贪心，要求最终合法。那么，如果某条线连了不会导致不合法，那禁掉它一定不优（如果不禁导致后面贪心得到的连线改变而不合法，可以在后面禁），因此可以在第一次发现不合法时禁。于是，上文 dp 的过程，就可以理解为决策禁哪些，然后分段贪心。

令 $f_i$ 表示 $a_{2i}$ 与 $a_{2i+1}$ 处出现了不合法，前面的最优答案。没法直接枚举放弃的两张牌，先考虑直接往后贪心。注意到如果后面某一时刻手牌数为 $k-2$，那么如果放弃的是缺的两张牌，那么这个时刻就会不合法。如果这两张牌的组合在之前没出现过，则要转移。直接转移到末尾的情况需要讨论一下。

一个实现问题是，如何快速求出缺的两张牌。可以记录缺的牌的和与平方和，也可以惰性删除，将所有新扫到的牌放在一个栈里，求时全拿出来判断。

时间复杂度 $\mathrm{O}(n^2)$，[代码](https://codeforces.com/contest/1969/submission/261329499)。

---

## 作者：zzzYheng (赞：5)

容易发现如果当前手中存在两张相同的牌，那么当前将它们消去一定不劣。证明可以分情况讨论然后归纳。

那么，我们只需要决策手中 $k$ 张牌颜色互不相同的情况。此时手中一定是每种颜色的牌各一张。那么不同情况有后效性的信息就只有当前牌堆的大小，只有 $n$ 种，所以可以考虑 $\text{dp}$。

令 $f_{i}$ 表示当前手中 $k$ 张牌颜色互不相同，牌堆中剩余 $a_{i\sim n}$，最多能获得多少硬币。

转移可以考虑枚举当前步扔了哪两张，然后不断取牌丢相同牌，直到手中的牌互不相同，就完成了转移。

注意直到将牌堆抽空手中的牌也从未互不相同也是一种转移。

模拟一下抽牌丢相同牌的过程就可以得到在哪里第一次手中的牌互不相同。这样时间复杂度是 $\Theta(n^4)$ 的。

发现每次转移都枚举丢了哪两张牌看起来是没有优化前途的，我们需要避免这个枚举过程。

仔细观察取牌丢相同牌的过程，发现如果手中存在相同牌，那么它们一定会在之后某一步中被丢掉。因为我们只研究何时手中会有 $k$ 个互不相同的牌，所以就可以直接在当前将这对相同牌删去。

所以这个过程可以看作：当前有一个 $01$ 序列 $p$ 表示每种牌手中是否有，每次从牌堆中取出两张牌 $x$ 和 $y$，就将 $p_x$ 和 $p_y$ 都异或上 $1$，直到 $p$ 序列变为全 $1$，或将牌堆抽空。

假设我们最初丢掉的两张牌是 $x,y$。此时求何时 $p$ 再一次全 $1$ 就等价于 $p$ 初始全 $0$，问何时 $p$ 恰好只在 $p_x$ 和 $p_y$ 处为 $1$。

那么我们直接将 $p$ 设为全 $0$，重复取牌的过程，期间如果 $p$ 恰好只在两个位置为 $1$，那么这两个位置就是可能的初始丢掉的 $x$ 和 $y$。

因此只有 $\Theta(n)$ 对 $x,y$ 丢掉后会使得之后再一次进入手中 $k$ 张牌互不相同的局面，并且进入这个局面的时刻就是上过程中 $x,y$ 对第一次出现的时刻。因此这个部分转移可以优化到 $\Theta(n^3)$。

而对于其他的 $x,y$ 对，我们丢掉它们后会一直抽牌丢相同牌直到将牌堆抽空，然后继续将手中相同牌全部丢去。容易发现最终丢去时没有获得硬币的卡牌就恰好是：将 $p_x,p_y$ 设为 $0$，其他位置设为 $1$，执行上述过程，最终在 $p$ 中为 $1$ 的那些卡牌。而这时 $p$ 的最终状态可以直接将 $p$ 初始全 $0$ 的执行该过程得到的最终 $p$ 在除 $p_x$ 和 $p_y$ 处异或 $1$ 得到。所以这部分也可以优化到 $\Theta(n^3)$。

但是由于常数原因过不去，怎么办？发现整个过程中我们一直在操纵 $01$ 序列，那么一个经典的优化就是使用 $\text{bitset}$，可以将复杂度优化到 $\Theta(\dfrac{n^3}{\omega})$，可以轻松通过。

一些细节可以参考代码实现：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int kMaxN = 1005;
 
int n, K;
 
int a[kMaxN];
 
int f[kMaxN];
 
bitset<kMaxN> bs;
int cnt;
 
void upd(int x) {
   if (bs[x]) {
      --cnt;
   }
   else {
      ++cnt;
   }
   bs[x] = bs[x] ^ 1;
}
 
pair<int, int> getPos() {
   pair<int, int> res;
   res.first = bs._Find_first();
   res.second = bs._Find_next(res.first);
   return res;
}
 
bitset<kMaxN> vis[kMaxN];
 
int main() {
   ios::sync_with_stdio(false);
   cin.tie(0), cout.tie(0);
 
   cin >> n >> K;
   for (int i = 1; i <= n; ++i) {
      cin >> a[i];
   }
   f[n + 1] = 0;
   for (int i = n - 1; i >= 1; i -= 2) {
      for (int j = 1; j <= n; ++j) vis[j].reset();
      bs.reset(), cnt = 0;
      for (int j = i + 2; j <= n + 1; j += 2) {
         upd(a[j - 1]), upd(a[j - 2]);
         if (cnt == 2) {
            pair<int, int> pos = getPos();
            if (vis[pos.first][pos.second]) continue;
            vis[pos.first][pos.second] = 1;
            f[i] = max(f[i], f[j] + (j - i) / 2 - 1);
         }
      }
      for (int j = 1; j <= K; ++j) {
         vis[j].flip();
         vis[j] >>= j + 1, vis[j] <<= j + 1;
         bitset<kMaxN> tmp = bs;
         int val = (bs[j]) ? -1 : 1;
         if ((vis[j] & tmp)._Find_first() <= K) {
            f[i] = max(f[i], ((n - i + 1) + cnt + val - 1) / 2 - 1);
         }
         tmp.flip();
         if ((vis[j] & tmp)._Find_first() <= K) {
            f[i] = max(f[i], ((n - i + 1) + cnt + val + 1) / 2 - 1);
         }
      }
   }
   bs.reset(), cnt = 0;
   for (int i = 1; i <= K; ++i) upd(a[i]);
   for (int i = K + 1; i <= n + 1; i += 2) {
      if (cnt == K) {
         cout << (i - 1 - K) / 2 + f[i] << '\n';
         return 0;
      }
      upd(a[i]), upd(a[i + 1]);
   }
   cout << (n - cnt) / 2 << '\n';
   return 0;
}
```

---

## 作者：Nelofus (赞：2)

其他题解实在是看不懂。看代码看半天看懂了（

首先是手牌里面有相同的肯定会直接打出。那么非平凡的情况就只有手牌中每种颜色各出现一次。

不妨设 $f(i)$ 表示前 $i$ 张牌，现在是非平凡局面时，非平凡局面的最小出现次数。但问题是到底先丢哪两张牌？这东西会带来转移的后效性，丢掉 $c$ 可能会让未来凑牌的时候没有办法凑出一对 $c$。

想一想没办法凑出一对 $c$ 是什么情况，假设我们当前在位置 $i$，还没有开始摸牌，而且是非平凡局面，要丢的牌是一对 $(x,y)$ 对于某个 $j$，$[i,j]$ 中，$(x,y)$ 出现的次数都是奇数。那么这些牌本该和当前非平凡局面中的 $(x,y)$ 有两两配对，但是现在丢掉 $(x,y)$ 之后，再到 $j$ 这个位置摸完牌就又是一个非平凡局面了。而这至少给我们带来了 $1$ 的代价。

考虑减少转移的次数，我们每次摸牌都是两张两张摸的，那么只有丢掉某对 $(c_j,c_{j+1})$ 的时候才可能造成影响，其他的情况一定都凑不出非平凡局面。那真正的转移就只有 $\mathcal O(n)$ 个了。每次转移的时候从 $j$ 从 $i$ 开始扫过去，动态维护过程中出现次数为奇数的数的集合，大小为 $2$ 的时候恰能转移到 $j+2$，每次复杂度是 $\mathcal O(n\log n)$ 的。对于所有凑不出非平凡局面的对，考虑当前已经花了多少次，以及丢完一对牌之后最后会剩下哪些牌即可。

可能讲得比较抽象，可以看看~~照抄自 jiangly 的~~代码。

个人感觉最难的部分是想到怎么处理掉丢掉某一个 $c$ 可能会对未来造成的影响，不在 $j$ 处考虑其前面所有可能的局面 $i$ 产生的贡献，而是使用费用提前计算的方式，直接计算对未来的贡献。剩下的部分都比较自然。

```cpp
#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

template<typename Ta, typename Tb>
inline void chkmin(Ta &a, const Tb &b) {if (a > b)	a = b;}

std::random_device seed;
std::mt19937_64 rng(seed());
constexpr int N = 1010;
int n, k;
int c[N];
int f[N];

int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++)
		std::cin >> c[i];

	int ans = 0x3f3f3f3f;
	int stp = 0;

	// 出现次数为奇数的颜色集合
	std::set<int> s;
	auto push = [&](int x) -> void {
		if (s.count(x))
			s.erase(x);
		else
			s.insert(x);
	};

	// 找到第一个手牌全部异色的位置
	for (int i = 1; i <= n; i++) {
		push(c[i]);

		if (s.size() == k) {
			stp = i + 1;
			break;
		}
	}

	memset(f, 0x3f, sizeof(f));
	if (!stp)
		ans = s.size();
	else
		f[stp] = 0;

	// 记录转移位置
	std::vector<std::vector<int>> vis(k + 1, std::vector(k + 1, -1));

	// stp = n + 1 是可能的
	for (int i = 1; i <= n + 1; i += 2) {
		s.clear();
		std::vector<std::pair<int, int>> trans;

		for (int j = i; j <= n; j += 2) {
			push(c[j]), push(c[j + 1]);

			// 恰好有两张出现是奇数次
			if (s.size() == 2) {
				int x = *s.begin();
				int y = *s.rbegin();
				if (vis[x][y] != i) {
					// 在 j 之后
					// 因为丢牌是两张两张的, 所以将贡献全部乘 2，最后除 2 即可
					chkmin(f[j + 2], f[i] + 2);
					vis[x][y] = i;
					trans.emplace_back(x, y);
				}
			}
		}
		int siz = s.size();
		// cnt[p] : 有多少个对 (x, y) 有 p 个端点在 [i, n] 中出现次数为偶数
		std::array<int, 3> cnt;
		
		// 不能包含自己
		cnt[2] = (k - siz) * (k - siz - 1) / 2;
		cnt[0] = siz * (siz - 1) / 2;
		cnt[1] = siz * (k - siz);
		
		// 去掉所有转移对
		for (const auto &[x, y] : trans) {
			int v = !s.count(x) + !s.count(y);
			cnt[v]--;
		}

		// 考虑所有丢弃之后能直接到序列末尾的牌对
		for (int p = 0; p <= 2; p++) {
			if (cnt[p]) {
				// f[i] + 1: 这次丢牌之后要增加 1 的代价
				// 后一部分是考虑最后会剩下哪些牌
				// 如果丢的两张在剩余过程中出现次数都是奇数，那么剩余过程中的牌肯定没法两两配对，都会剩下一张，那么这两张牌都会出现在最后剩下的牌里。
				// 两张都是偶数，那么剩下过程中肯定都能两两配对，这两张牌不会出现在最后剩下的牌里。
				// 一奇一偶的情况类似
				chkmin(ans, f[i] + 2 + k - (siz + 2 * p - 2));
			}
		}
	}

	ans = (n - ans) / 2;
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：lalaouye (赞：1)

少有的独自做出来的 *3000，还是很有成就感的！

集中注意力读题，首先注意到每一时刻牌数为 $k$，而牌的种类也为 $k$，如果实际牌的种类数小于 $k$，那么是很简单的情况，现在考虑实际牌的种类数等于 $k$ 的情况。

观察过程，首先发现如果有相同的牌直接丢就行，过程中还会出现没有牌相同的情况，显然这种情况每个牌的数量为 $1$，启发我们使用 dp，设 $f_i$ 表示已经考虑完 $i$ 张牌且当前没有相同牌，能获得的最多硬币数。

首先呼之欲出的是 $\mathcal{O}(n^2k^2)$ 的愚蠢做法。就是枚举我们删哪两张牌，再模拟出后面第一次出现没有相同牌状态的位置，并完成转移。

这样做是低效的。我们发现我们可以直接转移，在转移中变成判定问题，$f_j$ 能转移到 $f_i$，当且仅当区间 $[i+1,j]$ 从当前状态继续操作完成后出现无相同牌状态，且中途一直有相同牌。注意到删相同牌不会改变奇偶性，而加入会，我们发现这个判定过程实际上是一个异或加入牌的过程，而一个区间能满足条件当且仅当存在两种牌出现个数为奇数，直接异或哈希即可。

还有一种很烦人的情况，就是永远都不会出现无相同牌的状态了，这时的答案与实际牌的种类数小于 $k$ 的类似，他的答案就是 $\sum_{i=1}^k \lfloor \frac{s_i}{2}\rfloor$。$s_i$ 表示第 $i$ 种手牌的数量。然而，对于当前 $f_i$ 的答案来说，$s_i$ 是对于 $[i,n]$ 这个后缀算出来的，并且每个都会加一，因为当前每种牌各有一张。而这时我们要删除两张牌，显然我们因尽可能删除 $s_i$ 为奇数的牌，因为这样不会减少答案。枚举牌对显然不优，但我们可以将判断转为简单计数。

然后还有个细节就是起点问题，直接模拟找起点就行了。

总时间复杂度 $\mathcal{O}(n^2)$。

代码：

````
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define id(x, y) m * ((x) - 1) + (y)
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 1e3 + 5, P = 1e9;
constexpr double PI = acos (-1.0);
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int n, k;
int a[N], b[N], f[N];
bitset <N> bit;
ull w[N];
unordered_map <ull, pii> mp;
unordered_map <ull, bool> mmp;
int s1[N][N], s[N];
int main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd (), k = rd ();
  rep (i, 1, n) a[i] = b[i] = rd ();
  sort (b + 1, b + n + 1);
  int kk = unique (b + 1, b + n + 1) - b - 1;
  if (kk < k) {
    rep (i, 1, n) ++ s[a[i]];
    int sum = 0;
    rep (i, 1, k) sum += s[i] / 2;
    cout << sum;
    return 0;
  }
  rep (i, 1, n) a[i] = lower_bound (b + 1, b + k + 1, a[i]) - b;
  mt19937_64 rnd (time (0));
  rep (i, 1, k) {
    w[i] = rnd ();
    rep (j, 1, i - 1) mp[w[i] ^ w[j]] = pii (i, j);
  }
  rrp (i, 1, n) {
    ull now = 0;
    rep (j, i, n) ++ s1[i][a[j]];
    int s2[3] = {0, 0, 0}, s3[2] = {0, 0}, sum = 0;
    rep (j, i, n) {
      now ^= w[a[j]];
      if (mp.find (now) != mp.end () && ! mmp[now]) {
        pii p = mp[now];
        mmp[now] = 1;
        f[i - 1] = max (f[i - 1], f[j] + (j - i + 1) / 2 - 1);
        int x = s1[i][p.first], y = s1[i][p.second];
        if ((x & 1) ^ (y & 1)) ++ s2[1];
        else if (x & 1) ++ s2[0]; else ++ s2[2];
      }
    }
    now = 0;
    rep (j, i, n) {
      now ^= w[a[j]];
      mmp[now] = 0;
    }
    rep (j, 1, k) sum += (s1[i][j] + 1) / 2, ++ s3[s1[i][j] & 1];
    if (s3[1] * (s3[1] - 1) / 2 > s2[0]) f[i - 1] = max (f[i - 1], sum - 2);
    if (s3[0] * s3[1] > s2[1]) f[i - 1] = max (f[i - 1], sum - 1);
    if (s3[0] * (s3[0] - 1) / 2 > s2[2]) f[i - 1] = max (f[i - 1], sum);
  }
  int ans = -1;
  rep (i, 1, n) {
    if (bit[a[i]] == 1) bit[a[i]] = 0;
    else bit[a[i]] = 1;
    if (bit.count () == k) {
      ans = max (ans, (i - k) / 2 + f[i]);
      break;
    }
  }
  if (ans == -1) {
    rep (i, 1, n) ++ s[a[i]];
    int sum = 0;
    rep (i, 1, k) sum += s[i] / 2;
    cout << sum; return 0;
  }
  cout << ans;
}
````

---

## 作者：happybob (赞：0)

好题难得。

题意：

给定一副有 $n$ 张牌的牌组和常数 $k$，每张牌有花色 $a_i$，其中满足 $1 \leq a_i \leq k$。我们认为牌堆的顺序从上到下就是 $a_1,a_2,\cdots,a_n$。

现在进行如下游戏：

1. 游戏开始前，你先摸 $k$ 张牌。
2. 每回合，如果手牌为空，则游戏结束。否则你必须弃置手牌中的两张牌，如果他们同花色，你回复一点体力。弃牌后，你模两张牌，然后继续下一个回合。

求出最大的你能恢复的体力数。

$2 \leq k \leq n \leq 1000$，$1 \leq a_i \leq k$。

解法：

首先要注意一些性质。

容易发现弃牌时，如果手里有同花色的牌，弃置他们肯定不劣，并且弃哪一花色没有影响。真正需要决策的回合只是那些手牌中目前所有花色牌恰好出现 $1$ 次。此时你要选择弃置某两张牌，我们称这样的回合为决策回合。

基于这个可以设计 DP。记 $f_i$ 表示现在已经将 $[1,i]$ 中所有牌摸完，目前手牌中每种花色都恰好出现一次，在后续的回合中能恢复的最大体力。转移枚举弃置的两张牌并模拟到下一个所有牌都出现一次的回合。复杂度 $O(n^4)$，无法通过。

但事实上，我们考虑弃置花色为 $x,y$ 的牌，要么之后永远都不会到达决策回合，要么到达某个决策回合，从那个回合转移。考虑到达的决策回合是什么。不妨考虑记 $p_1,p_2,\cdots,p_k$ 表示目前每种花色的牌是否在手牌中。初始有 $p_x=p_y=0$，$\forall 1\leq i \leq k \land i \neq x \land i \neq y, p_i = 1$。每次摸的两张牌 $a,b$，其实是将 $p_a$ 与 $p_b$ 取反。决策回合则是 $\forall 1 \leq i \leq k, p_i = 1$。事实上我们可以假设初始时 $p$ 全为空，某次抽牌后，如果仅有 $p_x=p_y=1$，则 $(x,y)$ 的对应决策回合就是这个回合。

那么不然发现之后到达的决策回合的本质不同 $(x,y)$ 个数是 $O(n)$ 量级的，直接模拟可计算这部分的答案。

对于那种永远不到决策回合的，相当于补图边权最值，直接暴力枚举就行。复杂度 $O(n^2 \log n)$ 或 $O(n^2)$，具体依赖于实现。

[Submission Link.](https://codeforces.com/problemset/submission/1969/289906359)

---

