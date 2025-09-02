# 『MdOI R3』Number

## 题目描述

生活中我们会碰到一些特殊数字，这些数字使用一些特殊表达方式后会方便记忆和使用。比如说，$10^9+7$ 就非常常见——它相比于 $1000000007$，更方便选手看清数字而不必数 $0$，而且没有科学计数法的精度损失。

你现在有一个形如 $10^{k}+x$ 的数字，请还原成一般写法。

## 说明/提示

【样例解释】   

$10^9+7=1000000007$。

更多样例请[到这里](https://www.luogu.com.cn/paste/8lbtjwuk)领取。

【数据范围】   

**本题采用捆绑测试**，换言之，你只有通过一个子任务的所有测试点，才可以拿到该子任务对应分数。
|子任务编号|$x<$|$k\le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|1|$10$|$9$||12|
|2|$10$|$500$||15|
|3|$10^{18}$|$18$||8|
|4|$10^{18}$|$500$|$k\ge18$|25|
|5|$10^{18}$|$500$||40|

对于所有数据，$0\le x<10^{18}$，$0\leq k\leq 500$。

## 样例 #1

### 输入

```
9 7```

### 输出

```
1000000007```

# 题解

## 作者：yummy (赞：32)

**这是一篇C和C++通用的题解。**

**再次声明：本题不是高精模板题，虽然也可以练习高精。请各位同学选择对自己最有益的一种或几种方法AC本题。**

由于yummy算错日期，官方题解足足晚交了一天，题解区已经被常见的数 $0$ 法和Python法等占满了。

既然如此，如果想看常规解法的同学可以直接跳过本题解，本题解重点放在神奇的`sprintf`法。

---
首先，对于 $k\le 18$ 的情况我们仍然需要特判。计算 $10^k$ 可以使用for循环，`math.h`中的`pow`函数或者手动打表。

---
我们尝试进行一些小学生计算：

![temp.jpg](https://i.loli.net/2020/07/28/DKreMb15lR2FYGO.jpg)

观察这个竖式，可以将 $10^k>x$ 的情况表示成：

> 先输出字符1，然后将 $x$ 以固定的长度 $k$ 输出，不足 $k$ 位用前导零补齐。

在C/C++中，`printf`就可以上面的操作：

```c
//在主函数中加入这句
printf("%019d",19810);
```

你的输出是不是`0000000000000019810`？

因此，如果我们要计算 $10^{20}+x$，我们可以这么写：

```c
char ord[114]="1%020lld";
printf(ord,x);//相当于printf("1%020lld",x);
```

我们为了将 $k$ 填入形如`"1%0klld"`语句中，我们先将这个字符串存为`char ord[]`，然后我们`printf(ord,x);`即可。

接下来我们需要将 $k$ 以`"1%0klld"`的形式**输出到`ord`里面**，我们可以使用`sprintf`函数。

`sprintf`函数用法几乎和`printf`用法相同，唯一的不同点是`sprintf`需要在最前面加一个`char[]`表示输出的目标位置。因此，对于这道题我们可以这么写：

```c
//假设k=6,x=35
char ord[15];
sprintf(ord,"1%%0%dlld",k);//想输出%要在语句中填入%%
//ord现在是"1%06lld"
printf(ord,x);//1000035
```
那么我们就可以很快地写出完整代码（别看16行，只有250B，本来还能再短一点）：
```c
#include<stdio.h>
#include<math.h>
int k;long long x;
char ord[15];
int main()
{
	scanf("%d%lld",&k,&x);
	if(k<=18)
		printf("%lld",x+(long long)pow(10ll,k));
        //这里实际上不推荐这么用，pow函数有很大的精度误差，虽然我本地和你谷评测姬都能AC，但据说有些环境样例会输出1000000006.
	else
	{
		sprintf(ord,"1%%0%dlld",k);
		printf(ord,x);
	}
    return 0;
}
```

---

## 作者：chen_zhe (赞：29)

# 『MdOI R3』Number

对于自带高精的语言来说，这个题确实是个纯模拟。下面是 python 的代码。

```python
s=input()#python 读入的是一行文本
a=s.split(' ')#需要使用 split() 函数按照空格把原字符串划分为一个列表
k,x=int(a[0]),int(a[1])#python 的列表默认从 0 开始
print(10**k+x)#a**b 可以快速计算 a^b
```

但是作为一位使用 C++ 的 OIer 选手，当然还是要用 C++ 写一遍了。

作为一个月赛的 Div.2A，定位是个难度不超过普及组 T2 的小模拟（在[我的知乎](https://www.zhihu.com/question/412073132/answer/1394251057)有阐述过），因此我们肯定不会想着用高精去做。

我们会发现，一个数字乘以 $10$，本质上就是往这个数字后边写个 $0$。这也就启发了我们，计算 $10^k$ 的话，相当于写一个 $1$，然后在后边写 $k$ 个 $0$。

那么如何做到计算 $10^k+x$ 呢？观察数据范围，发现 $x<10^{18}$，故考虑分段，分成 $k \leq 18$ 和 $k>18$ 来做，因为前者可能考虑进位，而后者不用。

当 $k \leq 18$ 时，我们会发现，$10^{18}+10^{18}=2 \times 10^{18}<2^{63}-1$，即为 `long long` 可以存储下的范围，故可以考虑暴力计算。

当 $k>18$ 时，显然不能暴力计算。此时因为不用考虑进位，因此可以把这个数字分成三段：开头的 $1$，中间的一串 $0$，末尾的 $x$，其中开头和末尾我们都是已知的，因此我们关注的重点就在于：开头的 $1$ 和后面的 $x$ 之间差了多少个 $0$。因为 $10^k$ 一共提供了 $k$ 个 $0$，因此中间的 $0$ 的个数自然就是 $k-x\text{ 的位数}$。因此计算出 $x$ 的位数，就可以知道中间有多少个 $0$ 了。

这里计算 $x$ 的位数好像并不能用 `log()​` 直接去算，似乎精度会炸，直接暴力拆位计算得到 $x$ 的位数即可。顺带提醒一下 `c++` 自带的 `log()` 是 `ln()`，要用以 $10$ 为底的对数可以使用 `log10()`，或者考虑换底公式 $\lg x=\dfrac{\ln x}{\ln 10}$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

long long k,x;

int main()
{
	k=read(),x=read();
	if (k<=18)
	{
		long long ans=1;
		for (int i=1;i<=k;i++)
			ans=ans*10;
		cout << ans+x << endl;
	}
	else
	{
		putchar('1');
		long long x1=x,digit=0;
		while (x1>0)
		{
			digit++;
			x1/=10;
		}
		for (int i=1;i<=k-digit;i++)
			putchar('0');
		if (x!=0)
			cout << x << endl;//注意这里的特判，x=0 的话没必要再输出一个 0。
	}
	return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：14)

按理说应该是签到题，因为我只花了半个小时打月赛，所以都没想到用Python，空悲切。

分析：

因为数据可达 $10^{18}$ ，一看就不能用普通如题意，输出10的k次幂加上x。连ll都会炸，于是只能考虑到高精度的思路，或者必须采用某种优化方法来做。

### 一个骗分方法（27分，非正解）：

因为 $10^k$ 就是一个1带k个0，所以不防得出一个思路：

当x小于10的时候，输出k-1个0，最后一位上输出x。

当x小于100并且大于10的时候（二位数），输出k-2个0，最后两位输出x。

当x小于1000并且大于100的时候（三位数），输出k-3个0，最后两位输出x。

此可以通过$x \le 500$的测试点。

```
#include<bits/stdc++.h>

using namespace std;

long long k, x;

int main() {
    cin >> k >> x;
    if (k == 0) {
        cout << 1 + x;
        return 0;
    }
    if (x < 10) {
        for (int i = 0; i <= k; ++i) {
            if (i == 0) {
                cout << 1;
                continue;
            }
            if (i == k) {
                cout << x;
                break;
            }
            cout << 0;
        }
    }
    if (x >= 10 && x <= 99) {
        for (int i = 0; i <= k; ++i) {
            if (i == 0) {
                cout << 1;
                continue;
            }
            if (i == k - 1) {
                cout << x;
                break;
            }
            cout << 0;
        }
    }
    if (x >= 100 && x <= 999) {
        for (int i = 0; i <= k; ++i) {
            if (i == 0) {
                cout << 1;
                continue;
            }
            if (i == k - 2) {
                cout << x;
                break;
            }
            cout << 0;
        }
    }
    if (x >= 1000 && x <= 9999) {
        for (int i = 0; i <= k; ++i) {
            if (i == 0) {
                cout << 1;
                continue;
            }
            if (i == k - 3) {
                cout << x;
                break;
            }
            cout << 0;
        }
    }
    return 0;
}
```

虽然这样求下去可以达到$10^{18}$，但是非正解，所以不做过多说明，程序大概就是好多个循环和判断。

### 100分 正解：

#### C++：

C++高精度和板子一样，但是有两种写法，第一种就是乘法来做幂次方，加法相加，第二种利用上边的骗分思想来做，初始化的时候第一位上是1，其他k位上为0，这样就得出了 $10^k$ 存在了模板中的一个数组里，紧接着这个数和x求和就行了。

下面是核心处理：

```
for(int i = 0; i <= k; ++i){
	if(i==0) a[i]=1;
	else a[i]=0;
}
```

#### Python（或者其他语言）：

Python不需要担心高精度，并且`import math`库里有`pow()`这个函数可以直接用，加上一个字符串读入就完事。

Python方法较简单，但是对于写高精度咋也写不炸的大佬建议不要用Python，Ruby，等等这些语言。

```
//python 代码例子
s = input().split()
print (pow(10,int(s[0]))+int(s[1])) //强制转换int并且输出

```





---

## 作者：囧仙 (赞：11)

## 题目大意

给定 $k,x$ ，输出 $10^k+x$ 。

## 题解

观察到 $x\in[0,10^{18})$ ，在 $\text{long long}$ 范围内，所以我们可以按照 $k$ 的大小进行分类讨论。

-  $k\le 18$ 时，用 $\text{long long}$ 可以存下答案。直接暴力求解即可。

- $k>18$ 时，$10^{k}$ 最后 $18$ 位都是 $0$ 。于是不会有进位之类的问题困扰。我们将 $x$ 倒过来填进去就行了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
LL qread(){
    LL w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
char ans[600];
LL k,x; LL pwr(LL a,LL b){LL ret=1; up(1,b,i) ret*=a; return ret;}
int main(){
    k=qread(),x=qread();
    if(k<=18){
        printf("%lld\n",pwr(10,k)+x);
    } else {
        up(1,k+1,i) ans[i]='0'; ans[1]='1';
        up(1,18,i) if(x) ans[k-i+2]=x%10+'0',x/=10;
        printf("%s\n",ans+1);
    }
    return 0;
}
```

---

## 作者：囧仙 (赞：11)

## 题目大意

输入 $k,x$ ，输出 $10^k+x$ 。

## 题解

提供一个 $\text{Pascal} $ 版本的题解，共大家参考。

观察到 $0\le x< 10^{18}$ ，于是当 $k>18$ 时，$x$ 只会影响到结果最后的 $0$ 的部分，也就是不需要考虑进位的问题。

- 当 $k\le 18$ 时，我们能够使用 $\text{math}$ 库中的 $\text{power}$ 函数计算 $10^k$ ，并用 $\text{trunc}$ 函数转为整数。接着直接加上 $x$ 即可。

- 当 $k>18$ 时，我们能够使用 $\text{str}$ 函数将 $x$ 转化为字符串。这样便于我们使用 $\text{length}$ 函数统计 $x$ 的位数 $l$ 。只需要输出 $1$ 个 $\verb!1!$ ，和 $k-l$ 个 $\verb!0!$ ，再接着输出 $x$ 即可。

## 参考代码

```pascal
uses math;
var k,x,l,i,t:int64;
var s        :string;
begin
    read(k); read(x);
    if k<=18 then writeln(trunc(power(10,k))+x)
    else begin
        write(1); str(x,s); l:=length(s);
        for i:=1 to k-l do write(0);
        writeln(x); 
    end;
end.
```

---

## 作者：封禁用户 (赞：7)

[此处食用效果更佳](https://www.cnblogs.com/CM-0728/p/13475610.html)

### 前言

不知道是不是正解但是觉得挺好理解。

### 科学计数法

将一个数表示为$a\times 10^x$ 的形式。其中$a\leq10$，$x$ 为整数。

### $\sf Solution$

其实这题可以看成$10^k$ 与$x$ 两个大数相加。所以呢，就有了高精的写法。

- $k$ 的处理

我们都知道$10^k$ 其实就是$1000.......0000$（$1$ 后面$k$ 个$0$ ）

所以只要$a_{k+1}\gets1$ 。

- $x$ 的处理

就是一个裸的高精加了啦。

[强烈安利](https://www.luogu.com.cn/blog/CM0/solution-p1601)

### $\sf Code$

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string s;
int k,len;
int a[100001];
int main()
{
	scanf("%d",&k);
	cin>>s;
	for(int i=s.length()-1;i>=0;--i)
		a[++len]=s[i]-'0';//转换成数字
	a[k+1]++;//处理k
	len=max(len,k+1);//获取位数
	for(int i=1;i<=len;++i)
		if(a[i]>9)
			a[i+1]++,a[i]%=10;//处理进位
	if(a[len+1])
		++len;//最高位的处理
	for(int i=len;i>=1;--i)
		printf("%d",a[i]);//倒序输出结果
	return 0;
}
```

---

## 作者：k3v1n070828 (赞：6)

这是一道不需要高精度的数论水题，~~赛场上完全可以5min内切掉却犯了很多奇葩错误~~

当$k\leq18$时，正常进行整型运算。

>题目的良心之处在于$x\leq10^{18}$，$x$永远不会超过```long long```极限。

所以当$k>18$时，需要算出$x$的位数$cnt$，输出一个1，然后输出$k-cnt$个0，再输出$x$这个整体。

$\text{\green{AC}}$ Code：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long ans=1;
long long k;
long long x;
int calc(long long a)
{
	int cnt=0;
	while(a)
	{
		a/=10;
		cnt++; 
	}
	return cnt;
}//一个简单的算整型数位数的板子，不多解释
int main(){
	scanf("%lld%lld",&k,&x);//输入
	if(k<=18)
	{
		for(int i=1;i<=k;i++)
			ans*=10;
		ans+=x;
		printf("%lld",ans);
		return 0;
	}//k≤18时做正常运算
	else
	{
		printf("1");//先输出1
		if(x!=0)
		{
			for(int i=1;i<=k-calc(x);i++)
				printf("0");//输出k-cnt个0
			printf("%lld",x);//输出x
		}//注意：x可能是0，板子会把它误判为1位，需要一个特判
		else
		{
			for(int i=1;i<=k;i++)
				printf("0");
		}//x=0时直接输出一个1和k个0
	}//k>18时
	return 0;//结束
}
```

感谢阅读

---

## 作者：Eason_AC (赞：3)

### Content
给定 $k,x$ ，请将 $10^k+x$ 转写成一般形式。

数据范围：$0\leqslant k\leqslant 500, 0\leqslant x\leqslant 10^{18}$。

### Solution
我们看到这里的 $k$ 可以到 $500$ ，因此直接用 $\texttt{pow}$ 求出来肯定是不现实的，因此需要用字符串。

像在这里的话，我们可以直接把 $10^k$ 和 $x$ 分开来存储到两个字符串里面，然后的做法类似于高精加，就是把这两个数加起来就可以了。

总体来说难度不算大，红题应该是它最适合的难度。
### Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int k;
long long x;
char a[507], b[507];

int main() {
	scanf("%d%lld", &k, &x);
	int lena = k + 1, lenb = 0;
	a[0] = '1';
	for(int i = 1; i <= k; ++i)
		a[i] = '0';
	long long p = x;
//	printf("%d\n", p);
	int numb[27] = {0}, cnt = 0;
	while(p) {
		numb[++cnt] = p % 10;
		p /= 10;
	}
	for(int i = cnt; i >= 1; --i)
		b[lenb++] = numb[i] + '0';
//	puts("");
//	printf("%s %s\n", a, b);
	int aa[507] = {0}, bb[507] = {0}, ans[507] = {0};
	for(int i = 0; i < lena; ++i)	aa[lena - i] = a[i] - '0';
	for(int i = 0; i < lenb; ++i)	bb[lenb - i] = b[i] - '0';
	int lenc = 1, xx = 0;
	while(lenc <= lena || lenc <= lenb) {
//		printf("%d %d %d\n", aa[lenc], bb[lenc], xx);
		ans[lenc] = aa[lenc] + bb[lenc] + xx;
		xx = ans[lenc] / 10;
		ans[lenc] %= 10;
//		printf("%d\n", ans[lenc]);
		lenc++;
	}
	ans[lenc] = xx;
	while(!ans[lenc])	lenc--; 
	for(int i = lenc; i >= 1; --i)
		printf("%d", ans[i]);
	return 0;
}
```

---

## 作者：RBI_GL (赞：2)

很送分的一道题。

Solution 1：
--

直接用 pow 函数 + ull 

由于 $x$ 和 $k$ 都比较大，只能得20分。

Solution 2：
---

字符串模拟 + ull。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull k,x;
char stringg[100000005];
int main()
{
	cin>>k>>x;
	stringg[0] = '1';
	for (int i=1;i<=k;i++) 
	{
        stringg[i] = '0';
    }
    int i = k;
    while(x != 0)
	{
		stringg[i--]+=x%10;
        x/=10;
	}
	for (int i=0;i<=k;i++) cout<<stringg[i];
	return 0;
}



```
**但对于某些数据，这个代码会输出一些字符。**

实际得分：92pts

Solution 3：
--

加一个特判+小的数直接算。

100pts

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull k,x;
char stringg[100000005];
int main()
{
	cin>>k>>x;
	if (k==1) { //特判 
		cout<<(ull)10+x;
		return 0;
	}
	if (k<=18) { //小的数直接算 
		cout<<(ull)pow(10,k)+x;
		return 0;
	}
	stringg[0] = '1';
	for (int i=1;i<=k;i++) 
	{
        stringg[i] = '0';
    }
    int i = k;
    while(x != 0)
	{
		stringg[i--]+=x%10;
        x/=10;
	}
	for (int i=0;i<=k;i++) cout<<stringg[i];
	return 0;
}



```


UPD：2020/8/15
-

改了几个错别字。


---

## 作者：infinities (赞：1)

思路：模拟即可。

设 $x$ 的十进制下位数为 $num$。

分几种情况讨论：

1. $x = 0$。

此时需要特判，输出一个 1 和 $k$ 个 0 即可。

2. $num \le k$。

此时直接输出一个 1，然后输出 $k - num$ 个 0 和 $x$ 即可。

3. $num > k$ 。

此时直接输出 $10^k + x$ 即可，因为 $num > k$，又因为题目说 $x \le 10^{18}$，所以 $10^k \le 10^{18}$，直接加是不会炸的。

记得开 long long。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using namespace std;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}//快读
int k, x, qaq;
signed main(){
	cin >> k >> x;
	int qwq = x;
	while(qwq){
		qwq /= 10, qaq++;
	} //算位数
	if(k < qaq){
		cout << (int)x + ((int)pow(10, k));
		return 0;
	}//判断
	cout << 1;
	
	for(int i = 1; i <= k - qaq; i++){
		cout << 0;
	}
	if(x != 0)
	cout << x;
}

```

---

## 作者：Trafford1894 (赞：0)



### 这对自带高精度的Python来说就是一道模拟题题，~~Python秒解~~。

不多说，放代码：

```python
def Pow(a, b): #乘方,把a乘b次
    ans=1
    for i in range(b):
        ans=ans*a
    return ans

s=input().split()
t=int(s[0])#字符串转换成整型变量
b=int(s[1])
ans=Pow(10, t)
ans = ans + b
print(ans)
```


---

