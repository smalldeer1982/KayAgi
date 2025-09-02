# [COCI 2020/2021 #6] Anagramistica

## 题目描述

Biljana 喜欢出字谜游戏。

如果一个单词可以由另一个单词交换字母顺序得到，则称它们是「相似」的。

现在，她有 $n$ 个单词。她希望选出一些单词，使得其中恰好有 $k$ 对单词是「相似」的。请你帮她计算可行的方案数，对 $10^9 + 7$ 取模。

## 说明/提示

#### 样例 1 解释

恰含有一对「相似」的单词的方案为 `ovo, ono, voo` 和 `ovo, voo`。

------------

#### 数据规模与约定

**本题采用捆绑测试**。

| Subtask | 分值 | 数据规模与约定 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $1 \le n \le 15$ |
| $2$ | $30$ | $0 \le k \le 3$ |
| $3$ | $70$ | 无附加约定 |

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^3$，$0 \le k \le 2 \times 10^3$，单词的长度不超过 $10$ 且仅含小写字母。

------------

#### 说明

**本题分值按 COCI 原题设置，满分 $110$**。

**题目译自 [COCI2020-2021](https://hsin.hr/coci/archive/2020_2021/) [CONTEST #6](https://hsin.hr/coci/archive/2020_2021/contest6_tasks.pdf) _T3 Anagramistica_**。

## 样例 #1

### 输入

```
3 1
ovo
ono
voo```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2
trava
vatra
vrata
leo
ole```

### 输出

```
3```

## 样例 #3

### 输入

```
6 3
mali
lima
imal
je
sve
ej```

### 输出

```
6```

# 题解

## 作者：MinimumSpanningTree (赞：8)

[题目链接](https://www.luogu.com.cn/problem/P7552)

看完题解感觉这题的状态表示和转移方程好像还挺好想到的，不知道为什么自己考场上会想成一种奇怪的背包。

首先对每个字符串内的字符从小到大排序，相同的就是题目中「相似」的。我们把相同的字符串都归为一组，接下来用 `map` 就可以统计出每一组的字符串有多少个。这里用 $cnt_i$ 表示第 $i$ 组的字符串个数。接下来我们就可以从字符串组数和题目中的 $k$ 下手。

* 状态表示：$dp_{i,j}$ 表示考虑前 $i$ 组字符串，恰好 $j$ 对相似字符串的方案数。

* 状态转移：

  * 初始化：$dp_{0,0}=1$，唯一的方案是不取任何东西。 

  * $dp_{i,j}+=dp_{i-1,j}$，因为前 $i$ 组包含了前 $i-1$ 组，并且后面的枚举没有计算到第 $i$ 组取 $0$ 个字符串的情况。

  * 枚举第 $i$ 组字符串选择的字符串个数 $o$，$o$ 个相同的字符串一共能产生 $\frac{o(o-1)}{2}$ 的贡献，而要从第 $i$ 组中取出 $o$ 个，有 $C^o_{cnt_i}$ 种情况，所以 $dp_{i,j}+=\sum_{o=1}^{j}dp_{i-1,j-\frac{o(o-1)}{2}}\times C^o_{cnt_i}$。
 
* 答案在哪：$dp_{n,k}$，其中 $n$ 表示的是字符串组数，$k$ 为题目中的含义。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<unordered_map>
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
const int N=2e3+100;
int n,k,cnt[N],id;
ll dp[N][N],c[N][N];
string s;
unordered_map<string,int> um;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		sort(s.begin(),s.end()); 
		//map将「相似」的字符串归一组 
		if(um.count(s)) cnt[um[s]]++;
		else um[s]=++id,cnt[id]=1;
	}
	for(int i=0;i<=n;i++)//杨辉三角预处理出组合数 
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	dp[0][0]=1;//初始化 
	for(int i=1;i<=id;i++)//考虑前i组 
	{
		for(int j=0;j<=k;j++)//恰好j对相似 
		{
			dp[i][j]=dp[i-1][j];
			//枚举第i组取的字符串个数o 
			for(int o=1;o<=cnt[i]&&o*(o-1)/2<=j;o++) dp[i][j]=(dp[i][j]+dp[i-1][j-o*(o-1)/2]*c[cnt[i]][o]%MOD)%MOD;
		}
	}
	printf("%lld",dp[id][k]);
	return 0;
} 
```

---

## 作者：Chydz (赞：5)

首先可以发现一个性质：若串 $a$ 和 $b$ 相似且 $b$ 与 $c$ 相似，一定有 $a$ 与 $c$ 相似 ~~（显然）~~ 。 

于是可以将所有串分组，同一组内的两两相似，不同组的不相似。

对于一个组，任意选出 $k$ 个（$1\le k\le size$），都会有 $\frac{k(k-1)}{2}$ 的贡献。

然后就可以 `dp` 了。设 $f[i][j]$ 表示前 $i$ 组中选出**恰好构成 $j$ 对相似串**的方案数。枚举第 $i$ 组中**选的个数**（$l$）即可。最终答案为 $f[tot][k]$ （$tot$ 为组数）。

虽然 `dp` 过程中要枚举 $3$ 层：$i,j,l$。但实际上只有 $O(k\sum size)$ 即 $O(nk)$，通过此题没有问题。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;

const int mod=1e9+7;
int n,m,k,a[2005],f[2005][2005],b[2005],jc[2005],inv[2005],p[2005],size[2005],c[25];
char s[25];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int ksm(int a,int b){
	int s=1;
	while(b){
		if(b&1)s=1ll*s*a%mod;
		a=1ll*a*a%mod;b>>=1;
	}
	return s;
}
int getfa(int x){
	return x==p[x]?x:p[x]=getfa(p[x]);
}
int C(int n,int m){
	return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	n=read();
	k=read();
	for(int i=1;i<=n;i++){//将所有串排序（方便判断是否相似）
		cin>>s;
		int len=strlen(s);
		for(int j=1;j<=len;j++)c[j]=s[j-1]-'a';
		sort(c+1,c+1+len);
		a[i]=0;
		for(int j=1;j<=len;j++)a[i]=(a[i]*299ll+c[j]+1)%mod;
	}
	jc[0]=1;//阶乘
	for(int i=1;i<=n;i++)jc[i]=1ll*jc[i-1]*i%mod;
	inv[n]=ksm(jc[n],mod-2);//逆元
	for(int i=n-1;i>=0;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)b[i]=b[i-1]+i-1;//b：一组中选i个的贡献
	for(int i=1;i<=n;i++)p[i]=i;//并查集，分组
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)
			if(a[i]==a[j]){
				int f1=getfa(i);
				int f2=getfa(j);
				if(f1!=f2)p[f2]=f1;
			}
	}
	for(int i=1;i<=n;i++){
		p[i]=getfa(i);
		size[p[i]]++;
	}
	memset(a,0,sizeof(a));int tot=0;
	for(int i=1;i<=n;i++)if(size[i])a[++tot]=size[i];
   //tot：组数，a:每组的个数
	f[0][0]=1;//dp初始化
	for(int i=1;i<=tot;i++){
		for(int j=0;j<=k;j++){
			f[i][j]=f[i-1][j];//第i组中不选
			for(int k=1;k<=a[i]&&b[k]<=j;k++){
				f[i][j]=(f[i][j]+1ll*f[i-1][j-b[k]]*C(a[i],k)%mod)%mod;//第i组中选k个
			}
		}
	}
	cout<<f[tot][k];
	return 0;
}
```


---

## 作者：Fireworks_Rise (赞：4)

# 解题 idea

由于可以随意调换单词中的字母顺序，所以可以先对每个单词内部进行预处理排序，再用 $mp$ 记录其出现次数。

可以设 $f_{i,j}$ 为前 $i$ 个单词组中，恰好构成 $j$ 对相似单词的方案数。

枚举前 $m$ 组恰好构成 $i$ 对相似单词的数量，并且当前单词组使用了 $j$ 个单词的方案数，易知当前单词组可以贡献的相似单词数为 $(1+j-1)\times (j-1)\div 2$，并存入 $num$ 中。

利用杨辉三角预处理组合数学，则从当前单词组内的 $t$ 个单词中选出 $j$ 个单词的方案数为 $C_{t,j}$。

进而可以推出状态转移方程如下：

$f_{m,i}=(f_{m,i}+(f_{m-1,i-num}\times C_{t,j})$

最后输出 $f_{m,k}$ 即可，其中 $m$ 单词组数。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=2010;
string s;
int C[N][N];
int n,k,f[N][N];
map<string,int> mp;
void init_() {
	C[0][0]=1;
	for(int i=1;i<=2000;i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
signed main() {
	scanf("%lld%lld",&n,&k);
	init_();
	for(int i=1;i<=n;i++) {
		cin>>s;
		sort(s.begin(),s.end());
		mp[s]++;
	}
	map<string,int>::iterator it;
	int m=0;
	f[0][0]=1;
	for(it=mp.begin();it!=mp.end();++it) {
		m++;
		for(int i=0;i<=k;i++) {
			f[m][i]=f[m-1][i];
			int t=it->second;
			for(int j=1;j<=t&&j*(j-1)/2<=i;j++) {
				int num=j*(j-1)/2;
				f[m][i]=(f[m][i]+(f[m-1][i-num]*C[t][j])%mod)%mod;
			}
		}
	}
	printf("%lld\n",f[m][k]);
	return 0;
}
```


