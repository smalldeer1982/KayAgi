# Mishka and the Last Exam

## 题目描述

Mishka is trying really hard to avoid being kicked out of the university. In particular, he was doing absolutely nothing for the whole semester, miraculously passed some exams so that just one is left.

There were $ n $ classes of that subject during the semester and on $ i $ -th class professor mentioned some non-negative integer $ a_i $ to the students. It turned out, the exam was to tell the whole sequence back to the professor.

Sounds easy enough for those who attended every class, doesn't it?

Obviously Mishka didn't attend any classes. However, professor left some clues on the values of $ a $ to help out students like Mishka:

- $ a $ was sorted in non-decreasing order ( $ a_1 \le a_2 \le \dots \le a_n $ );
- $ n $ was even;
- the following sequence $ b $ , consisting of $ \frac n 2 $ elements, was formed and given out to students: $ b_i = a_i + a_{n - i + 1} $ .

Professor also mentioned that any sequence $ a $ , which produces sequence $ b $ with the presented technique, will be acceptable.

Help Mishka to pass that last exam. Restore any sorted sequence $ a $ of non-negative integers, which produces sequence $ b $ with the presented technique. It is guaranteed that there exists at least one correct sequence $ a $ , which produces the given sequence $ b $ .

## 样例 #1

### 输入

```
4
5 6
```

### 输出

```
2 3 3 3
```

## 样例 #2

### 输入

```
6
2 1 2
```

### 输出

```
0 0 1 1 1 2 
```

# 题解

## 作者：Reywmp (赞：3)

这个神奇的代码怎么过的我都不明白。。。

------------

先说下本人做这题时的几个奇特之处：

- 我直接使用栈(`stack`)存放数列，这样的好处是比较节省空间。。。

- 因为采用了在线的算法，所以啊a,b数组也免了，所以我的代码的空间复杂度不算高，不过毕竟`stack`是STL容器，速度不快。所以是空间换时间，不过这都不重要了。

- 在线的算法导致了我的输出看起来贼乱，请谅解。

------------

基本思路：

- 首先我们将a的第一项直接设为0，因为我们贪心贪的是a(i)能多小多小，a(n-i+1)尽量的大。那么第n项我们直接设为b(1)。因为是栈，所以直接丢到stack里就行了，这样保证会在最后一个输出。

- 我们在线做时，找到一个a(i)便输出，而找到一个a(n-i+1)便塞到stack里面。后面输出。

- 接下来我的贪心思路便与大家差不多了。如果是a(i-1)+a(n-i+2)<b(i)时:a(i)=b(i)-a(n-i+2),那么a(n-i+1)就等于b(i)-a(i);当b(i)已经小于a(n-i+2)时，那么a(i)只能是0,a(n-i+1)便是b(i)。

- 这些思路都有一个核心贪心思想： _**a(i)尽量小而a(n-i+1)尽量大**_ 。

------------

详情见代码:

```
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<stack>
#define ll long long
//IG NB!
using namespace std;
void read(ll &x)
{
	 x=0;ll w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 x*=w;
}
int mx(int a,int b){return a>b?a:b;}
int mn(int a,int b){return a<b?a:b;}
//ll b[200005];
//ll stk[200005];
stack <ll> s;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	read(n);
	ll x=0;
	putchar('0');putchar(' ');//a(1)=0,所以直接输出。
	read(x);
	s.push(x);//输入b(1)后扔到栈中为a(n-1+1),就是a(n);
	ll mina=0;
	for(int i=2;i<=n>>1;i++)//只需要2到n/2次就可以了,之前第一次已经预处理好了。
	{
    	/*因为mina存了a(i),而一次循环后的mina便是a(i-1).
        栈顶当前也是上一次的a(n-i+1)便为a(n-i+2)*/
		read(x);
		if(mina+s.top()<x)
		{ 
			mina=x-s.top();//贪心核心代码，看起来简单是因为stl省去了很多代码。
		}
		printf("%lld",mina);putchar(' ');//mina是每一次的a(i)
		s.push(x-mina);//stack里面存储的是a(n-i+1)
	}
	while(s.empty()==0)
	{
		printf("%lld",s.top());putchar(' ');//这些都是a(n-i+1)
		s.pop();//记得把上一次的a(n-i+1)甩掉
	}
	putchar('\n');
	return 0;
}
```


