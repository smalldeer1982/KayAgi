# The Most Reckless Defense

## 题目描述

You are playing a very popular Tower Defense game called "Runnerfield 2". In this game, the player sets up defensive towers that attack enemies moving from a certain starting point to the player's base.

You are given a grid of size $ n \times m $ , on which $ k $ towers are already placed and a path is laid out through which enemies will move. The cell at the intersection of the $ x $ -th row and the $ y $ -th column is denoted as $ (x, y) $ .

Each second, a tower deals $ p_i $ units of damage to all enemies within its range. For example, if an enemy is located at cell $ (x, y) $ and a tower is at $ (x_i, y_i) $ with a range of $ r $ , then the enemy will take damage of $ p_i $ if $ (x - x_i) ^ 2 + (y - y_i) ^ 2 \le r ^ 2 $ .

Enemies move from cell $ (1, 1) $ to cell $ (n, m) $ , visiting each cell of the path exactly once. An enemy instantly moves to an adjacent cell horizontally or vertically, but before doing so, it spends one second in the current cell. If its health becomes zero or less during this second, the enemy can no longer move. The player loses if an enemy reaches cell $ (n, m) $ and can make one more move.

By default, all towers have a zero range, but the player can set a tower's range to an integer $ r $ ( $ r > 0 $ ), in which case the health of all enemies will increase by $ 3^r $ . However, each $ r $ can only be used for at most one tower.

Suppose an enemy has a base health of $ h $ units. If the tower ranges are $ 2 $ , $ 4 $ , and $ 5 $ , then the enemy's health at the start of the path will be $ h + 3 ^ 2 + 3 ^ 4 + 3 ^ 5 = h + 9 + 81 + 243 = h + 333 $ . The choice of ranges is made once before the appearance of enemies and cannot be changed after the game starts.

Find the maximum amount of base health $ h $ for which it is possible to set the ranges so that the player does not lose when an enemy with health $ h $ passes through (without considering the additions for tower ranges).

## 说明/提示

In the first example, there is no point in increasing the tower range, as it will not be able to deal enough damage to the monster even with $ 1 $ unit of health.

In the second example, the tower has a range of $ 1 $ , and it deals damage to the monster in cells $ (1, 1) $ and $ (2, 2) $ .

In the third example, the tower has a range of $ 2 $ , and it deals damage to the monster in all path cells. If the enemy's base health is $ 1491 $ , then after the addition for the tower range, its health will be $ 1491 + 3 ^ 2 = 1500 $ , which exactly equals the damage the tower will deal to it in three seconds.

In the fourth example, the tower at $ (1, 2) $ has a range of $ 1 $ , and the tower at $ (3, 1) $ has a range of $ 2 $ .

## 样例 #1

### 输入

```
6
2 2 1
#.
##
1 2 1
2 2 1
#.
##
1 2 2
2 2 1
#.
##
1 2 500
3 3 2
#..
##.
.##
1 2 4
3 1 3
3 5 2
#.###
#.#.#
###.#
2 2 2
2 4 2
5 5 4
#....
#....
#....
#....
#####
3 2 142
4 5 9
2 5 79
1 3 50```

### 输出

```
0
1
1491
11
8
1797```

# 题解

## 作者：sky_landscape (赞：8)

为什么所有题解都是状压 DP ，这题不是看着很**网络流**（最小费用最大流）吗？

首先还是分析一下 $r$ 的取值范围，可以把敌人增加的血量理解为减少防御塔的伤害，那么一座防御塔的总伤害最多是 $500\pi r^2 - 3^r$，不难发现 $r$ 最大为 $12$，这就很符合网络流的范围。

接下来建图，把防御塔当作左部点，半径为右部点。有几种类型的边：

第 $1$ 类：源点向左部点连边，流量为 $1$，费用为 $0$。

第 $2$ 类：右部点向汇点连边，流量为 $1$，费用为 $0$。

第 $3$ 类：每一个左部点向每一个右部点连边，流量为 $1$，费用为这座防御塔在这个半径下的总伤害（减去了敌人增加的血量）的相反数。

对第 $3$ 类边做一下解释：

费用流求的是最小费用，但是我们要求的是最大的伤害，所以取一个相反数，输出的时候反过来就行了。当然如果本来就是个负数肯定不连。

