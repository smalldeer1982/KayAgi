# [BalticOI 2025] Exponents

## 题目描述

著名博学家尼古拉·哥白尼于 15 世纪在托伦出生并长大。考古学家最近发现了他的笔记本，了解到他喜欢用 2 的幂次来存储大数。特别是，当他将两个 2 的幂次相加时：

$$2^{a}+2^{b}$$

哥白尼会先计算结果，然后将结果向上舍入到最近的 2 的幂次。也就是说，他会将 $2^{a}+2^{b}$ 计算为 $2^{\max(a, b)+1}$。对于更长的表达式：

$$2^{b_{1}}+2^{b_{2}}+\ldots+2^{b_{k}}$$

他会先插入括号使其成为良好括号化表达式$\text{*}$。例如，表达式 $2^{5}+2^{4}+2^{4}+2^{4}+2^{5}$ 可以通过插入括号变为 $((2^{5}+2^{4})+(2^{4}+(2^{4}+2^{5})))$。最后，他按照上述方式计算这个良好括号化表达式的结果。注意，计算结果可能因括号插入方式的不同而有所变化。例如，以下是两种可能的计算方式：

$$((2^{5}+2^{4})+2^{4})+(2^{4}+2^{5}))=((2^{6}+2^{4})+2^{6})=(2^{7}+2^{6})=2^{8} \\((2^{5}+(2^{4}+2^{4}))+(2^{4}+2^{5}))=((2^{5}+2^{5})+2^{6})=(2^{6}+2^{6})=2^{7}$$

哥白尼笔记本的第一页仅包含一个称为**主表达式**的表达式 $2^{a_{1}}+2^{a_{2}}+\ldots+2^{a_{n}}$。笔记本后面的页面引用了主表达式的片段，这些片段的格式为 $2^{a_{\ell}}+2^{a_{\ell+1}}+\ldots+2^{a_{r}}$，其中 $1 \leq \ell \leq r \leq n$。

你不确定这些片段的含义，但怀疑应该为每个片段计算其可能的最小结果（按照上述方式计算）。注意，每个片段是独立于其他片段计算的。

$\text{*}$关于“良好括号化表达式”的形式化定义如下：对于任意非负整数 $a$，$2^{a}$ 是一个良好括号化表达式；如果 $E_{1}$ 和 $E_{2}$ 都是良好括号化表达式，那么 $(E_{1} + E_{2})$ 也是良好括号化表达式。除此之外没有其他形式的良好括号化表达式。

## 说明/提示

### 评分

