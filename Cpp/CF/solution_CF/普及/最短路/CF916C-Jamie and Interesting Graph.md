# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4
```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4
```

# 题解

## 作者：Fuko_Ibuki (赞：7)

构造题,好题.  
思考发现,如果我们让很多边的边权变得非常大,而故意留下$1->n$的某一条路径,使整条路径之和甚至还没有剩下一条边的权值大,这条路径显然就是最短路了.  
更重要的是,这样构造的结果,这条路径同时还是整张图的最小生成树!  
这样我们只需要找一个$100000$以上的质数,使得找出的路径的长度等于这个质数就可以了.  
如此问题就迎刃而解了.  


```cpp
/*
找出n-1条边先连成所求的最短路和最小生成树,剩下边全连inf.
*/
#include<cstdio>
int main()
{
int n,m,p=1e5+3,i;//10^5+3是比100000大的最小质数.如果选得比它小,一条边的长度可能到不了1.
scanf("%d%d",&n,&m);
printf("%d %d\n1 2 %d\n",p,p,p-n+2);
/*最短路和最小生成树的长度都是p.然后连接1和2,长度是p-n+2.*/
for (i=2;i<n;i++) printf("%d %d 1\n",i,i+1);
/*然后分别连接i和i+1,边权均为1.*/
m-=n-1;
for (int k=0,j=n;m--;)
/*接下来不断随意连接剩下的边就可以了.注意没有重边,不要连接已经连接过的边.打9999999的时候真的爽.*/
  {
  if (++j>n) j=++k+2;
  printf("%d %d 9999999\n",k,j);
  }
}
```

---

## 作者：0xFF (赞：5)

一道有趣的构造题，有了思路代码还是比较简单的

#### 简化题意
- 建一个图，总点数 $n$，总边数 $m$。

- 该图最短路和最小生成树边权和皆为质数。

#### 思路
考虑将最短路与最小生成树两者结合。

只需设计一条 $1$ 到 $n$ 的最短路同时包括所有的点就可以同时满足是一颗最小生成树。

考虑如何让这条路最小，我们可以把所有我们选上的边都标上 $1$，为了保证总和是一个质数，故我们找到一个大于 $10^5$ 的质数。

其余的边我只要让他们最大就行了。

#### 代码实现
1. 让 $1$ 到 $2$ 的一条边等于 $10^5+3-n+2$，这样我其他想要选的边全都标上 $1$ 就非常方便。
2. 把所有 $i$ 到 $i+1$ 的边都连成 $1$，这样最小生成树和最短路就都构造好了。
3. 按照需求补齐题目要求的边数，多出来的连回 $1$，边长不妨令其为 $10^9$。

#### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
#define ull unsigned long long
using namespace std;
const int MAXN = 2010;
const int prime = 1e5+3; 
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
ll n,m,cnt;
int main(){
	n = read() , m = read();
	printf("%d %d\n1 2 %d\n",prime,prime,prime-n+2);
	for(int i=2;i<n;i++){
		printf("%d %d 1\n",i,i+1);
	}
	m -= (n-1);
	for(int i=0,j=n;m--;){
		if(++j > n) j = ++i+2;
		printf("%d %d 1000000000\n",i,j);
	}
	return 0;
}
```


---

## 作者：东灯 (赞：4)

此处有一个比较长但是最正常的解法…

考虑把所有点连接成一条链，就把最短路和最小生成树的问题合并了。

考虑如何保证链的长度为质数，我们可以用线筛预处理出质数，然后二分找出大于等于 $n$ 的第一个质数，记为 $p$。

我们只需要在链上的 $1$ 到 $n-1$ 的位置连长度为 $1$ 的边，到最后在 $n-1$ 到 $n$ 连长度为 $p-(n-2)$ 的边就可以保证整条链的长度为质数。

如果这样构造，就可以让整张图的最小生成树和最短路径均为 $p$。

由于 $m$ 一般多于 $n$，还需要把 $m$ 处理掉，只需要从任意点 $i$ 开始，一直往 $i+k(k\ge 2)$ 的点连非常大的边即可，这里我们采取 $10^8$。

代码见下。

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<100005>isPrime;
int Prime[10005],cnt,ecnt;
void GetPrime(int n){
	for(int i=2;i<=n;++i){
		if(!isPrime[i])Prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*Prime[j]<=n;++j){
			isPrime[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}
int logalgor(int n){
    int l=1,r=cnt;
    while(l<r){
        int mid=(l+r)>>1;
        if(Prime[mid]>=n)r=mid;
        else l=mid+1;
    }
    return Prime[l];
}
int main(){
    int n,m,p;
    cin>>n>>m;
    GetPrime(100500);
    printf("%d %d\n",p=logalgor(n),p);
    for(register int i=1;i<n-1;++i){
        ++ecnt;
        printf("%d %d 1\n",i,i+1);
    }
    printf("%d %d %d\n",n-1,n,p-(n-2));
    for(register int i=1;i<=n;++i)
        for(register int j=i+2;j<=n;++j){
            if(ecnt==m-1)return 0;//m-1 是因为 n-1 到 n 的那条连边
            ++ecnt;
            printf("%d %d 100000000\n",i,j);
        }
}
```


