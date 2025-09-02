# [CEOI 2022] Abracadabra

## 题目描述

Tin 是一位著名的魔术师，他的一个经典魔术与洗牌有关。

Tin 会准备一套牌，总共 $n$ 张（保证 $n$ 为偶数），各编号为 $1\sim n$，一开始的时候牌是乱的且倒扣在桌子上。紧接着他开始表演洗牌，在洗牌的任意时刻，观众都可以向 Tin 询问从底往上数第 $t$ 张牌是什么牌，很显然 Tin 一定会立即回答出正确答案。

事实上，Tin 采用如下方式来完成这个魔术，首先他记下了一开始的 $n$ 张牌的顺序，接着采用如下技巧洗牌：

1. 拿起自顶向下 $\frac{n}{2}$ 张牌放在右手，自底向上 $\frac{n}{2}$ 张牌放在左手，牌的正面对着桌子。
1. 借助他的记忆，将左右手最底下的牌进行比较，将编号较小的那张牌放下，重复这个操作直到左右手一边为空。
1. 将还有牌的那只手上的所有牌放下。

请你写一个程序模拟 Tin 的魔术。

## 说明/提示

### 样例 3 解释

| 洗牌次数 |          自底向上的牌堆           |
| :------: | :-----------------------------: |
|   $0$    | $7\ 5\ 2\ 9\ 10\ 8\ 4\ 3\ 6\ 1$ |
|   $1$    | $7\ 5\ 2\ 8\ 4\ 3\ 6\ 1\ 9\ 10$ |
|   $2$    | $3\ 6\ 1\ 7\ 5\ 2\ 8\ 4\ 9\ 10$ |
|   $3$    | $2\ 3\ 6\ 1\ 7\ 5\ 8\ 4\ 9\ 10$ |

### 数据规模与约定

对于全部数据，满足 $1\le N\le 2\times 10^5$，$N$ 为偶数，$1\le Q\le 10^6$，$0\le t\le 10^9$，$p$ 为 $1\sim n$ 的排列，$1\le i\le N$。

| Subtask 编号 |       特殊限制        |   分数   |
| :----------: | :------------------: | :------: |
|   $1$	    |   $N\le 10^3$	    |   $10$   |
|   $2$	    | 每一个询问的 $t$ 相同 | 	$40$ |
|   $3$	    |   $N,Q\le 10^5$	   |   $25$   |
|   $4$	    |      无特殊限制	      |   $25$   |

## 样例 #1

### 输入

```
6 3
1 5 6 2 3 4
1 2
0 4
1 5```

### 输出

```
2
2
5```

## 样例 #2

### 输入

```
6 6
2 1 5 4 6 3
0 1
1 1
0 3
1 3
0 6
10 6```

### 输出

```
2
2
5
4
3
3```

## 样例 #3

### 输入

```
10 10
7 5 2 9 10 8 4 3 6 1
3 1
3 2
3 3
3 4
3 5
3 6
3 7
3 8
3 9
3 10```

### 输出

```
2
3
6
1
7
5
8
4
9
10```

# 题解

## 作者：Miraik (赞：15)

首先你发现归并的本质就是每轮选当前两段数中较小的那个数 $x$，然后在 $x$ 之后的一串 $<x$ 的数会被跟着选上。这启发我们按前缀最大值分段，每一段的第一个元素可以看作一个代表元。

再考虑一轮洗牌会对序列产生什么影响。容易发现，如果第 $\frac{n}{2}$ 和第 $\frac{n}{2}+1$ 个数不在一段那序列就不会再发生改变了，否则它会将这一段在它们中间分开得到新的段，再将后面的那些段向前归并。这也说明有效的洗牌轮数是 $<n$ 的。

那我们暴力维护这个过程每次需要的操作就是找到第 $k$ 个数的所在段，将一个段分裂，将一个段插入。

我们可以考虑用权值树状数组来维护这个过程，每个位置记录以 $i$ 为代表元的段长是多少，找第 $k$ 个数就树状数组二分，其他操作都是单点修改前缀求和。

总时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define mp make_pair
#define lowbit(x) (x&(-x))
using namespace std;
const int N=200005;
const int M=1000005;
int n,Q,top,a[N],nxt[N],pos[N],stc[N],c[N],ans[M]; vector<pii>q[N];
inline void update(int x,int y){ while(x<=n) c[x]+=y,x+=lowbit(x); }
inline int query(int x){ int r=0; while(x) r+=c[x],x-=lowbit(x); return r; }
inline pii find(int x){
	int pos=0,sum=0;
	for(int i=17;~i;i--)
		if((pos|(1<<i))<=n&&sum+c[pos|(1<<i)]<x)
			sum+=c[pos|(1<<i)],pos|=1<<i;
	return mp(pos+1,x-sum);
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i; stc[0]=n+1;
	for(int i=n;i;i--){
		while(top&&a[i]>a[stc[top]]) top--;
		nxt[i]=stc[top]; stc[++top]=i;
	}
	for(int i=1;i<=n;i=nxt[i]) update(a[i],nxt[i]-i);
	for(int i=1,t,k;i<=Q;i++){
		cin>>t>>k; t=min(t,n);
		q[t].emplace_back(i,k);
	}
	for(int i=0;i<=n;i++){
		for(pii j:q[i]){
			pii o=find(j.second);
			ans[j.first]=a[pos[o.first]+o.second-1];
		}
		int mid=n/2+1; pii k=find(mid);
		if(k.second==1) continue;
		int len=query(k.first)-query(k.first-1);
		update(k.first,k.second-1-len);
		for(int j=pos[k.first]+k.second-1;j<=pos[k.first]+len-1;j=nxt[j])
			update(a[j],min(pos[k.first]+len,nxt[j])-j);
	}
	for(int i=1;i<=Q;i++) cout<<ans[i]<<'\n';
	return 0;
}
```


---

## 作者：Day_Tao (赞：8)

考虑每一次操作的本质是什么，其实就是一个单次归并的过程（这也是模拟赛题面）。

让我们来模拟一下这个过程。记当前左右手牌堆分别为 $a$ 和 $b$ 两个序列，那么当比较的两个数分别为 $a_i$ 和 $b_j$ 时就有这两种情况：

- $a_i<b_j$，那么就把 $a_i$ 拿出放到答案序列中，让 $a_{i+1}$ 成为新的与 $b_j$ 比较的数，在 $a$ 序列中一直拿到某个 $a_i>b_j$ 为止。
- $a_i>b_j$，也同理，把 $b_j$ 拿出放到答案序列中，让 $b_{b+1}$ 成为新的与 $a_i$ 比较的数，在 $b$ 序列中一直拿到某个 $a_i<b_j$ 为止。

这一次操作结束之后将得到的答案序列在 $\frac{n}{2}$ 的地方分成两半，准备进行下一次操作。

可以发现这样一个性质：对于单次操作，假设当前在 $a$ 中取数，那么取的一段连续的数一定满足**第一个数大于剩下后面的数**。因为如果当前与 $a$ 比较的 $b$ 中的数大于了 $a$ 中的第一个数，那么肯定也是大于这个数之后比它小的数的。

所以我们不妨将这个序列看成是一段一段的，满足一段中的第一个数是这一段的 $\max$，每次比较都可以直接操作一段序列，而且**段内的数字之间位置相对不变**。这样得到的答案序列一定满足**每段的第一个数字单调递增**。

但是注意到下一次操作会将整个序列分为两部分，而一个段可能刚好被 $\frac{n}{2}$ 这个位置切开，这样就会断成若干段。具体的，我们对于位置 $i$ 记 $nxt_i$ 为下一个比 $a_i$ 大的数的位置，假如说原来这一段为 $[l,r]$，满足 $l\le\frac{n}{2}\le r$，那么就会断成 $[l,\frac{n}{2}],[\frac{n}{2}+1,nxt_{\frac{n}{2}+1}]\cdots$。不难发现最多会这样切 $O(n)$ 次。

考虑如何去维护分出来的这些段以及操作带来的段的修改。由于每次操作结束后的序列满足每段的第一个数字单调递增，所以考虑用第一个数字代表其所在段并记录该段长度，由于段内相对位置不变，所以说可以直接找到原序列中第一个数的位置去确定该段内其他数的位置。

而对于将序列分为两段的操作，需要找到那个 $\frac{n}{2}$ 的位置，可以考虑二分。需要动态修改，可以二分，这时我们所需要的算法就出来了：将每段的第一个数作为下标，放到树状数组上，每个点记录这个点为段首该段的长度，直接树状数组上二分出这个需要修改的位置即可。

对于查询，考虑将询问离线按照 $t$ 从小到大排序，特判 $t=0$ 的时候直接输出原序列上的值，否则增加更新轮数直到到达 $t$ 为止。不难发现，在操作最开始无法分出多的段时，这个序列就已经固定了，所以我们开个 $flag$ 记录是否到了这样的状态，更新下去没有意义了。容易发现更新次数也是 $O(n)$ 的。

一个注意点是，由于加入树状数组之后整个序列都是排好序的，所以说一开始分段加入树状数组就已经算是一次操作了。

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5,M = 1e6+5;
inline int rd(){
	int x=0,y=1;char c=getchar();for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);return x*y;
}struct Day_Tao{int t,i,id;inline bool operator<(const Day_Tao&dt)const{return t<dt.t;}}q[M];
int r[N],s[N],tp,a[N],n,m,ans[M],b[N];bool fl=0;
// b 记录 a 的逆排列
struct BIT{
	int tr[N];inline void ad(int x,int v){for(;x<=n;x+=x&-x)tr[x]+=v;}
	inline int qu(int x){if(x==0)return 0;int y=0;for(;x;x-=x&-x)y+=tr[x];return y;}
	inline int qu_(int v){int x=0,y=0;for(int i=__lg(n)+1;~i;i--)
	if(x+(1<<i)<=n&&y+tr[x+(1<<i)]<v)x+=1<<i,y+=tr[x];return x+1;}// 树状数组上二分
}tr;
inline void upd(){
	int p=tr.qu_(n/2+1),x=tr.qu(p),y=tr.qu(p-1),z=x-y,t=b[p];
    // p 表示包含 n/2+1 这个位置的段的段首的值，x,y 分别表示恰好包含和恰好不包含 n/2+1 的位置
    // z 表示 n/2+1 位置所在段的长度
	if(y==n/2){fl=1;return;}tr.ad(p,-z),tr.ad(p,n/2-y); // 该段变化：[l,r]->[l,n/2]
	for(int i=t+n/2-y;i<=t+z-1;i=r[i]){if(i<=t+z-1)tr.ad(a[i],min(r[i],t+z)-i);}//更新新加入的段
}signed main(){
	n=rd(),m=rd();for(int i=1;i<=n;i++){
		a[i]=rd(),b[a[i]]=i;while(tp&&a[s[tp]]<a[i])r[s[tp--]]=i;s[++tp]=i;//r 即上文所说的 nxt
	}while(tp)r[s[tp--]]=n+1;for(int i=1;i<=m;i++)q[i]={rd(),rd(),i};
	for(int i=1;i<=n/2;i=r[i])tr.ad(a[i],min(r[i],n/2+1)-i);
	for(int i=n/2+1;i<=n;i=r[i])tr.ad(a[i],r[i]-i);sort(q+1,q+m+1); // 初始化第一轮
	q[0].t=1;for(int i=1;i<=m;i++){
		if(q[i].t==0){ans[q[i].id]=a[q[i].i],q[i].t=1;continue;} // 直接考虑从第一轮开始更新
		for(int j=q[i-1].t;j<q[i].t;j++){if(fl)break;upd();}
		int p=tr.qu_(q[i].i);ans[q[i].id]=a[b[p]+q[i].i-tr.qu(p-1)-1];
        // 即把要求的 i 在树状数组中所在段抠出来，根据段首在原序列的位置推出 i 在原序列的位置
	}for(int i=1;i<=m;i++)printf("%d\n",ans[i]);return 0;
}
```

