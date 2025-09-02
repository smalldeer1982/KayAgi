# Add Modulo 10

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \dots, a_n $

You can apply the following operation an arbitrary number of times:

- select an index $ i $ ( $ 1 \le i \le n $ ) and replace the value of the element $ a_i $ with the value $ a_i + (a_i \bmod 10) $ , where $ a_i \bmod 10 $ is the remainder of the integer dividing $ a_i $ by $ 10 $ .

For a single index (value $ i $ ), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of $ a_i $ is taken into account each time. For example, if $ a_i=47 $ then after the first operation we get $ a_i=47+7=54 $ , and after the second operation we get $ a_i=54+4=58 $ .

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array $ [6, 11] $ .

- Let's apply this operation to the first element of the array. Let's replace $ a_1 = 6 $ with $ a_1 + (a_1 \bmod 10) = 6 + (6 \bmod 10) = 6 + 6 = 12 $ . We get the array $ [12, 11] $ .
- Then apply this operation to the second element of the array. Let's replace $ a_2 = 11 $ with $ a_2 + (a_2 \bmod 10) = 11 + (11 \bmod 10) = 11 + 1 = 12 $ . We get the array $ [12, 12] $ .

Thus, by applying $ 2 $ operations, you can make all elements of an array equal.

## 说明/提示

The first test case is clarified above.

In the second test case, it is impossible to make all array elements equal.

In the third test case, you need to apply this operation once to all elements equal to $ 5 $ .

In the fourth test case, you need to apply this operation to all elements until they become equal to $ 8 $ .

In the fifth test case, it is impossible to make all array elements equal.

In the sixth test case, you need to apply this operation to all elements until they become equal to $ 102 $ .

## 样例 #1

### 输入