| 子任务 | 限制条件 | 分值 |
| :---: | :---: | :---: |
| 1 | $n \leq 8, q \leq 10$ | 6 |
| 2 | $n \leq 200$ | 8 |
| 3 | $n, q \leq 2000$ | 23 |
| 4 | $a_{i} \leq 20$ | 22 |
| 5 | 无额外限制。 | 41 |

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8 4
2 4 2 5 4 4 4 5
4 8
1 4
2 5
1 7```

### 输出

```
7
7
7
8```

# 题解

## 作者：min_inf (赞：2)

设 $b_i=\max(a_i,a_{i+1})$，考虑在 $b$ 上操作，每次操作就是删掉一个数 $x$ 并且两侧都对 $x+1$ 取 $\max$。然后肯定是删最小的影响最小，考虑一个长度为 $l$ 的最小值 $x$ 的连续段，至少会操作出 $\lfloor \frac l 2 \rfloor$ 个 $x+1$。然后单次询问就可以直接在笛卡尔树上 DP 了。

考虑怎么刻画一个区间的笛卡尔树，找到最大值，然后就是最大值左侧所有前缀 $\max$（单调栈上的树）的右子树和右侧所有后缀 $\max$ 的左子树。

然后我们要在维护单调栈的同时维护笛卡尔树上的 DP 值。假如没有相同的数，我们暴力往上跳直到 DP 值没有变化，由于修改一定是增加，经过 $\log n$ 次后是一串 $+1$，经过的都是奇数变成偶数，而每次只会增加 $\log n$ 的势能，时间复杂度就是 $O(n\log n)$ 的。

考虑有相同的数的情况，我们建两棵笛卡尔树，分别认为相同的数左侧/右侧大，解决第一个最大值左侧和最后一个最大值右侧的情况，中间的部分可以在随便一棵树上前缀和一下。时间复杂度 $O((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ui = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(l);i>=(r);--i)
#define repn(i,n) for(int i=0;i<(n);++i)
#define sizc(x) ((int)(x).size())
#define allc(x) (x).begin(),(x).end()
#define fir first
#define sec second

constexpr int N = 3e5+5;
constexpr int S(int x,int y){return y<32?x>>y:0;}

int n,m;
int a[N],b[N];
int ls[N],rs[N],f[N];
void dfs1(int u){
    if(!u)return;
    dfs1(ls[u]),dfs1(rs[u]);
    f[u]=S(f[ls[u]],a[u]-a[ls[u]])+S(f[rs[u]],a[u]-a[rs[u]])+1;
}
int L(int u){return S(f[ls[u]],a[u]-a[ls[u]])+1;}
int R(int u){return S(f[rs[u]],a[u]-a[rs[u]])+1;}

int stk[N],tp,fs[N];
int sl[N];
void dfs2(int u,int fa){
    if(!u)return;
    sl[u]=sl[fa]+L(u);
    dfs2(ls[u],u),dfs2(rs[u],u);
}

int ans[N],cnt[N];
vector<pair<int,int>> Ql[N],Qr[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin>>n>>m;rep(i,1,n)cin>>b[i];
    rep(i,1,n-1)a[i]=max(b[i],b[i+1]);--n;
    rep(i,1,m){
        int l,r;cin>>l>>r;
        if(l==r)ans[i]=b[l];
        else{
            --r;
            Ql[l].emplace_back(r,i);
            Qr[r].emplace_back(l,i);
        }
    }
    rep(i,1,n){
        int lst=0;while(tp&&a[stk[tp]]<a[i])lst=stk[tp--];
        rs[stk[tp]]=i,ls[stk[++tp]=i]=lst;
    }dfs1(rs[0]),dfs2(rs[0],0);
    tp=0;per(i,n,1){
        while(tp&&a[stk[tp]]<=a[i])--tp;
        stk[++tp]=i;fs[tp]=R(i);
        int p=tp;while(p>1){
            int w=R(stk[p-1])+S(fs[p],a[stk[p-1]]-a[stk[p]]);
            if(w!=fs[p-1])fs[--p]=w;else break;
        }
        for(auto [r,id]:Ql[i]){
            p=lower_bound(stk+1,stk+tp+1,r,greater<int>())-stk;
            cnt[id]=-sl[stk[p]],ans[id]=a[stk[p]];
            if(p<tp)cnt[id]+=S(fs[p+1],a[stk[p]]-a[stk[p+1]]);
        }
    }
    rep(i,1,n)ls[i]=rs[i]=0;tp=0;
    rep(i,1,n){
        int lst=0;while(tp&&a[stk[tp]]<=a[i])lst=stk[tp--];
        rs[stk[tp]]=i,ls[stk[++tp]=i]=lst;
    }dfs1(rs[0]);
    tp=0;rep(i,1,n){
        while(tp&&a[stk[tp]]<=a[i])--tp;
        stk[++tp]=i;fs[tp]=L(i);
        int p=tp;while(p>1){
            int w=L(stk[p-1])+S(fs[p],a[stk[p-1]]-a[stk[p]]);
            if(w!=fs[p-1])fs[--p]=w;else break;
        }
        for(auto [l,id]:Qr[i]){
            p=lower_bound(stk+1,stk+tp+1,l)-stk;
            cnt[id]+=sl[stk[p]]+1;
            if(p<tp)cnt[id]+=S(fs[p+1],a[stk[p]]-a[stk[p+1]]);
        }
    }
    rep(i,1,m)cout<<ans[i]+(cnt[i]?__lg(cnt[i])+1:0)<<'\n';
}
```

---

## 作者：_Ch1F4N_ (赞：2)

