# [ABC146C] Buy an Integer

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc146/tasks/abc146_c

高橋くんは整数を $ 1 $ つ買いに整数屋さんに行きました。

整数屋さんには $ 1 $ 以上 $ 10^9 $ 以下の整数が売られていて、整数 $ N $ を買うためには $ A\ \times\ N\ +\ B\ \times\ d(N) $ 円が必要です。ここで、$ d(N) $ は $ N $ の十進表記での桁数です。

高橋くんの所持金が $ X $ 円のとき、高橋くんの買うことのできる最も大きい整数を求めてください。ただし、買うことのできる整数が $ 1 $ つもない場合は $ 0 $ を出力してください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ A\ \leq\ 10^9 $
- $ 1\ \leq\ B\ \leq\ 10^9 $
- $ 1\ \leq\ X\ \leq\ 10^{18} $

### Sample Explanation 1

$ 9 $ の値段は $ 10\ \times\ 9\ +\ 7\ \times\ 1\ =\ 97 $ 円で、これが買うことのできる最大の整数です。 他の整数の値段の例をいくつかあげると - $ 10:\ 10\ \times\ 10\ +\ 7\ \times\ 2\ =\ 114 $ 円 - $ 100:\ 10\ \times\ 100\ +\ 7\ \times\ 3\ =\ 1021 $ 円 - $ 12345:\ 10\ \times\ 12345\ +\ 7\ \times\ 5\ =\ 123485 $ 円 です。

### Sample Explanation 2

お店に売られている最大の整数を買うことができます。入力が $ 32 $ bit整数型に収まらないことがあることに注意してください。

## 样例 #1

### 输入

```
10 7 100```

### 输出

```
9```

## 样例 #2

### 输入

```
2 1 100000000000```

### 输出

```
1000000000```

## 样例 #3

### 输入

```
1000000000 1000000000 100```

### 输出

```
0```

## 样例 #4

### 输入

```
1234 56789 314159265```

### 输出

```
254309```

# 题解

## 作者：CYZZ (赞：4)

# [Buy an Integer](https://www.luogu.com.cn/problem/AT_abc146_c)
这难道不是一道清新的二分吗？？？
# 思路分析
题目已经说得很明确了，就是求最大的能满足要求的正整数。这题的单调性也很好推，因为 $\log_{10}n \le \log_{10}(n+1)$ 且 $n < n+1$，所以若 $n$ 满足要求，则比 $n$ 小的数一定满足要求。这题就很明确用二分推了。这里求 $mid$ 的位数可以用系统自带的函数。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,ans;
bool check(int mid)
{
	int x=log10(mid)+1;
	return (a*mid+b*x)<=c;
}
signed main()
{
	scanf("%lld%lld%lld",&a,&b,&c);
	int l=0,r=1e9;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}
	printf("%lld",r);
	return 0;//先别急着走
}
```
# 后记
对于像我这样的新手而言，二分其实是有些不友好的，尤其是看题解的时候。
```cpp
l<r 还是 l<=r
mid=(l+r)/2 还是 mid=(l+r+1)/2
```
这里简单提一嘴。

- 判断条件为 $l<r$ 时最终一定在 $l=r$ 时跳出循环，而判断条件为 $l\le r$ 时会在最后 $l=r$ 时再 check 一次。
- $mid$ 的取值和下面 $x$ 的取值有关。如果这样写：
```cpp
while(l<r)//跟while(1)没啥区别 
{
	int mid=(l+r)/2;//错误示例，应为mid=(l+r+1)/2; 
	if(check(mid))
		l=mid;
	else
		r=mid-1;
}
```

当程序来到 $l=r-1$ 时，若 $check(mid)=1$，程序会进入死循环。若 $mid=(l+r+1)/2$，则后面 $mid$ 会更新为 $r$，这样就可以避免死循环的问题。


```cpp
int binary_search1(int x)
{
	int l=1,r=n,mid;
	while(l<r)
    {
		mid=l+r>>1;
		if(a[mid]<x) 
        	l=mid+1;
		else 
        	r=mid;
	}
	return l;
}//两种写法不同，效果相同。
int binary_search2(int x)
{
	int l=1,r=n,mid,ans;
	while(l<=r)
    {
		mid=l+r>>1;
		if(a[mid]<x) 
        	l=mid+1;
		else 
        	r=mid-1,ans=mid;
	}
	return ans;
}
```
本蒟蒻文采不好，实在不懂就戳[这儿](https://blog.csdn.net/weixin_45636061/article/details/124096599)，引自 CSDN，Ethan-Code。还要感谢 @[_ maojun _](https://www.luogu.com.cn/user/350297) 大佬更正的亿些笔误。

希望本篇题解可以帮到大家！！！

---

## 作者：TLEWA (赞：4)

看到题解区是清一色二分啊，这道题二分理论复杂度是 $O(log^2 n)$ 的，不是最快的，来发篇 $O(\log n)$ 的。

我们可以将题面给出的算式进行一个拆分，先计算出这个整数的位数，可以这么计算：

设位数为 $x$，$c$ 最小的情况下，构造出来的数一定是 $10^{x-1}$。我们只要解方程判断一下就知道这个数字可不可以是这个位数了。

由于位数最多为 $\log n$，且判断耗时 $O(1)$，所以这部分是 $O(\log n)$ 的。

解出了这个整数的位数，我们将位数带入这个方程，发现只有一个未知数了，于是可以 $O(1)$ 解出另一个未知数。注意，如果解出来的未知数的位数比上面求出的大，那么应该将其变为 $10^x-1$。

总时间复杂度 $O(\log n)$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

unsigned long long a,b,c,summ=1; 

int main() {
	cin >> a >> b >> c;
	if(1000000000*a+10*b <= c) {
		cout << 1000000000 << endl;
		return 0;
	}else {
		unsigned long long i;
		for(i=1;i<=10;++i) {
//			cout << summ << ' ' << i << endl;
			if(summ*a+i*b>c) {
				--i;
				break;
			}
			summ*=10;
		}
		cout << min((c-(i*b))/a,summ-1) << endl;
	}
	
	return 0;
}

```

