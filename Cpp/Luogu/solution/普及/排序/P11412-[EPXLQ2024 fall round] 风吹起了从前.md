# [EPXLQ2024 fall round] 风吹起了从前

## 题目背景

对于过去，温昭雪有着断断续续的记忆。

## 题目描述

具体地，她有 $n$ 条记忆，每条记忆是一个长度不超过 $100$ 的字符串。第 $i$ 条记忆 $S_i$ 位于她心灵的 $r_i$ 深处，对她有 $v_i$ 的价值。

温昭雪正在试图恢复自己记忆中的美好，可记忆实在太多太复杂，她只能想到她记忆的一段前缀 $Q$ 和她能到达的最深位置 $d$。只有满足对应的 $Q$ 是 $S_i$ 的前缀且 $r_i \le d$ 的记忆才能被温昭雪回想到。

现在，温昭雪有 $m$ 次尝试。她想知道，对于每次尝试，她能获得的所有记忆价值之和是多少。

## 说明/提示

### 提示

本题对前缀的定义为：对于字符串 $S,P$，若 $|P| \le |S|$ 且对所有 $1 \le i \le |P|$ 均有 $S_i=P_i$，则称 $P$ 是 $S$ 的前缀。

### 数据规模与约定

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n \le$ | $ m\le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $100$ | $100$ | | $11$ |
| $1$ | $10^4$ | $10^5$ | $d = 10^9$ | $13$ |
| $2$ | $10^4$ | $10^5$ | 字符串长度不超过 $2$ | $9$ |
| $3$ | $10^4$ | $10^3$ | | $26$ |
| $4$ | $10^4$ | $10^5$ | | $41$ |

对于所有数据，保证 $1 \le |S_i|,|Q| \le100, 0 \le r_i,v_i,d \le 10^9$，所有字符串仅由小写字母组成。

请注意时间复杂度常数因子带来的影响。

请考虑使用较快的输入输出方式。

## 样例 #1

### 输入

```
5 6
5 6 abcab
7 10 abcba
4 3 abc
3 6 ade
2 4 cde
2 abc
4 abc
5 abc
6 a
7 c
8 ab```

### 输出

```
0
3
9
15
4
19```

# 题解

## 作者：SunsetVoice (赞：5)

