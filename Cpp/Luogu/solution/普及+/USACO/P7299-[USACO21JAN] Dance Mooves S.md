# [USACO21JAN] Dance Mooves S

## 题目描述

Farmer John 的奶牛们正在炫耀她们的最新舞步！

最初，所有的 $N$ 头奶牛（$2≤N≤10^5$）站成一行，奶牛 $i$ 排在其中第 $i$ 位。舞步序列给定为 $K$ （$1≤K≤2\times10^5$）个位置对 $(a_1,b_1),(a_2,b_2),…,(a_K,b_K)$。在舞蹈的第 $i=1…K$ 分钟，位置 $a_i$ 与 $b_i$ 上的奶牛交换位置。同样的 $K$ 次交换在第 $K+1…2K$ 分钟发生，在第 $2K+1…3K$ 分钟再次发生，以此类推，无限循环。换言之， 

 - 在第 $1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - ……
 - 在第 $K$ 分钟，位置 $a_K$ 与 $b_K$ 上的奶牛交换位置。
 - 在第 $K+1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $K+2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - 以此类推……

对于每头奶牛，求她在队伍中会占据的不同的位置数量。

## 说明/提示

 - 奶牛 $1$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $2$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $3$ 可以到达位置 $\{1,2,3\}$。
 - 奶牛 $4$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $5$ 从未移动，所以她没有离开过位置 $5$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤100,K≤200$。
 - 测试点 6-10 满足 $N≤2000,K≤4000$。
 - 测试点 11-20 没有额外限制。

供题：Chris Zhang 

## 样例 #1

### 输入

```
5 4
1 3
1 2
2 3
2 4```

### 输出

```
4
4
3
4
1```

# 题解

## 作者：Skies (赞：23)

本文语言较为生动，容易理解，~~适合像我一样的菜鸡~~

## 题面分析

我们考虑，在经过k次变换（k分钟）后，每头牛会途径某些点到达另一个点，假如其中有一头好看的牛叫A，A从x位置走到了y位置，而另一头牛B，从z走到了x，那么再经过一轮，B也会走到y位置。

也就是说

### B的运动轨迹将会和A一样，只不过是落后k分钟罢了

### 同时，B经过的点也和A一样

于是乎

### 像A , B一样的，有相同运动轨迹的牛，将会有一群（当然一群里面可能也只有一只）

### 而这群牛在k分钟内的运动轨迹将会构成一个环

用并查集维护这个环

我们再用vector来记录每个点途径的点，然后

对于同一个环内（同一牛群），用set来统计每个点的途径点总共有多少个，设为x

环内的每一头牛能经过点的个数，就是x.