---

## 作者：DYYqwq (赞：2)

看到这种题，一定是要往计数 dp 的方面想。

不难想到，在字符串自身内部排序后，直接比较两个字符串是否相等是一种很容易判断相似的方法。

于是考虑将一堆相似的字符串放在一组中。将第 $i$ 组中的字符串数量记为 $mp_i$。

考虑设 $dp_{i,j}$  表示前 $i$ **组**单词，恰好有 $j$ **对**单词是相似的的方案数。

考虑转移，不妨枚举前 $i-1$ 组单词的相似**对数** $k$。

不难想到，这说明我们需要从第 $i$ 组的 $mp_i$ 个字符串中选取一些，导致多了 $j-k$ **对**。

这个太不好算我到底从第 $i$ 组拿了多少**个**字符串了！因为我需要用从这组拿出的字符串**个数** $x$ 计算多累计的方案数 $C_{mp_i}^x$。

于是考虑改变枚举的东西的意义。于是枚举第 $i$ 组字符串选择的字符串**个数** $k$，与之前的分析同理，其多累计的方案数 $C_{mp_i}^k$，而多产生的相似字符串对数为 $\frac{k(k-1)}{2}$。

由此不难得到，$dp_{i,j} = dp_{i-1,j}+\sum\limits_{k=1}^{k \le mp_i,\frac{k(k-1)}{2} \le j} dp_{i-1,j-\frac{k(k-1)}{2}}  \times C_{mp_i}^k$。这甚至可以滚动数组。

