# Fun with Integers

## 题目描述

You are given a positive integer $ n $ greater or equal to $ 2 $ . For every pair of integers $ a $ and $ b $ ( $ 2 \le |a|, |b| \le n $ ), you can transform $ a $ into $ b $ if and only if there exists an integer $ x $ such that $ 1 < |x| $ and ( $ a \cdot x = b $ or $ b \cdot x = a $ ), where $ |x| $ denotes the absolute value of $ x $ .

After such a transformation, your score increases by $ |x| $ points and you are not allowed to transform $ a $ into $ b $ nor $ b $ into $ a $ anymore.

Initially, you have a score of $ 0 $ . You can start at any integer and transform it as many times as you like. What is the maximum score you can achieve?

## 说明/提示

In the first example, the transformations are $ 2 \rightarrow 4 \rightarrow (-2) \rightarrow (-4) \rightarrow 2 $ .

In the third example, it is impossible to perform even a single transformation.

## 样例 #1

### 输入

```
4
```

### 输出

```
8```

## 样例 #2

### 输入

```
6
```

### 输出

```
28```

## 样例 #3

### 输入

```
2
```

### 输出

```
0```

# 题解

## 作者：张心博harry (赞：10)

代码真的很短，所有人的代码几乎一模一样......

[题目传送门](https://www.luogu.com.cn/problem/CF1062D)

--------------------

### 大体思路：

一开始我想偏了，以为要用一个二维数组记录两个数是不是转换过，但事实证明这是不可能的。

```
int f[100001][100001]={0}; 
```

然后就想到了——直接计算，不做记录！

做法就是直接枚举 $2-n$ 中所有数的倍数，加上它的倍次，存到 $ans$（答案变量）中。

这里有个很妙的地方，我也是看了题解才知道的，就是在枚举的时候无需枚举负数，最后把 $ans\times4$，就包含了负数和正数的情况了。（真的很妙！）

----------

### 代码：

代码很短的。

```
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	ios::sync_with_stdio(false); //我习惯加个速，但是在比赛中不知道能不能用。（有知道的告诉我好吗 QAQ）
	long long n,ans=0;
	cin>>n;
	for(int i=2;i<=n;i++) for(int j=2*i;j<=n;j=j+i) ans=ans+j/i;//j 每次直接加 i，必定是 i 的倍数。
	cout<<ans*4<<endl; //巧妙极了！
	return 0;
} 
```

------------

最后祝大家在今年的比赛中取得好成绩！

---

## 作者：AubRain (赞：3)

~~乱搞~~ 贪心就行了。

对于 $>=2$ 的每个数，都找倍数变换一下，然后就像样例那样，变成倍数，再变成负数，再变回来，总共可以变四次，统计答案即可。

没有任何优化的 $O(nlogn)$ 调和级数算法。

代码严格十行，**短得可怜**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
signed main(){
	cin>>n;
	for(int i=2;i<=n;i++)
		for(int j=i+i;j<=n;j+=i)
			ans+=j/i;
	cout<<ans*4;
}
```
当然，可以算出每个数有几个倍数，然后加上就行了，这样是 $O(n)$ 的。

又当然，可以除法分块，这样就可以进一步优化到 $O(n^{1/2})$ 。

**可以优化，但没有必要。**

---

## 作者：ryf_loser (赞：1)

此题思路不易，但代码极易。

简单来说其实就是一个贪心。

根据题意，我们枚举每个 $\geq2$ 的数，计算出 $i\times2\sim n$ 是 $i$ 倍数的数相对于 $i$ 的多少倍存放到答案中即可，最后我们根据样例易知最后把答案 $\times4$ 即可把正负数所有的情况都得到了。

楼上几位都是用枚举 $O(n\log n)$ 的时间复杂度，个人比较喜欢优化
（~~抢最优解~~）。故直接使用了高斯求和公式计算。

不过，因为高斯求和公式是需要在最后 $\times \frac{1}{2}$ 的，答案在最后要 $\times4$ 的，经化简，仅需让答案在最后 $\times2$ 即可。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline long long in(){//快读板子。
	long long x=0,f=1;char c;
	c=getchar();
	while (c<'0'||c>'9'){
		if (c=='-')f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
long long n,ans;
int main(){
	n=in();
	for (int i=2;i<=n;i++)ans+=((n/i+2)*(n/i-1));//核心代码。
	printf ("%lld",ans<<1);//位运算优化。
	return 0;
}

```


---

## 作者：Yyxxxxx (赞：1)

首先看看样例$2\to4\to(-2)\to(-4)\to2$  
我们发现，这一轮下来，变换得到的贡献一共是$\dfrac{4}{2}\times4=8$  
那么直接枚举$n$以内的每个数，$n$ 以内的倍数。加贡献（即几倍）。  
最后乘$4$。结束。
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans=0;
int main()
{
	cin>>n;
	for(int i=2;i<=n;i++)
		for(int j=i+i;j<=n;j+=i)
			ans+=j/i;
	cout<<ans*4;
	return 0;
}
```


---

## 作者：jjy2023 (赞：0)

# CF1062D Fun with Integers
## 枚举法。
#### 思路：
- 因为 $n\ge2$，所以从 $2$ 开始枚举 $a$；

- 接着枚举 $x$，只要保证 $a×x≤n$ 即可，并将 $x$ 累加到分数中。（无需枚举 $b$，因为题目中所说不允许将再将 $a$ 转换为 $b$ 或 $b$ 再转换为 $a$）

- 最后输出分数即可。因为我们只讨论了一种情况，即 $a,x$ ****都为正数****的情况。但累加分数需要每局正正、正负、负正、负负四种情况，于是要将结果乘 $4$ 再输出。
## 注意：一定要开 longlong!!!
### code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=0;
signed main()
{
	ios::sync_with_stdio(false);//加速读入，可不加
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++)
		for(int j=i+i;j<=n;j+=i) ans+=j/i;//枚举并累加分数
	cout<<4*ans;//输出结果
	return 0;
}
```

---

## 作者：weicongjun (赞：0)

# 洛谷CF1062D题解
### 解题思路：

1. 定义一个变量 $ans$，用于记录最高得分，初始值为 $0$。
2. 对于每个整数 $a$，从 $2$ 循环遍历到 $n$。
- 从 $a$ 开始，以步长 $a$ 循环遍历到 $n$，记当前的数为 $b$。
- 将 $ans$ 增加 $|b$ $\div$ $a|$，表示将 $b$ 转换为 $a$ 的转换次数（取绝对值）。
3. 最后，将 $ans$ 乘以 $4$，得到最高得分。

# 接下来奉上代码：
```cpp
接下来奉上代码：
#include <iostream>
#include <cmath> 
using namespace std;
int main() {
    long long n;
    cin >> n;
    long long ans = 0;
    for (int a = 2; a <= n / 2; a++)
        for (int b = a + a; b <= n; b += a)
            ans += abs(b / a);
    cout << ans * 4 << endl;
    return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

其实思路挺好想的。

题目让我们取两个数 $a$ 和 $b$，使 $2≤|a|,|b|≤n$，这两个数满足 $a\div b=x$ 或者 $b\div a=x$，这时你可以将你的分数加上 $|x|$，但是加完分数之后就不能再用这一对数加分了（也就是不能刷分），问你可以加的最多分数。

首先，题目是说 $a$ 和 $b$ 这一对数在一起不能用了，但是没有说这个数用完之后就不能用了！也就是说这两个数还可以和其他的数组合使用。

所以，可以枚举 $a$，使得 $2≤a≤n$，然后再枚举 $x$，只要保证 $a×x≤n$ 就可以把 $|x|$ 加到答案里面。（不用枚举 $b$，因为 $a×x=b$ 和 $b×x=a$ 两个都只能加一次）

另外，上面的这种做法只考虑了 $a$ 和 $b$ 都是正数的情况。因为题目的 $a$，$b$，$x$ 都有加绝对值，使得答案有了四种可能，即 $|a\div b|$，$|(-a)\div b|$，$|a\div (-b)|$，$|(-a)\div (-b)|$，而这里所有的四种情况答案都是 $|x|$，又因为 $|a\div b|=|x|$，所以只要把枚举完正数情况的答案全部乘以 $4$ 就可以了！

CODE：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans; 
int main(){
	scanf("%lld",&n);
	for(ll i=2;i<=n;i++)//枚举 a
	for(ll j=2;i*j<=n;j++)//枚举 x
	ans+=j;
	printf("%lld",ans*4);//四种情况
	return 0;
} 
```

因为写这篇题解的时候 RMG 坏了，所以我是去 CF 本地测完 AC 的。

---

