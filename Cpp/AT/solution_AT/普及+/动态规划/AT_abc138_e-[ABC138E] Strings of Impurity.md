# [ABC138E] Strings of Impurity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc138/tasks/abc138_e

英小文字からなる二つの文字列 $ s,\ t $ が与えられます。次の条件を満たす整数 $ i $ $ (1\ \leq\ i\ \leq\ 10^{100}\ \times\ |s|) $ が存在するか判定し、存在する場合はそのような $ i $ の最小値を求めてください。

- $ s $ を $ 10^{100} $ 個連結して得られる文字列を $ s' $ とする。$ t $ は、文字列 $ {s'}_1{s'}_2\ldots{s'}_i $ ($ s' $ の先頭 $ i $ 文字) の部分列である。

## 说明/提示

### 注記

- 文字列 $ a $ の部分列とは、$ a $ から $ 0 $ 文字以上を削除して残った文字を相対的な順序を保ったまま連結して得られる文字列です。例えば、`contest` の部分列には `net`, `c`, `contest` などがあります。

### 制約

- $ 1\ \leq\ |s|\ \leq\ 10^5 $
- $ 1\ \leq\ |t|\ \leq\ 10^5 $
- $ s,\ t $ は英小文字からなる。

### Sample Explanation 1

$ t\ = $ `son` は文字列 `contestcon` ($ s'\ = $ `contestcontestcontest...` の先頭 $ 10 $ 文字) の部分列であるため、$ i\ =\ 10 $ は条件を満たします。 一方で、$ t $ は文字列 `contestco` ($ s' $ の先頭 $ 9 $ 文字) の部分列ではないため、$ i\ =\ 9 $ は条件を満たしません。 同様に、$ 8 $ 以下の任意の整数も条件を満たしません。よって、条件を満たす整数 $ i $ の最小値は $ 10 $ です。

### Sample Explanation 2

$ t\ = $ `programming` は $ s'\ = $ `contestcontestcontest...` の部分列ではありません。よって、条件を満たす整数 $ i $ は存在しません。

### Sample Explanation 3

ここにそのようなケースを置くことはできませんが、答えは $ 32 $ bit 整数に収まらない可能性があるのでご注意ください。

## 样例 #1

### 输入

```
contest
son```

### 输出

```
10```

## 样例 #2

### 输入

```
contest
programming```

### 输出

```
-1```

## 样例 #3

### 输入

```
contest
sentence```

### 输出

```
33```

# 题解

## 作者：STARSczy (赞：4)

# 思路：
暴力地开二十六个平衡树维护，保留加入操作与查询后继操作，分别对应二十六个小写字母。使用 $cnt$ 计数，表示有多少次重复循环的 $s$。使用 $now$ 表示上一次的位置。最后输出。时间复杂度 $\Theta(\Sigma n\log n)$，$\Sigma=26$。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10,mod=1e9+7;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}
class fhq{
	private: 
		struct node{
			int size,data,vis,sum;
			node *l,*r;
		}*root=0,zero;
	public:
		node *newnode(int x){
			node *ip=new node;
			ip->data=x,ip->vis=rand(),ip->size=1,ip->sum=x,ip->l=ip->r=NULL;
			return ip;
		}
		void pushup(node *ip){
			if(ip==NULL) return;
			ip->size=1,ip->sum=ip->data;
			if(ip->l) ip->size+=ip->l->size,ip->sum+=ip->l->sum;
			if(ip->r) ip->size+=ip->r->size,ip->sum+=ip->r->sum;
		}
		void split(node *ip,int val,node *&l,node *&r){
			if(ip==NULL) l=r=NULL;
			else{
				if(ip->data<=val){
					l=ip;
					split(ip->r,val,ip->r,r);
				}
				else{
					r=ip;
					split(ip->l,val,l,ip->l);
				}
				pushup(ip);
			}
		}
		node* merge(node *&l,node *&r){
			if(l==NULL) return r;
			if(r==NULL) return l;
			if(l->vis<=r->vis){
				l->r=merge(l->r,r);
				pushup(l);
				return l;
			}
			r->l=merge(l,r->l);
			pushup(r);
			return r;
		}
		void add(int x){
			node *a=NULL,*b=NULL;
			split(root,x,a,b);
			node *tmp1=newnode(x),*tmp2=merge(a,tmp1);
			root=merge(tmp2,b);
		}
		int nxt(int x){
			node *a=NULL,*b=NULL,*ans=NULL;
			split(root,x,a,b);
			for(ans=b;ans&&ans->l;ans=ans->l);
			root=merge(a,b);
			return ans?ans->data:0;
		}
		int empty(){return !root;}
}p[26];
int cnt;
char a[maxn],b[maxn];

