# [USACO18FEB] Hoofball B

## 题目描述

为了准备即将到来的蹄球锦标赛，Farmer John 正在训练他的 $N$ 头奶牛（方便起见，编号为 $1\ldots N$，其中 $1\le N\le 100$）进行传球。这些奶牛在牛棚一侧沿直线排列，第 $i$ 号奶牛位于距离牛棚 $x_i$ 的地方（$1\le x_i\le 1000$）。每头奶牛都在不同的位置上。

在训练开始的时候，Farmer John 会将若干个球传给不同的奶牛。当第 $i$ 号奶牛接到球时，无论是从 Farmer John 或是从另一头奶牛传来的，她会将球传给最近的奶牛（如果有多头奶牛与她距离相同，她会传给其中距左边最远的那头奶牛）。为了使所有奶牛都有机会练习到传球，Farmer John 想要确保每头奶牛都持球至少一次。帮助他求出为了达到这一目的他开始时至少要传出的球的数量。假设他在开始的时候能将球传给最适当的一组奶牛。 

## 说明/提示

在上面的样例中，Farmer John 应该将球传给位于 $x=1$ 的奶牛和位于 $x=11$ 的奶牛。位于 $x=1$ 的奶牛会将她的球传给位于 $x=3$ 的奶牛，在此之后这个球会在位于 $x=3$ 的奶牛和位于 $x=4$ 的奶牛之间来回传递。位于 $x=11$ 的奶牛会将她的球传给位于 $x=7$ 的奶牛，然后球会被传给位于 $x=4$ 的奶牛，在此之后这个球也会在位于 $x=3$ 的奶牛和位于 $x=4$ 的奶牛之间来回传递。这样的话，所有的奶牛都会至少一次接到球（可能从 Farmer John，也可能从另一头奶牛）。

可以看出，不存在这样一头奶牛，Farmer John 可以将球传给她之后所有奶牛最终都能被传到球。 

## 样例 #1

### 输入

```
5
7 1 3 11 4```

### 输出

```
2```

# 题解

## 作者：Silent1019 (赞：8)

### [题目链接](https://www.luogu.com.cn/problem/P1677)
## 思路
由于奶牛只会传球给离它最近的奶牛，可以想到将每个奶牛的位置进行从小到大排序，那么问题就变为奶牛传球给左右距离它近的奶牛，只需要考虑两边。

接下来，可以模拟一遍每个奶牛得到球后会传给哪个奶牛，每个奶牛传给球的奶牛的位置记在 ```to``` 数组中，每个奶牛从其他奶牛传球能得到球的次数记在 ```cnt``` 数组中。很显然，```cnt``` 值为 $0$ 的奶牛不能从其他奶牛传球中得到球，记录这些奶牛的个数为 ```ans```。

#### 注意：两个奶牛相互传球且这两个奶牛都不能从其他奶牛中得到球时，答案也需要加 $1$。

```INF``` 不能设置为 $2147483647$，在计算距离时会超出 ```int``` 范围。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000
const int N=105;
int n,ans;
int a[N],to[N],cnt[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);//将奶牛按距离左边从小到大排序 
	a[0]=-INF; a[n+1]=INF;
	for(int i=1;i<=n;i++)
		if(a[i]-a[i-1]>a[i+1]-a[i])//因为距离相同传给距左边最远的奶牛，那么只能用'小于'
		{
			to[i]=i+1;
			cnt[i+1]++;
		}else{
			to[i]=i-1;
			cnt[i-1]++;
		}
	//求出每个点的奶牛接到求后会传球给的奶牛
	 
	for(int i=1;i<=n;i++)
		if(!cnt[i]) ans++;
	//如果不能通过传球得到球，那么ans+1 
	
	for(int i=1;i<=n;i++)
		if(cnt[i]==1&&cnt[i+1]==1&&to[i]==i+1&&to[i+1]==i)
			ans++;
	//如果两个奶牛是相互传球，且其他奶牛不会传球给这两个奶牛，那么ans也要加1 
			
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：jianglai0119 (赞：4)

附上样例解释图

