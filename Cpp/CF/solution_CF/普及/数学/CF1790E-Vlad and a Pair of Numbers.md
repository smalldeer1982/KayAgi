# Vlad and a Pair of Numbers

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a,b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 样例 #1

### 输入

```
6
2
5
10
6
18
36```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22```

# 题解

## 作者：灵茶山艾府 (赞：28)

对于二进制加法，$a+b$ 可以拆分 $a\operatorname{xor} b$ 和两个 $a\operatorname{and} b$，即

$$
a+b = (a\operatorname{xor} b) + 2\cdot (a\operatorname{and} b)
$$

结合题目给的公式

$$
a+b = 2\cdot (a\operatorname{xor} b)
$$

得

$$
a\operatorname{and} b = \dfrac{a\operatorname{xor} b}{2}
$$

如果 $a\operatorname{xor} b$ 是奇数，或者 $(a\operatorname{xor} b) \operatorname{and}\  (a\operatorname{and} b) \ne 0$，那么无解。后者是因为 $a\operatorname{xor} b$ 中的 $1$ 说明在这个比特位上必定一个是 $0$ 另一个是 $1$，$\operatorname{and}$ 结果必定是 $0$，所以 $a\operatorname{xor} b$ 和 $a\operatorname{and} b$ 在同一个比特位上不可能都是 $1$，所以 $(a\operatorname{xor} b) \operatorname{and}\  (a\operatorname{and} b) = 0$ 恒成立。从集合的角度上来说就是 $a\operatorname{xor} b$ 和 $a\operatorname{and} b$ **不相交**。

现在 $a\operatorname{and} b$ 和 $a\operatorname{xor} b$ 都知道了，可以构造出一组解了。

由于 $a\operatorname{and} b$ 中的 $1$ 在 $a$ 和 $b$ 中都有，而 $a\operatorname{xor} b$ 中的 $1$ 要么在 $a$ 中，要么在 $b$ 中，不妨全部给 $a$，得

$$
\begin{cases}
a = (a\operatorname{xor} b) \operatorname{or}\ (a\operatorname{and} b) = (a\operatorname{xor} b) + (a\operatorname{and} b) = \dfrac{3(a\operatorname{xor} b)}{2}\\
b = a\operatorname{and} b = \dfrac{a\operatorname{xor} b}{2}
\end{cases}
$$

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var T, xor int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &xor)
		and := xor >> 1
		if xor&1 > 0 || xor&and > 0 {
			Println(-1)
		} else {
			Println(xor|and, and)
		}
	}
}
```

时间复杂度：$\mathcal{O}(1)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)


---

## 作者：幻想繁星 (赞：18)

# 题意
给定 $x$，求 $a$ 和 $b$，使 $a \oplus b=\frac{a+b}{2}=x$。若有多个解输出任意一个即可。若无解输出 $-1$。
# 思路
我们可以先尝试打表，通过打表找到一些规律。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read();
int main()
{
	for(int x=1;x<=1000;x++)
		for(int i=1;i<=x*2;i++)
			if((i^(x*2-i))==x)
			{
				cout<<x<<" "<<i<<" "<<(x*2-i)<<"\n";
				break;
			}
	return 0;
}
```
通过以上代码我们可以得到 $1000$ 以内所有 $x$ 的最小解。

结果如下：

[传送](https://www.luogu.com.cn/paste/d28t4n4i)   

通过观察可发现若 $x$ 有解则 $a$ 最小为 $\frac{x}{2}$，此时 $b=2x-a$ 即 $b=\frac{3x}{2}$。

所以只要判断 $\frac{x}{2}\oplus\frac{3x}{2}$ 是否等于 $x$ 并输出即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read();
int main()
{
	int t=read();
	while(t--)
	{
		int x=read(),a=x/2,b=x*2-a;
		if((a^b)==x)
			cout<<a<<" "<<b<<"\n";
		else
			cout<<"-1\n";
	}
	return 0;
}
```
# 证明——[2018ljw ](https://www.luogu.com.cn/user/128606)
令 $a=0$，$b=x$，对于二进制 $x$ 的任意为 $0$ 的位置 $p$，将 $a$，$b$ 加上 $2^p$，异或不变，总和加上 $2^{p+1}$。

