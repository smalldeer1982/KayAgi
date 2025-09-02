# [ABC363D] Palindromic Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc363/tasks/abc363_d

非負整数 $ X $ を $ 10 $ 進表記(先行ゼロ無し)で表した文字列が回文である時、$ X $ を回文数と呼びます。  
 例えば $ 363,\ 12344321,\ 0 $ はいずれも回文数です。

小さい方から $ N $ 番目の回文数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ N $ は整数
 
### Sample Explanation 1

小さい方から $ 46 $ 番目の回文数は $ 363 $ です。

## 样例 #1

### 输入

```
46```

### 输出

```
363```

## 样例 #2

### 输入

```
1```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000000000000```

### 输出

```
90000000000000000000000000000000009```

# 题解

## 作者：神犇の蒟蒻 (赞：9)

# [ABC363D] Palindromic Number 题解

[洛谷](https://www.luogu.com.cn/problem/AT_abc363_d) [Atcoder](https://atcoder.jp/contests/abc363/tasks/abc363_d) [Vjudge](https://vjudge.net.cn/problem/AtCoder-abc363_d)

## 题意

求第 $n$ 大的回文数（$n\le 10^8$)。

## 方法一（暴力）

枚举所有数，然后判断是不是回文。

代码就不放了，毕竟~~懒得写~~不是正解。

## 方法二（正解）

枚举位数，把这个数表示成几位的第几个回文数的形式，再进行处理。

$1$ 位的回文数有 $9$ 个（ $0$ 额外算）；

$2$ 位的回文数有 $9$ 个；

$3$ 位的回文数有 $90$ 个；

$4$ 位的回文数有 $90$ 个；

$5$ 位的回文数有 $900$ 个；

$6$ 位的回文数有 $900$ 个；

$7$ 位的回文数有 $9000$ 个；

$8$ 位的回文数有 $9000$ 个；

。。。。。。

按照以上规律，写出的转换代码：

```cpp
//把这个数表示成len位的第n个回文数的形式
long long tmp=9;
int len=1;
while(n>tmp){
	n-=tmp;
	++len;
	if(len&1){
		tmp*=10;
    }
}
```

然后直接把 $n$ 贴上去就行了：

```cpp
string ans=to_string(--n);
//这里的ans只是这个回文数的前一半
cout<<ans;
//输出前一半
if(len&1){
	ans.pop_back();
}
//特判一下，不然12321这类奇数位的回文数会像123321一样输出
++ans[0];
//注意是从1开始的
reverse(ans.begin(),ans.end());
cout<<ans;
//翻转一下，然后输出后一半
```

然而：

![](https://cdn.luogu.com.cn/upload/image_hosting/ovzz8s97.png)

错误样例：

$20$

错误输出：

$1$

正确输出：

$101$

原来上面的代码没有考虑前导零，所以需要下面三行：

```cpp
while(ans.size()*2-(len&1)<len){
	ans='0'+ans;
}
```

## AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long n;
	cin>>n;
	if(n--==1){//特判0的情况
		cout<<0;
		return 0;
	}
	//把这个数表示成len位的第n个回文数的形式
	long long tmp=9;
	int len=1;
	while(n>tmp){
		n-=tmp;
		++len;
		if(len&1){
			tmp*=10;
	    }
	}
	string ans=to_string(--n);
	//这里的ans只是这个回文数的前一半
	cout<<ans;
	//输出前一半
	if(len&1){
		ans.pop_back();
	}
	//特判一下，不然12321这类奇数位的回文数会像123321一样输出
	++ans[0];
	//注意是从1开始的
	reverse(ans.begin(),ans.end());
	cout<<ans;
	//翻转一下，然后输出后一半
	return 0;
}
```

---

## 作者：ikunTLE (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc363_d)

### 思路

本题要求的是第 $n$ 个回文数，暴力无法通过。但是我们可以先用暴力求出从 $1$ 位到 $8$ 位数各有多少个，见下表格（暂且忽略 $0$）：

| 位数 | 回文数个数 |
|:-------:|:-------:|
| $1$ | $9$ |
| $2$ | $9$ |
| $3$ | $90$ |
| $4$ | $90$ |
| $5$ | $900$ |
| $6$ | $900$ |
| $7$ | $9000$ |
| $8$ | $9000$ |

总结一下，当位数为 $k$ 时，有 $9\times10^{\lfloor{\frac{k-1}{2}}\rfloor}$ 个回文数。解释一下原因，这是因为一个回文数可以转化为该数左半边与右半边相等，即左 $\lfloor{\frac{k}{2}}\rfloor$ 位与右 $\lfloor{\frac{k}{2}}\rfloor$ 位相等。

我们可以用上述规律逐步逼近我们的答案，最后将回文数拼接起来，就是我们最终的答案。

**注意事项**

- 如果该数的位数是奇数，那么就只需要计算左半边。

