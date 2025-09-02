# Vanya and Books

## 题目描述

Vanya got an important task — he should enumerate books in the library and label each book with its number. Each of the $ n $ books should be assigned with a number from $ 1 $ to $ n $ . Naturally, distinct books should be assigned distinct numbers.

Vanya wants to know how many digits he will have to write down as he labels the books.

## 说明/提示

Note to the first test. The books get numbers $ 1,2,3,4,5,6,7,8,9,10,11,12,13 $ , which totals to $ 17 $ digits.

Note to the second sample. The books get numbers $ 1,2,3,4 $ , which totals to 4 digits.

## 样例 #1

### 输入

```
13
```

### 输出

```
17
```

## 样例 #2

### 输入

```
4
```

### 输出

```
4
```

# 题解

## 作者：chufuzhe (赞：6)

这道题要求1-$n$的正整数一共有多少位，如果用$l$来表示$n$的位数，可以将1位的数的个数*1 + 2位的数的个数*2... + $l$位的数的个数* $l$

不难发现，结果就是1-$l$位的数的个数+2-$l$位的数的个数+...+$l$位的数的个数。

```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long long s=0; //1-n的正整数的位数
	int n,a=1;
	cin>>n;
	while(a<=n)
	{
		s+=n-a+1; //这一位数的数的个数
		a*=10;
	}
	cout<<s<<endl; //输出
	return 0;
}

```


---

## 作者：　　　吾皇 (赞：2)

### 首先拿到题目我们不妨用小数据来分析：
```
1-15共有21位，让我们来看看这21位是怎么来的：1-15中个位共有15个，十位有6个
不难推出此时ans=(n-1+1)+(n-10+1)=2n-9  //(n-10+1)即为去掉一位数后的数。
同理可得当n=101时，ans=(n-1+1)+(n-10+1)+(n-100+1)=3n-108
```
#### 现在傻子都知道了，当n为m位时，ans=m*n-9-...-9..9(m-1个9)还是打个表吧
### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,n,c,a[10]={0,9,108,1107,11106,111105,1111104,11111103,111111102,1111111101};//c代表位数,a在打表，毕竟用c++算更麻烦
int main() {
	cin>>n;x=n;
	while(n>0) {
		n/=10;
		c++;
	}//这里在算位数
	cout<<c*x-a[c-1];//根据上面的规律一个式子搞定
	return 0;
}
```


---

## 作者：迷残云 (赞：0)

和所有题解（~~好吧就两篇~~）不同的做法。

显然，我们看到$ \mathbb{n} $ $ \le $ $ 10^9 $，而且是一道求位数的题。

~~那么，如果你经验丰富的话，可以开始打表了~~

暴力的方法显然会爆，那么我们可以预处理（~~打表~~）来求这道题。

代码思路：

首先我们求一下$ \mathbb{n} $位的情况总数，如下代码（可以自己手算~~也可以无耻的利用他人代码拍一拍~~）

于是得到了$ \mathbb{a} $ 数组，那么我们统计一下n的位数（记得用替身$ \mathbb{t} $哦）。然后对于k位数来说，自然地可以分为前$ \mathbb{k}-1 $位和$ \mathbb{k} $位数的个数，$ \mathbb{n}-1 $已经在$ \mathbb{a} $里统计好了，于是我们机制的发现$ \mathbb{k} $位数的位数就是$ \mathbb{k} $.

因为题目要求到$ \mathbb{n} $，所以在$ \mathbb{k} $位数上的位数就是$ (\mathbb{n}- \mathbb{10^k}+1 )\times $
k位数了，于是得到代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long   a[15]={0,9,189,2889,38889,488889,5888889,68888889,788888889,8888888889};
int main()
{
	scanf("%lld",&n);
	long long t=n;
	int weishu=0;
	while(t)
	{
		t/=10;
		weishu++;
	}
	int k=1;
	for(int i=1;i<=weishu-1;i++)
	k*=10;
	if(n==pow(10,9))printf("8888888899\n");
	else printf("%lld",a[weishu-1]+(n-k+1)*weishu);
	return 0;
}
```


---

## 作者：zoobidubi (赞：0)

这题有一个很好理解的办法

我们可以根据判断位数的大小，然后推出以下公式

### 前一位的位数+（10的当前数位次方）*当前数位

其中c为log10（n）(n此时为10的整数次方）

 然后如果是整数就特判喽，不需要任何算法优化，就用if-else判断就好了(因为数据范围只有到10的九次方)

ps：如果这题的数据范围增强到10的100次方的话，可以用字符数组先预处理之前位数的和，然后用一个while求出位数，最后再递归求解，这里因为与该题解无关，留给路过的大佬思考

最后是
Code

```cpp
#include<bits/stdc++.h>
#define Open(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout);
#define ri register int
using namespace std;
long long n;
long long ans; 
int main()
{
    //Open("");
    scanf("%lld", &n);
    if (n < 10) 
    {
        cout << n;//10以内的数位数就是自己本身
        return 0;
    }
    else if (n < 100) 
    {
        cout << 11 + (n-10)*2;//根据每一位长度来分别判断，输出答案
        //公式就是前一位的位数+（10的当前数位次方）*当前数位
        return 0;//一旦输出后就结束程序，不然会多输出
    }
    else if (n < 1000)
    {
        cout << 192+(n-100) * 3;//这里和下面同理
        return 0;
    }
    else if (n < 10000)
    {
        cout <<2893+(n-1000) *4;
        return 0;
    }
    
    else if (n < 100000)
    {
        cout << 38894+(n-10000) *5;
        return 0;
    }
    else if (n < 1000000)
    {
        cout << 488895 + (n - 100000) * 6;
        return 0;
    }
    else if (n < 10000000)
    {
        cout << 5888896 + (n - 1000000) * 7;
        return 0;
    }
    else if (n < 100000000)
    {
        cout << 68888897 + (n - 10000000) * 8;
        return 0;
    }
    else if (n < 1000000000)
    {
        cout << 788888898+(n-100000000) * 9;
        return 0;
    }
    else cout << 8888888899;//最后一个因为再用公式就累赘了，所以直接输出
return 0;
}

```
end

---

