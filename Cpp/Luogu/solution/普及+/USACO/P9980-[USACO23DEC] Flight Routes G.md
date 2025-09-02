# [USACO23DEC] Flight Routes G

## 题目描述

Bessie 最近发现她最喜欢的摇滚艺术家 Elsie Swift 正在表演她最新的“时代之旅”音乐会！不幸的是，票卖光的太快了，所以 Bessie 考虑飞往另一个城市参加音乐会。“时代之旅”将在编号为 $1\dots N$ 的 $N$（$2 \le N \le 750$）座城市上演，每对满足 $i<j$ 的城市对 $(i,j)$ 都可能存在从 $i$ 到 $j$ 的一条**单向直飞航班**。

从城市 $a$ 到城市 $b$ 的一条**航线**是一个包含 $k\ge 2$ 座城市的序列 $a=c_1<c_2<\cdots<c_k=b$，使得对于所有的 $1\le i< k$，城市 $c_{i}$ 到城市 $c_{i+1}$ 有**单向直飞航班**。对于所有满足 $i<j$ 的城市对 $(i,j)$，你将被告知它们之间航线数目的奇偶性（$0$ 代表偶数，$1$ 代表奇数）。

在计划她的旅行行程时，Bessie 分心了。现在她想知道，有多少对城市间有**单向直飞航班**。可以证明答案是唯一的。

## 说明/提示

### 样例解释 1

有两条单向直飞航班：$1\rightarrow 2$ 和 $2\rightarrow 3$。有城市 $1,2$ 之间、$2,3$ 之间，仅包含一条单向直飞航班的航线各一条。还有城市 $1,3$ 之间的航线一条（$1\rightarrow 2\rightarrow 3$）。

### 样例解释 2

有六条单向直飞航班：$1\rightarrow 2$，$1 \rightarrow 4$，$1\rightarrow 5$，$2\rightarrow 3$，$3\rightarrow 5$，$4\rightarrow 5$。这导致的航线数如下表所示：

| 出发地\目的地 | 1 | 2 | 3 | 4 | 5 |
| :-: | :-: | :-: | :-: | :-:|:-:|
| 1 | 0 | 1 | 1 | 1 | 3 |
| 2 | 0 | 0 | 1 | 0 | 1 |
| 3 | 0 | 0 | 0 | 0 | 1 |
| 4 | 0 | 0 | 0 | 0 | 1 |
| 5 | 0 | 0 | 0 | 0 | 0 |

这与输入是相符的。

### 测试点性质

- 测试点 $3-4$ 满足 $N \le 6$。
- 测试点 $5-12$ 满足 $N \le 100$。
- 测试点 $13-22$ 没有额外限制。

## 样例 #1

### 输入

```
3
11
1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1111
101
01
1```

### 输出

```
6```

# 题解

## 作者：RDFZchenyy (赞：7)

### 题目概述

有一张点数为 $n$ 的图，其中的单向边 $(i,j)$ 都满足 $i<j$。对于每一组满足 $1\le a<b\le n$ 的 $a,b$，给出从 $a$ 至 $b$ 的路径数对 $2$ 取模的值 $f(a,b)$，求这张图的边数。

对于 $100\%$ 的数据，满足 $2\le n\le 750$。

### 思路分析

我们首先注意到：可以确定这张图上存不存在边 $(a,a+1)$。因为从 $a$ 到 $(a+1)$ 的唯一可能的路径必然是只途径 $(a,a+1)$ 这一条边的路径。所以 $f(a,a+1)$ 为 $1$ 时存在边 $(a,a+1)$，否则不存在边 $(a,a+1)$。

通过这个性质，我们进一步发现所有的边 $(a,b)$ 是否存在都可以用 $f(a,b)$ 和从 $a$ 到 $b$ 不通过边 $(a,b)$ 的方案数对 $2$ 取模的值比对得到，即相同时不存在边 $(a,b)$ 不相同时存在。

