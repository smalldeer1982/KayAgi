# MEX maximizing

## 题目描述

Recall that MEX of an array is a minimum non-negative integer that does not belong to the array. Examples:

- for the array $ [0, 0, 1, 0, 2] $ MEX equals to $ 3 $ because numbers $ 0, 1 $ and $ 2 $ are presented in the array and $ 3 $ is the minimum non-negative integer not presented in the array;
- for the array $ [1, 2, 3, 4] $ MEX equals to $ 0 $ because $ 0 $ is the minimum non-negative integer not presented in the array;
- for the array $ [0, 1, 4, 3] $ MEX equals to $ 2 $ because $ 2 $ is the minimum non-negative integer not presented in the array.

You are given an empty array $ a=[] $ (in other words, a zero-length array). You are also given a positive integer $ x $ .

You are also given $ q $ queries. The $ j $ -th query consists of one integer $ y_j $ and means that you have to append one element $ y_j $ to the array. The array length increases by $ 1 $ after a query.

In one move, you can choose any index $ i $ and set $ a_i := a_i + x $ or $ a_i := a_i - x $ (i.e. increase or decrease any element of the array by $ x $ ). The only restriction is that  $ a_i $ cannot become negative. Since initially the array is empty, you can perform moves only after the first query.

You have to maximize the MEX (minimum excluded) of the array if you can perform any number of such operations (you can even perform the operation multiple times with one element).

You have to find the answer after each of $ q $ queries (i.e. the $ j $ -th answer corresponds to the array of length $ j $ ).

Operations are discarded before each query. I.e. the array $ a $ after the $ j $ -th query equals to $ [y_1, y_2, \dots, y_j] $ .

## 说明/提示

In the first example:

- After the first query, the array is $ a=[0] $ : you don't need to perform any operations, maximum possible MEX is $ 1 $ .
- After the second query, the array is $ a=[0, 1] $ : you don't need to perform any operations, maximum possible MEX is $ 2 $ .
- After the third query, the array is $ a=[0, 1, 2] $ : you don't need to perform any operations, maximum possible MEX is $ 3 $ .
- After the fourth query, the array is $ a=[0, 1, 2, 2] $ : you don't need to perform any operations, maximum possible MEX is $ 3 $ (you can't make it greater with operations).
- After the fifth query, the array is $ a=[0, 1, 2, 2, 0] $ : you can perform $ a[4] := a[4] + 3 = 3 $ . The array changes to be $ a=[0, 1, 2, 2, 3] $ . Now MEX is maximum possible and equals to $ 4 $ .
- After the sixth query, the array is $ a=[0, 1, 2, 2, 0, 0] $ : you can perform $ a[4] := a[4] + 3 = 0 + 3 = 3 $ . The array changes to be $ a=[0, 1, 2, 2, 3, 0] $ . Now MEX is maximum possible and equals to $ 4 $ .
- After the seventh query, the array is $ a=[0, 1, 2, 2, 0, 0, 10] $ . You can perform the following operations: 
  - $ a[3] := a[3] + 3 = 2 + 3 = 5 $ ,
  - $ a[4] := a[4] + 3 = 0 + 3 = 3 $ ,
  - $ a[5] := a[5] + 3 = 0 + 3 = 3 $ ,
  - $ a[5] := a[5] + 3 = 3 + 3 = 6 $ ,
  - $ a[6] := a[6] - 3 = 10 - 3 = 7 $ ,
  - $ a[6] := a[6] - 3 = 7 - 3 = 4 $ .
  
   The resulting array will be $ a=[0, 1, 2, 5, 3, 6, 4] $ . Now MEX is maximum possible and equals to $ 7 $ .

## 样例 #1

### 输入

```
7 3
0
1
2
2
0
0
10```

### 输出

```
1
2
3
3
4
4
7```

## 样例 #2

### 输入

```
4 3
1
2
1
2```

### 输出

```
0
0
0
0```

# 题解

## 作者：YooLc407 (赞：10)

## 题目大意

新定义：MEX（数列中最小未出现非负整数）

