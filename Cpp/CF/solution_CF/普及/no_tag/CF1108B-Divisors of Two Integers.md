# Divisors of Two Integers

## 题目描述

Recently you have received two positive integer numbers $ x $ and $ y $ . You forgot them, but you remembered a shuffled list containing all divisors of $ x $ (including $ 1 $ and $ x $ ) and all divisors of $ y $ (including $ 1 $ and $ y $ ). If $ d $ is a divisor of both numbers $ x $ and $ y $ at the same time, there are two occurrences of $ d $ in the list.

For example, if $ x=4 $ and $ y=6 $ then the given list can be any permutation of the list $ [1, 2, 4, 1, 2, 3, 6] $ . Some of the possible lists are: $ [1, 1, 2, 4, 6, 3, 2] $ , $ [4, 6, 1, 1, 2, 3, 2] $ or $ [1, 6, 3, 2, 4, 1, 2] $ .

Your problem is to restore suitable positive integer numbers $ x $ and $ y $ that would yield the same list of divisors (possibly in different order).

It is guaranteed that the answer exists, i.e. the given list of divisors corresponds to some positive integers $ x $ and $ y $ .

## 样例 #1

### 输入

```
10
10 2 8 1 2 4 1 20 4 5
```

### 输出

```
20 8
```

# 题解

## 作者：STA_Morlin (赞：15)

## Upd:
- 22.10.6 修一些锅，并且 CF 的 RMJ 好了，不用交两次了。

[CF1108A Divisors of Two Integers（两个整数的约数） の 题目传送门。](https://www.luogu.com.cn/problem/CF1108B)

## 题目简化
> 给定 $n$ 个数，都为 $x$ 和 $y$ 的约数之一。
>
> 求 $x$ 和 $y$ 的可能解之一。

题目翻译差评！根本没翻译全。

## 思路简析

水黄，非常简单（但我卡了很久（（

易知，$x$ 和 $y$ 中一定有一个为此数列中最大的数，即 $\max\limits_{i = 1}^{n}\{a_i\}$。

证：

> 因为 $x$ 与 $y$ 的因数全部在列，所以这列数中一定有 $x$ 和 $y$。
>
> 若 $x, y$ 全部小于数列中的某一个数 $a$，则 $a$ 必然不是 $x$ 或 $y$ 的因数，与题面不符。

E.D.Q.

不妨设 $x$ 为数列中最大的数，同理可证，$y$ 即为除去 $x$ 的约数之外的数的最大数。

---
## 代码实现

看到题解里很多大佬都写带排序的代码，$O(n\log n)$ 起步，我希望有 $\Theta(n)$ 的算法。

可以使用上上部分所述思路求出 $x$，。

然后挨个枚举，如果是 $x$ 的约数，则数量 $-1$，若还存在或不是 $x$ 的约数，就说明这是 $y$ 的约数，然后取最大值。

当 $y = 0$ 时，也就是所有的数都是 $x$ 的约数时，那 $y$ 随便，只要是 $x$ 约数就行，这里取随意取个 $1$。

而且这样就不用排序了，$\Theta(n)$ 搞定。

然后最优解。

#  _CODE_：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, x, y;
int a[150], v[10010];
int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a+i);
		++ v[a[i]];
		x = max(x, a[i]);
	} for (int i = 1; i <= n; ++ i) {
		v[a[i]] -= !(x%a[i]);
		if (v[a[i]]) y = max(y, a[i]);
	} printf("%d %d\n", x, y?y:1);
	return 0;
}
```
## E.N.D.

---

## 作者：AzureMist (赞：6)

一个数必然比它的因子大，所以输入当中最大的数可以直接认为是 $x$ ~~(连投票都不需要)~~，接下来我们再把 $x$ 的所有因数都去掉，剩下的数当中最大的就肯定是 $y$ ，需要注意的是，有时候 $x$ 与 $y$ 有公因数，这时 $x$ 的因数只需要删一遍，否则后果会非常严重。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int d[n],em[10001]={0};//em这个数组是用来防止同一个数被删掉多次的
	for(int i=0;i<=n-1;i++) cin>>d[i];
	sort(d,d+n);
	cout<<d[n-1]<<" ";
	for(int i=0;i<=n-1;i++)
	{
		if(d[n-1]%d[i]==0&&em[d[i]]==0)
		{
			em[d[i]]=1;
			d[i]=-1;//删掉之后把当前的数设为-1，这样不会影响后面的sort
		}
	}
	sort(d,d+n);
	cout<<d[n-1];
	return 0;
}
```

---

## 作者：installb (赞：4)

这题关键在一个点 对于任意一个正整数$a$ 它本身$a$是它的约数  
找出这堆数里最大的数$maxn$ 由于没有数比它大这个数不可能是其他任何一个数的约数  
那么$maxn$就是需要求的两数中较大的那个数 (两数可能相等 这种情况一样的方法可以处理)  

