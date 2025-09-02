# In Love

## 题目描述

Initially, you have an empty multiset of segments. You need to process $ q $ operations of two types:

- $ + $ $ l $ $ r $ — Add the segment $ (l, r) $ to the multiset,
- $ - $ $ l $ $ r $ — Remove exactly one segment $ (l, r) $ from the multiset. It is guaranteed that this segment exists in the multiset.

After each operation, you need to determine if there exists a pair of segments in the multiset that do not intersect. A pair of segments $ (l, r) $ and $ (a, b) $ do not intersect if there does not exist a point $ x $ such that $ l \leq x \leq r $ and $ a \leq x \leq b $ .

## 说明/提示

In the example, after the second, third, fourth, and fifth operations, there exists a pair of segments $ (1, 2) $ and $ (3, 4) $ that do not intersect.

Then we remove exactly one segment $ (3, 4) $ , and by that time we had two segments. Therefore, the answer after this operation also exists.

## 样例 #1

### 输入

```
12
+ 1 2
+ 3 4
+ 2 3
+ 2 2
+ 3 4
- 3 4
- 3 4
- 1 2
+ 3 4
- 2 2
- 2 3
- 3 4```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
NO
YES
NO
NO
NO```

# 题解

## 作者：yydfj (赞：6)

这是本蒟蒻第四十二次写的题解，如有错误点请好心指出！

## 问题简述

你有 $T$ 次操作，每次操作为添加或删除一条区间范围为 $[l,r]$ 的线段，问每次操作后是否存在两条线段，使得它们的区间范围没有交集。

## 解法综述

考虑如何判断符合条件的两条线段，贪心可得我们取当前所有线段中最小的 $r$，以及最大的 $l$，如果 $l>r$，说明该条件合法，可以证明如果 $l \le r$，那么任取某一线段，它与其它任意线段都有交集。

使用 multiset 可以快速地维护我们要求的 $l$ 和 $r$，注意删除 $x$ 时要使用 find 查找 $x$ 的迭代器，否则会将整个值为 $x$ 的元素删掉，而不是删除其中一个元素。

## 代码描述

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T;
struct node{
	ll v;
	bool operator<(const node &x)const{
		return x.v<v;
	}
};
multiset<node> st;
multiset<int> st1;
int main()
{
	cin>>T;
	while(T--)
	{
		ll l,r;
		char c;
		cin>>c>>l>>r;
		if(c=='+')
		{
			st.insert({l});
			st1.insert(r);
		}
		if(c=='-')
		{
			st.erase(st.find({l}));//使用find查找该值的迭代器
			st1.erase(st1.find(r));
		}
		if(st.size()>1)
		{
			if((*st.begin()).v>*st1.begin()) cout<<"YES\n";
			else cout<<"NO\n";
		}
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：LiJoQiao (赞：4)

[原题链接](https://codeforces.com/contest/1883/problem/D) [洛谷题面](https://www.luogu.com.cn/problem/CF1883D) [提交记录](https://www.luogu.com.cn/record/132026044)  
### 题目大意  
有 $q$ 次操作，为以下操作之一：  
>1. 加入一条端点分别为 $l$，$r$ 的线段。  
>2. 删除一条端点分别为 $l$，$r$ 的线段。 

每次操作后输出是否存在一对不相交的线段。  
### 题目分析  
存在一对不相交的线段当且仅当 $l_{max}$ > $r_{min}$（即有右端点在左端点的左边）。  

我们用 `multiset` 即可解决这个查询的问题。  
代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>sl,sr;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int q;cin>>q;
	while(q){
		--q;
		char c;int l,r;cin>>c>>l>>r;
		if(c=='+'){
			sl.insert(l);sr.insert(r);
			auto it=sl.end();
			if(*sr.begin()<*(--it)){
				cout<<"YES\n";
			}
			else cout<<"NO\n";
		}
		else{
			sl.erase(sl.find(l));
			sr.erase(sr.find(r));
			auto it=sl.end();
			if(!sr.empty()&&!sl.empty()&&*sr.begin()<*(--it)){
				cout<<"YES\n";
			}
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：Falling_Sakura (赞：1)

# 思路

由于删除线段时一定保证该线段存在，所以我们可以分别开两个 multiset，分别维护线段的左端点最大值和右端点最小值，然后就可以判断了。

注意判断集合为空时答案为 $\text{NO}$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

multiset<int> ml, mr;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        char op[2];
        scanf("%s", op);
        int l, r;
        scanf("%d%d", &l, &r);
        if(*op == '-')
        {
            ml.erase(ml.find(l));
            mr.erase(mr.find(r));
        }
        else
        {
            ml.insert(l);
            mr.insert(r);
        }
        if(!ml.size())
        {
            cout << "NO" << endl;
        }
        else if(*(prev(ml.end())) > *mr.begin())
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
```