给定 $q$ 次询问，和指定的数 $x$ 。每次可以进行如下操作：

- 把给定的数插入数列中

- 选定数列中的任意数，使其增加或减少 $x$ （可进行多次）

每次询问后进行的操作都会在下一次被重置。需要保证数列中的数一直非负。

## 思路

考场上脑抽了，忘了 $x$ 是给定的...... 既然 $x$ 给定了，而且我们可以对一个数可以任意增加或减少 $x$ 的倍数，那么每一个数对我们有用的部分其实就是 $a_i\mod x$。

只要记录数组中模 $x$ 等于 $0$ ... 到 $x-1$ 的数字的个数就可以了。

对于每一次询问，我们从上一次的答案（最开始为 $0$）开始扫描，如果经过 $ans\mod x$ 时有可用的数字，那么就将记录的值 $-1$，代表我用过了，如果出现了 $ans\mod x$ 最终没有数字可用了，那么 ``MEX`` 就是 $ans$

## 部分代码

```cpp
int main()
{
	int q, x, ans = 0;
	q = rd(); x = rd();
	for(int i = 1; i <= q; ++i)
	{
		int opt = rd();
		vis[opt % x] ++; // 记录添加的数字
		while(vis[ans % x])
			vis[ans++ % x]--; // 这里有压行，实际先计算 vis[ans % x]--，再计算 ans++
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：zhangyuxing (赞：3)

只有像我这样的蒟蒻才打Div3吧/kk
___
因为这题满足可以+-任意次x，所以直接考虑%x处理。

然后我们就要维护%x后，每个值的出现次数。

发现Ans与最小值的大小与出现位置有关。

设最小值是$v$，出现的数是$id$，则$Ans=v×x+id$

最小值的大小和最小值的位置可以打个包，用线段树维护一下。

于是做到$O(n·logx)$，可以解决本题。

___
```cpp
#include<cstdio>
#include<cctype>
#define ls(k) k<<1
#define rs(k) k<<1|1
using namespace std;
const int maxn=1e6;
void read(int &x)
{
	int flag=1;
	x=0;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')flag=-1;
		c=getchar();
	}
	
	while(isdigit(c))
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	x*=flag;
}
int n,x;
struct Node{
	int id,v;
};
struct sgt{
	Node minn;
	int l,r;
}a[maxn<<2];
sgt merge(sgt ls,sgt rs)
{
	sgt ret;
	ret.l=ls.l;
	ret.r=rs.r;
	if(ls.minn.v<=rs.minn.v)ret.minn=ls.minn;
	else ret.minn=rs.minn;
	return ret;
}
void build(int l,int r,int k)
{
	if(l==r)
	{
		a[k].l=a[k].r=l;
		a[k].minn.id=l;
		a[k].minn.v=0;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,ls(k));
	build(mid+1,r,rs(k));
	a[k]=merge(a[ls(k)],a[rs(k)]);
}
void add(int l,int r,int t,int k)
{
	if(l==r)
	{
		++a[k].minn.v;
		return;
	}
	int mid=l+r>>1;
	if(t<=mid)add(l,mid,t,ls(k));
	else add(mid+1,r,t,rs(k));
	a[k]=merge(a[ls(k)],a[rs(k)]);
}
int main()
{
	int in,i;
	read(n);read(x);
	build(0,x-1,1);
	for(i=1;i<=n;++i)
	{
		read(in);
		add(0,x-1,in%x,1);
		printf("%d\n",a[1].minn.v*x+a[1].minn.id);
	}
	return 0;
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1294/D)
我们需要在每次查询后，计算数组的 MEX（最小未出现的非负整数），并且可以通过对数组中的元素进行加减 $x$ 的操作来最大化 MEX。

## 思路
这题思路比较难想，但代码十分简短。

将问题转换一下：

- 每次查询后，向数组中添加一个元素 $y_j$。

- 可以通过对数组中的元素进行加减 $x$ 的操作，使得数组中的元素尽可能覆盖从 $0$ 开始的连续整数。

