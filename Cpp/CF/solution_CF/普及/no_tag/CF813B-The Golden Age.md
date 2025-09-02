# The Golden Age

## 题目描述

Unlucky year in Berland is such a year that its number $ n $ can be represented as $ n=x^{a}+y^{b} $ , where $ a $ and $ b $ are non-negative integer numbers.

For example, if $ x=2 $ and $ y=3 $ then the years 4 and 17 are unlucky ( $ 4=2^{0}+3^{1} $ , $ 17=2^{3}+3^{2}=2^{4}+3^{0} $ ) and year 18 isn't unlucky as there is no such representation for it.

Such interval of years that there are no unlucky years in it is called The Golden Age.

You should write a program which will find maximum length of The Golden Age which starts no earlier than the year $ l $ and ends no later than the year $ r $ . If all years in the interval $ [l,r] $ are unlucky then the answer is 0.

## 说明/提示

In the first example the unlucky years are 2, 3, 4, 5, 7, 9 and 10. So maximum length of The Golden Age is achived in the intervals $ [1,1] $ , $ [6,6] $ and $ [8,8] $ .

In the second example the longest Golden Age is the interval $ [15,22] $ .

## 样例 #1

### 输入

```
2 3 1 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 5 10 22
```

### 输出

```
8
```

## 样例 #3

### 输入

```
2 3 3 5
```

### 输出

```
0
```

# 题解

## 作者：chenlingxi (赞：3)

由题意

易得0<a<log2(1e18)=60

所以直接暴力枚举a，b

然后求出每一种可能的x^ai,y^bj

两两相加x^ai,y^bj之后得到大概3600个整数

sort排序后得到一个个区间

枚举每一个区间，求它与【L，R】的交集的大小

然后结束

---

## 作者：TRZ_2007 (赞：2)

