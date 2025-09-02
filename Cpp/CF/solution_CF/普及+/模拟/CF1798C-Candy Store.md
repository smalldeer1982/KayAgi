# Candy Store

## 题目描述

The store sells $ n $ types of candies with numbers from $ 1 $ to $ n $ . One candy of type $ i $ costs $ b_i $ coins. In total, there are $ a_i $ candies of type $ i $ in the store.

You need to pack all available candies in packs, each pack should contain only one type of candies. Formally, for each type of candy $ i $ you need to choose the integer $ d_i $ , denoting the number of type $ i $ candies in one pack, so that $ a_i $ is divided without remainder by $ d_i $ .

Then the cost of one pack of candies of type $ i $ will be equal to $ b_i \cdot d_i $ . Let's denote this cost by $ c_i $ , that is, $ c_i = b_i \cdot d_i $ .

After packaging, packs will be placed on the shelf. Consider the cost of the packs placed on the shelf, in order $ c_1, c_2, \ldots, c_n $ . Price tags will be used to describe costs of the packs. One price tag can describe the cost of all packs from $ l $ to $ r $ inclusive if $ c_l = c_{l+1} = \ldots = c_r $ . Each of the packs from $ 1 $ to $ n $ must be described by at least one price tag. For example, if $ c_1, \ldots, c_n = [4, 4, 2, 4, 4] $ , to describe all the packs, a $ 3 $ price tags will be enough, the first price tag describes the packs $ 1, 2 $ , the second: $ 3 $ , the third: $ 4, 5 $ .

You are given the integers $ a_1, b_1, a_2, b_2, \ldots, a_n, b_n $ . Your task is to choose integers $ d_i $ so that $ a_i $ is divisible by $ d_i $ for all $ i $ , and the required number of price tags to describe the values of $ c_1, c_2, \ldots, c_n $ is the minimum possible.

For a better understanding of the statement, look at the illustration of the first test case of the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1798C/1160d0ae9da0a28139cfb8794bbbd0911d44c66f.png)Let's repeat the meaning of the notation used in the problem:

 $ a_i $ — the number of candies of type $ i $ available in the store.

 $ b_i $ — the cost of one candy of type $ i $ .

 $ d_i $ — the number of candies of type $ i $ in one pack.

 $ c_i $ — the cost of one pack of candies of type $ i $ is expressed by the formula $ c_i = b_i \cdot d_i $ .

## 说明/提示

In the first test case, you can choose $ d_1 = 4 $ , $ d_2 = 6 $ , $ d_3 = 7 $ , $ d_4 = 5 $ . Then the cost of packs will be equal to $ [12, 12, 35, 35] $ . $ 2 $ price tags are enough to describe them, the first price tag for $ c_1, c_2 $ and the second price tag for $ c_3, c_4 $ . It can be shown that with any correct choice of $ d_i $ , at least $ 2 $ of the price tag will be needed to describe all the packs. Also note that this example is illustrated by a picture in the statement.

In the second test case, with $ d_1 = 4 $ , $ d_2 = 2 $ , $ d_3 = 10 $ , the costs of all packs will be equal to $ 20 $ . Thus, $ 1 $ price tag is enough to describe all the packs. Note that $ a_i $ is divisible by $ d_i $ for all $ i $ , which is necessary condition.

In the third test case, it is not difficult to understand that one price tag can be used to describe $ 2 $ nd, $ 3 $ rd and $ 4 $ th packs. And additionally a price tag for pack $ 1 $ and pack $ 5 $ . Total: $ 3 $ price tags.

## 样例 #1

### 输入

```
5
4
20 3
6 2
14 5
20 7
3
444 5
2002 10
2020 2
5
7 7
6 5
15 2
10 3
7 7
5
10 1
11 5
5 1
2 2
8 2
6
7 12
12 3
5 3
9 12
9 3
1000000000 10000```

### 输出

```
2
1
3
2
5```

# 题解

## 作者：一扶苏一 (赞：11)

# Candy Store

## Description

有 $n$ 种糖，第 $i$ 种糖有 $a_i$ 块，每块 $b_i$ 元。对每种糖，你要选择一个 $d_i | a_i$，然后每 $d_i$ 块糖装进一个袋子。

