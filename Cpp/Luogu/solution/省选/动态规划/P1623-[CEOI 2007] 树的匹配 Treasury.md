# [CEOI 2007] 树的匹配 Treasury

## 题目描述

给一棵树，你可以匹配有边相连的两个点，问你这棵树的最大匹配是多少，并且计算出有多少种最大匹配。

## 说明/提示

$1\leq N\leq 10^3$，其中 $40\%$ 的数据答案不超过 $10^8$。

## 样例 #1

### 输入

```
7
1 3 2 4 7
2 1 3
4 1 6
3 0
7 1 5
5 0
6 0```

### 输出

```
3
4```

# 题解

## 作者：inexistent (赞：10)

人生第一道省选/NOI-（其实并没有，可能是因为码量有点大吧）的树形Dp，看着题解还是想了很久~~（个人认为官方的SOL有点扯）~~

-------------------

楼下提到f[i][1]>=f[i][0]，我也没法证明，但这其实本质上和这道题没关系，我们可以通过判断来解决。而且，楼下dalao的dfs里竟然是一个for语句的，而我写了4个……

首先树形Dp是很明显的，f[i][0]表示i的子树中，i不参与匹配的最大匹配数，同样f[i][1]表示i参与匹配的最大匹配数。这样第一个子问题的答案就是Max(f[1][0], f[1][1])。（题目给出的是无根树，我们就把1当根吧）

对于f[i][0]的转移很简单，既然i不参与匹配，那么f[i][0]就是它的每棵子树的最大匹配之和，因为显而易见，两个不同子树内的节点不可能匹配，所以每一个子树是独立的。所以，就是所有儿子v的Max(f[v][0],f[v][1])的总和。（子节点参不参与都没关系）

对于f[i][1]，情况稍稍复杂一点。由于i节点最多只能被匹配一次，所以我们可以这样来考虑。对于节点u，选择其中一个子节点v来和自己匹配，剩余的仍然取最大值，这样剩余的最大值很显然是f[u][0]-Max(f[v][0],f[v][1])，并且除了子节点v，v的其余儿子依然是独立的，所以再加上f[v][0]。所以转移方程即为f[u][1] = Max(f[u][1], f[u][0]-Max(f[v][0],f[v][1])+f[v][0]+1);

然后考虑第二个子问题，方案数怎么办？依然Dp。g[i][k]表示对应的f[i][k]的方案数。但注意了，答案不是g[1][1]，因为有可能f[1][0]==f[1][1]，这时候最大值有两个，所以答案是g[1][0]+g[1][1]。对于其他情况，输出f较大的那个就可以了。

还是先考虑g[i][0]如何转移，对于节点u，它由于是由各个子节点转移过来的，所以总的方案数就是各个子节点最大值方案数的积。还是一样，需要特判一下g[v][0] == g[v][1]的情况。

最难的也就是g[i][1]的转移了。对于这种情况，首先我们需要判断一下哪些节点与根匹配以后会转移出来最大值f[u][1]，而判断这个只需要按照前面的方程再推一遍看看是否相等就可以了。即if(f[u][0]-Max(f[v][0],f[v][1])+f[v][0]+1 == f[u][1])。而这时候，我们还是仿照前面的思维过程，但是注意方案数中除去一部分使用除法而不是减法（前面是由乘法转移过来的），加上也要改成乘上。并且还是要特判f[v][0]==f[v][1]的情况。具体见代码。

想出上面这些并不复杂，而我却在g的初始化上卡了将近一小时。一开始我把每个g[i][0]和g[i][1]都初始化为1，结果挂了。调试千百遍之后把g[i][1]的初始化删掉以后突然就对了。这个现在我是这样理解的，因为我的g[i][0]是要拿去直接乘的，显然不能先赋成0，不然推出来的g[i][0]就全是0了。并且g[i][1]是加的，刚开始如果就是1就会影响结果。这个只不过是一个非常牵强的理解，希望大神能给出证明……

另外这道题要高精也是非常坑的，既然高精模板那么多，我也不好意思盗版权，高精代码就不贴了。

```cpp
/*written by -=qxz=- */
////////////////////////////////此处省略200行
int n,u,m,v;
vector <int> G[N];
int f[N][2];
BigInteger g[N][2];
inline void AddEdge(int u, int v){
	G[u].push_back(v);
}
void DP(int u, int fa){
	int v,sz=G[u].size(),not_leaf=0;
	for(int i = 0; i < sz; ++i){
		if(G[u][i] == fa) continue;
		++not_leaf;
	}
	g[u][0] = 1;
	if(!not_leaf){
		return;
	} 
	for(int i = 0; i < sz; ++i){
		v = G[u][i];
		if(v == fa) continue;
		DP(v,u);
		f[u][0] += Max(f[v][0], f[v][1]);
		if(f[v][0] == f[v][1]) g[u][0] *= (g[v][0] + g[v][1]);
		else{
			if(f[v][0] > f[v][1]) g[u][0] *= g[v][0];
			if(f[v][1] > f[v][0]) g[u][0] *= g[v][1];
		}
	}
	f[u][1] = f[u][0];
	for(int i = 0; i < sz; ++i){
		v = G[u][i];
		if(v == fa) continue;
		f[u][1] = Max(f[u][1], f[u][0]-Max(f[v][0],f[v][1])+f[v][0]+1);
	}
	for(int i = 0; i < sz; ++i){
		v = G[u][i];
		if(v == fa) continue;
		if(f[u][0]-Max(f[v][0],f[v][1])+f[v][0]+1 == f[u][1]){
			if(f[v][0] == f[v][1] && g[v][0]+g[v][1] != 0){
				g[u][1] += g[u][0]/(g[v][0]+g[v][1])*g[v][0];
			} 
			else{
				if(f[v][0] > f[v][1] && g[v][0] != 0){
					g[u][1] += g[u][0]/(g[v][0])*g[v][0];
				} 
				if(f[v][1] > f[v][0] && g[v][1] != 0){
					g[u][1] += g[u][0]/(g[v][1])*g[v][0];
				} 
			}
		}
	}
}
int main(){
//	freopen(".in","r",stdin);
	read(n);
	for(int i = 1; i <= n; ++i){
		read(u);
		read(m);
		for(int j = 1; j <= m; ++j){
			read(v);
			AddEdge(u,v);
		}
	}
	DP(1,0);
	printf("%d\n",Max(f[1][0], f[1][1]));
	if(f[1][0] == f[1][1]) cout << g[1][0]+g[1][1];
	else{
		if(f[1][0] > f[1][1]) cout << g[1][0];
		if(f[1][1] > f[1][0]) cout << g[1][1];
	}
	return 0;
}

```

---

## 作者：I_AM_HelloWord (赞：6)

