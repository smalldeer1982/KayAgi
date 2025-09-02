# Fishes

## 题目描述

While Grisha was celebrating New Year with Ded Moroz, Misha gifted Sasha a small rectangular pond of size $ n×m $ , divided into cells of size $ 1×1 $ , inhabited by tiny evil fishes (no more than one fish per cell, otherwise they'll strife!).

The gift bundle also includes a square scoop of size $ r×r $ , designed for fishing. If the lower-left corner of the scoop-net is located at cell $ (x,y) $ , all fishes inside the square $ (x,y)...(x+r-1,y+r-1) $ get caught. Note that the scoop-net should lie completely inside the pond when used.

Unfortunately, Sasha is not that skilled in fishing and hence throws the scoop randomly. In order to not frustrate Sasha, Misha decided to release $ k $ fishes into the empty pond in such a way that the expected value of the number of caught fishes is as high as possible. Help Misha! In other words, put $ k $ fishes in the pond into distinct cells in such a way that when the scoop-net is placed into a random position among $ (n-r+1)·(m-r+1) $ possible positions, the average number of caught fishes is as high as possible.

## 说明/提示

In the first example you can put the fishes in cells $ (2,1) $ , $ (2,2) $ , $ (2,3) $ . In this case, for any of four possible positions of the scoop-net (highlighted with light green), the number of fishes inside is equal to two, and so is the expected value.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912D/40c8b1b61edb367e0e414618a2e0b777e6a3b2ba.png)

## 样例 #1

### 输入

```
3 3 2 3
```

### 输出

```
2.0000000000
```

## 样例 #2

### 输入

```
12 17 9 40
```

### 输出

```
32.8333333333
```

# 题解

## 作者：4396瞎 (赞：6)



考点为【大根堆】+【map判重】+【多条性质】。首先看完题后，我们可能想的是放完鱼后再撒网，看每个网里有多少条鱼。但实际上我们可以换一个思路，考虑【每条鱼对期望的贡献】，即(x,y)位置的鱼能被多少个网网住。

那么，哪个位置的鱼是最好的呢？很容易想到【中间的点】比边缘上的点好，那么我们可以第一条鱼放在中间位置，第二条鱼在中间的上下左右四个方向找一条==>用bfs从中间往四周寻找放鱼位置，并将位置推到大根堆里。（为了避免一个位置被多次考虑到，我们用map判重。不能用visit数组，因为空间不够）

最后还有一个难点，如何求(x,y)点上的鱼能被多少网网住？ 
(min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(y,r)+1) 
min(n,x+r-1)是网最往右的右边界 
max(x,r)是网最往左的右边界 
这两个相减是网可移动的次数，相减为0则不可移动==>只有一种可能

AC代码：
```
#include<iostream>  
#include<iomanip>  
#include<queue>  
#include<map> 
using namespace std;
long long n,m,r,k; //n列，m行 
long long caught;

struct node{
    long long ca;
    int x,y;
    node(long long c1,int x1,int y1):
        ca(c1),x(x1),y(y1) {}
};

bool operator < (node n1,node n2){
    return n1.ca<n2.ca;
}

long long ci(long long x,long long y){//在(x,y)点放下一条鱼会被捞起来的次数 
    return (min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(y,r)+1);
}

map<pair<int,int>,bool> visit; 
priority_queue<node> q;//大根堆 

int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};

int main(){ 

    cin>>n>>m>>r>>k;

    int gold_x=(n+1)/2,gold_y=(m+1)/2;
    q.push( node(ci(gold_x,gold_y),gold_x,gold_y) );    //先把最中间的位置加进去
    visit[make_pair(gold_x,gold_y)]=true;

    for(int i=1;i<=k;i++){//k次bfs 
        node now=q.top(); q.pop();
        caught+=now.ca;

        for(int j=0;j<4;j++){//从黄金区域往外扩散
            int x1=now.x+dx[j];
            int y1=now.y+dy[j];
            if( x1<1 || y1<1 || x1>n || y1>m || visit[make_pair(x1,y1)] ) continue;
            q.push( node(ci(x1,y1),x1,y1) );
            visit[make_pair(x1,y1)]=true;
        }
    }

    cout<<fixed<<setprecision(10);
    double sumNet=(n-r+1)*(m-r+1); 
    cout<<caught/sumNet;

    return 0;
}

```


