# DNA Alignment

## 题目描述

Vasya became interested in bioinformatics. He's going to write an article about similar cyclic DNA sequences, so he invented a new method for determining the similarity of cyclic sequences.

Let's assume that strings $ s $ and $ t $ have the same length $ n $ , then the function $ h(s,t) $ is defined as the number of positions in which the respective symbols of $ s $ and $ t $ are the same. Function $ h(s,t) $ can be used to define the function of Vasya distance $ ρ(s,t) $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/0b4348c88074431fd692746719c4a6f852a88ac1.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/e04d6b40ed912903e989b816c65cd323f288312f.png) is obtained from string $ s $ , by applying left circular shift $ i $ times. For example,  $ ρ(&quot;AGC&quot;,&quot;CGT&quot;)= $   $ h(&quot;AGC&quot;,&quot;CGT&quot;)+h(&quot;AGC&quot;,&quot;GTC&quot;)+h(&quot;AGC&quot;,&quot;TCG&quot;)+ $   $ h(&quot;GCA&quot;,&quot;CGT&quot;)+h(&quot;GCA&quot;,&quot;GTC&quot;)+h(&quot;GCA&quot;,&quot;TCG&quot;)+ $   $ h(&quot;CAG&quot;,&quot;CGT&quot;)+h(&quot;CAG&quot;,&quot;GTC&quot;)+h(&quot;CAG&quot;,&quot;TCG&quot;)= $   $ 1+1+0+0+1+1+1+0+1=6 $ Vasya found a string $ s $ of length $ n $ on the Internet. Now he wants to count how many strings $ t $ there are such that the Vasya distance from the string $ s $ attains maximum possible value. Formally speaking, $ t $ must satisfy the equation: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/106c86f5cd7beb20b5aaf5b6e98985a65f7d4450.png).

Vasya could not try all possible strings to find an answer, so he needs your help. As the answer may be very large, count the number of such strings modulo $ 10^{9}+7 $ .

## 说明/提示

Please note that if for two distinct strings $ t_{1} $ and $ t_{2} $ values $ ρ(s,t_{1}) $ и $ ρ(s,t_{2}) $ are maximum among all possible $ t $ , then both strings must be taken into account in the answer even if one of them can be obtained by a circular shift of another one.

In the first sample, there is $ ρ(&quot;C&quot;,&quot;C&quot;)=1 $ , for the remaining strings $ t $ of length 1 the value of $ ρ(s,t) $ is 0.

In the second sample, $ ρ(&quot;AG&quot;,&quot;AG&quot;)=ρ(&quot;AG&quot;,&quot;GA&quot;)=ρ(&quot;AG&quot;,&quot;AA&quot;)=ρ(&quot;AG&quot;,&quot;GG&quot;)=4 $ .

In the third sample, $ ρ(&quot;TTT&quot;,&quot;TTT&quot;)=27 $

## 样例 #1

### 输入

```
1
C
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
AG
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
TTT
```

### 输出

```
1
```

# 题解

## 作者：lightningZ (赞：4)

## 思路
首先读完题之后我们可以很~~困难~~容易的想到这是一道排列组合的数学题。关键之处就在于到底怎么排列组合，我们可以具体列一个表在观察规律，其中用 $1,2,3,4$ 来代替 $A,C,G,T$。

|  | 2233 | 2332 | 3322 | 3223 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 2333 | 3 | 3 | 1 | 1 |
| 3332 | 1 | 3 | 3 | 1 |
| 3323 | 1 | 1 | 3 | 3 |
| 3233 | 3 | 1 | 1 | 3 |

最后结果 $32$。

|  | 2233 | 2332 | 3322 | 3223 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 3333 | 2 | 2 | 2 | 2 |
| 3333 | 2 | 2 | 2 | 2 |
| 3333 | 2 | 2 | 2 | 2 |
| 3333 | 2 | 2 | 2 | 2 |

最后结果 $32$。

|  | 2233 | 2332 | 3322 | 3223 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 2233 | 4 | 2 | 0 | 2 |
| 2332 | 2 | 4 | 2 | 0 |
| 3322 | 0 | 2 | 4 | 2 |
| 3223 | 2 | 0 | 2 | 4 |

最后结果 $32$。

|  | 2233 | 2332 | 3322 | 3223 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1233 | 3 | 1 | 0 | 2 |
| 2331 | 2 | 3 | 1 | 0 |
| 3312 | 0 | 2 | 3 | 1 |
| 3123 | 1 | 0 | 2 | 3 |

最后结果 $24$。

聪明的观众已经发现规律了（没发现的可以自己再手推几个），具体来说就是对于一个数列中，假设最多数量的字母有 $m$ 个，那么其余也有 $m$ 个的字母和它就可以随意调换顺序和数量，因为这样是不影响最终结果的（前几个图）。

注意，之后数量是 $m$ 个的字母可以调换，其他数量的调换之后会影响最终结果，导致不是最优（最后一个图）。

