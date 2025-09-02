# T-Shirts

## 题目描述

The big consignment of t-shirts goes on sale in the shop before the beginning of the spring. In all $ n $ types of t-shirts go on sale. The t-shirt of the $ i $ -th type has two integer parameters — $ c_{i} $ and $ q_{i} $ , where $ c_{i} $ — is the price of the $ i $ -th type t-shirt, $ q_{i} $ — is the quality of the $ i $ -th type t-shirt. It should be assumed that the unlimited number of t-shirts of each type goes on sale in the shop, but in general the quality is not concerned with the price.

As predicted, $ k $ customers will come to the shop within the next month, the $ j $ -th customer will get ready to spend up to $ b_{j} $ on buying t-shirts.

All customers have the same strategy. First of all, the customer wants to buy the maximum possible number of the highest quality t-shirts, then to buy the maximum possible number of the highest quality t-shirts from residuary t-shirts and so on. At the same time among several same quality t-shirts the customer will buy one that is cheaper. The customers don't like the same t-shirts, so each customer will not buy more than one t-shirt of one type.

Determine the number of t-shirts which each customer will buy, if they use the described strategy. All customers act independently from each other, and the purchase of one does not affect the purchase of another.

## 说明/提示

In the first example the first customer will buy the t-shirt of the second type, then the t-shirt of the first type. He will spend 10 and will not be able to buy the t-shirt of the third type because it costs 4, and the customer will owe only 3. The second customer will buy all three t-shirts (at first, the t-shirt of the second type, then the t-shirt of the first type, and then the t-shirt of the third type). He will spend all money on it.

## 样例 #1

### 输入

```
3
7 5
3 5
4 3
2
13 14
```

### 输出

```
2 3 
```

## 样例 #2

### 输入

```
2
100 500
50 499
4
50 200 150 100
```

### 输出

```
1 2 2 1 
```

# 题解

## 作者：tzc_wk (赞：34)

[题面传送门](https://codeforces.ml/contest/702/problem/F)

首先肯定将所有物品排个序。

考虑暴力做法，对于每个询问，枚举所有物品，能买就买。不过扫一眼就知道无法直接优化。

不妨换个角度，暴力做法是枚举询问，这次我们枚举物品。从左到右依次枚举所有物品，将所有买得起当前物品的询问答案 $+1$，钱数减去当前物品的价格。这样就貌似与 DS 能够搭得上边了。

于是题目变为：$n$ 次操作，每次操作将序列所有值 $\geq c$ 的数减去 $c$，问每个数被操作了几次。

可还是不好维护啊，平衡树 split 出 $\geq c$ 的数后你还是要暴力修改啊。
这时候我们就需要用到一种奇淫技巧，学名“势能分析”（咋感觉像物理内容啊qwq）

我们将原序列 split 成三个部分，$[1,c),[c,2c),[2c,\infty)$，显然，第一部分不会被操作，第三部分被操作后相对位置不会发生变化，因此我们只需暴力修改第二部分。

你可能会直觉地认为这样子优化没啥卵用，其实这样做复杂度反倒是对的。

这样看似不起眼的优化为什么就把不可能变成可能了呢？

注意到，我们暴力修改的数都在 $[c,2c)$ 中，也就是修改完之后，原数至多变为原来的一半。也就是说每个数最多被修改 $\log c_i$ 次，总复杂度线性对数方，可以通过时限。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e5+5;
int Rand(){return rand()<<15|rand();}
int n,m,ans[MAXN+5];
struct event{int c,q;} a[MAXN+5];
bool cmp(event x,event y){if(x.q!=y.q) return x.q>y.q;return x.c<y.c;}
struct node{
	int ch[2],id,val,key,cntlz,minlz,cnt;
} s[MAXN+5];
int ncnt=0,rt=0;
void pushdown(int k){
	if(s[k].minlz){
		if(s[k].ch[0]) s[s[k].ch[0]].minlz+=s[k].minlz,s[s[k].ch[0]].val-=s[k].minlz;
		if(s[k].ch[1]) s[s[k].ch[1]].minlz+=s[k].minlz,s[s[k].ch[1]].val-=s[k].minlz;
		s[k].minlz=0;
	} if(s[k].cntlz){
		if(s[k].ch[0]) s[s[k].ch[0]].cntlz+=s[k].cntlz,s[s[k].ch[0]].cnt+=s[k].cntlz;
		if(s[k].ch[1]) s[s[k].ch[1]].cntlz+=s[k].cntlz,s[s[k].ch[1]].cnt+=s[k].cntlz;
		s[k].cntlz=0;
	}
}
void split(int k,int val,int &a,int &b){
	if(!k){a=b=0;return;} pushdown(k);
	if(s[k].val<=val) a=k,split(s[k].ch[1],val,s[k].ch[1],b);
	else b=k,split(s[k].ch[0],val,a,s[k].ch[0]);
}
int merge(int x,int y){
	if(!x||!y) return x|y;pushdown(x);pushdown(y);
	if(s[x].key<s[y].key) return s[x].ch[1]=merge(s[x].ch[1],y),x;
	else return s[y].ch[0]=merge(x,s[y].ch[0]),y;
}
void dfsins(int x,int &y,int z){//insert all nodes in subtree x into subtree y, val-=z
	if(!x) return;pushdown(x);
	dfsins(s[x].ch[0],y,z);dfsins(s[x].ch[1],y,z);
	s[x].ch[0]=s[x].ch[1]=0;s[x].val-=z;s[x].cnt++;
	int k1,k2;split(y,s[x].val,k1,k2);y=merge(merge(k1,x),k2);
}
void insert(int x,int id){
	int k1,k2;split(rt,x,k1,k2);
	ncnt++;s[ncnt].id=id;s[ncnt].key=Rand();s[ncnt].val=x;
	rt=merge(merge(k1,ncnt),k2);
}
void dfscalc(int x){
	if(!x) return;pushdown(x);
	ans[s[x].id]=s[x].cnt;dfscalc(s[x].ch[0]);dfscalc(s[x].ch[1]);
}
int main(){
	srand(19260817);scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].c,&a[i].q);
	sort(a+1,a+n+1,cmp);scanf("%d",&m);
	for(int i=1;i<=m;i++){int x;scanf("%d",&x);insert(x,i);}
	for(int i=1;i<=n;i++){
		int k1,k2,k3;split(rt,a[i].c-1,k1,k2);split(k2,a[i].c<<1,k2,k3);
		if(k3){s[k3].val-=a[i].c;s[k3].cnt++;s[k3].minlz+=a[i].c;s[k3].cntlz++;}
		dfsins(k2,k1,a[i].c);rt=merge(k1,k3);
	}
	for(int i=1;i<=m;i++) ans[s[i].id]=s[i].cnt;
	dfscalc(rt);for(int i=1;i<=m;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：27)

## 题目大意

有 $n$ 种物品，每种物品有一个价格 $c_i$ 和品质 $q_i$ 。有 $k$ 个人，每个人手里有 $q_i$ 的钱，每个人会优先买能够支付的，品质最高的物品。每人只能买一件物品 **一次** ，但是一件物品可以被买的次数不限，即每个人之间是独立的。求每个人买的物品件数。

## 解题思路

如果分别处理每个人，贪心将物品按照 $q_i$ 从大到小排序，若相同则 $c_i$ 小的在前，每次查询扫一遍整个区间，能买则买，最后得出件数。这样的做法的时间复杂度是 $O(max\{k,\log_2 n\}\times n)$ 的，无法优化。

但是，如果我们换一个角度处理问题，维护每个人手里的钱的数量， **按照上面描述的排序方式** ，依次处理每个物品，即：

设当前处理的是物品 $i$ ，

对于一个人，若其手中的钱数大于等于 $c_i$ ，则需购买这件物品，将手中的钱数减去 $c_i$ ，将答案计数器增加 $1$ 即可。

若其手中的钱数小于 $c_i$ ，则不购买这件物品，不做任何修改。

一个 $O(max\{k,\log_2 n\}\times n)$ 的代码实现：

```cpp
for(int i=1;i<=k;i++)scanf("%d",q+i),id[i]=i;
sort(id+1,id+k+1);
for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)
if(q[id[j]]>=s[i].c)q[id[j]]-=s[i].c,ans[id[j]]++;
for(int i=1;i<=k;i++)printf("%d ",ans[i]);
printf("\n");
```

考虑用数据结构维护每个人手中的钱数，优化时间复杂度。

若每个人手中的钱数是有序的，每次操作只需要将大于等于 $c_i$ 的值（连续的，靠右的一段）减去 $c_i$ 并使答案计数器增加 $1$ 即可。

可以用 **平衡树** 来维护这些值并 **打标记** 做区间修改。

但是，人手中的钱数减去 $c_i$ 后可能会导致重复，即不能保证平衡树二叉搜索树的性质，也无法完成 FHQ 的合并操作（合并两个 FHQ Treap 需要保证一个子树中的最大值小于另一个子树中的最小值），怎么办呢？

方法是，对于有重复的部分，一个一个地暴力插入；不重复的部分，打标记即可。

直觉地认为这肯定会超时，但是如果一个人手中的钱数（不妨设为 $x$ ）需要被暴力插入，其需要满足：

$\because c_i\le x< 2c_i$

$\therefore c_i>\frac x 2$

