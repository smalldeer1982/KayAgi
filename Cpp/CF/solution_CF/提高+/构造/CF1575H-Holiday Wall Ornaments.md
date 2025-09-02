# Holiday Wall Ornaments

## 题目描述

The Winter holiday will be here soon. Mr. Chanek wants to decorate his house's wall with ornaments. The wall can be represented as a binary string $ a $ of length $ n $ . His favorite nephew has another binary string $ b $ of length $ m $ ( $ m \leq n $ ).

Mr. Chanek's nephew loves the non-negative integer $ k $ . His nephew wants exactly $ k $ occurrences of $ b $ as substrings in $ a $ .

However, Mr. Chanek does not know the value of $ k $ . So, for each $ k $ ( $ 0 \leq k \leq n - m + 1 $ ), find the minimum number of elements in $ a $ that have to be changed such that there are exactly $ k $ occurrences of $ b $ in $ a $ .

A string $ s $ occurs exactly $ k $ times in $ t $ if there are exactly $ k $ different pairs $ (p,q) $ such that we can obtain $ s $ by deleting $ p $ characters from the beginning and $ q $ characters from the end of $ t $ .

## 说明/提示

For $ k = 0 $ , to make the string $ a $ have no occurrence of 101, you can do one character change as follows.

100101011 $ \rightarrow $ 100100011

For $ k = 1 $ , you can also change a single character.

100101011 $ \rightarrow $ 100001011

For $ k = 2 $ , no changes are needed.

## 样例 #1

### 输入

```
9 3
100101011
101```

### 输出

```
1 1 0 1 6 -1 -1 -1```

# 题解

## 作者：Little09 (赞：2)

先对 $b$ 跑一遍 KMP，建出它的 KMP 自动机。接下来考虑 DP。我们定义 $dp[i][j][k]$ 表示在 $a$ 串中做到位置 $i$，$b$ 串中匹配到位置 $j$（也是 KMP 自动机上的位置），目前已经匹配了 $k$ 个字符串 $b$，此时的最小代价。

转移的时候，枚举 $a_i$ 这位填了什么，在 KMP 自动机上找到下一个位置，进行转移。当位置到 $m$ 的时候，给 $k$ 加上 $1$，表示此时完成了一次匹配。这样转移是 $O(1)$ 的，时间复杂度 $O(n^3)$，空间复杂度可以通过滚动数组降到 $O(n^2)$，不过这题也不必要。

```cpp
const int N=505;
int n,m; 
int a[N],b[N],kmp[N],tran[N][2],dp[N][N][N];
void prefix_function()
{
	kmp[0]=-1;
	if (b[1]==0) tran[0][0]=1;
	else tran[0][1]=1;
	for (int i=1;i<=m;i++)
	{
		int j=kmp[i-1];
		while (j!=-1&&b[j+1]!=b[i]) j=kmp[j];
		kmp[i]=j+1;
		if (b[i+1]==0) tran[i][0]=i+1;
		else tran[i][0]=tran[kmp[i]][0];
		if (b[i+1]==1) tran[i][1]=i+1;
		else tran[i][1]=tran[kmp[i]][1];
	}
}

int main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=readchar()-'0';
	for (int i=1;i<=m;i++) b[i]=readchar()-'0';
	b[m+1]=2;
	prefix_function();
	memset(dp,20,sizeof(dp));
	dp[0][0][0]=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=m;j++)
		{
			for (int k=0;k<=n-m;k++)
			{
				for (int t=0;t<=1;t++)
				{
					int u=tran[j][t],v=k+(u==m);
					dp[i][u][v]=min(dp[i][u][v],dp[i-1][j][k]+(a[i]!=t));
				}
			}
		}
	}
	for (int i=0;i<=n-m+1;i++)
	{
		int ans=n+1;
		for (int j=0;j<=m;j++) ans=min(ans,dp[n][j][i]);
		if (ans==n+1) ans=-1;
		printf("%d ",ans);
	}
	return 0;
}

```


---

## 作者：_maze (赞：1)

vp 时这种题没做出来，有被菜到。



------------

要进行匹配，条件反射建出自动机。在这里选择的是 KMP 自动机（就是只有一个串的 AC 自动机啦）。

思考所谓变换的本质，就是在自动机上你可以直接沿着当前字符走到下一个状态，或者你可以用 $1$ 的代价沿着相反的字符走到下一个状态。这不是一眼动态规划，转移都给你准备好了。

我们建出 $f_{i,j,k}$ 表示 $a$ 串匹配到 $i$，$b$ 串匹配到 $j$，且已经匹配了 $k$ 个 $b$ 串的最小代价。按上面的方法 $O(n^3)$ 大力转移即可。