- `long long` 也见祖宗了，需要开 `__int128`。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
__int128 read(){__int128 x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void write(__int128 x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');return;}
int main(){
	__int128 n=read()-2,sum=0,p1=9,wei=0;
	while(true){
		if(wei>0&&wei%2==0)
			p1*=10;
		++wei;
		if(sum+p1>n)
			break;
		sum+=p1;
	}
	n-=sum;
	__int128 p2=1;
	for(int i=1;i<=(wei-1)/2;++i)
		p2*=10;
	__int128 res=n+p2,temp=res;
	if(wei&1)
		temp/=10;
	while(temp)
		res=res*10+temp%10,temp/=10;
	write(res);
	return 0;
}
```

---

## 作者：int_stl (赞：6)

注：修正了一些小错误。

我们直接暴力枚举肯定是不可行的，那么我们考虑一些小技巧。

我们可知，我们只需要知道一个回文数的前半部分就能知道整个回文数，设 $|x|$ 为回文数的长度，那么我们有：

- 当 $|x|$ 为偶数时，长度为 $|x|$ 的回文数个数为 $9 \times 10^{\frac{|x|}{2}}$。

- 当 $|x|$ 为奇数时，长度为 $|x|$ 的回文数个数为 $9 \times 10^{\lceil\frac{|x|}{2}\rceil}$。

那么我们枚举位数 $d$，当 $n$ 小于等于长度为 $d$ 的回文数的个数时，直接输出即可，否则将 $n$ 减去这个个数，继续枚举即可。

时间复杂度 $O(\log^2n)$，其中底数为 $10$。

参考代码如下：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#define int long long
#define pb push_back
using namespace std;
typedef long long ll;
ll n, pw[123];
int m(ll n) {
	pw[0] = 1;
	for (int i = 1; i <= 25; i++) {
		pw[i] = pw[i - 1] * 10;
	}
	if (n < 10) {
		cout << n;
	}
	else {
		int len = 2;
		while (1) { 
			int half = len / 2;
			ll even = 9 * pw[half - 1];
			if (n <= even) {
				string number = to_string(pw[half - 1] + n - 1);
				number[(int)number.size() - 1];
				cout << number;
				reverse(number.begin(), number.end());
				for (int i = 1; i < (int)number.size() ;i++) {
					cout << number[i];
				}
				return 0;
			}
			n -= even;
			half = (len + 1) / 2;
			ll odd = 9 * pw[half - 1];
			if (n <= odd) {
				string number = to_string(pw[half - 1] + n - 1);
				cout << number;
				reverse(number.begin(), number.end());
				cout << number;
				return 0;
			}
			n -= odd, len += 2;
		}
	}
	return 0;
}
signed main() {
	cin >> n;
	int t = m(n - 1);
	return 0;
}
```

---

## 作者：yszkddzyh (赞：3)

注意：为了方便，本文将 $0$ 看作长度为 $0$ 的回文数。

发现回文数有一个小性质：只要确定了该数的前面一半，那么后面一半也就确定了（或者是确定了后面一半，前面的也确定了。但为了方便，我们就用前一条性质）。下面分两种情况讨论长度为 $n$ 的回文数的个数。

当 $n$ 为偶数时，则只需确定前 $\frac{n}{2}$ 个数，所以长度为 $n$ 时回文数的个数就等于 $\frac{n}{2}$ 位数的个数，即 $9 \times 10^{\frac{n}{2}-1}$ 个。

当 $n$ 为奇数时，同理可得回文数个数等于 $\frac{n+1}{2}$ 位数的个数，即 $9 \times 10^{\frac{n+1}{2}-1}$ 个。

事实上，将各个长度对应的回文数个数写下来，就是（$n$ 从 $0$ 开始）：

$$1,9,9,90,90,900,900,9000,9000,\dots$$

然后，我们可以求出排名为 $k$ 的回文数的位数。代码如下：

```cpp
a[0] = s[0] = 1;//a数组记录长度为i的回文数个数
a[1] = a[2] = 9;
for(int i = 3; i <= 35; i++){
	if(i & 1) a[i] = 10 * a[i - 1];
	else a[i] = a[i - 1];//此处求a数组采用递推方法，你想用通项公式我也不拦你
}
for(int i = 1; i <= 35; i++){
	s[i] = s[i - 1] + a[i];//s是a的前缀和，其实不必将s开成数组
	if(s[i] < n) t = i;//代码中的n代表了排名，即k
	else break;
}
ll ws = t + 1, rk = n - s[t];//ws是位数
```

代码中最后一行的 $rk$ 代表的是需要求的回文数在长度为 $ws$ 的回文数中的排名。下面解释求出它的作用。

先给出一个结论：考虑长度为 $ws$ 的回文数中排名为 $rk$ 的回文数，那么它的前一半的数（长度为 $\lceil\frac{n}{2}\rceil$）是第 $rk$ 大的 $\lceil\frac{n}{2}\rceil$ 位数。

举两个例子：第 $5$ 大的 $3$ 位回文数为 $141$，而 $14$ 就是第 $5$ 大的两位数；
第 $30$ 大的 $6$ 位回文数为 $129921$，而 $129$ 就是第 $30$ 大的三位数。

简略证明：由开头讲的小性质，我们只需考虑一个回文数的前一半，又由于数字比大小是从高位到低位，所以前一半大的整个数字就大。所以前一半在**与它位数相同的数**中的排名，就等于整个数在**与它位数相同的数**中的排名。

接着，求长度为 $ws$ 的回文数中排名为 $rk$ 的回文数，就转化成了求第 $rk$ 大的 $\lceil\frac{n}{2}\rceil$ 位数。代码如下：

```cpp
if(ws & 1){//我分类讨论了，你也可以不这样
	ll tmp = rk + Pow(ws / 2) - 1;
	//tmp就是在与前一半位数相同的数中第rk大的数，此处的ws/2实际上是(ws+1)/2-1，Pow函数可求10的次方，为手写
	for(int i = 1; tmp > 0; i++)
		ans[i] = tmp % 10, tmp /= 10;//数位分离，方便输出
	for(int i = (ws + 1) / 2; i >= 1; i--) cout << ans[i];
	for(int i = 2; i <= (ws + 1) / 2; i++) cout << ans[i];//注意i从2开始，因为最中间的数只需输出一遍
}
else{//与上同理
	ll tmp = rk + Pow(ws / 2 - 1) - 1;
	for(int i = 1; tmp > 0; i++)
		ans[i] = tmp % 10, tmp /= 10;
	for(int i = ws / 2; i >= 1; i--) cout << ans[i];
	for(int i = 1; i <= ws / 2; i++) cout << ans[i];
}
```

然后就可以快乐的 AC 了。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, t, a[39], s[39], ans[39];

ll Pow(int x){
	ll res = 1;
	for(int i = 1; i <= x; i++)
		res *= 10;
	return res;
}

int main(){
	
	cin >> n;
	if(n == 1){
		cout << 0;
		return 0;
	}
	a[0] = s[0] = 1;
	a[1] = a[2] = 9;
	for(int i = 3; i <= 35; i++){
		if(i & 1) a[i] = 10 * a[i - 1];
		else a[i] = a[i - 1];
	}
	for(int i = 1; i <= 35; i++){
		s[i] = s[i - 1] + a[i];
		if(s[i] < n) t = i;
		else break;
	}
	ll ws = t + 1, rk = n - s[t];
	if(ws & 1){
		ll tmp = rk + Pow(ws / 2) - 1;
		for(int i = 1; tmp > 0; i++)
			ans[i] = tmp % 10, tmp /= 10;
		for(int i = (ws + 1) / 2; i >= 1; i--) cout << ans[i];
		for(int i = 2; i <= (ws + 1) / 2; i++) cout << ans[i];
	}
	else{
		ll tmp = rk + Pow(ws / 2 - 1) - 1;
		for(int i = 1; tmp > 0; i++)
			ans[i] = tmp % 10, tmp /= 10;
		for(int i = ws / 2; i >= 1; i--) cout << ans[i];
		for(int i = 1; i <= ws / 2; i++) cout << ans[i];
	}
	
	return 0;
}
```

---

## 作者：kkxacj (赞：2)

#### 思路

首先考虑若 $x$ 为 $10^p \times a,0\le p,1 \le a\le 9$，小于 $x$ 的回文数有几个。

由于是回文，我们只考虑前一半的数，后一半就会确定，第 $1$ 位不能取零，那么有 $x-1$ 种选法，其它位数就有 $10$ 种选法，因为**第一位比 $x$ 小**，其它的数怎么取都没事。

能求出这个后，可以通过这个求出答案有几位，即当 $x=10^p,0\le p$ 时，$p$ 有多大后个数第一次大于 $n$，前一位就是答案位数。

然后对于前一半的位数确定答案，后面的由于是对称的所以先不用管，也是每一位找到第一个大于的，然后就做完了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,f[40],o,sum,v[100],cnt,mx,mx1;
signed main()
{
	read(n);
	if(n <= 10)
	{
		print(n-1);
		flush();
		return 0;
	}
	if(n <= 19)
	{
		print(n-10);print(n-10);
		flush();
		return 0;
	}
	f[1] = 10,f[2] = 9;
	sum = 19;
	for(int i = 3;i <= 40;i++)
	{
		f[i] = 9;
		for(int j = 2;j <= (i+1)/2;j++) f[i] *= 10;
		sum+=f[i];
		if(sum>n)
		{
			o = i;
			break;
		}
	}
	for(int i = 1;i < o;i++) n -= f[i];
	for(int i = 1;i <= (o+1)/2;i++)//每一位都去逼近 
	{
		mx = mx1 = 0;
		for(int j = 0;j <= 9;j++)
		{
			if(i == 1 && j == 0) continue; 
			if(i == 1) sum = j;
			else sum = (j+1);
			for(int z = i+1;z <= (o+1)/2;z++) sum *= 10;
			mx = j; 
			if(sum >= n) break;
			mx1 = sum;
		}
		v[i] = v[o-i+1] = mx,n -= mx1;
	}
	for(int i = 1;i <= o;i++) print(v[i]);
	flush();
	return 0;
} 
/*
101
111
121
202
212
222
*/
```

---

## 作者：jiangjiangQwQ (赞：2)

## 题目大意
给出一个正整数 $n$，$1\leq n \leq 10^{18}$，求第 $n$ 个回文数。
## 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/08roct7b.png)

像这种题，打表找规律，我们可以发现位数为 $3$ 和 $4$ 的回文数的个数都为 $90$，以此类推，当然位数为 $1$ 和 $2$ 的情况是例外。然后我们就可以预处理出类似与上面那张图的数组，求一遍前缀和。举个例子，第 $46$ 个回文数是 $363$，也就是三位回文数中的第 $27$ 个，因为位数 $\leq 2$ 的回文数的个数是 $19$，问题就转化成了找位数为 $3$ 的第 $27$ 个回文数，递归求解即可，具体思路在代码注释。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x){
    x<0?x=-x,putchar('-'):0;
    static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
}
inline char read(char &ch){return ch=getchar();}
inline char write(const char &ch){return putchar(ch);}
template<typename type,typename ...T>
inline void read(type &x,T&...y){read(x),read(y...);}
template<typename type,typename ...T>
inline void write(type x,T...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
#define ll __int128
__int128 cnt[71],f[71],weishu,put[71];
ll quick_pow(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1ll) res*=x;
        x*=x;y>>=1ll;
    }return res;
}
void dg(ll x,ll digit,ll pos){
    //x是第几个，digit是位数，pos是填到第几位
    if(digit==1){
        put[pos]=(pos==1?x:x-1);
        return;
    }else if(digit==2){
        put[pos]=put[weishu-pos+1]=(pos==1?x:x-1);
        return;
    }
    for(ll i=(pos==1?1:0);i<=9;i++){
        ll w=(ll)quick_pow(10,(digit+1)/2-1);
        x-=w;
        if(x<=0){
            x+=w;
            put[pos]=put[weishu-pos+1]=i;
            //可以确定这一位是 i
            dg(x,digit-2,pos+1);
            return;
        }
    }
}
signed main(){
    cnt[1]=10;cnt[2]=9;cnt[3]=cnt[4]=90;
    for(ll i=5;i<=70;i++) cnt[i]=cnt[i-2]*10;
    for(ll i=1;i<=70;i++) f[i]=f[i-1]+cnt[i];
    //预处理出位数从 1 到 70 的回文数的个数
    ll n;
    read(n);
    for(ll i=1;i<=10;i++){//特判
        if(n==i){
            write(i-1);
            return 0;
        }
    }
    ll x=lower_bound(f+1,f+70,n)-f;//查询第n个的回文数的位数
    if(f[x]<=n) x++;
    n-=f[x-1];weishu=x;
    //减去 x-1 的回文数的数量，在 x 位的回文数中继续找
    dg(n,weishu,1);//递归
    for(int i=1;i<=weishu;i++) write(put[i]);
    return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

就我一个人写递归吗。

## 思路

### 打表

|$n$|对应的答案|
|:-:|:-:|
|$1$|$0$|
|$2$|$1$|
|$3$|$2$|
|$4$|$3$|
|$5$|$4$|
|$6$|$5$|
|$7$|$6$|
|$8$|$7$|
|$9$|$8$|
|$10$|$9$|
|$11$|$11$|
|$12$|$22$|
|$13$|$33$|
|$14$|$44$|
|$15$|$55$|
|$16$|$66$|
|$17$|$77$|
|$18$|$88$|
|$19$|$99$|
|$20$|$101$|
|$21$|$111$|
|$22$|$121$|
|$30$|$202$|
|$31$|$212$|
|$100$|$909$|
|$101$|$919$|
|$110$|$1001$|
|$111$|$1111$|
|$112$|$1221$|
|$113$|$1331$|
|$200$|$10001$|
|$1000$|$90009$|
|$1100$|$100001$|

不难发现，每一次答案多一位，$n$ 的最高两位要么是 $20$，要么是 $11$，并且答案是奇数位的时候 $n$ 最高两位是 $20$，是偶数位的时候 $n$ 最高两位是 $11$。

然后我们就可以依此写出来一个打表程序。

观察最后一组样例发现有 $35$ 位，因此打表到 $35$ 位即可。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	cout<<"1,";
	for(int i=2;i<=35;i++){
		if(i%2==1){
			cout<<"2";
			for(int j=1;j<=i/2;j++)cout<<'0';
			cout<<',';
		}
		else {
			cout<<"11";
			for(int j=1;j<i/2;j++)cout<<'0';
			cout<<',';
		}
		if(i%4==0)cout<<endl;
	}
	return 0;
}
```
注意到一位数包括 $0$，因此特殊处理。

打表出来的数组是：
```
long long wei[45]= {0,1,11,20,110,
                    200,1100,2000,11000,
                    20000,110000,200000,1100000,
                    2000000,11000000,20000000,110000000,
                    200000000,1100000000,2000000000,11000000000,
                    20000000000,110000000000,200000000000,1100000000000,
                    2000000000000,11000000000000,20000000000000,110000000000000,
                    200000000000000,1100000000000000,2000000000000000,11000000000000000,
                    20000000000000000,110000000000000000,200000000000000000,1000000000000000001};