注意初始化，$dp_{0,0} = 1$。

代码为了压行不择手段，请勿模仿。

```cpp
#include<bits/stdc++.h>
#define int int_fast64_t
using namespace std;
const int mod = 1e9 + 7;
int n , K , mp[2010] , tot , C[2010][2010] , dp[2][2010];
unordered_map<string , int> ump;
signed main()
{
	for(int i = 0 ; i <= 2000 ; i ++) {C[i][0] = 1; for(int j = 1 ; j <= i ; j ++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1] , C[i][j] %= mod;}
	scanf("%lld%lld" , &n , &K); string s;
	for(int i = 1 ; i <= n ; i ++)
	{
		cin >> s; sort(s.begin() , s.end());
		if(ump.find(s) == ump.end()) ump[s] = ++ tot;
		mp[ump[s]] ++;
	}
	dp[0][0] = 1;
	for(int i = 1 ; i <= tot ; i ++) for(int j = 0 ; j <= K ; j ++) {dp[i & 1][j] = dp[(i & 1) ^ 1][j]; for(int k = 1 ; k <= mp[i] && k * (k - 1) / 2 <= j ; k ++) dp[i & 1][j] += dp[(i & 1) ^ 1][j - k * (k - 1) / 2] * C[mp[i]][k] % mod , dp[i & 1][j] %= mod;}
	printf("%lld" , dp[tot & 1][K]);
	return 0;
}
```

