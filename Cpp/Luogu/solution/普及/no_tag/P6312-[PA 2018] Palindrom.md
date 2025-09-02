# [PA 2018] Palindrom

## 题目描述

**译自 [PA 2018](https://sio2.mimuw.edu.pl/c/pa-2018-1/dashboard/)  Runda 3 [Palindrom](https://sio2.mimuw.edu.pl/c/pa-2018-1/p/pal/)**

**请特别注意本题的内存限制。**

给出一个字符串，请你判断其是否为回文串。

回文串是指从左往右读与从右往左读完全相同。

## 说明/提示

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证字符串长度不超过 $2\times 10^7$。

您可以假设在任何测试数据中都有 $n>0$ 或者 $n=0$。

感谢 @[Infinite_Eternity](/user/897776) 提供的测试数据！


## 样例 #1

### 输入

```
5
kajak```

### 输出

```
TAK```

## 样例 #2

### 输入

```
0
kanu```

### 输出

```
NIE```

# 题解

## 作者：离散小波变换° (赞：9)

## 题目大意

输入一个字符串 $\left({\mathrm{len}(S)}\le10^7\right)$，判断它是不是回文串。

## 题解

由于题目的空间限制非常小（$\tt 4MB$ 左右），所以这种大小的字符串显然不能全部读入。因此考虑边读入边进行哈希操作。

考虑使用一个非常传统的字符串哈希：

$$\operatorname{Hash}(S)=\sum_{i=0}^{\mathrm{len}(S)-1}b^i\times S_i \pmod {m}$$

但是我们同时要计算出 $S$ 的反转字符串 $S'$ 的哈希值。

我们能够发现，

$$\operatorname{Hash}(S')=\sum_{i=0}^{\mathrm{len}(S)-1}b^i\times S_{len-i-1}\pmod {m}$$

如果我们记 $S_{0..r}$ 表示 $S$ 的前缀 $S_0,S_1,\cdots,S_r$ 组成的字符串，那么有：

$$\begin{aligned}\operatorname{Hash}(S_{0,k})=&\operatorname{Hash}(S_{0,k-1})\times b+S_k &\pmod {m}\cr \operatorname{Hash}(S'_{0,k})=&\operatorname{Hash}(S'_{0,k-1})+b^k\times S_k & \pmod {m}\end{aligned}$$

两者都可以很容易地维护。最后比较 $\operatorname{Hash}(S)$ 和 $\operatorname{Hash}(S')$ 即可。为了保险起见，可以取两组不同的 $(b,m)$ 分别计算，只有两次检验得到的哈希值都相同才算 $\verb!TAK!$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
typedef unsigned int       u32;
typedef unsigned long long u64;
char c; int h1, h2, g1, g2, tmp, base1 = 1, base2 = 1;
const int BASE1 = 13331, MOD1 = 1e9 + 7;
const int BASE2 = 131  , MOD2 = 1e9 + 9;
int main(){
    while(!isalpha(c = getchar()));
    do{
        h1 = (1ll * h1 * BASE1 + c) % MOD1;
        h2 = (1ll * c * base1 + h2) % MOD1;
        base1 = 1ll * base1 * BASE1 % MOD1;
        g1 = (1ll * g1 * BASE2 + c) % MOD2;
        g2 = (1ll * c * base2 + g2) % MOD2;
        base2 = 1ll * base2 * BASE2 % MOD2;
    }while(isalpha(c = getchar()));
    puts(h1 == h2 && g1 == g2 ? "TAK" : "NIE");
    return 0;
}
```



---

## 作者：zgy_123 (赞：4)

祝大家 CSP 2023 J/S rp++！

---
首先，这题的空间显然不会让我们存下这么庞大的数组的，所以考虑小空间方法，也就是字符串哈希。

首先我们可以乱搞出如下的哈希函数：

$$hash_i=(\sum_{j=1}^{i}s_j\times 26^j)\bmod p$$

它的哈希值可以看作是一个 26 进制数，每一位存放着字符串的对应位。它也可以写作递推形式：

$$hash_i=(hash_{i-1}+26^i\times s_i)\bmod p$$

所以，每一次哈希相当于给原数前面补一位，那么反过来，将字符串倒转，然后哈希，其哈希值就等于每次在最后面补一位，写成递推式就是：

$$hash_i=(hash_{i-1}\times26+s_i)\bmod p$$

至此，我们就已经知道了问题的解决方式，加下来的细节就是代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define m 999983
#define t 26
int main(){
	int p=1,hsh1=0,hsh2=0;
	char ch=getchar();
	while(ch<'a'||ch>'z') ch=getchar();
	while(ch>='a'&&ch<='z'){
		hsh1=(hsh1*t+ch-'a')%m;
		hsh2=(hsh2+p*(ch-'a'))%m;
		p=p*26%m;
		ch=getchar();
	}
	if(hsh1==hsh2) cout<<"TAK";
	else cout<<"NIE";
	return 0;
}
//sto kkksc03 chen_zhe xht orz
//%%% YGL,RBB,RTY,XSY,LPZ,ivy_uu,asd %%%
//csp 2023 rp++
```

---
祝大家 rp++！！！

---

## 作者：Hulless_barley (赞：3)

当一个蒟蒻不会哈希，你可以将字符串转化成类似 $26$ 进制的东西。将前半段与后半段转化成 $26$ 进制并用 $10$ 进制表示出来。很轻松写出这样的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
char c;
int main(){
	cin>>n;
	for(int i=1;i<=(n>>1);i++){
		do c=getchar();while(!isalpha(c));
		x+=(c*(26+i));
	}
	if(n&1)getchar();
	for(int i=(n>>1)+1+(n&1);i<=n;i++){
		do c=getchar();while(!isalpha(c));
		y+=(c*(26+n-i+1));
	}
	if(x==y)cout<<"TAK";
	else cout<<"NIE";
	return 0;
}
```

很简单对吧？轻松获得 $30$ 分的~~好成绩~~（[测评结果](https://www.luogu.com.cn/record/154840953)）。忽视了 $n=0$ 的情况，不告诉你长度咋办？然后我就去网上搜了一下[哈希表](https://blog.csdn.net/Peealy/article/details/116895964)。

哈希和之前的思路差不多，定义两个整型，分别保存正推和逆推的答案，最后比较就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int q1=26,q2=1,s1,s2;
char c;
int main(){
	do c=getchar();while(!isalpha(c));
	while(isalpha(c)){
		c-='a';
		s1=s1*q1+c;
		s2=s2+q2*c;
		q2*=26;
		c=getchar();
	}
	cout<<(s1==s2?"TAK":"NIE");
	return 0;
}
```

神奇的是只有 $10$ 分了（[测评结果](https://www.luogu.com.cn/record/154925329)）。后来我想了一下，字符串太长了，可能爆 int 了，而且资料上好像取模了，那就取个模吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1145141919;
int q1=26,q2=1,s1,s2;
char c;
int main(){
	do c=getchar();while(!isalpha(c));
	while(isalpha(c)){
		c-='a';
		s1=(s1*q1+c)%mod;
		s2=(s2+q2*c)%mod;
		q2=q2*26%mod;
		c=getchar();
	}
	cout<<(s1==s2?"TAK":"NIE");
	return 0;
}
```

终于……还是 $10$ 分（[测评结果](https://www.luogu.com.cn/record/154927231)）。我冥思苦想许久之后，发现取模也不行，还是会爆 int。行，逼我发大招，`#define int unsigned long long int`。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long//这行语句多好
using namespace std;
const int mod = 1145141919;
int q1=26,q2=1,s1,s2;
char c;
signed main(){//一定是signed main！！！
	do c=getchar();while(!isalpha(c));//读入无用的字符
	while(isalpha(c)){
		c-='a';
		s1=(s1*q1+c)%mod;
		s2=(s2+q2*c)%mod;
		q2=q2*26%mod;
		c=getchar();
	}
	cout<<(s1==s2?"TAK":"NIE");
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/154927653)。

---

## 作者：banned_xiejiayun (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P6312)

### STEP1：简化题意

给定一个字符串，判断其是否为回文串。

### STEP2：思路分析

直接输入判断即可：

最后贴上代码：

#### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s,s1;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	int l=s.size();
	for(int i=l-1;i>=0;i--)s1+=s[i];
	if(s1==s)cout<<"TAK";
	else cout<<"NIE";
	return 0;
}
```
~~直接复制粘贴水题一道~~

[提交记录](https://www.luogu.com.cn/record/123820038)


~~细心的~~你一定发现了：

![](https://cdn.luogu.com.cn/upload/image_hosting/pe0fuh3i.png)

没错，内存超限。

注意题目说的是字符长度**字符串长度不超过两千万！** 

~~瞬间无语~~



------------


好，玩笑开够了。所以说，这道题不能一个串地读入，只能一个一个字符地挨个读。为了记录，我们就需要用到：

### 字符串哈希

不知道的点[这个](https://blog.csdn.net/Mikchy/article/details/103995537)。

据我的理解，字符串哈希就是将一个字符串转换为一个独有（即不可重复）的数字。

所以我们就定义 $c$ 是读入的字符，$x$ 是倒序字符串的编号（就先这么说吧），$y$ 是正序的，$base$ 是进制，$now$ 是 $base$ 的 $i$ 次方（第 $i$ 个字符）。

每次 $x$ 就要加上 $now$ 倍的 $c$（也可以减一个字符 $a$）,就是在当前数的前面添加一个 $c$。

而 $y$ 就加上 $c$ 过后乘以 $base$，可以理解为整体往后挪一位。

最后比较 $x$ 和 $y$ 是否相等即可。

## AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c;
unsigned long long x, y, now = 1;
const int mod = 1000039, base = 1000037;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while((c = getchar()) < 'a');//剔除不用的字符（反正把 n 读进来也没用）。
	for (; c >= 'a'; c = getchar()) {
		now = (now * base) % mod;
		x = (x + now * (c - 'a')) % mod;
		y = ((y + (c - 'a')) * base) % mod;
		//这些都说过了。
	}
	if (x == y)cout << "TAK";
	else cout << "NIE";
	return 0;
}

```
[提交记录](https://www.luogu.com.cn/record/123857260)

~~大片的 AC 看着好舒服。~~

---

## 作者：naroto2022 (赞：1)

# P6312 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P6312)

### 题意

题目的意思非常简单，就是给定一个字符串 $s$，问 $s$ 是否为回文串。

### 前置知识

1. 哈希

（没了，真的很简单）

### 思路（解法）

首先，哈希都会吧？不会的先看[这](https://www.luogu.com.cn/problem/P3370)。

其实判断回文最简单的就是分别求从头开始和从尾开始的哈希值，比较即可。

那么哈希值又是怎么求的呢？

先设 $a,b$ 分别为从头开始和从尾开始的哈希值。

求哈希值得：

$\begin{aligned} a=\sum_{i=1}^nbase^i\times s[i]\pmod m,b=\sum_{i=1}^nbase^{n-i+1}\times s[i]\pmod m\end{aligned}$

于是，我们就得到到了以下代码。

### 代码（$10$ 分）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int base=157;
const int mod=123456791;
const int MN=20000005;
int n,num[MN],a,b;
char s[MN];
bool flag;
void init(){
	num[1]=1;
	for(int i=2; i<=n; i++) num[i]=(num[i-1]*base)%mod; 
}
int main(){
	scanf("%d",&n);
	cin>>s+1;
	n=strlen(s+1);
	init();//预处理 
	for(int i=1; i<=n; i++){
		a=(a+s[i]*num[i])%mod;
		b=(b+s[i]*num[n-i+1])%mod;//哈希求值 
	}
	if(a==b) printf("TAK");
	else printf("NIE");
	return 0;
}
```

可以发现，这段代码成功的 MLE 了，所以我们就不能设数组，要将 $base$ 进行动态处理，且字符串也要拆成字符输入，于是就有。

### AC 代码（一点点小改动）

首先既然要拆成字符输入，不妨设 $hash1,hash2$ 分别为从头开始和从尾开始的哈希值。

于是易知：

$hash1_i=(hash1_{i-1}+base^i\times ch)$。

接下来考虑反过来的，其哈希值就等于每次在最后面补一位。

$hash2_i=(hash2_{i-1}\times base+ch)$。

于是代码就出来了：


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int base=157;
const int mod=123456791;
const int MN=20000005;
long long n,a,b,num=1;
char ch;
bool flag;
int main(){
	scanf("%lld",&n);
	while(1){
	    ch=getchar();
	    if(ch<'a'||ch>'z') break;
		a=(a*base+ch)%mod;
		b=(b+num*ch)%mod;
		num=num*base%mod;
	}
	if(a==b) printf("TAK");
	else printf("NIE");
	return 0;
}
```

---

## 作者：__Green_tick__ (赞：0)

# P6312 [PA2018] Palindrom
## 题目大意
判断一个字符串 $str$ 是不是回文串。

## 题目分析
时间限制：$\tt 1.00s$。\
内存限制：$\textcolor{red}{\tt 4.00MB}$。

很显然，如果我们开个字符串会直接 MLE。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
string str;
int main(){
	cin>>n; 
	cin>>str; //MLE
	string t=str;
	reverse(t.begin(),t.end());
	cout<<((str==t)?"TAK":"NIE")<<endl;
	return 0;
}
```

## 题目思路
### 字符串哈希
算出一个正序的哈希 $H_1$，再算出一个反的哈希 $H_2$。

#### 正的哈希
$$H_1=\sum^{n-1}_{i=0}bace^i\times str_i$$

#### 反的哈希
$$H_1=\sum^{n-1}_{i=0}bace^i\times str_{n-i-1}$$

---

### 现在我们逐个字符输入（节省内存）
```cpp
while(cin>>x){
  //TODO
}
```
#### 正的哈希
$$H_1=\sum^{n-1}_{i=0}bace^i\times x$$
即：
```cpp
while(cin>>x){
	Hash2=(Hash2+x*power)%Mod;//this
  power=power*Bace%Mod;//即如上 bace 的 i 次幂
}
```

#### 反的哈希
先将上式子变化：
$$H_1=\sum^{n-1}_{i=0}bace^{n-i-1}\times x$$
再变化：
$$H_1=(((0\times bace+x)\times bace+x)\dots)\times bace+x$$
即：
```cpp
while(cin>>x){
	Hash1=(Hash1*Bace+x)%Mod;//this
}
```

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long Bace=131;
const long long Mod=1e9+7;
unsigned long long Hash1;
unsigned long long Hash2; 
long long n;
unsigned long long power=1;
char x;
int main(){
	cin>>n;
	while(cin>>x){
		Hash1=(Hash1*Bace+x)%Mod;
		Hash2=(Hash2+x*power)%Mod; 
		power=power*Bace%Mod;
	}
	cout<<((Hash1==Hash2)?"TAK":"NIE")<<endl;
	return 0;
}
```
最后，以一句话结束：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

## 作者：Il1_1_3 (赞：0)

# P6312 Palindrom 题解

UPD on 2024/10/23：加入了进制哈希的解释。  
UPD on 2024/10/28：修改两处导致编译器警告的代码错误。

## 题意描述

给定一个字符串，判断它是否回文，如果回文，输出 `TAK`，否则输出 `NIE`。

## 思路

这题内存 $\texttt{4MB}$，字符长度又到了两千万，直接一股脑输入肯定会爆，~~不要问我是怎么知道的，
我愿称之为没（M）了（L）鹅（E）~~。

所以要有一种空间小一些的方法，就是用[**伟大的哈希**](https://www.luogu.com.cn/problem/P3370)，一位一位处理。

什么？你说你不会哈希？

好吧，介绍一种最基础的哈希——进制哈希。即将字符串的每一个字母看成一个 $bas$ 进制的数，每一位对应一个位值和一个它本身的数值。例如当 $bas$ 取 $131$ 且字符对应值为它的 ASCII 码的时候，字符串 `ILCd` 的哈希值计算方式为：

$$
73 \times bas^3 + 76 \times bas^2 + 67 \times bas^1 + 100 \times bas^0
$$

一定要记得模大素数，防止炸 `int` 或 `long long`，但与之而来的就有一个问题：模完之后可能有重复！但对付这道题足够了。如果想学更强大的哈希，可以去 [P3370](https://www.luogu.com.cn/problem/P3370) 的题解区，欣赏更多 dalao 们完美的解答。

因为要判断回文数，所以要把字符串的哈希值算两遍，**一次正着，一次反着**。设两次运算哈希值为 $x,y$，则有：

$$
x = (\sum_{i = 1}^{n} bas^i \times str_i) \bmod \; prim
$$

$$
y = (\sum_{i = 1}^{n} bas^{n - i + 1} \times str_i )\bmod \; prim
$$

其中 $bas$ 为进制（本题中我使用 $131$），$bas^i \times str_i$ 为每一位的位值，最后再模一个大质数就可以算出该串的哈希值。

###### 都让一让，$\Huge\textup{\textbf坑}$ 来了！

这里注意，**一定不能输入完再用 for 语句遍历，要一遍一遍地用 getchar 输入字符，计算一位再输入一位，就不会 $\texttt{MLE}$。**

由上式可得计算的递推式为：

$$
x_i = (x_{i-1} + str_i \times bas^i) \bmod \; prim
$$

$$
y_i = (y_{i-1} \times bas + str_i) \bmod \; prim
$$

直接写代码：
```cpp
#include<bits/stdc++.h>
#define bas 131
#define prim 998244353
#define int long long
using namespace std;
int n,x,y,bpi=1;
char st;
bool flag=0;//判断回车
signed main()
{
	scanf("%lld",&n);
	while(true)
	{
	    st = getchar();
	    if(((int)st<20)&&flag==0)//回车会有大问题
	    {
	        flag=1;
	        continue;
	    }
	    if(st < 'a' || st>'z') break;//不是字母就结束
		x = (x+bpi*st)%prim;
		y = (y*bas+st)%prim;//两个递推式
		bpi = bpi*bas%prim;//bpi表示bas的i次方，这样就不用加变量了
	}
	if(x==y) cout << "TAK";
	else cout << "NIE";
	return 0;
}
```

特别感谢：@皎月半洒花 在 P3370 的题解。

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
如果只是单纯的盘回文串，那么这题相当轻松。

但是，内存上限不允许开数组。

所以考虑在读入的同时哈希。
## 实现
读入无用字符：

```cpp
  k=getchar();
  while(k<'a'||k>'z')k=getchar();
```
哈希：

```cpp
	while(k>='a'&&k<='z'){
		ha1=(ha1*26+k)%mod;//正方向
		ha2=(ha2+k*cf)%mod;//反方向
		cf*=26;//反方向几次方
		cf%=mod;
		k=getchar();
	}	
```
正方向是正常的按进位处理。

反方向则用 cf 记录到第几位。

判断：

```cpp
	if(ha1==ha2)cout<<"TAK";
	else cout<<"NIE";
```
## 哈希是什么
简单来说，就是将一个字符串当作一串 26 进制数处理。

[详解](https://oi-wiki.org/string/hash/)。

---

## 作者：zxh923 (赞：0)

# P6312 [PA2018] Palindrom 题解

[题目传送门](https://www.luogu.com.cn/problem/P6312)

### 思路

发现空间给的非常小，根本存不下字符串 $s_i$，于是我们考虑哈希。

我们定义 $f_i$ 为从前到后的哈希数组，$g_i$ 为从后到前的哈希数组。

我们这里定义 $t=131$，$n$ 为字符串长度。

根据哈希的计算方法有 $f_i=f_{i-1}+s_i\times t^i$，同理 $g_i=g_{i-1}\times t+s_i$。

我们只需判断 $\displaystyle\sum_{i=1}^nf_i$ 是否等于 $\displaystyle\sum_{i=1}^ng_i$ 即可。

当然为了防止溢出，这两个数组需要对一个数取模，这个数可以自定。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,k1,k2,now=1,k;
char x;
signed main(){
	cin>>n;
	while(cin>>x){
		k=x-'a'+1;
		k1=(k1+k*now)%mod;
		k2=(k2*131+k)%mod;
		now=now*131%mod;
	}
	cout<<(k1==k2?"TAK":"NIE");
    return 0;
}
```

---

## 作者：Left_i_Forever (赞：0)

原来哈希有这种用法，学到了。

因为只用得到整个字符串的哈希值，就不用存储中间的值，而且也不用存储 base 的各个次方，现求现用。倒序的就像求数字的反序数一样即可（注意能不取模就不取，容易超时）。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int base = 131, mod = 998244353;
int z, d, b = 1;

signed main()
{
    int n;
    cin >> n;
    char c;
    while (cin >> c)
    {
        z = (z + c * b) % mod;
        d = (d * base + c) % mod;
        b = b * base % mod;
    }
    if (z == d) puts ("TAK");
    else puts ("NIE");
    return 0;
}
```

---

