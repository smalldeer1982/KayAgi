# Frodo and pillows

## 题目描述

 $ n $ hobbits are planning to spend the night at Frodo's house. Frodo has $ n $ beds standing in a row and $ m $ pillows ( $ n<=m $ ). Each hobbit needs a bed and at least one pillow to sleep, however, everyone wants as many pillows as possible. Of course, it's not always possible to share pillows equally, but any hobbit gets hurt if he has at least two pillows less than some of his neighbors have.

Frodo will sleep on the $ k $ -th bed in the row. What is the maximum number of pillows he can have so that every hobbit has at least one pillow, every pillow is given to some hobbit and no one is hurt?

## 说明/提示

In the first example Frodo can have at most two pillows. In this case, he can give two pillows to the hobbit on the first bed, and one pillow to each of the hobbits on the third and the fourth beds.

In the second example Frodo can take at most four pillows, giving three pillows to each of the others.

In the third example Frodo can take three pillows, giving two pillows to the hobbit in the middle and one pillow to the hobbit on the third bed.

## 样例 #1

### 输入

```
4 6 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 10 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6 1
```

### 输出

```
3
```

# 题解

## 作者：tallnut (赞：2)

此题评绿挺合适的，别信 [CF](https://codeforces.com/problemset/problem/760/B) 上的低评分 1500。
# 思路
此题 CF 标签有 binary search 和 greedy，很合适。就是二分答案+贪心。

直接对最终 Frodo 的枕头数进行二分取最大值。至于检查 `mid` 是否能做到就需要贪心。题目中说
> 如果一个霍比特人比他的邻床的枕头少至少 $2$ 个，那么他的心灵就会受到伤害。

所以相邻的枕头差不能超过 $1$。而在Frodo的枕头数固定的情况下，我们希望总枕头数尽可能小，因此在保证每个人的枕头数 $\ge 1$ 时，每向前一个人就把枕头数减少一个。如果已经 $=1$ 就把之后的枕头数全设为 $1$。向后推同理。
# TLE 代码
根据上面的考虑，我写下了如下代码，成功 $\text{TLE}$。[提交记录](https://www.luogu.com.cn/record/137915595)。
```
#include <iostream>
using namespace std;
int n,m,k,l,r,mid,ans;
bool check(int x)
{
	long long tmpsum = x;
	int i = k - 1,j = x - 1;
	while (i >= 1)
	{
		tmpsum += j;
		if (j >= 2) j--;
		i--;
	}
	i = k + 1;
	j = x - 1;
	while (i <= n)
	{
		tmpsum += j;
		if (j >= 2) j--;
		i++;
	}
	return tmpsum <= m;
}
int main()
{
	cin >> n >> m >> k;
	l = 1;
	r = m;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
		{
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	cout << ans;
}
```
后来我分析了一下复杂度，是 $\Theta (n \log m)$，在该题的数据范围下显然会爆。
# 正解
我们发现，推的过程是一个等差数列，可以直接套公式。只要特判一下，再注意细节，就可以优化到 $\Theta(\log m)$。

可以再加一个小优化。因为每个人至少有一个枕头，所以二分上界可以设为 $m - n + 1$，复杂度降到 $\Theta (\log  (m - n))$。不过没必要。

[AC 记录](https://www.luogu.com.cn/record/137919307)，代码中有注释。
```
#include <iostream>
using namespace std;
typedef unsigned long long ull;
ull n,m,k,l,r,mid,ans;
//计算 l+(l+1)+...+r
ull sum(ull l,ull r) { return ((l + r) * (r - l + 1)) >> 1; }
bool check(int x)
{
	ull tmpsum = x;
	ull i = k - 1,j = x - 1;
	//下面这段暴力会TLE
	/*while (i >= 1)
	{
		tmpsum += j;
		if (j >= 2) j--;
		i--;
	}*/
	//所以我们应该使用等差数列公式进行优化
	if (j >= i) tmpsum += sum(j - i + 1,j);
	else tmpsum += (sum(1,j) + (i - j));
	
	//同理
	i = n - k;
	j = x - 1;
	/*while (i <= n)
	{
		tmpsum += j;
		if (j >= 2) j--;
		i--;
	}*/
	if (j >= i) tmpsum += sum(j - i + 1,j);
	else tmpsum += (sum(1,j) + (i - j));
	return tmpsum <= m;
}
int main()
{
	cin >> n >> m >> k;
	//二分模板
	l = 1;
	//所有人至少有1个枕头，所以二分上界为 m-n+1 就够了
	r = m - n + 1;
	while (l <= r)
	{
		mid = (l + r) >> 1;
		if (check(mid))
		{
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}
	cout << ans;
}
```

---

## 作者：ModestCoder_ (赞：2)

还是挺好做的吧

首先可以想到二分答案

想一想枕头个数如何分配最好，自然是呈现金字塔形式分配

即k号床最多，旁边两个床少一个，再旁边少两个……

check就是直接数学计算一下，用等差数列求和，注意一下细节处理

Code：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n, m, k;

bool check(LL mid){
	LL x = k + mid - 1, sum = 0;
	if (x > n) sum += (mid + mid - n + k) * (n - k + 1) / 2; else
	sum += (mid + 1) * mid / 2 + n - k - mid + 1;
	x = k - mid + 1;
	if (x < 1) sum += (mid + mid - k) * (k - 1) / 2; else
	sum += (mid - 1) * mid / 2 + k - mid;
	return sum <= m;
}

int main(){
	scanf("%lld%lld%lld", &n, &m, &k);
	LL l = 1, r = m, ans;
	while (l <= r){
		LL mid = (l + r) >> 1;
		if (check(mid)) ans = mid, l = mid + 1; else r = mid - 1;
	} 
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：DHT666 (赞：1)

## 题意
有 $n$ 个人分 $m$ 个枕头，主角在第 $k$ 个位置，要求相邻的人枕头个数之差不能超过 $1$，且每个人都必须分到至少一个，求主角能分到的最多枕头数。

$1\le n,m \le 10^9$

## 思路
暴力考虑先给每人一个枕头，再不断给主角加枕头，如果出现了差超过 $1$ 的情况，就给两边的人加枕头。

明显，时间复杂度是不过关的。

稍微模拟一下，就能发现**一轮增加枕头的个数**是等差数列：$1,3,5,7$。如果增加到了两端就不变了，所以考虑去记录这个**一轮的增加区间**，如果两端到头了，就可以直接计算输出了。

时间复杂度大约是 $O(\sqrt n)$。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, k;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	
	m -= n;
	if(m == 0) { // 特判
		printf("1");
		return 0;
	}
	
	int l = k, r = k, res = 1; // l,r 表示一轮的增加区间
	while(m >= r - l + 1) { // 够一轮
		if(l == 1 && r == n) { // 到两端
			res += m / n;
			break;
		}
		m -= r - l + 1;
		res++;
		if(l > 1) l--;
		if(r < n) r++;
	}
	
	printf("%d", res);
	
	return 0;
}
```

---

## 作者：_JellyFish_ (赞：1)

# 1.分析
我们可以发现，$n$，$m$，$k$ 都在 $10^9$ 的范围，所以我们不能模拟做，考虑二分答案，我们首先先选定要二分的对象就是第 $k$ 个位置上放的枕头数量，而check里面的内容则是判断当前枕头总数量是否超过 $m$，如果超过了那就往把 $r$ 往左移移，如果没超过那就把 $l$ 往右移移。

接下来，考虑如何计算枕头数量。我们手造出两种情况来看看（放在我的代码注释里），不难发现，在 $k$ 位置往左和往右分别是一个公差为 $1$ 的等比数列。既然等比，我们就可以用及其快速的方法计算出他们的和。计算方法大家应该都知道，就不多赘述了。最后这个序列枕头的总数就是左边的数量加右边的数量加位置 $k$ 上的枕头数量。为了方便大家理解，等比数列用一个函数写出。

# 2.代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,L,R,ans;
int Cnt(int num){//Cnt(num)表示从1到num的序列和 
	return num*(num+1)/2;
}
int check(int x){
	int lsum=0,rsum=0;
	
	//						   x=5
	//考虑两种序列：1 1 1 2 3 4 5 4 3 2 1 1
	//				L=6			k		R=5
	//考虑两种序列：3 4 5 6 7 8 9 8 7 6 5 4
	//						   x=9
	
	
	if(x>L)lsum=x*L-Cnt(L);//x=9时，3 4 5 6 7 8像这样子的计数 
	
	else lsum=Cnt(x-1)+(L-x+1);//x=5时，1 1 1 2 3 4像这样子的计数 
	
	if(x>R)rsum=x*R-Cnt(R);//x=9时，8 7 6 5 4像这样子的计数 
	
	else rsum=Cnt(x-1)+(R-x+1);//x=5时，4 3 2 1 1像这样子的计数 
	
	return lsum+rsum+x;
}
signed main(){
	cin>>n>>m>>k;
	L=k-1,R=n-k;//L,R表示k左边右边分别有多少个人 
	int l=1,r=m;//二分 
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)<=m)ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Allanljx (赞：1)

## 思路
（枕头可以不用完）
因为 $n$ 和 $m$ 都比较大，所以考虑二分。二分 Frodo 所能拥有的最多枕头数。而且不难发现最后每个人拥有的枕头数一定是以 Frodo 为中心分别向两边递减的等差数列，因此就可以用求和公式 $O(1)$ 求出需要的枕头数。注意一下枕头数必须大于等于 $1$ 就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans;
bool check(int x)
{
	int s1=0,s2=0;
	if(x>=k)
	{
		s1=(x*2-k+1)*(k)/2;
	}
	else
	{
		s1=(1+x)*x/2+k-x;
	}
	int k1=n-k+1;
	if(x>=k1)
	{
		s2=(x*2-k1+1)*(k1)/2;
	}
	else
	{
		s2=(1+x)*x/2+k1-x;
	}
	if(s1+s2-x<=m) return 1;
	else return 0;
}
signed main()
{
	cin>>n>>m>>k;
	int l=1,r=m;
	while(l<=r)//二分
	{
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans;
}
```

---

## 作者：漠寒 (赞：1)

## 分析

就是一道二分答案的题，枚举 $Frodo$ 能拥有的枕头数，在确定该数后，运用贪心思想，其他人分得的枕头数，应该以他为中心，向四周递减，才能尽可能地少用枕头来满足这个要求，根据两个要点来计算，相邻之差不能大于等于二，因此向左和向右皆为一个公差为1的等差数列，第二个要点就是每人至少要有一个枕头，特判左右数列长度和首项关系即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,ans;
inline void read(int &res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
}
bool check(int x){
	int sum=x,len;//提前加入Frodo自身的枕头数，避免重复 
	len=k-1;//数列长度 
	if(len<x)sum+=(x-len+x-1)*(len)/2;
	else sum+=x*(x-1)/2+len-x+1;//首项加末项除以二 
	len=n-k;
	if(len<x)sum+=(x-len+x-1)*(len)/2;
	else sum+=x*(x-1)/2+len-x+1;
	return sum<=m;//最少需要的枕头数是否能够得到 
}
signed main()
{
	read(n);read(m);read(k);
	int l=1,r=m;
	while(l<=r){//二分 
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

二分与贪心典题。

二分 Frodo 的枕头数量。

因为相邻两人枕头数量的差必须小于二，所以可以构造公差为 $1$ 的等差数列，直接用公式计算即可。

时间复杂度 $O(\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k;
int check(int x){
    int sum1,sum2;
    if(x>=k)sum1=(x*2-k+1)*(k)/2;
    else sum1=(1+x)*x/2+k-x;
    int k1=n-k+1;
    if(x>=k1)sum2=(x*2-k1+1)*(k1)/2;
    else sum2=(1+x)*x/2+k1-x;
    return sum1+sum2-x<=m;
}signed main(){
    cin>>n>>m>>k;
    int l=0,r=m+1;//二分上界及下界
    while(l+1<r){//二分 F 的枕头数量
        int mid=l+r>>1;
        if(check(mid))l=mid;
        else r=mid;
    }return cout<<l,0;
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF760B)

### $\texttt{Description}$

有 $n$ 个人和 $m$ 个枕头， 在这 $n$ 个人中，第 $k$ 个人 Frodo 想要最多的枕头。但是相邻两个人的枕头数量之差不能多于 $1$ 个，否则会伤害到枕头少的人，求出 Frodo 在不伤害任何人的情况下，最多能获得多少枕头。

### $\texttt{Solution}$

首先看看数据范围：

>$1 \le k \le n \le m \le 10^9$

由于数据过大，考虑二分答案，二分 Frodo 最多能获得的枕头个数。

由于求满足条件的最大值，所以 $l$ 是最后的答案。

但是 `check` 函数按照正常写法的时间复杂度是 $O(n)$ 的，还是会超时，那么我们该怎么处理呢？

实际上我们只需要运用一点贪心的思想，构造公差为 $1$ 的等差数列就行了。用等差数列的公式就可以解决。

顺便贴下等差数列的常用公式：

>设 $s$ 为总和，$a_1$ 为首项，$a_n$ 为末项，$d$ 为公差，$k$ 为项数。
>
>则有如下公式：
>
>$d=a_2-a_1$
>
>$s=\frac{(a_1+a_n) \times k}{2}$
>
>$a_n=a_1+(k-1) \times d$
>
>$k=\frac{a_n-a_1}{d}+1$



### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k;

bool check(int x) {
	int s1, s2;
	if (x >= k) s1 = (x * 2 - k + 1) * k / 2;
	else s1 = (1 + x) * x / 2 + k - x;
	
	int k1 = n - k + 1;
	if (x >= k1) s2 = (x * 2 - k1 + 1) * k1 / 2;
	else s2 = (1 + x) * x / 2 + k1 - x;
	
	return s1 + s2 <= m + x;
}

inline int read() {
	int x = 0, f = 1; char ch;
	while (isdigit(ch) == 0) ch = getchar(), f = (ch == '-' ? -1 : 1);
	while (isdigit(ch) == 1) x = x * 10 + (ch ^ 48), ch = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {putchar('-'); x = -x; }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
	n = read(), m = read(), k = read();
	
	int l = 0, r = m + 1; // 二分的上界和下界
	
	while (l + 1 < r) {
		int mid = l + r >> 1;
		// 位运算，相当于除以二
		if (check(mid) == 1) l = mid;
		else r = mid;
	}
	
	cout << l;
	return 0;
}
```

完结。

---

## 作者：ATION001 (赞：0)

## 题目描述
有 $n$ 个人和 $m$ 个枕头，每个人**至少**需要有 $1$ 个枕头，第 $k$ 个人想拥有最多的枕头。但是相邻两个人拥有的枕头数量相差**最多**为 $1$，求第 $k$ 个人最多能拥有多少枕头。
## 思路
因为 $n$ 和 $m$ 实在是太大了，所以考虑二分查找最多的枕头数量。

一般情况下，二分是超不了时的，不过这题数据太毒瘤，常规的 $O(n)$ 写法会超时，先放一下 $O(n)$ 写法的判断函数（我不确保是不是对的）：
```cpp
bool code(int mid){
	long long x=mid;
	for(int i=mid-1,o=1;i>=1;i--,o++){
		if(k-o>=1){
			x+=i;
		}
		if(k+o<=n){
			x+=i;
		}
	}
	return x<=m;
}//还是比较好理解的
```
在 TLE 了亿发了以后去拜访了各位巨佬的题解，发现这可以用 $O(1)$ 的写法来求解：

由于相邻两个人枕头数量相差为 $1$，可以构成一个等差数列。从位置 $k$ 向两边递减，不过这个等差数列需要满足：

- 左右两边枕头数量至少为 $1$。

- 长度为 $n$。

所构成的枕头数量是个三角形。

其余的是二分模板，奉上我的代码：
## 代码
```cpp
// LUOGU_RID: 163938570
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool code(long long x){
	long long s1=0,s2=0,k1=n-k+1;
	s1=((x>=k)?(x*2-k+1)*(k)/2:(1+x)*x/2+k-x),s2=((x>=k1)?(x*2-k1+1)*(k1)/2:s2=(1+x)*x/2+k1-x);
	return s1+s2-x<=m;
}
int main(){
	cin>>n>>m>>k;
	long long l=1,r=m-n+1,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(code(mid)){
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<r;
	return 0;
}
```

---