考虑如何统计从 $a$ 到 $b$ 不通过边 $(a,b)$ 的路径数对 $2$ 取模的值。设 $g(a,b):a$ 到 $b$ 间是否有边。为了求出 $g(a,b)$，我们可以枚举从 $a$ 出发后紧接着到的位置 $k$。那么，我们有：

$$
g(a,b)=[(\sum\limits_{k=a+1}^{b-1}g(a,k)\times f(k,b))\bmod2=f(a,b)]
$$

其中，最外层中括号为艾佛森括号。这个式子的意思是：将每一组 $a\rightarrow k\rightarrow \cdots\rightarrow b$ 的方案数累和。

进一步地，这个式子也可以被简化为：

$$
g(a,b)=(\mathop{\oplus}\limits_{k=a+1}^{b-1}g(a,k)\times f(k,b))\oplus f(a,b)
$$

需要注意的是，为了求出 $g(a,b)$，我们必须先求出所有满足 $a+1\le k\le b-1$ 的 $g(k,b)$，所以我们从 $(b-a)$ 小的开始求起。

### 代码

根据以上内容，我们可以写得以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 800

char r;
int f[MAXN][MAXN],g[MAXN][MAXN];

int n,ans=0;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>r;
			f[i][j]=(r=='1');
		}
	}
	
	for(int len=1;len<=n;len++){ // 此处的 len 即枚举的 (b-a)
		for(int a=1,b=len;b<=n;a++,b++){ // 根据 len 和 a 确定 b
			for(int k=a+1;k<=b-1;k++){
				g[a][b]^=g[a][k]*f[k][b];
			}
			g[a][b]^=f[a][b];
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans+=g[i][j];
		}
	}
	cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：Argon_Cube (赞：5)

不需要限制对于所有边 $i\to j$ 满足 $i<j$ 的做法。

先考虑如果已知邻接矩阵 $A$ 能不能对于每一对 $(i,j)$ 求出 $i$ 到 $j$ 的路径条数奇偶性，我们记为 $f_{i,j}$，在题目中已经给出。可以发现，我们令 $f_{i,i}=1$，则

$$f_{i,j}=\sum_{k\to j}f_{i,k}=\sum_{k}f_{i,k}a_{k,j}(i\neq j)\implies F=FA+I\implies A=I-F^{-1}$$

矩阵求逆即可。（同时请教一个问题： $F$ 不存在逆是否等价于原图不是 DAG？）

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

using namespace std;

array<bitset<1500>,750> matrix;

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cnt;
    cin>>cnt;
    for(int i=0;i<cnt;matrix[i].set(i),matrix[i].set(i+cnt),i++)
        for(int j=i+1;j<cnt;j++)
        {
            char tmp;
            cin>>tmp;
            matrix[i][j]=tmp-'0';
        }
    for(int i=0;i<cnt;i++)
        for(int j=0;j<i;j++)
            if(matrix[j][i])
                matrix[j]^=matrix[i];
    int answer=0;
    for(int i=0;i<cnt;i++)
        for(int j=i+1;j<cnt;j++)
            answer+=matrix[i][j+cnt];
    cout<<answer;
    return 0;
}
```

场上在想能不能直接递推，以为 Gold 不会那么简单。原来是我想复杂了。

---

## 作者：Zi_Gao (赞：4)

> 题意：
>
> 给定一个 $n$ 个点的 DAG，并且有向边一定从编号小的点连向编号大的点，现在给出了两两间路径条数的奇偶性，问原图有多少条连边，可以证明答案唯一确定。
>
> $n\leq 750$

首先你需要知道如何求解这个问题的逆向问题，即给定一个这样的图，输出两两点连边的奇偶性，显然考虑一个 dp，设 $dp_{u,v}$ 表示 $u$ 和 $v$ 号点之间的连边奇偶性，显然有递推式子 $dp_{u,v}=\sum_{u\rightarrow w}dp_{w,v} \bmod2$。

然后考虑简化问题，只有两个点的时候怎么办？显然奇偶性为 $1$ 就是有边，否则没边。可以发现在原图扩张时由于 $n-1$ 号点只可能和 $n$ 点连边，这个性质仍然成立，这样就确定了一条边。继续考虑确定剩下的边，不妨先考虑 $n-2$ 号点和 $n-1$ 号点的连边情况，由于这两个点至多有一条连边，所以这条边的情况一可以直接确定。这时若有连边，那么 $n-2$ 号点就能通过 $n-1$ 号点尝试到达 $n$ 号点，然后就可以像上面的 dp 式子一样逆向转移一下，把这个点的贡献减出去，就可以少考虑一个点了。进而会发现当前 $n-2$ 号点到 $n$ 号点的其他路径已经确认完毕了，就剩是否直连的情况，在 dp 式子逆向转移后 $dp_{n-2,n}=1$ 那么肯定有边 $n-2\rightarrow n$ 了。不妨把这个解决过程推广到全图，从编号大的点倒序考虑，递推出来所有的连边情况。

用 `bitset` 实现的，因为可以发现逆向转移实际上就是在做一个异或。

```cpp
#include<bits/stdc++.h>
#define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

