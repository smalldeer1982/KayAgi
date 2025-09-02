# Agent2

## 题目背景

炎炎夏日还没有过去，Agent 们没有一个想出去外面搞事情的。每当 ENLIGHTENED 总部组织活动时，人人都说有空，结果到了活动日，却一个接着一个咕咕咕了。只有不咕鸟 `Lyn_king` 一个人冒着太阳等了半个多小时，然后居然看到连 ENLIGHTENED 行动参谋都咕咕咕了，果然咕咕咕是人类的本性啊。

## 题目描述

作为一个 ENLIGHTENED 行动指挥，自然不想看到这一点，于是他偷取到了那些经常咕咕咕的 Agent 的在下来 $N$ 天的 `活动安排表`，并且叫上了你来整理。在整理过程中，ENLIGHTENED 行动指挥对你说了 $M$ 条命令，命令操作如下。
1. 输入 $0,a,b$，这代表在第 $a$ 天到第 $b$ 天，有一名 Agent 要咕咕咕。
2. 输入 $1$ $a$，这代表 ENLIGHTENED 行动指挥询问你根据目前的信息，在第 $a$ 天有多少名 Agent 会咕咕咕。

作为同是不咕鸟的你，也想要惩戒那些经常咕咕咕的人，所以，请协助完成 ENLIGHTENED 行动指挥完成整理，并且在他每次询问时，输出正确的答案。

## 说明/提示

对于 $20\%$ 的数据 $N,M \leq 10$；

对于 $40\%$ 的数据 $N,M \leq 10^3$；

对于 $60\%$ 的数据 $N,M \leq 10^5$；

对于 $100\%$ 的数据 $1 \leq a,b \leq N \leq 10^7,M \leq 4\times 10^5$。

## 样例 #1

### 输入

```
5 5
0 1 2
0 1 5
1 1
0 3 5
1 5```

### 输出

```
2
2```

# 题解

## 作者：gwx123456 (赞：24)

### 树状数组+差分 ~~虽然也可以用线段树~~
首先，你需要普及一些前缀知识：**树状数组和差分**

