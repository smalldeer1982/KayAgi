# Vacant Seat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/apc001/tasks/apc001_c

**これはインタラクティブな問題です。**

$ N $ を $ 3 $ 以上の奇数とします。

$ N $ 個の席が円状に並んでいます。 席には $ 0 $ から $ N\ -\ 1 $ まで番号が振られています。 各 $ i $ ($ 0\ <\ =\ i\ <\ =\ N\ -\ 2 $) について、席 $ i $ と席 $ i\ +\ 1 $ は隣り合っています。 また、席 $ N\ -\ 1 $ と席 $ 0 $ は隣り合っています。

各席の状態は「空席」「男性が座っている」「女性が座っている」のどれかです。 ただし、同性どうしが隣り合う席に座っていることはありません。 $ N $ が $ 3 $ 以上の奇数の場合、空席が少なくとも $ 1 $ つは存在することが示せます。

あなたには $ N $ のみが与えられ、各席の状態は与えられません。 あなたの目標は、どれか $ 1 $ つの空席の番号を当てることです。 そのために、あなたは次のクエリを繰り返し送ることができます。

- 整数 $ i $ ($ 0\ <\ =\ i\ <\ =\ N\ -\ 1 $) を選ぶ。 席 $ i $ が空席ならば、正答となる。 そうでなければ、席 $ i $ に座っている人の性別が知らされる。

クエリを高々 $ 20 $ 回まで送ることで、どれか $ 1 $ つの空席の番号を当ててください。

### Input &amp; Output Format

最初に、$ N $ が次の形式で標準入力から与えられる。

> $ N $

次に、クエリを繰り返し送る。 クエリは次の形式で標準出力へ出力する。 行末には改行を出力せよ。

> $ i $

これに対するクエリの答えは、次の形式で標準入力から与えられる。

> $ s $

$ s $ は `Vacant`, `Male`, `Female` のどれかである。 これらはそれぞれ、席 $ i $ の状態が「空席」「男性が座っている」「女性が座っている」であることを表す。

## 说明/提示

### 制約

- $ N $ は奇数である。
- $ 3\ <\ =\ N\ <\ =\ 99,999 $

### 注意

- 出力の度に標準出力を flush せよ。 そうしない場合、`TLE` の可能性がある。
- $ s $ が `Vacant` の場合、すぐにプログラムを終了せよ。 そうしない場合、ジャッジ結果は不定である。
- クエリ回数が $ 20 $ を超えた場合、およびクエリの形式が正しくない場合、ジャッジ結果は不定である。

### 入出力例 1

このサンプルでは、$ N\ =\ 3 $ であり、席 $ 0 $, $ 1 $, $ 2 $ の状態はそれぞれ「男性が座っている」「女性が座っている」「空席」である。

 InputOutput30Male1Female2Vacant

# 题解

## 作者：AKPC (赞：3)

`APC001` 的题目我肯定要水一个题解啊！

~~其实是 @ivyjiao 让我来的~~。
### 思路
因为是一个编号 $0\sim n-1$ 的一个环，而环的二分是不好搞的，所以可以先判断环的接头，即 $n-1$，然后就变成了数列，而不是环。

