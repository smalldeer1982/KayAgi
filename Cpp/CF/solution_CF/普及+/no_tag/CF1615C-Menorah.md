# Menorah

## 题目描述

There are $ n $ candles on a Hanukkah menorah, and some of its candles are initially lit. We can describe which candles are lit with a binary string $ s $ , where the $ i $ -th candle is lit if and only if $ s_i=1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615C/23095c0b536d5c6c64ebf4ef5c8e358f51d36118.png)Initially, the candle lights are described by a string $ a $ . In an operation, you select a candle that is currently lit. By doing so, the candle you selected will remain lit, and every other candle will change (if it was lit, it will become unlit and if it was unlit, it will become lit).

You would like to make the candles look the same as string $ b $ . Your task is to determine if it is possible, and if it is, find the minimum number of operations required.

## 说明/提示

In the first test case, the two strings are already equal, so we don't have to perform any operations.

In the second test case, we can perform a single operation selecting the second candle to transform $ 01 $ into $ 11 $ .

In the third test case, it's impossible to perform any operations because there are no lit candles to select.

In the fourth test case, we can perform the following operations to transform $ a $ into $ b $ :

1. Select the $ 7 $ -th candle: $ 100010{\color{red}1}11\to 011101{\color{red} 1}00 $ .
2. Select the $ 2 $ -nd candle: $ 0{\color{red} 1}1101100\to 1{\color{red} 1}0010011 $ .
3. Select the $ 1 $ -st candle: $ {\color{red}1}10010011\to {\color{red}1}01101100 $ .

In the fifth test case, we can perform the following operations to transform $ a $ into $ b $ :

1. Select the $ 6 $ -th candle: $ 00101{\color{red}1}011\to 11010{\color{red}1}100 $
2. Select the $ 2 $ -nd candle: $ 1{\color{red}1}0101100\to 0{\color{red}1}1010011 $
3. Select the $ 8 $ -th candle: $ 0110100{\color{red}1}1\to 1001011{\color{red}1}0 $
4. Select the $ 7 $ -th candle: $ 100101{\color{red}1}10\to 011010{\color{red}1}01 $

## 样例 #1

### 输入

```
5
5
11010
11010
2
01
11
3
000
101
9
100010111
101101100
9
001011011
011010101```

### 输出

```
0
1
-1
3
4```

# 题解

## 作者：LCat90 (赞：13)

对于这个题目，你需要理解这样一个点：**如果我们在同一个位置操作两次，那么就相当于没有进行操作。如果在不同的两个位置 $i$ 和 $j$ 分别进行一次操作，那么，就相当于这两个位置的字符串进行互换且其余位置的字符串不变。**

因此，我们首先看 $a$ 串和 $b$ 串中 ``0`` 和 ``1`` 的数量是否相等，如果相等，我们就可以通过交换的方式得到最终的一个答案。

如果 ``0`` 和 ``1`` 的数量不相等，那么，我们就找到 $a$ 串和 $b$ 串中同一个数值为 ``1``的位置，对它进行操作，然后再进行和上面同样的操作。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int Maxn = 1e5 + 5;
int t, n;
char a[Maxn], b[Maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		int s = 0, s1 = 0, s2 = 0;
		scanf("%d", &n);
		scanf("%s %s", a + 1, b + 1);
		for(int i = 1;i <= n; ++i) {
			s += a[i] != b[i];
			if(a[i] == '1') s1 ++;
			if(b[i] == '1') s2 ++; 
		}
		int ans = 0x3f3f3f3f;
		if(s1 == s2) ans = s;
		if(n - s1 == s2 - 1) ans = min(ans, n - s);
		printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
	}
	return 0;
}
```


---

## 作者：gyh20 (赞：7)

可以发现，我们最终的答案和翻的次数的奇偶性是非常相关的。假如说是偶数次翻转，那么可以看成每一次都是单点操作。但是，题目中还有一个限制：每次只能翻一个 $\text{1}$，使得题目变得更加复杂。

但我们发现连续的两次操作还是有性质。第二次操作进行的位置一定在第一次操作前是一个 $0$，两次操作后只有这两个位置发生变化。

相当于，连续的两次操作必定会交换一个 $0$ 和一个 $1$。

用 "上"，"下" 分别指代两个字符串。

假如说最后进行了偶数次操作，那相当于交换了一些 $01$ 对，相当于上 $0$ 下 $1$ 和下 $0$ 上 $1$ 的个数要相等。

假如是奇数，那么最后一次操作前一定剩一个上下均为 $1$ 的位置，其他位置上下均不相等，这要求初始上下均为 $1$ 的位置比上下均为 $0$ 的位置多一个。

代码：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int t,n,m,ans,A,B,C,D;
char a[1000002],b[1000002];
inline int calc(re int x,re int y){
	return x/(y<<1)*y+max(0,x%(y<<1)-y+1);
}
int main(){
	t=read();
	while(t--){
		n=read(),scanf("%s%s",a+1,b+1);
		A=B=C=D=0;
		for(re int i=1;i<=n;++i){
			A+=(a[i]=='0')&&(b[i]=='0');
			B+=(a[i]=='0')&&(b[i]=='1');
			C+=(a[i]=='1')&&(b[i]=='0');
			D+=(a[i]=='1')&&(b[i]=='1');
		}
		ans=1e9;
		if(B==C)ans=min(ans,B+C);
		if(D==A+1)ans=min(ans,A+D);
		if(ans==1000000000)puts("-1");
		else printf("%d\n",ans);
		
	}
}

```