---

## 作者：lutaoquan2012 (赞：4)

## 题目大意
在 $n\times m$ 的鱼缸里面，放入 $k$ 条鱼，再用一张 $r\times r$ 的渔网再鱼缸里面捞鱼，看看平均每次能捞出多少条鱼，其实就是求一个 [期望值](https://baike.baidu.com/item/%E6%9C%9F%E6%9C%9B%E5%80%BC/8664642?fr=ge_ala)。
## 思路
1. 这道题我个人认为主体就是贪心，这个鱼放在什么位置最好呢？当然是最中间的位置，也就是 $\frac{(n+1)}{2},\frac{(m+1)}{2}$ 这个位置。
2. 如果这个位置已经放了鱼呢，那么不妨我们可以看看他四周可不可以放下鱼。很显然可以用一个宽搜求出。
3. 如果这个位置像四周扩散总得有一个顺序吧，那必须是这个点被打捞出来的次数越多那么就越在前，这样我们就可以用优先队列来算，定义一个结构体，里面存储这个点还有它的被打捞的次数。
4. 我们又该如何算出这个点他被打捞出来的次数呢。首先我们应该会有一个暴力的做法，去枚举每一个网的左上角，看他能不能捞出来这条鱼。很显然是不行的，因为复杂度太高了。那么我们不妨用一个数学的公式来算这个点被打捞出来的次数 $(\min(n,x+r-1)-\max(x,r)+1)\times(\min(m,y+r-1)-\max(r,y)+1)$ 我们为什么要用 $\min$ 或者 $\max$ 呢？主要是防止这个网的位置越界。
5. 大家想必都做过宽搜或者深搜吧，那是不是要用一个数组去记录他这个点是不是被访问过，这道题数据太大了，数组装不下，所以我们可以用一个 `set` 去记录。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//个人习惯
ll n,m,r,k,xc,yc,ans;
struct node{
	ll x,y,gx;//位置和被打捞出来的次数
	bool operator<(node b) const{//判断优先级
	    return gx<b.gx;
	}
}; 
set<pair<ll,ll>> s;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
priority_queue<node> q;
ll f(ll x,ll y){//数学公式，用于计算当前点被打捞出来的次数
	return (min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(r,y)+1);
}
int main(){
	cin>>n>>m>>r>>k;
	xc=(n+1)/2;//中心点
	yc=(m+1)/2;
	q.push({xc,yc,f(xc,yc)});
	s.insert({xc,yc});
	while(k--){//注意：这里不是判空，而是看他有每有放完k条鱼
		ll x=q.top().x,y=q.top().y;
		ans+=q.top().gx;//计入答案
		q.pop();//删除
		for(int i=0;i<4;i++){
			ll nx=x+dx[i],ny=y+dy[i];//下一个点的坐标
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&s.count({nx,ny})==0){//判断它能不能进入队中
				s.insert({nx,ny});//标记
				q.push({nx,ny,f(nx,ny)});//进队
			}
		}
	}
	double hh=(n-r+1)*(m-r+1);//输出答案
	printf("%.10f",ans/hh);
	return 0;
}
```

---

## 作者：万弘 (赞：3)

套路题.
$$E=\frac{\text{每个鱼被覆盖次数之和}}{\text{矩形数量}}$$

最大化**每个鱼被覆盖次数之和**即可.  
先考虑计算一条鱼的被覆盖次数.宽度是`min(y+r-1,m)-max(y,r)+1`,长度是`min(x+r-1,n)-max(x,r)+1`,相乘即可.  
显然整个矩形中间位置的被覆盖的次数是最大的;其周围一圈其次.于是bfs即可.用`std::map`或`std::set`判重即可.

时间复杂度$\mathcal O(k\log k)$
```cpp
/**********/
std::set<pll>s;
struct one
{
    ll x,y,f;
    bool operator <(const one& t)
    const
    {
        return f<t.f;
    }
};
std::priority_queue<one>q;
ll mx[]={0,1,0,-1},my[]={1,0,-1,0};
int main()
{
    ll n=read(),m=read(),r=read(),k=read(),sum=0;
    ll x=(n+1)/2,y=(m+1)/2;
    ll f=(min(y+r-1,m)-max(y,r)+1)*(min(x+r-1,n)-max(x,r)+1);
    s.insert(pll(x,y));q.push(one{x,y,f});
    while(k--)
    {
        ll x=q.top().x,y=q.top().y;
        sum+=q.top().f;
        //printf("%lld %lld %lld\n",x,y,q.top().f);
        q.pop();
        for(ll i=0;i<4;++i)
        {
            ll vx=x+mx[i],vy=y+my[i];
            if(vx>0&&vx<=n&&vy>0&&vy<=m&&!s.count(pll(vx,vy)))
            {
                s.insert(pll(vx,vy));
                q.push(one{vx,vy,(min(vy+r-1,m)-max(vy,r)+1)*(min(vx+r-1,n)-max(vx,r)+1)});
            }
        }
    }
    printf("%.10f",(double(sum))/((n-r+1)*(m-r+1)));
    return 0;
}
```

---

## 作者：Peiyuan (赞：3)

[题目通道](https://www.luogu.com.cn/problem/CF912D)

## 题目大意

有一个 $n\times m$ 的鱼缸和一个 $r\times r$ 的渔网，现在放入 $k$ 条鱼，使每次捞到鱼的条数的平均值最大，输出这个平均数。

## 思路

我们可以从中心点出发进行广度优先搜索。用一个优先队列作为 BFS 搜索用的队列，这样会每次优先选择捞起次数多的点进行遍历（贪心？）。注意在符号重载时，优先队列里大于号代表大根堆，从小到大排序，小于号代表小根堆，从大到小排序。同时，我们可以通过 $(\min_{n,x+r-1}-\max_{x,r}+1)\times(\min_{m,y+r-1}-\max_{y,r}+1)$ 来计算一个点 $(x,y)$ 的鱼被捞起来的次数。其中，计算最小值和最大值防止计算超出矩形范围。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
ll n,m,r,k,sum;
struct node{
    ll cnt,x,y;
	friend bool operator<(node a,node b){ //重载小于号
	    return a.cnt<b.cnt; //捞起次数多的在前 
	}
};
ll cal(ll x,ll y){ //(x,y)点的鱼会被捞起来的次数 
    return (min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(y,r)+1);
}
priority_queue<node> q;
map<pair<ll,ll>,bool> vis; //用一个标记数组来记录(x,y)是否被访问过进行bfs 
int dx[]={1,-1,0,0},dy[]={0,0,-1,1};
int main(){ 
    cin>>n>>m>>r>>k;
    int x=(n+1)/2,y=(m+1)/2; //获取中心点的x和y 
    q.push({cal(x,y),x,y}); //将中心点（起点）推入队列 
    vis[make_pair(x,y)]=1; //将起点标记 
    while(k--){
        node cur=q.top(); q.pop(); //取出队首 
        sum+=cur.cnt; //记录答案 
        for(int i=0; i<4; i++){ //遍历当前点能到达的四个点 
            int nx=cur.x+dx[i],ny=cur.y+dy[i];
            if(nx>0&&ny>0&&nx<=n&&ny<=m&&!vis[make_pair(nx,ny)]){ //没有越界且没有被标记过 
            	q.push({cal(nx,ny),nx,ny}); //将下一个点推入队列 
            	vis[make_pair(nx,ny)]=1; //将下一个点标记 
            }
        }
    }
    double cnt=(n-r+1)*(m-r+1); //n*m矩形内r*r正方形的个数 
    printf("%.10lf",sum/cnt); //平均值：总和/个数
    return 0;
}
```

