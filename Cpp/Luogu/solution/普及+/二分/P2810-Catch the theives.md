# Catch the theives

## 题目背景

你们懂的，浙江某高中的保安是非常敬（sui）职（bian）的，但是有一天，一群奶牛（不要问我怎么想的），溜进了校园走进了二食堂，偷吃了可口的饭菜（没尝过）。现在 headmaster 非常生气，让保安严查此事。这时 \*\*\* 走过，勤劳而又严谨的保安求助 \*\*\*，\*\*\* 很忙所以把任务交给了你。要不要来杯咖啡先。

## 题目描述

karlven 听说保安在打游戏值班时看到有 $4$ 只奶牛滚出校门（吃太饱了？），而且这个品种的奶牛非常贪心，而且有秩序。怎么体现？偷吃的时候他们会排队，且后一只偷吃的量是前一只的**整数倍（设为 $k,k>1$）**，按照他的经验估计这些奶牛**最多能吃 $m$ 吨**的食物，一旦**超过就会暴毙**化为灰烬，所以一只奶牛**不会**吃超过 $m$ 吨的食物并且只能**一吨一吨**吃。一旦有一只奶牛无法吃东西，他就会攻击同伴然后自尽。现在 karlven 不告诉你 $m$ 的值，只告诉你奶牛**能够一起偷吃并且一起安全滚出校门**的方案数量 $n$（$n\le10^{15}$，不要方），请你算出 $m$ 的值，若有多种解，输出**最小的可能值**。如果你怎么算都算不出，就输出 $-1$，然后投诉保安。

## 说明/提示

对于 $100\%$ 的数据，$n\le10^{15}.$

样例解释：

样例 #1：$(1,2,4,8)$；

样例 #2：$(1,2,4,8),(1,3,9,27),(2,4,8,16),(2,6,18,54),(3,6,12,24),(4,8,16,32),(5,10,20,40),(6,12,24,48).$

## 样例 #1

### 输入

```
1```

### 输出

```
8```

## 样例 #2

### 输入

```
8```

### 输出

```
54```

# 题解

## 作者：IcyFoxer_XZY (赞：10)