![](https://cdn.luogu.com.cn/upload/image_hosting/5nztkys3.png)

每头奶牛**都会**传给另一头奶牛。（~~少说废话~~）

如果没有其他奶牛会把球传给这头奶牛，则 FJ **必定**要把球传给这只奶牛。  
FJ 会把球传给也一头奶牛后，这头奶牛会继续传给另外的奶牛，直至两头奶牛一直循环。  
所以我们可以计算 FJ 必定要发的球个数。  
我们可以把传球抽象成有向边，那么奶牛我们可以抽象成节点。那么 FJ 必定要发给那些入度为 0 的奶牛（因为没有其他奶牛会传给他球）。

所以我们上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,a[maxn],Du[maxn],ans;
int read(){
	int ret=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))ret=ret*10+(c&15),c=getchar();
	return ret*f;
}
int main(){;
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);//注意要排序，因为每头奶牛的位置不一定单调递增
	for(int i=1;i<=n;i++){
		if(i==1)Du[i+1]++;
		else if(i==n)Du[i-1]++;
		else{
			if(a[i]-a[i-1]<=a[i+1]-a[i])Du[i-1]++;
			else Du[i+1]++;
		}
	}
	for(int i=1;i<=n;i++)if(!Du[i])ans++;
	printf("%d",ans);
	return 0;
}
```
很好，喜提 10 分。

所以我们到底哪里错了？

一个不错的反例：

```
7
7 1 3 11 4 100 101
```
![](https://cdn.luogu.com.cn/upload/image_hosting/1w3tlblz.png)

按照我们的思路，入度为 0 的只有 2 个节点，但是，答案却是 3，因为 100 和 101 他们互相传来传去，虽然他们度不为零，但是他们也要 FJ 传球。思考以后，我们发现，一组里面最多只有 2 头奶牛会传来传去，即一个环里面最多只有两个节点。因为没有自环，所以**一个环里面只有 2 个节点**。

我们可以先枚举入度为零的节点的个数，每出现一个入度为零的节点我们做一次 DFS，把走过的节点用 vis 标记，到最后还会剩下一些节点没有被遍历，即出现了前面的环，因为每个环要一个球，所以说 $ans=\textsf{入读为 0 的节点数}+\textsf{没被便利的节点数} \div 2$。

由于这道题每头奶牛只会传给一头奶牛，所以我们并不需要邻接表存图，只要用 nxt 数组标记这头奶牛会传给谁即可。

至此，这道题解完了。

你听懂了吗？

上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,a[maxn],Du[maxn],que[maxn],hed,til,ans,cnt,nxt[maxn];
bool vis[maxn];
int read(){
	int ret=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))ret=ret*10+(c&15),c=getchar();
	return ret*f;
}
void DFS(int x){
	if(vis[x])return;
	vis[x]=1;DFS(nxt[x]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);//注意要排序，因为每头奶牛的位置不一定单调递增
	for(int i=1;i<=n;i++){
		if(i==1)Du[i+1]++,nxt[i]=i+1;
		else if(i==n)Du[i-1]++,nxt[i]=i-1;
		else{
			if(a[i]-a[i-1]<=a[i+1]-a[i])Du[i-1]++,nxt[i]=i-1;
			else Du[i+1]++,nxt[i]=i+1;
		}
	}
	for(int i=1;i<=n;i++)if(!Du[i])ans++,DFS(i);
	for(int i=1;i<=n;i++)if(!vis[i])cnt++;
	printf("%d",ans+cnt/2);
	return 0;
}
```
**警告：抄题解会得到最宝贵的用户名颜色：${\color{brown} 棕}$**

---

## 作者：simple_child (赞：3)

