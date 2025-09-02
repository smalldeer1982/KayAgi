# [ABC131E] Friendships

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc131/tasks/abc131_e

以下の条件を満たす $ N $ 頂点の無向グラフは存在するでしょうか？

- グラフは単純かつ連結である。
- 各頂点には $ 1,\ 2,\ ...,\ N $ の番号が付けられている。
- グラフの辺数を $ M $ としたとき、各辺には $ 1,\ 2,\ ...,\ M $ の番号が付けられていて、辺 $ i $ は頂点 $ u_i $ と頂点 $ v_i $ をつなぐ長さ $ 1 $ の辺である。
- 最短距離が $ 2 $ であるような頂点対 $ (i,\ j)\ (i\ <\ j) $ が、ちょうど $ K $ 個存在する。

条件を満たすグラフが存在するならば $ 1 $ つ構築してください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ K\ \leq\ \frac{N(N\ -\ 1)}{2} $

### Sample Explanation 1

このグラフには最短距離が $ 2 $ であるような頂点対が $ (1,\ 4),\ (2,\ 4),\ (3,\ 5) $ の $ 3 $ 個存在します。よって条件を満たしています。

### Sample Explanation 2

条件を満たすグラフは存在しません。

## 样例 #1

### 输入

```
5 3```

### 输出

```
5
4 3
1 2
3 1
4 5
2 3```

## 样例 #2

### 输入

```
5 8```

### 输出

```
-1```

# 题解

## 作者：Dreamer_xbt910 (赞：6)

## 前言
这是本人第一篇题解。

## 题意

构造一个简单图（没有重边与自环）。图中总共有 $N$ 个节点，分别为 $1$ 到 $N$。总共有 $M$ 条边，每一条边的长度均为 $1$。有且仅有 $K$ 对节点 $(u,v)$ 满足 $u$ 到 $v$ 的最短距离为 $2$。若不存在这样的图，输出 `−1`，否则给出任何一种满足条件的图。

## 思路

这是一道简单的构造题，可以想到菊花图(或树)。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/u5vft8ym.png)

图中一共有 $\frac{(N-1)\times(N-2)}{2}$ 对距离为 $2$ 的点。

所以，还需要减去 $\frac{(N-1)\times(N-2)}{2} - K$ 对距离为 $2$ 的点。

如图，可以在 $2$ 和 $3$ 、 $2$ 和 $4$ 、 $2$ 和 $5$ 或 $3$ 和 $7$ 等连边即可，直到减完为止。

![](https://cdn.luogu.com.cn/upload/image_hosting/ar0kmznr.png)

## Code

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,b;
signed main(){
    scanf("%lld%lld",&n,&m);
    int q=(n-1)*(n-2)/2;
    if(m>q){
        printf("-1");
        return 0;
    }
    int o=q-m;
    b=o+n-1;
    printf("%lld\n",b);
    for(int i=2;i<=n;i++){
        cout<<"1 "<<i<<endl;
    }
    for(int i=2;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i==j)continue;
            if(!o)return 0;
            cout<<i<<" "<<j<<endl;
            o--;
        }
    }
    return 0;
}
```

---

## 作者：qwerty12346 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc131_e)

## 题意

这题就是输出 $n$ 个点的无向连通图的总边数。并输出 $m$ 组 $i$ 和 $j$ 表示其两点之间有一条边相连。

## 思路

我们可以知道 $5$ 个点的无向连通图最多有 $6$ 组，而 $4$ 个点的无向连通图最多有 $3$ 组。所以我们可以推出 $n$ 个点的无向连通图最多有 $(n-1)\times(n-2)\div2$ 组，然后我们将 $n$ 个点的无向连通图的组数计为 $k$ 组。再然后判断如果 $k$ 小于 $m$ 那么就输出 $-1$，如果 $k$ 等于 $m$ 那么就按上面的方式构造输出就行，如果 $k$ 大于 $m$ 那么就让 $k$ 减一，因为这组 $i$ 和 $j$ 不满足条件。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    int k=(n-1)*(n-2)/2;//求组数
    if(k<m)//判断
    {
        cout<<-1;
        return 0;
    }
    cout<<n-1+k-m<<endl;//输出总边数
    for(int i=2;i<=n;i++)cout<<i<<" "<<1<<endl;
    for(int i=2;i<=n;i++)
    {
	for(int j=i+1;j<=n;j++)
	{
	    if(k==m)return 0;//判断
	    cout<<i<<" "<<j<<endl;//合法就输出
            k--;//组数减一
	}
    }
    return 0;
}
```


