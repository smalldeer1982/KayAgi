# Sum of Two Numbers

## 题目描述

The sum of digits of a non-negative integer $ a $ is the result of summing up its digits together when written in the decimal system. For example, the sum of digits of $ 123 $ is $ 6 $ and the sum of digits of $ 10 $ is $ 1 $ . In a formal way, the sum of digits of $ \displaystyle a=\sum_{i=0}^{\infty} a_i \cdot 10^i $ , where $ 0 \leq a_i \leq 9 $ , is defined as $ \displaystyle\sum_{i=0}^{\infty}{a_i} $ .

Given an integer $ n $ , find two non-negative integers $ x $ and $ y $ which satisfy the following conditions.

- $ x+y=n $ , and
- the sum of digits of $ x $ and the sum of digits of $ y $ differ by at most $ 1 $ .

It can be shown that such $ x $ and $ y $ always exist.

## 说明/提示

In the second test case, the sum of digits of $ 67 $ and the sum of digits of $ 94 $ are both $ 13 $ .

In the third test case, the sum of digits of $ 60 $ is $ 6 $ , and the sum of digits of $ 7 $ is $ 7 $ .

## 样例 #1

### 输入

```
5
1
161
67
1206
19```

### 输出

```
1 0
67 94
60 7
1138 68
14 5```

# 题解

## 作者：LincW (赞：5)

将 $x$ 的数位和定义为 $\mathrm{d}(x)$。

$n$ 为偶数的情况时，$\mathrm{d}(\frac{n}{2})=\mathrm{d}(\frac{n}{2})$，显然的构造是 $\begin{cases}x=\frac{n}{2}\\y=\frac{n}{2}\end{cases}$

接下来的讨论默认 $n$ 为奇数。

对于 $\left\lfloor\frac{n}{2}\right\rfloor\not\equiv9\pmod{10}$ 的情况，显然 $\mathrm{d}(\left\lfloor\frac{n}{2}\right\rfloor+1)-\mathrm{d}(\left\lfloor\frac{n}{2}\right\rfloor)\le1$，所以 $\begin{cases}x=\left\lfloor\frac{n}{2}\right\rfloor+1\\y=\left\lfloor\frac{n}{2}\right\rfloor\end{cases}$ 是一组合法的构造。

对于 $\left\lfloor\frac{n}{2}\right\rfloor\equiv9\pmod{10}$ 的情况，考虑以下构造方式。

$$\mathrm{solve}(n)=
\begin{cases}(\mathrm{solve}(\left\lfloor\frac{n}{10}\right\rfloor)_x+4,\mathrm{solve}(\left\lfloor\frac{n}{10}\right\rfloor)_y+5)&\left\lfloor\frac{n}{2}\right\rfloor\equiv9\pmod{10}\\(\left\lfloor\frac{n}{2}\right\rfloor+1,\left\lfloor\frac{n}{2}\right\rfloor)&\left\lfloor\frac{n}{2}\right\rfloor\not\equiv9\pmod{10}\land n\equiv 1\pmod{2}\\(\frac{n}{2},\frac{n}{2})&n\equiv 0\pmod{2}\end{cases}$$

这样就把关于 $n$ 的问题转化为了关于 $\left\lfloor\frac{n}{10}\right\rfloor$ 的问题，同时避免了进位对数位和的影响。

但是这个方法有一定问题：每次递归调用 $\mathrm{solve}$ 时，构造出的 $y-x$ 会加 $1$，在多次递归时，$\mathrm{d}(y)-\mathrm{d}(x)>1$。

解决方法就是递归时传入深度 $\mathrm{depth}$，让 $4$ 和 $5$ 交替出现，也就是将构造改为$(\mathrm{solve}(\left\lfloor\frac{n}{10}\right\rfloor)_x+4+(\mathrm{depth}\bmod2),\mathrm{solve}(\left\lfloor\frac{n}{10}\right\rfloor)_y+5-(\mathrm{depth}\bmod2))$。

注：代码实现的 $\mathrm{solve}$ 与文中不同，仅作为参考。