关键点在于，对于每个元素 $y_j$，可以通过加减 $x$ 的操作，将其转换为 $y_j \bmod x$ 的[等价类](https://blog.csdn.net/shulianghan/article/details/108970289)。

我们需要统计每个等价类中的元素数量，并找到最小的未覆盖的整数。

于是我们可以这样：

1. 使用一个数组 `cnt` 来记录每个等价类中的元素数量。

2. 使用一个变量 `mex` 来记录当前的 MEX。

3. 对于每个查询，更新对应等价类的计数，并更新 `mex`。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[400005] ;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int q, x;
	cin >> q >> x;
	int mex = 0;
	while (q--) {
		int y;
		cin >> y;
		int mod = y % x;
		cnt[mod]++;
		// 更新 mex
		while (cnt[mex % x] > mex / x) {
			mex++;
		}
		cout << mex << '\n';
	}
	return 0;
}
```
代码十分简短，时间复杂度 $ \mathcal{O}(q) $，可以通过本题。

---

## 作者：Tyih (赞：1)

# solution

对于任意的 $a_i$ 只有 $a_i \bmod x$ 是有用的。考虑贪心，只要将每一种数的数量留一个，剩下的每次加 $x$ 直到不包含此数为止，并记录下来。最后枚举从 $0$ 开始第一个没有的数字即为答案。

为了提高效率，可以从 $ans$ 开始循环找到第一个不包含的数。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,x,a[500005],ans,k[500005],m;
bool vis[1000005];
int main(){
	cin>>q>>x;
	for(int i=1;i<=q;i++){
		cin>>a[i];
		m=a[i]%x;
		if(!k[m]) k[m]=m;
		while(vis[k[m]]&&k[m]<=q) k[m]+=x;
		vis[k[m]]=1;
		for(int j=ans;j<=q;j++)
			if(!vis[j]){
				ans=j;
				break;
			}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 思路

先记录原始数组的 mex 值，再考虑更改 a[i] 的操作。

对于 $\text{}\bmod x$ 值相同的数，操作时其实是等价的，所以 s 数组仅需记录 $\text{}\bmod x$ 值相同的数的个数即可。

操作时考虑是否有多余的数 $m$ ，使得 $m \equiv mex + 1 \pmod x$ 即可，若有，则判断下一个数是否能成为新的 mex，否则当前 mex 即为最大的 mex 值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int q, x, s[400001], ans;
int main() {
	scanf("%d%d", &q, &x);
	for (int i = 1;i <= q;i++) {
		int a;scanf("%d", &a);
		if (a % x == ans % x) ++ans;
		else s[a % x]++;
		while (s[ans % x]) s[ans % x]--, ans++;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Natsuzora (赞：1)

这里说一下官方题解中没有详细说明的$O(n)$解法。

先上代码
```cpp
#include <cstdio>
using namespace std;
const int N = 4e5 + 1;

int n, x, y, cnt[N], cntcnt[N], p, q;

int main(){
	scanf("%d%d", &n, &x);
	cntcnt[0] = x;
	for(int i = 1; i <= n; i++){
		scanf("%d", &y); y %= x;
		cntcnt[cnt[y]]--;
		cnt[y]++;
		cntcnt[cnt[y]]++;
		if(!cntcnt[p]) ++p, q = 0;
		while(cnt[q] > p) q++;
		printf("%d\n", p * x + q);
	}
	return 0;
}
```
首先与官方题解一样，因为每个数可以被任意地$±x$更改，我们将数字按照$\%x$后的值归类计数，用$cnt[k]$数组表示；

由于题目是求最小的未出现的数，我们优先将小的位置填满，因此从$0$开始往更大的数去填，可以发现，填$0$到$x-1$时正好从$cnt[0]$到$cnt[x-1]$各取出一个数，而每填进$x$个数，在$cnt$数组中取数的位置又从$0$到$x-1$开始轮回。

因此，使$p$为$cnt[0]$到$cnt[x-1]$中的值的最小值，$q$为使得$cnt[q]=p$的最小下标$q$，那么答案即为$p*x+q+1$。

接下来考虑如何维护$p$和$q$这两个值，用$cntcnt[k]$来记录$cnt$数组的**值**的出现次数。 初始时因为$cnt[0$ ~ $(x-1)]$都等于$0$，所以$cntcnt[0]=x$。那么$p$即为使得$cntcnt[p]>0$的最小下标$p$，$p$的初值为$0$。

由于题目只加数不删数也不会修改数，因此$p$是单调递增的，因此每次当$cntcnt[p]=0$时将$p++$；而当$p$不发生更新的前提下，$q$也是单调递增的，因此每次加数之后执行
```
	while(cnt[q] > p) q++;
