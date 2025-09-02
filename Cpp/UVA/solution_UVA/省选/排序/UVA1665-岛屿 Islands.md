# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)

# 题解

## 作者：犇犇犇犇 (赞：8)

## 这题竟然没有C++党的题解

看到这题。这不是求连通块么。看了下数据范围。一个个当然会超时啦。于是就自然的想到用并查集去求连通块。

并查集指支持合并和查找，并不支持“拆”。可是这道题的连通块是一点点减少的。于是我们可以想到把整个问题倒过来做，让水每年下降，把露出水面的点并上去，这就没问题了。

所以本蒟蒻大概思路是这样的。

**先把所有的点根据高度排序。用并查集保存连通块。最高的点作为父节点，然后向周围合并露出水面的点。**

## 代码：
```
#include<bits/stdc++.h>
#define map mapp //避开关键字
using namespace std;
int fa[1005*1005],ans;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int find(int x)
{
    if(fa[x]!=x)
        fa[x]=find(fa[x]);
    return fa[x];
}  //并查集模板
struct node
{
    int x,y;
    int h;
}a[1005*1005]; //用结构体记录每个点的情况，方便排序
int map[1005][1005],r[100005],n,m;
bool cmp(node a,node b)
{
    return a.h<b.h;
}
int main()
{
    int t,i,j,p,ans,ti,s,k;
    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>n>>m;
        for (i=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                cin>>map[i][j];
                s=i*m+j; //二维化为一维
                a[s].x=i;
                a[s].y=j;
                a[s].h=map[i][j];
            }
        cin>>ti;
        for(i=0;i<ti;i++)
            cin>>r[i];
        memset(fa,-1,sizeof(fa)); //并查集初始化为-1
        sort(a,a+n*m,cmp); //排序
        k=n*m-1;
        for(i=ti-1;i>=0;i--)
        {
            if(r[i]<a[k].h) //水位如果比当前高度低
            {
                while(k>=0 && r[i]<a[k].h) 
                {
                    if(fa[a[k].x*m+a[k].y]==-1) //这个点没有合并过
                    {
                    	fa[a[k].x*m+a[k].y]=a[k].x*m+a[k].y; //自己成为父节点
                    	ans++; //块数+1
                    }
                    for(j=0;j<4;j++) //四向往周围合并
                    {
                        int x,y,tx,ty; 
                        x=a[k].x+dx[j];
                        y=a[k].y+dy[j];
                        if(x>=0 && x<n && y>=0 && y<m && map[x][y]>r[i]) 
                        {
                            if(fa[x*m+y]!=-1) //可以合并
                            {
                                tx=find(a[k].x*m+a[k].y);
                                ty=find(x*m+y);
                                if(tx!=ty)
                                {
                                    fa[tx]=ty;
                                    ans--; //让块数-1
                                }
                            }
                        }
                    }
                    k--;  //这个点走完了
                }
                if(k<0) //所有点都走过了
                {
                    while(i>=0)
                    {
                        r[i--]=ans; //倒叙
                    }
                    break;
                }
          	}
            r[i]=ans; 
        }
        for(i=0;i<ti;i++)
            cout<<r[i]<<" "; //输出
        cout<<endl;
    }
}

```


---

## 作者：Nartsam (赞：2)

### 并查集 + 离线倒着做
首先看到题目的数据范围，我们显然可以意识到每一次都在整个网格上求一次联通块肯定是行不通的~~T到爽~~，所以我们需要换一种思路

