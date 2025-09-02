# Minimum number of steps

## 题目描述

题面：

你有一串字符串,仅由a,b组成,一次操作为"ab"->"bba",求使原串中没有a在b前面的操作次数.

## 说明/提示

l:[1,1e6]
注意：

None.
翻译贡献者：尘染梦

## 样例 #1

### 输入

```
ab
```

### 输出

```
1
```

## 样例 #2

### 输入

```
aab
```

### 输出

```
3
```

# 题解

## 作者：小闸蟹 (赞：7)

```cpp
// 多拿几个串试一遍就知道，最后状态必然形如：bbb...bbaa...a
// 我们逆序处理该字符串，如果遇到一个'a'，那么就看一下它之前有几个'b'，答案就加上几个，同时'b'的数量要翻倍
// 如果遇到一个'b'，那么'b'的数量就加一，同时答案保持不变
// 因为与'a'直接相邻的'b'的数量则是要被替换成"bba"的次数，然后每次做完这些替换之后'b'的个数会翻倍
// 最后，要注意取模
#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    constexpr int MOD = 1000000000 + 7;

    int Ans = 0, b = 0;

    std::string Str;
    std::cin >> Str;
    for (auto Iter = Str.crbegin(); Iter != Str.crend(); ++Iter)
    {
        if (*Iter == 'a')
        {
            Ans = (Ans + b) % MOD;
            b = b * 2 % MOD;
        }
        else if (*Iter == 'b')
        {
            ++b;
        }
    }
    std::cout << Ans << std::endl;

    return 0;
}
```

---

## 作者：JWRuixi (赞：3)

原难度 $1400$，这题非常适合我 ~~，因为不算难~~。

- 题意

给定一个字符串 $s$，可以进行如下操作：

将一个串 ```ab``` 替换为一个串 ```bba```。

问至少几次操作是的没有 ```a``` 在 ```b``` 之前。

- 分析

考虑这样一个操作的实质是将 ```a``` 挪到了 ```b``` 的后面，在把 ```b``` 乘二。