```cpp
#include<iostream>
#define endl '\n'
using namespace std;
typedef long long ll;
pair<int,int> solve(int x,int depth=0)
{
	int y=x/10;
	if((y/2)%10==9)
	{
		pair<int,int> p=solve(y,depth+1);
		return pair<int,int>(p.first*10+4+(depth%2),p.second*10+4+(1-(depth%2)));
	}
	else return pair<int,int>((x-10)/2+1,(x-10)/2+10);
}
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n%2==0)
		{
			cout<<n/2<<" "<<n/2<<endl;
		}
		else
		{
			if((n/2)%10==9)
			{
				pair<int,int> ans=solve(n);
				cout<<ans.first<<" "<<ans.second<<endl;
			}
			else
			{
				cout<<n/2<<" "<<n/2+1<<endl;
			}
		}
	}
	return 0;
}


```


---

## 作者：Mingrui_Yang (赞：1)

这道题让构造 $x,y$。

构造时可以按 $n$ 的每一位去一位一位的构造。  

设 $n$ 的当前位为 $a$。  
当 $a$ 为偶数时，$x, y$ 的当前位就都为 $\frac{a}{2}$。   
当 $a$ 为奇数时，则 $x, y$ 中的一个数为 $\lfloor \frac{a}{2} \rfloor$，另一个为 $\lceil \frac{a}{2} \rceil$（如有多个奇数，不能只分配在一个数上，$x, y$ 错开分配）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int get(int x) {
	int res = 1;
	x /= 10;
	while (x) {
		res *= 10;
		x /= 10;
	}
	return res;
}
void mian() {
	int n;
	cin >> n;
	int w = get(n); // 取最高位 
	bool col = true;
	int x = 0, y = 0;
	while (w) {
		int a = n / w % 10; // 当前位的数 
		if (a % 2 == 0) x = x * 10 + a / 2, y = y * 10 + a / 2; // 记得乘上10 
		else {
			if (col) x = x * 10 + a / 2 + 1, y = y * 10 + a / 2;
			else y = y * 10 + a / 2 + 1, x = x * 10 + a / 2;
			col ^= 1;
		} 
		w /= 10;
	}
	cout << x << " " << y << endl;
	
}
int main() {
	int t;
	cin >> t;
	while (t -- ) {
		mian();
	}
}
```

---

## 作者：xxxalq (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF1788B)&[CF链接](http://codeforces.com/problemset/problem/1788/B)

## 思路分析：

首先一定不能 $O(n)$ 枚举，因为 $1\le n\le10^9$ 且 $1\le T\le10000$。

分类讨论：

1. $n$ 为偶数，直接输出 $\displaystyle\frac{n}{2}$，两个相同的数各数位之和肯定也一样。

2. $n$ 为奇数且 $\displaystyle\frac{n}{2}+1$ 的个位不为 $0$，直接输出 $\displaystyle\frac{n}{2}$ 和 $\displaystyle\frac{n}{2}+1$。

3. $n$ 为奇数且 $\displaystyle\frac{n}{2}+1$ 的个位为 $0$，这也是最难的一种情况。我们可以拆位分析，将 $n$ 的每一位尽量平均的分给 $a$ 和 $b$。

## 代码：

```cpp
#include<iostream>
#include<stack>
using namespace std;
int n;
void slove(){
	stack<int>stk;//用栈存n的每一位
	int cnt=0,a=0,b=0,tmp;//tmp存储当前数位，cnt记录奇偶
	while(n){
		stk.push(n%10);//拆位
		n/=10;
	}
	while(stk.size()){//取位
		tmp=stk.top();
		stk.pop();
		if(tmp%2==0){//如果这一位是偶数，直接均分
			a=a*10+tmp/2;
			b=b*10+tmp/2;
			continue;
		}
		if(cnt%2==0){//偶数a多分一
			a=a*10+tmp/2+1;
			b=b*10+tmp/2;
		}else{//奇数b多分一
			a=a*10+tmp/2;
			b=b*10+tmp/2+1;
		}
		cnt+=1;//计数器
	}
	cout<<a<<" "<<b<<endl;//输出
	return;
}
int main(){
	int T;
	cin>>T;
	while(T--){//T组数据
		cin>>n;
		if(n%2==0){
			cout<<n/2<<" "<<n/2<<endl;//n为偶数直接输出n/2
			continue;
		}
		if((n/2+1)%10!=0){//n为奇数但是(n/2+1)的个位不为0
			cout<<n/2<<" "<<n/2+1<<endl;//直接输出n/2和n/2+1
			continue;
		}
		slove();//第3种情况
	}
	return 0;
}
```

---

## 作者：atomic_int (赞：1)

## 题意：
给定一个数 $n$，找到两个数 $x,y$ 满足：
- $x+y=n$
- $x,y$ 各位数字之和相差 $\leq 1$  

任意输出一种合法的 $x,y$。

## 分析：
分类讨论。
- 如果 $n$ 是偶数，可以令 $x=\frac{n}{2},y=\frac{n}{2}$，显然 $x=y$。
- 如果 $n$ 是奇数：
	- 如果 $\lceil\frac{n}{2}\rceil$ 不是 $10$ 的倍数，令 $x=\frac{n}{2},y=\lceil\frac{n}{2}\rceil$，$x,y$ 各位数字之和相差为 $1$。
    - 如果 $\lceil\frac{n}{2}\rceil$ 是 $10$ 的倍数，考虑将 $n$ 上每位数字分给 $x,y$。对于 $n$ 的第 $i$（第 $1$ 位从 $0$ 算起） 位数字（设为 $k$）：
    	- 如果 $k$ 是偶数，那么 $x=x+\frac{k}{2} \times 10^i,y=y+\frac{k}{2} \times 10^i$
        - 如果 $k$ 是奇数，那么依次为：
        	- $x=x+\lceil\frac{k}{2}\rceil \times 10^i,y=y+\frac{k}{2} \times 10^i$
            - $x=x+\frac{k}{2} \times 10^i,y=y+\lceil\frac{k}{2}\rceil \times 10^i$  
            
这样得到的 $x,y$ 相差 $\leq 1$。

## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ri register int
#define inf64 0x7f7f7f7f
#define endl '\n'
#define SeeFloat(x) fixed << setprecision(x)
using namespace std;
inline void solve() {
    int n; cin >> n;
    if (~n & 1) {
        cout << n / 2 << ' ' << n / 2 << '\n';
    }
    else {
        if ((n / 2 + 1) % 10 != 0) {
            cout << n / 2 << ' ' << n / 2 + 1 << '\n';
        }
        else {
            vector<int> v;
            while (n) {
                v.push_back(n % 10);
                n /= 10;
            }
            bool flag = false;
            int x = 0, y = 0;
            for (int i = 0; i < v.size(); i ++) {
                if (~v[i] & 1) {
                    x += v[i] / 2 * pow(10, i);
                    y += v[i] / 2 * pow(10, i);
                }
                else {
                    if (!flag) { 
                        x += (v[i] / 2 + 1) * pow(10, i);
                        y += (v[i] / 2) * pow(10, i);
                    }
                    else {
                        x += (v[i] / 2) * pow(10, i);
                        y += (v[i] / 2 + 1) * pow(10, i);
                    }
                    flag = !flag;
                }
            }
            cout << x << ' ' << y << '\n';
        }
    }
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int T; cin >> T;
    while (T --)    solve();
	return 0;
}
```

