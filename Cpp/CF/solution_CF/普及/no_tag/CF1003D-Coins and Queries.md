# Coins and Queries

## 题目描述

Polycarp has $ n $ coins, the value of the $ i $ -th coin is $ a_i $ . It is guaranteed that all the values are integer powers of $ 2 $ (i.e. $ a_i = 2^d $ for some non-negative integer number $ d $ ).

Polycarp wants to know answers on $ q $ queries. The $ j $ -th query is described as integer number $ b_j $ . The answer to the query is the minimum number of coins that is necessary to obtain the value $ b_j $ using some subset of coins (Polycarp can use only coins he has). If Polycarp can't obtain the value $ b_j $ , the answer to the $ j $ -th query is -1.

The queries are independent (the answer on the query doesn't affect Polycarp's coins).

## 样例 #1

### 输入

```
5 4
2 4 8 2 4
8
5
14
10
```

### 输出

```
1
-1
3
2
```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：11)

当我看到这道题时非常懵，竟把它当成了一道搜索题？（~~请容忍我的菜~~）。为了不让其他的人像我一样折腾了一个小时，我就仔细讲解一下如何贪心以及贪心证明。
#### 1.如何贪心：从大到小循环数的数值，每次竟可能的去取当前的数。如果刚好能凑成答案，则输出取的数的数目，不能则输出-1.
#### 2.贪心证明：先给你们看一句非常重要的话：第二行给你n个硬币的面值（保证都是2的次幂！）。这句话说明**每大个数都是小数的倍数**，如果是这样就好证明了。
#### 开始证明：许多人可能会想，这种贪心方式会导致本能凑成的数最终凑不成。假设导致凑不成的数是8，则按他们的说法就是把8去掉，再拿一些小一点的数最终凑成答案，但不管怎么说，他所说的小一点的数都是8的因数，最终肯定会先把8给补上，再把剩下的补上，那么这就是一个无意义的操作。这就证明了这个策略是最优的，并且不存在任何问题。
### 下面上代码(解释的相当清楚)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a,b;
map<int,int> m;//可以说map是一个高级的桶，只不过这个桶非常大 
int main(){   //之所以要用它是就是因为这个桶非常大......
	int i;
	scanf("%d%d",&n,&q);//n个硬币，q次询问 
	for(i=1;i<=n;i++){
		scanf("%d",&a);//读入每个硬币的值 
		m[a]++;//把每一种硬币的值的个数存在map数组里 
	}
	map<int,int>::iterator it;//指针 
	for(i=1;i<=q;i++){
		int ans=0;
		scanf("%d",&b);//询问的数值 
		it=m.end();
		while(1){
			it--;//每次从大到小找硬币 
			int minn=min(b/(it->first),it->second);//求出最多能取多少个这种硬币 
			b-=minn*(it->first);//减去取走的硬币总值 
			ans+=minn;//加上取走的数目 
			if(it==m.begin() && b!=0){//如果到了最后还没有凑成 
				printf("-1\n");
				break;
			}else if(b==0){//注意！！这块不能用else否则第一次循环就会跳出 
				printf("%d\n",ans);
				break;
			}
		}
	}
	//over! 
	return 0;
}

```
## 看在我第一次发题解的份上，请求管理员通过orz

---

## 作者：Ryo_Yamada (赞：7)

~~不是，CF 为什么会有这么水的 D 题啊~~  
~~哦 Div.3 啊，那没事了~~

很容易想到贪心的思路：每次从大的硬币面值向小取，面值大的硬币尽可能地多用，若最后还有无法凑出的输出 $-1$，否则输出计数。具体细节可见代码。

~~好像喜提你谷最短解了~~

$\text{Code}$：

```cpp
// CF1003D Coins and Queries
// By BreezeEnder
#include <bits/stdc++.h>

using namespace std;

int n, q;
int cnt[40];

