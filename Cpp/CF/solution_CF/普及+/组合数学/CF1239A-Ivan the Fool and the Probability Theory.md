# Ivan the Fool and the Probability Theory

## 题目描述

Recently Ivan the Fool decided to become smarter and study the probability theory. He thinks that he understands the subject fairly well, and so he began to behave like he already got PhD in that area.

To prove his skills, Ivan decided to demonstrate his friends a concept of random picture. A picture is a field of $ n $ rows and $ m $ columns, where each cell is either black or white. Ivan calls the picture random if for every cell it has at most one adjacent cell of the same color. Two cells are considered adjacent if they share a side.

Ivan's brothers spent some time trying to explain that it's not how the randomness usually works. Trying to convince Ivan, they want to count the number of different random (according to Ivan) pictures. Two pictures are considered different if at least one cell on those two picture is colored differently. Since the number of such pictures may be quite large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

The picture below shows all possible random pictures of size $ 2 $ by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1239A/79c5ab51966bd63fcda5df4992b30330daa2ccc2.png)

## 样例 #1

### 输入

```
2 3
```

### 输出

```
8
```

# 题解

## 作者：zty111 (赞：10)

*这道题是16年提高组初赛试题数学题的加强版。*

固定第一个格子的颜色。

我们发现如果只有一行的话涂色总数是斐波那契数列，

当行数更多时，分两种情况：

1、第一行是10101010即没有相邻颜色时，竖着可以看成另一个斐波那契数列。

2、第一行是11001100有相邻颜色时，下一行只能是对应的不同颜色。

