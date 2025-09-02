# [JRKSJ R8] 网球

## 题目背景

~~垒球是橙色的~~ 网球是绿色的。~~网球是上升的，网球是下落的~~。

> And you never meet the people, you never shake their hands, you never hear their story or tell yours.  
> But somehow in the act of making something with a great deal of care and love, something's transmitted there.

## 题目描述

你有两个啮合在一起的齿轮，你希望齿轮 A 每转 $a$ 圈齿轮 B 都能转恰好 $b$ 圈。

由于精细度要求，每个齿轮都必须有**不少于** $c$ 个齿，求齿轮 A 和齿轮 B 的总齿数和的最小值。

## 说明/提示

### 样例解释

- 对于第一组数据，最优方案为齿轮 A 有 $6$ 个齿，齿轮 B 有 $4$ 个齿，答案为 $4 + 6 = 10$；
- 对于第二组数据，最优方案为齿轮 A 有 $10$ 个齿，齿轮 B 有 $5$ 个齿，答案为 $10 + 5 = 15$；
- 对于第三组数据，最优方案为齿轮 A 有 $8$ 个齿，齿轮 B 有 $20$ 个齿，答案为 $8 + 20 = 28$。

### 数据规模与约定

**本题采用捆绑测试。**

令 $v = \max(a, b, c)$。

- Subtask 0（13 pts）：$v \leq 20$；
- Subtask 1（13 pts）：$v \leq 5000$；
- Subtask 2（20 pts）：$v \leq 10^6$；
- Subtask 3（54 pts）：无特殊限制。

对于所有数据，保证 $1 \leq T \leq 8\times 10^3$，$1 \leq a, b, c \leq 10^9$。

## 样例 #1

### 输入

```
3
2 3 4
4 8 5
5 2 8
```

### 输出

```
10
15
28
```

# 题解

## 作者：Alystkia (赞：10)

### 思路

- 当没有最小值 $c$ 的限制时，我们只需要求出 $a$ 和 $b$ 的最简比。

- 当有了最小值 $c$ 的限制时，我们只需要适当扩倍就可以了。


### 解法

首先找出 $a$ 和 $b$ 的最大公约数 $k$，然后，用 $k$ 除以 $a$ 和 $b$，求出两个齿轮齿的最简比，再用 $c$ 除以这两个比中较小的比，向上取整，最后用得到这个结果乘上两个比值，再相加就完事了。



------------


### 代码

