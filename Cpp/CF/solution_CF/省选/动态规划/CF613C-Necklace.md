# Necklace

## 题目描述

Ivan wants to make a necklace as a present to his beloved girl. A necklace is a cyclic sequence of beads of different colors. Ivan says that necklace is beautiful relative to the cut point between two adjacent beads, if the chain of beads remaining after this cut is a palindrome (reads the same forward and backward).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613C/f0403ee8a9ea8e51a7dc66253e50c2d1edfa6bff.png)Ivan has beads of $ n $ colors. He wants to make a necklace, such that it's beautiful relative to as many cuts as possible. He certainly wants to use all the beads. Help him to make the most beautiful necklace.

## 说明/提示

In the first sample a necklace can have at most one beautiful cut. The example of such a necklace is shown on the picture.

In the second sample there is only one way to compose a necklace.

## 样例 #1

### 输入

```
3
4 2 1
```

### 输出

```
1
abacaba```

## 样例 #2

### 输入

```
1
4
```

### 输出

```
4
aaaa
```

## 样例 #3

### 输入

```
2
1 1
```

### 输出

```
0
ab
```

# 题解

## 作者：_fairytale_ (赞：2)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/280999/cf613c-necklace-ti-xie)
# 题意简述
给出 $n$ 个字母及它们的数量，要求把它们排成一圈，使得排列后能被切割的位置最多。

如果把这个排列从一个位置切割后能形成回文串，那么这个位置就是能被切割的。

------------

# Solution

考虑分情况讨论。

### Case 1：有两个以上的字母的数量为奇数

显然，此时无法构造出任何一种合法的方案。

直接输出 $0$，随便输出一种方案即可。

### Case 2：有一个的字母的数量为奇数

对于这种情况，我们发现，可以通过构造回文循环节的形式使答案最大。

例如：
```plain
input:
2
3 6
output:
3
babbabbab
```

我们通过构造 $\verb!bab!$ 这一循环节，使得每个循环节之间都存在合法切割的位置。

进而，我们不难发现，循环节的个数为每个字母出现次数的 $\gcd$，并且也是这种情况的答案。

### Case 3：所有字母的数量都是偶数

这种情况的思路和上一种差不多，我们也可以通过构造回文循环节的方式来实现。

一组例子：
```plain
input:
2
4 4
output:
abbaabba
```

显然，此时合法切割的位置不仅存在于循环节之间，也存在于循环节内部，即 $\verb!abba!$ 的 $\verb!bb!$ 之间。

我们通过观察发现，尽管此时的 $\gcd$ 为 $4$，但是每个循环节内部必须有偶数个字母，以保证循环节内部存在合法切割的位置。因此，此时循环节的个数为 $ \dfrac{\gcd}{2}$。

每个循环节对答案的贡献为 $2$，所以答案依然为 $2 \times \dfrac{\gcd}{2} = \gcd$。

