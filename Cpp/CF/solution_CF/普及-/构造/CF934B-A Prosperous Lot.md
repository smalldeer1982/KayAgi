# A Prosperous Lot

## 题目描述

Apart from Nian, there is a daemon named Sui, which terrifies children and causes them to become sick. Parents give their children money wrapped in red packets and put them under the pillow, so that when Sui tries to approach them, it will be driven away by the fairies inside.

Big Banban is hesitating over the amount of money to give out. He considers loops to be lucky since it symbolizes unity and harmony.

He would like to find a positive integer $ n $ not greater than $ 10^{18} $ , such that there are exactly $ k $ loops in the decimal representation of $ n $ , or determine that such $ n $ does not exist.

A loop is a planar area enclosed by lines in the digits' decimal representation written in Arabic numerals. For example, there is one loop in digit $ 4 $ , two loops in $ 8 $ and no loops in $ 5 $ . Refer to the figure below for all exact forms.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
462```

## 样例 #2

### 输入

```
6
```

### 输出

```
8080```

# 题解

## 作者：Anguei (赞：8)

**贪心算法入门题**。

易知，在 $0-9$ 中，圈数最多的是数字 $8$。为了用更少的数字达到指定的总圈数，不妨先两个两个地填，最后再判断一下是否需要再填一个圈就好。

由于 $n <= 10^{18}$ ，所以即使都填上 $8$，最大圈数也只有 $36$。需要一个判断：如果 $k > 36$，直接输出 $-1$。

此题有一个陷阱。题目输出要求是正整数（positive integer），所以填一个圈**不能用数字零**。

代码非常简单，若不懂，可看文字描述。

```cpp
#include <iostream>

int main() {
    int k;
    std::cin >> k;
    if (k > 36) {
        std::cout << -1 << std::endl;
        return 0;
    }
    for (int i = 1; i <= k / 2; ++i)
        std::cout << 8;
    if (k % 2)
        std::cout << 4;
    std::cout << std::endl;
}
```

---

## 作者：PC_DOS (赞：3)

本题可以借助贪心的思想，由于'8'的圈圈数最多，因此我们可以采用尽可能多的'8'来填充答案。由于题目要求答案不超过10^18，因此我们可以知道当圈圈数大于等于37时，将无解(因为37个圈至少需要18个8+1个0，越界了)。生成答案时，我们可以分奇偶考虑：如果要求的圈数N为奇数，则生成(N-1)/2个"8"和1个"6"(防止出现圈数为1这种情况)；如果N为偶数，则生成N/2个"8"即可。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long nCount; //圈圈数
	register long long i; //循环计数器
	cin >> nCount; //读入圈数
	if (nCount >= 37){ //圈圈数大于等于37时，将无解
		cout << -1; //无解
	}
	else{ //否则生成答案，分奇偶考虑
		if (nCount % 2 == 0){ //如果要求的圈数nCount为偶数
			for (i = 1; i <= nCount / 2; ++i){ //生成nCount/2个"8"即可
				cout << 8;
			}
		}
		else{ //如果要求的圈数nCount为奇数
			for (i = 1; i <= nCount / 2; ++i){ //生成(nCount-1)/2个"8"
				cout << 8;
			}
			cout << 6; //补一个"6"
		}
	}
	return 0; //结束
}
```

---

## 作者：wuwenjiong (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF934B)
## 思路：
由于环数最大的是 $8$ ，有 $2$ 个环，并且这个数不大于 $10^{18}$ ，所以这个数最多只能有18位，所以如果输入的 $k$ 大于 $36$ 就直接按题意输出 $-1$ 。如果 $k\le36$ 就先判断，如果 $k$ 是偶数，就输出 $\dfrac{k}{2}$ 个 $8$ ，如果 $k$ 是奇数，就先输出 $4$ ，因为它有一个环，奇数减去一就是偶数了。

