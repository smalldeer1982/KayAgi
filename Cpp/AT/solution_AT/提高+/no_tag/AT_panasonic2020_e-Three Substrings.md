# Three Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e

すぬけ君は、文字列 $ s $ を持っています。 あぬけ君、ぶぬけ君、くぬけ君は次のような方法でそれぞれ文字列 $ a,\ b,\ c $ を得ました。

- $ s $ の空でない ($ s $ 全体であってもよい) 連続な部分文字列を一つ選ぶ。その部分文字列のうちいくつかの文字 ($ 0 $ 個や全部であってもよい) を `?` で置き換える。

たとえば、$ s $ が `mississippi` であるとき、部分文字列として `ssissip` を選び、その $ 1,\ 3 $ 文字目を `?` で置き換えることで `?s?ssip` を得ることができます。

文字列 $ a,\ b,\ c $ が与えられます。 $ s $ の長さとして考えられる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |a|,\ |b|,\ |c|\ \leq\ 2000 $
- $ a,\ b,\ c $ は英小文字と `?` からなる。

### Sample Explanation 1

たとえば、$ s $ が `atcoder` のとき条件を満たします。

### Sample Explanation 2

$ a,\ b,\ c $ は相異なるとは限りません。

## 样例 #1

### 输入

```
a?c
der
cod```

### 输出

```
7```

## 样例 #2

### 输入

```
atcoder
atcoder
???????```

### 输出

```
7```

# 题解

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT5808) & [AtCoder题目页面传送门](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e)

>给定$3$个字符串$a,b,c,|a|=n,|b|=m,|c|=s$，求长度最小的字符串$ans$，满足$a,b,c$都可以由$ans$的某个子串将其中某些字符替换成$\texttt?$得到。输出最小的长度。

>$n,m,s\in[1,2000]$。

（以下认为$n,m,s$同阶，在复杂度中用$n$表示）

首先，思路很显然：可以枚举$a,b$在$ans$的相对距离，如果无冲突就考虑$c$在$ans$中与$a,b$相对的位置。$a,b$的相对距离的数量是$\mathrm O(n)$，因为若$a$首$b$尾或$a$尾$b$首的距离超过$s+1$，那便没了意义。

接下来考虑确定了$a,b$的相对距离之后，如何“考虑$c$在$ans$中与$a,b$相对的位置”。显然，一次最多能承受$\mathrm O(n)$。

找到所有$c$的无冲突位置，然后以最小的能包含$a,b,c$的$|ans|$更新答案。位置数显然是$\mathrm O(n)$的。关键问题在于如何“找到所有$c$的无冲突位置”。看似很简单？哈希？Z？KMP？抱歉，都不行。该死的通配符$\texttt?$！显然，有了通配符之后，可匹配函数是这样定义的：$eq:eq(x,y)=[x=\texttt?\lor y=\texttt?\lor x=y]$，它并不满足传递性。而Z和KMP都利用了可匹配函数的传递性，所以跑不了。至于哈希，显然更跑不了了……bg，据说FFT可以解决带通配符的字符串模式匹配，而蒟蒻还没学过，而且那是$\mathrm O(n\log_2n)$的，你觉得能过么？

那怎么办呢？容易发现，字符串长度都很小，但是因为有$\mathrm O(n)$种相对位置，使得复杂度变高。我们可以充分利用“字符串长度都很小”这个特点，预处理一些东西。不难发现，$c$当前的位置无冲突，当且仅当它跟$a$无冲突且跟$b$无冲突。

以判断跟$a$有无冲突为例。显然，冲突只可能发生在$a,c$所覆盖的位置集合的交集里。于是我们考虑$a,c$覆盖的区间的关系，有以下几种：
1. $c$左离$a$，此时肯定无冲突；
1. $c$右离$a$，此时肯定无冲突；
1. $c$左交$a$，此时交集是$a$的前缀，共$\mathrm O(n)$种可能；
1. $c$右交$a$，此时交集是$a$的后缀，共$\mathrm O(n)$种可能；
1. $c$包含$a$，此时交集是$c$的长度为$|a|$的子区间，共$\mathrm O(n)$种可能；
1. $c$包含于$a$，此时交集是$a$的长度为$|c|$的子区间，共$\mathrm O(n)$种可能。