---

## 作者：Cells (赞：1)

#### 前置知识

1. 会使用 STL 中的 `map`。

2. 有 DP 基础。

3. 有脑子。

#### 思路

1. 容易想到字符串 $a$ 与 $b$ 相似，$a$ 与 $c$ 相似，则有 $b$ 与 $c$ 相似。
2. 然后，把所有相似的字符串分到一个组。如果我们从这里面 $n$ 个字符串选出 $m$ 个字符串，那么就会有 $C_n^m$ 种选择的可能。
3. 我们上一步选了 $m$ 个字符串，那这些字符串会产生 $C_m^2=\frac{m(m-1)}{2}$ 对单词是相似的。
4. 设 $dp_{i,j}$ 表示前 $i$ 组字符串中选出 $j$ 对相似字符串的方案总数，那 DP 方程就是 $dp_{i,j}=\sum_{num=1}^{cnt_i}dp_{i-1,j-\frac {num \times (num-1)}{2}} \times C_{cnt_i}^{num}$。解释一下，$tot$ 是分了多少组，$cnt_i$ 是这一组有多少个字符串，$num$ 是选出来了多少字符串。转移方程就是从上一组转移过来，然后减去当前能产生的字符串对数，再乘上你选出这些字符串的方案数的和。

#### 实现

分组先排序，能算出单词总长度 $len \leq 2 \times 10^4$，时间能接受，开 `map` 映射第几组。

注意到 $C_n^m$ 的时候 $1 \leq n \leq 2 \times 10^3$，所以需要用阶乘的逆元，预处理一下。

答案就是 $dp_{tot,k}$。

**Code**
```c++
# include <bits/stdc++.h>
# define int LL//开long long 
using namespace std;

typedef long long LL;

const int N = 2e3 + 10, mod = 1e9 + 7;

int n, k, tot;
int dp[N][N], fac[N], inv[N], cnt[N];

map<string, int> mp;

LL qpow(LL a, LL b, LL p){
	LL res = 1;
	while(b){
		if(b & 1) res = (res * a) % p;
		a = a * a % p;
		b >>= 1;
	}
	
	return res % p;
}

void getfacinv(){//线性求阶乘逆元 
	inv[n] = qpow(fac[n], mod - 2, mod);
	for(int i = n - 1; i >= 0; i --) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
}

LL C(int n, int m){//组合数 
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		string s;
		cin >> s;
		sort(s.begin(), s.end());
		if(!mp[s]) mp[s] = ++ tot;
		cnt[mp[s]] ++;//组内个数 
	}
	
	fac[0] = 1;
	for(int i = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % mod;
	getfacinv();//预处理阶乘和逆元 
	
	dp[0][0] = 1;
	for(int i = 1; i <= tot; i ++){
		for(int j = 0; j <= k; j ++){
			dp[i][j] = dp[i - 1][j];//不选 
			
			for(int num = 1; num <= cnt[i] && num * (num - 1) / 2 <= j; num ++){
				dp[i][j] += (dp[i - 1][j - num * (num - 1) / 2] * C(cnt[i], num)) % mod;
				dp[i][j] %= mod;//记得取模 
			}
		}
	}
	
	cout << dp[tot][k];
	
	return 0;
}
```

**完结撒花！！！**

---

## 作者：xuan_gong_dong (赞：1)

## 题面

