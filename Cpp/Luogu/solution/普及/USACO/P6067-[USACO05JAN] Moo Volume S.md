# [USACO05JAN] Moo Volume S

## 题目描述

Farmer John 的农场上有 $N$ 头奶牛（$1 \leq N \leq 10^5$），第 $i$ 头奶牛的位置为 $x_i$（$0 \leq x_i \leq 10^9$）。

奶牛很健谈，每头奶牛都和其他 $N-1$ 头奶牛聊天。第 $i$ 头奶牛和第 $j$ 头奶牛聊天时，音量为 $|x_i-x_j|$。

请您求出所有奶牛聊天音量的总和。

## 说明/提示

- 子任务 1（原测试数据，1 分）：$N \leq 10^4$；
- 子任务 2（99 分）：无特殊限制。

## 样例 #1

### 输入

```
5
1
5
3
2
4```

### 输出

```
40```

# 题解

## 作者：_ouhsnaijgnat_ (赞：19)

[题目传送门](https://www.luogu.com.cn/problem/P6067)

## 思路

拿到这个题，没看 $n$ 我就知道不能用暴力，看样子不能 $O(n^2)$。

首先，我们可以把题简化一下，第 $i$ 头牛和 $j$ 头牛音量只需要 $\mid x_{i}-x_{j}\mid$，因为有绝对值，$\mid x_{i}-x_{j}\mid$ 跟 $\mid x_{j}-x_{i}\mid$ 是一样的，所以最后只需乘 $2$ 即可。

于是，我们枚举第 $i$ 头奶牛，算出它与第 $1 \backsim i-1$ 头奶牛谈话的总音量。

咱们再看看这个算第 $i$ 头奶牛总音量的式子。

$(a_{i}-a_{i-1})+(a_{i}-a_{i-2})+...+(a_{i}-a_{1})$

我们把括号拆开。

$a_{i}-a_{i-1}+a_{i}-a_{i-2}+...+a_{i}-a_{1}$

这里一共有 $i-1$ 个 $a_{i}$，于是，我们可以把这个式子简化。

$a_{i}*(i-1)-a_{i-1}-a_{i-2}-...-a_{1}$

我们把 $a_{i-1}-a_{i-2}-...a_{1}$ 用前缀和存，这样时间复杂度并不会爆。

注意：这种方法必须有序，否则不能变成我们简化后的式子。

话不多说，直接上代码。

## 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
long long ans,a[1000005],n,sum[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];//前缀和 
	}
	for(int i=n;i>=1;i--){
		ans=ans+labs(sum[i-1]-a[i]*(i-1));//简化后的式子 
	}
	cout<<ans*2;//把少计算的补回来 
	return 0;
} 
```


---

## 作者：wuyonghuming (赞：3)

### 解题思路:
为了减少计算量，先将 $x$ 升序排序

用一个数组来把这个位置的牛和位置比它小的所有牛的聊天的音量的和用一个数组表示出来。
### 计算理由:
我们现在先用 $s$ 来表示这个数组，数组$x$表示所有牛的位置。

用$s_1$表示第一项，用$s_2$表示第二项，用$s_3$表示第三项......

$s_1$：$0$

$s_2$：$x_2-x_1$

$s_3$：$x_3-x_1+x_3-x_2$

$s_4$：$x_4-x_1+x_4-x_2+x_4-x_3$

$......$

不过从$s_3$开始，每一项都可以化简

因为算出了$s_2$,$s_3$就可算出来了

首先我们先不算上$s_i$和$s_1$,$s_i$和$s_2$,$s_i$和$s_3$,$s_i$和$s_4......$的差的和

那么$s_i=s_{i-1}+x_i-x_{i-1}$

如果加上$s_i$和$s_1$,$s_i$和$s_2$,$s_i$和$s_3$,$s_i$和$s_4......$的差的和

那么就是$s_i=s_{i-1}+(x_i-x_{i-1})(i-1)$
### 递推公式：
## $s_i=s_{i-1}+(x_i-x_{i-1})(i-1)$
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long s[100001],ans=0,n,x[100001];//x要用long long
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x[i]);
	sort(x+1,x+n+1);//升序排序
	memset(s,0,sizeof(0));//清零
	for(int i=2;i<=n;i++)
	{
		s[i]=s[i-1]+(x[i]-x[i-1])*(i-1);//递推公式
		ans+=s[i];//答案是它们的和的两倍
	}
	printf("%lld",ans*2);//答案要乘2输出
	return 0;
}
```