std::bitset<750> e[750],sour[750];

int main(){

    register char c;
    register int i,j,res=0;
    int n=read();
    for(i=0;i<n;++i){
        for(j=i+1;j<n;++j){
            loop:c=getchar();
            if(c!='0'&&c!='1') goto loop;
            sour[i][j]=e[i][j]=c-'0';
        }
    }

    for(i=n-1;~i;--i)
        for(j=i+1;j<n;++j)
            if(e[i][j]){
                ++res;
                e[i]=e[i]^sour[j];
            }

    print(res);

    return 0;
}
```


---

## 作者：DerrickLo (赞：3)

定义一条边的长度是两个顶点的编号之差。

我们先考虑从点 $i$ 到点 $i+1$ 是否有边，显然直接就能求出。

然后我们考虑从点 $i$ 到点 $i+2$ 是否有边，我们先求出从 $i$ 到 $i+2$ 是否有只经过长度为 $1$ 的边的路径，然后就能判断 $i$ 到 $i+2$ 有没有边了。

接着，我们推广到判断从点 $i$ 到点 $i+k$ 是否右边，只需要求出从 $i$ 到 $i+k$ 中只经过长度小于 $k$ 的边的路径的数量的奇偶性，然后看看与 $i$ 到 $i+k$ 的路径数量的奇偶性相不相同就行了。

求从 $i$ 到 $i+k$ 中只经过长度小于 $k$ 的边的路径的数量的奇偶性，可以从 $i+1$ 到 $j-1$ 枚举一个中间点 $l$，然后就能求出含有 $i\rightarrow l$ 这条边的路径有多少个，累加起来即可。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,vis[755][755],sum[755][755],ans;
char a[755][755];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n-i;j++)cin>>a[i][j],sum[i][i+j]=a[i][j]-'0';
	for(int i=1;i<=n;i++)vis[i][i]=1;
	for(int k=1;k<n;k++){
		for(int i=1;i<=n-k;i++){
			int j=i+k,flag=0;
			for(int l=i+1;l<=j;l++)flag^=vis[i][l]&sum[l][j];
			if(flag!=sum[i][j])ans++,vis[i][j]=1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：TSY48 (赞：1)

**解题思路**

---

不难发现，我们如果要知道 $i$ 和 $j$ 有没有连边，其实等价于  |$i$ 到 $j$ 的路径不包含 $i$ 直接到 $j$ 的路径| 的奇偶是否与 $c_{i,j}$ 相等。

知道这个后，我们就可以直接枚举在 $i$ 到 $j$ 的路径中的第一个点（不包含 $i$），令其为 $t$，则 $i<t<j$，则我们知道 $i$ 与 $t$ 是否相连，又知道 $t$ 到 $j$ 的路径数量的奇偶，则我们可以知道，以 $t$ 为第一个点的 $i$ 到 $j$ 的路径的数量的奇偶（这里 $i$ 与 $t$ 是否相连是为了判断存不存在这样的路径）。把所有的路径数量相加即可判断 $i$ 和 $j$ 有没有连边。

```cpp
const int Maxn = 750 + 10;
const int inf = 0x3f;
int c[Maxn][Maxn], e[Maxn][Maxn];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        str tw;
        cin >> tw;
        for (int j = 0; j < siz(tw); j++)
            c[i][i + j + 1] = (tw[j] - '0');
    }
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int res = 0;
            for (int t = i + 1; t < j; t++)
                res += (e[i][t] * c[t][j]);
            res %= 2;
            if (res != c[i][j])
                e[i][j] = 1;
            else
                e[i][j] = 0;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            ans += e[i][j];
            // printf("%d %d %d\n",i,j,e[i][j]);
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：yuanruiqi (赞：1)