```
当$q$发生更新时，先将$p$置为$0$，然后执行上述操作。

最后证明复杂度。设将要加入$n$个数，那么$q$最多更新到$n/x$，而每次$q$更新后$p$最多从$0$移动到$x-1$，也就是移动$x$次，那么$p$的总移动次数最多为$q$的更新次数乘上每次$q$更新后$p$的移动次数，即$n/x*x=n$，所以总复杂度为$O(n)$。

---

## 作者：been_apart (赞：1)

听说$div$ $3$不考数据结构？要考也只考栈和队列？

首先分析题目，允许让每个数加减任意次$x$，那么也就是说，这个数唯一的限制就是$mod$ $x$的结果不变。

所以直接对数取模即可，找到个数最少的模值即可，范围是$0$ ~ $x-1$。用一个小根堆维护。时间效率：$O(nlogn)$

具体的维护，答案计算还有些细节，自己试试就行了。下面给一个(很丑的)代码。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
struct tt{
	int id,x;
	bool friend operator <(tt xx,tt yy){
		if(xx.x==yy.x)return xx.id>yy.id;
		return xx.x>yy.x;
	}
};
int q,x,a[400005],y,ans;
priority_queue<tt> dl;
signed main(){
	q=read();x=read();
	for(re i=0;i<x;i++)dl.push((tt){i,0});
	for(int n=1;n<=q;n++){
		y=read();y%=x;a[y]++;dl.push((tt){y,a[y]});
		while(dl.top().x<a[dl.top().id])dl.pop();
		printf("%d\n",(dl.top().x)*(min(x,n))+dl.top().id);
	}
   	return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析
可以用取模把数字缩小到 $0$ 到 $m-1$（$m$ 指的是每次可以加上或者减去的数值）这样数组也可以开的到，如果把下 $x$ 加上，减去若干 $m$ 最后可以和 $cnt$ 一样的话，得 $cnt$ 取余等于 $x$ 取余 $m$，所以就可以用数组将 $x$ 取余 $m$ 的数量存储，之后看看 $cnt$ 取余 $m$ 有没有 $x$ 取余 $m$ 与之匹配就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x,m,cnt;
template <class T>
inline void read(T &ret){
    char c;
    int sgn;
    if(c=getchar(),c==EOF) return;
    while (c!='-'&&(c<'0'||c>'9')) c=getchar();
    sgn=(c=='-') ? -1:1;
    ret=(c=='-') ? 0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
    ret*=sgn;
    return ;
}
inline void out(ll x){
    if(x>9) out(x/10);
    putchar(x%10+'0');
}
const int M=4e+5+10;
int b[M];
int main(){
    read(n),read(m);
    while(n--){
        read(x);
        x%=m;
        b[x]++;
        while(b[cnt%m]>0) b[cnt%m]--,cnt++;
        out(cnt);
        putchar('\n');
    }
    return 0;
}


```

---

## 作者：The_foolishest_OIer (赞：0)

~~只有我这样的蒟蒻一开始没想到正解吧。~~

首先得知道几个性质：

- 第 $i$ 次操作的 MEX 必不小于第 $i-1$ 次操作的 MEX。

- 第 $i$ 操作的 MEX 必不大于 $i$。

把所有数分成 $x$ 组，第 $i$ 组数对 $x$ 取模所得余数为 $i$，维护每一组的最大值，MEX 直接暴力即可。

