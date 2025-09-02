# Swaps Again

## 题目描述

给出两个长度为 $n$ 的数列 $a,b$，你需要判断能否在数次操作后使得 $a$ 与 $b$ 相同。

操作是指你可以选择一个 $k(1\le k\le\lfloor\frac n2\rfloor)$，之后交换 $a$ 的长度为 $k$ 的前缀和长度为 $k$ 的后缀。

例如对于 $a=\{1,2,3,4,5,6\}$，选择 $k=2$，那么交换后会得到 $\{5,6,3,4,1,2\}$。

## 样例 #1

### 输入

```
5
2
1 2
2 1
3
1 2 3
1 2 3
3
1 2 4
1 3 4
4
1 2 3 2
3 1 2 2
3
1 2 3
1 3 2```

### 输出

```
Yes
Yes
No
Yes
No```

# 题解

## 作者：KellyFrog (赞：4)

~~这么水的round我怎么没打啊。~~

看到这种交换的、改数的、输出`yes`和`no`的，猜个结论绝对不亏。

看这个样例：
> 例如对于 $a=\{1,2,3,4,5,6\}$，选择$k=2$，那么交换后会得到 $\{5,6,3,4,1,2\}$

注意到${5,2}$和${1,6}$的位置关于中间那个点对称，于是我们有了一个大胆的想法

1. 前后数字是一样的（废话
2. $i$和$n-i+1$的位置换过之后应该是$j$和$n-j+1$的位置，可以两两交换

于是我们就愉快地写出了code：

```cpp
#include <map>
#include <iostream>

using namespace std;

const int MAXN = 5e3 + 5;

map<pair<int, int>, int> mp;
int a[MAXN], b[MAXN];

void Solve() {
	mp.clear();
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for(int i = 1; i <= (n >> 1); i++) {
		mp[make_pair(a[i], a[n - i + 1])]++;
		mp[make_pair(a[n - i + 1], a[i])]++;
	}
	if((n & 1) && a[(n + 1) >> 1] != b[(n + 1) >> 1]) {
		cout << "No" << endl;
		return;
	}
	for(int i = 1; i <= (n >> 1); i++) {
		if(!mp[make_pair(b[i], b[n - i + 1])]) {
			cout << "No" << endl;
			return;
		}
		mp[make_pair(b[i], b[n - i + 1])]--;
		mp[make_pair(b[n - i + 1], b[i])]--;
	}
	cout << "Yes" << endl;
}

int main() {
	int t, n;
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

然后你就AC了。

可是为什么呢？

考虑到我们换掉了一个$i\le k$，那么原来$a_i$就变成了$a_{i+(n-k)}$，$a_{n-i+1}$就变成了$a_{n-i+1-(n-k)=k-i+1}$又因为有$i+(n-k)+k-i+1=n+1$，故上面两个是关于中心点对称的，这证实了我们上面的猜想。

---

## 作者：Guitar_Jasmine (赞：3)

乍一看毫无思路的一道题。

假设我们选择交换的前后缀长度为$k$，我们考虑原本对称的两个点$i$ 和 $n-i+1$（$i \leq k$）现在怎么样了：
- $i \Rightarrow n-k+i$
- $n-i+1 \Rightarrow k-i+1$

我们惊奇的发现，他们进行交换后还是对称的！（仍然满足$i+j=n+1$）

~~于是我们大胆猜测~~：当且仅当两个序列的对称位置（我们把他们看成一个二元组）组成的集合相同时，这两个序列可以互相到达，应该可以感性理解。

那代码就呼之欲出了：
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>

using namespace std;

const int N=509;
int n,a[N],b[N];
map <pair<int,int>,int> bin;

void init()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    bin.clear();
}

void work()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        init();
        int flag=1;
        if((n&1)&&a[n+1>>1]!=b[n+1>>1])
        {
        	puts("NO");
        	continue;
        }
        for (int i=1;i<=(n+1)/2;i++)
            bin[make_pair(min(a[i],a[n-i+1]),max(a[i],a[n-i+1]))]++;
        for (int i=1;i<=(n+1)/2;i++)
            if((--bin[make_pair(min(b[i],b[n-i+1]),max(b[i],b[n-i+1]))])<0)
                flag=0;
        puts(flag?"Yes":"No");
    }
}

int main()
{
    work();
    return 0;
}
```

