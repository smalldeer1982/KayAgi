# Maximum splitting

## 题目描述

You are given several queries. In the $ i $ -th query you are given a single positive integer $ n_{i} $ . You are to represent $ n_{i} $ as a sum of maximum possible number of composite summands and print this maximum number, or print -1, if there are no such splittings.

An integer greater than $ 1 $ is composite, if it is not prime, i.e. if it has positive divisors not equal to $ 1 $ and the integer itself.

## 说明/提示

 $ 12=4+4+4=4+8=6+6=12 $ , but the first splitting has the maximum possible number of summands.

 $ 8=4+4 $ , $ 6 $ can't be split into several composite summands.

 $ 1,2,3 $ are less than any composite number, so they do not have valid splittings.

## 样例 #1

### 输入

```
1
12
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
6
8
```

### 输出

```
1
2
```

## 样例 #3

### 输入

```
3
1
2
3
```

### 输出

```
-1
-1
-1
```

# 题解

## 作者：_Qer (赞：4)

贪心地想，如果我们要把一个数尽可能多的分成若干个合数，那么每个数肯定是越小越好，显然最小的合数是$4$，所以我们可以尽量把数分成几个$4$相加。  
但是这样的话数不一定都能分成若干个$4$的和，减去一些$4$以后剩下的可能为$0,1,2,3$，然后来分类讨论  

先来看$0$和$2$
- 0  
显然已经分完了，由于每一个数都是最小，所以分的数最多，有$n/4$个


- 2  
我们发现$6$是第二小的合数，所以可以把最后分的一个$4$和剩下的$2$凑成$6$，也是最多的分法，有$\left\lfloor{n/4}\right\rfloor$个

----

然后看$1$和$3$  
因为每次减去的都是$4$，所以原来的$n$一定是一个奇数，无论怎么分都一定会有至少一个奇数的合数，然后我们发现最小的奇数合数是$9$，所以我们把这个$9$分出来，$n$就变成了偶数，也就可以按照上面$0$和$2$的做法来搞了

----

最后，还要排除掉几个不能分解的特殊情况。首先$1,2,3$这几个显然不行，然后就是$5,7,11$这几个数，自己手算一下就能发现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define uLL unsigned long long
namespace io {//这里快读，跳过即可
  template <typename T> inline void read(T &x) {
    bool flag = false;  char c = getchar();
    while ((c < '0' || c > '9') && c != '-')  c = getchar();
    c == '-' ? flag = true, x = 0 : x = c - '0';
    c = getchar();
    while (c >= '0' && c <= '9')  x = (x << 3) + (x << 1) + c - '0', c = getchar();
    if (flag)  x = -x;
  }
  template <typename T> inline void write(T x) {
    char st[10010];
    int cnt = 0;
    if (x < 0)  x = -x, putchar('-');
    if (x == 0)  putchar('0');
    while (x) { st[++cnt] = x % 10 + 48;  x /= 10; }
    while (cnt) { putchar(st[cnt--]); }
  }
}
using namespace io;
int T, n, ans;
int main() {
    read(T);
    while (T--) {
        read(n);
        ans = 0;
        if (n <= 3 || n == 5 || n == 7 || n == 11) {//先去掉特殊情况
            write(-1); putchar('\n');
            continue;
        }
        if (n & 1) {//奇数先去掉9变成偶数算
            ++ans, n -= 9;
        }
        ans += n / 4;
        write(ans); putchar('\n');
    }
    return 0;
}
```

---

## 作者：Amor_Hucsy (赞：2)

好了，本蒟蒻又来写题解啦！

~~这题挺水的，感觉算不上绿题~~

基本思路很简单，就是：

最小的合数是4 对4取余

如果余数是0， 直接 n/4

如果余数是1， 1可以和两个4 搭配形成一个 9  消耗一个 

如果余数是2， 2可以和一个4 搭配形成一个 6  不消耗 

如果余数是3， 3可以和三个4 搭配形成两个 6,9  消耗一个 

这个题不能用素数来判断因为 19数素数 但是 可以拆成 4,6,9

只能特判 

好了，废话不多说，直接放代码：

```
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <stack>
// 一大堆头文件
#define ll long long //将后面的值全部为long long
#define inf 0x3f3f3f3f 
using namespace std; //不写这个，不能识别cin和cout
//最小的合数是4 对4取余
//如果余数是0 直接 n/4
//如果余数是1 1可以和两个4 搭配形成一个 9  消耗一个 
//如果余数是2 2可以和一个4 搭配形成一个 6  不消耗 
//如果余数是3 3可以和三个4 搭配形成两个 6,9  消耗一个 
//这个题不能用素数来判断因为 19数素数 但是 可以拆成 4,6,9
//只能特判 
int main()
{
	int t; //定义t
	ll n;  //定义n
	cin>>t; //输入t
	while(t--) //核心代码，也就是特判
	{
		cin>>n;//先输入n
		if(n==1||n==2||n==3||n==5||n==7||n==11)	cout<<"-1"<<endl; //因为1、2、3、5、7、11不能拆成合数
		else if(n%4==0) //如果可以被4整除
		{
			cout<<n/4<<endl; //输出n/4的商
		 } else if(n%4==1) //如果除4后余数为1
		 {
		 	cout<<n/4-1<<endl;//输出n/4的商后还要再-1；
		 }else if(n%4==2) //如果除4后余数为2
		 {
		 	cout<<n/4<<endl;//也是输出n/4，为什么呢？因为是4的倍数的数一定是2的倍数
		 }else if(n%4==3) //如果除4后余数为3
		 {
		 	cout<<n/4-1<<endl;//和余数为1的一样
		 }
	}	
	return 0;//养成一个好习惯
}

