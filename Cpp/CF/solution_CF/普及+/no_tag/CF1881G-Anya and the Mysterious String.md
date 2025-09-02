# Anya and the Mysterious String

## 题目描述

Anya received a string $ s $ of length $ n $ brought from Rome. The string $ s $ consists of lowercase Latin letters and at first glance does not raise any suspicions. An instruction was attached to the string.

Start of the instruction.

A palindrome is a string that reads the same from left to right and right to left. For example, the strings "anna", "aboba", "level" are palindromes, while the strings "gorilla", "banan", "off" are not.

A substring $ [l \ldots r] $ of string $ s $ is a string $ s_l s_{l+1} \ldots s_{r-1} s_r $ . For example, the substring $ [4 \ldots 6] $ of the string "generation" is the string "era".

A string is called beautiful if it does not contain a substring of length at least two that is a palindrome. For example, the strings "fox", "abcdef", and "yioy" are beautiful, while the strings "xyxx", "yikjkitrb" are not.

When an integer $ x $ is added to the character $ s_i $ , it is replaced $ x $ times with the next character in the alphabet, with "z" being replaced by "a".

When an integer $ x $ is added to the substring $ [l, r] $ of string $ s $ , it becomes the string $ s_1 s_2 \ldots s_{l-1} (s_l + x) (s_{l+1} + x) \ldots (s_{r-1} + x) (s_r + x) s_{r+1} \ldots s_n $ . For example, when the substring $ [2, 4] $ of the string "abazaba" is added with the number $ 6 $ , the resulting string is "ahgfaba".

End of the instruction.

After reading the instruction, Anya resigned herself to the fact that she has to answer $ m $ queries. The queries can be of two types:

1. Add the number $ x $ to the substring $ [l \ldots r] $ of string $ s $ .
2. Determine whether the substring $ [l \ldots r] $ of string $ s $ is beautiful.

## 说明/提示

In the first test case of the first test, the following happens:

- tedubcyyxopz: the string edub is beautiful;
- tedubcyyxopz $ \to $ tedwdeaaxopz;
- tedwdeaaxopz: the string tedwdea is not beautiful as it contains the palindrome edwde;
- tedwdeaaxopz $ \to $ terkreaaxopz;
- terkreaaxopz $ \to $ terkreaaarsz;
- terkreaaarsz $ \to $ terkreaaaasz;
- terkreaaaasz: the string kreaaaa is not beautiful as it contains the palindrome aaaa;
- terkreaaaasz: the string asz is beautiful.

## 样例 #1

### 输入

```
5
12 8
tedubcyyxopz
2 2 5
1 4 8 2
2 1 7
1 3 5 40
1 9 11 3
1 10 10 9
2 4 10
2 10 12
10 4
ubnxwwgzjt
2 4 10
2 10 10
1 6 10 8
2 7 7
11 3
hntcxfxyhtu
1 4 6 1
2 4 10
1 4 10 21
13 2
yxhlmzfhqctir
1 5 9 3
1 8 13 15
2 3
bp
1 1 2 15
1 1 2 18
1 2 2 1000000000```

### 输出

```
YES
NO
NO
YES
NO
YES
YES
YES```

# 题解

## 作者：苏联小渣 (赞：8)

我们发现，回文串这个条件是来骗人的，因为如果区间存在长度 $\ge 2$ 的回文串，那一定存在长度为 $2$ 或 $3$ 的最小回文串。

如果长度为 $2$，那就是 $\texttt{aa}$ 的形式；如果长度为 $3$，那就是 $\texttt{aba}$ 的形式。这个东西显然是可以用线段树来合并的。具体而言，我们现在要判断，一个区间是否满足以下条件之一：

- 区间存在两个相邻且相等的字符；

- 区间存在两个相隔一个位置且相等的字符。

我们在合并的时候，只需要知道左区间和右区间分别有没有合法的，以及它们合并起来是否有合法的。考虑两区间合并，我们只需要知道左区间最右和次右、右区间最左和次左的字母就行了。