# 样例分析
本题跟 football（2024江苏省夏令营基础班第3课探究6）有点像，从[2107 传球](https://jsoi.jzhx.net/question/2107)来的huh~

在样例中， Farmer John 应该将球传给位于 $x=1$ 的奶牛和 $x=11$ 的奶牛。

位于 $x=1$ 的奶牛将她的球传给位于 $x=3$ 的奶牛，然后这个球会在位于 $x=3$ 和 $x=4$ 的奶牛之间来回传递。

位于 $x=11$ 的奶牛将她的球传给位于 $x=7$ 的奶牛，然后球会被传给 $x=4$ 的奶牛，然后球会在 $x=3$ 和 $x=4$ 的奶牛之间来回传递。这样的话，所有的奶牛都至少接到一次球（可能是从 Farmer John 传过来的，也可能是从其他奶牛传过来的）
# 思路
每次传球都是往最近的地方传球，如果相同距离，则向最左边传球。

那么首先一遍 DFS 判断哪些只有一个入度，那么给他一个球，然后再 DFS 一下，看一下环的情况，给每个环一个球即可。

# AC code
### （代码比较抽象，与思路关联不大）
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];
int dis[105][50];
int vis[105];
int ans[105];
int cnt=1;
int dfs(int i)//函数比较抽象，建议仔细读读，切勿直接抄袭——
{
	if(vis[i]==cnt) return 0;
	vis[i]=cnt;
	if(dis[i][1]==0) dfs(i+1);
	else if(dis[i][2]==0) dfs(i-1);
	else if(dis [i][1]!=0&&dis[i][2]!=0)
	{
		if(dis[i][1]<dis[i][2]) dfs(i-1);
		else if(dis[i][1]>dis[i][2]) dfs(i+1);
		else dfs(i-1);
	}
	return 0;
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//快读huh，本人不喜欢scanf和printf
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    dis[1][2]=a[2]-a[1];
    dis[n][1]=a[n]-a[n-1];
    for(int i=2;i<n;i++)
    {
    	dis[i][1]=a[i]-a[i-1];
    	dis[i][2]=a[i+1]-a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==0) dfs(i);
		cnt++;
	}
	for(int i=1;i<=n;i++)
	{
		ans[vis[i]]=1;
	}
	cnt=0;
	for(int i=1;i<=105;i++)
	{
		if(ans[i]==1) cnt++;
	}
	cout<<cnt<<endl;//忠爱endl
    return 0;
}
```

---

## 作者：Je_son (赞：2)

## 思路大意
对题目分析后可以发现，一头牛只会传给离它最近的牛传球，将牛的位置排序后，问题就简化成给两侧较近的牛传球，对于没有牛会给它传球的牛，农夫约翰都应给它一个球。

继续对题目分析，发现还会出现环的情况，也就是牛 A 给牛 B 传球且牛 B 给牛 A 传球的情况，且牛 A 和牛 B 只能接收到对方的球，此时需要特判，再将结果加 1。

## Ac代码
```
#include <bits/stdc++.h>
using namespace std;

const int N = 110, INF = 2e9;
int n, res, a[N], to[N], cnt[N];

int main()
{
    scanf("%d", &n);
    a[0] = -INF, a[n + 1] = INF;
    for(int i = 1; i <= n; i ++ )
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);

    // 模拟传球
    for(int i = 1; i <= n; i ++ )
    {
        if(a[i] - a[i - 1] <= a[i + 1] - a[i])
            cnt[i - 1] ++ , to[i] = i - 1;
        else
            cnt[i + 1] ++ , to[i] = i + 1;
    }

    // 记录没有牛会给它传球的牛的数量
    for(int i = 1; i <= n; i ++ )
        if(!cnt[i])
            res ++ ;

    // 特判产生环的情况
    for(int i = 2; i <= n; i ++ )
        if(to[i - 1] == i && to[i] == i - 1 && cnt[i - 1] == 1 && cnt[i] == 1)
            res ++ ;
    
    printf("%d\n", res);
}
```

---

## 作者：_Dynamic_Programming (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P1677)
# 思路
1. 因为对于每一个 $x_i$ 而言，可以传球给离自己最近的位置，也就是左边或右边，所以我们可以给 $x$ 数组从小到大排个序。
```c++
sort(x + 1, x + n + 1);
```
2. 接下来我们要用 $in$ 数组统计每一只奶牛会被多少只奶牛传球，并用 $out$ 数组每只奶牛会传球给那只奶牛，离左边近传给左边，离右边近传给右边。
```c++
for(int i = 1; i <= n; i++)
{
    if(x[i] - x[i - 1] <= x[i + 1] - x[i]) in[i - 1]++, out[i] = i - 1;
    else in[i + 1]++, out[i] = i + 1;
}
```
3. 统计完后，我们依次遍历每一只奶牛，如果没有奶牛会传给它球，那么说明我们要从它这里发球，`ans++`。
```c++
for(int i = 1; i <= n; i++)
    if(in[i] == 0) ans++;