**[题解 【CF813B The Golden Age】](https://www.luogu.com.cn/problem/CF813B)**    
# Solution  
题目大意不需要说了。这里我们考虑枚举 $a,b$，构造出**不是**幸运数字的**满足题目所给区间**的数字，存在一个 ```vector``` 里，然后将 ```vector``` 中的数字排序，依次做差得出幸运数字的最大连续长度就可以了，**注意：这里得出长度应该是两个数字之差再减一，才可以得出它们中间数字的长度**。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define gc getchar
inline ll read() {
	ll c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

ll x,y,l,r;
vector <ll> p; 

int main() {
	x = read(); y = read(); l = read(); r = read();
	for(ll i = 1;;i *= x) {	//构造形如 x^a + y^b 的形式
		for(ll j = 1;;j *= y) {
			if(i + j >= l && i + j <= r) p.push_back(i + j);	//如果满足区间就放到 vector 里面去
			if(r / j < y) break;	//作商之后如果小于 y，就证明乘 y 之后的所有数字都不能满足，跳出循环
		}
		if(r / i < x) break;	//同理
	}
	sort(p.begin(),p.end());
	if(p.size() == 0) printf("%lld\n",r - l + 1);
	else {
		ll ans = max(p[0] - l,r - p[p.size() - 1]);	//边界值不要忘记特判
		for(int i = 1;i < p.size();i++) ans = max(ans,p[i] - p[i - 1] - 1);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：__lcm (赞：1)

### 思路

把在 $[l,r]$ 中的 $x^a+y^b$ 算出来，然后从小到大排序，暴力枚举一遍即可。

### 代码

注意一下首尾的情况。

楼上楼下的代码都很清晰，这里不放了。

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

暴力。

把在 $[l,r]$ 中的 $x^a+y^b$ 的数筛出来，然后先排序，再枚举一下，求出最大值。

这其实没什么难点，同时写代码时要注意：

1.要把乘转化成除，不然可能会爆。

2.注意首尾也要判断。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>sum;
signed main(){
	int x,y,l,r;
	cin>>x>>y>>l>>r;
	for(int i=1;;i*=x){
		for(int j=1;;j*=y){
			if(i+j>=l&&i+j<=r) sum.push_back(i+j);
			if(r/j<y) break;//j*y>r
		}
		if(r/i<x) break;//i*x>r
	}
	if(!sum.size()){
		cout<<r-l+1;return 0;
	}//空
	int maxn=0;
	sort(sum.begin(),sum.end());
	for(int i=0;i<sum.size()-1;i++)
		maxn=max(maxn,sum[i+1]-sum[i]-1);
	maxn=max(maxn,sum[0]-l);maxn=max(maxn,r-sum[sum.size()-1]);//首尾
	cout<<maxn;
	return 0;
}
```

---

## 作者：dingshengyang (赞：0)

+ 吐槽

~~这题翻译有毒，明明是「$x^a$」，写成了「xa」……希望看到的管理修正一下。~~

啊，已经修了，那没事了。

+ 正题

首先，看到 $x\ge2,x^a \le R \le 10^{18}$，果断推出 $a \le 64$（$b$ 同理不超过 $64$），然后算出所有的 $x^a+y^b$，最多 $64^2 = 4096$ 个。然后排序，得到一堆开区间。这里有一个技巧，就是开两个哨兵 $L-1,R+1$。这样如果某一个区间直通 $L$ 或 $R$，就可以有效处理。

+ 代码

没事了吧，够详细了，真写不出来了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long int128;
template<typename T> class Scanner{
	public:
	T read(){
		char ch;T s = 0;bool f = 0;
		while(!isdigit(ch=getchar()))if(ch=='-')f^=1;s=ch^48;
		while(isdigit((ch=getchar())))s=(s<<3)+(s<<1)+(ch^48);
		return f?-s:s;
	}  
	void write(T x,bool first=true){
		if(x==0&&!first)return;if(x < 0)putchar('-'),x=-x;
		write(x/10,false);putchar((x%10)+48);
	}
};//OOP 走火入魔 
Scanner<int128> Scan;
int128 L,R,x,y,ans;
vector<int128> un_lucky;
int128 quick_power(int128 a,int b){
	int128 s = 1;
	while(b){
		if(b&1)s = s*a;
		a = a*a;b >>= 1;
	}
	return s;
}
void init(){
	for(LL i = 1;;i*=x){
		for(LL j = 1;;j*=y){
			if(i+j>=L&&i+j<=R)un_lucky.push_back(i+j);
			if(R/j<y)break;
		}
		if(R/i<x)break;
	}
	un_lucky.push_back(L-1);
	un_lucky.push_back(R+1);
	sort(un_lucky.begin(),un_lucky.end());
}
int main() {
	x = Scan.read();
	y = Scan.read();
	L = Scan.read();
	R = Scan.read();
	init();
	if(un_lucky.size() == 2)Scan.write(R-L+1),exit(0);
	for(int i = 1;i < un_lucky.size();i ++){
		int128 r = un_lucky[i];
		int128 l = un_lucky[i-1];
		r--,l++;
		ans = max(ans,r-l+1);
//		putchar('[');
//		Scan.write(l);
//		putchar(',');
//		Scan.write(r);
//		putchar(']');
//		putchar('\n');
	}
	Scan.write(ans);
	return 0;
}

```

---

## 作者：lzdqwq (赞：0)

### 思路：

暴力枚举在 $[l,r]$ 中的 $x^a+y^b$，然后排序，再求出区间最大值即可。

---

## 作者：jiangruibo (赞：0)

### 思路：
把 $x^a$ 与 $y^b$ **暴力枚举**出来，再排序，就变成了一个**线性**的区间问题，最后区间长度取最大值即可。

### 代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline void read(int& a)
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	a=s*w;
}
void write(int x)
{
    if(x<0)
    {
    	putchar('-'),x=-x;
	}
    if(x>9)
    {
    	write(x/10);
	}
    putchar(x%10+'0');
    return;
}
int a[10010];
int b[10010];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int x,y,l,r;
	read(x),read(y),read(l),read(r);
	int mul1=1;
	int mul2=1;
	int cnt=0;
	for(int i=1;i<=64;i++)
	{
		if(1e18/mul1<x)
		{
			break;
		}
		if(i>1) mul1*=x;
		if(mul1<0)
		{
			break;
		}
		mul2=1;
		for(int j=1;j<=64;j++)
		{
			if(1e18/mul2<y) break;
			if(j>1) mul2*=y;
			if(mul2<0)
			{
				break;
			}
			if(mul1*mul2<0)
			{
				break;
			}
			cnt++;
			a[cnt]=mul2+mul1;
		}
	}
//	for(int i=1;i<=cnt;i++)
//	{
//		cout<<a[i]<<endl;
//	}
	int cnt1=0;
	for(int i=1;i<=cnt;i++)
	{
		if(a[i]>=l&&a[i]<=r)
		{
			cnt1++;
			b[cnt1]=a[i];
		}
	}
	sort(b+1,b+cnt1+1);
	b[0]=l-1;
	b[cnt1+1]=r+1;
	int maxn=-1e9;
	for(int i=1;i<=cnt1+1;i++)
	{
		maxn=max(maxn,b[i]-b[i-1]-1);
//		cout<<b[i]<<" ";
	}
	write(maxn);
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路
直接暴力枚举所有在 $[l,r]$ 区间里的 $x^a+y^b$ 然后排序，最后枚举区间即可。
## 代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
long long x,y,l,r,cani,canj,ans;
vector<long long> s;
int main(){
	cin>>x>>y>>l>>r;
	for(long long i=1;;i*=x){
		for(long long j=1;;j*=y){
			if(i+j>=l&&i+j<=r) s.push_back(i+j);
			if(r/j<y) break;
		}
		if(r/i<x) break;
	}
	if(s.size()==0){
		cout<<r-l+1;
		return 0;
	}
	sort(s.begin(),s.end());
	for(int i=0;i<s.size()-1;i++){
		ans=max(ans,s[i+1]-s[i]-1);
	}
	ans=max(ans,s[0]-l);
	ans=max(ans,r-s[s.size()-1]);
	cout<<ans;
	return 0;
}
```

---