现在把糖摆上货架，第 $i$ 类糖的价签上的价格 $c_i$ 是一袋子 $i$ 类糖的价值，即 $c_i = d_i \times b_i$。

对于货架上一个区间 $[l, r]$，如果他们的价签相同，即 $c_l = c_{l + 1} = \dots = c_r$，则他们可以共用一个价签。

请问最少需要多少价签？

多组数据，保证 $n$ 之和不超过 $2 \times 10^5$，$1 \leq a_i \leq 10^9$，$1 \leq b_i \leq 10^4$。

## Analysis

对我来说是个有点新的题，以前没做过这样的，vp 时考虑了很久大力 dp。

考虑一段能共用同一个价签 $c$ 的区间 $[l, r]$，有 $c = b_l d_l = b_{l + 1}d_{l + 1} = \dots b_r d_r$。于是显然 $\mathrm{lcm}_{i=l}^r b_i | c$。

再考虑构造出的 $d_i | a_i$，而 $d_i = \frac{c}{b_i}$。于是 $\frac{c}{b_i} | a_i$，即 $c | a_i b_i$。于是 $c | \gcd_{i = l}^r a_ib_i$。

于是一个区间能共用一个价签的条件就是 $\mathrm{lcm}(b_l, b_{l + 1}, \dots b_r) | \gcd(a_lb_l, a_{l+1}b_{l+1}, \dots a_rb_r)$。

下一个问题是怎么安排价签。这是一个简单的贪心：只需要从最左端开始，每次尽可能地把多的糖果共用一个价签即可。证明上可以考虑如果为了后面某段区间调整了前面的价格，会多出一个区间端点，然后减少一个区间端点，答案不会变优。

## Code

cpp17 里的 `numeric` 库提供了 `std::gcd` 和 `std::lcm` 两个库函数，从此无需再使用 `std::__gcd` 了。但遗憾的是 NOI 系列赛事只有 cpp14 可用。

```cpp
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

int T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ++ans;
      long long x = b[i], y = 1ll * a[i] * b[i];
      for (int j = i + 1; j <= n; ++j) {
        x = std::lcm(1ll * b[j], x);
        y = std::gcd(y, 1ll * a[j] * b[j]);
        if (y % x != 0) {
          i = j - 1; break;
        }
        if (j == n) {
          i = j; break;
        }
      }
    }
    std::cout << ans << '\n';
  }
}
```

---

## 作者：inc1ude_c (赞：8)

考虑在什么情况下，$l\sim r$ 的糖果可以使用同一标签。

设这个标签值为 $c$，因为要满足每一个 $c=b_i\times d_i$，所以对于每一个 $b_i$ 都要满足 $c\mod b_i=0$。于是，$c$ 应该是 $\text{lcm}(b_l,\cdots ,b_r)$ 的倍数。

同时，又要满足每一个 $a_i\mod d_i=0$，而 $d_i=\frac{c}{b_i}$，所以 $a_i\mod \frac{c}{b_i}=0$，推出 $a_i\times b_i\mod c=0$。于是，$c$ 应该是 $\gcd(a_l\times b_l,\cdots,a_r\times b_r)$ 的因数。

于是，想要构造一个合法的 $c$，当且仅当 $\gcd(a_l\times b_l,\cdots,a_r\times b_r)\mod \text{lcm}(b_l,\cdots ,b_r)=0$。

答案的计算也便显而易见了。

