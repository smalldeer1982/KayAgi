# [USACO18DEC] Cowpatibility G

## 题目背景

2025/4/9 加入两组 hack 数据（@Starrykiller）。

## 题目描述

研究证明，有一个因素在两头奶牛能否作为朋友和谐共处这方面比其他任何因素都来得重要——她们是不是喜欢同一种口味的冰激凌！

Farmer John 的 $N$ 头奶牛（$2\le N\le 5\times 10^4$）各自列举了她们最喜欢的五种冰激凌口味的清单。为使这个清单更加精炼，每种可能的口味用一个不超过 $10^6$ 的正整数 $\texttt{ID}$ 表示。如果两头奶牛的清单上有至少一种共同的冰激凌口味，那么她们可以和谐共处。

请求出不能和谐共处的奶牛的对数。

## 说明/提示

在这里，奶牛 $4$ 不能和奶牛 $1$、$2$、$3$ 中的任一头和谐共处，奶牛 $1$ 和奶牛 $3$ 也不能和谐共处。

## 样例 #1

### 输入

```
4
1 2 3 4 5
1 2 3 10 8
10 9 8 7 6
50 60 70 80 90```

### 输出

```
4```

# 题解

## 作者：simonG (赞：20)

### 前言
题意：求两两集合间没有交集的对数。  
一看涉及集合计数，考虑容斥原理。  
### 详解
先把答案赋值为 $n(n-1)$，即总共的对数。  
枚举 $S_i$ ，答案减去与 $S_j(j<i)$ 有交集的对数。  
对于集合 $S_i=\{a,b,c\}$ ，（此处把 $m$ 设为3）  
设 $cnt_i$ 数组为含有$i$元素的集合个数。
那么与$S_i$有交集的集合个数为（容斥原理）：  
$cnt_{a}+cnt_{b}+cnt_{c}-cnt_{a,b}-cnt_{b,c}-cnt_{a,c}+cnt_{a,b,c}$ 。  
用总答案减去上式即可。  
$m=5$ 也同理：我们发现上面的 $cnt$ 中的下标对应的是每个元素的出现与不出现。  
这样就可以使用二进制枚举的方法。  
用二进制中的第 $i$ 位表示第 $i$ 个数的出现与否。  
当出现了奇数个元素时，对贡献为正；否则为负。  
但是如何存储 $cnt$ 数组呢？用哈希表或 STL ```map``` 即可。  
这里使用字符串存储。  
### 代码
```cpp
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<map>
using namespace std;
long long n,ans;
string a[7];
map<string,long long> f;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=5; j++) cin>>a[j];
		sort(a+1,a+6);
		for(int j=1; j<32; j++) {//利用二进制枚举哪些数被选
			int cnt=0;
			string s="";
			for(int k=1;k<=5;k++)
				if(j&(1<<(k-1))) {
					cnt++;
					s+=a[k]+" ";
				} //用字符串存储方案 
			if(cnt&1) ans+=f[s];
			else ans-=f[s];
			f[s]++; 
		}
	}
	printf("%lld\n",n*(n-1)/2-ans);
	return 0;
}
```
应该是较短的代码。

---

## 作者：用户已注销 (赞：8)

本题首发题解，求过~

建议标签：**容斥原理**

考虑暴力，枚举两个奶牛，将名单逐一对比，时间复杂度$O(N^2)$，再乘一个对比的常数，妥妥的超时。

先考虑如何转化问题，显然统计完全不同的清单不是那么容易，我们可以考虑统计**存在部分相同**的清单（也就是不合法答案，可以和谐相处的奶牛），然后用总答案（$N\times N-N$）减去统计到的不合法答案。

接着考虑如何优化这个暴力，如果可以用一个桶，使得对比不需要逐一对比，只需要枚举每个元素，先统计桶内已有的相同元素个数，再加入桶中。这样只有后面的元素会统计到前面的，可以保证每对关系只被记录一次。

现在问题在于，本题不要求两个奶牛的清单完全相同，只需要有相同的元素即可。所以我们考虑如何转化为可以用桶计数的模型（完全相等），这显然是一个经典的容斥原理的模型。

