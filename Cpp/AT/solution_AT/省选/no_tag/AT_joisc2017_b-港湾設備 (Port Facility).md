# 港湾設備 (Port Facility)

## 题目描述

#「JOISC 2017 Day 1」港口设施


**题目译自 [JOISC 2017](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/index.html) Day1 T2「[港湾設備](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d1.pdf)（[Port Facility](https://www.ioi-jp.org/camp/2017/2017-sp-tasks/2017-sp-d1-en.pdf)）」**

JOI 港口虽然很小，却非常繁忙。  
JOI 港口放置集装箱的结构可视为两个本质不同的栈。每天从船上卸下的集装箱会被压入某个栈，而被运出港口的集装箱则从栈顶弹出。  
今天 JOI 港口会迎来 $N$ 个集装箱，它们在今天内会被运出港口。今天出入口有 $2N$ 条记录，每条记录都表示一个集装箱到港或离港。  
第 $i$ 个集装箱 $(1\le i\le N)$ 的到港记录为 $A_i$，离港记录为 $B_i$。  
我们把 $N$ 个集装箱分别放在哪个栈称为一个方案。求放置集装箱的方案数$\bmod (10^9+7)$。

## 说明/提示

为了方便叙述，将这两个栈分别称为 A 和 B 。  
四种方案分别为：ABAA（第 $1$ 个集装箱放在 A，第 $2$ 个集装箱放在 B，以此类推），ABAB，BABA，BABB。

#### 样例输入 2
```plain
3
1 4
2 5
3 6
```

#### 样例输出 2
```plain
0
```

#### 样例输入 3
```plain
5
1 4
2 10
6 9
7 8
3 5
```

#### 样例输出 3
```plain
8
```

#### 样例输入 4
```plain
8
1 15
2 5
3 8
4 6
14 16
7 9
10 13
11 12
```

#### 样例输出 4
```plain
16
```


对于所有数据，$1\le N\le 10^6, 1\le A_i, B_i\le 2N(1\le i\le N), A_1\ldots A_N$ 和 $B_1\ldots B_N$ 这 $2N$ 个整数互不相同。

感谢 Planet6174 提供的翻译

# 题解

## 作者：bikuhiku (赞：10)

~~看了大佬的题解，并没有完全明白，然后就自己琢磨最劣解的 biku 是屑~~

我们首先想到了 $O\left(n^2 \alpha\left(n\right)\right)$ 的暴力：

发现两个物品 $i,j$，一旦 $j$ 比 $i$ 进得晚，出得也晚，那就不能把 $j$ 放在 $i$ 上面，也就是 $i,j$ 要分别装在两个集装箱中，此时 $a_j < a_i < b_j < b_i$。

这样一些物品之间就构成了矛盾关系，这样的物品之中，一旦有一个物品确定了位置，其他的物品的位置也就确定了。

于是我们把物品分组，每一组物品不对外产生影响（没有组外的矛盾），若组数为 $cnt$，则答案为 $2^{cnt}$。

那如何判断无解呢？

很显然，若三个物品 $i,j,k$ 之间，$i$ 与 $j$ 有矛盾，$k$ 同时与 $i,j$ 有矛盾，那就无解了。因为 $i,j$ 肯定各占一个集装箱，剩下的 $k$ 就没有地方去了。

可以尝试用并查集维护：一旦 $i,j$ 有矛盾，合并 $(i+n,j)$，$(i,j+n)$，表示 $i,j$ 不能在同一堆。最后判断 $i$ 和 $i+n$ 是否在同一堆，如果是则表明 $i$ 两个集装箱都不能放，回到了刚才讨论的物品 $k$ 的情况了。不然，统计最后维护的并查集形成的堆数 $cnt$，$ans = 2^{cnt}$。

我们不满足于暴力的时间复杂度，开始思考优化：

很显然如果我们先对每个物品以 $a_i$ 为维度排序，那么再找与物品 $i$ 矛盾的物品时，只需在 $i$ 之前的物品中寻找满足 $b_j \in (a_i,b_i)$ 的物品 $j$ 即可。

这不就是区间修改嘛，线段树维护！在区间 $(a_i,b_i)$ 打一个 $tag = i+n$，表示这个区间的元素需要与 $i+n$ 合并不就好了。

但是麻烦不小……

1. 如何合并 $tag$

如果我们单纯的只是把 $tag$ 往下推，或是简单的用 $vector$ 记录的话，时间复杂度是不会有什么改变的，只有 $tag$ 有可合并性的时候才可做到单次修改 $\log n$。

其实想法很简单，只要把之前的 $tag$ 与现在的 $tag'$ 在并查集上合并一下就好了，然后随便留一个在这里就行。

2. 空位问题

其实线段树上很多地方是没有填满的，如果你在一个没有数的区间做 $tag$ 合并，会假掉。

想法也不是很难，动态开点就好了，这样我们就知道了哪些地方什么东西也没有，在这种地方不去加 $tag$ 就好了。

其实也不是很麻烦，至少思路比较好想。

```cpp
#include <iostream>
#include <algorithm>
const int N = 2e6+10;
int n, q;
int ab(int _x) {
	return _x > n ? _x-n : _x+n;
}
template<const int element_tot>
class DSU {
	private : 
		int anc[element_tot];
		int size[element_tot];
		int help_x, help_y;
	public : 
		void init(int initial_size) {
			for(register int i = 1;i <= initial_size;++i) {
				anc[i] = i;
				size[i] = 1;
			}
		}
		int get_anc(int site) {
			if(anc[site] != site) 
				anc[site] = get_anc(anc[site]);
			return anc[site];
		}
		void merge(int site_x,int site_y) {
			// std :: cout << "merge >> " << site_x << " " << site_y << std :: endl;
			help_x = get_anc(site_x);
			help_y = get_anc(site_y);
			if(size[help_x] > size[help_y]) 
				anc[help_y] = help_x;
			else 
				anc[help_x] = help_y;
		}
		bool same_belong(int site_x,int site_y) {
			return get_anc(site_x,site_y);
		}
};
DSU<N<<1> dsu;
template<const int seg_tot>
class SEGMENT_TREE {
	private : 
		struct SEG {
			int lid, rid;
			int tag;
		} seg[seg_tot<<2];
		int current_size;
		int root;
	public : 
		#define tag(id) seg[id].tag
		#define lid(id) seg[id].lid
		#define rid(id) seg[id].rid
		void download(int id) {
			if(!tag(id)) 
				return;
			if(lid(id)) {
				if(tag(lid(id))) {
					// std :: cerr << "D :: let >> " << tag(id) << " " << tag(lid(id)) << std :: endl;
					dsu.merge(tag(lid(id)),tag(id));
					dsu.merge(ab(tag(lid(id))),ab(tag(id)));
				} else 
					tag(lid(id)) = tag(id);
			}
			if(rid(id)) {
				if(tag(rid(id))) {
					// std :: cerr << "D :: let >> " << tag(id) << " " << tag(rid(id)) << std :: endl;
					dsu.merge(tag(rid(id)),tag(id));
					dsu.merge(ab(tag(rid(id))),ab(tag(id)));
				} else 
					tag(rid(id)) = tag(id);
			}
			tag(id) = 0;
		}
		void insert(int &id,int L,int R,int pos,int val) {
			if(!id) 
				id = ++current_size;
			// std :: cerr << "insert >> " << id << " " << L << " " << R << " " << pos << " " << val << std :: endl;
			if(L == pos&&R == pos) {
				tag(id) = val;
				return;
			}
			int mid = (L+R)>>1;
			download(id);
			if(pos <= mid) 
				insert(lid(id),L,mid,pos,val);
			else 
				insert(rid(id),mid+1,R,pos,val);
		}
		void modify(int id,int L,int R,int l,int r,int val) {
			// std :: cerr << "modify >> " << id << " " << L << " " << R << " " << l << " " << r << " " << val << std :: endl;
			if(r < l) 
				return;
			if(!id) 
				return;
			if(L >= l&&R <= r) {
				if(tag(id)) {
					// std :: cerr << "M :: let >> " << val << " " << tag(id) << std :: endl;
					dsu.merge(tag(id),val);
					dsu.merge(ab(tag(id)),ab(val));
				} else 
					tag(id) = val;
				return;
			}
			int mid = (L+R)>>1;
			download(id);
			if(r <= mid) 
				modify(lid(id),L,mid,l,r,val);
			else if(l > mid) 
				modify(rid(id),mid+1,R,l,r,val);
			else {
				modify(lid(id),L,mid,l,r,val);
				modify(rid(id),mid+1,R,l,r,val);
			}
		}
		void dfs(int id,int L,int R) {
			// std :: cerr << "dfs :: " << id << " " << L << " " << R << std :: endl;
			if(!id) 
				return;
			if(L == R) 
				return;
			download(id);
			int mid = (L+R)>>1;
			dfs(lid(id),L,mid);
			dfs(rid(id),mid+1,R);
		}
		int& the_root() {
			return root;
		}
};
SEGMENT_TREE<N<<1> smt;
const unsigned long long moyn = 1000000007;
unsigned long long quick_pow(unsigned long long _a,unsigned long long _n,unsigned long long _p = moyn) {
	unsigned long long _res = 1LL;
	while(_n) {
		if(_n&1) 
			_res = _res*_a%_p;
		_a = _a*_a%_p;
		_n >>= 1;
	}
	return _res;
}
std :: pair<int,int> obt[N];
bool visit[N<<1];
int dsu_cnt;
int main() {
	// freopen("02-01.in","r",stdin);
	// freopen("test.out","w",stdout);
	scanf("%d",&n);
	for(register int i = 1;i <= n;++i) 
		scanf("%d %d",&obt[i].first,&obt[i].second);
	std :: sort(obt+1,obt+n+1);
	dsu.init(n<<1);
	for(register int i = 1;i <= n;++i) {
		smt.modify(smt.the_root(),1,n<<1,obt[i].first+1,obt[i].second-1,i+n);
		smt.insert(smt.the_root(),1,n<<1,obt[i].second,i);
	}
	smt.dfs(1,1,n<<1);
	for(register int i = 1, anc_i, anc_n;i <= n;++i) {
		anc_i = dsu.get_anc(i);
		anc_n = dsu.get_anc(i+n);
		if(anc_i == anc_n) {
			printf("0\n");
			return 0;
		}
		if(anc_i == i&&anc_n == i+n) 
			++dsu_cnt;
	}
	// std :: cerr << "to the end" << std :: endl;
	// printf("%d\n",dsu_cnt);
	printf("%llu\n",quick_pow(2LL,dsu_cnt));
	return 0;
}
```

---

## 作者：kiritokazuto (赞：8)

#  港口设施
[宣传博客(小声bb)](https://www.cnblogs.com/kiritokazuto/p/16719796.html#5104700)

可能是我见的题太少，真没看出来这个题是个二分图匹配和并查集优化建图
 首先我们可以发现什么样的区间是不合法的，假如有两个集装箱，他们分别是 $[l_1,r_1]$，$[l_2,r_2]$。
 
如果 $l_1 \le l_2 \le r_1 \le r_2$ 显然两个箱子不可能同时放在一个栈里，我想出出不去，显然不行，其他情况可以证明都可以。
     
所以我们对于不合法的区间连一条边，最后跑二分图匹配，如果有 $ans$ 个二分图，证明他们是时间上互相独立的，我们显然可以任意组合，所以最终的答案就是 $2^ {ans}$。
     
考虑如何建图

首先注意我的并查集和建图是独立的，一个是维护再栈里的连边关系 ($1$ $\sim$ $2\times n$)，一个是在原图上真正建图 ($1$ $ \sim $ $n$)，所以我连边实际上就是每次只连一条，其余冗杂的都通过并查集路径压缩合并了，优化就优化在了这里。
        
我们可以维护一个假的栈，里边存放左端点，当我扫到一个左端点对应的右端点时，显然我从我左端点的下一个左端点到栈顶都和我现在的区间应该连边。

那么我如果暴力连，最终是 $n ^ {2}$ 的显然跑不过去。

我们观察可以发现，其实那一坨左端点可以看成是同一性质的点，我只需要连接一个就可以了(因为我在扫到之后的左端点对应的右端点时又会和下一个连边，最终可以达到全部联通的效果，因为我是跑 ``dfs`` 染色，只要能染上色就行，没必要连那么多边)，我这里连接的是 $(l + 1)$ 的那个点，即是我下一个左端点，但是我要同时进行并查集的路径压缩，所以其实会跳到我并查集的祖宗的。

那么我们再连完一条边之后，应该直接调到下一个性质不同的位置，我们可以考虑维护一个链表，表示下一个可以连接的不同性质的位置，直接跳就行。

注意当我们扫到对应的右端点时应将他的左端点删除，因为对于之后的来说它已经不存在了，具体实现就是将他 ``nxt`` 设置为我的栈顶，直接跳走。

这里再讲一个很多人疑惑的问题，我对于包含的会直接跳过的，不会连边， 可以结合他人代码理解一下，我就不挂了。
        
例如
        
        
![](https://cdn.luogu.com.cn/upload/image_hosting/yqjchak8.png)



我们扫到 $1,2,3$，都是左端点，放到栈里，现在 ``top`` 是 $3$。

当我扫到 $4$ 时，它对应了 $2$，那么应该是 $2, 3$ 连接，没问题。

现在 $2$ 到 $4$ 这个区间已经结束了，那么它的 ``fa`` 成为了 $tot + 1$ 即是 $4$(现在没有这个点(第四个左端点，不是时间 $4$))。

当我扫到 $5$ 的时候它对于 $2$ 会直接连接到 $2$ 并查集里的祖宗，也就是 ``tot + 1``，是空，所以它只会和 $3$ 连边。

之后自己模就行。




---

## 作者：Iscream2001 (赞：7)

考试的时候并查集写挂了。。。还居然没有查出来。。。挂成20分。。
耻辱啊。。。

然后是题解。。。

首先比较好想的是转化成线段覆盖的问题。。如果有两个线段相交，我们就在图上把这两个线段代表的点连边。。。

然后考虑怎么判无解，有奇环就无解了。。那就黑白染色判一下嘛，搞个并查集就行了。

然后是有解的情况。。容易发现只要搞出有多少联通块，然后2的几次方就可以了。。

但是点很多，边数也很多，直接连边会T

考虑怎么维护线段相交。。。一个比较简单的想法是用一个栈，（假装支持在栈的中间位置弹栈），从左向右扫描，遇到左端点就压进栈里，遇到右端点时。。。发现左端点和右端点之间会有一些与之相交的线段，处理好只后把之前压进栈里的左端点弹掉。。。

发现这样很不科学。。在栈中间弹栈就很微妙了。。。
怎么维护这个呢。。我们用一个并查集，表示nxt(i)表示从i开始（包括i）的下一个未被弹栈的位置。。。这样就能方便的弹栈了。。

但是会发现相交的次数也很多。。。我们发现黑白染色的时候，被同一线段所交的线段颜色要么一样要么无解，于是我们在栈内在维护一个数组jump(i)表示下一个与当前位置颜色可能不同的位置。。。

然后就能过了。。。

代码

```cpp
#pragma GCC optimize("-O2")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
#include<map>
#include<bitset>
#include<ctime>
#include<cstdlib> 
#define LL long long
#define DB long double
#define pa pair<LL,int>
#define ctz __builtin_ctz
using namespace std;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void Out(LL x){
    if(x>9) Out(x/10);
    putchar(x%10+'0'); 
}
LL qpow(LL x,LL y,LL P){
    LL re=1;
    while(y){
        if(y&1) re=re*x%P;
        x=x*x%P;y>>=1;	
    } 
    return re;
}
const LL mod=1e9+7;
const int N=2e6+10;
int w[N];
int n;

int top=0;
int q[N];
int pos[N];
int fa[N],nxt[N],jp[N];
int findfa(int x){
	return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
int NXT(int x){
	return nxt[x]==x?x:nxt[x]=NXT(nxt[x]);
}
int add(int x,int y){
	int u=findfa(x),v=findfa(y);
	int uu=findfa(x+n),vv=findfa(y+n);
	if(u==v||uu==vv) return 0;
	if(u>vv) swap(u,vv);
	fa[vv]=u;
	if(v>uu) swap(v,uu);
	fa[uu]=v;
	return 1;
}
int main(){
//	freopen("down.in","r",stdin);
//	freopen("down.out","w",stdout);
	scanf("%d",&n);
	int l,r;
	for(int i=1;i<=n;++i){
		l=read();r=read();
		w[l]=i;w[r]=i;
		fa[i]=i;
		fa[i+n]=i+n;
	}
	for(int i=1;i<=n+n;++i){
		nxt[i]=i;
		jp[i]=i+1;
	}
	int x,y,z,t,flag;
	LL js=0;
	for(int i=1;i<=n+n;++i){
		//if(i%10000==0) cout<<js<<endl;
		x=w[i];
		if(!pos[x]){
			++top;
			pos[x]=top;
			q[top]=x;
		}
		else{
			y=pos[x];z=y+1;z=NXT(z);
			while(z<=top){
				flag=add(x,q[z]);
				//++js;
				if(!flag) {
					puts("0");return 0;
				}
				t=jp[z];
				jp[z]=top+1;
				z=t;
				z=NXT(z);
			}
			nxt[y]=y+1;
		}
	}
	LL ans=0;
	for(int i=1;i<=n+n;++i) if(findfa(i)==i) ++ans;
	ans>>=1;
	ans=qpow((LL)2,ans,mod);
	printf("%lld\n",ans);
	return 0;
}
/*
10
100 8 8

*/
```

---

## 作者：lanos212 (赞：6)

该题解写得很详细，图比较多，建议不怎么擅长数据结构的阅读。

## I. 初步分析得到 $O(N^2)$ 做法

下面将一个物品入栈出栈看作一个区间，具体地，如果一个物品 $i$ 在 $A_i$ 时刻入栈，$B_i$ 时刻出栈，那么这个物品在时间轴上形成一个区间 $[A_i,B_i]$。

我们先考虑如果只有一个栈，那么其入栈出栈是合法的，**当且仅当**对于里面的任意两个区间，它们**存在包含关系**或**不相交**。

从两面证明条件的充要性：

- 如果**存在两区间相交不包含**，则会有后入栈的压在先入栈的前面时，先入栈的想要出栈的情况，这是**不合法的出入栈情况**。

- 如果出现**不合法的出入栈情况**，也就是考虑当前某物品要出栈时不在栈顶，此时该物品和栈顶物品的区间必然**相交且不包含**。

那么我们可以暴力 $O(N^2)$ 枚举两个物品的区间，如果它们相交不包含，则在两物品间连一条边。

现在题目要求将每个物品放入 $A,B$ 两个集合中的一个，使得在同一个集合内的物品没有边相连。

这使我们想到二分图。

那么我们暴力建图之后，如果该图不是二分图，则一定无解，答案为 $0$。

否则答案为二分图合法黑白染色数量，我们考虑二分图的每个联通块都有恰好 $2$ 种染色方式，我们先对该二分图计算其联通块数量 $cnt$，则答案为 $2^{cnt}$。

至此，我们获得了一个 $O(N^2)$ 的做法。

## II. 减少边数，线段树优化

然而我们发现，这张图建出来，边数可能会是 $O(N^2)$ 级别的：

![](https://cdn.luogu.com.cn/upload/image_hosting/4tizfu3y.png)

所以我们如果要优化上述算法，应该从**去掉一些不必要的边**入手，毕竟我们只需要知道原图是否为二分图，并计算其连通块数量。

考虑前面 $O(N^2)$ 做法，两个物品连边的条件：

- 如果两个物品 $i,j$ 的区间 $[A_i,B_i],[A_j,B_j]$ 满足 $A_i<A_j,B_i\in[A_j,B_j]$，则 $i$ 与 $j$ 之间连边（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/cih1vw3r.png)

那么我们有一种想法：

- 我们在每个区间右端点的地方，存下其物品的编号与区间左端点位置。

- 再枚举每个区间，**查找这个区间内的右端点**，如果其对应区间的左端点在当前区间的左边，那么连边。

现在这个做法已经有了**区间查询**的雏形了，我们考虑用**线段树**进行优化：

- 我们先将所有物品区间按照左端点从小到大排序，然后按这个顺序依次加入线段树。

- 加入时，我们往包含该物品区间右端点的所有线段树上的节点里，加入这个物品区间。（如下图为加入物品区间 $[3,6]$ 的结果）

![](https://cdn.luogu.com.cn/upload/image_hosting/shredu1b.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/1324rbm4.png)

- 查询时，例如当前物品区间为 $[A_i,B_i]$，我们就在线段树上查询区间 $[A_i,B_i]$，然后在每个查询到的线段树节点内，向一个前缀的物品区间连边。（因为你加入是按照左端点从小到大加入的，具体可见下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/8zxplmx7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/zta5lsm9.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8lhin7gu.png)

- 优化前缀连边部分，我们对于一个节点内的物品区间，如果其不为当前节点中的第一个，则其连过边就可以直接删除：

![](https://cdn.luogu.com.cn/upload/image_hosting/ihqsakkr.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/i08hjtwm.png)

这样连边的正确性证明：

- 这样做原本的一条边可能被连多次，不影响图的连通性，以及是否为二分图。

- 关于一条原本应该连，而优化后没连的边（下图中橙色边），都可以被一条**长度奇偶性相同**的路径（下图中紫色路径）代替，这不改变图的连通性。

- 同时，边被路径替代不会改变图是否为二分图。因为如果图**不为二分图**，那么存在一个**奇环**，也就是存在从某一个点开始，**走奇数步走回这个点**的方案，现在在新图上，走**一条原本不存在的边**相当于走**一条不影响总路径奇偶性的路径**，这显然不影响二分图的判定。

![](https://cdn.luogu.com.cn/upload/image_hosting/dd2u7cfn.png)

对于时间复杂度的分析：

- 一次插入时间复杂度为 $O(\log N)$，总时间复杂度 $O(N \log N)$。

- 一次查询经过 $O(\log N)$ 个节点，对节点中第一个物品区间总共连 $O(N\log N)$ 条边。

- 节点中不是第一个物品区间的，在连边后就会被删除，总共连 $O(N\log N)$ 条边。

- 遍历整张图计算答案，时间复杂度 $O(N \log N)$。

综上所述，该算法时间复杂度为 $O(N \log N)$。

code（代码使用种类并查集代替遍历，复杂度和上述分析略有不同）

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int mo = 1e9 + 7;
int n, f[2000001];

inline int find(int x) {
    return (x == f[x] ? x : f[x] = find(f[x]));
}

inline void merge(int x, int y) {
    f[find(x)] = find(y + n);
    f[find(x + n)] = find(y);
}

inline bool cross(pii A, pii B) {
    return ((A.first > B.first && A.first < B.second) ^ (A.second > B.first && A.second < B.second));
}
pii a[1000001];

#define lc (x<<1)
#define rc (x<<1|1)
#define mid ((l+r)>>1)
vector<int> v[8000001];
int ed[8000001];

inline void upd(int x, int l, int r, int id) {
    v[x].push_back(id);

    if (l == r)
        return;

    if (a[id].second <= mid)
        upd(lc, l, mid, id);
    else
        upd(rc, mid + 1, r, id);
}

inline void query(int x, int l, int r, int id) {
    if (l > a[id].second || r < a[id].first)
        return;

    if (l >= a[id].first && r <= a[id].second) {
        if (!ed[x] && !v[x].empty())
            ed[x] = v[x].back();

        if (cross(a[id], a[ed[x]]))
            merge(id, ed[x]);

        while (!v[x].empty() && cross(a[id], a[v[x].back()]))
            merge(id, v[x].back()), v[x].pop_back();

        return;
    }

    query(lc, l, mid, id);
    query(rc, mid + 1, r, id);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;

    for (int i = 1; i <= n + n; ++i)
        f[i] = i;

    for (int i = 1; i <= n; ++i)
        cin >> a[i].first >> a[i].second;

    sort(a + 1, a + n + 1);

    for (int i = n; i; --i)
        upd(1, 1, n + n, i);

    for (int i = 1; i <= n; ++i)
        query(1, 1, n + n, i);

    int cnt = 0;

    for (int i = 1; i <= n; ++i)
        if (find(i) == i)
            ++cnt;

    for (int i = 1; i <= n; ++i)
        if (find(i) == find(i + n)) {
            cout << 0 << '\n';
            return 0;
        }

    int ans = 1;

    while (cnt--)
        ans = ans * 2 % mo;

    cout << ans << '\n';

    return 0;
}
```

---

## 作者：FFTotoro (赞：2)

模拟赛赛时想到的一种很简洁的做法，好想好写且只需要使用 `std::set`，故在此记录一下。

令 $l_i$ 与 $r_i$ 分别为集装箱 $i$ 的进 / 出港时间，那么本题有十分简洁的结论：如果 $\exist i\ne j$ 使得 $l_i<l_j<r_i<r_j$，那么这两个集装箱一定不能放在同一个栈内。于是 $O(n^2)$ 做法就很简单了，只需要暴力枚举 $i,j$ 并考虑建图：如果 $i,j$ 不能在同一个栈内那么将 $i,j$ 间连一条无向边；最终的图如果不是二分图必然无解，否则设连通块数量为 $c$，答案则为 $2^c$。

进一步地，对于每个集装箱，考虑其“在港时间”即 $[l_i,r_i]$：将所有集装箱按照 $l_i$ 排序后依次加入，假设当前扫到了一个区间 $[l_i,r_i]$，那么先删除所有满足 $r_j<l_i$ 的 $j$（称这个过程为**剔除**）：此时我们只需要考虑场上 $r_j<r_i$ 的所有 $j$，它们可以与 $i$ 进行连边。

考虑优化这个过程——这一些满足条件的 $j$ 对应的 $r_j$ 一定是当前存在于场上的所有 $r$ 中一段连续的元素，于是将 $i$ 对它们暴力连边后，仅取最小的 $r_j$ 对应的 $j$ 保留在场上（作为一个“代表元”），其他的扔进另一个容器 $s$ 里头（称这个过程为**挑选**）。当这个代表元 $j$ 在“剔除”过程中被删除时，用它在 $s$ 中的后继（即最小的 $r_k$ 使得 $r_k>r_j$ 对应的 $k$）作为新的代表元，解法正确性就可以得到保证。

均摊一下上述所有的操作只会进行 $O(n)$ 次，而我们使用 `std::set` 维护，所以时间复杂度为 $O(n\log n)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int p=1e9+7;
inline int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=1ll*r*a%p;
    a=1ll*a*a%p,b>>=1;
  }
  return r;
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,q=0; cin>>n;
  vector<pii> a(n);
  for(auto &e:a){
    cin>>e.first>>e.second;
    e.first--,e.second--;
  }
  sort(a.begin(),a.end());
  set<pii> s1,s2;
  /* s1 为所有可以留在场上的元素：
     换句话说，就是包含了所有在“挑选”过程中保留或者没保留的所有元素；
     它的作用与上文中所述的“容器 s”的作用相同。
     s2 为所有的代表元和还没有被连边的元素。
  */
  vector<vector<int> > g(n);
  for(int i=0;i<n;i++){
    int l,r; tie(l,r)=a[i];
    while(!s1.empty()&&s1.begin()->first<l)s1.erase(s1.begin());
    // 清空容器 s 中应该被“剔除”的元素
    while(!s2.empty()&&s2.begin()->first<l){
      auto p=s1.lower_bound(*s2.begin());
      if(p!=s1.end())s2.emplace(*p);
      s2.erase(s2.begin());
    } // “剔除”代表元的过程，要从 s1 中找后继
    auto p=s2.begin();
    if(p!=s2.end()&&p->first<r){
      int ps=p->second;
      g[i].emplace_back(ps);
      g[ps].emplace_back(i);
      for(auto it=next(p);it!=s2.end()&&it->first<r;it=s2.erase(it)){
        g[i].emplace_back(it->second);
        g[it->second].emplace_back(i);
      } // “挑选”过程，暴力连边，并删除非代表元
    }
    s1.emplace(r,i),s2.emplace(r,i); // 将其加入
  }
  vector<int> c(n,-1);
  auto dfs=[&](auto &&self,int u)->void{
    for(int i:g[u]){
      if(c[i]<0)c[i]=!c[u],self(self,i);
      else if(c[i]==c[u])cout<<"0\n",exit(0);
    }
  }; // 二分图染色
  for(int i=0;i<n;i++)
    if(c[i]<0)c[i]=0,dfs(dfs,i),q++;
  cout<<qpow(2,q)<<endl;
  return 0;
}
```

---

## 作者：yuanruiqi (赞：2)

观察到样例输出都是二的幂。考虑两个货物不能使用同一个栈的情况，当且仅当它们在栈中停留的时间段互不包含但存在交集。优化建图可以做到配合大常数的 $O(n\log^2n)$ 复杂度。注意到不能和货物 $x$ 并存的货物 $y\in S_x$，则 $S_x$ 一定是某个栈的子集。考虑并查集合并，这样 $x$ 只要和 $S_x$ 中任意一个代表元 $y$ 标记冲突即可。对所有货物的出栈时间从后往前扫描线，记当前考虑到 $x$，则用优先队列保留一些 $r_y\gt r_x,l_y\lt r_x$ 的货物 $y$。每一次合并操作相当于对所有 $l_y\gt l_x$ 的一段区间内的 $y$ 合并成一个等价类。并在队列中保留一个 $l$ 最大的货物作为代表元。 当队列中某个 $l_y\gt r_x$ 时，从队列删除 $y$，并在 $y$ 所在的等价类中找到一个 $l$ 次小的 $y$ 加入到队列作为新的代表元。复杂度瓶颈存在于并查集合并时，维护优先队列合并，可以使用 `__gnu_pbds` 中的 `priority_queue` 实现 $O(1)$ `join` 操作。复杂度 $O(n\log n)$。

---

## 作者：喵仔牛奶 (赞：2)

没找到 set 写的，来发一篇。

# Solution

## Part I

发现一条线段放入一个栈后，和它相交的线段就只能放到另一个栈里，这就是二分图黑白染色模型。将相交的线段连边，若不能染色则答案为 $0$，否则记连通块数为 $ct$，答案为 $2^{ct}$。

考虑暴力建图。枚举右端点，对于 $l_i<l_j<r_i<r_j$ 钦定在枚举到 $j$ 时建边。维护集合 $S$，从左到右扫描端点：若是左端点，将其加入 $S$；若是右端点，记该点对应的左端点为 $l$，向 $S$ 中所有 $>l$ 的端点连边，然后在 $S$ 中删除 $l$。

这样有 $\mathcal{O}(n^2)$ 条边，显然过不了。

## Part II

观察到一个右端点向 $[l,r]$ 中的点连边后，这些点的颜色就一样了，因而只要对其中一个连边即可。问题便转换成如下：
- 操作一：给出 $x$，加入 $x$ 这个点和连续段 $[x,x]$。
- 操作二：给出 $x$，删除 $x$ 这个点，并且更新相关的连续段。
- 操作三：给出 $x$，取出所有 $r>x$ 的连续段 $[l,r]$，最后将它们合成为一段。

对于操作三，一个连续段只会被至多遍历一次，所有总共遍历的连续段只有 $\mathcal{O}(n)$ 个（类似珂朵莉树的复杂度分析）。

具体地，仍然维护 $S$，每次遇到右端点时，记这个区间为 $[x,i]$，进行如下操作：
- 取出包含 $x$ 的连续段 $[l,r]$，从连续段集合中删除。
- 若 $x=l$，将 $l$ 变为 $S$ 中第一个大于 $x$ 的数，没有则为 $n+1$。
- 若 $x=r$，将 $r$ 变为 $S$ 中第一个小于 $x$ 的数，没有则为 $0$。
- 若 $l\leq r$，再把 $[l,r]$ 放回连续段集合。
- 若 $[l,r]$ 被放了回去，枚举所有满足 $p\geq l$ 的连续段 $[p,q]$，连边 $(p,x)$。
- 删除所有枚举的 $[p,q]$，记 $k$ 为其中最大的 $q$，将 $[l,q]$ 加入连续段集合。

这样就只有 $\mathcal{O}(n)$ 条边，最后跑一遍二分图染色就好了。

时间复杂度 $\mathcal{O}(n\log n)$。

---

## 作者：Piwry (赞：1)

## 解析

可以发现，有交叉的区间所属的集装箱是不能放在同一个栈的；因此对所有有交叉的区间连边，就能得到一张图，并且我们要在上面做 $2-$ 染色

首先要想到能 $2-$ 染色 的图一定是一个**二分图**

因此我们只需建图后确认各连通块是否全是二分图。如果有一个连通块不是二分图就违法，否则答案就是 $2^C$，其中 $C$ 是连通块个数

### 朴素建图

可以考虑用以下的方式：

先将左端点和右端点按位置存到一个数组里，得到一个由货箱编号组成的序列；其中每个数字第一次出现是其入栈点（左端点），第二次出现是其出栈点（右端点）

我们规定对于类似 `A_B_A_B` 的交叉区间，只在 `A` 时与 `B` 连边

这样，对于每个区间 $[a_l, a_r]$，我们只需找到 $[a_l, a_r]$ 内所有右端点大于 $a_r$ 的左端点 $b$，并将 $a$ 与 $b$ 连边即可

可以考虑用一个顺序表维护左端点。按顺序遍历序列，当遇到左端点时，将其从表末尾加入；当遇到右端点时，设该右端点所属的编号为 $a$，我们将表内 $a_l$ “右侧” 的所有元素与 $a$ 连边，并且删除 $a_l$。可以知道这样连边是不多不少的

但边数是 $n^2$ 的，会挂

### 建图优化

首先注意到，在一张非二分图中删去一些边，可能使它仍不为二分图。具体来说，只要保留图中的一个奇环即可。这是我们优化建图的理论

考虑我们建图的过程：

![1](https://cdn.luogu.com.cn/upload/image_hosting/ar46k1o0.png)

（图片 [来自](https://yhx-12243.github.io/OI-transit/records/uoj356%3Bloj2391%3Bac2534.html)）

考虑 $[\alpha, \beta]$ 的这段区间（事实上我们每次连边都是向一段区间的左端点连，不过**不包含已被删除的左端点**）。在我们向其第一次连边时，就已经限定了这些左端点的颜色相同；因此在第二次向这段区间（的一部分）连边时，只需连其中的一个点（例如图中 $\alpha$）就行了

&nbsp;

一种直接的思路是将这段区间（参考图中绿色区间）中的元素全部删去，只贪心地留下 “下标” 最大的那个（参考图中 $\beta$）。但注意到 $\beta$ 这个代表结点**是有可能被删去的**

比较粗暴的解决方案是，直接用一个可并堆维护同色区块的元素，堆顶为下标最大的结点；再以堆顶的元素的下标作为在平衡树中的 key 值，用平衡树维护这些堆

每次加入左端点时，就将这个左端点作为一个堆插入平衡树；每次遍历到右端点 $a_r$ 时，就将连边的堆都合并，并将 $a_l$ 所在的堆从平衡树弹出，并将 $a_l$ 从堆中删除，维护堆顶，再将堆放回平衡树

若连边次数为 $n$，这样做的复杂度是 $O(n\log n)$ 的

&nbsp;

还有一种思路是将同色的元素直接用并查集维护，并在并查集上维护一个指针，用来跳过这整个同色区块

但发现因为表中的元素可能会被删除，每个同色区块维护的指针有可能会失效。因此考虑不显式地删除元素，而是同样利用并查集跳过**被删除元素的区块**（连续的被删除的元素）

具体来说，每次加入左端点时，直接将这个左端点加入顺序表；每次遍历到右端点 $a_r$ 时，就将 $a_l$ 右侧的同色区块（注意 $a_l$ 可能**恰好在某个区块的中间**部分，但对于我们要做的操作没有太大影响）都和 $a$ 连边，连边时利用两个并查集跳过不需要重复连边和已被删除的元素，并合并途中的同色区块，最后再将 $a_l$ 在维护删除元素的区块的并查集中尝试与 $a_l$ 左/右的元素合并（需要左/右的元素也已被删除）

若连边次数为 $n$，这样做的复杂度是 $O(n)$ 的

&nbsp;

最后再分析下连边的复杂度

对于每个 $a$（货箱）在右端点 $a_r$ 处的连边，除了连的第一条边外，此后每一次连边都会**合并同色区间**。其中不合并区间的连边最多只有 $n$ 次；合并区间的连边次数可以参考线段树的边情况，至多也是 $n$ 次。于是总的连边次数就是 $O(n)$（粗略预估一下应该是约 $3n$ 条无向边，不过按数据的运行情况来看貌似是不到 $2n$ 条无向边的）

### 几句闲扯

另外两篇题解（我发这篇题解时）并没有维护同色区块的并查集，而是在表中的每个元素上储存一个 “下一个可能连边” 的元素位置的指针。貌似**有效指针**总是储存在每个同色区块最左的有效元素上（值得一提的是，在每个小区间被合并成大区间时，每个小区间的指针还会被最后更新一次，更新成大区间应有的指针）

当某同色区块最左的元素被删除时，合并区块的操作貌似恰好会将新的区块最左的有效元素的指针更新。但当某同色区块从中间被访问时，合并区块的操作就会把新的有效指针存于区块中间的某个元素上，导致最左的元素的指针过时；于是在下次连边时，就有可能多连边

参考 hack：

```
Hack:
[1]. 删区间最左元素：
7
7 1 2 3 1 4 5 6 4 7 2 3 5 6
[2]. 从中间截断区间（hack 成功）：
7
7 2 3 1 4 2 5 6 1 7 3 4 5 6
```

示意图：

![hack](https://cdn.luogu.com.cn/upload/image_hosting/3syen29w.png)

（讲得可能有些抽象）

不过尚不清楚这个问题对程序效率的影响大不大X

## CODE

这里是并查集版本

```cpp
#include <cstdio>
#include <iostream>
using std::max;

const int MAXN =1e6+50, M =1e9+7;

/*------------------------------Math------------------------------*/

int Pow(int x, int k){
	int ans =1;
	for(; k; x =1ll*x*x%M, k >>=1)
		if(k&1)
			ans =1ll*ans*x%M;
	return ans;
}

/*------------------------------Map------------------------------*/

int n;
int first[MAXN], tote;
struct edge{
	int net, to;
}e[4*MAXN];/*松一点的界应该是 (2*MAXN+MAXN)*2 */

inline void addedge(int u, int v){
	++tote;
	e[tote].net =first[u], first[u] =tote;
	e[tote].to =v;
	++tote;
	e[tote].net =first[v], first[v] =tote;
	e[tote].to =u;
}

bool vis[MAXN], color[MAXN];

bool dfs(const int &u){
	vis[u] =1;
	for(int l =first[u]; l; l =e[l].net){
		if(!vis[e[l].to]){
			color[e[l].to] =!color[u];
			if(!dfs(e[l].to))
				return 0;
		}
		else/*如果遇到的是父亲一定不会矛盾*/
			if(color[e[l].to] != (!color[u]))
				return 0;
	}
	return 1;
}

int work_Graph(){
	int ret =0;
	for(int u =1; u <= n; ++u)
		if(!vis[u]){
			if(!dfs(u))
				return -1;
			else
				++ret;
		}
	return ret;
}

/*------------------------------Disjoint Set------------------------------*/

struct set{
	int f[MAXN], pointer[MAXN], rank[MAXN];
	
	int find_root(const int &u){
		if(f[u] == u)
			return u;
		else
			return find_root(f[u]);
	}
	inline void merge(int u, int v){
		u =find_root(u), v =find_root(v);
		if(rank[u] < rank[u])
			u ^=v ^=u ^=v;
		f[v] =u;
		pointer[u] =max(pointer[u], pointer[v]);
		++rank[u];
	}
	inline int get_pointer(const int &u){
		return pointer[find_root(u)];
	}
}set_erase, set_color;

/*------------------------------=------------------------------*/

int array[MAXN], tot;
bool is_deleted[MAXN];

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int pos[MAXN];/*左端点在链表中的位置*/
int a[MAXN<<1];

int main(){
	n =read();
	for(int i =1; i <= n; ++i){
		int l =read(), r =read();
		a[l] =a[r] =i;
	}
	/*A_B_A_B，规定这样的交叉区间只由 A 连边*/
	for(int i =1; i <= n*2; ++i){
		int nw =a[i];
		if(pos[nw] == 0){
			++tot;
			array[tot] =nw, pos[nw] =tot;
			set_erase.f[tot] =tot, set_erase.pointer[tot] =tot;/*下一个未被删除元素的位置*/
			set_color.f[tot] =tot, set_color.pointer[tot] =tot+1;/*下一个区块的位置*/
		}
		else{
			is_deleted[pos[nw]] =1;
			++set_erase.pointer[pos[nw]];
			if(pos[nw]-1 >= 1 && is_deleted[pos[nw]-1])
				set_erase.merge(pos[nw], pos[nw]-1);
			if(pos[nw]+1 <= tot && is_deleted[pos[nw]+1])
				set_erase.merge(pos[nw], pos[nw]+1);
			for(int j =set_erase.get_pointer(pos[nw]), j_next; j <= tot; j =j_next){
				addedge(array[j], nw);
			//	j_next =set_erase.get_pointer(set_color.get_pointer(j));
				j_next =set_color.get_pointer(j);
				if(j_next <= tot)
					j_next =set_erase.get_pointer(j_next);
				if(j_next <= tot)
					set_color.merge(j, j_next);
			}
		}
	}
	int r =work_Graph();
	if(r == -1)
		puts("0");
	else
		printf("%d\n", Pow(2, r));
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2017B 题解



## 题目大意

> 有 $n$ 个物品和两个栈（后进先出），每个物品可能进入其中某个栈，现已知 $n$ 个物品的进出栈顺序，求有多少种安排物品入栈出栈的方式满足顺序要求。
>
> 数据范围：$n\le 1\times 10^6$。



## 思路分析

假如我们把每个栈的入栈出栈时间看成一个线段的话，那么同一个栈中的线段要么不相交要么包含，因此不能在同一个栈中的物品可以写成若干组关于 $(l,r)$ 的二维偏序关系。

假如我们把不能在同一个栈中的物品相连，那么这就是一个统计 2-SAT 解数的问题，若原图是二分图则答案为 $2^b$，$b$ 为连通块个数，否则答案为 $0$。

注意到题目中的二维偏序限制关系可以用主席树优化建图，然后用扩域并查集统计答案。

下面简单讲一下如何实现解题目中的 2-SAT：

- 首先建出主席树，把每个线段挂到对应的主席树的叶子节点上，并把这两个节点设为同色。
- 对于每个二维偏序限制，从对应线段节点连到主席树某个区间节点上，并把这两个节点设为异色。
- 把所有被连边的主席树区间节点取出，将这些节点的子树全部设为同色。

前两步并查集就可以直接做，而第三步需要离线出所有节点再 BFS 一遍以保证复杂度。

时间复杂度 $\mathcal O(n\log n\alpha(n\log n))$，注意实现常数。



## 代码呈现

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0; char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
}
using namespace std;
const int MAXN=1e6+1,MAXV=MAXN*24,MOD=1e9+7;
int n,siz;
struct Node {
	int ls,rs;
}	tree[MAXV];
int tar[MAXN]; 
inline void Append(int id,int u,int l,int r,int src,int &des) {
	tree[des=++siz]=tree[src];
	if(l==r) { tar[id]=des; return ; }
	int mid=(l+r)>>1;
	if(u<=mid) Append(id,u,l,mid,tree[src].ls,tree[des].ls);
	else Append(id,u,mid+1,r,tree[src].rs,tree[des].rs);
}
vector <int> sec[MAXN];
inline void Link(int u,int ul,int ur,int l,int r,int pos) {
	if(ul>ur||!pos) return ;
	if(ul<=l&&r<=ur) { sec[u].push_back(pos); return ; }
	int mid=(l+r)>>1;
	if(ul<=mid) Link(u,ul,ur,l,mid,tree[pos].ls);
	if(mid<ur) Link(u,ul,ur,mid+1,r,tree[pos].rs);
}
struct Interval {
	int l,r;
}	a[MAXN];
int root[MAXN],dsu[MAXV<<1],rnk[MAXV<<1];
inline int find(int x) {
	int u=x,fa;
	while(dsu[u]!=u) u=dsu[u];
	while(x!=u) fa=dsu[x],dsu[x]=u,x=fa;
	return u;
}
inline void merge(int u,int v) {
	u=find(u),v=find(v);
	if(u==v) return ;
	if(rnk[u]<rnk[v]) swap(u,v);
	dsu[v]=u,rnk[u]+=(rnk[u]==rnk[v]);
}
bool vis[MAXV],inq[MAXV<<1];
signed main() {
	siz=n=read();
	vector <int> rp;
	for(int i=1;i<=n;++i) a[i].l=read(),a[i].r=read(),rp.push_back(a[i].r);
	sort(a+1,a+n+1,[&](Interval u,Interval v) { return u.l<v.l; });
	sort(rp.begin(),rp.end());
	for(int i=1;i<=n;++i) {
		int lid=lower_bound(rp.begin(),rp.end(),a[i].l)-rp.begin()+1;
		int rid=lower_bound(rp.begin(),rp.end(),a[i].r)-rp.begin()+1;
		Link(i,lid,rid-1,1,n,root[i-1]);
		Append(i,rid,1,n,root[i-1],root[i]);
	}
	iota(dsu+1,dsu+siz*2+1,1);
	fill(rnk+1,rnk+siz*2+1,1);
	auto equal=[&](int u,int v) {
		merge(u,v),merge(u+siz,v+siz);
		if(find(u)==find(u+siz)||find(v)==find(v+siz)) puts("0"),exit(0);
	};
	auto diff=[&](int u,int v) {
		merge(u,v+siz),merge(u+siz,v);
		if(find(u)==find(u+siz)||find(v)==find(v+siz)) puts("0"),exit(0);
	};
	queue <int> Q;
	for(int i=1;i<=n;++i) {
		diff(tar[i],i);
		for(int u:sec[i]) equal(i,u),Q.push(u),vis[u]=true;
	}
	while(!Q.empty()) {
		int u=Q.front(); Q.pop();
		if(u<=n) continue;
		for(int v:{tree[u].ls,tree[u].rs}) if(v) {
			equal(u,v);
			if(!vis[v]) Q.push(v),vis[v]=true;
		}
	}
	int ans=1;
	for(int i=1,i0,i1;i<=n;++i) {
		i0=find(i),i1=find(i+siz);
		if(i0==i1) {
			puts("0");
			return 0;
		} else if(!inq[i0]&&!inq[i1]) {
			ans=ans*2%MOD;
			inq[i0]=inq[i1]=true;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：LlLlCc (赞：0)

我们先考虑两种数的情况，不难发现只有$1212$这种情况意味着$1$和$2$不能放在同一港口，$1122$，$1221$这两种是不需要考虑的

然后我们把这种相交且不包涵的区间连边，就成了多个团，判断每个团是否成立只需要dfs二分图染色即可。因为每个团都互不影响，所以答案就是$2^N$（$N$为团数）

这样$O(N^2)$的做法就出来了，对每一个编号$i$，从左边$L_i$向右边$R_i$枚举，对所有只有左端点在区间内的点连边。再跑一遍二分图染色

不过这样是过不了$1e6$的，我们考虑优化

可以发现，每一次连边都是对一段区间内大部分点连边，给这些点染成同一种颜色。

![](https://cdn.luogu.com.cn/upload/image_hosting/zorcn9l2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样会使得一些区间被大量染色，而且还是染成同一种颜色，这样的操作十分不合理，我们只需要染一次就够了

对染成同一颜色的区间并查集维护，这样就只会染一次了（有点像[P4473 [国家集训队]飞飞侠](https://www.luogu.com.cn/problem/P4473)的并查集优化做法）

建好图后dfs二分图染色就好了

## code
```
#include<bits/stdc++.h>
#define maxn 4000005
#define ll long long
using namespace std;
const ll TT=1e9+7;
int n,a[maxn],b[maxn],N,tot,lnk[maxn],nxt[maxn],Nxt[maxn],pos[maxn],son[maxn],ans,fa[maxn],cnt[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline int Getfa(int x){return fa[x]==x? x:fa[x]=Getfa(fa[x]);}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void dfs(int x){
	for (int i=lnk[x];i;i=nxt[i]){
		if (cnt[son[i]]==cnt[x]){printf("0");exit(0);}
		else if (cnt[son[i]]) continue;
		cnt[son[i]]=cnt[x]^1;dfs(son[i]);
	}
}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[read()]=a[read()]=i;
	n<<=1;
	for (int i=1;i<=n;i++) fa[i]=i,Nxt[i]=i;
	for (int i=1;i<=n;i++){
		if (!pos[a[i]]){b[pos[a[i]]=++N]=a[i];continue;}
		for (int j=fa[pos[a[i]]]=Getfa(pos[a[i]]+1),k;j<=N;j=k){
			add(b[j],a[i]);add(a[i],b[j]);
			k=Getfa(Nxt[j]+1);Nxt[j]=N;
		}
	}
	for (int i=1;i<=n>>1;i++) if (!cnt[i]) cnt[i]=2,ans++,dfs(i);
	ll Ans=1;
	for (int i=1;i<=ans;i++) Ans=Ans*2%TT;
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：LinkWish (赞：0)

原题可以转化成每个线段对与自己有交集且不被自己包含且不包含自己的线段建边，如果建出来的图是二分图，那么答案就是连通块数量，否则答案就是 $0$。

这个转化不难，难在建边。暴力建边显然边数太多了，所以考虑优化建图。这里提供一种没有思维难度但是有点难码的做法：可持久化线段树优化建边。

我们先按右端点对线段排序，然后对每一个时刻建一颗线段树。假设当前时刻为 $x$，那么 $rt_x$ 这棵树里需要包含所有左端点小于等于 $x$ 的线段的编号，显然这个可以扫一遍 $2\times n$ 个时刻，每找到一个左端点就将树中当前点的标记设为 $1$ 即可。注意在建初始树时，为了保证所有叶子节点同色同深度，我们需要找到第一个大于等于 $n$ 的 $2$ 的次幂，保证线段树是一颗满二叉树，这样所有的叶子节点自然就在同一深度，有同一颜色了。

考虑连边，设当前线段为 $i$，那么我们需要对所有 $l_j<l_i<r_j<r_i$，的线段建边，于是我们就在 $rt_{l_i-1}$ 里找到询问的区间，向下暴力建边，注意只给已经有点的区间建边，不然的话会误连到没有任何点的历史节点导致不该连的点被连上了。在树中找区间的时候需要注意，因为我们要保持二分图的性质，所以我们只能对和叶子节点一个颜色的点建边，如果当前区间被大区间覆盖了但是和叶子节点不是一个颜色，那么我们就要将其强行拆成两个区间到下一层去建边。建边不用真的建，只需要使用并查集判二分图即可，顺便维护连通性。

时空复杂度：

时间复杂度是 $\Theta(n\log n \times\alpha'(n\log n))$，空间复杂度是 $\Theta(n\log n+n)$，时间很充足，但是空间有点紧，但好在是 1024MB，注意一点别开太大即可。

代码：

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define fi first
#define se second
#define si static inline
using namespace std;
typedef const int ci;
typedef long long ll;
typedef __int128 li;
typedef pair<int,int> pii;
const int iinf=INT_MAX;
const ll linf=LLONG_MAX;
using namespace std;
ci N=(1<<20)+5,M=23*(1<<20)+5;
namespace Base{
	int n,tag[N<<1],p[N];
	bool got[N<<1];
	struct T{
		int l,r;
		inline bool operator < (const T an){return r<an.r;}
	}a[N];
}
using namespace Base;
namespace Dsu{
	template<ci SZ> struct dsu{
		int fa[SZ+5],sz[SZ+5];
		inline dsu(){for(int i=1;i<=SZ;i++)fa[i]=i,sz[i]=1;}
		int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);}
		void merge(int x,int y){
			x=getf(x),y=getf(y);
			if(x==y)return ;
			if(sz[x]<sz[y])swap(x,y);
			fa[y]=x,sz[x]+=sz[y];
		}
	};
	dsu<(N+M)<<1> d2;
	ci lim=N+M-5;
	si void add(ci x,ci y){
		d2.merge(x,y+lim);
		d2.merge(x+lim,y);
		if(d2.getf(x)==d2.getf(x+lim)||d2.getf(y)==d2.getf(y+lim)){
			cout<<"0\n";
			exit(0);
		}
	}
}
using namespace Dsu;
namespace Segment_tree{
#define ls(x) t[x].ls
#define rs(x) t[x].rs
	struct node{
		int ls,rs,pos,sz;
		bool ins,flag;
	}t[M];
	int rt[N<<1],cnt,amt;
	vector<int> res;
	void build(int &x,int l,int r){
		x=++cnt;
		if(l==r){
			t[x].flag=1;
			t[x].pos=l;
			return ;
		}
		t[x].pos=++amt;
		int mid=(l+r)>>1;
		build(ls(x),l,mid);
		build(rs(x),mid+1,r);
		t[x].flag=t[ls(x)].flag^1;
	}
	void insert(int &x,ci pre,int l,int r,ci goal){
		x=++cnt;
		t[x]=t[pre];
		if(l==r){
			t[x].ins=1;
			t[x].sz++;
			return ;
		}
		t[x].pos=++amt;
		int mid=(l+r)>>1;
		if(goal<=mid)insert(ls(x),ls(pre),l,mid,goal);
		else insert(rs(x),rs(pre),mid+1,r,goal);
		t[x].sz=t[ls(x)].sz+t[rs(x)].sz;
	}
	void link_down(int x,int l,int r){
		if(l==r)return ;
		int mid=(l+r)>>1;
		t[x].ins=1;
		if(t[ls(x)].sz){
			add(t[x].pos,t[ls(x)].pos);
			if(!t[ls(x)].ins)link_down(ls(x),l,mid);
		}
		if(t[rs(x)].sz){
			add(t[x].pos,t[rs(x)].pos);
			if(!t[rs(x)].ins)link_down(rs(x),mid+1,r);
		}
	}
	void ask(int x,int l,int r,int L,int R){
		if(l==r&&!t[x].ins)return ;
		if(l>=L&&r<=R&&t[x].flag){
			if(t[x].sz)res.push_back(t[x].pos);
			if(!t[x].ins)link_down(x,l,r);
			return ;
		}
		int mid=(l+r)>>1;
		if(L<=mid)ask(ls(x),l,mid,L,R);
		if(R>mid)ask(rs(x),mid+1,r,L,R);
	}
}
using namespace Segment_tree;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	amt=n;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
	sort(a+1,a+1+n);
	int up=1;
	while(up<n)up<<=1;
	for(int i=1;i<=n;i++){
		p[i]=a[i].r;
		tag[a[i].l]=tag[a[i].r]=i;
	}
	build(rt[0],1,up);
	for(int i=1,x,l,r;i<=n*2;i++){
		x=tag[i],rt[i]=rt[i-1];
		if(got[x]){
			l=lower_bound(p+1,p+1+n,a[x].l)-p;
			r=lower_bound(p+1,p+1+n,a[x].r)-p-1;
			if(r>=l){
				res.clear();
				ask(rt[a[x].l-1],1,up,l,r);
				for(int j:res)add(x,j);
			}
			got[x]=0;
		}
		else{
			got[x]=1;
			insert(rt[i],rt[i-1],1,up,x);
		}
	}
	unordered_map<int,bool> vis;
	int ans=1,mod=1e9+7;
	for(int i=1;i<=amt;i++)d2.merge(i,i+lim);
	for(int i=1,x;i<=n;i++){
		x=d2.getf(i);
		if(!vis[x])ans=ans*2%mod,vis[x]=1;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