最终目标要使总和加上 $x$，可知 $a$，$b$ 分别要加上 $\frac{x}{2}$。那么如果 $x$ 与 $\frac{x}{2}$ 某个位置均为 $1$ 就无解，否则构造出的 $a$ 即为最小。

---

## 作者：Night_sea_64 (赞：6)

很好玩的一道题。

先解释一下**按位异或**（$\operatorname{xor}$）。引用百度百科的几句话（以下所有 $a,b$ 都是二进制下的一位数）：

>如果 $a,b$ 两个值不相同，则异或结果为 $1$。如果 $a,b$ 两个值相同，异或结果为 $0$。  
> 异或也叫**半加运算**，其运算法则相当于**不带进位的二进制加法**。

也就是说，$a\operatorname{xor}b=(a+b)\bmod2$。而 $a+b$ 的最低位也是这么算的。可以看出在没产生进位的情况下，$a+b$ 应该等于 $a\operatorname{xor}b$。所以如果 $x$ 的某一位和 $2x$ 的相同位**不同**，我们能看出**这一位更低的一位加法会产生进位，否则不会。** 原因是：我们可以想到，这个不同一定是更低一位的进位贡献来的（因为异或没有进位，加法可能有，所以可能会出现进位的不同）。当然，如果这不同的一位是最低位，那是无解的！由于 $2x$ 一定是偶数，所以如果最低位不同，$x$ **一定是奇数**。则我们看到 $x$ 为奇数时就可以直接回答无解了。

但是 $x=6$ 为什么也无解呢？$6=(110)_2,6\times2=12=(1100)_2$。最低位是 $0,0$，符合要求。但是倒数第二位不同，说明要进位。但是到了倒数第二位，我们发现没法满足它**和的最低位为 $0$，但异或是 $1$，倒数第三位又不能进位**的~~麻烦的~~要求。这里就不细说了。

放个代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int x;
        cin>>x;
        if(x%2)
        {
            cout<<-1<<endl;
            continue;
        }
        int y=2*x,cur=0,a=0,b=0;
        bool flag=1;
        while(y)
        {
            if(x%2==0)
            {
                if(x/2%2!=y/2%2)
                    a=a+(1<<cur),b=b+(1<<cur);
            }
            else
            {
                if(y%2==0)
                {
                    if(x/2%2==y/2%2)
                    {
                        flag=0;
                        break;
                    }
                }
                else if(x/2%2!=y/2%2)
                {
                    flag=0;
                    break;
                }
                a=a+(1<<cur);
            }
            x/=2,y/=2;
            cur++;
        }
        if(!flag)cout<<-1<<endl;
        else cout<<a<<" "<<b<<endl;
    }
    return 0;
}
```

这篇题解应该会有一些人看不懂吧，本蒟蒻的语文太差了，虽然很仔细地改了好几回，但还是没法说得很清楚，很难把此题的好玩之处写出来。不懂的私信我吧。

---

## 作者：wdgm4 (赞：4)

### 思路

像这种有多组数据，求是否有解且只需输出任一答案的题，都可以尝试用打表找出规律。

[打表代码](https://www.luogu.com.cn/paste/ss3b4jcz)

打表之后发现，如果一个数 $x$ 有解，那么其中一定有一个 $a$（或 $b$）等于 $\frac{x}{2}$。

所以说只需判断 $\frac{x}{2} \oplus \frac{3x}{2}$ 是否等于 $x$ 即可。

但是如何证明呢？

首先要知道一个异或的特性，当 $a \oplus b$ 时，如果 $a$ 与 $b$ 的二进制中有任一位上均为 $0$，那么把这一位上的 $0$ 变为 $1$ 后 $a \oplus b$ 的值不变。也就是说对于二进制 $a$ 与 $b$ 中任意均为 $0$ 的位置 $p$，让 $a$ 和 $b$ 同时加上 $2^p$，$a \oplus b$ 的值不变。

令 $a$ 等于 $0$，$b$ 等于 $x$，让 $a$ 与 $b$ 同时加上 $\frac{x}{2}$，如果 $x$ 与 $\frac{x}{2}$ 同一位上都为 $1$，那么就无解，否则有解。

$\frac{x}{2}$ 相当于二进制 $x$ 向右移一位，假如 $x=18$，如下图。

```
x    =  10010  =18
x/2  =   1001  =9
```

那么还用 $x=18$ 举例。首先 $a$ 等于 $0$，$b$ 等于 $x$ 时，$a \oplus b=x$。让 $x$ 加上 $\frac{x}{2}$ 后只是让 `10010` 中几个为 `0` 的位变为 `1`，那么它与 $\frac{x}{2}$ 异或的值是不变的（还等于 $x$）。

再用 $x=12$ 举例。

```
x    =  1100  =12
x/2  =   110  =6
```

让 $x$ 加上 $\frac{x}{2}$ 后的二进制变为 `10010`，异或后的值发生了改变，所以无解。

因此我们还可以发现当 $x$ 为偶数，且 $x$ 没有相邻两位都为 `1` 的一定有解，反之无解。

#### 代码

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define yee 1919810

using namespace std;
int t,x;
int main() {
	cin>>t;
	while(t--){
		cin>>x;
		int a=x/2;
		int b=x*2-a;
		if((a^b)==x) cout<<max(a,b)<<" "<<min(a,b)<<endl;
		else cout<<"-1"<<endl;
	}
	return 0;
}

```

