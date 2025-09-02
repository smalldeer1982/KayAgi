# Less or Equal

## 题目描述

You are given a sequence of integers of length $ n $ and integer number $ k $ . You should print any integer number $ x $ in the range of $ [1; 10^9] $ (i.e. $ 1 \le x \le 10^9 $ ) such that exactly $ k $ elements of given sequence are less than or equal to $ x $ .

Note that the sequence can contain equal elements.

If there is no such $ x $ , print "-1" (without quotes).

## 说明/提示

In the first example $ 5 $ is also a valid answer because the elements with indices $ [1, 3, 4, 6] $ is less than or equal to $ 5 $ and obviously less than or equal to $ 6 $ .

In the second example you cannot choose any number that only $ 2 $ elements of the given sequence will be less than or equal to this number because $ 3 $ elements of the given sequence will be also less than or equal to this number.

## 样例 #1

### 输入

```
7 4
3 7 5 1 10 3 20
```

### 输出

```
6```

## 样例 #2

### 输入

```
7 2
3 7 5 1 10 3 20
```

### 输出

```
-1
```

# 题解

## 作者：lichenzhen (赞：11)

## 题目大意

给定一个长度为 $n$ 的整数序列和整数 $k$，你需要找到一个在 $[1, 10^9]$ 范围内的整数 $x$，使得给定序列中有正好 $k$ 个数小于等于 $x$，序列中可能含有相等的元素，如果没有这样的 $x$，输出 `-1`。

## 题目解法

我们只需要把数据从小到大排一下序（用`sort`快排就可以），然后特判一下某些是无解的情况，如果不是就直接输出数组中的第 $k$ 个数就可以了。

那什么时候是无解的呢？

我们把这个序列定义成 $a$ 数组，看一下数据的范围，发现 $0 \le k \le n$ ，

当 $k=0$ 时，意思是序列中没有数比 $x$ 的值小。

此时，如果 $a[1]=1$（$a[1]$ 就是序列中最小的数），那么 $x$ 的值就应该比 $1$ 小，但是我们看数据范围就会发现 $ 1 \le x \le 10^9 $。因此，此时是无解的。

那么如果 $a[1]>1$，我们输出 $a[1]-1$ 即可（也可以输出 $1$,这道题应该是有spj的）。

我们再注意一下题目，就会发现`序列中可能含有相等的元素`，这时候还有一个特殊的情况，如果第 $a[k]=a[k+1]$ 这时候 $x$ 的值就无法确定了，因此无解。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	if(k==0) 
	{
		if(a[1]==1){
			cout<<-1;
			return 0;
		}
		else {
			cout<<a[1]-1;//也可以输出1 
			return 0;
		}
	}
	if(a[k]==a[k+1]){
		cout<<-1;
		return 0;
	}
	cout<<a[k];
}
```


---

## 作者：xhz0311 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF977C)
## 题目分析
题目要求找一个数 $x$，使的给定的数组 $\texttt{a}$ 中有 $k$ 个小于等于 $x$ 的数。
首先，我们需要输入 $n$ $k$ 和数组 $\texttt{a}$。

所以有了下面这部分代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,k;
    cin>>n>>k;
	int a[n+1];
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    }
    ......
    return 0;
}
```
这一题的核心就在于接下来如何判断有没有符合题意的 $x$，如果有，是多少。

容易想到，先排序然后令 $x=\texttt{a[k]}$。
所以我们在“......”处补上这样一段：
```cpp
sort(a+1,a+n+1);
cout<<a[k];
```
**WA**。
反复推敲后发现，如果 $\texttt{a[k]=a[k+1]}$，那么其实是无解的，而上面的代码会输出 $\texttt{a[k]}$。
例如：
```
输入
3 2
2 1 2
```
此时如果你先排序，再输出 $\texttt{a[k]}$ 也就是 $2$，那么是错误的答案，可以发现此时有三个数小于你所输出的 $x=2$。事实上，如果有 $\texttt{a[k]=a[k+1]=...=a[k+m]}$ 的话，有 $k+m$ 个数小于等于 $x=\texttt{a[k]}$，那么就一定无解。

所以我们有了特判1。
```cpp
sort(a+1,a+n+1);
if (a[k]=a[k+1])//特判1，如果a[k]=a[k+1]，则一定无解
{
    cout<<"-1";
}
else
{
    cout<<a[k];
}
```
**仍然会 WA。**

接下来，仔细审题，发现数据范围是 $0≤k≤n$，这意味着 $k$ 有可能等于 $0$。由于数据范围显示 $\texttt{a[i]}≥1$，所以只要取 $x=0$，就一定能使 $\texttt{a}$ 中有 $0$ 个数小于等于 $x$。