---

## 作者：xiaoshumiao (赞：2)

蛮巧妙的构造题。

先构造一个菊花图，此时两两距离为 $2$ 的点对数量是最多的，为 $\frac{(n-1)(n-2)}{2}$。所以如果 $k>\frac{(n-1)(n-2)}{2}$ 直接输出 `-1`。

可以发现我们每往菊花里连一条新的边，就相当于把一组 $(u,v)$ 的最短距离变成 $1$。

因此可以得到最终的构造方案：

- $\forall i \in[2,n]$，连一条边 $(1,i)$。
- 再任意连 $k-\frac{(n-1)(n-2)}{2}$ 条边。


代码：
```cpp
#include<cstdio>
using namespace std;
int main() {
  int n,k; scanf("%d %d",&n,&k); int delta=(n-1)*(n-2)/2;
  if(k>delta) return printf("-1"),0;//无解
  printf("%d\n",n-1+delta-k);
  for(int i=2;i<=n;i++) printf("1 %d\n",i);//构造菊花
  int cnt=1;
  //再连剩下的边
  for(int i=2;i<=n;i++)
    for(int j=i+1;j<=n;j++) {
      if(cnt>delta-k) break;
      cnt++,printf("%d %d\n",i,j);
    }
  return 0;
}
```

---

## 作者：Sirkey (赞：1)

这道构造题，非常有趣。

首先我们要构造一个图。

我把这个图称为：

# 菊花阵：

