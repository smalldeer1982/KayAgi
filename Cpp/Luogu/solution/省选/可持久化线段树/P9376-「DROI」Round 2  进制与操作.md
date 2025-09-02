# 「DROI」Round 2  进制与操作

## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。

## 题目描述

定义数 $x$ 在 $B$ 进制下的一次操作为以下两种操作中的任意一种：

- 令 $x \rightarrow \lfloor \dfrac{x}{B} \rfloor$。

- 令 $x \rightarrow x \times B + t $。其中 $t \in [0,B-1]$。

现给定长度为 $n$ 的序列 $A$。$m$ 次询问，每次询问形如：

- `l r B` 表示询问将序列 $A$ 中下标在 $[l,r]$ 之内的数在 $B$ 进制下操作，至少多少次才能将所有数变为相同（注：每次操作是对**一个数**进行操作）。

**询问间相互独立，即操作不会真的进行。**



## 说明/提示

### 样例解释

对于样例一，五次询问分别将区间内所有数变为 $3$、$4$、$8$、$4$、$6$ 是一种最优操作。

------------

### 数据范围 

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(10\%)$：$n,m \leq 1000$。

- $\operatorname{Subtask} 2(20\%)$：保证所有询问 $B=2$。

- $\operatorname{Subtask} 3(40\%)$：$n,m \leq 3 \times 10^4$。

- $\operatorname{Subtask} 4(30\%)$：无特殊限制。

对于 $100\%$ 的数据：$1 \leq n,m \leq 10^5$，$2 \leq A_i,B \leq 10^8$。


## 样例 #1

### 输入

```
5 5
7 6 5 8 9
1 3 2
2 5 2
4 4 6
3 5 4
1 5 3```

### 输出

```
5
8
0
5 
10```

## 样例 #2

### 输入

```
8 4
10 14 7 11 19 13 7 18 
1 7 4
3 8 2
1 4 4
1 4 2
```

### 输出

```
15
18
8
11
```

# 题解

## 作者：dead_X (赞：8)

低情商：垃圾题。

高情商：颇有联考风范。

算了，可能是我对有趣的 DS 已经产生了足够扭曲的认识吧。

首先将所有数全部转 $B$ 进制变成字符串，然后操作就是 ``push_back``，``pop_back``。

显然最后所有数都会变成某个数的一段前缀，记最后变成了 $a_x[1,y]$，我们只需要统计 $\sum\limits_{t=1}^y\sum\limits_{i=l}^r[a_i[1,t]=a_x[1,t]]$ 即可，单次统计等价于 $\log a$ 次矩形查询，使用主席树可以做到 $\log^2 a$。

不难发现 $\sum\limits_{i=l}^r[a_i[1,t]=a_x[1,t]]$ 要 $\geq\frac{r-l+1}{2}$ 才是更优的，因此我们随机选一个数有 $\frac{1}{2}$ 的概率选到答案，选 $\log n+\log m$ 个数即可保证正确率。

随机选择一个数后一位一位扫判断 $\sum\limits_{i=l}^r[a_i[1,t]=a_x[1,t]]\geq\frac{r-l+1}{2}$ 是否成立即可，时间复杂度 $O(n(\log n+\log m+\log a)\log^2 a)$。


---

## 作者：Demeanor_Roy (赞：2)

- 出题人题解。

------------

做法比较复杂，我们一个一个 Subtask 来看。

### Subtask 0

不难发现操作的实质就是把一个数在 $B$ 进制加/减一位。也不难发现将一个数 $x$ 在 $B$ 进制下变成 $y$ 的最小操作数就是将 $x$ 先变成 $x$ 与 $y$ 在 $B$ 进制下的最长公共前缀再变成 $y$。

由于要使操作数最少，显然最后所有数都会变为区间内某个数的某个前缀，于是可以暴力枚举最终变为的数，计算贡献，时间复杂度 $O(nm\log v)$。

------------

### Subtask 1

考虑从令一个角度计算贡献：我们假设先把区间内所有数在 $B$ 进制下变为 $0$，再一位一位退回去。此时如果一个数 $x$ 原来的这一位与退回去的数相同，操作数就减一，若 $x$ 原来的这一位与退回去的数不同或不存在这一位，操作数就加一。

