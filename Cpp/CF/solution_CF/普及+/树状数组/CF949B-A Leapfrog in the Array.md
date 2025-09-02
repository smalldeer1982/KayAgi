# A Leapfrog in the Array

## 题目描述

## 题意:
Dima是一名初级程序员。 在他的工作中，他经常不断地重复以下操作：从数组中删除每个第二个元素。 有一天，他对这个问题的解决方案感到厌倦，他提出了以下华丽的算法。

假设有一长度为2n的数组，最初的数组包含从1到n的n个数字，数字i位于序号为2i - 1的单元格中（序号从1开始编号），并且数组的其他单元格为空。每个步骤你需要选择一个最大序号的非空单元格，并将其中的数字移动到它左边最近的空单元格。一直循环该过程，直到所有n个数字出现在数组的前n个单元格中。例如，如果n = 4，则数组更改如下：
![这里写图片描述](http://codeforces.com/predownloaded/1e/83/1e838f4fb99d933b7259fbfe5b8722990c08d718.png)
您必须编写一个程序，输出在该算法完成后，序号为x（1≤x≤n）的单元格中的数字。

## 样例 #1

### 输入

```
4 3
2
3
4
```

### 输出

```
3
2
4
```

## 样例 #2

### 输入

```
13 4
10
5
4
8
```

### 输出

```
13
3
8
9
```

# 题解

## 作者：lichenghan (赞：7)

# CF949B题解
[**传送门**](https://www.luogu.com.cn/problem/CF949B)

一看，没什么思路，手算几组，找规律：
```
1 2 34
1 243
1324

1 2 3 45
1 2 354
1 2435
15243

1 2 3 4 56
1 2 3 465
1 2 3546
1 26354
142635

1 2 3 4 5 67
1 2 3 4 576
1 2 3 4657
1 2 37465
1 253746
1625374

1 2 3 4 5 6 78
1 2 3 4 5 687
1 2 3 4 5768
1 2 3 48576
1 2 364857
1 2736485
15273648

```

我们~~不难~~想到把一个数组按下标奇偶性分成两半（以 $n=8$ 为例）
```
奇数：1 2 3 4
偶数： 5 7 6 8
```
奇数的规律很简单，不多赘述；

那么偶数时呢？

再次分成两类：

1. $n$ 为偶数（以 $n=8$ 为例）：
```
偶数： 5 7 6 8
```
~~也不难~~发现，这跟 $n=4$ 的情况好像啊！
就是每一个数加了4啊！

搞定。

2. $n$ 为奇数（以 $n=7$ 为例）：
```
偶数： 6 5 7
```
这个就有点不一样了，因为 $n=3$ 时的数组为 `1 3 2` ，而这个减掉4后是
`2 1 3`

~~又不难~~发现，就是把最后一个放在了第一位，其他向后一位。

搞定。

总结一下，设 $f_{n,k}$ 是长度为 $n$ 的数组的第 $k$ 位，则有：
$$
f_{n,k}=
\begin{cases}
\lceil \frac{k}{2} \rceil && k \mod 2=1\\
f_{\frac{n}{2},\frac{k}{2}}+\frac{n}{2} && k \mod 2=0&n\mod2=0\\
f_{\lfloor\frac{n}{2}\rfloor,\lfloor\frac{n}{2}\rfloor} +\lceil\frac{n}{2}\rceil&& k=2&n\mod2=1\\
f_{\lfloor\frac{n}{2}\rfloor,\lfloor\frac{k}{2}\rfloor-1} +\lceil\frac{n}{2}\rceil&& k\mod2=0 & n\mod2=1
\end{cases}
$$
~~不确定的话可以继续算几组大的~~

## 规律证明

如果 $k$ 为奇数，那么它根本没动过，就是操作前的样子；

然后，我们可以把整个操作视为2个部分：

1. 后 $\lfloor\frac{n}{2}\rfloor$ 个按规律操作；
2. 把后 $\lfloor\frac{n}{2}\rfloor$ 个“插进前面的缝隙”。

如图：**UPD:图炸了，且找不回来了qwq**
![](https://cdn.luogu.com.cn/upload/image_hosting/d48qp3bz.png)

当 $n$ 为偶数时，后面的数一个跳了一次，结果自然是按顺序的；

当 $n$ 为奇数时，后面的数除了最后一个跳了2次，其他都跳了一次，就有了最后一个移到第一个，其他往后一个的~~奇葩~~规律

于是，每个数组长为 $n$ 的询问可以从长为 $\frac{n}{2}$ 的询问转移过来，考虑递归，时间复杂度 $O(q \log n)$ 。

## code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long calc(long long n,long long pl){
	if(pl%2) return (pl+1)/2; //k为奇数时
	if(n%2==0){//n为偶数时
		return n/2+calc(n/2,pl/2);
	}
	else{//n为奇数时
		if(pl==2) return (n+1)/2+calc(n/2,n/2);
		else return (n+1)/2+calc(n/2,(pl-2)/2);
	}
}
int main(){
	long long n,q,x;
	scanf("%lld%lld",&n,&q);
	while(q--){
		scanf("%lld",&x);
		printf("%lld\n",calc(n,x));
	}
}
```
**Tips:注意上取整与下取整的区别！**

---

## 作者：vegetabird (赞：3)

这是一道很有意思的数学题。数据范围是2e5，可是单次询问复杂度可以是$\Omega(1)$的。作为一道Cf div.1 的B题，这好像很良心。

对于一个数$x$，假设在它或开始时的位置的后面的数有$t$个，则$x$的第一次移动会使它的位置减少$(2t+1)$。

在一次移动后，假设一个数的位置减少了$x$，那么直到它的下一次移动前，会有$x-1$个数移动。这$x-1$个数会占据$x-1$个空位。所以这个数在下一次移动后会移动到右数第$x$个空位。即这个数下一次移动位置减少$2x$。

那么我们可以发现，一个数$k$如果移动了$q$次，则位移为$[2(n-k)+1]*(2^q-1)$。 

所以我们结合题意，假设数$k$移动了$q$次后来到了位置$x$。则我们列出方程：

$(2k-1)-x=[2(n-k)+1]*(2^q-1)$

$2n-x=[2(n-k)+1]*2^q$

$2(n-k)+1=\frac{2n-x}{2^q}$

显然，$2(n-k)+1$是一个奇数。所以$2(n-k)+1$的二进制表示等于将$2n-x$表示为二进制后抹去最后所有的$0$，这可以通过除以$lowbit$（就是树状数组中的$lowbit$）实现。即：
```
2*(n-k)+1=(2*n-x)/((2*n-x)&(x-2*n))
```
然后我们就可以求出$k$，即答案啦。

至于标程，就应该不需要了吧。。

---

## 作者：王熙文 (赞：1)

## 前言

之前找 CF 的紫题最低评分是多少，然后找到了这题，想了半天不会。

结果今天又看到了这题，想了 30min 左右终于会了。

果然人还是在进步的。

## 思路

考虑先打一个 $n=14$ 的变化的表。

![](https://cdn.luogu.com.cn/upload/image_hosting/kmvc5tqx.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我们可以把每一个数每次的移动格数组成的序列列出来：

$14: 1 \ \ 2 \ \ 4 \ \ 8$

$13: 3 \ \ 6 \ \ 12$

$12: 5 \ \ 10$

$11: 7$

$10: 9$

$9: 11$

$8: 13$

可以发现，每一个数的序列都是公比为 $2$ 的等比数列！

为什么呢？可以这么理解：如果某数某一次移动了 $a$ 个格子，则这 $a$ 个格子之间的 $a-1$ 个数都会在这个数下一次移动之前插到前面的空白，这个数就只能移动到后面的第 $a$ 个空白，即移动了 $2a$ 个格子。

现在来考虑每个数的等比数列的第一项是什么。每一个数（设这个数为 $y$），都要移动到最后一个没有被比它大的 $n-y$ 个数占领的格子，可以发现移动格数为 $2 \times (n-y)+1$。

现在便可以确定一个数移动 $k$ 次后的位置了。若移动的数是 $y$，$y$ 的等比数列第一项为 $a_1$，则 $y$ 移动 $k$ 次会总共移动等比数列前 $k$ 项的和 $a_1 \times 2^k - a_1$ 个格子。又知道 $y$ 的初始位置为 $2 \times y - 1$，所以 $y$ 移动 $k$ 次后会变到 $2 \times y - 1 - (a_1 \times 2^k - a_1)$。

因为这些等比数列每一次都为原来的 $2$ 倍，所以它的长度最多为 $\log$ 量级。考虑枚举查询的 $x$ 通过某数移动几次到这个位置的（设当前枚举到的数为 $k$）。易发现 $2 \times y - 1 - (a_1 \times 2^k - a_1)$ 是单调递增的，所以我们可以二分数 $y$ 并检查它移动 $k$ 次之后与 $x$ 的关系。最终找到最接近的，看是否等于 $x$ 即可。

如果找到了，答案即为 $y$。

## 参考代码

如果直接按照上述方法做会 TLE，可以加一个小优化：走 $k$ 步的答案一定大于等于走 $k-1$ 步的答案。加上优化之后再简单卡常便可以卡着时限过了。。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define int __int128
using namespace std;

long long n,q;

int pow2[70];

inline int calc(const int &x,const int &k) // 计算一个数 x 走 k 跳 k 步后的位置
{
	// (n-x)<<1|1 就是 a_1
	return 2*x-1-(((n-x)<<1|1)*pow2[k]-((n-x)<<1|1));
}

signed main()
{
	pow2[0]=1;
	for(int i=1; i<=62; ++i) pow2[i]=pow2[i-1]*2;
	long long x;
	cin>>n>>q;
	while(q--)
	{
		cin>>x;
		int lastans=1;
		for(int i=0; i<=61; ++i) // 枚举每个数跳了几次（没跳为一次）
		{
			int l=lastans,r=n,mid; // 二分跳的那个数
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(calc(mid,i)>=x)
				{
					lastans=mid;
					r=mid-1;
				}
				else l=mid+1;
			}
			if(calc(lastans,i)==x)
			{
				cout<<(long long)lastans<<'\n';
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：_FL_ (赞：1)

## $ \texttt{CF949B} $  

---

### 题意：  

有一个长度为 $ 2n $ 的数组，第 $ 2i-1 $ 个位置上有数 $ i,1\le i\le n $  

每次将数组中最后一个数向前移动到第一个空位，询问 $ q $ 次最终数组第 $ x $ 位的值  

---

### 思路：  

发现每个数都要等到后面全是空位时才会移动位置，所以数组的前 $ n $ 位会保留初始状态  

那么我们就只需要考虑后面的数跳到前 $ n $ 位中的空位上的顺序  

看看 $ n=6 $ 的情况：  

$ 1\ 4\ 2\ 6\ 3\ 5\ 4\ 6\ 5\ 6\ 6 $  

上面的数组显示了整个移动的过程  

去除掉初始位置上的数：  

$ .\ 4\ .\ 6\ .\ 5\ .\ 6\ .\ 6\ . $  

我们看三个 $ 6 $ 之间的距离分别是 $ 4,2 $，不妨猜想每次间隔距离减半  

很容易发现这个结论是正确的，因为从后面往前移，每次移动会把最后面的 $ y $ 个数塞到这 $ y $ 个数前面的 $ y $ 个数中间，形成一段 $ 2y $ 个数，所以对应数的移动距离也是每次变为两倍  

那么问题就解决了，对于询问的位置，如果是奇数位，直接输出，否则每次向后跳跃，直到跳跃长度为奇数为止  

由于跳跃距离每次除以 $ 2 $，所以单次询问最劣复杂度为 $ O(\log n) $  

总复杂度 $ O(q\log n) $，可以通过  

---

### 代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//1e18开long long
ll n, x;
int q;
int main() {
	ll T1, T2;
	scanf("%lld%d", &n, &q);
	while (q--) {
		scanf("%lld", &x);
		if (x % 2 == 1) {
			printf("%lld\n", (x + 1) / 2);//奇数位是没有移动的
			continue;
		}
		T1 = x;
		T2 = n + x / 2 - x;//第一次跳跃距离可以直接求出
		while (T2 % 2 == 0) {//跳到跳跃距离为奇数
			T1 += T2;
			T2 /= 2;//每次跳跃距离除以2
		}
		T1 += T2;//别忘了跳最后一次
		printf("%lld\n", (T1 + 1) / 2);//跳到对应位置后即可求出答案
	}
	return 0;
}
```


---

## 作者：Drind (赞：0)

duel 做到了，发现好难，不会做！

首先我们发现整个过程都没有什么规律非常的烦人，但是我们可以模拟一下这个过程，发现每次填第 $i$ 个空格的时候，这后面正好是一连串的连续数字，而且数字个数就是 $n-i$。

而且我们还知道一个当下有数字的位置，今后再也不会被别的数字占领。

所以考虑倒着做，因为我们知道这个空格是从哪个位置的数字跳过来的（因为我们知道后面有多少连续数字，肯定是连续数字最后一个跳过来了），所以可以往后跳，直接模拟这个过程即可。因为每次距离结尾的距离减半，所以单次查询复杂度是对数 $O(\log n)$ 的。

注意如果跳到某个奇数位置（即初始时有值的位置）时，直接结束，输出答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool Mbe;
const int N=2e5+10;
inline int _abs(int x){if(x>0) return x;return -x;}

void fake_main(){
	int n,q; cin>>n>>q;
	for(int i=1;i<=q;i++){
		int tmp; cin>>tmp;
		while(1){
			if(tmp%2==1){//奇数位置！直接输出答案
				cout<<(tmp+1)/2<<"\n";
				break;
			}
			
			int back=n-tmp/2;//算一下后面有多少数字
			tmp+=back;//往后跳
		}
	}
}

bool Med;
signed main(){
	ios::sync_with_stdio(false);
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	int t; t=1;
	while(t--) fake_main();
	cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
}

```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有一个数组，从 $1$ 至 $n$，但中间有空，每一次操作把最后一个数字放到最后一个空上，直到整个数组都没空了。有 $q$ 次询问，问这个数组上第 $x$ 个数是多少。
## 大体思路
我们手玩几个数据找规律（这个要自己玩），比如说 $7$，$8$，$9$ 等，我们就会发现是成等比数列排列的。

比如 $9$ 这个数的情况：
```cpp
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 89 //这里9走了1格
1 2 3 4 5 6 798 //这里9走了2格
1 2 3 4 5 6879 //这里8走了3格
1 2 3 4 59687 //这里9走了4格
1 2 3 475968 //这里7走了5格  
1 2 3847596 //这里8走了6格
1 26384759 //这里6走了7格 
192638475 //这里9走了8格
```
我们发现，$9$ 的路径是 $1,2,4,8$；

$8$ 的路径是 $3,6$。

我们枚个大的就会发现很像等比数列形式，为什么呢？因为我们每次向前插空一个数之后，都会有 $\lceil (n-x)\div2\rceil$ 个数被越过（现在的 $n$ 是带上空的，也就是 $n\times2-1$）。

但是我们要解决第 $x$ 个数是哪个，那我们从现在这个位置开始做一个反操作，每次加 $\lceil (n-x)\div2\rceil$，直到超过了 $n\times2-1$ 的限制或者是跳跃距离为奇数。

最后我们处理答案时，只需要输出 $\lceil x\div2\rceil$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
	cin>>n>>m;
	n=n*2-1;//数组大小（带空） 
	while(m--){
		long long x;
		cin>>x;
		while(x%2==0&&x<n){
			x+=(n-x+1)/2;
		}
		cout<<(x+1)/2<<endl;
	}
	return 0;
}
```

---

## 作者：Sycamore_Ma (赞：0)

### 题解概述
从查询位**逆向跳跃**，回溯至构造前的起始跳转位，即可推导出起始跳转位所对应的数字值，操作**时间复杂度为 $O(qlog(n))$** .


------------

![](https://espresso.codeforces.com/353e66df2b64f64592e4ec61c819b5ad3856d759.png)

### 读者不难达成以下共识

0. **在构造过程中，序列的前半部分数字将会保持原位不动**；

1. 当有 $n$ 个数字时，初始序列共有 $n-1$ 个空位，因此总共**需要 $n-1$ 次移动操作才能完成最终序列构造**，即填满空位；

2. 在构造过程中，**第 $i$ 次操作的移动距离也为 $i$** ；

3. 在构造过程中，一个独特数字的**首次操作移动距离总是奇数**；

4. 一个独特数字的**下一次移动距离会翻倍**。

_由上述共识可得，无需推演全部构造过程，即可用 $O(logn)$ 的复杂度推出某一个数字的最终位置。_ 


------------

### **利用上述共识可逆向迭代回溯出查询位所对应的起始数字值**

首先易得，**_奇数查询位_** 的对应值为 $\lfloor\frac{x}{2}\rfloor + 1$ _（见共识 0）_ .

下面为 **_偶数查询位_** 的推导步骤：

1. 查询位 $x$ 的左侧有 $\lfloor\frac{x}{2}\rfloor - 1$ 个初始填充空位；

2. 由于共有$n-1$次移动操作，查询位$x$**末次移动为第 $(n-1) - (\lfloor\frac{x}{2}\rfloor - 1)$ 次移动**，**移动距离自然也是 $(n-1) - (\lfloor\frac{x}{2}\rfloor - 1)$** _（见共识 2，第 $i$ 次操作的移动距离也为 $i$ ）_ ；

3. 由共识3,4可得，**每次移动距离的上一次移动距离会减半**，直至**移动距离为奇数（首次移动）**，设2中的末次移动距离为 $len$ ，我们可通过迭代 $len /= 2$ 向右回推求解起始位，直至$len$为奇数，设推出查询位 $x$ 的起始位置为 $pos$ ；

4. 构造前起始 $pos$ 位的对应值为 $\lfloor\frac{pos}{2}\rfloor + 1$ .


------------
逆向迭代递推代码如下（附正向构造过程代码）：
```cpp
/*
    Backtracking code for construction
*/

#include <iostream>
using namespace std;

int main()
{
    long long int n, q;
    cin >> n >> q;
    long long mid = (n+1) / 2;
    for (int i = 0; i < q; i ++){
        long long int x;
        cin >> x;
        
        if (x % 2 == 1){
            cout << x / 2 + 1 << endl;
            continue;
        }
        
        // (n - 1) == tot empty cells number, or tot moves
        // (x/2 - 1) == pre empty cells number
        long long int firstStepLength_reverse = (n-1) - (x/2 - 1);
        
        long long int pos = x;
        while (firstStepLength_reverse % 2 != 1){
            pos += firstStepLength_reverse;
            firstStepLength_reverse /= 2;
        }
        
        pos += firstStepLength_reverse;
        
        cout << pos / 2 + 1 << endl;
    }
    return 0;
}

/*
    Construction code
*/

/*
#include <iostream>
using namespace std;

int main()
{
    long long int n, q;
    cin >> n >> q;
    long long int mid = (n+1) / 2;
    for (int i = 0; i < q; i ++){
        long long int x;
        cin >> x;
        
        if (x <= mid){
            cout << x * 2 - 1 << endl;
            continue;
        }
        
        long long int firstStepLength = (n-x+1) * 2 - 1;
        
        long long int pos = x * 2 - 1;
        while (pos > n){
            pos -= firstStepLength;
            firstStepLength *= 2;
        }
        cout << pos << endl;
    }
    return 0;
}
*/
```



---