既然所有单向边 $(u,v)$ 都满足 $u<v$，从原图取出点集 $[x,n]$ 就一定满足给定三角形 $[x,n-1]$ 行的限制。于是可以反过来递推，当前考虑到第 $x-1$ 行，顺次从 $x$ 到 $n$ 检查是否需要连接 $(x-1,i)$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 750 + 10;
bitset<maxn> v[maxn];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i=1;i<n;++i)
    {
        string s;
        cin >> s;
        for (int j=i+1;j<=n;++j)
            if (s[j-i-1] == '1')
                v[i][j] = 1;
    }
    int ans = 0;
    for (int i=n-1;i>=1;--i)
    {
        auto b = v[i];
        for (int x; (x=b._Find_first())<b.size();)
        {
            b.flip(x);
            b ^= v[x];
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

一排点，可以从前往后连单向边（无重边），给定每两个点之间路径数，求总连边数。

### 思路：

我们要求的就是对于每两个点 $i,j$ 满足 $i<j$，它们之间到底有没有单向边。设 $t_{i,j}=0$ 表示没有单向边，$t_{i,j}=1$ 表示有单向边。

考虑两点之间路径数是如何被计算出来的。设 $G(i,j)$ 表示 $i,j$ 之间的路径数（$i<j$），我们有：

$$G(i,j)=\sum_{k=i+1}^{j-1}t_{i,k}\times G(k,j)+t_{i,j}$$

即：考虑 $i,j$ 之间的一个点 $k$，若 $i,k$ 有连边，则答案增加 $G(k,j)$。最后再加上 $i,j$ 间直连的个数。

因此我们就有了递推式子，可以参考其它题解，这里不重复给出。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
const int N=755;
int n,ans;
char ch[N];
bool a[N][N],rt[N][N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%s",ch+1);
		for(int j=i+1;j<=n;j++)
			if(ch[j-i]=='1')
				a[i][j]=1;
	}
	for(int len=1;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			rt[i][j]=a[i][j];
			for(int k=i+1;k<j;k++)rt[i][j]^=(rt[i][k]&a[k][j]);
		}
	}
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			ans+=rt[i][j];
	printf("%d\n",ans);
	return 0;
}
```

### THE END

USACO 2024 Dec RP++.

---

## 作者：Jerrywang09 (赞：0)

题目中明确说了，单向直飞航班一定是 $(i,j)|i<j$。那么可以观察到线索：$(i,i+1)$ 的奇偶性就是 $(i,i+1)$ 是否有单向直飞航班。

有了这一点就好做了。倒序枚举 $i$，然后枚举 $j$，计算 $(i,j)$ 是否有单向直飞航班。枚举转折点 $k|i<k<j$，由于现在已经求得了 $(i,k)$ 是否有单向直飞航班，又已知 $(k,j)$ 的航线奇偶性，就可以知道所有中途需要换乘的 $(i,j)$ 航线奇偶性。如果刚才求得的奇偶性不同于输入的，则 $(i,j)$ 有单向直飞航班。

```cpp
// Title:  Flight Routes
// Source: USACO23DEC Gold
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=755;
using namespace std;

