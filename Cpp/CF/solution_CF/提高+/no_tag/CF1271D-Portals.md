# Portals

## 题目描述

You play a strategic video game (yeah, we ran out of good problem legends). In this game you control a large army, and your goal is to conquer $ n $ castles of your opponent.

Let's describe the game process in detail. Initially you control an army of $ k $ warriors. Your enemy controls $ n $ castles; to conquer the $ i $ -th castle, you need at least $ a_i $ warriors (you are so good at this game that you don't lose any warriors while taking over a castle, so your army stays the same after the fight). After you take control over a castle, you recruit new warriors into your army — formally, after you capture the $ i $ -th castle, $ b_i $ warriors join your army. Furthermore, after capturing a castle (or later) you can defend it: if you leave at least one warrior in a castle, this castle is considered defended. Each castle has an importance parameter $ c_i $ , and your total score is the sum of importance values over all defended castles. There are two ways to defend a castle:

- if you are currently in the castle $ i $ , you may leave one warrior to defend castle $ i $ ;
- there are $ m $ one-way portals connecting the castles. Each portal is characterised by two numbers of castles $ u $ and $ v $ (for each portal holds $ u > v $ ). A portal can be used as follows: if you are currently in the castle $ u $ , you may send one warrior to defend castle $ v $ .

Obviously, when you order your warrior to defend some castle, he leaves your army.

You capture the castles in fixed order: you have to capture the first one, then the second one, and so on. After you capture the castle $ i $ (but only before capturing castle $ i + 1 $ ) you may recruit new warriors from castle $ i $ , leave a warrior to defend castle $ i $ , and use any number of portals leading from castle $ i $ to other castles having smaller numbers. As soon as you capture the next castle, these actions for castle $ i $ won't be available to you.

If, during some moment in the game, you don't have enough warriors to capture the next castle, you lose. Your goal is to maximize the sum of importance values over all defended castles (note that you may hire new warriors in the last castle, defend it and use portals leading from it even after you capture it — your score will be calculated afterwards).

Can you determine an optimal strategy of capturing and defending the castles?

## 说明/提示

The best course of action in the first example is as follows:

1. capture the first castle;
2. hire warriors from the first castle, your army has $ 11 $ warriors now;
3. capture the second castle;
4. capture the third castle;
5. hire warriors from the third castle, your army has $ 13 $ warriors now;
6. capture the fourth castle;
7. leave one warrior to protect the fourth castle, your army has $ 12 $ warriors now.

This course of action (and several other ones) gives $ 5 $ as your total score.

The best course of action in the second example is as follows:

1. capture the first castle;
2. hire warriors from the first castle, your army has $ 11 $ warriors now;
3. capture the second castle;
4. capture the third castle;
5. hire warriors from the third castle, your army has $ 13 $ warriors now;
6. capture the fourth castle;
7. leave one warrior to protect the fourth castle, your army has $ 12 $ warriors now;
8. send one warrior to protect the first castle through the third portal, your army has $ 11 $ warriors now.

This course of action (and several other ones) gives $ 22 $ as your total score.

In the third example it's impossible to capture the last castle: you need $ 14 $ warriors to do so, but you can accumulate no more than $ 13 $ without capturing it.

## 样例 #1

### 输入

```
4 3 7
7 4 17
3 0 8
11 2 0
13 3 5
3 1
2 1
4 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4 3 7
7 4 17
3 0 8
11 2 0
13 3 5
3 1
2 1
4 1
```

### 输出

```
22
```

## 样例 #3

### 输入

```
4 3 7
7 4 17
3 0 8
11 2 0
14 3 5
3 1
2 1
4 3
```

### 输出

```
-1
```

# 题解

## 作者：Sweetlemon (赞：56)

### CF1271D Portals

这是一道有非常多做法的题目，值得一做。

#### 基础贪心思想

一个比较重要的贪心思想是，对于每一个城堡，我们都尽可能在最晚的时间控制，也就是早控制不如晚控制。这一点很容易理解，因为如果早控制，士兵到了城堡也是闲着，不如留在军队里凑数，到了时间再前往目标城堡。

因此，我们可以记录每一个城堡的最晚控制时间，在最晚控制时间才派出士兵控制。

#### 动态规划算法

看到这题的数据范围居然只有 $5000$，那就一定可以动态规划了。

设 $f[i][j]$ 表示攻下了前 $i$ 个城堡且手上还剩 $j$ 个士兵时，被控制的最大总价值。那么这个问题就类似一个背包，直接转移一下就可以得到答案了。只要注意边界——打第 $i$ 个城堡前手上必须有至少 $a[i]$ 个士兵。

时间复杂度 $O(n^2)$ 量级。

```cpp
#include <cstdio>
#include <cctype>
#include <vector>
#include <functional>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define LOWBIT(x) ((x)&(-(x)))
#define MAXN 5005
#define INF 19260817
using namespace std;

typedef long double ld;
typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void); //快读，实现略去
void ayano(io_t x,char spliter='\n'); //快写，实现略去

int n;
int a[MAXN],b[MAXN],c[MAXN];
int f[MAXN][MAXN];
int tcont[MAXN];  //每个城堡控制的最晚时间
pair<int,int> prs[MAXN]; //把可控制的城堡和它的价值放在 pair 中

int main(void){
    int m,k;
    n=seto(),m=seto(),k=seto();
    for (int i=1;i<=n;i++)
        a[i]=seto(),b[i]=seto(),c[i]=seto(),tcont[i]=i;
    while (m--){
        int u,v;
        u=seto(),v=seto();
        tcont[v]=max(tcont[v],u);
    }
    for (int i=1;i<=n;i++)
        prs[i]=make_pair(tcont[i],c[i]);
    sort(prs+1,prs+n+1);
    for (int t=0;t<=k;t++)
        f[0][t]=0;
    for (int t=k+1;t<=5000;t++)
        f[0][t]=-INF;
    int tpoint=1; //当前可控制的城堡指针
    for (int i=1;i<=n;i++){
        for (int t=0;t<=5000;t++)
            f[i][t]=-INF;
        for (int t=a[i];t<=5000;t++)
            f[i][t+b[i]]=max(f[i][t+b[i]],f[i-1][t]);
        while (tpoint<=n && prs[tpoint].first==i){
            for (int t=0;t<5000;t++)
                f[i][t]=max(f[i][t],f[i][t+1]+prs[tpoint].second);
            tpoint++;
        }
    }
    int ans=-1;
    for (int t=0;t<=5000;t++)
        ans=max(ans,f[n][t]);
    ayano(ans);
    return 0;
}
```

#### 数据结构优化贪心算法

我们可以想到一个这样的贪心：先不控制任何一个城堡，完成游戏后再按照价值从大到小的顺序尽可能地控制城堡。

这个贪心为什么是正确的呢？主要原因还是，控制任何一个城堡需要的士兵都是 $1$ 人。如果留着这个价值较大的城堡不控制，对后续的影响最多也就是“能多控制一个价值较小的城堡”，这一定是不划算的。

那么如何判断“能否控制这个城堡”呢？

考虑控制这个城堡对后续的影响——控制了这个城堡，今后攻打城堡时可用的士兵就会少一人。因此我们可以用一个数组记录“攻打这个城堡时，可用士兵比必需士兵（$a[i]$）多多少”。假设我们想要在 $t$ 时刻控制一个城堡，那么 $t$ 时刻以后的可用士兵就会少一人，我们就要检查，$t$ 时刻以后的“盈余士兵”是否都大于 $0$。如果确实大于 $0$，表示我们可以控制这个城堡，我们就需要更新“盈余士兵”——$t$ 时刻以后的盈余士兵都少一人。

区间减和区间最小值，可以方便地用线段树实现。

时间复杂度 $O(n\log n)$ 量级。

