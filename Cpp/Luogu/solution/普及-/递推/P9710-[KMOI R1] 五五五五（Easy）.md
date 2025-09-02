# [KMOI R1] 五五五五（Easy）

## 题目背景

“迟序之数，非出神怪，有形可检，有数可推。”——祖冲之

## 题目描述

小宋有一个序列 $a_1,a_2\dots,a_n$，其中对于 $i\in [1,n]$，满足 $a_i\in[0,9]$。

对于 $1\le l\le r\le n$，他记 $f(l,r)$ 等于 $\overline{a_la_{(l+1)}\dots a_r}$ 的末尾连续 $5$ 的个数。

例如：对于序列 $a=\{1,1,4,5,1,4\}$，$f(2,4)=1,f(1,3)=0$。

现在请你求出:

$$\Big(\sum\limits_{l=1}^
{n}\sum\limits_{r=l}^{n} f(l,r)\Big) \bmod 10^9+7$$

## 说明/提示

## 样例 $1$ 解释：

$f(1,1)=1$。

$f(1,2)=2$。

$f(2,2)=1$。

得到答案 $ans=f(1,1)+f(1,2)+f(2,2)=4$，故输出 $4$。

## 数据范围

**本题采用 subtask 捆绑测试。**

令 $m=\max\{a_1,a_2,\dots,a_n\}$。

| 子任务编号 | 测试点编号 | $n\le$ | $m\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $100$ | $3$ | 无 | $3$ |
| $2$ | $2\sim 4$ | $2\times 10^5$ | $5$ | $\mathbf{A}$ | $22$ |
| $3$ | $5,6$ | $100$ | $5$ | 无 | $10$ |
| $4$ | $7\sim 10$ | $2\times 10^5$ | $5$ | $\mathbf{B}$ | $25$ |
| $5$ | $11\sim 20$ | $2\times 10^5$ | $9$ | 无 | $40$ |

特殊性质 $\mathbf{A}:$ 序列平均数为 $5$。

特殊性质 $\mathbf{B}:$ 序列单调不上升。

对于 $100\%$ 的数据：$1\le n\le 2\times 10^5$，$0\le m\le 9$。

对于 $\forall i\in [1,n]$，满足 $a_i\in[0,9]$。

## 样例 #1

### 输入