```
代码就是这些了，如果觉得好，可以点赞哦~


---

## 作者：Super_Cube (赞：1)

# 题目大意：

给你 $q$ 次询问，每次询问一个整数 $n$，你需要回答这个整数最多可以被分成几个合数相加的和，如果分不出合数输出 $-1$。

---

# 思路：

为了分出更多的合数，我们可以使用贪心策略：一直分最小的合数 $4$。

因为 $4$ 是最小的合数，所以分出来的数量一定能够达到最大。

不过一直分合数 $4$ 最后会出现四种情况，分类讨论下：

1. $n \bmod 4 = 0$

这种情况说明直接分得干干净净，答案就是 $n / 4$。

2. $n \bmod 4 = 1$

这种情况说明分到最后剩下了个 $1$，只好去除两个 $4$，使 $1$ 变成合数 $9$。答案就是 $n / 4 - 1$。

3. $n \bmod 4 = 2$

这种情况说明分到最后剩下了个 $2$，可以随便让一个 $4$ 与这个 $2$ 匹配，变成合数 $6$，答案还是 $n / 4$。

4. $n \bmod 4 = 3$

这种情况说明分到最后剩下了个 $3$，需要拿出三个 $4$ 与剩下的 $3$ 配对，然后将其转化为合数 $6$ 和合数 $9$，答案是 $n / 4 - 1$。


总结下规律：偶数答案就是 $n /4$，奇数答案就是 $n / 4 - 1$。

至于需要输出 $-1$ 的数，需要自行特判下，详情见代码。

---

# Code：

```cpp
#include<cstdio>
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		if(n<4||n==5||n==7||n==11){//这里就是要特判的数，分别是：1 2 3 5 7 11
			puts("-1");continue;
		}printf("%d\n",(n>>2)-(n&1));
		//(n>>2)等价于(n/4),(n&1)等价于(n%2)
	}
	return 0;
}
```

---

## 作者：happybob (赞：1)

好久没A绿题了，纪念一下，发个题解

众所周知，最小合数为4，拆解n只需要用x个4就好了

但如果n % 4 != 0怎么办，自己去分析，这里只说一下结论

```cpp
n % 4 == 0 || n % 4 == 2

那答案就是n / 4，n % 4 == 2可以将最后的4和2合并，6是个合数

n % 4 == 1 || n % 4 == 3

答案：

n / 4 - 1
```

代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++)
    {
        int n;
        cin >> n;
        if(n == 1 || n == 2 || n == 3 || n == 5 || n == 7 || n == 11)
        {
            cout << "-1\r";
        }
        else
        {
            if(n % 4 == 0 || n % 4 == 2)
            {
                cout << n / 4 << endl;
                continue;
            }
            else if(n % 4 == 1 || n % 4 == 3)
            {
                cout << n / 4 - 1 << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：Insouciant21 (赞：1)

给出一个正整数 $n(1\leq n\leq10^9)$ ，求最多能分解成几个合数

最小的合数是 $4$ ，所以对于 $n$ 要尽可能的分出最多的 $4$

对于 $p=n \bmod 4$ 可能得到 $4$ 种值 $0,1,2,3$

当 $p=0$ 时，这个数为 $4$ 的倍数，此时 $\dfrac{n}{4}$ 为最多的个数

而 $p=2$ 时，这个数为 $2$ 的倍数，可将最后一个 $4$ 加上 $p$ 得到 $6$，$6$也是合数，故 $\left\lfloor\dfrac{n}{4}\right\rfloor$ 也为此时可分解的最多合数个数

当 $p=1$ 或 $p=3$ 时， $n$ 为奇数，最小的奇合数为 $9$，即 $n$ 如果可以进行分解必有 $n-9>=4$ 或是 $n-9=0$

最后还要注意小于 $4$ 的数无法分解

AC代码如下
``` cpp
#include <bits/stdc++.h>

