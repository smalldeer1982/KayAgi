# [PA 2020] Wycieczka górska

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 4 [Wycieczka górska](https://sio2.mimuw.edu.pl/c/pa-2020-1/wyc/)**

一群 $k$ 个旅行者朋友去了 Byte 山。在最后一天，他们决定组织一场登山比赛，从他们所住的旅店到 Byte 山顶。

每个旅行者都有一张区域地图，它是一个分为 $n$ 行 $m$ 列的矩形；因此地图一共包含 $n\cdot m$ 个区域。旅店位于地图左上角的区域，而山顶则位于地图右下角的区域。Byte 山以其非常均匀而闻名——对于地图上的任何区域，在地图上与之相邻的右面或下面的区域海拔较高，而相邻的左边或上面区域海拔较低。但是，这座山也因潜伏着许多危险地区而闻名。有些地区在地图上标明是非常危险的，因为那里有野生动物居住——所以最好不要到那里去……

你是 Byte 山山脚下的一个小屋的看守人。通过观察每一个旅行者，你已经为他们每个人分配了两个参数 $a_i$ 和 $b_i$，这些参数决定了他们在山坡上的运动速度。具体来说，如果第 $i$ 个旅行者向更高的区域移动，那么他需要 $a_i$ 分钟，如果旅行者向更低的区域移动，则需要 $b_i$ 分钟。你也知道，每个旅行者都会走对他们来说从小屋到山顶最快的路线，并且路线完全在地形图上，而且避开了所有的危险区域。

你想知道最快的人需要多长时间才能到达山顶，有多少人将与最快的人同时爬到山顶。你可以假设，从小屋到山顶至少有一条安全的路线。

## 说明/提示

#### 样例 2 解释

从旅店到山顶只有一条路径，这些旅行者的用时分别是 $13,14,13,13$。

------------

#### 数据范围

**本题采用捆绑测试**

对于一些子任务满足 $k=1$。

对于 $100\%$ 的数据，保证 $2\le n,m\le 2\times 10^3$，$1\le k\le 10^6$，$1\le a_i,b_i\le 10^9$。

## 样例 #1

### 输入

```
5 7 1
......X
X.X..X.
..X.X.X
.X.X...
.....X.
2 1```

### 输出

```
26 1```

## 样例 #2

### 输入

```
2 5 4
.X...
...X.
2 1
2 2
1 7
2 1```

### 输出

```
13 3```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

诈骗。所有人走的路径一定都是一样的。bfs 搜出来即可。

## 给人看的思路

首先，如果没有向上走，那么会向下走 $n-1$ 次。

考虑在整个过程中向上走了 $x$ 次。那么，就要额外向下走 $x$ 次，也就是一共向下走 $x+n-1$ 次。酱紫最后才能到达最后一行。

向左向右同理。

把向上和向左的次数加起来记作 $a$，统称【向回走】。

那么，会【向前走】 $n-1+m-1+a$ 次。

搜出使 $a$ 最小的路径。

## code

```cpp
#include<stdio.h>
#include<deque>
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,p,ans[2333][2333];long long ans1=1ll<<60,ans2;char s[2333][2333];
struct node
{
	int x,y,a;
	inline node(const int&x,const int&y,const int&a):x(x),y(y),a(a){}
};deque<node>q;
main()
{
	read(n);read(m);read(p);
	for(int i=0;i<n;++i)for(int j=0;j<m;s[i][j]^='X',ans[i][j++]=1<<30)
		for(;s[i][j]=nc(),(s[i][j]^'.')&&(s[i][j]^'X'););
	ans[0][0]=0;q.emplace_back(0,0,0);
	for(node i(0,0,0);q.size();)
	{
		i=q.front();q.pop_front();
		if(ans[i.x][i.y]^i.a)continue;
		if(i.x&&s[i.x-1][i.y]&&ans[i.x-1][i.y]>i.a+1)
			q.emplace_back(i.x-1,i.y,ans[i.x-1][i.y]=i.a+1);
		if(i.y&&s[i.x][i.y-1]&&ans[i.x][i.y-1]>i.a+1)
			q.emplace_back(i.x,i.y-1,ans[i.x][i.y-1]=i.a+1);
		if(i.x<n-1&&s[i.x+1][i.y]&&ans[i.x+1][i.y]>i.a)
			q.emplace_front(i.x+1,i.y,ans[i.x+1][i.y]=i.a);
		if(i.y<m-1&&s[i.x][i.y+1]&&ans[i.x][i.y+1]>i.a)
			q.emplace_front(i.x,i.y+1,ans[i.x][i.y+1]=i.a);
	}
	for(int x,y;p--;)
	{
		read(x);read(y);
		long long qwq=x*(long long)(n-1+m-1+ans[n-1][m-1])+
			y*(long long)(ans[n-1][m-1]);
		if(qwq<ans1)ans1=qwq,ans2=0;
		if(qwq==ans1)++ans2;
	}
	printf("%lld %lld",ans1,ans2);
}
```


---

## 作者：CSPAK_Zhangxiuqi0011 (赞：2)

大家好，今天本蒟蒻又来发题解啦啦啦~  
# 0.题目大致意思
有 $k$ 个人在一个 $n \times m$ 大小的地方从 $(0,0)$ 走到 $(n,m)$，路上有障碍物的地方不可通过。每个人的坐标中任意数值增加则要花 $a _ i$ 分钟，减少则要花 $b _ i$ 分钟。问这些人中最先到 $(n,m)$ 的人花了多少分钟，以及有多少人和最先到的人花的时间一样。
# 1.思路
这题乍眼一看：妈呀！每个人都有可能走不一样的路线，那我每个人都要搜一遍吗？  
如果你还在纠结这个问题，那么你可以想一想：不考虑障碍物，每个人最快所花的时间一定是 $n-1+m-1$（即不绕弯路，直接走整个地图的两条边），见下图（星号代表最快路径）：  
图1.1
```
*******
------*
------*
------*
```
但是，因为有许多障碍物，我们会多走许多的路，例如：  
图1.2
```
*******
------*
*******
*------
*******
```
那么，现在我们将上面图1.1的最短路成为“向前走”，剩下多走的成为“向回走”，那么我们可以发现：**只要你在某一时刻“向回走”了一次（当然这里指的是向下走），那么后面你就需要再用一次向上走的“向回走”补回来。**  
图1.3
```
******
-----*
----+*
------
------
  |
  |
  v
******
-----*
----+*
----*-
----*+
加号代表思路中的“向回走”
```
那么就不难发现，所有“向回走”中有一半是向下走的，有一半是向上走的。当然，所有“向前走”的那 $n-1+m-1$ 步绝对是向上走的，也就是说路径越短，“向回走”的步数就越少，又由于这个“向回走”里面向上走的步数和向下走的步数是 $1:1$ 的，所以“向回走”的步数越少，这条路对于一个人来说花的时间就越短（要是还不能理解的话，你可以想一想：设“向回走”了 $x$ 步，因为一次向下走的“向回走”和一次向上走的“向回走”是成对出现的，所以这个人“向回走”的时间就是 $(a+b) \times \frac{x}{2}$，显然 $x$ 越小这个“向回走”的时间越少）。每一条路径中“向前走”的步数又是一样的，也就是说，**路径长度越小对于一个人来说时间越少，所以所有人都只会选路径长度最小的那一条路径走，也就是说所有人走的路径都是一样的**。  
有的同学就要问了：如果路径长度最小的路径有多条呢？不妨像下图设想一下：两条路径长度相等的路径，它们“向回走”的步数也一样，时间不就一样了吗？  
图1.4
```
********
*------*
*-----**
*-----*-
*-----**
*-***--*
***-****
```
**所以，我们只需要知到路径最短的那条路径的长度就可以根据长度求出“向回走”的步数，进而求出向上走和向下走的步数，继续模拟知道答案。**
# 2. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INT_MAX LONG_LONG_MAX
#define INT_MIN LONG_LONG_MIN
int n,m,k,t[2005][2005],dx[4] = {1,-1,0,0},dy[4] = {0,0,1,-1};
struct node{
	int x,y,step;
}; 
struct children{
	int high,low;
}a[1000005];
queue<node>q;
void bfs(){ 
	q.push({1,1,0});
	t[1][1] = 1;
	while(!q.empty()){
		int l;
		l = q.size();
		while(l--){
			node h;
			h = q.front();
			q.pop();//好习惯——把pop放在前面写以防忘记 
			if(h.x == n && h.y == m){
				int num,minn;
				minn = INT_MAX;
				num = 0;
				int up,down,fast;//up:向上走的步数  down:向下走的步数  fast:即文中"向前走"的步数 
				fast = (n-1)+(m-1);
				down = (h.step-fast)/2;//给看不懂的同学解释一下：现在h.step已经是总步数了，减掉fast就是"向回走"的步数，其中向上走和
				//向下走各占一半，所以除以二。
				//注意：这里要是先算up的话记得还有向上走的fast步。 
				up = h.step-down;
				for(int i = 1;i<=k;i++){
					if(a[i].high*up+a[i].low*down<minn){
						minn = a[i].high*up+a[i].low*down;
						num = 1; 
					}else if(a[i].high*up+a[i].low*down == minn){
						num++;
					}
				}
				//这里不用先把最小值找出来再扫一遍，可以直接这样写。因为就算刚才num已经大于一了，但是
				//只要后面有更优的解，就会把之前的数据覆盖掉。由于找到的最优解一定是id最靠前的那一个人， 
				//后面所有和最优解一样的人都还没有统计，所以一定可以正确的找到答案 
				cout<<minn<<" "<<num<<"\n";
				return;
			}
			for(int i = 0;i<4;i++){
				int nx,ny;
				nx = h.x+dx[i];
				ny = h.y+dy[i];
				if(nx>0 && nx<=n && ny>0 && ny<=m && !t[nx][ny]){
					t[nx][ny]++;
					q.push({nx,ny,h.step+1});
				}
			}
		}
	}
}
signed main() {	
	cin>>n>>m>>k;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			char c;
			cin>>c;
			if(c == 'X'){
				t[i][j] = 1;//这里把状态数组和地图共用一个数组，1表示不能走，0则可以。 
			}
		}
	} 
	for(int i = 1;i<=k;i++){
		cin>>a[i].high>>a[i].low;
	}
	bfs();
	return 0;
}
```

---

## 作者：A_small_WA (赞：2)

思路：广搜一次即可，因为保证所有人的路径是一样的。

但是这个时候，~~大脑发育迟缓的~~我想到了一个~~弱智~~问题：假设有两条路线可以到达山顶，第一条路需要向上走 $u_1$ 次，向下走 $d_1$ 次；第二条路线需要向上走 $u_2$ 次，向下走 $d_2$ 次。若此时 $u1>u2,d1<d2$，那么对于不同速度的人，两条路都有可能出现最优解，应该选哪条呢？

但事实证明，我想多了。因为不会出现这种情况。因为 $u_1-d_1=u_2-d_2=m+n$ 所以当 $d_2>d_1$ 时，必有 $u_2>u_1$。

想明白了这点，我们就可以大胆写代码了。对整个图进行一遍 ```bfs``` 操作后确定最小的向上走的步数 $sumu$ 和向下走的步数 $sumd$。这样第 $i$ 个旅行者花费的时间应该为 $sumu\times a_i+sumd\times b_i$。比较大小即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,mp[2145][2145];
bool vis[2145][2145];
struct node{
	long long x,y,up,dn;
};
int dx[5]={1,0,0,-1};
int dy[5]={0,1,-1,0};
queue <node> q;
long long ans1,ans2;
void bfs(){
	node now,nxt;
	while(q.size()){
		now=q.front();
		q.pop();
		int xxx=now.x,yyy=now.y;
		if(xxx==n&&yyy==m){
			ans1=min(ans1,now.up),ans2=min(ans2,now.dn);
			continue;
		}
		if(vis[xxx][yyy]||mp[xxx][yyy]==-1) continue;
		if(xxx>=1&&yyy>=1&&xxx<=n&&yyy<=m){
			vis[xxx][yyy]=1;
			for(int i=0;i<4;i++){
				nxt.x=now.x+dx[i],nxt.y=now.y+dy[i];
				if(i<2) nxt.up=now.up+1;
				else nxt.up=now.up;
				if(i>=2) nxt.dn=now.dn+1;
				else nxt.dn=now.dn;
				q.push(nxt);
			}
		}
	}
}
int main(){
	long long xx,yy,k,a,b,ans3,cnt=1;
	ans1=ans2=ans3=1e18;
	cin>>n>>m>>k;
	char c;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='X') mp[i][j]=-1;
		}
	}
	node stt;
	stt.up=0,stt.x=1,stt.y=1,stt.dn=0;
	q.push(stt);
	bfs();
	for(int i=1;i<=k;i++){
		cin>>a>>b;
		long long k=a*ans1+b*ans2;
		if(k<ans3) ans3=k,cnt=1;
		else if(k==ans3) cnt++;
	}
	cout<<ans3<<" "<<cnt;
	return 0;
}
```
这是蒟蒻的第 $11$ 篇题解，感谢观看。

