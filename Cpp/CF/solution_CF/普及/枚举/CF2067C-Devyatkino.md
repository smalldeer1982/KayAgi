# Devyatkino

## 题目描述

You are given a positive integer $ n $ . In one operation, you can add to $ n $ any positive integer whose decimal representation contains only the digit $ 9 $ , possibly repeated several times.

What is the minimum number of operations needed to make the number $ n $ contain at least one digit $ 7 $ in its decimal representation?

For example, if $ n = 80 $ , it is sufficient to perform one operation: you can add $ 99 $ to $ n $ , after the operation $ n = 179 $ , which contains the digit $ 7 $ .

## 说明/提示

In the first test case, three operations are sufficient: $ 51 + 9 + 9 + 9 = 78 $ , which contains the digit $ 7 $ . It can be shown that it is impossible to achieve the goal in one or two operations.

In the second test case, two operations are sufficient: $ 60 + 9 + 9 = 78 $ .

In the third test case, one operation is sufficient: $ 61 + 9 = 70 $ .

In the fourth test case, $ n $ already contains the digit $ 7 $ , so no operations are required.

In the fifth test case, you can add $ 99 $ to $ n $ to obtain a number containing the digit $ 7 $ .

## 样例 #1

### 输入

```
16
51
60
61
777
12345689
1000000000
2002
3001
977
989898986
80
800001
96
70
15
90```

### 输出

```
3
2
1
0
1
3
5
4
0
7
1
2
7
0
7
3```

# 题解

## 作者：thedyingkai (赞：6)

### 思路
对于 $n$ 上加的数 $a$，有 $a=\underbrace{99\cdots9}_{x\text{个 9}}=10^x-1$，而 $n$ 的末尾加上至多 $9$ 个 $9$ 便一定可以得到 $7$，所以把答案的范围锁定在 $[0,9]$ 的范围内。
> **在外层枚举 $x\in[0,9]$ 的好处就是可以事先减去 $x$ 个 $1$，后面就不用考虑进位的问题了**。

这样问题就转换为了在数字的每一位尝试，找到把该位加到 $7$ 所需要的 $1$ 的最少数量。

- 只在 $res≤x$ 的情况下输出答案是因为 $res>x$ 的话，可能产生意外的进位，我们并不想单独判断这些情况。
- $res$ 初始化为 $7$，因为 $9+9\times2=27$，$8+9\times1=17$，所以无论如何 $res$ 不可能大于 $7$。
### AC code
```cpp
#include "iostream"
using namespace std;
int t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int x=0;x<10;x++){
            int res=7;
            string s=to_string(n-x);
            for(int i=0;i<s.length();i++)
                if(s[i]>='0'&&s[i]<='7') res=min(res,'7'-s[i]);
            if(res<=x){
                cout<<x<<endl;
                break;
            }
        }
    }
}
```

---

## 作者：what_can_I_do (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF2067C)

可以把加上 $n$ 位的 $9$ 看做第 $n+1$ 位加 $1$，第 $1$ 位减 $1$，所以每次变化相当于只对两位进行变化，或者说如果不考虑不管加上几位都要减 $1$ 的第一位，其实每次就只对第 $n+1$ 位进行变化，所以每次一定是加上相同位数的 $9$ 最优。