```
10
2
6 11
3
2 18 22
5
5 10 5 10 5
4
1 2 4 8
2
4 5
3
93 96 102
2
40 6
2
50 30
2
22 44
2
1 5```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
Yes
No```

# 题解

## 作者：EXODUS (赞：26)

# Part 1：前言
算是一道强大思维题（？

以下均为赛事想法

# Part 2：正文
~~通过大量的口胡~~可以发现，每次进行操作后个位数的变化是有规律的。然后我就花了一张~~很抽象的~~图。
![](https://cdn.luogu.com.cn/upload/image_hosting/tng0ro7v.png)
这是个位数字的变化规律。

接下来开始口胡。

1. 由于奇数只要变化一次就会变成偶数，且不会变回来，所以可以先把奇数变成偶数，这对答案没有影响。

尽管很显然，但我还是想简单证明一下qwq。

>- 如果原数列都是奇数且相等，注意到变化是对答案没有影响的，因为都是加上了一个相同的数，该相等的仍然相等。
>
>- 如果原数列有奇数且不全部相等，则答案一定不会是奇数
>>- 原数列全部是奇数，则必然会有一个奇数需要变化，其变化后会变成偶数且不会再变成奇数，则答案是偶数，所有奇数至少变化一次。
>>- 原数列有偶数，偶数变化后会变成偶数且不会再变成奇数，则答案是偶数，所有奇数至少变化一次。

下文中，称其为**奇数变化**。

2. 如果原序列在奇数变化后结尾存在 $0$，必然要求所有数字都和该数相等。

注意到 $0$ 是没有出边的，也就是说他的值不可能再变化了。那么只能是其他值变成他。

下文称其为**非零判断**，称**非零判断的值为真**代表在经过奇数变化后，原序列不存在位置 $i$，使得 $a_i\%10=0$。

3. 如果原序列在经过奇数变化后且非零判断的值为真，则 $[a_1,a_2,...,a_n]$ 是否成立与  $[a_1\%20,a_2\%20,...,a_n\%20]$ 是否成立等价。

注意到在环上转一圈不会改变个位数，且会让你的原数加 $20$，所以你可以直接对 $20$ 取模。

那么搞到这一步，基本结束了。

一次变换相当于在环上走一步。而在环上最多走 $3$ 步（第 $4$ 步就加 $20$ 了，取模意义下和走 $0$ 步等价），开桶记一下即可。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
using namespace std;
typedef long long ll;
il int read(){
    int ans=0,flag=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
    return ans*flag;
}
const int N=2e5+7;
int T;
int a[N];
int t[44];
int n;
int main(){
    T=read();
    while(T--){
        n=read();
        memset(t,0,sizeof(t));
        for(int i=1;i<=n;i++){
            a[i]=read();
            if(a[i]&1)a[i]+=a[i]%10;
        }
        for(int i=1;i<=n;i++){
        	if(a[i]%10==0){
        		for(int j=1;j<=n;j++){
        			if(a[j]!=a[i]){
        				puts("No");
        				goto there;
					}
				}
				break;
			}
		}
        for(int i=1;i<=n;i++){
            
            a[i]%=20;
            if(a[i]%10==0){
                t[a[i]]++;
            }else if(a[i]%10==2){
                t[a[i]]++;
                t[a[i]+2]++;
                t[a[i]+6]++;
                t[a[i]+14]++;
            }else if(a[i]%10==4){
                t[a[i]]++;
                t[a[i]+4]++;
                t[a[i]+12]++;
                t[a[i]+18]++;
            }else if(a[i]%10==8){
                t[a[i]]++;
                t[a[i]+8]++;
                t[a[i]+14]++;
                t[a[i]+16]++;
            }else if(a[i]%10==6){
                t[a[i]]++;
                t[a[i]+6]++;
                t[a[i]+8]++;
                t[a[i]+12]++;
            }
        }
        for(int i=0;i<=40;i++){
            if(t[i]==n){
                puts("Yes");
                goto there;
            }
        }
        puts("No");
        there:;
    }
    return 0;
}
/*
9
4143 341351 3245326 321411 32411 34123 415243 798989 7689
*/
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：I_am_Accepted (赞：21)

~~这玩意有算法吗。~~

首先我们达成共识：相同的两个数经过操作后必然相同（这不是映射吗）。

我们考察十进制末位，即数经过一次变换后末位会从啥变成啥：

![](https://cdn.luogu.com.cn/upload/image_hosting/ieb4ba3a.png)

由图得 $\{a\}$ 中不能同时存在 $5$ 的倍数和非 $5$ 的倍数。

若全为 $5$ 的倍数，将她们的末尾全部操作为 $0$，判断相等即可。

若全非 $5$ 的倍数，将她们的末尾全部操作为 $2$。由于 $2\to 4\to 8\to 6\to 2$ 绕一圈后原数会 $+20$，所以我们判断这些数是否 $\bmod\ 20$ 同余即可。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define N 200010
int n,a[N];
void calc(int &x){ while(x%10!=2 && x%10!=0) x+=x%10; }
void work(){
	cin>>n;
	For(i,1,n) cin>>a[i];
	int cnt=0;
	For(i,1,n) if(a[i]%5==0) cnt++;
	if(cnt>0 && cnt<n){
		cout<<"NO"<<endl;
		return ;
	}
	For(i,1,n) calc(a[i]);
	if(!cnt) For(i,1,n) a[i]%=20;
	For(i,2,n) if(a[i]!=a[i-1]){
		cout<<"NO"<<endl;
		return ;
	}
	cout<<"YES"<<endl;
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

## 作者：Dry_ice (赞：5)

[Blog推广](https://www.cnblogs.com/dry-ice/p/cf1714e.html)

> 这个E题有点怪。

## Description
你有一种操作，名曰 ```x+=x%10```，现在给你 $n$ 个数 $a_1$ 到 $a_n$，让你求能否对每个数字进行若干次上述操作使 $n$ 个数相同。

## Analysis
由于操作与个位数有关，故对个位数进行分析。

若个位数为 $1$，可经一次操作得到 $2$；

若个位数为 $3$，可经一次操作得到 $6$；

若个位数为 $7$，可经一次操作得到 $4$；

若个位数为 $9$，可经一次操作得到 $2$；

若个位数为非零偶数，则可经若干次操作相互转化（循环），具体表示为：
$$2\to4\to8\to6\to2\to4\to8\to6\to2\to\cdots$$

而对于个位数 $0$ 和 $5$，则有转化链：
$$5\to0\to0\to0\to\cdots$$

规律应该都懂了，下面看怎么判断多个数能否转为同一个数。

1. 第一种情况：$\exists a_i,a_i\equiv0\ \text{or}\ 5\pmod{10}$
则末位为 $5$ 的数最多进行一次操作，末位为 $0$ 的进行操作无效。故只需两次特判，一次原序列判断是否全相等，一次判断对末位为 $5$ 的数操作一次能否是全序列相等，若有一次满足相等，则输出 ```Yes```，否则为 ```No```。

2. 第二种情况：$\forall a_i,a_i\not\equiv0\ \text{or}\ 5\pmod{10}$
不妨先对序列不降排序，把除最大数外数的各位都转化为 $2$ 结尾的数，目的是将各数转化到 $2486$ 的循环上。

然后对 $a_n$ 即最大数进行操作，达成一次末位数循环，比如：$7\to4\to8\to6\to2$。对于每个操作后的 $a_n$，都对 $a_1$ ~ $a_{n-1}$ 扫描一次判断能否经过操作达到当前的 $a_n$。

由于一次 $2486$ 循环加 $2+4+8+6=20$，故判断是只需将 $a_n-a_i$ 的值先模 $20$，再判断余数是否为 $0,2=2,2+4=6$ 或 $2+4+8=14$，若能分解则 $a_i$ 可经过有限次操作转化为当前的 $a_n$。

若有一个操作后的 $a_n$ 对 $a_1$ ~ $a_{n-1}$ 均能达成，则输出 ```Yes```，否则 ```No```。

讲起来有些复杂，举个例子：原序列为 $44,11$。

第一步，先排序，得 $11,44$；

第二步，把除最大值外的数末位操作为 $2$，得 $22,44$；

第三步，对 $44$ 进行末位数循环：$44\to88\to176\to352\to704$，发现 $44-22=22\equiv2\pmod{20}$，故 $a_n$ 原数即可行，故答案为 ```Yes```。

## Code
理论明白了，还要用代码实现。

```cpp
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const LL N = (LL)2e5 + 5, rep[] = {0, 2, 4, 8, 6}, srep[] = {0, 2, 6, 14};
LL n, a[N];
inline bool check(LL x) {
    x %= 20;
    for (LL i = 0; i < 4; ++i)
        if (x == srep[i]) return true;
    return false;
}
int main(void) {
    LL t; for (scanf("%lld", &t); t--; ) {
        scanf("%lld", &n); bool flag = false;
        for (LL i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            if (a[i] % 5 == 0)  flag = true; //是否存在 x % 5 == 0 的数 x
        }
        if (flag) {
            bool ok = true;
            for (LL i = 1; i <= n; ++i) {
                if (a[i] % 10 == 5) a[i] += 5;
                if (i != 1 && a[i] != a[i - 1]) {ok = false; break;}
            }
            puts(ok ? "Yes" : "No");
            continue;
        }
        std:: sort(a + 1, a + 1 + n); //排序
        for (LL i = 1; i <= n; ++i) //转末位为2
            while (a[i] % 10 != 2) a[i] += a[i] % 10;
        for (LL i = 0; i < 5; ++i) { //最大数末位循环
            a[n] += rep[i]; flag = true;
            for (LL j = 1; j < n; ++j)
                if (!check(a[n] - a[j])) {flag = false; break;} //判断各数可行与否
            if (flag) break;
        }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}
```

## The end. Thanks.

---

## 作者：Daidly (赞：3)

观察个位数就可以得到一些变换的规律。

譬如：$1\to2\to4\to8\to6\to2\to\cdots$ 是有循环节的。

考虑 $0\sim 9$ 之间的联系，可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nf2i26w.png)

这是 $0\sim 9$ 每个数经过变换后得到结果形成的一幅有向图。

$7\to14\to18\to26\to32\to\cdots$ 在此图中就表示为 $7\to4\to8\to6\to2\to\cdots$

可以发现，图中有一个由 $2,4,8,6$ 组成的环，即：若一列数的个位能变成 $2,4,8,6$ 中的任何一个，就能变成其他三个，并且增量为 $20$。因为 $2\to4\to8\to16\to22$ 一圈的增量是 $22-2=20$。也就是说，在保证个位不变的情况下，十位可以每次增加 $2$（奇偶性不变）。

我们得到这样一个结论：判断序列中每一个数个位能否变成 $2$ 并加上对应的增量，若之后的每一个数的十位奇偶性相同，则一定可以变成同一个个位为 $2$ 的数。

通过图中的关系我们可以发现，一个数的个位若为 $1,2,3,4,6,7,8,9$，则都可以通过加上固定的增量变成 $2$。可以提前手算出增量数组：$add[10]=\{-1,1,0,9,18,-1,6,25,14,23\}$，其中 $-1$ 表示无法达到。

然后我们再关注这无法达到的两个数 $0,5$。$5$ 只能变换一次变成个位为 $0$，直接计算即可。

- 注意：在判断序列是否每个数都相同时，需要特判或排除 $a[0],a[n+1]$ 的情况。譬如：`if(a[i]==a[i-1])cnt++;` 是错的，需要 `if(a[i]==a[i-1]&&i!=1)cnt++;`。因为 $a_i$ 可能为 $0$！！！

较为简洁的代码：

```cpp
const int MAXN=2e5+5;
int t,n,a[MAXN],add[10]={-1,1,0,9,18,-1,6,25,14,23};

int main(){
	t=read();
	while(t--){
		n=read();
		int cnt=0;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]%10==5)a[i]+=5;
			if(a[i]==a[i-1]&&i!=1)cnt++;
		}
		if(cnt==n-1){puts("YES");continue;}
		cnt=0;
		for(int i=1;i<=n;++i){
			if(add[a[i]%10]==-1)break;
			a[i]+=add[a[i]%10];a[i]/=10;a[i]&=1;
			if(a[i-1]==a[i]&&i!=1)cnt++;
		}
		if(cnt==n-1){puts("YES");continue;}
		puts("NO");
	}
	return 0;
}
```

---

## 作者：Hedgehog_210508 (赞：1)


**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1714E)

**题意**：$n$ 个数，每次可让 $1$ 个数加上自己 $\bmod 10$ 的余数，问是否能让所有数都相等。

**思路**：找规律

- 情况一：尾数为 $5$ 或 $0$

为 $5$ 时进行一次操作变成 $0$ 的情况。

而尾数是 $0$ 时操作无意义，所有数必须相等。

- 情况二：尾数为 $1,3,7,9$

可进行一次操作变成情况三。

- 情况三：尾数为 $2,4,6,8$

我们通过找规律发现：

$2 \Rightarrow 4 \Rightarrow 8 \Rightarrow 16 \Rightarrow 22$  
$4 \Rightarrow 8 \Rightarrow 16 \Rightarrow 22 \Rightarrow 24$  
$6 \Rightarrow 12 \Rightarrow 14 \Rightarrow 18 \Rightarrow 26$  
$8 \Rightarrow 16 \Rightarrow 22 \Rightarrow 24 \Rightarrow 28$

每个数可以转换为它自己 $+20$ 的数，我们可以让每个数加足够多的 $20$，所以不妨 $\bmod 20$ 再进行比较。

而我们把尾数统一（比如都变成 $2$）之后，$2$ 和 $12$ 再也不能变成相同的了，所以这时全相等就相当于符合要求。

**代码**：（超短的
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,a[200009];
		cin>>n;
		for(ll i=1;i<=n;i++) cin>>a[i];
		for(ll i=1;i<=n;i++){
			if(a[i]%2) a[i]+=a[i]%10;
			if(a[i]%10) a[i]%=20;
		}
		for(ll i=1;i<=n;i++){
			if(a[i]%10!=0){
				if(a[i]%10==4) a[i]=(a[i]+18)%20;
				if(a[i]%10==6) a[i]=(a[i]+6)%20;
				if(a[i]%10==8) a[i]=(a[i]+14)%20;
			}
		}
		bool flag=0;
		for(ll i=1;i<n;i++)
			if(a[i]!=a[i+1]) flag=1;
		if(flag) cout<<"No";
		else cout<<"Yes";
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：xzy090626 (赞：0)

# CF1714E 题解
## 前言
由于本人太菜了不会做 D，所以赛时没开 E，十分后悔（E 为什么比 D 简单这么多？？）。

也告诫大家，一定要开完所有的题，不要放弃。
## 题意
给你一个长为 $n$ 的序列 $a$，每次操作可以选出 $a_i$ 使得 $a_i = a_i + (a_i \bmod 10)$。你需要回答，是否可以在若干次操作之后使得 $a$ 的所有元素都相同。

多测，$1\le t\le 10^4$，$1\le n \le 2\cdot 10^5$，$0\le a_i \le 10^9$，所有 $n$ 的值之和不大于 $2\cdot 10^5$。
## 分析
打表找规律的好题。

我们先来对 $a$ 只含 $2$ 个数的情况进行打表。

这里贴心地给出 generator。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4;
int main(){
	for(int i=1;i<=10;++i){
		for(int j=1;j<=10;++j){
			if(i==j) continue;
			int x = i,y = j;
			int cnt = 0;
			while(x%10!=y%10){
				x += x%10;
				cnt++;
				if(cnt>N){
					cout<<i<<' '<<j<<":NO\n";
					break;
				}
			}
			if(cnt<=N) cout<<i<<' '<<j<<":YES\n";
		}
	}
	return 0;
}
```
很容易可以发现，当 $(a_i \bmod 10)$ 为 $5$ 或 $10$ 时，它也只能变为 $5$ 或者 $10$。而其他的数，无论奇偶，都可以变为偶数。

