# Minimum Product

## 题目描述

You are given four integers $ a $ , $ b $ , $ x $ and $ y $ . Initially, $ a \ge x $ and $ b \ge y $ . You can do the following operation no more than $ n $ times:

- Choose either $ a $ or $ b $ and decrease it by one. However, as a result of this operation, value of $ a $ cannot become less than $ x $ , and value of $ b $ cannot become less than $ y $ .

Your task is to find the minimum possible product of $ a $ and $ b $ ( $ a \cdot b $ ) you can achieve by applying the given operation no more than $ n $ times.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, you need to decrease $ b $ three times and obtain $ 10 \cdot 7 = 70 $ .

In the second test case of the example, you need to decrease $ a $ one time, $ b $ one time and obtain $ 11 \cdot 7 = 77 $ .

In the sixth test case of the example, you need to decrease $ a $ five times and obtain $ 5 \cdot 11 = 55 $ .

In the seventh test case of the example, you need to decrease $ b $ ten times and obtain $ 10 \cdot 1 = 10 $ .

## 样例 #1

### 输入

```
7
10 10 8 5 3
12 8 8 7 2
12343 43 4543 39 123212
1000000000 1000000000 1 1 1
1000000000 1000000000 1 1 1000000000
10 11 2 1 5
10 11 9 1 10```

### 输出

```
70
77
177177
999999999000000000
999999999
55
10```

# 题解

## 作者：—维尼— (赞：3)

## 题目描述

给你两个数和两个限制，和操作次数

每次操作可以让其中一个数减一，输出能让$a*b$最小的最优方法的到的乘值，也就是最后的$a*b$

## 解题思路
这题也是个贪心

小学知识告诉我们，两数相乘越接近越大，那么差越大，乘值越小，此时优先让$a,b$中较小的减，然后交换$a,b$

整体很简单，虽然看谷歌翻译不太好想是真的（

注意数据范围

**开$long long$**

## 简单又好写的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long a,b,x,y,n;
		cin>>a>>b>>x>>y>>n;
		long long ans=1e18;
		int i=2;
		while(i--){
			int da=min(n,a-x);
			int db=min(n-da,b-y);
			ans=min(ans,(a-da)*1ll*(b-db));//不开long long见祖宗
			swap(a,b);
			swap(x,y);
		}
		cout<<ans<<endl;
	}
}
```



---

## 作者：江户川·萝卜 (赞：3)

如果将n次操作都用完的话，那剩下a,b的和肯定都一样。小学数学学过，`两数和相等，差越大，积越小`。所以我们要使两数的差尽量大，所以要将一个数减完了再减另一个数。

为了防止出现奇奇怪怪的情况，我的策略是：对于每个数据，试两次。一次先减a，一次先减b。

代码很短，感性理解。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long solve(int a,int b,int x,int y,int n){
	long long ans;
	if(a-x>=n) a-=n,n=0;//先减第一个数
	else n-=(a-x),a=x;
	if(b-y>=n) b-=n,n=0;//再减第二个数。
	else n-=(b-y),b=y;
	ans=1ll*a*b;
	return ans;
}
int main(){
	int t,a,b,x,y,n;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d%d%d%d%d",&a,&b,&x,&y,&n);
		printf("%lld\n",min(solve(a,b,x,y,n),solve(b,a,y,x,n)));
        //先减a和先减b的最小积都求出来，取最小值。
	}
	return 0;
} 
```


---

## 作者：SSerxhs (赞：2)

易证和相等时两数差越大乘积越小（代码后补充证明）

故只需要考虑尽量给 $x$ 变小和尽量给 $y$ 变小这两种情况即可

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,x,y,a,b,c,t;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	read(t);
	while (t--)
	{
		read(a);read(b);read(x);read(y);read(n);
		if (a>b) {swap(a,b);swap(x,y);}
		if (a-n>=x) {printf("%lld\n",(ll)(a-n)*b);continue;}
		printf("%lld\n",min((ll)x*max(b-n+(a-x),y),(ll)max(b-n,y)*max(a-n+min(b-y,n),x)));
	}
}
```

证明：设 $x+y=a,x-y=b\ (b\ge0)$

则 $x=\dfrac{a+b}{2},y=\dfrac{a-b}{2},xy=\dfrac{a^2-b^2}{4}$

显然 $b$ 越大 $xy$ 越小

---

## 作者：猜一猜我是谁 (赞：1)

# 思路
小学四年级的时候我们就知道，和一定，差小积大。所以在这题中，我们可以让两数之差尽量大，从而让积尽量小。

所以我们可以尝试用两种方法来计算：

$1.$ 先把 a 减到最小，再把 b 减去 $n-x$。

$2.$ 先把 b 减到最小，再把 a 减去 $n-y$。

最后再把两个答案取 $\min$ 就可以了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        long long a,b,x,y,n,ans;//注意要开 long long
        cin>>a>>b>>x>>y>>n;
        long long u1=min(n,a-x);
        long long v1=min(n-u1,b-y);//第一种方法
        long long u2=min(n,b-y);
        long long v2=min(n-u2,a-x);//第二种方法
        ans=min((a-u1)*(b-v1),(b-u2)*(a-v2));//计算答案
        cout<<ans<<endl;
    }
}
```