signed main(){
	cin>>(a+1)>>(b+1);
	for(int i=1;a[i];++i) p[a[i]-'a'].add(i);
	for(int i=1,now=0;b[i];++i){
		if(p[b[i]-'a'].empty()) puts("-1"),exit(0);
		now=p[b[i]-'a'].nxt(now);
		if(!now) now=p[b[i]-'a'].nxt(0),++cnt;
	}
	write(cnt*strlen(a+1)+now);
	return 0;
}

---

## 作者：wuwendongxi (赞：4)

### 思路
- 首先，如果 $T$ 中有 $S$ 没有的字母，那么一定不合法输出 $-1$。
- 因为最多跳 $lent$ 次 $S$ 串，所以把 $T$ 的字母挨个匹配
- $p[i][j]$ 表示：匹配到 $S$ 的第 $i$ 个字母，$i$ 后第一个字母 $j$的出现位置，若没有则为 $-1$；$ANS$ 表示周期数。

------------------
### 代码
```
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=100003;
char a[maxn],b[maxn];
int p[maxn][27],ans,lst;
int main()
{
	scanf("%s%s",&a,&b);
	int lena=strlen(a),lenb=strlen(b);
	for(int i=0;i<26;++i) p[lena-1][i]=-1; p[lena-1][a[lena-1]-'a']=lena-1;
	for(int i=lena-2;i>=0;--i){
		for(int j=0;j<26;++j) p[i][j]=p[i+1][j];
		p[i][a[i]-'a']=i;
	}
	for(int i=0;i<lenb;++i) if(p[0][b[i]-'a']==-1) return puts("-1"),0;
	for(int i=0;i<lenb;++i)
	{
		if(p[lst][b[i]-'a']==-1) ++ans,lst=0;
		lst=p[lst][b[i]-'a']; ++lst;
		if(lst==lena) ++ans,lst=0;
	}
	cout<<1ll*ans*lena+lst<<'\n';
	return 0;
}
```

---

## 作者：small_john (赞：3)

## 思路

挺简单的贪心题。

首先，对于每个 $t_i$，我们就可以找到第一个在 $s$ 出现的位置。所以开个二维 `vector` 来存储字符 $c$ 在 $s$ 出现的各个位置（命名为 $v$）。

每次记录上一个选的数的位置为 $pre$，另外记复制的 $s$ 的长度为 $ans$，再在 $v_{t_{i}}$ 里找第一个大于 $pre$ 的数（二分即可）。

- 如果 $s$ 里没有 $t_i$，输出 `-1`，退出；
- 如果找不到就说明该新复制一个，把 $ans$ 加 $|s|$，$pre$ 赋值为 $v_{t_i,0}$；
- 找到了就把 $pre$ 赋值为找到的数。