这样做的好处是我们可以一位一位从前往后贪心考虑，只有当所选择退的数能使总操作数减少时我们才继续考虑，这是因为如果退回去有用，那么至少区间内有大于一半的数都有这个前缀，所以这样的数只有一个，且往其他方向后续依旧不可能使操作数减少。故贪心成立。

当 $B=2$ 时，我们需要做的是就是维护区间中的数在 $2$ 进制下有某个前缀的数的个数。显然可以用可持久化字典树做这件事，时间复杂度 $O(n \log v)$。值得注意的是，此处字典树需要将每个数在二进制下前端对齐，而非普通情况下的后端对齐。

------------

### Subtask 2

当 $B$ 不确定时，我们显然无法再利用上述思路。限制有两点，第一是每一位的选择多了，单知道区间中的数在 $B$ 进制下有某个前缀的数的个数是不够的。第二就是 $B$ 是时刻变化的，我们无法预处理出想要的信息。

这时让我们将前两个 Subtask 联合起来，枚举最终变为哪个数的前缀，然后利用上一个 Subtask 的思路计算贡献。显然此时可以忽略第一个限制，而第二个限制其实可以枚举 $B$ 进制下的位数后用主席树查询区间中属于 $[L,R]$ 的数的个数来实现，具体来说如果当且前缀是 $x$，枚举的前缀后面的位数为 $k$，则查询 $[x \times B^k,x \times B^{k+1} - 1]$ 即可。