int main() {
	cin >> n >> q;
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); ++cnt[(int)(log2(x))]; } // 将面值对应的 2 的次幂 +1
	while(q--) {
		int x, ans = 0;
		scanf("%d", &x);
		for(int i = 31; ~i; i--) { // ~i 等价于 i >= 0，面值从 2^31 搜到 2^0
			int m = min(cnt[i], x / (1 << i));// 此面值最多能使用个数
			ans += m;// 计数器加上个数
			x -= m * (1ll << i);// 减去
		}
		printf("%d\n", x ? -1 : ans);
	}
	return 0;
}
```


---

## 作者：loving丶Drug (赞：7)

这个题的话用map就可以简化成一道****普及-****的题了  

****~~STL大法好~~****


具体代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

int n, q, a, b, ans;

map <int, int> Q;

map <int, int>::iterator it;//迭代器，不会的话baidu一下很快就懂了

inline int read ()
{
	int ret = 0;
	char ch = getchar ();
	while (! isdigit (ch))
		ch = getchar ();
	while (isdigit (ch))
	{
		ret = (ret << 3) + (ret << 1) + (ch ^ 48);
		ch = getchar ();
	}
	return ret;
}

int main ()
{
	n = read ();
	q = read ();
	for (int i = 1; i <= n; ++i)
	{
		a = read ();
		++ Q[a];
	}//用map的话还自带一个自动排序的功能
	while (q--)
	{
		ans = 0;
		b = read ();
		it = Q.end();//因为map最后的end()是空的所以先处理一下
		it--;
		for (;; --it) 
		{
			int t = min (b/it->first, it->second);//看能不能一次行全部取完，如果可以，那就先取完
			b -= t * it->first;
			ans += t;
			if (!b)//如果取完了就直接输出
			{
				cout << ans << endl;
				break;
			}
			if (it == Q.begin() && b != 0)
			{
				cout << -1 << endl;
				break;
			}
		}
	}
	return 0;
}
//完美结束
```

---

## 作者：风浔凌 (赞：3)

这道题就是有n枚硬币，每个硬币的币值都是2的次方（比如2 4 8 16之类的） 然后有q次询问，每次输入一个数，我们要用最少的硬币达到这个币值，如果存在结果的话就输出这个最小的使用硬币数，如果不存在的话，就输出-1

这道题应该算是一道贪心的题，我们先将2的各次方存到一个数组里，之后询问的时候，就先从最大的2的31次方开始找，然后记录一下就可以啦！

以下是代码：

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,q;
int sum[32];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        int t=log2(k);
        sum[t]++;
    }
    for(int i=1;i<=q;i++)
    {
        int k,ans=0;
        scanf("%d",&k);
        for(int j=31;j>=0;j--)
        {
            int cur=min(sum[j],k/(1<<j));
            ans+=cur;
            k-=(1<<j)*cur;
        }
        if(k!=0)  printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Otue (赞：1)

想一下我们二进制拆分优化多重背包时，是从大到小依次考虑的。

由于这道题输入的数都是二的幂，则完全可以将其放入二进制位中，然后每次询问枚举二进制位数（最多 $32$ 位），从高位到低位枚举，逐个相减，如果最后还没有变成 $0$ 则为 `-1`。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;

int n, q, a[N], x, vis[35]; 

signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i], vis[(int)log2(a[i])]++; // 将ai放入二进制数中
	while (q--) {
		cin >> x;
		int ans = 0;
		for (int j = 32; j >= 0; j--) {
			if (vis[j]) { // 当前这一位有权值
				int t = x / (1 << j);
				ans += min(vis[j], t);
				x -= min(vis[j], t) * (1 << j);
			}
		}
		if (x > 0) puts("-1");
		else cout << ans << endl;
	}
}
```


---

## 作者：skyfly886 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1003D)

~~这题卡了我好几天了，终于过了~~

本题十分适合用 $\mathrm{STL}$ 中的 $\mathrm{map}$ 来做，我们可以使用 $\mathrm{map}$ 再加上一点贪心的思想来切掉这道题。

- 先确定主思路：对于一个钱数，我们不断地减去其当前所能使用的最大硬币面值，直到它减为0。


------------

  
### Some Problems

- **Problem 1**

本题贪心的顺序是从大到小，可 $\mathrm{map}$ 的默认排序顺序为从小到大，怎么办？

解决方案：使用伪函数 greater ，如下：
```cpp
map<int,int,greater<int> > se;
```

- **Problem 2**

如何判断判断能否组成题目给出的钱数？

使用一个 $\mathrm{bool}$ 类型的变量，如下伪代码所示：

```cpp
bool f=false;
while(true){
    if(遍历完毕){
        break;
    }
    if(钱数可以组成){
        printf("%d\n",ans);
        f=true;
        break;
    }
    模拟;
}
if(!f){
    printf("-1\n");
}
```

------------


那么，根据我们的思路，不难得到以下代码段：
```cpp
for(int i=0;i<q;i++){
    int ans=0;
    int ask=0;
    scanf("%d",&ask);
    map<int,int,greater<int> >::iterator it=se.begin();
    bool f=false;
    while(true){
        if(it==se.end()){
            break;
        }
        if(ask==0){
            printf("%d\n",ans);
            f=true;
            break;
        }
        if(ask>=((it->first)*(it->second))){
            ans+=it->second;
            ask-=(it->first)*(it->second);
        }
        else{
            int z=ask/(it->first);
            ans+=z;
            ask-=z*(it->first);
        }
        it++;
    }
    if(!f){
        printf("-1\n");
    }
}
```

然后，一测样例，发现：纳尼？？？怎么辣么多 -1 ？？？

仔细一想，才会发现：有时候，需要遍历完整个 $\mathrm{map}$ 才能组成题目给出的钱数，但那时，我们的 while 循环已经退出了。

于是，赶紧改一下循环的退出条件：
```cpp
if(it==se.end()){
    if(ask==0){
        printf("%d\n",ans);
    }
    break;
}
```

再一测，又 $\mathrm{WA}$ 了？？？

这时才发现：要开 $\mathrm{long}\;\mathrm{long}$ ！~~（我也是醉了）~~

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll n,q;
    scanf("%lld%lld",&n,&q);
    map<ll,ll,greater<int> > se;
    for(ll i=0;i<n;i++){
        ll t;
        scanf("%lld",&t);
        se[t]++;
    }
    for(ll i=0;i<q;i++){
        ll ans=0;
        ll ask=0;
        scanf("%lld",&ask);
        map<ll,ll,greater<int> >::iterator it=se.begin();
        bool f=false;
        while(true){
            if(it==se.end()){
                if(ask==0){
                    printf("%lld\n",ans);
                    f=true;
                }
                break;
            }
            if(ask==0){
                printf("%lld\n",ans);
                f=true;
                break;
            }
            if(ask>=((it->first)*(it->second))){
                ans+=it->second;
                ask-=(it->first)*(it->second);
            }
            else{
                int z=ask/(it->first);
                ans+=z;
                ask-=z*(it->first);
            }
            it++;
        }
        if(!f){
            printf("-1\n");
        }
    }
    return 0;
}
```