---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1093C)

题目大意：构造递增数列 $a_i$ 使得 $b_i = a_i + a_{n - i + 1}$。

思路：为了满足条件，第一个数肯定为 $0$，最后一个数肯定为 $b_1$。

后面两种情况：为了使得 $a_i \ge a_{i - 1},a_{n - i + 1} \le a_{n - i + 2}$，同时满足，直接取 $\min$ 即可。

代码：

```cpp
#include <iostream>
using namespace std;
long long n,a[200005],b[200005];
int main()
{
    cin >> n;
    for(int i = 1;i <= n / 2;i ++)cin >> b[i];//输入
    a[n] = b[1];//第一个与最后一个
    for(int i = 2;i <= n / 2;i ++)
    {
        a[n - i + 1] = min(a[n - i + 2],b[i] - a[i - 1]);//取min
        a[i] = b[i] - a[n - i + 1];//可以根据n - i + 1项求得第 i 项
    }
    for(int i = 1;i <= n;i ++)cout << a[i] << " ";//最后输出
}
```

---

## 作者：zsc2003 (赞：1)

### codeforces 2018.12.15 C

#### 题目大意

读入一个正整数$n(n$为偶数$)$

有一个长度为$n/2$的数列$b_{1..n/2}$

求一个长度为$n$的序列$a_{1,2...n}$

满足$b_i=a_i+a_{n-i+1}$

并且$a_i\le a_{i+1}(1 \leq i<n)$

##### 思路：
采用贪心的策略，对于任意一个$b_i$，让$a_{n-i+1}$极可能大，$a_i$尽可能小

先预处理出$i=1$的情况，即让$a[1]=0,a[n]=b[1]$

然后$O(n)$的扫一遍，对于每个$b_i$

如果$b_i \leq a_{n-i+2}$，则让$a_{n-i+1}=b_i,a_i=0$

