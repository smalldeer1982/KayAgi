# [ABC152D] Handstand 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc152/tasks/abc152_d

正の整数 $ N $ が与えられます。  
 $ N $ 以下の正の整数の組 $ (A,B) $ であって、次の条件を満たすものの個数を求めてください。

- $ A,B $ を先頭に $ 0 $ のつかない $ 10 $ 進数表記で表したときに、 $ A $ の末尾の桁が $ B $ の先頭の桁に等しく、 $ A $ の先頭の桁が $ B $ の末尾の桁に等しい

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- 入力はすべて整数である。

### Sample Explanation 1

条件を満たす正の整数の組 $ (A,B) $ は、 $ (1,1) $, $ (1,11) $, $ (2,2) $, $ (2,22) $, $ (3,3) $, $ (4,4) $, $ (5,5) $, $ (6,6) $, $ (7,7) $, $ (8,8) $, $ (9,9) $, $ (11,1) $, $ (11,11) $, $ (12,21) $, $ (21,12) $, $ (22,2) $, $ (22,22) $ の $ 17 $ 個あります。

## 样例 #1

### 输入

```
25```

### 输出

```
17```

## 样例 #2

### 输入

```
1```

### 输出

```
1```

## 样例 #3

### 输入

```
100```

### 输出

```
108```

## 样例 #4

### 输入

```
2020```

### 输出

```
40812```

## 样例 #5

### 输入

```
200000```

### 输出

```
400000008```

# 题解

## 作者：zjyqwq (赞：6)

### AT4828 [ABC152D] Handstand 2题解
Pascal题解。


------------
#### 解题思路
第一眼看到这题，便想到 $O(n^2)$ 的两重配对。

但是看到 $n≤2×10^5$ ，不经陷入沉思……

——正解分割线——

我们可以用一个桶数组来记录记录一个数的开头和结尾。

后面在用一遍循环，注意后面访问桶数组的时候要反过来访问，原来存储开头的地方用结尾访问，原来存储结尾的地方用开头访问。


------------
#### 代码
```pascal
var
n,i,x,s:longint;
a:array[-1..10,-1..10]of longint;\\定义部分。
 begin
  readln(n);
  for i:=1 to n do
   begin
    x:=i;
    while x>9 do 
     x:=x div 10;\\求i的末尾。
    inc(a[x,i mod 10]);\\累加数组。
   end;
  for i:=1 to n do
   begin
    x:=i;
    while x>9 do 
     x:=x div 10;\\copy一遍。
    inc(s,a[i mod 10,x]);\\倒着访问。
   end;
  writeln(s);\\输出即可。
 end.
```

---

## 作者：StarPatrick (赞：3)

这是一道我们考试的题（我们的教练太勤快，居然在洛谷茫茫题海中找到了这道藏在角落中的题）。当时我用 $O(n^2)$ 的算法枚举 $(A,B)$ 直接爆掉，所以告诉我们：时间很珍贵。

来，废话不多说，下面步入正题。

**第一种方法**  
首先，题目要求的数字对的两个数字，我们只需要知道它们的首尾就行了。

因此，我们可以把 $[1,n]$ 扫一遍，用一个二维桶 $f[i][j]$ 存储首位为 $i$，尾位为 &j& 的数量。

最后，我们就可以计算答案，就是二维桶里所有数字的平方和（因为数对没有位置限制，所以这里是平方）。

时间复杂度 $O(n)$，空间复杂度 $O(1)$

这里代码就不用展示了，因为代码量少，思路清晰简单。

**第二种方法**  
这里如果听懂了上一种方法的可以跳过这种方法，不需要掌握，了解即可，因为一般这样的代码长，思维量大，出错率高，不建议在正式比赛采用。

