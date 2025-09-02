# Sereja and Two Sequences

## 题目描述

Sereja has two sequences $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{m} $ , consisting of integers. One day Sereja got bored and he decided two play with them. The rules of the game was very simple. Sereja makes several moves, in one move he can perform one of the following actions:

1. Choose several (at least one) first elements of sequence $ a $ (non-empty prefix of $ a $ ), choose several (at least one) first elements of sequence $ b $ (non-empty prefix of $ b $ ); the element of sequence $ a $ with the maximum index among the chosen ones must be equal to the element of sequence $ b $ with the maximum index among the chosen ones; remove the chosen elements from the sequences.
2. Remove all elements of both sequences.

The first action is worth $ e $ energy units and adds one dollar to Sereja's electronic account. The second action is worth the number of energy units equal to the number of elements Sereja removed from the sequences before performing this action. After Sereja performed the second action, he gets all the money that he earned on his electronic account during the game.

Initially Sereja has $ s $ energy units and no money on his account. What maximum number of money can Sereja get? Note, the amount of Seraja's energy mustn't be negative at any time moment.

## 样例 #1

### 输入

```
5 5 100000 1000
1 2 3 4 5
3 2 4 5 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4 3006 1000
1 2 3
1 2 4 3
```

### 输出

```
2
```

# 题解

## 作者：aoeiuv (赞：0)

暴力 $\mathcal{O}(nm)$ 的 DP 就是记 $f_{i,j}$ 表示删掉 $a$ 的前 $i$ 个，$b$ 的前 $j$ 个最多可以操作多少次。

观察到 $\dfrac{s}{t}$ 其实很小，所以最大的操作次数只有 $300$，那么就可以将 DP 记录的信息换一换！记 $f_{i,j}$ 表示删掉 $a$ 的前 $i$ 个，操作了 $j$ 次，$b$ 最小删到了哪个位置。

首先，$f_{i,j}$ 可以从 $f_{i,j-1}$ 转移过来，相当于第 $j$ 次没操作。如果第 $j$ 次选择删掉一段，那么肯定要从选择第 $j-1$ 次操作删掉最靠左的 $b$ 的位置的右边，找一个最靠左的 $a_i$ 转移。

对于第 $j-1$ 次操作删掉最靠左的 $b$ 的位置，可以用一个数组辅助维护（注意要倒序遍历或者放在外层循环更新，不然会算重）。要查找最靠左的 $a_i$ 的位置，可以用一个 `vector` 记录下 $b$ 数组每个值出现的位置，转移的时候用 `upper_bound` 查找一下。