---

## 作者：mygr (赞：1)

原题链接：[In Love](https://codeforces.com/contest/1883/problem/D)

大致题意：有 $q$ 个询问，每次两个操作
1. 添加一条线段 $l_i,r_i$。

2. 删去一条线段 $l_i,r_i$ 保证这条线段曾经被添加过。

每次操作过后，询问是否存在两条线段没有重合部分，若存在则输出 YES 否则输出 NO。

很好理解吧。

很容易想到**寻找是否存在两条线段没有重合部分**其实也就相当于**询问所有的线段都在一个点重合**。

当然需要特判当前场上的点的数量为 0 或 1 的情况，此时一定不存在重合部分。

区间，重合，计数，这不就是线段树吗！

所有线段都在一个点重合，其实也就相当于寻找**是否存在一个点被多少条线段覆盖的数量**为**当前场上的线段数量**。

接下来就很好理解了，用一棵动态开点线段树维护区间最大覆盖次数即可。

关于动态开点线段树的数组大小，我的建议是开 32 倍（虽然我开了 40 倍）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2e5;
struct tree{
	int l,r,Max,lazy;
}p[Maxn*40];
int t,idx=1,Maxr,Minl=0x7fffffff;
int op,l,r;
char c;
void pushup(int now)
{
	p[now].Max=max(p[p[now].l].Max,p[p[now].r].Max);
}
void pushdown(int now)
{
	if(p[now].lazy)
	{
		if(!p[now].l)
			p[now].l=++idx;
		if(!p[now].r)
			p[now].r=++idx;
		p[p[now].l].Max+=p[now].lazy;
		p[p[now].r].Max+=p[now].lazy;
		p[p[now].l].lazy+=p[now].lazy;
		p[p[now].r].lazy+=p[now].lazy;
		p[now].lazy=0;
	}
}
void add(int now,int l,int r,int nl,int nr,int num)
{
	if(l<=nl and nr<=r)
	{
		p[now].Max+=num;
		p[now].lazy+=num;
		return ;
	}
	int mid=(nl+nr)>>1;
	pushdown(now);
	if(l<=mid)
	{
		if(!p[now].l)
			p[now].l=++idx;
		add(p[now].l,l,r,nl,mid,num);
	}
	if(mid<r)
	{
		if(!p[now].r)
			p[now].r=++idx;
		add(p[now].r,l,r,mid+1,nr,num);
	}
	pushup(now);
}
struct mode{
	int op,l,r;
}mod[Maxn];
int main()
{
	scanf("%d",&t);
	int tot=0;
	for(int k=1;k<=t;k++)
	{
		c=getchar();
		while(c!='+' and c!='-')c=getchar();
		if(c=='+')
			op=1;
		else 
			op=2;
		scanf("%d%d",&l,&r);
		mod[k].op=op;
		mod[k].l=l;
		mod[k].r=r;
		Maxr=max(Maxr,r);
		Minl=min(Minl,l);
	}
	for(int k=1;k<=t;k++)
	{
		op=mod[k].op;
		l=mod[k].l;
		r=mod[k].r;
		if(op==1)
		{
			tot++;
			add(1,l,r,Minl,Maxr,1);
		}
		else
		{
			tot--;
			add(1,l,r,Minl,Maxr,-1);
		}
		if(tot==1 or tot==0 or p[1].Max==tot)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
}
```


---

## 作者：FireRain (赞：0)

# 思路

如果我们将加入一条线段 $[l_i,r_i]$ 记作将 $[l_i,r_i]$ 区间加 $1$；反之减 $1$。

可以发现如果一个点被两条线段覆盖，这个点上的权值为 $2$；如果被三条线段覆盖，这个点上的权值为 $3$；以此类推。

那么不难发现，如果一个点的权值为当前线段的数量 $num$，说明所有的线段都会在这个重合。

否则，可以证明一定有选取方案使得条件成立。

所以维护一个 区间最大值 + 区间加法 即可，可以用线段树维护。

由于 $l,r$ 范围较大，所以需要离散化。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int q,num;
int l[N],r[N];
bool op[N];
vector<int> p;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

struct seg{
	#define ls(u) (u << 1)
	#define rs(u) (u << 1 | 1)
	
	struct node{
		int l;
		int r;
		int Max;
		int tag;
	}tr[N << 2];
	
	inline void calc(int u,int k){
		tr[u].Max += k;
		tr[u].tag += k;
	}
	
	inline void pushup(int u){
		tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
	}
	
	inline void pushdown(int u){
		if (tr[u].tag){
			calc(ls(u),tr[u].tag);
			calc(rs(u),tr[u].tag);
			tr[u].tag = 0;
		}
	}
	
	inline void build(int u,int l,int r){
		tr[u] = {l,r};
		if (l == r) return;
		int mid = l + r >> 1;
		build(ls(u),l,mid);
		build(rs(u),mid + 1,r);
	}
	
	inline void modify(int u,int l,int r,int k){
		if (l <= tr[u].l && tr[u].r <= r){
			calc(u,k);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify(ls(u),l,r,k);
		if (r > mid) modify(rs(u),l,r,k);
		pushup(u);
	}
	
	#undef ls
	#undef rs
}tree;

int main(){
	q = read();
	for (re int i = 1;i <= q;i++){
		char s[10];
		scanf("%s",s);
		if (s[0] == '+') op[i] = true;
		l[i] = read();
		r[i] = read();
		p.push_back(l[i]);
		p.push_back(r[i]);
	}
	sort(p.begin(),p.end());
	unique(p.begin(),p.end());
	for (re int i = 1;i <= q;i++){
		l[i] = lower_bound(p.begin(),p.end(),l[i]) - p.begin() + 1;
		r[i] = lower_bound(p.begin(),p.end(),r[i]) - p.begin() + 1;
	}
	tree.build(1,1,2 * q);
	for (re int i = 1;i <= q;i++){
		if (op[i]){
			num++;
			tree.modify(1,l[i],r[i],1);
		}
		else{
			num--;
			tree.modify(1,l[i],r[i],-1);
		}
		if (tree.tr[1].Max != num && num > 1) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

如果每一次加或者删一个区间，再去暴力找有没有互不相交的区间的话，铁定 TLE。

那么，我们考虑维护有多少对互不相交的区间，那么每次加或者删一个区间，就去算这个区间对答案的贡献，然后再看答案是否为 $0$ 即可快速判断有没有互不相交的区间。

现在考虑如何计算一个新加入或者删去的区间能让互不相交的区间对数变化多少呢？

加入新加入或者删去的区间是 $[l,r]$，那么加入和删去带来的答案变化都应该相同，只是一个是加，一个是减，所以我们没必要分开讨论。

如果两个区间不相交，必须满足其中一个区间的左端点大于另一个区间的右端点，那么对于区间 $[l,r]$，要满足条件，就必须要左端点大于 $r$，右端点小于 $l$。

但是，如果还是全部扫一遍，挨个判断能否对答案造成贡献的话，复杂度高达 $O(q^2)$，依然会 TLE，所以考虑用个数据结构维护区间加，而每次加或者减一个区间就是单点修改，树状数组和线段树都可以完成，我选择了线段树。

无论是树状数组，还是线段树，就和值域有关系了，观察到值域达到了 $10^9$，直接做肯定不行，所以还需要离散化。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],num,ans;
struct opti{int l,r;char ch[2];}b[200005];
struct node{int l,r,s[2];}t[800005];
inline void pushup(int p){for(int i=0;i<2;++i) t[p].s[i]=t[p<<1].s[i]+t[p<<1|1].s[i];}
void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
void update(int p,int x,int op,int k)
{
	if(t[p].l==t[p].r){t[p].s[op]+=k;return;}
	int mid=t[p].l+t[p].r>>1;
	if(mid>=x) update(p<<1,x,op,k);
	else update(p<<1|1,x,op,k);
	pushup(p);
}
int ask(int p,int l,int r,int k)
{
	if(r<l) return 0;//因为出现了+1和-1，所以可能区间不存在，需要特判
	if(t[p].l>=l&&t[p].r<=r) return t[p].s[k];
	int mid=t[p].l+t[p].r>>1,ans=0;
	if(mid>=l) ans=ask(p<<1,l,r,k);
	if(mid<r) ans+=ask(p<<1|1,l,r,k);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%s%d%d",b[i].ch,&b[i].l,&b[i].r),a[i*2-1]=b[i].l,a[i*2]=b[i].r;
	sort(a+1,a+2*n+1),num=unique(a+1,a+2*n+1)-a-1;
	build(1,1,num);
	for(int i=1;i<=n;++i)
	{	
		b[i].l=lower_bound(a+1,a+num+1,b[i].l)-a,b[i].r=lower_bound(a+1,a+num+1,b[i].r)-a;
		if(b[i].ch[0]=='+')
		{
			ans+=ask(1,b[i].r+1,num,0)+ask(1,1,b[i].l-1,1),update(1,b[i].l,0,1),update(1,b[i].r,1,1);
			if(ans) printf("YES\n");
			else printf("NO\n");
		}
		else
		{
			ans-=ask(1,b[i].r+1,num,0)+ask(1,1,b[i].l-1,1),update(1,b[i].l,0,-1),update(1,b[i].r,1,-1);
			if(ans) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：_llch_ (赞：0)

题意描述：$q$ 次操作，每次插入一条线段或删除一条线段，每次操作后查询是否存在一对线段不相交。

有一个显然的结论是：如果有 $n$ 条线段任意两两相交，那么必然存在一点被 $n$ 条线段覆盖。

也就是说，题意可以转化为每次给定区间 $[l,r]$ 使这段区间内的值加 $1$ 或者减 $1$，然后查询当前最大值是否等于线段数量 $k$。

那么就很容易想到用线段树维护区间加和区间最大值，发现 $(1\leq l \leq r \leq 10^9)$，所以考虑离散化或者动态开点。

值得注意的是，线段数量小于等于 $1$ 的时候需要特判输出 `NO`。

赛场 AC 代码：
```cpp
#include<bits/stdc++.h>
#define ls (o<<1)
#define rs (o<<1|1)
#define mid (l+r)/2
using namespace std;
const int maxn=4e5+5;
int q,qu[maxn][5],a[maxn],cnt;
struct{
	int max,tag;
}tr[maxn*4];
void pushup(int o){
	tr[o].max=max(tr[ls].max,tr[rs].max);
}
void pushdown(int o){
	tr[ls].max+=tr[o].tag;
	tr[rs].max+=tr[o].tag;
	tr[ls].tag+=tr[o].tag;
	tr[rs].tag+=tr[o].tag;
	tr[o].tag=0;
}
void update(int o,int l,int r,int x,int y,int z){
	if(x<=l&&r<=y){
		tr[o].tag+=z;
		tr[o].max+=z;
		return;
	}
	if(tr[o].tag)pushdown(o);
	if(x<=mid)update(ls,l,mid,x,y,z);
	if(y>mid)update(rs,mid+1,r,x,y,z);
	pushup(o);
}
signed main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		char x;
		int s,t;
		cin>>x;
		cin>>s>>t;
		qu[i][0]=(x=='+')?1:-1;
		qu[i][1]=s;
		qu[i][2]=t;
		a[++cnt]=qu[i][1];
		a[++cnt]=qu[i][2];
	}
	sort(a+1,a+1+cnt);
	cnt=unique(a+1,a+1+cnt)-a-1;
	int ct=0;
	for(int i=1;i<=q;i++){
		qu[i][1]=lower_bound(a+1,a+1+cnt,qu[i][1])-a;
		qu[i][2]=lower_bound(a+1,a+1+cnt,qu[i][2])-a;
		ct+=qu[i][0];
		update(1,1,cnt,qu[i][1],qu[i][2],qu[i][0]);
		if(ct<=1)cout<<"NO"<<endl;
		else{
			if(tr[1].max==ct)cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Starrykiller (赞：0)



赛时译错题目（给同机房的大佬）了，当场谢罪。

## Statement

维护一个元素为线段的**多重集**，支持以下操作：

- 添加一条线段。
- 删去一条线段。

线段都在数轴上，端点都在整点上。每次操作后询问是否有两条线段无公共点。

## Solution

有两条线段不交 $\iff$ 所有线段不都交于一点。

于是我们可以维护每个点被覆盖的次数，于是 所有线段不都交于一点 $\iff$ 覆盖次数的最值小于当前线段数。

那么我们只需要维护一个支持区间加、区间最大值查询的线段树即可。注意特判当前线段树小于 $2$ 的情况。

注意到本题的端点范围很大，所以需要离散化或者使用动态开点线段树。sk 使用了离散化来实现。

完整代码见[此处](https://www.luogu.com.cn/paste/daxiq47v)。


---

