# [POI 2008] POC-Trains

## 题目描述

The Trains of Colour Parade begins tomorrow in Byteotia.

Intense preparations are already in progress at the station's auxiliary tracks. There are $n$ parallel tracks at the station, numbered from $1$ to $n$. The train no. $i$ occupies the $i^{th}$ track.

Every train consists of $l$ cars and each car is painted with one of 26 colours (denoted by non-capital letters of the English alphabet).

We say that two trains look the same, if their corresponding cars are painted the same colour.

Throughout the parade a crane will switch places of certain pairs of cars. The real parade, however, will take place tomorrow.

Today the train dispatcher, Byteasar, watched the general rehearsal    closely. He even wrote down the sequence of car swaps.

Byteasar particularly dislikes many trains looking the same.

For each train $p$ he would like to calculate the maximum number    of trains that at some moment look the same as the train $p$ at the very same moment.

## Task

Write a programme that:

- reads descriptions of the trains occupying tracks and the sequence of car swaps,

- for each train determines the maximum number of trains that look the same as it at certain moment,

- writes out the result.


给出n个字符串，长度均为len；

有m次操作，每次将两个字符交换；

求每个字符串在任何时点上，与相同的它最多的字符串个数；


## 说明/提示

The figure presents the successive car swaps:

```cpp
track 1:  ababbd    ababbd    ababbd    ababbd    aaabbd    aaabbd    aaabbd    aaabbd
track 2:  abbbbd    ababbd    ababbd    aaabbd    aaabbd    acabbd    acabbd    acabbd
track 3:  aaabad -> aaabad -> aaabad -> aaabbd -> aaabbd -> aaabbd -> aaabbd -> aaabbd
track 4:  caabbd    caabbd    caabbd    caabbd    cabbbd    cabbbd    cabbbd    dabbbd
track 5:  cabaad    cabbad    caabbd    caabbd    caabbd    aaabbd    aaabbd    aaabbc
           (0)       (1)       (2)       (3)       (4)       (5)       (6)       (7)
```

The number of trains looking the same as either of the trains no. 1, 2 or 3 was maximal at time (4) (when all three looked the same). The number of trains looking the same as the train no. 5 was maximal at time (5) and (6). The number of trains looking the same as the train no. 4 was maximal at time (2).


## 样例 #1

### 输入

```
5 6 7
ababbd
abbbbd
aaabad
caabbd
cabaad
2 3 5 4
5 3 5 5
3 5 2 2
1 2 4 3
2 2 5 1
1 1 3 3
4 1 5 6
```

### 输出

```
3
3
3
2
3
```

# 题解

## 作者：ppip (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P3471)

这是一个 $O(nl+m)$ 的做法（即和输入同阶）。

首先，看到字符串相同显然想到哈希。我们开一个哈希表，每个键值维护一个 `size`。对于每次修改，从表中原位置删除，重新计算哈希然后插入到新位置。

更新的话，只要在删除的时候查一下在当前的键值下，从插入到现在这段时间中 `size` 的最大值。

所以，我们只需要在线支持如下操作：

- 查询后缀最大值
- 在结尾插入一个数

