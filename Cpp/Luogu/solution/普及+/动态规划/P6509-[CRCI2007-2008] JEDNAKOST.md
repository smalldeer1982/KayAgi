# [CRCI2007-2008] JEDNAKOST

## 题目描述

给定一个形如 `A=B` 的字符串，其中 $A$ 和 $B$ 都是不含前导零的正整数。请给 $A$ 的一些相邻数位之间加上加号，要求添加的加号数量最少，使得等式成立。

在 $A$ 加上加号后，每个加数允许有多个前导 $0$。包括 $0$ 在内。也即允许形如 $000 \ldots$ 的数作为加数。

数据保证有解。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq A \lt 10^{1000}$，$1 \leq B \leq 5 \times 10^3$，$A \neq B$。

#### 说明

**题目译自 [COCI2007-2008](https://hsin.hr/coci/archive/2007_2008/) [Regional Competition](https://hsin.hr/coci/archive/2007_2008/regional_tasks.pdf) *T4 JEDNAKOST***。

## 样例 #1

### 输入

```
143175=120
```

### 输出

```
14+31+75=120```

## 样例 #2

### 输入

```
5025=30
```

### 输出

```
5+025=30```

## 样例 #3

### 输入

```
999899=125
```

### 输出

```
9+9+9+89+9=125```

# 题解

## 作者：青鸟_Blue_Bird (赞：5)

[博客园广告](https://www.cnblogs.com/wondering-world/p/12824895.html)

这道题感觉是一个很另类的DP      ~~至少我的做法是这样的~~。

### 重要前置思想：把A存成字符串！！！~~（应该也没人会想着存成int或者long long 吧）~~
首先，我们定义状态f[i][j]: 当我们处理A字符串到第i个位置时，我们还差j就能使式子的和等于B。

于是，开始想 ~~手摸~~ 状态方程。 

#### 嗯？怎么感觉有点难搞。  没事，慢慢来。


#### 定义n = strlen(A), 即A字符串的长度, sum为剩下仍需要的数
首先看特殊情况：

如果i == n, 那么：

case1: sum < 0 ，很明显不符合要求，令f[n][sum] = INF;

case2: sum > 0, 同上，并不能满足等式成立，f[n][sum] = INF；

case3:sum = 0,符合我们的要求，令 f[n][sum] = 0;

那么，对于其余的情况，我们很容易有：

f[i][sum] = min{f[i + 1][num - A[position] | i <= position < n};

可是。这里要用到 i + 1啊，怎么实现？

## 递归呗！！

设计一个函数change，在递归过程中返回下一层（i + 1）层的值，同时修改f数组即可。

### 还没完！！ 注意到题目中的前置0了吗？ 如何处理这种情况呢？？

如此考虑：如果我们出现 " xx + 0 + xx"，这种情况肯定不是最优的，因为我们完全可以写成 " xx + 0xx" ,两边的式子大小一样，可是加号却被浪费了。于是，我们设定一个pre数组，作为循环时的起始点，作为对‘0’位置的特判。如果位置是0，我们则从其上一位（i + 1）开始循环，否则从他自己。

##### 友情Tips：INF千万不要设成 ~0u >> 1、 2147483647等int上限，因为函数中有个地方要 + 1， 会超过上限。~~（我为此WA + RE了两遍）~~

#### 细节标记在代码中了，没讲清楚的地方可以尝试着看看代码QAQ

上一波代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9; /*千万不能写成int的极大值！！！下面会 + 1，造成错误*/
#define N 1010

char A[N]; 
int B; /*同题目*/
int pre[N], f[N][N * 5]; /*f是动规数组，pre为起始点（给 ‘0’用的）*/
int n; /*字符串的长度*/

int change(int now, int sum){
	if(now == n)return sum == 0 ? 0 : INF;
	int &cur = f[now][sum]; /*建个指针，懒得打那么长的 f数组*/
	if(cur != -1){
		return cur;
	}
	cur = INF;
	int temp = 0;
	for(int j = pre[now]; j < n; j++){
		temp = temp * 10 + A[j] - '0'; /*往上累加*/
		if(temp > sum) break;
		int hehe = change(j + 1, sum - temp);
		cur = cur < hehe + 1 ? cur : hehe + 1; 
	}
	return cur;
}

int solve(int now, int sum){ /*输出思路：一边输出A字符串，一边穿插 +号*/
	if(now == n){
		printf("=%d\n", B);
		return 1;
	}
	if(now > 0)printf("+");
	int num = 0;
	for(int j = now;j < n; j++){
		printf("%c", A[j]);
		num = num * 10 + A[j] - '0';/*有点快读那味儿了*/
		if(change(now, sum) == 1 + change( j + 1, sum - num)){
			return solve(j + 1, sum - num);
		}
	}
	return 0;
}

int main(){
	char c = getchar();
	while(isdigit(c)){
		A[n++] = c;
		c = getchar();
	}
	scanf("%d", &B);
	n = strlen(A);
	pre[n-1] = n - 1;
	for(int i = n - 2; i >= 0; i--){
		pre[i] = (A[i] == '0') ? pre[i + 1] : i;
	}
	memset(f, -1, sizeof(f)); /*初始化不要忘*/
	solve(0, B);
	return 0;
}
```


---

## 作者：一扶苏一 (赞：3)

## 【DP】【P6509】 [CRCI2007-2008] JEDNAKOST

### Analysis

比较套路的 dp，设 $f_{i, j}$ 是考虑 $A$ 的前 $i$ 位，其和为 $j$ 时，最少用了多少个加号，转移显然：

$$f_{i, j} = \min\limits_{k = 0}^{i - 1}\{f_{k, j - \operatorname{sum}_{k + 1, i}}\} + 1$$

其中 $\operatorname{sum}_{l, r}$ 指的是 $A$ 中第 $l$ 位到第 $r$ 位构成的数字，要求 $j - \operatorname{sum}_{k + 1, i} \geq 0$。

这样的复杂度看起来是 $O(n^3)$ 的（这里认为 $s$ 的大小与 $A$ 的长度同阶，均为 $n$）。但是注意到一个性质，在 $\operatorname{sum}$ 没有前导 $0$ 的情况下，$k$ 每次减小 $1$，$\operatorname{sum}$ 至少增大十倍。因此 $k$ 的枚举量不会超过 $4$。而对于 $k \leq i - 4$ 且 $\operatorname{sum}$ 存在前导 $0$ 的情况，我们注意到只有 $A$ 连续为 $0$ 的一段可以用来转移，一旦前面多了一个非零数，$\operatorname{sum}$ 会瞬间大的无法接受。因此我们只需要多维护一个 $g_{i, j}$，表示 $\min\limits_{k = x}^{i} f_{k,j}$，其中 $x$ 表示最小的 $x$ 到 $i$ 全部是 $0$ 的位置。这样即可做到 $O(1)$ 转移这段连续 $0$ 的最小值。

而输出方案只需要再维护每个状态从哪个状态转移而来，递归输出即可。

总时间复杂度 $O(B\log A)$。

### Code

```cpp
namespace Fusu {

const int maxn = 1003;
const int maxm = 5003;

void Init();
void Solve();
void Print();

void Main() {
  freopen("1.out", "w", stdout);
  Init();
  Solve();
  Print();
}

int n, s, dn;
char eq[maxn + 5];
int a[maxn], ten[5];
void Init() {
  scanf("%s", eq + 1);
  int m = strlen(eq + 1);
  int i = 0;
  while (eq[++i] != '=') {
    a[++n] = eq[i] - '0';
  }
  dn = n + 1;
  while (++i <= m) {
    s = s * 10 + eq[i] - '0';
  }
  ten[i = 0] = 1;
  while (++i < 4) ten[i] = ten[i - 1] * 10;
}

int f[maxn][maxm], py[maxn][maxm], px[maxn][maxm], mn[maxn][maxm];

void Solve() {
  memset(f, 0x3f, sizeof f);
  f[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] == 0) {
      for (int j = 1; j <= s; ++j) {
        mn[i][j] = mn[i - 1][j];
      }
    }
    for (int j = 1; j <= s; ++j) {
      int sum = 0;
      for (int k = 0, p = i + 1; k < 4; ++k) if ((--p > 0) && ((sum += a[p] * ten[k]) <= j)) {
        int d = j - sum;
        if ((p != 1) && (d == 0)) continue;
        if (a[p] == 0) {
          int x = mn[p - 1][d];
          if (f[x][d] < f[i][j]) {
            f[i][j] = f[x][d] + 1;
            px[i][j] = x;
            py[i][j] = d;
          } 
        } else if (f[p - 1][d] < f[i][j]) {
          f[i][j] = f[p - 1][d] + 1;
          px[i][j] = p - 1;
          py[i][j] = d;
        }
      } else {
        break;
      }
      if (f[mn[i][j]][j] >= f[i][j]) {
        mn[i][j] = i;
      }
    }
  }
}

void dfs(const int i, const int j) {
  if (px[i][j]) {
    dfs(px[i][j], py[i][j]);
    putchar('+');
  }
  for (int p = px[i][j] + 1; p <= i; ++p) {
    qw(a[p], 0);
  }
}

void Print() {
  dfs(n, s);
  printf("=%d\n", s);
}
```



---

## 作者：wbh20090611 (赞：1)

这道题是一道思维好题。

## 基本思路

首先用 DP 求出加号最少需要多少个，再记录每一个 DP 值的来源（或者说前驱）再通过在数字中间插入加号。

## 主题部分

### DP 部分

#### 表示

$dp_{i,j}$ 表示到了第 $i$ 个数字，加和是 $j$, 储存最少需要的加号个数。

#### DP 递推式

$dp_{i,j} = \min(dp_{i,j}, dp_{z,j-x})$。

其中循环遍历前驱 $z$ 计算加和 $j - x$。

不难看出：因为 $B \leq 5 \times 10^3$，所以只需要向前遍历 $5$ 个即可。

#### 时间复杂度

$O(5 \times \lg n \times m)$，是可以通过的。

### 前驱记录

这个地方很简单，详情见代码。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
long long dp[1010][5010], n, m, x, y, pre[1010][5010][2];
char s[1010], c;
int main()
{
	c = getchar();
	while(isdigit(c))
		s[++n] = c, c = getchar();
	scanf("%lld", &m);
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = -1; 
	for (int i = 0; i <= n; i++)
	{
		for (int z = 0; z <= m; z++)
		{
			x = 0, y = 1;
			for (int j = i - 1; j >= max(i - 5, 0); j--)
			{
				x += y * max(s[j + 1] - 48, 0);
				y *= 10;
				if (x > z)
					break;
				if (dp[i][z] > dp[j][z - x] + 1) //计算并记录前驱
				{
					pre[i][z][0] = j;
					pre[i][z][1] = z - x;
					dp[i][z] = dp[j][z - x] + 1;
				}
			}
		}
	}
	stack <long long> f;
	long long xx = n, yy = m, xx1, yy1;
	while(xx > 0) //利用前驱求加号位置
	{
		xx1 = pre[xx][yy][0];
		yy1 = pre[xx][yy][1];
		xx = xx1;
		yy = yy1;
		if (xx > 0)
			f.push(xx);
	}
	for(long long i = 1; i <= n; i++) //输出
	{
		printf("%c", s[i]);
		if (f.size() && i == f.top())
			printf("+"), f.pop();
	}
	cout << "=" << m;
}
```

不会有人真的把这个代码提交了吧。

喜提 $80pts$。

为什么错了呢？

### 缺陷

当遇到这个样例的时候，我们将会出错。

```
120000000012=24
```

Your answer:

```
12+00000+00012=24
```

Right answer:

```
12+0000000012=24
```

### 考虑优化：

对于这一段书数字加和为零的情况，累计 DP 值的时候不加一，在返回查找的时候如果 DP 值没有累加就不记录这个加号。

### 代码实现

```c++
#include <bits/stdc++.h>
using namespace std;
long long dp[1010][5010], n, m, x, y, pre[1010][5010][2];
char s[1010], c;
int main()
{
	c = getchar();
	while(isdigit(c))
		s[++n] = c, c = getchar();
	scanf("%lld", &m);
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = -1; 
	for (int i = 0; i <= n; i++)
	{
		for (int z = 0; z <= m; z++)
		{
			x = 0, y = 1;
			for (int j = i - 1; j >= max(i - 4, 0); j--)
			{
				x += y * max(s[j + 1] - 48, 0);
				y *= 10;
				if (x > z)
					break;
				if (dp[i][z] > dp[j][z - x] + (x != 0))
				{
					pre[i][z][0] = j;
					pre[i][z][1] = z - x;
					dp[i][z] = dp[j][z - x] + (x != 0);
				}
			}
		}
	}
	stack <long long> f;
	long long xx = n, yy = m, xx1, yy1;
	while(xx > 0)
	{
		xx1 = pre[xx][yy][0];
		yy1 = pre[xx][yy][1];
		xx = xx1;
		yy = yy1;
		if (xx > 0 && dp[pre[xx][yy][0]][pre[xx][yy][1]] != dp[xx][yy])
			f.push(xx);
	}
	for(long long i = 1; i <= n; i++)
	{
		printf("%c", s[i]);
		if (f.size() && i == f.top())
			printf("+"), f.pop();
	}
	cout << "=" << m;
}
```

---

## 作者：abcxyz123 (赞：1)

> 8天的血与泪。。。
>
> 从开始的TLE dp想到区间dp，建树，图论，数论，二进制。。。
>
> 最后才发现，在原来的dp基础上加个小小的优化就行了。。。
>
> ~~第一篇题解纪念一下qwq~~
# solution
$$80pts$$

首先，**把 $a$ 存成字符串！！！！**

先预处理出 $num_{i, j}$，第 $i$ 位到第 $j$ 位的数，如果这个数大于 $10000$，则把它设成 $10000$（因为这个数肯定大于 $b$）。

设 $add_{i, j}$ 是前 $i$ 位和为 $j$ 时的最少加数数量，则

$$
add_{i, j} = \max_{k = 1}^{k \le i, num_{k, i} \le j}(add_{k - 1, j - num_{k, i}} + 1)
$$

因为最后要求输出整个式子，则再用 $dp_{i, j}$ 表示前 $i$ 位和为 $j$ 时最后一个加数开始的位置，递归输出即可。

$$O(n^3)$$

[于是T了](https://www.luogu.com.cn/record/149641725)  

所以说我们需要亿点点小小的优化~~真的是一点点~~

$$100pts$$

我们发现，当我们枚举 $k$ 的时候，如果都是非零数，则最后一个加数的位数不超过 $4$，（因为 $b \le 5000$）。

而当 $a$ 中有很长的一段 $0$，（极限数据），则最后一个加数的位数甚至会接近 $a$ 的长度。

比如说 $100\ldots01=2$。

而我们发现，如果超过 $4$ 个 $0$ 左边加上一个非零数，那么这个数总会大于 $b$。

所以，对于一长串 $0$，我们只需要枚举第 $1$ 个 $0$ 往后 $4$ 位即可。

用 $last_{i}$ 表示第 $i$ 位前面最小的位置，使得

$$
a_{last_{i} + 1} = a_{last_{i} + 2}  = \ldots = a_{i} = 0
$$

也就是说，$last_{i}$ 是第 $i$ 位前面一串 $0$ 的第一个 $0$ 的位置的前一个位置。

如果第 $i$ 位不是 $0$，则 $last_{i} = i$。

所以对于一长串 $0$，我们只需要枚举 $last_{i} + 1$ 到 $last_{i} + 4$ 的位置（当然要不超过 $i$）。

$$O(n^3) \to O(n^2)$$

完成优化！！！

主要代码

```cpp
memset(dp, 0, sizeof(dp));
memset(add, 0x3f, sizeof(add));//初始化为INF
add[0][0] = 0;//前 0 位, 和为 0 时, 加数数量显然为 0
for (int i = 1; i <= n; i++) {
	for (int j = 0; j <= b; j++) {
		int k1;//加数数量最小时, 最后一个加数从第 k1 位开始
		for (int k = i; k >= 1; k--) {

			k = min(k, last_[k] + 4);

			int x = num[k][i];
			if (x > j) {
					//如果这时 x > j , 那么 k 更小时 x 也 > j
				break;
			}
			if (add[i][j] > add[k - 1][j - x] + 1) {
				add[i][j] = add[k - 1][j - x] + 1;
				//取加数数量最小的
				k1 = k;
			}
		}
		dp[i][j] = k1;
	}
}
```

完整代码

[云剪贴板 (猛戳](https://www.luogu.com.cn/paste/yiuf2ips)

### 备注
1. 对于 `string_to_int` 函数，不能写成

```cpp
int string_to_int(string s) {
    int sum = 0, cnt = 1;
    for (int i = s.length() - 1; i >= 0; i--) {
        int x = s[i] - '0';
        sum += x * cnt;
        cnt *= 10;
        if (sum >= 10000) {
            return 10000;
        }
    }
    return sum;
}
```

因为当这个数是 $000000000025$ 时，$cnt$ 会爆 int 范围。

2. 贡献几个样例~~希望有用~~

```cpp
1826553186455=572
18+265+53+186+45+5=572

1345276417972564571153=473
13+45+27+64+17+97+25+64+57+11+53=473

13452547535435745675341135745=3300
134+525+475+35+43+574+567+534+11+357+45=3300

135157452641045281425364472536212313012003=2050
135+157+45+264+104+528+142+53+64+47+253+62+12+31+30+120+03=2050

```

3. 如有问题，评论区多多指教！

---

## THE END

---

## 作者：unsigned_short_int (赞：1)

## P6509 题解

update: 被 @[xztl](www.luogu.com.cn/user/318025) hack 了，改了代码。

------------


本题解的做法是DP，但是细节较多。

先考虑不含 $0$ 的情况，定义 $f_{i,v}$ 为在第 $i$ 位之前添加加号，且 $1\sim i-1$ 位用加号分隔完后得到的数列加起来为 $v$ 时，最少需要用的加号数量。则显然有：
$$
f(i,v)=\min_{1 \leq j \lt i} \{ f(j,v-num(j,i-1)) \} +1
$$
其中 $num(j,i-1)$ 表示将 $[j,i-1]$ 的数字拼接起来的结果。因为本题 $B$ 很小，所以实际上 $j$ 只用枚举 $[i-4,i-1]$  。  

然而，本题最麻烦的地方就在于前导 $0$ 。我的做法是定义一个数组 $c$ 表示去除 $a$ 中连续超过 $3$ 个的 $0$ 后得到的数（连续超过 $3$ 个的 $0$ 只可能作为前导 $0$），再在 $c$ 的每一个位置上记录一个 $siz$ 表示这个位置之前删掉了几个 $0$。这样就可以直接在 $c$ 上 DP ，不过 $j$ 改为枚举 $[i-7,i-1]$，这是因为这种数据：

```
80001000=1008
```

此时由于不知道 $1000$ 前面的 $0$ 是前导 $0$ 还是正常的，必须枚举 $3+3+1$ 位。

由于状态设计得较为特殊，各种处理时都要循环到 $|c|+1$。

其他细节放在注释里。

```cpp
#include<string>
#include<iostream>
#include<vector>
using namespace std;

const int L=1005,Inf=10000000,V=5005;

int a[L],n,b;

void input()
{
	string tmp;
	cin>>tmp;
	
	bool flag=false;
	for(int i=0;i<tmp.size();i++)
	{
		if(tmp[i]=='=')
		{
			flag=true;
			continue;
		}
		if(!flag)
			a[++n]=tmp[i]-'0';
		else
			b=b*10+tmp[i]-'0';
	}
}

int c[L],cnt,f[L][V],siz[L];
pair<int,int> path[L][V]; //路径 

bool toPlus[L]; //这个位置前是否需要打加号 

void dfs(int p,int val)
{
	toPlus[p]=true;
	if(path[p][val].first<=1)
		return;
	dfs(path[p][val].first,path[p][val].second);
}

int main()
{
	input();
	
	int c0=0;
	for(int i=1;i<=n;i++) //c0 表示连续 0 的个数 
		if(!a[i])
		{
			c0++;
			if(c0>=4)
				continue;
			c[++cnt]=a[i];
		}
		else
		{
			c[++cnt]=a[i];
			siz[cnt]=max(0,c0-3);
			c0=0;
		}
	siz[cnt+1]=max(0,c0-3); //将末尾的 0 压在 cnt+1 上便于处理 
	
	for(int i=1;i<=cnt+1;i++)
		for(int j=0;j<=b;j++)
			f[i][j]=Inf; //手动初始化为极大值 
	f[1][0]=0;
	
	// DP
	for(int i=2;i<=cnt+1;i++)
	{
		int add=0;
		for(int j=i-1,pow=1;j>=max(i-7,1);j--,pow*=10)
		{
			add=add+c[j]*pow;
			if(add>b)
				break; 
			for(int k=0;k+add<=b;k++)
				if(f[j][k]+1<f[i][k+add])
				{
					f[i][k+add]=f[j][k]+1;
					path[i][k+add]=make_pair(j,k);
				}
		}
	}
	
	dfs(cnt+1,b);
	
	//此处特判经 @xztl hack 后加入 
	bool flag=false;
	int pos=cnt+1;
	do //判断最后一个加号到末尾是否有非零数位
	{
		pos--;
		if(c[pos])
		{
			flag=true;
			break;
		}
	} while(pos>=1 && !toPlus[pos]);
	toPlus[cnt+1]=siz[cnt+1] && flag;
	
	for(int i=1;i<=cnt+1;i++)
	{
		if(toPlus[i])
			cout<<'+';
		if(siz[i]) //展开压缩的 0 
			for(int j=1;j<=siz[i];j++)
				cout<<'0';
		if(i!=cnt+1)
			cout<<c[i];
	}
	cout<<"="<<b;
}
```



---

