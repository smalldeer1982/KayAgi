# A and B

## 题目描述

### 题意

有二整数 $a$ 和 $b$。你可以执行无数次操作，使得 $a$ 与 $b$ 相等。

操作如下：对于第 $k$ 次操作，你可以让 $a$ 或 $b$ 增加 $k$。

求使得 $a$ 和 $b$ 相等的最少操作数。

## 说明/提示

$1 \leq T \leq 100$

$1 \leq a,b \leq 10^9$

## 样例 #1

### 输入

```
3
1 3
11 11
30 20
```

### 输出

```
3
0
4
```

# 题解

## 作者：wsmsmm (赞：24)

 _（为小白准备的简单易懂题解）_ 如果感觉其他的题解有些费脑，那这里咱们就从头来分析一遍哦。

### 题意：

给定 $a$、$b$，能进行无数次操作，对于第 $i$ 次操作可以往 $a$ 或 $b$ 上加 $i$（例如，第$1$次向某个数上加$1$，第$2$次向某个数上加$2$，以此类推，第 $n$ 次向某个数上加数字 $n$ ），直到加上某个数后 $a$ 和 $b$ 相等。求能使两数相等的最少步骤数。
### 分析：

首先，大部分人可能会像我一样，第一反应会认为是每一步都向较小数上进行加操作。但是很快我们就能举出反例：

 $a=1$，$b=3$。

 对于这两个数，我们最少步骤为：

 第一步在 $a$ 上加1，这时 $a=2$,$b=3$。

 第二步却是在较大数 $b$ 上加$2$，这时 $a=2$,$b=5$。

 第三步在 $a$ 上加$3$，$a=b=5$，求得最少步骤数为$3$，结束。

那么这样看来，具体第几个数要加在哪里就很玄学，让人摸不到头脑，不着急，咱们来再从头分析一下。

最初，我们对较小数进行加操作是为了缩小 $a$ 与 $b$ 的差，最终使 $a$ 等于 $b$。那么，我们就先不考虑在每一步中哪个数较小，而来考虑较本质的问题：第 $i$ 个数与 $a$ 和 $b$ 的差的关系。