最后，代码实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k,i;
	cin>>k;
	if(k>36)
		cout<<-1;
	else
	{
		if(k%2==1)
			cout<<4;
		for(i=1;i<=k/2;i++)
			cout<<8;
	}
	return 0;
}
```
谢谢！！！

---

## 作者：Yaixy (赞：1)

# 题意及注意点

-  输入一个数 ，输出**任意一个**每个数位上的数字环之**和**等于它的数。如果不存在输出 $-1$。

- $0$ 到 $9$ 数字环的个数分别为：


| 数字 | 0  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 数字环个数 | 1 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 2 | 1 |

- 输出的数**必须小于** $10$ 的 $18$ 次方。

- 输出的数必须为**正整数**。（**温馨提醒**：$0$ 不是正整数。）

# 思路

- 先让我们来解决一下**输出的数最大**能为多少：

首先，我们可以排除 $0$ 的情况，因为它不是正整数。那么在数字 $1$ 到 $9$ 中，数字数最多的是 $8$，有 $4$ 个数字环。因此，能输出的最大数为 $4$ 乘 $9$ 即 $36$。

- 接下来，就是简单的判断与输出了

1.  **第一种情况** ：输入的数大于 $36$，直接输出 $-1$。

1. **第二种情况**：输入的数可以输出，这时候while循环不断判断奇偶并输出即可。

# 代码qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int x,n;
    cin>>x;
    if(x>36){cout<<-1;return 0;}
    while(x)
     {
         if(x%2==0){cout<<8;x-=2;}
         else {cout<<9;x-=1;}
     }
    return 0;
}
```

完结撒花qwq

---

## 作者：tZEROちゃん (赞：1)

### Sol #1

#### 分析

我们可以发现，$8$ 的“数字环”最多，所以我们一上来就全部填 $8$。要填多少次呢？显然是 $\lfloor \dfrac{n}{2} \rfloor$ 次，如果 $k$ 是奇数，我们就要在任意位置加一个 $4$ 或 $6$ 或 $9$。

既然数字要 $\le 10^{18}$，所以位数最多只有 $18 \times 2 = 36$ 位，当 $k \ge 37$ 时，可以直接输出 `-1`。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d", &n);
	if(n >= 37)
		return puts("-1"), 0;
	if(n % 2 == 0)
		for(int i=1; i<=n/2; i++)
			printf("8");
	else 
	{
	    printf("9");
		for(int i=1; i<=n/2; i++)
			printf("8");
	}
}
```

### Sol #2

可以发现，当 $k \ge 37$ 时，直接输出 `-1`，所以我们打个表就完事了（

[制表代码 & 代码](https://www.luogu.com.cn/paste/36mdt7gb)。

---

## 作者：梦理乾坤 (赞：1)

## 一道极简单的贪心

首先当$n$ $>=$ $37$就不行，因为即使全用8都要用18以上个，所以与题不服，显然无解

否则尽量用8来填，剩下的用4或6或9来填

岂不是很简单吗， hh

然后AC代码

```cpp
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n >= 37)//那么这样就不可以肯定要18以上个8但显然与题不服，所以无解
    {
        putchar('-');
        putchar('1');
        return 0;
    }

    if (n & 1)
    {
        for (int i = 1; i <= n / 2; i++)//奇数，尽量多用8最后用6或4或9来填，这里我用6
            putchar('8');
        putchar('6');
        return 0;
    }

    for (int i = 1; i <= n / 2; i++)//偶数全用8填
        putchar('8');

    return 0;//结束
}
```
求管理员过，谢谢

---

## 作者：GusyNight (赞：1)

思路其实很简单，我就不多提了线上代码
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline I read(){
    char c=getchar();
    I x=0;
    B f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long n,temp;
int main(){
    cin>>n;
    temp=n/2;
    for(int i=1;i<=temp;i++){
    	cout<<"8";
	}
    if(n%2==1)puts("6");
    return 0;
}
```
这样会WA应为，在36以上是无解的，要是你有解，快告诉我，让我大开眼界！