```cpp
#include <cstdio>
#include <cctype>
#include <vector>
#include <functional>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define LOWBIT(x) ((x)&(-(x)))
#define MAXN 5005
#define MAX4N 20005
#define INF 19260817
using namespace std;

typedef long double ld;
typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

struct Ene{
    int l,r,val,addv;
    #define L(x) ((stree[(x)]).l)
    #define R(x) ((stree[(x)]).r)
    #define X(x) ((stree[(x)]).val)
    #define ADD(x) ((stree[(x)]).addv)
    #define LC(x) (((x)<<1))
    #define RC(x) (((x)<<1)^1)
};

int n;
int a[MAXN],b[MAXN],c[MAXN];
int rst[MAXN];
int tcont[MAXN];
pair<int,int> prs[MAXN];
Ene stree[MAX4N];

void build_tree(int root,int l,int r);
void add(int root,int l,int r,int v);
int query(int root,int l,int r);
void pushdown(int root);

int main(void){
    int m,k;
    n=seto(),m=seto(),k=seto();
    for (int i=1;i<=n;i++)
        a[i]=seto(),b[i]=seto(),c[i]=seto(),tcont[i]=i;
    while (m--){
        int u,v;
        u=seto(),v=seto();
        tcont[v]=max(tcont[v],u);
    }
    for (int i=1;i<=n;i++)
        prs[i]=make_pair(c[i],tcont[i]);
    sort(prs+1,prs+n+1);
    for (int i=1;i<=n;i++){
        if (k<a[i]){
            ayano(-1);
            return 0;
        }
        rst[i-1]=k-a[i];
        k+=b[i];
    }
    rst[n]=k;
    int troot=1;
    build_tree(troot,1,n);
    ll ans=0;
    for (int i=n;i;i--){
        int ucont=prs[i].second;
        int tw=prs[i].first;
        if (query(troot,ucont,n)>0)
            add(troot,ucont,n,-1),ans+=tw;
    }
    ayano(ans);
    return 0;
}

void build_tree(int root,int l,int r){
    L(root)=l,R(root)=r,ADD(root)=0;
    if (l==r){
        X(root)=rst[l];
        return;
    }
    int mid=(L(root)+R(root))>>1;
    build_tree(LC(root),l,mid);
    build_tree(RC(root),mid+1,r);
    X(root)=min(X(LC(root)),X(RC(root)));
}

void add(int root,int l,int r,int v){
    if (l<=L(root) && r>=R(root)){
        X(root)+=v,ADD(root)+=v;
        return;
    }
    pushdown(root);
    int mid=(L(root)+R(root))>>1;
    (l<=mid)?(add(LC(root),l,r,v)):(void());
    (r> mid)?(add(RC(root),l,r,v)):(void());
    X(root)=min(X(LC(root)),X(RC(root)));
}

int query(int root,int l,int r){
    if (l<=L(root) && r>=R(root))
        return X(root);
    pushdown(root);
    int mid=(L(root)+R(root))>>1;
    int ans=INF;
    (l<=mid)?(ans=min(ans,query(LC(root),l,r))):(0);
    (r> mid)?(ans=min(ans,query(RC(root),l,r))):(0);
    return ans;
}

void pushdown(int root){
    int tadd=ADD(root);
    ADD(root)=0;
    if ((!tadd) || (L(root)==R(root)))
        return;
    ADD(LC(root))+=tadd,X(LC(root))+=tadd;
    ADD(RC(root))+=tadd,X(RC(root))+=tadd;
}
//略去读入输出优化的实现
```

#### 反悔型贪心

事实上，这题还有非常容易实现的反悔型贪心做法。

反悔型贪心同样基于“控制任何一个城堡需要的士兵都是 $1$ 人”的条件。它的思路是：在每个城堡的“最晚控制点”，先贪心地把城堡控制了。

这样就会存在问题：后面士兵可能就不够了，游戏失败了啊。那我们就会后悔，“要是那时没有控制某一个城堡就好了”；而程序可以实现“时光倒流”，把当时的操作反悔掉，也就是减少 $c[i]$ 个重要点数，增加一名士兵。贪心地想，因为每一个城堡都是贡献 $1$ 名士兵，所以我们肯定会选择反悔“最不重要”的、也就是 $c[i]$ 最小的城堡。

于是，我们只需要在控制城堡的时候，把城堡放进一个堆里，每次需要反悔时取堆中最不重要的城堡进行反悔即可；如果需要反悔时堆已经为空，就说明这个游戏不可能完成，输出 $-1$ 即可。

注意一个易错点：游戏结束时，如果士兵人数是负值，自然是不可行的。因此最后如果人数为负，则还要进行反悔。

时间复杂度 $O(n\log n)$ 量级。

这道题体现了反悔型贪心的基本思路（之一），非常适合作为反悔贪心的入门例题。