[P7552 [COCI2020-2021#6] Anagramistica](https://www.luogu.com.cn/problem/P7552)

## 分析

每一对相似匹配，它们排完序之后包长得完全一样的。

所以直接用  `map` 就行了。再考虑动态规划的转移方程，dp 有两维，表示前 $i$  个单词组中选择了 $j$ 对组合。

显然第一位可以滚掉，但是懒得滚了，反正随便过。

dp 的定义出来之后转移也顺水推舟就生出来了：

$$dp_{i,j}=dp_{i-1,j- \frac{ k \times (k-1)}{2}}+C_{cnt_i}^{k}$$

再预处理组合数就好了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e9+7;
int n,k;
int a[100010],b[100010];
map<string,int> m;
int num[10000],tot;
int dp[2010][2010];
int fac[2010];
int inv[2010];
int qpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1){
			ans=ans*x%p;
		}
		x=x*x%p;
		y>>=1;
	}
	return ans;
}
void init()
{
	fac[0]=fac[1]=1;
	inv[0]=1,inv[1]=1;
	for(int i=2;i<=2005;i++)
	{
		fac[i]=fac[i-1]*i%p;
		inv[i]=qpow(fac[i],p-2);
	}
}
char c[100];
signed main()
{
	init();
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		memset(c,0,sizeof(c));
		cin>>c;
		sort(c,c+strlen(c));
		string tmp=c;
		m[tmp]++;
	}
	dp[0][0]=1;

	int id=1;
	for(auto it=m.begin();it!=m.end();it++,id++)
	{
			for(int j=0;j<=k;j++)
			{
				for(int i=0;i<=(*it).second;i++)
				{
					if((i*(i-1)/2)>j)break;
	//				cout<<(j-(i)*(i-1)/2)<<' '<<id<<endl;
	//				cout<<(*it).second<<i<<' '<<(fac[(*it).second]*inv[i]%p*inv[(*it).second-i]%p)<<endl;
					dp[id][j]+=dp[id-1][j-(i)*(i-1)/2]%p*(fac[(*it).second]*inv[i]%p*inv[(*it).second-i]%p)%p;
					dp[id][j]%=p;
	//				cout<<dp[id][j]<<endl;
				}		
		}
	}
	cout<<dp[id-1][k]%p;
	return 0;
}
```

---

## 作者：Bamboo_Day (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7552).

# 分析
这道题有个比较明显的思路就是把所有相似的字符串分为一组，然后对每一组进行 dp，设 $f_{i,j}$ 表示当前到了第 $i$ 组，已经凑出了 $j$ 对相似的串的方案数.

考虑如何计算贡献，假设现在已经到了第 $i$ 组，第 $i$ 组一共有 $num_i$ 个字符串，准备选 $x$ 个字符串，那么这一组对总相似对数的贡献就是 $\frac{x(x-1)}{2}$，对方案数的贡献就是 $C_{num_i}^x$.

所以状态转移方程就出来了：
$$f_{i,j} = f_{i,j}+f_{i-1,j-\frac{x(x-1)}{2}}\times C_{num_i}^x$$ 

还有个显然的点就是对于每一组只需要记录这一组一共有几个字符串就可以了 ~~这个应该都知道罢~~.

# 预处理
## 组合数 $C$
因为要用到组合数 $C$ 所以对 $C$ 进行预处理.

当然也有预处理阶乘和逆元的做法，因为我太菜了所以只给出 $n^2$ 的预处理版本.

```cpp
void init(){
	C[0][0] = 1;
	for(int i = 1; i <= 2000; i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
		}
	}
}
```
对于组合数学不了解的可以去看我这篇博客 [【学习笔记】组合计数](https://blog.csdn.net/weixin_43617116/article/details/130289373?spm=1001.2014.3001.5501).

## 相似串的统计
**不知道冷不冷的知识：字符串也是可以进行排序的**.
```cpp
	for(int i = 1 ;i <= n; i++){
		string s;
		cin >> s;
		sort(s.begin(),s.end());
		if(!m.count(s)){
			m[s] = ++cnt;
		}
		int id = m[s];
		num[id]++;
	}
