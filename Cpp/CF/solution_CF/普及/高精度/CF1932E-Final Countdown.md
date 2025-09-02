# Final Countdown

## 题目描述

You are in a nuclear laboratory that is about to explode and destroy the Earth. You must save the Earth before the final countdown reaches zero.

The countdown consists of $ n $ ( $ 1 \le n \le 4 \cdot 10^5 $ ) mechanical indicators, each showing one decimal digit. You noticed that when the countdown changes its state from $ x $ to $ x-1 $ , it doesn't happen in one move. Instead, each change of a single digit takes one second.

So, for example, if the countdown shows 42, then it will change to 41 in one second, because only one digit is changed, but if the countdown shows 2300, then it will change to 2299 in three seconds, because the three last digits are changed.

Find out how much time is left before the countdown reaches zero.

## 说明/提示

In the first example, there are four changes that take 2 seconds: 40 to 39, 30 to 29, 20 to 19, and 10 to 09, other changes take 1 second each. So the total time is $ 2\cdot 4 + 1\cdot(42-4) = 46 $ .

## 样例 #1

### 输入

```
5
2
42
5
12345
2
99
4
0005
27
456480697259671309012631002```

### 输出

```
46
13715
108
5
507200774732968121125145546```

# 题解

## 作者：信息向阳花木 (赞：12)

E 比 D 简单？

位数越高，翻的秒数越多。从右往左数第 $i$ 位，翻的秒数就是 $i$ 秒。

例如样例 $12345$，个位要翻 $12345$ 次，每次一秒。十位要翻 $1234$ 次，在和个位一起翻的同时，每次比个位多用一秒。百位要翻 $123$ 次，在和十位一起翻的同时，每次比十位多用一秒……所以答案就是 $12345+1234+123+12+1$。

所以结论就很明显了。

但是这道题一个个加用高精度会超时，所以不能硬算。可以拆位计算。例如样例 $12345$。
```
12345
 1234
  123
   12
    1
```
我们可以求出数字 $a$ 从高位到低位的每个数字的前缀和 $s$。个位要加的就是 $s_n$，十位是 $s_{n-1}$……模拟一下竖式就可以了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 400010;

