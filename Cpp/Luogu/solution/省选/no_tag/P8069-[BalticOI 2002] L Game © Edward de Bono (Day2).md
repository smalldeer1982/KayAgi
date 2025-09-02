# [BalticOI 2002] L Game © Edward de Bono (Day2)

## 题目描述

L 棋是一种双人棋类游戏，在 $4 \times 4$ 的正方形棋盘上进行。

共有两种棋子：
- L 形棋：大小为 $4$，双方各有一枚；
- 中性棋：大小为 $1$，共两枚，中立。

任意时刻，棋盘上任意格子上方应至多有一枚棋子。

双方轮流操作。一次合法的操作是：先移动己方 L 形棋至一个合法的与当前位置不同的位置，再移动至多一枚中性棋。

无法进行合法操作者败。

![](https://cdn.luogu.com.cn/upload/image_hosting/pmca33zr.png)

记标有网格的 L 形棋操作者为 A，标有斜线者为 B。

若处于上图三种局面之一且 A 先手，则能且仅能将己方 L 形棋移至另外两种局面。此后，A 可以将中性棋之一移至某空格子，或不移动中性棋。故 A 共有 $2 \times (6 + 6 + 1)$ 种操作方案。

若处于下图局面且 A 先手，则 A 由于无法移动其 L 形棋而败，B 胜。

![](https://cdn.luogu.com.cn/upload/image_hosting/9j9uia3u.png)

「妙棋」指：先手进行后存在必胜策略的操作。「败局」指：先手无论如何操作，后手都存在必胜策略的局面。「和棋」指：先手不存在妙棋且不为败局的局面。

尽管棋盘很小，但 L 棋存在超过 $18 \thinspace 000$ 种可能的局面；且在同一时刻先手可能存在多达 $195$ 种操作方案，但其中仅有一种妙棋。

对于给定局面，找到一步妙棋，或判定该局面为败局或和棋。若存在多种妙棋，输出任意一种即可。

## 说明/提示

#### 数据范围

保证给出局面合法。

#### 提示

[BalticOI](https://boi.cses.fi/contests.php) 2002 Day2 B.

你能在不存在妙棋的测试点得分，当且仅当你通过了至少一半存在妙棋的测试点。（注：原题面中为至少一个，但这里取原题解中说法即「一半」。）

由于自定义计分脚本参数配置，暂不支持 AC WA TLE MLE 外的评测状态显示。如果你得到了此外任何一种评测状态，你将得到 UKE。

Subtask #0 为样例；Subtask #1 为数据。

## 样例 #1

### 输入

```
.*** 
#*.x 
###. 
x... ```

### 输出

```
.*** 
x*#x 
###. 
.... ```

## 样例 #2

### 输入

```
...x 
###. 
#*** 
x..* ```

### 输出

```
No winning move 
Draw ```

## 样例 #3

### 输入

```
.### 
x#*x 
***. 
.... ```

### 输出

```
No winning move 
Losing ```

# 题解

## 作者：樱雪喵 (赞：13)

调了 2.5h，比去年省选的时候有点进步 /cf

一眼看起来是有三种胜负态的爆搜，神似 [[省选联考 2023] 过河卒](https://www.luogu.com.cn/problem/P9169)。[给题解打广告 \>w<](https://www.luogu.com.cn/blog/yingxue-cat/solution-p9169)

题里告诉我们状态数只有 $18000$ 多种，也就是说直接暴力把状态转移图建出来是可行的。但是有环怎么判平局呢？

倒序拓扑转移，一个点可以入队当且仅当：

- 它存在至少一个必败的出边；
- 它所有的出边胜负态都已经被确定。

依次确定胜负状态，若初始状态最后仍没有入过队，则平局。

然后剩下的就是大模拟了。卡常技巧：

- 对于 L 形棋，相比于记录一个点和 $8$ 个方向（这有大量的不合法需要特判），记录 $2\times 3$ 的矩形和 $4$ 个方向是更优的选择；
- 用二进制而不是奇怪 hash 对状态直接压缩；
- map 很慢，如果用了奇怪 hash 建议手写哈希表；
- 两个中立点没有差别，钦定坐标较小的在前面可以减少一半状态；
- 钦定第一个棋子为先手，省去记录先后手的两倍状态常数。

本人代码踩遍了以上所有坑，喜提最劣解，建议不要参考。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9') 
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=6,M=1e5+15;
const int mod=1000019;
int tot,bck[M];
struct hashtable
{
    
    struct edge{int nxt,x,w;} e[mod+5];
    int head[mod+5],cnt;
    il int find(int x)
    {
        for(int i=head[x%mod];i;i=e[i].nxt) if(e[i].x==x) return e[i].w;
        tot++; e[++cnt]={head[x%mod],x,tot},head[x%mod]=cnt,bck[tot]=x; return tot;
    }
}Mp;
char s[N][N];
struct node
{
    int op;
    struct L {int x,y,tp;} l[2];
    struct X {int x,y;} x[2];
    node() {memset(x,-1,sizeof(x)),memset(l,-1,sizeof(l)),op=-1;}
};
int ans[M],vis[M];
vector<int> e[M],E[M];
il node trans(int x)
{
    x=bck[x]; node a;
    for(int i=1;i>=0;i--) a.x[i].y=x%10,x/=10,a.x[i].x=x%10,x/=10;
    for(int i=1;i>=0;i--) a.l[i].tp=x%10,x/=10,a.l[i].y=x%10,x/=10,a.l[i].x=x%10,x/=10;
    a.op=x%10;
    return a;
}
int dx[8][4],dy[8][4];
int c[N][N];
int cx[4]={-1,0,1,0},cy[4]={0,1,0,-1};
il void write(int x)
{
    node a=trans(x);
    memset(c,-1,sizeof(c));
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<4;j++)
        {
            int x=a.l[i].x+dx[a.l[i].tp][j],y=a.l[i].y+dy[a.l[i].tp][j];
            c[x][y]=i; 
        }
        int x=a.x[i].x,y=a.x[i].y;
        c[x][y]=2; 
    }
    for(int i=0;i<4;i++,printf("\n"))
        for(int j=0;j<4;j++) 
        {
            if(c[i][j]==-1) printf(".");
            else if(c[i][j]==0) printf("*");
            else if(c[i][j]==1) printf("#");
            else printf("x");
        }
}
il int hsh(node a)
{
    int res=a.op;
    if(a.x[0].x>a.x[1].x||(a.x[0].x==a.x[1].x&&a.x[0].y>a.x[1].y)) swap(a.x[0],a.x[1]);
    for(int i=0;i<=1;i++) res=res*10+a.l[i].x,res=res*10+a.l[i].y,res=res*10+a.l[i].tp;
    for(int i=0;i<=1;i++) res=res*10+a.x[i].x,res=res*10+a.x[i].y;

    return Mp.find(res);
}
il void init()
{
    dx[0][0]=0,dy[0][0]=0; dx[0][1]=-1,dy[0][1]=0; dx[0][2]=-2,dy[0][2]=0; dx[0][3]=0,dy[0][3]=1;
    for(int i=0;i<=3;i++) dx[1][i]=-dx[0][i],dy[1][i]=dy[0][i];
    for(int i=0;i<=3;i++) dx[2][i]=-dx[0][i],dy[2][i]=-dy[0][i];
    for(int i=0;i<=3;i++) dx[3][i]=dx[0][i],dy[3][i]=-dy[0][i];
    for(int j=4;j<8;j++) for(int i=0;i<=3;i++) dx[j][i]=dy[j-4][i],dy[j][i]=dx[j-4][i];
}
il bool check(node a)
{
    memset(c,-1,sizeof(c));
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<4;j++)
        {
            int x=a.l[i].x+dx[a.l[i].tp][j],y=a.l[i].y+dy[a.l[i].tp][j];
            if(x<0||x>=4||y<0||y>=4||c[x][y]!=-1) return 0;
            c[x][y]=i; 
        }
        int x=a.x[i].x,y=a.x[i].y;
        if(x<0||x>=4||y<0||y>=4||c[x][y]!=-1) return 0;
        c[x][y]=i; 
    }
    return 1;
}
int out[M],in[M],to[M];
void build(node s)
{
    queue<node> q; q.push(s);
    while(!q.empty())
    {
        node u=q.front(); q.pop(); int hu=hsh(u);
        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int tp=0;tp<8;tp++) 
            {
                node nxt=u; nxt.l[u.op]={i,j,tp},nxt.op=u.op^1;
                if((i==u.l[u.op].x&&j==u.l[u.op].y&&tp==u.l[u.op].tp)||!check(nxt)) continue;
                for(int id=0;id<=1;id++)
                for(int x=0;x<4;x++)   
                    for(int y=0;y<4;y++)
                    {
                        node nxt=u; nxt.l[u.op]={i,j,tp},nxt.op=u.op^1;
                        nxt.x[id]={x,y};
                        if(check(nxt)) 
                        {
                            int h=hsh(nxt);
                            e[h].push_back(hsh(u)),out[hu]++;
                            E[hu].push_back(h);
                            if(!vis[h]) 
                            {
                                vis[h]=1;
                                q.push(nxt);
                            } 
                        }
                    }
            }
    }
}
il void solve()
{
    queue<int> q;
    for(int i=1;i<=tot;i++) if(!out[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        if(ans[u]!=-1) continue;
        for(auto v:E[u]) if(!ans[v]) {ans[u]=1,to[u]=v;break;}
        if(ans[u]==-1) ans[u]=0;
        for(auto v:e[u]) {out[v]--;if((!out[v]||ans[u]==0)&&ans[v]==-1) out[v]=0,q.push(v);}
    }
}
signed main()
{
    for(int i=0;i<4;i++) scanf("%s",s[i]);
    node st; init();
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            if(s[i][j]=='x') 
            {
                if(st.x[0].x==-1) st.x[0]={i,j};
                else st.x[1]={i,j}; continue;
            }
            if(s[i][j]=='.') continue;
            int qwq=0;
            for(int w=0;w<4;w++) 
            {
                int x=i+cx[w],y=j+cy[w];
                if(x<0||x>=4||y<0||y>=4) continue;
                if(s[x][y]==s[i][j]) qwq++;
            }
            if(qwq!=2) continue;
            for(int tp=0;tp<8;tp++)
            {
                bool flag=1;
                for(int J=0;J<4;J++)
                {
                    int x=i+dx[tp][J],y=j+dy[tp][J];
                    if(x<0||x>=4||y<0||y>=4||s[x][y]!=s[i][j]) flag=0;
                }
                if(flag) {st.l[s[i][j]=='#']={i,j,tp};break;}
            }
        }
    st.op=1;
    build(st);
    memset(ans,-1,sizeof(ans));
    solve();
    int hst=hsh(st);
    if(ans[hst]!=1) 
    {
        printf("No winning move\n");
        if(ans[hst]==-1) printf("Draw\n");
        else printf("Losing\n");
        return 0;
    }
    write(to[hst]);
    return 0;
}
```

---

## 作者：Maverik (赞：9)



拆成先手和后手点连边，倒着转移。能到达任意必败态的必胜，只能到达必胜态的必败。环若都指向必胜态，上面的状态都平局。

对于 L 形的处理，不妨记录一个点和 $8$ 个向量集合，这样 check 之类的就都不用脑子了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10,n=4;
const int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};

int idx,start,deg[maxn],ans[maxn],fail[maxn];
vector<int>e[maxn],g[maxn];
inline void add(int x,int y){ g[x].push_back(y),e[y].push_back(x),deg[x]++; }
vector<int>dir[9];

char s[10][10],res[10][10];
int vis[10][10],arr[2][maxn];
inline bool inside(int x,int y){ return 0<=x&&x<n&&0<=y&&y<n; }

struct board{ int i0,j0,i1,j1,x0,y0,o0,x1,y1,o1; }sta[maxn];
int ID[4][4][4][4][4][4][8][4][4][8];
inline int id(board &st)
{
	return ID[st.i0][st.j0][st.i1][st.j1]
	[st.x0][st.y0][st.o0][st.x1][st.y1][st.o1];
} 
inline bool check(int i0,int j0,int i1,int j1,int x0,int y0,int o0,int x1,int y1,int o1)
{
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) vis[i][j]=0;	
	vis[i0][j0]++,vis[i1][j1]++,vis[x0][y0]++,vis[x1][y1]++;
	for(auto d:dir[o0]){ x0+=dx[d],y0+=dy[d]; if(!inside(x0,y0)) return false; vis[x0][y0]++; }
	for(auto d:dir[o1]){ x1+=dx[d],y1+=dy[d]; if(!inside(x1,y1)) return false; vis[x1][y1]++; }
	int Cnt=0;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){ Cnt+=vis[i][j]; if(vis[i][j]>1) return false; }
	return Cnt==10;
}
inline void col(int x)
{
	auto [i0,j0,i1,j1,x0,y0,o0,x1,y1,o1]=sta[x];
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) res[i][j]='.';	
	res[i0][j0]=res[i1][j1]='x',res[x0][y0]='#',res[x1][y1]='*';
	for(auto d:dir[o0]) x0+=dx[d],y0+=dy[d],res[x0][y0]='#';
	for(auto d:dir[o1]) x1+=dx[d],y1+=dy[d],res[x1][y1]='*';
}


inline void solve()
{
	dir[0]={2,4,4}; dir[1]={4,1,1};
	dir[2]={1,3,3}; dir[3]={3,2,2};
	dir[4]={1,4,4}; dir[5]={3,1,1};
	dir[6]={2,3,3}; dir[7]={4,2,2};
	
	for(int i0=0;i0<n;i0++) for(int j0=0;j0<n;j0++)
	for(int i1=0;i1<n;i1++) for(int j1=0;j1<n;j1++) if(i0!=i1 || j0!=j1)
	for(int x0=0;x0<n;x0++) for(int y0=0;y0<n;y0++) for(int o0=0;o0<8;o0++)
		if(x0!=i0 || y0!=j0) if(x0!=i1 || y0!=j1)
	for(int x1=0;x1<n;x1++) for(int y1=0;y1<n;y1++) for(int o1=0;o1<8;o1++)
		if(x0!=x1 || y0!=y1) if(i0!=x1 || j0!=y1) if(i1!=x1 || j1!=y1)
	if(check(i0,j0,i1,j1,x0,y0,o0,x1,y1,o1))
		ID[i0][j0][i1][j1][x0][y0][o0][x1][y1][o1]=++idx,
		sta[idx]=(board){i0,j0,i1,j1,x0,y0,o0,x1,y1,o1};
	for(int i=0;i<n;i++) cin>>s[i];	
	for(int i=1;i<=idx;i++)
	{
		col(i); bool flag=true;
		for(int x=0;x<n;x++) for(int y=0;y<n;y++) if(res[x][y]!=s[x][y]) flag=false;
		if(flag){ start=i; break; }
	}

	queue<pii>q; q.push(pii(0,start));
	while(!q.empty())
	{
		pii p=q.front(); q.pop();
		
		board nxt=sta[p.second];
		if(p.first==0)
		{
			for(int i=0;i<4;i++) for(int j=0;j<4;j++) for(int o=0;o<8;o++)
			{
				nxt=sta[p.second],nxt.x0=i,nxt.y0=j,nxt.o0=o;
				int nxt_id=id(nxt),to;
				if(nxt_id && nxt_id!=p.second)
				{
					for(int x=0;x<4;x++) for(int y=0;y<4;y++)
					{
						nxt.i0=x,nxt.j0=y,to=id(nxt);
						if(to)
						{
							add(p.second,to+idx);
							if(!arr[1][to]) arr[1][to]=true,q.push(pii(1,to));
						}
					}
					nxt.i0=sta[p.second].i0,nxt.j0=sta[p.second].j0;
					for(int x=0;x<4;x++) for(int y=0;y<4;y++)
					{
						nxt.i1=x,nxt.j1=y,to=id(nxt);
						if(to)
						{
							add(p.second,to+idx);
							if(!arr[1][to]) arr[1][to]=true,q.push(pii(1,to));
						}
					}
					nxt.i1=sta[p.second].i1,nxt.j1=sta[p.second].j1;
				}
			}
		}
		else
		{
			for(int i=0;i<4;i++) for(int j=0;j<4;j++) for(int o=0;o<8;o++)
			{
				nxt=sta[p.second],nxt.x1=i,nxt.y1=j,nxt.o1=o;
				int nxt_id=id(nxt),to;
				if(nxt_id && nxt_id!=p.second)
				{
					for(int x=0;x<4;x++) for(int y=0;y<4;y++)
					{
						nxt.i0=x,nxt.j0=y,to=id(nxt);
						if(to)
						{
							add(p.second+idx,to);
							if(!arr[0][to]) arr[0][to]=true,q.push(pii(0,to));
						}
					}
					nxt.i0=sta[p.second].i0,nxt.j0=sta[p.second].j0;
					for(int x=0;x<4;x++) for(int y=0;y<4;y++)
					{
						nxt.i1=x,nxt.j1=y,to=id(nxt);
						if(to)
						{
							add(p.second+idx,to);
							if(!arr[0][to]) arr[0][to]=true,q.push(pii(0,to));
						}
					}
					nxt.i1=sta[p.second].i1,nxt.j1=sta[p.second].j1;
				}
			}
		}
	}


	queue<int>Q;
	for(int i=1;i<=2*idx;i++) if(!deg[i]) Q.push(i);
    while(!Q.empty())
    {
        int x=Q.front(); Q.pop();
		if(ans[x]) continue;
		for(auto y:g[x]) if(ans[y]<0) { fail[x]=y,ans[x]=1; break; }
		if(!ans[x]) ans[x]=-1;
		for(auto y:e[x]){ deg[y]--; if(!deg[y] || ans[x]<0) deg[y]=0,Q.push(y); }
    }

	if(ans[start]>0)
	{
		col(fail[start]-idx);
		for(int i=0;i<n;i++,cout<<'\n') for(int j=0;j<n;j++) cout<<res[i][j];
	}
	else if(ans[start]==0) cout<<"No winning move\nDraw\n";
	else cout<<"No winning move\nLosing\n";
}

signed main()
{
	ios::sync_with_stdio(false);cin.tie(NULL);
	solve();
}
```

---

