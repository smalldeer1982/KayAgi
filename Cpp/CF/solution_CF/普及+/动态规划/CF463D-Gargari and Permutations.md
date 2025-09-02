# Gargari and Permutations

## 题目描述

给你k个长度为n的排列，求这些排列的最长公共子序列的长度

## 说明/提示

第一个测试样本的答案是子序列[1,2,3]。

## 样例 #1

### 输入

```
4 3
1 4 2 3
4 1 2 3
1 2 4 3
```

### 输出

```
3
```

# 题解

## 作者：Juanzhang (赞：19)

$dp$

这里给出另外一种思路

我们把每个数出现位置记下来

若在所有排列中，$i$ 都在 $j$ 的左边，那么就可以进行 $i$ 到 $j$ 的转移

因此我们对所有满足条件的 $(i,j)$ 连一条有向边，易发现该图是个 $\operatorname{DAG}$，因此只需跑一条最长路即可

代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
int n, m, h[maxn], f[maxn], pos[maxn]; bool flg[maxn][maxn];
vector <int> g[maxn];

int dfs(int u) {
	if (~f[u]) return f[u]; f[u] = 0;
	for (int v : g[u]) f[u] = max(f[u], dfs(v));
	return ++f[u];
}

int main() {
	scanf("%d %d", &n, &m);
	memset(f, -1, sizeof f);
	memset(flg, 1, sizeof flg);
	for (int k = 0; k < m; k++) {
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x), pos[x] = i;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				flg[i][j] &= pos[i] < pos[j];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (flg[i][j]) g[i].push_back(j);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, dfs(i));
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：傅思维666 (赞：5)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11777306.html)

~~2019.11.1模拟赛T2 20分场~~

首先阐明一个重要至极的性质：这个东西是排列，并不是数列。

排列数列的区别就是，排列就是$1-n$这些数变换顺序，而数列是$n$个你也不知道是多大的数变换顺序。

那么我们就会发现这样的一个性质：对于每一个排列，是否能为最大公共子序列长度做出贡献的决定因素仅是这些数的排列顺序。

回顾一下我们最长公共子序列的模板，为了保证转移的正确性，我们采取的是对于每一个数，遍历它之前的所有的数这种方法，是$O(n^2)$的。那么对于这道题，我们只需要记录下来每个数在每行中出现的位置。那么我们发现：我们只看第一个排列，枚举这个排列中每个数在所有行上的位置。假如相对位置都一样，即对于所有的数列，都有$pos[i]\ge pos[j]$，那么它就可以为答案做出贡献。

所以我们用一个$flag$判断是否需要转移。最后遍历一次统计一下答案即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n,m,ans;
int a[20][maxn],pos[20][maxn],dp[maxn];
//a数组存原数，pos数组存位置
//dp[i]表示以i结尾的最长公共子序列长度
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            pos[i][a[i][j]]=j;
        }
    for(int i=1;i<=n;i++)
        dp[i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
        {
            int x=a[1][i];
            int y=a[1][j];
            int flag=1;
            for(int t=2;t<=m && flag;t++)
                if(pos[t][x]<pos[t][y])
                    flag=0;
            if(flag)
                dp[x]=max(dp[x],dp[y]+1);
        }
    ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i]);
    printf("%d",ans);
    return 0;
}
```



---

## 作者：JK_LOVER (赞：4)

## 题意
给你 $m$ 个长度为 $n$ 的排列，求问最长的公共子序列的长度。
## 分析
- 先考虑 $n = 2$ 的特殊情况。我们先定义 $dp[x]$ 是以数字 $x$ 为开头的最长的公共子序列的长度。那么则有：
$$
dp[x] =\begin{cases}1\\ dp[y]+1 (pos[1][x]<pos[1][y] \&\&pos[2][x]<pos[2][y]  )\end{cases}
$$
- 将其推广到 $m\ge2$ 的情况。

那么必须在 $m$ 个排列之中全部满足
$$
pos[i][x] <pos[i][y] \Rightarrow dp[x] = \max(dp[y]+1,dp[x])
$$
才能转移。

- 考虑用有向无环图的 $dp$ 来转移。最后 $dp$ 的时间复杂度为 $O(n)$ 。因为每个点只会记录一次。总的时间复杂度为 $O(mn^2)$ 。瓶颈在于怎样快速建边。

建边要满足 $pos[i][x]<pos[i][y] (1\le i\le m)$ 。所以其实则是个 $m$ 维的偏序问题。如果用树套树套树...CDQ套CDQ....复杂度为 $O(nm \log^{m-1}n)$ 。常数也爆表。所以 $O(mn^2)$ 在 $n\le1000$ 时是可以接受的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
const double eps = 1e-8;
int read()
{
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n,m,pos[7][N],dp[N];
vector<int> G[N];
int dfs(int x)
{
	if(dp[x]) return dp[x];
	dp[x] = 1;
	for(int i = 0;i < G[x].size();i++)
	{
		dp[x] = max(dfs(G[x][i])+1,dp[x]);
	}
	return dp[x];
}
int main()
{
	n = read();m = read();
	for(int j = 1;j <= m;j++)
	{
		for(int i = 1;i <= n;i++)
		{
			int a = read();
			pos[j][a] = i;
		}
	}
	for(int j = 1;j <= n;j++)
	{
		for(int k = 1;k <= n;k++)
		{
			for(int i = 1;i <= m;i++)
			{
				if(pos[i][j] >= pos[i][k]) break;
				if(i == m)
				{
					G[j].push_back(k);
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i++)
	{
		ans = max(ans,dfs(i));
	}	
	printf("%d\n",ans);
	return 0;
}

```

