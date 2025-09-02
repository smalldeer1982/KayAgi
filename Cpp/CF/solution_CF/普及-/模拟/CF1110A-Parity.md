# Parity

## 题目描述

求$\sum_{i=1}^{k} a_i\times b^{k-i}$的奇偶性。

(如果看不懂上面式子的可以去看英语题目)

## 样例 #1

### 输入

```
13 3
3 2 7
```

### 输出

```
even
```

## 样例 #2

### 输入

```
10 9
1 2 3 4 5 6 7 8 9
```

### 输出

```
odd
```

## 样例 #3

### 输入

```
99 5
32 92 85 74 4
```

### 输出

```
odd
```

## 样例 #4

### 输入

```
2 2
1 0
```

### 输出

```
even
```

# 题解

## 作者：chenlingxi (赞：1)

## 先给个题面

先给你个b和个k

再给你一堆$a_1$,$a_2$,……$a_n$作为系数

让你判断$a_1*b^{k-1}+a_2*b^{k-2}+$……+$a_n$的奇偶性

是奇数输出odd，否则输出even

---

### 题解部分

显然的
- 奇数的任意自然数次幂都是奇数

- 偶数的任意正整数次幂都是偶数

那么k直接忽略

同样很显然的

- 任意整数乘偶数为偶数

那么分类讨论一下

当b为偶数时，除最后一项外，其余项均为偶数

那么只要看$a_n$的奇偶性

当b为奇数，则第i项的奇偶性由$a_i$决定

那么看$\sum_{i=1}^n$的奇偶性

复杂度O（n）

代码如下~~比赛的时候玄学写了一堆模~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int b,k;
	cin>>b>>k;
	b%=2;
	for(int i=1;i<=k;++i)cin>>a[i],a[i]%=2;
	int now=0;
	if(b==0&&a[k]==0)
	{
		cout<<"even"<<endl;
		return 0;
	}
	if(b==0&&a[k]!=0)
	{
		cout<<"odd"<<endl;
		return 0;
	}
	for(int i=1;i<=k;++i)
	now+=a[i];
	now%=2;
	if(now!=0)cout<<"odd"<<endl;
	else cout<<"even"<<endl;
	return 0;
} 
```

---

## 作者：BigJoker (赞：0)

# 0x00 前言

此题需要用到简单关于奇偶性的判断。

# 0x01 思路

我们小学就学过：

奇数 $\times$ 奇数 $=$ 奇数

奇数 $\times$ 偶数 $=$ 偶数

偶数 $\times$ 奇数 $=$ 奇数

那么 $b^{k-i}$ 这个式子，如果 b 是奇数那么这个式子的值就是奇数，否则就是偶数。

那么最终这一项的值就取决于 $a_i$，$a_i$ 如果和 b 同时为奇数，这一项才会为奇数，否则为偶数。

所以我们的方法就显而易见了，定义一个变量存储累加，奇数的情况 $+1$ 偶数的情况 $+2$，最后判断答案的奇偶性就可以了。

想到这里已经很不错了，不过还有一点问题，对于最后一项为 $b^0$，那么就需要另外判断：如果 $a_k$ 为奇数，则此项为奇数，否则为偶数。

以上就是正解，时间复杂度为 $O(k)$，由于 $k\le 10^5$，所以是不会超时的。

# 0x02 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
int main(){
	scanf("%d %d",&k,&n);
	int u;
	for(int i=1;i<n;i++){
		scanf("%d",&u);
		if(k%2 && u%2) ans++;
		else ans+=2;
	}
	scanf("%d",&u);
	if(u%2) ans++;
	if(ans%2) puts("odd");
	else puts("even");
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
求下面式子的奇偶性，其中 $a_i,k,b$ 会在输入中给定。

$$\sum\limits_{i=1}^k a_i\cdot b^{k-i}$$

**数据范围：$2\leqslant b\leqslant 100,1\leqslant k\leqslant 10^5,0\leqslant a_i<b$。**
## Solution
分类讨论的题目。

我们根据 $k$ 的奇偶性来分类讨论。

1. 如果 $k$ 是偶数，那么由于到了 $i=k$ 的时候，$a_k\cdot b^{k-k}=a_k$，并且除了这一项之外的所有项肯定都会是偶数（因为无论什么数与偶数相乘都是偶数），所以我们只需要看 $a_k$ 的奇偶性就好，毕竟整个式子的奇偶性就和 $a_k$ 是一样的。
2. 否则，如果 $k$ 是奇数，那么我们遍历整个 $a$ 数组，看里面有几个奇数，最后再判断奇数个数是否为奇数，如果是的那么这个式子的结果是奇数，否则它就是偶数。

讨论完之后，代码就很显而易见了。
## Code
```cpp
int b, k, a[100007], ans;

