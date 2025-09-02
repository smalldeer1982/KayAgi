# Heidi Learns Hashing (Easy)

## 题目描述

Melody Pond was stolen from her parents as a newborn baby by Madame Kovarian, to become a weapon of the Silence in their crusade against the Doctor. Madame Kovarian changed Melody's name to River Song, giving her a new identity that allowed her to kill the Eleventh Doctor.

Heidi figured out that Madame Kovarian uses a very complicated hashing function in order to change the names of the babies she steals. In order to prevent this from happening to future Doctors, Heidi decided to prepare herself by learning some basic hashing techniques.

The first hashing function she designed is as follows.

Given two positive integers $ (x, y) $ she defines $ H(x,y):=x^2+2xy+x+1 $ .

Now, Heidi wonders if the function is reversible. That is, given a positive integer $ r $ , can you find a pair $ (x, y) $ (of positive integers) such that $ H(x, y) = r $ ?

If multiple such pairs exist, output the one with smallest possible $ x $ . If there is no such pair, output "NO".

## 样例 #1

### 输入

```
19
```

### 输出

```
1 8
```

## 样例 #2

### 输入

```
16
```

### 输出

```
NO
```

# 题解

## 作者：shuzihan666 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1184A1)
- 考虑让 $x$ 最小，先让 $x$ 为 $1$，用方程 $x^2+2xy+x+1$ 算出 $2y+3=n$。
****
- 两种无解情况：
1. $n<5$。

   2. $n$ 被二整除。
****
## **AC 代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
void pd(long long n)
{
		if(n%2==0||n<5) cout<<"NO";
		else cout<<1<<" "<<(n-3)/2;
}
int main()
{
		long long n;
		cin>>n;
		pd(n);
		return 0;
} 
```

---

## 作者：xuchuhan (赞：2)

## 题意

题意简述中，没有说清楚 $x,y$ 均为正整数，同时无解应输出 `NO`，而不是 `No`。

题目简单来说，就是让你求 $x^2+2xy+x+1=r$ 的正整数解，使得 $x$ 最小，若无解，输出 $-1$。

## 暴力解法

由于 $x,y,r$ 都是正整数，所以 $x^2$ 一定小于 $r$。那么只需要从 $1$ 到 $\sqrt{r}$ 枚举 $x$ 的值，只要遇到一个满足的解直接输出并且 `return 0` 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r;
signed main(){
	cin>>r;
	for(int x=1;x<=sqrt(r);x++){//1到sqrt(r)枚举x
		int t=r-x*x-x-1;
		if(t<=0||t%(2*x)!=0)
			continue;
		//两种y不合法的情况：
		//1. y不为正数，需要注意0不是整数，所以设置的是t<=0的条件。
		//2. y不是正数。设置t%(2*x)!=0的条件
		int y=t/2/x;
		cout<<x<<" "<<y;
		return 0;
		//剩下情况即为合法，直接输出并结束。
	}
	cout<<"NO";
	//无解输出NO。
	return 0;
}
```

## 数学解法

首先判断无解。

第一种无解就是 $r$ 为偶数时。当 $x$ 为奇数时，$x^2$ 为奇数，$2xy$ 为偶数，$x$ 为奇数，$1$为奇数，那么 $x^2+2xy+x+1$ 为奇数；当 $x$ 为偶数时，$x^2$ 为偶数，$2xy$ 为偶数，$x$ 为偶数，$1$为奇数，那么 $x^2+2xy+x+1$ 同样为奇数。无论如何，$x^2+2xy+x+1$，也就是 $r$，都不可能为偶数，所以当 $r$ 为偶数时，直接输出 `NO`。

第二种无解就是当 $r < 5$ 时。当 $x,y$ 都取最小值 $1$ 时，$x^2+2xy+x+1$ 为 $5$，说明 $x^2+2xy+x+1$，也就是 $r$，的最小值为 $5$，所以当 $r < 5$ 时，无解，输出 `NO`。