显然可以开一个并查集维护（如果不会带权并查集可以看[这个](https://www.luogu.com.cn/blog/374433/union-find)）。

```cpp
// 返回的不是祖先而是 `x` 这个点的后缀最大值（其实所有点的祖先都是最后插入的数）
int Find(int u,int x)
{
    if (dsu[u][x].fa==x) return dsu[u][x].mx;
    dsu[u][x].mx=max(dsu[u][x].mx,Find(u,dsu[u][x].fa));
    dsu[u][x].fa=dsu[u][dsu[u][x].fa].fa;
    return dsu[u][x].mx;
}
void insert(int x)
{
    int H{h[x]};// h[x] 为串 x 的哈希
    // 动态开 vector，主要是开表大小个 vector 内存会炸
    if (!F[H]) F[H]=cnt++;
    // 插入的位置（即删除时要查询的位置）
    lst[x]=dsu[F[H]].size();
    ++sz[H];
    // 将前面的树 merge 到新插入的点
    if (lst[x]) dsu[F[H]][lst[x]-1].fa=lst[x];
    // 插入新节点
    dsu[F[H]].emplace_back(lst[x],sz[H]);
}
```

因为只有一棵树且没有 `merge`，所以这份并查集的复杂度是线性的。

最后还要再更新一下最大值。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int bn{2579},b6e0{25165843};
const int N(1e3),M(1e5);
int sz[b6e0],res[N];
int lst[N];
int F[b6e0];
struct node
{
	int fa,mx;
	node(int _fa=0,int _mx=0):fa{_fa},mx{_mx}{}
};
vector<node> dsu[N+M];int cnt;
int h[N],pl[N],l;
string s[N];
int Find(int u,int x)
{
	if (dsu[u][x].fa==x) return dsu[u][x].mx;
	dsu[u][x].mx=max(dsu[u][x].mx,Find(u,dsu[u][x].fa));
	dsu[u][x].fa=dsu[u][dsu[u][x].fa].fa;
	return dsu[u][x].mx;
}
void fresh(int x,int p,int n)
{
    h[x]=(h[x]+1LL*pl[l-p-1]*(n-s[x][p])%b6e0)%b6e0;
    if (h[x]<0) h[x]=(h[x]+b6e0)%b6e0;
    s[x][p]=n;
}
void upd(int x)
{
	int H{h[x]};
	if (!F[H]) F[H]=cnt++;
	lst[x]=dsu[F[H]].size();
	++sz[H];
    if (lst[x]) dsu[F[H]][lst[x]-1].fa=lst[x];
	dsu[F[H]].emplace_back(lst[x],sz[H]);
	
}
int main()
{
    int n,m;cin>>n>>l>>m;
    for (int i{0};i<n;++i)
    {
        cin>>s[i];
        for (char c:s[i])
            h[i]=(1LL*h[i]*bn%b6e0+c-'a')%b6e0;
        upd(i); 
    }
    pl[0]=1;
    for (int i{1};i<=l;++i)
        pl[i]=1LL*pl[i-1]*bn%b6e0;
    while (m--)
    {
        int a,i,b,j;
        scanf("%d %d %d %d",&a,&i,&b,&j);
        --a;--i;--b;--j;
        --sz[h[a]];res[a]=max(res[a],Find(F[h[a]],lst[a]));
        if (a!=b) --sz[h[b]],res[b]=max(res[b],Find(F[h[b]],lst[b]));
        char x{s[a][i]},y{s[b][j]};
        fresh(a,i,y);fresh(b,j,x);
        upd(a);if (a!=b) upd(b);
    }
    for (int i{0};i<n;++i)
        cout<<max(res[i],Find(F[h[i]],lst[i]))<<endl;
    return 0;
}
```

---

## 作者：degage (赞：3)

额，这道题我是先hash，然后用multiset水过去的，开了O2速度海星2333

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull base=131;
#define maxn 1005
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    } 
    return x*f;
}
ull hsh[maxn],val;
int n,l,m,ans[maxn],x,y,xx,yy;
char s[maxn][105];
multiset<ull>ss;
multiset<ull>::iterator it;
void init(){
    n=read();l=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        val=0;
        for(int j=1;j<=l;j++){
            val=val*base+s[i][j]-'0';
        }
        hsh[i]=val;
        ss.insert(hsh[i]);
    }
    for(int i=1;i<=n;i++) {
    int t=ss.count(hsh[i]);
    ans[i]=max(ans[i],t);	
    }
    for(int i=1;i<=m;i++){
        x=read();y=read();xx=read();yy=read();
        if(s[x][y]==s[xx][yy]) continue;
        swap(s[x][y],s[xx][yy]);
        if(x==xx){
            it=ss.find(hsh[x]);
            ss.erase(it);
            val=0;
            for(int j=1;j<=l;j++) val=val*base+s[x][j]-'0';
            hsh[x]=val;
            ss.insert(hsh[x]);
            int t1=ss.count(hsh[x]);
            for(int j=1;j<=n;j++){
            if(hsh[j]==hsh[x]) ans[j]=max(ans[j],t1);
            }
            continue;
        }
        it=ss.find(hsh[x]);
        ss.erase(it);
        it=ss.find(hsh[xx]);
        ss.erase(it);
        val=0;
        for(int j=1;j<=l;j++) val=val*base+s[x][j]-'0';
        hsh[x]=val;
        val=0;
        for(int j=1;j<=l;j++) val=val*base+s[xx][j]-'0';
        hsh[xx]=val;
        ss.insert(hsh[x]);ss.insert(hsh[xx]);
        int t1=ss.count(hsh[x]),t2=ss.count(hsh[xx]);
        for(int j=1;j<=n;j++){
            if(hsh[j]==hsh[x]) ans[j]=max(ans[j],t1);
            if(hsh[j]==hsh[xx]) ans[j]=max(ans[j],t2);
        }
    } 
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    
}
int main(){
    init();
    
    return 0;
}
```


---

## 作者：ink_ngm (赞：2)

~~非常好的平衡树题，让我的哈希旋转。~~

## 整体思路

哈希

分析一下题目，本题让我们找到在交换车厢的某个时刻，与该车颜色完全相同的火车最多数目。对于匹配相同字符串个数，我们很容易能想到 $\mathcal{O} (1)$ 查询哈希优化实现，对于本题 $n \leq 1000$ 的数据范围，我们可以在**每次修改火车哈希值后，暴力更新每个火车的最大值答案**，总时间复杂度为 $\mathcal{O} (nm)$，足以通过本题。

当然，对于本题的哈希值对应个数的记录，大多题解使用 unordered_map 记录，但是，对于本题会多次访问查询个数，使用 map 反而会更优：因为哈希实现的 unordered_map 在元素过多时造成的冲突会导致其复杂度退化。因为本题字符串长度 $n \leq 100$，哈希冲突概率不大，我们使用单哈希便可以通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;register char ch=getchar_unlocked();
	while(ch<'0'||'9'<ch){ch=getchar_unlocked();}
	while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48),ch=getchar_unlocked();}
	return x;
}
const int N=1e3+5,p=13331;
unsigned long long Hash[N],power[N],num[N];
map<unsigned long long,int>mp;
int ans[N];
char ch[N][105];
int main(){
	register int n=read(),l=read(),q=read()+1,i,j;
	power[0]=1;
	for(i=1;i<=n;++i) power[i]=power[i-1]*p;
	for(i=1;i<=n;++i){
		scanf("%s",ch[i]+1);
		for(j=1;j<=l;++j) Hash[i]=Hash[i]+(ch[i][j]-'a'+1)*power[j];
		++mp[Hash[i]];
	}
	for(i=1;i<=n;++i) ans[i]=mp[Hash[i]];
	while(--q){
		register int x=read(),l=read(),y=read(),r=read();
		if(ch[x][l]^ch[y][r]){//两节相同车间交换必不会对答案造成贡献
			--mp[Hash[x]];
			if(x^y) --mp[Hash[y]];//防止同一辆火车交换车间，导致答案多算
			Hash[x]-=(ch[x][l]-'a'+1)*power[l],Hash[y]-=(ch[y][r]-'a'+1)*power[r];
			swap(ch[x][l],ch[y][r]);
			Hash[x]+=(ch[x][l]-'a'+1)*power[l],Hash[y]+=(ch[y][r]-'a'+1)*power[r];
			++mp[Hash[x]];
			if(x^y) ++mp[Hash[y]];
		}
		for(i=1;i<=n;++i){
			if(Hash[i]^Hash[x]&&Hash[i]^Hash[y]) continue;
			ans[i]=max(ans[i],mp[Hash[i]]);
		}
	}
	for(i=1;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：TonviaSzt (赞：2)

概要：有 $n$ 个字符串，每个字符串的长度为 $m$。有 $q$ 次操作。每次交换两个字符串的两个字母。
对于每个字符串，求在整个交换过程中，最多有多少个字符串与它相同。

$n\le10^3,m\le100,q\le10^5$。

---

洛谷题解的方法大都很阳间，带权并查集的，非旋 $\operatorname{treap}$ 的，很牛。

$n\cdot q\cdot m\log m$ 的暴力在原题的飞速机子上能拿到 62 的好成绩，$\operatorname{map}$ 改成 $\operatorname{unordered\_map}$ 能提高3分。

考虑去掉 $m\log m$，哈希维护文本串即可，将每个字符串转成特征数字，特征数字若用 $\operatorname{map}$ 存会保留 $\log m$，拿到 73 的好成绩，压缩特征数字的值域，拿个桶存即可，保险起见可以用双哈希，更新答案的时候取 $\min$ 即可。

修改复杂度 $O(1)$，更新复杂度 $O(n)$，总复杂度 $O(nq)$ 很稳。

最短代码用单哈希 $\operatorname{unordered\_ map}$ 搭配自然溢出跑的飞快，我也试了，超时，令人忍俊不禁。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M1=10000019,M2=99959;
int n,m,q,a[1005],hsh1[1005],hsh2[1005];
int q1[1005],q2[1005],mp1[M1+5],mp2[M2+5];
string s[1005];
int main(){
//	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	q1[0]=1;for(int i=1;i<=m;i++) q1[i]=q1[i-1]*131%M1;
	q2[0]=1;for(int i=1;i<=m;i++) q2[i]=q2[i-1]*127%M2;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		for(int j=0;j<m;j++) (hsh1[i]+=1ll*s[i][j]*q1[j]%M1)%=M1,(hsh2[i]+=1ll*s[i][j]*q2[j]%M2)%=M2;
		mp1[hsh1[i]]++,mp2[hsh2[i]]++;
	}
	while (q--){
		int x,y,z,t;
		cin>>x>>y>>z>>t;y--;t--;
		mp1[hsh1[x]]--,mp2[hsh2[x]]--;if(x^z) mp1[hsh1[z]]--,mp2[hsh2[z]]--;
		hsh1[x]=((1ll*hsh1[x]-1ll*s[x][y]*q1[y])%M1+M1)%M1;hsh2[x]=((1ll*hsh2[x]-1ll*s[x][y]*q2[y])%M2+M2)%M2;
		hsh1[z]=((1ll*hsh1[z]-1ll*s[z][t]*q1[t])%M1+M1)%M1;hsh2[z]=((1ll*hsh2[z]-1ll*s[z][t]*q2[t])%M2+M2)%M2;
		swap(s[x][y],s[z][t]);
		hsh1[x]=((1ll*hsh1[x]+1ll*s[x][y]*q1[y])%M1+M1)%M1;hsh2[x]=((1ll*hsh2[x]+1ll*s[x][y]*q2[y])%M2+M2)%M2;
		hsh1[z]=((1ll*hsh1[z]+1ll*s[z][t]*q1[t])%M1+M1)%M1;hsh2[z]=((1ll*hsh2[z]+1ll*s[z][t]*q2[t])%M2+M2)%M2;
		mp1[hsh1[x]]++,mp2[hsh2[x]]++;if(x^z) mp1[hsh1[z]]++,mp2[hsh2[z]]++;
		for(int i=1;i<=n;i++) a[i]=max(a[i],min(mp1[hsh1[i]],mp2[hsh2[i]]));
//		for(int i=1;i<=n;i++) printf("%d %d\n",mp1[hsh1[i]],mp2[hsh2[i]]);puts("");
//		for(int i=1;i<=n;i++) printf("%d ",mp[s[i]]);puts("");
	}
	for(int i=1;i<=n;i++) printf("%d\n",a[i]);
}
```

---

## 作者：Ebola (赞：2)

发现字符串都很短，因此哈希冲突的概率不大，我们维护这些串的哈希值

那么我们对每个哈希值，要用一个数据结构来维护它，这个数据结构需要支持：插入、删除、下放标记（因为这个数据结构的大小，对里面所有元素的答案都可能有贡献）

线段树（动态开点）、平衡树都是可以的，这里我选择了Treap

开若干个Treap，与哈希值一一对应，其键值的含义是字符串的编号

由于哈希值是非常大的，不可能将根数组的下标开到那么大，因此我们使用一个map，将哈希值散列到一个小数组中，这样根数组就不会超过n+m了。当然也可以直接将map作为根数组

每当一个字符串的哈希值发生改变，我们将这个字符串从原来那个哈希值对应的Treap中删去，然后加入到新哈希值对应的Treap中，并更新根节点的lazy标记

lazy表示的是自己所在的Treap中，曾经达到过的最大结点数，这就是题目中说的“在交换车厢的某个时刻，与其颜色完全相同的火车最多有多少”

那么在插入、删除、旋转的过程中，都要先进行标记下放，并顺便更新答案。由于同时有标记下放与信息上传，因此一定要特别注意顺序。下放是访问一个结点之前进行的，上传是访问完一个结点进行的

注意加上a=c的特判，否则会导致RE

```cpp
#include<bits/stdc++.h>
#define newnode(x) x=new Node,x->son[0]=x->son[1]=null
using namespace std;

int read()
{
    int x=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x;
}

typedef unsigned long long ULL;
const int N=1010,M=100010;
ULL f[N],p[N];
char s[N][110];
int tot=0;
int ans[N];

struct Node
{
    Node *son[2];
    int sz,v,tag,r;
    Node(){son[0]=son[1]=NULL;}
};
Node *null;
map<ULL,Node*> rt;

void down(Node* &o,int x)
{
    ans[o->v]=max(ans[o->v],x);
    o->tag=max(o->tag,x);
}

void pushdown(Node* &o)
{
    if(!o->tag) return;
    Node *lc=o->son[0];
    Node *rc=o->son[1];
    if(lc!=null) down(lc,o->tag);
    if(rc!=null) down(rc,o->tag);
    o->tag=0;
}

void maintain(Node* &o){o->sz=o->son[0]->sz+o->son[1]->sz+1;}

void rotate(Node* &o,int d)
{
    Node *k=o->son[d^1];
    pushdown(o);
    pushdown(k);
    o->son[d^1]=k->son[d];
    k->son[d]=o;
    maintain(o);
    maintain(k);
    o=k;
}

void insert(Node* &o,int x)
{
    if(o==null)
    {
        newnode(o);
        o->sz=1;
        o->v=x;
        o->tag=0;
        o->r=rand();
        return;
    }
    pushdown(o);
    if(x<o->v)
    {
        insert(o->son[0],x);
        if(o->son[0]->r>o->r) rotate(o,1);
        else maintain(o);
    }
    else
    {
        insert(o->son[1],x);
        if(o->son[1]->r>o->r) rotate(o,0);
        else maintain(o);
    }
}

void remove(Node* &o,int x)
{
    if(o==null) return;
    pushdown(o);
    if(o->v==x)
    {
        if(o->son[0]==null) o=o->son[1];
        else if(o->son[1]==null) o=o->son[0];
        else
        {
            if(o->son[0]->r>o->son[1]->r) rotate(o,1),remove(o->son[1],x);
            else rotate(o,0),remove(o->son[0],x);
        }
    }
    else if(x<o->v) remove(o->son[0],x);
    else remove(o->son[1],x);
    if(o!=null) maintain(o);
}

void insert(int x)
{
    if(!rt.count(f[x])) rt[f[x]]=null;
    insert(rt[f[x]],x);
    Node *o=rt[f[x]];
    down(o,o->sz);
}

int main()
{
    newnode(null);
    int n=read(),l=read(),m=read();
    p[0]=1;for(int i=1;i<=100;i++) p[i]=131*p[i-1];
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s[i]+1);
        for(int j=1;j<=l;j++)	
            f[i]=f[i]*131+s[i][j];
        insert(i);
    }
    for(int i=1;i<=m;i++)
    {
        int a=read(),b=read(),c=read(),d=read();
        if(a==c)
        {
            remove(rt[f[a]],a);
            f[a]+=p[l-b]*(s[a][d]-s[a][b]);
            f[a]+=p[l-d]*(s[a][b]-s[a][d]);
            swap(s[a][b],s[a][d]);
            insert(a);
            continue;
        }
        remove(rt[f[a]],a);remove(rt[f[c]],c);
        f[a]+=p[l-b]*(s[c][d]-s[a][b]);
        f[c]+=p[l-d]*(s[a][b]-s[c][d]);
        swap(s[a][b],s[c][d]);
        insert(a);insert(c);
    }
    for(int i=1;i<=n;i++) remove(rt[f[i]],i);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：__FL__ (赞：1)