[不开 long long 见祖宗](https://www.luogu.com.cn/record/161973315)



```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int gcd(int a,int b)
{
    if(a%b!=0)
    	return gcd(b,a%b);
    else
    	return b;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int x,y,z;
    	cin>>x>>y>>z;
    	int k=gcd(x,y);
    	int x1=x/k,y1=y/k;
    	int h=min(x1,y1);
    	int ans=0;
    	if(z%h==0)
    		ans=z/h;
    	else
    		ans=z/h+1;
    	cout<<ans*x1+ans*y1<<endl;
	}
    
    return 0;
}
```

---

## 作者：GXZJQ (赞：4)

# P10570 [JRKSJ R8] 网球

- 更新于 $2024$ 年 $6$ 月 $13$ 日：修改了描述与 ${\LaTeX}$ 公式不符的问题。

[题目链接](https://www.luogu.com.cn/problem/P10570)

## 题目分析

这是一道数学题。

先来介绍一个库函数 `__gcd(a, b)`，它可以十分方便地求出两个数的最大公因数。

回到这道题，小学奥数知识告诉我们，两个齿轮，在某一时刻他们转过的齿数相同并且两个齿轮所转的圈数均为整数，当且仅当他们此时转过的齿数是它们各自齿数的最小公倍数。

所以，对于这道题，我们不妨先求出 $a$ 和 $b$ 的最小公倍数 $k$，先将它们同除 $k$，得到它们的最简整数比，然后对他们进行扩倍。

扩倍的时候，有两种方法，第一种是暴力扩倍，这样子效率比较低，会有一个点超时；第二种是再往前推一步：因为我们要齿轮数均不小于 $c$，那么很显然，我们至少要对更新后的 $a$ 和 $b$ 同时乘上一个 $\lceil \frac{c}{\min(a,b)}  \rceil$，即最后的对于每组输入的 $a$ 和 $b$，最终答案为：

$$\lceil \frac{c}{\min(\frac a {\gcd(a,b)},\frac b {\gcd(a,b)})}  \rceil \times (\frac a {\gcd(a,b)}+\frac b {\gcd(a,b)})$$


注意数据类型的选取和精度问题。

## 参考代码
```cpp
/**
 * 题目名称：P10570 [JRKSJ R8] 网球
 * 题目链接：https://www.luogu.com.cn/problem/P10570
 * 做题时间：2024年6月12日 
 * 考查内容：模拟，数学 
 * 难度评级：普及- 
 * 主要思路：略微推一下公式即可 
 * 注意事项：暂无 
 **/
#include<bits/stdc++.h>
using namespace std;
int t;
long long a, b, c;
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> a >> b >> c;
		long long k = __gcd(a, b);
		//找出最大公因数 
		a /= k, b /= k;
		//找出 a 和 b 的最简整数比 
		int num = ceil(double(c) / (double)(min(a, b) * 1.0));
		cout << num * (a + b)<< "\n";
	}
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：3)

这是一道简单的思维题。

思路：

首先，$a$ 齿轮与 $b$ 齿轮的转圈数之比为 $\frac{a}{b}$，则两齿轮的的齿数之比为 $\frac{b}{a}$，然后再化成最简比。

其次，齿轮之间的关系求出来了，接着再求齿轮的齿数。既然每个齿轮要不少于 $c$，那么齿轮数就以 $c$ 除以较小的齿轮数（向上取整）求出小的齿轮数，接着算出大的齿轮数，最后相加。

最后，根据上一步化简式子，得：$\frac{c + \min(a,b) - 1}{\min(a,b)} \times (a + b)$。

代码如下：
```
#include<bits/stdc++.h>
#define int long long//long long的重要性
using namespace std;
signed main(){
	int t;//多组数据
	cin>>t;
	while(t--){
		int a,b,c;
		cin>>a>>b>>c;
        	swap(a,b);
		int gcd=__gcd(a,b);//求出a,b的公因数
		a=a/gcd;//a,b都除以他们的公因数来化简
		b=b/gcd;
		cout<<(c+min(a,b)-1)/min(a,b)*(a+b)<<endl;	
	}return 0;
} 
```

---

## 作者：nightwatch.ryan (赞：3)

### 思路
小学数学题。

首先将 $a$ 和 $b$ 互质，也就是让 $a$ 和 $b$ 都除以他们的最大公因数，这样 $\dfrac{a}{b}$ 的值还是不变的。 

接下来题目中说必须有不少于 $c$ 个齿，那么我们让 $c$ 除以 $a$ 和 $b$ 中较小的那一个，我们设这个值为 $x$。

最后输出 $a$ 乘以 $x$ 的值加上 $b$ 乘以 $x$ 的值即可。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
int gcd(int a,int b){return b>0?gcd(b,a%b):a;}
int lcm(int a,int b){return a/gcd(a,b)*b;}
signed main(){
	int t;std::cin>>t;
	while(t--){
		int a,b,c;std::cin>>a>>b>>c;
		int gg=gcd(a,b);
		a/=gg;
		b/=gg;
		int cc=ceil(c*1.0/std::min(a,b));
		std::cout<<a*cc+b*cc<<std::endl;
	}
} 
```

---

## 作者：dulinfan2023 (赞：3)

## 题意

齿轮 A 每转 $a$ 圈齿轮 B 都能转恰好 $b$ 圈。

且两个齿轮的齿数均 $\ge c$。

求两个齿轮的齿数总和的最小值。

## 思路

首先我们很容易就能想到：齿轮 A 的齿数与齿轮 B 的齿数之比为 $b : a$。

先给 $b : a$ 这个比化简为 $x : y$。

那么易得，一个 $p$ 的倍数且 $\ge c$ 的最小值有以下情况：

- 若 $c \bmod p = 0$：则此数为 $c$，实际上就是 $(\frac{c}{p}) \times p$。

- 若 $c \bmod p \neq 0$：则此数为 $(\lfloor \frac{c}{p} \rfloor + 1) \times p$。

那么假设我们定的 $x$ 的倍数且 $\ge c$ 的最小值为 $X \times x$， $y$ 的倍数且 $\ge c$ 的最小值为 $Y \times y$。

那么答案即为 $\max(X,Y) \times x + \max(X,Y) \times y$，化简得 $\max(X,Y) \times (x + y)$。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
#define debug() cout<<"come on"<<'\n'
int gcd(int a,int b){
	if(b==0)return a;
	if(a%b==0)return b;
	return gcd(b,a%b);
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int a,b,c;
		cin>>a>>b>>c;
		int g=gcd(a,b);
		a/=g;b/=g;
		int l=c/b,r=c/a;
		if(c%b!=0)l++;
		if(c%a!=0)r++;
		cout<<max(l,r)*(a+b)<<'\n';
	}
	return 0;
}
```

~~求通过！！~~

---

## 作者：封禁用户 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10570)

为了找到最小齿数和，我们可以找一个数对 $(x,y)$（$x$ 是齿轮 A 的齿数，$y$ 是齿轮 B 的齿数），需要满足以下条件：

+ 当齿轮 A 转 $a$ 圈时，齿轮 B 转 $b$ 圈。即 $\dfrac{a}{x}=\dfrac{b}{y}$ 或者 $ay=bx$。
+ 齿轮 A 和齿轮 B 的齿数都不小于 $c$。即 $x\ge c$ 并且 $y\ge c$。

为了最小化 $x+y$，我们可以从 $c$ 开始尝试每一个可能的 $x$，并计算对应的 $y$，直到找到一个满足 $ay=bx$ 的整数解。

由于 $a$ 和 $b$ 的大小关系不确定，我们可以先计算 $a$ 和 $b$ 的最大公约数，然后用这个数来化简问题，找到最小值。

```cpp
#include <iostream>
#define int long long
using namespace std;
int gcd(int x, int y) { return (!y ? x : gcd(y, x % y)); }
int lcm(int x, int y) { return x / gcd(x, y) * y; }
signed main()
{
    int T;
    cin >> T;
    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;
        int l = lcm(a, b); // 最小公倍数，作为 A 和 B 齿数的基准
        int x = l / a; // 齿轮 A 转 a 圈时，需要 x 个齿
        int y = l / b; // 齿轮 B 转 b 圈时，需要 y 个齿
        // 确保齿数不小于 c
        int p = max((c + x - 1) / x, (c + y - 1) / y); // 向上取整
        x *= p, y *= p;
        cout << x + y << endl;
    }
    return 0;
}
```

---

## 作者：chenlongli (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10570)
### 思路
首先，我们将 $a,b$ 同时除以它们的最大公因数，得到的结果同样代表齿轮 A 转 $a$ 圈后齿轮 B 转 $b$ 圈。因为此时 $a,b$ 互质，所以我们此时齿轮 A 的齿孔即为 $b$，齿轮 B 的齿孔即为 $a$，但由于精细度要求，我们可以找出最小值最少乘几才能大于等于 $c$，也就是 $\lceil c \div \min(a,b)\rceil$，最后将 $a,b$ 都乘以这个数，将 $a,b$ 相加即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long cil(long long w1,long long w2)
{
    if (w1%w2==0)
    {
        return w1/w2;
    }
    else
    {
        return w1/w2+1;
    }
}
int main()
{
    long long t;
    cin>>t;
    for (long long i=0;i<t;i++)
    {
        long long a,b,c;
        cin>>a>>b>>c;
        if (a>b)
        {
            swap(a,b);
        }
        long long lc=__gcd(a,b);
        long long s1=a/lc,s2=b/lc;
        if (s1>=s2)//这个条件一定会成立
        {
            swap(s1,s2);
        }
        cout<<cil(c,s1)*s1+cil(c,s1)*s2<<endl;
    }
}
```