---

## 作者：wisp_sun (赞：7)

## 题意：

每次操作使前一半数与后一半数，以开头大小依次排序得到新序列。

多次询问操作变幻多次后某位置上的数是什么上的数是多少。

## 题解：

首先让我们来观察一下数据范围，发现 $1 \leq n \leq 2 \times 10^5,0 \leq t \leq 10^9$。

一眼看过去一头雾水，我们先来解决 $t$ 的问题。

### 引理：一个序列至多洗牌 $n$ 次，便不会再变化。

分析题目发现，洗牌相当于两个无序集合的归并排序。

每次会使其顺序按其方式逐渐有序，每次变化，$n$ 次后一定不再变化。

但暴力修改时间依旧不对，我们继续分析性质。

### 推论：两个无序序列的归并排序，相当于前缀最值数组的排序。

这个结论非常有意思，我们样例 $3$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/m3g2ea8a.png)

可以观察到每一次移动的都是一段连续区间，看其有何性质。

![](https://cdn.luogu.com.cn/upload/image_hosting/bpvpsmnk.png)

这是前缀最值的图，可以发现与以 $\frac{n}{2}+1$ 为起点分开重排是一致的且其余地方不受影响。

可以这么理解，以开头排序，不管后面多小都要在开头的后面，一个数影响其序列相对顺序的范围便是他作为前缀最值的范围，且其他数比他小一定一起（连续）放进去。

#### 将其转为前缀最值数组我们能得到两点性质：

* 当前变幻后序列（前缀最值递增）的相对位置与从小到大的前缀最值排序一样（在序列中的位置可以推出)。

* 前缀最值相同的一段，在原序列中同样是连续的。

## 简述：

用权值线段树等数据结构，维护每个前缀最值长度。

### 查询：

这样我们就可以找到寻找位置 $pos$ 在前缀最值数组的权值 $val$，记录差值，用 $val$ 在原序列中的位置加上差值得到查询值的位置。

### 修改：

初始化当前数影响范围（ST 表/单调栈）。

找到 $\frac{n}{2}+1$ 所属的区间切割。

暴力将后面一段计算长度，插入数据结构中。

### 时间复杂度：

势能分析一下：$n\log n$。

## 代码：

#### 这里我使用的是权值平衡树。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
random_device R;
mt19937 G(R());
int rd(int l,int r)
{
	return uniform_int_distribution<int>(l,r)(G);
}
namespace lzz
{
	
	int n,m;
	int root;
	int a[N];
	int stk[N],top;
	//使用权值平衡树 
	//每个权值维护长度 
	int L[N],R[N];
	struct treap
	{
		int val;
		int len;
		int ls,rs;
		int prior;
		int sum;//区间长度总和 
	}tree[N];
	void pushup(int u)
	{
		tree[u].sum=tree[tree[u].ls].sum+tree[tree[u].rs].sum+tree[u].len;
	}
	void split_val(int u,int &l,int &r,int val)
	{
		if(!u)
		{
			l=r=0;
			return ;
		}
		if(tree[u].val<=val)
		{
			l=u;
			split_val(tree[u].rs,tree[l].rs,r,val);
		}
		else
		{
			r=u;
			split_val(tree[u].ls,l,tree[r].ls,val);
		}
		pushup(u);
	}
	int merge(int u,int v)
	{
		if(!u||!v)return u|v;
		if(tree[u].prior<=tree[v].prior)
		{
			tree[u].rs=merge(tree[u].rs,v);
			pushup(u);
			return u;
		}
		else
		{
			tree[v].ls=merge(u,tree[v].ls);
			pushup(v);
			return v;
		}
	}
	int cnt;
	int new_node(int val,int len)
	{
		tree[++cnt].val=val;
		tree[cnt].len=len;
		tree[cnt].prior=rd(1,1e9);
		return cnt;
	}
	void insert(int val,int len)
	{
		int a=0,b=0;
		split_val(root,a,b,val-1);
		root=merge(merge(a,new_node(val,len)),b);
	}
	struct get
	{
		int val,dlt;//权值于其距离开头之差 
	};
	get find(int u,int size)//找到这个位置的权,与距离差 
	{
		if(!u)return get({0,0});
		if(tree[tree[u].ls].sum+tree[u].len<size)
		{
			return find(tree[u].rs,size-tree[tree[u].ls].sum-tree[u].len);
		}
		else if(tree[tree[u].ls].sum>=size)return find(tree[u].ls,size);
		else return get({tree[u].val,size-tree[tree[u].ls].sum-1}); 
	}
	int get_size(int val)
	{
		int a=0,b=0,c=0,d=0;
		split_val(root,a,b,val-1);
		split_val(b,c,d,val);
		int len=tree[c].len;
		root=merge(a,merge(c,d));
		return len; 
	}
	int get_num(int val)//找下标 
	{
		int a=0,b=0,c=0,d=0;
		split_val(root,a,b,val-1);
		split_val(b,c,d,val);
		int x=c;
		root=merge(a,merge(c,d));
		return x; 
	}
	void del(int val)
	{
		int a=0,b=0,c=0,d=0;
		split_val(root,a,b,val-1);
		split_val(b,c,d,val);
		root=merge(a,d);
	}
	void change(int val,int len)
	{
		int a=0,b=0,c=0,d=0;
		split_val(root,a,b,val-1);
		split_val(b,c,d,val);
		tree[c].len=len;
		pushup(c);
		root=merge(a,merge(c,d));
	}
	void print(int u)
	{
		if(!u)return ;
		print(tree[u].ls);
		cout<<"##"<<tree[u].val<<" "<<tree[u].len<<endl;
		print(tree[u].rs);
	}
	void check()
	{
		cout<<"**"<<endl;
		print(root);
	}
	int pos[N];
	int ans[2*N];
	int kth[N];//在原序列排名多少 
	vector<pair<int,int> >q[N];
	int main()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			pos[a[i]]=i;
		}
		a[n+1]=n+1;
		stk[++top]=n+1;//边界 
		for(int i=n;i>=1;i--)//找到后面第一个大于他的 
		{
			while(top&&a[stk[top]]<a[i])top--;
			R[i]=stk[top]-1,L[i]=i;
			stk[++top]=i;
		}
		for(int i=1;i<=n;i++)
		{
			if(L[i]<=R[i])
			{
				insert(a[i],R[i]-L[i]+1);
			}else insert(a[i],0);
			for(int j=i+1;j<=R[i];j++)insert(a[j],0);
			i=R[i];
		}
		for(int i=1;i<=m;i++)
		{
			int t,x;
			scanf("%d%d",&t,&x);
			if(t>n)t=n;
			q[t].push_back({i,x});
		}
		for(int i=0;i<=n;i++)//总变化次数最多n次 
		{
		//	check();
			for(int j=0;j<q[i].size();j++)
			{
				get now=find(root,q[i][j].second);
				ans[q[i][j].first]=a[pos[now.val]+now.dlt];
			}
			int mid=n/2+1;
			get now=find(root,mid);//找到区间 
			int r=pos[now.val]+(get_size(now.val))-1;
			change(now.val,now.dlt);//切割
			int x=pos[now.val]+now.dlt;//需要改的区间开头 
			while(x<=r)//重新获取序列前缀最值 
			{
				int len=min(r,R[x])-x+1; 
				change(a[x],len);
				x=R[x]+1;
			} 
		}
		for(int i=1;i<=m;i++)
		{
			printf("%d\n",ans[i]);
		}
		return 0;
	}
}
int main()
{
	return lzz::main();
}
```







---

## 作者：流水行船CCD (赞：6)

fhq-treap 好闪，拜谢 fhq-treap。

题解有了权值线段树和树状数组，写发平衡树算是补齐了。

## 思路1

考场思路，直接模拟，期望 $O(n^2)$。但是加入了启发式优化后实测可以跑到只有少数点超时，但是通过不了。

[记录](https://www.luogu.com.cn/record/143477266)

## 思路2

引理零：最多洗 $\min\{n,\max\{t_i\}\}$ 次牌。

证明：每次至少交换两个牌的相对位置，之后一定会被卡死或是有序。

洗牌次数不是瓶颈，考虑加速洗牌。

引理一：**一个值只会跟着它的前缀最大值走，不会发生相对移动**。所以可以把序列看成一个个块，而且这些块的前缀最大值成**升序排列**。

证明：因为如果 $x$ 的前缀最大值 $q$ 被一个更大的值 $p$ 扔到牌堆当中，即 $x<q<p$ 那么 $x$ 肯定也会被 $p$ 扔到牌堆中，而如果 $x<q>p$ 则 $x$ 根本就不会与 $p$ 比较，仍会在前缀最大值后。
  
![](https://cdn.luogu.com.cn/upload/image_hosting/quhbzwmm.png?x-oss-process=image/crop,x_200,y_50,w_400,h_300)

![](https://cdn.luogu.com.cn/upload/image_hosting/wuw4i3le.png?x-oss-process=image/crop,x_40,y_110,w_1000,h_300)

此时，看到下标和前缀最大值都是有序的，而且不是偏序，元素之间有相对顺序，可以考虑用同一棵平衡树维护相对顺序。然后就~~过了~~连样例都过不了。
  
观察样例，发现块与块的相对顺序并不是一成不变的。
  
引理二：**只有跨越 $\frac{n}{2}$ 的块会修改**。

证明：跨越 $\frac{n}{2}$ 的块会被强制切割成两部分，前一部分前缀最大值不变，后一部分会失去原有的前缀最大值，从而分裂成多个新的块，每一个新块都有独立的最大值，其他块依然是完整的。

![](https://cdn.luogu.com.cn/upload/image_hosting/8z4dbc1z.png?x-oss-process=image/crop,x_20,y_50,w_1000,h_300)

如果没有块跨越中轴线，不用更改。
  
发现切割块的过程就是反复去找到最大值，然后把最大值 $x$ 以及以后的部分全部切割出来，前缀最大值改为 $x$，这里可以使用懒标记修改前缀最大值的值，然后插入到前半部分平衡树合适的地方,这里可以把相同前缀最大值的块看作一个点，平衡树看作这些点构成的按权值排序的平衡树，在这里进行插入操作。
  
可见时间复杂度只和块的个数 $D$ 相关，而 $D \le n$，整体时间复杂度可以接受。
  
提醒：注意平衡树实现时的常数。
  
其余的看注释理解吧。

## AC Code

```cpp
#include<bits/stdc++.h>