考虑一个暴力做法，我们直接猜每次把 $\max$ 最小的相邻对合并即可。

然而这样其实不对，手摸一组全部相同的数据后，你发现你需要优先选择最靠前的相邻对。

考虑更好的刻画我们在干啥，我们希望将找出相邻 $\max$ 最小相邻对这个过程更加直观，于是不妨记 $b_i = \max(a_i,a_{i+1})$，我们的操作实际上是选择最靠前的最小 $b_i$ 将其删掉后将 $b_{i-1},b_{i+1}$ 与 $b_i+1$ check max。

现在回过头看这个为啥是对的，你发现对于最小的 $b_i$ 将其删掉只会对同样是值最小的 $b_i$ 产生影响，而现在不删后面如果这个位置被影响了再删就会产生更大的影响，所以应该现在删掉，对于一段连续的最小 $b_i$ 显然是从前往后删所新产生的 $b_{i}+1$ 最少，并且你发现最少数量恰好是原 $b_i$ 数量的一半下取整。

于是得到了一个更有前途的做法，将 $b_i$ 分成若干连续段，每次取出最小的连续段长度减半并让值增加 $1$，然后能合并连续段就合并。

先对全局从大往小将每个数的连续段找出来建一个广义笛卡尔树状物。并处理出每个点对其父亲的贡献。

考虑对于区间怎么算，不妨设区间最大值为 $u$，先找出全局处理出来的 $u$ 的连续段，区间内完整包含的处理权值为 $u$ 的情况的广义笛卡尔树上点的贡献可以通过前缀和预处理与二分计算出来，现在问题是对于没有被完整包含的点计算贡献。

注意到这些不完整部分形如一个前缀后缀，并且贡献在固定一个端点时显然关于另一个端点存在单调性，所以考虑对着贡献大小找做法。

关键结论，所有点的贡献之和是 $O(n)$ 量级的。

考虑计算贡献的方式，一个点所有非最大值类型儿子的贡献除掉至少 $2$ 后加和，再加上最大值类型儿子的数量。

不妨令 $Q_i$ 表示第 $i$ 层贡献和，有 $Q_i \leq \frac{Q_{i+1}}{2}+w_i$，其中 $\sum w_i = n$，有 $\sum Q_i = \sum w_i \times \sum_{j=0}^{i-1} 2^{-j} \leq 2 \times \sum w_i = 2 \times n$。

所以我们考虑对于每个结点处理出使得其贡献为 $i$ 的最短前缀最短后缀，这个又该怎么处理呢。

注意到我们是在树这个特殊的结构上处理问题，考虑利用树形结构从下往上求解。

知道一个点所有儿子的分界点后，可以考虑到由于暴力计算贡献的方式是先将儿子做完然后合并儿子上的连续段再处理其对父亲的贡献，所以一个结点的前后缀对父亲的贡献就是其对自己的贡献除以 $2$ 的若干次方下取整，因此其对父亲贡献的分界点就是对自己贡献的分界点进行若干次合并后的结果，注意到每次合并分界点数量减半故可以暴力合并，然后将所有儿子的分界点按顺序拼接即可，总复杂度是 $O(\sum Q_i) = O(n)$。

询问只需要求出区间最大值再二分出包含的广义笛卡尔树上结点范围即可，由于我用了 ST 表所以时间复杂度是 $O((n+q) \log n)$。


