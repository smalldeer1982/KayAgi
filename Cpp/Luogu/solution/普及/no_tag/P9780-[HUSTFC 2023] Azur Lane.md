# [HUSTFC 2023] Azur Lane

## 题目描述

你是港区的一位指挥官，你可以通过培养指挥喵来增强舰队的实力，指挥喵由对应的喵箱培育。喵箱有 $k$ 个等级，等级越高稀有度越高。你每天会获得若干个喵箱（至少一个），然后再使用 ''一键放入'' 将这些喵箱放到喵窝里进行培育。''一键放入'' 会优先放入稀有度更高的喵箱（即按照稀有度从高到低排序后依次放入），放入的喵箱会排在已放入喵箱的后面，在**每天结束时**系统会自动扣除与喵窝中喵箱数量相等的钱。最开始时你的喵窝里没有喵箱。

因为你非常懒，所以你会等 $n$ 天后才把喵箱一起打开。在你 $n$ 天后进入喵窝时，你看到了 $m$ 个喵箱，用一个长度为 $m$ 的序列 $a$ 表示喵窝里按放入先后顺序排列的喵箱的等级。但是你已经忘了这 $n$ 天里你每天获得了多少喵箱了，你甚至忘了 $n$ 的值是多少，显然这有许多情况。你想知道，对于满足 $1 \leq n \leq m$ 的所有整数 $n$，在所有情况中，这 $n$ 天总共扣除的钱数至少为多少？

## 说明/提示

样例一解释：

当 $n=1$ 时，无法在一天内获得这 $3$ 个喵箱（第二个喵箱的等级大于第一个喵箱的等级，不符合 ``一键放入'' 从高到低放入的原则），因此输出 $-1$。

当 $n=2$ 时，第一天获得第一个喵箱，此时喵窝内有 $1$ 个喵箱，当天花费为 $1$；第二天获得后两个喵箱，此时喵窝内有 $3$ 个喵箱，当天花费为 $3$。因此总钱数为 $4$。

当 $n=3$ 时，每天依次获得一个喵箱，总钱数为 $1+2+3=6$。

## 样例 #1

### 输入

```
3 3
2 3 1
```

### 输出

```
-1 4 6 ```

## 样例 #2

### 输入

```
8 4
3 2 4 2 1 2 3 2
```

### 输出

```
-1 -1 -1 21 22 25 29 36 ```

# 题解

## 作者：uncle_steve (赞：2)

## 知识点： 

就是一道板子贪心题。

## 思路：

当  $n=m$  时，刚好每天都放一个喵箱，可使用等差数列求和公式（高斯公式）计算：

- $\displaystyle\sum_{i=1}^{n} i$ 。

再看题面：**在每天结束时系统会自动扣除与喵窝中喵箱数量相等的钱。**  易知，在越晚的时候放喵箱，花费就越少。

例如：在 $\texttt{3}$ 天中放入了 $\texttt{6}$ 个喵箱（保证为单调不上升序列）：


最差：第一天 $\texttt{4}$ 个，第二天 $\texttt{1}$ 个，第三天 $\texttt{1}$ 个，花费 $4+5+6=15$ 元；

最好：第一天 $\texttt{1}$ 个，第二天 $\texttt{1}$ 个，第三天 $\texttt{4}$ 个，花费 $1+2+6=9$ 元；


**贪心策略：很明显，在越后面的天数放喵箱，花费越少。**

那代码怎么写呢？我们先倒序判断，只要当前值不小于之前的值，那么我们就可以付钱，并记录更新。

最后，在从头遍历一遍，如果答案数组的位置非 $\texttt{0}$，输出即可，如果为 $\texttt{0}$，输出 $\texttt{-1}$ 即可。

### 注意事项：

1.本题数据范围：$k\ (1 \leq k \leq 10^6)$，需开 `long long`！！！

2.注意答案数组的更新，并小心公式数值溢出！