int n, par[N][N], g[N][N];

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    rep(i, 1, n) rep(j, i+1, n) scanf("%1d", &par[i][j]);
    int res=0;
    for(int i=n-1; i; i--)
    {
        if(par[i][i+1]) g[i][i+1]=1, res++;
        rep(j, i+2, n)
        {
            int sum=0;
            rep(k, i+1, j-1) if(g[i][k])
                sum^=par[k][j];
            if(sum!=par[i][j]) g[i][j]=1, res++;
        }
    }
    printf("%d", res);
    
    return 0;
}
```

---

## 作者：_zqh_ (赞：0)

$\mathcal O(n^3)$ 的做法。

一层一层地做。

记 $f(i,j)$ 为 $i$ 到 $j$ 是否直接有道路相连，$p(i,j)$ 为 $i$ 到 $j$ 的路径条数。

首先考虑形如 $(i, i + 1)$ 的两点是否连边。

因为多连边是无意义的，所以 $(i,i + 1)$ 的连边数量一定是 $1$ 或 $0$。

我们推广到 $(i, i + k)$ 的情况。

首先计算出原先 $i$ 到 $i + k$ 有多少条路径。

即：

$$
p(i,j) = \sum ^ {j - 1} _ {k = i - 1} f(i,k) \times p(k,j)
$$

不难想到，若上式若使用 $p(i,k) \times p(k,j)$ 会与之前计算的重复。

若此时 $p(i,j)$ 与要求奇偶性不同，再直接连一条 $i$ 到 $j$ 的路径即可。

```cpp
namespace zqh {
	int path[755][755];
	bool a[755][755], f[755][755];
	int n;

	void init() {
		cin >> n;
		rep (i, 1, n) {
			rep (j, i + 1, n) {
				char c;
				cin >> c;
				a[i][j] = c - '0';
			}
		}
	}