优雅的暴力。

## 题意

给定 $n$ 个字符串，共有 $m$ 组修改操作，每次修改将第 $p1$ 个字符串的第 $w1$ 个字符和第 $p2$ 的第 $w2$ 个字符交换，统计每个字符串在任意一个时间点时，与它相同的字符串的数量最多是多少。

## 思路

本蒟蒻写平衡树写寄了，我们来思考能不能用暴力创过这道题。发现 $O(nm)$ 的量级只有 $1e8$，我们将此为突破口。由于主体是字符串，很容易想到用 $\mathrm{unordered\_map}$ 或是哈希将字符串映射成数字。考虑记录每个字符串出现的次数，更新答案时直接枚举并转换即可，细节可以参考代码。

可是本蒟蒻用的是 $\mathrm{unordered\_map}$，每次更新答案都要进行查找，会因巨大常数悲惨地超时。我们可以记录每个字符串在 $\mathrm{map}$ 中映射的值，每次修改字符串时进行更新。

## 复杂度分析

两层枚举的复杂度是 $O(nm)$，而因为我们已经处理出字符串映射的值，所以这个复杂度的常数非常小。代码吸氧后可以跑到最优解第一页，不吸氧也能创过。

## 代码

注意特殊处理 $p1 = p2$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,m,sz[300005],cnt,ans[300005],p1,w1,p2,w2,id[1005];
string a[1005];
unordered_map<string,int>mp;
void insert(string &a,int &p)
{
	int t = mp[a];
	if (!t)
	{
		mp[a] = ++cnt;
		sz[cnt]++;
	}
	else sz[t]++;
	id[p] = mp[a];
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n >> l >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		insert(a[i],i);
	}
	for (int i = 1; i <= n; i++)
		ans[i] = sz[mp[a[i]]];
	for (int i = 1; i <= m; i++)
	{
		cin >> p1 >> w1 >> p2 >> w2;
		w1--,w2--;
		if (p1 == p2)
		{
			sz[id[p1]]--;
			swap(a[p1][w1],a[p2][w2]);
			insert(a[p1],p1);
		}
		else
		{
			sz[id[p1]]--;
			sz[id[p2]]--;
			swap(a[p1][w1],a[p2][w2]);
			insert(a[p1],p1);
			insert(a[p2],p2);
		}
		for (int j = 1; j <= n; j++)
			ans[j] = max(ans[j],sz[id[j]]);
	}
	for (int i = 1; i <= n; i++)
		cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：XuYueming (赞：1)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P3471)。

