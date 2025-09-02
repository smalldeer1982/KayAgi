# Bear and Two Paths

## 题目描述

Bearland has $ n $ cities, numbered $ 1 $ through $ n $ . Cities are connected via bidirectional roads. Each road connects two distinct cities. No two roads connect the same pair of cities.

Bear Limak was once in a city $ a $ and he wanted to go to a city $ b $ . There was no direct connection so he decided to take a long walk, visiting each city exactly once. Formally:

- There is no road between $ a $ and $ b $ .
- There exists a sequence (path) of $ n $ distinct cities $ v_{1},v_{2},...,v_{n} $ that $ v_{1}=a $ , $ v_{n}=b $ and there is a road between $ v_{i} $ and $ v_{i+1} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/df2239069f54aa7a5a4a8635b063b23acac8c6be.png).

On the other day, the similar thing happened. Limak wanted to travel between a city $ c $ and a city $ d $ . There is no road between them but there exists a sequence of $ n $ distinct cities $ u_{1},u_{2},...,u_{n} $ that $ u_{1}=c $ , $ u_{n}=d $ and there is a road between $ u_{i} $ and $ u_{i+1} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/df2239069f54aa7a5a4a8635b063b23acac8c6be.png).

Also, Limak thinks that there are at most $ k $ roads in Bearland. He wonders whether he remembers everything correctly.

Given $ n $ , $ k $ and four distinct cities $ a $ , $ b $ , $ c $ , $ d $ , can you find possible paths $ (v_{1},...,v_{n}) $ and $ (u_{1},...,u_{n}) $ to satisfy all the given conditions? Find any solution or print -1 if it's impossible.

## 说明/提示

In the first sample test, there should be $ 7 $ cities and at most $ 11 $ roads. The provided sample solution generates $ 10 $ roads, as in the drawing. You can also see a simple path of length $ n $ between $ 2 $ and $ 4 $ , and a path between $ 7 $ and $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/3628f2a6a8994f3a6e5bdc8bfe5270b9f748a11c.png)

## 样例 #1

### 输入

```
7 11
2 4 7 3
```

### 输出

```
2 7 1 3 6 5 4
7 1 5 4 6 2 3
```

## 样例 #2

### 输入

```
1000 999
10 20 30 40
```

### 输出

```
-1
```

# 题解

## 作者：_xbn (赞：2)

我们可以构造这样一张图：

