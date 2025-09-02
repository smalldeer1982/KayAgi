# Leha and security system

## 题目描述

Bankopolis, the city you already know, finally got a new bank opened! Unfortunately, its security system is not yet working fine... Meanwhile hacker Leha arrived in Bankopolis and decided to test the system!

Bank has $ n $ cells for clients' money. A sequence from $ n $ numbers $ a_{1},a_{2},...,a_{n} $ describes the amount of money each client has. Leha wants to make requests to the database of the bank, finding out the total amount of money on some subsegments of the sequence and changing values of the sequence on some subsegments. Using a bug in the system, Leha can requests two types of queries to the database:

- 1 l r x y denoting that Leha changes each digit $ x $ to digit $ y $ in each element of sequence $ a_{i} $ , for which $ l<=i<=r $ is holds. For example, if we change in number $ 11984381 $ digit $ 8 $ to $ 4 $ , we get $ 11944341 $ . It's worth noting that Leha, in order to stay in the shadow, never changes digits in the database to $ 0 $ , i.e. $ y≠0 $ .
- 2 l r denoting that Leha asks to calculate and print the sum of such elements of sequence $ a_{i} $ , for which $ l<=i<=r $ holds.

As Leha is a white-hat hacker, he don't want to test this vulnerability on a real database. You are to write a similar database for Leha to test.

## 说明/提示

Let's look at the example testcase.

Initially the sequence is $ [38,43,4,12,70] $ .

After the first change each digit equal to $ 4 $ becomes $ 8 $ for each element with index in interval $ [1; 3] $ . Thus, the new sequence is $ [38,83,8,12,70] $ .

The answer for the first sum's query is the sum in the interval $ [2; 4] $ , which equal $ 83+8+12=103 $ , so the answer to this query is $ 103 $ .

The sequence becomes $ [38,83,8,12,78] $ after the second change and $ [38,73,7,12,77] $ after the third.

The answer for the second sum's query is $ 38+73+7+12+77=207 $ .

## 样例 #1

### 输入

```
5 5
38 43 4 12 70
1 1 3 4 8
2 2 4
1 4 5 0 8
1 2 5 8 7
2 1 5
```

### 输出

```
103
207
```

## 样例 #2

### 输入

```
5 5
25 36 39 40 899
1 1 3 2 7
2 1 2
1 3 5 9 1
1 4 4 0 9
2 1 5
```

### 输出

```
111
1002
```

# 题解

## 作者：xfrvq (赞：8)

[$\tt Link$](/problem/CF794F)。

~~口胡十秒钟，调题两小时。~~

好的其实是个不难的 $\tt {}^{\ast}2800$（自我安慰。

---

考虑线段树。节点维护十种信息代表 $0,\cdots,9$ 的权和。

> 权是啥？个位权是 $1$，十位权是 $10$，百位权是 $100$，以此类推。  
> 比如 $2627$，$2$ 的权是 $1010$，$6$ 的权是 $100$，$7$ 的权是 $1$。

于是一个节点代表的区间的和，就是 $\sum$ 数字乘上其对应权。

我们发现有了这个权和，修改可以轻松转移。

> 考虑原来是 $1243$。  
> $1$ 变 $2$，这时把 $1$ 的权加到 $2$ 头上  
> $2$ 再变 $4$，这时再把 $2$ 的权加到 $4$ 头上。  
> 完全没有问题，权和正确

考虑一个地方的修改。

我们对于线段树的节点维护 $tag_i$ 代表数字 $i$ 变成了什么。

打标记：$\forall tag_i=x,tag_i\gets y$。

当然同时要把 $x$ 的权和累加到 $y$ 头上。

考虑懒标记下传。直接枚举每个 $x\to y$ 的变换，然后修改？有问题。

> 比如 $1008$，先有一次 $1\to2$，再有一次 $0\to1$。  
> 最终有 $tag_0=1,tag_1=2$。  
> 直接暴力改所有 $i\to tag_i$，这时 $0$ 会变成 $2$。

所以我们在懒标记下传前，先备份当前的 $tag$ 以及权和。

然后懒标记下传的部分相比暴力改 $i\to tag_i$ 略有变化。

