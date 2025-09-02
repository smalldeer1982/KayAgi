# Divisibility Test

## 题目描述

Daisy has recently learned divisibility rules for integers and she is fascinated by them. One of the tests she learned is a divisibility test by 3. You can find a sum of all digits of a decimal number and check if the resulting sum is divisible by 3. Moreover, the resulting sum of digits is congruent modulo 3 to the original number — the remainder modulo 3 is preserved. For example, $ 75 \equiv 7 + 5 \pmod 3 $ . Daisy is specifically interested in such remainder preserving divisibility tests.

There are more examples like that that she learned for decimal integers (integers base 10):

- To test divisibility modulo 11, find an alternating sum of digits. Counting digits from the last (least significant) digit, add digits on odd positions (the last, 3rd to the last, etc) and subtract digits on even positions (2nd to the last, 4th to the last, etc) to get the sum that is congruent modulo 11 to the original number. For example, $ 123 \equiv 1 - 2 + 3 \pmod {11} $ .
- To test divisibility modulo 4, keep the last two digits. Their value is congruent modulo 4 to the original number. For example, $ 876543 \equiv 43 \pmod 4 $ .
- To test divisibility modulo 7, find an alternating sum of groups of three digits. For example, $ 4389328 \equiv 4 - 389 + 328 \pmod 7 $ .

Similar tests can be found in other bases. For example, to test divisibility modulo 5 for octal numbers (base 8), find an alternating sum of groups of two digits. For example, $ 1234_8 \equiv -12_8 + 34_8 \pmod 5 $ .

Daisy wants to find such rules for a given base $ b $ . She is interested in three kinds of divisibility rules:

- Kind 1 — take the last $ k $ digits of an integer in base $ b $ .
- Kind 2 — take a sum of groups of $ k $ digits of an integer in base $ b $ .
- Kind 3 — take an alternating sum of groups of $ k $ digits of an integer in base $ b $ .

It is not always possible to find such a divisibility rule. For example, in base 10 there is no such test for divisibility modulo 6, even though different approaches to testing divisibility by 6 exist.

Given base $ b $ and modulo $ n $ , Daisy wants to know the smallest group size $ k $ for which such a divisibility test exits.

## 样例 #1

### 输入

```
6
10 3
10 11
10 4
10 7
8 5
10 6```

### 输出

```
2 1
3 1
1 2
3 3
3 2
0```

# 题解

## 作者：FFTotoro (赞：4)

小学奥数判断整除的几种便捷方法。

考虑三种操作的实质：

- 取最后 $k$ 位：当 $b^k\bmod n=0$ 时可以使用该方法；

  证明：显然 $b^{k+d}\bmod n=0(d\ge 0)$，所以更高位上的数可以不用考虑，直接考虑后 $k$ 位即可；

- $k$ 位一组求和：当 $b^k\bmod n=1$ 时可以使用该方法；

  证明：有 $xb^{dk}\equiv xb^k\equiv x\pmod n(d\ge 0)$，于是将系数 $b^k$ 视为 $1$，$k$ 位一组求和是正确的；下面的证明类似，就是把 $1$ 换成 $-1$；

- $k$ 位一组求交叉和：当 $b^k\bmod n=n-1$ 时可以使用该方法；

显然 $k$ 最大为 $n$。枚举即可；注意判断无解。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int b,n; cin>>b>>n;
    long long c=1; bool f=false;
    for(int k=1;k<=n&&!f;k++){
      if((c*=b)%=n;!c)cout<<"1 "<<k<<'\n',f=true;
      if(c==1)cout<<"2 "<<k<<'\n',f=true;
      else if(c==n-1)cout<<"3 "<<k<<'\n',f=true;
    }
    if(!f)cout<<"0\n"; // 无解
  }
  return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
通过~~观察数据~~学习小学奥数我们可以知道，若可以取后 $k$ 位来判断，则 $b^k\bmod n=0$；若需要 $k$ 位一节相加来判断，则 $b^k\bmod n=1$；若需要 $k$ 位一节并且交替加减来判断，则 $b^k\bmod n=n-1$。如果 $b^k\bmod n$ 已经进入循环了还没出答案，则无解。若对这三个式子有疑问则可自己手动列竖式理解。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t, n, m, x;
bitset <1000005> vis;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> m >> n;
		x = 1;
		m %= n;
		for (int i = 0; i < n; ++ i)
			vis[i] = 0;
		for (int k = 1; ! vis[x = x * (ll) m % n]; ++ k) {
			if (! x) {
				cout << "1 " << k << '\n';
				goto there;
			} else if (x < 2) {
				cout << "2 " << k << '\n';
				goto there;
			} else if (x > n - 2) {
				cout << "3 " << k << '\n';
				goto there;
			}
			vis[x] = 1;
		}
		cout << "0\n";
