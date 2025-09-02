# [ABC211E] Red Polyomino

## 题目描述

## 题目翻译
&emsp;给你边长为 $ N $ 的且仅由字符 `#` 和 `.` 组成的正方形阵列，其中 `#` 表示黑色格子， `.` 表示白色格子。  
&emsp;你需要在白色格子中选择 $ K $ 个涂成红色，且使红色格子互相连接（仅包括上下左右相邻），求有多少种可能的方案。

## 样例 #1

### 输入

```
3
5
#.#
...
..#```

### 输出

```
5```

## 样例 #2

### 输入

```
2
2
#.
.#```

### 输出

```
0```

## 样例 #3

### 输入

```
8
8
........
........
........
........
........
........
........
........```

### 输出

```
64678```

# 题解

## 作者：Genius_Star (赞：5)

### 思路：

发现数据范围都非常的小，考虑暴力做法。

$N \times N$ 个方格中的 $K$ 个方格的选择数是 $C_{N^2}^k$，由于 $C_{64}^8 = 4426165368 > 4 \times 10^9$，因此直接暴力是不可能的了。

但是，由于红色方块相互连接，我们可以预测满足条件的组合数量很少。

所以可以跑枚举红色方块连接模式的 DFS（深度优先搜索）就足够了。

### 完整代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define me memset
#define rep(a,b,c) for(int a=b;a<=c;++a)
#define per(a,b,c) for(int a=b;a>=c;--a)
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b) {return a/gcd(a,b)*b;}

int n,k;
char s[10][10];
int dx[4]={0,0,1,-1},dy[4]={-1,1,0,0};
ll ans;

void dfs(int cnt){
    if(cnt==0){
        ans++;
        return;
    }
    vector<PII> vis;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(s[i][j]=='.'){
                bool flag=false;
                for(int t=0;t<4;++t){
                    int tx=i+dx[t],ty=j+dy[t];
                    if(tx>=1 && tx<=n && ty>=1 && ty<=n && s[tx][ty]=='@'){
                        flag=true;
                    }
                }
                if(flag){
                    s[i][j]='@';
                    dfs(cnt-1);
                    s[i][j]='#';
                    vis.pb({i,j});
                }
            }
        }
    }
    for(auto it:vis){
        s[it.fi][it.se]='.';
    }
}