### Code：
理解了上述内容后，代码就很好写啦~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
int gcd(int x,int y) {
	return y==0?x:gcd(y,x%y);
}
int n;
int a[30];
int g;//数组中所有数的最大公约数 
int cnt;//奇数个数
int flag;//奇数在数组中的下标
int main() {
	cin>>n;
	for(re int i=1; i<=n; ++i) {
		cin>>a[i];
		g=gcd(g,a[i]);//求最大公约数 
		if(a[i]%2)cnt++,flag=i;//记录奇数个数及下标
	}
	if(cnt>=2) {//两个以上的奇数
		puts("0");
		for(re int i=1; i<=n; ++i) {
			for(re int j=1; j<=a[i]; ++j) {
				putchar('a'+i-1);//随便输出一种就行
			}
		}
		return 0;
	}
	cout<<g<<'\n';
	if(flag) {//一个奇数
		for(re int k=1; k<=g; ++k) {//共有gcd个循环节
			//输出偶数的前一半
			for(re int i=1; i<=n; ++i)
				if(i!=flag)
					for(re int j=1; j<=a[i]/g/2; ++j)
						putchar('a'+i-1);
			//输出奇数
			for(re int i=1; i<=a[flag]/g; ++i)putchar('a'+flag-1);
			//输出偶数的后一半，注意此时要倒着输出，构造回文
			for(re int i=n; i>=1; --i)
				if(i!=flag)
					for(re int j=1; j<=a[i]/g/2; ++j)
						putchar('a'+i-1);
		}
	} else { //全是偶数
		for(re int k=1; k<=g/2; ++k) {//对于偶数，有gcd/2个循环节
		
			for(re int i=1; i<=n; ++i)//前半段
				for(re int j=1; j<=a[i]/g; ++j)
					putchar('a'+i-1);
					
			for(re int i=n; i>=1; --i)//后半段
				for(re int j=1; j<=a[i]/g; ++j)
					putchar('a'+i-1);
		}
	}
	return 0;//完结撒花
}
```
如果有疑惑或者错误，欢迎大家在评论区指出！

---

## 作者：elbissoPtImaerD (赞：0)

# 题意简述

有 $n$ 个数，每个数出现了 $a_i$ 次，将 $\sum\limits a_i$ 个数重排在一个环上。

定义切割：从某相邻两个数中间将环割成一条链，将这相邻两数连接的边叫切割边。

称一条切割边漂亮当且仅当其满足切割后的链是回文串。

对于每一个排列，它的权值为不同漂亮切割边的个数。

求最大权值以及构造。

$1 \le n\le 26$，$2 \le \sum\limits a_i \le 10^5$。

# 解题报告

记 $m=\sum\limits a_i$，$ans$ 为漂亮切割边数。

由于回文串的对称性，我们发现：对于每一个排列，$ans$ 要么是 $0$，要么是 $1$，要么是 $m$ 的因子。  
因为当切割边数 $\ge 2$ 时我们可以将一条切割边关于另外一条切割边对称，得到一条新的切割边。

进一步地，我们发现，这样割出的每一部分都是相同的或者仅是 reverse 了一下，所以 $ans$ 一定不超过 $k=\gcd\limits_{i=1}^n\{a_i\}$。  
尝试构造 $ans=k$。

察觉：当没有奇数的时候很好构造，只需要输出 $\frac k2$ 个相同的部分，每个部分里有 $\frac{a_i}k$ 个  $i$，相邻两部分 reverse 一下。

那考虑有奇数时怎么做：先考虑一个奇数。  
同样的，分成 $k$ 组完全相同的，那每一组中间放奇数就好了。

大于一个奇数显然做不了。

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/109868452)

细节看代码。

```cpp
// Wonder what you're doing for the rest of your life.
#include<cstdio>
#include<algorithm>
#define re register
#define il inline
#define ast(yx,wt) (yx)||(exit(wt),7)
#define rd(yx) scanf("%d",&yx)
#define prt(w,t) printf("%d%c",w,t)
#define pc(js) (putchar('a'+(js)-1))
int n,a[29],x,y,ans;
il int gcd(re int x,re int y)
{
	if(y) for(;(x%=y)&&(y%=x););
	return x+y;
}
#define Auto(r,x) for(re int k=1;k<=(r)/ans;++k) pc(x);
void Solve()
{
	rd(n);
	for(re int i=1;i<=n;++i) rd(a[i]),a[i]&1&&(++x,y=i);
	ans=a[1];
	for(re int i=2;i<=n;++i) ans=gcd(ans,a[i]);
	x>1&&(ans=0),prt(ans,'\n');
	if(!ans)
	{
		ans=1;
		for(re int i=1;i<=n;++i) Auto(a[i],i);
		return;
	}
	if(x)
	{
		for(re int i=1;i<=ans;++i)
		{
			for(re int j=1;j<=n;++j)
				if(j^y) Auto(a[j]/2,j);
			Auto(a[y],y);
			for(re int j=n;j;--j)
				if(j^y) Auto(a[j]/2,j);
		}
	}
	else
	{
		for(re int i=1;i<=ans/2;++i)
		{
			for(re int j=1;j<=n;++j) Auto(a[j],j);
			for(re int j=n;j;--j) Auto(a[j],j);
		}
	}
	return;
}
main()
{
//	freopen("1.in","r",stdin);
	return Solve(),0;
}
```

---

## 作者：localhost (赞：0)

1. 如果个数中没有奇数，那么答案就是所有数字的$gcd$，然后构造答案就是输出$\frac {gcd}2$个回文串

2. 如果个数中只有一个奇数，那么答案也是所有数字的$gcd$，然后构造答案就是输出$gcd$个回文串，个数为奇数的颜色放在回文串的中间

3. 如果个数中有两个或以上的奇数，那么答案就是$0$，因为两个奇数就已经构造不出有优美$cut$的环来了

```cpp
#include<bits/stdc++.h>
namespace ZDY{
	#define ll long long
	#define MB template <class T>il
	#define Fur(i,x,y) for(int i=x;i<=y;i++)
	#define Fdr(i,x,y) for(int i=x;i>=y;i--)
	#define fcin ios::sync_with_stdio(false)
	MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
}using namespace ZDY;using namespace std;
#define N 10011
int n,a[27];
int main(){
	fcin;
	cin>>n;
	int f=0,x;
	Fur(i,1,n){cin>>a[i];if(a[i]&1)x=i,f++;}
	int ans=a[1];
	Fur(i,2,n)ans=GCD(ans,a[i]);
	if(f>1)ans=0;
	cout<<ans<<endl;
	if(f>1){
		Fur(i,1,n)while(a[i]--)cout<<char('a'-1+i);
	}
    else
	if(f){
		Fur(i,1,ans)
			Fur(j,1,n)
			if(j!=x)
				Fur(k,1,a[j]/ans/2)cout<<char('a'-1+j);
		Fur(j,1,a[x]/ans)cout<<char('a'-1+x);
		Fdr(j,n,1)
		if(j!=x)
			Fur(k,1,a[j]/ans/2)cout<<char('a'-1+j);
	}
	else{
		Fur(i,1,ans/2){
			Fur(j,1,n)
				Fur(k,1,a[j]/ans)cout<<char('a'-1+j);
			Fdr(j,n,1)
				Fur(k,1,a[j]/ans)cout<<char('a'-1+j);
		}
	}
    cout<<endl;
}
```

---