---

## 作者：LostKeyToReach (赞：1)

我们发现 A 和 B 的齿数之比是 $b : a$。

那么我们先化简比，假设 A 的齿数为 $kb$，B 的齿数为 $ka$，那么 $k$ 很好求：

$$
\lceil \frac{c}{\min(a, b)}\rceil
$$

直接输出 $ka + kb$ 即可。

代码如下：

```cpp
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	int t;
	read(t);
	while (t--) {
		ll a, b, c;
		read(a, b, c);
		ll t = gcd(a, b);
		a /= t, b /= t;
		ll bs = ceil(1.0 * c / min(a, b));
		write(bs * (a + b));
		putchar('\n');
	}
}
```

---

## 作者：linch (赞：0)

## 题意
根据齿轮规律，实际上要求最小的 $n+m$ 使得

$$
\frac{m}{a}=\frac{n}{b}(a,b\ge c)
$$

其中 $n$ 表示齿轮 A 的齿数，$m$ 表示齿轮 B 的齿数，均为整数。

## 解决
首先，来分析一下样例数据（如第二组数据），或者根据已学的数学知识，容易发现，$a,b$ 约去最大公约数后 $
\frac{m}{a}$ 和 $\frac{n}{b}$ 都需是整数，可得 $a\mid m$ 且 $b\mid n$。