我们可以对其进行分类，将所有 $5$ 的倍数分为一类，其他的分为一类。

现在情况就很明了了：$5$ 的倍数出现的次数要么为 $0$，要么为 $n$（即全部都是 $5$ 的倍数），才能成功。

但是这就完了吗？

我们看到第二组样例：
```
3
2 8 22
```
答案是
```
NO
```
奇怪？为什么和我们之前打表找出的规律不一样？

原来，原题要求的是所有的 $a_i$ 相等，但是我们目前只能做到 $a_i \bmod 10$ 相等。

那么我们可以手算一下：

---
$2 \to 4 \to 8 \to 6 \to 2$

$2 \to 4 \to 8 \to 16 \to 22$

---
容易发现，每进行一轮，数据就会增加 $20$。

由于是取模数而非乘法，所以这个规律适用于所有非负整数。

也就是说，所有的数可以通过若干轮操作来变得相等。

那么，我们可以让所有数都不断进行操作直到末位为 $2$。

只要所有的数两两之差都是 $20$ 的倍数，就可以成功。

我们其实没有必要枚举 $i,j$ 进行判断，可以让所有的数对 $20$ 取模即可，然后判断是否相等即可。

---
另：对于所有的 $a_i$ ，如果均是 $5$ 的倍数的话，那么发现没有必要也不能取模，因为以 $0$ 结尾的数无法进行操作，而以 $5$ 结尾的数也只能操作一次，所以不需要取模。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;
int s[N];
int work1(int a){
	while(a%10!=2) a += a%10;
	return a;
}
int work2(int a){
	while(a%10!=0) a += a%10;
	return a;
}
void solve(){
	int n;
	bool flag = 0;
	cin>>n;
	int cnt = 0;
	for(int i=1;i<=n;++i){
		cin>>s[i];
		if(s[i]%5==0) cnt++;
	}
	if(cnt!=0 && cnt!=n){
		cout<<"NO\n";
		return ;
	}
	else flag = cnt;
	for(int i=1;i<=n;++i){
		if(flag) s[i] = work2(s[i]);
		else s[i] = work1(s[i])%20;
		if(s[i]!=s[i-1] && i!=1){
			cout<<"NO\n";
			return ;
		}
	}
	cout<<"YES\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

我们统计一下 $5$ 的倍数有多少个，设为 $cnt_5$。

+ 当 $cnt_5=n$ 时：

	很明显，如果 $a_i\bmod10=0$，它已经无法修改；所以，如果存在以 $0$ 结尾的数，就只能将以 $5$ 结尾的数变为以 $0$ 结尾的数。
    
   如果变化后数字不一样，就输出 `No`，否则输出 `Yes`。
   
+ 当 $0<cnt_5<n$ 时：

	因为 $5$ 的倍数和非 $5$ 的倍数永不能互通，所以无解。
    
+ 当 $cnt_5=0$ 时：

	我们可以发现，无论结尾是什么，都可以经过变换后，到 $2,4,8,6,……$ 的循环上。
    
   并且，一个循环过后，这个数会加 $20$。
   
   所以，我们可以先将所有数的结尾统一一下，统一到 $2$ 上。然后将它们分别模 $20$，看数字是否相同即可。
   
### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
long long a[max_n+2];
int cnt5;
bool check(){
	int x=a[1];
	for(int i=2;i<=n;++i){
		if(a[i]^x)return false;
	}
	return true;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714E_1.in","r",stdin);
	freopen("CF1714E_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		if(check()){
			printf("Yes\n");
			continue;
		}
		cnt5=0;
		for(int i=1;i<=n;++i){
			if(a[i]%5==0)++cnt5;
		}
		if(cnt5==n){
			for(int i=1;i<=n;++i)a[i]+=a[i]%10;
			if(check())printf("Yes\n");
			else printf("No\n");
			continue;
		}
		if(cnt5>0){
			printf("No\n");
			continue;
		}
		for(int i=1;i<=n;++i){
			while(a[i]%10!=2)a[i]+=a[i]%10;
			a[i]%=20;
		}
		if(check())printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82204066)

By **dengziyue**

---

## 作者：sixrc (赞：0)

可以手玩这样一个数据：$12$ 能到达的数字有 $12,14,18,26,32,34,38,46,...$。同样的，我们可以发现对于所有末尾不为 $5,0$ 的数，能到达的数包含且仅包含它本身，以及一些含有其他性质的末尾为 $2,4,6,8$ 的数。

---

考虑正解。

Step 1：特判掉个位为 $5,0$ 以及所有数都相等的情况。

step 2：否则，考虑个位和十位的奇偶性：

- 个位为 $1,2,4,8$，则能到达的数为与其十位奇偶性相同的、个位为 $2,4,8$ 的数以及与其十位奇偶性不相同的、个位为 $6$ 的数。

- 个位为 $3,6,7,9$，则能到达的数为与其十位奇偶性相同的、个位为 $6$ 的数以及与其十位奇偶性不相同的、个位为 $1,2,4,8$ 的数。

所以每输入一个，根据上面的结论判断即可。最后枚举个位、能到达的个位对应的十位的奇偶性即可。


### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, flag, pd, five, a[200010], s[200010][3][11];
int main(){
	scanf ("%d", &t);
	while (t --){
		flag = pd = five = 0;
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			for (int j=0; j<=1; j++){
				for (int k=0; k<=9; k++){
					s[i][j][k] = 0;
				}
			}
		}
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			if (a[i] % 5 != 0) flag = 1;
			if (a[i] % 5 == 0) five = 1;
			if ((a[i] / 10) % 2 == 0){
				if (a[i] % 10 == 1 || a[i] % 10 == 2 || a[i] % 10 == 4 || a[i] % 10 == 8){
					s[i][0][2] = 1, s[i][0][4] = 1, s[i][0][8] = 1;
					s[i][1][6] = 1;
				} 
				else{
					s[i][0][6] = 1;
					s[i][1][2] = 1, s[i][1][4] = 1, s[i][1][8] = 1;
				}
			}
			else{
				if (a[i] % 10 == 1 || a[i] % 10 == 2 || a[i] % 10 == 4 || a[i] % 10 == 8){
					s[i][1][2] = 1, s[i][1][4] = 1, s[i][1][8] = 1;
					s[i][0][6] = 1;
				} 
				else{
					s[i][1][6] = 1;
					s[i][0][2] = 1, s[i][0][4] = 1, s[i][0][8] = 1;
				}
			}
			if (i >= 2 && a[i] != a[i-1]) pd = 1;
		}
		if (!pd){
			puts ("Yes");
			continue;
		}
		if (!flag){
			int p = -1, q = -1, fin = 0;
			for (int i=1; i<=n; i++){
				if (a[i] % 10 == 5){
					if (p == -1) p = a[i];
					else if (p != a[i]) fin = 1;
					//printf ("%d\n", fin);
				}
				else{
					if (q == -1) q = a[i];
					else if (q != a[i]) fin = 1;
				}
				if (p != -1 && q != -1){
					if (q != p + 5) fin = 1;
				}
			}
			if (fin) puts ("No");
			else puts ("Yes");
			continue;
		}
		if (five){
			puts ("No");
			continue;
		}
		pd = 0;
		for (int i=2; i<=8; i+=2){
			for (int j=0; j<=1; j++){
				flag = 0;
				for (int k=1; k<=n; k++){
					if (!s[k][j][i]) flag = 1;
				}
				if (!flag) pd = 1;
			}
		}
		if (pd) puts ("Yes");
		else puts ("No");
	}
	return 0;
}
```

---

## 作者：Error_Eric (赞：0)

#### 题意

给定 $n$ 个整数 $a_1,a_2...a_n$。 每次操作可以给任意一个数加上其个位（e.g. $14 \rarr 18$ $16\rarr 22$。

试问能否通过若干次操作使得所有数相等。

多测，满足 $\sum n\leq 2 ·10^5$。

#### 解法

操作的顺序无关答案。相同的数进行一次操作不会变得无解。因此如果有解，不会因为操作变得无解。那么不妨度入之后将它们的个位数变一样。

打表

```python
for i in range(0,20):
    print(i,end=':')
    for j in range(0,15):
        i+=i%10
        print(i,end=' ')
    print("")
