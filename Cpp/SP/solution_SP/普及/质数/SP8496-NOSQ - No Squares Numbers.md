# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7```

### 输出

```
10
9
26318```

# 题解

## 作者：Galex (赞：4)

它是绿的？！（不敢相信


### 想法1：暴力

直接枚举 $a$ 到 $b$，判断它是否符合条件，复杂度 $O(Tb(\sqrt b + \lg b)$，明显会炸。

### 想法2：预处理出所有的答案。

我们看到 $a$ 和 $b$ 都 $\le 100000$，想到预处理出所有包含 $1$ 到 $9$ 的“无平方数” 的个数。我们用 $s[i][j]$ 表示前 $i$ 个数包含数字 $j$ 的“无平方数”的个数。很明显，

 `s[i][j] = s[i - 1][j] + (hav(i, j) && chk(i));`
 
 其中，$hav(i,j)$ 表示 $i$ 是否包含 $j$，$chk(i)$ 表示 $i$ 是否为 “无平方数”。
 
 然后对于每次询问，输出 $s[b][d] - s[a - 1][d]$ 即可。
 
 复杂度为 $O(10^6 \times (\sqrt{10^5} + \lg(10^5)) + T)$，勉强能过。
 
 ## Code
 
 ```cpp
#include <iostream>
using namespace std;

int s[100005][10];

bool hav(int a, int b){//判断a是否包含b 
	while (a > 0){
		if (a % 10 == b)//包含 
			return true;
		a /= 10;
	}
	return false; //找遍了，不包含
}

bool chk(int x){//判断a是否是"无平方数"
	for (int i = 2; i * i <= x; i++)//注意从2开始！！！我这个傻子半天才发现。。。 
		if (x % (i * i) == 0)//有因子是平方数 
			return false;
	return true;//找遍了，没有因子是平方数，故x是无平方数 
}

int main(){
	for (int i = 1; i <= 100000; i++)
		for (int j = 0; j <= 9; j++)
			s[i][j] = s[i - 1][j] + (hav(i, j) && chk(i));//类似前缀和 
	int t;
	cin >> t;
	while (t--){
		int a, b, d;
		scanf("%d %d %d", &a, &b, &d);
		printf("%d\n", s[b][d] - s[a - 1][d]);//注意是a - 1！！！ 
	}
	return 0;
} 
```



---

## 作者：wwwidk1234 (赞：3)

[洛谷题目传送门！](https://www.luogu.com.cn/problem/SP8496)

[SPOJ 传送门！](https://www.spoj.com/problems/NOSQ/)

[查看我的其他题解？](https://wwwidk1234.github.io/)

前置知识：[质数筛法](https://oi-wiki.org/math/number-theory/sieve/)

## 题目大意

求出 $a$ 到 $b$ 之间所有包含数字 $d$ 的无平方数因数的数个数。

无平方数因数的数是什么？不能被任何非 $1$ 的完全平方数整除的数即为无平方数因数的数。

## 题目思路

### 直接暴力

直接暴力枚举算出 $a$ 到 $b$ 之间的无平方数因数的数，数据范围 $1 \leq a,b \leq 10^5$，再加上 $T$ 次询问，明显会超时，因此考虑把所有答案算出来，然后每次询问 $O(1)$ 回答。

### 正解

```cpp
bool include(int src,int inc)  //判断在src中是否包含inc
{
	while(src>0)
	{
		int tmp=src%10; src/=10;
		if(tmp==inc) return true;
	}
	return false;
}
```

这是一个简单的判断在 $src$ 中是否包含 $inc$ 的函数，每次循环用 `src%10` 取出个位数字，然后使用 `src/=10` 去除个位数字，最后判断是否包含。

```cpp
const int MAXN=100000+10;
const int MAXD=9+10;
bool vis[MAXN];
vector<int> primes;
void primeinit()
{
	int cnt=1;
	vis[1]=1;
	for(int i=2;i<=MAXN;i++)
	{
		if(!vis[i])
		{
			++cnt;
			primes.push_back(i);
		}
		for(int j=0;j<cnt;j++)
		{
			if(1ll*i*primes[j]>MAXN) break;
			vis[i*primes[j]]=1;
			if(i%primes[j]==0) break;
		}
	}
}
```

欧拉筛法模板，可以在 $O(N)$ 的时间复杂度内找出 $1 \sim N$ 之间的所有质数。

```cpp
bool isnosq(int src)  //判断src是否为无平方数因数的数
{
	if(src==1) return true;
	for(auto prime:primes)
	{
		if(prime*prime>src) return true;
		if(src%(prime*prime)==0) return false;
	}
	return true;
}
```

这是一个判断一个数是否为无平方数因数的数，枚举每一个质数并检查是否满足条件。

```cpp
int sum[MAXN][MAXD];
for(int i=1;i<=100000;i++)
	{
		for(int digit=0;digit<=9;digit++)
		{
			if(include(i,digit)&&isnosq(i))
				sum[i][digit]=sum[i-1][digit]+1;
			else
				sum[i][digit]=sum[i-1][digit];
		}
	}
```

$sum_{i,j}$ 表示 $1 \sim n$ 之间包含 $j$ 的无平方数因数的数的个数，$sum_{b,d}-sum_{a-1,d}$ 就是 $a \sim b$ 之间所有包含数字 $d$ 的无平方数因数的数的个数了。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug(x) cout<<#x<<"="<<x<<endl;
using namespace std;

const int MAXN=100000+10;
const int MAXD=9+10;
bool vis[MAXN];
vector<int> primes;
void primeinit()
{
	int cnt=1;
	vis[1]=1;
	for(int i=2;i<=MAXN;i++)
	{
		if(!vis[i])
		{
			++cnt;
			primes.push_back(i);
		}
		for(int j=0;j<cnt;j++)
		{
			if(1ll*i*primes[j]>MAXN) break;
			vis[i*primes[j]]=1;
			if(i%primes[j]==0) break;
		}
	}
}
bool include(int src,int inc)  //判断在src中是否包含inc
{
	while(src>0)
	{
		int tmp=src%10; src/=10;
		if(tmp==inc) return true;
	}
	return false;
}
bool isnosq(int src)  //判断src是否为无平方数因数的数
{
	if(src==1) return true;
	for(auto prime:primes)
	{
		if(prime*prime>src) return true;
		if(src%(prime*prime)==0) return false;
	}
	return true;
}
int sum[MAXN][MAXD];
signed main()
{
	primeinit();
	for(int i=1;i<=100000;i++)
	{
		for(int digit=0;digit<=9;digit++)
		{
			if(include(i,digit)&&isnosq(i))
				sum[i][digit]=sum[i-1][digit]+1;
			else
				sum[i][digit]=sum[i-1][digit];
		}
	}
	int T;
	cin>>T;
	while(T--)
	{
		int a,b,d;
		cin>>a>>b>>d;
		cout<<sum[b][d]-sum[a-1][d]<<endl;
	}
	return 0;
}
```



---

## 作者：Luo_gu_ykc (赞：2)

## 题目大意

$T$ 次询问，每次询问给出 $a$，$b$，$d$ 三个整数，请输出 $a$ 到 $b$ 这些数之间包含数字 $d$ 且为“无平方数”的所有数的个数。

- 注：“无平方数”定义为：不为任意完全平方数的倍数，但 $1$ 也为“无平方数”。

## 思路

我们看到 $1 \le a \le b \le 10 ^ 5$ 的数据范围，我们其实想到可以预处理。

但是怎么解决包含数字 $d$ 的情况，我们其实仔细想想，一个数最多也就只有 $5$ 位，我们即使将所有数都提取每个位的数，也只有 $5 \times 10 ^ 5$。

所以我们可以开 10 个动态数组，第 $d$ 个数组存储包含 $d - 1$ 的“无平方数”。

然后我们就可以使用质数筛的思想，每次把所有平方数的倍数都筛掉，最后没被标记的就是“无平方数”。

同时，我们再询问时使用二分即可，因为这些数组明显满足单调性。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5;

int t;
vector <int> q[N + 15];
bool v[N + 15];

void solve(){
	int l, r, d;
	cin >> l >> r >> d;
	int x = lower_bound(q[d].begin(), q[d].end(), l) - q[d].begin();
	int y = upper_bound(q[d].begin(), q[d].end(), r) - q[d].begin();
	cout << y - x << "\n"; // 利用前缀和求区间和的思想，得出答案
}

signed main(){
	for(int i = 2; i * i <= N; i++){
		int s = i * i, cnt = 1; // 暴力筛完全平方数的倍数
		while(s * cnt < N){
			v[s * cnt] = 1;
			cnt++;
		}
	}
	for(int i = 1; i <= N; i++){
		if(!v[i]){ // 没有被筛过
			int tme = i;
			while(tme){
				int g = tme % 10; // 算出数的每一位
				int x = q[g].size() - 1;
				if(x == -1 || q[g][x] != i){ // 可能算重，标记一下
					q[g].push_back(i);
				}
				tme /= 10;
			}
		}
	}
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：LB_tq (赞：2)

```
//由于数据范围较小，没有优化，采用前缀和做法；
#include<iostream>
#include<cstdio>
using namespace std;
int t,a,b,d;//依题意
int s[100010][10];//s[i][j]表示1~i中含有数字j的无平方数的个数
bool tai(int x){
	for(int i=2;i*i<=x;i++)
		if(x%(i*i)==0)//一旦被整除返回false
			return false;
	return true;
}
int main(){
	int x,y;
	for(int i=2;i<=100000;i++)
		if(tai(i)){//如果是无平方数
			x=i;
			while(x>0){
				y=x%10;
				s[i][y]=1;
				x/=10;
			}//赋一,枚举每一位
		}
	for(int i=0;i<10;i++)
		for(int j=2;j<=100000;j++)
			s[j][i]+=s[j-1][i];//求出前缀和
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a>>b>>d;
		cout<<s[b][d]-s[a-1][d]<<endl;//O（1）查询
	}
	return 0;
}
我们可以在b中取一个最大值，只预处理1~b（max）
。。。
```


---

## 作者：feecle6418 (赞：1)

让我发一篇题解，来纪念一下包掉这一道题qwq（~~题解~~+翻译+第一个AC）

## 算法一

对于每个询问分别枚举。时间复杂度$O(T\times (b-a)^{1.5}\times log_{10}b)$。明显超时。

## 算法二

如果这道题没有“包含特定的数字”这个限制的话，那么它就是刘汝佳的紫书上的例题qwq。明显的看出可以用筛法先预处理出所有的“无平方数”。代码：

```
    memset(no_square,1,sizeof(no_square));
    for(int i=2; i*i<100000; i++) {
        for(int j=i*i; j<=100000; j+=i*i) {
            no_square[j]=0;
        }
    }
    no_square[1]=1;
    for(int i=1;i<=100000;i++) {
    	if(no_square[i])ans[++cnt]=i;
    }
```

这样每次枚举时只需枚举存在于ans数组里面的数了。时间复杂度$O(\text{筛法复杂度}+T\times cnt \times log_{10}b)$。可是通过输出cnt的值，我们发现cnt大于60000，并无明显优化。依然超时。

## 算法三

分别存表。

对于每一个d，我们用ans[i][d]表示第i个包含d的无平方数，cnt[d]表示包含d的无平方数的个数，last[i][d]表示小于等于i的第一个包含d的无平方数，next[i][d]大于等于i的的第一个包含d的无平方数。在预处理时，先分别算出这些数组里面应有的值，最后$O(1)$查询。时间复杂度$O(\text{能过})$。

有如下要注意的细节：
1. 当i小于第一个包含d的无平方数时，last[i][d]=next[i][d]=1。大于最后一个时同理。
2. Next要大写，小写是一个函数。
3. 同一个数在同一个表里面只存一次。

下面是AC代码：

```
#include<bits/stdc++.h>
using namespace std;
bool no_square[100005];
int ans[100005][12],cnt[12],last[100005][12],Next[100005][12];
int main() {
    memset(no_square,1,sizeof(no_square));
    for(int i=2; i*i<100000; i++) {
        for(int j=i*i; j<=100000; j+=i*i) {
            no_square[j]=0;
        }
    }
    no_square[1]=1;
    for(int i=1; i<=100000; i++) {
        if(no_square[i]) {
            int k=i;
            while(k) {
                if(ans[cnt[k%10]][k%10]!=i)ans[++cnt[k%10]][k%10]=i;
                k/=10;
            }
        }
    }
    for(int k=0; k<=9; k++) {
        for(int i=1; i<cnt[k]; i++) {
            for(int j=ans[i][k]; j<ans[i+1][k]; j++)last[j][k]=i;
            for(int j=ans[i][k]+1; j<=ans[i+1][k]; j++)Next[j][k]=i+1;
            last[ans[i][k]][k]=Next[ans[i][k]][k]=i;
        }
        for(int i=1;i<ans[1][k];i++)last[i][k]=Next[i][k]=1;
        for(int i=ans[cnt[k]][k]; i<=100000; i++)Next[i][k]=cnt[k],last[i][k]=cnt[k];
    }
    int T;
    scanf("%d",&T);
    while(T--) {
        int a,b,s;
        scanf("%d%d%d",&a,&b,&s);
        printf("%d\n",(last[b][s]-Next[a][s])+1);
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

暴力虽然能通过本题，但我们可以考虑一些优化手段。

首先观察无平方数的条件，不难发现一个数是无平方数等价于其质因数分解后没有质因子的出现次数超过 $ 2 $。用反证法可以证明这个结论的正确性。

于是直接上 Pollard-rho 分解质因子之后判一下质因子出现次数即可。

注意到做前缀和的时候我们没必要对每个位置都重新跑一遍分解质因子，这样分解的次数可以从 $ n\log{n} $ 降低到 $ n $ 次。

然后就用一样的思路，做一遍前缀和即可回答所有的询问。

总时间复杂度 $ \mathcal{O}(n^\frac{5}{4}) $，可以通过。

[代码](https://www.luogu.com.cn/paste/2veft3wq)

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP8496)    
现在绿题都这么水了吗？       
首先考虑暴力。   
我们把 $a$ 到 $b$ 里所有的数字都跑一遍就可以。但是时间复杂度是 $O(T n \log n)$，这里的 $n$ 指区间大小。   
我们读一下题，就可以想到正解：筛法+前缀和。      
我们先筛出 $1$ 到 $10^5$ 的所有“无平方数”，再做前缀和。$q_{i,j}$ 表示第 $j$ 个数包含数字 $i$ 的“无平方数”的前缀和。   
这样，对于每一次询问，就是 $O(1)$ 的了。   
初始化也是常数级别。    
CODE：    
```
#include <iostream>
using namespace std;
int t,l,r,d;
bool b[100001];
int q[10][100001];
bool check(int x,int n){//判断数字x是否含有n
	while(x!=0){
		if(x%10==n){
			return true;
		}
		x/=10;
	}
	return false;
}
void init(){
	b[1]=false;//特判1
	for(int i=2;i<=100000/i;i++){//先筛一遍
		for(int j=1;j*i*i<=100000;j++){
			b[j*i*i]=true;
		} 
	}
	for(int i=1;i<=100000;i++){//做前缀和数组
		for(int j=0;j<10;j++){
			q[j][i]=q[j][i-1]+(!b[i])*(int)check(i,j);
		}
	}
}
int main(void){
	init();
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&l,&r,&d);
		printf("%d\n",q[d][r]-q[d][l-1]);//回答
	}
}
```


---

## 作者：RAVE_LOVEo_O (赞：0)

对于这题：

- 模拟会炸掉。
- 此题正解应该是一个类似于前缀和的东西。


可以用一个函数来判断是否为无平方数，另一个判断在某个数中是否含有另一个数。

处理好之后，对于每组数据输出类似于前缀和的东西。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,t,a,b,d,f[100005][15];
bool pd(int x)//是不是“无平方数”
{
   for(int i=2;i*i<=x;i++)//注意!从2开始
      if(x%(i*i)==0)return 0;
   return 1;
}
bool h(int a,int b)//判断a是否包含b
{
   int x=a;
   while(x)
   {
      if(x%10==b)return 1;
      x/=10;//一位一位取
   }
   return 0;
}
int main()
{
   cin>>t;
   for(i=1;i<=100000;i++)//预处理
      for(j=0;j<10;j++)
      	f[i][j]=f[i-1][j]+(pd(i)&&h(i,j));//如果i含有j，并且i是无平方数，累计
   while(t--){
      cin>>a>>b>>d;
      cout<<f[b][d]-f[a-1][d];//直接输出
      puts("");
   }
	return 0;//完结撒花！
}
```


---

## 作者：COsm0s (赞：0)

## 1、枚举
枚举 $a$ 到 $b$，判断，复杂度约为 $O(T(b-a)(\sqrt b + \log_{10} b))$，炸了。

## 2、预处理（正解）
 $1 \leq a \leq b \leq 100000$，这个数据很容易想到预处理出所有包含 $1$ 到 $9$ 的“无平方数” 的个数。我们用 $x(i)(j)$ 表示前 $i$ 个数包含数字 $j$ 的无平方数的个数。

$check(i,j)$ 表示 $i$ 是否包含 $j$，$zyz(i)$ 表示 $i$ 是否为无平方数。

然后对于 $T$ 次询问，输出 $x(b)(d) - x(a - 1)(d)$ 。

复杂度为 $O(T + 10^6 \times (\sqrt{10^5} + \log(10^5)) )$

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[100008][20];
inline bool check(int x, int y) {
	while (x > 0) {
		if (x % 10 == y)
			return 1;
		x /= 10;
	}
	return 0;
}
//判断x中是否包含y 
inline bool zyz(int x) {
	for (int i = 2; i * i <= x; i++)
		if (x % (i * i) == 0)
			return 0;
	return 1;
}
//判断无平方数 
int main() {
	int t;
	for(int i = 1; i <= 100005; i ++)
		for(int j = 0; j < 10; j ++)
			x[i][j] = x[i - 1][j] + (check(i, j) && zyz(i) ? 1 : 0);
	//预处理：前缀和操作 
	cin >> t;
	for(int i = 1; i <= t; i ++) {
		int a, b, d;
		cin >> a >> b >> d;
		cout << x[b][d] - x[a - 1][d] << '\n';
	}
	//每次询问输出前缀和 
	return 0;
}
```


---

## 作者：Scorilon (赞：0)

To [SP8496](https://www.spoj.com/problems/NOSQ/)

这道题可以用到前缀和思想，先预处理出所有的结果，然后 $O(1)$ 查询即可。

注意：

- 是不能被 $x^2(x≠1)$ 的数整除的数叫做无平方数。 
- $d$ 可以为 $0$。

即对于每次询问，给出 $s[b][d]-s[a-1][d]$ 的值。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int s[100005][10];//第s[i][j]位存储从0~i中包含j的无平方数的数量
int t;
int a,b,c;
int z,p;
bool find(int x){
	for(int i=2;i*i<=x;i++){//注意i=2而非i=1，如原解释注意
		if(x%(i*i)==0) return false;
	}
	return true;
}
int main(){
	for(int i=2;i<=100000;i++){
		if(find(i)){
			z=i;
			while(z){
				p=z%10;
				s[i][p]=1;
				z/=10;
			}
		}
	}
	for(int i=0;i<=9;i++){
		for(int j=2;j<=100000;j++){
			s[j][i]+=s[j-1][i];
		}
	}
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a,&b,&c);
		printf("%d\n",s[b][c]-s[a-1][c]);
	}
	return 0;
}
```


---

## 作者：Leasier (赞：0)

前置芝士：[线性筛](https://www.luogu.com.cn/blog/cicos/notprime)

考虑先线性筛出 $1$ ~ $10^5$ 之间的无平方数（说白了就是筛出 $\mu^2$ 函数），然后暴力枚举其每一位，接下来求每一位存在情况的前缀和，每次询问直接输出即可。时间复杂度为 $O(T + N \log_{10} N + NM)$。

代码：
```cpp
#include <stdio.h>

const int N = 1e5 + 7, M = 9;
int prime[N], mu_sqr[N], sum[N][M + 7];
bool p[N], vis[N][M + 7];

inline void init(){
	int cnt = 0;
	p[0] = p[1] = true;
	mu_sqr[1] = 1;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			mu_sqr[i] = 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				mu_sqr[t] = 0;
				break;
			}
			mu_sqr[t] = mu_sqr[i];
		}
	}
	for (register int i = 1; i < N; i++){
		if (mu_sqr[i] == 1){
			for (register int j = i; j > 0; j /= 10){
				vis[i][j % 10] = true;
			}
		}
	}
	for (register int i = 1; i < N; i++){
		for (register int j = 0; j <= M; j++){
			sum[i][j] = sum[i - 1][j] + (vis[i][j] ? 1 : 0);
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (register int i = 1; i <= t; i++){
		int a, b, d;
		scanf("%d %d %d", &a, &b, &d);
		printf("%d\n", sum[b][d] - sum[a - 1][d]);
	}
	return 0;
}
```

---

