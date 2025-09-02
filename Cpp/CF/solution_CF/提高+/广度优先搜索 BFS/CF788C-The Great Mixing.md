# The Great Mixing

## 题目描述

Sasha 和 Kolya 决定再次用可乐把自己灌醉。这次他们有 $k$ 种可乐，第 $i$ 种的可乐二氧化碳浓度为 $\frac{a_i}{1000}$。今天，在温哥华 Sergiy 的派对上，他们决定调一杯二氧化碳浓度为 $\frac{n}{1000}$ 的可乐。饮料必须美味，因此每种可乐类型在杯中只能加入整数升（某些类型可以不加入）。此外，他们希望杯中的可乐总体积最小。

二氧化碳浓度的定义是可乐中二氧化碳的体积除以可乐的总体积。当混合两种可乐时，二氧化碳的总体积相加，可乐的总体积也相加。

请帮助他们找到制备二氧化碳浓度为 $\frac{n}{1000}$ 的可乐所需的最小自然数升数。假设朋友们每种可乐类型的供应是无限的。

## 说明/提示

在第一个示例中，我们可以通过混合 1 升 $\frac{300}{1000}$ 和 1 升 $\frac{500}{1000}$ 的可乐来达到浓度 $\frac{400}{1000}$：$\frac{300+500}{1000+1000} = \frac{400}{1000}$。

在第二个示例中，我们可以通过混合 2 升 $\frac{25}{1000}$ 和 1 升 $\frac{100}{1000}$ 的可乐来达到浓度 $\frac{50}{1000}$：$\frac{25+25+100}{3 \cdot 1000} = \frac{50}{1000}$。

## 样例 #1

### 输入

```
400 4
100 300 450 500
```

### 输出

```
2
```

## 样例 #2

### 输入

```
50 2
100 25
```

### 输出

```
3
```

# 题解

## 作者：Dragon_in_Bed (赞：7)

这篇的题解真的没有写到点子上的...

我解释一下为什么在做$\text{BFS}$的时候只要考虑$[-1000,1000]$范围内的节点，即使过程中可能出现不在这个范围之内的浓度和。

考虑最终选取的饮料，浓度为$a_1+a_2+...+a_m=0$。问题出在可能存在$a_1+a_2+...+a_k(k<m)\notin[-1000,1000]$。但是由于$a_i\in[0,1000]$，我们可以通过调整最终选取的饮料顺序，使得对于任意$a_1+a_2+...+a_{k-1}\leq0$，我们选取$a_k>0$作为第$k$个饮料；否则选取$a_k\leq0$。这样，就说明即使无视$[-1000,1000]$范围外的节点，依然可以找出一个满足条件的等价答案。

---

## 作者：Piwry (赞：7)

## 解析
可以发现，题目大概就是要求取一些数，使得它们的**平均数**为 $n$。

可以想到平时我们若想验证一些数的平均数是否为 $x$，通常都是将它们分别**减去** $x$（也可以说是贡献），并验证和是否为 $0$。这

于是题目就转化为从取最少的（不是种类最少），**可重复**的给定数字，要求其和为 $0$。

表面上看各种数字的组合情况非常多，难以求解。但可以想象我们取数字实际上是**一个一个**取的，即每次将一个**初始存在的**数字加入已取的数字集合，并**相加其贡献**。

因此我们每次仅取一个数字，就可以保证**第一次到达某个数字就是最优的**。枚举一轮数字是 $O(n)$ 的；由于每个数字仅会用来拓张一次，总复杂度是 $O(n^2)$ 的（注意实际上 $n$ 的有效最大范围是 $1000$）

## CODE

`+1000` 是为了调整数组下标，避免负下标越界。

```cpp
#include <cstdio>
#include <queue>
using std::queue;

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int cnt[2050], dist[2050];
queue<int> q;

int main(){
	int P =read(), n =read();
	for(int i =0; i < n; ++i) ++cnt[read()-P+1000];
	for(int i =1000-P; i <= 1000-P+1000; ++i) dist[i] =0x3f3f3f3f;
	for(int i =1000-P; i <= 1000-P+1000; ++i) if(cnt[i]) dist[i] =1, q.push(i);
	while(q.size()){
		int nw =q.front(); q.pop();
		for(int i =0; i <= 1000; ++i){
			int net =nw+i-P;
			/*仅拓张初始存在，并且得数数字未被遍历过的数字*/
			if(dist[i-P+1000] != 1 || dist[net] != 0x3f3f3f3f) continue;
			dist[net] =dist[nw]+1;
			q.push(net);
		}
	}
	if(dist[1000] != 0x3f3f3f3f) printf("%d", dist[1000]);
	else puts("-1");
}
```