类似的反悔型贪心还有这道题：[SP348 EXPEDI - Expedition](https://www.luogu.com.cn/problem/SP348)，可以作为例题的配套练习。它们有一个共同特点，那就是都有一个维度是 $1$——每个城堡所需士兵都是 $1$ 人；每个加油站对答案的贡献都是 $1$——这也许是这类反悔型贪心成立的条件。

下面是本题代码。

奇怪的是，dp 的代码只用时 $109 \text{ms}$，线段树的代码用时 $156 \text{ms}$，堆的代码用时竟达到 $171 \text{ms}$！理论上快的代码实际上反而慢，确实有些奇怪。

```cpp
#include <cstdio>
#include <cctype>
#include <functional>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define LOWBIT(x) ((x)&(-(x)))
#define MAXN 5005
using namespace std;

typedef long double ld;
typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void);
void ayano(io_t x,char spliter='\n');

int n;
int a[MAXN],b[MAXN],c[MAXN];
int rst[MAXN];
int tcont[MAXN];
pair<int,int> prs[MAXN];
int que[MAXN];

int main(void){
    int m,k;
    n=seto(),m=seto(),k=seto();
    for (int i=1;i<=n;i++)
        a[i]=seto(),b[i]=seto(),c[i]=seto(),tcont[i]=i;
    while (m--){
        int u,v;
        u=seto(),v=seto();
        tcont[v]=max(tcont[v],u);
    }
    for (int i=1;i<=n;i++)
        prs[i]=make_pair(tcont[i],c[i]);
    sort(prs+1,prs+n+1);
    int qtail=0,tpoint=1;
    ll ans=0;
    for (int i=1;i<=n;i++){
        while (k<a[i] && qtail){
            k++;
            ans+=que[0];
            pop_heap(que,que+qtail);
            qtail--;
        }
        if (k<a[i]){
            ayano(-1);
            return 0;
        }
        k+=b[i];
        while (tpoint<=n && prs[tpoint].first==i){
            k--,ans+=prs[tpoint].second;
            que[qtail++]=-prs[tpoint].second;
            push_heap(que,que+qtail);
            tpoint++;
        }
    }
    while (k<0 && qtail){
        k++;
        ans+=que[0];
        pop_heap(que,que+qtail);
        qtail--;
    }
    ayano(ans);
    return 0;
}
//略去读入输出优化的实现
```

---

## 作者：lenlen (赞：18)

很板子的一个反悔贪心。

### Problem

题目大意：按照从 1 到 n 的顺序依次攻打，攻打第 i 个需 $a_i$ 个人，打完后可以获得 $b_i$ 个人，占领一个城池需 1 个人，价值是 $c_i$，占领方法可以攻打完后直接占领，或者从 u 走一条道路到 v 占领，且在 i 点只能走 i 的所有路径，求保证全部依次攻打下来的最大的价值。

数据范围： $n \leq 5000,m \leq 3 \times 10^5$，总人数 $\leq 5000$。

### Solution

看到这种题，而且 $n \leq 5000$，特别容易想到 dp，但是我这个蒟蒻只想到了反悔贪心。

我们可以求得每一个点要占领的最大占领点，i 的最大占领点 j 表示 j 有一条道路或者 $i=j$ 使得攻打完 j 后可以占领 i，且 $[j+1,n]$ 无法占领 i。

我们可以贪心的在每个点的最大占领点占领此点，贪心的正确性显然，我们在 $[i,j-1]$ 的任何一个地方占领 i，都会使得接下来的路途中我们会少 1 个人，只有在 j 占领时，可以保证占领了 i。

并且我们可以注意到，每一个占领的城池需要的代价是一样的，都是 1 个人，所以当我们发现因为前面的占领了太多，导致后面无法攻打时，我们可以从占领过的点中选择一个最小价值的点反悔，使人数加 1，直到人够了可以攻占为止。

当然若第 n 个点更新完后，人数为负，那么也要找点出来使得人数变成 0，更新方法同上。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7232,M=3e5+7232;
int n,m,k,x,y;
int a[N],b[N],c[N],t[N];
long long ans;
int vis[N];
struct hl{
    int v,nxt;
}e[M];
int h[N],cnt;
void add(int u,int v)
{
    e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;
}
struct len{
    int id,d;
    bool operator < (const len&x) const {
        return id>x.id;
    }
}tmp;
priority_queue<len> q;
priority_queue<int ,vector<int> ,greater<int> > p;
int mx(int x,int y)
{
    return x>y?x:y;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&c[i]),t[i]=i;//自己当然可以占领自己
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);
        t[y]=mx(t[y],x);//求最大占领点
    }
    for(int i=1;i<=n;i++) q.push((len){t[i],c[i]});
    for(int i=1;i<=n;i++)
    {
        while(k<a[i])
        {
            if(p.empty()) 
            {
                printf("-1\n");
                return 0;
            }
            ans-=p.top();k++;//取最小的价值来换人
            p.pop();
        }
        k+=b[i];
        while(!q.empty()&&q.top().id==i)
        {
            tmp=q.top();q.pop();
            p.push(tmp.d);
            k--;ans+=tmp.d;
        }
    }
    while(k<0) 
    {
        if(p.empty()) 
        {
            printf("-1\n");
            return 0;
        }
        ans-=p.top();k++;
        p.pop();
    }
    printf("%lld\n",ans);
}
```



---

## 作者：一扶苏一 (赞：14)

# 【带悔贪心】【CF1271D】 Portals

## Solution

一个显然的结论是：对于任何一个城堡 $u$，如果要往 $u$ 驻军，则在攻占编号最大的能向 $u$ 行军的城堡后再驻军，答案不会变劣。因此对于每一个城堡，我们只需要保存编号最大的城堡到他的行军路线。换句话说，对于每个节点 $u$，我们只需要保存它能到达的城堡 $v$ 中，$u$ 是编号最大的能到达 $v$ 的城堡的所有城堡 $v$。

### Algorithm 1：DP

设 $f_{i , j}$ 是考虑前 $i$ 座城堡，当前军队有 $j$ 个人的最大得分情况，则有：

$$f_{i, j} = f_{i - 1, j - b_i}~~(j \geq a_i)$$

对于每个城堡，枚举它向编号更小的城堡的行军路线，设当前考虑向城堡 $u$ 行军：

$$f_{i, j} = \max(f_{i, j}, f_{i, j + 1} + c_u)$$

考虑时间复杂度（认为最终人数与 $n$ 同阶）：第一个式子的转移是 $O(1)$ 的，共有 $O(n^2)$ 个状态，所以复杂度是 $O(n^2)$；而第二个转移只会发生 $O(n)$ 次，每次在编号最大的可以到达 $u$ 的城堡处发生，转移是 $O(1)$ 的，枚举第二维需要 $O(n)$ 的复杂度，因此复杂度 $O(n^2)$。因此总时间复杂度 $O(n^2)$。

### Algorithm 2：带悔贪心

考虑每到一个节点，都贪心的向这个节点保存的的行军路线所指向的节点驻军。考虑某一时刻如果人数不足（包括两种情况，一种是驻军时人数不足，一种是攻城时人数不足），那么考虑把前面的某些节点驻军收回。无论收回哪个节点的驻军，都只会给总人数增加 $1$，因此显然收回 $c$ 值最小的节点是最优的。因此用堆以 $c$ 为关键字维护所有已被驻军的节点，反悔时把最小的 pop 出来即可。

如果攻城时人数不够用且堆已空，那么显然无解。

考虑时间复杂度：每个城堡都只会被 push 和 pop $O(1)$ 次，上述操作的复杂度为 $O(\log n)$，因此总时间复杂度 $O(n \log n)$。

## Code

### Algorithm 1

```cpp
namespace Fusu {

const int maxn = 5005;
const int INF = 0x3f3f3f3f;

void Init();
void Solve();

void Main() {
  Init();
  Solve();
}

int n, m, t;
int a[maxn], b[maxn], c[maxn], pro[maxn];
std::vector<int> e[maxn];

void Init() {
  qr(n); qr(m); qr(t);
  for (int i = 1; i <= n; ++i) {
    qr(a[i]); qr(b[i]); qr(c[i]);
    pro[i] = i;
  }
  for (int u, v; m; --m) {
    qr(u); qr(v);
    pro[v] = std::max(pro[v], u);
  }
  for (int i = 1; i <= n; ++i) {
    e[pro[i]].push_back(i);
  }
}

int f[maxn];

void Solve() {
  std::fill(f, f + maxn, -INF);
  f[t] = 0;
  int ans = -INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = (t += b[i]); (j - b[i]) >= a[i]; --j) {
      f[j] = f[j - b[i]];
    }
    std::fill(f, f + a[i], -INF);
    for (auto u : e[i]) {
      for (int j = 0, dj = j + 1; j < t; j = dj++) {
        f[j] = std::max(f[j], f[dj] + c[u]);
      }
    }
  }
  for (int i = 0; i <= t; ++i) {
    ans = std::max(ans, f[i]);
  }
  qw((ans < 0) ? -1 : ans, '\n');
}

} // namespace Fusu
```

### Algorithm 2

```cpp
namespace Fusu {

const int maxn = 5005;

void Init();
void Solve();

void Main() {
  Init();
  Solve();
}

int n, m, t;
int a[maxn], b[maxn], c[maxn], pro[maxn];
std::vector<int> e[maxn];

void Init() {
  qr(n); qr(m); qr(t);
  for (int i = 1; i <= n; ++i) {
    qr(a[i]); qr(b[i]); qr(c[i]);
    pro[i] = i;
  }
  for (int u, v; m; --m) {
    qr(u); qr(v);
    pro[v] = std::max(pro[v], u);
  }
  for (int i = 1; i <= n; ++i) {
    e[pro[i]].push_back(i);
  }
}

struct Cmp {
  inline bool operator()(const int &x, const int &y) {
    return c[x] > c[y];
  }
};

std::priority_queue<int, std::vector<int>, Cmp> Q;
void Solve() {
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    while ((t < a[i]) && (!Q.empty())) {
      int x = Q.top(); Q.pop();
      ans -= c[x];
      ++t;
    }
    if (t < a[i]) {
      ans = -1;
      break;
    }
    t += b[i];
    for (auto u : e[i]) {
      if (t == 0) {
        if ((!Q.empty()) && (c[Q.top()] < c[u])) {
          int x = Q.top(); Q.pop();
          ans -= c[x];
          ++t;
        } else {
          continue;
        }
      }
      --t;
      Q.push(u);
      ans += c[u];
    }
  }
  qw(ans, '\n');
}

} // namespace Fusu
```

---

## 作者：vijone (赞：7)

[CF1271D Portals](https://www.luogu.com.cn/problem/CF1271D) 解题报告

本题方法很多，本题解讲解DP解法。

相比于我们更熟悉的填表法（当前点的状态根据之前点的状态推导出来），这道题更适合使用刷表法（由当前点的状态，更新其他点的状态）。对于本题，刷表法比填表法在处理边界上更为便捷，且更容易理解。~~这也是本人第一次尝试刷表法。~~

以上为本人关于本题做法的一些看法。下文给出的代码个人认为可以看做是刷表法。

------------

先讲讲建图：

本题需要在图上跑DP，但图上错综复杂的边仿佛使转移十分复杂，并且还可能出现重复计算 驻守某个城堡的贡献。~~而且实际上空间可能开不下。~~ 所以考虑删去无用的边。

考虑贪心：如果我们可以控制一个城堡，那么，我们尽可能迟的控制这个城堡。这是因为如果过早控制了这个城堡，比起不控制，将会消耗更多士兵，更容易出现士兵不够的情况，而越迟（攻下城堡越多），士兵数量越多，显然更优。

所以，对于每个城堡 $i$ ，在所有可以到达它的城堡组成的集合中，我们可以只保留编号最大城堡，并在枚举到这个最大城堡时考虑 $i$ 取或不取。

同时，题目中提到 “你刚占领这个城堡，可以立马派兵驻守。” 实际上，这种派兵方式并不意味着需要分类讨论，我们可以将每个点加入上文所述的 “到达它的城堡组成的集合” （即建立自环）并进行处理（保留最大编号的城堡）。通过这样处理，原图已被我们化简成许多树（一座森林），恰好能够做到不重不漏的考虑每一座城堡的取或不取。

再讲讲DP：

其实本人最初想写填表法，但因为边界不好处理而改写刷表法，所以最终代码里带有一些填表法的细节

设 $dp[i][j]$ 表示 进攻到第 $i$ 个城堡，且当前可用 $j$  个士兵的最高分数。

对于每一个 $i$ 可以 预处理 出 它可以到达的所有城堡（此时已处理掉所有无用的边） 按权值排序（降序，因为优先驻守更大权值的城堡）后的权值序列，并做一个前缀和。本人采用优先队列来实现排序等预处理。

下文（为了配合代码），我将使用 $dp[i-1][j]$ 来推导后面的结果。

因为攻占第 $i$ 座城堡，士兵将多 $b[i]$ 个，所以 $dp[i][j+b[i]]$  可以由 $dp[i-1][j]$ 直接推导过来。即 $dp[i][j+b[i]]=max(dp[i][j+b[i]],dp[i-1][j])$ 

而考虑派兵去驻守其他城堡：设第 $i$ 座城堡可以到达的城堡（设其一共 $num$ 个）按权值排序后的权值序列前缀和数组为 $su[i]$ 。用变量 $l$ 枚举 $1$ 至 $num$ ，则 $dp[i][j+b[i]-l]=max(dp[i][j+b[i]-l],dp[i-1][j]+su[l])$ ，含义就是在第 $i$ 个城堡，派出 $l$ 个士兵，去驻守了 $su[l]$ 代表的那些城堡。

由于需要 $a[i]$ 个士兵才能攻下城堡 $i$ 所以上文所述的转移方程中的 $j$ 必须从 $a[i]$ 开始枚举。(这里就体现了对于本题，刷表法处理边界比较简单)

最后,设 $b[i]$ 的总和为 $sum$ ，答案就是 $dp[n][j] \ (\forall j \in \{ 0,1,2,...sum+k\})$ 中的最大值。(即一遍 $for$ 循环遍历  $dp[n][j]$ )

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int e=1e3*6+100;
int dp[e][e];
int c[e],a[e],b[e];
int n,k,m;
int maxx[e];//保存可以到达某个城堡的其他城堡中编号最大的那一个。
struct nod
{
	int nxt,to; 
} s[e*2];
int head[e],cnt=0;
inline void add(int aa,int bb)
{
	cnt++;
	s[cnt].nxt=head[aa];
	s[cnt].to=bb;
	head[aa]=cnt;
}
priority_queue<int >q;
int sum[e];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	memset(dp,-0x3f,sizeof(dp));//初值为 -inf 意味着某个状态不合法。
	dp[0][k]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i]>>c[i];
		sum[i]=sum[i-1]+b[i];//为可以得到的士兵数 做前缀和
		maxx[i]=i;//自环
		if(sum[i-1]+k<a[i])//判断游戏能否胜利 
		{
			cout<<-1;return 0;
		}
	}
	int u,v;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v;
		maxx[v]=max(maxx[v],u);
	}
	for(int i=1;i<=n;i++)
	{
		add(maxx[i],i);//建图 
	}
	int num;int su[e];
	memset(su,0,sizeof(su));
	for(int i=1;i<=n;i++)
	{
		while(!q.empty())q.pop();
		num=0;
		for(int l=head[i];l;l=s[l].nxt)
		{
			q.push(c[s[l].to]);
		}
		su[0]=0;
		while(!q.empty())
		{
			num++;
			if(num!=0)su[num]=su[num-1]+q.top();
			else su[num]=q.top();//预处理前缀和
			q.pop();
		}
		for(int j=a[i];j+b[i]<=k+sum[i];j++)
		{
			if(dp[i-1][j]<0) continue;//如果 dp[i-1][j] 这个状态不合法，自然无法转移。
			dp[i][j+b[i]]=max(dp[i][j+b[i]],dp[i-1][j]);
			for(int bj=1;bj<=num;bj++) 
			{
				dp[i][j+b[i]-bj]=max(dp[i][j+b[i]-bj],dp[i-1][j]+su[bj]);
			}
		}
	}
	int ans=-0x3f3f3f3f;
	for(int i=0;i<=k+sum[n];i++)
	{
		ans=max(ans,dp[n][i]);
	}
	cout<<ans;
	return 0;
}
```


