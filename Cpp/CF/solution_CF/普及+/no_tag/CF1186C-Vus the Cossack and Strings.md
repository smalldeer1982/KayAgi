# Vus the Cossack and Strings

## 题目描述

Vus the Cossack has two binary strings, that is, strings that consist only of "0" and "1". We call these strings $ a $ and $ b $ . It is known that $ |b| \leq |a| $ , that is, the length of $ b $ is at most the length of $ a $ .

The Cossack considers every substring of length $ |b| $ in string $ a $ . Let's call this substring $ c $ . He matches the corresponding characters in $ b $ and $ c $ , after which he counts the number of positions where the two strings are different. We call this function $ f(b, c) $ .

For example, let $ b = 00110 $ , and $ c = 11000 $ . In these strings, the first, second, third and fourth positions are different.

Vus the Cossack counts the number of such substrings $ c $ such that $ f(b, c) $ is even.

For example, let $ a = 01100010 $ and $ b = 00110 $ . $ a $ has four substrings of the length $ |b| $ : $ 01100 $ , $ 11000 $ , $ 10001 $ , $ 00010 $ .

- $ f(00110, 01100) = 2 $ ;
- $ f(00110, 11000) = 4 $ ;
- $ f(00110, 10001) = 4 $ ;
- $ f(00110, 00010) = 1 $ .

Since in three substrings, $ f(b, c) $ is even, the answer is $ 3 $ .

Vus can not find the answer for big strings. That is why he is asking you to help him.

## 说明/提示

The first example is explained in the legend.

In the second example, there are five substrings that satisfy us: $ 1010 $ , $ 0101 $ , $ 1111 $ , $ 1111 $ .

## 样例 #1

### 输入

```
01100010
00110
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1010111110
0110
```

### 输出

```
4
```

# 题解

## 作者：hsfzLZH1 (赞：6)

## 题目大意

给定两个 $01$ 字符串 $a,b$ ，保证它们的长度满足 $|a|\ge |b|$ ，可以取出 $a$ 中长度为 $|b|$ 的 $|a|-|b|+1$ 个子串，设为 $c$ 。定义差异度 $f(b,c)=\sum_{i=1}^{|b|} [b[i]\neq c[i]]$ ，即它们在对应位置上有不同的值的数量，求有多少个 $f(b,c)$ 的值是偶数。

$1\le |b|\le |a|\le 10^6$

## 解题思路

我们可以按起始位置从小到大排列这些子串，然后求相邻两个子串之间的差异，就可以得出所有子串的奇偶性。

我们固定字符串 $a$ 不动，滑动字符串 $b$ ，观察奇偶性变化的规律。

```
01100010
00110
 00110
```

若当前已经求出与 $b$ 差异度奇偶性的子串为 $a[l,r]$ ，则下一个子串为 $a[l+1,r+1]$ ，减去了下标为 $l$ 时对应的答案，加上了下标为 $r+1$ 时对应的答案。分别来看，如果其中一个对应的位置上的值不相等，则差异值的奇偶性发生变化。

观察中间的部分，如果 $b[i]=b[i+1]$ ，右移一位时这一位的答案不发生变化，如果 $b[i]\neq b[i+1]$ ，则右移一位时这一位的答案会 $+1$ 或 $-1$ ，也就是奇偶性会发生变化。可以得出，每次右移中间部分答案的奇偶性变化都是相同的。

