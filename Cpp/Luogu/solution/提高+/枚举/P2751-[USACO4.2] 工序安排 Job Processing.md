# [USACO4.2] 工序安排 Job Processing

## 题目描述

一家工厂的流水线正在生产一种产品，这需要两种操作：操作 $A$ 和操作 $B$。每个操作只有一些机器能够完成。

 ![](https://cdn.luogu.com.cn/upload/pic/1968.png) 

上图显示了按照下述方式工作的流水线的组织形式。$A$ 型机器从输入库接受工件，对其施加操作 $A$，得到的中间产品存放在缓冲库。$B$ 型机器从缓冲库接受中间产品，对其施加操作 $B$，得到的最终产品存放在输出库。所有的机器平行并且独立地工作，每个库的容量没有限制。每台机器的工作效率可能不同，一台机器完成一次操作需要一定的时间。

给出每台机器完成一次操作的时间，计算完成 $A$ 操作的时间总和的最小值，和完成 $B$ 操作的时间总和的最小值。

注：

1. 机器在一次操作中干掉一个工件；

2. 时间总和的意思是最晚时间点。

## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 4.2

## 样例 #1

### 输入

```
5 2 3
1 1 3 1 4```

### 输出

```
3 5```

# 题解

## 作者：BJpers2 (赞：27)

虽然代码和诸位大佬相去不远，但我的思路似乎有所不同。

假定**所有的A机器同时开始，所有的B机器同时结束。**

为什么可以这样想？因为结束时间不一样某种安排方案，我们可以找出那台最晚结束的B,然后把比它早结束的推迟一点，这样既不影响全局结束时间，又好理解。

首先考虑每一个物品，令f[i]表示第i个开始加工的物品处理完毕的最短时间，g[i]表示开始加工倒数第i个完成的物品距离“设定结束时间”的最短时间（其实和f[i]是一个意思）。

然后，完成一个成品就需要f[i]+g[j]的时间（i,j<=n）

最后贪心的想，**先完成的物品要离结束尽量远，后完成的物品要离结束尽量近**。因此不如直接把离结束最近的和最晚开始的凑成一对，离结束第二近的和第二晚开始的凑成一对......这样每一个物品都有了着落，耗时最长的物品就是全局时间。

但，考虑一下，这为什么是对的？我的意思是，f[i]+g[j]怎么就一定能表示一种可行解呢？难道不会出现，后完场的反而先做的情况吗？

实际上，假如i,j真的任意取，的确会这样。但在上述的“长配短”匹配当中，已经保证了 先被A加工完了的物品 ，一定不会排在 后被A加工完的物品 之后去被B加工。

思路清奇，但代码却十分简洁。
```cpp
#include<iostream>
#include<cstdio>
#define N 100
#define M 2020
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,A,B,a[N],b[N],x[N],y[N],f[M],g[M],p,q,ans;
int main(){
	scanf("%d%d%d",&n,&A,&B);
	FOR(i,1,A) scanf("%d",&a[i]),x[i]=a[i];
	FOR(i,1,B) scanf("%d",&b[i]),y[i]=b[i];
	FOR(i,1,n){
		f[i]=g[i]=1000010000;
		FOR(j,1,A) if(x[j]<f[i]) p=j,f[i]=x[j];
		FOR(j,1,B) if(y[j]<g[i]) q=j,g[i]=y[j];
		x[p]+=a[p],y[q]+=b[q]; 
	}FOR(i,1,n) ans=max(ans,f[i]+g[n-i+1]);
	printf("%d %d",f[n],ans);
}
```

---

## 作者：「QQ红包」 (赞：25)

ID: redbag

所以这道题贪心

开始从前往后贪，根据完成时间选择加工每件物品的机器（完成时间=等待时间+加工时间）

然后第二问从后往前贪，让最后一个完成操作A的物品 用效率最高的机器完成操作B

嗯代码挺详细的。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstdlib>
#include<list>
#include<map>
#include<set>
#include<list>
#include<stack> 
using namespace std;
int n,A,B;//n:
int m;
int i,j;
struct node
{
    int s;//目前这台机器 完成目前物品 结束的时间 
    int v;//该机器速度 
    bool operator<(node k)const
    {
        return s>k.s;
    } //小根堆 
};
priority_queue<node> q; 
int t[2000]; 
int ans;
int main()
{
    freopen("job.in","r",stdin);
    freopen("job.out","w",stdout);
    scanf("%d%d%d",&n,&A,&B); 
    node x;
    for (i=1;i<=A;i++)
    {
        scanf("%d",&x.v);
        x.s=x.v;
        q.push(x);//把速度压入优先队列中  
    }
    for (i=1;i<=n;i++)
    {
        x=q.top();//取出最小值 
        q.pop();//把最小值弹出 
        t[i]=x.s;//t[i]存的是第i个物品完成操作A 结束的时间 
        x.s+=x.v;//然后下一个物品要用这台机器 结束的时间就要+x.v 
        q.push(x);//再次压入栈 
    } 
    while (!q.empty()) q.pop(); 
    for (i=B;i>=1;i--)
    {
        scanf("%d",&x.v);
        x.s=x.v;
        q.push(x);
    } 
    ans=0;
    for (i=n;i>=1;i--)
    {
        x=q.top();//取出最小值 
        q.pop();//把最小值弹出 
        if (x.s+t[i]>ans) ans=x.s+t[i];//求最晚结束时间 
        x.s+=x.v;//然后下一个物品要用这台机器 结束的时间就要+x.v 
        //然而似乎开始用这台机器的操作该物品时候，可能上一个物品用这台 
        //机器已经完成任务了，然而这并不影响QAQ 
        q.push(x);
    }
    printf("%d %d\n",t[n],ans); 
    return 0;
}
```

---

## 作者：zltttt (赞：22)


第一问：贪心


让我们假设你有M1台效率不同的洗衣机，n件衣服，要求最短时间内洗完，你会怎么做？

——先把所有洗衣机塞满并打开，有任何一台洗好了就马上再塞一件衣服进去。


如果衣服都塞完了还有空闲的洗衣机，在其他在洗的洗衣机里找出还需用时最久洗完当前衣服的洗衣机，与空闲洗衣机中最快的比较，若速度比它洗完所用时间少，就取出来塞到这台空闲机子里去。


类比洗衣机与A机器，那么第一问就被我们解决了~


第二问：还是贪心


让我们假设你现在新获得了M2台烘干机并得到新任务——要求最短时间内洗完并烘干。


洗完一件马上塞一件到最快的空闲烘干机去？

显然有问题：连样例都过不去。为什么呢？

因为最后一件洗完的衣服决定了第二问的答案，但它并不一定得到最优待遇——最快的烘干机。


那，给最后一件洗完的衣服配最快的烘干机就是答案？

还是过不去样例。

因为可能会出现这样的情况——

两件衣服，第一件洗完时间为t,第二件为t+1,两台烘干机，速度为1和3。

显然答案是t+3,而上面的贪心答案是t+2。

也就是说，在上面贪心的情况下可能出现最后一件烘干的衣服并不是最后一件洗完的衣服的情况。


所以，我们想象：

对于从后往前的每一件衣服，为它像第一问一样准备一台当前最好的、能用的烘干机，给它烘干，然后记录这台烘干机在我们的规划中将烘干这件衣服，即在它需要烘干一件衣服的速度上加上自己最开始的速度，继续扫描，最后按规划来，就能过样例(AC)了！

为什么这样可以：

对每台烘干机记录相当于说：在它洗完上一件衣服后要求它洗记录的这件衣服，则我们在统计答案时这个结束时间便会被算在我们后面扫描到的衣服上——相当于我们在执行时先用这台烘干机烘干了后面使用它的衣服，再用它烘干了我们记录的这件衣服。


类比烘干机和B机器，第二问也解决了~

实现上，一个二叉堆（更省事可以用优先队列）随便搞搞（模拟）就可以了。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>

using namespace std;

struct node
{
    int nt,v;
    bool operator<(node k)const
    {
        return nt>k.nt;
    }
};

int n,cnta,cntb,ansa,ansb;
int t[1060];

priority_queue<node> q;

int main()
{
    scanf("%d%d%d",&n,&cnta,&cntb);
    
    for(int i=1;i<=cnta;i++)
    {
        node koishi;
        scanf("%d",&koishi.v);
        koishi.nt=koishi.v;
        q.push(koishi);
    }
    //推入一个优先队列 
    for(int i=1;i<=n;i++)
    {
        node koishi=q.top();
        q.pop();
        t[i]=koishi.nt;
        koishi.nt+=koishi.v;
        q.push(koishi);
    }
    ansa=t[n];
    //模拟[有空闲洗衣机就塞]过程 
    //第一问完毕 
    
    while(!q.empty())q.pop();
    
    for(int i=1;i<=cntb;i++)
    {
        node koishi;
        scanf("%d",&koishi.v);
        koishi.nt=koishi.v;
        q.push(koishi);
    }
    //同上推入队列 
    ansb=0;
    for(int i=n;i>=1;i--)//从后往前,这点很重要 
    {
        node koishi=q.top();
        q.pop();
        if(koishi.nt+t[i]>ansb)
            ansb=koishi.nt+t[i]; 
        koishi.nt+=koishi.v;//记录当前烘干机要在将来烘干第i件衣服
        q.push(koishi);
    }
    //模拟规划烘干的过程
     
    printf("%d %d\n",ansa,ansb);
    
    return 0;
}
```

---

## 作者：Zolrk (赞：3)

（碎碎念）-。-一开始想了个特别复杂的做法，后来发现写不出来233

先考虑A工序
考虑到产品是一个个完成的，而所用机器之间平行工作，题问的是时间轴上的最晚点
把机器在时间轴上平行排开，为每个机器分配一些工件，最后最晚完成最后一个机器的时间轴上的点就是最小“时间总和”
那么如何分配工件呢，发现机器的效率是已知的，结合机器曾经工作时间，就可以算出用这个机器完成第i个工件的时间点，找一个最小的，更新机器的曾经工作时间。同时记录下第i个工件完成的最早时间tim1[i]

（时间点，就是目前的最晚时间，最后一个处理的工件一定是最晚处理完的。如果说不是最晚处理完的，上一个工件比他早处理，处理完还比他晚，那我在处理上一个工件时，由于我是贪心地安排工序，我不可能说有能更早处理完的方案，我选择了更晚处理的方案，留更好的机器给下一个工件）

对于B工序，仍然采用上述方法求出tim数组，记作tim2[i]，因为A工序必须先于B工序，那么想要对第i个工件加工必须要在tim1[i]之后

先不管A的话，tim2数组表示的是，在B工序中，第i快完成的产品所花的时间，那么考虑A，假设某个工件在A中是第x个完成的，在B中是第y个完成的，那么总时间就是tm1[x] + tm2[y]，想要减少总时间，因为不能改变A，只能改变从“缓冲区”给B加工的工件次序，比如说A，1s，3s时分别出了两个产品x1,x2，改变x1,x2在B中处理的次序。

显然，tm1小的工件，他的tm2应该尽量大，才能使最后时间更平均（总时间是tm1  + tm2）

所以我们把tm1最小的安排成tm2最大的，第二小的安排成第二大的，最后答案是`max(tm1[i] + tm2[n-i+1])`
```c++
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1000 + 10;
int n,ma[MAXN],mb[MAXN],maa,mbb,at[MAXN],bt[MAXN],ans1,ans2,tm1[MAXN],tm2[MAXN];
int main() {
	cin >> n >> maa >> mbb;
	for(int i=1; i<=maa; i++) {
		cin >> ma[i];
	}
	for(int i=1; i<=mbb; i++) {
		cin >> mb[i];
	}
	
	for(int i=1; i<=n; i++) {
		int minj=1<<30, mint=1<<30;
		for(int j=1; j<=maa; j++) {
			if(at[j] + ma[j] < mint) {
				minj = j, mint = at[j] + ma[j];
			}
		}
		at[minj] = mint;
		tm1[i] = mint;
		if(i == n) ans1 = mint;
	}
	cout << ans1 << " ";
	for(int i=1; i<=n; i++) {
		int minj=1<<30, mint=1<<30;
		for(int j=1; j<=mbb; j++) {
			if(bt[j] + mb[j] < mint) {
				minj = j, mint = bt[j] + mb[j];
			}
		}
		bt[minj] = mint;
		tm2[i] = mint;
	}
	for(int i=1; i<=n; i++) {
		ans2 = max(ans2, tm1[i] + tm2[n-i+1]);
	}
	cout << ans2;
	return 0;
}
```

---

## 作者：Celebrate (赞：2)

先说明，我的代码及解释完善楼下的题解

第一问:

从前往后贪心，用f[i]记录第i个零件完成的最小时间

定义一个结构体，记录

v:每一台机器完成一个零件的时间和

s:完成下一个零件到达的时间点（会不断变化）

从前往后每次找完都要排序

最后输出f[n]

第二问：

f数组肯定是f[i]<=f[i+1],为了让最长时间尽量少，我们就尽量

让A,B连个步骤的总时间平均，,所以要 **从后往前** 找
查找的方

式和前面的几乎一样，但要记得+f[i]

代码如下：

```cpp
#include<bits/stdc++.h>
#define MAXN 1100
using namespace std;
int n,a,b;
struct node
{
	int s,v;
	//小根堆，在栈里面自动排序，非常有用，值得记一下 
	bool operator<(node k)const
	{
		if(s>k.s) return true;//这里把完成时间从小到大排一次序 
		return false;
	}
};
priority_queue<node> q;//栈，想学贪心必先学栈 
int f[MAXN];//记录第i个零件完成的最小时间
int main()
{
	int i;node x;
	scanf("%d%d%d",&n,&a,&b);
	for(i=1;i<=a;i++)
	{
		scanf("%d",&x.v); 
		x.s=x.v;
		//这里本来可以为0，但是为了让排序方便很多
		//而且这样可以避免很多不必要的情况发生  
		//比如说某一台机器运转时间比另一台高出了很多 
		q.push(x);//放进栈 
	}
	for(i=1;i<=n;i++)//从前往后 
	{
		x=q.top();//取出最小值 
		q.pop();
		f[i]=x.s;//记录 
		x.s=x.s+x.v;//为下一个做准备	
		q.push(x);//继续放进栈里面排序 
	}
	while(q.empty()==false) q.pop();//找完了A，再来找B，所以得把q全部弹出去 
	for(i=1;i<=b;i++)
	{
		scanf("%d",&x.v);//和上面几乎一样的操作 
		x.s=x.v;
		q.push(x);
	}
	int t=0;//t记录用时最长的那个 
	for(i=n;i>=1;i--)//从后往前 
	{
		x=q.top();
		q.pop();
		t=max(t,x.s+f[i]);//记得+f[i]，x不用自己加f[i] 
		x.s=x.s+x.v;
		q.push(x);
	}
	printf("%d %d\n",f[n],t);//输出 
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

模拟赛听同学讲没听明白故看了通过代码发现是简单贪心。

### 思路

只有 A 型机器显然是好做的，由于 $N$ 很小可以直接开优先队列存当前最早能完成操作的机器进行模拟然后取完成时间最大值即可。

考虑如何扩展到 B 型机器，发现想要更快地完成两种操作必须让完成时间更早的 B 型机器去接管完成时间较晚的 A 型机器的工件，然后直接取最大值即可。

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=3e4+5,mod=9999991;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
int f[N];
bool M2;signed main(){
	int q=qr,n=qr,m=qr;
	for(int i=1;i<=n;i++){
		int x=qr;
		pq.push({x,x});
	}
	int ans=0;
	for(int i=1;i<=q;i++){
		pair<int,int>x=pq.top();
		pq.pop();
		f[i]=x.first;
		ans=max(ans,f[i]);
		pq.push({x.first+x.second,x.second});
	}
	qws(ans);
	while(!pq.empty()) pq.pop();
	for(int i=1;i<=m;i++){
		int x=qr;
		pq.push({x,x});
	}
	ans=0;
	for(int i=q;i>=1;i--){
		pair<int,int>x=pq.top();
		pq.pop();
		f[i]+=x.first;
		ans=max(ans,f[i]);
		pq.push({x.first+x.second,x.second});
	}
	qw(ans);
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：1)

显然，这是一道贪心题。

$f_i$ 表示加工时间排名第 $i$ 的零件的产出时间即在 A 机器加工完成的时间，$g_i$ 统计在 B 机器中加工时间排名倒数第 $i$ 的零件的加工时间。

可以考虑一下为什么要这么设计 $f$ 数组和 $g$ 数组。借鉴一下乘船问题的思路，我们可以考虑让最先在 A 机器产出的零件进入到 B 机器中效率最慢的那一台，从而达到时间最短的目的。于是乎我们需要让 A 机器中的正数第 $i$ 和 B 机器中的倒数第 $i$ 配对。

我们可以考虑用堆优化降低时间复杂度。如果使用堆，可以自动排序，于是乎我们可以把数组 $f$、$g$ 用优先队列题解。

代码如下：

（这里提供的是堆优化的版本）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1005;
int N,M1,M2,ans[maxn];

struct node
{
	int id,t;//id是机器编号，t是产出当前物品和之前所有物品需要消耗的总时间
	friend bool operator < (node a,node b)
	{
		return a.t>b.t;
	}
}mach[maxn];

priority_queue<node> q1;
priority_queue<node> q2;

int main()
{
	cin>>N>>M1>>M2;
	int tmp;
   //对于每一台机器来说，它产出第一个物品的时间一定是它的初始效率时间
	for(int i=1;i<=M1;i++) cin>>tmp,q1.push({tmp,tmp});
	for(int i=1;i<=M2;i++) cin>>tmp,q2.push({tmp,tmp});
	for(int i=1;i<=N;i++)
	{
		node now=q1.top();q1.pop();
		ans[i]+=now.t;
		q1.push({now.id,now.id+now.t});//把更新之后的时间压入
	}
	cout<<ans[N]<<' ';
	for(int i=N;i;i--)//注意因为建立的是小根堆，所以要倒着枚举
	{
		node now=q2.top();q2.pop();
		ans[i]+=now.t;
		q2.push({now.id,now.id+now.t});
	}
	sort(ans+1,ans+N+1);
	cout<<ans[N];
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

简单贪心题。发现 $n, m1, m2$ 都很小，很自然的想到对于每个机器，处理出它做 $1-n$ 个物件的时间。

对于 A 类机器，我们会得到 $n \times m1$ 个数，将它们从小到大排序，此时第 $n$ 个数就是第一问的答案。

然后对 B 类做同样的处理，然后把 A 的用时前 $n$ 小的时间又从大到小排序，然后与 B 处理后的前 $n$ 个（B 是从小到大放）做计算，取最大用时。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long

const int N = 30005;
int n, m1, m2, cnt = 0, bar1[N], bar2[N], ans = 0;

bool cmp(int x, int y){return x > y;}
signed main(){
	scanf("%lld %lld %lld", &n, &m1, &m2);
	for(int i = 1; i <= m1; i ++){
		int x; scanf("%lld", &x);
		for(int j = 1; j <= n; j ++) bar1[++ cnt] = x * j;
	}
	sort(bar1 + 1, bar1 + cnt + 1);
	sort(bar1 + 1, bar1 + n + 1, cmp);
	cnt = 0;
	for(int i = 1; i <= m2; i ++){
		int x; scanf("%lld", &x);
		for(int j = 1; j <= n; j ++) bar2[++ cnt] = x * j;
	}
	sort(bar2 + 1, bar2 + cnt + 1);
	for(int i = 1; i <= n; i ++) ans = max(ans, bar1[i] + bar2[i]);
	printf("%lld %lld\n", bar1[1], ans);
	return 0; 
}
```


---

## 作者：Vin_1999 (赞：1)

好好的二分答案被我用二叉堆做是不是不太好（非正解轻喷）······

第一问二分答案就可以做，至于第二问就要用贪心了。

下面是本蒟蒻的不严格的证明：

因为,一件物品的完成时间=a加工时间+b加工时间。而我们求的是最大值中的最小值，那就要使timea and timeb尽量小。

所以第一个贪心就是先求出ta和tb最小的n个值存到pa和pb中。从pa和pb中求得答案，因为如果完成时间由不是前n小的数相加得到，那么该答案一定不会优于由前n小的数相加得到。

那么就用二叉堆求出pa和pb,特别的，要把一个机器加工两次得到两件物品等效为两个时间相差一倍的机器加工。（也就是说转化后的任何机器只加工一次，详见代码）

那第一问的答案就是pa[n]（有序），而对于第二问，在pa中最有可能相加得到最大完成时间的一定是最大数。我们首先考虑pa中最大的一个数，对它而言，一定要选pb中的最小数，这样得出的答案才会是最优的。当两者匹配后，忽略这二者再重复以上过程。在求出的完成时间中的最大值应该就是答案了。时间复杂度o(nlogn)

本来以为会错的，结果居然ac了。

以下是本蒟蒻丑陋的代码。








```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxn=1100,maxm=50;
int hr=0;struct H{int d,v;}h[maxn];
void ins(const H& T)
{
    int i;for(i=++hr;i!=1&&h[i>>1].v>T.v;i>>=1) h[i]=h[i>>1];h[i]=T;
}
void dlt()
{
    hr--;int i;for(i=1;(i<<1)<=hr&&(h[i<<1].v<h[hr+1].v||h[i<<1|1].v<h[hr+1].v);)
    i<<1!=hr&&(h[i<<1|1].v<h[i<<1].v)?(h[i]=h[i<<1|1],i=i<<1|1):(h[i]=h[i<<1],i<<=1);
    h[i]=h[hr+1];
}
```
static int a[maxm],b[maxm],n,ma,mb,

```cpp
           pa[maxn],pb[maxn],cnt;
int main()
{
     scanf("%d%d%d",&n,&ma,&mb);
     rep(i,1,ma) scanf("%d",&a[i]);
     rep(i,1,mb) scanf("%d",&b[i]);
    rep(i,1,ma) ins((H){i,a[i]});
    while(++cnt<=n)
    {
        pa[cnt]=h[1].v;
        H tmp=h[1];
        dlt();ins((H){tmp.d,tmp.v+a[tmp.d]});
    }
    printf("%d ",pa[n]);
    memset(h,0,sizeof(h));hr=0;
    rep(i,1,mb) ins((H){i,b[i]});
    while(--cnt)
    {
        pb[cnt]=h[1].v;
        H tmp=h[1];
        dlt();ins((H){tmp.d,tmp.v+b[tmp.d]});
    }
    int ans=-1<<29;
    rep(i,1,n) 
    {
        ans=max(ans,pa[i]+pb[i]);
    }
    printf("%d",ans);
    return 0;
}//by lyyz-ljy

```

---

## 作者：ymx2009 (赞：0)

# 题目大意
有 $N$ 个工件，$M_1$ 个 A 型机器，$M_2$ 个 B 型机器  
第一问求只用 A 型机器加工完所有的工件的最短时间  
第二问，A 型机器加工后用 B 型机器加工的最短时间
# Solution
## 第一问
贪心的使用完成加工时间靠前的机器，只需用一个小根堆维护即可，然后记录下每个工件完成加工的时间，以供第二问使用。
## 第二问
想要总耗时最短，那么一定要用第一问中完成时间晚的配 B 型机器中耗时少的。  
用一个小根堆维护，使用了一个机器以后就将现在的时刻加上它加工需要的时间重新加入堆中。  
注意：堆中存的是完成时刻，并不是加工耗时
# 代码时间

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010;
int n,ma,mb,t[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
signed main()
{
	cin>>n>>ma>>mb;
	for(int i=1;i<=ma;i++)
	{
		int a;
		cin>>a;
		q.push(make_pair(a,a));
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int x=q.top().first,v=q.top().second;
		t[i]=x;//记录每个工件的完成时间
		ans=max(x,ans);
		q.pop();
		q.push(make_pair(x+v,v));
	}
	cout<<ans<<' ';
	for(;!q.empty();) q.pop();
	for(int i=1;i<=mb;i++)
	{
		int b;
		cin>>b;
		q.push(make_pair(b,b));
	}
	ans=0;
	for(int i=n;i>=1;i--)//完成时间晚的配耗时短的，所以倒序遍历
	{
		int x=q.top().first,v=q.top().second;
		q.pop();
		ans=max(ans,t[i]+x);
		q.push(make_pair(x+v,v));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happy_zero (赞：0)

对于第一个问题，有一个比较显然的贪心：对于每一个物品，均找当前**做完**（而非开始做） A 操作时间最少的。由于物品之间是等价的，所以当前选时间更久的，之后选时间更短的，不如直接交换它们。容易用优先队列维护：$i$ 机器每增加一个物品，就将其在优先队列中的值加上 ${m_1}_i$。

这个策略是最优的（任意物品结束时间都最短），所以可以延续到第二问。

设所有物品 A 操作的结束时间为 $t_1\le t_2\le t_3\le...\le t_n$，最容易使答案增加的是 $t_n$。一次想到一个贪心策略：类似 A 操作那样，不过这次是从 $t_{n\to 1}$ 依次考虑，每次选择当前做完 B 操作时间最少的。

但这样其实是有点奇怪的。因为实际上做的顺序应该是 $t_{1\to n}$ 的做，但用优先队列维护时，计算的顺序是倒过来的。实际上，不妨设机器 $i$ 的机器序列为 $a_1,a_2,...a_{k_i}$，则第 $a_1$ 实际的结束时间为 $t_{a_1}+{m_2}_i$，$a_2$ 实际的结束时间为 $\max \{t_{a_1}+2\times {m_2}_i,t_{a_2}+{m_2}_i\}$，以此类推，$a_{k_i}$ 的结束时间就为 $\max_{1\le j\le k_i}\{t_{a_j}+(k_i-j+1)\times {m_2}_i\}$。

观察发现，这实际上和上面维护过程中计算的值是一样，事实上正着推也可以推出上面的实现。

```cpp
#include <bits/stdc++.h>
#define pii pair <int, int>
using namespace std;
const int N = 1005;
int a[N], t[N], b[N];
priority_queue <pii, vector <pii>, greater <pii> > q;
int main() {
	int s, n, m; cin >> s >> n >> m;
	for (int i = 1, x; i <= n; i++) 
		cin >> x, q.push({x, x});
	int ans = 0;
	for (int i = 1; i <= s; i++) {
		auto t = q.top(); q.pop();
		ans = max(ans, ::t[i] = t.first);
		q.push({t.first + t.second, t.second});
	}
	cout << ans << ' ';
	while (!q.empty()) q.pop();
	for (int i = 1, x; i <= m; i++)
		cin >> x, q.push({x, x});
	ans = 0;
	for (int i = s; i >= 1; i--) {
		auto t = q.top(); q.pop(); 
		ans = max({ans, ::t[i] + t.first});
		q.push({t.first + t.second, t.second});
	}
	cout << ans << '\n';
	return 0;
} 
```

---

## 作者：MarsCheng (赞：0)

# P2751 [USACO4.2] 工序安排 Job Processing 题解

## 启发思路的偏解

看到题目首先想到的是整体二分（不是正解，但对于思路推导有用）

考虑拿到一个答案后如何构造可行解。发现如果直接先考虑 A 工序再考虑 B 工序是不好做的，毕竟存在依赖关系。但是我们发现，如果 A 工序从前往后考虑，B 工序从后往前考虑，只需要 A 的结束时间比 B 的开始时间早，就可以天然满足依赖条件。

但是 A 的结束时间比 B 的开始时间早这个条件不好满足，考虑改成贪心（正解）

## 正解

根据上面的思路，我们可以让 A 工序从前往后考虑，B 工序从后往前考虑。

问题一是好做的，贪心每次选最快的机器即可。同时这个贪心也可以求出每一个工件在 A 的加工时间。

既然这样，我们也可以对 B 工序也做一遍同样的贪心。这样求出来的就是每一个工件的 B 工序时间。

最后我们需要匹配一下 A 工序的时间和 B 的工序的时间，最后的答案就是两个时间的最大的和，找到一个使其最小的匹配即可。

至于如何找到这样的一个匹配，把其中一个数组从大到小排序，另一个从小到大排序，此时答案最小。

## 代码

自认为码风很好。

```cpp
#include <bits/stdc++.h>

const int N = 1000 + 7, M = 30 + 7;
int n, a, b, fina[N], firb[N], ans;
struct Mas {
    int a, end;
} x[M], y[M];

int main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= a; i++)
        scanf("%d", &x[i].a);
    for (int i = 1; i <= b; i++)
        scanf("%d", &y[i].a);

    for (int i = 1; i <= n; i++) {
        int p = -1;
        for (int j = 1; j <= a; j++)
            if (p == -1 || x[j].end + x[j].a < x[p].end + x[p].a)
                p = j;
        x[p].end += x[p].a;
        fina[i] = x[p].end;
        ans = std::max(ans, x[p].end);
    }
    printf("%d ", ans);

    for (int i = 1; i <= n; i++) {
        int p = -1;
        for (int j = 1; j <= b; j++)
            if (p == -1 || y[j].end + y[j].a < y[p].end + y[p].a)
                p = j;
        y[p].end += y[p].a;
        firb[i] = y[p].end;
    }
    std::reverse(firb + 1, firb + n + 1);
    ans = 0;
    for (int i = 1; i <= n; i++)
        ans = std::max(ans, fina[i] + firb[i]);
    printf("%d", ans);
    return 0;
}

```

---

## 作者：AK_heaven (赞：0)

### [P2751 [USACO4.2] 工序安排 Job Processing](https://www.luogu.com.cn/problem/P2751)

这里讲解一下本题的归纳证明。

让人最开始的想法是从早到晚的去考虑每个刚刚从 $A$ 出来的产品，然后动态的决策用哪个机器。这是最容易假的，因为实际上很有可能前脚刚刚最优的动用了最快的机器，下一秒就又来了一个任务，而且还是最后一个！也就是说这道题目关注开始时间是没有用的，而且关注对于每个机器加工某个产品的结束时间同样是没用的，唯一有用的就是每台机器最后加工完成的时间。

首先陈述贪心策略：

让 $A_i$ 的分配方案最小，并让 $B_i$ 的分配方案同样最小。因为价值是 $A_i + B_i$，所以直接让最大的 $A_i$ 去匹配最小的 $B_i$，最后取 $\max$ 即可。

归纳证明：

考虑这是最后一个任务，现在所有机器都是空闲，肯定花时间最少的不会更劣。

现在最后一个任务完成了，倒数第二个任务成为了最后一个任务。现在就是一个子问题，至于是否所有机器都是空闲的，得看刚刚使用的机器中是不是空闲的。显然，永远不会更劣。

---

## 作者：Starry_Ocean (赞：0)

# 题解：P2751 [USACO4.2] 工序安排 Job Processing

参考文章：[BJpers2 的《题解 P2751 【[USACO4.2]工序安排Job Processing】》](https://www.luogu.com.cn/article/orv6f96r)。

### 算法：贪心算法。
### 主要思路如下：
+ 假定所有的 A 机器**同时开始**，所有的 B 机器**同时结束**。
  
+ 定义 $ f(i)$ 表示第 $ i$ 个开始加工物品处理完毕的最短时间。
  
+ 定义 $ g(i)$ 表示 开始加工后倒数第 $ j$ 个加工完毕的最短时间。


__所以,完成一个成品需要 $ f(i)+g(j) $的时间。__

即：
$$
 f(i)+g(N-i+1) 
$$

+ 由上述易得，要想完成时间最小，**就有让先完成的物品要离结束尽量远，后完成的物品要离结束尽量近。**


我们不妨假设第 $ i$ 个物品为 $ w_i$。 

再把 $ w_i$ 和 $ w_{N-i+1} $ 放在一起。

+ 那么，**总体最短时间**为**单个物品完成耗时最长时间**。

#### 由上述地，第一问的答案为 $ f(N)$。

#### 第二问的答案为
$$
 \max( f(i) + g(N-i+1) ) 
$$



### AC 代码如下： 
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll N,M1,M2;
ll a[36],b[36];
ll f[1006],g[1006];
ll aa[36],bb[36];
int main(){
	cin>>N>>M1>>M2;
	for(int i = 1;i <= M1;++i){
		cin>>a[i];
		aa[i]=a[i];
	}
	for(int i = 1;i <= M2;++i){
		cin>>b[i];
		bb[i]=b[i];
	}
	ll p,q;
	for(int i = 1;i <= N;++i){
		f[i]=1000000006;
		g[i]=1000000006;//因为需要f,g 最小，所以两个数组都要初始化到一个很大的数 
		for(int j = 1;j <= M1;++j){
			if(f[i]>aa[j]){
				p=j;
				f[i]=aa[j];
			}
		} 
		for(int j = 1;j <= M2;++j){
			if(g[i]>bb[j]){
				q=j;
				g[i]=bb[j];
			}
		}
		aa[p]+=a[p];
		bb[q]+=b[q];
	}
	cout << f[N] << " ";
	ll ans=0;
	for(int i = 1;i <= N;++i){
		ans=max(ans,f[i]+g[N-i+1]);
	}
	cout << ans;
	return 0;
} 
```

#### [AC 记录](https://www.luogu.com.cn/record/168274865)

---

## 作者：oddy (赞：0)

## 题意简述

有若干工件需要**依次**经历两道工序加工。每道工序各有若干台机器供使用，加工时间各不相同。求加工完这些工件所需的最短时间（挂钟时间）。

## 解题思路

假如只有一道工序，那是很容易的。就是贪心地加工每个零件，哪个机器加工完后的挂钟时间短就用哪个。

但是，有两道工序，那么完成工序 A 后，不好判断先加工谁，后加工谁。即我们不能通过直接依次模拟两道工序来得到答案。

那么，我们考虑分开进行两步的加工：即假设在 B 机器后面也有同样数量的工件（称为“新工件”）在等着，一个工件的工序 A 完成后，对应的新工件立即进入 B 机器。它们在中间“会合”，构成成品。考虑到这样做，工序 A、B 之间并无依赖关系，故我们可以**分别计算**每个工件经历两个工序的时间，且一个工件所用的时间，就是其两道工序的时间**之和**。

有人要问了：这样做与题意不一致，是否会改变答案呢？并不会。因为“新工件”进入 B 机器是在对应的工件已经完成 A 工序之后。并不会有一对“对应的”工件同时在两个机器里的情况。

## 代码

```cpp
#include <cstdio>
#include <algorithm>

int n, m1, m2, t, ans, a[35], b[35], t1[35], t2[35], f[1005];
// t1, t2 分别为两种机器加工完成后的挂钟时间

int main() {
    scanf("%d%d%d", &n, &m1, &m2);
    for(int i = 1; i <= m1; i++) scanf("%d", a+i);
    for(int i = 1; i <= m2; i++) scanf("%d", b+i);

    for(int i = 1; i <= n; i++) {
        for(int j = t = 1; j <= m1; j++)
            if(t1[j] + a[j] <= t1[t] + a[t]) t = j;
        f[i] = t1[t] += a[t];
    }
    printf("%d ", f[n]);

    for(int i = n; i; i--) {
        for(int j = t = 1; j <= m2; j++)
            if(t2[j] + b[j] <= t2[t] + b[t]) t = j;
        f[i] += t2[t] += b[t];
    }
    printf("%d\n", *std::max_element(f+1, f+n+1));

    return 0;
}
```

---