```
2
5 5```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 1 4 5```

### 输出

```
4```

# 题解

## 作者：Fire_flame (赞：6)

## $\mathbf{Solution}$

子任务 $1$：因为平均数小于等于 $3$，也就是说不会出现 $5$，输出 $0$ 即可。

----

子任务 $2$：平均数是 $5$，最大值也不超过 $5$，也就是说 $a_1=a_2=\dots=a_n=5$。

那么答案即为：

$$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}(r-l+1)$$

不难发现，枚举左端点 $l$，那么以左端点为 $l$ 的区间的贡献是 $(n - l + 2)\times(n - l + 1)\div 2$。

时间复杂度 $O(n)$。

----

子任务 $3$：枚举左端点，右端点，然后 $O(n)$ 求解答案即可。

时间复杂度 $O(n^3)$。

----

子任务 $4$：

因为序列单调不上升，而且最大数为 $5$。

所以如果出现了 $5$，肯定是只有前面连续的一段。

即可转化成子任务 $2$。

----
子任务 $5$：

考虑递推，假设当前**右端点**枚举到了第 $r$ 位，已经遍历了连续 $cnt$ 个 $5$。

- 如果 $a_r\neq5$，$cnt$ 清零，不添加贡献。

- 如果 $a_r=5$，考虑左端点 $l$：
	1. 首先 $cnt$ 要记得加一。
	2. 如果左端点 $l\le r-cnt$，每一个区间贡献添加 $cnt$。总贡献添加 $(r - cnt + 1) \times cnt$。
   3. 如果左端点 $r-cnt+1\le l\le r$，总贡献添加 $cnt\times(cnt-1)\div 2$。
   
最后统计答案即可。

标程：

```cpp
#include<bits/stdc++.h>//by Fire_flame
#define int long long
using namespace std;
const int MAXN = 5e5 + 5, MOD = 1e9 + 7;
int n, ans, cnt, a[MAXN];
signed main(){
	scanf("%lld", &n);
	ans = 0, cnt = 0;
	for(int i = 1;i <= n;i ++)scanf("%lld", &a[i]);
	for(int i = 1;i <= n;i ++){
		if(a[i] == 5)cnt ++;
		else cnt = 0;
		ans += (i - cnt + 1) * cnt % MOD + cnt * (cnt - 1) / 2 % MOD;
		ans %= MOD;
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：HEzzz (赞：2)

[题目跳转键](https://www.luogu.com.cn/problem/P9710)

## 分析

对于所有合法的 $l$ 和 $r$，他的 $f(l,r)$ 是可以通过 $f(l,r-1)$ 得到的，这就让我们想到了区间动态规划，但是这样必定会超时，所以不能怎么做。

## 解题思路

定义一个数组 $s_i$ 表示以第 $i$ 个数为结尾，末尾有多少个连续的 $5$。下面是求出 $s$ 数组的代码。

```cpp
for(int i=1;i<=n;i++) if(a[i]==5) s[i]=s[i-1]+1; else s[i]=0;
```
上面这个代码也很好理解，重点在下面这张图片。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ij8nxgn.png)

我们枚举 $r$ ，表示以 $r$ 为结尾的 $f$ 函数。

- 对于所有的在绿色框框以内的 $l$，它们对答案产生的贡献均为 $s_r$，而又多少在绿色框框里的 $l$ 呢？这也非常简单，即 $r-s_r+1$ 个。所以总的绿框框对答案产生的贡献为 $(r-s_r+1)\times s_r$。

- 对于所有的在蓝色框框以内的 $l$，它们对答案产生的贡献是一个等差数列，即 $(s_r-1)+(s_r-2)+....+1$，化简后是 $(s_r-1)\times s_r {\div}2$。

So，所有的以 $r$ 为结尾的 $f$ 函数对答案产生的贡献为
$$
(r-s_r+1)\times s_r+(s_r-1)\times s_r {\div}2	
$$

最后这道题答案如下！ 
$$
\sum_{r=1}^{n} (r-s_r+1)\times s_r+(s_r-1)\times s_r {\div}2	
$$

这样的代码时间复杂度达到了恐怖如斯的 $O(n)$。

## code
```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define _antirep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
typedef unsigned long long lxl;
const int N=2e5+5,mod=1e9+7; 
lxl n,a[N],s[N],ans; 
int main()
{            
	scanf("%lld",&n);
	_rep(i,1,n) scanf("%lld",a+i);
	_rep(i,1,n) if(a[i]==5) s[i]=s[i-1]+1; else s[i]=0;
	_rep(i,1,n) ans+=(i-s[i]+1)*s[i]+(s[i]-1)*s[i]/2,ans%=mod; 
 	printf("%lld",ans);
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

### 初步思路：

每次暴力枚举 $l$ 和 $r$，再从 $l$ 循环到 $r$，统计答案。

但这样时间复杂度是 $O(n^3)$ 的，过不了。

------------


### 优化：

我们可以先枚举 $r$，再从 $r$ 循环到 $1$，用一个变量
$num$ 记录末尾 $5$ 的数量。

我们发现对于每个 $\le i-num+1$ 的 $l$，对答案的贡献是 $num$，它们的总贡献是 $(i-num+1)\times num$。对于每个 $>i-num+1$ 的 $l$，对答案的总贡献是 $(num-1)\times num\div2$。

时间复杂度虽然降到了 $O(n^2)$，但还过不了。

------------
### 正解

我们要在刚刚枚举 $r$ 的基础上，再 $O(1)$ 计算出以 $r$ 为末尾的 $5$ 的数量。

我们可以一遍遍历一遍数，具体来说，是这样的：

$$num\Leftarrow\begin{cases}0&a_i\ne 5\\num+1&a_i=5\end{cases}$$

剩下步骤和之前一样。

------------
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
int n,ans,num;
int a[1000005];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==5){
			num++;
			ans=(ans+num*(i-num+1)%mod+num*(num-1)/2%mod)%mod;
		}
		else num=0;
	}
	cout<<ans%mod;
	return 0;
}
```


---

## 作者：Chiesl (赞：1)

这是一道推公式题。

### 思路

这题看看数据范围按照题意描述的来，暴力枚举明显会 TLE，那么就只能~~投机取巧~~进行一些小小的分析了。

我们边输入边处理，统输入到哪，$r$ 就是哪。计当前连续出现过几次 5，每次只要 5 的出现次数不为零，将已输入的数分为两部分：非连续末尾 5 部分，以及连续末尾 5 部分，开始计算：

#### 第一部分

首先是这一段连续 5 出现之前 $l$ 的总数，那就用当前的总长度 $r$ 减去当前这段连续 5 的长度，这段对于答案的贡献就是：$(r - len) \times len$，其中 $len$ 表示连续 5 的长度。

例子： 1 1 4 5 这一段中，$r = 4$，可以以这几个数为头：1, 1, 4。

其总数正好为：$r - len$，即 $4 - 1 = 3$。

能拼出来的对答案有贡献（末尾含 5）数就有：1 1 4 5，1 4 5，4 5，总贡献为 3，其值正好为：$(r - len) \times len$，即 $(4 - 1) \times 1 = 3$。

很容易理解，在连续 5 之前可以为 $l$ 的总数乘末尾连续 5 的总数可以得到第一部分对答案的贡献。

#### 第二部分

然后计算在这段连续 $5$ 的贡献，其实就是套用等差数列的公式，例：5 5 5 5。

以第一个 5 为 $l$ 时，数字为 5 5 5 5，其对答案的贡献为：4。

以第二个 5 为 $l$ 师，数字为 5 5 5，其对答案的贡献为：3。

找到规律后，可以得出整个序列的贡献就为：1 + 2 + 3 + 4。

设 $len$ 表示末尾连续 5 的长度，则有其对答案的贡献为：$\frac{len(1 + len)}{2}$。

所以输入到第 $r$ 个数，末尾连续 5 的长度为 $len$ 时，其对答案的总贡献为：$(r - len) \times len + \frac{len \times (1 + len)}{2}$。

### 代码

明白了这些，我们可以很快写出如下程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int main () {
	unsigned long long n, ans = 0, tmp = 0, a;
	scanf("%llu", &n);
	for (unsigned long long r = 1; r <= n; r++) {
		scanf("%llu", &a);
		if (a == 5) tmp++;//累计长度
		else tmp = 0;//不是 5 清零
		if (!tmp) continue;
		ans += (r - tmp) * tmp + (((1 + tmp) * tmp) >> 1);
      		/*蒟蒻比赛的时候推错了，只拿了60分qwq
           	蒟蒻比赛时推的：r - tmp + (1 + tmp) * tmp / 2 */
	}
	printf("%llu", ans % mod);//最后 mod 上就行了
	return 0;
}
```






---

## 作者：Miyamizu_Mitsuha (赞：1)

考虑每个 $5$ 的贡献。由于要求的是连续的 $5$ 的个数，所以存一下当前是连续的第几个 $5$，然后我们观察一组样例：

`1 1 1 5 5 5 1`
 
 这里我们分别定义这三个五为 $1\sim 3$ 号。
 
 显然一号的贡献为 $1\times 4=4$，前面的三个 $1$ 和他自己都能提供一个贡献。那么二号的贡献呢？显然不能直接认定为 $5\times 2$。虽然他前面（包括自己）有五个数，但是当左指针到自己时，本来的 $2$ 个贡献会变成一个（由于贡献算不上一号了），所以二号的贡献为 $2+2+2+2+1=9$。那么三号呢？显然就是 $3+3+3+3+2+1=15$。前面的三个一以及一号都能和三号提供 $3$ 的贡献，二号能提供 $2$，自己能提供 $1$。于是就可以总结出规律，设当前连续 $l$ 个 $5$，先计算出该 $5$ 所在 $5$ 的联通块的左端点左边到整个数列左端点的距离，在上文的例子中就是第一个 $1$ 和第三个 $1$，不难发现为 $i-l$，每个又能提供 $l$ 的贡献，所以这部分贡献即为 $(i-l)\times l$。然后联通块内的贡献可以表示为一个首项为 $l$，末项为 $1$ 的等差数列，套公式为 $\frac{l\times (l+1)}{2}$，然后加在一起取模即可。愿意逆元可以逆一下，不过其实没必要。
 
 ```
#include <stdio.h>
#include <iostream>
using namespace std;
#define int long long
signed main(){
  int n,a[200005],ans=0,l=0;
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=n;i++){
    if(a[i]==5){
    	l++;
      ans=(ans+l*(l+1)%1000000007*500000004+(i-l)*l%1000000007)%1000000007;
    }else l=0;
  }
  cout<<ans;
  
return 0;
}
```


---

## 作者：zxh923 (赞：1)

# P9710 [KMOI R1] 五五五五（Easy）题解

[题目传送门](https://www.luogu.com.cn/problem/P9710)。

### 思路

这道题在赛时在最后 $5$ 分钟想出了正解。

这道题观察题目可以看出，只有 $5$ 会产生贡献，所以可以查每一个 $5$，看看这个 $5$ 能产生多少贡献。

设这个 $5$ 及其前的 $5$ 共有 $k$ 个，这个 $5$ 在数列中的第 $i$ 个。例如数列 $5$ $5$ $5$。第一个的贡献是 $1$，第二个的贡献是 $2+1$，第三个的贡献是 $3+2+1$。
和就是 $3 \times 1 + 2 \times 2 + 1\times 3$。

所以这个点如果是 $5$，他的贡献是 $k \times (i-k+1)+f(k)$。这里 $f(k)$ 表示 从 $1$ 加到 $k-1$ 的和。

### 代码

详细版：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,m,a[200005],ans[200005],li=1;//li代表这个数及其前的连通的5数量
int f(int k){
	return (k-1)*k/2;//求和公式
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]==5)ans[i]=(i-li+1)*li+f(li),li++;//相连的5数量增加1
		if(a[i]!=5)li=1;//相连的5没了，恢复成只有1个
	}
	for(int i=1;i<=n;i++){
		m+=ans[i];
		m%=mod;//记得取余
	}
	cout<<m;
	return 0;
}
```

压行版：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,m,a[200005],ans[200005],li=1;
int f(int k){return (k-1)*k/2;}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==5)m+=((i-li+1)*li+f(li))%mod,li++;
		else li=1;
	}cout<<m%mod;
	return 0;
}
```

### 具体说明

公式的推导：

不在这个数后面的且不与其联通的 $5$ 有 $i-k+1$ 个。

这些数的所有按要求的选法就是他们的个数。

每个选法的贡献就是不在这个数后面的且与其联通的 $5$ 的数量。

所以总贡献就是他们的乘积。

加上 $f(k)$ 的原因是我们不一定选的数的数量比 $k$ 多。

并且选的数的数量不比 $k$ 多的选法只有 $f(k)$ 种。

即为选 $1$ 个，$2$ 个，$3$ 个 …… 一直选到 $k-1$ 个的加和。

---

## 作者：二叉苹果树 (赞：1)

题目中 $n \leq 2 \times 10^5$，故 $\mathcal{O} \left( n ^ 2 \right)$ 暴力处理显然不行。

我们用 $s_r$ 表示以 $a_r$ 结尾的最长连续 $5$ 的序列长度。

$$\displaystyle \sum_{l = 1}^{r}f \left(l, r\right) = s_r \cdot r - \dfrac{s_r \cdot s_{r - 1}}{2}$$

我们可以考虑 $a_r$ 对每个 $f \left(l, r\right)$ 的贡献均为 $s_r$，即有总贡献为 $s_r \cdot r$。除了对以 $l$ 升序的最后 $s_r - 1$ 个 $f \left(l, r\right)$ 的贡献依次减少 $1$，那么减去 $\dfrac{s_r \cdot s_{r - 1}}{2}$，得到上式。

这样我们就在 $\mathcal{O} \left( n\right)$ 的时间复杂度下解决了本题。

```cpp
#include <iostream>
#define maxn 200010
#define mod 1000000007
int n, a[maxn];
long long s[maxn];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 5)
            s[i] = s[i - 1] + 1;
        else
            s[i] = 0;
        if (s[i]!=0)
            ans = (ans + ((s[i] * i) - ((s[i] * (s[i] - 1))/ 2)) % mod) % mod;
    }
    std::cout << ans << std::endl;
    return 0;
}
```


---

## 作者：tallnut (赞：0)

# step 1
## 核心思想
我们采用类似于动态规划的算法求出 $f_ {i}$（表示以第 $i$ 个元素为结尾的前缀数组中的最长全五后缀长度）。
## 例子
如果上面说的太抽象的话，看以下两个例子：

1、对于数组
$$[1,1,4,5,1,4]$$
$f _ {i}$ 的值分别为：
$$[0,0,0,1,0,0]$$
2、对于数组
$$[4,5,5,6,5,5,5,7]$$
$f _ {i}$ 的值分别为：
$$[0,1,2,0,1,2,3,0]$$
## 求值具体过程
如果 $a _ {i} = 5$ 则：
$$f _ {i} = f _ {i - 1} + 1$$
表示在前面一项的长度上 $+1$。

否则：
$$f _ {i} = 0$$
很好理解，结尾都不是 $5$ 了当然是 $0$。
## 此部分代码
```
if (a[i] == 5) f[i] = f[i - 1] + 1;
else f[i] = 0;
```
## 时间复杂度
显然为 $\Theta (n)$。
# step 2
## 分析
我们记 $l$ 为 $r - f _ {r} + 1$（其中 $r$ 为枚举的区间结束点）。

（也就是说，区间 $[l,r]$ 为一个长度为 $f _ {r}$，结尾元素为第 $r$ 个元素的区间。）

那么对于 $1 \le i \le l$，因为区间足够大，区间 $[i,r]$ 的值均为 $f _ {r}$。

然后考虑 $l < i \le r$ 的情况，该部分的值从 $(f _ {r} - 1) \sim 1$ 依次减少，用数学语言表达为：
$$1 + 2 + \cdots + (f _ {r} - 1)$$
直接套等差数列公式，这一部分值为
$$\dfrac {f _ {r} \times (f _ {r} - 1)} {2}$$
## 代码
```
for (int r = 1;r <= n;r++)
{
	tmpl = r - f[r] + 1;
	ans += f[r] * tmpl + f[r] * (f[r] - 1) / 2;
	ans %= mod;
}
```
## 时间复杂度
显然仍为 $\Theta (n)$。
# 综合时间复杂度
$\Theta (n) + \Theta (n) = \Theta (n)$。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/127854669)，最长时间的一点也只跑了 21ms。
```
#include <iostream>
using namespace std;
const int N = 2e5 + 1,mod = 1e9 + 7;
long long n,ans,tmpl,tmp;
long long a[N],f[N];
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if (a[i] == 5) f[i] = f[i - 1] + 1;
		else f[i] = 0;
	}
	for (int r = 1;r <= n;r++)
	{
		tmpl = r - f[r] + 1;
		ans += f[r] * tmpl + f[r] * (f[r] - 1) / 2;
		ans %= mod;
	}
	cout << ans;
}
```

---

## 作者：sbno333 (赞：0)

我们记 $c_i$ 为 $$\Big(\sum\limits_{k=1}^{i} f(1,k)\Big) \bmod 10^9+7$$。

不难推出答案为 $$\Big(\sum\limits_{k=1}^{n} c_k\Big) \bmod 10^9+7$$。

对于 $a_i\not=5$，$c_i=0$。

对于 $a_i=5$，$c_i=c_{i-1}+i$，证明如下：

对于以 $i-1$ 为结尾的数，它们末尾 $5$ 的和为 $c_{i-1}$，在 $i-1$ 个数末尾都增加 $a_i=5$，此时答案为 $c_{i-1}+i-1$，加上以 $a_i=5$ 为结尾的数，即 $f(i,i)$，为 $1$，此时答案为 $c_{i-1}+i$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long mo=1e9+7;
long long a[1000009];
long long c[1000009];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]==5){
			c[i]=c[i-1]+i;
			c[i]%=mo;
		}
	}
	long long ans;
	ans=0;
	for(int i=1;i<=n;i++){
		ans+=c[i];
		ans%=mo;
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Vct14 (赞：0)

简化题意：给定数组 $a$，求满足 $1\leqslant l\leqslant r\leqslant n$ 的所有区间 $[l,r]$ 中末尾连续 $5$ 的数量之和。

我们定义 $N$ 表示当前末尾连续 $5$ 的个数，$s$ 为题目求的答案，然后遍历 $r$ 即可。

若当前 $a_r\ne5$，则直接跳过，不过 $N$ 要清零。

若 $a_r=5$，则 $N\gets N+1$，然后计算以每一个满足 $1\leqslant l\leqslant r$ 的 $l$，增加 $[l,r]$ 区间内 $5$ 的数量：

- 对于所有满足 $r-N+1\leqslant l\leqslant r$，即满足 $a_l=5$ 的 $l$，$[l,r]$ 区间内 $5$ 的数量只有 $r-l+1$ 个。此时所有 $l$ 的贡献之和为 $\sum\limits^{r}_{l=r-N+1}r-l+1=N+(N-1)+\cdots+1=\dfrac{N(N+1)}{2}$。
- 而对于所有满足 $1\leqslant l\leqslant r-N$ 的 $l$，$[l,r]$ 区间内 $5$ 的数量就都有 $N$ 个。贡献之和为 $N(r-N)$。

因此对于每一个 $r$，增加的贡献为 $\dfrac{N(N+1)}{2}+N(r-N)$。

因为计算与之前输入的 $a$ 无关，所以我们不需要存 $a$ 数组。

```c++
#include<bits/stdc++.h>
using namespace std;