然后就是二分了，从 $l=0$，$r=n-1$ 开始二分。如果 $r-mid+1$ 为奇数且 $r$ 与 $mid$ 性别相同，或者 $r-mid+1$ 为偶数且 $r$ 与 $mid$ 性别不同，那么 $r\sim mid$ 这个区间是有空位的，这也就是 `check` 函数的写法，可以自己手推一遍。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100001],l,r,mid;
void ask(int mid){
	cout<<mid<<endl;
	string s;cin>>s;
	if (s[0]=='M') a[mid]=1;
	else if (s[0]=='F') a[mid]=0;
	else exit(0);
}
signed main(){
    cin>>n,r=n-1,ask(r);
    while (l<=r){
        mid=(l+r)/2;ask(mid);
		(r-mid+1)%2==(a[mid]==a[r])?r=mid:l=mid;
    }
    return 0;
}
```


---

## 作者：Acerkaio (赞：3)

[题面](https://atcoder.jp/contests/apc001/tasks/apc001_c)

### 思路:  
纯纯的二分交互题  
那我们如何确定空位的位置呢?  
我们第一次需要查询的是 $n-1$ 即编号最后一个的位置。判断是否是空位 。  
然后就是二分 $0$ 至 $n-1$ 了。如图:
![](https://cdn.luogu.com.cn/upload/image_hosting/u9gh9czb.png)  
每次查询 $mid$  分类讨论:  
如果 $[mid,r]$ 长度为奇数并且 $r$ 的性别与 $mid$ 性别不同，或如果 $[mid,r]$ 长度为偶数并且 $r$ 的性别与 $mid$ 性别不同相同，那么这 $[mid,r]$ 中有空位，否则没空位。  
### CODE:
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1000001];
char s[19];
inline void polling(int mid) {
	printf("%d\n",mid);
	fflush(stdout);
	scanf("%s",s);
	if(s[0]=='M') {
		a[mid]=1;
	} else if(s[0]=='V') {
		exit(0);
	}
}
int main() {
	scanf("%d",&n);
	polling(n-1);
	int l=0,r=n-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		polling(mid);
		if (((r-mid+1)%2==1) == (a[mid]==a[r])) {
			r=mid;
		} else {
			l=mid;
		}
	}
	return 0;
}
```


---

## 作者：spire001 (赞：2)

## AT_apc001_c 题解

蒟蒻的第一篇交互题题解。。。

### 前言
~~难道没有人觉得倍增比二分好写 $114514$ 倍吗？~~

~~交互题加倍增或二分评黄题合适吗？~~

### 题目分析
题目大意是给你一圈座位（座位数为奇数），有一个位置是空的，现在告诉你坐了人的位置满足没有两个同性的人的座位相邻。

为了知道空位编号是多少，你可以发送不超过 $20$ 次询问，询问某个位子上坐的是什么人（当然如果是空位那你就直接做完了）。

首先我们明白，如果没有空一个位置的话，同性不相邻这个条件是绝对不可能成立的。

对于一个环形座位，记 $a_i$ 为 $i$ 座位坐的人的种类，$1$ 为男，$0$ 为女。

那么很显然在 $i\equiv j\pmod 2$ 的时候 $a_i = a_j$。  
我们为了方便称这个性质为 $A$。

但是题目中人数为奇数所以 $2\mid (n-1)$。
又因为 $2\nmid 1$，所以这个空位的性质 $A$ 一定是从某个点之后发生了改变。

说人话，就是在空位之后，如果 $i\equiv j\pmod 2$，$a_i\neq a_j$。

然后我们就可以倍增求空位了。

我们初始位置为 $0$。
如果往前移 $2^k,k\ge 1$ 后仍然满足性质 $A$。我们就往前移。
否则就不动。

如果过程中发现了空位，就直接输出。
如果一直没有发现空位，最后到达的位置一定是最后一个有 $A$ 性质的位置，向前移动一个位置（即 $pos+1$）一定是空位。

### 代码实现
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef long long LL;

constexpr int N = 200010;
int a[N], n, b[N];