时间复杂度和输入同阶的做法。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18332502)。

## 题意简述

有 $n$（$n \leq 10^3$）个长 $m$ 的字符串，$q$（$q \leq 10^5$）次操作，交换两个字符串的两个字符。问每个字符串在所有时刻，最多有几个和它相等。

## 题目分析

### 套路做法

看到字符串相等，想到使用哈希。但是要支持修改，怎么办呢？~~上数据结构！~~ 当然不是，把哈希的结果看做一个数字，每次把某一位的值扣掉再加上就行了。即减去该位权值乘上原值，加上权值乘上修改后的值。

至于询问，每次操作后不可能 $\Theta(n^2)$ 地弄。发现只会和当前修改的两个串有关，故 $\Theta(n)$ 把这两个串的结果统计一遍。其他的串，维护一个 $cur_i$ 表示当前 $i$ 能和几个字符串相等。如果 $i$ 和修改之前的串相等，就减去，如果和修改后的串相等了，再加上，最后和答案取个 $\max$ 即可。

需要注意的是，当两个字符串是同一个的时候，可能需要小小特判。

时间复杂度 $\Theta(nm + nq)$。可过此题。当然，可以优化。

### 优化做法

尝试从哈希表角度分析。发现，一个字符串不断从一个相同哈希值的集合中，移动到另一个集合中，而答案就是这段时间内，该集合大小的最大值。如果考虑在删除的时候统计答案，就是在该元素加入集合后，该集合大小的最大值。

尝试把集合大小独立出来，看做单独的一个权值。我们可以把元素扩展，额外附加**它在加入集合时集合的大小**，发现这样删除操作就没有了，而是直接将所在集合那个附加的权值减一。这样查询，就成了一个后缀最大值。即从所在结点一直扫到哈希表末尾，取每个结点权值的最大值，得到这段时间该集合大小的最大值。

对于一条链，我们会扫过很多次，不妨从这里优化，即去除重复操作。想到，如果扫过了一个值，那下次不用再从原来的位置开始再扫一遍，而是把当前扫过来的最值记下来，下次直接从这里开始扫就行了。很类似并查集的路径压缩。

时间复杂度呢？从一个点开始，经过若干没被压缩的点，到一个已经压缩了的点，并把前者变成已经压缩了的，与总点数相关，和 $n + q$ 是同阶的。总的时间复杂度是 $\Theta(nm + q)$ 的，非常快。

## 代码

### naive code