```cpp
using ll = long long;

#define rep(i,a,b) for(rg int i = (a);i <= (b);++i)
#define rg register
#define il inline

const int N = 1e5 + 5,S = N << 2;

int n,m;

ll T[10][S],tmp[2][10];
char tg[10][S],old[2][10];

#define lc (i << 1)
#define rc (lc | 1)
#define mid ((L + R) >> 1)

#define ls lc,L,mid
#define rs rc,mid + 1,R
#define id rg int i = 1,rg int L = 1,rg int R = n

il void psu(int i){
	rep(d,0,9) T[d][i] = T[d][lc] + T[d][rc];
}

il void psd(rg int i){
	rep(d,0,9){
		tmp[0][d] = T[d][lc];
		tmp[1][d] = T[d][rc];
		old[0][d] = tg[d][lc];
		old[1][d] = tg[d][rc];
	}
	rep(d,0,9) if(tg[d][i] != d){
		int x = d,y = tg[d][i];
		T[y][lc] += tmp[0][x]; T[x][lc] -= tmp[0][x];
		rep(d,0,9) if(old[0][d] == x) tg[d][lc] = y;
		T[y][rc] += tmp[1][x]; T[x][rc] -= tmp[1][x];
		rep(d,0,9) if(old[1][d] == x) tg[d][rc] = y;
		tg[d][i] = d;
	}
}

il void build(id){
	rep(d,0,9) tg[d][i] = d;
	if(L == R){
		int x = read(),cur = 1;
		while(x){
			T[x % 10][i] += cur;
			x /= 10; cur *= 10;
		}
		return;
	}
	build(ls); build(rs); psu(i);
}

il void upd(rg int l,rg int r,rg int x,rg int y,id){
	if(l <= L && R <= r){
		T[y][i] += T[x][i]; T[x][i] = 0;
		rep(d,0,9) if(tg[d][i] == x) tg[d][i] = y;
		return;
	}
	psd(i);
	if(l <= mid) upd(l,r,x,y,ls);
	if(r > mid) upd(l,r,x,y,rs);
	psu(i);
}

il ll qry(rg int l,rg int r,id){
	if(l <= L && R <= r){
		ll res = 0;
		rep(d,0,9) res += T[d][i] * d;
		return res;
	}
	psd(i);
	return (l <= mid ? qry(l,r,ls) : 0LL) + (r > mid ? qry(l,r,rs) : 0LL);
}

int main(){
	n = read(),m = read();
	build();
	while(m--){
		int op = read(),l = read(),r = read();
		if(op == 2) printf("%lld\n",qry(l,r));
		else { int x = read(),y = read(); if(x != y) upd(l,r,x,y); }
	}
	return 0;
}
```

---

## 作者：hwk0518 (赞：3)

定义一个数x对于数字y的权是x所有为y的数位权重相加。例如9199对于9的权是1011.

我们可以对0~9分别建立线段树，维护[l,r]区间上所有数对这个数字权的和。查询时只要把[l,r]上所有数对某数字的权之和乘以这个数字的大小加起来即可。

值得注意的是，下传标记时，要先对子节点作用，再对父节点作用。

最终复杂度为O(nlogn*maxm^2)，即O(100nlogn)。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=1e5+5;
const int T=5e5+5;
int n,q,a[N],tchg[10];
long long tsum[10];

struct Segment_Tree
{
	int chg[T][10];
	long long sum[T][10];
	
	void calc(int pos,int rt)
	{
		int tmp=a[pos],now=1;
		while(tmp)
		{
			sum[rt][tmp%10]+=now;
			now*=10,tmp/=10;
		}
	}
	void prework(int rt)
	{
		int i;
		for(i=0;i<10;++i) chg[rt][i]=i;
	}
	
	void cc(int sn,int rt)
	{
		int i,j;
		for(i=0;i<10;++i)
			tchg[i]=chg[sn][i],tsum[i]=sum[sn][i];
		for(i=0;i<10;++i)
			if(chg[rt][i]!=i)
			{
				for(j=0;j<10;++j)
					if(chg[sn][j]==i)
						tchg[j]=chg[rt][i];
				tsum[chg[rt][i]]+=sum[sn][i];
				tsum[i]-=sum[sn][i];
			}
		for(i=0;i<10;++i)
			chg[sn][i]=tchg[i],sum[sn][i]=tsum[i];
	}
	void CC(int rt,int x,int y)
	{
		int i;
		for(i=0;i<10;++i)
			if(chg[rt][i]==x)
			{
				sum[rt][y]+=sum[rt][x];
				sum[rt][x]=0;
				chg[rt][i]=y;
			}
	}
				
	void merge(int lsn,int rsn,int rt)
	{
		int i;
		for(i=0;i<10;++i)
			sum[rt][i]=sum[lsn][i]+sum[rsn][i];
	}
	
	void push_down(int rt)
	{
		int i,lsn=rt<<1,rsn=rt<<1|1;
		cc(lsn,rt),cc(rsn,rt);
		
		for(i=0;i<10;++i) chg[rt][i]=i;
	}
	
	void build(int l,int r,int rt)
	{
		prework(rt);
		if(l==r)
		{
			calc(l,rt);
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,rt<<1),build(mid+1,r,rt<<1|1);
		merge(rt<<1,rt<<1|1,rt);
	}
	
	void update(int l,int r,int rt,int L,int R,int x,int y)
	{
		if(L<=l&&r<=R)
		{
			CC(rt,x,y);
			return;
		}
		push_down(rt);
		int mid=(l+r)>>1;
		if(L<=mid) update(l,mid,rt<<1,L,R,x,y);
		if(R>mid) update(mid+1,r,rt<<1|1,L,R,x,y);
		merge(rt<<1,rt<<1|1,rt);
	}
	