![](http://codeforces.com/predownloaded/74/7c/747c733d8af335caaf82f3061ce443056ad12cc9.png)

可以发现边数肯定是要多于点数的，所以边数少于点数的图为无解情况，另外，当 $n = 4$ 时，我们枚举出所有情况，发现均为无解，所以 $n = 4$ 时也为无解。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, d[N], b[N], c[N], A, B, C, D;
vector<int> pr;
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int main()
{
	n = read(); m = read();
	A = read(); B = read(); C = read(); D = read(); b[A] = 1; b[B] = 1; b[C] = 1; b[D] = 1;
	if(n == 4 || m <= n) { puts("-1"); return 0; }
	for (int i = 1; i <= n; i++) if(b[i] == 0) pr.pb(i);
	cout << A << " " << C << " "; for (auto v : pr) cout << v << " "; cout << D << " " << B << endl;
	cout << C << " " << A << " "; for (auto v : pr) cout << v << " "; cout << B << " " << D << endl;
	return 0;
}
```



---

## 作者：yangzd (赞：1)

# 题目大意：

给出 $n$ 个点，要求用至多 $k$ 条无向边构造出从 $a$ 到 $b$ 和从 $c$ 到 $d$ 的哈密顿通路，且 $a$ 和 $b$ 之间以及 $c$ 和 $d$ 之间不能右边，如果存在则输出这两条哈密顿通路，否则输出```-1```。

# 分析：

首先构造从 $a$ 到 $b$ 的哈密顿通路需要 $n-1$条边，为节省连边， $c$ 到 $d$ 的哈密顿通路要尽量用已有的边，但是由于从 $c$ 出发必然要经过 $a$ 点和 $b$ 点后再经过 $d$ 点，所以至少需要两条边来中转，即按如下方案构造：a-c-u-...-v-d-b，其中 $a$ 和 $u$ 连， $v$ 和 $b$ 连，那么 $c$ 到 $d$ 的哈密顿通路即为c-a-u-...-v-b-d，这种方案用了最少的边（$n+1$条边），但是需要只要一个中转点（即 $u$ 和 $v$ ），故 $n<5$ 或者 $k<n+1$ 时均无解。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,k,a,b,c,d,ans[1005];

signed main()
{
	ios::sync_with_stdio(0);
	
    cin >> n >> k;
    
    cin >> a >> b >> c >> d;
        
    if(n<5 || k<n+1)
        cout << "-1" << endl;
        	
    else
    {
        ans[1]=a;
		ans[2]=c;
		ans[n-1]=d;
		ans[n]=b;
		
        for(long long i=3,j=1; i<=n-2; i++)
        {
            while(j==a || j==b || j==c || j==d)
				j++;
				
            ans[i]=j++;
        }
        for(long long i=1; i<=n; i++)
        { 
			cout << ans[i];
			if (i==n)
				cout << endl;
			
			else
				cout << " ";
		}
		
        cout << ans[2] << " " << ans[1] << " " << ans[3] << " "; 
        
        for(long long i=4; i<=n-2; i++)
        	cout << ans[i] << " ";
        	
        cout << ans[n] << " " << ans[n-1] << endl; 
    }
    
    return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[Luogu](https://www.luogu.com.cn/problem/CF643B)

[Codeforces](http://codeforces.com/problemset/problem/643/B)

题目大意：一条哈密尔顿路径是一条经过图中所有点的链。给定 $n,k,a,b,c,d$，要求构造一张点数为 $n$，边数不超过 $k$ 的图，满足 $a$ 和 $b$，$c$ 和 $d$ 之间各有一条哈密尔顿路径，且 $a$ 和 $b$，$c$ 和 $d$ 不相连。

当 $n = 4$ 时，枚举得无解。

我们可以按下图的方式构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/s74bxcgd.png)

两条路径：$a-c-v_1-v_2-\cdots -v_{n-4}-d-b$ 和 $c-a-v_1-v_2-\cdots -v_{n-4}-b-d$。

此时 $a-b$ 的路径需要 $n-1$ 条边，连通 $c-d$ 至少还需要两条边，所以当 $k \le n$ 时无解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a, b, c, d, node[1001], cnt;
signed main(){
	scanf("%d%d%d%d%d%d", &n, &k, &a, &b, &c, &d);
	if (n >= k || n <= 4){puts("-1"); return 0;}//判无解 
	for (int i = 1; i <= n; i++)
		if (i != a && i != b && i != c && i != d) node[++cnt] = i;//找到其它中间点 
	printf("%d %d", a, c);
	for (int i = 1; i <= cnt; i++) printf(" %d", node[i]);
	printf(" %d %d\n", d, b);
	printf("%d %d", c, a);
	for (int i = 1; i <= cnt; i++) printf(" %d", node[i]);
	printf(" %d %d\n", b, d);//输出路径 
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
一共有 $n$ 个结点，给出互异的四个点 $a,b,c,d$，请你构造一个边数不超过 $k$ 的无向图，使得 $a$ 到 $b$、$c$ 到 $d$ 之间都存在一条哈密尔顿路径，且 $a,b$ 之间和 $c,d$ 之间不能直接连通。  
请输出你构造的路径。  
$4\le n\le 1000$
## $\text{Solution}$
首先，对于 $n=4$ 的情况，显然无解。  
否则，只要找到一种用边最少的方案即可。  
手玩发现，可以通过构造 $a\to c\to x\to...\to y\to d\to b$，再加两条 $a\to x$ 和 $y\to b$ 的边满足要求，总边数是 $n+1$。  
由于从 $c$ 走一定要去往 $a,b$，这都需要加边跳，所以至少加两条边，答案不会少于这个了。  
问题得以解决。  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5050;
#define ll long long
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
int x[N],a,b,c,d,vis[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  a=read();b=read();c=read();d=read();
  if(n<=4||m<n+1){
    printf("-1");return 0;
  }
  x[1]=a;x[n]=b;x[2]=c;x[n-1]=d;
  vis[a]=vis[b]=vis[c]=vis[d]=1;
  int tot=2;
  for(int i=1;i<=n;i++){
    if(!vis[i]) x[++tot]=i;
  }
  for(int i=1;i<=n;i++) printf("%d ",x[i]);
  putchar('\n');
  printf("%d %d ",c,a);
  for(int i=3;i<=n-2;i++) printf("%d ",x[i]);
  printf("%d %d\n",b,d);
  return 0;
}
/*
*/

```


---