```

个位数无非陷入 ``0 0 0 0`` 的循环和 ``2 4 8 6`` 的循环。两个循环相互独立。

仔细观察发现后者陷入循环后每循环一次变大 $ 20 $。

因此分类讨论，对于 $5$ 和 $0$ 结尾的直接进入最终稳定状态，判断是否两两相等。对于其他结尾的数统一个位数判断对 $20$ 取模的结果是否两两相等。


#### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define il inline
#define rei register int
il const void readln(int &I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
int t,n,a[200005],ok,q;
const int biao[]={0,1,0,9,18,5,6,25,14,23};
int main(){
	readln(t);
	while(t--){
		readln(n),ok=1,q=-1;
		for(rei i=1;i<=n;i++){
			readln(a[i]),a[i]+=biao[a[i]%10];
			if(i>1)ok&=(a[i]%20==a[i-1]%20);
			if(a[i]%10==0)
				if(q!=-1 and q!=a[i])ok=0;
				else q=a[i];
		}
		puts(ok?"YES":"NO");
	}
}

```

---

## 作者：YCSluogu (赞：0)

## CF1714E 题解

### 翻译

给你一个数组 $a$，对于每一个元素 $a_{i}$，可以重复将 $a_{i}$ 加上 $a_{i} \bmod 10$。

