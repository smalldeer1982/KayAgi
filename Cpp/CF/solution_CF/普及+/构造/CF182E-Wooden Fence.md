# Wooden Fence

## 题目描述

Vasya has recently bought some land and decided to surround it with a wooden fence.

He went to a company called "Wooden board" that produces wooden boards for fences. Vasya read in the catalog of products that the company has at its disposal $ n $ different types of wood. The company uses the $ i $ -th type of wood to produce a board of this type that is a rectangular $ a_{i} $ by $ b_{i} $ block.

Vasya decided to order boards in this company and build a fence from them. It turned out that the storehouse of the company is so large that Vasya can order arbitrary number of boards of every type. Note that Vasya is allowed to turn the boards as he builds the fence. However, Vasya cannot turn square boards.

Vasya is required to construct a fence of length $ l $ , however, an arbitrary fence won't do. Vasya wants his fence to look beautiful. We'll say that a fence is beautiful if and only if the following two conditions are fulfilled:

- there are no two successive boards of the same type
- the first board of the fence has an arbitrary length, and the length of each subsequent board equals the width of the previous one

In other words, the fence is considered beautiful, if the type of the $ i $ -th board in the fence is different from the $ i-1 $ -th board's type; besides, the $ i $ -th board's length is equal to the $ i-1 $ -th board's width (for all $ i $ , starting from 2).

Now Vasya wonders, how many variants of arranging a fence for his land exist. Your task is to count the number of different beautiful fences of length $ l $ .

Two fences will be considered the same if the corresponding sequences of fence boards types and rotations are the same, otherwise the fences are different. Since the sought number can be large enough, you need to calculate the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample there are exactly two variants of arranging a beautiful fence of length 3:

- As the first fence board use the board of the first type of length 1 and width 2. As the second board use board of the second type of length 2 and width 3.
- Use one board of the second type after you turn it. That makes its length equal 3, and width — 2.

## 样例 #1

### 输入

```
2 3
1 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 2
2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 6
2 1
3 2
2 5
3 3
5 1
2 1
```

### 输出

```
20
```

# 题解

## 作者：pythoner713 (赞：6)

$$\text{题目大意}$$

给定 $n$ 种木板，每种木板有长度和宽度 $a_i,b_i$。

现在需要从中选一些木板，拼成长度总和为 $l$ 的栅栏，每种木板可以使用无限次。注意你可以将一块木板旋转 $90^\circ$，使其长度和宽度对调，但这不会改变它的种类。

建出的栅栏要求相邻两块木板：

- 种类不能一样
- 前者的长度需等于后者的宽度

请你求出有多少种建栅栏的方案数。答案对 $10^9+7$ 取模。


---

这题可以用 DP 解决。记 $f[i][j]$ 表示**当前栅栏长度为 $i$，最后一块木板种类为 $j$ 的方案数**。

对于每一种木板，若其不是正方形，则可以将其拆为长宽分别为 $(a,b)$ 和 $(b,a)$ 的两种木板。但是根据限制条件一，DP 时不能通过这两种木板转移。拆分时需要记录下每种木板**原来的种类** $c_i$。

枚举上一块木板的种类 $k$，可以得到转移方程：

$$f[i][j]=\sum f[i-a_j][k]$$
$$a_j=b_k, c_j\ne c_k$$

