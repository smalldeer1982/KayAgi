# Birthday

## 题目描述

Ivan is collecting coins. There are only $ N $ different collectible coins, Ivan has $ K $ of them. He will be celebrating his birthday soon, so all his $ M $ freinds decided to gift him coins. They all agreed to three terms:

- Everyone must gift as many coins as others.
- All coins given to Ivan must be different.
- Not less than $ L $ coins from gifts altogether, must be new in Ivan's collection.

But his friends don't know which coins have Ivan already got in his collection. They don't want to spend money so they want to buy minimum quantity of coins, that satisfy all terms, irrespective of the Ivan's collection. Help them to find this minimum number of coins or define it's not possible to meet all the terms.

## 说明/提示

In the first test, one coin from each friend is enough, as he will be presented with 15 different coins and 13 of them will definitely be new.

In the second test, Ivan has 11 friends, but there are only 10 different coins. So all friends can't present him different coins.

## 样例 #1

### 输入

```
20 15 2 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
10 11 2 4
```

### 输出

```
-1```

# 题解

## 作者：xiaozeyu (赞：5)

**WA的人注意了，这题的翻译其实有些小的错误，让人一直错**

题目中给的翻译

>每个人都要送一样多的硬币

>每个硬币都必须是不同的

>所有人送的纪念币总量不少于 $L$ ，而且都要是 $Ivan$ 没有的。

但是**原来的意思不是这样**的啊

看一下第三句的原句：

- Not less than $L$ coins from gifts altogether, must be new in Ivan's collection.

这个逗号后面的是前面的从句啊！

**应该这样翻译：**

- 所有人送的硬币中至少有$L$个是伊万没有的

也就是说，可以有他已经有的

**就是所有朋友要送给他至少 $ k+l $个纪念币**

一开始理解错误时这么写：

```cpp
if(k+l>n||k+m>n)printf("-1");
	else
	{
		for(int i=1;m*i+k<=n;i++)
		{
			if(m*i>=l) 
			{
				cout<<i;
				return 0;
			}
		}
		cout<<"-1";
	}
```
因为被题目误导了而错了，

正确理解题目后的正解
```cpp

#include<bits/stdc++.h>
#define For(i,a,b) for(register long long i=a;i<=b;i++)
#define Rep(i,a,b) for(register long long i=a;i>=b;i--)
using namespace std;
inline long long read()
{
	char c=getchar();long long x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
long long n,m,k,l,ans;
int main()
{
	//freopen("coin.in","r",stdin);
	//freopen("coin.out","w",stdout);
	n=read();m=read();k=read();l=read();
	if(n<m||n-k<l)
	{
		printf("-1\n");
		return 0;
	}
	ans=(k+l)/m;
	if(ans*m<k+l) ans++;
	if(ans*m<=n) printf("%lld\n",ans);
	else printf("-1\n");
}

```
但在写的过程中还遇到过一些问题

比如：

 1.见祖宗错误
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,l;
int main()
{
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
	cin>>n>>m>>k>>l;
	int y=n/m;
	if(n<m)
	{
		cout<<"-1";
		return 0;
	}
	else if(k+l>n)
	{
		cout<<"-1";
		return 0;
	}
	else if(y*m<k+l)
	{
		cout<<"-1";
		return 0;
	}
	else
	{
		int b=k+l,bb=b/m;
		if(b%m==0) cout<<bb;
		else cout<<bb+1;
	}
	return 0;
}
```

这题是$10^{18}$级别的,int直接爆炸

2. 最后特判


当时用了
```cpp
long long t=ceil((double)(k+l)/m);
```
直接WA，为什么，不是转换了吗？

ceil返回的是floor/double，直接爆炸

正确写法：
```cpp
ans=(k+l)/m;
	if(ans*m<k+l) ans++;
