# [ICPC 2021 WF] Crystal Crosswind

## 题目描述

你是一个科学团队中的一员，正在开发一种在分子级别上成像晶体结构的新技术。这种技术涉及在晶体表面吹送一股非常微弱的风，并以不同的角度吹送，以便检测边界（通过暴露给风的分子来表示）。这个过程会重复进行，每个吹送方向的边界都会被记录下来。你的团队已经收集到了数据，但是如同大多数应用科学一样，现在真正的工作，即分析工作必须开始。

对于给定的晶体，你将接收到风以不同方向吹送过晶体表面的数据，以及每个风吹过时遇到的所有边界的位置。对于在方向（$w_x, w_y$）吹送的风，边界被定义为位置（$x, y$），使得一个分子位于（$x, y$），并且没有分子位于（$x-w_x, y-w_y$）。请注意，出于技术原因，$w_x$ 和 $w_y$ 不一定互质。

这些数据可能无法唯一确定晶体的结构。你必须找到两个与观测数据一致且分子数最少和最多的晶体结构。

例如，在第一个示例输入中，通过给定的风，出现了9个不同的分子。必须有一个在位置（$3, 3$）处的分子，否则（$4, 2$）将成为第三股风的边界。出于类似的原因，必须在位置（$4, 4$）和（$5, 5$）处有分子。不能再有其他分子，因为它们会导致一些风的附加观测结果。

## 样例 #1

### 输入

```
6 6 3
1 1 3 3 1 1 3 2 2
0 2 6 3 1 1 3 2 2 6 4 5 3 4 2
1 -1 4 1 3 2 4 3 5 4 6
```

### 输出

```
..#...
.#.#..
#.#.#.
.#.#.#
..#.#.
...#..

..#...
.#.#..
#.#.#.
.#.#.#
..#.#.
...#..
```

## 样例 #2

### 输入

```
5 4 2
1 0 6 1 1 4 1 2 2 5 2 2 3 3 4
0 -1 7 1 1 4 1 5 2 2 3 3 4 4 4 5 4
```

### 输出

```
#..#.
.#..#
.#...
..###

##.##
.##.#
.###.
..###
```

# 题解

## 作者：iyaang (赞：4)

[幸福的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17548843.html)

