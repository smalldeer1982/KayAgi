# SubString

## 题目描述

给定一个字符串 `init`，要求支持两个操作：

- 在当前字符串的后面插入一个字符串。

- 询问字符串 $s$ 在当前字符串中出现了几次。(作为连续子串)

强制在线。

## 说明/提示

$|\mathrm{init}| \leq 6 \times 10^5$，$Q \leq 6\times 10^5$，询问总长度 $\leq 3 \times 10^6$。

保证字符串中只会出现 `A` 和 `B`。

为防止评测过慢，对于测试点 $2,3,5,6,8,11$ 时限为 3s，其余为 1s。

原题：BZOJ 2555

## 样例 #1

### 输入

```
2
A
QUERY B
ADD BBABBBBAAB```

### 输出

```
0```

# 题解

## 作者：皎月半洒花 (赞：19)

个人认为比其他题解写的都更详细更明白/kel

考虑字符串 $s$ 出现的次数，在SAM中，一个节点里面的某个子串的出现次数就是它的子树的出现次数和，因为长的后缀与短的后缀之间信息不共享，所以修改操作本质上是在进行 $parent$ 树上的链加。

考虑一种神奇的写法。每次对于新建的节点 $np$ ，他的贡献应该是 $parent$ 树上 $1\sim np$ 这条路径上的所有点。于是考虑先 `merge(1, np)` ，把 $np$ 给 `splay` 上去之后内部就变成了一棵以 $np$ 为根的一条链，这样就可以不用考虑链加，直接在 $np$ 处打标记即可。

似乎查询操作更为神奇。因为查询的时候只需要对于走到的一个点 $x$ ，直接把他 `splay` 掉就可以维护信息。看上去似乎不是很对，因为对 $x$ 产生贡献的是一颗子树而不是一条链。但这样做其实有他独特的正确性保证，即每个点都存在且仅存在于一棵 `splay` ，换 `splay` 的时候势必要 `access`，而 `access` 时本质上就已经把原来的标记给下放干净了，所以每次只有可能是当前的 `splay` 还有信息没有维护清楚。也就是每次只需要管一条链，剩下的链的标记已经清完了。这样就只需要 `splay` 一下即可。

写的时候，为了卡常发现了个更神奇的地方，就是在SAM里面抠点插子树/插点这两个操作，由于都保证了父亲不存在，所以 `Link` 这个操作，本质上是不需要 `make_root` 的，实测这样就会快很多很多。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

#define il inline
#define fa(x) t[x].fa
#define rv(x) t[x].rev
#define vl(x) t[x].val
#define tg(x) t[x].tag
#define lc(x) t[x].son[0]
#define rc(x) t[x].son[1]

using namespace std ;

const int N = 1000010 ;
const int M = 1500010 ;

struct LCT{
    int fa ;
    int rev ;
    int val ;
    int tag ;
    int son[2] ;
}t[M] ;
int n ;
int m ;
int tp ;
int len ;
int ans ;
int res ;
char s[N] ;
char o[N] ;
int stk[M] ;

