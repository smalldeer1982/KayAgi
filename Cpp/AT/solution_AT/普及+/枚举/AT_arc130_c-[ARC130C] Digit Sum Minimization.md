# [ARC130C] Digit Sum Minimization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc130/tasks/arc130_c

正の整数 $ a,\ b $ が与えられます。ただし、$ a,\ b $ のどの桁も $ 0 $ ではありません。

$ a+b $ の各桁の和が最小になるように、$ a $, $ b $ のそれぞれの桁を並べ替えてください。

## 说明/提示

### 制約

- $ 1\leq\ a,\ b\ <\ 10^{100000} $
- $ a,\ b $ のどの桁も $ 0 $ ではない

### Sample Explanation 1

$ 532\ +\ 268\ =\ 800 $ で、その各桁の和は $ 8+0+0=8 $ となります。 他にも、$ (a,\ b)\ =\ (325,\ 682) $ を出力しても正解となります。

### Sample Explanation 2

$ 435+565=1000 $ で、その各桁の和は $ 1+0+0+0=1 $ となります。

### Sample Explanation 3

$ 312\ +\ 799788\ =\ 800100 $ で、その各桁の和は $ 8+0+0+1+0+0=9 $ となります。

## 样例 #1

### 输入

```
253
286```

### 输出

```
532
268```

## 样例 #2

### 输入

```
345
556```

### 输出

```
435
565```

## 样例 #3

### 输入

```
123
987987```

### 输出

```
312
799788```

## 样例 #4

### 输入

```
11111111111111111111
111111111111111111111111111111```

### 输出

```
11111111111111111111
111111111111111111111111111111```

# 题解

## 作者：XYQ_102 (赞：1)

首先我们自然的想法就是拼出最多的进位，这显然是正确的，我们想拼出尽量多的 $10$，然后接尽量多的 $9$。

仔细观察，其实我们只用拼出一个 $10$，后面都拼 $9$ 就可以，也就是 $s_0+t_0\geq10,i>1,s_i+t_i\geq9$。

由于只有 $s_0$ 和 $t_0$ 是特殊的，于是考虑枚举这两个数就做完了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define str string
str s,t;
int n,m,cs[10],ct[10],ts[10],tt[10];
#define pip pair<int,pair<str,str>>
#define mkp make_pair
#define fi first
#define se second
inline pip calc(int a,int b){
	for(int i=1;i<=9;i++)ts[i]=cs[i],tt[i]=ct[i];
	string S(1,a+'0'),T(1,b+'0');int res=1;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)if(i+j>=9){
			int c=min(ts[i],tt[j]);
			ts[i]-=c;tt[j]-=c;res+=c;
			S+=str(c,i+'0'),T+=str(c,j+'0');
		}
	res+=max(ts[9],tt[9]);
	for(int i=9;i>=1;i--)
		S+=str(ts[i],i+'0'),T+=str(tt[i],i+'0');
	reverse(S.begin(),S.end());
	reverse(T.begin(),T.end());
	return mkp(res,mkp(S,T));
} 
int main(){
	cin>>s>>t;
	pip ans=mkp(0,mkp(s,t));
	for(char c:s)cs[c-'0']++;
	for(char c:t)ct[c-'0']++;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			if(cs[i]&&ct[j]&&i+j>=10){
				cs[i]--,ct[j]--;
				ans=max(ans,calc(i,j));
				cs[i]++,ct[j]++;
			}
	cout<<ans.se.fi<<endl<<ans.se.se;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

分类讨论，但是写起来挺答辩的。

首先发现我们要使进位尽量多。

特判怎么重排都没有进位的情况（$a_i + b_i < 10$）。然后枚举个位选的两个数字，并且要求它们和 $\ge 10$。

- 如果当前位两个位都有数字，那么从小到大枚举数位的和 $\in [9, 18]$；如果有数字加起来等于枚举的和就直接进入下一位。注意要优先选非 $9$ 的数，这样留给后面只有一位有数字的进位就更多。如果当前位不可能产生进位了，那么就直接摆烂，随便选。
- 如果当前位只有一位有数字，优先选 $9$，然后再选其他的（其实不需要）。

然后就做完了。

[code](https://atcoder.jp/contests/arc130/submissions/41525192)

---

