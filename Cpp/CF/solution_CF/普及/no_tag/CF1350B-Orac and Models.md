# Orac and Models

## 题目描述

给出一个长度为 $n$ 的序列 $a$，并令 $s$ 为 $a$ 的子序列，$pos_i$ 为 $s_i$ 在原序列里的位置  
当且仅当 $s_j<s_{j+1}$ 且 $pos_j \mid pos_{j+1}$ 时，序列 $s$ 是美丽的

你需要求出序列 $a$ 的最长的美丽子序列的长度

## 说明/提示

$1 \le T \le 100$  
$1 \le n \le 10^5$，$1 \le a_i \le 10^9$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
4
4
5 3 4 6
7
1 4 2 3 6 4 9
5
5 4 3 2 1
1
9```

### 输出

```
2
3
1
1```

# 题解

## 作者：Caro23333 (赞：4)

### Orac and Models 中文题解

考虑dp，不难设计出状态： $f_i$ 表示以编号为 $i$ 的模型结尾的最长合法序列长度。可以写出转移：
$$
f_i = \max\limits_{j\mid i, s_j<s_i} \{f_j + 1\}
$$
于是答案序列的长度为 $f_1,f_2,\cdots,f_n$ 中最大的一个。 

复杂度分析：令 $s=\sum n$，如果你通过枚举因数来进行转移，将花费 $O(s\sqrt s)$的时间；如果通过枚举倍数来进行转移，那么根据调和级数的结论你将花费 $O(s\log s)$ 的时间。不过事实上两种方法均可通过此题。

Problem and Tutorial by Caro23333

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 500005;
inline int readint()
{
	int res = 0;
	char c = 0;
	while(!isdigit(c))
		c = getchar();
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res;	
}
int n,a[MAXN],f[MAXN];

int main()
{
	int T = readint();
	while(T--)
	{
		n = readint();
		for(int i = 1; i<=n; i++)
			a[i] = readint();
		for(int i = 1; i<=n; i++)
			f[i] = 1;
		for(int i = 1; i<=n; i++) 
			for(int j = i*2; j<=n; j += i)
				if(a[i]<a[j])
					f[j] = max(f[j],f[i]+1);
		int ans = 0;
		for(int i = 1; i<=n; i++)
			ans = max(ans,f[i]);
		cout << ans << endl;
	}
	return 0;
}
  
```


---

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1350B)

这题的本质就是一个最长上升子序列，只不过多加了一个限制

对于求LIS，分别有 $\operatorname{O}(n^2)$ 和 $\operatorname{O}(n \log n)$ 两种方法。这题的做法类似第一种

设 $f[i]$ 为以 $i$ 结尾的最长美丽子序列的长度  
对于每个 $2 \le i \le n$，考虑从 $j$ 转移过来。我们发现它们一定满足 $j \mid i$，那么我们可以用 $\operatorname{O}(\sqrt n)$ 的枚举因数来枚举 $j$

总时间复杂度 $\operatorname{O}(n\cdot \sqrt n)$

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int Maxn=1000000+10;
int f[Maxn],s[Maxn];
int n,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int T=read();
	while(T--)
	{
		n=read(),ans=1;
		for(int i=1;i<=n;++i)
		s[i]=read(),f[i]=1;
		for(int i=2;i<=n;++i)
		{
			// numerate the divisors of i
			for(int j=1;j*j<=i;++j)
			{
				if(i%j)continue;
				// j is a divisor of i
				if(s[j]<s[i])f[i]=max(f[i],f[j]+1);
				if(j!=i/j && s[i/j]<s[i])f[i]=max(f[i],f[i/j]+1);
			}
			ans=max(ans,f[i]);
		}
		printf("%d\n",ans);		
	}
	return 0;
}
```

---

## 作者：王熙文 (赞：2)

#### 解题思路：

考虑 $\text{dp}$。

设 $dp_i$ 表示前 $i$ 个数，$a_i$ 必须选的情况下最长美丽子序列的长度。

那么 $dp_i = \max\{dp_j+1(j|i \And s_j<s_i)\}$。

初始 $dp_i=1$，因为选它本身长度为 $1$。

最后答案为 $\max\{dp_i(1 \le i \le n)\}$。

可以通过枚举倍数的方式做：先枚举 $i=1 \sim \lfloor\dfrac{n}{2}\rfloor$，之后枚举 $i$ 的倍数 $j$，$j$ 最开始为 $i \times 2$，一直到 $n$，每次加上 $i$。那么枚举到的倍数 $dp_j=\max(dp_j,dp_i+1)$。



#### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100010];

int dp[100010];

inline int max(int a,int b) { return a>b?a:b; }

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        int ans=1;
        scanf("%d",&n);
        for(int i=1; i<=n; ++i)
        {
            scanf("%d",&a[i]);
            dp[i]=1;
        }
        for(int i=1; i<=(n>>1); ++i)
        {
            for(int j=(i<<1); j<=n; j+=i)
            {
                if(a[i]<a[j])
                {
                    dp[j]=max(dp[j],dp[i]+1);
                    ans=max(ans,dp[j]);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```



