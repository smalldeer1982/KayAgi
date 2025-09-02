# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3```

### 输出

```
NO
NO```

# 题解

## 作者：fls233666 (赞：3)

想要检查每个城市的幸福指数是否合法，首先**要知道有多少人会经过这个城市**。根据每个城市居住的人数，我们可以先用一轮深度优先搜索求得答案。这段代码大概是这样的：

```cpp
void dfs1(int rp){   //计算编号为rp的城市会经过的人的数量
	for(rgt i=lst[rp];i;i=nxt[i]){   //遍历这个城市的出边
		if(!fw[to[i]]){   //找到没有被访问过的子节点
			fw[to[i]]=true;   
			dfs1(to[i]);   //访问子树
			p[rp]+=p[to[i]];   //累加结果
		}
	}
}
```

得到每个城市经过的人数后，我们开始进一步考虑什么情况下一个城市的幸福指数是错误的。

题目中有两条关键信息帮助我们：

- 一个城市的幸福指数=经过这个城市的好心情的人的数量-经过这个城市的坏心情的人的数量。
- 一个人的心情可以由好变坏，但不能由坏变好。

根据这两条信息，我们进一步归纳，发现一个城市如果符合如下条件之一则幸福指数是错误的。

我们设城市 $i$ 的幸福指数为 $h_i$，经过的人数量为 $p_i$，经过这个城市时心情好的人数量为 $hp_i$，则有如下规则：

1. 如果存在 $|h_i|>p_i$ 则幸福指数不合法（心情好或不好的人数超过了会经过这个城市的人数，不合法）；
2. 如果存在 $(p_i-|h_i|) \bmod 2 \neq 0$ 则幸福指数不合法（去掉了 $|h_i|$ 个人后，剩下的人一定是一半心情好一半心情不好，如果不能被 $2$ 整除，则不合法）；
3. 设城市 $i$ 的子树上的城市编号为 $j$，如果存在 $\sum\limits_{j \in son_i}hp_j > hp_i$，则幸福指数不合法（子树中高兴的人数比根节点的多，因为不高兴的人不会变高兴，所以不合法）；

如果树上的每个节点都不符合以上三条规则，则这组幸福指数是可能存在的。

我们可以再做一次深度优先搜索检查以上三条规则，代码如下：

```cpp
void ck(int rp){

	if(h[rp]>=0)
		hp[rp]+=h[rp];  //如果是高兴的人数多，记录高兴的人数
	else
		h[rp]=-h[rp];   //否则取绝对值
        
	if(h[rp]>p[rp]){   //检查第一条规则
		ans=false;
		return;
	}
    
	if((p[rp]-h[rp])%2){   //检查第二条规则
		ans=false;
		return;
	}else{
    
		hp[rp]+=(p[rp]-h[rp])/2;   //计算高兴的人数
		int s=0;
		for(rgt i=lst[rp];i;i=nxt[i]){
			if(!fw[to[i]]){   //向没有访问过的子树搜索
				fw[to[i]]=true;
				ck(to[i]);   
				if(!ans) return;  //如果子树不合法，则整个树必然不合法
				s+=hp[to[i]];   //累计子树中高兴的人数量
			}
		}
        
		if(hp[rp]-s<0){   //检查第三条规则
			ans=false;
			return;
		}
        
	}
}
```

到这里，这题代码的关键部分都写完了。下面就是把这些代码整理起来的事了，注意细节问题即可。

完整的代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
const int mxn = 1e5+5;
int lst[mxn],to[mxn*2],nxt[mxn*2],p[mxn],hp[mxn],h[mxn];
int n,m,tot;
bool ans,fw[mxn];
 
inline void add(int a,int b){  //树的加边函数
	tot++;
	to[tot]=b;
	nxt[tot]=lst[a];
	lst[a]=tot;
}
 
void dfs1(int rp){  //第一轮深度优先搜索
	for(rgt i=lst[rp];i;i=nxt[i]){
		if(!fw[to[i]]){
			fw[to[i]]=true;
			dfs1(to[i]);
			p[rp]+=p[to[i]];
		}
	}
}
 
