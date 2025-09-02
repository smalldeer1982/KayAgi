# [ABC109C] Skip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc109/tasks/abc109_c

数直線上に $ N $ 個の都市があり、$ i $ 番目の都市は座標 $ x_i $ にあります。

あなたの目的は、これら全ての都市を $ 1 $ 度以上訪れることです。

あなたは、はじめに正整数 $ D $ を設定します。

その後、あなたは座標 $ X $ から出発し、以下の移動 $ 1 $、移動 $ 2 $ を好きなだけ行います。

- 移動 $ 1 $: 座標 $ y $ から座標 $ y\ +\ D $ に移動する
- 移動 $ 2 $: 座標 $ y $ から座標 $ y\ -\ D $ に移動する

全ての都市を $ 1 $ 度以上訪れることのできる $ D $ の最大値を求めてください。

ここで、都市を訪れるとは、その都市のある座標に移動することです。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ X\ \leq\ 10^9 $
- $ 1\ \leq\ x_i\ \leq\ 10^9 $
- $ x_i $ はすべて異なる
- $ x_1,\ x_2,\ ...,\ x_N\ \neq\ X $

### Sample Explanation 1

$ D\ =\ 2 $ と設定すれば次のように移動を行うことですべての都市を訪れることができ、これが最大です。 - 移動 $ 2 $ を行い、座標 $ 1 $ に移動する - 移動 $ 1 $ を行い、座標 $ 3 $ に移動する - 移動 $ 1 $ を行い、座標 $ 5 $ に移動する - 移動 $ 1 $ を行い、座標 $ 7 $ に移動する - 移動 $ 1 $ を行い、座標 $ 9 $ に移動する - 移動 $ 1 $ を行い、座標 $ 11 $ に移動する

## 样例 #1

### 输入

```
3 3
1 7 11```

### 输出

```
2```

## 样例 #2

### 输入

```
3 81
33 105 57```

### 输出

```
24```

## 样例 #3

### 输入

```
1 1
1000000000```

### 输出

```
999999999```

# 题解

## 作者：亦枫 (赞：3)

## Solution

题意：给你一个初始位置 $ X $ ,再给你 $ N $ 个点的位置。你开始在初始位置，每次可以向左或向右移动 $ D $ 个单位，问你若要此人遍历全部城市，  $ D $ 值最大可为多少？

看到这道题，我第一反应就是二分答案，然后去写一个检查答案是否满足要求。

但是，每个 $ D $ 对于现在这个初始位置 $ X $ 来说，能到达的点是唯一的。

**所以对于每个点，让它的位置减去初始位置的坐标，在对所有点预处理后的值，求最大公因数即可。**

但是要注意，求出的可能是一个负数，所以要取绝对值。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x;
ll a[100005];
int main(){
	scanf("%d %d",&n,&x);
	for(ll i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]=a[i]-x;//减去初始位置，预处理
	}
	ll ans=a[1];
	for(ll i=2;i<=n;i++){
		ans=__gcd(ans,a[i]);//C++自带的求最大公因数的函数
	}
	printf("%d\n",abs(ans));//记得取绝对值
}
```


---

## 作者：zct_sky (赞：2)

~~又是一道大水题~~
### 思路
因为这个人每次只可以可以向左或向右 $D$ 个单位，所以 $D$ 一定能被他和每座城市之间的距离整除，因为如果有一座城市与他的距离不是 $D$ 的倍数，则他就不能通过向左或向右 $D$ 个单位来到达那座城市，就能得出 $D=\gcd (P_1-X,P_2-X,P_3-X,...,P_N-X)$，再输出 $D$ 即可。
### Code:
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;   
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}      
inline void write(int x){//快输 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
} 
int gcd(int a,int b){
	if(a%b) return gcd(b,a%b);
	return b;
}        
int n,x,a[100010],ans;
int main(){
	n=read(),x=read();
	for(int i=0;i<n;i++)a[i]=read()-x;
	ans=a[0];
	for(int i=1;i<n;i++)ans=gcd(ans,a[i]); 
	write(abs(ans));
	return 0;
}

```


---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4255)

# 思路

因为这个人每次只可以可以向左或向右 D 个单位，所以 D 必须整除他和每座城市的距离，才能保证这个人可以到达这座城市。于是我们就用一个数组保存这个人到每座城市的距离，然后用 c++ 的自带函数 __gcd 求最大公因数就行了。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,x,a[10000005],d[10000005],ans;
  int main(){
      cin>>n>>x;
      for(int i=1;i<=n;i++){
          cin>>a[i];
          d[i]=abs(a[i]-x);//保存这个人到每座城市的距离，因为可能是负数，所以要求绝对值
      }
      ans=d[1];
      for(int i=2;i<=n;i++){
          ans=__gcd(ans,d[i]);//求这些距离的最大公因数
      }
      cout<<ans;
      return 0;
  }