	long long qq(int rt)
	{
		int i;
		long long ret=0;
		for(i=1;i<10;++i) ret+=sum[rt][i]*i;
		return ret;
	}
	
	long long query(int l,int r,int rt,int L,int R)
	{
		if(L<=l&&r<=R) return qq(rt);
		long long ret=0;
		int mid=(l+r)>>1;
		push_down(rt);
		if(L<=mid) ret+=query(l,mid,rt<<1,L,R);
		if(R>mid) ret+=query(mid+1,r,rt<<1|1,L,R);
		merge(rt<<1,rt<<1|1,rt);
		return ret;
	}
};
Segment_Tree SS;

void init()
{
	int i,op,l,r,x,y;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;++i) scanf("%d",&a[i]);
	SS.build(1,n,1);
	while(q--)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d%d",&l,&r,&x,&y);
			if(x==y) continue;
			SS.update(1,n,1,l,r,x,y);
		}
		else
		{
			scanf("%d%d",&l,&r);
			printf("%lld\n",SS.query(1,n,1,l,r));
		}
	}
}

int main()
{
	init();
	return 0;
}

```

---

## 作者：李至擎 (赞：2)

比较水的 *2800，但是考察对标记的理解。

有一个比较原始的思路：因为需要让所有数码为 $x$ 的改成 $y$，我们不难想到这样一个做法：对十进制下第 $1,2,3\ldots 10$ 位各开一棵线段树，每个节点存区间内每种数码的出现次数 $cnt_i$，最后用位值原理合并得到答案。

对于区间修改操作，我们打标记 $tag_i$ 表示初始为 $i$ 的数码会改成什么。在将当前点的标记下传给左右儿子的过程中，我们要将儿子的标记和父亲的合并，而这就是我们要讲的重点：

首先，父亲的标记对应的修改的操作时间，一定在儿子的标记之后。因为如果在儿子之前，肯定已经在儿子当前的标记下传到儿子的同时已经处理了；然后，对于让人头晕的具体如何合并的问题，我们可以把这个修改关系看成一张类似拓扑图的东西，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/t2ebcovl.png)

画成图再理解就清晰了很多。

但是这样是 $O(x\cdot \log_{10}a\cdot n\log n)$ 的，也就是 $O(n\log n)$ 带 100 的常数。常数太大过不了，怎么办？发现我们其实并不需要真的按十进制位维护答案，只需要在建树的时候把每一位取出来，$cnt_i$ 直接维护所有数码为 $i$ 的位置的贡献和（$\sum\limits_{t=1}^{10}$ 十进制下从低到高第 $t$ 位等于 $i$ 的个数 $\times 10^{t-1}$）即可。时间复杂度 $O(x\cdot n\log n)$。

有一点细节：取出一位的时候需要避免把前导零也算进数码里。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll pw[15],CNT[15];int a[100005],TAG[15];
struct segtree{
	struct Node{
		ll cnt[15];int tag[15];
	}c[400005];
	ll get(int p){
		ll res=0;
		for(int o=0;o<=9;++o)res+=1ll*c[p].cnt[o]*o;
		return res;
	}
	void pushup(int p){
		for(int o=0;o<=9;++o)c[p].cnt[o]=c[p<<1].cnt[o]+c[p<<1|1].cnt[o];
	}
	void pushdown(int l,int r,int p){
		for(int o=0;o<=9;++o)CNT[o]=c[p<<1].cnt[o],TAG[o]=c[p<<1].tag[o],c[p<<1].cnt[o]=0;
		for(int o=0;o<=9;++o)c[p<<1].cnt[c[p].tag[o]]+=CNT[o],c[p<<1].tag[o]=c[p].tag[TAG[o]],CNT[o]=0,TAG[o]=0;
		for(int o=0;o<=9;++o)CNT[o]=c[p<<1|1].cnt[o],TAG[o]=c[p<<1|1].tag[o],c[p<<1|1].cnt[o]=0;
		for(int o=0;o<=9;++o)c[p<<1|1].cnt[c[p].tag[o]]+=CNT[o],c[p<<1|1].tag[o]=c[p].tag[TAG[o]],CNT[o]=0,TAG[o]=0;
		for(int o=0;o<=9;++o)c[p].tag[o]=o;
	}
	void build(int l,int r,int p){
		for(int o=0;o<=9;++o)c[p].tag[o]=o;
		if(l==r){
			for(int o=0;o<=9;++o)c[p].cnt[o]=0;
			for(int k=0;k<=9;k++)if(a[l]>=pw[k])c[p].cnt[(a[l]%pw[k+1])/pw[k]]+=pw[k];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
	void update(int l,int r,int p,int L,int R,int x,int y){
		if(L<=l&&r<=R){
			c[p].cnt[y]+=c[p].cnt[x],c[p].cnt[x]=0ll;
			for(int o=0;o<=9;++o)if(c[p].tag[o]==x)c[p].tag[o]=y;
			return;
		}
		int mid=(l+r)>>1;pushdown(l,r,p);
		if(L<=mid)update(l,mid,p<<1,L,R,x,y);
		if(R>mid)update(mid+1,r,p<<1|1,L,R,x,y);
		pushup(p);
	}
	ll query(int l,int r,int p,int L,int R){
		if(L<=l&&r<=R)return get(p);
		int mid=(l+r)>>1;ll res=0ll;pushdown(l,r,p);
		if(L<=mid)res+=query(l,mid,p<<1,L,R);
		if(R>mid)res+=query(mid+1,r,p<<1|1,L,R);
		return res;
	}
}Tr;
signed main(){
	pw[0]=1ll;
	for(int o=1;o<=10;++o)pw[o]=10ll*pw[o-1];
	int n=read(),k=read();
	for(int i=1;i<=n;++i)a[i]=read();
	Tr.build(1,n,1);
	while(k--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),x=read(),y=read();
			if(x==y)continue;
			Tr.update(1,n,1,l,r,x,y);
		}
		else{
			int l=read(),r=read();
			printf("%lld\n",Tr.query(1,n,1,l,r));
		}
	}
	return 0;
}
```