	void solve() {
		int ans = 0;
		rep (len, 1, n) {
			rep (i, 1, n - len) {
				int j = i + len;
				rep (k, i + 1, j - 1) path[i][j] += f[i][k] * path[k][j];
				if ((path[i][j] & 1) != a[i][j]) {
					ans++;
					path[i][j]++, f[i][j]++;
				}
			}
		}
		cout << ans;
	}
	void main() {
		init();
		solve();
	}
}  // namespace zqh
```

---

## 作者：Xiphi (赞：0)

一道类似区间 dp 的题。设 $a_{i,j}$ 表示 $i$ 到 $j$ 之间的方案数，$f_{i,j}$ 表示 $i$ 到 $j$ 时间是否有边。

我们可以通过计算不经过边 $x \to y$ 的情况下，$x$ 到 $y$ 路径方案的奇偶性，若其和 $a_{x,y}$ 不同，则必然会连边。

考虑如何计算这个东西，其显然为下式：
$$\sum_{i=x+1}^{y-1} f_{x,i} \times a_{i,y} \mod 2$$

然后又可以根据这个去求新的 $f_{x,y}$。于是现在的问题就是确定转移顺序，这个也是显然的，枚举路径长度，然后枚举起点 $x$，计算上上式子即可就求 $f_{x,y}$（记得这里还要在和 $a_{x,y}$ 异或）。最后统计一下有几条是可以连的输出即可。

```cpp
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
int n;
bool a[755][755];
int f[755][755];
signed main(){
//	freopen("*.in","r",stdin);
//	freopen("*.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);	
    cin>>n;
    _for(i,1,n){
    	_for(j,1,n-i){
    		char c;
    		cin>>c;
    		a[i][i+j]=c-'0';
    	}
    }
    int ans=0;
    _for(len,1,n-1){
    	_for(l,1,n){
    		int r=l+len;
    		if(r>n) break;
    		int cnt=0;
    		_for(i,l+1,r-1){
    			cnt+=f[l][i]*a[i][r];
    		}
    		cnt&=1;
    		f[l][r]=cnt^a[l][r];
    		ans+=f[l][r];
    	}
    }
    cout<<ans;
	return 0;
}
```

---

## 作者：_7thRC_CB_CRP_ (赞：0)

# Solution

首先我们得到的信息是奇偶性。我们肯定想的是先构造的不会因后构造的让答案改变，并且具有正确性。

那么我们尝试从第一个变量后往前枚举，并且再让第二个变量从前往后	枚举，分别作为其起点和终点。这样做的话前面确定的的答案就不会变。

那么，先判定。如果与给出条件不符合，那么就加上一条直接连上的边。当然，这要改变所有起点到终点后面的点的值，暴力改一下。复杂度 $O(n^3)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
bool vis[751][751];
bool vis1[751][751];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long n;
	cin>>n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j+i<=n;j++) {
			char c;
			cin>>c;
			vis[i][i+j]=c-'0';
		}
	long long ans=0;
	for(int i=n;i>=1;i--) {/*枚举起点*/
		for(int j=i+1;j<=n;j++) {/*枚举终点*/
			if(vis1[i][j]!=vis[i][j]) {/*查看是否与给出的信息不符*/
				ans++;/*进行修改*/
				vis1[i][j]=vis[i][j];
				for(int k=j+1;k<=n;k++) 
					vis1[i][k]^=vis1[j][k];/*同时改变起点到终点后面的点的答案*/
			}
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：wly09 (赞：0)

# 题目描述

给定一个 $N$ 个点的简单有向无环图，$i<j$ 是 $i$ 到 $j$ 存在有向边的必要条件。已知任意两点间路径条数的奇偶性，求原图的边数。
[传送门](https://www.luogu.com.cn/problem/P9980)

# 思路

先考虑一个简单的问题，注意到对于两个相邻的节点 $i,i+1$，可能存在的路径只有 $i\to i+1$。因此，如果两个相邻的节点间路径条数为偶数，它们间一定没有边（路径数为零）；反之，若路径条数为奇数，则一定有一条边。

现在假设我们已解决了所有 $i,i+j(j=1,2,\cdots,m-1)$ 间是否连边的问题，考虑 $i,i+m$ 间是否连边。从 $i$ 到 $i+m$ 共有两种方式：

* 先从 $i$ **直接**到 $i+j$，再从 $i+j$ 到 $i+m(j=1,2,\cdots,m-1)$；
* 直接从 $i$ 到 $i+m$。

假设已求出第一种方式的总路径（记为 $count$）。若 $count$ 的奇偶性与 $i,i+m$ 间路径奇偶性不符，说明 $i,i+m$ 间有连边；反之，$i,i+m$ 间没有直接相连的边。

因此，我们只需遍历所有 $j$，若 $i,i+j$ 间有一条边，就将 $i+j,i+m$ 间的路径条数累加进 $count$，然后检查 $count$ 的奇偶性。

由数学归纳法，以上方法可以求出原图的边数。

实现细节：任两个节点间的路径条数可能很大，即使用 `long long` 也可能超限；但我们不关心具体的路径条数，只需知道路径条数的奇偶性就能计算。

另外，使用 `unsigned` 存路径条数能给出正确答案，因为它在溢出时能保留数据的奇偶性。
 
# Code

```c++
#include <cstdio>
using namespace std;

char buf[1024];
char kk[1024][1024];
bool edges[1024][1024];