时间复杂度：$O(q + x)$，因为 MEX 最多跑 $q$ 遍。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 4e5 + 10;
int mx[N];
int mex,mexmod,q,x; // mexmod 表示上一次操作的 MEX 在第 mexmod 组
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> q >> x;
	for (int i = 0 ; i < x ; i++) mx[i] -= (x - i); // 预处理最大值
	for (int i = 1 ; i <= q ; i++){
		int y;
		cin >> y;
		int mod = y % x;
		mx[mod] += x;
		for (mexmod ; ; mexmod = (mexmod + 1) % x){
			if (mx[mexmod] < mex) break; // 如果没有这个数，那么这个数就是当前的 MEX
			mex++;
		}
		cout << mex << endl;
	}
	return 0;
}
```

---

## 作者：__zhuruirong__ (赞：0)

## 算法分析

观察数据范围，可以发现 $x$ 是较小的，所以可以让每个数字 $w_i\bmod x$（因为 $w_i$ 可以一直减 $x$ 直到不足 $x$，等价于 $w_i\bmod x$），再用一个桶存储出现数量，最后用一个 `multiset` 存储一个二元组（记作 $a$），第一位存储 $i\bmod x$ 出现的次数，第二位存储 $i\bmod x$，用于查找位置。

那么答案怎么求呢？

其实很简单，把 $a$ 的首个二元组第一位的乘 $x$ 再加上第二位就是答案。因为可以把两个数 $n_1$ 和 $n_2$（$n_1\equiv n_2 \pmod x$）中的 $n_1$ 设为 $i\bmod x$，$n_2$ 设为 $i\bmod x+x$，再多几个也一样。因为 `multiset` 会排序，所以首个二元组能组成的数量也一定最少，所以完整的 $x$ 个就只有这么多组。又因为当 $a$ 的首个二元组的第二位就是它前面还有多少个可以继续修改的数字。

但是记得要在最开始插入 $x$ 个 $0$，因为开始没有值。

## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int q, x, vis[N];
struct Node {
  int a, b;
  bool operator < (const Node& x) const { // 如果用pair就不用写这个。
    if(a != x.a)
      return a < x.a;
    return b < x.b;
  }
};
multiset<Node> s; 

int main() {
  // freopen("out.out", "w", stdout);
  cin >> q >> x;
  for(int i = 0; i < x; i++) s.insert({0, i});
  while(q--) {
    int y;
    cin >> y;
    s.erase({vis[y % x], y % x});
    vis[y % x]++;
    s.insert({vis[y % x], y % x}); // 更新二元组
    Node ans = *(s.begin());
    cout << ans.a * x + ans.b << endl;
  }

  return 0;
}
```

---

## 作者：zhu_wen (赞：0)

# MEX maximizing
## 主要题意
初始你有一个空序列，每一次往序列中加上一个数，你可以对序列中的数加或减 $x$ 的任意倍数，你的任务是在每一次找到数组内不存在的最小整数，并且通过操作使最小整数最大。
## 主要思路
我们从 $0$ 开始枚举，只要数组中不存在能变成这个数的数，那么这就是要找的最小整数，我们可以知道，对于 $a$ 和 $y$ 两个数，只要满足取余 $x$ 等于 $0$ 时，我们就可以将 $a$ 加上或减去 $x$ 的倍数就能变成 $y$。
## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int q, y, x;
int t[N];
int cnt = 0;

signed main()
{
    fst;
    q = read(), x = read();
    while (q--)
    {
        y = read();
        t[y % x]++;
        while (t[cnt % x])
        {
            t[cnt % x]--;
            cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
```


---

## 作者：123456zmy (赞：0)

首先发现可以将序列中元素的值改变 $x$，可以想到在 $%x$ 的结果上操作，然后用一个数组记录 $%m$ 后的各个值出现的次数然后模拟就可以了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,x,a[400001],y,ans1;
int main()
{
	scanf("%d%d",&q,&x);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&y);
		if(y%x==ans1%x)++ans1;
		else ++a[y%x];
		while(a[ans1%x])--a[ans1%x],ans1++;
		printf("%d\n",ans1);
	}
	return 0;
}
```


---