否则让$a_{n-i+1}=a_{n-i+2},a_i=a_{n-i+2}-b_i$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()//读入优化
{
    ll r,s=0,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
const int N=400010;
ll a[N],b[N];
int n,x;
int main()
{
    n=read();
    x=n>>1;
    for(int i=1;i<=x;i++)
        b[i]=read();
    a[1]=0,a[n]=b[1];
    for(int i=2;i<=x;i++)
    {	
        a[n-i+1]=min(a[n-i+2],b[i]);
        a[i]=b[i]-a[n+1-i];
        if(a[i]<a[i-1])
        {
            a[i]=a[i-1];
            a[n-i+1]=b[i]-a[i];
        }
    }
    for(int i=1;i<=n;i++)
        printf("%I64d ",a[i]);//codeforces上输出long long必须用%I64d
    return 0;
}
```

---

## 作者：Ousmane_Dembele (赞：1)

简单的贪心题

在后面<=上一个的后面的情况下第一个尽可能小

证明很简单，前面越小后面就越大，区间就会大，后面选数空间就大

太简单了就不加注释了(有点丑)
```
#include<bits/stdc++.h>//ss
using namespace std;
int n;
long long b[300002],a[300002];
long long last,first;
int main(){
    cin>>n;
    n/=2;
    for(int i=1;i<=n;i++)cin>>b[i];
    first=0;
    last=b[1];
    a[1]=0;
    a[2*n]=b[1];
    for(int i=2;i<=n;i++){
        if(b[i]-first<=last){
            a[i]=first;
            a[2*n-i+1]=b[i]-a[i];
            last=a[2*n-i+1];
        }else{
            a[2*n-i+1]=last;
            a[i]=b[i]-a[2*n-i+1];
            first=a[i];
        }
    }
    for(int i=1;i<=2*n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
```

---

## 作者：一扶苏一 (赞：1)

## Solution

考虑从前往后填这个数组，如果这个位置填 $x$ 是合法的，那么 $x$ 一定优于 $x~+~1$。因为当这个位置填 $x$ 的话下一个位置的选择比填 $x~+~1$ 多一个。同时对应的位置能填的数字也比填 $x~+~1$ 多一个。于是这个贪心是正确的。

因为数据保证有解，直接从前往后扫填合法的最小数字就可以。

## Code
(话说你谷什么时候资瓷py的高亮啊qaq)
```python
ans = [0] * 200010

n = int(input())
dn = n >> 1
MU = list(map(int, input().split()))
ans[n - 1] = MU[0]
for i in range(1, dn):
	k = MU[i] - ans[i - 1]
	if k > ans[n - i]:
		k = ans[n - i]
	ans[i] = MU[i] - k
	ans[n - i - 1] = k
for i in range(n):
	print(ans[i], end = " ")
print("")
```

---

## 作者：Maysoul (赞：0)

## 简述思路：

发现这题并没有那么复杂，直接贪心即可。

我们假设当前的 $b_{i}$ 拆出来的 $a_{i}$ 和 $a_{n-i+1}$ 这两个数分别为为 $x$ 和 $y$。

同时，假设上一个拆出的 $x$ 和 $y$ 分别是 $lx$ 和 $ly$。

我们需要构造非严格单调递增的数列，从贪心的角度考虑，我们需要让 $x$ 最小，也就是等于上一个拆出的 $x$。同时，$y$ 也必须小于等于上一个拆出的 $y$。

综上，我们存在两种拆法。

1. $x=lx$，同时 $y=b_{i}-lx$。

2. $y=ly$，同时 $x=b_{i}-ly$。

因为要满足题意，所以两种拆法取 $x$ 最大的那一种。

记录数列前一段可以使用栈，后一段可以使用队列，但是我为了方便输出，采用了两个双端队列，也是可以的。

## AC CODE:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=1e6+10;
const int INF=0x3f3f3f3f;
int num,ans;
int a[MAXN];
deque<int> x,y;
signed main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n/2;i++) cin>>a[i];
	x.push_back(0);
	y.push_back(a[1]);
	for (int i=2;i<=n/2;i++){
		int bx=x.back(),by=a[i]-y.front();
		int b=max(bx,by);
		x.push_back(b);
		y.push_front(a[i]-b);
	}
	while(x.size()){
		cout<<x.front()<<" ";
		x.pop_front();
	}
	while(y.size()){
		cout<<y.front()<<" ";
		y.pop_front();
	}
	return 0;
}
```


---

## 作者：vocaloid (赞：0)

贪心。分情况考虑。

贪心策略：令 $a_i=a_{i-1}$ 或 $a_{n-i+1}=a_{n-i+2}$

边界条件：$a_1=0$ ，$a_n=b_1$

分情况讨论：若 $a_{n-i+1}=a_{a-i+2}$ 不可行，即计算后的 $a_i<a_{i-1}$ ，则替换为另一种策略。

由于保证有解，所以贪心策略必正确。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll a[200005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n/2;i++)
	{
		ll x;
		scanf("%lld",&x);
		if(i==1)
		{
			a[i]=0;
			a[n-i+1]=x;
			continue;
		}
		a[n-i+1]=a[n-i+2];
		a[i]=x-a[n-i+2];
		if(a[i]<a[i-1])
		{
			a[n-i+1]=x-a[i-1];
			a[i]=a[i-1];
		}
	}
	for(int i=1;i<=n;i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

根据贪心的思想，我们只需让后面的数尽可能大，前面的数尽可能小即可。

可以证明，在 $ a_i $ 和 $ a_{n-i+1} $ 当中，我们至少要满足以下两个条件中的一个（特别地，当 $ a_i + a_{n-i+1} = b_i $ 时，这两个条件可以同时满足）：

* $ a_i = a_{i-1} $
* $ a_{n-i+1} = a_{n-i+2} $

```cpp
#include <iostream>
using namespace std;
unsigned long long a[200005],b[200005];
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n/2;i++)
  cin>>b[i];
 a[1]=0,a[n]=b[1];
 for(int i=2;i<=n/2;i++)
  if(b[i]-a[i-1]<=a[n-i+2])
  {
   a[i]=a[i-1];
   a[n-i+1]=b[i]-a[i];
  }
  else
  {
   a[n-i+1]=a[n-i+2];
   a[i]=b[i]-a[n-i+1];
  }
 for(int i=1;i<=n;i++)
  cout<<a[i]<<' ';
 return 0;
}
```

---

## 作者：little_sun (赞：0)

# 题解 CF1093C 【Mishka and the Last Exam】

贪心思路，对于每一个$a[i]$,都让他等于$a[i-1]$同时让$a[n-i+1]=b[i]-a[i]$

但是如果$a[n-i+1]>a[n-i+2]$的话，就不满足条件了，怎么办？

我们让$a[i]+=(a[n-i+1]-a[n-i+2])$，同时让$a[n-i+1]$减去这个值即可

```cpp
# include <bits/stdc++.h>
# define ll long long
const int MaxN = 200010;
ll a[MaxN], b[MaxN];
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= (n >> 1); i++)
        scanf("%lld", &b[i]);
    a[n + 1] = 1e18;
    for(int i = 1; i <= (n >> 1); i++)
    {
        a[i] = a[i - 1];
        a[n - i + 1] = b[i] - a[i];
        if(a[n - i + 1] > a[n - i + 2])
        {
            ll delta = a[n - i + 1] - a[n - i + 2];
            a[i] += delta;
            a[n - i + 1] -= delta;
        } 
    }
    for(int i = 1; i <= n; i++)
        printf("%lld ", a[i]);
    return 0;
}
```

---

## 作者：LJC00118 (赞：0)

贪心的想，我们如果要使整个序列非降，那么前面的数字要尽量小，后面的数字要尽量大

首先 $ a[1] = 0, a[n] = b[1] $，然后贪心的扫过去，在满足条件的情况下使得前面的数字尽量小，后面的数字尽量大即可

```cpp
#include <bits/stdc++.h>
#define int long long
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 4e5 + 5;

int a[N], b[N];
int n;

#undef int
int main() {
#define int long long
    read(n);
    for(register int i = 1; i <= n / 2; i++) read(b[i]);
    a[1] = 0; a[n] = b[1];
    for(register int i = 2; i <= n / 2; i++) {
        int wxw = a[i - 1];
        wxw = max(wxw, b[i] - a[n - i + 2]);
        a[i] = wxw; a[n - i + 1] = b[i] - wxw;
    }
    for(register int i = 1; i <= n; i++) print(a[i], i == n ? '\n' : ' ');
    return 0;
}
```

---

## 作者：Zechariah (赞：0)

题目就是要你构造一个不降序，使得对称两个项的和为给定值  
我们贪心的想，左端点尽量小，右端点尽量大  
用l,r表示构造的这个序列的两个对称点上面的值  
显然l尽量小，r尽量大这样更好构造  
所以l和r其中必定有一个与上次构造的l,r是相等的  
那么我们只需要判断是l满足条件还是r满足条件就行了  
当然这里判断是l优先，因为l从0开始，r开始的话就得不到解了  
具体看代码...
```
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 10;
using namespace std;
namespace fast_IO {
	long long read()
	{
		rg long long num = 0;
		rg char ch;
		rg bool flag = false;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
		while ((ch = getchar()) >= '0'&&ch <= '9')
			num = (num << 1) + (num << 3) + (ch ^ 48);
		if (flag)return -num; return num;
	}
	ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
ll num[N];

int main()
{
	rg int n = fast_IO::read() >> 1;
	rg ll l = 0, r = 1e18 + 10;
	for (rg int i = 1; i <= n; ++i)
	{
		rg ll a = fast_IO::read();
		if (a - l <= r)num[i] = l, num[(n << 1) - i + 1] = a - l, r = a - l;
		else num[(n << 1) - i + 1] = r, num[i] = a - r, l = a - r;
	}
	n <<= 1;
	for (rg int i = 1; i <= n; ++i)fast_IO::write(num[i]), putchar(' ');
	return 0;
}
```

---