顺便吐槽一下翻译，没有准确还原题意

---

## 作者：AbsMatt (赞：2)

## [题目传送器](https://www.luogu.com.cn/problem/AT_abc146_c)

# 题意
令 $x$ 的位数为 $g$，求 $x_{max}$ 使 $x \times a+g \times b \le c$。

# 思路
本题使用的是**二分答案**算法，只需要二分 $i_{max}$ 使 $i \times a$ 加上 $b$ 乘以 $i$ 的位数小于等于 $c$。

一下给予了两种求 $i$ 的位数的方法，但时间复杂度基本没有区别。

1.

```cpp
int digit(int x){
	int g=0;
	while(x) g++,x/=10;
	return g;
}
```
2.

```cpp
int digit(int x){
	return log10(x)+1;
}
```

## 特判

∵ $a \ge 1$ 且 $ans_{cost} \le 10^9$。

∴ $ans \le 10^9$。

---
分析完后本题就是一道非常模板的二分答案了，时间复杂度为 $O(\log_{2}c)$。


## AC Code
```cpp
#include<bits/stdc++.h>  // 开始
using namespace std;
const long long inf=1e9;  // 用于特判
long long n,m,k,ans=0;
bool check(long long x){  // check函数
	return (n*x+int(log10(x)+1)*m<=k);
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);  // 输入
	if(inf*n+10*m<=k){  // 特判 
		printf("%lld",inf);
		exit(0);
	}
	int l=0,r=1e9;
	while(l<=r){  // 二分答案板子
		int mid=(l+r)>>1; // 和 int mid=(l+r)/2; 一样 
		if(check(mid)){	// 合法 
			ans=mid;
			l=mid+1;
		}
		else	r=mid-1;  // 不合法 
	}
	printf("%lld",ans);  // 输出
	return 0;  // 再见 
}
```

---

## 作者：Composite_Function (赞：1)

# 思路

设 $digit(x) = \lceil \log _ {10} \rceil$，即 $x$ 的位数。