---

## 作者：lzqy_ (赞：1)

简单线段树，但是考察对 lazytag 的理解。

看到修改是在 $0\sim 9$ 之间转换，容易想到把 $0\sim 9$ 分开维护。

然后又发现同一个数上 不同位置且数值相同 的数 的本质没有差别（如 $114514$ 的两个 $4$ 和两个 $1$），因此可以将其放到一棵线段树里维护，只需要在数值上进行区分即可。

所以用线段树维护区间每个数值的和即可。

注意，为了方便转移，数值为 $0$ 时，要按照数值为 $1$ 的和进行计算，统计答案时不考虑数值为 $0$ 的即可。

以上内容都是平凡的线段树部分。接下来考虑标记下传。

显然懒标记的含义为：

$lz_{i,j}$：第 $i$ 个节点，数值为 $j$ 的数全部变为 $lz_{i,j}$。

注意，这里的懒标记时不存在嵌套关系的。

于是容易得到打标记的部分代码：

```cpp
if(l>=L&&r<=R){
	data[i][y]+=data[i][x]/max(x,1)*max(y,1),data[i][x]=0;
	//这里取max是对数值为0的特殊处理		
	for(int j=0;j<10;j++)
		if(f[i][j]==x)f[i][j]=y;
   //将所有指向x的指向y
	return ;
}
```

显然，这样得到的 $lz$ 数组显然不存在嵌套关系。

但也仅限于这一层。

考虑懒标记的一个性质：**标记时存在顺序，下传时没有顺序**。

（比如普通的加法线段树，打标记的时候可以分清先后，但在下传时只有一个值 $lztag$，无法进行先后区分）

```
3 3
1 1 1
1 1 3 5 9
1 1 3 1 5
2 1 1
```

在上述样例中，打标记时显然知道操作一在操作二之前，但下传时则会先下传操作二。

那么记录下标记的顺序，强制按顺序先传可以吗？答案也是否定的。

因为这一题有一个更特殊的性质：**儿子层的状态会影响父亲层的下传。**

因为在下传 $lz$ 的时候，也要像打标记一样，将所有指向 $x$ 的指向 $y$，这就会导致多次改变指向，而这显然与下传顺序有关。

考虑将下一层的值提前存储到另一个数组中，这样下传的顺序就不会影响到最终值了。

`pushdown` 函数如下：

```cpp
//注:代码中的f即lz
ll da1[10],da2[10];
int lz1[10],lz2[10];
il void pushdown(int i){
	for(int j=0;j<10;j++){
		da1[j]=data[i<<1][j],da2[j]=data[i<<1|1][j];
		lz1[j]=f[i<<1][j],lz2[j]=f[i<<1|1][j];
	}
	for(int x=0,y;x<10;x++)
	if(f[i][x]^x){
		y=f[i][x],f[i][x]=x;
		data[i<<1][y]+=da1[x]/max(x,1)*max(y,1),data[i<<1][x]-=da1[x];
		data[i<<1|1][y]+=da2[x]/max(x,1)*max(y,1),data[i<<1|1][x]-=da2[x];
		for(int j=0;j<10;j++){
			if(lz1[j]==x)f[i<<1][j]=y;
			if(lz2[j]==x)f[i<<1|1][j]=y;
		}
	}
}
```

**寄存数组记得开 longlong。**

顺便一提，如果硬要按照顺序下传也是可以的，传 data 数组时按照父亲层 $f$ 的拓扑序下传，传 $f$ 数组时按照对应儿子层 $f$ 的拓扑序下传。