## 我的代码（有注释，仅供参考）：


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+10;
int n,m,k,s[N],ans[N],sum;
signed main()
{
	cin>>m>>k;
	ans[m]=(1+m)*m/2; //等差数列求和公式（n=m时，求总和即可）；
	sum=m-1;
	for(int i=1;i<=m;i++){
		cin>>s[i];
	}
	for(int i=m-1;i>=1;i--){//倒序判断
		if(s[i]>=s[i+1]){//默认大的在前面，否则无解
			ans[sum]=ans[sum+1]-i;//可以为之花费，并记录钱数；
			sum--;
		}
	}
	for(int i=1;i<=m;i++){
		if(ans[i]){//当前位置有选择（非0）；
			cout<<ans[i]<<" ";
		}else{//反之输出-1；
			cout<<-1<<" ";
		}
	}
	
	return 0;
}
```

---

## 作者：佬头 (赞：2)

## Description
给定一个长度为 $m$ 的正整数序列 $A=\{a_1,a_2,\dots,a_m\}$。你每次会从左往右取走连续且降序的若干个 $a_i$（至少一个）接在序列 $B$ 的末尾，代价是连接后 $B$ 的长度（最开始 $B$ 的长度为 $0$），并且最终会将 $A$ 取完。请分别求出一共取 $i~(1\le i\le m)$ 次的[**最小总代价**](https://www.luogu.com.cn/problem/P9780)（若存在）。

（概述的与题目描述相差有点大，但显然本质上是等价的，因为`每天把喵箱按照稀有度从高到低排序后依次放入喵窝`，显然每天放入的稀有度是降序的）

## Solution
考虑把 $A$ 拆成 $cnt$ 段连续且降序的子序列，并且使每段尽可能的长，显然：
- 当 $i\lt cnt$ 时，没有合法的取数方案。
- 当 $i=cnt$ 时，只有一种取数方案（就是先后取走这 $cnt$ 段）。记 $v_j$ 表示取完第 $j$ 次后的总代价，$l_j$ 表示第 $j$ 段子序列的长度，则 $v_j=\sum\limits_{i=1}^{j}l_i,~ans_i=\sum\limits_{j=1}^{cnt}v_j$。
- 当 $i\gt cnt$ 时，有 $\tbinom{i-cnt}{m-cnt}$（即 $C^{i-cnt}_{m-cnt}$） 种取数方案（但这题不求这个）。我们思考如何从第二种情况推出这种情况的最优方案：
	+ 显然当 $i=cnt+1$ 时，就是在第二种情况的基础上将某一段子序列分两天取走。若我们选择把 $l_j~(l_j\gt1,j\ge1)$ 拆成 $l_x,l_y~(l_x,l_y\ge1)$ 并先后取走，则增加的贡献就是 $(\sum\limits_{i=1}^{j-1}l_i)+l_x$，因此我们想要让每次增加的贡献最少，就得尽量让 $j,l_x$ 越小。
	+ 当 $i\gt cnt+1$ 时同理。

  大体思路就是每次从前往后找到第一个可以拆的 $l_j$（等价于 $v_j-v_{j-1}$），把它拆成 $1,l_j-1$，同时计算增加的贡献（就是 $v_{j-1}+1$）。

为了方便理解，下面给出示意图（并非最优方案）：
![](https://cdn.luogu.com.cn/upload/image_hosting/lrc49gt0.png)

要开 `long long`。代码时间复杂度 $\mathcal O(m)$。

## Code
```cpp
#include <iostream>
using namespace std;
const int N = 1000006;
int m, a[N], cnt;
long long v[N], ans;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(long long x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	m = read(), read();
	for(int i = 1; i <= m; ++ i) a[i] = read();
	for(int l = 1, r; l <= m; l = r){
		r = l + 1;
		while(r <= m && a[r] <= a[r - 1]) ++ r;
		ans += v[cnt] = r - l + v[cnt ++];
	}
	for(int i = 1; i < cnt; ++ i) fputs("-1 ", stdout);
	write(ans);
	for(int i = cnt + 1, j = 0; i <= m; ++ i){
		while(v[j] + 1 == v[j + 1]) ++ j; //找可以拆的l[j+1]
		putchar(' '), write(ans += ++ v[j]); //显然v[j]已经计入答案里，我们直接对v[j]更新即可
	}
	return 0;
}
```


---

## 作者：S_Kuroko (赞：1)

## 题解

#### 思路

本题用贪心算法。

由题目可知喵箱放置越晚花费越少，因此尽可能多的在后面放置更多的喵箱。可以考虑倒序遍历，若当前 $a[i]$ 的值大于等于 $a[i+1]$ 的值，则将它加入后面的段使 $len$ 减小，并计算该段数代价。具体解释见代码。

```cpp
#include<bits/stdc++.h>
#define ll long long     //本题数据会超int类型 
using namespace std;