```cpp
#include <bits/stdc++.h>
#define forp(i, a, b) for (int i = (a);i <= (b);i ++)
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;
const ll maxn = 200005, maxk = 2;
int n, m;
int f[505][505][505];
class KMPAM{
	private:
		int cnt, to[maxn][maxk], link[maxn];
	public:
		void add(string s){
			int n = s.size();
			int u = 0;
			forp(i, 0, n - 1){
				int p = s[i] - '0';
				if(!to[u][p]) to[u][p] = ++ cnt;
				u = to[u][p];
			}
		}
		void build(){
			queue<int> q;
			forp(i, 0, 1) if(to[0][i]) q.push(to[0][i]);
			while(!q.empty()){
				int u = q.front();
				q.pop();
				forp(i, 0, 1){
					if(!to[u][i]) to[u][i] = to[link[u]][i];
					else link[to[u][i]] = to[link[u]][i],q.push(to[u][i]);
				}
			}
		}
		void dp(int n, string a, int m){
			forp(i, 0, n)
				forp(j, 0, m)
					forp(k, 0, n - m + 1)
						f[i][j][k] = 114514;
			f[0][0][0] = 0;
			forp(i, 1, n)
				forp(j, 0, m)
					forp(k, 0, n - m)
						forp(t, 0, 1){
							int x = a[i - 1] - '0';
							int u = to[j][t],v = k;
							if(u == m) v ++;
							if(x == t) f[i][u][v] = min(f[i][u][v], f[i - 1][j][k]);
							else f[i][u][v] = min(f[i][u][v], f[i - 1][j][k] + 1);
						}
		}
}A;
void print(int n, int m){
	forp(k, 0, n - m + 1){
		int ans = 114514;
		forp(j, 0, m) ans = min(ans, f[n][j][k]);
		if(ans == 114514) cout << -1 << ' ';
		else cout << ans << ' '; 
	}
	cout << endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	string a, b;
	cin >> a >> b;
	A.add(b);A.build();
	A.dp(n, a, m);
	print(n, m);
	return 0;
}


```


---

## 作者：Alex_Eon (赞：1)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1575h)

### 主体思路：ACAM/KMPAM+DP

### 复杂度：$O(n^3)$

### 完整思路

数据范围提示我们用 $O(n^3)$ 的算法来解决，这种匹配问题可以考虑放到 ACAM 或者 KMPAM 上，后者本质上是只添加一个字符串的前者。

很明显我们可以把串 $b$ 的 KMPAM 处理出来在上面跑 DP，具体地讲，需要处理出一个 $to_{i, j}$ 表示匹配到 $b$ 的 KMPAM 的状态 $i$ 时，下一个字符为 $j$ 时，应该转移到的状态。

当 $j = b_{i +1}$ 时，有 $to_{i, j} = i + 1$，否则有 $to_{i, j} = to_{nex_i, j}$。

具体求法可以参考 ACAM 求 fail 的过程，我写 KMP 的版本的时候写挂了，所以干脆换成 ACAM 的处理方式处理出了 $to$ 数组。

接下来考虑 DP，设 $f_{i, j, k}$ 表示 $a$ 匹配到第 $i$ 个字符，当前在 $b$ 的 $j$ 状态下，$b$ 已经完全匹配过 $k$ 次的最小代价。

我很难知道有哪些 $to_{p, q} = j$ 所以填表法在第二维上是困难的，所以第二维用刷表法处理，另外第一维是线性的，第三维刷表填表都是可行的，因为只与 $[to_{j, ch} = m]$ 的值有关（$ch$ 是枚举的 $a_i$）。

每次 $f_{i, to_{j, ch}, k +[to_{j, ch} = m]} \leftarrow \min\{f_{i, to_{j, ch}, k +[to_{j, ch} = m]}, f_{i - 1, j, k} + [a_i \not= ch]\}$ 即可。

### 参考代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 500 + 5;

int n, m, nex[N], to[N][2];
char a[N], b[N];

int f[N][N][N];

void init() {
    for (int i = 1; i <= m; i++)
        to[i - 1][b[i] - '0'] = i;
    for (int i = 1; i <= m; i++) {
        for (int ch = 0; ch < 2; ch++)
            if (!to[i][ch])
                to[i][ch] = to[nex[i]][ch];
            else
                nex[to[i][ch]] = to[nex[i]][b[i + 1] - '0'];
    }
    // for (int i = 0; i <= m; i++)
    //     printf("%d %d %d\n", nex[i], to[i][0], to[i][1]);
}
//--------------------//
int main() {
    scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
    init();
    memset(f, 0x3f, sizeof(f));
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= n - m; k++)
                for (int ch = 0; ch < 2; ch++) {
                    f[i][to[j][ch]][k + (to[j][ch] == m)] = min(f[i][to[j][ch]][k + (to[j][ch] == m)], f[i - 1][j][k] + (a[i] - '0' != ch));
                    // printf("%d %d %d %d\n", i, to[j][ch], k + (to[j][ch] == m), f[i][to[j][ch]][k + (to[j][ch] == m)]);
                }
    for (int ans, i = 0; i <= n - m + 1; i++) {
        ans = 114514;
        for (int j = 0; j <= m; j++)
            ans = min(ans, f[n][j][i]);
        if (ans == 114514)
            ans = -1;
        printf("%d ", ans);
    }
    return 0;
}

```



---

