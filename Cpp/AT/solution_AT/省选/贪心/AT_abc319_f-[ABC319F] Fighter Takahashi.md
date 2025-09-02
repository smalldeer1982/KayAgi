# [ABC319F] Fighter Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc319/tasks/abc319_f

$ N $ 頂点の木があります。 $ 1 $ 番目の頂点が根であり、$ i $ 番目 $ (2\leq i\leq N) $ の頂点の親は $ p_ i\ (1\leq p _ i\lt\ i) $ です。

根でない頂点には、**敵**か**薬**のどちらか一方が配置されています。 高橋くんは、すべての敵を倒したいです。 はじめ、高橋くんの強さは $ 1 $ で、頂点 $ 1 $ にいます。 $ i=2,\ldots,N $ について、$ i $ 番目の頂点の情報は整数の組 $ (t _ i,s _ i,g _ i) $ を用いて次のように表されます。

- $ t _i=1 $ ならば $ i $ 番目の頂点には敵がいます。この頂点に高橋くんが初めて訪れたとき、高橋くんの強さが $ s _ i $ 未満だった場合高橋くんは敵に倒されて**敗北**し、高橋くんは他の頂点に移動できなくなります。そうでなかった場合、高橋くんは敵を倒し、強さが $ g _ i $ 上昇します。
- $ t _ i=2 $ ならば $ i $ 番目の頂点には薬があります。この頂点に高橋くんが初めて訪れたとき、高橋くんは薬を飲み、強さが $ g _ i $ 倍になります。（薬がある頂点では、$ s _ i=0 $ です。）
 
薬がある頂点はたかだか $ 10 $ 個です。

