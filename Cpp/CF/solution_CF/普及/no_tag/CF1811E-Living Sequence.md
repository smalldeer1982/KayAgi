# Living Sequence

## 题目描述

In Japan, the number $ 4 $ reads like death, so Bob decided to build a live sequence. Living sequence $ a $ contains all natural numbers that do not contain the digit $ 4 $ . $ a = [1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, \ldots] $ .

For example, the number $ 1235 $ is part of the sequence $ a $ , but the numbers $ 4321 $ , $ 443 $ are not part of the sequence $ a $ .

Bob realized that he does not know how to quickly search for a particular number by the position $ k $ in the sequence, so he asks for your help.

For example, if Bob wants to find the number at position $ k = 4 $ (indexing from $ 1 $ ), you need to answer $ a_k = 5 $ .

## 样例 #1

### 输入

```
7
3
5
22
10
100
12345
827264634912```

### 输出

```
3
6
25
11
121
18937
2932285320890```

# 题解

## 作者：SunLegend (赞：29)

## 题目大意
给定 $t$ 次询问，每次询问给定一个正整数 $n$，求第 $n$ 个各个数位上都不含数字 $4$ 的正整数。

## 解法分析
初次读题后很容易把这道题想成数位 $dp$ 和二分了，但这样会大大增加代码实现难度。

其实有一种更简单的解法，显然输出结果的每个数位上都没有 $4$，那么每一位就一共只有 $9$ 种数字，由此可以联想到九进制，实际我们要做的就是把十进制转为九进制，再利用一个数组将九进制数的每一数位进行映射即可。