值得注意的是，`lower_bound` 函数会找到与 $pre$ 相等的数，所以要判断一下。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,t;
int ans,pre = 0;
vector<int> v[128];
signed main()
{
	cin>>s>>t;
	int n = s.size(),m = t.size();
	s = ' '+s,t = ' '+t;
	for(int i = 1;i<=n;i++)
		v[s[i]].push_back(i);
	for(int i = 'a';i<='z';i++)
		v[i].push_back(n+1);//防止RE
	for(int i = 1;i<=m;i++)
	{
		if(v[t[i]].size()==1) return cout<<-1,0;//没有t[i]
		auto now = lower_bound(v[t[i]].begin(),v[t[i]].end(),pre);
		if(*now==pre) now++;//特判
		int n1 = *now;//把值取出来
		if(n1==n+1) ans+=n,pre = v[t[i]][0];
		else pre = n1;
	}
	cout<<ans+pre;
	return 0;
}
```

## 后记

其实本题数据很水，完全可以不用二分，直接暴力也能过。

---

## 作者：Svemit (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/17802579.html)

[link](https://atcoder.jp/contests/abc138/tasks/abc138_e)

不懂为什么都写平衡树，明明 set 就好了啊，思路跟平衡树差不多，实现起来较为简单。

讲细一点。

一个显然的贪心策略是不断的选当前第一个能选的，不能选了就重置。

用一个 set 记录每个字母出现的位置就好。

```cpp
int n, m, k;
int s[N];
string s1, s2;
int cnt[N];
vector<int> t;
set<int> p[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin >> s1 >> s2;
	n = s1.size(), m = s2.size();
	s1 = " " + s1, s2 = " " + s2;
	for(int i = 1; i <= n; i ++) {
		s[i] = s1[i] - 'a';
		cnt[s[i]] ++;
		p[s[i]].insert(i);
	}
	for(int i = 1; i <= m; i ++) {
		int x = s2[i] - 'a';
		if(cnt[x]) t.push_back(x);
	}
	if(t.size() != m) {
		cout << -1 << '\n';
		return 0;
	}
	int cur = 0, now = -1;
	k = 1;
	while(cur < t.size()) {
		auto it = p[t[cur]].lower_bound(now + 1);
		if(it == p[t[cur]].end()) {
			now = -1;
			k ++;
			continue;
		}
		cur ++;
		now = *it;
	}
	cout << (LL)(k - 1) * n + now << '\n';
    return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
我们要想要总长度尽量小，肯定每次往后匹配是最优的，如果往前匹配要多循环一次 $s$，这样答案肯定不是最优的。我们考虑开 $26$ 个平衡树，分别维护字母 $a \sim z$ 每一个字母出现的位置，每次答案就加上 $t$ 的当前的字母的下一个位置减去当前在 $s$ 的位置就行了。但是如果要循环一次才能匹配这么做就会有问题，我们可以把一个字母的位置插进平衡树里两次分别为 $i$ 和 $i+n$。如果要匹配字母的子树大小为空就说明无解。

**注意：开平衡树时根节点要开数组维护**

# Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int l,r,rnd,size,val;
}t[35][1145141];
int root[1145141],cnt[1145141];
int New(int val,int id)
{
	t[id][++cnt[id]].val=val;
	t[id][cnt[id]].rnd=rand();
	t[id][cnt[id]].size=1;
	return cnt[id];
}
void update(int p,int id)
{
	t[id][p].size=t[id][t[id][p].l].size+t[id][t[id][p].r].size+1;
}
int merge(int x,int y,int id)
{
	if(!x||!y)
		return x|y;
	if(t[id][x].rnd<t[id][y].rnd)
	{
		t[id][x].r=merge(t[id][x].r,y,id);
		update(x,id);
		return x;
	}
	else
	{
		t[id][y].l=merge(x,t[id][y].l,id);
		update(y,id);
		return y;
	}
}
void split(int p,int val,int &x,int &y,int id)
{
	if(!p)
		x=y=0;
	else
	{
		if(t[id][p].val<=val)
		{
			x=p;
			split(t[id][p].r,val,t[id][p].r,y,id);
		}
		else
		{
			y=p;
			split(t[id][p].l,val,x,t[id][p].l,id);
		}
		update(p,id);
	}
}
void insert(int x,int id)
{
	int a,b;
	split(root[id],x,a,b,id);
	root[id]=merge(merge(a,New(x,id),id),b,id);
}
int nxt(int x,int id)
{
	int ans,a,b;
	split(root[id],x,a,b,id);
	int p=b;
	while(p)
		ans=t[id][p].val,p=t[id][p].l;
	root[id]=merge(a,b,id);
	return ans;
}
string S,T;
int n,m;
int ans;
int now;
signed main()
{
	cin>>S>>T;
	n=S.size();
	m=T.size();
	S=' '+S;
	T=' '+T;
	for(int i=1;i<=n;i++)
		insert(i,S[i]-'a'+1),insert(i+n,S[i]-'a'+1);
	for(int i=1;i<=m;i++)
	{
		if(t[T[i]-'a'+1][root[T[i]-'a'+1]].size==0)
		{
			cout<<-1;
			return 0;
		}
		int nx=nxt(now,T[i]-'a'+1);
		ans+=nx-now,now=(nx-1)%n+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：大眼仔Happy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc138_e)

感觉有点熟但是忘记和哪道题很像了。

首先显然是贪心匹配。假如说上一次匹配到 $\rm lst$，那么优先选择 $({\rm lst},n]$ 匹配，没有再找 $[1,{\rm lst}]$，这时候就是相当于找下一段的位置了。由于只有 $26$ 个字母，所以每个字母用一个数据结构维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,m,lst;long long ans;
char s[N],t[N];
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
struct Segment_Tree
{
	int t[N<<2];
	void build(int k,int l,int r)
	{
		if(l==r)return t[k]=inf,void();
		build(ls,l,mid);build(rs,mid+1,r);
		t[k]=min(t[ls],t[rs]);
	}
	void upd(int k,int l,int r,int q,int v)
	{
		if(l==r)return t[k]=v,void();
		if(q<=mid)upd(ls,l,mid,q,v);
		else upd(rs,mid+1,r,q,v);
		t[k]=min(t[ls],t[rs]);
	}
	int ask(int k,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return t[k];
		int res=inf;
		if(ql<=mid)res=min(res,ask(ls,l,mid,ql,qr));
		if(qr>mid)res=min(res,ask(rs,mid+1,r,ql,qr));
		return res;
	}
}T[26];
int main(){
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);m=strlen(t+1);
	for(int i=0;i<26;i++)T[i].build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		int a=s[i]-'a';
		T[a].upd(1,1,n,i,i);
	}
	for(int i=1;i<=m;i++)
	{
		int b=t[i]-'a',id=T[b].t[1];
		if(id==inf)return printf("-1"),0;
		int num=T[b].ask(1,1,n,lst+1,n);
		if(num!=inf)lst=num;
		else ans+=n,lst=id;
	}
	printf("%lld\n",ans+lst);
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