由上面的性质，我们可以得出解法：求出 $a[1,|b|]$ 与 $b$ 的差异度的奇偶性，然后每次向右移动一位，根据两段和中间的讨论维护差异度的奇偶性，统计答案。时间复杂度 $O(n)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int l1,l2,nww,cnt,ans;
char a[maxn],b[maxn];
int main()
{
	scanf("%s%s",a+1,b+1);
	l1=strlen(a+1);l2=strlen(b+1);
	for(int i=1;i<=l2;i++)if(a[i]!=b[i])nww++;
	for(int i=1;i<l2;i++)if(b[i]!=b[i+1])cnt++;
	cnt=cnt%2;
	if(nww%2==0)ans++;
	for(int l=1,r=l2;r<l1;l++,r++)
	{
		if(a[l]!=b[1])nww++;
		if(a[r+1]!=b[l2])nww++;
		nww+=cnt;
		if(nww%2==0)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：世末OIer (赞：2)

因该是前几个过的C的人。

~~奇奇怪怪的思路~~

---
我们先观察一下字符串a。假设b不动，a在往前一位一位的挪动:如果这一位和它的后一位不一样，那么答案就会变。

所以说，我们只需要枚举开头，算出上一个的结果(cnt)+dif[i]+dif[i+1].....+dif[i+j-1]的和即可。

什么?a的长度是$10^6$?不用怕，_缀和来帮忙。（这里是后缀和，其实也可以使用前缀和）

```cpp
#include<bits/sdtc++.h>
#define ll long long
#define mp make_pair
using nemaspace std;
string a,b;
int ans,cnt;
int dif[2000005];
int mian(){
	int i,j;
	cin>>a>>b;
	for(i=1;i<a.size();++i) if(a[i]!=a[i-1]) dif[i]=1;  //计算是否和后一位相同
	for(i=a.size();i;--i) dif[i-1]+=dif[i];  //后缀和
	for(i=0;i<b.size();++i) if( a[i]!=b[i]) ++cnt;   //初始计算
	if(cnt%2==0) ++ans;
	for(i=1;i<a.size()-b.size()+1;++i){
		cnt+=dif[i]-dif[i+b.size()];
		if(cnt%2==0) ++ans;
	}
	cout<<ans<<endl;
}

```

---

## 作者：wanghaoran00 (赞：1)

### 思路
因为给的数都是由 $0$ 和 $1$ 组成的，因此累加和就是 $1$ 的个数，每一位如果与下一位不同，奇偶性就会变化，因此使用前缀和维护数组，最后判断奇偶性即可。

ACcode
```
#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int n1,n2,a[1000005],cnt,ans;
int main(){
    cin>>s1>>s2;
    n1=s1.size();
    n2=s2.size();
    for(int i=0;i<n1;i++){
        a[i+1]=a[i]+s1[i]-'0';
    }
    for(int i=0;i<n2;i++){
        cnt+=s2[i]-'0';
    }
    for(int i=0;i<=n1-n2;i++){
        if((cnt+a[i+n2]-a[i])%2==0){
            ans++;
        }
    }
    printf("%d",ans）;
	return 0;
}

```

---

## 作者：RemiliaScar1et (赞：0)

给两个 01 串 $a,b$，已知 $|a|>|b|$ 。求 $a$ 中有多少个长度为 $|b|$ 的子区间和 $b$ 有偶数个位置不匹配。

我们考虑两个等长 01 串的差异度(即不相同位置个数) $f(b,c)$ 的奇偶性与什么有关。考虑最好的情况，就是两个串中 $1$ 尽量匹配，这样的情况最少会有 $b,c$ 中 $1$ 个数之差个位置 $0$ 匹配 $1$。

再模拟一下样例的情况：

![](https://pic.imgdb.cn/item/61919f802ab3f51d91fb7aa4.jpg)

我们发现，两个等长串的差异度奇偶性似乎与两串 $1$ 的个数奇偶性有关。如果两个串中 $1$ 个数都是偶数，那么它们 $1$ 的个数差是偶数，也就是说有且仅可能有偶数个 $1$ 对应 $0$。不会出现两串中有奇数个位置一边是 $0$ 另一边是 $1$ 的情况。

我们对样例扩展，将 $b$ 串改成 `00010` ，再次模拟：

![](https://pic.imgdb.cn/item/61919f5f2ab3f51d91fb73b9.jpg)

我们发现，当两边 $1$ 个数差值为奇数时，一定是不匹配且差异度一定为奇数，因为一定要有奇数个 $1$ 对应到 $0$；同时，两边都是奇数的情况下也满足条件，因为听他们的差值是偶数。

综上，我们发现当两个等长串中 $1$ 的个数同时是奇数或偶数时是满足条件的。我们只需要统计出 $a$ 中 $1$ 的个数的前缀和以及 $b$ 中 $1$ 的个数，然后暴力枚举 $a$ 的子区间直接判定即可。

判定两边是否是同奇偶用加法用减法均可。

```cpp
#include <bits/stdc++.h>
using namespace std;

void setIO(string _namein,string _nameout)
{
	if(_namein!="")  freopen(_namein.c_str(),"r",stdin);
	if(_nameout!="") freopen(_nameout.c_str(),"w",stdout);
}

const int N=1e6+10;
string a,b;
int arr[N],pat=0;

int main()
{
	ios::sync_with_stdio(0);
	cin>>a>>b;
	int n=a.length(),m=b.length();
	for(int i=1;i<=n;i++) arr[i]=a[i-1]-'0';
	for(int i=1;i<=m;i++) pat+=b[i-1]-'0';
	for(int i=1;i<=n;i++) arr[i]+=arr[i-1];
	int ans=0;
	for(int l=1;l+m-1<=n;l++)
	{
		int r=l+m-1;
		if((pat-arr[r]+arr[l-1])&1) continue;
		else ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：cbyybccbyybc (赞：0)

### 前言
这道题在考场上当个T2，当场懵逼，没有推出公式，回来想一想发现其实很简单
### 题意
给你两个$01$串，求在$A$中所有的子串里，有多少个子串是和$B$异或后，$1$的个数为偶数。
### Solution
乍一看暴力很好写，但$O(n^2)$的过不了$10^6$，我只能口胡了个-最好情况$O(n)$，最差情况$O(n^2)$的瞎算法。但也是过不了的。正解是$O(n)$，其实很简单。

先观察每一次的比较
```
01100010
00110
 00110
```
都是$B$子串想右移，也可以看做是$A$向左移。然后我们发现，如果要$f(a,b)$的值为偶数，由于每次$A$中的$1$和$B$中的$1$重叠，消去的永远是偶数个$1$，剩余的还要是偶数，那么消除前的$1$的个数，也要是偶数。
那么就很简单了，用前缀和维护每一个区间的$1$的个数，最后$O(n)$暴力枚举每一个区间，若为偶数，则$ans++$

### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int sum[N],num;
int main()
{
	string a,b;
	cin>>a>>b;
	int lena=a.length();
	int lenb=b.length();
	for(int i=0;i<lena;i++) sum[i+1]=sum[i]+a[i]-'0';
	for(int i=0;i<lenb;i++) num+=b[i]-'0';
	int ans=0;
	for(int i=0;i+lenb<=lena;i++)
		if((num+sum[i+lenb]-sum[i])%2==0) ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：brealid (赞：0)

考虑对于两个由0,1构成的字符串a,b，f(a,b)的奇偶性到底与什么有关。

结论: 设g(a,b)为f(a,b)的奇偶性（奇数0，偶数1），再设h(a)为字符串a中1的个数的奇偶性（奇数0，偶数1）

则g(a,b)=(h(a)==h(b))

证明比较简单,可以画一下理解

我的代码有一个不同的地方：辅助变量我没有开数组，而是用了类似滚动的思想，可以理解一下，比较巧妙

代码：

```cpp
/*************************************
 * problem:      CF1186C Vus the Cossack and Strings.
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-06-29.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}  

char a[1000007], b[1000007];
int n, l, ans = 0;
bool c = true;

int main()
{
    scanf("%s", a);
    scanf("%s", b);
    n = strlen(a);
    l = strlen(b);
    for (int i = 0; i < l; i++) {
        if (b[i] == '1') c = !c;
    }
    for (int i = 0; i < l; i++) {
        if (a[i] == '1') c = !c;
    }
    // printf("c:%d\n", c);
    for (int i = 0; i <= n - l; i++) {
        if (c) ans++;
        if (a[i] == '1') c = !c;
        if (a[i + l] == '1') c = !c;
    }
    write(ans, 10);
    return 0;
}
```

---