讲到这里，思路就非常明晰了，尝试自己写写吧！

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k;
int a[N];
int fa[N],si[N];
void init()
{
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		a[i]=i;
	}
}
int get(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
vector<int >vc[N];
int cx[N],cy[N];
set<int> ans[N];

void out()
{
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	
	cin>>n>>k;
	init();
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		
		swap(a[x],a[y]);
		vc[a[x]].push_back(x);//记录途径点
		vc[a[y]].push_back(y);//同上
	}
	for(int i=1;i<=n;i++)
	{
		vc[i].push_back(i);//加上他们的起点点
	}
	for(int i=1;i<=n;i++)
	{
	    int x=get(i),y=get(a[i]);//把这两个点放到同一个牛群中
	    fa[x]=y;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<vc[a[i]].size();j++)
		{
			ans[get(a[i])].insert(vc[a[i]][j]);//统计每个点的途径点总共有多少个
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[get(i)].size());//不同途径点的个数即答案
	}
	return 0;
}
```



~~管理员小哥哥辛苦！~~



---

## 作者：henrytb (赞：12)

感觉我的做法好暴力啊...

我们先模拟一轮，看每头牛分别能到哪里，对每头牛开一个 `set`。

模拟完一轮之后，我们可以找到这个序列中所有的环。

然后将这些环中的 `set` 合并即可。

一个节省代码量的小 trick：将两个 `set` 合并可以这么写：

```cpp
a.insert(b.begin(),b.end()); // 意为将 b 合并进 a
```

核心代码：

```cpp
void dfs(int u,int k,bool first) {
    if(!first&&u==k) return ;
    vis[u]=1;
    s[k].insert(s[u].begin(),s[u].end());
    dfs(cow[u],k,0);
}
void dfs2(int u,int k,bool first) {
    if(!first&&u==k) return ;
    ans[u]=s[k].size();
    dfs2(cow[u],k,0);
}
int main() {
    scanf("%d%d",&n,&k);
    rep(i,1,n) cow[i]=i,s[i].insert(i);
    rep(i,1,k) {
        int a,b;
        scanf("%d%d",&a,&b);
        swap(cow[a],cow[b]);
        s[cow[b]].insert(b);
        s[cow[a]].insert(a);
    }
    rep(i,1,n) if(!vis[i]) {
        dfs(i,i,1);
        dfs2(i,i,1);
    }
    rep(i,1,n) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Zenith_Yeh (赞：8)

先分析样例：

|  | 1 | 2 | 3 | 4 | 5 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| k=1 | 3 | 2 | 1 | 4 | 5 |
| k=2 | 2 | 3 | 1 | 4 | 5 |
| k=3 | 2 | 1 | 3 | 4 | 5 |
| k=4 | 2 | 4 | 3 | 1 | 5 |

进行一轮后，发现结果等价于把 $1,2,4$ 互换了位置，意味着接下来第二轮的时候：

-  $1$ 会走第一轮 $4$ 走的路线。
-  $2$ 会走第一轮 $1$ 走的路线。
-  $4$ 会走第一轮 $2$ 走的路线。

因为他们走的路线相同，所以我们可以把 $1,2,4$ 看成一个整体。（用并查集维护即可）

**上菜：**

```cpp
#include<bits/stdc++.h>
inline int read()
{   int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c))f|=(c=='-'),c=getchar();
    while(isdigit(c))x=x*10+(c&15),c=getchar();
    return f?-x:x;
}
#define read() Read<int>()
namespace pb_ds{
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
        #define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int n,k,num[100005],fa[100005];
vector<int>lg[100005];
set<int>answer[100005];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main()
{	n=read(),k=read();
	for(register int i=1;i<=n;++i)num[i]=i,fa[i]=i,lg[i].push_back(i);
	for(register int i=1;i<=k;++i)
	{	int a=read(),b=read();
		lg[num[a]].push_back(b);
		lg[num[b]].push_back(a);
		swap(num[a],num[b]);
	}
	for(register int i=1;i<=n;++i)
	{	int fx=find(i),fy=find(num[i]);
		if(fx!=fy)fa[fy]=fx;
	}
	for(register int i=1;i<=n;++i)
		for(register int j=0;j<lg[i].size();++j)
			answer[find(i)].insert(lg[i][j]);
	for(register int i=1;i<=n;++i)Print(answer[i].size());
	io::flush();
	return 0;
}
```


---

## 作者：aaki (赞：6)

这篇题解我们按照从50分为目标逐步优化收敛到100分。

由于交换是有先后顺序的,我们无法按照基本的搜索每一步来计算这道题.但是我们可以以k轮舞蹈为整体来作为分析的环节。

我们把奶牛编号为 $cow_1$ 到  $cow_n$。

位置编号为奶牛所在初始时 $cow_1$ 到  $cow_n$的编号。

# 50分思路:
 对于任意一头牛,经过k轮舞蹈之后会从一个点A经过一些点到一个落脚点B.由于只有n头奶牛.我们可以证明n 轮 k次舞蹈之后必然会有一个 $B_x$ 点出现在以前已经落脚过的 $B$ 点。
 
![](https://cdn.luogu.com.cn/upload/image_hosting/wub2tfpq.png)

之后的舞步就是在$B_x$ 点到$B_x$ 点之间循环,此次奶牛所有可以走到的点就是B 到B循环中所走过的点。

我们模拟这 n * k次操作,使用二维数组v记录 $cow_1$ 到  $cow_n$ 走过的点的数量, 行数表示奶牛的编号,列表示点是否走到过。

数组$now_x$表示编号为x的点现在奶牛的编号。

## 时间复杂度
O(n * k)

## 50分代码
```cpp
#include<iostream>
#include<vector>
using namespace std;
int v[2010][2010];
int a[200010],b[200010];
int n,k;
vector <int> ve[200010];
int now[200010];
int main(){
	cin >> n>>k;
	for(int i = 1;i<=n;i++)now[i] = i,v[i][i] = 1;
	for(int i = 1;i<=k;i++) cin >>a[i]>>b[i];
	for(int j = 1;j<=n;j++)
		for(int i = 1;i<=k;i++){
			swap(now[a[i]],now[b[i]]);
			v[now[a[i]]][a[i]] = 1;
			v[now[b[i]]][b[i]] = 1;
		}
	for(int i = 1;i<=n;i++){
		int t = 0;
		for(int j = 1;j<=n;j++){
			t+=v[i][j];
		}
		cout << t<<endl;
	}
	return 0;
}
```

# 从50到100

## 优化点1 

	由于n达到10w,记录数组v 从2维数组变为向量数组ve。
    
## 优化点2 

	只进行一轮k次舞蹈(而非之前的n轮),记录每头奶牛能够到达的点,最后一个点就是落脚点B。
    
## 优化点3	

	把n个点抽象成B1 到 Bx个落脚点,进行dfs操作(就是普通的记忆化搜索了).在bfs时把B点在k轮舞蹈能够到达的点全部进入集合dfs_v进行记录,集合中的数量就是bfs起点奶牛(或者说在多轮k次舞蹈之后能够到达该点的奶牛,他们共享答案,参见图中B1~B3)所能达到的点的数量。


## 100分代码:


```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int v[100010];
int dfs_v[100010];
int a[200010],b[200010];
int ans[100010];
int n,k,res;
vector <int> ve[100010];
int now[100010];
void dfs(int n1,int dfs_No){
	v[n1] = dfs_No;
	int tot = ve[n1].size();
	for(int i = 0;i<tot;i++){//这里不能使用i<ve[n1].size()会导致非常缓慢
		int num = ve[n1][i];
		if(dfs_v[num]==0) {
			dfs_v[num] = 1;
			res++;
		}
		if( !v[num]&& i==tot - 1) dfs(num,dfs_No);
	}
}
int main(){
	cin >> n>>k;
	for(int i = 1;i<=n;i++){
		now[i] = i;
		ve[i].push_back(i);
	}
	for(int i = 1;i<=k;i++){
		cin >>a[i]>>b[i];
      //这里ve记录k轮舞蹈之后奶牛所能到达的位置,最后一个就是落脚点B
		swap(now[a[i]],now[b[i]]);
		ve[now[a[i]]].push_back(a[i]);
		ve[now[b[i]]].push_back(b[i]);
	}
	int dfs_num = 0;
	for(int i = 1;i<=n;i++){
		if(!v[i]) {
        //一组环记录一次
			memset(dfs_v,0,sizeof(dfs_v));
			dfs_num ++ ;
			res = 0;
			dfs(i,dfs_num);
			ans[dfs_num] = res;			
		}
		
	}
	for(int i = 1;i<=n;i++){
		cout << ans[v[i]]<<endl;
	}
	return 0;
}
```


---

## 作者：Aiopr_2378 (赞：5)

# Solution [USACO21JAN] Dance Mooves S

这道题如果纯模拟，50分可以到手，但是想拿满分，就需要得出几个结论

我们不妨先以样例作参考，实践一下：

```
5 4
1 3
1 2
2 3
2 4
```

共有5只奶牛，4次**循环操作**，具体操作如下：

	第一项和第三项互换：1  2  3  4  5  ->  3  2  1  4  5

	第一项和第二项互换：3  2  1  4  5  ->  2  3  1  4  5

	第二项和第三项互换：2  3  1  4  5  ->  2  1  3  4  5

	第二项和第四项互换：2  1  3  4  5  ->  2  4  3  1  5

小伙伴们可以继续算下去，知道第$n*k$ 次互换后，数组为：

	1  2  3  4  5

与原数组相同，再多试几组数据，就会发现**每过** $n*k$ **次运算后，与原数组相同**

既然如此，操作会进行无数次，为循环类型出现。因此，**同一个点在不同循环节中经过的点是相同的**，然而每次循环后，会有许多路经相同的点，即：$A$从1走到2，$B$从3走到1，然后一定会走到2。因此，我们可以得出结论：经过$K$次操作后，一定会出现许多个环（路经相同的点们），当然，也可能有1个点组成的环。

### 根据以上说明，可以得出此题的特点：

1. 每经过$n*k$次操作，数组复原

1. 经过$k$次操作后，一定会出现许多个由路经相同的点组成的环，当然，也可能有1个点组成的环。

那我们怎样维护这个环呢

- 用a记录变化数组

- 用并查集记录形成的环

- 用vector记录每个点路过的点

- 用set记录答案（蒟蒻也是第一次用。。。）

详细解释在代码中体现：

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],fa[100005];
vector <int> v[100005];
set <int> ans[100005];
int find(int x){//并查集找父亲
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){//并查集和原数组重置
		fa[i]=i;
		a[i]=i;
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		swap(a[x],a[y]);//交换
		v[a[x]].push_back(y);//载入经过的点
		v[a[y]].push_back(x);
	}
	for(int i=1;i<=n;i++) v[a[i]].push_back(i);//载入改点的原点
	for(int i=1;i<=n;i++) fa[find(i)]=find(a[i]);//合并并查集
	for(int i=1;i<=n;i++){
		for(int j=0;j<v[a[i]].size();j++){
			ans[find(a[i])].insert(v[a[i]][j]);//用set载入a[i]的答案
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[find(i)].size()<<endl;//输出答案
	return 0;
}
```

在下蒟蒻，大佬勿喷

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经了解的题目意思

大家可以发现，每次进行$k$次操作，都会形成一次循环

首先，我们可以先求出进行第一次操作之后的数组

比如我们可以看一下样例：

进行操作前：

1 2 3 4 5

进行第一次操作后：

2 4 3 1 5

进行第二次操作后：

4 1 3 2 5

......

然后，我们可以发现，$1,2,4$会形成一个循环，$3$,$5$自己形成循环

然后我们发现，每一个点都会有一个即将到达的位置，每一个位置都有一个即将到达的点，这些点互不重复

所以，我们只有找出循环即可

最后，因为我们发现，一个点可能走到相同的点，所以直接用$STL$中的$set$维护即可

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
set<int> st[1000010];
int n,m;
struct node{
	int x,y;
}e[1000010];
int fa[1000010];
int num[1000010];
vector<int> vc[1000010];
inline int find(int x){
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
signed main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		fa[i]=i;
	for(register int i=1;i<=n;++i)
		num[i]=i;
	for(register int i=1;i<=m;++i)
		{
			e[i].x=read();
			e[i].y=read();
		}
	for(register int i=1;i<=n;++i)
		vc[i].push_back(i);
	for(register int i=1;i<=m;++i)
		{
			swap(num[e[i].x],num[e[i].y]);
			vc[num[e[i].x]].push_back(e[i].x);
			vc[num[e[i].y]].push_back(e[i].y);
		}
	for(register int i=1;i<=n;++i)
		{
			int fax;
			int fay;
			fax=find(i);
			fay=find(num[i]);
			fa[fax]=fay;
		}
	for(register int i=1;i<=n;++i)
		for(register int j=0;j<vc[i].size();++j)
			st[find(num[i])].insert(vc[i][j]);
	for(register int i=1;i<=n;++i)
		{
			write(st[find(i)].size());
			puts("");
		}
	return 0;
}

```


---

## 作者：Lonely_NewYear (赞：0)

# 洛谷 P7299 题解

赛时就这题没弄出来……~~果然我太菜了~~

## 题目分析

首先我们可以处理出经过一轮变化之后每头奶牛最后会到哪里（记为 $to_i$）和每头奶牛经过了哪些位置。注意记录位置时可以动态开内存（例如使用 vector），由于只有 $k$ 次交换，所以最多只会开 $2k+n$ 的内存。

这时我们再来看 $to_i$，可以把 $to$ 数组想象成一个图：当且仅当 $to_i=j$，有一条 $i$ 到 $j$ 的单向边。

每头奶牛最后只会到一个位置，所以图中每个点的出度为 $1$，最后每个位置只会有一头奶牛，所以图中每个点的入度为 $1$。那么这说明图中每个点都在一个环上。

我们考虑图中边的作用，如果有一条边 $i\to j$，那么说明奶牛 $i$ 第一轮循环会走到 $j$，那么在下一轮循环中奶牛 $i$ 就可以继续走遍奶牛 $j$ 可以走到的位置。

再看环上的点。由于环中下一个点能走到的位置上一个点也可以走到，所以这个环上每个点能走到的位置其实就是所有点能走到的位置，那么某个环上的所有点的答案都是一样的，可以统一处理。

具体看代码吧。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int now[100001],to[100001],cnt[100001],tot,ans[100001];
bool vis[100001];
vector<int> s[100001];//记录每头奶牛第一轮循环能走到的位置
queue<int> q;//记录这个环上的点
void dfs(int u)
{
	vis[u]=1;
	q.push(u);
	int len=s[u].size();
	for(int i=0;i<len;i++)
	{
		if(++cnt[s[u][i]]==1)//注意这样处理的话就不用每次都初始化数组了
		{
			tot++;
		}
	}
	if(!vis[to[u]])
	{
		dfs(to[u]);
	}
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		now[i]=i;
		s[i].push_back(i);
	}
	for(int i=1;i<=k;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		s[now[a]].push_back(b);//动态开内存
		s[now[b]].push_back(a);
		swap(now[a],now[b]);
	}
	for(int i=1;i<=n;i++)
	{
		to[now[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
			int res=tot;
			while(!q.empty())//遍历环上所有的点
			{
				int u=q.front();
				q.pop();
				ans[u]=res;
				int len=s[u].size();
				for(int j=0;j<len;j++)
				{
					if(--cnt[s[u][j]]==0)//注意这样处理的话就不用每次都初始化数组了
					{
						tot--;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

这里面最重要的优化我觉得就是这两段：

```cpp
for(int i=0;i<len;i++)
{
	if(++cnt[s[u][i]]==1)//注意这样处理的话就不用每次都清空数组了
	{
		tot++;
	}
}
```

```cpp
for(int j=0;j<len;j++)
{
	if(--cnt[s[u][j]]==0)//注意这样处理的话就不用每次都清空数组了
	{
		tot--;
	}
}
```

如果每次都清空数组的话，最多会有 $n$ 个环，清空数组会导致时间复杂度提高为 $O(n^2)$，只能拿到 $50pts$。

时间复杂度 $O(n+k)$。

谢谢观看！

---