通过观察（~~瞪眼~~），我们发现由于 **水位是单调不降的** ，所以在某一时刻当一个格子被淹没后，它就再也没有出头之日了，因此在之后的求解过程中我们可以直接忽略它，也就是**离线倒着做**（顺便说一下，[【JSOI 2008】星球大战](https://www.luogu.org/problemnew/show/P1197)这道题跟这个题思路很像，也是离线倒着做，但比这题简单一些，有兴趣的同学可以做一下）

首先我们先读入数据（不要忘记初始化），对于每个网格，我们都用**二分查找**找到最大的小于该点权值的位置，并把它 $push$ 到一个 $vector$ 里，方便以后的操作。然后我们倒序枚举天数，把当前联通块的个数加 $vector$ 内元素的个数，然后把它们都压进一个队列里  _*（注意一定不要忘记弹出 $vector$ 中的元素！！！，否则如果遇到连续几天的水位相等就会造成重复计算，我就因为这个地方WA了好几天调不出来）_  ，广搜就可以，每当发现可以合并的网格时就合并，然后把联通块的个数$--$ ，因为**每一次合并都代表联通块的个数减少$1$**。

程序还是比较好实现的，注意一下细节就好了。

除了样例之外，我还造了一组数据，供大家测试：

```
Sample Input
case 1: （样例）
1
4 5
1 2 3 3 1
1 3 2 2 1
2 1 3 4 3
1 2 2 2 2
5
1 2 3 4 5

case 2:
2
5 5
2 9 5 1 3 
1 1 10 6 4 
6 10 5 1 3 
4 1 3 8 1 
1 3 1 6 5 
7
2 2 7 7 7 8 8 
5 5
8 8 3 8 8 
1 7 4 9 10 
3 10 6 6 9 
9 2 9 8 4 
3 5 9 5 4 
7
4 4 5 6 7 8 9 

Sample Output
case 1:
2 3 1 0 0

case 2:
2 2 4 4 4 3 3 
2 2 2 4 5 4 2 
```


代码如下：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
const int MAXN=1000+7;
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1}; //方向数组
int a[MAXN][MAXN],belong[MAXN][MAXN],vis[MAXN][MAXN],level[MAXN*100];   //注意不要忘了开到1e5
int n,m,d,T,ans[MAXN*100],num;
int fa[MAXN*MAXN];
vector<pair<int,int> > tim[MAXN*100];
inline int get1(pair<int,int> x){
    return x.first;
}
inline int get2(pair<int,int> x){
    return x.second;
}
void setup(){     //初始化
    memset(vis,0,sizeof(vis));
    memset(belong,0,sizeof(belong));
    for(register int i=0;i<MAXN*MAXN;i++) fa[i]=i;
    for(int i=0;i<MAXN;i++) tim[i].clear();
    num=0; n=m=d=0;
}
inline int GetPos(int x){    //二分查找合适的位置
    int l=1,r=d,pos=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(level[mid]<x){
            pos=mid; l=mid+1;
        }
        else r=mid-1;
    }
    return pos;
}
void prework(){     //处理出每个点该在的位置
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=m;j++){
            int pos=GetPos(a[i][j]);
            if(pos) tim[pos].push_back(make_pair(i,j));
            belong[i][j]=pos;
        }
    }
}
int Find(int x){    //并查集查找
    if(fa[x]!=x) fa[x]=Find(fa[x]);
    return fa[x];
}
void Union(pi x,pi y){    //并查集合并
    int tx=n*(get1(x)-1)+get2(x),ty=n*(get1(y)-1)+get2(y);
    tx=Find(tx); ty=Find(ty);
    fa[ty]=tx;
}
bool Judge(pi x,pi y){    //判断是否属于同一集合
    int tx=n*(get1(x)-1)+get2(x),ty=n*(get1(y)-1)+get2(y);
    return Find(tx)==Find(ty);
}
pi Go(pi x,int twd){
    return make_pair(get1(x)+dx[twd],get2(x)+dy[twd]);
}
bool check(pair<int,int> x,int now){
    if(get1(x)>n||get1(x)<1||get2(x)>m||get2(x)<1) return 0;
    if(belong[get1(x)][get2(x)]<now) return 0;
    return 1;
}
void Update(int now){     //广搜
    queue<pi> q;
    for(int i=(int)tim[now].size()-1;i>=0;i--){
    	q.push(tim[now][i]); tim[now].pop_back();   
        //注意一定一定不要忘记弹出！！！
	}
    while(!q.empty()){
        pair<int,int> pos=q.front(); q.pop();
        int x=get1(pos),y=get2(pos);
        if(vis[x][y]) continue;
        vis[x][y]=1;
        for(int twd=0;twd<4;twd++){
            pair<int,int> nxt=Go(pos,twd);
            if(check(nxt,now)&&(!Judge(nxt,pos))){
                Union(nxt,pos); --num;  //不要忘了-1
                if(!vis[get1(nxt)][get2(nxt)]) q.push(nxt);
            }
        }
    }
}
int main(){
    scanf("%d",&T);
    while(T--){
        setup();
        scanf("%d %d",&n,&m);
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j) scanf("%d",&a[i][j]);
        scanf("%d",&d);
        for(int i=1;i<=d;++i) scanf("%d",&level[i]);
        prework();
        for(int i=d;i>=1;i--){
            num+=tim[i].size();
            Update(i);
            ans[i]=num;
        }
        for(int i=1;i<=d;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：liuyuanpei (赞：1)

本题建议降绿。

本题题意是求每个询问时间的连通块个数，暴力用 DFS 明显超时，时间复杂度 $O(T \times nm)$。

我们不难想到[并查集](https://www.luogu.com.cn/article/y11hyya8)~~（个人博客笔记）~~，但因为并查集不能用二维，所以要降为一维进行解决。大致代码如下：

```cpp
for (int i=1;i<=n;i++){
    for (int j=1;j<=m;j++){
        cin >>mp[i][j];
        a[i*m+j-m].x=i;
        a[i*m+j-m].y=j;
        a[i*m+j-m].h=mp[i][j];
    } 
}
```

这里注意，如果坐标从 1 开始保存，$a$ 数组有值部分是 $m$ 到 $n\times m+m$，所以要整体左移 $m$。

我们考虑在水上涨过程中可能出现集合一分为二的情况，我们可以让水从全部淹掉的状态水位**下降**，从而使用并查集。

代码：

```cpp
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <vector>
# include <set>
# include <map>
using namespace std;
int dis[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//方向 
int fa[1000005],r[1000005],ans[1000005];
int mp[1005][1005];
struct node {
	int x,y,h;//坐标和高度 
}a[1000005];
bool cmp (node a,node b){//排序 
	return a.h<b.h;
}
int find(int x){//并查集查找 
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio (false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T; 
	cin >>T;
	while (T--){
		int n,m,t,tans=0;
    	cin >>n>>m;
    	for (int i=0;i<=n*m;i++)//并查集初值 -1 
    		fa[i]=-1;
		for (int i=1;i<=n;i++){
    		for (int j=1;j<=m;j++){
				cin >>mp[i][j];
    			a[i*m+j-m].x=i;
				a[i*m+j-m].y=j;
	    		a[i*m+j-m].h=mp[i][j];//二维降一维
				//从 1 开始保存要整体左移 m 
			} 
		}
		sort(a+1,a+1+n*m,cmp);//排序 
		cin >>t;
		for (int i=1;i<=t;i++)	
			cin >>r[i];
		int sp=n*m;//从后往前遍历（水从淹没向下降） 
		for (int i=t;i>0;i--){
			if (r[i]<a[sp].h){//没有淹没 
				while (sp>0&&r[i]<a[sp].h){//没有淹没求连通块 
					if (fa[a[sp].x*m+a[sp].y-m]==-1){
						fa[a[sp].x*m+a[sp].y-m]=a[sp].x*m+a[sp].y-m;//建立集合 
						tans++;
					}
					for (int j=0;j<4;j++){
						int tx=a[sp].x+dis[j][0],ty=a[sp].y+dis[j][1];//向四个方向走 
						if (tx>0&&tx<=n&&ty>0&&ty<=m&&mp[tx][ty]>r[i]){
							if (fa[tx*m+ty-m]!=-1){
								int dx=find(a[sp].x*m+a[sp].y-m);
								int dy=find(tx*m+ty-m);
								if (dx!=dy) fa[dx]=dy,tans--;
							}
						}
					}
					sp--;//开始下一个点 
				}
				if (sp<1){//水不能淹没任何一格 
					while (i>0){
						ans[i]=tans;
						i--;
					}
					break;
				} 
			}
			ans[i]=tans;//保存答案 
		}
		for (int i=1;i<=t;i++)
			cout <<ans[i]<<" ";
		cout <<endl;
	} 
    return 0;
}
```

最后给大家留一个测试数据便于大家测试：

```
Sample Input:
2
4 5
1 2 3 3 1
1 3 2 2 1
2 1 3 4 3
1 2 2 2 2
5
1 2 3 4 5
6 8
696 773 379 368 208 48 355 102 
884 969 185 775 713 198 154 756 
811 564 793 298 485 98 369 418 
877 337 445 591 633 433 60 552 
976 17 862 402 22 540 188 992 
15 384 264 491 625 939 270 699 
8
327 397 532 541 561 692 732 917 

Sample Output:
2 3 1 0 0
4 2 7 7 7 7 7 4 
```

---

## 作者：ModestCoder_ (赞：1)

**题目大意**

输入一个n*m的矩阵，每个格子里都有一个[1,10^9]的正整数。再输入T个整数ti，对于每个ti，输出矩阵中大于ti的数组成了多少个联通块（上下左右相连，斜着不联通）。 

有Z组数据 

数据范围 

1≤n,m≤1000 

0≤t1≤t2≤···≤tT≤10^9 

1≤T≤10^5 
0≤Z≤20

【题解】 

首先想到暴力方法，对于每个ti，进行遍历，时间复杂度O(ZTnm)，完全Tle

然后我发现可以利用0≤t1≤t2≤···≤tT≤10^9这一性质，用离线的方法。 

而且我发现，ti越小，联通块的总面积是越大的，而且是从t i+1的联通块发展过来的，那么就倒序扫t数组，同时扩散联通块

然后我发现扫t的过程中很难确定到底矩阵中那个数大于ti，由于ti范围可以到10^9，不能开桶，所以想到对矩阵中的数进行排序 

排序可以把矩阵拉成一个序列进行排序，排序之前记录好每个数的坐标即可 

然后从大到小扫矩阵中的数，同时跟一个j，表示当前的数x，是满足tj< x< t j+1的，同时再跟一个ans，初始化为0，然后每进一个数，ans+1，用并查集进行合并，若四周的数大于tj，而且两数属于不同的块，那么合并、ans-1

分析时间复杂度：O(Z(nmlog(nm)+nmα(nm)+T))其中α为并查集常数，很小

Code：
```
var
    a:array[0..2000000] of record
        x,y,num:longint;
    end;
    s:array[0..1000,0..1000] of record
        num,x:longint;
    end;
    b,f,print:array[0..2000000] of longint;
    p,q,n,m,ans,x,y,z,i,j,k,t,sum1,sum2:longint;
    dx:array[1..4] of longint = (-1,0,0,1);
    dy:array[1..4] of longint = (0,-1,1,0);

function get(k:longint):longint;

begin
    if f[k] <> k then f[k] := get(f[k]);
    get := f[k];
end;

procedure swap(var x,y:longint);
var
    tmp:longint;

begin
    tmp := x; x := y; y := tmp;
end;

procedure sort(l,r:longint);
var
    i,j,mid:longint;

begin
    i := l; j := r; mid := a[(l + r) >> 1].num;
    repeat
        while a[i].num > mid do inc(i);
        while a[j].num < mid do dec(j);
        if i <= j then
        begin
            swap(a[i].x,a[j].x);
            swap(a[i].y,a[j].y);
            swap(a[i].num,a[j].num);
            inc(i); dec(j);
        end;
    until i > j;
    if i < r then sort(i,r);
    if l < j then sort(l,j);
end;

begin
    readln(q);
    for p := 1 to q do
    begin
        readln(n,m);
        for i := 1 to n do
        begin
            for j := 1 to m do
            begin
                x := (i - 1) * m + j;
                read(a[x].num);
                a[x].x := i; a[x].y := j;
            end;
            readln;
        end;
        sort(1,n * m);
        for i := 1 to n * m do
        begin
            s[a[i].x][a[i].y].num := a[i].num;
            s[a[i].x][a[i].y].x := i;
        end;
        readln(t);
        for i := 1 to t do read(b[i]);
        for i := 1 to n * m do f[i] := i;
        ans := 0; j := t; a[n * m + 1].num := 0;
        for i := 1 to n * m + 1 do
        begin
            while a[i].num <= b[j] do
            begin
                print[j] := ans;
                dec(j);
                if j = 0 then break;
            end;
            if j = 0 then break;
            inc(ans);
            for k := 1 to 4 do
            begin
                x := a[i].x + dx[k];
                y := a[i].y + dy[k];
                if (x < 1) or (y < 1) or (x > n) or (y > m) then continue;
                if s[x][y].num > b[j] then
                begin
                    sum1 := get(s[x][y].x); sum2 := get(i);
                    if sum1 <> sum2 then
                    begin
                        f[sum1] := sum2;
                        dec(ans);
                    end;
                end;
            end;
        end;
        for i := 1 to t do write(print[i],' ');
        writeln;
    end;
end.

```

---

## 作者：DerrickLo (赞：0)

看到求连通块个数考虑并查集，先二分预处理出每个点是在哪个时间沉没的，然后倒着加边，对于每个在当前时间存在而在下一时间沉没的点，我们可以将它与它四周的未沉没点连边，然后在这过程中就能动态维护连通块个数了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int z,n,m,t,b[100005],a[1005][1005],ans[100005],fa[1000005],vis[1000005],dx[]={1,-1,0,0},dy[]={0,0,1,-1};
vector<pair<int,int>>ve[100005];
int find(int x){
	return(fa[x]==x)?x:fa[x]=find(fa[x]);
}
int get(int i,int j){
	return(i-1)*m+j;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>z;
	while(z--){
		cin>>n>>m;
		for(int i=1;i<=n*m;i++)fa[i]=i,vis[i]=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
		cin>>t;
		for(int i=0;i<=t+1;i++)ve[i].clear();
		for(int i=1;i<=t;i++)cin>>b[i];
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			int xx=lower_bound(b+1,b+t+1,a[i][j])-b-1;
			ve[xx].push_back({i,j});
		}
		int cnt=0;
		for(int i=t;i;i--){
			for(auto v:ve[i])vis[get(v.first,v.second)]=1,cnt++;
			for(auto v:ve[i]){
				for(int j=0;j<4;j++){
					int xx=v.first+dx[j],yy=v.second+dy[j];
					if(xx<1||xx>n||yy<1||yy>m||!vis[get(xx,yy)])continue;
					int fx=find(get(v.first,v.second)),fy=find(get(xx,yy));
					if(fx==fy)continue;
					fa[fx]=fy,cnt--;
				}
			}
			ans[i]=cnt;
		}
		for(int i=1;i<=t;i++)cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
} 
```

---