[背景故事](https://www.luogu.com.cn/paste/wjv5htoq)

提供一个能将此题降上位橙的解法。

先按 $d$ 从小到大排序对每一个可能的前缀建桶，记录所有能对这个字符串产生贡献的 $d,v$ 数值，最后对 $v$ 做前缀和。

由于我们已经按 $d$ 排好了序，所以 $d$ 在数组中一定是从小到大排序的，查询时二分即可。

复杂度（使用 `map` 情况下） $O(n\log n+nS_i\log nS_i+m\log nS_i)$。

考虑在常数上优化，首先尽量少开 `long long`，后对每个桶记录是否已计算好前缀和以保证计算时只计算一次，再优化输入输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct memory{
	bool isvb;
	vector<long long>d,v,vb;
	void cl(){
		long long sum = 0;
		for(long long hjx:v){
			sum+=hjx;
			vb.push_back(sum);
		}
		isvb = 1;
	}
};
map<string,memory>mp;
long long n,m;
struct node{
	int d,v;
	string str;
}a[200001];
bool cmp(node x,node y){
	return x.d<y.d;
}
inline string read()
{
	string str="";
	char ch=getchar();
	while(ch==' ' || ch=='\n' || ch=='\r')
	{
		ch=getchar(); 
	}
	while(ch!=' ' && ch!='\n' && ch!='\r')
	{
		str+=ch;
		ch=getchar();
	} 
	return str;
}
signed main(){
	scanf("%lld %lld",&n,&m);
	for(register int i = 1;i<=n;i++){
		scanf("%d %d",&a[i].d,&a[i].v);
		a[i].str = read();
	}
	sort(a+1,a+1+n,cmp);
	for(register int i = 1;i<=n;i++){
		string nstr = "";
		int gl = a[i].str.length();
		for(register int j = 0;j<gl;j++){
			nstr+=a[i].str[j];
			mp[nstr].d.push_back(a[i].d);
			mp[nstr].v.push_back(a[i].v);
			mp[nstr].isvb = 0;
		}
	}
	for(int i = 1;i<=n;i++){
		string nstr = "";
		int gl = a[i].str.length();
		for(int j = 0;j<gl;j++){
			nstr+=a[i].str[j];
			if(mp[nstr].isvb==0){
				mp[nstr].cl();
			}
		}
	}
	while(m--){
		int fd;
		string fq;
		scanf("%d",&fd);
		cin>>fq;
		if(!mp.count(fq)){
			printf("0\n");
			continue;
		}
		int pos = upper_bound(mp[fq].d.begin(),mp[fq].d.end(),fd)-mp[fq].d.begin()-1;
		if(pos<0){
			printf("0\n");
			continue;
		}
		printf("%lld\n",mp[fq].vb[pos]);
	}
	return 0;
}
```

---

## 作者：ljc2230 (赞：5)

[P11412 [EPXLQ2024 fall round] 风吹起了从前](https://www.luogu.com.cn/problem/P11412)  
### 题目大意  
给出 $n$ 个字符串及其价值和深度，之后输入几个字符串判断该字符串是否为之前字符串的前缀的同时深度不小于它，输出其价值和。
### 思路解析  
本题直接选择用字典树来存储每一个记忆，然后用一个通过存储每一个节点的价值和深度，在最终统计结果的时候，进行判断即可。  
~~不开 long long 见祖宗。~~
### 代码
```
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
int n,m;
int t[N][30],r[N],v[N];
vector<int>prc[N];
int cnt;

void insert(string s,int p){
	int now=0;
	for(auto x:s){
		int k=x-'a';
		if(!t[now][k])t[now][k]=++cnt;
		now=t[now][k];
		prc[now].push_back(p);
	}
}

int find(string s){
	int now=0;
	for(auto x:s){
		int k=x-'a';
		if(!t[now][k])return 0;
		now=t[now][k];
	}
	return now;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>r[i]>>v[i];
		string s;
		cin>>s;
		insert(s,i);
	}
	for(int i=1;i<=m;i++){
		int t;
		string s;
		cin>>t>>s;
		long long k=find(s),ans=0;
		for(auto x:prc[k]){
			if(r[x]<=t)ans+=v[x];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：4)

[传送门](https://www.luogu.com.cn/problem/P11412)

将记忆称为操作一，回想称为操作二，将操作一和操作二一起放入操作序列中，按照操作的 $r$ 或者 $d$ 从小到大排序，排序后建一棵字典树，按序进行相应的插入或查询操作，插入时对于遍历到的每一个节点加上价值，查询时遍历到结束后目前所在的节点上的价值就是答案，最后再按照输入时的顺序输出答案，注意当 $r$ 或 $d$ 相同时应该先让操作一先进行，排序时注意一下，因为题目中产生价值的记忆的 $r$ 可以等于回想的 $d$，我们对这些操作进行这样的排序可以使目前插入字典树的所有回忆都满足 $r$ 小于等于回想的 $d$，可以方便进行答案的查询。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,len;
struct aaa
{
	char s[110];
	int id;
	ll x,v,ans;
}cz[110010];
int tr[1000010][26],tot=0;
ll sum[1000010];
inline void Insert(int dj)
{
	int p=0;
	for(register int i=0;i<len;i++)
	{
		int pos=cz[dj].s[i]-'a';
		if(!tr[p][pos]) tot++,tr[p][pos]=tot;
		p=tr[p][pos],sum[p]+=cz[dj].v;
	}
}
inline void query(int dj)
{
	int p=0;
	for(register int i=0;i<len;i++)
	{
		int pos=cz[dj].s[i]-'a';
		if(!tr[p][pos]) tot++,tr[p][pos]=tot;
		p=tr[p][pos];
	}
	cz[dj].ans=sum[p];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++) scanf("%lld%lld",&cz[i].x,&cz[i].v),cin>>cz[i].s,cz[i].id=1e9;
	for(register int i=1;i<=m;i++) scanf("%lld",&cz[n+i].x),cin>>cz[n+i].s,cz[n+i].v=-1,cz[n+i].id=i;
	sort(cz+1,cz+n+m+1,[](aaa x,aaa y){if(x.x==y.x) return x.v>y.v;return x.x<y.x;});
	for(register int i=1;i<=n+m;i++)
	{
		len=strlen(cz[i].s);
		if(cz[i].v!=-1) Insert(i);
		else query(i);
	}
	sort(cz+1,cz+n+m+1,[](aaa x,aaa y){return x.id<y.id;});
	for(register int i=1;i<=m;i++) printf("%lld\n",cz[i].ans);
	return 0;
}
```

---

## 作者：Tokisaki__kurumi (赞：3)

# [题目链接](https://www.luogu.com.cn/problem/P11412)

### 思路

很典的一道题，不难发现字符串处理顺序的先后对答案没有影响

因此我们可以将添加字符串和查询离线下来，根据深度排序，每处理一个询问就将深度在它之前的字符串添加进去。

字符串添加可以用 $trie$ ，查询用二分。

 $l$ 为字符串长度，总时间复杂度  $(nl+m\log m+ml)$ 
 。

然后就做完了
### 
### code
```
#define LOCAL
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ll long long
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int> 
#define max(a,b) ((a)<(b)?(b):(a))
#define min(a,b) ((a)<(b)?(a):(b))
#define sort stable_sort
using namespace std;
using namespace __gnu_pbds;
namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline int read(double &x){return scanf("%lf",&x);}
            inline int read(long double &x){return scanf("%Lf",&x);}
            inline void dwrite(const double &x,int y=6,bool flag=1){printf("%.*lf",y,x),flag?putchar(' '):putchar(' ');}
            inline void dwrite(const long double &x,int y=6,bool flag=1){printf("%.*Lf",y,x),flag?putchar(' '):putchar(' ');}
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const char *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch[50]={};read(ch),x=ch;}
            inline void write(const string &x){int len=x.length();for(int i=0;i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>
            inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar(' ');}
            inline __int128 read(){static __int128 x;return read(x);}
            template<typename type>
            inline type put(type x,bool flag=1){write(x),flag?putchar(' '):putchar(' ');return x;}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;
inline string read1()
{
	string str="";
	char ch=getchar();
	while(ch==' ' || ch=='\n' || ch=='\r')
	{
		ch=getchar(); 
	}
	while(ch!=' ' && ch!='\n' && ch!='\r')
	{
		str+=ch;
		ch=getchar();
	 } 
	return str;
}
const int N=1e5+1005;
const int M=1e6+5;
const int inf=1e9+5;
const int mod=1e9+7;
struct query{
	int r;
	string s;
	int id;
}q[N];
struct node{
	int r,v;
	string s;
}a[N];
int ch[26][M];
ll v[M];
int n,m;
int t[N];
int tot;
int top;
inline bool cmp(node a,node b){
	return a.r<b.r;
}
inline bool cmp1(query a,query b){
	return a.r<b.r;
}
inline int erfen(int pos){
	int l=1,r=n,mid,res=0;
	while(l<=r){
		mid=l+r>>1;
		if(a[mid].r<=pos){
			l=mid+1;
			res=mid;
		}else r=mid-1;
	}
	return res;
}
inline void insert(string s,int vl){
	int p=0;
	int l=s.size();
	for(int i=0;i<l;++i){
		int c=s[i]-'a';
		
		if(!ch[c][p]){
			ch[c][p]=++top;
		}
		p=ch[c][p];
		v[p]+=vl;
	}
}
inline ll query(string s){
	int p=0;
	int l=s.size();
	for(int i=0;i<l;i++){
		int c=s[i]-'a';
		if(!ch[c][p]){
			return 0ll;
		}
		p=ch[c][p];
	}
	return v[p];
}
ll ans[N];
inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i){
    	read(a[i].r,a[i].v);
    	a[i].s=read1();
    	// t[++tot]=a[i].r;
    }
    for(int i=1;i<=m;i++){
    	read(q[i].r);
    	q[i].s=read1();
    	q[i].id=i;
    	// t[++tot]=q[i].r;
    	
    }
    sort(a+1,a+n+1,cmp);
    sort(q+1,q+m+1,cmp1);
    int last=1;

    for(int i=1;i<=m;i++){
    	int pos=erfen(q[i].r);
    	
    	for(;last<=pos;last++){
    		insert(a[last].s,a[last].v);
    	}
    	ans[q[i].id]=query(q[i].s);
    }
    for(int i=1;i<=m;i++){
    	write(ans[i]);
    	puts("");
    }
}

