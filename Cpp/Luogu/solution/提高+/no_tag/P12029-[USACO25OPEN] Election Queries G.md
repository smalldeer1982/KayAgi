# [USACO25OPEN] Election Queries G

## 题目描述

**注意：本题时间限制为 3 秒，是默认时间的 1.5 倍。**

农夫约翰有 $N$ 头（$2 \leq N \leq 2 \cdot 10^5$）编号从 $1$ 到 $N$ 的奶牛。农场正在举行选举，将选出两头新的领头牛。初始时，已知第 $i$ 头奶牛会投票给第 $a_i$ 头奶牛（$1 \leq a_i \leq N$）。

选举过程如下：
1. 农夫约翰任意选择一个非空真子集 $S$（即至少包含一头牛但不包含所有牛）。
2. 在 $S$ 集合中，得票数最多的候选牛将被选为第一头领头牛 $x$。
3. 在剩余奶牛组成的集合中，得票数最多的候选牛将被选为第二头领头牛 $y$。
4. 定义两头领头牛的差异度为 $|x - y|$。若无法选出两头不同的领头牛，则差异度为 $0$。

由于奶牛们经常改变主意，农夫约翰需要进行 $Q$ 次（$1 \leq Q \leq 10^5$）查询。每次查询会修改一头奶牛的投票对象，你需要回答当前状态下可能获得的最大差异度。


## 说明/提示

样例一解释：

第一次查询后，$a = [1,2,4,4,5]$。选择 $S = \{1,3\}$ 时：

- $S$ 中：牛 $1$ 得 $1$ 票，牛 $4$ 得 $1$ 票 $\to$ 可选择牛 $1$ 或牛 $4$ 作为第一头领头牛。
- 剩余牛中：牛 $2,4,5$ 各得 $1$ 票 $\to$ 可选择牛 $2,4,5$ 作为第二头领头牛。

最大差异度为 $|1-5| = 4$。

第二次查询后，$a = [2,2,4,4,5]$。选择 $S = \{4,5\}$ 时：

- $S$ 中：牛 $4$ 得 $1$ 票，牛 $5$ 得 $1$ 票。
- 剩余牛中：牛 $2$ 得 $2$ 票。

最大差异度为 $|5-2| = 3$。

- 测试点 $3\sim4$：$N,Q \leq 100$。
- 测试点 $5\sim7$：$N,Q \leq 3000$。
- 测试点 $8\sim15$：无额外限制。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
3 4
1 2
5 2```

### 输出

```
4
3
2```

## 样例 #2

### 输入

```
8 5
8 1 4 2 5 4 2 3
7 4
8 4
4 1
5 8
8 4```

### 输出

```
4
4
4
7
7```

# 题解

## 作者：Twig_K (赞：5)

## 题意

[cnblogs](https://www.cnblogs.com/wanggk/p/-/P12029)

有 $n$ 个整数，值域 $[1,n]$。请你将这 $n$ 个数**划分**为两个**非空**集合 $S,T$，并选择 $x,y$。

要求 $x$ 为 $S$ 的众数之一，$y$ 为 $T$ 的众数之一。最大化 $\lvert x-y \rvert$ 的值。

$Q$ 组询问，每次询问前修改 $a_x \leftarrow y$。 $n \leq 2\times 10 ^5$。

## 题解

对于选出的 $x,y$，考虑如何贪心地划分集合：所有数 $x$ 放入 $S$，所有数 $y$ 放入 $T$，其他数摊到两个集合。

所以，$(x,y)$ 能被同时取出，当且仅当：

$$\forall i \in [1,n],cnt_i \leq cnt_x+cnt_y$$

即:

$$\max_{i=1}^n cnt_i \leq cnt_x+cnt_y$$

既然要最大化下标差，那么我们可以对每种不同的 $cnt$ 记录 $cnt_i=v$ 的最大、最小下标 $mxi_v,mni_v$。

双指针，枚举 $cnt_y$，找到最大的 $cnt_x$ 使 $cnt_x \geq mxcnt - cnt_y$，用 $mxi_{cnt},mni_{cnt}$ 之差更新答案。

双指针移动 $n$ 次，这样复杂度是 $O(n)$ 的，多组询问总复杂度 $O(nQ)$。

怎么优化呢？**因为始终有 $\sum cnt_i=n$，所以本质不同的 $cnt_i$ 最多有 $O(\sqrt n)$ 种**（考虑 $1+2+ \cdots + t \leq n$ 那么 $t$ 是 $O(\sqrt n)$ 的）。

所以只需要考虑那些不同的非零 $cnt_i$ 即可，用 `set` 维护存在的 $cnt$ 值，再对每种 $cnt$ 开一个 `set` 辅助求解最大、最小下标。

时间复杂度 $O(n \log n + n \sqrt n)$。

## 代码

[完整代码](https://www.cnblogs.com/wanggk/p/-/P12029)

```cpp
int n,Q;
set<int> st[maxn],S;
int a[maxn],c[maxn],mxi[maxn],mni[maxn];