那我们就可以这样考虑，从后往前扫，记录 ```b``` 的数量，即下一个 ```a``` 要翻越的数量，让后考虑遇到 ```a``` 时直接将数量计入答案，让后将 ```b``` 的数量乘一个二。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int ans, res, n;
char s[1000005];
namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline void read () {
		char c = gh();
		while ('a' <= c && c <= 'z') s[++n] = c, c = gh();
	}
	inline void write(long long x) {
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using IO::read;
using IO::write;
inline int add (int x, int y) {	return (x + y) > mod ? (x + y - mod) : (x + y); }
signed main () {
	read();
	for (int i(n); i; --i) {
		if (s[i] == 'a') ans = add(ans, res), res = add(res, res);
		else res = (++res > mod ? res - mod : res);
	}
	write(ans); 
}
```

---

## 作者：Mine_King (赞：3)

这题我们究其本质，首先可以发现，操作的顺序对结果没有影响，那么我们可以找一种处理起来最方便的处理方式。  
可以发现从后往前处理最方便。因为一次操作可以对其前面的字符产生影响，但对后面的字符是没有影响的。

于是我们从后往前扫描这个字符串。  
如果当前的字符为 `a`，那么它和它后面的字符组成的字符串一定是 `abbb...baaa...a`，也就是它后面一定是紧跟着一串 `b`（当然可以是 $0$ 个 `b`），然后又是一串 `a`（当然也可以是 $0$ 个 `a`），因为如果还有 `b` 在 `a` 前面那么还需要操作。  
然后，考虑操作的内在含义，可以发现每次操作都会让这个 `a` 后面的 `b` 的个数 $-1$，所以对于字符 `a`，让操作数加上其后 `b` 的个数。  
**同时我们也可以发现，其后 `b` 的个数其实就是当前扫到的 `b` 的个数。（当然也包括操作产生的 `b` 的个数）所以可以用一个计数器来记录当前扫到的 `b` 的个数。**  
同时，每次操作都会使 `b` 的个数 $+1$，那么做完这一整串的操作后，`b` 的总个数就应该 $\times 2$。  
那么如果当前扫到的字符是 `b` 呢？让 `b` 的个数的计数器 $+1$ 即可。  

具体实现见Code：
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
string s;
int ans,b;//b是计数器
const int mod=1e9+7;
int main()
{
	cin>>s;
	for(int i=(int)s.length()-1;i>=0;i--)
		if(s[i]=='a') ans=(ans+b)%mod,b=b*2%mod;
		else b++;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：cqbzcjh (赞：1)

观察最后满足条件的状态（如下），可以发现最后状态一定为前段是连续的 `b`，后段是连续的 `a`。
```
[样例1]     [样例2]
ab          aab
bba         bbbbaa
```
再观察 `ab` 和 `bba`，可以发现变化的实质就是**交换 `a` 和 `b` 的位置，并将 `b` 的个数增加 $1$（乘以 $2$）**。

所以**从后往前**遍历字符串，可以用一个计数器，记录当前字符 `a` 为了到后段需跨越的 `b` 的数量。当遇到 `b` 时，则计数器增加 $1$;遇到 `a` 时，则使答案加上计数器，并把计数器**乘以 $2$**。

记得取余。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
char s[1000005];
int ans,cnt,l;
int main(){
	cin>>s;
	l=strlen(s);
	for(int i=l-1;i>=0;i--){
		if(s[i]=='b'){
			cnt++;
			cnt%=mod;
		}
		else{
			ans+=cnt;
			ans%=mod;
			cnt*=2;
			cnt%=mod;
		}
	}
	cout<<ans%mod;
	return 0;
}
```


---

## 作者：cqbzhr (赞：1)

一开始，本蒟蒻以为是一道模拟题，于是……
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long m=1e9+7;
string s;
long long f(int l,long long ans){
	bool g=1;
	for(int i=0;i<l;i++){
		if(s[i]=='a'&&s[i+1]=='b'){
			g=0;
			break;
		}
	}
	if(g)return ans%m;
	for(int i=0;i<l;i++){
		if(s[i]=='a'&&s[i+1]=='b'){
			l++;
			s+=' ';
			for(int j=l-1;j>=i+2;j--){
				s[j+1]=s[j];
			}
			s[i+2]='a',s[i+1]=s[i]='b';
			ans++;
			ans%=m;
		}
	}
	f(l,ans%m);
}
int main(){
	cin>>s;
	int l=s.length();
	printf("%lld",f(l,0ll)%m);
	return 0;
}
```
结果就大紫又大黄了(学校oj)

整理思路后，我发现了一个神奇的事情：
	最后状态必然为 $bb \cdots baa \cdots aa$。

我们发现，一次 $ab\to bba$ 操作的实质是将 $a$ 挪到 $b$ 后面，再把 $b$ 乘 $2$。

那我们就可以这样考虑，从后往前扫描字符串，如果遇到 $b$，则计数器 $k$ 加 $1$，即下一个 $a$ 要翻越的数量。如果遇到 $a$，则把此时的计数器 $k$ 直接计入答案，再将 $b$ 的数量即计时器 $k$ 乘 $2$。

注意：记得对 $10^9+7$ 取余。

### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long m=1e9+7;
string s;
long long ans,k;
int main(){
	cin>>s;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]=='b')k++;
		else{
			ans=(ans+k)%m,
			k=k*2%m;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

这个代码的长度属实想把我给干掉 $\dots \dots$

---

## 作者：midsummer_zyl (赞：1)

## 理解：

题目描述中要将 ``ab`` 改为 ``bba``，如果我们在字符串中找不到 ``ab`` 子串，那么就结束了。输出执行的最小步骤，答案对 $10^9+7$ 取模。

我们发现，每一次操作实质是将 ``a`` 挪到了 ``b`` 后面，再把 ``b`` 的数量乘二。

最后字符串必然形如：``bb...baa...a``。

那么我们从后往前便利字符串，如果遇到 ``b``，则 $sum$ 加 $1$，即下一个 ``a`` 要越过的数量。如果遇到 ``a``，则把此时的 $sum$ 直接计入 $ans$，再将 ``b`` 的数量（即 $sum$）乘 $2$。

## AC代码：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mod = 1e9 + 7;
int main() {
	string s; cin >> s;
	LL sum = 0, ans = 0;
	for (int i = s.size() - 1; i >= 0; --i) {
		if(s[i] == 'b') sum++;
        //遇到 b 计数器加一
		else ans += sum, sum *= 2;
        //否则遇上 a 将 sum 的值存入 ans, 再将计数器乘二
		ans %= mod, sum %= mod;
        //取模
	}
	printf("%lld", ans);
	return 0;
}
//QwQ
```



---

## 作者：LOvO (赞：0)

# CF804B Minimum number of steps 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF804B)

## 题目大意：

我们有一串只包含字母 `a` 和 `b` 的字符串，我们需要将所有的子串 `ab` 变成 `bba`，求最小的操作次数。

## 解题思路：

先手玩几个小数据，我们会发现最终的字符串都是形如 `bbb...baaa...a` 形式，所以，我们可以维护每个 `a` 要花多少步可以移到字符串的尾部。

因为子串 `ab` 会变成 `bba`，所以每个 `a` 每移动一步，就会多出一个 `b`。

所以我们需要倒序枚举，并且当我们枚举到一个 `a`，`b` 的数量就会增加一倍（原来的数量加上这一个 `a` 跨越这些 `b` 所增加的 `b` 的数量）。

注意要取模！

## Code：

```cpp
#include <iostream>
#include <string>
#define int long long
using namespace std;
const int mod = 1000000007;
signed main() {
	string s;
	cin >> s;
	int num = 0, ans = 0;						//num 为当前 b 的数量，ans 为将第 i 位以后的 a 移动到字符串的末尾一共需要的步数。
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == 'b') num++;					//当前位置字符为 b，数量加一。
		if (s[i] == 'a') {
			ans += num, num += num;				//当前位置为 a，将这个 a 移到末尾，b的数量乘以二，累加答案。
			ans %= mod;
			num %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}
```







---

## 作者：Walrus (赞：0)

##  题意

给一个字符串 $str$，假设其长度为 $N$，如果其中出现子串 "$ab$"，那么就将其替换为 "$bba$"，直到字符串中没有子串 "$ab$" 为止。问你这时已经替换的次数。



## 考场思路+分析

我这里主要是考场思路，因为在考场上你没有这么多时间和精力去想，关键是我们这还是 T1，所以我们考虑通过暴力的方法寻找一些规律。

显然，如果你在纸上写一下，可以发现，最后的字符串一定类似于 "$bbb...baaa...a$" 的形式，所以我们可以研究替换过后的性质。

我们就题论题，研究一下将 "$ab$" 替换为 "$bba$" 后可能会有什么影响，举个例子，如果有一个子串为 "$aab$"，那么至少会连续进行两次操作，类似于连锁反应。这里给一下暴力思路。

- 直接找字符串中的子串 "$ab$"，找一个就替换它。

这种方法时间复杂度很高，应该是 $O(N \times ans)$，这里的 $ans$ 表示的是答案，答案可以到 $7e6$ 的级别，那肯定不能这么做，但我们可以利用暴力去寻找规律。

我们注意到，当遇到子串 "$ab$" 时，其左边一般都是 "$bb...baaa...aab$" 的形式，左边连续的一段 '$b$' 不会再产生任何可替换的子串了，所以我们直接无视它们，所以会对我们答案产生影响的，只有当前可替换的子串左边连续的 '$a$' 的个数，显然，'$a$' 越多，这一个子串所造成的连锁反应就越大，所以我们理所应当去研究**当前可替换子串左边连续的 '$a$' 的个数对答案的影响**。

用暴力程序分别测试字符串 "$ab$"、"$aab$"、"$aaab$"、"$aaaab$"、"$aaaaab$"、"$aaaaaab$"，所得到的答案应该分别是 $1$、$3$、$7$、$15$、$31$、$63$，我们发现，形如上述的字符串，它的答案应该表示为 $ans=sum\times 2-1$，这里的 $sum$ 是当前可替换子串左边连续的 '$a$' 的个数。

**假设当前可替换子串的位置记录为 $str_i$ 和 $str_{i+1}$。**

**所以我们可以扫一遍原串，如果发现子串 "$ab$"，那么就同上述方法累加答案，但这里要注意，为什么题目要让你替换为 "$bba$"，因为它最左边的 '$a$' 可能还会与右边的字符串继续造成影响，所以我们要将 $str_{i+1}$，也就是字符 '$b$'，替换为字符 '$a$'，继续遍历字符串。**

对于当前可替换子串左边连续的 '$a$' 的个数，也就是前缀 '$a$' 的个数，我们可以用**前缀和**的方式来记录，预处理一下即可。时间复杂度 $O(N)$。



## Code

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
char s[N];
int n, ans;
int a[N], f[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	// freopen("minstep.in", "r", stdin);
	// freopen("minstep.out", "w", stdout); 
	cin >> (s + 1);
	n = strlen(s + 1);
	for(int i = 1;i <= n;i++) 
		f[i] = f[i - 1] + (s[i] == 'a');
	for(int i = 1;i <= n;i++) 
		a[i] = a[i - 1] * 2 + 1, a[i] %= mod;
	
	for(int i = 1;i <= n;i++) {
		if(s[i] == 'a' && s[i + 1] == 'b')
			s[i + 1] = 'a', ans += a[f[i]], ans %= mod;
	}		
	cout << ans;
}
```



---

## 作者：lijunxi1 (赞：0)

对于此题，我们先来列一个样例：

| 操作次数 |     字符串     |
| :------: | :------------: |
|   $0$    |   ```aabb```   |
|   $1$    |  ```abbab```   |
|   $2$    |  ```bbaab```   |
|   $3$    |  ```bbabba```  |
|   $4$    | ```bbbbaba```  |
|   $5$    | ```bbbbbbaa``` |

我们发现，所有的 $a$ 都到了后面，所有的 $b$ 都到了前面。

思考让如何让所有 $a$ 到后面？

即判断里它应当到的位置的距离。

> 注意：移动一次会使距离乘二

~~完~~

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long ans,c;
string s;
int main ()
{
   
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>s;
    for(int i=s.size()-1;i>=0;i--)
    {
        if(s[i]=='a')
        {
            ans=(ans+c)%MOD;
            c=(c*2)%MOD;
        }
        else c=(c+1)%MOD;
    }
    cout<<ans;
}
```





---

## 作者：xinruian (赞：0)

### **题意**

给你一个仅由 `a`，`b` 组成的字符串，我们可以通过操作把串中的 `ab` 替换为 `bba`。求使得字符串中没有内容为 `ab` 的子串的最小操作数。

### **分析**

使得字符串中没有 `ab`，就是让字符串中不存在字符 `b` 在字符 `a` 后面。

字符串 `ab` 的最小操作数为 $1$，字符串变为 `bba`。

字符串 `abb` 的最小操作数为 $2$，字符串变为 `bbbba`。

字符串 `abbb` 的最小操作数为 $3$，字符串变为 `bbbbbba`。

显然，当字符 `a` 后面有 $cnt$ 个 `b`，需要的最小操作数为 $cnt$。

### **思路**

记操作次数为 `cnt`。我们只需从后往前遍历字符串，统计字符 `b` 的个数 `cnt`，若当前遍历到的字符为 `b`，统计字符 `b` 的个数 `cnt+=1`；若当前遍历到的字符为 `a`，操作次数 `ans +=cnt`，并且字符 `b` 的个数 `cnt = cnt*2`。

### **代码**

```cpp
#include <iostream>
#include <string>

const int mod = 1e9 + 7;

int main() {
	std::string s;
	std::cin >> s;
	long long ans = 0, cnt = 0;
	for (int i = s.size() - 1; ~i; i --) {
		if (s[i] == 'b')
			cnt ++;
		else
			ans = (ans + cnt) % mod,
			cnt = cnt * 2 % mod;
	}
	std::cout << ans << "\n";
	return 0;
}
```



---

## 作者：Morax2022 (赞：0)

# CF804B 题解
- **先读题**

给一个字符串，求多少次操作能使没有 a 在 b 前面。

而一次操作指将一个 ab 变成 bba。

------------

- **思路**

如果要变成这样，只需在字符串中每遇一个 a 就进行操作，但此次操作会使 ab 变成 bba，仍然有 a 出现。

所以若遇见了一个 a 就让总操作数加上之前所有的字符的个数，而之前的字符经过操作一定都变成了 b，那就要统计好出现过 b 的次数。

最后，因为经过了这些操作，每次都让 b 增加了一个，要把 b 的计数器乘 $2$ 再模一下。
# AC Code
```c
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int cntb = 0, mod = 1e9 + 7, tot = 0;//分别记录b的数量, 模的数, 与操作总数。
	for (int i = s.size() - 1; i >= 0; i--)//因为为了方便记录a之前出现的b的数量，使用倒序。
	{
		if (s[i] == 'a')//如果为a，就证明还要进行之前出现的b的个数次操作。 
		{
			tot = (tot + cntb) % mod;//计算加上的操作数模以mod。 
			cntb *= 2;//一个ab会变成bba，多出一个b，之前出现b的总数要变成两倍。 
			cntb %= mod;//模。
		}
		else cntb++;//是b的话就使b的数量加一个。 
	}
	cout << tot;//输出操作数。 
}
```
希望本题解能给大家带来帮助！

---

## 作者：弦巻こころ (赞：0)

考试CF原题大战可海星.

一道结论题,结论不难,~~OEIS解决问题~~,考场人全员A了这道题,wsl...

首先,我们可以很容易的想到,如果有多个a在b前面,我们一定会选择较前的.所以我们可以得出,较前的不会影响较后的.我们就可以考虑,将每个b单独处理.
我们略加思考就可以发现,如果我们一个个处理最前的b,那么当我们处理到当前b时,前面可能会有许多之前操作剩下来的b,**但它前面的a的个数,就是原序列中在它之前的a的个数.**

我们就将问题简化到了处理

aaaa....ab 的问题上了.

那么需要多少下呢.

经过简单的~~打表~~过后我们可以发现 它操作次数就为 Pow(2,n)-1(n为a的个数),这样我们储存下之前a的个数,或者直接记录下Pow值就可以做了

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n;
char s[2000010];
long long ans,num[2000010];
long long res,fa;
int main()
{
	cin>>s+1;
	int n=strlen(s+1);//输入
	res=1;//记得将res初始化为1
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='a')//如果有a就将res值乘2.
		{
			res<<=1;
			res%=mod;
		}
		else//如果有b就计算答案
		{
			ans+=res-1;
			ans%=mod;	
		}
	}

	cout<<ans;
}
```


---