---

## 作者：小薛小薛 (赞：4)

## 题意
用两个01序列代表一串蜡烛的的亮灭情况.每次可以选择一个亮着的蜡烛,保持它的状态,对其他位置进行取反,问第一个序列变为第二个序列的最小步数.
## 题解

**个人：**
首先考虑进行偶数次操作序列1能变成序列2，如果对于同一个蜡烛操作两次，序列将不会变化，如果选择不同的蜡烛操作两次，可以知道对于这两个蜡烛以外的所有蜡烛状态不变，且这两个蜡烛的状态互相调换，即原先为0变为1，原先为1变为0，即交换两个蜡烛的状态，那么现在的问题就变为，一个01序列在每次可以选择 两个数字交换能不能变成另外一个01序列，这样我们就分析出只有两个01串的0与1数目相同才可以互相转换，那么需要调换的次数就是不同的位置/2（每次将一组变为正确的位置）每次又需要2次操作即答案为不同的位置的数量。同样的对于奇数次操作可以把序列1变为序列2来说，操作一次后变成偶数次的情况，那么我们选择序列1选择任意一个1取反，要满足01的个数相同，所以原序列1的0比原序列2的1少一个，同样的，操作次数为变化后的不同位置。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{   
	int n,oa=0,ob=0,dif=0;
	cin >> n;
	string a, b;
	cin >> a >> b;
	for (int i = 0; i < n; i++)
	{
		oa += a[i] - '0', ob += b[i] - '0', dif += a[i] != b[i];//统计序列1、2的1的个数并且统计不同位置
	}
	int A = 1e9;
	if (oa == ob)A = dif;//1的个数相同自然0的个数也相同答案可以为dif
	if ((n - oa) == ob - 1)A =min(A, n - dif);//将ob操作一次，ob-1是翻转后序列b拥有1的个数 n-oa为操作序列1的个数，答案为不同的位置即为原来的n-dif，原先不同的都变相同，原先相同的都变不同
	cout << (A == 1e9 ? -1 : A )<<endl;

}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：ArrogHie (赞：4)


可以发现将 $01$ 串操作偶数次，$1$ 的个数是不变的。设将其操作一次后 $1$ 的个数为 $x$ ，再将新串操作偶数次， $1$ 的个数也一直是 $x$ 。所以每操作两次相当于只是将一个 $1$ 与 $0$ 交换位置，我们只需要分别求出操作奇数次需要的步数和操作偶数次需要的步数，取最小值即可。

---

## 作者：Hoks (赞：3)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF1615C)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf1615c)内食用更佳。

~~duel到的/kk。~~
## 思路分析
首先我想到的是暴力。对于每一个不同的 $1$ 都尝试把他转移到我们想要的位置上。这个时候只需要操作这个位置然后再操作我们想要的那个位置即可。

例如：

$10001$ 与 $10100$。

我们想要把第 $5$ 位的 $1$ 转移到第 $3$ 位上，过程为：

$10001,01111,10100$。