```

# Code
```cpp
#include <bits/stdc++.h>
const int mod = 1e9+7;
const int N = 2e3+10;
#define int long long
using namespace std;
map<string,int> m;
int num[N],cnt = 0;
int n;
int f[N][N];
int k;
int C[N][N];
void init(){
	C[0][0] = 1;
	for(int i = 1; i <= 2000; i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
		}
	}
}
signed main(){
	init();
	cin >> n >> k;
	for(int i = 1 ;i <= n; i++){
		string s;
		cin >> s;
		sort(s.begin(),s.end());
		if(!m.count(s)){
			m[s] = ++cnt;
		}
		int id = m[s];
		num[id]++;
	}	
	f[0][0] = 1;
	for(int i = 1; i <= cnt; i++){
		for(int j = 0; j <= k; j++){
			for(int x = 0; x <= num[i]&&x*(x-1)/2<=j; x++){
				f[i][j] = (f[i][j] + (f[i-1][j-x*(x-1)/2]*C[num[i]][x])%mod)%mod;
			}
		}
	}
	cout << f[cnt][k];
	return 0;
}
```
## 坑点
记得取模和开 `long long`！！！

---

## 作者：mxxby (赞：1)

今天学校比赛最后一题，我竟然是唯一 AC 的，妙啊。

赶紧来发篇题解。

# 题目介绍

**[题目传送门](https://www.luogu.com.cn/problem/P7552)**

在本题中：

如果一个单词可以由另一个单词交换字母顺序得到，则称它们是「相似」的。

现在，她有 $n$ 个单词。她希望选出一些单词，使得其中恰好有 $k$ 对单词是「相似」的。请你帮她计算可行的方案数，对 $10^9$ 取模。

# 思路

多读几次题目，你会发现这题其实~~不算太难~~做法很~~基础~~容易想到。

这题其实就是一堆预处理加动规。

首先，我们要处理有几组字符串（一组中的串两两「相似」），这样可以把问题从每个字符串取不取转换成——每组取几个数。

如下代码就是预处理字符串：

```
	for(int i=1;i<=n;i++){
		yw=0;
		for(int j=1;j<=zs;j++){
			if(xs(i,wz[j])==1){
				gs[j]++;
				yw=1;
				break;
			}
		}
		if(!yw) gs[++zs]++,wz[zs]=i;
	}
```

上述代码中判断「相似」的函数：
```
bool xs(int x,int y){
	string a=s[x],b=s[y];
	for(int i=0;i<26;i++) zfa[i]=0,zfb[i]=0;//清零
	for(int i=0;i<a.size();i++) zfa[a[i]-'a']++;//对于26个小写字母统计个数
	for(int i=0;i<b.size();i++) zfb[b[i]-'a']++;//因为在题目限制里说了：单词的长度不超过 10 且仅含小写字母
	for(int i=0;i<26;i++) if(zfa[i]!=zfb[i]) return 0;如果个数不对直接驱逐！
	return 1;否则欢迎新人！
}
```

其次，如果一组数中选 $s$ 个数，所贡献的对数为 $ s\times(s-1)\div2$，（$s$ 个数两两一组，学过组合的应该不须过多解释）但一组数肯定会有 $ s $ 以上个数，那就要从 $gs_i$ 里面选 $s$ 个数，虽然 $s$ 相同但都视为不同种，这还是组合数学，那完全可以预处理。

如下是求 $i$ 个数取 $j$ 个数的代码：

```
	for(int i=0;i<=n;i++){//预处理的预处理
		dp[0][i]=1;//0个数选i个肯定是1种方案
		dp[i][0]=1;//i个数选0个也是1种方案
	}
	for(int i=1;i<=n;i++){//i里选j个 
		for(int j=1;j<=i;j++){
			dp[i][j]+=dp[i-1][j-1];//这件选 
			if(i-1>=j) dp[i][j]+=dp[i-1][j];//这件不选
			dp[i][j]%=mod; //注意取模
		}
	}
```
然后也要将选 $s$ 个「相似」数的贡献对数预处理。（主要当时不知咋做，能预处理的，我都处理了一番qwq）
```
	for(int i=0;i<=n;i++) ds[i]=i*(i-1)/2;//选i件的对数 
