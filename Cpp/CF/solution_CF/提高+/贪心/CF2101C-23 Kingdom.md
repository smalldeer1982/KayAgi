# 23 Kingdom

## 题目描述

我们定义 $d_x(c)$ 为整数 $x$ 在数列 $c$ 中的距离，也就是 $c$ 中出现的两个 $x$ 之间的最长间隔。若 $x$ 出现的次数不足两次则为零。

形式化地，$d_x(c)=\max\limits_{1\le i<j\le\vert c\vert\wedge c_i=c_j=x}(j-i)$。

定义一个数列 $c$ 的美丽度为 $\sum\limits_{i=1}^n d_i(c)$。

给你一个长为 $n$ 的数列 $a$，你将构造一个长为 $n$ 的数列 $b$，要求每一项均满足 $1\le b_i\le a_i$。求这样的 $b$ 的最大美丽度。你需要求出这个值。

## 说明/提示

**样例解释**

第一组数据中，令 $b=(1,2,1,2)$，$d_1(b)=3-1=2,d_2(b)=4-2=2$，美丽度为 $4$。可以证明这个可能的最大的美丽值。

第二组数据中，令 $b=(1,1)$ 或 $b=(2,2)$ 均可得到 $1$ 的美丽值。

第三组数据中，令 $b=(1,2,1,4,1,2,1,1,1,2)$，则有 $d_1(b)=9-1=8,d_2(b)=10-2=8,d_4(b)=0$，可以获得 $16$ 的美丽值。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
4
4
1 2 1 2
2
2 2
10
1 2 1 5 1 2 2 1 1 2
8
1 5 2 8 4 1 4 2```

### 输出

```
4
1
16
16```

# 题解

## 作者：Unnamed114514 (赞：1)

考虑这样一个事情：对于一个值，我们只需要保留它的左右端点。

因此，我们考虑对于每个值维护一个 `set`，$s_x$ 表示 $a_i=x$ 的 $i$ 的集合。我们从大往小枚举 $x$，然后每次从 $s_x$ 中取出最大最小值，然后把剩下的值加入 $s_{x-1}$。

这个过程可以用启发式合并维护，时间复杂度 $O(n\log^2 n)$，不知道有没有什么高级一点的东西可以加速这个过程。

你会发现，它过不了第四组样例，考虑如下事实：

对于 `5 8 4 4` 这种情况，最有的构造是 `3 4 4 3`，但是根据上述做法，得到的是 `5 5 4 4`。

我们发现，答案是 $\sum r-\sum l$ 的形式，但是当 $r>l$ 时，我们可以通过一个 $|s_x|<2$ 的位置来进行调整，通过在 $x$ 构建区间的方式使两个相交的区间转化为包含关系。即让 $[l_1,r_1],[l_2,r_2](l_1<r_1<l_2<r_2)$ 变成 $[l_1,r_2],[r_1,l_2]$ 的形式。这就启发我们维护两个优先队列，小根堆维护 $r$ 得到 $r_{\min}$，大根堆维护 $l$ 得到 $l_{\max}$，从而快速处理这个操作。

同时，显然当 $|s_x|=1$ 时，此时 $s_x$ 内的这个元素也可以参与构建区间，所以就把上面的两个值和这个值排序，最大值和最小值构成新的区间，中间值加入 $x$。

这仍然是过不了的。我们发现，我们上述的讨论都建立在了“选取的区间尽可能多”的前提上。实际上，你会拍出来一些区间数目并非最多的情况。

问题就落在了加入区间上，此时我们可能有以下三种情况：

- 直接加入这个区间。

- 用这个区间的左端点替换掉一个区间的左端点，显然替换的左端点应该是所有左端点中最大的那一个。

- 用这个区间的右端点替换调一个区间的右端点，显然替换的右端点也应该是所有右端点中最大的那一个。

这三种方案对答案的贡献是容易算出来的。贪心地，选择贡献最大的那一个即可。

瓶颈在启发式合并，时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,R,a[N];
set<int> s[N];
void merge(int x){
	if(s[R].size()<s[x].size()){
		for(auto k:s[R]) s[x].insert(k);
		R=x;
	} else for(auto k:s[x]) s[R].insert(k);
}
priority_queue<int,vector<int>,greater<int> > q1;
priority_queue<int,vector<int>,less<int> > q2;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i],s[a[i]].insert(i);
		R=n;
		for(int i=n;i;--i){
			if(s[R].size()>=2){
				if(q1.empty()){
					q1.emplace(*(--s[R].end())),s[R].erase(--s[R].end());
					q2.emplace(*s[R].begin()),s[R].erase(s[R].begin());
				} else{
					int c1=(*(--s[R].end()))-(*s[R].begin()),c2=(*(--s[R].end()))-q1.top(),c3=q2.top()-(*s[R].begin());
					if(c1==max({c1,c2,c3})){
						q1.emplace(*(--s[R].end())),s[R].erase(--s[R].end());
						q2.emplace(*s[R].begin()),s[R].erase(s[R].begin());
					} else if(c2==max({c1,c2,c3})){
						s[R].insert(q1.top()),q1.pop();
						q1.emplace(*(--s[R].end())),s[R].erase(--s[R].end());
					} else{
						s[R].insert(q2.top()),q2.pop();
						q2.emplace(*s[R].begin()),s[R].erase(s[R].begin());
					}
				}
			} else if(s[R].size()==1){
				if(q1.size()){
					int x=q1.top(),y=q2.top(),z=(*s[R].begin());
					q1.pop(),q2.pop(),s[R].erase(s[R].begin());
					if(x>y) swap(x,y);
					if(y>z) swap(y,z);
					if(x>y) swap(x,y);
					q1.emplace(z),q2.emplace(x);
					s[R].insert(y);
				}
			} else{
				if(q1.size()){
					int x=q1.top(),y=q2.top();
					q1.pop(),q2.pop();
					if(x>y) swap(x,y);
					q1.emplace(y),q2.emplace(x);
				}
			}
			merge(i-1);
		}
		int ans=0;
		while(q1.size()) ans+=q1.top(),q1.pop();
		while(q2.size()) ans-=q2.top(),q2.pop();
		cout<<ans<<endl;
		for(int i=n;i;--i) s[i].clear();
	}
	return 0;
}
```