void addc(int i,int cl){ //i 的得票变成 cl 了
	if(!cl) return; st[cl].insert(i);
	mxi[cl]=max(mxi[cl],i);
	mni[cl]=min(mni[cl],i);
	if(st[cl].size()==1) S.insert(cl);
}
void delc(int i,int cl){ //i 的得票不再是 cl 了
	if(!cl) return; st[cl].erase(i);
	if(st[cl].empty()) S.erase(cl),mxi[cl]=0,mni[cl]=n+1;
	else if(!st[cl].empty()) mxi[cl]=*--st[cl].end(),mni[cl]=*st[cl].begin();
}
signed main()
{
	rd(n),rd(Q);
	For(i,1,n) rd(a[i]),c[a[i]]++,mxi[i]=0,mni[i]=n+1;
	For(i,1,n) addc(i,c[i]);
	while(Q--)
	{
		int i,x;rd(i),rd(x);
		delc(a[i],c[a[i]]--),addc(a[i],c[a[i]]); a[i]=x;
		delc(a[i],c[a[i]]++),addc(a[i],c[a[i]]);
		
		int mx=*--S.end(),mxp=0,mnp=n+1,res=0;
		if(*S.begin()+*S.begin()>=mx) res=max(res,mxi[*S.begin()]-mni[*S.begin()]);
		for(auto itl=S.begin(),itr=--S.end();itl!=S.end();itl++){//双指针
			while(itr!=S.begin() && (*itr)+(*itl)>=mx)
				mxp=max(mxp,mxi[*itr]),mnp=min(mnp,mni[*itr]),itr--;
			res=max(res,max(mxp-mni[*itl],mxi[*itl]-mnp));
		}
		write(res),End;
	}
	return 0;
}
```

---

## 作者：HD0X (赞：5)

题意略。

令 $c_i$ 表示第 $i$ 头牛被投了多少票。首先，如果我们钦定 $x$，那么第一个集合中就可以有每头牛的不超过 $c_x$ 张票。此后如果要找一个最小的 $y$（令 $y \lt x$），只要它的票数非 $\text{0}$ 且大于等于整体减 $c_x$ 之后的 $\max_{i=1}^{n} c_i$ 就可以单开一组了，这个显然可以线段树二分，于是就有一个 $O(q n \log n)$ 的做法了。

发现 $c_x$ 的取值最多只有 $\sqrt n$ 种，所以可以用 set 处理出每个 $c_x$ 对应的最大的 $x$。但是动态维护这 $\sqrt n$ 个取值用 set 只能做到$O(q \sqrt n \log^2 n)$，无法通过，所以选择用 unordered_map $O(1)$ 存迭代器，再用 list $O(1)$ 删除插入，即可做到 $O(q \sqrt n \log n)$。卡常后可以通过，usaco 上也能过。


```cpp
#include <bits/stdc++.h>
#pragma optimize("Ofast") 
#pragma target("avx,avx2,fma")
char *p1,*p2,buf[1<<21];
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
const int MAXN=2e5+5;
int n,q,a[MAXN],c[MAXN];
int id,x,mx,ans,tot;
set<int>p[MAXN];
list<int>s;
unordered_map<int,list<int>::iterator> iot;
int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
int write(int x)
{
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
struct tree{
	int val,add;
}t[MAXN<<2];
void pushup(int rt)
{
	t[rt].val=max(t[rt<<1].val,t[rt<<1|1].val);
}
void build(int l,int r,int rt)
{
	t[rt].add=0;
	if(l==r)
	{
		t[rt].val=c[l];
		return;
	}
	int m=(l+r)>>1;
	build(l,m,rt<<1),build(m+1,r,rt<<1|1);
	pushup(rt);
}
void Pointupdate(int rt,int res)
{
	t[rt].add+=res,t[rt].val+=res;
}
void pushdown(int rt)
{
	if(t[rt].add)
	{
		Pointupdate(rt<<1,t[rt].add);
		Pointupdate(rt<<1|1,t[rt].add);
		t[rt].add=0;
	}
}
void update(int l,int r,int p,int res,int rt)
{
	if(l==r) return Pointupdate(rt,res);
	int m=(l+r)>>1;
	pushdown(rt);
	if(p<=m) update(l,m,p,res,rt<<1);
	else update(m+1,r,p,res,rt<<1|1);
	pushup(rt);
}
int query(int l,int r,int rt)
{
	while(1)
	{
		if(l==r) return l;
		int m=(l+r)>>1;
		pushdown(rt);
		if(t[rt<<1].val+tot>=mx) r=m,rt<<=1;
		else l=m+1,rt=rt<<1|1;
	}
}
signed main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(),++c[a[i]];
	for(int i=1;i<=n;i++)
	{
		if(c[i])
		{
			if(!p[c[i]].size()) s.push_back(c[i]),iot[c[i]]=--s.end();
			p[c[i]].insert(i);
		}
	}
	build(1,n,1);
	while(q--)
	{
		id=read(),x=read();
		p[c[a[id]]].erase(a[id]);
		if(!p[c[a[id]]].size()) s.erase(iot[c[a[id]]]);
		--c[a[id]];
		if(c[a[id]])
		{
			p[c[a[id]]].insert(a[id]);
			if(p[c[a[id]]].size()==1) s.push_back(c[a[id]]),iot[c[a[id]]]=--s.end();
		}
		if(c[x])
		{
			p[c[x]].erase(x);
			if(!p[c[x]].size()) s.erase(iot[c[x]]);
		}
		p[++c[x]].insert(x);
		if(p[c[x]].size()==1) s.push_back(c[x]),iot[c[x]]=--s.end();
		update(1,n,a[id],-1,1);
		update(1,n,x,1,1);
		a[id]=x;ans=0;
		for(int i:s)
		{
			if(i==0 || p[i].empty()) continue;
			tot=i;
			mx=t[1].val;
			if(mx==i) mx=i+1;
			ans=max(ans,abs(*p[i].rbegin()-query(1,n,1)));
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：FFTotoro (赞：4)

赛时不会某个结论，被 @[V 赖摇斑炸鱼佬](https://www.luogu.com.cn/user/565742) 嘲讽了。

下文认为 $n,q$ 同阶。

令奶牛 $x$ 的得票数为 $c_x$，记 $\mathrm{mx}=\max\limits_{i=1}^n c_i$。显然两头奶牛 $x,y$ 能当选的充要条件为 $c_x+c_y\ge\mathrm{mx}$。

考虑一种 $O(n^2)$ 做法：对于每种 $c$ 的值 $v$，找出最小和最大的 $i$ 满足 $c_i=v$，枚举其中一个出现次数 $c_x$，找出 $c_x$ 对应的最小的 $x_{\min}$，使用双指针找出 $c_y\ge\mathrm{mx}-c_x$ 中的 $y_{\max}$，将所有情况取最大值即为答案。需要用到的值都可以用 `set` 维护。

赛时卡在这一步了，但事实上上面的做法离正解就差一个十分关键的结论：若一个正整数序列 $a$ 满足 $\sum a_i\le S$，那么 $a$ 中元素的**种类数的量级是 $O(\sqrt{S})$ 的**。证明考虑如何卡满到这个上界，只需要构造 $1,2,3,\ldots$ 即可。由于 $\sum c_i=n$，所以 $c_i$ 的值只有本质不同的 $O(\sqrt{n})$ 种。

于是对于上面的暴力做法，如果只考虑至少对应着一个 $x$ 的 $c_x$，时间复杂度就是 $O(n\sqrt{n})$ 的。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,q; cin>>n>>q;
  vector<int> a(n),c(n);
  for(auto &i:a)cin>>i,c[--i]++;
  vector<set<int> > s(n+1); set<int> v;
  // s 是每个 c 对应着那些 x
  // v 是至少对应着一个 x 的 c 的集合
  for(int i:a)s[c[i]].emplace(i),v.emplace(c[i]);
  while(q--){
    int p,x,r=0; cin>>p>>x,p--,x--;
    s[c[a[p]]].erase(a[p]);
    s[c[x]].erase(x);
    if(s[c[a[p]]].empty())v.erase(c[a[p]]);
    if(s[c[x]].empty())v.erase(c[x]);
    s[--c[a[p]]].emplace(a[p]);
    s[++c[x]].emplace(x);
    v.emplace(c[a[p]]),v.emplace(c[x]),a[p]=x;
    vector<int> e(v.begin(),v.end());
    for(int i=0,p=e.size()-1,mx=0;i<e.size();i++)
      if(e[i]){
        while(p>=0&&e[p]&&e[p]+e[i]>=e.back())
          mx=max(mx,*prev(s[e[p]].end())),p--;
        r=max(r,mx-*s[e[i]].begin());
      } // 双指针求解过程
    cout<<r<<'\n';
  }
  return 0;
}
```

---

## 作者：WDY_Hodur (赞：3)

# Problem

## 题目描述

农夫约翰有 $N$ 头（$2 \leq N \leq 2 \cdot 10^5$）编号从 $1$ 到 $N$ 的奶牛。农场正在举行选举，将选出两头新的领头牛。初始时，已知第 $i$ 头奶牛会投票给第 $a_i$ 头奶牛（$1 \leq a_i \leq N$）。

选举过程如下：
1. 农夫约翰任意选择一个非空真子集 $S$（即至少包含一头牛但不包含所有牛）。
2. 在 $S$ 集合中，得票数最多的候选牛将被选为第一头领头牛 $x$。
3. 在剩余奶牛组成的集合中，得票数最多的候选牛将被选为第二头领头牛 $y$。
4. 定义两头领头牛的差异度为 $|x - y|$。若无法选出两头不同的领头牛，则差异度为 $0$。

由于奶牛们经常改变主意，农夫约翰需要进行 $Q$ 次（$1 \leq Q \leq 10^5$）查询。每次查询会修改一头奶牛的投票对象，你需要回答当前状态下可能获得的最大差异度。

## 输入格式

第一行包含 $N$ 和 $Q$。

第二行包含初始投票数组 $a_1, a_2, \ldots, a_N$。

接下来 $Q$ 行，每行两个整数 $i$ 和 $x$，表示将 $a_i$ 修改为 $x$。

## 输出格式

输出 $Q$ 行，第 $i$ 行表示前 $i$ 次查询后的最大可能差异度。

# Solution
用桶 $c$ 来记录每个奶牛被投了多少多少票，容易发现，如果 $x$ 和 $y$ 要当选，那么 $c_x+c_y$ 要大于每一个 $c_i$，即 $c_x+c_y\ge c_{max}$。

有了这个结论，对于单个询问，我们就可以先找出 $c_{max}$，然后用 $O(n^2)$ 的复杂度找出满足条件 $x$ 和 $y$，然后记录最大的 $\left|x-y \right|$ 即为答案。

考虑如何优化。对于值 $v$，我们可以通过集合记录每一个 $c_i=v$ 的 $i$，相当于得到了值 $v$ 最先出现的位置和最后出现的位置。然后枚举每一个 $v$，同时枚举所有满足 $v+w\ge c_{max}$ 的 $w$，即从 $c_{max}-v$ 枚举到 $c_{max}$，然后使用 $w$ 最后出现的位置减去 $v$ 最先出现的位置，统计最大值即为答案。同时我们发现，因为 $v$ 在从小到大遍历的同时，$w$ 的值域也在从后往前由小变大，那么我们就可以采用双指针，并记录 $w$ 的最后出现位置的最大值，用这个值减去 $v$ 的最先出现位置，更新答案即可。此时单次查询复杂度为 $O(n)$，总体复杂度为 $O(qn)$。

考虑进一步优化。我们发现，$c$ 中完全不同的值只有 $\sqrt n$ 个，即 $v$ 和 $w$ 真正有意义的值只有 $\sqrt n$ 种。那么我们可以把这些值记录下来，在遍历 $v$ 和 $w$ 时只考虑记录下来的这些值。此时单次查询复杂度降为 $O(\sqrt n)$，总体复杂度为 $O(q\sqrt n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int n,m,a[N],c[N],ans;
int mx,mxid,smx,smxid;
set<int>s[N],sv;
vector<int>v;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)++c[a[i]];
	for(int i=1;i<=n;i++)s[c[i]].insert(i);
	for(int i=1;i<=n;i++)if(s[i].size())sv.insert(i);
	while(m--){
		int id,x,nmx=0;
		cin>>id>>x;
		s[c[a[id]]].erase(a[id]);
		s[c[x]].erase(x);
		if(!s[c[a[id]]].size())sv.erase(c[a[id]]);
		if(!s[c[x]].size())sv.erase(c[x]);
		
		c[a[id]]--,c[x]++;
		s[c[a[id]]].insert(a[id]);
		s[c[x]].insert(x);
		if(s[c[a[id]]].size()==1)sv.insert(c[a[id]]);
		if(s[c[x]].size()==1)sv.insert(c[x]);
		for(int j:sv)v.push_back(j);
		
		a[id]=x,mx=v.back();
		
		ans=-LONG_LONG_MAX;
		nmx=*s[mx].rbegin(); 
		for(int l=0,r=(int)v.size()-1;l<(int)v.size()&&r>=0;l++){
			while(r>0&&v[l]+v[r-1]>=mx&&v[r-1]!=0){
				--r;
				nmx=max(nmx,*s[v[r]].rbegin());
			}
			ans=max(ans,nmx-*s[v[l]].begin());
		}
		cout<<ans<<"\n";
		v.clear();
		v.shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：cyq32ent (赞：3)

观察可知，设 $m_i$ 为选 $i$ 的票数，那么 $x$ 和 $y$ 能当选，等价于 $m_x+m_y\geq \max m_i$。因此，我们对于每次询问，只需要枚举得票数 $d$，那么答案就是 $\max_{d\in[1,N]}\{\max_{m_i\geq d}i-\min_{m_i\geq \max m_i-d}\}$。时间复杂度 $\mathcal O(NQ)$。

考虑优化。我们注意到 $m_i$ 最多有 $\mathcal O(\sqrt N)$ 种取值，因为最坏情况为 $m=[1,2,3,4,\cdots,x,0,0,\cdots,0]$。所以我们只需在这 $\mathcal O(\sqrt N)$ 种取值中枚举即可。时间复杂度 $\mathcal O(N \log N+Q\sqrt N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[202504],N,Q,m[202504];
map<int,int>m_;set<int>f_[202504];
int d[2025],cnt,mi[2025],mx[2025];
void add(int x,int n){
	m_[m[x]]--;if(!m_[m[x]])m_.erase(m[x]);
	f_[m[x]].erase(x),m[x]+=n,m_[m[x]]++,f_[m[x]].insert(x);
}
int main(){
	cin>>N>>Q;
	for(int i=1;i<=N;i++)cin>>a[i],m[a[i]]++;
	for(int i=1;i<=N;i++)m_[m[i]]++,f_[m[i]].insert(i);
	for(int i,x,k,ans;Q--;){
		cin>>i>>x;
		add(a[i],-1);a[i]=x;add(a[i],1);
		memset(d,0,sizeof d);
		memset(mi,0,sizeof mi);
		memset(mx,0,sizeof mx);
		cnt=ans=0;
		for(auto u:m_)if(u.first)d[++cnt]=u.first;
		k=d[cnt];
		for(int i=1;i<=cnt;i++)
			mi[i]=*f_[d[i]].begin(),mx[i]=*f_[d[i]].rbegin();
		for(int i=cnt-1;i;i--)mx[i]=max(mx[i],mx[i+1]);
		for(int l=1,r=cnt;l<=cnt;l++){
			while(r-2>=0&&d[r-1]+d[l]>=k)r--;
			ans=max(ans,mx[r]-mi[l]);
		}cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：dpfs (赞：1)

## Solution

赛时写出来的。

我们先设 $V _ {i}$ 为第 $i$ 头牛的得票数，两只领头牛分别为 $x$ 和 $y$，当前得票最多的牛的得票数为 $V _ {max}$。

先假设我们知道 $V _ {x}$，则 $V _ {y}$ 应该满足 $ V _ {max}-V _ {x} \le V _ {y}$。

这个式子理解起来应该相对容易。

那么我们可以想到开 $n$ 颗权值线段树，去存得票数相同的牛的编号。在第 $i$ 棵权值线段树上把所有 $V _ {j} = i$ 的 $j$ 赋为1，这样就可以支持单点修改投票，查询最大值和最小值了。由于是全局查询，所以可以不用写查询函数。

但是我们不知道 $V _ {x}$。

没关系，其实仔细观察一下我们可以发现：所有牛的总票数加起来一定是 $n$，那么不一样的 $V _ {i}$ 最多只有 $\sqrt{n}$ 个。

那么每次我们处理出所有的出现不同投票数，排好序以后处理一个后缀编号最大值与最小值，然后枚举 $V _ {x}$，容易发现 $V _ {max}-V _ {x}$ 单调递减，所以可以用双指针替代二分。

整体时间复杂度可以做到 $O(n\sqrt{n})$。

### 注意

1. 每次修改完使用插入排序，不要重新排一遍序，否则复杂度会变成 $O(n\sqrt{n}\log n)$。

2. 对每一个数打一个标记，不要重复插入，否则复杂度会假。

3. 权值线段树动态开点。

4. 修改投票的部分比较繁琐，注意一下处理好细节。


## Code


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=2e5+10,inf=1e9,mod=1e9+7;
int read()
{
	int k=0,f=1;char c=getchar();
	while(c<'0' or c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' and c<='9') k=k*10+c-'0',c=getchar();
	return k*f;
}
int n,q,a[maxn],rk[maxn],vis[maxn],suf[maxn][2];
struct sgt{
	int idx=0,root[maxn];
	struct node{
		int mx,mn,lson,rson;
	} t[maxn*50];
	void init()
	{
		t[0].mn=inf,t[0].mx=0;
	}
	void pushup(int rt)
	{
		t[rt].mn=min(t[t[rt].lson].mn,t[t[rt].rson].mn);
		t[rt].mx=max(t[t[rt].lson].mx,t[t[rt].rson].mx);
	}
	int update(int L,int R,int pos,int ret,int rt)
	{
		if(!rt) rt=++idx,t[rt].mx=0,t[rt].mn=inf;
		if(L==R)
		{
			if(ret==-1) t[rt].mx=0,t[rt].mn=inf;
			else t[rt].mx=t[rt].mn=pos;
			return rt;
		}
		int mid=(L+R)>>1;
		if(pos<=mid) t[rt].lson=update(L,mid,pos,ret,t[rt].lson);
		else t[rt].rson=update(mid+1,R,pos,ret,t[rt].rson);
		pushup(rt);
		return rt;
	}
} tr;
vector<int> vec; 
signed main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(),rk[a[i]]++;
	tr.init();
	for(int i=1;i<=n;i++)
	{
		if(!rk[i]) continue;
		tr.root[rk[i]]=tr.update(1,n,i,1,tr.root[rk[i]]);
		if(!vis[rk[i]]) vec.push_back(rk[i]);
		vis[rk[i]]++;
	}
	sort(vec.begin(),vec.end());
	while(q--)
	{
		int x=read(),y=read(),mxrk=0,ans=0,j=0;
		vis[rk[a[x]]]--;
		if(rk[y]) vis[rk[y]]--;
		rk[a[x]]--,rk[y]++;
		if(rk[a[x]]) vis[rk[a[x]]]++;
		vis[rk[y]]++;
		tr.root[rk[a[x]]+1]=tr.update(1,n,a[x],-1,tr.root[rk[a[x]]+1]);
		if(rk[a[x]]) tr.root[rk[a[x]]]=tr.update(1,n,a[x],1,tr.root[rk[a[x]]]);
		if(rk[y]>1) tr.root[rk[y]-1]=tr.update(1,n,y,-1,tr.root[rk[y]-1]);
		tr.root[rk[y]]=tr.update(1,n,y,1,tr.root[rk[y]]);
		vector<int> v,v2;
		if(vis[rk[a[x]]]==1 and rk[a[x]]) v2.push_back(rk[a[x]]);
		if(vis[rk[y]]==1) v2.push_back(rk[y]);
		if(v2.size()==2 and v2[0]>v2[1]) swap(v2[0],v2[1]);
		for(int i=0;i<vec.size();i++)
		{
			while(j<v2.size() and v2[j]<vec[i]) v.push_back(v2[j]),j++;
			if(vis[vec[i]]) v.push_back(vec[i]);
		}
		if(j!=v2.size())
		{
			for(int i=j;i<=v2.size()-1;i++) v.push_back(v2[i]);
		}
		vec=v;
		a[x]=y;
		suf[vec.size()][0]=inf,suf[vec.size()][1]=0;
		for(int i=vec.size()-1;i>=0;i--)
		{
			mxrk=vec[vec.size()-1];
			suf[i][0]=min(suf[i+1][0],tr.t[tr.root[vec[i]]].mn);
			suf[i][1]=max(suf[i+1][1],tr.t[tr.root[vec[i]]].mx);
		}
		int pos=vec.size()-1;
	//	cout<<"! ";
		for(int i=0;i<=vec.size()-1;i++)
		{
	//		cout<<vec[i]<<" ";
			int tmp=mxrk-vec[i],mx,mn;
			while(pos>=0 and vec[pos]>=tmp) pos--;
			mx=suf[pos+1][1],mn=suf[pos+1][0];
			if(tr.t[tr.root[vec[i]]].mx!=0 and mn!=inf) ans=max(ans,tr.t[tr.root[vec[i]]].mx-mn);
			if(tr.t[tr.root[vec[i]]].mn!=inf and mx!=0) ans=max(ans,mx-tr.t[tr.root[vec[i]]].mn);
		}
	//	cout<<'\n';
		if(ans==0) cout<<-1<<'\n';
		else cout<<ans<<'\n';
	}
	return 0;
}   

```

---

## 作者：_JoeyJ_ (赞：1)

[博客园食用更佳](https://www.cnblogs.com/JoeyJ/articles/-/USACO-2025-OPEN-G)。

比较唐的根号做法。

记 $tot_x$ 为 $A$ 中 $x$ 的出现次数，不难发现题目中的限制等价于选取 $i,j$ 使得 $\displaystyle tot_i+tot_j\geq \max_k tot_k$。

考虑对 $lim=\displaystyle \max_k tot_k$ 阈值分治：

- 对于 $lim\leq B$ 的情况：

    记 $\displaystyle mx_i=\max_{tot_j\geq i} j$，$\displaystyle mn_i=\min_{tot_j\geq i} j$。考虑枚举最后可能的 $tot_i$，则答案为 $\displaystyle \max_{i\geq 1} mx_i-mn_{lim-i}$。

- 对于 $lim \gt B$ 的情况：

    称 $tot_x \geq \lceil \frac B2 \rceil$ 的 $x$ 为大数，则由 $\displaystyle \sum_i tot_i =n$ 可知大数的个数不会超过 $\lfloor\frac{2n}B\rfloor$ 个，同时一组合法的 $(i,j)$ 中至少有一个大数。考虑枚举大数，则答案为：$\displaystyle \max_{tot_i \geq \lceil \frac B2 \rceil} \max\{i-mn_{lim-tot_i},mx_{lim-tot_i}-i\}$。

现在的问题是如何 $O(1)$ 查 $mn_i$ 和 $mx_i$。

使用 set 做到 $O(\log n)$ 查询是简单的。发现每次修改 $\Delta tot_i \in \{-1,0,1\}$，所以实际上受到影响的只有 $O(1)$ 个位置，丢到数组上先修改后查询即可。

时间复杂度 $O(n\log n+q(\log n+\sqrt n))$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int B=4e2;

int a[N],cnt[N],mx[N],mn[N],n,q;
set<int> s[N],all,big;
inline void Update(int x){
    mx[x]=mx[x+1],mn[x]=mn[x+1];
    if(s[x].size()){
        mx[x]=max(mx[x],*s[x].rbegin());
        mn[x]=min(mn[x],*s[x].begin());
    }
}
inline void Veto(int x){
    all.erase(cnt[x]);
    s[cnt[x]].erase(x);
    Update(cnt[x]);
    if(cnt[x]>=(B>>1)) big.erase(x);
    cnt[x]--;
    if(cnt[x]>=(B>>1)) big.insert(x);
    all.insert(cnt[x]);
    s[cnt[x]].insert(x);
}
inline void Vote(int x){
    all.erase(cnt[x]);
    s[cnt[x]].erase(x);
    if(cnt[x]>=(B>>1)) big.erase(x);
    cnt[x]++;
    if(cnt[x]>=(B>>1)) big.insert(x);
    all.insert(cnt[x]);
    s[cnt[x]].insert(x);
    Update(cnt[x]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];

    mx[n+1]=0,mn[n+1]=n+1;
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    for(int i=1;i<=n;i++) s[cnt[i]].insert(i);
    for(int i=n;i>=0;i--) Update(i);
    for(int i=1;i<=n;i++) all.insert(cnt[i]);
    for(int i=1;i<=n;i++) if(cnt[i]>=(B>>1)) big.insert(i);

    while(q--){
        int i,x;
        cin>>i>>x;

        Veto(a[i]);
        a[i]=x;
        Vote(a[i]);

        int lim=*all.rbegin();
        if(lim<=B){
            int ans=0;
            for(int i=1;i<=lim;i++){
                ans=max(ans,mx[max(lim-i,1)]-mn[i]);
                ans=max(ans,mx[i]-mn[max(lim-i,1)]);
            }
            cout<<ans<<endl;
        }else{
            int ans=0;
            for(int i:big){
                ans=max(ans,mx[max(lim-cnt[i],1)]-i);
                ans=max(ans,i-mn[max(lim-cnt[i],1)]);
            }
            cout<<ans<<endl;
        }
    }

    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

upd on 25.04.10 修正笔误。

记 $c_i$ 为第 $i$ 头牛的得票数。

此时，若 $x,y$ 可以被选为领头牛，可以推出一个充要条件 $c_x+c_y\ge \max\limits_{i=1}^n c_i$。

这样，对单组询问而言，我们就可以得出一个 $O(n\log n)$ 做法。

先把 $a$ 序列按 $c$ 的值排序，记 $pos_i$ 为排完序后位置 $i$ 的值。

扫一遍序列，双指针维护最小的满足条件的位置，设当前位置为 $i$，使用 $pos$ 的后缀 $\min,\max$ 与 $pos_i$ 的差更新答案即可做到 $O(n\log n)$，瓶颈在排序。

注意到一个关键结论，对于 $c$ 值相同的牛，只需取编号最小的和编号最大的即可。

由于 $\sum c_i=n$，$c_i$ 最多只有 $O(\sqrt{n})$ 种取值。可以使用 map 维护 $c_i$ 的取值以及 min/max（具体细节见代码），这样就可以省掉排序，做到 $O(n\log n+n\sqrt{n})$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ldb long double 
#define bi __int128_t
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
int n,q;
int a[N],ac[N];
set<int> ap[N];
map<int,int> wp;
int mn[N],mx[N];
int smx[N],smn[N];
pii s[N];
int calc(int p){
    int res=0,mx=0;
    smx[p+1]=0;smn[p+1]=n+1;
    for(int i=p;i>=1;i--){
        smx[i]=max(smx[i+1],s[i].fi);
        smn[i]=min(smn[i+1],s[i].fi);
        mx=max(mx,s[i].se);
    }
    int it=p;
    for(int i=1;i<=p;i++){
        //cout<<s[i].fi<<' '<<s[i].se<<endl;
        while(it>1&&s[it-1].se+s[i].se>=mx) it--;
        res=max(res,max(smx[it]-s[i].fi,s[i].fi-smn[it]));
    }
    return res;
}
void upd(int id){
    if(ap[id].empty()) return ;
    mn[id]=*ap[id].begin();
    mx[id]=*(--ap[id].end());
}
void mdf(int x,int v){
    wp[ac[x]]--;if(wp[ac[x]]==0) wp.erase(ac[x]);
    ap[ac[x]].erase(x);upd(ac[x]);
    ac[x]+=v;
    wp[ac[x]]++;
    ap[ac[x]].insert(x);upd(ac[x]);
}
int main(){
    //freopen("3.in","r",stdin);
    //freopen("3.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) ac[a[i]]++;
    for(int i=1;i<=n;i++) ap[ac[a[i]]].insert(a[i]);
    for(int i=1;i<=n;i++){
        wp[ac[i]]++;upd(i);
    }
    while(q--){
        int x,v;cin>>x>>v;
        mdf(a[x],-1);
        a[x]=v;
        mdf(a[x],1);
        int p=0;
        for(auto ed:wp){
            if(ed.fi==0) continue;
            s[++p]=mk(mx[ed.fi],ed.fi);
            if(mn[ed.fi]!=mx[ed.fi]) s[++p]=mk(mn[ed.fi],ed.fi);
        }cout<<calc(p)<<endl;
    }
	return 0;
}
```

---

## 作者：Yao_yx (赞：0)

若其中一头领头牛 $x$ 票数为所有牛中最多的，则可直接枚举第二头领头牛 $y$（将其余牛放到 $x$ 所在集合里即可）。否则，$x$ 的票数加 $y$ 的票数需大于票数最多的牛的票数。

注意到票数相同的牛是否合法是等价的，而总票数为 $n$，所以最多只有 $O(\sqrt n)$ 中票数，记录每种票数牛的最大与最小编号，双指针移动判断即可。时间复杂的 $O(n\sqrt n)$。

注意实现细节。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5 + 10;

int n, q, a[MAXN];
int cnt[MAXN];
set<int> st[MAXN], vis;
int mn[MAXN], mx[MAXN];
int b[MAXN], tot;

void get(int i){ if(st[i].size()) mn[i] = *st[i].begin(), mx[i] = *prev(st[i].end()); else mn[i] = n + 1, mx[i] = 0; }

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> q; vis.insert(0);
	for(int i = 1; i <= n; ++i){
		cin >> a[i]; cnt[a[i]]++;
	}
	for(int i = 1; i <= n; ++i) vis.insert(cnt[a[i]]), st[cnt[a[i]]].insert(a[i]);
	for(int i = 1; i <= n; ++i) get(i);
	for(int i, x; q; --q){
		cin >> i >> x; if((st[cnt[a[i]]].size()) == 1) vis.erase(cnt[a[i]]); st[cnt[a[i]]].erase(a[i]), get(cnt[a[i]]);
		cnt[a[i]]--; vis.insert(cnt[a[i]]), st[cnt[a[i]]].insert(a[i]); get(cnt[a[i]]);
		a[i] = x; if((st[cnt[a[i]]].size()) == 1) vis.erase(cnt[a[i]]); st[cnt[a[i]]].erase(a[i]), get(cnt[a[i]]);
		cnt[a[i]]++; vis.insert(cnt[a[i]]), st[cnt[a[i]]].insert(a[i]); get(cnt[a[i]]);
		tot = 0; for(auto it = vis.begin(); it != vis.end(); ++it) if(*it) b[++tot] = *it;
		if(tot == 1 && b[1] == n){ cout << "0\n"; continue; }
		int mxn = b[tot], res = n + 1, res1 = 0, num = *st[b[tot]].begin(); st[b[tot]].erase(num);
		get(b[tot]); if(!st[b[tot]].size()) tot--;
		for(int i = 1; i <= tot; ++i) res = min(res, mn[b[i]]), res1 = max(res1, mx[b[i]]);
		int ans = max(num - res, res1 - num);
		for(int j = 1, k = tot + 1, gmn = n + 1, gmx = 0; j <= tot; ++j){
			while(k > 1 && b[k - 1] + b[j] >= mxn) k--, gmn = min(gmn, mn[b[k]]), gmx = max(gmx, mx[b[k]]);
			if(k <= tot && b[k] + b[j] >= mxn) ans = max({ans, abs(gmx - mn[b[j]]), abs(gmx - mx[b[j]]), abs(gmn - mn[b[j]]), abs(gmn - mx[b[j]])});
		}
		cout << ans << '\n';
		st[cnt[num]].insert(num), get(cnt[num]);
	}

	return 0;
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
普通题。
### Solution
设 $tim_i$ 为数字 $i$ 在序列 $a$ 出现的次数，我们要想选两个编号不同的 $i,j$ 分别作为两头不同的领头牛的编号，当且仅当：$tim_i+tim_j\ge \max_{k=1}^n tim_k$ 且 $tim_i,tim_j>0$，证明显然。

然后对于每个 $tim_i$ 维护出现次数等于其的编号，记录其最大值和最小值。显然对于每个 $tim_i$ 查询一段后缀的最值即可。

根据数据范围，我们不难想到用根号分治来优化上面的算法。设阈值为 $B=\sqrt n$，当一个编号的出现次数 $\le B$ 时，我们用 $B$ 个 set 维护编号集合；否则，我们直接用一个大的 set 维护。

可以发现，当一个编号的出现次数 $>B$ 时，不同编号个数最多只有 $\frac{n}{B}$ 个，于是就可以直接做了。

时间复杂度是 $O(q\sqrt n)$ 的，用大常数 set 维护也能过。

代码太丑了建议别看。
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 200010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int >
#define fi first
#define se second

using namespace std;
const int B=400;
int tim[N],a[N];
int n,q,mx;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
multiset<pii >S;
multiset<int >s[N],s2;
int L[N],R[N],prel[N],prer[N];

int main()
{
	n=read(),q=read();
	For(i,1,n) a[i]=read(),tim[a[i]]++;
	For(i,1,n){
		if(tim[i]<=B) s[tim[i]].insert(i);
		else S.insert(mk(tim[i],i));
		s2.insert(tim[i]);
	}
	For(i,0,B){
		if(!s[i].size()) L[i]=n+1,R[i]=-1;
		else L[i]=*s[i].begin(),R[i]=*prev(s[i].end());
	}
	while(q--){
		int x=read(),y=read();
		if(tim[a[x]]<=B) s[tim[a[x]]].erase(s[tim[a[x]]].lower_bound(a[x]));
		else{
			auto it=S.lower_bound(mk(tim[a[x]],a[x]));
			S.erase(it);
		}
		s2.erase(s2.lower_bound(tim[a[x]]));
		tim[a[x]]--;
		if(tim[a[x]]<=B) s[tim[a[x]]].insert(a[x]);
		else S.insert(mk(tim[a[x]],a[x]));
		s2.insert(tim[a[x]]);
		a[x]=y;
		if(tim[a[x]]<=B) s[tim[a[x]]].erase(s[tim[a[x]]].lower_bound(a[x]));
		else{
			auto it=S.lower_bound(mk(tim[a[x]],a[x]));
			S.erase(it);
		}
		s2.erase(s2.lower_bound(tim[a[x]]));
		tim[a[x]]++;
		if(tim[a[x]]<=B) s[tim[a[x]]].insert(a[x]);
		else S.insert(mk(tim[a[x]],a[x]));
		s2.insert(tim[a[x]]);
		mx=*prev(s2.end());
		For(i,0,B){
			if(!s[i].size()) L[i]=n+1,R[i]=-1;
			else L[i]=*s[i].begin(),R[i]=*prev(s[i].end());
		}
		prel[B]=L[B],prer[B]=R[B];
		Rof(i,B-1,1) prel[i]=min(prel[i+1],L[i]),prer[i]=max(prer[i+1],R[i]);
		int ans=0;
		if(S.size()){
			auto itr=S.end();
			int nowl=n+1,nowr=-1;
			for(auto itl=S.begin();itl!=S.end();itl=next(itl)){
				while(itr!=S.begin() && (*prev(itr)).fi+(*itl).fi>=mx){
					itr--;
					nowl=min(nowl,(*itr).se);
					nowr=max(nowr,(*itr).se);
				}
				ans=max(ans,max(nowr-(*itl).se,(*itl).se-nowl));
			}
			for(auto it=S.begin();it!=S.end();it=next(it)){
				int p=mx-(*it).fi;
				if(p<1) p=1;
				if(p<=B) ans=max(ans,max((*it).se-prel[p],prer[p]-(*it).se));
			}
		}
		Rof(i,B,1){
			int p=mx-i;
			if(p>B) break;
			if(p<1) p=1;
			ans=max(ans,max(R[i]-prel[p],prer[p]-L[i]));
		}
		cout<<ans<<endl;
	}
	return 0; 
}
/*

*/
```

---