[题目](https://www.luogu.com.cn/problem/P2810)

### ~~这道题挺简单的，怎么才74个AC?~~

废话不多说，讲一下思路：

题目给出合法的四元组的数量 $n$,求最小的 $m$。

那么我们就可以二分 $m$ 了，用 $check$ 来枚举。

可是，题目可能有多个 $m$ 满足 $check(m)=n$。我们需要找出最小的。

别急,把 $check(m)<n$ 的最大 $m+1$ 不就行了么？

**代码来了！**
```cpp
#include<iostream>
#define int long long//基本操作 
using namespace std;
int check(int x){
    int sum=0;
    for(int i=2;i*i*i<=x;i++)sum+=x/(i*i*i);
    return sum;//返回sum 
}
signed main(){//main返回signed也是可以的 
    int n,l=1,r=5000000000000000,ans;
    cin>>n;
    while(l<=r){//二分答案 
        int mid=(l+r)/2;
        if(check(mid)<n)ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<(check(ans+1)==n?ans+1:-1);//三目运算(格式:表达式1?成立时执行:不成立时执行;) 
    return 0;//Wonderful!
}//区区19行代码! 
```
Bye!

---

## 作者：critnos (赞：4)

题意简述：

定义一个合法的四元组为 $(a,ak,ak^2,ak^3)$ 满足：

* $k$ 是大于 $1$ 的整数。

* $ak^3\le m$。

现在给出合法的四元组的数量 $n$，求最小的 $m$。

---

首先这个四元组是否合法显然只和 $ak^3$ 有关。

那么不妨二分这个 $m$，对于 check 函数就枚举 $k$，对于每个 $k$，$ak^3\le n$合法的 $a$ 只有 $\lfloor \dfrac m {k^3}\rfloor$ 个。

有一个问题就是这个二分比较奇怪，可能有多个 $m$ 满足 $\text{check}(m)=n$。我们只用找出最小的。

那就把条件改一下，找到最大的满足 $\text{check}(m)<n$，这样最后二分出的答案 $+1$ 就是 $n$ 了。


还有一个问题就是二分的上界。这个我测试了一下，最大的数接近 $5 \times 10^{15}$（和 $m$ 同级），把 $r$ 设为这个就可以了。

时间复杂度 $O(n^{\frac 1 3}\log n)$

觉得很多同学的二分写的都是错的，所以把代码放一下吧：

```cpp
ll check(ll x)
{
	ll i,s=0;
	for(i=2;i*i*i<=x;i++)
		s+=x/(i*i*i);
	return s;
}
int main()
{
	ll l=1,r=4949100894494448,mid,ans;
	cin>>n;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid)<n) ans=mid,l=mid+1;
		else r=mid-1;
	}
	if(check(ans+1)==n) cout<<ans+1;
	else cout<<-1;
}
```


---

## 作者：lm6668 (赞：2)

## 题目理解：
定义一个四元组为（ $a$ , $ak$ , $ak^{2}$ $ak^{3}$）满足：

- $a \leqslant m , ak \leqslant m , ak^{2} \leqslant m , ak^{3} \leqslant m$。

- $k$ 是大于1的整数。

现在给出合法的四元组的数量 $n$ ，求最小的 $m$ 。

------------

这个问题只与 $ak^{3}$ 有关，如果 $ak^{3} \leqslant m$ 那么必定有： $(a-1)k^{3}\leqslant m , (a-2)k^{3}\leqslant m ...... k^{3}\leqslant m$ 。

所以总个数是就是a。

我们先定义一个函数 $f(mid)$ , 然后使用二分查找 $mid$, 判断 $f(mid)$ 与 $mid$ 的关系,小于就更新 $ans$。最后只要判断 $ans+1$ 是否等于 $n$ 即可

------------

直接上代码讲解：


```
#include<bits/stdc++.h>//万能头 
using namespace std;
long long n;//记得开 long long 
long long f(long long mid){//当 m=mid 时 n 的大小 
	long long s=0;
	for(long long i=2;i*i*i<=mid;i++){//i表示 k ,循环 k 等于不同值时有多少种可能 
		s+=mid/(i*i*i);//ak^3<m 时，一共有 a 种可能，用 mid/k^3 即为a 
	}
	return s;
}
int main(){
	cin>>n;
	long long l=0,r=5000000000000000,ans;//r一定开大一点 
	while(l<=r){//二分 
		long long mid=(l+r)/2;
		if(f(mid)<n){
			ans=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	if(f(ans+1)==n) cout<<ans+1;//如果结果等于 n 
	else{//不等于输出-1 
		cout<<-1;
	}
	return 0;
}
```


---

## 作者：望月野QwQ (赞：1)

# 1.题意理解

存在一个任意的正整数 $k$ ，可以使一个组合 $(a,ak,ak^2,ak^3)$ 满足 $a \le m,ak \le m,ak^2 \le m,ak^3 \le m$ 成立，且存在 $n$ 组这样的解，求满足条件的 $m$ 的最小值。

# 2.题目分析

根据题面我们可以知道，如果 $m$ 的大小满足 $ak^3 \le m$ ,那么对于 $a \le m,ak \le m,ak^2 \le m$ 一定满足。

但是，对于同一的 $n$ 可能存在多组	$m$ 满足，但是题目只需要我们求最小的 $m$ 。所以我们需要改变一下，找出一个 $m_1$ 使能有的组数为 $n-1$ 这样将 $m_1+1$ 就可以得到我们需要的 $m$ 了。

最后我们只需要判断一下存在的 $m_1+1=n$ 是否成立就行了。

# 3.代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,ans;
bool check(long long mid)
{
	long long cnt=0;
	for(long long i=2;i*i*i<=mid;i++)
	{
		cnt+=mid/(i*i*i);
	}
	return cnt<n;
}
bool check_last(long long ans)
{
	long long cnt=0;
	for(long long i=2;i*i*i<=ans;i++)
	{
		cnt+=ans/(i*i*i);
	}
	return cnt==n;
}
int main()
{
	cin>>n;
	long long l=0,r=5000000000000000;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(check(mid))l=mid+1,ans=mid;
		else	r=mid-1;
	}
	if(check_last(ans+1))
	{
		cout<<ans+1<<endl;
		return 0;
	}
	cout<<-1<<endl;
	return 0;
 } 
 ```

---

## 作者：LRY314 (赞：1)

设第一头奶牛吃 $a$ 吨，那么四只奶牛分别吃了 $(a,ka,k^2a,k^3a)$ 吨的食物。

然后，我们把奶牛甲乙丙~~彬彬有礼~~地踢出校门，看最后一头决定方案是否可行的奶牛丁，它吃了 $k^3a$ 吨食物。

然后发现对于特定的 $m$ 和 $k$ , $a$ 有 $\left\lfloor\dfrac{m}{k^3}\right\rfloor$ 种取法,所以我们只要考虑 $m$ ,枚举 $k$ 就行了。

由于数据很大， $m$ 需要二分确定。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l=1,r=5000000000000000/*这个是本蒟蒻看了别人题解确定的...*/,mid,ans,s,i;//二分时总喜欢把l,r全放上面
long long check(long long x) {
	s=0;
	for(i=2; i*i*i<=x; i++) //k>1，从2开始
		s+=x/(i*i*i);//总感觉x/i/i/i会出问题，毕竟整数除，这样保险。
	return s;
}
int main() {
	cin>>n;
	while(l<=r) { //二分
		mid=(l+r)/2;
		if(check(mid)<n)ans=mid,l=mid+1;
		else r=mid-1;
	}
	//对于下面这段程序解释：
	//比如当n=9时，m=56。
	//下一个有新方案的m是64，同时满足为2^3和4^3的整数倍
	//所以n=10无解 ，n=11解为m=64
	//不判断二分出的答案n=10时会输出n=11时的64。
	if(check(ans+1)==n) {
		cout<<ans+1;
		return 0;
	}
	cout<<'-'<<'1';
}
```


