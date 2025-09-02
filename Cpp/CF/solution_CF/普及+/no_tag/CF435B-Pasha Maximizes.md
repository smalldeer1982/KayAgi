# Pasha Maximizes

## 题目描述

Pasha has a positive integer $ a $ without leading zeroes. Today he decided that the number is too small and he should make it larger. Unfortunately, the only operation Pasha can do is to swap two adjacent decimal digits of the integer.

Help Pasha count the maximum number he can get if he has the time to make at most $ k $ swaps.

## 样例 #1

### 输入

```
1990 1
```

### 输出

```
9190
```

## 样例 #2

### 输入

```
300 0
```

### 输出

```
300
```

## 样例 #3

### 输入

```
1034 2
```

### 输出

```
3104
```

## 样例 #4

### 输入

```
9090000078001234 6
```

### 输出

```
9907000008001234
```

# 题解

## 作者：ToiletWater (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF435B)
# 题意分析：
 
 有一个长度为 $n$ 的正整数，可以交换相邻的两位上的数$k$次，求  $\max n$。

# 题解
##### _这是一道贪心！！！_
先来一组样例。（不是题目中的）
```
1034 3
```
我们可以知道，对于一个数 $n$，前面的位数越大，$n$ 就越大。

先不考虑 $k$，则1034最大为4301，但是现在有了 $k$ 的限制，就有以下几种方案。

### 第一种：
```
改变0次    1 0 3 4
改变1次    1 3 0 4
改变2次    3 1 0 4
改变3次    3 1 4 0
```
很容易想到从前往后找相邻的位进行比较，如果相邻的第二位大于第一位，则交换。

但是这样显然是不对的。

### 第二种：
```
改变0次    1 0 3 4
改变1次    1 0 4 3
改变2次    1 4 0 3
改变3次    4 1 0 3
```
此时得到的 $n$ 才是最大的，这样的方案就是尽量找大的数先放在第一位，然后把尽量能找到的数放在第二位，以此类推。

-----

### 为什么说尽量找最大的数呢？

因为当前位置 $now$ 能够放得数的范围是 $(now,now + \min(l,k + now)]$。
（$l$ 指的是 $n$ 的总长度）

当 $k + now > l$ 时在这个位置能放的数可以到最后，因为交换次数足够多，于是最大数在 $now \sim l$ 中选择。

但是当 $k + now < l$ 时，能交换到的最大数只能从 $now \sim now + k$ 中选择，再往后就无法交换了。

---------

### 把能找到最大的数放上来，后面的数怎么办？

根据样例可知，只需要将其余的数顺延，那么也能保证用最少的交换次数将最大数换上来。

--------

# AC Code
```cpp
//yjb出品，必属精品
#include<bits/stdc++.h>
using namespace std;
#define int long long
string n;
int m, a[25], l;
/*
m是题目中的k（交换次数）
a存储的是n的各个位
l是n的长度
*/
void work() {
	for (int i = 1;i <= l;++i) {
		if (m == 0) break;//当剩余交换次数为0时因为无法交换，所以直接退出
		int Max = i, p = min(l, m + i);
		for (int j = i + 1;j <= p;++j) 
			if (a[Max] < a[j]) Max = j;//找到尽可能大的数的位置
		int k = a[Max];
		for (int j = Max - 1;j >= i;--j) a[j + 1] = a[j];//每一位向后顺延，注意从后往前，不然前面的会被覆盖
		a[i] = k;
		m -= (Max - i);//次数减少，减去交换次数（移动位数）
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);//关闭流同步
	cin >> n >> m;
	l = n.length();
	n = ' ' + n;
	for (int i = 1;i <= l;++i) a[i] = n[i] - 48;//把n用数组存下来
	work();
	for (int i = 1;i <= l;++i) cout << a[i];
	return 0;
}
```



---

## 作者：FreedomKing (赞：1)

### 思路