---

## 作者：liguangjun2023 (赞：2)

# 算法分析
1. 宽搜算法找到最短路径，得到向左上的次数和向右下的次数；
1. 结构体的成员变量：行 x、列 y、左上次数、右下次数；
1. vis 数组保存不重复走；
1. '.' 表示可以行走，'X ' 表示不能行走；
1. 每个人的上山路线相同，根据每个人的向右下时间为 ta，向左上时间为 tb，计算总时间；
1. 打擂台得到结果。 
# 【详细说明见代码注释】
```c
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
int n,m,k;
//vis[][] 保存走过的格子，dr[][] 方向数组
int vis[2010][2010],dr[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
ll user[N];
char a[2010][2010]; 
//遍历时保存，行 x，列 y，左上次数，右下次数 
struct node{
	int x,y,ul,dr;	
	node(int tx,int ty,int tul,int tdr){
		x=tx,	y=ty;
		ul=tul,	dr=tdr;
	}
};
//宽搜过程 
void bfs(ll &ul,ll &rd){	
	queue<node> q;
	q.push(node(1,1,0,0));
	vis[1][1]=1;
	while(!q.empty()){		
		node nd=q.front();
		q.pop();
		if(nd.x==n && nd.y==m){			
			ul=nd.ul,	rd=nd.dr;
			return;
		}		
		for(int i=0;i<4;i++){
			int tx=nd.x+dr[i][0],	ty=nd.y+dr[i][1],	tul=nd.ul,	tdr=nd.dr;			
			//避开越界、X、走过的格子 
			if(tx<1 || tx>n || ty<1 || ty>m || a[tx][ty]=='X' || vis[tx][ty])	
				continue;
			//向上左走， tul+1 ,向下右走，trd+1 
			if(i==2 || i==3)
				tul+=1;
			else
				tdr+=1;
			//继续宽搜 
			q.push(node(tx,ty,tul,tdr));
			vis[tx][ty]=1;
		}
	}	
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i]+1;
	}
	ll ul=0,dr=0;
	bfs(ul,dr);	
	ll mi=LLONG_MAX,cnt=0;
	for(int i=1;i<=k;i++){
		int ta,tb;
		cin>>ta>>tb;
		//每个人的登山，打擂台找到最小 
		user[i]=ul*tb+dr*ta;
		mi=min(mi,user[i]);
	}
	//找到同时间的数量	
	for(int i=1;i<=k;i++){
		if(mi==user[i]){
			cnt+=1;
		}
	}
	cout<<mi<<" "<<cnt;
	return 0;
}
```

