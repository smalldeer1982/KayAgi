# Permutation

## 题目描述

### 题目大意
对于一个给定的$k$ ，求将自然数$1$ ~$k$ 所有的排列按照字典序从小到大排序后位于第$n$ 的排列。排序从$0$ 开始编号。

由于$n$ 有可能很大，所以现在将给你$k$ 个数，分别为$S_1$ ，$S_2$ ，……，$S_k$ ，规定$n$ 的计算方式为

$$n=\sum_{i=1}^k S_i \times (k-i)!$$

## 样例 #1

### 输入

```
4
3
2 1 0
3
1 0 0
4
2 1 1 0
4
1 2 1 0```

### 输出

```
3 2 1
2 1 3
3 2 4 1
2 4 3 1```

# 题解

## 作者：光明正大 (赞：13)

# 注意行末无空格！！！

本蒟蒻采用树状数组+倍增的方法，之前也有大佬这样写，但我的切入方式和他的略有不同，故发一篇题解，希望能帮到大家。

在此默认已经会了康托展开，不会的同学先看[这道题](https://www.luogu.com.cn/problem/P5367)。

先看这个式子：（题面Markdown挂了很难受）

$$n=\sum_{i=1}^k S_i*(k-i)!$$

根据简单的数学排列组合思想，$(k-i)!$指的是第i位后的数字全排列的个数，也就是说这些全排列字典序均**小于待求序列**。

这就要求第$i$位的数字小于实际第i为的数字$a[i]$，所以题中的$S[i]$指的是原序列第i位后的数字比$a[i]$小的数字的个数。

很多同学可能会想到权值线段树或者平衡树，可我太弱了，只会树状数组。

本意是想用二分答案，因为要填的数字$a[i]$越大，之后比它小的数就会越多，显然具有可二分性。

其实这样也可以倍增来解决。

虽然比权值线段树多一个$log$，但还是比较快的，没有刻意卡常，60ms，加上快输应该会再快一点。

有一个小细节，就是在query()函数中，所查询的可能大于k，所以树状数组不能卡边开5e4，应该开到$2^{log_2k+1}$，我直接开到2e5了

下面是代码：（略有压行，不喜勿喷）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int T,n,N,c[maxn],po[20]={1};
inline void modify(int x,int delta) {for(;x<=n;x+=x&-x) c[x]+=delta;}
inline int query(int x,int res=0) {for(;x;x-=x&-x) res+=c[x];return res;}
inline int gint() {
	char ch=getchar();int s=0,f=1;
	while(!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*f;
}
inline int work(int x,int res=0) {
	//query(res+po[i]),即为已填过的比当前将要填的数小的数的个数 
	//res+po[i]-query(res+po[i])-1即为未填的比当前树小的数的个数 
	for(int i=N;~i;i--) if(res+po[i]-query(res+po[i])<=x) res+=po[i];
	return res+1;
}
int main() {
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	T=gint();
	for(int i=1;i<=16;i++) po[i]=po[i-1]<<1;
	while(T--) {
		n=gint();memset(c,0,sizeof c);N=log2(n); 
		for(int i=1,x;i<=n;i++) {
			x=gint();int k=work(x);
			modify(k,1);
			printf("%d",k);
			if(i!=n) putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

```

## 感谢您的阅读

如果对您有帮助，请在右上角点一个赞


---

## 作者：cunzai_zsy0531 (赞：8)

# 题解

今天来分享UVA11525这道题。题目链接 [LINK](https://www.luogu.com.cn/problem/UVA11525)

这道题的本质是一个叫做**康托展开**的东西。就是把几个数字的每种排列都映射成一个数字（即为在全排列当中字典序排序后的序号），可以理解成一种哈希。

题目当中已经给出了康托展开的式子。这题其实是一个逆康托展开的过程，因为题目已经完成了寻找S1-Sk的过程，我们只需要用一种高效的数据结构来完成寻找即可。

运用权值线段树可以解决此类问题。每个节点的权值是这个节点的[l,r]范围内没有用的数（叶子结点即为1）的个数。第i次查询的时候寻找排名第Si的数：

# 本人的代码
```cpp
#include<iostream>
#include<cstdio>
#define N (500000+21)
//define一定一定要记得加括号
using namespace std;
struct SegmentTree{int l,r,cnt;}t[N*4];//线段树数组要开四倍
int T,n,x;
//下面是线段树模板，基本和区间加差不多，就是注意查询操作类似于平衡树找第k名
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l==r){
		t[p].cnt=1;
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].cnt=t[p*2].cnt+t[p*2+1].cnt;
}
int modify(int p,int v){
	if(t[p].l==t[p].r){
		t[p].cnt=0;//这里随着查询也改变了数值
		return t[p].l;
	}
	int res=0;
	if(v<=t[p*2].cnt) res=modify(p*2,v);//写p<<1更好
	else res=modify(p*2+1,v-t[p*2].cnt);//这里本人码风不好，写p<<1|1更好
	t[p].cnt=t[p*2].cnt+t[p*2+1].cnt;
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		build(1,1,n);
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			printf("%d",modify(1,x+1));//因为从0开始所以要把x加1
			if(i!=n) printf(" ");
		}
		printf("\n");
	}
	return 0;
}
```


# 谢谢大家！

---

## 作者：设计涉及社稷 (赞：5)

非权值线段树的stl做法：

使用vector动态维护序列，插入1~n到vector，对于每个s[i],（即代码中的x），直接输出v[x]（因为vector默认从0开始排序），然后删除此数即可。

```
#include<bits/stdc++.h>
using namespace std;

int T,n;

int main(){
	scanf("%d",&T);
	while(T--){
		vector<int>v;
		v.reserve(50010);
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			v.insert(lower_bound(v.begin(),v.end(),i),i);
            //插入x到第一个大于等于x的位置
		for(int i=1;i<=n;++i){
			int x;scanf("%d",&x);
			printf("%d ",v[x]);
			v.erase(remove(v.begin(),v.end(),v[x]));
            //删除权值为v[x]的数
		}
		puts("");
	}
	return 0;
} 
```


---

## 作者：OldVagrant (赞：4)

## 题意
[题目传送门](https://www.luogu.com.cn/problem/UVA11525)
## Solution
暂且把要求出的排列叫做 $A$。  
观察一下题目中给的式子，结合样例，不难发现 $S_i=\sum_{j=i+1}^n (A_j<A_i)$，即 $A$ 中位于 $A_i$ 后面且小于 $A_i$ 的数的总个数，所以 $A_i$ 就是位于 $A_{i-1}$ 之后的所有数中第 $S_i+1$ 大的数。  
问题转化成了：给定一个序列 $P$，初始时 $P_i=i$，有 $n$ 次操作，每次操作给定一个数 $S_i$，求出 $P$ 中的第 $S_i+1$ 大的数并删除这个数。   
看到删除和求排名，不难想到用平衡树来做，线段树也行。但是它们的常数太大了，我选用了树状数组+倍增来做，时间复杂度同样为 $O(n\log n)$，常数吊打平衡树和线段树。   
tips：关于树状数组+倍增，可以参考一下[这个博客](https://www.cnblogs.com/yzhx/p/14629840.html?ivk_sa=1024320u)，如果朴素地使用树状数组+二分来做的话时间复杂度会多出一个```log```。
## Code
并且这个题用树状数组+倍增要开两个树状数组，记得每组数据结束之后把两个树状数组都初始化掉。   
这个题很卡输出格式，行末不能有空格。
```c
#include <bits/stdc++.h>
using namespace std;
#define pc(x) putchar(x)
#define gc getchar
int t[50001],ans[50001],t2[50001];
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
void update(int x){
	while(x<=n) t[x]++,x+=x&-x;
}
void del(int x){
	while(x<=n) t2[x]--,x+=x&-x;
}
int main(){
	int q=read();
	while(q--){
		int n=read(),maxn=1<<(int)log2(n),x=read();
		for(int i=1;i<=n;i++) t2[i]=i&-i;
		write(++x),update(x),del(x);
		for(int i=2;i<=n;i++){
			int a=read(),pos=sum=0;
			for(int j=maxn;j;j>>=1) if(pos+j<=n&&sum+t2[pos+j]<=a) sum+=t2[pos+j],pos+=j;
			pc(' '),write(++pos),update(pos),del(pos);
		}pc('\n'),memset(t,0,n+1<<2);
	}return 0;
}
```


---

## 作者：CznTree (赞：2)

我们用线段树来解决这道题。

题目意思是不用多说了。我们只要用线段树就可以了，查询排名第 $s_i$ 的数，然后单点修改里塞这个查询就行了。

对了，好像末尾不能有空格。

```cpp
#include <bits/stdc++.h> 
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr) 
#define rep(i, a, b) for (int i = a; i <= b; i++) 
#define per(i, a, b) for (int i = a; i >= b; i--)
#define lcb(x) ((x) * size - size + 1) 
#define rcb(x) ((x) * size) 
#define lc(x) x << 1ll
#define rc(x) x << 1ll | 1ll				
#define lowbit(x) ((x) & (-x))
#define LEN_LC (tree[lc(i)].r - tree[lc(i)].l + 1) 
#define LEN_RC (tree[rc(i)].r - tree[rc(i)].l + 1) 
#define LEN (tree[i].r - tree[i].l + 1)  
#define int long long
const int N = 50000 + 7;
template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
struct Tree{
	int l, r, sum;
}tree[N << 2];
void push_up(int i) {
	tree[i].sum = tree[lc(i)].sum + tree[rc(i)].sum; 
}
void build(int i, int L, int R) {
	tree[i].l = L, tree[i].r = R;
	if(L == R) {
		tree[i].sum = (R - L + 1);
		return ;  
	}
	int mid = (L + R) >> 1; 
	build(lc(i), L, mid);
	build(rc(i), mid + 1, R);
	push_up(i);
}