![菊花阵](https://cdn.luogu.com.cn/upload/image_hosting/1ttbgfba.png)

你就说像不像吧。

这个神奇的菊花阵可以给我得到 $\dfrac{(n-1)\times(n-2)}{2}$ 个距离为 $2$ 的对数，这也将距离为 $2$ 的点的个数最大化。

其原因是，距离为 $2$ 的两个点必定会经过一个点，我们把这个点弄成一个，不就最多了吗。

接下来神奇的菊花阵的用处就体现出来了。

你连接任意两个点,只有不是中间的就行，你会发现就刚好少了一个对数。

反过来想想，如果菊花阵最多的数量都没有 $k$ 的数量多，就输出 $-1$，反之，你就工整的输出菊花阵，一条一条连接。

## 这道题不就做完了吗！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
    ll f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void out(ll x) {
    if(x<0) putchar('-');
    if(x>9) out(x/10);
    putchar('0'+x%10);
}
const int MX=1e2+5;
int m[MX][MX]; 
int main() {
	int n=read(),k=read();
	if(k>(n-1)*(n-2)/2) {
		cout<<"-1";
		return 0;
	}
	int have=(n-1)*(n-2)/2;
	cout<<n-1+have-k<<endl;
	have=have-k;
	FOR(i,2,n) cout<<i<<" 1"<<endl;
	ROF(i,n,3){ 
		ROF(j,i-1,2) {	
			if(have==0) return 0;
			cout<<i<<" "<<j<<endl;
			have--;
		}
	} 
    return 0;
}

```

——end——

---

## 作者：small_john (赞：1)

## 思路

还是挺简单的。

我们先来看 $5$ 个点最多有几对：

![](https://cdn.luogu.com.cn/upload/image_hosting/u1v87g2g.png)

可以发现，一共有 $6$ 对。按照这种构造方式，$n$ 个点最多有 $\frac{(n-1)\times(n-2)}{2}$ 对，记这个数为 $s$。

接下来就分类讨论：

1. 当 $k>s$ 时，构造不出来，输出 `-1`；
2. 当 $k=s$ 时，按上面的方式构造即可；
3. 当 $k<s$ 时，连满足 $1<i<j<n$ 的点 $i,j$，对数就会减少 $1$，即让 $i,j$ 这对点不满足条件。可以证明，这对其他的点没有影响（因为是最短路）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,s;
signed main()
{
	cin>>n>>k;
	s = (n-1)*(n-2)/2;//计算最多数量
	if(s<k) return cout<<-1,0;//无法构造
	cout<<n-1+s-k<<'\n';//n+1为最开始的边数，s-k为后面连的边数
	for(int i = 2;i<=n;i++)
		cout<<i<<" 1\n";
	for(int i = 2;i<=n;i++)
		for(int j = i+1;j<=n;j++)
		{
			if(s==k) return 0;//减完了
			cout<<i<<' '<<j<<'\n',s--;
		}
	return 0;
}
```

---

## 作者：Red_river (赞：0)

### 题目大意
其实这道题说的很明了了，就是构造一个简单图使得有且仅有 $k$ 对点的简单路径长度为二，[原题](https://www.luogu.com.cn/problem/AT_abc131_e)。
### 题意分析
这道题甚至已经告诉你了它是一道构造题。所以找结论就行了。实际我们可以发现，他最多还不到一个完全图，即边数为 $n(n-1)\div2$ 的任意一点都有一条边的图，而是边数为 $(n-2)\times(n-1)\div2$ 的图。于是超过这个就一定不符合条件了。接着我们又可以发现，我们可以将这个图从完全图后开始建边就能保证有且仅有 $k$ 对点的简单路径长度为二了。
### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define mod 998244353
#define N 200005
#define NO printf("No\n")
#define YES printf("Yes\n")
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N],kis[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9')){
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x){
	if(x==0){
		putchar('0');
		return;
	}
	if(x<0){
		x=-x;
		putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	k=(n-1)*(n-2)/2;
	if(k<m) wh(-1);
	else{
		wh(n+k-m-1);
		for(int i=2;i<=n;i++)
			wk(i),wh(1);k-=m;
		for(int i=2;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				if(!k) exit(0);k--;
				wk(i),wh(j);
			}
	}
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

抓住重要的关键点：$u$ 到 $v$ 距离为 $2$。

这相当于在 $u$ 和 $v$ 之间找一个中转节点。

那么可以想到，用菊花图来构造。

那么每个菊花的花瓣节点两两之间都是最短距离为 $2$ 的，共有 $t=\frac{(n-1)(n-2)}{2}$ 对节点。

可是题目要求有且仅有 $k$ 对满足条件。

若 $k>t$，那么无解。

若 $k<t$，我们还要删掉 $t-k$ 条边，选一对点，在他们之间直接加边即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, k, m;
signed main() {
	cin >> n >> k;
	int t = (n - 1) * (n - 2) / 2;
	if (k > t) return puts("-1"), 0;
	m = t - k;
	cout << m + n - 1 << '\n';
	for (int i = 2; i <= n; i++) cout << "1 " << i << '\n';
	for (int i = 2; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (m == 0) return 0;
			else cout << i << ' ' << j << '\n', m--;
}
```

---

## 作者：WoodReal12 (赞：0)

## 题意

你要构造一个 $n$ 点，$m$ 条边的没有重边和自环的无向图。使仅有 $k$ 个点对的距离为 $2$。

## 思路

要使距离为 $2$ 的点对最少，那么我们就可以想到一个特殊的图——菊花图。

> 什么是菊花图？
> 
> 菊花图是指能找到一个点与其他所有点都能有且仅有一条**直接连接**的边的图。例如：
> ![菊花图](https://cdn.luogu.com.cn/upload/image_hosting/4a6inim8.png)

可以证明，菊花图中距离为 $2$ 的点对是最少的，所以只要构造一个菊花图即可。

因为菊花图的边数是 $(n-1)\times(n-2)\div2$，所以当 $k$ 小于 $(n-1)\times(n-2)\div2$ 时就是不可以构造的。

具体细节请看代码。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define int long long
#define x first
#define y second
#define pii pair<int,int>
using namespace std;
int n,k;
signed main(){
	cin>>n>>k;
	if(k>(n-1)*(n-2)/2){
		cout<<-1<<endl;
		return 0;
	}
	int m=(n-1)*(n-2)/2;
	cout<<n-1+m-k<<endl;
	m-=k;
	for(int i=2;i<=n;i++)
		cout<<i<<' '<<1<<endl;
	for(int i=n;i>=3;i--)
		for(int j=i-1;j>=2;j--){
			if(m==0)
				return 0;
			cout<<i<<' '<<j<<endl;
			m--;
		}
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
首先我们会发现，对于任意一组满足 $i$ 到 $j$ 的距离为 $2$ 的 $(i,j)$，$i$ 与 $j$ 的度数一定为 $1$，并且他们有一个共同的过度点 $x$，若想要 $n$ 个点能产生最多的满足条件的组数，则将没组 $(i,j)$ 的过度点 $x$ 都设为一样的点即可，这样对于满足条件的 $(i_1,j_1)$ 与 $(i_2,j_2)$，$(i_1,j_2)$ 与 $(i_2,j_1)$ 同样是满足条件的，所以 $n$ 个点能够构造出来的组数 $k=\frac{(n-1) \times (n-2)}{2}$ 所以就可以设 $1$ 为那个中转点进行构造，构造出来的图的边数即为 $n+k-1-m$。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,m;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	m=read();
	int k=(n-1)*(n-2)/2;
	if(k<m)
	{
		puts("-1");
		return 0;
	}
	cout<<n+k-1-m<<endl;
	rep1(i,2,n) cout<<1<<' '<<i<<endl;
	rep1(i,2,n)
	{
		rep1(j,i+1,n)
		{
			if(k==m) return 0;
			--k;
			cout<<i<<' '<<j<<endl;
		}
	}
	return 0;
}

```

---

## 作者：watcher_YBH (赞：0)

# 思路:

按照题目要求，$n$ 个点一共有且仅有 $k$ 对点的最短路为 $2$。假设 $n$ 为 $5$，那么最优情况下，一共有 $\frac{(n-1)(n-2)}{2}$ 条边，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/ofn7fawi.png)

一共有 $(5,4),(5,3),(5,2),(4,3),(4,2),(3,2),6$ 对点。则 $k > \frac{(n-1)(n-2)}{2}$，可直接输出 $-1$。而在 $2,3,4,5$ 四个点之间，如果有某两个点相连，就会使总共满足要求的点的对数减一。所以，我们只需要在上图的基础上，在 $2,3,4,5$ 之间连接 $\frac{(n-1)(n-2)}{2} - k$ 条不重复的边就行了。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e3+5;
int n,k,ans;
int a[MAX][MAX];
int main(){
	cin>>n>>k;
	if(k > (n-1)*(n-2)/2){cout<<"-1";return 0;}
	int sub = (n-1)*(n-2)/2-k;//多的边数
	for(int i = 2; i<=n; i++) a[1][i] = a[i][1] = 1,ans++;//将2~n个点连接到1，并记录边数
	if(sub){
		int x = n,y = 2;
		while(sub--){//多了几条，就在2~n之间连接几条
			a[x][y] = a[y][x] = 1,ans++;//标记连接，并记录边数
			y++; if(y == x) x--,y = 2;
		}		
	}
	cout<<ans<<endl;
	for(int i = 1; i<=n; i++)//输出连接的边
		for(int j = 1; j<=n; j++)
			if(a[i][j]) cout<<i<<" "<<j<<endl,a[i][j] = a[j][i] = 0;//去掉边，以免重复
	return 0;//结束~
}
```


---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc131_e)

#### 思路

我们首先要思考怎么才能让距离为 $2$ 的一对点尽可能多，不难想到下面这种方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/6w6fy2hd.png)

这是 $n = 5$ 的时候，发现最多可以构成 $1 + 2 + 3 = 6$ 对距离为 $2$ 的点，也就是最多可以构成 $(n - 1) \times (n - 2) / 2$ 对，如果 $k$ 大于 $6$，说明一定不可能构成，当然，如果 $k$ 小于 $6$，我们可以再用几条线把距离不用为 $2$ 的连起来，如下图，是 $n = 5,k = 3$ 的其中一种构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/319470dl.png)

不难发现，我们只需要再连接 $(n - 1) \times (n - 2) / 2 - k$ 条其它不重复的边就可以了，明白了这些，代码就很好打了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum,v[110][110],l,whz;
int main()
{
	cin >> n >> k;
	sum = (n - 1) * (n - 2) / 2;
	if(k > sum)//无法构造 
	{
		cout << -1;
		return 0;
	}
	cout << n - 1 + (sum - k) + 1 << endl;
	for(int i = 1;i <= n - 1;i++) cout << i << " " << n << endl;
	for(int j = 1;j < n;j++)
	{
		if(whz == sum - k) return 0;
		for(int z = 1;z < n;z++)
		{
			if(whz == sum - k) return 0;//连完了
			if(j == z) continue; //相等不能连边
			if(!v[j][z])//没连过
			{
				v[j][z] = v[z][j] = 1; 
				cout << j << " " << z << endl;
				whz++;
			}
		}
	}
	return 0;
}


```


---

## 作者：Populus_euphratica (赞：0)

## 题意
构造一个满足如下要求的简单无向图：

1、一共有 $n$ 个点；

2、满足只有 $k$ 组点之间的最短路为 2；
## 思路
为了方便构造，我们可以考虑用一种图形作为基础，然后在上面进行调整。而作为基础的图需要可以准确求出满足最短路为 2 的点的组数。所以这个基础图只能是以总贡献最多的或最少的构造。贡献就是菊花图（也就是以一个点为父亲，其他的点都是这个点的儿子），最少的就是一条链。然后我们可以发现，如果在菊花图中，总贡献为 $MAX=\displaystyle \frac{(n-2)(n-2)}{2}$ 每一次连接两个未连接的点时，总贡献就只会减少 1，而且不会影响其他的点。总边数就为 $n-1+MAX-k$（菊花图需要 $n-1$ 条边，后面处理需要 $MAX-k$ 条边）。

所以我们可以先构造一个菊花图，然后在根据多出的贡献连接两点。当然，如果要求的 $k$ 大于了最大的贡献（也就是菊花图的贡献）就可以直接返回 -1 了。
## 举例 
可能光说不太好理解，现在用样例一来画图解释一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/jodiztw8.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/u25h95a2.png)
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k;
int m;
long long MAX;
int main()
{
    cin>>n>>k;
    MAX=(n-2)*(n-1)/2;
    if(k>MAX)
    {
	cout<<"-1"<<endl;
	return 0;
    }
    m=n-1+MAX-k;
    cout<<m<<endl;
    for(int i=2;i<=n;i++)
        cout<<1<<" "<<i<<endl;
    if(MAX-k==0)
        return 0;
    m-=n-1;
    for(int i=2;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            m--;
            cout<<i<<" "<<j<<endl;
            if(m==0)
                return 0;
	}
    }
	cout<<endl;
	return 0;
}


```


---

## 作者：StevenLiTheOIer (赞：0)

## 前言：
一道 ~~相对容易的~~ 构造题。
## 题意简述：
构造 $n$ 个点的无向连通图，相连的点距离为 $1$，要求存在 $k$ 对点的距离为 $2$，无解输出 $-1$。
## 思路：
距离为 $2$ 的两个点至少通过一个中点相连，所以距离为 $2$ 的点对最多的情况即 $n-1$ 个点都与同一个中点相连。容易证明此时点对的数量为 $(n-1)\times(n-2)$。所以 $k>(n-1)\times(n-2)$ 的情况无解。

在这个基础上，每连接一对点，相距 $2$ 的点对数即减少 $1$。按顺序连接不相连的点对，直到仅剩 $k$ 对合法的点，输出即可。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	int M = (n - 1) * (n - 2) >> 1; //最大合法点对数 
	if (k > M)
	{
		cout << -1 << endl; //无解 
		return 0;
	}
	int m = (n - 1) + (M - k); //先连接 n-1 条边，再从 M 对点中去掉 k 对，共 (n-1)+(M-k) 条边 
	cout << m << endl;
	for (int i = 2; i <= n; i++)
		cout << 1 << " " << i << endl;
	if (m == n - 1) return 0; //连完就直接退出 
	for (int i = 2; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			cout << i << " " << j << endl;
			if (--m == n - 1) return 0; //依次输出，直到满足条件 
		}
	}
	return 0;
}
```

---

## 作者：零殇 (赞：0)

#### 题意

构造 $n$ 个点的无向图，相邻两点距离为 $1$,令其有刚好有 $k$ 组点距离为 $2$。如果没有答案输出 $-1$。

#### 思路

首先考虑没有答案。

我们姑且把我们构造出的距离为 $2$ 的点的组数为 $x$。

$x$ 最小为 $0$，也就是完全图，这是很好想到的。

现在考虑最多。

因为距离为 $2$ 的一组点之间一定存在一个中点间接把它们连接。也就是说，最优的策略是让大家共享一个中间点，从而把剩下的所有点都连接起来，因此  $x$ 最大为 $(n-2)×(n-1)÷2$。

所以在这个范围之外的都是无解的。

现在考虑怎么构造。

我们回到完全图。

因为任意两点都是连接的，它们距离为 $1$。但是如果把这两个点连边去掉，那么就可以令它们之间产生中点。为了防止后来的删除会影响前面的结果，这个中点应该是所有组共用的，也就是说，以最优策略作为图的骨架。

这样每删除一条边，就可以让 $x$ 加一，因此 $m=n×(n-1)÷2-k$。

接下来只要在骨架不断添边就好了。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,m,sum;
int main() {
	scanf("%d%d",&n,&k);
	m=n*(n-1)/2-k;
	if(m<n-1) {//没有答案，其实就是无法构成骨架
		puts("-1");
		return 0;
	}
	printf("%d\n",m);
	for(int i=1;i<n;i++) {
		for(int j=i+1;j<=n;j++) {
			sum++;
			if(sum<=m)
				printf("%d %d\n",i,j);
			else
				return 0;
		}
	}
    return 0;
}
```
完结撒花~

---

## 作者：GeChang (赞：0)

# 题解 AT4752 【[ABC131E] Friendships】
纯思维题，卡了好久（（（
### 1.题意

构造一个有 $n$ 个点的无向连通图，图上任意两个点之间的距离为 $1$，其中有 $k$ 对点 $(i,j)(1≤i<j≤n)$ 之间的距离为 $2$。

### 2.分析

先考虑给出的图能否存在。

由于图是联通的，所以至少会存在 $n-1$ 条边，故假如按照给出的数据来连图，若边的数量比 $n-1$ 小，那么就不可能满足题意。

又因为对于每一对满足题意的点 $(i,j)$，它们之间一定没有边直接相连，而是通过一个“中间点”相连，不妨令“中间点”为 $N$。则此时对于每个不为 $N$ 的点 $i$，共有 $n-2$ 个点 $j$ 与之相对，又因为 $i$ 一共有 $n-1$ 个可能的取值，所以 $k$ 最大为 $(n-1)\times (n-2)$，具体方案见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/0lbl8f6h.png)

因此可以得到，每删去一条不与“中间点”相连的边，$k$ 的数目就会增加 $1$，故只要在保证与 $n$ 相连的边都存在的情况下将一个有 $n$ 个点的完全图不断向上述情况删减即可。然后不难得到，需要连接的边的数目为$n\times (n+1)/2-k$。

构造就如前所述，先把与 $n$ 相连的边都连上，再按照剩下的边数目来按顺序连边，直到已连边的数目与先前计算出的 $m$ 相等的时候结束就完成了。
### 3.代码

代码实现不难qwq

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,m,cnt=0;
int main()
{
	cin>>n>>k; //输入
	m=(n-1)*n/2-k; //一共要连多少条边
	if(m<n-1) //如果不能联通
	{
		cout<<-1<<endl;
		return 0; //结束
	}
	cout<<m<<endl; //输出m
	for(ll i=1;i<n;i++) cout<<i<<" "<<n<<endl;
   //先保证联通
	cnt+=n-1; //连边数+(n-1)
	for(ll i=1;i<=n;i++)
	{
		for(ll j=i+1;j<n;j++) //遍历所有没有连的边
		{
			if(cnt==m) return 0; //如果连够了，结束
			cout<<i<<" "<<j<<endl; //输出
			cnt++; //计数++
		}
	}
}
```


# 莫抄袭，没了AC记录，空悲切！
###### P.S.感谢管理的耐心审核！qwq

---

## 作者：Empty_Dream (赞：0)

## 分析

很容易想到菊花图，这种情况下叶子节点两两之间都满足要求，总共有 $(n-1)\times(n-2)$ 对，也是最多的情况。

我们考虑加边，算一下加边的贡献。模拟一遍，不难发现加一条边在两个叶子节点中间的贡献就是 $-1$，也就是把这两个叶子节点间的贡献去掉。只要加 $(n-1)\times(n-2)-k$ 条边就能满足条件。

实现方面，先构建一个菊花图，然后加边。对于加边的判重只需要先预处理出可以加的边（$n^2$ 一遍塞到队列里），~~如果欧气足够直接 random 后判重也行。~~

## 代码
```cpp
#include <bits/stdc++.h>
#define Luke return
#define Forever 0
#define int long long
using namespace std;

int n, k, cnt;
vector<int> g[105];
queue<pair<int, int>> q;

signed main(int argc, char **argv){
    cin >> n >> k;
    if (k > (n - 1) * (n - 2) / 2) return cout << -1, 0;//判断是否超过最大值
    for (int i = 2; i <= n; i++){
        for (int j = i + 1; j <= n; j++) q.push({i, j});//预处理
    }
    for (int i = 2; i <= n; i++) g[1].push_back(i), cnt++;//构建菊花图
    int now = (n - 1) * (n - 2) / 2;
    while (now > k){//不断在叶子节点间加边
        int x = q.front().first, y = q.front().second; q.pop();
        g[x].push_back(y);
        cnt++, now--;
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < g[i].size(); j++) cout << i << " " << g[i][j] << endl;
    }
    Luke Forever;
}
```

---

## 作者：Mu_leaf (赞：0)

## [思路]

很好的一道入门构造题。

我们可以先处理出距离为 $2$ 的点的对数最多且只存在距离为 1 或 2 的两个点的一个图。

可以发现，有了这些限制条件就可以建出此图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9y7ubwiy.png)

本图学名：菊花图。

指一个 $n$ 个点的图有 $n-1$ 个点的父亲是同一个。

那么我们可以发现此图中距离为 2 的两个点的个数为 $\dfrac{(n-1)\times (n-2)}{2}$。

且发现给任意未建边的两点间建一条边，对数就会减少 1。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5tg5xdjt.png)

于是本题就做完了，很简单是不是？那我就不放本人丑陋的代码了。

---