[Code](https://codeforces.com/contest/1798/submission/199426735)

---

## 作者：Hisaishi_Kanade (赞：2)

假设我们能让 $[l,r]$ 为一个价签（以下约定 $l\le i\le r$），考虑 $c_i$ 此时满足什么条件？

+ 由题意，$c_i=b_i\times d_i$。

+ 先看 $b_i$，显然，$b_{i}\mid c_i$，则 $\text{lcm} \{b_i\}\mid c_i$。

+ 再考虑 $d_i$，由于 $d_{i}\mid a_i$，那么 $(b_i\times d_i)\mid (a_{i}\times b_i)$，即 $c_{i}\mid (a_i\times b_i)$。进一步推得，$c_{i}\mid \gcd\{a_i\times b_i\}$。

综上，有 $\text{lcm}\{b_i\}\mid \gcd\{a_{i}\times b_i\}$，就能有合法的 $c_i$ 存在。

接下来考虑贪心：从左端点开始，取尽可能多的糖果求得右端点，下一次的左端点是这次的右端点加一。

为什么是正确的呢？

如果我前一段不取尽可能多，那么留给下一段的糖果会变多，也就是条件更加“严格”了，显然不会更优。
```cpp
/*
i in [l,r]
c[i]=b[i]*d[i]
b[i] | c[i]
lcm(b[i]) | c[i]
d[i] | a[i]
c[i] | gcd(a[i]*b[i])
therefore lcm(b[i]) | gcd(a[i]*b[i])
*/
#include <stdio.h>
using ll=long long;
inline ll gcd(ll x,ll y){return !y?x:gcd(y,x%y);}
inline ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
int t,n,i,j,cnt;
ll a[200005],b[200005];
ll fx,fy;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cnt=0;
		scanf("%d",&n);
		for(i=1;i<=n;++i)
			scanf("%d %d",a+i,b+i);
		for(i=1;i<=n;)
		{
			fx=b[i];
			fy=a[i]*b[i];
			for(j=i+1;j<=n;++j)
			{
				fx=lcm(fx,b[j]);
				fy=gcd(fy,a[j]*b[j]);
				if(fy%fx!=0)
				{
					i=j;
					break;
				}
			}
			++cnt;
			if(j>n)
				break;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：Larryyu (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1798C)
## _Description_
商店里有 $n$ 种糖果，每种糖果有 $a_i$ 颗，价格为 $b_i$ 每颗。

现在需要将每种糖果分成若干包，每包的数量 $d_i$ 要一样。第 $i$ 种糖果最终标价为 $c_i=d_i\times b_i$，一个价格标签可以概括 $l$ 到 $r$ 种糖果当且仅当 $c_l=c_{l+1}=\dots=c_r$，问最少需要多少个标签。

注意，问的是标签数量，不是价格有多少种。

假设价格依次为 $c_1=4,c_2=4,c_3=2,c_4=4,c_5=4$，则可以用三个标签 $4,2,4$ 来概括，数量为 $3$，而不是 $2$。
## _Solution_
假设 一个标签 $tag$ 概括了 $l$ 到 $r$ 种糖果的标签，则 $tag=c_{l\sim r}$。

$\because c_i=d_i\times b_i$，

$\therefore tag$ 能被 $b_{l\sim r}$ 整除

$\therefore \operatorname{lcm}(b_l,b_{l+1}\dots b_r)\mid tag$

$\because d_i\mid a_i$

$\therefore c_i\mid a_i\times b_i$

$\therefore tag\mid \gcd(a_i\times b_i,a_{i+1}\times b_{i+1}\dots a_r\times b_r)$

$\therefore \operatorname{lcm}(b_l,b_{l+1}\dots b_r)\mid \gcd(a_i\times b_i,a_{i+1}\times b_{i+1}\dots a_r\times b_r)$

所以只要判断当前 $\gcd(\dots)$ 是否能被 $\operatorname{lcm}(\dots)$ 整除即可，如果不能，就相当于进入了下一个标签，将 $\gcd(\dots)$ 更新成 $a_i\times b_i$，$\operatorname{lcm}(\dots)$ 更新成 $b_i$。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //记得开long long
int t;
int a[200200],b[200200];
int gcd(int x,int y){
	if(y==0) return x;
	return gcd(y,x%y);
}
int lcm(int x,int y){
	return x*y/gcd(x,y);
}
void solve(){
	int n,ansg=0,ansl=1,cnt=1; //注意gcd和lcm的初始化，以及标签至少有一个
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++){
		ansg=gcd(ansg,a[i]*b[i]);
		ansl=lcm(ansl,b[i]);
		if((ansg%ansl)!=0){ //下一个标签，更新gcd和lcm
			ansg=a[i]*b[i];
			ansl=b[i];
			cnt++;
		}
	}
	cout<<cnt<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
}
```

---

## 作者：ncwzdlsd (赞：1)

考虑一个区间 $[l,r]$ 是可以满足的，当且仅当该区间的公共价签 $c$ 满足条件 $c=b_i d_i,i\in [l,r]$，可得 $\text{lcm}_{i\in[l,r]}b_i|c$。

再考虑对于 $d$ 的限制，要求 $d_i|a_i$，即 $\dfrac{c}{b_i}|a_i$，于是有 $c|a_i b_i$。那么显然有 $c|\gcd_{i\in [l,r]}(a_i,b_i)$。

于是得到最终的限制条件：

$$
\text{lcm}_{i\in[l,r]}b_i|\gcd_{i\in [l,r]}(a_i,b_i)
$$

要求公共价签数最小，最大化每一段满足条件的区间的长即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+5;
int a[maxn],b[maxn];

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

int lcm(int x,int y){return x*y/__gcd(x,y);}

void solve()
{
    int n=read();
    int ans=1;
    for(int i=1;i<=n;i++) a[i]=read(),b[i]=read();
    int t1=a[1]*b[1],t2=b[1];
    for(int i=2;i<=n;i++)
    {
        t1=__gcd(t1,(int)a[i]*b[i]),t2=lcm(t2,b[i]);
        if(t1%t2) t1=a[i]*b[i],t2=b[i],ans++;
    }
    cout<<ans<<endl;
}

signed main()
{
    int t=read();
    while(t--) solve();
    return 0;
}
```

---

## 作者：OMG_NOIP (赞：0)

#### 首先考虑在什么情况下只用一个价格标签

设 $cost$ 为这个价格标签，即 $cost=d_1\times b_1=d_n\times b_n=\cdots=d_n\times b_n$。

可以看出 $cost$ 能够被任意 $b_i(1 \le i \le n)$ 整除，所以 $cost$ 被 $\operatorname{lcm}(b_1,b_2,\cdots,b_n)$ 整除，其中 $\operatorname{lcm}$ 表示最小共倍数。

根据题意：$a_i$ 可以被 $d_i$ 整除，两边同乘以 $b_i$ 后就等价于 $a_i\times b_i$ 可以被 $d_i\times b_i$ 整除。$d_i\times b_i$ 不就是 $cost$ 吗？所以对于 $(1 \le i \le n)$ 都有 $a_i \times b_i$ 可以被 $cost$ 整除。所以 $\gcd(a_i \times b_i)(1 \le i \le n)$ 可以被 $cost$ 整除。

因为：

$\gcd(a_i \times b_i)(1 \le i \le n)$ 可以被 $cost$ 整除。  
$cost$ 可以被 $\operatorname{lcm}(b_1,b_2,\cdots,b_n)$ 整除。

所以只用一个价格标签的情况是：

$\gcd(a_i \times b_i)(1 \le i \le n)$ 可以被 $\operatorname{lcm}(b_1,b_2,\cdots,b_n)$ 整除。

### 理解了以上的，再来看下面的

不难理解，如果一组糖果只需要一个价格标签，那么如果从该组中移除任何一种糖果，仍然只需要一个价格标签。

这意味着一个简单的贪心算法将会奏效。让我们选择最大的前缀糖果，使得一个价格标签足以覆盖它，为这个前缀“贴”一个价格标签，并重复剩余糖果，直到数组结束。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n , a[2000005] , b[2000005] ;
ll __lcm(ll a , ll b){
	return a * b / __gcd ( a , b ) ;
}
void work(){
	cin >> n ;
	for(ll i = 1 ; i <= n ; i ++ )cin >> a[i] >> b[i] ;
	ll ans = 0 , k1 = a[1] * b[1] , k2 = b[1] ;
	for(ll i = 2 ; i <= n ; i ++ ){
		k1 = __gcd( k1 , a[i] * b[i] ) ;
		k2 = __lcm( k2 , b[i] ) ;
		if( k1 % k2 != 0 ){
			ans ++ ;
			k1 = a[i] * b[i] ;
			k2 = b[i] ;
		}
	}
	ans ++ ; // 更新最后面的一个价格标签 
	cout << ans << endl ;
}
signed main(){
	ios::sync_with_stdio(false);
	ll T ; cin >> T ;
	while(T--)work();
	return 0;
}
```
~~冒昧问一句，我的码风好看吗？~~

---

## 作者：cqbzhr (赞：0)

要使得 $[l,r]$ 能合成一个标签，很清楚 $c_i$ 是一个关键（已知 $c_i=b_i\times d_i$）。

- $c_i\bmod b_i=0$。
- $c_i \bmod \operatorname{lcm}(b_i,\dots,b_j)=0$。

那么就相当于 $\gcd(a_i,\dots,a_j)\bmod \operatorname{lcm}(b_i,\dots,b_j)=0$。

那么代码实现就显而易见了。

### 上代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans,a[200005],b[200005];
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=1;
		for(int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
		}
		int k=0,x=1;
        for(int i=1;i<=n;i++){
            k=gcd(k,a[i]*b[i]),x=lcm(x,b[i]);
            if(k%x!=0){
                k=a[i]*b[i];
                x=b[i];
                ans++;
            }
        }
        cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ForgotDream_CHN (赞：0)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17638176.html)