---

## 作者：niuzexuan2011 (赞：1)

题目大意
------------
一堆旅行者爬山，他们的路径是相同的！！！（坑了我很久）
但旅行者身体素质不一样，有的慢有的快，我们要找到最快的人和最快的人的个数。

------------
大致思路
------------
很明显，一道广搜题，搜出公共路径即可，然后记录向上和向左走的次数，最后后再乘上旅行者用时，排完序，找到最快人的个数输出即可


------------
具体实现
-----------
1：输入地图，对障碍物进行标记。

2：定义一个避免查重的的数组，并标记起始点。
 
3：进入广搜，将旅行者们的路径记录下来。

4：记录路径中向上，左走的格子的个数，向右，下走的各自的个数。

5：将旅行者的用时计算后存进数组中，对数组排序。

6：找出第一名的用时和第一名的个数即可。

------------

AC代码附上，有注释
------------
```
#include<bits/stdc++.h>
using namespace std;
long long a[2005][2005],vis[2005][2005],e[100005],s1=0,s2=0,ans=1;//定义变量，切记long long 
long long dx[5]={0,0,1,0,-1};//爬格子专属 
long long dy[5]={0,1,0,-1,0};//爬格子专属 
char t;//输入的字符 
long long b,c;//每个旅行者爬山用时 
queue<int>qx,qy,qd1,qd2;//x,y是坐标，qd1是向上和向左爬的个数，qd2是向右和向下的步数 
int main(){
	long long n,m,k;//输入变量 
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>t;
			if(t=='X')  a[i][j]=1;//障碍物标记 
		}
	}
	vis[1][1]=1;//初始点标记 
	qx.push(1),qy.push(1),qd1.push(0),qd2.push(0);
	while(!qx.empty()){//广搜出路径 
		int x=qx.front(),y=qy.front(),d1=qd1.front(),d2=qd2.front();
		qx.pop(),qy.pop(),qd1.pop(),qd2.pop();
		if(x==n&&y==m){//抵达终点 
			s1=d1;//s1记录向上和左走步数 
			s2=d2;//s2记录向下和右走步数 
			break;
		}
		for(int j=1;j<=4;j++){//广搜 
			int xx=x+dx[j],yy=y+dy[j];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&vis[xx][yy]==0&&a[xx][yy]!=1){
				vis[xx][yy]=1;
				if(j<=2){//判断，j<=2是左走和上走 
					qx.push(xx),qy.push(yy),qd1.push(d1+1),qd2.push(d2);
				}
				else{//反之 
					qx.push(xx),qy.push(yy),qd1.push(d1),qd2.push(d2+1);
				}
			}
		}
	}
	for(int i=1;i<=k;i++){//记录每个旅行者用时 
	   cin>>b>>c;
	   e[i]=b*s1+c*s2;
	}
	sort(e+1,e+k+1);//排个序 
	for(int i=2;i<=k;i++){
		if(e[i]==e[i-1])  ans++;//记录用时和第一名一样的 人数 
		else break;
	}
	cout<<e[1]<<" "<<ans;//输出
	return 0; 
}
```