```
4. 当然，如果有两只奶牛互传的现象，`ans++`。
```c++
for(int i = 1; i < n; i++)
    if(in[i] == 1 && in[i + 1] == 1 && out[i] == i + 1 && out[i + 1] == i)
        ans++;
```
这样，我们便得到了答案。

# Code
```c++
#include <bits/stdc++.h>
using namespace std;
int n, x[105], in[105], out[105];
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
    sort(x + 1, x + n + 1);
    x[0] = -1e9, x[n + 1] = 1e9;
    for(int i = 1; i <= n; i++)
    {
    	if(x[i] - x[i - 1] <= x[i + 1] - x[i]) in[i - 1]++, out[i] = i - 1;
    	else in[i + 1]++, out[i] = i + 1;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    	if(in[i] == 0) ans++;
    for(int i = 1; i < n; i++)
    	if(in[i] == 1 && in[i + 1] == 1 && out[i] == i + 1 && out[i + 1] == i)
    		ans++;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：xxxaIq (赞：0)

# 思路：

首先将数组排序，这样每个奶牛都只会传给自己左边或右边距离最近的奶牛了。

我们在每头奶牛与它要传给的奶牛之间加一条有向边，这样就只需要农夫把球传给入度为 $0$ 的点的奶牛即可。

但是这样是不对的，因为还可能有 $2$ 头奶牛独立成一个环，它们的入度都是 $1$，但是也需要一个球。

下面来证明为什么独立成环的奶牛一定是 $2$ 头呢？假设现在有 $3$ 只奶牛可以互相传球，因为数组已经有序，每个奶牛都只会传给自己左边或右边的其中一头奶牛，如果有 $3$ 头奶牛的话那么中间那一只就既可以往左边传也可以往右边传，矛盾。

那么只需要从每一个入度为 $0$ 的结点枚举到所有能访问的点，剩下的点自然就是两两成环了。

# 代码：


```cpp
//code by xxxaIq
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=103;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}//快读 

int n,a[maxn],rd[maxn],cnt,ans;//cnt记录从入度为0的点出发能访问到的点的个数

vector<int>e[maxn];//存图

bool mk[maxn];//防止走回头路

void dfs(int u){
	mk[u]=true;
	cnt++;//更新cnt
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(mk[v]==false){
			dfs(v);
		}
	}
	return;
}

int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n);//排序
	rd[2]++;
	e[1].push_back(2);
	rd[n-1]++;
	e[n].push_back(n-1);
        //当i等于1或时有一边没有奶牛，所以单独处理
	for(int i=2;i<n;i++){//从2到n
		if(a[i]-a[i-1]<=a[i+1]-a[i]){//注意是小于等于
			rd[i-1]++;
			e[i].push_back(i-1);
		}else{
			rd[i+1]++;
			e[i].push_back(i+1);
		}
    //加边同时更新入度
	}
	for(int i=1;i<=n;i++){
		if(rd[i]==0){
			ans++;///入读为0的点
			dfs(i);
		}
	}
	cout<<ans+(n-cnt)/2;//计算并输出
	return 0;
}
```

---

## 作者：cdxxx04 (赞：0)

# 题解：P1677 [USACO18FEB] Hoofball B

**[[USACO18FEB] Hoofball B](https://www.luogu.com.cn/problem/P1677)**

## 题目简述

给定 $n$ 个点到起点的距离，这些点排成一行并向离他最近的点建边。求至少从多少个点开始，可以遍历这张图。

## 前言

什么是反图：
>于有向图 $G = (V, E)$ ，它的 **反图 (transpose graph)** 指的是点集不变，每条边反向得到的图，即：若 $G$ 的反图为 $G'=(V, E')$ ，则 $E'=\{(v, u)|(u, v)\in E\}$。
>
>**摘自 [OI Wiki](https://oi-wiki.org/graph/concept/#%E5%8F%8D%E5%9B%BE)**

## 题目思路

这题是用到了正难则反的思想：建反图然后暴力枚举。

为什么反图可以求至少从多少个点开始可以遍历图：

>因为如果一个图是连通的，那么从任意一个顶点开始都可以遍历到所有其他顶点。通过构造反图，我们可以更容易地识别原图中的连通分量。如果反图中存在孤立的顶点或不连通的分量，那么原图中就存在一些顶点之间的路径长度较长或者无法直接到达的情况。

**所以详细的做法是枚举每一个反图中的点来作为起点，然后依次查看之后的点是否已经访问。如果点没有访问过那么就访问所有这个点可以到达的点并始答案增加。最后输出所有答案中的最小值。**

## 代码

```cpp
#include<bits/stdc++.h>
namespace fasI{//快速读入。 
    #define BF_SIZE 100000
    bool IOerr=0;
    inline char nc(){
        static char buf[BF_SIZE],*p1=buf+BF_SIZE,*pend=buf+BF_SIZE;
        if(p1==pend){
            p1=buf;
            pend=buf+fread(buf,1,BF_SIZE,stdin);
            if(pend==p1){IOerr=1;return -1;}
        }
        return *p1++;
    }
    inline bool bla(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        register char ch;
        while(bla(ch=nc()));
        if(IOerr){return;}
        for(x=ch-'0';(ch=nc())>='0'&&ch<='9';x=x*10+ch-'0');
    }
    //快读。 
    void write(int x)
	{
	    if(x<0)	putchar('-'),x=-x;
	    if(x>9)	write(x/10);
	    putchar(x%10+'0');
	}
	//快写。 
    #undef BF_SIZE
};
using namespace std;
using namespace fasI;//使用快读的名字空间。 
const int N=105;
int a[N],ans=INT_MAX,n;//距离，答案，奶牛数量。 
bool vis[N];//是否访问。 
vector<int> v[105];//图。 
void dfs(int x){//dfs暴力求解。 
	vis[x]=true;
	for(int y:v[x]){
		if(vis[y]==true)	continue;
		dfs(y);
	}
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)	read(a[i]);
	//输入。 
	sort(a+1,a+n+1);
	//输入无单调性，需排序。
	a[n+1]=INT_MAX;	a[0]=INT_MIN;
	//防止建图出界。 
	for(int i=1;i<=n;i++)
		if(a[i]-a[i-1]>a[i+1]-a[i])	v[i].push_back(i+1);
		else	v[i].push_back(i-1);
	//向离的近的建反图。 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)	vis[j]=false;
		//多次要清空。 
		int sum=0;
		for(int j=i-1,k=1;k<=n;j=(j+1)%n,k++)
			if(vis[j+1]==false)
				sum++,dfs(j+1);
		//暴力遍历起点。 
		ans=min(sum,ans);
		//打擂台。 
	}
	write(ans);
	//输出。 
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

显然，我们需要把所有奶牛的坐标排序，这样就能很方便地找到某个奶牛会传给的奶牛。

具体来说，排序后，对于每个奶牛 $i$，它会传给的奶牛必为 $i+1$ 和 $i-1$，所以判断它和哪一头奶牛距离更近即可。与此同时，我们还可以处理出每头奶牛会被多少头奶牛传球。

接下来，我们就该统计答案了。观察到，如果一头奶牛不会被任何一头奶牛传球，则 FJ 就必须给它传球。

用这样的思路写完，发现过不了。自己手造了一个样例：

```
4
1 2 100 101
```

我们发现，每头奶牛都会被一头奶牛传球，所以程序输出零。但是，实际需要给第 $1$ 和 $3$ 头奶牛传球，答案是 $2$。

由此，我们发现，如果两头奶牛满足它们不会被其他奶牛传球，且它们会无限互相传球时，答案需要加一。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,an,a[101],nx[101],cn[101];
signed main(){
	ios::sync_with_stdio(0),cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(i==1)nx[i]=2,cn[2]++;
		else if(i==n)nx[i]=n-1,cn[n-1]++;
		else if(a[i]-a[i-1]>a[i+1]-a[i])
			nx[i]=i+1,cn[i+1]++;
		else nx[i]=i-1,cn[i-1]++;
	}
	for(int i=1;i<=n;i++)if(!cn[i])an++;
	for(int i=1;i<=n;i++)
		if(cn[i]==1&&cn[i+1]==1&&nx[i]==i+1&&nx[i+1]==i)an++;
	cout<<an;
	return 0;
}
```

---