代码看似三重循环，实则均摊一下，发现转移是 $O(1)$ 的，预处理总共是$O(n \ log \ n)$的，所以总复杂度 $O(n^2)$ 。

在解题时，其实也不必拘泥于刷表法和填表法，我只是想提醒大家，对于状态转移，并不只有我们所熟悉的方法，对于特殊的题目，特殊的解法或许更优。

以上是本人的题解，如有错误请您指出。



---

## 作者：WZKQWQ (赞：3)

### 前言

很中规中距的贪心加 $\text{DP}$ 题，$\text{RMJ}$ 坏了所以在 $\text{CF}$ 上交的。

### 正文

首先，这个题意有些扭曲，设计状态时最难的部分在于转移时怎么记录哪些城堡已经被驻守了，后来发现不用记录，直接贪就行，因为越后面驻守城堡越赚，所以直接设计状态 $f_{i,j}$ 表示当前在第 $i$ 个城堡，军队有 $j$ 个兵时的最大得分，等于 $-1$ 表示状态不可达。

首先进攻下一个城堡的转移就是 $f_{i,j}=f_{i - 1,j - b_i}$，还有一种转移是驻守的转移，我们先预处理一下能到达每个城堡的最后一个城堡，再对每个城堡支配的城堡排序再做前缀和。设第 $i$ 个城堡的支配集大小 $len_i$，驻守这一部分的转移就是 $f_{i,j} = \max_{k=0}^{len_i}f_{i,j+k} + sum_{i,k}$。

所有支配集总大小是 $n$，所以复杂度是 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005;
int n,m,k,V,a[N],b[N],c[N],v[N],f[N][N];
vector<int>e[N];
vector<int>o[N];
bool cmp(int x,int y){return x > y;}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	V = k;
	for(int i = 1;i <= n;++i) scanf("%d%d%d",&a[i],&b[i],&c[i]),V += b[i];
	for(int i = 1,x,y;i <= m;++i){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
	}
	//printf("QwQ\n");
	for(int i = 1;i <= n;++i){
		v[i] = i;
		for(int j:e[i]) v[j] = i;
	}
	for(int i = 1;i <= n;++i) o[v[i]].push_back(c[i]);
	//printf("QwQ\n");
	for(int i = 1;i <= n;++i){
		sort(o[i].begin(),o[i].end(),cmp);
		int len = o[i].size();
		for(int j = 1;j < len;++j) o[i][j] += o[i][j - 1];
	} 
	//printf("QwQ\n");
	memset(f,-1,sizeof(f));
	f[0][k] = 0;
	for(int i = 1;i <= n;++i){
		for(int j = a[i] + b[i];j <= V;++j) f[i][j] = f[i - 1][j - b[i]];
		for(int j = 0;j <= V;++j){
			int len = o[i].size();
			for(int k = 1;k <= min(len,V - j);++k) if(f[i][j + k] != -1) f[i][j] = max(f[i][j],f[i][j + k] + o[i][k - 1]);
		}
	}
	int ans = -1;
	for(int i = 0;i <= V;++i) ans = max(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_Yoimiya_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1271D)。

本题方法很多，这里讲解 DP 解法。~~（我不会其他的）~~  
先看数据范围，$n≤5000$，考虑 DP。  
思路如下（闫式 DP 万岁）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9jpsi7d3.png)
时间复杂度为 $O(n^2)$ 量级。(同 01 背包)


------------

代码放送~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M(5e3+1);
const int D(0x3f3f3f3f);
int n, a[M],b[M],c[M];
int f[M][M],t[M],m,k;
struct node{
	int t,c;
};node l[M];
inline bool cmp(node x,node y){
	return x.t<y.t;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(register int i(1);i<=n;++i) {
		cin>>a[i]>>b[i]>>c[i];t[i]=i;//初始化最晚控制时间
	}
	while(m--){int u,v;cin>>u>>v;t[v]=max(t[v],u);}//更改最晚控制时间
	for(register int i(1);i<=n;++i){
		node pos;pos.c=c[i];pos.t=t[i];
		l[i]=pos;
	}
	sort(l+1,l+n+1,cmp);//按照最晚控制时间排序
	for(register int j(0);j<=k;++j) f[0][j]=0;//初始化
    for(register int j(k+1);j<M;++j) f[0][j]=-D;//又是初始化成极小值
	int tim(1);//指向当前可控制的城堡
	for(register int i(1);i<=n;++i){//正常转移
		for(register int j(0);j<M;++j) f[i][j]=-D;
		for(register int j(a[i]);j<M;++j)
		f[i][j+b[i]]=max(f[i][j+b[i]],f[i-1][j]);
		while(tim<=n&&l[tim].t==i){
			for(register int j(0);j<M-1;++j)
			f[i][j]=max(f[i][j],f[i][j+1]+l[tim].c);
			++tim;
		}
	}
	register int ans(-1);
	for(register int j(0);j<M;++j)ans=max(ans,f[n][j]);//找出最终答案
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：yuzhechuan (赞：3)

比赛时自己卡在了这题上，现在特来写篇比较符合现场思路的题解

---

### 题解：

dp很好想，状态也十分经典：设$f[i][j]$表示前$i$个城堡，手头剩下$j$个士兵的最大收益

初始化$f[0][k]=0$，其它赋为负无穷

从后往前继承状态时要从$a_i$开始枚举（能成功占领的条件），士兵数要减$b_i$（可以加兵的条件）

转移需要稍微思考下

是考虑从每条路转移吗？这样的话就会变得相当复杂，二维状态也不够用了

这时候就需要注意到一条很关键的性质：**假设当前要从$u$走路径$<u,v>$到$v$，那么在合法的前提下，$u$肯定是越大越好**

为什么呢？

因为题目有一条很重要的限制，就是$n$座城堡都要被占领，也就是说，既然这条路转移的收益是相同的，而多一个士兵也许能让你占领更多城堡，那么贪心地肯定是要把这个士兵留的时间越长越好

依照这样的思路，我们可以处理出$v_{u,i}$，满足存在边$<u,v>$，且$u$是连向$v$的最远的一个城堡

由于$v_{u,i}$都是互不干扰的，我们就可以根据收益的从大到小，贪心地在$v_{u,i}$中做选择，注意所做的选择必须是成前缀式的，也就是说要选次优的前提条件是更优的都选了

另外，题目还说可以原地留兵，这怎么搞呢？

我们不妨看成每个城堡上都有一条自环，与其它有着相同终点的路一起比较起点的远近即可

---

转移部分具体可以看看代码

---

代码中为了方便理解，最大士兵人数我用的都是常数5000，其实也可以把它换成士兵数的前缀和来减小常数

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=5005;
int ans=-1,a[N],b[N],c[N],link[N],f[N][N],n,m,k,g[N];
vector<int> nxt[N];

inline bool cmp(const int &x,const int &y){
	return c[x]>c[y];
}

signed main(){
	read(n);read(m);read(k);
	for(int i=1;i<=n;i++){
		read(a[i]);
		read(b[i]);
		read(c[i]);
		link[i]=i; //建立自环
	}
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		link[y]=max(link[y],x); //处理出最远起点
	}
	for(int i=1;i<=n;i++)
		nxt[link[i]].push_back(i); //枚举终点，从该点的最远起点连边
	for(int i=1;i<=n;i++)
		sort(nxt[i].begin(),nxt[i].end(),cmp); //按照收益从大到小排序
	memset(f,~0x3f,sizeof f);
	f[0][k]=0; //初始化
	for(int i=1;i<=n;i++){
		for(int j=a[i];j+b[i]<=5000;j++) //继承上个城堡的状态，注意a[i]和b[i]
			f[i][j+b[i]]=f[i-1][j];
		int cnt=nxt[i].size();
		for(int j=0;j<=5000;j++){
			int sum=0;
			g[j]=f[i][j]; //另外开个临时数组g[]，以免覆盖原数组
			for(int k=0;k<cnt;k++) if(j+k+1<=5000){
				sum+=c[nxt[i][k]]; //几个前缀和
				g[j]=max(g[j],f[i][j+k+1]+sum); //k+1是因为k是从0开始的，其实是表示在前缀上选择的城堡的数量（即要花费的士兵的数量）
			}
		}
		memcpy(f[i],g,sizeof g); //赋回去
	}
	for(int i=0;i<=5000;i++)
		ans=max(ans,f[n][i]);
	write(ans);
}
```

---

## 作者：万弘 (赞：3)

早控制不如晚控制.

对于每个点$u$,维护$maxv(u)$表示最晚的能到达$u$的点(注意这里认为$u$能到$u$),然后只连$maxv(u)->u$的边

假设现在在考虑$u$,已经控制的点集为$S$.若现有兵力不足$a(u)$,那么放弃价值最小的点,直到兵力不少于$a(u)$.(若无法做到就是-1).然后就控制了$u$,获得$b(u)$兵力.考虑$u$的每条出边,把能控制的点都控制了(加入$S$),先不管兵力是否够下一个点,因为$u+1$的时候会考虑的.

最后若兵力不足0,放弃价值最小的点直到$k\ge 0$.最后$S$中的点价值和就是答案.  
显然$S$可以用堆维护.时间复杂度$O(m\log n)$
```cpp