```

---

## 作者：happybob (赞：1)

每座城市 $\large p_i$ 距离起点位置为 $ \lvert p_i-x \lvert$，$ d$ 满足题意时当且仅当 $ d \,\,|\,\, |p_i-x|(i=1,2,3,……,n)$。若要 $ d$ 尽量大，则是求 $ \gcd(|p_1-x|,|p_2-x|,……,|p_n-x|)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int p[N];

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

signed main()
{
	int n, x, gcdx = 1;
	scanf("%lld %lld %lld", &n, &x, &p[1]);
	p[1] -= x;
	gcdx = p[1];
	for (int i = 2; i <= n; i++)
	{
		scanf("%lld", &p[i]);
		p[i] -= x;
		gcdx = gcd(gcdx, p[i]); 
	}
	printf("%lld\n", abs(gcdx));
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

我讲一下这个题目大致的思路。

首先，对于数轴上两个坐标分别为 $x$ 和 $y$ 的点，因为向左和向右都没有问题，如果每次只移动 $D$ 的话，这两个点能够互相到达的充分必要条件是

$\exists k \in \mathbf{Z}$ 使得 $y=x+kD$

所以 $y-x=kD$，即 $D$ 为 $y-x$ 的约数。

所以，我们只要求出 $\gcd(P_1-X,P_2-X,\cdots,P_N-X)$ 
 即可。
 
 这时，我们只需一个个读入数据，并用辗转相除法求最大公约数，输出即可，实现也较为简单，甚至不用数组，~~但我为了偷懒还是用了~~。大家可以写一下不用数组的方法，一定要快很多。
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], X;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	cin >> n >> X;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	int val = 0;
	for (register int i = 1; i <= n; ++i) {
		if (val == 0) val = abs(a[i] - X);
		else val = gcd(val, abs(a[i] - X));
	}
	cout << val;
}
```

---

## 作者：REAL_曼巴 (赞：1)


我们先设要到达的地方为 $C$ 。

推到：从现在的位置到 $C$ 肯定是答案 $D$ 的倍数。

结论：从现在的位置到前面或后面的 $C$ ，一定是固定的点。

方法：求现在的位置到任意一点间的距离的最大公约数，再遍历取答案。

注：求距离用到的减法会出现负数，记得要取下绝对值！



这是求最大公因数的辗转相除法

```cpp
inline int gcd(int a,int b){
	if(b==0) return a;
	else return gcd(b,a%b);
}
```

这是求绝对值的函数

```cpp
abs(n)//这是求n的绝对值，要加cmath库
```

我认为说的够清楚，读者可带着我给的两个函数完成余下部分。


---

## 作者：jxbe6666 (赞：0)

再讲正题之前，我想先吹一波 STL，感谢它为我们带来了 __gcd() 这个巨 NB 的函数
## 思路
因为这个人每次只可以可以向左或向右 ans 个单位，所以 ans 一定能被他和每座城市之间的距离整除，因为如果有一座城市与他的距离不是 ans 的倍数，则他就不能通过向左或向右 ans 个单位来到达那座城市，就能得出 $ans=\gcd (P_1-X,P_2-X,P_3-X,...,P_N-X)$ 的结论，最后输出 ans 即可，注意 ans 有可能是负数，记得取绝对值。



------------

Code:
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const int N = 1e5 + 5;
int a[N], n, m, ans;
inline int read()
{ // 快读
    int number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(int x)
{ // 快输
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read() - m;// 读入时就减去m
    }
    ans = a[1];
    for (int i = 2; i <= n; i++)
    {
        ans = __gcd(ans, abs(a[i]));// STL YYDS
    }
    write(abs(ans));
    I AK IOI
}

```


---

## 作者：Black_Porridge (赞：0)

### 题目大意：

已知有 $N$ 个城市，每个城市的坐标互不相同。有一初始位置 $x$ , 每次只能向左或向右移动 $k$ 个单位。给出城市坐标和初始位置 $x$ ，求能使得最终到达每个城市 的 $k$ 的最大值是多少。



------------

### 解题思路：

如果我们要想移动到某个城市，那么当前点到该城市的距离必然是 $k$ 的倍数，否则我们就无法到达，所以我们只需要使得 $k$ 是任意两个坐标距离最近的城市之间的距离即可。而 $k$ 要求最大，则我们每次求一下当前两点之间的距离与之前的 $k$ 的 $gcd$ 即可。



------------
### 代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;

int n, ans;

int a[N];

int gcd(int x, int y)
{
    if(!y)
        return x;
    return gcd(y, x % y);
}

int main()
{
    cin >> n >> a[0];
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a, a + n + 1);
    ans = a[1] - a[0];//注意此处 ans要初始化 
    for(int i = 2; i <= n; i++)
        ans = gcd(ans, a[i] - a[i - 1]);
    cout << ans << endl;
    return 0;
}
```

---