昨晚 VP 的时候想了半个多小时的怎么卡质因数分解的常。

> 给定两个长度为 $n$ 的序列 $a$ 与 $b$，对每一个 $i$ 固定一个 $d_i$，使得 $d_i \mid a_i$。将 $b_i \times d_i$ 记为一个新的序列 $c$，你要使得 $c$ 的连续段最少。  
> $n \le 10^5$，$a_i \le 10^9$，$b_i \le 2 \times 10^4$。

我们考虑一个贪心：每次都尽量向后走，直到走到无法满足题目要求的 $i$ 为止，再 $ans \gets ans + 1$，另起一段，直到走完整个序列。容易证明贪心的正确性，现在需要考虑的就是如何验证是否存在满足条件的 $c_i$。

对于合法的一段 $[l, r]$，我们设其对应的 $c_i$ 为 $c$，合法的要求是对于每一个 $i \in [l, r]$，都有 $d_i \mid a_i$，也就是 $c_i \mid a_i \times b_i$，那么显然，如果 $\gcd_{l \le i \le r} a_i \times b_i$ 是 $c$ 的倍数的话，$[l, r]$ 这一段才合法。显然有对于任意的 $i \in [l, r]$，都有 $b_i \mid c$。那么我们容易看出最小的，也是最优的 $c$ 为 $\operatorname{lcm}_{l \le i \le r} b_i$。那么 $[l, r]$ 这一段合法等价于 $\operatorname{lcm}_{l \le i \le r} b_i | \gcd_{l \le i \le r} a_i \times b_i$，贪心即可做到 $\mathcal{O}(n \log |S|)$，其中 $|S|$ 为值域大小。