```cpp
#include<bits/stdc++.h>
#define p 1000000007
#define nb 210
using namespace std;

int ans, n, l, cnt, a[nb], b[nb], c[nb], f[3010][nb];

// f[i][j] = 当前长度为 i, 最后一块木板为 j 的总方案数
// f[i][j] += f[i - a[j]][k] (a[j] = b[k], c[j] != c[k])

int main(){
	cin >> n >> l;
	for(int i = 1; i <= n; i++){
		c[++cnt] = i;
		cin >> a[cnt] >> b[cnt];
		if(a[cnt] != b[cnt]){
			c[++cnt] = i;
			a[cnt] = b[cnt - 1];
			b[cnt] = a[cnt - 1];
			// 如果不是正方形，将其拆成两种木板
			// 但原来的木板种类仍为 i 
		}
	}
	for(int i = 1; i <= l; i++){
		for(int j = 1; j <= cnt; j++){
			for(int k = 0; k <= cnt; k++){
				if(c[j] == c[k]) continue;		// 若种类相同则跳过 
				if(!k && a[j] == i) f[i][j]++;	// k = 0 代表当前已是第一块木板 
				else if(a[j] == b[k] && i > a[j]){
					// 根据限制条件二, a[j] = b[k] 
					f[i][j] = (f[i][j] + f[i - a[j]][k]) % p;
				}
			}
		}
	}
	for(int i = 1; i <= cnt; i++) ans = (ans + f[l][i]) % p;
	cout << ans;
	return 0;
}
```

---

## 作者：_segmenttree (赞：1)

## 思路

很简单的一个动态规划，我们分析一下两个条件就可以得出状态和转移式。第一个条件种类不能一样，那么我们应该有一维关于种类。第二个条件要求长度等于前一个宽度，那么长度宽度我们肯定要记一个。由于输出长度，我就把一维设为长度。因为它可旋转，我们还应该加一维表示长是 $a_i$ 或 $b_i$。所以得到 $dp_{i,j,2}$ 表示现在放的种类为 i,长度为 j,长是 $a_i$ 或 $b_i$。