```


------------

最后，**感谢管理的审核**，希望看到的人能规避一些**题意（翻译）和方法**带来的错误

记得点个赞在走φ(≧ω≦*)♪ ヾ(≧O≦)〃嗷~

---

## 作者：damage (赞：5)

~~好像并没有那么难（好吧我真的是蒟蒻）~~

# 题解

很容易发现，当满足一下情况时，会产生无解的情况：

1. $n\lt{m}$，即纪念币数比朋友数还少~~（这么好的人缘啊）~~，每个朋友连一个都送不了，所以当然无解了。

2. $n-k\lt{l}$，$n-k$表示剩下可以送的纪念币总数，当可以送的纪念币总数比需要的还小时，当然也无解了。

接下来设定答案$res$为$\frac{k+l}{m}$，就是平均每个朋友要给的纪念币数量，因为有$k$种纪念币没有办法送，所以是$\frac{\bold{k+}l}{m}$。

但是整型除法会有精度损失，所以朋友们送的纪念币总数$res\times{m}$有可能比$k+l$小，所以此时就要```++res```

然后还是有两种情况：

1. $res\times{m}\leq{n}$，即朋友们送的纪念币种类数小于总种类数，则有解，直接输出$res$

2. 否则就无解，输出$-1$

### 注意题目数据范围$10^{18}$需要开$long\ long$！

---

# 代码

```cpp
#include<cstdio>
long long n,m,k,l,res; //long long
int main()
{
	scanf("%lld%lld%lld%lld",&n,&m,&k,&l);
	if(n<m||n-k<l) //特判无解
	{
		printf("-1\n");
		return 0;
	}
	res=(k+l)/m; //计算res
	if(res*m<k+l) ++res; //如果不够就res+1
	if(res*m<=n) printf("%lld\n",res); //有解则直接输出
	else printf("-1\n"); //否则无解输出-1
	return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：2)

~~其实很简单的一道题。~~

### 思维路径

其实题目主要要考虑的就是以下三个条件。

- 每个人都要送一样多的硬币。
- 每个硬币都必须是不同的。
- 所有人送的硬币至少有 $L$ 个是 Ivan 没有的。

我们一个一个来看。

1. 每个人都要送一样多的硬币。

一共有 $M$ 个朋友，所以说总共送的硬币的个数为 $M$ 的倍数即可满足

2. 每个硬币都必须是不同的。

一共只有 $N$ 种硬币，也就是说送的硬币的个数最多 $N$ 个，这一条对于数的大小做了限定。

3. 所有人送的硬币至少有 $L$ 个是 Ivan 没有的。

Ivan 原先有 $K$ 种硬币，要保证至少 $L$ 个是 Ivan 没有的，根据抽屉原理，至少要送 $K+L$ 种硬币。

综上，我们需要找一个在 $[K+L,N]$ 区间内的 $M$ 的倍数，寻找方式程序实现很容易，有需求的可以来问。

### 实现细节

注意数据范围 $10^{18}$，一定要用 long long，一定不要随随便便相乘。（这边用的是unsigned long long）

### AC 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull n,m,k,l;

void input(){
	cin>>n>>m>>k>>l;
}

void solve(){
	if((k+l)<=n&&(k+l)%m==0) cout<<(k+l)/m;
	else if(((k+l)/m+1)*m<=n) cout<<(k+l)/m+1;
	else cout<<"-1";
}

int main(){
	input();
	solve();
	return 0;
}

```

---

## 作者：_Winham_ (赞：1)

思路：

先考虑无解的情况，不难发现分别会有两个情况：

- 当 $n < m$，也就是朋友的数量少于总纪念币的数量。

- 或者 $n - k < l$，主角剩余的纪念币数量小于至少要送的纪念币数量。

以上两种情况只要满足一种，即输出 `-1`。

---

现在我们知道是否有解后，我们就能知道主角做少获得纪念币数量为 $n + l$。

则我们就能知道每个人至少要给的纪念币数量为 $\frac{n+l}{m}$。由于可能出现小数情况，我们得加以一个向上取整的操作。

在这里解释一下，是不能直接用函数去实现向下取整，因为整除他的高精会消失，所以得手打判断。

----

到了最后之后我们还得要小心，因为可能朋友送的纪念币数量可能多与纪念币数量，所以后面还要加个判断。

----

上代码：

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,m,k,l;
	cin>>n>>m>>k>>l;
	if(n<m||n-k<l){
		cout<<-1<<endl;
		return 0;
	}
	int sum=(k+l)/m;
	if(sum*m<k+l)sum++;
	if(sum*m<=n)cout<<sum<<endl;
	else cout<<-1<<endl;
	return 0;
}

```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1068A Birthday 题解
### 思路：
先判断无解情况：