---

## 作者：jiazhichen844 (赞：0)

## 题意
对于一个序列 $a$，定义 $f(a)=\sum\limits_{x=1}^{n}\max\limits_{1\le i<j\le n,a_i=a_j=x}(j-i)$。  
对于所有 $1\le b_i\le a_i$ 的 $b$，求 $\max f(b)$。
## 做法
一些神秘东西。

计算 $f(a)$ 时考虑一些奇思妙想，对于一个出现 **至少两次** 的数字 $x$，将第一次出现的位置上标一个负号，最后一个出现的位置上标一个正号，则 $f(a)$ 是标正号的位置和减去标负号的位置和。  
感觉这个更复杂了，但是注意到这个东西的计算只跟标正负号的位置有关，所以考虑在 $a$ 上面标正负号。

假设我们有一种标正负号的方法，则它是好的当且仅当存在一种 $b$，满足标正号的位置上的 $b$ 互不相同，负号同理，且正号位置上数的集合和负号位置上数的集合相同。  
首先若存在一个满足前两条条件且正负号数量相同的 $b$，则一定可以调整到满足第三个条件。  
然后就很好了，因为正号和负号独立。  
若我们在 $x_1,x_2,\cdots,x_k$ 标了正号，则要求 $\forall 1\le y\le n,\sum\limits_{i=1}^k [a_{x_i}\le y]\le y$，否则根据鸽巢原理一定不存在无重复元素的 $b$，若条件成立，也容易构造出 $b$，标负号同理。

