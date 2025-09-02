# [ABC048C] Boxes and Candies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc048/tasks/arc064_a

$ N $ 個の箱が横一列に並んでいます。 最初、左から $ i $ 番目の箱には $ a_i $ 個のキャンディが入っています。

すぬけ君は次の操作を好きな回数だけ行うことができます。

- キャンディが $ 1 $ 個以上入っている箱をひとつ選び、その箱のキャンディを $ 1 $ 個食べる。

すぬけ君の目標は次の通りです。

- どの隣り合う $ 2 $ つの箱を見ても、それらの箱に入っているキャンディの個数の総和が $ x $ 以下である。

目標を達成するために必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 10^5 $
- $ 0\ <\ =\ a_i\ <\ =\ 10^9 $
- $ 0\ <\ =\ x\ <\ =\ 10^9 $

### Sample Explanation 1

$ 2 $ 番目の箱のキャンディを $ 1 $ 個食べればよいです。 すると、各箱のキャンディの個数は $ (2,\ 1,\ 2) $ となります。

### Sample Explanation 2

たとえば、$ 2 $ 番目の箱のキャンディを $ 6 $ 個食べ、$ 4 $ 番目の箱のキャンディを $ 2 $ 個食べ、$ 6 $ 番目の箱のキャンディを $ 3 $ 個食べればよいです。 すると、各箱キャンディの個数は $ (1,\ 0,\ 1,\ 0,\ 0,\ 1) $ となります。

### Sample Explanation 3

最初から目標が達成されているので、操作を行う必要はありません。

### Sample Explanation 4

すべてのキャンディを食べなければなりません。

## 样例 #1

### 输入

```
3 3
2 2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
6 1
1 6 1 2 0 4```

### 输出

```
11```

## 样例 #3

### 输入

```
5 9
3 1 4 1 5```

### 输出

```
0```

## 样例 #4

### 输入

```
2 0
5 5```

### 输出

```
10```

# 题解

## 作者：小王子2021 (赞：5)

# AT2152 [ARC064A] Boxes and Candies题解

## **题目链接**

------------