这里，我们默认 $a$ 小于 $b$，那么 $a$ 和 $b$ 的差就为 $b-a$。咱们像别的题解一样，也来画个图看看。就以$1$和$3$为例，我们也把数字模拟为线段，将数一直向 $a$ 上加。
![](https://cdn.luogu.com.cn/upload/image_hosting/xw8w5h2t.png)

为什么我们在加完第$2$步后 $a$ 已经超过 $b$ 了，却没有停止呢？为什么我们加完$3$后又停止了呢？为什么我们要把$2$这个数分配到 $b$ 上去呢？

**为什么呢？这里看，$a$ 加$1$后仍比 $b$ 小；$a$ 加完$2$后，$a$、$b$ 差为$1$；$a$ 再加完$3$，$a$、$b$ 差为$4$！这时，我们是把$4$整除$2$得到的$2$移到了 $b$ 上。（大家可以多找几个数来自己模拟一下）几步模拟下来，我们的思路有点明确了，一直向 $a$ 进行加操作，一直加到 $a$ 大于等于 $b$，如果 $a$ 等于 $b$，问题就解决了；如果 $a$ 大于 $b$，那就把多出来那块平分！如果多出来的是奇数（无法被$2$整除），那就再加数加到多出来的部分为偶数，解决了！！**

所以，我们就从$1$枚举，while 的循环条件为 ```（a<b||(a-b)%2!=1）```
，意思就是，只要 $a$ 小于 $b$ 或 $a$ 大于 $b$ 但 $a$ 与 $b$ 的差不为偶数，那就还要接着枚举，直到满足条件，这时就是正确答案了！

接下来就是代码了，这里有个问题，我们前面的分析是默认 $a<b$ 的，所以我们对于每个 $a$ 和 $b$ 还要判断一下，不符合条件就互换，始终要使加法操作前的 $a<b$。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,a,b;
	cin>>n;
	for(int j=1;j<=n;j++)
	{
	cin>>a>>b;
	int i=0;
	if(a>b)
	swap(a,b);	
	while(a<b||(a-b)%2)//找到第一个满足条件的i
	{
		i++;
		a+=i;  
	}
    cout<<i<<endl;}
}
```
简单明了吧！最后，再解释一下为什么我们只要多出来的部分是偶数就一定可以平分掉：

对于加到第 $i$ 步后，$a>b$，需要平分的情况，多出来的部分 $c$ 是一定小于 $i+i+1$ 的，否则就不是最优解了。
而我们平分的部分就是 $\frac{c}{2}$，奇数不能被$2$整除，所以 $c$ 一定要是偶数，而 $\frac{c}{2}$ 就是是肯定小于等于 $i$ 的正整数，所以在 $i$ 之前，我们一定在 $a$ 上加过能凑成 $\frac{c}{2}$ 的数，进而就把这些数转移到 $b$ 上就行了。




---

## 作者：Dolphin_ (赞：8)

### $CF1278B$ 题解
这道题成功地吸引了我的注意力，于是和~~化竞~~巨佬一番讨论，得出了一个规律及其证明。
****
### 题意
给定两个数$a$和$b$，第$i$次的操作可以选一个数增加$i$（仅能增加i并且只能增加一次），求让$a$和$b$相等最小操作次数。
****
### 先说结论：
如果 $ a+b+i*(i+1)/2$是偶数 ，并且，$ a+b+i*(i+1)/2 $比 $ 2*max(a,b) $ 大，那么i++。最后算出的i即为答案。
****
### 那么这是为什么呢？？
证明$1$ : 我们可以把两个数想象成两条线段。一直对这两个数中较小的那个数$ +i$，直到最后的比另一个数大。于是我们可以反悔原来的策略，把一开始给较短的线段的长度放到较长的线段中去。由于之前的数包括$ [1,i]$,所以全部可以凑出。

证明$2$ : 因为当且仅当和是偶数时，$a$和$b$才有可能相等，所以如果和不是奇数时继续往后加，只要家到一个奇数就可以改变和当奇偶性，同时满足证明$1$ 。
#### 看图
![](https://cdn.luogu.com.cn/upload/image_hosting/e90lgk6w.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/azy58ab9.png)
********
### 只有一行的代码$ qwq$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll T,a,b,ans;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&a,&b);
        ans=0;
        while( !( (a+b+ans*(ans+1)/2)%2==0 && a+b+ans*(ans+1)/2>=2*max(a,b) ) ) ans++;
        printf("%lld\n",ans);
    }
    return 0;
}

---

## 作者：GIFBMP (赞：1)

首先贪心地想，我们要找到一个最小的非负整数 $k$，使得 $\dfrac{k(k+1)}{2}\ge |a-b|$。

我们设 $x=\dfrac{k(k+1)}{2}-|a-b|$，则有：

当 $x$ 为偶数时，显然有 $\dfrac{x}{2}\le k$，答案即为 $k$。

当 $x$ 为奇数时，我们考虑转化成偶数的情况。

当 $k+1$ 为奇数时，$x+k+1$ 为偶数，答案即为 $k+1$。

当 $k+1$ 为偶数时，$x+k+1+k+2$ 为偶数，答案即为 $k+2$。

Code：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std ;
int T , a , b ; 
long long sum[100010] ;
void swap (int &x , int &y) {
	x ^= y ^= x ^= y ;
}
int main () {
	scanf ("%d" , &T) ;
	for (int i = 1 ; i <= 1e5 ; i++) sum[i] = sum[i - 1] + i ;
	while (T--) {
		scanf ("%d %d" , &a , &b) ;
		if (a > b) swap (a , b) ;
		long long x = b - a ;
		int k = lower_bound (sum , sum + 100001 , x) - sum ;
		if ((sum[k] - x) & 1)
			if (k & 1) printf ("%d\n" , k + 2) ;
			else printf ("%d\n" , k + 1) ;
		else printf ("%d\n" , k) ;
	} 
	return 0 ;
}
```

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1278B)

## 题意

有 $2$ 个整数 $a$，$b$，你可以在第 $i$ 次操作给 $a$ 或 $b$ 增加 $i$，求最少的操作次数使得 $a$ 与 $b$ 相等。

## 分析

当 $a = b$ 时，$a+b=2a$，所以 $2 \mid a+b$，那么当 $a+b$ 为奇数时，就要进行一次加法，又当 $\min(a,b) < \max(a,b)$ 时也要进行加法，所以循环模拟这个过程即可，每次模拟将变量加 $1$ 记录次数，然后输出即可。 

## 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/onxdn3ls)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int a,b,i = 0,p;
		cin >> a >> b;
		p = min(a,b);
		b = max(a,b);
		a = p;//将a设为a，b中的较小值，b设为较大值
		while((abs(a + b) % 2) || (a < b))
		{
			i++;
			a += i;
		}
		cout << i << endl;
	}
}