[代码](https://www.luogu.com.cn/paste/ng3yzpsq)。

### 优化

哈希值域太小会 WA，所以使用了 `unordered_map`，对时间复杂度没有影响。略去了快读，是[最优解](https://www.luogu.com.cn/record/169478051)。

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int N = 1010;
const int M = 110;
const int Q = 100010;
const int mod = 1e9 + 11;
const int bas = 1331;

inline int add(int a, int b) {
	return a + b >= mod ? a + b - mod : a + b;
}

inline int sub(int a, int b) {
	return a - b < 0 ? a - b + mod : a - b;
}

inline int mul(int a, int b) {
	return 1ll * a * b % mod;
}

int n, m, q;
char str[N][M];
int hsh[N], res[N], pw[M];
int whr[N];  // 记录字符串对应哪一个结点

struct node {
	int fa, ans;
} tree[N + Q * 2];
int tot;

unordered_map<int, int> ysiz, ylst;  // 哈希对应的字符串有几个、上一个哈希值为它是哪个结点

int query(int x) {  // 返回后缀最大值，并路径压缩
	if (tree[x].fa == x) return tree[x].ans;
	int res = query(tree[x].fa);
	tree[x].fa = tree[tree[x].fa].fa;
	return tree[x].ans = max(tree[x].ans, res);
}

void update(int x) {
	int bl = hsh[x];
	whr[x] = ++tot, ++ysiz[bl];
	tree[tot] = {tot, ysiz[bl]};
	tree[ylst[bl]].fa = tot;
	ylst[bl] = tot;
}

signed main() {
	fread(buf, 1, MAX, stdin);
	read(n), read(m), read(q);
	pw[0] = 1;
	for (int i = 1; i <= m; ++i)
		pw[i] = mul(pw[i - 1], bas);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			hsh[i] = add(mul(hsh[i], bas), str[i][j] = readchar());
		}
		update(i);
	}
	for (int i = 1, a, x, b, y; i <= q; ++i) {
		read(a), read(x), read(b), read(y);
		res[a] = max(res[a], query(whr[a])), --ysiz[hsh[a]];
		if (a != b) res[b] = max(res[b], query(whr[b])), --ysiz[hsh[b]];
		hsh[a] = sub(hsh[a], mul(pw[m - x], str[a][x]));
		hsh[b] = sub(hsh[b], mul(pw[m - y], str[b][y]));
		swap(str[a][x], str[b][y]);
		hsh[a] = add(hsh[a], mul(pw[m - x], str[a][x]));
		hsh[b] = add(hsh[b], mul(pw[m - y], str[b][y]));
		update(a);
		if (a != b) update(b);
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", max(res[i], query(whr[i])));  // 这里注意也要取 max
	}
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

首先发现不太好用字符串算法去做，就去考虑哈希+数据结构。对于每种字符串，将其离散化成一个数（用 unordered_map 会更快），然后用平衡树去维护实时的森林。更新操作可以在每次修改的时候做懒标记。

我这里用的是非旋 Treap。将字符串的序号作为平衡树的排序元。

复杂度 $O(nl + m\log n)$。
```cpp
#include <ctime>
#include <cstdio>
#include <random>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef unsigned long long ull;

const int M = 105;
const int N = 300005;
const ull base = 131;
int n, m, q, cnt, rec[M * 10], ans[M * 10];
char s[M * 10][M];
unordered_map<ull, int> mp;
void chmax(int &x, int y){x = max(x, y);}

namespace fhq{
	int tot, root[N], a, b, c;
	int sz[N], id[N], lc[N], rc[N], tag[N], dat[N];
	int newnode(int x){id[++ tot] = x; sz[tot] = 1; lc[tot] = rc[tot] = tag[tot] = 0; dat[tot] = rand(); return tot;}
	void pushup(int x){sz[x] = sz[lc[x]] + sz[rc[x]] + 1;}
	void pushadd(int x, int k){if(! x) return; chmax(tag[x], k); chmax(ans[id[x]], k);}
	void pushdown(int x){if(tag[x]){pushadd(lc[x], tag[x]); pushadd(rc[x], tag[x]); tag[x] = 0;}}
	void split(int x, int k, int &l, int &r){
		if(! x){l = r = 0; return;} pushdown(x); 
		if(id[x] <= k){l = x; split(rc[x], k, rc[x], r);}
		else{r = x; split(lc[x], k, l, lc[x]);}
		pushup(x);
	}
	int merge(int l, int r){
		if(l == 0 || r == 0) return l + r;
		if(dat[l] < dat[r]){pushdown(l); rc[l] = merge(rc[l], r); pushup(l); return l;}
		else{pushdown(r); lc[r] = merge(l, lc[r]); pushup(r); return r;}
	}
	void insert(int &rt, int x){split(rt, x - 1, a, b); c = newnode(x); rt = merge(merge(a, c), b); pushadd(rt, sz[rt]);}
	void del(int &rt, int x){split(rt, x - 1, a, b); split(b, x, b, c); rt = merge(a, c);}
};
using namespace fhq;

int get(int x){
	ull hsh = 0 * 1ull;
	for(int i = 1; i <= m; i ++) hsh = hsh * base + 1ull * (s[x][i] - 'a');
	if(mp[hsh]) return mp[hsh]; return mp[hsh] = ++ cnt;
}
int main(){
	srand(time(NULL)); scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i ++){scanf("%s", s[i] + 1); rec[i] = get(i); insert(root[rec[i]], i);}
	while(q --){
		int c1, c2, t1, t2; scanf("%d %d %d %d", &t1, &c1, &t2, &c2);
		del(root[rec[t1]], t1); if(t1 != t2) del(root[rec[t2]], t2); 
		swap(s[t1][c1], s[t2][c2]); rec[t1] = get(t1); rec[t2] = get(t2);
		insert(root[rec[t1]], t1); if(t1 != t2) insert(root[rec[t2]], t2);
	}
	for(int i = 1; i <= n; i ++) del(root[rec[i]], i);
	for(int i = 1; i <= n; i ++) printf("%d\n", ans[i]); return 0;
}
```


---

## 作者：黑影洞人 (赞：1)

这是一道 STL 大水题。

首先我们预处理处每一串的哈希值，然后将所有的哈希值编号。

给每一个编号开一个 set，里面储存着每一个哈希值为该哈希值的序列的编号。

```cpp
for(int i=1;i<=n;i++){
	scanf("%s",s[i]+1);
	for(int j=1;j<=m;j++)a[i]=a[i]*base+1ull*s[i][j];//处理哈希值
	if(mp.find(a[i])==mp.end())mp[a[i]]=++tot;//给新的哈希值编号
	siz[mp[a[i]]]++;
	st[mp[a[i]]].insert(i);//压入集合
}
```
然后对于交换的操作就很容易了，哈希值的话就把原来的字母的哈希值减掉再加上新的，然后更新 set 里装的点，每次修改更新一下答案，然后就可以顺利 AC 了。
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<set>
#define N 1145
#define ull unsigned long long
using namespace std;
ull oh[N],base=131;//LZ love ohq 
void csh(){oh[0]=1;for(int i=1;i<N;i++)oh[i]=oh[i-1]*base;}
int n,m,q;
int a[N],ans[N],tot,siz[114514];
char s[N][105];
set<int>st[114514];
map<ull,int>mp;
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	csh();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)a[i]=a[i]*base+1ull*s[i][j];
		if(mp.find(a[i])==mp.end())mp[a[i]]=++tot;
		siz[mp[a[i]]]++;
		st[mp[a[i]]].insert(i);
	}
	for(int i=1;i<=n;i++)ans[i]=siz[mp[a[i]]];
	while(q--){
		int x,y,xx,yy;
		scanf("%d%d%d%d",&x,&y,&xx,&yy);
		if(s[x][y]==s[xx][yy])continue;
		if(x==xx){
			int old=mp[a[x]];
			siz[old]--;
			st[old].erase(x);
			a[x]+=(s[x][yy]-s[x][y])*oh[m-y];
			a[x]+=(s[x][y]-s[x][yy])*oh[m-yy];
			if(mp.find(a[x])==mp.end())mp[a[x]]=++tot;
			swap(s[x][y],s[xx][yy]);
			int nw=mp[a[x]];
			siz[nw]++;
			st[nw].insert(x);
			for(set<int>::iterator it=st[nw].begin();it!=st[nw].end();it++)ans[*it]=max(ans[*it],siz[nw]);
		}else{
			int old1=mp[a[x]],old2=mp[a[xx]],new1,new2;
			siz[old1]--;siz[old2]--;
			st[old1].erase(x);
			st[old2].erase(xx);
			a[x]+=(s[xx][yy]-s[x][y])*oh[m-y];
			if(mp.find(a[x])==mp.end())mp[a[x]]=++tot;
			new1=mp[a[x]];siz[new1]++;
			st[new1].insert(x);
			a[xx]+=(s[x][y]-s[xx][yy])*oh[m-yy];
			swap(s[x][y],s[xx][yy]);
			if(mp.find(a[xx])==mp.end())mp[a[xx]]=++tot;
			new2=mp[a[xx]];siz[new2]++;
			st[new2].insert(xx);
			for(set<int>::iterator it=st[new1].begin();it!=st[new1].end();it++)ans[*it]=max(ans[*it],siz[new1]);
			for(set<int>::iterator it=st[new2].begin();it!=st[new2].end();it++)ans[*it]=max(ans[*it],siz[new2]);		
		}
	}
	for(int i=1;i<=tot;i++){
		if(!siz[i])continue;
		for(set<int>::iterator it=st[i].begin();it!=st[i].end();it++)ans[*it]=max(ans[*it],siz[i]);
	}
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：kczno1 (赞：1)

