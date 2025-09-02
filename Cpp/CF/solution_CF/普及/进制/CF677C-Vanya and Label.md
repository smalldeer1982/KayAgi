# Vanya and Label

## 题目描述

While walking down the street Vanya saw a label "Hide&Seek". Because he is a programmer, he used $ & $ as a bitwise AND for these two words represented as a integers in base $ 64 $ and got new word. Now Vanya thinks of some string $ s $ and wants to know the number of pairs of words of length $ |s| $ (length of $ s $ ), such that their bitwise AND is equal to $ s $ . As this number can be large, output it modulo $ 10^{9}+7 $ .

To represent the string as a number in numeral system with base $ 64 $ Vanya uses the following rules:

- digits from '0' to '9' correspond to integers from $ 0 $ to $ 9 $ ;
- letters from 'A' to 'Z' correspond to integers from $ 10 $ to $ 35 $ ;
- letters from 'a' to 'z' correspond to integers from $ 36 $ to $ 61 $ ;
- letter '-' correspond to integer $ 62 $ ;
- letter '\_' correspond to integer $ 63 $ .

## 说明/提示

For a detailed definition of bitwise AND we recommend to take a look in the corresponding article in Wikipedia.

In the first sample, there are $ 3 $ possible solutions:

1. $ z&_=61&63=61=z $
2. $ _&z=63&61=61=z $
3. $ z&z=61&61=61=z $

## 样例 #1

### 输入

```
z
```

### 输出

```
3
```

## 样例 #2

### 输入

```
V_V
```

### 输出

```
9
```

## 样例 #3

### 输入

```
Codeforces
```

### 输出

```
130653412
```

# 题解

## 作者：cff_0102 (赞：2)

把字符串每一位都拆成二进制，那题目就变成了寻找有多少对二进制数，它们按位与的结果是输入的字符串转换成的那个二进制。

对于每位 $1$，只有 $1\ \&\ 1=1$ 一种方法。

对于每位 $0$，可以是 $0\ \&\ 0=0$，可以是 $0\ \&\ 1=0$，也可以是 $1\ \&\ 0=0$，有三种这一位得到 $0$ 的方法。

所以，只需要记录下输入的字符串对应的数字的二进制中 $0$ 的个数，累加起来，记这个数为 $s$，则答案是 $3^s$（记得还要取模）。

本题坑点：翻译翻的一塌糊涂，字母表最后一个字母成了 `b`，大小写范围都翻反了。请各位不要看中文翻译，看英文原文。

```python
d={'0':0,'1':1,'2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9,
'A':10,'B':11,'C':12,'D':13,'E':14,'F':15,'G':16,'H':17,'I':18,'J':19,'K':20,'L':21,'M':22,'N':23,'O':24,'P':25,'Q':26,'R':27,'S':28,'T':29,'U':30,'V':31,'W':32,'X':33,'Y':34,'Z':35,
'a':36,'b':37,'c':38,'d':39,'e':40,'f':41,'g':42,'h':43,'i':44,'j':45,'k':46,'l':47,'m':48,'n':49,'o':50,'p':51,'q':52,'r':53,'s':54,'t':55,'u':56,'v':57,'w':58,'x':59,'y':60,'z':61,
'-':62,'_':63}

a=input()
s=0
for c in a:
    s+=6-str(bin(d[c])).count('1') # 注意：不能直接 count('0')，一是因为 str(bin(x)) 得到的结果开头有“0b”，而是因为有可能二进制位数不足 6 位，前面几位的“0”不会被算进去

print(3**s%1000000007)
```

---

## 作者：浮光掠影 (赞：1)

### 前言

