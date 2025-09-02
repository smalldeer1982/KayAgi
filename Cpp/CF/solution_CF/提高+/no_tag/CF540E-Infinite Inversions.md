# Infinite Inversions

## 题目描述

There is an infinite sequence consisting of all positive integers in the increasing order: $ p={1,2,3,...} $ . We performed $ n $ swap operations with this sequence. A $ swap(a,b) $ is an operation of swapping the elements of the sequence on positions $ a $ and $ b $ . Your task is to find the number of inversions in the resulting sequence, i.e. the number of such index pairs $ (i,j) $ , that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

## 说明/提示

In the first sample the sequence is being modified as follows: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF540E/c911e52ddf33371777464860f326e25b9c055886.png). It has 4 inversions formed by index pairs $ (1,4) $ , $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

## 样例 #1

### 输入

```
2
4 2
1 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 6
3 4
2 5
```

### 输出

```
15
```

# 题解

## 作者：kbzcz (赞：6)

~~csp初赛前三天还在刷水题~~

---
### 思路

显然，题目是要求求交换过后的数列的逆序对个数。

考虑朴素求逆序对，用的权值树状数组。但这题的数据范围是 $1\le x_i,y_i\le 2^{31}-1$，所以必须要离散化，但是离散化后就求不到那些**并没有被交换的数对答案的贡献**，所以我们考虑把被交换的数和没被交换的数分开计算。


------------

被操作过的数之间的逆序对个数显然离散化+树状数组就可以求了，所以这题的难点是求没被交换过的数和被交换过的数之间的逆序对个数。