### 思路

当时我第一眼看上去挺懵的好吧……

懵逼咋办捏 ~~打表~~ 找规律呗……

当时我写了一个这样简短的函数：

``` cpp
void print(int x) {
  int last = -1;
  for (int i = 1; i <= 10 && last != x; i++) {
    cout << x << " ";
    last = x;
    x += x % 10;
  }
  cout << endl;
}
```

``` cpp
print(10);
print(11);
print(12);
print(13);
print(14);
print(15);
print(16);
```

然后得到了一堆奇妙的数字：

```
10
11 12 14 18 26 32 34 38 46 52
12 14 18 26 32 34 38 46 52 54
13 16 22 24 28 36 42 44 48 56
14 18 26 32 34 38 46 52 54 58
15 20
16 22 24 28 36 42 44 48 56 62
```

会发现，除了 `0` 或者 `5` 之外，所有的个位数字都是按照 `2 4 8 6` 如此四位一循环。对比以后，会发现 `22` 和 `32` 是无法通过操作相等的。但是 `22` 与 `42`、`32` 与 `52` 等，都是可以通过操作相等的。

啧……那么通过这样的找规律，会发现 `0` 和 `5` 需要特殊考虑外，当个位都一致时，可以通过十位的奇偶性来进行分类，而同一类里的数字一定是可以通过转换获得的。

