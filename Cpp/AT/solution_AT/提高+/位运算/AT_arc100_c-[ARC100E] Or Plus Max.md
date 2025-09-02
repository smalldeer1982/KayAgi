# [ARC100E] Or Plus Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc100/tasks/arc100_c

長さ $ 2^N $ の整数列 $ A_0,\ A_1,\ ...,\ A_{2^N-1} $ があります。（添字が $ 0 $ から始まることに注意）

$ 1\ \leq\ K\ \leq\ 2^N-1 $ を満たすすべての整数 $ K $ について、次の問題を解いてください。

- $ i,j $ を整数とする。$ 0\ \leq\ i\ <\ j\ \leq\ 2^N-1 $, $ (i $ $ or $ $ j)\ \leq\ K $ のとき、$ A_i\ +\ A_j $ の最大値を求めよ。 ただしここで $ or $ はビットごとの論理和を表す。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

$ K=1 $ のとき、$ i,j $ としてあり得る組合せは $ (i,j)=(0,1) $ のみなので、答えは $ A_0+A_1=1+2=3 $ となります。 $ K=2 $ のとき、$ i,j $ としてあり得る組合せは $ (i,j)=(0,1),(0,2) $ です。 $ (i,j)=(0,2) $ のとき、$ A_i+A_j=1+3=4 $ となり、これが最大なので、答えは $ 4 $ です。 $ K=3 $ のとき、$ i,j $ としてあり得る組合せは $ (i,j)=(0,1),(0,2),(0,3),(1,2),(1,3),(2,3) $ です。 $ (i,j)=(1,2) $ のとき、$ A_i+A_j=2+3=5 $ となり、これが最大なので、答えは $ 5 $ です。

## 样例 #1

### 输入

```
2
1 2 3 1```

### 输出

```
3
4
5```

## 样例 #2

### 输入

```
3
10 71 84 33 6 47 23 25```

### 输出

```
81
94
155
155
155
155
155```

## 样例 #3

### 输入

```
4
75 26 45 72 81 47 97 97 2 2 25 82 84 17 56 32```

### 输出

```
101
120
147
156
156
178
194
194
194
194
194
194
194
194
194```

# 题解

## 作者：vectorwyx (赞：51)