using namespace std;

int q, n;

int main() {
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &n);
        int ans = 0;
        if (n % 2 != 0)
            n -= 9, ans = 1;
        ans += n / 4;
        if (n < 4 && n != 0)
            ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：业余门槛 (赞：1)

这里介绍一种O(1)的做法

由于要最大，所以说每一次减去4就行了（奇数的话先减一次9）

最后剩下0或2（2的话最后一次为6）可以，否则不可以


```cpp
#include<iostream>                           
using namespace std;      
inline void solve(){                          //这是一个O(1)的解法 
	int n;
	cin>>n;
	int cnt=0;
	if(n%2){
		if(n<9){
			cout<<-1<<endl;
			return;
		}
		n-=9;
		cnt=1;
	}
	if(n>0 and n<4){                                   //一定要放在后面！！！（11） 
		cout<<-1<<endl;
		return;
	}
	cnt+=(int)(n/4);
	if(n%4==1 or n%4==3) cout<<-1<<endl;
	else cout<<cnt<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：seanlsy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF870C)

**思路**

可以贪心地想，为了凑出更多的合数，每次应该选更小的合数。

根据小学就知道的知识，$4$ 是最小的合数，所以我们可以根据模 $4$ 的余数进行分类讨论。

$1.n \equiv 0\pmod{4}$

一直取 $4$ 即可，答案为 $\dfrac{4}{n}$。

$2.n \equiv 1\pmod{4}$

不难发现可以先减去 $9$，答案为 $\dfrac{n-9}{4}+1$

$3.n \equiv 2\pmod{4}$

不难发现可以先减去 $6$，答案为 $\dfrac{n-6}{4}+1$

$4.n \equiv 3\pmod{4}$

不难发现可以先减去 $15$，答案为 $\dfrac{n-15}{4}+1$

但是其实 $15$ 可以拆成 $6+9$，所以其实答案为 $\dfrac{n-15}{4}+2$

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?x:-x;
}
int t,n;
int main(){
	t=read();
	while(t--){
		n=read();
		if(!(n&3)) printf("%d\n",n<4?-1:(n>>2));
		else if((n&3)==1) printf("%d\n",n<9?-1:((n-9)>>2)+1);
		else if((n&3)==2) printf("%d\n",n<6?-1:((n-6)>>2)+1);
		else printf("%d\n",n<15?-1:((n-15)>>2)+2);
     		//注意特判无解的情况
	}
	return 0;
}
```


---

## 作者：Nygglatho (赞：0)

贪心。

我们发现，最小合数是 $4$，所以考虑拆成多个 $4$ 相加的结果。

但是这样可能会有余数，例如，$22 \bmod 4 = 2$。

这样我们可以分类讨论：

- 余数为 $1$：考虑拼到 $4$ 上，由于 $4 + 1 = 5$，$5$ 是质数，而我们再拼一次，那么就拼出了 $9$，而 $9$ 是合数，损失 $1$ 个合数。
- 余数为 $2$：由于 $4 + 2 = 6$，所以直接拼到 $6$ 上，不会损失。
- 余数为 $3$：由于 $4 \times 3 + 3 = 15$，需要损失 $2$ 个合数，不划算。考虑将 $3$ 拆成 $1$ 和 $2$，这样就转换为上面做法了。损失 $1$ 个合数。

接下来是无解情况：

- $0, 1, 2, 3$：由于最小合数为 $4$，显然不可能。
- $5$：$5$ 以下的合数只有 $4$，其中一个为合数的拆分只有 $4 + 1 = 5$，$1$ 不是合数，故不可能。
- $7$：$7$ 可以拆分成 $4 + 3$ 和 $6 + 1$。$3$ 和 $1$ 都不是合数，故不可能。
- $11$：$11$ 可以拆分成：$4 + 4 + 3, 6 + 4 + 1, 6 + 5, 9 + 2$。$3, 1, 5, 2$ 不是合数，故不可能。

代码：
```c
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    scanf ("%d", &T);
    while (T--) {
        int x;
        scanf ("%d", &x);
        if (x == 0 || x == 1 || x == 2 || x == 3 || x == 5 || x == 7 || x == 11) puts("-1");
        else if ((x % 4) % 2 == 1) printf ("%d\n", x / 4 - 1);
        else printf ("%d\n", x / 4);
    }
}
```

---