一篇使用较为简单的贪心实现的解法。

### 思路

字符串题说实话是挺唬人的，但是考虑直接贪心解决即可。

关于无解的判断，因为要将 $S$ 复制 $10^{100}$ 次方份，所以只要 $T$ 中的每一个字符 $S$ 也有就一定能匹配上。反之就无法匹配，即无解。

判完无解开始着手贪心匹配，以 $f$ 代替 $T_i(0\le i<len_T)$ 在 $S$ 中匹配的字母的下标。先按顺序预处理出每个字母在 $S$ 中出现的下标，使用一个 `vector` 存下，下文以 $e$ 代替。然后对每个 $T_i$，借助库函数 `upper_bound` 寻找 $e_{T_i}$ 中大于 $f_{i-1}$ 的元素，如果有就说明不需要切到下一个文本串 $S$，否则切到下一个文本串 $S$。

最后统计一下 $f$ 中逆序对数即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5,mod=1e9+7;
int f[N],n,m,t,k,ans;
bool a[N],b[N];
map<pair<int,int>,bool>mp;
priority_queue<int,vector<int>,less<int>>pq;
vector<int>e[N];
inline int qread(){
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		t^=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
	if(x<0) x=-x,putchar('-');
	if(x>9) qwrite(x/10);
	putchar(x%10+'0');
	return;
}
inline int qpow(int x,int p,int mod){
	x=(p?x:1);
	mod=(mod?mod:LONG_LONG_MAX);
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (x*t)%mod;
}
inline int gcd(int x,int y){
	return (x%y==0?y:gcd(y,x%y));
}
inline int lcm(int x,int y){
	x/=gcd(x,y);
	return (x*y);
}
signed main(){
	string s,t;
	cin>>s>>t;
	int lens=s.size(),lent=t.size();
	for(int i=0;i<lens;i++){
		s[i]-='a';
		a[s[i]]=true;
		e[s[i]].push_back(i);
	}
	for(int i=0;i<lent;i++){
		t[i]-='a';
		b[t[i]]=true;
	}
	for(int i=0;i<26;i++){
		if((!a[i])&&b[i]){
			puts("-1");
			return 0;
		}
	}
	f[0]=e[t[0]][0];
	for(int i=1;i<lent;i++){
		auto it=upper_bound(e[t[i]].begin(),e[t[i]].end(),f[i-1]);
		if(it==e[t[i]].end()) f[i]=e[t[i]][0];
		else f[i]=*it;
	}
	for(int i=0;i<lent;i++) f[i]++;
	ans=f[0];
	for(int i=1;i<lent;i++){
		ans+=f[i]-f[i-1];
		if(f[i]<=f[i-1]) ans+=lens;
	}
	qwe(ans);
	return 0;
}
```

---

## 作者：__Chx__ (赞：1)

## 题目大意
给出两个字符串 $S$ 和 $T$，定义 $S'$ 为 $S$ 复制 $10^{100}$ 次后的字符串,设 $x$ 使 $T$ 成为 $S'$ 的子串（当且仅当 $S'$ 的前 $x$ 位删除任意个字符后等同于 $T$），求 $x$ 的最小值。

## 思路
我们考虑在 $S'$ 上搜索 $T$ 的每一个字符：

- 定义 $a[i][j]$ 为第 $j$ 个字符 $i$ 在 $S$ 中的位置 


- 对于 $T$ 的每一个字符，选出到达 $a[i][j]$ 的最小值

于是我们搜索时又有三种情况：

- $T[i]$ 在 $S$ 中不存在，直接输出 $-1$ 并结束搜索

- $T[i]$ 在 $S$ 的位置不在当前搜索位置的后面，考虑复制一遍 $S$，再计算

- $T[i]$ 在 $S$ 的位置在当前搜索位置的后面，考虑用二分搜索最近点并计算

我们就可以根据这三种情况进行 $T$ 的遍历，时间复杂度约为 $O(\left|T\right| log \left|S\right|)$，时间复杂度合理，方法可行。


## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s,t;
int a[30][100005],ans;
signed main(){
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		a[s[i]-'a'][0]++;
		a[s[i]-'a'][a[s[i]-'a'][0]]=i+1;
	}
	if(a[t[0]-'a'][0]==0){
		cout<<"-1";
		return 0;
	}
	int now=a[t[0]-'a'][1];
	ans=a[t[0]-'a'][1];
	for(int i=1;i<t.size();i++){
		if(!a[t[i]-'a'][0]){
			cout<<"-1";
			return 0;
		}
		if(a[t[i]-'a'][a[t[i]-'a'][0]]>now){
			int l=1,r=a[t[i]-'a'][0];
			while(l<=r){
				int mid=(l+r)/2;
				if(a[t[i]-'a'][mid]>now)  r=mid-1;
				else l=mid+1;
			}
			ans=ans+a[t[i]-'a'][l]-now;
			now=a[t[i]-'a'][l];
		}
		else{
			ans=ans+(s.size()-now+a[t[i]-'a'][1]);
			now=a[t[i]-'a'][1];
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：BMTXLRC (赞：1)

校内赛后两分钟AC人又来了。

考虑一下我们遍历 $t$ 数组，发现如果 $t$ 数组有不在 $s$ 数组中，一定是无解的。

如果存在，对应上一位的前面，后面，当前位置，三种情况，我们可以用平衡树查询。

举个例子，$s=\texttt{contest},t=\texttt{sentence}$。

$i=1,t_i=\texttt{s}$，此时 $last=0$，将平衡树 `split` 一下，看看右子树 $y$ 是否含有 $\texttt{s}$ 这个字母，如果有的话找到这个位置，就是 $6$，此时答案加上 $6$。

$i=2,t_i=\texttt{e}$，此时 $last=6$，发现 $\texttt{s}$ 后面没有 $\texttt{e}$，但是前面有，故 $ans$ 加上 $n-last+\min dis_\texttt{e}$。

以此类推。

至于实现方法，我们可以开 $26$ 棵平衡树，一棵专门存对应字母的位置。

当然由于我打二分就没打对过，我就没写，所以大家也是可以用二分实现的。

代码实现如下：

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e6+5;
char s[N],t[N];
struct FHQ_treap{
    int l,r,x,pri;
    int size;
}a[N][30];
int root[30],cnt[30],last,ans;
int new_node(int x,char ch){
    int k=ch-'a'+1;
    a[++cnt[k]][k].x=x;
    a[cnt[k]][k].pri=rand();
    a[cnt[k]][k].size=1;
    return cnt[k];
}
void pushup(int x,char ch){
    int k=ch-'a'+1;
    a[x][k].size=a[a[x][k].r][k].size+a[a[x][k].l][k].size+1;
    return;
}
void split(int now,int k,int &x,int &y,char ch){
    int p=ch-'a'+1;
    if(!now){
        x=y=0;
        return;
    }
    if(a[now][p].x<=k){
        x=now;
        split(a[now][p].r,k,a[now][p].r,y,ch);
    }else{
        y=now;
        split(a[now][p].l,k,x,a[now][p].l,ch);
    }
    pushup(now,ch);
}
int merge(int x,int y,char ch){
    int p=ch-'a'+1;
    if(!x||!y) return x+y;
    if(a[x][p].pri<a[y][p].pri){
        a[x][p].r=merge(a[x][p].r,y,ch);
        pushup(x,ch);
        return x;
    }else{
        a[y][p].l=merge(x,a[y][p].l,ch);
        pushup(y,ch);
        return y;
    }
}
int kth(int now,int x,char ch){
    int p=ch-'a'+1;
    while(1){
        if(x<=a[a[now][p].l][p].size) now=a[now][p].l;
        else if(x==a[a[now][p].l][p].size+1) return now;
        else x-=a[a[now][p].l][p].size+1,now=a[now][p].r;
    }
}
signed main(){
    scanf("%s%s",s+1,t+1);
    int n=strlen(s+1),m=strlen(t+1);
    for(register int i=1;i<=n;i++){
        int x,y,z;
        split(root[s[i]-'a'+1],i,x,y,s[i]);
        root[s[i]-'a'+1]=merge(merge(x,new_node(i,s[i]),s[i]),y,s[i]);//s中每个字母插入FHQ Treap
    }
    for(register int i=1;i<=m;i++){
        if(a[root[t[i]-'a'+1]][t[i]-'a'+1].size==0){
            printf("-1");
            return 0;
        }
        int x,y,z,p=t[i]-'a'+1;
        split(root[p],last,x,y,t[i]);
        if(a[y][p].size!=0){
            int q=a[kth(y,1,t[i])][p].x;
            root[p]=merge(x,y,t[i]);
            ans+=(q-last);
            last=q;
            continue;
        }//后面
        root[p]=merge(x,y,t[i]);
        x=0,y=0;
        split(root[p],last-1,x,y,t[i]);
        if(a[x][p].size!=0){
            int q=a[kth(x,1,t[i])][p].x;
            root[p]=merge(x,y,t[i]);
            ans+=(n-last+q);
            last=q;//前面
        }else{
            ans+=n;
            root[p]=merge(x,y,t[i]);
        }//就在这个位置
    }
    printf("%lld",ans);
}
```