void ck(int rp){   //第二轮深度优先搜索
	if(h[rp]>=0)
		hp[rp]+=h[rp];
	else
		h[rp]=-h[rp];
	if(h[rp]>p[rp]){
		ans=false;
		return;
	}
	if((p[rp]-h[rp])%2){
		ans=false;
		return;
	}else{
		hp[rp]+=(p[rp]-h[rp])/2;
		int s=0;
		for(rgt i=lst[rp];i;i=nxt[i]){
			if(!fw[to[i]]){
				fw[to[i]]=true;
				ck(to[i]);
				if(!ans) return;
				s+=hp[to[i]];
			}
		}
		if(hp[rp]-s<0){
			ans=false;
			return;
		}
	}
}
 
int main(){
	int test;
	scanf("%d",&test);
	while(test--){
		ans=true;
		scanf("%d%d",&n,&m);
        
		for(rgt i=1;i<=n;i++)
			scanf("%d",&p[i]);  //读入每个城市的居住人口
            
		for(rgt i=1;i<=n;i++)
			scanf("%d",&h[i]);  //读入预估的幸福指数
            
		memset(lst,0,sizeof(lst));
		tot=0;
		for(rgt x,y,i=1;i<n;i++){
			scanf("%d%d",&x,&y);  //读入树边，并加边
			add(x,y);
			add(y,x);
		}
        
		memset(fw,0,sizeof(fw));
		fw[1]=true;
		dfs1(1);   //从根节点开始第一轮搜索
        
		memset(fw,0,sizeof(fw));
		memset(hp,0,sizeof(hp));
		fw[1]=true;
		ck(1);   //开始第二轮搜索
        
		if(ans)   //根据结果判断幸福指数是否合法，并输出答案
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```


---

## 作者：两年打铁 (赞：2)

一开始看错了题目，我还以为每个人出发时都是开心的，直到经过一条边后才可以变。

首先因为每个人都是从起点开始出发的，我们把每个人的路径看成树上的一条条链，这满足树上差分的模型，所以我们可以处理出经过每个点的路径个数

处理出到每个点的人个数后我们开始考虑这个怎么做

因为是在边上变的心情，所以我们可以认为是在到达这个点的时候变的。

其次，我们可以算出这个点强制要求的坏心情人数

设当前点经过人数为$p_i$,坏心情人数为$al_i$，题目要求$h_i$

得到$al_i=\frac{p_i-h_i}{2}$，因为$al_i$要求是整数，可以判断是否合法。

继续往下做，已知子节点的$al_i$,那么父节点的$al_i$要尽量小，我们可以让人到子节点那边变坏，所以我们尽量让到父节点结束的人变坏，得到不合法的方案为

设到父节点结束的人为$now_i$,$sum$为子节点的$al_i$的和

即要满足$al[x]-now[x]<=sum$

到这里就做完了

注意多组数据

```cpp
#include<bits/stdc++.h>
#define huan putchar('\n')
#define kong putchar(' ')
using namespace std;

template <class T>
inline void read(T &x)
{
	x=0;register char ch=getchar();int pd=1;
	while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=pd;
}

template <class T>
void write(T x)
{
	if(x<0)x=-x,putchar('-');
	if(x<10)putchar(x+'0');
	else {write(x/10);putchar(x%10+'0');}
}

template <class T>
void wrl(T x)
{
	write(x);
	huan;
}

const int N=2e5+233;


int n,p[N],h[N],al[N],m,hh[N],now[N];
int t;
bool flag;
struct dd
{
	int end,nt;
}e[N<<1];

inline void add(int begin,int end)
{
	++t;
	e[t].end=end;
	e[t].nt=h[begin];
	h[begin]=t;
}

void dfs(int x,int fa)
{
	if(!flag)return;
	int sum=0;
	for(register int i=h[x];i;i=e[i].nt)
	{
		int u=e[i].end;
		if(u==fa)continue;
		dfs(u,x);
		p[x]+=p[u];
		sum+=al[u];
	}
	if(p[x]-hh[x]<0||((p[x]-hh[x])&1))
	{
		flag=false;
		return;
	}
	al[x]=(p[x]-hh[x])/2;
	if(al[x]-now[x]>sum)
	{
		flag=false;
		return;
	}
}

int main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n);
		read(m);
		flag=1;
		t=0;
		for(register int i=1;i<=n;++i)
		{
			al[i]=0;
			h[i]=0;
			read(now[i]);
			p[i]=now[i];
		}
		
		for(register int i=1;i<=n;++i)
		{
			read(hh[i]);
		}
		int x,y;
		for(register int i=1;i<n;++i)
		{
			read(x);
			read(y);
			add(x,y);
			add(y,x);
		}
		dfs(1,0);
		flag?puts("YES"):puts("NO");
	}
	return 0;
}

