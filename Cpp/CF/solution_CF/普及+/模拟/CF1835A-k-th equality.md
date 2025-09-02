# k-th equality

## 题目描述

Consider all equalities of form $ a + b = c $ , where $ a $ has $ A $ digits, $ b $ has $ B $ digits, and $ c $ has $ C $ digits. All the numbers are positive integers and are written without leading zeroes. Find the $ k $ -th lexicographically smallest equality when written as a string like above or determine that it does not exist.

For example, the first three equalities satisfying $ A = 1 $ , $ B = 1 $ , $ C = 2 $ are

- $ 1 + 9 = 10 $ ,
- $ 2 + 8 = 10 $ ,
- $ 2 + 9 = 11 $ .

An equality $ s $ is lexicographically smaller than an equality $ t $ with the same lengths of the numbers if and only if the following holds:

- in the first position where $ s $ and $ t $ differ, the equality $ s $ has a smaller digit than the corresponding digit in $ t $ .

## 说明/提示

In the first test case, the first $ 9 $ solutions are: $ \langle 1, 1, 2 \rangle, \langle 1, 2, 3 \rangle, \langle 1, 3, 4 \rangle, \langle 1, 4, 5 \rangle, \langle 1, 5, 6 \rangle, \langle 1, 6, 7 \rangle, \langle 1, 7, 8 \rangle, \langle 1, 8, 9 \rangle, \langle 2, 1, 3 \rangle $ .

Int the third test case, there are no solutions as the smallest possible values for $ a $ and $ b $ are larger than the maximal possible value of $ c $ — $ 10 + 10 = 20 > 9 $ .

Please note that whitespaces in the output matter.

## 样例 #1

### 输入

```
7
1 1 1 9
2 2 3 1
2 2 1 1
1 5 6 42
1 6 6 10000000
5 5 6 3031568815
6 6 6 1000000000000```

### 输出

```
2 + 1 = 3
10 + 90 = 100
-1
9 + 99996 = 100005
-1
78506 + 28543 = 107049
-1```

# 题解

## 作者：XSean (赞：12)

# C：k-th equality