---

## 作者：_edge_ (赞：6)

觉得不难，$2300$ 虚高？

首先理清楚题意，原题意稍微有点神奇，事实上应该是找若干个 $\dfrac{a_i}{1000}$ 使得他们加起来是 $\dfrac{n}{1000}$。

然后他可以重复选择同一个 $a_i$。

也就是说，相当于是他们几个的平均数要等于 $n$。

现在问题变成了选取最少的数使得他们的平均数是 $n$。

非常愚蠢的一种做法就是去枚举这个个数，会发现这个复杂度是爆炸的。

当然有一种有趣的 trick 是把 $a_i$ 都减去 $n$，然后就变成了他们的总和要是 $0$。

现在问题变成了给若干个数，然后选出最少的数使得总和变成 $0$。

然后这东西 $k \le 10^6$，挺难背包的，但是仔细思考值域，发现本质不同的一共就 $1000$ 个。

也就是说，现在有 $1000$ 个数，然后选出最少的数使得他们变成 $0$。

背包？但是上下界怎么确定？

粗略估计一下的话，应该就在 $10^6$ 以内，我开了个 $5 \times 10^5$ 就过了。

具体的，可以思考它的最劣情况是 $500$ 和 $499$，不会超过这个界。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int INF=4e6+5;
int f[INF],N,n,k,a[INF],sum;
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for (int i=1;i<=k;i++) cin>>a[i];
	for (int i=1;i<=k;i++) a[i]-=n;
	sort(a+1,a+1+k);
	int m=unique(a+1,a+1+k)-a-1;
	N=2e6;sum=5e5;
	for (int i=1;i<=m;i++) {
		f[N+a[i]]=1;
		if (a[i]<0) { 
			for (int j=sum;j>=-sum;j--) {
				f[j+N]=min(f[j+N],f[j+N-a[i]]+1);
			}
		}
		else {
			for (int j=-sum;j<=sum;j++)
				f[j+N]=min(f[j+N],f[j+N-a[i]]+1);
		}
	}
	if (f[N]>1e9) cout<<"-1\n";
	else cout<<f[N]<<"\n";
	return 0;
}
```


---

## 作者：斯茂 (赞：4)

非常有意思的一道题

首先我们看到k是1e6，而n是1e3，所以k的规模也可以缩到1e3

浓度由于要涉及到除法，是个很难处理的东西

但考虑到分母是固定的

如果用x瓶饮料凑出了n/1000的浓度，则他们的ai的平均值一定是n

我们可以把ai变成ai-1000（这个数叫做权值），这样就变成了选取最少的饮料数目，使得和为0

然后就有多种方法了

我用的是bfs（因为好写）

将已有浓度饮料的权值的dis设为1（其他设为inf），然后把他们塞进队列。

每次取队头，把他加上所有可能的饮料的情况都枚举一遍。

若有新扩展的点，加入队列。

就这样，复杂度O(n^2)

```
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
int d[2005];
queue <int> q;
int main()
{
    int n, k, i, a;
    scanf("%d %d", &n, &k);
    for(i = 0; i <= 2000; i++)
      d[i] = 999999;
    for(i = 1; i <= k; i++)
    {
      scanf("%d", &a);
      d[a - n + 1000] = 1;
	}
	for(i = 0; i <= 2000; i++)
	  if(d[i] == 1)
	    q.push(i);
	while(q.size())
	{
	  a = q.front();
	  q.pop();
	  for(i = 0; i <= 2000; i++)
	    if(d[i] == 1 && d[a + i - 1000] == 999999)
	    {
	      q.push(a + i - 1000);
	      d[a + i - 1000] = d[a] + 1;
		}
	}
	if(d[1000] == 999999)
	  cout << -1 << endl;
	else
	  cout << d[1000] << endl;
	return 0;
}
```


---

## 作者：YLWang (赞：3)

不理解为什么出题人要把 $k$ 出成 $10^6$。

首先容易套路地把 $a_i \leftarrow a_i-m$。这样问题就变成了选一些数使他们的和为 $0$。

那么发现这是一个完全背包问题。但是值域过大无法保存。

再发现其实因为每个转移都一样，所以只用考虑 $[-1000, 1000]$ 之间的值。

然后就做完了。

有个 Bonus 就是把这个完全背包换成 01 背包。

发现这个时候不能只考虑 $[-1000, 1000]$ 的值了。如果先是和大于 $1000$ 的两个正数就直接 GG 了。

这时候我们可以采用 random_shuffle。可以证明最终只要考虑$[-\sqrt{1000} \cdot 1000, \sqrt{1000} \cdot 1000]$ 之间的数，错误概率在 $10^{-7}$ 左右。

证明非常繁杂。不需要会。记住优美的结论就行。

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
有 $k$ 种可乐，第 $i$ 瓶可乐的 CO2 浓度是 $\frac{a_i}{1000}$，问要配置出浓度 $\frac{n}{1000}$ 的可乐，最少需要几瓶可乐.  
无解输出 $-1$.  
$0\le n\le 1000,k\le10^6$.
## $\text{Solution}$
不难想到把所以值减 $n$ 然后转化为加和为 $0$ 的问题.  
我的做法是正负两边暴力背包，值域在最差的情况下是 $500\times499$.  
然后就 $3\times 10^5$ 艹过去了...  

现在讲讲 $n^2$ 的正解.  
考虑 **bfs**.  
从 $0$ 开始，向外寻找.  
把边界设为 $1000$ 即可.  
为什么这么是对的？
设答案的组合为 $x_1+x_2+...+x_k=0$.  
不难发现，通过调整前后顺序，一定可以使序列 $x$ 的任意一个前缀和的绝对值均不超过 $1000$，那么这个调整后的序列就可以被 bfs 搜到.  
因此这样做是正确的.
## $\text{Code}$
~~代码还是之前的暴力背包~~  
~~bfs 不难实现，留给读者自行思考~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e6+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,k;
int a[1050],b[1050],x,y;
int o=3e5;
int w[N];
int f1[300050],f2[300050];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  for(int i=1;i<=k;i++) w[i]=read();
  sort(w+1,w+1+k);
  k=unique(w+1,w+1+k)-w-1;
  for(int i=1;i<=k;i++){
    w[i]-=n;
    if(w[i]==0){
      printf("1");return 0;
    }
    else if(w[i]>0) a[++x]=w[i];
    else b[++y]=-w[i];
  }
  if(!x||!y){
    printf("-1");return 0;
  }
  memset(f1,0x3f,sizeof(f1));
  f1[0]=0;
  for(int i=1;i<=x;i++){
    int w=a[i];
    for(int j=w;j<=o;j++) f1[j]=min(f1[j],f1[j-w]+1);
  }
  memset(f2,0x3f,sizeof(f2));
  f2[0]=0;
  for(int i=1;i<=y;i++){
    int w=b[i];
    for(int j=w;j<=o;j++) f2[j]=min(f2[j],f2[j-w]+1);
  }
  int ans=2e9;
  for(int i=1;i<=o;i++) ans=min(ans,f1[i]+f2[i]);
  printf("%d\n",ans);
  return 0;
}
/*

*/

```