观察到每次暴力插入的话人手中的钱数是会减去 $c_i$ 的，因为 $c_i$ 大于 $x$ 的一半，所以每次暴力插入时都使 $x$ 至少减少了一半，所以对于一个有 $q_i$ 块钱的人来说其最多会被暴力插入 $O(\log_2 q_i)$ 次，所以可以保证总的时间复杂度为 $O((n+\sum \log_2 q_i)\log_2 n) $ ，在四秒的时限内可以通过此题。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue> 
using namespace std;
const int maxn=200010;
int n,k,q;
struct FHQ
{
    int rt,cnt,lc[maxn],rc[maxn],siz[maxn],pri[maxn],val[maxn];
	int sum[maxn],tag[maxn],minu[maxn];
    void print(int o)
    {
        if(!o)return;
        pushdown(o);
        print(lc[o]);
        //printf("%d ",val[o]);
        print(rc[o]);
    }
    void maintain(int o){siz[o]=siz[lc[o]]+siz[rc[o]]+1;}
    void pushdown(int o)
    {
    	if(tag[o])
    	{
    		if(lc[o])tag[lc[o]]+=tag[o],sum[lc[o]]+=tag[o];
			if(rc[o])tag[rc[o]]+=tag[o],sum[rc[o]]+=tag[o];
			tag[o]=0; 
		}
		if(minu[o])
		{
			if(lc[o])minu[lc[o]]+=minu[o],val[lc[o]]-=minu[o];
			if(rc[o])minu[rc[o]]+=minu[o],val[rc[o]]-=minu[o];
			minu[o]=0;
		}
	}
    int merge(int x,int y)
    {
        if(x==0||y==0)return x+y;
        pushdown(x);pushdown(y);
        maintain(x);maintain(y);
        if(pri[x]<pri[y])
        {
            rc[x]=merge(rc[x],y);
            maintain(x);return x;
        }
        else
        {
            lc[y]=merge(x,lc[y]);
            maintain(y);return y;
        }
    }
    void split_val(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        pushdown(o); 
        if(val[o]<=k)x=o,split_val(rc[o],k,rc[o],y);
        else y=o,split_val(lc[o],k,x,lc[o]);
        maintain(o);
    }
    void split_siz(int o,int k,int&x,int&y)
    {
        if(!o){x=y=0;return;}
        pushdown(o);
        if(siz[lc[o]]>=k)y=o,split_siz(lc[o],k,x,lc[o]);
        else x=o,split_siz(rc[o],k-siz[lc[o]]-1,rc[o],y);
        maintain(o);
    }
    int newnode(int v)
    {
        cnt++;
        lc[cnt]=rc[cnt]=0;
        val[cnt]=v;
        siz[cnt]=1;
        pri[cnt]=rand();
        tag[cnt]=sum[cnt]=0;
        minu[cnt]=0;
        return cnt;
    }
}st;
struct node
{
	int c,q;
	bool operator<(node x)const{if(q==x.q)return c<x.c;return q>x.q;}
}s[maxn];
//int q[maxn],id[maxn],ans[maxn];
queue<int>Q;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&s[i].c,&s[i].q);
	sort(s+1,s+n+1);
	scanf("%d",&k);
	/*
	for(int i=1;i<=k;i++)scanf("%d",q+i),id[i]=i;
	sort(id+1,id+k+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)
	if(q[id[j]]>=s[i].c)q[id[j]]-=s[i].c,ans[id[j]]++;
	for(int i=1;i<=k;i++)printf("%d ",ans[i]);
	printf("\n");
	*/
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&q);
		int x,y;
		st.split_val(st.rt,q,x,y);
		st.rt=st.merge(st.merge(x,st.newnode(q)),y); 
	}
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		st.split_val(st.rt,s[i].c-1,x,y);
		st.split_val(y,s[i].c+s[i].c-1,y,z);
		st.minu[z]+=s[i].c;st.val[z]-=s[i].c;
		st.tag[z]++;st.sum[z]++;
		while(!Q.empty())Q.pop();
		Q.push(y);
		while(!Q.empty())
		{
			int t=Q.front();Q.pop();
			st.pushdown(t);
			if(st.lc[t])Q.push(st.lc[t]);
			if(st.rc[t])Q.push(st.rc[t]);
			int a,b;
			st.split_val(x,st.val[t]-s[i].c,a,b);
			st.lc[t]=st.rc[t]=0;
			st.val[t]-=s[i].c;
			st.siz[t]=1;
			st.tag[t]=0;
			st.sum[t]++;
			st.minu[t]=0;
			x=st.merge(st.merge(a,t),b); 
		}
		st.rt=st.merge(x,z);
	}
	st.print(st.rt);
	for(int i=1;i<=k;i++)printf("%d\n",st.sum[i]);
	return 0;
}
```

## 几点注意

1.本题要维护两个标记，钱数的减少量 $minu$ 和答案计数器的增加量 $tag$ 。

2.无论何时都要记得下传标记！（包括暴力插入时）

3.我的代码实现中，结点 $x$ 代表第 $x$ 个人，这种写法在暴力合并前需要重置结点信息；如果您的写法是每次新建一个结点，记得保存每个结点的归属，即其表示哪一个人。

4.在输出结果前，需要全部下传一次标记（我被坑了一次）。

5.网上一些题解说本题用可持久化平衡树求解，其实就只是 FHQ  Treap 而已，只是当时并没有一个统一的叫法，而这种平衡树被用来实现可持久化罢了。

---

## 作者：ღꦿ࿐ (赞：23)

先将所有 T-shirts 按照品质和价格排序，接下来问题变为 $m$ 次询问给出初始值 $b$，对于 $i\in [1,n]$，依次执行：如果 $b \geq c$ 执行 $p \gets b -c$，值域较大，可能需要使用一些经典的折半技巧。

## 做法 1，离线 $O(n\log n\log w)$

考虑离线，将所有人按拥有的钱升序排序，依次枚举所有 T-shirts，买了这件 T-shirt 的人一定是一个后缀，买了这件 T-shirt 的人可能会因为钱变少而发生了人之间顺序的改变，我们把这个改变的形态写出来：

- 所有 $b \in [0,c)$，不改变。

- 所有 $b \in [c,+\infty)$，$b\gets b-c$。

两个人钱之间相对顺序的改变仅当一个人在 $[0,c)$ 中，而另一个人原本在 $[0,2c)$ 中，而此时后者的钱会减少 $c$，也就是说至少减去了一半，这意味着这种相对顺序的改变最多发生 $O(n\log w)$ 次，所以我们可以暴力进行这种相对顺序的改变。

使用平衡树维护所有人之间的钱的顺序，每次将平衡树分成三部分，$[0,c)$ 不改变，$[c,2c)$ 直接暴力减去 $c$ 插入到 $[0,c)$ 之间，$[2c,+\infty)$ 直接打上 $-c$ 的标记。

时间复杂度 $O(n\log n \log w)$。

## 做法 2，在线 $O(n\log n\log w)$

对于大于 $x$ 减 $x$ 的问题往往可以考虑值域分层的思想，将值域按照 $[2^{E},2^{E+1})$ 分成 $\log w$ 层次，因为我们直接模拟的话会浪费大量的时间在减去较小的 $c_i$ 上，因此我们考虑将很小的 $c_i$ 一起考虑。对于目前的 $b$ 所在的层 $E$，我们将 $\lceil\log_2 c_i\rceil < E$ （层更低）的物品一起考虑，并试图快速地跳过这些物品。

如果在继续枚举 $i$ 的过程中发生了以下两种情况之一，那么 $b$ 一定会进入到更低的层中：

-  出现了一个层比 $E$ 更低的 $c_i$ 满足 $b<c_i$。

- 出现了一个层也为 $E$ 的 $c_i$ 满足 $b\geq c_i$。

前者显然成立，后者因为 $b$ 和 $c_i$ 在同层，$b\gets b-c_i$ 后新的 $b$ 的最高位一定减去了，所以一定去到了 $E$ 更低的层。

出去这两种情况，就只剩下出现了一个层级更低切 $b\geq c_i$ 的 $c_i$ 的情况。

对于目前的位置 $l$，我们可以二分之后第一个出现的上方两种情况的位置 $p$，这说明我们完整的减去了所有 $[l,p)$ 内的层比 $E$ 更低的 $c_i$，可以直接减去。

因为在经过了 $p$ 位置后一定会进入更低的层，所以总共只需寻找 $O(\log w)$ 次这样的 $p$ 并手动处理。

使用线段树维护区间内低于每个层级的 $c_i$ 的和，以确定能否满足对于该区间内的低于 $E$ 层的 $a_i$ 都可以被减去。

同时也维护每个层级内不会减去一个同层的 $c_i$ 的 $b$ 的最大界，以确定是否会在该区间内减去一个同层的 $c_i$，由于不可能减去两次同层的数，该信息的维护是简单的。

在维护这些信息后容易把该二分丢到线段树上，调整信息合并的方式后也可以选择直接 ST 表二分，但是 ST 表二分的空间 2log 的，不太可取。

信息合并的方式与二分的过程可能有些细节，可以参考[我的代码](https://codeforces.com/contest/702/submission/244765775)。

该做法时间复杂度 $O(n\log n\log w)$，常数很小。

这种值域分层的思想将在 CF1515I、P8522 中得到更进一步的运用。

## 做法 3，在线 $O(n(\log n+\log w))$

该做法由李欣隆老师在 WC2024 时讲述。

考虑直接回归最朴素的暴力，就直接 $O(nw)$ 地 dp：$f_{i,j}$ 表示从第 $i$ 个位置开始，$j$ 块钱买了几件 T-shirts，显然有转移 :

$$

f_{i,j}=f_{i+1,j} (j< c_i)


$$

$$

f_{i,j}=f_{i+1,j-{c_i}}+1 (j\geq c_i)
$$

也就是说对于 $f_{i}$ 数组，从 $i+1$ 到 $i$ 的改变就是前面的某一段复制，区间加一后拼接到后面，直接使用可持久化平衡树自拼接的技巧*可以做到 $O(n(\log n+\log w))$。

*：其实就是路径复制，像正常地平衡树拼接序列一样，复制自己的之后将合并路径上的节点复制作为新的，没有改变的儿子继续指向原本的即可。


---

## 作者：slgdsxw (赞：10)

不会fhq的小蒟蒻试图用splay解决这道题，来讲一下splay的维护方法。

这道题的思路比较清晰：按人手中的钱数维护平衡树，将物品按品质排序后依次让人买，设当前物品价格为 $x$ ，即将钱数分为 $[0,x) [x,2x) [2x,inf) $ 三部分，对中间部分暴力删除再插入，右半部分打标记维护。

考虑用splay来分离区间的话需要找到 $x$ 的前驱点 $u$， $2x-1$ 的后继点 $v$ ，为了避免过多讨论，插入-inf 值保证 $u$ 存在，而对于 $v$ 讨论：

1. $v$ 存在，将 $u$ 旋至根, $v$ 旋至 $u$ 的右儿子，则 $v$ 的左子树就是需要暴力删除再插入的部分，$v$ 和 $v$ 的右子树是要打标记的部分
1. $v$ 不存在，说明没有人的钱数大于等于 $2x$ ，将 $u$ 旋至根后，钱数小于 $x$ 的点位于 $u$ 和 $u$ 的左子树，对 $u$ 的右子树重新插入。

从程序效率角度可以做以下优化：

1. 重复利用被删除的点，空间复杂度降至线性，由于内存命中率的提高运行速度也得到提升。
1. 对排序后的物品的价格做整体最小值或后缀最小值，当钱数小于价格最小值时无需再插入树中。

关于下传标记：从上至下访问树的结构时必须下传，以防万一的话可以在点向上旋转之前下传标记。最后输出答案前要下传所有的标记。

代码如下(fhq&splay) , splay的解法目前是你谷最优解：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define LL long long
using namespace std;
const int N=200005,inf=0x7fffffff;
int n,m,top,minc;
int num[N];
struct shirt
{
	int ci,qi;
}a[N];
bool operator < (const shirt x,const shirt y)
{
	if(x.qi!=y.qi)return x.qi>y.qi;
	return x.ci<y.ci;
}
int input()
{
	int x=0,F=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')F=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
	return x*F;
}
void print(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>=10)print(x/10);
	putchar(x%10+'0');
}
struct fhq
{
	int rt,tot;
	int val[N],rnd[N],tag[N],ans[N],ch[N][2],pool[N],id[N];
	inline int random(){return rand()<<15|rand();}
	inline void cover(int u,int x,int y){if(u)tag[u]+=x,val[u]+=x,ans[u]+=y,num[id[u]]+=y;}
	inline void pushdown(int u){if(tag[u]!=0)cover(ch[u][0],tag[u],ans[u]),cover(ch[u][1],tag[u],ans[u]),tag[u]=ans[u]=0;}
	void split(int u,int k,int &x,int &y)// x <= k  y > k
	{
		if(!u){x=y=0;return;}
		pushdown(u);
		if(val[u]<=k)x=u,split(ch[u][1],k,ch[u][1],y);
		else y=u,split(ch[u][0],k,x,ch[u][0]);
	}
	int Merge(int u,int v)
	{
		if(!u||!v)return u|v;
		pushdown(u);pushdown(v);
		if(rnd[u]>rnd[v]){ch[u][1]=Merge(ch[u][1],v);return u;}
		else {ch[v][0]=Merge(u,ch[v][0]);return v;}
	}
	void ins(int x,int ID)
	{
		int l,r,u=pool[tot--];
		val[u]=x;rnd[u]=random();id[u]=ID;
		tag[u]=ans[u]=ch[u][0]=ch[u][1]=0;
		split(rt,x,l,r);
		rt=Merge(Merge(l,u),r);
	}
	void trans(int u,int x)
	{
		if(!u)return;
		pushdown(u);
		trans(ch[u][0],x);
		trans(ch[u][1],x);
		pool[++tot]=u;
		num[id[u]]++;
		if(val[u]-x>=minc)ins(val[u]-x,id[u]);
	}
	void dfs(int u)
	{
		if(!u)return;
		pushdown(u);dfs(ch[u][0]);dfs(ch[u][1]);
	}
	void solve()
	{
		int l,r,mid;
		tot=0;
		for(int i=1;i<=m;i++)pool[++tot]=i;
		for(register int i=1;i<=m;i++)ins(input(),i);
		for(register int i=1;i<=n;i++)
		{
			split(rt,(a[i].ci<<1)-1,l,r);
			split(l,a[i].ci-1,l,mid);
			if(r)cover(r,-a[i].ci,1);
			rt=Merge(l,r);
			trans(mid,a[i].ci);
		}
		dfs(rt);
		for(register int i=1;i<=m;i++)
		{
			print(num[i]);
			if(i<m)putchar(' ');
		}
	}
}tf;
struct Splay
{
	int rt,tot;
	int val[N],id[N],fa[N],ch[N][2],tag[N],ans[N],pool[N];
	inline void con(int u,int v,int w){fa[u]=v;ch[v][w]=u;}
	inline void cover(int u,int x,int y){if(u)tag[u]+=x,val[u]+=x,ans[u]+=y,num[id[u]]+=y;}
	inline void pushdown(int u){if(tag[u]!=0)cover(ch[u][0],tag[u],ans[u]),cover(ch[u][1],tag[u],ans[u]),tag[u]=ans[u]=0;}
	void rot(int u)
	{
		int v=fa[u],d=(u==ch[v][1]);
		con(u,fa[v],v==ch[fa[v]][1]);
		con(ch[u][d^1],v,d);
		con(v,u,d^1);
	}	
	void splay(int u,int v)
	{
		pushdown(u);
		while(fa[u]!=v)
		{
			int f1=fa[u],f2=fa[f1];
			if(f2!=v)rot(((u==ch[f1][1])^(f1==ch[f2][1]))?u:f1);
			rot(u);
		}
		if(!v)rt=u;
	}
	void ins(int x,int ID)
	{
		int u=rt,f=0;
		while(u)pushdown(u),f=u,u=ch[u][x>val[u]];
		u=pool[tot--];
		val[u]=x;id[u]=ID;
		ch[u][0]=ch[u][1]=fa[u]=tag[u]=ans[u]=0;
		if(f)con(u,f,x>val[f]);
		splay(u,0);
	}
	int pre(int x)
	{
		int u=rt,res=0;
		while(u)
		{
			pushdown(u);
			if(val[u]<x)res=u,u=ch[u][1];
			else u=ch[u][0];
		}
		return res;
	}
	int nxt(int x)
	{
		int u=rt,res=0;
		while(u)
		{
			pushdown(u);
			if(val[u]>x)res=u,u=ch[u][0];
			else u=ch[u][1];
		}
		return res;
	}
	void trans(int u,int x)
	{
		if(!u)return;
		pushdown(u);
		trans(ch[u][0],x);
		trans(ch[u][1],x);
		pool[++tot]=u;
		num[id[u]]++;
		if(val[u]-x>=minc)ins(val[u]-x,id[u]);
	}
	void dfs(int u)
	{
		if(!u)return;
		pushdown(u);dfs(ch[u][0]);dfs(ch[u][1]);
	}
	void solve()
	{
		for(register int i=1;i<=m+1;i++)pool[++tot]=i;
		for(register int i=1;i<=m;i++)ins(input(),i);
		ins(-inf,0);
		for(register int i=1;i<=n;i++)
		{
			int u,v,k;
			u=pre(a[i].ci);
			splay(u,0);
			v=nxt((a[i].ci<<1)-1);
			if(v)
			{
				splay(v,u);
				k=ch[v][0];ch[v][0]=0;
				cover(v,-a[i].ci,1);
				trans(k,a[i].ci);
			}
			else k=ch[u][1],ch[u][1]=0,trans(k,a[i].ci);
		}
		dfs(rt);
		for(int i=1;i<=m;i++)
		{
			print(num[i]);
			if(i<m)putchar(' ');
		}
	}
}ts;
void File()
{
	freopen("data.in","r",stdin);
	freopen("ans.out","w",stdout);
}
int main()
{
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)a[i].ci=input(),a[i].qi=input(),minc=min(minc,a[i].ci);
	sort(a+1,a+n+1);
	scanf("%d",&m);
	ts.solve();
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：7)

- 此题为开摆计划 T9。
- 感谢[奆佬](https://www.luogu.com.cn/user/52881)，[奆佬](https://www.luogu.com.cn/user/52170)的指导。
- 写法想必码量会小一些。

**[题意](https://www.luogu.com.cn/problem/CF702F)**
- 有一些 T 恤，各自有其价格与品质。
- 静态多次查询，如果有人带了一些钱，并且贪心地买能买到的品质最好的，问他能买多少件。

**分析**
- 如果钱不多，可以建出转移的内向树然后倍增。
- 现在钱很多，我们考虑转换维度思考，把所有人离线下来，每一次操作相当于把不小于 $x$ 的数减 $x$。
- 而这应该如何做呢？考虑倍增分块的方法，维护 $\log w$ 棵线段树，第 $i$ 棵线段树维护 $[2^{i-1},2^i-1]$ 内的数，对于每次操作，如果减数大于区间最大值则无影响，不能使区间最小值降层就先打个标记，否则递归下去搞，把降层的领出来降即可做到 $O(n\log n\log w )$ 的复杂度，因为每次递归下去必然导致区间内至少一个数降层（如果减数大于区间最小值，那么一定会有降层，体现了二进制分解的作用），[代码](https://www.luogu.com.cn/paste/syfzgq7h)。
- 作者几乎是偶然发现~~其实是直接二进制分组被卡常~~，按照更大的进制分组会更优一点，我直接选了 $32$ 进制，然后跑得还行。

---

## 作者：Calculatelove (赞：6)

# Description

有 $n$ 个 T 恤。每个 T 恤都有一个价格 $c_i$ 和品质 $p_i$。

有 $m$ 个人要购买 T 恤，第 $i$ 个人有 $v_i$ 元。  
每个人每次购买 T 恤都会在可以买得起的 T 恤中选一件品质最高的 T 恤，若有多个品质最高的 T 恤，则选择其中最便宜的那一件 T 恤。

请你求出这 $m$ 个人各买了多少件 T 恤，注意每次询问都是独立的。

数据范围：$1 \leq n, m \leq 2 \times 10^5$，$1 \leq c_i, p_i \leq 10^9$。  
时空限制：$4000 \ \mathrm{ms} / 1000 \ \mathrm{MiB}$。

# Solution

首先，将所有的 T 恤按照品质从大到小排序，品质相同的情况按价格小到大排序。

考虑使用平衡树维护每一个人的金钱数，本题解使用的是 fhq treap。

依次处理每一个 T 恤，考虑该 T 恤可以贡献给哪些人。  
设当前处理到的 T 恤的价格为 $c$。  
显然，金钱数在区间 $[0, c)$ 内的人不需要购买该 T 恤，金钱数在区间 $[c, +\infty)$ 内的人必须购买该 T 恤。

那么，对应到平衡树上，我们需要将平衡树中权值 $\geq c$ 的所有点的权值减去 $c$，T 恤件数加上 $1$。  
使用 fhq treap 打打标记可以很轻松的做到这些事情。

关键在于合并上，我们的操作是要将平衡树 split 成 $[0, c), [c, 2c), [2c, +\infty)$ 三部分。   
其中第一部分不需要被操作，第二、三部分必须被操作。  
并且注意到，第二部分被操作后，其值域从 $[c, 2c)$ 被修改为了 $[0, c)$，与第一部分发生了重合。  
而正常的 fhq treap 是不支持任意权值合并的。

考虑第二部分里任意一个点的 " 操作前权值 " 与 " 操作后权值 " 的比值：
$$
\frac{x - c}{x} = 1 - \frac{c}{x}
$$
注意到该比值随着 $x$ 的增大而增大，当 $x = 2c - 1$ 时该比值取到最大，不难得出该比值的取值范围：
$$
0 \leq \frac{x - c}{x} < \frac{1}{2} \implies x - c < \frac{x}{2}
$$
观察上式，我们可以知道：第二部分的点被操作之后，权值至少缩小一半。  
也就是说，每个点被分到第二部分的次数至多是 $\log_2 \text{SIZE}$，其中 $\text{SIZE}$ 表示值域的大小。

那么在合并操作的时候，我们只需要遍历第二部分中的所有点，将其直接插入第一部分，最后再将第一部分和第三部分合并即可。

依次考虑完了每个 T 恤之后，再遍历一遍整棵树，将答案存下来后输出即可，注意要标记下放。

时间复杂度 $\mathcal{O}(n \log n \log \text{SIZE})$。

# Code

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read() {
	int x = 0, f = 1; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') f = -f; s = getchar(); }
	while (s >= '0' && s <= '9') { x = x * 10 + s - '0'; s = getchar(); }
	return x * f;
}

const int N = 200100;

int m, n;

struct article {
	int p, c;
} seq[N];

bool cmp(article a, article b) {
	if (a.p != b.p) return a.p > b.p;
	else return a.c < b.c;
}

int cT, root;
struct Treap {
	int lc, rc;
	int val, dat, id;
	int money;
	int tagV, tagM;
} t[N];

int New(int val, int id) {
	cT ++;
	t[cT].lc = t[cT].rc = 0;
	t[cT].val = val, t[cT].dat = rand(), t[cT].id = id;
	t[cT].money = 0;
	t[cT].tagV = t[cT].tagM = 0;
	return cT;
}

void spread(int p) {
	int lc = t[p].lc, rc = t[p].rc;
	if (t[p].tagV) {
		if (lc) t[lc].val += t[p].tagV, t[lc].tagV += t[p].tagV;
		if (rc) t[rc].val += t[p].tagV, t[rc].tagV += t[p].tagV;
		t[p].tagV = 0;
	}
	if (t[p].tagM) {
		if (lc) t[lc].money += t[p].tagM, t[lc].tagM += t[p].tagM;
		if (rc) t[rc].money += t[p].tagM, t[rc].tagM += t[p].tagM;
		t[p].tagM = 0;
	}
}

void split_v(int p, int val, int &x, int &y) {
	if (!p)
		x = y = 0;
	else {
		spread(p);
		if (t[p].val <= val)
			x = p, split_v(t[p].rc, val, t[x].rc, y);
		else
			y = p, split_v(t[p].lc, val, x, t[y].lc); 
	}
}

int merge(int p, int q) {
	if (!p || !q) return p ^ q;
	spread(p), spread(q);
	if (t[p].dat > t[q].dat) {
		t[p].rc = merge(t[p].rc, q);
		return p;
	} else {
		t[q].lc = merge(p, t[q].lc);
		return q;
	}
}

void insert(int &rt, int p) {
	int X, Z;
	split_v(rt, t[p].val, X, Z);
	rt = merge(X, p), rt = merge(rt, Z); 
}

void search(int p, int &rt) {
	if (!p) return;
	spread(p);
	search(t[p].lc, rt), search(t[p].rc, rt);
	t[p].lc = t[p].rc = 0;
	insert(rt, p);
}

int ans[N];

void solve(int p) {
	if (!p) return;
	spread(p);
	solve(t[p].lc), solve(t[p].rc);
	ans[t[p].id] = t[p].money; 
}

int main() {
	m = read();

	for (int i = 1; i <= m; i ++)
		seq[i].c = read(), seq[i].p = read();

	sort(seq + 1, seq + 1 + m, cmp);

	n = read();

	for (int i = 1; i <= n; i ++) {
		int x = read();
		int p = New(x, i);
		insert(root, p);
	}

	for (int i = 1; i <= m; i ++) {
		int c = seq[i].c, p = seq[i].p;

		int X, Y, Z;
		split_v(root, c - 1, X, Y);
		split_v(Y, 2 * c - 1, Y, Z);

		if (Z) {
			t[Z].val -= c, t[Z].tagV -= c;
			t[Z].money ++, t[Z].tagM ++; 
		}

		if (Y) {
			t[Y].val -= c, t[Y].tagV -= c;
			t[Y].money ++, t[Y].tagM ++;
			search(Y, X);
		}

		root = merge(X, Z);
	}

	solve(root);

	for (int i = 1; i <= n; i ++)
		printf("%d ", ans[i]);
	puts("");

	return 0;
}
```

