# Orangutan Approved Subarrays

## 题目描述

Suppose you have an array $ b $ . Initially, you also have a set $ S $ that contains all distinct elements of $ b $ . The array $ b $ is called orangutan-approved if it can be emptied by repeatedly performing the following operation:

- In one operation, select indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq |b| $ ) such that $ v = b_l = b_{l+1} = \ldots = b_r $ and $ v $ is present in $ S $ . Remove $ v $ from $ S $ , and simultaneously remove all $ b_i $ such that $ l \leq i \leq r $ . Then, reindex the elements $ b_{r+1}, b_{r+2}, \ldots $ as $ b_l, b_{l+1}, \ldots $ accordingly.

You are given an array $ a $ of length $ n $ and $ q $ queries.

Each query consists of two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), and you need to determine whether or not the subarray $ a_{l}, a_{l+1}, \ldots, a_r $ is orangutan-approved.

## 说明/提示

In the first query of the first testcase, the answer is YES.

- Initially, $ S=\{1,2\} $ and $ b=[1,2,2,1] $
- Select $ l=2 $ and $ r=3 $ . Since $ b_2=b_3=2 $ is in $ S $ , we may erase $ b_2 $ and $ b_3 $ from the array, as well as erasing $ 2 $ from $ S $ . The set $ S $ becomes $ \{1\} $ and the array becomes $ [1,1] $ .
- Select $ l=1 $ and $ r=2 $ . Since $ b_1=b_2=1 $ is in $ S $ , we may erase $ b_1 $ and $ b_2 $ from the array, as well as erasing $ 1 $ from $ S $ . The set $ S $ becomes $ \{\} $ and the array becomes $ [] $ .
- Since the array is now empty, we can say the original array is orangutan-approved.

In the first query of the second testcase, the answer is NO, because it can be shown that the subarray $ [2,1,2,1] $ cannot become empty through any sequence of valid operations.

## 样例 #1

### 输入

```
3
4 2
1 2 2 1
1 4
1 3
5 3
1 2 1 2 1
2 5
3 5
1 3
8 4
1 2 3 2 1 3 2 3
1 5
2 8
3 5
6 8```

### 输出

```
YES
YES
NO
YES
YES
YES
NO
YES
YES```

# 题解

## 作者：happybob (赞：3)

题意：

有一个正整数集合 $S$，初始为空。称一个长度为 $n$ 的正整数序列 $a_1,a_2,\cdots,a_n$ 是好的，当且仅当可以通过若干次如下操作将序列删空：

每次选择序列的一段区间 $[l,r]$ 使得区间中所有数相同，且 $a_l \notin S$。删去 $a_{l},a_{l+1},\cdots,a_r$，并在 $S$ 中加入 $a_l$。

给定一个长度为 $n$ 的序列，$q$ 次询问，每次给定区间 $[l,r]$，判断 $a_l,a_{l+1},\cdots,a_r$ 是否是好的。

$n, q \leq 2 \times 10^5$，$1 \leq a_i \leq n$。

解法：

考虑固定 $l$，则使得 $[l,r]$ 是好的的 $r$ 必然是一段以 $l$ 开始的区间。我们希望对于每个 $l$ 求 $nxt_l$ 表示最大的合法 $r$。则询问相当于判断 $nxt_l \geq r$。

考虑双指针。容易发现在加入右侧一个数的时候，如果存在某种数，与这个数出现的位置有交但不包含则判定为不合法。考虑目前区间 $[l,r]$，对每个 $i \in [l,r]$ 维护 $pre_i$ 表示最大的 $j$ 满足 $a_j = a_i$ 且 $j \in [l,r]$。不存在则 $pre_i = +\infty$。容易发现往后加和在前面删都是单点修改区间求 $\min$，使用线段树维护，复杂度 $O(n \log n + q)$。