如果你没学过差分，就点[这里](https://gwx123456.blog.luogu.org/ci-fen)

如果你没学过树状数组，就点[这里](https://gwx123456.blog.luogu.org/solution-p2068)

**注：树状数组虽然只有一道例题，但也详细讲解了树状数组**

相信，你看完上面两个链接后就明白代码怎么写了吧。

上代码：
```
#include <bits/stdc++.h>
using namespace std;
int n,a[10000001],c[10000001],m;
int lowbit(int i){
    return i&(-i);
}
int getSum(int x){//求和
    int sum=0;
    for(int i=x;i>0;i-=lowbit(i))//树状数组的前缀和
        sum+=c[i];
    return sum;
}
void modify(int x,int delta){//改变数据
    for(int i=x;i<=n;i+=lowbit(i)) //因为前缀和是一个一个推的，所以一个儿子节点改变了，所有父亲节点也要改变 
        c[i]+=delta;
}
int main(){
    cin>>n;
    cin>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>c;
        if(c==1){
            cin>>a;
            cout<<getSum(a)<<endl;//树状数组前缀和得到单点查询
        }
        else {
            cin>>a>>b;
            modify(a,1);//差分，因为a~b加1就相当于左边的加1右边的减1（差分博客里详细讲解了差分用法）
            modify(b+1,-1);
        }
    }
    return 0;
}
```


---

## 作者：My_666 (赞：9)

本人最近刚学完树链剖分，被线段树部分搞RE到自闭，所以来切一道~~水题~~，上来就打了一个线段树出来：

### 70分代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e7 + 5;

#define ms(a) memset(a, 0, sizeof(a))

#define ls p << 1
#define rs p << 1 | 1

template<class T> void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {f |= (ch == '-'); ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	x = f ? -x : x;
	return;
}

int n, m;

int L[N * 4], R[N * 4], s[N * 4];

inline void pushup(int p) {
	s[p] = s[ls] + s[rs];
}

void build(int p, int l, int r) {
	L[p] = l, R[p] = r;
	if (l == r) {s[p] = 0; return;} 
	int m = (l + r) >> 1;
	build(ls, l, m);
	build(rs, m + 1, r);
	pushup(p);
}

void modify(int p, int k, int v) {
	if (L[p] == R[p]) {s[p] += v; return;}
	int m = (L[p] + R[p]) >> 1;
	if (k <= m) modify(ls, k, v);
	else modify(rs, k, v);
	pushup(p);
}

int query(int p, int l, int r) {
	if (L[p] == l && R[p] == r) return s[p];
	int m = (L[p] + R[p]) >> 1;
	if (r <= m) return query(ls, l ,r);
	if (l > m) return query(rs, l, r);
	return query(ls, l, m) + query(rs, m + 1, r);
}

int main() {
	read(n), read(m);
	build(1, 1, n + 1);
	int p, x, y;
	while (m--) {
		read(p);
		if (p == 0) {
			read(x), read(y);
			modify(1, x, 1);
			modify(1, y + 1, -1);
		}
		else {
			read(y);
			printf("%d\n", query(1, 1, y));
		}
	}
	return 0;
}
```

然而，一开始样例都过不了，调了半个小时，最后发现建树时只建到了 $1 $ ~ $ N$，直到最后被一位dalao看出来了，因为差分数组需要多开一个空间，所以$build(1, 1, n + 1)$就过了。

但是，万万没想到，一串$MLE$爆了出来，并且我的线段树比较~~毒瘤~~， 先把每个节点的左右儿子存起来，用空间换时间，后来发现就算写~~正常~~一点也过不了，$qwq$。

没办法，也不能就这样了，所以~~被迫~~打了个树状数组上去。

### 100分代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e7 + 5;

template<class T> void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {f |= (ch == '-'); ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	x = f ? -x : x;
	return;
}

int n, m, t[N];

inline int lowbit(int k) {
	return k & -k;
}

void add(int x, int v) {
	for (int i = x; i <= n + 1; i += lowbit(i)) t[i] += v;
} 

int sum(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) ans += t[i];
	return ans;
}

int main() {
	read(n), read(m);
	int p, x, y;
	while (m--) {
		read(p);
		if (p == 0) {
			read(x), read(y);
			add(x, 1);
			add(y + 1, -1);
		}
		else {
			read(y);
			printf("%d\n", sum(y));
		}
	}
	return 0;
}
```


希望大家做到做题先把题看完，再开始动键盘，省着到时候会一下删掉50多行代码，**$qwq$**

## 虽然没有讲解，但是至少可以让大家吸取一点做题教训，也算是不让本人昨天一个小时白费了，感谢阅读！

---

## 作者：Suuon_Kanderu (赞：7)

有树状数组的地方，就少不了线段树。有线段树的地方，就少不了分块。~~我自己编的~~

**分块是一种很容易理解数据结构，他可以维护很多的东西**~~当然我都不会~~，本题解旨在让只能得暴力分的同学AC本题！学会分块的思想以及方法，会比较详细。

- 分块的思想

	所谓分块，顾名思义，就是把一组数据分为若干块，从而提高效率。
    
    举个例子：来看一组数据1,5,6,4,5。
    我们把他分成$\sqrt{n}$个块（不同的情况块的数量不同，就是这样
 
| 编号 | 数值 | 第几块 |
| ----------- | ----------- | ----------- |
| 1 | 1 | 1 |
| 2 | 5 | 1 |
| 3 | 6 | 2 |
| 4 | 4 | 2 |
| 5 | 5 | 3 |

如果我们要让编号一到五加1，可以这样做：
	
    1. 把第一块（1）的值 暴力 加1
    2. 把中间块（2）的每个块的标记+1
    （如何打标记？只要再开一个数组，记录每一块的统一加的值即可，相信学过线段树的同学一定很熟悉）
    3. 把最后一块（3）的数值 暴力 加1

然后就是这样




|编号 | 数值 | 第几块 |
| ----------- | ----------- | ----------- | ----------- |
| 1 | 2（1+1） |1  | 
| 2 | 6 （5+1）| 1 | 
| 3 | 6 | 2 |  |
| 4 | 4 | 2 |  |
| 5 | 6 （5+1）|3  |

|第几块  | 标记 |
| ----------- | ----------- |
| 1 | 0 |
| 2 | 1（0+1） |
| 3 | 0 |


区间查询同理，只是暴力加的时候要加上打的标记。

单点查询就是把标记和数值加起来就OK。

- 具体实现
	
    实现时我们要考虑一些细节。
    
    1. 如果要操作的两个端点在一个块内，直接暴力相加。
    2. 如果左端点或右端点本来就在块的开头或末尾，就别加了。
    还是很好理解的
- 代码实现（本题
```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string.h>
using namespace std;
const int N=10000000+100;
struct fk{//分块大法 
	int num,rank;//数值，第几块 
}a[N];
int tag[N];//标记
#define rank(x) a[x].rank
#define tag(x) tag[x]
#define num(i) a[i].num
int n,bs,zo;//共有几个数，块的大小 ,总共有几个块 
int qsum(int l){
	return a[l].num + tag(rank(l));//单点查询
}
void change2(int l,int r,int add){
    for (int i=l; i<=min(rank(l)*bs,r); i++)num(i)+=add;//这个是前面的块，这里后面解释
    if (rank(l)!=rank(r))
        for (int i=(rank(r)-1)*bs+1; i<=r; i++)num(i)+=add;//这个是后面的块，这里后面解释
    for (int i=rank(l)+1; i<=rank(r)-1; i++)
        tag(i)+=add;//这个是整块处理
}
void pr(){
	printf("\tid\tnum\trank\n");
	for(int i=1;i<=n;i++)printf("\t%d:\t%d\t%d\n",i,num(i),rank(i));
	printf("\n\tid\ttag\n");
	for(int i=1;i<=zo;i++)printf("\t%d:\t%d\t\n",i,tag(i));	
}
signed main(){
	cin>>n;bs=sqrt(n);
	if(n/bs*bs==n)zo=n/bs; else zo=n/bs+1
    //会不会有不完整的块;
	int k;cin>>k;		
	for(int i=1;i<=n;i++){
		a[i].num = 0;
		a[i].rank=(i-1)/bs+1;		
	} 
	int l,r;
	while(k--){            
		int op; scanf("%d",&op);
		if(op==0){
		    scanf("%d%d",&l,&r);
            change2(l,r,1);
		}
		if(op==1) {
			scanf("%d",&l);
            printf("%d\n",qsum(l));
		}	
	} 
	return 0;
}
```
（大佬自行跳过此区域）
	解释一下处理前面的块和后面的块的代码
     min(rank(l)*bs,r)
     
       				
                    
                    
rank（l） $\times$ bs就是第 I 个块 乘上 块的大小，很容易明白，就是块的最后一个元素。
	用前面的数列，比如
    
  rank(1) $\times$ 2 = 1 $\times$2 = 2 
  
  果然是第一个块的最后一个元素。
    min()里面有个 r 是考虑左端点和右端点可能在一个块里，如果是，那么就直接暴力全加完，后面的操作其实都没执行。
    
 (rank(r)-1)*bs+1同理，就是块的第一个元素。
 
 简单粗暴
 




---

## 作者：αnonymous (赞：7)

~~哈哈哈，竟然都是用树状数组写的，那线段树的人头我就收下了~~

其实，在进入左右子树时，为防止MLE，可以不用当前位置* 2或* 2+1，这样十分浪费空间

可以记录a[i]左子树的位置为al[i]=j,这样进入左子树可以直接变为a[al[i]]
```cpp
#include <iostream>
using namespace std;
int n,m,al[20000001],a[20000001],ar[20000001],an=1;
/*
a[i]为当前区间内有多少人咕咕
al[i]为当前区间a[i]的左子树位置
ar[i]为当前区间a[i]的右子树位置
an为a现在的大小
*/
void add(int l,int r,int k,int x,int y){
	if(x<=l&&y>=r)//如果当前整个区间都会咕咕，则不用向下继续搜，直接标记
		a[k]++;
	else{
		int mid=(l+r)>>1;
		if(mid>=x){
			if(!al[k])//如果a的左子树还未分配空间
				al[k]=++an;
			add(l,mid,al[k],x,y);
		}
		if(mid+1<=y){
			if(!ar[k])//如果a的右子树还未分配空间
				ar[k]=++an;
			add(mid+1,r,ar[k],x,y);
		}
	}
}
int query(int l,int r,int k,int x){
	if(l==r)//搜到底部,返回
		return a[k];
	else{
		int mid=(l+r)>>1;
		if(mid>=x)
			return a[k]+query(l,mid,al[k],x);//a[k]为当前区间都会咕咕时,则答案需要加上a[k]和左子树中会咕咕的人数
		else
			return a[k]+query(mid+1,r,ar[k],x);
	}
}
int main(){
	int i,j,k,x,y;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>k;
		if(k){
			cin>>x;
			cout<<query(1,10000000,1,x)<<endl;
		}
		else{
			cin>>x>>y;
			add(1,10000000,1,x,y);
		}
	}
	return 0;
}
```


---

## 作者：Null_Cat (赞：3)

~~毒瘤智颓怎么光给窝颓线段树/树状数组~~

---

前置芝士：[线段树/树状数组](https://www.luogu.org/blog/NullCatsBlog/solution-p3372)

这个题非常明显能看出来（数据范围 $und$ 题目）这是一道线段树/树状数组的题目。

如果看不出来也没有关系。窝们不妨把这些日程用一个一维数组表示出来，而$date_i$表示第$i$天```咕咕咕```的人数。很显然刚开始的时候所有人都不~~是up~~咕咕咕，因此$date$的所有元素都是$0$。继续思考，从$a$到$b$有一个人```咕咕咕```维护的就是区间$date_a \to date_b$中间所有值$++$。相同的，查询就是查找单点的喏！

因为本题前面没有初始的咕咕咕的人数，因此也就不需要再$Build$了，同时也因为并不是维护的区间和这种~~毒瘤的东西~~，因此也不需要弄什么$PushUp, PushDown, lazy\_tag$这种。~~因此题解里说本题树状数组比线段树码量小特别多的都在扯淡~~

但是值得吐槽的是，本题的数组得开肥肠大，$1e6$只有$60$分，$1e7$是$95$分，到$2e7$才能满。。。~~不要问窝怎么知道的，实践出真知~~

下面贴代码，解释倒也没什么。。。$Query$和模板题不同的是本题需要把$from, to$想象成一个重合的顶点进行查询

```
#include <bits/stdc++.h>

using namespace std;

int tree[19198100 << 1], scan[11451400 << 1];

void Add(int, int, int, int, int);

int Query(int, int, int, int);

int main(int argc, char* argv[])
{
	int n, m, a, b;
	scanf("%d%d", &n, &m);
	for(register int i = 0; i < m; i++)
	{
		int md;
		scanf("%d", &md);
		if(md)
		{
			scanf("%d", &a);
			printf("%d\n", Query(1, n, 1, a));
		}
		else
		{
			scanf("%d%d", &a, &b);
			Add(1, n, 1, a, b);
		}
	}
	return 0;
}

void Add(int left, int right, int root, int from, int to)
{
	if(left >= from && right <= to)
	{
		tree[root]++;
	}
	else
	{
		int mid = (left + right) >> 1;
		if(mid >= from)
		{
			Add(left, mid, root << 1, from, to);
		}
		if(mid < to)
		{
			Add(mid + 1, right, root << 1 | 1, from, to);
		}
	}
}

int Query(int left, int right, int root, int date)
{
	if(left == right)
	{
		return tree[root];
	}
	else
	{
		int mid = (left + right) >> 1;
		if(mid >= date)
		{
			return tree[root] + Query(left, mid, root << 1, date);
		}
		else
		{
			return tree[root] + Query(mid + 1, right, root << 1 | 1, date);
		}
	}
}
```

---

## 作者：philosopherchang (赞：3)

如果只想得60分，可以右转差分，复杂度O(mn)。

正解应该就是树状数组，也不知道线段树可不可以，但在这个题里线段树应该没有树状数组跑得快。

其实在此题中树状数组也使用了差分的思想，执行"0"操作时，把a[x]+1,同时a[y+1]-1，于是我们很快的就能完成对一个区间的修改，复杂度O(1)(应该是常数，蒟蒻不太会算复杂度QwQ),可以忽略不计。对于"1"操作，我们直接返回sum(x)即可，复杂度O(logn);

树状数组的时间复杂度为O(mlongn)，比纯差分快不少。

还不明白的话左转[树状数组2](https://www.luogu.org/problemnew/show/P3368)

代码如下：

```CPP
#include<iostream>
#include<cstdio>
using namespace std;
long long a[10000001],n,m,last,now;
int lowbit(int x)//树状数组标志性操作
{
	return x&(-x);
}
void update(int x,int k)//区间修改
{
	for(;x<=n;x+=lowbit(x))
	{
		a[x]+=k;
	}
}
long long sum(int x)//单点查询
{
	long long ans=0;
	for(;x;x-=lowbit(x))
	{
		ans+=a[x];
	}
	return ans;
}
int main()
{
	cin>>n>>m;
	int w,x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&w);
		if(w==0)
		{
			scanf("%d%d",&x,&y);
			update(x,1);//差分
			update(y+1,-1);
		}
		else if(w==1)
		{
			scanf("%d",&x);
			cout<<sum(x)<<endl;
		}
	}
}
```
让我的题解过呗QwQ

---

## 作者：AC_Automation (赞：2)

先看题目描述，总结起来就是：
#### 1. 区间修改
#### 2. 单点查询

于是：

## 标准的线段树、树状数组题目。

墙裂推荐树状数组~~（只要能用）~~，码量小，空间和时间都比线段树优
#### 所以，这里只讲树状数组
这里的树状数组采用了差分和前缀和的思想，利用树状数组维护差分数组的前缀和（不懂树状数组的出门左转[这里](https://www.luogu.org/problemnew/solution/P3374)。~~话说会树状数组的还看题解干嘛~~）

久违的放代码时间：
```cpp
#include<iostream>
using namespace std;
int n,m;
long long c[100000005];
inline int lowbit(int x){return x&(-x);}//树状数组的标志
void add(int x,int t){//单点加（为什么要t看后面）
	while(x<=n){
		c[x]+=t;
		x+=lowbit(x);
	}
}
long long sum(int x){//求和
	long long ret=0;
	while(x>0){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int opt,x,y;
	for(int i=0;i<m;i++){
		cin>>opt;
		if(!opt){
			cin>>x>>y;
			add(x,1);
			add(y+1,-1);//差分，用到上面的t了~
		}
		else{
			cin>>x;
			cout<<sum(x)<<endl;
		}
	}
	return 0;
}//完结撒花！

```

---

## 作者：Hexarhy (赞：1)

真不敢相信你谷有模板题的重题……

此题为[P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)的弱化版。

本篇题解将把**重心**偏向为什么且如何通过差分来实现本题要求，因而将淡化甚至略过树状数组的相关知识。

有关树状数组入门的请看[这里](https://www.luogu.com.cn/problemnew/solution/P3374)。

---------

### 题意简述

给定长度为 $n$ 的初始序列，全部为 $0$。要求支持区间修改和单点询问。

-----------

### 解题思路

**前置知识**：

- 树状数组入门。详情点[这里](https://www.luogu.com.cn/problemnew/solution/P3374)。本题是一个小小的拓展而已。
- 差分基础知识。

我们知道，普通的树状数组维护的是一个**前缀和**数组，支持**单点修改**和**区间查询**。

但是这道题目，要我们实现**区间修改**和**单点查询**。

对于区间修改，有一种很暴力思路是：

- 遍历 $[L,R]$ 的区间，每次进行一次单点修改。

然而时间复杂度最劣为 $O(n^2\log n)$，显然这是会超时的。

想到这，学过的同学就能很敏感的想到，**差分**可以轻松解决。

----------

**提示：下面大部分内容关于差分。若您已经非常熟悉请跳过。**

举个例子：记差分数组为 $T$。

原来的序列为：

| 1 |2  | 3 | 4 |5  |
| :----------: | :----------: | :----------: | :----------: | :----------: |

差分数组为：

| 1 |1  | 1 | 1 |1  |
| :----------: | :----------: | :----------: | :----------: | :----------: |

在 $[2,4]$ 之间 $+2$，则序列为：

| 1 |4 | 5 | 6 |5  |
| :----------: | :----------: | :----------: | :----------: | :----------: |

差分数组变为：

| 1 |3 | 1 | 1 |-1  |
| :----------: | :----------: | :----------: | :----------: | :----------: |

对比发现，只有 $T_2+2$，以及 $T_5-2$。只用了两次单点修改。

推广一下：

对于序列 $a_1,a_2,a_3,\cdots,a_n$，在区间 $[L,R]$ 内加上 $\Delta$，不难发现：

- $[L,R]$ 由于加上同一个数，**相对大小是不变**的，因此 $(L,R]$ 区间内的 $T$ 不需要修改。

- 而 $T_L=a_L-a_{L-1}$，$a_{L-1}$ 大小不变，只有 $a_L$ 增加了 $\Delta$，因此 $T_L$ 增加了 $\Delta$。同理，$T_{R+1}$ 减少 $\Delta$。

通过上述方法，就可以实现只修改 $T_L$ 和 $T_{R+1}$ 共两次就完成了 $[L,R]$ 的区间修改。时间复杂度大大降低。

不过本题的修改值 $\Delta=1$ 而已。我们只需用树状数组维护这个 $T$ 。

但是对于**单点查询**，需要略微改动。

我们直接输出`query(x)`即可，因为$a_x=\sum^x_{i=1}T_i$，而树状数组询问恰好是**差分数组的前缀和**。

时间复杂度依然为 $O(n\log n)$。

----

### 参考代码

其实也就是略加改动。

**注意数组别开小了。**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=2e7+5;
int n,m;
int tree[MAXN],a[MAXN];

inline int lowbit(const int x)
{
	return x&(-x);
}

void insert(int x,const int k)
{
	while(x<=n)
	{
		tree[x]+=k;
		x+=lowbit(x);
	}
}

int query(int x)
{
	int res=0;
	while(x)
	{
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int main(int argc, char const *argv[])
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int opt,x,y,k;
		cin>>opt>>x;
		if(opt==0)
		{
			cin>>y;
			insert(x,1);
			insert(y+1,-1);
		}
		if(opt==1)
		 cout<<query(x)<<endl;
	}
	return 0;
}
```

---

## 作者：Waddles (赞：1)

树状数组

一开始写的是线段树，75ptsMLE，其实练练手挺好的，~~虽然只有75~~

先贴一下线段树代码：
```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,m,a[100005],f[40000005],tag[40000005];
inline int L(int x){
    return x<<1;
}
inline int R(int x){
    return x<<1|1;
}
void pushup(int c){
    f[c]=f[L(c)]+f[R(c)];
}
void lazy(int l,int r,int c,int s){
    f[c]+=(r-l+1)*s;
    tag[c]+=s;
}
void pushdown(int c,int l,int r){
    int mid=(l+r)>>1;
    lazy(l,mid,L(c),tag[c]);
    lazy(mid+1,r,R(c),tag[c]);
    tag[c]=0;
}
void add(int x,int y,int l,int r,int c){
    if(x<=l&&y>=r){
        f[c]+=(r-l+1);
        tag[c]++;
        return;
    }
    pushdown(c,l,r);
    int mid=(l+r)>>1;
    if(x<=mid)add(x,y,l,mid,L(c));
    if(y>mid)add(x,y,mid+1,r,R(c));
    pushup(c);
}
int query(int x,int l,int r,int c){
    if(x==l&&x==r)return f[c];
    pushdown(c,l,r);
    int mid=(l+r)>>1,sum=0;
    if(x<=mid)sum+=query(x,l,mid,L(c));
    else sum+=query(x,mid+1,r,R(c));
    return sum;
}
int main(){
    in(n);in(m);
    while(m--){
        int opt;
        in(opt);
        if(opt==0){
            int x,y;
            in(x);in(y);
            add(x,y,1,n,1);
        }
        if(opt==1){
            int x;
            in(x);
            printf("%d\n",query(x,1,n,1));
        }
    }
    return 0;
}
```

MLE主要因为f和tag两个4千万数组（此题内存125MB，512MB就够了）

所以请出树状数组

树状数组其实就是线段树砍一半，所以2千万就够了，而且不需要tag打标记

但树状数组实质上是前缀和，所以应用不如线段树广，时间复杂度相同，优势是比线段树常数小，内存小，代码好写
~~（如果写zkw线段树当我没说）~~

树状数组的区间修改需要用到差分思想

举个栗子，1~5区间加上3，只要1加上3,6减3就行了

最后统计前缀和

因为树状数组~~自带前缀和~~（实现就是靠前缀和）

所以直接差分搞就可以了

基本上算模板题，下面是code：
```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,m,f[20000005];
inline int lowbit(int x){//找x二进制最后1的位置
    return x&-x;
}
void add(int x,int y){
    while(x<=n){//修改
        f[x]+=y;
        x+=lowbit(x);
    }
}
int query(int x){
    int sum=0;
    while(x!=0){//查询
        sum+=f[x];
        x-=lowbit(x);
    }
    return sum;
}
int main(){
    in(n);in(m);
    while(m--){
        int opt;
        in(opt);
        if(opt==0){
            int x,y;
            in(x);in(y);
            add(x,1);//上面的栗子解释了
            add(y+1,-1);
        }
        if(opt==1){
            int x;
            in(x);
            printf("%d\n",query(x));//查询
        }
    }
    return 0;
}
```

---

## 作者：muller (赞：1)

因为是单点查询与区间修改

我们可以考虑差分，结果既是前缀和

修改的时候改 l 和 r+1 两个点。

l产生影响，r+1消除影响

用树状数组或线段树维护。

其实也可以不差分，直接分块的qwq

当然你也可以线段树，就有点像usaco的一道题，维护lazy标记

然后不断下穿即可

注意操作是改变不是清零

代码：

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int N = 10000005;
int n;
struct Bit {
	#define lowbit(x) x & -x
	int c[N];
	void add(int x, int v) {for (; x <= n; x += lowbit(x)) c[x] += v;}
	int query(int x) {
		int res = 0;
		for (; x; x -= lowbit(x)) res += c[x];
		return res;
	}
} bit;
int main() {
	int m, opt, l, r, x;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d", &opt);
		if (!opt) {
			scanf("%d%d", &l, &r);
			bit.add(l, 1); bit.add(r + 1, -1);
		}
		else {
			scanf("%d", &x);
			printf("%d\n", bit.query(x));
		}
	} 
	return 0;
}

```


---

## 作者：lamboo (赞：1)

### 题目大意

给定两个操作

1. $0\ x\ y$ 将$[x,y]$区间内每个数加1

2. $1\ x$询问第$x$数的值

### 正解

不难发现，$0$操作是区间加法，$1$操作是单点求和。于是，这道题就变成了树状数组和线段树的模板题。

由于线段树常数大，不写标记永久化会被卡空间。所以我选择了代码量较小的树状数组+差分~~（其实我不会标记永久化）~~。

### 代码

```cpp
#include <bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
#define N 20000001
int tree[N],n,m;
inline int sum(int x)
{
	int ans;
	while (x)
	{
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
inline void add(int x,int k)
{
	while (x<=n)
	{
		tree[x]+=k;
		x+=lowbit(x);
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int p;
		scanf("%d",&p);
		if (p==0)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			add(x,1);add(y+1,-1);
		}
		else
		{
			int x;
			scanf("%d",&x);
			printf("%d\n",sum(x));
		}
	}
	return 0;
}
```

---

