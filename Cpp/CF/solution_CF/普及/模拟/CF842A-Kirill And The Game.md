# Kirill And The Game

## 题目描述

Kirill plays a new computer game. He came to the potion store where he can buy any potion. Each potion is characterized by two integers — amount of experience and cost. The efficiency of a potion is the ratio of the amount of experience to the cost. Efficiency may be a non-integer number.

For each two integer numbers $ a $ and $ b $ such that $ l<=a<=r $ and $ x<=b<=y $ there is a potion with experience $ a $ and cost $ b $ in the store (that is, there are $ (r-l+1)·(y-x+1) $ potions).

Kirill wants to buy a potion which has efficiency $ k $ . Will he be able to do this?

## 样例 #1

### 输入

```
1 10 1 10 1
```

### 输出

```
YES```

## 样例 #2

### 输入

```
1 5 6 10 1
```

### 输出

```
NO```

# 题解

## 作者：lukelin (赞：4)

发一个O(1)题解，我们发现真正影响答案的只有四个端点，那么无非有两种情况，  
第一种：
```cpp
    (x * k >= l && x * k <= r) || (y * k >= l && y * k <= r)
```
就是一个区间的端点在另一个区间内

第二种
```cpp
    ((x * k <= l && r <= y * k))
```
就是一个区间包含另一个区间

对于第二种情况，我们发现**有一部分情况是不成立**的  
于是特判一下：
```cpp
    if ((r % k) < (l % k) || (r - l) >= k || !(l % k) || !(r % k))
        printf("YES");
    else
        printf("NO");
```

最后放一下全部代码：  
```cpp
#include <cstdio> 

long long read(){
    long long x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int main(){
    long long l = read(), r = read(), x = read(), y = read(), k = read();
    if ((x * k >= l && x * k <= r) || (y * k >= l && y * k <= r))
        printf("YES");
    else if((x * k <= l && r <= y * k)){
        if ((r % k) < (l % k) || (r - l) >= k || !(l % k) || !(r % k))
            printf("YES");
        else
            printf("NO");
    }
    else
        printf("NO");
    return 0;
}
```

---

## 作者：ztytql (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF842A)
## Description
给定正整数 $l,r,x,y,k,$ 询问是否存在正整数 $a,b,$ 满足 $l≤a≤r,x≤b≤y$ 且 $\dfrac a b=k.$
## Solution
我们先将 $\dfrac a b=k$ 化简，得到 $a =bk.$ 因为 $k$ 是已知的，所以不难想到，在 $[x,y]$ 区间内依次枚举 $b,$ 求出对应 $a$ 的值并判断是否在 $[l,r]$ 区间内，如果符合条件，那么直接输出 ```yes``` 并结束程序。如果直到区间内所有数全被枚举且仍未结束程序，说明无解，输出 ```no``` 即可。

具体详见极其简短的代码。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int l, r, x, y, k;

signed main()
{
	cin >> l >> r >> x >> y >> k;
	for (int b = x ; b <= y ; b ++) // 在区间 [x, y] 内枚举所有可能的 b
		if (b * k >= l && b * k <= r) // 判断对应的 a 是否在 [l, r] 区间内
		{
			puts("YES");
			return 0; // 直接退出程序
		}
	puts("NO"); // 循环结束且仍未退出程序，说明无解
    return 0;
}