所以我们需要维护：区间最左和次左、最右和次右的字符，以及区间是否有长度为 $2/3$ 的回文串就行了。

对于区间修改，我们只需要打一个 tag 就行了，同时修改区间最左和次左、最右和次右的字符。时间复杂度 $O(n\log n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
int t, n, m, op, l, r, x, tag[800010];
char s[200010];
struct node{
	int l, r, l2, r2, len, sx, sy;
}d[800010];
node operator + (node x, node y){
	node ret;
	ret.l = x.l, ret.r = y.r, ret.len = x.len + y.len;
	if (x.len == 1) ret.l2 = y.l;
	else ret.l2 = x.l2;
	if (y.len == 1) ret.r2 = x.r;
	else ret.r2 = y.r2;
	ret.sx = (x.sx | y.sx), ret.sy = (x.sy | y.sy);
	if (x.r == y.l) ret.sy = 1;
	if (x.len > 1 && x.r2 == y.l) ret.sx = 1;
	if (y.len > 1 && y.l2 == x.r) ret.sx = 1;
	return ret;
}
void pushdown(int k){
	if (tag[k]){
		tag[lc(k)] = (tag[lc(k)] + tag[k]) % 26, tag[rc(k)] = (tag[rc(k)] + tag[k]) % 26;
		d[lc(k)].l = (d[lc(k)].l + tag[k]) % 26, d[lc(k)].r = (d[lc(k)].r + tag[k]) % 26;
		d[lc(k)].l2 = (d[lc(k)].l2 + tag[k]) % 26, d[lc(k)].r2 = (d[lc(k)].r2 + tag[k]) % 26;
		d[rc(k)].l = (d[rc(k)].l + tag[k]) % 26, d[rc(k)].r = (d[rc(k)].r + tag[k]) % 26;
		d[rc(k)].l2 = (d[rc(k)].l2 + tag[k]) % 26, d[rc(k)].r2 = (d[rc(k)].r2 + tag[k]) % 26;
		tag[k] = 0;
	}
}
void build(int k, int l, int r){
	tag[k] = 0;
	if (l == r){
		d[k] = (node){s[l]-'a', s[l]-'a', 0, 0, 1, 0, 0};
		return ;
	}
	int mid = l + r >> 1;
	build(lc(k), l, mid);
	build(rc(k), mid+1, r);
	d[k] = d[lc(k)] + d[rc(k)];
}
void modify(int k, int l, int r, int x, int y, int val){
	if (x <= l && r <= y){
		tag[k] = (tag[k] + val) % 26;
		d[k].l = (d[k].l + val) % 26, d[k].r = (d[k].r + val) % 26;
		d[k].l2 = (d[k].l2 + val) % 26, d[k].r2 = (d[k].r2 + val) % 26;
		return ;
	}
	int mid = l + r >> 1;
	pushdown(k);
	if (x <= mid) modify(lc(k), l, mid, x, y, val);
	if (y > mid) modify(rc(k), mid+1, r, x, y, val);
	d[k] = d[lc(k)] + d[rc(k)];
}
node query(int k, int l, int r, int x, int y){
	if (x <= l && r <= y) return d[k];
	int mid = l + r >> 1;
	pushdown(k);
	if (y <= mid) return query(lc(k), l, mid, x, y);
	if (x > mid) return query(rc(k), mid+1, r, x, y);
	return query(lc(k), l, mid, x, y) + query(rc(k), mid+1, r, x, y);
}
int main(){
	scanf ("%d", &t);
	while (t --){
		scanf ("%d%d%s", &n, &m, s+1);
		build(1, 1, n);
		for (int i=1; i<=m; i++){
			scanf ("%d%d%d", &op, &l, &r);
			if (op == 1){
				scanf ("%d", &x);
				modify(1, 1, n, l, r, x);
			}
			else{
				node ans = query(1, 1, n, l, r);
				if (ans.sx | ans.sy) puts ("NO");
				else puts ("YES");
			}
		}
	}
	return 0;
}

```

---

## 作者：shinzanmono (赞：4)

首先，我们知道，对于 $l>3$ 的回文串，都可以通过删除两边的字符来变为 $l=2$ 或 $l=3$ 的回文串。

我们对原序列分块。由于给一个整块 $+x$ 这个操作对这个块内是否有回文子串的真假无影响，所以我们可以枚举处理整个块内并记录答案。

修改时，散块暴力重构修改，整块打标记。查询时，散块暴力重构然后枚举查询，整块直接维护块间的交界处即可。

时间复杂度 $O(n\sqrt n)$，可以通过此题。

细节看代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
const int sz=2e5+10;
const int sqsz=510;
int arr[sz],belong[sz],bl[sqsz],br[sqsz],tag[sqsz];
bool allow[sqsz];
void remake(int pid){
    for(int i=bl[pid];i<=br[pid];i++)arr[i]=(arr[i]+tag[pid])%26;
    tag[pid]=0;
}
void build(int pid){
    allow[pid]=true;
    for(int i=bl[pid]+1;i<=br[pid];i++){
        if(arr[i]==arr[i-1])return allow[pid]=false,void();
        if(i!=br[pid]&&arr[i-1]==arr[i+1])return allow[pid]=false,void();
    }
}
void add(int ln,int rn,int val){
    if(belong[ln]==belong[rn]){
        remake(belong[ln]);
        for(int i=ln;i<=rn;i++)arr[i]=(arr[i]+val)%26;
        build(belong[ln]);
        return;
    }
    remake(belong[ln]);
    for(int i=ln;i<=br[belong[ln]];i++)arr[i]=(arr[i]+val)%26;
    build(belong[ln]);
    remake(belong[rn]);
    for(int i=bl[belong[rn]];i<=rn;i++)arr[i]=(arr[i]+val)%26;
    build(belong[rn]);
    for(int i=belong[ln]+1;i<belong[rn];i++)tag[i]=(tag[i]+val)%26;
}
bool query(int ln,int rn){
    if(belong[ln]==belong[rn]){
        remake(belong[ln]);
        for(int i=ln+1;i<=rn;i++){
            if(arr[i]==arr[i-1])return false;
            if(i!=rn&&arr[i-1]==arr[i+1])return false;
        }
        return true;
    }
    remake(belong[ln]);
    for(int i=ln+1;i<=br[belong[ln]];i++){
        if((arr[i]+tag[belong[i]])%26==(arr[i-1]+tag[belong[i-1]])%26)return false;
        if((arr[i-1]+tag[belong[i-1]])%26==(arr[i+1]+tag[belong[i+1]])%26)return false;
    }
    remake(belong[rn]);
    for(int i=bl[belong[rn]];i<=rn;i++){
        if((arr[i]+tag[belong[i]])%26==(arr[i-1]+tag[belong[i-1]])%26)return false;
        if(i!=rn&&(arr[i-1]+tag[belong[i-1]])%26==(arr[i+1]+tag[belong[i+1]])%26)return false;
    }
    for(int i=belong[ln]+1;i<belong[rn];i++){
        if(!allow[i])return false;
        int l=bl[i],r=br[i];
        if((arr[l]+tag[belong[l]])%26==(arr[l-1]+tag[belong[l-1]])%26)return false;
        if((arr[l+1]+tag[belong[l+1]])%26==(arr[l-1]+tag[belong[l-1]])%26)return false;
        if((arr[r-1]+tag[belong[r-1]])%26==(arr[r+1]+tag[belong[r+1]])%26)return false;
    }
    return true;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin>>t;
    while(t--){
        int n,q;
        std::cin>>n>>q;
        for(int i=1;i<=n;i++){
            char ch;
            std::cin>>ch;
            arr[i]=ch-'a';
        }
        int lim=std::sqrt(n),tot=n/lim;
        for(int i=1;i<=tot;i++)
            bl[i]=br[i-1]+1,br[i]=i*lim;
        if(br[tot]!=n)tot++,bl[tot]=br[tot-1]+1,br[tot]=n;
        for(int i=1;i<=tot;i++){
            build(i),tag[i]=0;
            for(int j=bl[i];j<=br[i];j++)belong[j]=i;
        }
        while(q--){
            int op,l,r,x;
            std::cin>>op>>l>>r;
            if(op==1)std::cin>>x,add(l,r,x);
            else{
                if(query(l,r))std::cout<<"YES\n";
                else std::cout<<"NO\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：WaterSun (赞：3)

# 思路

发现如果一个字符串中有长度大于等于 $2$ 回文子串，必定有长度为 $2$ 的回文子串或长度为 $3$ 的回文子串，并且形如：`aa` 和 `aba`。

所以考虑用线段树这两种情况。维护一段区间的最左、次左、最右、次右的元素，同时用两个标记变量 $f_1,f_2$ 分别表示这个区间中是否出现形如 `aa` 和 `aba` 的子串即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int T,n,q;
char s[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l;
        int r;
        int tag;
        int lc[2];
        int rc[2];
        bool f[2];
    }tr[N << 2];

    inline int Add(int a,int b){
        return (a + b) % 26;
    }

    inline node merge(node a,node b){
        node res = {a.l,b.r,0,{a.lc[0],a.lc[1]},{b.rc[0],b.rc[1]},{a.f[0] | b.f[0],a.f[1] | b.f[1]}};
        if (!~res.lc[1]) res.lc[1] = b.lc[0];
        if (!~res.rc[1]) res.rc[1] = a.rc[0];
        if (~a.rc[0] && ~b.lc[0] && a.rc[0] == b.lc[0]) res.f[0] = true;
        if (~a.rc[1] && ~b.lc[0] && a.rc[1] == b.lc[0]) res.f[1] = true;
        if (~a.rc[0] && ~b.lc[1] && a.rc[0] == b.lc[1]) res.f[1] = true;
        return res;
    }

    inline void calc(int u,int k){
        for (re int i = 0;i <= 1;i++){
            if (~tr[u].lc[i]) tr[u].lc[i] = Add(tr[u].lc[i],k);
            if (~tr[u].rc[i]) tr[u].rc[i] = Add(tr[u].rc[i],k);
        }
        tr[u].tag = Add(tr[u].tag,k);
    }

    inline void pushup(int u){
        tr[u] = merge(tr[ls(u)],tr[rs(u)]);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag);
            calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,0,{-1,-1},{-1,-1},{false,false}};
        if (l == r){
            tr[u].lc[0] = tr[u].rc[0] = s[l] - 'a';
            return;
        }
        int mid = l + r >> 1;
        build(ls(u),l,mid);
        build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r){
            calc(u,k);
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }
    
    inline node query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u];
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid) return merge(query(ls(u),l,r),query(rs(u),l,r));
        if (l <= mid) return query(ls(u),l,r);
        if (r > mid) return query(rs(u),l,r);
    }

    #undef ls
    #undef rs
}tree;

inline void solve(){
    n = read();
    q = read();
    scanf("%s",s + 1);
    tree.build(1,1,n);
    while (q--){
        int op;
        op = read();
        if (op == 1){
            int l,r,x;
            l = read();
            r = read();
            x = read();
            tree.modify(1,l,r,x);
        }
        else{
            int l,r;
            l = read();
            r = read();
            auto res = tree.query(1,l,r);
            if (res.f[0] | res.f[1]) puts("NO");
            else puts("YES");
        }
    }
}

int main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

最后：祝 CSP-2023 J2/S2 RP += inf。

---

## 作者：shao0320 (赞：1)

显然对于一个回文串，如果长度是偶数我们只需看最中间两个，若为奇数我们只关心最中心三个即可。

考虑用线段树维护，在父节点合并两个儿子回文串之和的同时，处理跨区间的信息，那么只需记录每个节点左右两端的第一个和第二个数即可。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int t,n,q;
char S[N];
struct Segment_Tree
{
    int v[N*4],l1[N*4],r1[N*4],l2[N*4],r2[N*4],ans[N*4],tag[N*4];
    void pushup(int l,int r,int k)
    {
        int len=r-l+1,mid=(l+r)>>1;
        if(len==1)
        {
            l1[k]=r1[k]=v[k];
            l2[k]=r2[k]=v[k];
            ans[k]=0;
            return;
        }
        if(len==2)
        {
            l1[k]=l1[k<<1];
            l2[k]=l1[k<<1|1];
            r1[k]=l1[k<<1|1];
            r2[k]=l1[k<<1];
            ans[k]=(v[k<<1]==v[k<<1|1]);
            return;
        }
        if(len==3)
        {
            l1[k]=l1[k<<1];
            l2[k]=r1[k<<1];
            r1[k]=l1[k<<1|1];
            r2[k]=r1[k<<1];
            ans[k]=ans[k<<1]+(l2[k]==r1[k])+(l1[k]==r1[k]);
            return;
        }
        l1[k]=l1[k<<1];l2[k]=l2[k<<1];
        r1[k]=r1[k<<1|1];r2[k]=r2[k<<1|1];
        ans[k]=ans[k<<1]+ans[k<<1|1]+(r1[k<<1]==l1[k<<1|1])+(r2[k<<1]==l1[k<<1|1])+(l2[k<<1|1]==r1[k<<1]);
    }
    void build(int l,int r,int k)
    {
        tag[k]=0;
        if(l==r)
        {
            v[k]=S[l]-'a';
            tag[k]=0;
            pushup(l,r,k);
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,k<<1);build(mid+1,r,k<<1|1);
        pushup(l,r,k);
    }
    void pushdown(int l,int r,int k)
    {
        v[k<<1]+=tag[k];v[k<<1]%=26;
        tag[k<<1]+=tag[k];tag[k<<1]%=26;
        v[k<<1|1]+=tag[k];v[k<<1|1]%=26;
        tag[k<<1|1]+=tag[k];tag[k<<1|1]%=26;
        l1[k<<1]+=tag[k];l2[k<<1]+=tag[k];
        r1[k<<1]+=tag[k];r2[k<<1]+=tag[k];
        l1[k<<1]%=26;l2[k<<1]%=26;
        r1[k<<1]%=26;r2[k<<1]%=26;
        l1[k<<1|1]+=tag[k];l2[k<<1|1]+=tag[k];
        r1[k<<1|1]+=tag[k];r2[k<<1|1]+=tag[k];
        l1[k<<1|1]%=26;l2[k<<1|1]%=26;
        r1[k<<1|1]%=26;r2[k<<1|1]%=26;
        tag[k]=0;
    }
    void modify(int l,int r,int k,int x,int y,int val)
    {
        if(l>=x&&r<=y)
        {
            tag[k]+=val;
            tag[k]%=26;
            v[k]+=val;
            v[k]%=26;
            l1[k]+=val;
            l1[k]%=26;
            r1[k]+=val;
            r1[k]%=26;
            l2[k]+=val;
            l2[k]%=26;
            r2[k]+=val;
            r2[k]%=26;
            return;
        }
        int mid=(l+r)>>1;
        pushdown(l,r,k);
        if(x<=mid)modify(l,mid,k<<1,x,y,val);
        if(y>mid)modify(mid+1,r,k<<1|1,x,y,val);
        pushup(l,r,k);
    }
    int calc(int l,int r,int k,int x,int y)
    {
        int mid=(l+r)>>1;
        int Ans=0;
        int L=max(x,l),R=min(r,y);
        Ans+=(r1[k<<1]==l1[k<<1|1]);
        if(L!=mid)Ans+=(r2[k<<1]==l1[k<<1|1]);
        if(R!=mid+1)Ans+=(r1[k<<1]==l2[k<<1|1]);
        return Ans;
    }
    int query(int l,int r,int k,int x,int y)
    {
        if(l>=x&&r<=y)return ans[k];
        int mid=(l+r)>>1;pushdown(l,r,k);
        if(y<=mid)return query(l,mid,k<<1,x,y);
        if(x>mid)return query(mid+1,r,k<<1|1,x,y);
        int Ans=query(l,mid,k<<1,x,y)+query(mid+1,r,k<<1|1,x,y);
        Ans+=calc(l,r,k,x,y);
        return Ans;
    }
}T;
int main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    t=read();
    while(t--)
    {
        n=read();q=read();
        cin>>(S+1);
        T.build(1,n,1);
        while(q--)
        {
            int opt=read();
            if(opt==2)
            {
                int x=read(),y=read();
                puts(T.query(1,n,1,x,y)?"No":"Yes");
            }
            else
            {
                int x=read(),y=read(),val=read()%26;
                T.modify(1,n,1,x,y,val);
            }
        }
    }
}
```

---

## 作者：sunkuangzheng (赞：1)

大水题，不知道为什么赛时 AC 人数远少于 F（

$\textbf{1.1 Solution}$

我们发现任意长度为 $\ge 3$ 的奇数回文串都存在长度为 $3$ 的回文子串，同理任意长度为偶数的回文串也存在长度为 $2$ 的回文子串。那么，我们只需要维护长度为 $2,3$ 的回文串即可。

我们线段树维护区间的最左边的点 $l_1$，次左边的点 $l_2$，最右边的点 $r_1$，次右边的点 $r_2$ 和答案 $ans$。合并两区间时，只需要考虑边界处的贡献。如果左区间的最右端的点的字符等于右区间最左边的字符，则会形成长度为 $2$ 的回文串。同理，通过判断 $l_1,l_2,r_1,r_2$ 可以维护长度为  $3$ 的回文串。

区间加法时，发现区间内没有影响，只有区间边界处有影响。我们打 tag 即可，遇到 tag 就给 $l_1,l_2,r_1,r_2$ 加，然后下传。时间复杂度 $\mathcal O(n \log n)$。

$\textbf{1.2 Code}$

注意不合法区间的判定和长度为 $1$ 的区间，实现时有一些细节。

[code](https://codeforces.com/contest/1881/submission/227909381)。

---

## 作者：__vector__ (赞：1)

将字母看成 $[0,25]$ 的数字。  

每次修改都视为模 $26$ 意义下的区间加法。  

对于询问，注意题目要求没有任何回文子串，这等价于 ${\forall i} \in [1,n], s_i \neq s_{i+1}, s_i \neq s_{i+2}$，对此维护数据结构标记它们的相等关系。  

想一想如何维护区间加法，以及 $s_i$ 是否等于 $s_{i+1}$ 或 $s_{i+2}$。  

一次区间加法操作结束后，被修改区间内部相等关系不会有变化，主要考虑边界变化。设加法操作区间为 $[l,r]$，那么我们需要更新 $l-1,l-2,r,r-1$ 位置的相等关系记录。  

而查询操作，设区间为 $[l,r]$ 则意味着 $l \le {\forall i} \le {r-1}, s_i \neq s_{i+1}, l \le {\forall i} \le {r-2}, s_i \neq s_{i+2}$。  

第一种操作包含区间加法，单点查询（和区间加法共用数据结构，用于修改相等关系），单点修改（相等关系的标记，和区间加法独立）。  

第二种操作包含区间查询（和第一种操作的单点修改共用数据结构，查询相等关系）。  

显然可以树状数组，~~但我赛时脑子抽了，写了 250 整行分块，不过也 50min 写完一发 AC 了，反正是打星就图个愉快~~。  

[提交记录](https://codeforces.com/contest/1881/submission/227875170)

---

## 作者：surroundedcity (赞：0)

我们发现， 判断区间是否存在一个回文串长度 $\ge 2$，这个条件其实可以转换为判断区间是否存在一个长度为 $2$ 或者 $3$ 的回文串。  

直接维护的话不是很方便去维护， 更何况还有区间加操作，我们结合回文串和区间修改就可以很自然地想到差分。

举个例子，`aa` 差分后，就变成判断第二个位置是否为 $0$； `aba` 差分后，就变成了判断两个相邻位置的和在 $\bmod26$ 意义下是否为 $0$。  
接下来的操作就变成了单点修改， 区间查询， 直接套线段树就可以了。
## AC code
```cpp
#include <iostream>
using namespace std;

const int N = 2e5 + 5, inf = 1e9, mod = 26;

int A[N];
struct infor {
	bool e;
	int ld, rd;
	infor() {
		e = false;
		ld = rd = inf;
	}
} tr[N << 2];
infor UP(infor a, infor b) {
	if(a.ld == inf)return b;
	if(b.ld == inf)return a;
	infor c;
	c.e = a.e | b.e | ((a.rd + b.ld) % mod == 0);
	c.ld = a.ld;
	c.rd = b.rd;
	return c;
}
void update(int p) {
	tr[p] = UP(tr[p << 1], tr[p << 1 | 1]);
	return;
}
void build(int p, int l, int r) {
	if(l == r) {
		tr[p].ld = tr[p].rd = A[l];
		tr[p].e = A[l] == 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	update(p);
	return;
}
void chg(int p, int l, int r, int x, int k) {
	if(l == r) {
		tr[p].ld = tr[p].rd = (tr[p].ld + k) % mod;
		tr[p].e = tr[p].ld == 0;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)chg(p << 1, l, mid, x, k);
	else chg(p << 1 | 1, mid + 1, r, x, k);
	update(p);
	return;
}
infor ask(int p, int l, int r, int L, int R) {
	if(l >= L && r <= R)return tr[p];
	int mid = (l + r) >> 1;
	infor ans;
	if(L <= mid)ans = UP(ans, ask(p << 1, l, mid, L, R));
	if(R > mid)ans = UP(ans, ask(p << 1 | 1, mid + 1, r, L, R));
	return ans;
}
void solve() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		A[i] = ch - 'a';
	}
	for(int i = n; i >= 1; i--)A[i] = (A[i] - A[i - 1] + mod) % mod;
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int opt, l, r, x;
		cin >> opt >> l >> r;
		if(opt == 1) {
			cin >> x;
			x %= 26;
			chg(1, 1, n, l, x);
			if(r != n)chg(1, 1, n, r + 1, mod - x);
		} else {
			if(l < r && ask(1, 1, n, l + 1, r).e)cout << "NO\n";
			else cout << "YES\n";
		}
	}
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin >> T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

首先，只需要找到长度为 $2$ 或者 $3$ 的回文就可以了，这个应该很好想，不多说了。

下文中，字符串 $s$ 从 $1$ 开始标号。

为了防止越界，在开始和结尾加入两个不同的字符。

记 $L_i$ 表示 $s_i$ 和 $s_{i-1}$ 是否相同，$R_i$ 表示 $s_i$ 和 $s_{i+1}$ 是否相同，$M_i$ 表示 $s_{i-1}$ 和 $s_{i+1}$ 是否相同。他们代表了长度为 $2\sim 3$ 的回文串的判断。

发现一次更改只会改变 $R_{l-1},M_{l-1},L_{l},M_{l},R_{r},M_{r},M_{r+1},L_{r+1}$，其实就是把 $l-1,l,r,r+1$ 的 $L,M,R$ 三个值重新计算一遍，那么，我们把和这几个值有关的 $s_{l-2},s_{l-1},s_{l},s_{l+1},s_{r-1},s_{r},s_{r+1},s_{r+2}$ 更新到最新值之后进行计算上面的值即可。

看一下查询，对于 $l+1\sim r-1$ 的部分，可以直接查 $L,R,M$ 三个值，如果有一个为 $1$ 就说明可行，接下来查 $R_l$ 和 $L_r$，这两对也是在 $[l,r]$ 这个区间中的。查询的时候注意特判 $l=r$ 的情况。

我们用树状数组维护每个点加了多少，用一个 $gett$ 数组表示第 $i$ 个点已经更改过多少，那么一次改变就是总改变值减去已经改变过的值。

查询部分使用线段树。

相比其他题解，用了两个数据结构，但是感觉更好想。

[code](https://codeforces.com/contest/1881/submission/238908565)

---

