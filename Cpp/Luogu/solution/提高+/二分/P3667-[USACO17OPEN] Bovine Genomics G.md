# [USACO17OPEN] Bovine Genomics G

## 题目描述

Farmer John 拥有 $N$ 头有斑点的牛和 $N$ 头没有斑点的牛。他刚刚完成了一门关于牛遗传学的课程，并确信他牛身上的斑点是由牛基因组中的突变引起的。

Farmer John 花费巨资对他的牛进行了基因组测序。每个基因组是一个由字符 A、C、G 和 T 组成的长度为 $M$ 的字符串。当他将牛的基因组排列起来时，会得到如下表格，这里展示的是 $N=3$ 和 $M=8$ 的情况：

```
位置：   1 2 3 4 5 6 7 8

斑点牛 1：A A T C C C A T  
斑点牛 2：A C T T G C A A  
斑点牛 3：G G T C G C A A  

普通牛 1：A C T C C C A G  
普通牛 2：A C T C G C A T  
普通牛 3：A C T T C C A T  
```

仔细观察这个表格后，他推测从位置 2 到位置 5 的序列足以解释斑点现象。也就是说，通过仅查看这些位置（即位置 $2 \ldots 5$）的字符，Farmer John 可以预测哪些牛是有斑点的，哪些是没有斑点的。例如，如果他在这些位置看到字符 GTCG，他就知道这头牛一定是有斑点的。

请帮助 Farmer John 找到能够解释斑点现象的最短位置序列的长度。

## 样例 #1

### 输入

```
3 8
AATCCCAT
ACTTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT```

### 输出

```
4
```

# 题解

## 作者：Eafoo (赞：10)

## 前置知识：字符串Hash (板子：P3370)

一句话题意：给定 n 个A串和 n 个B串，长度均为 m，求一个最短的区间 $[l,r]$，使得不存在一个A串a和一个B串b，使得 $a[l,r]=b[l,r]$

在这篇题解中，我们使用a来代表A串中的一个串，b来代表B串中的一个串

使用 $a[l, r]$ 来代表 a串中从 l ~ r 位置的子串

最暴力的想法无非于先从小到大枚举最短的子串长度$len$，之后再枚举长度为$len$的所有区间$[l, r] (r = l + len - 1, 1 \le l \le r \le m)$，暴力判断每个A串 $a[l, r]$ 与每个B串 $b[l, r]$ 有没有重复，时间复杂度$O(n ^ 2 * m ^ 3)$，显然会超时

我们考虑判断区间$[l, r]$是否合法的操作进行优化。

具体操作（设当前判断的区间为 $[l, r]$）：

1.在操作进行前预处理出每个A串中 $a[1, x] (1 \le x \le m)$ 的Hash值，假定Hash时的进制数为 $p$ ，模数为 $mod$ ，那就有$Hash[l, r] = (Hash[r] - Hash[l - 1] * p ^ {r - l + 1} + mod) \% mod$

预处理代码：
```cpp
//strA[i][j]: 第i个A串中第j个字符
//hA[i][j]: 第i个A串中前j个字符构成子串的Hash值

for (int i = 1; i <= n; ++i)
{
	for (int j = 1; j <= m; ++j)
	{
		hA[i][j] = hA[i][j - 1] * p + strA[i][j];
	}
}
```


2.建立一个从整数映射到bool的map，名叫$vis$，遍历每个A串，将 $vis[Hash(a[l, r])]$ 设为 $true$

3.遍历每个B串，若 $vis[Hash(b[l, r])]$ 为 $true$，则当前区间不合法。若对于所有B串都有 $vis[Hash(b(l, r))] = false$，则当前区间合法。

代码：
```cpp
//pp[i]为已经预处理好的 p 的 i 次方
map<ull, bool> vis;

bool check(int l, int r)
{
	bool f = 1;
	vis.clear();
	for (int i = 1; i <= n; ++i)
	{
		vis[hA[i][r] - pp[r - l + 1] * hA[i][l - 1]] = 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (vis.count(hB[i][r] - pp[r - l + 1] * hB[i][l - 1]))
		{
			f = 0;
			break;
		}
	}
	if (f)
	{
		return true;
	}
	return false;
}
```

这样我们就可以把判断区间是否合法的操作从 $O(n ^ 2 * m)$ 优化到 $O(n logn * m)$，总时间复杂度 $O(nlogn * m ^ 3)$，仍然会超时。

于是我们考虑二分答案，对从小到大枚举区间长度 $len$ 的操作改为二分枚举，那么总时间复杂度降为 $O(nlogn * m^2logm)$，可以愉快的AC啦~

以下为AC代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
using namespace std;

int read() //快读
{
	int x = 0;
	char c;
	bool f = 0;
	while (!isdigit(c = getchar()))
	{
		if (c == '-')
		{
			f = 1;
		}
	}
	do
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
	} while (isdigit(c = getchar()));
	if (f)
	{
		return -x;
	}
	return x;
}

typedef unsigned long long ull;

const int maxn = 5e2 + 10;
const ull p = 131;

int n, m;

ull pp[maxn]; //p的i次方
ull hA[maxn][maxn], hB[maxn][maxn]; //Hash前缀和
char strA[maxn][maxn], strB[maxn][maxn]; //串

map<ull, bool> vis;