```

我们在这个序列中找到第一个大于等于 $n$ 的数，就可以确定答案的位数。

然后我们对奇数位和偶数位分开处理。

### 偶数位

不难发现答案为偶数位的 $n$ 取值范围为 $[1.1\times 10^m,2\times 10^m)$（其中 $m\ge 1$）。

所以答案为偶数位的 $n$ 最高位都是 $1$。

所以我们把 $n$ 的最高位去掉得到 $p$，然后把 $p$ 翻转之后拼在后面，根据上面的打表这其实就是答案。

```
void dfs2(int now) {
	if(now>q/2+1)return;
	cout<<n10[now];
	dfs2(now+1);
	cout<<n10[now];
}
```

### 奇数位

奇数位的处理相对麻烦一点。

首先先看答案的最高位（最低位），其实就是 $n$ 的最高位减 $1$（如果 $n$ 最高位是 $1$，答案的最高位是 $9$）。

然后除掉 $n$ 的最高位（如果最高位是 $1$ 则把最高两位一起去掉）得到 $q$，把 $q$ 翻转过来拼到后面，根据打表，加上最高位和最低位就是答案了。

```
void dfs1(int now) {
	if(n10[1]==1&&n10[2]==0&&now==1) {//因为对最高位是 1 的情况过于麻烦，我特判了一下
		bool f=1;
		for(int i=3; i<=cnt; i++) {
			if(n10[i]!=0)f=0;
		}
		if(f) {
			cout<<9;
			for(int i=2; i<q; i++)cout<<0;
			cout<<9;
			return;
		}
		else{
			cout<<9;
			q++;
			dfs1(3);
			cout<<9;
			return;
		}
	}
	int g=0;
	if(now==q/2+1) {
		cout<<n10[now];
		return;
	}
	if(now==1) {
		cout<<n10[now]-1;
	} else cout<<n10[now];
	dfs1(now+g+1);
	if(now==1) {
		cout<<n10[now]-1;
	} else cout<<n10[now];
}
```

## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
long long wei[45]= {0,1,11,20,110,
                    200,1100,2000,11000,
                    20000,110000,200000,1100000,
                    2000000,11000000,20000000,110000000,
                    200000000,1100000000,2000000000,11000000000,
                    20000000000,110000000000,200000000000,1100000000000,
                    2000000000000,11000000000000,20000000000000,110000000000000,
                    200000000000000,1100000000000000,2000000000000000,11000000000000000,
                    20000000000000000,110000000000000000,200000000000000000,1000000000000000001

                   };
//设置最后一个数的意义：防止对于极大的数据找不到要求的位数
long long n;
int flag,n10[25],cnt,q;
void dfs1(int now) {
	if(n10[1]==1&&n10[2]==0&&now==1) {
		bool f=1;
		for(int i=3; i<=cnt; i++) {
			if(n10[i]!=0)f=0;
		}
		if(f) {
			cout<<9;
			for(int i=2; i<q; i++)cout<<0;
			cout<<9;
			return;
		}
		else{
			cout<<9;
			q++;
			dfs1(3);
			cout<<9;
			return;
		}
	}
	int g=0;
	if(now==q/2+1) {
		cout<<n10[now];
		return;
	}
	if(now==1) {
		cout<<n10[now]-1;
	} else cout<<n10[now];
	dfs1(now+g+1);
	if(now==1) {
		cout<<n10[now]-1;
	} else cout<<n10[now];
}
void dfs2(int now) {
	if(now>q/2+1)return;
	cout<<n10[now];
	dfs2(now+1);
	cout<<n10[now];
}
int ans[15]= {0,0,1,2,3,4,5,6,7,8,9};
int main() {
	cin>>n;
	if(n<=10) {
		cout<<ans[n];
		return 0;
	}
	for(int i=1; i<=36; i++) {
		if(wei[i]>n) {
//问题：当 n 取极大值时，如果只是判断 35 位，可能找不到 q 的值
			flag=(i-1)%2;
			q=i-1;
			break;
		}
	}
	while(n) {
		n10[++cnt]=n%10;
		n/=10;
	}
	for(int i=1; i<=cnt/2; i++) {
		swap(n10[i],n10[cnt-i+1]);
	}
	if(flag)dfs1(1);
	else dfs2(2);
	return 0;
}
```
## 为什么可以用递归实现？