---

## 作者：_lmz_ (赞：3)

## Part 1 枚举做法 
双层循环枚举每两头牛，最后求和，时间复杂度 $O(n^2)$，可以过子任务 1，但是只能过 1。
## Part 2 优化
我们可以发现，音量总和为：
$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}|a_i-a_j|(i \neq j)$$
我们把式子拆开来看，第 $i$ 头牛的音量为：
$$\sum\limits_{j=1}^{n}|a_i-a_j|(i \neq j)$$
我们还可以发现一个简单的结论：
$$|a-b|=|b-a|$$
所以我们可以化简刚才的那个式子：
$$\sum\limits_{j=1}^{i}|a_i-a_j|(i \neq j) \times 2$$
再把这个式子拆分来，就得到了：
$$|a_i-a_{i-1}|+|a_i-a_{i-2}|+|a_i-a_{i-3}|+…+|a_i-a_1|$$
这个式子大家可能看不出什么来，但是我们可以把这个式子再提取公因数：
$$a_i \times (i-1)-\sum\limits_{j=1}^{i-1}a_j$$
这样大家可能就可以看出来了，这个式子看上去是 $O(n)$ 的时间复杂度，但是我们可以预处理把 $a$ 数组的前缀和求助来，这样的话这个式子的时间复杂度就可以缩减到 $O(1)$。

但是我们不要忘了，这个式子是基于除以 $2$ 的基础上，所以我们最后还需要把结果 $\times 2$。

**注意：因为这种做法需要数组的单调性，所以我们需要先把 a 数组排序。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=1e6;
int n,a[maxn],sum[maxn];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i]*(i-1)-labs(sum[i-1]);
	}
	cout<<ans*2;//刚才说过了，这里的结果要除以2
	return 0;
}
```

---

## 作者：EDqwq (赞：2)

#### 一道简单的推柿子题

***

首先，针对subtask1，我们可以考虑$O(n ^ 2)$暴力，对于$n = 10000$是可以过的，但是只能拿一分。

考虑如何优化。

对于两个同样的数，不同的顺序，因为绝对值的存在，我们无需算两次，只需算其中一个，然后最后乘2即可。

所以我们需要排序，sort一遍。

但是这个时间复杂度还是过不了。

***

继续考虑优化。

我们排序之后（从大到小），对于每一个位置的数，只需算它前面与它的值即可，最后乘2。

我们发现，单一一个值为：

$$(a_i - a_j)$$

对于所有的i前面的j来说，和为：

$$(a_i - a_1)+(a_i-a_2)+...+(a_i-a_{i-1})$$

拆括号化简得：

$$a_i \times (i - 1) - (a_1 + a_2 + ... + a_{i - 1})$$

对于前面的部分，我们直接乘即可。对于后面的部分，我们可以用一个前缀和维护。

最后记得对答案乘2并且取绝对值即可，当然你也可以直接在算的时候取绝对值。

于是这道题便迎刃而解。

***


### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n;
int a[100010];
int pre[100010];
int ans;

bool cmp(int x,int y){
	return x > y;
} 

signed main(){
	cin>>n;
	for(int i = 1;i <= n;i ++)a[i] = read();
	sort(a + 1,a + n + 1,cmp);
	for(int i = 1;i <= n;i ++)pre[i] = pre[i - 1] + a[i];
	for(int i = 1;i <= n;i ++)ans += a[i] * (i - 1) - pre[i - 1];
	cout<<abs(ans * 2);
	return 0;
}
```

---

## 作者：sto_OwenLMZ2022_orz (赞：1)

## Part 1 枚举做法
这种做法非常简单，双层循环枚举 $i,j$，时间复杂度 $O(n^2)$。