所以我们有了特判2。
```cpp
sort(a+1,a+n+1);
if (k==0)
{
    cout<<"0";//特判2，若k=0，取x=0必可以使a中任意一项大于x，直接输出
}
else if (a[k]=a[k+1])//特判1，如果a[k]=a[k+1]，则一定无解
{
    cout<<"-1";
}
else
{
    cout<<a[k];
}
```
**继续 WA。**

再次返回去审题。发现题目要求 $x≥1$。这说明我们不能在 $k=0$ 时取 $x=0$。解决方法很简单，那就取 $x=1$ 嘛。不过如果取 $x=1$，需要判断 $\texttt{a}$ 中是否含有 $1$。如果 $\texttt{a}$ 中含有 $1$，则无解；若不含 $1$，则 $x=1$ 满足题意。因为 $\texttt{a[i]}≥1$，判断 $\texttt{a}$ 中是否含有 $1$ 其实只需要判断 $\texttt{a[1]}$ 也就是 $\texttt{a}$ 中最小的一项是否为 $1$。

所以我们需要修改特判2，并加上特判3。
```cpp
sort(a+1,a+n+1);
if(k==0 && a[1]==1) //特判3，若k=0且a[1]=1，则无解
{
    cout<<-1;
}
else if(k==0)//特判2，若k=0且a[1]≠1，则x=1必定满足题意
{
    cout<<"1";
}
else if(a[k]==a[k+1])//特判1，如果a[k]=a[k+1]，则一定无解
{
    cout<<"-1";
}
else
{
    cout<<a[k];//特判结束，放心输出a[k]
}
```
**可以 AC**
## 附上完整 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
	int a[n+1];
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    }
    sort(a+1,a+n+1);
    if(k==0 && a[1]==1) //若k=0且a[1]=1，则无解
    {
        cout<<-1;
    }
    else if(k==0)//若k=0且a[1]≠1，则x=1必定满足题意
    {
        cout<<"1";
    }
    else if(a[k]==a[k+1])//如果a[k]=a[k+1]，则一定无解
    {
    	cout<<"-1";
    }
    else
    {
    	cout<<a[k];//特判结束，放心输出a[k]
    }
    return 0;
}
```

最后吐个槽：我在洛谷上一直 UKE，去 codeforces 交就 AC 了，估计又是 CF 新年彩蛋惹得祸。

如果不算我上次写的那篇没法提交的[题解](https://www.luogu.com.cn/blog/xhz0311/p5461-she-mian-zhan-fu-ti-xie-c)，这应该是我的第一篇，望通过。

### 注
本文提到的“无解”，指的是没有满足题意的 $x$，而非某个方程无解。

---

## 作者：封禁用户 (赞：3)

楼下讲得不太详细,那我就讲得详细点吧

这题有几点需要注意:

第一点: 需要排序

第二点: $1\le x\le 10^9$ , $1\le a_i\le 10^9$ (注意是小于等于)
也就是如果 $k=0$ 而最小数 $=1$ 则无解,否则输出$a_1-1$ ; 且如果 $x>10^9$ ,也只用输出 $1000000000$ ~~我在这被坑了好久~~

第三点: 如果排序后的第$k$个数等于第$k+1$个数,也无解(这应该很好理解吧)

第四点: 如果第二点和第三点都不成立,则$x$就是第$a$数组中的第$k$个数

注意到这几点就可以了

代码($c++$):

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000005],n,k,x;
int main(){
	cin>>n>>k;
	memset(a,128,sizeof(a));
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	if(k==0)
	{
		if(a[1]==1)
			cout<<-1;
		else
			cout<<a[1]-1;
		return 0;
	}
	if(a[k+1]==a[k])
	{
		cout<<-1;
		return 0;
	}
	if(a[k]<=1000000000)
		cout<<a[k];
	else
		cout<<1000000000;//以上是几种判断
	return 0;
}
```


---

## 作者：Eason_AC (赞：3)

## Content
给定一个 $n$ 个数的数列 $a_1,a_2,a_3,...,a_n$ 和一个数 $k$，试找出这样的一个数 $x$，使得数列中有 $k$ 个数小于等于 $x$。求出任意一个 $x$，或者 $x$ 不存在。

**数据范围：$1\leqslant n\leqslant 2\times 10^5,0\leqslant k\leqslant n,1\leqslant a_i\leqslant 10^9,x\in[1,10^9]$。**
## Solution
比大小的话肯定要排序，所以我们先对这个序列排序。设排序后的每个数下标是按照其排序之后的位置决定的。然后，按照 $k$ 的值分类讨论：