时间复杂度 $O(t)$。

---

## 作者：ZHANGyutao123 (赞：3)

# CF1790E 题解
## [传送门](https://www.luogu.com.cn/problem/CF1790E)
## 题目大意
给定 $t$ 个正整数 $x$，构造一组正整数 $a$ 和 $b$，使得 $a + b = x \times 2$ 且 $a \operatorname{xor} b = x$。若有多组解，输出任意一组解；若无解，输出 $-1$。

需要注意的是，这里 $a$ 和 $b$ 都需要是正整数，并且并没有要求 $a \neq b$，也就是说 $a$ 和 $b$ 可以相等。

## 解题思路

我们对 $a \oplus b = x$ 进行转换，得到：

$$\begin{aligned} a \oplus b = x & \Leftrightarrow a = x \oplus b \\ & \Leftrightarrow a = (x \oplus (2x - a)) \\ & \Leftrightarrow a = 3x / 2 \oplus a \end{aligned}$$

两边同时异或上 $a$，则得到：

$$\begin{aligned} a \oplus a \oplus a &= a \oplus (3x / 2) \\ 0 \oplus a \oplus a &= 3x/2 \\ a &= 3x/2 \end{aligned}$$

所以只用判断 $\frac{3}{2}x$ $\oplus$ $\frac{1}{2}x$ 是否等于 $x$ 就行了。

## 代码如下：
```
#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t; // 读入测试数据组数
    while (t--) { // 处理每一组测试数据
        int x;
        cin >> x; // 读入正整数 x
        long long a = x / 2, b = x + (x - a); // 根据题目意思求出满足条件的 a 和 b
        if ((a ^ b) == x) // 如果异或结果与 x 相等，则说明 a 和 b 满足条件
            cout << a << ' ' << b << '\n'; // 输出 a 和 b
        else
            cout << "-1\n"; // 否则输出 -1
    }
    return 0;
}

```




---

## 作者：Allanljx (赞：2)