---

## 作者：songhongyi (赞：1)

一道很好的DP+数论结合的题目。  
题意大概就是让你求出一个$S_1,S_2,\cdots S_n$的子序列，满足:
- 严格上升;
- 对于选出来的数，满足前一个的下标是后一个的约数。

求它的最长长度。  
既然与上升子序列相关，不难想到对LIS魔改，进行DP。  
对于LIS，转移方程是:
$$dp_i=\max(dp_1+1,dp_2+1,\cdots dp_{i-1}+1,1)$$
即从前面的所有数进行转移，但是现在多了一个现在条件,我们就需要考虑可以从哪些数转移，根据题意，应该是它的所有约数，所有转移方程就是:
$$dp_i=\max(\{dp_j+1|j<i,j|i\},1)$$
于是我们可以对每个数，**拿它转移到所有它的倍数上**。  
所有代码如下
```cpp
#include <cstring>
#include <iostream>
using namespace std;
int dp[ 100010 ];
int a[ 100010 ];
int main()
{
    int t;
    cin >> t;
    while ( t-- )
    {
        memset( dp, 0, sizeof( dp ) ); //多测不清空，爆零两行泪
        int n;
        cin >> n;
        for ( int i = 1; i <= n; i++ )
        {
            cin >> a[ i ];
        }
        for ( int i = 1; i <= n; i++ )
        {
            if ( dp[ i ] == 0 )
                dp[ i ] = 1;  //对于没有转移到过的，设为1
            for ( int j = i + i; j <= n; j += i )  //枚举约数
            {
                if ( a[ j ] > a[ i ] ) // 严格上升
                    dp[ j ] = max( dp[ j ], dp[ i ] + 1 );  // 转移
            }
        }
        int ans = 0;
        for ( int i = 1; i <= n; i++ )
        {
            ans = max( ans, dp[ i ] );
        }
        cout << ans << endl;
    }
}

---

## 作者：Meatherm (赞：1)

有一个显而易见的 DP 式子：

$$f_i=\max\limits_{}\{f_j+1\}(j|i,s_j<s_i)$$

可以预处理出 $[1,100000]$ 中每个数的因数，转移的时候可以不用枚举了，直接拿出来用就行。

然后因为 $[1,100000]$ 中因数个数最多的数也就 $200$ 个左右，所以这么转移能过。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=100010,INF=0x3f3f3f3f;
int f[N];
std::vector <int> G[N];
int a[N];
int n;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	for(rr int i=1;i<=100000;++i){
		for(rr int j=1;i*j<=100000;++j){
			G[i*j].push_back(i);
		}
	}
	int T=read();
	while(T--){
		n=read();
		for(rr int i=1;i<=n;++i){
			a[i]=read();
		}
		memset(f,0,sizeof(f));
		int ans=0;
		for(rr int i=1;i<=n;++i){
			int maxx=0;
			for(rr int j=0;j<G[i].size();++j){
				if(a[i]>a[G[i][j]])maxx=std::max(maxx,f[G[i][j]]);
			}
			f[i]=maxx+1;
			ans=std::max(ans,f[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1400}$
---
### 解题思路：

设 $f_i$ 表示考虑到第 $i$ 个数，能选出来的最长的序列长度。

对于任意一个位置 $i$，只能转移到 $ki$ 位置，其中 $k\in Z$，直接枚举这个 $k$ 并要求 $a_i<a_j$ 就行了。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[100005],f[100005],maxn;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i]=1;;
		maxn=0;
		for(int i=1;i<=n;i++)
		for(int j=i*2;j<=n;j+=i)
		if(a[i]<a[j])
		f[j]=max(f[j],f[i]+1);
		for(int i=1;i<=n;i++)
		maxn=max(maxn,f[i]);
		printf("%d\n",maxn);
	}
	return 0;
}
```