所以计算答案的方法就显而易见了：数量是 $m$ 的字母种类的 $n$ 次方。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a,c,g,t,ans;
int zdx(int x)//计算答案 
{
	int num=1;
	while(n--) num=num*x%mod;//别忘了膜 
	return num;
}
signed main()
{
	scanf("%lld ",&n);
	for(int i=1;i<=n;i++)
	{
		char s;
		scanf("%c",&s);
		if(s=='A') a++;
		if(s=='C') c++;//啊！出现了(不是 
		if(s=='G') g++;
		if(s=='T') t++;
	}
	int m=max(a,max(c,max(g,t)));
	if(a==m) ans++;//统计个数 
	if(c==m) ans++;
	if(g==m) ans++;
	if(t==m) ans++;
	printf("%lld",zdx(ans));
	return 0;
}

```
###### 完结撒花~~~

---

## 作者：The_jester_from_Lst (赞：1)

简易数学题。

既然要求相同位数总和，容易想到答案应该与原字符串中出现次数最多的字符有关系。构造的序列中，这些字符显然是一定要出现的。至于范围，$1$ 到**该字符在原字符串中的出现次数**都是有效的。其它字符与答案并没有关联。于是我们就得出了答案的计算方法：原字符串中出现次数最多的字符的个数的 $n$ 次方。

附上代码：
```cpp
#include<bits/stdc++.h>
#define JYAAKIOI 0x8080
#define int long long
#define pii pair<int,int>
#define rg register
#define mk make_pair
#define il inline
#define fr front()
#define ep empty()
#define pp pop()
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,sum[5],s=1,ans=1;
char a;
il bool cmp(int x,int y){
	return x>y;
}
signed main(){
	n=rd();
	for(int i=1;i<=n;++i){
		cin>>a;
		if(a=='A')++sum[1];
		else if(a=='C')++sum[2];
		else if(a=='G')++sum[3];
		else if(a=='T')++sum[4];
	}
	sort(sum+1,sum+1+4,cmp);
	for(int i=2;i<=4;++i){
		if(sum[i]<sum[1])break;
		++s;
	}
	for(int i=1;i<=n;++i)ans=(ans*s)%mod;
	wr(ans);
	return 0;
}
```

---

## 作者：_Passerby_ (赞：0)

【题目大意】

给定一个长度为 $n$ 字符串，只包含```A```，```T```，```G```，```C```四种字符。

定义 $shift$ 值，指两个字符串**分别**移位之后的相同位的个数。

你需要求出满足与原字符串 $shift$ 值最大的字符串的**个数**。

【解题思路】

考虑贪心构造。

我们对于构造的字符串，每个字符都选取原字符串出现次数最多的字符，这样可以使 $shift$ 值最大。

可以这么理解，选字符串出现次数更多的字符会让移位时相同位出现的“概率”更大，这样的话，选出现次数越多的字符那也就比选其他的 $shift$ 值越大。

也就是说，构造的字符串中，每个位置都选择原字符串里出现次数最多的字符即可。

注意这题的问法，我们需要求的是这样的字符串的**个数**。我们每个位置都要 $k$ 种选法，其中 $k$ 为在字符串中出现次数最多次的字符的**个数**。这样，答案就是 $k ^ n$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int P = 1e9 + 7;
int n, mx;
int ts[10], bs;
string s;

int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = (ans * a) % P;
        }
        a = (a * a) % P;
        b >>= 1;
    }
    return ans % P;
}

signed main() {
    cin >> n;
    cin >> s;
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'A') ts[1]++;
        if (s[i] == 'T') ts[2]++;
        if (s[i] == 'G') ts[3]++;
        if (s[i] == 'C') ts[4]++;
    }
    for (int i = 1; i <= 4; i++) {
        mx = max(mx, ts[i]);
    }
    for (int i = 1; i <= 4; i++) {
        if (mx == ts[i]) bs++;
    }
    cout << qpow(bs, n);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题目描述中的，**两者相同的位数总和最大。**

从中，我们就可以想到这道题与字符串中出现最多次数的字符个数有关。（~~没读懂题的赶紧回去读题！！~~）

接着，我们随便想几个数据就会想到同一个数列中会出现出现次数相同的字符。如：
```cpp
AACTTGAT
```
可以发现 $T$ 和 $A$ 字符出现的个数都是三，而最后结果是 $256$。$T$ 和 $A$，只有两个字符，而 $n$ 是 $8$，结果就是 $ 2^8 $。（~~你可以自己再手膜几个样例~~）

显然，这个最终答案肯定与这个最大值有关。移位操作是能进行无数次的。对于整个序列来说，我们能进行无数次移位，那么就是把整个序列都与这个出现次数最多的字母匹配。就是 $1 ^ n$，而这个次数最多的字母肯定不止一个数，所以假设这些字母有 $x$ 个，那么答案就是 $x ^ n$。

***Code***
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()
inline int ra()
{
    int jjy = 0,txy = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') txy = -1; ch = getchar(); }
    while(isdigit(ch)){jjy = jjy * 10 + ch - '0'; ch = getchar(); }

    return jjy * txy;
}
const int mod = 1e9 +7;
int a[100], ans = 1, n;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = re;
	for(int i = 1; i <= n; i ++)
	{
		char x;
		cin >> x;
		a[x - 'A' + 1] ++;
	}
	sort(a + 1, a + 1 + 26);
	a[27] ++;
	if(a[26] == a[25]) a[27] ++;
	if(a[26] == a[24]) a[27] ++;
	if(a[26] == a[23]) a[27] ++;
	for(int i = 1; i <= n; ++ i) ans = (ans * a[27]) % mod;
	cout << ans;
	return 0;
}
```

---