不过谁想在线段树里再套一个拓扑呢。

完整代码如下：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3)
//#pragma GCC optimize(2)
#define il inline
#define ll long long
using namespace std;
const int maxn=100010;
const int N=maxn<<2;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
int f[N][10]; 
int a[maxn],n,m;
ll data[N][10];
void build(int i,int l,int r){
	if(l==r||l>r){
		if(l==r){
			for(int x=a[l],cnt=1;x;x/=10)
				data[i][x%10]+=cnt*max(x%10,1),cnt=(cnt<<1)+(cnt<<3);
			if(!a[l])data[i][0]=1;
		}
		for(int j=0;j<10;j++) f[i][j]=j;
		return ;
	}
	if(l>r) return ;
	int mid=l+r>>1;
	build(i<<1,l,mid),build(i<<1|1,mid+1,r);
	for(int j=0;j<10;j++) data[i][j]=data[i<<1][j]+data[i<<1|1][j],f[i][j]=j; 
}
ll da1[10],da2[10];
int lz1[10],lz2[10];
il void pushdown(int i){
	for(int j=0;j<10;j++){
		da1[j]=data[i<<1][j],da2[j]=data[i<<1|1][j];
		lz1[j]=f[i<<1][j],lz2[j]=f[i<<1|1][j];
	}
	for(int x=0,y;x<10;x++)
	if(f[i][x]^x){
		y=f[i][x],f[i][x]=x;
		data[i<<1][y]+=da1[x]/max(x,1)*max(y,1),data[i<<1][x]-=da1[x];
		data[i<<1|1][y]+=da2[x]/max(x,1)*max(y,1),data[i<<1|1][x]-=da2[x];
		for(int j=0;j<10;j++){
			if(lz1[j]==x)f[i<<1][j]=y;
			if(lz2[j]==x)f[i<<1|1][j]=y;
		}
	}
}
void Modify(int i,int l,int r,int L,int R,int x,int y){
	if(x==y) return ;
	if(l>=L&&r<=R){
		data[i][y]+=data[i][x]/max(x,1)*max(y,1),data[i][x]=0;
		for(int j=0;j<10;j++)
			if(f[i][j]==x)f[i][j]=y;
		return ;
	}
	pushdown(i);
	int mid=l+r>>1;
	if(L<=mid) Modify(i<<1,l,mid,L,R,x,y);
	if(R>mid) Modify(i<<1|1,mid+1,r,L,R,x,y);
	for(int j=0;j<10;j++) data[i][j]=data[i<<1][j]+data[i<<1|1][j];
}
ll Query(int i,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		ll sum=0;
		for(int j=1;j<10;j++) sum+=data[i][j];
		return sum;
	}
	if(l>R||r<L) return 0;
	pushdown(i);
	int mid=l+r>>1;
	return Query(i<<1,l,mid,L,R)+Query(i<<1|1,mid+1,r,L,R);
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read();
	int opt,l,r,x,y;
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	while(m--){
		opt=read(),l=read(),r=read();
		if(opt==1)
			x=read(),y=read(),Modify(1,1,n,l,r,x,y);
		else printf("%lld\n",Query(1,1,n,l,r));
	}
	return 0;
}

```


---

## 作者：chihik (赞：1)


一道神奇的线段树...

题目要求区间修改，区间查询，很容易想到线段树，但是怎么维护每一位数字呢？

显然，我们将每位拆分，对于每一个数字维护他的贡献，如 $1221123$ 中 $1$ 的贡献为 $1001100$ , $2$ 的贡献为 $110010$。于是，我们需要$10$棵线段树，维护$0-9$的贡献。

修改很简单，如果将$x$改为$y$，注意区间有懒标记时要比较懒标记（因为该区间的数字在下传时会变），将区间懒标记为$x$的改为$y$，统计贡献，同时更改懒标记。

最后统计答案时，将区间数字的贡献乘上该位的数字，求和即可。

最关键的是懒标记下传，将子树懒标记不同的加入到贡献里，再将子树懒标记修改，注意改变后可能会影响答案，建议先用变量存储再赋值。

```cpp
#include <cstdio>
#define ls x << 1
#define rs x << 1 | 1

const int MAXN = 100000;
int n , k , a[ MAXN + 5 ];
struct Point{
	int l , r , Lazy;
    long long sum;
};
struct Segment_Tree{
	Point Tree[ 10 ][ 4 * MAXN + 5 ];
	