signed main(){
    int _=1;
    while(_--) solve();
    return 0;
}

```

---

## 作者：CaiZi (赞：2)

### 思路分析
感觉有点板。

看到“查询以某个串为前缀的串的价值和”，应该可以很显然的想到字典树，先考虑没有深度的限制应该怎么做。

我们可以把给定的每个字符串加入字典树，加入的同时给路径上的每个节点的价值加 $v_i$。查询时只需要找到对应位置并输出该节点的价值即可。

现在加上深度的限制，显然可以把给定的记忆和查询的记忆按照深度，进行从小到大排序。排完序后，动态加入字符串并查询即可。
### 代码展示
时间复杂度 $O(n\log n+m\log m+\sum S+\sum Q)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct query{
	int x,y;
	string z;
	inline friend bool operator < (query l,query r){
		return l.x<r.x;
	}
}a[10001],b[100001];
struct trie{
	struct node{
		int s[26];
		long long t;
	}w[1000001];
	int c=1;
	inline void insert(string l,long long r){
		int j=0;
		w[0].t+=r;
		for(int i=0;i<l.length();i++){
			if(w[j].s[l[i]-'a']==0){
				w[j].s[l[i]-'a']=c;
				c++;
			}
			j=w[j].s[l[i]-'a'];
			w[j].t+=r;
		}
	}
	inline long long find(string l){
		int j=0;
		for(int i=0;i<l.length();i++){
			if(w[j].s[l[i]-'a']==0){
				return 0;
			}
			j=w[j].s[l[i]-'a'];
		}
		return w[j].t;
	}
}f;
int n,m,p=1;
long long g[100001];
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].x>>b[i].z;
		b[i].y=i;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		while(p<=n&&a[p].x<=b[i].x){
			f.insert(a[p].z,a[p].y);
			p++;
		}
		g[b[i].y]=f.find(b[i].z);
	}
	for(int i=1;i<=m;i++){
		cout<<g[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：NTT__int128 (赞：1)

注意到 $r_i\le d$ 不好在线处理，考虑离线。

将记忆按 $r$ 从小到大排序，尝试按 $d$ 从小到大排序。每次将 $r_i\le d$ 的记忆放入 Trie 中。

然后改一下 Trie 的 `find` 即可。（好像和板题的 `find` 是一样的）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e7+5,M=1e5+5;
struct trie{
	int nxt[N][30],cnt=0;
	ll siz[N];
	int get(char c){return c-'a';}
	void insert(string s,int v){
		int p=0;
		for(int i=0;i<(int)s.size();i++){
			int x=get(s[i]);
			if(!nxt[p][x])nxt[p][x]=++cnt;
			siz[p]+=v;
			p=nxt[p][x];
		}
		siz[p]+=v;
	}
	ll find(string s){
		int p=0;
		for(int i=0;i<(int)s.size();i++){
			int x=get(s[i]);
			if(!nxt[p][x])return 0;
			p=nxt[p][x];
		}
		return siz[p];
	}
}tr;
struct memory{
	int r,v;
	string s;
	bool operator<(const memory&a)const{return r<a.r;}
}e[M];
struct attempt{
	int d,id;
	string q;
	bool operator<(const attempt&a)const{return d<a.d;}
}a[M];
int n,m;
ll ans[M];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>e[i].r>>e[i].v>>e[i].s;
	for(int i=1;i<=m;i++)cin>>a[i].d>>a[i].q,a[i].id=i;
	sort(e+1,e+n+1);sort(a+1,a+m+1);
	int p=1;
	for(int i=1;i<=m;i++){
		while(p<=n&&e[p].r<=a[i].d)tr.insert(e[p].s,e[p].v),p++;
		ans[a[i].id]=tr.find(a[i].q);
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Jia_Sylvia (赞：0)

## **讲述一种哈希的做法：**

本人为哈希初学者且代码能力有限，有问题还请各位大佬指出。

- 首先用结构体储存每条记忆的深度 $r$,价值 $v$ 以及字符串 $s$ 。
- 再让它们按深度从小到大进行排序
用 $dox$ 记录最长字符串的长度,方便后续操作：
```cpp
for(int i=1;i<=n;i++) {
        cin>>st[i].r>>st[i].v>>st[i].s;
        ll len = st[i].s.length();
        dox=max(len, dox);
    }
