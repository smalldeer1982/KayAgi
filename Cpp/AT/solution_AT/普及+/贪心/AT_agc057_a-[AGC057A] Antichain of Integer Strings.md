# [AGC057A] Antichain of Integer Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc057/tasks/agc057_a

正整数からなる集合 $ A $ は次の条件を満たすとき、**良い集合**であるといいます。

- 任意の相異なる $ 2 $ 要素 $ a,\ b\ \in\ A $ に対して、$ a $ を $ 10 $ 進法表記した文字列は、$ b $ を $ 10 $ 進法表記した文字列の部分文字列**ではない**。
 
 部分文字列とは？ 部分文字列とは連続する部分列のことを指します。例えば `1`, `12`, `23` は `123` の部分文字列ですが、`21` や `13` は `123` の部分文字列ではありません。 正整数 $ L,\ R $ が与えられます。$ L $ 以上 $ R $ 以下の整数からなる良い集合 $ A $ の要素数の最大値を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 10^4 $
- $ 1\leq\ L\leq\ R\leq\ 10^{9} $

### Sample Explanation 1

はじめの $ 2 $ つのテストケースについて、例えば次の $ A $ が要素数が最大であるような良い集合となります。 - $ 1 $ つめのテストケース：$ A=\{3,4,5,6,7,8\} $. - $ 2 $ つめのテストケース：$ A=\{3,4,6,8,9,10,11,12,15,17\} $.

## 样例 #1

### 输入

```
3
3 8
3 18
1 1000```

### 输出

```
6
10
900```

# 题解

## 作者：QianRan_GG (赞：1)

## 解题思路
本题考虑贪心做法。

首先可以想到位数越小的数作为其他数的子串的概率越大，所以我们可以从较大的数开始考虑。

当 $l$ 和 $r$ 的位数相同时，显然在 $l$ 到 $r$ 中的任何数都不能作为其他在此区间的数的子串，因为其中任意两个不同的数位数相同，而它们不同说明至少有一位上的数字不同。

当 $l$ 和 $r$ 的位数不同时，又要分两类讨论。  
1.$r$ 的最高位为 $1$ 时，假设 $l=12,r=123456$，则大于 $23456$（$r$ 的后五位）的数都能被选，因为从 $100000$ 到 $r$，$r$ 的第二高位并没有轮完一轮 $1$ 到 $9$ 的轮回。  
同理，当 $r=1000001$ 时，大于 $10000$（$r$ 的前五位）的数都能被选。  
还有就是 $l=99999,r=110001$，$r$ 的前五位和后五位组成的数都比 $l$ 小，所以此时能选的数是 $l$ 到 $r$。

2.$r$ 的最高位大于 $1$ 时，此时已经经历了至少一次 $1$ 到 $9$ 的轮回，所以不能选比 $r$ 位数低的数，例如当 $r=234567$ 时能选的数是 $100000$ 到 $r$。

## AC 代码
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
//保险一点开了long long
using namespace std;
int lg[15]; // 用于快速求出n位的最小数即10的n - 1次方
signed main()
{
	int t; scanf("%lld", &t);
	//预处理
	lg[1] = 1;
	for(int i = 2; i <= 12; ++ i)
		lg[i] = lg[i - 1] * 10;
	for(int i = 1; i <= t; ++ i)
	{
		int l, r;
		scanf("%lld%lld", &l, &r);
		int x = l, y = r, s1 = 0, s2 = 0; //s1是l的位数，s2是r的位数
		//求出位数
		while(x) s1 ++ , x /= 10;
		while(y) s2 ++ , y /= 10;
		if(s1 == s2) printf("%lld\n", r - l + 1); //位数相同时
		else
		{
			if(r / lg[s2] == 1) printf("%lld\n", r - max(r % lg[s2], max(r / 10, l - 1)));
			//r最高位是1时                              后s2 - 1位   前s2 - 1 位  l的值
			else printf("%lld\n", r - lg[s2] + 1);
		}
	}
}
```


---

## 作者：zhangxy__hp (赞：1)

记 $f(x)$ 为最小的大于 $x$ 的 $y$，使得 $x$ 是 $y$ 的子串。易得：

$$
f(x)=\min(10x,x+10^{|x|})
$$

其中 $|x|$ 表示 $x$ 的位数。

可以发现，$f(x)$ 为一个严格单调递增的函数。

考虑贪心策略，显然选小的数不如选大的数优，因为小的数更有可能成为别的数的子串。于是，我们要求的其实就是这样一个集合 $\mathbb{A}$，满足：

$$
\mathbb{A}=\{x\in[l,r]\mid f(x)>r\}
$$

因为 $f(x)$ 是严格单增的，因此二分即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define read(x){\
	char ch;\
	int fu=1;\
	while(!isdigit(ch=getchar()))\
		fu-=(ch=='-')<<1;\
	x=ch&15;\
	while(isdigit(ch=getchar()))\
		x=(x<<1)+(x<<3)+(ch&15);\
	x*=fu;\
}
#define int ll
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int pw10[]={
1,
10,
100,
1000,
10000,
100000,
1000000,
10000000,
100000000,
1000000000,
10000000000,
100000000000};
il int len(int x){
	int res=0;
	do{
		res++,x/=10;
	}while(x);
	return res;
}
il int f(int x){
	return min(x*10,x+pw10[len(x)]);
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
signed main(){
//	for(int i=1;i<=33;i++){
//		cout<<i<<" "<<f(i)<<"\n";
//	}
	int T;
	read(T);
	while(T--){
		int l,r,L,R;
		read(l)read(r);
		L=l,R=r;
		while(l<r){
			int mid=(l+r)>>1;
			if(f(mid)>R){
				r=mid;
			}
			else{
				l=mid+1;
			}
		}
		printf("%d\n",R-l+1);
	}
	return 0;
}
}
signed main(){return asbt::main();}
```