#### 这题很像P1411树+P1352没有上司的舞会。

#### 看看数据范围就是一个高精度问题，先考虑一下普通的dp方法。我们类似的设dp[u][0]表示在以u为根的子树中，不匹配u所能得到的最大匹配数，dp[u][1]表示在以u为根的子树中，u已经匹配了所等得到的最大匹配数，

#### 那么我们可以比较容易的得到：

#### dp[u][1]=sigma(max(dp[v][1],dp[u][0]+dp[v][0]+1))

#### dp[u][0]=sigma(max(dp[v][0],dp[v][1]))

#### 但是由于此题较（没有上司的舞会）来说，有一个非常特殊的地方，就是每个点的点权都是1，那么一般来说，dp[u][1]是不会小于dp[u][0]的，即dp[u][1]>=dp[u][0]对于每个u都是成立的。那么我们上面的dp[u][0]=max(dp[v][1])

#### 这里给出一个比较简单的证明：我们不取u，考虑u的子树中一个从u到一个叶子的路径，为了更好的证明，我们选择那条最长的边，我们的这个匹配最大的方案，在这个路径上必然是一条选了的边，接着一条不选的边，那我们对这些边做一个修改：把v和其一个儿子连边，然后把选了的边都删掉，把这些边的下端点连到下一个边的上端点，那么如果路径的长度是偶数，我们就会得到另一个和dp[v][0]匹配数相等的方案，如果路径是奇数，我们得到的就会比dp[v][0]多1个匹配边，可以自己画一个图方便理解。

#### 至于方案数，就和求一个序列中最大的数有多少个一样，我们先把dp[u][1],dp[u][0]搞出来，然后对于匹配数相同的直接用乘法原理搞一搞就行了。

#### 具体给个转移方程吧：设g[u][0]表示不选u的能得到最大匹配的方案数，g[u][1]类似。

#### 那么：对于g[u][0]，如果某个dp[v][0]!=dp[v][1]，那么就把g[u][0]\*=g[v][1],否则就是g[u][0]\*=g[v][1]+g[v][0]（这步还是比较好理解的）

#### 那么g[u][1]就差不多了。

#### 最后输出的时候就和转移的时候搞一个类似的特判，其他的就是要加一个高精度就行了。


#### 参考代码：


``` cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
const int N=1010;
struct Int{
    static const int Bit=1e4;
    int a[Bit],size;
    inline void operator = (const int &x){
        memset(a,0,sizeof(a));
        a[size=1]=x;
    }
    inline Int operator + (const Int t){
        Int c=*this;
        int sz=max(c.size,t.size);
        for (re int i=1;i<=sz;++i){
            c.a[i]+=t.a[i];c.a[i+1]+=c.a[i]/Bit;c.a[i]%=Bit;
        }
        if (c.a[sz+1])sz++;
        c.size=sz;
        return c;
    }
    
    inline Int operator * (const Int t){
        int sz=size+t.size-1;
        Int c;c=0;
        for (re int i=1;i<=size;++i)
            for (re int j=1;j<=t.size;++j)
                c.a[i+j-1]+=a[i]*t.a[j];
        for (re int i=1;i<=sz;i++)
            c.a[i+1]+=c.a[i]/Bit,c.a[i]%=Bit;
        if (c.a[sz+1])sz++;c.size=sz;
        return c;
    }
    inline void out(){
        printf("%d",a[size]);
        for (re int i=size-1;i;--i)
            printf("%04d",a[i]);
    }
}g[N][2];
int dp[N][2],n,a[N],to[N],next[N],EdgeCnt=0;
inline void operator *= (Int &a,Int b){a=a*b;}
inline void operator += (Int &a,Int b){a=a+b;}
inline int read(){
    re int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
inline void adde(int u,int v){
    int &p=EdgeCnt;
    to[++p]=v;next[p]=a[u];a[u]=p;
}
inline void dfs(int u){
    g[u][0]=1;g[u][1]=1;
    for (re int p=a[u];p;p=next[p]){
        int v=to[p];
        dfs(v);
        if (dp[u][1]){
            dp[u][1]+=dp[v][1];
            if (dp[v][0]^dp[v][1])g[u][1]*=g[v][1];
                else g[u][1]*=g[v][0]+g[v][1];
        }
        int t=dp[u][0]+dp[v][0]+1;
        if (t>dp[u][1]){
            dp[u][1]=t;g[u][1]=g[u][0]*g[v][0];
        }else if (t==dp[u][1]){
            g[u][1]+=g[u][0]*g[v][0];
        }
        dp[u][0]+=dp[v][1];
        if (dp[v][0]^dp[v][1])g[u][0]*=g[v][1];
            else g[u][0]*=g[v][0]+g[v][1];
    }
    if (!dp[u][1])g[u][1]=0;
}
int main(){
    n=read();
    for (int i=1;i<=n;++i){
        int u=read(),sz=read();
        for (int j=1;j<=sz;++j){
            int v=read();
            adde(u,v);
        }
    }
    dfs(1);
    printf("%d\n",dp[1][1]);
    if (dp[1][1]^dp[1][0])g[1][1].out();
        else (g[1][1]+g[1][0]).out();
    return 0;
}
```

---

## 作者：Adove (赞：5)

这题我想的方程跟dalao们不大一样啊

定义`f[3][MAXN]`

`f[0][x]`为以`x`为根子树与儿子连的最大匹配

`f[1][x]`为与`father`连的最大匹配

`f[2][x]`为独立时的最大匹配

`f[0][x]`转移就是从儿子中选一个与祖先连其他独立或连儿子

`f[1][x]`转移儿子们可以独立或连儿子，除根节点外初始为1

`f[2][x]`转移儿子可以不选或者连儿子，初始为0

计数时注意加法原理与乘法原理的运用

顺便贡献一个压九位高精板子

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1005;
const int MOD=1e9;

int n,np,maxn,root;
int fa[MAXN],h[MAXN];
int f[3][MAXN];
struct rpg{
	int li,nx;
}a[MAXN];
struct Big{
	long long v[25];
	
	void reset(){memset(v,0,sizeof(v));v[0]=1;}
	void write(){printf("%lld",v[v[0]]);for(int i=v[0]-1;i;--i) printf("%09lld",v[i]);puts("");}
	void pls(Big a,Big b){
		reset();
		v[0]=max(a.v[0],b.v[0])+1;
		for(int i=1;i<=v[0];++i){
			v[i]+=a.v[i]+b.v[i];
			if(v[i]>=MOD) v[i]-=MOD,++v[i+1];
		}if(!v[v[0]]&&v[0]>1) --v[0];
		return;
	}
	
