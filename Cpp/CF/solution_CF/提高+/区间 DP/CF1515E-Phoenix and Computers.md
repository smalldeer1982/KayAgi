# Phoenix and Computers

## 题目描述

There are $ n $ computers in a row, all originally off, and Phoenix wants to turn all of them on. He will manually turn on computers one at a time. At any point, if computer $ i-1 $ and computer $ i+1 $ are both on, computer $ i $ $ (2 \le i \le n-1) $ will turn on automatically if it is not already on. Note that Phoenix cannot manually turn on a computer that already turned on automatically.

If we only consider the sequence of computers that Phoenix turns on manually, how many ways can he turn on all the computers? Two sequences are distinct if either the set of computers turned on manually is distinct, or the order of computers turned on manually is distinct. Since this number may be large, please print it modulo $ M $ .

## 说明/提示

In the first example, these are the $ 6 $ orders in which Phoenix can turn on all computers:

- $ [1,3] $ . Turn on computer $ 1 $ , then $ 3 $ . Note that computer $ 2 $ turns on automatically after computer $ 3 $ is turned on manually, but we only consider the sequence of computers that are turned on manually.
- $ [3,1] $ . Turn on computer $ 3 $ , then $ 1 $ .
- $ [1,2,3] $ . Turn on computer $ 1 $ , $ 2 $ , then $ 3 $ .
- $ [2,1,3] $
- $ [2,3,1] $
- $ [3,2,1] $

## 样例 #1

### 输入

```
3 100000007```

### 输出

```
6```

## 样例 #2

### 输入

```
4 100000007```

### 输出

```
20```

## 样例 #3

### 输入

```
400 234567899```

### 输出

```
20914007```

# 题解

## 作者：GsjzTle (赞：58)