然后遍历数组把所有$maxn$的约数**删去一个**  
$d_i<10^4$直接用visited数组存一个数之前有没有被删过 保证出现两次的数只删掉一个  

**同理**剩下的数里最大的就是另一个数了  
由于这步操作是求最大值 将一个数删去时把它改成零即可

## code :
```cpp
#include <map>
#include <list>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;

LL n;
LL a[1005];
LL maxn = 0,maxn2 = 0;
char vis[100005] = {0}; // char当bool用 char只占一字节

int main(){
	ios::sync_with_stdio(false); // 加了这句cin比scanf快
	cin >> n;
	for(register int i = 1;i <= n;i ++){
		cin >> a[i]; maxn = max(maxn,a[i]); // 找最大值
	}
	for(register int i = 1;i <= n;i ++){
		if(maxn % a[i] == 0 && (!vis[a[i]])){
			vis[a[i]] = 1;
			a[i] = 0; // 删约数 之前删过这个数 再次碰到这个数就不删了
		}
	}
	for(register int i = 1;i <= n;i ++){
		maxn2 = max(maxn2,a[i]); // 第二遍找最大值
	}
	cout << maxn2 << ' ' << maxn << endl; // 输出
	return 0;
}
```
~~为什么起maxn不起max我觉得大家都懂吧~~

---

## 作者：_ouhsnaijgnat_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1108B)

## 题目大意

这道题就是给你一串数字，为 $x$ 和 $y$ 的因子，让你求出 $x$ 和 $y$ 的值。

## 思路

我们可以将这一串数字排个序，最大值就是要求的 $x$，因为一个数最大的因子就是它自己，$x$ 又比 $y$ 大，所以最大值便是 $x$。

然后再枚举 $1\backsim n$，将 $x$ 的因子踢出去，剩下的最大值便是 $y$，这里 $x$ 的因子只要删一遍即可，因为 $y$ 可能是 $x$ 的因数，那样会把 $y$ 一并删掉。

我们就使用桶来记录这个数是否被踢过。

代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[10005],a[130],s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);//找出最大值 
	cout<<a[n]<<' ';
	s=a[n];
	for(int i=1;i<=n;i++){
		if(s%a[i]==0&&vis[a[i]]==0){//判断这个数是否是x的因子且之前没有出现过这个数字。 
			vis[a[i]]=1;//桶记录上。 
			a[i]=0;//将a[i]踢出去 
		}
	}
	sort(a+1,a+1+n);//找出最大值 
	cout<<a[n];
    return 0;
}
```


---

## 作者：minVan (赞：2)

**题目大意**

有 $2$ 个数 $x$ 与 $y$ ，可是你忘了。

现在给你 $n$ 个数字 $d_1 \cdots d_n$ 每个数都是  $x$ 或 $y$ 的约数之一，如果一个数字在其中出现了 $2$ 次，则是 $x$ 与 $y$ 的公约数。那么现在叫你求出 $x$ 与 $y$ 的可能值（只需要 $1$ 个解并且保证有解）

**解题思路**

经典的暴力。

可以在因数数组 $a$ 中选出最大值 $maxi$ ，然后输出 $maxi$ ，接着遍历 $a$ 数组，如果 $a_i$ 能整除 $maxi$ ，则标记 $a_i$ ，最后查找没被标记过的选最大值，输出最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[130], maxi = INT_MIN, ans = INT_MIN;
bool f[10005], d[130];
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		maxi = max(maxi, a[i]);
	}
	cout << maxi << " ";
	for(int i = 1; i <= n; i++)
		if(maxi % a[i] == 0 && f[a[i]] == 0)
		{
			d[i] = 1;
			f[a[i]] = 1;
		}
	for(int i = 1; i <= n; i++)
		if(d[i] == 0)
			ans = max(ans, a[i]);
	cout << ans;
	return 0;
}
```

---

## 作者：Heartlessly (赞：2)

## Solution
没有想到这道题居然这么容易被 $Hack$ ~~(虽然我没有)~~，达到了 $200$ 多个测试点。现在说说我比赛时看完这道题的想法：因为本题的所有因数的排列中包含了 $x$ 和 $y$，所以不难想到，排列中所有元素的最大值为 $max(x,y)$。现在我们假设 $x > y$，那么 $x$ 的值就是所有元素的最大值。接下来我们分解出 $x$ 的所有因数，很显然排列中除去 $x$ 的因数就剩下了 $y$ 的因数。怎么去除 $x$ 的因数呢？其实很简单，只要把排列中 $x$ 的因数第一次出现的值改为 $0$ 就行了。而剩下所有元素的最大值就是 $y$。


------------

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template < class T > inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}

int n, x, a[100001];

