# [BJWC2018] Border 的四种求法

## 题目背景

Scape 一到机房，所有做题的人便都看着他笑，有的叫道，“Scape，你一定又被标准分倍杀了！”他不回答，对柜里说，“测两个程序，看一眼成绩单。”便拷出两个程序。他们又故意的高声嚷道，“你怎么欧拉回路和逆序对都WA了！”……

## 题目描述

Scape 知道，以上的故事只是 OI 生涯里的一个意外，为了证明自己，他决定教你 $\text{Border}$ 的四种求法。

给一个小写字母字符串 $S$，$q$ 次询问每次给出 $l,r$ ，求 $s_{l\ldots r}$ 的 $\text{Border}$。

$\text{Border}$：对于给定的串 $s$，最大的 $i$ 使得 $s_{1\ldots i} = s_{|s|-i+1\ldots |s|}$。$|s|$ 为 $s$ 的长度。

## 说明/提示

对于 $30%$ 的数据， $n,q\leq 1000$ 。

对于 $50%$ 的数据， $n,q\leq 2\times 10^4$ 。

对于另外 $30\%$ 的数据，答案至少为 $r-l+1$ 的一半。

对于 $100\%$ 的数据， $n,q\leq 2\times 10^5$ 。

## 样例 #1

### 输入

```
abbabbaa
3
1 8
1 7
2 7```

### 输出

```
1
4
3```

# 题解

## 作者：_sys (赞：65)

## 子串周期查询

本文介绍了字符串结构相关的若干性质与能够在 $O(n\log n)$ 预处理，$O(\log n)$ 询问子串所有周期的算法。

后文会证明子串的所有周期能够通过特殊的形式表示，所以输出不会成为瓶颈。

***

#### 符号定义。

字符串：$s_{1\ldots n}$。串长为 $|s|$。

子串：$s_{[l,r]}$。

前缀 $pre(s, i) = s_{1, i}$。后缀 $suf(s, i)=s_{[|s|-i+1,|s|]}$。

***

#### 周期和 $\text{border}$。

若 $0< p \leq |s|$，对于 $1\leq i\leq |s| - p$ 有 $s_i=s_{i+p}$，就称 $p$ 为 $s$ 的一个周期，最小周期写作 $per(u)$。

若 $0\leq r < |s|$，$pre(s, r) = suf(s, r)$，就称 $pre(s, r)$ 是 $s$ 的 $\text{border}$。

**本文所述 $\text{border}$ 定义与原题有差别。**

一个显然的结论：$s_{1..k}$ 为 $s$ 的 $\text{border}\rightleftharpoons|s| - k$ 为 $s$ 的周期。

$\textbf{Weak Periodicity Lemma}$：若 $p$ 和 $q$ 是 $s$ 的周期，$p+q\leq |s|$，则 $\gcd(p, q)$ 也是 $s$ 的周期。

证明：令 $d=q-p\ (q > p)$， $i - p < 0$ 和 $i + q \leq |s|$ 至少有一个成立，于是要么得到 $s_i=s_{i-p}=s_{i-p+q}=s_d$ 要么得到 $s_i=s_{i+q}=s_{i+q-p}=s_d$。

于是 $d$ 和 $p$ 都是 $s$ 的周期，$d+p\leq |s|$，发现这是一个更相减损的过程，最后便会得到 $\gcd(p, q)$ 也为 $s$ 的周期。

$\textbf{Periodicity Lemma}$：若 $p$ 和 $q$ 是 $s$ 的周期，$p+q-\gcd(p, q)\leq |s|$，则 $\gcd(p, q)$ 也是 $s$ 的周期。

***

#### 字符串匹配

熟知的字符串匹配算法有 $\text{KMP}$。

其中 $fail_i$ 表示了 $s_{1,i}$ 的最长 $\text{border}$。

而很显然地 $\text{border}$ 的 $\text{border}$ 是 $\text{border}$。

所以一个字符串的所有 $\text{border}$ 便为 $fail_{|s|},fail_{fail_{|s|}},fail_{fail_{fail_{|s|}}},\ldots$。

**引理**：字符串 $u$ 和 $v$ 满足 $2|u| \geq |v|$，则 $u$ 在 $v$ 中的所有匹配位置组成一个等差数列，公差为 $per(u)$。

证明：只考虑匹配次数大于 $2$ 的情况。$2|u|\geq|v|$ 表明了两次匹配之间 $u$ 的位置必有交，而两次位置之差必定为 $u$ 的一个周期。

考虑第一次第二次和最后一次匹配，根据 $\textbf{Weak Periodicity Lemma}$ 可知 $\gcd$(第一次和第二次距离之差，第二次和最后一次距离之差) 为 $u$ 的周期。

通过简单的反证法可以得出它便是 $u$ 的最小周期。从而得到 $v$ 在此的结构为 $u$ 的最小周期的不断重复。

***

#### $\text{border}$ 的结构

**引理**：字符串 $s$ 的所有不小于 $\frac{|s|}2$ 的 $\text{border}$ 长度组成一个等差数列。

证明：有等价的说法为本质不同的长度小于 $\frac{|s|}2$ 的 $s$ 的周期至多只有一个。用简单的反证法与 $\textbf{Weak Periodicity Lemma}$ 可以得到。

现在我们将 $\text{border}$ 按照长度分类，分为 $[1, 2), [2, 4), [4, 8), \ldots [2^{k-1}, 2^k), [2^k, |s|)$ 这些集合。

对于长度相同的两个字符串 $u, v$，记 $PS(u, v)=\{k|pre(u, k)=suf(v, k)\}$。

记 $LargePS(u, v)=\{k\in PS(u, v)|k \geq \frac{|u|}2\}$。

则一个 $\text{border}$ 集合可以表示为 。$LargePS(pre(s, 2^i), suf(s, 2^i))$。

**引理**：$LargePS(u, v)$ 组成一个等差数列。

证明：$\text{border}$ 的 $\text{border}$ 是 $\text{border}$。对于这个集合里最长的 $\text{border}$ 而言，不小于它长度一半的 $\text{border}$ 长度组成一个等差数列。

**推论**：字符串 $s$ 的所有 $\text{border}$ 长度排序后可分成 $O(\log |s|)$ 段，每段是一个等差数列。