[代码](https://codeforces.com/contest/1798/submission/219111802)

---

## 作者：masonpop (赞：0)

小数学题。

首先有一个很明显的贪心就是，每次选取尽量长的区间贴一个标签，正确性是显然的。

接下来就考虑判定区间 $[l,r]$ 是否能贴一个标签。设 $b_ld_l=b_{l+1}d_{l+1}=\cdots=b_rd_r=w$。则对任意 $i$，有 $b_i|w$。然后对任意 $i$，有 $d_i|a_i$，即 $w|a_ib_i$。综合可得，$\text{lcm}(b_l,b_{l+1},\cdots,b_r)|w$ 且 $w|\gcd(a_lb_l,a_{l+1}b_{l+1},\cdots,a_rb_r)$。存在这样的 $w$ 即等价于 $\text{lcm}(b_l,b_{l+1},\cdots,b_r)|\gcd(a_lb_l,a_{l+1}b_{l+1},\cdots,a_rb_r)$。

边选取边维护区间 $\gcd$ 及 $\text{lcm}$ 即可。[代码](https://codeforces.com/contest/1798/submission/218797523)。

---

## 作者：Pwtking (赞：0)

首先考虑贪心，即为怎样能使价签数最小。

我们**从前往后扫，判断我们扫到的下标是否能和前面的区间合并**，这样的结果一定是最优的。

为什么？

因为我们每次把一个新数加入原有集合，就相当于对下一次加入这个集合的数加了“限制”（看了下文你自然会懂），我们若不按从前往后的顺序扫，那么这个数就会影响我下一个新的集合，所以不如从前往后扫更优。

接下来考虑怎么去扫。

如果想让两个 $c1$，$c2$ 相等，那么肯定要让 $c1$，$c2$ 分别除以 $b1$，$b2$ 的值为整数，即为 $b1$，$b2$ 的公倍数。显然我们知道若想合法则这个公倍数越小越好，也即是我们的 $c$ 应为 $b1$，$b2$ 的最小公倍数。同时应该满足 $a1$，$a2$ 分别除以 $\frac{c}{b1} $，$\frac{c}{b2} $ 的值为整数。那么在从前往后扫的过程中，即为在 $\forall i\in\left [l  ,r\right ]$，$\gcd (a_{i}\times b_{i}) \operatorname{mod}\operatorname{lcm}b_{i} $ 的情况下，才存在一个相同的 $c$ 值使其合法。

---

## 作者：Benzenesir (赞：0)

我们不难发现，有一个基本的贪心策略，若我们有一个打好的包，我们要尽可能的把更多的物品放进去。

同时，正难则反，我们想象一下，如果有一个打好的包，其价格为 `w`，则 `w` 要满足什么性质。

首先，$\forall b_i \, , b_i \mid w $。

这个条件等价于 $ \text{lcm} (b_i) \mid w $。

同时，有 $\forall a_i , \frac{w}{b_i}\mid a_i$。

这个条件也可以等价于 $w \mid \gcd(a_i\times b_i) $。

两个条件综合一下，就是看 $\text{lcm}(b_i)$ 是否整除 $\gcd(a_i\times b_i)$，如果是，则一定可以打成一包。

所以我们就贪心的加入，直到不能加入为止。

```
#include <iostream>
#include <vector> 
#include <map>
#include <algorithm>
#define int unsigned long long 

using namespace std;
const int maxN=2*1e5+10;
int n,m;
int a[maxN],b[maxN];

inline int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}

void solve(){
	cin >> n;
	for(int i=1;i<=n;++i)cin >> a[i] >> b[i];
	int lm=b[1],gd=a[1]*b[1],ans=1;
	for(int i=2;i<=n;++i){
		int p=(lm*b[i])/gcd(lm,b[i]),q=gcd(a[i]*b[i],gd);
		if(q%p!=0ll){
			lm=b[i],gd=a[i]*b[i];
			++ans;
		}
		else lm=p,gd=q;
	}
	cout << ans << endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int t;
	cin >> t;
	while(t--){
		solve();
	} 
	return 0;
} 
```

---

## 作者：bmatrix (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1798C)

形式化题意：
> 给出长为 $n$ 的两个序列 $\{a\}$ 和 $\{b\}$，定义序列 $\{c\}$ 满足：$c_i=d_ib_i$，其中 $d_i\mid a_i$。求 $\{c\}$ 最少能被分成多少个连续段，使得每个连续段内的值相同。

首先对于一个 $i$，如果 $c_i$ 能和 $c_{i-1}$ 分到同一个段里，那么一定优于它单独成段或者和 $c_{i+1}$ 分到同一段里。因为在一个段里加一个数只会让这个段的限制更紧。

基于这个贪心有了一个思路：对于一个左端点 $l$，找到它能形成的最长合法连续段的右端点 $r$，然后令 $ans\leftarrow ans+1,l\leftarrow r+1$ 继续直到 $l>n$。

现在问题来到对于一个 $l$，如何快速求 $r$。

不妨对 $\{c\}$ 的构造方式做一下转化：$c_i=\dfrac{a_ib_i}{e_i}$，其中 $e_i\mid a_i$。由此可以发现，如果一个区间 $[l,r]$ 合法，则这个区间的 $c$ 值一定是 $\gcd\limits_{i=l}^ra_ib_i$ 的约数，并且显然取最大公约数是最优的，由此可以求出每个 $i$ 对应的 $e$。同时不难发现 $r$ 的出现满足可二分性，因此只要 ST 表求区间 $\gcd$，二分答案即可。

[赛时 AC 记录](https://codeforces.com/contest/1798/submission/199272356)。

时间复杂度分析：ST 表初始化是 $O(n\log^2 n)$。设 $len=r-l+1$，由于 `check` 在检测到不合法后立即返回，所以 `check` 一次的复杂度是 $O(len)$，二分一次就是 $O(len\log n)$，又因为 $\sum len=n$，所以二分答案总时间复杂度为 $O(n\log n)$。程序总复杂度为 $O(n\log^2 n)$。常数好像挺小的。

---