```

---

## 作者：__Octhyccc__ (赞：0)

简要题意：给定 $5$ 个数 $l,r,x,y,k$，问有没有两个数 $a,b$ 满足 $l\le a\le r$，$x\le b\le y$，$\frac{a}{b}=k$。

考虑暴力枚举 $[x,y]$ 中的每一个数，找到 $a=b\times k$ 时直接结束程序，输出 `YES`，若是结束时还没找到，输出 `NO`。

然后看了一眼数据范围，$1\le x,y\le 10^7$，时限 $2.00s$ 的情况下循环大约可以跑 $2\times 10^8$ 次，暴力足矣。

等等，忘说了，在枚举的时候有这么一个式子：
```cpp
i*k>=l && i*k<=r
```
注意到里面有 $i\times k$。$i,k\le 10^7$，那么两个 $10^7$ 乘起来是 $10^{14}$，**因此，必须开 long long！**

奉上我的 AC 代码：

```cpp
#include<cstdio>
#define int long long//改动后的精华。
int l,r,x,y,k;
signed main(){
	scanf("%d%d%d%d%d",&l,&r,&x,&y,&k);
	for(int i=x;i<=y;i++){
		if(i*k>=l && i*k<=r){//条件判断。
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return signed(0==1);//花式结束。
}
```

---

## 作者：ttq012 (赞：0)

方法 $1$：因为 $y-x<10^7$，所以直接暴力枚举 $x\sim y$ 之间的每一个正整数 $i$，判断是否满足条件即可。

时间复杂度 $O(n)$。

方法 $2$：容易发现 $i\times k$ 满足单调性，所以直接二分即可。时间复杂度 $O(\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
  int l, r, x, y, k;
  cin >> l >> r >> x >> y >> k;
  for (int i = x; i <= y; i++)
    if (i * k >= l && i * k <= r)
    {
      cout << "YES\n";
      return 0;
    }
  cout << "NO\n";
  return 0;
}
```

---

## 作者：Milthm (赞：0)

## CF842A 题解

### 题目思路

~~这真的不是红题吗~~

容易发现，直接模拟的复杂度是 $O(y-x)$，最多也只有 $10^7$，明显可以过两秒的时限，所以直接模拟就好啦！剩下的放在注释里。

### AC代码

```cpp
#include<iostream>
#define int long long
using namespace std;
int l,r,x,y,k;
signed main(){
	cin>>l>>r>>x>>y>>k;
	for(int i=x;i<=y;++i){
		if(i*k>=l&&i*k<=r){//如果 i*k 在 [l,r] 范围内
			cout<<"YES";return 0;//输出 YES
		}
	}
	cout<<"NO";//没有就输出 NO
	return 0;
} 
```


---

## 作者：DANIEL_x_ (赞：0)

## 思路
为了让 $i \times k \in [l,r]$，则 $i \in [\frac{l}{k},\frac{r}{k}]$。

可以枚举每一个数，然后在通过上面写的区间来看是否符合条件。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;
	for(int i=a;i<=b;i++)
		if(i%e==0&&c<=i/e&&d>=i/e)
			return cout<<"YES",0;
	cout<<"NO";
	return 0;
}

```


---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF842A](https://www.luogu.com.cn/problem/CF842A)

* **【解题思路】**

题目让你寻找是否有两个数 $l\leq x\leq r,a\leq y\leq b$ 使得 $\dfrac xy=k$。

那么，我们可以枚举每一个 $x$，然后检查它是否合法：首先它要能被 $k$ 整除；其次 $\dfrac xk$ 要在 $[a,b]$ 之内。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;
	for(int i=a;i<=b;i++)
		if(i%e==0&&c<=i/e&&d>=i/e)
			return cout<<"YES",0;
	cout<<"NO";
	return 0;
}

```

---

## 作者：__Hacheylight__ (赞：0)

【题意】：

给你两个区间[L,R],[X,Y]，和一个整数k。

求是否能从第一个区间中取一个整数a，第二个区间取一个整数b，使得a/b恰好等于k。

【分析】

这个题目真的是个大水题，所以也分析不了多少。。o(╥﹏╥)o

问题可以转化成为有没有一个i∈x到y，i*k在l和r之间

于是就可轻轻松松过这个题了

还有就是新手要注意i*k可能会爆int，要用long long

【代码】：

一年前有Pascal版，给P党发福利了！

当然也有C++的

```
var i:longint;
       l,r,x,y,k:int64;
begin
     readln(l,r,x,y,k);
     for i:=x to y do
     if (i*k>=l) and (i*k<=r) then
   begin
     write('YES');
     halt;
   end;
   write('NO');
end.
```

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

ll l, r, x, y, k ;

signed main(){
	scanf("%lld%lld%lld%lld%lld", &l, &r, &x, &y, &k) ;
	for (ll i = x; i <= y; i++)
	if (i * k >= l && i * k <= r) PRINT("YES") ;
	PRINT("NO") ;
}

/*
写代码时请注意：
	1.是否要开Long Long？数组边界处理好了么？
	2.实数精度有没有处理？
	3.特殊情况处理好了么？
	4.做一些总比不做好。
思考提醒：
	1.最大值和最小值问题可不可以用二分答案？
	2.有没有贪心策略？否则能不能dp？
*/

```

---

