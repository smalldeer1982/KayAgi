# [ARC116B] Products of Min-Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc116/tasks/arc116_b

長さ $ N $ の整数列 $ A $ が与えられます。$ A $ の空でない部分列 $ B $ は $ 2^N\ -\ 1 $ 個あります。これらについて $ \max\left(B\right)\ \times\ \min\left(B\right) $ の値を計算し、その総和を答えてください。

ただし、答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 998244352 $

### Sample Explanation 1

$ B $ として、以下の $ 7 $ つが考えられます。 - $ B\ =\ \left(2\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 4 $ - $ B\ =\ \left(4\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 16 $ - $ B\ =\ \left(3\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 9 $ - $ B\ =\ \left(2,\ 4\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 8 $ - $ B\ =\ \left(2,\ 3\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 6 $ - $ B\ =\ \left(4,\ 3\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 12 $ - $ B\ =\ \left(2,\ 4,\ 3\right) $ : $ \max\left(B\right)\ \times\ \min\left(B\right)\ =\ 8 $ 以上の $ 7 $ つの値を足した値 $ 63 $ が答えです。

## 样例 #1

### 输入

```
3
2 4 3```

### 输出

```
63```

## 样例 #2

### 输入

```
1
10```

### 输出

```
100```

## 样例 #3

### 输入

```
7
853983 14095 543053 143209 4324 524361 45154```

### 输出

```
206521341```

# 题解

## 作者：CQ_Bab (赞：5)

# 前言
这道题是因为看到某个 CC 怪发了题解，然后才来做的，然后这一道黄题我竟和 SYC 大佬推了整整 $40$ 多分钟。然后准备发题解，发现题解第一篇的作者竟然真的是抄的。
# 思路
我们明显可以得到一个 $n^2$ 的代码，就是枚举最大值和最小值然后在中间任选即可（当然要先排序）。

公式就是。
$$
Ans=\sum_{i=1}^{n}(a_i\times a_i+\sum_{j=i+1}^{n}a_i\times a_j\times2^{j-i-1})
$$

这里是主要代码：
```cpp
for (re int i = 1;i <= n;i++){
	for (re int j = i + 1;j <= n;j++) ans = Add(ans,Mul(Mul(arr[i],arr[j]),pot[j - i - 1]));
	ans = Add(ans,Mul(arr[i],arr[i]));
}
```

然后我们就像一下如何优化，既然第一层 $i$ 没办法优化，那么我们就将公式中的只给优化掉。

所以在这里我们定义 $m_i=\sum_{j=1}^{i} a_i\times 2^i$，那么我们乍一看是不是没办法优化。

这里我们在来展开看一下，我们用 $m_n-m_i$ 不就是 $\sum_{j=i+1}^{n} a_j\times 2^j$ 然后我们发现对于每一个 $j$ 是不是 $2$ 的指数都多乘了 $2^{i+1}$。

那么我们就可以得出一个公式。

$$
Ans=\sum_{i=1}^{n} \frac{(m_n-m_i)} {2^{i+1}}\times a_i+a_i\times a_i
$$

然后这道黄题你就可以过了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scnaf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=2e5+10;
int m[N],n,inv[N],pot[N],a[N];
const int mod=998244353;
int res;
int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a)%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void init() {
	pot[0]=1;
	rep(i,1,n+1) {
		pot[i]=pot[i-1]*2%mod;
		m[i]=(m[i-1]+a[i]*pot[i])%mod;
		inv[i]=qmi(pot[i],mod-2);
	}
}
fire main() {
	scanf("%lld",&n);
	rep(i,1,n) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	init();
	rep(i,1,n) {
		res=(res+a[i]*a[i])%mod;
		res=(res+a[i]*(m[n]-m[i]+mod)%mod*inv[i+1]%mod)%mod;
	}
	print(res);
	return false;
}

```

---

## 作者：Jekyll_Y (赞：4)

# 题解

## 题目大意

给定一个长度为 $n$ 的序列，这个序列显然有 $2^{n - 1}$ 个非空子序列，定义每个子序列的贡献为这个子序列的最大值和最小值的乘积， 求所有非空子序列的权值和，对 $998244353$ 取模。

## 数据限制

$ n \le 2 \times 10 ^ 5$ ， $0 \le a_i \le 998244353$ 。

## 解法

可以先将序列从小到大排序固定然后固定住最大值，直接统计贡献即可，比如排序后固定住最小值为 $a_i$ ， 最大值为 $a_j (i < j)$ ， 贡献即为 $a_i a_j 2 ^ {i - j - 1}$ 。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 2e5 + 10;
const int mod = 998244353;
const int INF = 1e9;

int n, a[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    ll ans = 0, sum = 0;
    for(int i = 1; i <= n; i++)
    {
        ans = (ans + a[i] * (sum + a[i]) % mod) % mod;
        sum = sum * 2ll % mod; sum = (sum + a[i]) % mod;
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：WaterSun (赞：3)

# 思路

我们容易可以得到一个朴素的做法，首先对 $a$ 数组排序，然后枚举最大值和最小值 $a_i,a_j$，那么对于中间的元素都有选与不选两种情况，得到答案：

$$
\sum_{i = 1}^{n}(a_i \times a_i + (\sum_{j = i + 1}^{n}a_i \times a_j \times 2^{j - i - 1}))
$$

然后对这个式子做一个化简：

$$
\sum_{i = 1}^{n}(a_i \times a_i + a_i \times (\sum_{j = i + 1}^{n}a_j \times 2^{j - i - 1}))
$$

发现对于每一个 $i$，$a_j \times 2^{j - i - 1}$ 都是类似的，所以考虑预处理。

定义 $m_i = \sum_{j = 1}^{i}(a_j \times 2^j)$，那么发现：

$$
m_n - m_i = \sum_{j = i + 1}^{n}{a_j}\times 2^j
$$

然后，发现对于每一项 $j$ 对于原式都多乘了一个 $2^{i + 1}$，直接除掉即可。得答案为：

$$
\sum_{i = 1}^n{(a_i \times a_i + \frac{m_n - m_i}{2^{i + 1}} \times a_i)}
$$

时间复杂度 $\Theta(n \log n)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n,ans;
int arr[N],pot[N],mul[N],inv[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int Add(int a,int b){
	return (a + b) % mod;
}

inline int Sub(int a,int b){
	return ((a - b) % mod + mod) % mod;
}

inline int Mul(int a,int b){
	return a * b % mod;
}

inline void exgcd(int a,int b,int &x,int &y){
	if (!b){
		x = 1;
		y = 0;
		return;
	}
	exgcd(b,a % b,y,x);
	y = y - a / b * x;
}

inline int get_inv(int a,int p){
	int x,y;
	exgcd(a,p,x,y);
	return (x % mod + mod) % mod;
}

inline void init(){
	pot[0] = 1;
	for (re int i = 1;i <= n + 1;i++){
		pot[i] = Mul(pot[i - 1],2);
		mul[i] = Add(mul[i - 1],Mul(arr[i],pot[i]));
		inv[i] = get_inv(pot[i],mod);
	}
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	sort(arr + 1,arr + n + 1);
	init();
	for (re int i = 1;i <= n;i++){
		ans = Add(ans,Mul(Mul(Sub(mul[n],mul[i]),inv[i + 1]),arr[i]));
		ans = Add(ans,Mul(arr[i],arr[i]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

在题库里面乱翻，就翻到了。

因为在这道题里面子序列不需要考虑元素顺序，所以原序列无论是什么顺序都不会影响答案。

所以先把元素按照从大到小的顺序排列，然后考虑每个元素的贡献。

在当前序列中，对于元素 $a_i$，不妨设其为最小值，并去寻找它能作为哪些序列的最小值。容易发现它作为最小值的时候只能和 $1\sim i$ 中的元素产生贡献。

具体的，对于当前从 $1\sim i$ 中选择的 $a_j$，如果令其为最大值，那么由 $a_i$ 和 $a_j$ 这两个值作为最值的序列元素一定都在 $j\sim i$ 之间，学过集合的同学都知道，这样的序列显然有 $2^{i-j-1}$ 个。

这样我们就可以得到一个 $\mathcal{O}(n^2)$ 的解法，如下：
$$\sum_{i=1}^{n}(a_i\times(\sum_{j=1}^{i}(a_j\times 2^{i-j-1})))$$

由于 $i-j-1$ 中会出现负数，我们稍微变一下式子可以得到：

$$\sum_{i=1}^{n}(a_i\times(\sum_{j=1}^{i-1}(a_j\times 2^{i-j-1})+a_i))$$
但是这样显然还不够，于是我们可以
对 $j$ 的枚举进行优化。容易想到预处理。

我们用一个中间变量 $sum$ 表示第二个括号里面的值。每次计算过答案以后，我们让 $sum\gets sum\times 2+a_i$ 即可。

记得取模。

[提交记录](https://atcoder.jp/contests/arc116/submissions/57263535)

---

## 作者：_weishiqi66_ (赞：1)

对于本题。由于 $A$ 会有 $2^N-1$ 的非空子序列，且 $1 \leq N\leq 2\times 10^5 $ 。所以一个个暴力枚举，然后找最大值最小值肯定不行。通过这个暴力的角度我们可以想到，知道对于每个子序列我们不关心子序列的具体信息。我们只关心它的最大值最小值。而对于序列中的每个数来说，它都有可能成为子序列的最大值最小值。

因此我们考虑，对于每一个数来说将其看成最小值，考虑每个数会成为它搭配最大值的次数。具体操作，将序列从大到小进行排序。依次考虑每个数作为最小值的贡献。简单推理可以的出。

$ans =\sum_{i=1}^{n} a_i \times (\sum_{j=1}^{i-1} a_j \times 2^{i-j-1}+a_i )$ 

简单分析一些时间复杂度 $O(n^{2})$ ，对于这道题这显然还不够优秀。通过观察式子，我们可以很容易想到优化。具体见代码，思路参考[秦九韶算法](https://baike.baidu.com/item/%E7%A7%A6%E4%B9%9D%E9%9F%B6%E7%AE%97%E6%B3%95/449196)。

代码
```
#include <bits/stdc++.h>
#define int unsigned long long 
using namespace std;

const int N=1E6;
const int mod=998244353;
int n,a[N],ans,sum;

bool cmp(int x,int y){
	return x>y;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) {
		ans= (ans+(a[i]*(sum+a[i])%mod)%mod)%mod;
		sum=sum*2%mod; sum=(sum+a[i])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

连黄题都没法一眼掉，我太菜了。      
甚至看题解也好久才看懂（外加手推了一大坨式子），于是励志写一篇通俗易懂的。  

------
首先肯定不可能手动数出一个个子序列对吧。    
那么自然会考虑对于每一个数计算它的贡献。    
那么问题就来了，具体如何计算它的贡献呢？我怎么去统计当一个数是一个子序列的最大值的时候，这个子序列有多少个，以及这些子序列的最小值是什么呢？   
打住，为什么偏要只固定最大值？为什么不能**同时固定最大值和最小值**呢？        
是啊，这样的话就只用**计算符合条件的子序列个数**就可以了。      
（得，校内模拟赛的时候偏偏只想着怎么只固定最大值计算贡献，结果愣是想不出来怎么敲。）        
你说这样的话难道不会超时吗？没关系，到后面我们再进行优化。      

--------

如何计算符合条件的子序列个数？     
肯定不能一个一个去数，但我们要意识到无论顺序如何打乱，该存在的子序列还是会存在的。    
顺序打乱？那肯定要**排序**啊！     
把数组从小到大排序之后，若**固定最大值为第 $i$ 个元素，最小值为第 $j$ 个元素（易得 $i>j$）**，则符合条件的子序列有 $2^{i-j-1}$ 个。      
但还有一种情况，就是**子序列只包括 $a_i$ 一个元素**。这时这个子序列对答案的贡献就是 $(a_i) \,^2$。     
所以可得最终答案为：
$$\sum^n_{i=1}\,a_i\,\times\,((\sum^{i-1}_{j=1}a_j \times 2^{i-j-1}) \, +a_i)$$    

---------

如果暴力去求的话，时间复杂度至少是平方级。        
现在我们重新审视一下这个式子，看看是否有能优化的地方。   
第一层循环看样子是无法优化了，考虑优化第二层。      
考虑在一次循环中的 $\sum^{i-1}_{j=1}a_j \times 2^{i-j-1}$ 能否通过上一次循环的结果得到。      
把式子拆开得到原式 $=a_{i-1} \times 2^0\,+\,a_{i-2} \times 2^1\,+a_{i-3}\, \times 2^2 \, + \dots + a_1\, \times 2^{i-2}$。       
再思考这些 $a_{i-1},a_{i-2},\, \dots \, a_1$ 的项在上一次循环中的系数是多少。       
可以得到，$a_{i-1}$ 系数是 $0$（也就是说这个 $a_{i-1}$ 是上一次循环统计完答案后再加上的），$a_{i-2}$ 系数是 $1$，$a_{i-3}$ 系数是 $2$，依次直到 $a_1$ 的系数是 $2^{i-3}$。           
发现没有？每过一次循环，每一项的系数就会乘 $2$。    
因此，设 $x_i=\sum^{i-1}_{j=1}a_j \times 2^{i-j-1}$，则 $x_i=x_{i-1} \times 2  \,+a_i$。     
答案也就变成了：
$$\sum^n_{i=1}\,a_i\,\times\,(x_i \, +a_i)$$
于是时间复杂度就被优化到了 $O(n \log n)$。            
（其实这是排序的复杂度。）  

------

最后在代码实现的时候，记得 $\bmod \, 998244353$。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long sum,ans,n,s[200005];
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]);
    sort(s+1,s+n+1);
    for(int i=1;i<=n;i++) ans=(ans+s[i]*(sum+s[i])%998244353+998244353)%998244353,
    sum=((sum<<1)%998244353+s[i]+998244353)%998244353;
    printf("%lld",ans);
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

# AT_arc116_b [ARC116B] Products of Min-Max
数学好题。。。
## 解法
平方级解法肯定是不行的，我们考虑拆贡献。先将数组从小到大排序，固定第 $i$ 位为最大值，此时我们就需要算以 $a_i$ 末尾的子序列的最小值的和，先算 $a_j$ 对此次计算的贡献，应为我们已经从小到大排过序了，所以第 $j$ 位以前的数肯定是不可以选的，只能选 $j + 1 \sim i - 1$ 的数，而这些数无论怎样都无法影响到最大值和最小值，所以可以随便选，最小值都是 $a_j$，那么，$a_j$ 就被加了 $2^{i - j - 1}$ 次，对以 $a_i$ 位末尾的情况的贡献就是 $2^{i - j - 1} \times a_j$。但是，这里还有一种情况，就是只选 $a_i$ 的情况，这也很简单，贡献就是 $a_i \times a_i$，那么总贡献就是 $(\sum_{j = 1}^{i - 1} ({2^{i - j - 1} \times a_j})) \times a_i + a_i \times a_i$，但是但是，这样很显然是会超时的，所以我们可以使用一个数组 $s$ 来算出当以 $a_i$ 为末尾时的最小值的和，这里可以运用前缀和的思想，简单推一下即可得到柿子 $s_i = s_{i - 1} \times 2 + a_{i - 1}$，其中 $i = 2 \sim n$，那么原先的柿子就变为了 $s_i \times a_i + a_i \times a_i$。这样，就可以以线性的时间复杂度解决题目了！

## 注意事项

注意取模鸭！

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10, mod = 998244353;

int n, res;
int a[N], s[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	
	sort(a + 1, a + n + 1);
	
	for (int i = 2; i <= n; i++) 
		s[i] = (s[i - 1] * 2 + a[i - 1]) % mod;
	for (int i = 1; i <= n; i++)
		(res += (s[i] * a[i] % mod + a[i] * a[i] % mod) % mod) %= mod;
	 
	cout << res << '\n';
	
	return 0;
}
/*
7
853983 543053 143209 4324 524361 45154 14095
998244352 

4
3 3 3 3
*/
```

---

## 作者：Davis1 (赞：0)

题解：

看到比较大小，和子序列，说明顺序不影响结果，又有关大小，所以果断排序找规律。

先看例子：$2,4,3,5$ 

排序后为：$2,3,4,5$ 

先从前往后一个个看：当子序列最后一个数为 $2$ 时，因为排了序，所以子序列最大值为 $2$，子序列第一个为最大值，所以现在只用看子序列第一个数有几种情况，很显然，可以是 $2$，那么 $(2,3,4,5)$ 的子序列中，有哪几种情况使得子序列第一个数为 $2$，最后一个为 $2$ 呢？很简单，就是子序列 $(2)$。所以最后一个数为 $2$ 的情况对答案的总贡献为 $2\times2$。

那最后一个是 $3$ 呢？第一个数有 $2,3$ 两种情况。那第一个数为 $2$，最后一个为 $3$ 呢？$(2,3)$。然后第一个为 $3$，最后为 $3$ 呢？$(3,3)$。所以最后一个数为 $3$ 的情况总贡献为 $3\times(2+3)$。

接着是最后一个为 $4$。第一个数可为 $2,3,4$。此时注意，第一个数为 $2$，最后一个为 $4$ 就有两（！！！）种情况了，分别为 $(2,4)$、$(2,3,4)$。第一个数为 $3$ 或 $4$ 的情况相信已经会了。这些情况的总贡献为 $4\times(2+2+3+4)$。

接着最后一种情况为 $5$。第一个数为 $2$，最后一个数为 $5$ 的情况有：$(2,5)$、$(2,3,5)$、$(2,4,5)$、$(2,3,4,5)$。第一个数为 $3$ 的情况为：$(3,5)$、$(3,4,5)$。第一个为 $4$ 的情况为：$(4,5)$。第一个为 $5$ 的情况为：$(5,5)$，总贡献为 $5\times(2+2+2+2+3+3+4+5)$。

现在将所有情况的总贡献值列出来，它们分别是！：

 $2\times(2)$ 

 $3\times(2+3)$ 

 $4\times(2+2+3+4)$ 

 $5\times(2+2+2+2+3+3+4+5)$  

现在着重于括号里的内容，你会（很难）发现：任意一个括号里的数，就是它前面所有括号里的数之和，再加上当前括号前那个乘数！！！

这个发现很惊人，因为当你看到“前面所有....之和”，就（应该）会想到：

**前缀和**

所以代码如下：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[200001],sum[200001],sum2[200001];
//sum[i]表示当前括号里的内容
//sum2[i]表示括号的前缀和
ll ans,mod=998244353;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	sum[1]=a[1];
	sum2[1]=a[1];
	ans+=a[1]*a[1]%mod;
	for(int i=2;i<=n;i++)
		sum[i]=((sum2[i-1])%mod+a[i])%mod,ans=(ans+(sum[i]*a[i])%mod)%mod,sum2[i]=sum2[i-1]+sum[i];
  		//每次运算都取下模
	cout<<ans;
	return 0;
}
```

---

## 作者：lilong (赞：0)

考虑计算每对 $(a_i,a_j)$ 的贡献，即计算当 $a_i$ 为最小值，$a_j$ 为最大值时的方案数。将 $a$ 排序后，显然 $(i,j)$ 中的元素可选可不选，$i,j$ 必选，$[1,i)$ 和 $(j,n]$ 必不选，共有 $2^{j-i-1}$ 种方案（$i=j$ 的情况另外计算）。不妨固定左端点 $i$，考察贡献：

- $a_1 \times( a_2 + 2a_3 + \cdots + 2^{n-2}a_n)$
- $a_2 \times( a_3 + 2a_4 + \cdots + 2^{n-3}a_n)$
- $a_3 \times( a_4 + 2a_5 + \cdots + 2^{n-4}a_n)$
- $\cdots$

从后往前看，发现括号内的数是在下面一行乘 $2$ 的基础上，再加上下面一行式子前面的数。于是就可以倒着扫一遍，求贡献即可。

时间复杂度 $O(n\log n)$，瓶颈在排序。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
#define N 1000001
#define MOD 998244353

using namespace std;

int n,a[N],sum,ans;

signed main()
{
    cin >> n;
    for( int i = 1 ; i <= n ; i ++ )
        cin >> a[i];
    sort( a + 1 , a + n + 1 );
    for( int i = n ; i >= 1 ; i -- )
    {
        ans = ( ans + a[i] * sum % MOD ) % MOD;
        ans = ( ans + a[i] * a[i] % MOD ) % MOD;//i=j 的情况
        sum = ( sum * 2 + a[i] ) % MOD;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

直接枚举肯定会超时，注意到子序列内部的东西并不重要，我们只需要知道最大值乘最小值，我们可以考虑枚举最大值和最小值。我们先把数列从小到大排序一下。

我们定义 $s_i$ 为“最小值不比 $a_i$ 小的子序列的最大值 $a_j$ 的和”。我们注意到有的时候很多 $a_j$ 会被同时计算，而计算的次数是 $2^{j-i}$ 次。所以有 $s_i=\sum_{j\leq i}a_j2^{j-i}$。使用一些数学可以轻松得出 $s_i=2s_{i+1}+a_i$，这样我们就能 $O(n)$ 地递推 $s_i$ 了。然而 $s_i$ 有什么用呢？

我们可以注意到一件事，设 $p_i$ 是“最小值等于 $a_i$ 的子序列的最大值 $a_j$ 的和”，就有答案是 $\sum a_ip_i$。而根据定义，$p_i=s_{i}-s_{i+1}$。所以答案就出来了。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 998244353
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll n, a[200000], sum[200005], ans;
//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a, a + n);
	for(int i = n - 1; i >= 0; i--){
		sum[i] = sum[i + 1] * 2 + a[i];
		sum[i] %= mod;
	}
	for(int i = 0; i < n; i++){
		ans += (sum[i] - sum[i + 1]) * a[i];
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}



```

---

## 作者：Dream_Stars (赞：0)

## 题目大意：
有一个长度为 $n$ 的序列，在它所有的 $2^n-1$ 的子序列中求出每个子序列最大的值和最小的值的乘积，最终求和，和就是最终的答案。题面已经说得很清楚了，这里就不多赘述了，但是，有一点要注意，就是最终的答案要对 $998244353$ **取模**。
## 算法分析：
这道题我们可以首先一个排序，接着再去进行贡献的计算，具体计算，我们可以想：对于**每一个**数都将其看成最大值，因为是所有的序列，所以每个数都会成为它搭配的最小值。将序列从小到大进行排序，依次考虑每个数作为最大值的贡献，即可正确，具体见代码，这里也不多赘述了。
## 代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 * 2 + 10 , mod = 998244353;
long long ans , cnt , n , a[N] , b[N];
int main(){
  scanf("%lld" , &n);
  for(int i=1;i<=n;i++) scanf("%lld" , &a[i]);
//读入数据。
  sort(a + 1 , a + n + 1);//进行排序。
  for(int i=1;i<=n;i++){//遍历数组，进行确定最大值贡献的计算。
    ans = (ans + a[i] * (cnt + a[i]) % mod ) % mod;
    cnt = ((cnt * 2) % mod + a[i] % mod) % mod;//总贡献值的计算。
//这里一定要注意取模，不然会WA。
  }
  cout<<ans;
  return 0;//return 养成好习惯。
}
```

---

## 作者：Swirl (赞：0)

**一道思维水题**。

# 思路简述

首先将其排序，讨论每个数作为 $\max$ 的情况，

然后将其归入答案中即可。

不过需要开一个变量 $num$，存储以前的数作为 $\min$ 的情况。

**思路部分完结**。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
ios::sync_with_stdio(0); \
cin.tie(0);              \
cout.tie(0)
// #pragma GCC Typetimize(2)
#define int long long
#define pll pair<ll, ll>
#define pii pair<ll, ll>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define r_g register
#define Mod 998244353
using namespace std;

namespace Nothing {
	il int read() {
		int f = 1, t = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if ( ch == '-' ) {
				f = -1;
			}
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			t = t * 10 + ch - '0';
			ch = getchar();
		}
		return t * f;
	}
	
	il void write(int x, bool s) {
		if (x < 0) {
			putchar('-');
			write(-x, false);
			return ;
		}
		if (!s && x == 0) 
			return ;
		if (s && x == 0) {
			putchar('0');
			return ;
		}
		write(x / 10, false);
		putchar(x % 10 + '0');
	}
}

int n;
int a[200005];

signed main() {
	n = Nothing::read();
	for (int i = 1; i <= n; i++) {
		a[i] = Nothing::read();
	}
	stable_sort(a + 1, a + n + 1);
	int ans = 0, num = 0;
	for (int i = 1; i <= n; i++) {
		ans = (ans + ((num + a[i]) * a[i]) % Mod) % Mod;
		num = (a[i] + (num * 2)) % Mod;
	}
	Nothing::write(ans, true);
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

不妨抓子序列中的最高的进行计算。则可以发现，若 $a_i$ 为最大的，则在 $1\dots i-1$ 中，有 $\sum_{j=1}^{i} a_i\times a_j \times 2^{i-j-1}$ 个，所以枚举讨论即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,a[maxn];
const int inf=998244353;
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	int sum=0,ans=0;
	for(int i=1;i<=n;++i){
		ans=(ans+a[i]*(sum+a[i])+inf)%inf;
		sum=(sum*2ll)%inf;
		sum=(sum+a[i])%inf;
	}
	cout << ans << endl;
	return 0;
}
```


---