```
- 接下来是挨个求出每个字符串的哈希值并储存下来:

```cpp
for(int i=1;i<=n;i++) {
        ll len=st[i].s.length();
        h[i][0]=st[i].s[0];
        for(int j=1;j<len;j++) {
            h[i][j]=h[i][j-1]*p+st[i].s[j];
        }
    }
```
### 然后是重中之重。

这里为了防止因字符串长度不同而导致出现哈希碰撞的概率变大,用了一个二维 vector，但本题一维也可以过(代码将一并放到后面)。

本质为将前  $j$ 位一样的字符串的深度与价值单独放置在一个二维数组(第一维代表长度)里面。

并用 map 去记录跑到的字符串长度及它的哈希值，方便后续查询。

(因为前面已经将结构体按照深度从小到大排放,所以放进 vector 的时候也会变成深度小的先进)。
```cpp
for(int j=0;j<dox;j++) {
        ll cnt=0;
        for(int i=1;i<=n;i++) {
            if(!mp[{j,h[i][j]}]) {
                mp[{j,h[i][j]}]=++cnt;
            }
            f[j][mp[{j,h[i][j]}]].push_back({st[i].r,st[i].v});
        }
    }
```
- 最后是查询步骤:

```cpp
for(int i=1;i<=m;i++) {
        ll x,ans=0;
        string e;
        cin>>x>>e;
        ll l1=e.length();
        r[0]=e[0];
        for(int j=1;j<l1;j++) {
            r[j]=r[j-1]*p+e[j];
        }
        if(mp[{l1-1,r[l1-1]}]) {
            ll oyt=mp[{l1-1,r[l1-1]}];
            for(auto ed:f[l1-1][oyt]) {
                if(ed.first>x)break;
                ans+=ed.second;
            }
        }
        cout<<ans<<endl;
    }