~~建议评黄（（（~~

---

## 作者：FireRain (赞：0)

# 思路

令 $d(i)$ 表示 $n$ 的第 $i$ 上的数字。

那么，我们可以考虑将 $n$ 的每一位都拆分开来。

如果 $d(i) \bmod 2 = 0$，那么我们直接将 $\frac{d(i)}{2}$ 分别放在 $x,y$ 的后面，对于数位和的差不变。

否则，我们依旧想尽量的使 $d(i)$ 被平均的分为两半，但是肯定不行，因为无论怎么分数位和的差都会变化。那么，我们将 $\lceil\frac{d(i)}{2}\rceil$ 交替地放入 $x,y$，第一次会将差变为 $1$，第二次将变为 $0$，所以无论如何差最多为 $1$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

int T;
string n;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--){
		int x = 0,y = 0;
		bool r = false;
		cin >> n;
		for (re int i = 0;n[i];i++){
			int num = n[i] - '0';
			if (num & 1){
				if (r){
					x = x * 10 + num / 2 + 1;
					y = y * 10 + num / 2;
				}
				else{
					x = x * 10 + num / 2;
					y = y * 10 + num / 2 + 1;
				}
				r ^= 1;
			}
			else{
				x = x * 10 + num / 2;
				y = y * 10 + num / 2;
			}
		}
		cout << x << " " << y << "\n";
	}
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路
很简单的一道数学思维题，当这个数的一半的最后一位不是 $9$ 时，直接输出这个数的一半，否则就进行特判。