---

## 作者：Hooch (赞：0)

这道题目就是想让你求出**一个数的倍数组成的序列**的最长上升子序列的长度。

我们不难想到用动态规划处理最长上升子序列。

状态转移方程为：
$$
f_i=\max\limits_{j\le i \wedge j\mid i}\{f_j\}+1
$$
但是显然用朴素的算法做，时间为 $\operatorname{O}(n^2)$。

朴素算法代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[100005], f[100005];
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n; 
		for (int i(1); i <= n; ++i) cin >> a[i];
		for (int i(1); i <= n; ++i) f[i] = 1;
		for (int i(2); i <= n; ++i) 
			for (int j(1); j < i; ++j) if (i % j == 0 && a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        // 动态规划
		int ans = 0;
		for (int i = 1; i <= n; ++i) ans = max(ans, f[i]); //对每一个结束的下标取max
		printf("%d\n", ans);
	}
}
```

我们考虑优化。

接着我们发现只有这个**下标 $i$ 的因数**才对最终的 $f_i$ 产生了贡献。

于是就能预处理出每个下标的因数，然后直接枚举因数就能推出正确答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[100005], f[100005], st[100005][20], tot[100005];
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	for (int i(1); i <= 100000; ++i) 
		for (int j = 1; j * j <= i; ++j) if (i % j == 0) st[i][++tot[i]] = j, st[i][++tot[i]] = i / j;
    //预处理因数
	while (t--) {
		cin >> n; 
		for (int i(1); i <= n; ++i) cin >> a[i];
		for (int i(1); i <= n; ++i) f[i] = 1;
		for (int i(2); i <= n; ++i) 
			for (int j(1); j <= tot[i]; ++j) 
				if (a[st[i][j]] < a[i]) f[i] = max(f[st[i][j]] + 1, f[i]);
        // 动态规划
		int ans = 0;
		for (int i = 1; i <= n; ++i) ans = max(ans, f[i]);
		printf("%d\n", ans);
	}
}
```

时间复杂度大约 $\operatorname{O}(tn\log n)$​​​​。



---

## 作者：juicyyou (赞：0)

# CF1350B Orac and Models
## 题目大意：
本题一共 $t$ 组数据，对于每组数据，给定一个数列 $a$ ，求满足一下条件的 $a$ 的子序列 $b$ 的最大长度： $b$ 是 $a$ 的子序列 $a_{p_1}, a_{p_2} \cdots a_{p_m}$ 使得 对于每一个 $i > 1$ ，有 $p_i > p_{i - 1}$ 且 $p_i | p_{i-1}$ 且 $a_{p_i} > a_{p_{i-1}}$ 。
## 解法：
直接 $dp$ 即可。

令 $dp_i$ 为以 $a_i$ 为结尾的满足条件的子序列的最大长度，我们考虑枚举 $i$ 的所有因子，则有方程：
$$dp_i = \sum\limits_{d\,|\,i} dp_d + 1 (a_d < a_i)$$
所以我们枚举每一个小于 $\sqrt{i}$ 的因子 $j$，然后再用 $dp_j$ 和 $dp_{i / j}$ 更新 $dp_i$ 即可。