代码：
```cpp
/*网络流千万想清楚清空！！！！！！！！！！！！！*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=400010;
const int INF=10000000000000000;
int t,n,m,k,s,tt;
int used[N];
int pw[20];
int ct;
struct stu{
    int x,y;
}road[N];

struct node{
    int x,y,p;
}tow[N];

int ans;

namespace EK{
    int nxt[N],dis[N],cost[N],to[N],head[N],flow[N];
    int pre[N],increase[N];
    bool vis[N];
    int tot=1;
    void add(int x,int y,int z,int c){
        to[++tot]=y;
        flow[tot]=z;
        cost[tot]=c;
        nxt[tot]=head[x];
        head[x]=tot;
    }
    bool spfa(){
        for(int i=0;i<=t;i++){
            dis[i]=INF;
            increase[i]=INF;
            pre[i]=0;
            vis[i]=false;
        }
        vis[s]=true;
        queue<int> q;
        q.push(s);
        dis[s]=0;
        while(!q.empty()){
            int x=q.front();
            q.pop();
            vis[x]=false;
            for(int i=head[x];i;i=nxt[i]){
                int y=to[i];
                if(flow[i] && dis[y]>dis[x]+cost[i]){
                    dis[y]=dis[x]+cost[i];
                    pre[y]=i;
                    increase[y]=min(increase[x],flow[i]);
                    if(!vis[y]){
                        vis[y]=true;
                        q.push(y);
                    }
                }
            }
        }
        return dis[t]<INF;
    }
    void update(){
        int cur=t;
        while(cur!=s){
            int last=pre[cur];
            flow[last]-=increase[t];
            flow[last^1]+=increase[t];
            cur=to[last^1];
        }
        ans+=(increase[t]*dis[t]);
    }
    void clear(){
        for(int i=0;i<=max(t,tot);i++){
            head[i]=to[i]=nxt[i]=flow[i]=cost[i]=0;
        }
        tot=1;
        ans=0;
    }
}

inline int read(){
    char ch;int x=0;bool f=false;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    if(f) x=-x;
    return x;
}

int dist(int x1,int y1,int x2,int y2){
    int a=abs(x1-x2),b=abs(y1-y2);
    return a*a+b*b;
}

int calc(int x,int r){
    int dam=0;
    for(int i=1;i<=ct;i++){
        if(dist(tow[x].x,tow[x].y,road[i].x,road[i].y)<=(r*r)){
            dam+=tow[x].p;
        }
    }
    return dam-pw[r];
}

signed main(){
    cin>>tt;
    pw[0]=1;
    for(int i=1;i<=12;i++) pw[i]=pw[i-1]*3;
    pw[0]=0;
    while(tt--){
        n=read(),m=read(),k=read();
        s=0,t=k+14;
        for(int i=1;i<=n;i++){
            string ss;
            cin>>ss;
            ss=" "+ss;
            for(int j=1;j<=m;j++){
                if(ss[j]=='#'){
                    road[++ct].x=i,road[ct].y=j;
                }
            }
        }
        for(int i=1;i<=k;i++){
            cin>>tow[i].x>>tow[i].y>>tow[i].p;
        }
        for(int i=1;i<=k;i++){
            EK::add(s,i,1,0);
            EK::add(i,s,0,0);
        }
        EK::add(k+1,t,INF,0);//当时判了一下r=0
        EK::add(t,k+1,0,0);
        for(int j=2;j<=13;j++){
            EK::add(j+k,t,1,0);
            EK::add(t,j+k,0,0);
        }
        for(int i=1;i<=k;i++){
            EK::add(i,k+1,INF,-calc(i,0));
            EK::add(k+1,i,0,calc(i,0));
            for(int j=1;j<=12;j++){
                int kl=calc(i,j);
                if(kl>0){
                    EK::add(i,k+j+1,1,-kl);
                    EK::add(k+j+1,i,0,kl);
                }
            }
        }
        while(EK::spfa()) EK::update();
        cout<<((-1)*ans)<<"\n";
        ct=0;
        EK::clear();
    }
    return 0;
}
```

---

## 作者：LHLeisus (赞：5)

