# Dima and Lisa

## 题目描述

Dima loves representing an odd number as the sum of multiple primes, and Lisa loves it when there are at most three primes. Help them to represent the given number as the sum of at most than three primes.

More formally, you are given an odd numer $ n $ . Find a set of numbers $ p_{i} $ ( $ 1<=i<=k $ ), such that

1. $ 1<=k<=3 $
2. $ p_{i} $ is a prime
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF584D/e7615e00ba022b6aedbad362df530b3fd81c2681.png)

The numbers $ p_{i} $ do not necessarily have to be distinct. It is guaranteed that at least one possible solution exists.

## 说明/提示

A prime is an integer strictly larger than one that is divisible only by one and by itself.

## 样例 #1

### 输入

```
27
```

### 输出

```
3
5 11 11
```

# 题解

## 作者：wanggk (赞：3)

## 分析部分
个人认为，比较好的突破口在于： $k≤3$ ，$n$ 为奇数。

那么其实就可以分类讨论：

- $k=1$，也就是只有一个数，这个时候需要判断 $n$ 是否为质数。
- $k=2$，两个质数相加等于一个奇数，由此得出若成立，则这两个质数中必有 $2$ ，即判断 $n-2$ 是否为质数。
- $k=3$，这个时候 可以是 $n=2+2+n-4$ ，也可以是一般情况，即三个奇质数相加。

前两种情况很明确，第三种情况中的一般情况（三个奇质数相加）可以再优化。