#define MAXN 5011
#define MAXM 300011
struct edge
{
    ll v,nxt;
}e[MAXM];
ll cnt=0,last[MAXN];
void adde(ll u,ll v)
{
    e[++cnt].v=v;
    e[cnt].nxt=last[u],last[u]=cnt;
}
std::priority_queue<ll,std::vector<ll>,std::greater<ll> >q;
ll maxv[MAXN],a[MAXN],b[MAXN],c[MAXN];
int main()
{
    ll n=read(),m=read(),k=read();
    for(ll u=1;u<=n;++u)
    {
        a[u]=read(),b[u]=read(),c[u]=read();
        maxv[u]=u;
    }
    for(ll i=1;i<=m;++i)
    {
        ll u=read(),v=read();
        umax(maxv[v],u);
    }
    for(ll i=1;i<=n;++i)adde(maxv[i],i);
    for(ll u=1;u<=n;++u)
    {
        while(k<a[u]&&!q.empty())++k,q.pop();
        if(k<a[u]){puts("-1");return 0;}
        k+=b[u];
        for(ll i=last[u];i;i=e[i].nxt)q.push(c[e[i].v]),--k;
    }
    while(k<0&&!q.empty())++k,q.pop();
    if(k<0){puts("-1");return 0;}
    ll ans=0;
    while(!q.empty())ans+=q.top(),q.pop();
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：TheShadow (赞：2)

# Solution

首先，我们需要一个贪心的想法：**对于城堡 $u$ ，我们一定是在最后一个能向它派兵的地方选择派兵**。

考虑正确性：如果在前面派兵，可能导致后面的士兵不够，而在最后的地方派兵，对之后的影响与在前面派兵相同。

所以选择在最后派兵影响是最小的。

这样我们只用其中的 $n$ 条边即可。

考虑 $dp$ 。

设 $dp_{i,j}$ 表示在第 $i$ 个城堡，还剩 $j$ 个士兵的最大收益。

这显然是一个 $01$ 背包，直接转移即可，时间复杂度 $O(n^2)$ 。

事实上这道题可以做到 $O(n\log n)$ 的复杂度。

还是考虑贪心。

我们每攻占一座城堡，就把所有的兵全部派出。

然后考虑调整。

如果当前剩余士兵 $S$ 不小于 $a_{i+1}$ ，那么直接向后走。

否则我们从收益小的开始依次收回士兵，直到 $S\geq a_{i+1}$ 为止。

如果全部收完也不能攻占下一个，就输了。

# Code

```cpp
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res;
}
const int MAXN = 5e3+5;
int n,m,k,u,v,val[MAXN];
struct Node{
	int a,b,c;
}node[MAXN];
vector<int> G[MAXN];
it max(int x,int y){return x>y?x:y;}
priority_queue<int> q;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m),read(k);
	for(ri i=1;i<=n;++i)
		read(node[i].a),read(node[i].b),read(node[i].c),val[i]=i;
	for(ri i=1;i<=m;++i)
		read(u),read(v),val[v]=max(val[v],u);
	for(ri i=1;i<=n;++i)
		G[val[i]].push_back(i);
	for(ri i=0,S=k;i<=n;++i){
		S+=node[i].b;
		for(ri j=0;j<(int)G[i].size();++j){
			int v=G[i][j];
			q.push(-node[v].c),--S;
		}
		while(S<node[i+1].a&&!q.empty())
			q.pop(),++S;
		if(S<node[i+1].a)
			return puts("-1"),0;
	}
	int res=0;
	while(!q.empty())
		res+=-q.top(),q.pop();
	print(res);
	return 0;
}
```


---

## 作者：Forg1weN (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1271D)

考虑动态规划。

首先一个城堡能被驻守，肯定是越晚驻守越好，如果提前驻守很有可能出现到了后面不够兵占领的情况。
 
记 $f_{i,j}$ 为占领了第 $i$ 个城堡还剩下 $j$ 个兵力的最大价值。

记 $S_i$ 为 $i$ 是城堡 $j$ 最后能够占领的集合，其中 $j<i$。

进入一个新城堡拥有的兵力就是上一个城堡拥有的兵力，**注意**，由于占领了城堡兵力会变多，转移应为：$f_{i,j}=f_{i-1,j-b_i}$。

若要回头占领城堡 $k\in S_i$，则转移为：$f_{i,j}=\max(f_{i,j+1}+c_k)$。

因为值域与 $N$ 同阶，所以时间复杂度为 $O(N^2)$。

## code

提供一份好看的代码


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5e5;
int n,m,k,ans,sum;
int a[maxn],b[maxn],c[maxn];
int way[maxn],f[5005][5005];
vector<int>G[maxn];
bool loser;
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	for(int i=1;i<=m;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		if(u>v)swap(u,v);
		if(way[u]<v)way[u]=v;
	}
	for(int i=1;i<=n;i++)
		if(way[i])
			G[way[i]].push_back(i);
	sum=k;
	for(int i=1;i<=n;i++) {
		if(sum<a[i])loser=1;
		sum+=b[i];
		for(int j=a[i]+b[i];j<=sum;j++)
			f[i][j]=f[i-1][j-b[i]];
		if(!way[i]) {
			for(int j=0;j< sum;j++)
				f[i][j]=max(f[i][j],f[i][j+1]+c[i]);
		}
		for(auto k:G[i]) {
			for(int j=0;j< sum;j++)
				f[i][j]=max(f[i][j],f[i][j+1]+c[k]);
		}
	}
	if(loser)printf("-1");
	else {
		for(int i=0;i<=sum;i++)
			ans=max(ans,f[n][i]);
		printf("%d",ans);
	}
		
	return 0;
}
```


---

## 作者：OrezTsim (赞：1)

虽然给出了图，但是和图没有太大关系。

首先可以想到一个非常朴素的 DP。

设 $dp_{i,j}$ 表示当前占领到 $i$，拥有 $j$ 个士兵的最大 $\sum c$。

那么转移就很显然了。

$\begin{cases}dp_{i,j+b_i}\leftarrow dp_{i-1,j}\space(j\ge a_i)\\dp_{i,j}\leftarrow dp_{i,j+1}+c_{to}\space(i-to\text{ is connected})\end{cases}$

枚举 $i,j,to$，时间复杂度 $O(n^2m)$，不能承受。

考虑进行优化。由于 $to$ 是唯一一个状态内没出现的枚举量，从 $to$ 方面优化。

想到一个贪心。对于每一个 $to$，显然是到最后能走的时候再走最优。

为什么？因为每一次占领不消耗士兵，而有限制 $a_i$，所以当前士兵越多越好。

也就是，不妨让士兵再走一段，来获得 $b_i$ 个士兵，最后再走到 $to$ 去。

所以预处理出每一个点最后由哪个点到达，再走就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10, MAX = 5e3, inf = 1e9;
int n, m, k, lt[N], a[N], b[N], c[N], dp[N][N];
pair <int, int> fk[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n >> m >> k; for (int i = 1; i <= n; ++i)
        cin >> a[i] >> b[i] >> c[i], lt[i] = i;
    for (int i = 1, u, v; i <= m; ++i)
        cin >> u >> v, lt[v] = max(lt[v], u);
    for (int i = 1; i <= n; ++i) fk[i] = {lt[i], c[i]};
    sort(fk + 1, fk + 1 + n);
    for (int i = k + 1; i <= MAX; ++i) dp[0][i] = -inf;
    int prev = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= MAX; ++j) dp[i][j] = -inf;
        for (int j = a[i]; j <= MAX; ++j)
            dp[i][j + b[i]] = max(dp[i][j + b[i]], dp[i - 1][j]);
        while (prev <= n && fk[prev].first == i) {
            for (int j = 0; j < MAX; ++j)
                dp[i][j] = max(dp[i][j], dp[i][j + 1] + fk[prev].second);
            ++prev;
        }
    }
    int res = -1;
    for (int i = 0; i <= MAX; ++i) res = max(res, dp[n][i]);
    cout << res << endl;
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 闲话

感觉应该出一个 $n \leq 10^6$ 并且 $k,b_i \leq 10^9$ 的 Hard Version 版本，因为这道题两种做法，一种是 $O(n(k+\sum b_i))$ 的 dp，一种是 $O(n \log n)$ 的贪心。

## 思路

有一个非常好想的贪心思路可以大大简化题目难度，那就是对于每个城堡我们都尽量拖到最后再控制，因为控制城堡需要消耗士兵，留着士兵并不会使答案更劣。

因此，我们先求出每个城堡最晚最晚什么时候必须占领。这个很好求，因为输入的 $u,v$ 保证 $u>v$ 所以我们每次用 $u$ 更新 $v$ 最晚的时间 $lst_v$ 即可。为什么不用 $lst_u$ 更新呢？因为题目中说了 **如果走到了 $i+1$ 那么 $i$ 这里的小路就不能用了**，也就是说这个 $lst$ 数组不具有可转移性。

### 一、dp 做法

想到这里题目难度已经几乎没有了，剩下的就是一个裸的背包问题。我们设 $dp_{i,j}$ 表示当前到了 $i$ 节点，拥有 $j$ 个士兵的时候，前 $i$ 个节点能取得的最大值。

第一个转移就是我们攻打 $i$ 这里。那么我们的士兵会需要 $a_i$ 个，所以 $j \geq a_i$；另外我们会获得 $b_i$ 个士兵，所以要从 $j-b_i$ 转移过来，因此 $j \geq a_i+b_i$；注意我们并没有占领，所以这个 $c_i$ 不能加上。

那么第一个转移方程就出来了：

$$dp_{i,j}=\max(dp_{i-1,j-b_i},dp_{i,j})[j \geq a_i]$$

第二个转移就是我们占领所有当前必须占领的地方。这个时候我们会损失 $1$ 的兵力，获得 $c_i$ 的价值。

所以第二个转移方程：

$$dp_{i,j}=\max_{lst_k=i}(dp_{i,j},dp_{i,j+1}+c_k)$$

上面虽然枚举了 $k$，但实际上是一个双指针，因为要更新的城堡一共就 $n$ 个，均摊下来并不会升高复杂度。

最后输出 $\max\limits_{j=0}^{k+\sum b_i} dp_{n,j}$ 即可。时间、空间复杂度均为 $O(n(k+\sum b_i))$。

### Code 1

```cpp
#include <bits/stdc++.h>
inline int qr(){
	char ch=getchar(); bool f=1; int w=0;
	for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-')f=0;
	for(;ch>='0' && ch<='9';ch=getchar()) w=w*10+ch-'0';
	return f?w:-w;
}
using namespace std;
const int MAXN=5005;