[题目链接](https://www.luogu.com.cn/problem/P9439)

首先找出必须是 `.` 和 `#` 的位置，剩下的就可以随便填，最少分子就是都填 `.`，最多分子就是都填 `#`。

根据题意，对于给定的任意 $(x,y)$，它们都位于边界上，必定是 `#`；同时只要其所对应的 $(x - w_x,y - w_y)$ 合法，则 $(x - w_x,y - w_y)$ 必定为 `.`，于是我们就得到了边界限制下的最初答案。

接下来考虑不在边界上的 $(x,y)$，对于**任意的** $(w_x,w_y)$，要么 $(x,y)$ 为 `.`，要么 $(x,y)$ 和 $(x - w_x,y - w_y)$ 都为 `#`。首先可以通过边界上的 $(x,y)$ 根据后者条件选定出剩下的 `#`，对于剩下的还没有被钦定的位置再进行下面的筛选：如果**任意的** $(w_x,w_y)$，$(x - w_x,y - w_y)$ 都不合法，此时有没有别的位置会使其成为 `#`，那么这个位置只能成为 `.`。最后我们再将后者条件反过来考虑，如果 $(x,y)$ 为 `.` 且 $(x + w_x,y + w_y)$ 还未被钦定，此时其他条件都已经用完了，那么 $(x + w_x,y + w_y)$ 只能为 `.` 了。至此，题目里面提供的信息都已经用上，仍没有被遍历的节点就可以随便填了。

可以发现，上面的两次扩散过程都可以轻松的用 bfs 来实现，于是复杂度 $\mathcal O(nm)$。本人代码为了图省事两次 bfs 缩在一起了，看起来可能有点抽象。

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
        putchar(ch);
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
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
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
    static const int MAX=1010;
    static const int bMAX=11;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int n,m,T;
    int wx[bMAX],wy[bMAX],x,y,all;
	int ans[MAX][MAX],vis[MAX][MAX][bMAX];
	queue<pii> q;
	
    inline void lmy_forever()
	{	
		auto check=[&](int x,int y)->bool
		{
			return x>=1&&x<=n&&y>=1&&y<=m;
		};
	
		read(n,m,T),memset(ans,-1,sizeof ans);
		for(int i=1;i<=T;++i)
		{
			read(wx[i],wy[i],all);
			while(all--)
			{
				read(x,y),ans[x][y]=1,vis[x][y][i]=1;
				if(check(x-wx[i],y-wy[i])) ans[x-wx[i]][y-wy[i]]=0;
			}
		}
		
		auto bfs=[&](int res)->void
		{
			for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(ans[i][j]==res) q.emplace(mp(i,j));
			while(!q.empty())
			{
				auto now=q.front(); q.pop();
				for(int i=1;i<=T;++i)
				{
					int tx=now.fi+(res?-1:1)*wx[i],ty=now.se+(res?-1:1)*wy[i];
					if(check(tx,ty)&&ans[tx][ty]==-1) ans[tx][ty]=res,q.emplace(mp(tx,ty));
				}
			}
		};
		
		bfs(1);
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(ans[i][j]==-1)
		{
			int flag=0;
			for(int k=1;k<=T;++k) flag|=(!check(i-wx[k],j-wy[k]));
			if(flag) ans[i][j]=0;
		}
		bfs(0);
		
		for(int i=1;i<=m;++i,puts("")) for(int j=1;j<=n;++j) putchar(ans[j][i]==1?'#':'.');
		puts("");
		for(int i=1;i<=m;++i,puts("")) for(int j=1;j<=n;++j) putchar(ans[j][i]==0?'.':'#');
		puts("");
    }
}

bool Med;