当这个数末尾为 $9$ 时，它有几个 $9$ 就要去在上面加上其他数去调节。我们发现，要想满足条件，加的数就为 $4$ 和 $5$ 交替组成的数，打一个表，最后加上对应的数就行了。

# code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[10]={0,4,54,454,5454,45454,545454,4545454,54545454,454545454};
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		int k=n/2;
		if(k%10<9||n%2==0){
			if(n%2==0){
				cout<<n/2<<" "<<n/2<<endl;
				continue;
			}
			else{
				cout<<n/2+1<<" "<<n/2<<endl;
				continue;
			}
		}
		else{
			int c=k;
			int cnt=0;
			while(c>0&&c%10==9){
				cnt++;
				c/=10;
			}
			cout<<k+a[cnt]+1<<" "<<k-a[cnt]<<endl;
			continue;
		}
	}
	return 0;
}
```


---

## 作者：FLAMEs_ (赞：0)

针对本题，我们对每一位进行奇偶性讨论。

本文默认 $\text{cur}$ 指目前讨论到的那位，$D_x$ 表示正整数 $x$ 的各位数字之和。

- 当该位是偶数时，直接拆成两个值即可。

- 当该位是奇数时，根据题意，我们必然将 $\text{cur}$ 拆成 $\left \lfloor   \frac{\text{cur}}{2}\right \rfloor$ 与 $\left \lfloor   \frac{\text{cur}}{2}\right \rfloor +1$。由于用了两个值 $\text{ans1,ans2}$ 记录答案，故我们用一个值 $\text{odd}$ 记录 $\text{ans1}$ 是否多一位即可。如此记录的原因是：当 $\text{ans1}=\text{ans2}$ 时，直接将 $(\left \lfloor   \frac{\text{cur}}{2}\right \rfloor +1)\times10^k$ 加给 $\text{ans1}$ 即可，此时记录 $\text{odd}$ 为 $1$,$D_{\text{ans1}}=D_{\text{ans2}}+1$。如果下次再遇到奇数位，直接加给 $\text{ans2}$ 即可，此时 $D_{\text{ans1}}=D_{\text{ans2}}$，更新 $\text{odd}$ 的值为 $0$。

至此，我们构造出了合法的方案，可以直接依照如上方案进行构造。

```cpp
#include <bits/stdc++.h>
using namespace std;
void read(int &x){
	x=0;int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x*=f;
}
int T,n;
int main(){
	read(T);
	while(T--){
		read(n);
		int ans1=0,ans2=0,j1=0,cnt=1;
		int temp=n;
		while(temp){
			int cur=temp%10;temp/=10;
			if(cur&1){
				if(j1){
					ans1=ans1+(cur/2)*cnt;
					ans2=ans2+(cur/2+1)*cnt;
					j1=0;
				}else{
					ans1=ans1+(cur/2+1)*cnt;
					ans2=ans2+(cur/2)*cnt;
					j1=1;
				}
			}else{
				ans1=ans1+(cur/2)*cnt;
				ans2=ans2+(cur/2)*cnt;
			}
			cnt*=10;
		}
		cout<<ans1<<" "<<ans2<<"\n";
	}
	return 0;
}
```


---

## 作者：xzyg (赞：0)

## 题意概述

设 $ f(x) $ 为 $ x $ 上的各个数位之和。

给定一正整数 $ n $，求正整数 $ x,y $ 使得 $ x + y = n $ 且 $ | f(x) - f(y) | \le 1 $。

## Sol 1

显然可以发现，若 $ n $ 的个位不是 $ 9 $，则合法的一种拆分可以是：

$$

\begin{cases}
  & \text{ x = n/2,y = n/2 if } n \bmod 2 = 0 \\
  & \text{ x = (n + 1) / 2,y = (n - 1) / 2 if } n \bmod 2 = 1
\end{cases}

$$

可以这样感性理解：

如果为偶数，可以构造 $ x = y $，显然符合条件。

如果为奇数，则个位可能是 $ 1,3,5,7 $，新数的个位分别为 $ (0,1),(1,2),(2,3),(3,4) $，均不向前借位或进位（不影响前面）。

若 $ n $ 的个位是 $ 9 $，可以将所有后缀 $ 9 $ 与除去后缀 $ 9 $ 的数 $ s $ 单独分开考虑。

由于不包括后缀 $ 9 $，$ s $ 显然可以被合法拆分。

然后再将一堆连续的 $ 9 $ 拆分，一种拆分方案是拆成一堆 $ 4 $ 和 $ 5 $，例如 $ 9999 $ 拆成 $ 4455 $ 和 $ 5544 $。

最后把两步拆分的结果加起来就好了。

### 代码（奇丑无比）：

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm> 
#define ll long long

using namespace std;

struct node{
	ll a, b;
};

ll sum(ll x){
	ll cnt = 0;
	while(x != 0){
		cnt += x % 10;
		x /= 10;
	}
	return cnt;
}

node de(ll n){
	ll a, b;
	ll pos = 1, t = n, cnt = 0;
	while(t > 0){
		if(t % 10 == 9){
			pos *= 10;
			cnt++;
			t /= 10;
		}else{
			break;
		}
	}
	a = (n / pos) / 2;
	b = (n / pos) - a;
	
	
	
	for(ll i = 1; i <= (cnt >> 1); i++){
		a *= 10, b *= 10;
		a += 4, b += 5;
	}
	for(ll i = (cnt >> 1) + 1; i <= cnt; i++){
		a *= 10, b *= 10;
		a += 5, b += 4;
	}
	return (node){a,b};
}

int main(){
	
	ll T;
	cin >> T;
	while(T--){
		ll n;
		cin >> n;
		if(n % 10 == 9){
			if(abs(sum(n/2) - sum(n/2+1)) <= 1){
				cout << n/2 << " " << n/2+1 << '\n'; 
			}else{
				node t = de(n);
				cout << t.a << " " << t.b << '\n'; 
			} 
		}else{
			if(n & 1){
				cout << n/2 << " " << n/2+1 << '\n'; 
			}else{
				cout << n/2 << " " << n/2 << '\n'; 
			}
		}
	}
	return 0;
}
```