- 原来的中文翻译一塌糊涂，感谢 [cff_0102](https://www.luogu.com.cn/user/542457) 为本题提供正确翻译！

### 解题思路

这题要判断有多少种方法通过逻辑与来获得输入的字符串，其中每个字符对应的数值如上面描述。

由于字符的数值的范围为 $0 \sim 63$ ，即 $2^6-1$，那么每个字符可以转化为 $6$ 位的二进制数，然后我们用一个循环来统计这个字符串所有字符转化为二进制后一共有多少位数为 `0` 即可。

因为当一个位为 `0` 的时候，那么这一位就可以由 $3$ 种情况获得：`0&0`,`1&0`,`0&1`，而当一位为`1`时，只有 `1&1` 一种方法获得；因此最后的结果为 $3^n$，其中 $n$ 代表转化为二进制后为 `0` 的位的数目。

最后还要记得对 $10^9+7$ 取模，由于 $3\times (10^9+7)$ 会超过 `int` 的范围，因此我们需要用 `long long` 来存储。


### 解题代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int Map[256];
void init()
{
	for(int i = '0';i<='9';i++)Map[i] = i-'0'; 
	for(int i = 'A';i<='Z';i++)Map[i] = i-'A'+10;
	for(int i = 'a';i<='z';i++)Map[i] = i-'a'+36;
	Map['-']=62;
	Map['_']=63;
}
int Cal(char c)
{
	int dec = Map[c];
	int one = 0;
	while(dec>0)
	{
		if(dec%2==1) one++;
		dec/=2;
	}
	return 6-one;
}
int main()
{
    init();
    string s;
    cin>>s;
    int cnt=0;
    long long result = 1;
    for(int i=0;i<s.size();i++)cnt += Cal(s[i]);
    for(int i=1;i<=cnt;i++)result = (3*result) % 1000000007;
    cout<<result<<endl;
	return 0;
}
```

---

## 作者：wurang (赞：0)

1. 字符到数字的映射：
- 数字 '0' 到 '9' 映射到 ${0}$ 到 ${9}$。
- 大写字母 'A' 到 'Z' 映射到 ${10}$ 到 ${35}$。
- 小写字母 'a' 到 'z' 映射到 ${36}$ 到 ${61}$。
- 字符 '-' 映射到 ${62}$。
- 字符 '_' 映射到 ${63}$。

2. 计算按位与的可能性：

- 对于字符串 ${s}$ 中的每个字符，我们将其转换为对应的数字 ${x}$。
- 对于每个数字 ${x}$，我们需要找出所有可能的字符对 ${(s_{1} , s_{2})}$，使得 ${s_{1}}$ 和 ${s_{2}}$ 按位与得到的字符是 ${x}$。这可以通过遍历 ${0}$ 到 ${63}$ 的所有数字组合来实现。

3. 构建可能性表：
- 创建一个数组 ${count}$，其中 ${count_{i}}$ 表示所有可能的字符对 ${(s_{1} , s_{2})}$，使得 ${s_{1}}$ 和 ${s_{2}}$ 按位与得到的字符是 ${i}$。

4. 计算结果：
- 对于字符串 ${s}$ 的每个字符，找到对应的数字 ${x}$，然后将 ${count_{x}}$ 乘起来，即可得到总的可能字符串对的数量。

**记得取模**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
string s;
long long ans = 1;
int num[100];

int change(char c) 
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 36;
    if (c == '-') return 62;
    if (c == '_') return 63;
    return -1;
}

int main() 
{
    cin >> s;
    //预处理出每个可能的 (s1[i], s2[i]) 对
    for (int a = 0; a < 64; ++a) 
    {
        for (int b = 0; b < 64; ++b) 
        {
            if ((a & b) < 64) 
            {
                num[a & b] = (num[a & b] + 1) % MOD;//取模
            }
        }
    }

    for (int i = 0; i < s.size(); i++) 
	{
		char c = s[i];
        int x = change(c);
        ans = (ans * num[x]) % MOD;//每一位相乘
    }

    cout << ans << endl;
    return 0;
}

```

---

## 作者：HUTEHE (赞：0)

## 题目大意

找到满足 $s_1\operatorname{and}s_2=s$ 的字符串对 $(s_1,s_2)$ 的数量，且 $s_1$ 和 $s_2$ 的长度都要与 $s$ 相同，并给出了字符转为数字，进行比较的规则。

## 解题思路

由于字符串 $s_1$ 和 $s_2$ 的每一位进行与运算的结果都对应着 $s$ 的相应位置，因此我们可以对 $s$ 的每一位进行单独分析。

针对 $s$ 的每一位，只有两种情况：

* 该位二进制为 $1$，则 $s_1$ 和 $s_2$ 的对应位都为 $1$。
* 该位二进制为 $0$，则 $s_1$ 和 $s_2$ 的对应位为 $00$，$01$ 或 $10$。

因此，对于 $s$ 的每一位，我们只需要统计该位表示为数字后，二进制表示中 $0$ 的个数总和，记为 $sum$，对于每一个 $0$ 最多有三种情况，根据乘法原理，最终答案为 $3^{sum}$。

## 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define int long long
#define endl "\n"
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
const int MOD=1e9+7;//记得模1e9+7
int ans;
inline int check(int n)//检查函数，计算二进制表示下 0 的的个数
{
	int sum=0;
	for(int i=1;i<=6;i++)//数最大为 64，则二进制最多有 6 位，只需检查 6 位
	{
		if(n&1)n>>=1;//当前末尾为 1，右移一位
		else n>>=1,sum++;//末尾为 0，计数器加 1，右移一位
	}
	return sum;
}
inline int fastpow(int b,int a)//此题需要用到快速幂
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}
signed main()
{	
	string s;
	cin>>s;
	for(char c:s)
	{
		int n;
		if(c>='0'&&c<='9')n=c-'0';//按题目要求进行字符与数字间转换
		if(c>='A'&&c<='Z')n=c-'A'+10;
		if(c>='a'&&c<='z')n=c-'a'+36;
		if(c=='-')n=62;
		if(c=='_')n=63;
		ans+=check(n);//累加 0 的个数
	}
	cout<<fastpow(ans,3);
	return 0;
}
```

### 时间复杂度

$O(|s|\log |s|)$，其中 $|s|$ 表示字符串 $s$ 的长度。

### 空间复杂度

$O(|s|)$，所需存储空间取决于字符串 $s$ 的长度，并随着 $s$ 长度的增加而线性增加。

---

## 作者：QWQ_123 (赞：0)

考虑对于每一位分别与然后再乘起来。

那么实际上就是对于字符串的每一位，看有多少个是 $0 \sim 63$ 数满足他们与起来是当前的数，那么预处理即可。

统计答案时乘起来即可。

```cpp
// Problem: C. Vanya and Label
// Contest: Codeforces - Codeforces Round 355 (Div. 2)
// URL: https://codeforces.com/problemset/problem/677/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Begin solve time: 2024-04-16 06:06:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;