	void Pushup( int x ) {
		for( int i = 0 ; i <= 9 ; i ++ )
			Tree[ i ][ x ].sum = Tree[ i ][ ls ].sum + Tree[ i ][ rs ].sum;
	}
	void Pushdown( int x ) {
		int lazy[ 15 ];
        long long sum[ 15 ];
		
		for( int i = 0 ; i <= 9 ; i ++ )
			lazy[ i ] = Tree[ i ][ ls ].Lazy , sum[ i ] = Tree[ i ][ ls ].sum;
		for( int i = 0 ; i <= 9 ; i ++ ) {
			if( Tree[ i ][ x ].Lazy == i ) continue;
			for( int j = 0 ; j <= 9 ; j ++ )
				if( Tree[ j ][ ls ].Lazy == i ) lazy[ j ] = Tree[ i ][ x ].Lazy;
			sum[ Tree[ i ][ x ].Lazy ] += Tree[ i ][ ls ].sum;
			sum[ i ] -= Tree[ i ][ ls ].sum;
		}
		for( int i = 0 ; i <= 9 ; i ++ )
			Tree[ i ][ ls ].Lazy = lazy[ i ] , Tree[ i ][ ls ].sum = sum[ i ];
		
		for( int i = 0 ; i <= 9 ; i ++ )
			lazy[ i ] = Tree[ i ][ rs ].Lazy , sum[ i ] = Tree[ i ][ rs ].sum;
		for( int i = 0 ; i <= 9 ; i ++ ) {
			if( Tree[ i ][ x ].Lazy == i ) continue;
			for( int j = 0 ; j <= 9 ; j ++ )
				if( Tree[ j ][ rs ].Lazy == i ) lazy[ j ] = Tree[ i ][ x ].Lazy;
			sum[ Tree[ i ][ x ].Lazy ] += Tree[ i ][ rs ].sum;
			sum[ i ] -= Tree[ i ][ rs ].sum;
		}
		for( int i = 0 ; i <= 9 ; i ++ )
			Tree[ i ][ rs ].Lazy = lazy[ i ] , Tree[ i ][ rs ].sum = sum[ i ];
		
		for( int i = 0 ; i <= 9 ; i ++ )
			Tree[ i ][ x ].Lazy = i;
	}
	
	void Build( int x , int l , int r ) {
		for( int i = 0 ; i <= 9 ; i ++ ) {
			Tree[ i ][ x ].l = l , Tree[ i ][ x ].r = r;
			Tree[ i ][ x ].sum = 0 , Tree[ i ][ x ].Lazy = i;
		}
		if( l == r ) {
			int t = 1;
			while( a[ l ] ) {
				Tree[ a[ l ] % 10 ][ x ].sum += t;
				a[ l ] /= 10 , t *= 10;
			}
			return;
		}
		int Mid = ( l + r ) / 2;
		Build( ls , l , Mid );
		Build( rs , Mid + 1 , r );
		Pushup( x );
	}
	void Insert( int x , int l , int r , int dex1 , int dex2 ) {
		if( r < Tree[ 0 ][ x ].l || Tree[ 0 ][ x ].r < l )
			return;
		if( l <= Tree[ 0 ][ x ].l && Tree[ 0 ][ x ].r <= r ) {
			for( int i = 0 ; i <= 9 ; i ++ )	
				if( Tree[ i ][ x ].Lazy == dex1 ) {
					Tree[ dex2 ][ x ].sum += Tree[ dex1 ][ x ].sum;
					Tree[ dex1 ][ x ].sum = 0;
					Tree[ i ][ x ].Lazy = dex2;
				}
			return;
		}
		Pushdown( x );
		Insert( ls , l , r , dex1 , dex2 );
		Insert( rs , l , r , dex1 , dex2 );
		Pushup( x ); 
	}
	long long Find( int x , int l , int r ) {
		if( r < Tree[ 0 ][ x ].l || Tree[ 0 ][ x ].r < l )
			return 0;
		if( l <= Tree[ 0 ][ x ].l && Tree[ 0 ][ x ].r <= r ) {
			long long Ans = 0;
			for( int i = 0 ; i <= 9 ; i ++ )
				Ans += Tree[ i ][ x ].sum * i;
			return Ans;
		}
		Pushdown( x );
		return Find( ls , l ,r ) + Find( rs , l , r );
	}
}Tree;