具体实现的时候，先枚举每个清单，然后枚举这个清单的每一个非空子集，在桶中查询并加入桶中。至于容斥，如果选出的元素个数是奇数，贡献为负，否则贡献为正。

实现代码：其中位运算有些恶心人，请耐心理解~

本代码常数较大，不开$O2$单个测试点最慢$2300ms$

```
#include <bits/stdc++.h>
using namespace std ;
inline long long Readin() {
	long long K = 0 , F = 1 ; char C = ' ' ;
	while( C < '0' or C > '9' ) F = C == '-' ? -1 : 1 , C = getchar() ;
	while( C <= '9' and C >= '0' ) K = ( K << 1 ) + ( K << 3 ) + C - '0' , C = getchar() ;
	return F * K ;
}
inline long long Min( long long A , long long B ) { return A < B ? A : B ; }
inline long long Max( long long A , long long B ) { return A > B ? A : B ; }
inline long long Abs( long long A ) { return A < 0 ? -A : A ; }

const int MaxN = 50000 + 5 ;
long long N , Ans ; 
struct Ice {
	int A[7] ;
	Ice() { /* 构造函数，也就是自动初始化（缺点是常数大）*/ 
		A[1] = A[2] = A[3] = A[4] = A[5] = -1 ;	
	}
} C[MaxN] ;
inline bool operator < ( Ice A , Ice B ) { /* Map需要用到的比较函数，如果两个元素关系不唯一将会出错 */ 
	for(register int i = 0 ; ++i <= 5 ; )
		if( A.A[i] ^ B.A[i] ) return A.A[i] < B.A[i] ;
	return false ; /* 不能是true */
}
map<Ice,long long> Map ; /* 桶 */ 
int main() {
	N = Readin() ;
	Ans = N * N - N >> 1 ;
	for(register int i = 0 ; ++i <= N ; sort( C[i].A + 1 , C[i].A + 6 ) )
		for(register int j = 0 ; ++j <= 5 ; )
			C[i].A[j] = Readin() ;
	for(register int i = 0 , I , j , k , D , Top ; ++i < 32 ; )
		for( j = 0 ; ++j <= N ; ) {
			register Ice Reg ;
			/* 重点解释接下来这一步：D是记录子集元素个数的变量，I是状压以后选出的状态 */
			for( I = i , Top = k = D = 0 ; ++k <= 5 ; ( D ^= I & 1 ) , I >>= 1 )
				if( I & 1 ) Reg.A[++Top] = C[j].A[k] ; /* 注意必须用一个Top使所有元素前置，方便比较函数进行比较 */
			Ans -= ( D ? 1 : -1 ) * Map[Reg] ; /* 计算贡献 */
			++Map[Reg] ; /* 新的元素入桶 */
		}
	return not printf( "%lld\n" , Ans ) ; /* 这里好像流行写一句拜拜程序？ */
}
```

---

## 作者：vegetable_king (赞：6)