因为不难发现一个奇位回文数都是在之前产生的一个奇位回文数两边加上一个相同的数，偶位回文数同理。

这样，我们可以递归把 $n$ 的最高位去掉。因为去掉的是最高位，所以我先把 $n$ 的十进制各位分离，然后通过数组下标实现去除最高位。

---

## 作者：Heldivis (赞：1)

## ABC363 B

看到这个题，先打个表找规律：

```
编号: 答案
   1: 0
   ...
  10: 9
  11: 11
   ...
  19: 99
  20: 101
   ...
 109: 999
 110: 1001
   ...
 199: 9999
```

发现：合法回文数字中，$1$ 位数有 $10$ 个，两位数有 $9$ 个，三位数有 $90$ 个，四位数有 $90$ 个……

进一步发现，$x$ 位和 $x+1$ 位（$x$ 是大于 $1$ 的奇数）的回文数字是相同数量的，其中奇数位的是形如 $\overline{ab\dots yzy\dots ba}$ 这样的不重复个位的回文数，偶数位的是形是形如 $\overline{ab\dots yzzy\dots ba}$ 这样的重复个位的回文数。

这样就可以做题了。

首先预处理出各个位数回文数的数量 $num_i$ 和前缀和 $sum_i$，用二分法找出 $N$ 在 $sum$ 数组里的位置 $pos$ 以确定答案位数：

```cpp
num[1] = 10, num[2] = 9;
// 注意：这里预处理的位数不能正好为 18，如第 1E18 小的回文数就会超出 1E18 的范围。
for (int i = 3; i <= 35; i++) num[i] = (i & 1) ? num[i - 1] * 10 : num[i - 1];
for (int i = 1; i <= 35; i++) sum[i] = sum[i - 1] + num[i];
int pos = lower_bound(sum + 1, sum + 36, n) - sum;
```

考虑相同位数的回文数，其规律为前半部分按照自然数顺序，后半部分按照位数奇偶性反转。

对于前半部分位数为 $len = \lceil\dfrac{pos}{2}\rceil$ 的数，答案的前半部分 $res = 10^{len} + n - sum_{pos} - 1$，即在这个位数本身的基础上，向后数 $n - sum_{pos} - 1$ 个自然数。$n - sum_{pos}$ 的意义是这个为位数中的第 $n - sum_{pos}$ 小的数，$-1$ 是因为要考虑十的整次幂是最小的数。

最后按奇偶性正确翻转，就做完了。时间复杂度 $O(\log n)$，瓶颈在预处理和输出。