int op , x , y , l , r;
int main( ) {
	scanf("%d %d",&n,&k);
	for( int i = 1 ; i <= n ; i ++ )
		scanf("%d",&a[ i ]);
	Tree.Build( 1 , 1 , n );
	
	for( int i = 1 ; i <= k ; i ++ ) {
		scanf("%d",&op);
		if( op == 1 ) {
			scanf("%d %d %d %d",&l,&r,&x,&y);
			if( x == y ) continue;
			Tree.Insert( 1 , l , r , x , y );
		}
		if( op == 2 ) {
			scanf("%d %d",&l,&r);
			printf("%lld\n",Tree.Find( 1 , l , r ));
		}
	}
	return 0;
}
```


---

## 作者：RainWetPeopleStart (赞：0)

考虑 $l=1,r=n$ 的情况，不难想到维护 $tr_i$ 表示 $i$ 变成了哪一个数字，以及 $sum_i$ 表示数字 $i$ 的位值和。（对于序列 $a=123,211,111$ 而言 $sum_2=10+100+0=110$）

考虑推广，可以考虑上线段树，对区间维护 $tr$（标记） 和 $sum$，$sum$ 的合并就是对位加法，$tr$ 的合并以及 $tr$ 对 $sum$ 的影响也可以通过定义轻松解决，做完了，复杂度为 $O(n+q\log n)$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define ctz __builtin_ctz
using namespace std;
const int N=1e5+10,mod=1e9+7;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int qp(int a,int b){
    int x=1;
    while(b){
        if(b&1) Mul(x,a);
        Mul(a,a);b>>=1;
    }return x;
}
int n,a[N],d[N],to[N],bel[100010];
struct info{
    ll a[10];
};
info I=(info){{0,1,2,3,4,5,6,7,8,9}};
info Z=(info){{0,0,0,0,0,0,0,0,0,0}};
info operator+(info a,info b){
    info c;
    for(int i=0;i<10;i++) c.a[i]=a.a[i]+b.a[i];
    return c;
}
info operator*(info a,info b){
    for(int i=0;i<10;i++) a.a[i]=b.a[a.a[i]];
    return a;
}
info operator&(info a,info b){
    info c=Z;
    for(int i=0;i<10;i++) c.a[b.a[i]]+=a.a[i];
    return c;
}
int val[N][10];
struct segtree{
    info T[N<<2],tg[N<<2];
    #define ls p*2
    #define rs p*2+1
    #define mid (l+r)/2
    void pu(int p){
        T[p]=T[ls]+T[rs];
    }
    void pd(int p){
        tg[ls]=tg[ls]*tg[p];
        tg[rs]=tg[rs]*tg[p];
        T[ls]=T[ls]&tg[p];
        T[rs]=T[rs]&tg[p];
        tg[p]=I;
    }
    void bd(int p,int l,int r){
        tg[p]=I;
        if(l==r){
            for(int i=0;i<10;i++) T[p].a[i]=val[l][i];
            //cout<<val[l][i]<<' ';
            //cout<<endl;
            return ;
        }bd(ls,l,mid);bd(rs,mid+1,r);pu(p);
    }void upd(int p,int l,int r,int pl,int pr,info v){
        if(pl<=l&&r<=pr){
            tg[p]=tg[p]*v;
            T[p]=T[p]&v;
            //cout<<p<<' '<<l<<' '<<r<<' '<<v.a[4]<<endl;
            return ;
        }pd(p);
        if(pl<=mid) upd(ls,l,mid,pl,pr,v);
        if(pr>mid) upd(rs,mid+1,r,pl,pr,v);
        pu(p);
    }info qry(int p,int l,int r,int pl,int pr){
        if(pl<=l&&r<=pr) return T[p];
        pd(p);info a=Z;
        if(pl<=mid) a=a+qry(ls,l,mid,pl,pr);
        if(pr>mid) a=a+qry(rs,mid+1,r,pl,pr);
        return a;
    }
}sgt;
int main(){
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++){
        int v,p10=1;cin>>v;
        while(v!=0){
            int w=v%10;v/=10;
            val[i][w]+=p10;p10*=10;
        }
    }sgt.bd(1,1,n);
    while(q--){
        int op,l,r,a,b;cin>>op>>l>>r;
        if(op==1){
            cin>>a>>b;
            info tag=I;tag.a[a]=b;
            sgt.upd(1,1,n,l,r,tag);
        }else{
            info res=sgt.qry(1,1,n,l,r);
            ll ans=0;
            for(int i=0;i<10;i++) ans+=res.a[i]*i;
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF794F)。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到这道题，考虑直接 将每一位分开来考虑，因为每一位之间互不干扰。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~8848钛金手机，两个空间，分别存储，互相干扰~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后不难想到用一个$cnt$存储$0-9$的数在某一位上的个数。这样查询就解决了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;现在考虑修改。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面考虑$lazy$的打法。考虑用一个数组$l$记录。$l[i]$表示当前区间中所有$i$都会变成$l[i]$。这样$lazy$下传的时候就可以直接改$l[i]$了（类似于接链表）（当然$cnt$也要改）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后交一下这个$10$棵线段树的代码，你会发现......$T$飞了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其实本来可以把$10$棵线段树合在一起变成一棵的，只不过上面为了方便理解这样说。这样$cnt$和$l$的改法和意义是一样的。所以交上去一棵树的代码就可以$A$了。
# 代码
```cpp
#include <cstdio>

#define isLeaf( b ) ( segTree[b].l == segTree[b].r )

typedef long long LL;
#define int LL

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct segmentTreeNode
{
	int l, r;
	LL cnt[10];
	int lazy[10];
}segTree[MAXN << 2];

int a[MAXN];
int p[10];
int N, Q;