[参考博客](https://www.cnblogs.com/heyuhhh/p/11585358.html)

考虑对每个 $k$ 分别进行计算。即令  $A_k=\max_{i|j=k,i\not=j}a_i+a_j$，则 $ans_k=\max_{i|j\le k,i\not=j}a_i+a_j=\max_{i=1}^{k}A_i$。

由于答案是对每种可能的 $a_i+a_j$ 取 max，因此不妨扩展一下 $A_i$ 的范围。把 $i,j,k$ 看做二进制数，我们说 $i\subseteq j$，当且仅当 $i$ 的每一位都小于等于 $j$。令 $A_k=\max_{i,j\subseteq k,i\not=j}a_i+a_j$，则 $ans_k$ 仍等于 $\max_{i=1}^{k}A_i$。

上述式子成立是由于或运算的性质。或运算是不减的，并且 $i,j\subseteq k$ 是 $i|j=k$ 的必要条件、$i|j\le k$ 的充分条件。这使得所有满足 $i,j\subseteq k,i\not=j$ 的 $(i,j)$ 组成的集合保留了原来那些满足 $i|j=k,i\not=j$ 的 $(i,j)$ 的集合，又没有把 $i|j>k$ 的 $(i,j)$ 放进来，因此答案的正确性不变。

现在我们需要求对于每个 $k$ 求 $\max_{i,j\subseteq k,i\not=j}a_i+a_j$，这是**类子集和问题**，得借助**高维前缀和**完成。

## 高维前缀和
一维前缀和不用多说，二维前缀和一般是用容斥来做。但容斥的复杂度为 $O(2^nV)$，其中 $n$ 为维数，$V$ 为点数。随着维度的增加复杂度将变得无法接受。其实我们可以以维为单位，逐维拓展，复杂度就会降至 $O(nV)$。具体思路可以参考如下代码：

求二维前缀和：
```
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        a[i][j] += a[i - 1][j];
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        a[i][j] += a[i][j - 1];
```
求三维前缀和：
```cpp
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        for(int k = 1; k <= n; k++) 
            a[i][j][k] += a[i - 1][j][k];
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        for(int k = 1; k <= n; k++)
            a[i][j][k] += a[i][j - 1][k];
for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        for(int k = 1; k <= n; k++)
            a[i][j][k] += a[i][j][k - 1];
```
手模一下就非常清晰明了了，更高维度的以此类推。

回到本题上来，$A_k=\max_{i,j\subseteq k,i\not=j}a_i+a_j$ 实际上就是求高维前缀最大值和次大值，特殊之处在于它的对象是一个边长为 $2$ 的 $n$ 维超立方体，点数为 $2^n$，总时间复杂度为 $O(n2^n)$。

代码如下（码字不易，还望给个赞QAQ）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=19,inf=1e9;
int n,m;
struct Node{
	int m1,m2;
	Node operator+(const Node &x){
		Node y;
		if(m1>x.m1){
			y.m1=m1;
			y.m2=max(m2,x.m1);
		}else{
			y.m1=x.m1;
			y.m2=max(m1,x.m2);
		}return y;
	}
}a[1<<N];

int main(){
	cin>>n;m=1<<n;
	fo(i,0,m-1) a[i].m1=read(),a[i].m2=-inf;
	fo(i,0,n-1)
		fo(j,0,m-1) if((j>>i)&1) a[j]=a[j]+a[j^(1<<i)];
	//cout<<a[0].m1+a[0].m2<<endl;
	int ans=0;
	fo(j,1,m-1){
		big(ans,a[j].m1+a[j].m2);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：犇犇犇犇 (赞：17)

[题目链接](https://www.luogu.com.cn/problem/AT4168)

~~萌新初学高维前缀和，来写篇题解~~  

观察题目，我们需要满足的条件有两个，找出最大的$a_i+a_j$并且$ i|j \leq k$

我们可以转化一下题目，满足$ i|j \leq k$ 可以认为是在 $i|j$在等于1-k时的最大值，所以我们只要求出对于所有的k，满足$i|j=k$时的解，询问的时候取max就行了。

我们发现这时候问题就转化成了$i|j⊂k$ 变成了一个子集问题，即对于所有k，求出它所有子集的最大值和第二大值。

这里显然枚举所有子集会超时，所以我们需要高维前缀和。  
我们拿一个结构体绑一下每个k的最大值和次大值，初始时最大值为当前值，次大值为 0 或 -inf , 然后做高维前缀和，只不过这里前缀和保存的不是前缀和，而是所有前缀的最大值。  

代码：

```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0' || c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
struct number
{
	int f,s;
}a[1<<MAXN]; //f表示最大值,s为次大值
int n;
int main()
{
	n=read();
	for(int i=0;i<1<<n;i++)
	{	
		int x;
		x=read();
		a[i].f=x; 
	}
	for(int j=0;j<n;j++)
		for(int i=0;i<1<<n;i++)
			if(i>>j & 1) //高维前缀和
			{
				int x=i^(1<<j); //上一层的状态
				number ans;
				ans.f=max(a[i].f,a[x].f); //f为两个状态最大值
				if(a[i].f>a[x].f) 
					ans.s=max(a[i].s,a[x].f); //选择了i的最大值时,仍可以选择x的最大值作为当前答案的第二大
				else
					ans.s=max(a[i].f,a[x].s);
				a[i]=ans;
			}
	int ans=0;
	for(int i=1;i<1<<n;i++)
	{
		ans=max(ans,a[i].f+a[i].s);  //对于所有k，取之前状态的最大值
		cout<<ans<<endl;
	}
	cout<<endl;
	return 0;
}
```




---

## 作者：XL4453 (赞：7)

### 前置知识：高维前缀和

~~（我觉得看到紫题敢点进来的肯定会普通前缀和~~

对于一类求子集和问题，即形如 $\sum_{A\subseteqq B}V_A$ 的问题。

首先想到可以对于每一个集合 $B$ 枚举其子集，若集合中一共有 $k$ 个元素，则一共有 $2^k$ 个集合，对于每一个集合，又需要 $2^k$ 次运算来枚举其子集，时间复杂度为 $O(4^k)$，当 $k=13$ 时就已经逼近时间上限了，难以接受。

考虑对其使用前缀和优化，这里先引入另一种前缀和求法（非容斥原理求法）：

对于一个二维前缀和，可以考虑先把他的第一维用一维前缀和的方式求出，然后对其第二维再求一次前缀和，这样就可以得到整个的前缀和了，代码实现如下：

```cpp
for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
f[i][j]+=f[i][j-1];//第一次 

for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
f[i][j]+=f[i-1][j];//第二次
```
类似的,有三维前缀和的非容斥求法：

```cpp
for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
for(int k=1;k<=l;k++)
f[i][j][k]+=f[i][j][k-1];//第一次 

for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
for(int k=1;k<=l;k++)
f[i][j][k]+=f[i][j-1][k];//第二次 

for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
for(int k=1;k<=l;k++)
f[i][j][k]+=f[i-1][j][k];//第三次 
```
这样就可以很轻松地推出更高维的前缀和求法了。

回到原问题，发现这不就是一个每一维的边界都是 $2$ 的高维前缀和吗？

立刻有：

```cpp
for(int i=0;i<n;i++)
for(int j=0;j<(1<<n);j++)
if((1<<i)&j)f[j]+=f[j-(1<<i)];
//写成f[j]+=f[j^(1<<i)]显然也是可以的 
```
其中 $f_i$ 的初值即为集合价值 $V$。

分析一下时间复杂度，是 $O(k\times2^k)$ 的，在数组空间逼近极限的 $k=20$ 时时间复杂度也比时间上限小了一个数量级，还是很优秀的（相对上面那个）。

------------
### 题目分析：

对于这道题，可以把它先转换为求 $i|j\subseteqq K$ 的问题，然后再把每一个小于 $K$ 的集合里取一个最大值即可。

然后就记录下每一个集合中最大值和次大值，每当两个子集合并时，优先比较要合并的两个的最大值，如果原来的更大就只需要将另一个的最大值和这一个次大值比较就行了，否则在这一个最大值和另一个的次大值里选一个给这一个的次大值。

~~虽然思路一样，但或许这已经不能叫高维前缀和了。~~

------------
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1<<19;
pair <int,int> f[MAXN];
int n,x,maxn,ans;
int main(){
	scanf("%d",&n);
	for(int i=0;i<(1<<n);i++){
		scanf("%d",&x);
		f[i].first=x;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<(1<<n);j++){
			if((1<<i)&j){
				int m1=f[j].first,m2=f[j].second;
				int m3=f[j^(1<<i)].first,m4=f[j^(1<<i)].second;
				if(m3>m1)m2=max(m1,m4),m1=m3;
				else m2=max(m2,m3);
				f[j].first=m1;
				f[j].second=m2;
			}
		}
	}
	for(int i=1;i<(1<<n);i++){
		ans=max(ans,f[i].first+f[i].second);
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：无钩七不改名 (赞：5)

可以将题目转化为求每个 $1 \leq K \leq 2^n-1$，找出最大的 $a_i+a_j$（$i$ $or$ $j = K$，$0 \leq i < j < 2^n$）。然后对于每个 $1 \leq K \leq 2^n-1$，答案为 $1$~$K$ 中最大的答案。

具体的，我们可以开两个数组 $b1$ 和 $b2$，分别记录能被选取的次大值和最大值的位置。为什么是位置呢，因为要防止重复选取。

然后从小到大枚举每个 $1 \leq K \leq 2^n-1$，对于每个 $1\le j \le n$（$i$ $and$ $2^{j-1}\gt 0$），更新 $b1_k$ 和 $b2_k$ 就好了。从小到大枚举可以保证覆盖到所有可能的取值。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[270000];
int b1[270000],b2[270000];//262144

int main(){
	scanf("%d",&n);
	int m=1<<n;
	for(int i(0);i<m;i++){
		scanf("%d",a+i);
		b2[i]=i;
	}
	for(int i(1);i<m;i++)
		for(int j(0);j<n;j++)
			if(i&(1<<j)){
				int x=i-(1<<j);
				if(a[b2[x]]>a[b1[i]]&&b2[x]!=b2[i])b1[i]=b2[x];
				if(a[b1[i]]>a[b2[i]])swap(b1[i],b2[i]);
				if(a[b1[x]]>a[b1[i]]&&b1[x]!=b2[i])b1[i]=max(b1[i-(1<<j)],b1[i]);
			}
	int ans=a[b1[1]]+a[b2[1]];
	for(int i(1);i<m;i++){
		//cout<<b1[i]<<" "<<b2[i]<<" ";
		ans=max(ans,a[b1[i]]+a[b2[i]]);
		printf("%d\n",ans);
	}
	return 0;
} 
```


---

## 作者：皎月半洒花 (赞：5)

发现似乎是在做一个FMT状物，但是直接转移最大值需要 $k ^2$ 甚至更高的代价，不能直接转移。

考虑对于每个集合 $s$ 记一下这个集合中的最最大数和次大数，不难发现这样转移是方便的。复杂度 $2^kk$ 。

```cpp
ll ans ;
int m, n ;
pint f[N] ;
ll base[N] ;
 
bool comp(int x, int y){
    return base[x] > base[y] ;
}
int main(){
    cin >> m ; n = (1 << m) - 1 ;
    for (int i = 0 ; i <= n ; ++ i){
        cin >> base[i] ;
        f[i] = make_pair(i, n + 1) ;
    }
    base[n + 1] = -1 ;
    for (int i = 0 ; i <= n ; ++ i)
        for (int j = 0 ; j < m ; ++ j)
            if (!((1 << j) & i)){
                int k = (1 << j) | i ;
                int t[4] = {fr(i), sc(i), fr(k), sc(k)} ;
                sort(t, t + 4, comp) ; unique(t, t + 4) ;
                f[k] = make_pair(t[0], t[1]) ;
            }
    for (int i = 1 ; i <= n ; ++ i){
        ans = max(ans, base[fr(i)] + base[sc(i)]) ;
        cout << ans << endl ;
    }
}
```

---

## 作者：灵华 (赞：3)

### 思路：

~~怎么题解里面都是 FMT 啊。~~
~~这题不是一看就是或卷积嘛？~~

直接用 FWTor 卷：

把前缀和，转变为前缀最大值，次大值，这个可以同时维护。

然后直接跑就行了。思路大体应该和 FMT 差不多，但是常数比 FMT 小，跑的要快一点。

时间复杂度：$O(2^nn)$。

### Code：
```cpp
#include <iostream>
using namespace std ;

typedef pair < int , int > PII ;
int n , ans ;
PII f[(1<<19)+5] ;

PII Max ( PII u , PII v ) {
	if ( u .first > v .first )
		return { u .first , max ( u .second , v .first ) } ;
	return { v .first , max ( u .first , v .second ) } ;
}

int main ( ) {
	cin >> n ;
	for ( int i = 0 ; i < ( 1 << n ) ; ++ i )
		cin >> f [ i ] .first , f [ i ] .second = 0 ;
	
	for ( int i = 1 ; i < ( 1 << n ) ; i <<= 1 )
		for ( int j = 0 ; j < ( 1 << n ) ; j += i << 1 )
			for ( int k = 0 ; k < i ; ++ k )
				f [ i + j + k ] = Max ( f [ i + j + k ] , f [ j + k ] ) ;
	
	ans = f [ 0 ] .first + f [ 0 ] .second ;
	for ( int i = 1 ; i < ( 1 << n ) ; ++ i ) {
		ans = max ( ans , f [ i ] .first + f [ i ] .second ) ;
		cout << ans << "\n" ;
	}
	return 0 ;
}
```

---

## 作者：Z1qqurat (赞：2)

CSP-S 2023 我紧紧地抱住了零酱，遂更新。

SOSDP 部分的参考资料：<https://www.cnblogs.com/Troverld/p/14601821.html>。在此基础上做了一些补充和自己的理解。

我们可以把它当作一个 SOSDP（高位前缀和）的模板题，所以先讲讲 SOSDP 这玩意儿。实际上是 ZROI 场上大眼瞪出 T2 大概是什么子集状物，当时感觉是啥 SOSDP，然后我不会这个算法（看出解法不会算法次数 ++，目前已达 $4$ 次）。

唔姆，首先考虑这样一个通式问题：给出一个全集 $U$，对于每个子集 $S \subseteq U$，已知一个 $f(S)$ 的值。现在设 $g(S) = \sum\limits_{T \subseteq S} f(T)$，对于每个 $S \subseteq U$，求 $g(S)$。$n \le 22$。

首先你可以简单枚举子集做到 $O(3 ^ n)$，这是怎么做呢？这相当于先在外层暴力枚举 $U$ 的子集 $S$，再对每个 $S$ 枚举其子集 $T$：

```cpp
for (int S = 0; S <= U; ++S) {
    for (int T = S; T; T = (T - 1) & S) {
        g[S] += f[T];
    }
}
```

这个求 $T$ 的原理就是每次找到与当前 $T$ 最近的，小于 $T$ 的子集，利用 $T \le S$ 的性质。复杂度是 $tim = \sum\limits_{0 \le k \le n} \binom{n}{k} 2 ^ k$，根据二项式定理，$(a + b) ^ n = \sum\limits_{0 \le k \le n} a ^ {n - k} b ^ k$，所以 $tim = (2 + 1) ^ n = 3 ^ n$，也就是 $O(3 ^ n)$。枚举子集的技巧还是很有用的说。

能不能更优啊喂？我们考虑对 $n = 2$ 暴力列出 $f, g$ 的式子。设 $U = \{x_1, x_2\}$，

$$
g(\varnothing) = f(\varnothing)\\
g(\{x_1\}) = f(\varnothing) + f(\{x_1\})\\
g(\{x_2\}) = f(\varnothing) + f(\{x_2\})\\
g(\{x_1, x_2\}) = f(\varnothing) + f(\{x_2\}) + f(\{x_1\}) + f(\{x_1, x_2\})
$$

你会发现 $g(\{x_1, x_2\}) = f(\{x_1, x_2\}) + g(\{x_1\}) + g(\{x_2\}) - g(\varnothing)$。

这很容斥，写成 $n$ 不定的一般形式就是，

$$
g(S) = f(S) + \sum\limits_{T \subset S} (-1) ^ {|S| - |T| + 1}g(T)
$$

所以我们可以这样做，也是枚举子集的形式，还是 $O(3 ^ n)$。

但是通过这个转化，我们将 $g(S)$ 转化为了一种容斥的形式，看到这个转移形式我们不仅想到一些东西：前缀和。

多维前缀和可以用容斥求，也可以将维度从后往前拆开一次叠加贡献。如果我们将 $g(S)$ 的转移看作一种 $n$ 维前缀和，那我们为什么不适着用拆维的思路来求一下 $g(S)$？这样的话，复杂度会是 $O(n 2^n)$ 的。模板写法：

```cpp
for (int i = 0; i < n; ++i) {
    for (int S = 1; S <= U; ++S) {
        if(S & (1 << i)) f[S] <- f[S ^ (1 << i)]
    }
}
```

这玩意儿的正确性可以参考 <https://www.luogu.com.cn/blog/zac2010/gao-wei-qian-zhui-he>，写的很细致，清晰易懂。

于是我们就将子集问题转化为高维前缀和问题，最后用前缀和的另一种更为简便快捷的计算方式解决了这个子集问题。可以说是一种很神奇的转化了。

那我们来看这个题。考虑对于 $S \subseteq U$，求出 $i | j \subseteq S,\max(a_i + a_j)$，其实就相当于求 $i \subseteq S, a_i$ 最大值和次大值。这玩意儿直接高位前缀和一下，设 $f(S)$ 为对于 $S, i \subseteq S$ 中最大和次大的 $a_i$ 之和。那么 $ans(S) = \max\limits_{T \le S} f(T)$，相当于一个前缀 $\max$，直接 for 循环做就可以了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pair<int, int>
#define mr make_pair
#define fi first
#define se second
using namespace std;
const int N = 18;
int n, U;
pii f[1 << N];

void upd(pii &x, int y) {
    if(y > x.fi) x.se = x.fi, x.fi = y;
    else x.se = max(x.sem y);
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n; U = (1 << n) - 1;
    for (int i = 0; i <= U; ++i) cin >> f[i].fi;
    for (int i = 0; i < n; ++i) {
        for (int S = 1; S <= U; ++S) {
            if(S & (1 << i)) upd(f[S], f[S ^ (1 << i)].fi), upd(f[S], f[S ^ (1 << i)].se);
        }
    }
    int ans = f[0].fi + f[0].se;
    for (int i = 1; i <= U; ++i) {
        ans = max(ans, f[i].fi + f[i].se); cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：zac2010 (赞：2)

不难发现我们可以处理出每个下标状态的所有子集中 $a_i$ 的最大值和次大值，用一个 `pair<int,int>` 维护，跑一遍 $\text{SOSDP}$，这时每个状态的权值就是最大值加次大值，最终输出的每一个答案都是一个前缀最大值。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = a; i <= b; i++)
#define FR(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
int n, U, ans;
pair<int, int> f[1 << 18];
void upd(pair<int, int> &a, int x){
    if(x > a.first) a.second = a.first, a.first = x;
    else if(x > a.second) a.second = x;
}
int main(){
    scanf("%d", &n), U = (1 << n) - 1;
    FL(s, 0, U) scanf("%d", &f[s].first);
    FL(i, 1, n) FR(s, U, 1) if(s & (1 << i - 1))
        upd(f[s], f[s ^ (1 << i - 1)].first), upd(f[s], f[s ^ (1 << i - 1)].second);
    FL(s, 1, U) ans = max(ans, f[s].first + f[s].second), printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Chocola4ever (赞：2)

考虑对于每个 $k$ ，都存在一个最大的 $a_i+a_j \ (i \ | \ j=k)$ 。

但发现还是不好求。

于是我们可以将问题进一步转化为求 $a_i+a_j \ (i \ | \ j \sub k)$ 。

然后在输出的时候将当前位的答案与上一位的答案取 $\max$ 即可。

那么就变成了一个**类**子集求和问题(SOS-DP)

只要求出**对于每个 $k$ 的子集的最大值和次大值**即可。

那么就可以用~~高维前缀和~~ **高维前缀最大/次大值**求解

#### Code

```cpp
/*
	Author: Chocola4ever
	Date: 2021-03-31 10:05:44
	LastEditTime: 2021-04-23 10:41:29
	FilePath: \Programs\test.cpp
	Description: RP++
*/
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=1e6+5;
struct Chocola{
	int mx1,mx2;
}dp[N];
int n,m,a[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=0;i<1<<n;++i)
		cin>>a[i],dp[i].mx1=a[i],dp[i].mx2=0;
	for(int i=0;i<n;++i)
		for(int j=0;j<1<<n;++j)
			if(j&(1<<i)){
				int lst=j^(1<<i);
				Chocola temp;
				if (dp[j].mx1>dp[lst].mx1){
					temp.mx1=dp[j].mx1;
					temp.mx2=max(dp[j].mx2,dp[lst].mx1);
				}else{
					temp.mx1=dp[lst].mx1;
					temp.mx2=max(dp[j].mx1,dp[lst].mx2);
				}
				dp[j]=temp;
			}
	int mx=0;
	for (int i=1;i<1<<n;++i){
		mx=max(mx,dp[i].mx1+dp[i].mx2);
		cout<<mx<<endl;
	}
	return 0;
}
```

---

## 作者：dbxxx (赞：1)

[ARC100E Or Plus Max](https://www.luogu.com.cn/problem/AT_arc100_c)

位运算上的比大小问题通常都很难处理，因此一般都是先把这种条件转化。

考虑下面三个集合：

- $A_K = \{(i, j) \mathop | i \operatorname{or} j \le K \land i \ne j\}$。
- $B_K = \{(i, j) \mathop | i, j \subseteq K\land i \ne j\}$。
    - 这里 $i \subseteq K$ 的意思，可以用以下四种等价角度理解：
    - $i \operatorname{bitand} K = i$。$\operatorname{bitand}$ 是按位与的意思。
    - 同一个二进制位上，$i$ 的这一位小于等于 $K$ 的这一位。
    - 同一个二进制位上，$K$ 这一位为 $1$，则 $i$ 这一位可以为 $1$ 或 $0$；$K$ 这一位为 $0$，则 $i$ 这一位只能为 $0$。
    - $i$ 的所有为 $1$ 的二进制位数集，是 $K$ 的所有为 $1$ 的二进制位数集的子集。
- $C_K = \{(i, j)\mathop | i \operatorname{or} j = K\land i \ne j\}$。

不难发现 $C_K \subseteq B_K \subseteq A_K$，以及 $A_K = \bigcup\limits_{i=1}^K C_i$。

不难发现 $\bigcup\limits_{i=1}^K C_i \subseteq \bigcup\limits_{i=1}^K B_i$，而 $\bigcup\limits_{i=1}^K B_i \subseteq A_K$。所以，$A_K = \bigcup \limits_{i = 1}^KB_i$。唯一不同点在于，原先 $C_i$ 之间互不相交，而 $B_i$ 有交。

用语言说明这个转化的正确性：$B_i$ 包含满足 $i \operatorname{or} j = K$ 的全部 $(i, j)$，也不把 $i \operatorname{or} j >K$ 的 $(i, j)$ 给放进来，所以正确。

为什么要这么转化？两个原因。

【原因一】

原先 $i \operatorname{or} j \le K$ 或 $i \operatorname{or} j = K$ 都是一条二元制约关系。

而 $i, j \subseteq K$ 可以理解为 $i \subseteq K \land j \subseteq K$，即两条一元制约关系，会更好处理。

当然一直还有一个二元制约关系是 $i \ne j$，不过这个通常也不难处理。

【原因二】

$i \subseteq K$ 是一个套路性的 sosdp 形式。

不难发现 $\max$ 是可重复贡献的（即 $\max(x, x) = x$），所以上面的并集运算可以直接转 $\max$。

假设数对 $(i, j)$ 的权值是 $a_i + a_j$，那么要求的答案可以看做 $\max(A_K) = \max_{i = 1}^K \max(B_i)$

因此考虑求 $\max(B_k) =\max \{a_i + a_j \mathop | i, j \subseteq k\}$。

不难发现，我们只需要维护满足 $i \subseteq k$ 的 $a_i$ 的最大值和次大值分别作为 $a_i$ 和 $a_j$，就能让和取到最大值。

而最大值和次大值与和一样，可以方便地合并。这题做完了。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-04-17 10:20:23 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-04-17 11:06:28
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool f = true;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = false;
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    return f ? x : (~(x - 1));
}
inline bool gmx(int &a, int b) {
    return b > a ? a = b, true : false;
}

const int maxn = 19;
std :: vector <int> f[1 << maxn];

int main() {
    int n = read();
    for (int i = 0; i < (1 << n); ++i)
        f[i].push_back(read());
    
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < (1 << n); ++i) {
            if (i & (1 << j)) {
                int lst = i ^ (1 << j);
                for (int x : f[lst])
                    f[i].push_back(x);
                std :: sort(f[i].begin(), f[i].end(), std :: greater <int> ());
                while (f[i].size() > 2)
                    f[i].pop_back();
            }
        }
    }

    int ans = 0;
    for (int K = 1; K < (1 << n); ++K) {
        gmx(ans, f[K][0] + f[K][1]);
        printf("%d\n", ans);
    }
    return 0;
}
```



---

## 作者：XiangyuHu (赞：1)

### 题意解释

给定 $2^n$ 个数 $a_0,a_1,\cdots,a_{2^n-1}$，对每一个 $0\le k<2^n$，求 $(a_i+a_j)_\mathrm{max}$，其中 $i\mid j\le k$。

### 题解

我们记 $x\in y$ 表示 $x\And y=y$，于是有了一种非常自然的思路：对每个 $x$ 求 $f_{x,0}$ 与 $f_{x,1}$ 表示找到 $i\in x,j\in x$ 使得 $a_i+a_j$ 最大时的 $i$ 和 $j$。最后求和前缀最大值即可。

那么就考虑来求 $f$。考虑高维前缀和，每次去掉一个 $1$ 转移过来即可。

细节方面，$f$ 开成 `pair`，注意像刚刚说的那样存序号（避免重复），还有下标不要变成 $-1$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int n, a[1001000];
pii f[1001000];
int ans[1001000];
void add(int pos, int x) {                // 将 x 作为新值添加到 f[pos]
    if (a[x] > a[f[pos].first]) {         // 注意存下标
        f[pos].second = f[pos].first;
        f[pos].first = x;
    } else if (a[x] > a[f[pos].second] && x != f[pos].first) {
        f[pos].second = x;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); i++) {
        scanf("%d", a + i);
        f[i].second = 1000099;            // 这个值永远都是 0，一定会被更新大
        add(i, i);
    }
    for (int i = 1; i < (1 << n); i++) {  // 高维前缀和
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {           // 枚举从哪里转移
                add(i, f[i ^ (1 << j)].first);
                add(i, f[i ^ (1 << j)].second);
            }
        }
    }
    for (int i = 1; i < (1 << n); i++) {  // 统计答案
        ans[i] = a[f[i].first] + a[f[i].second];
        ans[i] = max(ans[i], ans[i - 1]); // 前缀最小值
        printf("%d\n", ans[i]); 
    }
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

### 高维前缀和

另一种前缀和求法（非容斥原理求法）：

二维前缀和：

```
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        a[i][j]+=a[i-1][j];
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        a[i][j]+=a[i][j-1];
```

三维前缀和：

```
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		for(int k=1;k<=l;k++)
			f[i][j][k]+=f[i][j][k-1];

for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		for(int k=1;k<=l;k++)
			f[i][j][k]+=f[i][j-1][k]; 

for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		for(int k=1;k<=l;k++)
			f[i][j][k]+=f[i-1][j][k];
```


更高维度的以此类推。

我们可以将问题转化为求 $a_i+a_j(i|j\subset k)$，再在每个比 $k$ 小的集合中取最大答案即可。那么只要求出每个 $k$ 的子集的最大值和次大值即可。可以用类似高维前缀和的思路求解。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=5e6;
struct Node{
	int mxa,mxb;
}a[N];
int n,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=0;i<(1<<n);i++)a[i].mxa=read();
	for(int i=0;i<n;i++){
		for(int j=0;j<(1<<n);j++){
			if((1<<i)&j){
				int x=j^(1<<i);
				Node ans;
				ans.mxa=max(a[x].mxa,a[j].mxa);
				if(a[j].mxa>a[x].mxa)ans.mxb=max(a[x].mxa,a[j].mxb);
				else ans.mxb=max(a[x].mxb,a[j].mxa);
				a[j]=ans;
			}
		}
	}
	for(int i=1;i<(1<<n);i++){
		ans=max(ans,a[i].mxa+a[i].mxb);
		printf("%d\n",ans);
	}
	return 0;
}


```


---

## 作者：chenxia25 (赞：1)

考虑对于每个 $K$ 求出下标为 $K$ 子集的最大 $a_i+a_j$。那么显然一个是最大值，一个是次大值，这个是高维前缀和（前缀最值、次值）可以轻松计算的。

但这样子是假的，因为 $\leq K$ 不等于是 $K$ 的子集。但很显然是 $\leq K$ 的所有数的子集的并。于是按原先算法算出来答案后取个前缀 $\max$ 即可。

---

