# Seating Arrangements (hard version)

## 题目描述

It is the hard version of the problem. The only difference is that in this version $ 1 \le n \le 300 $ .

In the cinema seats can be represented as the table with $ n $ rows and $ m $ columns. The rows are numbered with integers from $ 1 $ to $ n $ . The seats in each row are numbered with consecutive integers from left to right: in the $ k $ -th row from $ m (k - 1) + 1 $ to $ m k $ for all rows $ 1 \le k \le n $ .

  $ 1 $

 $ 2 $  $ \cdots $  $ m - 1 $  $ m $  $ m + 1 $

 $ m + 2 $  $ \cdots $  $ 2 m - 1 $  $ 2 m $  $ 2m + 1 $

 $ 2m + 2 $  $ \cdots $  $ 3 m - 1 $  $ 3 m $  $ \vdots $

 $ \vdots $  $ \ddots $  $ \vdots $  $ \vdots $  $ m (n - 1) + 1 $

 $ m (n - 1) + 2 $  $ \cdots $  $ n m - 1 $  $ n m $ The table with seats indicesThere are $ nm $ people who want to go to the cinema to watch a new film. They are numbered with integers from $ 1 $ to $ nm $ . You should give exactly one seat to each person.

It is known, that in this cinema as lower seat index you have as better you can see everything happening on the screen. $ i $ -th person has the level of sight $ a_i $ . Let's define $ s_i $ as the seat index, that will be given to $ i $ -th person. You want to give better places for people with lower sight levels, so for any two people $ i $ , $ j $ such that $ a_i < a_j $ it should be satisfied that $ s_i < s_j $ .

After you will give seats to all people they will start coming to their seats. In the order from $ 1 $ to $ nm $ , each person will enter the hall and sit in their seat. To get to their place, the person will go to their seat's row and start moving from the first seat in this row to theirs from left to right. While moving some places will be free, some will be occupied with people already seated. The inconvenience of the person is equal to the number of occupied seats he or she will go through.

Let's consider an example: $ m = 5 $ , the person has the seat $ 4 $ in the first row, the seats $ 1 $ , $ 3 $ , $ 5 $ in the first row are already occupied, the seats $ 2 $ and $ 4 $ are free. The inconvenience of this person will be $ 2 $ , because he will go through occupied seats $ 1 $ and $ 3 $ .

Find the minimal total inconvenience (the sum of inconveniences of all people), that is possible to have by giving places for all people (all conditions should be satisfied).

## 说明/提示

In the first test case, there is a single way to give seats: the first person sits in the first place and the second person — in the second. The total inconvenience is $ 1 $ .

In the second test case the optimal seating looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566D2/80308625ebb7c50e30fb4af9e2e0a85ec7f6e480.png)In the third test case the optimal seating looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566D2/46f26744e5411d13af43bc68c4d54fb7352debca.png)The number in a cell is the person's index that sits on this place.

## 样例 #1

### 输入

```
7
1 2
1 2
3 2
1 1 2 2 3 3
3 3
3 4 4 1 1 1 1 1 2
2 2
1 1 2 1
4 2
50 50 50 50 3 50 50 50
4 2
6 6 6 6 2 2 9 6
2 9
1 3 3 3 3 3 1 1 3 1 3 1 1 3 3 1 1 3```

### 输出

```
1
0
4
0
0
0
1```

# 题解

## 作者：Jur_Cai (赞：3)

[题意 & 简单分析在 D1](https://www.luogu.com.cn/blog/105865/solution-cf1566d1)

沿着 D1 的思路，我们只需要维护当前进入的人，所在行视力比他差的人的个数，这个可以用树状数组维护每一行。但 $a_i$ 的范围很大，且只需要大小关系，可以离散化。

但如果同一视力的人跨越了很多行呢？同样顺延 D1 的贪心，因为不要求输出方案，同一行里随便进，先进靠前的行。这个实际也比较好想，因为在靠前的交界处这个人的列数必定靠后，先放这个必然不会更劣。处理就是离散化的时候用 `stable_sort`，顺便处理出每个人的位置，就可以保证进入时间靠前的位置也靠前。

详见代码
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
#define lowbit(x) x&-x 
using namespace std;
map<int,int> mp;
struct node {
	int elem,id;
	bool operator<(const node b) const {
		return this->elem<b.elem;
	}
}a[100005],b[100005];
int cnt,n,m;
int tree[305][90005];
//树状数组板子
//p是行数，每行用一个树状数组维护
inline void update(int p,int x) {
	for(;x<=cnt;x+=lowbit(x)) tree[p][x]++;
}
inline int query(int p,int x){
	int sum=0;
	for(;x;x-=lowbit(x)) sum+=tree[p][x];
	return sum;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n*m;i++)
			scanf("%d",&a[i].elem),b[i].elem=a[i].elem,b[i].id=i;
		stable_sort(b+1,b+n*m+1);
		mp.clear(),cnt=0;
		for(int i=1;i<=n*m;i++) {
			a[b[i].id].id=i;//a.id表示该人座位
			//离散化
			if(mp.find(b[i].elem)==mp.end()) mp[b[i].elem]=++cnt;
		}
		//十年CF一场空，memset见祖宗
		for(int i=1;i<=n;i++)
			for(int j=1;j<=cnt;j++)
				tree[i][j]=0;
		for(int i=1;i<=n*m;i++) {
			int l=(a[i].id-1)/m+1;//该人的行数
			//树状数组里存的是离散化后对应值的个数
			//所以query直接查询小于当前值的前缀和就是所需
			ans+=query(l,mp[a[i].elem]-1);
			update(l,mp[a[i].elem]);
		}
		cout<<ans<<'\n';
	} 
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