void normalize( const int now )
{
	LL cnt1[10], cnt2[10];
	int ns1[10], ns2[10];
	for( int i = 0 ; i < 10 ; i ++ ) ns1[i] = segTree[now << 1].lazy[i], ns2[i] = segTree[now << 1 | 1].lazy[i];
	for( int i = 0 ; i < 10 ; i ++ ) cnt1[i] = segTree[now << 1].cnt[i], cnt2[i] = segTree[now << 1 | 1].cnt[i];
	for( int i = 0 ; i < 10 ; i ++ )
	{
		if( segTree[now].lazy[i] ^ i )
		{
			for( int j = 0 ; j < 10 ; j ++ )
			{
				if( segTree[now << 1].lazy[j] == i ) ns1[j] = segTree[now].lazy[i];
				if( segTree[now << 1 | 1].lazy[j] == i ) ns2[j] = segTree[now].lazy[i];
			}
			cnt1[segTree[now].lazy[i]] += segTree[now << 1].cnt[i];
			cnt2[segTree[now].lazy[i]] += segTree[now << 1 | 1].cnt[i];
			cnt1[i] -= segTree[now << 1].cnt[i];
			cnt2[i] -= segTree[now << 1 | 1].cnt[i];
		}
		segTree[now].lazy[i] = i;
	}
	for( int i = 0 ; i < 10 ; i ++ )
		segTree[now << 1].lazy[i] = ns1[i], segTree[now << 1 | 1].lazy[i] = ns2[i],
		segTree[now << 1].cnt[i] = cnt1[i], segTree[now << 1 | 1].cnt[i] = cnt2[i];
}

void upt( const int now )
{
	#ifdef _DEBUG
	segmentTreeNode &node2 = segTree[now];
	#endif
	for( int i = 0 ; i < 10 ; i ++ ) 
		segTree[now].cnt[i] = segTree[now << 1].cnt[i] + segTree[now << 1 | 1].cnt[i];
}

void build( const int now, const int left, const int right )
{
	segTree[now].l = left, segTree[now].r = right;
	for( int i = 0 ; i < 10 ; i ++ ) segTree[now].lazy[i] = i;
	if( isLeaf( now ) )
	{
		for( int i = 0 ; i < 10 && p[i] <= a[left] ; i ++ )
			segTree[now].cnt[( a[left] / p[i] ) % 10] += p[i];
		return ;
	}
	build( now << 1, left, ( left + right ) >> 1 );
	build( now << 1 | 1, ( ( left + right ) >> 1 ) + 1, right );
	upt( now );
}

void update( const int now, const int segL, const int segR, const int sta, const int ed )
{
	#ifdef _DEBUG
	segmentTreeNode &node1 = segTree[now];
	#endif
	if( segR < segTree[now].l || segTree[now].r < segL ) return ;
	if( segL <= segTree[now].l && segTree[now].r <= segR )
	{
		if( sta == ed ) return ;
		segTree[now].cnt[ed] += segTree[now].cnt[sta], segTree[now].cnt[sta] = 0;
		int tmp[10];
		for( int i = 0 ; i < 10 ; i ++ ) tmp[i] = segTree[now].lazy[i];
		for( int i = 0 ; i < 10 ; i ++ )
			if( segTree[now].lazy[i] == sta )
				tmp[i] = ed;
		for( int i = 0 ; i < 10 ; i ++ )
			segTree[now].lazy[i] = tmp[i];
		return ;
	}
	if( isLeaf( now ) ) return ;
	normalize( now );
	update( now << 1, segL, segR, sta, ed );
	update( now << 1 | 1, segL, segR, sta, ed );
	upt( now );
}

LL query( const int now, const int segL, const int segR )
{
	#ifdef _DEBUG
	segmentTreeNode &node3 = segTree[now];
	#endif
	if( segR < segTree[now].l || segTree[now].r < segL ) return 0;
	if( segL <= segTree[now].l && segTree[now].r <= segR )
	{
		LL tmp = 0;
		for( int i = 0 ; i < 10 ; i ++ )
			tmp += 1ll * segTree[now].cnt[i] * i;
		return tmp;
	}
	if( isLeaf( now ) ) return 0;
	normalize( now );
	upt( now );
	LL tmp = query( now << 1, segL, segR );
	return tmp + query( now << 1 | 1, segL, segR );
}

signed main()
{
	p[0] = 1;
	for( int i = 1 ; i < 10 ; i ++ ) p[i] = p[i - 1] * 10;
	read( N ), read( Q );
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( a[i] );
	}
	build( 1, 1, N );
	int opt, l, r, x, y;
	for ( int i = 1 ; i <= Q ; i ++ )
	{
		read( opt ), read( l ), read( r );
		if( opt & 1 )
		{
			read( x ), read( y );
			update( 1, l, r, x, y );
		}
		else
			write( query( 1, l, r ) ), putchar( '\n' );
	}
	return 0;
}
```

---