bool check(int len) //判断区间长度为len时合不合法
{
	for (int l = 1, r = l + len - 1; r <= m; ++l, ++r)
	{
		bool f = 1;
		vis.clear();
		for (int i = 1; i <= n; ++i) //枚举所有A串
		{
			vis[hA[i][r] - pp[r - l + 1] * hA[i][l - 1]] = 1;
		}
		for (int i = 1; i <= n; ++i) //枚举所有B串
		{
			if (vis.count(hB[i][r] - pp[r - l + 1] * hB[i][l - 1])) //这种操作尽量用count函数写，直接用下标方式写的话常数大很多
			{
				f = 0;
				break;
			}
		}
		if (f)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	n = read(), m = read();
	pp[0] = 1; //注意
	for (int i = 1; i <= 500; ++i) //预处理p的i次方
	{
		pp[i] = pp[i - 1] * p;
	}
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", strA[i] + 1);
		for (int j = 1; j <= m; ++j)
		{
        	//预处理前缀Hash
			hA[i][j] = hA[i][j - 1] * p + strA[i][j];
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", strB[i] + 1);
		for (int j = 1; j <= m; ++j)
		{
			hB[i][j] = hB[i][j - 1] * p + strB[i][j];
		}
	}
	int l = 1, r = m;
	int ans = 0;
	while (l <= r) //二分枚举区间长度
	{
		int mid = (l + r) >> 1;
		if (check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d\n", ans);
}
```


---

## 作者：45dino (赞：10)

自己做出的蓝题~~说明是恶评~~

众所周知，45dino连红题都做不对



------------
一开始只想到暴力，但发现要求的是最大的最小，于是可以使用二分，复杂度约为 $O(n^2)$ ,调了一下就A了，连氧都不用吸。



------------

讲一下二分（还用讲吗）

二分的要求就是求“最大的最小”或“最小的最大”

以本题为例，由于这一段长度为 $m$ 必然可以，而且要求最小值，所以符合“最大的最小”。

所以，可以进一步，如果出现“最大”或“最小”，基本上就是二分。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m; 
string a[501],b[501];
map<string,int> mp;
bool check(int x,int k)
{
	mp.clear();
	for(int i=1;i<=n;i++)	
		mp[a[i].substr(x,k)]=1;
	for(int i=1;i<=n;i++)
		if(mp[b[i].substr(x,k)])
			return 0;
	return 1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	int l=1,r=m;
	while(l<r)
	{ 
		int mid=(l+r)/2;
		bool flag=0;
		for(int i=0;i<=m-mid;i++)
			if(check(i,mid))
			{
				flag=1;
				break;
			}
		if(flag)
			r=mid;
		else
			l=mid+1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：COUPDETAT (赞：6)

## 二分+hash前缀和优化

#### 二分最短答案长度  
##### 二分就是优雅的暴力（苏神语录-001）

枚举长度为mid的区间 

然后用set存入第一种点

再用前缀和处理出该区间的hash值

每次都处理太浪费时间 预先处理出前缀和的一张哈希表

和set里的数据进行比对即可

### hash值不能直接减：
预处理出一个mul（模数的幂）

r-l时需要用1到r的hash值减去（1到l-1）*mul（r-l+1）

~~（读者自证不难）~~
### 关于set.find()
查找时如果找不到 就会枚举直到end()

如果找到了则不会

判断时不要像我这个傻逼一样写错if

```
#include<bits/stdc++.h>
using namespace std;
char s[510][510],t[510][510];
const int prime=198427;
int mul[510],hash_first[510][510],hash_second[510][510];
set<long long > f;	
int n,m;
bool check(int len)
{

	int re=0;
	for(int i=1;i+len-1<=m;i++)
	{
		f.clear();
		int flag=0;
		int j=i+len-1;
		for(int k=1;k<=n;k++)
			f.insert(hash_first[k][j]-hash_first[k][i-1]*mul[j-i+1]);
		for(int k=1;k<=n;k++)
			if(f.find(hash_second[k][j]-hash_second[k][i-1]*mul[j-i+1])!=f.end())
			{
				flag=1;
				break;
			}
		if(!flag)
		{
			re=1;
			break;
		}
	}
	return re;
}
int main()
{

	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i]+1;
	for(int i=1;i<=n;i++)
		cin>>t[i]+1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			hash_first[i][j]=(hash_first[i][j-1]*prime+s[i][j]);
		for(int j=1;j<=m;j++)
			hash_second[i][j]=(hash_second[i][j-1]*prime+t[i][j]);
	}
	mul[0]=1;
    for(int i=1;i<=m;i++) 
		mul[i]=mul[i-1]*prime;
	int l=1,r=m,ans=m;
	while(l<=r) 
	{
        int mid=(l+r)>> 1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
	cout<<ans;
 	return 0;
}
```


---

## 作者：jijidawang (赞：5)

有斑点和没斑点的牛称作 A 牛和 B 牛 .

最大值最小，显然二分（答案，即长度） .

然后问题就变成判断有没有满足长度 $L$ 的区间了 .

枚举左端点，算出右端点，然后把所有 A 牛的区间 Hash 值都丢到一个  `set`（或哈希表）里，然后对每个 B 牛的区间 Hash 值查询即可 .

时间复杂度 $O(nm\log m)$ .

***
P.S.

（以下 $n$ 是字符串长度，字符串下标从 $1$ 开始）

这里字符串 Hash 我用的是
$$\operatorname{Hash}(s)=\left(\sum_{i=1}^{n}s_i\cdot base^{n-i}\right)\bmod P$$
其中 $base$ 是定值 .

可以 $O(n)$ 求 $base$ 的幂，于是可以 $O(n)$ 递推 Hash 前缀和 $\operatorname{ph}(k)$，然后就可以随便求区间 Hash 值了
$$\operatorname{Hash}(s[l:r])=\operatorname{ph}(r)-base^{r-l+1}\cdot \operatorname{ph}(l-1)$$

关于正确性：

我们根据生日悖论，可以得到一个东西
> 考虑模数 $P$, 所有的哈希值都在 $P$ 之内
> 
> 于是每一次判定的错误率是 $\dfrac 1P$，在大约 $\sqrt P$ 次判定之后,错误率成为常数 .

可怕，，，这东西大概叫 *生日攻击* 罢 .

于是我们可以考虑双 Hash 或者加大模数，我就加大模数了 .

令
$$P=999999999999989$$
这样正确率就非常高力，但是我们递推求 $base$ 的幂和前缀 Hash 的时候需要乘法，于是就要搞 $10^{16}$ 级别的乘法模运算 .

我代码里用的是 $O(\log)$ 乘法 .
***

Code
```cpp
using namespace std;

typedef long long ll;
const int N = 555;
const ll P = 999999999999989, base = 131;
typedef char str[N];
int n, m;
ll pb[N];
ll mul(ll A, ll B) // O(log)
{
	ll ans = 0;
	while (B)
	{
		if (B & 1) ans = (ans + A) % P;
		B >>= 1; A = (A + A) % P;
	} return ans;
}
void init()
{
	pb[0] = 1;
	for (int i=1; i<N; i++) pb[i] = mul(pb[i-1], base) % P;
}
struct HashS
{
	ll ph[N];
	ll hash(int l, int r)
	{
		ll sub = l ? ph[l-1] : 0;
		return (ph[r] - mul(sub, pb[r-l+1]) + P) % P;
	}
	inline explicit HashS(const str& s)
	{
		ph[0] = s[0];
		for (int i=1; i<m; i++) ph[i] = (mul(ph[i-1], base) + s[i]) % P;
	}
};
vector<HashS> HA, HB;
str tmp;
unordered_set<int> H; // Hash Table
bool check(int len)
{
	for (int l=0; l<m; l++)
	{
		int r = l + len - 1;
		if (r >= m) continue;
		H.clear(); bool flg = true;
		for (int i=0; i<n; i++) H.insert(HA[i].hash(l, r));
		for (int i=0; i<n; i++)
			if (H.find(HB[i].hash(l, r)) != H.end()){flg = false; break;}
		if (flg) return true;
	} return false;
}
int main()
{
	init();
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; i++){scanf("%s", tmp); HashS x(tmp); HA.push_back(x);}
	for (int i=0; i<n; i++){scanf("%s", tmp); HashS x(tmp); HB.push_back(x);}
	int l = 0, r = m, ans;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)){r = mid - 1; ans = mid;}
		else l = mid + 1;
	} printf("%d\n", ans);
	return 0;
}

```

---

## 作者：Flandres (赞：3)

## 字符串哈希+二分

一道比较基础的字符串题。

先把所有的字符串的哈希值预处理出来，再从 $1$ 到 $m$ 枚举出区间长度 $len$，不难想到这一步可以使用二分答案将时间复杂度进一步优化。

对于每一个区间，我们知道区间内每一个子串的哈希值。在这里我用到了 STL 库中的 set 去重。

将前 $n$ 个代表 SpottCow 的字符串在这一区间内的哈希值扔到集合 $s_{1}$ 中，将后 $n$ 个代表 PlainCow 的字符串的哈希值扔到集合 $s_{2}$ 中。

当 $s_{1}$ 和 $s_{2}$ 两个集合内的元素没有重复时，当前的区间满足题意，否则不满足。记录当前的合法区间 $len$，继续二分找下一个更小的 $len$。

总体时间复杂度约为 $O(m\log m\cdot n\log n)$，可以通过。

详情见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int base=29;
const int LEN=514;
int n,m,N;
struct node{//存储每个字符串及其hash值
	char str[LEN];
	ull f[LEN];
}s[LEN<<1];
ull p[LEN];
inline bool check(int st,int ed,int len){	
	set <ull> s1;
	set <ull> s2;
	for(int i=1;i<=N;++i){
		if(i<=n) s1.insert(s[i].f[ed]-s[i].f[st-1]*p[len]);
		else s2.insert(s[i].f[ed]-s[i].f[st-1]*p[len]);		
	}
	int len1=s1.size(),len2=s2.size(),len3;
	s1.insert(s2.begin(),s2.end());
	len3=s1.size();
	if(len1+len2>len3)return false;//不符合题意
	return true;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	p[0]=1;
	for(int i=1;i<=500;++i)p[i]=(ull)(p[i-1]*base);
	N=(n<<1);
	for(int i=1;i<=N;++i){
		for(int j=1;j<=m;++j){
			cin>>s[i].str[j];
			s[i].f[j]=s[i].f[j-1]*base+s[i].str[j]-'A'+1;		
		}				
	}
	int l=1,r=m,mid;
	while(l<r){//二分答案
		bool flag=false;
		mid=(l+r)>>1;
		for(int st=1;st+mid-1<=m;++st){//枚举区间起点
			int ed=st+mid-1;//区间终点
			if(check(st,ed,mid)){//判断当前区间是否满足条件
				flag=true;
				break;
			}
		}
		if(flag) r=mid;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
``` 