这时我们便发现偶数次操作可以把想要的数字转换过来。

所以如果两个数列的 $1$ 的个数相同，只要偶数次操作便可以，注意到此时的操作次数便是数字不同的个数。

对于奇数次操作，即为偶数次操作后再操作一次即可，此时前面那个数列中的 $1$ 的个数即为先前 $0$ 的个数再加 $1$。

需要注意的是，一个数列可能同时满足上面两种条件，所以要两个都判断去最小。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,s1,s2,s,ans;
string a,b;
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();s1=0,s=0,s2=0;
		cin>>a>>b;ans=0x3f3f3f3f3f3f3f3f;
		for(int i=0;i<n;i++)
		{
			s+=a[i]!=b[i];
			if(a[i]=='1') s1++;
			if(b[i]=='1') s2++;
		}
		if(s1==s2) ans=s;
		if(n-s1==s2-1) ans=min(ans,n-s);
		printf("%lld\n",ans==0x3f3f3f3f3f3f3f3f?-1:ans);
	}
	return 0;
}
```


---

## 作者：Eazin_star (赞：2)

### 思路
首先需要知道两个性质：

- 在同一个位置操作两次，相当于没有操作。

- 在两个不同位置各操作一次，那么相当于交换两个位置的数，其余位置不变。

那么这道题就很简单了，首先遍历一遍，看两组数 $0$ 和 $1$ 的数量是否相等。如果相等我们可以通过若干次交换让两个数组相等。否则我们就找到两组中同一个数值为 $1$ 的位置，对它进行操作，重复上一个操作。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
string a, b;
int main() {
	scanf("%d", &t);
	while (t--) {
		int cnt = 0, cnta = 0, cntb = 0, ans = 0x3f3f3f3f; //cnt记录两个数组不等的数量，cnta记录a中1的数量，cntb记录b中1的数量
		scanf("%d", &n);
		cin >> a >> b;
		for (int i = 0; i < n; i++) { //遍历
			if (a[i] != b[i]) cnt++;
			if (a[i] == '1') cnta++;
			if (b[i] == '1') cntb++;
		}
		if (cnta == cntb) ans = cnt; //如果数量相等，证明可以通过若干次操作使两个数组相等
		if (n-cnta == cntb-1) ans = min(ans, n-cnt); //如果先交换一次再重复操作的情况成立，取min
		if (ans == 0x3f3f3f3f) printf("-1\n"); //如果两种情况都不成立，输出-1
		else printf("%d\n", ans); //输出ans
	}	
	return 0;
} 
```



---

## 作者：清烛 (赞：2)

## Description
给定两个 01 串 $a_1$ 和 $b_i$。长度 $n\le 10^5$。问能否通过下面的操作使得 $a$ 变为 $b$：

- 选择一个 $a_i = 1$ 的 $i$，保持其不变，然后翻转剩余所有 $a_i$。

如果能，则输出最小步数。

## Solution
比较妙的题。

首先我们注意到，一次操作可以视为**改变 $a_i$，然后打上全局翻转标记**。

然后我们简化一下状态：不难发现每个 $i$ **初始**满足如下状态之一：

- $a_i = 1$ 且 $a_i = b_i$，简称 $1$ 同，满足这样的 $i$ 的个数记为 $f(1, 1)$。
- $a_i = 1$ 且 $a_i \ne b_i$，简称 $1$ 异，满足这样的 $i$ 的个数记为 $f(1, 0)$。
- $a_i = 0$ 且 $a_i = b_i$，简称 $0$ 同，满足这样的 $i$ 的个数记为 $f(0, 1)$。
- $a_i = 0$ 且 $a_i \ne b_i$，简称 $0$ 异，满足这样的 $i$ 的个数记为 $f(0, 0)$。

然后现在一个局面的状态就可以用 $f(0/1, 0/1)$ 来表示。我们考虑预处理出一开始的 $f(0/1, 0/1)$。

随后，我们注意到如果我们视为改变 $a_i$ 然后打标记的话，第一次操作肯定只能操作 $1$ 同/异，但是由于打上了全局标记，第二次操作就只能操作 $0$ 同/异了，剩下同理，所以我们的操作一定是 $10101010\cdots$ 交替进行。