---

## 作者：Rainy_chen (赞：6)

## 题意
有 $n$ 个物品，物品有价值 $c_i$ 和品质 $q_i$。  

有 $m$ 个人，人有 $v_i$ 的钱，假设物品无限，但每个人只能买某种物品一次。

人会尽可能买品质高的并且买得起的物品，如果有多个，则选择价格较低的那个。  

求每个人会买多少件物品。

## 题解

很明显我们并不关心 $q_i$ 的具体数值，于是按照 $q_i$ 从大到小排完序后得到一个新的 $c_i$ 序列，题目所求即为在新序列上尽可能向后加数，要加几个数。  

我们当然是希望能对每个人单独处理，但是你会发现这样做很难把单次处理的复杂度降低到低于 $O(n)$ 的级别。  

如果不能对每个人单独处理，那么我们应当考虑对每个物品单独处理，对于当前处理的物品 $c_i$，它会使所有 $v_i \ge c_i$ 的人的 $v_i -= c_i$，并且答案加一，那么这就是一个很显然的平衡树模型，对所有人的 $v_i$ 建一颗平衡树，之后遍历物品，遍历到 $c_i$ 时把满足条件的区间打一个标记就可以了。  

但是凡事都要有个但是，如果仅仅如此的话，这题也不过就是个平衡树板子。  