string res, tmp;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n;

  if (n <= 20)
  {
    for (int i = 0; i != n; i++)
    {
      cout << i << endl;
      cin >> res;

      if (res == "Vacant")
      {
        cout << i << endl;
        exit(0);
      }
    }
  }

  int pos = 0; 

  cout << pos << endl;
  cin >> res;

  if (res == "Vacant") // 初始位置就是空位 
  {
    cout << 0;
    exit(0);
  }

  for (int i = 17; i >= 1; i--) // 2^17 > 99999
  {
    if (pos + (1 << i) >= n) continue; // 越界
  
    cout << pos + (1 << i) << endl; // 询问

    cin >> tmp; // 结果

    if (tmp == res) pos += 1 << i; // 满足性质 A, 前移

    if (tmp == "Vacant") // 空位 
    {
      cout << pos << endl;
      exit(0);
    }
  }

  cout << pos + 1 << endl; // 不放心你也可以问一下
  
  return 0;
}
```

值得注意的是，在 $n\le3$ 的情况下这个算法并不正确，其原因是这个算法可能会误认为 $3$ 是空位。

但是在 $n\le 20$ 的情况下都可以直接暴力，所以仍然可以通过本题。

---

## 作者：Big_Dinosaur (赞：1)

鲜花：这题可以在[这里](https://www.luogu.com.cn/problem/list?type=AT&difficulty=5&page=6)看见。

为了方便，下文 `Male` 记为 `M`，`Female` 记为 `F`，`Vacant` 记为 `V`。

分三种情况考虑。
### 第一位是 `V`。
什么也不用做，答案出了。
### 第一位是 `M`。
按 $0\sim N-1$ 的顺序遍历座位构成的串一定为 `MF` 构成的串加上 `V` 再加上 `MF` 构成的串（可能为空）。二分答案，设询问的位置是 $x$，则：

- $x\bmod2=0$：若交互库返回 `M`，答案大于 $x$；反之小于 $x$。
- $x\bmod2=1$：若交互库返回 `M`，答案小于 $x$；反之大于 $x$。

证明：若没有 `V`，遍历座位构成的串是由 `MF` 组成的串。此时，位置编号为奇数为 `F`，否则为 `M`。加上 `V` 后，相当于 `V` 之后的位置后移一位。此时奇数为 `M`，否则为 `F`。因此对于询问的位置奇偶性与答案可得知答案范围，二分即可。
### 第一位是 `F`。
与上文类似。这里只给结论，证明类似。

- $x\bmod2=1$：若交互库返回 `M`，答案大于 $x$；反之小于 $x$。
- $x\bmod2=0$：若交互库返回 `M`，答案小于 $x$；反之大于 $x$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
namespace IO{
	inline int r(){
		int z=1,y=0;char t=getchar();while(t<'0'||t>'9'){if(t=='-')z=-1;t=getchar();}
		while(t<='9'&&t>='0'){y=(y<<1)+(y<<3)+(t^48);t=getchar();}return z*y;
	}
	inline void w_(int x){if(x<0){x=-x;putchar('-');}if(x==0)return;w_(x/10);putchar(x%10+48);}
	inline void wln(int x){if(x==0)putchar('0');else w_(x);putchar('\n');}
	inline void ww(int x){if(x==0)putchar('0');else w_(x);putchar(' ');}
	inline void w(int x){if(x==0)putchar('0');else w_(x);}
}
using namespace IO;
namespace d1n0{
	int L,R,m,f,N,mid;
	inline string ask(int x){
		cout<<x<<endl;
		string s;cin>>s;
		return s;
	}
	inline void _(){
		N=r();
		string s=ask(0);
		if(s[0]=='V')return;
		if(s[0]=='M')m=0,f=1;
		else f=0,m=1;
		L=1,R=N-1;
		while(L<=R){
			mid=L+R>>1;
			s=ask(mid);
			if(s[0]=='V')return;
			if(s[0]=='M'&&mid%2==m)L=mid+1;//过程与上文所述有所差别，但是本质相同。
			else if(s[0]=='F'&&mid%2==f)L=mid+1;
			else R=mid-1;
		}
	}
}
signed main(){d1n0::_();}
```

---

## 作者：ivyjiao (赞：1)

一个简单的二分交互题。

我们设 $a_i$ 为位置 $i$ 上的值。

我们第一次询问 $n-1$ 位置的值，判断是否空位。

然后就是二分 $1\sim n-1$ 的值。

在没有空位的情况下，当 $(r-mid)\bmod2=0$ 时，$a_{mid}\ne a_r$；$(r-mid)\bmod2=1$ 时，$a_{mid}=a_r$，这很容易想。