#define in inline
#define re register
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb emplace_back
#define sort stable_sort
#define REP(i,l,r) for(register int i=l;i<=r;++i)
#define PER(i,r,l) for(register int i=r;i>=l;--i)

using namespace std;

random_device R;    
mt19937 G(R());
inline int rd(int l,int r){return uniform_int_distribution<int>(l,r)(G);}

const int inf=1e9+7;
const ll INF=1e18+7;

char buf[1<<19],*p1=buf,*p2=buf;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<19,stdin),p1==p2)?EOF:*p1++)
static inline int read() {
	register int x=0,w=1;
	register char ch=gc();
	while((ch<48||ch>57)&&ch!='-') ch=gc();
	if(ch=='-')w=-1,ch=gc();
	while(ch>=48&&ch<=57) x=(x<<3)+(x<<1)+(ch^48),ch=gc();
	return x*w;
}
static inline char readc(){
	register char ch=gc();
	while(isspace(ch))ch=gc();
	return ch;
}

namespace Code{
	const int N=2e5+7; 
	const int Q=1e6+7;
	int n,q;
	int arr[N],pri[N],pmax[N];
	int Ans[Q];
	struct lyt{int t,ith,id;}In[Q];
	bool cmp(lyt a,lyt b){return a.t<b.t;}
	
