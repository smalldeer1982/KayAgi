# Margarite and the best present

## 题目描述

小女孩Margarita是信息竞赛的忠实粉丝，她对数组和数列问题尤其感兴趣。

最近，她提出了一个长度为$10^9$的数列：

$a_1=-1$

$a_2=2$

$a_3=-3$

$a_4=4$

$a_5=-5$

$\cdots$

同样的，它也可以被表示成下面这个样子：
$$
a_i=i*(-1)^i,1\le i \le 10^9
$$
Margarita提出了$q$个询问，每一个询问包含两个整数：$l$和$r$。对于每一个询问，你需要回答$\sum_{i=l}^{r}a_i$的值，即数列中第$l$项至第$r$项的和。

## 说明/提示

第一个询问中，你需要回答第$1$项至第$3$项的和，$a_1+a_2+a_3=-1+2-3=-2$。

第二个询问中，你需要回答第$2$项至第$5$项的和，$a_2+a_3+a_4+a_5=2-3+4-5=-2$。

第三个询问中，你需要回答第$5$项至第$5$项的和，$a_5=-5$。

第四个询问中，你需要回答第$4$项至第$4$项的和，$a_4=4$。

第五个询问中，你需要回答第$2$项至第$3$项的和，$a_2+a_3=2-3=-1$。

## 样例 #1

### 输入

```
5
1 3
2 5
5 5
4 4
2 3
```

### 输出

```
-2
-2
-5
4
-1
```

# 题解

## 作者：_xbn (赞：3)

一道类似于找规律的题，读完题我们可以发现若 i 为奇数，$a(i)=-i$;若 i 为

偶数，$a(i)=i$;所以 $a(i)+a(i+1)$ 只可能等于 1 或 -1，发现了这点，

题目就好做了。

要求区间 $(l,r)$,我们可以先把 $(l,r)$ 区间的数两两分组，若 l 为数，

每组值为 1；否则值为 -1，之后若还剩 r，就加上 $a(r)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=2e6+5;
int n,m,l,r,s,t;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>l>>r;
		if(l%2==1)
		{
			int cnt=(r-l+1)/2;
			int ans=cnt;
			int tot=cnt*2;
			if(tot<r-l+1)ans=ans-r;
			cout<<ans<<endl;
		}
		else
		{
			int cnt=(r-l+1)/2;
			int ans=-cnt;
			int tot=cnt*2;
			if(tot<(r-l+1))ans=ans+r;
			cout<<ans<<endl;
		}
	}
	return 0;
}
```




---

## 作者：dblark (赞：3)

发一波Codeforces的Pascal题解~~~

数据那么大，看一眼就知道是分情况讨论。

只要枚举两个端点奇偶的情况就可以了。

Pascal代码：

```pas
var
  q,i,l,r:longint;
begin
  read(q);
  for i:=1 to q do
  begin
    read(l,r);
    if l mod 2=0 then
      if r mod 2=0 then        //如果两端都为偶
        writeln((r-l) div 2+l) //一堆1，再加左端
      else                     //如果左端为偶，右端为奇
        writeln((l-r-1) div 2) //一堆-1
    else
      if r mod 2=0 then        //如果左端为奇，右端为偶
        writeln((r-l+1) div 2) //一堆1
      else                     //如果两端都为奇
        writeln((l-r) div 2-l);//一堆-1，顺便把左端减了
  end;
end.
```

---

## 作者：JerryVoider (赞：2)

本题用到前缀和，对于题目中的a[i],a[1]+a[2]+a[3]+...+a[i]定义为sum[i].

因为数组a的特殊，可以发现规律，对于每一个sum[i],如果i为偶数,sum[i]=i/2,如果i为奇数sum[i]=-(i+1)/2，对于每一组询问，ans=sum[r]-sum[l-1].
#
代码：
```cpp
#include<iostream>
#include<cstdio>
int l,r,q;
int main()
{
    
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int ans=0;
        scanf("%d%d",&l,&r);
        l--;
        if(l%2==0) l/=2;
        else l=-(l+1)/2;
        if(r%2==0) r/=2;
        else r=-(r+1)/2;
        printf("%d\n",r-l);
    }
    return 0;
 } 