int main() {
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;++i){
        getchar();
        for(int j=1;j<=n;++j){
            scanf("%c",&s[i][j]);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(s[i][j]=='.'){
                s[i][j]='@';
                dfs(k-1);
                s[i][j]='#';
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}

```


---

## 作者：iiiiiyang (赞：4)

[可爱的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17623952.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc211_e)

薄纱爆搜老哥。显然是染色模型，我们只需要维护连通性（即每个位置属于哪个连通块），不需要具体维护插头，考虑逐格 DP 维护轮廓线，类似于[神秘的生物](https://www.luogu.com.cn/problem/P3886)。恰好染色 $k$ 个格子很烦，不过 $k$ 不大，不妨直接放到状态里面，我选择了最小表示法哈希。设 $f_{i,j,S}$ 表示当前在第 $i$ 个格子，当前轮廓线状态为 $S$，总共染色了 $j$ 个格子的方案数。第一维依旧是滚动数组优化掉。枚举转移到哪个格子，当前染色了多少和轮廓线的状态，考虑如何转移：

- 当前格子是障碍物
  - 若当前格上侧染色了并且当前轮廓线上**上侧所属的连通块**没有其他露出来的地方，那么就没有机会再使上方这一部分连通起来，所以不能转移。否则就可以将上个状态的值转移过来。
- 当前格子不是障碍物
  - 若当前格左侧和上侧都没有选，则既可以选择维持现状、当前格也不选，也可以选择选择当前格，新建一个连通块。
  - 若当前格左侧选了，上侧没选，则当前格也可以考虑不选或者延伸左侧连通块。
  - 若当前格左侧没选，上侧选了，则当前格可以延申上侧连通块；如果不选的话还是要考虑上侧所属的连通块有没有其他露出来的地方，如果还有就可以不选这个格子。
  - 若当前格左侧和上侧都选了，如果选当前格子就会使两个联通块联通，需要手动修改状态；不选当前格子，约束条件和上面相同。

在每个格子转移完之后直接再次枚举状态，如果该状态 $S$ 只有一个连通块，则直接累加上答案 $f_{i,k,S}$。

最多只有四种连通块即五个状态，依然是方便运算直接压八进制，新建一个连通块直接把状态设成 $7$ 就好了。于是做到 $\mathcal O(nmkT)$，其中 $T$ 是总方案数，毛估估一下也就一千出头，搜出来也确实如此，第三个样例的状态只有 $1100$，轻松跑进 20ms。

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
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
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
    static const int Mod=1e9+7;
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
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=10;
    static const int Max=10000;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,m,K,a[MAX][MAX],ans;
    int now,last,f[2][MAX][Max];
    char c;
    
    namespace Hash
    {
    	namespace MinimumRepresent
    	{
    		constexpr int mask=7,offest=3;
    		int Ment[MAX],Vis[MAX];
    		inline int GetMin(int s)
    		{
    			memset(Vis,-1,sizeof Vis),Vis[0]=0;
    			int tot=0,ns=0;
    			for(int i=0;i<m;++i) Ment[i]=s>>(i*offest)&mask;
    			for(int i=0;i<m;++i) if(!~Vis[Ment[i]]) Vis[Ment[i]]=++tot,Ment[i]=tot; else Ment[i]=Vis[Ment[i]];
    			for(int i=0;i<m;++i) ns|=Ment[i]<<(i*offest);
    			return ns;
			}
			inline int GetTyp(int s)
			{
				memset(Vis,-1,sizeof Vis),Vis[0]=0;
				int tot=0;
				for(int i=0;i<m;++i) Ment[i]=s>>(i*offest)&mask;
    			for(int i=0;i<m;++i) if(!~Vis[Ment[i]]) Vis[Ment[i]]=++tot,Ment[i]=tot; else Ment[i]=Vis[Ment[i]];
    			return tot;
			}
		}
		using namespace MinimumRepresent;
		
		constexpr int mod=1000003;
		int nex[Max],head[mod],content[Max],tot;
		inline void ins(int x) {nex[++tot]=head[x%mod],content[tot]=x,head[x%mod]=tot;}
		inline int find(int x) {for(int i=head[x%mod];i;i=nex[i]) if(content[i]==x) return i; return ins(x),tot;}
	}
	using namespace Hash;

    inline void lmy_forever()
    {
    	read(n),m=n,read(K);
    	for(int i=0;i<n;++i) for(int j=0;j<m;++j) {do c=getchar(); while(c!='#'&&c!='.'); a[i][j]=c=='.';}
    	now=0,last=1,f[now][0][find(0)]=1;
    	for(int i=0;i<n;++i) for(int j=0;j<m;++j)
    	{
    		now^=1,last^=1,memset(f[now],0,sizeof f[now]);
    		int all=tot;
    		for(int k=0;k<=K;++k) for(int p=1;p<=all;++p) if(f[last][k][p])
    		{
    			auto DO=[&](int S,int V)->void{S=GetMin(S); if(k==K) return; f[now][k+V][find(S)]+=f[last][k][p];};
    			auto Check=[&](int S,int T)->bool{bool flag=0; for(int u=0;u<m;++u) flag|=(u!=j&&(S>>(u*offest)&mask)==T); return flag;};
    			
    			int state=content[p],left=j==0?0:state>>((j-1)*offest)&mask,up=state>>(j*offest)&mask;
    			if(!a[i][j])
    			{
    				if(up&&!Check(state,up)) continue;
    				DO(state^(up<<(j*offest)),0); continue;
				}
				if(!left&&!up) DO(state,0),DO(state^(7ll<<(j*offest)),1);
				else if(left&&!up) DO(state,0),DO(state^(left<<(j*offest)),1);
				else if(!left&&up) Check(state,up)?(DO(state,1),DO(state^(up<<(j*offest)),0)):(DO(state,1));
				else
				{
					if(Check(state,up)) DO(state^(up<<(j*offest)),0);
					int nstate=state;
    				for(int u=0;u<m;++u) if((nstate>>(u*offest)&mask)==up) nstate^=(up<<(u*offest))^(left<<(u*offest));
    				DO(nstate,1);
				}
			}
			for(int p=1;p<=tot;++p) if(f[now][K][p]) if(GetTyp(content[p])==1) ans+=f[now][K][p];
		}
		write(ans,'\n');
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

## 作者：lhs_chris (赞：0)

# 思路
首先我们可以想到暴搜。如果暴力搜索当前点是否染色，那么复杂度是很高的。我们记总点数 $m=n \times n$。那么复杂度为 $o(2^m)$，一定会超时。我们可以考虑换一种搜索的写法。

由于在上述的搜索过程中指数过高，考虑优化一下。我们可以先枚举第一个需要染色的点，然后循环枚举有意义的点进行搜索，总共跑 $k$ 次那么指数就变小了。但是还可以优化。

我们可以想到使用重复性剪枝。那么总的时间复杂度就是方案总数。我们可以看到方案总数并不算多。

那我们可以将整个地图压成一个字符串用 map 去重。需要注意的是 map 是有一个 $\log$ 的常数的，尽量不要在搜索中使用，但是这一题无法状压，只能使用 map。

# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
using namespace std;
const int N=5e5+10;
const int M=2147483647;
const int inf=0x3f3f3f3f;
int n,k;
char x;
int a[30][30];
int ans;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
string h;
map<string,int> mp;	
void init()
{
	h.clear();
	for(int i=0;i<=100;i++)h+='0';
//初始的string是空的
}
int change(int x,int y)
{
	return (x*10+y);
}
void dfs(int num)
{
	if(mp[h])
	{
		return;
	}
	mp[h]=1;
	if(num==k)
	{
		ans++;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==1)
			{
				int flag=0;
				for(int k=0;k<4;k++)
				{
					int nx=i+dx[k];
					int	ny=j+dy[k];
					if(nx>=1 and nx<=n and ny>=1 and ny<=n and a[nx][ny]==2)
					{
						flag=1;
						break;
					}
				}
				if(flag)
				{
					h[change(i,j)]='1';
					a[i][j]++;
					dfs(num+1);
					a[i][j]--;
					h[change(i,j)]='0';
				}
			}
		}
	}
}
int main()
{
	cin>>n>>k; 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			if(x=='.')
			{
				a[i][j]=1;
			} 
			else
			{
				a[i][j]=4;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==1)
			{
				init(); 
				h[change(i,j)]='1';
				a[i][j]++;
				dfs(1);
				a[i][j]--;
				h[change(i,j)]='0';
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：PDAST (赞：0)

一眼深搜，细节也不多，感觉像黄？
## 思路
看一眼数据范围，大概率深搜，再看一眼样例，极限情况下答案也没有超过 $10^{5}$，深搜无疑了。

每次枚举每个格子，看周边是否有红色的色块，若有，那么这个位置可行，染色后进入下一层，但是一定要记得回溯和判重。

对于判重，只需要将矩阵压缩成一个字符串，用 map 判一下就行了。
## 代码

```cpp
#include<bits/stdc++.h>
#define f(x,y) (x)*n+y
using namespace std;
string s,tmp;
map<string,int>mp;
int ans,n,t;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void dfs(int d){
//	cout<<d<<" "<<s<<"\n";
	if(mp[s])return ;
	mp[s]=1;
	if(d==0){
		ans++;
		return ;
	} 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(s[f(i,j)]=='.'){
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(x<0||x>=n||y<0||y>=n||s[f(x,y)]!='@')continue;
//					cout<<i<<" "<<j<<" "<<x<<" "<<y<<"\n";
					s[f(i,j)]='@';
					dfs(d-1);
					s[f(i,j)]='.';
				}
			}
		}
	}
}
signed main(){
//	freopen("a.txt","r",stdin);
	cin>>n>>t;
	for(int i=0;i<n;i++)cin>>tmp,s+=tmp;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(s[f(i,j)]=='.'){
				s[f(i,j)]='@';
				dfs(t-1);
				s[f(i,j)]='.';
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：Phoenix114514 (赞：0)

# AT_abc211_e [ABC211E] Red Polyomino
## 思路
因为数据规模不大，直接暴力。在 $N\times N$ 的方格中，若考虑所有格子，暴力会超时。但题目中说只需考虑红色的联通块，预测的就会少很多。虽然少了很多，但是还可以优化，比如判重。

题中让我们找出所有的可能，所以需要回溯，因为要枚举出起点，起点也要回溯。

算法：深度优先搜索（回溯）。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mxn=1010;
const int dx[]={0,-1,0,1};
const int dy[]={-1,0,1,0};//方向数组
map<string,bool> mp;//用一个map来记录这种涂法是否出现过
char g[mxn][mxn];//地图
int n,k,ans;
void dfs(int res){
    string s="";
    for (int i=0;i<n;i++)s+=g[i];//拼字符串
    if (mp[s])return;//判重
    mp[s]=1;
    if (!res){
        ans++;//这种涂法成立
        return;
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (g[i][j]=='.'){
                for (int k=0;k<4;k++){
                    int nx=i+dx[k];
                    int ny=j+dy[k];
                    if (g[nx][ny]=='r'&&nx>=0&&nx<n&&ny>=0&&ny<n){//条件一个不能少
                        g[i][j]='r';
                        dfs(res-1);
                        g[i][j]='.';//回溯
                    }
                }
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for (int i=0;i<n;i++)cin>>g[i];//输入地图
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (g[i][j]=='.'){
                g[i][j]='r';
                dfs(k-1);
                g[i][j]='.';//起点回溯
            }
        }
    }
    cout<<ans;
    return 0;
}
//完美收场！
```

---

## 作者：wmrqwq (赞：0)

本文同步在 [cnblog](https://www.cnblogs.com/wangmarui/p/18197697) 发布。

# 题目链接

[[ABC211E] Red Polyomino(luogu)](https://www.luogu.com.cn/problem/AT_abc211_e)

[[ABC211E] Red Polyomino(at)](https://atcoder.jp/contests/abc211/tasks/abc211_e)

# 解题思路

从第三个样例可以看出总的方案数一定很少，因此我们可以直接确定第一个被染色的格子后直接向外爆搜，搜到最后可以使用哈希判重，但光凭这样的话 $2$ 秒钟肯定跑不过去，因此我们可以在搜索的过程中使用哈希存储状态来剪枝，如果这个状态之前搜过了就不搜了。这样剪枝就足以通过此题了。

# 参考代码

这里使用双哈希。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
//#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,m,ans;
ll Base1=666,Base2=223;
ll mod1=1e9+9,mod2=998244353;
ll dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char a[10][10];
map<ll,map<ll,ll>>mp;
map<ll,map<ll,ll>>vis;
bool check(ll x,ll y){
	return x>=1 && x<=n && y>=1 && y<=n && a[x][y]=='.';
}
void check2()
{
	ll sum1=0,sum2=0;
/*	forl(i,1,n)
	{
		forl(j,1,n)
			cout<<a[i][j];
		cout<<endl;
	}
	cout<<endl;*/
	forl(i,1,n)
		forl(j,1,n)
			sum1*=Base1,sum1+=a[i][j]*(i*n+j),sum1%=mod1,
			sum2*=Base2,sum2+=a[i][j]*(i*n+j),sum2%=mod2;
	ans+=++mp[sum1][sum2]==1;
}
bool check3()
{
	ll sum1=0,sum2=0;
/*	forl(i,1,n)
	{
		forl(j,1,n)
			cout<<a[i][j];
		cout<<endl;
	}
	cout<<endl;*/
	forl(i,1,n)
		forl(j,1,n)
			sum1*=Base1,sum1+=a[i][j]*(i*n+j),sum1%=mod1,
			sum2*=Base2,sum2+=a[i][j]*(i*n+j),sum2%=mod2;
	if(vis[sum1][sum2])
		return 1;
	vis[sum1][sum2]=1;
	return 0;
}
void dfs(ll last)
{
	if(check3())
		return ;
	if(last==0)
	{
		check2();
		return ;
	}
	forl(x,1,n)
		forl(y,1,n)
			if(a[x][y]=='*')
				forl(i,0,3)
				{
					ll fx=x+dx[i],fy=y+dy[i];
					//cout<<fx<<","<<fy<<">>\n";
					if(check(fx,fy))
						a[fx][fy]='*',dfs(last-1),a[fx][fy]='.';
				}
}
void solve()
{
	cin>>n>>m;
	forl(i,1,n)
		forl(j,1,n)
			cin>>a[i][j];
	forl(i,1,n)
		forl(j,1,n)
			if(a[i][j]=='.')
				a[i][j]='*',dfs(m-1),a[i][j]='.';
	cout<<ans<<endl;
}
int main()
{
	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
	QwQ;
}

```

---

## 作者：majoego (赞：0)

这道题也很简单，由于数据范围非常小，所以我们只需要考虑最暴力的方式直接搜索。我们直接枚举每一个起点，然后对他进行 DFS，最多走 $k$ 步，当走到 $k$ 步的时候直接退出搜索，所以时间复杂度就是 $n^2 \times 4^k$，并且统计一下数量，数据非常充裕，所以可以通过本题。

[link](https://atcoder.jp/contests/abc211/submissions/51902225)。

---