三个奇质数相加，那么其中两个奇质数相加必为偶数，满足[哥德巴赫猜想](https://baike.baidu.com/item/%E5%93%A5%E5%BE%B7%E5%B7%B4%E8%B5%AB%E7%8C%9C%E6%83%B3/72364?fr=aladdin)。

这个时候，我们把 $n$ 拿出一个 $3$ 来，根据哥德巴赫猜想，剩下的 $n-3$ 必然可以分为两个质数之和，枚举即可。


## 代码部分
首先是一个大暴力、不加任何优化的判断素数 ~~（原本写线性筛MLE了）~~ ：
```cpp
bool isprime(int x)
{
	if(x==1) return 0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}
```

然后其实就按上述说的来就可以了：
```cpp
int main()
{
	scanf("%d",&n);
	if(isprime(n)) printf("1\n%d",n);
	else if(isprime(n-2)) printf("2\n2 %d",n-2);
	else{
		if(isprime(n-4)) printf("3\n2 2 %d",n-4);
		else{
			printf("3\n3 ");
			n-=3;
			for(int i=3;i<=n;i++)
				if(isprime(i)&&isprime(n-i))
				{
					printf("%d %d\n",i,n-i)
					return 0;
				}
		}
	}
 	return 0;
}
```




---

## 作者：Special_Tony (赞：2)

# 思路
先找到不超过 $n$ 的最大质数 $maxx$，若 $n=maxx$ 说明 $n$ 本身就是质数，输出 $n$ 就行，若 $n=maxx+2$ 说明 $n$ 可以拆分为 $maxx+2$，直接输出 $maxx,2$。如果还不是，只要对 $n-maxx$ 做一次[哥德巴赫猜想](/problem/P1304)即可。注意，$10^9$ 以内质数间的“密度”还很大，暴力枚举判断完全没问题。另外 $n\le10^9$ 的哥德巴赫猜想已被证明，你不用担心无解。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, maxx;
bool check (int x) {
	for (int i = 2; i * i <= x; ++ i)
		if (! (x % i))
			return 0;
	return 1;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = n; i; -- i)
		if (check (i)) {
			maxx = i;
			n -= i;
			break ;
		}
	if (! n)
		cout << "1\n" << maxx;
	else if (n < 3)
		cout << "2\n2 " << maxx;
	else
		for (int i = 2; i < n; ++ i)
			if (check (i) && check (n - i))
				cout << "3\n" << maxx << ' ' << i << ' ' << n - i, exit (0);
	return 0;
}
```

---

## 作者：Fa1thful (赞：2)

### 一、题意

给定一个奇数 $n$，将它表示为最多三个的素数之和。

### 二、分析

首先对于这类型的题，我们首先想到的就是先处理特殊的情况。最容易想到的就是 $n$ 为素数的时候，此时输出 $n$ 的结论是显然的。其次再想也貌似没有什么特殊情况了。想到将一个数的和拆分成三个素数，很自然地就会想到哥德巴赫猜想（即：可以证明对于大于 $2$ 偶数，均可将这个偶数写成两个素数的和）。下面将介绍具体怎么处理。

因为 $n$ 为奇数，可以先将 $n$ 中拆分出一个可以拆分的最大的奇素数（最大是为了降低后面枚举哥德巴赫猜想的复杂度），然后因为 $n$ 是奇数，这个拆分出来的素数也是奇数，所以拆分之后的 $n$ 一定是偶数，所以就可以解决了。但是我们要考虑一种特殊情况就是通过拆分出最大的奇素数之后 $n$ 的大小小于 $3$。于是我们这里进行特判，剩下的 $n$ 只可能等于 $2$ ，可以发现这种情况直接再输出 $2$ 就行了。于是我们就欢乐地解决啦！

### 三、代码
```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(register int i=a;i<=b;++i)
#define _FOR(i,a,b) for(register int i=a;i>=b;--i)
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-'){f=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int mod=1e9+7;
const long double eps=1e-8;
inline int max(int x,int y){return x>=y?x:y;}
inline int min(int x,int y){return x<=y?x:y;}
inline int gcd(int x,int y){return !y?x:gcd(y,x%y);}
inline int lcm(int x,int y){return x/gcd(x,y)*y;   }
inline bool isp(int x){FOR(i,2,sqrt(x))if(x%i==0)return false;return true;}
int poww(int a,int k){a%=mod;int ans=1;while(k){if(k&1)ans=ans*a%mod;a=a*a%mod;k/=2;}return ans;}
int n,diao;
signed main(){
	n=read();if(isp(n)){cout<<1<<endl<<n<<endl;return 0;}//如果n是素数 
	if(isp(n-2)){cout<<2<<endl<<"2 "<<n-2<<endl;return 0;}//如果n分出2之后是素数，对应的是n为奇数时分出来大素数后为2的情况 
	if(isp(n-4)){cout<<3<<endl<<2<<" 2 "<<n-4<<endl;return 0;}//ps：其实这种情况是多余的QWQ 
	_FOR(i,n,2)if(isp(i)){diao=i;break;}//找到最大的素数 
	n-=diao;cout<<3<<endl<<diao<<" "; 
	FOR(i,3,n)if(isp(i)&&isp(n-i)){cout<<i<<" "<<n-i<<endl;return 0;}//哥德巴赫猜想暴力枚举过程 
	return 0;
}
```

### 四、亿点点思考
可以非常显然的看到我们的程序中有从 $n$ 到 $1$ 的循环，可是 $n\le10^9$ 而没有TLE。这是因为可以通过数学证明证明出两两素数间的平均距离大致为 $logn$ （过于复杂这里不做赘述，有兴趣可以左转这篇文章[相邻素数的间距和分布概率期望](https://zhuanlan.zhihu.com/p/480142754)）,所以枚举最大的素数不会超时。

对于本程序的核心思想哥德巴赫猜想部分，虽然哥德巴赫猜想没有被完全证明，但是对于本题的数据范围，这个区间内的哥德巴赫定理是已经通过高性能计算机枚举法证明过的，所以可以保证本题哥德巴赫猜想的正确性。

谢谢观赏

---

## 作者：World_Creater (赞：1)

哥德巴赫猜想应用：

首先根据哥德巴赫猜想：**任何一个大于 $5 $ 的整数都可以表示为三个质数之和**，因此解一定存在。

先考虑一些简单情况：  
1. $n$ 本身就是质数  
没什么好说的，直接输出
2. $n-2$ 是质数  
这个也只需要特判一下直接输出
3. 一般情况  
先找到一个比较大的质数拆出来，然后对于剩下一个较小的**偶数**，我们一定可以找到两个质数之和等于这个数（哥德巴赫猜想的另一个版本）。实际上，虽然 $n\leq10^9$，我们暴力也不需要枚举非常多的数，直接使用 $O(\sqrt{x})$ 的暴力求质数即可通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool pm(int x)
{
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0) return 0; 
	}
	return 1;
}
int main()
{
	int t;
	cin>>t;
	if(pm(t))
	{
		puts("1");
		cout<<t;
		return 0;
	}
	if(pm(t-2))
	{
		puts("2");
		cout<<"2 "<<t-2;
		return 0;
	}
	puts("3");
	for(int i=t;i>=1;i--)
	{
		if(pm(i))
		{
			cout<<i<<" ";
			int k=t-i;
			for(int j=2;j<k;j++)
			{
				if(pm(j)&&pm(k-j))
				{
					cout<<j<<" "<<k-j;
					return 0;
				}
			}
		}
	}
}
```