在[博客](https://yjh965.github.io/post/cowpatibility-g-ti-jie/)食用更佳。

提供一个正确的 `bitset` 做法。

首先可以将冰激凌的数字离散化。

然后发现直接求不能和谐共处的方案数不好求，我们考虑反过来求能和谐相处的个数。

设能与第 $i$ 头奶牛和谐相处的奶牛的个数为 $cnt_i$（包括自己），那要求的答案即为 $\dfrac{n(n - 1) - \sum_{i = 1}^n cnt_i - 1}2$。

我们可以想到对于每种冰激凌开一个大小为 $n$ 的 `bitset`，记录有哪些奶牛喜欢这种冰激凌，那么 $cnt_i$ 就等于这头奶牛喜欢的五种冰激凌所代表的 `bitset` 或起来的 $1$ 位数。

然后这样求时间复杂度为 $O(\frac{n^2}w)$，空间复杂度为 $O(\frac{n^2}w)$，无法通过。

我们发现其中有很多的 `bitset` 都没有存什么东西，浪费了很多空间，所以我们考虑根号分治。

具体来讲，如果一个冰激淋的出现次数 $> \sqrt n$，那么对于这种冰激凌开一个 `bitset`；否则，代替 `bitset`，对于这种冰激凌开一个 `vector`。（也是记录有哪些奶牛喜欢这种冰激凌）

查询时，将对应的 `bitset` 或起来，再把对应的 `vector` 里面的奶牛暴力加进去。

单次查询时，处理 `bitset` 时间复杂度为 $O(\frac nw)$，因为我们限制开了 `vector` 的冰激凌出现次数 $\le \sqrt n$，`vector` 暴力添加时间复杂度为 $O(\sqrt n)$，总共为 $O(\frac{n^2}w + n \sqrt n)$。

因为我们限制开了 `bitset` 的冰激凌至少出现 $\sqrt n$ 次，所以至多会开 $\sqrt n$ 个 `bitset`，且 `vector` 最多总共占用 $O(n)$ 的空间，空间复杂度为 $O(n \sqrt n)$。

如果实现优秀甚至可以吊打一大堆大常数 $1 \log$……

代码主体部分：

```cpp
// 懒惰的作者并没有离散化
// lim 为 sqrt(n)
int n, m, cnt, a[50001][6], t[1000001], id[1000001];
vector<int> v[1000001];
bitset<50001> b[lim + 1], c;
ll ans;
int main(){
	read(n);
	for (int i = 1;i <= n;i ++){
		for (int j = 1;j <= 5;j ++) read(a[i][j]), m = max(m, a[i][j]), t[a[i][j]] ++;
	}
	for (int i = 1;i <= m;i ++){
		if (t[i] > lim) id[i] = ++ cnt;
	}
	for (int i = 1;i <= n;i ++){
		for (int j = 1;j <= 5;j ++){
			if (t[a[i][j]] > lim) b[id[a[i][j]]][i] = 1;
			else v[a[i][j]].push_back(i);
		}
	}
	for (int i = 1;i <= n;i ++){
		c.reset();
		for (int j = 1;j <= 5;j ++){
			if (t[a[i][j]] > lim) c |= b[id[a[i][j]]];
			else {
				for (int x : v[a[i][j]]) c[x] = 1;
			}
		}
		ans += c.count() - 1;
	}
	write(n * (n - 1ll) / 2 - ans / 2);
}
```

---

## 作者：摸鱼酱 (赞：4)

大致题意：有 $n$ 个大小为 $m$ 的集合，求有多少对集合交集大小为 $0$。

$m=5$，$1\leq n\leq 5\times 10^4$，集合内元素在 $[1,10^6]$ 内。

发现 5e4 好像挺能暴力的，于是我们考虑容斥。

先试着枚举集合元素来容斥，即枚举所有可能的大小为 $1$ 到 $m$ 的集合作为共有元素来容斥，记 $f_i$ 为所有大小为 $i$ 的共有元素集合对应的集合有多少对，那么答案为 $\frac{n(n-1)}{2}+\sum_{i=1}^m (-1)^if_i$，即再枚举集合大小完成容斥。

虽然这样在复杂度上不太可行，但把问题转化为了求 $f_i$。不难发现我们枚举的集合不需要是所有可能的大小不超过 $5$ 的集合，而只需要是某个集合的子集即可。

于是把集合元素排序一下，枚举每个给定集合的子集，问题就转化为了插入一个长度不超过 $m$ 的串以及查询一个长度不超过 $m$ 的串的出现次数，选择自己喜欢的方式维护就好了。

为了实现效率，我使用了 [Trie + 哈希表](https://www.luogu.com.cn/paste/xy77vfv8) 来维护这个过程，但没有注意常数，所以效率并没有特别优秀。

时间复杂度 $\mathcal O(nm2^m)$ 或 $\mathcal O(nm2^m\log n)$，视实现方式而定。

---

## 作者：LiveZoom (赞：4)

## P5123 [USACO18DEC]Cowpatibility G

这题正着直接做显然不行，所以要反着容斥做。

记录 $f_i$ 表示从第 $1\sim i-1$ 头奶牛中可以和第 $i$ 头奶牛和谐共处的头数。

$f_i=\text{有1个数与 i 中的匹配的个数}-\text{有2个数与 i 中的匹配的个数}+\text{有3个数与 i 中的匹配的个数}-\text{有4个数与 i 中的匹配的个数}+\text{有5个数与 i 中的匹配的个数}$ 。

这个匹配的个数显然可以用 $5$ 个 $\text{map+tuple}$ 记，每次算完 $f_i$ 就将 $i$ 这头牛的信息加入 $\text{map}$ 即可。

时间复杂度：$O(64\cdot n\log n)$，不开 $O2$ 过不了。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int kMaxN = 5e4 + 5;

map <tuple <int>, int> mp1;
map <tuple <int, int>, int> mp2;
map <tuple <int, int, int>, int> mp3;
map <tuple <int, int, int, int>, int> mp4;
map <tuple <int, int, int, int, int>, int> mp5;
int n;
int s[6], a, b, c, d, e;
ll ans;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d%d", &s[1], &s[2], &s[3], &s[4], &s[5]);
    sort(s + 1, s + 6);
    a = s[1], b = s[2], c = s[3], d = s[4], e = s[5];
    ans += i - 1;
    ans -= mp1[make_tuple(a)] + mp1[make_tuple(b)] + mp1[make_tuple(c)] + mp1[make_tuple(d)]
         + mp1[make_tuple(e)];
    ans += mp2[make_tuple(a, b)] + mp2[make_tuple(a, c)] + mp2[make_tuple(a, d)] + mp2[make_tuple(a, e)]
         + mp2[make_tuple(b, c)] + mp2[make_tuple(b, d)] + mp2[make_tuple(b, e)] + mp2[make_tuple(c, d)]
         + mp2[make_tuple(c, e)] + mp2[make_tuple(d, e)];
    ans -= mp3[make_tuple(a, b, c)] + mp3[make_tuple(a, b, d)] + mp3[make_tuple(a, b, e)]
         + mp3[make_tuple(a, c, d)] + mp3[make_tuple(a, c, e)] + mp3[make_tuple(a, d, e)]
         + mp3[make_tuple(b, c, d)] + mp3[make_tuple(b, c, e)] + mp3[make_tuple(b, d, e)]
         + mp3[make_tuple(c, d, e)];
    ans += mp4[make_tuple(a, b, c, d)] + mp4[make_tuple(a, b, c, e)] + mp4[make_tuple(a, b, d, e)]
         + mp4[make_tuple(a, c, d, e)] + mp4[make_tuple(b, c, d, e)];
    ans -= mp5[make_tuple(a, b, c, d, e)];
    ++mp1[make_tuple(a)], ++mp1[make_tuple(b)], ++mp1[make_tuple(c)], ++mp1[make_tuple(d)], 
    ++mp1[make_tuple(e)];
    ++mp2[make_tuple(a, b)], ++mp2[make_tuple(a, c)], ++mp2[make_tuple(a, d)], ++mp2[make_tuple(a, e)], 
    ++mp2[make_tuple(b, c)], ++mp2[make_tuple(b, d)], ++mp2[make_tuple(b, e)], ++mp2[make_tuple(c, d)], 
    ++mp2[make_tuple(c, e)], ++mp2[make_tuple(d, e)];
    ++mp3[make_tuple(a, b, c)], ++mp3[make_tuple(a, b, d)], ++mp3[make_tuple(a, b, e)], 
    ++mp3[make_tuple(a, c, d)], ++mp3[make_tuple(a, c, e)], ++mp3[make_tuple(a, d, e)], 
    ++mp3[make_tuple(b, c, d)], ++mp3[make_tuple(b, c, e)], ++mp3[make_tuple(b, d, e)], 
    ++mp3[make_tuple(c, d, e)];
    ++mp4[make_tuple(a, b, c, d)], ++mp4[make_tuple(a, b, c, e)], ++mp4[make_tuple(a, b, d, e)], 
    ++mp4[make_tuple(a, c, d, e)], ++mp4[make_tuple(b, c, d, e)];
    ++mp5[make_tuple(a, b, c, d, e)];
  }
  printf("%lld\n", ans);
  cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's' << endl;
  return 0;
}
```

---

## 作者：zhmshitiancai (赞：2)

[门](https://www.luogu.org/problem/P5123)

题意:每个奶牛有5个口味值，若两个奶牛有一个口味值相同，则它们能和谐共处。求不能和谐共处的奶牛的对数。$n \leq 5\times10^4$


解：用总对数去掉能和谐共处的对数。

能和谐共处的对数=有$1$个口味值相同的对数-有$2$个口味值相同的对数······

就是个容斥。

用$map$ 维护一下就行。细节见代码。

复杂度很鬼，$O(n\times32\times log(32n))=1.2\times10^8$

不过时间开了3s

**Code**
``` cpp

