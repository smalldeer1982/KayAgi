# Yet Another Meme Problem

## 题目描述

Try guessing the statement from this picture <http://tiny.cc/ogyoiz>.

You are given two integers $ A $ and $ B $ , calculate the number of pairs $ (a, b) $ such that $ 1 \le a \le A $ , $ 1 \le b \le B $ , and the equation $ a \cdot b + a + b = conc(a, b) $ is true; $ conc(a, b) $ is the concatenation of $ a $ and $ b $ (for example, $ conc(12, 23) = 1223 $ , $ conc(100, 11) = 10011 $ ).  $ a $ and $ b $ should not contain leading zeroes.

## 说明/提示

There is only one suitable pair in the first test case: $ a = 1 $ , $ b = 9 $ ( $ 1 + 9 + 1 \cdot 9 = 19 $ ).

## 样例 #1

### 输入

```
3
1 11
4 2
191 31415926```

### 输出

```
1
0
1337```

# 题解

## 作者：Rainbow_qwq (赞：6)

[CF1288B Yet Another Meme Problem](https://www.luogu.com.cn/problem/CF1288B)

---

# 思路

数学题，主要是推柿子。

设$b$的长度为$lb$。那么：

$$a\times b +a+b=conc(a,b)$$
$$a\times b +a+b=a\times 10^{lb}+b$$
$$a\times b +a=a\times 10^{lb}$$
$$a\times (b+1)=a\times 10^{lb}$$
$$b+1=10^{lb}$$
$$b=10^{lb}-1$$

所以$b=9,99,999,\cdots$

枚举$b$就行了。对于$b=9,99,999,\cdots$，$a$可以随便取。

代码部分：

```cpp
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

void work()
{
	int a=read(),b=read(),res=0;
	for(int i=10;;i*=10){
		if(i-1>b)break;
		res+=a;
	}cout<<res<<endl;
}
```

---

## 作者：icefake (赞：2)

首先，这道题作为B题，题意应该很好理解。

### 题目翻译

输入2个 ($int$) 变量 $A$ 和 $B$，计算数对$(a,b)$满足 $ab+a+b=conc(a,b)$，其中 $1≤a≤A$, $1≤b≤B$。

$conc(a,b)$表示 $a$ 与 $b$ 相连接所得到的数，(例如：$conc(12,23)=1223$，$conc(100,11)=10011$ )。

a与b中不包含前导零。

### 推算

作为蒟蒻的我第一眼看题便懵了，但旁边的一位dalao——@Exqule,见到题便说可以吧上面的方程式简化，(即：把左右两边各减去一个 $b$)，顿时恍然大悟，但即使在该dalao的带领下，本蒟蒻还是提交了~~7~~很多遍才过~~身败名裂~~(时时刻刻要提醒你自己，~~不能搭讪~~要记得开 $longlong$)。。。

看这个方程式：$ab+a+b=conc(a,b)$ $<=>$ $a(b+1)+b=10^na+b$

看到这两个 $b$ 没有？这不消掉都对不起出题人好吧。于是我们就得到了 $a(b+1)=10^na$ 

看到这两个 $a$ 没有？这不消掉。。。~~人类的本质~~。。。于是我们就得到了 $b+1=10^n$ ， 其中 $n$ 为 $b$ 的长度，所以我们就知道了——只有 $b$ 的各个数位上的数都为 '9' 时，才符合该方程式。

然后就可以开始~~打码~~，呸，打代码了。。。
本蒟蒻实在是太弱了，以至于当时只会交DB(dabiao)的代码。

### ~~dabiao~~AC代码

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
long long int t, A, B, temp, ans, sum;
int sjs;

void dabiao()
{
	if(B == 9) sum ++;
    	else if(B == 99) sum ++;
    	else if(B == 999) sum ++;
    	else if(B == 9999) sum ++;
    	else if(B == 99999) sum ++;
    	else if(B == 999999) sum ++;
    	else if(B == 9999999) sum ++;
    	else if(B == 99999999) sum ++;
    	else if(B == 999999999) sum ++;
}

void normol()
{
	bool truth = 1;
	while(B > 0) {
		if(B % 10 != 9) {
			truth = 0;
			break;
		}
		else B /= 10;
	}
	if(truth) sum ++;
}

int main()
{
    cin>>t;
    while(t --) {
        sum = 0;
        ans = 0;
        cin>>A>>B;
        temp = B;
        while(temp > 0) {
            temp /= 10;
            sum ++;
        }
        srand((int)time(0));
        sjs = rand() % 100;
        if(sjs % 2 == 0) dabiao();
        else normol();
        sum --;
        ans = sum * A;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Rosmarinus (赞：1)

## 思路分析

一道简单的数学题。

首先，考虑到 $\text{conc}(a,b)$ 的特殊性，我们显然要将它转化一下：

设 $l$ 表示 $b$ 的长度（如当 $b=312$ 时 $l=3$），则：

$$\text{conc}(a,b)=a\times10^l+b$$

看着难受，先令 $10^l=t$。

因此：

$$a\times b+a+b=at+b$$

$$a\times b+a=at$$

$$a\times(b+1)=at$$

$$b+1=t$$

稍加思索，我们发现：只有在 $b=9,b=99,b=999,b=9999,\dots$ 时这个等式才会成立。

至于 $a$，等式是否成立与 $a$ 无关，$a$ 可以是其值域中的任意值。

## Code

```cpp
#include<iostream>
#include<cmath>
using namespace std;

void Work()
{
    long long a, b, ans = 0, t = 9;
    cin >> a >> b;
    while(t <= b)
    {
        ans += a;
        t = t * 10 + 9;
    }
    cout << ans << endl;
}

int main()
{
    int T;
    cin >> T;
    while(T --) Work();
}
```

---

## 作者：BotDand (赞：1)

# $\text{Problems}$
求$a,b$中有几对$(a,b)$满足$a\cdot b+a+b=conc(a,b)$，其中$conc(a,b)$表示将$a,b$拼接在一起。
# $\text{Answer}$
$\because conc(a,b)=a\cdot 10^{\text{b的位数}}+b$

不妨设$\text{w=b}$的位数，则$conc(a,b)=a\cdot 10^{w}+b$

$\because a\cdot b+a+b=a\cdot 10^{w}+b$

两边同减去$b$得$a\cdot b+a=a\cdot 10^{w}$

两边同除以$a$得$b+1=10^{w}$

移项得$b=10^{w}-1$

$\therefore \text{b为9,99,999...}$

所以有情况$\text{(1,9)，(2,9)，...，(a,9)，(1,99)，(2,99)，...，(a,99)...}$

暴力枚举即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,x,ans,t;
void work()
{
    cin>>a>>b;
    x=0;ans=0;
    while(x*10+9<=b)
    {
        ans++;
        x=x*10+9;
    }
    cout<<a*ans<<"\n";
}
int main()
{
    cin>>t;
    while(t--) work();
    return 0;
}
```


---

## 作者：lemonfor (赞：1)

一道降智数学题。。。

题目让我们找出数对 $(a ,b)$ ,使得 $a * b + a + b$ $=$
$conc(a,b)$,$conc()$即为将两个数合在一起。我们可以先来分析一下这个好吃的柿子。

设 $k$ 为 $b$ 的数字位数，即原柿可化为：

$$
a * b + a = a * 10 ^k
$$

即

$$
b + 1 = 10^k
$$

又因为只有当 $b$ 为 $9 ，99 ，999……$ 时才对答案有贡献，所以，我们可以把$b$中全是由$9$构成的数目算出来，而对于 $a$ ， $a$ 在上面的柿子中被约去，即 $a$ 的构成不产生影响，所以每一个 $a$ 都可以对答案做出贡献，所以答案就为

$$
a * (k - 1)
$$


代码如下
```cpp
#include<cstdio>
#define int long long
#define _ 0
using namespace std;
int t ,a ,b ,wei;
int read() {
    char cc = getchar() ; int cn = 0  ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar() ;}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc=  getchar();
    return flus * cn;
}
int getnumb(int x) {
    int ans = 0;
    while(x > 0) ++ans ,x /= 10;
    return ans - 1;
}
signed main() {
    t = read();
    while(t --) a = read() ,b = read() ,printf("%lld\n" ,a * getnumb(b + 1));//+1用来避免像99等特殊情况
    return ~~(0^_^0);
}
```

---

## 作者：_zhx (赞：0)

#  CF1288B Yet Another Meme Problem 

## 题目大意

给定 $A,B$，问有多少个二元组 $(a,b)$ 满足

$1\le a \le A,1\le b\le B$

且

$a\cdot b+a+b=a$ 和 $b$ 拼接起来的数

且 $a,b$ 没有含有前导 $0$。

### 做法

我们不妨把 $b$ 的长度设为 $s$。

得：

$a\cdot b+a+b=a\times10^s+b$

再同时去掉 $b$。

得：

$a\cdot b+a=a\times10^s$

简化后。

得：

$a\cdot(b+1)=a\times10^s$

再同时除以 $a$。

得：

$b+1=10^s$

因为 $b+1=10^s$，所以 $b=10^s-1$。

再用 for 循坏枚举 $s$，就能求出答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,x=0;
int main()
{
	scanf("%lld",&t);//t组数据
	while(t--)
	{
		x=0;scanf("%lld%lld",&a,&b);
		for(int i=10;i-1<=b;i*=10) x+=a;
     		//i直接从10开始，就等于b=s-1
		printf("%lld\n",x);
	}
	return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1288B)

## 思路

一道数学题。

题目就是问 $a\times b+a+b= conc(a,b)$。

设 $b$ 的长度为 $l$。

$\displaystyle ab+a+b=conc(a,b)$

$\displaystyle ab+a=10^la$

$\displaystyle (b+1)a=10^{lb}a$

$\displaystyle b+1=10^l$

$\displaystyle b=10^l-1$

## 代码

```
#include<bits/stdc++.h>
using namespace std; 
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        long long a,b;
        long long sum=0;
        cin>>a>>b;
        for(int i=10;i-1<=b;i*=10)
        {
        	sum+=a;
    	}
   		cout<<sum<<"\n";
    }
    return 0;
}
```


---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1288B)

## 题意
给定 $A,B$ 问有多少个二元组 $(a,b)$ 满足 $1\le a \le A,1\le b\le B$ 且 $a\cdot b+a+b=\operatorname{conc}(a,b)$。其中 $\operatorname{conc}(a,b)$表示将 $a,b$ 拼接在一起，比如 $\operatorname{conc}(12,23)=1223,\operatorname{conc}(100,11)=10011,a,b$ 不能含有前导 $0$。

## 分析

题目是要让 $(a,b)$ 满足 $1\le a \le A,1\le b\le B$ 并且 $a\times b+a+b=\operatorname{conc}(a,b)$ 然后 $\operatorname{conc}(a,b)$ 就是连接 $a,b$。

然后就是推公式了。

设 $b$ 长度为 $l$，然后可以得到
			    
$a\cdot b+a+b=a^l+b$

$a\times b +a=a\times 10^{l}$
 

$a\times (b+1)=a\times 10^{l}$
 

$b+1=10^{l}$
 

$b=10^{l}-1$

## 下面是通过代码
```
#include<bits/stdc++.h>
using namespace std; 
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long a,b,ans=0;
		cin>>a>>b;
		for(int i=10;i-1<=b;i*=10)
		{
		ans+=a;
	}
	cout<<ans;
			printf("\n");
	}
	return 0;
}
```


---

## 作者：HEzzz (赞：0)

[题目跳转建](https://www.luogu.com.cn/problem/CF1288B)

### 分析

令：$P$ 表示 $b$ 有多少位数。

$$
a\times  b+a+b=conc(a,b)
$$

$$
a\times  b+a+b=a\times 10^P+b
$$

$$
a\times  b+a=a\times 10^P
$$

$$
a\times (b+1)=a\times 10^P
$$

$$
b+1=10^P
$$

$$
b=10^P-1
$$

可以知道只需要满足 $b$ 的要求，$a$ 就可以随便选，最后枚举 $P$ 即可。

### code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
const int N=1e5+10; 
lxl t,a,b;
int main() 
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		lxl ans=0;
		for(int i=1;;i++)
		{
			lxl t=pow(10.0,i)-1;
			if(t<=b) ans+=a; 
			else break;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：__int127 (赞：0)

## CF1288B Yet Another Meme Problem 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1288B)

### 题目大意

本题有多组数据。

给定两个整数 $A,B$，求出二元组 $(a,b)$ 的个数，其中 $1\le a\le A\le10^9$，$1\le b\le B\le10^9$，$ab+a+b=\text{conc}(a,b)$，且 $a,b$ 不允许有前导零。$ab$ 表示 $a\cdot b$，$\text{conc}$ 表示数字的拼接。

### 思路

这其实是一道数学题，我们先把式子 $ab+a+b=\text{conc}(a,b)$ 化简一下，这里应用到了小学方程知识。

$$ab+a+b=\text{conc}(a,b)$$

$$ab+a+b=a\cdot 10^{len(b)^{[1]}}+b$$

$$ab+a=a\cdot10^{len(b)}$$

$$b+1=10^{len(b)}$$

$$b=10^{len(b)}-1$$

$[1]$：$\text{len}$ 表示数字的长度，即数字的位数。

所以，只要满足 $b=9,99,999\ldots\ldots$，等式 $ab+a+b=\text{conc}(a,b)$ 就成立，这里有一个易错点，方案个数可能很大，所以个数变量需要开 long long。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long a, b, gs;
int main(){
	ios::sync_with_stdio(false);// 关闭读写同步
	cin.tie(0);
	cout.tie(0);
	cin >> t;// t 组数据
	while (t--){
		cin >> a >> b;
		for (int i = 9; i <= b; i = i * 10 + 9){
			gs += a;// a 从 1 到 a 都可以，所以每次加 a
		}
		cout << gs << "\n";// 输出并换行
		gs = 0;// 重置 gs 变量
	}
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：墨忧 (赞：0)

## 思路

根据题意，很显然有以下等式：

$a×(b+1)+b=a×10^n+b$ 

其中 $n$ 为 $b$ 的长度（或者说位数）。

化简可得:

$a×(b+1)=a×10^n$ 

$b=10^n-1$

所以可以得出：

当 $a×b+a+b=conc(a,b)$ 时，对于 $a$ ，只需要满足任意 $1≤a≤A$ 即可。

对于 $b$ ，则需要有 $b=\sum_{i=0}^{n}{9×10^i}$ ，即 $b=9,99,999…$ 且 $1≤b≤B$ 。

所以，可以每次枚举 $b$ ，设最终合法的 $b$ 的数量为 $p$ ，最终合法的方案数即为 $p×A$ 。

最后，注意答案可能会爆 ```int``` ，所以要转化为 ```long long``` 输出。



## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,b,A,B,ans;
inline int read()//快读 
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch && ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int main()
{
	t=read();
	for(int jsq=1;jsq<=t;jsq++)
	{
		ans=0;
		A=read();
		B=read();
		b=9;
		while(b<=B)
		{
			ans++;
			b=10*b+9;
		}
		cout<<(long long)ans*A<<'\n';//转化为 long long 形式输出 
	}
	return 0;
}
```