	void mul(Big a,Big b){
		reset();
		v[0]=a.v[0]+b.v[0];
		for(int i=1;i<=a.v[0];++i){
			for(int j=1;j<=b.v[0];++j){
				v[i+j-1]+=a.v[i]*b.v[j];
				if(v[i+j-1]>=MOD) v[i+j]+=v[i+j-1]/MOD,v[i+j-1]%=MOD;
			}
		}while(!v[v[0]]&&v[0]>1) --v[0];
		return;
	}
}cnt[3][MAXN],ans;

void add(int ls,int nx){a[++np]=(rpg){h[ls],nx};h[ls]=np;}
void dfs(int x)
{
	f[1][x]=(bool)fa[x];
	for(int i=0;i<3;++i) cnt[i][x].reset();
	cnt[1][x].v[1]=cnt[2][x].v[1]=1;
	if(h[x]) cnt[0][x].v[1]=1;
	Big cl,ct;cl.reset();cl.v[1]=1;
	for(int i=h[x];i;i=a[i].li){
		dfs(a[i].nx);
		if(f[0][a[i].nx]==f[2][a[i].nx]) ct.pls(cnt[0][a[i].nx],cnt[2][a[i].nx]),cl.mul(cl,ct);
		if(f[0][a[i].nx]>f[2][a[i].nx]) cl.mul(cl,cnt[0][a[i].nx]);
		if(f[0][a[i].nx]<f[2][a[i].nx]) cl.mul(cl,cnt[2][a[i].nx]);
		f[1][x]+=max(f[0][a[i].nx],f[2][a[i].nx]);
		f[2][x]+=max(f[0][a[i].nx],f[2][a[i].nx]);
	}cnt[1][x]=cnt[2][x]=cl;
	for(int i=h[x];i;i=a[i].li){
		int mx=f[1][a[i].nx];
		Big clc=cnt[1][a[i].nx];
		for(int j=h[x];j;j=a[j].li){
			if(a[j].nx==a[i].nx) continue;
			if(f[0][a[j].nx]==f[2][a[j].nx]) ct.pls(cnt[0][a[j].nx],cnt[2][a[j].nx]),clc.mul(clc,ct);
			if(f[0][a[j].nx]>f[2][a[j].nx]) clc.mul(clc,cnt[0][a[j].nx]);
			if(f[0][a[j].nx]<f[2][a[j].nx]) clc.mul(clc,cnt[2][a[j].nx]);
			mx+=max(f[0][a[j].nx],f[2][a[j].nx]);
		}if(f[0][x]<mx) f[0][x]=mx,cnt[0][x]=clc;
		else if(f[0][x]==mx) cnt[0][x].pls(cnt[0][x],clc);
	}return;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int x,m;scanf("%d%d",&x,&m);
		while(m--){int y;scanf("%d",&y);fa[y]=x;add(x,y);}
	}for(int i=1;i<=n;++i) if(!fa[i]) root=i;
	dfs(root);maxn=max(f[0][root],f[2][root]);
	if(f[0][root]>f[2][root]) ans=cnt[0][root];
	if(f[0][root]==f[2][root]) ans.pls(cnt[0][root],cnt[2][root]);
	if(f[0][root]<f[2][root]) ans=cnt[2][root];
	printf("%d\n",maxn);ans.write();
	return 0;
}
```

NOIP2018 RP++

---

## 作者：xtx1092515503 (赞：4)

个人觉得树上背包的做法更为易懂，并且只需要高精度加法和乘法。

------------

我们令 $f[i,j,0/1]$ 表示 $i$ 的子树中有 $j$ 个匹配，且 $i$ 本身没有/有匹配的方案数。再令 $g[i,0/1]$ 表示没有/有匹配时的最大匹配数。显然，当合并父亲 $x$ 和儿子 $y$ 时，就直接拿 $f[x]$ 和 $f[y]$ 做一下背包即可。

注意，当父亲和儿子均没有匹配时（即 $f[x,?,0]$ 与 $f[y,?,0]$），它可以直接转移到 $f[x,?+?+1,1]$，即在父子间产生一对匹配（当然，也可以选择不用这一对匹配）。其余情况下，以父亲是否有匹配为准。

这里先贴出使用```long long```的 $60$ 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,g[1010][2];
ll f[1010][510][2],h[1010][2];
//f[i,j,0/1]:the number of situations when there're j matchings in subtree i and i itself isn't/is matched; and g is the maximal matchings. h is an array for assistance.
vector<int>v[1010];
bool occ[1010];
void dfs(int x){
	f[x][0][0]=1;
	for(auto y:v[x]){
		dfs(y);
		int tmp0=g[x][0]+max(g[y][0],g[y][1]),tmp1=max(g[x][1]+max(g[y][0],g[y][1]),g[x][0]+g[y][0]+1);
		for(int i=0;i<=tmp0;i++)h[i][0]=0;
		for(int i=0;i<=tmp1;i++)h[i][1]=0;
		for(int i=0;i<=g[x][0];i++)for(int j=0;j<=g[y][0];j++)h[i+j][0]+=f[x][i][0]*f[y][j][0],h[i+j+1][1]+=f[x][i][0]*f[y][j][0];
		for(int i=0;i<=g[x][1];i++)for(int j=0;j<=g[y][0];j++)h[i+j][1]+=f[x][i][1]*f[y][j][0];
		for(int i=0;i<=g[x][0];i++)for(int j=0;j<=g[y][1];j++)h[i+j][0]+=f[x][i][0]*f[y][j][1];
		for(int i=0;i<=g[x][1];i++)for(int j=0;j<=g[y][1];j++)h[i+j][1]+=f[x][i][1]*f[y][j][1];
		for(int i=0;i<=tmp0;i++)f[x][i][0]=h[i][0];
		for(int i=0;i<=tmp1;i++)f[x][i][1]=h[i][1];
		g[x][0]=tmp0;
		g[x][1]=tmp1;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y,z;i<=n;i++){
		scanf("%d%d",&x,&y);
		while(y--)scanf("%d",&z),v[x].push_back(z),occ[z]=true;
	}
	for(int i=1;i<=n;i++){
		if(occ[i])continue;
		dfs(i);
		int mx=max(g[i][0],g[i][1]);
		ll ret=0;
		if(mx==g[i][0])ret+=f[i][g[i][0]][0];
		if(mx==g[i][1])ret+=f[i][g[i][1]][1];
		printf("%d\n%lld\n",mx,ret);
	}
	return 0;
}
```

剩下的部分需要高精度。但明显，上述算法本身复杂度已经达到 $O(n^2)$，假如再套上高精度不大可能过去（根据极不靠谱的估算，高精度最大可能会有 $2^{333}\approx10^{100}$ 的位数，因为还要用乘法，所以就更不靠谱了）。当然，有胆大的可以尝试用FFT优化背包的卷积和高精度的卷积，但 $100,1000$ 这么点大的卷积可能用不用FFT效果都没啥区别。