//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX=5e5+5;
int n;
struct node {
	int si;
	int kw[5];
}a[MAX];
map<node,int> ma;
bool operator < (const node &x,const node &y)
{
	for(int i=0;i<5;i++)
	{
		if(x.kw[i]<y.kw[i]) return true;
		if(x.kw[i]>y.kw[i]) return false;
	}
	return false;
}
int main()
{
	cin>>n;
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		a[i].si=0;
		for(j=0;j<5;j++){
			scanf("%d",&a[i].kw[j]);
		}
		sort(a[i].kw,a[i].kw+5);
		for(k=0;k<32;k++)
		{
			node temp;temp.si=0;
			for(j=0;j<5;j++)
				temp.kw[j]=0;
			for(j=0;j<5;j++)
			{
				if(k&(1<<j)){
					temp.kw[temp.si++]=a[i].kw[j];
				}
			}
			sort(temp.kw,temp.kw+temp.si);
			ma[temp]++;
		}
	}
	map<node,int>::iterator it;
	ll ans=0;
	for(it=ma.begin();it!=ma.end();++it)
	{
		pair<node,int> temp=*it;
		
		if(temp.first.si==0) continue;

		if(temp.first.si%2==1)
		{
			ans+=(ll)temp.second*(ll)(temp.second-1)/2;
		}
		else
		{
			ans-=(ll)temp.second*(ll)(temp.second-1)/2;
		}
/*		cout<<temp.first.si<<endl;
		for(j=0;j<5;j++)
			cout<<temp.first.kw[j]<<" ";
		cout<<endl;*/
	}