时间复杂度 $\mathcal{O}(\dfrac{s}{t}n\log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n,m,S,T,a[N],b[N],f[N][305],mi[N];

vector<int> g[N];

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p1 = buf, p2 = (p1 + fread(buf, 1, 1 << 21, stdin))) == p1 ? EOF : *p1++)
inline int read() { int x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
inline void write(int x) { if (!x) return; write(x / 10), putchar((x % 10) ^ '0'); }

int main(){
    n = read(), m = read(), S = read(), T = read();
    for (int i = 1;i <= n;i++) a[i] = read();
    for (int i = 1;i <= m;i++) b[i] = read(), g[b[i]].push_back(i);
    int ans = 0;
    memset(f,0x3f,sizeof(f));
    memset(mi,0x3f,sizeof(mi));
    mi[0] = f[0][0] = 0;
    for (int i = 1;i <= n;i++){
        for (int j = 1;j <= min(i,S / T);j++){
            int p = upper_bound(g[a[i]].begin(),g[a[i]].end(),mi[j - 1]) - g[a[i]].begin();
            if (p == g[a[i]].size()) continue;
            f[i][j] = g[a[i]][p];
            if (j * T + i + f[i][j] <= S)
                ans = max(ans,j);
        }
        for (int j = 1;j <= min(i,S / T);j++) 
            mi[j] = min(mi[j],f[i][j]);
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
这题是不是有点水啊，好像挺一眼的，但是我没看清数据范围给硬控了。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
我们考虑肯定是删掉最少数量的数，并且操作次数尽可能大。

观察数据范围就可以发现，我们的操作次数不会超过 $300$ 次。

那么考虑设计 $f_{i,j}$ 表示第一个序列删到第 $i$ 个数，操作了 $j$ 次，第二个序列最小删到第 $f_{i,j}$ 个数。

那么只需要满足 $j\cdot e+i+f_{i,j}\le s$，答案就可以取到 $j$。

考虑怎么转移这个 dp。

首先 $f_{i,j}=f_{i-1,j}$ 是显然的，接着我们考虑从一个点 $f_{k,j-1}$ 转移到 $f_{i,j}$，即为在 $f_{k,j-1}$ 这个位置后再找到第一个 $b_x=a_i$，$f_{i,j}$ 即为 $x$。

后面的那个实现可以考虑对于每种数开个 vector 然后二分。

目前唯一的问题便在选择 $f_{k,j-1}$ 上。

不难发现，我们只需要让 $f_{k,j-1}$ 最小即可保证最优，没必要在意 $k$。

所以对于每一个 $j$ 转移的同时做个前缀最小值即可。
## 代码

```cpp
#include<bits/stdc++.h>
#define get(x,y) (e[y][upper_bound(e[y].begin(),e[y].end(),x)-e[y].begin()])
#define int long long
using namespace std;
const int N=1e5+10,V=1e5,M=310,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,k,s,q,ans,a[N],f[N][M],mn[N][M];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read(),m=read(),s=read(),q=read();k=s/q;memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++) a[i]=read();memset(mn,0x3f,sizeof mn);
    for(int i=1;i<=m;i++) e[read()].emplace_back(i);mn[0][0]=f[0][0]=0;
    for(int i=1;i<=V;i++) e[i].emplace_back(INF+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=min(i,k);j++)
        {
            f[i][j]=min(f[i-1][j],get(mn[i-1][j-1],a[i]));
            mn[i][j]=min(mn[i-1][j],f[i][j]);
            if(j*q+i+f[i][j]<=s) ans=max(ans,j);
        }mn[i][0]=0;
    }print(ans);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：SFlyer (赞：0)

没有什么题解，交一发！

发现这个 $e$ 的范围有一点唐，然后发现 $\frac{s}{e}\le 300$，也就是最多操作 $300$ 次。

设 $dp_{j,i}$：$a$ 删了 $1\sim i$，操作了 $j$ 次了，最小 $b$ 删到了哪儿。

考虑转移。$dp_{j,i}$ 可以从 $dp_{j-1,k<i}$ 转移过来，我们发现我们只要知道 $dp_{j-1,k<i}$ 的最小值就一定是最优的。这个可以前缀 $\min$ 维护。最后二分一下 $\min \{dp_{j-1,k<i}\}$ 后面 $b$ 中第一个 $a_i$ 下标即可。

复杂度 $\mathcal{O}(\frac{s}{e}n\log n)$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+5;
const int M = 303;

int n,m,s,e,a[N],b[N];
vector<int> g[N];
int dp[M][N],mn[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m>>s>>e;
	for (int i=1; i<=n; i++){
		cin>>a[i];
	}
	for (int i=1; i<=m; i++){
		cin>>b[i];
		g[b[i]].push_back(i);
	}
	memset(dp,0x3f,sizeof dp);
	int inf=dp[0][0]; 
	dp[0][0]=0;
	for (int t=1; t<M; t++){
		mn[0]=dp[t-1][0];
		for (int i=1; i<=n; i++){
			mn[i]=min(dp[t-1][i],mn[i-1]);
		}
		for (int i=1; i<=n; i++){
			if (g[a[i]].empty()){
				continue;
			}
			int ps=mn[i-1];
			int pos=lower_bound(g[a[i]].begin(),g[a[i]].end(),ps)-g[a[i]].begin();
			while (pos<g[a[i]].size() && g[a[i]][pos]<=ps){
				pos++;
			}
			if (pos<g[a[i]].size() && g[a[i]][pos]>ps){
				dp[t][i]=g[a[i]][pos];
			}
		}
	}
	int ans=0;
	for (int t=1; t<M; t++){
		for (int i=1; i<=n; i++){
			if (dp[t][i]==inf) continue;
			int nd=t*e+i+dp[t][i];
			if (nd<=s){
				ans=max(ans,t);
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