期望得分 $1$ 分。
## Part 2 前缀和优化
我们先看看题目的数学表达方式：
$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}|a_i-a_j|(i\neq j)$$
我们只看第二层：
$$\sum\limits_{j=1}^{n}|a_i-a_j|(i\neq j)$$
然后把求和符号展开：
$$|a_i-a_n|+|a_i-a_{n-1}|+|a_i-a_{n-2}|+...+|a_i-a_1|$$
化简，得：
$$(i-1) \times a_i-\sum\limits_{j=1}^{i}|a_i-a_j| \times 2$$
后面用前缀和求，单个时间复杂度 $O(1)$。

总共时间复杂度 $O(n)$。

~~不包含 sort 时间.~~

---

## 作者：Kalium (赞：1)

# P6067 [USACO05JAN]Moo Volume S题解

## 题意：

没啥简化的，[传送门](https://www.luogu.com.cn/problem/P6067)。

## 思路：

小学数学题。

暴力可解决，但是要 $O(n^2)$，恭喜你能拿到 1 分的高分。

考虑优化。

我们枚举下，$n = 4$ 的情况。

$(a_1 - a_2) + (a_1 - a_3) + (a_1 - a_4)$。

$(a_2 - a_1) + (a_2 - a_3) + (a_2 - a_4)$。

$(a_3 - a_1) + (a_3 - a_2) + (a_3 - a_4)$。

$(a_4 - a_1) + (a_4 - a_2) + (a_4 - a_3)$。

全部相加后我们得到 $2((a_4 - a_3 + a_4 - a_2 + a_4 - a_1) + (a_3 - a_2 + a_3 - a_1) + (a_2 - a_1))$。

这个式子化简下还是可以很容易得出：

$2((a_4 * 3 - (a_1 + a_2 + a_3)) + (a_3 * 2 - (a_1 + a_2)) + (a_2 * 1 - a_1))$。

那么我们类比下，若是换成 i 的话，他是不是就有可能是：

$a_i * (i - 1) - \sum\limits_{j = 1}^{i-1}{a_j}$。

后面这东西前缀和，前面这玩意暴力草。

复杂度 $O(n)$。

## 细节：

注意 long long。

## 代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio> 
#include <algorithm> 
#include <cmath>

#define ll long long

const int N = 1e5 + 7;

using namespace std;

int n;

ll a[N], pre[N];

ll ans;

inline bool cmp(ll x, ll y) {
	return x < y;
}

int main() {
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i ++)
		scanf("%lld", &a[i]);
	
	sort(a + 1, a + 1 + n, cmp);
	
	for (int i = 1; i <= n; i ++) 
		pre[i] = pre[i - 1] + a[i];
	
	for (int i = 1; i <= n; i ++) 
		ans += a[i] * (i - 1) - pre[i - 1];
	
	printf("%lld\n", abs(ans) << 1);
	
	return 0;
}
```

$Atlantis.$

---

## 作者：Hexarhy (赞：1)

简单易上手的结论题。新手推也很容易就出来了，难度大约为CSP-J T2。

不过我的解法跟另一篇题解很不一样呢。

---------

### 解题思路

**算法一**

枚举 $a_i$ 和 $a_j$ 直接暴力计算。时间复杂度 $O(n^2)$。

可以过 subtask 0。

**算法二**

显然需要优化。

由于两两之间都有贡献，顺序对贡献不造成影响，因此考虑按升序**排序**。

排序完之后，用什么快速计算差值呢？**前缀和**，其数列记为 $s$。

接下来就简单的推一下。

计算贡献时，题面要求的“两两之间”是**单向**的，因此答案要 $\times 2$。

那么下面**只需考虑比 $a_i$ 大的数**即可。

对于当前枚举到的 $a_i$，根据题意增加的贡献为：

$$(a_n-a_i)+(a_{n-1}-a_i)+\cdots+(a_{i+1}-a_i)$$

化简并合并同类项得：

$$(a_n+a_{n-1}+\cdots+a_{i+1})-(n-i)a_i$$

前面括号里那一串，可以用前缀和表示为 $s_n-s_i$。那么原式等于

$$s_n-s_i+(n-i)a_i$$

至此，答案就出来了。

预处理前缀和得到 $s$，再枚举一遍 $a_i$，时间复杂度为 $O(n)$。

然而，由于使用了排序`sort()`，实际复杂度应为 $O(n\log n)$。但已经可以通过本题。

不过我们已经知道 $a_i$ 的值域，可以用基数排序进一步优化，使时间更接近线性。

-------------

### 实现细节

- 题面已声明答案开`long long`，前缀和数组 $s$ 也要开。

- 再提醒一遍，答案最后还要乘以二，因为我们只计算了比 $a_i$ 大的数。

------------

### 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int n;
ll a[MAXN],s[MAXN];
ll ans;

void input(void)
{
	cin>>n;
	for(int i=1;i<=n;i++)
	 cin>>a[i];
}

void solve(void)
{
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	 s[i]=s[i-1]+a[i];//求出前缀和
	for(int i=1;i<=n;i++)
	 ans=ans+(s[n]-s[i]-(n-i)*a[i]);//根据式子计算
	ans*=2;//最后乘2
}

int main()
{
	input();
	solve();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：郑朝曦zzx (赞：1)

# 一 解题思路
~~不想进行数学推导的同学看这篇题解。~~
## 一分解法
很显然，如果只想得一分可以使用平方级别的算法完成。

第一步：排序，从大到小排序。

第二步两层循环求解，并加出总答案。
## 考虑优化——线段树/前缀和优化
线段树支持**区间求和**，在排好序后，计算每头牛和声音比它小的牛制造的噪音总和，把每头牛产生的噪音总和加在一起就可以了。

注意：两头牛说话的噪音**要算两遍**，不然样例都过不了。

# 二 参考代码
已经有很多前缀和题解了，发个线段树的。
```cpp
#include <cstdio>
#include <algorithm>
#define ls (pos << 1)
#define rs (ls | 1)
#define maxn 100010
#define ll long long
using namespace std;
ll ans, sum[maxn << 2];
int n, ql, qr;
int num[maxn];
bool cmp(int x, int y) { return x > y; }
void build(int l, int r, int pos)
{
	if (l == r)
	{
		sum[pos] = num[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ls);
	build(mid + 1, r, rs);
	sum[pos] = sum[ls] + sum[rs];
}
ll query(int l, int r, int pos)
{
	if (ql <= l && qr >= r) return sum[pos];
	int mid = (l + r) >> 1;
	ll now = 0;
	if (ql <= mid) now += query(l, mid, ls);
	if (qr > mid) now += query(mid + 1, r, rs);
	return now;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &num[i]);
	sort(num + 1, num + n + 1, cmp);
	build(1, n, 1);
	for (int i = 1; i < n; ++i)
	{
		ql = i + 1, qr = n;
		ll add = (ll)num[i] * (n - i) - query(1, n, 1);
		ans += add;
	}
	printf("%lld\n", ans * 2);
	return 0;
}
```


---

## 作者：lmy_2011 (赞：0)

## 基本做法：
首先这道题有一个很朴素的做法，就是双重循环，通过一个计数器  $sum$  统计第 $i$ 头牛与第 $j$ 头牛的音量。
但是数据范围中 $n$ 最大可以到达 $10^5$，双重循环的时间复杂度是  $O(n^2)$，所以时间就是 $10^5\times10^5=10^{10}$，这明显会超时。

## 优化做法：
题目中说每头牛要与 $n-1$ 头牛谈话：
1. 我们可以先算每头牛"前面的"牛与他谈话的音量，再在结果上乘上二，即可求出正确答案
2. 每头牛与"前面的"每头牛的谈话音量为： $\left\vert x_i-x_j\right\vert+\left\vert x_i-x_{j-1}\right\vert+\left\vert x_i-x_{j-2}\right\vert\cdots\left\vert x_i-x_{1}\right\vert$，在此公式中，有一个共同的数： $x_i$， 然后一头牛不可能跟自己谈话，而且我们只算他"前面的"，所以我们得到公式： $x_i\times(i-1)$ 。
3. 最后，我们只需要通过一个前缀和数组来存 $i$ 头牛已知的音量。


小细节：
1. 前缀和需要有序，所以我们得排序
2. 倒序循环，算每一头牛与他"前面的"牛的音量。

最后上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[100005],sum[100005],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i];
	sort(x+1,x+1+n);//排序
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+x[i];//前缀和公式
	for(int i=n;i>=1;i--)//倒序枚举，注意需要取绝对值，只算每头奶牛"前面的"
		ans+=abs(sum[i-1]-x[i]*(i-1));
	cout<<ans*2;//我们只算了一半，所以要乘回来
	return 0;
}
```




