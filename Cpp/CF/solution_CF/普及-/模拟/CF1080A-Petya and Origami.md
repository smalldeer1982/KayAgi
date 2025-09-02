# Petya and Origami

## 题目描述

Petya 将要举行一场派对，她要发送大量的邀请函给朋友们。

每一张邀请函需要耗费 2 张红色纸，5 张绿色纸和 8 张蓝色纸。

然而，商店里卖纸是一堆一堆卖的，每一堆有 $k$ 张且只含有红，绿，蓝三种颜色之一的纸，Petya 可以选择买哪种颜色的一堆纸。

现在 Petya 要给 $n$ 名朋友发送邀请函，请问她至少要到商店买几堆纸。

## 说明/提示

$1 \leq n,k \leq 10^8$

## 样例 #1

### 输入

```
3 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
15 6
```

### 输出

```
38
```

# 题解

## 作者：封禁用户 (赞：4)

真不懂为什么要弄得那么麻烦，不就是一个向上取整嘛  
直接上代码，反正都~~看得懂~~
```cpp
#include <iostream>
using namespace std;
int n,k,r,g,b,ans,t; //r:红色,g:绿色,b:蓝色
int main(){
	cin>>n>>k;
	r=n*2;g=n*5;b=n*8;//统计每种颜色所需张数
    
	t=r/k;
	if(r%k!=0)t++;
	ans+=t;			//红色需要几本
    
	t=g/k;
	if(g%k!=0)t++;
	ans+=t;			//绿色需要几本
    
	t=b/k;
	if(b%k!=0)t++;
	ans+=t;			//蓝色需要几本
    
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Chtholly_L (赞：0)

### 题意：

一张邀请函要耗费 $2$ 张红纸， $5$ 张绿纸， $8$ 张蓝纸。

你需要去商店买纸，只是按照堆来卖的，每堆纸有 $k$ 张，问一共需要买几堆纸。

---

### 分析：

其实这题就相当于是小学数学，用人脑来算非常简单。

这道题用到的是进一法（和去尾法相对），即在算出最后结果时，不足一的要当成一来算，比如一群人坐大巴车，一共 $41$ 个人，每辆大巴车可以坐10人，那么必须要租 $5$ 辆大巴车（你不能把剩下的一个人丢掉不管吧！！！）。

其实这道题和上面的例子一样，你需要 $41$ 张纸，每堆纸有 $10$ 张，你必须买 $5$ 堆纸。 C++ 中自带向上取整的函数，函数名为 ceil ，使用它时应注意，它只能对浮点数进行取整。

---

知道了这些就来代码实现吧！

```cpp
#include<iostream>
#include<cmath>  //ceil 的函数库
using namespace std;
int main()
{
	double n,k;
	cin>>n>>k;
	double red=2*n,green=5*n,blue=8*n;  //变量名有点丑，不好意思
	int dui=ceil(red/k)+ceil(green/k)+ceil(blue/k);  //如题
	cout<<dui;
	return 0;
}
```


---

## 作者：Nt_Tsumiki (赞：0)

### 题意
一个人要给$n$ 个朋友发邀请函，每张邀请函要2张红纸，5张绿纸，8张蓝纸，现商店中出售这这些纸张，但只能按堆买，一堆$k$ 张纸（任意颜色），求一共要多少堆纸。
### 做法
因为纸是按堆买，所以要向上取整，就需要用到c++的向上取整函数`ceil`(记得写上头文件)，然后就去算红、绿、蓝纸每种所需的堆数（要为double类型），即为$ \lceil n * a / k \rceil $ （a为红、绿、蓝纸每封信所需张数），代码为：`ans += ceil(a[i] * n / k);` 
将堆数加到总堆数中，最后输出（坑点：$n$ 和$k$ 也要为double类型，因为`ceil`所进行的取整操作只能作用于小数），上代码。
### Code
```cpp
#include <iostream>
#include <cmath>//ceil所需函数

using namespace std;
int a[4] = {0 ,2 ,5 ,8}, ans;//一封信所需的红纸，绿纸，蓝纸张数和总堆数
double n, k;//要定义成double