有了这个推论，可以尝试 [[WC2016]论战捆竹竿](https://www.luogu.com.cn/problem/P4156)。

***

#### 子串周期查询

* 给定字符串 $str$，每次询问 $str$ 一个子串的所有周期，用 $O(\log |str|)$ 个等差数列表示。

为方便起见，我们总是先求 $\text{border}$ 再推出周期。

我们设给定的子串为 $s$。

先考虑长度为 $[2^{i-1}, 2^i)$ 的集合。

假设 $\text{border}$ 为 $s_{1\ldots k}$，称他为 $t$。它合法当且仅当 $pre(t, 2^{i-1})=pre(s, 2^{i-1}), suf(t, 2^{i-1})=suf(s, 2^{i-1})$。

于是我们可以求出 $pre(s, 2^{i-1})$ 在 $pre(s, 2^i)$ 中的匹配位置与 $suf(s, 2^{i-1})$ 在 $suf(s, 2^i)$ 中的匹配位置的交集（移位后）。

而匹配位置为一个等差数列。我们只用求第一次匹配第二次匹配与最后一次匹配便可知道这个等差数列的首项、公差、项数。相当于实现一个 $succ(v, i)$ 和 $pred(v, i)$ 表示求 $v$ 从位置 $i$ 开始向前/后的第一次匹配位置。

问题变为 $str$ 中所有长度为 $2^{i-1}$ 的串有哪些位置能够与之匹配。

发现这就是倍增求后缀数组的时候把每一轮结束后的结果都记录下来。

最后是长度为 $[2^k, |s|)$ 的集合。做法其实一样，把上面所有 $2^i$ 替换为 $|s|$ 即可。

于是我们就有了 $O(n\log n)$ 预处理，单次询问 $O(log^2n)$ 的优秀做法。

如何优化？考虑将 $O(log^2n)$ 降低。这时瓶颈为求出等差数列、等差数列求交。

等差数列求交的优化肯定建立在字符串性质上。

**引理**：四个字符串满足 $|x_1|=|y_1|\geq|x_2|=|y_2|$，且 $x_1$ 在 $y_2y_1$ 中至少匹配 $3$ 次，$y_1$ 在 $x_1x_2$ 中至少匹配 $3$ 次，则 $x_1$ 和 $y_1$ 的最小周期相等。

证明：否则不妨设 $per(x_1) > per(y_1)$，考虑 $x_1$ 在 $y_2y_1$ 中的最右边一次匹配, 设它与 $y_1$ 的重叠部分为 $z$。

则 $|z| \geq 2per(x_1) > per(x_1) + per(y_1)$, 则 $z$ 拥有周期 $d = \gcd (per(x_1), per(y_1))|per(x_1)$, 于是 $d$ 也是 $x_1$ 的周期。但 $d < per(x_1)$, 矛盾。

同样，$y_1$ 在 $x_1x_2$ 里至少匹配 $3$ 次保证了 $per(x_1)<per(y_1)$ 矛盾。

所以我们合并的两个等差数列要么长度不足 $3$，要么公差相同。所以可以 $O(1)$ 合并。

求出等差数列的优化如下。

注意到在求 $succ(v, i)$ 的时候，$|v|$ 是二的幂，我们只在意起点在 $[i, i+|v|]$ 的匹配。

我们把原串按 $2^k$ 为段长分成若干段，考虑长度为 $2^k$ 的串的匹配信息。这样 $[i, i + |v|]$ 的匹配最多跨越两个段。我们可以分别得到这两个段的信息，直接合并即可。

如何维护匹配信息呢？我们发现最多只有 $O(n)$ 个长度为 $2^k$ 的串在原串中匹配了至少一次。而 $k$ 的取值有 $O(\log n)$ 种。所以匹配信息的空间是 $O(n\log n)$ 的。我们可以用 $\text{hashtable}$ 来解决。设 $h_{i,k}$ 表示 $S_{[i, i + 2^k]}$ 的哈希值，发现 $h_{[i, k]}$ 可以由 $h_{[i, k - 1]}$ 和 $h_{[i+2^{k-1}, k-1]}$ 在 $O(1)$ 的时间求出。所以预处理时间为 $O(n\log n)$。

这样就可以做到 $O(1)$ 求出等差数列。

至此，我们完成了所有的工作！

时间复杂度：$O(n\log n)-O(\log n)$。

空间复杂度：$O(n\log n)$。



---

## 作者：q1uple (赞：28)

[题目链接](https://www.luogu.com.cn/problem/P4482)

主播觉得什么后缀状物和神秘 Border 理论根本无法战胜，于是直接哈希！！！

本题解不需要任何 Border 的性质！！！

暴力哈希非常简单 (直接枚举 Border 长度)，但是根本就过不了啊，我们要考虑优化。

我们发现我们实际上有很多相同的东西，我们本可以预处理出来但是还要跑，浪费了很多时间。

我们肯定要预处理一些东西，我们设一个阈值 $S$，我们对于字符串 $S$ 中的 $S_{l \dots l+S-1}$，将相同的都放在一起一个集合 (用一个 vector 维护所有的集合)，对于每次询问，小于阈值 $S$ 直接跑暴力就行了，我们来考虑大于阈值 $S$ 的情况，我们在之前维护的集合中二分找到区间里面的下标，直接枚举所有合法的就行了，看似上很暴力，但是实际上字符集只有 $26$，所以很难卡掉吧，复杂度不敢下定论，有人分析一下吗。

阈值随便取几百几千就行了，下面是代码核心部分

```
ull hs[N],p[N];
const ull P=1331;
char s[N];
int n;
ull gv(int l,int r){
	return hs[r]-hs[l-1]*p[r-l+1];
}
map<ull,int>ma;
vector<int>pos[N];
const int len=3000;
int solve(int x,int y){
    if(y-x<=len+11){
        int l=1,r=y-x,ans=0;
        while(l<=r){
            int mid=r;
            if(gv(x,x+mid-1)==gv(y-mid+1,y))    qma(ans,mid),l=mid+1;
            else r--;
        }
        return ans;
    }
    int l=1,r=len+11,ans=0;
    while(l<=r){
        int mid=r;
        if(gv(x,x+mid-1)==gv(y-mid+1,y))    qma(ans,mid),l=mid+1;
        else r--;
    }
    ull now=gv(x,x+len-1);
    l=0,r=pos[ma[now]].size()-1;
    int be=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(x<pos[ma[now]][mid])   be=mid,r=mid-1;
        else l=mid+1;
    }
    if(be==-1)   return max(ans,(int)(s[x]==s[y]));
    for(int i=be;i<pos[ma[gv(x,x+len-1)]].size();i++){
        int now=pos[ma[gv(x,x+len-1)]][i];
        if(now+len-1>y)   break;
        int len=y-now+1;
        if(gv(x,x+len-1)==gv(now,y)){
            qma(ans,len);  return ans;
        }
    }
    return max(ans,(int)(s[x]==s[y]));
}
```

---

## 作者：shadowice1984 (赞：26)

从6月份咕咕咕到现在的一道题

对了申请增强数据，似乎暴力蛤希可以通过现在的数据

不过还是好好写你的samn连吧

# 数据范围是假的,$n,m<=2×10^5$
_____

### 前置芝士：sam(后缀自动机)

~~蛤？不会后缀自动机？出门左转你站膜板区，包教不包会~~

### 前置芝士：线段树合并

~~蛤？不会线段树合并，出门左转度娘，包教不包会~~

## 本题题解

一句话题意:给你一个字符串求区间的border

那么我们见到这种题考虑在后缀自动机上乱搞几下看看能不能出来

那么当然要对先对这个字符串建一个后缀自动机出来，然后提取这只后缀自动机的parent树看看有没有什么性质

那么我们发现求(l,r)的border相当于找一个i满足限制$i-l+1 \leq lcs(r,i), l<i \leq r$并且让i最大

那么既然有这个lcs(两个前缀的最长公共后缀)这个限制条件的话我们就考虑能不能在后缀自动机上处理这个条件了

先让我们思考一个部分分，串是随机生成的，也就是说parent树的高度是log的

那么我们可以在parent树上暴力跳r这个前缀对应的节点到祖先的路径了，此时我们实际上在做的事情就是枚举lcs(r,i)的值（因为parent树的性质是两个前缀节点的lca的len值就是这两个点lcp的len值）,

那么我们把限制条件简单做个转化就是求子树中点的区间最大值问题(要求i这个节点必须在这个点的子树中,限制条件在lcs值确定的条件下就是一个区间最大值问题)这个东西使用线段树合并维护一下每个节点的right集合的区间最大值即可轻松搞定

那么我们解决了这个部分分之后来考虑parent树树高不是log的情况

其实我们的问题就是此时lcs的值的种类是$O(n)$级别的而不是$O(logn)$级别的

那么我们不妨强行给刚才的暴力套上一个树剖看看能不能做

那么我们发现r对应的前缀节点到根节点的路径会被拆分成若干条重链的**前缀**(前缀这点相当重要，不然这题不能做)

那么对于每一个重链前缀的底部那个点对答案的贡献我们可以套用线段树合并来解决这个问题，此时的复杂度是$O(log^2n)$的

接下来是每条重链前缀对答案的贡献了

那么我们可以顺着这个重链把整棵树拎起来，就像这张图一样

![](https://cdn.luogu.com.cn/upload/pic/43944.png)

我们重新修改一下限制条件，把$i-l+1 \leq lcs(r,i)$改写成$i-lcs(r,i) < l$

假设我们令key(i)=i-len(x)其中x是i和当前正在处理的重链的lca

那么我们的问题其实就是求在\[l,r)这个区间当中并且key值小于l的i的最大值

乍一看这东西似乎需要二维数据结构才能处理……

但其实是不需要的……因为我们发现有个操作叫**线段树上二分**,如果我们在线段树上每个节点维护key(i)的区间最小值的话，此时我们就可以轻松的知道这个区间内是否存在一个合法的i值了，因此我们维护key(i)的区间最小值即可在一个log的时间复杂度内轻松出解了

那么问题来了，我们的线段树内需要存储这个重链前缀的所有轻子树的信息才能正确的出解，如果我们采取暴力dfs的方式来插入这个复杂度是对的吗？

(其实这个复杂度对不对无所谓的，因为无论如何你都可以使用线段树合并来强行插入点,不过这里其实暴力插点复杂度就是对的，并且可以让你少写一个线段树合并)

答案是肯定的，因为我们考虑每个点的被插入次数，显然一个点只会被插入这个点的轻边深度次，那么每个点的轻边深度都是$O(logn)$的自然总的插入次数就是$O(nlogn)$的

那么我们要做的就是先将parent树重链剖分之后离线每一个询问，对于重链底端的点将这log个询问二次离线之后使用线段树合并解决，对于每一个重链前缀的询问我们将着log个询问二次离线之后，采用下面这个算法解决(其实就是链分治，不过有人叫他树上启发式合并,不过这题和传统的树上启发式合并不一样)

假设我们正在处理某一条重链上的所有询问，那么我们先递归的分治和这条重链相关的所有重链，接下来从高到低的枚举重链上每一个点，将这个点的轻子树暴力dfs一遍在插入到维护区间key最小值的线段树中去,然后回答所有和当前重链前缀相关的询问

然后我们就做完了这道题，总的时间复杂度是$O(nlog^2n)$由于数据极其水所以跑的飞快

上代码~

```C
// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;const int N=2*1e5+10;
char mde[N];int ans[N];int n;int m;int siz[2*N];int h[2*N];int top[2*N];
int v[2*N];int x[2*N];int ct;int al[2*N];int len[2*N];int fa[2*N];int ql[N];int qr[N];
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
struct suffixautomaton//简易后缀自动机模板
{
    int mp[2*N][30];int ct;
    inline void ih(){for(int i=1;i<=n;i++)len[i]=i;ct=n+1;}
    inline void ins(int i,int c)
    {
        int p=(i==1)?n+1:i-1;for(;p&&mp[p][c]==0;p=fa[p])mp[p][c]=i;
        if(p==0){fa[i]=n+1;return;}int q=mp[p][c];
        if(len[q]==len[p]+1){fa[i]=q;return;}len[++ct]=len[p]+1;
        for(int j=1;j<=26;j++)mp[ct][j]=mp[q][j];
        for(;p&&mp[p][c]==q;p=fa[p])mp[p][c]=ct;
        fa[ct]=fa[q];fa[q]=fa[i]=ct;return;
    }
    inline void build(){for(int i=1;i<=ct;i++)add(fa[i],i);}
}sam;
inline int dfs1(int u)//重链剖分
{
    for(int i=al[u];i;i=x[i])
        siz[u]+=dfs1(v[i]),h[u]=(siz[h[u]]<siz[v[i]])?v[i]:h[u];return ++siz[u];
}
inline void dfs2(int u)
{
    top[u]=top[u]?top[u]:u;if(h[u])top[h[u]]=top[u],dfs2(h[u]);
    for(int i=al[u];i;i=x[i])if(v[i]!=h[u])dfs2(v[i]);return;
}
namespace lt1//线段树合并
{
    int s[20*N][2];int ct;int va[20*N];int ali[18*N];int nx[18*N];int mct;int tw[18*N];
    inline void pb(int p,int tim){tw[++mct]=tim;nx[mct]=ali[p];ali[p]=mct;}
    inline void ins(int p,int l,int r,int pos)
    {
        va[p]=pos;if(r-l==1)return;int mid=(l+r)/2;
        if(pos<=mid)ins(s[p][0]=++ct,l,mid,pos);
        else ins(s[p][1]=++ct,mid,r,pos);return;
    }	
    inline int cmx(int p,int l,int r,int dl,int dr)
    {
        if((dl==l&&dr==r)||p==0){return va[p];}int mid=(l+r)/2;int res=0;
        if(dl<mid)res=max(res,cmx(s[p][0],l,mid,dl,min(dr,mid)));
        if(mid<dr)res=max(res,cmx(s[p][1],mid,r,max(dl,mid),dr));return res;
    }
    inline void mg(int p1,int p2,int l,int r)
    {
        if(r-l==1)return;int mid=(l+r)/2;
        if(s[p1][0]&&s[p2][0])mg(s[p1][0],s[p2][0],l,mid);else if(s[p2][0])s[p1][0]=s[p2][0];
        if(s[p1][1]&&s[p2][1])mg(s[p1][1],s[p2][1],mid,r);else if(s[p2][1])s[p1][1]=s[p2][1];
        va[p1]=max(va[s[p1][0]],va[s[p1][1]]);
    }
    inline void ih(){ct=n;for(int i=1;i<=n;i++)ins(i,0,n,i);}
    inline int dfs(int u)
    {
        int ret=(u<=n)?u:0;
        for(int i=al[u];i;i=x[i])if(ret)mg(ret,dfs(v[i]),0,n);else ret=dfs(v[i]);
        for(int i=ali[u],tv=tw[i];i;i=nx[i],tv=tw[i])
        {
        	int R=min(ql[tv]+len[u],qr[tv]);
        	if(ql[tv]<R)ans[tv]=max(ans[tv],cmx(ret,0,n,ql[tv]-1,R-1));
        }return ret;
    }
}
namespace lt2//链分治+线段树上二分
{
    int s[2*N][2];int ct;int va[2*N];int ali[18*N];int nx[18*N];int mct;int tw[18*N];
    inline void pb(int p,int tim){tw[++mct]=tim;nx[mct]=ali[p];ali[p]=mct;}
    inline void ih(){for(int i=0;i<=2*N-10;i++)va[i]=0x3f3f3f3f;}
    inline void clr()
    {
        for(int i=1;i<=ct;i++)va[i]=0x3f3f3f3f;
        for(int i=1;i<=ct;i++)s[i][0]=s[i][1]=0;ct=1;
    }
    inline void ins(int p,int l,int r,int pos,int val)
    {
        va[p]=min(va[p],val);if(r-l==1)return;int mid=(l+r)/2;
        if(pos<=mid)ins(s[p][0]=s[p][0]?s[p][0]:++ct,l,mid,pos,val);
        else ins(s[p][1]=s[p][1]?s[p][1]:++ct,mid,r,pos,val);
    }
    inline int cmx(int p,int l,int r,int dl,int dr,int lim)
    {
        if(va[p]>=lim)return -0x3f3f3f3f;if(r-l==1)return r;int mid=(l+r)/2;
        if(mid<dr)
        {
            int ret=cmx(s[p][1],mid,r,max(dl,mid),dr,lim);
            if(ret!=-0x3f3f3f3f)return ret;
        }if(dl<mid)return cmx(s[p][0],l,mid,dl,min(dr,mid),lim);return -0x3f3f3f3f;
    }
    inline void subsolve(int u,int le)//暴力dfs插入
    	{if(u<=n)ins(1,0,n,u,u-le);for(int i=al[u];i;i=x[i])subsolve(v[i],le);}
    inline void solve(int u)//链分治
    {
        for(int p=u;p;p=h[p])
            for(int i=al[p];i;i=x[i])if(v[i]!=h[p])solve(v[i]);clr();
        for(int p=u;p;p=h[p])
        {
            for(int i=al[p];i;i=x[i])if(v[i]!=h[p])subsolve(v[i],len[p]);
            if(p<=n)ins(1,0,n,p,p-len[p]);
            for(int i=ali[p],tv=tw[i];i;i=nx[i],tv=tw[i])
            	{ans[tv]=max(ans[tv],cmx(1,0,n,ql[tv]-1,qr[tv]-1,ql[tv]));}
        }
    }
}
inline void stqr(int tim,int l,int r)//暴力跳重链，将询问二次离线
{
    if(l==r)return;ql[tim]=l;qr[tim]=r;
    for(int p=r;p;p=fa[top[p]]){lt1::pb(p,tim);lt2::pb(p,tim);}
}
int main()
{
    scanf("%s",mde+1);for(n=1;mde[n+1]!='\0';n++);sam.ih();lt2::ih();
    for(int i=1;i<=n;i++)sam.ins(i,mde[i]-'a'+1);sam.build();
    dfs1(n+1);dfs2(n+1);scanf("%d",&m);
    for(int i=1,l,r;i<=m;i++)scanf("%d%d",&l,&r),stqr(i,l,r);
    lt1::ih();lt1::dfs(n+1);lt2::solve(n+1);
    for(int i=1;i<=m;i++)if(ans[i]==0)printf("0\n");else printf("%d\n",ans[i]-ql[i]+1);return 0;//拜拜程序~
}

```


























---

## 作者：command_block (赞：17)

**题意**：给出字符串 $S$，$m$ 次询问子串 $S[l:r]$ 的最长 Border 长度。

$|S|,m\leq 2\times 10^5$，时限 $\texttt{5s}$。

------------

记 ${\rm lcs}(i,j)$ 为前缀 $i,j$ 的最长公共后缀长度。

则求 $S[l:r]$ 的 Border 相当于找到一个 $[l,r]$ 中最大的 $p$  满足 ${\rm lcs}(p,r)\geq p-l$。

这个 ${\rm lcs}(p,r)$ 正是两个前缀节点 Parent Tree 上 LCA 的 $len$ 值。

这看起来很不好直接使用数据结构维护，可能需要树链分治。

先考虑暴力跳 Parent Tree 的做法。即枚举前缀 $r$ 在 Parent Tree 上的所有祖先 $t$，令 ${\rm lcs}(p,r)=t$，再考虑有那些 $p$。维护 $t$ 的 endpos 集合 ${\rm end}(t)$，则最好的 $p$ 是 ${\rm end}(t)$ 中在 $[l,r]$ 内的最大元素。

这可以线段树合并维护 endpos，然后区间查询。

-----

为了不那么暴力，将树树剖，一个询问就会被拆成对 $O(\log n)$ 条重链的询问。

假设从点 $u$ 进入该重链，则从上到 $u$ 的路径，LCA  为上方的重链点，$u$ 向下的路径，LCA 为 $u$ 本身。

注意,这可能会产生上下重复的路径，但是容易发现答案更劣，所以不用除去。

对于一条重链，我们需要解决如下的子问题：

> 记 $len[u]$ 为 SAM 的前缀节点 $u$ 与当前重链的 LCA 的 $len$。
>
> 将重链的节点从浅往深编号为 $1\sim m$，记 ${\rm end}(i)$ 为第 $i$ 个节点的 endpos 集合，它是递减的。
>
> 每次对一个前缀 $[1,u)$，询问
> $$
> \max\limits_{i=1}^{u-1}\max\limits_{v\in{\rm end}(i)}[l\leq v\leq r][v\leq l+len[v]]v
> $$
> 对一个后缀 $[u,m]$，询问
> $$
> \max_{i=u}^m\max_{v\in{\rm end}(i)}[l\leq v\leq r][v\leq l+len[u]]v
> $$

需要考虑的“前缀节点”的数目是每条轻链头的子树大小和，为 $O(n\log n)$。可以对每条重链分别暴力计算 $len$，并分别处理这个类似偏序的问题。

第一维 $[l\leq u\leq r]$ 不难解决，使用区间数据结构：线段树。

对于第二维 $[v\leq l+len[v]]$ 或 $[v\leq l+len[u]]$，可以在线段树上记下 $v-len[v]$ 或 $v$ 的区间最小值，即可判断某个区间内是否可能有解。

然后使用线段树上二分即可。

写起来大概就是先把询问挂到重链上，然后对每条重链，暴力 DFS 轻子树。

然后离线处理，对每条重链前后扫描线两次，将轻子树依次从上到下加入线段树（不必动态开点），就能得到每个前缀/后缀的状态。

这样空间复杂度就是 $O(n)$，时间复杂度为 $O(n\log^2n)$，常数不大。



```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#define ll long long
#define MaxN 205000
using namespace std;
struct Node
{int t[26],f,len,tf,son;}a[MaxN<<1];
int tot,las;
void ins(int c)
{
  int np=++tot,p=las;las=np;
  a[np].len=a[p].len+1;
  for (;p&&!a[p].t[c];p=a[p].f)a[p].t[c]=np;
  if (!p)a[np].f=1;
  else {
    int v=a[p].t[c];
    if (a[p].len+1==a[v].len)a[np].f=v;
    else {
      int nv=++tot;a[nv]=a[v];
      a[nv].len=a[p].len+1;
      for (;p&&a[p].t[c]==v;p=a[p].f)a[p].t[c]=nv;
      a[v].f=a[np].f=nv;
    }
  }
}
vector<int> g[MaxN<<1];
int siz[MaxN<<1];
void pfs1(int u)
{
  siz[u]=1;
  for (int i=0,v;i<g[u].size();i++){
    pfs1(v=g[u][i]);
    siz[u]+=siz[v];
    if (siz[v]>siz[a[u].son])
      a[u].son=v;
  }
}
void pfs2(int u,int tf)
{
  a[u].tf=tf;
  if (!a[u].son)return ;
  pfs2(a[u].son,tf);
  for (int i=0,v;i<g[u].size();i++)
    if ((v=g[u][i])!=a[u].son)
      pfs2(v,v);
}
int n,tn,to,wfc,t[MaxN<<2];
#define INF 1000000000
void clr(int l=1,int r=n,int u=1)
{
  if (t[u]==INF)return ;
  t[u]=INF;
  if (l==r)return ;
  int mid=(l+r)>>1;
  clr(l,mid,u<<1);
  clr(mid+1,r,u<<1|1);
}
void add(int l=1,int r=n,int u=1)
{
  if (l==r){t[u]=wfc;return ;}
  int mid=(l+r)>>1;
  if (to<=mid)add(l,mid,u<<1);
  else add(mid+1,r,u<<1|1);
  t[u]=min(t[u<<1],t[u<<1|1]);
}
int wfr,wfx;
int qry(int l=1,int r=n,int u=1)
{
  if (t[u]>wfx)return 0;
  if (l==r)return l;
  int mid=(l+r)>>1;
  if (mid<wfr&&t[u<<1|1]<=wfx){
    int sav=qry(mid+1,r,u<<1|1);
    if (sav)return sav;
  }return qry(l,mid,u<<1);
}
int tlen,w[MaxN<<1];
void dfs2(int u)
{
  if (w[u]){to=w[u];wfc=w[u]-tlen;add();}
  for (int i=0;i<g[u].size();i++)
    dfs2(g[u][i]);
}
struct QData {int l,r,p;};
vector<QData> q[MaxN<<1];
void addop(int u,int l,int r,int p)
{
  while(u){
    q[u].push_back((QData){l,r,p});
    u=a[a[u].tf].f;
  }
}
int ans[MaxN],st[MaxN];
void solve(int u)
{
  clr();
  int tot=0,sf=a[u].tf;
  for (;a[u].tf==sf;u=a[u].f)
    st[++tot]=u;
  clr();tlen=0;
  for (int k=1;k<=tot;k++){
    if (w[u=st[k]]){to=w[u];wfc=w[u];add();}
    for (int i=0;i<g[u].size();i++)
      if (g[u][i]!=a[u].son)
        dfs2(g[u][i]);
    for (int i=0;i<q[u].size();i++){
      wfx=q[u][i].l+a[u].len-1;wfr=q[u][i].r-1;
      if (wfr)ans[q[u][i].p]=max(ans[q[u][i].p],qry());
    }
  }clr();
  for (int k=tot;k;k--){
    tlen=a[u=st[k]].len;
    if (w[u]){to=w[u];wfc=w[u]-tlen;add();}
    for (int i=0;i<g[u].size();i++)
      if (g[u][i]!=a[u].son)
        dfs2(g[u][i]);
    for (int i=0;i<q[u].size();i++){
      wfx=q[u][i].l-1;wfr=q[u][i].r-1;
      if (wfr)ans[q[u][i].p]=max(ans[q[u][i].p],qry());
    }
  }
}
char str[MaxN];
int m,sl[MaxN],sr[MaxN],edp[MaxN];
int main()
{
  scanf("%s",str+1);n=strlen(str+1);
  tot=las=1;
  for (int i=1;i<=n;i++)ins(str[i]-'a');
  for (int i=1,p=1;i<=n;i++){
    p=a[p].t[str[i]-'a'];
    edp[w[p]=i]=p;
  }for (int i=2;i<=tot;i++)
    g[a[i].f].push_back(i);
  pfs1(1);pfs2(1,1);
  scanf("%d",&m);
  for (int i=1;i<=m;i++){
    scanf("%d%d",&sl[i],&sr[i]);
    addop(edp[sr[i]],sl[i],sr[i],i);
  }for (int i=1;i<=tot;i++)
    if (!a[i].son)solve(i);
  for (int i=1;i<=m;i++)
    printf("%d\n",max(ans[i]-sl[i]+1,0));
  return 0;
}
```

---

## 作者：万弘 (赞：17)

 $ Q $ 次询问子串的最长 Border.    $ |S|,Q\le 2\times 10^5 $ 

求 $ [l,r] $ 的 border 等价于选一个最大的 $ i\in [l,r) $ ,使 $ \text{LCS}([1,i],[1,r])\ge i-l+1 $ 。比较难以处理的是，这个条件没有单调性。

考虑前缀的 $ \text{LCS} $ 在前缀树（也是 SAM 的 parent 树）上就是 LCA 表示的状态的长度。那么一种naive的做法就是先线段树合并处理 endpos 集合，然后枚举前缀树上的每个祖先 $ u $ ，在 $ u $ 的 endpos 集合中找一个在 $ [l,\min(r-1,l+len(u)-1)] $ 中且最大的位置。  
理论最坏是平方。~~但是能过~~

常用套路树上倍增在这里也没法用，因为从下到上 endpos 集合增大，但 $ len $ 值减小，同样不单调。

将问题转化一步，记表示 $ [1,r] $ 的节点为 $ u $ .等价于从**整个前缀树中选一个前缀节点** $ v $ (记其表示 $ [1,i] $ )，要求 $ len(\text{LCA}(u,v))\ge i-l+1 (\ i-len(\text{LCA}(u,v))<l)$且 $ i $ 尽量大。

用链分治来搞这件事。考虑先划分轻重链，一个点到根的路径划分为至多 $ \log_2 n $ 段（且每一段都是一条重链的子段）。

对于每一段，记其中最深的点（就是进去那个点）为 $ S $ ,链顶端为 $ top $ .则贡献为：

- 从 $ S $ 的子树中取一个点
- 从重链上 $S$ 上面的点中选一个点
- 从重链上 $S$ 上面的点的轻子树中选一个点

容易发现，各条重链的贡献可能有重叠的部分，但一定没有遗漏，具体处理如下：  
对于第一种情况，我们同样用线段树合并。每个询问的代价是 $ \mathcal O(\log^2 n) $ .  
所有重链长度之和为 $ \mathcal O(n) $ ,所有轻子树大小之和是 $ \mathcal O(n\log n) $ ,所以后两种贡献总共涉及 $ \mathcal O(n\log n) $ 个点，这很好（因此我们的链分治才是有意义的，并且第一种情况必须用线段树合并做，否则这里的点数就爆炸了）。  
维护一棵线段树，第 $i$ 个叶子存 $ i-len(LCA(u,S)) $ 的值（$u$是表示 $[1,i]$ 的点）。将“重链上 $S$ 上面的点及其轻子树”中的前缀点全部在线段树上修改。对于 $S$ 上的每个询问，在线段树上找一个最大的 $i$ 满足 $i<r,i-len(LCA(u,S))<l$ 。这可以用线段树上二分做到。

将询问离线，放到每个段最深的点（进去的点）上，统一处理所有询问即可。

总时间复杂度 $ \mathcal O((n+Q)\log^2 n) $ ，空间复杂度 $ \mathcal O((n+Q)\log n) $ 

一些细节：处理完一条重链后要撤销其在线段树上的修改。

另外，似乎网上的好几份代码都在我造的几组$|S|=10,Q=50$,字符集为$\{a,b\}$的数据下挂掉了。好像是他们的线段树上二分写的不太对（比如区间为空时）

```cpp
const int INF=1e9;
#define MAXN 400011
int n,root[MAXN],cnt=0;
struct Endp
{
    struct node{int lson,rson;}t[MAXN<<6|1];
    #define rt t[num]
    void insert(int& num,un pos,un l=1,un r=n)
    {
        if(!num)num=++cnt;
        if(l==r)return;
        un mid=(l+r)>>1;
        if(pos<=mid)insert(rt.lson,pos,l,mid);
        else insert(rt.rson,pos,mid+1,r);
    }
    int Query(int num,int upp,un l=1,un r=n)
    {
        if(!num||upp<1)return 0;
        if(l==r)return l;
        un mid=(l+r)>>1;
        int res=0;
        if(upp>mid)res=Query(rt.rson,upp,mid+1,r);
        if(res)return res;
        return Query(rt.lson,upp,l,mid);
    }
    int merge(int x,int y,un l=1,un r=n)
    {
        if(!x||!y)return x|y;
        if(l==r)return x;
        int num=++cnt;un mid=(l+r)>>1;
        rt.lson=merge(t[x].lson,t[y].lson,l,mid);
        rt.rson=merge(t[x].rson,t[y].rson,mid+1,r);
        return num;
    }
    void debug(un l,un r,un num)
    {
        if(l==r){printf("%d ",l);return;}
        un mid=(l+r)>>1;
        if(rt.lson)debug(l,mid,rt.lson);
        if(rt.rson)debug(mid+1,r,rt.rson);
    }
}endp;

struct Segment_Tree
{
    int t[MAXN<<2|1];
    void build(un l=1,un r=n,un num=1)
    {
        rt=INF;
        if(l==r)return;
        else build(l,(l+r)>>1,num<<1),build(((l+r)>>1)+1,r,num<<1|1);
    }
    void modify(un pos,int val,un l=1,un r=n,un num=1)
    {
        if(l==r){rt=val;return;}
        un mid=(l+r)>>1;
        if(pos<=mid)modify(pos,val,l,mid,num<<1);
        else modify(pos,val,mid+1,r,num<<1|1);
        rt=min(t[num<<1],t[num<<1|1]);
    }
    int Query(int upp,int lim,un l=1,un r=n,un num=1)
    {
        if(rt>=lim)return 0;
        if(l==r)return rt<lim?l:0;
        un mid=(l+r)>>1;
        int res=0;
        if(upp>mid)res=Query(upp,lim,mid+1,r,num<<1|1);
        if(res)return res;
        return Query(upp,lim,l,mid,num<<1);
    }
    
}sgt;
struct SAM
{
    
    int t[MAXN][26],pre[MAXN],len[MAXN],End[MAXN];
    int last,tot;
    SAM(){last=tot=1;}
#define from(u) for(int i=head[u],v=e[i].v;i;i=e[i].nxt,v=e[i].v)
    void extend(int w,int dex)
    {
        int pos=last,cur=++tot;
        len[cur]=len[pos]+1,last=cur,End[cur]=dex;
        while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
        if(!pos){pre[cur]=1;return;}
        int nxt=t[pos][w];
        if(len[nxt]==len[pos]+1)pre[cur]=nxt;
        else
        {
            int tmp=++tot;
            len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
            pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
            while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
        }
    }
    
    struct one{int l,r,dex;};
    std::vector<one>q[MAXN];
    int ans[MAXN];
    struct edge{int v,nxt;}e[MAXN<<1|1];
    int cnt,head[MAXN];
    void adde(int u,int v){e[++cnt].v=v,e[cnt].nxt=head[u],head[u]=cnt;}
    int size[MAXN],dep[MAXN],mson[MAXN],top[MAXN];
    void dfs1(int u)
    {
        size[u]=1;
        if(End[u])endp.insert(root[u],End[u]);
        from(u)
        {
            dep[v]=dep[u]+1,dfs1(v);
            size[u]+=size[v];
            if(size[v]>size[mson[u]])mson[u]=v;
            root[u]=endp.merge(root[u],root[v]);
        }
    }
    void dfs2(int u,int now_top)
    {
        top[u]=now_top;
        if(mson[u])dfs2(mson[u],now_top);
        from(u)
            if(v!=mson[u])dfs2(v,v);
    }
    void build()
    {
        for(int i=2;i<=tot;++i)adde(pre[i],i);
        dfs1(1),dfs2(1,1);
    }

    void push(int u,int k)
    {
        if(End[u])sgt.modify(End[u],End[u]-k);
        from(u)push(v,k);
    }
    void back(int u)
    {
        if(End[u])sgt.modify(End[u],INF);
        from(u)back(v);
    }
    void solve(int S)
    {
        for(int u=S;u;u=mson[u])
        {
            if(End[u])sgt.modify(End[u],End[u]-len[u]);
            from(u)
                if(v!=mson[u])push(v,len[u]);
            // printf("consider %d,len=%d\n",u,len[u]);
            for(auto x:q[u])
            {
                int res=endp.Query(root[u],min(x.r-1,x.l+len[u]-1));
                if(res>=x.l)umax(ans[x.dex],res-x.l+1);
                res=sgt.Query(x.r-1,x.l);
                if(res>=x.l)umax(ans[x.dex],res-x.l+1);
            }
        }
        for(int u=S;u;u=mson[u])
        {
            if(End[u])sgt.modify(End[u],INF);
            from(u)
                if(v!=mson[u])back(v);
        }
        for(int u=S;u;u=mson[u])
            from(u)
                if(v!=mson[u])solve(v);
    }
}sam;
int ed[MAXN];
char s[MAXN];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;++i)sam.extend(s[i]-'a',i),ed[i]=sam.last;
    sam.build();
    // endp.debug(1,n,root[ed[2]]);
    // puts("?");
    // printf("Res=%d\n",endp.Query(root[1],1));
    int query=read();
    for(int i=1;i<=query;++i)
    {
        int l=read(),r=read();
        if(l==r){sam.ans[i]=0;continue;}
        int pos=ed[r];
        while(pos)sam.q[pos].push_back({l,r,i}),pos=sam.pre[sam.top[pos]];
    }
    sgt.build();
    sam.solve(1);
    for(int i=1;i<=query;++i)printf("%d\n",sam.ans[i]);
    return 0;
}
```



---

## 作者：Schi2oid (赞：10)


SAM 胎教题。（？）

这个题的关键在于，你要想到两种暴力。精妙绝伦！所以以后看到不会的题，想完暴力不一定就要结束这道题，可以尝试再想一个暴力，说不定就把这题给秒了。

下文中的 Border 指公共前后缀，并不特指最长。

## 暴力 1

假设当前询问 $[l,r]$。设 $s[1\dots r]$ 对应的字符串所在的 SAM 结点编号为 $x$。考虑 SAM 上如何描述 Border，由于其既是 $s[l\dots r]$ 的前缀又是后缀，它对应的字符串一定在 $x$ 的祖先链（含 $x$）上。现在我们遍历这条祖先链，只需要对其是否为前缀进行判定。设当前遍历到的点为 $p$。由于同一个结点内的字符串长度连续变化，并且 endpos 集合相同，只要 $[l,l+len_p-1]$ 中有位置出现在 endpos 集合里，记为 $i$，那么 $i-l+1$ 就是一个 Border。那么，一次询问被转化成 $O(n)$（深度决定）次查询区间内最大有值位置，使用  `set<int>::lower_bound()` 可以处理。

每个点的 endpos 集合可以通过 `set` 启发式合并在 $O(n\log^2n)$ 时间复杂度内求出。深搜 parent tree，将每个询问挂在对应的 $x$ 上，遇到一个询问则将其加入处理集合，在每个点遍历处理集合内的所有询问，总时间复杂度 $O(n^2\log n)$。

## 暴力 2

假设当前询问 $[l,r]$。设 $s[1\dots r]$ 对应的字符串所在的 SAM 结点编号为 $x$。记 $lcs(i,j)$ 表示 $s[1\dots i]$ 和 $s[1\dots j]$ 的最长公共后缀，那么这个后缀对应的结点就是 $s[1\dots i]$ 和 $s[1…j]$ 在 parent tree 上对应结点的 LCA。也就是说，$lcs(i,j)=len_{lca(i,j)}$。考虑 SAM 上如何描述 Border，相当于找到一个位置 $i<r$，使得 $lcs(i,r)\ge i-l+1$，那么 $i-l+1$ 就是一个 Border。（$i<l$ 时，Border 并不存在，但是为了后续方便处理，我们允许 Border 为非正数的情况出现）稍作整理，可得 $l\ge i-lcs(i,r)+1$。我们可以在 $lcs(i,r)$ 确定的情况下，将 $i-lcs(i,r)+1$ 存入线段树的下标 $i$，线段树维护区间最小值即可查询。

考虑在 parent tree 上深搜，每次进入一个子树时将别的子树及其父结点对其贡献直接加入，这是因为这一子树与别的子树内的点的 LCA 一定是它们的父结点。这可以通过搜索其所有轻儿子，将所有前缀点的贡献加入，进入某个子树时将其内部贡献删除，回溯时再撤销来实现。将询问挂在对应的 $x$ 上，对于单次询问相当于查询线段树上下标在 $[1,r)$ 中满足 $t[i]\le l$ 的最大下标 $i$。线段树上二分即可处理，具体来说，优先进右儿子，结点区间在范围内时判断区间最小值是否 $\le l$，满足条件直接返回，总时间复杂度 $O(\sum sz_u\log n)$。

## Pen Pineapple Apple Pen

考虑 **暴力 1** 的特点是单次判定复杂度极低（$O(\log n)$），然后 **暴力 2** 的特点是复杂度基于子树大小和。有一个关键的注意，所有的轻子树大小之和是 $O(n\log n)$ 的，这是因为每个点对轻子数大小之和等于其到根路径上的轻边个数，也就是 $O(\log n)$ 的。这启发我们利用 **暴力 2** 处理所有轻子树，而 **暴力 1** 负责处理残余部分。由此~~容易想到~~轻重链剖分。

具体来说，我们直接跑**暴力 2**，不同的是，我们只对轻子树进行上述操作，而暂时忽略重子树产生的贡献。现在，我们要分析哪些贡献被遗落。从 $r$ 出发上跳，过程中会经过 $O(\log n)$ 条重链的**前缀**，之间用一条轻边连接。容易发现，我们只漏掉了轻边顶部的点的重子树产生的贡献。可以在过程中同时维护 endpos 集合，这样就可以把每个询问同时也挂在每个轻边顶部点上，直接利用 **暴力 1** 统计其产生的贡献。也许有些贡献在两种暴力中都被计算到（例如轻边顶部点的轻子树中的点），但这不重要，因为我们只关心最大值。对于一次询问，我们只会对至多 $O(\log n)$ 个点跑 **暴力 1**，所以，总的时间复杂度为 $O(n\log^2 n)$。

至此，本题完结。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define mid ((l+r)>>1)
int n;
const int INF=1e9;
char S[400005];
int ch[800005][26];
set<int>s[800005];
vector<int>edge[800005];
int len[800005],fa[800005];
int lst=1,idcnt=1;
int sz[800005],son[800005],top[800005];
int ans[800005];
vector<int>todo1[800005];
vector<int>todo2[800005];
int L[800005],R[800005];
int loc[800005],isp[800005];
void insert(int c){
	int p=lst,cur=++idcnt;
	len[cur]=len[lst]+1;
	while(p&&!ch[p][c]) ch[p][c]=cur,p=fa[p];
	int q=ch[p][c];
	if(!q) fa[cur]=1;
	else if(len[q]==len[p]+1) fa[cur]=q;
	else{
		int r=++idcnt;
		memcpy(ch[r],ch[q],sizeof ch[r]);
		len[r]=len[p]+1;
		fa[r]=fa[q],fa[q]=fa[cur]=r;
		while(p&&ch[p][c]==q) ch[p][c]=r,p=fa[p];
	}
	s[cur].insert(len[cur]);
	isp[cur]=len[cur];
	loc[len[cur]]=cur;
	lst=cur;
}
void dfs(int x){
	sz[x]=1;
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		dfs(v);
		sz[x]+=sz[v];
		if(sz[v]>sz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v==son[x]) continue;
		dfs2(v,v);
	}
}
void put(int p,int id){
	while(p){
		todo1[p].push_back(id);
		p=fa[top[p]];
	}
}
void merge(int x,int y){
	if(s[x].size()<s[y].size()) swap(s[x],s[y]);
	while(s[y].size()){
		s[x].insert(*s[y].begin());
		s[y].erase(*s[y].begin());
	}
}
int mn[3200005];
void push_up(int p){
	mn[p]=min(mn[ls(p)],mn[rs(p)]);
}
void init(int p,int l,int r){
	mn[p]=INF;
	if(l==r) return;
	init(ls(p),l,mid);
	init(rs(p),mid+1,r);
}
void modi(int p,int l,int r,int q,int k){
	if(l==r){
		mn[p]=k;
		return;
	}
	if(q<=mid) modi(ls(p),l,mid,q,k);
	else modi(rs(p),mid+1,r,q,k);
	push_up(p);
}
int get(int p,int l,int r,int id){
	if(l==r) return l;
	if(mn[rs(p)]<=L[id]) return get(rs(p),mid+1,r,id);
	else return get(ls(p),l,mid,id);
}
int query(int p,int l,int r,int id){
	if(r<R[id]){
		if(mn[p]<=L[id]) return get(p,l,r,id);
		else return -1;
	}
	if(R[id]-1>mid){
		int tmp=query(rs(p),mid+1,r,id);
		if(tmp!=-1) return tmp;
	}
	int tmp=query(ls(p),l,mid,id);
	if(tmp!=-1) return tmp;
	return -1;
}
struct node{int id,k;};
stack<node>stk;
void add(int x,int lca,int op){
	if(isp[x]){
		if(op) modi(1,1,n,isp[x],isp[x]-lca+1);
		else modi(1,1,n,isp[x],INF);
	}
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		add(v,lca,op);
	}
}
void fdfs(int x){
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v!=son[x]) add(v,len[x],1);
	}
	for(int i=0;i<todo2[x].size();i++){
		int id=todo2[x][i];
		ans[id]=max(ans[id],query(1,1,n,id)-L[id]+1);
	}
	if(isp[x]) modi(1,1,n,isp[x],isp[x]-len[x]+1);
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v!=son[x]) add(v,len[x],0);
		fdfs(v);
		merge(x,v);
		if(v!=son[x]) add(v,len[x],1);
	}
	for(int i=0;i<todo1[x].size();i++){
		int id=todo1[x][i];
		set<int>::iterator it=s[x].lower_bound(min(L[id]+len[x],R[id]));
		if(it!=s[x].begin()){
			it--;
			ans[id]=max(ans[id],(*it)-L[id]+1);
		}
	}
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v!=son[x]) add(v,len[x],0);
	}
	if(isp[x]) modi(1,1,n,isp[x],INF);
}
int main(){
	int q;
	scanf("%s",S+1);
	n=strlen(S+1);
	for(int i=1;i<=n;i++) insert(S[i]-'a');
	for(int i=1;i<=idcnt;i++) edge[fa[i]].push_back(i);
	dfs(1);
	dfs2(1,1);
	cin>>q;
	for(int i=1;i<=q;i++){
		scanf("%d%d",&L[i],&R[i]);
		todo2[loc[R[i]]].push_back(i);
		put(loc[R[i]],i);
	}
	init(1,1,n);
	fdfs(1);
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：FjswYuzu (赞：10)

重点不在 Border Theory 内容……单是做法就已经很有意思了。

记一个字符串 $s$ 长为 $p$ 的前缀为 $\operatorname{pre}(s,p)$，长为 $q$ 的后缀为 $\operatorname{suf}(s,q)$。字符串 $s$ 的长度记为 $|s|$，那么 $s$ 可由 $|s|$ 个字符拼接表示，第 $i$ 字符为 $s_i$。

---

### 周期与 Border

如果 $1 \leq p < |s|$，且 $\forall i,s_i=s_{i+p}$，称 $p$ 为 $s$ 的周期。$per(s)$ 表示 $s$ 的最小周期。

如果 $1 \leq q < |s|$，且 $\operatorname{pre}(s,q)=\operatorname{suf}(s,q)$，称 $q$ 为 $s$ 的 Border。

显然一个字符串 $s$ 的一个 Border $p$ 会对应一个周期 $|s|-p$。

#### Weak Periodicity Lemma

如果字符串 $s$ 有周期 $p,q$，满足 $p+q\leq |s|$，则 $\gcd(p,q)$ 也为 $s$ 的周期。 

根据周期定义，假设 $p<q$，不难发现 $q-p$ 为周期。类似于更相减损，可得到 $\gcd(p,q)$ 为周期。

想去掉 Weak 的话把限制缩成 $p+q-\gcd(p,q) \leq |s|$ 就好了。虽然实际应用一般。

推一个引理：如果字符串 $u,v$ 满足 $2|u| \geq |v|$，则 $u$ 在 $v$ 里匹配位置构成一个等差数列；如果项数不小于 $3$，那么公差为 $per(u)$。

证明的话，考虑第一次，第二次以及最后一次匹配。记第一次和第二次匹配位置之差为 $d$，第二次和最后一次匹配位置之差为 $q$。显然 $d,q$ 都是 $u$ 的周期；若 $u$ 存在比 $\gcd(d,q)$ 更小的周期，那么 $d$ 显然会变得更小，矛盾。所以 $per(u) = d \leq p \leq \gcd(d,q)$，证毕。

---

### Border Theory

几乎是把 Border 与周期联系证明的，具体证明不难，根据上面的内容摆结论就好了。

1. 对于一个字符串 $s$，其长度大于等于 $\frac{|S|}{2}$ 的 Border 构成一个等差数列（运用：失配树 10MiB 版，HNOI2019 JOJO）；   
2. 对于两个字符串 $u,v$，记 $\operatorname{LargePS}(u,v) = \{k:\operatorname{pre}(u,k)= \operatorname{suf}(v,k),k \geq \frac{|u|}{2}\}$，则 $\operatorname{LargePS}(u,v)$ 的元素构成一个等差数列；    
3. 一个字符串的所有 Border 可以划分成 $O(\log n)$ 个等差数列（运用：Mivik 的标题，论战捆竹竿）。实际运用的时候一般按长度 $[1,2),[2,4),\cdots,[2^k,|s|)$ 分。

---

然后回到这个题上。

考虑一个厉害的想法，我们求出这个子串的所有 Border，问题就解决啦！

其实根据 Border Theory，我们将其所有 Border 按值域划分成 $O(\log n)$ 个等差数列。那我们就先枚举大的值域然后求一个 Border 等差数列就好了。

注意到除了最后一个 $[2^k,|s|)$ 比较特殊，于是我们分类，分成 $[2^{i-1},2^i)$ 和 $[2^k,|s|)$ 两种。

考虑到如果一个字符串 $s$ 有一个 Border $p \in [2^{i-1},2^i)$。想要求出这样的 Border，我们将 $\operatorname{pre}(s,2^{i-1})$ 提出来，在 $\operatorname{suf}(s,2^i)$ 里面匹配；对 $\operatorname{suf}(s,2^{i-1})$ 提出来做一样的事情。不难发现 Border 就是对两个匹配匹配上的位置求交。注意到 Weak Periodicity Lemma 里面提到的一个引理，不难发现这两个匹配匹配出来的位置是两个等差数列，要做的是求出这个等差数列。而一个等差数列最多三项就可以完全描述（第一项，第二项和最后一项），要求的是第一次，第二次和最后一次匹配。

于是需要实现一个 $\operatorname{succ}(v,i)$ 表示字符串 $v$ 在 $s$ 中，位置不小于 $i$ 的第一次匹配；类似地实现 $\operatorname{pred}(v,i)$ 表示字符串 $v$ 在 $s$ 中，位置不大于 $i$ 的第一次匹配。保证 $|v|$ 可表示为 $2^x$。

而就是因为这个可表示为 $2^x$，我们可以先对整个串求一个后缀数组并记录下每个后缀按前 $2^k$ 个字符为关键字排序后的结果。那么 $\operatorname{succ}(v,i)$ 和 $\operatorname{pred}(v,i)$ 本质上就是提出一个区间出来玩二分，非常 naive。

$[2^k,|s|)$ 和 $[2^{i-1},2^i)$ 在思考之后知道本质相同。

于是有了 $O(n \log^2 n)$ 的做法。

瓶颈在等差数列求交上。一般的问题没有优化思路，我们将其放到字符串上，代用字符串的性质考虑。在这里抄鏼的 ppt。

> 引理：四个字符串满足 $|x_1| = |y_1| \geq |x_2| = |y_2|$，且 $x_1$ 在 $y_2y_1$ 中至少匹配 $3$ 次，则 $per(x_1)=per(y_1)$。   
  证明：否则假设 $per(x_1) \geq per(y_1)$，考虑 $x_1$ 在 $y_2y_1$ 最右边一次匹配，设其与 $y_1$ 重叠部分为 $z$，则 $|z| \geq 2per(x_1)>per(x_1)+per(y_1)$，则 $z$ 存在周期 $d=\gcd(per(x_1),per(y_1))$，显然 $d|per(x_1)$，因此 $d$ 为 $x_1$ 的周期，但是 $d<per(x_1)$，矛盾。
  
证明其实有点不说人话……

然后是，这个性质必须要在保证合并的两个等差数列都至少有三项，不然的话就直接暴力合并就行了。

于是整个问题被优化至 $O(n \log n)$。下面的代码实现是 $O(n \log^2 n)$ 的（因为我的后缀数组莫名其妙的就死了……所以把后缀数组求出来之后暴力球的每次匹配后的状态，等差数列优化求交的部分是写了的。并且应用哈希表优化的地方是直接暴力二分的，所以是 $O(n \log^2 n)$）。

似乎用不着什么哈希表？

```cpp
/*
他决定要“格”院子里的竹子。于是他搬了一条凳子坐在院子里，面对着竹子硬想了七天，结果因为头痛而宣告失败。
他决定要“格”金策字符串选讲里面的 Interval Pattern Matching。于是他搬了一份 std 坐在机房里，面对着机房硬想了一天，结果因为 Para 太引荐而宣告失败。
DONT NEVER AROUND . //
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const int MAXN=200005,MxLgs=19;
int n,Q;
char str[MAXN];
struct SuffixArray{
	struct STtable{
		int lgstr[MAXN],f[MxLgs][MAXN];
		void init(int *a)
		{
			for(int i=2;i<=n;++i)	lgstr[i]=lgstr[i>>1]+1;
			for(int i=1;i<=n;++i)	f[0][i]=a[i];
			for(int i=1;i<MxLgs;++i)	for(int j=1;j+(1<<i)-1<=n;++j)	f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
		}
		int query(int l,int r)
		{
			int d=lgstr[r-l+1];
			return min(f[d][l],f[d][r-(1<<d)+1]);
		}
		void debug(){for(int i=1;i<=n;++i)	for(int j=i;j<=n;++j)	write(query(i,j)),putchar(' ');puts("");}
	}st;
	int sa[MAXN],ht[MAXN],cnt[MAXN],x[MAXN],tmp1[MAXN],rk[MAXN],Sigma;
	void MakeSuffix()
	{
		Sigma=128;
		for(int i=1;i<=n;++i)	++cnt[x[i]=str[i]];
		for(int i=2;i<=Sigma;++i)	cnt[i]+=cnt[i-1];
		for(int i=n;i;--i)	sa[cnt[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1)
		{
			int tmp=0;
			for(int i=n-k+1;i<=n;++i)	tmp1[++tmp]=i;
			for(int i=1;i<=n;++i)	if(sa[i]>k)	tmp1[++tmp]=sa[i]-k;
			for(int i=1;i<=Sigma;++i)	cnt[i]=0;
			for(int i=1;i<=n;++i)	++cnt[x[i]];
			for(int i=2;i<=Sigma;++i)	cnt[i]+=cnt[i-1];
			for(int i=n;i;--i)	sa[cnt[x[tmp1[i]]]--]=tmp1[i],tmp1[i]=0;
			swap(x,tmp1);
			tmp=1;
			x[sa[1]]=1;
			for(int i=2;i<=n;++i)	x[sa[i]]=(tmp1[sa[i]]==tmp1[sa[i-1]] && tmp1[sa[i]+k]==tmp1[sa[i-1]+k])?tmp:++tmp;
			if(tmp==n)	break;
			Sigma=tmp; 
		}
	}
	void MakeHeight()
	{
		int k=0;
		for(int i=1;i<=n;++i)	rk[sa[i]]=i;
		for(int i=1;i<=n;++i)
		{
			if(rk[i]==1)	continue;
			if(k)	--k;
			int j=sa[rk[i]-1];
			while(j+k<=n && i+k<=n && str[i+k]==str[j+k])	++k;
			ht[rk[i]]=k;
		}
	}
	int getLCP(int p,int q)
	{
		if(p==q)	return n-p+1;
		p=rk[p],q=rk[q];
		return st.query(min(p,q)+1,max(p,q));
	}
	int compare(int l1,int r1,int l2,int r2)
	{
		assert(r1-l1==r2-l2);
		int len=r1-l1+1,lcp=getLCP(l1,l2);
		if(lcp>=len)	return 0;
		return str[l1+lcp]<str[l2+lcp]?-1:1;
	}
	void init(){MakeSuffix(),MakeHeight(),st.init(ht);}
	void debug(){for(int i=1;i<=n;++i)	write(sa[i]),putchar(i==n?'\n':' ');for(int i=1;i<=n;++i)	write(rk[i]),putchar(i==n?'\n':' ');for(int i=1;i<=n;++i)	write(ht[i]),putchar(i==n?'\n':' ');}
}Sa;
int CmpLen;
bool cmp(int x,int y)
{
	int rt=Sa.compare(x,x+CmpLen-1,y,y+CmpLen-1);
	if(!rt)	return x<y;
	return rt<0;
}
namespace IntervalPatternMatching{
	struct matchSeq{
		int p0,p1,cnt;
		matchSeq(){p0=p1=cnt=0;}
		matchSeq(int a,int b,int c,int type)
		{
			if(type==1)	p0=p1=a,cnt=1;
			else if(type==2)	p0=a,p1=b,cnt=1+int(p0!=p1);
			else	p0=a,p1=b,cnt=c;
		}
		matchSeq(int *a,int c)
		{
			if(c<=0)
			{
				cnt=0;
				return ;
			}
			if(c==1)	p0=p1=a[0];
			else	p0=a[0],p1=a[1],cnt=c;
		}
		inline bool isContain(int x)
		{
			if(!cnt)	return false;
			if(cnt<=2)	return (x==p0 || x==p1);
			x-=p0;
			int d=p1-p0;
			return bool(x%d==0 && x/d>=0 && x/d<cnt);
		}
		inline int getIndex(int x)
		{
			if(!isContain(x))	return -1;
			return (x-p0)/(p1-p0);
		}
		inline int getVal(int id){return p0+id*(p1-p0);}
		inline int getMax(){return getVal(cnt-1);}
		matchSeq operator - (){return matchSeq(-p0,-p1,cnt,3);}
		matchSeq operator + (int d){return matchSeq(p0+d,p1+d,cnt,3);}
		matchSeq operator - (int d){return matchSeq(p0-d,p1-d,cnt,3);}
		inline void debug(){printf("%d %d %d\n",p0,p1,cnt);}
	};
	matchSeq mov(matchSeq seq)
	{
		if(seq.cnt<=1)	return seq;
		int q0=seq.getVal(seq.cnt-1),q1=seq.getVal(seq.cnt-2);
		return matchSeq(q0,q1,seq.cnt,3);
	}
	matchSeq merge(matchSeq u,matchSeq v)
	{
		int tmp[6],cnt=0;
		if(!u.cnt || !v.cnt)	return matchSeq();
		if(u.cnt<3)
		{
			for(int i=0,x=u.p0,d=u.p1-u.p0;i<u.cnt;++i,x+=d)	if(v.isContain(x))	tmp[cnt++]=x;
			return matchSeq(tmp,cnt);
		}
		if(v.cnt<3)
		{
			for(int i=0,x=v.p0,d=v.p1-v.p0;i<v.cnt;++i,x+=d)	if(u.isContain(x))	tmp[cnt++]=x;
			return matchSeq(tmp,cnt);
		}
		assert(u.p1-u.p0==v.p1-v.p0);
		int l=u.getIndex(v.p0);
		if(l==-1)	return matchSeq();
		int r=l+v.cnt;
		r=min(r,u.cnt);
		if(l>=r)	return matchSeq();
		return matchSeq(u.getVal(l),u.getVal(l+1),r-l,3);
	}
	int f[MxLgs][MAXN];
	void init()
	{
		Sa.init();
		for(int k=0;(1<<k)<=n;++k)
		{
			CmpLen=(1<<k);
			for(int i=1;i+CmpLen<=n+1;++i)	f[k][i]=i;
			sort(f[k]+1,f[k]+1+(n-CmpLen+1),cmp);
		}
	}
	#define mp make_pair
	pair<int,int> getRange(int s,int k)
	{
		int len=(1<<k),L=-1,R=-1;
		int l,r;
		l=1,r=n-len+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(Sa.compare(s,s+len-1,f[k][mid],f[k][mid]+len-1)>0)	l=mid+1;
			else	r=(L=mid)-1;
		}
		l=1,r=n-len+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(Sa.compare(s,s+len-1,f[k][mid],f[k][mid]+len-1)>=0)	l=(R=mid)+1;
			else	r=mid-1;
		}
		return mp(L,R);
	}
	#undef mp
	int succ(int s,int k,int i,int L,int R)
	{
		if(L>R)	return MAXN*2;
		int l=L,r=R,ans=R+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(f[k][mid]>=i)	r=(ans=mid)-1;
			else	l=mid+1;
		}
		if(ans>R)	return MAXN*2;
		return f[k][ans];
	}
	int pred(int s,int k,int i)
	{
		int L,R;
		pair<int,int> tmp=getRange(s,k);
		L=tmp.first,R=tmp.second;
		if(L>R)	return -MAXN;
		int l=L,r=R,ans=L-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(f[k][mid]<=i)	l=(ans=mid)+1;
			else	r=mid-1;
		}
		if(ans<L)	return -MAXN;
		return f[k][ans];
	}
	matchSeq query(int l,int r,int s,int k)
	{
		int len=(1<<k);
		pair<int,int> tmp=getRange(s,k);
		int L=tmp.first,R=tmp.second;
		int q0=succ(s,k,l,L,R);
		if(q0+len-1>r)	return matchSeq();
		int q1=succ(s,k,q0+1,L,R);
		if(q1+len-1>r)	return matchSeq(q0,q0,1,1);
		int qx=pred(s,k,r-len+1);
		matchSeq ret=matchSeq(q0,q1,MAXN,3);
		ret.cnt=ret.getIndex(qx)+1;
		return ret;
	}
	void debug(){for(int i=0;i<MxLgs;++i,puts(""))	for(int j=1;j<=n;++j)	printf("%d ",f[i][j]);puts("");}
}
#define IPM IntervalPatternMatching
int query(int l,int r)
{
	int Slen=(r-l+2)/2,lim=0;
	while((1<<lim)<Slen)	++lim;
	for(int i=lim;~i;--i)
	{
		int len=min(r-l,1<<(i+1)),slen=(1<<i);
		IPM::matchSeq st1=IPM::query(l,l+len-1,r-slen+1,i),st2=IPM::query(r-len+1,r,l,i);
		st1=st1-l+slen;
		st2=-IPM::mov(st2)+r+1;
		st1=IPM::merge(st1,st2);
		if(st1.cnt)	return st1.getMax();
	}
	return int(str[l]==str[r] && (l^r));
}
int main(){
	scanf("%s",str+1),n=strlen(str+1);
	IPM::init();
	Q=read();
	while(Q-->0)
	{
		int l=read(),r=read();
		write(query(l,r)),puts("");
	}
	return 0;
}
```


---

## 作者：ღꦿ࿐ (赞：9)

[在我的博客查看](https://www.cnblogs.com/Dreamerkk/p/17959651)

一种很好写的 $O(n\log ^2 n)$ 的做法和处理技巧，不需要会任何 border series 的知识，只需要会 SAM 和一些基础数据结构就行。 

考虑 $\text{MaxBorder}(l,r)$ 可以被写成即找到最大的 $p \leq r - l$ 满足 $S[l:l+p]=S[r-p+1:r]$，子串相等并不是我们喜欢见到的形式，考虑写成前缀的形式，即需要找到最大的 $p \leq r - l$ 满足 $\text{lcs}(l+p,r)\geq p$。

建出 SAM 的 parent 树即前缀树，那么 $\text{lcs}$ 可以被表示为前缀树上的 $\text{LCA}$ 的 $\text {len}$ **和 $r-l+1$ 取 $\min$** 后的值。


于是我们有了一种 SAM 的暴力做法：在前缀树上往上跳，对于所有满足 $\text{len} \leq r - l$ 的点（这些点的 $\text{lcs}$ 长度就是 $\text{len}$）考虑其为 $\text{LCA}$ 时的最大 $p$，即查询其 $\text{endpos}$ 集合中 $[l,l+\text{len}-1]$ 的最大的 $\text{endpos}$，这个位置 $p$ 代表的前缀在 $[l,p]$ 内的部分就（可能）是一个最大 $\text{Border}$。
 

那些 $\text{len}>r-l$ 的节点作为 $\text{LCA}$ 不应该被考虑，因为这些节点的意义是“整个串都是 $\text{lcs}$”，显然这个串本身不应该被考虑进自己的 $\text{Border}$ 中。又因为前缀树上的 $\text{len}$ 是单调的，可以直接倍增找第一个 $\text{len} \leq r - l$ 的点。

---

我们现在将字符串的问题转化成了前缀树上的问题，如下：

- 前缀树上每个点可能对应着一个或没有的 $\text{endpos}$ 位置。

- 每次给出 $(u,l)$，对于点 $u$ 到根的链上的所有点 $x$ 查询所有 $\text{lca}(u,P)=x$ 的点的 $P$ 的 $\text{endpos}$ 在 $[l,l+\text{len}(x)-1]$ 内的最大值。


- 因为 $\text{len}$ 的单调性，我们在高于 $\text{LCA}$ 的地方统计到一个点不会影响答案（更短的 $\text{lcs}$ 不会使得它更优），所以我们只需要保证最近公共祖先被考虑到即可，不用担心考虑到更高的公共祖先。



直接可持久化线段树合并维护 $\text{endpos}$ 暴力跳 parent 树查询 $[l,l+\text{len}-1]$ 树高是 $O(n)$，复杂度不正确。

因为是和 $\text{LCA}$ 相关的信息，考虑树分治，分别考虑 $u$ 作为 $\text{LCA}$ 的轻子树和重子树时的情况。

$u$ 作为轻子树仅有 $O(\log n)$ 次，直接在这些位置的维护 $\text{endpos}$ 的线段树上查询即可。

$u$ 作为重子树：这个时候我们询问的是一条重链的前缀，这条重链上可能和它产生贡献的点只有**这个前缀和这个前缀轻子树里边的点**。因为轻子树的大小和是 $O(n\log n)$ 的，对于每条重链直接遍历轻子树是可以接受的。

因为是前缀询问所以考虑把问题离线，询问挂在对应的点上，在对应的位置加入轻子树的点，考虑一个和这条重链的 $\text{LCA}$ 在 $x$ 处的轻子树内 $\text{endpos}$ 位置 $P$，在 $\text{LCA}$ 处询问 $[l,l+\text{len}(x)-1]$ 能够包含这个点的 $l$ 就在范围 $[P-\text{len}(x)+1,P]$ 内。

区间取 $\max$，单点查即可。
 

---

回顾本题，我们本质上是使用了**重链剖分作为平衡复杂度的方式**

- 在轻子树从下到上维护，基于作为轻子树的询问考虑被询问对象。

- 在重链从上到下扫描，基于作为轻子树的被询问对象考虑向询问贡献。

因为轻子树的大小和是 $O(n\log n)$，两侧使用的数据结构都是 $O(\log n)$ 的，所以时间复杂度 $O(n\log ^2 n)$。


[完整代码](https://www.luogu.com.cn/paste/w59iu08k)

---

## 作者：蒟蒻君HJT (赞：8)

这个题大概确实算比较困难的后缀字符串题目了。链分治这种方法以前没见过真的想不出来。~~反正我是贺的题解。~~

**个人评价：写出了做题思考的心路历程，逐渐导向正解，可能对像我一样的字符串萌新更友好一些。**

题意：给定字符串 $s$，$q$ 次询问某一子串的最长 Border 长度。

考虑怎么把题意转化成 SAM 的语言。对 $s$ 建 SAM ，每次询问找到子串 $[1,r]$ 的位置 $x$，那么我们知道，答案肯定是 $x$ 往上跳转后缀链接若干次所到的节点 $y$，$y$ 所代表的等价类中的某一子串（不一定是最长的）。假设答案所代表的 Border 是 $s_{l,l+1,...i}$，则需要满足的要求是：$lcs(i,r)\geq i-l+1,l\leq i \leq r - 1$，且 $i$ 最大。

先用线段树合并求出每个节点所代表的 endpos 集合，那么暴力的做法就是在 link 树上往上爬，并分别在每个节点 $y$ 上求出区间 $[l,l-1+len_y]$ 的最大值就能得出我们要的 $i$。

这个复杂度是有问题的，因为 link 树的深度没有保证。如何做出一定优化呢？

让我们来看一下另外一种做法。首先把每个询问挂在插入 $s_r$ 时的结点上（即这个节点包括了 $s_{1,2,...r}$ 这个前缀）。然后考虑对于每个结点，$lcs(i,r)$ 肯定是它的某个祖先（不能是自身，不过这是不重要的细节）那么我们直接深度优先搜索 link 树，在从结点 $x$ 往儿子结点 $v$ 下搜索的过程中，考虑 $x$ 作为这个 $lcs(i,r)$ 的时候，有用的 $i$ 就是 $x$ 除了 $v$ 子树以外所有子树的信息。于是，我们可以在刚进入 $x$ 的时候，将 $x$ 子树中的结点搜索一遍全部加入一颗维护区间内 $i-lcs(i,r)$ 最大值的线段树，进入儿子时再临时删去这个儿子中的所有结点，回溯时再加入，就可以在遇到每个询问时，在线段树上二分做出这道题目了。

很遗憾，这种做法的复杂度是 $O(\log n\cdot \sum)$， $\sum$ 是所有子树的大小之和，可以达到 $n^2$ 级别，所以按道理来说也是错误的。

但是，可以用第一种方法 $+$ 轻重链剖分优化第二种方法。

首先，对 link 树进行轻重链剖分。我们先证明轻子树的大小之和不超过 $n\log n$，原因是每个点的对总和的贡献即为它到根节点的路径上经过的轻边数量，这显然是 $\log n$ 的，所以轻子树的大小之和就有保证。

这有什么用处呢？对于一个询问，子串 $[1,r]$ 的位置预处理出来是 $x$，然后将它到根节点的路径进行剖分，剖成若干重链，并把询问挂在每一条重链第一次被到达的位置。

这时候，离线后从上往下搜索每条重链，将重链上的每个点和它的所有轻子树的信息暴力搜索，加入线段树，套用第二种方法解决：对于每条零散的重链，非底端的点作为 $lcs(i,r)$ 的话， $i$ 只能是重链上的点或轻子树中的点，已经被考虑掉了；唯一漏掉的是底端的点作为 $lcs(i,r)$ 的情况，每个询问中这种情况只会出现 $O(\log n)$ 次，所有只需要直接对 link 树跑一遍线段树合并，显式地维护出每个点所代表的 endpos 集合，查询区间最大值并判断合法性即可。所以这个地方用平衡树的启发式合并好像也可以。

由于轻子树大小之和有保证，而每个询问特殊处理的点也很有限，所以总时间复杂度是 $O((n+q)\log^2n)$，用一些线段树合并方面的技巧，空间复杂度可以做到线性。

代码：

[差点突破码长记录](https://www.luogu.com.cn/paste/7famymq9)

---

## 作者：Mobius127 (赞：7)

基本子串结构做法。

[题传](https://www.luogu.com.cn/problem/P4482)

[推荐阅读](https://www.cnblogs.com/sizeof127/articles/17579027.html)

对正反串分别建立 SAM（以下简称正反 SAM）。

我们尝试为每个本质不同子串一种标记方式，对反 SAM 的 parent 树重链剖分（若有子树相同 size 优先选择最后一次出现位置更晚的那个），对于反串 SAM 上的每个结点 $a$，$a$ 所代表的 startpos 等价类的串，我们以二维坐标表示它们：第一维是 $a$ 所在重链链底的 startpos（SAM 的性质保证了叶子的 startpos 大小为 1），第二维是自己的串长。

通过这样的编号方式，结合基本子串结构相关知识，可以导出以下结论：

1. 对于反串 SAM 的一个结点，其代表的所有等价类在 $xOy$ 平面上为一条竖线段。

1. 对于正串 SAM 的一个结点，其代表的所有等价类在 $xOy$ 平面上为一条斜线段。

1. 对于反串 SAM 的任意一条由上至下的链，其代表的所有等价类在 $xOy$ 平面上仍为一条竖线段。

考虑同时对正 SAM parent 树做树链剖分，区间 border 即为 $s[l, r]$ 在正反 SAM 上的结点到链的一个信息交。同时从正反 SAM 的 parent 树向上跳重链，显然两边的 $O(\log n)$ 条重链只会有 $O(\log n)$ 对有交集。现在问题转化成求正反 SAM parent 树的中的两条重链（的前缀）的交集信息。

将询问挂在正串 SAM 的重链上，离线后枚举每条重链，问题相当于加入 $O(n)$ 条斜线段，$O(q\log n)$ 次查询一条竖线段和其它斜线段的交点的纵坐标最大值。

重新设置坐标，横坐标不变，纵坐标减去原来的横坐标，那么加入的斜线段变成横线段，询问仍然是竖线段。对新的横坐标扫描线，线段树查询区间最靠右不为 1 点即可。复杂度 $O((n+q\log n)\log n)$。



### Code:

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <vector>
#include <queue>
#include <bitset>
#include <assert.h>
#define mcy(arra, arrb) memcpy(arra, arrb, sizeof(arra))
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using namespace std;
typedef long long ll;
typedef pair <int, int> Pii;
const int INF=0x3f3f3f3f;
const int cp=998244353;
inline int mod(int x){return x+(x<0?cp:0)-(x>=cp?cp:0);}
inline void plust(int &x, int y){x=mod(x+y);return ;}
inline void minut(int &x, int y){x=mod(x-y);return ;}
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a, int b=cp-2){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%cp)
		if(b&1) ret=1ll*ret*a%cp;
	return ret;
}
const int N=2e5+5;
const int M=N<<1;
struct SAM{
	int tr[M][26], len[M], fa[M][21], ndc, lst;
	inline int clr(int x){len[x]=fa[x][0]=0;mcy(tr[x], tr[0]);return x;}
	inline int rmk(){return lst=clr(ndc=1);}
	inline int insert(char cc){
		int p=lst, cur=clr(++ndc), c=cc-'a';len[cur]=len[p]+1;
		for(; p&&!tr[p][c]; p=fa[p][0]) tr[p][c]=cur;int q=tr[p][c];
		if(!q) fa[cur][0]=1;else if(len[p]+1==len[q]) fa[cur][0]=q;
		else{
			int nex=clr(++ndc);len[nex]=len[p]+1, fa[nex][0]=fa[q][0], mcy(tr[nex], tr[q]);
			for(; p&&tr[p][c]==q; p=fa[p][0]) tr[p][c]=nex;fa[q][0]=fa[cur][0]=nex;
		}
		return lst=cur;
	}
	vi G[M];int mxp[M], pos[N], siz[M], son[M], top[M], edr[M];
	void dfs(int x){
		for(int i=1; i<=20; ++i) fa[x][i]=fa[fa[x][i-1]][i-1];int y;siz[x]=1;
		for(auto v:G[x]) dfs(v), siz[x]+=siz[v], mxp[x]=max(mxp[x], mxp[v]),
		y=son[x], son[x]=(siz[y]==siz[v])?(mxp[y]<mxp[v]?v:y):(siz[y]<siz[v]?v:y);
	}
	int id[M], cnt, bac[M], L, R;
	void dfs(int x, int rt){
		top[x]=rt;if(son[x]) dfs(son[x], rt);edr[x]=son[x]?edr[son[x]]:mxp[x];
		for(auto v:G[x]) if(!top[v]) bac[id[v]=++cnt]=v, dfs(v, v), 
		L=min(L, len[x]+1-edr[v]), R=max(R, len[v]-edr[v]);
	}
	void build(char *str, int len){
		L=INF;rmk();for(int i=1; i<=len; ++i) mxp[pos[i]=insert(str[i])]=i;
		for(int i=2; i<=ndc; ++i) G[fa[i][0]].pb(i);dfs(1), son[1]=0;dfs(1, 1);
	}
	inline int mnl(int x){return len[fa[x][0]]+1;}
	inline int find(int x, int y){
		int u=pos[y], k=y-x+1;for(int i=20; i>=0; --i) 
		if(len[fa[u][i]]>=k) u=fa[u][i];return u;
	}
}A, B;
namespace SegmentTree{
	int L, R, mx[M<<2];
	void init(int l, int r){L=l, R=r;}
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	void modify(int k, int l, int r, int x, int v){
		if(l==r) return (void)(mx[k]+=v);
		if(x<=mid) modify(ls, l, mid, x, v);
		else modify(rs, mid+1, r, x, v);
		mx[k]=max(mx[ls], mx[rs]);
	}
	void update(int p, int v){modify(1, 1, R-L+1, p-L+1, v);}
	int query(int k, int l, int r, int x, int y){
		if(!mx[k]||x>r||y<l) return -INF;if(l==r) return mid+L-1;
		int t=query(rs, mid+1, r, x, y);return (t!=-INF)?t:query(ls, l, mid, x, y);
	}
	int qry(int l, int r){return query(1, 1, R-L+1, l-L+1, r-L+1);}
	#undef ls
	#undef rs
	#undef mid
}
char s[N];int n, m, ans[N];
struct node{int qid, rid, riq, len;};vector <node> Q[M];
inline void wrk(int id, int l, int r){
	int u=A.find(l, r), v=B.find(n-r+1, n-l+1);
	for(u=A.fa[u][0], v=B.fa[v][0]; u!=1&&v!=1; ){
		int fu=A.top[u], a=A.mnl(fu), b=A.len[u];
		int fv=B.top[v], c=B.mnl(fv), d=B.len[v];
		Q[A.id[fu]].pb((node){id, fv, v, min(r-l, A.len[u])});
		if(a<c) v=B.fa[fv][0];else u=A.fa[fu][0];
		//[a, b] [c, d] [a, c b d]
	}
}
struct seg{int d, x, y, op, qid;};
inline void slv(int lid){
	vector <seg> vec;
	for(int x=A.bac[lid]; x; x=A.son[x]){
		// printf("-->%d ", x);
		int mnl=A.mnl(x), r=A.mxp[x], l=r-mnl+1, u=B.find(n-r+1, n-l+1);
		int linknxt=B.edr[u], k=mnl-linknxt;//[x=linknxt, y=len[x]-k]
		assert(linknxt<=A.len[x]-k);
		vec.pb((seg){linknxt-1, k, k, -2});vec.pb((seg){A.len[x]-k, k, k, 0});
	}
	for(auto v:Q[lid]){
		int x=B.edr[v.rid], l=B.mnl(v.rid), r=min(B.len[v.riq], v.len);
		if(l<=r) vec.pb((seg){x, l-x, r-x, v.qid});\
	}
	sort(vec.begin(), vec.end(), [&](seg a, seg b){if(a.d==b.d) return a.op<b.op;return a.d>b.d;});
	for(auto v:vec){
		if(v.op<=0) SegmentTree :: update(v.x, v.op+1);
		else ans[v.op]=max(ans[v.op], v.d+SegmentTree :: qry(v.x, v.y));
	}
}
signed main(){
	scanf("%s", s+1);n=strlen(s+1);
	A.build(s, n);reverse(s+1, s+n+1);B.build(s, n);m=read();
	for(int i=1, l, r; i<=m; ++i) l=read(), r=read(), wrk(i, l, r);
	SegmentTree :: init(-n-4, n+4);for(int i=1; i<=A.cnt; ++i) slv(i);
	for(int i=1; i<=m; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

一些实现细节：

我实际上写的重剖是拿在原串中最早出现的重儿子，是本质相同的。

当询问的是重链前缀时，需要对长度进行额外限制。


---

## 作者：lzyqwq (赞：5)

五倍经验。

![](https://cdn.luogu.com.cn/upload/image_hosting/ppsdoic3.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)

提供一个 **不需要用到十级算法** 且 **空间线性** 的 $2\log$ 可爱 **后缀数组** 做法！

**[P4482 [BJWC2018] Border 的四种求法](https://www.luogu.com.cn/problem/P4482)**

> - 给出字符串 $s$，$q$ 次询问 $l,r$，求 $s[l,r]$ 的 Border 长度。
> - $|s|,q\le 2\times 10^5$。

记 $n=|s|$。

考虑套用 [CF1098F Ж-function](https://www.luogu.com.cn/article/9pk3x1uu) 的做法，对于每次询问相当于求 $(l,r]$ 中最小的 $p$，使得 $|\text{LCP}(s[l,n],s[p,n])|\ge r-p+1$。那么答案为 $r-p+1$。

后缀排序求出 $\text{height}$ 数组，将 $\text{LCP}$ 转化为区间最小值。考虑对于 $\text{rk}_p<\text{rk}_l$ 和 $\text{rk}_p>\text{rk}_l$ 的部分分别求解。

以后面那种为例。考虑求满足如上条件的后缀的 **排名** 中，$\text{sa}$ 的最小值。相当于要求在满足 $w>\text{rk}_l$，$\min\limits_{\text{rk}_l< i\le w}\text{height}_i\ge r-\text{sa}_w+1$ 且 $l<\text{sa}_w\le r$ 的 $w$ 中，$\text{sa}_w$ 的最小值。

考虑离线，将询问挂在 $\text{rk}_l$ 上，对 $\text{height}$ 数组序列分治。记当前分治区间为 $[L,R]$，中点 $m=\left\lfloor\dfrac{L+R}{2}\right\rfloor$。考虑右半边对左半边的贡献。

对于右半边的一个位置 $i$，记 $k_i=\min\limits_{m+1\le j\le i}\text{height}_j$。对于左半边，从右往左扫描 $i$，维护 $\text{mn}=\min\limits_{i<j\le m}\text{height}_j$，同时更新挂在她上的询问的答案。则 $\min\limits_{i<x\le w}\text{height}_w$ 可以表示成 $\min\{\text{mn},k_w\}$。

考虑拆 $\min$。对于 $\text{mn}\le k_w$ 的部分，要求满足 $\begin{cases}l<\text{sa}_w\le r\\r-\text{sa}_w+1\le \text{mn}\end{cases}$ 的 $w$ 中，$\text{sa}_w$ 的最小值。这是关于 $k_w$ 和 $\text{sa}_w$ 两维限制的偏序问题。

对于 $\text{mn}>k_w$ 的部分，要求满足 $\begin{cases}l<\text{sa}_w\le r\\r-\text{sa}_w+1\le k_w\end{cases}$ 的 $w$ 中，$\text{sa}_w$ 的最小值。这是关于 $k_w,\text{sa}_w,\text{sa}_w+k_w$ 三维限制的偏序问题。

小 L 发现这题不像 [CF1098F Ж-function](https://www.luogu.com.cn/article/9pk3x1uu) ，求的是个数可以差分和容斥。如果直接做要 $\log$ 满天飞了！虽然 $3\log$ 貌似也能过，但是小 L 是可爱的女孩子，她不喜欢这样丑陋的做法。

考虑改变思路，能否转化成求个数的问题然后套用 [CF1098F Ж-function](https://www.luogu.com.cn/article/9pk3x1uu) 的做法？考虑求 $l<\text{sa}_w\le x$ 的范围内满足条件的排名个数，则最小的 $\text{sa}_w$ 就是最小的使得满足条件排名个数不为 $0$ 的 $x$。

考虑如何求个数。对于 $\text{mn}\le k_w$ 的部分，要求满足 $\begin{cases}l<\text{sa}_w\le x\\r-\text{sa}_w+1\le \text{mn}\end{cases}$ 的 $w$ 个数；对于 $\text{mn}>k_w$ 的部分，要求满足 $\begin{cases}l<\text{sa}_w\le x\\r-\text{sa}_w+1\le k_w\end{cases}$ 的 $w$ 个数。后者是三维数点，考虑继续简化。

考虑容斥，用满足 $\begin{cases}\text{mn}>k_w\\l<\text{sa}_w\le x\\r-\text{sa}_w+1\le \text{mn}\end{cases}$ 的 $w$ 个数减去 $\begin{cases}\text{mn}>k_w\\l<\text{sa}_w\le x\\k_w< r-\text{sa}_w+1\le\text{mn}\end{cases}$ 的 $w$ 个数。前者可以和 $\text{mn}\le k_w$ 的部分合并转化成全局 $r-\text{sa}_w+1\le \text{mn}$ 个数；对于后者，我们发现满足第三个条件一定满足第一个条件，因此进一步转化为求 $\begin{cases}l<\text{sa}_w\le x\\k_w< r-\text{sa}_w+1\le\text{mn}\end{cases}$ 的个数，这样她就是关于 $\text{sa}_w$ 和 $\text{sa}_w+k_w$ 两维的二维数点了！

将转化后的限制整理一下，即加上 $\max\{r-\text{mn},l\}+1\le \text{sa}_w\le x$ 的 $w$ 个数再减去 $\begin{cases}\max\{r-\text{mn},l\}+1\le \text{sa}_w\le x\\\text{sa}_w+k_w\le r\end{cases}$ 的 $w$ 个数。

到这里，由于满足条件的 $w$ 个数是随 $x$ 增加非降的，朴素的想法是考虑二分 $x$，然后按照上述方式数点。但是仍是 $3\log$，还是不优雅。但是小 L 发现要求的 $\text{sa}_w$ 还出现在限制中，并且加上、减去的部分对于 $\text{sa}_w$ 的限制还是相同的。可以考虑利用这一点性质。

发现二分和数据结构契合的不是很好，考虑 **直接在数据结构上二分**。维护两棵线段树 $t_1,t_2$。$t_1$ 是全局 $\text{sa}_w$ 的权值线段树，$t_2$ 是满足 $\text{sa}_w+k_w\le r$ 的 $w$ 的 $\text{sa}_w$ 的权值线段树，均维护每个权值的出现次数。

$t_1$ 直接在分治开始维护好；$t_2$ 考虑将所有排名按照 $\text{sa}_w+k_w$ 排序，所有询问按照 $r$ 排序。按顺序处理询问，满足条件的 $w$ 排序后一定构成一段前缀。由于 $r$ 已经递增，因此前缀长度即前缀末尾不降。每到一个新的询问时，向右扩展一段合法的 $w$ 然后在 $t_2$ 上加入她们的 $\text{sa}_w$ 即可。这个过程类似双指针，每个 $w$ 只会被扫一次。

考虑将线段树上表示 $[\max\{r-\text{mn},l\}+1,r]$ 的 $\mathcal{O}(\log n)$ 个区间单独拉出来并从左到右存好。然后按顺序遍历这些区间。如果 $t_1$ 和 $t_2$ 中这一段区间权值出现次数相同，则答案不在这一段中，因为对于右端点代表的 $x$，两者相减之后个数为 $0$；对于更左边的 $x$，根据单调性得知她们都不合法。

否则，设这个区间为 $[\text{ql},\text{qr}]$，答案一定 $\le\text{qr}$。在以表示这个区间的结点为根的 **整棵子树** 上线段树二分即可。若 $t_1$ 左儿子权值出现次数大于 $t_2$，递归左儿子求解，不然递归右儿子求解。

对于这个过程，仅有枚举到的最后一个区间需要 $\mathcal{O}(\log n)$ 时间的递归求解，之前的 $\mathcal{O}(\log n)$ 个区间只是用到了子树根的信息就跳过了，每个都是 $\mathcal{O}(1)$ 时间。因此这个过程的时间复杂度是 $\mathcal{O}(\log n)$ 的。

~~其实可以直接用区间中线段树二分的写法，但小 L 觉得那样比较丑陋。~~

这样就可以计算 $\text{rk}_p>\text{rk}_l$ 的部分的贡献了。

$\text{rk}_l>\text{rk}_p$ 的部分在分治时考虑左半边对右半边的贡献，类似上面转化成偏序问题然后同样排序再线段树二分做即可。注意 $\text{height}$ 最小值的区间是 **左开右闭** 的。

最后来个整个做法的正经时间复杂度分析吧。分治一共进行 $\mathcal{O}(\log n)$ 层，每层的规模总和为 $\mathcal{O}(n)$。对于每一层，每个位置在线段树的修改时被访问 $\mathcal{O}(1)$ 次，贡献 $\mathcal{O}(n\log n)$ 的时间复杂度；每个询问同样被访问 $\mathcal{O}(1)$ 次 ，贡献 $\mathcal{O}(q\log n)$ 的时间复杂度；这一层的每个区间都要对询问和修改排序，两者总规模分别为 $\mathcal{O}(n)$ 和 $\mathcal{O}(q)$，因此贡献的时间复杂度分别为 $\mathcal{O}(n\log n)$ 和 $\mathcal{O}(q\log q)$。

认为 $\mathcal{O}(n)=\mathcal{O}(q)$，总时间复杂度为 $\mathcal{O}\left(n\log^2 n\right)$，空间复杂度为 $\mathcal{O}(n)$。可以接受。

**[AC Link](https://www.luogu.com.cn/record/173285501)**

**[AC Code](https://www.luogu.com.cn/paste/hmis2828)**

话说 $1\log$ 是不是只能用 Border 理论那套东西才能做到啊，字符串萌新爬了。

---

## 作者：hs_black (赞：5)

子串周期查询，给定一个串，每次询问一个子串的最长 border。

这里介绍一种点分治 + 后缀自动机 + 线段树的做法。

字符串就想后缀自动机，对于询问串 $s[l,r]$，在后缀自动机上找到 $r$ 所在的节点向上跳，我们需要找到满足条件 $p - len[Lca(p,ed[r])] + 1 \le l$ 和 $p < r$ 最大的 $p$。

你可以暴力跳 + 线段树查询，这样复杂度显然是不对的。

考虑树分治，这里我们选择点分治来解决，设分治重心为 $x$，因为是有根树，我们分为上半部分和下半部分。

考虑下半部分对整体的贡献，我们可以将下半部分所有的位置 $u$ 插入到线段树上，那么 $u$ 和另一个点 $v$ 的 $LCA$ 就是 $v$ 和 $x$ 的 $LCA$ （如果 $u$，$v$ 在同一子树我们算的贡献不会对答案产生影响，因为错算的 $len[LCA]$ 更小），现在我们就是预处理 p，然后枚举 $len[Lca(p,ed[r])]$，在线段树上查满足条件最大的 p 即可。

另外一方面，我们需要考虑上半部分对下半部分的贡献，那么插入的时候顺便枚举 $len[Lca(p,ed[r])]$，查询的时候直接线段树二分得到最大的 p 即可。

常数略大，但是空间达到了优秀的 $\Theta(N\Sigma)$ 

```cpp
#include <bits/stdc++.h>
#define MP make_pair
#define ll long long
#define fi first
#define se second
using namespace std;
template <typename T>
inline void Mx(T &x, T y) { x < y && (x = y); }

#define ls p << 1
#define rs ls | 1
const int N = 400050;
const int inf = 1145141919;
int mn[N<<1];
void build(int p, int l, int r) { mn[p] = inf; if (l == r) return; int mid = (l + r) >> 1; build(ls, l, mid), build(rs, mid + 1, r); }
void change(int p, int l, int r, int x, int c) {
	if (l == r) return mn[p] = c, void();
	int mid = (l + r) >> 1;
	x <= mid ? change(ls, l, mid, x, c) : change(rs, mid + 1, r, x, c);
	mn[p] = min(mn[ls], mn[rs]);
}

int query(int p, int l, int r, int R, int lim) {
	if (mn[p] > lim) return 0;
	if (r <= R) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (mn[rs] <= lim) return query(rs, mid + 1, r, R, lim);
		return query(ls, l, mid, R, lim); 
	}
	int mid = (l + r) >> 1;
	if (R <= mid) return query(ls, l, mid, R, lim);
	int t = query(rs, mid + 1, r, R, lim); if (t) return t;
	return query(ls, l, mid, R, lim);
}

int len[N], ch[N][26], f[N], cnt = 1, las = 1;
int insert(int c) {
	int p = las, np = las = ++cnt; 
	len[np] = len[p] + 1;
	for (; p && !ch[p][c]; p = f[p]) ch[p][c] = np;
	if (!p) return f[np] = 1, las;
	int q = ch[p][c];
	if (len[p] + 1 == len[q]) return f[np] = q, las;
	int nq = ++cnt; memcpy(ch[nq], ch[q], sizeof(ch[q]));
	len[nq] = len[p] + 1, f[nq] = f[q], f[q] = f[np] = nq;
	for (; ch[p][c] == q; p = f[p]) ch[p][c] = nq;
	return las;
}

int siz[N], Siz, lim, rt, n;
int ans[N], L[N], Ed[N], ed[N], vis[N], dep[N];
int h[N], ne[N<<1], to[N<<1], tot;
void getrt(int x, int fa) {
	siz[x] = 1; int mn = 0;
	for (int i = h[x], y; i; i = ne[i]) {
		if (vis[y = to[i]] || y == fa) continue;
		getrt(y, x), siz[x] += siz[y], Mx(mn, siz[y]);
	}
	Mx(mn, Siz - siz[x]);
	if (mn < lim) lim = mn, rt = x;
}

inline void add(int x, int y) { ne[++tot] = h[x], to[h[x] = tot] = y; }
void Addin(int x, int t) {
	if (Ed[x]) change(1, 1, n, Ed[x], t ? Ed[x] : inf);
	for (int i = h[x], y; i; i = ne[i]) 
		if (!vis[y = to[i]] && dep[y] > dep[x]) Addin(y, t);
}

vector<pair<int, int> > vec[N];
void Check(int x, int L, int fa) {
	if (dep[x] <= dep[L]) L = x;
	if (!len[L]) return;
	for (int i = 0;i < (int)vec[x].size(); ++i) {
		int t = Ed[x] - vec[x][i].fi + 1;
		t = min(t, len[L]);
		Mx(ans[vec[x][i].se], query(1, 1, n, vec[x][i].fi + t - 1, Ed[x] - 1));
	}
	for (int i = h[x], y; i; i = ne[i]) 
		if (!vis[y = to[i]] && y != fa) Check(y, L, x);
}

void Addin2(int x, int L, int fa, int t) {
	if (dep[x] <= dep[L]) L = x;
	if (!len[L]) return;
	if (Ed[x]) change(1, 1, n, Ed[x], t ? Ed[x] - len[L] + 1 : inf);
	for (int i = h[x], y; i; i = ne[i]) 
		if (!vis[y = to[i]] && y != fa) Addin2(y, L, x, t);
}

void Check2(int x) {
	for (int i = 0;i < (int)vec[x].size(); ++i) 
		Mx(ans[vec[x][i].se], query(1, 1, n, Ed[x] - 1, vec[x][i].fi));
	for (int i = h[x], y; i; i = ne[i]) 
		if (!vis[y = to[i]] && dep[y] > dep[x]) Check2(y);
}

void solve(int x, int Sz) {
	lim = Siz = Sz, getrt(rt = x, 0), x = rt;
	vis[x] = 1, Addin(x, 1), Check(x, x, 0), Addin(x, 0);
	if (!vis[f[x]]) Addin2(f[x], f[x], 0, 1), Check2(x), Addin2(f[x], f[x], 0, 0);
	for (int i = h[x], y; i; i = ne[i]) 
		if (!vis[y = to[i]]) solve(y, siz[x] > siz[y] ? siz[y] : Sz - siz[x]);
}

void pre(int x, int fa) {
	dep[x] = dep[fa] + 1;
	for (int i = h[x], y; i; i = ne[i])
		if ((y = to[i]) != fa) pre(y, x);
}

char s[N]; int q;
int main() {
	scanf ("%s", s + 1), n = strlen(s + 1), vis[0] = 1;
	for (int i = 1;i <= n; ++i) Ed[ed[i] = insert(s[i] - 'a')] = i; 
	scanf ("%d", &q);
	for (int i = 1, l, r;i <= q; ++i) {
		scanf ("%d%d", &l, &r), L[i] = l;
		if (l != r) vec[ed[r]].push_back(MP(l, i));
	}
	for (int i = 2;i <= cnt; ++i) add(f[i], i), add(i, f[i]);
	build(1, 1, n), pre(1, 0), solve(1, cnt);
	for (int i = 1;i <= q; ++i) printf ("%d\n", ans[i] == 0 ? 0 : max(0, ans[i] - L[i] + 1));
	return 0;
}
```



---

## 作者：Alex_Wei (赞：5)

> [P4482 [BJWC2018] Border 的四种求法](https://www.luogu.com.cn/problem/P4482)

很有启发性的一道题目，爱来自瓷器。

假设 $n, q$ 同级。

首先建出 $s$ 的 SAM，那么我们希望用一种 SAM 容易刻画的方式描述 border。因为两字符串的 LCS 即它们在 link 树上的 LCA，所以尝试从 LCS 角度描述 border，易知答案为
$$
\max\left(l - 1, \max\limits_{i = l} ^ {r - 1} i[|lcs(s[l, i], s[l, r])| \geq i - l + 1]\right) - l + 1
$$
看起来相当难以维护，因为涉及到 $\mathcal{O}(n ^ 2)$ 种子串。尝试用等价条件简化答案式：

- 由于 $s[l, i]$ 和 $s[l, r]$ 长度均不小于 $i - l + 1$，所以可用 $pref_i$ 和 $pref_r$ 代替。
- 由于当 $i < l$ 时 $\max$ 必然取到 $l - 1$，所以下界 $l$ 可改为 $1$，这样 $i$ 就是一段前缀。但最后我们会发现这并没有什么卵用。

重写一下答案式，令 $ed_i$ 表示 $pref_i$ 在 SAM 上对应节点，则单组询问的答案可表示为
$$
\max\left(l - 1, \max\limits_{i = 1} ^ {r - 1} i [\mathrm{len}(lca(ed_i, ed_r)) \geq i - l + 1]\right) - l + 1
$$
其中 $\mathrm{len}(x)$ 即 $x$ 所表示的最长子串长度。

容易发现只需对每组询问求出 $\max\limits_{i = 1} ^ {r - 1} i [\mathrm{len}(lca(ed_i, ed_r)) \geq i - l + 1]$。这种形式让我们想到了 [[LNOI2014] LCA](https://www.luogu.com.cn/problem/P4211)，但是很遗憾，我们无法套用那题的方法解决，因为外层是 $\max$ 而非和式。

接下来给出一个非常厉害的技巧：注意到一次询问涉及到的节点均为 $ed_r$ 的祖先，链查询在树上前缀和不管用的情况下考虑树上链分治，也就是树剖。从 dsu on tree 角度出发可以得到本质差不多的东西，但鉴于我不太熟悉 dsu on tree 所以会觉得这种技巧很厉害。

对于从 $ed_r$ 到根路径上的一条重链，考虑其上某点 $x$，问题在 $x$ 处相当于查询 $x$ 的轻子树内所有 $ed_i$ 对应的最大的 $i$ 满足 $i < r$ 且 $\mathrm{len}(x) \geq i - l + 1$，变形一下即 $l\geq i - \mathrm{len}(x) + 1$。根据树剖经典结论：所有轻子树大小之和为 $\mathcal{O}(n\log n)$，故所有不同的 $(x, ed_i)$ 对仅有 $\mathcal{O}(n\log n)$ 个。回到整条重链上来，可知问题相当于查询重链一段 **前缀** 上所有点 $x$ 的答案，即对一段前缀做二维数点，即静态三维数点。复杂度摊一下就是 $\mathcal{O}(n\log n)$ 个点的三维数点，很恐怖！

![](https://cdn.luogu.com.cn/upload/image_hosting/mxzwmam1.png)

如图，绿色链是 $ed_r$ 到根的链，实边是重边，虚边是轻边，则当前询问在 $x$ 这条重链上的查询形如：对每个 $x_k$，求其所有轻子树内所有 $ed_i$ 对应的 $i$ 的最大值，满足 $i < r$ 且 $l\geq i - \mathrm{len}(x_k) + 1$。

现在关键问题在于把时间复杂度和代码复杂度降下来（虽然 $\mathcal{O}(n\log ^ 3 n)$ 说不定也能过）。注意到我们只要求最大的符合条件的 $i$ 而不是所有 $i$ 的和，所以可通过二分将一维消掉，即二分 $i$，设当前二分值为 $i'$，则查询所有 $i'\leq j < r$ 的 $j - \mathrm{len}(x_k) + 1$ 的最小值 $v$，若 $v \leq l$ 说明 $i\geq i'$，否则 $i < i'$，这样复杂度不变，但是将一维计数转化成一维判定。用线段树上二分代替上述二分即可做到 $\mathcal{O}(n\log ^ 2 n)$。

仔细思考一下上述操作考虑到了哪些点与 $r$ 之间的贡献。我们发现它多算了一些贡献，又少算了一些贡献：

- 多算的贡献在于考虑路径重链末端（上图中的 $x_3$，而非询问重链末端 $x_4$）的轻子树直接把这条路径末端的前一条轻边 $(x_3, y)$ 的整棵轻子树给算上了，但由于这样只会将 LCA 算浅，使得 LCS 长度即 $\mathrm{len}$ 值算小，更不容易满足条件，所以不会算入不符合条件的点。
- 少算的贡献在于路径重链末端 $x_3$ 的整棵重子树（$x_4$ 的子树）均没有算上。但仅有 $\mathcal{O}(\log n)$ 个这样的子树，所以考虑线段树合并 + 暴力查询。此时 $l$ 和 $\mathrm{len}(x)$ 关于每个 $i$ 为定值，因此限制式形如 $l + \mathrm{len}(x)\geq i + 1$，线段树维护的值从 $i - \mathrm{len}(x_k) + 1$ 变成了 $i + 1$。注意单次查询中 $\mathrm{len}(x)$ 取 $\mathrm{len}(x_3)$，但在 $x_4$ 的子树中查询。

还有最后一个细节：若 $ed_i$ 和 $ed_r$ 有祖先后代关系，该怎么办？由于 $ed_i$ 互不相同，所以考虑新建虚点 $ed'_i$，$ed_i$ 向 $ed'_i$ 连边，然后将 $ed$ 更新成 $ed'$ 即可保证 $ed$ 之间无祖先后代关系。容易发现上述操作不影响答案。

综上，我们以 $\mathcal{O}(n\log ^ 2 n)$ 时间，$\mathcal{O}(n\log n)$ 空间解决了本题。

总结一下这题用到的技巧：

- 将链查询转化为 $\mathcal{O}(\log n)$ 次轻边查询和重链前缀查询。
- 当数点问题求最值且点权等于某一维的值时，可以计数转判定，线段树每个下标表示该维度，区间维护另外某个维度的最值，通过线段树二分下标去掉一个 $\log$。前提：**另外某维的限制只能是前后缀而非区间**。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
bool Mbe;
constexpr int N = 6e5 + 5;
constexpr int S = 26;
constexpr int K = 2e7 + 5;
int cnt = 1, fa[N], len[N], ed[N];
namespace SAM {
  int las = 1, son[N][S];
  void ins(int it) {
    int p = las, cur = ++cnt;
    ed[len[cur] = len[p] + 1] = cur;
    las = cur;
    while(!son[p][it]) son[p][it] = cur, p = fa[p];
    if(!p) return fa[cur] = 1, void();
    int q = son[p][it];
    if(len[p] + 1 == len[q]) return fa[cur] = q, void();
    int cl = ++cnt;
    len[cl] = len[p] + 1;
    memcpy(son[cl], son[q], S << 2);
    fa[cl] = fa[q], fa[q] = fa[cur] = cl;
    while(son[p][it] == q) son[p][it] = cl, p = fa[p];
  }
}

int node, ls[K], rs[K], val[K];
void clear() {
  for(int i = 0; i <= node; i++) ls[i] = rs[i] = 0, val[i] = N;
  node = 0;
}
void modify(int l, int r, int p, int v, int &x) {
  if(!x) x = ++node;
  val[x] = min(val[x], v);
  if(l == r) return;
  int m = l + r >> 1;
  if(p <= m) modify(l, m, p, v, ls[x]);
  else modify(m + 1, r, p, v, rs[x]);
}
int merge(int x, int y) {
  if(!x || !y) return x | y;
  int z = ++node;
  ls[z] = merge(ls[x], ls[y]);
  rs[z] = merge(rs[x], rs[y]);
  return val[z] = min(val[x], val[y]), z;
}
int query(int l, int r, int qr, int lim, int x) {
  if(val[x] > lim) return -1;
  if(l == r) return l;
  int m = l + r >> 1;
  if(m < qr) {
    int res = query(m + 1, r, qr, lim, rs[x]);
    if(res != -1) return res;
  }
  return query(l, m, qr, lim, ls[x]);
}

char s[N];
vector<int> e[N], buc[N], qu[N];
int n, q, R[N], l[N], r[N], ans[N];
int son[N], sz[N], dep[N];
int dn, rev[N], dfn[N], top[N];
void dfs1(int id) {
  sz[id] = 1;
  dep[id] = dep[fa[id]] + 1;
  for(int it : e[id]) {
    dfs1(it), sz[id] += sz[it];
    R[id] = merge(R[id], R[it]);
    if(sz[it] > sz[son[id]]) son[id] = it;
  }
}
void dfs2(int id, int tp) {
  top[id] = tp;
  rev[dfn[id] = ++dn] = id;
  if(son[id]) dfs2(son[id], tp);
  for(int it : e[id]) if(it != son[id]) dfs2(it, it);
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  memset(val, 0x3f, sizeof(val));
  scanf("%s%d", s + 1, &q), n = strlen(s + 1);
  for(int i = 1; i <= n; i++) SAM::ins(s[i] - 'a');
  for(int i = 1; i <= n; i++) e[ed[i]].push_back(++cnt), fa[cnt] = ed[i], ed[i] = cnt; // add fa[cnt] = ed[i]
  for(int i = 1; i <= n; i++) modify(1, n, i, i + 1, R[ed[i]]);
  for(int i = 2; i <= cnt; i++) e[fa[i]].push_back(i);
  dfs1(1), dfs2(1, 1);
  for(int i = 1; i <= n; i++) {
    int x = fa[top[ed[i]]];
    while(x) buc[x].push_back(i), x = fa[top[x]];
  }
  for(int i = 1; i <= q; i++) {
    cin >> l[i] >> r[i];
    if(l[i] == r[i]) continue;
    int x = ed[r[i]];
    while(x) qu[x].push_back(i), x = fa[top[x]];
  }
  for(int i = 1; i <= cnt; i++) {
    if(!son[i]) continue;
    for(int it : qu[i]) ans[it] = max(ans[it], query(1, n, r[it] - 1, l[it] + len[i], R[son[i]]));
  }
  for(int i = 1; i <= cnt; i++) {
    if(top[i] != i) continue;
    int x = i, R = 0;
    clear();
    while(x) {
      for(int it : buc[x]) modify(1, n, it, it - len[x] + 1, R);
      for(int it : qu[x]) ans[it] = max(ans[it], query(1, n, r[it] - 1, l[it], R));
      x = son[x];
    }
  }
  for(int i = 1; i <= q; i++) cout << max(0, ans[i] - l[i] + 1) << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/8/13
Author: Alex_Wei
start coding at 8:25
finish debugging at 9:10
*/
```

---

## 作者：foreverlasting (赞：5)

线段树合并的空间常数太大了，有些时候会被卡掉，这里提供一种空间常数较小的做法。

我们可以先将询问按$r$递减排序，然后扫过去，每次处理之前加进去的询问，看当前位置是否能被作为$i$，然后把已经处理完毕的询问给删掉，再加入当前询问。现在的问题还是在处理询问，发现其实可以对于每一条链打一个$l$的标记在最深的地方，处理询问就查一下$i$到根的最大$mxlen(x)+l$，然后删掉询问。加入询问就是沿着重链往上跳，放标记。具体实现上，查询最大值是线段树可以做的事情，然后你需要对于每个结点开个$set$记录这个结点还有哪些标记，查询的时候讨论一下标记的位置即可。

这样空间常数较小，大概是线段树合并的$\frac{1}{2}$甚至更小。因为这里线段树不用多开$log$的空间，空间上的瓶颈是在$set$上，而询问是动态加减的，很多数据下可能当时存在在$set$里的标记就没几个。

---

## 作者：lalaouye (赞：4)

这里较严谨地证明了 Border 理论并给出了较为详细的题目解法。

令 $pre(i,s)$ 表示 $s_{[1,i]}$，$suf(i,s)$ 表示 $s_{[i,|s|]}$。

$\mathbf{Weak\ Periodicity\ Lemma}$：若 $p,q$ 是字符串 $S$ 的两个周期，且满足 $p+q\le|S|$，那么 $\gcd(p,q)$ 也是 $S$ 的一个周期。

证明：不妨令 $q\ge p$，$d=q-p$。

对于 $1\le i\le |S|-q$，$s_i=s_{i+q}=s_{i+q-p}=s_{i+d}$。

对于 $p+1\le i\le|S|$，$s_i=s_{i-p}=s_{i-p+q}=s_{i+d}$。

由于 $p+q\le |S|$，所以 $p\le|S|-q$，那么对于所有的 $i$ 都有至少一个限制可以满足。且 $d=q-p$ 是个辗转相减的形式，也就是 $\gcd$。

$\mathbf{Periodicity\ Lemma}$：若 $p,q$ 是字符串的两个周期，且满足 $p+q-\gcd(p,q)\le|S|$，那么 $\gcd(p,q)$ 也是 $S$ 的一个周期。

这个定理网上貌似很少有人证明，不知道是不是因为太简单了，我还是证一下吧。考虑对于 $i\in(|S|-q,p+1)$ 怎么保证 $s_i=s_{i+\gcd(p,q)}$。

尝试使用归纳法，首先如果 $p|q$ 显然成立。

而对于一般情况，当 $\gcd(p,q)$ 是 $suf(p+1,S)$ 的一个周期，我们便可以证明 $s_i=s_{i+\gcd(p,q)}$，同样也能够证明 $s_i=s_{i+d}$。如果满足 $p+q-\gcd(p,q)\le|S|$，对于 $suf(p+1,S)$ 的两个周期 $p,q-p$ 来说，容易证明 $p+(q-p)-\gcd(p,q-p)\le|S|-p$，容易发现两式等价。通过不断归纳可以归纳到 $p|q$ 的情况。

介绍完周期定理后就可以介绍其它一些常用引理了。

**引理**：若字符串 $s$ 和 $t$ 满足 $|s|\le |t|\le 2|s|$，则 $s$ 在 $t$ 中的所有匹配位置构成了一个等差数列，且公差为最小周期。

证明：只需要考虑匹配次数大于 $2$ 的情况。在这种情况下，显然匹配的区间之间是有交的。容易证明不存在两个位置相邻的匹配之间差值不为最小周期，手玩一下即可。

**引理**：对于字符串 $S$，所有大于等于 $\frac {|S|}{2}$ 的 border 的长度构成等差数列。

证明：显然一个长为 $p$ 的 border 对应一个长为 $|S|-p$ 的周期。那么我们考虑把最长的 border 找出来，设其长为 $p$，可知存在周期为 $|S|-p$。对于其它的满足条件的 border，若长为 $q$，那么显然 $|S|-p$ 和 $|S|-q$ 这对周期满足周期引理的条件，所以 $\gcd(|S|-p,|S|-q)$ 同样是 $|S|$ 的周期，而结果只能为 $|S|-p$，否则与 $p$ 为最长的 border 相矛盾。所以对于任意满足条件的 $q$ 都有 $|S|-q$ 整除 $|S|-p$。而所有长为 $|S|-p$ 倍数的周期都对应了一个 border，得证。

现在我们类似倍增分块，将 border 按长度分为 $[1,2),[2,4),\cdots,[2^k,|S|)$ 这些集合。

**引理**：每个集合内 border 的长度构成等差数列。

证明：找出最长的 border，集合内其它 border 肯定也是最长 border 的 border，且长度都满足上一个引理的条件。

这意味着，我们可以将一个字符串的 border 分成 $\log n$ 个等差数列表示，我们可以利用它来干一些很厉害的事情，比如说 [[BJWC2018] Border 的四种求法](https://www.luogu.com.cn/problem/P4482)。

怎么找一个子串的 $\log n$ 个等差数列呢？现在尝试对于每个集合找出它对应的等差数列，由于最后一个集合上界是 $|S|$，有点特殊，我们先想其它集合怎么处理。这里有个很巧妙的方法，对于 $[2^k,2^{k+1})$ 这个集合，我们让 $pre(2^k,S)$ 放到 $suf(2^{k+1}-1,S)$ 匹配，$suf(2^k,S)$ 放到 $pre(2^{k+1},S)$ 匹配。那么将匹配位置平移后求交就是 border 序列。根据引理，我们发现这两次匹配的匹配位置同样构成等差数列，我们只需要找到前两次匹配位置和最后一次匹配位置就能完美刻画等差数列了。

直接 KMP 显然在多组询问中不优，我们考虑哈希。由于我们知匹配长度为 $2$ 的整次幂的串，我们可以 $\mathcal{O}(n\log n)$ 预处理每个串的哈希值。现在我们要处理形如一个二元组 $(s,i)$ 的询问，表示查询在 $i$ 的左边或右边 $s$ 第一次匹配的位置。但是对于 $|s|=2^k$ 的查询，对于 $i$ 我们只关注 $[i,i+2^k]$ 这个区间中有没有答案，想想我们在什么情况下才查询的。这样我们对于序列每 $2^k$ 个位置就分一个段，总段数显然是 $\mathcal{O}(n)$ 的，每个段存段内每个哈希值的等差数列，然后我们查询位置的时候只需要涉及到两个段就可以查出 $pre$ 和 $suf$ 匹配时的等差数列了。

接下来等差数列合并貌似是个棘手的问题，直接做的话只能写非常麻烦的双 $\log$ 做法。如果想做到简洁的单 $\log$ 需要继续分析性质。

**引理**：四个字符串满足 $|x_1|=|y_1|\ge|x_2|=|y_2|$，且 $x_1$ 至少在 $y_2y_1$ 中匹配了 $3$ 次，则 $per(x_1)=per(y_1)$。

证明：考虑使用反证法，假设 $per(x_1)>per(y_1)$，考虑 $x_1$ 在 $y_2y_1$ 最右边一次匹配，令 $z$ 表示 $x_1$ 与 $y_1$ 重叠的部分，那么 $|z|\ge 2per(x_1)>per(x_1)+per(y_1)$，并且 $per(x_1)$ 和 $per(y_1)$ 都是 $z$ 的周期，那么 $\gcd(per(x_1),per(y_1))$ 也是 $z$ 的周期，但是它显然是要小于 $per(x_1)$ 的，与 $per(x_1)$ 是最小周期矛盾。

这意味着，两个等差数列要么公差相同，要么长度不超过 $3$。这样就可以 $\mathcal{O}(1)$ 合并等差数列了。

总复杂度 $\mathcal{O}(n\log n)$，常数较大，[代码](https://www.luogu.com.cn/paste/zooexg4j)。

---

## 作者：FZzzz (赞：4)

字符串神题。

独立做出这题可能可以说明你后缀数据结构基本上毕业了，独立想出 1log 做法说明你对 border 理论那一套基本完全理解了。

当然我必然是不会 border 那一套理论的，所以这是 2log 题解。这个做法应该跟 foreverlasting 神仙的做法差不多，不过我觉得我说得详细一点。

------------
一句话题意：多次询问区间最长 border。

border 这个东西一看就很不可做，考虑用更舒服一点的方式去刻画它。设当前询问是 $[l,r]$，$i$ 是一个 border 的充要条件是 $l+\operatorname{lcs}(r,l+i-1)>l+i-1$。lcs 这个东西就可以非常舒服地用 SAM 转化成 lca，于是我们现在就是需要对每个询问求出最大的 $l+i-1<r$ 满足上述条件。

考虑把询问离线下来，从右往左扫描线，扫到 $r$ 的时候把以它为右端点的询问加到未处理的询问里面。对于每个位置，考虑用一定时间求出它能成为哪些未处理询问的 $l+i-1$，然后暴力把这些询问删掉。因为我们是从右往左扫，所以以后的位置必然不能更新答案。

那么现在看看我们现在把问题转化成了什么样：每个询问相当于给出 $l$ 和 $u$，每次我们需要对 $x$ 和 $v$，找出所有未处理询问满足：$l+len_{\operatorname{lca}(u,v)}>x$。这就是完完全全的一个树上问题了。SAM 的问题转化到此结束，接下来是朴实无华的套路树上数据结构环节。

考虑树剖。每次我们从 $v$ 往上跳，那么与最开始的 $v$ 的 lca 在现在的 $(top_v,v)$ 这条路径上的 $u$ 一定满足两种情况之一：$u$ 在 $v$ 的子树内或在 $(top_v,v)$ 上某个点的轻子树内。

先来解决第一种情况。满足这个条件的 lca 一定在 $v$ 的子树内，所以虽然 lca 可能不是 $v$，但是 lca 的 len 一定大于 $len_v$，所以在这里满足条件，那么一定已经在下面就被处理过了，只需要删掉就可以了。

我们用一个线段树，每个叶子维护一个优先队列存 $u$ 为这个点的所有未处理询问，然后每个节点维护这个节点的区间内所有询问中 $l$ 最大的。这样我们每次可以取出子树里所有未处理询问中 $l$ 最大的（如果已经被处理过直接 pop 掉就可以了），如果可以处理就直接更新答案然后删掉这个询问继续找，如果不能处理说明这个子树内没有可以处理的询问了，跳出循环。

现在考虑第二种情况。我们从询问子树转而询问 $(top_v,v)$ 这段路径。加入询问时，从 $u$ 往上跳重链，跳到一个点就把这个询问挂在这个点，这样如果被询问到了，说明 lca 就是这个点。那么我们可以用上一种情况的线段树维护，只是改为维护 $l+len_u$（注意这个 $u$ 是跳到的 $u$ 而不是初始的 $u$）最大的即可。

时间复杂度容易分析出是 $O(n\log^2n)$（忽略建 SAM 的复杂度），空间复杂度是 $O(n\log n)$，可能有很多方法可以优化到线性，但已经足以通过此题。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n,q,l[maxn];
char s[maxn];
int sz=1,last=0,len[maxn*2],link[maxn*2],nxt[maxn*2][26];
vector<int> ch[maxn*2];
void extend(int c){
	int cur=sz++;
	len[cur]=len[last]+1;
	int p=last;
	while(p>=0&&!nxt[p][c]){
		nxt[p][c]=cur;
		p=link[p];
	}
	if(p>=0){
		int q=nxt[p][c];
		if(len[q]==len[p]+1) link[cur]=q;
		else{
			int clone=sz++;
			link[clone]=link[q];
			memcpy(nxt[clone],nxt[q],sizeof(nxt[0]));
			len[clone]=len[p]+1;
			while(p>=0&&nxt[p][c]==q){
				nxt[p][c]=clone;
				p=link[p];
			}
			link[cur]=link[q]=clone;
		}
	}
	last=cur;
}
int cur[maxn],size[maxn*2],hson[maxn*2];
void dfs1(int u){
	size[u]=1;
	hson[u]=-1;
	for(int v:ch[u]){
		dfs1(v);
		size[u]+=size[v];
		if(hson[u]<0||size[v]>size[hson[u]]) hson[u]=v;
	}
}
int pos[maxn*2],top[maxn*2];
vector<int> f;
void dfs2(int u){
	pos[u]=f.size();
	f.push_back(u);
	if(hson[u]<0) return;
	top[hson[u]]=top[u];
	dfs2(hson[u]);
	for(int v:ch[u]){
		if(v==hson[u]) continue;
		top[v]=v;
		dfs2(v);
	}
}
struct item{
	int x,u;
	bool type;
	bool operator <(const item b)const{
		if(x<0||b.x<0) return x<0&&b.x>=0;
		return type?l[x]+len[u]<l[b.x]+len[b.u]:l[x]<l[b.x];
	}
};
struct node{
	int l,r;
	node* ch[2];
	item v;
	priority_queue<item> pq;
	void pushup(){
		v=max(ch[0]->v,ch[1]->v);
	}
	node(int l,int r,bool type):l(l),r(r),v({-1,0,type}){
		if(l==r){
			pq.push({-1,0,type});
			return;
		}
		int mid=l+(r-l)/2;
		ch[0]=new node(l,mid,type);
		ch[1]=new node(mid+1,r,type);
		pushup();
	}
	void modify(int x,item k){
		if(l==r){
			if(k.x>=0) pq.push(k);
			else pq.pop();
			v=pq.top();
			return;
		}
		if(x<=ch[0]->r) ch[0]->modify(x,k);
		else ch[1]->modify(x,k);
		pushup();
	}
	item query(int ql,int qr){
		if(ql<=l&&qr>=r) return v;
		item ans={-1,0,v.type};
		if(ql<=ch[0]->r) ans=max(ans,ch[0]->query(ql,qr));
		if(qr>=ch[1]->l) ans=max(ans,ch[1]->query(ql,qr));
		return ans;
	}
	int debug(int x){
		if(l==r) return pq.size();
		if(x<=ch[0]->r) return ch[0]->debug(x);
		else return ch[1]->debug(x);
	}
}*rt1,*rt2;
vector<int> vec[maxn];
int ans[maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	link[0]=-1;
	for(int i=1;i<=n;i++){
		extend(s[i]-'a');
		cur[i]=last;
	}
	for(int i=1;i<sz;i++) ch[link[i]].push_back(i);
	dfs1(0);
	dfs2(0);
	q=readint();
	for(int i=1;i<=q;i++){
		l[i]=readint();
		vec[readint()].push_back(i);
	}
	rt1=new node(0,sz-1,0);
	rt2=new node(0,sz-1,1);
	memset(ans,-1,sizeof(ans));
	for(int i=n;i>0;i--){
		int u=cur[i];
		while(u>=0){
			while(1){
				item res=rt1->query(pos[u],pos[u]+size[u]-1);
				if(res.x<0||l[res.x]+len[u]<=i) break;
				if(ans[res.x]<0) ans[res.x]=i-l[res.x]+1;
				rt1->modify(pos[res.u],{-1,0,0});
			}
			while(1){
				item res=rt2->query(pos[top[u]],pos[u]);
				if(res.x<0||l[res.x]+len[res.u]<=i) break;
				if(ans[res.x]<0) ans[res.x]=i-l[res.x]+1;
				rt2->modify(pos[res.u],{-1,0,1});
			}
			u=link[top[u]];
		}
		for(int j:vec[i]){
			int u=cur[i];
			rt1->modify(pos[u],{j,u,0});
			while(u>=0){
				rt2->modify(pos[u],{j,u,1});
				u=link[top[u]];
			}
		}
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：xianggl (赞：4)

题意：

求区间 border。

题解：

转化为求最大的 $i$ 使得 $\operatorname{lcs}(i, r) \geq i - l + 1$。

再转化为 $len[\operatorname{lca}(ver[i], ver[r])] \geq i - l + 1$，其中 $ver[x]$ 表示后缀自动机中表示 $x$ 这个前缀的节点。

然后注意到，如果令后缀树上的一条边边权为 $len[x] - len[fa[x]]$，则 $len[x]$ 可以转化为 $x$ 到根的距离。

又因为 $dis(x, y) = dis[x] + dis[y] - 2 \times dis[\operatorname{lca}(x, y)]$，则 $dis[\operatorname{lca}(x, y)] = (dis[x] + dis[y] - dis(x, y)) / 2$。

于是，$\operatorname{lcs}(i, r)$ 可以用各自的 $dis$ 和他们树上距离表示，考虑点分治。

令 $dis_r[x]$ 为 $x$ 到分治中心的距离，则需要满足的条件是：

$dis[ver[i]] + dis[ver[r]] - dis_r[ver[i]] - dis_r[ver[r]] \geq 2 \times (i - l + 1)$

移项，将与 $i$ 有关的放到一起，得到一个不等式：

$dis[ver[i]] - dis_r[ver[i]] - 2 \times i \geq dis_r[ver[r]] - dis[ver[r]] - 2 \times (l - 1)$。

于是将所有表示前缀的点和询问列出来，排序，用 set 维护即可，不需要手写任何数据结构。

代码：

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
#define fi first
#define se second
using namespace std;
//dis[ver[i]] - dis_[ver[i]] - 2 * i >= dis_[ver[r]] - dis[ver[r]] - 2 * (l - 1)
const int Maxn=2e5;
template <typename T> struct SAM {
	vector<int>len,fa;
	vector<map<T,int>>ch;
	int tot,las;
	inline int newnode() {
		len.emplace_back(),fa.emplace_back(),ch.emplace_back();
		return ++tot;
	}
	SAM() {tot=-1,newnode(),las=newnode();}
	inline void insert(T &c) {
		int now=newnode(),p=las;
		len[now]=len[p]+1,las=now;
		for(;p&&!ch[p][c];p=fa[p])ch[p][c]=now;
		if(!p) {fa[now]=1;return ;}
		int q=ch[p][c];
		if(len[p]+1==len[q]) {fa[now]=q;return ;}
		int cq=newnode();
		len[cq]=len[p]+1,fa[cq]=fa[q];
		ch[cq]=ch[q];
		for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=cq;
		fa[q]=fa[now]=cq;
	}
};
SAM<char>sam;
vector<pair<int,int>>adj[2*Maxn+5];
vector<int>query[2*Maxn+5];
int pos[2*Maxn+5];
int l[Maxn+5],r[Maxn+5];
int vis[2*Maxn+5],size[2*Maxn+5],mx[2*Maxn+5],dis[2*Maxn+5];
int ans[Maxn+5];
vector<pair<int,int>>s;
void dfs(int u,int fa,int n) {
	size[u]=1,mx[u]=0;
	for(auto &e:adj[u]) {
		int v=e.fi;
		if(v!=fa&&!vis[v]) {
			dfs(v,u,n);
			size[u]+=size[v];
			mx[u]=max(mx[u],size[v]);
		}
	}
	mx[u]=max(mx[u],n-size[u]);
	s.emplace_back(mx[u],u);
}
void dfs_dis(int u,int fa) {
	for(auto &e:adj[u]) {
		int v=e.fi;
		if(v!=fa&&!vis[v]) {
			dis[v]=dis[u]+e.se;
			dfs_dis(v,u);
		}
	}
}
void solve(int u,int n) {
	dfs(u,0,n);
	auto p=min_element(s.begin(),s.end())->se;
	dis[p]=0,dfs_dis(p,0);
	vector<pair<int,int>>x;
	vector<pair<int,int>>y;
	for(auto &t:s) {
		int u=t.se;
		if(pos[u]) {
			x.emplace_back(sam.len[u]-dis[u]-2*pos[u],pos[u]);
		}
		for(auto x:query[u]) {
			y.emplace_back(dis[u]-sam.len[u]-2*(l[x]-1),x);
		}
	}
	sort(x.begin(),x.end(),greater<pair<int,int>>());
	sort(y.begin(),y.end(),greater<pair<int,int>>());
	set<int>mx;
	int now=0;
	for(auto &t:y) {
		int id=t.se;
		while(now<(int)x.size()&&x[now].fi>=t.fi) {
			mx.insert(x[now].se);
			++now;
		}
		auto it=mx.lower_bound(r[id]);
		if(it!=mx.begin()) {
			ans[id]=max(ans[id],*prev(it));
		}
	}
	s.clear();
	vis[p]=1;
	for(auto &e:adj[p]) {
		int v=e.fi;
		if(!vis[v]) {
			solve(v,size[v]<size[p]?size[v]:n-size[p]);
		}
	}
}
int main() {
	static char str[Maxn+5];
	scanf("%s",str+1);
	int n=strlen(str+1),q;
	scanf("%d",&q);
	vector<int>ver(n+1);
	for(ri i=1;i<=n;i++) {
		sam.insert(str[i]);
		ver[i]=sam.las,pos[sam.las]=i;
	}
	for(ri i=2;i<=sam.tot;i++) {
		int fa=sam.fa[i],len=sam.len[i]-sam.len[fa];
		adj[i].emplace_back(fa,len);
		adj[fa].emplace_back(i,len);
	}
	for(ri i=1;i<=q;i++) {
		scanf("%d%d",&l[i],&r[i]);
		query[ver[r[i]]].push_back(i);	
	}
	solve(1,sam.tot);
	for(ri i=1;i<=q;i++)printf("%d\n",max(0,ans[i]-l[i]+1));
	return 0;
}
```


---

## 作者：lzqy_ (赞：3)

原来这题正解不是 DAG 链剖分啊（

先考虑怎么刻画 border，发现它可以表示成 $s_{[1,r]}$ 的后缀节点与 $s_{[l,r]}$ 的前缀节点的交。前者在 Parent Tree 上是一条到根的链，后者在 DAG 上是一条从 $1$ 出发的路径。

对 DAG 进行 DAG 链剖分，以 $O(\log V)$ 的代价将路径拍成编号连续的区间。那么问题转化为给出 $O(q\log V)$ 组询问，每次询问 $\{1\rightarrow x\}$ 路径上且编号在 $[l,r]$ 区间内权值的最大值。

另一个问题是这个权值该怎么刻画。一个点的权值等价于从 $1$ 到它的路径长，所以对于路径上任意一条重链的区间，权值与编号的差是一个定值 $c$。所以我们强制钦定点 $x$ 的权值为 $x$，每组询问加一个权值 $c$ 即可。

时间复杂度 $O(n\log n\log V+n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
#define il inline
using namespace std;
const int inf=1<<30;
const int maxn=400010;
const int MAXN=maxn<<2;
const int mod1=998244353;
const int base1=39;
const int mod2=1e9+7;
const int base2=41;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x; 
}
il void chkmax(int &x,int y){if(y>x)x=y;}
struct sam{
	int ch[26],fa,len;
}a[maxn];
int loc[maxn],End=1,cnt=1;
void Insert(int c){
	int t=End,x=End=++cnt,nt=0,nx; a[x].len=a[t].len+1;
	/////////
	loc[a[x].len]=x;
	////////
	for(;t&&!nt;t=a[t].fa,nt=a[t].ch[c]) a[t].ch[c]=x;
	if(!t){a[x].fa=1;return ;}
	if(a[t].len+1==a[nt].len){a[x].fa=nt;return ;}
	nx=++cnt,a[nx].fa=a[nt].fa;
	a[x].fa=a[nt].fa=nx,a[nx].len=a[t].len+1;
	for(int i=0;i<26;i++) a[nx].ch[i]=a[nt].ch[i];
	for(;a[t].ch[c]==nt;t=a[t].fa) a[t].ch[c]=nx;
}
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
//	if(ecnt&1) printf("Tree:%d->%d\n",u,v);
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
vector<int>v1[maxn];
vector<int>c1[maxn];
vector<int>v2[maxn];
struct Que{
	int l,r,ad,id;
	Que(int a=0,int b=0,int c=0,int d=0){l=a,r=b,ad=c,id=d;}
};
int deg[maxn];
ll f1[maxn],f2[maxn];
int dfn[maxn],DFN[maxn],idx;
int zc[maxn],zson[maxn],mf1[maxn],mf2[maxn];
int top[maxn],Ed[maxn];
vector<Que>Q[maxn];
int n,m,M,w[maxn];
int ans[maxn];
char c[maxn];
queue<int>q;
int h1[maxn],h2[maxn];
int pow1[maxn],pow2[maxn];
int ch1[maxn],ch2[maxn];
int d[MAXN];
void Build(int i,int l,int r){
	d[i]=-inf;
	if(l==r) return ;
	int mid=l+r>>1;
	Build(i<<1,l,mid);
	Build(i<<1|1,mid+1,r); 
}
void Mod(int i,int l,int r,int x,int k){
	if(l==r) return d[i]=k,void();
	int mid=l+r>>1;
	if(mid>=x) Mod(i<<1,l,mid,x,k);
	else Mod(i<<1|1,mid+1,r,x,k);
	d[i]=max(d[i<<1],d[i<<1|1]);
}
int Query(int i,int l,int r,int L,int R){
	if(l>=L&&r<=R) return d[i];
	if(l>R||r<L) return -inf;
	int mid=l+r>>1;
	return max(Query(i<<1,l,mid,L,R),Query(i<<1|1,mid+1,r,L,R)); 
}
pair<int,int>H(int x,int y,int len){
	return mp((h1[y]-1ll*h1[x]*pow1[len]%mod1+mod1)%mod1,
			   (h2[y]-1ll*h2[x]*pow2[len]%mod2+mod2)%mod2);
}
pair<int,int>cH(int x,int y,int len){
	return mp((ch1[y]-1ll*ch1[x-1]*pow1[len]%mod1+mod1)%mod1,
			   (ch2[y]-1ll*ch2[x-1]*pow2[len]%mod2+mod2)%mod2);
} 
void bfs1(){
	memset(deg,0,sizeof(deg));
	for(int u=1;u<=cnt;u++)
		for(int v:v1[u]) deg[v]++;
	q.push(1);
	while(!q.empty()){
		int u=q.front(); 
		q.pop(),f1[u]++;
		for(int v:v1[u]){
			f1[v]+=f1[u],deg[v]--;
			if(!deg[v]) q.push(v); 
		}
	}
}
void bfs2(){
	memset(deg,0,sizeof(deg));
	for(int u=1;u<=cnt;u++)
		for(int v:v2[u]) deg[v]++;
	for(int i=1;i<=cnt;i++)
		if(!deg[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop(),f2[u]++;
		for(int v:v2[u]){
			f2[v]+=f2[u],deg[v]--;
			if(!deg[v]) q.push(v);
		}
	} 
}
void build(){
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<v1[i].size();j++)
			if(f2[mf2[i]]<f2[v1[i][j]]) 
				mf2[i]=v1[i][j],zc[i]=c1[i][j];
		for(int j=0;j<v2[i].size();j++)
			if(f1[mf1[i]]<f1[v2[i][j]]) mf1[i]=v2[i][j];
	}
	for(int i=1;i<=cnt;i++)
		if(mf1[mf2[i]]==i) zson[i]=a[i].ch[zc[i]];
	
	pow1[0]=pow2[0]=1;
	for(int i=1;i<=cnt;i++){
		pow1[i]=1ll*pow1[i-1]*base1%mod1;
		pow2[i]=1ll*pow2[i-1]*base2%mod2;
	}
	for(int i=1;i<=cnt;i++)
		if(mf2[mf1[i]]!=i){
			top[i]=i,Ed[i]=i,dfn[i]=++idx,DFN[idx]=i;
			for(int x=zson[i],lst=i;x;lst=x,x=zson[x]){
				h1[x]=(1ll*h1[lst]*base1+zc[lst]+'a')%mod1;
				h2[x]=(1ll*h2[lst]*base2+zc[lst]+'a')%mod2;
				top[x]=i,Ed[i]=x,dfn[x]=++idx,DFN[idx]=x;
			}
		}
	for(int i=1;i<=cnt;i++){
		ch1[i]=(1ll*ch1[i-1]*base1+c[i])%mod1;
		ch2[i]=(1ll*ch2[i-1]*base2+c[i])%mod2;
	}
}
void DFS(int fa,int x){
	Mod(1,1,cnt,dfn[x],dfn[x]);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fa) DFS(x,e[i].v);
	for(Que t:Q[x]) 
		chkmax(ans[t.id],Query(1,1,cnt,t.l,t.r)+t.ad);
	Mod(1,1,cnt,dfn[x],-inf);
}
int getp(int x,int L,int R){
	if(!zson[x]||zc[x]!=c[L]-'a') return x;
	int l=2,r=min(R-L+2,dfn[Ed[top[x]]]-dfn[x]+1),mid;
	while(r>l){
		mid=l+r+1>>1;
		if(H(x,DFN[dfn[x]+mid-1],mid-1)==cH(L,L+mid-2,mid-1)) l=mid;
		else r=mid-1;	
	}return DFN[dfn[x]+l-1];
}
int main(){
	scanf("%s",c+1);
	n=strlen(c+1),m=read();
	for(int i=1;i<=n;i++) Insert(c[i]-'a');
	for(int i=2;i<=cnt;i++) 
		addedge(i,a[i].fa),addedge(a[i].fa,i);
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<26;j++)
			if(a[i].ch[j]){
				v1[i].push_back(a[i].ch[j]);
				v2[a[i].ch[j]].push_back(i);
				c1[i].push_back(j);
//				printf("DAG:%d->%d(%c)\n",i,a[i].ch[j],j+'a');
			}
	bfs1(),bfs2(),build(),Build(1,1,cnt);
//	printf("DAG subdivision:\n");
//	for(int i=1;i<=cnt;i++)
//		printf("%d ",zson[i]);
//	printf("\n");
	for(int i=1;i<=m;i++){
		int l=read(),r=read()-1;
		int X=loc[r+1],x=1,y,fl,tot=0;
		while(l<=r){
			y=getp(x,l,r);
			Q[X].push_back(Que(dfn[x],dfn[y],tot-dfn[x],i));
			tot+=dfn[y]-dfn[x],l+=dfn[y]-dfn[x],fl=0;
			if(l>r) break;
			x=a[y].ch[c[l]-'a'],l++,tot++,fl=1;
		}
		if(fl)Q[X].push_back(Que(dfn[x],dfn[x],tot-dfn[x],i));
	}DFS(0,1);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]); 
	return 0;
} 
```

---

## 作者：Leasier (赞：3)

Border 这种东西一看就很难直接搞区间，考虑转化成比较好处理的形式。

注意到当 $[l, i]$ 为其 Border，则 $[l, i] = [r - (i - l), r]$。再换个形式表示，则 $[1, i]$ 和 $[1, r]$ 的 LCS 长度 $\geq i - l + 1$，我们记作 $lcs(i, r) \geq i - l + 1$。

看到 LCS，考虑建出 SAM 的 fail 树，则 $len_{lca(pos_i, pos_r)} \geq i - l + 1$。

然后就有一个~~简单的~~暴力了：

- 可持久化线段树合并预处理每个子树内所有 $pos_i$ 的信息。
- 枚举 $pos_r$ 的祖先 $u$ 作为 $lca(pos_i, pos_r)$，则 $l \leq i \leq \min(l + len_u - 1, r - 1)$。在 $u$ 的可持久化线段树中二分查询该区间内的最大 $i$ 即可。

这里看上去似乎是要去重的，但因为越往祖先走 $i$ 的限制越紧，所以没影响。

时间复杂度为 $O(qn \log n)$，只有 $50 \operatorname{pts}$。

考虑树剖。现在我们将 $pos_r$ 到根的路径划分为 $O(\log n)$ 条重链的前缀，比如说我们要考虑其中一条 $x \to top_x$。

既然树剖了，我们就来考虑一下轻重子树分别的贡献。

1. 轻子树

- $x \to top_x$ 上的点（不包括 $x$）的轻子树带来的贡献。考虑离线下来 DSU on tree，把询问挂到 $x$ 的位置，对于每条重链从上往下依次处理，每次我们相当于知道 $lca(pos_i, pos_r) = u$（$u$ 为当前处理的点），则移项可知 $l \leq i < r$ 且 $i - len_u + 1 \leq l$。找出轻子树中作为原串前缀的 $[1, i]$ 并把 $i - len_u + 1$ 插入线段树 $i$ 的位置，然后线段树上二分即可。
- 这个前缀底部 $x$ 的子树带来的贡献。进行一次可持久化线段树查询即可。

2. 重子树

- $x \to top_x$ 上的点带来的贡献。在 DSU on tree 时一起加入这些位置的贡献即可。
- 这个前缀底部 $x$ 的子树带来的贡献（在轻子树的部分已经一起处理过了）。

综上，时间复杂度为 $O((|S| + q) \log^2 |S|)$。

代码有点长，应管理员要求放在[剪贴板](https://www.luogu.com.cn/paste/8gkbh4no)里。

---

## 作者：251Sec (赞：2)

设 $n,q$ 同阶。

所求为最大的 $p \le r-l$ 使得 $s(l,l+p-1)=s(r-p+1,r)$。容易转化成最大的 $p \le r-l$ 使得 $\text{lcs}(l+p-1,r) \ge p$。在 SAM 上即为 $\text{len}(\text{lca}(v,u)) \ge p$，$v$ 为 $s(1,l+p-1)$ 对应的点，$u$ 为 $s(1,r)$ 对应的点。

先考虑 $p \le r-l$ 的限制，实际上我们可以直接把上面的 $u$ 变成 $s(l+1,r)$ 对应的点，这样就保证了 $p>r-l$ 一定不合法。找这个点是经典套路，在 Parent 树上倍增即可。

接下来枚举 LCA，则 $p \in [1,\text{len}]$，也就是 $l+p-1 \in [l,l+\text{len}-1]$，发现 $u,v$ 的 LCA 不需要恰好是枚举的这个点，如果是它的子树里的点也可以，不会算多。于是我们需要线段树合并，查询区间 $[l,l+\text{len}-1]$ 内 EndPos 的最大值。这个查询的下界是假的，可以转化为查询 $[1,l+\text{len}-1]$ 内的最大值。这里每次询问都要枚举 LCA，复杂度是炸裂的 $O(n^2 \log n)$，不如暴力[]()~~，但是听说能过不知道是不是真的~~，考虑优化。

对 Parent 树进行树剖。考虑 $u$ 在 LCA 的哪个子树：

- 轻子树：这样的情况只会发生 $\log$ 次，直接跑上面的算法就可以了。
- 重子树：会贡献到 $u$ 的是 $\log$ 条重链的前缀，考虑把所有 $u$ 离线下来挂上去，对每条重链扫描线，暴力加入所有轻子树的贡献。加入贡献的形式形如，加入一个 EndPos 为 $x$ 的点，会使得 $l \in [x-\text{len}+1,x]$ 的答案和 $x$ 取 $\max$。可以用线段树维护。根据经典结论，加入的轻子树贡献之和是 $O(n \log n)$ 级别的，因此复杂度正确。

总复杂度 $O(n \log^2 n)$。

---

## 作者：yizhiming (赞：2)

本文核心指导思想来自国集论文，浅谈一类树上统计相关问题。

有讲错的地方还请海涵，作者实力太差可能具体实现上并没有很优秀。

[Link](https://www.luogu.com.cn/problem/P4482)

### 题目大意

给定一个长度为 $n$ 的小写字母组成的字符串，$q$ 次查询 $l,r$ 表示，查询 $[l,r]$ 组成的这个子串的最长 border 长度，其中 border 的定义为在这个串中完全相等的前缀后缀集合。即 $s[l,l+len-1] = s[r-len+1,r]$，满足这个条件的最长的 $len$。

$1\leq n,q \leq 2\times 10^5$。

### 题目分析

定义前缀 $i$ 表示 $s[1,i]$。

首先考虑建出后缀树，那么对于两个前缀 $i,j$，它们的最长公共后缀的长度，即为对应终止节点在后缀树上的最近公共祖先的 $maxlen$，那么对于一个询问 $l,r$，若 $i\in[l,r-1]$，那么前缀 $i$ 和前缀 $r$ 的最长公共后缀长度记为 $k$，若满足 $i-k+1\leq l$，那么 $s[l,i]$ 就是一个合法的 border。

考虑如何求满足这个条件的最大的 $i$，这时就引出论文中的这类问题。

这类问题利用的是重链剖分的性质去处理，若一个问题的形式是形如查询一个点到根路径上的相关信息，且问题可以拆成重链上每个节点的轻儿子贡献，以及在当前查询链上的节点的不在查询上的重儿子的子树贡献。

这有什么用呢？第一种贡献，会利用重剖到根节点，会拆成若干个重链的前缀拼起来，以及轻儿子的子树大小和为 $O(n\log n)$ 这两个性质，第二种则用到了挂在这样特殊单点的询问只有 $O(q\log n)$ 种，由于都是重剖的基本性质，这里不解释原因。

我们现在的问题并没有形如上面这个形式，考虑将其化成这个形式。

具体的，我们考虑枚举最近公共祖先，记作 $L$，那么 $L$ 对于一个查询来说，就是一条到根的链，我们考虑维护这些的贡献。

什么时候会产生贡献呢？当 $L$ 子树内存在有前缀 $i$ 满足 $i\in[l,r-1]$，且 $i-maxlen_L+1\leq l$，并且前缀 $r$ 对应的节点和 $i$ 不在 $L$ 的同一棵子树内，我们只需要想办法求出这种贡献。

首先先考虑第二种，我们先离线将所有的查询按照上述说法挂到对应节点上，那么对于第二种情况，相当于求一个节点子树内 $[l,\min(r-1,i-maxlen_L+1)]$ 中的最大的 $i$，这个直接线段树合并，查询的时候线段树二分就好，只有 $n\log n$ 个询问，所以这部分复杂度 $O(n\log^2n)$。

第一种情况，也是将询问扔上去，由于我们每次查询的是一个前缀，容易想到枚举前缀，用类似扫描线的方法，将新的贡献扔进数据结构里，具体的就是从顶开始枚举，每次将当前节点轻儿子子树内所有点爆搜出来，总次数为 $n\log n$，然后问题就是怎么查询这个东西了，我们发现上面的式子中 $l,r,L$ 是变的，所以我们并不能直接扔到线段树上二分，因为之前满足条件现在可能不一定。

但是我们注意到只需要求最大的 $i$，发现相当于在一个区间中，查询最靠右的权值 $\leq k$ 的位置，所以将 $i-maxlen_L+1$ 视作权值加到对应位置上，查询的时候线段树二分即可，总体复杂度 $O(n\log^2n)$。

有一个小小的问题叫做 $i,r$ 可能在同一个子树内，我们应该把那棵子树扣掉，但是信息不具有可减性，所以用一个经典的方法，就是记录每个询问由哪个子树跳上来，然后这个询问的贡献拆成在他前面的子树的贡献，与在他后面的子树的贡献，具体的就是正反跑两遍，每次把当前子树要更新贡献的子树统计答案，复杂度不变。

### Code

常数巨大，空间巨大，写的时候没仔细想怎么优化，见谅。
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 2e6+5;
int I;
int fa[N],Rt,n;
vector<int>ed[N];
struct SAM{
	struct aa{
		int ch[26],len,fa;
	}node[N*2];
	int id[N];
	int las=1,tot=1;
	void ins(int x){
		int p = las,np = las = ++tot;
		id[np] = I;
		node[np].len = node[p].len+1;
		for(;p&&!node[p].ch[x];p=node[p].fa){
			node[p].ch[x] = np;
		}
		if(!p){
			node[np].fa = 1;
		}else{
			int q = node[p].ch[x];
			if(node[p].len+1==node[q].len){
				node[np].fa = q;
			}else{
				int nq = ++tot;
				node[nq] = node[q];
				node[nq].len = node[p].len+1;
				node[q].fa = nq;node[np].fa = nq;
				for(;p&&node[p].ch[x]==q;p=node[p].fa){
					node[p].ch[x] = nq;
				}
			}
		}
	}
	int s[N],a[N];
	void build(){
		for(int i=1;i<=tot;i++){
			s[node[i].len]++;
		}
		for(int i=1;i<=tot;i++){
			s[i]+=s[i-1];
		}
		for(int i=1;i<=tot;i++){
			a[s[node[i].len]--] = i;
		}
		for(int i=tot;i>=1;i--){
			int u = a[i];
			fa[u] = node[u].fa;
			ed[fa[u]].push_back(u);
			if(ed[u].size()){
				sort(ed[u].begin(),ed[u].end());
			}
		}
	}
}T;
struct seg{
	struct aa{
		int lc,rc,mi;
		void clear(){
			lc = rc = 0;
			mi = 1e18;
		}
	}node[N*40];
	int tot;
	int sta[N*40],tp;
	int newnode(){
		if(!tp){
			return ++tot;
		}else{
			node[sta[tp]].clear();
			return sta[tp--];
		}
	}
	void build(int &u,int l,int r){
		u = newnode();
		node[u].mi = 1e18;
		if(l==r){
			return;
		}
		int mid = (l+r)/2;
		build(node[u].lc,l,mid);
		build(node[u].rc,mid+1,r);
	}
	void pushup(int u){
		node[u].mi = min(node[node[u].lc].mi,node[node[u].rc].mi);
	}
	void upd(int &u,int l,int r,int x,int y){
		if(!u){
			u = newnode();
		}
		if(l==r){
			node[u].mi = min(node[u].mi,y);
			if(y==1e18){
				node[u].mi = 1e18;
			}
			return;
		}
		int mid = (l+r)/2;
		if(x<=mid){
			upd(node[u].lc,l,mid,x,y);
		}else{
			upd(node[u].rc,mid+1,r,x,y);
		}
		pushup(u);
	}
	int ask(int u,int l,int r,int ll,int rr,int x){//下标[ll,rr]且权值<=x的最大位置 
		if(node[u].mi>x||ll>rr){
			return 0;
		}
		if(l==r){
			return l;
		}
		int mid = (l+r)/2;
		if(l==ll&&r==rr){
			int y = ask(node[u].rc,mid+1,r,mid+1,rr,x);
			if(!y){
				return ask(node[u].lc,l,mid,ll,mid,x);
			}
			return y;
		}
		if(rr<=mid){
			return ask(node[u].lc,l,mid,ll,rr,x);
		}else if(ll>mid){
			return ask(node[u].rc,mid+1,r,ll,rr,x);
		}else{
			int y = ask(node[u].rc,mid+1,r,mid+1,rr,x);
			if(!y){
				return ask(node[u].lc,l,mid,ll,mid,x); 
			}
			return y;
		}
	}
	int merge(int u,int v,int l,int r){
		if(!u||!v){
			return u+v;
		}
		if(l==r){
			node[u].mi = min(node[u].mi,node[v].mi);
			sta[++tp] = v;
			return u;
		}
		int mid = (l+r)/2;
		node[u].lc = merge(node[u].lc,node[v].lc,l,mid);
		node[u].rc = merge(node[u].rc,node[v].rc,mid+1,r);
		pushup(u);
		sta[++tp] = v;
		return u;
	}
	void rebuild(){
		tot = 0;
		Rt = 0;
		memset(node,0,sizeof(node));
		node[0].mi = 1e18;
		tp = 0;
		build(Rt,1,n);
	}
}T1,T2;
int q;
char s[N];
int pos[N];
int dep[N],son[N],siz[N],top[N],cnt;
void dfs1(int u){
	siz[u] = 1;
	for(auto x:ed[u]){
		dep[x] = dep[u]+1;
		dfs1(x);
		siz[u]+=siz[x];
		if(siz[x]>siz[son[u]]){
			son[u] = x;
		}
	}
}
void dfs2(int u,int t){
	top[u] = t;
	if(!son[u]){
		return;
	}
	dfs2(son[u],t);
	for(auto x:ed[u]){
		if(x==son[u]){
			continue;
		}
		dfs2(x,x);
	}
}
struct bb{
	int id,u,l,r;//编号，从哪个节点走上来，左右端点 
	bool operator<(const bb&x)const{
		return u<x.u;
	}
};
vector<bb>in1[N],in2[N];
int rt[N];
int op=1;
int ans[N];
void upd(int u,int x,int L){
	if(T.id[u]){
		if(x){
			T1.upd(Rt,1,n,T.id[u],T.id[u]-T.node[L].len+1);
		}else{
			T1.upd(Rt,1,n,T.id[u],1e18);
		}
	}
	for(auto now:ed[u]){
		upd(now,x,L);
	}
}
void dfs(int u){
	if(son[u]){
		dfs(son[u]);
		if(op==1){
			rt[u] = rt[son[u]];
		}
	}
	if(u==top[u]){
		int U = u;
		while(U){
			int z = 0;
			if(T.id[U]){
				T1.upd(Rt,1,n,T.id[U],T.id[U]-T.node[U].len+1);
			}
			for(auto x:ed[U]){
				int sz = in2[U].size();
				while(z<sz){
					if(in2[U][z].u==x){
						auto a = in2[U][z];
						int y = T1.ask(Rt,1,n,a.l,a.r-1,a.l);
						if(y>=a.l){
							
							ans[a.id] = max(ans[a.id],y-a.l+1);
						}
						z++;
					}else{
						break;
					}
				}
				x = x*op;
				if(x==son[U]){
					continue;
				} 

				upd(x,1,U);
			}
			
			U = son[U];
		}
		U = u;
		while(U){
			if(T.id[U]){
				T1.upd(Rt,1,n,T.id[U],1e18);
			}
			for(auto x:ed[U]){
				x = x*op;
				if(x==son[U]){
					continue;
				}
				upd(x,0,U);
			}
			
			U = son[U];
		}
	}
	for(auto x:ed[u]){
		x = x*op;
		if(x==son[u]){
			continue;
		}
		dfs(x);
		if(op==1){
			rt[u] = T2.merge(rt[u],rt[x],1,n);
		}
	}
	if(T.id[u]){
		T2.upd(rt[u],1,n,T.id[u],1);
	}
	if(op==1){
		for(auto x:in1[u]){
			int y = T2.ask(rt[u],1,n,1,min(x.r-1,x.l+T.node[u].len-1),1);
			if(y>=x.l){
				ans[x.id] = max(ans[x.id],y-x.l+1);
			}
		}
	}
}
signed main(){
	scanf("%s",s+1);
	q = read();
	n = strlen(s+1);
	for(int i=1;i<=n;i++){
		I = i;
		T.ins(s[i]-'a');
		pos[i] = T.las;
	}
	T.build();

	dfs1(1);
	dfs2(1,1);
	T1.node[0].mi = 1e18;
	T2.node[0].mi = 1e18;
	T1.build(Rt,1,n);
	for(int i=1;i<=q;i++){
		int l,r;
		l = read();r = read();
		int u = pos[r];
		while(u){
			if(u==pos[r]){
				if(u==top[u]){
					in2[fa[u]].push_back((bb){i,u,l,r});
					u = fa[u];
				}else{
					in2[fa[u]].push_back((bb){i,u,l,r});
					u = top[u];
					in2[fa[u]].push_back((bb){i,u,l,r});
					u = fa[u];
				}
			}else{
				u = top[u];
				in2[fa[u]].push_back((bb){i,u,l,r});
				u = fa[u];
			}
			in1[u].push_back((bb){i,0,l,r});
		}
	}
	for(int i=1;i<=T.tot;i++){
		if(in2[i].size()){
			sort(in2[i].begin(),in2[i].end());
		}
	}
	dfs(1);
	for(int i=1;i<=T.tot;i++){
		int sz = ed[i].size();
		for(int j=0;j<sz;j++){
			ed[i][j]*=-1; 
		}
		if(sz){
			sort(ed[i].begin(),ed[i].end());
		}
		sz = in2[i].size();
		for(int j=0;j<sz;j++){
			in2[i][j].u*=-1;
		}
		if(sz){
			sort(in2[i].begin(),in2[i].end());
		}
	}
	op = -1;
	dfs(1);
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```


---

## 作者：275307894a (赞：2)

题解区关于重链上的做法貌似做烦了？

我们先把这个 border 用有关后缀的东西表示出来，不难发现对于给定区间 $[l,r]$，我们要求 $\max j$ 使得 $LCP(j,l)+j\geq r+1$，且 $j\in(l,r]$。

考虑将其放到 parent 树上，则 LCP 相当于两个点在树上的深度，特别的，如果为祖先后代关系那么是祖先在原串后缀的长度。

深度问题考虑树剖，那么我们将每个后缀转化成 $O(\log n)$ 次跳轻边的过程，这样的好处是每次跳轻边都可以确定出 LCA，也即深度。同理询问也可以这么拆。那么接下来我们只需要考虑一条重链上的问题。

我们记每个后缀的二元组为 $(j,lcp_j)$，询问的三元组为    $(l,r,dep_i)$ 则如果这个后缀能被统计入答案，需要满足：$j\in(l,r],\min(lcp_j,dep_i)+j\geq r+1$。

把 $\min(lcp_j,dep_j)$ 拆了，得到 $lcp_j+j\geq r+1$，且 $dep_i+j\geq r+1$。我们发现实际上将上面三个式子整合以后是两维的问题，也即：$j\in [\max(l+1,r+1-dep_i),r]$，且 $lcp_j+j\geq r+1$。

这个是平凡的，将后缀按照 $lcp_j+j$，询问按照 $r+1$ 排序后双指针，然后用个树状数组维护大于某个数的最小值即可，如果你不想写你也可以写 set，反正跑得飞快。总时间复杂度   $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define Gc() getchar() 
#define Me(x,y) memset(x,y,sizeof(x))
#define Mc(x,y) memcpy(x,y,sizeof(x))
#define d(x,y) ((m)*(x-1)+(y))
#define R(n) (rnd()%(n)+1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define PB push_back
using ll=long long;using db=double;using lb=long db;using ui=unsigned;using ull=unsigned ll;using LL=__int128;
using namespace std;const int N=4e5+5,M=N*4+5,K=50+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const int INF=1e9+7;mt19937 rnd(time(0));
int n,m,k,Le[N],Ip[N],X[N],Y[N],Ans[N];char c[N];vector<int> S[N];
namespace SAM{
	int son[N][26],link[N],Ct=1,La=1;
	void Ins(int c){
		Le[++Ct]=Le[La]+1;int p=La;La=Ct;while(p&&!son[p][c]) son[p][c]=La,p=link[p];if(!p){link[La]=1;return;}
		int q=son[p][c];if(Le[q]==Le[p]+1){link[La]=q;return;}Le[++Ct]=Le[p]+1;link[Ct]=link[q];Mc(son[Ct],son[q]);
		link[q]=link[La]=Ct;while(p&&son[p][c]==q) son[p][c]=Ct,p=link[p]; 
	}
	void BD(){for(int i=2;i<=Ct;i++) S[link[i]].PB(i);}
}
int fa[N],Tp[N],Si[N],Sn[N],d[N];
void dfs1(int x,int La){fa[x]=La;Si[x]=1;for(int i:S[x]) dfs1(i,x),Si[x]+=Si[i],Si[i]>Si[Sn[x]]&&(Sn[x]=i);}
void dfs2(int x,int La){Tp[x]=La;if(Sn[x]) dfs2(Sn[x],La);for(int i:S[x]) i^Sn[x]&&(dfs2(i,i),0);}
struct Node{int x,Ls;};vector<Node> P[N];bool C1(Node x,Node y){return x.Ls+x.x>y.Ls+y.x;}
struct Ques{int x,y,Ls,id;};vector<Ques> Q[N];bool C2(Ques x,Ques y){return x.y>y.y;}
void II(int x,int id,int Ls){while(x)P[Tp[x]].PB((Node){id,Ls}),/*cerr<<"Ins"<<' '<<Tp[x]<<' '<<id<<' '<<Ls<<'\n',*/x=fa[Tp[x]],Ls=Le[x];}
void IQ(int x,int y,int id){int z=x,Ls=n-x+1;x=Ip[x];while(x) Q[Tp[x]].PB((Ques){z+1,y,Ls,id}),/*cerr<<"Q"<<' '<<Tp[x]<<' '<<z+1<<' '<<y<<' '<<Ls<<' '<<id<<'\n',*/x=fa[Tp[x]],Ls=Le[x];}
namespace BIT{
	int f[N];void Ins(int x){while(x<=n) f[x]++,x+=x&-x;}
	void Cl(int x){while(x<=n&&f[x]) f[x]=0,x+=x&-x;}
	int Qry(int x){int Ans=0;while(x) Ans+=f[x],x-=x&-x;return Ans;}
	int Find(int x){int y=0;for(int i=19;~i;i--) y+(1<<i)<=n&&x>=f[y+(1<<i)]&&(y+=(1<<i),x-=f[y]);return y+1;}
}
int main(){
	freopen("1.in","r",stdin);
	int i,j;scanf("%s",c+1);n=strlen(c+1);for(i=n;i;i--) SAM::Ins(c[i]-'a'),Ip[i]=SAM::La;SAM::BD();
	dfs1(1,0);dfs2(1,1);for(i=1;i<=n;i++) II(Ip[i],i,n-i+1);
	scanf("%d",&m);for(i=1;i<=m;i++) scanf("%d%d",&X[i],&Y[i]),Ans[i]=Y[i]+1,IQ(X[i],Y[i],i);
	for(i=1;i<=SAM::Ct;i++) if(Tp[i]==i){
		sort(P[i].begin(),P[i].end(),C1);sort(Q[i].begin(),Q[i].end(),C2);
		int R=0;for(Ques j:Q[i]){
			while(R<P[i].size()&&P[i][R].Ls+P[i][R].x>=j.y+1) BIT::Ins(P[i][R].x),R++;
			int p=BIT::Find(BIT::Qry(max(j.x,j.y+1-j.Ls)-1));if(p<=j.y)Ans[j.id]=min(Ans[j.id],p);
		}
		for(j=0;j<R;j++) BIT::Cl(P[i][j].x);
	}
	for(i=1;i<=m;i++) printf("%d\n",Y[i]-Ans[i]+1);
}
```



---