---

## 作者：lingfunny (赞：0)

## $\texttt{Solution}$
很简单的贪心，每次从价格最高的硬币开始取即可。因为硬币面值满足都是$2$的幂次，$\text{yy}$一下就可以猜到这个贪心的正确性。

硬币可以用桶存储：由于$\forall 1\le a_i\le 2\cdot10^9$，且$a_i=2^d$，很容易可以求出来$d$的取值范围是$0\le d\le30$，随便开个数组就可以存下了。接下来可以用$tot[x]$表示有多少个$a_i$满足$a_i=2^x$。

至于如何将$a_i$转化成对应的$d$，显然有$d=\log_2a_i$，可以用`cmath`库自带的`log2`函数计算。此外这个函数返回值是`double`类型，要强制类型转换一下。

最后对于每个询问，从硬币面值最高的来取。如果每次判断能不能加下下一个硬币，显然最坏情况下时间复杂度是$\mathcal{O(nq)}$。但转念一想，如果当前还需凑出$b'$元，对于面值为$2^d$的硬币，每次显然应该取$\min(tot[d], \left \lfloor \frac{b'}{2^d} \right \rfloor )$，这样便可以$\mathcal{O(1)}$求出每个硬币应取多少。

`log2`函数时间复杂度$\mathcal{O(loga_i})$，即$\mathcal{O(d)}$。拆分所有数总时间复杂度$\mathcal{O(nd)}$。每个询问要从面值最高的到面值最低的取，总的有$d$种面值，对于每种面值求解需要$\mathcal{O(1)}$，回答询问的总时间复杂度为$\mathcal{O(qd)}$。综上，总时间复杂度$\mathcal{O(nd)}$。

## $\texttt{Code}$
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2e5+5;
const int maxk = 40;
#define rep(i, n) for(int i=1;i<=n;++i)

int n, q, a[maxn];
int tot[maxk], pow2[maxk];

int main(){
	scanf("%d%d", &n, &q);
	pow2[0] = 1;
	rep(i, 30) pow2[i] = pow2[i-1]<<1;			//预处理2的幂次
	rep(i, n) {
		scanf("%d", &a[i]);
		++tot[ int(log2(a[i])) ];				//拆分
		//如果怕log2的时候出现2.9999999这样的值被int吞掉的话，可以改写为++tot[ int(log2(a[i]) + 0.5) ]
	}
	rep(i, q) {
		int b, ans = 0;
		scanf("%d", &b);
		for(int j=30;j>=0;--j)
		if(b >= pow2[j]) {
			int cur = min(b/pow2[j], tot[j]);
			ans += cur, b -= cur*pow2[j];
		}
		printf("%d\n", b==0?ans:-1);			//最后如果减不到0，则无解
	}
	return 0;
} 
```

---

## 作者：睿3030 (赞：0)

## 背景
某一天，在做CF(CodeForces)1003D Coins and Queries([题目转送门 洛谷](https://www.luogu.org/problem/CF1003D))([题目转送门 VJudge](https://vjudge.net/problem/CodeForces-1003D))的时候，遇上了神奇的WA！！

## 题目大意（摘自洛谷）
n个硬币，q次询问。第二行给你n个硬币的面值（保证都是2的次幂）。每次询问组成b块钱，最少需要多少个硬币？

## 错误
首先我写了这样一行代码（为了搞清楚输入的数是2的几次幂）
```cpp
cnt[(int) (log(a[i]) / log(2))]++;
```
然而，由于VJ上的CF默认用VS的VC++，它编译出错了！
```
program.cpp(23) : error C2668: \u0027log\u0027 : ambiguous call to overloaded function
        c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\math.h(575): could be \u0027long double log(long double)\u0027
        c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\math.h(527): or       \u0027float log(float)\u0027
        c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\math.h(120): or       \u0027double log(double)\u0027
        while trying to match the argument list \u0027(int)\u0027