你会发现当某一部分人的 $v_i$ 发生了变化后，这一部分人的 $v_i$ 取值区间会从 $[l_i,r_i]$ 平移到 $[l_i-c_i,r_i-c_i]$，而我们维护的平衡树上想要正确的合并区间的话，至少要保证取值范围不能交叉。  

换句话说如果你只是单纯的分开指定区间，打标记，合并，那么你的平衡树大概率会变的不是平衡树。  

这个问题实际上是非常容易处理的，容易发现会交叉的区间只有 $v_i$ 取值在 $[0,c_i)$ 和 $[c_i,2\times c_i)$ 这两部分的人，凭直觉你觉得后面这部分的人应该不会很多，所以你直接把后面这部分的所有人逐个插入前面这部分的平衡树。然后你就过了。  

事实上这个做法能过的原因并非是取值在 $[c_i,2\times c_i)$ 的人不多，而是对于每一个人，他一旦被暴力插入，就意味着他的 $v_i$ 至少要减去一个不小于 $\frac {v_i}2$ 的值，很明显，任何一个数最多会被减 $log_2 v_i$ 次，所以每个人最多会被暴力插入 $log_2 v_i$ 次，最后分析出来的复杂度还是足以通过此题的。  

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long int_t;

int_t read() {
    int_t x = 0, w = 1; char ch = 0;
    while(!isdigit(ch)) {ch = getchar(); if(ch == '-') w = -1;}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}

