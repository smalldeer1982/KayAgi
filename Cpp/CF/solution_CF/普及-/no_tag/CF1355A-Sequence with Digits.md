# Sequence with Digits

## 题目描述

Let's define the following recurrence: $ $$$a_{n+1} = a_{n} +       minDigit(a_{n}) \cdot maxDigit(a_{n}). $ $ </p>     <p>Here  $ minDigit(x) $  and  $ maxDigit(x) $  are the minimal and       maximal digits in the decimal representation of  $ x $  without       leading zeroes. For examples refer to notes.</p>     <p>Your task is calculate  $ a\_{K} $  for given  $ a\_{1} $  and  $ K$$$.

## 说明/提示

$ a_{1} = 487 $

 $ a_{2} = a_{1} + minDigit(a_{1}) \cdot maxDigit(a_{1}) = 487 +       \min (4, 8, 7) \cdot \max (4, 8, 7) = 487 + 4 \cdot 8 = 519 $

 $ a_{3} = a_{2} + minDigit(a_{2}) \cdot maxDigit(a_{2}) = 519 +       \min (5, 1, 9) \cdot \max (5, 1, 9) = 519 + 1 \cdot 9 = 528 $

 $ a_{4} = a_{3} + minDigit(a_{3}) \cdot maxDigit(a_{3}) = 528 +       \min (5, 2, 8) \cdot \max (5, 2, 8) = 528 + 2 \cdot 8 = 544 $

 $ a_{5} = a_{4} + minDigit(a_{4}) \cdot maxDigit(a_{4}) = 544 +       \min (5, 4, 4) \cdot \max (5, 4, 4) = 544 + 4 \cdot 5 = 564 $

 $ a_{6} = a_{5} + minDigit(a_{5}) \cdot maxDigit(a_{5}) = 564 +       \min (5, 6, 4) \cdot \max (5, 6, 4) = 564 + 4 \cdot 6 = 588 $

 $ a_{7} = a_{6} + minDigit(a_{6}) \cdot maxDigit(a_{6}) = 588 +       \min (5, 8, 8) \cdot \max (5, 8, 8) = 588 + 5 \cdot 8 = 628 $

## 样例 #1

### 输入

```
8
1 4
487 1
487 2
487 3
487 4
487 5
487 6
487 7```

### 输出

```
42
487
519
528
544
564
588
628```

# 题解

## 作者：do_while_true (赞：5)

看到 $k<=10^{16}$ 就知道暴力是稳超时了，让我们来~~假装~~分析一下。

每次变化，当前的数都是加上自己最小的数码 $*$ 最大的数码，那如果最小的数码是 $0$ ，加上的数肯定也是 $0$，这个数本身不变，最小的数码也不会变，所以当数出现 $0$ 的时候我们就不用继续往后找了。

由于最大的数码和最小的数码相乘的结果最大也不过是 $81$（最大最小均为 $9$），所以每次变化的数不超过 $100$。则我们一定能加到百位出现 $0$ 的情况。而就算每次加上的数都是最小的 $1$（即不出现0的最小值，最小和最大的数码都是 $0$），也只是需要最多 $1000$ 就能让百位有 $0$ 出现，时间复杂度大大减少。