---

## 作者：miao5 (赞：0)

这道题就是推式子的题。

我们用 $a$ 表示奶牛的位置，用 $s$ 表示某个位置的牛和位置比它小的所有牛的聊天的音量的和， $si$ 表示第 $i$ 项。
我们推一下式子：

$s_1=0$

$s_2=a_2-a_1$

$s_3=a_3-a_1+a_3-a_2$

$s_4=x_4-x_1+a_4-a_2+a_4-a_3$

我们可以发现 $s_i=s_{i-1}+(a_i-a_{i-1})\times(i-1)$

$ans=\sum_{i=1}^ns_i \times2$


```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long s[100005],ans=0,n,a[100005];
int main(){
	cin>>n; 
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++){
		s[i]=s[i-1]+(a[i]-a[i-1])*(i-1);
		ans+=s[i];
	}
	cout<<ans*2;
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：0)

考虑如何优化暴力计算：最容易想到的是，对于两个数 $a_i$ 和 $a_j$ ，只需计算 $|a_i-a_j|$ ，然后再乘以 $2$ 就是这两个数产生的音量。但是算法还是 $O(n^2)$ 的qaq

根据以上内容，对于某头牛，只需计算它与比它音量小的牛产生的音量即可。首先进行排序，对于第 $i$ 头牛，产生音量为

$|a_i-a_1|+|a_i-a_2|+...+|a_i-a_{i-1}|$

由于已经排好序了，因此 $a_1\leq a_2\leq...\leq a_i$ ，

所以可以直接脱去绝对值得到

$a_i-a_1+a_i-a_2+...+a_i-a_{i-1}$

$=a_i*(i-1)-\sum_{j=1}^{i-1}a_j$

至此算法已经很明显了，排序后求出前缀和，$O(n)$ 计算即可。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
inline long long read()
{
	long long s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if (c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c&15),c=getchar();
	return s*b;
}
long long n,ans,i,a[N],s[N];//不开ll见祖宗
int main()
{
	n=read();
	for(i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);//排序
	for(i=1;i<=n;i++) s[i]=s[i-1]+a[i];//前缀和
	for(i=1;i<=n;i++) ans+=a[i]*(i-1)-s[i-1];//统计答案啊
	printf("%lld",ans*2);//注意，由于我们只统计了大减小的情况，所以ans要乘以2
	return 0; 
}

```