## Sol 2

机房大佬的思路 %%%

大概就是对每一位都平均分配，如果当前位是偶数显然可以平均分；对于奇数的情况,如果当前位置是第奇数个奇数，那么就令 $ a $ 取较大的那位值，如果当前位置是第偶数个奇数，那么就令 $ b $ 取较大的那位值。

---

## 作者：Sharpsmile (赞：0)

# Sum of Two Numbers 

## 题目大意
给定 $n\leq 10^9$ ，你需要找到一对 $x,y$ ，使得 $x+y$ 等于 $n$。且 $x,y$ 在十进制下的数位和的差不超过一。

## 题目解法
直接按照位每次平分，奇数的话留下，最后把奇数的位上多出来的 $1$ 在 $x,y$ 轮换分配即可。因为只有这些多出来了 $1$ 的数位有影响，但是平分之后 $x,y$ 承接的多出来的 $1$ 的个数差不超过一。所以符合条件。


---

## 作者：loser_seele (赞：0)

不难发现可以构造出解 $ (\frac{n}{2},n-\frac{n}{2}) $，这个在大多数情况下都合法。

但是这样存在一个问题：如果给定的数是类似于 $ n9 $ 这种形式的（$ n $ 是一个奇数，例如 $ 1299 $，注意这里的 $ n $ 是一个整体，在这个例子中为 $ 129 $），那么上述构造无法出解。于是从 $ \frac{n}{2} $ 往上暴力跳，搜到解则直接记忆化，下次不必重新计算答案，可以通过。

时间复杂度在下面给出了正确性证明。

代码：

[提交记录](https://codeforces.com/contest/1788/submission/192996750)

[upd](https://www.luogu.com.cn/blog/lovely-seele/cf1788b-fixed-version)

---

