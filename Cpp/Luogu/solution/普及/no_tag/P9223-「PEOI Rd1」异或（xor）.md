# 「PEOI Rd1」异或（xor）

## 题目描述

给定两个正整数 $n,m$，求：

$$\sum_{i=1}^{n}\sum_{j=1}^{m}\left(i \oplus j\right) $$

其中，$\oplus$ 表示按位异或运算（即 C++ 中的 `^` 符号）。答案对 $998244353$ 取模。

## 说明/提示

#### 样例解释

第一个样例第一组数据：

$\begin{aligned}&(1 \oplus 1)+(1 \oplus 2)+(2 \oplus 1)+(2 \oplus 2)\\=\ &0+3+3+0\\=\ &6\end{aligned}$

第二组数据：

$\begin{aligned}&(1 \oplus 1)+(1 \oplus 2)+(1 \oplus 3)+(2 \oplus 1)+(2 \oplus 2)+(2 \oplus 3)+(3 \oplus 1)+(3 \oplus 2)+(3 \oplus 3)\\=\ &0+3+2+3+0+1+2+1+0\\=\ &12\end{aligned}$

---

#### 数据范围

|子任务|$n,m \leq$|特殊性质|分值|
|:-:|:-:|:-:|:-:|
|$1$|$10^3$|无|$10$|
|$2$|$10^6$|无|$20$|
|$3$|$10^{16}$|A|$20$|
|$4$|$10^{16}$|无|$50$|

- 特殊性质 A：保证 $n=2^p-1$，$m=2^q-1$，其中 $p,q\in\mathbb Z$。

对于 $100\%$ 的数据，保证 $1 \leq n,m \leq 10^{16}$，$1 \leq T \leq 50$。

## 样例 #1

### 输入

```
2
2 2
3 3```

### 输出

```
6
12```

## 样例 #2

### 输入

```
2
4 8
8 9```

### 输出

```
144
420```

# 题解

## 作者：GavinCayne (赞：10)