## 思路
按二进制的每一位考虑。当 $x$ 的第 $i$ 位为 $1$ 时，则不管怎么填对平均数的贡献都是一样的，因此给 $a,b$ 都可以，此时对平均数的贡献是 $2^{i-1}$；当 $x$ 的第 $i$ 位为 $0$ 时，对平均数的贡献要么是 $2^i$ 要么是 $0$，所以考虑剩余还需的贡献（$x$ 减去上面这些 $2^{i-1}$ 后的贡献）二进制下的每一位。当第 $i$ 位为 $1$ 时，就需要这一位都填 $1$，否则就要都填 $0$，判断一下能不能填就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,x;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		int a=0,b=0;
		cin>>x;
		int y=x;//剩余贡献
		if(x%2)//防止i/2是小数
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=x;i*=2)
		{
			if(x&i) a+=i,y-=i/2;
		}
		int fl=0;
		for(int i=1;i<=y;i*=2)
		{
			if(y&i)//这一位是1
			{
				if(x&i) fl=1;//这一位不能都填1，要有一个0
				a+=i,b+=i;
			}
		}
		if(fl)
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<a<<' '<<b<<endl;
	}
}
```

---

## 作者：uid_310801 (赞：2)

### 题意：

给定一个数 $x$，找到两个数 $a,b$ 使得 $a⊕b=\frac{a+b}2=x$，或判断无解。

### 题解：

转换一下式子，$a+b=2\times x$.

将 $x$ 二进制拆分，按位处理，根据这一位需要的和(即为下一位的值)，这一位的异或，和上一位的进位需求，即可构造出一组解。

- 如果上一位需要进位，这一位异或值为 $1$，且和为 $1$，则判断无解。

- 如果到了最后一位仍有进位需求，则无解。

- 其他情况可以根据手模列举各种情况找到一组合适的解。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=29+10;
ll T,n,a[N],x[N],y[N],tmp;
void work(){
	scanf("%lld",&tmp);
	ll cnt=0,pls=1;//pls代表上一位是否有进位的需求。由于初始时最高位和是1异或是0，所以需要下一位的进位，且a,b这一位都是0
	memset(a,0,sizeof(a));
	while(tmp){
		a[++cnt]=tmp%2;
		tmp/=2;
	}
	for(int i=cnt;i>=1;i--){
		if(a[i-1]==0){
			if(a[i]==1){
				if(pls==1){
					x[i]=0,y[i]=1;
					pls=1;
				}
				else{
					x[i]=0,y[i]=1;
					pls=0;
				}
			}
			else{
				if(pls==1){
					x[i]=1,y[i]=1;
					pls=0;
				}
				else{
					x[i]=0,y[i]=0;
					pls=0;
				}
			}
		}
		else{
			if(a[i]==1){
				if(pls==1){
					puts("-1");
					return;
				}
				else{
					x[i]=0,y[i]=1;
					pls=0;
				}
			}
			else{
				if(pls==1){
					x[i]=1,y[i]=1;
					pls=1;
				}
				else{
					x[i]=0,y[i]=0;
					pls=1;
				}
			}
		}
	}
	if(pls==1){
		puts("-1");
		return;
	}
	ll ax=0,bx=0;
	for(int i=cnt;i>=1;i--){
		ax=ax*2+x[i];
		bx=bx*2+y[i];
	}
	printf("%lld %lld\n",ax,bx);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		work();
	}
	return 0;
}
/*
exSample:

*/

```



---

## 作者：mc_him (赞：1)