剩下的情况，当 $x$ 取最小值 $1$ 时，$y$ 的值为 $(r-3) \div 2$，因为 $r \geq 5$，所以 $r-3>0$，那么 $(r-3) \div 2>0$。同时因为 $r$ 是奇数，那么 $r-3$ 是偶数，那么 $(r-3) \div 2$ 为整数。结合以上两个条件，得出在剩下的情况中，当 $x$ 取最小值 $1$ 时，$y$ 有正整数解。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r;
signed main(){
	cin>>r;
	if(r<5||r%2==0)//无解
	    cout<<"NO";
	else
	    cout<<1<<" "<<(r-3)/2;//1:x的最小值，(r-3)/2:x取1时y的取值
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：2)

> 给定二元二次方程 $x^2 + 2xy + x + 1 = r$，其中 $x, y, r$ 为正整数，若有解，输出 $x$ 最小时 $x,y$ 的值，否则输出 `NO`。
>
> $1\le r\le 10^{12}$。

因为要让 $x$ 取最小，所以考虑令 $x = 1$，代入 $x^2 + 2xy + x + 1 = r$，即为 $2y + 3 = r$。

然后移项，$y = \dfrac{r - 3}{2}$，注意到 $y \ge 1$，所以 $\dfrac{r - 3}{2} \ge 1$，即 $r-3 \ge 2$，所以 $r\ge 5$，所以当 $r < 5$ 时无解。

又因为 $y$ 是正整数，所以 $\dfrac{r - 3}{2}$ 是正整数，所以 $r - 3$ 是 $2$ 的倍数，所以 $r$ 不是 $2$ 的倍数。

所以当 $r < 5$ 或 $r \bmod 2 = 0$ 时无解，其他情况有解，$x = 1, y = \dfrac{r - 3}{2}$。

```python
r = int(input())
if r % 2 == 0: 
  print('NO')
elif r < 5:
  print('NO')
else:
  print(1, end = ' ')
  print((r - 3) // 2)
```

---

## 作者：Mercury_C (赞：2)

0 .更正题面（如果无解输出 $NO$ 而不是 $No$），并且原题中 $x$ 和 $y$ 要求为正整数即 $x$ 大于 $0$ 且 $y$ 大于 $0$.

1.题目解析

>本题为数学问题,大意就是给定一个二次方程的函数值，让我们输出**最小**的 $x$ 以及对应的 $y$ 的数值。

最小的正整数 $x$ 我们自然就想到了 $1$ 这个数字，而将 $1$ 带入后我们便可得到如下推导
>我们假设函数值为 $r$ ，
而 $x$ 的值为 $1$ ，那么将 $x$ 带入题目中的函数表达式就可以得到如下代码:
```cpp
y = （ r - 3 ） / 2；
```
>而此代码中的限制条件为

>1.$r-3$ 的值必须大于0.

>2.$r-3$ 的值必须为偶数。

就能写出如下代码

```
if(r%2==0||r<=3)
            cout<<"NO"<<endl;
        else
        cout<<1<<" "<<(r-3)/2<<endl;
```

2.一些疑惑

在本题处理时，或许会有这样的疑惑，为什么 $x$ 不能为 $2$，$3$，$4$ 等任意值？
就是存在这样的情况如： $x$ 为 $1$ 答案不存在，而 $x$ 为 $2$ 或 其他的数使得答案存在？

>答案是不存在。

原因如下


我们注意到题目中有 $x$ 的平方加 $x$ 加 $1$ 这个代数式，我们可以发现，无论 $x$ 取多少数值， 该代数式**一直**为奇数！

原因是 $x$ 乘以 $（x+1)$ 的值一定是偶数，而再加 $1$ 就是奇数，本题目只用判断奇偶性即可，所以如果 $x$ 为 $1$ 的值不存在，那么无论 $x$ 取多少都是没有用的！

附上代码，仅供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long r;
int main()
{
    while(cin>>r)
    {
        if(r%2==0||r<=3)
            cout<<"NO"<<endl;
        else
        cout<<1<<" "<<(r-3)/2<<endl;

    }
    return 0;
}

