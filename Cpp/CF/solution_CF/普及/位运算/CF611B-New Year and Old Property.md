# New Year and Old Property

## 题目描述

The year 2015 is almost over.

Limak is a little polar bear. He has recently learnt about the binary system. He noticed that the passing year has exactly one zero in its representation in the binary system — $ 2015_{10}=11111011111_{2} $ . Note that he doesn't care about the number of zeros in the decimal representation.

Limak chose some interval of years. He is going to count all years from this interval that have exactly one zero in the binary representation. Can you do it faster?

Assume that all positive integers are always written without leading zeros.

## 说明/提示

In the first sample Limak's interval contains numbers $ 5_{10}=101_{2} $ , $ 6_{10}=110_{2} $ , $ 7_{10}=111_{2} $ , $ 8_{10}=1000_{2} $ , $ 9_{10}=1001_{2} $ and $ 10_{10}=1010_{2} $ . Two of them ( $ 101_{2} $ and $ 110_{2} $ ) have the described property.

## 样例 #1

### 输入

```
5 10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2015 2015
```

### 输出

```
1
```

## 样例 #3

### 输入

```
100 105
```

### 输出

```
0
```

## 样例 #4

### 输入

```
72057594000000000 72057595000000000
```

### 输出

```
26
```

# 题解

## 作者：Rainbow_qwq (赞：7)