![](https://cdn.luogu.com.cn/upload/image_hosting/wnyb9hb0.png)

假设一个数往前交换，红色圈是一个数的原来位置和所有交换完成后的位置。可以发现，因为中间的数并没有被交换过，所以不会产生逆序对，只有交换后的数会对中间**没被交换的每一个数**都产生一个逆序对，因为那个数的值比中间的都大，且在他们前面。    

往后交换同理。

综上，我们先把每个数离散化，并记录原来的位置和交换完后的位置。用树状数组求交换过的数的逆序对，再用一个循环求每个数到他原来位置之间没被交换的数的个数，并累加到答案中。

---

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+5;
struct node {
	int x,y;
}a[N];
int n;
LL ans;
int pos[N];
int c[N];
vector<int> ls;
int val(int x) {return lower_bound(ls.begin(),ls.end(),x)-ls.begin()+1;}
void lsnum() {
	sort(ls.begin(),ls.end());
	ls.erase(unique(ls.begin(),ls.end()),ls.end());
	for(int i=1;i<=n;i++) {
		a[i].x=val(a[i].x);
		a[i].y=val(a[i].y);
	}
}
int lowbit(int k){return k&-k;}
void add(int x,int k) {
	while(x<=2*n) {
		c[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x) {
	int sum=0;
	while(x) {
		sum+=c[x];
		x-=lowbit(x);
	}
	return sum;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&a[i].x,&a[i].y);
		ls.push_back(a[i].x);
		ls.push_back(a[i].y);
	}
	lsnum();
	for(int i=0;i<ls.size();i++) pos[i+1]=ls[i];
	for(int i=1;i<=n;i++) swap(pos[a[i].x],pos[a[i].y]);
	for(int i=0;i<ls.size();i++) {
		int x=pos[i+1],y=ls[i];
		ans+=abs(y-x)-abs(val(x)-(i+1));//求没被交换的数的贡献
	}
	for(int i=ls.size();i>=1;i--) {
		ans+=query(val(pos[i])-1);
		add(val(pos[i]),1);
	}
	printf("%lld",ans);
	return 0;
}
```

---
~~再水篇题解~~



---

## 作者：qczrz6v4nhp6u (赞：3)

双倍经验：P2448。

### Solution

注意到原序列中有很多形如 $u,u+1,\cdots,v$ 的段（即这些段没有被操作），而这些部分内部并不会产生逆序对，我们从这入手考虑。

设上述段对应的区间是 $[l,r]$，则一个容易注意到的性质是：如果存在 $p,q$ 满足 $l\le q\le r$ 且 $(p,q)$ 是逆序对，那么 $\forall l\le i\le r,(p,i)$ 是逆序对。

证明注意到 $p<l$ 且 $a_p>r$ 即可。对于 $(q,p)$ 是逆序对的情况也有类似的结论成立。

由以上的结论，$[l,r]$ 内的数在计算逆序对时并没有本质不同。我们可以把每段 $[l,r]$ 缩成任意一个 $[u,v]$ 内的数来计算逆序对，计算贡献时乘上 $(r-l+1)$ 即可。

缩完后的序列只有 $O(k)$ 个数，直接正常求逆序对即可。时间复杂度 $O(k\log k)$。

### Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
using ull=unsigned long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
const int N=1e5+5;
int n,a[N],b[N],va[N],vb[N],p[N<<1];
int num[N<<1],len;
int c[N<<2];
void add(int x,int k){
	x=(len<<1)-x;
	for(;x<(len<<1);x+=x&-x)
		c[x]+=k;
}
int ask(int x){
	x=(len<<1)-x;
	int res=0;
	for(;x;x-=x&-x)
		res+=c[x];
	return res;
}
int val(int x){return lower_bound(num+1,num+len+1,x)-num;}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i],b[i]);
		num[++len]=a[i];
		num[++len]=b[i];
	}
	sort(num+1,num+len+1);
	len=unique(num+1,num+len+1)-num-1;
	for(int i=1;i<=n;i++){
		va[i]=val(a[i]);
		vb[i]=val(b[i]);
		p[va[i]]=(va[i]<<1)-1;
		p[vb[i]]=(vb[i]<<1)-1;
	}
	for(int i=1;i<=n;i++)
		swap(p[va[i]],p[vb[i]]);
	ll ans=0;
	for(int i=1;i<=len;i++){
		ans+=ask(p[i]);
		add(p[i],1);
		if(i<len){
			ans+=ask(i<<1)*(num[i+1]-num[i]-1ll);
			add(i<<1,num[i+1]-num[i]-1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：__Star_Sky (赞：2)

双倍经验：P2448

## 题意简述

给定一个数列 $1,2,3\dots n$ 和 $k$ 次操作，每次操作交换数列中下标为 $x$ 和 $y$ 的数。求最终数列中有多少个逆序对。其中 $n,x,y\le2^{31}-1,k\le10^5 $。

## 前置知识
树状数组，离散化

## Solution

显然可以用树状数组求逆序对。但是难点在于原数列中可能有很多元素没有被交换过，要考虑怎么计算它们的贡献。

注意到操作数 $k\le10^5$，因此最多只有 $2\times10^5$ 个数被交换了。这样，最多会产生 $2\times10^5-1$ 个区间，处于这些区间之间的数都没有被交换过。设区间 $[l,r]$ 中的所有元素都没有被交换过，显然这些数两两之间都不可能产生逆序对，因此考虑用任意一个 $x\in[l,r]$ 代替这些数，并将 $x$ 的权值设为 $r-l+1$ 。对于交换过的数，权值设为 $1$ 即可。这样一来，我们就得到了一个新的序列，这个序列仅有不超过 $4\times10^5-1$ 个数，离散化之后就可以使用权值树状数组来求逆序对了。注意对于每个 $x$ 统计贡献时要乘上 $x$ 的权值。

时间复杂度 $O(k \log{k})$。

## Code
```
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x
#define INF 0x7fffffff
using namespace std;
const int N=1e6+10;
struct node{int x,y;}t[N];
int n;
int a[N],b[N],c[N];
void add(int x,int k) {while(x<=n) c[x]+=k,x+=lowbit(x);}
int get_sum(int x) {int res=0;while(x>=1) res+=c[x],x-=lowbit(x);return res;}
int s[N],siz[N];//siz[x]表示x的权值
signed main()
{
	int k;
	scanf("%lld",&k);
	for(int i=1;i<=k;i++) 
		scanf("%lld%lld",&t[i].x,&t[i].y),
		a[i*2-1]=t[i].x,a[i*2]=t[i].y;
	memcpy(b,a,sizeof(b));
	sort(b+1,b+2*k+1);
	n=unique(b+1,b+2*k+1)-b-1;
	for(int i=1;i<=n;i++) a[i*2-1]=b[i];
	n=n*2-1;
	for(int i=1;i<=n;i++) 
	{
		if(i&1) continue;
		if(a[i+1]==a[i-1]+1) a[i]=INF;
		else a[i]=a[i-1]+1,s[i]=a[i+1]-a[i-1]-1;
	}
	memcpy(b,a,sizeof(b));
	sort(a+1,a+n+1);
	int tmp=n;
	while(a[n]==INF) n--;
	for(int i=1;i<=tmp;i++)
	{
		if(b[i]==INF) continue;
		int idx=lower_bound(a+1,a+n+1,b[i])-a;
		siz[idx]=s[i];
	}
	for(int i=1;i<=n;i++) if(!siz[i]) siz[i]=1;
	memcpy(b,a,sizeof(b));
	for(int i=1;i<=k;i++)
	{
		int idx=lower_bound(b+1,b+n+1,t[i].x)-b;
		int idy=lower_bound(b+1,b+n+1,t[i].y)-b;
		swap(a[idx],a[idy]);
	}
	int ans=0;
	for(int i=n;i>=1;i--)
	{
		int idx=lower_bound(b+1,b+n+1,a[i])-b;
		ans+=siz[i]*get_sum(idx-1);
		add(idx,siz[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：fantastic_dream (赞：2)

#### 写在题解前的疑问
笔者在普通 `cin` 下跑出 405 ms，关掉同步后只用了 109 ms，按题目的输入量我觉得不应该差距这么大。具体见：[我的记录](https://www.luogu.com.cn/record/list?pid=CF540E&user=848391)。欢迎各位大佬说明。

------------
### 解答
我们很容易发现交换后，被交换的最小数前面与最大数后面的数不会对答案产生贡献。那考虑在被换数中间的数，发现一段在中间的数，若对答案有贡献，那么对于被交换数要么贡献为 $0$，要么贡献一定为该段的长度。那么这些数便可以看成一个数，然后便可以求答案。

简单来说，就是求“带权值”的逆序对。离散化后，对于每一段中间没有被交换的数，可以用该段的第一个数当作该段的代表，以该段的长度为该代表的权值，然后就能简单地跑逆序对了，由于这里每个（段）数都有权值，用树状数组比较方便。

由于被交换的数最多只有 $2\times n$ 个，那么段数最多也就只有 $3\times n$ 段，所以离散化后把值域压缩后可以轻松通过本题，时间复杂度省去常数为 $O(n\log n)$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int ma=400005;
int k,a1[ma],a2[ma],sz[ma],id[ma],t[ma],tr[ma],n=0,dy[ma];//id 为每段数的代表，t 为权值，dy 为离散化后的排名  
int lb(int x){return x&(-x);}
void upd(int pos,int x){while(pos<=n)	tr[pos]+=x,pos+=lb(pos);}
int que(int pos){
	int ans=0;
	while(pos)	ans+=tr[pos],pos-=lb(pos);
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>a1[i]>>a2[i];
		sz[i]=a1[i],sz[k+i]=a2[i];
	}	
	sort(sz+1,sz+1+2*k);
	int len=unique(sz+1,sz+1+2*k)-sz-1;//离散化 
	for(int i=1;i<=len;i++){
		id[++n]=sz[i];t[n]=1;
		if(sz[i+1]-sz[i]>1){
			id[++n]=sz[i]+1;
			t[n]=sz[i+1]-sz[i]-1;
		}
	}
	for(int i=1;i<=n;i++)	dy[i]=i;//由于 id 数组有序，可以直接确定 
	for(int i=1;i<=k;i++){
		int p1=lower_bound(id+1,id+n+1,a1[i])-id,p2=lower_bound(id+1,id+n+1,a2[i])-id;
		swap(dy[p1],dy[p2]),swap(t[p1],t[p2]);
	}
	long long ans=0;//注意数据范围 
	for(int i=n;i>=1;i--){
//		cout<<dy[i]<<' '<<t[i]<<'\n';
		ans+=1ll*que(dy[i]-1)*t[i];
		upd(dy[i],t[i]);
	}
	cout<<ans;
	return 0;
}
```
讲的不是很清楚，望多指正捏。另附：[题目传送门](https://www.luogu.com.cn/problem/CF540E)，[数据比较水的双倍经验](https://www.luogu.com.cn/problem/P2448)。

---

## 作者：45dino (赞：2)

$n$ 次交换后，大多数数位都没有发生改变，只有 $2n$ 个发生改变，用 map 将其依次记录。

这些发生改变的位被设为“特殊位”。

由于非特殊位与非特殊位之间不会有逆序对关系，所以一对逆序对要不然是两个特殊位之间，要不然是一个特殊位和一个非特殊位。

两个特殊位之间的逆序对相当好找，离散化后用树状数组统计，复杂度为 $\Theta (n \log_2 n)$。

对于一个特殊位 $a_i=j(i\neq j)$，要找 $a_k=k$ 的个数，满足 $i<k<j$ 或 $j<k<i$，且 $k$ 不能是特殊位。

因为 $a_i=j$ 是特殊位，所以第 $j$ 位也是特殊位。问题变成了求 $(i,j)$ 之间有多少个非特殊位。设 $i$ 是第 $x$ 个特殊位，$j$ 是第 $y$ 个特殊位，就应该有 $|i-j-x+y|$ 个特殊位。

参考代码：
```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define int long long
using namespace std;
void fileio(const string &s)
{
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int n,c,ans,t[400001];
map<int,int> mp,cnt;
int lowbit(int x)
{
	return x&(-x);
}
void add(int x)
{
	for(;x<=2*n;x+=lowbit(x))
		t[x]+=1;
}
int query(int x)
{
	int ans=0;
	for(;x;x-=lowbit(x))
		ans+=t[x];
	return ans;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read();
		if(!mp[x])
			mp[x]=x;
		if(!mp[y])
			mp[y]=y;
		swap(mp[x],mp[y]);
	}
	for(auto i:mp)
	{
		int x=i.first;
		cnt[x]=++c;
	}
	for(auto i:mp)
	{
		int x=i.first,y=i.second;
		ans+=abs(x-y-cnt[x]+cnt[y]);
		ans+=cnt[x]-query(cnt[y])-1;
		add(cnt[y]);
	}
	cout<<ans<<endl;
	return 0;
}
``

---

## 作者：OtterZ (赞：0)

~~说一下：把这题评紫的人也是懂算法的~~
# 题意
你有一个无限长的 $a_i = i$ 的数列，交换若干位置，然后问你最终有过少个逆序对。
# 求逆序对的树状数组操作
对于完整的数列，我们可以将其离散化，然后用树状数组倒序操作，每次统计 $< a_i$ 的位置之和，再在 $a_i$ 相应位置 $+1$，然后你就过了。
# 回到此题
操作两个位置 $\le 10^9$，序列无限长，不保证原来的方式可以过了，因为处理不了完整的序列，现在怎么办？
## 大致思路
因为操作不超过 $10^5$，我们可以只取操作过的数放在一起，然后同上处理即可。
## 其他的怎么办
交换操作后，最前面操作之前或最后面操作之后的数显然不会影响答案，只需要考虑新构成的数列相邻两个下表的原本中间的数。
当后面有 $x$ 个数小于中间的所有数，则前面也会有 $x$ 个数大于其中所有的数，同时，因为相应子序列是连续的，前后没有原本穿插在中间的数。
我们可以将这几段子序列统一处理，这样就不影响复杂度了。
# 时间复杂度
我们至多处理 $2 \times n$ 个特殊位置和 $2 \times n - 1$ 个特殊位置中间的子序列。用树状数组处理是 $\operatorname{O}(n\log n)$ 的。另外离散化也是 $\operatorname{O}(n\log n)$ 的，故而整体是 $\operatorname{O}(n\log n)$ 的，因为 $n \le 10 ^ 5$，故而可过。
# 代码

```
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
int BIT[200009],n,sz,art[200009],bk[200009],cnt,a[100009],b[100009],ctr[200009];
map<int,int>mp;
//树状数组
void add(int pl,int val){
	for(int i = pl; i <= sz; i += i & (-i)){
		//printf("%d\n",i);
		BIT[i] += val; 
	}
}
int query(int pl){
	int ans = 0;
	for(int i = pl; i > 0; i -= i & (-i)){
		ans += BIT[i]; 
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++){
		scanf("%d %d",&a[i],&b[i]);
		art[++cnt] = a[i];
		art[++cnt] = b[i];
	}
	//离散化
	sort(art + 1,art + cnt + 1);
	for(int i = 1; i <= cnt; i ++){
		if(i != 0 && art[i] == art[i - 1])
			continue;
		mp[art[i]] = ++ sz;
		bk[sz] = art[i];
		ctr[sz] = sz;
	}
	//交换
	for(int i = 1; i <= n; i ++){
		swap(ctr[mp[a[i]]],ctr[mp[b[i]]]);
	}
	//正式的树状数组统计
	long long ans = 0;
	for(int i = sz; i >= 1; i --){
		if(i != sz){
			ans += 2ll * (bk[i + 1] - bk[i] - 1) * query(i);
		}
		ans += query(ctr[i] - 1);
		add(ctr[i],1);
	}
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：cjrqwq (赞：0)

### 思路

虽然值域很大，但是 $n$ 不大。看个样例：
```
2
3 8
5 10
```
将点交换后，会发现对于 $x<2$ 或 $x>10$ 的数，不会产生逆序对。

同时，对于 $6,7$， 会发现产生的逆序对是一样的。运用整体思想，把它们看成一个点，称为“区间点”。

对于需要修改的点，我们也看成一个点，至多有 $2\times 10^5$ 个点，构成 $2\times 10^5-1$ 个区间点。所以数组记得开到 $4\times 10^5$。

因为求逆序对只在意数的相对大小，所以将每个点离散化。对于区间点，选其中的任意值离散化都相同。

**注意：一个区间点实际上有区间点的长度个。**

然后对所有的点求逆序对即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 5e5+10;
int n,m;
struct BIT{
    int c[N],t[N];
    int tg,len=N;
    void clear() {tg++;}
    void init(int l) {len=l;}
    #define lowbit(x) ((x)&-(x))
    void upd(int x,int k) {for(;x<=len;x+=lowbit(x)) if(tg==t[x]) c[x]+=k; else c[x]=k, t[x]=tg;}
    int s(int x) {int p=0;for(;x;x-=lowbit(x)) if(tg==t[x]) p+=c[x]; return p;}
}c;
int p[N],cnt,x[N],y[N];
int a[N],t[N],rk[N];
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>x[i]>>y[i];
		p[++cnt]=x[i],p[++cnt]=y[i];
	}
	sort(p+1,p+cnt+1);
	cnt=unique(p+1,p+cnt+1)-(p+1);
	int cc=1;
	a[cc]=p[1],t[cc]=1;
	for(int i=2;i<=cnt;i++) {
		if(p[i]-p[i-1]>1) {
			a[++cc]=p[i-1]+1;
			t[cc]=p[i]-p[i-1]-1;
		}
		a[++cc]=p[i],t[cc]=1;
	}
	#define xb(i) (lower_bound(a+1,a+cc+1,i)-a)
	for(int i=1;i<=cc;i++) {
		rk[i]=i;
	}
	for(int i=1;i<=n;i++) {
		int xx=xb(x[i]),yy=xb(y[i]);
		swap(t[xx],t[yy]);
		swap(rk[xx],rk[yy]);
	}
	c.init(cc);
	int ans=0;
	for(int i=cc;i>=1;i--) {
		ans+=c.s(rk[i]-1)*t[i];
		c.upd(rk[i],t[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：forever_nope (赞：0)

## 简要分析

求逆序对，但是元素很多（$\le 10^9$），由于题目给出的 $n$ 却比较小，所以我们可以从 $n$ 入手：

显而易见，$10^9$ 的元素中最多只会有 $2 \times 10^5$ 个被交换（不会重复交换一个元素），而剩下的大量数据如果都储存下来，是没有意义的。

我们可以将没有参与交换的元素中，连续的部分看成一个整体，这里就用到了离散化的思想，将这些元素合并以后，剩下的元素就可以 $O(n \log n)$ 求逆序对了。

## 逆序对

逆序对怎么求，这里我们可以用树状数组求。由于这个不是模板题，不再解释。（~~都是紫题了还要讲逆序对？~~）

但是在这道题中，一部分元素是包含多个元素的，怎么办？

这就可以用到权值逆序对：我们在查找的过程中，现在发现了一个现在数组中的一对逆序对 $p_i > p_j$（$i < j$），$p_i$ 包含 $t_i$ 个元素，$p_j$ 包含 $t_j$ 个元素。因为只有连续的区间才会被合并，所以 $p_i$ 包含的所有元素都大于 $p_j$ 中的任意元素。

因此，$p_i$ 和 $p_j$ 对答案的贡献为 $t_i \times t_j$。

## 细节和易错点

1. 数组别开的太小，开到 $2 \times 10^5$ 是会 RE 的，我开到了 $4 \times 10^5$。

2. $10^5$ 级别的数据，不开 `long long` 怎么行？

## 代码

（由于我大量使用了 STL，所以效率并不太高 ~~懒 呵呵~~）

```cpp
#include <bits/stdc++.h>

#define int long long

#define rr read()

using namespace std;

const int N = 4e5 + 10;

// 快读

inline int read()
{
    int num = 0, flag = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            flag = -1;
    for (; isdigit(ch); ch = getchar())
        num = (num << 3) + (num << 1) + ch - '0';
    return num * flag;
}

// 存放元素

struct node
{
    int x, y;
    node()
    {
        x = y = 0;
    }
    node(int _x, int _y)
    {
        x = _x, y = _y;
    }
    bool operator<(const node &t) const
    {
        return x < t.x;
    }
};

vector<node> q;
vector<node> a;

set<node> uq;
set<node> ad;

unordered_map<int, int> to;

// 树状数组

int s[N];

inline int lobit(int x)
{
    return x & -x;
}

void upd(int x, int t)
{
    for (; x < N; x += lobit(x))
        s[x] += t;
}

int que(int x)
{
    int res = 0;
    for (; x; x -= lobit(x))
        res += s[x];
    return res;
}

signed main()
{
    int m = rr;
    for (int i = 0; i < m; ++i)
        q.push_back({rr, rr}), uq.emplace(q[i].x, 1), uq.emplace(q[i].y, 1);

    // 去重和合并

    set<node>::iterator _a = uq.begin(), _b(_a);
    for (++_b; _b != uq.end(); ++_a, ++_b)
        if (_a->x < _b->x - 1)
            ad.emplace(_b->x - 1, _b->x - _a->x - 1);
    uq.insert(ad.begin(), ad.end());

    int n = 0;
    for (node i : uq)
        to[i.x] = n++, a.push_back({n, i.y});

    // 进行交换操作

    for (int i = 0; i < m; ++i)
        swap(a[to[q[i].x]], a[to[q[i].y]]);

    // 求逆序对

    int ans = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        ans += que(a[i].x - 1) * a[i].y;
        upd(a[i].x, a[i].y);
    }

    printf("%lld\n", ans);
    return 0;
}
```

---

