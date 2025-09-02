# String LCM

## 题目描述

如果字符串 $s$ 可以变成 $n$ 个字符串 $s_1$ 首尾相连，则说 $s$ 能被 $s_1$ 整除或 $s_1$ 能整除 $s$。

定义两个字符串 $s_1,s_2$ 的最短公倍串为：**可以被 $s_1$ 和 $s_2$ 整除的最短的非空串**。

例如： $baba$ 和 $ba$ 的最短公倍串为 $baba$；$aa$ 和 $aaa$ 的最短公倍串为 $aaaaaa$；$aba$ 和 $ab$ 没有最短公倍串。

## 样例 #1

### 输入

```
3
baba
ba
aa
aaa
aba
ab```

### 输出

```
baba
aaaaaa
-1```

# 题解

## 作者：きりと (赞：5)

**[题目传送门](https://www.luogu.com.cn/problem/CF1473B)**

### 题目大意

若字符串$a$为字符串$b$中的某一段连续的循环字串，我们则称$b$可以被$a$整除，现给出两个字符串$s,t$求可被$s$和$t$整除的最短非空字符串

### 解题思路

##### 方法一

我们要求能同时被$s$和$t$整除的最短字符串，也就是要求$s$和$t$的最小公倍数。我们知道，在求整数之间的最小公倍数时，我们会先求出他们的公约数，再求公倍数。



转移到字符串之间，我们也应该先求出$s$和$t$的约数，也就是他们的公共循环字串，然后就很容易可以求出他们的最小公倍数。

##### 方法二

此时我们考虑：若两个字符串有最小公倍数，则最小公倍数的长度为：$L=\frac{ls*lt}{gcd(ls,lt)}$，那么我们不妨将字符串$s$,$t$都$×gcd(ls,lt)$，然后比较两个字符串是否相等，若相等，则此时的$s$,$t$就是它们的最小公倍数，若不相等，输出$-1$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int main()
{
    int q;
    cin>>q;
    while(q--)
    {
    	cin>>s>>t;
    	int ls=s.size(),lt=t.size();
    	int x=__gcd(ls,lt);  //如果能将这个gcd换成手写，我这个程序将是最优解，可惜改不得
    	int lp=x*(ls/x)*(lt/x);
    	int t1=lp/ls,t2=lp/lt;
    	string ss="",tt="";  //清空它一手,这个初值不能赋，这个初值...不用赋,它AC定了
    	for(int i=1;i<=t1;i++)
    	{
    		ss+=s; 
		}
		for(int i=1;i<=t2;i++)
    	{
    		tt+=t; 
		}
		if(ss==tt)
		{
			cout<<ss<<endl;
		}
		else
		{
			cout<<-1<<endl;
		}
	}
    return 0;
}
```



---

## 作者：xtracer (赞：4)

## 简单小学数论题
这题我们可以用小学整数的 $\gcd$ 和 $\operatorname{lcm}$ 来解决。对于字符串 $a$ ，$b$ ，它们的“最小公倍字符串”就是由 $x$ 个 $a$ ，或者 $y$ 个 $b$ 拼接而成（ $x,y$ 均为正整数）。所以这题的关键在于求出 $a,b$ 长度的最小公倍数。

### 求最小公倍数
我们都知道，两个整数 $A_0,A_1$ 的最小公倍数为 $\dfrac{A_0 \times A_1}{\gcd(A_0,A_1)}$ ，其中 $\gcd$ 是最大公因数。先辗转相除求出 $\gcd$，再进一步计算即可。

### 获得两数的拼接
求出 $\operatorname{lcm}$后，就可计算出 $x,y$ 了。$x$ 就为 $\operatorname{lcm}/\operatorname{len(a)}$ ， $y$ 就为 $\operatorname{lcm}/\operatorname{len(b)}$ 。将 $a,b$ 分别复制 $x,y$ 次，得到两个新串 $aa,bb$ 。

### 求出答案
此时的 $aa,bb$ 长度相同。我们只需判断 $aa$ 是否等于 $bb$ ，是则输出 $aa$ （ $bb$ 也行），否则输出 `-1` 。

### 注意事项
- Python 3 里的 `max` 和 `min` 在手写 $\gcd$ 时不要使用！会导致结果出错！正确的应该是 `if a<b:a,b=b,a` 。
- 此题辗转相减比相除快。
- 此题标准数学库 math 里的 $\gcd$ 空间花费较小。
- 别忘了，Python 3 里 `//` 才是整除（这点和 C++ 不同）。
### 完整代码
```python
#from math import gcd
def gcd(a,b):
    	if a<b:a,b=b,a
    	if b==0:return a
    	else:return gcd(b,a-b)
def solve():
    	a=input()
    	b=input()
    	glen=gcd(len(a),len(b))
    	glen=len(a)*len(b)//glen
    	aa=a*(glen//len(a))
    	bb=b*(glen//len(b))
    	if aa==bb:print(aa)
    	else:print(-1)
t=int(input())
for i in range(0,t):solve()
```
math 库函数版：
```python
from math import gcd
def solve():
    	a=input()
    	b=input()
    	glen=gcd(len(a),len(b))
    	glen=len(a)*len(b)//glen
    	aa=a*(glen//len(a))
    	bb=b*(glen//len(b))
    	if aa==bb:print(aa)
    	else:print(-1)
t=int(input())
for i in range(0,t):solve()
```
感谢收看！

update on 2021.3.15 22:27 修复了博客缩进的错误（将原先的4空格缩进改成8空格了）。

update on 2021.3.16 20:24 修复了错误的 $\LaTeX$ 。

---

## 作者：Yizhixiaoyun (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1473B)

## 题目分析

本题其实就是将我们熟悉的**求数字公倍数**变成了**求字符串公倍数**，因此我们做题的方法考虑**数学**。

先求出两个字符串的最大公因数，然后就可以求出它们的最小公倍数。接着将它们全部加长到最小公倍数的长度，比较它们是否相同即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		string s1,s2;
		cin>>s1>>s2;
		register int size1=s1.size(),size2=s2.size(); 
		register int gcd=__gcd(size1,size2);
		register int lcm=size1*size2/gcd;
		string ans1,ans2;
		for(register int i=1;i<=lcm/size1;++i) ans1+=s1;
		for(register int i=1;i<=lcm/size2;++i) ans2+=s2;
		if(ans1==ans2) cout<<ans1<<endl;
		else cout<<"-1"<<endl;
	}
}
```

---

## 作者：expnoi (赞：1)

根据观察可以得知，最短公倍串的长度就是两个串的长度的最小公倍数。

那么我们只要计算出两个串的最小公倍数，然后两个串直接一起扩展到对应的最短公倍串的长度，再判断其是不是相同的串即可。


最后献上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T;
string s1,s2,s3,s4;
int main()
{
	T=read();
	while(T--)
	{
		s1=s2=s3=s4="";//多组数据，每次测试都要初始化
		cin>>s1>>s2;
		int n=s1.size(),m=s2.size();
		int gys=n*m/__gcd(n,m);//求最短公倍串的长度
		for(int i=1;i<=gys/n;i++)
		{
			s3+=s1;
		}
		for(int i=1;i<=gys/m;i++)
		{
			s4+=s2;
		}
		if(s3==s4)
		{
			cout<<s3;
			puts("");
		}
		else
		{
			puts("-1");
		}
	}
}
```