---

## 作者：I_Love_QingYu (赞：1)

# 分析
下山是很亏的，因为每一次下山都需要重新上山来补回来，那么总步数为 $n+m+down+down$。在每位旅行者下山速度不为负数的情况下，花费时间最少的路一定下山次数最少的路，而 $n$ 与 $m$ 都是固定的，所以总步数越少，下山次数越少，也就是说答案就是最短路径。最后计算出每个人花费的时间，输出即可。


# 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long int ans=1e17,f[1000006],shang=1e9,xia=1e9,n,m;
int mmp[2003][2003],p=0,to[4][2]={0,1,1,0,0,-1,-1,0},bfs[4000001][4];
int main()
{
    int k,x,y;
    cin>>n>>m>>k;
    char c;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>c;
            if(c=='.')
                mmp[i][j]=1;
        }
    int head=0,tail=1;
    bfs[0][0]=1;
    bfs[0][1]=1;
    mmp[1][1]=0;
    while(tail>head){
        x=bfs[head][0];
        y=bfs[head][1];
        if(x==n&&y==m)
            break;
        for(int i=0;i<4;i++){
            int x1=x+to[i][0];
            int y1=y+to[i][1];
            if(x1>0&&y1>0&&x1<=n&&y1<=m)
                if(mmp[x1][y1]){
                    mmp[x1][y1]=0;
                    bfs[tail][0]=x1;
                    bfs[tail][1]=y1;
                    bfs[tail][2]=bfs[head][2];
                    bfs[tail][3]=bfs[head][3];
                    if(i>1)
                        bfs[tail][3]++;
                    else
                        bfs[tail][2]++;
                    tail++;
                }
        }
        head++;
    }
    shang=bfs[head][2];
    xia=bfs[head][3];
    for(int i=1;i<=k;i++){
        cin>>n>>m;
        f[i]=n*shang+m*xia;
        ans=min(ans,f[i]);
    }
    int q=0;
    for(int i=1;i<=k;i++)
        if(f[i]==ans)
            q++;
    cout<<ans<<" "<<q;
    return 0;
}

