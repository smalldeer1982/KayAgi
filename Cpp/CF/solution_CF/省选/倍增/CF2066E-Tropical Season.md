# Tropical Season

## 题目描述

您有 $n$ 个容量无限的桶。第 $i$ 个桶初始装有 $a_i$ 千克水。在此问题中，我们假设所有桶自身重量相同。

已知恰好有一个桶的表面含有少量热带毒药，总重量为 $0.179$ 千克。但您不知道具体是哪个桶含有毒药。您的任务是确定这个有毒的桶。

所有桶都放置在秤上。然而秤不会显示每个桶的确切重量，而是为每对桶显示它们的重量比较结果。因此，对于任意两个桶，您可以判断它们的重量是否相等，若不相等则可知哪个桶更重。毒药和水的重量均计入桶的总重量。

秤始终处于开启状态，其信息可无限次使用。

您还可以进行倒水操作：可以将任意数量的水从任意一个桶倒入另一个桶（两者可为不同桶）。

但倒水时，您必须物理接触被倒出的桶。如果该桶恰好是含毒桶，您将死亡。必须避免这种情况发生。

但您可以将水倒入含毒桶而无需触碰它。

换言之，您可以选择参数 $i, j, x$（$i \neq j$，$1 \leq i, j \leq n$，$0 < x \leq a_i$，且编号 $i$ 的桶不含毒）并执行操作 $a_i := a_i - x$，$a_j := a_j + x$。其中 $x$ 不必是整数。

在利用倒水操作和秤的信息时，能否保证确定含毒桶的同时存活？已知毒药必定存在于恰好一个桶中。

此外，您需要处理 $q$ 次查询。每次查询将移除一个现有桶，或添加一个装有指定水量新桶。每次查询后，您需要回答在恰好存在一个含毒桶的条件下，能否保证确定该桶。

## 说明/提示

第一个测试案例中，初始桶的水量为 $[2, 2, 4, 11]$。可先比较第一和第二个桶的重量：若不等则可断定较重桶含毒；若相等则二者均不含毒。接着可将第一桶所有水倒入第二桶，此时第二和第三桶均有 $4$ 千克水。再次比较二者重量：若不等则较重桶含毒；否则二者均不含毒。唯一可能含毒的桶变为第四个。通过此策略可安全确定含毒桶。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 7
2 2 4 11
- 2
+ 4
+ 30
+ 40
- 4
+ 2
+ 2```

### 输出

```
Yes
No
Yes
No
Yes
No
No
Yes```

## 样例 #2

### 输入

```
6 7
5000 1000 400 400 100 99
+ 1
- 5000
- 1
- 400
- 400
- 100
- 99```

### 输出

```
No
Yes
Yes
Yes
No
No
No
Yes```

# 题解

## 作者：immix (赞：7)

[更好的体验](https://linlexiao.com/posts/d9bd22dab93b/)

提供一个比较好写的 1 log 做法。

## 题意

有 $n$ 个桶，容积无限大，知道每个桶初始有 $a_i$ 千克的水。现在有一个桶恰额外含有 $0.179$ 千克的毒药，进行任意次如下两种操作：
1. 选择两个桶 $A$，桶 $B$，比较重量，知道哪边重或一样重；
2. 选择桶 $A$，桶 $B$，从 $A$ 桶中倒 $x$ 千克水（$x$ 不一定是整数）进入 $B$ 桶，要求：
    - $A$ 桶必须不含毒药；
    - $A$ 桶至少要含有 $x$ 千克的水。

判断是否能唯一确定哪个桶装着毒药，输出 `Yes`/`No`。

现在会进行 $q$ 次修改，每次的修改为增加一个初始水量为 $b$ 的桶，或删去一个初始水量为 $b$ 的桶（保证存在），修改持续。
每次修改后，输出 `Yes`/`No`，代表当前情况是否能判断哪个桶装着毒药。

$n,q\le 2\times 10^5, a_i,b\le10^6$。

## 解法

注意到操作 1 只有两个桶装的水是同样重的才有用（要不然有没有毒药不会影响结果），而且操作 2 选择的桶 $A$ 一定确定没有毒药。


则初始一定是选择两个装的水都是 $k$ 千克的桶，然后比较，如果有毒药就结束了，我们考虑它们重量一样，也就是没有毒药的情况。

这时候我们可以自由支配的水量是 $2k$，记作 $L$。
我们发现所有的操作都可以归为两种：
1. 选择 $a_i\le L$，让 $L\leftarrow L+a_i$。（也就是用 $L$ 获得一个装了 $a_i$ 水的桶去比）
2. 选择 $a_i+L\ge a_j$（$i$ 和 $j$ 都未确定），让 $L\leftarrow L+a_i+a_j$。（也就是把 $a_j-a_i$ 的水倒进桶 $i$ 里面，然后 $i$ 和 $j$ 再去比较）

初始令 $L=0$，一开始找到两个装的水都是 $k$ 千克的桶的过程可以用操作 2 来描述，所以我们抛弃第一步，直接从 $L=0$，未确认任何桶开始的初始条件来解决这个问题，不断进行操作，如果最后能确定大于等于 $n-1$ 个桶没有毒药，那么就应该输出 `Yes`（因为最后一个桶可以排除法确定）。

用值域倍增分块加速这个过程。

把值域按照 $[2^k,2^{k+1})$ 分成 $O(\log a_i)$ 块。
我们可以发现一个性质，如果我们确定了某一块内任意一个桶没有毒药，那么就可以确定一整块所有的桶是否有毒药。

我们证明这个结论：
假设当前这个数是 $a_i$，在块 $[2^k,2^{k+1})$ 中：
1. 如果这一个桶是由操作 1 确定的，那么此时 $L' = L + a_i \ge 2a_i \ge 2^{k+1}$，所以 $L'$ 比这一个块内所有数都大，自然可以用操作 1 确定这一块里面每个桶。
2. 如果这一个桶是由操作 2 确定的，$L' = L + a_i + a_j \ge 2a_i \ge 2^{k+1}$，同理得证。

对于每个块 $[2^k,2^{k+1})$，用 `multiset` 可以在 $O(\log a_i)$ 时间复杂度内轻易维护每块内的数，和每块两两之间的差。

我们从小到大遍历每一块，如果这一块存在一个能被确定，就把之前所有没确定的都确定，总和加入 $L$ 中。

存在一个在 $S$ 内能被确定的等价条件是：$L\ge \displaystyle\min_{i\in S}(a_i)$ 或 $L\ge \displaystyle\min_{i\in S, j\text{ 未被确定}}(|a_i-a_j|)$。

第一个就是当前块内的最小值，已经用 `multiset` 维护了。

第二个条件只需要维护相邻块最大值和最小值之间的差和块内的差取最小值即可，尽管下一块可能是一个空块，也就是相邻的下一个数在下下块，但无需考虑这个的差，因为这个的差一定比 $2^{k+1}$ 大，一定不优，只需要上一块和下一块的差就行了。值得注意的是，如果上一块已经被确定了，那么不应考虑上一块的贡献。

这样遍历一遍，维护当前确定到了第几块，每次成功确定了这一块就把前面的都加入贡献，维护我们确定了多少个数就能解决本题。

代码很好写，也比较短：
```cpp
#include<bits/stdc++.h>
using namespace std;