---

## 作者：UnfortunatelyDead (赞：0)

选字符是贪心选的，显然要想最少字符一定得选最近的，因为如果我选了一个较远的，那么它的下一个字符我现在还是可以选择得到，所以选近的一定不劣于选远的。

那么我考虑对于当前字符 $i$，记上一个字符匹配的位置是 $x$，那么我选的东西将会被分成 $(x,n]$ 与 $[1,x)$ 两部分，其中后面一部分用到了新的字符串，按照顺序二分即可。

答案显而易见，为使用字符串的个数 $+ x$。

```cpp
vector<int> g[30];
signed main() {
	string s, t; cin >> s >> t;
	int len1 = s.size(), len2 = t.size();
	s = " " + s;
	for (int i = 1; i <= len1; ++i) g[s[i] - 'a'].eb(i);
	for (int i = 0; i < 26; ++i) g[i].eb(len1 + 1);
	int x = 0, y = 0;
	for (int i = 0; i < len2; ++i) {
		int a = t[i] - 'a';
		if (g[a].size() == 1) return puts("-1"), 0;
		++y;
		int u = *lower_bound(g[a].begin(), g[a].end(), y);
		if (u == len1+1) {
			++x;
			y = *lower_bound(g[a].begin(), g[a].end(), 0);
		} else y = u;
	} write(x * len1 + y, '\n');
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：0)

看有些大佬是用平衡树来写的，不过这题也是有很简单的贪心做法的。

对于 $T$ 中的每个字符，我们可以去寻找他第一次在 $S$ 中出现的位置，用二维数组去进行存储，我们先叫它 $sum$。

最后每次记录上一个选的数的位置为 $pre$，用二分来查找 $sum$ 中第一个大于 $pre$ 的数。

剩余细节在代码中。

```cpp
string s,t;
long long ret;
vector<vector<long long>>sum(200);
int main()
{
	cin>>s>>t;
	int size1=s.size(),m=t.size();
	s=' '+s,t=' '+t;
	for(int i=1;i<=size1;i++)
	{
		sum[s[i]].emplace_back(i);//c++11小妙招，让你push_back跑得飞快 
	}
	for(int i='a';i<='z';i++)
	{
		sum[i].emplace_back(size1+1); 
	}
	long long pre; 
	for(int i=1;i<=m;i++)
	{
		if(sum[t[i]].size()==1) 
		{
			cout<<-1;//S无T输-1 
			return 0;//一定要return而不是break 
		}
		auto cnt=lower_bound(sum[t[i]].begin(),sum[t[i]].end(),pre);//找一个不小于pre的数 
		if(*cnt==pre)
		{
			cnt++;//lower_bound可能找到等于pre的数 
		}
		int n1=*cnt;
		if(n1==size1+1)
		{
			ret+=size1;
			pre=sum[t[i]][0];//找不到就更新答案，并且pre也要更新 
		}
		else 
		{
			pre=n1;//找到了，更新 
		}
	}
	ret+=pre;
	cout<<ret;
}
```

---