填写正号的过程是容易的，从后往前扫，每当扫到一个数，尝试标上正号，如果不违反条件就标上，否则不标，负号同理，这个贪心的证明在最后。  
怎么判断是否违反条件？令 $S$ 为标上号的集合，$f_i=i-\sum\limits_{x\le S}[a_x\le i]$，则不违反条件当且仅当 $\min\limits_{i=1}^n f_i\ge 0$。  
发现加一个数相当于区间减，判断相当于求区间 $\min$，线段树维护即可。  
设最后第 $i$ 个填上的正号位置为 $r_i$，负号位置为 $l_i$，则找到最大的 $k$ 满足 $l_k<r_k$，答案即为 $\sum\limits_{i=1}^k (r_i-l_i)$。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[200005];
int pre[200005],presum[200005],suf[200005],sufsum[200005];
const int inf=0x3f3f3f3f3f3f3f3f;
struct segT
{
	struct segment
	{
		int l,r,tag,mn;
	}a[800005];
	void build(int pos,int l,int r)
	{
		a[pos]={l,r,0,l};
		if(l==r)
		{
			a[pos].mn=l;
			return;
		}
		int mid=l+r>>1;
		build(pos<<1,l,mid);
		build(pos<<1|1,mid+1,r);
	}
	void update(int pos)
	{
		a[pos].mn=min(a[pos<<1].mn,a[pos<<1|1].mn);
	}
	void puttag(int pos,int x)
	{
		a[pos].tag+=x,a[pos].mn+=x;
	}
	void pushdown(int pos)
	{
		puttag(pos<<1,a[pos].tag);
		puttag(pos<<1|1,a[pos].tag);
		a[pos].tag=0;
	}
	void add(int pos,int l,int r,int x)
	{
		if(r<a[pos].l||l>a[pos].r)
			return;
		if(l<=a[pos].l&&a[pos].r<=r)
		{
			puttag(pos,x);
			return;
		}
		pushdown(pos);
		add(pos<<1,l,r,x);
		add(pos<<1|1,l,r,x);
		update(pos);
	}
	int query(int pos,int l,int r)
	{
		if(r<a[pos].l||l>a[pos].r)
			return inf;
		if(l<=a[pos].l&&a[pos].r<=r)
			return a[pos].mn;
		pushdown(pos);
		return min(query(pos<<1,l,r),query(pos<<1|1,l,r));
	}
}tr;
void test()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],pre[i]=suf[i]=0;
	tr.build(1,1,n);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(tr.query(1,a[i],n))
		{
			cnt++;
			pre[cnt]=i;
			presum[cnt]=presum[cnt-1]+i;
			tr.add(1,a[i],n,-1);
		}
	}
	tr.build(1,1,n);
	cnt=0;
	for(int i=n;i>=1;i--)
	{
		if(tr.query(1,a[i],n))
		{
			cnt++;
			suf[cnt]=i;
			sufsum[cnt]=sufsum[cnt-1]+i;
			tr.add(1,a[i],n,-1);
		}
	}
	for(int i=n;i>=1;i--)
		if(pre[i]&&suf[i]&&pre[i]<=suf[i])
		{
			cout<<sufsum[i]-presum[i]<<"\n";
			return;
		}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test();
}
```

证明：  
这个贪心能假当且仅当某一个数不能标正号时，最优策略是撤销之前的某一个数的正号并给当前数标上。  
设最优策略撤销了位置 $y$ 上的正号给位置 $x$。  
若 $a_x\le a_y$，则这会 $\forall a_x\le z\le a_y$，$\le z$ 的数字数量增加 $1$，后面的局面将更难办，且贡献减少，显然不优。  
若 $a_x>a_y$，则其虽然使 $z\in(a_y,a_x]$ 中的限制变松了，但此时存在一个 $z>a_y$ 的很紧的限制（不能再加 $\le z$ 的数），则这前面的难做程度是无意义的，且这个过程中贡献变劣了，所以也劣。  
综上，每一种 $x,y$ 都不会使问题好做吗，这样一个贪心过程是正确的。

---

