# [ABC403E] Forbidden Prefix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_e

现有两个字符串多重集合 $X$ 和 $Y$，初始时均为空集合。

需要依次处理 $Q$ 个查询。第 $i$ 个查询给出整数 $T_i$ 和字符串 $S_i$：
- 若 $T_i=1$，则将 $S_i$ 加入 $X$；
- 若 $T_i=2$，则将 $S_i$ 加入 $Y$。

在每个查询处理完成后，请输出以下值：
- $Y$ 中满足"不以 $X$ 中任何字符串作为前缀"的字符串数量。

## 说明/提示

### 约束条件

- $Q$ 是 $1$ 到 $2 \times 10^5$ 之间的整数
- $T_i \in \{1,2\}$
- $S_i$ 是长度在 $1$ 到 $5 \times 10^5$ 之间的小写字母字符串
- $\displaystyle \sum_{i=1}^Q |S_i| \leq 5 \times 10^5$

### 样例解释 #1

各查询处理后的结果如下：
- $i=1$：$Y$ 为空集，答案为 $0$
- $i=2$：`watcoder` 不以 $X$ 中的 `at` 为前缀，答案为 $1$
- $i=3$：`watcoder` 仍满足条件，而 `atcoder` 以 `at` 为前缀，答案为 $1$
- $i=4$：`watcoder` 以新增的 `wa` 为前缀，`atcoder` 以 `at` 为前缀，答案为 $0$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1 at
2 watcoder
2 atcoder
1 wa```

### 输出

```
0
1
1
0```

## 样例 #2

### 输入

```
10
1 w
1 avko
2 atcoder
1 bzginn
2 beginner
1 atco
2 contest
1 ntxcdg
1 atc
1 contest```

### 输出

```
0
0
1
1
2
1
2
2
2
1```

# 题解

## 作者：_xguagua_Firefly_ (赞：7)

赛时教练说 G 题可以做一下，做完没时间了就没看 E。

### 分析

只维护前缀，明显 Trie 树。

Trie 树上每个节点维护这个节点的权值以及以这个节点为根的子树和。

插入第一种字符串的时候，由于字符串结尾的节点的子树内的所有字符串都是以这个字符串为前缀的，都不计入贡献，所以我们清空字符串结尾的节点的权值并且打个标记表示这个子树的权值不计入答案。

插入第二种的时候我们直接把字符串结尾的节点的权值加上 $1$。

修改用 DFS 实现，在回溯的时候 pushup 维护子树和，每次输出根节点的权值和。

### Code

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 5e5 + 5;
struct ARIS
{
    int son[26],clear,val;
    int sum;
}tree[MAXN];
int n,opt,cnt,root;
string S;
inline void pushup(int rt)
{
    tree[rt].sum = tree[rt].val;
    for(int i = 0;i < 26;i++)
        tree[rt].sum += tree[tree[rt].son[i]].sum;
    if(tree[rt].clear)
        tree[rt].sum = 0;
}
inline void modify(int &rt,int pos,int val)
{
    if(!rt)
        rt = ++cnt;
    if(pos == S.length())
    {
        if(val)
            ++tree[rt].val;
        else
            tree[rt].val = 0,tree[rt].clear = 1;
        pushup(rt);
        return ;
    }
    modify(tree[rt].son[S[pos] - 'a'],pos + 1,val);
    pushup(rt);
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    while(n--)
    {
        cin >> opt >> S;
        modify(root,0,opt - 1);
        cout << tree[root].sum << "\n";
    }
}
```

---

## 作者：Roy_2010 (赞：4)

# AT_abc403_e 题解
标解好像是字典树，但为什么不用又好写又好调的哈希呢？
## 思路
实际上就是对 $Y$ 集合中每个字符串的所有前缀，求 $X$ 集合是否有相等字符串。\
那么需要判相等自然就想到哈希了。

思考维护方式，题目要求我们支持以下操作：
1. 加一个字符串到 $X$。
2. 加一个字符串到 $Y$。

因为只有添加字符串的操作，所以我们对这个操作翻译一下，令新字符串为 $S$：
1. 标记 $Y$ 集合中有 $S$ 这一前缀的字符串。
2. 查找 $X$ 集合中是否有 $S$ 的任一前缀，有就标记 $S$，没有就不标记。