把字符串$hash$了，一样的放在一起维护。


考虑每个串只在删除时或最后更新答案。


那么可以单调栈维护。


$O(mlogn)$


但我自信不会被卡，于是写的双向链表维护，每次暴力

$O(nm)$

(跑的飞快)


```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1000+5,L=100+5,M=1e5+5,T=N+M;
char s[N][L];

const int D=1e9+7,w=26;
ll mi[L],a[N];
map<int,int>dy;int tot;

int cnt[T],nex[T+N],pre[N],have[N],mx[N];
void push(int x)
{
    if(!dy.count(a[x]))dy[a[x]]=++tot;
    int i=dy[a[x]];
    int now=++cnt[i];
    for(int y=nex[N+i];have[y]<now;y=nex[y])have[y]=now;
    pre[nex[x]=nex[N+i]]=x;
    nex[pre[x]=N+i]=x;
    have[x]=now;
}
void del(int x)
{
    int i=dy[a[x]];
    --cnt[i];
    chmax(mx[x],have[x]);
    pre[nex[x]]=pre[x];
    nex[pre[x]]=nex[x];
}

int main()
{
    freopen("1.in","r",stdin);
    int n,l,m;
    cin>>n>>l>>m;
    mi[0]=1;
    rep(i,1,l)mi[i]=mi[i-1]*w%D;
    rep(i,1,n)
    {
        scanf("%s",s[i]+1);
        rep(j,1,l)(a[i]+=mi[j]*s[i][j])%=D;
    }
    have[0]=N;
    rep(i,1,n)push(i);
    while(m--)
    {
        int i1=read(),j1=read(),i2=read(),j2=read();
        if(i1==i2)
        {
            del(i1);
            a[i1]=(a[i1]+(s[i2][j2]-s[i1][j1])*mi[j1]%D+D)%D;
            a[i2]=(a[i2]+(s[i1][j1]-s[i2][j2])*mi[j2]%D+D)%D;
            swap(s[i1][j1],s[i2][j2]);
            push(i1);
            continue;
        }
        del(i1);del(i2);
        a[i1]=(a[i1]+(s[i2][j2]-s[i1][j1])*mi[j1]%D+D)%D;
        a[i2]=(a[i2]+(s[i1][j1]-s[i2][j2])*mi[j2]%D+D)%D;
        swap(s[i1][j1],s[i2][j2]);
        push(i1);push(i2);
    }
    rep(i,1,n)printf("%d\n",max(mx[i],have[i]));
}
```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑暴力做法。

观察到 $n \le 10^3,m \le 10^5$。对于每个字符串哈希，因为每次操作最多会影响到 $2$ 个字符串的哈希值，所以暴力维护是 $O(nm)$ 的。维护答案的话直接用 map 会多一个 $\log$，是无法接受的。但是对每个哈希值离散化一下，每次操作将新的哈希值放到 map 里去找离散化之后的值，这样维护哈希值是 $O(m \log V)$ 的。然后就能过了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
    il int read(){
        int x=0,f=1;char ch=gc;
        while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
        while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
        return x*f;
    }
    il int qmi(int a,int b,int p){
        int ans=1;
        while(b){
            if(b&1) ans=ans*a%p;
            a=a*a%p,b>>=1;
        }
        return ans;
    }
    il auto max(auto a,auto b){return (a>b?a:b);}
    il auto min(auto a,auto b){return (a<b?a:b);}
    il int gcd(int a,int b){
        if(!b) return a;
        return gcd(b,a%b);
    }
    il int lcm(int a,int b){
        return a/gcd(a,b)*b;
    }
    il void exgcd(int a,int b,int &x,int &y){
        if(!b) return x=1,y=0,void(0);
        exgcd(b,a%b,x,y);
        int t=x;
        x=y,y=t-a/b*x;
        return ;
    }
    mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e4+10,M=105,K=1e5+5;
int n,l,m;
char s[N][M];
int B=12347;
int hs[N],Max[N];
unordered_map<int,int> c;
int cnt,Cnt[K<<1],id[N];

il int get(int x){
    if(!c.count(x)) return c[x]=++cnt;
    return c[x];
}