int main() {
  int n;
  long long res = 0;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%s", buf);
    for (int j = 0; i + j < n; ++j)
      kk[i][j + 1] = buf[j] ^ 48;
  }
  for (int j = 1; j < n; ++j) {
    for (int i = 1; i + j <= n; ++i) {
      int count = 0;
      for (int k = 1; k < j; ++k)
        if (edges[i][k])
          count ^= kk[i + k][j - k];
      if (kk[i][j] != (count & 1)) ++res, (edges[i][j] = true);
    }
  }
  printf("%lld\n", res);
  return 0;
}
```

---

## 作者：we_are_the_chuibing (赞：0)

### 思路

路线是从小的到大的点，可以从后往前确定。确定一个点 $x$，从后往前枚举 $y > x$，如果现在到 $y$ 的路线不符合奇偶性，就连一条边。

时间复杂度 $O (n^3)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 755;
int n;
char c[N][N];
int main(){
	cin>>n;
	for (int i=1; i<n; i++){
		for (int j=i+1; j<=n; j++){
			cin>>c[i][j];
		}
	}
	int ans=0;
	for (int i=n-1; i>=1; i--){
		vector<int> cnt(n+1,0);
		for (int j=i+1; j<=n; j++){
			if ((cnt[j]+(c[i][j]-'0'))&1){
				ans++;
				for (int k=j+1; k<=n; k++){
					cnt[k]+=c[j][k]-'0';
				}
			}
		}
	}
	cout<<ans<<endl; 
	return 0;
}
```


---

## 作者：kczw (赞：0)

# 题意
给定一个有 $n$ 个点有向图，只能从编号小的点到编号大的点。

现在告诉你每两个点之间路径数的奇偶，问一共有多少条两个点之间直接相连的边。
# 思路
首先，我们会发现，如果 $c-1$ 和 $c$ 之间路径数为奇的话，那他们之间一定是有直接相连的路径的。

这里详细解释下**为什么**（看懂的可以跳到下一段）。根据题意我们知道，从 $c-2$ 到 $c-1$ 再到 $c$ 也是一种路径，但是不可避免的，它会经过 $c-1$ 到 $c$ 的边，只有 $c-2$ 直接到 $c$，才不会对 $c-1$ 到 $c$ 的边有贡献。所以可得出结论，只要是 $c-1$ 和 $c$ 之间有路径，那么 $c-1$ 和 $c$ 之间一定有直接相连的边。

然后这个结论有什么用呢？

看到题目的一个限制，**只能从小编号点到大编号点**。那么 $n-1$ 是只能到 $n$ 的，我们可以直接推导出 $n-1$ 和 $n$ 之间是否有边。然后我们可以看到 $n-2$，我们可以直接判断出 $n-2$ 和 $n-1$ 之间是否有边，然后可以推出 $n-2$ 和 $n$ 之间是否有边。我们可以将这个推导的方式扩散到全局，最后得出答案。
# 实现
```cpp
#include<iostream>
using namespace std;
int ans,n,f[755][755],way[755][755];
char p;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
		cin>>p,f[i][j]=p-'0';
	for(int i=n-1,res;i>=1;i--)
	for(int j=i+1;j<=n;j++){
		res=0;
		for(int l=i+1;l<j;l++)if(way[l][j])res^=f[i][l];
		way[i][j]=f[i][j]^res;
		ans+=way[i][j];
	}printf("%d",ans);
	return 0;
} 
```

---

## 作者：mRXxy0o0 (赞：0)

# 分析

我们考虑题目中一个很强的限制：下标小的向下标大的连单向边。这意味着从 $n-1$ 号点出发的路线只有 $(n-1,n)$ 这一条。

尝试由此递推，若大于 $i$ 的路线全部确定了，那么当前 $i$ 到 $j$ 的路径数奇偶性就是确定的，由此可以推出 $(i,j)$ 的连边情况。