```
于是，我~~机智地~~把我的代码改为了下面这个
```cpp
cnt[(int) (log((long double)a[i]) / log((long double)2))]++;
```
然后我就AC了

------------

后来我又看到洛谷上也有这个题，于是又把我的代码在洛谷上重新提交了一次，这一次，我看到了：  
![WA1](https://cdn.luogu.com.cn/upload/pic/67120.png)  
WHAT F***?!!!!

然后自以为是的我想起我最开始写的代码可以我Devcpp的编译于是把
```cpp
cnt[(int) (log(a[i]) / log(2))]++;
```
交了上去。没想到。。。。  
![WA2](https://cdn.luogu.com.cn/upload/pic/67121.png)  
Emmmmm....?????

G++是个什么烂编译器，long double的精度居然不够？！

于是，我又学会了一个新函数 log2 ！！
于是，我的代码变成了
```cpp
cnt[(int)log2(a[i])]++;
```
然后成功AC了。。。。
```cpp
cnt[upper_bound(pow_2, pow_2 + 32, a[i]) - pow_2 - 1]++;
```
上面那个代码也可以AC，其中pow_2是预处理出2的n次幂的值。

上面这两个代码，用VC++编译也都可以过，我就好奇了，这个G++的log是不是有毒？？？

------------

## 解答
用下面这个程序可以很好的告诉我们G++的log为什么有毒：
```cpp
int main(){
	for(int x = 0; x < 31; x++){
		printf("log 2^%d: %.20Lf\n", x, log((long double) (1 << x)) / log((long double)2));
		cout << "(int): " << (int) (log((long double) (1 << x)) / log((long double)2)) << endl;
	}
	return 0;
}
```

它的运行结果是：
```
log 2^0: 0.00000000000000000000
(int): 0
log 2^1: 1.00000000000000000000
(int): 1
log 2^2: 2.00000000000000000000
(int): 2
log 2^3: 3.00000000000000000000
(int): 3
log 2^4: 4.00000000000000000000
(int): 4
log 2^5: 5.00000000000000000000
(int): 5
log 2^6: 6.00000000000000000000
(int): 6
log 2^7: 6.99999999999999999957
(int): 6
log 2^8: 8.00000000000000000000
(int): 8
log 2^9: 9.00000000000000000000
(int): 9
log 2^10: 10.00000000000000000000
(int): 10
log 2^11: 11.00000000000000000000
(int): 11
log 2^12: 12.00000000000000000000
(int): 12
log 2^13: 13.00000000000000000000
(int): 13
log 2^14: 13.99999999999999999913
(int): 13
log 2^15: 15.00000000000000000000
(int): 15
log 2^16: 16.00000000000000000000
(int): 16
log 2^17: 17.00000000000000000000
(int): 17
log 2^18: 18.00000000000000000000
(int): 18
log 2^19: 19.00000000000000000000
(int): 19
log 2^20: 20.00000000000000000000
(int): 20
log 2^21: 21.00000000000000000000
(int): 21
log 2^22: 22.00000000000000000000
(int): 22
log 2^23: 23.00000000000000000000
(int): 23
log 2^24: 24.00000000000000000000
(int): 24
log 2^25: 24.99999999999999999827
(int): 24
log 2^26: 26.00000000000000000000
(int): 26
log 2^27: 27.00000000000000000000
(int): 27
log 2^28: 27.99999999999999999827
(int): 27
log 2^29: 29.00000000000000000000
(int): 29
log 2^30: 30.00000000000000000000
(int): 30
```

看到了吧，(int)把0.999999999999都吃掉了！！！！

所以，在希望进行四舍五入的时候，请这样使用：
```cpp
cnt[(int) (log(a[i]) / log(2) + 0.5)]++;
```


---

