# Johnny and Ancient Computer

## 题目描述

Johnny has recently found an ancient, broken computer. The machine has only one register, which allows one to put in there one variable. Then in one operation, you can shift its bits left or right by at most three positions. The right shift is forbidden if it cuts off some ones. So, in fact, in one operation, you can multiply or divide your number by $ 2 $ , $ 4 $ or $ 8 $ , and division is only allowed if the number is divisible by the chosen divisor.

Formally, if the register contains a positive integer $ x $ , in one operation it can be replaced by one of the following:

- $ x \cdot 2 $
- $ x \cdot 4 $
- $ x \cdot 8 $
- $ x / 2 $ , if $ x $ is divisible by $ 2 $
- $ x / 4 $ , if $ x $ is divisible by $ 4 $
- $ x / 8 $ , if $ x $ is divisible by $ 8 $

For example, if $ x = 6 $ , in one operation it can be replaced by $ 12 $ , $ 24 $ , $ 48 $ or $ 3 $ . Value $ 6 $ isn't divisible by $ 4 $ or $ 8 $ , so there're only four variants of replacement.

Now Johnny wonders how many operations he needs to perform if he puts $ a $ in the register and wants to get $ b $ at the end.

## 说明/提示

In the first test case, Johnny can reach $ 5 $ from $ 10 $ by using the shift to the right by one (i.e. divide by $ 2 $ ).

In the second test case, Johnny can reach $ 44 $ from $ 11 $ by using the shift to the left by two (i.e. multiply by $ 4 $ ).

In the third test case, it is impossible for Johnny to reach $ 21 $ from $ 17 $ .

In the fourth test case, initial and target values are equal, so Johnny has to do $ 0 $ operations.

In the fifth test case, Johnny can reach $ 3 $ from $ 96 $ by using two shifts to the right: one by $ 2 $ , and another by $ 3 $ (i.e. divide by $ 4 $ and by $ 8 $ ).

## 样例 #1

### 输入

```
10
10 5
11 44
17 21
1 1
96 3
2 128
1001 1100611139403776
1000000000000000000 1000000000000000000
7 1
10 8```

### 输出

```
1
1
-1
0
2
2
14
0
-1
-1```

# 题解

## 作者：_jimmywang_ (赞：2)

$emmm \quad$赛后看到此题，没啥人做，写个题解~~加社贡~~帮助广大谷民好了~

进入正题：

我们发现，要$a$变成$b$，首先只能一个整除另一个，而且商还的是$2^n$的形式

那就好了。

那么可以的咋算？

最少的步骤？

那先来$8$的，没了来$4$,再没了来$2$

就行了。

$the\_code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll t;
int main(){
	t=d;
	while(t--){
		ll a=d,b=d;
		if(a>b)swap(a,b);
		if(b%a)cout<<"-1\n";
		else{
			ll ans=0;
			b/=a;
			while(b%8==0)b/=8,ans++;
			while(b%4==0)b/=4,ans++;
			while(b%2==0)b/=2,ans++;
			if(b!=1)cout<<"-1\n";
			else cout<<ans<<endl;
		}
	}
	return 0;
}
```


---

## 作者：SpeedStar (赞：1)

### 算法分析
先分两种情况进行考虑：

如果$a$和$b$相等，直接输出$0$；

否则统一成$a>b$的情况，然后判断$a$是否能被$b$整除，如果不能直接输出$-1$。否则接着判断$a/b$是否是$2$的整数次幂，如果不是则直接输出$-1$。否则统计一下$a/b$是$2$的多少次幂，记为$cnt$，然后继续统计一下$cnt$里有多少个$3、2$和$1$，最后把这三个值相加即得答案。


### C++代码
```cpp
#include <iostream>

#define int long long

using namespace std;

signed main() {
	int t;
	cin >> t;
	
	while (t--) {
		int a, b;
		cin >> a >> b;
		if (a == b) {
			cout << 0 << '\n';
			continue;
		}
		if (a < b) swap(a, b);
		int res = 0;
		int cnt = 0;
		if (a % b == 0) {
		    a /= b;
		    if (a & (a - 1)) {
		    	cout << -1 << '\n';
		    	continue;
			}
		    while (a) {
		    	if (a % 2 == 0) cnt++;
		    	a /= 2;
			}
			res += cnt / 3;
			cnt %= 3;
			res += cnt / 2;
			cnt %= 2;
			res += cnt;
			cout << res << '\n';
			continue;
		}
		cout << -1 << '\n';
	}
	
	return 0;
}
```


---

## 作者：zjr0330 (赞：0)

先分析一下题目，我们发现：如果 $a$ 能被 $b$ 整除或 $b$ 能被 $a$ 整除，那么 $a$ 就可以变成 $b$，否则输出 $-1$。

首先我们就想到了用两个循环看看 $a$ 是经过除法还是经过乘法才能变成 $b$，但我们再想想，如果 $a\le b$，那么交换他们。这样我们就可以在只除的情况下完成这份代码。

我们发现，先除 $8$，再除 $4$，最后除 $2$ 利益会更大。在除完之后，我们要判断它是否被除完，如果没被除完，那么输出 $-1$。

注意数据范围是 $10^{18}$ 所以要开 ```long long```。

下面就是代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long t;
	cin >> t;
	while (t--) {
		long long a = 1, b = 1;
		scanf("%lld%lld", &a, &b);
		if (a > b) {
			long long an = b;
			b = a;
			a = an;
		}
		if (b % a) {
			cout << "-1\n";
		} else {
			long long ans = 0;
			b /= a;
			while (b % 8 == 0) {
				b = b / 8, ans++;
			}
			while (b % 4 == 0) {
				b = b / 4, ans++;
			}
			while (b % 2 == 0) {
				b = b / 2, ans++;
			}
			if (b != 1) {
				printf("-1\n");
			} else {
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

当 $a = b$ 时，不需要任何操作就可以让 $a$ 变成 $b$。

当 $a > b$ 时，那么我们就先让 $a$ 每一次都乘上一个 $8$，直到 $a\times 8\gt b$ 为止，然后让 $a$ 每次乘 $4$，到 $a\times 4\gt b$ 为止，然后让 $a$ 每次乘 $2$，到 $a\times 2\gt b$ 为止。这个时候，如果 $a = b$，那么输出执行上面语句的次数，否则就代表无解输出 $-1$。

当 $a < b$ 的时候，我们只需要让 $a$ 和 $b$ 的值交换一下，然后按照 $a > b$ 的情况来操作即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t --) {
        long long a, b;
        cin >> a >> b;
        if (a == b) puts("0");
        else {
            if (a < b) swap (a, b);
            int cnt = 0;
            while (a % 8 == 0 && a / 8 >= b) a /= 8, cnt ++;
            while (a % 4 == 0 && a / 4 >= b) a /= 4, cnt ++;
            while (a % 2 == 0 && a / 2 >= b) a /= 2, cnt ++;
            if (a == b)
                printf ("%d\n", cnt);
            else
                puts("-1");
        }
    }
    return 0;
}

```