---

## 作者：清清老大 (赞：0)

## 思路

设 $b$ 的位数为 $l$ ，则：

$$ab+a+b=a\times10^l+b$$

$$ab+a=a\times10^l$$

$$\because a\ne 0$$

$$\therefore b+1=10^l$$

$$b=10^l-1$$

$$b=9,99,999,...$$

因为 $b<B$ ，所以 $b$ 可能的取值有 $l$ 个，因为化简后的式子取值与 $a$ 无关，所以 $a$ 有 $A$ 个可能的取值，一共有 $A(l-1)$ 个满足条件的二元组。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    long long a,b;
    int T;
    cin >> T;
    while(T --)
    {
        cin >> a >> b;
        cout << a * (to_string(b + 1).length() - 1) << endl;
    }
    return 0;
}
```


---

## 作者：银河AI (赞：0)

### 思路

主要是推式子。

$a \times b+a+b= \text{conc}(a,b)$

$a \times b +a+b+1=\text{conc}(a,b)+1$

$(a+1) \times (b+1)=\text{conc}(a,b)+1$

现在假设我们已知 $a$。

令 $a+1=k$ , 并设 $b$ 有 $n$ 位。

则原式为：

$k \times (b+1)=\text{conc}(a,b)+1$

考虑 $\text{conc}(a,b)$

$\text{conc}(a,b)=a \times 10^n+b$

代回原式，得

$k \times (b+1)=a \times 10^n+b+1$

$b \times (k-1)=a \times 10^n-k+1$

$b = \frac{a \times 10^n-k+1}{k-1}$

将 $k=a+1$ 代回原式，则原式为：

$b=\frac{a \times 10^n-(a+1)+1}{a+1-1}=10^n-1$

我们可以发现 $b$ 与 $a$ 的大小无关，且 $b$ 为一个 $10$ 的幂次方 $-1$。

所以我们只需要找到 $b$ 有多少个取值，再乘上 $a$ 就好了。

### AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b;
int s,cnt;
int t;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&a,&b);
		cnt=s=0;
		while(s*10+9<=b){
			cnt++;
			s=s*10+9;
		}
		printf("%lld\n",cnt*a);
	}
}
```


---