	struct box{
		int son[2];
		int pri;//随机堆权值
		int sz,val,pmax;//子树大小，当前点权值，前缀最大值
		int ma,maid;//最大值，最大值原序列编号
		int id,tg;//当前值原序列编号，覆盖前缀最大值的标记
		box(){son[0]=son[1]=pri=sz=val=pmax=id=ma=maid=tg=0;}
	}tr[N];
	int rt=0,trc=0;
#define ls tr[x].son[0]
#define rs tr[x].son[1]
	inline void pu(int x){//更新最大值和最大值编号
		tr[x].sz=tr[ls].sz+tr[rs].sz+1;
		tr[x].ma=std::max(tr[x].val,std::max(tr[ls].ma,tr[rs].ma));
		if(tr[x].ma==tr[x].val)     tr[x].maid=tr[x].id;
		else if(tr[x].ma==tr[ls].ma)tr[x].maid=tr[ls].maid;
		else if(tr[x].ma==tr[rs].ma)tr[x].maid=tr[rs].maid;
	}
	inline void pd(int x){
		if(tr[x].tg){//更新前缀最大值
			tr[ls].pmax=tr[x].tg,tr[rs].pmax=tr[x].tg;
			tr[ls].tg=tr[rs].tg=tr[x].tg;
			tr[x].tg=0;
		}
	}
	void splitsz(int x,int &l,int &r,int key){//按相对排名分裂
		if(!x){l=r=0;return;}
		if(tr[ls].sz+1<=key){l=x,pd(x),splitsz(rs,tr[l].son[1],r,key-tr[ls].sz-1),pu(x);}
		else                {r=x,pd(x),splitsz(ls,l,tr[r].son[0],key),pu(x);}
	}
	void splitpm(int x,int &l,int &r,int key){//按前缀最大值分裂
		if(!x){l=r=0;return;}
		if(tr[x].pmax<=key){l=x,pd(x),splitpm(rs,tr[l].son[1],r,key),pu(x);}
		else               {r=x,pd(x),splitpm(ls,l,tr[r].son[0],key),pu(x);}
	}
	void merge(int &x,int l,int r){
		if(!l||!r){x=l|r;return;}
		if(tr[l].pri<tr[r].pri){x=l,pd(x),merge(rs,tr[l].son[1],r),pu(x);}
		else                   {x=r,pd(x),merge(ls,l,tr[r].son[0]),pu(x);}
	}
	int Build(int l,int r){//建树
		if(l>r)return 0;
		int node=++trc,mid=(l+r)>>1;
		tr[node]=box();
		tr[node].id=mid;
		tr[node].pri=pri[node];
		tr[node].val=arr[mid],tr[node].pmax=pmax[mid],tr[node].sz=1;
		tr[node].son[0]=Build(l,mid-1);
		tr[node].son[1]=Build(mid+1,r);
		pu(node);return node;
	}
	int now=0;
	int ask_kth(int x,int key){//递归找 k 大值
		pd(x);
//		cout<<x<<' '<<key<<"ASK\n";
		if(tr[ls].sz>=key)       return ask_kth(ls,key);
		else if(tr[ls].sz+1>=key)return x;
		else                     return ask_kth(rs,key-tr[ls].sz-1);
	}
	void Wash(){//一次洗牌
		int lr=ask_kth(rt,(n>>1)),rl=ask_kth(rt,(n>>1)+1),rr=ask_kth(rt,n);
		if(tr[lr].pmax!=tr[rl].pmax)return;//没有块被切开
		int ma,maid;
		int ltr=0,rtr=0,fhq=0,node=0;
		splitsz(rt,ltr,rtr,(n>>1));//沿中轴线切割块
		splitpm(rtr,rtr,fhq,tr[rl].pmax);//切割出要改变的块rtr
		int L=tr[rl].id,R=tr[rl].id+tr[rtr].sz-1;
		do{
			maid=tr[rtr].maid,ma=tr[rtr].ma;//块中最大值编号，值
			splitsz(rtr,rtr,node,maid-L);//块中新的最大值作为前缀最大值的块
			tr[node].tg=ma,tr[node].pmax=ma;//更新前缀最大值
			int ltrl=0,ltrr=0;
			splitpm(ltr,ltrl,ltrr,tr[node].pmax);
			merge(ltrl,ltrl,node),merge(ltr,ltrl,ltrr);//把新块按照前缀最大值中序遍历插入到前半部分
			R=maid-1;
		}while(maid!=L);
		merge(rtr,rtr,fhq);
		merge(rt,ltr,rtr);//合并回去
	}
	int solve(int ti,int kth){
		ti=std::min(ti,n);//最多洗 n 次牌
//		cout<<ti<<" "<<kth<<"Solve:\n";
		while(now!=ti)Wash(),++now;	//模拟洗牌
//		cout<<"SOVLE:"<<ask_kth(rt,kth)<<' '<<tr[ask_kth(rt,kth)].val<<'\n';
		return tr[ask_kth(rt,kth)].val;//此时平衡树的中序遍历就是牌堆
	}
	signed main(){
		n=read(),q=read();
		REP(i,1,n)arr[i]=read(),
		pmax[i]=std::max(pmax[i-1],arr[i]),
		pri[i]=rd(pri[i-1],10000*i);
		rt=Build(1,n);
//		Treer("YU",rt);
		REP(i,1,q)In[i].t=read(),
		In[i].ith=read(),
		In[i].id=i;
		stable_sort(In+1,In+q+1,cmp);
		REP(i,1,q){Ans[In[i].id]=solve(In[i].t,In[i].ith);}//离线处理询问
		REP(i,1,q)cout<<Ans[i]<<'\n';
		return 0;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	Code::main();
	return 0;
}
```

---

## 作者：gdf_yhm (赞：4)

[P8996](https://www.luogu.com.cn/problem/P8996)

### 题解

当有 $a_i<a_j$ 时，先放 $a_i$，再放 $i$ 之后连续的 $a_k<a_i$。设 $i$ 后第一个比 $a_i$ 大的位置是 $nxt_i$，对于一个前缀最大值位置 $i$，合并后 $[i,nxt_i)$ 的顺序不变且依然连续。让前缀最大值 $a_l$ 代表整个区间，可以看做合并是将两个序列的前缀最大值排序。

每次合并相当于在 $\frac{n}{2}$ 处断开跨过序列中点的区间 $[l,r]$，生成 $[l,\frac{n}{2}]$ 和 $[\frac{n}{2}+1,nxt_{\frac{n}{2}+1}-1],[nxt_{\frac{n}{2}+1},nxt_{nxt_{\frac{n}{2}+1}}-1],\dotsb,[pos,r]$，然后再重新按区间左端点的值排序。每个区间不会扩大，只会被分割；每次操作如果没有区间跨过序列中点就不会再操作，否则区间数量至少加 $1$。所以最多操作 $n$ 次，最多 $n$ 种区间。

将询问离线，维护每次合并后的区间信息。建权值线段树表示前缀最大值 $l$ 代表的区间长度之和。询问时线段树上二分出包含 $p$ 的区间的最大值和 $p$ 在区间中的位置，对应回初始时最大值的位置加 $p$ 在区间中的位置得到 $p$ 初始时的位置。进行合并操作时二分出包含 $\frac{n}{2}$ 的区间的最大值 $l$，将这个区间 $[l,l+len_l-1]$ 断开为 $[l,\frac{n}{2}]$。从 $\frac{n}{2}+1$ 开始不断跳 $nxt_i$，形成新的区间加入权值线段树。

复杂度 $O(n\log n+q\log n)$。

### code

```cpp
int n,q,a[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2];
void updata(int nd,int l,int r,int p,int w){
	if(l==r){tree[nd]=w;return ;}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
pii query(int nd,int l,int r,int w){
	if(l==r){return {l,w};}
	if(tree[ls]>=w)return query(ls,l,mid,w);
	else return query(rs,mid+1,r,w-tree[ls]);
}
vector<pii> que[maxn];int ans[maxn*5];
int st[maxn],tp,nxt[maxn],len[maxn],pos[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
	a[n+1]=n+1;st[++tp]=n+1;
	for(int i=n;i;i--){
		while(a[st[tp]]<a[i])tp--;st[++tp]=i;
		nxt[i]=st[tp-1];
	}
	for(int i=1;i<=n/2;i=nxt[i]){
		len[i]=min(n/2,nxt[i]-1)-i+1;
		updata(1,1,n,a[i],len[i]);
	}
	for(int i=n/2+1;i<=n;i=nxt[i]){
		len[i]=nxt[i]-1-i+1;
		updata(1,1,n,a[i],len[i]);
	}
	for(int i=1;i<=q;i++){
		int t=read(),d=read();
		if(!t)ans[i]=a[d];
		else que[min(t,n)].push_back({i,d});
	}
	for(int t=1;t<=n;t++){
		for(auto[id,d]:que[t]){
			pii p=query(1,1,n,d);
			// cout<<p.fi<<" "<<p.se<<"\n";
			ans[id]=a[pos[p.fi]+p.se-1];
		}
		pii p=query(1,1,n,n/2);
		int lst=pos[p.fi],r=lst+len[lst]-1,x=lst+p.se;
		len[lst]=p.se;updata(1,1,n,p.fi,p.se);
		while(x<=r){
			len[x]=min(r,nxt[x]-1)-x+1;updata(1,1,n,a[x],len[x]);
			x=nxt[x];
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}
```

---

## 作者：是青白呀 (赞：2)

一个基础的观察是，我们把 $x$ 从后面某个位置移动到前面来的时候，$x$ 之后满足所有值都 $<x$ 的连续段会跟随一起移动。于是我们可以把前后两个部分（以 $\frac n2$ 为界）分别按照前缀最大值分成两段。取出两段的前缀最大值，设为 $L_1,L_2,\dots,L_x$ 和 $R_1,R_2,\dots,R_y$，则一次归并结束后，这些值会变得有序，且段内元素的相对位置关系不变。

进一步地，若把整个序列的前缀最大值取出来，其序列应当是整个 $L$ 和 $R$ 的一段后缀的拼合。若 $R_1>L_x$，则原序列此后都不再变化；否则原来不是整个序列前缀最大值的 $R_1,R_2,\dots,R_z$ 会变为新序列的前缀最大值。也就是说每次变化后序列的前缀最大值至少增加 $1$ 个，故至多有 $n$ 次有效变化。

考虑维护前缀最大值引导的段。由于每次操作结束后所有 $L$ 和 $R$ 会变得有序，不妨考虑使用权值线段树维护每个值是否是 $L,R$ 中的值，若是，同时维护对应段的长度。由于仅有跨越 $\frac n2$ 的段有可能被切开，形成 $R$ 的一部分前缀，且段内相对位置关系不变，不妨预处理处 $len_i$ 表示从在**初始序列中** $i$ 及其之后的值不超过 $i$ 的连续段长度，则每次可以二分到会被切割的段，依次在该段中利用 $len$ 数组和当前段的长度往后跳，求出此次新增的 $R_1,R_2,\dots,R_z$ 的值及对应段长，并在线段树上做对应更新。对于询问可以离线之后按照 $t$ 排序，同样二分到对应段来解决。由于总增加的段数不超过 $n$ 个，故总复杂度为 $O((n+q)\log n)$。

细节较多，需要注意：

- $len$ 数组仅代表**初始状态下**的情况，后续计算每个值开始的段长时，我们只能保证一个段内的元素投射到初始状态下是连续的，而没有保证 $len$ 的长度一直完成没被切开，因此实际段长应当是 $len$ 和当前段对应后缀长度的较小值。

更多细节见代码。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define double long double
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2e5+5,M=1e6+5,S=(1<<15)+5,inf=(ll)1e18+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,a[N],pos[N],len[N],ans[M];
struct query{
    int id,x;
};
vector<query>q[N];
struct seg{
    int t[4*N];
    void pushup(int x){
        t[x]=t[ls(x)]+t[rs(x)];
    }
    void modify(int x,int le,int ri,int p,int v){
        if(le==ri){
            t[x]=v;
            return;
        }
        int mid=(le+ri)>>1;
        if(p<=mid)modify(ls(x),le,mid,p,v);
        else modify(rs(x),mid+1,ri,p,v);
        pushup(x);
    }
    pii query(int x,int le,int ri,int v){
        if(le==ri)return mp(0,le);
        int mid=(le+ri)>>1;
        pii res;
        if(t[ls(x)]<v)res=query(rs(x),mid+1,ri,v-t[ls(x)]),res.fir+=t[ls(x)];
        else res=query(ls(x),le,mid,v);
        return res;
    }
    int queryv(int x,int le,int ri,int p){
        if(le==ri)return t[x];
        int mid=(le+ri)>>1;
        if(p<=mid)return queryv(ls(x),le,mid,p);
        else return queryv(rs(x),mid+1,ri,p);
    }
}T;
void update(int firp,int nwv,int upp){
    if(firp>upp)return;
    int npos=pos[nwv];
    T.modify(1,1,n,nwv,min(len[npos],upp-firp+1));
    update(firp+len[npos],a[npos+len[npos]],upp);
}
void trans(){
    pii res=T.query(1,1,n,n/2+1);
    if(res.fir==n/2)return;
    int nwl=T.queryv(1,1,n,res.sec);
    T.modify(1,1,n,res.sec,n/2-res.fir);
    update(n/2+1,a[pos[res.sec]+n/2-res.fir],res.fir+nwl);
}
signed main(){
    read(n),read(m);
    rep(i,1,n)
        read(a[i]),pos[a[i]]=i;
    rep(i,1,m){
        int t,x;
        read(t),read(x),t=min(t,n);
        if(t==0)ans[i]=a[x];
        else q[t].push_back((query){i,x});
    }
    stack<int>stk;
    rep(i,1,n){
        while(!stk.empty()&&a[stk.top()]<a[i])
            len[stk.top()]=i-stk.top(),stk.pop();
        stk.push(i);
    }
    while(!stk.empty())
        len[stk.top()]=n-stk.top()+1,stk.pop();
    int x=1;
    while(x<=n){
        T.modify(1,1,n,a[x],len[x]);
        x+=len[x];
    }
    rep(i,1,n){
        trans();
        for(auto j:q[i]){
            pii res=T.query(1,1,n,j.x);
            int firp=res.fir+1,firv=res.sec;
            ans[j.id]=a[pos[firv]+j.x-firp];
        }
    }
    rep(i,1,m)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：541forever (赞：2)

我们可以发现，如果一个数被删去，那么他后面一直到第一个比他大的都会被删去。那么我们实际上可以把他分为若干段，注意到，我们一次分裂实际上是把中间一段裂开并将其他段按开头的那个数将段排序，由此，我们也不难证明他最多能被操作 $n$ 次就已经拍好序了。我们考虑记录每个位置下一个比他大位置在哪？这个可以用单调栈简单实现。我们考虑怎么维护这些段，因为我们每次需要将段按开头地那个数排序，因此我们考虑建一棵权值线段树，节点 $[l,r]$ 存储的是值以 $[l,r]$ 开头的段的长度和。查询某次修改后的第 $i$ 个数可以线段树上二分出它所在段开头的值以及它在原数组上这个值对应的位置后几个位置。考虑如何分裂中间的穿过 $n \over 2$ 的那一段，首先，将这段的右端点改为 $n \over 2$，然后我们对 $> {n \over 2}$ 的那些位置暴力划分段，注意到，每个数都只会变成一次段的开头且划分好了的段的长度是不会增加的，因此这么暴力划分段划分的总次数是不超过 $n$ 的，因此总时间复杂度为 $O(Q \log n +n \log n)$。

[Code](https://www.luogu.com.cn/paste/te9a8av1)

---

## 作者：_ZML_ (赞：1)

观察到一轮操作会先选两个数中较小的，再把后面的更小的数选上。

将这样的区间的第一个数排序（把它看做代表元）。

每个区间的第一个数单调递增。就是一个单调数组。

现在考虑一次洗牌会有什么影响。

若 $\frac{n}{2}$ 和 $\frac{n}{2} + 1$ 不在一段内，没有影响。

若在一个块内，后面一段会被分成很多个小段。

注意到一个块内的数的顺序与原序列相同，于是我们可以预处理下一个比 $a_i$ 大的数 $nxt_{i}$。

将每个区间开头插入权值线段树，维护每个区间长度。

每次在线段树上二分，找到包含 $\frac{n}{2}$ 的区间。设这个区间为 $[l, r]$，把它分成两段 $[l, \frac{n}{2}]$ 和 $[\frac{n}{2} + 1, r]$ 对后面的区间暴力分成许多小块，由于最多分解 $n$ 次。

所以时间复杂度 $(n + m) \log_n$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
const int N = 2e5 + 10, M = 1e6 + 10;
int n, T;
int a[N], pos[N], nxt[N], ans[M];
int sum[N << 2];
vector<pair<int, int> > q[N];
void change(int p, int l, int r, int x, int y) {
    if (l > x || r < x)
        return;
    if (l == r) {
        sum[p] = y;
        return;
    }
    int mid = (l + r) / 2;
    change(p * 2, l, mid, x, y), change(p * 2 + 1, mid + 1, r, x, y);
    sum[p] = sum[p * 2] + sum[p * 2 + 1];
}

int query(int p, int l, int r, int x) {
    if (l == r)
        return sum[p];
    int mid = (l + r) / 2;
    if (x <= mid)
        return query(p * 2, l, mid, x);
    return query(p * 2 + 1, mid + 1, r, x);
}

pair<int, int> queryk(int p, int l, int r, int k) {
    if (l == r) {
        return { l, k };
    }
    int mid = (l + r) / 2;
    if (sum[p * 2] < k) {
        return queryk(p * 2 + 1, mid + 1, r, k - sum[p * 2]);
    }
    return queryk(p * 2, l, mid, k);
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    freopen("tors.in", "r", stdin);
    freopen("tors.out", "w", stdout);
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<int> stk;
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && a[*stk.rbegin()] < a[i]) {
            stk.pop_back();
        }
        if (!stk.empty())
            nxt[i] = *stk.rbegin();
        else
            nxt[i] = n + 1;
        stk.push_back(i);
    }
    for (int i = 1; i <= n; i = nxt[i]) {
        change(1, 1, n, a[i], nxt[i] - i);
    }
    for (int i = 1; i <= T; i++) {
        int t, p;
        cin >> t >> p;
        q[min(t, n)].push_back({ p, i });
    }
    for (int i = 0; i <= n; i++) {
        for (auto t : q[i]) {
            auto res = queryk(1, 1, n, t.fi);
            ans[t.sc] = a[pos[res.first] + res.second - 1];
        }
        int mid = n / 2 + 1;
        auto t = queryk(1, 1, n, mid);
        int len = query(1, 1, n, t.first);
        if (t.second == 1)
            continue;
        change(1, 1, n, t.first, t.second - 1);
        for (int j = pos[t.first] + t.second - 1; j <= pos[t.first] + len - 1; j = nxt[j]) {
            change(1, 1, n, a[j], min(pos[t.first] + len, nxt[j]) - j);
        }
    }
    for (int i = 1; i <= T; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

观察这个归并的过程，我们发现可以将数分段，按照前缀 $\max$ 分段，我们不妨将每个前缀 $\max$ 当作该段的代表，用它的权值代表这一段。

这时候我们就会发现，如果此时 $\frac{n}{2},\frac{n}{2}+1$ 这两项不在同一个段内，之后就不会在进行归并了，因为这些段的代表（开头的数）是满足单调递增的。于是我们考虑如果要归并，相当于分裂两个段，考虑我们直接从 $\frac{n}{2}+1$ 的位置开始，每次跳到当前位置下一个 $>$ 它的位置，就能够重构所有段了。由于段只存在分裂没有合并，并且每次在不再归并之前，每次都会至少将一个段分裂成两个。所以一共会分裂 $\le n$ 次，也就是说有效的归并只有 $\le n$ 轮。

维护段的分裂，由于归并过程中保证每个段开头的数是前缀最大值，也就是段开头的数是递增的，所以我们按照数的值维护它开头的段的长度 $a_x$，如果它不是开头则将 $a_x$ 记为 $0$。这样的话我们一开始用单调栈预处理出 $nxt_i$ 表示 $i$ 位置往后的第一个 $>p_i$ 的位置，如果不存在则记为 $n+1$。然后用树状树组维护 $a$，维护前缀和单点改，那么每次要找到 $\frac{n}{2}$ 的位置以及要询问的牌的位置的时候，相当于一个树状树组上倍增，可以做到单 $\log$。分裂的时候暴力用 $nxt$ 跳段起点，然后在树状树组上修改就好了，并且记得同时维护 $a$ 的变化。

复杂度 $O\left(n\log n\right)$。

```cpp
struct fwk {
   tp n, k;
   vector<tp> t;
   fwk(tp n) : n(n), t(n + 1, 0), k(__lg(n)) {}
   tp ask(tp x) {
      tp z = 0;
      for (tp i = x; i; i -= i & (-i)) z += t[i];
      return z;
   }
   void upd(tp x, tp v) {
      for (tp i = x; i <= n; i += i & (-i)) t[i] += v;
      return ;
   }
   pair<tp, tp> binary(tp v) {
      tp x = 0, s = 0;
      for (tp i = 17; ~i; --i)
         if ((x | (1 << i)) <= n && s + t[x | (1 << i)] < v) x |= 1 << i, s += t[x];
      return {x + 1, v - s};
   }
}; 

tp HARUTO() {
   tp n, m; cin >> n >> m;
   vector<tp> p(n + 1, 0), a(n + 1, 0), q(n + 1, 0), nxt(n + 1, n + 1);
   for (tp i = 1, x = 0; i <= n; ++i) {
      cin >> p[i], q[p[i]] = i;
      ckmax(x, p[i]), a[x]++;
   }
   fwk t(n);
   for (tp i = 1; i <= n; ++i) t.upd(i, a[i]);
   stack<tp> stk;
   for (tp i = 1; i <= n; ++i) {
      while (stk.size() && p[stk.top()] < p[i]) nxt[stk.top()] = i, stk.pop();
      stk.emplace(i);
   }
   
   vector<vector<pair<tp, tp>>> qr(n + 1);
   for (tp i = 1, t, x; i <= m; ++i)
      cin >> t >> x, qr[min(t, n)].emplace_back(x, i);
   
   vector<tp> ans(m + 1, 0);
   for (tp i = 0; i <= n; ++i) {
      for (auto [y, id] : qr[i]) {
         auto [x, s] = t.binary(y);
         ans[id] = p[q[x] + s - 1];
      }
      auto [x, s] = t.binary(n / 2);
      if (s < a[x]) {
         tp y = q[x] + s;
         s = a[x] - s, t.upd(x, -s), a[x] -= s;
         for (tp j = y; j < y + s; j = nxt[j])
            a[p[j]] = min(y + s, nxt[j]) - j, t.upd(p[j], a[p[j]]);
      }
   }
   for (tp i = 1; i <= m; ++i) cout << ans[i] << "\n";
   return 0;
}
```

---

## 作者：ll_dio (赞：1)

## 题目大意
给定一个 $n$ 的排列，要对这个排列执行若干次操作，每次操作会将这个排列从中间分成两段并进行一次归并排序的合并过程。现给定 $Q$ 次问询，每次问询求出进行一定次操作后某个位置上的数。
## 题目分析
不难发现，归并操作至多执行n次之后，序列将不会再发生改变。（哪怕不知道归并的这个结论，观察部分分一只给了 $n\le1000$ 也可以得出同样的结论。因此我们可以把询问离线下来，操作一次就记录一次答案。接下来只需要解决如何快速的求归并排序后某个位置上的数即可。
### 找性质
多手算几组样例，不难发现，每一次都会是连续的一段数被移动过去，且这段数中的第一个值是这一段的最大值。因此我们大胆假设，一次洗牌操作是将一个序列分成两段之后，按每段内的前缀最大值排序。

这个结论也很好证明。![我滴证明完成了！](https://cdn.luogu.com.cn/upload/image_hosting/sjdh85bc.png)
如上图，我们令分成两段的序列此时的段首分别为 $a_{i}$，$a_{j}$。因为前缀最大值时单调不降的，所以我们可以证明，在两段内，$a_{i}$ 处的前缀最大值和 $a_{j}$ 处的前缀最大值分别是两段内最小的前缀最大值。当 $a_{j}$ 移动时，$a_{j}<a_{i}$ 一定成立，此时 $a_{j}$ 处的前缀最大值一定最小，而 $a_{j}$ 所在段内所有跟 $a_{j}$ 处前缀最大值相同的 $a_{k}$，它们一定时连续的且一定有 $a_{k}<a_{j}<a_{i}$，所以与 $a_{j}$ 前缀最大值相同的一段一定会被作为一个整体移动，因此假设成立。
### 维护前缀最大值
因此我们需要维护整个序列的前缀最大值，接下来分析前缀最大值在什么情况下会发生改变。

洗牌操作中，后面的合并过程是按照前缀最大值排序，不会改变前缀最大值，但将一个序列分成两半的操作会改变前缀最大值，且只会改变跨越 $\frac{n}{2}+1$ 的一段。这次改变会将这一段分成两段并重新计算后一段的前缀最大值。因此我们可以建立数组 $nxt_{i}$ 来记录 $i$ 后面第一个比 $a_{i}$ 大的位置（即 $i$ 后第一个前缀最大值发生改变的位置），用来方便更改居中段的后半段。

查询操作只需要找第 $k$ 个数所在段即可。这里使用权值线段树来维护以上操作（~~点名批评一个不会平衡树且倍增树状数组天天写挂的铸币~~）。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 200001
#define M 1000001
using namespace std;
typedef long long ll;
ll n,nQ,a[N],ans[M],stk[N],top,nxt[N],rk[N],len[N];
struct Node{
	ll id,pos;
};//结构体用了两遍，一遍是记录离线问询，一遍是记录kth的返回信息。 
vector<Node> q[N];
struct Segment{
	ll l,r,sum;
} tr[4*N];
void brush(ll u){
	if(tr[u].l==tr[u].r) return;
	tr[u].sum=tr[2*u].sum+tr[2*u+1].sum;
}
void build(ll u,ll l,ll r){
	tr[u].l=l; tr[u].r=r; tr[u].sum=0;
	if(l==r) return;
	ll mid=(l+r)/2;
	build(2*u,l,mid); build(2*u+1,mid+1,r);
}
void upd(ll u,ll x,ll val){
	if(tr[u].l==tr[u].r){
		tr[u].sum=val;
		return;
	}
	if(x<=tr[2*u].r) upd(2*u,x,val);
	else upd(2*u+1,x,val);
	brush(u);
}
Node kth(ll u,ll k){
	if(tr[u].l==tr[u].r) return (Node){tr[u].l,k};
	if(k<=tr[2*u].sum) return kth(2*u,k);
	return kth(2*u+1,k-tr[2*u].sum);
}//这里返回两个值，一个是所在段的前缀最大值，一个是这个数在所在段的第几个位置 
void input(){
	scanf("%lld %lld",&n,&nQ);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=nQ;i++){
		ll cnt,pos;
		scanf("%lld %lld",&cnt,&pos);
		q[min(cnt,n)].push_back((Node){i,pos}); //离线 
	}
}
void solve(){
	stk[++top]=n+1;
	for(ll i=n;i>=1;i--){
		while(top>1&&a[i]>=a[stk[top]]) top--;
		nxt[i]=stk[top]; stk[++top]=i; rk[a[i]]=i;
	}//单调栈求nxt 
	build(1,1,n);
	for(ll i=1;i<=n;i=nxt[i]) upd(1,a[i],nxt[i]-i),len[i]=nxt[i]-i;
	//初始化权值线段树 
//	for(ll i=1;i<=n;i++) printf("%lld ",nxt[i]);
//	printf("\n");
	for(ll iC=0;iC<=n;iC++){
		for(ll i=0;i<q[iC].size();i++){
			Node k=kth(1,q[iC][i].pos);
			ans[q[iC][i].id]=a[rk[k.id]+k.pos-1];
		}//算答案 
		Node k=kth(1,n/2+1);
		if(k.pos==1) continue;//中间段没有跨越两个部分就不用修改 
		upd(1,k.id,k.pos-1);
		for(ll i=rk[k.id]+k.pos-1;i<=rk[k.id]+len[rk[k.id]]-1;i=nxt[i]){//跳他丫的 
			len[i]=min(rk[k.id]+len[rk[k.id]],nxt[i])-i;
			upd(1,a[i],len[i]);
		}
		len[rk[k.id]]=k.pos-1;//这俩顺序不能倒，倒了后半段的前缀最大值更新不了。 
	}
	for(ll i=1;i<=nQ;i++) printf("%lld\n",ans[i]);
}
int main(){
// 	freopen("game.in","r",stdin);
// 	freopen("game.out","w",stdout);
// 上面这段是模拟赛搬原题时写的输入输出 
	input();
	solve();
	return 0;
}
```

---

## 作者：Add_Catalyst (赞：0)

# P8996 [CEOI 2022] Abracadabra 题解

------

## 知识点

线段树，平衡树，树状数组。

## 分析

首先，我们可以分析一下样例。

| 洗牌次数 |         自底向上的牌堆          |
| :------: | :-----------------------------: |
|   $0$    | $7\ 5\ 2\ 9\ 10\ 8\ 4\ 3\ 6\ 1$ |
|   $1$    | $7\ 5\ 2\ 8\ 4\ 3\ 6\ 1\ 9\ 10$ |
|   $2$    | $3\ 6\ 1\ 7\ 5\ 2\ 8\ 4\ 9\ 10$ |
|   $3$    | $2\ 3\ 6\ 1\ 7\ 5\ 8\ 4\ 9\ 10$ |

### 分段

我们将第 $0$ 次与第 $1$ 次作比较，发现两次都有几段连续的数：

| 洗牌次数 |            自底向上的牌堆             |
| :------: | :-----------------------------------: |
|   $0$    | $7\ 5\ 2\mid 9\ 10\mid 8\ 4\ 3\ 6\ 1$ |
|   $1$    | $7\ 5\ 2\mid 8\ 4\ 3\ 6\ 1\mid 9\ 10$ |

我们可以先凭最表面的分段，就会分成上面两种，发现第 $1$ 次就是第 $0$ 次分段后按第一个数排序。

而每段又有什么规律呢？好像有两段第一个数都是最大的，而另一段是 $9\ 10$，似乎不符合规律，但是我们又可以把上面的分成：

| 洗牌次数 |               自底向上的牌堆                |
| :------: | :-----------------------------------------: |
|   $0$    | $7\ 5\ 2\ \mid 9 \mid 10\mid 8\ 4\ 3\ 6\ 1$ |
|   $1$    |  $7\ 5\ 2\mid 8\ 4\ 3\ 6\ 1\mid 9\mid 10$   |

这下就符合规律了。

### 拆段

再考虑 $1$ 次时到第 $2$ 次，我们按照上面的方式来分段：

| 洗牌次数 |               自底向上的牌堆                |
| :------: | :-----------------------------------------: |
|   $1$    | $7\ 5\ 2\mid 8\ 4\mid 3\ 6\ 1\mid 9\mid 10$ |
|   $2$    | $3\ 6\ 1\mid 7\ 5\ 2\mid 8\ 4\mid 9\mid 10$ |

这好像就是把上面横跨中间的分开就好了，但是我们换一个样例看一下：

| 洗牌次数 |            自底向上的牌堆            |
| :------: | :----------------------------------: |
|   $0$    | $9 \ 7\ 5\ 2\ 10 \ 8 \ 4\ 3\ 6\ 1\ $ |
|   $1$    |   $9 \ 7\ 5\ 2\ 8\ 4\ 3\ 6\ 1\ 10$   |
|   $2$    |   $3\ 6\ 1\ 4\ 8\ 9 \ 7\ 5\ 2\ 10$   |

- $0 \to 1$：

  | 洗牌次数 |              自底向上的牌堆               |
  | :------: | :---------------------------------------: |
  |   $0$    | $9 \ 7\ 5\ 2\mid 10\mid 8 \ 4\ 3\ 6\ 1\ $ |
  |   $1$    |  $9 \ 7\ 5\ 2\mid 8\ 4\ 3\ 6\ 1\mid 10$   |

- $1 \to 2$：

  | 洗牌次数 |                自底向上的牌堆                |
  | :------: | :------------------------------------------: |
  |   $1$    | $9 \ 7\ 5\ 2\mid 8\mid 4\mid 3\ 6\ 1\mid 10$ |
  |   $2$    | $3\ 6\ 1\mid 4\mid 8\mid 9 \ 7\ 5\ 2\mid 10$ |

除了分开横跨中间的部分，我们还要把分开的后面那段给按照一开始分段的方法分开，这里我们可以处理出对于每个值下一个大于它的值是多少，然后一路处理过去，均摊次数是线性的。

那么我们就可以动态模拟维护了。

## 实现

考虑套数据结构进行动态维护。

### 平衡树

最简单的思想，把区间存在平衡树中，用一些操作解决即可。

这里选用无旋 Treap，那么实现按值分裂、按大小分裂和分裂第一个节点即可。

### 线段树 & 树状数组

由于对每段排序是按照每段第一个值大小升序排序，而且我们只要求按大小查值，所以我们可以用权值线段树或树状数组代替，只需实现单点修改，线段树二分或树状数组倍增以及前缀和查询即可。

## 代码

### 平衡树

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define Fi first
#define Se second
#define Pii pair<int,int>
#define uint unsigned int
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(2e5+10),Qr(1e6+10);
mt19937 rng(random_device {}());

namespace IOEcat {
    //Fast IO
} using namespace IOEcat;

bool flag;
int n,Q;
int a[N],len[N],nxt[N],pos[N],ans[Qr];
vector<Pii> vec[N];

struct Treap {
	int rt,tot;
	struct node {
		int key,cnt,siz,ls,rs;
		uint blc;
		node(int key=0,int cnt=0,int siz=0,int ls=0,int rs=0,uint blc=rng()):
			key(key),cnt(cnt),siz(siz),ls(ls),rs(rs),blc(blc) {}
	} tr[N];

	node &operator [](int i) { return tr[i]; }

	Treap():rt(0),tot(0) {}
#define ls(p) (tr[p].ls)
#define rs(p) (tr[p].rs)
	void Init() { tr[rt=tot=1]=node(); }

	int New(int key,int cnt) { return tr[++tot]=node(key,cnt,cnt),tot; }

	void Up(int p) { tr[p].siz=tr[ls(p)].siz+tr[p].cnt+tr[rs(p)].siz; }

	int &Merge(int &o,int p,int q) {
		if(!p||!q)return o=p|q;
		return (tr[p].blc<=tr[q].blc?Merge(rs(o=p),rs(p),q):Merge(ls(o=q),p,ls(q))),Up(o),o;
	}

	void Split_key(int &o,int &p,int key) { //[<=key] -> o,[>key] -> p
		if(!p)return o=0,void();
		if(key<tr[p].key)return Split_key(o,ls(p),key),Up(p);
		if(key==tr[p].key)return o=p,p=rs(p),rs(o)=0,Up(o);
		return o=p,Split_key(rs(o),p=rs(o),key),Up(o);
	}

	void Split_siz(int &o,int &p,int siz) { //[<=siz] -> o,[>siz] -> p
		if(!p)return o=0,void();
		if(tr[ls(p)].siz+tr[p].cnt<=siz)
			return o=p,Split_siz(rs(o),p=rs(o),siz-tr[ls(p)].siz-tr[p].cnt),Up(o);
		return Split_siz(o,ls(p),siz),Up(p);
	}

	void Split_begin(int &o,int &p) { //[begin] -> o,[otherwise] -> p
		if(!p)return o=0,void();
		if(ls(p))return Split_begin(o,ls(p)),Up(p);
		return o=p,p=rs(p),rs(o)=0,Up(o),void();
	}

	int Kth(int p,int k) {
		if(!p)return 0;
		if(ls(p)&&k<=tr[ls(p)].siz)return Kth(ls(p),k);
		if(k<=tr[ls(p)].siz+tr[p].cnt)return a[pos[tr[p].key]+k-tr[ls(p)].siz-1];
		return Kth(rs(p),k-tr[ls(p)].siz-tr[p].cnt);
	}

	void Print(int p,int fa=-1,int sign=-1) {
		if(!p)return;
		Print(ls(p),p,0);
		DE(p,fa,sign,tr[p].key);
		Print(rs(p),p,1);
	}
#undef ls
#undef rs
} trp;

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	/*DE("Input");*/
	I(n,Q);
	FOR(i,1,n)I(a[i]);
	/*DE("Offline");*/
	FOR(i,1,Q) {
		int t,x;
		I(t,x),t?vec[min(n,t)].push_back({x,i}),0:ans[i]=a[x];
	}
	/*DE("Init");*/
	//len
	auto Init_len=[&](int L,int R) {
		int it(L);
		FOR(i,L+1,R)if(a[i]>a[it])len[a[it]]=i-it,it=i;
		len[a[it]]=R-it+1;
	};
	Init_len(1,n>>1),Init_len((n>>1)+1,n);
	//Treap
	trp.Init();
	FOR(i,1,n)if(len[i])trp.Merge(trp.rt,trp.rt,trp.New(i,len[i]));
	//nxt
	set<int> st;
	DOR(i,n,1) {
		auto it(st.upper_bound(a[i]));
		nxt[a[i]]=(it==st.end()?n+1:*it),st.insert(a[i]);
		while(!st.empty()&&*st.begin()<a[i])st.erase(st.begin());
	}
	//pos
	FOR(i,1,n)pos[a[i]]=i;
	pos[n+1]=n+1;
	/*DE("Solve");*/
	FOR(i,1,n) {
		for(const Pii &p:vec[i])ans[p.Se]=trp.Kth(trp.rt,p.Fi);
		if(flag)continue;
		int l(0),mid(0),r(trp.rt);
		trp.Split_siz(l,r,n>>1);
		if(trp[l].siz==(n>>1)&&(trp.Merge(trp.rt,l,r),flag=true))continue;
		int pla(trp[trp.Split_begin(mid,r),mid].key);
		trp[mid].cnt=trp[mid].siz=(n>>1)-trp[l].siz;
		for(int p(a[pos[pla]+(n>>1)-trp[l].siz]); p<=n&&pos[p]<pos[pla]+len[pla]; p=nxt[p]) {
			len[p]=min(pos[pla]+len[pla],pos[nxt[p]])-pos[p];
			int L(0),R(l);
			trp.Split_key(L,R,p),trp.Merge(l,L,trp.Merge(R,trp.New(p,len[p]),R));
		}
		len[pla]=trp[mid].cnt,trp.Merge(trp.rt,l,trp.Merge(r,mid,r));
	}
	/*DE("Output");*/
	FOR(i,1,Q)O(ans[i],'\n');
	return 0;
}
```

### 线段树

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define Fi first
#define Se second
#define Pii pair<int,int>
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(2e5+10),Qr(1e6+10);

namespace IOEcat {
    //Fast IO
} using namespace IOEcat;

int n,Q;
int a[N],len[N],nxt[N],pos[N],ans[Qr];
vector<Pii> vec[N];

struct SEG {
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
	int tr[N<<2];

	void Up(int p) { tr[p]=tr[ls]+tr[rs]; }

	void Build(int p=1,int l=1,int r=n) {
		if(l==r)return tr[p]=len[l],void();
		Build(ls,l,mid),Build(rs,mid+1,r),Up(p);
	}

	void Change(int x,int d,int p=1,int l=1,int r=n) {
		if(l==r)return tr[p]=d,void();
		return (x<=mid?Change(x,d,ls,l,mid):Change(x,d,rs,mid+1,r)),Up(p);
	}

	int Binary(int k=(n>>1),int p=1,int l=1,int r=n) {
		if(l==r)return l;
		if(tr[rs]>=k)return Binary(k,rs,mid+1,r);
		return Binary(k-tr[rs],ls,l,mid);
	}

	int Sum(int L,int R,int p=1,int l=1,int r=n) {
		if(L<=l&&r<=R)return tr[p];
		if(R<=mid)return Sum(L,R,ls,l,mid);
		if(mid<L)return Sum(L,R,rs,mid+1,r);
		return Sum(L,R,ls,l,mid)+Sum(L,R,rs,mid+1,r);
	}
#undef ls
#undef rs
#undef mid
} seg;

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	/*DE("Input");*/
	I(n,Q);
	FOR(i,1,n)I(a[i]);
	FOR(i,1,Q) {
		int t,x;
		I(t,x),t?vec[min(n,t)].push_back({x,i}),0:ans[i]=a[x];
	}
	/*DE("Init");*/
	//pos
	FOR(i,1,n)pos[a[i]]=i;
	pos[n+1]=n+1;
	//left
	int it(1);
	FOR(i,2,n>>1)if(a[i]>a[it])len[a[it]]=i-it,it=i;
	len[a[it]]=(n>>1)-it+1;
	//right
	it=(n>>1)+1;
	FOR(i,(n>>1)+2,n)if(a[i]>a[it])len[a[it]]=i-it,it=i;
	len[a[it]]=n-it+1;
	//nxt
	set<int> st;
	DOR(i,n,1) {
		nxt[a[i]]=(st.upper_bound(a[i])==st.end()?n+1:*st.upper_bound(a[i])),st.insert(a[i]);
		while(!st.empty()&&*st.begin()<a[i])st.erase(st.begin());
	}
	//seg
	seg.Build();
	/*DE("Solve");*/
	FOR(i,1,n) {
		for(const Pii &p:vec[i]) {
			int x(p.Fi),pla(seg.Binary(n-x+1));
			if(pla>1)x-=seg.Sum(1,pla-1);
			ans[p.Se]=a[pos[pla]+x-1];
		}
		int pla(seg.Binary()),sum(pla>1?seg.Sum(1,pla-1):0);
		if(sum==(n>>1))continue;
		for(int p(a[pos[pla]+(n>>1)-sum]); p&&p<=n&&pos[p]<pos[pla]+len[pla]; p=nxt[p])
			seg.Change(p,len[p]=min(pos[pla]+len[pla],pos[nxt[p]])-pos[p]);
		seg.Change(pla,len[pla]=(n>>1)-sum);
	}
	/*DE("Output");*/
	FOR(i,1,Q)O(ans[i],'\n');
	return 0;
}
```

### 树状数组

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define Fi first
#define Se second
#define Pii pair<int,int>
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(2e5+10),Qr(1e6+10);

namespace IOEcat {
    //Fast IO
} using namespace IOEcat;

bool flag;
int n,Q,L;
int a[N],len[N],nxt[N],pos[N],ans[Qr];
vector<Pii> vec[N];

struct BIT {
#define lowbit(i) ((i)&-(i))
	int c[N];

	void Build() {
		FOR(i,1,n) {
			c[i]+=len[i];
			if(i+lowbit(i)<=n)c[i+lowbit(i)]+=c[i];
		}
	}

	void Plus(int x,int d) { if(x>0)for(; x<=n; x+=lowbit(x))c[x]+=d; }

	int Sum(int x) {
		int ans(0);
		if(x>0)for(; x; x&=x-1)ans+=c[x];
		return ans;
	}

	int Binary(int k=(n>>1)+1) {
		int ans(0),sum(0);
		DOR(i,L,0)if((ans|1<<i)<=n&&sum+c[ans|1<<i]<k)sum+=c[ans|=1<<i];
		return ans+(sum<k);
	}
} bit;

namespace Sub {
	int Cmain() {
		/*DE("Init");*/
		//pos
		FOR(i,1,n)pos[a[i]]=i;
		pos[n+1]=n+1;
		//left
		int it(1);
		FOR(i,2,n>>1)if(a[i]>a[it])len[a[it]]=i-it,it=i;
		len[a[it]]=(n>>1)-it+1;
		//right
		it=(n>>1)+1;
		FOR(i,(n>>1)+2,n)if(a[i]>a[it])len[a[it]]=i-it,it=i;
		len[a[it]]=n-it+1;
		//nxt
		set<int> st;
		DOR(i,n,1) {
			nxt[a[i]]=(st.upper_bound(a[i])==st.end()?n+1:*st.upper_bound(a[i])),st.insert(a[i]);
			while(!st.empty()&&*st.begin()<a[i])st.erase(st.begin());
		}
		//bit
		bit.Build();
		/*DE("Solve");*/
		FOR(i,1,n) {
			for(const Pii &p:vec[i]) {
				int x(p.Fi),pla(bit.Binary(x));
				if(pla>1)x-=bit.Sum(pla-1);
				ans[p.Se]=a[pos[pla]+x-1];
			}
			if(flag)continue;
			int pla(bit.Binary()),sum(pla>1?bit.Sum(pla-1):0);
			if(sum==(n>>1)&&(flag==true))continue;
			for(int p(a[pos[pla]+(n>>1)-sum]); p&&p<=n&&pos[p]<pos[pla]+len[pla]; p=nxt[p])
				bit.Plus(p,len[p]=min(pos[pla]+len[pla],pos[nxt[p]])-pos[p]);
			int tmp(len[pla]);
			bit.Plus(pla,(len[pla]=(n>>1)-sum)-tmp);
		}
		/*DE("Output");*/
		FOR(i,1,Q)O(ans[i],'\n');
		return 0;
	}
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n,Q),L=__lg(n);
	FOR(i,1,n)I(a[i]);
	FOR(i,1,Q) {
		int t,x;
		I(t,x),t?vec[min(n,t)].push_back({x,i}),0:ans[i]=a[x];
	}
	return Sub::Cmain();
}
```

------

---

## 作者：shiruoyu114514 (赞：0)

发现一个事实：当一张牌被放下后，其之后的所有点数小于这张牌的牌都会放下。

这启示我们在每一半中，若一张牌没有被前面的牌捆绑，则令其与后面第一个比其大的数之前的所有数捆绑。

我们设一组的代表元为发起捆绑的那张牌的点数。容易发现，代表元为这一组的第一个元素，并且一定是这组的最大值。

在如此分组后，我们可以发现每一堆中每组代表元不降。并且在每一次洗牌过后，所有组代表元组成的序列不降。

以样例3为例：

初始为 ``7 5 2 9 10 8 4 3 6 1``。

在进行如上分组后为 ``7 5 2`` `9` `10` `8 4 3 6 1`。

在排序后为 `7 5 2` `8 4 3 6 1` `9` `10`。

注意到在洗牌后，可能会有一组跨过 $\frac{n}{2}$ 与 $\frac{n}{2}+1$，因此我们需要对这组进行分割。

具体地，我们暴力从 $\frac{n}{2}$ 与 $\frac{n}{2}+1$ 分割这组，如 ``7 5 2`` ``8 4`` ``3 6 1`` ``9 10``。

然后我们可以发现 $\frac{n}{2}+1$ 所在的这一组可能不满足“第一个元素为最大值”的性质。

此时我们需要再次分割。

具体地，我们找出以 $\frac{n}{2}+1$ 为开头的合法组，然后从合法组与其余部分分割，再处理其余部分。

如对 `3 6 1` 进行分割的过程中，我们发现以 $3$ 为开头的合法组只有 $3$ 本身，于是将 `3 6 1` 分割为 `3` `6 1`。然后发现以 $6$ 为开头的合法组正好为 `6 1`，不用分割，此时结束分割过程。

我们考虑用权值线段树来维护排序、分割以及查询的过程。具体地，令 $len_i$ 为以值 $i$ 为开头的组的长度（若 $i$ 不是任何组的开头，则令 $len_i$ 为 $0$ ），并用权值线段树维护区间和。

当进行查询时，在权值线段树上二分出所在组的代表元素，并用区间求和求出代表元素之前有多少个元素。因为同一个组内的相对位置关系与初始序列相同，所以在定位代表元素的位置后直接用初始元素的相对位置信息求出答案。时间复杂度 $O(\log n)$。

在进行分割时，首先将跨过中点的组分割开，然后对后面的组进行检查并分割。设 $j$ 为大于 $a_i$ 的第一个元素的位置，则若一个组以 $a_i$ 为代表元，那个组的长度一定不超过 $j-i$。所以我们在分割以 $a_i$ 为开头的组时直接从第 $i-j$ 个数分开即可。这也可以用权值线段树维护。时间复杂度 $O(\log n)$。

又观察到最多有 $n$ 个段，故最多进行 $n$ 次分割操作。

时间复杂度 $O((n+q)\log n)$。

```
#include<bits/stdc++.h>

using namespace std;

const int maxn=1e6;
int n,q;
bool ed;

int sum[(maxn<<2)+5];
int rev[maxn+5];
int a[maxn+5];
int cnt[maxn+5];

void pushup(int now){
	sum[now]=sum[now<<1]+sum[now<<1|1];
}

void update(int now,int from,int to,int pos,int value){
	if(from==to){
		sum[now]=value;
		return;
	}
	int mid=(from+to)>>1;
	if(pos<=mid){
		update(now<<1,from,mid,pos,value);
	}
	else{
		update(now<<1|1,mid+1,to,pos,value);
	}
	pushup(now);
}

int getsum(int now,int from,int to,int ql,int qr){
	if(from==ql&&to==qr){
		return sum[now];
	}
	int ans=0;
	int mid=(from+to)>>1;
	if(ql<=mid){
		ans+=getsum(now<<1,from,mid,ql,min(qr,mid));
	}
	if(mid<qr){
		ans+=getsum(now<<1|1,mid+1,to,max(mid+1,ql),qr);
	}
	return ans;
}

int find(int now,int from,int to,int k){
	if(from==to){
		return from;
	}
	int mid=(from+to)>>1;
	if(k<=sum[now<<1]){
		return find(now<<1,from,mid,k);
	}
	else{
		return find(now<<1|1,mid+1,to,k-sum[now<<1]);
	}
}

int split(int value,int pre){
	int det=getsum(1,1,n,value,value)-pre;
	int now=a[rev[value]+pre];
	update(1,1,n,value,pre);
	update(1,1,n,now,det);
	return now;
}

void sort(){
	if(ed){
		return;
	}
	int p=find(1,1,n,n/2);
	int q=find(1,1,n,n/2+1);
	if(p!=q){
		ed=1;
		return;
	}
	int presum=getsum(1,1,n,1,p-1);
	int now=split(p,n/2-presum);
	while(1){
		int len=getsum(1,1,n,now,now);
		if(len>cnt[rev[now]]){
			now=split(now,cnt[rev[now]]);
		}
		else{
			break;
		}
	}
}

int ask(int x){
	int in=find(1,1,n,x);
	int presum;
	if(in==1){
		presum=0;
	}
	else
		presum=getsum(1,1,n,1,in-1);
	return a[rev[in]+x-presum-1];
}

vector<pair<int,int>> quary[maxn+5];
int answer[maxn+5];

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		rev[a[i]]=i;
	}
	stack<int> work;
	for(int i=1;i<=n;i++){
		cnt[i]=1;
	}
	for(int i=n;i>=1;i--){
		while(!work.empty()&&a[i]>a[work.top()]){
			cnt[i]+=cnt[work.top()];
			work.pop();
		}
		work.push(i);
	}
	for(int i=1;i<=n/2;i++){
		int j;
		for(j=i+1;j<=n/2&&a[j]<a[i];j++);
		update(1,1,n,a[i],j-i);
		i=j-1;
	}
	for(int i=n/2+1;i<=n;i++){
		int j;
		for(j=i+1;j<=n&&a[j]<a[i];j++);
		update(1,1,n,a[i],j-i);
		i=j-1;
	}
	for(int i=1;i<=q;i++){
		int t,x;
		cin>>t>>x;
		t=min(t,n);
		quary[t].push_back(make_pair(x,i));
	}
	for(auto i:quary[0]){
		answer[i.second]=a[i.first];
	}
	for(int i=1;i<=n;i++){
		for(auto j:quary[i]){
			answer[j.second]=ask(j.first);
		}
		sort();
	}
	for(int i=1;i<=q;i++){
		cout<<answer[i]<<'\n';
	}
}

---

