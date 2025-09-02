# [USACO21FEB] No Time to Dry P

## 题目描述

Bessie 最近收到了一套颜料，她想要给她的牧草地一端的栅栏上色。栅栏由 $N$ 个 $1$ 米长的小段组成（$1\le N\le 2\cdot 10^5$）。Bessie 可以使用 $N$ 种不同的颜色，她将这些颜色由浅到深用 $1$ 到 $N$ 标号（$1$ 是很浅的颜色，$N$ 是很深的颜色）。从而她可以用一个长为 $N$ 的整数数组来描述她想要给栅栏的每一小段涂上的颜色。

初始时，所有栅栏小段均未被上色。Bessie 一笔可以给任意连续若干小段涂上同一种颜色，只要她不会在较深的颜色之上涂上较浅的颜色（她只能用较深的颜色覆盖较浅的颜色）。

例如，一段长为 $4$ 的未被涂色的栅栏可以按如下方式上色：

```
0000 -> 1110 -> 1122 -> 1332
```

不幸的是，Bessie 没有足够的时间等待颜料变干。所以，Bessie 认为她可能需要放弃为栅栏上某些小段上色！现在，她正在考虑 $Q$ 个候选的区间（$1\le Q\le 2\cdot 10^5$），每个区间用满足 $1 \leq a \leq b \leq N$ 的两个整数 $(a,b)$ 表示，为需要上色的小段 $a \ldots b$ 的两端点位置。

对于每个候选区间，将所有区间内的栅栏小段都涂上所希望的颜色，并且区间外的栅栏小段均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选区间的回答是独立的。

## 说明/提示

#### 样例 1 解释

在这个样例中，对应颜色为  `1 1 2` 的子段涂上颜色需要两笔。  
对应颜色为 `2 1 1 2` 的子段涂上颜色需要三笔。  
对应颜色为 `1 2 2 1 1 2` 的子段涂上颜色需要三笔。  
对应颜色为 `1 2 3 2` 的子段涂上颜色需要三笔。

#### 测试点性质

 - 对于 $10\%$ 的数据，满足 $N,Q\le 100$。
 - 对于另外 $15\%$ 的数据，满足 $N,Q\le 5000$。
 - 对于另外 $25\%$ 的数据，输入数组不包含大于 $10$ 的数。
 - 对于另外 $50\%$ 的数据，没有额外限制。

供题：Andi Qu，Brian Dean，Benjamin Qi

## 样例 #1

### 输入

```
8 4
1 2 2 1 1 2 3 2
4 6
3 6
1 6
5 8```

### 输出

```
2
3
3
3```

# 题解

## 作者：Alex_Wei (赞：9)