---

## 作者：heaven_soar (赞：1)

### 题目简述

给两个字符串 $a,b$ ，求是否存在一个最短字符串 $c$ 使得 $a$ 重复若干遍和 $b$ 重复若干遍都能得到 $c$。

### 解题思路
(默认下标从 $0$ 开始。)

我们假设存在这么一个字符串 $c$，那么对于下标 $i$，有$a[i\% lena]= b[i\% lenb]=c[i]$($lena$ 表示 $a$ 的长度，$lenb$ 表示 $b$ 的长度)。

这样我们就可以从 $0$ 开始，不断增加 $i$ 构造 $c$,如果某一个 $i$ 使得 $a[i\%lena]\ne b[i\%lenb]$ 就没有这个 $c$。反之如果一直相等，直到 $i\%lena=lena-1$ 且 $i\%lenb=lenb-1$（即 $a,b$ 同时被枚举完）这时候的 $c$ 就是最短的。（因为长度是最小公倍数）

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring> 
#define re register
using namespace std;
char lcm[4010];
int len=0;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		len=0;
		char s1[30],s2[30];
		scanf("%s%s",s1,s2);
		int len1=strlen(s1),len2=strlen(s2);
		int ths=0;
		bool f=true;
		while(1){
			lcm[len++]=s1[ths%len1];
			if(s1[ths%len1]!=s2[ths%len2]){
				f=false;
				break;
			}else if(ths%len1==len1-1&&ths%len2==len2-1) break;
			ths++;
		}
		if(f){
			for(re int i=0;i<len;++i) cout<<lcm[i];
		}else cout<<"-1";
		puts("");
	} 
	return 0;
}
```

---

## 作者：happybob (赞：0)

各位大佬数学好厉害，$\LARGE\text{orz}$，我想不出数学方法，只好用 $\large 14.42s$ 的模拟，每个点 $\large 500ms$ 左右，数据小，不会超时。

我用的是 ~~字符串乘法~~ 运算符重载做的这道题，将 $a, b$ 两个字符串从 $1$ 乘到 $100$，然后 $ \text{O}(100^2)$ 的复杂度判断，有就输出，没有就是 $-1$。

代码：

```cpp
#include <iostream>
#include <string>
using namespace std;