---

## 作者：luosw (赞：1)

注意到对于每次操作后，无论执行哪一种，$a+b=C$，现在要求 $ab$ 的最小值，考虑构造下面的函数：

$$
f(x)=x(C-x)=-x^2+Cx
$$

求导后可得

$$
f'(x)=-2x+C
$$

令 $f'(x)=0$ 可得其最大值为 $x=\dfrac{C}{2}$，即 $x=C-x$ 的情况。由于 $f(x)$ 是一个二次函数，则其在区间 $(0,C)$ 间的最大值为 $x\to 0$ 的结果。因此我们得到**和一定，差大积小**。

然后只需要看 $\max(a-x,b-y)$ 取最大的那个减到 $a=x$，然后再减 $b-y$ 就可以了。

---

## 作者：jun头吉吉 (赞：1)

## 题意
给定$a,b,x,y,n$，你可以进行至多$n$次操作，每次操作把$a$或$b$减一，但必须保证$a≥x$与$b≥y$始终成立，求$ab$的最小值。

## 题解
一道很有意思的数学题，如果你上过二次函数应该随便切

首先，我们特判一种情况$a+b-x-y≥n$，那么不用想，肯定是减到$x,y$，直接输出$xy$即可

那么对于剩下的情况，肯定是不肯能变成$x,y$，根据常识，$n$次必须全部用掉，才有可能达到最小值

那么设这$n$个里有$t$个给$a$减，另外$n-t$个给$b$减，那么此时的乘积就为
$$(a-t)(b-n+t)$$
令$c=b-n$，那么化简完就为
$$-t^2+(a-c)t+ac$$
根据初中~~导数~~知识，这是一条 **开口向上，对称轴为$x=\dfrac{a-c}{2}$的抛物线** ，所以我们要考虑$t$的范围，再把特殊点带进去，由题意得：

$$\begin{cases}t≥0\\ t\le n\\ a-t≥ x\\ b+t-n≥y\end{cases}$$

整理得$\max(0,y+n-b)\le t\le \min(a-x,n)$

只要学过二次函数的就知道，这样的抛物线**最小值必定在两端取到**，因此我们只要带进去就行了

## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[55];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
#define int long long
int T,a,b,x,y,n,t,ans;
signed main(){
	in::read(T);
	while(T--){
		in::read(a,b,x,y,n);
		if(a+b-x-y<=n)out::write(x*y),out::putc('\n');//特判
		else{
			int aa,bb;
			int ans=0x7f7f7f7f7f7f7f7f;
			{
				t=max(y+n-b,0ll);
				aa=a-t,bb=b+t-n;
				if(y+n-b<=t&&t<=a-x&&t<=n)
				ans=min(ans,aa*bb);
			}{
				t=min(a-x,n);
				if(t<0)t=0;
				aa=a-t,bb=b+t-n;
				if(y+n-b<=t&&t<=a-x&&t<=n)
				ans=min(ans,aa*bb);
			}
			out::write(ans);
			out::putc('\n');
		} 
	}
	out::flush();
	return 0;
}
```

---

## 作者：daiarineko (赞：0)

## 0. 题意简述

给定 $a,b,x,y,n$，你可以进行至多 $n$ 次操作，每次操作把 $a$ 或 $b$ 减一，但必须保证 $a\ge x$ 与 $b\ge y$ 始终成立，求 $a\cdot b$ 的最小值

## 1. 题目分析

考察点：贪心

题目难度：普及-

时间复杂度：$\Theta(T)$

### 题目分析

如果不会高深的数论算法，那么就简单地分析情况吧。

因为要求 $a\cdot b$ 的最小值，所以要尽量拉大 $a$ 和 $b$ 的差距，同时尽可能让 $a$ 和 $b$ 变小。

所以，要么先尽量减 $a$，剩下的次数再尽量减 $b$，要么反过来进行。

得到：

当 $n<a-x$ 时，先减 $a$ 结果为 $(a-n)\times b$；  
否则先把 $a$ 减到 $x$，剩下 $n-(a-x)$ 次减 $b$，结果为 $x\times \max\{b-[n-(a-x)],y\}$。

当 $n<b-y$ 时，先减 $b$ 结果为 $(b-n)\times a$；  
否则先把 $b$ 减到 $y$，剩下 $n-(b-y)$ 次减 $a$，结果为 $y\times \max\{a-[n-(b-y)],x\}$。

最后对上面两个结果取最小值。

## 2. 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    int t;
    int a,b,x,y,n,nn;
    cin>>t;
    while(t--){
        cin>>a>>b>>x>>y>>n;
        nn=n;
        int aa,bb,ans1,ans2;
        if(nn>(a-x)){
            nn-=(a-x);
            aa=x;
            bb=b-nn;
            if(bb<y)bb=y;
            ans1=aa*bb;
        }else{
            aa=a-nn;
            bb=b;
            ans1=aa*bb;
        }
        if(n>(b-y)){
            n-=(b-y);
            bb=y;
            aa=a-n;
            if(aa<x)aa=x;
            ans2=aa*bb;
        }else{
            bb=b-n;
            aa=a;
            ans2=aa*bb;
        }
        cout<<min(ans1,ans2)<<endl;
    }
}
```

## 3. 坑点

1. 多组数据；
2. 爆 `int`。


---

## 作者：big_news (赞：0)

~~小学数学没学好啊，只会傻傻的推柿子。~~

这里有一个傻做法。

设 $a$ 变成了 $a-c$，$b$ 变成了 $b-d$，则减少的部分是 $-cb-ad+cd$，代入 $c+d=n$ 可以推出这是一个关于 $c$ 的二次函数，且开口向下，那么容易知道 $c$ 只有两种取值 $\max(0,y-b+n)$ 或 $a-x$，代入检验即可。

代码：
```cpp
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;
int t, a, b, x, y, n;
t = read(); while(t--){
    a = read(), b = read(), x = read(), y = read(), n = read();
    int ans = INF, c, d;
    if(a + b - x - y <= n) ans = x * y;
    else{
        c = min(n, a - x), d = min(b - y, n - c);
        ans = min(ans, (a - c) * (b - d));
        c = min(n, max(0ll, y - b + n)), d = min(b - y, n - c);
        ans = min(ans, (a - c) * (b - d));
    }
    printf("%I64d", ans);
    puts("");
}}
```

---

## 作者：Meaninglessness (赞：0)

## B. Minimum Product

**题目大意:**
>将 $a$、$b$ 一共减去 $n$,且需要保证 $a > x$、$b > y$ ,求 $a\times b$ 最小值。

***

**解题思路:**


我们可以用两种情况考虑:先减 $a$ 和先减 $b$。

如果减完第一个数后 $n$ 还有剩余,那么我们可以继续减第二个数。反之就不能再减。最后取两种情况较小的值。

注意此题$a,b\le 10^9$,$a\times b\le 10^{18}$,需要开long long。

***

**代码实现:[Code](https://www.luogu.com.cn/paste/ta62kyop)　时间复杂度$O(T)$**

---

## 作者：Ryo_Yamada (赞：0)

贪心题。刚开始贪心思路错了好几次。

我们知道，一个大数乘上一个小数才最小。

贪心思路：在可能的情况下，能减得越小的先减。（即 $\min(\max(a - n, x), \max(b - n, y))$。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int a, b, x, y, n;
		scanf("%d%d%d%d%d", &a, &b, &x, &y, &n);
		int ta = max(x, a - n), tb = max(y, b - n);
		if(ta > tb) {
			swap(a, b);
			swap(x, y);
		}//交换
		if(a - x <= n) {
			n -= a - x;
			a = x;
			b = max(y, b - n);
		}//若不需要 n 步就能将 a 减成 x，剩下的步数用来减 b
		else a -= n;
		long long tmp = 1ll * a * b;//需要开long long
		printf("%lld\n", tmp);
	}
	return 0;
}

```


---