int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    sort(a + 1, a + n + 1), x = a[n];//所有元素的最大值即为x
    for (int i = 1; i <= x; i++) if (x % i == 0) a[lower_bound(a + 1, a + n + 1, i) - a] = 0;//用lower_bound找到x的因数i第一次出现的下标，并赋值为0
    sort(a + 1, a + n + 1);//剩下元素的最大值即为y
    printf("%d %d\n", x, a[n]);
    return 0;
}
```

---

## 作者：zsc2003 (赞：1)

#### 2019.1.23 codeforces div3

Divisors of Two Integers

##### 题目大意:

第一行读入一个正整数$n$

接下来一行读入$n$个数

其中第$i$个数为$d_i$

你需要求出$x,y$

使得$d$数组内的所有元素都是$x,y$的因数

若$x,y$有相同的因数，则该数会在$d$数组中出现$2$次

##### 思路

先将$d$数组排一边序

拍过序后的$d_n$一定是$x,y$中较大的数$maxn$

然后将$d$数组中所有$maxn$的因数去掉，记作已经已经用过

如果有两个相同的数，则只能去掉一个

去掉后从大到小扫一遍$d$数组

当找到第一个没被用过的数，即为$x,y$中较小的数

##### 下面附上本人的代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=130;
int n;
int a[N];
bool vis[N];//判断该数是否为最大数的因数
bool num[100100];//判断该数字是否已经被用过一次
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		if(a[n]%a[i]==0)
		{
			if(num[a[i]]==0)
			{
				vis[i]=1;
				num[a[i]]=1;
			}
		}
	printf("%d ",a[n]);
	for(int i=n;i>=1;i--)
		if(!vis[i])
		{
			printf("%d\n",a[i]);
			return 0;
		}
	return 0;
}
```

---

## 作者：da32s1da (赞：1)

首先最大数一定是两个数中的一个。

然后暴枚因子去掉

再取最大数，就是另外一个。

因为$d_i\le 10^4$，复杂度可以保证

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200;
const int M=1e4+50;
int n,a[N],b[M];
int x,y;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++)b[a[i]]++;
	x=a[n];//最大数
	for(int i=1;i<=x;i++)
	if(x%i==0)b[i]--;
	for(int i=x;i>=1;i--)
	if(b[i]){y=i;break;}//再取最大数
	printf("%d %d\n",x,y);
}
```

---

## 作者：mzyc_yang2021 (赞：0)

题意：给你两个数的因子，求这两个数。

思路：我们知道，一个数的因子必定包含本身。那么其中最大的数就是两个数的其中一个。那还有一个数怎么求？我们只需要把求到的那个数的因子全部剔除，在剩下的数中找最大值，那就是我们要求的第二个数。

实现：第一个数可以通过把数组排序，取最后一个值得到。第二个数我用了标志数组加优先队列来求。我们枚举这些数，若当前这个数是第一个数的因子且标志数组没有标记，则标记，否则添加进队列。枚举完后，队列最顶端的数就是我们要求的第二个数。

代码（加解释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 150000
int n,maxn,a[150],f[20000];
priority_queue<int>q;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1); // 从小到大排序
	maxn=a[n]; // 第一个数
	for(int i=1;i<=n;i++)
	{
		if(maxn%a[i]==0&&!f[a[i]]){f[a[i]]=1;continue;} // 若是第一个数的因子，且未标记，就标记
		else q.push(a[i]); // 否则进入队列
	}
	cout<<maxn<<" "<<q.top(); // 队列最顶端就是第二个数
	return 0;
}
```

---

## 作者：032o35 (赞：0)

题意：给出两个数的因子，求这两个数可能的情况（只求其中一种情况）

思路：易证因子中包括两数中较大数，所以我们可以枚举寻找因子中最大值来求得 $A$。然后枚举每一个数，如果是 $A$ 的倍数，标记下来，最后再跑一遍，没被标记的数中的最大值就是我们要求的 $B$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[205],vis[10005];//a数组存值，vis数组标记
int main(){
	int n;
	cin>>n;
	int maz=-0x3f;
	for(int i=1;i<=n;i++)cin>>a[i],maz=max(a[i],maz);//第一遍找最大值
	int maz2=-0x3f;
	for(int i=1;i<=n;i++)
		if(maz%a[i]==0&&!vis[a[i]])vis[a[i]]=1,a[i]=0;//改标记，删数
	for(int i=1;i<=n;i++)maz2=max(maz2,a[i]);//第二遍找最大值
	cout<<maz<<" "<<maz2;
	return 0;
}

```


---

## 作者：Zechariah (赞：0)

不难发现序列中的最大值一定是其中一个答案x  
然后我们把序列中x的因数各删掉一个，剩下的数字里面再取最大就是y了
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N], cnt[N];

int main(void)
{
    rg int n = fast_IO::read(), maxn = 0;
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read(), maxn = fast_IO::max(maxn, a[i]), ++cnt[a[i]];
    fast_IO::write(maxn); putchar(' ');
    for (rg int i = 1; i <= maxn; ++i)if (maxn%i == 0)--cnt[i];
    rg int max2 = 0; for (rg int i = 1; i <= maxn; ++i)if (cnt[i])max2 = i;
    fast_IO::write(max2);
    return 0;
}

```

---