```


---

## 作者：J_lim1307 (赞：0)

写在前面：本蒟蒻第三篇题解，望管理审核。
### 1.题意
很简单，给出一个 $T$，代表有 $T$ 组数据。然后输入 $a$ 和 $b$，对于第 $k$ 次操作，可以让 $a$ 或 $b$ 增加 $k$，求最小的操作次数。
### 2.思路
本人第一反应：无限地把所有的 $k$ 加到较小的数上。

但是并不行，样例的第一组数据举出了反例：

第一步：$1+1=2$，此时 $a=2$，$b=3$。

第二步：$3+2=5$，此时 $a=2$，$b=5$。

第三步：$2+3=5$，此时 $a=5$，$b=5$。

我们发现：当且仅当 $a$ 与 $b$ 的和是偶数时，$a$ 与 $b$ 才可能相等。若不是偶数，则继续往后加。这样，我们就得到了循环的条件：
$a<b$ 或 $a-b$ 为奇数。
### 3.步骤

输入：$a$ 和 $b$。

排序：保证 $a\le b$。

当 $a<b$ 或 $a-b$ 是奇数时循环，操作次数加一。
### 4.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int a,b;
int dick;
int main(){
	cin>>T;
	while(T--)
	{
		dick=0;
		cin>>a>>b;
		if(a>b)
		swap(a,b);
		while(a<b||abs(a-b)%2)
		{
			dick++;
			a+=dick;
		}
		cout<<dick<<endl;
	}
	return 0;
}
```
#### 感谢您的阅读！


---

## 作者：Tiago (赞：0)

## Solution

对样例换一种方式解释。

样例 $1$：

$a=1,b=3\to a=1+2,b=3$

此时相等，故最小操作数为 $2$。

样例 $2$ 不用解释。

样例 $3$：

$a=30,b=20\to a=30,b=20+1+2+3+4$

此时相等，故最小操作次数为 $4$。

这些样例不明确，再构造一组样例：

$a=5,b=22\to a=5+1+2+3+4+5+6=26>b=22$

此时注意到若将 $a$ 中的 $2$ 转移到 $b$ 上即可使 $a=b$。

再构造一组样例：

$a=5,b=23\to a=5+1+2+3+4+5+6=26>b=23$

发现无法将 $a$ 多出的部分均分，此时考虑继续加直至可以均分（可以证明最多加两次），然后多出部分均分即可。

推广至所有情况，发现只需使 $a$ 和 $b$ 的差值小于 $0$（假设 $a<b$，即要使 $a-b>0$）和差值为偶数即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