约去最大公因数过程：
```cpp
int y=__gcd(a,b);
a/=y;
b/=y;
```

由于 $a,b$ 均为定值，易得，$m$ 越小，$n$ 也越小。

我们可以从小到大枚举 $a$ 的倍数，如果它也是 $b$ 的倍数，就符合题意。

但是 $a,b\ge c$，所以我们可以从**不小于** $c$ 的最小的 $a$ 的倍数开始枚举，防止超时。
```
int k=c%a;
int s=c+(a-k)%a;//注意要再 %a，因为当 c 是 a 的倍数时，k=0，a-k=a，c+a 是下一个倍数。
```

根据开头的等式，此时的 $n$ 应为 $m \div a \times b$，即判断这个数是否大于等于 $c$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,c,k;//与题意相同，k 在下面会解释。
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		int y=__gcd(a,b);
		a/=y;
		b/=y;//约去公约数。
		if(a>b){
			swap(a,b);
		}//让 a 更小，否则可能会跳过正确答案。
		int k=c%a;
		int i=c+(a-k)%a;////注意要再 %a，因为当 c 是 a 的倍数时，k=0，a-k=a，c+a 是下一个倍数。
		while(1){//枚举。
			if(i/a*b>=c){//判断并输出
				cout<<i+i/a*b<<endl;
				break;
			}
        i+=a;
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/162291071)

---

## 作者：封禁用户 (赞：0)

首先，我们要知道，两个轮各转过的总齿数一定，转的圈数和一圈的齿数是成反比的。

所以，两个齿轮的转圈数之比是 $a:b$，那么它们的齿数之比就是 $b:a$。

然后两个轮的齿数还要不小于 $c$，那么两个轮的齿数之和就是：

$$⌈\displaystyle \frac{c}{\min(a^{\prime},b^{\prime})}⌉ \times (a^{\prime} + b^{\prime})$$

其中因为 $a$ 和 $b$ 还必须互质，那么 $a^{\prime}$ 和 $b^{\prime}$ 就代表：

$$\begin{cases}
 a^{\prime} = \displaystyle \frac{a}{\gcd(a,b)} \\
 b^{\prime} = \displaystyle \frac{b}{\gcd(a,b)}
 \end{cases}$$

如果想变为综合算式，那么已知 $a$，$b$，$c$，两个轮的齿数之和就是：

$$⌈\displaystyle \frac{c}{\min(\displaystyle \frac{a}{\gcd(a,b)},\displaystyle \frac{b}{\gcd(a,b)})}⌉ \times (\displaystyle \frac{a}{\gcd(a,b)} + \displaystyle \frac{b}{\gcd(a,b)})$$

还要注意的是，因为 $1 \le \max(a,b,c) \le 10^9$，所以考虑最极端的情况，即 $c = 10^9$，$b = 10^9$，$a = 1$，代入原式答案为 $10^9 \times (10^9 + 1)$，答案肯定大于 $10^{18}$，需要开 long long。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() 
{
    int T;
    cin >> T;
    while (T--)
    {
    	int a, b, c;
    	cin >> a >> b >> c;
    	cout << (long long) ceil(1.0 * c / min(b / __gcd(a, b), a / __gcd(a, b))) * (b / __gcd(a, b) + a / __gcd(a, b)) << endl;
	}
    return 0;
}
```
最后感谢 C++ 库里的 ```__gcd``` 函数（算出两个数的最大公因数），帮我省去了写辗转相除法的空间。

---

## 作者：ggylz49 (赞：0)

## 思路分析
容易发现，$a,b$ 并未被保证互质。所以让 $a$ 和 $b$ 最小又保持原来的比。即 $a\gets a\div \gcd(a,b),b\gets b\div \gcd(a,b)$。

然后将 $a,b$ 对于 $c$ 扩倍求解即可。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long t;
	cin>>t;
	while(t--)
	{
	    long long a,b,c;
		cin>>a>>b>>c;
		long long gcd=__gcd(a,b);
		a/=gcd,b/=gcd;
		long long beishu=ceil((double)c/(double)min(a,b)*1.0);//转换成浮点型除避免精度问题，这一点参考了讨论区
		cout<<beishu*(a+b)<<endl;
	}
	return 0;
}
```

---