il void solve(){
    n=rd,l=rd,m=rd;
    for(re int i=1;i<=n;++i){
        scanf("%s",s[i]+1);
        for(re int j=1;j<=l;++j) hs[i]=hs[i]*B+(s[i][j]-'a'+1);
        ++Cnt[get(hs[i])],id[i]=get(hs[i]);
    }
    for(re int i=1;i<=n;++i) Max[i]=Cnt[id[i]];
    while(m--){
        int a=rd,x1=rd,b=rd,x2=rd;
        --Cnt[id[a]];
        if(a!=b) --Cnt[id[b]];
        hs[a]=hs[b]=0;
        swap(s[a][x1],s[b][x2]);
        for(re int j=1;j<=l;++j) hs[a]=hs[a]*B+(s[a][j]-'a'+1);
        if(a!=b) for(re int j=1;j<=l;++j) hs[b]=hs[b]*B+(s[b][j]-'a'+1);
        id[a]=get(hs[a]),id[b]=get(hs[b]);
        ++Cnt[id[a]];
        if(a!=b) ++Cnt[id[b]];
        for(re int i=1;i<=n;++i) Max[i]=max(Max[i],Cnt[id[i]]);
    }
    for(re int i=1;i<=n;++i) printf("%lld\n",Max[i]);
    return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    int t=1;while(t--)
    solve();
    return 0;
}
```

---

## 作者：Baikaisama (赞：0)

观察数据范围 $n\le10^5$，$m\le10^3$，$nm$ 不过也才 $10^8$，也就是每次询问后还有 $n$ 的复杂度给我们跑。

整体思路是：先预处理出每个串的哈希，因为在交换的同时只会对修改前相同和修改后相同有影响，而答案求历史最值，于是我们只用暴力跑一遍 $n$ 来处理相等的就行，最后再输出答案。

接下来的问题是：怎么在 $O(1)$ 复杂度判相等和修改节点，容易想到用哈希。

众所周知，哈希便利于字符串的修改和匹配，对于本题：给每个字符串建个 哈希，令字符串 $Str$，可以得到他的哈希 $Hash=Base^{(Len-1)}\times Str_1+Base^{(Len-2)}\times Str_2+...+\times Base^{0}\times Str_{Len}$（普通的线性哈希）。

接下来考虑修改：

若要修改其中第 $x$ 项，将 $Str_x$ 修改为 $Ch$，哈希会如何变化？在哈希上的体现就是：先减去了 $x$ 这个位置的 $Str_x$ 的哈希，再加上 $Ch$ 在 $x$ 位置上的的哈希，也就是减去 $Base^{Len-x}\times Str_x$ 再加上 $Base^{Len-x}\times Ch$ ，简化为 $Base^{Len-x}\times(Ch-Str_x)$。

这道题自然溢出也问题不大，写的时候注意常数，稍微大点可能会超时几个点。

细节看代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, Q;
const int Base=27;
long long Basep[110];
int Str[1010][110];
int tmp[1010];
long long Hash[1010];
int ans[1010];
void Find(int Tar)//找相同以及更新其影响的串
{
	int Cnt=0;
	for(int i=1;i<=n;i++)
		if(Hash[i]==Hash[Tar])
			tmp[++Cnt]=i;
	for(int i=1;i<=Cnt;i++)
		ans[tmp[i]]=max(ans[tmp[i]], Cnt);
}
signed main()
{
	scanf("%d%d%d", &n, &m, &Q);
	Basep[0]=1;
	for(int i=1;i<=m;i++)
		Basep[i]=Basep[i-1]*Base;
	for(int i=1;i<=n;i++)
	{
		getchar();
		for(int j=1;j<=m;j++)
			Hash[i]=Hash[i]*Base+(Str[i][j]=getchar()&31);//得到哈希
	}
	for(int i=1;i<=n;i++)
		Find(i);//开始状态也得考虑
	for(register int i=1;i<=Q;i++)
	{
		int x, y, z, t;
		scanf("%d%d%d%d", &x, &y, &z, &t);
		Hash[x]+=Basep[m-y]*(Str[z][t]-Str[x][y]);
		Hash[z]+=Basep[m-t]*(Str[x][y]-Str[z][t]);//更新交换的哈希
		int tp=Str[x][y];
		Str[x][y]=Str[z][t];
		Str[z][t]=tp;//交换（用swap会超，常数暴大）
		Find(x), Find(z);//更新ans
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：Themooncake (赞：0)

# 一、题目大意
给定 $n$ 个长度为 $m$ 的字符串，有 $q$ 次操作，每次操作会交换第 $x$ 个字符串的第 $y$ 位和第 $z$ 个字符串的第 $t$ 位（注意， $x$ 可以和 $z$ 相等），问在这 $q$ 次操作过程中对于每个字符串最多有多少个字符串和它相等（包括它自己）。
# 二、题目分析
对于统计有多少个串和某个串相同的问题，有一个很经典的思路就是把这些字符串全部塞到桶里然后把值取过来，这一步可以（hash 后，也可以不 hash，用 STL 库自带的）用 map 或者 unordered_map 实现。所以考虑怎么动态维护这一过程。

初步设想，我们可以维护每一个字符串当前的个数 $cnt$ 以及其历史最大值 $hcnt$。但很快我们就会发现问题：设第 $x$ 个字符串在第 $i$ 次操作后从 $s$ 变成了 $s'$，$hcnt_{s'}$ 在第 $j$ 次操作后产生。倘若 $i>j$，且 $cnt_{s'}<hcnt_{s'}$，就会导致第 $x$ 个字符串的答案偏大。根据上面的分析，可以发现，如果我们能知道**某一个时间段**的最大值，这个问题也就迎刃而解了。所以，我们可以以**时间戳**为下标，使用动态开点线段树来维护每一个字符串的 $cnt$，同时维护每个字符串的变化时间，每次变化的同时更新答案。
# 三、Code
部分细节已在注释中写出。

代码中可以先哈希了再压到 map 里，不过无伤大雅。
```
#include<bits/stdc++.h>
#define LL long long
/*
#include<bits/stdc++.h>
#define LL long long
/*
	动态开点线段树 给每个串维护一个以时间戳为下标的最大值线段树
	并给每一个字符串一个记录修改成当前状态时时间戳的标记 用于查询区间内最大值 
*/
using std::cin;
using std::cout;
using std::max;
using std::string;
const int N=1e5+5;
std::unordered_map<string,int>cnt,root;//桶、根节点的位置 
int n,m,Q,pcnt,ans[1005],stmp[1005];
string s[1005];
struct node{
	int lson,rson,mx;
};
node tree[N*80];//动态开点线段树
#define ls(rt) tree[(rt)].lson
#define rs(rt) tree[(rt)].rson
void update(int rt){tree[rt].mx=max(tree[ls(rt)].mx,tree[rs(rt)].mx);}
int modify(int rt,int l,int r,int tar,int x)
{
	if(l>tar||r<tar)
		return rt;
	if(!rt)
		rt=++pcnt;
	if(l==r)
	{
		tree[rt].mx=x;
		return rt;
	}
	int mid=l+r>>1;
	ls(rt)=modify(ls(rt),l,mid,tar,x);
	rs(rt)=modify(rs(rt),mid+1,r,tar,x);
	update(rt);
	return rt;
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L||!rt)
		return 0;
	if(L<=l&&r<=R)
		return tree[rt].mx;
	int mid=l+r>>1;
	int tmpL=query(ls(rt),l,mid,L,R);
	int tmpR=query(rs(rt),mid+1,r,L,R);
	return max(tmpL,tmpR);
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>Q;
	for(int i=1;i<=n;++i)
	{
		cin>>s[i];
		++cnt[s[i]];
	}
	for(int i=1;i<=n;++i)
	{
		ans[i]=cnt[s[i]];
		root[s[i]]=modify(root[s[i]],0,Q,0,cnt[s[i]]);//最开始认为时间戳为 0 
	}
	for(int i=1,x,y,z,t;i<=Q;++i)
	{
		cin>>x>>y>>z>>t;
		--y,--t;
		if(x==z)//注意可以时一个串内交换 只算一次 
		{
			--cnt[s[x]];
			int tmp=query(root[s[x]],0,Q,stmp[x],i);//更新在变成某个字符串时的历史最值 
			ans[x]=max(ans[x],tmp);
			std::swap(s[x][y],s[z][t]);
			++cnt[s[x]];
			root[s[x]]=modify(root[s[x]],0,Q,i,cnt[s[x]]);
			stmp[x]=i;
		}
		else
		{
			--cnt[s[x]],--cnt[s[z]];
			int tmp1=query(root[s[x]],0,Q,stmp[x],i);
			int tmp2=query(root[s[z]],0,Q,stmp[z],i);
			ans[x]=max(ans[x],tmp1);
			ans[z]=max(ans[z],tmp2);
			std::swap(s[x][y],s[z][t]);
			++cnt[s[x]],++cnt[s[z]];
			root[s[x]]=modify(root[s[x]],0,Q,i,cnt[s[x]]);
			stmp[x]=i;
			root[s[z]]=modify(root[s[z]],0,Q,i,cnt[s[z]]);
			stmp[z]=i;
		}
	}
	for(int i=1;i<=n;++i)//注意最后还得再算一次，类似尾判 
	{
		int tmp=query(root[s[i]],0,Q,stmp[i],Q);
		ans[i]=max(ans[i],tmp);
		cout<<ans[i]<<"\n";
	}
}
```
# 四、其他
其实根据数据范围，$O(nq)$ 也是可以卡过去的，但笔者常数写不过去，被迫写了棵树~~每天一棵树有益身心健康~~。

---

## 作者：Kelvin2009 (赞：0)

这题直接哈希即可。

每次修改时同时更新各个哈希串的出现次数，再更新一下该时点上与各串相同的最多的字符串个数。

可以有两个剪枝。

如果两个换的字符相同，直接跳掉（无意义）。

在更新各串最大值时，只有与新改完的串相同（即哈希值相同时）才更新，否则跳掉。

题目不卡哈希，自然溢出即可。

保险的话可以取个模（用个特定的不太常见的模数），再就是用孪生素数双哈希。


---

代码：


---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int range=1005;
const int tem_ran=105;
const long long base=27;
map<long long,int>ma;
char c[range][tem_ran];
int n,m,q,x,y,z,t,maxn[range];
long long pai1[tem_ran],hush1[range];
int main()
{
	pai1[0]=1ll;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) pai1[i]=pai1[i-1]*base;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> c[i][j];
			c[i][j]=c[i][j]-'a'+1;
			hush1[i]=hush1[i]*base+c[i][j];
		}
		ma[hush1[i]]++;
	}
	for(int i=1;i<=n;i++) maxn[i]=ma[hush1[i]];
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d%d",&x,&y,&z,&t);
		if(c[z][t]==c[x][y]) continue;
		ma[hush1[x]]--,ma[hush1[z]]--;
		if(x==z) ma[hush1[x]]++;
		hush1[x]=hush1[x]+(c[z][t]-c[x][y])*pai1[m-y];
		hush1[z]=hush1[z]+(c[x][y]-c[z][t])*pai1[m-t];
		swap(c[x][y],c[z][t]);
		ma[hush1[x]]++,ma[hush1[z]]++;
		if(x==z) ma[hush1[x]]--;
		for(int j=1;j<=n;j++) if(hush1[j]==hush1[x] || hush1[j]==hush1[z]) maxn[j]=max(maxn[j],ma[hush1[j]]);
	}
	for(int i=1;i<=n;i++) printf("%d\n",maxn[i]);
	return 0;
}
```