```
**全代码给出:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define p 131
typedef unsigned long long ull;
const ll N = 1e4+10;
ull h[N][105],t[105],r[105];
ll g[105];
void sync() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
}
struct node {
    ll r,v;
    string s;
}st[N];
bool cmp(node o1,node o2) {
    return o1.r<o2.r;
}
int main () {
    sync();
    ll n,m,dox=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>st[i].r>>st[i].v>>st[i].s;
        ll len = st[i].s.length();
        dox=max(len, dox);
    }
    sort(st+1,st+1+n,cmp);
    for(int i=1;i<=n;i++) {
        ll len=st[i].s.length();
        h[i][0]=st[i].s[0];
        for(int j=1;j<len;j++) {
            h[i][j]=h[i][j-1]*p+st[i].s[j];
        }
    }
    map<pair<ll,ll>,ll>mp;
    vector<vector<vector<pair<ll,ll>>>>f(105, vector<vector<pair<ll,ll>>> (n + 10));
    for(int j=0;j<dox;j++) {
        ll cnt=0;
        for(int i=1;i<=n;i++) {
            if(!mp[{j,h[i][j]}]) {
                mp[{j,h[i][j]}]=++cnt;
            }
            f[j][mp[{j,h[i][j]}]].push_back({st[i].r,st[i].v});
        }
    }
    for(int i=1;i<=m;i++) {
        ll x,ans=0;
        string e;
        cin>>x>>e;
        ll l1=e.length();
        r[0]=e[0];
        for(int j=1;j<l1;j++) {
            r[j]=r[j-1]*p+e[j];
        }
        if(mp[{l1-1,r[l1-1]}]) {
            ll oyt=mp[{l1-1,r[l1-1]}];
            for(auto ed:f[l1-1][oyt]) {
                if(ed.first>x)break;
                ans+=ed.second;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**一维 vector 代码给出:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define p 131
typedef unsigned long long ull;
const ll N = 1e4+10;
ull h[N][105],t[105],r[105];
ll g[105];
void sync() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
}
struct node {
    ll r,v;
    string s;
}st[N];
bool cmp(node o1,node o2) {
    return o1.r<o2.r;
}
int main () {
    sync();
    ll n,m,dox=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>st[i].r>>st[i].v>>st[i].s;
        ll len = st[i].s.length();
        dox=max(len, dox);
    }
    sort(st+1,st+1+n,cmp);
    for(int i=1;i<=n;i++) {
        ll len=st[i].s.length();
        h[i][0]=st[i].s[0];
        for(int j=1;j<len;j++) {
            h[i][j]=h[i][j-1]*p+st[i].s[j];
        }
    }
    map<ll,ll>mp;
    vector<vector<pair<ll,ll>>>f(100*(n+10));
    ll cnt=0;
    for(int j=0;j<dox;j++) {
        for(int i=1;i<=n;i++) {
            if(!mp[h[i][j]]) {
                mp[h[i][j]]=++cnt;
            }
            f[mp[h[i][j]]].push_back({st[i].r,st[i].v});
        }
    }
    for(int i=1;i<=m;i++) {
        ll x,ans=0;
        string e;
        cin>>x>>e;
        ll l1=e.length();
        r[0]=e[0];
        for(int j=1;j<l1;j++) {
            r[j]=r[j-1]*p+e[j];
        }
        if(mp[r[l1-1]]) {
            ll oyt=mp[r[l1-1]];
            for(auto ed:f[oyt]) {
                if(ed.first>x)break;
                ans+=ed.second;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：liguangjun2023 (赞：0)

#### 解题思路
首先，把所有记忆的前缀字符串 $q$ 作为 `map` 结构的 `key`，保存在 `map` 结构中，值为对应的 `vector` 结构保存的多个记忆深度 $r$ 和价值 $v$。
把 `vector` 按照记忆深度 $r$ 排序，并计算对应位置的前缀和 $sm$。
每次查询前缀 $q$ 的时候，通过 `map` 得到对应的`vector`，按照记忆深度二分查找对应的前缀和 $sm$，输出答案即可。
1. 定义 `map < string,vector < int > >` 数据结构，保存记忆前缀 $q$、深度 $r$、价值 $v$、价值前缀和 $sm$。
2. 遍历记忆，统计记忆前缀 $q$、深度 $r$、价值 $v$、价值前缀和 $sm$。
3. 遍历 `map` 的记忆前缀 $q$，按照深度 $r$ 对 `vector` 进行 `sort`。
4. 遍历 `map` 的记忆前缀 $q$，求出不同记忆前缀的前缀和 $sm$。
5. 遍历 $m$ 次查询，二分查找对应的前缀和 $sm$，输出结果。
   

---


```cpp
typedef long long ll;
struct node{
	int r,v;
	ll sm;
};
map<string,vector<node>> mp;
bool cmp(node x, node y){
	return x.r<y.r;
}