$O(n^3)$ 递推即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=800;
const ll inf=1e18;
int n,m,k,a[N][N],b[N][N],f[N],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			scanf("%1d",&a[i][j]);
		}
	}
	for(int i=n;i;--i){//start
		for(int j=i+1;j<=n;++j){//now
			int res=0;
			for(int k=i+1;k<j;++k){
				if(b[k][j]) res^=a[i][k];
			}
			b[i][j]=a[i][j]^res;
			ans+=b[i][j];
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

~~USACO 不就是用来水题解和 AC 数的~~

题意：一个 DAG，无重边，边都是从编号小连向编号大，已知任意两个点之间路径条数的奇偶性，求边数。

对于 $i$ 到 $j$ 是否有边，我们显然可以按照 $j-i+1$ 从小到大的顺序排列解决。每次枚举一个中间点 $k$，算出经过 $k$ 的路径数量并叠加在一起。

但是直接叠加容易导致一些问题。

比如说一条 $1-2-3-4$ 的路径，我们在算 $1$ 到 $4$ 的路径数量时，这条路径同时经过 $2$ 和 $3$，就有可能被算重。

为了避免这个问题，我们在枚举中间点 $k$ 时改为计算它是路径中倒数第二个节点的路径数量（最后一个是 $j$），这样就不会算重了。

把不考虑 $i$ 到 $j$ 的边的路径方案数算出来后，只要它奇偶性与预期不同就说明 $i$ 到 $j$ 有一条边，于是就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
bool mp[1005][1005];
bool cg[1005][1005];
int s[1005][1005],ans;
// mp 即输入内容，s 是不考虑 i 直接到 j，cg 代表是否存在边
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		char c;
		cin>>c;
		mp[i][j]=(c=='1');
	}
	for(int r=1;r<=n;r++)for(int l=r;l;l--){
		for(int i=l+1;i<r;i++)(s[l][r]+=cg[l][i]*s[i][r])%=2;// l 到 i 的路径条数乘 i 到 r 是否有边就是 i 作为倒数第二个点的方案数
		if(mp[l][r]^s[l][r])s[l][r]^=1,cg[l][r]=1,++ans;// 连一条边
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：SFlyer (赞：0)

注意到路线是从小的到大的点，因此可以从后往前确定。具体地说，确定一个点 $i$，从前往后枚举 $j>i$，如果现在到 $j$ 的路线个数不符合奇偶性，就连一条边。

很容易证明是正确的。$\mathcal{O}(N^3)$。


```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 755;

int n;
char c[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<n; i++){
		for (int j=i+1; j<=n; j++){
			cin>>c[i][j];
		}
	}
	int ans=0;
	for (int i=n-1; i>=1; i--){
		vector<int> cnt(n+1,0);
		for (int j=i+1; j<=n; j++){
			if ((cnt[j]+(c[i][j]-'0'))&1){
				ans++;
				for (int k=j+1; k<=n; k++){
					cnt[k]+=c[j][k]-'0';
				}
			}
		}
	}
	cout<<ans<<endl; 
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：0)

考虑直接求出所有城市之间的连边情况，再来统计出有多少条边。

从小到大枚举右端点 $i$，再从小到大枚举左端点 $j$，考虑数出从 $j$ 到 $i$ 不直飞的路径条数的奇偶性，若和输入不同则有边，否则无边。

因为是从小到大枚举右端点，所以在 $i$ 前面的连边情况已经确定。要统计不直达路径条数，枚举一条边对剩下的路径条数求和即可。枚举 $j$ 的出度 $k$，路径条数即为所有 $k$ 到 $i$ 路径条数之和。

时间复杂度 $O(n^3)$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=810;
int n,ans,f[N][N],e[N][N];
char str[N];
int main()
{
	n=read();
	for(int i=1;i<n;i++){
		scanf("%s",str+1);
		for(int j=1;j<=n-i;j++)
			f[i][i+j]=str[j]-'0';
	}
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++){
			int res=0;
			for(int k=j+1;k<i;k++)
				if(e[j][k])
					res=(res+f[k][i])%2;
			e[j][i]=abs(res-f[j][i]);
			ans+=e[j][i];
		}
	cout<<ans;
	return 0;
}
```

---