- $k=0$，那么看最小的数 $a_1$ 是否大于 $1$，是的话 $x=a_1-1$，否则不存在这样的 $x$。
- $k>0$，那么直接看是否有 $a_k=a_{k+1}$，有的话 $x$ 不存在，否则 $x=a_k$。

## Code
```cpp
int n, k, a[200007], ans;

int main() {
	getint(n), getint(k);
	_for(i, 1, n)	getint(a[i]);
	sort(a + 1, a + n + 1);
	ans = (!k ? (a[1] > 1 ? a[1] - 1 : -1) : (a[k] == a[k + 1] ? -1 : a[k]));
	writeint(ans);
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

这是一道练手题。

思路：排序，然后判断是否有解，有则输出解，无则输出 `-1`。

由于我们按照从小到大排序，所以要使得数列中有 $k$ 个数**小于等于** $x$，我们只需要输出序列中第 $k$ 大的数，但如果排序后数列中的第 $k$ 个数与第 $k+1$ 个数相等，就说明无解。代码奉上：
```cpp
#include <iostream>//个人不建议使用万能头。
#include <algorithm>
using namespace std;
const int maxn=2e5+1;
int n,k,a[maxn];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    sort(a,a+n);
    if(!k){//0需要特判一下，不然执行a[k-1]时会RE。
        if(a[0]>1) printf("1");//k=0时说明数列中所有数都比x大，所以答案要做到比排序后的a[0]小。
        else printf("-1");//因为答案在[1,1e9]之间，所以a[0]=1时，不可能存在解。
        return 0;//直接返回。
    }
    if(a[k]==a[k-1]) printf("-1");//当数列中第k大的数与第k+1大的数相等时就无解，因为我们这里记录的数组下标从0开始，所以要减1。
    else printf("%d",a[k-1]);//有解则输出数列中第k大的数。
    return 0;
}
```


---

## 作者：LJC00111 (赞：1)

这道题只需排一个序，再判断一下即可

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
int a[1000001];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    if(k==0&&a[1]==1)//有几个需要特判
    {
        cout<<"-1"<<endl;
        return 0;
    }
    else if(k==0)//也需要特判
    {
        cout<<"1"<<endl;
        return 0;
    }
    
    if(a[k]==a[k+1])cout<<"-1"<<endl;
    else 
    {
        if(a[k]<=1000000000)
        cout<<a[k]<<endl;
        else cout<<"1000000000"<<endl;//若大于1000000000，则只需输出1000000000
        }
    
    return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/977/C)[链接](https://www.luogu.com.cn/problem/CF977C)

乍一看以为是排序 $+$ 二分，仔细阅读题目才发现想难了。

要求数组 $a$ 中有 $k$ 个小于等于 $x$ 的数，只需要一遍快排，再比较 $a_k$ 和 $a_k+1$ 即可。观察样例可以发现，只要两数不相等就输出 $a_k$，否则无解。

但题目中 $0\leq k$ 并且 $1\leq x$，说明还得特判 $k$ 为 $0$ 的情况。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200005];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	sort(a+1,a+n+1);
	if(!(a[k]-a[k+1])||(!k&&a[1]==1))printf("-1");
	else if(!k)printf("1");
	else printf("%d",a[k]);
	return 0;
}
```


---

## 作者：I_AK_CTSC (赞：0)