const int M=1000000007;

int main(){
	int n;
	cin>>n;
	long long s=0,N=0;
	for(int r=1; r<=n; r++){
		int a;
		cin>>a;
		if(a!=5){
			N=0;
			continue;
		}
		N++;
		s=(s+(N*(N+1)/2%M+(r-N)*N%M)%M)%M;
	}
	cout<<s%M;
	return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9710)

一种看起来似乎是 $n^2$ 的做法，但是不知道是不是，过了但不太清楚时间复杂度。

我们可以对于每个 `5` 计算其的贡献。

先处理出每块连续的 `5` 的区间长度，接下来我们用一重循环枚举前 $j$ 个 `5` 的贡献和第 $j$ 个 `5` 在 `5` 的区间内与前面的 `5` 结合起来的贡献。第一个明显是 $(i-s)\times j$，第二个是 $\sum_{i=1}^{j-1}$，等差数列求和为 $j\times (j-1) \div 2$。
# CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200010];
long long ans=0;
const long long mod=1e9+7;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
	long long s=0;
	for(register long long i=1;i<=n+1;i++)
	{
		if(a[i]!=5)
		{
			for(register long long j=1;j<=s;j++)
				ans+=(i-s)*j,ans%=mod,ans+=(j-1)*j/2,ans%=mod;
			s=0;
		}
		else s++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：哈哈人生 (赞：0)

## 思路
这道题如果用暴力，枚举左端点和右端点再计算，时间复杂度是立方的，肯定过不去。我们不如倒过来想，如果有一段连续的 $5$，左端点和右端点分别为 $l$ 和 $r$，对答案 $ans$ 的贡献为多少？

设这段 $5$ 的长度为 $cd$，则 $cd=l-r+1$。而 $1$ 到 $cd$ 个连续的 $5$ 对答案都有贡献，需要都枚举（我们把它设为 $i$），现在就需要思考：有多少个区间的末尾连续有 $i$ 个 $5$ 呢？因为题目要求的是末尾连续的 $5$，则区间的右端点的情况是 $cd-(j-1)-1$，而左端点有 $l$ 种情况（$1$ 到 $l$）吗，所以区间的末尾连续有 $i$ 个 $5$ 的区间个数为 $1\times l+cd-(j-1)-1$，实现请看代码。

## 代码
非常简单。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a[1000005];
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	int ans=0,l=-1,r,la=1;
	for(int i=1; i<=n; i++) {
		if(a[i]==5) {
			if(l==-1)l=i,r=i;
			else r++;
		} else {
			if(l==-1)continue;
			int cd=(r-l+1);
			for(int j=1; j<=cd; j++) {
				ans+=(cd-(j-1)-1)*j;
				ans+=(l-la+1)*j;
				ans%=mod;
			}
			l=-1;
		}
	}
	if(l!=-1) {
		int cd=(r-l+1);
		for(int i=1; i<=cd; i++) {
			ans+=(cd-(i-1)-1)*i;
			ans+=(l-la+1)*i;
			ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```
点个赞把。

---

## 作者：ICU152_lowa_IS8 (赞：0)

一道基础题，虽然算法标签里是递推，但是作者使用的是一种类似于找规律的方法。

记从第 $i$ 个数（包含第 $i$ 个数）往前的 $5$ 的数量为 $s_i$，则有：

$$s_i=\begin{cases}
s_{i-1}+1 &a_i=5\\

0&\text{otherwise.}

\end{cases}
$$

然后从 $1$ 到 $n$ 遍历一遍，显然如果 $a_i$ 不为 $5$ 的话，$\sum_{j=1}^{n} f(j,i)$ 的值为 $0$。

否则，分类讨论一下：

一个数字 $114514555$，当 $i$ 指向最后一个 $5$ 时，显然在连续的三个 $5$ 之前的 $114514$ 可以与后面的三个 $5$ 构成 $6\times3=18$ 对答案的贡献，而后面的三个 $5$ 可以构成 $\dfrac{(1+3)\times3}{2}=6$ 对答案的贡献，共计 $18+6=24$ 个对答案的贡献。

从上面这个例子中不难总结出规律（$a_i$ 不为 $5$ 时也没关系，计算出来的值是 $0$）：

$$\sum_{j=1}^{i}f(j,i)=(i-s_i)\times s_i+\dfrac{(1+s_i)\times s_i}{2}$$

即：

$$\sum_{l=1}^{n}\sum_{r=l}^{n}f(l,r)=\sum_{i=1}^{n}\sum_{j=1}^{i}f(j,i)=\sum_{i=1}^{n}(i-s_i)\times s_i+\dfrac{(1+s_i)\times s_i}{2}$$
可以多去想一想，在纸上画一画，是可以自己推出来的。

根据上面的式子，把整个数组遍历一遍，统计答案再取个模即可。

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
int s[200005];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==5){
			s[i]=s[i-1]+1;
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]==5){
			ans+=(i-s[i])*s[i];
			ans%=1000000007;
			ans+=(1+s[i])*s[i]/2;
			ans%=1000000007;
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：UncleSam_Died (赞：0)

### 题意简述
有一个长度为 $n$ 的序列 $a$，求对于每一个 $a_l\sim a_r (1\leq l,r\leq n)$，其中从 $a_r$ 开始的连续的 $5$ 的个数（向前找）之和。

### 思路
我们发现会出现没有 $5$ 的情况，这个时候直接输出 $0$ 就可以了。但是正解思路显然不是这个。

因为 $n\leq 2\times 10^5$ ，所以自然不能 $O(n^2)$ 暴力统计。显然，答案为 $\Sigma_i^{cnt} (pos_i\times len_i+sum_i)$，其中 $cnt$ 为连续的 $5$ 的块数，$len_i$ 为每个连续的 $5$ 的块的长度，$pos_i$ 表示当前块的起始位置，$sum_i$ 表示 $\Sigma_j^{len_i} j\times (len_i - j + 1)$。

那么根据这个公式，我们就很容易得到如下的两个代码：

第一部分，计算 $\Sigma_i^{cnt} (pos_i\times len_i)$。
```cpp
for(int i=1;i<=n+1;i++){//遍历到n+1，可以统计最后一个5的块 
	if(a[i]==5)//如果当前的ai为5，那么更新长度 
		f[i]=f[i-1]+1;
	else f[i]=0;//如果不是的话，就一直为0 
	if(a[i]==5&&a[i-1]!=5)//如果这是一个块的起点，那么更新起始点的位置（第一个不为5的点） 
		lst=i-1;
	if(a[i]!=5&&a[i-1]==5){//如果这是一个块的结束，那么计算答案 
		len[++ce]=f[i-1];//统计长度 
		ans+=lst*(((len[ce]+1)*len[ce]/2)%Mode)%Mode;//根据公式计算答案 
		ans%=Mode;//取模 
	}
}
```
第二部分，计算 $\Sigma_i^{cnt}\Sigma_j^{len_i} j\times (len_i - j + 1)$。
```cpp
for(int i=1;i<=ce;i++){
	for(int j=1;j<=len[i];j++){
		ans+=j*(len[i]-j+1);//根据公式计算如果l在块内部的答案 
		ans%=Mode;//取模 
	}
	ans%=Mode;//还是取模 
//		cout<<len[i]<<" ";
}
```
### AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull usigned long long
using namespace std;
const string TypideName="c";
inline void readc(char &c){
	c=getchar();
	while(c==' '||c=='\n')
		c=getchar();
}inline void writec(char c){putchar(c);}
template<typename T>inline void read(T& x) {
	if(typeid(x).name()==TypideName){char ch;readc(ch);x=ch;return;}
	x = 0; bool f = false; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = !f; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x = (f ? -x : x); return;
}template<typename T>inline void put(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) put(x / 10);
	putchar(x % 10 + '0'); return;
}template<typename T>inline void write(T x) {
	if(typeid(x).name()==TypideName){writec(x);return;}
	put(x);
}
template<typename T,typename... Args>
inline void read(T& x,Args&...x_) {read(x),read(x_...);}
template<typename T,typename... Args>
inline void write(T x,Args...x_){write(x),write(x_...);}
#define N 200005
#define int ll
#define Mode 1000000007
int n,a[N],maxt=-1;
int f[N],len[N],ce,lst;ll ans=0;
inline void work(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),
		maxt=max(maxt,a[i]);
	for(int i=1;i<=n+1;i++){//遍历到n+1，可以统计最后一个5的块 
		if(a[i]==5)//如果当前的ai为5，那么更新长度 
			f[i]=f[i-1]+1;
		else f[i]=0;//如果不是的话，就一直为0 
		if(a[i]==5&&a[i-1]!=5)//如果这是一个块的起点，那么更新起始点的位置（第一个不为5的点） 
			lst=i-1;
		if(a[i]!=5&&a[i-1]==5){//如果这是一个块的结束，那么计算答案 
			len[++ce]=f[i-1];//统计长度 
			ans+=lst*(((len[ce]+1)*len[ce]/2)%Mode)%Mode;//根据公式计算答案 
			ans%=Mode;//取模 
		}
	}
	for(int i=1;i<=ce;i++){
		for(int j=1;j<=len[i];j++){
			ans+=j*(len[i]-j+1);//根据公式计算如果l在块内部的答案 
			ans%=Mode;//取模 
		}
		ans%=Mode;//还是取模 
	}
	write(ans);
}
signed main(){
	work();
	return 0;
}
```


---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/P9710)

## 题意

给定一个长度为 $n$ 的数列，保证每一项都满足 $a_i \in [0,9]$。定义 $f(i,j)$ 代表 $[l,r]$ 区间内末尾 $5$ 的个数，请求出：$(\sum_{l=1}^{n}\sum_{r=l}^{n}f(l,r)) \bmod (10^9 + 7)$。

## 思路

预处理出以每一个 $f(1,i)$，然后就可以 $O(1)$ 求出 $\sum_{i=1}^{r} f(i,r)$ 了。**记得取模**

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 5, P = 1e9 + 7;

LL n, ans, a[kMaxN], s[kMaxN];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    s[i] = (a[i] == 5 ? s[i - 1] + 1 : 0), s[i] %= P;
  }
  for (int i = 1; i <= n; i++) {
    ans += ((s[i] * (s[i] + 1)) >> 1), ans %= P;
    if (i > s[i]) {
      ans += (i - s[i]) * s[i], ans %= P;
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