int a,b;
void solve()
{
	cin>>a>>b;
	int c=abs(a-b);
	int i=0,sum=0;
	while(sum<c || abs(sum-c)%2==1)sum+=(++i);
	cout<<i<<"\n";
}
int main()
{
	IOS;
	int T;cin>>T;
	while(T--)solve();

	return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

题意很简单，给定两个数 $a$ 和 $b$，第 $i$ 次操作可以选择其中的一个数增加 $i$，求使两数相等的最小操作次数。

蒟蒻狂喜思维题。

我们首先令 $a\leq b$，然后开始操作，使得 $a\geq b$，如果经过操作之后恰好 $a=b$，那就直接输出次数即可；如果变成 $a>b$，考虑回退操作。可以想到，如果令 $k=a-b$，我们可以在第 $\dfrac{k}{2}$ 步对 $a$ 不做操作，让 $b$ 做一个增加 $\dfrac{k}{2}$ 的操作就可以让两者平衡，这也是为什么我们要让 $a-b$ 为偶数的原因。于是乎我们只需要不停地让 $a$ 加到比 $b$ 大且两者之差是偶数即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		int a,b;cin>>a>>b;
		int ans=0;
		if(a>b) swap(a,b);
		while(a<b||abs(a-b)%2) ans++,a+=ans;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

这道题和 [CF11B Jumping Jack](https://www.luogu.com.cn/problem/CF11B) 的思路基本是一样的。建议去做做。

思路：

- 输入。

- 首先排大小，保证 $a\le b$。

- 先把目前的数都加到 $a$ 上直到 $a \ge b$。这里有两种情况：

- 第一种，$a=b$，直接输出答案。

- 第二种，$a>b$。我们可以看出，当 $(a-b)$ 为偶数时，设 $t=a-b$，我们可以回溯到第 $t$ 步。如果把这一步的 $t$ 加到 $b$ 上而不是 $a$ 上，那么 $a_n=a-t$ 且 $b_n=b+t$。代入 $t$ 可以得到 $a_n=b_n=(a+b)/2$。所以当 $(a-b)$ 为偶数时可以直接输出现在的 $t$！（因为 $t$ 也代表操作次数）

- 对于 $(a-b)$ 为奇数的情况，继续直到 $(a-b)$ 为偶数时即可。

所以答案很明显了。

[CF11B Jumping Jack](https://www.luogu.com.cn/problem/CF11B) 这道题不过是把上面过程中的 $a$ 改成了 $0$ 而已，相对来说更简单。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);//保证 a≤b 
		int times=0;
		while(a<b||(a-b)%2==1)times++,a+=times;//这里是判断
		printf("%d\n",times);
	}
	
	
	return 0;
} 
```

---

## 作者：TheOnlyMan (赞：0)

首先看题目知道它要让我们求的是用最少的数将两个数的差距填平。那我们可以这么想，我只对其中最小的数进行加数字的操作，因为对另一个数字加上一个正数效果等同于在原来的数字上减去这个正数（数字由 $1$ 到 $n$）。假设两个数分别为 $a$，$b$，$a$ 为其中较大的那个数，那我们可以先求出 $\sum_{i=1}^{n}i$ 大于 $a-b$ 的最小 $n$ 值，然后判断一下 $\sum_{i=1}^{n}i-(a-b)$ 的差是否为偶数，如果是偶数的话那么这就是最小答案，因为偶数是可以可以分解为两个相等的数的，刚好就是将加在 $b$ 上的累加和去掉一个改为负数；如果是奇数的话，在不超过2次的情况下就可以将刚才的差值转化为偶数，成为最小值。复杂度 $O(t)$。代码如下：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll; 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		ll a,b;
		cin>>a>>b;
		ll k=abs(a-b);
		ll p=ceil((-1+sqrt(1+8*k))/2.0);//求最小p值使1到p的和大于差值（求解p*(p+1)/2=k的方程即可）
		while(p*(p+1)/2-k&1)p++;//最多进行两次，因为遇到奇数便会把差值调为偶数
		cout<<p<<"\n";
	}
	return 0;
}
```


---

## 作者：F_Mu (赞：0)

**题意**

对于$t(1\leq t\leq 100)$个测试点，给两个数$a$和$b$，作如下操作：

第一次挑一个数使其加$1$，第二次挑一个数使其加$2$，以此类推，最后两个数相等，问最小操作数。

**分析**

题目所述意思即为挑选最小的$n$，满足以下等式$(\pm$表示可取正号可取负号$)$
$$
\pm1\pm2\pm3\pm\cdots\pm n= \left|a-b\right|\qquad(1)
$$
我们令$\left|a-b\right|$为$x$，我们先找到最小的$k$满足$\frac{k*(k+1)}{2}\geq x$，即$(1)$式中全为加号$($如果全为加号都不满足，其中一些变为减号肯定更不满足$)$。我们有一个以下式子
$$
1+2+\cdots+k=x+y\qquad(2)
$$
其中$y$为超过的部分。

$1.$如果$y$是偶数，我们已知$y<k$，否则不满足上述$k$最小。那么我们将$\frac{y}{2}$的符号变为负号即可满足$(1)$式，那么答案就是$k$。

$2.$如果$y$是奇数，那么该式子将一些正号变为负号也肯定不满足（改变后式子的值变化为偶数），我们往$(2)$式左右都加上$k+1$。

+ 如果$k+1$是偶数，那么$y+k+1$仍然为奇数，同上，仍不满足，我们需两边再加上$k+2$，$y+2*k+1$为偶数，我们将$\frac{y+1}{2}$和$k$的符号变为负号即可满足$(1)$式，$(\frac{y+1}{2}=k$显然不满足条件$)$，那么答案就是$k+2$。
+ 如果$k+1$是奇数，那么$y+k+1$为偶数，我们将$\frac{y+k+1}{2}(\frac{y+k+1}{2}<k+1)$的符号变为负号即可满足$(1)$式，那么答案就是$k+1$

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define LL long long
#define pii pair<int,int>
#define int ll
#define ls st<<1
#define rs st<<1|1
using namespace std;
const int maxn = (ll) 1e5 + 5;
const int mod = (ll) 1e9 + 7;
const int inf = 0x3f3f3f3f3f3f3f3f;
int sum[maxn];

signed main() {
    start;
    for (int i = 1; i < maxn; ++i)
        sum[i] = sum[i - 1] + i;
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        int x = b - a;
        int ans = lower_bound(sum, sum + maxn, x) - sum;
        if ((sum[ans] - x) & 1) {
            if (ans & 1)
                cout << ans + 2 << '\n';
            else
                cout << ans + 1 << '\n';
        } else
            cout << ans << '\n';
    }
    return 0;
}
```

---