```


---

## 作者：F_Mu (赞：2)

**题意**

给一棵$n$节点的树，每个节点有$a[i]$个人住，他们从$1$号节点回家，回家路上可能从开心的状态变成不开心的状态（但不可以由不开心变为开心），每个节点有个探测器，会探测经过该节点开心的人数减不开心的人数，而预期值为$h[i]$，问是否可能存在一种情况，使得所有节点的探测值等于真实值

**分析**

先想一下思路：我们可以发现叶子节点的开心人数和不开心人数，开心人数一定是从$1$号节点一直开心走回家的，不开心的人可能在路中间是开心的，那么我们不妨将题目转换为每个人从家出发到$1$号节点，他可能一开始是不开心的，他可以从不开心变为开心，但不会从开心变为不开心，那么对于一个节点，统计它的儿子节点的开心人数和不开心人数，然后不妨设该节点的所有人都是不开心，设$x$为开心的人数，$y$为不开心的人数，$tot$为经过该节点的总人数那么有方程
$$
x+y=tot
$$
$$
x-y=h[i]
$$
然后判断即可

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
 
#include <bits/stdc++.h>
 
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define repd(z, x, y) for(int z=x;z>=y;--z)
#define com bool operator<(const node &b)const
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
vector<int> v[maxn];
int a[maxn];
int h[maxn];
bool flag;
 
pii dfs(int now, int pre) {
    if (!flag)
        return {0, 0};
    pii p = {0, a[now]};
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        pii tmp = dfs(to, now);
        p.first += tmp.first;
        p.second += tmp.second;
    }
    int x = p.first + p.second + h[now];
    if (x & 1) {
        flag = false;
        return {0, 0};
    }
    x /= 2;
    if (x < p.first || x > p.first + p.second) {
        flag = false;
        return {0, 0};
    }
    return pii{x, p.first + p.second - x};
}
 
void solve() {
    int n, m;
    cin >> n >> m;
    rep(i, 1, n) {
        cin >> a[i];
        v[i].clear();
    }
    rep(i, 1, n)cin >> h[i];
    rep(i, 1, n - 1) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    flag = true;
    dfs(1, 0);
    if (flag)
        cout << "YES\n";
    else
        cout << "NO\n";
}
 
signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：Isshiki_Hugh (赞：1)

两遍dfs即可

第一次dfs通过回溯计算子树权值和`val[i]`，也就是通过这个节点的人数

有了这个`val[i]`以后，我们可以借助`h[i]`计算每一个节点的高兴人数和悲伤人数

计算公式：

$num\_happy = \frac{(val[now] + h[i])}{2}$

$num\_sad = \frac{(val[now]-h[i])}{2}$

但是需要注意，我们在除以二之前，要判断一下是否是偶数，如果不是偶数显然不合法。

除此之外，我们还需要判断高兴的人数和不高兴的人数是否存在负数，如果存在负数显然也是不合理的。

你以为结束了嘛？还没有呢！

你还需要维护一个东西叫亲儿子的高兴人数权值和。目的是判断儿子里的高兴人数总和是不是大于父亲的高兴人数总和，大于了肯定也是不合法的。回溯实现。


### AC代码
```cpp
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for(register int i = (a);i <= (b);++i)
#define per(i,a,b) for(register int i = (a);i >= (b);--i)  
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

const int N = 1e5+5;
int _,n,m,p[N],h[N],u,v;
int next[2*N],head[2*N],ver[2*N],tot,val[N],back[N];

inline void link(int x,int y){ver[++tot] = y , next[tot] = head[x] , head[x] = tot;}

inline void dfs(int now,int father){
	val[now] = p[now];
	for(int i = head[now];i;i = next[i]){
		if(ver[i] == father) continue;
		dfs(ver[i],now);
		val[now] += val[ ver[i] ];
	}
}