int a[MAXN],b[MAXN],c[MAXN];
int lst[MAXN],dp[MAXN][MAXN];
pair<int,int> occ[MAXN]; // 闲话：occ, short of occupy = 占领（
int main(){
	int n=qr(),m=qr(),k=qr(),M=k;
	for(int i=1;i<=n;i++){
		a[i]=qr(); b[i]=qr();
		c[i]=qr(); lst[i]=i;
		M+=b[i]; // 计算背包容量（这个相比于 5000，可以大大减小常数） 
	}
	for(int i=1;i<=m;i++){
		int u=qr(),v=qr();
		lst[v]=max(lst[v],u); // 计算 lst 
	}
	for(int i=1;i<=n;i++) occ[i]=make_pair(lst[i],c[i]); // 按照 lst 从小到大排序，顺便记录 c 
	sort(occ+1,occ+1+n);
	int cur=1,maxn=-1;
	memset(dp,-0x3f,sizeof(dp));
	for(int i=0;i<=k;i++) dp[0][i]=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i]+b[i];j<=M;j++)
			dp[i][j]=max(dp[i][j],dp[i-1][j-b[i]]); // 转移 1 
		while(occ[cur].first==i && cur<=n){
			for(int j=0;j<=M;j++)
				dp[i][j]=max(dp[i][j],dp[i][j+1]+occ[cur].second); // 转移 2 
			cur++;
		}
//		for(int j=0;j<=M;j++){
//			cout<<"dp["<<i<<"]["<<j<<"]="<<dp[i][j]<<endl;
//		}
	}
	for(int j=0;j<=M;j++) maxn=max(maxn,dp[n][j]);
	cout<<maxn<<endl; 
	return 0;
}

```

根据实用主义，能做出来就行，应该到此为止。~~但是由于我比较懒，懒得到此为止，所以就口胡了一个奇奇怪怪的贪心~~。

$$\text{----------------------------------------- 实而不华的分割线 -----------------------------------------}$$

### 二、贪心做法

我们可不可以考虑，先把这个游戏打完看能不能通关，通关之后再每次考虑占领价值更大的城堡呢？

所以我们记录一个 $d_i$ 表示到了 $i$ 这个位置剩余的士兵数量。然后，我们把所有的城堡按价值从大到小排序。如果我们要在 $lst_i$ 时刻占领这个城堡，我们必须让 $lst_i$ 及之后的时刻，至少都剩下一个士兵，所以我们区间查询最小值即可。然后，我们对 $[lst_i,n]$ 这个区间进行区间减一。

暴力做的复杂度是 $O(n^2)$。所以可以再出一个 $n \leq 5000$ 然后 $b_i,k \leq 10^{9}$ 的（狗头

不过这个复杂度很好优化，线段树维护即可，时间复杂度 $O(n \log n)$。关键是码量也挺短，你说 dp 气不气？

![](https://cdn.luogu.com.cn/upload/image_hosting/w2yd8qup.png)

正确性的话，如果我们大的能放不放，那么相当于放一个更小的城堡，答案不会更优，所以这个贪心应该没啥问题。

### Code 2

```cpp
#include <bits/stdc++.h>
inline int qr(){
	char ch=getchar(); bool f=1; int w=0;
	for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-')f=0;
	for(;ch>='0' && ch<='9';ch=getchar()) w=w*10+ch-'0';
	return f?w:-w;
}

using namespace std;
const int MAXN=5005;

int a[MAXN],b[MAXN],c[MAXN];
int d[MAXN],lst[MAXN];
pair<int,int> occ[MAXN];