---

## 作者：Eibon (赞：2)

拿到题没有思路，不妨举例寻找规律。

![](https://cdn.luogu.com.cn/upload/image_hosting/dyv3yyoa.png)

发现每次相距字符串中心相等的两字符是同一个，因为每次交换时，交换的长度是相等的,并且前后顺序没有发生改变，所以这会使 $a_i$ 转移到 $n-i$ 的位置。

只需正常模拟判断即可，先将每一对对称的字符维护，暴力判断，并判断长度为奇数的串中央。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1000+5;
const int mod=998244353;
int T,n,l;
int a[maxn],b[maxn];
struct node
{
	int l,r;
	bool operator < (const node &x) const
	{
		if(l==x.l){
			return r<x.r;
		}
		return l<x.l;
	}
};
node x[maxn],y[maxn];
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	l=n/2;
	for(int i=1;i<=l;i++){
		if(a[i]>a[n-i+1]){
			swap(a[i],a[n-i+1]);
		}
		if(b[i]>b[n-i+1]){
			swap(b[i],b[n-i+1]);
		}
		x[i]={a[i],a[n-i+1]};
		y[i]={b[i],b[n-i+1]};
	}
	sort(x+1,x+l+1);
	sort(y+1,y+l+1);
	for(int i=1;i<=l;i++){
		if(x[i].l!=y[i].l||x[i].r!=y[i].r){
			puts("NO");
			return;
		}
	}
	if(n&1){
		if(a[(n+1)/2]!=b[(n+1)/2]){
			puts("NO");
			return;
		}
	}
	puts("YES");
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Provicy (赞：1)

考虑有一个 $k$，使得 $a_{i}$ 和 $a_{n-i+1}$ $(i\leq k)$ 能改变位置，观察对于每个 $i$ 和 $n-i+1$ 改变后的位置。

$$\large a_{i}->a_{i+(n-k)}$$
$$\large a_{n-i+1}->a_{n-i+1-(n-k)}$$

可以发现 $a_{i}$ 和 $a_{n-i+1}$ 移动的下标长度是一样的。而 $a_{i}$ 与 $a_{n-i+1}$ 是对称的，故可以得出，无论怎么交换序列 $a$ 长度为 $k$ 的前缀与后缀，原本的 $a_{i}$ 和 $a_{n-i+1}$ 会一直对称。所以序列 $a$ 在若干次操作后能和序列 $b$ 相同的条件是：在 $a$ 序列中对称（即 $a_{i}$ 和 $a_{n-i+1}$）的两个数，在 $b$ 中也要对称，即两个序列的对称位置二元组分别组成的集合是相等的。

当 $n$ 为奇数时，发现 $a_{\lceil \frac{n}{2}\rceil}$ 这个位置无法移动的。但是这个位置也是要与 $b_{\lceil \frac{n}{2}\rceil}$ 匹配的。即在当 $n$ 为奇数时，还需要判断 $a_{\lceil \frac{n}{2}\rceil}$ 与 $b_{\lceil \frac{n}{2}\rceil}$ 是否相等。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define mk make_pair
#define int long long
using namespace std; const int N=510;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
void print(int x) {if(x<0) x=-x, putchar('-'); if(x>9) print(x/10); putchar(x%10+'0'); }
int n,a[N],b[N];
map< pair<int, int>, int > Q;
signed main()
{
	for(ri int T=read();T;T--)
	{
		n=read();
		for(ri int i=1;i<=n;i++) a[i]=read();
		for(ri int i=1;i<=n/2;i++)
		{
			int p=min(a[i],a[n-i+1]),
				q=max(a[i],a[n-i+1]);
			Q[mk(p,q)]++;
		}
		for(ri int i=1;i<=n;i++) b[i]=read();
		int flag=1;
		for(ri int i=1;i<=n/2;i++)
		{
			int p=min(b[i],b[n-i+1]),
				q=max(b[i],b[n-i+1]);
			if(--Q[mk(p,q)]<0) {flag=0; break; }
		}
		if(n&1ll)
		{
			if(b[n/2+1]^a[n/2+1]) flag=0;
		}
		(flag)?puts("Yes"):puts("No");
		Q.clear();
	}
	return 0;
}
```


---

## 作者：luan341502 (赞：0)

首先我们注意到一个很重要的性质：

对于一次修改，存在两个下标 $i$ 和 $n-i+1(i \le k)$，它们原本是中心对称的，修改完之后，下标为 $i$ 的数现在到了 $n-k+i$，下标为 $n-i+1$ 的数到了 $k-i+1$，我们发现

$$(n-k+i)+(k-i+1)=i+(n-i+1)=n+1.$$

也就是说修改完之后，它们的下标依然中心对称。

因此我们依照这个性质，将点对 $(i,n-i+1)$ 放到集合里面，并将 $a$ 和 $b$ 的点对比较就行了。

注意特判 $n$ 为奇数时两个数组中间的数是否相等。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[505],b[505];
multiset<pair<int,int> > s;
void solve(){
	s.clear();
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	if((n&1)&&(a[(n+1)/2]^b[(n+1)/2])){
		cout<<"No\n";
		return;
	}
	for(int i=1;i<=n/2;i++){
		if(a[i]>a[n-i+1]) swap(a[i],a[n-i+1]);
		s.insert(make_pair(a[i],a[n-i+1]));
	}
	for(int i=1;i<=n/2;i++){
		if(b[i]>b[n-i+1]) swap(b[i],b[n-i+1]);
		if(s.find(make_pair(b[i],b[n-i+1]))==s.end()){
			cout<<"No\n";
			return;
		}
		s.erase(s.find(make_pair(b[i],b[n-i+1])));
	}
	cout<<"Yes\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int tt;cin>>tt;while(tt--)solve();
	return 0;
} 
```


---

## 作者：Daniel_yao (赞：0)

## Problem
给定长度为 $n$ 的序列 $a,b$，每次操作可以选择一个 $k$，交换长度为 $k$ 的前缀和长度为 $k$ 的后缀。问是否能通过操作使得 $a,b$ 同构。
## Solve
将操作等价转化：以 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 为对称轴，将两边呈轴对称的数（称为：**一对数**）交换，交换后可以置于左右半边的**任意位置**。

因为没有规定操作次数，所以可以默认**操作合法即可成立**。然后就会发现，只要所有的一对数在 $b$ 中也成对出现。则认为可行，否则不行。

当然序列长度为奇数时，$a_{\left\lceil\frac{n}{2}\right\rceil}$ 落单了，此时需要特判，因为 $a_{\left\lceil\frac{n}{2}\right\rceil}$ 无论如何都不可能移动。

时间复杂度 $O(n\log n)$，原因是套了个 map。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

inline int read() {
  rint x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
  return x*f;
}

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 5e5 + 10;

int T, n, a[N], b[N];

map<pair<int, int>, int> mp;

signed main() {
  T = read();
  while(T--) {
    n = read();
    map<pair<int, int>, int>().swap(mp);
    For(i,1,n) a[i] = read();
    For(i,1,(n>>1)) mp[make_pair(a[i], a[n - i + 1])]++, mp[make_pair(a[n - i + 1], a[i])]++;
    For(i,1,n) b[i] = read();
    if((n & 1) && a[(n + 1) >> 1] != b[(n + 1) >> 1]) {puts("No"); continue;}
    For(i,1,(n>>1)) {
      if(!mp[make_pair(b[i], b[n - i + 1])]) {
        puts("No");
        goto yzsy;
      }
      mp[make_pair(b[i], b[n - i + 1])]--;
      mp[make_pair(b[n - i + 1], b[i])]--;
    }
    puts("Yes");
    yzsy: continue;
  }
  return 0;
}
```


---

## 作者：Exber (赞：0)

结论题，别的题解都没给证明，我来证一下吧。

观察到每次操作中对于所有满足 $i\le \lfloor\frac{n}{2}\rfloor$ 的 $i$ 都进行了  $\operatorname{swap}(a_i,a_{n-k+i})$，而和 $a_i$ 以序列中点对称的元素是 $a_{n-i+1}$，操作中同时进行了 $\operatorname{swap}(a_{k-i+1},a_{n-i+1})$，所以 $(a_i,a_{n-i+1})$ 和 $(a_{k-i+1},a_{n-k+i})$ 在交换之后仍然以序列中点对称。

那么把 $a$ “对折”，把 $(a_i,a_{n-i+1})$ 这一对记作 $b_i$，那么每次操作相当于是交换了所有满足 $i\le \lfloor\frac{k}{2}\rfloor$  的 $b_i$ 和 $b_{k-i+1}$，并且所有满足 $i\le k$ 的 $b_i$ 组内顺序都被交换了。

不难发现，组内顺序是可以随便交换的，只要做一次 $k=i$，一次 $k=1$，一次 $k=i$ 即可。

现在问题转化为：

> 有一个 $n$ 的排列 $p$，请问能否通过任意次交换满足 $1\le i\le \lfloor\frac{k}{2}\rfloor$ 的 $p_i$ 和 $p_{k-i+1}$，得到 $n$ 的另外的一个排列 $b$？

这个问题对于任意 $p,b$ 的答案都是可以，证明如下：

****

- 引理：可以使用 $2$ 次操作将 $p_1,p_2,p_3,\dots,p_i$ 变为 $p_i,p_1,p_2,\dots p_{i-1}$，即让某个前缀往后循环移位一位。

  证明：一次 $k=i-1$，一次 $k=i$ 的操作即可。

不难发现，想要证明从任意 $p$ 出发可以到达任意 $b$，只要证明能交换 $p$ 中任意相邻两项即可。

考虑相邻的两项 $i,i+1$，我们只需要做一次 $k=i-1$ 的操作，把 $p_{[1,i+1]}$ 往后循环移位两位，再做一次 $k=i+1$ 的操作即可交换 $p_i,p_{i+1}$，得证。

****

所以直接开桶做就行了。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

const int S=505;

int n,a[S],b[S];
map<int,map<int,int> > mp;

inline void slove()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	if((n&1)&&a[n/2+1]!=b[n/2+1])
	{
		puts("No");
		return;
	}
	if(n==1)
	{
		puts("Yes");
		return;
	}
	mp.clear();
	for(int i=1;i<=n/2;i++) mp[a[i]][a[n-i+1]]++,mp[a[n-i+1]][a[i]]++;
	for(int i=1;i<=n/2;i++)
	{
		if(mp[b[i]][b[n-i+1]]==0)
		{
			puts("No");
			return;
		}
		mp[b[i]][b[n-i+1]]--;
		mp[b[n-i+1]][b[i]]--;
	}
	puts("Yes");
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--) slove();
	return 0;
}
```



---

## 作者：zsyyyy (赞：0)

## CF1365F 2100

### 题目描述

给出两个长度为 $n$ 的数列 $a,b$，你需要判断能否在数次操作后使得 $a$ 与 $b$ 相同。

操作是指你可以选择一个 $k(1\le k\le\lfloor\frac n2\rfloor)$，之后交换 $a$ 的长度为 $k$ 的前缀和长度为 $k$ 的后缀。

例如对于 $a=\{1,2,3,4,5,6\}$，选择 $k=2$，那么交换后会得到 $\{5,6,3,4,1,2\}$。



### 思路

有如下数组：$a_1,a_2,a_3,a_4,a_5,a_6,a_7$。

若交换左三和右三，则变为 $a_4,a_5,a_6,a_7,a_1,a_2,a_3$。

可以发现，一开始关于中心对称的每对点交换后依然关于中心对称。

所以，判断 $b$ 数组中关于中心对称的每对点是否在 $a$ 数组中也关于中心对称，即可。



### 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=510;
int T,n,a[MAXN],b[MAXN];
bool flag;
map<pair<int,int>,int> book;
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		flag=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)  scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++)
		{
			if(a[i]>a[n-i+1])  swap(a[i],a[n-i+1]);
		}
		for(int i=1;i<=n;i++)
		{
			if(b[i]>b[n-i+1])  swap(b[i],b[n-i+1]);
		}
		for(int i=1;i<=n;i++)  book[make_pair(a[i],a[n-i+1])]++;
		for(int i=1;i<=n;i++)
		{
			if(!book[make_pair(b[i],b[n-i+1])])
			{
				puts("No");
				flag=1;
				break;
			}
			else  book[make_pair(b[i],b[n-i+1])]--;
		}
		for(int i=1;i<=n;i++)  book[make_pair(a[i],a[n-i+1])]=0;
		if(!flag)  puts("Yes");
	}
	return 0;
}
```



---

## 作者：Gloaming (赞：0)

## 题目大意

可以将一个字符串的前面 $k$ 个字符和后面的 $k$ 个进行调换，然后在只用这种操作的前提下（**不限操作次数**），判断将其变为另一个字符串的可行性

## 分析

对于这一种不限次数的问题，通常就是推导出一个结论。我们自己手动模拟几组数据
```
1 2 3 4 5 6 -> 1 5 3 4 2 6 (yes)
* *     * *
5 6 3 4 1 2
*         *
2 6 3 4 1 5
* *     * *
1 5 3 4 2 6 
```
我们可以发现对称的两个字符都是可以通过题目中给的操作来调换位置的。

具体操作：假设要换的为 $str_i,str_{n-i+1}$，我们令 $k=i$ 把 $str_i, str_{n-i+1}$ 放到字符串的两边，然后令 $k=1$ 进行交换。然后再令 $k=i$ 换回去就可以了 

那么我们就可以将这两个字符关联起来，在 $a$ 数组中添加这种字符对，然后 $b$ 数组中进行删除。如果出现了没有统计过的的字符对，说明不能转换。

实现方面，我们用 STL 中的 `map` 类来实现关联两个字符。

## 代码

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int a[510], b[510];
map<pair<int, int>, int> mp;
int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    while (T--)
    {
        n = 0;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        if ((n % 2 == 1) && a[n + 1 >> 1] != b[n + 1 >> 1])
        {
            //特判奇数的情况，那时最中间的字符动不了
            //必须要求a,b中的中间字符的一样
            cout << "No\n";
            continue;
        }
        mp.clear();
        for (int i = 1; i <= (n >> 1); i++)
        {
            mp[make_pair(a[i], a[n - i + 1])] ++;
            mp[make_pair(a[n - i + 1], a[i])] ++;
        }
        int fl = 0;
        for (int i = 1; i <= (n >> 1); i ++)
        {
            if(mp[make_pair(b[i], b[n - i + 1])] == 0)
            {
                cout << "No\n";
                fl = 1;
                break;
            }
            mp[make_pair(b[i], b[n - i + 1])] --;
            mp[make_pair(b[n - i + 1], b[i])] --;
        }
        if(!fl) cout << "Yes\n";
    }
    return 0;
}
```