string s;
ll cnt[100], res = 1;

int main() {
	for (int i = 0; i <= 63; ++i) {
		for (int j = 0; j <= 63; ++j)
			for (int k = 0; k <= 63; ++k)
				if ((j & k) == i)
					++cnt[i];
	}

	cin >> s;
	for (auto ch : s) {
		if (ch >= '0' && ch <= '9') res = res * cnt[ch - '0'] % mod;
		else if (ch >= 'A' && ch <= 'Z') res = res * cnt[ch - 'A' + 10] % mod;
		else if (ch >= 'a' && ch <= 'z') res = res * cnt[ch - 'a' + 36] % mod;
		else if (ch == '-') res = res * cnt[62] % mod;
		else res = res * cnt[63] % mod;
	}
	
	printf("%lld\n", res);

	return 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

## 思路
每个字符只有三种可能，跟 $0$ 取与，跟自己取与，跟下划线取与。跟 $0$ 取与和跟自己取与还是自己，所以每个字符只能跟自己取与。所以用一个变量记录每一个字符转数字后的二进制上 $0$ 的个数，最后答案就是 $3^{sum}$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
using ll=long long;
const int N=1e6+7;
int change(char a){
	if(a>='0'&&a<='9'){
		return a-'0';
	}
	if(a>='A'&&a<='Z'){
		return a-'A'+10;
	}
	if(a>='a'&&a<='z'){
		return a-'a'+36;
	}
	if(a=='-') return 62;
	if(a=='_') return 63;
}
int two(int x){
	int sum=0;
	for(int i=1;i<=6;i++){
		if(x&1){
			x>>=1;
		}
		else{
			x>>=1;
			sum++;
		}
	}
	return sum;
}
int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	string s;
	int cnt=0;
	cin>>s;
	for(int i=0;i<s.size();i++){
		int x=change(s[i]);
		cnt+=(two(x));
	}
	cout<<fpow(3,cnt);
	return 0;
} 
```


---

## 作者：CznTree (赞：0)

这翻译看的我是一头雾水，这写的啥啊？？？

虽然这不是关键，但是还是想吐槽一下。

考虑一个长度为 $n$ 的字符串 $s$，对于每一位字符，有三种组合，要么和 $0$ 取与，要么和下划线取与，要么和自身取与。

然后对 $0$ 取与是没有意义的，和自己本身取与还是本身，也就是说实际上我们只要和下划线取与就行了。

这样我们就可以得出一个结论了，答案就是这个字符串每一位上的二进制数的 $0$ 的个数，把每位上的和全部加起来就行，最后的答案也就是 $3^{sum}$。

注意答案还要取模。

### 核心代码

```cpp
void solve() {
	std::cin >> s; 
	for (int i = 0; i < strlen(s); i++) {
		sum += cnt(tonum(s[i])); // tonum 就是将字符转换为数字的形式，如题。 cnt则是统计其在二进制中 0 的个数。
	}
	std::cout << fastpow(3, sum) << std::endl; //fastpow就是快速幂
}