string operator*(string a, int b)
{
	string x = "";
	for (register int i = 1; i <= b; i++)
	{
		x += a;
	}
	return x;
}

const int MAXN = 1e2 + 5, N = 1e2;
string ax[MAXN], bx[MAXN];

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		string a, b;
		cin >> a >> b;
		for (register int i = 1; i <= N; i++)
		{
			ax[i] = a * i;
			bx[i] = b * i;
		}
		bool f = true;
		for (register int i = 1; i <= N; i++)
		{
			for (register int j = 1; j <= N; j++)
			{
				if (ax[i] == bx[j])
				{
					cout << ax[i] << endl;
					f = false;
					break;
				}
			}
			if (!f) break;
		}
		if (f) cout << "-1\n";
	}
	return 0;
}
```


---

## 作者：Fa1thful (赞：0)

### 题意：
给定两个只含有 $ab$ 的字符串，求出将它们分别延长后最小可以相同的字符串（延长指在后面接一段相同的字符串），如果没有输出$-1$
### 分析：
一开始看到这题想到的就是直接模拟，在每个后面接上自己，判断是否相同。可是有一个问题：到底延长到什么时候才能下定论呢？看到最小公倍串，我想到可以延长到两个长度的最小公倍数的长度。

#### 证明：
我们可以想到一个字符串在后面接一段自己，那么长度一定是这个字符串的倍数。如果有两个字符串，那么两个字符串相同的前提是长度相同。如果长度相同，那么必须是两个字符串每个长度的倍数的乘积的倍数，就是两个数最小公倍数的倍数。

那么最小公倍数怎么求呢？

以$6$和$8$为例

![](https://cdn.luogu.com.cn/upload/image_hosting/nbkz7x1z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

根据短除法就可以知道

$LCM=(a*b)/gcd$

### 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
char s[100000];
char s1[100000];
int gcd(int x, int y)                //最大公约数gcd（也可以用辗转相除） 
{
	for (int i = max(x, y); i >= 1; i--)
	{
		if (x % i == 0 && y % i == 0)
		{
			return i;
		}
	}
}
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> s >> s1;
		int n = strlen(s);
		int m = strlen(s1);
		int lxy = n * m / gcd(n, m);             //lcm
		for (int i = 0; i + n < lxy; i++)
		{
			s[i + n] = s[i];                      //拼接1 
		}
		for (int i = 0; i + m < lxy; i++)
		{
			s1[i + m] = s1[i];                  //拼接2 
		}
		int shabi = 0;
		for (int i = 0; i < lxy; i++)
		{
			if (s[i] != s1[i])
			{
				shabi = 1;                     //如果不相等 
				cout << -1 << endl;
				break;
			}
		}
		if (shabi == 0)                    //如果相等 
		{
			for (int i = 0; i < lxy; i++)
			{
				cout << s[i];
			}
			cout << endl;
		}
	}
}
```

一个小故事：做这题我蹦出这个想法时别的同学都没有想法，为了抢首杀，写得十分仓促，错了一堆小细节。最后成了第五个A的。。。
以后一定要脚踏实地地好好细心地做题啊！

---

## 作者：Eason_AC (赞：0)

## Content
如果一个字符串 $s$ 由若干个字符串 $t$ 拼接而成，则我们说 $s$ 能被 $t$ 整除。定义 $s_1,s_2$ 的最短公倍串为可以同时被 $s_1,s_2$ 的最短非空字符串。给定 $T$ 对字符串 $s_1,s_2$，求出每对字符串的最短公倍串。

**数据范围：$T\in[1,2000],|s_1|,|s_2|\in[1,20]$。**
## Solution
《记我用 1.81k 代码过了一道普及- 的题目》

由于数据范围小得可怜，我们可以先暴力求出 $s_1,s_2$ 的所有非空子串，然后再判断两个字符串是否同时存在一个子串 $s$，使得 $s_1,s_2$ 都能够被 $s$ 整除。设我们找出来的这个字符串为 $s_0$，并设 $s_1$ 由 $a$ 个 $s_0$ 拼成，$s_2$ 由 $b$ 个 $s_0$ 拼接而成，那么只需要连续输出 $\operatorname{lcm}(a,b)$ 个 $s_0$ 就好了。

这种思路说起来容易，代码实现却不是那样简单。所以包括宏定义、头文件和快读在内，我打了 1.81k 的代码。