我们还可以发现就算是第一位减 $1$ 导致退位，第 $n+1$ 位要变化到 $7$ 的次数也不超过 $10$，可以直接暴力枚举加的次数，然后暴力判断现在的数中是否含 $7$。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
char s[110];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=1e9;ll x=0,js=1;
		cin>>s,n=strlen(s);
		for(register int i=0;i<n;i++) x=x*10+1ll*(s[i]-'0');
		for(register int i=1;i<=n;i++)
		{
			js*=10;ll v=x;
			for(register int j=0;j<=11;j++)
			{
				ll sum=v;
				int f=0;
				while(sum)
				{
					if(sum%10==7)
					{
						f=1;
						break;
					}
					sum/=10;
				}
				if(f){ans=min(ans,j);break;}
				v+=js-1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：3)

## 题解：CF2067C Devyatkino

### 题意简述

您将获得一个正整数 $n$。

在一个运算中，您可以将十进制表示形式仅包含数字 $9$ 的任何正整数加到 $n$ 上，并且可能会重复多次。

使数字 $n$ 在其十进制表示中至少包含一个数字 $7$ 所需的最小操作次数是多少？

例如，如果 $n = 80$，则执行一个操作就足够了：您可以将 $99$ 添加到 $n$ 中使 $n = 179$，此时 $n$ 包含 $7$。

### 解题思路

观察样例发现答案都是一位数，打表同样可以证明：在末位任意的情况下，最多 $9$ 次操作使末位变成 $7$。

|答案|$0$|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|$9$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**末位：$0$**|$0$|$9$|$8$|$\color{Red}7$|$6$|$5$|$4$|$3$|$2$|$1$|
|**末位：$1$**|$1$|$0$|$9$|$8$|$\color{Red}7$|$6$|$5$|$4$|$3$|$2$|
|**末位：$2$**|$2$|$1$|$0$|$9$|$8$|$\color{Red}7$|$6$|$5$|$4$|$3$|
|**末位：$3$**|$3$|$2$|$1$|$0$|$9$|$8$|$\color{Red}7$|$6$|$5$|$4$|
|**末位：$4$**|$4$|$3$|$2$|$1$|$0$|$9$|$8$|$\color{Red}7$|$6$|$5$|
|**末位：$5$**|$5$|$4$|$3$|$2$|$1$|$0$|$9$|$8$|$\color{Red}7$|$6$|
|**末位：$6$**|$6$|$5$|$4$|$3$|$2$|$1$|$0$|$9$|$8$|$\color{Red}7$|
|**末位：$7$**|$\color{Red}7$|$6$|$5$|$4$|$3$|$2$|$1$|$0$|$9$|$8$|
|**末位：$8$**|$8$|$\color{Red}7$|$6$|$5$|$4$|$3$|$2$|$1$|$0$|$9$|
|**末位：$9$**|$9$|$8$|$\color{Red}7$|$6$|$5$|$4$|$3$|$2$|$1$|$0$|

这时暴力就很好打了。

从小到大枚举答案，对于每个答案，对于每个形如 $99\dots9$ 的数，检查 $n + 99\dots9$ 中是否有 $7$ 即可。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t;
long long n;
const long long biao[20] = {0ll , 9ll , 99ll , 999ll , 9999ll , 99999ll , 999999ll , 9999999ll , 99999999ll , 999999999ll , 9999999999ll};
inline bool check(int q)
{
	long long k;
	for(int i = 0 ; i <= 10 ; i++)
	{
		k = n + biao[i] * q;
		while(k)
		{
			if(k % 10 == 7)
			{
				return 1;
			}
			k /= 10;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 0 ; i <= 10 ; i++)
		{
			if(check(i))
			{
				cout << i << '\n';
				break;
			}
			if(i == 10)
			{
				cout << "WA\n"; 
			}
		}
	}
	return 0;
}
```

内容来源：[赛时提交](https://mirror.codeforces.com/contest/2067/submission/305643003)

---

## 作者：AetherWaves (赞：1)

## 题目大意

不妨设现在有一正整数 $n(10<n<10^9)$ ，让我们求出最小的 
 $x(x\in N_{+})$ 使得 $n$ 加上 $x$ 次 $10^m-1(m\in N_{+})$ 形式的数中含有 $7$ 这个数字。

## 解题思路
### 第一步
首先，我们要去判断现在的 $n$ 是否含有 $7$ ，这件事情十分容易，我们只需遍历 $n$ 的所有数位，紧接着进行模 $7$ 运算的即可，参照下面代码。
```
long long xyz(long long n){
  	while(n>0){
		long long p=n%10;
		if(p==7) return 1;
		else n=(n-p)/10;
	}
}
```
### 第二步.
在解决了基础问题后，我们开始解决核心问题，同时我们不妨抛出一个问题：对于 $cnt$ 是否会有一个上限呢？
#### 问题——$cnt$ 的上限
我们发现，在九九乘法表中，对于 $1\times 9$ 至 $9\times 9$ 中，$1$ 到 $9$ 均出现了一次，这说明，对于任意正整数，只需加上 $10$ 次以下 $10^m-1(m\in N_{+})$ 形式的数，个位就能出现 $7$ 。我们得出结论。
$$\max cnt=9$$
下面为严谨证明。

假设 $cnt>=10$，不妨设 

$$cnt\equiv q\pmod 
{10} (q\in N，q<10)$$ 

$$\therefore n \equiv 9\times q+9\times (cnt-q)\equiv 9\times q\pmod {10}。$$

又$\because n\equiv9\times q+9\times (cnt-q)\equiv 9\times q+9\times (cnt-10-q)\equiv9\times(cnt-10)\pmod {10}$

$\therefore$ 对于 $cnt>9$ 的情况，总有 $cnt-10$ 使得中 $n$ 含有 $9$。

### 第三步
现在我们已经解决了问题中的核心问题，就已经可以解决题目了，代码如下。

```
#include<bits/stdc++.h>
using namespace std;
long long n,t;  //题目中个数变量
long long xyz(long long n){  //判断n中是否含有7
  	while(n>0){
		long long p=n%10;
		if(p==7) return 1;
		else n=(n-p)/10;
	}
}
int main(){
	cin>>t;
	for(int j=1;j<=t;j++){
		cin>>n;
		long long ans=1e18,val=9;  //ans定为long long上限，方便更新，val为10^m-1，后面更新
		for(int i=1;i<=10;i++){    //我们刚刚解决的核心问题，cnt<=9
			long long cnt=0,a=n;
			while(!xyz(a)){  //判断n中是否含有7，若没有，继续更新
				a+=val;
				cnt++;
			}
			ans=min(ans,cnt);
			val=val*10+9;
			
		}
		cout<<"抄题解的直接坐下！"<<endl; 
	}
	return 0;
}
```

---

## 作者：__O__W__O__ (赞：0)

### 题意
给定一个数 $n$，允许进行无限次操作，每次可以加上一个每位都是 $9$ 的数（比如：$9,99,999$），问最少多少次操作，能将这个数有一位是 $7$。

### 思路
这道题是一道找规律题，规律就是答案不会超过 $7$，加的数最大是 $9999999$，暴力打 $7$ 层循环即可，时间复杂度为 $O(T$ $7!) = O(6480T)\approx O(T)$。规律请看证明。
##### 证明：
个位为 $7$ 肯定可以。

每次只加 $9$，那么 $n$ 次操作后该数加了 $9n$。  
众所周知：
$$1 \times 9 = 9$$
$$2 \times 9 = 18$$
$$3 \times 9 = 27$$
$$4 \times 9 = 36$$
$$5 \times 9 = 45$$
$$6 \times 9 = 54$$
$$7 \times 9 = 63$$
个位为 $8,9,0,1,2,3,4$ （分别加上 $1 \times 9 ,2 \times 9,3 \times 9$ 等）的数可以在 $7$ 次操作内将个位变 $7$。

个位为 $5,6$ 的时候，当十位不为 $5,6$，也可加 $99$，在 $7$ 步内十位变 $7$。当十位为 $5$ 时，加 $4$ 次 $9$ 即可把十位变 $7$。同样，十位为 $6$ 时，加 $3$ 次 $9$ 即可把十位变 $7$。

综上，最多操作 $7$ 次即可能将 $n$ 有一位是 $7$。

### code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
 
// 存储由 9 组成的数字
int a[] ={9,99,999,9999,99999,999999,9999999,99999999};
int t;
 
// 检查数字是否包含 7
bool check(int f){
    while (f != 0){
        if (f % 10 == 7){
            return true;
        }
        f /= 10;
    }
    return false;
}
 
signed main(){
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        int ans = 7;
        // 枚举每种由 9 组成的数字的选取次数，每种数字选取次数之和不大于 7
        for (int i0 = 0;i0 <= 7;++i0){
            for (int i1 = 0;i1 + i0 <= 7;++i1){
                for (int i2 = 0;i2 + i1 + i0 <= 7;++i2){
                    for (int i3 = 0;i3 + i2 + i1 + i0 <= 7;++i3){
                        for (int i4 = 0;i4 + i3 + i2 + i1 + i0 <= 7;++i4){
                            for (int i5 = 0;i5 + i4 + i3 + i2 + i1 + i0 <= 7;++i5){
                                for (int i6 = 0;i6 + i5 + i4 + i3 + i2 + i1 + i0 <= 7;++i6){
                                    for (int i7 = 0;i7 + i6 + i5 + i4 + i3 + i2 + i1 + i0 <= 7;++i7){
                                        int sum = i0 * a[0] + i1 * a[1] + i2 * a[2] + i3 * a[3] + i4 * a[4] + i5 * a[5] + i6 * a[6] + i7 * a[7];
                                        if (check(sum + n)){
                                            ans = min(ans,i0 + i1 + i2 + i3 + i4 + i5 + i6 + i7);
                                        }
                                    //    cout << sum << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：GZXUEXUE (赞：0)

### 思路

暴力水过去了……

首先，答案肯定不大于 $7$。

- 证明（其实有更好的证明啦）

  我们记答案为 $\operatorname{ans}$。

  1. $n$ 的最高位不可能是 $0$。
  2. 如果 $n$ 的最高位是 $1$，那么我们给 $n$ 加上同样位数的 $999\dots$ 就可以得到一个 $10\dots$ 或者 $11\dots$ 这样的数字。如果得到了 $11\dots$ 这样的数字，那么再给它加上位数为这个数字的位数减去 $1$ 的 $999\dots$ 就可以变为 $20\dots$ 这样的数字。那么显见连续在 $0$ 这一位加上 $3$ 次 $9$ 即可让这一位变成 $7$，所以 $\operatorname{ans}$ 最大为 $5$。
  3. 如果 $n$ 的最高位是 $2$，那么我们给 $n$ 加上同样位数的 $999\dots$ 就可以得到一个 $1\dots$ 这样的数字，转化为第二种情况即可。$\operatorname{ans}$ 最大为 $6$。
  4. 如果 $n$ 的最高位是 $3$，那么显见最多给 $n$ 加上 $5$ 次位数为 $n$ 的位数减去 $1$ 的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $5$。
  5. 如果 $n$ 的最高位是 $4$，那么显见最多给 $n$ 加上 $4$ 次位数为 $n$ 的位数减去 $1$ 的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $4$。
  6. 如果 $n$ 的最高位是 $5$，那么显见最多给 $n$ 加上 $3$ 次位数为 $n$ 的位数减去 $1$ 的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $3$。
  7. 如果 $n$ 的最高位是 $6$，那么显见最多给 $n$ 加上 $2$ 次位数为 $n$ 的位数减去 $1$ 的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $2$。
  8. 如果 $n$ 的最高位是 $7$，那么已经符合题意了。$\operatorname{ans}$ 最大为 $0$。
  9. 如果 $n$ 的最高位是 $8$，那么显见最多给 $n$ 加上 $2$ 次同样位数的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $2$。
  10. 如果 $n$ 的最高位是 $9$，那么显见最多给 $n$ 加上 $3$ 次同样位数的 $999\dots$ 就可以得到一个 $7\dots$ 这样的数字，于是符合题目。$\operatorname{ans}$ 最大为 $3$。

  显见不可能再有其他的最高位。

  证毕。

然后，要加的数字必定不大于 $99999999$，乘起来的时候记得开 `long long`。

- 证明

  注意到 $n \le 10^9$。

  如果 $n = 10^9$，则可令其加上 $3$ 次 $9$，得到 $10^9 + 27$，于是符合题意。

  否则，我们可以直接按照上文「答案显然不大于 $7$」的证明方法发现，我们最大要用到的只是「与 $n$ 同样位数的 $999\dots$」，又因为此时 $n$ 最大为八位数，故最大要加的数字为 $99999999$。

  证毕。

于是，我们可以直接用枚举解决题目。

还有一点，其实我们初始已知答案最大为 $7$ 后，其实可以一直把这个最大值更新，这样子说不定可以省去不少时间，而且顺便记录了答案。

时间复杂度为 $O(\operatorname{mt})$，其中 $m = 7! = 5040$。

~~啸常数怕个屁~~乱开 longlong 见太奶啊！

### 实现

~~八层 for 循环难绷。~~

```cpp
# include <iostream>
using namespace std;
# define ll long long
# define f(x,y) for (int (x) = 0;(x) <= (y);(x)++)
ll input(){
	int ans = 0,op = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') op = -1;
		c = getchar();
	}while (c >= '0' && c <= '9') ans = ans * 10 + (c - '0'),c = getchar();
	return ans * op;
}void output(int x){
	if (x < 0) putchar('-'),x *= -1;
	if (x > 9) output(x / 10);
	putchar((x % 10) + '0');
}bool check(int x){
	while (x){
		if (x % 10 == 7) return true;
		x /= 10;
	}return false;
}void solve(){
	ll n = input(); int ans = 7;
    if (check(n)){
        output(0); cout << '\n';
        return;
    }f(g,ans){
		f(z,ans-g){
			f(x,ans-g-z){
				f(u,ans-g-z-x){
					f(e,ans-g-z-x-u){
						f(X,ans-g-z-x-u-e){
							f(U,ans-g-z-x-u-e-X){
                                int now = n + 99 * g + 999 * z + 9999 * x + 99999 * u + 999999 * e + 9999999 * X + 99999999 * U;
								if (check(now)){
									ans = min(ans,g+z+x+u+e+X+U);
									continue;
								}f(E,ans-g-z-x-u-e-X-U){
									if (check(now)){
										ans = min(ans,g+z+x+u+e+X+U+E);
										break;
									}now += 9;
								}
							}
						}
					}
				}
			}
		}
	}output(ans);
	cout << '\n';
}signed main(){
	int t = input();
	while (t--) solve();
	return 0;
}
```

---

## 作者：SICKO (赞：0)

考虑加上 $9\dots9$ 对数字的影响，发现 $9\dots9 = 10\dots0 - 1$。所以对于给出数字 $n = \overline{a_Aa_{A-1}a_{A-2}\dots{a_2a_1}}$ 的**每一位**，有两种接近 $7$ 的办法：一种是当前位数 $a_i$ 通过前面数加上 $9\dots9$ 进位变成 $7$，另一种则是 $\overline{a_ia_{i-1}\dots a_2a_1}$ 一直减去 $1$ 直到变成 $79\dots9$ 从而使得当前位变成 $7$。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+6;
const int INF = 1e18;
 
int fsp(int x, int y){
    int res = 1;
    while(y) {
        if(y&1) res *= x;
        x *= x; y >>= 1;
    }
    return res;
}
 
void solve() {
    int n; cin>>n;
    int bef = 0, res = 7, ws = 0, use = 7;
    while(n) {
        int tis = n % 10; n /= 10;
 
        if(tis == 7) res = 0;
        // 进位
        if(ws != 0 && tis < 7) res = min(res, 7 - tis + (bef < 7-tis));
 
        bef = tis * fsp(10, ws) + bef; ws += 1;
        // 退位
        res = min(res, bef - use + (bef < use) * fsp(10, ws));
 
        use = use * 10 + 9;
    }
 
    cout<<res<<"\n";
}
 
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    for(int i=1; i<=T; i++) solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 闲话
本文同步发布在 [cnblogs](https://www.cnblogs.com/zhangzirui66)。

---

首先易得答案一定 $\le 9$，因为一个数位增加数字 $9$ 后，重复 $9$ 次操作，一定出现过 $0 \sim 9$ 的所有数字，这个手搓就可证明。

由于 $n$ 的数据范围只有 $10^9$，我们依次枚举仅含 $9$ 的数，只用枚举到 $10$，模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, n;
// 是否含有 7
bool check(long long x){
    int flag = 0;
    while(x){
        flag = max(flag, (int)(x % 10 == 7));
        x /= 10;
    }
    return flag;
}
int main(){
    cin >> t;
    while(t --){
        cin >> n;
        long long ans = 2e9, add = 9;
        for(int i = 1; i <= 14; i ++){// 这里只用枚举到 9 ~ 10，我为了保险多枚举了一些
            long long sum = 0, b = n;
            while(!check(b)){
                b += add;
                sum ++;
            }
            ans = min(ans, sum);// 更新最优答案
            add = 10 * add + 9;// 增加一个 9
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

唐吗？唐的。

# 题目链接

[CF2067C Devyatkino](https://www.luogu.com.cn/problem/CF2067C)

# 解题思路

首先注意到答案一定不会大于 $7$，这点显然，不多说。

那么直接暴力枚举即可，你需要保证每种数字选取次数之和不大于 $7$，还是暴力即可，时间复杂度 $O(T \times 7!)$，可以通过此题。

那么为什么只用取到 $9999999$ 呢？因为根据 $7$ 的整除性，此时 $7$ 个 $9$ 构成了一个 $7$ 循环，此时一定最优，此时必定取到最优情况。

# 参考代码

唐的一批。

```cpp
ll n;
ll f(ll x)
{
    ll pd=0;
    while(x)
        pd|=x%10==7,
        x/=10;
    return pd;
}
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    if(f(n))
    {
        cout<<0<<endl;
        return ;
    }
    ll nn=n,ans=7;
    forl(______,0,ans)
        forl(_____,0,ans-______)
            forl(____,0,ans-______-_____)
                forl(___,0,ans-______-_____-____)
                    forl(__,0,ans-______-_____-____-___)
                        forl(_,0,ans-______-_____-____-___-__)
                            forl(qwq,0,ans-_-__-___-____-_____-______)
                            {
                                nn=n+99*_+999*__+9999*___+99999*____+999999*_____+9999999*______+99999999*qwq;
                                if(f(nn))
                                {
                                    Min(ans,_+__+___+____+_____+______+qwq);
                                    continue;
                                }
                                forl(i,1,ans-_-__-___-____-_____-______-qwq)
                                {
                                    nn+=9;
                                    if(f(nn))
                                    {
                                        Min(ans,i+_+__+___+____+_____+______+qwq);
                                        break;
                                    }
                                }
                            }
    cout<<ans<<endl;
}
```

---