there:
		;
	}
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

又是一道水绿。

刚刚小学毕业的数学 idiot——我释怀地笑了。

第一种很好判断，当 $b^k$ 为 $n$ 的倍数时，取基数为 $b$ 的能被 $n$ 整除的整数 $c$ 的最后 $k$ 位数显然能被 $n$ 整除。

第二种也不难，当 $b^k \equiv 1 \pmod n$ 时，取以 $b$ 为底数的能被 $n$ 整除的整数 $c$ 的 $k$ 位数的各组之和能被 $n$ 整除。 

为什么呢？ 

令 $a_1,a_2,\dots,a_l$ 为 $c$ 从低位到高位各个 $k$ 位数，则 $c=\sum _ {i=1} ^ {l} a_i \times 10^{(i-1)k}$，而和 $d$ 为 $\sum _ {i=1} ^ {l} a_i$。∵$10^{(i-1)k}\equiv 1 \pmod n$。于是 $c=\sum _ {i=1} ^ {l} a_i \times 10^{(i-1)k} \equiv \sum _ {i=1} ^ {l} a_i \times 1 \pmod n$。∴$c \equiv d \pmod n$。

第三种也很好判断，按第二种的方法，能推出式子。当 $b^k \equiv -1 \pmod n$ 时，取以 $b$ 为底数的能被 $n$ 整除的整数 $c$ 的 $k$ 位数的各组之和能被 $n$ 整除。 

令 $a_1,a_2,\dots,a_l$ 为 $c$ 从低位到高位各个 $k$ 位数，则 $c=\sum _ {i=1} ^ {l} a_i \times 10^{(i-1)k}$，而和 $d$ 为 $\sum _ {i=1} ^ {l} (-1)^i\times a_i$。∵$10^{(i-1)k}\equiv -1 \pmod n$。于是 $c=\sum _ {i=1} ^ {l} a_i \times 10^{(i-1)k} \equiv \sum _ {i=1} ^ {l} a_i \times (-1)^i  \pmod n$。∴$c \equiv d \pmod n$。

My code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,b,n;
ll power;
int main(){
	cin>>t;
  	while(t--){
	    cin>>b>>n;
	    power=1; 
		bool f=0;
	    for(int k=1;k<=n&&!f;k++){
	    	power=power*b%n; 
	      	if(!power)cout<<"1 "<<k<<'\n',f=1;
	      	else if(power==1)cout<<"2 "<<k<<'\n',f=1;
	      	else if(power==n-1)cout<<"3 "<<k<<'\n',f=1;
	    }
	    if(!f) cout<<"0\n"; 
  }
  return 0;
}



```

---

## 作者：Robin_kool (赞：0)

观察发现在有解的情况下 $k \leq n$ 一定成立，又因为 $n$ 和 $T$ 很小,我们可以暴力枚举每一个 $k$ 判断是否符合三种情况中的一种。

第 $1$ 种情况：可以从 $10$ 进制推出，当 $n=4$ 时，只需要取 $k=2$ 即可。可以证明，满足 $b^k \equiv 0 \pmod n$，$k$ 便符合条件。

证明：


$\because b^k\equiv 0 \pmod n$

$\therefore b^k b^x \equiv 0 \pmod n (x \geq 0)$

所以 $k$ 一定为最优解。

第 $2$ 种情况：$b^k \equiv 1 \pmod n$ 时 $k$ 有最优解。

证明：还是先从 $10$ 进制考虑。 $k$ 满足条件时，分成若干段后显然从这段数之后的所有数都等同于变成了 $0$ ，那么就可以拆成 $a · 10^b$ 的形式，因为之前那段数满足条件所以 $10^b$ 同理。

即 $x·b^kb^y \equiv x·b^k \equiv x \pmod n$。令 $x=1$ 便和第 $1$ 种情况类似。

第 $3$ 种情况：

同第 $2$ 种情况，只是对于每段的奇偶性进行了分类讨论，令 $x=1,b^k=-1$ 便和第 $1$ 种情况类似。

代码很短。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, b, now;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("CF1912D.in", "r", stdin);
	//freopen("CF1912D.out", "w", stdout);
    T = read();
    while(T --){
    	b = read(), n = read(), now = 1;
    	for(int i = 1; i <= n; ++ i){
    		now = (now * b) % n;//注意取模，最好开long long
    		if(now == 0){
    			write(1), putchar(' '), write(i);
    			break;
			}else if(now == 1){
				write(2), putchar(' '), write(i);
				break;
			}else if(now == n - 1){
				write(3), putchar(' '), write(i);
				break;
			}
			if(i == n){
				write(0), putchar(' ');
			}//注意判断无解
		}
		putchar('\n');
	}
	return 0;
}

```

---