---

## 作者：MurataHimeko (赞：0)


如果两个不同的数位数相同，那么这两个数不可能存在包含关系。

当 $l$ 和 $r$ 位数相同时，输出 $r-l+1$。

忽略最高位，那么一个 $x+1$ 位的数可以对应到一个 $x$ 位的数。

不妨就只选位数最多的。

设 $z$ 为最大的小于 $r$ 的 $10$ 的幂。
那么答案为

$$r - z + 1 + (z - \max({\lfloor \frac{r}{10} \rfloor + 1, r - z + 1, l, \lfloor \frac{z}{10} \rfloor + 1}))$$

代码：

```cpp
signed main () { 
	io >> T;
	while(T--) {
		io >> l >> r;
		int lim = 1;
		while(lim * 10 <= r) {
			lim *= 10;
		}
		if(l >= lim) {
			io << r - l + 1 << "\n";
			continue;
		}
		if(r - lim + 1 >= lim) {
			io << r - lim + 1 << "\n";
			continue;
		}	
		int ans = r - lim + 1 + lim - max({r / 10 + 1, r - lim + 1, l, lim / 10 + 1});
		io << ans << "\n";
	}
}
```


---

## 作者：SMTwy (赞：0)

越是小的数，能组成的大的数就越多，选它的代价就越大。

肯定是从后往前先选大的数。

这题主要还是细节问题比较多。

如果 $l$ 和 $r$ 的位数一样，答案就是之间的所有数，因为位数一样，没有数可以组成或者被组成。

如果位数不一样，答案就是 $r$ 减去 $r$ 的位数。所有比这些小的数都会去组成它，不能再选。

只有一种特例是 $r$ 的开头位数是 $1$。这个时候它可能铺不满一个整的 $9$。下面有些小的数可以被选。

比如 $l$ 是 $35$。$r$ 是 $13789$。像 $7865$ 这些比 $3789$ 大的数都是可以选的。而如果 $r$ 是 $24097$。$r$ 从最高位的 $1$ 到 $2$ 可以走完一个整的 $9$。所以小的不能再选。


其实也就是减一下，再处理边界即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=1000;
int T,l,r;
int pos[mx];
inline int get(int x){
    int ret=0;
    while(x){x/=10;ret++;}
    return ret;
}
void MYH(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&l,&r);
        int re1=get(l),re2=get(r);
        int ans=0;re1--;re2--;
        if(re1==re2)ans=r-l+1;
        else {
            int uo=1;
            for(int i=1;i<=re2;++i){uo*=10;}
            if(r/uo>1){
                ans=ans+r-uo+1;
            }
            else {
                int t=r-r/uo*uo;
                int tt=r-r/uo*uo;
                ans=ans+r-uo+1;
                int u1=uo/10;
                int u2=r/10;
                t=max(t,max(l,max(u2,u1)));
                ans=ans+uo-t;
                if(t==uo/10 || t==tt || t==u2)ans--;
            }
        }
        printf("%d\n",ans);
    }
}
int main(){
 //   freopen("1.in","r",stdin);
 //   freopen("1.out","w",stdout);
    MYH();
    return 0;
}
```



---