## 总结

打了很多场CF~~还是很菜~~，像字符串的操作类题目，特别是不限次数的，大部分是结论题，希望我的题解能对大家的OI学习起到帮助作用。

---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果](https://vipblog.github.io/fFLyfTS-c/)

## description：

把一个数字串进行若干次前缀与对应长度的后缀交换位置的操作，问是否能够变成另一个字符串。

## solution：

观察 swap 时的性质：任意一对原本在对称位置的数在 swap 后仍然会保持对称。

因为交换 $k$ 长度的前缀也就会对应 $k$ 长度的后缀，一组对称位置的数永远会要么同时互换位置，要不都不变。

这样就简化了题目，我们考虑把每一组对称数的位置都存到一个 map 中，直接 check 对数上是否对等即可。

## code：

上一个版本贴错代码了，感谢评论区 1 楼的神仙指出，已更换。

```cpp
#include<cstdio>
#include<map>
#include<algorithm> 
using namespace std;
int a[505],b[505];
map<pair<int,int>,int>mp;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
        mp.clear();
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
		}
		if(n%2==1&&a[(n+1)/2]!=b[(n+1)/2])
		{
			printf("No\n");
			continue;
		}
		for(int i=1;i<=(n+1)/2;i++)
		{
			mp[make_pair(min(a[i],a[n-i+1]),max(a[i],a[n-i+1]))]++;
		}
		int flag=0;
		for(int i=1;i<=(n+1)/2;i++)
		{
			//mp[make_pair(min(b[i],b[n-i+1]),max(b[i],b[n-i+1]))]--;
			if(--mp[make_pair(min(b[i],b[n-i+1]),max(b[i],b[n-i+1]))]<0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			printf("No\n");
		}
		else
		{
			printf("Yes\n");
		}
	}
	return 0;
} 
```

---