所以答案就是$(F[n] + F[m] - 1)\times 2$
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100010;
const int mod = 1e9 + 7;
long long f[N];
int main() {
    int n, m;
    scanf("%d %d", &m, &n);
    f[1] = f[0] = 1;
    for(int i = 2; i <= max(n, m); i++)
        f[i] = (f[i-1] + f[i-2]) % mod;
    long long ans = ((f[n] + f[m] - 1) % mod) * 2 % mod;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Meatherm (赞：7)

由一个奇妙的性质：

对于第 $i$ 行 $j$ 列的格子 $(i,j)$，如果满足 $i>1$ 或 $j>1$ 且 $(i-1,j)$，$(i-1,j-1)$ 和 $(i,j-1)$ 的颜色已经确定，那么这个格子只会有一种填法。

数据不大一共 $2^3=8$ 种情况，可以手玩推出。

也就是说确定了第一列和第一行的状态之后，整个矩阵的状态就确定了。

那么现在只需要来确定第一行和第一列的状态即可。这样就变成了一个 DP 了。

设 $f[i][0/1][0/1]$ 表示前 $i$ 个格子中最后一个格子的颜色是黑色/白色，结尾是否连续放置了两个相同颜色的格子。

初始化 $f[1][0][0]=f[1][1][0]=1$。

对于所有的 $i$ 满足 $i>1$：

- $f[i][0][0]=(f[i-1][1][0]+f[i-1][1][1]) \mod 10^9+7$。既然结尾没有连续放置两个相同颜色的格子，那么上一个格子一定是另外一种颜色，所以要从 $f[i-1][1][0/1]$ 转移。

- $f[i][0][1]=f[i-1][0][0]$。既然结尾连续放置了两个相同颜色的格子，那么上一个格子一定是相同的颜色，所以要从 $f[i-1][0][0]$ 转移。

- $f[i][1][0/1]$ 的情况类似，就不再赘述。

最终答案即为

$$((\sum_{i=0}^{1} \sum_{j=0}^{1} f[n][i][j]+f[m][i][j])-2) \mod 10^9+7$$

为什么要 $-2$ 呢？因为我们漏掉了一些不合法的情况，即 $(1,1),(1,2),(2,1)$ 颜色相同。

时间复杂度 $O(n)$。

```cpp
# include <bits/stdc++.h>
# define int long long
# define rr register
const int N=100010,MOD=1e9+7;
int f[N][2][2];
signed main(void){
	int n,m;
	scanf("%I64d%I64d",&n,&m);
	f[1][1][0]=1;
	f[1][0][0]=1;
	for(rr int i=2;i<=std::max(n,m);++i){
		f[i][0][1]+=f[i-1][0][0];
		f[i][0][1]%=MOD;
		f[i][0][0]+=f[i-1][1][1]+f[i-1][1][0];
		f[i][0][0]%=MOD;
		f[i][1][1]+=f[i-1][1][0];
		f[i][1][1]%=MOD;
		f[i][1][0]+=f[i-1][0][1]+f[i-1][0][0];
		f[i][1][1]%=MOD;
	}
/*	for(rr int i=1;i<=n;++i){
		printf("%d %d %d %d\n",f[i][0][0],f[i][0][1],f[i][1][0],f[i][1][1]);
	}*/
	printf("%I64d",((f[n][0][0]+f[n][0][1]+f[n][1][0]+f[n][1][1]+(f[m][0][0]+f[m][0][1]+f[m][1][0]+f[m][1][1])-2)%MOD));
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：5)

这题数据范围在$10^5$,而且还是二维的矩阵。  
当然如果是结论题,数据范围会更加大一些。我们应该考虑线性或线性带log。  
那么对于二维的数据,如果横纵坐标不能够独立,那么就很不可做了。  
我们猜测横纵坐标上的统计独立,然后证明:  
结论一:如果图中存在$(x, y), (x, y+1)$的颜色相同,那么不存在$(a, b), (a+1, b)$的颜色相同。  
结论二:如果图中$(x, y), (x, y+1)$颜色相同,那么$\forall t \in [1,n], (t, y)$和$(t, y+1)$的颜色相同,且$(x, y-1)$和$(x, y+1)$的颜色被确定,为与$(x, y)$不同的颜色。  
如果结论正确,那么分别统计相同为横向和纵向即可。然后,列是有一致性的,因而是在枚举列。  
因此,这个问题等价于列的12排列划分,等于$Fib$数列的项。  
答案即为:$2(Fib_n + Fib_m - 1)$
```cpp
#include <iostream>

using namespace std;

const int mode = 1e9+7, maxn = 123456;
int f[maxn];

int main() {
	ios::sync_with_stdio(false);
	int n, m, mx;
	cin >> n >> m;
	mx = max(n, m);
	f[0] = f[1] = 1;
	for(int i = 2; i <= mx; ++i) f[i] = (f[i-1] + f[i-2]) % mode;
	cout << ((f[n] + f[m] - 1) % mode) * 2 % mode << endl;
	return 0;
}
```


---

## 作者：Froggy (赞：3)

(虽然过了一个星期了,不过我还是抽空发一下考场做法)

### 第一步:演草纸上乱画

发现:相邻同色的2个格子要么都是横着的,要么都是竖着的,不可能横着竖着出现在同一个格子里

所以就可以分开算了(显然,两种情况除了长度不同没啥区别)

### 第二步:dp转移

~~不想找规律直接dp走人..~~

先考虑都是横着的情况:

每列要么是```黑白黑白黑白...```-->状态表示为$0$,要么是```白黑白黑白黑...```-->状态表示为$1$

由于连续三列不是同一种状态,所以我们要记录当前和上一列的状态,即:

$dp_{i,j,k}$表示第$i$列的状态为$j$,第$i-1$列的状态为$k$  $(j,k \in \{0,1\}$)

#### 转移方程:(根据连续三列不是同一种状态)

第i列与第i-1列状态相同:

$dp_{i,0,0}=dp_{i-1,0,1}$

$dp_{i,1,1}=dp_{i-1,1,0}$

第i列与第i-1列状态不同:

$dp_{i,0,1}=dp_{i-1,1,0}+dp_{i-1,1,1}$

$dp_{i,1,0}=dp_{i-1,0,0}+dp_{i-1,0,1}$

保证转移是$O(1)$的

### 第三步:细节!

#### 初始化:
$dp_{1,1,0}=dp_{1,0,0}=1$(我竟闲到把第2列也初始化了)

#### 容斥:
最后答案要-2

**原因**:

```
黑白黑白黑白...
白黑白黑白黑...
黑白黑白黑白...
白黑白黑白黑...
...
```

和

```
白黑白黑白黑...
黑白黑白黑白...
白黑白黑白黑...
黑白黑白黑白...
...
```

(黑白相间的)分别被计算了两次

### *STEP 4:show me your code*:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 100010
typedef long long ll;
const ll mod=1e9+7;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,m;
ll dp[N][2][2];
ll ans=0;
void solve(int n){
	memset(dp,0,sizeof(dp));
	dp[1][0][0]=dp[1][1][0]=1;
	dp[2][0][1]=dp[2][1][0]=dp[2][1][1]=dp[2][0][0]=1;
	for(int i=3;i<=n;i++){
		dp[i][0][1]=dp[i-1][1][1]+dp[i-1][1][0];
		dp[i][1][0]=dp[i-1][0][1]+dp[i-1][0][0];
		dp[i][0][0]=dp[i-1][0][1];
		dp[i][1][1]=dp[i-1][1][0];
		for(int j=0;j<=1;j++){
			for(int k=0;k<=1;k++){
				dp[i][j][k]%=mod;//瞎mod一下
			}
		}
	}
	ans+=dp[n][0][1]+dp[n][1][0]+dp[n][1][1]+dp[n][0][0];
	ans%=mod;
}
int main(){
	n=read(),m=read();
	solve(n),solve(m);//算一遍横的,再算一遍竖的
	cout<<(ans-2+mod)%mod<<endl;
	return QAQ;
}

```

就这吧,懒得滚动数组了

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!


---

## 作者：开始新的记忆 (赞：3)

题目大意：给定一个 n \times mn×m 的方格图，每个格子可以被染成黑色或白色，且与其相邻的格子（上，下，左，右）中至多只有一个与其颜色相同。求方案数。

思路：首先我们可以发现，如果有相邻两块颜色一样，那么他们下一行一定是确定的，因为这两块的下面两个块颜色不能与之相同，L状是不能出现的。然后就可以发现，无论旁边是什么颜色，都会与之相反。（简单地说就是，第一行如果存在相邻两块颜色一样，那么这个图形整个的图案就确定了）

还有一种黑白交错的，但是由于这样的话如果你确定了首行和首列的话那么其实满足题意的情况就只有一种了。

故题目转化成了求一行一列的满足题意的情况有多少种。

设f[i][0]为第i个填白色的方案数，f[i][1]表示第i个填黑色的方案数，那么显而易见，f[1][0]=f[1][1]=1，f[2][0]=f[2][1]=2。

所以f[i][0]=f[i-1][1]+f[i-2][1]，f[i][1]=f[i-1][0]+f[i-1][0]，合并，发现f[i][0]+f[i][1]=f[i-1][0]+f[i-1][0]+f[i-1][1]+f[i-2][1]，那就直接合并，ans[i]=ans[i-1]+ans[i-2]
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
ll ans[100010];
int n,m;

int main()
{	cin>>n>>m;
    ans[1]=2;ans[2]=4;
    for(int i=3;i<=max(n,m);++i)
        ans[i]=(ans[i-1]+ans[i-2])%P;
    cout<<(ans[n]+ans[m]-2+P)%P<<endl;
    return 0;
}
```


---

## 作者：BADFIVE (赞：1)

**题意**：有一个 $n \ast m$ 网格，每个格可以被涂成白色或黑色，现在定义随机图 ：每个点的上下左右最多只有一个格与其颜色相同，请计算其数量，对 $10^9+7$ 取模。   
**思路**：对于一个 $(i,j)$，如果它的左、左上、上的颜色确定了，那么它的颜色就确定了。   
那我们就枚举 $(1,1)$ 的所有颜色，然后将第一行第一列的颜色都确定下来，这个时候的行列都是独立的。   
所以说答案就相当与一个排列划分，答案为： $2 \ast (f[n]+f[m]-1)$。

参考代码：   
```
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int f[5000001];
int main(){
    int m,n;
    cin>>m>>n;
    f[0]=f[1]=1;
    for(int i= 2;i<=max(n,m);i++)f[i]=(f[i-1]+f[i-2])%mod;
    int ans=((f[n]+f[m]-1)%mod)*2%mod;
    cout<<ans;
}
```

---

## 作者：songhn (赞：0)

### 题意简述：
给定一个 $n\cdot m$ 的方格图，每个格子可以被染成黑色或白色，且与其相邻的四个格子中至多只有一个与其颜色相同，求方案数。
### 题解：
我们可以一行一行的考虑，首先假如第一行存在连续的两个1，那么后面的状态就全部可以推出，因为下面两个肯定是0，然后所有状态就可以一步步推出来。相邻没有连续的只有一种情况即101010...注意我们此时只考虑一个大类，实际上01可以取反所以最后算出的状态要乘2

在101010...的情况下，第一行没有影响，所以第一列会产生影响，这种情况和之前一样，所以我们只要考虑第一行或者第一列合法的有多少状态即可，要么一个要么两个，其实这就是斐波那契数列。当然我们也可以写一个dp

f[i][0]表示第i个是黑色，f[i][1]表示第i个是白色，有如下dp式

$f[i][0]=f[i-1][1]+f[i-2][1]$

$f[i][1]=f[i-1][0]+f[i-2][0]$

$f[0][0]=f[0][1]=f[1][1]=f[0][0]=1$

当然这个dp式的值其实就是斐波那契

然后我们算出$f[n]$注意10101..的情况要去掉给列考虑，所以有$f[n]-1$个状态，列又有$f[m]$个状态，最后01取反，所以状态共有$(f[n]+f[m]-1)\cdot 2$

注意由于有减法所以模意义下有可能会变成负数，所以需要(x%p+p)%p这样的操作
### AC代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
#include<set>
#define ll long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define mst(a,b) memset((a),(b),sizeof(a))
#define PII pair<int,int>
using namespace std;
template<class T>inline void read(T &x) {
    x=0; int ch=getchar(),f=0;
    while(ch<'0'||ch>'9'){if (ch=='-') f=1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    if(f)x=-x;
}
const int inf=0x3f3f3f3f;
const int mod=1e9+7; 
const int N=100000;
const int maxn=100050;
ll f[maxn][2];
ll n,m;
void init(int n)
{
	f[1][1]=1,f[1][0]=1,f[0][0]=1,f[0][1]=1;
	for(int i=2;i<=n;i++)
	{
		f[i][1]=(f[i-1][0]+f[i-2][0])%mod;
		f[i][0]=(f[i-1][1]+f[i-2][1])%mod;
	}
		
}
int main()
{
	init(N);
	cin>>n>>m;
	cout<<((((f[n][1]-1+f[m][1])*2)%mod+mod)%mod)<<endl;
	return 0;
}

```

---

## 作者：Cesare (赞：0)

来一种奇怪的找规律做法。

先写一份暴力：

```cpp
while (cin >> n >> m) {
	Ans = 0;
	ll Max = (1 << (n * m)) - 1;
	For ( S, 0, Max ) {
		For ( i, 1, n ) For ( j, 1, m ) 
			mp[i][j] = (S & (1 << (id(i, j) - 1))) > 0;
		Ans += Check();
	} wln(Ans);
} return 0;
```

然后打出一份表：

$$
(1, 1) \to 2,\ (1, 2) \to 4,\ (1, 3) \to 6,\ (1, 4) \to 10
$$
$$
(2, 1) \to 4,\ (2, 2) \to 6,\ (2, 3) \to 8,\ (2, 4) \to 12
$$
$$
(3, 1) \to 6,\ (3, 2) \to 8,\ (3, 3) \to 10,\ (3, 4) \to 14
$$

然后发现第一行是一个广义斐波那契数列，第二、三行差分一次之后就也是这个斐波那契数列了。
设 $f[1] = 2, f[2] = 4$ ，后面初始 $g[i][1] = f[i], g[i][2] = f[i] + 2$

然后有

$$
g[i][j] = g[i][j - 1] + f[j - 2] (j >= 3)
$$

把最后一行的结果搞出来即可。

---

## 作者：Heartlessly (赞：0)

## Description

给定一个 $n \times m$ 的方格图，每个格子可以被染成黑色或白色，且与其相邻的格子（上，下，左，右）中至多只有一个与其颜色相同。求方案数，对 $10^9 + 7$ 取模。

## Solution

先考虑 $n = 1$ 怎么做。

用 $f_{i,0/1}$ 表示填了前 $i$ 个格子，最后一个格子的颜色是白色/黑色的方案数。

初始有 $f_{0,0/1}=f_{1,0/1} = 1$ 。

对于 $f_{i,0}$，可以通过第 $i - 1$ 格填什么颜色转移。如果填的是黑色，则 $f_{i - 1,1}$ 都是合法方案。如果填的是白色，则 $f_{i - 2,1}$ 都是合法方案。
$$
f_{i,0} = f_{i - 1,1} + f_{i - 2,1}
$$
一个很显然的性质：$f_{i,0} = f_{i,1}$（把以白色结尾的任意一种合法方案取反，都能得到一种新的以黑色结尾的方案）

所以有 $f_{i,0} = f_{i - 1,0} + f_{i - 2,0}$，且 $f_{i,1} = f_{i,0}$ 。

若我们用 $fib_i$ 表示斐波那契数列的第 $i$ 项，那么 $n = 1$ 时的方案数就是 $f_{m,0} + f_{m,1} = 2fib_m$ 。

对于一行中所有的合法方案，我们再分两种情况：

方案 1：有白色/黑色连续

方案 2：黑白相间（只有两种情况，情况 1 是 `010101...`，情况 2 是 `101010...`）

对于方案 1，第一行确定了，接下来的每一行都有且只有一种方案（将上一行取反），方案数为 $2fib_m - 2$ 。

对于方案 2，我们不妨把情况 1 看做白色格子，情况 2 看做黑色格子。

显然在 $n$ 行里，白色格子和黑色格子最多只能连续出现 $2$ 次，那么方案数就和 $n = 1$ 一样了，即 $2fib_{n}$ 。

最终答案就是 $2fib_{n} + 2fib_{m} - 2$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
int n, m, f[MAXN + 5];

int main() {
    read(n), read(m);
    f[0] = f[1] = 1;
    for (int i = 2; i <= max(n, m); ++i) f[i] = (f[i - 1] + f[i - 2]) % MOD;
    write((((f[n] << 1) % MOD + (f[m] << 1) % MOD) % MOD - 2 + MOD) % MOD);
    putchar('\n');
    return 0;
}
```



---

## 作者：两年打铁 (赞：0)

先手模几个，我们可以发现如果第一行和第一列确定，那么一个方案是确定的。

因为根据第一行和第一列，可以依次顺推出剩下的所有格子的颜色。

那么问题就变成了只确定第一行和第一列有多少方案。

如果是只确定一行的话，我们可以进行dp
设$f_{i,0/1}$表示当前填0/1,如果同种颜色从前面转移的话我们发现会重复，那么我们强制不重复，即只从不同颜色那里转移，钦定当前的两格还是一格是同种颜色，然后转移就变成了一个斐波那契数列的转移。


但是答案并不是$2(f_n+f_m)$因为我们的方案数还包括了第一行的第二格和第一列第二格和第一行第一格相同，因为只可能填黑或白，减去2就可以了

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define kong putchar(' ')
#define huan putchar('\n')
#define bug puts("QWQ")
#define pr putchar
#define int long long 
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[100];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
inline void wrs(const int &x)
{
	write(x);
	putchar(' ');
}

inline void wrl(const int &x)
{
	write(x);
	putchar('\n');
}
int n,m,f[1000000];

const int mod=1e9+7;
#undef int 
int main()
{
	read(n);
	read(m);
	f[0]=1;
	for(register int i=1;i<=max(n,m);++i)
	{
		f[i]=f[i-1]+f[i-2];
		f[i]%=mod;
	}
	cout<<(f[n]+f[m]-1)*2%mod<<endl;
}
```


---

## 作者：big_news (赞：0)

## Fibonacci数列

数论不会先打表系列。

单考虑一行的情况：手模一下，1\*1时答案为2，1\*2时答案为4，1\*3时答案为6，1\*4时答案为10...

把答案搞出来，这个时候规律就已经很显然了：(2) 2 4 6 10 .... 这是一个普通的Fibonacci数列的两倍。

也就是这个递推式：$f[0] = f[1] = 2, f[i] = f[i-1]+f[i-2]$。

对于单一列也同理。

然后根据楼下讲的很明白的那个性质，确定了元素$(i-1,j),(i-1,j-1),(i,j-1)$即确定了元素$(i,j)$，我们就可以得到最终的答案为$f[n]+f[m]-2$。

然后就做完了。

代码
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
const int CN = 1e5+5;
const int R = 1e9+7;
int n,m,f[CN];
int main()
{
	scanf("%d%d",&n,&m);
	f[0] = 2,f[1] = 2;
	for(int i=2;i<=max(n,m);i++) f[i] = (f[i-1]+f[i-2]) % R;
	printf("%d", (f[n]+f[m]-2) % R);
	return 0;
}
```

---

## 作者：Llf0703 (赞：0)

[更好的阅读体验](https://llf0703.com/p/cf-1248.html#civanthefoolandtheprobabilitytheory)

先考虑只有一行的情况，令斐波那契数列的第 $m$ 项为 $f_m$ ，那么方案数为 $f_m\times 2$ （黑白可以交换）。

如果第一行中不存在同种颜色相邻的情况，有 $2$ 种方案：这时确定了第一列就确定了整个图，所以答案为 $2f_n$ 。

如果第一行存在同种颜色相邻的情况，有 $f_m\times 2-2$ 种方案：这时整张图就确定了，答案为 $2f_m-2$ 。

总的答案即为 $2f_n+2f_m-2$ 。

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1239A) & [原题链接](http://codeforces.com/problemset/problem/1239/A)

~~申请降级……太水了~~

---

**题意：**

我们先来看看题面：
>给定一个 $n \times m$ 的方格图，每个格子可以被染成黑色或白色，且与其相邻的格子（上，下，左，右）中至多只有一个与其颜色相同。求方案数。

额……翻译成能听懂的就是：
>给你一个 $n \times m$ 的矩阵，你要对它进行黑白染色，要求十字相邻的格子里最多能有1种颜色相同，求染色方案数？

---

**解题：**

首先，这是一道**数学**题。

我们先把第一个格子的颜色染了，有 $2$ 种染色方案（废话）。

然后，我们先看只有一行的情况，那你会惊讶地发现方案数是一个**斐波那契数列**。

于是，第一行解决后，我们看多行的情况。

我们可以分两种情况讨论：
1. 上一行没有相邻颜色一样的，那就肯定是黑白相间的，那么竖着看，也是一个**斐波那契数列**
2. 上一行要是有相邻颜色一样的，那么下一行就只能上一行的颜色相反了

所以，我们推出答案的式子（用 $a_n$ 表示斐波那契的第 $n$ 项（从0开始））：

$$2\times(a_n+a_m-1)$$

然后，我们就可以用这个式子去写代码啦！

时间复杂度：$\Theta(\max(n,m))$

---

**代码：**

压行不适请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,ans,t=1,tt=1;
int main()
{
	cin>>n>>m;
	if(n<2)ans++;
	if(m<2)ans++;
	for(register int i=2;i<=max(n,m);i++)tt+=t,t=tt-t,tt%=mod,t%=mod,ans+=((i==n)?tt:0)+((i==m)?tt:0),ans%=mod;
	cout<<(ans-1+mod)*2ll%mod;
	return 0;
}
```

极限压行~~其实本来就很短~~：

```cpp
#include<bits/stdc++.h>
using namespace std;const int mod=1e9+7;int n,m,ans,t=1,tt=1;int main(){cin>>n>>m;if(n<2)ans++;if(m<2)ans++;for(register int i=2;i<=max(n,m);i++)tt+=t,t=tt-t,tt%=mod,t%=mod,ans+=((i==n)?tt:0)+((i==m)?tt:0),ans%=mod;cout<<(ans-1+mod)*2ll%mod;return 0;}
```

---