所以我们只需要将每一个数字转换成个位一致，然后对比十位奇偶性就好。其结论也是比较好证明的。可以知道，当个位一致时，重复执行操作直到个位仍然为这个数，其值刚好增长 20，例如 `2`，会先后经过 `4` `8` `16` `22`。由于十位的增长为偶数，所以其奇偶性一定不变。

当然，如果个位为 `0` 那么数字的值都要一样。因为 `0` 结尾的数字无法再增长。

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6;

int t, n;
int a[kMaxN];

int change(int x) {
  while (x % 10 != 2 && x % 10 != 0) { x += x % 10; }
  return x;
}

int kind(int x) {
  if (x % 10 == 0) return 0;
  return (x / 10) % 2 + 1;
}

// 2 4 8 16 22

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] = change(a[i]);
  }
  for (int i = 1; i < n; i++) {
    if (kind(a[i]) != kind(a[i + 1])) {
      cout << "No" << endl;
      return;
    }
    if (kind(a[i]) == 0 && a[i] != a[i + 1]) {
      cout << "No" << endl;
      return;
    }
  }
  cout << "Yes" << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```


---

## 作者：封禁用户 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1714E)
# FWT__FFT 开讲啦！
先看一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9bexyw0v.png)

首先我们可以发现，$0$ 和 $5$ 这两个数是与其他数没有联系的，所以其他任何数是变换不到 $5$ 或 $0$ 的，所以一个序列中如果既存在 $5$ 的倍数也存在不是 $5$ 的倍数的数，则序列一定是不合法的。

其次我们发现，$2,4,6,8$ 这四个数构成了一个环，而 $1,3,7,9$ 经过变换都会连到这个环上，于是我们可以把它的末尾数字全部变换成 $2$，这样经过 $2 \to 4 \to 8 \to 6 \to 2$ 共 $5$ 次变换后，原数就会加上 $20$，所以最后还需对 $20$ 取模。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开 long long 见祖宗
const int N=2e5+100;
int n,a[N];
void change(int &x){//转换成2
	while(x%10!=2&&x%10!=0){
		x+=x%10;
	}
}
int T;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(a[i]%5==0){
				cnt++;
			}
		}
		if(cnt>=1&&cnt<=n-1){//判断是否是5的倍数
			cout<<"NO"<<endl;
			goto end;
		}
		for(int i=1;i<=n;i++)change(a[i]);//转换
		if(cnt==0){
			for(int i=1;i<=n;i++){
				a[i]%=20;//对20取模
			}
		}
		for(int i=2;i<=n;i++){
			if(a[i]!=a[i-1]){//如果不相等，则不合法
				cout<<"NO"<<endl;
				goto end;
			}
		}
		cout<<"YES"<<endl;//合法
		end:;//这是一个简单的写法，就是当不合法时直接跳转到这里，避免不必要的判断(比如立flag)
	}
	return 0;
}
```


---

## 作者：fast_photon (赞：0)

**0. 前言**  
模数有关 CF 题，周期以及剩余系。  