- 朋友比纪念币数多，每人送不了一个，无解。

- Ivan 没有的种数 $n-k$ 比需要送的他没有的种数 $l$ 还少，无解。

如果不是无解的则算出平均每个朋友要给的 $\frac{k+l}{m}$ 枚纪念币，但是整形除法可能会有精度损失，特判一下如果 $\frac{k+l}{m}\times m$ 比 $k+l$ 小，把算出的 $\frac{k+l}{m}$ 加上 $1$，得到的结果用 $fraci$ 表示。

但是，这时还是有无解的可能：当 $fraci\times m>n$ 时无解。无解输出 `-1`，否则输出 $fraci$。

#### 注意：要开 long long。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, l, fraci;
signed main()
{
	cin>>n>>m>>k>>l;
	if(m>n||(n-k)<l) 
	{
		cout<<-1;
		return 0;
	}
	fraci=(k+l)/m;
	if(fraci*m<k+l)
	{
	    fraci+=1;
	}
	if(fraci*m>n)
	{
	    cout<<-1;
	    return 0;
	}
	cout<<fraci;
	return 0;
}

---

## 作者：Soul_Seeker (赞：0)

# CF1068A Birthday 题解

PS：就这种水题评绿？！

# 题意概述

已经很明确了，不说了。

# 思路详解

先考虑一下无解的情况：

1. Ivan 的纪念币比他的朋友还少……~~什么人缘啊真是~~

2. 当可以送的纪念币比需要的还少时，也无解。

由于所有人送的纪念品至少有 $L$ 个是 Ivan 没有的，实际上一共最少要送 $L+k$ 个，所以最后平均每人至少要送 $\frac{k+l}{m}$ 个。

但是整除精度可能损失，所以要再判断一下，假如精度损失，那么 $ans$ 加一。

最后还是有两种情况：

1. 朋友送的纪念币种类小于总种类数，则直接输出。

2. 否则输出 $-1$。

**注：十年 OI 一场空，不开 long long 见祖宗**

# 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, k, l, ans;//不开long long见祖宗
int main() {
	cin >> n >> m >> k >> l;
	if (n < m || n - k < l)return cout << -1 << endl, 0;//开局特判
	ans = (k + l) / m;
	if (ans * m < k + l) ans++;
	if (ans * m <= n) cout << ans << endl;
	else cout << -1 << endl;
	return 0;//完结撒花
}