---

## 作者：Muel_imj (赞：3)

## P3667 二分+hash前缀和+set

二分是很显然的，那么 check 的过程是一个给字符串判等的过程，那么自然就会想到 hash：

$$hash(s)=\sum_{i=1}^{n}{s_i·base^{n-i}}$$

(也就是把字符串看成一个 base 进制数)

(一般会加一个模数，但实际上放着不管就相当于对 unsigned long long 的最大值取模了，效率更高风险更大，至少在这题没出什么锅)

这样的 hash,用类似前缀和的思想存下到每一位的 hash 值之后，就可以做到 $O(1)$ 查询子串的 hash 值：

$$hash(s_{l-r})=hash(s_r)-hash(s_{l-1})·base^{r-l+1}$$

比如 $base=10$ 时：

$$hash(s_9)=123456789$$
$$hash(s_5)=12345$$
$$hash(s_{6-9})=123456789-12345·10^4=6789$$

(当然 base 要预处理 i 次幂)

---
二分答案长度，枚举每一个左端点，将前 n 个串的 hash 值存到 set 里，再遍历后 n 个字符串，如果某个字符串的 hash 值已在 set 里，说明有重复

---
一些让我最优解第二的卡常小技巧：

1. 读入字符串时，实测使用↓的cin比快读要快
```cpp
cin.tie(0),ios::sync_with_stdio(0);
```

2. unordered_set 是无序的听起来会快很多，但也因此迭代的效率不如普通set，在此题中也是set稍快一点点

完整代码qwq：
```cpp
#include<bits/stdc++.h>
#define EL puts("Elaina")
#define reg register int
#define qwq 0
using namespace std;
typedef unsigned long long ull;
const int maxn=5e2+3;
const ull base=5;
ull pw[maxn];
int val[137];
inline void init(){
    pw[0]=1,val['A']=1,val['C']=2,val['G']=3,val['T']=4;
    for(reg i=1;i<maxn;++i)
        pw[i]=pw[i-1]*base;
}
int n,m;
ull h[2][maxn][maxn];
char s[maxn];
inline void getHash(int p,int x){
    for(reg i=1;i<=m;++i)
        h[p][x][i]=h[p][x][i-1]*base+val[s[i]];
}
inline ull zStr(int p,int x,int l,int r){
    return h[p][x][r]-h[p][x][l-1]*pw[r-l+1];
}
inline bool check(int l,int r){
    set <ull> S;
    for(reg i=1;i<=n;++i){
        ull tmp=zStr(0,i,l,r);
        S.insert(tmp);
    }
    for(reg i=1;i<=n;++i){
        ull tmp=zStr(1,i,l,r);
        if(S.count(tmp))return 1;
    }
    return 0;
}
inline bool check(int len){
    for(reg l=1,r=len;r<=m;++l,++r)
        if(!check(l,r))return 1;
    return 0;
}
void solve(){
    cin>>n>>m;
    for(reg i=1;i<=n;++i)
        cin>>s+1,getHash(0,i);
    for(reg i=1;i<=n;++i)
        cin>>s+1,getHash(1,i);
	int l=0,r=m,mid,ans;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
}
int main(){
    cin.tie(qwq),ios::sync_with_stdio(qwq);
    init();
    solve();
    return qwq;
}
```


---

## 作者：Jμdge (赞：3)

csdn上写了篇blog，然后算法其实也很常规：差分+hash。

相较楼下可能也就是说我的blog写的详细一些吧...

然后附个连接我看看能不能过审吧~