[欢迎来踩](https://www.luogu.com.cn/blog/xzc/solution-cf463d)



---

## 作者：ZJle (赞：2)

### CF463D 题解
一道挺好的 DP 题。

最长公共子序列大家都会求：
$$
f(i,j)=\begin{cases}f(i-1,j-1)+1&A_i=B_j\\\max(f(i-1,j),f(i,j-1))&A_i\ne B_j\end{cases}
$$

但是本题有 $k$ 组数据,因此我们需要在此基础上于次算法进行魔改。

题意为：求 $k$ 个长度为 $n$ 的最长公共子序列。

由于这个串中有 $n$ 个数，并且只有 $n$ 种数，我们可以考虑每个数的位置。

并且我们知道所得的最长公共子序列一定在第一个序列中，我们枚举第一个串的可能，然后检查在每个串中,$s_i$ 的位置是否在 $s_j$ 的位置之前, 如果对于一个成立的子串，那么每个 $s_i$ 都会在 $s_j$ 的前面，由此，我们可以得到 DP 式子：

$dp_i=\max(dp_{i}+1,dp_j)$

最后，答案就是以 $s$ 种的哪个数作为结尾的最大值。

上代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int pos[10][1006], s[10][1006], f[1006];
int x,y;
void file()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}
signed main()
{
    file();
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> s[i][j];
            pos[i][s[i][j]] = j;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            bool ztxmd = true;
            for (int op = 2; op <= k; op++)
            {
                if (pos[op][x] > pos[op][y])
                {
                    ztxmd = false;
                    break;
                }
            }
            if (ztxmd)
            {
                f[j] = max(f[j], f[i] + 1);
            }
        }
    }
    int ans = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i]);
    }
    cout << ans;
}
```

---

## 作者：FP·荷兰猪 (赞：2)

题意:k个1~n的排列,求这k个排列的LCS.k<=5,n<=1000.

~~一看就是个dp~~

因为序列为排列,设dp[x]以x结尾能得到最长的LCS.
当x出现k次时，说明x能作为结尾，枚举能接在其前面的数即可 O(k*n^2)。

**水过：**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+10;
int dp[N],a[N][N],pos[N][N],cnt[N];
vector<int> ans;

int main()
{
	int n,k;
	cin>>n>>k;
	int i,j,res=0;
	ans.clear();
	for(i=1;i<=k;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j],pos[i][a[i][j]]=j;
	memset(dp,0,sizeof(dp));
	memset(cnt,0,sizeof(cnt));
	ans.push_back(0);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=k;j++)
		{
			int x=a[j][i];
			cnt[x]++;
			if(cnt[x]==k)
			{
				for(int p=0;p<ans.size();p++)
				{
					int y=ans[p];
					bool flag=1;
					for(int q=1;q<=k;q++)
					{
						if(pos[q][y]>=pos[q][x])
							flag=0;
					}
					if(flag)
						dp[x]=max(dp[x],dp[y]+1),res=max(res,dp[x]);
				}
				ans.push_back(x);	
			}
		}
	}
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：Weng_Weijie (赞：1)

题解：

将 $k$ 个排列中每个元素的位置记录下来

如果是公共子序列，那么这些数的位置在 $k$ 个排列中都是递增的

然后就变成了一个 $k$ 维偏序问题

然而良心的出题人 $n \leq 1000$ ，因此就可以直接dp, 不需要CDQ套CDQ套CDQ套树状数组~~或者树套树套树套树~~

代码：
```cpp
#include <cstdio>
#include <algorithm>
#define N 1005 
int pos[5][N], p[5][N], n, k, x, f[N];
int main() {
	std::scanf("%d%d", &n, &k);
	for (int i = 0; i < k; i++)
		for (int j = 1; j <= n; j++) std::scanf("%d", &p[i][j]), pos[i][p[i][j]] = j;
	for (int i = 1; i <= n; i++) f[i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++) {
			int v = p[0][i], u = p[0][j];
			int flag = 1;
			for (int t = 1; t < k && flag; t++) if (pos[t][v] < pos[t][u]) flag = 0;
			if (flag) f[v] = std::max(f[v], f[u] + 1);
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
	std::printf("%d\n", ans); 
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

首先明确两两求出 LCS 再跟下一个求的这种方法是错误的。

例如：

```
3
5 8 6 7 9
1 6 5 8 7
6 7 2 3 4
```

发现前两个求出来是 ```5 8 7``` 与第三个求出来答案是 1，但明显可以是 ```6 7 ``` 答案更优是 2，虽然和题目描述不太一样但也说明不能这么求。

于是考虑转移发现只有一种可能：在所有序列中相对位置一样，也就是对于每一个 $k$ 都有 $ p_{k,i} < p_{k,j}$ 那么 $i$ 元素对应的位置才可以转移到 $j$ 元素对应的位置。其中 $p_{i,j}$ 表示在第 $i$ 个序列里元素 $j$ 的位置。

最后按照上述规则转移即可。不太像 LCS 反而有点像 LIS 了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,dp[1010],arr[7][1010],p[7][1010];
bool can(int x,int y){
	for(int l=1;l<=k;l++) if(p[l][x]>p[l][y]) return false;
	return true;
}
signed main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&arr[i][j]);
			p[i][arr[i][j]]=j;
		}
	}
	for(int i=1;i<=n;i++) dp[i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
            if(can(arr[1][j],arr[1][i])) dp[i]=max(dp[i],dp[j]+1);
		}
	}
	ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	printf("%d",ans);
    return 0;
}

```

---