```

---

## 作者：__int127 (赞：0)

## CF1068A Birthday 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1068A)

### 题目大意

Ivan 很喜欢收藏硬币，碰巧他的生日到了，于是他的朋友们准备送给他一些硬币，需要满足以下规则：

- 每人都要送相同多的硬币

- 每个硬币必须不同

- 所有人送的硬币至少有 $L$ 个是 Ivan 没有的

其中，一共有 $N$ 个硬币，Ivan 有 $M$ 个朋友，Ivan 有 $K$ 个硬币，$1\le K\le N\le10^{18},1\le M,L\le10^{18}$。

但 Ivan 的朋友们不知道 Ivan 的硬币有哪些。

请你输出数量最少硬币的方案的朋友们每人送给 Ivan 的硬币数量，如不存在任何方案，输出 `-1`。

### 思路

不难发现，根据最不利原则，最少有朋友们送给 Ivan 的硬币数量 $-K$ 个硬币与 Ivan 的硬币不相等，那么，上述式子的答案大于 $N$，则说明没有任何方案，输出 `-1`，如果小于或等于 $N$，再次判断是否大于等于 $L$，如果是，说明朋友们送给 Ivan 的硬币数量除以朋友的数量就是正确答案，否则输出 `-1`，那么求出朋友们送给 Ivan 的硬币数量就可以知道这道题的答案了，那怎样求呢？

我们知道朋友们送给 Ivan 的硬币数量 $-K$ 个硬币与 Ivan 的硬币不相等，要想让朋友们给 Ivan 的硬币最少，不相等的硬币数量为 $L$ 个，也就是说，朋友们每人给 Ivan 的硬币最少为 $\lceil \frac{K+L}{M}\rceil$ 个，那么只需要判断此式子的答案 $\times M$，是否大于 $N$ 就可以了。

这里有一个易错点，就是不能使用 ```ceil()``` 函数，因为输入的数据都是 $10^{18}$ 级别的，用 ```ceil()``` 直接爆炸。

那么来看代码吧。

### 代码+注释

**本题最短代码。**

```cpp
#include <bits/stdc++.h>
long long n, m, k, l, ans;
int main(){
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);// 关闭读写同步
	std::cin >> n >> m >> k >> l;// 读入
	ans = (k + l) / m;// 计算
	if (((long double)k + l) / m > ans)ans++;// 判断是否向上取整
	std::cout << (ans * m <= n ? ans : -1);// 判断并输出
	return 0;
}
```

当然也可以更短。~~虽然不那么美观~~

```cpp
#include <bits/stdc++.h>
long long n, m, k, l, ans;int main(){std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);std::cin >> n >> m >> k >> l;ans = (k + l) / m;if (((long double)k + l) / m > ans)ans++;std::cout << (ans * m <= n ? ans : -1);return 0;}
```

### 拓展——三目运算符

由于程序里使用了三目运算符，这里给大家解释一下三目运算符，你也可以[戳这里](https://baike.baidu.com/item/%E6%9D%A1%E4%BB%B6%E8%BF%90%E7%AE%97%E7%AC%A6/6180633?fromtitle=%E4%B8%89%E7%9B%AE%E8%BF%90%E7%AE%97%E7%AC%A6&fromid=6434591&fr=aladdin)来了解。

三目运算符其实跟 ```if else``` 差不多，它的语句是这样的：

```cpp
表达式 1 ? 表达式 2 : 表达式 3
```

如果表达式 $1$ 为真，那么它就会执行表达式 $2$，否则就会执行表达式 $3$。

例如：

```cpp
a > b ? cout << a : cout << b;
```

就是输出 $a$ 与 $b$ 中更大的数。

三目运算符还可以用来返回值，例如：

```cpp
int s = a > b ? a : b;
```

是使 $s$ 赋值为 $a$ 与 $b$ 中更大的数。

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：fengxiaoyi (赞：0)

### 修改日志

$2022/11/5$：修改了分数格式。

### 思路

这题首先就先判断一下 $m$ 是否大于 $n$，如果是，则输出 `-1`。

#### 为什么呢？

因为每个人最少买一枚纪念币，且因为每个纪念币都必须是不同的，所以会买 $m$ 种纪念币，而纪念币只有 $n$ 种，因为 $m\le n$，所以是不可能实现的。

考虑可能的最坏的情况，也就是所有人买的纪念币正好包含 Ivan 有的那 $K$ 个纪念币，因为还有保证至少有 $L$ 个是 Ivan 没有的，所以他们至少买 $L+K$ 个纪念币。

也就是说，他们每个人得买 $\lceil\frac{(L+K)}{m}\rceil$ 个纪念币。

设 $ans=\lceil\frac{(L+K)}{m}\rceil$。  
最后再判断一下 $ans\times m$ 是否小于等于 $n$，如果是，输出 $ans$，否则，输出 `-1`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,l,p,ans;
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&k,&l);
	if(n<m) return !printf("-1");
	p=k+l;
	ans=p/m;
	if(p%m!=0) ans++;
	if(n/m<ans)  return !printf("-1");
	return !printf("%lld",ans);
}
```

有错或疑问欢迎私信指出~

---

## 作者：user470883 (赞：0)

评黄吧...

## 思路：
分类讨论（排除）+模拟。

观看样例，我们至少可以发现 $2$ 处无解的地方（输出 `-1`）。

- $n <m$ 时，朋友要多于纪念币，必定无解。
- $n-k<l$ 时，$l$ 表示需要的，$n-k$ 表示能给的，这样也必定无解。