[原题](https://www.luogu.org/problemnew/show/CF611B)

题意：求出从A到B之间的所有数中，有多少数转化为2进制后，只有一个零。

有点大，A，B<=10^18

思路：
这道题可以找规律，但是~~我脑子太笨~~，只会自己构造符合条件的数
```cpp
先构造一个二进制位全是1的数，
如：
long long t1=pow(2,i)-1
i可取2~62，这里以i=7为例。
t1=(10000000)-1=(1111111)

再构造t2=t1-pow(2,j),其中0<=j<=i-2。
此时 t1-t2 就是符合条件的数。
如：我们取j=3,
则t2=(1111111)-(0001000)=(1110111)
刚好二进制只有一位是0。

二重循环枚举，时间复杂度：O((log n)^2)

枚举代码：
//a,b为题意输入的数，tot为总数
long long t1,t2,tot=0;
for(int i=2;i<=62;i++){
	t1=pow(2,i)-1;
	for(int j=i-2;j>=0;j--){
		t2=t1-pow(2,j);
		if(t2>=a&&t2<=b)tot++;
	}
}
```
完整AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define TP long long
inline TP read(){//快读
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long a=read(),b=read(),sum,tot;
long long ans[1000010],t1,t2;
int main()
{
	//枚举
	for(int i=2;i<=62;i++){
		t1=pow(2,i)-1;
		for(int j=i-2;j>=0;j--){
			t2=t1-pow(2,j);
			if(t2>=a&&t2<=b)tot++;//符合条件，总数++
		}
	}
	cout<<tot;
	return 0;
}
```
注意：这里不能用位运算，会出错！！！！

[我的AC记录](https://www.luogu.org/recordnew/show/16384160)

[使用位运算的WA记录](https://www.luogu.org/recordnew/show/16384205)

---

## 作者：Fool_Fish (赞：3)

# 题意

给出A、B，请你求出从 A 到 B 之间的所有数中，有多少数转化为 $2$ 进制后，只有一个零。$1\leq a,b\leq 10^{18}$

# 思路

加上数据范围考虑就是一道很明显的数位 DP 好吧

在进行搜索的时候我们可以保存一个当前 $0$ 的个数，搜完后判断当前 $0$ 的个数是不是为 $1$ ,是的话就累加答案，最后加个记忆化就行了

**code**:

```cpp
int dp[MAXN][MAXN];
int dfs(int pos,bool lim,int cnt0){
	if(pos==0) return (cnt0==1);
	if(!lim && ~dp[pos][cnt0]){
		return dp[pos][cnt0];
	}
	int up=lim?a[pos]:1;
	int ans=0;
	for(int i=0;i<=up;i++){
		ans+=dfs(pos-1,lim&&(i==a[pos]),cnt0+(i==0));
	}
	if(!lim){
		dp[pos][cnt0]=ans;
	}
	return ans;
}
```

但是这样又有问题了

在上面这份代码中，前导 $0$ 也会被算作是 $0$，这样就会影响答案

所以我们还需再加一个对前导 $0$ 的判断：

**code**：

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
#define int long long
const int MAXN=75;
int a[MAXN];
int dp[MAXN][MAXN];
int dfs(int pos,bool lim,int cnt0,bool zero){
//	cout<<pos<<endl;
	if(pos==0) return (cnt0==1);
	if(!lim && ~dp[pos][cnt0] && !zero){
		return dp[pos][cnt0];
	}
	int up=lim?a[pos]:1;
	int ans=0;
	for(int i=0;i<=up;i++){
		ans+=dfs(pos-1,lim&&(i==a[pos]),cnt0+(i==0 && !zero),zero && i==0);
	}
	if(!lim && !zero){
		dp[pos][cnt0]=ans;
	}
	return ans;
}
int work(long long n){
	memset(dp,-1,sizeof(dp));
	int cnt=0;
	while(n){
		a[++cnt]=n%2;
		n/=2;
	}
	return dfs(cnt,1,0,1);
}
signed main(){
	long long l,r;
	scanf("%lld %lld",&l,&r);
	printf("%lld",work(r)-work(l-1));
return 0;
} 
```



---

## 作者：封禁用户 (赞：3)

这一题有种找规律的感觉。

这是1~100之间符合要求的数字
```
2 5 6 11 13 14 23 27 29 30 47 55 59 61 62 95
```
之间的规律一点也不好找。规律出现在他们的差上面。差分别是
```
(3.1)(5.2.1)(9.4.2.1)(17.8.4.2.1)
p=1,  p=2   p=3      p=4
```
有没有发现第一个数字是2的p次方+1，后面就一直/2下去

规律出来了，代码也就好写了↓↓↓
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,ans=0;
int main()
{
    scanf("%lld %lld",&a,&b);
    ll sum=2,i=1,p=0,j=1;/*第一个数字是2*/
    for( ; ; )
    {
        if(p==0)/*p已经被除没了*/
        {
            j*=2;
            p=j+1;
        }
        
        if(sum<a);/*还不到就啥都别干*/
        else if(sum>b)/*到了就跳出循环*/
        break;
        else
        ans++;
		sum+=p;
        p/=2;
    }
    printf("%lld",ans);
    return 0;
}
```
顺便附上每一个数字都判断一下(TLE)的代码，可参考一下↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int check(int i)
{
	int ans=0;
	while(i)/*2进制的转换办法，不用管前后顺序*/
	{
		if(i%2==0)
		ans++;
		i/=2; 
	}
	return ans;
}
int a,b,ans=0;
int main()
{
	scanf("%d %d",&a,&b);
	for(int i=a;i<=b;i++)/*一个一个下去*/
	{
		if(check(i)==1)
		ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：hmya (赞：2)

尝试用暴力嗯草过去。

我们注意到，在 $i$ 位的二进制数中，有 $i-1$ 个数转化为2进制后，只有一个 $0$。

原因显然，以 $5$ 位二进制数举例。

`10111,11011,11101,11110`

共有以上 $4$ 个 $5$ 位二进制数只有一个 $0$。

而他们中， $0$ 所在的位越高，值就越小。

`10111<11011<11101<11110`

比如 $10111$ 中 $0$ 在第 $3$ 位，是最高的能放 $0$ 的位，所以他就是最小的。

那么，我们自然而然的想到，我们可以把区间 $[lt,rt]$ 破成 $3$ 块，第一块是 $lt$ 位，第二块是从 $lt$ 位再多一位到 $rt$ 位再少一位，第三块是 $rt$ 位。

显然，第二块可以直接用整块的方法计算。

对于第一块和第三块这样的散块，我们可以枚举 $0$ 的位置。

然后就做完了，时间复杂度 $O(\log(n))$，跑得飞快。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int lt,rt;
int ans;
int P=1;
int num(int x){
    int N=0;
    bool tag=false;
    for(int i=62;i>=0;i--){
        if((x&(1ll<<i))||tag){
            tag=true;
            N++;
        }
    }
    return N-1;
}
signed main(){
    scanf("%lld%lld",&lt,&rt);
    int now=lt;
    int tag=-1;
    for(int i=0;i<num(lt)+1;i++){
        if(!(now&(1ll<<i))){
            tag=i;
            now+=(1ll<<i);
        }
    }
    if(tag>-1){
        now-=(1ll<<tag);
    }
    if(now>rt){
        puts("0"); 
        return 0;
    }
    if(tag>-1)ans++;
    for(int i=num(lt);i>=1;i--){
        if(now>rt){
            break;
        }
        if((1ll<<i)>now){
            continue;
        }
        if(!(now&(1ll<<i))){
            now-=(1ll<<(i-1));
            now+=(1ll<<i);
            if(now<=rt){
                ans++;
            }
        }
    }
    if(now>rt){
        printf("%lld\n",ans);
        return 0;
    }
    if(num(lt)==num(rt)){
        printf("%lld\n",ans);
        return 0;
    }
    int L=num(lt)+1,R=num(rt)-1;
    for(int i=L;i<=R;i++){
        ans+=(i);
    }
    int tmp=R+1;
    now=(1ll<<(tmp+1))-1ll-(1ll<<(tmp-1));
    if(now<=rt)ans++;
    for(int i=tmp;i>=1;i--){
        if(now>rt){
            break;
        }
        if((1ll<<i)>now){
            continue;
        }
        if(!(now&(1ll<<i))){
            now+=(1ll<<i);
            now-=(1ll<<(i-1ll));
            if(now<=rt){
                ans++;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

注意事项：

1. `(1ll<<i)`的地方一定要加`ll`，不然会爆
2. `if(tag>-1)ans++;`如果不判，答案就会多一个
3. 务必先减再加，不然会爆

---

## 作者：XL4453 (赞：1)

### 题目分析：

首先想到一个数位 DP，由于整个的判断都是在二进制下进行的，考虑将其转换为二进制进行记忆化搜索，然后基本就是一个数位 DP 的板子题了。

但这样还不够优秀，可以考虑打表（预处理），代码简单，不易出错。

大概计算一下所有的满足条件的数。显然有，对于一个 $n$ 二进制位，有且仅有 $n$ 个数满足条件，$\log_2^{10^{18}}$ 大概是 $\dfrac{18}{0.3}$ 也就是 $60$ 位二进制，立刻得到大约有几千个数满足条件（这里只大概计算了一下数量级，更具体的还是写个程序跑一下吧）。

这些数直接打表打出来是不现实的，但数量也不是很多，可以直接预处理出来。

这里用构造法直接求出所有情况，即用一个全是二进制 $1$ 的数去掉任意一位就可以了。

------------

### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long num[4005],l,r,tot;
int main(){
	scanf("%lld%lld",&l,&r);
	for(long long i=1;i<=63;i++){
		for(long long j=0;j<i-1;j++){
			num[++tot]=((1ll<<i)-1ll-(1ll<<j));
		}
	}
	sort(num+1,num+tot+1);
	l=upper_bound(num+1,num+tot+1,l-1)-num;
	r=upper_bound(num+1,num+tot+1,r)-num;
	printf("%d",r-l);
	return 0;
}
```


---

## 作者：happybob (赞：0)

来一篇打表的解法。

显然暴力打表会很慢，考虑找一下规律，我们先列举出前几个二进制只有 $1$ 个 $0$ 的数看看：$2, 5, 6, 11, 13, 14, 23, 27, 29, 30$，直接看没有规律，我们来看差，分别是 $3, 1, 5, 2, 1, 9, 4, 2, 1$。

1. $2^1+1=3,2^0=1$。
1. $2^2+1=5, 2^1=2,2^0=1$。
1. $2^3+1=9,2^2=4,2^1=2,2^0=1$。

规律显然易见，打表出来从 $1$ 到 $10^{18}$ 中这样的数只有 $1712$ 个，暴力即可。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long g[1715] = { 不给看 };

int main()
{
	long long a, b;
	scanf("%lld%lld", &a, &b);
	int ans = 0;
	for (int i(1); i <= 1712; i++)
	{
		if (g[i] >= a and g[i] <= b) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：王熙文 (赞：0)

这题的题解区里大家好像都想复杂了，实际上我们只需要用 $\text{dfs}$ 构造出这样的数就行了。

从 $1$ 开始枚举，每次都判断是否满足条件，之后扩展到别的数。

设当前的数为 $x$。当 $a \le x \le b$ 并且二进制中的 $x$ 恰好有一个 `0`，这样的数就满足条件。我们可以使用一个 `bool ` 类型数判断二进制下它是否正好有一个 `0`，否则就没有 `0`（二进制下多于一个 `0` 的情况，扩展到别的数也一定多于一个 `0`，且看下文分解）。

当 $x$ 大于 $b$ 了，扩展后的数也一定大于 $b$，直接 `return;`

接下来考虑扩展到别的数。

当 $x$ 二进制下正好有一个 `0`，它只能扩展到 $x \times 2 + 1$，因为在二进制下乘上 $2$（二进制是 `10`）相当于二进制下在末尾添了一个 `0`，再加上 `1` 相当于在末尾添了一个 `1`，不会影响 `0` 的个数。

当 $x$ 二进制下没有 `0`，它可以扩展到 $x \times 2$，这样扩展后的数末尾就有了一个 `0`。它也可以扩展到 $x \times 2 + 1$，这样扩展后的数还是没有 `0`。

接下来是代码qwq：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long a,b,cnt=0; // 记得要用 long long 类型 qwq

void dfs(long long x,bool if0)
// 当前的数是 x，如果二进制 x 有一个 0，if0 为 true，否则（没有 0）为 false
{
    if(x>=a && x<=b && if0) ++cnt; // 满足条件
    if(x>b) return; // 大于 b 了扩展后也大于 b，不可能
    if(if0) dfs(x*2+1,1 /* 添 1 没有改动 */); // 当二进制下 x 有一个 0，只能在末尾添 1
    else dfs(x*2,1 /* 添了一个 0，扩展后的数有一个 0 了 */),dfs(x*2+1,0 /* 添 1 没有改动 */); // 否则在末尾添 0 或 1 都行
}

int main()
{
    cin>>a>>b;
    dfs(1,0); // 从 1 开始扩展，二进制下 1 没有 0
    cout<<cnt; // 输出满足要求的个数
    return 0;
}
```

---

## 作者：LXH5514 (赞：0)

## CF611B New Year and Old Property

### 题目大意：

好像已经翻译了很清楚了，[传送门](https://www.luogu.com.cn/problem/CF611B) 。

### solution

基本就是数位 dp 的板子。

将数先转化为 2 进制 ，从高位开始记搜，记搜的时候记录一下当前状态下出现过几个 0，因此状态就是 $f[pos][a]$，$a$ 表示 0 出现的次数，（貌似只需要记录是否出现过 0，但实现起来略有些复杂，~~主要是我太菜了~~，这样虽然时间复杂度会劣一点，但能过题就行）。到最后一个数位的时候就判断一下出现 0 的次数是否为 1 即可，具体细节在代码注释中。（数据范围 `1e18`，记得开 `long long`）。

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+f*(c-'0'),c=getchar();
	return x;
}
const int MAXN=2000;//避免越界，实际上用开这么大，反正数位dp 基本上空间都很小。
int f[MAXN][MAXN];
int a,b,len;
int d[MAXN];
int dfs(int pos,int limit,int lead,int sum)
{
	if(!pos) return sum==1;
	if(limit==0&&lead==0&&f[sum][pos]!=-1)return f[sum][pos];//如果这个状态做到过就直接返回值
	int maxn=1,res=0;
	if(limit==1)maxn=d[pos];
	for(int i=0;i<=maxn;i++)
	{
		res+=dfs(pos-1,limit&&(i==maxn),lead&&(i==0),sum+(int)((!lead)&&(i==0)));//记录出现了多少个0.
	}
	if(limit==0&&lead==0)f[sum][pos]=res;
	return res;
}
int part(int x)
{
	len=0;
	while(x>0)
	{
		d[++len]=x%2;
		x>>=1;
    }//将数转化成二进制。
	return dfs(len,1,1,0);
}
int pd(int x)//避免边界出锅，特判一下l，
{
	int h=0;
	while(x>0)
	{
		if(x%2==0)h++;
		x>>=1;//看一下有多少个 1 ，
	}
	if(h==1)return 1;
	return 0;
}
signed main()
{
	memset(f,-1,sizeof(f));//一定要清空，为了避免出锅，直接初始化为 -1 ，
	a=read();
	b=read();
	printf("%lld\n",part(b)-part(a)+pd(a));
 	return 0;
}
```

---

## 作者：斜揽残箫 (赞：0)

## Description

给出 $a$ 和 $b$，求 $a$ ~ $b$ 中二进制状态有且仅有一个零的数字的个数。

$1 \leq a,b \leq 10 ^ {18}$

## Solution

看到要求关于数位的题，立马想到数位 DP。

说到数位 DP，肯定写记忆化搜索了，~~毕竟模板改改就行了~~，记忆化搜索需要一个记录每一位的数组 $s[i]$，一个储存答案的数组 $f[i][j][k][p]$。

先把 $a$ 和 $b$ 换为二进制，发现最多有 57 位，根据这个来开数组。

对于一个长度为 $cnt$ 的数字，我们可以从高位向低位枚举数字，统计 0 的个数，当 0 的个数为 1 的时候就返回 1，否则返回 0。

+ 我们枚举的位数是必须要记录的。 $(id)$
+ 其次，我们还要记录是否出现过 0。 $(have)$
+ 还要记录是否上一位是否到达了边界。 $(limit)$
+ 记录是否有前导零，因为我们要找是 0，所以如果有前导零就会误判，要直到前导零没有了才可以统计答案。 $(zero)$

每次没有到达边界并且没有前导零的时候就可以用 $f$ 数组把答案存下来，记忆化搜索。

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
LL l,r,Ans;
LL f[100][100][2][2];
int s[100]; 
inline LL read()
{
	LL s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
LL dfs(int id,int have,bool limit,bool zero)//上面提到的四个参数
{
  if(!id) return (have == 1) ? 1 : 0;//判断是否为 1 个，返回。
  if(~f[id][have][limit][zero] && !limit && !zero) return f[id][have][limit][zero];//记忆化直接调用
  int up = limit ? s[id] : 1;//枚举数位
  LL ans = 0; 
  for(int i = 0;i <= up;i ++) {
    ans += dfs(id - 1,have + (i == 0 && !zero),(i == up) && limit,zero && (i == 0));//这里一定要到没有了前导零才能够统计答案
  }
  if(!limit && !zero) f[id][have][limit][zero] = ans;//记忆化
  return ans;
} 
int Solve(LL num)
{
  int cnt = 0;
  memset(f,-1,sizeof f);
  for(;num;num >>= 1) s[++ cnt] = num & 1;//分离数位
  return dfs(cnt,0,1,1);
}
signed main()
{
  l = read(),r = read();
  Ans = Solve(r) - Solve(l - 1);
  printf("%lld",Ans);
  return 0;
}
```

---

## 作者：cqbz_lipengcheng (赞：0)

### 前言：
在同学的推荐下做了这道题，感觉还是比较水，但是很适合我这种蒟蒻
### 题解：
通过分析题目，我们不难知道此题要求我们求出l~r之间又有多少个数转化成二进制后含一个零，所以我们不难想到在DFS中存入一个记录零的个数的变量。但是显然
我们会被前导零影响，所以要加上前导零的判断。
### 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 105;
long long a[MAXN], dp[MAXN][MAXN], n, m;
long long dfs(long long step, long long sumz, bool limit, bool qz) {
	if(step < 0) {
		if(sumz == 1) return 1;
		else return 0;
	}
	if(!limit && qz && dp[step][sumz] != -1) return dp[step][sumz];
	long long up = limit ? a[step] : 1, ans = 0;
	for(long long i = 0;i <= up; i++) {
		if(i == 0 && qz) ans += dfs(step - 1, sumz + 1, limit && (a[step] == i), qz || i);
		else if(i == 1) ans += dfs(step - 1, sumz, limit && (a[step] == i), qz || i);
		else ans += dfs(step - 1, sumz, limit && (a[step] == i), qz || i);
	}
	if(qz && !limit) dp[step][sumz] = ans;
	return ans;
}
long long query(long long sum) {
	memset(dp, -1, sizeof(dp));
	long long cnt = 0;
	while(sum) {
		a[cnt++] = sum % 2;
		sum /= 2;
	}
	return dfs(cnt - 1, 0, 1, 0);
}
int main() {
	scanf("%lld %lld", &n, &m);
	printf("%lld", query(m) - query(n - 1));
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

此题看到所求和数位有关，果断考虑 $数位DP$ 。  
经过一系列思考，我们需要在 $DP$ 里面记录数位(老套路了)， $0 , 1$ 的个数，  
至于为什么要记录 $1$ 的个数，是因为我们在统计时要是把前导 $0$ 给算进去了我们 $数位DP$ 就~~直接起飞了~~对吧。  
所以这里我们要记录一下 $1$ 的个数，看看这一步统计的 $0$ 是前导 $0$ 还是数位 $0$ 。  
不过这里我们为了防止以后遇到类似的题需要维护其他东西时 $数位DP$装不下了，我们可以考虑优化这两维。  
由于 $0$ 的个数大于了 $1$ 的话肯定就没贡献，所以这里我们的这一维大小可以设置为 $2$ 而另一位只用记录有没有出现过 $1$ 即可，数组大小就缩成 $1$ 了。  
一道还算可以的题，能打 $数位DP$ 为什么要熬费心思去找规律呢对吧。  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
long long dp[105][3][2],n,m;
int digit[105],le;
long long dfs(int len,int sum,int srt,bool up)
{
	if(!len) return sum == 1;
	if(sum > 1) return 0;
	if(!up && dp[len][sum][srt] != -1) return dp[len][sum][srt];
	int maxlen = (up == 0) ? 1 : digit[len];
	long long res = 0;
	for(int i = 0 ; i <= maxlen ; i ++)
	{
		if(i == 0) 
		{
			if(srt > 0) res += dfs(len - 1 , sum + 1 , 1 , up && (i == maxlen));
			else res += dfs(len - 1 , sum , 0 , up && (i == maxlen));
		}
		else res += dfs(len - 1 , sum , 1 , up && (i == maxlen)); 
	}
	if(!up) dp[len][sum][srt] = res;
	return res;
}
long long Solve(long long x)
{
	le = 0;
	while(x) digit[++ le] = x % 2 , x >>= 1;
	return dfs(le , 0 , 0 , 1);
}
int main()
{
	scanf("%lld %lld",&n,&m);
	memset(dp , -1 , sizeof dp);
	printf("%lld\n",Solve(m) - Solve(n - 1));
	return 0;
}
```

---