[C - k-th equality](https://codeforces.com/contest/1836/problem/C)

## 基本思路：

假设式子是 $a + b = c$。

由 $A$ 暴力枚举 $a$ 的范围，由 $B$ 与 $C$ 确定 $b$ 的范围，也就知道了一个 $a$ 对应了多少的 $b$，与 $k$ 不断对比即可。

**时间复杂度：$O(10^A)$**

为什么可以这样的复杂度，$t$ 都有 $10^3$ 诶？请看这句话：

> Each input file has at most $5$ test cases which **do not** satisfy $A, B, C \leq 3$.
>
> 最多有 $5$ 个测试用例不满足 $A, B, C \leq 3$。

## 代码实现：

核心代码：

```cpp
int qmi(LL a, int k){
	int res = 1;
	for(; k; k >>= 1, a = a * a) if(k & 1) res = res * a;
	return res;
}
void ans(int a, int b){
	prf("%d + %d = %d\n", a, b, a + b);
}
int main(){
	int T; rd(T);
	while(T--){
		LL a, b, c, k; rd(a, b, c, k);
		bool f = true;
		int l = qmi(10, a - 1), r = qmi(10, a) - 1;
		rep(i, l, r){
			int L = max(qmi(10, b - 1), qmi(10, c - 1) - i);
			int R = min(qmi(10, b) - 1, qmi(10, c) - 1 - i);
			if(L > R) continue;
			int temp = R - L + 1;
			if(k <= temp){
				ans(i, L + k - 1);
				f = false;
				break;
			}
			k -= temp;
		}
		if(f) puts("-1");
	}	
	return 0;
}
```

**[完整代码](https://www.luogu.com.cn/paste/u7qxryow)**

---

## 作者：qwq___qaq (赞：4)

首先，因为 $A,B,C>3$ 时的数据组数不超过 $5$，所以可以直接考虑暴枚。由于字典序最小，所以肯定先枚举 $a,b$。

在 $a+b=c$ 中，在 $a$ 确定后，我们可以转化为 $b+a=c$，也就是说，我们可以通过 $b$ 的范围来得到 $c$ 的范围，那么我们就可以得到可行的 $c$ 的数量，然后就可以判断此时的 $a$ 是否已经达到了第 $k$ 个式子了。

时间复杂度 $O(10^A)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,k,cnt,p[15];
inline void solve(){
	cnt=0;
	for(int A=p[a-1];A<p[a];++A){
		int l=max(p[b-1]+A,p[c-1]),r=min(p[b]-1+A,p[c]-1);
		if(l>r)
			continue;
		if(cnt+(r-l+1)>=k){
			cout<<A<<" + "<<l+(k-cnt-1)-A<<" = "<<l+(k-cnt-1)<<endl;
			return;
		}
		cnt+=(r-l+1);
	}
	cout<<"-1"<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    p[0]=1;
    for(int i=1;i<=10;++i)
    	p[i]=p[i-1]*10;
    cin>>T;
	while(T--){
		cin>>a>>b>>c>>k;
		solve();
	}
	return 0;
}
```

---

## 作者：jasonshen_ (赞：1)

## 翻译
我们考虑所有的形式上满足 $a + b = c$ 的等式。其中数字 $a$ 有 $A$ 个位，$b$ 有 $B$ 个位，$c$  有 $C$ 个位。

（注：所有的数字都是正整数，并且没有前导零。）

现在你的任务是：找到第 $k$ 小字典序的等式，或者断言它不存在。

例如，满足 $A = 1, B = 1, C = 2$ 的前三小字典序的等式为：

- $1 + 9 = 10$。

- $2 + 8 = 10$。

- $2 + 9 = 11$。
## 思路
我们可以直接打暴力来确定 $A$ 的范围，也就知道了一个 $a$ 对应了多少的 $b$，与 $k$ 不断对比即可。
代码就很简单了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a,b,c;
ll k;
void solve(){
		cin>>a>>b>>c>>k;
		int max_a=pow(10,a),min_a=pow(10,a-1); 
		int max_b=pow(10,b),min_b=pow(10,b-1); 
		int max_c=pow(10,c),min_c=pow(10,c-1);
		for(int i=min_a;i<max_a;i++){ 
			ll x=max(min_b,min_c-i); 
			ll y=min(max_b,max_c-i);
			if(x>y) continue;
			if(y-x>=k){
				cout<<i<<" + "<<x+k-1<<" = "<<x+k-1+i<<endl;x+k-1;
				return;
			}
			k-=y-x;
		}
		cout<<-1<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	
}
 							 														
                                                                                    ```

---

## 作者：rainygame (赞：1)

> 这个小丑十分钟就想到了完整的思路，然而一小时之后还没有通过。

感觉绿/蓝吧。赛时思路：

本题可以注意到 $A,B,C \le 6$ 且“每个测试点不超过 $5$ 个测试数据不满足 $A,B,C \le 3$”。所以考虑暴力一波。

我们可以先考虑枚举 $a$ 的值，不难发现它的取值范围是 $[10^{A-1},10^A-1]$。然后思考如何通过这个求出 $b$ 的值。因为如果 $b$ 确定，那么 $c=a+b$ 也确定。

显然，一个合法的 $b$ 要满足以下条件：

- $b\in[10^{B-1},10^B-1]$。
- $a+b \in[10^{C-1},10^C-1]$。

把两条信息简单结合，可以得出：

$$
b\in[\max\{10^{B-1},10^{C-1}-a\},\min\{10^B-1,10^C-a-1\}]
$$

这样，我们就可以得出 $b$ 在确定 $a$ 的时候的取值范围，两者相减后 $+1$ 即可求出合法的 $b$ 的数量。

然后我们就有了一个具体的思路：

- 先枚举 $a$。
- 对于每个 $a$，求出合法的 $b$ 的数量，记为 $g$。
- 如果 $k>g$，那么 $k \rightarrow k-g$；否则输出 $b=\max\{a+10^{B-1}, 10^{C-1}\}+k-1-a$ 的式子。

注意：这里有一个坑点！考虑数据 `2 1 3 1`。

当枚举到 $a=10$ 时，$\max\{10^{B-1},10^{C-1}-a\}=90$，$\min\{10^B-1,10^C-a-1\}=9$，所以 $b \in [90,9]$。

更加恐怖的是，此时我们的程序并不会把 $g$ 取为 $0$，而是取为 $-80$，然后 $k \rightarrow k+80$，并继续运行下去！**所以，我们要把 $g$ 和 $0$ 再取一次 $\max$。**

~~就是这个问题导致我赛时没有 AC。~~

代码如下：

```cpp
#include <iostream>
using namespace std;
#define ll long long
#define int long long
#define for1(i, s, t) for (ll i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second
//#define MAXN 100001

ll read(){
	ll x(0), f(1);
	char ch;
	while ((ch = getchar()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = getchar()) > 47);
	return x * f;
}

void uwrite(ll x){
	ll tmp(x/10);
	if (tmp) uwrite(tmp);
	putchar(x-(tmp<<1)-(tmp<<3)^48);
}

void write(ll x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	uwrite(x);
}

ll pow(int a, int b){
	int res(1);
	while (b--) res *= a;
	return res;
}

int A, B, C;
ll k, sum;

void solve(){
	A = read();
	B = read();
	C = read();
	k = read();
	for1(i, pow(10, A-1), pow(10, A)-1){
		sum = max(min(i+pow(10, B)-1, pow(10, C)-1)-max(i+pow(10, B-1), pow(10, C-1))+1, 0ll);
		if (k > sum) k -= sum;
		else{
			write(i);
			printf(" + ");
			write(max(i+pow(10, B-1), pow(10, C-1))+k-1-i);
			printf(" = ");
			write(max(i+pow(10, B-1), pow(10, C-1))+k-1);
			return;
		}
	}
	write(-1);
}

signed main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	int t(1);
	t = read();
	while (t--){
		solve();
		putchar('\n');
	}

	return 0;
}
 
```


---

## 作者：Dehydration (赞：0)

### 前言：

一道暴力求解题目，根本不到绿题难度。

### 思路：

首先，我们看到这句话：

>Each input file has at most $5$ test cases which do not satisfy $A,B,C\le 3$。

让我们情不自禁的想到暴力枚举。

为了方便，我们枚举 $a+b=c$ 中的 $a$，首先对他的取值范围从小到大（为了字典序）一个一个的枚举，然后通过枚举 $b$ 的范围确定 $c$ 可取的范围，然后一个一个计算，当达到 $k$ 以后就输出即可。

### 代码：


```cpp
//Solution:CF1835A
//Date:2024.3.4
//Author:Dehydration
//power by @luogu

#include<bits/stdc++.h>
#define int long long
using namespace std;
int pw[10]={0,1,10,100,1000,10000,100000,1000000,10000000,100000000};//通过数组方便求出范围
void solve(){
	int a,b,c,k;
    scanf("%lld%lld%lld%lld",&a,&b,&c,&k);
	for(int _a=pw[a];_a<pw[a+1];_a++){//为了字典序，从小到大
		//a+b=c bmin=pw[b] bmax=pw[b+1]-1
		//下面的范围就是对 b的范围和 c的范围取并，因为要两个都达到
		int nowmin=max(pw[b]+_a,pw[c]);
		int nowmax=min(pw[b+1]-1+_a,pw[c+1]-1);
		if(nowmin>nowmax)continue;//要注意这个，等会nowmax-nowmin+1变成负数代码就会直接趋势
		if(nowmax-nowmin+1>=k){
			printf("%lld + %lld = %lld\n",_a,nowmin+k-1-_a,nowmin+k-1);return;
			//用printf方便输出
		}
		k-=nowmax-nowmin+1;//后面减掉，为了判断
	}
	puts("-1");
}
signed main(){
	int T;scanf("%lld",&T);
	while(T--)solve();//简洁的mian包
}
```

---

## 作者：封禁用户 (赞：0)

因为题目说：

不满足 $A,B,C≤3$ 的数据只有 $5$ 组。
所以，我们可以枚举所有的 $A$ 位数，然后每次减去可能的 $B$ 位数的个数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int NN = 10;
int t,a,b,c;
ll k;
ll l[NN] = {0,1,10,100,1000,10000,100000,1000000};
ll r[NN] = {0,9,99,999,9999,99999,999999,9999999};
 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d %lld",&a,&b,&c,&k);
		if(c != max(a,b) && c != max(a,b)+1) {puts("-1");continue;}
		ll ans = k;
		for(ll i = l[a]; i <= r[a]; ++i){
			ll lt = max(l[b],l[c] - i),rt = min(r[b],r[c] - i);
			if(lt > rt) rt = lt - 1;
			if(ans <= (rt - lt + 1)){
				printf("%lld + %lld = %lld\n",i,lt + ans - 1,(i + lt + ans - 1));
				ans = 0;
				break;
			}
			ans -= (rt - lt + 1);
		}
		if(ans > 0) puts("-1");
	}
}
``````

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1835A) & [CF 传送门](//codeforces.com/problemset/problem/1835/A)
# 思路
题目中有句很重要的话：
> Each input file has at most $5$ test cases which do not satisfy $A,B,C\leq3$.

这意味着 $O(10^A)$ 的做法是可行的。

我们可以枚举每个 $a$，枚举范围是 $10^A\sim10^{A+1}-1$。对于每个 $a$ 对应的解法就是 $\max(10^{B-1},10^{C-1}-i)\sim\min(10^B-1,10^C-1-a)$，解法数就是 $\min(10^B-1,10^C-1-a)-\max(10^{B-1},10^{C-1}-i)+1=\min(10^B,10^C-a)-\max(10^{B-1},10^{C-1}-i)$ 种。对于每个 $a$，如果 $k$ 当前还比解法数 $x$ 大，说明最终答案一定不在 $a$ 里，把 $k$ 变成 $k-x$，继续下一轮枚举即可。否则，说明答案一定是 $a$ 开头的第 $k$ 个数，即 $k+\max(10^{B-1},10^{C-1}-i)-1$，停止枚举，直接输出即可。如果枚举完了还没答案，那只能说明无解，输出 $-1$ 了。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t, a, b, c, lg[10], x;
ll k;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> a >> b >> c >> k;
		x = max (a, b);
		if (c != x && c != x + 1) { //不可能有解啊
			cout << "-1\n";
			continue ;
		}
		for (int i = lg[a - 1]; i < lg[a]; ++ i) {
			x = max (0, min (lg[b], lg[c] - i) - max (lg[b - 1], lg[c - 1] - i));
			if (k > x) {
				k -= x;
				continue ;
			}
			k += max (lg[b - 1], lg[c - 1] - i) - 1;
			cout << i << " + " << k << " = " << i + k << '\n';
			goto there; //使程序跳转到 there 的地方继续执行
		}
		cout << "-1\n";
there:
		;
	}
	return 0;
}
```

---