那怎么办呢？

观察到我们只需要求最大的方案数。这意味着我们只需要记录最大值附近的几个DP值即可——剩余的DP值无论怎么搞都不可能最终成为最大值。于是这样搞正常DP的复杂度就被优化到了 $O(n)$。套上高精度，上限约是 $1000\times 100^2=10^8$ 的。但是很松，所以跑得很快。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,g[1010][2];
struct Wint:vector<int>{
	Wint(){clear();}
	Wint(int x){clear();while(x)push_back(x%10),x/=10;}
	void operator ~(){
		for(int i=0;i+1<size();i++)(*this)[i+1]+=(*this)[i]/10,(*this)[i]%=10;
		while(!empty()&&back()>9){
			int tmp=back()/10;
			back()%=10;
			push_back(tmp);
		}
		while(!empty()&&!back())pop_back();
	}
	void operator +=(const Wint &x){
//		print(),putchar('+'),x.print();
		if(size()<x.size())resize(x.size());
		for(int i=0;i<x.size();i++)(*this)[i]+=x[i];
		~*this;
//		putchar('='),print(),putchar('\n');
	}
	friend Wint operator *(const Wint &x,const Wint &y){
//		x.print(),putchar('*'),y.print();
		Wint z;
		if(!x.size()||!y.size())return z;
		z.resize(x.size()+y.size()-1);
		for(int i=0;i<x.size();i++)for(int j=0;j<y.size();j++)z[i+j]+=x[i]*y[j];
		~z;
//		putchar('='),z.print(),putchar('\n');
		return z;
	}
	void print()const{
		if(empty()){putchar('0');return;}
		for(int i=size()-1;i>=0;i--)putchar('0'+(*this)[i]);
	}
}f[1010][510][2],h[1010][2];
//f[i,j,0/1]:the number of situations when there're j matchings in subtree i and i itself isn't/is matched; and g is the maximal matchings. h is an array for assistance.
vector<int>v[1010];
bool occ[1010];
void dfs(int x){
	f[x][0][0]=1;
	for(auto y:v[x]){
		dfs(y);
		int tmp0=g[x][0]+max(g[y][0],g[y][1]),tmp1=max(g[x][1]+max(g[y][0],g[y][1]),g[x][0]+g[y][0]+1);
		for(int i=0;i<=tmp0;i++)h[i][0]=0;
		for(int i=0;i<=tmp1;i++)h[i][1]=0;
		for(int i=max(0,g[x][0]-1);i<=g[x][0];i++)for(int j=max(0,g[y][0]-1);j<=g[y][0];j++)h[i+j][0]+=f[x][i][0]*f[y][j][0],h[i+j+1][1]+=f[x][i][0]*f[y][j][0];
		for(int i=max(0,g[x][1]-1);i<=g[x][1];i++)for(int j=max(0,g[y][0]-1);j<=g[y][0];j++)h[i+j][1]+=f[x][i][1]*f[y][j][0];
		for(int i=max(0,g[x][0]-1);i<=g[x][0];i++)for(int j=max(0,g[y][1]-1);j<=g[y][1];j++)h[i+j][0]+=f[x][i][0]*f[y][j][1];
		for(int i=max(0,g[x][1]-1);i<=g[x][1];i++)for(int j=max(0,g[y][1]-1);j<=g[y][1];j++)h[i+j][1]+=f[x][i][1]*f[y][j][1];
		for(int i=max(0,tmp0-1);i<=tmp0;i++)f[x][i][0]=h[i][0];
		for(int i=max(0,tmp1-1);i<=tmp1;i++)f[x][i][1]=h[i][1];
		g[x][0]=tmp0;
		g[x][1]=tmp1;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y,z;i<=n;i++){
		scanf("%d%d",&x,&y);
		while(y--)scanf("%d",&z),v[x].push_back(z),occ[z]=true;
	}
	for(int i=1;i<=n;i++){
		if(occ[i])continue;
		dfs(i);
		int mx=max(g[i][0],g[i][1]);
		Wint ret;
		if(mx==g[i][0])ret+=f[i][g[i][0]][0];
		if(mx==g[i][1])ret+=f[i][g[i][1]][1];
		printf("%d\n",mx);
		ret.print();
	}
	return 0;
}
```

---

## 作者：ppp204 (赞：3)

~~才不会告诉你我高精调了一个下午~~

> 做法:树形DP+高精

我们假设$dp[i][0]$为访问编号为i的节点时,不与父亲配对时其子树上的最大对子,$dp[i][1]$为与父亲配对的最大对子

我们可以得到

$dp[i][1]=\sum^{n}_{i=1}dp[j][0]$

由于对于$dp[i][1]$我们需要找到跟他匹配的点,所以我们要找到$min\{dp[j][0]-dp[j][1]-1\}$，记为$mn$,再用$dp[i][1]-mn$表示$dp[i][0]$,即下面的方程

$dp[i][0]=dp[i][1]-min(0,min\{dp[j][0]-dp[i][1]-1\})$

那么问题来了：**上面为什么要对$0$与$min\{dp[j][0]-dp[i][1]-1\}$取min?**

这是为了防止我们将当前这个点**与任意子节点相连后,反而不如不与子节点相连的方案**，特地设置的$0$(即这个点即不连父节点，也不连子节点)。

由此，我们可以看出$dp[i][1]\leq dp[i][0]$,所以最后只需要输出$dp[1][0]$即可

那么让我们来来看看第二个问题:求出方案数

对于$f[i][0]$我们记为满足$dp[i][0]$的方案数,$f[i][1]$我们记为满足$dp[i][1]$的方案数

那么我们可以用类似于$dp[i]$的思想去分析。

对于满足$dp[i][1]$的方案数$f[i][1]$,那么就为$f[j][0]$方案数相乘(因为必定是从这些状态转移而来)

对于满足$dp[i][0]$的方案数$f[i][0]$,我们就需要找出满足$dp[j][0]-dp[j][1]-1==mn$的每一个j，然后$f[i][0]+=f[i][1]\div f[j][0]\times f[j][1]$(这里应该还好理解,就相当于把j匹配i，与上面相同)

最后，如果$mn==0$，则说明$dp[i][0]==dp[i][1]$,此时此刻我们可以知道$i$是不跟父亲节点连的。但是因为$mn==0$,则我们可以知道**如果它选择了一个子节点连接，反而方案 不优于 它不与子节点连**，所以我们可以看做父亲节点占用了这个节点(但实际上没有占用)，让子节点相连,这样既就能保证方案最优了。

#### Code:

```
#include<cstdio>
#include<vector>
using namespace std;
const int M=1000+5,base=1e8;
vector<int>Edge[M];
int n;
 