## 题目大意
给定一个数，让你判断是否有两个数的和为给定数的二倍，并且两数异或的结果为给定数。
## 题目分析
这是一道很明显的数学题。数据范围令人堪忧，我们最喜欢的打表是行不通的。那我们就要分析一下。如果大家不容易找到规律，就先[打一下表](https://www.luogu.com.cn/paste/fl7qxy25)。如果你打了，就不难发现，有解的数都是偶数。并且有一个数为给定数的二分之一。以下为分析：
```
a^b=x 	a=x^b
	a=(x^(2x−a))
    	a=3x/2^a
        
a^a^a=a^(3x/2)
0^a^a=3x/2
   a=3x/2
 
```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t;
int main() {
	cin>>t;
	while(t--){
		cin>>n;
		(((n/2)^(n/2*3))==n)?cout<<n/2*3<<' '<<n/2<<endl:cout<<-1<<endl;
	}
	return 0;
}
```

---

## 作者：IkeveLand (赞：0)

## 思路：

- 考虑 $a$ 和 $b$ 的二进制位数是否会大于 $x$ 的二进制位数，让我们先设 $x$ 的位数为 $len$ ，设 $a$ 的二进制数位为 $la$ ，设 $b$ 的二进制数位为 $lb$ 。在这里我们让 $a \ge b$ ，并且 $a+b=x \times 2$ ，接下来进行分类：

- 当 $la>len$ 且 $lb<len$ 时，则 $a \oplus b$  一定大于 $x$ ， $a \oplus b$ 的最高位是 $1$ ，所以大于 $x$ 。
  
- 当 $la>len$ 且 $lb>len$ 时，则 $a \oplus b$ 不一定大于 $x$ ，但又由于 $a>x$ 且 $b>x$ ，因此 $a+b$ 一定会大于 $x \times 2$ 。

**总结：** $a$ 和 $b$ 的二进制数位一定不大于 $x$ 的二进制数位。

**问题：** 如何找到具体的 $a$ 和 $b$ ，让我们试着从最高位往第零位枚举每一位。 

- 若 $x$ 的第 $i$ 位为 $0$ ， 说明 $a$ 和 $b$ 的第 $i$ 位要么都为 $1$ ，要么都为 $0$ ，只能有这两种情况。如果当前 $a$ 的值加上当前 $b$ 的值小于或等于 $x \times 2-2^{i+1}$ ，它们的第 $i$ 位也只能都为 $1$ ，因为如果都为 $0$ 的情况下，即使是两个数更小的位数上的数全部都为 $1$ ，最终的 $a+b$ 也不可能大于或等于 $x \times 2$ 了。可证明出： $
2^m > \sum_{i = 0}^{m-1} {2^i}
$ 。

- 如果当前 $a$ 的值加上当前 $b$ 的值大于 $x \times 2-2^{i+1}$ ，那么第 $i$ 位全部都是 $0$ 。如果 $x$ 的第 $i$ 位为 $1$ ，同理，只是当前的 $a+b$ 要小于或等于的数字变成了 $x \times 2-2^{i+1}$ ，原因是因为只有一个数在第 $i$ 位的数字会是 $1$ 。如果当前的式子成立那么就可以给 $a$ 或 $b$ 中的任意一个数加上 $2^i$ 。最后在判断 $a+b$ 是否等于 $x\times 2$ 。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n;
signed main() {
    cin >> T;
    while (T--) {
        cin >> n;
        if (n % 2 == 1) {
            puts("-1");
            continue;
        }
        int x = n * 2, a = 0, b = 0;
        for (int i = log2(x); i >= 0; i--) {
            if (n & (1 << i))
                a += (1 << i);
            else if (a + b + 2 * (1 << i) <= x)
                a += (1 << i), b += (1 << i);
        }
        if (a + b == x)
            cout << a << " " << b;
        else
            cout << -1;
        puts("");
    }
    return 0;
}
```

---

## 作者：nominater (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1790E)
### 题意
求 $a$ 和 $b$ 满足 $a\oplus b=n$。
### 思路
$n$ 的二进制中不可能有两个连续的一。$\frac{a \times b}{2}$ 可以看作 $a$ 和 $b$ 逐位相加，最终向右移一位。可推出 $a=\frac{x}{2}$，$b=2\times x -a$。
### 代码
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
    register int x = 0, t = 1;
    register char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            t = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * t;
};
int main()
{
    ll t,x;
    cin >> t;
    while (t--)
    {
        x = read();
        ll a = x / 2;
        ll b = 2 * x - a;
        if ((a ^ b) == x)
        {
            cout << a << " " << b << endl;
        }
        else
            cout << "-1" << endl;
    }
    return 0;
}
```


---