所以特判一下
```cpp
if(n>36){
        puts("-1");
        return 0;
    }
```
完整代码
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline I read(){
    char c=getchar();
    I x=0;
    B f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long n,temp;
int main(){
    cin>>n;
    if(n>36){
        puts("-1");
        return 0;
    }
    temp=n/2;
    for(int i=1;i<=temp;i++){
    	cout<<"8";
	}
    if(n%2==1)puts("6");
    return 0;
}
```
**这时有人要问了：**
**为什么不改成零变成这样：**
```cpp
if(n%2==0)puts("6");
```
**万一是：**

一圈呢?
=

---

## 作者：想不好名字 (赞：0)

题目分析

其实这题明显就是一道贪心题，输出的数 $<=$ $10^{18}$,换句话说，你输出的数不能超过$18$位;

由于环数最多的是$8$，有两个环，因此一定要先输出$18$。


```c
#include<iostream>
using namespace std;
int main(void)
{
	int n;
	cin>>n;
	if(n>36)
	{
		cout<<"-1";
		return 0;
	}
	while(n)
	{
		for(int i=1;i<=n/2;++i) //一个8里面有两个环
		cout<<8;
		n=n%2;
		if(n!=0)//如果8输出完了还有剩余
		cout<<6;//再随便输出一个有环的数（注意输出正整数，所以不能输出0）
		return 0;
	}
	return 0;
} 
```


---

## 作者：sinsop90 (赞：0)

由于题目只需要我们输出任意一组解, 我们只需要讨论怎么构造这个数 $n$ 即可

我们发现, 输出的数要求小于 $10 ^ {18}$ , 最多环的数为 $8$ 共两个

$2 * 18$ $=$ $36$ 因此若 $k$ 大于 $36$ 直接输出 $-1$ 即可

由于我们要使得位数尽量小, 输出的数尽量含更多的 $8$

如果 $k$ 是一个偶数, 输出 $\frac{k}{2}$ 个 $8$

如果 $k$ 是一个奇数, 输出 $\frac{k}{2}$ 个 $8$ 和一个 $4$ 即可

注意不能输出 $0$ 因为题目要求是正整数$...$

代码如下:

```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, mp[11] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};
	cin >> n;
	if(n > 36) {
		cout << -1 << endl;
		return 0;
	}
	while(1) {
		if(n >= 2) {
			printf("8");
			n -= 2;
		}
		else if(n == 1) {
			printf("4");
			n--;
		}
		else {
			break;
		}
	}
	cout << endl;
}
```


---

## 作者：LSG_waterf (赞：0)

我感觉这道题是　~~入门~~　普及-

先看数据，别看 $k$ 到 $10^{6}$ ，但是我们后输出数的不能超过 $10^{18}$，$10^{18}$ 这个数最多能表示多少个环呢？？

$10^{18}$ 有十九位，小于 $10^{18} $  ，最多的环的数字是十八位的 $18$ 个 $8$ ，也就是 $36$ 个环，所以，只要当 $k>36$ 时，我们可以直接输出 $-1$ 了．
 
#### $k=1$ 时　有数字　 $4$

#### $k=2$ 时　有数字　 $8$

#### $k=3$ 时　有数字　 $84$

#### $k=4$ 时　有数字　 $88$

~~~~~ ~~~~~~

#### $k=7$ 时　有数字　 $8884$

#### $k=8$ 时　有数字　 $8888$

#### $k=10$ 时　有数字　 $88888$
所以我就只可以用 $8$ 和 $4$ 来理解就行了．

#### 最后奉上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int k,st[110],top;//ｋ是输入的数
signed main()
{
    cin>>k;
    if(k>36) {printf("-1");return 0;}//如果当k>36，也就是说小于10＾18次方的任意一个数都不满足，直接输出－１．
    int t=k;
    while(t)//储存这个数
    {
        if(t>=2) {st[++top]=8;t-=2;}//一个８就是２个环
        else if(t==1) {st[++top]=4;t--;}//一个4就是1个环
        else if(t==0) break;
    }
    for(int i=top;i>=1;i--) printf("%lld",st[i]);
    puts("");
    return 0;
}
```


---

## 作者：Creroity (赞：0)

~~一道水题~~，以至于代码只有 13 行……

#### 这道题的思路其实很简单就是两个特判加上一个循环就好了。

首先，因为输出的数字 ans 满足 $ans \leqslant 10^{18}$ 。也就是说，最大的 ans 应该是 18 个 9，那么可能达到的最大环数就很好求了，自然是 18 个 8 的时候最大，也就是当 $k > 36$ 时无法达到。（注意， $10^{18}$ 其实是 1 后面跟 18 个 0 ，也就是 19 位数，所以最大的是 18 个 8 ）

接着我们只需要全部输出 8 就可以了，输出 $k \div 2$ 个 8 ，就刚好满足题意。