```

---

## 作者：InversionShadow (赞：1)

## CF1184A1 Heidi Learns Hashing (Easy) 题解

观察翻译说“输出 $x$ 在最小值下 $x$ 和 $y$ 分别的值”，而又因为题目要求的 $x,y$ 均为正整数，所以我们要让 $x$ 尽量小，所以我们钦定 $x=1$，那么 $H(1,y)=x^2+2xy+x+1=1+2y+1+1=2y+3$，所以 $2y+3=r$，所以有解且 $x$ 最小的情况就是 $x=1,y=\dfrac{r-3}{2}((r-3) \bmod2=0)$，否则如果 $(r-3)\bmod2=1$ 的情况就是 `NO` 啦！

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int x;

signed main() {
  cin >> x;
  if ((x - 3) % 2 == 0 && x >= 4) {
    cout << "1 " << (x - 3) / 2 << endl;
    return 0;
  }
  cout << "NO\n";
  return 0;
}
```

---

## 作者：zsh_haha (赞：1)

### 思路讲解

由于要求 $x$ 最小，所以只用考虑 $x$，而 $y$ 可以被求出来。

首先考虑 $x=0$ 的情况，带入方程：$r=0^2+2\times0\times y+0+1$。

这时 $r=1$，所以 $r=1$ 时，$(x,y)=(0,n)$ 了，吗？

并不是，因为在这里 $y$ 是不固定的，所以也算无解。

然后考虑 $x=1$，带入方程 $r=1^2+2\times1\times y+1+1$，这时 $y$ 就是固定的了，所以只用考虑 $x=1$。

然后再来看无解情况，因为 $r=1^2+2\times1\times y+1+1$，所以 $r-1^2-1-1=2\times1\times y$，这时的 $2\times1\times y$ 必须为偶数，且必须大于等于 $2$，最终就是 $r$ 必须为奇数，且 $r-1^2-1-1\ge2$。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long q;
	cin>>q;
	if(q%2==1&&(q-1*1-1-1)>=2){//化简为 q%2&&q>=5 
		cout<<"1 "<<(q-1*1-1-1)/1/2;//化简为 cout<<"1 "<<(q-3)/2; 
	}else{
		cout<<"NO";
	}
	return 0;
}
```

---

## 作者：二叉苹果树 (赞：1)

似乎另外两篇题解符合难度的却忽略了暴力的做法。

对于方程 $x ^ 2 + 2xy + x + 1 = r$，可以得到 $x \left( x + 2y + 1\right) = r - 1$，这样我们只需要考虑是否有符合题意的 $x$ 和 $x + 2y + 1$ 即可。

由于 $x$ 一定是 $r - 1$ 的约数，所以枚举 $\sqrt r$ 内的正整数 $x$，再判断 $y = \dfrac{\frac{\left( r - 1\right)}{x} - x - 1}{2}$ 是否是正整数即可。

```cpp
#include <bits/stdc++.h>

int main()
{
    long long r;
    std::cin >> r;
    for (int i = 1; i <= 1000000; i++)
        if ((r - 1) % i ==0)
        {
            long long y = (r - 1) / i - i - 1;
            if (y % 2 == 0 && y > 0)
            {
                std::cout << i << " " << y / 2 << std::endl;
                return 0;
            }
        }
    std::cout << "NO" << std::endl;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现如果要是 $x$ 最小，使它为 $1$ 就行。接下来化简方程，不难得出 $2 \times y+3$，而 $y$ 最小为 $1$，所以当 $r<5$ 时无解。当 $r \geq 5$ 时，$y$ 即为 $\frac{r-3}{2}$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int r;
int main(){
	cin>>r; 
	if(r%2==0||r<5){
		cout<<"NO";
	}
	else{
		cout<<1<<" "<<(r-3)/2;
	}
	return 0;
}
```


---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1184A1)

# 思路

我们想让$\ x\ $最小，又$\ x\ $为正整数，所以不妨令$\ x=1$。

所以一个未知数消掉了，代入原方程得$\ 2y+3=r$，因为$\ y\ $也是正整数，所以当$\ r<5\ $时，原方程无解。

而且，还有一个无解情况：因为$\ 2\ $一定不整除$\ 2y+3$，所以当$\ 2\ $整除$\ r\ $时，原方程无解。

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long r;
    cin>>r;
    if(r%2==0||r<5)cout<<"NO";
    else cout<<"1 "<<(r-3)/2<<endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/110434366)

---