[$\mathcal{Code}$](https://codeforces.com/contest/1355/submission/80323431)

---

## 作者：b6e0_ (赞：4)

打完CF又来写题解啦~求兹磁qwq（第一次AC div2的D题）

[CF题面传送门](https://codeforces.com/contest/1355/problem/A) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1355A) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1355A)

这道题最暴力的方法就是$O(k)$时间枚举，但是这样肯定会爆的，所以我们要想一种办法来优化。如果对于一个$a_i$，它的任意一位是$0$，那么这里的$minDigit(a_i)$就是$0$，所以后面$a$的值都不会发生变化。所以，我们就可以用这个性质来优化，省去不必要的循环。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	long long n,k,i,maxv,minv;//建议long long
	cin>>t;
	while(t--)//这儿是执行t次
	{
		cin>>n>>k;
		while(--k)//这儿是执行k-1次
		{
			i=n;//拷贝一份，否则会修改n的值
			maxv=0;
			minv=10;
			while(i)
			{
				maxv=max(maxv,i%10);
				minv=min(minv,i%10);
				i/=10;
			}
			if(!(maxv*minv))//如果为0，即n的每一位数字中含有0
				break;
			n+=maxv*minv;
		}
		cout<<n<<endl;
	}
	return 0;
}
```
这个算法没有一个准确的时间复杂度。即使最坏的时间复杂度也为$O(k)$，但是是能通过这一题的。

---

## 作者：vectorwyx (赞：3)

显然，当 $a_{i}$ 的数码中出现‘0’时，它就会停止变化，那么最终的答案就是 $a_{i}$。

而如果你是通过打暴力发现这个结论的，你同时也会发现 $i$ 的值并不是很大。于是这题的解法就是不断暴力递推，直到 $a_{i}$ 的数码中出现了0。

但是，要注意，这是**有可能超时的**。因为我们现在还不知道 $i$ 的范围。 那接下来我们分析一下这个算法的时间复杂度。

只考虑 $a_{i}$ 的百位数，那么，当 $a_{i}$ 首次出现了百位向千位上的进位时，也就是当 $a_{i}-a_{1}\ge 1000$时，百位上一定会出现一次0。因为$1\le MinDigit(x)\cdot MaxDigit(x) \le 81$ 。

故而，累加的和最多为1000，那么累加的次数也就是 $i$ 最大为1000。最坏时间复杂度为 $O(1000^{2})$，肯定不会超时。



------------
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline ll read(){
	ll x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

inline int f(ll x){//f(x)=MinDigit(x)*MaxDigit(x)
	int mn=100,mx=0;
	while(x){
		int k=x%10;
		x/=10;
		mn=min(mn,k);
		mx=max(mx,k);
	}
	return mn*mx;
}

void work(){
	ll a=read(),k=read();//注意long long
	for(ll i=1;i<k;++i){
		int w=f(a);
		if(w==0){
			break;
		}
		a+=f(a);
	}
	printf("%lld\n",a);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}

```
点个赞再走吧qwq

---

## 作者：钓鱼王子 (赞：1)

这道题看到数据范围放弃模拟，然而这个 $\min\times\max$ 完全无法转化，但是有一个特点：$0$ 乘任何数等于 $0$，所以一旦 $\min$ 变为 $0$ 就没有任何影响。

但什么时候会变成 $0$ 呢？

假设每次都增加 $1$，这是不可能的情况，但可以这样考虑，再假设每次到一百零几的时候就跳 $10$。

这样在 $1000$ 次以内肯定出现 $10ab$ 的情况，实际上远不到，所以只要 $\min=0$ 就退出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,ans;
inline int mn(re int x){
	re int ans=10;
	while(x){
		ans=min(ans,x%10);
		x/=10;
	}
	return ans;
}
inline int mx(re int x){
	re int ans=0;
	while(x){
		ans=max(ans,x%10);
		x/=10;
	}
	return ans;
}
signed main(){
	t=read();
	while(t--){
		n=read(),m=read()-1;
		while(m--){
			re int x=mn(n),y=mx(n);
			if(!x)break;
			n+=x*y;
		}
		printf("%lld\n",n);
	}
}
```


---

## 作者：PragmaGCC (赞：0)

这道题暴力肯定是不能过的。

那么，我们尝试去减少一下递推的次数

考虑到0乘以任何数都得0，一个数加上0后不变

那么，只要$\min \times \max = 0$，之后的就不用考虑了。

我们不妨大胆猜测，并且事实的确是这样的：乘积最大是$81<100$，必然出现 0，就算是 rp 差到非洲，每次都加 1 ，也能出现 0。
```cpp
#include<cstdio>
typedef long long ll;
ll a, k, ioi; // a 和 k 要开 long long
int qwq;
int min(int x, int y) { // 手写 min 和 max
    return (x < y)? x:y;
}
int max(int x, int y) {
    return (x > y)? x:y;
}
int query(ll n) { // 计算各位最大最小
    int minn = 114514, maxn = 0;
    while(n) {
        int digit = n % 10;
        n /= 10;
        minn = min(minn, digit);
        maxn = max(maxn, digit);
    }
    return minn * maxn;
}
int main(void) {
    scanf("%d", &ioi);
    while(ioi--){
        scanf("%lld%lld", &a, &k);
        for(ll i=2; i<=k; i++){
            qwq = query(a);
            if(qwq != 0)
                a += qwq; // 不是 0 , 加上
            else
                break; // 是 0 了, 后面不需要考虑了
        }
        printf("%lld\n", a);
    }
    return 0;
}
```

---

## 作者：_jimmywang_ (赞：0)

首先，你看看这个$k \leq 10^{16}$,一看哎呀暴力都挂，~~还做什么题~~

那么，我们随便弄几个数试试：

$436-->436+3*6=454$

$454-->454+4*5=474$

$474-->474+4*7=502$

$502-->502+0*5=502$

$502-->502+0*5=502$

$502-->502+0*5=502$

？？？

然后就都是$502$了？~~果然502强力胶名不虚传~~

发现了啥？

这个数里面有一位是0啦

然后你再咋变都是它了~

于是，就好了。。。


$the$_$code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll t;
ll n,m;
ll a[20];
ll mx,mn;
ll doit(ll x,ll k){
	f(i,1,k-1){
		mn=100000000,mx=0;
		ll xx=x;
		while(xx){
			mx=max(mx,xx%10);
			mn=min(mn,xx%10);
			xx/=10;
		}
		if(mn==0)break;
		x+=mn*mx;
	}
	return x;
}
int main(){
	t=d;
	while(t--){
		n=d,m=d;
		printf("%lld\n",doit(n,m));
	}
	return 0;
}
```


---

## 作者：oimaster (赞：0)

# Codeforces 1355 A 题解

## Part1 前言

这道题是我在比赛的时候做的。当时我没想出来，就直接看了 B。然后同学说这道 A 题很水，我就回来看了看，根据他给的提示，完成了本题。

## Part2 题面

有一个数列 $a$，满足以下要求：
$$
a_{n+1}=a_{n}+\operatorname{minDigit}\left(a_{n}\right) \cdot \operatorname{maxDigit}\left(a_{n}\right)
$$
但是题目毕竟没有那么简单。它会给你一个 $a_1$ 和 $K$ ，满足 $1 \leq a_{1} \leq 10^{18}, 1 \leq K \leq 10^{16}$，让你求出 $a_K$ 的值。

## Part3 思路

这道题其实并不难，你可以先暴力看看，会发现一个神奇的结果，在不久后 $\operatorname{minDigit}\left(a_{n}\right)$ 就成了 $0$！

所以，当我们发现 $\operatorname{minDigit}\left(a_{n}\right)$ 到 $0$ 的时候，就立刻终止暴力循环，省掉后面不必要的操作。

其实就是当 $\operatorname{minDigit}\left(a_{n}\right)$ 为 $0$ 的时候 `break`，或者老老实实执行 $K$ 次。

虽然这种做法我没法证明会不会被卡掉，但至少它能 `Accepted`。

## Part4 代码

请自觉不要抄袭。

```c++
#include<iostream>
#define int long long
using namespace std;
int next(int x){
	int maxv=0,minv=10;
	int p=x;
	while(p){
		maxv=max(maxv,p%10);
		minv=min(minv,p%10);
		p/=10;
	}
	return x+maxv*minv;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		while(--k){
			int x=next(n);
			if(x==n)
				break;
			n=x;
		}
		cout<<n<<endl;
	}
}
```

## Part5 结语

自己连这么简单的题都不会，真是太菜了啊！

另外，这道题我曾经 `Wrong Answer ` 过一次，在此提醒：
$$
\texttt{十年 OI 一场空，不开 long long 见祖宗！}
$$

---