但显然第一个限制不能真的忽略，我们不可能枚举每一个数。那该怎么办呢？考虑 [这道题](https://www.luogu.com.cn/problem/P3765) 的一个套路，我们发现由于区间内有大于一半的数都有这个前缀才有退回去的意义，那么我们只需要在区间内随机 $k$ 个数，就有 $\dfrac{2^k-1}{2^k}$ 的概率得到最优答案。假设所有测试点询问次数为 $T$。那么全对的概率就为 $(\dfrac{2^k-1}{2^k})^T$，算下来 $k$ 取 $22$ 时大约为 $0.7$，因为是 IOI 赛制，所以足够了。（如果是 OI 赛制建议取到 $25$）。

但还有一个问题，这样做的时间复杂度是 $O(nk\log^3v)$。尽管远远跑不满，但通过本档部分分还是比较困难。考虑真正有用的前缀只有一个，所以如果用 `map` 将随机化时前缀的答案记录下来，均摊分析时间复杂度就做到 $O(nk\log^2v)$。由于跑不满，足以通过本 Subtask。

------------

### Subtask 3

考虑优化上一个算法，不难发现其时间复杂度与 $B$ 的大小息息相关，比如 $B=2$ 与 $B=4$ 时效率就差了 $4$ 倍。这启发我们数据分治，对于较小的 $B$ 使用 Subtask 1 的算法，较大的 $B$ 使用 Subtask 2 的算法。考虑到前者空间复杂度较高，笔者取的阈值为 $6$，足以通过本题。

------------

由于本题代码较为复杂，是锻炼码力的好题，所以这里就不给出代码了。若有需要可以私信找我。



---

## 作者：lfxxx (赞：1)

首先考虑怎么暴力。

考虑把每个数进行 $B$ 进制分解，然后我们惊奇的发现这两个操作就是把最低位去掉和往最低位后面插入一个数。

然后我们顺藤摸瓜，把每个数的分解扔到 Trie 树上，我们发现我们要找到一个节点，使得所有单词节点到其的距离之和最短，答案就是这个最短距离。

这里直接考虑一个 Trie 树上 dp，记所有单词节点到节点 $i$ 的最短距离为 $dp_i$，然后直接去转移。

然后考虑找找性质。

记 $sz_i$ 表示以节点 $i$ 为根的子树内单词节点数量，我们发现节点 $i$ 的转移如下 $dp_i = dp_{fa_i} - sz_j + (sz_1 - sz_j)$。

又因为 $sz_i \leq sz_{fa_i}$，所以只有当节点 $i$ 满足 $sz_i \times 2 > sz_1$ 进入到以 $i$ 为根的子树转移才最优。

而我们又发现对于一个节点满足条件的子节点**至多只有 $1$ 个**。

也就是说如果把最优答案在树上的转移画出来，并称其为**最优路径**，那么首先这一定是一条从根出发的路径，而且以这条路径所代表的数为前缀的数一定超过总数的**一半**。

然后有两种优化方向。

第一种是利用可持久化 Trie 树预处理，然后直接在 Trie 上利用刚刚的性质暴力 $\log_{B} V$ 查询，缺点是对于每个 $B$ 都要建一棵树。

第二种是因为我们只在乎最优路径上的转移，所以我们随机抽取 $\log n$ 个节点放到 Trie 树上，显然因为这个性质类似于**绝对众数**的性质，因此最优的转移路径不在 Trie 上出现的可能只有 $\frac{1}{n}$。那么多抽取几个节点就可以基本保证一定会出现。

那么转移路径找出来了，现在问题是转移中 $sz_i$ 怎么求？

我们有发现 $sz_i$ 等价于 $B$ 进制下以从根节点到节点 $i$ 所表示的数为前缀的数的数量，而这个可以枚举这个前缀后面有几位数转变成一个连续区间上查询权值为 $[L,R]$ 的数的数量，这个可以直接主席树来搞。这么做缺点是复杂度是 $n \log_{B}^3 V$。

考虑到 $\log_{2} n$ 一般远大于 $\log_{3} n$。

所以结合两种算法，用第一种算法解决 $B = 2$ 的询问，用第二种算法解决其他询问。

那么就做完了。

~~代码极丑，慎入。~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int top = 100000001;
const int maxn = 1e6+114;
struct Node{
    int sz;//当前这个节点子树内有多少个单词节点
    vector <pair<int,int> > edge;//边
}Trie[maxn];
struct node{
    int sz;
    int ls,rs;
}_01trie[maxn*30];
struct NODE{
    int val;
    int ls,rs;
}SGTtree[maxn*30];
int SGTroot[maxn];
int SGTtot=1;
int SGTask(int ql,int qr,int lt,int rt,int L,int R){
    if(rt<ql||lt>qr){
        return 0;
    }
    if(ql<=lt&&rt<=qr){
        return SGTtree[R].val-SGTtree[L].val;
    }
    int mid=(lt+rt)/2;
    int res=0;
    res+=SGTask(ql,qr,lt,mid,SGTtree[L].ls,SGTtree[R].ls);
    res+=SGTask(ql,qr,mid+1,rt,SGTtree[L].rs,SGTtree[R].rs);
    return res;
}
int SGTquery(int l,int r,int cl,int cr){
    return SGTask(cl,cr,1,top,SGTroot[l-1],SGTroot[r]);
}
void SGTupdate(int cur,int lst,int lt,int rt,int pos,int v){
    SGTtree[cur].val=SGTtree[lst].val+v;
    if(lt==rt){
        return ;
    }
    int mid=(lt+rt)/2;
    if(pos<=mid){
        SGTtree[cur].rs=SGTtree[lst].rs;
        SGTtree[cur].ls=++SGTtot;
        SGTupdate(SGTtree[cur].ls,SGTtree[lst].ls,lt,mid,pos,v);
    }
    else{
        SGTtree[cur].ls=SGTtree[lst].ls;
        SGTtree[cur].rs=++SGTtot;
        SGTupdate(SGTtree[cur].rs,SGTtree[lst].rs,mid+1,rt,pos,v);
    }
}
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return min(a,top);
    int res=min(qpow(a,b/2),top);
    res=min(top,res*res);
    if(b%2==1) res=min(res*a,top);
    return min(top,res);
}
void SGTadd(int pos,int val){
    SGTroot[pos]=++SGTtot;
    SGTupdate(SGTroot[pos],SGTroot[pos-1],1,top,val,1);
}
int SUMQUERY(int B,int L,int R){//查询 B 进制下区间 [L,R] 所有数长度之和 
    int res=0;
    for(int k=1;k<=30;k++){
        int l=min(top,qpow(B,k-1)),r=min(top,qpow(B,k)-1);
        res+=SGTquery(L,R,l,r)*k;
        if(r==top) break;
    }
    return res;
}
int PREQUERY(int x,int B,int L,int R){//查询 B 进制下区间 [L,R] 内多少个数前缀为 x
    int res=0;
    for(int k=0;k<=30;k++){
        int l=min(top,x*qpow(B,k)),r=min(top,(x+1)*qpow(B,k)-1);
        res+=SGTquery(L,R,l,r);
        if(r==top) break;
    }
    return res;
}
int tot=1,anser;
int _01tot=1;
int sum;
int n,m;
int flag;
stack<int> s;
int root[maxn],Sum[maxn];
void _01insert(int cur,int lst){
    _01trie[cur].sz++;
    s.pop();
    if(s.size()==0) return ;
    if(s.top()==0){
        _01trie[cur].rs=_01trie[lst].rs;
        _01trie[cur].ls=++_01tot;
        _01trie[_01trie[cur].ls].sz+=_01trie[_01trie[lst].ls].sz;
        _01insert(_01trie[cur].ls,_01trie[lst].ls);
    }
    else{
        _01trie[cur].ls=_01trie[lst].ls;
        _01trie[cur].rs=++_01tot;
        _01trie[_01trie[cur].rs].sz+=_01trie[_01trie[lst].rs].sz;
        _01insert(_01trie[cur].rs,_01trie[lst].rs);
    }
}
void _01dfs(int l,int r,int ans,int L,int R){
    if(l==0&&r==0) return ;
    anser=min(anser,ans);
    if(_01trie[_01trie[r].ls].sz-_01trie[_01trie[l].ls].sz>_01trie[_01trie[r].rs].sz-_01trie[_01trie[l].rs].sz){
        _01dfs(_01trie[l].ls,_01trie[r].ls,ans-(_01trie[_01trie[r].ls].sz-_01trie[_01trie[l].ls].sz)+(_01trie[R].sz-_01trie[L].sz-(_01trie[_01trie[r].ls].sz-_01trie[_01trie[l].ls].sz)),L,R);
    }
    else{
        _01dfs(_01trie[l].rs,_01trie[r].rs,ans-(_01trie[_01trie[r].rs].sz-_01trie[_01trie[l].rs].sz)+(_01trie[R].sz-_01trie[L].sz-(_01trie[_01trie[r].rs].sz-_01trie[_01trie[l].rs].sz)),L,R);
    }
}
int _01query(int l,int r){
    anser=INT_MAX;
    _01dfs(root[l-1],root[r],Sum[r]-Sum[l-1],root[l-1],root[r]);
    return anser;
}
void _01add(int x,int B,int pos){
    while(x!=0){
        s.push(x%B);
        x/=B;
    }
    s.push(0);
    Sum[pos]=s.size()-1+Sum[pos-1];
    root[pos]=++_01tot;
    _01trie[root[pos]].sz+=_01trie[root[pos-1]].sz;
    _01insert(root[pos],root[pos-1]);
}
void insert(int cur,int val){
    Trie[cur].sz+=val;
    s.pop();
    if(s.size()==0) return ;
    for(pair<int,int> v:Trie[cur].edge){
        if(v.second==s.top()){
            insert(v.first,val);
            return ;
        }
    }
    Trie[cur].edge.push_back(make_pair(++tot,s.top()));
    insert(tot,val);
}
void add(int x,int B){
    while(x!=0){
        s.push(x%B);
        x/=B;
    }
    s.push(0);
    sum+=s.size()-1;
    insert(1,1);
}
void dfs(int cur,int ans,int PRE,int S,int B,int L,int R){
    anser=min(anser,ans);
    for(pair<int,int> v:Trie[cur].edge){
        int nxt=PRE*B+v.second;
        int g=PREQUERY(nxt,B,L,R);
        if((S-g)-g>=0) continue;
        dfs(v.first,ans-g+(S-g),nxt,S,B,L,R);
    }
}
int query(int B,int L,int R){
    anser=INT_MAX;
    dfs(1,SUMQUERY(B,L,R),0,(R-L+1),B,L,R);
    return anser;
}
void clear(){
    for(int i=1;i<=tot;i++){
        Trie[i].edge.clear();
        Trie[i].sz=0;
    }
    sum=0;
    tot=1;
}
int a[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
            cin>>a[i];
            SGTadd(i,a[i]);
            _01add(a[i],2,i);
    }       
    while(m--){
        int l,r,B;
        cin>>l>>r>>B;
        if(B==2){
            cout<<_01query(l,r)<<"\n";
        }
        else{
        clear();
        for(int j=1;j<=22;j++){
            int x=rand()%(r-l+1)+l;
            add(a[x],B);
        }
        cout<<query(B,l,r)<<'\n';
        }
    }            
}
/*
5 2
7 6 5 8 9
1 3 2
2 5 2
*/
```


---