此篇题解是为**补充前两位大佬（均为排名前 $200$ 的超级大犇）的题解**。毕竟人家和本蒟不在同一水平，简单说几句就以为我这样的小蒟蒻能一下搞懂找到门路（~~嘤嘤嘤~~）。
# 题目大意
[传送门](https://www.luogu.com.cn/problem/P9223)

给你 $n$ 和 $m$，求 $1$ 到 $n$ 所有的数异或上 $1$ 到 $m$ 所有的数结果相加的总和。
## 整理一波思路
1. 暴力计算。直接双环枚举 $n$ 和 $m$，把每一次异或的值算出来再加。这样的话时间复杂度为 $O(Tnm)$。由于 $n,m\le10^{16}$，**必炸**。
1. 考虑从异或本身定义出发。只有当 $a$ 和 $b$ 某一二进制位一个为 $1$ 且另一个为 $0$ 时异或值为 $1$。**即当进行到第 $now$ 位，若 $n$ 这边取了一个某位为 $1$ 的数，$m$ 这边要取一个同一位为 $0$ 的数才能使结果产生贡献**。不妨设 $n$ 这边有 $x$ 个 $now$ 位为 $1$，$m$ 这边有 $y$ 个 $now$ 位为 $1$，那么 $n$ 这边贡献（该位为 $1$ 的数的个数）即可表示为 $x\times(m-y)$，同理 $m$ 这边的贡献为 $y\times(n-x)$。$now$ 位为 $1$ 时自身数值为 $2^{now}$，结果用总贡献乘数值，为 $[x\times(m-y)+y\times(n-x)]\times2^{now}$。然后找到每一位按这种方案求出贡献，加在一起即可。
1. 如何找到每一位有几个数为 $1$？（**重点来啦，两位奆佬没细讲**）设现在在第 $now$ 位。那么，不考虑高位，第 $now$ 位为 $0$ 的数从 $0$ 到 $2^{now}-1$，一共 $2^{now}$ 个；而第 $now$ 位为 $1$ 的数从 $2^{now}$ 到 $2^{now+1}-1$，也是 $2^{now}$ 个。那么我们就可以得出第 $now+1$ 位的数值中第 $now$ 位为 $1$ 的占一半！只要我们算出 $n\div2^{now+1}$ 再乘 $2^{now}$ 不就知道这一位有几个数为 $1$ 了吗？（**有的人会问这是不是多此一举，直接用 $n\div2$ 不就得了**，但实际上 $now$ 可以取到小于等于 $n$ 的最大偶数次幂，换句话说 $2^{now+1}$ 很有可能超过 $n$，**也就是除法运算时 $n$ 不够除**。）如果 $n$ 不是 $2$ 的整数次幂，结果**必然产生余数**。余数中前 $2^{now}-1$ 是第 $now$ 位为 $0$（与前文相比排除了 $0$，即没余数），那么 $n\bmod2^{now+1}\le 2^{now}-1$ 时贡献为 $0$，反之就减去前 $2^{now}-1$，贡献为 $n\bmod2^{now+1}-(2^{now}-1)$。

### 喜闻乐见的代码时间
**为了偷懒，本蒟把 $now$ 定义为了 $2^{now}$，用 $i$ 来枚举当前的位置，观看时请务必注意。**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M=998244353;
int t,cnt[33][3];
int times(int x,int y)
{
	return ((x%M)*(y%M))%M;
}
int pl(int x,int y)
{
	return ((x%M+y%M)%M+M)%M;
}
inline int read()
{
	int f=1,k=0;
	char c=getchar();//读入一个字符 
	//非数字 
	while(c<'0'||c>'9')//读到空格后
	{
		if(c=='-')f=-1;//读到负数  
		c=getchar();//两个功能：读取负号后面的数字或者读入空格等。 
	}
	//数字 
	while(c>='0'&&c<='9')
	{
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();//一位一位读入数字 
	}
	return f*k;	
}
signed main()
{
	t=read();
	while(t--)
	{
		int n=read(),m=read(),ans=0,now=1;
		memset(cnt,0,sizeof(cnt));
		for(register int i=0;(1ll<<i)<=max(n,m);i++)
		{		
			int f=now<<1;
			cnt[i][1]=(now<=n?(now*(n/f)+(n%f+1>=now?(n%f-now+1):0)):0);//1~n第i位几个数值位1 
			cnt[i][2]=(now<=m?(now*(m/f)+(m%f+1>=now?(m%f-now+1):0)):0);//1~m第i位几个数值位1 
			ans=pl(ans,times(now,pl(times(cnt[i][1],(m-cnt[i][2])),times(cnt[i][2],n-cnt[i][1]))));
			now<<=1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
最后提醒大家时刻不要忘记模 $998244353$！完结撒花！感谢观看！

---

## 作者：Uuuuuur_ (赞：4)

这道题细节很多呢。

思路其实不难想，就是把 $1 \sim N$ 和 $1 \sim M$ 的数全部拆成二进制，对于每一位 $i$，我们设 $1 \sim N$ 中一共有 $P$ 个数在第 $i$ 位上为 $1$，$1 \sim M$ 中一共有 $Q$ 个数第 $i$ 位上为 $1$，那么第 $i$ 位对答案的贡献是 
$$2^i * ( P * (M - Q) + Q * (N - P))$$
这个式子利用乘法原理就能推导。

接下来关键是如何算出 $P$ 和 $Q$。

这个只需要你把 $1 \sim N$ 的二进制一个一个写下来就好了。

![](https://cdn.luogu.com.cn/upload/image_hosting/5fvqli0v.png)

观察每一位 $1$ 出现的规律，它们是周期性出现的，运用小学奥数知识，相信你一定能找到答案！

时间复杂度 $O(T \log N)$。

我的计算方式过于无脑复杂请不要学我。

但~~为了仪式感~~我还是放上了我的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll T, n, m;
ll f[70];
ll ans;
ll mult(ll a, ll b) {
    return a % mod * (b % mod) % mod;
}
ll add(ll a, ll b) {
    return ((a % mod + b % mod) % mod + mod) % mod;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        memset(f, 0, sizeof(f));
        ans = 0;
        cin >> n >> m;
        for (ll i = 0, w = 1; 1ll << i <= m; i++, w <<= 1) {
            ll now = w << 1;
            ll k = m - w + 1;
            f[i] = w * (k / now) + min(k % now, w);
        }
        for (ll i = 0, w = 1; 1ll << i <= max(n, m); i++, w <<= 1) {
            ll now = w << 1;
            ll k = n - w + 1;
            ll g = w > n ? 0 : w * (k / now) + min(k % now, w);
            ans = add(ans, add(mult(w, mult(g, (m - f[i]))), mult(w, mult(n - g, f[i]))));
        }
        cout << ans << '\n';
    }
  
    return 0;
}
```


---

## 作者：E1_de5truct0r (赞：4)

## 前言

出题人来一篇。

这道题的目的主要是想考查位运算关于“拆位算贡献”的小 trick 的使用。感觉这个 trick 在一些题目中比较常用，也比较有意义，就放上来了。

## 正文

### Subtask 1

直接暴力枚举 $n,m$，算答案即可。

### Subtask 2

首先一个套路就是，对于所有的二进制相关的题，可以拆位算贡献。

枚举当前的位数 $k$（从低位到高位）。

假设 $1 \sim n$ 这一位是 $0$ 的个数是 $c_0$，是 $1$ 的个数是 $c_1$。

假设 $1 \sim m$ 这一位是 $0$ 的个数是 $d_0$，是 $1$ 的个数是 $d_1$。

则我们任选一个 $c_0$ 的，乘上一个 $d_1$ 的，就会产生 $2^k$ 的贡献。同理，任选一个 $c_1$ 的，乘上一个 $d_0$ 的，也会产生 $2^k$ 的贡献。

所以这一位的贡献就是 $c_1 \times d_0 + c_0 \times d_1$。

那么我们拆位，按位枚举 $1 \sim n$ 和 $1 \sim m$ 算一下 $c_0,c_1,d_0,d_1$ 的数量，统计贡献即可。

注意由于 $T$ 比较大，所以可以从 $1$ 到 $10^6$ 预处理一遍，到时候的贡献就可以直接算了。

复杂度 $O(n \log n+T)$。

### Subtask 3

容易发现这个时候，除了 $n$ 和 $m$ 的最高位，每一位要么全 $0$，要么 $0/1$ 等分。

因此 $c_0=c_1=n/2$，$d_0=d_1=m/2$。

直接算即可。复杂度 $O(T \log n)$。

### Subtask 4

考虑第 $k$ 位，显然一个长度为 $2^{k+1}$ 次方的段可以让 $0$ 和 $1$ 等分。因此可以先拆出若干个段，剩下的长度肯定小于一段。

考虑分类讨论。显然如果剩下的长度 $L \leq 2^k$，则这一位剩下的只有 $0$，否则会有 $L-2^k$ 个 $1$。

对 $n$ 和 $m$ 分别计算一下，乘起来即可。

复杂度 $O(T \log n)$。

---

## 作者：Yang18630303 (赞：3)

[原题](https://www.luogu.com.cn/problem/P9223)

本人发这篇题解，是为了使用 `if else `之类的而不是三目运算符这种像我这样的蒟蒻看不懂的东西来解释一下。

大致题意：

给定两个正整数 $n,m$，求 $ \sum_{i=1}^{n}\sum_{j=1}^{m}\left(i \oplus j\right) $ 并对 $998244353$ 取摸。

因为有 $T$ 组数据，所以我们的时间复杂度肯定是 $O(Tx)$，$x$ 表示处理单个问题的时间复杂度。

然后，我们看一眼数据范围：$1 \le m,n \le 10^{16}$。

这个范围只能通过根号或者 $\log$ 级别的时间复杂度通过，根号大概需要卡常，而异或是位运算，将数转化二进制计算，所以经过猜测 $x$ 是 $\log_2$ 级别。

### 主题思路

因为异或是根据按位计算的，那么二进制上同一位只能对改位的结果造成影响，最后结果相当于各个位上异或值的和，因此我们可以考虑到按照二进制一位一位的计算。

接下来我们看单个位的特点。这里使用 $\operatorname{w}(x,sum)$ 表示 $x$ 在二进制下从后往前的第 $sum$ 位的值。

首先，我们发现，对于任意的 $\operatorname{w}(x,sum) = 0$ 的 $x$，只有 $\operatorname{w}(y,sum) = 1$ 的 $y$ 才能使其异或之后值为 $1$，而对于任意的 $\operatorname{w}(x,sum) = 1$ 的 $x$，只有 $\operatorname{w}(y,sum) = 0$ 的 $y$ 才能使其异或之后值为 $1$。

所以，如果 $ \sum_{i=1}^n \operatorname{w}(i,sum) = a$，$ \sum_{i=1}^m \operatorname{w}(i,sum) = b$，不难发现这个时候总二进制从后向前第 $sum$ 位一共有 $a(m-b)+b(n-a)$ 个本位异或值为 $1$，此时这一位的总共的值为 $[a(m-b)+b(n-a)] \times 2^{sum}$。

这个时候，我们的问题转化了：如何求出 $a$ 和 $b$。

首先我们观察一下规律，下表是 $1$ 到 $15$ 转化成二进制之后的表。
```
0 0 0 1
0 0 1 0
0 0 1 1
0 1 0 0
0 1 0 1
0 1 1 0
0 1 1 1
1 0 0 0
1 0 0 1
1 0 1 0
1 0 1 1
1 1 0 0
1 1 0 1
1 1 1 0
1 1 1 1
```

看最后一位，发现先有 $0$ 个 $0$（注意，这一步很关键），之后 $1$ 个 $1$，$1$ 个 $0$ 循环。

倒数第二位，发现先有 $1$ 个 $0$，之后 $4$ 个 $1$，$4$ 个 $0$ 循环。

倒数第三位，发现先有 $3$ 个 $0$，之后 $4$ 个 $1$，$4$ 个 $0$ 循环。

于是，规律出来了：

对于任意正整数 $k$，正整数二进制倒数第 $k$ 位的规律是先有 $k-1$ 个 $0$， 之后是 $k$ 个$1$，$k$ 个 $0$ 依次循环。

日常分类讨论。

+ 当 $sum>n$ 的时候，$a = 0$。

+ 当 $sum<n$ 的时候，还是分为两种情况。
	+ 当 $2sum > n$ 的时候，前 $sum-1$ 个都是 $0$，剩下的都是 $1$。因此此时 $a=n-sum+1$。
   + 当 $2sum < n$ 的时候，我们可以发现每 $2sum$ 个数里面一定有 $sum$ 个数 $\operatorname{w}(x,sum)$ 等于 $1$ ，因此我们将这里分成两个部分：整的和零的。 
       + 不难发现整的部分贡献值为 $2^{sum}\lfloor \frac{n}{2^{sum+1}} \rfloor $ **注意：这里不能化简，因为需要有整除**
       + 零散的部分可以发现与 $2sum>n$ 的情况类似，**不过注意由于此时 $n \bmod (2sum)$ 不一定大于 $sum$，所以零散部分的值为 $\max(0,n \bmod (2sum)-sum+1)$**
	+ 因此当 $2sum < n$ 的时候 $a= 2^{sum}\lfloor \frac{n}{2^{sum+1}} \rfloor + \max(0,n \bmod (2sum)-sum+1)$
    
~~不难发现~~ $a= 2^{sum}\lfloor \frac{n}{2^{sum+1}} \rfloor + \max(0,n \bmod (2sum)-sum+1)$ ~~这个公式适用于所有情况但是为了可读性我还是没有这样做~~

$b$ 和 $m$ 同理。

此时时间复杂度为 $O(T(\log_2n+\log_2m))$。

### 代码

**注意：在下面的代码中 $\log_2sum$ 表示题解之中的 $sum$ **

~~~
#include <iostream>
#include <cmath>
#define int long long
using namespace std;
const int mod=998244353;
signed main(){
    long long m,n,sum,ans,o,p;
    //m,n用于输入，sum用来标记当前位数，anms记录答案，o表示题解之中的a，p表示b
    int t;
    cin>>t;
	for(int i=0;i<t;i++){
        cin>>n>>m;
        if(n>m){
            swap(n,m);
            //这里是为了确定m>=n使得下面while循环的条件更好写
        }
        sum=1;
        ans=0;
        while(sum<=m){//按位计算
        	o=0;
        	p=0;
        	if(sum>n){
        		o=0;
			}
            else if(sum*2>n){
                o=n-sum+1;
            }
            else{
                o=n/(sum*2)*sum+(max(1LL-1,n%(sum*2)-sum+1));
                //注意这里我用了1LL-1，要不然会CE，警示后人
            }
            if(sum>m){
            	p=0;
			}
            else if(sum*2>m){
                p=m-sum+1;
            }
            else{
                p=m/(sum*2)*sum+(max(1LL-1,m%(sum*2)-sum+1));
                //注意这里我用了1LL-1，要不然会CE，警示后人
            }
            //o=n/(sum*2)*sum+(max(1LL-1,n%(sum*2)-sum+1));
            //p=m/(sum*2)*sum+(max(1LL-1,m%(sum*2)-sum+1));
            ans+=(o%mod*((m-p)%mod)+p%mod*((n-o)%mod))%mod*(sum%mod);
            //这里因为取摸爆了好几次，最后搞得现在一下一取摸
            ans%=mod;
            sum<<=1;
            //上面的一定加，我一次提交忘加了，好害怕被说是卡评测(
        }
        cout<<ans<<endl;
    }
    return 0;
}
~~~

### 警示后人（全是我犯过的）

+ 一定记得取摸，宁可取得狠也要防止溢出
+ 多组数据一定记得清空
+ 一定记着不要误交死循环代码
+ $\max$ 两个参数一定是同一个类型，一个 `int` 一个 `long long` 会 CE 。
+ 分类讨论一定考虑全面，要耐心的找规律
+ 对于两个相同作用的量一个量改变了求法另一个也要记得跟着改（我有三发就是这么 20pts 的）

感谢题解审核员 cn_ryh 、樱雪喵 和 蒟蒻君HJT 对我的题解进行细致的修改并指明本人稀碎的 $\LaTeX$。

第一篇题解完结撒花。

---

## 作者：PineappleSummer (赞：2)

不是，调了 1h 发现模数写成 $10^9+7$ 了。

题不难啊，拆个位就好了，有点像 [[ABC356D] Masked Popcount](https://www.luogu.com.cn/problem/AT_abc356_d)，把这题代码改一改就过了。

考虑按位处理。对于第 $i$ 位，如果 $1\sim n$ 中第 $i$ 位为 $1$ 的数字个数为 $y_a$，$1\sim m$ 中第 $i$ 位为 $1$ 的个数为 $y_b$，那么第 $i$ 为对答案的贡献就是 $2^i\times (y_a\times (m-y_b)+y_b\times (n-y_a))$。

那么问题在于如何计算 $y_a$ 和 $y_b$。可以自己将前几个数的二进制打表输出看一下，会发现对于第 $i$ 位，令 $a=n+1,b=m+1$，则 $y_a={\dfrac{a}{2^{i+1}}\times 2^i+\max(0,a\bmod 2^{i+1}-2^i)}$，$y_b$ 同理。

那么就做完了。时间复杂度 $O(T\log n)$。

代码：
```cpp
#define int long long
int mul (int a, int b) { return a % mod * (b % mod) % mod; }
int add (int a, int b) { return ((a % mod + b % mod) % mod + mod) % mod; }
void solve () {
	cin >> n >> m;
	int a = n + 1ll, b = m + 1ll, ans = 0ll;
	for (int i = 0; i < 60; i++) {
		int x = 1ll << (i + 1ll);
		int ya = (a / x) * (x >> 1ll) + max (0ll, a % x - (x >> 1ll));
		int yb = (b / x) * (x >> 1ll) + max (0ll, b % x - (x >> 1ll));
		ans = add (ans, add (mul ((1ll << i), mul (ya, (m - yb))), mul ((1ll << i),  mul (yb, (n - ya)))));
	}
	cout << ans << '\n';
}
```

感觉对于取模的题目，写个加和乘的取模函数比较方便，不用考虑哪个地方爆 `long long`。

---

## 作者：Herobrine6265 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9223)

---

# 思路

### Step 1：暴力
没啥说的

时间复杂度 $\Omicron(nm)$ 

期望得分：10pts

### Step 2：观察分析
首先显然的是最后的结果只与 $[1,n]$ 和 $[1,m]$ 内每一个二进制位上出现 $1$ 的次数有关

记 $[1,m]$ 内二进制第 $i$ 位为 $1$ 的次数为 $\text{cnt1}_i$，$[1,n]$ 内二进制第 $i$ 位为 $1$ 的次数为 $\text{cnt2}_i,\text{pos}=\lfloor\log_2\max(n,m)\rfloor$

对第 $k$ 位分析，则在累加过程中有 $n-\text{cnt2}_k$ 次原式中 $j$ 在第 $k$ 位没有发生反转，贡献了 $\text{cnt1}_k$ 个 $1$；有 $\text{cnt2}_k$ 次在第 $k$ 位发生了反转，贡献了 $m-\text{cnt1}_k$ 个 $1$。

则第 $k$ 位在结果中带来的 $1$ 的数量（忽略进位）为 
$$\text{cnt1}_k(n-\text{cnt2}_k)+\text{cnt2}_k(m-\text{cnt1}_k)$$

则最终答案为 
$$
\sum_{i=0}^{\text{pos}}2^i\times(\text{cnt1}_i(n-\text{cnt2}_i)+\text{cnt2}_i(m-\text{cnt1}_i))
$$

计算上式的时间复杂度为 $\Omicron(\text{pos})$ 次，是可接受的，因此我们考虑如何快速得出 $\text{cnt1}_i$ 和 $\text{cnt2}_i$

显然的，若第 $i$ 位不是 $m$ 最高位，则 $\text{cnt1}_i=\lfloor\frac{m+1}{2^i}\rfloor\times 2^{i-1}$

若第 $i$ 位是 $m$ 最高位，则 $\text{cnt1}_i=\max(0,(m+1)\mod2^{j+1}-2^j)$，原因在于从 $0$ 开始计起则则 $[0,2^{i-1})$ 的第 $i$ 位为 $0$，$[2^{i-1},2^i)$ 的第 $i$ 位为 $1$

对 $n$ 同理，因此可以在 $\Omicron(\text{pos})$ 内得出 $\text{cnt1},\text{cnt2}$ 的值

综上总时间复杂度为 $\Omicron(T\times\text{pos})$，可以通过本题

# AC Code
温馨提示：记得及时取模
```cpp
#include <iostream>
#define ll long long

using namespace std;

const int mod = 998244353;

ll pow2[60] = {1};

signed main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 1; i < 60; i++)
        pow2[i] = (pow2[i - 1] << 1);
    while (t--)
    {
        ll n, m, ans = 0;
        cin >> n >> m;
        for (int j = 0, cnt1, cnt2; pow2[j] <= max(m, n); j++)
        {
            cnt1 = (m + 1) / pow2[j + 1] % mod * pow2[j] % mod + max(0ll, (m + 1) % pow2[j + 1] - pow2[j]) % mod;
            cnt1 %= mod;
            cnt2 = (n + 1) / pow2[j + 1] % mod * pow2[j] % mod + max(0ll, (n + 1) % pow2[j + 1] - pow2[j]) % mod;
            cnt2 %= mod;
            ans += (m - cnt1) % mod * (pow2[j] % mod) % mod * cnt2 % mod;
            ans %= mod;
            ans += (n - cnt2) % mod * (pow2[j] % mod) % mod * cnt1 % mod;
            ans %= mod;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：P9223 「PEOI Rd1」异或（xor）
## 题目大意：
给你 $n$ 和 $m$，求 $1$ 到 $n$ 所有的数异或上 $1$ 到 $m$ 所有的数结果相加的总和。

大意来源于 GavinCayne。

## 题目思路：

本题要求计算 $$\sum_{i=1}^{n}\sum_{j=1}^{m}\left(i \oplus j\right) $$ 对 $998244353$ 取模的结果。直接暴力枚举从 $1$ 到 $n$， 从 $1$ 到 $m$ 计算异或和，在 $n$ 和 $m$ 达到 $10^{16}$ 时会超时。因此，我们可以按位来处理异或运算，分别计算每一位上 $1$ 的贡献，最后将所有位的贡献相加。

## 注意：
- 本题需开 long long。
- 注意模运算。
## 复杂度：
- 时间复杂度：$O(60 × T)$。
- 空间复杂度：$O(1)$。
肯定能过呀。

---