要注意一下如果 $a_i$ 等于 $b_i$ 千万不要算重。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
const int mod = 1000000007;
int dp[3005][110][2],a[110],b[110];
signed main() {
    int n,l;
    scanf("%lld%lld",&n,&l);
    for(int i=1;i<=n;i++) 
	    scanf("%lld%lld",&a[i],&b[i]);
    for(int i=1;i<=l;i++)
        for(int j=1;j<=n;j++) {
            if(a[j]==i) dp[i][j][0]++;
            if(b[j]==i) dp[i][j][1]++;
        }
    for(int i=1;i<=l;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            {
                if(j==k) continue;
                if(a[j]==a[k]&&i>a[j]&&dp[i-a[j]][k][1]) dp[i][j][0]=(dp[i][j][0]+dp[i-a[j]][k][1])%mod;
                if(a[j]==b[k]&&i>a[j]&&a[k]!=b[k]&&dp[i-a[j]][k][0]) dp[i][j][0]=(dp[i][j][0]+dp[i-a[j]][k][0])%mod; 
                if(b[j]==b[k]&&i>b[j]&&dp[i-b[j]][k][0]) dp[i][j][1]=(dp[i][j][1]+dp[i-b[j]][k][0])%mod;
                if(b[j]==a[k]&&i>b[j]&&a[k]!=b[k]&&dp[i-b[j]][k][1]) dp[i][j][1]=(dp[i][j][1]+dp[i-b[j]][k][1])%mod; 
            }
    int ans=0;
    for(int i=1;i<=n;i++) {
        ans+=dp[l][i][0],ans%=mod;
        if(a[i]!=b[i]) ans+=dp[l][i][1],ans%=mod;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：C6H14 (赞：1)

## 一点废话

[%%%WXC学长](https://www.luogu.com.cn/blog/pythoner713/solution-cf182e)

[题目传送门](https://www.luogu.com.cn/problem/CF182E)

[My blog](https://www.luogu.com.cn/blog/128433/#)

看到学校集训以前的题单，扒过来练题，补到这题做完后一看题解发现是WXC写的……

## 思路

显然可以DP

定义$f[i][j][0/1]$为拼出长度为$i$的栅栏，最后一块栅栏是第$j$种木板，没有/有转$90 ^\circ$的方案数，第i种栅栏的长为$a_i$，宽为$b_i$。

特别的，j=0表示当前为第一块木板。

状态转移方程有些复杂……

先定义$[P]=\begin{cases}0 & P\text{为假}\\ 1 & P\text{为真}\end{cases}$，其中P是一个命题。

考虑去掉最后一块木板后的情况：

1. 去掉后没木板了，也就是这是唯一一块木板，那么方案数加$1$；

1. 去掉后有木板，枚举是哪种木板，只要不是同种木板且符合限制条件就累加到当前方案数

状态转移方程：

$f[i][j][0]=\begin{cases} \sum_{k=1,k \neq j}^n (f[i-a_j][k][0]*[a_j==b_k]+f[i-a_j][k][1]*[a_j==a_k])+[a_j==i]\end{cases}$

$f[i][j][1]=\begin{cases} \sum_{k=1,k \neq j}^n (f[i-b_j][k][0]*[b_j==b_k]+f[i-b_j][k][1]*[b_j==a_k])+[b_j==i]\end{cases}$

时间复杂度为$O(l*n^2)$

## 代码

```cpp
const ll maxn=1000000007;
ll n,l,a[105],b[105],f[3005][105][2],ans;
int main()
{
	n=read(),l=read();
	for (register int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	for (register int i=1;i<=l;++i)//枚举栅栏总长度
		for (register int j=1;j<=n;++j)//枚举最后一块木板的种类
			for (register int k=0;k<=n;++k)//枚举倒数第二块木板的种类，k=0含义如上
				if (j!=k)
				{
					if (!k && a[j]==i)//去掉后没木板了
						++f[i][j][0];
					else//还有木板
					{
						if (i>a[j] && a[j]==b[k])
							f[i][j][0]=(f[i][j][0]+f[i-a[j]][k][0])%maxn;
						if (i>a[j] && a[j]==a[k])
							f[i][j][0]=(f[i][j][0]+f[i-a[j]][k][1])%maxn;
					}
					if (a[j]==b[j])//长宽相同的转不转一样
						continue;
					if (!k && b[j]==i)//将木板旋转
						++f[i][j][1];
					else
					{
						if (i>b[j] && b[j]==b[k])
							f[i][j][1]=(f[i][j][1]+f[i-b[j]][k][0])%maxn;
						if (i>b[j] && b[j]==a[k])
							f[i][j][1]=(f[i][j][1]+f[i-b[j]][k][1])%maxn;
					}
				}
	for (register int i=1;i<=n;++i)
		ans=(ans+f[l][i][0]+f[l][i][1])%maxn;
	write(ans);
	return 0;
}
```


---

## 作者：Graph_Theory (赞：0)

### 确定算法
对于这道题来讲，首先让我们确定用什么算法。

考虑到神奇的操作以及只需求出方案数，~~并且看到了动态规划标签~~，且当前的方案数量可以推出下一个方案数量，所以大概是一道动态规划。

### 状态定义

状态定义较简单，既然要考虑到所有情况，所以我们定义 $dp_{l,i}$ 表示长度为 $len$ 时，最后一个木板种类为 $i$ 时的方案数量。

### 状态转移

建议大家看完定义之后先自己思考转移方法。

到这一部分时，因为木板可以横着用又可以竖着用，所以我们可以对非正方形的木板重复加入数组，但因为木板横着放和竖着放是一类物品，所以我们还需要一个数组 $num$ 记录一下当前木板的种类是什么。

对于第 $i$ 个木板想要达到长度 $len$ 时，此时到这一步的答案为上一块满足题目两种条件的木板 $j$，且达到长度为 $len-a_i$ 时的方案数量，也就是 $dp_{len-a_i,j}$ 的总和。

所以转移方程就是：

$$
dp_{len,i}=\sum_{j=0}^{n} dp_{len-a_i,j}
$$
$$
num_j \ne num_i,a_i=b_j
$$

### 最终状态

此时的最终状态就是所有 $dp_{l,j}$ 的和，也就是长度为 $l$ 最长下，任意种类木板为最后一块木板的种类之和。

所以最终状态是：
$$
ans=\sum_{j=0}^{n} dp_{l,j}
$$

---

## 作者：Special_Tony (赞：0)

# 思路
一眼 dp。

先定义一下状态：$dp_{i,j,k}$ 表示最后选了第 $i$ 块木板，用了 $j$ 长度，旋转状态为 $k$。然后显然可以先枚举当前状态，再枚举上一次是由谁转移过来的（只要枚举 $lsti,lstk$ 就行，因为 $lstj$ 是可以由 $i,j,k$ 倒推回去的），再判断是否合法即可。

至于状态转移方程，我们设 $a_{i,0}$ 是原长度，$a_{i,1}$ 是原宽度，则 $dp_{i,j,k}=\sum dp_{lsti,j-a_{i,k},lstk}$。

注意一下要先以 $j$ 为第一维，因为更新时，只有用小 $j$ 更新大 $j$，而 $i,k$ 则可能互相更新，不好搞。

时间复杂度 $O(n^2l)$，绝不会爆。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <char, int> pci;
const int mod = 1e9 + 7;
int n, m, dp[105][3005][2], a[105][2], sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 0; i < n; ++ i)
		cin >> a[i][0] >> a[i][1];
	for (int j = 1; j <= m; ++ j)
		for (int i = 0; i < n; ++ i)
			for (int k = 0; k < 2; ++ k)
				if (a[i][0] != a[i][1] || ! k)
					if (j == a[i][k])
						dp[i][j][k] = 1;
					else if (j > a[i][k])
						for (int l = 0; l < n; ++ l)
							if (i != l)
								for (int s = 0; s < 2; ++ s)
									if (a[l][s] == a[i][k ^ 1])
										dp[i][j][k] = (dp[i][j][k] + dp[l][j - a[i][k]][s]) % mod;
	for (int i = 0; i < n; ++ i)
		for (int k = 0; k < 2; ++ k)
			sum = (sum + dp[i][m][k]) % mod;
	cout << sum;
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

由~~CF标签~~ 数据范围以及题意可以看出，这肯定是一道 dp 题。

题目对木板的类型做出了限制，并且范围是可控的，因此我们把木板类型放到状态里，而木板长度则可以在转移的时候较容易的判断。

所以令 $dp_{i,j}$ 表示已经堆了长度为 $i$ 的栅栏，最后一个栅栏类型为 $j$ 的方案数。输出答案是显然的，即 $\sum_{i=1}^n dp_{l,i}$。接着考虑转移：每次枚举总长度 $i$ 和当前类型 $j$，然后枚举上一个的类型 $k$，那么 $j$ 能放的条件是 $j \neq k$ 并且 $a_j = b_k$ 并且 $i > a_j$，此时上一次是 $dp_{i-a_j,k}$。所以，转移方程：

$$dp_{i,j} = \sum_{k=1}^n dp_{i-a_j,k}(j \neq k ,a_j=b_k,i>a_j)$$

然后由于横竖可以颠倒，所以我们把横竖反过来存一遍即可。记得用数组记录一下（如果一个栅栏模块分成两个部分 $i$ 和 $j$，那么 $oth_i = j$ 且 $oth_j = i$）。但是正方形颠过来倒过去一样的，就跳过。

最后是初始化，肯定是对于所有的 $i$，$dp_{a_i,i} = 1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int dp[3005][205],a[205],b[205],oth[205];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int l,n,cnt=0; cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		if(a[i]!=b[i])
			cnt++,a[n+cnt]=b[i],b[n+cnt]=a[i],oth[i]=n+cnt,oth[n+cnt]=i; // 如果不是正方形就多存一个
	}
	n+=cnt;
	
	for(int i=1;i<=l;i++)
		for(int j=1;j<=n;j++)
		{
			dp[a[j]][j]=1; // 初始化
			for(int k=1;k<=n;k++)
			{
				if(k==j || k==oth[j]) continue;
				if(b[k]==a[j] && i>a[j])
					(dp[i][j]+=dp[i-a[j]][k])%=mod; // dp 转移，记得取模
			}
		}
	int ans=0;
	for(int i=1;i<=n;i++)
		(ans+=dp[l][i])%=mod; // 统计答案
	cout<<ans%mod;
	return 0;
}
```

---