---

## 作者：USTC_Ming (赞：1)

校内大佬讲的题，我来水题解。

~~他没有博客啊，怪怪怪，significant~~

用bfs做掉这道题，其实很简单

鉴于分母固定，得a[i]的权值

权值是用n-a[i]

为满足题意要使1000对应的权值和为0

但这时可能权值小于0，于是都加上1000

然后bfs

最后要得到a[1000]的值

代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<cstdlib>
using namespace std;

inline int read(){
	int s=0;bool flag=true;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=false;ch=getchar();}
	while(isdigit(ch)){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return flag?s:-s;
}

inline void write(int x){
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}

inline void print(int x){write(x),puts("");}

int a[2001];
queue<int> q;

signed main(void){
	memset(a,0x3f3f3f,sizeof(a));
	int n=read(),m=read();
	for(int i=1;i<=m;i++)	a[read()-n+1000]=1;
	for(int i=0;i<=2000;i++)
		if(a[i]==1)	q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<=2000;i++)
			if(a[i]==1 && a[u+i-1000]==1061109567){
				q.push(u+i-1000);
				a[u+i-1000]=a[u]+1;
			}
	}
	if(a[1000]==1061109567)	puts("-1");
	else	cout<<a[1000]<<endl;
	return 0;
}
```


---

## 作者：__vector__ (赞：0)

我不理解为什么题解区所有做法都需要枚举 $[-1000,1000]$。  

我实际测试，$[0,1000]$ 就足够了。      

这篇题解将主要说明为什么 $[0,1000]$ 足够。  
### 做法  
首先，令 $b_i = a_i -n$，那么题目显然可以转化为，选择 $k \gt 0$ 个下标 $p_1,p_2,\cdots,p_k$，使得 $\sum\limits_{i=1}^k b_{p_i} = 0$。  

令 $dis_i$ 表示总和为 $i$ 需要选择的最少下标数量，那么，可以通过 bfs 来进行转移。  

但是，可能的总和范围在 $[-10^6,10^6]$ 之间，也就是说有 $2\times 10^6$ 个编号在 $[-10^6,10^6]$ 的点。  

而每个点最多有 $10^3$ 个连接的点，肯定爆炸了。  

但是，事实上，只有编号 $[0,10^3]$ 的点才是有效的，接下来证明为什么。  

首先，枚举的总和范围在 $[0,10^6]$。  

证明：已知最后总和为 $0$，所以，负数的绝对值总和是等于正数的绝对值总和的，重新排列累加顺序，先累加所有正数，再累加所有负数，就可以保证过程的总和非负。  

接着，上界可以降低到 $10^3$。  

证明：如果有某一步，总和超过了 $10^3$，但是已知的是最终总值小于等于 $10^3$，所以，必然存在一种方案，将当前的数和后面步骤某个数交换，使得当前这一步的绝对值小于等于 $10^3$。   


```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(auto i=(a);i<=(b);i++)
#define REP(i,a,b) for(auto i=(a);i>=(b);i--)
#define FORK(i,a,b,k) for(auto i=(a);i<=(b);i+=(k))
#define REPK(i,a,b,k) for(auto i=(a);i>=(b);i-=(k))
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
#define islower(ch) (ch>='a'&&ch<='z')
#define isupper(ch) (ch>='A'&&ch<='Z')
#define isalpha(ch) (islower(ch)||isupper(ch))
template<class T>
void wrint(T x){
    if(x<0){
        x=-x;
        pc('-');
    }
    if(x>=10){
        wrint(x/10);
    }
    pc(x%10^48);
}
template<class T>
void wrintln(T x){
    wrint(x);
    pln
}
template<class T>
void read(T& x){
    x=0;
    int f=1;
    char ch=gc;
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=gc;
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=gc;
    }
    x*=f;
}
const int maxn=1005;
int n,k;
bitset<maxn> ok;
int dis[maxn];
void bfs(){
    memset(dis,0x3f,sizeof dis);
    int inf=dis[0];
    queue<int> q;
    FOR(i,n,1000){
        if(ok[i])dis[i-n]=1,q.push(i-n);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        FOR(i,0,1000){
            if(ok[i]){
                int to=u+i-n;
                if(to>=0&&to<=1000){
                    if(dis[to]>dis[u]+1){
                        dis[to]=dis[u]+1;
                        q.push(to);
                    }
                }
            }
        }
    }
    if(dis[0]==inf)puts("-1");
    else printf("%d\n",dis[0]);
}
void solve(int id_of_test){
	read(n);
    read(k);
    FOR(i,1,k){
        int a;
        read(a);
        ok[a]=1;
    }
    bfs();
}
int main()
{
	int T;
	T=1;
	FOR(_,1,T){
		solve(_);
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先题意即为找到一些 $a_i$ 使得平均数为 $n$，于是考虑每个物品减去 $a_i$，问题变为找到有一些物品使得和为 $0$。

由于物品之间本质相同，仅有大小上的区别，所以一定存在一种加入物品的方式使得任意时刻物品重量和绝对值不超过 $V$，具体证明考虑重量和小于 $0$ 时放重量为正的，否则放重量为负的，于是设计状态 $dp_i$ 表示凑出和为 $i$ 最少需要多少个物品。

由于每次转移时不限制转移物品的顺序，所以每次可以对于所有物品转移，且对于一个物品的多次转移也可以拆成多次单个物品的转移，所以 $dp_i$ 可以用所有 $dp_{i - w}$ 转移而来，虽然这个转移有环，但是观察到转移时加上的权值为 $1$，于是可以抽象为一个边权均为 $1$ 的最短路问题，直接 BFS 即可做到 $O(V^2)$。

[代码](https://codeforces.com/contest/788/submission/284429086)

---

## 作者：Leaper_lyc (赞：0)

## 0.闲话

题目难度虚高？

但是整体做差这个技巧如果第一次见很可能想不出来。

~~但是确实挺简单的。~~

## 1.题目简意

有 $k$ 种数，第 $i$ 种数为 $a_i$，每种数字都有无限多个。问至少要取多少个数，使得取出的数的平均值为 $n$。

## 2.分析

这里我们要用**整体做差思想**（不知道这么说对不对，反正我管它叫整体差分思想）。

显然原问题的式子是：

$$
\frac{\sum\limits_{i=1}^p b_i}{p}=n
$$

即：

$$
\sum\limits_{i=1}^p b_i=np
$$

其中 $b_i$ 表示我们选出来的数字，$p$ 表示我们选的数字个数。

令 $b_i'=b_i-n$。

转换一下原先的式子就是：

$$
\sum\limits_{i=1}^p (b_i-n)=np-np\\
$$

也就是：

$$
\sum\limits_{i=1}^p b_i'=0\\
$$

这个式子表达的不就是选出若干个数，使得和为 $0$ 吗？

背包勉强能够过去，但是不够优秀。

于是我们每次直接 $O(n)$ 枚举加了哪个数字，其实与广搜无差。由于每个数字都只会往外拓展一轮，所以时间复杂度是 $O(n^2)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 1e3;
const int N = M * 2 + 10;
const int inf = 0x3f3f3f3f;
int m, n;
int t[N], dis[N];
queue <int> q;
signed main() {
    cin >> m >> n;
    for (int i = 1, x; i <= n; i++)
        cin >> x, t[x - m + M]++;
    for (int i = 0 - m; i <= M - m; i++)
        if (t[i + M]) dis[i + M] = 1, q.push(i + M);
        else dis[i + M] = inf;
    for (int u; !q.empty();) {
        u = q.front(), q.pop();
        for (int i = 0 - m; i <= M - m; i++)
            if (dis[i + M] == 1 && dis[u + i] == inf)
            dis[u + i] = dis[u] + 1, q.push(u + i);
    }
    cout << (dis[M] != inf ? dis[M] : -1);
}
```

---

## 作者：ZjfAKIOI (赞：0)

这道题读完后，不难将其转化为选出最少的几瓶可乐，使其的平均数为 $n$。为了方便，我们可以将所有的 $a_i$ 减掉 $n$，最后使它们的和为 0。虽然 $k$ 很大，但我们发现本质不同的可乐只有 1000 种，然后就可以跑背包了。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
int dp[4000005],N,n,k,a[4000005];
signed main(){
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>k;
	for(int i=1;i<=k;i++) cin>>a[i],a[i]-=n;
	sort(a+1,a+1+k);
	int m=unique(a+1,a+1+k)-a-1;
	N=2e6;//偏移量，防止数组下标为负数
	for(int i=1;i<=m;i++){
		dp[N+a[i]]=1;
		if(a[i]<0){ 
			for(int j=500000;j>=-500000;j--){
				dp[j+N]=min(dp[j+N],dp[j+N-a[i]]+1);
			}
		}
		else{
			for(int j=-500000;j<=50000;j++){
				dp[j+N]=min(dp[j+N],dp[j+N-a[i]]+1);
			}
		}
	}
	if(dp[N]>1e9) cout<<"-1\n";
	else cout<<dp[N]<<"\n";
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有 $k$ 个数，每个数是 $a_i$，问要配出平均数为
 $n$ 最少需要几个数，无解输出 $-1$。
## 大体思路
虽然 $k\le10^6$，但是 $a_i\le1000$，所以我们直接去个重即可，然后我们直接定一个队列，枚举一下所有的配置情况，由于每次都取平均数太麻烦，我们可以所有的 $a_i$ 都变成 $a_i-n+1000$，这样我们处理的时候到 $0$ 即可，在输出答案的时候输出 $dis_{1000}$ 就行了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[2005];
queue<int> q; 
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=0;i<=2000;i++){
		dis[i]=0x3f3f3f3f;
	}
	for(int i=1;i<=k;i++){
		int a;
		cin>>a;
		dis[a-n+1000]=1;//免得他直接减n变成负数，可以这样处理 
	}
	for(int i=0;i<=2000;i++){
		if(dis[i]==1){
			q.push(i);
		}
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<=2000;i++){//最多就2000的平方，我们直接枚举就行 
			if(dis[i]==1&&dis[x+i-1000]==0x3f3f3f3f){//之前没出现过这个浓度，而且i浓度出现过 
				q.push(x+i-1000);
				dis[x+i-1000]=dis[x]+1;//汽水数加一 
			}
		} 
	}
	if(dis[1000]==0x3f3f3f3f){//没出现过
		cout<<-1; 
	} 
	else{
		cout<<dis[1000];
	}
	return 0;
}
```

---