```cpp
#include<bits/stdc++.h>
#define ve vector
#define fst first
#define scd second
#define pb push_back
using namespace std;
const int maxn = 1e6+114;
int b[maxn],a[maxn],n,q;
ve<int> pos[maxn];
const int maxs = 3e5+114;
int st[maxs][20];
int lg[maxs];
void ST(){
    for(int i=1;i<n;i++){
        st[i][0]=a[i];
    }
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<n;i++) st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
    lg[1]=0;
    for(int i=2;i<n;i++) lg[i]=lg[i/2]+1;
}
int ask(int l,int r){
    int len=lg[r-l+1];
    return max(st[l][len],st[r-(1<<len)+1][len]);
}
ve< pair< pair<int,int>,pair< ve<int>,ve<int> > > > seq[maxn];//[l,r] 前缀后缀贡献变化位置
ve<int> sum[maxn];
pair< ve<int>,ve<int> > build(int l,int r){
    int mx=ask(l,r);
    int lt=-1,rt=pos[mx].size()-1;
    while(lt+1<rt){
        int mid=(lt+rt)>>1;
        if(pos[mx][mid]>=l) rt=mid;
        else lt=mid;
    }
    int beg=rt,tai=rt;
    for(int i=beg;i<pos[mx].size();i++){
        if(pos[mx][i]<=r) tai=i;
        else break;
    }
    ve<int> pre,suf;
    if(pos[mx][beg]!=l){
            auto it=build(l,pos[mx][beg]-1);
            for(int i=ask(l,pos[mx][beg]-1);i<mx;i++){
                pair< ve<int>,ve<int> > nit;
                for(int j=0;j<it.fst.size();j++){
                    if(j&1) nit.fst.pb(it.fst[j]);
                    if((it.fst.size()-j-1)&1) nit.scd.pb(it.scd[j]);
                }
                swap(nit,it);
                if(it.fst.size()==0) break;
            }
            seq[mx].pb(make_pair(make_pair(l,pos[mx][beg]-1),it));
            for(int i=0;i<it.fst.size();i++) pre.pb(it.fst[i]),suf.pb(it.scd[i]);
    }
    for(int i=beg;i<=tai;){
        bool flag=false;
        for(int j=i+1;j<=tai;j++){
            if(pos[mx][j]!=pos[mx][j-1]+1){
                pair< ve<int>,ve<int> > vec;
                for(int k=i;k<j;k++) pre.pb(pos[mx][k]),suf.pb(pos[mx][k]),vec.fst.pb(pos[mx][k]),vec.scd.pb(pos[mx][k]);
                seq[mx].pb(make_pair(make_pair(pos[mx][i],pos[mx][j-1]),vec));
                auto it=build(pos[mx][j-1]+1,pos[mx][j]-1);
                for(int k=ask(pos[mx][j-1]+1,pos[mx][j]-1);k<mx;k++){
                    pair< ve<int>,ve<int> > nit;
                    for(int p=0;p<it.fst.size();p++){
                        if(p&1) nit.fst.pb(it.fst[p]);
                        if((it.fst.size()-p-1)&1) nit.scd.pb(it.scd[p]);
                    }
                    swap(nit,it);
                    if(it.fst.size()==0) break;
                }
                seq[mx].pb(make_pair(make_pair(pos[mx][j-1]+1,pos[mx][j]-1),it));
                for(int k=0;k<it.fst.size();k++) pre.pb(it.fst[k]),suf.pb(it.scd[k]);
                i=j;
                flag=true;
                break;
            }
        }
        if(flag==false){
            pair< ve<int>,ve<int> > vec;
            for(int j=i;j<=tai;j++){
                pre.pb(pos[mx][j]),suf.pb(pos[mx][j]),vec.fst.pb(pos[mx][j]),vec.scd.pb(pos[mx][j]);
            }
            seq[mx].pb(make_pair(make_pair(pos[mx][i],pos[mx][tai]),vec));
            break;
        }
    }
    if(pos[mx][tai]!=r){
            auto it=build(pos[mx][tai]+1,r);
            for(int i=ask(pos[mx][tai]+1,r);i<mx;i++){
                pair< ve<int>,ve<int> > nit;
                for(int j=0;j<it.fst.size();j++){
                    if(j&1) nit.fst.pb(it.fst[j]);
                    if((it.fst.size()-j-1)&1) nit.scd.pb(it.scd[j]);
                }
                swap(nit,it);
                if(it.fst.size()==0) break;
            }
            seq[mx].pb(make_pair(make_pair(pos[mx][tai]+1,r),it));
            for(int i=0;i<it.fst.size();i++) pre.pb(it.fst[i]),suf.pb(it.scd[i]);
    }
    return make_pair(pre,suf);
}
int solve(int l,int r){
    int mx=ask(l,r);
    int lt=-1,rt=seq[mx].size()-1;
    while(lt+1<rt){
        int mid=(lt+rt)>>1;
        if(seq[mx][mid].fst.scd>=l) rt=mid;
        else lt=mid;
    }
    int beg=rt;
    lt=0,rt=seq[mx].size();
    while(lt+1<rt){
        int mid=(lt+rt)>>1;
        if(seq[mx][mid].fst.fst<=r) lt=mid;
        else rt=mid;
    }
    int tai=lt;
    if(beg==tai) return r-l+1;
    int res=sum[mx][tai-1]-sum[mx][beg];
    if(seq[mx][beg].scd.scd.size()>0&&seq[mx][beg].scd.scd.back()>=l){
        lt=-1,rt=seq[mx][beg].scd.scd.size()-1;
        while(lt+1<rt){
            int mid=(lt+rt)>>1;
            if(seq[mx][beg].scd.scd[mid]>=l) rt=mid;
            else lt=mid;
        }
        res+=(seq[mx][beg].scd.scd.size()-1)-rt+1;
    }
    if(seq[mx][tai].scd.fst.size()>0&&seq[mx][tai].scd.fst[0]<=r){
        lt=0,rt=seq[mx][tai].scd.fst.size();
        while(lt+1<rt){
            int mid=(lt+rt)>>1;
            if(seq[mx][tai].scd.fst[mid]<=r) lt=mid;
            else rt=mid;
        }
        res+=lt+1;
    }
    return res;
}
const int top = 1e6;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    if(n==1){
        while(q--){
            int l,r;
            cin>>l>>r;
            cout<<b[l]<<"\n";
        }
        return 0;
    }
    for(int i=1;i<n;i++) a[i]=max(b[i],b[i+1]),pos[a[i]].pb(i);
    ST();
    build(1,n-1);
    for(int i=0;i<=top;i++){
        if(seq[i].size()>0) sum[i].pb(seq[i][0].scd.fst.size());
        for(int j=1;j<seq[i].size();j++){
            sum[i].pb(sum[i].back()+seq[i][j].scd.fst.size());
        }
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        if(l==r) cout<<b[l]<<"\n";
        else{
            r--;
            int sum=solve(l,r);
            int ans=ask(l,r);
            while(sum>0) ans++,sum/=2;
            cout<<ans<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

主播终于战胜了这道题。感觉难点全在第一步转化上。

先特判 $l=r$ 的情况。然后看如何单组询问。不妨设 $l=1$，$r=n$。

设 $b_i = \max\{a_i,a_{i+1}\}$。问题的本质是：选择一个 $b_i$，如果 $b_{i-1}$ 和 $b_{i+1}$ 存在就对 $b_i+1$ 做 $\rm checkmax$，然后将 $b_i$ 删掉。

发现一个长度为 $k$ 的 $b_i=B$ 连续段（要求左右两边都不比 $B$ 小），可以通过这个过程变成长度为 $\lfloor \frac{k}{2} \rfloor$ 的 $b_i=B+1$ 的连续段。

所以肯定是贪心，每次选出最小的数将其加一。这样可以建出广义笛卡尔树在上面 DP。

![](https://img.picui.cn/free/2025/05/28/6836938eca05d.png)

这是一个广义笛卡尔树的例子。

而本题希望我们求出区间笛卡尔树信息。

比如我们需要求出 $[l,r]$ 的笛卡尔树。我们考虑求出最大值 $mx$，以及其最靠左和最靠右的出现位置 $lpos$ 和 $rpos$。

1. $[lpos,rpos]$ 之间的笛卡尔树，和全局笛卡尔树对应子树相同。

这个结论是显然的。

2. $[l,lpos)$ 之间的笛卡尔树，和 $[l,n]$ 对应子树相同。$(rpos,r]$ 是同理的。

这个结论依然是显然的。

我们最终只需要求出，把所有数都变成 $mx$ 之后还有多少个，因此只用关心子树信息。

对于类型 $1$，我们可以求出所有 $(i,j)$ 满足：$b_i=b_j$，且 $\min\{b_i,b_j\} > \max_{i < k < j} b_k$，$(i,j)$ 中所有数合并成 $b_i$ 的时候还剩多少个。查询的时候使用前缀和即可。

对于类型 $2$，我们考虑学习笛卡尔树的时候使用的线性建树的方法。维护后若干个数的单调栈，它表示了笛卡尔树上的一条左子树链。插入一个数的时候，会对树的形态产生改变。

假设我们新增了点 $u$，显然对于 $u$ 的所有父亲的 DP 数组都应该被改变。我们可以直接暴力更新。因为 DP 值的总变化量为 $O(n)$。你访问一次，一定会带来一次 DP 的变化。那么复杂度就对了。

代码可能有一些细节，我写的比较丑陋，凑合着看吧。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,q,a[MAXN],cnt[MAXN],rnk[MAXN],nxt[MAXN];

map<int,vector<int>> occ,qr;
map<int,int> tmp;
pair<int,int> st1[MAXN][20],st2[MAXN][20];
vector<int> qr1[MAXN],qr2[MAXN];

int st[MAXN],dp[MAXN],tot;
int l[MAXN],r[MAXN],mx[MAXN],lpos[MAXN],rpos[MAXN],ans[MAXN];
pair<int,int> query1(int l,int r) {
	int k=__lg(r-l+1);
	return max(st1[l][k],st1[r-(1<<k)+1][k]);	
}
pair<int,int> query2(int l,int r) {
	int k=__lg(r-l+1);
	return max(st2[l][k],st2[r-(1<<k)+1][k]);	
}
int Div(int x,int y) {
	if(y<=30) {
		ffor(i,1,y) x>>=1;
		return x;	
	}
	return 0;	
}
int suf[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
    ffor(i,1,q) {
        cin>>l[i]>>r[i];
        if(l[i]==r[i]) mx[i]=a[l[i]];
    }
	n--;
	ffor(i,1,n) a[i]=max(a[i],a[i+1]);
	cnt[1]=1;
	ffor(i,2,n) cnt[i]=cnt[i>>1]+1;
	ffor(i,1,n) st1[i][0]={a[i],i},st2[i][0]={a[i],-i};
	ffor(i,1,19) for(int l=1,r=(1<<i);r<=n;l++,r++) st1[l][i]=max(st1[l][i-1],st1[l+(1<<i-1)][i-1]),st2[l][i]=max(st2[l][i-1],st2[l+(1<<i-1)][i-1]);
	ffor(i,1,q) {
        r[i]--;
        if(l[i]>r[i]) continue ;
		auto pr1=query1(l[i],r[i]),pr2=query2(l[i],r[i]);	
		mx[i]=pr1.first,lpos[i]=-pr2.second,rpos[i]=pr1.second;
		if(a[r[i]]!=mx[i]) qr1[r[i]].push_back(i);
		if(a[l[i]]!=mx[i]) qr2[l[i]].push_back(i);
		qr[mx[i]].push_back(i);
	}
	ffor(i,1,n) rnk[i]=++tmp[a[i]],occ[a[i]].push_back(i);
	
	
	ffor(i,1,n) {
		int lst=0,del=0,lv=0;
		while(tot&&a[i]>a[st[tot]]) lv=a[st[tot]],del=dp[tot],lst=dp[tot],--tot;
		lst=Div(lst,(a[i]-lv))+1;
		if(tot&&a[i]==a[st[tot]]) lv=a[i],nxt[st[tot]]=lst-1,del=dp[tot],lst=dp[tot]+1,--tot;
		++tot,st[tot]=i,dp[tot]=lst;
		roff(i,tot-1,1) {
			int val=dp[i]-Div(del,(a[st[i]]-lv))+Div(dp[i+1],(a[st[i]]-a[st[i+1]]));
			if(val==dp[i]) break ;
			del=dp[i],dp[i]=val,lv=a[st[i]];
		}
		for(auto id:qr1[i]) {
			int l=1,r=tot,res=0;
			while(l<=r) {
				int mid=(l+r>>1);	
				if(a[st[mid]]>=mx[id]) res=mid,l=mid+1;
				else r=mid-1;
			}
			ans[id]+=Div(dp[res+1],(mx[id]-a[st[res+1]]));
		}
	}
	tot=0,memset(dp,0,sizeof(dp)),memset(st,0,sizeof(st));
	
	roff(i,n,1) {
		int lst=0,del=0,lv=0;
		while(tot&&a[i]>a[st[tot]]) lv=a[st[tot]],del=dp[tot],lst=dp[tot],--tot;
		lst=Div(lst,(a[i]-lv))+1;
		if(tot&&a[i]==a[st[tot]]) lv=a[i],del=dp[tot],lst=dp[tot]+1,--tot;
		++tot,st[tot]=i,dp[tot]=lst;
		roff(i,tot-1,1) {
			int val=dp[i]-Div(del,(a[st[i]]-lv))+Div(dp[i+1],(a[st[i]]-a[st[i+1]]));
			if(val==dp[i]) break ;
			del=dp[i],dp[i]=val,lv=a[st[i]];
		}
		for(auto id:qr2[i]) {
			int l=1,r=tot,res=0;
			while(l<=r) {
				int mid=(l+r>>1);	
				if(a[st[mid]]>=mx[id]) res=mid,l=mid+1;
				else r=mid-1;
			}
			ans[id]+=Div(dp[res+1],(mx[id]-a[st[res+1]]));
		}
	}
	
	for(auto pr:qr) {
		int av=pr.first;
		vector<int> vc=occ[av];
		suf[tmp[av]+1]=0;
		roff(i,tmp[av],1) suf[i]=suf[i+1]+nxt[vc[i-1]];
		for(auto qid:pr.second) {
			int lid=rnk[lpos[qid]],rid=rnk[rpos[qid]];
			ans[qid]+=rid-lid+1+suf[lid]-suf[rid];
		}
	}
	
	ffor(i,1,q) cout<<mx[i]+cnt[ans[i]]<<'\n';
	return 0;
}
```

