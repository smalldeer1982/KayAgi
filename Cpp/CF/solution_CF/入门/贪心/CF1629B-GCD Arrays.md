# GCD Arrays

## 题目描述

考虑一下数组 $a$，范围是 $[l,r]$。例如，$[3,7]$，数组 $a$ 就是 $[3,4,5,6,7]$。   
给出 $l,r,k$，询问 $gcd(a)$ 是否能在最多 $k$ 次如下 操作以后比 1 大？
* 在 $a$ 数组中选择两个数。
* 删除这两个数。
* 将这两个数的乘积放回数组 $a$。    

其中，$gcd(b)$ 意思就是 $b$ 数组中数字的[最大公因数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fromtitle=%E6%9C%80%E5%A4%A7%E5%85%AC%E5%9B%A0%E6%95%B0&fromid=869104&fr=aladdin)

## 说明/提示

对于样例输入的第 1 组测试数据，$a = [1]$，所以输出
`NO`，因为 1 是数组 $a$ 的唯一元素。   
对于样例输入的第 2 组数据，数组 $a = [3,4,5]$，现在我们有 1 次操作机会。不难发现，无论如何操作，结果只会有 3 个：$[3,20],[4,15],[5,12]$，他们的最大公因数都是 1，没有其他的数，所以输出
`NO`。    

对于样例输入的第 3 组测试数据，$a = [13]$，所以输出
`YES`，因为唯一的元素就是 13，一个质数。

对于样例输入的第 4 组数据，$a = [4]$，输出
`YES`，因为 4 是唯一的元素。

## 样例 #1

### 输入

```
9
1 1 0
3 5 1
13 13 0
4 4 0
3 7 4
4 10 3
2 4 0
1 7 3
1 5 3```

### 输出

```
NO
NO
YES
YES
YES
YES
NO
NO
YES```

# 题解

## 作者：xzyg (赞：3)

## 题意简述：

给定正整数 $l,r,k$，有集合 $A=\{l,l+1,l+2...r-2,r-1,r\}$，

*操作*：任选两个数，删去一个，并将两个数的乘积加入到集合 $A$ 里。

问： $k$ 次*操作*后，$\gcd(A)$ 能否不为 $1$。若可以，则输出“YES”；反之，输出“NO”。

## Sol:

操作等价于将一个数乘上另一个数 ~~（显然）~~。

要使 $\gcd(A) \ne 1$ 那么就要使集合 $A$ 内的所有数有**共同的质因数 $p$ 。**

那么就要进行一步操作，使质因数没有 $p$ 的数乘上质因数有 $p$ 的数，从而使前者的质因数带有 $p$。

容易发现，当 $p=2$ 时，操作数最少，此时将所有奇数乘上一个偶数即可。

所以，**最少操作数为原集合中奇数的个数**。

所以分类讨论出原区间内奇数的个数，再与 $k$ 比较就可以了。

设原区间共 $s$ 个数，则 $s = r - l +1$。

当 $s \bmod 2 = 1$ 且 $l \bmod 2 = 1$ 时，最小操作数为 $\left\lfloor\dfrac{s}{2}\right\rfloor+1$

当 $s \bmod 2 = 1$ 且 $l \bmod 2 = 0$ 时，最小操作数为 $\left\lfloor\dfrac{s}{2}\right\rfloor$

当 $s \bmod 2 = 0$ 且 $l \bmod 2 = 1$ 时，最小操作数为 $\dfrac{s}{2}$

当 $s \bmod 2 = 0$ 且 $l \bmod 2 = 0$ 时，最小操作数为 $\dfrac{s}{2}$

最后特判一下 $r=1$ 和 $l=r$ 的情况就 AC 了。

### 代码：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll unsigned long long
using namespace std;