struct TShirt {
    int_t c, p;
    TShirt(int_t c = 0, int_t p = 0):c(c),p(p){}
} tss[200020];

int_t v[200020], ans[200020];

struct Node;
typedef Node* ptr_t;

struct Node {
    int_t w, rnd, tag1, val, tag2, id;
    ptr_t lson, rson;    

    Node(int_t w, int_t id):w(w), val(0), id(id){
        rnd = rand(); 
        lson = rson = 0;
        tag1 = tag2 = 0;
    }

    void pushdown() {
        if(tag1) {
            lson ? lson -> tag1 += tag1, lson -> w -= tag1 : 0;
            rson ? rson -> tag1 += tag1, rson -> w -= tag1 : 0;
            tag1 = 0;
        }
        if(tag2) {
            lson ? lson -> tag2 += tag2, lson -> val += tag2 : 0;
            rson ? rson -> tag2 += tag2, rson -> val += tag2 : 0;
            tag2 = 0;
        }
    }
};

void split(ptr_t rt, int_t w, ptr_t &l, ptr_t &r) {
    if(rt == 0) return (void) (l = 0, r = 0);
    rt -> pushdown();
    if(rt -> w <= w) {
        split(rt -> rson, w, l, r);
        rt -> rson = l; l = rt;
    } else {
        split(rt -> lson, w, l, r);
        rt -> lson = r; r = rt;
    }
}

ptr_t merge(ptr_t a, ptr_t b) {
    if(!a || !b) return a ? a : b;
    a -> pushdown(); b -> pushdown();
    if(a -> rnd < b -> rnd) {
        a -> rson = merge(a -> rson, b);
        return a;
    }
    b -> lson = merge(a, b -> lson);
    return b;
}

void insert(ptr_t& rt, ptr_t node) {
    ptr_t a, b;
    split(rt, node -> w, a, b);
    rt = merge(merge(a, node), b);
}

ptr_t root;

void mid(ptr_t rt, ptr_t& insert, int_t c) {
    if(!rt) return;
    rt -> pushdown();
    mid(rt -> lson, insert, c);
    mid(rt -> rson, insert, c);
    rt -> lson = rt -> rson = 0; 
    ::insert(insert, rt);
}

void mid2(ptr_t rt) {
    if(!rt) return;
    rt -> pushdown();
    ans[rt -> id] = rt -> val;
    mid2(rt -> lson); mid2(rt -> rson);
}

void addTag(ptr_t rt, int_t w, bool tag2) {
    if(rt) {
        if(tag2) rt -> tag2 += w, rt -> val += w;
        else rt -> tag1 += w, rt -> w -= w;
    }
}

int main() {
    int_t n = read();
    for(int_t i=1;i<=n;i++) tss[i].c = read(), tss[i].p = read();
    sort(tss + 1, tss + n + 1, [](TShirt a, TShirt b) {return a.p == b.p ? a.c < b.c : a.p > b.p;});
    int_t m = read();
    for(int_t i=1;i<=m;i++) {
        int_t v = read();
        ptr_t node = new Node(v, i);
        insert(root, node);
    }
    for(int_t i=1;i<=n;i++) {
        int_t c = tss[i].c;
        ptr_t a, b, d, e;
        split(root, c - 1, a, b);
        split(b, c * 2 - 1, d, e);
        b = d; d = e; e = 0;
        addTag(b, c, 0); addTag(b, 1, 1);
        addTag(d, c, 0); addTag(d, 1, 1);
        mid(b, a, c);
        root = merge(a, d);
    }
    mid2(root);
    for(int_t i=1;i<=m;i++) cout << ans[i] << ' ';
}
```

不要在意我函数的命名。。  
好久没写平衡树了写的心态有点炸，函数名就瞎取了几个。

---

## 作者：1saunoya (赞：6)

## 题意:
题面上面很清楚了（

## solution:


~~常用套路？~~

做过一道[类似的](https://www.cnblogs.com/Isaunoya/p/12595575.html)，不过那个太板子了。

这两题本质相同，都是势能分析的暴力合并。

平衡树，大家都会，减掉 $k$ 后，相对位置发生改变的，只有 $[1,k]$ 和 $[k+1,2k]$。
我们发现这个减法，如果减成功了，不会超过 $\log$ 次的。（这个是可以证明的每次减小的至少是一半，减到很小的时候就不会再减小了，所以是 $\log$ 次的）

具体点的做法大概就是，你根据值域分成三个部分，[1,k] && [k+1,2k] && [2k+1,inf]。
然后我们只需要将 $[1,k]$ 和 $[k+1,2k]$ 有序的合并就好了。
怎么合并呢？你发现$[k+1,2k]$的权值的相对大小还是不变的，那么我们就直接递归把一个个点提取出来然后合并qwq。

---

## 作者：Lgx_Q (赞：3)

题意：有 $n$ 件 T-Shirts，第 $i$ 件有价格 $c_i$ 和品质 $q_i$。有 $k$ 个人，第 $i$ 个人有 $v_i$ 元。对于一个人，他会按照品质从大到小，相同品质则按照价格从小到大，依次比较手中的钱数和每件 T-Shirts 的价格，若买得起则买，求每个人最后买了多少件 T-Shirts。  $1\le n,k\le 2\times 10^5$

---

先把所有 T-Shirts 排序，然后直接 dp。

设 $f[i,j]$ 表示从第 $i$ 件开始买，手中还有 $j$ 元，会买多少件 T-Shirts。

不难写出转移：

$$f[i,j]= \begin{cases}
f[i,j] & j<c_i \\
f[i,j-c_i] & j\ge c_i
\end{cases}$$

边界： $f[n+1,j]=0$

考虑优化这个 dp，考虑 $f[i+1,]$ 到 $f[i,]$ 的转移长什么样。

对于第二维，$[0,c_i-1]$ 的部分会原封不动地复制过来。

而 $[c_i,+\infty]$ 地部分会从 $f[i+1,0...+\infty]$ 即 $f[i+1]$ 整个数组整体 $+1$ 后复制过来。

考虑利用可持久化平衡树，每次相当于从 $c_i$ 处分裂一棵平衡树，或者打个 $+1$ 标记，或者合并两棵原有地平衡树。

我用的是 WBLT，但是总在爆空间这上面卡住。

考虑乱搞，瓶颈主要在合并操作，可以合并随机化一下。

一棵平衡树经过若干次合并后，大小为 $O(nV)$。

时空复杂度 $O(n(\log n+\log V))$。

```cpp
#include<bits/stdc++.h>
#define ls(p) a[p].lc
#define rs(p) a[p].rc
#define fi first
#define se second
#define mkp make_pair
#define ll int
#define pir pair<ll,ll>
#define pb push_back
#define ls(p) a[p].lc
#define rs(p) a[p].rc 
using namespace std;
const ll maxn=2e5+10, M=53e6+10, inf=1e9+3;
const double alpha=0.25;
struct WBLT{
	ll rt[maxn],tot;
	struct node{
		ll lc,rc,tag,use;
		ll siz;
	}a[M];
	void pushup(ll p){
		a[p].siz=a[ls(p)].siz+a[rs(p)].siz;
		if(a[p].siz>inf) a[p].siz=inf;
	}
	bool isleaf(ll p){
		return !ls(p)||!rs(p);
	}
	void refresh(ll &p){
		if(a[p].use<=1) return;
		--a[p].use;
		a[++tot]=a[p]; p=tot;
		++a[p].use;
		if(!isleaf(p)) ++a[ls(p)].use, ++a[rs(p)].use;
	}
	void pushdown(ll p){
		if(isleaf(p)||!a[p].tag) return;
		refresh(ls(p));
		refresh(rs(p));
		a[ls(p)].tag+=a[p].tag, a[rs(p)].tag+=a[p].tag;
		a[p].tag=0;
	}
	ll merge(ll p,ll q){
		if(!p||!q) return p|q;
		if(min(a[p].siz,a[q].siz)>=alpha*(a[p].siz+a[q].siz)||rand()<10000){ // 合并随机化
			ll x=++tot;
			ls(x)=p, rs(x)=q;
			++a[p].use, ++a[q].use;
			pushup(x); return x;
		}
		if(a[p].siz>=a[q].siz){
			pushdown(p);
			if(a[ls(p)].siz>=alpha*(a[p].siz+a[q].siz)||rand()<10000) return merge(ls(p),merge(rs(p),q));
			else{
				pushdown(rs(p));
				return merge(merge(ls(p),ls(rs(p))),merge(rs(rs(p)),q));
			}
		} else{
			pushdown(q);
			if(a[rs(q)].siz>=alpha*(a[p].siz+a[q].siz)||rand()<10000) return merge(merge(p,ls(q)),rs(q));
			else{
				pushdown(ls(q));
				return merge(merge(p,ls(ls(q))),merge(rs(ls(q)),rs(q)));
			}
		}
	}
	void split(ll p,long long k,ll &x,ll &y){
		if(isleaf(p)){
			if(k==0) y=p, x=0;
			else x=p, y=0;
			return;
		}
		pushdown(p);
		if(a[ls(p)].siz>=k){
			split(ls(p),k,x,y);
			y=merge(y,rs(p));
		} else{
			split(rs(p),k-a[ls(p)].siz,x,y);
			x=merge(ls(p),x);
		}
	}
	ll query(ll p,ll k){
		if(isleaf(p)) return a[p].tag;
		pushdown(p);
		if(a[ls(p)].siz>=k) return query(ls(p),k);
		return query(rs(p),k-a[ls(p)].siz);
	}
}T;
struct Ts{
	ll c,q;
}b[maxn];
bool cmp(Ts a,Ts b){
	return a.q==b.q? a.c<b.c:a.q>b.q;
}
ll n,m,w[maxn];
int main(){ 
	scanf("%d",&n); srand(time(0));
	for(ll i=1;i<=n;i++){
		scanf("%d%d",&b[i].c,&b[i].q);
	}
	sort(b+1,b+1+n,cmp);
	T.rt[n+1]=T.tot=1;
	T.a[1].siz=1;
	for(ll i=1;i<=30;i++) T.rt[n+1]=T.merge(T.rt[n+1],T.rt[n+1]);
	for(ll i=n;i;i--){
		ll s1=0, s2=0;
		T.split(T.rt[i+1],b[i].c,s1,s2);
		T.a[++T.tot]=T.a[T.rt[i+1]];
		++T.a[T.tot].tag;
		T.rt[i]=T.merge(s1,T.tot);
	}
	scanf("%d",&m);
	for(ll i=1;i<=m;i++){
		ll x; scanf("%d",&x);
		printf("%d ",T.query(T.rt[1],x+1));
	}
	return 0;
}