**1. 怎么想**  
首先，一直进行操作判断肯定不现实，我们需要给每个数进行一定的操作看看规律。（这里只考虑对 $10$ 取余的结果）  
$1\to2\to4\to8\to6\to2\to\dots$  
$2\to\dots$  
$3\to6\to2\to\dots$  
$4\to8\to6\to2\to\dots$  
$5\to0\to0\to\dots$  
$6\to2\to\dots$  
$7\to4\to8\to6\to2\to\dots$  
$8\to6\to2\to\dots$  
$9\to8\to6\to2\to\dots$  
$0\to0\to\dots$  
不难发现，它存在一个周期 $2\to4\to8\to6$ 和无数个终止点 $10k$。到达终止点以后数就不变了。  
但是，奇数不在周期内，所以读入进来对每个数操作一次。  
所以，我们只需要操作后给周期内的数赋值 $-1$，然后判断是否都一样就做完了...吗？  
这样写出来代码，连样例都过不了。  
为什么？  
周期是 $2\to4\to8\to16\to22$，没有出现 $12$！  
也就是说，实际上存在两个周期：$2\to4\to8\to16\to22$ 这样的和 $12\to14\to18\to26\to32$ 这样的。判断在某一个周期只需要用**除以 $10$ 向下取整的结果是否为奇数**异或**各位是否为6**。如果是奇数且个位为6，或者是偶数且个位不为6，那么属于第一类。反之，属于第二类。我们只需要给它们分别赋值 $-1$ 和 $-2$ 就可以了。  

**2. 代码**  
```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define maxn 200005

using namespace std;

int t, n, a[maxn];

signed main() {
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			a[i] += a[i] % 10;
        		if(a[i] % 10 == 0) continue;
			if((a[i] % 10 != 6) ^ ((a[i] / 10) % 2 == 1)) {
				a[i] = -1;
			}
			else a[i] = -2;
		}
		sort(a, a + n);
		if(unique(a, a + n) - a != 1) {//我这里用sort-unique的方式判断所有数是否都一样，也可以用其它的办法
			cout << "NO\n";
		}
		else cout << "YES\n";
	}
}
```

---

## 作者：Composite_Function (赞：0)

# 思路

我们轻松可以看出，本题肯定不是通过枚举的方式来做。由于对于每个数可以进行无限次操作，于是可以考虑数学思想。

首先，可以一开始先判断。如果一开始就相同，那么就并不需要继续操作了，直接输出 $\texttt{YES}$。

接下来可以看到，每次操作后的数均为偶数（见①）。所以如果一开始不都相等，那么只能对于每个奇数，对其进行一次操作。如果操作完之后，所有数相等了，那么成立，输出 $\texttt{YES}$。

然后，如果有数的末尾为 $0$，那么由于对它进行操作不会改变它的值，所以不行，输出 $\texttt{NO}$。

如果以上几种情况都并不满足，则看看能否通过操作变相同。会发现，除了末尾为 $0$ 的数，对于每 $4$ 次操作，该数就会 $+20$（见②）。于是，只要看这些数的前 $4$ 次操作 $\div 20$ 所得的余数。如果所有数的余数都能取到一个一样的值，那么就是可以的。否则不行。

# 证明

## 证明 --- ①

$\forall$ 正整数 $x$，因为 $x \equiv x$ 的个位 $ (\mod 2)$，所以每次操作后的数为偶数。

## 证明 --- ②

$\forall$ 正整数 $x$，有：

若 $x$ 的个位为 $0$，$x$ 的值无法改变。

若 $x$ 的个位为 $2$，$x \rightarrow x + 2 \rightarrow x + 4 \rightarrow x + 12 \rightarrow x + 20$。


若 $x$ 的个位为 $4$，$x \rightarrow x + 4 \rightarrow x + 12 \rightarrow x + 18 \rightarrow x + 20$。


若 $x$ 的个位为 $6$，$x \rightarrow x + 6 \rightarrow x + 8 \rightarrow x + 12 \rightarrow x + 20$。


若 $x$ 的个位为 $8$，$x \rightarrow x + 8 \rightarrow x + 14 \rightarrow x + 16 \rightarrow x + 20$。

而 $x$ 的个位与 $x + 20$ 的个位相同，所以该情况可循环。

# 代码

```
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 2e5 + 10;
int t, n, a[N];
signed main()
{
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		// 输入 n 以及 ai 
		bool flag1 = true;
		for (int i = 1; i < n; ++i)
			if (a[i] != a[i + 1])
				flag1 = false;
		if (flag1) {
			cout << "YES" << endl;
			continue;
		}
		// 如果一开始就全部相等，则直接输出 YES  
		for (int i = 1; i <= n; ++i)
			if (a[i] % 2 == 1)
				a[i] += a[i] % 10;
		bool flag2 = true, flag3 = false;
		for (int i = 1; i < n; ++i) {
			if (a[i] != a[i + 1])
				flag2 = false;
		}
		for (int i = 1; i <= n; ++i)
			if (a[i] % 10 == 0)
				flag3 = true;
		if (flag2) {
			cout << "YES" << endl;
			continue;
		}
		else if(flag3) {
			cout << "NO" << endl;
			continue;
		}
		// 特判做一次操作后是否相等以及是否有整 10 数 
		int flag[100];
		for (int i = 0; i < 20; ++i)
			flag[i] = true;
		for (int i = 1; i <= n; ++i) {
			int x = a[i] % 20;
			a[i] += a[i] % 10;
			int y = a[i] % 20;
			a[i] += a[i] % 10;
			int z = a[i] % 20;
			a[i] += a[i] % 10;
			int w = a[i] % 20;
			for (int j = 0; j < 20; ++j) {
				if (j != x && j != y && j != z && j != w)
					flag[j] = false;
			}
		}
		// 所有非整 10 的偶数数都可以通过 4 此操作 +20
		// 则直接算 %20 的余数即可 
		int flag5 = false;
		for (int i = 0; i < 20; ++i)
			if (flag[i] == true)
				flag5 = true;
		cout << (flag5?"YES":"NO") << endl;
	}
	return 0;
}
```