[想看题目的戳这](https://www.luogu.com.cn/problem/AT2152)

## **本题的解题思路：**

用贪心，尽量让本次后面（下次前面）尽可能小

重点（~~敲黑板~~）：

1. 要用long long!!! 

![long long 坑点](https://cdn.luogu.com.cn/upload/image_hosting/5zmkk7hv.png)

2. 第一个数需要单独处理

似乎很重要，不然WA四个点

## 话不多说，上代码：


------------


```cpp
#include<bits/stdc++.h>
long long n,a[100010],x,ans,tmp;
int main()
{
  int i;
  scanf("%lld%lld",&n,&x);//long long 坑点
  for (i=1;i<=n;i++)//第一次可以考虑a[1]
  {
    scanf("%lld",&a[i]);
    if(a[i]+a[i-1]>x)
    {
	tmp=a[i]+a[i-1]-x;
	a[i]-=tmp;
	ans+=tmp;
    }//如果两数之和超过，先吃后面的（贪心）
  }
  printf("%lld",ans);//long long 坑点
}
```

**本蒟蒻第一篇题解，各位巨佬谅解一下奇特的码风，谢谢！！**

膜拜同机房巨佬 zzx,lhy!


---

## 作者：Ryo_Yamada (赞：2)

本来看到这题，觉得就是道水题嘛。后来一看数据范围，顿时明白了本题的第一个坑：

$$\text{爆int.}$$

$a_i+a_j-x$有可能爆`int`，要开`long long`.

第二个坑：

$$\text{样例.}$$

~~没错，就是样例。~~ 写完第一版代码后看了一下样例：答案为$0$的时候样例什么也不输出？！虽然觉得奇怪，但还是乖乖打了一个

```cpp
if(cnt) printf("%lld\n", cnt);
```
结果……WA了10几个点。把`if`去掉以后只WA了后4个点。

第三个坑：

$$\text{不够减.}$$

什么是不够减？我选择从前往后枚举，也就是

```cpp
for(int i=0; i<n - 1; i++) {
    if(a[i] + a[i + 1] > x)            
        cnt += a[i] + a[i + 1] - x;
        a[i + 1] -= a[i] + a[i + 1] - x;
    }
}
```
但我忽略了一种情况：如果$a_{i+1} \leq x$，就还得从$a_i$里取糖果。修改之后应该是：

```cpp
for(int i=0; i<n - 1; i++) {
    if(a[i] + a[i + 1] > x) {
        cnt += a[i] + a[i + 1] - x;
        if(a[i] <= x) a[i + 1] = x - a[i];
        else {
            a[i + 1] = 0;
            a[i] = x;
        }
    }
}
```
终于A了。

完整的代码：

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll a[100000], cnt;
int main() {
    ll n, x;
    cin >> n >> x;
    for(int i=0; i<n; i++) {
        scanf("%lld", &a[i]);
    }
    for(int i=0; i<n - 1; i++) {
        if(a[i] + a[i + 1] > x) {
            cnt += a[i] + a[i + 1] - x;
            if(a[i] <= x) a[i + 1] = x - a[i];
            else {
                a[i + 1] = 0;
                a[i] = x;
            }
        }
    }
    printf("%lld\n", cnt);
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

大家好，本蒟蒻又来写题解啦~~~

~~AT 的黄题就是水。~~

[题目传送门](https://www.luogu.com.cn/problem/AT2152)

这个题用到的知识点是贪心。为什么呢？很简单，因为它是一个最值问题，而且有不同的决策。

贪心策略是什么？

如果我们从前往后遍历，那么对于每相邻两个箱子，是先吃左边的还是先吃右边的？

这个问题应该很简单，答案一定是先吃右边的。

拿样例来举个例子，$N=3,x=3,a=\{2,2,2\}$。对于前两个箱子，都有 $2$ 个糖果。如果我们吃掉左边箱子里的，$a$ 就变成了 $\{1,2,2\}$，这时我们发现需要再吃一个糖果才能满足条件。但是如果我们吃掉右边箱子里的，结果就不一样了，$a$ 变成了 $\{2,1,2\}$，此时已经满足条件。

想出了贪心策略，这道题就做完了。AC 代码非常简单。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010];
int main()
{
    int n,x;
    long long sum=0;//不加 long long 见祖宗！！！
    cin>>n>>x;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)
        if(a[i-1]+a[i]>x)//如果还需要再吃
        {
            int num=a[i]+a[i-1]-x;//num 表示当前需要吃的个数。
            if(a[i]>=num)sum+=num,a[i]-=num;//只需要在右边的箱子里吃的情况。
            else sum+=num,a[i-1]-=num-a[i],a[i]=0;//两个箱子里都要吃的情况。
        }
    cout<<sum<<endl;
    return 0;
}
```

求各位 julao 点个赞吧~~~

---

## 作者：Otomachi_Una_ (赞：0)

首先，考虑到 $n\leq10^5$ 考虑贪心。

假设正在处理第 $i+1$ 个数，前 $i$ 个数已处理完毕(相邻之和不超过 $x$)，但第 $i+1$ 个数与其之和大于 $x$ ，那怎么操作好呢？

显然，操作 $i+1$ 个数会更好，因为他对 $i+2$ 个数与其之和也做了影响，比只改第 $i$ 个数更好。

按照上述方法贪心即可。

## _Code_

```cpp
#include<iostream>
#include<cstdio> 
using namespace std;
#define ll long long
const int MAXN=1e5+5;
ll n,s;
ll a[MAXN];
ll ans=0;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]+a[i-1]>s){
			ans+=(a[i]-s+a[i-1]);
			a[i]=s-a[i-1];
		}
	}
	cout<<ans;
	return 0;
}

```
双倍经验 ： P3817

---

## 作者：零殇 (赞：0)

#### 关于题意的一点点小差错

箱子里的糖果不是要多于$1$，而是多于$0$（就是有东西就好了）。

#### 思路

我们从前往后遍历。

对于每一次到达的$i$，我们判断$a[i]$与$a[i-1]$之和是否大于$x$。

如果不是，则不进行任何操作。

如果是的话，由于$a[i-1]$对我们后面的操作没有影响，而$a[i]$因为我们下一次循环还会用到，因此我们就优先修改$a[i]$。

我们用$temp$表示当前$a[i]$,$a[i-1]$之和减去$x$，如果$temp$大于$0$，就让$a[i]$减去$temp$。

这里有一个小细节，因为$a[i-1]$是绝对小于等于$x$的，因此不用担心$a[i]$小于$temp$的情况（因为做的时候没有想到这一点，所以下面的代码和我的思路有点不同，非常抱歉）。

还有，对于$a[1]$，我们要特判。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
long long a[100001],x;
long long sum;
int main() {
	int n;
	scanf("%d%lld",&n,&x);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	if(a[1]>x) {
		sum+=a[1]-x;
		a[1]=x;
	}
	for(int i=2;i<=n;i++) {
		long long temp=a[i]+a[i-1]-x;
		if(temp>0) {
			sum+=temp;
			if(a[i]>temp)
				a[i]-=temp;
			else{
				temp-=a[i];
				a[i]=0;
				a[i-1]-=temp;
			}
		}
	}
	printf("%lld\n",sum);
	return 0;
}
```

