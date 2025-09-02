# Mischievous Mess Makers

## 题目描述

It is a balmy spring afternoon, and Farmer John's $ n $ cows are ruminating about link-cut cacti in their stalls. The cows, labeled $ 1 $ through $ n $ , are arranged so that the $ i $ -th cow occupies the $ i $ -th stall from the left. However, Elsie, after realizing that she will forever live in the shadows beyond Bessie's limelight, has formed the Mischievous Mess Makers and is plotting to disrupt this beautiful pastoral rhythm. While Farmer John takes his $ k $ minute long nap, Elsie and the Mess Makers plan to repeatedly choose two distinct stalls and swap the cows occupying those stalls, making no more than one swap each minute.

Being the meticulous pranksters that they are, the Mischievous Mess Makers would like to know the maximum messiness attainable in the $ k $ minutes that they have. We denote as $ p_{i} $ the label of the cow in the $ i $ -th stall. The messiness of an arrangement of cows is defined as the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

## 说明/提示

In the first sample, the Mischievous Mess Makers can swap the cows in the stalls $ 1 $ and $ 5 $ during the first minute, then the cows in stalls $ 2 $ and $ 4 $ during the second minute. This reverses the arrangement of cows, giving us a total messiness of $ 10 $ .

In the second sample, there is only one cow, so the maximum possible messiness is $ 0 $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
1 10
```

### 输出

```
0
```

# 题解

## 作者：MurataHimeko (赞：4)

## [CF645B](https://www.luogu.com.cn/problem/CF645B)


------------


### 思路

每次将第 $i$ 和第 $n-i+1$ 位置上的数字交换，其中第 $i+1 \sim n-i$ 个数字和交换后的第 $i$ 位数字总共会产生 $n-2i$ 的贡献，交换后的第 $n-i+1$ 位数字则会和第 $i \sim n-i$ 位数字新产生 $n-2i+1$ 的贡献。循环一遍统计答案即可。


------------

### 注意

交换最多 $\lfloor \frac{n}{2} \rfloor$ 次，此后再交换会将更小的数从后置换至前，逆序对数则会减少。


------------

### 代码


------------
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define INF 0x3f3f3f3f
// #define int long long

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

#define gc getchar

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;
int n, k;
long long ans;

/*
1 2 3 ... n 
n 2 3 ... 1   +N-2+(N-1 - (1-1))
n n-1 3 ... 1  +N-4+(N-2 - (2-1))

1 2 3 4 5
5 2 3 4 1
5 4 3 2 1
*/

int main() {
    read(n), read(k);
    int lim = (n>>1);
    lim = min_(lim, k);
    for(register int i(1); i <= lim; ++i) {
        ans += (n-(i<<1) + (n-i+1) - i);
    }  
    out(ans);
}
```


------------

感谢您能阅读本篇博客！

---

## 作者：AstaSunch_ (赞：2)

# $\mathtt{0x00}$ 序

蒟蒻的第 $\color{red}\mathbf{22}$ 篇题解。

# $\mathtt{0x01}$ 明

给定长度为 $n$ 的排列（$1,2,3,4\cdots n$），使其在**小于等于** $k$ 次操作后[逆序对](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554)数量最多。

# $\mathtt{0x02}$ 解

我们知道，每次交换都会对序列产生 $2\times(n-2\times i)+1$ 的贡献，因此直接模拟即可。

注意只能交换 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 次，否则会将减少逆序对数量（更小的数就跑到前面去了）。

# $\mathtt{0x03}$ 文

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum;
int main(){
    cin>>n>>k; 
    for(int i=1;i*2<=n&&i<k;i++)
    	sum+=2*(n-2*i)+1;
    cout<<sum;
}
```


---

## 作者：saixingzhe (赞：2)

# 题意
有一个长度为 $n$ 的排列，从 $1\sim n$（即 $1, 2, 3, 4, \cdots$ ），给定交换次数 $k$，要求使用 **小于等于 $\bm k$** 次交换使得逆序对数量最多，最多的逆序对数量。

逆序对是指设 $A$ 为一个有 $n$ 个数字的有序集 $(n>1)$，其中所有数字各不相同。逆序对是指 $1≤i<j≤n$ 而且 $A_i> A_j$，则 $<A [i], A [j]>$ 这个有序对称为 $A$ 的一个逆序对。
# 思路
很明显，循环模拟每次增加的逆序对数量，当次数大于 $k$ 时终止，硬算即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ans;
int main(){
    cin>>n>>k; 
    for(int i=1;i*2<=n;i++){
	if(i>k) break;
        ans+=2*(n-2*i)+1;//计算每次增加的逆序对
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：yuangq (赞：1)

这题只需一一计算即可

~~~
#include<bits/stdc++.h>
#define MAXN 10005
#define LL long long
using namespace std;
long long n,k,s;
int main()
{
    cin>>n>>k;//输入 
    for(int i=1;i*2<=n;i++)//不用再循环了 
	{
		if(i>k)
		{
			break;//已经用完次数了 
		}
        s=s+2*(n-2*i)+1;//计算增加的逆序对 
    }
    cout<<s;//输出 
    return 0;
}
~~~

---

## 作者：yangzd (赞：0)

# 题目大意：

给定步数和排列，每步可以交换两个数，问最后逆序数最多是多少对？

# 分析：

看例子就能看出来肯定是不断往中间逼近，然后交换头尾两个，给定交换的对数，直接算就好了，复杂度 $O(1)$。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
    long long n,m;
    
    cin >> n >> m;

    long long res=0,ans=min(n/2,m);
    
    res=(n-1+(n-ans+1))/2*ans+(n-2*ans+n-ans-1)/2*ans;
    
    cout << res << endl;

    return 0;
}
```

---