using ll=long long;

struct Bucket{
    multiset<int> diff;
    multiset<int> st;
    ll sum;
    void insert(int x){
        sum += x;
        auto it = st.insert(x);
        if(it != st.begin())diff.insert(*it - *prev(it));
        if(next(it) != st.end())diff.insert(*next(it) - *it);
        if(it != st.begin() && next(it) != st.end())
            diff.erase(diff.find(*next(it) - *prev(it)));
    }
    void erase(int x){
        auto it = st.find(x);
        if(it != st.begin())diff.erase(diff.find(*it - *prev(it)));
        if(next(it) != st.end())diff.erase(diff.find(*next(it) - *it));
        if(it != st.begin() && next(it) != st.end())
            diff.insert(*next(it) - *prev(it));
        st.erase(it);
        sum -= x;
    }
    bool empty(){return st.empty();}
}b[21];

void insert(int x){b[__lg(x)].insert(x);}
void erase(int x){b[__lg(x)].erase(x);}

int n,q;
void solve(){
    ll sum = 0;
    int nowb = 0,cnt = 0;

    for(int i=0;i<=19;i++){
        if(b[i].empty())continue;
        int mindiff = b[i].diff.size() ? *b[i].diff.begin() : 1e9; 
        mindiff = min(mindiff, *b[i].st.begin());
        
        if(i && b[i-1].st.size() && nowb<=i-1)mindiff = min(mindiff, *b[i].st.begin());
        if(i!=19 && b[i+1].st.size())mindiff = min(mindiff, *b[i+1].st.begin() - *b[i].st.rbegin());
        if(mindiff <= sum){ 
            for(;nowb<=i;++nowb){
                sum+=b[nowb].sum,cnt+=b[nowb].st.size();
            }
        }
    }
    
    if(cnt >= n-1)cout<<"Yes\n";
    else cout<<"No\n";
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        insert(x);
    }

    solve();
    while(q--){
        string op; int x;
        cin>>op>>x;
        if(op[0]=='-')erase(x),--n;
        else          insert(x),++n;
        solve();
    }
    return 0;
}
```

---

## 作者：xieziheng (赞：3)

你说的对，这题或许是好题，但是给我写吐了。

一个简单的观察是，如果有相同的元素，互相查一下就可以知道有没有毒，如果有毒直接做完了，所以我们可以直接当成他们都没毒。这样就剩下一堆互不相同的元素。

因此我们可以用存在相同的那些元素随便倒，等价于我们有自由的 $s$ 千克，因此任意 $\leq s$ 的都可以被我们判断是否有毒，同理，任意差 $\leq s$ 的也可以被我们判断是否有毒。 

所以直接每次吃掉 $\leq s$ 的部分并给 $s$ 加上对应大小，如果剩下全大于 $s$ 那么算一下相邻差值的最小值和 $s$ 比较即可，由于每次这种情况后 $s$ 大小至少翻倍，所以至多进行 $\mathcal{O}(\log V)$ 轮，$V$ 为 $a_i$ 值域。

互不相同的那一堆元素可以 ```set``` 维护，相邻差值开个线段树维护就行。复杂度 $\mathcal{O}(n\log^2 V)$

实现有巨大多细节，而且还卡常。

```cpp
#include <bits/stdc++.h>
#define il inline
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned int uint;
mt19937 rnd(time(0));
il char readc(){
    char c=getchar();
    while(c!='+' && c!='-') c=getchar();
    return c;
}
il int read(){
    int x=0,c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=x*10+c-48,c=getchar();
    return x;
}
const int N=2e5+5,M=1e6,inf=1e9;
int n,m,a[N],in[M+5];ll sum;
set<int> s;
struct node{
    ll s;int l,r,mi,u,v;
    il node(){s=0,l=r=mi=u=v=0;}
}t[(M<<2)+5],tt[(M<<2)+5];
il node merge(node x,node y){
    node z;z.s=x.s+y.s,z.l=(x.l?x.l:y.l),z.r=(y.r?y.r:x.r),z.mi=inf,z.u=z.v=0;
    if(x.mi<z.mi) z.mi=x.mi,z.u=x.u,z.v=x.v;
    if(y.mi<z.mi) z.mi=y.mi,z.u=y.u,z.v=y.v;
    if(x.r && y.l && y.l-x.r<z.mi) z.mi=y.l-x.r,z.u=x.r,z.v=y.l;
    return z;
}
il void pushup(int x){
    t[x]=merge(t[x<<1],t[x<<1|1]);
}
void build(int x,int l,int r){
    if(l==r){if(in[l]==1) t[x].s=l,t[x].l=t[x].r=l;else t[x].s=0,t[x].l=t[x].r=0;t[x].mi=inf,t[x].u=t[x].v=0;return ;}
    int mid=(l+r)>>1;build(x<<1,l,mid),build(x<<1|1,mid+1,r),pushup(x);
}
void update(int x,int l,int r,int p,int w){
    if(l==r){
        if(w) t[x].s=1ll*l,t[x].l=t[x].r=l;else t[x].s=0,t[x].l=t[x].r=0;
        t[x].mi=inf,t[x].u=t[x].v=0;return ;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(x<<1,l,mid,p,w);
    else update(x<<1|1,mid+1,r,p,w);
    pushup(x);
}
node query(int x,int l,int r,int L,int R){
    if(l>=L && r<=R) return t[x];
    int mid=(l+r)>>1;
    if(L>mid) return query(x<<1|1,mid+1,r,L,R);
    else if(R<=mid) return query(x<<1,l,mid,L,R);
    else return merge(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
}
ll qsum(int x,int l,int r,int L,int R){
    if(l>=L && r<=R) return t[x].s;
    int mid=(l+r)>>1;
    if(L>mid) return qsum(x<<1|1,mid+1,r,L,R);
    else if(R<=mid) return qsum(x<<1,l,mid,L,R);
    else return qsum(x<<1,l,mid,L,R)+qsum(x<<1|1,mid+1,r,L,R);
}
il void add(int x){
    if(!in[x]) s.insert(x),++in[x],update(1,1,M,x,1);
    else if(in[x]==1) s.erase(x),++in[x],sum+=2ll*x,update(1,1,M,x,0);
    else ++in[x],sum+=1ll*x;
}
il void del(int x){
    if(in[x]==1) s.erase(x),--in[x],update(1,1,M,x,0);
    else if(in[x]==2) s.insert(x),--in[x],sum-=2ll*x,update(1,1,M,x,1);
    else --in[x],sum-=1ll*x;
}
vector<int> f;
il int calc(){
    if(sum>=M) return 1;
    f.clear();
    ll cur=sum;int x,y,z;ll u,v,w;
    if(s.size()<=1) return 1;
    int pre=1;
    while(1){
        if(sum>=M) return 1;
        auto it=s.upper_bound(cur);if(it==s.end()) return 1;
        x=(*it),++it;if(it==s.end()) return 1;--it;
        y=max(*s.begin(),pre),pre=max(pre,y);if(y<=x-1) cur+=qsum(1,1,M,y,x-1),pre=max(pre,x);
        if(cur>=x){cur+=x,pre=x+1;continue;}
        node c=query(1,1,M,x,M);if(c.mi>cur) return 0;
        cur+=c.u+c.v,s.erase(c.u),s.erase(c.v),update(1,1,M,c.u,0),update(1,1,M,c.v,0);
        f.push_back(c.u),f.push_back(c.v);
        if(s.size()) pre=max(pre,*s.begin());else pre=M+1;
    }
    return 0;
}
il void init(){
    for(int x:f) s.insert(x),update(1,1,M,x,1);
    f.clear();
}
il void print(){
    for(int x:s) printf("%d ",x);printf(" : %lld\n",sum);
}
int x,y,z,u,v,w;char opt;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) a[i]=read(),++in[a[i]];
    for(int i=1;i<=M;++i) if(in[i]>1) sum+=1ll*i*in[i];else if(in[i]==1) s.insert(i);
    build(1,1,M);
    puts(calc()?"Yes":"No");init();int tt=1;
    while(m--){
        opt=readc(),x=read();++tt;
        if(opt=='+') add(x);
        else del(x);
        puts(calc()?"Yes":"No"),init();
    }
    return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

*##))? *@#))!

vp 赛后 1min 补题，原因是我线段树没判空区间死循环了，红温了，感觉又不会写代码了。

首先发现初始只能搞两个相同的桶，然后这俩桶要么就确定了毒药，要么就都确定不是毒药。都不是的话可以拿个桶装起来备用（怎么写着写着突然冒出种美食节目的风味）。

假设两个相同的桶为 $x$，那么现在我们有 $2x$ 的自由水量，也就可以造出任何一个 $\le 2x$ 的水桶，用来吞并一个更小的水桶。因此我们可以一路把所有 $\le 2x$ 的吃了，得到一个新的总量，再一路吃下去。

但是有可能吃到某一步吃不动了，这时候不一定意味着无解。设目前总量为 $S$，考虑一组 $x,y>S$，如果 $|x-y|\le S$，那么我们可以倒一部分给小的那个，然后就能把 $x,y$ 都吃下来了。所以我们还需要找差最小的 pair。

整理一下我们的过程：

- 初始总量 $S=0$。

- 优先吞并所有 $\le S$ 的水桶，直到无法吞并；

- 若存在 $x,y>S$ 使得 $|x-y|\le S$，吞并 $x,y$ 并回到上一步。

两个部分都可以用线段树维护。

接下来证明直接暴力这么跳复杂度是对的。

考虑吞并比自己小的水桶的过程，比如目前是 $S$，我们吃下了所有 $\le S$ 的水桶，如果下一次还能吃，设吃了一个 $x$，那么 $x>S$，因此两次操作内 $S$ 至少翻了个倍，因此这样的操作至多发生 $2\log V$ 次。

而找相差最小的水桶对，吃下来之后至少变成原来的三倍，因此只会发生 $\log_3 V$ 次。

总复杂度 $\mathcal O(q\log ^2 V)$。[submission](https://codeforces.com/contest/2066/submission/315302661)

---

## 作者：ljw0102 (赞：1)

## 题目大意

有 $n$ 个桶，每个桶中有 $a_i$ 千克水，其中恰有一个桶装有 $0.179$ 千克毒药。你可以进行以下两种操作任意次：

1. 选择两个桶比较，返回哪个更重或一样重；

2. 从桶 $A$ 向桶 $B$ 中倒任意多的水，要求 $A$ 确定不含毒药。

$q$ 次修改，加入或删除一个重量为 $x$ 的桶，每次修改后求能否唯一确定含有毒药的桶。

$n,q\le 2\times 10^5,a_i,x\le 10^6$

## 题解

若所有 $a_i$ 均不同，我们是无从下手的。只能找两个 $a_i$ 相同的桶进行比较，若重量不同则能确定哪个含有毒药，否则这两个桶均不含有毒药。以下只假设最坏情况，即若两个桶重量相同则都视为没有毒药。

当我们确定了一个桶中没有毒药，其中的水可以随意支配。于是想到维护可支配的水的重量  $k$，有以下两种操作：

1. 对任意 $a_i\le k$ 的桶，可以从 $k$ 中拿出 $a_i$ 与其进行比较，然后令 $k:=k+a_i$；

2.  对两个桶 $a_i,a_j(a_i\le a_j)$，若 $a_j-a_i\le k$，可以将 $a_i$ 补成 $a_j$ 并比较，然后令 $k:=k+a_i+a_j$。

可以得到一个算法流程：每次不断加入所有 $\le k$ 的数，然后找 $>k$ 的数中差值最小的两个数加入，如此往复。剩下至多一个桶或 $k\ge 10^6$ 则获胜，无法更新 $k$ 则失败。

每次 $k$ 至少加倍，至多进行 $O(\log V)$ 次。

让人联想到 [神秘数](https://www.luogu.com.cn/problem/P4587) 这道题，可以开一个值域线段树维护。要维护的信息有：值域区间中数字个数，数值之和，最小值，最大值，差值最小的两个数。写一个 node 封装起来可以大大简化细节。复杂度 $O(n\log^2 V)$。

## 代码


```cpp
#include<bits/stdc++.h>
#define N 400005
using namespace std;
int n,q,M=1000000;
struct node{
	int cnt,mn,mx,v1,v2;
	long long sum;
};
struct SegmentTree{
	int l,r;
	node v;
}t[N*10];
node merge(node a,node b){
	if(!a.mn) return b;
	if(!b.mn) return a;
	node c;
	c.cnt=a.cnt+b.cnt;
	c.sum=a.sum+b.sum;
	c.mn=a.mn,c.mx=b.mx;
	c.v1=a.mx,c.v2=b.mn;
	if(a.v2-a.v1<c.v2-c.v1) c.v1=a.v1,c.v2=a.v2;
	if(b.v2-b.v1<c.v2-c.v1) c.v1=b.v1,c.v2=b.v2;
	return c;
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r) return;
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
void change(int p,int x,int k){
	if(t[p].l==t[p].r){
		t[p].v.cnt+=k;
		t[p].v.sum+=t[p].l*k;
		if(t[p].v.cnt==0)
			t[p].v.mn=t[p].v.mx=t[p].v.v1=t[p].v.v2=0;
		else if(t[p].v.cnt==1)
			t[p].v.mn=t[p].v.mx=t[p].l,t[p].v.v2=0x3f3f3f3f,t[p].v.v1=0;
		else t[p].v.mn=t[p].v.mx=t[p].v.v1=t[p].v.v2=t[p].l;
		return;
	}
	int mid=(t[p].l+t[p].r)/2;
	if(x<=mid) change(p*2,x,k);
	else change(p*2+1,x,k);
	t[p].v=merge(t[p*2].v,t[p*2+1].v);
}
node ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r) return t[p].v;
	int mid=(t[p].l+t[p].r)/2;
	if(r<=mid) return ask(p*2,l,r);
	if(l>mid) return ask(p*2+1,l,r);
	return merge(ask(p*2,l,r),ask(p*2+1,l,r));
}
bool check(){
	long long k=0;
	while(1){
		while(k){
			node val=ask(1,1,k);
			if(k>=val.sum) break;
			k=val.sum;
			if(k>=M) return 1;
		}
		node val=ask(1,k+1,M);
		if(val.cnt<=1) return 1;
		if(val.v2-val.v1<=k) k+=val.v2+val.v1;
		else return 0;
		if(k>=M) return 1;
	}
}
int main(){
	scanf("%d%d",&n,&q);
	build(1,1,M);
	for(int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		change(1,x,1);
	}
	if(check()) puts("YES");
	else puts("NO");
	while(q--){
		char op=getchar();
		while(op!='+'&&op!='-') op=getchar();
		int x;
		scanf("%d",&x);
		if(op=='+') change(1,x,1);
		else change(1,x,-1);
		if(check()) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：AmaoFox (赞：1)

~~O(3) 优化太恐怖了！给我从 TLE on 78 优化到只有不到 1000 毫秒了！~~

~~氦气的通常密度刚好一方就有这么重，怎么回事呢。~~

假设当前有一些桶我们确定没有毒，则里面的所有的水我们就可以来回倒腾而不需要担心了。

如果我们知道两桶水体积一致，那么可以对它们进行称量：如果不一样重则重的那边肯定有毒了。不过如果体积不一致，肯定是体积大的那一边重。（我们不考虑倒出 $0.1$ 升之类的情况，没必要。）

所以我们只考虑每一次称量都刚好一样重的情况。假设我们现在已经确定了其中若干桶一共 $V$ 升的水是无毒的，则：

- 有第 $i$ 桶水还不确定，而他的 $a_i\le V$。则我们可以把这 $V$ 升水凑到一起，分一些给到第 $i$ 桶水，然后就有两桶各 $(\dfrac{V+a_i}2)$ 升水了。~~很好笑的是我一开始不知道能倒小数升，害得我在这里卡了半天。~~
- 有第 $i$ 和 $j$ 桶水还不确定，而 $\operatorname{abs}(a_i-a_j)\le V$。那么我们可以把 $V$ 分一部分出去，使得小的那一桶水和大的一样。这样，两桶就同时有 $\max(a_i, a_j)$ 升水了。

所以现在关键就在于如何构造出如上的方式。

我们对所有的数进行值域分块。具体地说，我们进行对数分块：对于自然数 $i$，把 $[2^i,2^{i+1})$ 的桶放在一个块里面。  
这是因为：如果该块中有一个，比方说第 $i$ 桶确定无毒，则一定是因为有另一个至少有相同重量的桶也确定无毒，然后对它们进行了称量。故现在确定无毒的水 $V\ge2a_i$，也就是说该块中所有的水都确定无毒了。

所以，我们接下来需要维护：每个块的最小和最大值、块内的最小差、整块的和。这些用 `multiset` 很好维护。

每一次从头到尾扫过每一个块，如果发现块内最小差 $\le V$，或者块内最小值和最后一个未确定的最大值的差 $\le V$，那么就把到目前为止的和全都加到 $V$ 上。

最后记录一下未确定无毒的桶数：如果不超过一桶不能确定即可，因为最后可以用排除法。

于是时间复杂度是 $O((n+q)\log V)$ 了。

代码：
``` cpp
#include <bits/stdc++.h>
#pragma GCC optimize (3)

using namespace std;

const int V = 1000005, lgV = 22;

multiset<int> buck[lgV], dif[lgV];
long long sum[lgV];
int lg2[V];

void add(int x) {
  int p = lg2[x];
  if (buck[p].count(x)) {
    dif[p].insert(0);
  } else if(buck[p].size()) {
    auto it = buck[p].lower_bound(x);
    if (it == buck[p].end()) {
      dif[p].insert(x - *prev(it));
    } else if (it != buck[p].begin()) {
      dif[p].erase(dif[p].find(*it - *prev(it)));
      dif[p].insert(*it - x);
      dif[p].insert(x - *prev(it));
    } else {
      dif[p].insert(*it - x);
    }
  }
  sum[lg2[x]] += x;
  buck[lg2[x]].insert(x);
}

void remove(int x) {
  int p = lg2[x];
  buck[p].erase(buck[p].find(x));
  sum[p] -= x;
  if(buck[p].count(x)) {
    dif[p].erase(dif[p].find(0));
  } else if(buck[p].size()) {
    auto it = buck[p].lower_bound(x);
    if (it == buck[p].end()) {
      dif[p].erase(dif[p].find(x - *prev(it)));
    } else if (it != buck[p].begin()) {
      dif[p].insert(*it - *prev(it));
      dif[p].erase(dif[p].find(*it - x));
      dif[p].erase(dif[p].find(x - *prev(it)));
    } else {
      dif[p].erase(dif[p].find(*it - x));
    }
  }
}

bool solve() {
  long long rsum = 0, dsum = 0; // rsum = 确定无毒, dsum = 目前不确定
  int dis = 0, maxv = 0; // dis = 未确定的桶数, maxv = 最后没确定的最大值
  for (int i = 0; i < lgV; i++) {
    dsum += sum[i];
    if (dif[i].size() && *dif[i].begin() <= rsum) {
      rsum += dsum;
      dis = dsum = maxv = 0;
    } else if (buck[i].size() && *buck[i].begin() - maxv <= rsum) {
      rsum += dsum;
      dis = dsum = maxv = 0;
    } else if (buck[i].size()) {
      dis += buck[i].size();
      maxv = *(buck[i].rbegin());
    }
  }
  return dis <= 1;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  lg2[0] = -1;
  for (int i = 1; i < V; i++) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    add(x);
  }
  cout << (solve() ? "Yes\n" : "No\n");
  while (q--) {
    char c;
    int x;
    cin >> c >> x;
    if (c == '+') {
      add(x);
    } else {
      remove(x);
    }
    cout << (solve() ? "Yes\n" : "No\n");
  }
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题意

有 $n$ 个数 $a_i$，有一个 $i$ 被标记成了 $f_i=1$。被标记了 $f_i=1$ 的真实值是 $a_i+0.179$。每次可以取出 $i,j$ 得到 $a_i$ 和 $a_j$ 的真实值的大小关系。

你可以进行若干次操作，每次选择整数对 $(i,j,x)$ 前提是 $f_i\neq 1$ 且 $0\lt x\leq a_i$，操作 $a_i\gets a_i-x$ 和 $a_j\gets a_j+x$。

你并不知道哪个数被标记了。问能不能知道被标记的数是哪一个。

有 $q$ 次修改。每次给出 `+ x` 或 `- x`。表示添加一个 $a_i=x$ 或删除一个 $a_i=x$。每次操作都是一个全新的局面，即你仍然不会知道什么数被标记了，信息无关。

对于初始局面和之后的 $q$ 个局面给出 $q+1$ 个答案表示这个局面是否能得到被标记的数。

$1\leq n,q\leq 2\times 10^5$，$1\leq a_i,x\leq 10^6$。

# 做法

考虑 $q=0$ 怎么做。

做一下样例，发现我们每一步有两种做法：

1. 选择两个相等的数 $a_i,a_j$ 比较大小。如果比出来就结束了，否则你将获得 $a_i+a_j$ 的『可支配空间』。
1. 选择两个数 $a_i\lt a_j$，匀一部分『可支配空间』给 $a_i$ 使得 $a_i=a_j$。然后做 1 操作。

也就是说，$q=0$ 的时候我们维护目前的『可支配空间』$s$，然后每次尝试吞并一些 $a_i\leq s$ 的 $a_i$，即 $s\gets s+a_i$。或者选一对 $a_i\leq a_j$ 满足 $a_j-a_i\leq s$，然后 $s\gets s+a_i+a_j$。

$q=0$ 直接用一个堆维护这个操作。

考虑有修改删除。我们发现在 $q=0$ 的时候，两次操作交替次数很少。因为你每次如果到了 $s\lt \min\{a\}$，用 2 操作之后可以继续 1 操作，那么 $s$ 至少变为了 $2s$。所以 1 操作 2 操作只会交替 $\mathcal O(\log V)$ 次。

那么我们就需要一个数据结构维护一个连续段的贡献，然后每次跳一部分连续段。

值域很小，可以考虑线段树。

具体的，我们维护大小为 $\mathcal O(V)$ 的线段树。每个节点维护『最小差分』、『最小最大值』、『数值之和』、『有多少个实际有效的数』。

『最小最大值』是用来更新『最小差分』的。因为 pushup 合并信息可能会最小差分是右儿子的 $\max$ 减去左儿子的 $\min$。

『有多少个实际有效的数』是用来判断我们是否操作到了只剩一个或者零个数，即是否能推出答案。

每次操作尝试找到最后一个差分 $\leq s$ 的位置。这里可以用线段树二分实现，线段树二分注意一下『最小差分』可能是在左右儿子之间形成的，需要加个特判。那么这个差分之前的都可以成为『可支配空间』。如果找不到这样的差分，那么 $\leq s$ 的值都可以成为『可支配空间』。模拟这个过程，至多交替 $\mathcal O(\log V)$ 次。每次线段树复杂度 $\mathcal O(\log V)$。总复杂度 $\mathcal O(q\log^2 V)$。

# 代码

<https://codeforces.com/contest/2066/submission/311385798>

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
typedef long long ll;
const ll inf = 1e18;
int n, q;
const int N = 1e6;
int tot;
struct SegTree
{
    struct node
    {
        ll mnd;
        ll L, R;
        ll sum;
        int c;
    } t[1000020 << 2];
#define ls id << 1
#define rs id << 1 | 1
#define Llen (mid - l + 1)
#define Rlen (r - mid)
    void push_up(int id)
    {
        t[id].mnd = min({t[ls].mnd, t[rs].mnd, t[rs].L - t[ls].R});
        t[id].L = t[ls].L == inf ? t[rs].L : t[ls].L;
        t[id].R = t[rs].R == -inf ? t[ls].R : t[rs].R;
        t[id].sum = t[ls].sum + t[rs].sum;
        t[id].c = t[ls].c + t[rs].c;
    }
    void build(int id = 1, int l = 1, int r = N)
    {
        if (l == r)
            return t[id].mnd = inf, t[id].L = inf, t[id].R = -inf, t[id].sum = 0, void();
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        push_up(id);
    }
    void add(int pos, int id = 1, int l = 1, int r = N)
    {
        if (r < pos || l > pos)
            return;
        if (pos <= l && r <= pos)
        {
            t[id].c++;
            if (t[id].c > 1)
                t[id].mnd = 0;
            t[id].L = t[id].R = pos;
            t[id].sum += pos;
            return;
        }
        int mid = l + r >> 1;
        add(pos, ls, l, mid);
        add(pos, rs, mid + 1, r);
        push_up(id);
    }
    void del(int pos, int id = 1, int l = 1, int r = N)
    {
        if (r < pos || l > pos)
            return;
        if (pos <= l && r <= pos)
        {
            t[id].c--;
            if (t[id].c <= 1)
                t[id].mnd = inf;
            if (!t[id].c)
            {
                t[id].L = inf;
                t[id].R = -inf;
            }
            t[id].sum -= pos;
            return;
        }
        int mid = l + r >> 1;
        del(pos, ls, l, mid);
        del(pos, rs, mid + 1, r);
        push_up(id);
    }
    int query(ll d, int pos, int id = 1, int l = 1, int r = N)
    {
        if (r <= pos)
            return 0;
        if (t[id].mnd > d)
            return 0;
        if (l == r)
            return l;
        int mid = l + r >> 1;
        return t[rs].mnd <= d ? query(d, pos, rs, mid + 1, r) : t[rs].L - t[ls].R <= d && pos < t[ls].R ? t[rs].L
                                                                                                        : query(d, pos, ls, l, mid);
    }
    ll getsum(int ql, int qr, int id = 1, int l = 1, int r = N)
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return t[id].sum;
        int mid = l + r >> 1;
        return getsum(ql, qr, ls, l, mid) + getsum(ql, qr, rs, mid + 1, r);
    }
    ll getc(int ql, int qr, int id = 1, int l = 1, int r = N)
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
            return t[id].c;
        int mid = l + r >> 1;
        return getc(ql, qr, ls, l, mid) + getc(ql, qr, rs, mid + 1, r);
    }
} T;
bool calc()
{
    ll s = 0;
    int cnt = 0;
    int pos = 0;
    bool ok = 1;
    while (cnt < tot - 1 && ok)
    {
        int lst = T.query(s, pos);
        ok = 0;
        if (cnt < lst)
        {
            pos = lst;
            s = T.getsum(1, pos);
            cnt = T.getc(1, pos);
            ok = 1;
        }
        if (pos < s)
        {
            pos = min(s, 1LL * N);
            s = T.getsum(1, pos);
            cnt = T.getc(1, pos);
            ok = 1;
        }
    }
    return ok;
}
int main()
{
    T.build();
    read(n, q);
    for (int i = 1; i <= n; i++)
    {
        int x;
        read(x);
        T.add(x);
        tot++;
    }
    puts(calc() ? "Yes" : "No");
    while (q--)
    {
        char op = getchar();
        while (op != '+' && op != '-')
            op = getchar();
        int x;
        read(x);
        if (op == '+')
            tot++, T.add(x);
        else
            tot--, T.del(x);
        puts(calc() ? "Yes" : "No");
    }
    return 0;
}
```

---

## 作者：ForgotMe (赞：0)

蚌埠住了，C 题做了 1h，D2 不会做，这题 30min 就会了，E << C,D2 /fn/fn。不管怎么说，这题确实算是非常套路的题了。

首先可以发现如果一个桶中的水可以用，当且仅当存在另外一个桶重量与其相同，因为可以通过比较知道两者中有无毒药。
设当前所有能用的水重量之和为 $L$，设当前还不能用的桶中水的重量形成的集合（显然是不重的）为 $S$，然后可以做以下操作

- $x\in S$，$x\le L$，那么这个桶中的水就可以用，因为可以把当前能用的所有水拿出 $x$ 放在一个桶里面，与这个还不能用的桶比较。即 $L\leftarrow L+x$，将 $x$ 从 $S$ 中删去。

- $x,y\in S(x\ne y)$，$|x-y|\le L$，将 $|x-y|$ 的水放进水少的那个桶，然后进行比较。即 $L \leftarrow L+x+y$，将 $x,y$ 从 $S$ 中删去。

最后如果能操作到使得 $|S|\le 1$，那么就有解。

于是现在就会暴力做法了，显然能删就删。注意到一个很显然的性质是，如果 $x$ 可以从 $S$ 中删取，那么 $S$ 中小于等于 $x$ 的数一定也能被删去。

对于这种某个变量（$L$）在不断变大使得更多数能够操作的题目，容易想到使用值域倍增分块来加速该过程，一个非常经典的题目就是 IOI 的地牢游戏。

考虑将 $S$ 中处在 $(2^k,2^{k+1}]$ 的数分成一块，一个关键性质是，对于一个块，如果能将该块中的**任意一个数**删去，那么整块中的数都能删去！因为当块中存在超过 $1$ 个数时，任意两个数的差值都小于等于该块中的所有数。其实看出来这个本题基本上就做完了，挨着看每块其中是否存在一个数可以删掉即可，如果存在，那么整个块的数都可以删去（包括不在该块但是比这个块中的数还小的数）。复杂度容易通过 multiset 做到 $\mathcal{O}(q\log^2 V)$。实现存在一些细节。

给一个写的比较粗糙的代码，好像写成了 3log 了，但是时限给的挺大，也能轻松通过（最大点用时 1324ms）。

代码：https://www.luogu.com.cn/paste/r8w0ca95

---