---

## 作者：peppaking8 (赞：0)

## 思路：
首先，由于 $|a_i-a_j|=|a_j-a_i|$，所以 $i,j$ 的对话有两遍，故只需要求
$$\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n |a_i-a_j|$$
然后把答案乘 $2$ 即可。因为有绝对值，比较麻烦，所以我们考虑**排序**。

将 $a_i$ 从小到大排序后，原式就是：
$$\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n (a_j-a_i)$$
将其全部拆开，并考虑系数，得原式等于
$$-(n-1)a_1-(n-3)a_2-...+(n-3)a_{n-1}+(n-1)a_n$$
所以写代码就很简单了。每次记录一个系数 ```tot```，初始化为 $-n+1$，每次累加完后 ```tot+2```。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int n;
int a[N];
int ans=0,tot;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);//从小到大排序
	tot=-n+1;//初始化tot，思路里说了
	for(int i=1;i<=n;i++){
		ans+=a[i]*tot;//累加
		tot+=2;//tot累加
	}
	printf("%lld\n",ans*2);//答案的两倍
}
```

---

## 作者：lyhqwq (赞：0)

### 简化题意

给定一个序列 { $A_n$ } ,求 $\sum_{i=1,j=1}^n \mid A_i-A_j \mid$

### 思路

对于每个 $A_i$ ，他的贡献为 
$(A_i-A_1)+(A_i-A_2)+\cdots +(A_i-A_{i-1})$

拆开后是 $A_i \times (i-1)-\sum_{j=1}^{i-1}A_j$

前缀和维护即可，记得开longlong

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll n,a[100005],sum[100005],ans;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++){
		ans+=a[i]*(i-1)-sum[i-1];
	}
	printf("%lld",abs(ans*2));
	return 0;
} 
```