高橋くんは、隣接する頂点に移動することができます。 高橋くんがすべての敵を倒すことができるか判定してください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 500 $
- $ 1\leq\ p _ i\lt\ i\ (2\leq\ i\leq\ N) $
- $ t _ i\in\lbrace1,2\rbrace\ (2\leq\ i\leq\ N) $
- $ t _ i=1\implies1\leq\ s _ i\leq\ 10 ^ 9\ (2\leq\ i\leq\ N) $
- $ t _ i=2\implies\ s _ i=0\ (2\leq\ i\leq\ N) $
- $ 1\leq g _ i\leq\ 10 ^ 9\ (2\leq\ i\leq\ N) $
- $ t _ i=2 $ である頂点は $ 10 $ 個以下
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、木は以下のようになっています。 ![](https://img.atcoder.jp/abc319/df876b93cd1181b6e7269d978c19632b.png) 高橋くんは、頂点 $ 1 $ から $ 2,3,2,1,6,7,6,1,4,5,8 $ の順に移動することで、すべての敵を倒すことができます。 このとき、高橋くんがいる頂点と高橋くんの強さは以下の図のように変化します（図では、すでに訪れたことのある頂点への移動は省略しています）。 ![](https://img.atcoder.jp/abc319/de96b59f8e4b180017fbd1aba73f4fb3.png) 例えば、頂点 $ 1 $ から $ 4,5,8 $ の順に移動すると、頂点 $ 8 $ に訪れた時点での強さが $ s _ 8=140 $ より小さいので高橋くんは敗北してしまい、すべての敵を倒すことができません。

## 样例 #1

### 输入

```
8
1 2 0 3
2 1 3 3
1 2 0 4
4 1 2 2
1 2 0 5
6 1 5 5
5 1 140 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
12
1 1 166 619
1 1 17 592
2 1 222 983
2 1 729 338
5 1 747 62
3 1 452 815
3 2 0 1
4 2 0 40
4 1 306 520
6 1 317 591
1 1 507 946```

### 输出

```
No```

## 样例 #3

### 输入

```
12
1 1 1 791
2 2 0 410
2 1 724 790
2 1 828 599
5 2 0 13
3 1 550 803
1 1 802 506
5 1 261 587
6 1 663 329
8 1 11 955
9 1 148 917```

### 输出

```
Yes```

## 样例 #4

### 输入

```
12
1 2 0 1000000000
2 2 0 1000000000
3 2 0 1000000000
4 2 0 1000000000
5 2 0 1000000000
6 2 0 1000000000
7 2 0 1000000000
8 2 0 1000000000
9 2 0 1000000000
10 2 0 1000000000
11 1 1 1```

### 输出

```
Yes```

# 题解

## 作者：吴思诚 (赞：21)

与其他题解截然不同的思路。

发现如果确定了吃药顺序，那么只要可以打一只怪兽一定打（因为先加后乘优于先乘后加），不可以打了，依次吃枚举顺序的药。复杂度 $O(m!n\log n)$。

可能会超时，所以我们考虑随机化其中几个排列，然后计算，若存在合法的方式，那么就 `Yes`，否则就 `No`。

注意到可以使用 C++ 的 `chrono` 头文件提供的方式或者 C 的 `clock()` 进行卡时（我卡到 `1900ms`），可能会 `WA`，多交几发就好。

[代码](https://atcoder.jp/contests/abc319/submissions/45484737)（注意多交几次！）

---

## 作者：封禁用户 (赞：13)

## 思路

看完题目，有一个显然的结论：

- 能加先加，不能加再吃药。

因为先加再乘得到的值肯定比先乘再加的值要大。

然后，我们注意到一个关键信息：

- 只有最多 $10$ 个顶点有药。

这个条件再结合题目让我们想到状压 dp。

接下来设计状态：$S$ 表示吃过药的集合，那么 $dp[S]$ 就表示吃了 $S$ 中的药力量最多能到达多少。

转移时选择一个集合中的药来转移。每次转移先看转移状态能否到达当前状态，也就是能否吃到当前选择转移的药，然后再吃掉这个药，再把能加的敌人加上，最后取个 $\max$ 就可以了。

然后如何判断能不能加，因为先加后加是有区别的。首先我们开一个优先队列，存放一个敌人的 $s$ 值（当然如果是药就是 $0$）。然后我们把最小的 $s$ 拿出来，看当前的力量值是不是大于 $s$，如果是，那么把他的儿子入队，如果不是，说明后面的都不行了，直接 `break`。

最后判断吃完所有药的力量值是否大于等于所有敌人。

细节在代码中有注释。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int rd(int x=0,char c=getchar()){int f=1;while(!isdigit(c))f=(c^'-'?1:-1),c=getchar();while(isdigit(c))x=x*10+(c^48),c=getchar();return x*f;}
const int N=505;
using ll=long long;
int n,f[N];
vector<int> E[N];
int t[N];
ll s[N],g[N];
int tot,id[N],pos[N];//id[i]表示第i个药的编号，pos[i]表示i是第几个药
ll dp[1<<10];
bitset<N> vis[1<<10];//记录哪些是已经用过的
signed main(){
	n=rd();
	for(int i=2;i<=n;i++){
		f[i]=rd();
		E[f[i]].push_back(i);
		t[i]=rd(),s[i]=rd(),g[i]=rd();
		if(t[i]==2)id[++tot]=i,pos[i]=tot;
	}
	// for(int i=1;i<=n;i++)cerr<<f[i]<<" "<<i<<endl;
	// for(int i=1;i<=tot;i++)cerr<<id[i]<<endl;
	using PII=pair<ll,int>;
	priority_queue<PII,vector<PII>,greater<PII> > q;//优先队列，第一个值代表s,第二个代表编号。
	ll now=1;
   //给dp[0]初始化
	for(int v:E[1])if(t[v]==1)q.push({s[v],v});//是敌人就入队。
	while(q.size()){
		int u=q.top().second;q.pop();
		if(now<s[u])break;//如果不行直接break
		now+=g[u];vis[0][u-1]=1;
		for(int v:E[u])if(t[v]==1){
			q.push({s[v],v});
		}
	}dp[0]=now;
	queue<int> Q;
	bitset<N> sp;
	if(now>=1e9){puts("Yes");return 0;}//因为s最大1e9，只要超过就说明一定可以。
	for(int i=1;i<(1<<tot);i++){
		dp[i]=-1e9;
		for(int j=0;j<tot;j++){
			if((i>>j)%2==0)continue;
			if(dp[i^(1<<j)]<0)continue;
			ll tmp=dp[i^(1<<j)]*g[id[j+1]];
			sp.reset();
			Q.push(1);
			int f=0;
		//判断转移状态能不能吃到第j+1个药
			while(Q.size()){
				int u=Q.front();Q.pop();
				for(int v:E[u]){
					if(v==id[j+1])f=1;
					if(vis[i^(1<<j)][v-1])Q.push(v);
				}
			}if(!f)continue;
			while(q.size())q.pop();
			for(int v:E[1])if(t[v]==1){
				if(vis[i^(1<<j)][v-1])//之前走到过了s就是0了。
				q.push({0,v});
				else
				q.push({s[v],v});
			}else if((i>>(pos[v]-1))&1){//注意只能走吃过的药。
				q.push({0,v});
			}
			while(q.size()){
				ll sb=q.top().first;
				int u=q.top().second;q.pop();
				if(tmp<sb)break;
				sp[u-1]=1;//标记走过了。
				if(!vis[i^(1<<j)][u-1]&&t[u]==1)tmp+=g[u];//只能加之前没吃过的敌人。
				for(int v:E[u])if(t[v]==1){
					if(!vis[i^(1<<j)][v-1])
					q.push({s[v],v});
					else
					q.push({0,v});
				}else if((i>>(pos[v]-1))&1){
					q.push({0,v});
				}
			}
			if(tmp>dp[i])
			dp[i]=tmp,vis[i]=sp;
			if(dp[i]>=1e9){
				puts("Yes");
				return 0;
			}
		}
	}
	ll ans=dp[(1<<tot)-1];
	// cerr<<ans<<endl;
	for(int i=1;i<=n;i++)if(t[i]==1)if(ans<s[i]){//判断是不是大于等于所有敌人。
		puts("No");
		return 0;
	}puts("Yes");
	return 0;
}
```

---

## 作者：zhongpeilin (赞：11)

## 题目大意：
高桥来刷怪了，有 $N$ 个节点，构成了一棵树。除 `1` 以外，每个节点上有药水或怪，且有 $t_{i}, s_{i}, g_{i}$ 三个值。  
若 $t_{i} = 1$，这里是一个怪，如果高桥到这里的之后能力不小于 $s_{i}$，就可以增加 $g_{i}$。否则就被打败。  
若 $t_{i} = 2$，这里是一个药水，$s_{i}=0$，如果高桥到这里的话能力就可以 $ \times g_{i}$。  
每个怪或者药水只能干一次。

## 解题思路：
首先贪心的想，一定是先尽量刷怪，然后喝药水，因为这样能保证之前加上的怪的值一定能乘以一个 $g_{i}$，又因为 $1 \le g_{i}$，所以让尽可能多的怪的 $s_{i}$ 乘上 $g_{i}$。  
因为药水只能用一次，所以每个药水无论如何都可以表示成 `0` 或 `1`，而药水数 $ \le 10$，那么可以用 $dp_{i}$ 表示药水编号拿的情况为 $i$ 的且不拿其他药水的最大力量。其中 $i$ 是一个二进制压缩数。  
问题来了，我们假设现在可以到达 $ID_{1}, ID_{2} \dots ID_{cnt}$ 这些点，但是不保证他们上面的怪物现在可以战胜，这里怎么处理？  
其实不难想到，我们不关心攻击的顺序，那么我们可以先打 $s_{i}$ 小的，然后一点一点加实力，最后把他们全都打败。为什么这样是对的？因为我们保证了在打第 $x$ 个怪物时，能打的全都打了。这样就保证了对于每一个怪物打他时，实力最大。  
而这个过程，可以用一个优先队列来以 $s_{i}$ 为第 `1` 关键字，从小到大攻击。  
但是 dp 怎么转移呢？可以枚举下一个要喝的药水，然后在枚举之前，要将 $dp_{i}$ 可以到达的点标记一下，枚举下一个时就先判断 $dp_{i}$ 可不可以到达 $j$。枚举完点 $j$ 之后，就可以将初始力量变成 $dp_{i} \times g_{j}$，再根据上面说的打怪顺序来打怪，如果现在优先队列队头的点 $x$，在 $dp_{i}$ 就能被遍历，那么就不加上他的 $g_{x}$。  
最后要注意一下：要在向外扩张的时候要特殊判断一下如果这个点是一瓶药水的话，状态对应的数一定要为 `1`，以及优先队列记得清空。  
时间复杂度：$O(2^mnm \log n)$。  
希望这篇博客能帮到您！
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>

int bh[505], dp[1100];
bool vis[505];
int n, p[505], t[505], s[505], g[505], maxn;
vector<int> G[505];


void todp(int id){
	for(int i = 0; i <= n; i++) vis[i] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > q;
	while(!q.empty()) q.pop();
	q.push({0, 1});
	
	while(!q.empty()){ //标记id能到的所有点
		int x = q.top().second;
		q.pop();
		if(s[x] > dp[id]) break;
		vis[x] = 1;
		
		for(auto y : G[x]){
			if(t[y] == 1 || (id & (1 << (bh[y] - 1)))){//要时刻注意一定是在id的范围内
				q.push({s[y], y});
			} else {
				vis[y] = 1; //表示可以到
			}
		}
	}
	
	for(int i = 1; i <= n; i++){
		if(bh[i] && vis[i] && (id & (1 << (bh[i] - 1))) == 0){ //枚举新拓展的点
			int sum = dp[id] * g[i];
			int nid = (id | (1 << (bh[i] - 1)));
			
			while(!q.empty()) q.pop();//一定要清空
			q.push({0, 1});
		
			while(!q.empty()){
				int x = q.top().second, y = q.top().first;
				q.pop();
				if(y <= sum && y) sum += g[x]; //y=0表示在dp[id]里被算过
				if(y > sum) break;//如果比现在的sum大，没救了。
				
				if(sum >= maxn){ //随时随地判断
					cout << "Yes" << endl;
					exit(0);
				}
				
				for(auto y : G[x]){
					if(!vis[y]){
						if(t[y] == 2) continue;//不能到的药水不能拿
						q.push({s[y], y});
					} else {
						if(t[y] == 2 && (nid & (1 << (bh[y] - 1))) == 0){ //即使id能到，也要判断在(id| (1<<(bh[i]-1))) 的条件下
							continue;
						}
						q.push({0, y});//无贡献
					}
				}
			}
			
			dp[nid] = max(dp[nid], sum);//取最大值
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 2; i <= n; i++){
		cin >> p[i] >> t[i] >> s[i] >> g[i];
		G[p[i]].push_back(i);//建边
		maxn = max(maxn, s[i]);//记录最大值，因为要及时跳出，否则1000000000^10会炸！
	}
	
	int now = 0;
	for(int i = 1; i <= n; i++){
		if(t[i] == 2) bh[i] = ++now;//药水编号
	}
	dp[0] = 1;//初始战力
	
	priority_queue<pii, vector<pii>, greater<pii> > q;
	q.push({0, 1});
	while(!q.empty()){
		int x = q.top().second;
		q.pop();
		
		if(s[x] > dp[0]) break;
		dp[0] += g[x];
		
		if(dp[0] >= maxn){//如果不用任何一瓶药水就可以打通关，输出Yes
			cout << "Yes" << endl;
			exit(0);
		}
	
		for(auto y : G[x]){
			if(t[y] == 1){//因为要拿的集合是0，所以不能拿药水
				q.push({s[y], y});//先打s[i]小的
			}
		}
	}//算dp[0]
	
	for(int i = 0; i < (1 << (now)); i++){
		todp(i);
	}
	cout << "No" << endl;
	return 0;
}//喜欢的话点个赞吧！

---

## 作者：iiiiiyang (赞：7)

[劲爆的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17691604.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc319_f)

有过类似的 idea 啊，怎么撞了 ABC 了/fn。

注意到药最多只有十个，肯定是先尽可能的加，然后再用乘，因此从这上面入手。状压药定点的使用情况，设 $f_S$ 表示只用掉 $S$ 这些药最后能够到达的最大力量值，那么有解的充要条件就是存在 $f_S \geq \max s_i$。转移方程为 $f_{S \cup \{ j \}} = f_S \times g_j (j \notin S)$，能够进行转移的 $j$ 需要符合到达 $j$ 点前的怪物关都被打通，而打关则是一个贪心扩展的过程，因为肯定从当前能够打的关中挑选最小 $s$ 的怪打，这可以通过小根堆维护候选集合。记药定点的个数为 $m$，则复杂度为 $\mathcal O(2^m n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=510;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,m,x,all,top,S;
	int t[MAX],s[MAX],g[MAX];
    int f[1<<10],use[10],med[MAX],rmed[10];
    vector<int> G[MAX];
    priority_queue<pii,vector<pii>,greater<pii>> q;
    
    inline void lmy_forever()
    {
    	read(n);
    	for(int i=2;i<=n;++i) read(x,t[i],s[i],g[i]),G[x].eb(i),t[i]==2?(med[i]=m,rmed[m]=i,++m,void()):cmax(top,s[i]);
    	f[0]=1,t[1]=1;
    	for(int i=0;i<(1<<m);++i) if(f[i])
    	{
    		while(!q.empty()) q.pop();
    		q.emplace(mp(-1,1)),all=S=0,memset(use,0,sizeof use);
    		while(!q.empty())
    		{
    			auto [val,now]=q.top(); q.pop();
    			++all;
    			if(val>f[i]) break;
    			if(t[now]==1) f[i]+=g[now],S+=g[now]; else if(!(i>>med[now]&1)) {use[med[now]]=1; continue;}
    			for(auto to:G[now]) q.emplace(mp((t[to]==2?-1:s[to]),to));
			}
			if(all==n||f[i]>=top) return puts("Yes"),void();
			for(int j=0;j<m;++j) if(use[j]) cmax(f[i|(1<<j)],f[i]*g[rmed[j]]-S);
		}
		puts("No");
	}
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：是青白呀 (赞：4)

## 题意
给定一棵有 $n$ 个节点的树，每个点上有一只怪兽或一些药品。对于点 $i$，若 $t_i=1$，则该点上有一只可爱的小怪兽。若你的能力值不小于 $s_i$，则你可以和这只怪兽交朋友，它会让你的能力值提升 $g_i$。若你的能力值小于 $s_i$，则它会把你打败。若 $t_i=2$，则该点上有一些药品，吃下它们后，你的能力值将会变为原来的 $g_i$ 倍。对于 $t_i=2$ 的节点，保证 $s_i=0$。$1$ 号点上既没有药品，也没有怪兽。

你最开始在 $1$ 号节点处，能力值为 $1$。你每次行动可以走到相邻的点。若你首次到达一个节点，则你必须吃下那个点的药品或与那个点上的怪兽相遇（交朋友或被打败）。一旦你吃下了药品或与怪兽交了朋友，药品或怪兽就会消失。请问是否存在一种方案，使得你能与所有的怪兽交朋友，而不被打败？

保证上面是药品的节点不超过 $10$ 个。

## 分析
不难发现先加后乘所得的结果一定不劣于先乘后加。因此我们可以确定一个显然的策略——先与所有能走到的、且能交朋友的怪兽交朋友，再吃下一个点的药。可以用优先队列维护所有能交朋友的怪兽，优先与能力值要求小的怪兽交朋友。

当有多个药品可以吃时，先吃哪一个药品是很难决定的。由于药品的总数很小，考虑状态压缩，状态是每一个点上的药品是否被吃过。由于前面的贪心策略，显然每种状态最终走过的点的情况是唯一的。我们可以用两个 vector 分别存下下一步可以走到的有怪兽的点和有药品的点，每次转移枚举下一次吃哪一个点上的药品，并用 bfs 和优先队列更新下一个状态的 vector 即可。

注意只要当能力值大于最大的要求值时，即可判定为 Yes。若把所有药品节点的值都乘起来，数值太大。

设有药品的节点个数为 $m$ 个，则时间复杂度为 $O(2^{m}\times  mn\log n)$。

## Code

```cpp
#include<bits/stdc++.h> 
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
#define lowbit(x) x&-x
using namespace std;
typedef long long ll;
const int N=505,M=(1<<10)+2,mo=998244353,inf=1e18+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n;
struct edge{
	int to,nxt;
}e[N];
int fir[N],np,t[N],s[N],g[N],m[12],cntm,maxn;
int dp[M];
vector<int>med[M],ene[M];//装最佳状态下下一步即可走到的那些节点 
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
} 
struct point{
	int id,val;
	friend bool operator<(point x,point y){
		return x.val>y.val;
	}
}; 
bool fin=0;
void bfs(int st,int la,int mdc){//要更新的状态是st,上一个状态是la,这一次喝的药是mdc位置上的那个. 
	priority_queue<point>nen;
	vector<int>nmd;
	if(la==-1)nen.push((point){1,0});
	else{//初始化 
	    nmd=med[la];
	    rep(i,0,(int)ene[la].size()-1)
	        nen.push((point){ene[la][i],s[ene[la][i]]});
		for(auto it=nmd.begin();it!=nmd.end();it++){
			if(*it==mdc){
				nmd.erase(it);
				break;
			}
		}
		for(int i=fir[mdc];i;i=e[i].nxt){
			int j=e[i].to;
			if(t[j]==2)nmd.push_back(j);
			else nen.push((point){j,s[j]});
		}
	}
	int num;//现目前的能力值. 
	if(la==-1)num=1;
	else num=dp[la]*g[mdc];
	if(num>=maxn){
	   	fin=1;
	   	return;
	}
	while(!nen.empty()){
		point nw=nen.top();
		if(nw.val>num)break;
		nen.pop(),num+=g[nw.id];
		for(int i=fir[nw.id];i;i=e[i].nxt){
			int j=e[i].to;
			if(t[j]==2)nmd.push_back(j);
			else nen.push((point){j,s[j]});
		}
		if(num>=maxn){
	    	fin=1;
	    	return;
	    }
	}
	if(num>dp[st]){
		dp[st]=num,med[st]=nmd,ene[st].clear();
		while(!nen.empty())
		    ene[st].push_back(nen.top().id),nen.pop();
	}
}
signed main(){
	read(n);
	rep(i,2,n){
		int f;
		read(f),read(t[i]),read(s[i]),read(g[i]);
	    add(f,i),maxn=max(maxn,s[i]);
	    if(t[i]==2)m[++cntm]=i,s[i]=cntm;
	}
    bfs(0,-1,0);//把第一个装进去 
    if(fin){
    	printf("Yes");
    	return 0;
	}
	rep(st,0,(1<<cntm)-1){
		rep(i,0,(int)med[st].size()-1){
		    int j=med[st][i];
			if((st>>(s[j]-1))&1)continue;
			int nw=st|(1<<(s[j]-1));
			bfs(nw,st,j);
			if(fin){
				printf("Yes");
            	return 0;
			}
		}
	}
	if(fin)printf("Yes");
    else printf("No");
    return 0;
}
```

---

## 作者：EityDawn (赞：2)

好题。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_f)

# 思路：

首先一个贪心的思路是能打怪加血就尽量打怪，嗑药的时间越往后那么你得到的血量就越多。

而对于当前我们能打的怪，肯定是优先打 $s_i$ 最小，同时 $g_i$ 最大的最优，这个可以用小根堆来维护

考虑 $\sum [t_i=2] \le 10$，我们可以对嗑药的集合进行状压。

定义 $f_{S}$ 为嗑完集合状态为 $S$ 中的药后，所能获得的最大血量，同时记录状态为 $S$ 时，树上节点的可达性。一个状态对应的可达节点一定构成了一个联通块。

先处理出不嗑一瓶药的所能获得的最大血量。枚举所有状态，枚举嗑了集合里的哪瓶药产生了当前集合。

对于当前枚举的药，需要用 bfs 判断在原状态的基础上是否能到达对应节点，即是否合法。然后将可达节点全部压入小根堆继续计算嗑完这瓶药后打怪所能得到的最大血量。

注意每次计算完后，都需判断一次当前血量是否大于 $s_i$ 的最大值，否则会炸 long long。

总复杂度为 $O(2^mnm\log n)$，$m$ 是药的数量。

## code

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define FileIn(x) freopen(""#x".in","r",stdin)
#define FileOut(x) freopen(""#x".out","w",stdout)
#define debug(x) cerr<<""#x" = "<< (x) <<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 Int;
const int N=510,M=10,inf=2e9;
bool StM;
vector<int>G[N];
int n,t[N],s[N],g[N];
int rt=1,m=0,id[N],Re[N];
ll f[(1<<M)],ma;
bitset<N>vis[(1<<M)];
struct enermy{
    int up,del,id;
    bool operator<(const enermy&a) const{
        if(a.up==up) return a.del>del;
        return a.up<up;
    }
};
priority_queue<enermy>q;
void Main()
{
    cin>>n;m=0;
    for(int i=2,x;i<=n;i++)
    {
        cin>>x>>t[i]>>s[i]>>g[i];
        G[x].push_back(i);ma=max(ma,(ll)s[i]);
    }
    for(int i=2;i<=n;i++)
        if(!(t[i]&1)) Re[id[i]=++m]=i;
    for(int to:G[rt])
        if(t[to]&1) q.push({s[to],g[to],to});
    ll cur=1;vis[0][rt]=1;
    while(q.size())
    {
        auto [up,del,now]=q.top();q.pop();
        if(up>cur) break;
        cur+=del;vis[0][now]=1;
        for(int to:G[now])
            if(t[to]&1) q.push({s[to],g[to],to});
    }
    f[0]=cur;
    if(f[0]>ma) return void(cout<<"Yes\n");
    for(int S=1;S<(1<<m);S++)
    {
        f[S]=-inf;
        for(int i=1;i<=m;i++)
        {
            if(S&(1<<i-1)){
                if(f[S^(1<<i-1)]<0) continue;
                bool OK=false;
                queue<int>p;p.push(rt);
                while(p.size())
                {
                    int now=p.front();p.pop();
                    for(int to:G[now])
                    {
                        if(id[to]==i) OK=true;
                        if(vis[S^(1<<i-1)][to]) p.push(to);
                    }
                    if(OK) break;
                }
                if(!OK) continue;
                while(q.size()) q.pop();
                for(int to:G[rt])
                {
                    if(t[to]&1){
                        if(vis[S^(1<<i-1)][to]) q.push({0,0,to});
                        else q.push({s[to],g[to],to});
                    }
                    else if(S&(1<<id[to]-1)) q.push({0,0,to});
                }
                ll cur=1ll*f[S^(1<<i-1)]*g[Re[i]];
                bitset<N>per;per.reset();
                while(q.size())
                {
                    auto [up,del,now]=q.top();q.pop();
                    if(up>cur) break;
                    cur+=del;per[now]=1;
                    for(int to:G[now])
                    {
                        if(t[to]&1){
                            if(vis[S^(1<<i-1)][to]) q.push({0,0,to});
                            else q.push({s[to],g[to],to});
                        }
                        else if(S&(1<<id[to]-1)) q.push({0,0,to});
                    }
                }
                if(cur>f[S])
                    f[S]=cur,vis[S]=per;
                if(f[S]>ma) return void(cout<<"Yes\n");
            }
        }
    }
    cout<<"No\n";
}
bool EdM;
int main()
{
    cerr<<fabs(&StM-&EdM)/1024.0/1024.0<<" MB\n";
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int StT=clock();
    int T=1;
    while(T--) Main();   
    int EdT=clock();
    cerr<<1e3*(EdT-StT)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：Xy_top (赞：1)

独立想出的一道紫题，甚至没有走到弯路里去。

显然，先把能打的怪都打掉再嗑药一定是最优的，因为加号加的东西可以被更多的乘号乘。

设 $f_{S}$ 为每个药磕没嗑的状态为 $S$，此时的最大战斗值以及能到的所有点，转移的话先把能嗑的药乘上，然后用优先队列每次取出血量最低的不为药的节点，走过去，这是一个类似于广搜的过程。

代码（实现略有不同）：

```cpp
#include <bits/stdc++.h>
#define pi pair <int, int>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, cy;
int p[505], t[505], s[505], g[505], y[11];
int f[1024][505];
vector <int> G[505], tmp;
bool uu[505];
priority_queue <pi, vector <pi>, greater <pi> > q;
int func (int S, int x) {
	tmp.clear ();
	while (!q.empty () ) q.pop ();
	For (i, 1, 500) uu[i] = 0;
	For (i, 1, f[S][0]) uu[f[S][i] ] = 1;
	For (i, 1, f[S][0]) for (int v : G[f[S][i] ]) if (!uu[v]) q.push (make_pair (s[v], v) );
	int ret = f[S][501];
	while (!q.empty () ) {
		int u = q.top ().second;
		q.pop ();
		if (s[u] > ret) break;
		if (t[u] == 2 && u != y[x]) continue;
		tmp.push_back (u);
		if (t[u] == 1) ret = min (1000000001LL, ret + g[u]);
		else ret = min (1000000001LL, ret * g[u]);
		for (int v : G[u]) q.push (make_pair (s[v], v) );
	}
	For (i, 1, f[S][0]) tmp.push_back (f[S][i]);
	return min (ret, 1000000001LL);
}
void solve () {
	cin >> n;
	For (i, 2, n) {
		cin >> p[i] >> t[i] >> s[i] >> g[i];
		if (t[i] == 2) y[++ cy] = i;
		G[p[i] ].push_back (i);
	}
	for (int v : G[1]) q.push (make_pair (s[v], v) );
	int tt = 1;
	f[0][501] = 1;
	while (!q.empty () ) {
		int u = q.top ().second;
		q.pop ();
		if (s[u] > f[0][501]) break;
		if (t[u] == 2) continue;
		f[0][501] = min (1000000001LL, f[0][501] + g[u]);
		f[0][++ f[0][0] ] = u;
		for (int v : G[u]) q.push (make_pair (s[v], v) );
	}
	f[0][++ f[0][0] ] = 1;
	int S = (1 << cy) - 1;
	For (i, 1, S) {
		For (k, 0, cy - 1) {
			if (!(i & (1 << k) ) ) continue;
			int x = func (i ^ (1 << k), k + 1);
			if (x <= f[i][501] && x != 1000000001) continue;
			f[i][501] = x;
			f[i][0] = 0;
			for (int j : tmp) f[i][++ f[i][0] ] = j;
		}
	}
	if (f[S][0] == n) cout << "Yes";
	else cout << "No";
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```

---

## 作者：0x3F (赞：0)

容易想到一个策略：先打怪，从小往大打，把能打的怪都打了再嗑药。

关键在于嗑药的顺序，这个需要状压 dp，唯一问题在于怎么从 dp 值恢复出哪些怪被打过。

实际上，只需要从头走一遍，如果怪的血量小于等于当前体力就是打过的。

时间复杂度为 $\mathcal{O}(n\log n2^k)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 510;
const int inf = 1000000000;
int n, c, id[_], p[_], t[_], s[_], g[_], e, hd[_], nx[_], to[_], dp[1024];
inline void add(int u, int v) {
	e++;
	nx[e] = hd[u];
	to[e] = v;
	hd[u] = e;
}
priority_queue<pair<int, int> > Q;
int l, r, q[_];
int c1, a1[_];
int c2, a2[_];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> p[i] >> t[i] >> s[i] >> g[i];
		add(p[i], i);
		if (t[i] == 2) {
			id[i] = c;
			c++;
		}
	}
	memset(dp, 0xFF, sizeof(dp));
	int v = 1;
	Q.push(make_pair(0, 1));
	while (!Q.empty()) {
		int x = Q.top().second;
		Q.pop();
		if (v >= s[x]) {
			v += g[x];
			if (v >= inf) {
				cout << "Yes" << endl;
				return 0;
			}
			for (int i = hd[x]; i; i = nx[i]) {
				int y = to[i];
				if (t[y] == 1) {
					Q.push(make_pair(-s[y], y));
				}
			}
		}
	}
	dp[0] = v;
	for (int i = 0; i <= (1 << c) - 2; i++) {
		if (dp[i] == -1) continue;
		int v = dp[i];
		l = r = 1;
		q[1] = 1;
		c1 = 0;
		c2 = 0;
		while (l <= r) {
			int x = q[l];
			l++;
			for (int j = hd[x]; j; j = nx[j]) {
				int y = to[j];
				if ((t[y] == 1 && s[y] <= v) || (t[y] == 2 && (i & (1 << id[y])))) {
					r++;
					q[r] = y;
				} else if (t[y] == 1) {
					c1++;
					a1[c1] = y;
				} else {
					c2++;
					a2[c2] = y;
				}
			}
		}
		int vv = v;
		for (int l = 1; l <= c2; l++) {
		    v = vv;
			int p = a2[l];
			int k = g[p];
			int ii = (i | (1 << id[p]));
			if (1LL * v * k >= inf) {
				cout << "Yes" << endl;
				return 0;
			}
			v *= k;
			for (int j = hd[p]; j; j = nx[j]) {
				int x = to[j];
				if (t[x] == 1) {
					Q.push(make_pair(-s[x], x));
				}
			}
			for (int j = 1; j <= c1; j++) {
				int x = a1[j];
				Q.push(make_pair(-s[x], x));
			}
			while (!Q.empty()) {
				int x = Q.top().second;
				Q.pop();
				if (v >= s[x]) {
					v += g[x];
					if (v >= inf) {
						cout << "Yes" << endl;
						return 0;
					}
					for (int j = hd[x]; j; j = nx[j]) {
						int y = to[j];
						if (t[y] == 1) {
							Q.push(make_pair(-s[y], y));
						}
					}
				}
			}
			dp[ii] = max(dp[ii], v);
		}
	}
	int A = dp[(1 << c) - 1];
	for (int i = 1; i <= n; i++) {
		if (t[i] == 1 && A < s[i]) {
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;
	return 0;
}
```

---

## 作者：RandomLife (赞：0)

~~题目名曰《战斗的精神小伙 Takahashi》~~

----------

首先要讲究一个最优策略：先打怪再嗑药一定比先嗑药再打怪更优。

另外，由于打怪的过程中战斗力只会增加，因此显然先打战斗力弱的怪。

看到对于 $t_i=2$ 的数量不会超过 $10$，直接考虑状压 DP。设 $f[i]$ 表示在状态 $i$ 下能到达的最大战斗力，最后再判断巅峰状态下的战斗力会不会超过所有怪。

对于每个状态，维护一个小根堆。小根堆维护的是所有目前能打的怪以 $s_i$ 为关键字排序的优先队列。显然，每一个状态的小根堆都会由前面的转移。

另外，为了判断一个药是否能磕到，需要维护一个关系树。若点 $i$ 在关系树中的父亲为 $fa[i]$，则在原树中 $fa[i]$ 是 $i$ 最近一个是药的祖先。

时间复杂度 $O(2^mn \log n)$，其中 $m$ 是药的数量。

代码：
```c++
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>PII;
typedef priority_queue<PII,vector<PII>,greater<PII> >PQ;
const int N=505,M=15;
int n,p[N],id[M],pos[N],fa[M],vis[1<<M][N],tot=0;
long long t[N],s[N],g[N],f[1<<M],Max=0;
PQ pq[1<<M];
vector<int>adj[N];
void solve(){
    queue<int>q;
    for(int i=1;i<=tot;++i){
        q=queue<int>();
        q.push(id[i]);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            if(pos[u]&&i!=pos[u])fa[pos[u]]=i;
            else
                for(int v:adj[u])q.push(v);
        }
    }
}
int main(){
    cin>>n;
    for(int i=2;i<=n;++i){
        cin>>p[i]>>t[i]>>s[i]>>g[i];
        if(t[i]==2)id[++tot]=i,pos[i]=tot;
        else Max=max(Max,s[i]);
        adj[p[i]].push_back(i);
    }
    solve(),f[0]=1,vis[0][1]=1;
    for(int v:adj[1])
        if(t[v]==1)pq[0].push({s[v],v});
    while(!pq[0].empty()){
        int u=pq[0].top().second;
        if(f[0]<s[u])break;
        f[0]+=g[u],pq[0].pop(),vis[0][u]=1;
        for(int v:adj[u])
            if(t[v]==1)pq[0].push({s[v],v});
    }
    for(int i=0;i<(1<<tot);++i){
        if(f[i]>=Max){
            cout<<"Yes";
            return 0;
        }
        PQ q;
        for(int j=0;j<tot;++j){
            if(!vis[i][p[id[j+1]]]||(i&(1<<j))||fa[j+1]&&!(i&(1<<(fa[j+1]-1))))continue;
            int Next=i|(1<<j);
            long long val=f[i]*g[id[j+1]];
            q=pq[i];
            for(int k=1;k<=n;++k)vis[Next][k]=vis[i][k];
            vis[Next][id[j+1]]=1;
            for(int v:adj[id[j+1]])
                if(t[v]==1)q.push({s[v],v});
            while(!q.empty()){
                int u=q.top().second;
                if(val<s[u])break;
                val+=g[u],q.pop(),vis[Next][u]=1;
                for(int v:adj[u])
                    if(t[v]==1)q.push({s[v],v});
            }
            if(f[Next]<val)f[Next]=val,pq[Next]=q;
        }
    }
    cout<<"No";
    return 0;
}
```

---

