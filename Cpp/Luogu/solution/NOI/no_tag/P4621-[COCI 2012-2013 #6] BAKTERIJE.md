# [COCI 2012/2013 #6] BAKTERIJE

## 题目描述

一个 $N$ 行，$M$ 列的矩形区域，行从上到下从 $1$ 到 $N$ 编号，列从左到右从 $1$ 到 $M$ 编号，有 $K$ 个细菌被放在这些单元格内，每个细菌都有自己的方向和运动规则。规则如下：读取自己在这个单元格的数字 $X$，顺时针转 $90^{\circ}$ $X$ 次，如果它面对矩形边界，则转 $180^{\circ}$，最后进入自己面向的单元格。我们放置一个陷阱在某一单元格，当所有细菌同时进入陷阱时，陷阱被激活，细菌会在一秒内被消灭。

给定所有信息，求什么时候所有细菌被消灭。

## 说明/提示

$3\leq N\leq 50$，$3\leq M \leq 50$，$1\leq K\leq 5$。

## 样例 #1

### 输入

```
3 3 1
2 2
1 1 R
010
000
000```

### 输出

```
3```

## 样例 #2

### 输入

```
3 4 2
2 2
3 4 R
2327
6009
2112
3 2 R
1310
2101
1301```

### 输出

```
8```

## 样例 #3

### 输入

```
4 4 3
4 3
1 1 U
1001
0240
3322
2327
1 3 L
9521
2390
3020
2421
2 2 D
3397
2013
1102
7302```

### 输出

```
296```

# 题解

## 作者：tzc_wk (赞：10)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P4621)

发篇正常点的题解。

首先对于这样的题暴力枚举肯定是不行的，因为最小时间显然可能达到 $(4nm)^5\approx 10^{20}$，就算数据很难卡到这个上界，构造出一些使你暴力超时的数据还是很容易的，因此考虑一些不基于暴力枚举的做法。不难发现，对于每个细菌而言，如果它的位置及方向已经确定了，那么它下一步所在的位置及面对的方向也已经确定了，也就是说，如果我们对于每个细菌，把位置及方向看作一个三元组 $(x,y,d)$，并且在一步可达的三元组之间连有向边，那么可以得到 $k$ 个基环内向森林。而由于得到的图是基环内向森林，对于一个点，从它出发可以到达的点应是一个 $\rho$ 形。而对于陷阱格 $(x,y)$，到达陷阱格即意味着在建好的图上到达 $(x,y,0),(x,y,1),(x,y,2),(x,y,3)$ 中的一个点，因此题目可以转化为：

- 求最小的时间 $t$，满足对于全部全部 $k$ 个基环内向森林的起点，走 $t$ 步后到达的点都是 $(x,y,0),(x,y,1),(x,y,2),(x,y,3)$ 中的一个

由于此题 $k$ 很小，因此我们考虑暴力 $4^k$ 枚举每个细菌的终点 $(x,y,d_i)$，那么问题可进一步转化为，最少需要多少时间 $t$，满足每个细菌走 $t$ 步后到达的点都恰好是 $(x,y,d_i)$。我们对于每个细菌 $i$，预处理出以下四个量：

- $mn_i$：从该细菌起点对应的三元组开始，最少走多少步可以走到环上
- $len_i$：从该细菌起点对应的三元组开始，能够走到的 $\rho$ 字形的环长
- $typ_{i,d}$：对于终点 $(x,y,d)$，它在不在该细菌对应的起点能够走到的 $\rho$ 字形的环上
- $tim_{i,d}$：对于终点 $(x,y,d)$，最少需要多少时间才能从细菌 $i$ 起点对应的三元组走到 $(x,y,d)$

那么显然如果存在一个 $(x,y,d_i)$ 无法从 $i$ 的起点到达那么就不存在这样的 $i$，否则继续分类讨论：如果存在一个 $(x,y,d_i)$ 不在细菌 $i$ 的起点对应的环上，那么显然时间必须为 $tim_{i,d_i}$，因为错过这个点就无法再回来了，我们只需检验从所有细菌的起点开始走 $T=tim_{i,d_i}$ 步是否能够到达对应的终点即可，如果都能那么就用 $T$ 更新答案，否则不做处理。具体检验方法就是如果 $typ_{i,d_i}=1$，那么必须有 $T\ge mn_i$ 且 $T\equiv tim_{i,d_i}\pmod{len_i}$，否则必须有 $tim_{i,d_i}=T$，存在 $typ_{i,d_i}=0$ 的情况都判完了，剩余的就是 $typ_{i,d_i}$ 都为 $1$ 的情况了。对于每个细菌 $i$，显然它在 $T$ 时刻到达 $(x,y,d_i)$ 的充要条件是 $T\ge mn_i$ 且 $T\equiv tim_{i,d_i}\pmod{len_i}$。我们如果只考虑后一个条件，那显然就是一个解同余方程组的问题，exCRT 合并即可，加了第一个条件，由于方程组的通解可以写成 $T=T_0+kT'$ 的形式，因此我们对于每个细菌求出 $k$ 最少需要是多少才能满足第一个限制，然后取个 $\max$ 即可。

复杂度大概是 $4^kk\log T+nmk$，跑得飞快，最慢的一个点只用了 6ms

u1s1 这题上界是 $10^{20}$，但实测把 INF 开到 $9\times 10^{18}$ 能过……

```cpp
const int MAXN=50;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int n,m,k,X,Y,id[1<<7];
int getid(int x,int y,int d){return d*n*m+(x-1)*m+y;}
pair<pii,int> getcor(int x){return mp(mp((x-1)%(n*m)/m+1,(x-1)%m+1),(x-1)/n/m);}
int a[7][MAXN+5][MAXN+5],st[7];
int getnxt(int t,int x,int y,int d){
	d=(d+a[t][x][y])&3;
	if(x+dx[d]<1||x+dx[d]>n||y+dy[d]<1||y+dy[d]>m)
		d^=2;
	return getid(x+dx[d],y+dy[d],d);
}
vector<int> rch[7];
int stk[MAXN*MAXN*4+5],tp=0,len[7];
bool vis[MAXN*MAXN*4+5];
void dfs(int t,int x){
	if(vis[x]){
		for(int i=1;i<=tp;i++) rch[t].pb(stk[i]);
		for(int i=1;i<=tp;i++) if(stk[i]==x) len[t]=tp-i+1;
		return;
	} vis[x]=1;pair<pii,int> p=getcor(x);stk[++tp]=x;
	dfs(t,getnxt(t,p.fi.fi,p.fi.se,p.se));
}
int need[7][5],typ[7][5];
ll gcd(ll x,ll y){return (!y)?x:gcd(y,x%y);}
void exgcd(ll x,ll y,ll &a,ll &b){
	if(!y) return a=1,b=0,void();exgcd(y,x%y,a,b);
	ll tmp=a;a=b;b=tmp-(x/y)*b;
}
ll smul(ll x,ll y,ll mod){
	x=(x%mod+mod)%mod;y=(y%mod+mod)%mod;ll res=0;
	for(;y;y>>=1,x=(x+x)%mod) if(y&1) res=(res+x)%mod;
	return res;
}
pair<ll,ll> combine(ll a1,ll b1,ll a2,ll b2){
	if(!~a1||!~a2) return mp(-1,-1);
	ll d=gcd(a1,a2);if((b2-b1)%d) return mp(-1,-1);
	ll t=(b2-b1)/d;ll k1,k2;exgcd(a1,a2,k1,k2);
	k1=smul(k1,t,a2/d);ll A=a1/d*a2;
	return mp(A,(smul(a1,k1,A)+b1)%A);
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&k,&X,&Y);
	id['U']=0;id['R']=1;id['D']=2;id['L']=3;
	for(int i=1;i<=k;i++){
		int x,y;char c;cin>>x>>y>>c;
		st[i]=getid(x,y,id[c]);
		for(int j=1;j<=n;j++) for(int l=1;l<=m;l++)
			scanf("%1d",&a[i][j][l]);
	}
	for(int i=1;i<=k;i++){
		memset(vis,0,sizeof(vis));tp=0;
		dfs(i,st[i]);
//		for(int x:rch[i]) printf("%d\n",x);
		for(int d=0;d<4;d++){
			int x=getid(X,Y,d),ps=-1;
			for(int j=0;j<rch[i].size();j++) if(rch[i][j]==x) ps=j;
			need[i][d]=ps;typ[i][d]=(ps>=rch[i].size()-len[i]); 
//			printf("%d %d %d %d %d\n",i,d,x,need[i][d],typ[i][d]);
		}
	} ll res=9e18;
	for(int i=0;i<(1<<(k<<1));i++){
		bool flg=1;
		for(int j=1;j<=k;j++){
			int x=i>>((j-1)<<1)&3;
			if(!~need[j][x]) flg=0;
		} if(!flg) continue;
		int tim=-1;
		for(int j=1;j<=k;j++){
			int x=i>>((j-1)<<1)&3;
			if(!typ[j][x]) tim=need[j][x];
		}
		if(~tim){
			for(int j=1;j<=k;j++){
				int x=i>>((j-1)<<1)&3;
				if(!typ[j][x]&&need[j][x]!=tim) flg=0;
				if(typ[j][x]&&(tim<rch[j].size()-len[j]||tim%len[j]!=need[j][x]%len[j]))
					flg=0;
			} if(flg) chkmin(res,tim);
			continue;
		}
		pair<ll,ll> A=mp(1,0);
		for(int j=1;j<=k;j++){
			int x=i>>((j-1)<<1)&3;
			A=combine(A.fi,A.se,len[j],need[j][x]%len[j]);
		} if(!~A.fi) continue;ll tt=A.se;
		for(int j=1;j<=k;j++){
			int x=i>>((j-1)<<1)&3;
			if(A.se<need[j][x]) chkmax(tt,A.se+(need[j][x]-A.se+A.fi-1)/A.fi*A.fi);
		} chkmin(res,tt);
	} printf("%lld\n",(res==9e18)?-1:(res+1));
	return 0;
}
```



---

## 作者：Feyn (赞：8)

[link](https://www.luogu.com.cn/problem/P4621) & [博客园食用](https://www.cnblogs.com/dai-se-can-tian/p/16476289.html)

### 题意

有一个矩形区域被划分成了许多小方格，这些方格中有一个是陷阱。这个区域内有一些细菌，这些细菌有初始方向，它们会沿着各自的初始方向去到相邻的格子（特别地，假如当前方向会导致它们冲出矩形那么细菌会转身），每到一个新的格子，细菌就会按照格子中的数值旋转一定的角度从而改变自己的方向。显然很有可能这些细菌有一个时刻会进入陷阱中，但是一般来说为了防止打草惊蛇这些陷阱不会发作，进入陷阱的细菌会照常改变方向然后离开。陷阱发挥作用当且仅当所有细菌同时进入陷阱，题目中问的就是陷阱第一次发作的时间。

### 解法

很显然的是细菌所到达的格子会循环往复。因为细菌的状态由所在位置和当前方向决定，当前状态会产生唯一的一个新状态，而状态是有限的，所以肯定会产生循环。那么就可以推断出每一个细菌的路径一定是分为两个阶段，第一个阶段从初始状态走到一个状态 $A$ ，第二个阶段就是从 $A$ 通过一些时间重新回到 $A$ ，这样循环往复。也可以像第一篇题解那样理解，把每一个状态抽象成一个节点，那么每个节点的出度都是一，所以肯定会形成一片内向基环树森林。

既然如此可以分两类情况。对于第一阶段大可以直接枚举时间然后判断是否合法，因为可以想见可能的时间一定不多。对于第二个阶段，假设第一次到达某个状态的时间为 $t_0$，每次循环的时间是 $c$，那么每次到达这个点的时间都可以表示为 $t=t_0+kc(k\in N)$ ，换句话说就是 $t\equiv t_0\pmod c$ ，注意这里的 $t$ 应该不小于 $t_0$ 。每个陷阱会对应四种状态（也就是四种方向），所以所有细菌就可能会有 $K^4$ 种掉入陷阱的方式。这个数量也不多，可以枚举之后解同余方程组即可。

另外就是理论上这道题要用 ```__int128``` 来存储，但造出这样的数据似乎并不是很容易，于是只用龙龙就可以存的下了。

代码有注释，蒟蒻代码能力有限请大佬轻喷。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=60;
using namespace std;
inline void read(int &wh){
	wh=0;int f=1;char w=getchar();
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w>='0'&&w<='9'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}
inline int min(int s1,int s2){
	return s1<s2?s1:s2;
}

int m,n,num,x,y,data[N][4],cnt[N],st[N];

int c[N][N],vis[N][N][4];
int f[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//方向数组 
inline bool check(int a,int b){
	return a<1||b<1||a>m||b>n;//是否跳出边界 
}
void solve(int wh){
	memset(vis,0,sizeof(vis));
	int a,b,now;read(a);read(b);
	char w[N];scanf("%s",w);
	switch(w[0]){
		case 'U':now=0;break;
		case 'R':now=1;break;
		case 'D':now=2;break;
		case 'L':now=3;break;
	}
	for(int i=1;i<=m;i++){
		scanf("%s",w);
		for(int j=1;j<=n;j++)c[i][j]=w[j-1]-'0';
	}//处理输入 
	
	int an=0;
	while(true){
		an++;
		if(vis[a][b][now]){cnt[wh]=an-vis[a][b][now];st[wh]=vis[a][b][now];return;}
		//如果一个状态已经被访问过了，那么两次访问的时间差就会是循环长度 
		vis[a][b][now]=an;if(a==x&&b==y)data[wh][now]=an;//记录第一次进入陷阱的时间 
		now=(now+c[a][b])%4;//按照题意改变方向 
		if(check(a+f[now][0],b+f[now][1]))now=(now+2)%4;//如果走出矩阵了 
		a+=f[now][0],b+=f[now][1];//移动到下一个格子 
	}
}

inline bool able(int wh,int t){
	for(int i=0;i<4;i++){
		if(data[wh][i]==0)continue;
		if(data[wh][i]<st[wh]){if(data[wh][i]==t)return true;}
		else if(t>=data[wh][i]&&t%cnt[wh]==data[wh][i]%cnt[wh])return true;
	}
	return false;
}

int limit,ans=1e18,a[10],b[10];

struct node{int x,y,g;};
inline node exgcd(int a,int b){
	if(b==0)return (node){1,0,a};
	node an=exgcd(b,a%b);
	return (node){an.y,an.x-a/b*an.y,an.g};
}//扩展欧几里得的板子 
void work(){
	int M=b[1],x0=a[1];
	for(int i=2;i<=num;i++){
		node an=exgcd(M,b[i]);
		int c=a[i]-x0,bg=b[i]/an.g;
		if(c%an.g)return;
		int x=an.x*(c/an.g)%bg;
		x0+=x*M;M*=bg;
		x0=(x0%M+M)%M;
	}//扩展中国剩余定理的板子 
	while(x0<limit)x0+=M;//要保证最后的答案大于等于limit 
	ans=min(ans,x0);return;//更新答案 
}
void dfs(int wh){
	if(wh>num){work();return;}
	for(int i=0;i<4;i++){
		if(data[wh][i]<st[wh])continue;//没进入循环的状态只会出现一次，不能加入同余方程 
		a[wh]=data[wh][i]%cnt[wh];
		b[wh]=cnt[wh];//记录余数和模数 
		dfs(wh+1);
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);read(num);
	read(x);read(y);
	for(int i=1;i<=num;i++)solve(i);
	for(int i=1;i<=num;i++){
		bool ok=true;
		for(int j=0;j<4;j++){
			limit=max(limit,st[i]);
			if(data[i][j])ok=false;
		}
		if(ok){printf("-1");return 0;}//如果有细菌根本到不了陷阱 
	}
	//limit是所有细菌中进入循环的最晚细菌的时间 
	
	//处理第一阶段的答案，枚举加验证 
	for(int i=0;i<=limit;i++){
		bool ok=true;
		for(int j=1;j<=num;j++){
			if(able(j,i)==false){ok=false;break;}//如果有细菌到不了 
		}
		if(ok){printf("%lld",i);return 0;}//假如存在小于limit的答案直接输出 
	}
	
	dfs(1);//枚举状态 
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：sky_landscape (赞：6)

一道很好的数学题。

首先不难想到每个细菌的移动路线是有循环节的，循环节外的时间最多就是每个格子的四个方向都走一遍，也就是 $4\times N \times M$。

可以预处理每个细菌分别通过四个方向第一次到达终点的时间 $b_{i,0/1/2/3}$ 和再次回到当前状态的循环节长度 $md_{i,0/1/2/3}$。

要特别注意的是不同方向到达终点是不同的状态。

首先 $4\times N \times M$ 以内的答案直接暴力算出来（有可能有病毒没有进入循环节）。

然后计算大于 $4\times N \times M$ 的答案，假设已知了每个病毒最终到达终点面对的方向 $face_i$，其实限制就是一个同余方程，设答案为 $x$，对于每个病毒有限制：

$$x\equiv b_{i,face_i}(\bmod$$ $$md_{i,face_i})$$

可以扩展中国剩余定理求解，每个病毒面对的方向可以搜索。

有一个细节，扩展中国剩余定理求解的答案必须大于等于所有的 $b_{i,face_i}$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=60;
const int INF=1e18;
int as=INF;
int n,m,k,rx,ry;
int dx[10]={-1,0,1,0},dy[10]={0,1,0,-1};
int tun[10]={2,3,0,1};
int vis[N][N][4],b[N][4],md[N][4],rec[N][N];
int mp[N][N],x,y;
int ton[2*N*N*4];
int hp[4],cho[N],lim=0;

struct node{
    int x,y;
    char c;
}q[N];
bool out(int xx,int yy){
    if(xx>n || xx<1 || yy>m || yy<1) return true;
    return false;
} 

int go(int xx,int yy,int st){
    st+=mp[xx][yy];
    st%=4;
    if(!out(xx+dx[st],yy+dy[st])) return st;
    else return tun[st];
}

void work(int now,int nx,int ny,char ch){
    int st;
    if(ch=='U') st=0;
    else if(ch=='R') st=1;
    else if(ch=='D') st=2;
    else st=3;
    int tim=0;
    hp[0]=hp[1]=hp[2]=hp[3]=0;
    int xf=INF;
    while(tim<=n*m*4){
        ++tim;
        if(nx==rx && ny==ry){
            xf=min(xf,tim);
            if(b[now][st]==INF) b[now][st]=tim;
            else if(md[now][st]==INF) md[now][st]=tim-b[now][st];
            ton[tim]++;
            hp[st]=tim;
        }
        st=go(nx,ny,st);
        nx+=dx[st],ny+=dy[st];
    }
    lim=max(lim,xf);
}

void init(){
    cin>>n>>m>>k;
    cin>>rx>>ry;
    for(int i=0;i<N;i++){
        for(int j=0;j<4;j++) b[i][j]=md[i][j]=INF;
    }
    for(int i=1;i<=k;i++){
        cin>>q[i].x>>q[i].y>>q[i].c;
        string s;
        for(int j=1;j<=n;j++){
            cin>>s,s=" "+s;
            for(int k=1;k<=m;k++) mp[j][k]=(s[k]-'0');
        }
        work(i,q[i].x,q[i].y,q[i].c);
    }
}

int exgcd(int a,int b){
	if(b==0){
		x=1,y=0;
		return a;
	}
	else{
		int as=exgcd(b,a%b);
		int xx=x,yy=y;
		x=yy,y=xx-(a/b)*yy;
		return as;
	}
}

int qmul(int af,int bf,int p){
	int aa=0,x=af;
	while(bf){
		if(bf&1){
			aa+=x;
			aa%=p;
		}
		x*=2;
		x%=p;
		bf/=2;
	}
	return aa;
}

int excrt(){
    int ans=b[1][cho[1]],lcm=md[1][cho[1]];
	for(int i=2;i<=k;i++){
        int aa=lcm,bb=md[i][cho[i]],cc=b[i][cho[i]]-ans;
		cc=(cc%md[i][cho[i]]+md[i][cho[i]])%md[i][cho[i]];
		int d=exgcd(aa,bb);
		if(cc%d){
		    return INF;
		}
		ans=ans+lcm*qmul(x,cc/d,md[i][cho[i]]);
		lcm/=d,lcm*=md[i][cho[i]];
		ans=(ans%lcm+lcm)%lcm;
	}
    int af=ans;
    if(lim>af){
        int xx=(lim-af)/lcm;
        af+=(xx*lcm);
        if(af<lim) af+=lcm; 
    }
    return af;
}

void dfs(int x){
    if(x==k+1){
        as=min(as,excrt());
        return;
    }
    for(int i=0;i<4;i++){
        if(b[x][i]==INF || md[x][i]==INF) continue;
        cho[x]=i;
        dfs(x+1);
    }
}

signed main(){
    init();
    for(int i=1;i<=n*m*4;i++){
        if(ton[i]==k){
            cout<<i;
            return 0;
        }
    }
    dfs(1);
    if(as==INF) cout<<-1;
    else cout<<as;
    return 0;
}
```

---

## 作者：ShwStone (赞：3)

[Link](https://www.luogu.com.cn/problem/P4621)

## 题目分析

这个题在 Luogu 居然评了黑，也是比较离谱的。

首先这是一道大模拟。考察每一个细菌的行为，可以发现其状态可以用三元组 $(x, y, d), 1 \le x \le n, 1 \le y \le m, 0 \le d < 4$ 表示。其中 $(x, y)$ 为位置， $d$ 为方向。

显而易见的，细菌的行动最终一定陷入循环，所以我们可以通过模拟求出细菌循环节的长度以及他进入循环之前需要走的步数。

考虑用记录到达位置 $(x, y, d)$ 所需的步数。在模拟的过程中，如果发现重复进入同一个位置说明产生了循环，循环节长度为当前步数 - 第一次步数，记为 $stp$，进入循环节之前的步数记为 $st$。

由于题目要求所有细菌进入陷阱，所以我们还要统计每一个细菌进入陷阱的时刻。用 $pas_i$ 表示细菌第一次以方向 $i$ 进入陷阱的时刻。可以发现，如果 $pas_i < st$，则细菌只可能在进入循环节之前以方向 $i$ 进入陷阱，在循环节中绝对不会（如果也进了说明 $st$ 可以提前到 $pas_i$ ）。同理，在循环节中经过的也不会在循环节之前经过。所以用一个数组就可以记录，互不干扰。

大致代码如下：

```cpp
void calc(int id) {
	memset(book, 0, sizeof book);
	book[a[id].x][a[id].y][a[id].d] = 1;
	while (true) {
		if (a[id].x == xx && a[id].y == yy) a[id].pas[a[id].d] = book[a[id].x][a[id].y][a[id].d];
		int td = ((a[id].d + a[id].mp[a[id].x][a[id].y]) & 3),
			tx = a[id].x + ch_d[td][0],
			ty = a[id].y + ch_d[td][1];
		if (tx < 1 || tx > n || ty < 1 || ty > m) {
			td = ((td + 2) & 3);
			tx = a[id].x + ch_d[td][0];
			ty = a[id].y + ch_d[td][1];
		}
		if (book[tx][ty][td]) {
			a[id].st = book[tx][ty][td];
			a[id].stp = book[a[id].x][a[id].y][a[id].d] + 1 - book[tx][ty][td];
			return;
		}
		book[tx][ty][td] = book[a[id].x][a[id].y][a[id].d] + 1;
		a[id].x = tx;
		a[id].y = ty;
		a[id].d = td;
	}
}
```

接下来对于怎么求答案进行分析：

首先如果有一个细菌没有经过陷阱，那么直接输出 `-1`。

接下来要把问题分为两部分。求出最晚进入循环的细菌进入循环的时刻，记为 $maxst$，则在 $maxst$ 之前的时刻可以暴力枚举，在 $maxst$ 之后的时间可以用数学方法。

在 $maxst$ 之前的时刻枚举如下，注意此时已经有一些细菌进入循环，所以也要考虑进入循环的细菌。

```cpp
for (long long i = 0; i <= mst; i++) {
    bool flag = true;
    for (int j = 1; j <= k; j++) {
        bool f = false;
        for (int l = 0; l < 4; l++) {
            if (a[j].pas[l] == 0) continue;
            if (a[j].pas[l] < a[j].st) {
                if (a[j].pas[l] == i) {
                    f = true;
                    break;
                }
            }
            else if (i >= a[j].pas[l] && i % a[j].stp == a[j].pas[l] % a[j].stp) {
                f = true;
                break;
            }
        }
        if (f == false) {
            flag = false;
            break;
        }
    }
    if (flag) {
        printf("%lld\n", i);
        return 0;
    }
}
```

而在进入循环之后，实际上就是求解这样一个方程组：

$$
\begin{cases}
x \equiv a[1].pas_0 \text{ or } a[1].pas_1 \text{ or } a[1].pas_2\text{ or }a[1].pas_3 \pmod {a[1].stp}\\
x \equiv a[2].pas_0\text{ or }a[2].pas_1\text{ or }a[2].pas_2\text{ or }a[2].pas_3 \pmod {a[2].stp}\\
x \equiv a[3].pas_0\text{ or }a[3].pas_1\text{ or }a[3].pas_2\text{ or }a[3].pas_3 \pmod {a[3].stp}\\
x \equiv a[4].pas_0\text{ or }a[4].pas_1\text{ or }a[4].pas_2\text{ or } a[4].pas_3 \pmod {a[4].stp}\\
x \equiv a[5].pas_0\text{ or }a[5].pas_1\text{ or }a[5].pas_2\text{ or }a[5].pas_3 \pmod {a[5].stp}
\end{cases}
$$

因为一共就 5 个细菌，每个细菌 4 种选择，所以可以先枚举所有的情况，求解 $4^5$ 次如下方程组：

$$
\begin{cases}
x \equiv pas_1 \pmod {a[1].stp}\\
x \equiv pas_2 \pmod {a[2].stp}\\
x \equiv pas_3 \pmod {a[3].stp}\\
x \equiv pas_4 \pmod {a[4].stp}\\
x \equiv pas_5 \pmod {a[5].stp}
\end{cases}
$$

标准答案大概是现在使用扩展 CRT （中国剩余定理），求解同余方程组。如果这样黑题也就勉勉强强，但有意思的是直接暴力 CRT 就可以 AC。这黑题就有点水了。

枚举方程组和暴力 CRT 如下：

```cpp
long long cal() {
	long long res = yushu[1];
	long long lllcm = moshu[1];
	for (int i = 2; i <= k; i++) {
		int cnt = 0;
		while (res % moshu[i] != yushu[i]) {
			res += lllcm;
			res %= llcm;
			if (++cnt > moshu[i]) return LLONG_MAX;
		}
		lllcm = lcm(lllcm, moshu[i]);
	}
	while (res < mst) res += llcm; //注意要在循环之内
	return res;
}

void doit(int id) {
	if (id == k + 1) {
		ans = min(ans, cal());
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (a[id].pas[i] < a[id].st) continue;
		moshu[id] = a[id].stp;
		yushu[id] = a[id].pas[i] % a[id].stp;
		doit(id + 1);
	}
}
```

个人觉得降紫还是合理的。

# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e1 + 5, maxk = 7;
const int ch_d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct node {
	int x, y, d;
	long long st, stp;
	long long pas[4];
	char mp[maxn][maxn];
};

int n, m, k, xx, yy;
node a[maxk];
int book[maxn][maxn][4];
int dir[256];
long long mst, ans = LLONG_MAX, llcm = 1, sum = 1;
long long moshu[maxk], yushu[maxk];

long long lcm(long long a, long long b) {
	return a / __gcd(a, b) * b;
}

void calc(int id) {
	memset(book, 0, sizeof book);
	book[a[id].x][a[id].y][a[id].d] = 1;
	while (true) {
		if (a[id].x == xx && a[id].y == yy) a[id].pas[a[id].d] = book[a[id].x][a[id].y][a[id].d];
		int td = ((a[id].d + a[id].mp[a[id].x][a[id].y]) & 3),
			tx = a[id].x + ch_d[td][0],
			ty = a[id].y + ch_d[td][1];
		if (tx < 1 || tx > n || ty < 1 || ty > m) {
			td = ((td + 2) & 3);
			tx = a[id].x + ch_d[td][0];
			ty = a[id].y + ch_d[td][1];
		}
		if (book[tx][ty][td]) {
			a[id].st = book[tx][ty][td];
			a[id].stp = book[a[id].x][a[id].y][a[id].d] + 1 - book[tx][ty][td];
			return;
		}
		book[tx][ty][td] = book[a[id].x][a[id].y][a[id].d] + 1;
		a[id].x = tx;
		a[id].y = ty;
		a[id].d = td;
	}
}

long long cal() {
	long long res = yushu[1];
	long long lllcm = moshu[1];
	for (int i = 2; i <= k; i++) {
		int cnt = 0;
		while (res % moshu[i] != yushu[i]) {
			res += lllcm;
			res %= llcm;
			if (++cnt > moshu[i]) return LLONG_MAX;
		}
		lllcm = lcm(lllcm, moshu[i]);
	}
	while (res < mst) res += llcm;
	return res;
}

void doit(int id) {
	if (id == k + 1) {
		ans = min(ans, cal());
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (a[id].pas[i] < a[id].st) continue;
		moshu[id] = a[id].stp;
		yushu[id] = a[id].pas[i] % a[id].stp;
		doit(id + 1);
	}
}

int main() {
	dir['U'] = 0; dir['R'] = 1; dir['D'] = 2; dir['L'] = 3;
	scanf("%d %d %d", &n, &m, &k);
	scanf("%d %d", &xx, &yy);
	for (int i = 1; i <= k; i++) {
		char ch; scanf("%d %d %c", &a[i].x, &a[i].y, &ch);
		a[i].d = dir[ch];
		for (int j = 1; j <= n; j++) {
			scanf("%s", a[i].mp[j] + 1);
			for (int l = 1; l <= m; l++) a[i].mp[j][l] -= 48;
		}
		calc(i);
		if (!(a[i].pas[0] || a[i].pas[1] || a[i].pas[2] || a[i].pas[3])) {
			printf("-1\n");
			return 0;
		}
	}
	for (int i = 1; i <= k; i++) {
		mst = max(mst, a[i].st);
		llcm = lcm(llcm, a[i].stp);
	}
	for (long long i = 0; i <= mst; i++) {
		bool flag = true;
		for (int j = 1; j <= k; j++) {
			bool f = false;
			for (int l = 0; l < 4; l++) {
				if (a[j].pas[l] == 0) continue;
				if (a[j].pas[l] < a[j].st) {
					if (a[j].pas[l] == i) {
						f = true;
						break;
					}
				}
				else if (i >= a[j].pas[l] && i % a[j].stp == a[j].pas[l] % a[j].stp) {
					f = true;
					break;
				}
			}
			if (f == false) {
				flag = false;
				break;
			}
		}
		if (flag) {
			printf("%lld\n", i);
			return 0;
		}
	}
	doit(1);
	if (ans == LLONG_MAX) printf("-1\n");
	else printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Mirasycle (赞：2)

简单题，没有任何细节。

直接搜出每个细菌从四种方向进入陷阱的周期。然后暴力枚举每种细菌是从哪个方向进入的。

使用 ExCRT 合并周期，算出最后的时间即可。注意我们的时间是形如 $kT+d$ 的形式，但是可能 $d>T$（第一次进入时间大于周期），这个时候直接用同余方程 $x\equiv d\pmod T$ 的话可能得到 $<d$ 的解。我们需要对于最后得到的解，进行 $\ge d$ 的约束检测，如果不满足这个约束就加上若干倍的周期使得其 $\ge d$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef __int128 i128; 
const int maxn=55;
void cmin(ll &x,i128 y){ x=x<y?x:y; }
struct node{ int x,y,t; }b[maxn]; ll ans=LLONG_MAX;
vector<pair<int,int> > vec[maxn],E;//T d
int n,m,K,a[maxn][maxn][maxn],vis[maxn][maxn][4],lst[5],sx,sy;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1},ID; char S[maxn];
int to(char c){
	if(c=='U') return 0; if(c=='R') return 1;
	if(c=='D') return 2; if(c=='L') return 3;
}
bool chk(int T){
	for(auto z:E){
		if(!z.fi&&z.se!=T) return 0;
		if(z.fi&&((T%z.fi)!=(z.se%z.fi)||T<z.se)) return 0;
	}
	return 1;
}
void exgcd(ll a,ll b,ll& x,ll& y){
	if(!b){ x=1, y=0; return ; }
	exgcd(b,a%b,y,x); y-=x*(a/b);
}
i128 ExCRT(){
	for(auto z:E)
		if(!z.fi){
			if(chk(z.se)) return z.se;
			else return -1;
		}
	ll tm=E.front().fi,ta=E.front().se%tm,x,y;
	for(int i=1;i<E.size();i++){
		ll cm=E[i].fi,ca=E[i].se%cm;
		ll F=(ca-ta%cm+cm)%cm,d=__gcd(tm,cm);
		if(F%d) return -1; cm/=d; F/=d;
		exgcd(tm/d,cm,x,y); x=(x%cm+cm)%cm;
		ta+=(i128)F*x%cm*tm; tm=tm*cm; ta%=tm;
	}
	for(auto z:E){
		if(ta>=z.se) continue;
		ll k=(z.se-ta+tm-1)/tm;
		ta+=k*tm;
	}
	return ta;
}
void dfs(int x,int y,int t,int l){
	if(vis[x][y][t]>=2) return ;
	if(x==sx&&y==sy){
		if(!lst[t]) vec[ID].pb(0,l),lst[t]=l;
		else vec[ID].pb(l-lst[t],lst[t]);
	}
	vis[x][y][t]++; t=(t+a[ID][x][y])%4;
	int nx=x+dx[t],ny=y+dy[t];
	if(nx<1||nx>n||ny<1||ny>m) t=(t+2)%4;
	dfs(x+dx[t],y+dy[t],t,l+1);
}
void solve(int x){
	if(x==K+1){
		i128 res=ExCRT(); 
		if(~res) cmin(ans,res);
		return ;
	}
	for(auto z:vec[x]){ E.pb(z); solve(x+1); E.pop_back(); }
}
int main(){// U0 R1 D2 L3
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m>>K>>sx>>sy;
	for(int i=1;i<=K;i++){
		int x,y; char c;
		cin>>x>>y>>c; b[i]=node{x,y,to(c)};
		for(int j=1;j<=n;j++){
			cin>>(S+1);
			for(int k=1;k<=m;k++) a[i][j][k]=S[k]-'0';
		}
	}
	for(int i=1;i<=K;i++){
		memset(vis,0,sizeof(vis)); ID=i;
		memset(lst,0,sizeof(lst));
		dfs(b[i].x,b[i].y,b[i].t,0);
	}
	solve(1);
	if(ans==LLONG_MAX) cout<<-1;
	else cout<<ans+1;
	return 0;
}
```

---

## 作者：CatFromMars (赞：1)

恶臭细节题。

这道题看上去完全不可做，定睛一看 $K = 5$ 怎么做都能过了。很容易想到对于每个点每个时刻状态 $(x, y, dir)$（其中 $(x, y)$ 为坐标，$dir$ 为方向）一共只有 $O(nm)$ 种，非常少。所以可以以每个点为起点往外面直接找到它的行走状态路径，显然先是一条链后面进入了后面一个环。

对于它到点 $(ex, ey)$ 的状态，因为 $dir$ 不同所以有 $O(4^k)$ 种。如果 $k$ 个状态存在一个在链上，那么最小时刻就是这个在链上的时刻，从而可以直接判断。否则就是全在环上的情况。我们令这个状态在行走中是第 $t$ 步，环大小为 $m$，那么问题变成了求解一个最小 $c$ 使得 $c = t_i+k_im_i, \forall i\in[1, n]$。$k$ 特别讨厌，所以我们构造成线性同余方程组的形式吞掉 $k$。最后问题变成了 $c\equiv t_i \pmod {m_i}, \forall i \in [1, n]$，这就是 exCRT 的模板了。套一下即可。

代码细节很恶臭，调了很久。如果大家有细节错误可以到[这里](https://hsin.hr/coci/archive/2012_2013/)下载数据 qwq。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
int cdiv(int n, int m) {
	return ((n % m == 0) ? (n / m) : (n / m + 1));
}
const ll inf = 9e18;
const int N = 50;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
struct node {
	int x, y, dir;
};
int a[6][N + 10][N + 10];
int n, m, qk, X[N + 10], Y[N + 10], S[N + 10], edx, edy;

bool vis[N + 10][N + 10][5];
int step[6][N + 10][N + 10][5];

vector <node> vec[10];
int start[10], tim[10], c[10][10];//type[i] i->repeat
void getpath(int x, int y, int w, int ind) {
	int nowx = x, nowy = y, nowd = w, st = 0;
	while(1) {
		vis[nowx][nowy][nowd] = 1;
		step[ind][nowx][nowy][nowd] = st; st++;
		vec[ind].push_back((node){nowx, nowy, nowd});
		if(nowx == edx && nowy == edy) 
			c[ind][nowd] = st - 1;
		nowd = (nowd + a[ind][nowx][nowy]) % 4;

		int xx = nowx + dx[nowd], yy = nowy + dy[nowd];
		if(!(xx >= 1 && xx <= n && yy >= 1 && yy <= m)) {
			if(nowd == 0) nowd = 2;
			else if(nowd == 2) nowd = 0;
			else if(nowd == 1) nowd = 3;
			else if(nowd == 3) nowd = 1;
			xx = nowx + dx[nowd], yy = nowy + dy[nowd];
		}

		if(vis[xx][yy][nowd]) {
			start[ind] = step[ind][xx][yy][nowd];
			tim[ind] = vec[ind].size() - start[ind];
			break;
		}
		else {
			nowx = nowx + dx[nowd];
			nowy = nowy + dy[nowd];
		}
	}

	for(int i = 0; i < vec[ind].size(); i++)
		vis[vec[ind][i].x][vec[ind][i].y][vec[ind][i].dir] = 0;
}

int arrd[10];
ll ans = 9e18;
namespace excrt {
	int exgcd(int a, int b, int &x, int &y) {
		if(!b) {
			x = 1, y = 0;
			return a;
		}
		int d = exgcd(b, a % b, x, y);
		int tmp = x; x = y;
		y = tmp - a / b * y;
		return d;
	}
	int qmul(int n, int m, int Mod) {
		int res = 0;
		while(m) {
			if(m & 1) res = (res + n) % Mod;
			n = (n + n) % Mod, m >>= 1;
		}
		return res;
	}

	int d;
	int xxtyfc(int a, int b, int c) {
		int x, y;
		d = exgcd(a, c, x, y);
		if(b % d != 0) return -1;
		x = qmul(x, b / d, c);
		y = qmul(y, b / d, c);
		
		return (x % (c / d) + (c / d)) % (c / d);
	}
	int r[N + 10], m[N + 10];
	int excrt() {
		int x = xxtyfc(1, r[1], m[1]);
		int L = m[1];
		
		int maxn = 0;
		for(int i = 1; i <= qk; i++)
			maxn = max(maxn, r[i]);
		for(int i = 2; i <= qk; i++) {
			int t = xxtyfc(L, ((r[i] - x + m[i]) % m[i] + m[i]) % m[i], m[i]);
			if(t == -1) {
				return inf;
			}
			int tmp = L; 
			L = L / d * m[i];
			x = (x + qmul(t, tmp, L)) % L;
		}
		x %= L;//特别的 x 要比所有的 t 大！
		while(x < maxn)
			x += L;
		return x;
	}
}
void calc(int u) {//搜索
	if(u > qk) {
		int cnt = 0;
		for(int i = 1; i <= qk; i++)
			if(c[i][arrd[i]] == -1) return ;

		for(int i = 1; i <= qk; i++)
			if(c[i][arrd[i]] < start[i])
				cnt++;
		if(cnt) {//存在链上可以直接判断
			ll stand = -1;
			bool nos = 0;
			for(int i = 1; i <= qk; i++)//在链上的讨论
				if(c[i][arrd[i]] < start[i]) {
					if(stand < 0) stand = c[i][arrd[i]];
					else if(c[i][arrd[i]] != stand) {
						nos = 1;
						break;
					}
				}
			for(int i = 1; i <= qk; i++)//在环上的讨论
				if(c[i][arrd[i]] >= start[i]) {
					if(c[i][arrd[i]] > stand) {
						nos = 1;
						break;
					}
					else if((stand - c[i][arrd[i]]) % tim[i] != 0) {
						nos = 1;
						break;
					}
				}
			if(!nos) ans = min(ans, stand);
		}
		else {
			for(int i = 1; i <= qk; i++)
				excrt::r[i] = c[i][arrd[i]], excrt::m[i] = tim[i];//否则可以直接 excrt
			ans = min(ans, excrt::excrt());
		}

		return ;
	}
	for(int i = 0; i < 4; i++)
		if(c[u][i] != -1)
		arrd[u] = i, calc(u + 1);
}
signed main() {
	memset(c, -1, sizeof(c));
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> qk;
	cin >> edx >> edy;
	for(int i = 1; i <= qk; i++) {
		char o;
		cin >> X[i] >> Y[i] >> o;

		if(o == 'R') S[i] = 0;
		else if(o == 'D') S[i] = 1;
		else if(o == 'L') S[i] = 2;
		else S[i] = 3;

		for(int j = 0; j <= n + 1; j++) 
			for(int k = 0; k <= m + 1; k++)
				a[i][j][k] = 2;
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k <= m; k++) {
				char ch; cin >> o;
				a[i][j][k] = (o - '0') % 4;
			}
		}
	}

	for(int i = 1; i <= qk; i++)
		getpath(X[i], Y[i], S[i], i);
	calc(1);
	if(ans >= inf) cout << -1 << endl;
	else cout << ans + 1 << endl;
}
```

---

## 作者：Forever1507 (赞：1)

## P4621 BAKTERIJE

题意略。

注意到细菌的数量相当少，因此我们逐个细菌进行考虑。对于单个细菌而言，如果将每个位置的四个朝向分别视为一个节点，那么每个节点会移动向唯一的另一个节点，那么也就构成了一个内向基环树森林。

于是，由于数据范围很小，所以如果我们希望求出到某一个点的步数，在环外的部分我们可以暴力跳，每跳一步就判断一次是否满足答案，跳到环上之后就构成一个循环。

注意到终点并不是唯一的，陷阱位置四个方向对应的节点都可以作为终点，但是可以直接 $4^k$ 强行枚举每个细菌到达的究竟是哪个终点。然后在多个细菌的情况下，我们可以先暴力跳直到所有细菌都在环上，这样每个细菌的出现位置都构成了一个循环，然后注意到这是一个同余方程组的形式，于是可以直接使用扩展中国剩余定理求解。

一些实现上的注意事项：

1. 方程组求解完后，如果步数小于跳到环上的步数，要加上若干最小公倍数直到不小于跳到环上的步数。
2. 陷阱消灭细菌需要消耗一秒时间，所以最后答案还要加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e4+5;
int n,m,k,x,y,to[10][N];
char c[4]={'U','R','D','L'};
int getid(int i,int j,char c){
    int ans=4*((i-1)*m+j-1);
    if(c=='U')return ans+1;
    else if(c=='R')return ans+2;
    else if(c=='D')return ans+3;
    return ans+4;
}
bool vis[10][N],flg[10][N];
int pos[N],a[10][55][55];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int siz[10][N],fa[10][N];
int find(int i,int x){
    return fa[i][x]==x?x:fa[i][x]=find(i,fa[i][x]);
}
void unionn(int i,int a,int b){
    int x=find(i,a),y=find(i,b);
    if(x==y)return;
    fa[i][x]=y;
}
int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,x,y),_x=x,_y=y;
	x=_y;
	y=_x-(a/b)*_y; 
	return d;
}
int A[N],B[N];
int excrt(int n,int p){
	int lcm=A[1],ans=B[1];
	for(int i=2;i<=n;++i){
		int x,y;
		B[i]=((B[i]-ans)%A[i]+A[i])%A[i];
		int d=exgcd(lcm,A[i],x,y);
		if(B[i]%d)return 1e18;
		x=B[i]/d*x%A[i];
		A[i]/=d;
		ans=ans+x*lcm;
		lcm=lcm*A[i];
		ans=(ans%lcm+lcm)%lcm;
	}
    if(ans<p)ans=(p-ans+lcm-1)/lcm*lcm+ans;
    return ans;
}
int st[N];
int ed[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k>>x>>y;
    for(int i=1;i<=4*n*m;++i)for(int j=1;j<=k;++j)fa[j][i]=i;
    for(int i=1;i<=k;++i){
        int x,y;char z;
        cin>>x>>y>>z;
        pos[i]=getid(x,y,z);
        for(int j=1;j<=n;++j){
            for(int p=1;p<=m;++p){
                char c;
                cin>>c;
                a[i][j][p]=c-'0';
            }
        }
    }
    int tot=4*n*m;
    for(int o=1;o<=k;++o){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                for(int p=0;p<=3;++p){
                    int nxt=(p+a[o][i][j])%4;
                    if(nxt==0&&i==1)nxt=2;
                    if(nxt==3&&j==1)nxt=1;
                    if(nxt==1&&j==m)nxt=3;
                    if(nxt==2&&i==n)nxt=0;
                    to[o][getid(i,j,c[p])]=getid(i+dx[nxt],j+dy[nxt],c[nxt]);
                    unionn(o,getid(i,j,c[p]),getid(i+dx[nxt],j+dy[nxt],c[nxt]));
                }
            }
        }
    }
    for(int j=1;j<=k;++j){
        for(int i=1;i<=tot;++i){
            if(!vis[j][find(j,i)]){
                int now=i;
                while(!vis[j][now]){
                    vis[j][now]=1;
                    now=to[j][now];
                }
                if(flg[j][now])continue;
                vis[j][find(j,i)]=1;
                int tmp=now;
                do{
                    flg[j][tmp]=1;
                    siz[j][find(j,now)]++;
                    tmp=to[j][tmp];
                }while(tmp!=now);
            }
        }
    }
    int ans=1e18;
    for(int i=0;i<(1<<2*k);++i){
        int cnt=0,cnt2=0,tim=0;
        for(int j=1;j<=k;++j)st[j]=pos[j];
        for(int j=0;j<k;++j)ed[j+1]=(i>>(j*2)&1)*2+(i>>(j*2+1)&1);
        for(int j=1;j<=k;++j)ed[j]=getid(x,y,c[ed[j]]);
        for(int j=1;j<=k;++j)if(flg[j][st[j]])cnt++;
        for(int j=1;j<=k;++j)if(st[j]==ed[j])cnt2++;
        if(cnt2==k){
            cout<<1;
            return 0;
        }
        while(cnt!=k){
            for(int j=1;j<=k;++j)if(st[j]==ed[j])cnt2--;
            cnt=0;
            for(int j=1;j<=k;++j)st[j]=to[j][st[j]];
            for(int j=1;j<=k;++j)if(flg[j][st[j]])cnt++;
            for(int j=1;j<=k;++j)if(st[j]==ed[j])cnt2++;
            tim++;
            if(cnt2==k)ans=min(ans,tim);
        }
        bool tmp=0,tmp2=0;
        for(int j=1;j<=k;++j){
            if(!flg[j][ed[j]])tmp=1;
            if(find(j,st[j])!=find(j,ed[j]))tmp2=1;
        }
        if(tmp||tmp2)continue;
        for(int j=1;j<=k;++j){
            B[j]=tim;
            A[j]=siz[j][find(j,st[j])];
            int now=st[j];
            while(now!=ed[j]){
                now=to[j][now];
                B[j]++;
            }
            B[j]%=A[j];
        }
        ans=min(ans,excrt(k,tim));
    }
    if(ans==1e18)ans=-2;
    cout<<ans+1;
    return 0;
}
```

---

## 作者：Add_Catalyst (赞：1)

# P4621 [COCI2012-2013#6] BAKTERIJE 题解

---

## 知识点

扩展中国剩余定理。

---

## 题意分析

给你 $K$ 个网格图及其起点坐标和方向，求 $K$ 个网格图上的点同时到达给定终点 $(X,Y)$ 的最小时间。

---

## 思路分析

首先，显而易见的是每个点得拆成四个方向的分点，而每个方向只有一个出边，这就容易让人想到内向基环树。但是，这题的起点是固定的，那么我们最多只需维护一条基环树下的链，所以一遍 DFS 或迭代就可以搞定链长和环长。

那么最后的求解我们需要分别枚举 $K$ 个网格图到达给定终点 $(X,Y)$ 时的方向，也就是它所拆成的四个点，这可以二进制枚举、DFS 或格雷码实现。

现在再考虑处理细节。假设我们现在处理的终点 $(X,Y,D)$（$D$ 为其方向）是在以下情况：

1. 终点 $(X,Y,D)$ 在环上：

   设环长为 $Cyc$，从起点第一次到终点 $(X,Y,D)$ 的时间为 $Tim$，那么我们所求的答案 $res$ 就需要满足 $res \equiv Tim \pmod {Cyc} \land res \ge Tim$。

2. 终点 $(X,Y,D)$ 在链上：

   那么这张图从起点到达终点 $(X,Y,D)$ 的时间 $Tim$ 有且仅有一种，那么我们所求的答案 $res$ 就需要满足 $res =Tim$。

那么最后的统计也很简单：

- 所有枚举到的终点都在各自图的环上：

  那么题目就变成了一个线性同余方程组，注意到模数不一定互质，所以需要用**扩展中国剩余定理**。

- 有任意一个不在环上：

  就简单的判断一下同余就好了。

由于本题范围可以超过 `long long`，所以需要 `__int128`（不过数据没超过 `long long` 的范围，也可以不开）。

*注*：本题细节很多，要谨慎编码。

---

## CODE

时间复杂度：$O(4^K K \log_2{A} + N M K)$（$A$ 为求解扩展中国剩余定理时的最大数值），空间复杂度：$O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define Fi first
#define Se second
#define ll long long
#define Pll pair<ll,ll>
#define INF 0x3f3f3f3f3f3f3f3f
#define tomax(a,b) ((a)=max((a),(b)))
#define tomin(a,b) ((a)=min((a),(b)))
#define FOR(i,a,b) for(int i=(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i=(a);i>=(int)(b);--i)
#define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
typedef __int128 Int;
namespace IOstream{
#define getc() getchar()
#define putc(c) putchar(c)
#define blank(c) ((c)==' '||(c)=='\n'||(c)=='\r'||(c)==(EOF))
#define isdigit(c) ('0'<=(c)&&(c)<='9')
	template<class T>inline void rd(T &x){
		static bool sign(0);
		static char ch(0);
		for(x=0,sign=0,ch=getc();!isdigit(ch);ch=getc())if(ch=='-')sign^=1;
		for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^'0'),ch=getc());
		return x=sign?-x:x,void();
	}
	template<class T>inline void wr(T x,char End='\n'){
		static short top(0),st[100];
		x<0?putc('-'),x=-x:0,top=0;
		do st[++top]=x%10,x/=10;while(x);
		for(;top;putc(st[top]^'0'),--top);
		return putc(End),void();
	}
#undef blank
#undef isdigit
}using namespace IOstream;
constexpr int N=50+10,dx[4]= {-1,0,1,0},dy[4]= {0,1,0,-1}; //U,R,D,L
//constexpr ll INF=2e20;
namespace Ex_CRT {
	ll Ex_Gcd(ll &x,ll &y,ll a,ll b) {
		if(!b)return x=1,y=0,a;
		ll G=Ex_Gcd(y,x,b,a%b);
		return y-=(a/b)*x,G;
	}
	bool merge(Pll &A,Pll B) {
		A.Fi%=A.Se,B.Fi%=B.Se;
		ll x=0,y=0,a=A.Se,b=B.Se,c=B.Fi-A.Fi,g=Ex_Gcd(x,y,a,b);
		if(c%g)return 0;
		return x*=c/g,x=(x%(b/g)+(b/g))%(b/g),A=(Pll) {a*x+A.Fi,a/g*b},1;
	}
	Pll CRT(const vector<Pll> &vec) {
		Pll res= {0,1};
		for(const Pll &x:vec)if(!merge(res,x))return (Pll) {
				INF,INF
			};
		return res;
	}
}
int n,m,Q,X,Y;
ll ans=INF;
vector<Pll> Bac[5];
namespace Bacteria {
	int turn[N][N];
	int dis[N][N][4];
	struct Place {
		int x,y,d;
		Place(int x=0,int y=0,int d=0):x(x),y(y),d(d) {}
		Place Nxt() {
			Place nxt(x,y,(d+turn[x][y])&3);
			if(x+dx[nxt.d]<1||x+dx[nxt.d]>n||y+dy[nxt.d]<1||y+dy[nxt.d]>m)nxt.d^=2;
			return nxt.x+=dx[nxt.d],nxt.y+=dy[nxt.d],nxt;
		}
	} S;
	vector<Pll> Constr() {
		char C[N];
		int Cycle;
		vector<Pll> eq;
		rd(S.x),rd(S.y),scanf("%s",C),S.d=(C[0]=='U'?0:(C[0]=='R'?1:(C[0]=='D'?2:3)));
		FOR(i,1,n) {
			scanf("%s",C);
			FOR(j,1,m)turn[i][j]=(C[j-1]^'0')&3;
		}
		RCL(dis,-1,dis,1),dis[S.x][S.y][S.d]=1;
		for(Place u=S,v=u.Nxt();; u=v,v=u.Nxt()) {
			if(~dis[v.x][v.y][v.d]&&(S=v,Cycle=dis[u.x][u.y][u.d]-dis[v.x][v.y][v.d]+1,1))break;
			dis[v.x][v.y][v.d]=dis[u.x][u.y][u.d]+1;
		}
		FOR(d,0,3)if(~dis[X][Y][d])eq.push_back({dis[X][Y][d],dis[X][Y][d]<dis[S.x][S.y][S.d]?-1:Cycle});
		return eq;
	}
}
void dfs(int u,vector<Pll> &cur) {
	if(u>=Q) {
		ll t=-1;
		for(const Pll &x:cur)if(!~x.Se&&(t=x.Fi,1))break;
		if(~t) {
			bool flag=1;
			for(const Pll &x:cur)flag&=(!~x.Se?x.Fi==t:t>=x.Fi&&t%x.Se==x.Fi%x.Se);
			if(flag)tomin(ans,t);
			return;
		}
		Pll res=Ex_CRT::CRT(cur);
		if(res.Fi>=INF&&res.Se>=INF)return;
		t=res.Fi;
		for(const Pll &x:cur)if(x.Fi>res.Fi)tomax(t,res.Fi+(x.Fi-res.Fi-1+res.Se)/res.Se*res.Se);
		return tomin(ans,t),void();
	}
	for(const Pll &x:Bac[u])cur.push_back(x),dfs(u+1,cur),cur.pop_back();
}
signed main() {
	rd(n),rd(m),rd(Q),rd(X),rd(Y);
	FOR(i,0,Q-1)Bac[i]=Bacteria::Constr();
	vector<Pll> cur;
	dfs(0,cur),wr(ans>=INF?-1:ans,'\n');
	return 0;
}
```

---

---

## 作者：dAniel_lele (赞：1)

拆点，将每个位置拆成从上下左右四个方向进入的情况。

原图转化为一个内向基环树。

注意到一个细菌进入陷阱有且仅有四种情况，也就是从上下左右进入，且到达时间一定可以表示成 $kx+b$ 或 $b$。

$4^k$ 枚举每个细菌是从哪个方向进入陷阱的，然后使用 exCRT 合并得到一个 $kx+b$ 或 $b$ 的形式（或无解），对所有情况取最小值即可。

剩余都是 dirty work，具体可以见代码。

总复杂度 $O(4^k\times k^2\times(\log n+\log m)+\operatorname{poly}(nm))$。

```cpp
#include <bits/stdc++.h>
#define int __int128
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
int read(){
	long long x; cin>>x;
	return x;
}
void print(int x){
	cout<<(long long)x;
}
int n,m,k;
struct node{
	int mod,rem,mint;
};
struct pos{
	int x,y;
	char c;
	friend bool operator <(pos a,pos b){
		if(a.x!=b.x) return a.x<b.x;
		if(a.y!=b.y) return a.y<b.y;
		return a.c<b.c;
	}
};
pos go(pos a){
	if(a.c=='R'&&a.y==m) a.c='L';
	if(a.c=='L'&&a.y==1) a.c='R';
	if(a.c=='D'&&a.x==n) a.c='U';
	if(a.c=='U'&&a.x==1) a.c='D';
	if(a.c=='R') a.y++;
	if(a.c=='L') a.y--;
	if(a.c=='D') a.x++;
	if(a.c=='U') a.x--;
	return a;
}
pair<int,int> exgcd(int a,int b){
	int tag=0;
	if(a<b) swap(a,b),tag=1;
	if(b==0){
		return make_pair(1,0);
	}
	auto p=exgcd(b,a%b);
	if(!tag) return make_pair(p.second,p.first-(a/b)*p.second);
	return make_pair(p.first-(a/b)*p.second,p.second);
}
node excrt(node a,node b){
	int d=__gcd(a.mod,b.mod);
	if((a.rem-b.rem)%d!=0){
		node ans; ans.mod=ans.rem=-1;
		return ans;
	}
	auto p=exgcd(a.mod/d,b.mod/d);
//	cout<<a.mod/d*p.first+b.mod/d*p.second<<"\n";
	node ans; ans.mod=a.mod/__gcd(a.mod,b.mod)*b.mod;
	ans.rem=(a.rem+(b.rem-a.rem)/d*p.first*a.mod)%ans.mod;
	ans.mint=max(a.mint,b.mint);
	while(ans.rem<0) ans.rem+=ans.mod;
//	cout<<ans.rem%b.mod<<"\n";
	return ans;
}
map<pos,int> mp;
node a[6][5];
int top[6];
map<char,int> num;
char val[4];
int g[55][55];
signed main(){
	num['R']=0,num['D']=1,num['L']=2,num['U']=3;
	val[0]='R',val[1]='D',val[2]='L',val[3]='U';
	n=read(),m=read(),k=read();
	int dx=read(),dy=read();
	int x[k+1],y[k+1]; char c[k+1];
	for(int i=1;i<=k;i++){
		x[i]=read(),y[i]=read();
		cin>>c[i];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char t; cin>>t;
				g[i][j]=t-'0';
			}
		}
		pos now; int cnt=0;
		c[i]=val[(num[c[i]]+g[x[i]][y[i]])%4];
		now.x=x[i],now.y=y[i],now.c=c[i];
		mp.clear();
		mp[now]=cnt; now=go(now),cnt++;
		while(!mp[now]){
			mp[now]=cnt;
//			cout<<cnt<<" "<<now.x<<" "<<now.y<<" "<<now.c<<"\n";
			cnt++;
			now.c=val[(num[now.c]+g[now.x][now.y])%4];
			now=go(now);
//			cout<<now.x<<" "<<now.y<<"\n";
		}
//		cout<<cnt<<" "<<mp[now]<<" ";
		int cyc=cnt-mp[now];
//		cout<<cyc<<" ";
		cnt=mp[now];
		mp.clear();
		while(!mp[now]){
			mp[now]=cnt;
			if(now.x==dx&&now.y==dy){
				a[i][++top[i]].mint=cnt;
				a[i][top[i]].mod=cyc;
				a[i][top[i]].rem=cnt%cyc;
			}
			cnt++;
			now.c=val[(num[now.c]+g[now.x][now.y])%4];
			now=go(now);
		}
		cnt=0;
		now.x=x[i],now.y=y[i],now.c=c[i];
		while(!mp[now]){
			mp[now]=cnt;
			if(now.x==dx&&now.y==dy){
				a[i][++top[i]].mint=cnt;
				a[i][top[i]].mod=-1;
				a[i][top[i]].rem=-1;
			}
			cnt++;
			now.c=val[(num[now.c]+g[now.x][now.y])%4];
			now=go(now);
		}
		if(top[i]==0){
			cout<<"-1";
			return 0;
		}
//		cout<<top[i]<<"\n";
//		for(int j=1;j<=top[i];j++){
//			cout<<a[i][j].mint<<" "<<a[i][j].mod<<" "<<a[i][j].rem<<"\n";
//		}
	}
	int pw=1; for(int i=1;i<=k;i++) pw*=top[i];
	int minv=1e18;
	for(int j=0;j<pw;j++){
		int cs[k+1],tmp=j;
		for(int i=1;i<=k;i++){
			cs[i]=tmp%top[i]+1;
			tmp/=top[i];
		}
		node pre; pre.mint=0,pre.mod=1,pre.rem=0;
		int eq=0;
		for(int i=1;i<=k;i++){
			if(a[i][cs[i]].mod==-1){
				if(a[i][cs[i]].mint==eq||eq==0){
					eq=a[i][cs[i]].mint;
				}
				else{
					eq=-1;
					break;
				}
			}
			else{
				pre=excrt(pre,a[i][cs[i]]);
				if(pre.mod==-1){
					eq=-1;
					break;
				}
			}
		}
		if(eq==-1) continue;
		while(pre.rem<pre.mint) pre.rem+=pre.mod;
		if(eq==0||((eq-pre.rem>=0)&&((eq-pre.rem)%pre.mod==0))){
			pre.rem=max(pre.rem,eq);
			minv=min(minv,pre.rem);
		}
	}
	if(minv>1e17){
		cout<<-1;
	}
	else print(minv+1);
	return 0;
}
```

---

## 作者：2021hych (赞：1)

# 一、思路的起点
废话有点多：加粗的是重点。

从暴力开始，一个朴素的思路是枚举时间，然后模拟，但肯定爆炸。那么我们思考一下，如果细菌不停运动，会有什么特点呢？在一个时刻下，我们可以用三元组 $(x,y,dir)$ 来表示细菌的状态，即横纵坐标加方向，显然**如果有两个时刻，细菌的状态相同，那么由于路径唯一，之后的状态也会相同，是的，这构成了一个循环**。那么，显然循环节的上限就是状态数的上限，大约：$4 \times 50 \times 50=10000$。

但是，这个循环有什么用呢？有！同余方程。
# 二、算法主体
第一步：预处理。（目的：对于每个细菌，处理出来循环的开始时刻 $bg$，循环节的长度 $p$，掉入陷阱的时刻 $A$）这个可以直接模拟。不过注意的是，掉入陷阱的时刻对应了四种状态，所以要记录四个时刻，如果这四个时刻都不存在，直接输出无解就好了。

第二步：解决循环开始前的答案。注意这里的循环开始前是指在时刻 $maxn$ 之前。其中 $maxn=\max bg$。我们可以先枚举时间，然后枚举每个细菌掉入陷阱时的状态，通过预处理的 $A$ 数组求出时刻，如果所有细菌此时的时刻都和枚举的时刻相等，输出该时刻即可。

第三步：解决循环开始后的答案。思考一下，细菌 $i$ 掉入陷阱的时刻可以用 $A_{i,dir_1} + k_1 \times p_i$。如果在时刻 $t$ 细菌掉入陷阱，则：$t=A_{i,dir_1} + k_1 \times p_i$，这个显然可以写成同余式：

$$t\equiv A_{i,dir_1}\pmod{p_i}$$

同理我们可以列出 $k$ 个同余式组成的线性同余方程。但是我们要列出 $4^k$ 个同余方程组，原因是掉入陷阱的方向有四种，故可以形成 $4^k$ 种可能的激活形式。所以只要做 $4^k$ 次扩展中国剩余定理就好了。

时间复杂度 $O(4^kk \log V+Vk)$，$V$ 大概就是 $10000$ 的规模。可以过。
# 三、代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,K;
int x,y;
char ch,s[60][60];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int t[60][60][4];
int F[15],G[15];
map<char,int>mp;
int maxn,ans=9e18;
struct node {
	int x;
	int y;
	int dir;
	int num[60][60];
	int p;
	int bg;
	int A[4];
}a[15];
void exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
void exCRT() {
	int M=G[1],ansx=F[1];
	for(int i=2;i<=K;i++) {
		int d=__gcd(M,G[i]);
		int C=(F[i]-ansx%G[i]+G[i])%G[i];
		if(C%d) return;
		C/=d;
		int A=M/d;
		int B=G[i]/d;
		int X,Y;
		exgcd(A,B,X,Y);
		X=(X%G[i]+G[i])%G[i];
		ansx+=(__int128)C*X%B*M;
		M*=B;
		ansx%=M;
	}
	while(ansx<maxn) ansx+=M;
	ans=min(ans,ansx);
}
void dfs(int num) {
	if(num>K) {
		exCRT();
		return;
	}
	for(int i=0;i<4;i++) {
		if(a[num].A[i]>=a[num].bg) {
			F[num]=a[num].A[i]%a[num].p;
			G[num]=a[num].p;
			dfs(num+1);
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	mp['U']=0;
	mp['R']=1;
	mp['D']=2;
	mp['L']=3;
	cin>>n>>m>>K;
	cin>>x>>y;
	for(int i=1;i<=K;i++) {
		cin>>a[i].x>>a[i].y>>ch;
		a[i].dir=mp[ch];
		for(int j=1;j<=n;j++) {
			cin>>s[j]+1;
			for(int k=1;k<=m;k++) a[i].num[j][k]=s[j][k]-'0';
		}
		memset(t,0,sizeof(t));
		int cnt=0;
		while(1) {
			cnt++;
			if(t[a[i].x][a[i].y][a[i].dir]) {
				a[i].p=cnt-t[a[i].x][a[i].y][a[i].dir];
				a[i].bg=t[a[i].x][a[i].y][a[i].dir];
				break;
			}
			t[a[i].x][a[i].y][a[i].dir]=cnt;
			if(a[i].x==x&&a[i].y==y) a[i].A[a[i].dir]=cnt;
			a[i].dir=(a[i].dir+a[i].num[a[i].x][a[i].y])%4;
			int xx,yy;
			xx=a[i].x+dx[a[i].dir];
			yy=a[i].y+dy[a[i].dir];
			if(xx<1||xx>n||yy<1||yy>m) a[i].dir=(a[i].dir+2)%4;
			a[i].x+=dx[a[i].dir];
			a[i].y+=dy[a[i].dir];
		}
		bool flag=false;
		for(int j=0;j<4;j++) {
			if(a[i].A[j]) {
				flag=true;
				break;
			}
		}
		if(!flag) {
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=K;i++) maxn=max(maxn,a[i].bg);
	for(int i=0;i<=maxn;i++) {
		bool flag=true;
		for(int j=1;j<=K;j++) {
			bool flag2=false;
			for(int k=0;k<4;k++) {
				if(a[j].A[k]) {
					if(a[j].A[k]<a[j].bg) {
						if(a[j].A[k]==i) {
							flag2=true;
							break;
						}
					}
				}
			}
			if(!flag2) {
				flag=false;
				break;
			}
		}
		if(flag) {
			cout<<i;
			return 0;
		}
	}
	dfs(1);
	cout<<ans;
	return 0;
}

```