那么现在加上了空位，就变成了当 $(r-mid)\bmod2=0$ 时，$a_{mid}=a_r$；$(r-mid)\bmod2=1$ 时，$a_{mid}\ne a_r$。所以如果出现了这种情况，空位就在 $[mid,r]$ 之间，否则就在 $[l,mid]$ 之间。

$2^{20}>10^{5}-1$，过。

```cpp
#include<iostream>
using namespace std;
int n,a[100001],l,r,mid;
string s;
void check(int mid){
    cout<<mid<<endl;
    cin>>s;
	if(s[0]=='M') a[mid]=1;
	else if(s[0]=='F') a[mid]=0;
    else exit(0);
}
int main(){
    cin>>n;
    r=n-1;
    check(r);
    while(l<=r){
        mid=(l+r)/2;
        check(mid);
		if((r-mid+1)%2==(a[mid]==a[r])) r=mid;
		else l=mid;
    }
}
```

---

## 作者：EuphoricStar (赞：1)

## 思路

看到限制交互的次数和 $\log N$ 很接近，于是考虑二分。

首先先查询 $N - 1$ 的性别，然后令左端点为 $0$，右端点为 $N - 1$ 开始二分。

每次 check 先查询 $mid$ 的性别，然后考虑 $[mid,r]$ 这个区间。如果区间长度为奇数且 $mid$ 的性别等于 $r$，或者区间长度为偶数且 $mid$ 的性别不等于 $r$，说明 $[mid,r]$ 这个区间没有空位，空位一定在 $[l,mid]$ 中。反之则说明区间中有空位，将范围缩小到 $[mid,r]$。

注意交互时一旦查询到 $mid$ 为空位就要立刻退出程序。

## 代码

```cpp
const int maxn = 100100;

int n, a[maxn];
char s[19];

void query(int x) {
	printf("%d\n", x);
	fflush(stdout);
	scanf("%s", s);
	if (s[0] == 'M') {
		a[x] = 1;
	} else if (s[0] == 'V') {
		exit(0);
	}
}

void solve() {
	scanf("%d", &n);
	query(n - 1);
	int l = 0, r = n - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		query(mid);
		if (((r - mid + 1) & 1) == (a[mid] == a[r])) {
			r = mid;
		} else {
			l = mid;
		}
	}
}
```


---

## 作者：yanxu_cn (赞：0)

**本题中只有一个空座位。**

简单的交互题。

重点讲一下二分的判定：记 $l,r$ 为左右端点，$mid=\displaystyle{\frac{l+r}{2}}$。先判断 $mid$ 是不是是空的座位，如果是直接结束；如果不是，如果 $mid-l$ 是个奇数且 $mid$ 与 $l$ 对应的性别不同或者是偶数且性别相同，则空座位在 $mid$ 右侧。反之亦然。