```

之后就可以思考 dp 啦。~~其实 dfs 爆搜也能拿到分。~~

范围可以二维 dp。

第一个为前 $i$ 个数，第二个为对数，存的值为方案数。

但这样必须再弄一个 $t$，但是总比 dfs 拿分多。

$i$ 为前 $i$ 个数，$j$ 为对数，$t$ 为这次取 $t$ 个数，总共 $ds_{t}$ 对。

咱们一边看代码一边理解。

```
	ddp[0][0]=1;//初始化
	for(int i=1;i<=zs;i++){//对于前i组数达到j对的方案数
		for(int j=0;j<=k;j++){
			for(int t=0;t<=gs[i];t++){//当前gs[i][j]选t个数贡献ds[t]对
				if(j>=ds[t]) ddp[i][j]=(ddp[i][j] + (ddp[i-1][j-ds[t]]*dp[gs[i]][t]) )%mod;从前i-1个数贡献j-ds[t]加上第i个数贡献ds[t]队就是ddp[i][j]啦
				else break;//因为ds[t]越加越大，如果大于j那后续肯定都不能做了直接退出
			}
		}
	}
```

然后你会发现其实感觉起来代码好像也没多少，这字符串也就开始预处理派上了用场。

# 一堆~~麻袋~~代码

最后看看我的纯代码：

```
#include<bits/stdc++.h>
#define lon long long
using namespace std;
const lon mod=1e9+7;
lon n,k;
lon wz[2023],zfa[36],zfb[36];//判断相似 
lon dp[2023][2023],ds[2023],ddp[2023][2023];//预处理 
string s[2023];//前期过度 
bool yw;
lon gs[2023],zs,da;//排列组合道具 
bool xs(int x,int y){
	string a=s[x],b=s[y];
	for(int i=0;i<26;i++) zfa[i]=0,zfb[i]=0;
	for(int i=0;i<a.size();i++) zfa[a[i]-'a']++;
	for(int i=0;i<b.size();i++) zfb[b[i]-'a']++;
	for(int i=0;i<26;i++) if(zfa[i]!=zfb[i]) return 0;
	return 1;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++){
		yw=0;
		for(int j=1;j<=zs;j++){
			if(xs(i,wz[j])==1){
				gs[j]++;
				yw=1;
				break;
			}
		}
		if(!yw) gs[++zs]++,wz[zs]=i;
	}
	for(int i=0;i<=n;i++){
		dp[0][i]=1;
		dp[i][0]=1;
	}
	for(int i=1;i<=n;i++){//i里选j个 
		for(int j=1;j<=i;j++){
			dp[i][j]+=dp[i-1][j-1];//这件选 
			if(i-1>=j) dp[i][j]+=dp[i-1][j];//这件不选
			dp[i][j]%=mod; 
		}
	}
	for(int i=0;i<=n;i++) ds[i]=i*(i-1)/2;//选i件的对数 
	ddp[0][0]=1;
	for(int i=1;i<=zs;i++){
		for(int j=0;j<=k;j++){
			for(int t=0;t<=gs[i];t++){
				if(j>=ds[t]) ddp[i][j]=(ddp[i][j] + (ddp[i-1][j-ds[t]]*dp[gs[i]][t]) )%mod;
				else break;
			}
		}
	}
	cout<<ddp[zs][k];
	return 0;
}//整体也就56行，但相信各位神犇的代码都比我短qwq
```

这题主要是思路要清楚，实现的话除了 dp 要琢磨琢磨其实都蛮简单的。~

~~蒟蒻的第三篇题解二审求过 qwq。~~

~~亿天一题解，写完就跑路。（溜了溜了。）~~

---

## 作者：Liquefyx (赞：1)

噢，写一个简单的灰题的题解 ~~（再不写题解就凉了）~~

# 题目分析

题目要求找有多少对除顺序外一模一样的字符串，那么将每个字符排序后用 map 储存或统计各个字符个数后归为一类就行了，我们将每一类字符串的个数统计下来，用 dp 再算个组合数便能解决这道题。

但是，因为组合数的缘故，我们还需要求逆元 （因为组合数有除法，含除法运算没办法取模出准确的值）。而 dp 便简单了，枚举每一类字符串取出来的个数便好了。

# 代码奉上

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
string a;
int n,k,QAQ,inv[2015],sum[2005],jc[2015],abab[2005],f[2][2005];
map <string,int> px;
inline int Inv(int x,int base=mod-2){
	int res=1;
	while(base){
		if(base&1)res= (long long) res*x%mod;
		x= (long long) x*x%mod;
		base>>=1;
	}return res;
}
inline void init(){
	jc[0]=1;
	for(int i = 1; i <= 2009; i++)
		jc[i]= (long long) jc[i-1]*i%mod;
	inv[2009]=Inv(jc[2009]);
	for(int i = 2008; i >= 0; i--)
		inv[i]= (long long) inv[i+1]*(i+1)%mod;
	return;
}
int main() {
	scanf("%d%d",&n,&k);
	init();
	for(int i = 1; i <= n; ++i){
		cin>>a;
		sort(a.begin(),a.end());
		if(!px[a])
			px[a]=++QAQ;
		++sum[px[a]];
	}
	int op=0;
	f[0][0]=1;//滚动数组（怕炸）
	for(int i = 1; i <= QAQ; ++i){
		op^=1;
		memset(f[op],0,sizeof f[op]);
		for(int j = 0; j <= k; ++j)
			for(int o = 0; o <= sum[i]; ++o){
				int now = o*(o-1)/2, qwq= (long long) jc[sum[i]]*inv[sum[i]-o]%mod*inv[o]%mod;
				if(now + j <= k)
					f[op][j+now] = (f[op][j+now]+( (long long) f[op^1][j]*qwq)%mod)%mod;
			}
	}
	cout<<f[op][k];
	return 0;
}
```