const int N=1e6+5;
ll n,m,k,a[N],b[N],len;
int main()
{
	cin>>m>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	b[m]=(1+m)*m/2;      //n=m时，每天获得一个喵箱，求总和即可 
	len=m;
	for(int i=m-1;i>=1;i--)
	{
		if(a[i]>=a[i+1])
		{
			len--;
			b[len]=b[len+1]-i;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(b[i])   //当前位置不是0 
		{
			cout<<b[i]<<" ";
		}
		else       //当前位置是0 
		{
			cout<<-1<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Anins (赞：1)

## [P9780 [HUSTFC 2023] Azur Lane](https://www.luogu.com.cn/problem/P9780)

### 题意：
给定一长度为 $m$ 的序列 $a$，分别将序列 $a$ 分成 $1,2, \dots ,n$ 段（$n$ 不确定，每段都不为空），要求每段内的数字单调不上升，定义代价为 $\sum\limits_{i=1}^{k}cut[i]$（$k$ 表示分成的段数，$cut[i]$ 表示前 $i$ 段内数字个数），输出分成 $1,2, \dots ,n$ 段各自所需要的**最小**代价，若无解输出 $-1$。

### 思路：
显然，$1 \leq n \leq m$。
- 当 $n=m$ 时，每个数字单独成段，代价恒为 $\frac{(1+n) \times n}{2}$（等差数列求和）。
- 当 $n < m$ 时，由贪心得：一个数字越往后放越优（被重复计算的次数少）。那么考虑倒序枚举数字大小，若当前数字不小于后面数字，则将它加入后面数字的那一段使段数减小，并计算该段数代价，由贪心得，该代价为最优解。
- 代码有注释，如果不理解可以手动模拟看下。

### 数据范围：
$1 \leq m \leq 10^6$，求和会爆 int，要开 long long。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long m, k, a[1000005];
long long f[1000005]; //f[i] 表示分成 i 段时需要的代价 
int main(){
	ios::sync_with_stdio(0);
	cin >> m >> k;
	for(int i=1; i<=m; i++) cin >> a[i];
	f[m]=(1+m)*m/2; //当 n=m 时的代价 
	long long k=m; // k 表示当前的分段数量 
	for(int i=m-1; i>=1; i--){
		if(a[i]>=a[i+1]) {
			k--; //可以将 a[i] 与 a[i+1] 捆绑，因此分段数量减少 1 
			f[k]=f[k+1]-i; //减去该数字在上一个代价中的贡献 
		}
	}
	for(int i=1; i<=m; i++){
		if(!f[i]) cout << "-1 ";
		else cout << f[i] << " ";
	}
	return 0;
}
```

---

## 作者：seika27 (赞：1)

### 分析
不难发现在 $n=m$ 时，所用的钱是 $\sum\limits_{i=1}^n i$。

也就是 $\frac{n^2+n}{2}$。

对于 $n=m-1$，我们需要有两个喵箱一起进入喵窝。

于此同时，为了让花费更少，我们希望让着两个喵箱尽可能晚的加入喵窝。

假如我们第一天就加入了两个喵箱，那么我们每一天，这两个喵箱都会花费掉我们的两个金币，也就是 $2n$ 枚金币。但如果我们把这两个喵箱放在最后一天加入，这两个喵箱就只花费掉了两枚金币。

总而言之，我们的 $n$ 每减少一次，就需要一个喵箱能与其余的一个或多个喵箱一起加入。

我们考虑倒着遍历，如果令当前的喵箱的等级为 $a_i$，那么如果 $a_i\geq a_{i+1}$，就说明这两个喵箱是可以一起进喵窝的，于此同时由于我们是倒着遍历，所以我们找到的这个一定是尽可能的后面的，所以可以直接加入。

令答案数组为 $f$，其中 $f_i$ 表示 $n=i$ 的情况。

我们知道 $f_j$，那么假设我们发现 $a_i\geq a_{i+1}$，那么我们实际减少了多少金币消耗呢？

首先，因为我们的合并，导致总天数减少一天，所以 $a_1\sim a_{i-1}$ 这里的每一个喵窝都少了一天，所以总消耗减少了 $i-1$ 枚金币。与此同时，原本 $a_i$ 消耗的金币是 $n-i+1$，而 $a_{i+1}$ 则是 $n-i$，一共是 $2(n-i)+1$。而现在合并以后变成了 $2(n-i)$。又减少一枚金币的消耗，所以一共减少了 $i$ 枚金币。

也就是 $f_j=f_{j+1}-i$。

对于 $-1$ 的判断也很简单，扫完一遍后，发现有 $p$ 个 $a_i\geq a_{i+1}$，那么第 $1\sim m-p-1$ 天就都是不合法的。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
/*
bocchi the rock and girls band cry
*/
int n,k;
const int N=1e6+6;
int a[N];
int f[N];
signed main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>k;
	for(register int i=1;i<=n;++i)cin>>a[i];
	f[n]=(n+1)*n>>1;
	int j=n;
	for(register int i=n-1;i;--i)
	{
		if(a[i]<a[i+1])continue;
		--j;
		f[j]=f[j+1]-i;
;	}
	for(register int i=1;i<=n;++i)
	{
		if(!f[i])cout<<"-1 ";
		else cout<<f[i]<<' ';
	}
}
```

---

## 作者：hz_lin7532159 (赞：0)

**贪心……**

## 过程：

当 $n=m$ 时，刚好每天都放一个喵箱。

因为**在每天结束时系统会自动扣除与喵窝中喵箱数量相等的钱**，所以贪心策略：喵箱越晚放越好。

先倒序遍历，只要今天的值不小于之前天数的值，那么我们就可以消费并更新。

最后特判 $-1$ 即可。

**注意**：十年 OI 一场空，不开____见祖宗。

## 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long m,k,n,sum,a[1000010],kq[1000010];
int main(){
	cin>>m>>k;
	kq[m]=(1+m)*m/2;						//(首相 + 末项 ) * 项数 / 2 ;
	sum=m-1;
	for(int i=1;i<=m;i++)	cin>>a[i];
	for(int i=m-1;i>=1;i--)					//倒序!!!
		if(a[i]>=a[i+1])					//必须大在前 
			kq[sum]=kq[sum+1]-i,sum--;		//可行就记录 
	for(int i=1;i<=m;i++)
		if(kq[i])	cout<<kq[i]<<" ";
		else		cout<<-1<<" ";			//无合法
	return 0;
}
```

---

## 作者：Lacuna (赞：0)

题面写的很难懂，但理解后还是很简单的。

#### 题意：

这题就相当于把一个数列 $a$ 分成 $1 \sim m$ 段，每一段满足单调不降，每天将前面已经分段的数的个数加进花费里，问最小的花费是多少。

#### 思路：

显然，我们越往前加入，这个花费加的次数越多，考虑从后往前分段。遍历到第 $i$ 个数满足 $a_i \ge a_{i+1}$，则这两个数可以分一段，又因为是从后往前遍历，所以找到的方案是最优的，因为要尽可能的在后面分段。

用一个 $f$ 数组记录答案，定义一个 $d$ 表示天数，每次的 $f_i$ 就是上一天的答案减去 $i$，因为我们要减去这新增一天前面 $i$ 个数产生的花费。

对于没有答案的地方，我们输出 $-1$ 即可。

预处理 $f_m$ 的情况，$f_m$ 相当于每天分一段，产生的花费就是 $\sum_{i=1}^{m} i$，用等差数列求和公式计算即可。

#### 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

#define gc getchar
#define pc putchar
#define LL long long

const int N=1e6+5; 

LL i,m,k,d,a[N],f[N];

inline LL read(){LL x=0,f=1; char ch=gc(); while(!isdigit(ch)){if(ch=='-') f=-1;ch=gc();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc();} return x*f;}
inline void write_(LL x){if(x<0) x=-x,pc('-'); if(x>9) write_(x/10); pc(x%10+'0');}
inline void write(LL x){write_(x); pc(' ');} 

int main(){
  d=m=read(),k=read();
  for(i=1;i<=m;i++) 
    a[i]=read();
  f[m]=(m+1)*m/2;
  for(i=m-1;i>=1;){
  	while(a[i]>=a[i+1]){
	  f[d-1]=f[d]-i,d--,i--;
    } i--;
  }
  for(i=1;i<=m;i++)
    write(f[i]?f[i]:-1);
  return 0;
}
```

---

## 作者：ssfx2019s005 (赞：0)

先考虑从什么时候开始合法，即第一个不输出 `-1` 的位置上的数是什么。

因为同一天内放置的箱子中，编号更大的总是在编号更小的点前面，所以，如果存在一个 $i<n$ 使得 $a[i] < a[i+1]$，则这两个箱子必定不是同一天放置的。所以第一个不输出 `-1` 的位置就是满足上述条件的 $i$ 的个数加一，我们将这个点记为 $p$。容易发现此时的答案 $res[p]$ 就是这些 $i$ 的值累加起来再加上 $n$，我们对上述点进行标记，代表该点以前和以后分为两天。

然后再考虑 $p$ 之后的情况。贪心地选择第一个没有被标记的节点 $i$ 并标记之，那么答案就会增加 $i$，可以看出这是答案最小的方案，直接输出即可。

代码：


```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;
int n,m;
const int N=1e6+15;
int a[N],blo[N],cnt;
signed main(){
	cin>>n>>m;
	int res=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i]<a[i+1]){
			++cnt;
			res+=i;
			blo[i]=1;
		}
	}
	res+=n;
	for(int i=1;i<=cnt;i++){
		cout<<"-1 ";
	}
	cout<<res<<" ";
	int now=1;
	for(int i=cnt+2;i<=n;i++){
		while(blo[now]){
			++now;
		}
		blo[now]=1;
		res+=now;
		++now;
		cout<<res<<" ";
	}
	return 0;
}
```

---

## 作者：rain_dew (赞：0)

原题目链接：[[HUSTFC 2023] Azur Lane](https://www.luogu.com.cn/problem/P9780)

经典贪心模拟题。

### 思路

很容易发现，当 $n=m$ 时，每天依次要获得一个喵箱，所有的喵箱都被放完，因此最后定会输出 $i_1+i_2+\cdots+i_n$，这里我们运用高斯求和公式计算即可。

再考虑前面的放置情况。很显然喵箱放置越晚花费越少，因此尽可能多的在后面放置更多的喵箱。这时，我们需要倒序判断，只要当前的值不比前面的小，那么我们就可以为之花费，记录留存。

最后，如果当前的位置仍是 $0$，为满足题目要求，输出 `-1`，否则输出当前花费。

### 注意

1. 本题目 $1 \le k \le 10^6\ (1 \le a_i \le k)$，数值极大，要开 `long long`；
2. 在运用求和公式时，也要注意防止溢出。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[1000005];
long long dp[1000005],ans;
int main()
{
	scanf("%d%d",&n,&k);
	dp[n]=1ll*(1+n)*n/2;
	for (int i=1;i<=n;i++)
		scanf("%d",a+i);
	int num=n;
	for (int i=n-1;i>=1;i--)
		if (a[i]>=a[i+1])
		{
			num--;
			dp[num]=dp[num+1]-i;
		}
	for (int i=1;i<=n;i++)
		if (dp[i])
			printf("%lld ",dp[i]);
		else
			printf("-1 ");
	return 0;
}
```

---

## 作者：sky_chen (赞：0)

【HUSTACM】此题解为官方题解。

显然每个喵箱越晚放入越好。

显然我们每天放的喵箱等级是一个单调不上升连续子序列。

考虑贪心。我们的策略是，开始每天只放一个喵箱，但是这可能会导致喵箱放不完，为了保证合法性，我们得在最后都尽可能地放喵箱，也就是说，最后几天每天放的喵箱等级一定是一个极大单调不上升连续子序列。

考虑选一个中间点 $k$，前 $k$ 个喵箱在前 $k$ 天中每天放一个，而后面每天都尽可能地放喵箱。

所以我们可以从后往前遍历数组，当遍历到第 $k$ 个位置时，我们已经计算出了最后 $n-k$ 个喵箱组成的极大单调不上升连续子序列的个数 $num$ 和这么放所最后 $n-k$ 个喵箱需要的钱数 $money$，而前 $k$ 个喵箱每天放一个，所以我们就得到了天数为 $k+num$ 时的答案，最小可能的钱数为 $k(k+1)/2 + num \cdot k + money$。

时间复杂度 $O(n)$​。

---

## 作者：Imerance1018 (赞：0)

### 题意简述

[传送门](https://www.luogu.com.cn/problem/P9780)

### 基本思路

贪心 + 模拟，从后往前依次遍历求解。

### 详细描述

可以发现，当 $n=m$ 时，答案为
$$
\sum_{i = 1}^{n} i
$$ 
可以直接使用[等差数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527418)进行求解（高斯公式指的是[另一个公式](https://zhuanlan.zhihu.com/p/408911169)）。

那其他情况怎么办呢？

观察样例，有了一个好用的结论：每个 $a_i>a_{i+1}$ 都为结果贡献了一天，如样例一中有 1 个 $a_2>a_3$ ，那么就无法只用 1 天完成。

再比如：
```
8 4
3 2 4 2 1 2 3 2
```
(样例二）

分析如下：
```
n=8
	1+2+3+4+5+6+7+8=36
n=7
    从后往前遍历：
    i=7
		3>2,满足条件。
    所以将第 7 个喵箱同第 8 个一起放入，结果就少了喵箱数是 7 的那一天，所以减 7，答案为 36-7=29。
n=6
    继续遍历：
    i=6
		2<3,不满足条件。
	i=5
		1<2,不满足条件。
	i=4
		2>1,满足条件。
	所以将第 4 个喵箱同第 5 个一起放入，结果就少了喵箱数是 4 的那一天，所以减4，答案为29-4=25。
n=5
    以此类推。
	......
n=3
    此时i=0,不满足条件。
    所以之后都输出 -1。
```

### 代码实现

**注意**：十年 OI 一场空，不开 long long 见祖宗（我 CSP-J2023 没开 long long 丢了 50 分）。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,a[1000010],f[1000010],len;
int main()
{
	scanf("%d%d",&m,&k);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	f[m]=(1+m)*m/2;
	len=m;
	for(int i=m-1;i>=1;i--)
	{
		if(a[i]>=a[i+1])
		{
			len--;
			f[len]=f[len+1]-i;
		}
	}
	for(int i=1;i<=m;i++)
		if(f[i])
			printf("%lld ",f[i]);
		else
			printf("-1 ");
	return 0;
}
``````

---