struct BigInt{
    int sum[21];
    void operator += (const BigInt &x){
        sum[0]=max(sum[0],x.sum[0]);
        for(int i=1; i<=sum[0]; i++){
            sum[i]+=x.sum[i];
            if(sum[i]>=base) sum[i+1]++,sum[i]-=base;
        }
        if(sum[sum[0]+1]>0) sum[0]++;
    }
    void operator *= (const BigInt &x){
        long long A[21]={};
        for(int i=1; i<=sum[0]; i++){
            for(int j=1; j<=x.sum[0]; j++){
                A[i+j-1]+=1ll*sum[i]*x.sum[j];
            }
        }
        for(int i=1; i<=sum[0]+x.sum[0]; i++){
            A[i+1]+=A[i]/base; A[i]%=base; sum[i]=A[i];
        }
        if(A[sum[0]+x.sum[0]]) sum[0]=sum[0]+x.sum[0];
        else sum[0]=sum[0]+x.sum[0]-1;
    }
    void Print(){
        printf("%d",sum[sum[0]]);
        for(int i=sum[0]-1; i>0; i--){
            printf("%08d",sum[i]);
        }
    }
}f[M][2],f1[M],f2[M],fnow;//f1-->前缀累乘,f2-->后缀累乘,方便接下来状态转移的乘法(不用枚举子点或者写高精除)
 
int dp[M][2]; //dp[i][0]-->不跟父亲连, dp[i][1] --> 跟父亲连
 
void dfs(int x){
    int mn=0,sz=Edge[x].size();
    f[x][0].sum[0]=f[x][1].sum[0]=f[x][1].sum[1]=1,f[x][0].sum[1]=0;
    for(int i=0; i<sz; i++){
        int y=Edge[x][i]; dfs(y);
        dp[x][0]+=dp[y][0], dp[x][1]+=dp[y][0];
        f[x][1]*=f[y][0];
        mn=min(mn,dp[y][0]-dp[y][1]-1);
    }
    dp[x][0]-=mn;
    f1[0].sum[0]=f1[0].sum[1]=f2[sz].sum[0]=f2[sz].sum[1]=1;
    for(int i=0; i<sz; i++) f1[i+1]=f1[i],f1[i+1]*=f[Edge[x][i]][0];
    for(int i=sz-1; i>=0; i--) f2[i]=f2[i+1],f2[i]*=f[Edge[x][i]][0];
    for(int i=0; i<sz; i++){
        int y=Edge[x][i];
        if(dp[y][0]-dp[y][1]-1==mn){
            fnow=f[y][1], fnow*=f1[i]; fnow*=f2[i+1]; f[x][0]+=fnow;
        }
    }
    if(!mn) f[x][0]+=f[x][1];
}
 
int main(){
    scanf("%d",&n);
    for(int i=1,x,y,sz; i<=n; i++){
        scanf("%d %d",&x,&sz);
        for(int j=1; j<=sz; j++){
            scanf("%d",&y);
            Edge[x].push_back(y);
        }
    }
    dfs(1);
    printf("%d\n",dp[1][0]);
    f[1][0].Print();
    return 0;
}
```

---

## 作者：wwlw (赞：2)

[Link](https://www.luogu.com.cn/problem/P1623)
----------------

### 题目描述
给一棵树，你可以匹配有边相连的两个点，问你这棵树的最大匹配是多少，并且计算出有多少种最大匹配。

### 解法
容易想到将边的匹配转换到点上面，用 $dp_{u,0/1}$ 表示以节点 $u$ 为根节点的子树中，不选/选 $u$ 节点来匹配得到的最大匹配数。

那么当 $u$ 没有被选时，子节点选不选都无所谓

我们令
$$f_u=max\{dp_{u,0},dp_{u,1}\}$$
则有
$$dp_{u,0}=\sum_{v\in son(u)} f_v$$

若选择 $u$，则只有被选的那条边的那个子节点必不能选，其他节点选不选无所谓，则
$$dp_{u,1}=max\{dp_{u,0}-f_v+dp_{v,0}+1\}$$

第一问这样做已经可以了，难点在于第二问——记录方案。

由第一问，我们得到启发，用 $g_{u,0/1}$ 表示以节点 $u$ 为根节点的子树中，不选/选 $u$ 节点来匹配得到的最大匹配数的方案数。

若不选择 $u$ 节点，则由乘法原理将所有的子节点对应的方案的方案数乘起来即可

令
$$h_u=\begin{cases}
g_{u,0}, & dp_{u,0}>dp_{u,1} \\
g_{u,0}+g_{u,1}, & dp_{u,0}=dp_{u,1}\\
g_{u,1}, & dp_{u,0}<dp_{u,1}
\end{cases}$$

则
$$g_{u,0}=\prod_{v\in son(u)} h_v$$

而对于 $g_{u,1}$ 我们需要在更新 $dp_{u,1}$ 的时候同时更新它。假设我们当前选的边为 $u\to v$ ，那么除了 $v$ 之外的其它子节点都可以任意选，而不选 $v$ 节点对应的方案数为 $g_{v,0}$，那么总的方案数为 $g_{u,0}/h_v\times g_{v,0}$。若 $dp_{u,1}<dp_{u,0}-f_v+dp_{v,0}+1$，即
我们找到了一个更大的匹配，那么直接将 $g_{u,1}$ 更新为 $g_{u,0}/h_v\times g_{v,0}$；若 $dp_{u,1}=dp_{u,0}-f_v+dp_{v,0}+1$，即我们找到了一个和最大匹配方案数相同的方案，那么将 $g_{u,1}$ 累加上这个值即可。

```cpp
for(int i=head[u];i;i=e[i].next){
    int v=e[i].to;
    ll ret=dp[u][0]-f[v]+dp[v][0]+1;
    ll tmp=g[u][0]/h[v]*g[v][0];
    if(dp[u][1]<ret) dp[u][1]=ret,g[u][1]=tmp;
    else if(dp[u][1]==ret) g[u][1]+=tmp;
}
```

###Tips 
我们发现最后的方案数超过了 $long long$，需要些高精。然而方程中带了除法QAQ，此时需要一些转换。观察方程，发现所求值是一个总积除上中间一个数的形式，实际上可以把其转换为一个前缀积和一个后缀积相乘，完美的避开了除法。（如果你不想再重载减法的话，也可以把其转换为前缀和加后缀和）

```cpp
#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define N 1007

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

inline int max(int x,int y){return x>y? x:y;}

struct BigNum{
    int n,s[207];
    