芜湖，一篇题解水过。

---

## 作者：joy2010WonderMaker (赞：0)

### 题目分析

这道题的相似满足传递性。~~显然。~~

所以我们将所有的字符串分类，每类字符串互相之间都是相似的。这个可以用各种方法解决。

然后就可以开始愉快地进行动态规划。

这是一个套路，$dp[i][j]$ 表示前 $i$ 类字符串，选了 $j$ 个字符串的方案数。转移时可以枚举第 $i$ 类字符串选的个数 $k$，设第 $i$ 类有 $x$ 个字符串，所以 $dp[i][j]=(dp[i-1][j]+\sum\limits dp[i-1][j-\dfrac{k(k-1)}{2}]\times C_{x}^{k})\bmod p$。

组合数可以 $O(n^2)$ 预处理，动态规划是 $O(k\sum\limits size)$ 的，也就是 $O(nk)$，字符串分类是 $O(\sum\limits |S|\log|S|)$ 的，所以总时间复杂度 $O(n(n+k))$。

### 代码

```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
unordered_map<unsigned long long,int>m;
int n,k,dp[2005][2005],C0[2005][2005];
char s[11];
void init(){//预处理组合数
	C0[0][0]=1;
	for(int i=1;i<=2000;i++)
		C0[i][0]=C0[i][i]=1;
	for(int i=1;i<=2000;i++)
		for(int j=1;j<i;j++)
			C0[i][j]=(C0[i-1][j]+C0[i-1][j-1])%MOD;
}
long long C(long long n,long long m){
	return C0[n][m];
}
int main(){
	init();
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		unsigned long long res=1;
		int len=strlen(s+1);
		sort(s+1,s+len+1);
		for(int j=1;j<=len;j++)//哈希处理字符串分类
			res=res*1331+(s[j]-'a'+1);
		m[res]++;
	}
	int cnt=0;
	dp[0][0]=1;//dp初始化
	for(auto &&it:m){//dp
		cnt++;
		for(int j=0;j<=k;j++){
			dp[cnt][j]=dp[cnt-1][j];
			for(int s=1;s<=it.second&&(s-1)*s/2<=j;s++){
				int num=s*(s-1)/2;
				dp[cnt][j]=(dp[cnt][j]+((long long)(dp[cnt-1][j-num]*C(it.second,s))%MOD)%MOD)%MOD;
			}
		}
	}
	printf("%d",dp[cnt][k]);
	return 0;
}
```


---