int main(){
	int n,m;
	cin>>n>>m;
	//遍历 n 个记忆字符串，统计前缀 q 的 r 和 v，sm 初始化为 0
	for(int i=1;i<=n;i++){
		int r,v;
		string s;
		cin>>r>>v>>s;
		for(int j=1;j<=s.size();j++){
			string ts=s.substr(0,j);
			mp[ts].push_back({r,v,0});
		}
	}
	//对每个前缀字符串，按照深度排序，为前缀和做准备
	for(auto it=mp.begin();it!=mp.end();it++){
		sort(mp[it->first].begin(),mp[it->first].end(),cmp);
	}
	//计算每个前缀字符串的前缀和
	for(auto it=mp.begin();it!=mp.end();it++){
		for(int i=0;i<mp[it->first].size();i++){
			if(i>0)
				mp[it->first][i].sm=mp[it->first][i-1].sm+mp[it->first][i].v;
			else
				mp[it->first][i].sm=mp[it->first][i].v;
		}
	}
	//遍历每次问询，找到前缀字符的 vector，二分查询结果。
	for(int i=1;i<=m;i++){
		int d;
		string q;
		cin>>d>>q;
		vector<node> vc=mp[q];
		node nd={d,0,0};
		auto it=upper_bound(vc.begin(),vc.end(),nd,cmp);
		if(it!=vc.begin())
			cout<<(--it)->sm<<endl;
		else
			cout<<"0"<<endl;
	}

	return 0;
}
```

---

## 作者：naught (赞：0)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18608767)

# （A）[EPXLQ2024 fall round] 风吹起了从前

## 题意

给定 $n$ 个字符串 $a_1$ 到 $a_n$。第 $i$ 个字符串拥有一个深度值 $r_i$，有一个价值 $v_i$。

再给你 $m$ 次询问，每次给出一个字符串 $t$ 和深度 $d$，求以 $t$ 为前缀且深度值小于 $d$ 的字符串价值之和。

## Soluion

显然要使用字典树来处理，这道题可持久化字典树可以实现，但未免有点小题大做，本题解用普通字典树来实现。

首先思考，若每次询问的 $d$ 单调不降该如何处理。

显然，先将字符串 $a$ 按 $r$ 从小到大排序，使用一个指针 $pos$ 表示当前把几个字符串放入了字典树中。对于每次询问，不断将字符串放入字典树（在代码中即 `++pos`）直到 $a_{pos} > d$，然后求值即可。

那么，$d$ 不是单调不降的该怎么办呢？

因为本题不强制在线，所以直接将询问离线下来，排序使得 $d$ 不降即可。

其他疑问见代码。

## 代码

```cpp
//written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 20005
#define Maxm 200005
#define Maxlen 105
#define fo(i, l, r) for (int i = l; i <= r; ++i)