综上，共$\mathrm O(n)$种交集，对于每个交集都$\mathrm O(n)$暴力匹配预处理一下即可！

对$b$与$c$的冲突判断与$a$与$c$的冲突判断类似。

最后还有一个小调整：我们可以强行令$c$为长度最小的那个字符串，这样就可以排除掉第$5$种——$c$包含$a$啦！

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000;
int n,m,s;//3个字符串的长度 
char a[N+5],b[N+5],c[N+5];//3个字符串 
bool eq(char x,char y){return x=='?'||y=='?'||x==y;}//可匹配函数 
bool pre_a[N+1]/*交集是a的前缀*/,rg_a[N+1]/*交集是a的子区间*/,suf_a[N+1]/*交集是a的后缀*/,pre_b[N+1],rg_b[N+1],suf_b[N+1]/*类似a*/;
void pre_rg_suf_init(int lenx,char x[],bool pre[],bool rg[],bool suf[]){//预处理 
	memset(pre,1,N+1);memset(rg,1,N+1);memset(suf,1,N+1);
	for(int i=1;i<=s;i++)for(int j=1;j<=i;j++)/*暴力匹配*/pre[i]&=eq(x[j],c[j-i+s]); 
	for(int i=2;i+s-1<lenx;i++)for(int j=i;j<=i+s-1;j++)/*暴力匹配*/rg[i]&=eq(x[j],c[j-i+1]);
	for(int i=lenx-s+1;i<=lenx;i++)for(int j=i;j<=lenx;j++)/*暴力匹配*/suf[i]&=eq(x[j],c[j-i+1]);
}
bool ok(int dif){//a与b的位置差为dif时是否无冲突 
	for(int i=1;i<=n;i++)if(1<=i-dif&&i-dif<=m&&!eq(a[i],b[i-dif]))/*冲突*/return false;
	return true;
}
int sol(int dif){//a与b的位置差为dif时最小的|ans| 
	//设a的位置为1~n 
	int l=min(1,1+dif),r=max(n,m+dif);//能包含a,b的最小区间 
	int ans=inf;
	for(int i=l-s;i<=r+1;i++)//枚举c开头的位置 
		if((i+s-1<1?true:i<=1?pre_a[i+s-1]:i+s-1<n?rg_a[i]:i<=n?suf_a[i]:true)&&//a,c无冲突 
		   (i+s-1<1+dif?true:i<=1+dif?pre_b[i+s-1-dif]:i+s-1<m+dif?rg_b[i-dif]:i<=m+dif?suf_b[i-dif]:true)/*b,c无冲突*/)
			ans=min(ans,max(r,i+s-1)-min(l,i)+1/*能包含a,b,c的最小区间长度*/);//更新答案 
//	cout<<dif<<" "<<ans<<"\n";
	return ans;
}
int main(){
	cin>>a+1>>b+1>>c+1;
	n=strlen(a+1);m=strlen(b+1);s=strlen(c+1);
	if(s>n){
		for(int i=1;i<=s;i++)swap(a[i],c[i]);
		swap(n,s);
	}
	if(s>m){
		for(int i=1;i<=s;i++)swap(b[i],c[i]);
		swap(m,s);
	}//强行令c为最短的字符串 
	pre_rg_suf_init(n,a,pre_a,rg_a,suf_a);pre_rg_suf_init(m,b,pre_b,rg_b,suf_b);//预处理 
	int ans=inf;
	for(int i=-(m+s);i<=n+s;i++)if(ok(i))ans=min(ans,sol(i));//求答案 
	cout<<ans;
	return 0;
}
```

---