    BigNum(int x=0){
        n=0;
        memset(s,0,sizeof(s));
        while(x) s[++n]=x%10,x/=10;
    }
    
    BigNum operator *(const BigNum B){
        BigNum c;
        c.n=B.n+n-1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=B.n;j++){
                c.s[i+j-1]+=s[i]*B.s[j];
                c.s[i+j]+=c.s[i+j-1]/10;
                c.s[i+j-1]%=10;
            }
        while(c.s[c.n+1]) c.n++;
        while(c.n>=1&&(!c.s[c.n])) c.n--;
        return c;
    }
    
    BigNum operator +(const BigNum B){
        BigNum c;
        c.n=max(B.n,n);
        for(int i=1;i<=c.n;i++){
            c.s[i]+=s[i]+B.s[i];
            c.s[i+1]=c.s[i]/10;
            c.s[i]%=10;
        }
        while(c.s[c.n+1]) c.n++;
        while(c.n>=1&&(!c.s[c.n])) c.n--;
        return c;
    }
    
    bool operator <(const BigNum B){
        if(n!=B.n) return n<B.n;
        for(int i=n;i>=1;i--)
            if(s[i]!=B.s[i]) return s[i]<B.s[i];
        return 0;
    }
    
    bool operator ==(BigNum B){
        return !(((*this)<B)|(B<(*this)));
    }
    
    void print(){
        if(!n) putchar('0');
        else for(int i=n;i>=1;i--) putchar(s[i]+'0');
        putchar('\n');
    }
    
}f[N],g[N][2],h[N],dp[N][2],pre[N],suf[N],pres[N],sufs[N];

int n;
bool vis[N];
vector<int> G[N];

void dfs(int u){
    vis[u]=1,g[u][0]=BigNum(1);
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!vis[v]) dfs(v);
        dp[u][0]=dp[u][0]+f[v];
        g[u][0]=g[u][0]*h[v];
    }
    pre[0]=BigNum(1);
    pres[0]=BigNum(0);
    for(int i=0;i<G[u].size();i++)
        pres[i+1]=pres[i]+f[G[u][i]],
        pre[i+1]=pre[i]*h[G[u][i]];
    suf[G[u].size()+1]=BigNum(1);
    sufs[G[u].size()+1]=BigNum(0);
    for(int i=G[u].size()-1;~i;i--)
        sufs[i+1]=sufs[i+2]+f[G[u][i]],
        suf[i+1]=suf[i+2]*h[G[u][i]];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        BigNum r(1);
        BigNum ret=pres[i]+sufs[i+2]+dp[v][0]+r;
        BigNum tmp=pre[i]*suf[i+2]*g[v][0];
        if(dp[u][1]<ret) dp[u][1]=ret,g[u][1]=tmp;
        else if(dp[u][1]==ret) g[u][1]=g[u][1]+tmp;
    }
    if(dp[u][0]<dp[u][1]) f[u]=dp[u][1],h[u]=g[u][1];
    else if(dp[u][0]==dp[u][1]) f[u]=dp[u][0],h[u]=g[u][0]+g[u][1];
    else f[u]=dp[u][0],h[u]=g[u][0];
}

signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++){
        int u=read(),op=read();
        for(int i=1;i<=op;i++)
            G[u].push_back(read());
    }
    BigNum ans(0),ret(1);
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs(i);
        if(ans<f[i]) ans=f[i],ret=h[i];
    }
    ans.print(),ret.print(); 
}
```

---

## 作者：Smallbasic (赞：2)

考场A了纪念一下。

最大匹配的部分很显然，我们设$\text{f[i][0/1]}$表示第$i$个点是否和他的爸爸匹配。因为这个点和他爸爸匹配之后他的儿子不能和它匹配，所以有：

$$\text{f[i][1]}=\sum_{j\in son_i}\text{f[j][0]+1}$$

$\text{f[i][0]}$的部分要麻烦一点，我们枚举他的哪个儿子和它匹配，或者根本没有儿子和它匹配即可。

至于计数我们在dp的时候另开数组$\text{g[i][0/1]}$，dp出$\text{f}$之后枚举由那些点转移可以得到相同的结果，再用乘法原理或加法原理计数即可。

具体的，对于$\text{g[i][1]}$

$$\text{g[i][1]}=\prod_{j\in son_i}\text{g[j][0]}$$

我们设$\text{mx}=\prod_{j\in son_i}\text{f[j][0]}$，则对于$\text{g[i][0]}$

$$\text{g[i][0]}=\sum_{\text{j是最优转移点}}{\text{mx} \cdot \text{g[j][1]}\over \text{g[j][0]}}$$

最后还要判儿子都不和它匹配的情况。

这样我们大致思路就已经讲完了。但是这题要恶心的写高精，而且带除法。

所以我们能否避免高精除高精？我是每次直接暴力重算，但是被机房大佬喷会被菊花图上挂很多链卡。实际上可以每次额外记一个前缀积和后缀积。

还有些细节就看代码吧：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct BigInteger {
	int len;
	short int ch[1005];
	BigInteger() { len = 0; memset(ch, 0, sizeof ch); }
	inline void print() {
		for (int i = len; i; --i) printf("%d", ch[i]);
	}
	inline void prepare(const int b) {
		int k = b; len = 0;
		while (k) { ch[++len] = k % 10; k /= 10; }		
	}
};

inline int max_(int a, int b) {
	return a > b ? a : b;
} 

inline BigInteger operator + (BigInteger a, BigInteger b) {
	BigInteger c; c.len = max_(a.len, b.len);
	for (int i = 1; i <= c.len; ++i) {
		c.ch[i] += a.ch[i] + b.ch[i];
		if (c.ch[i] >= 10) c.ch[i + 1] += c.ch[i] / 10, c.ch[i] %= 10;
	} while (c.ch[c.len + 1] != 0) ++c.len;
	return c;
}

inline BigInteger operator * (BigInteger a, int b) {
	BigInteger c; c.len = a.len;
	for (int i = 1; i <= c.len; ++i) {
		c.ch[i] += a.ch[i] * b;
		if (c.ch[i] > 10) c.ch[i + 1] += c.ch[i] / 10, c.ch[i] %= 10;
	} while (c.ch[c.len + 1] != 0) ++c.len;
	return c;
}

inline BigInteger operator << (BigInteger a, int c) {
	BigInteger b; b = a;
	for (int i = b.len; i; --i) swap(b.ch[i], b.ch[i + c]);
	b.len += c;
	return b;
}

inline BigInteger operator * (BigInteger a, BigInteger b) {
	BigInteger c; c.prepare(0);
	for (int i = 1; i <= b.len; ++i) { 
		c = c + ((a * b.ch[i]) << (i - 1));
	} return c;
}

vector<int> nxt[1005];
int n, m, v, fr, f[1005][2], fa[1005], rt;
BigInteger g[1005][2];

inline void dfs(int now) {
	f[now][0] = 0; f[now][1] = (fa[now] != -1);
	g[now][1].prepare(1);
	vector<int> :: iterator it;
	int mx0 = 0, mx1 = 0;
	BigInteger gx0, gx1; gx0.prepare(1); gx1.prepare(1);
	for (it = nxt[now].begin(); it != nxt[now].end(); ++it) {
		dfs(*it);
		f[now][1] += f[*it][0];
		gx1 = gx1 * g[*it][0];
		mx0 += f[*it][0];
		g[now][0].prepare(0);
	} g[now][1] = gx0 = gx1; f[now][0] = mx0;
	for (it = nxt[now].begin(); it != nxt[now].end(); ++it)
		f[now][0] = f[now][0] > (mx0 - f[*it][0] + f[*it][1]) ? f[now][0] : (mx0 - f[*it][0] + f[*it][1]);
	for (it = nxt[now].begin(); it != nxt[now].end(); ++it) {
		if(f[now][0] == (mx0 - f[*it][0] + f[*it][1])) {
			gx1.prepare(1);
			for (vector<int> :: iterator iv = nxt[now].begin(); iv != nxt[now].end(); ++iv) {
				if (*iv == *it) gx1 = gx1 * g[*iv][1];
				else gx1 = gx1 * g[*iv][0];
			}
			g[now][0] = g[now][0] + gx1;
		}
	}if (f[now][0] == mx0) g[now][0] = g[now][0] + gx0;
//	cout << "now = " << now << endl;
//	cout << f[now][0] << ' ' << f[now][1] << endl;
//	cout << g[now][0] << ' ' << g[now][1] << endl;
//	cout << "mx = " << mx0 << ' ' << "gx = " << gx0 << endl; 
	
}

int main() {
	scanf("%d", &n); memset(fa, -1, sizeof fa);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &fr, &m);
		while (m--) {
			scanf("%d", &v);
			nxt[fr].push_back(v);
			fa[v] = fr;
		}
	}
	for (int i = 1; i <= n; ++i)
		if (fa[i] == -1) {
			rt = i; break;
		}
	dfs(rt);
	printf("%d\n", f[rt][0]);
	g[rt][0].print();
	return 0;
}
```