你可以去[这里](https://www.luogu.com.cn/paste/ju6neodf)看到我和其他一些神仙的代码长度比较，由此可以看出我很菜qwq。
## Code
```cpp
string s1, s2, subs1[27], subs2[27], pos[27], ans;
int t, pos1[27], pos2[27], poscnt;
map<string, int> vis;

inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline int lcm(int a, int b) {return a * b / gcd(a, b);}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	t = Rint;
	while(t--) {
		F(i, 1, 20) subs1[i] = ""; F(i, 1, 20) subs2[i] = ""; F(i, 1, 20) pos[i] = "";
		memset(pos1, 0, sizeof(pos1)), memset(pos2, 0, sizeof(pos2));
		vis.clear(); poscnt = 0; ans = "";
		cin >> s1 >> s2;
		int len1 = s1.size(), len2 = s2.size();
		F(i, 1, len1) subs1[i] = s1.substr(0, i);
		F(i, 1, len2) subs2[i] = s2.substr(0, i);
		F(i, 1, len1) {
			if(len1 % i) continue;
			string s = "";
			F(j, 1, len1 / i) s += subs1[i];
			if(s == s1) pos1[++pos1[0]] = len1 / i, pos[++poscnt] = subs1[i], vis[subs1[i]] = pos1[0];
		}
		F(i, 1, len2) {
			if(len2 % i) continue;
			string s = "";
			F(j, 1, len2 / i) s += subs2[i];
			if(s == s2 && vis[subs2[i]]) pos2[++pos2[0]] = len2 / i, ans = subs2[i];
		}
		if(ans == "") {puts("-1"); continue;}
		F(i, 1, lcm(pos1[vis[ans]], pos2[pos2[0]])) cout << ans;
		puts("");
	}
	return 0;
}

```

---

## 作者：CGDGAD (赞：0)

### Codeforces 1473 B 题解

提供一个非常“傻”的暴力方法，但可以通过本题（

### 思路

先找出A的所有可能的拆解方式（例如样例1的第一个字符串： `baba` = `ba` $\times 2$ = `baba` $\times 1$）

然后找出B的所有可能拆解方式（例如样例1的第二个字符串： `ba` = `ba` $\times 1$） 

发现 `ba` 是公共的，所以结果就是 `ba` $\times \operatorname{lcm}(2, 1)$ = `baba`。

所以程序思路如下：

- 找出A的所有可能的拆解方式，存储下来（我用了 `pair<string, int>`）
- 找出B的所有可能拆解方式，也存下来
- 枚举A和B的所有拆解方式，找出最长的公共拆解方式（即两个拆解方式拆出来的字符串是一样的）
- 然后生成 `String LCM`。

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
typedef std::pair<std::string, int> psi;
std::string a, b;
std::vector<psi> aRes;
std::vector<psi> bRes;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
void parseA() { // 生成A的所有拆解
	aRes = std::vector<psi>();
	for (int i = 1; i <= a.length(); i += 1) {
		if (a.length() % i == 0) {
			int x = a.length() / i;
			std::string now, last;
			bool flag = true;
			for (int j = 0; j < a.length(); j += 1) {
				const int n = j + 1;
				now += a[j];
				if (n % x == 0) {
					if (last != now && last != std::string()) {
						flag = false;
						break;
					}
					last = now;
					now = std::string();
				}
			}
			if (flag) {
				aRes.push_back( std::make_pair(last, i) );
			}
		}
	}
}
void parseB() { // 生成B的所有拆解
	bRes = std::vector<psi>();
	for (int i = 1; i <= b.length(); i += 1) {
		if (b.length() % i == 0) {
			int x = b.length() / i;
			std::string now, last;
			bool flag = true;
			for (int j = 0; j < b.length(); j += 1) {
				const int n = j + 1;
				now += b[j];
				if (n % x == 0) {
					if (last != now && last != std::string() ) {
						flag = false;
						break;
					}
					last = now;
					now = std::string();
				}
			}
			if (flag) {
				bRes.push_back( std::make_pair(last, i) );
			}
		}
	}
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		std::cin >> a >> b;
		parseA();
		parseB();
		bool flag = false;
		for (auto i : aRes) {
			for (auto b : bRes) { // 枚举所有拆解方式
				if (i.first == b.first) { // 如果是公共的连续子串
					int _gcd = gcd(i.second, b.second);
					int lcm = i.second * b.second / _gcd; // 生成String LCM并输出
					for (int j = 1; j <= lcm; j += 1) std::cout << i.first;
					printf("\n");
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag) printf("-1\n");
	}
	return 0;
}
```

---