int main(){	
	ll t;
	cin >> t;
	while(t--){
		ll l,r,k;
		cin >> l >> r >> k;
		if(r == 1){
			cout << "NO" << endl;
		}else if(l == r){
			cout << "YES" << endl;
		}else{
			ll s = r - l + 1;
			bool f = l % 2, p = s % 2;
			ll limit;
            
			if(f && p) 
                limit = s / 2 + 1;
			else 
                limit = s / 2;
			if(k >= limit)
                cout << "YES" << endl;
			else 
                cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：2)

思维题。

分类讨论。

当 $k = 0$ 时，当且仅当 $l = r$ 且 $l\neq 1$ 时，$\gcd(a) \gt 1$。

否则，我们将序列 $a$ 中所有的奇数全部和一个偶数进行操作，并且保留偶数，删除在序列里的奇数。

当 $l$ 和 $r$ 都是奇数的时候，序列要操作的次数为 $\frac{r-l+1}{2}+1$，否则需要操作的次数为 $\frac{r-l+1}{2}$。

当需要操作的次数 $\gt k$ 的时候，可以让 $\gcd(a)\gt 1$，否则无法让 $\gcd(a) \gt 1$。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int T;
    cin >> T;
    while (T --) {
        long long a, b, c;
        scanf ("%lld%lld%lld", &a, &b, &c);
        if (c == 0) {
            if (a == b && a != 1) {
                puts("YES");
            } else {
                puts("NO");
            }
        } else {
            long long CC = (b - a + 1);
            long long C = (CC >> 1);
            if ((a & 1) && (b & 1)) C ++;
            if (C <= c) puts("YES");
            else        puts("NO");
        }
    }
    return 0;
}
```


---

## 作者：Novice233 (赞：0)

那天打了现场比赛，看到这道题的时候有点懵，但很快发现：这不就一道数学题吗...

我们可以从另一个角度来翻译一下题面。

已知目前有一个数 $k$ ,请问让整个序列里所有数的最大公约数是 $k$ 需要几步（记为 $A_k$ )？ 然后对于所有的 $A_k$ ( $1 \leqslant  i \leqslant n $ ) 最小值是多少？

其实稍微想想就知道。肯定是 $k=2$ 的时候，$A_k$ 取到最小值.

原因很简单，对于目前数列里不是 $k$ 的倍数的数字，需要一个 $k$ 的倍数与其取最小公倍数。那么取 $k=2$ 就是最好的抉择。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,k;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>l>>r>>k;
		if(l==r){
			if(l==1) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
		else if(l%2==1&&r%2==1){
			if(k<(r-l)/2+1) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
		else if(l%2==0&&r%2==0){
			if(k<(r-l)/2) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
		else{
			if(k<(r-l+1)/2) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：BaCO3 (赞：0)

## 题意
给你一个序列 $a$，包含区间 $[l,r]$ 中的整数，你可以从中任选两个数删除，再将他们的乘积放回序列中。问你能不能在最多 $k$ 次操作后，使 $\gcd(a)>1$。

## 分析
在任意一个区间 $[l,r]$ 中，包含的 $2$ 的倍数一定是最多的（当然 $1$ 除外哈），所以我们考虑将数列中的数都变成 $2$ 的倍数。

那么做法就很显然了，只要判一下区间 $[l,r]$ 中奇数的个数和 $k$ 的大小就好了。

记得要特判一下 $l=r$ 的情况。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t,l,r,k;
 
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r>>k;
		if(l==r){
			if(l==1) cout<<"NO"<<endl;
			else cout<<"YES"<<endl;
			continue;
		}
		if((r-l)%2==1){
			if(k>=(r-l+1)/2) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
		else{
			if(l%2==1){
				if(k>=(r-l)/2+1) cout<<"YES"<<endl;
				else cout<<"NO"<<endl;
			}
			else{
				if(k>=(r-l)/2) cout<<"YES"<<endl;
				else cout<<"NO"<<endl;
			}
		}
	}
    
    return 0;
}
```


---

## 作者：清烛 (赞：0)

发现该问题等价于删去最少的数使得数集中的 $\gcd$ 大于 $1$。

然后发现 $\forall a$，都有 $\gcd(a, a + 1) = 1$。所以我们考虑在 $[l,r]$ 中保留所有的偶数。这样子可以使得他们的 $\gcd$ 至少为 $2$，不难发现这样一定是最优的（因为其他数的倍数必然少于 $2$ 的倍数）

所以统计 $[l,r]$ 中奇数个数即可，需特判 $l = r$ 的情况。

```cpp
int main() {
    int T; read(T);
    while (T--) {
        int l, r, k; read(l, r, k);
        if (l == r) print(l > 1 ? "YES" : "NO");
        else {
            int cnt = (r - l + 1) >> 1;
            if (!(l & 1) && !(r & 1)) ++cnt;
            print(r - l + 1 - cnt <= k ? "YES" : "NO");
        }
    }
    return output(), 0;
}
```

---

## 作者：zhicheng (赞：0)

### 题意简述

求出：去掉连续数组中的不多于 $k$ 个数后，是否能使数组的最大公因数大于 $1$。

### 题目分析

题目实际上就是让我们将数组的每一个元素都变为 $v$ $(v > 1)$ 的倍数。

而在题目要求的$[l,r]$范围内，只要 $l$ 与 $r$ 不相等，$2$ 的倍数一定是最多的。

于是题目转化为：去掉连续数组中的不多于 $k$ 个数后，是否能使数组所有数都为偶数。

注意当 $l=r$，需要特判：

- 当 $l=r=1$，一定不能；
- 否则可以。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,num,a,b,c;
	scanf("%d",&n);
	while(n--){
		scanf("%d%d%d",&a,&b,&c); //题目中的l，r，k
		if(a==b){  //特判
			if(a==1){
				printf("NO\n");
			}
			else{
				printf("YES\n");
			}
			continue;
		}
		num=(b/2-(a-1)/2); //偶数个数
		if(b-a+1-num<=c){  //奇数个数是否小于等于可删去数的个数
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}
```
~~球赞~~

---

## 作者：CmsMartin (赞：0)

## 题目简述

[题目传送门](https://www.luogu.com.cn/problem/CF1629B)

给你一个长度为 $N$ 的 $a$ 数组（$a$ 数组的元素是 $l$ 到 $r$ 区间中的整数），你可以进行 $k$ 此操作，每次操作可以选择两个数，将他们的乘积加入 $a$ 数组并且删除这两个数，问 $k$ 此操作后能否使 $\gcd(a)$ 大于 $1$

## 思路

很容易想到要让每个奇数与偶数相乘，很容易算出数组中的奇数个数（即最小操作次数），**并且对 $L = R$ 特判即可**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
template<class T>
inline char read(T &ret) {
	ret = 0;
	char c = getchar();
	short f = 1;
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c <= '9' && c >= '0') {
		ret = (ret << 3) + (ret << 1) + c - 48;
		c = getchar();
	}
	ret *= f;
	return c;
}
 
int T;
int L , R , K;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--) {
		cin >> L >> R >> K;
		int Count = 0;
		if(L % 2 == 0 && R % 2 == 1) {
			Count = (R - L + 1) / 2;
		}
		else if(L % 2 == 0 && R % 2 == 0) {
			Count = (R - L + 1) / 2 + 1;
		}
		else if(L % 2 == 1 && R % 2 == 0) {
			Count = (R - L + 1) / 2;
		}
		else if(L % 2 == 1 && R % 2 == 1) {
			Count = (R - L + 1) / 2;
		}
		if(L == R) {
			if(L == 1) cout << "NO" << endl;
			else if(L != 1) cout << "YES" << endl;
		}
		else if(R - L + 1 - Count > K) cout << "NO" << endl; 
		else cout << "YES" << endl;
	}
	return 0;
}
```

---