操作奇数次后，会存在全局翻转标记，这意味着所有的 $0/1$ 异实际上都是同，所以我们要的最终状态是 $f(1/0, 1) = 0$。

操作偶数次后，没有全局翻转标记，这意味着所有的 $0/1$ 同实际上就是同，所以要的最终状态就是 $f(1/0, 0) = 0$。

一次对 $1$ 同的操作会使得 $1$ 同减一并且使得 $0$ 异加一，剩余情况同理。

所以，当且仅当 $f(1, 1) - f(0, 1) = 1$ 时，我们可以操作奇数次使得 $f(1/0, 1) = 0$，操作次数显然为 $f(1, 1) + f(0, 1)$。

当 $f(1, 0) = f(0, 0)$ 时，我们可以操作偶数次使得 $f(1/0, 0) = 0$，操作次数显然为 $f(1, 0) +f(0, 0)$。

于是此题就做完了，没有看懂的可以看下代码：

## Implementation
```cpp
const int maxn = 1e5 + 5;
char s1[maxn], s2[maxn];
int n;

int main() {
    int T; read(T);
    while (T--) {
        read(n), read(s1 + 1), read(s2 + 1);
        int same[2][2] = {0};
        FOR(i, 1, n)
            ++same[s1[i] - '0'][s1[i] == s2[i]];
        int ans = 1e9;
        if (same[1][1] - same[0][1] == 1) ans = same[1][1] + same[0][1];
        if (same[1][0] == same[0][0]) chkmin(ans, same[1][0] + same[0][0]);
        print(ans > n ? -1 : ans);
    }
    return output(), 0;
}
```

---

## 作者：bigclever (赞：1)

## 前置芝士：
- 如果我们在同一个位置操作两次，那么就相当于没有操作。
- 如果在不同的两个位置**分别进行一次操作**，那么就相当于这两个位置的数字进行互换且其余位置不变（可以自己手动验证一下）。

## 思路：
因为在同一个位置操作两次，那么就相当于没有操作。所以无非就只有两种情况：
1. 直接让 $a$ 变成 $b$。因为我们可以通过 $2$ 次操作使得字符串中的两个位置上的数字进行互换，所以如果 $a$ 和 $b$ 中 $0$ 和 $1$ 的数量都相等，那么必然可以通过若干次操作使得 $a=b$，此时操作次数即为 $a$ 和 $b$ 中每一位数字不同的个数（因为每 $2$ 次操作就可以让 $a$ 中 $2$ 个原本不同的数字和 $b$ 相同）。
1. 先选择一个 $a$ 和 $b$ 都为 $1$ 的位置操作一次，再让 $a$ 变成 $b$。此时我们同样判断**除了这个位置以外**的 $0$ 和 $1$ 的数量相不相等。因为你先操作了一次，所以如果相等，那么此时答案为**原来** $a$ 和 $b$ 中每一位数字**相同**的个数。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	        ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	        int t,n; cin>>t;
	        while(t--){
		        string a,b;
		        int dif=0,cnta=0,cntb=0;
		        cin>>n>>a>>b;
		        for(int i=0;i<n;i++)dif+=(a[i]!=b[i]),cnta+=(a[i]=='1'),cntb+=(b[i]=='1');
		        int ans=1e9;
		        if(cnta==cntb)ans=min(ans,dif);//如果a和b中1的个数相同，那么0的个数也肯定相同
		        if(n-cnta==cntb-1)ans=min(ans,n-dif);//n-cnta是原本a中0的个数，操作后即为a中除选择的位置以外1的个数，cntb-1即为b中除选择的位置以外1的个数
		        cout<<(ans==1e9?-1:ans)<<endl;
	        }
	        return 0;
}
```

---

## 作者：ylch (赞：1)

# [CF1615C](https://www.luogu.com.cn/problem/CF1615C) Menorah 题解

知识点：数学，找规律。

## PART1. 思路描述

首先可以推出几个结论：

1.在同一点重复操作两次，就相当于没有操作，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/53hxeudk.png)

2.在两个不同位置 $p_1$ 和 $p_2$ 各操作一次，所得结果就相当于把两个位置的数互换，如图（注意标黄部分）：

![](https://cdn.luogu.com.cn/upload/image_hosting/sqrm9kkk.png)


------------

然后举例说明，假设两个数列如下（相同数用蓝框圈出）：

![](https://cdn.luogu.com.cn/upload/image_hosting/r5twpl5c.png)

此时相同的个数为偶数，所以可以通过性质二交换出合适的结果，过程如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0ozet75a.png)


------------

再看两个数列（相同的用蓝色框圈出来）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ak4oki4e.png)

当数列相同个数为奇数时，需要先找到任意一个两串都为 $1$ 的位置进行操作，这样就可以让原来奇数个不相等的数转化成偶数个不相等的数，就可以求解了。

不懂看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9jiwwmyb.png)

## PART2. AC 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

signed main()
{
	int T , n;
	string a , b;
	for(cin >> T; T --; ){
		cin >> n >> a >> b;
		int m = 0, ans = 0x3f3f3f;
		int sum1 = count(a.begin(), a.end(), '1'); //自带conut函数
		int sum2 = count(b.begin(), b.end(), '1');
		for(int i = 0; i < n; i++){
			if(a[i] != b[i]){
				m++;
			}
		}
		if(sum1 == sum2){
			ans = min(m , ans);
		}
		//第二种情况：在a[i]!=b[i]的组里必有一个1，在a[i]==b[i]的组里a[i]为1的情况恰好多1
		if(sum1 + sum2 - 1 == n){
			ans = min(n - m , ans);
		}
		if(ans == 0x3f3f3f){
			cout << -1 << endl;
		}else{
			cout << ans << endl;
		}
	}
	return 0;
}
```

