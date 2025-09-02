# Johnny and Another Rating Drop

## 题目描述

The last contest held on Johnny's favorite competitive programming platform has been received rather positively. However, Johnny's rating has dropped again! He thinks that the presented tasks are lovely, but don't show the truth about competitors' skills.

The boy is now looking at the ratings of consecutive participants written in a binary system. He thinks that the more such ratings differ, the more unfair is that such people are next to each other. He defines the difference between two numbers as the number of bit positions, where one number has zero, and another has one (we suppose that numbers are padded with leading zeros to the same length). For example, the difference of $ 5 = 101_2 $ and $ 14 = 1110_2 $ equals to $ 3 $ , since $ 0101 $ and $ 1110 $ differ in $ 3 $ positions. Johnny defines the unfairness of the contest as the sum of such differences counted for neighboring participants.

Johnny has just sent you the rating sequence and wants you to find the unfairness of the competition. You have noticed that you've got a sequence of consecutive integers from $ 0 $ to $ n $ . That's strange, but the boy stubbornly says that everything is right. So help him and find the desired unfairness for received numbers.

## 说明/提示

For $ n = 5 $ we calculate unfairness of the following sequence (numbers from $ 0 $ to $ 5 $ written in binary with extra leading zeroes, so they all have the same length):

- $ 000 $
- $ 001 $
- $ 010 $
- $ 011 $
- $ 100 $
- $ 101 $

The differences are equal to $ 1 $ , $ 2 $ , $ 1 $ , $ 3 $ , $ 1 $ respectively, so unfairness is equal to $ 1 + 2 + 1 + 3 + 1 = 8 $ .

## 样例 #1

### 输入

```
5
5
7
11
1
2000000000000```

### 输出

```
8
11
19
1
3999999999987```

# 题解

## 作者：SpeedStar (赞：7)

### 算法分析
注意到这里的不公平性恰为$n$加上$n$每右移一位的值。

举例：$11$的二进制为$1011$，那么它的不公平性为$1011+101+10+1$，换成十进制就是$11+5+2+1$，得到答案为$19$。


### C++代码
```cpp
#include <iostream>

#define int long long

using namespace std;

signed main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		int res = 0;
		while (n) {
			res += n;
			n /= 2;
		}
		cout << res << '\n';
	}
	
	return 0;
}
```


---

## 作者：LeavingZzz (赞：4)

# Solution For CF1362C
我笨一点，自然就没有发现其他大佬说的结论..  
~~但是我会暴力列~~  
于是我就把二进制位列了出来  

$0000$  
$0001$  
$0010$  
$0011$  
$0100$  
$0101$  
$0110$  
$0111$  
$.......$   

然后我就发现了另外一个东西  
如果把上面的这个数列分开一位一位的看，那么从右往左数第 $i$ 位重复周期为 $2^i$，而且一个周期中前 $2^{i-1}$ 项都是 $0$，后 $2^{i-1}$ 项都是 $1$。  

这有什么用呢？  
你会发现一个周期内会对答案有两次贡献  
周期内部由 $0->1$ 会有一次，同时从一个周期到下一个周期又会有一次。  
那么每一位的贡献就是 $2*(N/2^i)$ （除号为整除）  
但是不一定 $N$ 就刚刚好落在某一个周期结束的位置，可能还会多出来一些。  
那么对于每一位还需要加上 $N\&(2^i)$  

为啥呢？  
因为如果对于第 $i$ 位，$N$ 在第 $i$ 位处为 $0$ 的话，是不会有额外贡献的，只有出现了周期内部的 $0->1$ 才有 $1$ 次贡献，所以加上 $N\&(2^i)$ 直接计算额外贡献。注意当 $N$ 是奇数的时候还要加一次 $1$ ，原因是因为第一位用上述方法计算由于整除的原因需要特别关照（第一位贡献永远是 $N$）。  