[更好的阅读体验](https://www.cnblogs.com/StarRoadTang/p/14727012.html) 

## 题目链接

[点我跳转](https://codeforces.com/contest/1515/problem/E) 

## 题目大意

>给定 $N$ 台电脑，起初每台电脑都是关闭的
>
>现在你可以随意打开电脑，但如果第 $i-1$、第 $i+1$ 台电脑是开启的，则第 $i$ 台电脑也会自动开启，而你无法手动开启它
>
>问你有多少种打开电脑的方法，使得最后所有电脑都是开着的

## 解题思路

>分成两步来解决.
>
>**第一步：**
>
>考虑：如果 $N$ 台电脑我都要手动开启，有多少种方法？
>
>可以枚举是从哪台电脑开始打开：
>
>+ 从 $1$ 开始，剩下的 $N-1$ 必须按照 $2,3,...,n$ 的顺序开(不理解可以画一下)
>+ 从 $2$ 开始，对于 $2$ 右边的电脑 $[3$~$N]$，$4$ 必须在 $3$ 开了之后开，$5$ 必须在 $4$ 开了之后开 $...$ ，而 $1$ 可以在任意时刻开机
>+ $...$
>+ 从 $k$ 开始开，对于 $k$ 右边的电脑， 它们的相对开机顺序必须是 $k + 1 , k + 2 , ... , n$
>  对于$k$ 左边的电脑，它们的相对开机顺序必须是 $k-1,k-2,...,1$ 
>  不过左右两边的开机顺序是可以穿插（合并）在一起的
>![C](https://dn-simplecloud.shiyanlou.com/questions/uid1331660-20240821-1724231876437)
>
>**所以手动开启 $N$ 台电脑的方案数为 $C_{n-1}^{1}+C_{n-1}^{2}+\ldots +C_{n-1}^{n-1} = 2^{n-1}$**
>
>**第二步：**
>
>考虑：最后电脑开启的状态？
>
>显然最后电脑开启的状态会是这样的：
>
>手动开启 $1\sim X_1$ → 自动开启 $X_1+1$  → 手动开启 $X_1+2\sim X2$ 台 →自动开启 $X_2+1$ → $...$ → 手动开启 $X_{n-1} + 1\sim X_n$ ，其中需要保证 $X_i + 1 < N$
>
>于是我们可以定义 $f[i][j]$ 表示：前 $i$ 台电脑，手动打开了 $j$ 台, 第 $i$ 台是手动打开的 , 第 $i + 1$ 台是自动打开的方案数。
>
>那么 $f[i][j]$ → $f[i + 1 + K][j + X_i]$ 的意义为：
>
>手动打开 $pos \sim i$ → 自动打开$i+1$ → 手动打开 $i + 2 \sim X_i$ 的过程。
>
>+ $f[i+1+X_i][j+X_i]$ 相对 $f[i][j]$ 又多手动开启了 $X_i$ 台电脑
>+ 这 $X_i$ 台的电脑的开启方案数有 $2^{Xi-1}$种（**第一步得出的结论**）
>+ 然后考虑将这 $X_i$ 台"新"电脑开机的顺序和 $j$ 台"旧"电脑开机的顺序穿插（合并）在一起。
>  即现在有 $X_i+j$ 个开机顺序需要确认，我们可以从中选 $X_i$ 个放"新"电脑的开机顺序，剩下的放"旧"电脑的开机顺序，那么方案数为 $C_{X_i+j}^{X_i}$ (或者 $C_{X_i+j}^{j}$也可以）
>
>所以可得： $f[i + 1 + X_i][j + X_i] = f[i][j] \times 2^{Xi-1} \times C[j + X_i][X_i]$
>
>答案即： $ans=\sum ^{n}_{i=0}f\left[ n\right] \left[ i\right] $
>
>$i$、$j$、$X_i$ 都可以通过枚举得到
>
>**写题解不易，如有帮助到您请点个赞给予我一点小小的鼓励！**

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e2 + 10;
long long C[N][N] , bit[N];
long long n , m , ans , f[N][N]; 
void init(int mod)
{
	bit[0] = 1;
	for(int i = 1 ; i <= N - 10 ; i ++) bit[i] = bit[i - 1] * 2 % mod; 
	for(int i = 0 ; i <= N - 10 ; i ++)
	{
		C[i][0] = 1;
		for(int j = 1 ; j <= i ; j ++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
}
signed main()
{
	cin >> n >> m;
	init(m);
	for(int i = 1 ; i <= n ; i ++)
	{
		f[i][i] = bit[i - 1];
		for(int j = 0 ; j <= i ; j ++)
		{
			for(int k = 1 ; k + i + 1 <= n; k ++)
			{
				f[i + 1 + k][j + k] += f[i][j] * bit[k - 1] % m * C[j + k][k] % m;
				f[i + 1 + k][j + k] %= m; 
			}
		}
	}
	for(int i = 0 ; i <= n ; i ++) ans += f[n][i] , ans %= m;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：yuzhechuan (赞：39)

类比CEOI kangaroo一题的插入思想，有一种 $O(n^2)$ 的简单做法

令 $f_{i,j}$ 表示已开机 $i$ 台，构成了 $j$ 个连续段，每段间距离是大于 $1$ 的一个 **不确定值**

转移有 **新建段，段扩增，段合并** 共五种情况

注意由于两段间的距离是不确定的，所以怎么插都是可以的，转移系数见代码

```cpp
const int N=405;
int n,f[N][N],mod;

signed main(){
	read(n);read(mod);
	f[0][0]=1;
	for(int i=0;i<n;i++) for(int j=0;j<=i;j++){
		f[i+1][j+1]=(f[i+1][j+1]+f[i][j]*(j+1))%mod; //j+1个间隔选一个插
		f[i+1][j]=(f[i+1][j]+f[i][j]*j*2)%mod; //两端贴着开
		f[i+2][j]=(f[i+2][j]+f[i][j]*j*2)%mod; //两端隔一个开
		if(j>=2){
			f[i+2][j-1]=(f[i+2][j-1]+f[i][j]*(j-1)*2)%mod; //定两段间距离为2，有正反两种开法
			f[i+3][j-1]=(f[i+3][j-1]+f[i][j]*(j-1))%mod; //定两段间距离为3，开中间那个
		}
	}
	write(f[n][1]);
}
```

---

## 作者：BqtMtsZDnlpsT (赞：27)

可以发现最终序列一定会分为：

一段手动点亮 $+$ 一个自动点亮 $+$ 一段手动点亮 $+\dots+$ 一段手动点亮

设 $f_{i,j}$ 表示点亮了 $i$ 盏灯，有 $j$ 段手动点亮的方案数。

则 $f_{i,j}=f_{i-1,j}\times2j+f_{i-2,j-1}\times j$

每一次开灯可以看做在原来的基础上插入序号 $i$ 表示第 $i$ 次开灯。

表示第 $i$ 次开灯可以开 **每一段开头或结尾的灯** 或 **新开一段**。

Q：方案算少了吗？

A：没有，只是表示当前开启的灯分成 $j$ 段，并没有一定连续，这 $j$ 段可以散落在原序列各个位置，插入 $n$ 个数后，自然对应上了每个位置。

Q：插入新一段时为什么要 $+2$ 盏灯？

A：如果新开了一段，必然与前后段形成一个自动打开，所以不仅要加本身，还要加自动打开的灯。

[![LeQP5n.png](https://s1.ax1x.com/2022/04/12/LeQP5n.png)](https://imgtu.com/i/LeQP5n)

Q：为什么乘 $2j$、$j$？

A：
1. 有 $j$ 段可以手动打开，可以选择开每段开头或结尾。
2. 新开一段可以开在头/尾/中间。

Q：加段能加中间，为什么开灯不能开中间？

A：
1. 加段加中间是因为保证开灯顺序不同
2. 但是如果加的话加在段中间，那么当前没加的序列中间段中间一定是空的，这意味着这个点将自动打开。


复杂度 $O(n^2)$

```cpp
int n,M,ans,f[405][405];
signed main(){
	cin>>n>>M;
	f[1][1]=1;//一个点只有一种开灯法
	for(int i=2;i<=n;i++)
		for(int j=1;j<=((i+1)>>1);j++)
			f[i][j]=(2ll*f[i-1][j]*j+1ll*f[i-2][j-1]*j)%M;
	for(int i=1;i<=((n+1)>>1);i++)ans=(ans+f[n][i])%M;
	//答案就是 n 个点，分成 1...n 段的方案数
	//但是不难发现，分成段数 ≤ n/2向上取整，所以就有了以上代码
	cout<<ans;
	return 0;
}
```


---

## 作者：Social_Zhao (赞：16)

一个不需要 EGF 没啥思维难度的 $O(n^3)$ 做法（

以下称 Computer 为灯。

考虑一种点灯方案的结构（不考虑点灯的顺序的话）是什么，显然是点亮了若干个连续段，每个连续段之间间隔一个不点亮（这一个会自动亮起来）

我们设 $g_n$ 表示完全手动点亮一个长度为 $n$ 的连续段的方案。这个点亮的方案显然是首先点亮中间某一个点，然后往两边扩展。

两种思考方法：

1. 枚举中间点了哪一个，求两边扩展的方案数，这是一个很简单的模型：

	$$
    	\sum_{i=1}^n\binom{n-1}{n-i}=2^{n-1}
   $$

1. 时间倒流，考虑已经点亮了一个连续段，然后倒着灭回去，每次可以灭掉最左边或者最右边的一个灯，但最后一盏灯不区分左右，方案数还是（在一个长为 $n-1$ 的序列中填上 "左" 或者 "右"）：

	$$
    	2^{n-1}
   $$
   
求出了 $g_n$ 之后，我们就可以枚举最后一段连续段的长度，做一个 DP。设 $f_{i, j}$ 表示点亮了前 $i$ 个灯，其中有 $j$ 个是手动点的，转移方程显然：

$$
	f_{i, j}=\sum_{k=1}^jf_{i - k - 1, j - k}\times g_k \times \binom{j}{k}
$$

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 405;
int n, P;
int g[N], fac[N], inv[N];
int f[N][N]; // f[i][j]: 1~i，一共手动点了 j 盏灯的方案数 

int qpow(int x, int y) {
	int res = 1;
	while(y) res = res * ((y & 1)? x : 1) % P, x = x * x % P, y >>= 1;
	return res;
}

void init(int n) {
	g[1] = 1;
	for(int i = 2; i <= n; i++) g[i] = g[i - 1] * 2 % P;
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
	inv[n] = qpow(fac[n], P - 2);
	for(int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i % P;
}

int C(int n, int m) { return n >= m? fac[n] * inv[m] % P * inv[n - m] % P : 0; }

signed main() {
	n = get(), P = get();
	init(n);
	for(int i = 1; i <= n; i++) {
		f[i][i] = g[i];
		for(int j = 1; j < i; j++) {
			for(int k = 1; k < j; k++) {
				f[i][j] = (f[i][j] + f[i - k - 1][j - k] * g[k] % P * C(j, k) % P) % P;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = (ans + f[n][i]) % P;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：zmx_wzx_JY (赞：15)

刷计数 $dp$ 遇到一年前上分场的题，发现这个题完全可以 $O(n^2)$，然而数据范围是 400。。。

发现一个方案相当于：划分成若干段，段之间空一个位置，段长和加空格数为 $n$。段内元素是先选择其中一个，段中位置选的时间是先递减再递增，不同段中位置选的顺序没有关系。

那么直接 $f_{i,j}$ 表示开的前 $i$ 台机器构成了 $j$ 段的方案数。

转移是：

- 新开一段：$f_{i+1,j+1}\leftarrow (j+1)f_{i,j}$

- 在原来某一段的左边或者右边加一台：$f_{i+1,j}\leftarrow 2jf_{i,j}$

初值 $f_{1,1}=0$。满足 $i+j-1=n$ 的 $f_{i,j}$ 向答案做贡献。

复杂度 $O(n^2)$。

code:

```
	f[1][1] = 1;
	long long ans = 0;
	Rep(i, 1, n) Rep(j, 1, n){
		f[i][j] %= P;
		if(i + j - 1 == n) ans += f[i][j];
		f[i + 1][j] += f[i][j] * (j << 1) % P;
		f[i + 1][j + 1] += f[i][j] * (j + 1) % P;
	}
	cout<<ans % P<<'\n';
```

不知道能不能用代数重工业搞到更优复杂度

---

## 作者：JiaY19 (赞：12)

**[更好的阅读体验](https://www.cnblogs.com/mfeitveer/p/16664291.html)**

感觉这样的 $\text{dp}$ 题还比较多，思路都比较的神奇。

个人感觉比较像区间 $\text{dp}$ 的一类变种。

但又和区间 $\text{dp}$ 的维护方式极不一样。

### 对于此类 $\text{dp}$

这一类 $\text{dp}$ 主要维护的是一个一个的块，可以理解成连通块。

将 $f_{i,j}$ 看作放置 $\text{i}$ 个元素，形成了 $\text{j}$ 个块的方案数。

有三类操作。

#### 将某个块的元素个数加一

那么每一个块都有可能加一。

所以。

$$f_{i,j}=f_{i-1,j}\times j$$

#### 新增一个块

类似插空的思路。

原来有 $j - 1$ 个块，所以有 $\text{j}$ 个空。

$$f_{i,j}=f_{i-1,j-1}\times j$$

#### 合并两个块

与第二点类似，但是不能在两边插空。

所以还是只有 $\text{j}$ 个空。

$$f_{i,j}=f_{i-1,j+1}\times j$$

时间复杂度 $O(n^2)$。

这就是这一类问题的基本操作。

### 关于本题

我们发现，对于一般的 $\text{dp}$ 而言，不怎么好去维护这个问题。

就可以考虑一下上面所说的 $\text{dp}$。

我们从小到大去给元素排位置。

还是从三种情况去讨论。

#### 新增元素 

可以发现，对于一个新增加的元素，有两种情况。

第一种是直接加入。

$$f_{i,j}=f_{i-1,j}\times j\times 2$$

第二种是隔一个加入，这样又会有一个自动生成，相当于加了两个。

$$f_{i,j}=f_{i-2,j}\times j\times 2$$

#### 新增块

这种情况直接加就可以了。

$$f_{i,j}=f_{i-1,j-1}\times j$$

#### 合并块

可以发现，合并两个块也有两种情况。

第一种是两个块中间空了两个格子，随便加上一个另一个也有了。

$$f_{i,j} = f_{i-2,j+1}\times 2\times j$$

第二种是两个块中间空了三个格子，这种情况加上中间的那个就可以连起来了。

$$f_{i,j}=f_{i-3,j+1}\times j$$

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n , mod , f[410][410];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

signed main()
{
    n = read() , mod = read() , f[1][1] = 1;
    for(int i = 2;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            f[i][j] += f[i - 1][j - 1] * j;
            f[i][j] += f[i - 1][j] * j * 2;
            f[i][j] += f[i - 2][j] * j * 2;
            if(i > 2) f[i][j] += f[i - 2][j + 1] * 2 * j;
            if(i > 3) f[i][j] += f[i - 3][j + 1] * j;
            f[i][j] %= mod;
        }
    }
    cout << f[n][1] << endl;
    return 0;
}

```

---

## 作者：Cry_For_theMoon (赞：10)

[传送门](https://www.luogu.com.cn/problem/CF1515E)

卡C，D两个半小时，来不及做这个水题，-103 /cy

先考虑 $g(n)$ 为 $n$ 台电脑全部手动打开的方案数。

第一眼是容斥，第二眼不会。试试正着直接排列组合草。设第一次选择了第 $i$ 台电脑。容易发现 
$$\begin{cases}index_{i+1}<index_{i+2}<...<index_{n} \\  index_{i-1}>index_{i-2}>...>index_{1} \end{cases}$$

其中 $index_i$ 是第 $i$ 个元素的打开时间（序号）。

这样的话方案就有 $\dbinom{n-1}{i-1}$. 只要在剩下 $n-1$ 个位置中选取 $i-1$ 个给前 $i-1$ 个，剩下的位置自动确定。因此：

$$g(n)=\sum_{i=0}^{n-1}\dbinom{n-1}{i}=2^{n-1}$$

非常优美。

然后先想想如果割裂开的两段如果要求全部手动打开，能否通过组合答案得到。我们发现没有问题，设第一段 $k1$ 个，第二段 $k2$ 个。则它们全部手动打开的方案数：

$$cnt=\dbinom{k1+k2}{k1}\,\times\,2^{k1-1}\,\times\,2^{k2-1}$$

换言之因为各段之间互相独立，只需要在操作序列中确定每一段的位置乘上 $g$ 就可以了。显然多个段之间也可以类似的组合。

不过这个东西没有直接用处，因为 $n=400$ 我们做不到暴力分段（如果 $<=20$ 就可以枚举）。这个东西是允许立方算法通过的，立方算法并不多，很容易尝试 dp. 设 $f(i,j)$ 是 $i$ 台电脑，其中 $j$ 台是自动打开的。

注意到 $f(i,0)$ 即为 $g(i)$ ; 对于 $j>0$ 有：

$$f(i,j)=\sum_{k=2}^{i-1}f(k-1,j-1)\,\times\,2^{i-k-1}\,\times\,\dbinom{i-j}{i-k}$$

$k$ 是枚举最后一个自动打开的电脑的位置。方程就是基础排列组合乱推。

最后输出 $\sum_{j=0}^{n}f(n,j)$ 就是答案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=410;
ll n,f[MAXN][MAXN];
ll power[MAXN],ans,moder;
ll c[MAXN][MAXN];
int main(){
	cin>>n>>moder;
	power[0]=1;rep(i,1,n)power[i]=power[i-1]*2%moder;
	rep(i,1,n){
		f[i][0]=power[i-1];
	}
	c[0][0]=1;
	rep(i,1,n){
		c[i][0]=1;
		rep(j,1,i)c[i][j]=(c[i-1][j-1]+c[i-1][j])%moder;	
	}
	rep(i,2,n){
		rep(j,1,i-2){
			//i个里j个自动
			per(k,i-1,2){
				//[k+1,i]手动，k自动
				f[i][j]=(f[i][j]+f[k-1][j-1]*power[i-k-1]%moder*c[i-j][i-k]%moder)%moder;
			}
		}
	}
	rep(j,0,n)ans=(ans+f[n][j])%moder;
	cout<<ans;
	return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：7)

**CF1515E sol**

感觉其它的 $O(n ^ 2)$ 做法题解写的都好迷惑。

**前置知识**：连续段型 dp，可以考虑设 $dp_{i,j}$ 表示将前 $i$ 个数分成 $j$ 个连续段，在向 $i \rightarrow i + 1$ 状态转移时，可以考虑对 $j$ 个连续段的一个做扩展或者在 $j + 1$ 个空中插入一个连续段。视题目情况决定如何转移。

----------------------------------

**性质 $1$**，对于一种摆放方法可以理解称将原序列划分为 $j$ 个相邻段距离为 $1$ 的连续段，$j$ 个连续段内的所有数存在一种整体摆法。

需要注意的是一种合理的摆法需要保证段内数的插入顺序是合理的，即一个段如果要扩展，每次只向两端拓展，否则该连续段会裂开，无法构成连续段。

**性质 $2$**，加入一个数只会造成 $O(1)$ 的连续段变化，这里只涉及扩展段和加入段。

我们考虑在 dp 的时候**不插入在已经钦定好的空上**，因为这也会破坏连续段的性质，你也可以理解成一个空和连续段是绑在一起的。

设 $dp_{i,j}$ 表示前 $i$ 个数当前存在 $j$ 个连续段的方案数，则转移式： 

$\begin{cases}dp_{i,j} \leftarrow dp_{i - 1,j} \times 2j,i \geq 1\\dp_{i,j} \leftarrow dp_{i - 2,j-1} \times j,i \geq 2,j\geq 1\end{cases}$

前一个转移方程即扩展一个已知的连续段，向两边扩展是都能加的，所以乘积系数为 $2j$。

对于后一个转移方程为在 $j - 1$ 个连续段，$j$ 个空中插入一个连续段，注意这里我们插入一个连续段形如“一个位置加一个空”，所以需要 $2$ 的 $i$ 维代价。

这么统计完后你发现，所有连续段内数在插入时就已经决定好顺序了，满足我们性质 $1$ 的定义。

最后一个段会多一个空，所以答案应该是 $\sum f_{n + 1,j},j\in[0,n]$。

你也可以发现连续段数量没这么多少枚举点卡卡常数。

时空复杂度 $O(n ^ 2)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 4e2 + 5;
int n,mod,dp[Len][Len];
inline void Mod(int &x){if(x > mod) x -= mod;}
int main()
{
	scanf("%d %d",&n,&mod);
	dp[0][0] = 1;
	for(int i = 1 ; i <= n + 1 ; i ++)
	{
		for(int j = 0 ; j <= i ; j ++)
		{
			dp[i][j] += 1ll * 2 * j % mod * dp[i - 1][j] % mod , Mod(dp[i][j]);//将一个数插入一个段的左右两边 
			if(i >= 2 && j >= 1) dp[i][j] += 1ll * j * dp[i - 2][j - 1] % mod , Mod(dp[i][j]);//插入一个段。 
		}
	}
	int ans = 0;
	for(int i = 0 ; i <= n + 1 ; i ++) ans = (ans + dp[n + 1][i]) % mod;
	printf("%d\n",ans);
	return 0;	
} 
```

---

## 作者：7KByte (赞：4)

注意到数据范围 $N\le 400$ ，非常像区间 $\rm DP$ 。

所以我们可以定义状态 $f[l][r][k]$ 表示覆盖区间 $[l,r]$ 使用 $k$ 次操作的方案数。

显然任意长度相等的区间是等价的，所以我们优化状态 $f[i][j]$ 表示长度为 $i$ 的区间，使用 $j$ 次操作覆盖的方案数。

考虑转移。覆盖一个区间，所有方案分为有自动开机的和没有自动开机的方案。

对于没有自动开机的方案，即 $f[i][i]$ ，手算一下发现固定初始点后，每次可以向右或者向左扩展一格，方案数为 $2^{i-1}$。

对于有自动开机的方案，我们枚举第一个自动开机的电脑为 $k$ ，有转移方程

$$f[i][j]=\sum\limits_{k=2}^{\min\{i-1,j\}}2^{k-2}\binom{j}{k-1}f[i-k][j-k+1]$$

预处理组合数，时间复杂度$\rm O(N^3)$，常数很小。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
int n;long long f[N][N],c[N][N],P;
signed main(){
	scanf("%d%lld",&n,&P);
	rep(i,0,n){
		c[i][0]=1LL;
		rep(j,1,i)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%P;
	}
	f[1][1]=1LL;
	rep(i,2,n){
		rep(j,1,i)f[i][i]=(f[i][i]+c[i-1][j-1])%P;
		rep(j,2,i-1){
			rep(k,1,i-j)
				(f[i][j-1+k]+=f[j-1][j-1]*c[k+j-1][j-1]%P*f[i-j][k]%P)%=P;
		}
	}
	long long ans=0LL;
	rep(i,1,n)ans=(ans+f[n][i])%P;
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：bellmanford (赞：3)

这是一个不用任何数学知识的套路做法。

考虑 $f_{i,j,k,0/1}$ 表示已经放入了 $[1,i]$ 的电脑，第 $i$ 台电脑在第 $j$ 个位置，已有的操作总长度为 $k$ ，第 $i-1$ 台电脑是否在第 $i$ 台电脑前面被开启。

显然有式子：

$f_{i+1,l,k+1,0}+=f_{i,j,k,0}\ (l\in [1,j])$

$f_{i+1,l,k+1,1}+=f_{i,j,k,0}+f_{i,j,k,1}\ (l\in [j,k+1])$

$f_{i+2,l,k+1,0}+=f_{i,j,k,0}+f_{i,j,k,1}\ (l\in [1,k+1])$

可以用差分优化做到 $\mathcal{O(n^3)}$ ，滚动数组优化第三维做到空间 $\mathcal{O(n^2)}$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int M=405;

int max(int x,int y){ return x>y?x:y; }
int min(int x,int y){ return x<y?x:y; }

int read(){
	int x=0,y=1;char ch=getchar();
	while(ch<'0'||ch>'9') y=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*y;
}

int n,p,Ans=0,f[M][M][2][2],pre[M];
int qmod(int x){ return x>=p?x-p:x; }
void Add(int &x,int y){ x=qmod(x+y); }
void ADD(int l,int r,int x){ Add(pre[l],x),Add(pre[r+1],p-x); }
void solve(){
	n=read(),p=read();
	f[1][1][1][0]=1;
	for(int k=1;k<=n;k++){
		int cur=k&1,las=cur^1;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j][las][0]=f[i][j][las][1]=0;
		for(int i=k;i<=n;i++){
			
//			for(int j=1;j<=k;j++){
//				for(int l=1;l<=j;l++) Add(f[i+1][l][k+1][0],f[i][j][k][0]);
//				for(int l=j+1;l<=k+1;l++) Add(f[i+1][l][k+1][1],f[i][j][k][0]+f[i][j][k][1]);
//				for(int l=1;l<=k+1;l++) Add(f[i+2][l][k+1][0],f[i][j][k][0]+f[i][j][k][1]);
//			}
			
			for(int l=0;l<=k+2;l++) pre[l]=0;
			for(int j=1;j<=k;j++) ADD(1,j,f[i][j][cur][0]);
			for(int l=1;l<=k+1;l++) Add(pre[l],pre[l-1]),Add(f[i+1][l][las][0],pre[l]);
			
			for(int l=0;l<=k+2;l++) pre[l]=0;
			for(int j=1;j<=k;j++) ADD(j+1,k+1,qmod(f[i][j][cur][0]+f[i][j][cur][1]));
			for(int l=1;l<=k+1;l++) Add(pre[l],pre[l-1]),Add(f[i+1][l][las][1],pre[l]);
			
			for(int l=0;l<=k+2;l++) pre[l]=0;
			for(int j=1;j<=k;j++) ADD(1,k+1,qmod(f[i][j][cur][0]+f[i][j][cur][1]));
			for(int l=1;l<=k+1;l++) Add(pre[l],pre[l-1]),Add(f[i+2][l][las][0],pre[l]);
			
			if(i==n) for(int j=1;j<=k;j++) Add(Ans,qmod(f[i][j][cur][0]+f[i][j][cur][1]));
			
		}
	}
	printf("%lld\n",Ans);
}

signed main(){
	solve();
}
```

---

## 作者：45dino (赞：2)

题目大意：

- 有一排电脑，从 $1$ 到 $n$ 依次编号。

- 对于 $i(1<i<n)$，如果 $i+1$ 和 $i-1$ 号电脑都已经打开，那么第 $i$ 号电脑就会自动打开。

- 求把所有电脑都打开的操作序列的个数。

- $1≤n≤400$

分析：

令 $f(i,j)$ 表示目前考虑到第 $i$ 台电脑，且之前有 $j$ 台电脑没打开（计划自动打开）的方案数。

考虑如何求 $f(i,j)$，发现可以由 $j-1$ 时转移而来，设当前由 $f(k,j-1)$ 转移而来，那么就有$(^{i-k-1} _ {i-j+1})$ 种方式将新的 $i-k-1$ 个数安置下来，同时通过规律发现，如果 $k$ 台连续的电脑不自动打开，有 $2^{k-1}$ 种操作顺序。

故转移方程如下：
$$f(i,j)=f(k,j-1)\times (^{i-k-1}_ {i-j+1})\times 2^{i-k-2} |1≤k≤i-2$$

预处理组合数和2的次幂即可。

[参考代码](https://codeforces.com/contest/1515/submission/114992866)

---

## 作者：Wenoide (赞：1)

## 状态定义

注意到共 $i$ 台电脑的情况下，第 $i$ 台一定是手动打开的。

我们定义：

- $f_{i, j, k}$ 表示共 $i$ 台电脑的情况下，手动打开次数为 $j$ ，其中第 $k$ 次打开了第 $i$ 台，此前第 $i-1$ 台未打开。

- $g_{i, j, k}$ 表示共 $i$ 台电脑的情况下，手动打开次数为 $j$ ，其中第 $k$ 次打开了第 $i$ 台，此前第 $i-1$ 台已打开。

## 转移方程

边界条件：$f_{1, 1, 1} = 1$，$f_{2, 2, 1} = g_{2, 2, 2} = 1$，$f_{2,2,2} = g_{2, 2, 1} = 0$。

$$ f_{i, j, k} = \sum_{l=k}^{j} f_{i-1, j-1, k} + \sum_{l = 1}^{j-1}(f_{i-2, j-1, l} + g_{i-2, j-1, l})$$

$$ g_{i, j, k} = \sum_{l=1}^{k-1}(f_{i-1, j-1, l} + g_{i-1, j-1, l}) $$

### 第一个 $\sum$

考虑第 $i-1$ 台是手动打开的情况。

则手动打开第 $i-1$ 台时，第 $i-2$ 台未打开。否则，由于第 $i$ 台在第 $i-1$ 台前打开，第 $i-1$ 台将被自动打开。矛盾。 

对于打开前 $i-1$ 台且打开第 $i-1$ 台在第 $i-2$ 台前打开的操作序列，在打开第 $i-1$ 台之前的某一时刻插入开第 $i$ 台的操作可得到一个新的操作序列。

### 第二个 $\sum$

考虑第 $i-1$ 台是自动打开的情况。

第 $i-2$ 台和第 $i$ 台一定手动打开。

对于打开前 $i-2$ 台的任意操作序列，在任意时刻插入开第 $i$ 台的操作可得到一个新的操作序列。

### 第三个 $\sum$

第 $i-1$ 台一定是手动打开的。

对于打开前 $i-1$ 台的任意操作序列，在打开第 $i-1$ 台之后的某一时刻插入开第 $i$ 台的操作可得到一个新的操作序列。

## 代码实现

使用滚动数组压掉第一维以节约空间。

使用前缀和的思想可以 $O(1)$ 转移。

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。

参考代码：
```
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N = 400 + 10;
 
ll sum[N][N];
ll f[2][N][N], g[2][N][N];
int main() {
	int n, MOD;
	cin >> n >> MOD;
	f[1][1][1] = 1, sum[1][1] = 1;
	f[0][2][1] = g[0][2][2] = 1, sum[2][2] = 2;
	for (int i = 3; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			ll sumf, sumg;
			sumf = sumg = 0;
			for (int k = j; k >= 1; --k) {
				sumf = (sumf + f[(i&1)^1][j-1][k]) % MOD;
				if (k != i) f[i&1][j][k] = (sumf + sum[i-2][j-1]) % MOD;
			}
			sumf = sumg = 0;
			for (int k = 1; k <= j; ++k) {
				if (k != 1) g[i&1][j][k] = (sumf + sumg) % MOD;
				sumf = (sumf + f[(i&1)^1][j-1][k]) % MOD;
				sumg = (sumg + g[(i&1)^1][j-1][k]) % MOD;
			}
			for (int k = 1; k <= j; ++k) {
				sum[i][j] = (sum[i][j] + f[i&1][j][k] + g[i&1][j][k]) % MOD;
			}
		}
	}
	ll ans = 0;
	for (int j = 1; j <= n; ++j) {
		ans = (ans + sum[n][j]) % MOD;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：grass8cow (赞：1)

EGF 是啥啊，我不懂啊

一个 $O(n^3)$ 的 $dp$ 做法：

考虑一下，如果手动打开的已经钦定了，它满足两个条件：

1. 第一个和最后一个是手动开的

2. 每个连续段的间距为 $1$ ，否则会有没自动打开的

那么可以考虑 $dp_{i,j}$ 表示最后一段末尾为 $i$ ，已分 $j$ 段的排列数。段与段之间互相独立，所以先算当前段在排列中哪些位置，用组合数算一下；再段内排列。

段内排列的方案数怎么算？已钦定是手动打开，它就不能自己打开。不难发现，已开的只能是连续区间，每次在左右开。若长度为 $x$ ，则方案数为：

$\sum\limits_{i=1}^x\dbinom{x-1}{i-1}=2^{x-1}$

然后转移就是 $dp_{i,j}=\sum\limits_{k=1}^{i-2}\dbinom{i-j+1}{i-k-1}2^{i-k-2}dp_{k,j-1}$

初始化 $dp_{i,1}=2^{i-1}$ ,答案即为  $\sum\limits_{i=1}^ndp_{n,j}$ 。

code：

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int T,n,mod,dp[410][410],p2[410],jc[410],c[410][410];
    int main(){
    		scanf("%d%d",&n,&mod);p2[0]=jc[0]=1;
    		c[0][0]=1;
    		for(int i=1;i<=n;i++){
    			c[i][0]=1;
    			for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    		}
    		for(int i=1;i<=n;i++)p2[i]=p2[i-1]*2%mod,jc[i]=1ll*jc[i-1]*i%mod;
    		for(int i=1;i<=n;i++)dp[i][1]=p2[i-1];
    		for(int j=2;j<=n;j++)for(int i=1;i<=n;i++)
    			for(int k=1;k<i-1;k++)(dp[i][j]+=1ll*p2[i-k-2]*c[i-j+1][i-k-1]%mod*dp[k][j-1]%mod)%=mod;
    		int ans=0;
    		for(int i=1;i<=n;i++)(ans+=dp[n][i])%=mod;
    	return printf("%d",ans),0;
    }
```


---

## 作者：lgswdn_SA (赞：1)

首先发现最终手动打开的电脑一定组成了很多连续段，且各个连续段间有一个自动打开的电脑。

对于一个长 $x$ 的连续段，打开的方式有 $2^{x-1}$ 种（从中间往两边推进）。各个连续段之间互不影响，只是内部的步数是段内自己钦定的。所以假设一共有 $k$ 段，每段为 $x_1,x_2,\dots,x_k$，答案即为
$$
\prod_{i=1}^{k} \binom{\sum_{j=1}^{i} x_j}{x_i}2^{x_i}
$$
对这个求和可以 DP。设 $f(i,j)$ 表示前 $i$ 台电脑，分了 $j$ 段（留下 $j-1$ 个自动打开的位置）。
$$
f(i,1)=2^{i-1}
$$
$$
f(i,j)=\sum_{k\le i-2}f(k,j-1)\times \binom{i-j+1}{i-k-1}\times 2^{i-k-1}
$$
https://codeforces.com/contest/1515/submission/114950103



---

## 作者：jun头吉吉 (赞：1)

## 题意
有 $n$ 个数。可以按顺序选若干个，满足以下条件：

- 如果已经选了 $i-1$ 和 $i+1$，自动选 $i$ $(2\le i\le n-1)$
- 不能重复选，也不能漏掉一个

求这样的方案数。
## 题解
[$\tiny\color{skyblue}\text{在Blog上查看}$](https://chen-jia-liang.gitee.io/article/CF1515E.html)

$\rm CF$ 救命题。直接 $\bf EGF$ 莽就好了。

现在看来，似乎有更优的解法，反正 $\rm CF$ 机子快暴力随便过。

既然是救命题当然要好好写题解了。

首先考虑自动选的数，那么这些数把整个序列分成了若干段。细心观察就会发现，每一段内的数选其实是要有一定顺序的。

那么一个连续的段有多少选法呢。假设这个段长度为 $n$，那么方案数就是 $2^{n-1}$，考场上观察长度 $=1,2,3$ 观察出来这个结论，现在来证明一波。如果钦定了起始点 $i$，那么 $1\sim i-1$，$i+1\sim n$ 的各段的相对位置已经选好了。因此只要在剩下的 $n-1$ 个位置中挑选 $i-1$ 个位置放小于 $i$ 的数，剩下的放大于 $i$ 的数。

考虑一个合法的顺序本质就是分配编号，因此使用 $\bf EGF$

把一个块的 $\bf EGF$ 记为$F(x)$

那么知道了一个连续段，剩下的就好办了。只需要枚举有多少个块就行了。

假如有 $i$ 个块，那么给答案加上 $(n-i+1)![x^{n-i+1}]F^i(x)$ 就做完了。

这个解法是 $\mathcal O(n^3\log n)$ 的，如果用任意模数 $\rm NTT$ 就是 $\mathcal O(n^2\log n)$ 了。

如有讲错或者有更优的解法欢迎 $\rm D$ 爆这个屑。
## 代码
给出考场上的 $\mathcal O(n^3\log n)$
```cpp
#include<bits/stdc++.h>
using namespace std;
int mod;
struct modint{
    int x;
    modint(int o=0){x=o;}
    modint &operator = (int o){return x=o,*this;}
    modint &operator +=(modint o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint &operator -=(modint o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint &operator *=(modint o){return x=1ll*x*o.x%mod,*this;}
    modint &operator ^=(int b){
        modint a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint &operator /=(modint o){return *this *=o^=mod-2;}
    modint &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint &operator /=(int o){return *this *= ((modint(o))^=mod-2);}
    template<class I>friend modint operator +(modint a,I b){return a+=b;}
    template<class I>friend modint operator -(modint a,I b){return a-=b;}
    template<class I>friend modint operator *(modint a,I b){return a*=b;}
    template<class I>friend modint operator /(modint a,I b){return a/=b;}
    friend modint operator ^(modint a,int b){return a^=b;}
    friend bool operator ==(modint a,int b){return a.x==b;}
    friend bool operator !=(modint a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint operator - () {return x?mod-x:0;}
    modint &operator++(int){return *this+=1;}
};
int n;
const int N=420;
struct poly{
	modint a[N];
	modint&operator[](int x){return a[x];}
	void init(){memset(a,0,sizeof a);}
	void cpy(poly&b){memcpy(a,b.a,sizeof a);}
}tmp,tmp1,tmp2;
void mul(poly&c,poly&a,poly&b){
	c.init();
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			if(i+j<=n)c[i+j]+=a[i]*b[j];
}
void pow(poly&res,poly a,int b){
	static poly tmp;
	res.init();res[0]=1;
	while(b){
		if(b&1)mul(tmp,res,a),res.cpy(tmp);
		mul(tmp,a,a),a.cpy(tmp);b>>=1;
	}
}
modint fac[N];
signed main(){
	scanf("%d%d",&n,&mod);
	fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	modint ans=0;
	tmp1.init();
	for(int i=1;i<=n;i++)tmp1[i]=(modint(2)^i-1)/fac[i];
	for(int i=1;i<=(n+1)/2;i++){
		pow(tmp2,tmp1,i);
		ans+=tmp2[n-i+1]*fac[n-i+1];
		//printf("%d %d\n",i,ans);
	}
	printf("%d",ans);
}
```

---