[blog from csdn](https://blog.csdn.net/qq_35416331/article/details/80135708)

（如果能过审的话...还是挺不错的）

---

## 作者：User439000 (赞：2)

与别的不同的题解是，我的 hash 值生成极为简单。
```cpp
long long h(int point ,char as)//point为字符位置
{
	return point*as;
}
```
这样我们得到了一个简易的哈希生成器。但这样遇到的问题是：不同的字符串哈希值有一定概率可能会相等。为了解决这一瑕疵，我们遇到哈希值相等时候，可以直接将两个字符串一一比较，看看是否真的为同一字符串。这样一来即使哈希掌握得不太好，也依然能通过此题。

做法：给每个字符串每个字符生成对应哈希值，用一个数组保存起来，然后再用一个数组保存好每个字符串的前缀和。这时候我们二分长度，二分的长度是否能满足题意，我们需要一一将每个斑点马的部分基因与无斑点马的部分基因对照，看看是否有相同的（用前面计算的 哈希值判断）。如果这时候哈希值相等了，有可能是不同的字符串（毕竟我这个哈希生成较简单，而且题目只有四种字母，遇到不同字符串哈希值相等的概率还是有的），那我们朴素验证是否为同一字符串即可。这样我们就用哈希排除了很多不可能相等的字符串，减少的朴素验证的次数。

上代码（附注释）。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct pp{
	string s;
}a[1050];
long long n,m,b[1050][505],c[1050][505];//b 装每第 i 个字符串的第j字符的hash值，c则为第i个字符串第j位置的前缀和 
bool check(int len){
	for(int bg=0;bg<m-len;bg++)//枚举基因的起点 
	{
		int pd=0;//作为判断是否遇到相同基因的标记 
	for(int i=1;i<=n;i++)// 这是斑点牛基因的循环 
	{
	for(int u=n+1;u<=2*n;u++)// 这是没有斑点的牛基因的循环 
	{
		long long temp=c[i][bg+len]-c[i][bg]+b[i][bg]-b[i][bg+len],temp1=c[u][bg+len]-c[u][bg]+b[u][bg]-b[u][bg+len];//利用前缀和求子串hash值 
		if(temp==temp1)//核心点：如果 hash 值相等了，那么朴素比较两个字符串 
	    {
	    	int sum=0;
	    	for(int j=bg;j<bg+len;j++)
	    	{
	    		if(a[i].s[j]==a[u].s[j])
	    		sum++;
			}
			if(len==sum)//成立说明两个字符串完全相等 
	    	{
	    		pd=1;
	    		break;//那么这个点并不能作为基因起点，退出到最大的那个循环去 
			}
		}
	}
	if(pd==1)break;
	}
	if(pd==0)return 1;//如果 bg 作为起点符合题意，就没必要再枚举其他符合题意的点了 
}
return 0;//如果每个点作为起点都枚举完了，找不到符合要求的就返回假； 
}

long long h(int point ,char as)
{
	return point*as;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=2*n;i++)cin>>a[i].s;
	
	for(int i=1;i<=2*n;i++)//hash 每个字符 
	for(int u=0;u<m;u++)b[i][u]=h(u,a[i].s[u]);

	for(int i=1;i<=2*n;i++)c[i][0]=b[i][0];// hash 前缀和初始化下 
	
	for(int i=1;i<=2*n;i++) // hash 前缀和
	for(int u=1;u<m;u++)c[i][u]=c[i][u-1]+b[i][u];

	int l=1,r=m;
	while(l<r){//二分长度 
	int mid=(l+r)>>1;
	if(check(mid))r=mid;else l=mid+1;
}
	cout<<l;
}
```



---

## 作者：liangchenming (赞：2)

第一次发题解。

作为蒟蒻终于有会并且还可以提交题解的题了还是很开心的。

## 思路
首先这个题是一道字符串匹配的题，可以用哈希解决。

其次这个题是一道求最短区间的题，那么很容易就能想到从 $1$ 到 $m$ 枚举区间长度再上下匹配,但这样的情况下复杂度将会达到  $O(m^2/2 \times n^2)$，绝对超时。                   

然后我想到二分，但我太蒟蒻只听说过二分查找，不过忽然在看二分查找时看到一个新名词：二分答案。而最短区间长度这些东西就是很典型的可以靠二分答案去解决的。

那这道题突然就好办了，二分枚举匹配长度就行了。

比如说每行有 $500$ 个基因字符组成的基因组，那就首先假设 $250$ 是最短区间长度，拿它去上下暴力匹配，
如果有不存在一个 $A$ 串 $a$ 和一个 $B$ 串 $b$，使  $a[l,r]=b[l,r]$ 的情况出现，那么就说明这一段长度可行，再二分左边（$1$ 到 $250$）假设 $125$ 是最短区间。

那如果说 $250$ 不行，就说明最短长度要更长，就去二分右边假设 $375$ 是最短区间。

以此类推，最后当左右节点相等时得出的就是最终答案。

这样以来，原本需要约 $O(m^2/2)$ 枚举区间长度的时间复杂度，就直接降低为了这个更优的 $O(\log_2m)$ 的时间复杂度了。

但是上下直接匹配的过程仍然会乘上 $n^2$ 级别的时间复杂度，并不优美，所以可以把在枚举某区间时先把后 $n$ 行扫一遍，用 $map$ 数据结构维护某个哈希值是否出现过，这样再扫前 $n$ 行时就可以以 $O(n \times \log n)$ 的时间复杂度查找该子串是否在后 $n$ 行。

中出现过了，那么总体时间复杂度就降为了 $O(\log_2 m \times n \times \log n)$，蛮快的。                   

## 代码

```cpp
#include<bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;//二分答案查找 
char a[1200][600];
ll f[1200][600];
ll c[1200];//每一行暂时存的哈希值 
ll B=233;
ll Bi[1200];
int n,m;
int ans;
map<ll,ll> maps;
int main()//查找是否有和它不在同一组但是哈希值一样的，有的就直接舍 
{
	cin>>n>>m;
	for(int i=1;i<=2*n;i++)
	{
		scanf("%s",a[i]+1);
		f[i][0]=0;
		for(int j=1;j<=m;j++)
		{
			f[i][j]=f[i][j-1]*B+a[i][j];
		}
	}
	int l=1;int r=m;Bi[0]=1;
	for(int i=1;i<=m;i++)Bi[i]=Bi[i-1]*B;
	while(l<r)//log2n查找 
	{
		int mid=(l+r)>>1;
		int len=mid;		
		bool flag=0;//flag=1就说明这么小的地方不够 
		for(int i=1;i+len-1<=m;i++)//n查找 
		{
			flag=0;
			int j=i+len-1;//区间右端点
			memset(c,0,sizeof(c));
			maps.clear();
			for(int u=1;u<=2*n;u++)
			{
				c[u]=f[u][j]-f[u][i-1]*Bi[len];
				//cout<<"cu1="<<c[u]<<endl;
			}			
			for(int u=n+1;u<=2*n;u++)
			{
				maps[c[u]]=u;//表示这个哈希值对应的在u这里 
			} 
			for(int u=1;u<=n;u++)
			{
				if(maps[c[u]])//说明存在与之相同的子串
				{
					
					flag=1;
					break;
				} 
			}
			if(flag==0)break;//只要有一个地方做到了这里不存在一个alr=blr了，就及时跳出向左走
		}
		if(flag==1)
			l=mid+1;//就说明答案还要更大一些
		else
		 	r=mid;
	}
	cout<<l; 
}
```



---

## 作者：俺是小程 (赞：2)

其实二分 + trie树也是可以水过去的qwq     
总的来说, 就是二分长度, 用`trie树`来判断是否可行.   
思路倒是简单, 可是常数不知道大到哪儿去了.  

```cpp
#include <cstdio>
#include <stack>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 5e2 + 20;


    
int N, M;
char str[MAXN << 1][MAXN];

inline int getnum(char ch){
    switch (ch){
        case 'A': return 0;
        case 'T': return 1;
        case 'C': return 2;
        case 'G': return 3;
    }
}

namespace trie
{
    struct Node
    {
        bool ended;
        Node *ch[4];
        Node() : ended(false) {}
    }pool[MAXN * MAXN], *pit = pool, root, null;

    int cnt = 1;

    inline Node *newnode(){
        if(cnt < (MAXN * MAXN)) return ++cnt, new(pit++) Node();
        return new Node();
    }

    Node *insert(Node *cur, char s[], int p){
        if(!cur) cur = newnode();
        if(!p) return cur->ended = true, cur;
        cur->ch[getnum(*s)] = insert(cur->ch[getnum(*s)], s + 1, p - 1);
        return cur;
    }

    bool query(Node *cur, char s[], int p){
        if(!cur) return false;
        if(!p) return cur->ended;
        return query(cur->ch[getnum(*s)], s + 1, p - 1);
    }

    void init(){
        for(int i = 0; i < 4; i++) null.ch[i] = NULL;
        null.ended = false;
        for(int i = 0; i < cnt; i++) pool[i] = null;
        pit = pool, cnt = 1; root = null;
    }
}

bool check(int x){
    using namespace trie;
       
    for(int l = 1; l <= (M - x + 1); l++){
    	init();
        for(int i = 1; i <= N; i++) insert(&root, str[i] + l, x);
        bool flag = false;
        for(int i = N + 1; i <= (N << 1); i++) 
            if(query(&root, str[i] + l, x)) {
                flag = true; break;
            }
        if(!flag) return true;
    }

    return false;
}

int main()
{
    //freopen("p3667.in", "r", stdin);
    cin>>N>>M;
    for(int i = 1; i <= (N << 1); i++) scanf(" %s", str[i] + 1);

    int l = 0, r = M;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    } 
    cout<<l<<endl;
    return 0;
}

