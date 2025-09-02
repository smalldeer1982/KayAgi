# [GCJ 2009 #3] EZ-Sokoban

## 题目描述

Sokoban 是一款著名的日本益智游戏。Sokoban 在日语中意为“仓库管理员”。在这款游戏中，你的目标是将箱子推到仓库中指定的位置。推箱子时，箱子的前后方都必须是空的。这是因为你在推箱子时需要站在箱子的后面，并且每次只能推一个箱子。你不能把箱子推出棋盘，也不能在推箱子时站在棋盘外。

例如，在下图中：

![](https://cdn.luogu.com.cn/upload/image_hosting/449dtvoj.png)

箱子 1 可以向任意四个方向推动，因为它四周的格子都是空的。箱子 2 只能向东或向西推动；它不能向北或向南推动，因为其南侧的格子不是空的。箱子 3 不能向任何方向推动。箱子 4 只能向东或向西推动，因为其南侧有一堵墙。

Sokoban 已被证明是一个 **P-Space 完全** 问题，但我们这里讨论的是一个更简单的变体。在我们的 EZ-Sokoban 变体中，箱子内部装有强力磁铁，必须几乎始终保持相互连接。在“稳定”状态下，所有箱子都必须边与边相连。也就是说，从任意一个箱子出发，都可以通过依次经过与其相邻的箱子，到达任意其他箱子。如果你推动了一个箱子，导致箱子们不再连通，你就进入了“危险模式”。在危险模式下，下一步推动必须使得所有箱子重新连通。

例如，在下图中：

![](https://cdn.luogu.com.cn/upload/image_hosting/sf431enx.png)

当前状态是稳定的，因为所有 4 个箱子都通过边相连。假设你决定将最北边的箱子向西推动：

![](https://cdn.luogu.com.cn/upload/image_hosting/5xwhygv7.png)

现在处于危险模式，因为最北边的箱子与其他箱子不再连通。下一步推动必须让箱子们重新变为连通状态。例如，你可以将最北边的箱子向南推动：

![](https://cdn.luogu.com.cn/upload/image_hosting/x8g8d58g.png)

这样箱子们又重新连接，回到了稳定状态。

一个 Sokoban 谜题由棋盘、箱子的初始布局以及目标布局（即希望箱子最终达到的位置）组成。给定一个 EZ-Sokoban 谜题，请你求出使箱子移动次数最少的解，或者判断该谜题无解。初始和目标布局都不会处于“危险模式”。

为了简化问题，假设你（仓库管理员）可以随时跳到棋盘上的任意空位。

## 说明/提示

**限制条件**

- $1 \leqslant T \leqslant 50$
- $1 \leqslant R, C \leqslant 12$

**小数据集（7 分）**

- 时间限制：3 秒
- $1 \leqslant$ 箱子数量 $\leqslant 2$

**大数据集（10 分）**

- 时间限制：5 秒
- $1 \leqslant$ 箱子数量 $\leqslant 5$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
5 4
....
#..#
#xx#
#oo#
#..#
7 7
.######
.x....#
.x....#
..#oo.#
..#...#
.######
.######
4 10
##########
#.x...o..#
#.x...o..#
##########
3 4
.#x.
.ow.
....```

### 输出

```
Case #1: 2
Case #2: 8
Case #3: 8
Case #4: 2```

# 题解

## 作者：Shadow_T (赞：1)

貌似是这一题首 A 呢，调了一个半小时，遂发题解。

首先我们发现：

- $1 \leq R,C \leq 12$。

数据范围极小，所以可以用爆搜去做。

我们可以考虑使用 bfs 实现。这一题的状态特别多，不想别的普通 dfs，只要判断有没有重复走过某个坐标就行了。对于 bfs 的每一个状态，我存了三个东西：

- 当前已经移动箱子的次数 $num$。

- 前一次的状态是否是危险的 $flag$。

- 当前的整个地图情况 $mp$。

```cpp
struct status
{
    int num;
    bool flag;
    bitset<maxn> mp[maxn];
};
```

然后对于每一个状态，我们都枚举他所有的箱子，往 $4$ 个方向移动。注意要判断箱子的前面和后面没有箱子，也不是墙，也不能超出地图。

然后我们再对移动完的地图跑连通块，如果连通块数量大于 $1$，那么说明这是危险的。如果移动前的 $flag$ 记录下来也是危险的，那么这是无效的移动。否则就在 $flag$ 标记，丢进队列里。如果不危险就没关系。

对于重复状态的判断，我维护了每个状态的哈希，丢进 map 里判断就行了。注意哈希值只要把 $flag$ 和地图 $mp$ 丢进去。

细节巨多，代码自己看。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
void Ios(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
const int maxn=15;
int n,m;
int a[maxn][maxn];
int b[maxn][maxn];
int get(int a,int b)
{
    return a*n+b;
}
struct status
{
    int num;
    bool flag;
    bitset<maxn> mp[maxn];
};
bool comp(status a,status b)
{
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    if(a.mp[i][j]!=b.mp[i][j]) return 0;
    return 1;
}
int box;
status target;
bitset<maxn> A[maxn];
ull Hash(status a)
{
    ull ans=0;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    ans*=131,ans+=(a.mp[i][j]+25);
    ans+=(int)a.flag;
    return ans;
}
map<ull,bool> mp;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

bitset<maxn> vis[maxn];
bitset<maxn> bl[maxn];
void dfs(int x,int y)
{
    for(int i=0;i<4;i++)
    {
        int newx=x+dx[i],newy=y+dy[i];
        if(newx<1||newy<1||newx>n||newy>m) continue;
        if(vis[newx][newy]) continue;
        if(!bl[newx][newy]) continue;
        vis[newx][newy]=1;
        dfs(newx,newy);
    }
}

void solve()
{
    memset(a,0,sizeof a);
    memset(b,0,sizeof b);
    mp.clear();
    box=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        char c;
        cin>>c;
        //2代表箱子 空位0 墙1
        if(c=='.') a[i][j]=b[i][j]=0;
        if(c=='#') a[i][j]=b[i][j]=1;
        if(c=='x') a[i][j]=0,b[i][j]=2;
        if(c=='o') a[i][j]=2,b[i][j]=0,box++;
        if(c=='w') a[i][j]=b[i][j]=2,box++;
    }
    status fir;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        if(b[i][j]==2) target.mp[i][j]=1;
        else target.mp[i][j]=0;
        if(a[i][j]==2) fir.mp[i][j]=1;
        else fir.mp[i][j]=0;
    }

    // for(int i=1;i<=n;i++)
    // for(int j=1;j<=m;j++)
    // cout<<target.mp[i][j]<<(j==m?"\n":"");
    // cout<<"\n";

    queue<status> q;
    fir.flag=fir.num=0;
    q.push(fir);
    mp[Hash(fir)]=1;
    while(!q.empty())
    {
        status t=q.front();

        // for(int i=1;i<=n;i++)
        // for(int j=1;j<=m;j++)
        // cout<<t.mp[i][j]<<(j==m?"\n":"");
        // cout<<"\n";

        q.pop();
        if(comp(t,target))
        {
            cout<<t.num<<"\n";
            return;
        }
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(t.mp[i][j])
        {
            for(int k=0;k<4;k++)
            {
                int newx=i+dx[k],newy=j+dy[k];
                //cerr<<newx<<" "<<newy<<"\n";
                if(newx<1||newy<1||newx>n||newy>m) continue;
                if(t.mp[newx][newy]||a[newx][newy]==1) continue;

                int tx=i-dx[k],ty=j-dy[k];
                if(tx<1||ty<1||tx>n||ty>m) continue;
                if(t.mp[tx][ty]||a[tx][ty]==1) continue;

                status upd=t;
                upd.mp[i][j]=0;
                upd.mp[newx][newy]=1;
                for(int i=1;i<=n;i++)
                {
                    vis[i].reset();
                    bl[i]=upd.mp[i];
                }
                int cnt=0;
                for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                if(bl[i][j]&&!vis[i][j])
                {
                    cnt++;
                    if(cnt>1) break;
                    vis[i][j]=1;
                    dfs(i,j);
                }
                if(cnt>1)
                {
                    if(upd.flag) continue;
                    upd.flag=1;
                }
                else upd.flag=0;
                upd.num++;
                ull hs=Hash(upd);
                if(mp[hs]) continue;
                mp[hs]=1;
                q.push(upd);
            }
        }
    }
    cout<<"-1\n";
}
int main()
{
    Ios();
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cout<<"Case #"<<i<<": ";
        solve();
    }
}
```

[R229121224 记录详情](https://www.luogu.com.cn/record/229121224)

---

## 作者：wang_wen_zhe (赞：0)

## 简要题意

对于一个 $R \times C$ 的棋盘，有不超过 $5$ 个箱子，初始位置和目标位置已知，要求最少的推箱子次数（每次将一个箱子向一个方向推动一格）使得所有箱子在目标位置上。题目定义如果所有箱子是连通的，那么箱子处于稳定状态，否则就是 **危险状态**，如果箱子处于 **危险状态**，那么下次操作必须让它回到稳定状态。箱子的初始状态和目标状态都是稳定的。注意将箱子向某个方向推动时需要保证其相反方向的相邻一格在棋盘内且不是墙。

## 思路及代码实现

这道题我们考虑用 bfs 来求出最小答案。很明显我们需要记录当前箱子的位置、操作次数及是否处于危险状态，于是我们可以定义以下结构体和队列。其中 $s$ 和 $g$ 分别表示箱子的初始和目标位置。

```cpp
struct wei
{
    int x,y;
}s[6],g[6];
struct node
{
    wei a[6];//箱子状态
    bool f;//是否稳定
    int sum;//操作次数
};
queue<node>q;
```

为了判断当前箱子是否连通，我们可以写个 dfs，计算连通的箱子数量，与总箱子数量相比即可。

```cpp
int dfs(int k,node p)
{
    int sum=1;
    ff[k]=true;//被访问过
    for(int i=1;i<=t1;i++)
        if(abs(p.a[i].x-p.a[k].x)+abs(p.a[i].y-p.a[k].y)==1&&!ff[i])//判断 p.a[i] 是否与 p.a[k] 相邻
        {
            sum+=dfs(i,p);
        }
    ff[k]=false;
    return sum;//返回与 k 连通的数量
}
```

同时为了方便比较箱子的位置，我们可以写个排序，这里不多阐述。\
接下来讲最重要的 bfs 部分。首先我们要把初始状态的箱子放入队列。然后对于每一个状态，我们先判断其是否已经与目标位置重合，如果重合可以直接返回答案。随后我们对每个箱子进行判断并移动，判断主要为以下几点：

- 箱子的下个位置是否为空格且在棋盘内。
- 箱子的移动方向的反方向的相邻一格（仓库管理员站的位置）是否为空格且在棋盘内。
- 箱子是否连续处于危险状态。
- 箱子移动后的位置（所有箱子的位置）是否与先前的位置相同。

对于前三点相信大家可以轻松解决，判断第四点是为了防止出现死循环导致时间或内存爆了，那具体怎么做呢？聪明的你应该能想到将当前所有的箱子位置用一种特殊的方式表示，然后在 `unordered_set` 中查找其是否出现过，没有的话就把它也放进去，并更新队列。具体用什么方式表示大家可以用自己熟悉的方式，下面给出一个示例以及 bfs 部分。

```cpp
struct node
{
    wei a[6];
    bool f;
    int sum;
    string getHash() const 
    {
        string s;
        for(int i=1;i<=t1;i++)//t1为箱子总数
            s+=to_string(a[i].x)+","+to_string(a[i].y)+"|";
        return s;
    }
};

int bfs()
{
    while(!q.empty()) q.pop();//把上次剩余的清除
    node b;
    for(int i=1;i<=t1;i++)
        b.a[i]=s[i];
    b.f=b.sum=0;
    q.push(b);
    string hash=b.getHash();
    vis.insert(hash);
    while(!q.empty())
    {
        node p=q.front();
        q.pop();
        if(!p.f)//判断是否已经到达目标位置
        {
            bool fff=true;
            for(int i=1;i<=t1;i++)
                if(p.a[i].x!=g[i].x||p.a[i].y!=g[i].y)
                {
                    fff=false;
                    break;
                }
            if(fff) return p.sum;
        }
        for(int i=1;i<=t1;i++)
        {
            bool f1[4]={1,1,1,1};
            for(int j=1;j<=t1;j++)
                for(int k=0;k<=3;k++)//初步判断是否能向各个方向移动
                    if(p.a[i].x+dx[k]==p.a[j].x&&p.a[i].y+dy[k]==p.a[j].y||p.a[i].x+dx[k]>n||p.a[i].x+dx[k]<=0||p.a[i].y+dy[k]<=0||p.a[i].y+dy[k]>m||p.a[i].x-dx[k]==p.a[j].x&&p.a[i].x-dx[k]>n||p.a[i].y-dy[k]==p.a[j].y||p.a[i].x-dx[k]<=0||p.a[i].y-dy[k]<=0||p.a[i].y-dy[k]>m) f1[k]=false;
            for(int k=0;k<=3;k++)
                if(f1[k])
                {
                    int nx=p.a[i].x+dx[k],ny=p.a[i].y+dy[k];//箱子的下个位置
                    int xx=p.a[i].x-dx[k],yy=p.a[i].y-dy[k];//仓库管理员的位置
                    if(ch[nx][ny]=='#'||ch[xx][yy]=='#') continue;
                    b={{},0,0};
                    for(int j=1;j<=t1;j++)
                        if(i==j) b.a[j]={nx,ny};
                        else b.a[j]={p.a[j].x,p.a[j].y};
                    sort(b.a+1,b.a+1+t1,cmp);//按一定方式排序
                    b.sum=p.sum+1;
                    b.f=(dfs(1,b)<t1);
                    if(b.f&&p.f) continue;//判断是否连续处于危险状态
                    string st=b.getHash();
                    if(vis.count(st)) continue;//判断移动后的箱子位置是否出现过
                    vis.insert(st);
                    q.push(b);
                }
        }
    }
    return -1;//无解返回-1
}
```

最后是主函数，较为简单，不多阐述，直接上代码。

```cpp
int main()
{
    cin>>T;
    for(int ii=1;ii<=T;ii++)//方便输出
    {
        cin>>n>>m;
        t1=t2=tot=0;
        vis.clear();//多测不清空，爆零两行泪
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>ch[i][j];
                if(ch[i][j]=='w') s[++t1]={i,j},g[++t2]={i,j};
                else if(ch[i][j]=='o') s[++t1]={i,j};
                else if(ch[i][j]=='x') g[++t2]={i,j};
            } 
        }
        sort(s+1,s+1+t1,cmp);
        sort(g+1,g+1+t1,cmp);
        ans=1e9;
        cout<<"Case #"<<ii<<": "<<bfs()<<"\n";
｝
```

:::info[完整代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
int T,n,m,t1,t2,ans,tot;
char ch[15][15];
struct wei
{
    int x,y;
}s[6],g[6];
struct node
{
    wei a[6];
    bool f;
    int sum;
    string getHash() const 
    {
        string s;
        for(int i=1;i<=t1;i++)
            s+=to_string(a[i].x)+","+to_string(a[i].y)+"|";
        return s;
    }
};
queue<node>q;
bool ff[13];
int dfs(int k,node p)
{
    int sum=1;
    ff[k]=true;
    for(int i=1;i<=t1;i++)
        if(abs(p.a[i].x-p.a[k].x)+abs(p.a[i].y-p.a[k].y)==1&&!ff[i])
        {
            sum+=dfs(i,p);
        }
    ff[k]=false;
    return sum;
}
bool cmp(wei a,wei b)
{
    return a.x==b.x?a.y<b.y:a.x<b.x;
}
unordered_set<string>vis;
int bfs()
{
    while(!q.empty()) q.pop();
    node b;
    for(int i=1;i<=t1;i++)
        b.a[i]=s[i];
    b.f=b.sum=0;
    q.push(b);
    string hash=b.getHash();
    vis.insert(hash);
    while(!q.empty())
    {
        node p=q.front();
        q.pop();
        if(!p.f)
        {
            bool fff=true;
            for(int i=1;i<=t1;i++)
                if(p.a[i].x!=g[i].x||p.a[i].y!=g[i].y)
                {
                    fff=false;
                    break;
                }
            if(fff) return p.sum;
        }
        for(int i=1;i<=t1;i++)
        {
            bool f1[4]={1,1,1,1};
            for(int j=1;j<=t1;j++)
                for(int k=0;k<=3;k++)
                    if(p.a[i].x+dx[k]==p.a[j].x&&p.a[i].y+dy[k]==p.a[j].y||p.a[i].x+dx[k]>n||p.a[i].x+dx[k]<=0||p.a[i].y+dy[k]<=0||p.a[i].y+dy[k]>m||p.a[i].x-dx[k]==p.a[j].x&&p.a[i].y-dy[k]==p.a[j].y||p.a[i].x-dx[k]<=0||p.a[i].y-dy[k]<=0||p.a[i].y-dy[k]>m||p.a[i].x-dx[k]>n) f1[k]=false;
            for(int k=0;k<=3;k++)
                if(f1[k])
                {
                    int nx=p.a[i].x+dx[k],ny=p.a[i].y+dy[k];
                    int xx=p.a[i].x*2-nx,yy=p.a[i].y*2-ny;
                    if(ch[nx][ny]=='#'||ch[xx][yy]=='#') continue;
                    b={{},0,0};
                    for(int j=1;j<=t1;j++)
                        if(i==j) b.a[j]={nx,ny};
                        else b.a[j]={p.a[j].x,p.a[j].y};
                    sort(b.a+1,b.a+1+t1,cmp);
                    b.sum=p.sum+1;
                    b.f=(dfs(1,b)<t1);
                    if(b.f&&p.f) continue;
                    string st=b.getHash();
                    if(vis.count(st)) continue;
                    vis.insert(st);
                    q.push(b);
                }
        }
    }
    return -1;
}
int main()
{
    cin>>T;
    for(int ii=1;ii<=T;ii++)
    {
        cin>>n>>m;
        t1=t2=tot=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>ch[i][j];
                if(ch[i][j]=='w') s[++t1]={i,j},g[++t2]={i,j};
                else if(ch[i][j]=='o') s[++t1]={i,j};
                else if(ch[i][j]=='x') g[++t2]={i,j};
            } 
        }
        sort(s+1,s+1+t1,cmp);
        sort(g+1,g+1+t1,cmp);
        ans=1e9;
        vis.clear();
        cout<<"Case #"<<ii<<": "<<bfs()<<"\n";
    }
}
```
::::

总的时间复杂度应为 $O (T \times (R \times C)^k)$ 带上一些常数，$k$ 为箱子数。由于题目的特殊限制，bfs 不会跑满，不用担心超时。~~时间开那么大，实际大数据组 1 秒内都能跑完。~~\
这是我的第一篇题解，可能会出现一些错误，如发现错误请私信或在讨论区提出。

---