```

---

## 作者：wuhan1234 (赞：1)

## 1.编程思路。

根据题意：在地图上与之相邻的右面或下面的区域海拔较高，而相邻的左边或上面区域海拔较低。旅店位于地图的第一行第一列，此处也是海拔最低。山顶在地图的的第 $n$ 行第 $m$ 列，此处也是海拔最高。我们将向右边或下面走称为“上山”，每走一步花费时间为 $a$；将向左边或上面走称为“下山”，每走一步花费时间为 $b$。

根据我们爬山的经验，费时最少的爬山路径应该是一直“上山”，在本题中如果一直“上山”的话，走 $n+m-2$ 步就可以从旅店走到山顶，这样其总花费时间为 $(n+m-2)\times a$。

如果在爬山过程中走了“下山”的路，则一定要重新走“上山”的路将“下山”的路补回来。设“下山”走了 $bcnt$ 步，则“上山”的路得多走 $bcnt$ 步，即“上山”得走 $n+m-2+bcnt$ 步。因此，爬山要花费时间最少，“下山”的步数 $bcnt$ 越少越好。

用 BFS 求得从旅店到山顶的最短路径长度 $len$。

则其中上山走的长度 $acnt$ 为 $(n+m-2)+(len-n-m+2)/2 $，

下山走的长度 $bcnt$ 为 $(len-n-m+2)/2$。

这样旅行者到达山顶的最短时间为 $acnt\times a+bcnt\times b$。

用一重循环一边读取每位旅行者的 $a$ 和 $b$ 值，一边记录 $acnt\times a+bcnt\times b$ 的最小值及最小值的个数即可。
## 2.源程序。

```c
#include <stdio.h>
struct Node
{
    int x,y,step;
};
int vis[2001][2001]={0};
char map[2005][2005];
struct Node q[4000005];
int BFS(int n,int m)
{
    struct Node cur,next;
    int front=0,rear=0;
    cur.x=1;  cur.y=1;
    cur.step=0;
    q[rear++]=cur;
    vis[1][1]=1;
    int dx[4]={0,0,-1,1};
    int dy[4]={-1,1,0,0};
    while (front<rear)
    {
        cur=q[front++];
        int i;
        for (i=0;i<4;i++)
        {
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];
            if (nx==n && ny==m) return cur.step+1;
            if (nx>=1 && nx<=n && ny>=1 && ny<=m && map[nx][ny]=='.' && !vis[nx][ny])
            {
                next=cur;
                next.x=nx;  next.y=ny;
                next.step++;
                q[rear++]=next;
                vis[nx][ny]=1;
            }
        }
    }
}
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int i;
    for (i=1;i<=n;i++)
        scanf("%s",&map[i][1]);
    int len=BFS(n,m);     // 用BFS求得最短路径的长度len
    len=len-(n+m-2);      // 求得最短路径中有上下反复的路径长度
    int acnt=(n+m-2)+len/2;   // 上山的步数
    int bcnt=len/2;           // 下山的步数
    long long  ans=0x3f3f3f3f3f3f3f3f;
    int cnt=0;                // 同时上山的人数
    while (k--)
    {
        long long a,b,t;
        scanf("%lld%lld",&a,&b);
        t=a*acnt+b*bcnt;
        if (t<ans)
        {
            ans=t;  cnt=1;
        }
        else if (t==ans)
            cnt++;
    }
    printf("%lld %d\n",ans,cnt);
    return 0;
}