```


---

## 作者：nihanchu (赞：2)

我首先首先先考虑了二分+hash，但可能是我的二分有点问题，一直tle了一个点，然后完全不知道怎么去改变，只能去USACO的官网上看，结果发现了更厉害的方法。


原英文题解：[http://www.usaco.org/current/data/sol\_cownomics\_gold\_open17.html](http://www.usaco.org/current/data/sol\_cownomics\_gold\_open17.html)


那么我按照我的理解讲一下，首先我们开始定义一个区间lef和righ，开始我们将其全部赋值为0，表示求出lef+1到righ这个区间各个牛的hash值(我是用rand(),不过这个看自己的心情随便赋值吧），然后看看有没有重复的，如果这个区间双方的牛互相没有相同的hash值那么就可以更新答案，同时将lef++,同时每头牛的hash值减去最前面一个字母的hash,然后继续往下做（意思就是如果当前符合答案，那么我们把这个区间的最前面一位去掉，看看是否有更优的答案），如果有相同的hash值，那么说明当前区间还不可以，所以righ++，并将每头牛的hash值加上后面一位的值进行更新。他利用的就是如果当前区间是可行的，那么把它当做后缀的区间也一定是可行的，所以一定会访问到这个可行区间。

(感觉自己的分析很不清楚，可能有错误，很抱歉。。)

分析了一下，它的hash值计算是从上一次的推出来的，而我之前hash是每次都重新计算一遍，所以。。。


对了判断hash有无，很方便的可以用set来。


下面是具体程序：

复制代码


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#define maxn 1009
#define mo 53894320
using namespace std;
typedef long long ll;
char ch[maxn];
int n,ans,m,t;
ll val[maxn],s1[maxn][maxn],s2[maxn][maxn],hash1[maxn],hash2[maxn];
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;i++) 
  {
   scanf("%s",ch);
   for (int j=0;j<m;j++) s1[i][j]=ch[j]-65;
  }
  for (int i=1;i<=n;i++) 
  {
   scanf("%s",ch);
   for (int j=0;j<m;j++) s2[i][j]=ch[j]-65;
  }
  for (int i=0;i<m;i++) val[i]=rand()%mo;
  ans=m;t=n;
  int lef=0,righ=0;
  while (righ<m)
  {
       set<ll>p; 
       if (t==0) ans=min(ans,righ-lef);
       if (t>0)
       {
        t=0;
        for (int i=1;i<=n;i++) 
      {
       hash1[i]=(hash1[i]+s1[i][righ]*val[righ])%mo;
       p.insert(hash1[i]);
      }
      for (int i=1;i<=n;i++)
      {
       hash2[i]=(hash2[i]+s2[i][righ]*val[righ])%mo;
       if (p.count(hash2[i])) t++;
      }
      righ++;
     }
     else
     {
      t=0;
      for (int i=1;i<=n;i++) 
      {
       hash1[i]=((hash1[i]-(s1[i][lef]*val[lef]))%mo+mo)%mo;
       p.insert(hash1[i]);
      } 
      for (int i=1;i<=n;i++)
      {
       hash2[i]=((hash2[i]-s2[i][lef]*val[lef])%mo+mo)%mo;
       if (p.count(hash2[i])) t++;
      }
      lef++;
     }
  }
  printf("%d\n",ans);
  return 0;
}
```

---

## 作者：_edge_ (赞：1)

提供一种常数较小的解法。