int t, n;
string s;
int A[N], C[N], sum[N];
int siz_A, siz_C;

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		siz_A = siz_C = 0;
		
		scanf("%d", &n); cin >> s;
		
		sum[0] = s[0] - '0';
		for (int i = 1; i < s.size(); i ++ )
			sum[i] = sum[i - 1] + s[i] - '0';
			
		int t = 0;
		for (int i = n - 1; i >= 0; i -- )
		{
			t += sum[i];
			C[siz_C ++ ] = t % 10;
			t /= 10;
		}
		if(t) C[siz_C ++ ] = t;
		while (siz_C > 1 && C[siz_C - 1] == 0) siz_C --;
		
		for (int i = siz_C - 1; i >= 0; i -- )
			printf("%d", C[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Z_drj (赞：5)

# 简要题意

把一个数不断减一直到变成零，每个数位变化一次需要一秒。

比如 $300$ 变成 $299$ 需要 $3$ 秒。

求把一个数变成零要多少秒。
# 思路

对于每一位分开讨论它修改的次数发现。

把一个数 $x$ 变成零的总次数其实就是
$\sum \limits _{i=0}^n \lfloor \frac{x}{10^i} \rfloor$ 其中 $n$ 是这个数字的位数。

比如 $12345$ 变化次数

就是 $12345 + 1234 + 123 +12 +1$。

但是数字太大需要使用高精度。

观察发现第 $i$ 位是前 $n-i+1$ 个数的和的个位，所以维护前缀和，然后进行高精度就行。

# code

```c++
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long ;

const int N = 4e5 + 5 ;

char s[N];

void solve(){

    int n;
    scanf("%d",&n);

    scanf("%s",s+1);
    
    std::vector<int> sum(n+10,0);
    std::vector<int> ans(n+10,0);

    for(int i = 1; i <= n; i++) 
        sum[i] = sum[i-1] + s[i]-'0';
    
    std::vector<int> add(n+10,0);
    for(int i = 1; i <= n; i++) {
        int x = (sum[n-i+1] + add[i])/10;

        ans[i] = (sum[n-i+1] + add[i])%10;

        add[i+1] += x; //维护进位
    }

    if(add[n+1])
        ans[n+1] = add[n+1],n++;

    while(ans[n] == 0) n--; //去掉前导零
    for(int i = n; i >= 1; i--)
        printf("%d",ans[i]);

    puts("");
}

int main(){
    
    int t;
    scanf("%d",&t);
    
    while(t--) solve();
    return 0;
}
```

---

## 作者：2huk (赞：3)

### Description

有一个钟表，当前显示的时间是一个 $n$ 位数。

 从当前时刻变道下一个时刻需要花费的时间为发生变化的数位数量。

例如，从 $3200$ 变到 $3199$ 需要花费 $3$ 个单位时间。

求变到 $0$ 的时间。

### Solution

首先可以开贡献做。例如 $12345$：

- 最高位 $1$ 只会变化 $1$ 次，即 $10000 \to 09999$ 时变。
- 第二位 $2$ 会变化 $12$ 次，即 $12000 \to 11999$，$11000 \to 10009$，$10000 \to 09999$，$09000 \to 08999$，$08000 \to 07999$，$07000 \to 06999$，$06000 \to 05999$，$05000 \to 04999$，$04000 \to 03999$，$03000 \to 02999$，$02000 \to 01999$，$01000 \to 00999$ 时变。
- 第三位 $3$ 会变化 $123$ 次；
- 第四位 $4$ 会变化 $1234$ 次；
- 第五位 $5$ 会变化 $12345$ 次。

不难发现就是原数的每个前缀的和。例如 $12345$ 的答案为 $1 + 12 + 123 + 1234 + 12345$。

再拆贡献，还是 $1 + 12 + 123 + 1234 + 12345$ 的例子：

- 最高位 $1$ 的贡献次数为 $1 + 10 + 10^2 + 10^3 + 10^4 = 11111$，贡献为 $11111 \times 1 = 11111$；

- 第二位 $2$ 的贡献次数为 $1 + 10 + 10^2 + 10^3 = 1111$，贡献为 $1111 \times 2 = 2222$；
- 第三位 $3$ 的贡献次数为 $1 + 10 + 10^2 = 111$，贡献为 $111 \times 3 = 333$；
- 第四位 $4$ 的贡献次数为 $1 + 10 = 11$，贡献为 $11 \times 2 = 22$；
- 第五位 $5$ 的贡献次数为 $1$，贡献为 $1 \times 5$。

所以总答案为 $11111 + 2222 + 333 + 44 + 5 = 13715$。

列竖式就是：

```none
    5
   44
  333
 2222
11111
-----
13715
```

所以可以按位计算：

- 个位上是原数的数位和，即 $1 + 2 + 3 + 4 + 5 = 15$；
- 十位上是原数的前 $4$ 位和，即 $1 + 2 + 3 + 4 = 10$；
- 百位上是原数的前 $3$ 位和，即 $1 + 2 + 3 = 6$；
- 千位上是原数的前 $2$ 位和，即 $1 + 2 = 3$；
- 万位上是原数的前 $1$ 位和，即 $1$。

所以可以维护前缀和（实际上按照数位反转后就是后缀和）计算答案的每一位，然后处理进位即可。

### Code

```cpp
void solve() {
	int n = read(), suf = 0;
	vector<int> a(n), res(n + 1, 0);
	fup (i, 0, n - 1) {
		char c;
		cin >> c;
		a[i] = c - '0';
		suf += a[i];
	}
	
	reverse(a.begin(), a.end());
	
	fup (i, 0, n - 1) {
		res[i] = suf;
		suf -= a[i];
	}
	
	int fin = n;
	fup (i, 0, n - 1) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	
	while (!res[fin] && fin) fin -- ;
	
	fdw (i, fin, 0) cout << res[i];
	puts("");
}
```

---

## 作者：apiad (赞：2)

暴力显然不行，考虑每一位的贡献。

我们可以看下面的表直观理解，第一行是个位，第二行是十位，以此类推。

$1\ 2\ 3\ 4\ 5\ 6$

$\ \ \ 1\ 2\ 3\ 4\ 5$

$\ \ \ \ \ \ 1\ 2\ 3\ 4$

$\ \ \ \ \ \ \ \ \ 1\ 2\ 3$

$\ \ \ \ \ \ \ \ \ \ \ \ 1\ 2\ $

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1\ $

显然，这一位的贡献是他上一位除以十。

我们如何计算呢？

我们可以从下往上去推，上面一行是下面一行 $\times 10$ 再加上接上来的那一位。然后直接将答案累计，用到高精度的加法，后面再跑一下进位即可。

由于进位可能会比原来的长度大，所以我预留多了 $20$ 位。

```cpp
//Author: gsczl71
//Copyright (c) 2024 gsczl71 All rights reserved.

#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define endl '\n'
#define debug puts("AK IOI")
#define re register
#define pb push_back
#define mem(a,x) memset((a),(x),sizeof(a))
#define vi vector<int>
using namespace std;
//#define int long long
const int mod = 1e9+7;
//const int mod = 998244353;
const int inf = 0x3f3f3f3f,N = 4e5+5,M = 2e5+5;
const ll linf = 0x3f3f3f3f3f3f3f3f;
string s;
int a[N];
void solve(){
	int n;cin>>n>>s;
	for(int i=1;i<=n;i++){
		a[i+20]=a[i+19]+s[i-1]-'0';
		
	}
	// for(int i = 1;i <= 3;i++) cout<<a[i];
	for(int i = n+20;i >= 1;i--){
		a[i-1] += a[i] / 10;
		a[i] %= 10;
	}
	int flag=1;
	for(int i = 1;i <= n + 20;i++){
		if(!a[i]&&flag){
			continue;
		}flag=0;
		cout<<a[i];
		a[i]=0;
	}cout<<endl;
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	cin >> T;
	while(T--) solve();
	return 0;
}

```

---

## 作者：SY_nzwmb83 (赞：2)

### 题意

对于 $n$ 位的数 $x$，求出从 $x$ 每次减一直到 $0$ 的过程中，数位变化的次数。

### 分析

首先每次个位的数位必然是变化的，十位的数每隔 $10$ 发生一次变化，所以一共发生 $\lfloor \frac{x}{10} \rfloor$ 次变化，百位的数每隔 $100$ 发生一次变化，所以一共发生 $\lfloor \frac{x}{100} \rfloor$ 次变化，以此类推。这些次数其实就是 $x$ 从低位依次去掉若干位后的数，最后只要把这些数加起来即可。

由于 $x$ 很大，考虑高精度。如果列竖式就可以发现个位上的数（进位前）就是 $x$ 每个数位之和，而十位则是 $x$ 除去个位后每个数位之和，以此类推。考虑前缀和，先求出 $x$ 从最高位一直到各位的数位和，记录到答案中。最后只要进行进位就行了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int tt,a[400005],q[400005],ans[400005];
char s[400005];
void solve()
{
	int n;
	cin>>n;
	q[0]=0;
	ans[n+1]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];//直接按数位读入
		a[i]=s[i]-'0';
		q[i]=q[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
	{
		ans[i]=q[n-i+1];//倒序方便进位
	}
	for(int i=1;i<=n;i++)//进位
	{
		if(ans[i]>=10)
		{
			ans[i+1]+=(ans[i]/10);
			ans[i]=ans[i]%10;
		}
	}
	int cnt=n+1;
	while(!ans[cnt])//去前导零
	{
		cnt--;
	}
	for(int i=cnt;i>=1;i--)
	{
		cout<<ans[i];
	}
	cout<<'\n';
	return;
}
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>tt;
	while(tt--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：vorDeal (赞：1)

数学不好，没能场切。

每翻动一位，就需要一个单位的时间。个位上的数字变动一次翻一次，十位上的数字变动十次翻一次……推知：从右往左第 $i$ 位的数字，变动次数为 $\lfloor k/10^{i-1} \rfloor$。

现在，记 $k=\overline{a_1a_2 \dots a_n}$。于是，我们得到，总时间 $t=a_1+\overline{a_1a_2}+\overline{a_1a_2a_3}+\dots+\overline{a_1a_2 \dots a_n}$。

$\sum n \leq 4\times10^5$，需要使用高精度，而暴力会超时。对式子进行化简，得到 $t=\sum\limits_{i=1}^n 10^{i-1}\sum\limits_{j=1}^{n-i+1}a_j$。考虑对每一位上的数字进行前缀和，再进行进位、去前缀零即可。

注意数位高低位顺序经常需要调换。

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5;

bool flag;
int n, t, s[maxn], p;
string k;

int main()
{
    cin >> t;
    while (t--)
    {
        memset(s, 0, sizeof(s));
        cin >> n >> k;
        p = 0;
        for (int i = 0; i < n; i++)
            s[i] = (i == 0 ? 0 : s[i - 1]) + (k[i] - '0');
        reverse(s, s + n);
        for (int i = 0; i < n || s[i] > 0; i++, p++)
            if (s[i] >= 10)
                s[i + 1] += s[i] / 10, s[i] %= 10;
        flag = true;
        for (int i = p - 1; i >= 0; i--)
        {
            if (s[i] == 0 && flag == true)
                continue;
            cout << s[i];
            flag = false;
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先就拿样例二 $12345$ 来看吧。万位没啥好说，肯定只要转 $1$ 次。千位，从 $12345\to02345$ 需要转 $1\times10=10$ 次，再加上 $02345\to00345$ 的 $2$ 次，共 $12$ 次。剩下的百位、十位、个位则分别是 $123,1234,12345$ 次。所以答案就是把这个数的每个前缀都加起来。然后暴力加前缀是不可取的，我们列个数据会发现，这个数也可以通过 $11111+2222+333+44+5$ 来计算。然后我们差分一下，然后高精度进位就好。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, ans[400005], x;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> a;
		for (int i = 0; i <= n; ++ i)
			ans[i] = 0;
		for (int i = 0; i < n; ++ i) {
			x = a[n - i - 1] - '0';
			ans[0] += x, ans[i + 1] -= x;
		}
		for (int i = 0; i < n; ++ i)
			ans[i + 1] += ans[i];
		for (int i = 0; i < n; ++ i)
			ans[i + 1] += ans[i] / 10, ans[i] %= 10;
		while (! ans[n])
			-- n;
		while (~n)
			cout << ans[n], -- n;
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

## 题目大意

输入 $t$ 个 $n$ 位数 $k$，求将 $n$ 变为 $0$ 每一位的变化次数和。

## 思路

首先我们举一个例子，当 $n$ 为 $7$ 且 $k$ 为 $1234567$ 时，变化的总数就是 $1234567+123456+12345+1234+123+12+1$ 显然，规律已经出现了。接下来我们就要将它们计算出来：

我首先想到的是将每一个数都存上然后再进行高精度运算，可看到这数据范围，明显，这条路行不通。这时候我们就需要用到我们之前学到过的一个东西——前缀和。从最高位开始，每一个都是前面的前缀和。

最后再处理一下进位和前导零就完成了。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=4*1e5+5;
long long t;
long long n;
string s;
long long a[N];
int main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		cin>>n;
		cin>>s;
		for(int i=n;i>=1;i--)
			a[i]=a[i+1]+(s[n-i]-'0');
		for(int i=1;i<=n;i++) a[i+1]+=a[i]/10,a[i]%=10;
		while(a[n+1]!=0) n++;
		while(a[n]==0) n--;
		for(int i=n;i>=1;i--) cout<<a[i];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：wangxinyi2010 (赞：0)

### Solution
（英文版题干也太刺激了）

本题难度：CF：1600，洛谷上对应绿题（稍微有点水）。此题的标签包括模拟、数学、数论。

很明显，暴力的方法一定过不了，必须要推出公式。   
从较简单的情况入手。
- 若此数个位上的数字为 $a$。则很显然，此数位从 $a$ 变为 $0$ 需要 $a$ 秒时间。
- 若此数十位上的数字为 $b$，个位上是 $0$，则十位从 $b$ 变为 $(b-1)$ 需要 $1$ 秒时间，而个位需要 $10$ 秒。因此，十位从 $b$ 变为 $0$ 需要 $11b$ 秒时间。
- 因此，若这个数从个位起第 $x$ 位上的数字为 $c$，前 $x-1$ 位是 $0$，则可知第 $x$ 位从 $c$ 变为 $0$ 需要 $c\,\cdot\,\sum^{x-1}_{i=0}10^i$ 秒时间。
- 最后再把每一位的结果相加，即可得到最终总和。

通过列加法竖式可知，最终结果每一位上的数都是输入的数从最高位开始到当前数位的所有数字的总和，注意现在还没有进位。这一步很明显要用前缀和实现。

最后再使用与高精加类似的方法进位即可，注意最高位是否还要进位。

注意输入样例的第四组测试数据有前导零，因此一定要**删除前导零**。

时间复杂度为 $\Omicron(n)$。
### AC Code
```cpp
#include<iostream>
#include<cstring> 
using namespace std;
#define maxn 400005
int t,n,k[maxn];
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		memset(k,0,sizeof(k));//清空总和
		cin>>n;
		for(int j=1;j<=n;j++){
			char c;
			cin>>c;
			k[j]=k[j-1]+c-'0';
		}
		int t=0;
		for(int j=n;j>=1;j--){
			k[j]+=t;
			t=k[j]/10;
			k[j]=k[j]%10;
		}
	    if(t) cout<<t;
	    int j=1;
	    while(k[j]==0&&t==0) j++;
	    for(;j<=n;j++) cout<<k[j];
	    cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1932E
## 题意
给定一串数字，将它倒计时到零，求每一位数字一共变化了多少次。
## 思路
先研究一下第二组样例 $12345$，很明显万位变化了 $1$ 次，千位变化了 $12$ 次，百位变化了 $123$ 次，十位变化了 $1234$ 次，个位变化了 $12345$ 次。从而得出结论：第 $i$ 位变化的次数 $=$ 给定数字 $1 \sim i$ 位的数。所以，我们只要先计算从前往后每一位的和，而 $1 \le n \le 4 \times 10 ^ {5}$，所以要使用高精度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int t,n,a[N];
string s;
int main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		cin>>n>>s;
		reverse(s.begin(),s.end());
		int i=s.size()-1;
		while(s[i]=='0')i--,n--;//删除前导零 
		for(int i=0;i<n;i++)a[i]=s[i]-'0';
		for(int i=n-2;i>=0;i--)a[i]+=a[i+1];//前缀和 
		for(int i=0;i<n;i++){
			if(a[i]>=10){//进位 
				if(i==n-1)n++; 
				a[i+1]+=a[i]/10;
				a[i]%=10;
			}
		}
		for(int i=n-1;i>=0;i--)cout<<a[i];
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

[CF1932E Final Countdown](https://www.luogu.com.cn/problem/CF1932E)

### 思路

考虑每一位上的数字跳动一次，可以看作把这一位减 $1$。

如果我们要在第 $t$ 位上的数字减一，那么第 $t$ 位要转动 $1$ 秒，显然这会执行 $t\sim n$ 位组成的数的次数。因为 $1\sim t-1$ 位没有影响，此时可以看作 $t\sim n$ 位组成的数可以减多少次 $1$。于是我们对每一个 $t$，划分出对应的次数，然后加和即可。

实现时，可以看作把第 $i$ 位上的数值加到答案的第 $1\sim i$ 位上，这与上述加和方式显然等价，最后处理一下即可。

时间复杂度 $O(\sum n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=400015;
int t,n;
std::string s;
struct Bigint{
	int a[N],len;
	inline int& operator[](int i){return a[i];}
	inline void flatten(int L){
		len=L;
		for(int i=1;i<=len;++i){a[i+1]+=a[i]/10;a[i]%=10;}
		for(;!a[len]&&len>1;--len);//进位处理
	}
	inline void print(){
		for(int i=len;i;--i) cout<<a[i];
	}
}ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<'\n'){
		cin>>n>>s;int sum=0;
		for(int i=1;i<=n+11;++i) ans[i]=0;
		for(int i=0;i<n;++i){
			sum+=s[i]-'0';//将 i~n 组成的数加和等价于把第 i 位的数值加到 1~i 位上
			ans[n-i]=sum;
		}
		ans.flatten(n+11);
		ans.print();
	}
	return 0;
}
```

---

## 作者：fengziyi (赞：0)

题意请见本人提交的翻译。

### 思路

考虑到超长的数数时间和 $n$ 的定义，我们思考一下倒计时的规律，分位计算。

显然当每次减一的退位操作进行时，才会引发高位数字的转动。换而言之，一位的转动次数等价于 $10$ 倍的其高一位的转动次数加上其自身值。

显然，最高位的转动次数等于本身。

综上，我们要求的答案即为该数字所有前缀的和。

例如数字 $123$ 所需时间 $T=1+12+123$。

但是显然长达 $4\times10^5$ 的数字不好加。

观察发现以上例子的计算可以转化为 $111+22+3$ 的计算。

考虑高精度加法的含义，考虑对每一位再次分别计算。

又转化为 $(100)+(10+20)+(1+2+3)$ 的计算。

预处理每一位上的值，做高精进位即可。

令 $V(\le 4\times 10^6)$ 为原数各位之和。时间复杂度 $O(n\log V)$。

```cpp
	rep (i, 1, n)
	{
		char ch; cin >> ch;
		a[i] = ch - '0';
		prv[i] = prv[i - 1] + a[i]; 
	}
 
	reverse(prv + 1, prv + n + 1); 
 
	int d = 0;
 	// 别忘清空 res[]
	rep (i, 1, n) 
	{
		int t = prv[i], cnt = 0;
		while (t)
		{
			res[i + cnt] += t % 10;
			d = max(d, i + cnt);
			if (res[i + cnt] > 9)
			{
				d = max(d, i + cnt + 1);
				res[i + cnt + 1] += res[i + cnt] / 10;
				res[i + cnt] %= 10;
			}
			++cnt;
			t /= 10;
		}
	}
	per (i, d, 1) cout << res[i];
```

### Tips

清空数组的时候别用 `memset()` 每次刷个 $4 \times 10^5$ 够呛。

---

## 作者：无名之雾 (赞：0)

# Final Countdown 题解

~~本来会做的，赛时没开!~~
## 题意

给定你一个十进制数字 $x$，每次当 $x$ 变成 $x-1$ 所需要的时间就是 $x$ 变成 $x-1$ 所改变数字的数量。问一共需要多少时间才可使 $x$ 归零。 

## 思路

假设一开始的数是 $m$，可以看出来最后答案是 $m+(m/10)+(m/100)$....

假如就是 $1234$，写出来就是这样

```
1 2 3 4 
  1 2 3  
    1 2 
      1
```
      
然后拆散成一位一位的，发现从右至左每一位是 $sum-\sum_{i}^{n} x_i$。就是原数的数字和减去他在原数中后缀的数字和。

直接暴力加一遍，发现每一位都在 $10^9$ 以内，然后暴力进位就行。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int s[400005];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main() {
	int t=read();
	while(t--){
		int n=read();
		string str;
		cin>>str;
		for(int i=1;i<=n;i++)s[i]=s[i-1]+str[i-1]-'0';
		string ans="";
		int t=0;
		for(int i=n;i>=1;i--) {
			t+=s[i];
			ans.push_back(t%10+'0');
			t/=10;
		}
		while(t){
			ans.push_back(t%10+'0');
			t/=10;
		}
		while(ans.size()>1&&ans.back()=='0')ans.pop_back();
		reverse(ans.begin(),ans.end());
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

最简单的方法就是模拟，复杂度 $O(10^n)$，大概是我见过的最大的复杂度了。

我们不妨考虑每一位对答案的贡献，以 $114514$ 为例。

首先个位一定是一直在走的，共走了 $114514$ 秒。

再看十位，想要十位动一步，个位先要动 $10$ 步。我们已经得出个位的时间，所以十位的时间就是 $\displaystyle\lfloor\frac{114514}{10}\rfloor=11451$ 秒。

同理，百位就是 $1145$ 秒，千位就是 $114$ 秒。

设当前数为 $n$，长度为 $m$，得出结论：

$$ans=\displaystyle\sum \limits_{i=0}^{m-1}\lfloor\frac{n}{10^i}\rfloor$$

这里你可以使用高精度，但是很遗憾，一次加法的复杂度为 $O(n)$，总复杂度 $O(n^2)$，你是过不去的。

既然我们开始的数已经按每一位考虑了，那么答案也按位考虑就行了。我们将式子计算出来，列成一个竖式：

$$1\ 1\ 4\ 5\ 1\ 4$$
$$\ \ \ 1\ 1\ 4\ 5\ 1$$
$$\ \ \ \ \ \ 1\ 1\ 4\ 5$$
$$\ \ \ \ \ \ \ \ \ 1\ 1\ 4$$
$$\ \ \ \ \ \ \ \ \ \ \ \ 1\ 1$$
$$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1$$

随后你会发现个位的数加上了十位至十万位的数的和。也就是 $1+1+4+5+1$，十位则加上了 $1+1+4+5$，以此类推。我们发现这就是一个前缀和而已，预处理一下，再每位进行累加。

由于每一位可能会大于 $10$，所以我们还需要处理进位，并且处理前导零。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[400005],b[400005];
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
    a[0]=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
	  char c;
	  cin>>c;
	  a[i]=c-'0';
	  b[i]=b[i-1]+a[i];
	}
	for(int i=1;i<=n;i++) a[i]+=b[i-1];
	for(int i=n;i>=1;i--)
	{
	  a[i-1]+=a[i]/10;
	  a[i]%=10;
	}
	int f=1;
	for(int i=0;i<=n;i++)
	{
	  if(a[i]!=0) f=0;
	  if(f==0) cout<<a[i];
	}
	if(f==1) cout<<0;
	cout<<"\n";
  }
  return 0;
}
```

---

## 作者：No_Rest (赞：0)

## 思路

神仙找规律题。

可以发现，一个数 $m$ 倒计时时个位变化次数为 $\displaystyle \lfloor \frac{m}{1} \rfloor$ 即 $m$ 次，十位变化次数为 $\displaystyle \lfloor \frac{m}{10} \rfloor$ 次，百位变化次数为 $\displaystyle \lfloor \frac{m}{100} \rfloor$ 次……所以最终答案为 $\displaystyle \sum^{k-1}_{i=0} \lfloor \frac{m}{10^i} \rfloor$，其中 $k$ 是 $m$ 的位数。

然而 $m$ 可能很大，要用到高精度，但是一个个暴力加又会超时。观察 $m = 12345$ 时的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/l14ictmm.png)

一列列竖着看，可以发现答案的个位是 $12345$ 个十百千万各位之和，十位是十百千万各位之和，百位是百千万各位之和……这个显然可以前缀和处理。

于是就结束了。时间复杂度 $\mathcal O(Tn)$。

注意前导 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 4e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, st, sum[maxn];
string s;
void solve(){
	n = read(), cin >> s, st = sum[0] = 0;
	s = ' ' + s;
	for(ll i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (s[i] - '0');//前缀和
	for(ll i = n; i >= 1; --i) sum[i - 1] += sum[i] / 10ll, sum[i] %= 10ll;//进位
	while(!sum[st]) st++;//处理前导 0
	for(ll i = st; i <= n; ++i) printf("%lld", sum[i]);
	putchar('\n');
}
int main(){	
	for(; t; --t) solve(); 
    return 0;
}
```

---