## End

管理员的大大辛苦啦~

这里是 YLCHUP，谢谢大家！

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1615C Menorah (luogu)](https://www.luogu.com.cn/problem/CF1615C)

[CF1615C Menorah (codeforces)](https://codeforces.com/problemset/problem/1615/C)

# 解题思路

这题有三个重要的性质：

1. 在同一个点做两次操作与不在这个点做操作是等价的。

2. 给两个不同的点做操作等价于交换这两个点。

3. 给一个字符串做偶数次操作，这个字符串的 $0$ 的数量和 $1$ 的数量不会改变。

知道这三个性质，这题就很好做了，直接分操作次数的奇偶性来讨论即可，详见代码。

时间复杂度 $O(n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
ll t;
/*
一个位置不会被做 2 次操作

100010111 --> 4 5 
111101000 --> 4 5
010010111 --> 4 5
101101100 --> 4 5 

100000000 --> 8 1
111111111 --> 0 9
010000000 --> 8 1
111111111 --> 0 9
*/
ll n;
string s1,s2,s3;
ll sum0,sum1,sum2,sum3,ans;
void solve()
{
	sum0=sum1=sum2=sum3=ans=0;
	ans=1e18;
	cin>>n>>s1>>s2;
	s1=' '+s1;
	s2=' '+s2;
	forl(i,1,n)
		sum0+=s1[i]=='0',sum1+=s1[i]!='0';
	forl(i,1,n)
		sum2+=s2[i]=='0',sum3+=s2[i]!='0';
	if(sum0==sum2 && sum1==0)
	{
		cout<<0<<endl;
		return ;
	}
	else if(sum1==0)
	{
		cout<<-1<<endl;
		return ;
	}
	ll ke1=sum0+1,ke0=n-ke1;
//	cout<<ke0<<' '<<ke1<<endl; 
	if(!((sum0==sum2 && sum1==sum3) || (ke0==sum2 && ke1==sum3)))
	{
		cout<<-1<<endl;
		return ;
	}
	s3=s1;
	forl(i,1,n)
	{
		if(s3[i]=='0')
			s3[i]='1';
		else
			s3[i]='0';
	}
	if(sum0==sum2 && sum1==sum3)
	{
		ll sum=0;
		forl(i,1,n)
			if(s1[i]!=s2[i])
				sum++;
		ans=min(ans,sum);
	}
	if(ke0==sum2 && ke1==sum3)
	{
		ll sum=0;
		forl(i,1,n)
			if(s3[i]!=s2[i])
				sum++;
		ans=min(ans,sum);
	}
	cout<<ans<<endl;
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1615C)
易证：

- 在一个位置操作两次等于没有操作
- 在两个不同的位置上的 $1$ 个 $1$ 和 $1$ 个 $0$ 分别进行 $1$ 次操作，会让这两个数交换位置。

所以只要 $a$ 和 $b$ 中 $1$ 的数量相同，就必然可以通过若干次操作使得 $a$ 和 $b$ 相同。（操作次数为一开始 $a$ 和 $b$ 中数字不同的个数，因为每进行两次操作就可以使 $a$ 和 $b$ 中的两个不同的数变为相同）

或者先选择一个 $a$ 和 $b$ 中都为 $1$ 的一个位置进行一次操作，如果此时 $a$ 和 $b$ 中的 $1$ 的数量相同，那也可以通过若干次操作使得 $a$ 和 $b$ 相同。（操作次数为一开始 $a$ 和 $b$ 中数字相同的个数）

除了这两种情况以外，$a$ 不可能通过若干次操作变成 $b$。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
char a[100005],b[100005];
int main(){
    scanf("%d",&t);
    while(t--){
        int n,cnt=0,ca=0,cb=0,ans=2e9;
        scanf("%d",&n);
        scanf("%s%s",a+1,b+1);
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i])cnt++;
            if(a[i]=='1')ca++;
            if(b[i]=='1')cb++;
        }
        if(ca==cb)ans=cnt;//如果a和b中的1数量相同，a和b中数字不同的个数为操作次数
        if(n-ca+1==cb)ans=min(ans,n-cnt);//如果a操作一次后1的数量和b相同，a和b中数字相同的个数为操作个数
        if(ans==2e9)printf("-1\n");//如果不是以上两种情况中的一种，则不能让a变成b
        else printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1615C](https://www.luogu.com.cn/problem/CF1615C)

# 思路

这里先写出两个性质：

$1.$ 在一个位置操作两次与没有操作是一样的。

$2.$ 在两个不同位置进行操作，相当于交换两个位置的状态，剩下位置因为经过偶数次变换，所以不变。

那么这题的思路就是统计他们 $1$ 的数量，看看他们 $1$ 的数量是否相同，如果相同那么我们统计他们相同位置不同值的个数，根据性质二可得答案就是他们不同的个数。

如果 $1$ 的个数不相同，我们继续在分类。如果他们个数相差 $\gt1$，直接输出 $-1$，因为操作一次他最多会让 $0$ 和 $1$ 的数量改变 $1$。

如果个数相差 $1$，如果相同位置不同值的个数大于极大值，就输出 $-1$。否则输出相同位置不同值的个数。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string a,b;
signed main(){
	cin>>t;
	while(t--){
		int c=0,a1=0,b1=0;
		cin>>n>>a>>b;
		for(int i=0;i<n;i++){
			c+=(a[i]!=b[i]);
			if(a[i]=='1'){
				a1++;
			}
			if(b[i]=='1'){
				b1++;
			}
		}
		int ans=0x3f3f3f3f;
		if(a1==b1){
			ans=c;
		}
		if(n-a1==b1-1){
			ans=min(ans,n-c);
		}
		cout<<(ans==0x3f3f3f3f?-1:ans)<<endl;
	}
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/140633318)

---

## 作者：Spir1t (赞：0)

仔细读题后我们可以知道：如果我们在同一个位置 $i$ 操作两次，那么就等于没有进行操作，如果在不同的两个位置分别进行一次操作，就是说除去一个位置的 $1$ 或 $0$ 互换，其余位置的变过去再变回来，换言之，就是这两个位置的字符串进行互换且其余位置的字符串不变。

发现这个规律后，题就好做了，统计一下 $01$ 数量，看相等情况，分支判断即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;
using ull = unsigned long long;
int kmp(int n, char* a, char* b) {
	int s = 0, s1 = 0, s2 = 0;
	for(int i = 1; i <= n; ++i) {
		s += a[i] != b[i];
		if(a[i] == '1') s1++;
		if(b[i] == '1') s2++;
	}
	int ans = 114514;
	if(s1 == s2) ans = s;
	if(n - s1 == s2 - 1) ans = min(ans, n - s);
	return ans == 114514 ? -1 : ans;
}
int main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		char a[n+1], b[n+1];
		scanf("%s %s", a + 1, b + 1);
		int ans = kmp(n, a, b);
		printf("%d\n", ans);
	}
	return 0;
}