[Submission Link.](https://codeforces.com/contest/2030/submission/286743569)

---

## 作者：Hoks (赞：2)

## 前言
离结束 $50$ min 时想到的正解，但是给毙了，最后 $20$ min 拉出来写没写完遗憾离场。
## 思路分析
主要讲讲这种题在场上怎么样才能想到，想出来。

首先看到这玩意是定义了一种区间，并且多次询问给定区间。

这个感觉上就非常 DS，思考的时候尝试往 DS 靠。

这个时候就可以分出来很多种大致的走向了。

1. 区间询问，考虑使用线段树合并区间。

   这时我们需要考虑的就是区间两两之间能否快速合并，在这题看来是不太行的，直接毙了。
2. 大力莫队，结合 $3$ 秒实现大力做。

   注意到如果我们删掉了一个区间的一个数，要对后面的所有值相同的数都进行判定，显然爆了。
3. 找性质。

那这题也没什么办法了只能找性质了。

其实我们可以发现一个显而易见的单调性。

就是对于区间 $[l,r]$ 如果合法那么他的子区间 $[l',r']$ 肯定也是合法的。

为了证明这个东西，我们考虑怎么样的区间才是合法的。

其实也就是，对于每一种值 $i$ 处理出他的第一次出现位置为 $l_i$，最后一次出现位置为 $r_i$，那么就会形成一个区间 $[l_i,r_i]$，只要满足这些区间都不交就行了。

证明很 ez，如果区间是包含那就可以把里面的区间删了让外面的并起来。

如果区间是相交的话那么不管删哪边都还会剩下一半，所以显然不行。

那如果我们把这些区间之间，**看做是成对的带颜色的固定匹配的括号**，那我从合法的括号序列中截取一段，显然也是合法的。

所以我们有了一个单调性，**合法区间的子区间是合法区间**。

这就启发我们去找到所有的**极大合法子区间**。

其中极大即为不可再扩展。

根据刚刚那个单调性，我们考虑一个双指针的扩展过程。

钦定右端点 $r$，我们考虑计算左端点的最左位置。

首先考虑从原本的答案直接拿过来是否可行，若不行那便暴力加一。

其实就是原本答案 $[l,r-1]$ 合法的，$r$ 的添加导致把一些原本的括号对嵌套起来相交了。

那么我们直接计算出 $[l,lst_r]$ 这里区间最右右端点位置即可，如果越过了 $lst_r$ 就是相交了暴力移动 $l\leftarrow l+1$。

这个过程直接用线段树实现即可。

其实如果场上想清楚一点 $20$ min 完全够写了。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,M=21,V=2e5,INF=1e18,mod=998244353;
int n,m,tot,a[N],L[N],lst[N],t[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void modify(int p,int l,int r,int x,int w)
{
    if(l==r) return t[p]=w,void();
    (mid>=x)?(modify(ls,l,mid,x,w)):(modify(rs,mid+1,r,x,w));
    t[p]=max(t[ls],t[rs]);
}
inline void clear(int p,int l,int r){t[p]=0;if(l==r) return;clear(ls,l,mid);clear(rs,mid+1,r);}
inline int query(int p,int l,int r,int s,int e)
{
    if(e<s) return 0;if(l>=s&&r<=e) return t[p];int res=0;
    if(mid>=s) res=query(ls,l,mid,s,e);
    if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
    return res;
}
inline void solve()
{
    n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1,l=1;i<=n;i++)
    {
        int r=lst[a[i]];while(query(1,1,n,l,r)>r) l++;
        if(r) modify(1,1,n,r,i);L[i]=l;lst[a[i]]=i;
    }
    for(int i=1,l,r;i<=m;i++) l=read(),r=read(),put(L[r]<=l?"Yes\n":"No\n");
    for(int i=1;i<=n;i++) lst[a[i]]=0;clear(1,1,n);
}
signed main()
{
    int T=1;
    T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：rainygame (赞：0)

感觉自己比较牛想到了这道题，来一篇题解。

首先这个东西一看就不好莫队/线段树合并信息，所以考虑找充要。

可以注意到一个区间不合法当且仅当存在 $i<j<k<l$ 满足 $a_i=a_k,a_j=a_l,a_i\ne a_k$。这其实相当于存在 `ABAB` 的情况，可以感性理解一下。

那么就好做了，设 $p_i$ 表示上一个 $a_i$ 出现的位置，那么设 $v_i=\max\limits_{j=p_i+1}^{i-1}[p_j<p_i]p_j$，则合法当且仅当 $\max\limits_{i=l}^rv_i < l$。

$v_i$ 可以用主席树上二分求，答案相当于一个二维偏序，离线后扫描线即可（具体地，把询问按 $l$ 排序，每次添加一些 $v_i<l$ 的 $i$，查询区间内是否有数被添加即可），时空复杂度均为 $O(n \log n)$。

[submission](https://codeforces.com/problemset/submission/2030/299458602)

---

## 作者：lfxxx (赞：0)

首先化简限制。

由于一种颜色只能消除一次，所以不能出现形如满足 $i<j<k<w$ 使得 $a_i=a_k,a_j=a_w$。

也就是不能出现两个端点相同颜色的区间相交。

假若存在相交的区间，对于其中任意一个区间，一定可以不断地把左端点向右移或者把右端点向左移直到两个端点是相邻的两个同色点。

令 $nxt_i$ 表示 $i$ 后面第一个同色点，条件等价于不存在 $i < j < nxt_i < nxt_j \leq r$。

在固定 $r$ 时，$l$ 显然有单调性，于是考虑双指针，check 形如一个区间 rmq 与单点修改（需要将 $nxt_i > r$ 的 $nxt_i$ 设置为 $0$）用你喜欢的数据结构维护即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int a[maxn],nxt[maxn];
int cnt[maxn];
vector<int> vec[maxn];
int tr[maxn<<2];
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur]=nxt[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    tr[cur]=max(tr[cur<<1],tr[cur<<1|1]);
}
int query(int cur,int lt,int rt,int l,int r){
    if(l>r) return 0;
    if(l<=lt&&rt<=r) return tr[cur];
    if(r<lt||rt<l) return 0;
    int mid=(lt+rt)>>1;
    return max(query(cur<<1,lt,mid,l,r),query(cur<<1|1,mid+1,rt,l,r));
}
void del(int cur,int lt,int rt,int pos){
    if(lt==rt){
        tr[cur]=0;
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid) del(cur<<1,lt,mid,pos);
    else del(cur<<1|1,mid+1,rt,pos);
    tr[cur]=max(tr[cur<<1],tr[cur<<1|1]);
}
int n,q;
int minl[maxn];
void work(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i],cnt[i]=0;
    for(int i=n;i>=1;i--){
        nxt[i]=cnt[a[i]];
        cnt[a[i]]=i;
        vec[nxt[i]].push_back(i);
    }
    build(1,1,n);
    int l=n+1,r=n+1;
    while(r>1){
        r--;
        if(r!=n){
            for(int x:vec[r+1]) del(1,1,n,x);
        }
        while(l>1&&min(r,query(1,1,n,l,nxt[l-1]-1))<=nxt[l-1]) l--;
        minl[r]=l;
    }
    while(q--){
        int ql,qr;
        cin>>ql>>qr;
        cout<<(ql>=minl[qr]?"YES\n":"NO\n");
    }
    for(int i=1;i<=n+1;i++) vec[i].clear();
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
5 5
1 2 1 1 1
1 5
2 5
3 5
4 5
5 5
*/
```

---