完结撒花~

---

## 作者：翼德天尊 (赞：0)

**非常经典的贪心题。**

## STEP 1 题目大意

给定一段序列，要求序列任意两个相邻的数之和都小于 $x$，求至少需要将这个序列里的数减去多少？

## STEP 2 浅谈做法

所有题解都说这道题是贪心，但贪心策略到底是怎么得出来的呢？

>任何 $2$ 个相邻的箱子都不多于 $x$ 个糖果。

这句话非常重要！两个相邻的箱子？那取哪个箱子里的呢？

假设我们从前往后取，现在该考虑第 $a$ 个箱子和第 $a+1$ 个箱子。因为我们已经取到这里，所以前面的箱子就可以不用再管了。如果优先取第 $a$ 个箱子，则第 $a+1$ 个箱子可以少取；如果取第 $a+1$ 个箱子，那么第 $a$ 个箱子和第 $a+2$ 个箱子都可以少取，**两倍贡献啊**！我们怎能不优先考虑后面的箱子呢？

所以我们得出结论：对于每一组箱子（相邻两个），取的话都优先考虑后一个箱子。

而在具体实现的过程中，我们也没有必要将所有箱子里的糖果都一次性储存，太耗费空间了。考虑到只有上一个箱子会对本次箱子的决策产生影响，所以我们只需要用两个变量滚动记录糖果数即可。

对了，注意数据范围（好心提醒）——开 $long\ long$！

## STEP  3 AC code

```cpp
#include<cstdio>
long long n,a,b,x,ans;
int main(){
	scanf("%lld %lld",&n,&x);
	for (int i=1;i<=n;i++){
		scanf("%lld",&a);
		if (a+b>x){//如果大于
			int zc=a+b-x;//记录需要减去的
			a-=zc,ans+=zc;
		}
		b=a;//滚动储存
	}
	printf("%lld\n",ans);
	return 0;
}//15行超短代码
```


---

## 作者：YosemiteHe (赞：0)

学校考试出原题，来发一篇题解。

这题其实就是贪心。

如果 $a_i + a_{i - 1} > x$，那就在 $a_{i}$ 中啃，因为啃了 $a_i$ 那 $a_{i - 1}$ 和 $a{i + 1}$ 都可以少啃一些，这样就可以求到最小值。

统计一下啃掉的总数量即可。

当 $i = 1$ 时，如果 $a_i > x$，只要将数组定义在主函数外边，自动初始化为 $0$，所以不用担心答案出错。

这题是考试的 $T1$，写了N次都是 $0$ 分，人直接垮掉了，考试结束后发现：
- $2\ \leq\ N\ \leq\ 10^5$
- $0\ \leq\ a_i\ \leq\ 10^9$
- $0\ \leq\ x\ \leq\ 10^9$

$a_i + a_{i - 1}$ 直接爆 $int$。

上代码：
```cpp
#include <iostream>//头文件
#include <cstdio>
#include <cctype>//isdigit要用到<cctype>
#define int long long//注意用long long，宏定义成int，方便
using namespace std;//命名空间
inline int read() { //快读
	int s = 0, v = 1;
	char c = getchar();
	while (!isdigit(c)) {if (c == '-') v = -1; c = getchar();}
	while (isdigit(c)) s = s * 10 + c - '0', c = getchar();
	return s * v;
}
inline void write(int x) { //快写
	if (x < 0) x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int n = read(), x = read(), a[100005], ans;//定义+读入
signed main(void) { //主函数
	for (int i = 1; i <= n; ++i) {
		a[i] = read();//读入
	}
	for (int i = 1; i <= n; ++i) {
		if (a[i] + a[i - 1] > x) ans += a[i] + a[i - 1] - x, a[i] -= a[i] + a[i - 1] - x;//贪心，啃掉a[i]
	}
	write(ans);//输出答案
	return 0;
}
```

---