```


---

## 作者：ryl_ahu (赞：0)

首先我们需要知道：

- 前后两次操作会有关联。
- 设第一次操作选择的位置为 $i$，第二次操作选择一个第一次操作前是 $0$ 的位置 $j$，那么两次操作完以后就相当于交换了 $i$ 和 $j$ 位置上的值。

举个例子：

有一个字符串 $s$ 为 ```10010```，第一次操作选择 $s_0$（字符串下标从 $0$ 开始），操作完后变成 ```11101```，第二次操作选择 $s_2$，操作完后变成 ```00110```。可以看到两次操作以后 $s_0$ 与 $s_2$ 的值互换了。

定义 $x$ 为 $a_i=1,b_i=0$ 中 $i$ 可能的值的个数，$y$ 为 $a_j=0,b_j=1$ 中 $j$ 可能的值的个数。当 $x$ 与 $y$ 相等时，一定能操作 $x+y$ 次将 $a$ 串变为 $b$ 串。

除了 $x=y$ 的时候，还有别的情况 $a$ 一定能变成 $b$ 吗？

有的。

定义 $m$ 为 $a_i=1,b_i=1$ 中 $i$ 可能的值的个数，$n$ 为 $a_j=0,b_j=0$ 中 $j$ 可能的值的个数。当 $m=n+1$ 时，一定能操作 $m+n$ 次将 $a$ 串变为 $b$ 串。

其它情况都无法经过若干次操作将 $a$ 变成 $b$。

最后还需要注意两点：

- 当以上所说的两种情况都满足时，需要输出所需操作数最小的。
- 当永远无法将 $a$ 变成 $b$ 时需要输出 $-1$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t, n;
	int q, w, e, r;
	string a, b;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		q = 0;
		w = 0;
		e = 0;
		r = 0;
		cin >> n >> a >> b;
		for (int i = 0; i < n; i++) {
			if (a[i] == '1' && b[i] == '1') {
				q++;
			}
			if (a[i] == '0' && b[i] == '0') {
				w++;
			}
			if (a[i] == '0' && b[i] == '1') {
				e++;
			}
			if (a[i] == '1' && b[i] == '0') {
				r++;
			}
		}
		if (q == w + 1 && e != r) {
			cout << q + w << endl;
		}
		else if (q != w + 1 && e == r) {
			cout << e + r << endl;
		}
		else if(q == w + 1 && e == r) {
			cout << min(q + w, e + r) << endl;
		}
		else {
			cout << -1 << endl;
		}
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

我们发现，对于连续两次操作，第二次操作的位置在第一次操作是一定是 $0$，若操作同一个位置等于不操作，因此只操作不同的位置。

两次操作后只有操作的位置由 $0$ 变 $1$，相当于交换了序列中的一个 $0$ 和一个 $1$。下面分两种情况讨论：

如果 $a$ 中是 $0$，$b$ 中是 $1$ 的位置的数量与 $a$ 中是 $1$，$b$ 中是 $0$ 的位置的数量相同，即可将所有这些位置两两交换，答案即为它们的数量之和；

如果 $a$ 中是 $0$，$b$ 中是 $0$ 的位置的数量比 $a$ 中是 $1$，$b$ 中是 $1$ 的位置的数量少 $1$，则可找到那个多出来的 $1$ ，对它进行操作，之后就变回了第一种情况。

对于其他情况，无解。若两种情况都满足，取最小值即可。


## 代码

```cpp
int t;
cin>>t;
while(t--){
	int n;
	cin>>n;
	string a,b;
	cin>>a>>b;
	a='#'+a,b='#'+b;
	int sum00=0,sum10=0,sum01=0,sum11=0;
    //a0b0,a1b0,a0b1,a1b1
	for(int i=1;i<=n;i++){
		if(a[i]=='0'&&b[i]=='0') sum00++;
		if(a[i]=='1'&&b[i]=='0') sum10++;
		if(a[i]=='0'&&b[i]=='1') sum01++;
		if(a[i]=='1'&&b[i]=='1') sum11++;
	}
	int ans=0x3f3f3f3f;
	if(sum01==sum10) ans=min(ans,sum01+sum10);
	if(sum11==sum00+1) ans=min(ans,sum11+sum00);
	cout<<(ans==0x3f3f3f3f?-1:ans)<<'\n';
}
```

---