# 首先声明
这道题我在洛谷上提交不了，所以我就交在官网了。
![](https://cdn.luogu.com.cn/upload/image_hosting/0dc87nm1.png)


# 题目讲解

这道题大家发现要想求小于等于 $k$ 的 $x$，那么我们肯定得先排序啊，想必大家都知道。

然而，如果只有排序，我也不可能交了那么多次都不对啊……

这是基础的代码，我们在后续会逐渐修改，就先放在这里：

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, k;
ll a[200005];
int main() {
    cin >> n >> k;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    ll p = a[k];
    if (p < a[k + 1]) {//如果都已经相等了，那么如果x等于a[k]了，那么a[k+1]又小于等于x了吧？那小于等于x的数课就大于k个了，那就对不起，无解
        cout << p << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
```

那么，有哪些细节需要我们注意呢？

1. $k = 0$ 时，在我们上述的代码中会直接输出 $0$，但是按照题目中的数据范围，貌似输出的 $0$ 不在这个范围里。

所以，对于 $k = 0$ 的情况，我们要加上特判。

第二版代码：

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
ll n, k;
ll a[200005];
const ll N = 1e9;
int main() {
    cin >> n >> k;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    ll p = a[k];
    if (k == 0) {
        if (a[1] == 1) {
            cout << -1 << endl;
        } else {
            cout << 1 << endl;//这里做一下解释，因为a[i]不为1，而且a[i]又为整数且大于1，那么1一定是满足条件的
        }
        return 0;
    }
    if (a[k] == a[k + 1]) {
        cout << -1 << endl;
    } else {
        cout << a[k] << endl;
    }
    return 0;
}
```
交上去了以后貌似还是过不了，所以还得继续找错误。

那么，竟然可能超出下界，我们就要考虑一下会不会超出上界了。

2. 当我们所求的 $x$ 已经超过了 $10^9$，那么我们直接输出 $10^9$ 即可。


好了，整理一下就是这些了：

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
ll n, k;
ll a[200005];
const ll N = 1e9;
int main() {
    cin >> n >> k;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    ll p = a[k];
    if (k == 0) {
        if (a[1] == 1) {
            cout << -1 << endl;
        } else {
            cout << 1 << endl;
        }
        return 0;
    }
    if (p > N) {
        cout << N << endl;
        return 0;
    }
    if (a[k] == a[k + 1]) {
        cout << -1 << endl;
    } else {
        cout << a[k] << endl;
    }
    return 0;
}
```

谢谢大家。

---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](/problem/cf977c)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf977c)

给出 $n,k$ 和长度为 $n(1\le n\le2\times10^5)$ 的数组 $a(1\le a_i\le10^9)$，问能否找一个数 $x(1\le x\le10^9)$ 满足数组 $a$ 中有 $k(0\le k\le n)$ 个 $\le x$ 的数。没有输出 `-1`。

# 分析
~~这题真的太水了，但有个坑。~~

要求最小的，我们可以先排个序。

然后因为要 $k$ 个数，所以直接看 $a_k$即可。

如果 $a_k = a_{k+1}$（当然也可能一直等于），就会有 $k+m(m\ge1)$ 个数 $\le x$。所以此时无解。

**但是**，$k$ 可能为 $0$。而 $x\ge1$，所以如果 $a_1=1$,无解，否则 $<a_1$、$>0$ 的数均可。

时间复杂度：$O(n\times \log_2 n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, k, a[MAXN];
int main(){
  cin >> n >> k;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  cout << (a[k] == a[k + 1] || (!k && a[1] == 1) ? -1 : max(1, a[k]));//上面说的
  return 0;
}
```

---

## 作者：Patients (赞：0)

### [Less or Equal](https://www.luogu.com.cn/problem/CF977C)

------------

### 分析：

乍一看，这不是排序输出 $ a_k $ 吗？

天真！（不然为什么不放在A题上

![](https://cdn.luogu.com.cn/upload/image_hosting/w8jfy1f5.png)

主要的错误是因为取值范围小端的问题。

$ 0 \le k \le n , 1 \le x \le 10^9 $。

所以要讨论。

- 当 $ k \ne 0 $，答案为 $ a_k $。

- 当 $ k = 0 $：

	+ 当 $ Min \ne 1 $，输出 $ 1 $。
   
   + 当 $ Min = 1 $，输出 $ -1 $。

ps：以上是只是排除坑点，思路看代码。

### Code：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,k;
int a[200005];
signed main()
{
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    if(k==0 && a[1]==1) {cout<<-1;return 0;}
    if(a[k]==a[k+1]) cout<<"-1";
    else
        if(k==0) cout<<1;
        else cout<<a[k];
	return 0;
}
```


---

## 作者：ZZQF5677 (赞：0)

### 解题思路
首先我们排个序，这样就能找到第 $k$ 个数的位置了。

这题就这么简单？有坑！我们分成三个情况：
+ $k = 0$：这个情况我们就要好好注意了，程序可能会输出 $a_0$ 的数，但是 $a_0$ 没有数，就会输出 $0$，但是 $0$ 又不符合题目 $1 \leq x \leq 10^{9}$ 的规定，所以输出 $a_1 - 1$ 的数。就这么完了？没完！我们继续分析：如果 $a_1 - 1 \leq 0$ 岂不是又要不符合 $1 \leq x \leq 10^{9}$ 了吗？所以这里还要加一个特判。
+ 如果 $a_k = a_{k+1}$ 也是不行的，因为如果 $x = a_k$，那 $a_{k+1}$ 也要算在内，就不止 $k$ 个数了。
+ 如果上面的情况都不是，就能放心的输出 $a_k$ 了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[200005], k;
int main() {
  scanf("%lld%lld", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  stable_sort(a + 1, a + 1 + n);
  if (k == 0) {
    if (a[1] - 1 > 0) {
      printf("%lld\n", a[1] - 1);
    } else {
      puts("-1");
    }
  } else if (a[k] == a[k + 1]) {
    puts("-1");
  } else {
    printf("%lld\n", a[k]);
  }
  return 0;
}
```

---