int main() {
	cin >> n >> k;
	for(int i = 1; i <= 3; i++) {
		ans += ceil(a[i] * n / k);//将分别所需堆数加入总堆数
	}
	cout << ans;//输出
	return 0;//完美结束
}
```
### 总结
这道题主要就是考察对于`ceil`的运用，如果不为小数，就会直接保留原数。

---

## 作者：Ptilopsis_w (赞：0)

题目传送门[CF1080A](https://www.luogu.com.cn/problem/CF1080A)

这道题题目很简单，就是一个向上取整而已，不多赘述

这里我看其他题解都没写，给出一种比较简单的整数向上取整的办法，例如 $ \lceil a/b \rceil $ 可以直接写成`(a+b-1)/b`，当 $a$ 能整除 $b$ 时，结果就是`a/b`，若不能整除，因为是`a+b-1`，所以除 $b$ 的结果就是 `a/b+1`，就可以达到向上取整的目的了

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	int s = (n*2+k-1)/k + (n*5+k-1)/k + (n*8+k-1)/k;
	printf("%d", s);
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
小 P 想给 $n$ 位朋友各发一张邀请函，每张邀请函需要耗费 $2$ 张红色纸，$5$ 张绿色纸和 $8$ 张蓝色纸。商店里面的纸是一堆一堆卖的，每堆里面有 $k$ 张只含有红、绿、蓝三种颜色中的一个颜色的纸。求小 P 至少要买多少堆。

**数据范围：$1\leqslant n,k\leqslant 10^8$。**
## Solution
直接看每种颜色需要多少堆，由于只能一堆一堆地买，所以只能多买，不能少买，因此答案就很显而易见了，分别是 $\left\lceil\dfrac{2n}{k}\right\rceil,\left\lceil\dfrac{5n}{k}\right\rceil$ 和 $\left\lceil\dfrac{8n}{k}\right\rceil$。
## Code
```cpp
int n, k;

int main() {
	getint(n), getint(k);
	int ans = ceil(n * 2.0 / k) + ceil(n * 5.0 / k) + ceil(n * 8.0 / k);
	writeint(ans);
	return 0;
}
```

---

## 作者：Ouaoan (赞：0)

题目：[Petya and Origami](https://www.luogu.org/problemnew/show/CF1080A)

---

思路：

膜你题，就是输出x/k+y/k+z/k就可以了。

要注意向上取整。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 100000000
#define read(x) scanf("%d",&x)

int n,k;

int main() {
	read(n),read(k);
	int x=n*2,y=n*5,z=n*8;
	
	printf("%d",x/k+(x%k!=0)+y/k+(y%k!=0)+z/k+(z%k!=0));
	
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

根据题目条件求出每种颜色需要多少个，分别除k向上取整相加就是答案
```
#include <bits/stdc++.h>
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const double PI = acos(-1.0);
const int N = 1e5 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    int read()
    {
        register int num = 0;
        register char ch;
        register bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    void write(register int x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};


int main()
{
    register int n = fast_IO::read(), k = fast_IO::read();
    fast_IO::write((n * 2 + k - 1) / k + (n * 5 + k - 1) / k + (n * 8 + k - 1) / k);
    return 0;
}
```


---

## 作者：little_sun (赞：0)

# 题解 CF1080A 【Petya and Origami】

## [安利博客](https://www.cnblogs.com/little-sun0331/p/10014591.html)

这道题其实要我们求的就是
$$\lceil 2*n/k \rceil + \lceil 5*n/k \rceil + \lceil 2*n/k \rceil$$
然后就做完了
```cpp
# include <bits/stdc++.h>

# define ll long long

int main()
{
    ll n, k;
    scanf("%lld%lld", &n, &k);
    ll ans = ((2 * n) / k) + ((5 * n) / k) + ((8 * n) / k) + bool((2 * n) % k != 0) + bool((5 * n) % k != 0) + bool((8 * n) % k != 0);
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/10014521.html]()

题意：Petya要发出n张邀请函，每张请函需要2张红纸，5张绿纸，8张蓝纸。现在商店里有一些不同颜色的笔记本，每本中有k张颜色相同的纸，求最少要买几本笔记本。

这题就是一道模拟题，算出每种纸的数量，答案加上数量除以k，对于每张颜色如果还有余数，答案加一。

 

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
int lowbit(int x){ return x & -x; }
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p; } return x; }
//head by DYH

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    int a = n * 2, b = n * 5, c = n * 8;
    int ans = a / k + b / k + c / k;
    if(a % k) ans++;
    if(b % k) ans++;
    if(c % k) ans++;
    printf("%d\n", ans);
    return 0;
}
```
Problem-A

---