来一发清晰的题解~

相信大家一定会做 Easy Vision 了吧……（不就是个贪心嘛）

而若将 cinema 看成一条序列，则 Easy Vision ->  Hard Vision 的唯一区别是**人可以从序列里下标为 $m$ 的倍数的 seat 之后插入并右移至目标位置。**

e.g.

![](https://i.loli.net/2021/09/16/qZYpIbaKrcAEfs1.png)

于是构造一个二维序列 $row_i(j)$ 表示第 $i$ 个块（图中一个红色矩形为一块）中第 $j$ 个 seat 是否空闲（空闲为 $1$，否则为 $0$）。

通过预处理数据，可知一个人 $x$ 在最终 cinema 座位编号的范围 $[L(x),R(x)]$，而且**近视度数相同的人范围一定相同，近视度数不同的人范围一定不相交**。

所以从 $1$ 至 $nm$ 编号的人依次进入 cinema，依次贪心地安排 seat。

* 若 $L(x)$ 与 $R(x)$ 同 $row$，则同 Easy Vision 一样，选择最靠 $R(x)$ 的空闲的 seat 坐下。

* 若不同 $row$，则优先坐 $L(x)$ 那 $row$ 右边（因为之后可能有更多人插到这 $row$ 的左边），坐满则坐中间几 $row$ 的右边（因为这些 $row$ 都被同一近视度数的人包场了），否则只能坐 $R(x)$ 那 $row$ 最右边可能的位置（因为这样之前可以有更多人插到这 $row$ 的右边）。

用树状数组维护即可。

[Code](https://codeforces.com/contest/1566/submission/128992162)

---

## 作者：Umbrella_Leaf (赞：1)

### 题目大意

> 你有 $n\times m$ 个数，要把它们排进一个 $n\times m$ 的矩阵中，且须满足从上到下、从左到右的数值不严格递增。设第 $i$ 行，第 $j$ 列排的数在输入中是第 $p_{i,j}$ 个。定义第 $k$ 行的不方便值为 $1\le i<j\le m$ 且 $p_{k,i}<p_{k,j}$ 的 $i,j$ 个数。求所有行不方便值之和的最小值。

### 做法

首先注意到让我们求的相当于 $p$ 在每一行的顺序对数之和的最小值。

那么考虑对于相同的值，先求出这个值在最终的矩阵中排在哪一块（显然这这个位置是固定的）。

有两种情况（红框是该值的位置）：

![](https://cdn.luogu.com.cn/upload/image_hosting/r7r8bevs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/20pwt58k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第一种情况，显然应该按输入顺序倒序排序。

对于第二种，在最上面一块偏右的，应该选择在输入中尽量靠前的倒序排；最下面偏左的，应该选择在输入中尽量靠后的倒序排；中间的直接倒序排。

这样就可以求出最优方案下每个数排在哪里。然后按题意数一遍顺序对数就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
int a[200005],b[200005];
vector<int> v[200005];
int s[200005],cnt;
int invs[200005];
int num[200005];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n*m;i++){
			scanf("%d",&a[i]);
			b[i]=a[i];
		}
		sort(b+1,b+n*m+1);
		int mx=unique(b+1,b+n*m+1)-b-1;
		for(int i=1;i<=n*m;i++)a[i]=lower_bound(b+1,b+mx+1,a[i])-b;
		for(int i=1;i<=mx;i++)v[i].clear();
		for(int i=1;i<=n*m;i++)v[a[i]].push_back(i);
		cnt=0;
		for(int i=1;i<=mx;i++){
			int len1=min((int)v[i].size(),m-cnt%m);
			for(int j=len1-1;j>=0;j--)s[++cnt]=v[i][j];
			if(v[i].size()>len1){
				int lenlen=v[i].size()-len1;
				int len2=lenlen/m*m;
				for(int j=len2+len1-1;j>=len1;j--)s[++cnt]=v[i][j];
				for(int j=v[i].size()-1;j>=len2+len1;j--)s[++cnt]=v[i][j];
			}
		}
//		for(int i=1;i<=n*m;i++)printf("%d ",s[i]);puts("");
		for(int i=1;i<=n*m;i++)invs[s[i]]=i;
		int ans=0;
		memset(num,0,sizeof(num));
		for(int i=1;i<=n*m;i++){
			for(int j=(invs[i]-1)/m*m+1;j<invs[i];j++)if(num[j])ans++;
			num[invs[i]]++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：GaryH (赞：0)

# CF1566D2 题解
~~赛后才发现不用树状数组优化就能过。。。~~

**题意**：

给定 $n \times m$ 个数和一个初始为空的 $n \times m$ 大小的矩阵，要求将数一一填入矩阵，并满足任意两个位置的价值的大小关系与两个位置里填入的数的大小关系相同。

求一种方案，使得依次填入每一个数的代价和最小，并输出这个最小值，其中填入一个数的代价是其位置左边已填入的数的个数，位置 $(x,y)$ 的价值是 $x \times m + y$

显然，对于任意两个不相同的数，它们两个填入的位置的价值的大小关系是确定的，那么假设所有数两两不等，则填数的方案数就已经确定了。

那么，若是有相同的数，又该如何处理呢？

为了方便表示，我们记该数值为 $x$ ，等于该值的数的下标分别为 $i_1,i_2,...,i_k$ ，则这些数在一一放置好后，最终所在的位置对应到矩阵上，一定形成了几段连续的区间。并且，这些位置的价值也一定在值域上连续。那么，我们需要确定的，就是相同的数的放置方法。

再理一理思路，我们注意到，放数的先后顺序的决策权不在我们手中，我们手中的决策权，只能确定每个数最终在的位置，并且这个放置位置的方案还必须满足对于数之间大小关系的限制，故我们真正可以决定的，只有相同数的放置位置。

这时，我们采用一个贪心的思路，且一定是最优的。

可以考虑两个相同的数，它们所放置的位置带来的影响：

设有两个数 $a,b$ ，值都为 $x$ ，目前有 $(x,y),(x,y+1)$ 两个位置可供放置,而数 $a,b$ 分别在第 $j,k$ 次放入。不妨设 $j<k$ 。

此时，我们说：将 $a$ 放到位置 $(x,y+1)$ ，将 $b$ 放到位置 $(x,y)$ 一定更优，因为这样放对答案的贡献为 $0$ ；而若是将 $a$ 放到位置 $(x,y)$ ，将 $b$ 放到位置 $(x,y+1)$ ，这样的贡献是 $1$ ,就没有刚才的方法更优。

我们由此可以联想到真正的电影院里的座位：在最里面的人最先进去，在最外面的人最后进去，这样安排一定是最方便的，且每个人经过的人也最少。

那我们只需要按照这个宗旨去处理这个问题即可：

每次找到等于值 $x$ 的所有数的下标 $i_1,i_2,...,i_k$ ，若它们可选的所有位置在同一行，我们就按它们填入的先后顺序倒序安排座位；若它们可选的所有位置不在同一行，则每一行中都倒序排列，而所有位置所在行中最上面那不一定完整的一行放最大的若干个数，最下面那不一定完整的一行放最小的若干个数即可。

于是我们只需先确定每个数所在的座位，再按题意模拟算贡献即可，时间复杂度是 $O(nm^2)$ ，本题可以通过。

但实际上，在模拟算贡献时，我们需要对每一行支持单点修改，区间查询，这时我们可以不遍历整行，而是每一行维护一个树状数组，来快速的支持这个操作，此时时间复杂度优化到了 $O(nmlogm)$。

至于实现方法，可以在下面的代码和注解里看到。（~~我的实现方法可能很烂~~）

**code:**

```

const int N(305);

int n,m;
int idx;

int a[N*N];

inline bool cmp(int x,int y){return x>y;}

struct BIT{
	// 树状数组
	int t[N<<2];
	void add(int x,int val){
		while(x<=m)t[x]+=val,x+=(x&-x);
	}
	int qry(int x){
		int res=0;
		while(x)res+=t[x],x-=(x&-x);
		return res;
	}
}bit[N];

inline pii gtline(int pos){
	// 算出矩阵中某个权对应的行和列
	int x=(pos/m);
	if(x*m!=pos)x++;
	int y=pos%m;
	if(!y)y=m;
	return mp(x,y);
}

int pla[N*N];

inline void work(){
	// 多组数据
	map < int , vector < int > > buk ;
    	// buk 的作用是将每个数按权值归类
	n=read(),m=read(),idx=0;
	int ALL=n*m,ans=0;
	rep(i,1,ALL)buk[a[i]=read()].pb(i);
	sort(a+1,a+ALL+1); int T=unique(a+1,a+ALL+1)-a-1;
    	// 排序后去重，即可避免处理重复的数
	int now=0;
	rep(i,1,T){
		int sz=buk[a[i]].size();
		int st=now+1,en=now+sz;
		pii tmps=gtline(st),tmpe=gtline(en);
		int sx=tmps.fi,sy=tmps.se;
		int ex=tmpe.fi,ey=tmpe.se;
		sort(buk[a[i]].begin(),buk[a[i]].end());
		if(sx==ex){
			per(j,sz-1,0)pla[buk[a[i]][j]]=(++now);
			continue;
		}
		per(j,m-sy,0)pla[buk[a[i]][j]]=(++now);
		per(j,sz-ey-1,m-sy+1)pla[buk[a[i]][j]]=(++now);
		per(j,sz-1,sz-ey)pla[buk[a[i]][j]]=(++now);
        	// 处理出每个数最终填入的位置
	}
	rep(i,1,ALL){
		pii tmp=gtline(pla[i]);
		int x=tmp.fi,y=tmp.se;
		ans+=bit[x].qry(y-1),bit[x].add(y,1ll);
        	// 按题意算贡献
	}
	cout<<ans<<endl;
	rep(i,0,n)rep(j,0,(m<<2))bit[i].t[j]=0ll;
	rep(i,1,(n*m))pla[i]=0ll;
    	// 多组数据一定要清空！！！
}

int main(){
	int tasks=read();
	while(tasks--)work();
	return 0;
}

```

---

## 作者：KSToki (赞：0)

# 题目大意
有 $n\times m$ 个人和 $n$ 排每排 $m$ 个座位，每个人对应一个值 $a_i$，$a_i$ 越小的人要坐越靠前（在 D1 的基础上排数也要靠前），从第 $1$ 个人到第 $n\times m$ 个人依次从他的位置对应的那一排从前往后走，代价为经过的人数，安排座位最小化总代价。
# 题目分析
其实和 D1 差别不大，先挂一个[D1题解](https://www.luogu.com.cn/blog/ypcaeh/solution-cf1566d1)，只是多了一个在不同排的人代价互不影响。还是只用在内部考虑最小化代价，仍然贪心，这下先往靠前的排坐，再往靠后的座位坐即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,a[90001],t[90001],k,cnt[90001],s[90001],c[301][301],v[90001];
vector< pii >pos[90001];
I void update(int op,int x,int v)
{
	for(;x<=m;x+=lowbit(x))
		c[op][x]+=v;
} 
I int sum(int op,int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=c[op][x];
	return res;
}
I pii rget(int x)
{
	return mp((x-1)/m+1,(x-1)%m+1);
}
I bool cmp(pii x1,pii x2)
{
	return x1.fi==x2.fi?x1.se>x2.se:x1.fi<x2.fi;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		For(i,1,n*m)
		{
			t[i]=a[i]=read();
			cnt[i]=s[i]=v[i]=0;
			pos[i].clear();
		}
		For(i,1,n)
			For(j,1,m)
				c[i][j]=0;
		sort(t+1,t+n*m+1);
		k=unique(t+1,t+n*m+1)-t-1;
		For(i,1,n*m)
		{
			a[i]=lower_bound(t+1,t+k+1,a[i])-t;
			++cnt[a[i]];
		}
		For(i,1,k)
		{
			s[i]=s[i-1]+cnt[i];
			For(j,1,cnt[i])
				pos[i].pb(rget(s[i-1]+j));
			sort(pos[i].begin(),pos[i].end(),cmp);
		}
		int ans=0;
		For(i,1,n*m)
		{
			ans+=sum(pos[a[i]][v[a[i]]].fi,pos[a[i]][v[a[i]]].se);
			update(pos[a[i]][v[a[i]]].fi,pos[a[i]][v[a[i]]].se,1);
			++v[a[i]];
		}
		putint(ans);
	}
	return 0;
}

```

---