[详细题意](https://www.luogu.com.cn/discuss/157857)。

看到这道题目，很容易想到的解决方案是枚举长度，然后把一类字符串里面的字串拿出来，和二类字串进行比较。

比较的话可以利用 hash 实现，总时间复杂度是 $O(n^3)$，还有可能会爆空间，如果你用另类 STL 实现 hash 判重需要多只 $\log$，完全跑不过去。

我们来寻找最优答案，他肯定是一段子串，对于包含他的子串也必定成立。

因此具有单调性，可以进行二分答案，然后判重，这样的复杂度是 $O(n^2 \log n)$，或者实现不好可能会两只 $\log$，具体代码可以翻我的提交记录。

当然，我们需要做的是进一步进行优化，二分答案是维护一段区间，事实上有更加优秀的方法来代替这种，就是枚举左端点算出可行的最左边的右端点，然后对于下一个左端点进行继承操作，单调性和二分答案一样。

如果这样实现的话就可以拿掉一只 $\log$，复杂度是 $O(n^2)$ 的，~~但是我实现的不够优秀，还是变成了 $O(n^2 \log n)$~~。

这里介绍几种卡常方式，用 map set 等 STL 常数真的很大，我们把哈希的东西存到一个数组里面，然后进行 lower_bound 查找是否出现，当然前提是要排序。

这样常数以及够小了，如果还不满意可以把取模哈希改成自然溢出，这样也会减小常数。

目前我在最优解 rk2。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=505;
const int base=233;
int n,m;
string s1[INF],s2[INF];
unsigned long long ba[INF],hash1[INF][INF],hash2[INF][INF],p[INF];
unsigned long long  Get1(int x,int l,int r) {return (hash1[x][r]-hash1[x][l-1]*ba[r-l+1]);}
unsigned long long  Get2(int x,int l,int r) {return (hash2[x][r]-hash2[x][l-1]*ba[r-l+1]);} 
bool check(int len) {
	for (int i=1;i+len-1<=m;i++) {
		p[0]=0;
		for (int j=1;j<=n;j++)
			p[++p[0]]=Get1(j,i,i+len-1);
		sort(p+1,p+1+p[0]);int fl=0;
		for (int j=1;j<=n;j++) {
			unsigned long long xx=Get2(j,i,i+len-1);
			int it=lower_bound(p+1,p+1+p[0],xx)-p;
			if (p[it]==xx) {fl=1;break;}
		}
		if (!fl) return 1;
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;ba[0]=1;
	for (int i=1;i<=m;i++) ba[i]=ba[i-1]*base;
	for (int i=1;i<=n;i++) {
		cin>>s1[i];s1[i]=" "+s1[i];
		for (int j=1;j<=m;j++)
			hash1[i][j]=(hash1[i][j-1]*base+s1[i][j]);
	}
	for (int i=1;i<=n;i++) {
		cin>>s2[i];s2[i]=" "+s2[i];
		for (int j=1;j<=m;j++)
			hash2[i][j]=(hash2[i][j-1]*base+s2[i][j]);
	}
//	cout<<check(2)<<" ?\n";
//	int l=1,r=m,ans=-1;
//	while (l<=r) {
//		int Mid=(l+r)>>1;
//		if (check(Mid)) r=(ans=Mid)-1;
//		else l=Mid+1;
//	}
//	cout<<ans<<"\n";
	int r=1,ans=1e9;
	for (int i=1;i<=m;i++) {
		int cnt=0;
		while (r+1<=m) {
			p[0]=0;
			for (int j=1;j<=n;j++)
				p[++p[0]]=Get1(j,i,r);
			sort(p+1,p+1+p[0]);int fl=0;
			for (int j=1;j<=n;j++) {
				unsigned long long xx=Get2(j,i,r);
				int it=lower_bound(p+1,p+1+p[0],xx)-p;
				if (p[it]==xx) {fl=1;break;}
			}
			if (!fl) {cnt=1;break;}
			r++;
		}
		if (cnt) ans=min(ans,r-i+1);
	}
	cout<<ans<<"\n"; 
	return 0;
}
```


---

## 作者：Rolling_star (赞：1)

updated：修改了部分不符合题解规范的标点，管理员大大辛苦了，求通过

如果我们通过 hash 硬跑暴力，复杂度是 $O(n^4)$ 的，   $n=500$ 显然会超时,所以要逐步优化。

### Step 1
通过观察可以发现，查询 $A,B$ 各串的 hash 值时可以将其中一个串的 hash 值排序，然后以另外一个串的 
hash 值在其中查找，可以把时间复杂度降到 
$O(n^3\log n)$ ，但显然不够，所以需要进一步优化。
```cpp
ll tmp[n+5];
for(int k=1;k<=n;k++)
	tmp[k]=gethashb(k,i,j);
sort(tmp+1,tmp+n+1);
for(int k=1;k<=n;k++){
	int temp=lower_bound(tmp+1,tmp+1+n,gethasha(k,i,j))-tmp;
	if(tmp[temp]==gethasha(k,i,j)){
		flag=true;
		break;
	}
}
```
### Step 2

不难发现对于一个固定的左端点，答案对于长度具有单调性。

比如对于右端点为 $1$ 的情况，如果左端点在第 $i$ 个位置 $A,B$ 串都不相等，那对于任意的 $j>i$ ， $A,B$ 串均不相等。

所以枚举左端点，对子串长度进行二分，找出符合答案的最小解，统计入答案即可，最终时间复杂度为 $O(n^2\log^2n)$ 。

还需要注意的一点是这道题答案的单调性有所不同，在右侧二不是左侧，最小值而不是最大值。

蒟蒻码风不佳，勿喷。
```cpp
#include<bits/stdc++.h>
#define N 505
#define B 233
#define ll long long
using namespace std;

const ll mod=1e9+21;
int n,m,ans=N+100;
ll p[N],hash_suma[N][N],hash_sumb[N][N];
string a[N],b[N];
inline string getstr();
inline ll gethasha(int i,int l,int r);
inline ll gethashb(int i,int l,int r);

int main(){
	cin>>n>>m;
	p[0]=1;
	for(int i=1;i<=N-2;i++)
		p[i]=p[i-1]*B%mod;
	for(int i=1;i<=n;i++)
		a[i]=getstr();
	for(int i=1;i<=n;i++)
		b[i]=getstr();
	for(int i=1;i<=n;i++){
		hash_suma[i][0]=a[i][0];
		hash_sumb[i][0]=b[i][0];
		for(int j=1;j<m;j++){
			hash_suma[i][j]=(hash_suma[i][j-1]*B+a[i][j])%mod;
			hash_sumb[i][j]=(hash_sumb[i][j-1]*B+b[i][j])%mod;
		}
	}
	for(int i=0;i<m;i++){
		int l=1,r=m-i;
		int t=605;
		while(l<=r){
			int mid=(l+r)>>1;
			int j=i+mid-1;
			bool flag=false;
			ll tmp[n+5];
			for(int k=1;k<=n;k++)
				tmp[k]=gethashb(k,i,j);
			sort(tmp+1,tmp+n+1);
			for(int k=1;k<=n;k++){
				int temp=lower_bound(tmp+1,tmp+1+n,gethasha(k,i,j))-tmp;
				if(tmp[temp]==gethasha(k,i,j)){
					flag=true;
					break;
				}
			}
			if(flag) l=mid+1;
			else{
				t=min(t,mid);
				r=mid-1;
			}
		}
		if(t) ans=min(ans,t);
	}
	cout<<ans;
} 

inline string getstr(){
	char ch=getchar();
	string s="";
	while(ch==' '||ch=='\n')
		ch=getchar();
	while(ch!=' '&&ch!='\n')
		s+=ch,ch=getchar();
	return s;
}

inline ll gethasha(int i,int l,int r){
	return (hash_suma[i][r]-hash_suma[i][l-1]*p[r-l+1]%mod+mod)%mod;
}

inline ll gethashb(int i,int l,int r){
	return (hash_sumb[i][r]-hash_sumb[i][l-1]*p[r-l+1]%mod+mod)%mod;
}
```

---

## 作者：Hanghang (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P3667)

介绍一种 $O(n^2)$ 的算法。

简单浏览题目，发现是个字符串题，自然想到哈希。

先考虑如何判断区间 $l$ 到 $r$ 是符合条件，把前面 $n$ 个串 $l$ 到 $r$ 的哈希值放到 `unordered_set` 里面，查询后面 $n$ 个串的哈希值是否出现过。复杂度 $O(n)$。

然后考虑怎么枚举 $l$，$r$。这里就是个套路，[滑动窗口](https://www.luogu.com.cn/problem/P1886)，不会的可以去学习一下。由于 $r$ 在加，$l$ 在加，枚举的复杂度是 $O(n)$。

所以总的复杂度是 $O(n^2)$。

目前排行榜：[第三](https://www.luogu.com.cn/record/79728398)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N=503;
ull n,m,q[N],X[N][N],Y[N][N];
int O(char x)
{
	if(x=='A')return 1;
	if(x=='C')return 2;
	if(x=='G')return 3;
	if(x=='T')return 4; 
}
bool C(int l,int r)
{
	unordered_set<ull> k;
    for(int i=1;i<=n;i++)
        k.insert(X[i][r]-X[i][l-1]*q[r-l+1]);
    for(int i=1;i<=n;i++)
        if(k.count(Y[i][r]-Y[i][l-1]*q[r-l+1]))return 1;
    return 0;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
    cin>>n>>m;q[0]=1;
    for(int i=1;i<N;i++)q[i]=q[i-1]*5;
    for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
		    char x;cin>>x;
			X[i][j]=X[i][j-1]*5+O(x);
		}
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
        	char x;cin>>x;
            Y[i][j]=Y[i][j-1]*5+O(x);
        }
    int s=1e9;
    for(int l=1,r=1;l<=m&&r<=m;l++)
    {
    	while(C(l,r)==1&&r<=m)r++;
    	s=min(s,r-l+1);
	}
	cout<<s<<endl;
    return 0;
}
```

---

## 作者：Boxxxxxx (赞：1)

[博客链接](https://blog.csdn.net/qq_43804974/article/details/110091863)

在这里，我们不二分，也不哈希，纯dp。~~但是复杂度真不行~~ 
可以知道，什么时候一个连续区间可以作为答案呢？前N个串称之为A集合，后N 个串称集合B。

假设这个连续区间是[L,R],长度是len，只有对于**任意一个**A中的串，在L位置与B中所有的串一一去比对，最长的相同的部分的的长度最多只能达到len - 1.

上面一段话是最重要也是我们dp的基础，为什么最长只能达到len - 1,如果最长相等部分达到len也就是[L,R]整个都一样，那么根据题意来说这是一个非法的连续区间，不能够作为答案。

设f[i][j][z] 代表A集合里面的i串与B集合里面的j串，在从z位置开始匹配，最长相同部分的串的长度。

显然 
第z位的字符相同 则f[i][j][z] = f[i][j][z + 1] + 1,

第z位的字符不相同 则f[i][j][z] = 0.

然后对于每一个z，求出每一个i的f[i][j][z]的最大值为maxlen，然后关于z向前的区间的答案长度就是maxlen + 1，注意判断前面所说的非法情况。

在配合上滚动数组减少空间，
这样我们就可以在O(N^2*M)下完成这题。不开O2最大的点是540ms，开了O2最大的点是100ms，

```cpp

int N, M,f[max_][max_];
char node[max_ << 1][max_];
il void ini() {
	N = read(); M = read();
	re int len,i, j,z,maxlen,ans = inf,Tm;
	for (i = 1; i <= (N << 1); i++) {
		scanf("%s", node[i] + 1);
	//	cin >> node[i] + 1;
	}
	for (len = 1, i = M; i >= 1; i--, len++) {
		Tm = 0;
		for (j = 1; j <= N; j++) {
			maxlen = 0;
			for (z = 1; z <= N; z++) {
				if (node[j][i] == node[N + z][i]) {
					f[j][z]++;
				}
				else {
					f[j][z] = 0;
				}
				maxlen = max(maxlen, f[j][z]);
			}
			Tm = max(Tm, maxlen);
		}
		if (Tm != len) {
			ans = min(ans, Tm + 1);
		}
	}
	write(ans);
//	cout << ans;
}
signed main() {
	ini();
	return 0;
}
```


---

## 作者：whc2020 (赞：1)

题意：

对于两组各n个的字符串，找到一个区间（lef，rig）使得区间长度最小，第一组字符串中此区间对应的子串与第二组中的不同。

思路：

二分枚举长度，再枚举区间的开头，再用map加以判断，整体时间复杂度O（n ^ 2 * logn ^ 2）。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

map < string , bool > Hash;

int n , m , ans;
bool flag;
string s[1005];//因为有两组字符串，所以数组多开一倍。 

bool check (int lef , int rig) {//判断区间（lef ， rig）是否符合条件。 
	Hash.clear ();
	int len = (rig - lef + 1);
	for (int i = 1 ; i <= n ; i++) {
		string temp = s[i].substr (lef , len);
		Hash[temp] = 1;
	}
	for (int i = n + 1 ; i <= 2 * n ; i++) {
		string temp = s[i].substr (lef , len);
		if (Hash[temp] == 1) {
			return 0;
		}
	}
	return 1;
}

int main () {
	ios::sync_with_stdio(false);//读入优化 
	cout.tie(NULL);
	cin >> n >> m;
	for (int i = 1 ; i <= 2 * n ; i++) {//[1 , n] 记录第一组数据，[n + 1 , 2 * n] 记录第二组数据。 
		cin >> s[i];
	}
	int lef = 1 , rig = m , len;
	while (lef <= rig) {//二分查找len 
		len = (lef + rig) >> 1;
		flag = 0;
		for (int front = 1 ; front + len - 1 <= m ; front++) {//枚举左端点 
			int last = front + len - 1;
			if (check (front , last) == 1) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			lef = len + 1;
		} else {
			ans = len;
			rig = len - 1;
		}
	}
	cout << ans;
	return 0;
}
```


---

## 作者：桑树下的邂逅 (赞：1)

首先这题可以枚举区间长度，然后枚举左端点，将前一半hash值放入map中，再算后一半的hash值，这样复杂度是n^3

显然若x满足条件，则x+1也满足条件，故可以二分区间长度

hash值可以用hash[r]-hash[l-1]*pow(prime,r-l+1)得到

```
#include<bits/stdc++.h>
using namespace std;
const int maxN=500+10,base=131,mod=1e9+7;
char s1[maxN][maxN],s2[maxN][maxN];
int n,m,h1[maxN][maxN],h2[maxN][maxN],mul[maxN];
map<int,bool>ma;
bool check(int len){
	bool out=false;
	for(int i=1;i+len-1<=m;i++){
		ma.clear();
		bool flag=true;
		for(int j=1;j<=n;j++) 
			ma[(h1[j][i+len-1]-1ll*h1[j][i-1]*mul[len]%mod+mod)%mod]=true;
		for(int j=1;j<=n;j++)
			if(ma.count((h2[j][i+len-1]-1ll*h2[j][i-1]*mul[len]%mod+mod)%mod)){
				flag=false;break;
			}
		if(flag){
			out=true;break;
		}
	}
	return out;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s1[i]+1);
	for(int i=1;i<=n;i++)scanf("%s",s2[i]+1);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		h1[i][j]=(1ll*h1[i][j-1]*base+s1[i][j])%mod;
		h2[i][j]=(1ll*h2[i][j-1]*base+s2[i][j])%mod;
	}
	mul[0]=1;for(int i=1;i<=m;i++) mul[i]=1ll*mul[i-1]*base%mod;
	check(1); 
	int l=1,r=m,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0; 
} 
```

---

## 作者：Azuree (赞：1)

[查看原题请戳这里](https://www.luogu.org/problem/P3667)

首先，这道题让求最大值最小，于是我们就很自然得想到了去二分这个最小值。

那么，怎么check呢？

我们发现，如果直接暴力去check，即二分区间长度+暴力枚举字符串+暴力枚举区间左端点+暴力对比，那么时间复杂度是$O(n^2m^2\log_2n)$的。（引人深思的复杂度……）

很显然，我们需要去优化这个时间复杂度。

首先，如果我们对要进行对比的区间进行哈希，然后用set进行判断，就可以将时间复杂度降低到$O(nm^2\log_2^2n)$。

这里提供两种用set去检验的思路：

1. 用一个set去记录好的基因有多少不同的哈希值$cnt1$，再用一个set去记录坏的基因有多少不同的哈希值$cnt2$，再用一个set去记录好的基因和坏的基因一共有多少不同的哈希值$cnt3$，如果$cnt3-cnt1=cnt2$，那么好的基因的哈希值和坏的基因的哈希值没有重复。
2. 用一个set去储存好的基因的哈希值，然后用set自带的find函数查询每一个坏的基因的哈希值是否在这个集合中出现过。

但是，即便如此，我们的时间复杂度依然无法通过这道题，主要原因是每次记录哈希值都占用了大量的时间。
$hash[i]-hash[j-1]\times pri^{i-j+1}(i>j)$快速求得$hash[i][j]$的值。

时间复杂度：$O(nm\log_2 n)$

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#define ll long long
#define INF 0x7fffffff
#define re register
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define qwq printf("qwq\n");
#define mod1 122420729
#define mod2 131937371

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

int n,m,l,r,mid,cnt1,cnt2,cnt3;

long long hfg[505][505],hfb[505][505],a[505],b[505],c[505];

char good[505][505],bad[505][505];

void Hash()
{
	memset(hfg,0,sizeof(hfg));
	memset(hfb,0,sizeof(hfb));
	for(register int i = 0; i < n; i++) hfg[i][0] = good[i][0];
	for(register int i = 0; i < n; i++) hfb[i][0] = bad[i][0];
	for(register int i = 0; i < n; i++)
		for(register int j = 1; j < m; j++)
			hfg[i][j] = hfg[i][j - 1] * 13331 + good[i][j];
	for(register int i = 0; i < n; i++)
		for(register int j = 1; j < m; j++)
			hfb[i][j] = hfb[i][j - 1] * 13331 + bad[i][j];
}

void get_Hash(int s,int l)
{
	if(s == 0)
	{
		for(int i = 0; i < n; i++) a[i] = hfg[i][l - 1];
		for(int i = 0; i < n; i++) b[i] = hfb[i][l - 1];
		return ;
	}
	for(int i = 0; i < n; i++) a[i] = hfg[i][s + l - 1] - hfg[i][s - 1] * c[l];
	for(int i = 0; i < n; i++) b[i] = hfb[i][s + l - 1] - hfb[i][s - 1] * c[l];
}

set<int> se1,se2,se3;

bool check(int l)
{
	for(register int i = 0; i + l - 1 < m; i++)
	{
		get_Hash(i,l);
		int flag = 1;
		se1.clear(); se2.clear(); se3.clear();
		for(register int j = 0; j < n; j++) se1.insert(a[j]),se3.insert(a[j]);
		cnt1 = se1.size();
		for(register int j = 0; j < n; j++) se2.insert(b[j]),se3.insert(b[j]);
		cnt2 = se2.size();
		if(se3.size() - cnt1 == cnt2) return true;
	}
	return false;
}

int main()
{
	n = read(); m = read();
	c[1] = 13331;
	for(int i = 2; i <= m; i++) c[i] = c[i - 1] * 13331; 
	for(register int i = 0; i < n; i++) cin >> good[i];
	for(register int i = 0; i < n; i++) cin >> bad[i];
	l = 1; r = m;
	Hash();
	while(l < r)
	{
		mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	
	get_Hash(1,4);
	printf("%d\n",r);
    return 0;
}

```

---

## 作者：henry_y (赞：1)

[$blog$](http://www.cnblogs.com/henry-1202)

我的做法是$O(nmlog^2n)$的。

先把字符串hash掉，然后这个判断可行一看就知道是可以二分的。那就二分一波答案。判断那里，考虑用set来维护相同hash值。

枚举长度为x（二分的值）的区间，然后将A串里面这个区间的hash值塞进set里面。对每个B串在set里面find一下这个字串有没有出现过即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define il inline
#define ull unsigned long long

namespace io {

#define in(a) a = read()
#define out(a) write(a)
#define outn(a) out(a), putchar('\n')

#define I_int ll
inline I_int read() {
    I_int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
char F[200];
inline void write(I_int x) {
    if (x == 0) return (void) (putchar('0'));
    I_int tmp = x > 0 ? x : -x;
    if (x < 0) putchar('-');
    int cnt = 0;
    while (tmp > 0) {
        F[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (cnt > 0) putchar(F[--cnt]);
}
#undef I_int

}
using namespace io;

using namespace std;

#define N 510
#define base 13131

int n = read(), m = read();
char s[N][N], t[N][N];
ull h1[N][N], h2[N][N], p[N];
set<ull>S;

ull get(ull *h, int l, int r) {
	return h[r] - h[l-1] * p[r-l+1];
}

bool check(int x) {
	bool ans = 0;
	for(int l = 1; l + x - 1 <= m; ++l) {
		int r = l + x - 1, flag = 0;
		S.clear();
		for(int i = 1; i <= n; ++i) {
			S.insert(get(h1[i], l, r));
		}
		for(int i = 1; i <= n; ++i) {
			if(S.find(get(h2[i], l, r)) != S.end()) {
				flag = 1;
				break;
			}
		}
		if(!flag) {
			ans = 1;
			break;
		}
	}
	return ans;
}

int main() { 
	for(int i = 1; i <= n; ++i) scanf("%s",s[i]+1);
	for(int i = 1; i <= n; ++i) scanf("%s",t[i]+1);
	p[0] = 1;
	for(int i = 1; i <= m; ++i) p[i] = p[i - 1] * base;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) h1[i][j] = h1[i][j-1]*base+(ull)s[i][j];
		for(int j = 1; j <= m; ++j) h2[i][j] = h2[i][j-1]*base+(ull)t[i][j]; 
	}
	int l = 1, r = m, ans = m;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	outn(ans);
	return 0;
}
```

---

## 作者：Porsche (赞：1)

## 想让大家注意一点，这道题打hash需要随机化，至于操作
```cpp
srand(time(NULL));
for(int i=1;i<=m;i++)
	flag[i]=rand();
```
### 我们来一个鲜明的对比：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[501];
unsigned long long ans=1<<30,l=1,r=1;
unsigned long long p[501][501],s[501][501],hashs[501],hashp[501],mod[501];
set<unsigned long long> t;
bool flag;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++)
			s[i][j]=ch[j]-'A'+1;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++)
			p[i][j]=ch[j]-'A'+1;
	}
	while(r<=m)
	{
		t.clear();
		if(flag)
		{
			ans=min(ans,r-l);
			flag=1;
			for(int i=1;i<=n;i++)
			{
				hashs[i]=(hashs[i]-13131*s[i][l]);
				t.insert(hashs[i]);
			}
			for(int i=1;i<=n;i++)
			{
				hashp[i]=(hashp[i]-13131*p[i][l]);
				if(t.count(hashp[i]))flag=0;
			}
			l++;
		}
		if(!flag)
		{
			flag=1;
			for(int i=1;i<=n;i++)
			{
				hashs[i]=(hashs[i]+13131*s[i][r]);
				t.insert(hashs[i]);
			}
			for(int i=1;i<=n;i++)
			{
				hashp[i]=(hashp[i]+13131*p[i][r]);
				if(t.count(hashp[i]))flag=0;
			}
			r++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
#### ↑不好意思，只有10分
然而：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[501];
unsigned long long ans=1<<30,l=1,r=1;
unsigned long long p[501][501],s[501][501],hashs[501],hashp[501],mod[501];
set<unsigned long long> t;
bool flag;
int main()
{
    srand(time(NULL));
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++)
            s[i][j]=ch[j]-'A'+1;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++)
            p[i][j]=ch[j]-'A'+1;
    }
    for(int i=1;i<=m;i++)
        mod[i]=rand();
    while(r<=m)
    {
        t.clear();
        if(flag)
        {
            ans=min(ans,r-l);
            flag=1;
            for(int i=1;i<=n;i++)
            {
                hashs[i]=(hashs[i]-mod[l]*s[i][l]);
                t.insert(hashs[i]);
            }
            for(int i=1;i<=n;i++)
            {
                hashp[i]=(hashp[i]-mod[l]*p[i][l]);
                if(t.count(hashp[i]))flag=0;
            }
            l++;
        }
        if(!flag)
        {
            flag=1;
            for(int i=1;i<=n;i++)
            {
                hashs[i]=(hashs[i]+mod[r]*s[i][r]);
                t.insert(hashs[i]);
            }
            for(int i=1;i<=n;i++)
            {
                hashp[i]=(hashp[i]+mod[r]*p[i][r]);
                if(t.count(hashp[i]))flag=0;
            }
            r++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
### 不好意思，满分
~~宝宝的内心：MMP出题人死出来吃屎~~

---

## 作者：FCJ666 (赞：0)

通过观察发现答案具有单调性,并且出现满足某一条件的最小值这样的字样,于是可以考虑用二分进行优化,即二分符合的答案,并对答案进行判断是否可行,于是求解问题转化为了判断可行性问题.

判断部分思路:

一:看到题目大概意思是要大数量的判断字符串是否相等,第一反应就是字符哈希(避免低效循环判断),如果字符哈希不明白可以参考楼下大佬题解.

二:在枚举起点的过程中,可以预先用一个桶来装所有斑点牛的哈希值,然后再对纯黑的牛进行扫描,若发现纯黑牛对应的哈希值被占了,即可认为有两子串是相等的,于是便可以直接退出循环并换至下一个起点.至于对桶的清空,因为对每一个起点的判断中总共需要占用桶个数最多不超过五百,用清空函数显然时间不划算,于是可以考虑用一个数组来装有哪些桶被占用了,退出循环后直接从数组里取数出来一个个将桶清空即可.这也就意味着不能用无符号长整型来省略取模过程(因为桶不能开那么大),但是时间上其实是要快的.

三:当找到一个起点符合"有斑点的牛这部分的子串,不能和无斑点的牛的这部分子串相同"要求时,即可退出函数,缩小区间答案,这可以算是一个小剪枝.

最后奉上代码(第一篇题解,不好的地方欢迎指出):
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,l=1,r,mid,memr[510],cnt=1;//memr数组为记录数组 
const int INI=9999991;//INI进制数 
char str1[1001][510];//装两种牛基因 
long long hash1[1001][510],p[510];//哈希和对应幂 
bool pd[INI+1000];//桶 
bool ck(int nn){
	for(int j=1;j<=M-nn+1;j++){//枚举起点，切记加上长度后不能超过M 
		bool bj=false;
		for(int i=1;i<=N;i++){
			pd[(((hash1[i][j+nn-1]-hash1[i][j-1]*p[nn])%INI)+INI)%INI]=true;//装桶 
			memr[cnt++]=(((hash1[i][j+nn-1]-hash1[i][j-1]*p[nn])%INI)+INI)%INI;//记录哪些桶被装了 
			//(注意某子串的哈希值有可能是负数，所以要加上INI再取模，不然会RE)
		}
		for(int i=N+1;i<=2*N;i++){//对纯黑牛判断 
			if(pd[(((hash1[i][j+nn-1]-hash1[i][j-1]*p[nn])%INI)+INI)%INI]){
				bj=true;
				break;
			}
		}
		if(!bj)return true;//小剪枝 
		for(int i=1;i<cnt;i++){//恢复桶和记录数组 
			pd[memr[i]]=false;
			memr[i]=0;
		}
		cnt=1;
	}
	return false;	
}
int main(){
	cin>>N>>M;
	p[0]=1;//切记切记，一个非零数的零次幂是1 
	for(int i=1;i<=M;i++)p[i]=(p[i-1]*131)%INI;//预处理幂次 
	for(int i=1;i<=2*N;i++)
		for(int j=1;j<=M;j++)cin>>str1[i][j];//读入基因 
	for(int i=1;i<=2*N;i++)
		for(int j=1;j<=M;j++)hash1[i][j]=(hash1[i][j-1]*131+(str1[i][j]-'A'+1))%INI;//哈希预处理 
	r=M;
	while(l<r){//二分 
		mid=(l+r)>>1;
		if(ck(mid))r=mid;
		else l=mid+1;
	} 
	printf("%d",l);//输出答案 
	return 0;
}
```


---