bool nroot(int x){
    return ((lc(fa(x)) == x) || (rc(fa(x)) == x)) ;
}
void reverse(int x){
    rv(x) ^= 1 ; swap(lc(x), rc(x)) ;
}
void _down(int x){
    if (rv(x)){
        rv(x) = 0 ;
        if (lc(x)) reverse(lc(x)) ;
        if (rc(x)) reverse(rc(x)) ;
    }
    if (tg(x)){
        if (lc(x)) vl(lc(x)) += tg(x), tg(lc(x)) += tg(x) ;
        if (rc(x)) vl(rc(x)) += tg(x), tg(rc(x)) += tg(x) ;
        tg(x) = 0 ;
    }
}
void rotate(int x){
    bool w = x == rc(fa(x)) ;
    int f1 = fa(x), f2 = fa(f1) ;
    if (nroot(f1))
        t[f2].son[f1 == rc(f2)] = x ;
    t[f1].son[w] = t[x].son[w ^ 1] ;
    fa( t[x].son[w ^ 1] ) = f1 ;
    fa(x) = f2 ; fa(f1) = x ;
    t[x].son[w ^ 1] = f1 ;
}
void splay(int x){
    int y = x ;
    stk[++ tp] = y ;
    while (nroot(y))
        stk[++ tp] = (y = fa(y)) ;
    while (tp) _down(stk[tp --]) ;
    while (nroot(x)){
        int f1 = fa(x) ;
        int f2 = fa(f1) ;
        if (nroot(f1)){
            if ((rc(f1) == x) == (rc(f2) == f1))
                rotate(f1) ; else rotate(x) ;
        }
        rotate(x) ;
    }
}
il void access(int x){
    int y = 0 ;
    for ( ; x ; x = fa(y = x))
        splay(x), rc(x) = y ;
}
il void make_root(int x){
    access(x) ;
    splay(x) ; reverse(x) ;
}
il int find_root(int x){
    access(x) ; splay(x) ;
    while(lc(x)) x = lc(x) ;
    return x ;
}
il void merge(int x, int y){
    make_root(x) ;
    access(y) ; splay(y) ;
}
il void link(int x, int y){
    fa(x) = y ;
}
il void cut(int x, int y){
    merge(x, y) ;
    fa(x) = t[y].son[0] = 0 ;
}
il void Input(int mk) {
    len = strlen(s) ;
    for (int j = 0 ; j < len ; ++ j)
        mk = (mk * 131 + j) % len, swap(s[j], s[mk]) ;
}
struct SAM{
    int size ;
    int last ;
    int len[M] ;
    int fal[M] ;
    int trans[M][2] ;
    void Init(){
        last = ++ size ;
    }
    void Ins(int x){
        int np = ++ size ;
        int q, nq, p = last ;
        len[last = np] = len[p] + 1 ;
        while (p && !trans[p][x])
            trans[p][x] = np, p = fal[p] ;
        if (!p){
            fal[np] = 1 ;
            link(np, 1), merge(1, np) ;
            vl(np) ++, tg(np) ++ ; return ;
        }
        q = trans[p][x] ;
        if (len[q] == len[p] + 1){
            fal[np] = q ;
            link(np, q), merge(1, np) ;
            vl(np) ++, tg(np) ++ ; return ;
        }
        nq = ++ size ;
        cut(fal[q], q) ;
        fal[nq] = fal[q] ;
        link (q, nq) ;
        link (np, nq) ;
        link (nq, fal[q]) ;
        len[nq] = len[p] + 1 ;
        fal[q] = fal[np] = nq ;
        splay(q) ; vl(nq) = vl(q) ;
        memcpy(trans[nq], trans[q], 8) ;
        while (p && trans[p][x] == q)
            trans[p][x] = nq, p = fal[p] ;
        merge(1, np), vl(np) ++, tg(np) ++ ;
    }
}S ;
int main(){
    cin >> m ;
    scanf("%s", s + 1) ;
    len = strlen(s + 1) ; S.Init() ;
    for (int i = 1 ; i <= len ; ++ i) S.Ins(s[i] - 'A') ;
    while (m --){
        scanf("%s", o + 1) ;
        scanf("%s", s), Input(ans) ;
        if (o[1] == 'A'){
            for (int i = 0 ; i < len ; ++ i)
                S.Ins(s[i] - 'A') ; //, cout << i << endl ;
        }
        else{
            int rt = 1 ;
            for (int i = 0 ; i < len ; ++ i){
                rt = S.trans[rt][s[i] - 'A'] ;
                if (!rt) break ;
            }
            if (!rt) res = 0 ;
            else splay(rt), res = vl(rt) ;
            printf("%d\n", res) ; ans = ans ^ res ;
        }
    }
    return 0 ;
}
```




---

## 作者：一扶苏一 (赞：14)

##  【SAM & LCT】【P5212】 SubString

### Description

给定一个字符串 $s$，要求支持动态在 $s$ 后增加字符和查询某串 $t$ 的出现次数，强制在线。

$s$ 最终长度不超过 $6 \times 10^5$。询问串长度之和不超过 $6 \times 10^3$。

### Analysis

考虑对 $s$ 建出 SAM，则查询时把查询串放在 SAM 上跑，求终止节点的在 parent 树上的 right 集合大小。

当动态增加字符时，需要在 parent 树上加边、删边，查询时需要查询子树和，可以用 LCT 维护上述操作。

其他题解都是在加入一个节点时，对其到根的链进行链加，但事实上 LCT 是可以直接维护子树信息的。具体的，对每个节点维护其虚子树的信息和 $si$，以及其在 splay 上的子树中的节点以及其虚子树信息和 $sr$。设 一个节点自身的权值为 $k$，$si + sr + k= ss$，则上述关系可以表示为

$$si_u = \sum\limits_{v \not \in \operatorname{children}(u)}^{\operatorname{fa}(v) = u} ss_v$$

$$sr_u = \sum\limits_{v \in \operatorname{subtree(u)}} si_v + k_v = \sum\limits_{v \in \operatorname{children(u)}} ss_v$$

其中 $\operatorname{children}(u)$ 表示 $u$ 在 splay 上的直接孩子，$\operatorname{fa}(v)$ 表示 $v$ 的父节点，$\operatorname{subtree}(u)$ 表示 $u$ 在 splay 上的子树。

那么我们发现，当需要查询 $u$ 在 parent 树上的子树信息时，只需要在 LCT 中提取 $u$ 到根的路径 `access(u)`（这里是为了保证 $u$ 在 parent 树上的子节点全部成为虚子树），然后把 $u$ 转到根，求其虚子树信息和+自身信息即可。

当然，在这里需要注意的是 access 操作时，因为修改了其虚实子树，所以要修改一下对应节点的 $si$ 和 $sr$ 值。同样在加边删边时，也要注意修改父节点的对应虚子树信息和。

### Code

由于这是一棵有根树，我们插入的时候不需要 makeroot 就能保证不会存在环，所以不需要 makeroot 操作，当然也就不需要 pushdown 操作，码量相对于其他 LCT 题目要小不少。

```cpp
namespace Fusu {

const int maxt = 2;
const int maxn = 1200005;

void Init();
void Solve();

void Main() {
  Init();
  Solve();
}

struct Node {
  int len, si, sr, ss, sz;
  Node *fail, *fa;
  Node *trans[2], *ch[2];

  void pushup() {
    sr = 0;
    for (auto u : ch) if (u != nullptr) {
      sr += u->ss;
    }
    ss = si + sr + sz;
  }
  
  inline int GetSon() { return fa->ch[1] == this; }
  inline bool IsRot() { return (fa == nullptr) || (fa->ch[GetSon()] != this); }

  void rotate(const int x) {
    auto nt = ch[x];
    ch[x] = nt->ch[x ^ 1];
    nt->ch[x ^ 1] = this;
    if (ch[x]) ch[x]->fa = this;
    if (!IsRot()) fa->ch[GetSon()] = nt;
    nt->fa = fa; fa = nt;
    pushup(); nt->pushup();
  }

