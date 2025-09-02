# [ABC021D] 多重ループ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc021/tasks/abc021_d

新入社員の高橋君は、とある企業の新人プログラマーとして部署に配属されました。 高橋君が担当した初めての仕事は、以下の擬似コードで表されるプログラムを高速化するというものでした。

 ```

n←(標準入力)
ans←0
for i=1..n
  for j=i..n
    ans ← ans+1
ansの値を表示
```

高橋君にかかってしまえばこんな仕事はお茶の子さいさいです。 各 $ i $ に対する内側のループ回数を考えて総和の公式を用いれば $ ans=n+n-1+…+1=n(n+1)/2 $ となり、これを用いればすぐ答えが出せます。

劇的な高速化に成功した高橋君への部署からの期待は鰻登りです。そこで、上司は彼に更なる仕事を与えることにしました。

その仕事内容は、以下のような for ループのネストの深さが $ k $ の場合におけるプログラムの高速化です。

 ```

n←(標準入力)
k←(標準入力)
ans←0
for a_1=1..n
  for a_2=a_1..n
    for a_3=a_2..n
      …
      for a_k=a_{k-1}..n // a_0=1とする
        ans ← ans+1
ansの値を表示
```

さすがの高橋君もこれには少し悩みました。総和の公式が使えないからです。

いろいろ考えてみたところ、このプログラムの出力する答えは $ 1≦a_1≦a_2≦…≦a_k≦n $ であるような整数の組 $ (a_1,a_2,…,a_k) $ の個数に等しいということに気づきました。 しかし、彼はそのようなものの個数を数える方法を思いつきませんでした。

彼の同僚であるあなたは、彼の代わりにこの課題をこなすプログラムを作ってあげることにしました。 ただし、答えは非常に大きくなることがあるので、ans の代わりに ans を $ 1,000,000,007(=10^9+7) $ で割った余りを出力してください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1≦n≦1000 $ かつ $ 1≦k≦1000 $ であるようなデータセットに正解した場合は $ 99 $ 点が得られる。
- 上記のデータセットを含む全てのデータセットに正解した場合はさらに $ 1 $ 点が得られる。

## 样例 #1

### 输入

```
10
2```

### 输出

```
55```

## 样例 #2

### 输入

```
10
3```

### 输出

```
220```

## 样例 #3

### 输入

```
10
4```

### 输出

```
715```

## 样例 #4

### 输入

```
400
296```

### 输出

```
546898535```

## 样例 #5

### 输入

```
100000
100000```

### 输出

```
939733670```

# 题解

## 作者：Soohti (赞：4)

