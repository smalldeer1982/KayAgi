# [ARC038C] 茶碗と豆

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc038/tasks/arc038_c

$ N $ 個の大きな茶碗が横 $ 1 $ 列に並んでいます。左から $ i\ (0\ ≦\ i\ ≦\ N-1) $ 番目の茶碗を茶碗 $ i $ と呼ぶことにします。茶碗 $ i\ (1\ ≦\ i\ ≦\ N-1) $ には整数 $ C_i $ が書かれており、中には $ A_i $ 個の豆が入っています。茶碗 $ 0 $ には整数は書かれておらず、豆も入っていません。ゲーム好きな兄妹がこれらの茶碗と豆を使って以下のようなゲームをしようとしています。

- プレイヤーは自分のターンに、茶碗 $ 0 $ 以外の茶碗に入っている豆 $ 1 $ つ選んで取り出す。
- 茶碗 $ i $ から豆を取り出したときは、茶碗 $ i\ -\ C_i $, 茶碗 $ i\ -\ C_i\ +\ 1 $, ..., 茶碗 $ i-1 $ のいずれかの茶碗に豆を入れなければならない。
- 交互にターンを繰り返し、自分のターンに選べる豆がなくなったプレイヤーの負けとなる（もう一方のプレイヤーが勝ちとなる）。

$ 2 $ 人ともが勝ちを目指して最適な戦略をとったとき、先手と後手のどちらが勝つでしょうか？

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 100 $ かつ $ A_i\ ≦\ 10 $ を満たすデータセット $ 1 $ に正解した場合は、$ 80 $ 点が与えられる。
- $ N\ ≦\ 100 $ を満たすデータセット $ 2 $ に正解した場合は、上記とは別に $ 20 $ 点が与えられる。
- 全てのテストケースに正解した場合は、上記とは別に $ 4 $ 点が与えられる。

### Sample Explanation 1

ゲームは、例えば以下のように進行します。 - $ 1 $ ターン目：先手が茶碗 $ 2 $ の豆を選んで取り出し、茶碗 $ 1 $ に豆を入れる - $ 2 $ ターン目：後手が茶碗 $ 1 $ の豆を選んで取り出し、茶碗 $ 0 $ に豆を入れる - $ 3 $ ターン目：豆を選ぶことができないため、先手の負けとなる この例の場合、各プレイヤーの行動の選択肢はどのターンにも $ 1 $ つしかないため必ずこのような結果となります。

### Sample Explanation 2

ゲームは、例えば以下のように進行します。 - $ 1 $ ターン目：先手が茶碗 $ 5 $ の豆を選んで取り出し、茶碗 $ 4 $ に豆を入れる - $ 2 $ ターン目：後手が茶碗 $ 4 $ の豆を選んで取り出し、茶碗 $ 2 $ に豆を入れる - $ 3 $ ターン目：先手が茶碗 $ 2 $ の豆を選んで取り出し、茶碗 $ 1 $ に豆を入れる - $ 4 $ ターン目：後手が茶碗 $ 1 $ の豆を $ 1 $ つ選んで取り出し、茶碗 $ 0 $ に豆を入れる - $ 5 $ ターン目：先手が茶碗 $ 1 $ の豆を選んで取り出し、茶碗 $ 0 $ に豆を入れる - $ 6 $ ターン目：豆を選ぶことができないため、後手の負けとなる その他の進行でも、後手がどのような行動をとっても先手が適切な行動をとることによって勝つことができます。

## 样例 #1

### 输入

```
3
1 0
1 1```

### 输出

```
Second```

## 样例 #2

### 输入

```
7
1 1
2 0
1 0
2 0
4 1
3 0```

### 输出

```
First```

## 样例 #3

### 输入

```
7
1 1
2 0
1 9
2 10
4 3
3 5```

### 输出

```
Second```

# 题解

## 作者：ifffer_2137 (赞：1)

完了完了怎么一眼不会 polylog。
### 题意
两个人 有 $n$ 个碗，每个里 $a_i$ 个球，第 $i$ 个碗里的可以扔到 $[i-c_i,i)$ 的碗里，每次扔一个，不能操作者负，问赢家。
### 分析
发现是 Nim，于是考虑 SG 函数，容易发现把 $a_i$ 为奇数的 SG 函数全部 xor 起来就行了。

于是变成末尾追加区间 mex，然后我忘记扫描线了。

直接分块，考虑维护每个块左端点为起点的桶，这样每次求出一个值后修改的代价是 $O(\sqrt n)$ 的。扫过去的时候查询只要额外插入 $O(\sqrt n)$ 个数，然后再对桶值域分块，暴力跳 mex 即可做到 $O(n\sqrt n)$。

### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){if(y<x)return x=y,1;return 0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){if(y>x)return x=y,1;return 0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=1e5+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e5;
constexpr int B=320;
constexpr int H=18;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x-y<0)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int col[maxn],L[B],R[B];
int n,ans;
int c[maxn],a[maxn];
class Bin{
private:
	int bcnt[maxn],gcnt[B];
public:
	void add(int x){if(!bcnt[x])gcnt[col[x]]++;bcnt[x]++;}
	void del(int x){bcnt[x]--;if(!bcnt[x])gcnt[col[x]]--;}
	int mex(){int x;for(x=1;gcnt[x]==R[x]-L[x]+1;x++);for(x=L[x];bcnt[x];x++);return x;}
}bin[B];
int sg[maxn];
void Init(){
	for(int i=0;i<=V;i++){
		col[i]=i/B+1;
		if(col[i]>1&&!L[col[i]]) L[col[i]]=i;
		R[col[i]]=i;
	}
	L[col[V]+1]=V+1;
}
void Clear(){}
void Mymain(){
	Clear();
	n=read();
	for(int i=1;i<n;i++) c[i]=read(),a[i]=read();
	bin[1].add(0);
	for(int i=1;i<n;i++){
		int l=i-c[i],x=col[l]+1,r=min(L[x],i);
		for(int j=l;j<r;j++) bin[x].add(sg[j]);
		sg[i]=bin[x].mex();
		if(a[i]&1) ans^=sg[i];
		for(int j=l;j<r;j++) bin[x].del(sg[j]);
		for(int j=1;L[j]<=i;j++) bin[j].add(sg[i]);
	}
	cout<<(ans?"First\n":"Second\n");
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：wgyhm (赞：0)

## Description

https://www.luogu.com.cn/problem/AT_arc038_c

## Solution

首先观察到每个豆是独立的，这启发我们算出每个位置的 sg 值然后异或起来即可。

现在要做的操作是单点加入值，后缀区间求 mex。

一种解法是使用 P4137，另一篇题解有说。

还有一个很蠢又劣的线段树维护对顶堆做法，区间加入一个数表示这个数在这个区间中没有，堆相当于标记永久化。因为 mex 是单调递减的，查询时单点查询即可。复杂度是很劣的 $O(n\log ^2n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 100004
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
ll power(ll x,int y=mod-2,int p=mod) {
	ll sum=1;x%=p;
	while (y) {
		if (y&1) sum=sum*x%p;
		x=x*x%p;y>>=1;
	}
	return sum;
}
int n,a[maxn],c[maxn];
int las[maxn],ans,sg[maxn];
const int inf=1e9;
priority_queue<int,vector<int> ,greater<int> >q1[maxn<<2],q2[maxn<<2];
int f[maxn<<2];
void Update(int l,int r,int rt,int head,int tail,int k,int flag) {
	if (head<=l&&r<=tail) {
		if (flag==1) {
			q1[rt].push(k);
		}
		else {
			q2[rt].push(k);
		}
		while (!q1[rt].empty()&&!q2[rt].empty()&&q1[rt].top()==q2[rt].top()) q1[rt].pop(),q2[rt].pop(); 
		if (l!=r) f[rt]=min(f[rt<<1],f[rt<<1|1]);else f[rt]=inf;
		f[rt]=min(f[rt],!q1[rt].empty()?q1[rt].top():inf);
		return ;
	}
	int mid=l+r>>1;
	if (head<=mid) Update(l,mid,rt<<1,head,tail,k,flag);
	if (tail>mid) Update(mid+1,r,rt<<1|1,head,tail,k,flag);
	if (l!=r) f[rt]=min(f[rt<<1],f[rt<<1|1]);else f[rt]=inf;
	f[rt]=min(f[rt],!q1[rt].empty()?q1[rt].top():inf);
}
int Query(int l,int r,int rt,int head,int tail) {
	if (head<=l&&r<=tail) return f[rt];
	int mid=l+r>>1,tmp1=inf,tmp2=inf,tmp;
	if (head<=mid) tmp1=Query(l,mid,rt<<1,head,tail);
	if (tail>mid)  tmp2=Query(mid+1,r,rt<<1|1,head,tail);
	tmp=min(min(tmp1,tmp2),!q1[rt].empty()?q1[rt].top():inf);
	// gdb(l,r,rt,head,tail,tmp,tmp1,tmp2);
	return tmp;
}
signed main(void){
	int i;
	read(n);
	memset(f,0x3f,sizeof(f));
	for (i=1;i<=n+1;i++) Update(0,n,1,0,n,i,1),las[i]=-1;
	Update(0,n,1,1,n,0,1);las[0]=0;
	for (i=1;i<n;i++) {
		read(c[i]);read(a[i]);
		sg[i]=Query(0,n,1,i-c[i],i-c[i]);
		Update(0,n,1,las[sg[i]]+1,n,sg[i],0);
		Update(0,n,1,i+1,n,sg[i],1);
		las[sg[i]]=i;
		if (a[i]&1) ans^=sg[i];
		// gdb(i,sg[i],las[sg[i]]);
	}
	puts(ans?"First":"Second");
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

## 作者：Phobia (赞：0)

首先注意到这是一个有向无环图博弈游戏，每个点的 $SG$ 值就是不包含它的前缀的一段后缀的 $\operatorname{mex}$ 值，然后你发现这个东西很像 [P4137](https://www.luogu.com.cn/problem/P4137)，直接套过来就可以了。

时间复杂度 $\Theta(n\log n)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 100005;

int n, ans, minn[maxn * 4];

int read()
{
	int res = 0, f = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		f = (ch == '-');
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return f ? -res : res;
}

void modify(int root, int l, int r, int x, int v)
{
    if (l == r)
    {
        minn[root] = v;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid)
        modify(root << 1, l, mid, x, v);
    if (mid < x)
        modify(root << 1 | 1, mid + 1, r, x, v);
    minn[root] = min(minn[root << 1], minn[root << 1 | 1]);
}

int query(int root, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = l + r >> 1;
    if (minn[root << 1] < k)
        return query(root << 1, l, mid, k);
    return query(root << 1 | 1, mid + 1, r, k);
}

int main()
{
	n = read();
	memset(minn, -1, sizeof(minn));
	modify(1, 0, n, 0, 0);
	for (int i = 1; i < n; ++i)
	{
		int c = read(), a = read();
		int sg = query(1, 0, n, i - c);
		modify(1, 0, n, sg, i);
		if (a & 1)
			ans ^= sg;
	}
	puts(ans ? "First" : "Second");
	return 0;
}
~~~

---