而对于奇数的 k 只需要在输出完 8 之后再多输出一个 6 即可，因为满足情况的最大奇数是 35 ，末位再加一个 6 不会超过 $10^{18}$ 。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int main(){
	cin>>k;//输入 
	if(k>36){//特判 
		cout<<-1;
		return 0;//直接结束 
	}
	for(int i=1;i<=k/2;i++)cout<<8;//输出 8 
	if(k%2==1)cout<<6;//奇数特判（注：输出其他的数也可以，只是蒟蒻我比较喜欢6而已） 
	return 0;//结束 
}
```
这么精简的代码，~~不给个赞再走吗？~~

---

## 作者：happybob (赞：0)

这个题目感觉和贪心关系不是很大，思路也很好理解的哦！

其实n >= 37就会无解

不然n为偶数全输出8

不然输出n / 2个8和一个9

代码，452ms：

```cpp
#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    if(n >= 37)
    {
        cout << "-1\n";
        return 0;
    }
    else
    {
        long long c = n / 2;
        if(c * 2 == n)
        {
            for(int i = 1; i <= c; i++)
            {
                cout << "8";
            }
            cout << endl;
        }
        else
        {
            for(int i = 1; i <= c; i++)
            {
                cout << "8";
            }
            cout << "9\n";
        }
    }
    return 0;
}
```


---

## 作者：2132B (赞：0)

### 思路

这道题的意思很明了，我就不多说了

我们知道这道题只要随便输出一个数字环数量和为$k$的数就可以了

$8$的数字环最多，所以我们为了使数字本身最小，就要使每个数字的环数最大

所以，我们就用一个贪心

### 具体实现

对于输入的数$k$

另：因为要小于$10^{18}$所以$k$必须小于$36$

有两种情况：

$1.k$除以$2$余$0$，则输出$k/2$个$8$

$2.k$除以$2$余$1$，则输出$(k-1)/2$个$8$，再加上一个数字环数为$1$的数字

### $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
int main()
{
	cin>>k;
	if(k>36)
		cout<<-1;
	else
	{
		while(k>=2)
			cout<<8,k-=2;//当k%2==0时，输出k/2个8 
		if(k==1)
			cout<<4;//当k%2==1时 
	}
	return 0;
}
```


---

## 作者：李至擎 (赞：0)

求管理员手下留情(╥﹏╥...)！！！

[点我看题](https://www.luogu.com.cn/problem/CF934B)

由于只要输出任意一个每个数位上的数字环之和等于 $k$ 的数字就行了，所以我们只用任意找到一个符合条件的数。
这时候，我们就可以分类讨论——假设需要用 $k$ 个数字环：

+ $1.$ 偶数：

	很简单，只要用 $\frac{ k }{2}$ 个 $8$ 拼在一起就可以了；

- $2.$ 奇数：

	也不难，只要先转化成偶数的情况（用 $4$ ， $6$ 或 $9$ 拼一个），再用 $\frac{ k-1 }{2}$ 个 $8$ 拼在一起就可以了。
    
    注意：不能使用 $0$ 来凑数。因为题目输出要求是正整数，而如果用 $0$ 的话再 $k=1$ 时会输出 $0$ ，所以凑数不能用 $0$ （当然，如果你非要用，也可以，只不过要加特判）。
    
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;//k的意思如题
int main()
{
	cin>>k;//输入
	if(k>36)//超过数据范围，不行
	{
		cout<<-1;
		return 0;//结束程序
	}
	if(k%2==1)//如果是奇数，还要多输出一个6（转化）
	{
		cout<<6;
	}
	for(int i=1;i<=k/2;i++)//因为cpp自带向下取整，所以直接输出k/2个8就行了
	{
		cout<<8;
	}
	return 0;//结束程序
}
```

修改记录：

$2020.8.10$ ：修改了一部分 $\LaTeX$ ，增加了注释并精简了一部分语言。

$2020.12.19$ ：增加了一部分 $\LaTeX$ ，增加了注释并精简了一部分语言。

---

## 作者：TRZ_2007 (赞：0)

# Solution  
这是一道贪心题，其实可以评红的……  
我们要求一个有 $n$ 个圈的数字，如果 $n$ 是偶数时，全部都是 8 就行了，不然的话 6 有一个圈，可以满足奇数。  
因为我们要的数字小于$10^{18}$，所以就算是全都是 8 ，也只能满足 36 个，所以当 $n \le 36$ 时，数字才是有效的。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	scanf("%d",&n);
	if(n > 36) { //无解
		puts("-1");
		return 0;
	}else {
		if(n % 2) {//奇数
			for(int i = 1;i <= n / 2;i++) {//先来一波 8
				printf("8");
			}
			printf("6\n");//再来一个 6
		}else {//偶数
			for(int i = 1;i <= n / 2;i++) {//全都是 8 
				printf("8");
			}
			puts("");
		}
	}
}
```

---