[My cnblog](https://www.cnblogs.com/LHLeisus/p/18141079)

给敌人加血可以看成是减少防御塔的攻击力，那么一个塔对敌人能造成的最大伤害即为 $500\pi r^2-3^r$，注意到 $r=12$ 时已经小于 $0$ 了，所以半径不会很大，又因为每个 $r$ 只能选一次，所以有效的塔很少，考虑状压 $dp$。

具体地，我们设 $f_{i,S}$ 表示前 $i$ 个塔中，被选到的塔的半径集合为 $S$，所造成的伤害（攻击力）为多少。显然最后答案就等于最大的伤害。有转移方程：
$$
f_{i,S}=\max(f_{i-1,S},f_{i-1,S\oplus r}+p_i\times calc(i,r)-3^r)
$$
含义很简单，就是当前选或不选。$calc(i,r)$ 表示第 $i$ 座塔半径为 $r$ 时能攻击到几次敌人。预处理 $calc$ 的复杂度为 $\mathcal{O}(k\cdot R^3)$，$dp$ 的复杂度为 $\mathcal{O}(k\cdot R\cdot 2^R)$，总复杂度 $\mathcal{O}(k\cdot R\cdot (R^2+2^R))$。

其实也可以最后一起减去 $\sum 3^r$ 的，两种都对。一开始我不理解为啥两种写法是等价的，想了想，大概是因为每次取 $\max$ 的两项只差一个 $r$，所以要么都减了，要么都没减，不影响相对大小，也就不影响结果。

其实这题还能费用流。每个塔作为左部点，$12$ 个半径作为右部点，边权或者说费用就是 $p_i\times calc(i,r)-3^r$，跑一遍二分图带权最大匹配，也就是最大费用最大流即可。不过我没写，听 @cuiyulin 口胡的。

$dp$ 代码：

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(register int i=(a);i>=(b);--i)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
using namespace std;
inline int read();
typedef long long ll;
typedef double db;
const int N=50+5;
const int inf=0x3f3f3f3f;
const int INF=0x7f7f7f7f;
const int R=12;
int sqr(int x){return (x)*(x);}
int n,m,k;
char s[N][N];
struct tower{
    int x,y,p;
}a[N*N];
int f[N*N][1<<R];
int calc[N*N][R+1];
int Calc(int x,int y,int r){
    int res=0;
    FOR(i,max(x-r,1),min(n,x+r))
        FOR(j,max(y-r,1),min(m,y+r))
            if(s[i][j]=='#'&&sqr(x-i)+sqr(y-j)<=sqr(r))
            	res++;
    return res;
}
void work(){
    n=read(),m=read(),k=read();
    FOR(i,1,n) scanf("%s",s[i]+1);
    FOR(i,1,k) a[i]={read(),read(),read()};
    FOR(i,1,k){
        int x=a[i].x,y=a[i].y;
        FOR(r,1,R) calc[i][r]=Calc(x,y,r);
    }
    memset(f,-0x3f,sizeof f);
    f[0][0]=0;
    FOR(i,1,k){
    	for(int S=0;S<(1<<R);++S){
    		f[i][S]=f[i-1][S];
    		FOR(r,1,R)
    			if(S>>(r-1)&1) 
					f[i][S]=max(f[i][S],f[i-1][S^(1<<r-1)]+a[i].p*calc[i][r]-(int)pow(3,r));
		}
	}
	int ans=0;
	FOR(i,1,k)
		FOR(S,0,(1<<R)-1)
			ans=max(ans,f[i][S]);
	printf("%d\n",ans);
}
int main()
{
    int T=read();
    while(T--) work();
	return 0;
	//あまりに短い夏だけで何を残していけるのかな？
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```

---

## 作者：huangrenheluogu (赞：1)

因为 $3^k$ 是指数级别增长，所以范围肯定不能很大。容易得到最大的范围应该是 $12$。

然后放塔。$f_{i,s}$ 表示放了 $i$ 个塔，用了 $s$ 中的数字的最大攻击值 - 给怪物生命的增加值。dp 枚举增加那一种塔即可，需要提前处理这个塔用 $r$ 的范围可以攻击怪物多少次即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 55;
int T, n, m, k, x, y, p, qp[N], sq[N * N << 1];
ll ans, f[1 << 12];
int cnt[N], mx;
char s[N][N];
vector<pii> ps;
inline void chkmax(ll &x, ll y){
    if(x < y) x = y;
}
inline void solve(){
    scanf("%d%d%d", &n, &m, &k);
    ps.clear();
    qp[0] = 1;
    mx = 12;
    for(int i = 1; i <= mx; i++) qp[i] = qp[i - 1] * 3;
    for(int i = 1; i <= n; i++){
        scanf("%s", s[i] + 1);
        for(int j = 1; j <= m; j++){
            if(s[i][j] == '#'){
                ps.push_back({i, j});
            }
        }
    }
    for(int i = 1; i <= max(n, m) * max(n, m) * 2; i++){
        sq[i] = sqrt(i);
        if(sq[i] * sq[i] < i){
            sq[i]++;
        }
    }
    ans = 0ll;
    while(k--){
        scanf("%d%d%d", &x, &y, &p);
        for(pii e : ps) if((e.fi - x) * (e.fi - x) + (e.se - y) * (e.se - y) <= mx * mx){
            cnt[sq[(e.fi - x) * (e.fi - x) + (e.se - y) * (e.se - y)]]++;
        }
        for(int i = 1; i <= mx; i++) cnt[i] += cnt[i - 1];
        for(int s = (1 << mx) - 1; ~s; s--){
            // assert(!f[s]);
            for(int i = 0; i < mx; i++) if(~s >> i & 1){
                // cerr << s << ' ' << i << ' ' << f[s] << ' ' << cnt[i + 1] * p << ' ' << qp[i + 1] << endl;
                // assert(!f[s]);
                chkmax(f[s | (1 << i)], f[s] + cnt[i + 1] * p - qp[i + 1]);
            }
        }
        for(int i = 0; i <= mx; i++) cnt[i] = 0;
    }
    printf("%lld\n", f[(1 << mx) - 1]);
    memset(f, 0, sizeof(f));
}
signed main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：OPEC (赞：1)

# [CF1955H The Most Reckless Defense](https://www.luogu.com.cn/problem/CF1955H)

这道题仅计算以后发现 $r$ 不大于是 $12$。一看见 $12$ 就会联想到状压dp。

设 $r$ 为半径，$w_i$ 表示 $3$ 的 $i$ 次方，状态转移方程是 $f_{i\ j}=\max(f_{i\ j},f_{i-1\ j \oplus (2^{(r-1)})}+c_r\times p-w_r)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=5e1+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n,m,k;
char a[N][N];
int w[13];
int f[2510][1<<12];
void solve()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=k;i++)
	{
		int x,y,p;
		cin>>x>>y>>p;
		int c[13]={0};
		for(int j=1;j<=n;j++)
		{
			for(int l=1;l<=m;l++)
			{
				if(a[j][l]=='#')
				{
					int r=ceil(hypot(j-x,l-y));
					if(r<=12)
					{
						c[r]++;
					}
				}
			}
		}
		for(int j=1;j<=12;j++)
		{
			c[j]+=c[j-1];
		}
		for(int j=0;j<(1<<12);j++)
		{
			f[i][j]=f[i-1][j];
			for(int r=1;r<=12;r++)
			{
				if(j>>(r-1)&1)
				{
					f[i][j]=max(f[i][j],f[i-1][j^(1<<(r-1))]+c[r]*p-w[r]);
				}
			}
		}
	}
	cout<<f[k][(1<<12)-1]<<'\n';
}
signed main()
{
	fst
	w[1]=3;
	for(int i=2;i<=12;i++)
	{
		w[i]=w[i-1]*3;
	}
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：1)

# CF1955H The Most Reckless Defense

#### [题面](https://www.luogu.com.cn/problem/CF1955H)

## 思路

首先我们可以发现防御塔的 $r$ 最多为 $11$。

因为我们肯定希望防御塔对怪物的伤害越多越好，我们可以发现对怪物增加血量就相当于减少伤害，于是我们的防御塔对怪物初始血量的伤害为：

$$
	\pi r^{2}-3^{r}
$$

我们发现在 $r=12$ 时这个式子就已经是负数了，所以 $r$ 最多为 $11$。

注意到**每个 $r$ 只能用于最多一座塔**，于是我们就可以直接状压了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int n,m,k;
string s[55];
int d[4505][20];
int f[2][2050];
char ch;
int i,j,kk,o;
int x,y,z,cnt,sum,tmp,tp;
int ans;
void solve(){
	scanf("%d %d %d\n",&n,&m,&k);
	for(i=1;i<=n;++i){
        s[i]=' ';
        ch=getchar();
        while(ch!='\n'){
            s[i]+=ch;
            ch=getchar();
        }
	}
	for(i=1;i<=k;++i){
		scanf("%d %d %d\n",&x,&y,&z);
		cnt=0;
        sum=1;
        for(j=1;j<=11;++j){
            cnt=0;
            for(kk=1;kk<=n;++kk){
                tmp=abs(kk-x)*abs(kk-x);
                tp=j*j;
                for(o=1;o<=m;++o)
                    if(s[kk][o]=='#')
                        if(tmp+abs(o-y)*abs(o-y)<=tp)
                            cnt++;
            }        
            sum=sum+(sum<<1);
            d[i][j]=max(cnt*z-sum,0);
        }
	}
	for(i=1;i<=k;++i){
		for(j=0;j<2048;++j) f[i&1][j]=f[!(i&1)][j];
		for(j=0;j<2048;++j)
			for(kk=1;kk<=11;++kk)
				if((j>>(kk-1))&1)
					f[i&1][j]=max(f[i&1][j],f[!(i&1)][j^(1<<(kk-1))]+d[i][kk]);
		for(j=0;j<2048;++j) f[!(i&1)][j]=0;
	}
    tp=k&1;
	for(i=0;i<2048;++i){
		ans=max(ans,f[tp][i]);
		f[tp][i]=0;
	}
	printf("%d\n",ans);
	ans=0;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d\n",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1955H)

------------
## 思路
可以发现，每个敌人受到的最大伤害和不会超过 $50\times 50\times 500=1250000$，而 $\log_3(1250000)<13$，并且
> 每个 $r$ 只能用于**最多一座**塔

所以，我们最多只能给 $12$ 座塔不同的攻击范围。这个数据范围是可以状压的，定义 $dp_i$ 表示状态为 $i$ 时的最大伤害和，$Minus_i$ 表示状态为 $i$ 会让敌人的生命值增加的数量，那么答案 $ans=\max\limits_{i=0}^{2^{12}-1}(dp_i-Minus_i)$。

状态转移方程不难想：
$$
dp_j=\max\limits_{i=1}^{k}\max\limits_{l=0}^{11}(dp_{j\text{ xor }2^l}+d_{i,l+1}+p_i)
$$

其中 $d_{i,j}$ 表示当第 $i$ 座塔的攻击范围为 $j$ 时能够攻击到的总单元格数。

$Minus$ 数组和 $d$ 数组都可以预处理，但是需要注意的是当 $i$ 相同时 $dp_j$ 之间会互相影响，所以需要两个 $dp$ 数组，其中一个用来存上次循环的结果。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<12;
int T,n,m,k;
string s;
struct towers{
	int x,y,p;
}t[2505];
int pow3[15]={1},f[55][55],d[2505][15],Minus[N],ans,dp[2][N];
bool Now,Past;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	for(int i=1;i<=12;i++){
		pow3[i]=pow3[i-1]*3;
	}
	int r;
	for(int i=0;i<N;i++){
		for(int j=0;j<12;j++){
			if((i>>j)&1)Minus[i]+=pow3[j+1];
		}
//		printf("Minus[%d]=%d\n",i,Minus[i]);
	}
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			cin>>s;
			for(int j=1;j<=m;j++){
				f[i][j]=s[j-1]=='#';
			}
		}
		for(int i=1;i<=k;i++){
			cin>>t[i].x>>t[i].y>>t[i].p;
			for(int j=1;j<=12;j++){
				d[i][j]=0;
			}
			for(int j=1;j<=n;j++){
				for(int l=1;l<=m;l++){
					if(f[j][l]==0)continue;
					r=ceil(sqrt(pow(t[i].x-j,2)+pow(t[i].y-l,2)));
					if(r>0&&r<13)d[i][r]++;
				}
			}
			for(int j=1;j<=12;j++){
				d[i][j]+=d[i][j-1];
			}
		}
		for(int i=0;i<N;i++){
			dp[0][i]=dp[1][i]=0;
		}
		ans=0;
		for(int i=1;i<=k;i++){
			Now=i&1;Past=!Now;
			for(int j=0;j<N;j++){
				dp[Now][j]=dp[Past][j];
				for(int l=0;l<12;l++){
					if((j>>l)&1){
						dp[Now][j]=max(dp[Now][j],dp[Past][j^(1<<l)]+d[i][l+1]*t[i].p);
					}
				}
				ans=max(ans,dp[Now][j]-Minus[j]);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
/*
input:
1
5 3 7
###
..#
..#
..#
..#
3 2 175
4 2 409
5 1 470
4 1 140
5 2 275
2 1 465
3 1 415
output:
12196
*/
```

时间复杂度 $O(k(nm+r)+k(r2^r))$，空间复杂度 $O(nmr+2^r)$，满足题目要求。

---