---

## 作者：linyihdfj (赞：0)

## E.Add Modulo 10
### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/E)
### 题目分析：
我们通过打表可以发现，数可以分为两类：

- 以 $0$ 或 $5$ 结尾的数
- 以其他数结尾的数

因为这两类数内部可以相互转化，但是不能跨类别转化，所以当同时存在两类数就判负。

考虑以 $0$ 或 $5$ 结尾的数：显然只有以 $5$ 结尾的数的改变有意义，而且只可以改变一次，所以就对这些数全部更改一次，然后判断整个序列是否相等就好了。

考虑另一类数：我们发现他们的结尾数字是有规律的 $2 - 4 - 8 - 6$。而且我们也会发现一个事实，当两个数仅最后一位不一样时，这两个数无论如何变化都不能相等。

所以这也就启发我们：他们最后变成的相等的数一定是最大值，并且时最大值将最后一位变成 $2 - 4 - 8 - 6$ 中的某一个。

那么就每个数判一下能不能变成最大值就好了。 
### 代码详解：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5+5;
int fx[10] = {2,4,6,8};
int a[MAXN];
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n;
		scanf("%lld",&n);
		int mx = 0; 
		bool flag_1 = false,flag_5 = false;
		for(int i=1; i<=n; i++){
			scanf("%lld",&a[i]);
			int h = a[i] % 10;  
			if(h == 5 || h == 0)	flag_5 = true;
			else{
				if(h != 2 && h != 4 && h != 8 && h != 6)  //把这些数都变成 2 - 4 - 8 - 6 结尾的数 
					a[i] += h;
				flag_1 = true;
			}
			mx = max(mx,a[i]);
		}
		if(flag_5 && flag_1){
			printf("NO\n");
			continue;
		}
		else if(flag_5){  //只有 0,5 结尾的数，直接暴力改 
			bool flag = false;
			for(int i=1; i<=n; i++){
				a[i] += (a[i] % 10);
			}
			for(int i=2; i<=n; i++){
				if(a[i] != a[1]){
					flag = true;
					break;
				}
			}
			if(!flag)	printf("YES\n");
			else	printf("NO\n");
			continue;
		}
		bool flag = false;
		for(int i=1; i<=n; i++){
			if(a[i] < mx){  //判断 a[i] 是否可以变成 mx 
				int pos = (a[i] % 10) / 2 - 1;   //将最后一位变成 2 
				while(pos != 1 && a[i] < mx){
					a[i] += (a[i] % 10);
					pos = (pos + 1) % 4;
				}
				if(a[i] > mx){
					printf("NO\n");
					flag = true;
					break;
				}
				a[i] = a[i] + (mx - a[i])/20 * 20;  //变一轮是加 20，所以直接变 
				pos = (a[i] % 10) / 2 - 1;   //让 a[i] 尽可能变大，使得它不超过 mx 
				while(a[i] < mx){
					a[i] += (a[i] % 10);
					pos = (pos + 1) % 4;
				}
				if(a[i] > mx){
					printf("NO\n");
					flag = true;
					break;
				}
			}
		}
		if(!flag)
			printf("YES\n");
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
给你一个 $n$ 个数的数列，每一次可以进行一个数进行如下操作：把这个数加上它的个位数字。

问你能否经过若干次操作使所有数都相等。

## 思路
考虑该操作的性质。注意到我们有两种循环。

$$2,4,8,16,22,24,28,36,42,44,48,56,\dots$$

$$12,14,18,26,32,34,38,46,52,54,58,66,\dots$$

我们不妨称第一种为偶循环，第二种为奇循环。

接下来，分别讨论 $10$ 至 $19$ 的情况。

$10,10$ 无循环。$11,12$ 奇循环。$12$ 奇循环。

$13,16,22$ 偶循环。$14,18,26,32$ 奇循环。$15,30$ 无循环。

$16,22$ 偶循环。$17,24,28,36,42$ 偶循环。

$18,26,32$ 奇循环。$19,28,36,42$ 偶循环。

所以末尾为 $1,2,4,8$ 会进入奇循环，末尾为 $3,6,7,9$ 会进入偶循环，末尾为 $0,5$ 不会进入循环。

可以推出，设当前数为 $m$，若 $m$ 的十位是奇数，则在 $2,4,6,8$ 进入奇循环，在 $3,6,7,9$ 进入偶循环，当其十位是偶数时则恰好相反。

我们只需计算出每个数会进入奇循环还是偶循环，若最后都相同则一定可以，否则就不行。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,a[200005],cnt;
int flag,aflag,ab;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    ab=1;
    flag=0;
    rep(i,1,n){
      cin>>a[i];
      if(a[i]%10==1 || a[i]%10==2 || a[i]%10==4 || a[i]%10==8){
        aflag=(a[i]/10)%2;
      }
      else if(a[i]%10==3 || a[i]%10==6 || a[i]%10==7 || a[i]%10==9){
        aflag=1-(a[i]/10)%2;
      }
      else aflag=5+a[i]+a[i]%10;
      if(i==1)flag=aflag;
      if(aflag!=flag)ab=0;
    }
    if(ab)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
  return 0;
}
```

---