int modify(int i, int pos) {
	if(tree[i].l == tree[i].r) {
		tree[i].sum = 0; 
		return tree[i].l;
	}
	int res = 0; 
	if(tree[lc(i)].sum >= pos) res = modify(lc(i), pos); 
	else res = modify(rc(i), pos - tree[lc(i)].sum);
	push_up(i);
	return res; 
}
void solve() {
	int k; read(k);
	build(1, 1, k);
	rep(i, 1, k) {
		int x; read(x);
		x++; 
		std::cout << modify(1, x); 
		if(i < k) std::cout << " ";// 末尾不能有空格 
	}
	std::cout << std::endl; 
}

signed main() {
	int t; read(t); while(t--) solve(); 
	return 0; 
}
```

---

## 作者：hgzxHZR (赞：2)

**注意：本题测评时不忽略行尾空格！！！**

首先这是个排列，熟知 Cantor Expansion
$$
X=\sum_{i=1}^{i=n}{a_i\times (n-i)!}+1
$$
其中 $a_i$ 指排列中**第 $i+1$ 个数**到**第 $n$ 个数**中比**第 $i$ 个数**小的数的个数。

对比题目形式，我们知道 $s$ 数组即上面的 $a$ 数组。（至于为什么不能是别的形式，~~不知道，凭感觉的。~~）

以第 $3$ 组样例为例：

$\texttt{{1,2,3,4}}$ 中有 $2$ 个数字小于第一个数字，那么第一个数字为 $3$；剩下的为 $\texttt{1,2,4}$，有 $1$ 个数字比第二个数字小，那么第二个数字就是里面第 $1+1=2$ 小的，即 $2$……

也就是说，每次操作，找到当前数列中第 $s_i+1$ 小的数字即可，然后删除。FHQ_Treap 可以办到。

~~~cpp
#include<bits/stdc++.h>

#define int long long
#define for1(r1,r2,r3) for(int r1=(r2);r1<=(r3);++r1)
#define for2(r1,r2,r3) for(int r1=(r2);r1>=(r3);--r1)
#define mem(r1,r2) memset(r1,r2,sizeof(r1))
using namespace std;

const int MAXN=2e6+505,inf=0x3f3f3f3f3f3f3f3f;

namespace FHQ_Treap{
	int cnt=0,root=0;
	struct tNode{
		int lson,rson;
		int siz,val,hal;
		void INIT(const int &x)
		{
			siz=1; lson=rson=0; val=x,hal=rand();
			return ;
		}
	}a[MAXN];
	#define lc(r1) a[r1].lson
	#define rc(r1) a[r1].rson
	void Update_siz(const int &r)
	{
		a[r].siz=a[lc(r)].siz+a[rc(r)].siz+1;
		return ;
	}
	void SplitW(int r,const int &x,int &L,int &R)
	{
		if(!r){L=R=0;return ;}
		if(x<a[r].val) R=r,SplitW(lc(r),x,L,lc(r));
		else L=r,SplitW(rc(r),x,rc(r),R);
		Update_siz(r);
		return ;
	}
	int Merge(const int &L,const int &R)
	{
		if(!L||!R) return L+R;
		if(a[L].hal>a[R].hal)
		{
			rc(L)=Merge(rc(L),R);
			Update_siz(L);
			return L;
		}
		else
		{
			lc(R)=Merge(L,lc(R));
			Update_siz(R);
			return R;
		}
	}
	void Insert(const int &x)
	{
		int L,R;
		SplitW(root,x,L,R);
		a[++cnt].INIT(x);
		int p=Merge(L,cnt);
		root=Merge(p,R);
		return ;
	}
	void Delete(const int &x)
	{
		int L,R,p;
		SplitW(root,x,L,R),SplitW(L,x-1,L,p);
		p=Merge(lc(p),rc(p));
		root=Merge(Merge(L,p),R);
		return ;
	}
	int Rank(const int &k,const int &r=root)//排名第k小的数
	{
		if(!r) return 0;
		if(k==a[lc(r)].siz+1) return a[r].val;
		if(k<a[lc(r)].siz+1) return Rank(k,lc(r));
		else return Rank(k-a[lc(r)].siz-1,rc(r));
	}
}//以上是Treap板子

int n,s[MAXN];
void solve()
{
	cin>>n;
	for1(i,1,n)
	{
		cin>>s[i];
		FHQ_Treap::Insert(i);
	}
	for1(i,1,n)
	{
		int tmp=FHQ_Treap::Rank(s[i]+1);
		FHQ_Treap::Delete(tmp);//删除
		cout<<tmp<<" ";
	}
	cout<<'\n';
	return ;
}

signed main()
{
	srand(time(NULL));
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	
	int T; cin>>T;
    //多测，但不用清空，因为最后一定是每个数都删了一遍，自动清除了属于是。
	//但是我的平衡树不会回收空间，所以开的很大
    while(T--) solve();
	
	return 0;
}
~~~

此外，我们还可以考虑 BIT，因为找排名时显然是可以二分答案的。

~~~cpp
namespace BIT{
	#define lowbit(r1) ((r1)&-(r1))
	int sum[MAXN];
	void Update(int pos,const int &delta)
	{
		while(pos<=n) sum[pos]+=delta,pos+=lowbit(pos);
		return ;
	}
	int Query(int pos)
	{
		int res=0;
		while(pos) res+=sum[pos],pos-=lowbit(pos);
		return res;
	}
}

void solve()
{
	cin>>n;
	for1(i,1,n)
	{
		cin>>s[i];
		BIT::Update(i,1);//初始化
	}
	for1(i,1,n)
	{
		int l=1,r=n,tmp;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(BIT::Query(mid)>=s[i]+1) tmp=mid,r=mid-1;
			else l=mid+1;
		}
		BIT::Update(tmp,-1);
		cout<<tmp;
		if(i!=n) cout<<" ";
	}
	cout<<'\n';
	return ;
}

~~~

比第一种写法多了一个 $O(\log n)$，但是常数极小，时间是第一种的 $1/3$。

当然 SegmentTree 也是一种做法，有点在树上二分的味道。

~~~cpp
int a[MAXN<<2];
#define lc(r1) ((r1)<<1)
#define rc(r1) ((r1)<<1|1)
#define mid (L+R>>1)
inline void UP(const int &pos) {return (void)(a[pos]=a[lc(pos)]+a[rc(pos)]);}
void Build(const int &L,const int &R,const int &pos)
{
	if(L==R) return (void)(a[pos]=1);
	Build(L,mid,lc(pos)),Build(mid+1,R,rc(pos));
	return UP(pos);
}
int Query(const int &L,const int &R,const int &pos,const int &k)//查询[L,R]中的第k大
{
	if(L==R)
	{
		a[pos]=0;//可以顺便带上修改
		return L;
	}
	int res=0;
	if(k<=a[lc(pos)]) res=Query(L,mid,lc(pos),k);
	else res=Query(mid+1,R,rc(pos),k-a[lc(pos)]);
	UP(pos);
	return res;
}
~~~



---

## 作者：Zkl21 (赞：2)

# [UVA11525](https://www.luogu.com.cn/problem/UVA11525)

如果你还不会**康托展开**，或者想要更好的用户体验，欢迎莅临本蒟蒻的[博客](https://www.cnblogs.com/week-end/articles/17572096.html)，如果你还不会**平板电视**，也可以参考一下[蒟蒻的博客](https://www.cnblogs.com/week-end/articles/17575966.html)。

## 思路
首先不难看出，这是一道**逆康托展开**的题目。但是 $n$ 的计算方式貌似有点奇怪，有没有感觉有一点熟悉？往上翻翻。

这和**康托展开公式**很相似嘛，考虑从这里入手。

手模样例不难看出，$S_i$ 的意义就是：对于第 $i$ 个数字，**后面的数字中有多少个比当前位大**。因此，我们就可以直接考虑维护每个数字找第 $k$ 大这个过程。

方法有很多，题解中也有不少。

可以考虑时间复杂度为 $O(n\log n)$ 的但常数比较大的权值线段树或平衡树，也可以考虑时间复杂度为 $O(n\log^2n)$ 但是常数较小的二分 + 树状数组，个人认为最优秀的是时间复杂度为 $O(n\log n)$ 并且常数很小的树状数组 + 倍增。

但是由于倍增解法各位大佬已经讲得很清楚了（~~本蒟蒻懒~~），因此蒟蒻这里带来码量极小（~~头文件和红黑树命名除外~~）的平板电视中的红黑树实现。

## 代码实现
```cpp
#include<iostream>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>rbt;
int k,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>k;
		for(int i=1;i<=k;i++)rbt.insert(i);
		for(int i=1,a;i<=k;i++)
		{
			cin>>a;
			auto it=rbt.find_by_order(a);//返回排名为a的元素
			cout<<*it<<(i!=k?' ':'\n');
			rbt.erase(it);
		}
	}
	return 0;
}
```
个人认为学会平板电视，对于一些需要用到简单平衡树的题目来说还是很方便的。但是对于正经的数据结构题，还是老老实实的手写平衡树吧，~~小心被卡常~~。

最后，本题解难免有一些讲解的不好的地方，欢迎各位大佬神犇指导。

---

## 作者：Huang_Yuhan (赞：2)

# 题目描述
给定整数$K,n$,求$1\sim K$的排列中按字典序第$n$大的排列(从$0$开始编号).

因为$n$很大.所以我们用$k$个整数$S_i$来表示$n$

$$n=\sum_{i=1}^{K}\ {S_i\times\ (K-i)!}$$

$1\leqslant k\leqslant 50000$

# 解:

这其实就是逆康托展开的过程.

我们先来看看康托展开.

什么是康托展开?

就是把一个排列映射成一个自然数,可以理解为一种哈希.

这个自然数的大小就是它在所有排列中按字典序大小的排名.

假如给定一个排列$\{S_i\}$

怎么计算他的排名呢?

我们只需要求出有多少个排列比他小.

对于第$i$个位置.

我们只需要保证$[1,i-1]$的排列相同.

第$i$个位置比$S_i$小.

$[i+1,K]$的位置就可以随便弄了(反正已经保证了$S_i$大)

所以第$i$个位置的贡献就是$(kth(S_i)-1)\times(K-i)!$

这里的$kth(S_i)$是指在$[i,K]$区间内$S$中$S_i$的排名.

所以给定一个指定排列,比它小的排列的个数就是

$$\sum_{i=1}^{K}\{(kth(S_i)-1)\times (K-i)!\}$$

我们发现这个东西跟题目中的$n$的定义一样.

所以答案就很显然了.

我们从左往右讨论.

设原本排列为$\{a_i\}$

那么$a_i=kth(S_i)+1$

$kth$跟上面的定义一样.

这道题的思路就是这样.

然后我们来看看怎么实现.

我怎么找在$[i,K]$区间内$S_i$的排名呢?

首先平衡树.

但是我忘了怎么写.

但是我们还有另一种工具:权值线段树

什么是权值线段树呢?

普通的线段树中的一个节点的$l,r$管辖的是$[l,r]$这个区间的序列的信息.

而权值线段树中的$l,r$表示的是$[l,r]$这个区间内的数字的信息.

操作跟平衡树差不多.

实际复杂度为$O(klog_2k)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=50000+5;
int s[maxn],ans[maxn];
int k;
struct phtree
{
	int cnt[maxn<<3];
	int kth(int p,int l,int r,int x)
	{
		if(l==r)return l;
		int mid=l+r>>1;
		if(x<=cnt[p<<1])return kth(p<<1,l,mid,x);
		else return kth(p<<1|1,mid+1,r,x-cnt[p<<1]);
	}
	void Delete(int p,int l,int r,int x)
	{
		cnt[p]--;
		if(l==r)return;
		int mid=l+r>>1;
		if(x<=mid)Delete(p<<1,l,mid,x);
		else Delete(p<<1|1,mid+1,r,x);
	}
	void Insert(int p,int l,int r,int x)
	{
		cnt[p]++;
		if(l==r)return;
		int mid=l+r>>1;
		if(x<=mid)Insert(p<<1,l,mid,x);
		else Insert(p<<1|1,mid+1,r,x);
	} 
	void clear()
	{memset(cnt,0,sizeof(cnt));}
}tree;
void work(int t)
{
	cin>>k;
	for(int i=1;i<=k;i++)cin>>s[i],tree.Insert(1,1,k,i);
	for(int i=1;i<=k;i++)
	{
		ans[i]=tree.kth(1,1,k,s[i]+1);
		tree.Delete(1,1,k,ans[i]);
	}
	for(int i=1;i<=k;i++){if(i>1)putchar(' ');printf("%d",ans[i]);}
	putchar('\n');
}

int main()
{
	//freopen("data.in","r",stdin);
	//freopen("ans.out","w",stdout);
	int t;
	cin>>t;
	while(t--)work(t);
	return 0;
}
```