```



---

## 作者：cppcppcpp3 (赞：0)

- 注意：只有英文题面是正确的。

## Solution

字符串 $s$ 的每一个字符没有互相影响，因此先将字符串的每一个字符按照规则转换为二进制数 $a_i$，再对每一个字符进行解决。


又因为每个二进制位的与运算是互不影响的，所以考虑单独一个二进制位：设一组可行答案的第 $i$ 个字符对应的数为 $b_i$ 和 $c_i$。如果 $a_i$ 的某一位是 $1$，则 $b_i$ 和 $c_i$ 的这一位也都是 $1$。否则有 $10$、$01$、$00$ 三种情况。

这样做法就出来了：统计 $a_i$ 转化为 $6$ 位二进制数后 $0$ 的个数 $cnt_i$，则答案为 $3^{sum}$，其中 $sum = \sum\limits_{i=1}^{n} a_i$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;
const int N=1e5+5;
const int P=1e9+7;

string s;
int n,a[N],ans;

int v(char x){ //转换规则。
	if(x>='0' && x<='9') return x-'0';
	if(x>='A' && x<='Z') return x-'A'+10;
	if(x>='a' && x<='z') return x-'a'+36;
	return x=='-' ? 62 : 63;
}

il int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=P;
		(a*=a)%=P,b>>=1; 
	}
	return ans;
}

main(){
	cin >> s,n=s.size(),s=" "+s;
	for(int i=1;i<=n;++i) a[i]=v(s[i]);
	
	for(int i=1;i<=n;++i){
		int cnt=6;
		for(int j=0;j<6;++j) cnt-=((a[i]>>j)&1); //统计 0 的个数。
		ans+=cnt;
	}
	
	return printf("%lld",qpow(3ll,ans)),0;
}
```

---

## 作者：MiRaciss (赞：0)

快速幂，因为0&任何值都啥都等于其本身，所以我们只需要用tot统计每一个字符二进制后的0的个数，再累加即可。

最后的答案即是$3^{tot}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll Mod=1e9+7;

int Cheak(char a){
	int x=0;
	if('9'>=a&&a>='0'){
		x=a-'0';
		return x;
	}
	if('Z'>=a&&a>='A'){
		x=a-'A'+10;
		return x;
	}
	if('z'>=a&&a>='a'){
		x=a-'a'+36;
		return x;
	}
	if(a=='-')
		return 62;
	if(a=='_')
		return 63;
	return 100;
}

int CHEAK(int x){
	int tot=0;
	for(int i=1;i<=6;i++){
		if(x&1){
			x>>=1;
			continue;
		}
		x>>=1;
		tot++;
	}
	return tot;
}

ll Pow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1){
			ans=ans*a%Mod;
		}
		a=a*a%Mod;
		b>>=1;
	}
	return ans%Mod;
}

int main(){
	char a[1000005];
	scanf("%s",a+1);
	int n=strlen(a+1);
	ll sum=0;
	for(int i=1;i<=n;i++){
		int now=Cheak(a[i]);
		sum+=CHEAK(now);
	}
	printf("%lld",Pow(3,sum));
	return 0;
}

```

---

## 作者：Michael1234 (赞：0)

- 本题主要涉及**位运算**：

- 首先，我们将所有字符换成数，再按照二进制考虑，如果这一位上的数是 `1`，其只能拆分为 `1&1`。如果是 `0`，其可以拆分为 `1&0`，`0&1`或 `0&0`。

- 因此，我们只需要考虑所有二进制数中，存在多少个 `0`。

- 因为每出现一个 `0`，就有三种拆分方法，而 `1` 就只有一种拆分方法。

- 设 `sum` 为所有二进制数中 `0` 的个数。答案就是 $3^{sum}$ 。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,MOD=1e9+7;
int len,plan[N],sum;
string s;
inline int tint(char ch)
{
	if(ch<='9'&&ch>='0') return ch-'0';
	if(ch<='Z'&&ch>='A') return ch-'A'+10;
	if(ch<='z'&&ch>='a') return ch-'a'+36;
	if(ch=='-') return 62;
	if(ch=='_') return 63;
	return 100;
}//转换成数字
inline int zeros(int x)
{//最大的63转成二进制只有6位，所以只考虑6位
	int ans=0;
	for(int i=1;i<=6;i++)
	{
		if(x&1)
		{
			x>>=1;
		}
		else
		{
			x>>=1;
			ans++;
		}
	}
	return ans;
}//每个数中有多少个0
inline int ksm(int a,int b)
{//快速幂加速
	int ans=1;
	for(;b;b>>=1)
	{
		if(b&1) ans*=a,ans%=MOD;
		a*=a,a%=MOD;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++)
	{
		sum+=zeros(tint(s[i]));
	}
	cout<<ksm(3,sum);//按公式计算
	return 0;
}
~~~

---