//	cout<<ans<<endl;
	cout<<(ll)n*(ll)(n-1)/2-ans<<endl;
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：2)

没想到 $map$ 和容斥，直接 $bitset$ 好了

发现没有 $map$ 的 $bitset$ 空间开不下，我们用 $[Ynoi2016]$ 跳进兔子洞的思想，将 $bitset$ 就开 $10000$ 左右，然后每次暴力扫一遍，或以下就可以了。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=50000+10;
const int maxm=250000+10;
int n,a[maxn][5],vis[maxn],mp[maxm],tot;ll ans;
bitset<maxn+10> s[10010],t[10010]; 

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

void solve(int l,int r,int x,int y){
	for(int i=x;i<=y;i++) t[i-x].reset();
	for(int i=l;i<=n;i++)
		for(int j=0;j<5;j++)
			if(x<=a[i][j]&&a[i][j]<=y) t[a[i][j]-x][i]=1;
	for(int i=l;i<=r;i++){
		for(int j=0;j<5;j++)
			if(x<=a[i][j]&&a[i][j]<=y) t[a[i][j]-x][i]=0;
		for(int j=0;j<5;j++)
			if(x<=a[i][j]&&a[i][j]<=y){
				if(!vis[i]) s[i-l]=t[a[i][j]-x],vis[i]=1;
				else s[i-l]|=t[a[i][j]-x];
			}
	}
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=0;j<5;j++) a[i][j]=mp[++tot]=read();
	sort(mp+1,mp+tot+1);
	tot=unique(mp+1,mp+tot+1)-mp-1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<5;j++) a[i][j]=lower_bound(mp+1,mp+tot+1,a[i][j])-mp;
	for(int l=1,r;l<=n;l+=10000){
		r=min(l+9999,n);
		for(int x=1,y;x<=tot;x+=10000){
			y=min(x+9999,tot);
			solve(l,r,x,y);
		}
		for(int i=l;i<=r;i++) ans+=s[i-l].count();
	}
	ans=1ll*n*(n-1)/2-ans;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Violet___Evergarden (赞：1)

**前排提醒：** 我的做法并不是正解，只有开 O2 的情况下才能过，正解应为哈希，但思路是一样的。