显然地，$digit(x)$ 关于 $x$ 有单调性。因此，所花费的价格，$x \times a + digit(x) \times b$，具有单调性。

想到单调性，我们就能想到 ~~卡常的~~ 的二分来做了，不会二分的戳这里：[link](https://www.luogu.com.cn/blog/fgxseven/qian-tan-er-fen)。

------------

# 代码

```
# include <bits/stdc++.h>
using namespace std;

# define int long long

int a, b, c;

int digit(int x) // 即文中的 digit() 函数
{
    int ans = 0;
    while (x > 0)
        ++ans, x /= 10;
    return ans;
}
bool judge(int x) // 检测是否成立
{
    int n = x * a;
    int m = digit(x) * b;
    return (n + m <= c);
}
int find(int l, int r)
{
    int mid = (l + r) / 2;
    if (l > r) return 0;
    if (judge(mid) == false) return find(l, mid - 1); // 如不成立，则继续找更小的整数
    else return max(mid, find(mid + 1, r)); // 如成立，则找有没有更大的
}

signed main()
{
    cin >> a >> b >> c;
    if (judge(1e9) == true) // 由于商店只卖 1 ~ 1e9 的整数，所以需要特判（顺便吐槽翻译）
        cout << "1000000000" << endl; // 注意这个点，不要直接写 1e9
    else cout << find(0, 1e9) << endl; // 注意区间是 [0, 1e9] 而不是 [1, 1e9]
    return 0;
}
```

---

## 作者：洛璟 (赞：1)

## Solution：

这题较水，大概为橙题+到黄题。

不妨设答案的位数为 $n$，这个答案为 $m$。

我们不难发现，$b$ 只在进位时才会增加价格，因此我们不妨计算出 $a \times m + b \times n$ 何时会超过给定的钱数。（$m$ 为10的倍数）然后，我们再降低，保证 $b \times n$ 的值不会变，这时这个问题就变成了 $x$ 元钱能够购买的物品的最大整数了。

但是这个方法需要增加多个特判，细节比较多，有点繁琐（~~但是它时间复杂度低啊QwQ~~

~~我因为这些特判调了一个多小时的代码，洛璟酱太菜了QwQ。~~

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1000000000
using namespace std;
int a, b, s, base = 1, k = 1;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main()
{
    a = read();
    b = read();
    s = read();
    if (s < a + b)//特判，判断是否为0
    {
        printf("0");
        return 0;
    }
    while (1)//找出比给出钱数大的位数与整数，base记载整数，k记载位数
    {
        if (base * a + k * b >= s) break;
        if (base >= INF)//特判，判断是否超过上限
        {
            printf("%lld", INF);
            return 0;
        }
        base *= 10;
        k++;
    }
    if (base * a + k * b == s)//特判恰好等于的情况，不知道是否必要QwQ
    {
        printf("%lld", base);
    }
    else
    {
        int qwq = base;
        base = base / 10;//将k与base减去，使其所需钱数比总钱数小
        k--;
        s -= k * b;
        s -= base * a;
        base += s / a;//判断剩下的钱能买多大的物品
        if (base >= qwq)//特判，判断增加后的数字是否超过先前规定的比钱数大的数字。
        {
            base = qwq - 1;//超过的话，先前已证明无法购买，故为规定数字减一。
            printf("%lld", base);
        }
        else printf("%lld", base);
    }
    return 0;
}
```


---

## 作者：KazamiHina (赞：1)

 题目大意：

给定$a,b,c$三个数

定义一个整数的价格为

这个整数$*a+$这个整数的位数$*b$

请判断用$c$元钱能买到的最大的整数

 思路：

因为数据很大，有$10^9$，所以不能用暴力求解，会 $T$ 到 飞 起

所以可以用二分的方法快速求解

在$1$~$10^9$的范围内进行二分答案

如果$mid$可以买到，那么收缩左区间

否则收缩右区间

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long//随手define int long long 好习惯（
#define maxn 1000000000//最大的数(即10^9)

using namespace std;

int a,b,x;
int ans;

inline int getf(int w){//获取位数的函数
	int tot=0;
	while(w!=0){
		w/=10;
		tot++;
	}
	return tot;
}

inline int solve(int l,int r){//二分答案
	while((a*l+b*getf(l)<=x) && (abs(l-r)>1)){//一直二分
		int mid=(l+r)>>1;//求出中点
		if(a*mid+b*getf(mid)<=x)l=mid;//如果能买就收缩左区间
		else r=mid;//否则输出右区间
	}
	return l;//返回左端点
}

signed main(){
	scanf("%lld%lld%lld",&a,&b,&x);
	if((maxn*a)+getf(maxn)*b<=x)return printf("1000000000"),0;//特判：如果最大的都能买，那么直接输出最大的数
	printf("%lld",solve(0,maxn));//二分求解
	return 0;
}
```

$qwqwq$

---

## 作者：high_sky (赞：0)

### 解题思路
二分题目中的答案，用自定义函数进行检查是否可行，得到最大的攻击力，但是要注意的是：**攻击力范围为：$[0,10^9]$**

因此我们的右指针只能为 $10^9$ 不能再大，不然就会 `Wrong Answer`！

如何二分，这是个问题？

### 二分
模板如下:
```cpp
int l=1,r=n;//按照数组的二分查找
while(l<=r)
{
	int mid=l+r>>1;
	if(a[mid]==x) return mid;//x即为说找
	if(a[mid]<x)l=mid+1;
	else r=mid-1;
}
```
二分每一次都可以淘汰掉一半的答案，这使他的时间复杂度为：$O(\log n)$

注意的是：**这个序列必须是单调的，单调即为朝着一个方向发展**

### Code
```cpp
#include<iostream>
#define int long long
using namespace std;
int a,b,x;
int get_wei(int n){
	int len=0;
	while(n)len++,n/=10;
	return len;
}
bool check(int k){
	return a*k+b*get_wei(k)<=x;
}
signed main(){
	cin>>a>>b>>x;
	int l,r,ans=0;
	l=0,r=1e9;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
} //100000000000
//   49999999994--->错误的
```

---

## 作者：SSSdyzs (赞：0)

### 题目注意：
- 答案的范围是**大于等于** $1$，**小于等于** $10^9$。 

- 若无解，**输出** $0$。~~样例没有。~~


------------

### 题目分析：
 1. #### 无解
 
 	由数据范围得，选整数 $1$ 时价格最小，若此时不符合条件，直接输出 $0$；
    
    特判：
```cpp
    if(a+b>x){
        printf("0");
        return 0;
    }
```

 2. #### 有解
 
    可以想到暴力枚举答案，找到满足条件的最大整数。

    判断条件：
```cpp
    ll sum=mid*a,num=0;
    while(mid!=0){
        mid/=10;
        num++;
    }//记录mid的位数
    return (sum+num*b)<=x;//判断，若价格小于等于x，符合条件，返回1
```

**但是** $10^9$ 的数据，不 TLE 才怪。
所以想到用**二分**，来减少枚举次数。

用 $l$ 来记录左边界，初始值为 $1$；用 $r$ 来记录右边界，初始值为 $10^9$。当 check 函数返回 $1$ 时，代表 $mid$ 符合条件，收缩左区间；否则，收缩右区间。


------------

### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,x,l=1,r=1000000000;//左右边界赋初始值
inline ll read(){
    char c=getchar();ll x=0,f=1;
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')c=getchar(),f=-1;
    while(c<='9'&&c>='0'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}// 快读
bool check(ll mid){
    ll sum=mid*a,num=0;
    while(mid!=0){
        mid/=10;
        num++;
    }//记录mid的位数
    return (sum+num*b)<=x;//判断，若价格小于等于x，符合条件，返回1
}
int main(){
    a=read();b=read();x=read();
    if(a+b>x){
        printf("0");
        return 0;
    }//特判无解情况
    while(l<r){
        ll mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }//二分模板寻找答案
    printf("%lld",r);
    return 0;//好习惯
}
```


------------
### 关于二分：
请参考[二分查找及边界问题](https://blog.csdn.net/weixin_45636061/article/details/124096599)。
引自CSDN，Ethan-Code。

---