贴代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
inline int check(int x)
{
	cout<<x<<endl;
	static string s;
	cin>>s;
	switch(s[0])
	{
		case 'V':return 0;
		case 'M':return 1;
		case 'F':return -1;
	}
}
int main()
{
	int n;
	string str;
	cin>>n;
	int l=0,r=n-1,cl=check(l),cr;
	if(cl==0)return 0;
	cr=check(r);
	if(cr==0)return 0;
	while(l<r)
	{
		int mid=(l+r)/2;
		int res=check(mid);
		switch(res)
		{
			case 0:
			return 0;
			default:
			if(mid-l+(cl==res)&1)
			{
				l=mid;
				cl=res;
			}
			else
			{
				r=mid;
				cr=res;
			}
		}
	}
	return 0;
}
```

---

## 作者：CatsFlyInTheOcean (赞：0)

~~这题怎么没有输入输出格式，翻译后才看懂~~

# 思路
因为最多询问 $20$ 次，但 $n\le99999$，所以用二分刚好不会炸。

### 先来看 ``` check ``` 函数：
先把要判断的 ``` mid ``` 输出，再输入性别。

我们用一个 $a$ 数组来存每个人的性别，如果是空位就不存。 
```cpp
void check(int x){
	cout<<x<<endl;
	string s;
	cin>>s;
	if(s=="Male"){
		a[x]=1;
	}//男性
	else if(s=="Female"){
		a[x]=2;
	}//女性
	else{
		return;
	}//空位
}
```
### 再来看二分过程：
我们先判断 $n-1$ 的位置是不是空位，然后二分 $0$ 至 $n-1$ 的值。

如果 $r-mid$ 为偶数并且 $mid$ 和 $r$ 座位上的人性别相同，那么 $mid$ 到 $r$ 的区间内有空位。

同理，如果 $r-mid$ 为奇数并且 $mid$ 和 $r$ 座位上的人性别不同，那么 $mid$ 到 $r$ 的区间内有空位。

否则，$l$ 到 $mid$ 的区间内有空位。

按照这个思路二分，直到 $ l=r$ 时结束。
```cpp
cin>>n;
int l=0,r=n-1;
check(r);
while(l<=r){
	int mid=(l+r)/2;
	check(mid);
	if((a[mid]==a[r])!=(r-mid)%2){
		r=mid;
	}
	else{
		l=mid;
	}
}
```
# 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005];
void check(int x){
	cout<<x<<endl;
	string s;
	cin>>s;
	if(s=="Male"){
		a[x]=1;
	}
	else if(s=="Female"){
		a[x]=2;
	}
	else{
		return;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int l=0,r=n-1;
	check(r);
	while(l<=r){
		int mid=(l+r)/2;
		check(mid);
		if((a[mid]==a[r])!=(r-mid)%2){
			r=mid;
		}
		else{
			l=mid;
		}
	}
	return 0;
}

```

---

## 作者：__Hacheylight__ (赞：0)

题意：
有一个周长为n的环形，每一格是一个座位，每个位置要么坐着一个男人M要么女人F要么空的V，但安排座位M和M不能并列且F和F不能并列，所以n个座位中至少一个座位是空着的，通过交换的方式在20步之内找出一个空着的座位的坐标。

解法：
首先，这是一道交互题，交互题的写法就是cout << ... << endl ; fflush(stdout) ;

我们先输出0和n-1，判断首和尾是M或者F或者V

然后二分mid找答案

然后r和mid之间有(r - mid - 1)个位置，



如果有奇数个位置，则当a[r] == a[mid]时，则在(l,mid)中必定有V 故r = mid，否则(mid, r)中必定有V故 l = mid。



如果有偶数个位置，则当a[r] ！= a[mid]时，则在(l,mid)中必定有V 故r = mid，否则(mid, r)中必定有V故 l = mid。

代码：

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

int n ;
int a[N] ;
string s ;

void get(int x) {
	printf("%d\n", x) ; fflush(stdout) ;
	cin >> s ;
	if (s[0] == 'M') a[x] = 1 ;
	if (s[0] == 'F') a[x] = 2 ;
	if (s[0] == 'V') a[x] = -1, exit(0) ;
}

signed main(){
	cin >> n ;
	int l = 0, r = n - 1 ;
	get(l) ; get(r) ;
	while (l + 1 < r) {
		int mid = (l + r) >> 1 ;
		get(mid) ;
		if ((r - mid - 1) & 1) {
			if (a[mid] == a[r]) r = mid ;
			else l = mid ;
		}
		else {
			if (a[mid] != a[r]) r = mid ;
			else l = mid ;
		}
	}
}

/*
写代码时请注意：
	1.是否要开Long Long？数组边界处理好了么？
	2.实数精度有没有处理？
	3.特殊情况处理好了么？
	4.做一些总比不做好。
思考提醒：
	1.最大值和最小值问题可不可以用二分答案？
	2.有没有贪心策略？否则能不能dp？
*/

```





---