struct A
{
    int r, val/*, id*/;
    char s[Maxlen];
}a[Maxn];

struct Query
{
    int div, id;
    char s[Maxlen];
}q[Maxm];

struct Trie
{
    int son[30];
    ll sum;
}t[Maxn*Maxlen];

int cnt = 1;
int n, m, pos = 1;
ll ans[Maxm];

void Insert(char *s, int val)
{
    int p = 0, len = strlen(s);
    fo(i, 0, len-1)
    {
        int ch = s[i]-'a';
        if(t[p].son[ch] == 0) t[p].son[ch] = cnt++;
        p = t[p].son[ch];
        t[p].sum += val;
    }
}

ll find(char *s)
{
    int p = 0, len = strlen(s);
    fo(i, 0, len-1)
    {
        int ch = s[i]-'a';
        if(t[p].son[ch] == 0) return 0;
        p = t[p].son[ch];
    }
    return t[p].sum;
}


signed main()
{
    scanf("%d%d", &n, &m);

    fo(i, 1, n) scanf("%d%d%s", &a[i].r, &a[i].val, a[i].s);
    sort(a+1, a+n+1, [](A x, A y) {return x.r < y.r;});

    fo(i, 1, m) scanf("%d%s", &q[i].div, q[i].s), q[i].id = i;
    sort(q+1, q+m+1, [](Query x, Query y) {return x.div < y.div;});

    fo(i, 1, m)
    {
        while(pos <= n && a[pos].r <= q[i].div) Insert(a[pos].s, a[pos].val), ++pos;
        ans[q[i].id] = find(q[i].s); 
    }

    fo(i, 1, m) printf("%lld\n", ans[i]);
    
    return 0;
}
```

## Tips

$100 \times 10^9$ 会爆 `int`，记得开`long long`。

---