然后灵活运用小学数学算出平均数 $\frac{k+l}{m}$ 并将其代表最小答案 $minv$。

接着判断 $res\times n$ 是否能够 $\leq n$，可以直接输出我们的最小答案 $minv$，否则其实是第三种无解，直接输出 `-1` 即可！

**注意事项**：数据范围 $\leq 10^{18}$，不开 `long long` 见祖宗。

## AC CODE：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int n,m,k,l;
	cin >> n >> m >> k >> l;
	if(n<m||n-k<l)
	{
		cout << -1 << endl;
		return 0;
	}
	int minv=(k+l)/m; 
	if(minv*m<k+l)	
	{
		res++; 
	}
	if(minv*m<=n) 
	{
		cout << minv << endl;
	}
	else
	{
		cout << -1 << endl;
	}
	return 0;
}
```


---

## 作者：LeTu_Jun (赞：0)

# CF1068A Birthday 题解
**首先，仔细阅读数据范围，发现是 $10^{18}$ 的范围，注意开 long long。**

~~`define`准备好了~~

其次，发现题目中是有无解的地方的。

经过思考发现有 3 处无解：

1. $n > m$ 朋友比纪念币总数还多，不可能满足题目条件。

1. 根据题目中“而且都要是 Ivan 没有的”可以推出如果 $n-k < l$ 那么也是不可能的。

1. 如果最后求出最小答案（ans）却发现 $ans × m ≤ n$ 也是不可以的。
  
    (即每个人送的数目相乘后 $>$ 总数,题里说明了“每个硬币都必须是不同的”)

前两个情形可以一开始特判掉。
```cpp
if(n<m||n-k<l)
{
    printf("-1");
    return 0;
}
```

之后设 $ans$ 为 $\mathcal{\frac{k+l}{m}}$ ，即平均每个朋友要给的纪念币数量。

#### 但是在这里，要注意整型除法的误差，所以要特判：
```cpp
if(ans*m<k+l) 
{
    ans++;
}
```
之后判掉第 3 个无解。（这里加上了输出）
```
if(ans*m>n) 
{
    cout<<"-1";
}
else cout<<ans;
```
这里注意如果没有打 `else` 的话就必须在 `if` 里写 `return 0;` 。

否则在无解时会同时输出错误答案。

最后~~喜闻乐见的 [$code$](https://www.luogu.com.cn/paste/ushpdrfb)~~

代码还是能不看就不看吧。

---

## 作者：codeLJH114514 (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1068A)

[CodeForces 题目传送门](https://codeforces.com/problemset/problem/1068/A)

## Problem

一共有 $N$ 种不同的硬币，Ivan 有其中的 $K$ 种，Ivan 有 $M$ 个朋友，每个朋友都会送给他相同数量的硬币，不会送给他一样的硬币，且其中至少 $L$ 个 Ivan 没有，请问要满足上述条件每个朋友至少需要送多少个硬币？

## Solution

显然，在送完后 Ivan 肯定至少有 $L + K$ 种硬币。

因为要求的是最坏情况满足至少要多少个，所以我们可以假设朋友们把 Ivan 有的几种全送过了，Ivan 需要 $L + K$ 种，那么朋友们总共送的肯定超过 $L + K$ 种，又因为送的总数必定是 $M$ 的倍数，所以答案是 $\lceil\frac{(L + K)}{M}\rceil$。

那么无解的情况呢？很简单，假如需要每个朋友们送的乘以 $M$ 比 $N$ 还大了，那就无解了。

另外，由于数据范围过大，需要开六十四位整形。

## Code

这道题代码非常短，只有 $10$ 行。

```cpp
#include <iostream>
#include <cstdlib>
#define int int64_t
int n, m, k, l;
signed main() {
    std::cin >> n >> m >> k >> l;
    int solved = (l + k) / m + bool((l + k) % m);
    std::cout << (solved * m > n ? -1 : solved);
    return 0;
}
```

坑点：在计算 `solved` 的时候不可以写 `ceil((l + k) * 1.0 / m)`，因为 `double` 的精度不到 $18$，这样写会损失精度，导致得出错误的答案。

$\texttt{End.}$

---