---

## 作者：MVP_Harry (赞：1)

感觉前几个题解完全没有说到点子上。。。

这个题正解的复杂度是对的，~~虽然我也是看了官方题解之后才知道的。~~ 利用的关键性质是这样的：对于两个素数$p_1, p_2 \le 10^9$, $|p_1 - p_2| < 300.$ 实际上，最大的差值为$282.$ 同时，我们可以发现对于一个小于三百的偶数，一定能被表示成两个素数的和。

因此，可以得出如下的解法：先找一个最大的，满足$p < N - 1$的素数。这一部分复杂度为$O(k\sqrt{N})$，其中最坏情况下，$k = 282$。而剩下的$N - p$为偶数，且小于三百，可以直接暴力枚举，复杂度也为$O(k\sqrt{N})$，跑过绰绰有余。

~~不过感觉这题出的一般，毕竟还是挺玄学的。~~

代码如下：

```
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)
#define per(i, m, n) for (int i = m; i >= n; i--)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define INF 0x3f3f3f3f
using namespace std;

int check(int p) {
    if (p == 1) return 0;
    for (int i = 2; i * i <= p; i++)
        if (p % i == 0) return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    int p1, p2, p3;
    if (check(N)) {
        cout << 1 << "\n" << N << "\n";
        return 0;
    }
    if (check(N - 2)) {
        cout << 2 << "\n" << 2 << " " << N - 2 << "\n";
        return 0;
    }
    for (int i = N - 2; i >= 2; i--) {
        if (check(i)) {
            p1 = i;
            break;
        }
    }
    int remain = N - p1;
    rep(i, 2, remain / 2) if (check(i) && check(remain - i)) {
        p2 = i, p3 = remain - i;
    }
    cout << 3 << "\n" << p1 << " " << p2 << " " << p3 << "\n";
    return 0;
}
```

---

## 作者：lhs_chris (赞：0)