[提交记录](https://atcoder.jp/contests/abc363/submissions/55797302)。

---

## 作者：buowen123 (赞：1)

### 题目大意

- 回文数是指正读反读都一样的数，如 $0$，$22$，$29384648392$。
- 给你一个 $n$，求第 $n$ 大的回文数 $x$（$0$ 是第一个回文数）。
- $1 \le n \le 10^{18}$，$n$ 为整数。

### 题目解决

为了方便讨论，以下不考虑 $0$，$n$ 自减 $1$。

$n \le 10^{18}$，直接枚举肯定没有前途。观察样例，发现 $n=10^{18}$ 时 $x$ 只有 $35$ 位，考虑枚举位数。

具体地，考虑计数位数为 $d$ 的回文数的个数 $c_d$。其前 $q=\left\lceil\dfrac{d}{2}\right\rceil$ 位可以自由决定，后面的数字会被前面的数确定。由于最高位非 $0$，所以 $c_d=9 \times 10^{q-1}$。

我们找到第一个 $d$ 使 $c_1+c_2+\dots +c_d\ge n$，则 $x$ 的位数是 $d$。设 $m=n-s_{d-1}$，问题转化为求第 $m$ 小的 $d$ 位回文数。

由于前 $q$ 位可以自由决定，而前 $q$ 位越大 $x$ 越大，所以前 $q$ 位一定是 $10^{q-1}+m$。只需要把这个数反转拼到后面即可，记得讨论 $d$ 的奇偶性。

实现并不需要 int128，但是用了没坏处。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i1=__int128;
long long n;
i1 ans;
i1 qpow(i1 a,i1 b){
	i1 res=1;
	while(b){if(b&1) res=res*a; a=a*a,b>>=1;}
	return res;
}
i1 find(i1 d){
	if(d==0) return 0;
	return qpow(10,d-1)*9;
}
void out(i1 i,i1 op){
	int stk[200],tt=0;
	while(i){
		stk[++tt]=i%10;
		i/=10;
	}
	for(i1 i=tt;i>=1;i--)
		cout<<stk[i];
	for(i1 i=op;i<=tt;i++)
		cout<<stk[i];
}
void slv(i1 d){
	i1 x=qpow(10,d-1>>1)+n-1;
	out(x,(d&1)+1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n; if(n==1){puts("0"); return 0;} n--;
	for(i1 d=1;d<=36;d++){
		if(find(d+1>>1)>=n){
			slv(d); return 0;
		}
		n-=find(d+1>>1);
	}
	return 0; 
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[abc363d](https://atcoder.jp/contests/abc363/tasks/abc363_d)

# 解题思路

比较无脑的思路。

你考虑到，你只需要确定前半部分的数字也就可以构造出后面的部分使此数字回文。

于是可以进行数位 dp 来进行计数 $1 \sim n$ 中有几个回文数，再二分答案即可。

状态大概是 $dp_{x,0/1}$ 表示考虑到前 $x$ 为目前的数字大小有无填满的方案数。

时间复杂度 $O(\log V \log^2 n)$，其中 $V$ 为答案值域，这里我取了 $10^{36}$。

由于计数的是 $1 \sim n$，所以记得将 $n$ 减去 $1$ 再计算。

注意特判 $n = 1$ 的情况。

# 参考代码


```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
*/
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid (l+r)>>1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll __int128
int t;
string s;
ll a[110],dp[110][2],k,b[110],len,mod=9e18;
void cl()
{
	forl(i,0,108)
		forl(j,0,1)
			a[i]=0,dp[i][j]=-1,b[i]=0;
	len=0;k=0;
}
bool check()
{
	for(int i=k,j=len/2+len%2;i&&j;i--,j--)
		if(b[i]!=a[j])
			return b[i]<a[j];
	return 1;
}
string f(__int128 x)
{
	string s="";
	while(x)
		s+=x%10+'0',x/=10;
	reverse(s.begin(),s.end());
	return s;
}
__int128 Mid;
__int128 L=1,R=1e36;
ll dfs(ll last,bool _1)
{
	if(last==len/2)
	{
		if(_1==0)
			return 1;
		else
			return check();
	}
	if(dp[last][_1]>=0)
		return dp[last][_1];
	ll maxn=_1?a[last]:9,ans=0;
	forl(i,0,maxn)
	{
		if(last==len && i==0)
			continue;
		b[++k]=i;
		ans+=dfs(last-1,_1&&i==maxn)%mod;ans%=mod;
		k--;
	}
	return dp[last][_1]=ans;
}
ll sol(string s)
{
//	cin>>s;
	len=s.size();
	forl(i,0,len-1)
		a[len-i]=s[i]-'0';
	ll ans=0;
	forr(i,len-1,1)
	{
		ll sum=9;
		forr(j,i-1,i/2+1)
			sum*=10,sum%=mod;
		ans+=sum%mod,ans%=mod;
	}
	forl(i,0,105)
		dp[i][0]=dp[i][1]=-1;
	ans+=dfs(len,1)%mod;
	return ans%mod;
}
long long n;
void print(__int128 x)
{
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

void solve()
{
	cin>>n;
	n--;
	if(n==0)
	{
		cout<<0<<endl;
		return ;
	}
	while(L<R)
	{
		cl();
		Mid=(L+R)/2;
		if(sol(f(Mid))<n)
			L=Mid+1;
		else
			R=Mid;//,cout<<"!";
	}
	//L--;
//	print(sol(f(L)));
//	cout<<endl;
	print(L);
}
/*
1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,
*/
int main()
{
//	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：2011FYCCCTA (赞：1)

[原题](https://www.luogu.com.cn/problem/AT_abc363_d)

第一次 abc 无伤切前四题。

---
### 分析

可以先从答案的位数入手。

如何计算答案的位数呢？只需要将 $n$ 依次减去 $1,2,3 \dots$ 位回文数的个数，直到 $n$ 不大于某位回文数个数，此即为答案的位数，设为 $x$。

所以我们现在就需要计算 $i$ 位回文数的个数。

根据回文数的性质，只需关注前 $\lceil \frac{i}{2} \rceil$ 位即可。

最高位有 $9$ 种选择，其余都有 $10$ 种，所以总个数为 $9 \times 10^{\lceil \frac{i}{2} \rceil-1}$。但由于本题将 $0$ 也算做了回文数，所以 $1$ 位回文数有 $10$ 个。

最终的数列是这样的：$10,9,90,90,900,900 \dots$。

接下来就需要确定具体的数值了，设第 $n$ 个回文数是第 $m$ 个位数为 $x$ 的回文数。

那么答案的前 $\lceil \frac{x}{2} \rceil$ 位即为 $10^{\lceil \frac{x}{2} \rceil-1}+m-1$，其中 $10^{\lceil \frac{x}{2} \rceil-1}$ 为最小的 $x$ 位回文数的前 $\lceil \frac{x}{2} \rceil$ 位。

最终输出时把它翻转即可（注意奇回文的情况）。

---
### [代码](https://atcoder.jp/contests/abc363/submissions/55866416)
这是赛时代码改的，变量名比较抽象。我特判的 $0$，所以 $1$ 位回文数数量为 $9$。

---

## 作者：LuukLuuk (赞：1)

# 题解：AT_abc363_d [ABC363D] Palindromic Number

### 题目大意
给定一个 $N$，问你第 $N$ 大的回文数字是多少。

---
### 题解
我认为过于抽象，打了一个表来找规律：（其中“同位编号”指在位数相同的数中该数是第几小的）

![](https://cdn.luogu.com.cn/upload/image_hosting/lxbflz5j.png)

具体算法是先去零的情况，再向高位数枚举在 $N$ 上减去当前位数所符合条件的数的个数，若其大于 $N$ 则表明到达最高位，当前 $N$ 的值即是答案的同位编号，利用当前同位编号计算出结果（详见代码，表格也可以推）。

---
### 代码

```cpp

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;

#define int long long
int n;

signed main() {
	scanf("%lld", &n);
	n--;
	if (n == 0) {
		printf("0");
		return 0;
	}
	for (int i = 1; i; ++i) {//枚举当前位数 
		//逼近答案最高位 
		int len = (i + 1) / 2;//回文用其一半处理 
		int max_last = pow(10, len - 1) * 9ll;//算出当前位答案数 
		if (n > max_last) {
			n -= max_last;//除去 
			continue;
		}
		//最高位 
		//规律：答案的一半是(编号+最高位加一+去零减一) 
		string ans = to_string(max_last / 9 + n - 1);//利用规律将编号变成答案的一半 
		ans.resize(i);//string扩容 
		for (int j = len; j < i; ++j)	ans[j] = ans[i - 1 - j];//利用对称补全另一半 
		cout << ans;
		break;
	} 
	return 0;
}

```

---

## 作者：DengStar (赞：0)

[题目链接](https://atcoder.jp/contests/abc363/tasks/abc363_d)

首先，为了方便，我们不把 $0$ 视作回文数（因此需要特判一下 $n = 1$ 的情况）。

下面要证明：$d$ 位回文数有 $10^{\left\lfloor \frac{d+1}{2} \right\rfloor} - 10^{{\left\lfloor \frac{d+1}{2} \right\rfloor} - 1}$ 个。这里，我们定义 $d$ 位**不含前导零**回文数的数量为 $\operatorname{palin}(d)$，则欲证的命题为 $\operatorname{palin}(d) = 10^{\left\lfloor \frac{d+1}{2} \right\rfloor} - 10^{{\left\lfloor \frac{d+1}{2} \right\rfloor} - 1}$。

（这个数列在 OEIS 上面标号为 [A050683](https://oeis.org/A050683)）

证明这个结论的要点在于：如果一个数是回文数，它就可以由它的“前一半”数位确定。例如，如果已知一个 $8$ 位回文数的前 $4$ 位是 $1827$，那么这个回文数就一定是 $18277281$。所以 $d$ 位回文数的个数，实际上就是“前一半”数位能产生的数的个数。下面以 $d$ 为偶数来讨论。

如果 $d$ 是偶数：$d$ 的前一半数位有 $d / 2$ 位，而 $d / 2$ 位的整数有 $10^{\frac{d}{2}}$ 个，但这些整数有的包含了前导零。包含了前导零的整数的数量，可以看作确定第一位为 $0$，剩下 $d/2 - 1$ 位产生的整数的数量。这个数量是 $10^{\frac{d}{2} - 1}$。综上所述，$d / 2$ 位的**不含前导零的**整数的个数为 $10^{\frac{d}{2}} - 10^{\frac{d}{2} - 1}$。

$d$ 为奇数的情况依法类推。总之，如果把奇偶的表达式合并，就得到了欲证的式子：$\operatorname{palin}(d) = 10^{\left\lfloor \frac{d+1}{2} \right\rfloor} - 10^{{\left\lfloor \frac{d+1}{2} \right\rfloor} - 1}$。

得到这个结论以后，我们枚举位数 $d$，不断从 $n$ 减去 $\operatorname{palin}(d)$，直到 $n \le \operatorname{palin}(d)$，这就说明欲求的回文数的位数是 $d$，并且它是第 $n$ 个 $d$ 位回文数（这里的 $n$ 指的是已经减去了位数小于 $d$ 的回文数个数的 $n$，下同）。

再次运用回文数的性质：回文数可以由它的前一半数位决定。对于 $d$ 位回文数，它的前一半数位就是前 $\left\lfloor \frac{d+1}{2} \right\rfloor$ 位。所以我们只要求出第 $n$ 个不含前导零的 $\left\lfloor \frac{d+1}{2} \right\rfloor$ 位数即可，这点不难实现。求出以后，把它翻转并拼接到自己的末尾，所得的就是欲求的回文数。

[参考代码](https://atcoder.jp/contests/abc363/submissions/55869752)

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑先求出该回文数的位数。

然后依次枚举当前位的值，看一下小于当前的回文数数量，是否超过 $n$ 来决定当前位的值。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,h=9,t,sum;
ll ans[100];
ll check(ll x){
	x=(x+1)/2;
	ll ans=1,t=10;
	while(x--)
	  ans*=t;
	return ans;
} 
bool End;
int main(){
	while(1){
		t=sum=0;
		h=9;
		n=read();
		if(!n)
		  break;
		if(n<=9){
			write(n);
			putchar('\n');
			continue;
		}
		while(1){
			++t;
			sum+=h;
			if(sum>=n){
				sum-=h;
				break;
			}
			if(t%2==0)
			  h*=10ll;
		}
		for(int i=1;i<=t/2;i++){
			ans[i]=10;
			ll start=(i==1?1:0);
			for(int x=start+1;x<=9;x++){
				ll p=check(t-2ll*i);
	//			cerr<<p<<'\n';
				if(sum+p>=n){
					ans[i]=x-1;
					break;
				}
				sum+=p;
			}
			if(ans[i]==10)
			  ans[i]=9;
		}
		for(int i=1;i<=t/2;i++)
		  write(ans[i]);
		if(t&1ll)
		  write(n-sum-1);
		for(int i=t/2;i>=1;i--)
		  write(ans[i]);
		putchar('\n');		
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

我们发现，一个回文数是由两个反转的数拼接而成，所以一个回文数最主要的部分就是前面一半，因为确定了前一半就能确定后一半，整个数就确定了。

现在我们考虑计算 $n$ 位回文数的个数，分奇偶讨论：

- 如果 $n$ 为奇数，那么确定前 $\lfloor (n+1)/2\rfloor$ 个数可确定整个数，共有 $9\times 10^{\lfloor (n+1)/2\rfloor-1}$ 个。

- 如果 $n$ 为偶数，那么确定前 $\lfloor n/2\rfloor$ 个数可确定整个数，共有 $9\times 10^{\lfloor n/2\rfloor-1}$ 个。

枚举位数较低的回文数，代入上式计算，可以得出下面的结论：$n$ 位回文数的个数为 $9\times 10^{\lfloor (n+1)/2\rfloor-1}$。

有了这个结论，我们就能很快找出第 $n$ 个回文数的位数（枚举）。

根据前面回文数由前一半确定的性质，我们还能得到：第 $k$ 小的 $n$ 位回文数前一半为 $10^{x-1}+k-1$。这样我们就能算出题目所求回文数的前一半。

根据回文数的前一半，我们把它反转后与原数拼接，就能得到第 $n$ 个回文数了。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,po[101],d=1;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n,po[0]=1;
	if(n==1){cout<<0;return 0;}
	n--;
	for(int i=1;i<=18;i++)
		po[i]=po[i-1]*10;//10的幂次
	while(1){
		int x=(d+1)/2;
		if(n<=9*po[x-1]){
			string s=to_string(po[x-1]+n-1);
			cout<<s;
			reverse(s.begin(),s.end());
			cout<<s;
			return 0;
		}else n-=9*po[x-1];
		d++;
	}return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

遇到这种题，我们可以先写个暴力找找规律。找规律的过程大家可以自己去探究，下面直接给出结论。

首先我们让 $n$ 的最高位 $-1$，得到一个数 $x$。

- 如果 $n$ 与 $x$ 的位数相同，则答案为 $x$ 正反各写一遍拼起来，**中间位重叠**。
- 如果 $n$ 与 $x$ 的位数差为 $1$，则答案为 $x$ 正反各写一遍拼起来。
- 如果 $n$ 与 $x$ 的位数差大于 $1$，则令 $y$ 为 $n$ 的第二高位 $-1$（不够就退位），答案为 $y$ 正反各写一遍拼起来，中间位重叠。

这个公式由于实现方式差异，对一位数可能会算错。但 $n$ 为一位数的情况是很简单的，直接输出 $n-1$ 即可。所以把这类情况提前排除掉。剩下的按如上情况分类讨论模拟即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int f(int x){//计算x的位数
	int k=0;
	while(x!=0) k++,x/=10;
	return k;
}
void ff(int x){//倒序输出x
	while(x!=0){ cout<<x%10; x/=10; }
}
int a[1000005],top;
signed main(){
	cin>>n;
	if(n<=10){ cout<<n-1; return 0; }
	int k=0,x=n;
	while(x!=0) x/=10,k++;
	k--;
	x=pow(10,k);
	if(x%10!=0) x++;//pow函数精度会出问题！！！！！
	if(f(n)-f(n-x)>1){       n-=x/10; cout<<n; ff(n/10); }
	else if(f(n)-f(n-x)==1){ n-=x;    cout<<n; ff(n);    }
	else{                	 n-=x; 	  cout<<n; ff(n/10); }
	return 0;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

求第 $n$ 小的回文数（不含前导零）。

## 思路

可以发现，一般地，长度为 $k$ 的回文数有 $9 \times 10^{\lfloor \frac{k - 1}{2} \rfloor}$ 个。特别地，长度为 $1$ 的回文数有 $10$ 个。这样，就可以求出第 $n$ 小的回文数的长度。

接着每一位去判断是哪个数字，第 $i$ 位每增大 $1$，会产生 $10 ^ {\lceil \frac{k}{2} \rceil - i}$ 个比它小的回文数。一般地，每一位要从 $0$ 开始枚举；特别地，当 $i = 1$ 时，要从 $1$ 开始枚举。

注意：当 $n \le 10$ 时需要特判。

## 代码

```cpp
ll a[40] = {0, 10, 9}, ans[40];

ll pw(ll x, ll y) {
	ll ans = 1;
	while(y) {
		if(y & 1) ans *= x;
		x *= x;
		y >>= 1;
	}
	return ans;
}
signed main() {
	ll n = rd(), k = 0, sum = 0;
	if(n <= 10) return cout << n - 1, 0;
	for(ll i = 3, j = 10; i <= 36; i += 2, j *= 10) a[i] = a[i + 1] = 9 * j;
	while(sum < n) sum += a[++k];
	ll tmp = pw(10, (k - 1) >> 1);
	sum -= a[k];
	ans[1] = 1;
	for(ll i = 1; i * 2 - 1 <= k; i++) {
		while(sum < n) {
			ans[i]++;
			sum += tmp;
		}
		ans[i]--;
		sum -= tmp;
		tmp /= 10;
	}
	for(ll i = 1; i * 2 - 1 <= k; i++) cout << ans[i];
	for(ll i = k >> 1; i; i--) cout << ans[i];
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路

数据范围很大，考虑数学方法。

由于我们知道 $n$ 位回文数共有 $9\times10^{\lceil\frac{n}{2}\rceil}$ 个，可以枚举答案的位数。

由于首位不能为零，所以第 $n$ 个 $k$ 位回文数的一半为 $n+10^{\lceil\frac{k}{2}\rceil-1}-1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p(ll a,ll x)//暴力计算a的x次方
{
	ll c=1;
	for(int i=1;i<=x;i++)c*=a;
	return c;
}
void re(ll x)//输出x翻转后的值
{
	while(x)
	{
		cout<<x%10;
		x/=10;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n;
	cin>>n;
	if(n==1)
	{
		cout<<0<<'\n';
		return 0;
	}
	n--;
	for(int i=1;i<=37;i++)
	{
		if(n>9*p(10,i/2+i%2-1))n-=9*p(10,i/2+i%2-1);
		else
		{
			n+=p(10,i/2+i%2-1)-1;
			if(i&1)//分位数奇偶性讨论
			{
				if(n/10)cout<<n/10;
				re(n);
			}
			else
			{
				cout<<n;
				re(n);
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 题意
求第 $N\le 10^{18}$ 个回文数。
# 题解
回文数的构造方法：选一个数，要么是将其倒过来拼在后面，要么最后一位重叠拼起来。

设 $j$ 为 $i\div 2$ 向上取整，那么 $i$ 位的回文数肯定是 $j$ 位数用上述方法拼出来的。

$j$ 位数共有 $10^j-10^{j-1}$ 个（一位数有些特殊，是 $10$ 而不是上面公式得到的 $9$ 个，可以特判 $n-1$ 并将 $n$ 的值减一）。设这个值为 $p$ 吧，如果 $n\le p$，说明答案是由 $j$ 位数得到的。更确切地说，是由第 $n$ 个 $j$ 位数得到的。求第 $n$ 个 $j$ 位数的公式是：$10^{j-1}+n-1$。求得这个数后先输出，接着求它的每一位。如果 $j$ 是奇数，从十位开始倒着输出。否则从个位开始倒着输出。
# 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n;
__int128 p[20];
int main(){
	scanf("%lld",&n),p[0]=1;
	for(int w=1;w<=19;w++)p[w]=p[w-1]*10;
	if(n==1){printf("0");return 0;}
	n--;
	for(int w=1;w<=37;w++){
		int x=(w+1)/2;
		__int128 y=p[x]-p[x-1];
		if(y<n)n-=y;
		else{
			long long k=p[x-1]+n-1;
			printf("%lld",k);
			int t=0,a[20]={0};
			while(k)a[++t]=k%10,k/=10;
			for(int z=1+w%2;z<=t;z++)printf("%d",a[z]);
			return 0;
		}
	}
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
一篇 Python 题解。

题目要我们求第 $n$ 个回文数，注意到 $n \leq 10^{18}$，我们得用 $O(\log n)$ 的时间复杂度解决。

首先不断循环，设当前枚举到的长度为 $len$。

如果 $len \bmod 2 = 1$ 那么长度为 $len$ 的回文串有 $9 \times 10^{\frac{len-1}{2}}$ 个。否则长度为 $len$ 的回文串有 $9 \times 10^{\frac{len}{2}}$ 个。

设长度为 $len$ 的回文串有 $num$ 个，用计数器 $cnt$ 累加这个结果。如果 $cnt+num \geq n$，说明现在位数的回文串个数大于 $n$，那么直接结束循环，否则 $cnt$ 加上 $sum$，并且 $len$ 加上 $1$。

根据回文数的性质，它的左边的一半和右边的一半是相等的，所以我们只需要计算一半的长度即可，即 $\lfloor \dfrac{len+1}{2} \rfloor$，这里设这个值为 $midlen$。

那么，长度为 $midlen$ 的回文数的值应该是 $10^{midlen-1}$。前面 $cnt$ 是小于 $n$ 的（因为 $cnt + num \geq n$ 就结束循环了，但是 $cnt$ 没有加上 $num$）所以 $10^{midlen-1}$ 还要加上 $n - cnt +1$。至此，我们就把回文串的一半给求了出来。

最后，设回文串的一半是 $x$，我们将 $x$ 给反转。如果 $x$ 的长度是偶数，我们就将 $x$ 和反转后的 $x$ 直接给拼接在一起，如果 $x$ 的长度是奇数，那么将 $x$ 和反转后的 $x$（要去掉反转后的 $x$ 的第一位）拼接在一起。 

最后输出这个回文数。
### 代码
```python
def gen(mid,len):
	mid_s=str(mid)
	mid_r=mid_s[::-1]
	if len:
		return int(mid_s+mid_r[1:])
	else:
		return int(mid_s+mid_r)
def find(n):
	cnt=0
	len=1
	while True:
		if len%2==1:
			num=9*10**((len-1)//2)
		else:
			num=9*10**(len//2-1)
		if cnt+num>=n:
			break
		cnt+=num
		len+=1
	rp=n-cnt
	midlen=(len+1)//2
	st=10**(midlen-1)
	middle=st+rp-1
	return gen(middle,len%2==1)

n=int(input())
n-=1
print(find(n))
```

---

## 作者：Alex_smy (赞：0)

## 题意简述
输入 $N$，求第 $N$ 小的回文数。
## 解题思路
要求出第 $N$ 小的回文数，首先要将回文数的原理理解透彻。

所谓回文数，就是从左往右读和从右往左读都相同的数。

那么回文数是怎么来的呢？我们可以先观察下面几个数：

$363$：可以看成是 $36$ 后面接了一个倒着的 $36$（即 $63$），且中间重复的 $6$ 被省略掉了。  
$12344321$：可以看成是 $1234$ 后面接了一个倒着的 $1234$（即 $4321$）。  
$0$：所有的一位数都肯定是回文数。可以看成是 $0$ 后面又接了一个 $0$，重复的一个 $0$ 被省略掉了。

我们发现：所有的回文数无论是奇数位还是偶数位，都是左右对称的；且都可以通过一个更简单的数构造出来。

所以，在枚举回文数时，我们只用枚举能构造出来即可。
## 代码实现
最主要的部分已经被解决了，那么具体怎么实现呢？

首先要确定的是第 $N$ 小的回文数的位数。我们可以用列表法找一下规律：

|回文数的位数|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|回文数的个数|$10$|$9$|$90$|$90$|$900$|$900$|$9000$|$9000$|

我们发现，除了一位数的回文数有 $10$ 个以外，有 $i$ 位的回文数的个数都有 $10^{\frac{n-1}{2}}$ 个。因此可以先预处理。

知道了第 $N$ 小的回文数的位数，那么这个数是由哪个数字构造出来的呢？

我们可以再用一个数组来存放不同位数的回文数中最小的一个回文数是由哪个数构造出来的。这个数组长这样：

|回文数的位数|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|第一个构造数|$0$|$1$|$10$|$10$|$100$|$100$|$1000$|$1000$|

为什么要这样做呢？每两个相邻的数，它们构造出来的两个回文数也必定是相邻的。例如，$35$ 和 $36$ 相邻，则 $353$ 和 $363$ 也是两个相邻的回文数。

根据这个原理，我们就可以知道第 $N$ 小的回文数到底是由哪个数构造出来的了。例如，第 $46$ 个回文数应该有 $3$ 位，是有 $3$ 位的回文数中的第 $27$ 个，它是由 $10+27-1=36$ 构造而来的。

本题数据范围很大，需要开 long long。
### 参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long num[40]; //num[i] 用来存放有 i 位的回文数共有多少个
long long a[45]; //a[i] 用来存放有 i 位的回文数中最小的一个回文数是由哪个数构造出来的
int main(){
	scanf("%lld",&n);
	num[1]=10;
	num[2]=9;
	for(int i=3;i<=36;i++) num[i]=i&1?num[i-1]*10:num[i-1];
	a[1]=0;
	a[2]=1;
	for(int i=3;i<=36;i++) a[i]=pow(10,(i+1)/2-1); //预处理
	long long sum=0;
	for(int i=1;i<=36;i++){
		if(n-sum>num[i]) sum+=num[i]; //位数不够
		else{
			long long x=(n-sum-1)+a[i]; //这个回文数是由 x 构造出来的
			printf("%lld",x);
			if(i&1) x/=10; //计算是否要去掉重叠部分
			while(x){
				printf("%lld",x%10);
				x/=10;
			} //倒序输出一遍
			break;
		}
	}
	return 0;
}
```

---

## 作者：wly09 (赞：0)

好板好板的数位 DP。

## 题意简述

求第 $N$ 个回文数。

## 思路

一眼数位 DP。

定义 DP 数组 $f_{0/1,i}$：
+ $f_{0,i}$ 表示带前导零的 $i$ 位回文数的个数；
+ $f_{1,i}$ 表示不带前导零的 $i$ 位回文数的个数。

转移方程非常简单：

$$
\begin{aligned}
f_{0,i}&=f_{0,i-2}+f_{1,i-2}\\
f_{1,i}&=9\cdot f_{0,i}
\end{aligned}
$$

因为一个 $i$ 位的回文数显然首位和末位相等，中间夹着一个 $i-2$ 位的回文数。

然后随便搞个初值：

$$
\begin{aligned}
f_{0,0}=0&,f_{1,0}=1\\
f_{0,1}=0&,f_{1,1}=10
\end{aligned}
$$

DP 到大概三四十位就够用了。

接下来先确定回文数的位数，然后逐位试填，注意第一次试填从 $1$ 开始，接下来从 $0$ 开始。

具体来说，我们枚举 $f_{1,i}$ 的前缀和数组 $S$，找到 $S_{i}<N\le S_{i+1}$，那么我们要找的就是第 $N-S_{i}$ 个 $i+1$ 位数。然后确定首位，剩下一个找第 $X$ 个 $i-1$ 位回文数（带前导零）的子任务，递归下去即可。

[记录](https://atcoder.jp/contests/abc363/submissions/55807724)

---

## 作者：Hughpig (赞：0)

我们先考虑用某个回文数的前半部分 $H$ 去生成回文数，显然只有两种方法：
* 生成的长度为奇数，即在 $H$ 后面拼接上倒序的 $H$，再删掉 $H$ 最后一位，如 $123$ 可以生成 $12321$。
* 生成的长度为偶数，即在 $H$ 后面直接拼接上倒序的 $H$如 $123$ 可以生成 $123321$。

考虑一个长为 $L$ 的数生成的数长度可以为 $L\times 2-1$ 和 $L\times 2$，长为 $L+1$ 的数生成的数长度可以为 $L\times 2+1$ 和 $L\times 2+2$。而对于长度相同的数进行生成，显然原来更大的数生成的数也更大。

因此，$H$ 越大，生成的数越大。

考虑长为 $L$ 的回文数的个数，显然所有长为 $\lceil\dfrac{L}{2}\rceil$ 的数都能生成长为 $L$ 的回文数，所有答案就是长为 $\lceil\dfrac{L}{2}\rceil$ 的数的个数，就是 $9\times 10^{\lceil\dfrac{L}{2}\rceil-1}$。

然后我们就可以找到第 $N$ 个回文数的长度了，记为 $L$，记所有长度小于 $L$ 的回文数的数量和为 $c$，然后第 $N$ 个回文数前半部分的剩下部分就是 $N-c-1$。

然后把答案转成字符串，进行拼接即可。

代码：

```cpp
/*
*Author: Hughpig
*made in China
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll slowpow(ll a,ll b){
	ll ret=1;
	while(b--)ret*=a;
	return ret;
}

ll get(ll x){
	if(x==1)return 10;
	ll qwq=(x+1)/2;
	return 9ll*static_cast<ll>(slowpow(10,qwq-1));
}

string query(ll x){
	if(x<=10)return to_string(x-1);
	ll l=1,cnt=0;
	while(1){
		ll c=get(l);
		if(cnt+c>=x)break;
		cnt+=c;
		l++;
	}
	ll idx=x-cnt-1,h=(l+1)/2;
	ll st=slowpow(10,h-1);
	string hs=to_string(st+idx);
	if(l%2==0){
		return hs+string(hs.rbegin(),hs.rend());
	}
	else{
		return hs+string(hs.rbegin()+1,hs.rend());
	}
}

int main()
{
    ll n;cin>>n;
    cout<<query(n);
	return 0;
}
```

---

## 作者：Drifty (赞：0)

### Solution

- 先不考虑 $0$，后面特判。
我们会发现位数为 $1$ 的回文数有 $9$ 个，位数为 $2$ 的回文数有 $90$ 个，位数为 $3$ 的回文数有 $900$ 个，以此类推。
- 然后算出这个回文数的位数，再减一减得出与当前位数最小回文数的距离。
- 然后考虑这个回文数的前一半，会发现它就是刚刚算出的距离，因此把它翻折一下即为答案，暴力构造就好。

范围大记得开 `__int128`。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 35;
using ll = __int128_t;
ll find (int64_t idx) {
    ll res, cnt = 0, w = 0, num = 9, p = 1;
    for (; cnt < idx; cnt += num, w ++) if (w > 0 && !(w & 1)) num *= 10;
    idx = idx - (cnt - num) - 1;
    for (int i = 0; i < ((w - 1) >> 1); i ++) p *= 10;
    p += idx, res = p, p /= (w & 1) ? 10 : 1;
    for (; p; p /= 10) res = res * 10 + p % 10;
    return res;
}
inline void print(ll n) {
	if (n > 9) print(n / 10); cout << char(n % 10 + '0');
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
    int64_t n; cin >> n;
	return print(find(n - 1)), 0;
}
```

---

## 作者：cqbzhr (赞：0)

数学题

通过暴力枚举回文数，可以发现下述规律：

1. 如果 $k$ 是奇数，那么 $k$ 个位数的回文数中的 $(k+1) \div 2$ 位数是由 $((k+1) \div 2)$ 个正整数组成。

2. 如果 $k$ 是偶数，那么 $k$ 个位数的回文数中的的 $(k \div 2)$ 位数就包含 $(k \div 2)$ 个位数的正整数。

根据上述规律暴力枚举即可，时间复杂度 $O(\log n)$。
### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r,sum,op;
signed main(){
	cin>>n;
	if(n==1)return cout<<0,0;
	n--;
	for(l=9,sum=0,r=1,op=1;sum<=n;){
		if(sum+l>=n)break;
		sum+=l;
		if(op==0)l*=10,r*=10;
		op^=1;
	}
	n-=sum;
	r+=n-1;
	string s=to_string(r);
	cout<<r;
	reverse(s.begin(),s.end());
	if(op)cout<<s.substr(1,s.size());
	else cout<<s;
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

天波写了个数位 dp，惊恐。

考虑枚举数位 $len$，对 $len$ 的奇偶进行讨论。

- 偶数，那么回文的得是长度为 $\frac{len}{2}$ 的数，也就说会有 $10^{\frac{len}{2}-1} \times 9$ 个方案。

  如果说现在要第 $i$ 小的长度为 $len$ 的方案，那么回文的就是 $i + 1000 - 1$。

- 奇数，那么中间一个选什么都是回文，故方案有 $10^{\lfloor \frac{len}{2} \rfloor-1} \times 9 \times 10$ 个，可以先求出构造出回文的那个子串，然后再求出中心。

[代码](https://atcoder.jp/contests/abc363/submissions/55793447)。

---