---

## 作者：SpringFullGarden (赞：2)

## 题意

构造一个由 $n$ 个点，$m$ 条边的图，满足以下要求：

- $1$ 到 $n$ 的最短路径长度是质数。
- 最小生成树的边权和是质数。

## 思路

一个图可以化为一条链，让边权尽可能小，最短路和最小生成树便解决了。

找到 $n$ 后的质数 $p$，前面的边权都为 $1$，最后一个为 $p - n + 1$。其余 $m - n + 1$ 条边为无穷大。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define iu unsigned int
using namespace std;

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	int n, m, p; scanf("%d%d", &n, &m);
	for(int i = n + 1; 1; i++) {
		bool flag = 1;
		for(int j = 2; j * j <= i; j++)
			if(i % j == 0) {flag = 0; break;}
		if(flag) {p = i; break;} 
	}
	printf("%d %d\n", p, p);
	for(int i = 1; i < n - 1; i++)
		printf("%d %d 1\n", i, i + 1);
	printf("%d %d %d\n", n - 1, n, p - n + 2);
	m -= n - 1;
	for(int i = 1; i <= n; i++)
		for(int j = i + 2; j <= n && m; j++, m--)
			printf("%d %d 999999999\n", i, j);
	return 0;
}

```

---

## 作者：Larry76 (赞：2)

## 题目大意：
要求构造一张图，并让该图满足以下条件：
1. 有 $n$ 个点，$m$ 条边。
2. 每条边的边权范围是 $[1,10^9]$。
3. 图中从 $1$ 到 $n$ 的最短路径长度是个质数。
4. 最小生成树的边权和为质数。
5. 没有重边和自环。

## 题目分析：
先用质数筛筛一遍，然后因为与生成树相关，所以不难想到先构造一颗树，然后在树上添加边权为 $+\infty$ 的边。又因为要满足最短路径的长度为质数，所以方便起见，我们可以先构造一朵菊花，然后再在其上面加边即可。

时间复杂度 $O(n+m)$。

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define TIME_LIMIT (time_t)2e3
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define inf (int)1e9
#define MAX_SIZE (int)2e6
bitset<MAX_SIZE>nf;
int primes[MAX_SIZE];
void primeshai(int num) {
    for (int i = 2; i < num; i++) {
        if (!nf[i])
            primes[++primes[0]] = i;

        for (int j = 1; j <= primes[0] && primes[j]*i <= num; j++) {
            nf[i * primes[j]] = 1;

            if (i % primes[j] == 0)
                break;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    time_t cs = clock();
#endif
    //========================================
    primeshai(MAX_SIZE);
    int m, n;
    cin >> n >> m;
    int nowsum = (n - 2) * 2;
    int lastw = primes[1];

    for (int i = 1; i <= primes[0] && primes[i] + nowsum < MAX_SIZE; i++) {
        if (!nf[nowsum + primes[i]]) {
            nowsum += primes[i];
            lastw = primes[i];
            break;
        }
    }

    cout << 2 << ' ' << nowsum << endl;
    cout << 1 << ' ' << 2 << ' ' << lastw << endl;

    for (int i = 2; i < n; i++)
        cout << 1 << ' ' << i + 1 << ' ' << 2 << endl;

    int cnt = 0;
    m -= n - 1;

    while (cnt < m) {
        for (int i = 2; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                cout << i << ' ' << j << ' ' << inf << endl;
                cnt++;

                if (cnt >= m)
                    break;
            }

            if (cnt >= m)
                break;
        }
    }

    //========================================
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
    time_t ce = clock();
    cerr << "Used Time: " << ce - cs << " ms." << endl;

    if (TIME_LIMIT < ce - cs)
        cerr << "Warning!! Time exceeded limit!!" << endl;

#endif
    return 0;
}
```