---

## 作者：DengDuck (赞：1)

死因：高精加边界写错了。

动态规划比较显然。

我们设 $f_{i,0/1}$ 表示 $i$ 子树内，根节点是否匹配的最大匹配数，$g_{i,0/1}$ 则是对应的方案数。

$$
\begin{aligned}
f_{x,0}&=\sum_{i\in xson}{\max(f_{i,0},f_{i,1})}\\
f_{x,1}&=\max_{i\in xson}(f_{i,0}+1+\sum_{j\in xson,j\not=i}\max(f_{j,0},f_{j,1}))\\
\end{aligned}
$$

$g_{i,0/1}$ 的推导根据上面的式子，从最优策略那里继承答案即可。

为了避免除法，我们可以考虑求出一个节点 $x$ 的儿子的 $g$ 值前缀积后缀积，拼一拼就行。

这个显然是 $\mathcal O(n)$，但是不要忽视高精度的巨大常数。


```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;
const LL M=1005;
const LL N=1005;
struct Num
{
	short num[M],len;
	Num(const LL x=0):len(x)
	{
		memset(num,0,sizeof(num));
	}
	void operator=(const Num&x)
	{
		len=x.len;
		memset(num,0,sizeof(num));
		for(int i=0;i<len;i++)num[i]=x.num[i];
	}
	void operator=(LL x)
	{
		memset(num,0,sizeof(num));
//		cout<<"Get"<<x<<endl;
		if(x==0)
		{
			len=1;
			return;
		}
		len=0;
		while(x)
		{
			num[len++]=x%10;
			x/=10;
		}
		
	}
	void operator*=(LL x)
	{
		for(int i=0;i<len;i++)
		{
			num[i]*=x;
		}
		len+=10;
		for(int i=0;i<len;i++)
		{
			num[i+1]+=num[i]/10;
			num[i]%=10;
		}
		while(num[len-1]==0&&len)len--;
	}
	void operator+=(const Num&x)
	{
		Num ans(x.len+len+10);
		for(int i=0;i<len||i<x.len;i++)
		{
			ans.num[i]+=num[i]+x.num[i];
		}
		for(int i=0;i<ans.len;i++)
		{
			ans.num[i+1]+=ans.num[i]/10;
			ans.num[i]%=10;
		}
		len=ans.len;
		memset(num,0,sizeof(num));
		for(int i=0;i<len;i++)num[i]=ans.num[i];
		while(num[len-1]==0&&len>1)len--;		
	}
	void operator*=(const Num&x)
	{
		Num ans(x.len+len+5);
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<x.len;j++)
				ans.num[i+j]+=num[i]*x.num[j];
		}
		for(int i=0;i<ans.len;i++)
		{
			ans.num[i+1]+=ans.num[i]/10;
			ans.num[i]%=10;
		}
		len=ans.len;
		memset(num,0,sizeof(num));
		for(int i=0;i<len;i++)num[i]=ans.num[i];
		while(num[len-1]==0&&len>1)len--;		
	}
	void print()
	{
		for(int i=len-1;i>=0;i--)
		{
			putchar(num[i]+'0');
		}
	}
};
LL n,f[N][2],pre[N],suf[N];
Num Suf[N],Pre[N];
Num g[N][2];
vector<LL>v[N];
void dfs(LL x)
{
	g[x][0]=1,g[x][1]=0;
	for(LL i:v[x])
	{
		dfs(i);
		f[x][0]+=max(f[i][1],f[i][0]);
		Num t;
		t=0;
		if(f[i][1]>=f[i][0])t+=g[i][1];
		if(f[i][0]>=f[i][1])t+=g[i][0];
		g[x][0]*=t;
	}
	LL sum=0;
//	cout<<"Prepare"<<endl;
	Num cnt;
	cnt=1;
//	cout<<"Cnt";
//	cout<<cnt.len<<' '<<cnt.num[0]<<' ';
//	cnt.print();
//	cout<<endl;
	for(LL i:v[x])
	{
		pre[i]=sum,Pre[i]=cnt;
//		cout<<"Pre"<<i<<' ';
//		Pre[i].print();
//		cout<<endl;
		sum+=max(f[i][1],f[i][0]);
		Num t;
		t=0;
		if(f[i][1]>=f[i][0])t+=g[i][1];
		if(f[i][0]>=f[i][1])t+=g[i][0];
		cnt*=t;
	}
	reverse(v[x].begin(),v[x].end());
	sum=0;
	cnt=1;
	for(LL i:v[x])
	{
		suf[i]=sum,Suf[i]=cnt;
		sum+=max(f[i][1],f[i][0]);
		Num t;
		t=0;
		if(f[i][1]>=f[i][0])t+=g[i][1];
		if(f[i][0]>=f[i][1])t+=g[i][0];
		cnt*=t;
	}	
	for(LL i:v[x])
	{
		f[x][1]=max(f[x][1],suf[i]+pre[i]+f[i][0]+1);
	}
	for(LL i:v[x])
	{
		if(f[x][1]==suf[i]+pre[i]+f[i][0]+1)
		{
			Num k=Suf[i];
			k*=Pre[i];
//			cout<<i<<' ';
//			Suf[i].print();
//			cout<<' ';
//			Pre[i].print();
//			cout<<' ';
//			k.print();
//			cout<<endl;
			k*=g[i][0];
			g[x][1]+=k;
		}
//		cnt.print();
//		cout<<endl;
	}
//	cout<<x<<' '<<f[x][0]<<' ';
//	g[x][0].print();
//	cout<<' '<<f[x][1]<<' ';
//	g[x][1].print();
//	cout<<endl;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		LL x,m;
		scanf("%lld%lld",&x,&m);
		for(int j=1;j<=m;j++)
		{
			LL y;
			scanf("%lld",&y);
			v[x].pb(y);
		}
	}
	dfs(1);
	LL ans=max(f[1][0],f[1][1]);
	printf("%lld\n",ans);
	Num cnt;
	cnt=0;
//	cout<<f[1][0]<<' '<<f[1][1]<<endl;
	if(ans==f[1][0])cnt+=g[1][0];
	if(ans==f[1][1])cnt+=g[1][1];
	cnt.print();
}
```