---

## 作者：钰瑾_恋涵 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P3471)

#### 题目大意：

给定 $n$ 个字符串，有 $m$ 次操作，每次操作从所有字符串中选择任意两个不同的字符并交换，求每个字符串在任意时刻，当前字符串数量的最大值。

#### 思路：

先将字符串离散化，hash，map 都可以，如果觉得 map 多一个 $\log$ 比较慢，也可以用 unordered_map。一个字符串的数量增加时更新这个字符串集合中所有下标的最大值，这一操作可以用动态开点线段树或平衡树~~轻松~~实现。

本蒟蒻动态开点线段树莫名 WA，无奈之下只能用 fhq_treap，思路简单，实现简单，码量也少得多。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;		
i64 read() {
	i64 x(0), f(0); char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
int __stk[128], __len;
void put(i64 x) {
	if (x < 0) putchar('-'), x = -x;
	do { __stk[++__len] = x % 10, x /= 10; } while (x);
	while (__len) putchar(__stk[__len--] ^ 48);
}		
const int N = 2.5e5;
int n, l, m, cnt, id[N], root[N], ans[N];
string s[N];
unordered_map<string, int> mp;
inline int get(string x) { return mp.find(x) == mp.end() ? (mp[x] = ++cnt) : mp[x]; }
namespace FHQ {
	#define ls(x) t[x].ls
	#define rs(x) t[x].rs
	int num, a, b, c;
	struct node {
		int ls, rs, siz, id, tag, rnd;
	}t[N];
	inline int New(int x) { return ++num, ls(num) = rs(num) = t[num].tag = 0, t[num].siz = 1, t[num].id = x, t[num].rnd = rand(), num; }
	inline void pushup(int x) { t[x].siz = t[ls(x)].siz + t[rs(x)].siz + 1; }
	inline void update(int x, int k) { if (x) ans[t[x].id] = max(ans[t[x].id], k), t[x].tag = max(t[x].tag, k); }
	inline void pushdown(int x) { if (t[x].tag) update(ls(x), t[x].tag), update(rs(x), t[x].tag), t[x].tag = 0; } 
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].rnd < t[y].rnd) return pushdown(x), rs(x) = merge(rs(x), y), pushup(x), x;
		return pushdown(y), ls(y) = merge(x, ls(y)), pushup(y), y;
	}
	void split(int x, int k, int &a, int &b) {
		if (!x) return a = b = 0, void ();
		pushdown(x);
		if (t[x].id <= k) a = x, split(rs(x), k, rs(x), b);
		else b = x, split(ls(x), k, a, ls(x));
		pushup(x);
	}
	inline void insert(int &rt, int x) { split(rt, x - 1, a, c), b = New(x), rt = merge(merge(a, b), c), update(rt, t[rt].siz); }
	inline void remove(int &rt, int x) { split(rt, x, a, c), split(a, x - 1, a, b), rt = merge(a, c); }
}
signed main() {
	srand(114514);
	n = read(), l = read(), m = read(); 
	for (int i = 1; i <= n; ++i) cin >> s[i], id[i] = get(s[i]), FHQ::insert(root[id[i]], i);
	while (m--) {
		int x = read(), p1 = read() - 1;
		int y = read(), p2 = read() - 1;
		FHQ::remove(root[id[x]], x);
		if (x != y) FHQ::remove(root[id[y]], y);
		swap(s[x][p1], s[y][p2]);
		id[x] = get(s[x]), id[y] = get(s[y]);
		FHQ::insert(root[id[x]], x);
		if (x != y) FHQ::insert(root[id[y]], y);
	}
	for (int i = 1; i <= n; ++i) FHQ::remove(root[id[i]], i);
	for (int i = 1; i <= n; ++i) put(ans[i]), putchar('\n');
	return 0;
}
```


---