直接枚举 $63$ 位计算即可。  
$\large\mathsf{Code:}$  
```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
typedef unsigned long long LL;
LL T,N;
inline LL R()
{
	char c;
	LL re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
inline void print(LL x)
{
	if(x>=10) print(x/10);
	putchar(x%10+48);
	return ;
}
int main()
{
	T=R();
	while(T--)
	{
		N=R();LL p=1,ans=0;
		for(int i=1;i<=63;i++)
		{
			p<<=1;
			ans+=2*(N/p);
			if(N&p) ans++;
		}
		if(N&1) ans++;
		print(ans);puts("");
	}
	return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\text{ }End}$  
谢谢管理大大审核^_^

---

## 作者：LEle0309 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1362C)

一道很好的思维题。

$ n \le {10}^{18} $，暴力会寄，得用数学方法。

#### 题目分析

观察可得：

- $ 000 $
- $ 001 $
- $ 010 $
- $ 011 $
- $ 100 $
- $ 101 $
- $ 110 $
- $ 111 $

对于每一个 $ i $（$ i \ge 1 $），可以得到 $ i $ 与 $ i-1 $ 的差异之和为：

- 当 $ i \bmod 2^0=0 $ 时，$ i $ 的末位与 $ i-1 $ 不同，差异度加 $ 1 $，所以总答案增加 $ \lfloor\dfrac{n}{2^0}\rfloor $。

- 当 $ i \bmod 2^1=0 $ 时，$ i $ 的倒数第 $ 2 $ 位与 $ i-1 $ 不同，差异度加 $ 1 $，所以总答案增加 $ \lfloor\dfrac{n}{2^1}\rfloor $。

- 当 $ i \bmod 2^2=0 $ 时，$ i $ 的倒数第 $ 3 $ 位与 $ i-1 $ 不同，差异度加 $ 1 $，所以总答案增加 $ \lfloor\dfrac{n}{2^2}\rfloor $。

以此类推。

所以有公式：

$$ ans=\sum_{i=0}^{\infty} \lfloor\dfrac{n}{2^i}\rfloor $$

```cpp
#include<iostream>
#include<cmath>
using namespace std;
long long n,t,ans;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;ans=0;//多测清空
		while(n)//加到n>=2^i
		{
			ans+=n;//加上此时的n
			n/=2;//n除以2，实际上就是求出下一个i时n除以2^i的值
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

### [CF1362C 题目传送门。](https://www.luogu.com.cn/problem/CF1362C)

```
input:7

```

$000$

$001$

$010$

$011$

$100$

$101$

$110$

$111$

对于最右面一位，每一个数会和相邻的两个数产生差异（但不包括 $0$ 和 $7$），共 $7$ 组。

对于倒数第二位，每 $2$ 个数就会产生一组差异（去重后），共有 $3$ 组。

对于倒数第三位，每 $4$ 个数会产生一对差异，共 $1$ 组。、

对于倒数第 $k$ 位，每 $2^{k-1}$ 个数会产生一对差异。

$\lfloor \frac{7}{2^0} \rfloor=7$

$\lfloor \frac{7}{2^1} \rfloor=3$

$\lfloor \frac{7}{2^2} \rfloor=1$

$ans=7+3+1=11$

继续验证 $n=11,1,2000000000000$，发现可以沿用上面的方式。

依此，我们推论 $ans=\sum_{i=1}^{\log_2(n)}\ \lfloor \frac{n}{2^i} \rfloor$。

然后写出代码。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long t,b;
	cin>>t;
	while(t--){
		cin>>b;
		long long i=1,ans=0;
		long long q=b;
		
		while(q){
			q/=2;
			ans+=b/i;
			i*=2;
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：__int127 (赞：0)

## CF1362C Johnny and Another Rating Drop 题解

#### [题目传送门](https://www.luogu.com.cn/problem/CF1362C)

### 题目大意

本题有多组数据。

对于每一组数据，给定一个整数 $n$（$1\le n\le10^{18}$），计算 $\sum\limits_{i=0}^{\infty}\left\lfloor\frac{n}{2^i}\right\rfloor$ 的值。

### 思路

由于看不懂大佬们的结论，这里提供一个简单的暴力思路。

这道题大部分人（至少我身边的人是）都是先把 $n$ 转为二进制，再依次相加，最后转为十进制，这算是直接根据题意模拟了，觉得很麻烦直接创建一个 while 循环就可以了，伪代码如下：

```cpp
while (结束条件){
	使 sum + n 右移一位的结果
    使 n 右移一位
}
```

可是问题来了，终止条件是什么呢？

#### 终止条件——思路 $1$

把 $n$ 转为二进制的结果存入另一个变量，过程中计算 $n$ 二进制下的位数，每次相加时使位数减 $1$，直至位数等于 $1$ 时停止相加，输出结果。

可是这还是把 $n$ 转为二进制了，很麻烦，于是又有了思路 $2$。

#### 终止条件——思路 $2$

这里为了更好地理解，我们举个例子（我设 $n=7$）：

$(7)_{10}=(111)_2$，也就是说，式子是这样的（以下式子中的项均为二进制下的数）：

$111+11+1=1011$

注意到最后一个加数为 $(1)_2$，它的十进制也是 $1$，我们再举个例子（$n=10$）：

$(10)_{10}=(1010)_2$，式子为：

$1010+101+10+1=10010$

找到规律了吗，每一次相加，最后一个加数永远为 $(1)_2$，因为其十进制也为 $1$，终止条件就出来了，就是 $n\neq1$ 时，就相加。

这里拓展一下为什么最后一个加数永远为 $1$，因为 $n\geq1$，并且没有前导零（有了也是一样），因此它的首位定为 $1$，所以最后一个加数也为 $1$。

这里有一个易错点，就是数据范围，$1\le n\le10^{18}$，需要开 long long 或 unsigned long long，这里我使用的是 unsigned long long，比较保险。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long a, sum;
int t;
int main(){
	ios::sync_with_stdio(false);// 关闭读写同步，本题数据量较大，建议用 cin 和 cout 的写上这一行和后两行
	cin.tie(0);
	cout.tie(0);
	cin >> t;// t 组数据
	while (t--){
		cin >> a;
		sum = a;// 先让 sum 加上 a（题目里是 n），因为没有重置，直接让他赋值为 a 就可以覆盖原来的数了
		while (a != 1){// 结束条件
			sum += a >> 1;// 每一次 sum 都加上上一次 a 右移一位的结果
			a /= 2;// a 每次右移一位，相当于除以 2
		}
		cout << sum << "\n";// 输出并换行
		// 这里是不需要重置 sum 的，因为 sum 每次都会先加上 a，即使重置了也会被覆盖
	}
	return 0;
}
```

### 拓展——关闭读写同步的好处

[没有关闭的（$\text{77ms}$）](https://www.luogu.com.cn/record/120973985)

[关闭了的（$\text{31ms}$）](https://www.luogu.com.cn/record/120974673)

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：suxxsfe (赞：0)

[在我的博客查看](https://www.cnblogs.com/suxxsfe/p/13052358.html)  

[https://codeforces.com/problemset/problem/1362/C](https://codeforces.com/problemset/problem/1362/C)  

一开始强行找了一波规律，发现并不明显  
然后打了个表，放到oeis上，[发现还真有](http://oeis.org/search?q=1%2C3%2C4%2C7%2C8%2C10%2C11%2C15%2C16%2C18%2C19%2C22%2C23%2C25%2C26%2C31%2C32%2C34%2C35%2C38%2C39%2C41%2C42%2C46%2C47%2C49%2C50%2C53%2C54%2C56%2C57%2C63%2C64%2C66%2C67%2C70%2C71%2C73%2C74%2C78%2C79%2C81%2C82%2C85%2C86%2C88%2C89%2C94%2C95%2C97%2C98&language=english&go=Search)  

按照第一个公式写的，就是对于 $n=2m+1$，答案是：  

$$2^q+3m+\sum_{k\ge 1}\lfloor\frac{m-2^q}{2^k}\rfloor$$  

其中，$q=\lfloor\log_2 m\rfloor$，而第 $2m$ 项是第 $2m+1$ 项减一  
这玩意可以 $O(\log n)$ 来算，所以[写了一发](https://codeforces.com/contest/1362/submission/82528990)交上去pretest过了，结果第二天以看fst了/kk，并不知道为什么  
~~当然这个我也不会证明~~  

然后才发现还有一个更简单的公式，答案是  

$$\sum_{k\ge 0} \lfloor\frac{n}{2^k}\rfloor$$  

也是 $O(\log n)$，赛后按这个写过了  

这个还是可以稍微说明一下的，把它理解为对于每个二进制位一位一位地看  
对于第 $k$ 个（从 $0$ 开始编号）二进制位（位权 $2^k$），那么其对答案的贡献是 $\lfloor\dfrac{n}{2^k}\rfloor$  
也就是说，每 $2^k$ 个数，$k$ 位的数字会更改一次，对答案产生 $1$ 的贡献  
比如 $k=2$  

```plaint  
001
010
011
100 <----改变了一次
101
110
111
(1)000<------改变了一次
```  

为什么会这样应该挺好理解的，就是从 $0$ 到 $k$ 为上的所有数字累加一遍，就会改变一次  

代码  

```cpp  
signed main(){int T=read();while(T--){
	LL n=read(),f=0;
	if(n==1){
		std::puts("1");continue;
	}
	LL ans=0;
	for(reg LL now,k=1;;k*=2){
		now=n/k;
		if(!now) break;
		ans+=now;
	}
	std::printf("%lld\n",ans);
}
	return 0;
}
```

---