```


---

## 作者：Starry_Ocean (赞：0)

# 题解：P9107 [PA2020] Wycieczka górska

马上 CSP 了，记录以下可能退役的自己吧。

进入正题。首先，**所有人走的路径一定都是一样的**。BFS 搜出来即可。

所以说，主函数就写好了。

```cpp
signed main(){
	init(); 	
	BFS();
	OUT();
	return 0;
}
```

初始化与输入部分也不解释了。

```cpp
int n,m,k;
char mp[8006][8006];
bool vis[8006][8006];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
struct node{
	int x,y,c;
};
int cnt=0;//用于统计最短路径 
void init(){
	cin>>n>>m>>k;
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j){
			cin>>mp[i][j];
		}
	}
}
```


接着，BFS 也没有什么变化，依旧是套模板。

```cpp
void BFS(){
	queue<node> q;
	memset(vis,false,sizeof(vis));
	q.push({1,1,0});
	vis[1][1]=true;
	while(q.size()){
		node dt=q.front();
		q.pop();
		if(dt.x==n&&dt.y==m){
			cnt=dt.c;
			return;
		} 
		for(int i = 0;i < 4;++i){
			int xx=dt.x+dx[i];
			int yy=dt.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&mp[xx][yy]!='X'&&!vis[xx][yy]){
				vis[xx][yy]=true;
				q.push({xx,yy,dt.c+1});
			}
		}
	}
	return;
}
```


当然，最重要的是输出部分了。

这里有一个很重要的算式。

记这个图的长为 $n$，宽为 $m$，最短移动次数为 $cnt$。那么，向更低地方移动的次数就是：
$$
\frac{cnt-(n+m-2)}{2}
$$

那么，输出函数也而完成了。

```cpp
void OUT(){
	int ans=1e18,ansb=(cnt-(n+m-2))/2,ansa=cnt-ansb;
	while(k--){
		int a,b,t;
		cin>>a>>b;
		t=a*ansa+b*ansb;
		if(t<ans){
			ans=t;
			cnt=1;
		} 
		else if(t==ans){
			cnt++;
		}
	}
	cout<<ans<<" "<<cnt;
}
```

不放 AC 代码了，祝大家都能通过第一轮。

---

## 作者：Harry_Potter_fan (赞：0)

# 阅读与理解：
这道题是诈骗题，因为每个人的线路是一样的（水题）。

我们只需要用 BFS 求出最短路需要径向上爬多少次，向下爬多少次，再乘上相应的时间即可（因为最短路径一定是最短时间）。

BFS 解析：用队列存储搜索到的点，周围的点循环入队，当到达终点时返回队头元素（不会的建议背下来）。

把每个人的用时存放到 $ti$ 数组里，快排一下，输出 $ti_1$、和 $ti_1$ 相等的元素个数即可。

# 附上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,up,down;
};
long long ti[1000010];
int n,m,k,dir[4][2]={1,0,0,1,0,-1,-1,0},cnt=0;
char a[3010][3010];
bool vis[3010][3010];
node bfs(int x,int y){
	queue<node> q;
	vis[1][1]=1;
	q.push(node{x,y,0,0});
	while(!q.empty()){
		node u=q.front();
		q.pop();
		if(u.x==n&&u.y==m){
			return u;
		}
		for(int i=0;i<4;i++){
			int bx=u.x+dir[i][0],by=u.y+dir[i][1];
			if(bx>n||bx<1||by>m||by<1)continue;
			if(vis[bx][by])continue;
			if(a[bx][by]=='X')continue;
			vis[bx][by]=1;
			if(i<2)q.push(node{bx,by,u.up+1,u.down});
			else q.push(node{bx,by,u.up,u.down+1});
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	node road=bfs(1,1);
	for(int i=1;i<=k;i++){
		long long x,y;
		cin>>x>>y;
		ti[++cnt]=x*road.up+y*road.down;
	}
	sort(ti+1,ti+cnt+1);
	cout<<ti[1]<<" ";
	int ans=1,i=2;
	while(ti[i]==ti[i-1]){
		ans++;
		i++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：donnieguo (赞：0)

## 思路

省流：诈骗题。每个人走的路径必然是一样的。

因为每一次向上走都一定需要一次向下走来抵消，记向上走的次数为 $x$，那么一共需要向下走 $n - 1 + x$ 次。

向左走同理。记向左走的次数为 $y$，那么一共需要向右走 $m - 1 + y$ 次。

一共需要走 $n + m - 2 + 2x + 2y$ 次。

那么我们只需要搜出使得 $x+y$ 最小的路径即可，其实就是最短路径。

## AC code

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e3 + 10, K = 1e6 + 10;
typedef long long ll;

int n, m, k;
char a[N][N];
ll ul, dr, t[K];
bool vis[N][N];
struct node {int x, y; ll tul, tdr;};
queue <node> q;

void bfs()
{
	q.push({1, 1, 0, 0});
	while (!q.empty())
	{
		int x = q.front().x, y = q.front().y;
		ll tul = q.front().tul, tdr = q.front().tdr;
		q.pop();
//		cout << "QwQ" << '\n';
		if (x < 1 || x > n || y < 1 || y > m) continue;
		if (vis[x][y] || a[x][y] == 'X') continue;
		if (x == n && y == m) {
			ul = tul;
			dr = tdr;
			return;
		}
		vis[x][y] = 1;
		q.push({x + 1, y, tul, tdr + 1});
		q.push({x - 1, y, tul + 1, tdr});
		q.push({x, y - 1, tul + 1, tdr});
		q.push({x, y + 1, tul, tdr + 1});
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	bfs();
	ll minn = 1e18;
	int ans = 0;
	for (int i = 1; i <= k; i++)
	{
		ll a, b; cin >> a >> b;
		t[i] = b * ul + a * dr;
		minn = min(t[i], minn);
	}
	for (int i = 1; i <= k; i++) 
		if (minn == t[i]) ans++;
	cout << minn << ' ' << ans << '\n';
	return 0;
}
```