操作一，我们可以使用一个 map，将某一前缀的哈希值映射到有这一前缀的 $Y$ 集合中的字符串。同时标记后立刻清空，防止反复标记拉高复杂度。\
操作二，开一个 set 维护 $X$ 集合中的所有字符串的哈希值。

说起来太抽象了，看不懂的话看代码会好许多。
## Code
代码采用双哈希实现。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N (500000)
#define M (200000)
#define pli pair<ll, int>
#define M1 (999999937)
#define M2 (999999929)
#define B1 (19491001)
#define B2 (13331)

int Q, n;
char s[N + 5];

int ans = 0;
bool vis[M + 5];
set<ll> st;
map<ll, vector<int> > mp;

int main() {
	scanf("%d", &Q);
	for (int i = 1, op; i <= Q; ++i) {
		scanf("%d%s", &op, s + 1);
		n = strlen(s + 1);
		if (op == 1) {
			int res1 = 0, res2 = 0; ll h;
			for (int j = 1; j <= n; ++j) {
				res1 = (1ll * res1 * B1 % M1 + s[j]) % M1;
				res2 = (1ll * res2 * B2 % M2 + s[j]) % M2;
			}
			h = ((1ll * res1) << 31) | res2;
			if (mp.count(h) && !mp[h].empty()) {
				vector<int> &vec = mp[h];
				while (!vec.empty()) {
					if (!vis[vec.back()]) {
						vis[vec.back()] = 1;
						--ans;
					}
					vec.pop_back();
				}
			}
			st.insert(h);
		}
		else {
			int res1 = 0, res2 = 0; ll h; bool flg = 1;
			for (int j = 1; j <= n; ++j) {
				res1 = (1ll * res1 * B1 % M1 + s[j]) % M1;
				res2 = (1ll * res2 * B2 % M2 + s[j]) % M2;
				h = ((1ll * res1) << 31) | res2;
				if (st.count(h)) {
					flg = 0;
					vis[i] = 1;
				}
				mp[h].push_back(i);
			}
			if (flg) {
				++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

```
由于前缀总数等于字符串总长，每个前缀最多被访问一次，令 $N = \sum |S|$，所以复杂度为 $O(N \log N)$。

---

## 作者：gcx114514 (赞：4)

我们考虑对集合 $Y$ 中的元素计算它在哪些区间会有贡献。那么一个元素有贡献的区间的右端点是其某个前缀在 $X$ 中出现的最早时间。

我们将询问离线，将每个加入 $X$ 的元素记录出现时间最小的（这里可以使用哈希维护）。

然后对于每个在 $Y$ 中的元素（假设其出现时间为 $l$），我们枚举它的前缀，取它所有前缀在 $X$ 中出现最小的时间 $r$。那么在 $[l,r)$ 中每个位置都会产生贡献。（注意特判 $r<l$ 的情况。） 

这样时间复杂度是 $O(\sum\limits_{i=1}^Q|S_i|\log\sum|S_i|)$ 的，可以通过。

（建议使用双模哈希，考场上我写的单模被卡了。）

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define ll long long
#define mk make_pair
#define se second
#define fi first
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}


template <int mod>
struct modint{

	int val;

	static int norm(const int &x){return x<0?x+mod:x;}
	static int Norm(const int &x){return x>=mod?x%mod:x;}

	modint inv()const{
		int a=val,b=mod,u=1,v=0,t;
		while(b>0)t=a/b,swap(a-=t*b,b),swap(u-=t*v,v);
		return modint(u);
	}


	modint():val(0){}
	modint(const int &m):val(norm(m)){}
	modint(const long long &m):val(norm(m%mod)){}
	modint operator -()const{return modint(norm(-val));}
	bool operator ==(const modint &x){return val==x.val;}
	bool operator !=(const modint &x){return val!=x.val;}
	bool operator <=(const modint &x){return val<=x.val;}
	bool operator >=(const modint &x){return val>=x.val;}
	bool operator >(const modint &x)const{return val>x.val;}
	bool operator <(const modint &x)const{return val<x.val;}
	modint& operator *=(const modint &x){return val=static_cast<int>(1ll*val*x.val%mod),*this;}
	modint& operator <<=(const modint &x){return val=(1ll*val<<x.val)%mod,*this;}
	modint& operator +=(const modint &x){return val=Norm(1ll*val+x.val),*this;}
	modint& operator -=(const modint &x){return val=norm(1ll*val-x.val),*this;}
	modint& operator >>=(const modint &x){return val>>=x.val,*this;}
	modint& operator ^=(const modint &x){return val^=x.val,*this;}
	modint operator >>(const modint &x){return modint(*this)>>=x;}
	modint operator <<(const modint &x){return modint(*this)<<=x;}
	modint& operator /=(const modint &x){return *this*=x.inv();}
	modint operator +(const modint &x){return modint(*this)+=x;}
	modint operator -(const modint &x){return modint(*this)-=x;}
	modint operator *(const modint &x){return modint(*this)*=x;}
	modint operator /(const modint &x){return modint(*this)/=x;}
	modint operator ^(const modint &x){return modint(*this)^=x;}
	friend std::ostream& operator<<(std::ostream& os,const modint &a){return os<<a.val;}
	friend std::istream& operator>>(std::istream& is,modint &a){return is>>a.val;}
};

typedef modint<1000000007>m17;
typedef modint<998244353>m98;

m17 Bas1=97;
m98 Bas2=83;


map<pii,int>m;
int sum[Max];

struct Que{
	int opt;string s;
}b[Max];


pii get(string s){
	int len=s.size();
	m17 Ans1=0;m98 Ans2=0;
	for(int i=0;i<len;++i){
		Ans1=Ans1*Bas1+(s[i]-'a'+1);
		Ans2=Ans2*Bas2+(s[i]-'a'+1);
	}
	return mk(Ans1.val,Ans2.val);
}



bool Med;
signed main(){
	int q=read();
	for(int i=1;i<=q;++i){
		cin>>b[i].opt>>b[i].s;
		if(b[i].opt==1)	{
			pii Res=get(b[i].s);
			if(m.find(Res)==m.end())m[Res]=i;
		}
	}
	
	for(int i=1;i<=q;++i){
		if(b[i].opt==2){
			int len=b[i].s.size();
			int pos=q+1;
			m17 Ans1=0;m98 Ans2=0;
			for(int j=0;j<len;++j){
				Ans1=Ans1*Bas1+(b[i].s[j]-'a'+1); 
				Ans2=Ans2*Bas2+(b[i].s[j]-'a'+1);
				pii Res=mk(Ans1.val,Ans2.val) ;
				if(m.find(Res)!=m.end())pos=min(pos,m[Res]);
			}
			if(pos>=i){
				sum[i]++;sum[pos]--;
			}
		}
	}
	for(int i=1;i<=q;++i){
		sum[i]+=sum[i-1];
		cout << sum[i] << "\n";
	}


	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
```

---

## 作者：aulive (赞：4)

省流：学 DS 学傻了。
## 题意
有 $m$ 次操作。\
每次往集合 $A$ 或集合 $B$ 中加入一个字符串 $S$。\
每次插入完后查询 $B$ 中没有 $A$ 中元素作为前缀的字符串数。
$\sum |S| \le 5\times 10^5$。
## solution
看到前缀匹配，不难想到字典树。\
先离线下来建出字典树。\
如果插入到集合 $B$ 中，就是树上单点加。\
如果插入到集合 $A$ 中，就是给子树标号，也就是这一子树以后的值一直都只能为 $0$。\
直接把字典树拍到 DFS 序上维护子树信息即可。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO {//我向众神祈祷，回应我的只有心跳
#define IOsiz 100000
	char ibuf[IOsiz], obuf[IOsiz], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOsiz,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOsiz)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
#define int long long
const int maxn=1e6;
struct node{
	int ch[26];
}trie[maxn+5];
int q,pos[maxn+5];
int op[maxn+5],rt,tot,dfn[maxn+5],siz[maxn+5],idx;
string s[maxn+5];
void insert(string &s,int id){
	int now=1;
	for(int i=0;i<s.size();i++){
		int c=s[i]-'a';
		int &v=trie[now].ch[c];
		if(!v)v=++tot;
		now=v;
	}
	pos[id]=now;
}
void dfs(int now){
	siz[now]=1;
	dfn[now]=++idx;
	for(int i=0;i<26;i++){
		int to=trie[now].ch[i];
		if(!to)continue;
		dfs(to);
		siz[now]+=siz[to];
	}
}
struct segmenttree{
	struct node{
		int lef,rig,tag,sum;
	}tree[maxn<<2|1];
	void pushup(int now){
		tree[now].sum=tree[now<<1].sum+tree[now<<1|1].sum;
		if(tree[now].tag)tree[now].sum=0;
	}
	void build(int now,int lef,int rig){
		tree[now].lef=lef,tree[now].rig=rig;
		if(lef==rig)return;
		int mid=lef+rig>>1;
		build(now<<1,lef,mid);
		build(now<<1|1,mid+1,rig);
		pushup(now);
	}
	void modify(int now,int lef,int rig){
		if(lef<=tree[now].lef&&tree[now].rig<=rig)return tree[now].tag=1,tree[now].sum=0,void();
		int mid=tree[now].lef+tree[now].rig>>1;
		if(lef<=mid)modify(now<<1,lef,rig);
		if(mid<rig)modify(now<<1|1,lef,rig);
		pushup(now);
	}
	void update(int now,int to){//注意可能有重复的串
		if(tree[now].tag)return;
		if(tree[now].lef==tree[now].rig)return tree[now].sum=(tree[now].tag?0:tree[now].sum+1),void();
		int mid=tree[now].lef+tree[now].rig>>1;
		if(to<=mid)update(now<<1,to);
		else update(now<<1|1,to);
		pushup(now);
	}
}tr;
signed main(){
	rt=tot=1;
	cin>>q;
	for(int i=1;i<=q;i++)cin>>op[i]>>s[i],insert(s[i],i);
	dfs(rt);
	tr.build(1,1,idx);
	for(int i=1;i<=q;i++){
		int x=pos[i];
		if(op[i]==1){
			tr.modify(1,dfn[x],dfn[x]+siz[x]-1);
		}else{
			tr.update(1,dfn[x]);
		}
		cout<<tr.tree[1].sum<<"\n";
	}
	return 0;
}
```

---

## 作者：xxr___ (赞：3)

首先前缀想到字典树，公共前缀想到哈希。

我们考虑每种操作互相产生的影响。

我们维护一个字典树，存当前**可行的** $B$ 集合中的所有可能的前缀。且维护一个下标集合。

对于 $1$ 操作，我们维护 $s$ 的哈希值。且在 $B$ 集合的字典树上走一走，走到头删一删当前的下标集合。

对于 $2$ 操作，依次遍历每一位，求一求所有前缀哈希值，看看这个值有没有被 $1$ 操作维护过，如果没有，就插到字典树里。

可以开一个 `set` 记录当前所有合法的 $s\in B$ 这样方便删除。

复杂度是 $O(Q\log Q + \sum |S| \log Q)$ 的，但是赛时偷懒，没写回溯删除，但是数据可能比较水也是跑的飞快就没管。

代码：
```cpp
#include<iostream>
#include<cstring>
#include<set>
#include<map>
const int N = 2e5 + 5;
const int mod = 1e9 + 7; 

int q,rt = 0,idx = 0,base = 131;
std::set<int> st;
struct trie{
	int son[26];
	std::set<int> st;
}tr[N * 3];
inline void ins(int x,std::string s){
	rt = 0;
	for(auto & it : s){
		if(tr[rt].son[it - 'a']){
			rt = tr[rt].son[it - 'a'];
		}else{
			tr[rt].son[it - 'a'] = ++ idx;
			rt = tr[rt].son[it - 'a'];
		}
		tr[rt].st.insert(x);
	}
}
inline void del(std::string s){
	rt = 0;
	for(auto & it : s){
		if(tr[rt].son[it - 'a']){
			rt = tr[rt].son[it - 'a'];
		}else{
			return;
		}
	}
	for(auto & it : tr[rt].st){
		if(st.count(it)){
			st.erase(it);
		}
	}
}
std::map<long long,bool> vs,vs2;
int32_t main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cin >> q;
	int cnt = 0;
	while(q --){
		int op;
		std::string s;
		std::cin >> op >> s;
		if(op == 1){
			long long now = 0,now2 = 0;
			base = 1;
			int base2 = 12345;
			for(auto & it : s){
				now = (now * base + it) % mod;
				now2 = (now2 * base2 + it) % mod;
				(base *= 131) %= mod;
				(base2 *= 12345) %= mod;
			}
			vs[now] = 1;
			vs2[now2] = 1;
			if(!st.size()){
				std::cout << 0 << '\n';
				continue;
			}else{
				del(s);
			}
		}else{
			long long now = 0,now2 = 0;
			base = 1;
			int base2 = 12345;
			bool f = 1;
			for(auto & it : s){
				now = (now * base + it) % mod;
				now2 = (now2 * base2 + it) % mod;
				(base *= 131) %= mod;
				(base2 *= 12345) %= mod;
				if(vs[now] && vs2[now2]){
					f = 0;
					break;
				}
			}
			if(f){
//				std::cout << cnt << '\n';
				ins(++ cnt,s);
				st.insert(cnt);
			}else{
				std::cout << st.size() << '\n';
				continue;
			}
		}
		std::cout << st.size() << '\n';
	}
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：2)

有点意思。

定义 $X$ 为题目描述中的集合 $X$，$Y$ 为题目描述中的集合 $Y$。

看到前缀，我们把所有字符串扔到 trie 树上，考虑一个时刻的贡献形式：所有在 $Y$ 中字符串在 trie 树上的终止节点有 $1$ 的贡献，如果路径上经过了在 $X$ 中字符串在 trie 上的终止节点，那么贡献就是 $0$。

然后做法就比较套路了。考虑 $X$ 中加入一个字符串，相当于清空 $X$ 在 trie 上终止节点子树中的值，用线段树维护。在 $Y$ 中加入一个字符串，相当于单点修改一个终止节点的值，但是如果有 $X$ 中字符串终止节点在路径上，贡献就不能计算。换算到线段树上维护就相当于如果递归到叶子节点的路径上曾出现过代表清空子树的懒标记，就不计算贡献。

注意 $Y$ 中出现相同字符串的贡献是累加。

[submission](https://atcoder.jp/contests/abc403/submissions/65282062)

---

## 作者：lyx128 (赞：2)

提供一种**在线**的哈希写法。

考虑双向相互删除的方法，通过此方法~~仿佛~~可以降低一点点复杂度。

思路很简单，维护两个 multiset 分别记录 $X$ 集合的字符串与 $Y$ 集合的所有字符串的前缀。

当然，警示一点：注意 multiset 取值的时候不要越界！！！

代码实现如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5;
const ll base=257;
const ll mod=1e9+7;
int Q;
int T;
int n;
char s[N+5];

multiset<pair<ll,int>> hy;
multiset<ll> hx;
int cnt;
bitset<N+5> vis;
int sum;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>Q;
	while(Q--){
		cin>>T>>(s+1);
		n=strlen(s+1);
		if(T&1){
			ll hash_val=0;
			for(int i=1;i<=n;i++)
				hash_val=(hash_val*base%mod+s[i])%mod;
			hx.insert(hash_val);
			pair<ll,ll> hp=make_pair(hash_val,0);
			auto it=hy.lower_bound(hp);
			while(it!=hy.end()){
				if((*it).first!=hash_val)
					break;
				if(!vis[(*it).second])
					++sum;
				vis[(*it).second]=1;
				auto it2=it;
				++it2;
				hy.erase(it);
				it=it2;
			}
		}
		else{
			++cnt;
			ll hash_val=0;
			for(int i=1;i<=n;i++){
				hash_val=(hash_val*base%mod+s[i])%mod;
				hy.insert({hash_val,cnt});
				if(hx.count(hash_val)){
					vis[cnt]=1;
					++sum;
					break;
				}
			}
		}
		cout<<cnt-sum<<"\n";
	}	
	return 0;
}
```

但是，我估计许多同学通过和我一样数十次的提交和无限久的调试仍然无果，那就是**单哈希**被卡了，呵呵。

---

## 作者：kkxacj (赞：2)

主观最难的题，多浪费了 $25$ 分钟 和 $4$ 罚时，两个少一个都 `perf` $2400$ 了。

#### 思路

看到这个题首先想到字典树吧，反正用字典树方便一点。

考虑对于一棵树，加点的情况。

1. 加一个点到 `X` 集合，就加到字典树，设每个点的经过次数为 $sum_i$，则把对应的点 $x$ 到祖先的每个点和答案都减去 $sum_x$，给 $x$ 这里打上标记，然后 $x$ 子树内的点都需要清零，这个可以之后再来清，具体的是每访问一个点就与祖先点在不计入本次操作加的值取最小值。
2. 加一个点到 `Y` 集合，答案加一，然后从前往后，每一个点都加一，若遇到当前点为标记，就立即结束，并把答案减一，在把对应的点 $x$ 到祖先的每个点和答案都减一。若没遇到就不管。

然后就没了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 1e6+10;
int q,x,v[N][27],sum[N],bj[N],ans,n,cnt,o,o1;
string s;
inline void insert(int x,int y,int z)
{ 
	if(bj[x] && z == 1) 
	{
		ans--,sum[x] = 0,o1 = 1;//已经死了 
		return;
	}
	if(z == 1) sum[x]++;
	if(y > n)
	{ 
		if(z != 1) bj[x] = 1,ans -= sum[x],o1 = sum[x],sum[x] = 0;
		return;
	}
	if(!v[x][s[y]-'a']) v[x][s[y]-'a'] = ++cnt;
	for(int i = 0;i <= 26;i++) sum[v[x][i]] = min(sum[v[x][i]],sum[x]-z);
	insert(v[x][s[y]-'a'],y+1,z);
	sum[x] -= o1;
}
signed main()
{
	read(q); cnt = 1;
	while(q--)
	{
		read(x),cin >> s; n = s.size(); s = ' '+s;
		if(x == 2) o1 = 0,insert(1,1,1),ans++;
		else o1 = 0,insert(1,1,0);
		print(ans),pc('\n');
	}
	flush();
	return 0;
}
/*
动态搞的话不好搞啊
4
2 b
2 ba
1 ba
1 b
*/
```

---

## 作者：ty_mxzhn (赞：2)

嘟嘟嘟。

考虑不使用离线的性质，存储 $Y$ 每个前缀的哈希值计入 $S$。

如果要加入 $X$，那么找到所有 $Y$ 的前缀 $=X$，然后一个个把这些 $Y$ 的前缀从 $S$ 删去。

如果要加入 $Y$，就直接判断每个前缀是否是 $X$。

用 multiset 维护 $S$。

时间复杂度 $O(\sum s\log \sum s)$。

---

## 作者：MaiJingYao666 (赞：1)

# AT_abc403_e [ABC403E] Forbidden Prefix 题解  
赛时做得比 D 题还快，字典树好题。  
### 解题思路  
其实只要考虑插入一个字符串会带来什么影响。如果向 $X$ 中插入一个字符串 $S_i$，那么以 $S_i$ 为前缀的 $Y$ 中的字符串得贡献都会被抹去，包括当前的和以后的。由于作者聪明 ~~（只学过字典树）~~，所以自然可以想到用字典树，时间复杂度为 $O(\sum |S_i|)$。具体操作为：维护每个子树的贡献总和。  
- 当向 $X$ 插入一个字符串时，在该位置打上标记，同时将沿路上的节点的贡献和都减去该节点的子树和。
- 当向 $Y$ 插入一个字符串时，如果整个沿路上没有标记，那么就在沿路的节点上的子树和都加 1。

两种操作都可以用回滚一次覆盖实现，所以自然时间复杂度正确。每一次操作后的答案就是根节点的子树和。  
剩下的就是字典树板子了。  
### AC 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct Trie{
	int ch[26];
	int zt,ans,fa;
}t[N];
int cnt;
int q;
inline void insert(int d,string s){
	int p=0;
	int len=s.size();
	for(int i=0;i<s.size();i++){
		if(t[p].zt==1)return;
		if(t[p].ch[s[i]-'a']) p=t[p].ch[s[i]-'a'];
		else{
			t[p].ch[s[i]-'a']=++cnt;
			t[cnt].fa=p;
			p=cnt;
			t[p].zt=0;
			t[p].ans=0;
		}
	}
//	cout<<p<<endl;
	if(t[p].zt) return;
	if(d==1){
		t[p].zt=1;
		if(t[p].ans!=0){
			int del=t[p].ans;
			t[p].ans=0;
			do{
				p=t[p].fa;
				t[p].ans-=del;
			}while(p!=0);
		}
	}
	else if(d==2){
		t[p].ans++;
		do{
			p=t[p].fa;
			t[p].ans++;
		}while(p!=0);
	}
}
int main(){
	t[0].zt=0;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	for(int i=1;i<=q;i++){
		int opt;
		string s;
		cin>>opt>>s;
		insert(opt,s);
		cout<<t[0].ans<<'\n';
	}
}
```

---

## 作者：include13_fAKe (赞：1)

赛时该切的题，因为 B 花了太久时间调然后这题又再往 hash 上面想没写完。

---

Trie 树板子题。

考虑权值 Trie 树。

考虑只有 $2$ 操作时的维护方法：每一次操作时，在串的尾端打上一个标记，树的每一个节点统计子树上有多少个标记。

然后考虑 $1$ 操作，要求 $2$ 有 $1$ 的前缀时子树答案清零，直接在字符串的末尾对应的节点打个标记就清零了。

每一次查询根节点的答案即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6; 
struct node{
	int tag0,tag1;
	//tag0 表上代表清零其值，tag1 代表本子树的值 
	int son[35];
	int ans; 
}trie[N];
int idx=1;
string s;
int n;
void insert(int now,int now1,int op){
//	cout<<'^'<<endl;
//	cout<<now<<' '<<now1<<' '<<op<<' '<<sonidx<<endl;
	if(now1==n+1){
		trie[now].tag1++;
		if(op==1)	trie[now].tag0=1;
		trie[now].ans=trie[now].tag1;
		for(int i=1;i<=26;i++){
			trie[now].ans+=trie[trie[now].son[i]].ans;
		}
		if(trie[now].tag0)	trie[now].ans=0;
		return;
	}
	int sonidx=s[now1]-'a'+1;
	int nxt;
	if(trie[now].son[sonidx])	nxt=trie[now].son[sonidx];
	else	trie[now].son[sonidx]=++idx,nxt=idx;
//	cout<<now<<' '<<now1<<' '<<op<<' '<<sonidx<<' '<<op<<endl;
	insert(trie[now].son[sonidx],now1+1,op);
	trie[now].ans=trie[now].tag1;
	for(int i=1;i<=26;i++){
		trie[now].ans+=trie[trie[now].son[i]].ans;
	}
	if(trie[now].tag0)	trie[now].ans=0;
}
signed main(){
	int q;
	cin>>q;
	while(q--){
		int op;
		cin>>op;
		cin>>s;
		n=s.size();
		s=' '+s;
		insert(1,1,op);
		cout<<trie[1].ans<<endl;
	}
	cout<<endl;
	return 0;
} //ABC403E1 
```

---

## 作者：Kexi_ (赞：1)

提供一种更加规范的字典树做法。

我们建一颗有关于 $Y$ 集合内字符串的字典树。而 $X$ 集合内的字符串则看作查询。分别处理两种操作，动态维护答案。

操作一，将字符串最后一位的子树全部手动标记为清空状态,同时计算被清空的贡献并减去。

操作二，除了添加字符串的基本操作，我们还要看字符串经过的路径上是否有清空状态的点。如果有就不加他的贡献。

其实这个题的思路是好想的，难点主要在复杂度的证明和这个清空状态的下传。复杂度不会证 qwq，只能说一下这个清空操作的下传了。

其实就是在动态开点的过程中遗传一下父节点的清空状态。然后要记得如果你手动标记清空状态的时候遇到了已经清空的点你就可以停了。这样的话每个点只会标记一次，标记状态的复杂度应该是 $O(\sum \lvert s \rvert)$。

代码是清晰的。


```cpp
#include <bits/stdc++.h>
constexpr int N = 5e5 + 7;
using namespace std;
bool clear[N];
int ans , tot , q , n , trie[N][27] , cnt[N] , sum[N];
char a[N];
static inline int getnum(char c) {
	return c - 'a';
}
static int dfs(int s) {
	if(clear[s]) {
		return 0;
	}
	clear[s] = true;
	int res = cnt[s];
	for(int i(0); i < 26; ++i) {
		if(trie[s][i]) {
			res += dfs(trie[s][i]);
		}
	}
	return res;
}
static inline void Insert1() {
	int p = 0;
	for(int i(0); i < n; ++i) {
		int now = getnum(a[i]);
		if(!trie[p][now]) {
			trie[p][now] = ++ tot;
			clear[trie[p][now]] = clear[p];//遗传父节点的清空状态
		}
		p = trie[p][now];
	}
	if(!clear[p]) {
		ans -= dfs(p);//如果自己这个点还未被清空，要删掉自己子树的贡献
	}
}
static inline void Insert2() {
	int p = 0;
	for(int i(0); i < n; ++i) {
		int now = getnum(a[i]);
		if(!trie[p][now]) {
			trie[p][now] = ++ tot;
			clear[trie[p][now]] = clear[p]; //遗传父节点的清空状态
		}
		p = trie[p][now];
	}
	++ cnt[p];
	if(!clear[p]) {
		++ ans;//如果路径上没有清空状态的点，就加上贡献
	}
}
int main() {
	ios ::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
	cin >> q;
	while(q--) {
		int opt; cin >> opt >> a;
		n = strlen(a);
		switch(opt) {
			case 1 : {Insert1();break;}
			case 2 : {Insert2();break;}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