在区间内查找第$K$小也可以用树状数组倍增来做。

对于$[1,K]$的数，都先赋值为一。

所以对于对于一个数$x$,它的前缀和$sum[x]$就是它在$[1,K]$中的排名。

我们要在$[1,K]$中找第$k$小的数，就在树状数组维护的前缀和上找第一个大于等于$k$的数。

就是用树状数组倍增,代码比较短，而且很好写。

不知道可以看这一篇，看不懂就看链接里面的另一个topcoder链接里面的博客（不过是英文的，但是它配有图，比较好懂）

[树状数组倍增](https://www.luogu.org/blog/HuangYuhan-Yuzhe/shu-zhuang-shuo-zu-bei-zeng)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&-x)
const int maxn=50000+5;
int s[maxn],ans[maxn];
int k;
struct phtree
{
	int c[maxn];
	void modify(int x,int d){for(x;x<=k;x+=lowbit(x))c[x]+=d;}
	int kth(int K)
	{
		int sum=0,index=0;
		for(int i=log2(k);i>=0;i--)
		if(index+(1<<i)<=k&&sum+c[index+(1<<i)]<K)
		{
			sum+=c[index+(1<<i)];
			index+=1<<i;
		}
		return index+1;
	}
}tree;
void work(int t)
{
	cin>>k;
	for(int i=1;i<=k;i++)cin>>s[i],tree.modify(i,1);
	for(int i=1;i<=k;i++)
	{
		ans[i]=tree.kth(s[i]+1);
		tree.modify(ans[i],-1);
	}
	for(int i=1;i<=k;i++){if(i>1)putchar(' ');printf("%d",ans[i]);}
	putchar('\n');
}

int main()
{
	//freopen("data.in","r",stdin);
	//freopen("ans.out","w",stdout);
	int t;
	cin>>t;
	while(t--)work(t);
	return 0;
}
```

---

## 作者：naroto2022 (赞：1)

# UVA11525 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/UVA11525)

### 前置知识

[正向康托展开](https://www.luogu.com.cn/problem/P5367)

题意很简单，就是求长度为 $n$ 的数组 $a$ 在全部 $n$ 的排列中按字典序排序的排名。

先那一组数据来手玩：

求 `4 2 3 5 1` 的排名。

- 第一位是 $4$，在这这个排列中，还会有以 $1,2,3$ 作为第一位，所以它会增加 $3\times(5-1)!=72$ 的排名。
- 第二位是 $2$，在以 `4` 为第一位的排列中，还会有 $1$ 作为第二位，所以它会增加 $1\times(5-2)!=6$ 的排名。
- 第三位是 $3$，在以 `4 2` 为前两位的排列中，还会有 $1$ 作为第三位，所以他会增加 $1\times(5-3)!=2$ 的排名。
- 第四位是 $5$，在以 `4 2 3` 为前三位的排列中，还会有 $1$ 作为第四位，所以它会增加 $1\times(5-4)!=1$ 的排名。
- 第五位无需考虑

所以，该排列的排名为 $72+6+2+1+1=82$ 名，记得最后要加 $1$，因为我们算的是该排列前面有多少个排列。

形式化的，记 $s_i\gets\begin{aligned}\sum_{j=i+1}^n [a_j<a_i]\end{aligned}$，则 $a$ 的排名就为 $\begin{aligned}\sum_{i=1}^n s_i\times(n-i)!\end{aligned}$。

如果暴力求这个数组的话是 $O(n^2)$，会超时，所以考虑用树状数组优化，就可以达到 $O(n\log n)$，原理和树状数组求逆序对一样。

### 思路

把本题的题面对比下正向康托展开发现式子一模一样，所以也就知道这题中的 $S_i$ 就是 $\begin{aligned}\sum_{j=i+1}^n [a_j<a_i]\end{aligned}$，所以问题就转化成了已知每个数后面有几个小于自己的数，求这个序列。

这个很好办，用树状数组加二分，我们可以从前往后一个一个确定 $a$。

$S_i$ 就为比 $i$ 小并且未被确定的数的个数。

在逐步确定 $a$ 过程中，对于每个 $i\in\{1,2,\cdots,n\}$，比 $i$ 小并且未被确定的数的个数满足单调性，于是就可以二分求 $a_i$，然后标上 $a_i$ 已被标记（在树状数组中把 $a_i$ 位置减一）。

时间复杂度为 $O(n\log^2 n)$，用线段树上二分可以优化到 $O(n\log n)$，但是笔者太懒（菜）了，只打了树状数组（反正能过就行）。

### 实现细节

一定要记得每一行的最后不能打空格！！！

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=5e4+5;
ll n,t[MN],a[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll lowbit(ll x){return x&-x;}
void change(ll x, ll v){while(x<=n){t[x]+=v;x+=lowbit(x);}}
ll query(ll x){ll res=0;while(x){res+=t[x];x-=lowbit(x);}return res;}
ll get(ll x){
    ll l=1,r=n+1,res;
    while(l<r){
        ll mid=l+r>>1,num=query(mid-1);
        if(num>x) r=mid;
        else l=mid+1;
    }
    return l-1;
}
void solve(){
    for(int i=1; i<=n; i++) t[i]=0;
    n=read();
    for(int i=1; i<=n; i++) change(i,1);
    for(int i=1; i<=n; i++){
        ll x=read();
        a[i]=get(x);
        change(a[i],-1);
    }
    for(int i=1; i<=n; i++){
        write(a[i]);
        if(i!=n) putchar(' ');
    }putchar('\n');
}
int main(){
    ll T=read();while(T--) solve();
    return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：1)

这是一道逆康托展开的好题。

在康托展开的板子里，我们需要独立证出位于当前元素后且比当前元素小的元素个数。但这道题中，给出了公式，所以我们按公式求解即可。

## 题意
有一排列，给出该排列全排列的排位，求出该序列原序列。

## 分析
首先我们需要知道什么是康托展开。这是一个类似于哈希的求法，赋予每个排列一个不同于其他排列的值，得出该排列的排位。

已知康托展开的式子为：$1+\sum\limits_{i=1}^nA_i\times(n-i)!$。

所以：$\frac{ans-1}{(n-i)!}=A_i\cdots j$，其中 $j$ 是剩余排名数量，作为下一次的 $ans$ 参与下一个数的运算。

对逆康托展开举一个例子：$21453$。我们很容易就能算出它的排名是 $28$ 名，也就是说有 $27$ 个排列比它小。

$\frac{27}{(5-1)!}=1\cdots3$，得出有1个元素从未出现且比当前元素小，所以当前元素为 $2$。

$\frac{3}{(5-2)!}=0\cdots3$，得出有0个元素从未出现且比当前元素小，所以当前元素为 $1$。

以此类推，原序列为 $21453$。

我们再进一步推导，发现比当前元素小且位于当前数后的元素个数可以这样表示：$A_i=\sum\limits_{j=i+1}^n(a_j<a_i)$。

问题转化成了：构建一个新序列，每次删除这个序列中位于 $A_i+1$ 的元素，利用树状数组+二分求解。

复杂度为 $O(n\operatorname{log}\operatorname{log}n)$，为了优化，二分改为倍增，复杂度降一个 $\operatorname{log}$，太实惠了！

## 代码

开两个树状数组，$tree1$ 用来求和，$tree2$ 用来删去。

另外，我们发现序列的第一元素等于 $A_i+1$，所以我们单独存储。

```cpp
	int s;
	cin >> s;
	s++;
	cout << s << " ";
	add(s),del(s);
```


**注意**：不要加行末空格。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=6e4+10;
int T,tree1[maxn],tree2[maxn],n,maxx;
int lowbit(int k){
	return k&-k;
}
void add(int x){
	while(x<=n){
		tree1[x]++;
		x+=lowbit(x);
	}
}
void del(int x){
	while(x<=n){
		tree2[x]--;
		x+=lowbit(x);
	}
}
int main(){
	cin >> T;
	while(T--){
		cin >> n;
		for(int i=1;i<=n;i++){
			tree2[i]=lowbit(i);
		}
		int s;
		cin >> s;
		s++;
		cout << s << " ";
		add(s),del(s);
        maxx=1<<(int)log2(n);
		for(int i=2;i<=n;i++){
			int x;
			cin >> x;
			int a=0;
            int sum=0;
			for(int j=maxx;j>0;j>>=1){
				if(a+j<=n){
                    if(sum+tree2[a+j]<=x){
                        sum+=tree2[a+j];
					    a+=j;
                    }
				}
            }
			a++;
            cout <<a ;
			if(i!=n){
			    cout << " ";
			}
            add(a),del(a);
		}
    	cout << endl;
	}
	return 0;
}
```













---

## 作者：DengDuck (赞：1)

康托展开是这样的，对于一个没有重复元素的数组，它的字典序排名为：

$$
sum=\sum_{i=1}^nS(i)\times (n-i)!
$$

其中 $S(i)$ 表示第 $i$ 项后面有多少项比它小。

发现很眼熟—— $S(i)$ 和题目给出的 $S_i$ 是一样的！

所以这里的 $S_i$ 表示后面有多少数字比第 $i$ 项小。

思路很简单，从前往后，对于每个数字，它在剩下数字中的排名就是后面比它小的数字的数量加上 $1$。

那么对应的，剩下的数字中从小到大排序，对应排名的数字就是这个位置的数字，我们删除这个数字即可。

这个过程用平衡树很好维护，我写了一个 FHQ Treap，实现没有什么难点。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5;
LL T,n,tot,rt,x;
struct node
{
	LL l,r,val,pri,sz;
}t[N];
void pushup(LL x)
{
	LL l=t[x].l,r=t[x].r;
	if(x)t[x].sz=t[l].sz+t[r].sz+1;
}
void split(LL rt,LL &lrt,LL &rrt,LL x)
{
	LL l=t[rt].l,r=t[rt].r;
	if(rt==0)lrt=0,rrt=0;
	else if(t[rt].val<=x)lrt=rt,split(t[rt].r,t[rt].r,rrt,x);
	else rrt=rt,split(t[rt].l,lrt,t[rt].l,x);
	pushup(rt); 
} 
void merge(LL &rt,LL lrt,LL rrt)
{
	LL l=t[rt].l,r=t[rt].r;
	if(lrt==0||rrt==0)rt=lrt+rrt;
	else if(t[lrt].pri<t[rrt].pri)rt=lrt,merge(t[rt].r,t[rt].r,rrt);
	else rt=rrt,merge(t[rt].l,lrt,t[rt].l);
	pushup(rt);
}
void ins(LL &rt,LL x)
{
	t[++tot]={0,0,x,rand(),1};
	LL rt1,rt2;
	split(rt,rt1,rt2,x);
	merge(rt1,rt1,tot),merge(rt,rt1,rt2); 
}
void del(LL &rt,LL x)
{
	LL rt1,rt2,k;
	split(rt,rt1,rt2,x),split(rt1,rt1,k,x-1);
	merge(k,t[k].l,t[k].r),merge(rt1,rt1,k),merge(rt,rt1,rt2);
}
LL kth(LL rt,LL x)
{
	LL l=t[rt].l,r=t[rt].r;
	if(x<=t[l].sz)return kth(l,x);
	if(t[l].sz+1==x)return t[rt].val;
	return kth(r,x-t[l].sz-1);
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		tot=rt=0;
		memset(t,0,sizeof(t));
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)ins(rt,i);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&x);
			LL k=kth(rt,x+1);
			printf("%lld",k);
			del(rt,k);
			if(i!=n)putchar(' '); 
		}
		putchar('\n');
	}
}
```

---

## 作者：ForgotDream_CHN (赞：1)

# UVA11525 Permutation

### 题意

给你一个正整数 $k$ 与一个序列 $S$。定义 $n$ 如下：

$$
n = \sum_{i = 1}^{k} S_i \times (k - i)!
$$

你要输出长度为 $k$ 的字典序为 $n$ 的排列，排列从 $0$ 开始编号。

$1 \le k \le 50000$，多测，$T \le 10$。

### 思路

如果你曾经听说过**康托展开**的话，那么恭喜你，~~你又会了一道水蓝~~。

如果没有的话，也不要紧，现在就去做模板题 [P5367](https://www.luogu.com.cn/problem/P5367) 吧！那里题解区的老哥讲的比我清楚的多~~逃~~。

做完模板题后，再来看这个题，你会发现，题目给出的这个式子是不是跟康托展开的式子有点像？

没错，题目给出的这个 $n$ 值，事实上就是待求序列的康托展开值。而你要做的，是把这个序列还原出来，也就是所谓的逆康托展开。

这当然也是简单的，如果你已经深刻理解了康托展开的具体过程，那么不难发现题目中的 $S_i$ 是这一项的数，在删掉了前边找出的数后，在 $1 \sim k$ 的序列中的排名。

可能听上去有些拗口，不过看了代码，就会明白的。

### 代码

时间复杂度是 $O(k ^ 2)$？但是我过了，这说明 STL 数据结构在吸了氧之后是相当快的。

当然是可以用权值线段树或者平衡树做到 $O(k \log k)$ 的，不过能过就行。

```cpp
/**
 * @file    UVA11525 Permutation.cpp
 * @author  ForgotDream
 * @brief   逆康托展开
 * @date    2023-02-28
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int k;
  std::cin >> k;
  
  std::vector<int> s(k), rest(k);
  for (auto &i : s) {
    std::cin >> i;
  }
  std::iota(rest.begin(), rest.end(), 1);  
  // 这一句的作用是生成一个递增的 1 ~ n 的序列

  std::vector<int> ans;

  for (int i = 0; i < k; i++) {
    ans.push_back(rest[s[i]]);  // 找到当前项的数字
    rest.erase(rest.begin() + s[i]);  // 删去这一项
  }

  for (int i = 0; i < k; i++) {
    std::cout << ans[i] << " \n"[i == k - 1];
  }

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
```

---

## 作者：Karry5307 (赞：1)

[安利一下我的博客](https://karry5307.github.io/)
### 题意
给定$n$个数$x_1,x_2\cdots x_n$，已知$S=\sum^{n}_{i=1}x_i(n-i)!$，求第$S$个排列
### 前置技能
康托展开是一个比较常用的哈希技巧，可以将一个排列$a_1,a_2\cdots a_n$映射到一个整数$k$，这个整数$k$就是这个排列在所有排列中的名次。

由于它是双射的，所以也可以从一个整数还原这个整数所对应的全排列。

假定这个排列是由$n$个数组成的，那么有从一个整数$k$映射到第$k$小的排列的方法：

将$k$写成$\sum^{n}_{i=1}x_i(n-i)!$的形式，其中对于任意$x_i$，有$0\leq x_i\leq i$。

对于第$i$次操作，选择当前没有选过的第$x_i$大的数加入排列。

进行第二步$n$次，所得的排列即为所求。
### 题解
注意到，题目已经完成了第一步，所以只需要完成第二步就可以了。

而数据范围$k\leq 5\times10^4$，所以要写一种高效的数据结构，支持区间第$k$小和删除一个数。

这里用权值线段树实现，由于$1\leq x_i\leq n$（这里的变量都是值上面的题意而言的），所以不用离散化。于是查询变得很简单了，但删除呢？

可以将这个数置为$0$，意思是被删除了。如果这个节点的值为$0$，那么整个子树都不复存在。

这份代码还是跑的蛮快的，$60$ms。~~可还是没有最优解跑的快~~

最后，**此题卡输出格式，**要像我这么写才能AC
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=5e4+51;
struct SegmentTree{
	ll l,r,size;
};
ll test,cnt,num;
SegmentTree tree[MAXN<<2];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll node)
{
	tree[node].size=tree[node<<1].size+tree[(node<<1)|1].size;
}
inline void create(ll l,ll r,ll node)
{
	tree[node].l=l,tree[node].r=r;
	if(l==r)
	{
		tree[node].size=1;
		return;
	}
	ll mid=(l+r)>>1;
	create(l,mid,node<<1);
	create(mid+1,r,(node<<1)|1);
	update(node);
} 
inline ll findVal(ll rk,ll node)
{
	if(tree[node].l==tree[node].r)
	{
		tree[node].size=0;
		return tree[node].l;
	}
	ll res;
	if(rk<=tree[node<<1].size)
	{
		res=findVal(rk,node<<1);
	}
	else
	{
		res=findVal(rk-tree[node<<1].size,(node<<1)|1);
	}
	update(node);
	return res;
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		cnt=read();
		create(1,cnt,1);
		for(register int j=0;j<cnt;j++)
		{
			num=read()+1;
			printf("%d",findVal(num,1));
			putchar(j==cnt-1?'\n':' ');
		}
	}
}
```

---

## 作者：autoint (赞：1)

# 分析
### 简述“康托展开”
康托展开是一个全排列到一个自然数的双射，常用于构建hash表时的空间压缩。设有$n$个数$(1,2,3,4,…,n)$，可以有组成不同($n!$种)的排列组合，康托展开表示的就是是当前排列组合在$n$个不同元素的全排列中的名次。式子表示：
$$X=\sum_{i=1}^{n}a_i*(i-1)!$$
$\rightarrow$
$$X=a_n*(n-1)!+a_{n-1}*(n-2)!+...+a_i*(i-1)!+...+a_1*0!$$

其中, $a_i$为整数，并且$0\leq a_i\leq i, 0 < i \leq n,$ 表示当前未出现的的元素中排第几个，这就是康托展开。

### 推论
根据康托展开，$S_i$就是第$i$位上可选的数中比第$i$位上应选的数小的数的个数。那么此题转化为求总区间第$S_i+1$大。一颗权值线段树解决问题，不用持久化。康托展开的排名也是基于0的，所以也不用调用STL的last_permutation().
### 算法流程
1. 用权值线段树求出总区间第$S_i+1$大，记答案为$ans$并输出
2. 将权值线段树的$[ans,ans]$叶节点置0

就这么简单
### 时间复杂度
对于单组数据，执行一次上述算法流程需要$O(\log k)$时间，而要执行$k$次，所以单组数据的时间复杂度为$O(k\log k)$。有$T$组数据所以总时间复杂度为$O(T\cdot k\log k)$
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define rg register
template<typename T>T read(T&x)
{
	T data=0;
	int w=1;
	char ch=getchar();
	while(ch!='-'&&!isdigit(ch))
		ch=getchar();
	if(ch=='-')
		w=-1,ch=getchar();
	while(isdigit(ch))
		data=data*10+ch-'0',ch=getchar();
	return x=data*w;
}
using namespace std;
const int MAXK=5e4+7;
struct SegTree
{
	int sum;
}ST[MAXK<<2];
#define root ST[o]
#define lson ST[o<<1]
#define rson ST[o<<1|1]
void pushup(int o)
{
	root.sum=lson.sum+rson.sum;
}

void build(int o,int l,int r)
{
	if(l==r)
	{
		root.sum=1;
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pushup(o);
}

int qkth(int o,int l,int r,int rnk)
{ // 边找边删，简化操作
	if(l==r)
	{
		root.sum=0;
		return l;
	}
	int mid=(l+r)>>1,ans;
	if(rnk<=lson.sum)
		ans=qkth(o<<1,l,mid,rnk);
	else
		ans=qkth(o<<1|1,mid+1,r,rnk-lson.sum);
	pushup(o);
	return ans;
}


int main()
{
//	freopen("UVa11525.in","r",stdin);
//	freopen("UVa11525.out","w",stdout);
	int T;
	read(T);
	while(T--)
	{
		memset(ST,0,sizeof(ST));
		int k;
		read(k);
		build(1,1,k);
		for(rg int i=1;i<=k;++i)
		{
			int s; // 不用开s数组，节省空间
			read(s);
			printf("%d%c",qkth(1,1,k,s+1),i==k?'\n':' ');
		}
	}
}
```
# Hint
这题卡输出格式，必须按我那样写，不然会WA。~~（我就WA了好几次。）~~

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11525)

# 前置知识

[康托展开](https://oi-wiki.org/math/permutation/#%E6%8E%92%E5%90%8D) | [线段树基础](https://oi-wiki.org/ds/seg/)

# 解法

题目贴心地帮助我们把排名转化成了康托展开完 Lehmer 码的形式（因排序从 $0$ 开始标号，也不需要手动减 $1$ 后更新 $s_{i}$），现在就只需要支持查询动态第 $k$ 小，可以使用权值线段树上二分来处理。

注意本题评测时未过滤行末空格。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct SMT
{
	struct SegmentTree
	{
		int sum;
	}tree[200010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void pushup(int rt)
	{
		tree[rt].sum=tree[lson(rt)].sum+tree[rson(rt)].sum;
	}
	void build(int rt,int l,int r)
	{
		tree[rt].sum=r-l+1;
		if(l==r)  return;
		int mid=(l+r)/2;
		build(lson(rt),l,mid);  build(rson(rt),mid+1,r);
	}
	int query(int rt,int l,int r,int k)
	{
		if(l==r)
		{
			tree[rt].sum=0;
			return l; 
		}
		int mid=(l+r)/2,ans=0;
		if(k<=tree[lson(rt)].sum)  ans=query(lson(rt),l,mid,k);
		else  ans=query(rson(rt),mid+1,r,k-tree[lson(rt)].sum);
		pushup(rt); 
		return ans;
	}
}T;
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int t,n,x,i;
	cin>>t;
	for(;t>=1;t--)
	{
		cin>>n;  T.build(1,1,n);
		for(i=1;i<=n;i++)
		{
			cin>>x;
			cout<<T.query(1,1,n,x+1);
			if(i!=n)  cout<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Shizaki_Crazy_Three (赞：0)

# [题目链接](https://www.luogu.com.cn/problem/UVA11525)

首先默认读者已经会了康托展开，不会出门左转模板题。

首先观察题面，这题的题面和式子一看就很康托展开，题里的 $S_{i}$ 就是 $i$ 后面比 $a_{i}$ 小的数的个数。于是我们可以使用权值线段树或树状数组上二分解决此题。

时间复杂度 $O(n\log_{}{n})$ 。

### code


```c++
int n;
struct BIT{
	int t[N];
	inline void add(int x,int v){
		for(;x<=n;x+=lowbit(x)) t[x]+=v;
		return;
	}
	inline int query(int x){
		int res=0;
		int sum=0;
		for(int i=20;~i;--i){
			if(res+(1<<i)<=n&&res+(1<<i)-sum-t[res+(1<<i)]<=x){
				res+=(1<<i);
				sum+=t[res];
			}
		}
		return res+1;
	}
};
inline void solve(){
	read(n);
	BIT T;
	memset(T.t,0,sizeof T.t);
	for(int i=1;i<=n;++i){
		int x;
		read(x);
		int t=T.query(x);
		write(t);
		T.add(t,1);
		if(i!=n) putchar(' ');
	}
	cout<<endl;
}
```

---