---

## 作者：Mr_罗 (赞：0)

简单题。

先考虑怎么做单组。把所有最大值拎出来，剩下的位置递归下去贪心地合并成尽可能少的、等于最大值的块，然后一堆块的代价是好算的。代码如下：

```cpp
pii slv(int l, int r) {
    if (l > r) return pii(-1, 0);
    int mx = 0, t = l, c = 0;
    rep(i, l, r) chkmx(mx, a[i]); // 最大值
    rep(i, l, r) if (a[i] == mx) {
        c++; auto [x, y] = slv(t, i - 1); t = i + 1;
        int z = bit(min(30, mx - x)); c += (y + z - 1) / z;
        // 递归下去之后会合并成一堆等于那个子区间最大值的块，把它们两两合并直到等于最大值
    } auto [x, y] = slv(t, r);
    int z = bit(min(30, mx - x)); c += (y + z - 1) / z;
    return pii(mx, c);
}

// 查询
auto [x, y] = slv(l, r);
x + lg2(y) + (y != lowbit(y)) // 答案
```

做多组就离线下来。设当前区间相邻两个最大值位置是 $u,v$，那么我们需要维护出 $(u,v)$ 这个子区间划分成若干等于 $\max\{a_i\mid u<i<v\}$ 的块，再从左到右贪心地合并成若干等于 $a_u$ 的块，再维护一个从右到左的（递归下去时也要是从右到左的），这样一次查询时最大值块的个数就是中间若干整块加上左边后半块加右边前半块，直接算就好了。