---

## 作者：Mlzsan_HP (赞：1)

一道~~很水的~~构造题，但找到方法之后代码极其简单。

[题目链接](https://www.luogu.com.cn/problem/CF916C)

### 题意：

构造一个由 $n$ 个点， $m$ 条边的图，并满足以下要求

$1$ 到 $n$ 的最短路径长度是质数。

最小生成树的边权和是质数。

### 思路：

如果让许多边的边权变得很大，都连上 ${10}^{9}$ 只留下一条 $1$ 到 $n$ 的路径。

为了保证最小路的总和为质数，我们找到一个大于 ${10}^{5}$ 的质数即可。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+3;
int n,m,a(N);
int main(){
	scanf("%d%d",&n,&m);
	printf("%d %d\n1 2 %d\n",a,a,a-n+2);
	for(int i=2;i<n;i++)printf("%d %d 1\n",i,i+1);
	m-=n-1;
	for(int i=0,j=n;m--;){
  		j++;
		if(j>n)i++,j=i+2;
  		printf("%d %d 1000000000\n",i,j);
  	}
  return 0;
}
```



---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF916C)

题目大意：要求构造一个无向图，要求它的最短路径以及最小生成树都为质数。

分析：其实只要换一下思路就很好解决。我们只需要将 `1 n` 这条路径的权值设为 $2$，这样已经为最小的质数，之后的路径即使两个 $1$ 的路径也难以刷新；那么这个问题已经解决了。同样，对于最小生成树，直接将 `1 i` 的路径都设为 $2$ 一个难以刷新的值就行。这里需要将某一条路径增大，来保证为质数。最后就是剩余的路径了。因为前面都是只包含了 $1$ 的路径，所以随意找几条不包含它的就行了。这里注意避免被刷新设成一个最大值 `1000000000`。

## AC Code:

```cpp
#include <iostream>
#define int long long
using namespace std;
int n,m;
bool check(int x)//判断质数
{
    for(int i = 2;i * i <= x;i ++)if(x % i == 0)return false;
    return true;
}
signed main()
{
    cin >> n >> m;
    cout << "2 ";
    for(int i = 2 * n - 2;;i ++)
        if(check(i))
        {
            cout << i << endl;
            cout << "1 2 " << i - (2 * n) + 4 << endl;//第一条边，为了满足质数条件需要特判
            for(int j = 2;j < n;j ++)cout << "1 " << j + 1 << " 2\n";//剩余n-2条
            int cnt = n - 1;
            for(int j = 2;j <= n;j ++)
                for(int k = j + 1;k <= n;k ++)
                {
                    if(cnt == m)return 0;
                    cout << j << " " << k << " 1000000000\n";
                    cnt ++;
                }
            return 0;
        }
}
```

---

## 作者：yimuhua (赞：1)

一道构造题。

**题意：**

求出一个图，总点数 _n_ ，总边数 _m_ ，其最小生成树的边权和和从 _1_ 到 _n_ 的最短路长度都是一个质数。

**思路：**

将最小生成树和最短路结合起来。

设计一个 _1_ 到 _n_ 的最短路，那自然包括所有节点就行了，这就是一颗生成树。

考虑如何让这条路最小，可以把所有选上的边都标上 _1_ ，为了保证和是一个质数，随便选一个大于 _10^5_ 的质数，我选择的是 _10^5+3_, 其余的边只要让他们最大就行了。

**代码构造：**

1.可以让 _1_ 到 _2_ 的一条边等于 _10^5+3-n+2_，这样其他想要选的边全标 _1_ 就非常方便。

2.把所有 _i_ 到 _i+1_ 的边都连成 _1_ ，这样最小生成树和最短路就都构造好了。

3.按照需求补齐他想要的边数，多出来的连回 _1_ ，边长不妨令其为 _1e9_ 。

**AC代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 1e5 + 3;
int n, m;
int main() {
    cin >> n >> m;
    cout << p << ' ' << p << "\n" << "1 2 " << p - n + 2 << "\n";
    for(int i = 2; i < n; i++)
        cout << i << ' ' << i + 1 << " 1\n";
    m -= n - 1;
    for(int i = 0, j = n; m--; ) {
        if(++j > n)
            j = ++i + 2;
        cout << i << ' ' << j << " 1000000000\n";
    }
    return 0;
}
```


---

## 作者：Great_Influence (赞：1)

直接构造。

随便找一个比较大的质数，构建一条从1到n的哈密顿路径使得这条路加起来等于这个质数。其他多余的边直接连1e9就可以了。


代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline void read(int &x)
{
    int s=0,f=1;char k=getchar();
    while(!isdigit(k)&&(k^'-'))k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
inline void file()
{
    #ifndef ONLINE_JUDGE
        freopen("c.in","r",stdin);
        freopen("c.out","w",stdout);
    #endif
}
const int MAXN=2011;
const int prime=999999929,ma=1e9;
static int n,m;
inline void init()
{
    read(n);read(m);
}
inline void solve()
{
    printf("999999929 999999929\n");
    Rep(i,1,n-2)printf("%d %d %d\n",i,i+1,1);
    printf("%d %d %d\n",n-1,n,prime-n+2);
    m-=n-1;
    static int st=1,ed=3;
    while(m)
    {
        printf("%d %d %d\n",st,ed,ma);
        ++ed;--m;
        if(ed>n)++st,ed=st+2;
    }
}
int main()
{
    file();
    init();
    solve();
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

这是一道很水的构造题。为了满足：

- $1$ 到 $n$ 的最短路径长度是质数。

- 最小生成树的边权和是质数。

那么我们一开始就把最短路径和最小生成树构造出来。其实他们两个可以是同一个！我们想象把 $1\sim n$ 连成一条链，链上的边权很小且满足边权和为质数。然后其他的边都很大。那么这条链很明显就是最小生成树又是最短路径。

因为题目没有说边权不重复，所以我们可以让 $1\sim n-1$ 之间的链上的边权为 $1$，$n-1\sim n$ 这条边我们配一个尽可能小的，使得链的边权和为质数的边权。

现在我们已经配好了 $n$ 个点和 $n-1$ 条边，对于剩下的 $m-n+1$ 条边我们枚举任意两个不相邻的点，在他们之间连边，边权为一个很大的质数（如 $998244353$），一直连直到边数等于 $m$ 即可。题目保证边数最多是 $\frac{n(n-1)}{2}$，即完全图。

## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


const int N=5e3+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;

int q;
int t,ans,p[M],mn=INF,mx;
int cnt,r;
int f[N][N];
int a,b;

bool f2;


signed main(){
	// freopen("xor.in","r",stdin);
	// freopen("xor.out","w",stdout);
	int M=100003;
	n=rd;
	m=rd;
	cout<<M<<' '<<M<<endl;
	for(int i=1;i<n-1;i++){
		cout<<i<<' '<<i+1<<' '<<1<<endl;
		M--;
	}
	cout<<n-1<<' '<<n<<' '<<M<<endl;
	m-=n-1;
	for(int i=1;i<=n;i++){
		for(int j=i+2;j<=n;j++){
			if(m==0) return 0;
			cout<<i<<' '<<j<<' '<<998244353<<endl;
			m--;
		}
	}
}

/*
2
3 2 3 6
*/

```




---

## 作者：feiji_code (赞：0)

## 题意：
- 建一个图，$n$ 个点 $m$ 条边。
- $1$ 到 $n$ 的最短路得是质数，这张图的最小生成树也得是质数。（质数是只有1和它本身两个因数的自然数）
- 没有自环和重边。

### 思路：
让图变成一条链，使边权尽可能小，就能将最短路和最小生成树合并了。

$P$ 只要是 $100000$ 以上的质数就行了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
//主函数
const int P=1e5+3;//个人喜好，大于100000的最小质数
int n,m;
int main(){
	cin>>n>>m;
	printf("%d %d\n1 2 %d\n",P,P,P-n+2);
	for(int i=2;i<n;i++){
		printf("%d %d 1\n",i,i+1);
	}
	m-=(n-1);
	for(int k=0,j=n;m--;){
		j++;
		if (j>n){
			k++;
			j=k+2;
		}
  		printf("%d %d 1000000000\n",k,j);
	}
	return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：0)

既然要 $1\to n$ 的最短路和最小生成树都是质数，不妨令最小生成树即 $1\to n$ 的这条链。

如何使得这个东西成立？我们找到一个略大于 $10^5$ 的质数 $p$，使得最小生成树的权值为它。这是简单的，这条链是 $(n-1)$ 长度，所以，$2\to 3$、$3\to 4$ 直到 $n-1\to n$ 这 $(n-2)$ 条边全是 $1$，$1\to2$ 为 $p-n+2$。

然后我们会发现 $m$ 条边没有补齐。那么既然已经出现了一条链我们在链旁边加无意义的边，钦定边权 $10^9$，这样最小生成树肯定不会包括它，从小往大枚举边长然后输出就好了。

```cpp
// LUOGU_RID: 119075136
#include <bits/stdc++.h>
using namespace std;
const int p=1e5+19,big=1e9;
int n,m,i,l=3;
#define rep(i,l,r) for(i=l;i<=r;++i)
int main()
{
	scanf("%d %d",&n,&m);m=m-n+1;
	printf("%d %d\n",p,p);
	printf("%d %d %d\n",1,2,p-n+2);
	rep(i,3,n)printf("%d %d %d\n",i-1,i,1);
	i=1;
	while(m--)
	{
		if(i+l-1>n)
		{
			++l;
			i=1;
		}
		printf("%d %d %d\n",i,i+l-1,big);
		++i;
	}
	return 0;
}
```

---

## 作者：BMTXLRC (赞：0)

一道很有意思的构造题。

首先分析一下题，题目想要我们求出一个图，总点数 $n$ ，总边数 $m$ 。

其次构造出的图，其最小生成树得边权和必须是一个质数，从 $1$ 到 $n$ 的最短路长度也得是一个质数。

------------

### 思路：

看到最小生成树和最短路同时出现，就想到把他们俩结合在一起。

**怎么结合呢？**

设计一个 $1$ 到 $n$ 的最短路，那自然包括所有节点就行了，这就是一颗生成树。

考虑如何让这条路最小，我们可以把所有我们选上的边都标上 $1
$ ，为了保证总共是一个质数，我们找到一个大于 $10^5$ 的质数。

这个随便选都行，按照习惯（其实是看起来顺），我选择的是 $10^5+3$ （不过第一篇题解也是这样选的qwq）。

其余的边我只要让他们最大就行了。

------------

### 代码构造：

第一步，我们可以让 $1$ 到 $2$ 的一条边等于 $10^5+3-n+2$ ，这样我其他想要选的边全都标 $1$ 就非常方便。

第二步，把所有 $i$ 到 $i+1$ 的边都连成 $1$ ，这样最小生成树和最短路就都构造好了。

第三步，按照需求补齐他想要的边数，多出来的连回 $1$ ，边长不妨令其为 $10^9$ 。

------------

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1e5+3;
int n,m,cnt=0;
int main(){
    scanf("%d %d",&n,&m);
    printf("%d %d\n1 2 %d\n",p,p,p-n+2);
    for(register int i=2;i<n;i++) printf("%d %d 1\n",i,i+1);
    m-=(n-1);
    for(register int i=0,j=n;m--;){
        if(++j>n) j=++i+2;
        printf("%d %d 1000000000\n",i,j);
    }
}
```

---

## 作者：All_Unluck_Beginning (赞：0)

# CF916C 题解

## 思路

思考发现，如果我们让很多边的边权变得非常大，而故意留下 $1$ 到 $n$ 的某一条路径，使整条路径之和甚至还没有剩下一条边的权值大，这条路径显然就是最短路了。

更重要的是，这样构造的结果，这条路径同时还是整张图
的最小生成树。

这样我们只需要找一个 $100000$ 以上的质数，使得找出的路径的长度等于这个质数就可以了。

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n,m,p=1e5+3;
int main() {
	cin>>n>>m;
	cout<<p<<" "<<p<<endl<<1<<" "<<2<<" "<<p-n+2<<endl;
	for (int i=2; i<n; i++) cout<<i<<" "<<i+1<<" "<<1<<endl;//然后分别连接i和i+1,边权均为1。 
	m-=n-1;
	for (int k=0,j=n; m--;){
		if (++j>n) j=++k+2;
		cout<<k<<" "<<j<<" 9999999"<<endl;
	}
	return 0;
}
```

---