  void splay() {
    while (!IsRot()) {
      if (fa->IsRot()) {
        fa->rotate(GetSon());
      } else {
        int k1 = GetSon(), k2 = fa->GetSon();
        if (k1 == k2) {
          fa->fa->rotate(k2);
          fa->rotate(k1);
        } else {
          fa->rotate(k1);
          fa->rotate(k2);
        }
      }
    }
  }
};
Node Mem[maxn], *pool = Mem + 1, *rot = Mem;
inline Node* New(const int x) {
  pool->len = x;
  return pool++;
}

void access(Node *u) {
  for (Node *v = nullptr; u; u = (v = u)->fa) {
    u->splay();
    if (u->ch[1]) u->si += u->ch[1]->ss;
    if (v) u->si -= v->ss; 
    u->ch[1] = v;
    u->pushup();
  }
}


void link(Node *const u, Node *const v) {
  access(u);
  u->splay();
  v->fa = u;
  u->si += v->ss;
  u->pushup();
}

void cut(Node *const u, Node *const v) {
  access(v);
  v->splay();
  v->ch[0]->fa = nullptr;
  v->ch[0] = nullptr;
  v->pushup();
}

void extend(const int x) {
  static Node *lst = rot;
  auto p = lst, np = New(lst->len + 1);
  np->sz = np->ss = 1; lst = np;
  while (p && (p->trans[x] == nullptr)) {
    p->trans[x] = np;
    p = p->fail;
  }
  if (p == nullptr) {
    link(np->fail = rot, np);
  } else {
    auto q = p->trans[x];
    if (q->len == (p->len + 1)) {
      link(np->fail = q, np);
    } else {
      auto nq = New(p->len + 1);
      for (int i = 0; i < maxt; ++i) nq->trans[i] = q->trans[i];
      link(nq->fail = q->fail, nq);
      cut(q->fail, q);
      link(q->fail = nq, q);
      link(np->fail = nq, np);
      while (p && p->trans[x] == q) {
        p->trans[x] = nq;
        p = p->fail;
      }
    }
  }
}

int q;
char s[maxn];
void Init() {
  qr(q);
  int n = qrs(s + 1);
  for (int i = 1; i <= n; ++i) {
    extend(s[i] - 'A');
  }
}

void missyzy(const int n, int mk) {
  for (int i = 0; i < n; ++i) {
    mk = (mk * 131 + i) % n;
    std::swap(s[i], s[mk]);
  }
}

void Solve() {
  static int mk;
  static char tp[50];
  while (q--) {
    qrs(tp); int n = qrs(s);
    missyzy(n, mk);
    if (tp[0] == 'A') {
      for (int i = 0; i < n; ++i) {
        extend(s[i] - 'A');
      }
    } else {
      auto u = rot;
      int ret = -1;
      for (int i = 0, x = s[i] - 'A'; i < n; x = s[++i] - 'A') {
        if (u->trans[x] == nullptr) {
          ret = 0;
          break;
        }
        u = u->trans[x];
      }
      if (ret == 0) {
        puts("0");
      } else {
        access(u);
        u->splay();
        int ret = u->si + u->sz;
        qw(ret, '\n');
        mk ^= ret;
      }
    }
  }
}

} // namespace Fusu
```



---

## 作者：PM250 (赞：5)

### 前置技能

0.重量平衡树（替罪羊树）,后缀数组

1.给定一个序列，比较两个元素的先后

**排名比较** $O(1)$

2.一个**带插入**的序列，比较两个元素的先后

**顺序查找？** $O(n)$

**比较排名？**

插入时以前驱和后继的排名的平均数作为自己的排名

添加0和正无穷两个虚拟节点

**排名比较** $O(1)$

3.给定一个后缀数组，比较两个后缀的先后

用SA数组求出每个后缀的排名， $O(1)$

4.给定一个**带插入（动态）**的后缀数组，比较两个后缀的先后

相当于在SA数组中动态插入一个后缀，排名由前驱后继的排名计算，同2. $O(1)$

### 概念

后缀平衡树是**动态的后缀数组**

支持的操作：

1.在字符串前插入字符c（相当于加入一个后缀）

2.在字符串前删除字符c（相当于删除一个后缀）

3.询问一个后缀在平衡树中的排名

4.询问一个字符串在平衡树中的排名

### 操作1

我们用$S_i$ 代表原串$S$从第$i$个字符开始的后缀

假设我们已经有了串$S$的后缀平衡树 

插入一个字母 $c$ 

则后缀 $cS$ 与任意一个后缀 $S_i$ 的大小关系可以用 $c$ 与 $S_i$ 的第一个字母的大小关系以及后缀 $S_1$ 与后缀 $S_{i+1}$ 的大小关系来表示 

前面是两个字符的比较 $O(1)$ 

后面原串后缀的大小关系可以在平衡树上维护排名 $O(1)$ 比较

tips：插入过程中维护前驱后继的排名

### 操作2

平衡树删除 $O(qlogn)$

### 操作3

平衡树基本操作 $O(qlogn)$

### 操作4

平衡树基本操作，比较改为字典序比较 $O(\sum |Q|logn)$

### 关于这题

后缀平衡树裸题~~就是不给用SAM~~

前缀转后缀

出现次数就是$rank(Q'inf')-rank(Q'\0')$

### 代码 
~~貌似挺快的也就rnk1~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;
typedef long long ll;
inline ll read()
{
    int ch=getchar(),f=1;
    ll ans=0;
    for(;ch<'0'||ch>'9';ch=getchar())
        if(ch=='-')f=0;
    for(;ch>='0'&&ch<='9';ch=getchar())
        ans=(((ans<<2)+ans)<<1)+(ch^'0');
    return f?ans:-ans;
}
int mask;
const int maxn=600005;
const ll inf=0x4000000000000000;
char q[maxn*5];
void decode(char *s,int msk=mask)
{
    int len=strlen(s);
    for(int j=0;j<len;++j)
    {
        msk=(msk*131+j)%len;
        char t=s[j];
        s[j]=s[msk];
        s[msk]=t;
    }
}
char s[maxn];
int len;
ll val[maxn];//每个位置的值，用于O(1)比较两个后缀的先后
int cnt,c[maxn][2],siz[maxn],st[maxn],top,rt;
inline void push_up(int x)
{
    siz[x]=c[x][0][siz]+c[x][1][siz]+1;
}

/****替罪羊删除****/
int uni(int x,int y)
{
    return (!x||!y)?(x+y):siz[x]>siz[y]?(c[x][1]=uni(c[x][1],y),push_up(x),x):(c[y][0]=uni(x,c[y][0]),push_up(y),y);
}
void del(int &x,int y)
{
    x^y?siz[x]--,del(c[x][val[y]>val[x]],y),0:x=uni(c[x][0],c[x][1]);
}
void dfs(int &x)
{
    if(x)dfs(c[x][0]),st[++top]=x,dfs(c[x][1]),x=0;
}
/****替罪羊重建****/
int reb(int l,int r,ll L,ll R)
{
    int mid=l+r>>1;
    int x=st[mid];
    siz[x]=r-l+1;
    val[x]=L+R>>1;
    if(l<mid)c[x][0]=reb(l,mid-1,L,val[x]);
    if(mid<r)c[x][1]=reb(mid+1,r,val[x],R);
    return x;
}

/****替罪羊插入****/
void ins(int &x,int y,ll L=0,ll R=inf,bool d=1)
{
    if(!x)
        x=y,c[x][0]=c[x][1]=0,siz[x]=1,val[x]=L+R>>1;
    else
    {
        siz[x]++;
        bool w=s[x]<s[y]||s[x]==s[y]&&val[x-1]<val[y-1];
        bool bad=d&&siz[c[x][w]]>siz[x]*0.7+5;
        ins(c[x][w],y,w?val[x]:L,w?R:val[x],d&&!bad);
        if(bad)top=0,dfs(x),x=reb(1,top,L,R);
    }
}
int rnk(char *q,int len)
{
    int ans=0;
    for(int x=rt;x;)
    {
        bool w=0;
        for(int i=0;i<len;++i)
            if(q[i]^s[x-i])
        {
            w=q[i]>s[x-i];
            break;
        }
        if(w)ans+=c[x][0][siz]+1;
        x=c[x][w];
    }
    return ans;
}
int main()
{
    int Q=read();
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=1;i<=len;++i)
        ins(rt,i);
    while(Q--)
    {
        char opt[9];
        scanf("%s",opt);
        if(*opt=='A')
        {
            scanf("%s",q+1);
            decode(q+1);
            int l=strlen(q+1);
            for(int i=1;i<=l;++i)
            {
                s[len+i]=q[i];
                ins(rt,len+i);
            }
            len+=l;
        }
        else if(*opt=='D')
        {
            int l=read();
            for(int i=1;i<=l;++i)
            {
                s[len]=0;
                del(rt,len);
                --len;
            }
        }
        else
        {
            scanf("%s",q+1);
            decode(q+1);
            int l=strlen(q+1);
            for(int i=1,j=l;i<j;++i,--j)
                swap(q[i],q[j]);
            int ans=-rnk(q+1,l+1);
            q[l+1]='Z'+1;
            ans+=rnk(q+1,l+1);
            printf("%d\n",ans);
            mask^=ans;
        }
        //printf("%s\n",s+1);
    }
    //cout << "Hello world!" << endl;
    return 0;
}

```