signed main()
{
    //file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：feizhu_QWQ (赞：1)

## 题意简化

### [题目传送门](https://www.luogu.com.cn/problem/P9439)

看起来很难，做起来也不会。\
首先我们理解一下题意：\
他说有一个二维空间，他每次会吹一次风，每次风都会被这个方向的第一个 `#` 拦下来，然后他就会告诉你这个 `#` 的坐标。\
让你求这个结构最多分子长啥样，最少分子长啥样？

## 思路

我们先把所有点设为 `?`，也就是不确定，因为他有两个答案，一个分子要最少，一个分子要最多。\
接着我们可以发现，如果风是从 $(x-wx,y-wy)$ 吹来的，那么我们称这个点为入风口，所以 $(x,y)$ 为边界 `#`，那么入风口一定没有分子，不然这个风就会被入风口的分子挡下来。\
如果说 $(x,y)$ 为 `.` 怎么办？\
那么他们的入风口一定是 `#`，不然就没人挡风了。\
那么我们又称 $(x+wx,y+wy)$ 为出风口，如果说 $(x,y)$ 是一个 `#`，出风口就无法确定，但如果 $(x,y)$ 没有分子，那么出风口也一定没有分子。\
所以，我们就可以根据这个规律推出所有的位置，至于没有被遍历的地方，我们看情况行事。\
推的话我们采取 BFS，可以先通过输入的所有点推的两个点，然后再 BFS。\
万恶的出题人，输出要先 $m$ 再 $n$！\
~~没事找事~~。\
但要注意了，有可能在求入风口和出风口的时候数组越界了，所以我们用一个判断函数同时也是 BFS 的判断函数来判越界。\
注：出风口和入风口可能过大或过小，所以枚举要从 $-n$ 到 $2n$，$m$ 同理～\
懂吧！\
代码：

```cpp
#include<bits/stdc++.h>
#define int long long//long long好习惯~
using namespace std;
int n,m,k;
struct node
{
	int x,y;
}q[18000005];
int head=0,tail=1;
char a[3005][3005];
node wind[100];//记录每阵风的方向
bool check(int x,int y)
{
	if(x<1||x>n||y<1||y>m) return false;
	return true;
}
void work(int x,int y)
{
	if(check(x,y)&&a[x][y]=='?') return;//如果说是问号，也就是说不能用它推其他的
	for(int i=1;i<=k;i++)
	{
		int xx=0,yy=0;
		if(check(x,y)&&a[x][y]=='#')//如果说这个点是分子，就可以用它推出入风口
		{
			xx=x-wind[i].x;
			yy=y-wind[i].y;
		}
		else//否则只能用他推出出风口
		{
			xx=x+wind[i].x;
			yy=y+wind[i].y;
		}
		if(check(xx,yy)&&a[xx][yy]=='?')//如果我们要推的点还没推出来
		{
			if(check(x,y)) a[xx][yy]=a[x][y];//推
			else a[xx][yy]='.';//推
			head++;
			q[head].x=xx;//手写队列万岁！
			q[head].y=yy;
		}
	}
	return;
}
void bfs()
{
	for(int i=-n;i<=2*n;i++)
	{
		for(int j=-m;j<=2*m;j++)
		{
			work(i,j);//一开始先全部入队
		}
	}
	while(head-tail+1>0)
	{
		int x=q[tail].x;
		int y=q[tail].y;
		tail++;
		work(x,y);//广搜模板
	}
	return;
}
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]='?';//初始设为？
		}
	}
	for(int i=1;i<=k;i++)
	{
		int wx,wy;
		cin>>wx>>wy;
		wind[i].x=wx,wind[i].y=wy;//记录风的方向
		int t;
		cin>>t;
		for(int j=1;j<=t;j++)
		{
			int x,y;
			cin>>x>>y;
			a[x][y]='#';
			if(check(x-wx,y-wy)) a[x-wx][y-wy]='.';
		}
	}
	bfs();
	for(int j=1;j<=m;j++)//输出先m后n!
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i][j]=='?') cout<<".";
			else cout<<a[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i][j]=='?') cout<<"#";
			else cout<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```

~~建议升紫~~\
下课！！！

---

## 作者：yr409892525 (赞：1)

### 题解 [P9439 [ICPC2021 WF] Crystal Crosswind](https://www.luogu.com.cn/problem/P9439)
我们设晶体有三种状态。           
1. 障碍物（有结晶）
2. 空地（无结晶）
3. 未知

我们可以通过空地推出所有方格的状态。                       
所以我们就可以根据题目中给出的边界，来推出所有的状态。             

所以我们不妨枚举每一个方格，当是我们要注意边界。          
例如 $(-1,-1)$ 当这个坐标增加或减少有可能在合法范围内。           
也就是 $(-1+w_x,-1+w_y)$ 有可能在合法范围内。             

所以我们的枚举范围是：           
$-dx \le x \le dx \times 2$，$-dy \le y \le dy \times 2$。               
当一个 $(x,y)$ 在合法范围内，并且状态未知，那就不可以由当前方格来推出其他的方格。             
当一个 $(x,y)$ 不在合法范围内，状态默认为空地。                  

所以我们枚举每一个方格，前提是当前的方格已经确定了状态。               
如果 $(x,y)$ 是一个边界，并且他不是第 $i$ 个风的边界。                   
就说明 $(x-w_x,y-w_y)$ 必须是障碍物。            
反过来一样，如果 $(x,y)$ 不是边界，当 $(x+w_x,y+w_y)$ 不是 $i$ 个风的边界，就是空地。         

我们设当前方格为 $(x,y)$ 它能推出的方格为 $(xx,yy)$。                    
那么如果 $(xx,yy)$ 是未知的并且 $(xx,yy)$ 是合法的。                
有两种情况：
1. $(x,y)$ 是合法的，$(xx,yy)$ 的状态为 $(x,y)$ 的状态。
2. $(x,y)$ 是不合法的，$(xx,yy)$ 的状态为空地。

但是执行一次不可以，我们可以使用广搜进行递推。            
递推的代码一样。

但有一些状态还是无法确定的。          

当要输出最少的结晶，未知的就输出没有结晶。        
当要输出最多的结晶，未知的就输出有结晶。           

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int M=1e5+5,N=1e3+5; 
int n,m,k;
int dx[N],dy[N];
char a[N][N];
bool check(int x,int y){
	if(x>=1 && x<=n && y>=1 && y<=m) return 1;
	return 0;
}
struct code{
	int x,y;
};
void bfs(){
	queue<code> q;
	for(int x=-n;x<=n*2;x++){
		for(int y=-m;y<=m*2;y++){
			if(check(x,y) && a[x][y]=='?') continue;
			for(int i=1;i<=k;i++){
				int xx,yy;
				if(check(x,y) && a[x][y]=='#'){
					xx=x-dx[i];
					yy=y-dy[i];
				}else{
					xx=x+dx[i];
					yy=y+dy[i];
				}
				if(check(xx,yy) && a[xx][yy]=='?'){
					if(check(x,y)) a[xx][yy]=a[x][y];
					else a[xx][yy]='.';
					q.push({xx,yy});
				}
			}
		}
	}
	while(!q.empty()){
		code u=q.front();
		q.pop();
		int x=u.x;
		int y=u.y;
		for(int i=1;i<=k;i++){
			int xx,yy;
			if(check(x,y) && a[x][y]=='#'){
				xx=x-dx[i];
				yy=y-dy[i];
			}else{
				xx=x+dx[i];
				yy=y+dy[i];
			}
			if(check(xx,yy) && a[xx][yy]=='?'){
				if(check(x,y)) a[xx][yy]=a[x][y];
				else a[xx][yy]='.';
				q.push({xx,yy});
			}
		}
	}
	return ;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]='?';
		} 
	}
	for(int i=1;i<=k;i++){
		cin>>dx[i]>>dy[i];
		int p;
		cin>>p;
		while(p--){
			int x,y;
			cin>>x>>y;
			a[x][y]='#';
			int xx=x-dx[i];
			int yy=y-dy[i];
			if(check(xx,yy)){
				a[xx][yy]='.';
			}
		}
	}
	bfs();
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(a[i][j]=='?') cout<<'.';
			else cout<<a[i][j];
		} 
		cout<<"\n";
	}
	cout<<"\n";
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(a[i][j]=='?') cout<<'#';
			else cout<<a[i][j];
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：program_xwl (赞：0)