---

## 作者：Purslane (赞：0)

# Solution

考虑每个细菌的移动方式为一条链加一个环，且最多有 $4$ 种在陷阱上的方式。$4^K$ 枚举所有情况，暴力解方程即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=55,dx[5]={-1,0,1,0},dy[5]={0,1,0,-1};
int n,m,k,px,py,ans=LONG_LONG_MAX,spin[10][MAXN][MAXN],len[MAXN],X[MAXN],Y[MAXN],C[MAXN]; 
map<char,int> trans={{'U',0},{'R',1},{'D',2},{'L',3}};
pair<int,int> exgcd(int a,int b) {
	if(!b) return {1,0};
	auto pr=exgcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
int solve(vector<pair<int,int>> eq,vector<int> ok) {
	__int128 v=0,mod=1;
	//x=a1 mod b1 = a2 mod b2
	//a1 + x*b1 = a2 + y*b2
	for(auto EQ:eq) {
		__int128 rhs=EQ.first,MOD=EQ.second;
		rhs%=MOD;
		if((v-rhs)%__gcd(mod,MOD)) return LONG_LONG_MAX;
		auto pr=exgcd(mod,MOD);
		pr.first=-pr.first;
		__int128 mul=(v-rhs)/__gcd(mod,MOD);
		pr.first*=mul,pr.second*=mul;
		__int128 nv=v+pr.first*mod;
		v=nv,mod=mod/__gcd(mod,MOD)*MOD;
		v=(v%mod+mod)%mod;
	}
	int mx=v;
	for(auto pr:eq) while(mx<pr.first) mx+=mod;
	ffor(j,0,k-1) if(mx>eq[j].first&&!ok[j]) return LONG_LONG_MAX;
	return mx;
}
int lst_t[MAXN][MAXN][6],fst[MAXN];
vector<int> possible[MAXN];
void dfs(int dep,vector<pair<int,int>> eq,vector<int> ok) {
	if(dep==k+1) return ans=min(ans,solve(eq,ok)),void();
	for(auto id:possible[dep]) {
		auto neq=eq;
		auto nok=ok;
		neq.push_back({id,len[dep]}),nok.push_back(id>=fst[dep]);
		dfs(dep+1,neq,nok);
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>px>>py;
	ffor(i,1,k) {
		char ch;
		cin>>X[i]>>Y[i]>>ch,C[i]=trans[ch];
		ffor(x,1,n) {
			string S;cin>>S;
			ffor(y,1,m) spin[i][x][y]=S[y-1]-'0';
		}
		memset(lst_t,-1,sizeof(lst_t));
		lst_t[X[i]][Y[i]][C[i]]=0;
		int tx=X[i],ty=Y[i],tc=C[i];
		if(tx==px&&ty==py) possible[i].push_back(0);
		ffor(t,1,4*n*m*3) {
			tc=(tc+spin[i][tx][ty])%4;
			if(tx+dx[tc]>n||ty+dy[tc]>m||tx+dx[tc]==0||ty+dy[tc]==0) tc=(tc+2)%4;
			tx+=dx[tc],ty+=dy[tc];
			if(lst_t[tx][ty][tc]!=-1) {fst[i]=lst_t[tx][ty][tc],len[i]=t-lst_t[tx][ty][tc];break ;}
			lst_t[tx][ty][tc]=t;
			if(tx==px&&ty==py) possible[i].push_back(t);
		}
	}
	dfs(1,{},{});
	if(ans==LONG_LONG_MAX) cout<<-1;
	else cout<<ans+1;
	return 0;
}
```

---