> [题目传送门](https://www.luogu.com.cn/problem/P7418)

> 题意简述：给出颜色序列 $a$，多次询问给出 $l,r$，求涂成 $a_l,a_{l+1},\cdots,a_r$ 的最小操作次数。每次涂色只能用一段数值更大的颜色覆盖原有的颜色。

> [在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/P7416.html)

---

首先考虑 $l=1,r=n$ 的情况：从左到右考虑每个位置上的颜色 $a_i$，记 $pre$ 为 $i$ 左边的颜色为 $a_i$ 的最大位置。若 $a_i\leq \min_{j=pre}^i a_j$ 则表明可以直接将颜色从 $pre$ 直接涂到 $i$，否则要再用一次操作。

从左到右不断加入新的位置 $i$，记 $ans_j$ 为 $[j,i]$ 的答案，考虑维护 $ans$：若 $a_i\leq \min_{j=pre}^i a_j$ 则只需将 $ans_{pre+1},ans_{pre+2},\cdots,ans_i$ 加 $1$；否则这个位置需要再用一次操作，也就是 $ans_1,ans_2,\cdots,ans_i$ 加 $1$。将所有询问按右端点排序，这样就是区间最值和区间加，单点查询，分别用 ST 表和树状数组维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair <int,int>

const int N=2e5+5;
int n,q,d[N],m[N<<1][18],ans[N],pre[N],lst[N];
vector <pii> e[N];
void add(int x,int v){while(x<=n)d[x]+=v,x+=x&-x;}
int query(int x){int ans=0; while(x)ans+=d[x],x-=x&-x; return ans;}

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>m[i][0],pre[i]=lst[m[i][0]],lst[m[i][0]]=i;
	for(int j=1;j<18;j++)for(int i=1;i<=n;i++)m[i][j]=min(m[i][j-1],m[i+(1<<j-1)][j-1]);
	for(int i=1,l,r;i<=q;i++)cin>>l>>r,e[r].emplace_back((pii){i,l});
	for(int i=1;i<=n;i++){
		int p=pre[i],d=log2(i-p);
		add(min(m[p+1][d],m[i-(1<<d)+1][d])<m[i][0]?1:p+1,1),add(i+1,-1);
		for(pii it:e[i])ans[it.first]=query(it.second);
	} for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Tony2 (赞：9)

首先想一下怎样涂色是最优的。

比如一个串`1221`。右边的`1`是不是一定是涂左边的时候延续过来的？

所以如果从左到右涂色的话，某个位置**如果不用自己新开始涂色**一定是来自它**左边第一个颜色相同的位置**的延续。

至于自己要不要新开始涂色可以预处理一下就可以了。具体处理方式是：某个位置和前一个位置之间是否有（比自己）更小的数字。如果有，那必须重新开始涂色。

回到题目：题目里会提出一小段来涂色。考虑下面这种情况：
```
1221
 ^ ^
 l r
```
这样最后一个1需要重新开始涂色，因为第一个1不会涂色。

那对于每一个位置都记录一个$lst[i]$，表示**左边第一个颜色相同的位置**，如果之间有比它们小的数字则为0。

对于所有$[l,r]$的位置，当$lst[i]<l$时，答案加一。这东西主席树维护。

```cpp
#include <bits/stdc++.h>
#define I int
#define ll long long
#define F for
#define In cin
#define ou cout
#define ln endl
#define pb push_back
using namespace std;
const I N=2e5+5;
I n,log2n,q;
I a[N],lst[N];
I st[N][30];
I rt[N];
map<I,I> mp;
struct tree{
#define mid ((l+r)>>1)
	I tot;
	struct node{
		I num,ls,rs;
	}a[N*40];
	void add(I &p,I o,I l,I r,I s,I k){
		a[p=++tot]=a[o];
		if(l==r)return void(a[p].num+=k);
		if(s<=mid)add(a[p].ls,a[o].ls,l,mid,s,k);
		else add(a[p].rs,a[o].rs,mid+1,r,s,k);
		a[p].num=a[a[p].ls].num+a[a[p].rs].num;
	}
	I ask(I p,I o,I l,I r,I s,I t){
		if(s<=l&&r<=t)return a[p].num-a[o].num;
		I res=0;
		if(s<=mid)res+=ask(a[p].ls,a[o].ls,l,mid,s,t);
		if(t>mid)res+=ask(a[p].rs,a[o].rs,mid+1,r,s,t);
		return res;
	}
#undef mid
}T;
I stmin(I l,I r){
	I tmp=log2(r-l+1);
	return min(st[l][tmp],st[r-(1<<tmp)+1][tmp]);
}
I main(){
	std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
//	freopen("in.txt","r",stdin);
//	freopen("out.out","w",stdout);
	In>>n>>q;
	log2n=log2(n);
	F(I i=1;i<=n;i++){
		In>>a[i];
		st[i][0]=a[i];
		I &p=mp[a[i]];
		lst[i]=p;
		p=i;
	}
	F(I j=1;j<=log2n;j++)
		F(I i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	F(I i=1;i<=n;i++)
		if(lst[i]&&stmin(lst[i],i)<a[i])
			lst[i]=0;
	F(I i=1;i<=n;i++){
		lst[i]++;//主席树没法查询0的位置 QAQ
		T.add(rt[i],rt[i-1],1,n,lst[i],1);
	}
	while(q--){
		I l,r;
		In>>l>>r;
		ou<<T.ask(rt[r],rt[l-1],1,n,1,l)<<ln;
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：8)

考虑对每个点 $i$ 求出 $pre_i$ 和 $nxt_i$ 表示它前面 / 后面第一个小于它的数的位置。这个可以用单调栈线性求。不难发现，对于两个 $pre,nxt$ 相同的点，它们一定可以在同一次涂色内涂完，中间比它们大的数可以后面再覆盖掉。

用一个 `map<pii,int>` 来给所有点**重新分配一次颜色**，$pre$ 和 $nxt$ 相同的点划到同一个颜色，不同的点划到不同的颜色，那么原问题就变成了静态区间数颜色数。把询问离线下来用树状数组解决即可。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
using pii=pair<int,int>;
int n,q;
struct BIT{
	int s[N];
	#define lb(x) ((x)&(-(x)))
	void add(int p,int x){
		while(p<=n){
			s[p]+=x;
			p+=lb(p);
		}
	}
	int sum(int p){
		int ss=0;
		while(p){
			ss+=s[p];
			p-=lb(p);
		}
		return ss;
	}
}bit;
int a[N],c[N];
map<pii,int>mp;
array<int,4>que[N];
int pre[N],nxt[N];
int lst[N],pos[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	stack<int>st;
	st.emplace(0);
	for(int i=1;i<=n;i++){
		while(a[st.top()]>=a[i])st.pop();
		pre[i]=st.top();
		st.emplace(i);
	}
	while(!st.empty())st.pop();
	st.emplace(n+1);
	for(int i=n;i>=1;i--){
		while(a[st.top()]>=a[i])st.pop();
		nxt[i]=st.top();
		st.emplace(i);
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!mp.count({pre[i],nxt[i]})){
			mp[{pre[i],nxt[i]}]=++cnt;
		}
		c[i]=mp[{pre[i],nxt[i]}];
	}
	for(int i=1;i<=n;i++){
		lst[i]=pos[c[i]];
		pos[c[i]]=i;
	}
	for(int i=1;i<=q;i++){
		cin>>que[i][1]>>que[i][0];
		que[i][2]=i;
	}
	sort(que+1,que+1+q);// r l i ans
	int x=1;
	for(int i=1;i<=n;i++){
		bit.add(i,1);
		if(lst[i])bit.add(lst[i],-1);
		while(que[x][0]==i){
			que[x][3]=bit.sum(que[x][0])-bit.sum(que[x][1]-1);//cout<<que[x][0]<<" "<<que[x][1]<<" "<<que[x][2]<<" "<<que[x][3]<<endl;
			x++;
		}
	}
	sort(que+1,que+1+q,[](auto x,auto y){
		return x[2]<y[2];
	});
	for(int i=1;i<=q;i++)cout<<que[i][3]<<"\n";
	return 0;
}
```

同学反映我代码太长了所以我来放个压行后的代码（

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,q,cnt=0,x=1;
struct BIT{
	int s[N];
	void add(int p,int x){while(p<=n){s[p]+=x;p+=(p&(-p));}}
	int sum(int p){int ss=0;while(p){ss+=s[p];p-=(p&(-p));}return ss;}
}bit;
int a[N],c[N],pre[N],nxt[N],lst[N],pos[N];
map<pair<int,int>,int>mp;
array<int,4>que[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	stack<int>st;st.emplace(0);
	for(int i=1;i<=n;i++){while(a[st.top()]>=a[i])st.pop();pre[i]=st.top();st.emplace(i);}
	while(!st.empty())st.pop();st.emplace(n+1);
	for(int i=n;i>=1;i--){while(a[st.top()]>=a[i])st.pop();nxt[i]=st.top();st.emplace(i);}
	for(int i=1;i<=n;i++){if(!mp.count({pre[i],nxt[i]})){mp[{pre[i],nxt[i]}]=++cnt;}c[i]=mp[{pre[i],nxt[i]}];lst[i]=pos[c[i]];pos[c[i]]=i;}
	for(int i=1;i<=q;i++){cin>>que[i][1]>>que[i][0];que[i][2]=i;}
	sort(que+1,que+1+q);
	for(int i=1;i<=n;i++){bit.add(i,1);if(lst[i])bit.add(lst[i],-1);while(que[x][0]==i){que[x][3]=bit.sum(que[x][0])-bit.sum(que[x][1]-1);x++;}}
	sort(que+1,que+1+q,[](auto x,auto y){return x[2]<y[2];});
	for(int i=1;i<=q;i++)cout<<que[i][3]<<"\n";
	return 0;
}
```

---

## 作者：ETHANK (赞：6)

考虑一段区间 $[l,r]$ 最多要涂 $r-l+1$ 笔，然而有些笔是“多余的”。不难发现，对于每对 $(x,y)$ 满足 $A_x=A_y<\min_{x<i<y}A_i$ （一对相同颜色且中间的颜色更深），我们可以少涂一笔。那么记区间内的 $(x,y)$ 对个数为$cnt$，所求的答案就是 $r-l+1-cnt$。

我们可以通过维护一个单调栈来找出所有这样的点对，栈内元素单调递增。如果新插入的元素和栈顶元素相等，那么它就是一对符合要求的点，更新 $cnt$ 和栈顶。最后对这些询问按照右端点坐标排序， 用树状数组来维护一段前缀的 $cnt$ ，离线处理每组询问即可。

时间复杂度： $O((N+Q)\log N)$ 。

代码：

```cpp
#include <bits/stdc++.h>
#define f first
#define s second
#define pi pair<int,int>
using namespace std;
const int N=2e5+5;
int n,q,a[N],stk[N],top,ans[N],bit[N];
inline void I(int x){for(;x<=n;x+=(x&-x))bit[x]++;}
inline int Q(int x){int res=0;for(;x;x-=(x&-x))res+=bit[x];return res;}
vector <pi> query[N];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1,l,r;i<=q;i++){
        scanf("%d%d",&l,&r);
        query[r].push_back({l,i});
    }
    for(int i=1;i<=n;i++){
        while(top&&a[stk[top]]>a[i])top--;
        if(top&&a[stk[top]]==a[i]){
            I(stk[top]);
            stk[top]=i;
        }else stk[++top]=i;
        if(query[i].size()){
            for(int j=0;j<query[i].size();j++){
                pi t=query[i][j];
                ans[t.s]=i-t.f+1-(Q(i)-Q(t.f-1));
            }
        }
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：约瑟夫用脑玩 (赞：3)

为什么就没有一篇简单好写的题解呢？

先将询问离线，挂在 r 上，然后从 1~n 依次加入每段栅栏。

每次向右移时先加自己的代价，再考虑能不能和前一个颜色连起来，如果可以就把前面的代价删掉，查询就是区间和，树状数组维护单改区查即可。

这里判能不能连起来可以用 RMQ，但码量太大，可以复制一遍树状数组，检查两个相同颜色中间有没有比其小的。

设当前颜色为 c ，也就是看当前比 c 小的个数和上一个 c 前比 c 小的个数差是否为 0。

这么简单的思路没人想到我也是服气。

[没人看的代码](https://www.luogu.com.cn/paste/5uzxoakg)

---

## 作者：PanH (赞：2)

这题做法好多，一篇题解一个做法。

这里提供另一种思路的**树状数组**做法。

考虑一个位置 $i$ 如果可以顺带着染色，应该要满足的条件：

当前位置与上一个同颜色的位置 $lst[i]$ 之间的数都比当前位置的值小，且 $lst[i]$ 应该要在询问区间内。

而如果区间 $[lst[i],i ]$ 中有小于 $a[i]$ 的值，无论如何这个位置都要染一次色，于是遇到这种情况可以直接对树状数组的 $0$ 的位置 $++$ （平移值域）。

其他情况的话，可以将树状数组的 $lst[i]$ 位置 $++$ ，相当于求区间内只出现一次的数。

这样处理之后，再将每个询问拆成两个，即：
$$
ans[i]=query(r,l-1)-query(l-1,l-1)
$$

（$query(i,j)$ 表示循环到位置 $i$ 时，树状数组求前 $j$ 个数的前缀和，即一个简单的容斥，减掉区间外的位置产生的贡献。）

其中区间求最小值我用了线段树 ~~（由于懒）~~。

code：
```
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
template<class T>inline void write(T x)
{
	if(x<0) return putchar('-'),write(-x);
	if(x>9) write(x/10);
	putchar('0'+x%10);
}
const int N=2e5+5;
struct Que{
	int l,r,op,id;
	bool operator < (const Que &o) const {return r<o.r;}
}q[N<<1];//询问翻倍了
int n,m,tree[N<<2],sum[N<<1],a[N],lst[N],ans[N<<1],tot;
#define mid ((l+r)>>1)
void build(int l,int r,int k)
{
	if(l==r) return tree[k]=a[l],void();
	build(l,mid,k<<1),build(mid+1,r,k<<1|1);
	tree[k]=min(tree[k<<1],tree[k<<1|1]);
}
int query(int l,int r,int k,int x,int y)
{
	if(x>y) return INF;
	if(l>=x&&r<=y) return tree[k];
	int res=INF;
	if(x<=mid) res=min(res,query(l,mid,k<<1,x,y));
	if(y>mid) res=min(res,query(mid+1,r,k<<1|1,x,y));
	return res;
}//其实ST表可能更好写一些。。。
void add(int x)
{
	for(int i=x+1;i<=n+1;i+=i&-i) sum[i]++;//树状数组平移值域
}
int Sum(int x)
{
	int res=0;
	for(int i=x+1;i;i-=i&-i) res+=sum[i];
	return res;
}
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;i++) read(a[i]);
	build(1,n,1);
	for(int i=1;i<=m;i++)
	{
		int L,R;read(L),read(R);
		if(L>1) q[++tot]=(Que){L,L-1,-1,i};//如果询问本身是从 1 开始，那么不用拆。
		q[++tot]=(Que){L,R,1,i};
	}
	sort(q+1,q+tot+1);
	for(int i=1,j=1;i<=n;lst[a[i]]=i,i++)
	{
		if(query(1,n,1,lst[a[i]]+1,i)<a[i]) add(0);
		else add(lst[a[i]]);
		while(q[j].r==i&&j<=tot)
			ans[q[j].id]+=Sum(q[j].l-1)*q[j].op,j++;
	}
	for(int i=1;i<=m;i++) write(ans[i]),puts("");
	return 0;
}

```


---

## 作者：Seauy (赞：2)

先考虑暴力怎么求 $[L,R]$ 的最少覆盖次数。颜色 $a$ 其实可以瞎涂，因为比他深的颜色 $b$ 总能覆盖掉他涂错的部分，但是 $a$ 不能覆盖已经涂过的比他浅的颜色 $c$。

所以 $[L,R]$ 覆盖的最优方案是：从浅到深涂色，尽量要连续，碰到比自己浅的才迫不得已断开。这个用树状数组线段树随便搞搞就能做到了。

但是本题又要求多次区间查询，考虑离线计算每个颜色对于查询的影响。

我们可以把同一种颜色所在的位置放入对应的 vector 中，然后从浅到深遍历每一种颜色。同一种颜色在两点间“有比自己浅的颜色”处断开。

比如 $\{2,1,2\}$ 在“1”处断开了。

同一种颜色的 vector 被断成了好几段，每一段都会对与自己有交集的查询产生一个贡献。注意这里的“段”其实是点的集合，因此我们要把“段”中点与点之间的区间都要扣掉。

比如我们有段 $\{1,3,4,6,7,9\}$（段中的数字都为原序列的下标），我们会让 $L\leq 1 \space , \space 9 \leq R$ 的查询都加一，但是如果查询被 $(1,3), (3,4),(4,6),(6,7),(7,9)$ 包含，跟“段”就没有交集，但是也被计算了贡献，于是我们又要对

$1 < L\leq R <3$

$3 < L\leq R <4$

$4 < L\leq R <6$

$6 < L\leq R <7$

$7 < L\leq R <9$

再减一，每个查询可以看作是二维平面上的点，扫描线搞掉离线的二维区间加单点查就行了。

时间 $O(n\lg n)$，空间 $O(n)$

```cpp
#include<bits/stdc++.h>
#define Lson (now<<1)
#define Rson (now<<1|1)
using namespace std;

const int MAXN=2e5;

struct Query
{
	int L,R,ID;
	void Scan() {scanf("%d %d",&L,&R);}
}ope[2*MAXN+5],Ask[MAXN+5];int Tail; 

int n,m,ans[MAXN+5];
vector<int> Col[MAXN+5];

struct BIT
{
	int sum[MAXN+5];
	void Clean() {for(int i=1;i<=n;i++) sum[i]=0;}
	int lowbit(int x) {return x&-x;}
	void Insert(int x) {for(;x<=n;x+=lowbit(x)) ++sum[x];}
	int Ask(int x)
	{
		int cnt=0;
		for(;x>0;x-=lowbit(x)) cnt+=sum[x];
		return cnt;
	}
	int GetSum(int L,int R) {return Ask(R)-Ask(L-1);}
}mapn;

bool cmp1(Query a,Query b)
{return (a.L==b.L ? (a.R==b.R ? !a.ID : a.R<b.R) : a.L>b.L);}

bool cmp2(Query a,Query b)
{return (a.L==b.L ? (a.R==b.R ? !a.ID : a.R>b.R) : a.L<b.L);}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1,A;i<=n;i++)
	{
		scanf("%d",&A); 
		Col[A].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		Ask[i].Scan();
		Ask[i].ID=i;
		ope[i]=Ask[i];
	}
   //加一
	Tail=m;
	for(int i=1;i<=n;i++)
	{
		for(int j=0,k;j<Col[i].size();j=k+1)
		{
			k=j;
			while(k+1<Col[i].size())
				if(mapn.GetSum(Col[i][j],Col[i][k+1])) break;
				else ++k;
			ope[++Tail]=Query{Col[i][k],Col[i][j],0};
		}
		for(int j=0;j<Col[i].size();j++) mapn.Insert(Col[i][j]);
	}
	mapn.Clean();
	sort(ope+1,ope+Tail+1,cmp1);
	for(int i=1;i<=Tail;i++)
		if(ope[i].ID) ans[ope[i].ID]=mapn.Ask(ope[i].R);
		else mapn.Insert(ope[i].R);
	//减一
	mapn.Clean();
	Tail=m;
	for(int i=1;i<=m;i++) ope[i]=Ask[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=0,k;j<Col[i].size();j=k+1)
		{
			k=j;
			while(k+1<Col[i].size())
				if(mapn.GetSum(Col[i][j],Col[i][k+1])) break;
				else
				{
					++k;
					if(Col[i][k]-Col[i][k-1]>1) ope[++Tail]=Query{Col[i][k-1]+1,Col[i][k]-1,0};
				}
		}
		for(int j=0;j<Col[i].size();j++) mapn.Insert(Col[i][j]);
	}
	mapn.Clean();
	sort(ope+1,ope+Tail+1,cmp2);
	for(int i=1;i<=Tail;i++)
		if(ope[i].ID) ans[ope[i].ID]-=mapn.Ask(n-ope[i].R+1);
		else mapn.Insert(n-ope[i].R+1);
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：UltiMadow (赞：2)

~~铂金组题好毒瘤啊（~~

不带修的区间问题，第一个想到莫队，考虑新加入/删除一个点的时候答案怎么变化

从左边新加入一个点的话，记右边第一个等于这个点的下标为 $a$，第一个小于这个点的下标为 $b$，如果 $b<a$ 则答案需要加一；反过来就是删除左边一个点的情况

同理从右边新加入一个点的话，记左边第一个等于这个点的下标为 $a$，第一个小于这个点的下表为 $b$，如果 $b>a$ 则答案需要加一；反过来就是删除右边一个点的情况

还需要求出左右第一个比它小的点，随便用一个数据结构维护一下即可

时间复杂度 $\mathcal O(Q\sqrt n)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 200010
using namespace std;
const int S=450;
int n,Q,a[MAXN],ans[MAXN];
int L[MAXN],R[MAXN],pre[MAXN];
struct qnode{int l,r,x,q;}que[MAXN];
bool cmp(qnode a,qnode b){
	if(a.x==b.x)return a.r<b.r;
	return a.x<b.x;
}
int t[MAXN<<2];
void pushup(int p){t[p]=min(t[p<<1],t[p<<1|1]);}
void build(int p,int l,int r){
	if(l==r){t[p]=a[l];return;}int mid=(l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);pushup(p);
}
int query(int p,int l,int r,int L,int R){
	if(L>R)return -1;
	if(L<=l&&r<=R)return t[p];int mid=(l+r)>>1;
	if(R<=mid)return query(p<<1,l,mid,L,R);
	if(L>mid)return query(p<<1|1,mid+1,r,L,R);
	return min(query(p<<1,l,mid,L,R),query(p<<1|1,mid+1,r,L,R));
}
int main(){
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,1,n);memset(pre,0,sizeof(pre));
	for(int i=1;i<=n;i++){
		if(pre[a[i]])L[i]=(query(1,1,n,pre[a[i]],i)<a[i]?-1:pre[a[i]]);
		else L[i]=-1;pre[a[i]]=i;
	}memset(pre,0,sizeof(pre));
	for(int i=n;i;i--){
		if(pre[a[i]])R[i]=(query(1,1,n,i,pre[a[i]])<a[i]?n+5:pre[a[i]]);
		else R[i]=n+5;pre[a[i]]=i;
	}
	for(int i=1;i<=Q;i++){
		int l,r;scanf("%d%d",&l,&r);
		que[i]=(qnode){l,r,l/S+1,i};
	}sort(que+1,que+Q+1,cmp);
	int l=1,r=0,res=0;
	for(int i=1;i<=Q;i++){
		int ql=que[i].l,qr=que[i].r;
		while(l>ql){l--;res+=R[l]>r;}
		while(r<qr){r++;res+=L[r]<l;}
		while(l<ql){res-=R[l]>r;l++;}
		while(r>qr){res-=L[r]<l;r--;}
		ans[que[i].q]=res;
	}
	for(int i=1;i<=Q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Thunder_S (赞：1)

[不一样的阅读体验。](https://www.cnblogs.com/Livingston/p/15150177.html)

## Solution

考虑每个右端点对左端点的贡献。

一段区间 $[l,r]$ 可以连续被 $i$ 上色仅限于 $l$ 到 $r$ 中没有比 $i$ 小的颜色存在。

预处理出每个点上一次出现同色位置 $pre_i$。

对于新加入的点 $i$，查询 $pre_i+1$ 到 $i-1$ 中的最小值 $mn$。设 $res_l$ 表示以 $l$ 为左端点的答案。

如果 $mn\ge a_i$​，说明 $a_i$ 是可以从 $pre_i$ 直接涂过来的，但是 $pre_i+1$ 到 $i-1$ 这个区间里的答案要加一，因为对于他们 $a_i$ 是第一次出现，需要重新涂色。

否则从 $1$ 到 $i+1$ 都要加一，因为要多操作一次。

对于询问考虑离线，对于每个右端点为 $i$ 的询问，查询左端点上的权值，即这个询问的答案。

为此我们需要一个数据结构满足区间最小值查询，区间修改，单点查询。普通的线段树可以轻松解决。

## Code

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005
using namespace std;
struct seg
{
	int mn,val,lazy;
}tree[N<<2];
int n,q,l,r,t[N],pre[N],a[N<<1],ans[N],qo[N][3],last[N],ls[N];
void build(int now,int l,int r)
{
	if (l==r)
	{
		tree[now].mn=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	tree[now].mn=min(tree[now<<1].mn,tree[now<<1|1].mn);
}
int getmin(int now,int l,int r,int p,int q)
{
	if (p>q) return 2147483647;
	if (l>=p&&r<=q) return tree[now].mn;
	int mid=(l+r)>>1,res=2147483647;
	if (p<=mid) res=min(res,getmin(now<<1,l,mid,p,q));
	if (q>mid) res=min(res,getmin(now<<1|1,mid+1,r,p,q));
	return res;
}
void pushup(int now,int len)
{
	if (tree[now].lazy)
	{
		tree[now<<1].lazy+=tree[now].lazy;
		tree[now<<1|1].lazy+=tree[now].lazy;
		tree[now<<1].val+=tree[now].lazy*(len-(len>>1));
		tree[now<<1|1].val+=tree[now].lazy*(len>>1);
		tree[now].lazy=0;
	}
}
void modify(int now,int l,int r,int p,int q,int v)
{
	if (l>=p&&r<=q)
	{
		tree[now].lazy+=v;
		tree[now].val+=v*(r-l+1);
		return;
	}
	pushup(now,r-l+1);
	int mid=(l+r)>>1;
	if (p<=mid) modify(now<<1,l,mid,p,q,v);
	if (q>mid) modify(now<<1|1,mid+1,r,p,q,v);
	tree[now].val=tree[now<<1].val+tree[now<<1|1].val;
}
int query(int now,int l,int r,int p)
{
	if (l==r) return tree[now].val;
	pushup(now,r-l+1);
	int mid=(l+r)>>1;
	if (p<=mid) return query(now<<1,l,mid,p);
	else return query(now<<1|1,mid+1,r,p);
}
int main()
{
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	build(1,1,n);
	for (int i=1;i<=n;++i)
	{
		pre[i]=t[a[i]];
		t[a[i]]=i;
	}
	for (int i=1;i<=q;++i)
	{
		scanf("%d%d",&l,&r);
		last[i]=ls[r];
		ls[r]=i;
		qo[i][1]=i;qo[i][2]=l;
	}
	for (int i=1;i<=n;++i)
	{
		if (getmin(1,1,n,pre[i]+1,i-1)<a[i]) modify(1,1,n,1,i,1);
		else modify(1,1,n,pre[i]+1,i,1);
		for (int j=ls[i];j;j=last[j])
			ans[qo[j][1]]=query(1,1,n,qo[j][2]);
	}
	for (int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：White_gugu (赞：0)

题意
-
给出一段长度为 $n$ 的目标区间，刚开始区间数都为0，每次可以使一段连续的区间的本身和一个数取 $min$ 值，此为一次操作，给出 $q$ 个询问，每次询问给出区间的左右端点 $l,r$ ，求使得区间 $[l,r]$ 变为目标区间的最小操作数。

方法
-
设 $i$ 的目标数为 $a_{i}$ ，首先可以肯定：先染色染较深的颜色（直至此区间所有的此颜色都染好），再染较浅的颜色，这样就能够构造出染色的方案。

设有两个目标数相同的位置 $a,b(a<b)$ ，考虑什么时候我们可以一次性将 $a$ 和 $b$ 同时染色，因为颜色深的会覆盖颜色浅的，所以当区间 $[a,b]$ 中有数比 $a$ 和 $b$ 的目标数要小的时候，若将 $a,b$ 同时染色，一定会经过这个点，所以只能分为两次染色。

我们设 $next_{i}$ 表示下一个与 $i$ 的目标数相同的位置，显然当区间 $[i,next_{i}]$ 内最小值为 $a_{i}$ 时，两个位置可以用一次操作搞定，此处可以用线段树区间求最小值解决。

题中没强制在线要求，我们可以离线做。将所有的询问按照 $l$ 从大到小排序(便于处理答案)，从后往前枚举 $i$ ，考虑将每一个要进行操作的起点处 $+1$ ，最后答案肯定是 $sum(l,r)$ ，所以我们可以先将 $sum(i)+1$ ，但是先前有 $next_{i}$ 可以不进行操作，所以要判断 $i$ 和 $next_{i}$ 能否连成一起，如果可以显然 $sum(next_{i})-1$ 

枚举时用指针判断是否到达 $l$ 并线段树区间求和记录下答案，最后输出就可以了。

时间复杂度 $O(n \log n)$ ，常数有点大，但可以过。

代码
-
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{
	int ll,rr,num;
}kkk[200200];
int n,q;
int a[200200];
int tree[2000800];
int tre[2000800];
int next[200800]; 
int tot[200050];
bool bz[200200];
int ans[200200];
int now=1;
void build(int k,int l,int r)
{
	if(l==r)
	{
		tree[k]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	tree[k]=min(tree[k*2],tree[k*2+1]);
}
int query(int k,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	return tree[k];
	int mid=(l+r)/2;
	if(R<=mid)
	return query(k*2,l,mid,L,R);
	else if(L>mid)
	return query(k*2+1,mid+1,r,L,R);
	else
	return min(query(k*2,l,mid,L,mid),query(k*2+1,mid+1,r,mid+1,R));
}
void add(int k,int l,int r,int d,int x)
{
	if(l==r)
	{
		tre[k]+=x;
		return;
	}
	int mid=(l+r)/2;
	if(d<=mid)
	add(k*2,l,mid,d,x);
	else
	add(k*2+1,mid+1,r,d,x);
	tre[k]=tre[k*2]+tre[k*2+1];
}
int query2(int k,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	return tre[k];
	int mid=(l+r)/2;
	if(R<=mid)
	return query2(k*2,l,mid,L,R);
	else if(L>mid)
	return query2(k*2+1,mid+1,r,L,R);
	else
	return query2(k*2,l,mid,L,mid)+query2(k*2+1,mid+1,r,mid+1,R);
}
bool cmp(node x,node y)
{
	return x.ll>y.ll;
}
int main()
{
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)
	{
		next[i]=tot[a[i]];
		tot[a[i]]=i;
	}
	build(1,1,n);
	for(int i=1;i<=q;i++)
	scanf("%d %d",&kkk[i].ll,&kkk[i].rr);
	for(int i=1;i<=q;i++)
	kkk[i].num=i;
	sort(kkk+1,kkk+q+1,cmp);
	for(int i=n;i>=1;i--)
	{
		add(1,1,n,i,1);
		if(next[i]&&query(1,1,n,i,next[i])>=a[i])
		add(1,1,n,next[i],-1);
		while(kkk[now].ll==i&&now<=q)
		{
			ans[kkk[now].num]=query2(1,1,n,kkk[now].ll,kkk[now].rr);
			now++;
		}	
		if(now>q)
		break;
	}
	for(int i=1;i<=q;i++)
	printf("%d\n",ans[i]);
}
```


---

## 作者：丛雨 (赞：0)

奶牛的题还是很~~友好~~，至少第一题还是挺简单的，不像后2道恶心

先考虑如何暴力

我们可以想到对于每个询问，递归地去做

我们先找到区间内最小的颜色，再用这些颜色所在的位置把区间分割开来，递归得到结果

例如，对于[1,2,2,1,1,2,3,2],我们第一次分割出了[2,2],[2,3,2],分割[2,3,2]则得到[3],[3]分割后得到[]

答案则为分割至空集的总次数

考虑优化

我们可以先对原序列建一颗树,边表示分割转移:

我们还需要从每个单位点向这个点被删时的区间连边,如下图（注意没方括号的为单位点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/o4uge3ii.png)

单位点的点权为0,区间的点权为1

所以答案为左右端点对应的单位点向上直到lca所包住的点权和

可以发现为dfs序连续的一段

但这并不正确

首先dfs序会遗忘掉左端点到根的一段

其次是如果左端点在往上跳的过程中，如果它的右边（包括自己）没有兄弟是单位点，则它的父亲不会产生贡献

同理如果右端点往上跳的时候左边（包括自己）没有单位点则不产生贡献

所以我们加上dfs序那一段后还需加上左端点到lca的贡献再减去右端点多算的贡献

查询区间最小值可以用标准RMQ优化至$O(\log_2n)$,建树时存下每个值出现的位置，暴力后退，均摊$O(1)$.查询时可以离线tarjan$O(1)$计算lca

总时间复杂度$O(n)$

但我是个懒狗，打的$O(n\log_2n)$求$\tt lca$和线段树查区间最小值

```cpp
#include<bits/stdc++.h> 
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t; 
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define N 1000005
vector<int>h[200005],G[N];
vector<int>::iterator nx[200005];
int va[N],s,m,tot,dfn[200005],a[N],hi[N],fa[N][22],hv[N],nv[N];
void build(int l,int r,int d){
	if(l==r){
		h[va[d]=read].push_back(l);
		return;
	}int mid=l+r>>1;
	build(l,mid,d<<1);
	build(mid+1,r,d<<1|1);
	va[d]=min(va[d<<1],va[d<<1|1]);
}
int query(int l,int r,int tl,int tr,int d){
	if(l==tl&&r==tr)return va[d];
	int mid=tl+tr>>1;
	if(r<=mid)return query(l,r,tl,mid,d<<1);
	if(mid<l)return query(l,r,mid+1,tr,d<<1|1);
	return min(query(l,mid,tl,mid,d<<1),query(mid+1,r,mid+1,tr,d<<1|1));
}
int tbuild(int l,int r){
	int n=++tot,v=query(l,r,1,s,1);a[n]=1;
	vector<int>::iterator &x=nx[v];
	while(x!=h[v].end()&&*x<l)++x;
	int la=l-1,tv;
	for(;x!=h[v].end()&&*x<=r;++x){
		if(la+1<*x)hv[tot+1]=1,nv[tot+1]=la==l-1,G[n].push_back(tv=tbuild(la+1,*x-1));
		G[n].push_back(dfn[*x]=++tot);hv[tot]=1;
		la=*x;
	}if(la!=r)nv[tot+1]=la==l-1,G[n].push_back(tv=tbuild(la+1,r));
	return n;
}void dfs(int n){
	for(int i=0;fa[n][i+1]=fa[fa[n][i]][i];++i);
	for(int i=0;i<G[n].size();++i)
		if(G[n][i]!=fa[n][0]){
			hi[G[n][i]]=hi[n]+1;
			hv[G[n][i]]+=hv[n];
			nv[G[n][i]]+=nv[n];
			fa[G[n][i]][0]=n;
			dfs(G[n][i]);
		}
}
int lca(int x,int y){
	if(hi[x]<hi[y])swap(x,y);
	for(int i=0,t=hi[x]-hi[y];t>>i;++i)
		if(t>>i&1)x=fa[x][i];
	if(x==y)return x;
	for(int i=20;fa[x][0]!=fa[y][0];--i)
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	return fa[x][0];
}
int main(){
	s=read,m=read;
	build(1,s,1);
	for(int i=1;i<=s;++i)nx[i]=h[i].begin();
	tbuild(1,s);dfs(1);
	for(int i=1;i<=tot;++i)a[i]+=a[i-1];
	for(int i=1;i<=m;++i){
		int l=read,r=read,w=lca(dfn[l],dfn[r]);
		if(l==r){puts("1");continue;}
		printf("%d\n",a[dfn[r]]-a[dfn[l]-1]+hv[dfn[l]]-hv[w]-nv[dfn[r]]+nv[w]);
	}
	return 0;
}
```



---