时间复杂度 $\mathcal O(n\log^2n)$。

```cpp
int n, m;
int tt;
int a[N];
int ans[N];
int xm[21][N];
vi va[M];
struct Q { int l, r, i; } q[N], _q[N];
vector<Q> vq[N << 5], vQ[M];

bool operator<(const Q &i, const Q &j) {
    return i.l == j.l ? i.r < j.r : i.l < j.l;
}

int qry(int l, int r) {
    int k = lg2(r - l + 1);
    return max(xm[k][l], xm[k][r - bit(k) + 1]);
}

void init(int l, int r) {
    if (l > r) return;
    int mx = qry(l, r); vi vt{l - 1}, vs, sv;
    vQ[mx].eb(Q{l, r, tt});
    int p = lower_bound(all(va[mx]), l) - va[mx].begin();
    while (p < va[mx].size() && va[mx][p] <= r)
        vt.eb(va[mx][p]), p++;
    vt.eb(r + 1), vs.rsz(vt.size()), sv.rsz(vt.size());
    req(i, 1, vt.size()) tt++, init(vt[i - 1] + 1, vt[i] - 1);
}

pair<vector<Q>, vector<Q>> slv(int l, int r) {
    if (l > r) return mkpr(vector<Q>{}, vector<Q>{});
    int mx = qry(l, r); vi vt{l - 1}, vs, sv;
    vQ[mx].eb(Q{l, r, tt});
    int p = lower_bound(all(va[mx]), l) - va[mx].begin();
    while (p < va[mx].size() && va[mx][p] <= r)
        vt.eb(va[mx][p]), p++;
    vt.eb(r + 1), vs.rsz(vt.size()), sv.rsz(vt.size());
    vector<Q> vo, ov; int I = tt;
    req(i, 1, vt.size()) {
        vector<Q> vp, pv, up; tt++;
        auto pp = slv(vt[i - 1] + 1, vt[i] - 1); vp = pp.fi, pv = pp.se;
        if (!vp.empty()) {
            int x;
            while (vp.size() > 1 && (x = vp[0].i) < mx) {
                req(j, 0, vp.size() >> 1) {
                    auto u = vp[j << 1], v = vp[j << 1 | 1];
                    up.eb(Q{u.l, v.r, max(u.i, v.i) + 1});
                } if (vp.size() & 1) up.eb(vp.back());
                vp = up, up.clear();
            } for (auto X : vp) vo.eb(X);
        }
        if (!pv.empty()) {
            int x; reverse(all(pv));
            while (pv.size() > 1 && (x = pv[0].i) < mx) {
                req(j, 0, pv.size() >> 1) {
                    auto u = pv[j << 1], v = pv[j << 1 | 1];
                    up.eb(Q{v.l, u.r, max(u.i, v.i) + 1});
                } if (pv.size() & 1) up.eb(pv.back());
                pv = up, up.clear();
            } reverse(all(pv)); for (auto X : pv) ov.eb(X);
        }
        if (i + 1 != iEnd) {
            vs[i] = vo.size();
            vo.eb(Q{vt[i], vt[i], mx});
            sv[i] = ov.size();
            ov.eb(Q{vt[i], vt[i], mx});
        }
    }
    for (auto x : vq[I]) {
        int u = lower_bound(all(vt), x.l) - vt.begin();
        int v = prev(upper_bound(all(vo), Q{x.r, inf, 0})) - vo.begin();
        int y = v - vs[u] + 1;
        v = prev(upper_bound(all(ov), Q{x.l, inf, 0})) - ov.begin();
        y += sv[u] - v;
        ans[x.i] = mx + lg2(y) + (y != lowbit(y));
    } return mkpr(vo, ov);
}

void mslv() {
    rd(n, m), rda(a, n);
    rep(i, 1, n) va[a[i]].eb(i), xm[0][i] = a[i];
    rep(k, 1, 20) rep(i, 1, n - bit(k) + 1)
        xm[k][i] = max(xm[k - 1][i], xm[k - 1][i + bit(k - 1)]);
    rep(i, 1, m) rd(q[i].l, q[i].r), q[i].i = i;
    rep(i, 1, n) sort(all(vq[i]));
    sort(q + 1, q + m + 1), init(1, n);
    req(i, 0, M) sort(all(vQ[i]));
    rep(i, 1, m) {
        int mx = qry(q[i].l, q[i].r);
        int x = prev(upper_bound(all(vQ[mx]), Q{q[i].l, inf, 0}))->i;
        vq[x].eb(q[i]);
    } tt = 0, slv(1, n);
    rep(i, 1, m) prs(ans[i]);
}
```

---