考虑贪心。把更大的数移到更靠前的位置显然是更优的，因为位与位之间操作完不会互相影响所以可以拆位处理。对于第 $i$ 位，在剩余 $k_0$ 次操作时，最远可以操作 $i+k_0$ 位的数，也就是交换 $a_i$ 和 $\max_{j=i}^{i+k_0}\{a_j\}$。

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=3e4+5,mod=998244353;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int mxans=0;
			for(int i=x;i>1;i-=lowbit(i)) mxans+=tree[i];
			return mxans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[x]=y;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,vis=getchar(),t=1;
		while(vis<'0'||vis>'9'){
			t^=(vis=='-');
			vis=getchar();
		}
		while(vis>='0'&&vis<='9'){
			x=(x<<3)+(x<<1)+vis-'0';
			vis=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
string s,a,ans;
bool M2;signed main(){
	cin>>s;
	int k=qr,n=s.size(),maxn=0;
	a=" "+s;
	int tmpk=k;
	for(int i=1;i<=s.size();i++){
		maxn=i;
		for(int j=i+1;j<=i+tmpk&&j<=s.size();j++) if(a[j]>a[maxn]) maxn=j;
		for(int j=maxn;j>i;j--) swap(a[j],a[j-1]);
		tmpk-=(maxn-i);
	}
	for(int i=1;i<=n;i++) cout<<a[i];
	return 0;
}
```

---

## 作者：BotDand (赞：1)

# $\text{Problems}$

有一个长度为 $n$ 的正整数。可以对这个数进行交换相邻两个数位的操作。最多能进行 $k$ 次这样的操作，问能得到的最大的数是多少。

# $\text{Answer}$

对于每一个在第 $i$ 位的数，与在这之后的 $k$ 中的最大值交换（如果最大值小于该值则不交换）。

证明：要求最大数，肯定位数越高的数越大越好，因为有交换次数的限定，只能往后找 $k$ 位，交换即可得出最大值。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
string N;
int k;
int len;
int a[52];
int ma;
int main()
{
    cin>>N>>k;
    len=N.length();
    for(int i=0;i<len;++i) a[i+1]=N[i]-48;
    for(int i=1;i<=len;++i)
    {
        ma=i;
        for(int j=i+1;j<=i+k&&j<=len;++j) if(a[j]>a[ma]) ma=j;
        for(int j=ma;j>i;--j) swap(a[j],a[j-1]);
        k-=(ma-i);
    }
    for(int i=1;i<=len;++i) cout<<a[i];
    return 0;
}
```


---

## 作者：SuperBeetle (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF435B)

这道题算 CF 最水的绿题了，这道题一眼贪心。

但怎么贪心呢？ 

我们只需要在范围内枚举最大值即可。而这个范围，就是它能交换的次数，因为交换次数比可以的交换次数大，所以到不了想要的那一位，那选其他能交换到这里来的最大值不就行了吗？

### 话不多说，上代码！

```cpp
#include <bits/stdc++.h>
#define IAKIOI ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define UPB(x,y,z) upper_bound(x + 1, x + y + 1, z) - x
#define LWB(x,y,z) lower_bound(x + 1, x + y + 1, z) - x
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pre(i, l, r) for (int i = r; i >= l; i--)
#define UNQIUE(x, y) unqiue(x + 1, x + y + 1)
#define SORT(x, y) sort(x + 1,x + y + 1)
#define pf push_front 
#define pb push_back 
#define IT iterator
#define endl '\n';

const int N = 5e5 + 1, M = 5e4 + 1, INF = 0x3f3f3f3f;
const double ecnts = 1e-6;

#define int long long

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef double db;

void read(int &x) {
	int f = 1, y = 0;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		y = y * 10 + c - '0';
		c = getchar();
	}
	x = y * f;
}

void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline int max(int x, int y) {return x > y ? x : y;}
inline int min(int x, int y) {return x < y ? x : y;}

inline void swap(int &x, int &y) {int t = x;x = y, y = t;}
inline int pow(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1) ans *= x;
		x *= x, y = y >> 1;
	}
	return ans;
}

void solve() {
	string s;
	int n;
	cin >> s >> n;
	for (int i = 0, j = 0; j < n && i < s.size(); i++) { //i为位置，j为已经交换的次数，j<n是因为它如果已经交换了n次，那就交换不了了，直接退出即可
		int maxn = i; //最大数的位置
		for (int k = i, p = j; k < s.size() && p <= n; k++, p++) { //在范围内找最大值
			if (s[maxn] < s[k]) maxn = k; //取最大的位置
		}
		if (maxn != i) { //如果这个位置不是最大的
			char t = s[maxn]; //因为后面会覆盖当前位置，所以提前存起来
			pre(k, i, maxn - 1) s[k + 1] = s[k]; //倒序，不然覆盖后数会没
			s[i] = t; //当前位置改成最大值
			j += maxn - i; //会交换maxn - i次
		}
	}
	cout << s << '\n'; //输出
}

signed main() {
	IAKIOI;
	int t = 1;
		cin >> t;
	while (t--) {
		solve();
	}
}//完结撒花
```

---

## 作者：Jorisy (赞：0)

因为要让数字尽可能大，我们直接考虑让高位尽可能大即可。

于是贪心地，每次从高往低第 $i$ 位，找到第 $[i,\min\{i+k,n\}]$ 位内数码最大且靠前的往前移即可。

代码实现很简单，就不放了。

---

## 作者：SakurajiamaMai (赞：0)

### **思路:**
只需要让高位尽量最大就可以，由于数很大要用字符串来进行操作，用一个数记录要找的次数，从这个数向后找，直到次数用完，并记录下来最大的数，让他们交换。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
string s;
int res,n,num,cnt,i;
int main()
{
    cin>>s>>n;
    num=n;
    while(num>0){
        while(s[cnt]=='9'&&cnt<=s.size()) ++cnt;
        int maxx=cnt;
        if(cnt>=s.size()) break;
        for(i=cnt+1;i<=num+cnt&&i<s.size();i++) if(s[maxx]<s[i]) maxx=i;
        if(maxx==cnt){//如果后面没有比它大的了，那就找下一位。
            cnt++;
            continue;
        }
        for(i=cnt+1;i<=maxx;i++) swap(s[cnt],s[i]),num--;//每一步都要交换。
    }
    cout<<s<<endl;
    return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 思路
首先，这道题是一个贪心，要先保证第一位最大，然后是第二位以此类推。我们可以从前往后枚举每一位，然后往后枚举 $k$ 位去找一个最大的数，将它交换到前面。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[20];
int k;
signed main()
{
	cin>>(c+1)>>k;
	int l=strlen(c+1);
	for(int i=1;i<=l;i++)
	{
		int maxn=0;
		for(int j=i;j<=min(i+k,l);j++)//找最大的数 
		{
			maxn=max(maxn,(int)(c[j]-'0'));
		}
		for(int j=i;j<=min(i+k,l);j++)
		{
			if(c[j]-'0'==maxn)
			{
				k=k-(j-i);
				char ch=c[j];
				for(int d=j;d>i;d--)//交换 
				{
					c[d]=c[d-1];
				}
				c[i]=ch;
				break;
			}
		}
	}
	for(int i=1;i<=l;i++) cout<<c[i];
}
```

---

## 作者：ChikHid (赞：0)

### 首先看看题目吧:

一个 $n$ 位的数字，每次可以交换相邻的两位，但只能交换 $k$ 次（不一定要用完），求可以得到的最大的数。

***

非常的明显，这是一道贪心，肯定是把较大的数提到前面啊。

比如说样例 1：`1990 1`，因为 $1<9$，所以把 $1$ 和 $9$ 调换，得 $9190$。

我们就可以得出：每次判断相邻的两位，如果后者大于前者就交换，但事实真的如此吗？我们再看看一个数据：`451462 5`

如果我们按上面的方法，则：

1. $4<5$，交换，得 $541462$；
2. $1<4$，交换，得 $544162$；
3. $1<6$，交换，得 $544612$；
4. $4<6$，交换，得 $546412$；
5. $4<6$，交换，得 $564412$。

但这个答案是错的，正解:

1. 交换 $4$ 和 $6$，得 $451642$；
2. 交换 $1$ 和 $6$，得 $456142$；
3. 交换 $5$ 和 $6$，得 $465142$；
4. 交换 $4$ 和 $6$，得 $645142$；
5. 交换 $4$ 和 $5$，得 $654142$。

我们可以发现正解中先把 $6$ 提前到最高位，然后把 $5$ 提前到次高位，那如果 $k$ 更大呢？是不是把 $4$ 提前呢？

***

所以，我们又可以得出一个方法：将最高为替换成尽量大的数。照这种方法，我们来看看样例 3：`1034 2`

因为最大数是 $4$ ，但只能交换 $2$ 次，发现次大的 $3$ 正好交换 $2$ 次，于是把 $3$ 提前，得 $3104$，也就是答案。

***

所以，这种方法是正确的，那接下来就是代码实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int k,n,a[25];

int f(int x,int xx)                    //寻找可以替换到当前位的最大数
{
	int maxn=x-1;
	if(xx==0)
		return 0;
	for(int i=x;i<=n;i++)
		if(xx>a[i])
			if(a[maxn]<a[i])
				maxn=i;
	if(maxn-x+1>k)
		return f(x,a[maxn]);
	else
		return maxn;
}

int main()
{
	string nn;
	int x;
	cin>>nn>>k;                     //字符串处理更方便(自认为)
	n=nn.length();
	for(int i=1;i<=n;i++)           //转成数组(也可以用字符串直接做)
		a[i]=(int)nn[i-1]-48;
	for(int i=1;i<n;i++)
	{
		if(k==0)
			break;          //如果次数用完了就可以跳出循环
		x=0;
		x=f(i+1,10);
		k=k-(x-i);
		if(x!=0)                //如果找到这个数的话就提前
		{
			a[22]=a[x];
			for(int j=x;j>i;j--)
				a[j]=a[j-1];
			a[i]=a[22];
		}
	}
	for(int i=1;i<=n;i++)           //输出
		cout<<a[i];
	return 0;
}
```


---