具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,a[22];
int m[12]={0,1,2,3,5,6,7,8,9};//用来映射的数组 
long long n; //记得long long！！！ 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		while(n)
		{
			a[++x]=m[n%9]; 
			n/=9;
		}
		for(int i=x;i>=1;i--) cout<<a[i];
		cout<<endl;
		x=0;
	}
	return 0;
}
```


---

## 作者：IceKylin (赞：3)

# CF1811E Living Sequence 题解

[原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1811E)

[原题链接（in CodeForces）](https://codeforces.com/problemset/problem/1811/E)

[更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1811e-ti-xie)

显然有一种数位 DP 的做法，但未免有些小题大做了。

考虑不含 $4$ 的正整数，最多只含 $9$ 个不同数码，这与 **九进制** 的定义很相似。

所以有如下思路：构造一个从集合 $\text{A}=\{0,1,2,3,4,5,6,7,8\}$ 到集合 $\text{B}={\{0,1,2,3,5,6,7,8,9\}}$ 的双射。

$f(x)=\left\{\begin{matrix}x&\quad(x\le3)\\x+1&\quad(x\ge4)\end{matrix}\right.$

那么题目就变成了 **进制转化**。

P.S. 本题需要开 long long。

## AC 代码

```cpp
//By IceKylin
#include<bits/stdc++.h>
#define maxn 20
#define ll long long
#define ios ios::sync_with_stdio(false)
using namespace std;
ll t,n,a[maxn],phi[10]={0,1,2,3,5,6,7,8,9};
int main(){
	ios;
	cin>>t;
	while(t--){
		cin>>n;
		ll cnt=0;
		while(n)a[++cnt]=phi[n%9],n/=9;
		for(int i=cnt;i;--i)cout<<a[i];
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Drystynt (赞：3)

我们把原题中“不能有 $4$”这个条件换成 “不能有 $9$”后，再来看这个数列。它变成了：

$[1,2,3,4,5,6,7,8,10,11,12,13,...,18,20,...,87,88,100...]$

发现这正好是十进制转九进制后的数列。这样就可以把原题转换成一道简单的进制转换题了。

因为原题是“不能有 $4$”这个条件，所以把九进制里 $4$ 到 $8$ 五个数码每个数码加上 $1$ 就能变成原题的数列了。

根据数据范围，所以需要开 $\text{long long}$.

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define N 21
int a[N];
long long n;
int j;
int main()
{
	int t;
	cin>>t;
	for(int R=1;R<=t;R++)
	{
		cin>>n;
		for(j=0;;j++)
		{
			a[j]=n%9;
			if(a[j]>=4)	a[j]++;
			n/=9;
			if(n==0) break;
		}
		for(;j>=0;j--)
			printf("%d",a[j]);
		cout<<endl;
	}
	return 0;
} 

```


---

## 作者：aeiouaoeiu (赞：3)

两种方法。

### 方法 $1$：oeis 大法

在 [oeis.org](https://www.oeis.org) 查找这个序列，发现有这样一个公式（注意 oeis 上的序列包含 $0$，而本题没有，所以要把 $n-1$ 换为 $n$）:

![](https://cdn.luogu.com.cn/upload/image_hosting/t8suhu7a.png)

形式化地，若 $n=(\overline{b_{m-1}b_{m-2}\ldots b_0})_9$，$a_n=\sum_{i=0}^{m-1}{10^i(b_i+[b_i>3])}$。

显然，$x+[x>3]\neq4$，所以用该方法不会构造出错误的数字，且对于每一个 $b_i$，$b_i+[b_i>3]$ 都与其一一对应，所以我们可以直接构造出 $a_n$。

代码就不贴了。

### 方法 $2$：数位 dp + 二分

我们先来考虑另一个问题：

给你一个数 $n$，问 $[1,n]$ 范围内有多少个不包含数码 $4$ 的整数？

这题很经典，这里直接给出做法：设 $f_{i,j}$ 表示 $i$ 位数中首位是 $j$，符合要求的数的个数，有
$$f_{i,j}=\sum_{k=0}^9{f_{i-1,k}}~(j\neq 4)$$
根据 $n$ 的每一位数拆开计算答案（具体实现看代码）。

设 $g(x)$ 为当这个问题的 $n=x$ 时的答案，我们看向这道题，发现它可以变成这样：

给你一个数 $n$，求一个不包含数码 $4$ 的最小正整数 $x$，使得 $g(x)=n$。

发现 $g(x)$ 有单调性，于是考虑二分 $x$，然后这道题我们就差不多做完了。

最后一个小坑：二分后的 $x$ 可能包含数码 $4$，所以要再处理一下，变为离 $x$ 最近的不包含数码 $4$ 的数，具体方法就是找到最高位的 $4$，然后把后面全变成 $9$，最后把这个 $4$ 变为 $3$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,f[20][15],di[20],cnt=0;
ll pre(void){
	ll res=0,p=1;
	for(int i=cnt;i>=1;i--){
		if(di[i]==4){
			di[i]--;
			for(int j=i-1;j>=1;j--) di[j]=9;
			break;
		}
	}
	for(int i=1;i<=cnt;i++) res+=p*di[i],p*=10;
	return res;
} 
ll calc(ll x){ //计算 g(x)
	ll ans=0;
	for(cnt=0;x;x/=10) di[++cnt]=x%10;
	for(int i=cnt;i>=1;i--){
		for(int j=0;j<di[i];j++){
			if(j!=4) ans+=f[i][j];
		}
		if(di[i]==4){
			ans--;
			break;
		}
	}
	return ans;
}
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll T;
    cin>>T;
    f[0][0]=1;
    for(int i=1;i<=18;i++){ //数位 dp 预处理
    	for(int j=0;j<=9;j++){
    		for(int k=0;k<=9;k++){
    			if(j!=4) f[i][j]+=f[i-1][k];
			}
		}
	}
    for(;T--;){
    	cin>>n;
    	ll l=1,r=8000000000000ll,mid,val;
    	for(;l<=r;){ //二分
    		mid=(l+r)>>1;
    		val=calc(mid);
    		if(val==n){ //等于就直接退出
    			l=mid;
    			break;
			}else if(val>n) r=mid-1;
			else l=mid+1;
		}
		for(cnt=0;l;l/=10) di[++cnt]=l%10;
		cout<<pre()<<"\n"; //最后的小坑
	}
    return 0;
}
```

---

## 作者：庄nnnn额 (赞：1)

把答案中的 $5\sim9$ 换成 $4\sim8$，就变成了一个九进制数。显然，输入加 $1$，这个九进制数就加 $1$。因此只要把输入转成九进制数，再把 $4\sim8$ 换成 $5\sim9$ 即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
void p(long long a){
	(a>8?p(a/9),a%=9:0),putchar((a>3?a+1:a)|48);
}
int main(){
	int t;
	long long n;
	scanf("%d",&t);
	while(t--)scanf("%lld",&n),p(n),putchar(10);
	return 0;
}
```
喜提本题最短题解代码。

---

## 作者：hycqwq (赞：1)

~~活着的序列（？~~

所以说为什么 CF 的题会牵扯到日语啊喂！

## 思路

去掉了数码 $4$，我们只剩下了 $9$ 个数码即 $0 \sim 3$ 与 $5 \sim 9$。容易想到题目中的序列就是九进制下的正整数表，只不过把大于等于 $4$ 的数码都加了个 $1$。

于是我们也可以这么做。

## 代码

~~对不起，但是这个火车头，它……~~

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if

int t;
ll n;

ll slv(ll x)
{
    ll ans = 0, s10 = 1;
    while (x > 0)
    {
        ll tmp = x % 9;
        if (tmp >= 4)
            tmp++;
        ans += tmp * s10;
        x /= 9, s10 *= 10;
    }
    return ans;
}

int main()
{
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> n;
        cout << slv(n) << endl;
    }
    return 0;
}
```

---

## 作者：ShenTianYi_ (赞：1)

既然 Living Sequence 只由  $0, 1, 2, 3, 5, 6, 7, 8, 9$  这  $9$  个数字构成，那么只需要将数字  $k$  转换成  _9进制_  ，然后将 $4$ ~ $8$ 这几个数字分别增加 $1$ 就可以了。

不多说，上代码。

```cpp
#include<iostream>
using namespace std;
long long t,k;							//观察数据范围，记得开long long
int main()
{
	cin>>t;
	while(t--){
		char ans[20]={};
		int len=0;
		cin>>k;
		while(k){						//短除法转9进制
			int x=k%9;
			k/=9;
			if(x<4){
				ans[++len]=x+'0';		//不超过4的数字不变
			}
			else{
				ans[++len]=x+'1'; 		//超过4的数字要增加1
			}
		}
		for(int i=len;i>=1;i--){		//逆序输出
			cout<<ans[i];
		}
		cout<<endl;
	}
	return 0;
}
```

制作不易，点个赞吧！

---

## 作者：zeekliu (赞：1)

题意简述：给定一个序列（序列从 $1$ 开始），要求其中不能有含有 $4$ 的数（因为日语中 $4$ 是死的意思，~~果然日语抄中文~~）。对于每个询问，求出序列的第 $n$ 个数。

一眼数据范围，$1\le k \le 10^{12}$，$1 \le t \le 10^4$，枚举肯定爆炸。

那么该怎么做呢？观察样例。

可以观察到其中的每个数都变大了一些，而十个数字中有一个不能用，可以想到什么？**九进制**。

但显然这不是普通的九进制，普通的九进制是没有 $9$，这个是没有 $4$，所以显然它也不能按普通的方法处理。

但我们列几组数据看看：

数据 $1$：
> $10$ 进制：$4$ ｜
> 普通 $9$ 进制：$4$ ｜
> 特殊 $9$ 进制：$5$

数据 $2$：
> $10$ 进制：$10$ ｜
> 普通 $9$ 进制：$11$ ｜
> 特殊 $9$ 进制：$11$

数据 $3$：
> $10$ 进制：$40$ ｜
> 普通 $9$ 进制：$44$ ｜
> 特殊 $9$ 进制：$55$

数据 $4$：
> $10$ 进制：$130$ ｜
> 普通 $9$ 进制：$154$ ｜
> 特殊 $9$ 进制：$155$

数据 $5$：
> $10$ 进制：$69$ ｜
> 普通 $9$ 进制：$76$ ｜
> 特殊 $9$ 进制：$87$

观察了这么多组，我们应该能发现，对于每一位数字，如果它的九进制表示大于等于 $4$，那么他就会被跳过，因此这一位数字应该 $+1$。

所以就很简单了，总结：**进制转换 + 逐位判断**。

很好，这样做就掉坑了。

因为你对一个数位是 $9$ 的位置 $+1$ 后就会爆炸，因此还要统计进位。这样就可以了。

代码：

```cpp
//CF1811E 23.04.07
#include <bits/stdc++.h>
using namespace std;

inline void change()
{
    long long x,b,jw=0;
    cin>>x; b=9;
    string ans="";
    while (x)
    {
        ans+=x%b+48,x/=b;
    }
    reverse(ans.begin(),ans.end());
    for (int i=0;i<ans.length();i++)
    {
        if (ans[i]=='9') ans[i]='0',jw=1;
        ans[i]+=jw,jw=0;
        if (ans[i]>'3') ans[i]++;
    }
    for (int i=0;i<ans.length();i++) cout<<ans[i];
    cout<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int _; cin>>_;
    while (_--) change();
    exit(0);
}
```

---

## 作者：AllenKING_RED (赞：1)

### 题目大意

给你一个整数 $k$，求第 $k$ 个不含整数 `4` 的整数。

### 具体思路

不含整数 `4` 的整数，每一位上相当于只有 `9` 个数（遇到 `4` 的时候直接跳过），所以我们可以把 $k$ 转化为 `9` 进制，再进行下一步操作。

显而易见的，此时每一位上 `4` 以上的数会少一，所以给他们再加上一就好了。

### 代码实现

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int a[20];
signed main(void)
{
	cin>>T;
	while(T--)
	{
		int k;
		cin>>k;
		int cnt=0;
		while(k)
		{
			a[++cnt]=k%9;
			k-=a[cnt];
			k/=9;
		}
		for(int i=cnt;i>=1;i--)
		{
			if(a[i]>=4)a[i]++;
			cout<<a[i];
		}
		cout<<endl;
	}
	return 0;
}
```




---

## 作者：WaTleZero_pt (赞：1)

本题浅浅地分析以下，我们就可以发现：欸，去掉数字 $4$ 不就相当于将 $10$ 进制数转换为 $9$ 进制再将 $9$ 进制下大于等于 $4$ 的数位加 $1$ 输出不就可以了吗？以 $150$ 为例：

$150$ 的 $9$ 进制数为 $176$，所以答案为 $187$。

所以本题是一道基本的进制转换题，~~本人赛场上 $3$ 分钟就把这题切了~~，难度大致为 入门 至 普及- 之间。

### AC CODE [Codeforces比赛期间提交记录](https://codeforces.com/contest/1811/submission/200742882)

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;long long n;int a[25],tot;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n); tot=0;
		while(n) a[++tot]=n%9,n/=9;
		for(int i=tot;i>=1;i--)
			if(a[i]<4) printf("%d",a[i]);
			else printf("%d",a[i]+1);
		printf("\n");
	}
}

```

---

## 作者：enyyyyyyy (赞：0)

题目说第 $k$ 个数字里没有 $4$ 的正整数,相当于只有 $0$,$1$,$2$,$3$,$5$,$6$,$7$,$8$,$9$，就相当于一个伪的 $9$ 进制，可以使用字符串处理，但要注意不开 `long long` 见祖宗。


------------

AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗 
using namespace std;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline void print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll t,tot,op;//数组开很大 ，以防越界 
string s;
int main(){	
	t=read();//多组数据用快读 
	while(t--){
		op=read();//多组数据用快读 
		s="";////多组数据注意清空 
		while(op!=0){
			ll t=op%9;//模拟 9进制 
			op/=9;//9进制 
			if(t>=4) t++;//特殊处理 
			char ch=t+'0';//字符串处理 
			s=ch+s;//添加 
		}
		cout<<s<<endl;//输出 
	}
	return 0;
}

```


---

## 作者：Jerry_heng (赞：0)

（一）

题意：询问第 $k$ 个不含 $4$ 的数。

也就是说，每一位有 $0,1,2,3,5,6,7,8,9$ 九种选择。

将这 $9$ 个数看成数列 $a$。

把 $k$ 由 $10$ 进制转为 $9$ 进制。

$k$ 的每一位表示满足题意的数中的那一位能取到第几个数。

如 $k=89$，那么 $9$ 进制就是 $(108)_9$。

$k$ 的第一位是 $1$，所以答案的第一位就是 $a_1=1$。

$k$ 的第二位是 $0$，所以答案的第一位就是 $a_0=0$。

$k$ 的第三位是 $8$，所以答案的第一位就是 $a_8=9$。

所以答案是 $109$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long//大坑 
using namespace std;
int t,a[10001];
signed main(){
	cin>>t;
	while(t--){
		int x,s=0;
		cin>>x;
		while(x>0){
			a[++s]=x%9;
			x/=9;
		}
		for(int i=s;i>=1;i--)
			if(a[i]>=4)cout<<a[i]+1;
			else cout<<a[i];
		cout<<endl;
	}
	return 0;
}

---

## 作者：ZVitality (赞：0)

做法：一眼数位 DP，但它求的是第 $k$ 个而不是 $k$ 以内个数。

可以发现随着 $x$ 的增长，$x$ 以内的个数也在增长，呈单调性。

所以我们只需二分即可。

---