下面是我的Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 2e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll ans, n;
ll a[maxn], dp[maxn];
int main(){
	ll t;
	qread(t);
	while(t--){
		qread(n);
		for(int i = 1;i <= n;i++){
			qread(a[i]);
			dp[i] = 1;
		}
		ans = 1;
		for(int i = 2;i <= n;i++){
			for(int j = 1;j * j <= i;j++){
				if(i % j != 0) continue;
				if(a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
				if(a[i / j] < a[i]) dp[i] = max(dp[i], dp[i / j] + 1);
			}
			ans = max(ans, dp[i]);
		}
		cout << ans;
		puts("");
	}
	return 0;
}
```

上述算法的单次复杂度即为 $\mathcal O(n\sqrt{n})$ 算上多组数据之后，总复杂度即为 $\mathcal O(\sum n\sqrt{n})$ ，可以通过此题。

---

## 作者：JamesQin (赞：0)

考虑 dp。

设 $dp_k$ 表示考虑第 $k$ 个元素及其后面的元素时的最大长度。

得出如下方程：

$$dp_i=dp_j+1(i \mid j ,s_i < s_j)$$

直接计算即可。时间复杂度$O(Tn \sqrt{n})$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=100010;
int s[MAX],dp[MAX];
int main(){
	int T;
	cin>>T;
	while(T--){
		for(int i=1;i<MAX;i++){
			s[i]=0;
			dp[i]=1;
		}
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>s[i];
		}
		for(int i=n;i>=1;i--){
			for(int j=1;j<=sqrt(n);j++){     //O(sqrt(n))求因数
				if(i%j==0){
					if(s[j]<s[i])dp[j]=max(dp[j],dp[i]+1);
					if(s[i/j]<s[i])dp[i/j]=max(dp[i/j],dp[i]+1);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=max(ans,dp[i]);
		}
		cout<<ans<<endl<<endl;
	}
	return 0;
}
```


---

## 作者：几何之舞丶 (赞：0)

一道挺好的dp题.

首先,如果题目去掉整除的条件,那么这个题就是一个标准的最长上升子序列,然后就有了非常传统的O(n^2)的做法.

加上整除条件之后,我们可以怎么处理呢?

既然是要整除,那么我们在dp的过程中,第二层循环的时候可以直接枚举整数倍,因为所有非整数倍的物品显然我们是不会去选的.

那么这样就可以过啦.

代码

```cpp

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<algorithm>
#define N 100005
#define INF 0x7fffffff
#define inf 0x3f
#define int long long
#define ll long long
#define lson (now<<1)
#define rson (now<<1|1)
#define pii pair<int ,int >
#define pushup1(now)  tr[now].sum=(tr[lson].sum+tr[rson].sum);
#define pushup2(now)  tr[now].sq=(tr[lson].sq+tr[rson].sq);
using namespace std;
const int mod=100000000;
inline ll read() {
	ll now=0;
	char c=getchar();
	ll f=1;
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		now=(now<<1)+(now<<3)+(c^48);
		c=getchar();
	}
	return f*now;
}
int a[N],t,n,m,g[N];
signed main(){
	t=read();
	while(t--){
		n=read();int ans=1;
		memset(a,0,sizeof(a));
		memset(g,0,sizeof(g));
		for(int i=1;i<=n;i++)
		a[i]=read();
		for(int i=1;i<=n;i++)
		g[i]=1;
		for(int i=n;i>=1;i--){
			for(int j=i+i;j<=n;j+=i){
				if(a[j]>a[i]){
					g[i]=max(g[i],g[j]+1);
					ans=max(ans,g[i]);
				}
			}
		}
		printf("%lld\n",ans);
	}
	//system("pause");
	return 0;
}
```


---

## 作者：do_while_true (赞：0)

求的是最长的长度，而不管当前的位置前面的序列选择了哪些，都不会对后面的选择造成影响。所以后面的选择和前面的选择无关，则我们可以直接动规（因为无后效性）。

设 $f_i$ 为前 $i$ 个数所选的最长长度，则我们很容易想到对于任意满足 $j<i,j|i,s_j<s_i$ 的 $j$ ，$f_i=\max\{f_j\}+1$，也就是从前面最长的一个接过来。

答案就为 $f$ 的最大值。

[$\mathcal{Code}$](https://codeforces.ml/contest/1350/submission/79931096)

---