```





---

## 作者：一扶苏一 (赞：2)

## Solution

看到这个题目想到[CF15C](https://www.luogu.org/problemnew/show/CF15C),只不过那个题目是求连续异或和。

考虑当$i$为一个奇数时，$a_i~+~a_{i+1}~=~1$.按照这样的方式可以得到从奇数下标开始数，每两个数的和是$1$，于是当$l$为奇数，$r$为偶数时，$[l,r]$的和就是$\frac{r-l+1}{2}$。当$l$为偶数时把$l$的贡献加上然后$++l$即可，$r$也同理。

考虑$l$和$r$相差很小的时候，$--r$再$++l$很可能会让$l$和$r$错过去。但是对于这样的差很小的边界情况完全可以直接暴力跑答案。于是就不存在边界情况啦~

## Code

```cpp
#include<cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a,b,c)
#define putchar(o)\
puts("I am a \
cheater!")
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L],*front=buf,*end=buf;
	char GetChar() {
		if(front == end) {
			end = buf + fread(front = buf , 1 , L , stdin);
			if(front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch=IPT::GetChar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=IPT::GetChar();
	while((ch >= '0') && (ch <= '9')) x=(x<<1)+(x<<3)+(ch^48),ch=IPT::GetChar();
	if(lst == '-') x=-x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch=IPT::GetChar(),lst=' ';
	while((ch > '9') || (ch < '0')) lst=ch,ch=IPT::GetChar();
	while((ch >= '0') && (ch <= '9')) x=x*10+(ch^48),ch=IPT::GetChar();
	if(ch == '.') {
		ch=IPT::GetChar();
		double base=1;
		while((ch >= '0') && (ch <= '9')) x+=(ch^48)*((base*=0.1)),ch=IPT::GetChar();
	}
	if(lst == '-') x=-x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x,const char aft,const bool pt) {
	if(x < 0) {x=-x,putchar('-');}
	rg int top=0;
	do {OPT::buf[++top]=x%10+'0';} while(x/=10);
	while(top) putchar(OPT::buf[top--]);
	if(pt) putchar(aft);
}

int n;

int main() {
	freopen("1.in","r",stdin);
	qr(n);
	int l,r;
	while(n--) {
		ll _ans=0;
		l=r=0;qr(l);qr(r);
		if((r-l) <= 100) {
			for(rg int i=l;i<=r;++i) {
				_ans+=i*((i&1)?-1:1);
			}
		}
		else {
			if(!(l&1)) _ans=l++;
			if(r&1) _ans-=r--;
			_ans+=(r-l+1)>>1;
		}
		qw(_ans,'\n',true);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 这道题可以用分类讨论来解答

首先，我们可以看出当 $a_i$ 为奇数时 $a_i=-i$,

而当 $a_i$ 为偶数时 $a_i=i$。

然后把情况分完后，可得4种情况

**当输入的 $l$ 和 $r$ 均为奇数时**

![](https://cdn.luogu.com.cn/upload/image_hosting/k4od9e92.png)

通过读图可知，此时 $l$ 到 $r$ 之间共有 $(r-l)/2$ 个 $-1$ 和 一个 $l$（此时为 $a_l$ 负数）。

所以这个类别的解为 $-((r-l)+1)/2-l$。

**当输入的 $l$ 和 $r$ 均为偶数时**

![](https://cdn.luogu.com.cn/upload/image_hosting/1uhcluer.png)

又通过读图可知，此时 $l$ 到 $r$ 之间共有 $(r-l)/2$ 个 $1$ 和 一个 $l$（此时为 $a_l$ 正数）。

所以这个类别的解为 $((r-l)+1)/2+l$。

**当输入的 $l$ 为奇数， $r$ 为偶数时**

![](https://cdn.luogu.com.cn/upload/image_hosting/3vd62lwx.png)

又双通过读图可知，此时 $l$ 到 $r$ 之间共有 $(r-l)/2$ 个 $1$。

所以这个类别的解为 $((r-l)+1)/2$。

**当输入的 $l$ 为偶数， $r$ 为奇数时**

![](https://cdn.luogu.com.cn/upload/image_hosting/83fzhg76.png)

又双叒通过读图可知，此时 $l$ 到 $r$ 之间共有 $(r-l)/2$ 个 $-1$。

所以这个类别的解为 $-((r-l)+1)/2$。

~~下面是坠喜欢的代码环节！~~

## AC Code
```
#include<iostream>
using namespace std;
long long q,ans;
int l,r;
int main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>l>>r;
		if(l&1 && r&1){				//判奇偶
			ans-=(((r-l)+1)/2)+l;
		}
		if(l%2==0 && r%2==0){
			ans+=(((r-l)+1)/2)+l;
		}
		if(l%2==0 && r&1){
			ans-=((r-l)+1)/2;
		}
		if(l&1 && r%2==0){
			ans+=((r-l)+1)/2;
		}
		cout<<ans<<endl;
		ans=0;					//别忘了初始值设为0
	}
	return 0;
}
/* by aw_aw*/
```

这是本人的第二篇题解，如有不对之处，恳请指出。

---

## 作者：fengxiaoyi (赞：0)

### 思路
这道题很简单，我们来看看下面的式子：
$$a_1+a_2+a_3+\cdot\cdot\cdot+a_n(a_i=i*(-1)^i)$$
当 $n$ 是偶数时，这个式子等于 $n/2$。

当 $n$ 是奇数时，这个式子等于 $n/2+1$。

那么我们只要输入 $l$ 和 $r$，求出 $a_1+a_2+\cdot\cdot\cdot+a_{l-1}$ 和 $a_1+a_2+\cdot\cdot\cdot+a_r$，再做减法即可（前缀和思想）。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long q;
int main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		long long a,b;
		cin>>a>>b;
		long long s1,s2;
		if(a&1){
			s1=(a-1)/2;
		}
		else{
			s1=(a-1)/2-a+1;
		}
		if(b&1){
			s2=b/2-b;
		}
		else{
			s2=b/2;
		}
		cout<<s2-s1<<endl;
	}
	return 0;
}

```

---

## 作者：Arghariza (赞：0)

分类讨论 $l$ 是否被 $2$ 整除，$r$ 是否被 $2$ 整除。

如果 $2\mid l$ 并且 $2\mid r$，即两个端点均为偶数，那么前面一共有 $\frac{r-l}{2}$ 个 $-1$ ，加上最后的第 $r$ 项（即为 $r$），答案为 $-\frac{r-l}{2}+r$ 

如果 $2\mid l$ 并且 $2\nmid r$，即左端点为偶数，右端点为奇数，所以一共就有 $\frac{r-l+1}{2}$ 个 $-1$，答案为 $-\frac{r-l+1}{2}$ 

如果 $2\nmid l$ 并且 $2\mid r$，即左端点为奇数，右端点为偶数，所以一共就有 $\frac{r-l+1}{2}$ 个 $1$，答案为 $\frac{r-l+1}{2}$ 

最后一种情况，如果 $2\nmid l$ 并且 $2\nmid r$，即两个端点均为奇数，那么前面一共有 $\frac{r-l}{2}$ 个 $1$ ，加上最后的第 $r$ 项（即为 $-r$），答案为 $\frac{r-l}{2}-r$ 

所以直接判断即可，复杂度 $O(q)$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	cin >> n;
	for (int i = 1, l, r; i <= n; i++) {
		cin >> l >> r;
		if (l % 2 == 0) {
			if (r % 2 == 0) cout << -(r - l) / 2 + r << "\n";// 都是偶数
			else cout << - (r - l + 1) / 2 << "\n";// 左偶右奇
		} else {
			if (r % 2 == 0) cout << (r - l + 1) / 2 << "\n";// 左奇右偶
			else cout << (r - l) / 2 - r << "\n";// 都是奇数
		} 
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $t$ 次询问，每次询问给定两个整数 $l,r$，求 $\sum\limits_{i=l}^r (-1)^i\times i$。

**数据范围：$1\leqslant t\leqslant 10^3,1\leqslant l\leqslant r\leqslant 10^9$。**
## Solution
建议先去做 [CF486A](https://www.luogu.com.cn/problem/CF486A)，然后我们可以得知 $\sum\limits_{i=1}^n (-1)^i\times i=\begin{cases}\dfrac{i}{2}&2\mid i\\\left\lfloor\dfrac{i}{2}\right\rfloor-i&2\nmid i\end{cases}$。因此，我们利用前缀和的思想，设 $f_x=\sum\limits_{i=1}^x (-1)^i\times i$，那么每次询问的答案就是 $f_r-f_{l-1}$，直接套用上面的公式计算即可。
## Code
```cpp
int t, l, r;
long long calc(int i) {
	return i / 2 - (i % 2 ? i : 0);
}

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &l, &r);
		printf("%lld\n", calc(r) - calc(l - 1));
	}
	return 0;
}
```

---

## 作者：Ouaoan (赞：0)

题目：[Margarite and the best present](https://www.luogu.org/problemnew/show/CF1080B)

----

[更好阅读体验？](https://blog.csdn.net/rabbit_ZAR/article/details/85254282)

---

思路：

其实我们可以先列个表看看的——


```cpp

a_i       -1  2 -3  4 -5  6 -7  8 -9 10
sum_i     -1  1 -2  2 -3  3 -4  4 -5  5   //sum是a的前缀和

```

找个规律——

发现 $sum_i=\left\lfloor\dfrac{i-1}{2}\right\rfloor × (-1)^i $

然后就可以求出$sum_L$和$sum_R$了，相减即可。

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x)

int main() {
	int T;
	read(T);
	while(T--) {
		int L,R;
		read(L),read(R);
		printf("%d\n",((R+1)/2*((R&1)?-1:1))-((L)/2*((L&1)?1:-1)));
	} 
	
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

观察数列  
-1,2,-3,4,-5,6,-7,8,-9...  
发现从一个奇数项开始，往后偶数个项的和为len/2  
每个询问都可以对两端暴力修改使得询问满足上述条件  
就可以O(1)求解了
```
#include <bits/stdc++.h>
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const double PI = acos(-1.0);
const int N = 1e5 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    int read()
    {
        register int num = 0;
        register char ch;
        register bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    void write(register int x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};


int main()
{
    register int n = fast_IO::read();
    while (n--)
    {
        register int l = fast_IO::read(), r = fast_IO::read(), ans = 0;
        if (!(l & 1))ans += l++;
        if (r & 1)ans -= r--;
        ans += (r - l + 1) >> 1;
        fast_IO::write(ans); putchar('\n');
    }
    return 0;
}

```


---

## 作者：little_sun (赞：0)

# 题解 CF1080B 【Margarite and the best present】

[安利博客](https://www.cnblogs.com/little-sun0331/p/10014591.html)

这道题其实求的是区间内偶数和减去奇数和

用等差数列求和公式即可

注意区间长度要$+1$

```cpp
# include <bits/stdc++.h>

# define ll long long

int main()
{
    int q;
    scanf("%d", &q);
    while(q--)
    {
        ll l, r;
        ll ans;
        scanf("%I64d%I64d", &l, &r);
        if(l == r)
        {
            printf("%I64d\n", ((l % 2) ? -l : l));
            continue;
        }
        ll x, y;
        ll lodd = ((l % 2 == 1) ? l : l + 1), leven = ((l % 2 == 0) ? l : l + 1), rodd = ((r % 2 == 1) ? r : r - 1), reven = ((r % 2 == 0) ? r : r - 1);
       
        x = ((reven - leven) / 2 + 1) * ((reven + leven) / 2);
        y = ((rodd - lodd) / 2 + 1) * ((rodd + lodd) / 2);
        //printf("%d %d %d %d\n", leven, lodd, reven, rodd);
        ans = x - y;
        printf("%I64d\n", ans);
    }
    return 0;
}
```


---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/10014521.html]()

题意：有一个序列，ai = (-1)i * i，现在有t个询问，问你ax~y的和。

看到这题想到了小学奥数题，对于每个询问只要求a1~y - a1~x-1就好了，至于a1～i就很好求了，当i是偶数就是i / 2, 否则是i - i / 2。搞不懂为什么有人在luogu群上问这题是不是莫队（蒟蒻表示压根不会莫队）。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
int lowbit(int x){ return x & -x; }
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p; } return x; }
//head by DYH

int solve(int x){
    int res = x / 2;
    if(x % 2 == 1) res -= x;
    return res;
}

int main(){
    int t;
    scanf("%d", &t);
    rep(times, 1, t){
        int x, y;
        scanf("%d%d", &x, &y);
        int ans = solve(y) - solve(x - 1);
        printf("%d\n", ans);
    }
    return 0;
}
 Problem-B
```

---