int main() {
	getint(b), getint(k);
	_for(i, 1, k)	getint(a[i]);
	if(!(b % 2)) return printf(a[k] % 2 ? "odd" : "even"), 0;
	_for(i, 1, k)	ans += a[i] % 2;
	printf(ans % 2 ? "odd" : "even");
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

# 结论题

题目网址：[$\mathcal{Link}$](https://www.luogu.com.cn/problem/CF1110A)

看到楼下的题解讲得过于简略，这里给予更详细的解析。

**题目大意：**

问 $\sum_{i=1}^k a_i\times b^{k-i}$ 的奇偶性。

**题目解析：**

很显然，既然问奇偶性，那么就是问该式**最后一位**的奇偶性。

第一种想法就是暴力 $+$ 高精，将 $i$ 从 $1$ 至 $k$ 循环，算出答案，时间复杂度：$\mathcal{O}(k^2)$，在 $k\le 10^5$ 的数据下难以承受。

~~接着，$\sout{python}$ 顺势而生。~~

----

考虑正解，先说几件非常显然的事情：

- 偶数的 $i$ 次方还是偶数，奇数的奇次方还是奇数。

  于是，题目变为求：$\sum_{i=1}^k a_i\times b$ 的奇偶性。
  
- 只有奇数 $\times$ 奇数才等于奇数。

  很显然，其它的情况都不是。
  
对于为什么要说第二个结论，那是因为：**原式的值的奇偶性取决于每一项的奇偶性！**

方便理解，设原式每一项答案的奇偶性为奇数的项数的个数为 $x$，那么显然:

- 如果 $x$ 为偶数，那么两两可以配对相加，得到 $\dfrac{x}{2}$ 个偶数，因为奇数 $+$ 奇数是偶数，所以最后答案就是偶数。

- 如果 $x$ 为奇数，两两相加，还会多出来一个奇数，所以最后答案就是奇数。

不难发现，只要知道每一项的奇偶性，统计共有几个答案为奇数的项，如果总数为偶数，那么答案就是偶数；否则，答案就是奇数的。

**注意：** 本题有个大坑，当原式中 $i=k$ 时，$b^{k-i}$ 次方等于 $1$！所以在循环当中，应该特判 $i$ 是否等于 $k$，若等于，那么这一项的奇偶性必定为 $a_k$ 的奇偶性，因为任何非 $0$ 的数的 $0$ 次幂等于 $1$，任何数 $\times1$ 都等于原来的数 。

~~恰恰是最重要的一个坑点，而其它的题解都没有写。~~

时间复杂度：$\mathcal{O}(k)$；空间复杂度：$\mathcal{O}(1)$。

$AC$ 记录：[$\mathcal{Link}$](https://www.luogu.com.cn/record/37907871)

~~这么多 $\sout{AC}$ 真好看。~~

$Code:$ ~~此为我第一篇放代码的题解~~

```cpp
#include<cstdio>
using namespace std;
int b,k,cnt;
//b和k都为题面中的b,k，cnt为统计答案为奇数的项数的个数。
bool s2;
//判断b的奇偶性，若为奇数则为false，否则为true。
inline bool iseven(int x){return x%2==0;}
//判断一个数是否为偶数的函数，若是返回true，否则返回false。
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
//快读，由于k=1e5，所以用快读。 
int main()
{
	b=read(),k=read();
	s2=iseven(b);
	//事先判断一下b的奇偶性，毕竟是个常量。 
	for(register int i=1;i<=k;i++)
	{
		bool s1=iseven(read());
		//边读边判断奇偶性 
		if(i==k&&!s1) cnt++;
		//如果i=k，那么b^{k-i}的值肯定为1，所以只要判断一下s1的奇偶性就好了
		//奇数*1还是奇数 
		else if(!s1&&!s2) cnt++;
		//否则就看看a_i和b是否都为奇数，只有都是奇数答案才是奇数。 
	} 
	if(iseven(cnt)) puts("even");
	else puts("odd");
	//判断答案为奇数的项的个数，
	//若为偶数则答案肯定是偶数，因为奇数两两可以配对。
	//否则如果是奇数，那么答案就是奇数，因为多出一个奇数不能配对成偶数。 
	return 0;
} 
```
貌似我的代码是最优解，这里纪念一下，~~或许以后就不是了。~~











---

## 作者：YUYGFGG (赞：0)

首先两个公式$：$奇数 $+$ 奇数 $=$ 偶数，奇数 $*$ 奇数 $=$ 奇数

如果 $a_i$ 与 $b$ 只要同时是奇数就 $s+1$，但最后一位只要判断 $a_i$.

最后判断 $s$ 的奇偶性

code：
```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
    long long b,n,k,i,a,s=0;
    cin>>b>>n;
    k=n-1;
    for(i=0;i<n;i++,k--){
        cin>>a;
        if(i<n-1){
            if((a%2!=0)&&(b%2!=0)){
                s++;
            }
        }
        if(k==0){
            if(a%2!=0){
                s++;
            }
        }
    }    
    if(s%2==0){
        cout<<"even"<<endl;
    }
    else{
        cout<<"odd";
    }
    return 0;
}

```

---

## 作者：lihanyang (赞：0)

这道题我们要求的主要就是$ a_i $和$ b^{k-i}$是否为偶数。   
如果其中一个是偶数，那么乘积一定就是偶数，就不用对最终奇偶性改变。   
如果都是奇数，那么flag++；表示奇数的个数。   
我们再看$ b^{k-i}$。   
若$ b $是偶数，$ k-i == 0 $，那么$ b^{k-i}$是1，奇数。   
若$ b $是奇数，随便什么$ k $ 和 $ i $都是奇数。    
所以就有了以下代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100002];
int main()
{
	int b,k;
	int flag=0;//奇数的个数
	cin>>b>>k;
	for(int i=1;i<=k;i++)
		cin>>x[i];
	for(int i=1;i<=k;i++)
	{
		if(x[i]%2==0) continue;//是偶数，pass
		if(k==i) flag++;//k-i是0，++
		if(k!=i and b%2==1) flag++;//b是奇数，++
	}
	if(flag%2==0)//奇数个数是二的倍数
	{
		cout<<"even"<<endl;//偶
	}
	else //其他
	{
		cout<<"odd"<<endl;//奇
	}
	return 0;
}
```


---

## 作者：WCG2025 (赞：0)

赶紧给CF~~水题~~写一发题解

------------

这道题题意十分清晰，就是一个判断奇偶性的问题，但是数据范围一看就知道，纯模拟会爆long long，就需要一点小小的优化

主要是要%上一个偶数，因为偶数模偶数还是偶数，奇数模奇数还是奇数，这样就相对方便的解决了数据范围的问题
而求b的k-i次方简单一个，快速幂搞定

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 2
inline long long read()
{
    long long x=0,f=1;
    char ch=getchar(); 
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
long long quick(long long a,long long b)
{
    long long res=1;
    while(b)
    {
        if(b&1)
        res=res*a%mod;
        a=a*a%mod;
        b>>=1;	
    }
    return res; 
} 
long long b,k;
long long a[100005];
long long sum;
int main()
{
    b=read();
    k=read();
    for(int i=1;i<=k;i++)
        a[i]=read();
    for(int i=1;i<=k;i++)
    {
        sum+=(a[i]*quick(b,k-i));//其实这里最好还是再%一个二
    }//但毕竟CF第一题，数据肯定相对水一点
    if(sum&1)
    cout<<"odd";
    else
    cout<<"even";
    return 0;	
} 
```

---

## 作者：Zechariah (赞：0)

这题我看好多人暴力求，秦九韶公式都出来了，其实没这个必要...  
考虑奇数$*$奇数总是奇数，偶数$*$任何数都是偶数  
那么如果$b$是奇数，$b$的正整数幂次一定是奇数，否则就是偶数，再判断一下$a_i$的奇偶，根据上述规律统计答案就行了  
复杂度$O(k)$
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};

int main(void)
{
    rg int b = fast_IO::read(), k = fast_IO::read(), ans = 0;
    b &= 1;
    while (k--)
    {
        rg int a = fast_IO::read(); a &= 1;
        if (k) { if (a && b)ans ^= 1; }
        else ans ^= a;
    }
    if (ans)puts("odd");
    else puts("even");
    return 0;
}

```

---

## 作者：xukuan (赞：0)

模拟+快速幂+同余

对于每一组询问，用快速幂求出计算的值（中间要取余！！！），然后对结果进行判断奇偶。

代码（codeforces评测id：49567777），我的比赛代码

因为题目简单，注释就不贴了
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll b,k,ans;

ll ksm(ll x,ll y){
    if(y==0) return 1;
    ll t=ksm(x,y/2)%2;
    t=t*t%2;
    if(y%2==1) t=t*x%2;
    return t%2;
}

int main(){
	cin>>b>>k;
	for(ll i=1; i<=k; i++){
		ll x;
		scanf("%I64d",&x);
		ans=(ans+x*ksm(b,k-i))%2;
	}
	if(ans%2) printf("odd");
	else printf("even");
	return 0;
}
```

---

## 作者：hpbl (赞：0)

一道很水的题目，但是好像是我打过的```CF```里面最难的```A```（雾

题意就是给你一个$b$进制下的$k$位数，让你判断它的奇偶性

第一感觉肯定是先求出这个数

然后我们发现$2 \le b \le 100,1 \le k \le 10^5$

这种做法明显会爆```long long```

我会高精!

然后你会发现当$b=100,k=10^5,a_i=99(1 \le i \le k)$时，这个数可以取到$100^{10^5}-1=10^{2 \cdot 10^5}-1= \underbrace{999 \ldots 999}_{2 \cdot 10^5}$，有整整$2 \cdot 10^5$位

这下空间不爆时间也爆了

转念一想```CF```这种短时间多题目的比赛好像也不会出高精这种恶心东西，而且也没有出过（雾

而且```A```好像也没有这么难？

其实只是让你判断奇偶，根本不需要存整个数

看题目，$n = a_1 \cdot b^{k-1} + a_2 \cdot b^{k-2} + \ldots a_{k-1} \cdot b + a_k$

当$b \equiv 0(mod \ 2)$时，$n \equiv a_1 \cdot b^{k-1} + a_2 \cdot b^{k-2} + \ldots a_{k-1} \cdot b + a_k   \equiv a_k(mod 2)$，直接忽略前$k-1$个数输出$a_k$的奇偶性就行了

当$b \equiv 1(mod \ 2)$时，$n \equiv a_1 \cdot b^{k-1} + a_2 \cdot b^{k-2} + \ldots a_{k-1} \cdot b + a_k   \equiv a_1 + a_2 + \ldots + a_{k-1} + a_k(mod 2)$，开一个```bool```变量```ans```标记$a_1 + a_2 + \ldots + a_{k-1} + a_k$的奇偶性，然后每次```ans^=a_i%2```即可

附上代码

抄题解勿扰
```cpp
include<cstdio>
using namespace std
int b,k;
bool ans;
int main()
{
    scanf("%d %d",&b,&k);
    if(b&1)
    {
        for(int i=1,a;i<=k;i++)
        {
            scanf("%d",&a);
            ans^=a&1;
        }
        if(ans) puts("Odd");
        else puts("even");
    }
    else
    {
        for(int i=1,a;i<=k;i++)
        {
            scanf("%d",&a);
            if(i==k)
            {
                if(a&1) puts("Odd");
                else puts("even");
            }
        }
    }
}
```

---