---

## 作者：EllehLucifenia (赞：1)

### 题意简述：
定义一个合法的四元组$\;(x,k\times x,k^2\times x,k^3\times x)\;$满足：

- $\;1\leq k$。
- $\;k^3\times x\leq m$。

现在给定合法的四元组数量$\;n$,求满足条件的最小的$\;m$。
### 分析：
我们可以很容易的知道，一个四元组是否合法，只与其中的$\;k^3\times x\;$有关，若$\;k^3\times x\leq m$，那么这个四元组也就合法了。

我们又得知，$\;n\;$的范围很大，高达$\;10^{15}$，总时间复杂度的角度来看，我们熟知的且常用的可以满足这个范围的只有$\;O(log\;n)\ O(\sqrt n)\;$和$\;O(1)\;$判断了。

我们发现，这个答案是具有单调性的，当$\;m\;$越大时，合法的四元组数量$\;n\;$也就越多。所以我们可以尝试对这个$\;m\;$进行二分。对于每一个$\;m$，最多只有$\;\left\lfloor\dfrac{n}{k^3}\right\rfloor\;$个合法的$\;x$，对于每一个$\;m$，我们可以在$\;O(n^{\frac{1}{3}})\;$的时间内求出其合法的方案数。

总时间复杂度为$\;O(n^{\frac{1}{3}}\times log\;n)$，可以通过此题。

还有一点需要注意的是，当我们二分出最后的答案时，输出前还需判断其合法的方案数是否为$\;n$，因为我们的二分是当其方案数**大于等于$\;n\;$时记录的**，因此我们二分出的答案可能是**方案数大于$\;n\;$的**。