---

## 作者：lml0928 (赞：2)


# Part 0.题意

题目大意：现在给一个 $n \times m$ 个 $1 \times 1$ 的格子组成的长方形，你可以让 $k$ 个格子为 $1$，其他为 $0$。求出在长方形内的所有 $r \times r$ 大小的正方形内的和的期望值。
完整题目移步 [传送门](https://www.luogu.com.cn/problem/CF912D)。
期望值的概念移步 [百度百科](https://baike.baidu.com/item/%E6%9C%9F%E6%9C%9B%E5%80%BC/8664642?fr=ge_ala)。
# Part 1. 思路
我们如果暴力枚举所有 $k$ 个填 $1$ 的格子，显然会超时。
所以我们可以使用**贪心**的思想来考虑。假设我们已经知道每个格子对最终期望的贡献（也就是这个格子所在的 $r \times r$ 的**正方形的个数**），就可以把所有格子扔到**优先队列里**，进而求出答案。但是由于 $n$ 和 $m$ 都达到了 $10^5$，$O(nm\log(nm))$ 的复杂度依旧无法接受。但我们顺着这个思路可以做的更好。

通过手动模拟可以发现，每一个格子的贡献一定比**比这个格子更靠外的格子**更多。从这里很容易联想到 [P1631. 序列合并](https://www.luogu.com.cn/problem/P1631) 这道题。
根据我们刚才的推论，最中间的格子一定是最优的。然后，我们可以写一个类似于 BFS 的程序，把队列换为大根堆（比较格子的贡献），每次得到当前最优的点，就把这个点的邻接点放到优先队列里。由于 $n \times m$ 过大，无法开 vis 数组，所以我们用 set 代替。

最后，怎么计算每个点的贡献呢？
考虑当前格子为 $(x, y)$。首先考虑正方形的右边界。右边界最左可以到 $\max(x, r)$，最右可以到 $\min(x + r - 1, n - r + 1)$。下边界的最上和最下同理。
# Part 2. 代码
时间复杂度 $O(k\log(k))$，可以轻松通过。

为了防止抄袭，空出代码中的 Calc 函数（该函数表示 $(x, y)$ 的贡献）。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x, y;
	long long c;
	bool operator < (const node& cmp) const
	{
		return c < cmp.c; //STL 的优先队列以小为大
	}
};
priority_queue<node> q; //代替 BFS 中的队列
set<pair<int, int> > s; //代替 BFS 中的 vis 数组
int n, m, r, k;
long long Calc(int x, int y); //这里由读者自行思考
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};
int main()
{
	scanf("%d%d%d%d", &n, &m, &r, &k);
	int midx = (1 + n) / 2, midy = (1 + m) / 2;
	//启动变了样的广搜
	q.push({midx, midy, Calc(midx, midy)});
	s.insert({midx, midy});
	long long res = 0;
	while(k--)
	{
		node f = q.top();
		q.pop();
		res += f.c;
		for(int i = 0; i < 4; i++)
		{
			int tx = f.x + DX[i];
			int ty = f.y + DY[i];
			if(tx < 1 || tx > n) continue;
			if(ty < 1 || ty > m) continue;
			if(s.count(make_pair(tx, ty))) continue;
			s.insert(make_pair(tx, ty));
			q.push({tx, ty, Calc(tx, ty)});
		}
	}
	long long tmp = (n - r + 1) * 1ll * (m - r + 1);
	printf("%.9lf", res * 1.0 / tmp); //题目要求 -1e9
	return 0;
}
```


~~蒟蒻第一篇题解，求过~~

---

## 作者：dead_X (赞：2)

## 思路
显然我们可以把期望转化成**总答案除以方法数**的形式。

然后我们发现对于每个位置，对总答案的贡献是固定的，即 $x,y$ 轴能取到的个数乘起来。

于是我们只要选贡献最高的 $k$ 个位置就好了。

然后你发现贡献是从中间向四周减小的，所以优先队列搜索即可。

坑点：别忘了判一个点是否被搜过，输出保留尽可能多的小数。
## 代码
```cpp
#include<bits/stdc++.h>
#define qaq(x,y) vis[make_pair(x,y)]=1,q.push(make_pair(x,y))
#define qwq(x,y) vis[make_pair(y,x)]=1,q.push(make_pair(y,x))
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
map<pair<int,int>,bool> vis;
int n=read(),m=read(),r=read(),k=read();
int val(pair<int,int> x)
{
	int i=x.first,j=x.second;
 		int u=min(n-r+1,i)-max(1ll,i-r+1)+1;
 		int v=min(m-r+1,j)-max(1ll,j-r+1)+1;
 		return u*v;
}
bool valid(int x,int y)
{
	if(vis[make_pair(x,y)]) return 0;
	if(1<=x&&x<=n&&1<=y&&y<=m) return 1;
	return 0;
}
struct cmp
{
	bool operator()(pair<int,int> x,pair<int,int> y)
	{
		return val(x)<val(y);
	}
};
signed main()
{
 	priority_queue<pair<int,int>,vector<pair<int,int> >,cmp> q;
 	int ans=0;
 	if(n&1ll) if(m&1ll) qaq((n+1)>>1,(m+1)>>1);
 	else qaq((n+1)>>1,m>>1),qaq((n+1)>>1,(m>>1)+1);
 	else if(m&1ll) qwq((m+1)>>1,n>>1),qwq((m+1)>>1,(n>>1)+1);
 	else qaq(n>>1,m>>1),qaq(n>>1,(m>>1)+1),qwq(m>>1,(n>>1)+1),qwq((m>>1)+1,(n>>1)+1);
 	for(int i=1; i<=k; i++)
 	{
 		pair<int,int> p=q.top();q.pop();
 		ans+=val(p);
 		int x=p.first,y=p.second;
 		++x;if(valid(x,y)) qaq(x,y);--x;
 		--x;if(valid(x,y)) qaq(x,y);++x;
 		++y;if(valid(x,y)) qaq(x,y);--y;
 		--y;if(valid(x,y)) qaq(x,y);++y;
 	}
 	int tot=(n-r+1)*(m-r+1);
 	printf("%.10lf\n",1.0*ans/tot);
	return 0;
}
```

---

## 作者：GWBailang (赞：1)

#### [原题传送](https://www.luogu.com.cn/problem/CF912D)

题意：一个 $n\times m$ 大小的网格，往里面放 $k$ 条鱼（$1\times 1$ 大小），问：随机的在网格上沿格线放一个边长为 $r$ 的正方形鱼网，平均可以获得多少鱼。

考虑每一条鱼对期望值的贡献，很好想到，越接近网格的中间位置的鱼对期望值的捐献越大。我们只需从网格中间的位置开始遍历，利用优先队列来找到“下一步”能走到的格子中，对期望值贡献最大的一个格子即可。

#### 计算 $(x,y)$ 对期望值的贡献：

可以发现有以下区域的鱼网可以包含 $(x,y)$（红色区域为所有可以包含 $(x,y)$ 的鱼网可以覆盖的区域，绿色区域为所以可以包含 $(x,y)$ 的鱼网的左上角的格子）：

![](https://pic.imgdb.cn/item/6524ba1bc458853aef8b4627.jpg)

我们只需要计算绿色区域的面积即可知道 $(x,y)$ 对期望值的捐献。还需要注意一下，鱼网不能撒到网格外。

最终我们得出 $(x,y)$ 对期望值的捐献为：

$(\min(n-r+1,x)-max(1,x-r+1)+1)\times(\min(m-r+1,y)-\max(1,y-r+1)+1)$

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	long long x,y,zhi;
	bool operator < (Node a) const{
		return zhi<a.zhi;//用对期望值的捐献的大小来决定下一步走哪
	}
};
priority_queue<Node>q;
long long n,m,r,k,sum,cnt;
//sum用来记录所有鱼对期望值捐献的总和
//cnt用来记录已经放了几条鱼
long long gx(long long x,long long y){//(x,y)对整个的贡献
	return (min(n-r+1,x)-max(1ll,x-r+1)+1)*(min(m-r+1,y)-max(1ll,y-r+1)+1);
}
map<pair<long long,long long>,bool>ma;
//用map来判断这个点是否已经放上鱼了。直接用数组空间会炸。
long long dx[]={0,0,-1,1};
long long dy[]={-1,1,0,0};
int main(){
	cin>>n>>m>>r>>k;
	Node l={(n+1)/2,(m+1)/2,gx((n+1)/2,(m+1)/2)};
	ma[make_pair((n+1)/2,(m+1)/2)]=true;
	q.push(l);
	while(q.size()&&cnt<k){//BFS，我们只能放k条鱼
		l=q.top();q.pop();
		sum+=l.zhi;
		cnt++;
		for(long long i=0;i<4;i++){
			long long xx=l.x+dx[i],yy=l.y+dy[i];
			if(xx>0&&xx<=n&&yy>0&&yy<=m
			 &&ma[make_pair(xx,yy)]==false){
				ma[make_pair(xx,yy)]=true;
				q.push({xx,yy,gx(xx,yy)});
			}
		}
	}
	printf("%.9f\n",(double)sum/(double)((n-r+1)*(m-r+1)));
	//一定要输出到小数点后9位，否则误差会很大
	return 0;
}
```

---

## 作者：蒟蒻丁 (赞：1)

~~这是一个很邪门的贪心~~  
[更好体验](https://www.cnblogs.com/caijiLYC/p/16855976.html)  
考虑到最终答案是每个正方形的贡献除以总的正方形个数，而正方形个数容易计算，那么只需最大化贡献。  
~~从题面给出的图易得~~ 每个点被覆盖的次数是一定的，我们只需要在被覆盖最多的点上面放置小鱼即可让答案最大化  
接着容易想到一个暴力的做法，就是 $n^2$ 统计每个点的贡献，取前 $k$ 个点放置小鱼。  
再考虑优化，每个点被覆盖情况实际上可以看成长和宽的被覆盖情况的乘积，我们把正方形看成是两条线段，分别覆盖在长和宽上，这样的两条线段对应原矩形中唯一一个正方形。设长和宽被覆盖次数为两个序列 $a_i$、$b_j$ ，原矩形为 $c_{i,j}$，那么 $c_{i,j}=a_i \times b_j$, 我们的任务就是计算出前 $k$ 大的 $c_{i,j}$，考虑把 $a_i$ $b_j$ 排序，从大到小分别枚举 $i$ ，$j$ 把对应的乘积放入平衡树或者 set。因为我们是从大到小枚举，如果一个乘积 $a_i \times b_j$ 在平衡树中的排位大于 $k$ ，继续下去的话乘积只会更小，那么他自己和他后面的元素也就都没有价值了，我们直接 break 掉，这个做法时间复杂度目测不会超过 $O( n \sqrt{n} \log{n}$)，实际测试跑的快得多。 
```c++11
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
typedef long long ll;
using namespace std;
ll n,m,k,r,a[400001],b[400001],ans;

struct Splay{
	#define N (ll)3e6
	ll siz[N],fa[N],son[N][2],vul[N],tot,root,cnt[N];
	void UP(ll x){
		siz[x]=siz[son[x][0]]+siz[son[x][1]]+cnt[x];
	}
	bool dir(ll x){
		return son[fa[x]][1]==x;
	}
	void rotate(ll x){
		ll y=fa[x],z=fa[y],k=dir(x),w=son[x][k^1];
		fa[x]=z,son[z][dir(y)]=x;
		fa[y]=x,son[x][k^1]=y;
		fa[w]=y,son[y][k]=w;
		UP(y),UP(x); 
	}
	void splay(ll x,ll goal=0){
		while(fa[x]!=goal){
			ll y=fa[x],z=fa[y];
			if(z!=goal){
				if(dir(x)==dir(y))rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		if(!goal)root=x;
	}
	void find(ll x){
		if(!root)return ;
		ll cur=root;
		while(son[cur][x>vul[cur]]&&x!=vul[cur])
			cur=son[cur][x>vul[cur]];
		splay(cur);
	}
	ll LR(ll x,ll k){
		find(x);
		if(vul[root]<x&&k==0)return root;
		if(vul[root]>x&&k==1)return root;
		ll cur=son[root][k];
		while(son[cur][k^1])cur=son[cur][k^1];
		return cur;
	}
	ll insert(ll x){
		ll cur=root,p=0;
		while(cur&&x!=vul[cur]){
			p=cur;
			cur=son[cur][x>vul[cur]];
		}
		if(cur)cnt[cur]++;
		else {
			cur=++tot;
			if(p)son[p][x>vul[p]]=cur;
			siz[cur]=cnt[cur]=1;
			fa[cur]=p,vul[cur]=x;
			son[cur][0]=son[cur][1]=0;
		}
		splay(cur);
	}
	void Delete(ll x){
		ll le=LR(x,0),re=LR(x,1);
		splay(le),splay(re,le);
		ll del=son[re][0];
		if(cnt[del]>1)cnt[del]--,splay(del);
		else son[re][0]=0;
		UP(re),UP(le);
	}
	ll get_rank(ll x){
		find(x);
		if(vul[root]>=x)return siz[son[root][1]]+cnt[root];
		return siz[son[root][1]];
	}
}T;

int main(){
	T.insert(-1e15);
	T.insert(1e15);
	cin>>n>>m>>r>>k;
	for(ll i=1;i<=n-r+1;i++)a[i]++,a[i+r]--;
	for(ll i=1;i<=m-r+1;i++)b[i]++,b[i+r]--;
	for(ll i=1;i<=n;i++)a[i]+=a[i-1];
	for(ll i=1;i<=m;i++)b[i]+=b[i-1];
	sort(1+a,1+a+n);
	sort(1+b,1+b+m);
	for(ll i=n;i>=1;i--){
		for(ll j=m;j>=1;j--){
			ll sum=a[i]*b[j];
			if(T.get_rank(sum)>k+1)break;
			T.insert(sum);
		}
	}
	while(k--){
		ll cur=T.LR(1e12,0);
		ans+=T.vul[cur];
		T.Delete(T.vul[cur]);
	}
	long double Ans=1.0*ans/(n-r+1)/(m-r+1);
	printf("%.10Lf",Ans);
}
```

---

## 作者：N1K_J (赞：0)

显而易见的考虑把鱼放在每个位置能被多少种 $r \cdot r$ 取到，把 $k$ 个鱼放在有最大被取到次数的位置。

显而易见的，中心是被取得最多的。

然后注意到这个东西不妨设被取到的次数为 $X_{i,j}$。

可以对比较小的 $n,m,r$ 手搓这个数组。

就能注意到第 $N$ 大的 $X_{i,j}$ 一定和前 $N-1$ 大的当中的一个联通，所以可以类似 bfs 的方式放置鱼。

只需要求出 $X_{i,j}$。

注意到 $(i,j)$ 被 $r \cdot r$ 包含要求这个 $r \cdot r$ 在 $n \cdot m$ 内。

所以说可以类似于枚举 $(i,j)$ 在 $r \cdot r$ 的哪一个位置的方式求出：

$$X_{i,j} = (\min(n,x+r-1)-\max(x,r)+1)\times(\min(m,y+r-1)-\max(r,y)+1)$$

当然，靠肉眼观测也可以。（）

[Code](https://codeforces.com/contest/912/submission/249684564)

---

## 作者：Xeqwq (赞：0)

upd 2022.1.7 ：修复 $\LaTeX$  
感谢管理员&各位观众

---
## 题目大意  
求每次用 $r \times r$ 的网在 $n \times m$ 的鱼缸里面捞鱼  
鱼的位置自己定 一共 $k$ 条 
最多能捞到多少？  

求期望 就是在求：  

- $val$ = 所有捞鱼方案中 这个点被捞的次数  
- $ans$ = 最大的 $k$ 个点的 $val$ 的和  

- $tot$ = 所有捞鱼方案种类数  

$$\text{所求 = } \frac{ans}{tot}$$  

## 解题方案  
先写一个函数来求每个点的 $val$  
```cpp
ll gt(ll x,ll y)
{
	return (min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(y,r)+1);
}
```
如此 我们可以开一个结构体 $point$  
里面存储点的坐标和这个点的 $val$  
```cpp
struct point
{
	ll x;
	ll y;
	ll val;
	point(ll x,ll y,ll val): 
	x(x),y(y),val(val){}
};
```

但是如果我们暴力算法那时间空间都会超限  


## 考虑优化？
我们可以发现在**中间部分点的 $val$ 大，外部的点 $val$ 小**，所以我们可以从中间开始，搜附近哪里 $val$ 最大，再往外面一圈扩出去  
开个大根堆 往里面放点每个点坐标和 $val$ ，然后用 bfs 向外部广搜  
```priority_queue<point>```   
既然要用优先队列  我们就要写出**比较 $point$ 大小的函数**  
```cpp
struct point
{
	ll x;
	ll y;
	ll val;
	point(ll x,ll y,ll val): 
	x(x),y(y),val(val){}
	friend bool operator<(const point p1,const point p2)
	{
		if(p1.val!=p2.val) return p1.val<p2.val;
	}
};
```  
然后我们要写广搜就要**存搜过的点**  
可以开一个  
```set<pair<ll,ll>> st```  

在最后输出的时候记得**输出保留 10 位小数**  

## CODE  
勿抄 最后给出全 code  
```cpp
#include <iostream>
#include <queue>
#include <set>
#include <iomanip>
using namespace std;
typedef long long ll;
ll dx[5]={0,1,-1,0,0};
ll dy[5]={0,0,0,1,-1};
set<pair<ll,ll>> st;
ll n,m,r,k;
struct point
{
	ll x;
	ll y;
	ll val;
	point(ll x,ll y,ll val): 
	x(x),y(y),val(val){}
	friend bool operator<(const point p1,const point p2)
	{
		if(p1.val!=p2.val) return p1.val<p2.val;
	}
};

ll max(ll x,ll y)
{
	return x>y ? x : y;
}
ll min(ll x,ll y)
{
	return x<y ? x : y;
} 
ll gt(ll x,ll y)
{
	return (min(n,x+r-1)-max(x,r)+1)*(min(m,y+r-1)-max(y,r)+1);
}
priority_queue<point> q;
ll ans;
int main()
{
	cin>>n>>m>>r>>k;
	st.insert(make_pair((n+1)/2,(m+1)/2));
	q.push(point((n+1)/2,(m+1)/2,gt(((n+1)/2),(m+1)/2)));
	ll xx,yy;
	for(ll i=1;i<=k;i++)
	{
		point p=q.top();
		q.pop();
		ans+=p.val;
		for(ll dir=1;dir<=4;dir++)
		{
			xx=p.x+dx[dir];
			yy=p.y+dy[dir];
			if(xx<=0||xx>n||yy<=0||yy>m) continue;
			if(st.count(make_pair(xx,yy))) continue;
			q.push(point(xx,yy,gt(xx,yy)));
			st.insert(make_pair(xx,yy));
		}
	}
	ll tot=(n-r+1)*(m-r+1);
	double out=1.0*ans/tot;
	cout<<fixed<<setprecision(10)<<out;
}
```

---

## 作者：ljk123 (赞：0)

# Fishes题解

我们考虑每一条鱼的贡献，

显然是能被选中的矩形的个数/矩形总数

![fish](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912D/40c8b1b61edb367e0e414618a2e0b777e6a3b2ba.png)

可知，我们普通的鱼能被选中的矩形个数为r*r[从上至下r,从左至右r],

但是有时会受到矩形大小的限制，

此时x-r+1<1或者x+r-1>n或者y-r+1<1或者y+r-1>m，

能选矩形的下界为min(n-r+1,x),上界为max(1,n-r+1),上下长度为min(n-r+1,x)-max(1,x-r+1)+1=min(n-r+1,x)-max(0,x-r),

同理，左右长度为min(m-r+1,y)-max(0,y-r)，个数即为（min(n-r+1,x)-max(0,x-r)）×（min(m-r+1,y)-max(0,y-r)）。

矩形总数为：(n-r+1)*(n-r+1);

选出k条鱼的方案使期望最大，即是选出前k大期望的正方形格子，越在中间，肯定越不受矩形边界的限制，我们不妨从最中间起，向四周拓展。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100006,f[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
map<int,int> ha[N];
int n,m,r,k;
double ans=0.000;
struct xd{
   int x,y;
   double z;
   bool operator < (const xd &a) const {return a.z>z;}
}tmp,nw;
priority_queue<xd> q;
inline int read(){
   int T=0,F=1; char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') F=-1; ch=getchar();}
   while(ch>='0'&&ch<='9') T=(T<<3)+(T<<1)+(ch-48),ch=getchar();
   return F*T;
}
int main(){
    n=read(),m=read(),r=read(),k=read();
    tmp.x=n/2+1,tmp.y=m/2+1,ha[tmp.x][tmp.y]=1,tmp.z=(min(n-r+1,tmp.x)-max(0,tmp.x-r))*(min(m-r+1,tmp.y)-max(0,tmp.y-r))*1.0000000000000/(n-r+1)*1.0000000000000000/(m-r+1),q.push(tmp);
    for(int i=1;i<=k;++i){
        tmp=q.top(),ans+=tmp.z,q.pop();
        for(int j=0;j<4;++j){
            nw.x=tmp.x+f[j][0],nw.y=tmp.y+f[j][1];
            if(nw.x<1||nw.x>n||nw.y<1||nw.y>m||ha[nw.x].find(nw.y)!=ha[nw.x].end()) continue;
            nw.z=(min(n-r+1,nw.x)-max(0,nw.x-r))*(min(m-r+1,nw.y)-max(0,nw.y-r))*1.0000000000000/(n-r+1)*1.0000000000000000/(m-r+1);
            q.push(nw),ha[nw.x][nw.y]=1;
        }
    }
    printf("%.10lf",ans);
    return 0; 
}
 
```

---