---

## 作者：happybob (赞：0)

## 题意

给定一个 $n$ 个元素的序列 $a$，求出 $(\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \lvert a_j-a_i \rvert ) \times 2$。

## 解法

我有一个独特的方法。

首先 $O(n^2)$ 明显只能过任务 $0$，并且只能得 $1$ 分，那么我们考虑式子中 $\sum_{j=i+1}^{n} \lvert a_j-a_i \rvert$  的特性，第一个想法是 $\sum_{j=i+1}^{n} \lvert a_j-a_i \rvert = (\sum_{j=i+1}^n a_j) - [(n-i) \times a_i]$，但是明显需要排序。

那么排序完后大家都是拆式子，但是我们可以看出 $(\sum_{j=i+1}^n a_j)$ 可以线段树维护，所以排序 $O(n \log n)$，获取答案 $O(n \log n)$，总复杂度 $O(n \log n)$，足以通过，当然其他解法可能更快，例如前缀和可以做到 $O(n)$ 获取答案。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define int long long

const int N = 1e5;

int a[N];

struct Node
{
	int l, r, sum;
};

Node tree[N << 2ll];

void push_up(int u)
{
	tree[u].sum = tree[u << 1ll].sum + tree[u << 1ll | 1ll].sum;
}

void build(int u, int l, int r)
{
	tree[u] = { l, r };
	if (l == r) tree[u].sum = a[r];
	else
	{
		int mid = (l + r) >> 1ll;
		build(u << 1ll, l, mid);
		build(u << 1ll | 1ll, mid + 1ll, r);
		push_up(u);
	}
}

int query(int u, int l, int r)
{
	if (tree[u].l >= l && tree[u].r <= r) return tree[u].sum;
	int mid = (tree[u].l + tree[u].r) >> 1ll, s = 0;
	if (l <= mid) s = query(u << 1ll, l, r);
	if (r > mid) s += query(u << 1ll | 1ll, l, r);
	return s;
}

signed main()
{
	int n, ans = 0, sum = 0;
	scanf("%lld", &n);
	for (int i = 1ll; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	sort(a + 1ll, a + n + 1ll);
	build(1ll, 1ll, n);
	for (int i = 1ll; i <= n; i++)
	{
		sum = query(1ll, i + 1ll, n);
		ans += sum - a[i] * (n - i);
	}
	printf("%lld\n", ans << 1ll);
	return 0;
}
```


---

## 作者：Great_Influence (赞：0)

我们将 $x_i$ 从小到大排序依次考虑。

容易发现对于比 $x_i$ 小的 $x_j$ 产生贡献为 $x_i-x_j$ ，对比 $x_i$ 大的 $x_k$ 产生贡献为 $x_k-x_i$ 。

只考虑 $x_i$ 的部分，容易发现有多少数字比 $x_i$ 小 $x_i$ 产生多少正贡献， 有多少数字比 $x_i$ 大产生多少负贡献。综合起来 $x_i$ 产生的贡献为:

$$x_i[i-1-(n-i)]=x_i(2i-n-1)$$

最后因为题目比较奇葩， $i$ 和 $j$ 之间会对话两次，所以将答案乘以 $2$ 即可。

瓶颈在排序，总时间复杂度为 $O(n\log n)$ 。

代码省略。

---