$Code$：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f3f3f3f3f
#define il inline
#define vocaloid(v) (v>='0'&&v<='9')
#define ll long long
template <typename T>
il void read(T &x)
{
	x=0;char v=getchar();
	while(!vocaloid(v)) v=getchar();
	while(vocaloid(v)) {x=(x<<1)+(x<<3)+(T)v-'0';v=getchar();}
}
ll n,l,r,ans=inf,mid;
il ll check(ll x)
{
	ll num=0;
	for(ll i=2;i*i*i<=x;i++)
		num+=x/(i*i*i);
	return num;
}
int main()
{
	read(n);
	l=1;r=5000000000000000;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid)>=n) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(check(ans)==n) printf("%lld\n",ans);
	else puts("-1");
	return 0;
}
```


---

## 作者：胡金梁 (赞：1)

题目意思简化一下就是定义一个合法的四元组 $(a,ak,ak^2,ak^3)$ 满足：
* $k$ 是大于1的整数。
* $ak^3≤m$ 。
现在给了你这些四元组中合法的四元组数量 $n$ ，求最小的 $m$ 。
****
因为 $k$ 不是1，所以四元组中最大的数是 $ak^3$ ，那么四元组是否合法也就取决于 $ak^3$ 。当 $ak^3≤m$ 时，整个四元组肯定合法。这是我们会发现暴力枚举肯定会超时，那么就出来了一个新的算法：二分查找。二分查找的条件很简单，左边界右移的条件是 $cheak(m)<n$ ，否则就右边界左移。在我测试的时候，发现最大的情况接近于 $5×10^{15}$ ，那就直接把右边界定义为 $5×10^{15}$ 就行了。
```cpp
/*胡金梁*/
#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
#define int long long
int cheak(int cs)
{
	int s=0;
	for(int i=2;i*i*i<=cs;i++)
	{
		s+=cs/(i*i*i);
	}
	return s;
}
signed main(){
#if __MY_TEST__
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	int n,ans;
	cin>>n;
	int l=1,r=5000000000000000;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(cheak(mid)<n)
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<(cheak(ans+1)==n?ans+1:-1);
#if __MY_TEST__
	fclose(stdin);
	fclose(stdout);
#endif
}
```


---

## 作者：xmkevin (赞：0)

## 题目大意

题目看似很啰嗦，其实就是给定一个四元组 $(a, ak, ak^2, ak^3)$，使得 $ak^3 < m$。已经给出了数量 $n$，求最小符合要求的 $m$。

## 解题思路

这个四元组中我们显然只需考虑 $ak^3$，我们假设一个函数 $chk(x)$，使得 $chk(x) = n$，那么 $x + 1$ 就是我们想要的答案。

~~什么？你想用顺序查找？~~ 这题用顺序查找T飞了！所以我们要用二分。

二分具体方法：

首先 $l$、$r$ 先定义，注意 $r$ 要$>10^{15}$。

然后套模板，先求出 $mid$，然后判断 $chk(mid)$ 和 $mid$ 的关系，如果小于就更新 $ans$ 为 $mid$。

剩下部分（ $l$ 和 $r$ 的转移方法）真的就是模板了。

## 代码

```cpp
#include <iostream>
using namespace std;
typedef long long ll;//不开longlong见祖宗

