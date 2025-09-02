# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 样例 #1

### 输入

```
3 2
2 1 3
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10
```

### 输出

```
30
```

# 题解

## 作者：wsyhb (赞：5)

## 分析 + 题解

首先考虑删数的顺序——显然按数值从小到大删，为什么？

**证明**：较小的数可能会限制较大的数删除时的区间范围，且较大的数可能会对较小的数删除时的区间长度有贡献，且没有任何负面影响。

因此从小到大讨论每个数，若此数不应删除，将此数的位置加入 `set`；否则在 `set` 中进行二分查找，找到左右两边未被删除的数中第一个比它小的位置，若无则为边界，并使用树状数组维护前缀剩余的数的个数即可。

时间复杂度：$O(n \log n)$

## 代码

实现细节详见代码。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
const int max_n=1e6+5;
int pos[max_n];//pos[i] 记录数值 i 所在位置 
bool mark[max_n];//mark[i] 标记数值 i 是否应保留 
set<int> s;
set<int>::iterator it;
namespace BIT//树状数组 
{
	int c[max_n];
	inline void modify(int p,int v)
	{
		if(p>0)
		{
			for(int i=p;i<=n;i+=i&(-i))
				c[i]+=v;
		}
	}
	inline int query(int p)
	{
		int res=0;
		for(int i=p;i>0;i-=i&(-i))
			res+=c[i];
		return res;
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		int p;
		scanf("%d",&p);
		pos[p]=i;
	}
	for(int i=1;i<=k;++i)
	{
		int b;
		scanf("%d",&b);
		mark[b]=true;
	}
	for(int i=1;i<=n;++i)
		BIT::modify(i,1);//树状数组初始化，实际上可以做到 O(n)，但没必要 
	long long ans=0;//记得开 long long 
	for(int i=1;i<=n;++i)
	{
		if(mark[i])
			s.insert(pos[i]);
		else
		{
			int l=1,r=n;//找不到即为边界 
			it=s.lower_bound(pos[i]);
			if(it!=s.end())
				r=*it-1;
			if(it!=s.begin())
				l=*(--it)+1;
			ans+=BIT::query(r)-BIT::query(l-1);
			BIT::modify(pos[i],-1);//记得将此数在树状数组中的影响消除 
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Little_Fox_Fairy (赞：2)

## 题目大意

~~题面其实挺清晰的吧。~~

## 思路分析

显然可以贪心地考虑删除数的顺序：每一次从小到大删数。

原因易证，因为如果先删掉较大的数会受到区间里较小数的限制，而先删掉小的数对大数并无影响。所以按照从小到大的顺序删数。

设我们现在要删的数为 $ a_i $ ,每一次删数的时候，分别向左右找到第一个小于 $ a_i $ 的数 $ a_l $ 和 $ a_r $ ,那么区间 $ [ l + 1 , r - 1 ] $  就是我们需要删掉并且贡献最大的区间。

考虑用一个 $ set $ 来维护不需要删掉的数，从小到大枚举，如果不需要删除，就把它丢到 $ set $ 里面，否则就二分向左右查找。然后随便拿一种支持单点修改，区间查询的数据结构维护答案即可。这里我用的是线段树。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
char eof_flag;inline char read(int*s){if(eof_flag)return 0;int k=0,f=1;char c=getchar();while(c!='-'&&(c<'0'||c>'9')){if(c==EOF){eof_flag=1;return 0;}c=getchar();}f=(c=='-')?-1:1;k=(c=='-')?0:(c^48);c=getchar();while(c>='0'&&c<='9')k=(k<<1)+(k<<3)+(c^48),c=getchar();if(c==EOF)eof_flag=1;(*s)=f>0?k:-k;return 1;}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');return;}
const int N=1e6+10;
struct Segement_Tree
{
	struct node {int l,r,val;}t[N<<2];
	inline void push_up(int u) {return t[u].val=t[u<<1].val+t[u<<1|1].val,void();}
	inline void build(int u,int l,int r) {t[u].l=l,t[u].r=r;if (l==r) return t[u].val=1,void();int mid=l+r>>1;build(u<<1,l,mid);build(u<<1|1,mid+1,r);push_up(u);return ;}
	inline void update(int u,int x,int val) {if (t[u].l==t[u].r) return t[u].val+=val,void();int mid=t[u].l+t[u].r>>1;if (x<=mid) update(u<<1,x,val);else update(u<<1|1,x,val);push_up(u);return ;}
	inline int query(int u,int l,int r) {if (t[u].l>=l and t[u].r<=r) return t[u].val;int mid=t[u].l+t[u].r>>1,sum=0;if (l<=mid) sum+=query(u<<1,l,r);if (r>mid) sum+=query(u<<1|1,l,r);return sum;}
}tr;
set<int> s;
int n,m,ans;
int vis[N],e[N],pos[N];
signed main()
{	
	read(&n),read(&m);
	tr.build(1,1,n);
	for (int i=1;i<=n;i++) read(e+i),pos[e[i]]=i;
	for (int i=1;i<=m;i++)
	{
		int x;read(&x);
		vis[x]=1;
	}
	s.insert(0),s.insert(n+1);
	for (int i=1;i<=n;i++)
	{
		if (vis[i])
		{
			s.insert(pos[i]);
			continue;
		}
		auto itr=s.lower_bound(pos[i]);
		auto itl=itr;itl--;
		ans+=tr.query(1,(*itl)+1,(*itr)-1);
		tr.update(1,pos[i],-1);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Saliеri (赞：2)

为什么唯一的题解是暴力啊……~~（虽然碾了std）~~

___

一个显然的贪心：删数必定从小到大删。

感性理解：删小数可以减少后来大数扩张区间时的阻碍，而先删大数对小数不会有影响。显然前者更优，因为留下了更多正面效果。

依次考虑删每个数时的贡献。

删数必然要使选的区间最大，且区间的 $min$ 为删的这个数。发现只要有比这个数小的数存在，必然是这个数扩张中无法逾越的障碍。

所以做法呼之欲出：按照权值从小到大枚举，维护一个$set$表示比当前数小的未被删的数的位置。贡献就是在set中找到的前驱后继所确定的区间中未被删的数的个数。

我们需要一种数据结构支持单点加，区间求和。树状数组即可。

代码：（奇短无比）

```cpp
#include <set>
#include <cstdio>
const int maxn = 1e6+5;
int n,k,a[maxn],inb[maxn],pos[maxn],c[maxn];
void update(int pos,int v){for(;pos<=n;pos+=(pos&(-pos)))c[pos] += v;}
int sum(int pos){
	int res = 0;
	for(;pos;pos-=(pos&(-pos)))res += c[pos];
	return res;
}
std :: set<int> p;
long long ans;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),pos[a[i]] = i,update(i,1);
	for(int i=1,v;i<=k;++i)
		scanf("%d",&v),inb[v] = 1;
	p.insert(0),p.insert(n+1);
	std :: set<int> :: iterator it1,it2;
	for(int i=1;i<=n;++i){
		if(!inb[i]){
			it1 = it2 = p.lower_bound(pos[i]),--it1;
			ans += sum((*it2)-1)-sum((*it1));
			update(pos[i],-1);
		}
		else p.insert(pos[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：1)

# 思路分析

如果我们要删去一个数，一定要选择一个**尽可能大**区间，且保证要删的数在这个区间中是最小的；具体来说，每次删掉数 $a_i$ 时，向左边和右边寻找第一个大于 $a_i$ 的数 $a_l,a_r$，区间 $[l+1,r-1]$ 就是删掉这个数可以获得最大收益的区间。

思考删数的顺序，一个策略是：**先删小的数，再删大的数**。原因很简单：删掉一个数的最大收益区间是受到比它小的数的限制，如果先删掉小的数再删掉大的数，区间可能会扩散，但删掉大的数再删掉小的数，区间一定不会扩散。因此我们按从小到大的顺序删就可以取到最大收益。

**原问题转换为**：

执行若干项操作。

1. 查询一个数 $a_i$ 前有多少个数。

2. 删除 $a_i$。

具体的做法是，我们记录每个数 $x$ 在 $a$ 中的下标 $pos_x$。并设置一个数组 $c_i$ 表示下标为 $i$ 的数目前有没有删去，并定义一个 STL 中的集合 set。

因为题目给出的是**排列**，我们从依次枚举 $1\sim n$。假设当前枚举到了数 $x$，如果不需要删除，就把这个数的**下标** $pos_x$ 插入在 set 中。如果需要删除，set 中第一个大于 $pos_x$ 的就是上文的 $r$，第一个小于 $pos_x$ 的就是上文的 $l$。

对于第二种情况，因为我们先删小的再删大的，所以第一个小于 $x$ 的一定是保留下来的数，这些数都存在 set 中。因为 set 存放的是下标，所以第一个大于或小于 $pos_x$ 的元素就是第一个大于小于 $x$ 的数的位置。

得到了区间 $[l+1,r-1]$，只需要求出这个区间还有多少数没删除，即该区间内 $c_i$ 的和。删除操作只需要使 $c_i\to 0$ 即可。对于数组 $c$，涉及到区间和，单点修改，可以用树状数组优化。

无论是 set 还是树状数组，执行一次的时间复杂度均为 $O(\log n)$，总时间复杂度 $O(n\log n)$，且常数较小，可以通过 $10^6$ 的数据。

# $\text{Code}$：

```cpp
#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int N=1e6+10;
set<int>s;
set<int>::iterator it;
int n,k,pos[N],vis[N],l,r,c[N];
long long ans;
inline void read(int &a){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    a=x*f;return;
}
inline void add(int x,int t){
    while(x<=n){
        c[x]+=t;
        x+=(x&-x);
    }
    return;
}
inline int ask(int x){
    int cnt=0;
    while(x>0){
        cnt+=c[x];
        x-=(x&-x);
    }
    return cnt;
}
int main(){
    read(n),read(k);
    for(int i=1,x;i<=n;i++){
        read(x);
        pos[x]=i;
    }
    for(int i=1,x;i<=k;i++){
        read(x);
        vis[x]=1;
    }
    s.insert(0),s.insert(n+1);
    for(int i=1;i<=n;i++)add(i,1);
    for(int i=1;i<=n;i++){
        if(vis[i])s.insert(pos[i]);
        else{
            it=s.lower_bound(pos[i]);
            r=(*it)-1,it--,l=(*it)+1;
            ans+=(long long)(ask(r)-ask(l-1));
            add(pos[i],-1);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

如有错误，请指出。

---

## 作者：toolong114514 (赞：1)

# CF387E George and Cards 题解
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/CF387E)
## 解题思路
考虑一种贪心的策略：从小到大删数。

由于较大的数总是会对较小的数产生区间的贡献，所以要让较大的数尽可能晚删。如果先删了较大的数，那么答案一定不会更优。

将整个数组从小到大排序，如果当前是要删的数，那么计算出向左最长的区间长，以及向右最长的区间长，加上自己所占的的区间长（值显然为 $1$），就是这个数的贡献。加完后删掉这个数。最后全部加起来即可。
### 没那么好的方法

考虑写一颗维护区间最值和区间和的线段树，并记 $\operatorname{cnt}(x,y)$ 为当前区间 $[x,y]$ 剩下的数字个数。

对于当前的点 $t$，每次分别向左向右二分（在固定一个区间的端点时），找到最小的 $l\in[1,t]$，满足 $\min\{a_l,a_{l+1},\cdots,a_t\}\geqslant a_t$，找到最大的 $r\in[t,n]$，满足 $\min\{a_t,a_{t+1},\cdots,a_r\geqslant a_t\}$，就可以计算出想要的答案，即 $\operatorname{cnt}(l,r)$。算完后在线段树上删去当前的 $a_t$

二分时每一次 check 时间复杂度为 $O(\log n)$，即一次二分的总体时间复杂度为 $O(\log^2{n})$。线段树的一次删除操作为 $O(\log n)$。总共要做 $O(n)$ 次二分，即上述做法总的时间复杂度为 $O(n\log^2 n)$。

做法比较优秀，但在 $1\le k\le n\le10^6$ 的数据范围和 CF 造的的数据下，会光荣地 ```Time limit exceeded on test 8```。
### 正解
考虑对刚才的做法进行优化。

我们发现，以删除为主的线段树只能在其上二分，已无优化可能，需要换一个方向：删数变成加数。

先开一颗（权值？）线段树，维护区间最值。

还是顺序扫一遍，记当前数为 $a_t$。

如果 $a_t$ 不需要删除，那么以 $t$ 为下标，将 $t$ 插入线段树中。

若 $a_t$ 要删除，发现此时线段树里都是限制贡献的数，那么直接找到线段树里最大的 $1\le l\le t$，最小的 $t\le r\le n$，当前贡献即为 $\operatorname{cnt}(l,r)$，$\operatorname{cnt}$ 函数的意义同上。最后在线段树里删掉 $a_t$，维护一下 $\operatorname{cnt}$ 即可。

每一次删除操作，涉及的线段树操作是 $O(\log{n})$ 的，一共要删 $O(n)$ 个数，总的时间复杂度即为 $O(n\log{n})$，可以通过本题。

答案记得要开 ```long long```！
### 卡常

当然，直接这么写常数太大，会被卡 ```TLE```，需要卡常（听说将权值线段树改为 ```STL``` 容器就能过）。

我写的代码卡常内容如下：

1. 开 ```O4``` 优化。
2. 加火车头指令集。
3. 手写 ```std::max``` 和 ```std::min``` 函数。
4. 写快读。

注：CF 允许编译代码中的指令集和优化指令。

如果你有什么更好的卡常方案，欢迎在本文的讨论区分享。

逆天的运行时间：

![](https://cdn.luogu.com.cn/upload/image_hosting/wurgg4nz.png)
## 参考代码
$O(n\log^2n)$ 的做法：[code](https://www.luogu.com.cn/paste/ykxb0og0)。

$O(n\log{n})$ 的做法（带卡常）：
```cpp
#include<algorithm>
#include<iostream>
#pragma GCC optimize(4)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
const int INF=1e9+10;
const int N=1e6+10;
int b[N];
bool vst[N];
int n,k,cnt;
long long ans;
struct ccf{
	int pos,val;
}p[N];
bool cmp(ccf pre,ccf nxt){
	return pre.val<nxt.val;
}
int tmax(int x,int y){
	return (x>y)?(x):(y);
}
int tmin(int x,int y){
	return (x<y)?(x):(y);
}
struct node{
	int l,r,sum,maxn,minn;
}tree[4*N];
void push_up(int pos){
	tree[pos].sum=tree[pos*2].sum+tree[pos*2+1].sum;
	tree[pos].maxn=tmax(tree[pos*2].maxn,tree[pos*2+1].maxn);
	tree[pos].minn=tmin(tree[pos*2].minn,tree[pos*2+1].minn);
}
void build(int pos,int lft,int rgt){
	tree[pos].l=lft;
	tree[pos].r=rgt;
	if(lft==rgt){
		tree[pos].sum=1;
		tree[pos].maxn=-INF;
		tree[pos].minn=INF;
		return;
	}
	int mid=(lft+rgt)/2;
	build(pos*2,lft,mid);
	build(pos*2+1,mid+1,rgt);
	push_up(pos);
}
void upd1(int pos,int dot){
	if(dot<tree[pos].l||tree[pos].r<dot) return;
	if(tree[pos].l==tree[pos].r){
		tree[pos].sum=0;
		return;
	}
	upd1(pos*2,dot);
	upd1(pos*2+1,dot);
	push_up(pos);
}
void upd2(int pos,int dot,int x){
	if(dot<tree[pos].l||tree[pos].r<dot) return;
	if(tree[pos].l==tree[pos].r){
		tree[pos].maxn=tree[pos].minn=x;
		return;
	}
	upd2(pos*2,dot,x);
	upd2(pos*2+1,dot,x);
	push_up(pos);
}
int ask1(int pos,int lft,int rgt){
	if(rgt<tree[pos].l||tree[pos].r<lft||lft>rgt) return 0;
	if(lft<=tree[pos].l&&tree[pos].r<=rgt) return tree[pos].sum;
	return ask1(pos*2,lft,rgt)+ask1(pos*2+1,lft,rgt);
}
int ask2(int pos,int lft,int rgt){
	if(rgt<tree[pos].l||tree[pos].r<lft) return -INF;
	if(lft<=tree[pos].l&&tree[pos].r<=rgt) return tree[pos].maxn;
	return tmax(ask2(pos*2,lft,rgt),ask2(pos*2+1,lft,rgt));
}
int ask3(int pos,int lft,int rgt){
	if(rgt<tree[pos].l||tree[pos].r<lft) return INF;
	if(lft<=tree[pos].l&&tree[pos].r<=rgt) return tree[pos].minn;
	return tmin(ask3(pos*2,lft,rgt),ask3(pos*2+1,lft,rgt));
}
inline void read(int &x) {
	x=0;int f=1;
	char s=getchar();
	for(;s<'0'||s>'9';s=getchar()) f=s=='-'?-f:f;
	for(;s>='0'&&s<='9';s=getchar()) x=x*10+s-'0';
	x*=f;
}
signed main(){
	ios::sync_with_stdio(false);
	read(n);read(k);
	if(n==k){
		cout<<"0";
		return 0;
	}
	for(int i=1;i<=n;i++){
		read(p[i].val);
		p[i].pos=i;
	}
	for(int i=1;i<=k;i++){
		read(b[i]);
		vst[b[i]]=true;
	}
	build(1,1,n);
	sort(p+1,p+n+1,cmp);	
	for(int i=1;i<=n;i++){
		if(vst[p[i].val]){
			upd2(1,p[i].pos,p[i].pos);
		}else{
			int tmp=-INF;
			if(p[i].pos>1) tmp=ask2(1,1,p[i].pos-1);
			if(tmp==-INF) tmp=0;
			ans+=ask1(1,tmp+1,p[i].pos-1);
			tmp=INF;
			if(p[i].pos<n) tmp=ask3(1,p[i].pos+1,n);
			if(tmp==INF) tmp=n+1;
			ans+=ask1(1,p[i].pos+1,tmp-1);
			ans++;
			upd1(1,p[i].pos);
		}
	}
	cout<<ans;
	return 0;
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/162994392)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/6/24.

---

## 作者：迟暮天复明 (赞：0)

贪心地考虑从小到大删数，正确性显然（删小的数能够允许大的数得到更多的分数）。从小到大枚举每个数字，拿个 set 维护到目前为止需要保留的数。如果当前数不用删，那就丢进 set 里。否则找出 set 中当前数前面和后面的位置，就得到了删除的区间。然后用树状数组维护已经删除的数字，就可以得到区间中剩余了多少数，直接累加贡献即可。时间复杂度 $O(n\log n)$。

---

## 作者：Hoks (赞：0)

## 前言
卡了挺久的一个题，鉴定为 STL 不够熟。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先比较重要的一个点在于删数的顺序。

因为数据范围很大有 $10^6$，所以我们肯定要找到其特殊性质。

比如这个例子：

$$1~4~2~3~5$$
$$1~2~5$$

这里需要删掉 $3,4$，考虑下删除的顺序。

不难发现先删除 $3$ 会优于先删除 $4$。

猜想：先删除小的数更优。

其实到这一步已经不难证明了，因为删除的数是区间的 $\min$，所以一个包含小数的区间大数不会产生影响。

也就是先删小数不劣于先删大数。

接着考虑其优越性。

比如这个样例中，当我删掉 $3$ 后，$4$ 的区间就可以覆盖到 $5$，变长了一格。

结合下肯定先删小数好了。

接着考虑怎么实现。

因为要从小到大删，所以我们直接考虑枚举数字。

又因为大数对小数没有影响，所以是可以这样枚举的。

对于区间长度，考虑把还存在的数的原位置扔进 set 里，碰到要删除的就二分下区间长度再用 BIT 计算剩下的数个数即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,V=1e6,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int n,k,ans,a[N],mp[N];set<int>s;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
}tt;
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
signed main()
{
    tt.n=n=read(),k=read();for(int i=1;i<=n;i++) a[read()]=i,tt.modify(i,1);
    for(int i=1;i<=k;i++) mp[read()]=1;
    for(int i=1;i<=n;i++)
        if(mp[i]) s.insert(a[i]);
        else
        {
            int l=1,r=n;auto u=s.lower_bound(a[i]);
            if(u!=s.end()) r=*u-1;
            if(u!=s.begin()) l=*(--u)+1;
            ans+=tt.query(r)-tt.query(l-1);
            tt.modify(a[i],-1);
        }
    print(ans);
    genshin:;flush();return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
二分和贪心，加上小小的树状数组的优化。
## 分析。
有一个很显然的思路：因为在删除时的每一个数甚至每一个区间都是固定的，所以删一个数时候选的区间肯定要尽量大，使得其对整个答案的贡献越大，那么我们就去确定这个区间即可。这个区间的要求很显然，因为我们每次要删去区间内的最小的数，所以只要固定任意一个数，然后往左往右查询第一个比这个数小的，显然如果比我们固定的小，那么这个区间的删除的数就变了，所以直接以这两个比我们固定的数小的数作为左右区间，不包括这两个区间端点，那么这个查询到的区间内一定含有当前最小值，所以该区间就是删除这个数的时候要选的区间。

那么我们考虑贪心：显然从较小的数开始删是最优的，因为删了较大的数可能会让删较小的数时候的可选区间变小，而删了较小的数不会减小较大的数的区间。显然如果我们先删除较大的数，可以进行操作的区间就会减少，而删除较大的数的区间中可以分成很多较小的数的许多区间，所以不会更优。

那么这个题就简单了，首先从小往大找要删的数，找到一个就确定一个区间，然后删除它，按照我们第一段的思路，每次删的区间长度就是往右往左第一个比他小的数，去掉左右端点。注意在删除时，这两个不包括的端点中间夹的数中，我们应该删除的是还没被删的数的个数。预处理出来较小数和左右区间即可。这里可以用二分查询，然后套树状数组优化。

注意特殊情况，即每一个数都是一个区间，或者区间范围极大或极小，这时答案可能很大，所以要用较大的数据范围。当然，貌似这道题的读入有点大，所以需要快读。

代码如下，仅供参考：
```
#include<iostream>
#include<string>
#include<algorithm>
#include<set>
using namespace std;
int n,k,p,b;
long long ans=0;
int s[2000005];
int ti[2000005],pd[1000005];
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
void add(int id,int num){
    for (int i=id;i<=n;i+=i&-i){
        s[i]+=num;
    }
}
int sum(int id){
    int res=0;
    for (int i=id;i>0;i-=i&-i){
        res+=s[i];
    }
    return res;
}
set<int> se;
set<int>::iterator point;
int main(){
	read(n);
	read(k);
    for(int i=1;i<=n;i++){
        read(p);
        add(i,1);
        ti[p]=i;
    }
    for(int i=1;i<=k;i++){
	    read(b);
        pd[b]=1;
    }
    se.insert(0);
    se.insert(n+1);
    for(int i=1;i<=n;i++){
        if(pd[i]){
            se.insert(ti[i]);
            continue;
        }
        point=se.upper_bound(ti[i]);
        int r=*point-1,l=*(--point);
        ans+=sum(r)-sum(l);
        add(ti[i],-1);
    }
    write(ans);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：ywy_c_asm (赞：0)

这题数据似乎都是rand的，导致我交了个暴力过了。。。

首先我们把这个序列的笛卡尔树建出来，然后给的那个子序列就相当于在笛卡尔树上标记了一些关键点，这些关键点是不能删的。

那么我们考虑处理一个子树的根节点，这是这个子树里面最小的对吧，如果它没有被标记，那么我们可以贪心的选整个子树删去最小值也就是这个根，也就是把答案加上子树size。删去这个点之后我们需要把它左右儿子合并，接着处理根。

如果根已经被标记了，那么就不能再出现跨越根的区间了，就递归左右儿子处理就行了。

然后这里的合并是没有复杂度保证的暴力笛卡尔树合并……然后它过了还跑得飞快。我以前听过一个号称是均摊$O(n)$的链表维护的笛卡尔树合并，然后我写了一个发现它复杂度是假的（还没直接暴力合并跑得快），如果您有什么比较好的笛卡尔树的合并方法，欢迎找我私聊~

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1000100
#define ll long long
#define isroot(_o) ((fa[_o] == 0) || (_o != ch[fa[_o]][1] && _o != ch[fa[_o]][0]))
#define opp(_o) (_o == ch[fa[_o]][1])
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	int lend[N], rend[N], changel[N], adds[N], changer[N], size[N];
	int ch[N][2], fa[N], ints[N], stk[N], fan[N];
	unsigned char bv[N];
	void dfs(int pt) {
	    if (!pt)
	        return;
	    dfs(ch[pt][0]);
	    dfs(ch[pt][1]);
	    fa[ch[pt][0]] = pt;
	    fa[ch[pt][1]] = pt;
	    if (ch[pt][1])
	        rend[pt] = rend[ch[pt][1]];
	    else
	        rend[pt] = pt;
	    if (ch[pt][0])
	        lend[pt] = lend[ch[pt][0]];
	    else
	        lend[pt] = pt;
	    size[pt] = size[ch[pt][0]] + size[ch[pt][1]] + 1;
	}
	int united(int a, int b) {
	    if (!(a && b))
	        return (a | b);
	    if (ints[a] < ints[b]) {
	        ch[a][1] = united(ch[a][1], b);
	        size[a] = size[ch[a][0]] + size[ch[a][1]] + 1;
	        return (a);
	    }
	    ch[b][0] = united(a, ch[b][0]);
	    size[b] = size[ch[b][0]] + size[ch[b][1]] + 1;
	    return (b);
	}
	ll ans = 0;
	void efs(int pt) {
	    if (!pt)
	        return;
	    while (pt && !bv[pt]) {
	        ans += size[pt];
	        int a = ch[pt][0], b = ch[pt][1];
	        pt = united(a, b);
	    }
	    if (!pt)
	        return;
	    efs(ch[pt][0]);
	    efs(ch[pt][1]);
	}
	void ywymain() {
	    int n = get(), k = get();
	    for (register int i = 1; i <= n; i++) fan[ints[i] = get()] = i;
	    for (register int i = 1; i <= k; i++) bv[fan[get()]] = 1;
	    int sp = 0, rt = 1;
	    stk[sp] = 1, sp++;
	    for (register int i = 2; i <= n; i++) {
	        int lst = 0;
	        while (sp && ints[i] < ints[stk[sp - 1]]) sp--, lst = stk[sp];
	        if (!sp)
	            rt = i;
	        else
	            ch[stk[sp - 1]][1] = i;
	        ch[i][0] = lst;
	        stk[sp] = i;
	        sp++;
	    }
	    dfs(rt);
	    efs(rt);
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