在了解以下内容时，确保你已经看过[@cqbzljt](https://www.luogu.com.cn/blog/LingWang-Blog/solution-at4828)
的第三种方法。

各位读者可能已经知道，她的方法在考虑 **$i$ 的搭档数首位与 $x$ 相等** 时，复杂度比较高且技巧性强（从十位开始加的确有点冒险，数据一大就废了）。

这里，考虑这种情况的时候，答案其实可以通过数学方法算出来，因为首尾两端已确定，我们可以算出中间数字从而求出个数。

时间复杂度 $O(1)$，空间复杂度 $O(1)$

献上我丑陋的代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define int long long
#define max(a,b) a>b?a:b
int n, L, R, ans, f[15][15], len = 1, i;
int quick(int a, int b)//快速幂
{
	if (b<0)
	{
		return 0;
	}
	if (b==0)
	{
		return 1;
	}
	int mid = quick(a, b/2);
	if (b%2==0)
	{
		return mid*mid;
	}
	else
	{
		return a*mid*mid;
	}
}
signed main()
{
	cin>>n;
	if(n<10){//特判
		cout<<n;
		return 0;
	}
	L = n;
	while (L>=10)
	{
		L/=10;
		len++;
	}
	R = n%10;
	i = (n-quick(10, len-1)*L)/10+1;
	for (int l=1;l<=9;l++)
	{
		for (int r=1;r<=9;r++)
		{
			if (l<L)
			{
				f[l][r] = quick(10, len-1)/9;
			}
			else if (l>L)
			{
				f[l][r] = quick(10, len-2)/9;
			}
			else
			{
				if (r>R)//两种情况
				{
					f[l][r] = i-1+quick(10, len-2)/9;
				}
				else
				{
					f[l][r] = i+quick(10, len-2)/9;
				}
			}
			if(l==r)
			{
				f[l][r]++;
			}
		}
	}
	for (int p=1;p<=9;p++)
	{
		for (int k=1;k<=9;k++)
		{
			ans+=f[p][k]*f[k][p];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Code_Select_You (赞：2)

## 思路:
直接暴力枚举时间复杂度为 $O(n^2)$，会超时。所以看一下题目，答案只与这个数的头和尾有关，所以令 $h_i$ 表示第 $i$ 的数的头，$l_i$ 表示第 $i$ 个数的尾，然后让二维数组 $cnt_{i,j}$ 表示头为 $i$，尾为 $j$ 的数的个数。最后统计答案时直接让答案加上 $cnt_{l_i,h_i}$ 即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;long long ans;
int h[200010],l[200010],cnt[10][10];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		l[i]=i%10;
		int x=i;
		while(x>=10) x/=10;
		h[i]=x;
		cnt[h[i]][l[i]]++;
	}
	for(int i=1;i<=n;++i) ans+=cnt[l[i]][h[i]];
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

首先注意，每一个数字，出了第一位与最后一位，中间的数位彻底无用处。只需要一个表，计有多少数字，第一位是 $a$，最后一位是 $b$。

先对每一个输入数字设 $a$ 为第一位的数字，$b$ 为最后一位；把一个计数数组里的第 $a*10+b$ 位置加1。假设这个统计数组叫 $c$ , 统计完了，答案为
$$-n+\sum^9_{a=1}\sum^9_{b=1}(c[10a+b]c[10b+a])$$

注意要减去$n$，应为一对数字是有序的，但是一对相同的数字不能算两次。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

map<int, int> ht;

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	ll ans = 0;
	int N; cin >> N;
	rep1(i, N) {
		int ld = i%10;
		int v = i;
		while(v/10) v /= 10;
		ht[ld*10+v]++;
	}
	rep1(i, N) {
		int ld = i%10;
		int v = i;
		while(v/10) v /= 10;
		ans += ht[v*10+ld];
	}
	cout << ans << endl;
}

```


---

## 作者：small_john (赞：1)

## 思路

可以发现，方案数只和首位和末位有关。所以可以开个二维数组 $ton$，其中 $ton_{i,j}$ 表示 $1\sim n$ 以内首位为 $i$，个位为 $j$ 的数的个数。

用 $O(n)$ 统计出这个数组。

那么对于一个数首位为首位为 $i$，个位为 $j$ 的数 $x$，答案为 $ton_{j,i}$。把 $1\sim n$ 的答案统计起来就是最后的答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ton[10][10],ans;
int get(int x)//取出首位
{
	int res = 0;
	while(x)
		res = x%10,x/=10;
	return res;
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++)//统计数组
		ton[get(i)][i%10]++;
	for(int i = 1;i<=n;i++)//统计答案
		ans+=ton[i%10][get(i)];
	cout<<ans;
	return 0;
}
```

---

## 作者：zhouzihe (赞：1)

## 1 观察题目
观察题目，发现这道题可以用 dp 做。我们设 $f_{i,j}$ 为首位为 $i$，末位为 $j$ 的数字的个数。则答案为 $\sum\limits_{i=0}^{9}\sum\limits_{j=0}^{9}{f_{i,j} \times f_{j,i}}$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,ans,f[10][10];
int first(int x){
	while(x>=10){
		x/=10;
	}
	return x;
}
int main(){
	cin>>n;
	if(n<10){
		cout<<n;
		return 0;
	}
	for(int i=1;i<=n;i++){
		f[first(i)][i%10]++;
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			ans+=f[i][j]*f[j][i];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：PosVII (赞：1)

**前言**

------------

赛时想到正解，打了一个小时还错了……我的方法和其他人的不太一样，思考难度蓝题（提高+/省选-）吧。

**思路**

------------

我们把这道题看作一个递推。那么每次 $n$ 加一时，我们可以多做出 $([1,n-1],n)+(n,[1,n-1])+(n,n)$ 个选择。

因为 $(x,y)=(y,x)$ 那么我们可以化简式子得：

每次 $n$ 加一时，我们可以多做出 $2\times([1,n-1],n)+(n,n)$ 个选择。

但是，这么搜索只能得 $48$ 分，所以我们要对这个式子进行优化。

**优化**

------------

每一次的 $n$ 是一定的，那么对于 $(n,x)$ 可行的 $x$ 来说，它的首位和末位被确定了，所以对于 $x$ 而言，它要满足如下表的形式。

设 $n$ 的首位和末位为 $h$ 和 $b$，而 $n$ 和 $x$ 的长度为 $lenn$ 和 $lenx$

当 $lenx=lenn$ 且 $b<h$ 时：

$x=\overline{bm(lenm=lenx-2)h}$ ，$(n,x)=10^{lenx-2}$

当 $lenx=lenn$ 且 $b=h$ 时：

$x=\overline{bm(lenm=lenx-2,m\leq \frac{(n \mod 10^{lenn})}{10})h}$ ，$(n,x)=\frac{(n \mod 10^{lenn})}{10}$

当 $lenx<lenn$ 且 $lenx\geq 3$ 时：

$x=\overline{bm(lenm=lenx-2)h}$ ，$(n,x)=10^{lenx-2}$

当 $lenx\geq 3$ 且 $b=h$ 时：

$x=\overline{bh}$ ，$(n,x)=1$

这下所有的情况都列出来了，我们可以发现 $3 \geq lenx \geq lenn-1$ 时，$(n,x)$ 可以直接求出，那么其它的情况也可以特判得到。

当然，记得将每一次得到的 $(n,x)$ 的数量乘二，因为有 $(x,n)$，同时也要判重减一，因为有 $(n,n)$。

最后，如果 $b=0$ 时，$x$ 是不存在的！

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
long long sum=9,n,las,len;
long long l[10]={1,10,100,1000,10000,100000,1000000};
long long suml[10]={1,11,111,1111,11111,111111,1111111};
int main() {
//	freopen("handstand.in","r",stdin);
//	freopen("handstand2.out","w",stdout);
	cin>>n;
	if(n<=9) {
		cout<<n;
		return 0;
	}
	for(int i=10;i<=n;i++) {
		las=0;
		if(l[len]<=i) len++; 
		if(i/l[len-1]>i%10&&i%10!=0) {
			las+=suml[len-2];
		}
		else if(len>=3&&i%10!=0) las+=suml[len-3];
		las*=2;
		if(i/l[len-1]==i%10) {
			las+=((i%l[len-1])/10+1)*2+1;
		}
		sum+=las;
	}
	cout<<sum; 
	return 0;
} 
```

**总结**

------------

此题比较简单，但是一旦错了真的要你调半天。

---

## 作者：Liynw (赞：1)

### 前言

[题目链接](https://www.luogu.com.cn/problem/AT4828)

来一点不一样的方法。

**正解：动态规划 / ~~打表~~数据暴力分析**

考试半小时想出方法，最后输在了两个细节上。

写一篇题解以此纪念。

***

### 打表暴力程序

最开始打的暴力对拍，没想到最后只能交这个上去了。

思路：两层循环枚举两个数，判断是否符合要求。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll ans;
bool check(int x,int y){
	int c=x%10,d=y%10;
	while(x>=10) x/=10;
	while(y>=10) y/=10;
	if(x==d&&y==c) return 1;
	else return 0;
}
int main(){
	//freopen("out1.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		if(!i%10) continue;
		for(int j=1;j<=n;j++){
			if(check(i,j)) {//printf("%d %d\n",i,j);
			ans++;} 
		}
	}
	printf("%lld",ans);
	return 0;
}
```

***

### 动态规划

这个方法很简单啊！！！

$dp_{i,j}$ 代表以 $i$ 开头以 $j$ 结尾的不超过 $n$ 的数的个数。

求一个数字首位的函数：

```cpp
int one(int m){
	while(m>=10) m/=10;
	return m;
}
```

因为要保证 $1\le m\le 9$，所以 $dp$ 开 $10\times 10$ 即可。

最后 $9\times 9$ 的循环枚举满足题意的数量。

因为要求两个数的开头结尾互相对应，所以若一个数以 $i$ 开头，以 $j$ 结尾，那么它就有 $dp_{j,i}$ 个数对。而这样的数一共有 $dp_{i,j}$ 个，根据小学学的可能性总数需要用乘法，可以看出前面是 $i\ldots j$ 数字的数对个数为 $dp_{i,j}\times dp_{j,i}$。答案累加就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,dp[10][10];
int one(int m){
	while(m>=10) m/=10;
	return m;
}
int main(){
	scanf("%d",&n);
	if(n<10){
		printf("%d",n);
		return 0;
	}
	for(int i=1;i<=n;i++) dp[one(i)][i%10]++;
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			ans+=dp[i][j]*dp[j][i];
		}
	}
	printf("%d",ans);
	return 0;
} 
```

***

### 数据分析

考试想到的方法。

方法与 [@CQBZJJH](https://gugeblog.blog.luogu.org/at4828-abc152d-handstand-2-ti-xie) 相同，但是我们俩都是考试的时候想出来的，我只是调代码比他慢啊 awa！！1 ~~这个不要 face 的人竟然说版权是他的，IEE。~~

我来说说这个思路是怎么出来的。

首先第一层循环肯定是枚举 $1\sim n$，看每个数字有多少个数字对。

用第一个程序打表 $2020$，可以得到如下的输出：[Link](https://www.luogu.com.cn/paste/pcgevhwj)

~~等等好像复制不完诶，不过没关系这点够了。~~

然后我们先通览全篇，然后仔细观察一下 $1\sim 9$ 的数字对。

发现如下规律：

设 $x$ 为 $n$ 的首位，$k$ 为 $n$ 的位数。

分析：对于每个数 $i$，因为它的数字对的那个搭档的首尾两个数字已经定下来了，所以，中间夹着的数字就可以分析出：中间没有数字的情况，中间有一个数字的情况，中间有两个数字的情况……也就是说，如果没有 $n$ 的限制，那么这个数有的数字对的数量计算公式就是：$10^0+10^1+10^2+\ldots$。

但是这道题当中是有 $n$ 的限制的（~~不然这道题还有什么意义呢~~），所以就要分析下列三种情况讨论：

**1. 若 $i \bmod 10<x$，即 $i$ 的搭档数首位小于 $x$。**

非常简单的情况，这个时候，中间数字数量可以从 $0$ 取到 $k-2$，而且不管怎么取它的搭档数都不会超过 $n$ 的，因为它的首位小于 $x$，而且位数不会大于 $k$。

所以直接：

$ans←ans+10^{k-2}$

即可。

**2. 若 $i \bmod 10>x$，即 $i$ 的搭档数首位大于 $x$。**

也是非常简单的情况，这个时候，只要此搭档数的位数等于 $k$，就一定会大于 $n$，此点~~显然易证~~，就不需要我多哔哔了吧？所以中间掐头去尾的数字的数量可以从 $0$ 取到 $k-3$，所以可以：

$ans←ans+10^{k-3}$。

**3. 若 $i \bmod 10=x$，即 $i$ 的搭档数首位与 $x$ 相等。**

这个情况就比较复杂了。[@CQBZJJH](https://gugeblog.blog.luogu.org/at4828-abc152d-handstand-2-ti-xie) 奆佬用了很巧妙的方法推出了简洁的式子，但是我太蒟蒻了，不会那些~~花里胡哨的东西~~，所以就有了一个朴素的第二层循环 qwq。

我的想法就是这样的：既然你这个数无法确定位数为 $k$ 的时候到底是否大于 $n$，那么你就一点一点枚举呗！定义第二层循环 $j$ 为中间的数字（$j÷10$ 一定是一个 $k-2$ 位数，位数不够前面补 $0$），其中 $j$ 一定是 $10$ 的倍数（因为要保留最后一位，从倒数第二位开始改），每次枚举时这个 $i$ 的搭档数就是：

$x\times 10^{k-1}+j+\operatorname{one}(i)$

其中 $\operatorname{one}(i)$ 是指求 $i$ 的首位的函数（前面有）。

可以看出，只要这个数小于 $n$，那循环就可以继续下去；但是如果这个数超出了 $n$，因为 $j$ 只会越来越大，不可能后面还有满足的，直接退出循环即可。


最后说一下 $j$ 的枚举范围：$0\sim 10^{k-1}-1$（不能加到首位上去）。

***

### 一个小优化

适用于第三种方法，因为这个方法时间复杂度比较大，所以想到了这个。

试想一下：如果一个数的首位是相同的，那么它的数对的数量就相当于它末尾这个一位数的数对数量。所以，$1\sim 9$ 可以与上面分开枚举，枚举 $i$ 时把答案加在 $b_i$ 里面，最后 $ans←ans+b_i$ 即可。

（**注意一定要考虑和自己组成数对即一位数的情况，所以最后 $b_i$ 需要 $+1$！！！** 考试就栽在这个细节上了。）

其实想到了这个之后，就离想到上述的动态规划简单做法不远了……考试没想到有点可惜 qaq。

### $Code$ （第三种）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k=1,x,a[10],b[10];
ll ans,t;
int one(int m){
	while(m>=10) m/=10;
	return m;
}
int buxian(int m){
	int s=0;
	for(int i=0;i<=m;i++) s+=pow(10,i);
	return s;
}
int main(){
	scanf("%d",&n);
	if(n<10){
		printf("%d",n);
		return 0;
	}
	//求n的位数
	a[1]=n;
	x=one(n);
	int u=n;
	while(u){
		u/=10;
		a[++k]=u;
	} 
	k--;
	//求数 
	for(int i=1;i<=9;i++){
		if(i<x) b[i]+=buxian(k-2);
		else if(i==x){
			b[i]+=buxian(k-3);
			int y=pow(10,k-1);
			for(int j=0;j<=y;j+=10){
				if(x*y+j+one(i)<=n) b[i]++;
				else continue;
			}
		}else b[i]+=buxian(k-3);
	}
	for(int i=1;i<=9;i++) b[i]++,ans+=b[i];
	for(int i=11;i<=n;i++){
		if(!(i%10)) continue;
		t=i%10;
		if(one(i)==t){
			ans+=b[t];
			continue;
		}
		if(t<x){
			ans+=buxian(k-2);
			continue;
		}
		if(t==x){
			ans+=buxian(k-3);
			int y=pow(10,k-1);
			for(int j=0;j<=y;j+=10){
				if(x*y+j+one(i)<=n) ans++;
				else continue;
			}
			continue;
		}
		//t>x
		ans+=buxian(k-3);
	}
	//for(int i=1;i<=9;i++) printf("%d ",b[i]);
	printf("%lld\n",ans);
	return 0;
}
```

时间复杂度的话……大概 $Θ\big(9+\frac{1}{10}\times (n-9)^2+\frac{4}{5}\times (n-9)\big)$？？反正能过，极限数据大概 $1.5$ 秒跑完。

***

### 写在最后

送给大家一句来自初三教练的名言：

> 你思维的深度决定你代码的长度。

这道题体现得淋漓尽致啊。

---

## 作者：cjZYZtcl (赞：1)

## AT4828 [ABC152D] Handstand 2 题解
这题可以用map解决。

由于一个数只能与所有末位与它首位相同，首位与它末位相同的数组成一对，且题目说是有序序列。

那我们可以枚举 $1$ 到 $n$，然后用map对于每一个数存一个二元组 $(x,y)$ 出现的次数（$x$ 表示数的首位，$y$ 表示数的末位）。

所有数都存完之后，再从 $1$ 到 $n$ 循环，对于每一个数在 $ans$ 中累加上它的 $x$ 和 $y$ 相对应的map中的 $(y,x)$ 的个数即可（$x$ 和 $y$ 意义同上）。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<pair<int, int>, int> a;
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), sum = 0;
	for(int i = 1; i <= n; i++){
		if(!(i % 10)) continue;
		int x = i;
		while(x >= 10) x = x / 10;
		a[make_pair(x, i % 10)]++;
	}
	for(int i = 1; i <= n; i++){
		if(!(i % 10)) continue;
		int x = i;
		while(x >= 10) x = x / 10;
		sum += a[make_pair(i % 10, x)];
	}
	write(sum);
}
```


---

## 作者：__Octhyccc__ (赞：0)

先说一句话：建议降个难度。

- 我会暴力！

当你要暴力时，一眼看到 $1\le N\le 2\times 10^5$，再想想自己 $O(n^2)$ 的时间复杂度，TLE 等着你。

正解很简单，因为题目中只要最后一位和第一位，所以我们拆数。设 $a_{ij}$ 为首位为 $i$，末位为 $j$。

答案就是：

$$\sum_{i=1}^9{\sum_{j=1}^9{t_{ij}\times t_{ji}}}$$

因为我们要求的是排列，所以不用 $\times \frac{1}{2}$。

代码：

```cpp
#include<cstdio>
int a[10][10],n,cnt;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int las,now=i;
		las=now%10;
		while(now>=10)now/=10;
		a[now][las]++;
	}
	for(int i=0;i<=9;i++){
		for(int j=0;j<=9;j++)cnt+=a[i][j]*a[j][i];
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[[ABC152D] Handstand 2の传送门](https://www.luogu.com.cn/problem/AT_abc152_d)

题目要求 $A$ 的第一位数字等于 $B$ 的最后一位数字，且 $A$ 的最后一位数字等于 $B$ 的第一位数字。

所以我们只需要知道 $A$ 和 $B$ 的首位和末位即可。

因此，我们可以把 $[1,n]$ 中的每一个数的首位 $i$ 和末位 $j$ 用桶 $f[i][j]$ 存储。

最后，我们就可以计算答案，让 $i,j$ 从 $1$ 到 $9$ 循环，每次加上 $f_{i,j} \times f_{j,i}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,f[10][10];
signed main() {
	cin>>n;
	for(int i=1;i<=n;++i) {
		int t=i,s=t%10;
		while(t/10)	t/=10;
		++f[s][t];
	}
	for(int i=1;i<10;++i)
		for(int j=1;j<10;++j)	ans+=f[i][j]*f[j][i];
	cout<<ans;
	return 0;
}
```

---

## 作者：yzm0325 (赞：0)

~~热毛巾又炸了啊啊啊啊啊啊~~

## 思路

本题中 $n$ 的数据范围达到了 $10^5$，而直接暴力枚举复杂度是 $O(n^2)$，会超时。

因为题目只关心每个数的首位和末位，所以我们可以开一个二维数组 $t$，用 $t_{i,j}$ 表示首位为 $i$，末位为 $j$ 的数的数量。

将 $t$ 数组统计出来后，答案就是：

$$\sum_{i=1}^9 \sum_{j=1}^9 t_{i,j} \times t_{j,i}$$

直接循环计算即可。

## 代码（禁止抄袭！）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t[10][10], ans;
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int i1 = i; // 注意不能更改循环变量
        int sw, mw = i1 % 10; // sv 是这个数的首位，mv 是这个数的末位
        while(i1 >= 10) i1 /= 10; // 不断舍弃末位直到只剩一位
        sw = i1;
        t[sw][mw]++;
    }
    for(int i = 1; i <= 9; i++)
        for(int j = 1; j <= 9; j++)
            ans += t[i][j] * t[j][i];
    cout << ans;
    return 0; // 完结撒花！
}
```

---