个人主观难度 $\color{purple}省选/NOI-$。
## 细节：

- 先输入列再输入行。
- $w_x$ 和 $w_y$ 不一定互质。
- $-d_x \le w_x\le d_x,-d_y \le w_y\le d_y$ 表示风可以从一些玄学的地方吹过来。

## 思路：

在晶体中，每个格点可以大体分为中状态：

1. 必须为分子结构。
2. 必须为非分子结构。
3. 为两种结构都合法。

如果要得到包含最少分子数量的结构，就要让第 $3$ 状态全部为分子结构，反之则让全为非分子结构。我们的任务就是确定所有 $1,2$ 状态格点。

首先，根据题意，风的边界都是分子结构，任意一个风结构坐标向对应风向的反方向移动一次（即点 $x,y$ 移到点 $x-w_x,y-w_y$）必定是非分子结构，我们只能通过这些信息来推其他的格点。

我们定义 $(x,y)$ 的入风口是 $(x-w_x,y-w_y)$，出风口是 $(x-w_x,y-w_y)$。

首先，枚举所有可以作为晶体任意一点入风口的坐标，因为 $-d_x \le w_x\le d_x,-d_y \le w_y\le d_y$，所以我们的枚举范围应该是：

![](https://cdn.luogu.com.cn/upload/image_hosting/fmkxyb9m.png)

- 如果 $(x,y)$ 在晶体范围内，且状态未知，那么不能就用其来推出其他格点，因为分子结构和非分子结构推出的格点是不同的。

- 如果 $(x,y)$ 不在晶体范围内，那么它的类别为非分子结构。

- 如果以上两条都满足，就开始以该点为起始点开始刮风。我们枚举所有的风，设当前的风向是 $w_x,w_y$，它吹向的点是 $(nx,ny)$：

  如果 $(x,y)$ 是某阵风的边界，且它对应的风不是当前这阵，那么它的入风口一定是分子结构，否则 $(x,y)$ 必须作为该阵风的边界，与前面的条件相矛盾。反过来也一样，如果 $(x,y)$ 是不是任意阵风的边界，那么那么它的入风口一定是分子结构。推导时有两种情况：

  - 如果 $(nx,ny)$ 和 $(x,y)$ 都是在晶体范围内的，$(nx,ny)$ 当前为未知，那么 $(nx,ny)$ 的状态就是 $(x,y)$ 的状态。
  - 如果 $(x,y)$ 不在晶体范围之内，$(nx,ny)$ 在晶体范围内且为未知，那么 $(nx,ny)$ 的状态为未知。

这就是第一轮递推过程，接下来的递推应该用广搜，方便快速找到下一个递推位置。枚举范围同上。

代码比较复杂，我打了注释。

## 代码：
>莫抄袭，棕了你的名，空悲切！
```cpp
#include <bits/stdc++.h>
using namespace std;

struct pos {int x,y;} w[15];
int m,n,k;
char mp[1005][1005];
queue<pos>q;

bool check_pos(int x,int y)//检查当前坐标是否在晶体范围内
{
	if(x < 1 || y < 1 || x > n || y > m) return 0;
	return 1;
}

void bfs(void)
{
	for(int x = -n+1;x <= 2*n;x++)//第一轮递推，推出来的全部加入队列，以便下一轮递推
	{
		for(int y = -m+1;y <= 2*m;y++)
		{
			if(check_pos(x,y) && mp[x][y] == 0) continue;//如果递推的起始点必须是已知的
			for(int i = 1;i <= k;i++)
			{
				int nx,ny;
				if(check_pos(x,y) && mp[x][y] == '#')
				{
					nx = x-w[i].x;
					ny = y-w[i].y;
				}else
				{
					nx = x+w[i].x;
					ny = y+w[i].y;
				}
				if(check_pos(nx,ny) && mp[nx][ny] == 0)
				{
					if(check_pos(x,y)) mp[nx][ny] = mp[x][y];
					else mp[nx][ny] = '.';
					q.push({nx,ny});
				}
			}
		}
	}
	while(q.size())
	{
		pos u = q.front();
		q.pop();
		int x = u.x,y = u.y;
		for(int i = 1;i <= k;i++)
		{
			int nx,ny;
			if(check_pos(x,y) && mp[x][y] == '#')
			{
				nx = x-w[i].x;
				ny = y-w[i].y;
			}else
			{
				nx = x+w[i].x;
				ny = y+w[i].y;
			}
			if(check_pos(nx,ny) && mp[nx][ny] == 0)
			{
				if(check_pos(x,y)) mp[nx][ny] = mp[x][y];
				else mp[nx][ny] = '.';
				q.push({nx,ny});
			}
		}
	}
	return;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1;i <= k;i++)
	{
		int n2;
		cin >> w[i].x >> w[i].y >> n2;
		for(int j = 1;j <= n2;j++)
		{
			int x,y;
			cin >> x >> y;
			mp[x][y] = '#';
			if(check_pos(x-w[i].x,y-w[i].y)) mp[x-w[i].x][y-w[i].y] = '.';
		}
	}
	bfs();
	for(int j = 1;j <= m;j++)//本题最大的坑：先列再行
	{
		for(int i = 1;i <= n;i++)
		{
			if(mp[i][j] == 0 || mp[i][j] == '.') cout << '.';//既然要分子结构最少，那么把所有未知的都填成非分子结构
			else if(mp[i][j] == '#') cout << '#';
		}
		cout << '\n';
	}
	cout << '\n';//注意中间还有一个换行
	for(int j = 1;j <= m;j++)
	{
		for(int i = 1;i <= n;i++)
		{
			if(mp[i][j] == '.') cout << '.';
			else if(mp[i][j] == 0 || mp[i][j] == '#') cout << '#';//既然要分子结构最多，那么把所有未知的都填成分子结构
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：2b2b2bbb (赞：0)

我们先来看看数据范围是多少。$dx,dy \le 10^3 , k \le 10$。那么根据这个范围，我们可以对我们的时间复杂度有一个猜测，$O(n \times m)$ 或 $O(n \times m \times k)$。

然后根据题目的意思，我们可以发现如果 $(x , y)$ 是障碍物，春来的风是 $(wx , wy)$ 那么我们的 $(x - wx , y - wy)$ 就一定不是障碍物。

我们可一先来看看样例中初始的时候是什么样子的。

![https://cdn.luogu.com.cn/upload/image\_hosting/nvro5ii9.png?x-oss-process=image/resize,m\_lfit,h\_170,w\_225](https://cdn.luogu.com.cn/upload/image_hosting/nvro5ii9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这就是图片的基础形状。然后最重要的一点其实是题目中的一句话。题目说：必须有一个在位置 $(3 , 3)$ 处的分子，否则 $(4 , 2)$ 将成为第三股风的边界。

我们主要就是要理解这句话，如果你能够理解了这句话的含义，那么你就已经相当于做完一半了，因为这句话就是关键。

那么我们就可以定义三种类型的字符，井号，点和问号，它们分别表示障碍物，空地和未知。

然后我们可以定义一个出风口和一个入风口。

入风口：$(x - wx , y - wy)$。

出风口：$(x + wx , y + wy)$。

那么如果 $(x , y)$ 是障碍物，为了不让它选成边界那么出风口就是障碍物。

然后如果 $(x , y)$ 是点，说明出风口也一定是点。

然后我们我们的每一个点首先要找到入风口和出风口的最小值和最大值，最小值就是 $(1 -dx , 1 -dy)$ 最大值就是 $(dx + dx , dy + dy)$ 这是界限。

还有这道题目的输入你要仔细观察吗，你会发现是先是列再是行。还有我们一开始要全部为 $?$ 号，因为我们还不知道当前位置是什么。

那么合法并且是井号，我们就只看入风口，否则说明是点只看出风口。

然后如果这个点我们不知道是什么，也就是问号说明之前的点在范围内，井号就可以推出井号，点就可以推出点。否则这个点就是点号。

然后要放入队列之中哦，出循环之后我们就直接来一次广度优先搜索，将我们之前放入的点再来一次同样的操作。

还有，我们再一开始的时候我们并不知道任何的答案，所以在一切都没开始的时候全部都是问号。所以不要定义忘记初始值了。

然后想要井号的数量要最少，那么我们就在最后将所有不确定的答案改为点号。

然后想要井号的数量要最多，那么我们就在最后将所有不确定的答案改为井号。
## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t;
int l[1005],r[1005];//每个位置的风
int a[1005][1005];//存储的图，0是点，1是井，2是问号
bool check(int x,int y){//是否合法
	if(x >= 1 && x <= n && y >= 1 && y <= m){
		return true;
	}
	return false;
}
struct pi{
	int x,y;
};
void bfs(){
	queue<pi>q;
	for(int x = 1 - n ; x <= 2 * n ; x ++){//边界别忘了
		for(int y = 1 - m ; y <= 2 * m ; y ++){
			if(check(x , y) && a[x][y] == 2){//如果是问号就直接退出
				continue;
			}
			//接下来就按照题解一个一个的枚举吧
			for(int i = 1 ; i <= t ; i ++){
				int x_1,y_1;
				if(check(x , y) && a[x][y] == 1){
					x_1 = x - l[i];
				}else{
					x_1 = x + l[i];
				}
				if(check(x , y) && a[x][y] == 1){
					y_1 = y - r[i];
				}else{
					y_1 = y + r[i];
				}
				if(check(x_1 , y_1) && a[x_1][y_1] == 2){
					if(check(x , y)){
						a[x_1][y_1] = a[x][y];
					}else{
						a[x_1][y_1] = 0;
					}
					q.push({x_1 , y_1});//不要忘记还有一次搜索
				}
			}
		}
	}
	while(!q.empty()){
		pi u = q.front();//取出点
		int x = u.x;
		int y = u.y;
		q.pop();
		//然后直接将上面的代码复制即可，注意点已经选好了，不要复制错
		for(int i = 1 ; i <= t ; i ++){
			int x_1,y_1;
			if(check(x , y) && a[x][y] == 1){
				x_1 = x - l[i];
			}else{
				x_1 = x + l[i];
			}
			if(check(x , y) && a[x][y] == 1){
				y_1 = y - r[i];
			}else{
				y_1 = y + r[i];
			}
			if(check(x_1 , y_1) && a[x_1][y_1] == 2){
				if(check(x , y)){
					a[x_1][y_1] = a[x][y];
				}else{
					a[x_1][y_1] = 0;
				}
				q.push({x_1 , y_1});
			}
		}
	}
	return;
} 
signed main(){
	cin >> n >> m >> t;//列 行
	for(int i = 1 ; i <= n ; i ++){
		for(int j = 1 ; j <= m ; j ++){
			a[i][j] = 2;
		}
	}
	for(int i = 1 ; i <= t ; i ++){
		cin >> l[i] >> r[i];//记录每一次的风
		int k;
		cin >> k;
		for(int j = 1 ; j <= k ; j ++){
			int x,y;
			cin >> x >> y;
			a[x][y] = 1;
			if(check(x - l[i] , y - r[i])){//还有入风口哦
				a[x - l[i]][y - r[i]] = 0;
			}
		}
	}
	bfs();
	//最后就输出即可，不要弄反了
	for(int j = 1 ; j <= m ; j ++){
		for(int i = 1 ; i <= n; i ++){	
			if(a[i][j] == 2){
				cout << '.';
			}else{
				if(a[i][j] == 1){
					cout << "#";
				}else{
					cout << '.';
				}
			} 
		}
		cout << endl;
	}
	cout << endl;
	for(int j = 1 ; j <= m ; j ++){
		for(int i = 1 ; i <= n; i ++){	
			if(a[i][j] == 2){
				cout << '#';
			}else{
				if(a[i][j] == 1){
					cout << "#";
				}else{
					cout << '.';
				}
			} 
		}
		cout << endl;
	}
	return 0;
}

```

---

## 作者：sieve (赞：0)

# [P9439 [ICPC2021 WF] Crystal Crosswind](https://www.luogu.com.cn/problem/P9439)

## 思路

这题的核心是推导。

我们将题目中的晶体分为几种状态：

`#`：有晶体，称为障碍物。

`.`：没有晶体，称为平地。

`?`：目前无法确认的位置。

首先，根据题目描述，我们可以发现，题目中给出的扫到的点都是障碍物，不然不会被风扫到。

那么，我们定义入风口为 $(x - w_x,y - w_y)$，出风口为 $(x + w_x,y + w_y)$。其中 $x$ 和 $y$ 是输入中扫到的地点的行和列。

如果入风口在这个晶体范围内，那么这里一定是一个平地，否则就会被拦住。于是，我们就推出了一个大致的样子了。

接下来就要继续推出其它的平地了。

我们这里采用广度优先搜索，因为输入中给出的 $w_x$ 和 $w_y$ 可能是负数，也可能是正数，所以我们确定起点的枚举范围是 $-dx \sim dx \times 2,-dy \sim dy \times 2$。

我们能够从当前格子推出下一个的标准是什么？当前格子的位置已知。所以，如果当前格子的状态时未知，可以直接跳过。

假设我们当前的位置为 $(x,y)$，通过风（入风口和出风口）推出的下一个点的坐标为 $(nx,ny)$，那么，就又有两种情况了：

- 当前的位置合法（$1 \le x \le n , 1 \le y \le m$），则 $(nx,ny)$ 可以继承当前格子的状态。

- 当前的位置不合法（$1 \le x \le n , 1 \le y \le m$），则 $(nx,ny)$ 的状态为平地。

然后，我们就可以进行广搜了，和上面的代码（确定起点的代码）一模一样。但是，广搜跑完后，还是会有一些格子无法被确定，也就是状态仍然时 `?`，最后输出的时候还需要判断一下。

既然题目说第一个矩阵的障碍物是最少的，所以我们就将所有状态为 `?` 的格子都设为平地，这样就能保证第一个矩阵的障碍物是最少的。

对于第二个矩阵，把所有状态为 `?` 的格子都设为障碍物，这样就能保证第二个矩阵的障碍物是最多的。

还有，题目中给出的 $dx$ 和 $dy$ 分别是晶体的列和行，但是跑的时候对应的仍然是行和列。

代码还是非常好理解的。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3005;
int n,m,k,wx[N],wy[N];
char vis[N][N];
struct no{
	int x,y;
};
vector<no> wind;
bool check(int x,int y)
{
	return (x>=1&&x<=n&&y>=1&&y<=m);
}
void bfs()
{
	queue<no> q;
	for(int x=-n;x<=n+n;++x)
	{
		for(int y=-m;y<=m+m;++y)
		{
			if(check(x,y)&&vis[x][y]=='?') continue;
			for(int i=1;i<=k;++i)
			{
				int nx=(check(x,y)&&vis[x][y]=='#'?x-wind[i].x:x+wind[i].x);
				int ny=(check(x,y)&&vis[x][y]=='#'?y-wind[i].y:y+wind[i].y);
				if(check(nx,ny)&&vis[nx][ny]=='?')
				{
					vis[nx][ny]=(check(x,y)?vis[x][y]:'.');
					q.push({nx,ny});
				}
			}
		}
	}
	while(!q.empty())
	{
		no u=q.front();
		q.pop();
		int x=u.x,y=u.y;
		for(int i=1;i<=k;++i)
		{
			int nx=(check(x,y)&&vis[x][y]=='#'?x-wind[i].x:x+wind[i].x);
			int ny=(check(x,y)&&vis[x][y]=='#'?y-wind[i].y:y+wind[i].y);
			if(check(nx,ny)&&vis[nx][ny]=='?')
			{
				vis[nx][ny]=vis[x][y];
				q.push({nx,ny});
			}
		}
	}
	return;
}
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			vis[i][j]='?';
		}
	}
	wind.resize(k+1);
	for(int i=1;i<=k;++i)
	{
		int now;
		cin>>wind[i].x>>wind[i].y>>now;
		for(int j=1;j<=now;++j)
		{
			int x,y;
			cin>>x>>y;
			vis[x][y]='#';
			int wx=x-wind[i].x,wy=y-wind[i].y;
			if(check(wx,wy)) vis[wx][wy]='.';
		}
	}
	bfs();
	for(int j=1;j<=m;++j)
	{
		for(int i=1;i<=n;++i)
		{
			cout<<(vis[i][j]!='?'?vis[i][j]:'.');
		}
		cout<<'\n';
	}
	cout<<'\n';
	for(int j=1;j<=m;++j)
	{
		for(int i=1;i<=n;++i)
		{
			cout<<(vis[i][j]!='?'?vis[i][j]:'#');
		}
		cout<<'\n';
	}
	return 0;
}
```

---