namespace Seg_tree{ // 线段树维护区间最小值，支持区间 -1 
	int tr[MAXN<<2],tag[MAXN<<2];
	void push_down(int p,int l,int r){
		if(!tag[p]) return;
		tr[p<<1]+=tag[p];
		tr[p<<1|1]+=tag[p];
		tag[p<<1]+=tag[p];
		tag[p<<1|1]+=tag[p];
		tag[p]=0;
	}
	void build(int p,int l,int r){
		if(l==r){
			tr[p]=d[l];
			return;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		tr[p]=min(tr[p<<1],tr[p<<1|1]);
	}
	void upd(int p,int l,int r,int st,int en){
		if(l>en || r<st) return;
		if(st<=l && r<=en){
			tr[p]--;
			tag[p]--;
			return;
		}
		push_down(p,l,r);
		int mid=(l+r)>>1;
		upd(p<<1,l,mid,st,en);
		upd(p<<1|1,mid+1,r,st,en);
		tr[p]=min(tr[p<<1],tr[p<<1|1]);
	}
	int query(int p,int l,int r,int st,int en){
		if(l>en || r<st) return 1e9;
		if(st<=l && r<=en) return tr[p];
		push_down(p,l,r);
		int mid=(l+r)>>1;
		return min(query(p<<1,l,mid,st,en),query(p<<1|1,mid+1,r,st,en)); 
	}
}
using namespace Seg_tree;
int main(){
	int n=qr(),m=qr(),k=qr();
	for(int i=1;i<=n;i++){
		a[i]=qr(); b[i]=qr();
		c[i]=qr(); lst[i]=i;
	}
	for(int i=1;i<=m;i++){
		int u=qr(),v=qr();
		lst[v]=max(lst[v],u); // 和 dp 的版本同理，计算 lst 
	}
	int now=k;
	for(int i=1;i<=n;i++){
		if(now<a[i]) return puts("-1"),0; // 如果兵不够了那就 GG 了 
		now=now+b[i]; // 否则更新兵力 
		d[i]=now-a[i+1]; // 计算当前富裕兵力 
	}
	build(1,1,n); // 建树 
	for(int i=1;i<=n;i++) occ[i]=make_pair(c[i],lst[i]); // 按照 c 为第一关键字，和 dp 不同 
	sort(occ+1,occ+1+n,greater<pair<int,int> >()); // 从大到小 
	int ans=0;
	for(int i=1;i<=n;i++){
		int val=occ[i].first,x=occ[i].second;
		if(query(1,1,n,x,n)>0){ // 如果能放就放 
			ans+=val; // 记录价值
			upd(1,1,n,x,n); // 区间 -1 
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

考虑贪心。因为无论驻守哪个城堡，都要花费 $1$ 的代价，所以肯定优先驻守 $c_i$ 大的。一个城堡能够派兵驻守，意味着即使不用这个兵，后面城堡也能全部占领。所以可以先处理 $p_i$，表示占领第 $i$ 个城堡后最多剩余的士兵数。如果不驻守任何一个城堡也无法满足条件，那就是无解。

然后从大到小判断，每次找到能被这个点影响的，编号最大的点。为什么是编号最大的呢？假设编号最大点为 $a$，另有一个非最大点为 $b$。如果选 $a$，则会影响区间 $[a,n]$，如果选 $b$，则会影响区间 $[b,n]$，显然如果 $[a,n]$ 不能满足条件，$[b,n]$ 也不会满足条件。然后把 $[a,n]$ 中的每个数都减一就行。如果 $[a,n]$ 中出现了负数，意味着如果驻守这个城堡，后面就无法全部占领，所以该城堡无法驻守。

可以发现操作就是区间加，区间取 $\min$，可以用线段树维护，总时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
struct tree{
	int l,r,mi,tag;
}t[N<<2];
struct Node{
	int a,b,c,id;
}e[N];
int n,m,k,to[N],pp[N],ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].mi=pp[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t[p].mi=min(t[p<<1].mi,t[p<<1|1].mi);
}
bool cmp(Node xxx,Node yyy){
	return xxx.c>yyy.c;
} 
void spread(int p){
	if(t[p].tag){
		t[p<<1].mi+=t[p].tag;
		t[p<<1|1].mi+=t[p].tag;
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0;
	}
}
void add(int p,int l,int r,int w){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].mi+=w;t[p].tag+=w;return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)add(p<<1,l,r,w);
	if(r>mid)add(p<<1|1,l,r,w);
	t[p].mi=min(t[p<<1].mi,t[p<<1|1].mi);
}
int ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r){
		return t[p].mi;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	int mi=1e9;
	if(l<=mid)mi=min(mi,ask(p<<1,l,r));
	if(r>mid)mi=min(mi,ask(p<<1|1,l,r));
	return mi;
}
int main(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)to[i]=i;
	for(int i=1;i<=n;i++){
		e[i].a=read();e[i].b=read();e[i].c=read();e[i].id=i;
	}
	for(int i=1;i<=m;i++){
		int u,v;u=read();v=read();
		to[v]=max(to[v],u);
	}
	for(int i=1;i<=n;i++){
		//cout<<k<<endl;
		if(k<e[i].a){
			puts("-1");return 0;
		}
		pp[i-1]=k-e[i].a;
		k+=e[i].b;
	}
	pp[n]=k;
	//for(int i=1;i<=n;i++)cout<<pp[i]<<" ";
	//cout<<endl;
	build(1,1,n);
	sort(e+1,e+1+n,cmp);
	for(int i=1;i<=n;i++){
		//cout<<to[e[i].id]<<" "<<n<<endl;
		add(1,to[e[i].id],n,-1);
		//cout<<ask(1,to[e[i].id],n)<<endl; 
		if(ask(1,to[e[i].id],n)>=0){
			ans+=e[i].c;
		}
		else{
			add(1,to[e[i].id],n,1);
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Day_Dreamer_H (赞：0)

# CF1271D 题解
## 题目大意
给定 $n$ 个重要度为 $c_i$ 的点，$m$ 条边，以及初始军队数量 $k$，你需要从 $1$ 到 $n$ 依次占领，占领需要至少 $a_i$ 个兵力但是不会消耗，占领后可以增加 $b_i$ 个兵，对于每一个被占领的点，你可以驻守至少一个兵，最终要求有驻守的点重要度之和最大。
## 思路
这题是很明显的反悔贪心，因为如果兵不够用了我们可以继续把驻守的兵重新拿回来凑数，那么显然有一些之后占领点得到的兵是派不回去的，因为有的点没有道路到前面。所以我们可以记录每一个点 $i$ 利用道路所能到达的最后的点，因为再往后走的话兵力就无法到达 $i$ 了，所以我们必须在最后一个可到达点做出驻守或是不驻守的决定

具体实现就是循环判断每一个点，如果当前兵力不足以攻下这个点那就把之前驻守的重要度最小的一个点上的兵征用过来，如果已经没有驻守依旧不够那就输出 $-1$，攻下这个点增加 $b_i$ 兵力后对之前可到达点进行判断是否驻守，如果没有兵了有两种选择：不驻守或是把之前重要度最低的一个兵调过来，最后统计即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,result;
int a[5005],b[5005],c[5005];
int maxi_arrive[5005];//可到达最后的点
vector<int>adj[5005];
priority_queue<int,vector<int>,greater<int> > q;//储存的是驻守的点的重要度
int main(){
	cin>>n>>m>>k;
	for(int i = 1;i<=n;i++){
		scanf("%d %d %d",&a[i],&b[i],&c[i]);
		maxi_arrive[i] = i;
	}
	for(int i = 0;i<m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		maxi_arrive[v] = max(maxi_arrive[v],u);
	}
	for(int i = 1;i<=n;i++){
		adj[maxi_arrive[i]].push_back(i);
	}
	for(int i = 1;i<=n;i++){
		while(k<a[i]){
			if(q.size() == 0){
				cout<<"-1";
				return 0;
			}
			k++;
			result-=q.top();
			q.pop();
		}
		k+=b[i];
		for(int j = 0;j<adj[i].size();j++){
			if(k == 0){
				if(q.size()!=0&&c[adj[i][j]]>q.top()){
					result = result-q.top()+c[adj[i][j]];
					q.pop();
					q.push(c[adj[i][j]]);
				}
			}else{
				k--;
				q.push(c[adj[i][j]]);
				result+=c[adj[i][j]];
			}	
		}
	}
	cout<<result;
}
```

---

## 作者：Find_Yourself (赞：0)

贪心+DP。

对于一个点，后选显然比先选好，也就是说每个点都对应了唯一一个来源。

于是我们可以把每个点所能回溯到的点的收益值从大到小排序，贪心地选前缀。

定义 $f_{i,j}$ 表示考虑了前 $i$ 个点，剩下 $j$ 个人，最大收益。

转移方程和 $01$ 背包的一样。

$$f_{i,j}=f_{i-1,j-b_i}$$

$$f_{i,j}=\max\limits_{t}(f_{i-1,j+t-b_i}+\sum\limits_{k=1}^{t}c_{vec_{i,k}})$$

注意边界,我因为 RE 调了半天....

复杂度 $O(n^2)$。代码很短。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5000+5,inf=INT_MAX>>1;
int n,m,k,a[N],b[N],c[N],l[N],f[N][N];
vector<int>vec[N];
bool cmp(int x,int y){return c[x]>c[y];}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i]>>c[i];
		l[i]=i;
	}
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		l[v]=max(l[v],u);
	}
	for(int i=1;i<=n;++i)vec[l[i]].push_back(i);
	for(int i=1;i<=n;++i)sort(vec[i].begin(),vec[i].end(),cmp);
	memset(f,~0x3f,sizeof(f));f[0][k]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=5000;++j){
			int v=0,w=0;
			if(j-b[i]>=a[i])f[i][j]=f[i-1][j-b[i]];
			for(int t=0;t<vec[i].size();++t){
				++v;w+=c[vec[i][t]];
				int p=j+v-b[i];
				if(p>=a[i]&&p<=5000)f[i][j]=max(f[i][j],f[i-1][p]+w);
			}
		}
	}
	int ans=-1;
	for(int j=0;j<=5000;++j)ans=max(ans,f[n][j]);
	cout<<ans<<endl;
  return 0;
}

```


---

## 作者：D2T1 (赞：0)

~~省选前随便写点东西~~

容易发现兵的数量不降，故每个点越晚占领肯定越优。

那么我们就把每个 $c_i$ 绑在能够占领 $i$ 号点（即存在 $j\to i$）的下标最大的点 $j$ 上。若不存在这样的点 $j$，直接绑在 $i$ 上。

注意到 $k+\sum b\leq 5000$，故可以直接 dp。设 $f_{i,j}$ 表示考虑前 $i$ 个点，有 $j$ 个兵的最大收益，方程：

$$f_{i,j+b_i-k}=\max\{f_{i-1,j}+c_{i,k}\}$$

其中 $c_{i,k}$ 表示绑在 $i$ 号点上的前 $k$ 大 $c$ 的和。

注意边界：能够转移当且仅当 $j-a_i\geq0,j+b_i-k\geq0$。

初始条件 $f_{0,i}=0,0\leq i\leq k$，其他位置均为 $-\inf$。

```cpp
//CF1271D
#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int n, m, k, a[N], b[N], vis[N], f[N][N];
vector<int> c[N], g[N];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++ i){
		int tmp;
		scanf("%d%d%d", &a[i], &b[i], &tmp);
		c[i].push_back(tmp);
	}
	for(int i = 1; i <= m; ++ i){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
	}
	for(int i = n; i >= 1; -- i){
		for(int y : g[i]){
			if(vis[y]){
				continue;
			}
			vis[y] = 1;
			c[i].push_back(c[y][0]);
			c[y].clear();
		}
	}
	for(int i = 1; i <= n; ++ i){
		sort(c[i].begin(), c[i].end());
		c[i].push_back(0);
		reverse(c[i].begin(), c[i].end());
		for(int j = 1; j < c[i].size(); ++ j){
			c[i][j] += c[i][j-1];
		}
	}
	memset(f, 0xcf, sizeof(f));
	for(int i = 0; i <= k; ++ i){
		f[0][i] = 0;
	}
	for(int i = 1; i <= n; ++ i){
		for(int j = 0; j <= 5000; ++ j){
			for(int k = 0; k < c[i].size(); ++ k){
				if(j >= a[i] && j+b[i]-k >= 0 && f[i-1][j] >= 0){
					f[i][j+b[i]-k] = max(f[i][j+b[i]-k], f[i-1][j] + c[i][k]);
				}
			}
		}
	}
	int ans = 0xcfcfcfcf;
	for(int i = 0; i <= 5000; ++ i){
		ans = max(ans, f[n][i]);
	}
	printf("%d\n", ans < 0 ? -1 : ans);
}
```

---

## 作者：Yansuan_HCl (赞：0)

如果直接按图中的关系进行转移，则会出现重复派兵的情况。

**多个难以处理，考虑保留其中一个**。一个贪心的做法是，记录每个点能被控制的最大时间，这样可以使带着攻城的军队最多。

```cpp
const int N = 5005;
int n, m, k, a[N], b[N], c[N];
BS<int> g[N], t[N];
int postCont[N]; // 一个点最晚能被哪个点派兵占据

int f[N][N]; // 已攻占 i, 现有 j 个士兵
int main() {
    rd(n, m, k);
    U (i, 1, n) rd(a[i], b[i], c[i]), postCont[i] = i;

    U (i, 1, m) {
        int u, v; rd(u, v);
        g[u] += v;
        postCont[v] = max(postCont[v], u);
    }
    U (i, 1, n) t[postCont[i]] += i;

    ms(f, 0xc0);
    f[0][k] = 0;
    U (i, 1, n) {
        U (j, a[i], 5000 - b[i])
            f[i][j + b[i]] = f[i - 1][j];
        for (int v : t[i])
            U (j, 1, 5000)
                f[i][j - 1] = max(f[i][j] + c[v], f[i][j - 1]);
    }

    int ans = f[n][0];
    U (j, 1, 5000)
        ans = max(ans, f[n][j]);
    printf("%d\n", (ans < 0) ? -1 : ans);
}
```

---

## 作者：vvauted (赞：0)

- [CF1271D Portals](https://www.luogu.com.cn/problem/CF1271D)

易发现一个性质，只有驻兵操作才会使兵力减少，影响最终是否能胜利。我们考虑一个城堡 $i$，如果要在 $i$ 处驻兵，我们一定是在最后一个能到达 $i$ 的地方向 $i$ 驻兵，这样才能尽可能的减少驻兵操作对结果的影响。

设：

$$s_i= \sum_{k=1}^i b_i+k$$

即为如果在前 $i$ 位不驻兵此时的兵力，那显然在前 $i$ 位我们最多进行驻兵 $lim_i=\min_{k=i+1}^n(s_{k-1}-a_k)$ 次，特别的，$lim_n =s_n$，那么我们即可以在这个限制下做背包：

> $f_{i,j}$ 为经过前 $i$ 个城堡，驻军了 $j$ 个城堡的最大值，其中 $j\leq lim_i$，那么答案即为 $f_{n,s_n}$

**Code**

```cpp
#include <bits/stdc++.h>
#define Nep(i, l, r) for(int i = l; i != r; ++ i)
#define Rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rep(i, l, r) for(int i = l; i < r; ++ i)
#define Lep(i, l, r) for(int i = l; i >= r; -- i)
#define lep(i, l, r) for(int i = l; i > r; -- i)
#define ll long long
#define ull unsigned long long
#define int long long
#define Maxn 5005
#define Min(a, b) a = std :: min(a, b)
#define Max(a, b) a = std :: max(a, b)

int n, m, k, dp[Maxn], minn = 0, lim[Maxn];
std :: vector <int> g[Maxn];
int a[Maxn], b[Maxn], c[Maxn];
int las[Maxn], s[Maxn];

signed main() {
	scanf("%lld%lld%lld", &n, &m, &s[0]); int u, v; int ans = 0; 
    Rep(i, 1, n) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]), las[i] = i, s[i] = s[i - 1] + b[i];
    Rep(i, 1, n) Min(minn, lim[i] = s[i - 1] - a[i]); if(minn) return printf("-1"), 0; lim[n + 1] = s[n];
    Lep(i, n, 1) Min(lim[i], lim[i + 1]); Rep(i, 1, m) scanf("%lld%lld", &u, &v), Max(las[v], u);
    Rep(i, 1, n) g[las[i]].push_back(i);  Rep(i, 1, n)  for(int j : g[i]) Lep(k, lim[i + 1], 1) Max(dp[k], dp[k - 1] + c[j]);
    Rep(i, 0, s[n]) Max(ans, dp[i]); return printf("%lld", ans), 0;
}
```

---

## 作者：fanypcd (赞：0)

比较经典的贪心题了。

需要明确的一点是每座城堡能够空余的士兵数单调不减。

那显然的一个贪心是对于这座城堡，（如果要控制的话）选取最后能倒回来控制这个城堡的位置派兵是最优的。

然后贪心地，对于每个位置，我们可以求出当前这个位置‘值得’倒回去驻兵的有哪些位置（邻接表或者动态数组），显然每个城堡只会对应一个回溯点。如果当前这个倒回去的位置的价值高于我已经选过的某些位置的价值，那么我可以考虑反悔做出的选择，转而选择在价值更高的位置驻兵。

具体的实现就是用一个优先队列存储下已做出的选择的价值，然后插入当前能做出的选择，再弹出一定数量的价值（保证能征服下一个城堡）。

注意 ```priority_queue``` 默认是大根堆，价值取相反数后堆顶就是最小值（取出的时候需要乘上 -1）。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 5005
int n, k, a[N], b[N], c[N];
int m, last[N];
vector<int> fr[N];
bool cmp(int &aa, int &bb)
{
	return c[aa] > c[bb];
}
priority_queue<int> q;
signed main()
{
	read(n), read(m), read(k);
	for(int i = 1; i <= n; i++)
	{
		last[i] = i;//自己的位置显然可以直接驻军
		read(a[i]), read(b[i]), read(c[i]);
	}
	int u, v;
	for(int i = 1; i <= m; i++)
	{
		read(u), read(v);
		last[v] = max(last[v], u);//比较取最后的那个位置
	}
	for(int i = 1; i <= n; i++)
	{
		fr[last[i]].emplace_back(i);
	}
	int ans = 0;
	if(k < a[1])//现有兵力无法征服 1 号城堡，无解
	{
		printf("-1");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		k += b[i];
		sort(fr[i].begin(), fr[i].end(), cmp);//贪心地将当前位置能回溯的位置按价值从大到小排序
		for(int j = 0; j < fr[i].size(); j++)
		{
			ans += c[fr[i][j]];
			q.push(-c[fr[i][j]]);
			k--;
		}
		while(k < a[i + 1])//贪心地弹出部分决策，保证能征服下一个城堡
		{
			if(q.empty())
			{
				printf("-1");
				return 0;
			}
			ans += q.top();	
			q.pop();
			k++;
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：RedLycoris (赞：0)

在1:43时A掉了这一题，成功翻盘，rank34

---

题解：

贪心+dp

首先我们可以发现，如果一个城堡是可以被守卫的，那么，我们就会尽可能的让他往后被守卫。

为什么呢？

因为，如果在前面就守卫了，也许就会影响到后面的关卡过不去。而到了最后，如果你再不守卫的话，那么就没有机会了。但是如果到最后再守卫，造成的代价与之前一样，但是可以让他有更多的机会去进攻。

dp:

令dp[i][j]表示考虑到第i个城堡时，剩余了j个人时的最大成果。

```cpp
inline void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)cin>>a[i]>>b[i]>>c[i];  //读入
	checkbad();                       //特判-1
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		lst[v]=max(lst[v],u);             //找最后
	}
	for(int i=1;i<=n;++i){
		lst[i]=max(lst[i],i);
		v[lst[i]].push_back(i);
	}
	for(int i=1;i<=n;++i)sort(v[i].begin(),v[i].end(),cmp);  //贪心
	for(int i=1;i<=n;++i)for(int j=0;j<=5000;++j)dp[i][j]=-INf; //初始化
	dp[1][k]=0;
	for(int i=1;i<=n;++i){
		for(int j=a[i];j<=5000;++j){
			dp[i+1][j+b[i]]=max(dp[i+1][j+b[i]],dp[i][j]);  //不选
			int sum=0,cnt=0;
			for(int f:v[i]){  //贪心的选
				sum+=c[f];
				++cnt;
				if(j+b[i]-cnt>=0)dp[i+1][j+b[i]-cnt]=max(dp[i+1][j+b[i]-cnt],dp[i][j]+sum);
				else break;   //优化
			}
		}
	}
    
```

---