## 前置知识
[哥德巴赫猜想](https://baike.baidu.com/item/%E5%93%A5%E5%BE%B7%E5%B7%B4%E8%B5%AB%E7%8C%9C%E6%83%B3/72364?fr=ge_ala)，任一大于 $2$ 的偶数都可写成两个素数之和。
# 思路
我们可以分类讨论一下。

1. $n$ 一开始就是质数。直接输出即可
2. $n$ 是偶数，那么一定可以写成两个质数之和。那么暴力枚举两个质数即可。

如果以上均不符合，计 $n$ 以内最大的质数为 $x$，它们的差为 $y$。

因为 $x$ 一定是奇数，且此时 $n$ 也一定是奇数。奇数减去奇数一定是偶数。所以直接暴力么枚举两个质数即可。
# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=3e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
ll n,x,y;
bool check(ll x)
{
	if(x==1)return 0;
	for(ll i=2;i<=sqrt(x);i++)
	{
		if(x%i==0)return 0;
	}
	return 1;
 } 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	if(check(n))
	{
		cout<<"1\n";
		cout<<n;
		return 0;
	}
	if(n%2==0)
	{
		cout<<"2\n";
		for(ll i=n-1;i>=2;i--)
		{
			if(check(i))
			{
				ll k=n-i;
				if(check(k))
				{
					cout<<i<<" "<<k<<"\n";
					return 0;
				}
			}
		}
	}
	for(ll i=n-1;i>=2;i--)
	{
		if(check(i))
		{
			x=i;
			break;
		}
	}
	ll y=n-x;
	if(check(y))
	{
		cout<<"2\n";
		cout<<x<<" "<<y;
		return 0;
	}
	if(y%2==0)
	{
		cout<<"3\n";
		for(ll i=y-1;i>=2;i--)
		{
			if(check(i))
			{
				ll k=y-i;
				if(check(k))
				{
					cout<<i<<" "<<k<<" "<<x;
					return 0;
				}
			}
		}
	}
	
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

这道题要求把奇数 $n$ 分解为三个质数之和。

我们不难联想到，把 $n$ 减去任意一个奇质数，问题就可以转化为对偶数 $n_1$ 分解为两个质数，即哥德巴赫猜想了。

但这个奇素数还是有一定的限制的，毕竟哥德巴赫猜想需要进行暴力枚举，时间复杂度理论最大是 $O(n \sqrt{n})$（~~虽然远远远远跑不满，但我们要尊重理论上的极限复杂度分析嘛~~）所以我们奇质数越大越好。

根据素数分布的定理，在 $n \leq 10^9$ 范围内相邻两个质数的距离不会超过 $300$，可以看成一个常数很大的 $\log$（？

所以我们从 $n$ 倒着枚举，每次 $O(\sqrt{n})$ 暴力判断即可，找一个质数 $p$ 的时间复杂度 $O(\sqrt{w}\log{w})$（$w$ 为值域）。然后我们发现 $n'=n-p \leq 300$，暴力哥德巴赫猜想即可，复杂度 $O(\log{w}\sqrt{\log{w}})$。

这里注意哥德巴赫猜想中只满足 $\geq 4$ 的偶数，所以如果 $n=p$ 我们就输出 $n$ 就好了，$n=p+2$ 我们就输出 $p$ 和 $2$。

**理论**时间复杂度 $O(\sqrt{w}\log{w}+\log{w}\sqrt{\log{w}})$，实际远远跑不满。~~反正能过就行管他呢~~。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bool isprime(int x)
{
	if(x<2) return false;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}
int main()
{
	int n,flag=0; scanf("%d",&n);
	for(int i=n;i>=1;i--)
		if(isprime(i)) // 找质数
		{
			flag=i;
			break;
		}
	if(n==flag) // 判断 n=p
	{
		printf("1\n%d",n);
		return 0;
	}
	if(n==flag+2) // 判断 n=p+2
	{
		printf("2\n2 %d",n-2);
		return 0;
	}
	
	n-=flag; // 如果上述判断不成立，说明 n>=p+4，一定可以哥德巴赫猜想找到解。
	for(int i=2;i<=n;i++)
		if(isprime(i) && isprime(n-i))
		{
			printf("3\n%d %d %d",flag,i,n-i);
			return 0;
		}
	return 0;
}
```

顺便吐槽一下某些直接把 $n$ 减 3 暴力做的题解，这个是错误的，理论上不能通过，只是质数太多了只跑了一点点就找到了答案。

---

## 作者：Aehnuwx (赞：0)

一个很偶然的机遇发现了这道数论题。

竟然抢到了 $ 1A $，挺激动的。毕竟第一次嘛。

废话不多说，看题。

题目不难理解，就是给你一个奇数，让你用至多 $ 3 $ 个质数的和来表示它。

数据范围是 $ 10^9 $，乍一看无法用暴力解决此题。

然而我们转念一想：

“ $ CF $ 的机子，emmm”

再仔细看了看，回忆回忆自己学习的数论知识，确定无法用 $ O(1) $ 等时间复杂度较低的方法了（如果有请私信我，评论我有可能看不到）。

然后再想：怎么打暴力？

“一个**奇数**”、“质数**和**”

“woc这不是哥德巴赫猜想嘛”

没错，就是哥德巴赫猜想。

把原数减去一个 $ 3 $ ，然后直接暴力求解就星了。

$ \rm code $

```cpp
# include <bits/stdc++.h>
inline void xhw();
using namespace std;
inline bool is_prime(int);
int n;
int main() {
	xhw();
	return 0;
}
void xhw() {
	scanf("%d", &n);
	if(n == 3) {
		puts("1");
		puts("3");
		return;
	}
	if(n == 5) {
		puts("1");
		puts("5");
		return;
	}
	if(n == 7) {
		puts("1");
		puts("7");
		return;
	}//先来一堆特判
	puts("3");
	printf("3 ");
	n -= 3; //将n减去3
	for(register int i = 2; i < n - 1; i ++)
		if(is_prime(i) && is_prime(n - i)) { //直接用朴素判断素数算法跑暴力
			printf("%d %d", i, n - i);
			return;
		}
}
inline bool is_prime(int x) {
	for(register int i = 2; i * i <= x; i ++)
		if(x % i == 0) return false;
	return true;
}
```

最后，鸣谢 $ CF $ 评测机。（笑）（逃

---

## 作者：寒冰大大 (赞：0)

### 关于弱哥德巴赫猜想

> 任何一个大于7的奇数都能被表示成三个奇质数的和。（一个质数可以被多次使用）

因此： 对于5 

> 5=2+3  
>
> 5=5

对于3

> 3=3

于是问题似乎变成了弱哥德巴赫猜想

> 2013年5月，巴黎高等师范学院巴黎高等师范学院研究员哈洛德·贺欧夫各特发表了两篇论文，宣布彻底证明了弱哥德巴赫猜想弱哥德巴赫猜想。

~~于是本题变成了绿题~~

于是我们设第一个为3

然后变成了两个质数在大于4的合数上分解

N=4，2+2;

为什么要设第一个数=3 ?

当N=1e9时候，N^(7/120)≈3.34

当第一个为3是，后面就变成了哥德巴赫猜想，在long long 内绝对有解。

> ### 三素数定理
>
> 我们可以把这个问题反过来思考：如果偶数的哥德巴赫猜想正确，那么奇数的猜想也正确。已知奇数N可以表成三个素数之和，假如又能证明这三个素数中有一个非常小，譬如说第一个素数可以总取3，那么我们也就证明了偶数的哥德巴赫猜想。这个思想促使潘承洞先生在1959年，25岁时，研究有一个小素变数的三素数定理。这个小素变数不超过N的θ次方。我们的目标是要证明θ可以取0，即这个小素变数有界，从而推出偶数的哥德巴赫猜想。潘承洞先生首先证明θ可取1/4。后来的很长一段时间内，这方面的工作一直没有进展，直到1995年展涛教授把潘老师的定理推进到7/120。这个数已经比较小了，但是仍然大于0。



最后，由于素数密度较大，所以基本上第二个和第三个差值在5000以内，因此用N sqrt(N)的方法都不会挂。

代发如下

```cpp
#include<ThinkByYourself>

using namespace std;

int n,a,b,c;

inline int pri(int x)
{
	register int i;
	for(i=2;i<=sqrt(x);i++)
	if(x%i==0) return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	cin>>n;
	a=3;
	if(n==3)  //刚开始没特判结果WA了
	{
		cout<<1<<endl;
		cout<<3;
		return 0;
	}
	if(n==5)
	{
		cout<<1<<endl;
		cout<<5;
		return 0;
	}
	if(n==7)
	{
		cout<<1<<endl;
		cout<<7;
		return 0;
	}
	n-=3;
	b=n/2;
	c=n/2;
	if((n/2)%2==0)  //b,c都是合数除了N=4其他都可以发现b,c必然不是质数
	{
		b--;
		c++;
	}
	for(;c<=n-3&&b>=3;b-=2,c+=2)
	{
		if(pri(b)&&pri(c)) 
		{
			cout<<3<<endl;
			cout<<a<<" "<<b<<" "<<c;
			return 0;
		}
	}
	return 0;
}
```


---