每一组奶牛要么能和谐共处要么不能，于是设有 $n$ 头牛，有 $m$ 组奶牛能和谐共处，那么不能和谐共处的数量就是 $\frac{n\times(n-1)}{2}-m$。

 $m$ 又可以通过容斥原理来求，设 $ num_i$ 为有 $i$ 种喜欢的口味相同的数量那么可得：
 
 $$m=num_1-num_2+num_3-num_4+num_5$$
 
 于是不能和谐共处的数量 $ans$ 就能这样求了：
 $$ans\gets \frac{n\times(n-1)}{2}-num_1+num_2-num_3+num_4-num_5$$

对于 $num_i$ 可以用一个 ```map``` 记录共同喜欢的口味为 $k_1,k_2 \cdots$ 的奶牛组数。

于是代码写得极丑。

```cpp
#include <iostream>
#include <algorithm>
#include <map>
#define int long long
#define mt make_tuple
using namespace std;
const int kMaxN=5e4+1;
int n;
int k[6],ans;
map<tuple<int>,int>mp1;
map<tuple<int,int>,int>mp2;
map<tuple<int,int,int>,int>mp3;
map<tuple<int,int,int,int>,int>mp4;
map<tuple<int,int,int,int,int>,int>mp5;
signed main()
{
cin>>n;
ans=n*(n-1)/2;
for(int i(1);i<=n;++i)
{
  for(int j(1);j<=5;++j)
  {
    scanf("%lld",&k[j]);
  }
  sort(k+1,k+6);
  int a=k[1],b=k[2],c=k[3],d=k[4],e=k[5];//手动枚举口味的可能性
  ans-=(mp1[mt(a)]+mp1[mt(b)]+mp1[mt(c)]+mp1[mt(d)]+mp1[mt(e)]);
  ans+=(mp2[mt(a,b)]+mp2[mt(a,c)]+mp2[mt(a,d)]+mp2[mt(a,e)]+mp2[mt(b,c)]+mp2[mt(b,d)]+mp2[mt(b,e)]+mp2[mt(c,d)]+mp2[mt(c,e)]+mp2[mt(d,e)]);
  ans-=(mp3[mt(a,b,c)]+mp3[mt(a,b,d)]+mp3[mt(a,b,e)]+mp3[mt(a,c,d)]+mp3[mt(a,c,e)]+mp3[mt(a,d,e)]+mp3[mt(b,c,d)]+mp3[mt(b,c,e)]+mp3[mt(b,d,e)]+mp3[mt(c,d,e)]);
  ans+=(mp4[mt(a,b,c,d)]+mp4[mt(a,b,c,e)]+mp4[mt(a,b,d,e)]+mp4[mt(a,c,d,e)]+mp4[mt(b,c,d,e)]);
  ans-=(mp5[mt(a,b,c,d,e)]);
  ++mp1[mt(a)],++mp1[mt(b)],++mp1[mt(c)],++mp1[mt(d)],++mp1[mt(e)];//更新信息
  ++mp2[mt(a,b)],++mp2[mt(a,c)],++mp2[mt(a,d)],++mp2[mt(a,e)],++mp2[mt(b,c)],++mp2[mt(b,d)],++mp2[mt(b,e)],++mp2[mt(c,d)],++mp2[mt(c,e)],++mp2[mt(d,e)];
  ++mp3[mt(a,b,c)],++mp3[mt(a,b,d)],++mp3[mt(a,b,e)],++mp3[mt(a,c,d)],++mp3[mt(a,c,e)],++mp3[mt(a,d,e)],++mp3[mt(b,c,d)],++mp3[mt(b,c,e)],++mp3[mt(b,d,e)],++mp3[mt(c,d,e)];
  ++mp4[mt(a,b,c,d)],++mp4[mt(a,b,c,e)],++mp4[mt(a,b,d,e)],++mp4[mt(a,c,d,e)],++mp4[mt(b,c,d,e)];
  ++mp5[mt(a,b,c,d,e)];
}
cout<<ans;
return 0;
}
```
因为 STL 很慢（但是在 O2 的情况下快倒飞起），所以可以通过哈希表优化一下，代码懒得写了。

---