```

---

## 作者：UperFicial (赞：3)

首先肯定是要对品质 $q_i$ 进行排序。

朴素的暴力，枚举每一个人，然后依次考虑每件物品，能买则买。

但是注意到每个人的钱数会实时变化，而又要比较大小关系，所以很难维护。

换个角度，先枚举物品 $i$，然后考虑这个物品对每个人 $j$ 的贡献，若 $v_j\ge c_i$，那么就将 $v_j$ 减去 $c_i$，然后 $j$ 的答案加 $1$。

这个问题就好做多了，因为它是一个全局的减。具体的，我们可以抽象成这样一个问题：

> 给定 $m$ 个数 $v_1,v_2,\cdots,v_m$，$n$ 次操作，每次将 $\ge c_i$ 的数减去 $c_i$，问每个数你能被操作几次。

很容易想到平衡树维护 $v$ 数组，每次将 $\ge c_i$ 的部分进行 $\text{split}$，然后打标记并进行合并。

但是这样做会有问题。

考虑 $[0,c_i)$ 部分的值不会变，$[c_i,2c_i)$ 部分的值会变成 $[0,c_i)$ 部分的值。而如果将这两个平衡树进行合并，大小关系不确定，合并出来的东西可能就不是平衡树。而 $[2c_i,\infty)$ 部分的值不需要考虑值的大小关系，因为它们减去 $c_i$ 之后是必定不小于 $c_i$ 的。

我们考虑对 $[c_i,2c_i)$ 这个部分减去 $c_i$ 后暴力插入进 $[0,c_i)$ 的部分。

分析一下复杂度，这个很有意思，我们考虑每人钱数 $v_j$ 的变化。

如果 $v_i$ 需要被暴力插入，说明 $c_i\le v_j<2c_i$，得出，$c_i>\frac{v_j}{2}$，也就是说，每次 $v_j$ 减去的数至少是它的一半，最多会被暴力插入 $\log$ 次，算上平衡树一个 $\log$，最后复杂度俩老哥。

---

## 作者：o51gHaboTei1 (赞：2)

考虑变换一下问题的角度：给定 $m$ 个数，有 $n$ 次操作，每次操作将 $\geq x_i$ 的数全部减去 $x_i$，并且将这些数维护的另一个维的值 $+1$ 最后输出 $m$ 个数另一维的值。

考虑用平衡树维护一个动态的排序过程，我们考虑这个问题一个经典的套路：对于 $x_i \leq c < 2 \times x_i$ 的所有 $c$ 我们特殊处理其他值域段整体处理。

不难发现针对此题，我们只需要将 $[2 \times x_i , +\infty)$ 值域段内的数暴力减去 $x_i$，对于 $[x_i , 2 \times x_i)$ 的值域段拿出来重构插入时间复杂度是对的。

分析时间复杂度，每个数每次暴力重构至多 $O(\log c)$ 次，算上插入时间复杂度就是 $O(n \log n \log c)$ 的。

实现使用的是 WBLT。

```cpp
/*
考虑倍增分块。
然后就做完了。
*/
#include "bits/stdc++.h"
using namespace std;
const double alpha = 0.25 , aalpha = 0.33;
const int Len = 2e5 + 5;
struct Node
{
	int ch[2],sz,tag,mx,id,v;
	Node(){ch[0] = ch[1] = sz = tag = mx = id = v = 0;}
	Node(int CH0,int CH1,int SZ,int TAG,int MX,int ID,int V){ch[0] = CH0 , ch[1] = CH1 , sz = SZ , tag = TAG , mx = MX , id = ID , v = V;}
}t[Len << 2];
#define ls(p) t[p].ch[0]
#define rs(p) t[p].ch[1]
int pool[Len << 2],psz,n,m,tot,rt;
inline void push_up(int p){t[p].sz = t[ls(p)].sz + t[rs(p)].sz;t[p].mx = max(t[ls(p)].mx , t[rs(p)].mx);}
inline void cg(int p,int w){t[p].mx += w , t[p].tag += w;}
inline void push_down(int p)
{
	if(t[p].tag){cg(ls(p) , t[p].tag) , cg(rs(p) , t[p].tag);t[p].tag = 0;}
	if(t[p].v){t[ls(p)].v += t[p].v , t[rs(p)].v += t[p].v;t[p].v = 0;}
}
inline int Id(){return psz ? pool[psz --] : ++ tot;}
inline void rec(int x){pool[++ psz] = x;}
inline int clone(int w,int id,int v){int nm = Id();t[nm] = Node(0 , 0 , 1 , 0 , w , id , v);return nm;} 
inline int mg(int x,int y){int nm = Id();t[nm] = Node(x , y , t[x].sz + t[y].sz , 0 , max(t[x].mx , t[y].mx) , 0 , 0);return nm;}
int merge(int u,int v)
{
	if(!u || !v) return u + v;
	if(t[u].sz >= t[v].sz * aalpha && t[v].sz >= t[u].sz * aalpha) return mg(u , v);
	if(t[u].sz <= t[v].sz)
	{
		push_down(v);
		int l = ls(v) , r = rs(v);rec(v);
		if(t[r].sz >= (t[u].sz + t[v].sz) * alpha) return merge(merge(u , l) , r);
		push_down(l);
		int Ls = ls(l) , Rs = rs(l);rec(l);
		return merge(merge(u , Ls) , merge(Rs , r));
	}
	else
	{
		push_down(u);
		int l = ls(u) , r = rs(u);rec(u);
		if(t[l].sz >= (t[u].sz + t[v].sz) * alpha) return merge(l , merge(r , v));
		push_down(r);
		int Ls = ls(r) , Rs = rs(r);rec(r);
		return merge(merge(l , Ls) , merge(Rs , v)); 
	}
}
void split(int now,int Sz,int &x,int &y)
{
	if(!Sz){x = 0 , y = now;return;}
	if(Sz == t[now].sz){x = now , y = 0;return;}
	push_down(now);
	int u = ls(now) , v = rs(now);
	rec(now);
	if(t[u].sz == Sz){x = u , y = v;return;}
	else if(t[u].sz > Sz){split(u , Sz , x , y);y = merge(y , v);return;}
	else{split(v , Sz - t[u].sz , x , y);x = merge(u , x);return;} 
}
int qrk(int p,int w)
{
	if(!p) return 0;
	if(t[p].sz == 1) return w > t[p].mx;
	push_down(p);
	if(w > t[ls(p)].mx) return t[ls(p)].sz + qrk(rs(p) , w);
	return qrk(ls(p) , w);
}
int qnm(int p,int rk)
{
	if(!p) return 0;
	if(t[p].sz == 1) return t[p].mx;
	push_down(p);
	if(rk > t[ls(p)].sz) return qnm(rs(p) , rk - t[ls(p)].sz);
	return qnm(ls(p) , rk);
}
struct mode
{
	int w,id,v;
	mode(){w = id = v = 0;}
	mode(int W,int ID,int V){w = W , id = ID , v = V;}
};
vector<mode> vs;
inline void Ins(mode s)
{
	int x = 0 , y = 0;
	int qp = qrk(rt , s.w);
	split(rt , qp , x , y);
	rt = merge(merge(x , clone(s.w , s.id , s.v)) , y);
}
void del(int p,int w)
{
	if(!p) return;
	if(t[p].sz == 1)
	{
		vs.push_back(mode(t[p].mx + w , t[p].id , t[p].v));
		rec(p);
		return;
	}
	push_down(p);
	del(ls(p) , w);
	del(rs(p) , w);
	rec(p);
}
void Work(int w)
{
	//split:[c_i,2c_i - 1]
	int x = 0 , y = 0 , z = 0 , h = 0;
	const int l = w , r = 2 * w - 1;
	int qp = qrk(rt , l);
	split(rt , qp , x , y);
	t[y].v ++;
	qp = qrk(y , r + 1);
	split(y , qp , z , h);
	vs.clear();
	//x,z:[c_i,2c_i - 1],h
	del(z , -w);
	cg(h , -w);
	rt = merge(x , h);
	for(int i = 0 ; i < vs.size() ; i ++) Ins(vs[i]);
}
void output(int p)
{
	if(!p) return;
	if(t[p].sz == 1) 
	{
		printf("%d %d %d\n",t[p].mx,t[p].id,t[p].v);
		return;
	}
	push_down(p);
	output(ls(p));
	output(rs(p));
}
int Print[Len];
void Answer(int p)
{
	if(!p) return;
	if(t[p].sz == 1)
	{
		Print[t[p].id] = t[p].v;
		return;
	}
	push_down(p);
	Answer(ls(p));
	Answer(rs(p));
}
struct Qs
{
	int c,q;
	Qs(){c = q = 0;}
	Qs(int C,int Q){c = C , q = Q;}
}mm[Len];
bool cmp(Qs x,Qs y){return x.q > y.q || (x.q == y.q && x.c < y.c);}
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
	//freopen("WA.in","r",stdin);
	//freopen("WA.out","w",stdout);
	n = read();
	for(int i = 1 ; i <= n ; i ++) mm[i].c = read() , mm[i].q = read();
	sort(mm + 1 , mm + 1 + n , cmp);
	m = read();
	for(int i = 1 ; i <= m ; i ++) 
	{
		int x;x = read();
		Ins(mode(x , i , 0));
	}
	for(int i = 1 ; i <= n ; i ++) Work(mm[i].c);
	Answer(rt);
	for(int i = 1 ; i <= m ; i ++) printf("%d ",Print[i]);
	return 0;
}
```

---

## 作者：Purple_wzy (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1290E)

[英文题面](http://codeforces.com/problemset/problem/702/F)

题意：

![](https://img2020.cnblogs.com/blog/1564093/202007/1564093-20200715211126901-1439364998.png)

题解：考虑枚举每个物品，用数据结构来维护人。先将物品按$v_i$递减排序，用平衡树来维护人。设当前枚举到了物品$i$，那么所有平衡树内权值大于等于$v_i$的节点的权值都要减去$v_i$，然后答案$+1$，但这样会破坏平衡树的二叉搜索树的性质。

考虑权值在$[v_i+1,2v_i]$的节点会破坏性质，我们就将这些点删除，然后一个一个暴力插回平衡树里。由于这些点的权值都至少减半，每个点只会被这样操作$log_B$次。所以复杂度是正确的。

建议使用fhq-treap。注意最后求答案时要将打的标记全部下传。

时间复杂度：$O(nlogm+mlogmlogB)$。

代码：

```c++
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
mt19937 _rnd(time(0));
struct P{
	int c,w;
	friend bool operator < (P x,P y){
		return x.w==y.w?x.c<y.c:x.w>y.w;
	}
}p[202000];
int n,m,a[202000],sa[202000],rk[202000],ans[202000];
int root,ch[202000][2],siz[202000],rnd[202000],laz[202000],tag[202000];
inline bool bbb(int x,int y){return a[x]<a[y];}
I push_up(int x){
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
I build(int &k,int l,int r){
	if(l>r)return;
	k=(l+r)>>1;siz[k]=1;rnd[k]=_rnd();
	build(ch[k][0],l,k-1);build(ch[k][1],k+1,r);
	push_up(k);
}
I add(int k,int val,int num){
	laz[k]+=val;a[k]-=val;ans[k]+=num;tag[k]+=num;
}
I push_down(int x){
	if(ch[x][0])add(ch[x][0],laz[x],tag[x]);
	if(ch[x][1])add(ch[x][1],laz[x],tag[x]);
	laz[x]=tag[x]=0;
}
I split(int now,int k,int &x,int &y){
	if(!now)return x=y=0,void();
	if(laz[now])push_down(now);
	if(a[now]<=k){
		x=now;split(ch[x][1],k,ch[x][1],y);push_up(x);
	}
	else{
		y=now;split(ch[y][0],k,x,ch[y][0]);push_up(y);
	}
}
IN merge(int x,int y){
	if(!x||!y)return x+y;
	if(laz[x])push_down(x);if(laz[y])push_down(y);
	if(rnd[x]<rnd[y]){
		ch[x][1]=merge(ch[x][1],y);push_up(x);return x;
	}
	else{
		ch[y][0]=merge(x,ch[y][0]);push_up(y);return y;
	}
}
I damage(int x){
	if(laz[x])push_down(x);
	if(ch[x][0])damage(ch[x][0]);
	if(ch[x][1])damage(ch[x][1]);
	ch[x][0]=ch[x][1]=0;siz[x]=1;rnd[x]=_rnd();
	re X,Y;split(root,a[x]-1,X,Y);
	root=merge(merge(X,x),Y);
}
I getans(int x){
	if(laz[x])push_down(x);
	if(ch[x][0])getans(ch[x][0]);
	if(ch[x][1])getans(ch[x][1]);
}
int main(){
	read(m);
	F(i,1,m)read(p[i].c),read(p[i].w);sort(p+1,p+1+m);
	read(n);F(i,1,n)read(a[i]),sa[i]=i;
	sort(sa+1,sa+1+n,bbb);F(i,1,n)rk[sa[i]]=i;
	sort(a+1,a+1+n);build(root,1,n);
	re X,Y,Z;
	F(i,1,m){
		split(root,p[i].c-1,X,Y);add(Y,p[i].c,1);split(Y,p[i].c,Y,Z);root=merge(X,Z);
		damage(Y);
	}
	getans(root);
	F(i,1,n)printf("%d ",ans[rk[i]]);
	return 0;
}
/*
3
7 5
3 5
4 3
2
13 14
2
100 500
50 499
4
50 200 150 100
*/
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

[**CF702F T-shirts**](https://www.luogu.com.cn/problem/CF702F)

有 $n$ 种 T 恤，每种有价格 $c_i$ 和品质 $q_i$。

有 $m$ 个人要买 T 恤，第 $i$ 个人有 $v_i$ 元，每人每次都会买一件能买得起的 $q_i$ 最大的 T 恤，相同 $q_i$ 时价格低的优先买。一个人只能买一种 T 恤**一件**，问最后每个人买了多少件 T 恤。

**解法**

按品质 $q$ 从大到小，按照价格 $c$ 从小到大排序。

将 $m$ 个人的钱作为权值建立一棵平衡树。

枚举第 $i$ 种衣服，价格为 $c_i$，将 $c_i$ 将平衡树 split，则 $a$ 树的人不买，$b$ 树的人都买。

维护两个懒标记，$shirt$ 表示衣服数， $money$ 表示扣除的钱数，则 $b$ 树 $shirt$ 标记 $+1$，$money$ 标记 $-c_i$。

标记下传就是给左右子节点打标记，时机有三个：split，merge，以及最后询问之前。

将 $b$ 树按 $2c_i$ 进行 split，将较小权值的子树的节点依次插入 $a$ 树，由于每次钱数减半，时间复杂度 $O(N \log N \log V)$

**注意：** 我们在插入的时候需要更新单点的信息和下传标记，将子树信息改回单点并更新购买的衣服数。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=1e6+10;
int n,m,tot,rt=0;
int shirt[N],cost[N];
struct eq{int q,c;bool operator <(const eq &a)const{if(q==a.q)return c<a.c;return q>a.q;}}q[N];
struct node{int val,rnk,lc,rc,size,del,sm;}tree[N];
inline void upd(int k){tree[k].size=tree[tree[k].lc].size+tree[tree[k].rc].size+1;return;}
inline int add_node(int val){tree[++tot]={val,rand(),0,0,1,0,0};shirt[tot]=cost[tot]=0;return tot;}
inline void pushdown(int x){
	if(shirt[x]){
		if(tree[x].lc)shirt[tree[x].lc]+=shirt[x],tree[tree[x].lc].sm+=shirt[x];
		if(tree[x].rc)shirt[tree[x].rc]+=shirt[x],tree[tree[x].rc].sm+=shirt[x];
		shirt[x]=0;
	}
	if(cost[x]){
		if(tree[x].lc)cost[tree[x].lc]+=cost[x],tree[tree[x].lc].val-=cost[x];
		if(tree[x].rc)cost[tree[x].rc]+=cost[x],tree[tree[x].rc].val-=cost[x];
		cost[x]=0;
	}
	return;
}
void print(int k){if(!k)return;pushdown(k);print(tree[k].lc);print(tree[k].rc);return;}
inline void split(int k,int &a,int &b,int val){
	if(!k){a=b=0;return;}
	pushdown(k);
	if(tree[k].val<=val)a=k,split(tree[k].rc,tree[k].rc,b,val);
	else b=k,split(tree[k].lc,a,tree[k].lc,val);
	upd(k);return;
}
inline void merge(int &k,int a,int b){
	if(!a||!b){k=a+b;return;}
	pushdown(a);pushdown(b);
	upd(a);upd(b);
	if(tree[a].rnk<tree[b].rnk)k=a,merge(tree[k].rc,tree[k].rc,b);
	else k=b,merge(tree[k].lc,a,tree[k].lc);
	upd(k);return;
}
inline void insert(int &k,int val){
	int a=0,b=0,cur=add_node(val);cost[cur]=val;
	split(k,a,b,val-1);merge(a,a,cur);merge(k,a,b);return;
}
inline void del(int &k,int val){
	int a=0,b=0,z=0;
	split(k,a,b,val);split(a,a,z,val-1);merge(z,tree[z].lc,tree[z].rc);
	merge(a,a,z);merge(k,a,b);return;
}

inline int find_num(int k,int x){
	while(tree[tree[k].lc].size+1!=x){
		if(tree[tree[k].lc].size>=x)k=tree[k].lc;
		else{
			x-=tree[tree[k].lc].size+1;
			k=tree[k].rc;
		}
	}
	return tree[k].val;
}
inline int find_rank(int &k,int val){
	int a=0,b=0;split(k,a,b,val-1);
	int tmp=tree[a].size+1;
	merge(k,a,b);
	return tmp;
}
inline int prev(int &k,int val){
	int a=0,b=0;split(k,a,b,val);
	int tmp=find_num(a,tree[a].size);merge(k,a,b);
	return tmp;
}
inline int suf(int &k,int val){
	int a=0,b=0;split(k,a,b,val-1);
	int tmp=find_num(b,1);merge(k,a,b);
	return tmp;
}
inline void ins(int a,int b){
	if(!a)return;
	pushdown(a);
	insert(b,tree[a].val);
	ins(tree[a].lc,b);
	ins(tree[a].rc,b);
	return;
}
int v[N];queue<int>Q; 
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>q[i].c>>q[i].q;
	sort(q+1,q+1+n);
	cin>>m;
	for(int i=1,x;i<=m;++i)cin>>x,insert(rt,x);
	for(int i=1;i<=n;++i){
		int a=0,b=0,z=0;
		split(rt,a,b,q[i].c-1);
		split(b,b,z,2*q[i].c-1);
		cost[z]+=q[i].c,tree[z].val-=q[i].c;
		++shirt[z];++tree[z].sm;
		while(!Q.empty())Q.pop();
		Q.push(b);
		while(!Q.empty())
		{
			int t=Q.front();Q.pop();
			pushdown(t);
			if(tree[t].lc)Q.push(tree[t].lc);
			if(tree[t].rc)Q.push(tree[t].rc);
			int _1=0,_2=0;
			split(a,_1,_2,tree[t].val-q[i].c);
			tree[t].lc=tree[t].rc=0;tree[t].val-=q[i].c;
			tree[t].size=1;shirt[t]=0;
			tree[t].sm++;cost[t]=0;//这一部分用于把子树 t 拆成节点 t，加入 a 树。 
			merge(t,_1,t);
			merge(a,t,_2);
		}
		merge(rt,a,z);
	}
	print(rt);
	for(int i=1;i<=m;++i)cout<<tree[i].sm<<' ';
	return 0;
}
// ZHONGZIJIE0608 
```
[AC](https://www.luogu.com.cn/record/157845821)

---

## 作者：ダ月 (赞：0)

### 题目分析：

我们先将衣服以品质为第一关键字降序排序，以价格为第二关键字升序排序。我们直接模拟题意，时间复杂度达到 $O(nm)$，显然过不了。

我们不妨将人拥有的钱从大到小排序，现在我们只需要考虑每一个物品对整体的贡献，记当前衣服的价格为 $c_i$，当前人们有 $v_j$ 的钱。我们找出所有 $v_j\ge c_i$ 的人，将其钱减去 $c_i$，并将其能够购买的衣服 $+1$。不难发现，这种权值区间修改，查询集合权值的问题，我们可以使用平衡树来维护。

但我们还能发现，若当前一个人拥有 $c_i+1$ 的钱，另一个人拥有 $c_i-1$ 的钱。前者会买，后者不会买，他们拥有钱的多少相对大小发生了改变。也就是平衡树它所拥有的性质会被破坏掉。

解决这一问题的办法，我们可以对 $v_i\in[1,c_i)$ 的人不做操作，$v_i\in[c_i,2c_i)$ 的人暴力修改，$v_i\in[2c_i,+\infty)$ 的人打标记修改。由于一个数被暴力修改的次数不会超过 $\log v$ 次，所以时间复杂度为 $O((n+m)\log n\log v)$，可以通过本题。

---

## 作者：xixike (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15726473.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/CF702F)

## Solution

先对物品按照品质从大到小排序，相同品质的按价格从小到大排序。

依次枚举每一个物品，考虑对于一个物品，其价格为 $c$，品质为 $q$：

- 拥有钱数小于 $c$ 的人买不起，不用管。
- 拥有钱数大于等于 $c$ 的人买得起，也必须买（物品是按品质从大到小排序的），所以这些人钱数减去 $c$，答案（购买的衣服数）加 1。

上述这两种情况用 $fhq-treap$ 维护一下即可快速解决。

但是我们不能直接合并，因为钱数减去 $c$ 之后和钱数原本就小于 $c$ 的树的大小关系就不确定了，所以不能直接合并。

那该如何合并呢？

其实没有特别复杂，直接暴力重构这棵树即可。

具体地说，枚举钱数原本在 $c \sim 2 \times c - 1$ 的树中的每一个点，在原本钱数为 $0 \sim c - 1$ 的树中查找一下，然后暴力插进去即可。

> 原本钱数 $\geq 2 \times c$ 的点减去 $c$ 之后照样满足大小关系，可以直接合并。

## Code

（有注释）

```cpp
#include <bits/stdc++.h>
#define ls(x) t[x].l
#define rs(x) t[x].r

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 2e5 + 10;

struct fhq_treap{
    int siz, val, sum, wei, l, r;
    int lazy, sub;// lazy: 答案增加数   sub: 钱减少数
}t[N];
int root, tot, a, b, c;

inline void pushup(int x){
    t[x].siz = t[ls(x)].siz + t[rs(x)].siz + 1;
}

inline void pushdown(int x){
    if(t[x].lazy){
        if(ls(x)) t[ls(x)].lazy += t[x].lazy, t[ls(x)].sum += t[x].lazy;
        if(rs(x)) t[rs(x)].lazy += t[x].lazy, t[rs(x)].sum += t[x].lazy;
        t[x].lazy = 0;
    }
    if(t[x].sub){
        if(ls(x)) t[ls(x)].sub += t[x].sub, t[ls(x)].val -= t[x].sub;
        if(rs(x)) t[rs(x)].sub += t[x].sub, t[rs(x)].val -= t[x].sub;
        t[x].sub = 0;
    }
}

inline void split_val(int x, int k, int &a, int &b){
    if(!x) return a = b = 0, void();
    pushdown(x);
    if(k >= t[x].val) a = x, split_val(rs(x), k, rs(x), b);
    else b = x, split_val(ls(x), k, a, ls(x));
    pushup(x);
}

inline void split_siz(int x, int k, int &a, int &b){
    if(!x) return a = b = 0, void();
    pushdown(x);
    if(k >= t[ls(x)].siz + 1) a = x, split_siz(rs(x), k - t[ls(x)].siz - 1, rs(x), b);
    else b = x, split_siz(ls(x), k, a, ls(x));
    pushup(x);
}

inline int merge(int x, int y){
    if(!x || !y) return x | y;
    pushdown(x), pushup(x);
    pushdown(y), pushup(y);
    if(t[x].wei < t[y].wei){
        rs(x) = merge(rs(x), y);
        return pushup(x), x;
    }else{
        ls(y) = merge(x, ls(y));
        return pushup(y), y;
    }
}

inline int newnode(int k){
    t[++tot].val = k, t[tot].wei = rand(), t[tot].siz = 1;
    t[tot].l = t[tot].r = t[tot].sum = t[tot].lazy = t[tot].sub = 0;
    return tot;
}

inline void insert(int k){
    int a, b;
    split_val(root, k, a, b);
    root = merge(merge(a, newnode(k)), b);
}
//-------------------------------------------上面都是 fhq-treap 基本操作不解释。

//最后统计答案前全都 pushdown 一下。
inline void update(int x){
    if(!x) return;
    pushdown(x);
    update(ls(x)), update(rs(x));
}

int n, m;
struct node{
    int c, q;
    bool operator < (const node &b) const{
        return q != b.q ? q > b.q : c < b.c;
    }
}p[N];
int v[N];
queue <int> q;

//暴力重构树
inline void build(int &r1, int r2, int i){// r1 为原本在 0 ~ c-1 的树地根， r2 为 c ~ 2c-1 的根
    int a, b;
    while(!q.empty()) q.pop();
    q.push(r2);
    while(!q.empty()){//暴力枚举 r2
        int x = q.front(); q.pop();
        pushdown(x);
        if(ls(x)) q.push(ls(x));
        if(rs(x)) q.push(rs(x));
        split_val(r1, t[x].val - p[i].c, a, b);//在 r1 中查找
        ls(x) = rs(x) = t[x].lazy = t[x].sub = 0;//赋上初值
        t[x].val -= p[i].c;
        t[x].siz = 1, t[x].sum++;
        r1 = merge(merge(a, x), b);//合并进去
    }
}

inline void solve(int i){
    int a, b, c;
    split_val(root, p[i].c - 1, a, b);//把 0 ~ c-1 分裂出来
    split_val(b, (p[i].c << 1) - 1, b, c);//把 c ~ 2c-1 分裂出来，>= 2c 的减去 c 之后照样满足大小关系直接合并即可。
    t[c].sub += p[i].c, t[c].val -= p[i].c;
    t[c].sum++, t[c].lazy++;
    build(a, b, i);//重建树
    root = merge(a, c);//把 >= 2c 的树合并上去
}

int main(){
    n = read();
    for(int i = 1; i <= n; ++i) p[i].c = read(), p[i].q = read();
    sort(p + 1, p + 1 + n);
    m = read();
    for(int i = 1; i <= m; ++i) insert(read());
    for(int i = 1; i <= n; ++i) solve(i);
    update(root);//统计答案前 pushdown
    for(int i = 1; i <= m; ++i) write(t[i].sum), putchar(' ');
    return puts(""), 0;
}
```

$$
\_EOF\_
$$

---