---

## 作者：XuYueming (赞：0)

## 前言

[更好的体验](https://www.cnblogs.com/XuYueming/p/18295437)。

## 题目简述

给一棵树，问你这棵树的最大匹配是多少，并且计算出有多少种最大匹配。

## 题目分析

先来考虑较简单的最大匹配数。对于某一个结点，它有以下三种状态：

1. 不参与匹配；
1. 和某一个儿子匹配；
1. 和父亲匹配。

考虑使用树形 DP，我们发现，只需要知道一个孩子，和或不和自己匹配的最大匹配是多少，也即，在 DP 时，前两种状态在向上合并时是相同的——都不能和父亲构成一个新的匹配。那我们就可以记 $f[i][0 / 1]$ 表示 $i$ 这个点，能或不能和父亲匹配构成的最大匹配数。为了方便，我们把一个匹配的贡献记在孩子上。那么答案 $ans = f[root][0]$。接下来考虑递推式。

以下考虑对于一个结点 $yzh$ 和其一个孩子 $xym \in \operatorname{son}(yzh)$。

对于 $f[yzh][1]$，即 $yzh$ 可以和她父亲合并，那么她不能和她的孩子构成匹配。也就是只能从孩子的 $f[xym][0]$ 转移而来。

$$
f[yzh][1] = 1 + \sum f[xym][0]
$$

对于 $f[yzh][0]$，即 $yzh$ 可以不参与匹配，或者和某一个孩子构成匹配，相应转移即可。

$$
\begin{aligned}
f[yzh][0] &= \max \Bigg \lbrace \sum f[xym][0], \sum f[xym][0] + \max \lbrace f[xym][1] - f[xym][0] \rbrace \Bigg \rbrace  \\
          &= \sum f[xym][0] + \max \lbrace f[xym][1] - f[xym][0] \rbrace \cup \lbrace 0 \rbrace
\end{aligned}
$$

对于方案数，我们再记 $g[i][0 / 1]$，转移时把 $\sum$ 变成 $\prod$ 即可。

$$
g[yzh][1] = \prod g[xym][0]
$$

如果 $f[yzh][0]$ 在不和任何一个儿子匹配时取得 $\max$，

$$
g[yzh][0] = \prod g[xym][0]
$$

如果和某一个孩子 $xym' \in \operatorname{son}(yzh)$ 匹配时取得 $\max$，

$$
g[yzh][0] = g[xym'][1] \prod _ {xym \neq xym'} g[xym][0]
$$

注意，如果有多个 $xym'$ 满足，应根据加法原理对 $g[yzh][0]$ 累加；如果 $f[xym'][1] = f[xym'][0]$，在不参与匹配的方案数也要累加进来。

最后注意到题目最后一句话：

> 其中 $40\%$ 的数据答案不超过 $10^8$。

我们要使用高精度存 $g$ 的答案。有个 trick，$\prod \limits _ {xym \neq xym'}$ 可以用前后缀积来优化。

## 代码

略去了高精度 `BigInteger` 的实现。

```cpp
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

int n;
vector<int> edge[1010];
BigInteger g[1010][2];
int f[1010][2];

void dfs(int now) {
	f[now][1] = 1, g[now][1] = 1;
	unsigned mx = 0, son = 0;
	for (unsigned i = 0; i < edge[now].size(); ++i) {
		int to = edge[now][i];
		++son, dfs(to);
		f[now][1] += f[to][0], g[now][1] *= g[to][0];
		if (f[to][1] - f[to][0] > f[edge[now][mx]][1] - f[edge[now][mx]][0])
			mx = i;
	}
	if (!son) return g[now][0] = 1, void();
	f[now][0] = f[now][1] - 1 + f[edge[now][mx]][1] - f[edge[now][mx]][0];
	static BigInteger suf[1010]; suf[edge[now].size()] = 1;
	for (unsigned i = edge[now].size() - 1; ~i; --i)
		suf[i] = suf[i + 1] * g[edge[now][i]][0];
	BigInteger pre = 1;
	for (unsigned i = 0; i < edge[now].size(); ++i) {
		int to = edge[now][i];
		if (f[to][1] - f[to][0] == f[edge[now][mx]][1] - f[edge[now][mx]][0])
			g[now][0] += pre * suf[i + 1] * g[to][1];
		pre *= g[edge[now][i]][0];
	}
	if (f[edge[now][mx]][1] - f[edge[now][mx]][0] == 0)
		g[now][0] += g[now][1];
}

signed main(){
	scanf("%d", &n);
	for (int i = 1, u, v, k; i <= n; ++i) {
		scanf("%d%d", &u, &k);
		while (k--) scanf("%d", &v), edge[u].push_back(v);
	}
	dfs(1);
	printf("%d\n", f[1][0]);
	printf("%s", string(g[1][0]).c_str());
	return 0;
}
```

## 后记 & 反思

一道很水的题目，但是模拟赛时没写出来，寄。

---