#### 参考资料:

[后缀平衡树学习笔记](https://blog.csdn.net/liutian429073576/article/details/53056038)

---

## 作者：Purple_wzy (赞：4)

题面：https://www.lydsy.com/JudgeOnline/problem.php?id=2555

题解：

如果没有修改操作，这就是一道SAM模板题。

有了修改操作后，发现fail树可能会有断边的过程，

不难想到使用LCT维护fail树。

每次加边时，需要将贡献也一并加入LCT的节点中，

查询时，找到对应节点，将其splay到根，此时的val就是答案。

注意：

1.splay时记得要pushdown;

2.是大写字母；

3.数组要开到$1.2e6$。

时间复杂度：$O(n+Qlogn)$

代码：
```
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
char c[3030000];
int n,m,Q;
namespace LCT{
	int fa[1202000],ch[1202000][2],laz[1202000],w[1202000];
	int st[1202000];
	IN nroot(int x){
		return (ch[fa[x]][0]==x)||(ch[fa[x]][1]==x);
	}
	IN get(int x){
		return ch[fa[x]][1]==x;
	}
	I add(int x,int val){
		if(!x)return;laz[x]+=val;w[x]+=val;
	}
	I push_down(int x){
		add(ch[x][0],laz[x]);add(ch[x][1],laz[x]);
		laz[x]=0;
	}
	I rotate(int x){
		re y=fa[x],z=fa[y],dir=get(x);
		if(nroot(y))ch[z][get(y)]=x;fa[x]=z;
		ch[y][dir]=ch[x][dir^1];fa[ch[x][dir^1]]=y;
		ch[x][dir^1]=y;fa[y]=x;
	}
	I splay(int x){
		re y=x,z=0;st[++z]=y;
		while(y)st[++z]=y=fa[y];
		while(z)push_down(st[z--]);
		while(nroot(x)){
			y=fa[x],z=fa[y];
			if(nroot(y))rotate((get(x)^get(y))?x:y);
			rotate(x);
		}
	}
	I access(int x){
		for(re y=0;x;x=fa[y=x])splay(x),ch[x][1]=y;
	}
	I link(int x,int y){
		fa[x]=y;access(y);splay(y);add(y,w[x]);
	}
	I cut(int x,int y){
		access(x);splay(x);add(ch[x][0],-w[x]);
		fa[ch[x][0]]=0;ch[x][0]=0;
	}
};
namespace SAM{
	int len[1202000],ch[1202000][27],link[1202000],tot,las,p,q,cle,cur;
	I init(){tot=las=1;}
	I add(int x){
		cur=++tot;len[cur]=len[las]+1;p=las;las=cur;LCT::w[cur]=1;
		while(p&&!ch[p][x])ch[p][x]=cur,p=link[p];
		if(!p){link[cur]=1;LCT::link(cur,1);return;}
		q=ch[p][x];
		if(len[p]+1==len[q]){link[cur]=q;LCT::link(cur,q);return;}
		cle=++tot;len[cle]=len[p]+1,link[cle]=link[q];LCT::link(cle,link[cle]);
		memcpy(ch[cle],ch[q],sizeof(ch[q]));
		LCT::cut(q,link[q]);link[q]=cle;LCT::link(q,link[q]);link[cur]=cle;LCT::link(cur,cle);
		while(p&&ch[p][x]==q)ch[p][x]=cle,p=link[p];
	}
	I insert(){F(i,0,n-1)add(c[i]-'A'+1);}
	I ques(){
		p=1;
		F(i,0,n-1){
			if(!ch[p][c[i]-'A'+1]){
				printf("0\n");return;
			}
			p=ch[p][c[i]-'A'+1];
		}
		LCT::splay(p);
		printf("%d\n",LCT::w[p]);m^=LCT::w[p];
	} 
};
I getit(int x){
	scanf("%s",c);n=strlen(c);
	F(i,0,n-1){
		x=(x*131+i)%n;
		swap(c[i],c[x]);
	}
}
int main(){
	read(Q);m=0;
	scanf("%s",c);
	n=strlen(c);
	SAM::init();
	SAM::insert();
	while(Q--){
		scanf("%s",c+1);
		if(c[1]=='A'){
			getit(m);SAM::insert();
		}
		else{
			getit(m);SAM::ques();
		}
	}
	return 0;
}
```
更好的阅读体验：https://www.cnblogs.com/Purple-wzy/

---

## 作者：asuldb (赞：4)

[题目](https://www.luogu.org/problemnew/show/P5212)

真是一道非常好的码农题，$SAM+LCT$

看到查询子串出现次数我们就能想到这是一个$SAM$

看到动态往后加入字符串我们就可以想到需要$LCT$来维护子树和

由于$LCT$并不是很方便维护子树，所以每次加入一个点的时候只需要把根到这个点的路径上的点权加一就好了

查询在$SAM$上匹配出位置，差一个单点权值就可以了

别忘了加入$clone$节点的时候要继承儿子的点权

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#define maxn 1200005
#define re register
#define LL long long
char S[3000005],opt[10];
std::string chars;
int Q,mask,ans,lst=1,cnt=1;
int tag[maxn],rev[maxn],fa[maxn],ch[maxn][2],s[maxn],st[maxn];
inline int nroot(int x) {return ch[fa[x]][1]==x||ch[fa[x]][0]==x;}
void Gets(int mask) {
    scanf("%s",S);
    chars=S;
    for (int j=0;j<chars.length();j++) {
        mask=(mask*131+j)%chars.length();
        char t=chars[j];
        chars[j]=chars[mask];
        chars[mask]=t;
    }
}
inline void pushdown(int x) {
	if(rev[x]) {
		if(ch[x][0]) rev[ch[x][0]]^=1,std::swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
		if(ch[x][1]) rev[ch[x][1]]^=1,std::swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
		rev[x]=0;
	}
	if(tag[x]) {
		if(ch[x][0]) s[ch[x][0]]+=tag[x],tag[ch[x][0]]+=tag[x];
		if(ch[x][1]) s[ch[x][1]]+=tag[x],tag[ch[x][1]]+=tag[x];
		tag[x]=0;
	}
}
inline void rotate(int x) {
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][k^1];
	if(nroot(y)) ch[z][ch[z][1]==y]=x;
	ch[x][k^1]=y,ch[y][k]=w;
	fa[w]=y,fa[y]=x,fa[x]=z;
}
inline void splay(int x) {
	int y=x,top=0;
	st[++top]=x;
	while(nroot(y)) st[++top]=fa[y],y=fa[y];
	while(top) pushdown(st[top--]);
	while(nroot(x)) {
		int y=fa[x];
		if(nroot(y)) rotate((ch[fa[y]][1]==y)^(ch[y][1]==x)?x:y);
		rotate(x);
	}
}
inline void access(int x) {
	for(re int y=0;x;y=x,x=fa[x])
		splay(x),ch[x][1]=y;
}
inline void makeroot(int x) {
	access(x);splay(x),rev[x]^=1;std::swap(ch[x][0],ch[x][1]);
}
inline void split(int x,int y) {
	makeroot(x);access(y);splay(y);
}
inline void link(int x,int y) {
	fa[x]=y;
}
inline void cut(int x,int y) {
	split(x,y);ch[y][0]=fa[x]=0;
}
struct Suffix_Automata {
	int len[maxn],fa[maxn],son[maxn][26];
	inline void ins(int c) {
		int p=++cnt,f=lst; lst=p;
		len[p]=len[f]+1;
		while(f&&!son[f][c]) son[f][c]=p,f=fa[f];
		if(!f) {fa[p]=1;link(p,fa[p]);split(1,p);tag[p]++;s[p]++;return;}
		int x=son[f][c];
		if(len[f]+1==len[x]) {fa[p]=x;link(p,fa[p]);split(1,p);tag[p]++;s[p]++;return;}
		int y=++cnt;
		len[y]=len[f]+1,fa[y]=fa[x],cut(fa[x],x),fa[x]=fa[p]=y;
		link(x,fa[x]),link(p,fa[p]),link(y,fa[y]);
		splay(x);s[y]=s[x];
		for(re int i=0;i<26;i++) son[y][i]=son[x][i];
		while(f&&son[f][c]==x) son[f][c]=y,f=fa[f];
		split(1,p);tag[p]++;s[p]++;
	}
	inline void add() {
		Gets(mask);
		int len=chars.length();
		for(re int i=0;i<len;i++) ins(chars[i]-'A');
	}
	inline int check() {
		Gets(mask);
		int len=chars.length();
		int now=1;
		for(re int i=0;i<len;i++) {
			now=son[now][chars[i]-'A'];
			if(!now) break;
		}
		if(!now) return 0;
		splay(now);return s[now];
	}
}SAM;
int main()
{
	scanf("%d",&Q);
	scanf("%s",S+1);
	int len=strlen(S+1);
	for(re int i=1;i<=len;i++) SAM.ins(S[i]-'A');
	while(Q--) {
		scanf("%s",opt);
		if(opt[0]=='A') SAM.add();
		else {
			ans=SAM.check();
			mask^=ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Caicz (赞：1)

#### 前言

辛酸的调题过程：

前夜
20:30 -> 82pts ，        21:50 -> 0pts   
当日
14:31 -> 27pts ，        14:52 -> 91pts ，       15:28 -> 100pts

#### 题意

给你一个字符串，要求支持以下两个操作

1. 在当前字符串后面插入一个字符串 S
2. 查询字符串 S 在当前字符串中出现了几次

强制在线，$|S|\le6\times10^5,\quad Q\le10^4$

#### 题解

如果没有强制在线，可以将所有插入字符串按顺序加入后，跑一遍 $SAM/SA$ ,对于每个询问划定区间查询即可

但如果强制在线呢？还是考虑 $SAM$ ，对于用 $SAM $建成的$parent$ 树来说，一个节点的子树和即为其答案

一般来说，$parent$ 树都是在我们跑完 $SAM$ 之后构建，我们考虑在 $SAM$ 插入字符的过程中进行构建，很显然我们只需要支持删边和加边的操作，可以用 $lct$ 简单维护

对于每个点的子树和，不难看出这其实是一个链加的过程  
即将 $x$ 连为 $y$ 的子树，直接将 $y->root(y)$ 全部加上 $si(x)$  
删边操作也是同理
$$
\large\color{grey}{\text{Talk is cheap , show you the code}}
$$


#### 代码

```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1200005;
const int inf=0x3f3f3f3f;
int m,mask;
char s[maxn];

struct link_cut_tree
{
	int st[maxn];
	struct node
	{
		int ch[2],fa;
		int si,tag;
	}tr[maxn];
	inline bool pd(int x){return tr[tr[x].fa].ch[0]==x||tr[tr[x].fa].ch[1]==x;}
	inline void add(int x,int val){if(!x)return;tr[x].si+=val,tr[x].tag+=val;}
	inline void pushdown(int x){if(tr[x].tag){add(tr[x].ch[0],tr[x].tag),add(tr[x].ch[1],tr[x].tag),tr[x].tag=0;}}
	inline void rotate(int x)
	{
		int y=tr[x].fa,z=tr[y].fa,k=tr[y].ch[1]==x;
		if(pd(y))tr[z].ch[tr[z].ch[1]==y]=x;tr[y].ch[k]=tr[x].ch[k^1];tr[x].fa=z;
		if(tr[x].ch[k^1])tr[tr[x].ch[k^1]].fa=y;tr[x].ch[k^1]=y;tr[y].fa=x;
	}
	inline void splay(int x)
	{
		int y=x,z=0;while(y)st[++z]=y,y=tr[y].fa;while(z)pushdown(st[z--]);
		while(pd(x)){y=tr[x].fa,z=tr[y].fa;if(pd(y))rotate((tr[z].ch[1]==y)^(tr[y].ch[1]==x)?x:y);rotate(x);}
	}
	inline void access(int x){for(register int y=0;x;x=tr[y=x].fa)splay(x),tr[x].ch[1]=y;}
	inline void link(int x,int y){splay(x),tr[x].fa=y;access(y),splay(y),add(y,tr[x].si);}
	inline void cut(int x){access(x),splay(x),add(tr[x].ch[0],-tr[x].si),tr[tr[x].ch[0]].fa=0,tr[x].ch[0]=0;}
}supccz;

struct suffix_automaton
{
	int la=1,tot=1;
	struct node
	{
		int fa,len,ch[2];
	}tr[maxn];
	inline void insert(int x)
	{
		int p=la,u=++tot;supccz.tr[u].si=1;
		tr[u].len=tr[p].len+1;
		while(p&&!tr[p].ch[x])tr[p].ch[x]=u,p=tr[p].fa;
		if(!p)tr[u].fa=p|1,supccz.link(u,1);
		else
		{
			int q=tr[p].ch[x];
			if(tr[q].len==tr[p].len+1)tr[u].fa=q,supccz.link(u,q);
			else
			{
				int nu=++tot;tr[nu]=tr[q];
				supccz.cut(q),supccz.link(nu,tr[q].fa),supccz.link(u,nu),supccz.link(q,nu);	
				tr[nu].len=tr[p].len+1,tr[u].fa=tr[q].fa=nu;
				while(p&&tr[p].ch[x]==q)tr[p].ch[x]=nu,p=tr[p].fa;
			}
		}
		la=u;
	}
}ccz;
inline void decode(char *s,int mk,int len){for(register int i=0;i<len;++i){mk=(mk*131+i)%len,swap(s[i],s[mk]);}}
signed main(void)
{
	freopen("P5212.in","r",stdin);
	cin>>m;
	scanf("%s",s);
	int len=strlen(s);
	for(register int i=0;i<len;++i)ccz.insert(s[i]-'A');
	for(register int t,i=1;i<=m;++i)
	{
		scanf("%s",s);
		if(s[0]=='A')
		{
			scanf("%s",s);
			int len=strlen(s);decode(s,mask,len);
			for(register int i=0;i<len;++i)ccz.insert(s[i]-'A');
		}
		else
		{
			scanf("%s",s);
			int len=strlen(s),u=1;decode(s,mask,len);
			for(register int j=0;j<len;++j)
			{
				u=ccz.tr[u].ch[s[j]-'A'];
				if(!u)break;
			}
			if(u)supccz.splay(u);
			t=supccz.tr[u].si;
			mask^=t;
			printf("%d\n",t);
		}
	}
	return 0;
}

```



---

## 作者：yijan (赞：1)

为了可能更好的阅读体验，建议在 luogu 博客或者 [这里](https://www.yijan.co/p5212-substring/) 查看。

考虑如果不强制在线，我们可以建 SAM ，于是 SAM 一个点出现次数就是前缀树子树和。

如果强制在线，也就是我们得动态维护前缀树，一个简单想法就是拿 LCT 来维护前缀树。

于是我们需要写一个 LCT ，但是显然是不需要支持 `makeroot` 的。

同时我们还需要求子树和。可以在 LCT 上维护子树和，具体做法就是插入一个点后直接给这个点到根的链全部 `+c` 。这个东西是**不需要 `pushup` 的**，删除一个点就是一个点 `access` 后左子树内的点全部 `-c`（也就是它到根的路径 `-c`）即可。维护这些操作只需要一个 `+` tag即可。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 1300006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , m;
char ch[MAXN];

namespace LCT {
	int ch[MAXN][2] , fa[MAXN] , S[MAXN] , lz[MAXN];
	inline bool notroot( int x ) {
		return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
	}
	inline void add( int x , int c ) {
		if( x )
			lz[x] += c , S[x] += c;
	}
	inline void pd( int x ) {
		if( lz[x] ) {
			if( ch[x][0] ) add( ch[x][0] , lz[x] );
			if( ch[x][1] ) add( ch[x][1] , lz[x] );
			lz[x] = 0;
		}
	}
	inline void rotate( int x ) {
		int f = fa[x] , g = fa[f] , w = ch[fa[x]][1] == x;
		int wf = ch[g][1]==f , k = ch[x][w^1];
		if( notroot(f) ) ch[g][wf] = x; ch[f][w] = k , ch[x][w^1] = f;
		fa[f] = x , fa[k] = f , fa[x] = g;
	}
	void update( int x ) {
		if( notroot( x ) ) update( fa[x] );
		pd( x );
	}
	void splay( int x ) {
		update( x );
		int f , g;
		while( notroot( x ) ) {
			f = fa[x] , g = fa[f];
			if( notroot( f ) ) 
				rotate( (ch[f][0]==x)^(ch[g][0]==f) ? x : f );
			rotate( x );
		}
	}
	void ac( int x ) {
		for( int p = 0 ; x ; ( p = x , x = fa[x] ) ) 
			splay( x ) , ch[x][1] = p;
	}
	void link( int u , int v ) {
		fa[u] = v;
		ac( v ) , splay( v );
		add( v , S[u] );
	}
	void cut( int u ) { // cut the edge from u to par u
		ac( u ) , splay( u );
		add( ch[u][0] , -S[u] );
		fa[ch[u][0]] = 0;
		ch[u][0] = 0;
	}
}

struct SAM {
    int son[MAXN][26] , par[MAXN] , len[MAXN];
    int head[MAXN] , to[MAXN] , nex[MAXN] , ecn;
    int num[MAXN];
    int lst , cnt;
    void init( ) {
        // initialize
        lst = cnt = 1 , ecn = 0;
    }
    void ade( int u , int v ) {
        to[++ ecn] = v , nex[ecn] = head[u] , head[u] = ecn;
    }
    void addall( ) {
        for( int i = 1 ; i <= cnt ; ++ i ) ade( par[i] , i );
    }
    void ins( int x ) {
        using namespace LCT;
        int cur = ++ cnt;
        len[cur] = len[lst] + 1 , num[cur] = 1;
        S[cur] = 1;
        int p = lst;
        while( p && !son[p][x] ) son[p][x] = cur , p = par[p];
        if( !p ) par[cur] = 1 , link( cur , 1 );
        else {
            int q = son[p][x];
            if( len[q] == len[p] + 1 ) par[cur] = q , link( cur , q );
            else {
                int ct = ++ cnt;
                len[ct] = len[p] + 1 , par[ct] = par[q] , link( ct , par[q] );
                cut( q );
                memcpy( son[ct] , son[q] , sizeof son[q] );
                par[q] = par[cur] = ct , link( q , ct ) , link( cur , ct );
                for( ; son[p][x] == q ; p = par[p] ) son[p][x] = ct;
            }
        }
        lst = cur;
    }
    int wkr( char* ch , int u ) {
    	if( !u ) return 0;
    	if( ch[0] != 0 ) return wkr( ch + 1 , son[u][ch[0] - 'A'] );
    	else {
    		using namespace LCT;
    		splay( u );
    		return S[u];
		}
	}
} S ;

void decodeWithMask(char* s, int len , int mask) {
	for (int j = 0; j < len; j++ ) {
		mask = (mask * 131 + j) % len;
		char t = s[j];
		s[j] = s[mask];
		s[mask] = t;
	}
}

void solve() {
	cin >> m;
	scanf("%s",ch + 1);
	n = strlen( ch + 1 );
	S.init();
	rep( i , 1 , n ) 
		S.ins( ch[i] - 'A' );
	char op[10];
	int mask = 0 , ans = 0;
	while( m-- ) {
		scanf("%s",op);
		if( op[0] == 'A' ) {
			scanf("%s",ch + 1);
			n = strlen( ch + 1 );
			decodeWithMask( ch + 1 , n , mask );
			rep( i , 1 , n ) S.ins( ch[i] - 'A' );
		} else {
			
			scanf("%s",ch + 1);
			n = strlen( ch + 1 );
			decodeWithMask( ch + 1 , n , mask );
			printf("%d\n",ans = S.wkr( ch + 1 , 1 ) );
			mask ^= ans;
		}
	}
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}


```



---

## 作者：2018LZY (赞：1)

[更好的阅读体验戳这里哦~~](https://blog.csdn.net/qq_42886072/article/details/105185379)
# 前言
太久未打LCT了,样例又太菜了,让我调试得快去世了.
# 正题
首先,默认你会不强制在线且没有ADD的情况.~~(不会你来做这题干嘛)~~

做题的时候,第一眼居然想到树剖.
然鹅,树剖只能处理静态问题.

那能处理在线问题的且可能实现树上路径加的是啥呢?

没错,就是LCT.

先安利一个[模板](https://blog.csdn.net/qq_42886072/article/details/105181973).

然后LCT维护的东西也非常简单,就是一个子树加和自身点值.

主要看代码吧~~~:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar()
using namespace std;
const int N=2e6+10;

template<class o> void qr(o &x) {
	char c=gc; x=0; int f=1;
	while(!isdigit(c)){if(c=='-')f=-1; c=gc;}
	while(isdigit(c)) x=x*10+c-'0',c=gc;
	x*=f;
}
template<class o> void qw(o x) {
	if(x/10) qw(x/10);
	putchar(x%10+'0');
}
template<class o> void pr1(o x) {
	if(x<0)x=-x,putchar('-');
	qw(x); putchar(' ');
}
template<class o> void pr2(o x) {
	if(x<0)x=-x,putchar('-');
	qw(x); puts("");
}

namespace LCT {
	#define lc ch[0][x]
	#define rc ch[1][x]
	int ch[2][N],fa[N],ad[N],f[N];
	int sta[N],top;
	bool son(int x) {return x==ch[1][fa[x]];}
	bool isroot(int x) {return x!=ch[son(x)][fa[x]];}
	void pushdown(int x) {
		if(ad[x]) {
			int y=ad[x];
			ad[lc]+=y;
			f[lc]+=y;
			ad[rc]+=y;
			f[rc]+=y;
			ad[x]=0;
		}
	}
	void rotate(int x) {
		int y=fa[x],z=fa[y],c=son(x);
		ch[c][y]=ch[c^1][x]; if(ch[c][y]) fa[ch[c][y]]=y;
		fa[x]=z; if(!isroot(y)) ch[son(y)][z]=x;
		ch[c^1][x]=y; fa[y]=x;
	}
	void splay(int x) {
		sta[top=1]=x;
		for(int i=x;!isroot(i);i=fa[i]) sta[++top]=fa[i];
		while(top) pushdown(sta[top--]);
		for(int y=fa[x];!isroot(x);rotate(x),y=fa[x])
			if(!isroot(y)) son(x)^son(y)?rotate(x):rotate(y);
	}
	void access(int x) {
		for(int y=0;x;x=fa[y=x])
			splay(x),rc=y;
	}
	void cut(int x) {
		access(x); splay(x);
		f[lc]-=f[x]; ad[lc]-=f[x]; 
		fa[lc]=0; lc=0;
	}
	void link(int x,int y) {
		access(y); splay(y); access(x);
		ch[1][y]=x; fa[x]=y;
		ad[y]+=f[x]; f[y]+=f[x]; f[x]=0;
	}
	int calc(int x) {access(x); splay(x); return f[x];}
}

namespace SAM {
	int last=1,tot=1;
	struct node{int fa,len,v[2];}tr[N];
	void add(int c) {
		int p=last,x=last=++tot; tr[x].len=tr[p].len+1;
		for(	;p&&!tr[p].v[c];p=tr[p].fa) tr[p].v[c]=x;
		if(!p) tr[x].fa=1;
		else {
			int q=tr[p].v[c],y;
			if(tr[p].len+1==tr[q].len) tr[x].fa=q;
			else {
				tr[y=++tot]=tr[q];
				tr[y].len=tr[p].len+1;
//				LCT::f[y]=LCT::calc(q);这句话是错误的,可是加了居然还有81分. 
				LCT::link(y,tr[y].fa);
				LCT::cut(q);//隔断q与其父亲的联系 
				tr[q].fa=tr[x].fa=y;
				LCT::link(q,y);
				for(	;p&&tr[p].v[c]==q;p=tr[p].fa) tr[p].v[c]=y;
			}
		}
		LCT::f[x]=1;
		LCT::link(x,tr[x].fa);
	}
}

char op[10],s[N];
int m,n,ans;

void decodeWithMask(int mask) {
	scanf("%s",s);
	m=strlen(s);
	for (int j = 0; j < m; j++) {
		mask = (mask * 131 + j) % m;
		swap(s[mask],s[j]);
	}
}
int mask;


int main() {
	qr(n); scanf("%s",s);
	for(int i=0;s[i];i++) SAM::add(s[i]-'A');
	while(n--) {
		scanf("%s",op);
		decodeWithMask(mask);
		if(op[0]=='A') 
			for(int i=0;s[i];i++) 
				SAM::add(s[i]-'A');
		else {
			int p=1;
			for(int i=0;s[i]&&p;i++) p=SAM::tr[p].v[s[i]-'A'];
			if(p)ans=LCT::calc(p);
			else ans=0;
			mask^=ans;
			pr2(ans);
		}
	}
	return 0;

```


---

## 作者：Infiltrator (赞：1)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P5212)

------------

# Solution

动态加入字符就用$SAM$，发现答案就是一个点的子树的$siz$之和，所以需要动态维护子树和，上$LCT$。

$lCT$上每个节点，$siz$表示$Splay$上大小，$lsiz$表示虚子树大小，修改$Update$、$Access$、$Link$函数进行修改即可。

最后答案就是$Splay$上深度比它大的节点的$siz$之和加上它的虚子树大小，如果它是字符串的前缀，再加一。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1200050;
const int INF = 999999999;

int fa[N], son[N][26], last = 1, cnt = 1, len[N], rev[N], n, mask, ans;

char s[3000050];

struct LCT
{
	int son[2], siz, lsiz, fa, v;
} tr[N + 50];

bool Is(int x)
{
	return tr[tr[x].fa].son[1] != x && tr[tr[x].fa].son[0] != x;
}

int Get(int x)
{
	return tr[tr[x].fa].son[1] == x;
}

void Rv(int x)
{
	rev[x] ^= 1;
	swap(tr[x].son[0], tr[x].son[1]);
	return;
}

void Pushdown(int x)
{
	if (rev[x])
	{
		if (tr[x].son[0]) Rv(tr[x].son[0]);
		if (tr[x].son[1]) Rv(tr[x].son[1]);
		rev[x] = 0;
		return;
	}
}
void Update(int x)
{
	tr[x].siz = tr[tr[x].son[0]].siz + tr[tr[x].son[1]].siz + tr[x].lsiz + tr[x].v;
	return;
}

void Rotate(int x)
{
	int f = tr[x].fa, p = tr[f].fa, d = Get(x);
	if (!Is(f)) tr[p].son[Get(f)] = x;
	tr[x].fa = p;
	tr[f].son[d] = tr[x].son[d ^ 1];
	if (tr[f].son[d]) tr[tr[f].son[d]].fa = f;
	tr[x].son[d ^ 1] = f;
	tr[f].fa = x;
	Update(f); 
	Update(x);
	return;
}//旋转，记得判断父亲是不是splay的根 

void Calc(int x)
{
	if (!Is(x)) Calc(tr[x].fa);
	Pushdown(x);
	return;
}//递归处理标记 

void Splay(int x)
{
	Calc(x);
	while (!Is(x))
	{
		int f = tr[x].fa;
		if (!Is(f))
			Get(f) ^ Get(x) ? Rotate(x) : Rotate(f);
		Rotate(x);
	}
	return;
}

void Access(int x)
{
	int p = 0;
	while (x)
	{
		Splay(x);
		tr[x].lsiz += tr[tr[x].son[1]].siz - tr[p].siz;
		tr[x].son[1] = p;
		Update(x);
		p = x;
		x = tr[x].fa;
	}
	return;
}

void Makeroot(int x)
{
	Access(x);
	Splay(x);
	Rv(x); 
	return;
}

int Findroot(int x)
{
	Access(x);
	Splay(x);
	while (tr[x].son[0]) Pushdown(x), x = tr[x].son[0];
	Splay(x);
	return x;
}

void Link(int u, int v)
{
	Makeroot(u);
	if (Findroot(v) == u) return;
	tr[u].fa = v; tr[v].lsiz += tr[u].siz;
	Update(v);
	return;
}

void Cut(int u, int v)
{
	Makeroot(u);
	if (Findroot(v) != u || tr[v].fa != u || tr[v].son[0]) return;
	tr[u].son[1] = tr[v].fa = 0;
	Update(u);
	return;
}

int Askk(int x)
{
	Makeroot(1); Access(x); Splay(x);
	return tr[x].lsiz + tr[x].v + tr[tr[x].son[1]].siz;
}

void Init(int x)
{
	tr[x].siz = tr[x].v = 1;
	return;
}

void Change(int x, int y)
{
	if (fa[x]) Cut(x, fa[x]);
	Link(x, fa[x] = y);
	return;
}

void Insert(int c)
{
	int p = last, ne = last = ++cnt;
	len[ne] = len[p] + 1; Init(ne);
	while (p && !son[p][c]) son[p][c] = ne, p = fa[p];
	if (!p) { Change(ne, 1); return; }
	int q = son[p][c];
	if (len[q] == len[p] + 1) { Change(ne, q); return; }
	int sp = ++cnt;
	for (int i = 0; i < 26; i++) son[sp][i] = son[q][i];
	len[sp] = len[p] + 1;
	Change(sp, fa[q]);
	Change(q, sp); Change(ne, sp);
	while (p && son[p][c] == q) son[p][c] = sp, p = fa[p];
	return;
}

void Work()
{
	scanf("%s", s); n = strlen(s);
//	return;
	int rec = mask;
	for (int i = 0; i < n; i++)
	{
		rec = (rec * 131 + i) % n;
		swap(s[rec], s[i]);
	}
	return;
}

void Ask()
{
	int now = 1, ans = 0;
	Work();
	for (int i = 0; i < n && now; i++) now = son[now][s[i] - 'A'];
	if (!now) puts("0");
	else printf("%d\n", ans = Askk(now));
	mask ^= ans;
	return;
}

void Add()
{
	Work();
	for (int i = 0; i < n; i++) Insert(s[i] - 'A');
	return;
}

int main()
{
	int t;
	char st[10];
	scanf("%d", &t);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) Insert(s[i] - 'A');
	while (t--)
	{
		scanf("%s", st + 1);
		if (st[1] == 'Q') Ask();
		else Add();
	}
	return 0;
}
```

---