inline bool check(int now,int father,int num_H){
		// cout << "\n now in " << now << " ";
	bool flag = true;
	int num_happy,num_unhappy,num_now = val[now];
	num_now -= h[now];
		// cout << num_now << " ";
	if(num_now % 2 || num_now < 0) return false;
	else num_now /= 2;
	num_happy = num_now + h[now] , num_unhappy = num_now;
	back[father] += num_happy;
		// cout << num_now << " ";
		// cout << num_happy << " " << num_unhappy << " " << num_H << " ";
	if(num_happy > num_H || num_happy < 0 || num_unhappy < 0) return false;
	for(int i = head[now];i;i = next[i]){
		if(ver[i] == father) continue;
		flag &= check(ver[i],now,num_happy);
		if(!flag) return false;
	}
	if(back[now] > num_happy) return false;
	return true;
}

inline void reset(){
	rep(i,1,tot) head[i] = next[i] = ver[i] = 0;
	tot = 0;
	return;
}

int main(){
	std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	//freopen("in.in", "r", stdin);
	cin >> _;
	while(_--){
		reset();
		cin >> n >> m;
		rep(i,1,n) val[i] = back[i] = 0;
		rep(i,1,n) cin >> p[i];
		rep(i,1,n) cin >> h[i];
		rep(i,1,n-1){
			cin >> u >> v;
			link(u,v) , link(v,u);
		}
		dfs(1,0);
		if(check(1,0,m)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
#### }
```

---

## 作者：PanH (赞：1)

## 题意
给出一棵 $n$ 个节点根为 $1$ 的树。还有 $m$ 个人，每个人都从 $1$ 出发走最短路回家。其中有些人是快乐的，有些人不快乐，在路上可以改变一些人从快乐变为不快乐，但不快乐并不能变成快乐。

每个点都有一个 $h$ 值，表示走到这个点的人快乐的要比不快乐的多 $h$ 人。

你需要判断能否构造出一种方案符合题意。

（这题意真诡异，建议配合样例理解）

## 题解
由于知道了到这个点的总人数，和这个点的 $h$ 值，显然这个点的快乐的人的人数是可以直接算出来的。

另外，当前点快乐的人数要不小于其所有儿子节点的快乐人数之和。再判一下快乐人数是否超过这个点的总人数，或是是否是负数。

code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
void MEM(int *a,int n)	{for(int i=0;i<=n;i++)	a[i]=0;}
const int N=2e5+5;
struct edge{
	int next,to;
}e[N<<1];
int head[N],cnt,n,m,p[N],h[N],num[N],happy[N],flag;
void add(int u,int v)
{
	e[++cnt]={head[u],v};
	head[u]=cnt;
}
void dfs1(int x,int fa)
{
	num[x]=p[x];
	for(int i=head[x];i;i=e[i].next)
		if(e[i].to!=fa)	dfs1(e[i].to,x),num[x]+=num[e[i].to];
}
void dfs2(int x,int fa)
{
	int sum=0;
	for(int i=head[x];i;i=e[i].next)
		if(flag&&e[i].to!=fa)
			dfs2(e[i].to,x),sum+=happy[e[i].to];
	if(sum>happy[x]&&flag)
	{
		puts("NO"),flag=0;
		return;
	}
}
signed main()
{
	int T;read(T);
	while(T--)
	{
		flag=1;
		read(n),read(m);
		MEM(head,n),cnt=0;
		for(int i=1;i<=n;i++)	read(p[i]);
		for(int i=1;i<=n;i++)	read(h[i]);
		for(int i=1,u,v;i<n;i++)	read(u),read(v),add(u,v),add(v,u);
		dfs1(1,0);
		for(int i=1;i<=n;i++)
			if((num[i]+h[i])&1)
			{
				puts("NO"),flag=0;
				break;
			}
			else
			{
				happy[i]=(num[i]+h[i])/2;
				if(happy[i]>num[i]||happy[i]<0)
				{
					puts("NO"),flag=0;
					break;
				}
			}
		if(!flag)	continue;
		dfs2(1,0);
		if(!flag)	continue;
		puts("YES");
	}
}
```


---

## 作者：KSToki (赞：0)

题意巨佬们都解释的很清楚啦，这里分享一下蒟蒻的做法。

这道题只让我们判断它给出的结果是否正确，判断正确不太好想~~可能是我太蒻了~~，那我们考虑哪些情况下会输出NO。

首先我们需要求出经过每个点的人数，记为$siz[i]$，那么通过分类讨论$h[i]$的正负可以求出经过该点时高兴的人数$up[i]$和不高兴的人数$down[i]$。此时我们可以明显的发现两种错误：

情况1：$siz[i]<|h[i]|$，人数都不够。

情况2：$siz[i]$与$h[i]$奇偶性不同，你不可能把人分成两半，也没有人即高兴又不高兴。

题目中专门强调了高兴可以变成不高兴，而不高兴不能转化为高兴，那么对于每个节点，其所有子节点的$down$之和一定大于等于该节点的$down$（或者$up$之和一定小于等于该节点的$up$）。

这里我们将所有错误的情况都考虑完了，除此之外的情况便都是YES了。提交一遍AC~。

代码~：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,p[100001],h[100001],x,y,head[100001],to[200001],nxt[200001],tot,siz[100001],up[100001],down[100001];
bool f;
inline void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs1(int x,int fa)//第一遍dfs，求出siz，即会经过改点的人数
{
	siz[x]=p[x];
	for(register int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa)
		    continue;
		dfs1(y,x);
		siz[x]+=siz[y];
	}
}
void dfs2(int x,int fa)//第二遍dfs，求解
{
	if(h[x]>0)//分类讨论嘛
	{
		if(siz[x]<h[x]||((siz[x]-h[x])&1))
		{
			f=0;
			return;
		}//情况1、2
		else
		{
			down[x]=(siz[x]-h[x])>>1;
			up[x]=siz[x]-down[x];
		}
	}
	else
	{
		if(siz[x]<-h[x]||((siz[x]+h[x])&1))
		{
			f=0;
			return;
		}
		else
		{
			up[x]=(siz[x]+h[x])>>1;
			down[x]=siz[x]-up[x];
		}
	}
	int ups=0,downs=0;
	for(register int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa)
		    continue;
		dfs2(y,x);
		ups+=up[y];
		downs+=down[y];
	}
	if((ups!=0||downs!=0)&&(ups-p[x]>up[x]||downs+p[x]<down[x]))
	    f=0;//情况3
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(head,0,sizeof(head));//记得清零
		tot=0;
		scanf("%d%d",&n,&m);
		for(register int i=1;i<=n;++i)
		    scanf("%d",&p[i]);
		for(register int i=1;i<=n;++i)
		    scanf("%d",&h[i]);
		for(register int i=1;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		memset(siz,0,sizeof(siz));//记得清零
		f=1;
		dfs1(1,0);
		dfs2(1,0);
		if(f)
		    printf("YES\n");
		else
		    printf("NO\n");
	}
	return 0;
}

```


---

## 作者：Zechariah (赞：0)

# 题意
首先读懂题，有m个人从1城市出发回到自己居住的城市，这些人出发时候心情好坏的人数不确定，然后每个人都可能会在路上从心情好变成心情坏（不存在心情坏变成心情好）。现在告诉你已知计算出的经过每个城市的人心情好人数-心情坏人数，也就是h[i]（不一定正确），以及每个城市居住的人数p[i]，问这样的h数组可不可能成立。

# 解法
设某一处心情好的人数为good，心情差的人数为bad，那么很显然有good + bad = 总人数，good - bad = h[i]，那么就可以得到good = (总人数+h[i])/2。另外很容易得知，abs(h[i])>总人数是不可能的，并且abs(h[i])与总人数的奇偶必然相同（总人数一定时abs(h[i])奇偶性是一定的且与总人数的奇偶性相同）。于是就有这样的解法：首先处理1这个点，这个点的good可以算出，直接按上面的规则判断h[1]是否成立。然后从1开始dfs，对于每一个点，他的所有孩子节点的good和bad都是确定的，而其中的bad有可能是从该节点离开时变坏的，所以把孩子节点中的bad和该节点的人数合在一起，这些人都是既可能是good也可能是bad，这些人对应的h则是h[i]-孩子中所有的good数。然后判定的规则与上面相同。最后比较dfs出来经过1的孩子的good总数与1处good数大小。

# AC代码

```cpp
#include <bits/stdc++.h>
#define jh(x, y) x ^= y ^= y ^= x
#define lowbit(x) (x & -x)
#define loc(x, y) (x = 1) * m + y
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll nt[N], b[N], p[N], num, pp[N], h[N], gd[N], good;
bool flag = true;
void add(int x, int y) {
	b[++num] = y, nt[num] = p[x], p[x] = num;
	b[++num] = x, nt[num] = p[y], p[y] = num;
}
void dfs(int x, int fa) {
	ll sum = 0;
	for (int e = p[x]; e; e = nt[e]) {
		int k = b[e];
		if (k == fa)continue;
		dfs(k, x);
		if (!flag)return;
		sum += h[k];
	}
	if (x == 1)return;
	int tg;
	int tp = gd[x] - sum + pp[x], th = h[x] - gd[x];
	if (abs(th) > tp || (abs(th) & 1) != (tp & 1))flag = false;
	tg = (tp + th) / 2;
	gd[fa] += tg + gd[x];
}

int main() {
	rg int T = fast_IO::read();
	while (T--) {
		rg int n = fast_IO::read(), m = fast_IO::read(); num = 0; flag = true; good = 0;
		for (rg int i = 1; i <= n; ++i)pp[i] = fast_IO::read(), p[i] = 0, gd[i] = 0;
		for (rg int i = 1; i <= n; ++i)h[i] = fast_IO::read();
		for (rg int i = 1; i < n; ++i)add(fast_IO::read(), fast_IO::read());
		if (abs(h[1]) > m || (abs(h[1]) & 1) != (m & 1)) {
			puts("NO");
			continue;
		}
		good = (m + h[1]) / 2;
		dfs(1, 0);
		if (gd[1] > good)flag = false;
		if (flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 前言
安利自己首场 CF 的[游记](https://www.luogu.com.cn/blog/PsephurusGladius-zdx/codeforces-round-660-div-2-post)（其实啥也没写）。

## 题目分析
考场上一开始拿到这道题的时候是蒙的……做了 D 题之后回来猛然发现一个事实：知道人数和好坏情绪人数之差时，是可以直接算出坏情绪人数的。具体一点，由于 $good_i+bad_i=people_i,good_i-bad_i=h_i$，可以算出 $bad_i=(people_i-h_i)/2$。  

我们既然算出了走到每个结点的坏情绪人数，这道题实际上已经解决了。根据题目描述，没有人的情绪会由坏变好，而人行走的路线是由根向下，那么一个结点的坏情绪人数一定不会大于其子结点坏情绪人数之和加上当前结点居住的人数。判断这一条件是否满足，同时判断 $bad_i$ 是否是非负整数即可完成此题。

## 代码
```cpp
#include<cstdio>
using namespace std;
int T,n,m,x,y,tot,p[200001],h[200001],head[200001],go[400001],suc[400001],down[200001];
bool check;
inline void add_edge(int x,int y)
{
	go[++tot]=y;
	suc[tot]=head[x];
	head[x]=tot;
	return;
}
void dfs(int now,int father)
{
	int sum=0,q=p[now];
	for(int i=head[now];i;i=suc[i])
		if(go[i]!=father)
		{
			dfs(go[i],now);
			sum+=down[go[i]];
			p[now]+=p[go[i]];
		}
	int t=p[now]-h[now];
	down[now]=t>>1;
	if((t&1)||t<0||sum+q<down[now])
		check=false;
	return;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		check=true;
		tot=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%d",&p[i]);
		for(int i=1;i<=n;++i)
			scanf("%d",&h[i]);
		for(int i=1;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			add_edge(x,y);
			add_edge(y,x);
		}
		dfs(1,0);
		for(int i=1;i<=n;++i)
			down[i]=head[i]=0;
		puts(check?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

思路： 通过预处理出**走到**各个点的坏蛋有多少，搜到当前点记录当前点至少有多少坏蛋，贪心分配坏蛋，如果有多出来的坏蛋则为无解。

贪心思路: 当前点能存多少坏蛋就全存，儿子需要多少坏蛋就分配多少坏蛋。这样就是尽可能地多往外分配坏蛋，不够没有关系，可以让好人变成坏蛋，但是如果多了就说明无解。

观察几个良心的样例加几个特判就可以了

[$\mathcal{Code}$](https://codeforces.com/contest/1388/submission/88505098)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read()
{
	int r=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
int cnt,head[1000010];
struct node {
	int to,next;
}e[2000010];
void add()
{
	int xx=read(),yy=read();
	e[++cnt].to=yy;
	e[cnt].next=head[xx];
	head[xx]=cnt;
	e[++cnt].to=xx;
	e[cnt].next=head[yy];
	head[yy]=cnt;
}
int T,n,m;
int p[1000010],h[1000010],siz[1000010];
bool f=1;
void dfs(int now,int fa,int badsum)
{
	if((siz[now]+h[now])%2) f=0;
	if(badsum>=p[now]) badsum-=p[now];
	else badsum=0;
	for(int i=head[now];i;i=e[i].next) {
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,now,siz[v]-(siz[v]+h[v])/2);
		badsum-=siz[v]-(siz[v]+h[v])/2;
	}
	if(badsum>0) f=0;
}
void dfs1(int now,int fa)
{
	siz[now]=p[now];
	for(int i=head[now];i;i=e[i].next) {
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,now);
		siz[now]+=siz[v];
	}
}
int main()
{
	scanf("%d",&T);
	while(T--) {
		for(int i=1;i<=cnt;i++)
			e[i].next=e[i].to=0;
		cnt=0;
		f=1;
		n=read();m=read();
		for(int i=1;i<=n;i++)
			p[i]=read(),head[i]=0;
		for(int i=1;i<=n;i++)
			h[i]=read();
		for(int i=1;i<n;i++)
			add();
		dfs1(1,-1); 
		dfs(1,-1,siz[1]-(siz[1]+h[1])/2);
		for(int i=1;i<=n;i++)
			if(siz[i]<h[i])
				f=0;
		if(f) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：MyukiyoMekya (赞：0)

> 一个人一旦变得伤心就不会再开心起来

所以我们反向考虑，我们从叶子结点一个一个向上合并，这样就变成了一个人一开始可以是伤心或开心，但是走到1 号点的过程中如果变得开心后就不会再伤心。显然有一个贪心，要尽可能让更多的人伤心。然后每次合并完每个儿子的子树最多能让多少人保持伤心，然后再结合当前节点的 $h$ 判断在这个节点要让多少人变的开心。然后就一边合并一边判断就行。

注意有些细节比如人数不够啥的。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
using namespace std;
const int MaxN=200050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],en,n,m;
int p[MaxN],h[MaxN],siz[MaxN];
bool flg;
inline void adde(int u,int v)
{
	++en;
	E[en]=(Edge){hd[u],v};
	hd[u]=en;
	return;
}
inline int dfs(int u,int fa)
{
	if(!flg)
		return 0;
	siz[u]=p[u];
	reg int happy=0;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		happy+=dfs(v,u);
		siz[u]+=siz[v];
	}
	reg int now=happy-(siz[u]-happy);
	if(now>h[u])
	{
		flg=false;
//		printf("failed in %d\n",u);
		return 0;
	}
	if(now<h[u])
	{
		if((h[u]-now)&1)
		{
			flg=false;
//			printf("died in %d\n",u);
//			printf("siz %d happy %d now %d h[u]-now = %d\n",siz[u],happy,now,h[u]-now);
			return 0;
		}
		happy+=(h[u]-now)/2;
		if(happy>siz[u])
		{
			flg=false;
			return 0;
		}
	}
	return happy;
}
inline void work()
{
	read(n);read(m);
	fill(hd,hd+n*2+5,-1);en=0;
	for(int i=1;i<=n;++i)
		read(p[i]);
	for(int i=1;i<=n;++i)
		read(h[i]);
	reg int u,v;
	for(int i=1;i<n;++i)
	{
		read(u);read(v);
		adde(u,v);
		adde(v,u);
	}
	flg=true;
	dfs(1,0);
	puts(flg?"YES":"NO");
	return;
}
signed main(void)
{
	int t;cin>>t;
	while(t--)
		work();
	return 0;
}
```

---