---

## 作者：kaaaai (赞：0)

## 分析 ~~且只有分析~~
由题意，如果旅行者**只上山**的话，由小学学的关于**平移**的知识，他走的步数为 $n+m$。但是如果路上**有下山**的部分，他又需要同等步数的上山来**补回**。此时，他的总步数为 $n+m+down+up$。只要旅行者上山下山的时间不为负数，那么 $n+m+down+up>n+m$。因此，下山步数最少的路径就是时间花费最少的路径，既**最短路径**。所有旅行者的路径都是一样的。

直接用广搜搜出最短路径，并记录其下山和上山的步数即可。然后就可以求每位旅行者的时间，注意要**开 long long**。

---

## 作者：makerli (赞：0)

[link](https://www.luogu.com.cn/problem/P9107)

一道非常有趣的广搜题，把蒟蒻卡了两周半。

## #1 (30pts)

不难想到，对于每个旅行者都运行一次广搜，然后比较出最快的路线,这样可以光荣地骗到30分。

code:
```cpp
#include<bits/stdc++.h>
#define int long long	//不开long long见祖宗 
using namespace std;
char mp[202][2002];
bool flag[2002][2002];
//方位数组 
int fx[5]= {0,1,-1,0,0};	 
int fy[5]= {0,0,0,1,-1};
int n,m,k;
struct zt {
	int x,y,step;
};
queue<zt>q;
int bfs(int a,int b) {	//广搜 
	int ans=11451419198101145;
	q.push({1,1,0});
	while(!q.empty()) {
		zt now=q.front();
		q.pop();
		if(now.x==n&&now.y==m) {	//边界 
			ans=min(ans,now.step);
			continue;
		}
		for(int i=1; i<=4; i++) {
			int tx=now.x+fx[i],ty=now.y+fy[i];
			if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&!flag[tx][ty]&&mp[tx][ty]=='.')
				if(i&1==1) {
					flag[tx][ty]=1;
					q.push({tx,ty,now.step+a});
				} else {
					flag[tx][ty]=1;
					q.push({tx,ty,now.step+b});
				}
		}
	}
	memset(flag,0,sizeof(flag));	//多测要清空 
	return ans;
}
signed main() {
	//输入输出优化 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int ta,tb,cnt=1,ans=11451419198101145;
	cin>>n>>m>>k;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>mp[i][j];
	for(int i=1; i<=k; i++) {
		cin>>ta>>tb;
		int t=bfs(ta,tb);
		if(ans==t)
			cnt++;
		if(t<ans)
			ans=t,cnt=1;
	}
	cout<<ans<<' '<<cnt;
	return 0;
}
```

## #2 (100pts)

不难发现，其实每个人走的最短路线都是一样的，所以只需通过一次广搜即可搜出所有旅行者的上山最短路径，然后比较每个人的用时即可求出答案。

在计算最短路径时，要注意：由于每下山一次都要上一次山补回来，所以当总路程相同时，下山次数少的方案更优。

“每个人走的最短路线都是一样的”证明：设上山的次数为 $x$，下山的次数为 $y$，那么一个人的用时即为 $x \cdot a +y \cdot b$。因为 $a,b$ 都大于0，所以 $x,y$ 越小，用时就越少。

code:
```cpp
#include<bits/stdc++.h>
#define int long long	//不开long long见祖宗
using namespace std;
char mp[2002][2002];
bool flag[2002][2002]
int fx[5]= {0,1,-1,0,0};
int fy[5]= {0,0,0,1,-1};
int n,m,k;
struct zt {
	int x,y,up,down;
	bool operator <(const zt &a) const {	//重载运算符，比较最短步数。当步数相同时，下山次数少的总时长更少 
		if(a.up+a.down!=up+down)
			return up+down<a.up+a.down;
		else
			return up<a.up;
	}
};
queue<zt>q;
signed main() {
	//输入输出优化 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int a,b,cnt=0,sum=114514191981011145,t;
	zt ans= {0,0,11451419198101145,11451419198101145};
	cin>>n>>m>>k;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>mp[i][j];
	q.push({1,1,0,0});
	flag[1][1]=1;
	while(!q.empty()) {	//广搜 
		zt now=q.front();
		q.pop();
		if(now.x==n&&now.y==m) {
			ans=min(ans,now);
			continue;
		}
		for(int i=1; i<=4; i++) {
			int tx=now.x+fx[i],ty=now.y+fy[i];
			if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&!flag[tx][ty]&&mp[tx][ty]=='.')
				if(i%2==1) {
					flag[tx][ty]=1;
					q.push({tx,ty,now.up+1,now.down});
				} else {
					flag[tx][ty]=1;
					q.push({tx,ty,now.up,now.down+1});
				}
		}
	}
	for(int i=1; i<=k; i++) {
		cin>>a>>b;
		t=ans.up*a+ans.down*b;	//计算用时 
		if(t<sum)
			sum=t,cnt=0;
		if(t==sum)
			cnt++;
	}
	cout<<sum<<' '<<cnt;	
	return 0;
}
```

---

## 作者：__Octhyccc__ (赞：0)

BFS 板子题，但是需要开 long long。

因为最多有 $10^6$ 个人，一个人最多每步的时间高达 $10^9$，再有好几步，$10^6\times 10^9=10^{15}$，远超 int。

一般遵循以下几个原则：

- 不重复走。
- 按照每层来扩展节点。
- 在本题中有 $4$ 个方向，分别为 $(x+1,y),(x-1,y),(x,y+1),(x,y-1)$。

每次记录是上坡还是下坡，如果抵达了目的地（$x=n,y=m$），就返回上坡的次数和下坡的次数。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct point{int x,y,ustep,dstep;};
struct person{int a,b,time;}pe[1000001];
int n,m,k,ans;
bool vis[8001][8001];
char ma[8001][8001];
int frx[4]={0,0,-1,1};
int fry[4]={1,-1,0,0};
queue<point>q;
point bfs(){
	q.push((point){1,1,0,0});
	vis[1][1]=1;
	while(!q.empty()){
		point p=q.front();q.pop();
		int x2=p.x,y2=p.y;
		for(int i=0;i<4;i++){
			int x3=x2+frx[i],y3=y2+fry[i];//移动坐标
			if(x3<=n && y3<=m && x3>0 && y3>0 && !vis[x3][y3])/*判断是否在地图里*/{
				if(ma[x3][y3]=='X')continue;//不能移动，下一种情况
				if(i==0 || i==3){
					q.push((point){x3,y3,p.ustep+1,p.dstep});//向上走
					vis[x3][y3]=1;
				}
				else{
					q.push((point){x3,y3,p.ustep,p.dstep+1});//向下走
					vis[x3][y3]=1;//标记走过
				}
			}
		}
		if(p.x==n && p.y==m)return p;
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ma[i][j];
		}
	}
	point u=bfs();
	int mintime=1e18;//别写成 INT_MAX
	for(int i=0;i<k;i++){
		scanf("%lld%lld",&pe[i].a,&pe[i].b);
		pe[i].time=pe[i].a*u.ustep+pe[i].b*u.dstep;//计算时间
		mintime>pe[i].time?mintime=pe[i].time:mintime;
	}
	for(int i=0;i<k;i++){
		if(pe[i].time==mintime)ans++;
	}
	printf("%lld %lld",mintime,ans);
	return 0;
}
```

---