---

## 作者：liuyongle (赞：0)

#### 思路分析

将 $a$ 转换为 $r_a \cdot 2^x$，将 $b$ 转换为 $r_b \cdot 2^y$，其中 $r_a$ 和 $r_b$ 是奇数。唯一的操作是将 $x$ 改变为 $\{ -3,-2,-1,1,2,3\}$，因此 $r_a$ 必须等于 $r_b$，否则输出 $-1$。

不难发现到我们可以贪心，将 $x$ 向 $y$ 移动，因此答案等于$\lceil\frac{|x-y|}{3}\rceil$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

LL getR(LL a) {
	while(a%2==0)
		a/=2;
	return a;
}

void solve() {
	LL a,b;
	scanf("%lld %lld",&a,&b);
	if(a>b)
    	swap(a, b);
	LL r = getR(a);
	if(getR(b)!=r) {
		puts("-1");
		return ;
	}
	int ans=0;
	b/=a;
	while(b>=8)
		b/=8,++ans;
	if(b>1)
    	++ans;
	printf("%d\n",ans);
    return ;
}

int main() {
	int quest;
	scanf("%d",&quest);
	while(quest--)
		solve();
	return 0;
}
```

---

## 作者：Tarsal (赞：0)

这题貌似没什么好讲的= =

大概就是对于每对 $a, b$ 只可能有如下 $3$ 种情况：

### a > b 
此时显然可以知道你只会进行 $a -> a / 2$, $a -> a / 4$ 或者 $a -> a / 8$ 这 $3$ 种操作 

然后根据贪心, 如果可以进行 $a -> a / 8$ 操作, 并且变完以后 $a$ 还是保证 $a > b$ 那就用这个操作

$a -> a / 2$ 和 $a -> a / 4$ 都是一个道理

### a < b
此时显然可以知道你只会进行 $a -> a * 2$, $a -> a * 4$ 或者 $a -> a * 8$ 这 $3$ 种操作 

还是根据贪心可以先尝试 $a -> a * 8$ 然后依次尝试 $a -> a * 2$ 和 $a -> a * 4$

```
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#define N 1010
#define M 5000010
#define ls x << 1
#define rs x << 1 | 1
#define inf 0x3f3f3f3f
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define mid ((l + r) >> 1)
 #define int long long
//#define ll long long
#define XRZ 10000000000000
#define pai acos(-1)
#define debug() puts("XRZ TXDY");
#define mem(i, x) memset(i, x, sizeof(i));
#define Next(i, u) for(register int i = head[u]; i ; i = e[i].nxt)
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))
using namespace std;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1;c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar(); 
    return x * f;
}
int dx[10] = {0, 1, 1, 2, 2, -1, -1, -2, -2};
int dy[10] = {0, 2, -2, 1, -1, 2, -2, 1, -1};

signed main() { int T = read();
	while(T --) { int a = read(), b = read(), ans = 0;
		if(a == b) puts("0");
		if(a > b) {
			while(a >= b) {
				if(a % 8 == 0 && a / 8 >= b) a /= 8, ans ++;//可以除8就除8 
				else if(a % 4 == 0 && a / 4 >= b) a /= 4, ans ++;//可以除4就除4 
				else if(a % 2 == 0 && a / 2 >= b) a /= 2, ans ++;//可以除2就除2
				else break;//如果2都除不了，那么要么已经成立，要么永远都存在不了 
			} if(a != b) { puts("-1"); continue;} else printf("%d\n", ans);
		}
		if(a < b) {
			while(a <= b) {
				if(a * 8 <= b) a *= 8, ans ++;//乘法同上 
				else if(a * 4 <= b) a *= 4, ans ++;
				else if(a * 2 <= b) a *= 2, ans ++;
				else break;
			} if(a != b) { puts("-1"); continue;} else printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