ll n;
ll chk(ll u) {
	ll sum = 0;
	for(ll i = 2; i * i * i <= u; i++) {
		sum += u / (i * i * i);//三元组中的ak^3
	}
	return sum;
}
int main() {
	cin >> n;
	ll l = 0, r = 5000000000000000, ans;//r一定要开大！
	while(l <= r) {//模板二分
		ll mid = (l + r) / 2;
		if(chk(mid) < n) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	if(chk(ans + 1) == n) cout << ans + 1;
	else {
		cout << -1;//如果最后求出的结果经过计算后不得n那么就要输出-1
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 简化版题意

有一个四元组：$(x,xk,xk ^ 2,xk ^ 3)$ 满足以下条件：

1. $k > 1$
2. $x \leq m$
3. $xk \leq m$
4. $xk ^ 2 \leq m$
5. $xk ^ 3 \leq m$

现在给定满足条件的四元组的个数 $n$，求：最小的 $m$ 是多少？

# 思路

$\because x \leq xk \leq xk ^ 2 \leq xk ^ 3 \leq m$

$\therefore \text{满足条件的四元组只与} xk ^ 3 \text{有关}$

我们的 $f$ 函数，就可以枚举 $k$，那么对于每一个合法的 $xk ^ 3$，那么它的贡献为 $\lfloor \frac{m}{k ^ 3} \rfloor$。

此时，我们可以用上二分答案的方法，来枚举 $m$。

但是，这题的答案很奇怪，它是求满足条件 $m$ 的最小值。

因此，我们可以求出方案数小于 $n$ 的最大的 $m$，然后判断一下 $m + 1$ 的方案数是否等于 $n$。

如果是直接输出 $m + 1$，否则输出 `-1`。

# code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n,ans;

int f(int x){
	int res = 0;
	for (int i = 2;i * i * i <= x;i++) res += x / (i * i * i);//枚举 k 算出方案数 
	return res;
}

signed main(){
	cin >> n;
	int l = 1;
	int r = 5e15 + 10;
	while (l <= r){//二分模板 
		int mid = l + r >> 1;
		if (f(mid) < n){
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	if (f(ans + 1) == n) cout << ans + 1;//判断 
	else puts("-1");
	return 0;
}
```

---

## 作者：Exschawasion (赞：0)

如果要通过方案数 $n$ 计算最大的 $m$ 是比较难做的。正难则反，逆向思考：知道 $m$ 求 $n$。即求四元组 $(x, xk, xk^2,xk^3),$ 且 $xk^3 \leq m$ 的个数。

假设 $k$ 已知，求方案数。显然，如果 $xk^3 \leq m$，那么必然有 $(x-1)k^3 \leq m$，$(x-2)k^3 \leq m$…… $k^3 \leq m$，方案总数为 $x$。根据这一点，我们可以枚举 $k$，使得 $k^3 \leq m$，总方案数 $f(m)$ 即为 

$$f(m)=\sum_{k=2}^{m^{1/3}} \lfloor \frac{m}{k^3} \rfloor$$

需要注意，题目中限制 $k$ 不能取 $1$。有了这个函数，本题转化成求一个最小的 $m$ 使得 $f(m)=n$。显然函数 $f$ 是**单调不降**的，能用二分法求解这个方程。

有一个细节：$f$ 是**单调不降**但并非**单调上升**，可能存在相邻的一段区间使得 $f$ 值均为 $n$，而要求的解是这个区间的左端点。解决这个问题的办法是先求 $f(m)=n-1$ 的解，取解的区间的右端点加上 $1$ 即可得到 $f(m)=n$ 解的区间的左端点。

二分的上界。实际上大约只需要 $5 \times 10^{15}$ 就可以，保险起见这里取了 $10^{16}$ 作为上界。

```
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define Cubes(x) ((x) * (x) * (x))

int n;

int check(int v) {
	int ans = 0;
	for(int i = 2; Cubes(i) <= v; i++) ans += v / Cubes(i);
	return ans;
}

signed main() {
	scanf("%lld", &n);
	bool ok = false;
	int L = 1, R = 1e16;
	int ans;
	while(L <= R) {
		int mid = (L + R) >> 1;
		if(check(mid) < n) ans = mid, L = mid + 1, ok = true;
		else R = mid - 1;
	}
	if(check(ans + 1) != n) puts("-1");
	else printf("%lld", ans + 1);
	return 0;
}
```



---