**前置知识：[快速幂](https://oi-wiki.org/math/quick-pow/)、[乘法逆元](https://oi-wiki.org/math/inverse/)**
---
首先看到样例 1：  

> 输入 #1		10 2  
> 输出 #1		55  

很显然这是等差数列 $a_n=n$ 的前 $10$ 项和。  

再看到样例 2：  

> 输入 #2		10 3  
> 输出 #2		220  

这是上述数列的**前 $n$ 项和 $S_n=\frac{n\times(n+1)}{2}$ 的前 $10$ 项和**。  

**题目所求即为这一数列这样迭代 $k$ 次后的结果。**  

所以我们有了一份 TLE 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,P=1e9+7;
int n,k,a[N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		a[i]=i;					//生成数列
	for(int i=2;i<=k;i++)		//迭代
		for(int j=1;j<=n;j++)
			a[j]=(a[j]+a[j-1])%P;
	cout<<a[n]<<endl;
	return 0;
}
```
再运用数列求和知识经过简单的数学变换即可求出迭代后的通项：$ans=\frac{\prod_{i=0}^{k-1}(n+i)}{k!}$。  

由于用到了除法取模，所以这里使用了快速幂求逆元。  

附 AC 代码：
```c
#include<stdio.h>
const int P=1e9+7;
int n,k,s,f;
int pom(int a,int b){
	int r=1;
	for(;b;b>>=1,a=1LL*a*a%P)
		if(b&1)r=1LL*r*a%P;
	return r;
}
int main(){
	scanf("%d%d",&n,&k);
	s=n;f=1;
	for(int i=2;i<=k;i++)
		s=1LL*s*(n+i-1)%P,
		f=1LL*f*i%P;
	printf("%d\n",1LL*s*pom(f,P-2)%P);
	return 0;
}
```


---

## 作者：查帅 (赞：4)

------------
乍眼一看，这似乎是道水题（~~虽然真的有点水~~）

------------

咳咳，按照正常的思路来讲
### 第一步显然是~~暴力~~ _**递推**_ ！！！
不难想到，用dp[i][j]表示有i层每层有j个的循环ans总值，则有


------------
## **dp[i][j] = dp[i-1][j]+dp[i][j-1] ;**

------------
而题目数据范围显然不支持n^2的空间复杂度，但由于这里只涉及i与i-1可以用
滚动数组优化空间，那么直接可以打完一个轻松的部分分（虽然remote judge非0即ac），代码如下

```cpp
#include<bits/stdc++.h>
using namespace std ;
template<typename T> void read(T &x){
	x = 0 ; int flag = 1 ;
	char c = getchar() ;
	while(!isdigit(c)){
		if(c=='-')
			flag = -1 ;
		c = getchar() ;
	}
	while(isdigit(c)){
		x = x * 10 + c - '0' ;
		c = getchar() ;
	}
	x = x * flag ;
}
const int maxn = 1e5+10 ;
int n,k ;
const int mod = 1e9+7 ;
int dp[2][maxn] ;
int main(){
	read(n) ; read(k) ;
	int p = 0 ;
	for(int i = 1 ; i <= n ; i++)
		dp[p][i] = i ;
	for(int q = 2 ; q <= k ; q++){
		p^=1 ;
		for(int i = 1 ; i <= n ; i++)
			dp[p][i] = (dp[p^1][i]+dp[p][i-1])%mod ;
	} 
	
	cout<<dp[p][n]<<endl ;
	return 0 ;
}

```
有了dp思路之后怎么推出这个公式呢？

------------

方案一：由于已知道递推式，我们可以嫖一眼题解然后用数学归纳法证明

------------

## 方案二：对于dp[k][n] = dp[k-1][n]+dp[k][n-1],将dp[k][n-1]继续用这个式子展开，可以得到

------------
## dp[k][n]=$\sum\limits_{i=1}^ndp[k-1][i]$，

------------
各位参加数竞的应该很熟悉一个式子


------------
 $$\boxed{\sum\limits_{i = 1}^{n} \dbinom{m}{m+i-1} = \dbinom{m+1}{m+n-1}}$$
 这应该是属于数学高考难度的组合证明题，所以这里我就不加以证明了。

------------
$\color{OrangeRed}\colorbox{White}{知道这个公式，相信各位都看出来了答案是啥子。直接就可以把组合 }$
$\color{OrangeRed}\colorbox{White}{数套上去了，用快速幂求一下逆元就结束了。但是，我们要有严谨的}$
$\color{OrangeRed}\colorbox{White}{钻研精神，不仅要知道答案是这个，还要知道为什么是这个}$


------------
## **下面转化一下思路**
对于这个数列$a_n$，不难发现它是非严格单调递增的，且$a_i\in[1,n]$。我们可以理解为，我要取k个数，使这k个数能构成一个从小到大的排列，这样的选法应是无序的。如果$a_n$是一个单调递增的数列，那么很显然，这样的取法就是

------------
$$\dbinom{k}{n}$$

------------
当$a_n$是一个非严格单调增，也就是多了$a_i$=$a_{i+1}$的情况，其实也很容易想。当第一个数确定后，后面k-1个数每个都会比单调增多一种相等的取法，不是因该多k-1个数吗？所以这个答案就是


------------
$$\dbinom{k}{n+k-1}$$
下面附上ac代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
template<typename T> void read(T &x){
	x = 0 ; int flag = 1 ;
	char c = getchar() ;
	while(!isdigit(c)){
		if(c=='-')
			flag = -1 ;
		c = getchar() ;
	}
	while(isdigit(c)){
		x = x * 10 + c - '0' ;
		c = getchar() ;
	}
	x = x * flag ;
}
const int maxn = 1e2 ;
long long ans1 = 1,ans2 = 1 ;
const long long mod = 1e9+7 ;
int n,k ;
inline long long po(long long base,long long power){
	long long result = 1;
    while (power > 0) {
        if (power & 1) 
            result = result * base % mod ;
        power >>= 1 ;
        base = (base * base) % mod;
    }
    return result;
}
int main(){
	read(n) ; read(k) ;
	for(register int i = 1 ; i <= k ; i++)
		ans1 = ans1*((long long)(n+i-1))%mod,ans2 = ans2*i%mod ;
	
	ans1 = ans1*po(ans2,mod-2)%mod ;
	printf("%lld\n",ans1) ;
	return 0 ;
}

```
蒟蒻较菜，可能分析会有一些瑕疵，望神犇理解体谅。

---

