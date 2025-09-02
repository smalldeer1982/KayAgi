# Strings of Monody

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/tcsfyv6l.png)

LGD 是一只喜欢 Monody 的小恐龙。

根据 Monody 的音乐，他建立了一个模型，叫做 赞歌字符串。简称， SoM (String of Monody)。


## 题目描述

赞歌字符串是一个由 $1,4,5$ 组成的字符串。每次操作 LsWn 会拿出左端点为 $l$，右端点为 $r$ 的子串，（注意，第一个字符的下标为 $1$，最后一个字符的下标为 $n$）并把它替换为新的给出的子串。替换之后，你需要回答 $3$ 个对于完整串的问询，分别是：  
1. $1$ 的个数。  
2. 整个字符串每个数位的总和。  
3. 整个字符串每个数位的乘积。

所有输出都要对 $\color{black}998\color{red}24\color{black}353$ 取模。  



## 说明/提示

样例一的解释：  

第一次操作，字符串变为 ```111514``` ，其中 $1$ 的个数为 $4$，和为 $1+1+1+5+1+4=13$，乘积为 $1\times 1\times 1\times 1\times 5\times 1\times 4=20$。   
第二次操作，字符串变为 ```114414```。   
第三次操作，字符串变为 ```114514```。  

---

我们设初始字符串长度为 $n$。  

对于 $10\%$ 的数据，$n\le 10$。   
对于 $40\%$ 的数据，$n\le 1000$。  
对于全部数据，$n\le 10^6, m\le 10^3, 1\le r-l+1\le 10^3$。


## 样例 #1

### 输入

```
114514
3
1 3 111  
3 4 44
4 4 5```

### 输出

```
4 13 20
3 15 64
3 16 80```

# 题解

## 作者：Ptilopsis_w (赞：6)

这道题的题意很简单这里就不赘述了  

首先看数据范围,$n<=10^6$, $m<=10^3$,肯定不能暴力求解了，但是对于这道题，$1,4,5$的所在位置对答案没有影响，**所以我们可以分别记录$1,4,5$的数量，每次修改时维护这个数量就可以了**,但是每次询问乘积时如果直接求的话会TLE,所以我们可以预处理出$4,5$的次幂来，每次询问直接调用就好了

注意模数是99824353，不要想当然 ~~(Ctrl+C是个好东西)~~

下面是代码详解
```cpp
#include<bits/stdc++.h>
#define MAXN 1000000
using namespace std;
typedef long long ll;
int m, tot[6], a[MAXN+5];
ll pow4[MAXN+5], pow5[MAXN+5];
const ll mod = 99824353;
int main()
{
	pow4[0] = pow5[0] = 1;//预处理4,5的次幂
	for(int i = 1; i <= MAXN; i++)
		pow4[i] = (pow4[i-1]*4) % mod, pow5[i] = (pow5[i-1]*5) % mod;
	char ch;
	int cnt = 0;
	while(ch = getchar(), ch != '\n')
	{//逗号表达式返回最后一个语句的值,这个while就是每次读入一个字符存到ch里,如果ch是换行就结束循环
		cnt++;
		a[cnt] = ch-'0';
		tot[a[cnt]]++;//数据只有1,4,5，可以直接用数组下标对应
	}
	scanf("%d", &m);
	while(m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);getchar();//注意这里要先用一个getchar()读掉r后面的空格,不然会RE
		for(int i = l; i <= r; i++)
		{
			int x = getchar()-'0';
			tot[a[i]]--;//原a[i]对应的数的数量减一
			tot[x]++;//新a[i]对应的数的数量加一
			a[i] = x;//一定要把a[i]换掉,不然重复更新的时候会出错
		}
		ll sum = (tot[1] + 4*tot[4] + 5*tot[5]) % mod;
		ll p = (pow4[tot[4]] * pow5[tot[5]]) % mod;//已经预处理过4,5的次幂了,直接调用就可以 (没有1的原因都懂)
		printf("%d %lld %lld\n", tot[1], sum, p);//注意longlong要用%lld,不然会见祖宗的
	}
	return 0;
}
```

---

## 作者：lycx03 (赞：4)

乍一眼还以为要线段树，后来发现其实很简单。
题目要求的是：
1. 1 的个数。
1. 整个字符串每个数位的总和。
1. 整个字符串每个数位的乘积。

然后我们发现字符串组成的数字只有 $1$ $4$ $5$ 3种，所以解决三个问题只需要分别统计出 $1$ $4$ $5$ 三个数的个数。

对于问题一，直接输出即可；对于问题二，把3个数字分别以数值乘以出现次数相加求和即可；对于问题3，由于每次计算成绩消耗时间过大，我们可以考虑**预处理**每个数的 $k$ 次方，然后直接带入得解。

继续……

先统计原串个数字个数，每次修改的时候可以顺带把数字个数统计出来，按上述方法计算输出即可。

下面是代码（应该都能看懂吧）：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000011],a[1000011];
int n,m,l,r,h[11],mod=99824353,q4[1000011],q5[1000011];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d",&m);
	for(int i=1;i<=n;i++) h[s[i]-48]++;
	q4[0]=q5[0]=1;
	for(int i=1;i<=1000000;i++) q4[i]=(q4[i-1]*4)%mod,q5[i]=(q5[i-1]*5)%mod;
	while(m--)
	{
		scanf("%d%d%s",&l,&r,a);
		for(int i=l;i<=r;i++) h[s[i]-48]--,h[a[i-l]-48]++,s[i]=a[i-l];
		printf("%d %d %lld\n",h[1],h[1]+h[4]*4+h[5]*5,(long long)(q4[h[4]])*(q5[h[5]])%mod);
	}
	return 0;
}
```


---

## 作者：pocafup (赞：3)

好久之前比赛打的，然后众所周知我这个菜鸡打比赛不带脑子，于是就硬上了一波线段树（不过好像挺快就写出来了

思路其实没什么特别的。如果这题要上线段树的话，其实就是给你一个板子，要求支持单点修改，区间和，区间乘和某个数字的个数。

某个数字的个数只需要预处理出来，在修改的时候统计即可。

具体为如果修改的数为 1 而原本不为 1，那么 1 的个数++。反之如果原本的数为 1 修改后不为 1， 1 的个数++。其他情况不变个数不变。

注意修改后要更新某个位置的数字。

区间和和区间乘就不讲了，不会的左转模板线段树 2

代码：
```
#include <iostream>
#include <algorithm>

using namespace std;
#define lson (way<<1)
#define rson (way<<1|1)
#define mid (l+r)/2
const int MAXN = 1e6+5;
const int mod =99824353;
long long n,pos[MAXN],m,ans1,ans2,ans3=1;
long long seg[MAXN<<2][2];
inline void build(int way, int l, int r){
  if (l==r) {seg[way][0] = seg[way][1] = pos[l];return;}
  build(lson,l,mid);
  build(rson,mid+1,r);
  seg[way][0]=(seg[lson][0]+seg[rson][0])%mod;
  seg[way][1]=(seg[lson][1]*seg[rson][1])%mod;
}
inline void update(int way, int l, int r, int qlow, int val){
  if (l==r && r==qlow) {
    seg[way][0] = seg[way][1] = val;
    return;
  }
  if (mid>=qlow) update(lson,l,mid,qlow,val);
  else update(rson,mid+1,r,qlow,val);
  seg[way][0]=(seg[lson][0]+seg[rson][0])%mod;
  seg[way][1]=(seg[lson][1]*seg[rson][1])%mod;
}
inline int read(){
    register int a=0,f=1;register char c;
    while((c=getchar())<'0')if(c=='-')f=-1;;
    while(c>='0')a=a*10+(c^48),c=getchar();
    return a*f;
}
string s;
int main(){
  ios_base::sync_with_stdio(0);
  cin >> s;
  for (int i=1;i<=s.length();i++) {
    pos[i]= (int)s[i-1]-48;
    ans1+=(pos[i]==1);//统计1
  }
  n = s.length();
  build(1,1,n);
  cin >> m;
  for (int l,r, i=1;i<=m;i++){
    cin >> l >> r >> s;
    int curr = -1;
    for (int j=l;j<=r;j++){
      int now = (int)(s[++curr]-48);
      ans1+= (now==1) - (pos[j]==1);
      update(1,1,n,j,now);//线段树更新
      pos[j] = now;//注意更新时要把这个位置的数更了，要不统计1的数量会出错
    }
    printf("%d %d %d\n",ans1,seg[1][0],seg[1][1]);
  }
}

```

---

## 作者：Collapsar233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6553)

## 题目描述

修改一个由 $1,4,5$ 组成的字符串，每次修改后计算 $1$ 出现的次数，每个数位的总和，每个数位的乘积，结果对 $99824353$ 取模。

## 分析

考虑到数据范围是 $n\le 10^6, m\le 10^3, 1\le r-l+1\le 10^3$ ，如果每次都求整段肯定会超时，所以我们只计算修改的区间。

- 统计 $1$ 的个数：遍历修改前区间和修改后区间即可。
- 计算数位和：计算修改前区间数位和，修改后的区间数位和，计算即可。

以上两问都非常简单，那么如何计算修改后的数位积呢？

阅读题目，发现每次计算时都需要对结果取模，而取模又是不符合分配律的，即：

$(a \div b) \bmod p \ne ( a \bmod p \div b \bmod p ) \bmod p$

因此，我们需要求一个叫做**逆元**的东西，来计算 $(a \div b) \bmod p$ 的值。

我们设 $b$ 的逆元为 $b^{-1}$ 。

则 $(a \div b) \bmod p = (a * b^{-1}) \bmod p$

简单来说，**在模的意义下，除以一个数等于乘这个数的逆元**。

所以，我们要求出修改前的区间数位积的逆元，然后就能求出修改区间以外的数位积，再求修改后区间的数位积，相乘取模后即可获得整个区间的数位积。

我们发现， $99824353$ 为质数，而**对于质数取模求逆元**，可以想到使用**费马小定理**，即

> $p$ 为质数时， $a^{p-2} \equiv a^{-1} \left ( \bmod \space p \right )$ 。

求出修改前区间的数位积的逆元 $inv$ ，修改前整体数位积 $oc$ 和修改后区间数位积 $nc$ ，那么新串整体的乘积为 $oc \times inv \times nc$ ，即为所求结果。

**注意对结果取模**

代码如下


```cpp
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

template<typename T>
void read(T& x) {
	x = 0;
	bool sgn = false;
	char ch = getchar();
	while (ch < 48 || 57 < ch) {
		sgn ^= ch == '-';
		ch = getchar();
	}
	while (48 <= ch && ch <= 57) {
		x = x * 10 + (ch ^ 48);
		ch = getchar();
	}
	x = sgn ? -x : x;
	return;
}

const int maxn = 1e6+7;
const ll mod = 99824353;

char str[maxn];
ll n, m, a[maxn], sum, cdt = 1, cnt1;// sum 为数位和， cdt 为数位积， cnt1 为 1 的个数

// 快速幂
ll ksm(ll a, ll p) {
	ll res = 1;
	while (p > 0) {
		if (p & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		p >>= 1;
	}
	return res;
}

// 费马小定理求逆元
ll inv(ll x) {
	return ksm(x, mod - 2);
}

int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++i) // 计算初始数位和，数位积， 1 的个数
		a[i] = str[i] ^ 48, sum = (sum + a[i]) % mod, cdt = (cdt * a[i]) % mod, cnt1 += (a[i] == 1);
	read(m);
	int l, r;
	while (m--) {
		read(l), read(r);
		scanf("%s", str + 1);
		int len = r - l + 1;
		ll c = 1, s = 0, c2 = 1, s2 = 0, cur;
		for (int i = 1; i <= len; ++i) {
			cur = a[l + i - 1], c = (c * cur) % mod, s = (s + cur) % mod; // 修改前区间属性
			if (cur == 1)
				--cnt1;
			a[l + i - 1] = str[i] ^ 48;
			cur = a[l + i - 1], c2 = (c2 * cur) % mod, s2 = (s2 + cur) % mod; // 修改后区间属性
			if (cur == 1)
				++cnt1;
		}
		sum = sum - s + s2; // 修改数位和
		cdt = (((cdt * inv(c)) % mod) * c2) % mod; // 修改数位积
		cout << cnt1 << " " << sum << " " << cdt << "\n";
	}
	return 0;
}
```

---

## 作者：mot1ve (赞：1)

//其实这题不用开桶，直接三个变量记录就可以，注意，计算乘积的时候可以优化，$O(n)$ 预处理出 $1,4,5$ 的 $x$ 次方，这样就可以 $O(1)$ 用了。
```
#include<bits/stdc++.h>
using namespace std;
const int mod=99824353;
int a,b,c,m;//a记录1的个数，b记录4的个数，c记录5的个数 
string str1,str2;
int k,p;
int c4[1000010],c5[1000010];
int main()
{
	c4[0]=1,c5[0]=1;
	for(int i=1;i<=1000000;i++) 
	{
		c4[i]=(c4[i-1]*4)%mod;
		c5[i]=(c5[i-1]*5)%mod;
	}
	cin>>str1;
	cin>>m;
	for(int i=0;i<str1.size();i++)
	{
		 if(str1[i]=='1')
		 a++;
		 if(str1[i]=='4')
		 b++;
		 if(str1[i]=='5')
		 c++;
	}
	while(m--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		cin>>str2;
		l-=1,r-=1,p=0;
		for(int i=l;i<=r;i++)
		{
			if(str1[i]=='1')
			a--;
			if(str1[i]=='4')
			b--;
			if(str1[i]=='5')
			c--;
			if(str2[p]=='1')
			a++;
			if(str2[p]=='4')
			b++;
			if(str2[p]=='5')
			c++;
			str1[i]=str2[p++];
		}
		printf("%d %d %d\n",a,a+4*b+5*c,(1ll*c4[b]*c5[c])%mod);
	}
	return 0;
} 
```

---

## 作者：血色黄昏 (赞：1)

此题竟然有点卡python，不开森/kk

~~400ms的时间是有毒吗~~

第一眼看上去就准备上线段树了，结果发现我个菜鸡不会处理字符串/kk

看了下数据，就决定打优化过的暴力了

作为普及-的题目，直接暴力的复杂度是O(nm)，1e9绝对超出时间限制，考虑优化，每次只算更改部分的变化，复杂度为O(m(r-l+1)，不超过1e6，可以跑过去。

代码非常简单，思路其实也很简单，代码基本每行都有注释，容易食用

# Code
```python
n = input()#输入n
m = int(input())#输入m
ans1 = 0#记录每次的和
c4 = n.count('4')#4出现次数
c5 = n.count('5')#5出现次数
c1 = n.count('1')#6出现次数
for i in n:#计算出原来的和
    ans1 += int(i)
for i in range(m):#m次问答
    s = input().split()#python每次读入一行
    l, r, s = int(s[0]), int(s[1]), s[2]#赋值给lrs
    s1 = n[l - 1: r]#截取出要替换的那一段
    ans2 = 0#计算和更改了多少
    for j in range(len(s)):
        ans2 += int(s[j]) - int(s1[j])#计算每位上的增加
    c1 += s.count('1') - s1.count('1')#计算增加的1的个数
    c4 += s.count('4') - s1.count('4')#计算增加的4的个数
    c5 += s.count('5') - s1.count('5')#计算增加的5的个数
    ans1 += ans2#计算出更改后的和
    n = n[:l-1] + s + n[r:]#替换字符串
    print(c1, end=' ')#输出1的个数
    print(ans1, end=' ')#输出和
    print(4 ** c4 * 5 ** c5)#输出积，python自带快速幂


```

祝大家暑假快乐~

---

## 作者：青鸟_Blue_Bird (赞：1)

蒟蒻来一发题解。

首先，最容易想到的就是暴力了。但是那样容易T掉。
然后，看一下题目，考虑如何化简我们的暴力。

题目中的数字只可能有1、 4、 5三种数字。这样就好办了。

首先，我们开3个数组，维护我们数列中有多少个1,4,5.
对于问题1，直接输出。

对于问题2，还是直接计算输出。（直接手摸乘法算式，这都会吧）。

其次，对于乘法的询问，我们直接预处理出所有4和5的次方。

然后全部直接输出就好了。

上代码：：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 10000100
#define mod 99824353

inline int read(){
	int x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-')s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s; 
}

int Log4[N], Log5[N];
int num[666];
char s[N], a[N];

int main(){
	cin >> s + 1;
	int n = strlen(s + 1);
	for(int i = 1;i <= n; i++)
		num[s[i] - '0']++;
	Log5[0] = Log4[0] = 1;
	Log5[1] = 5; Log4[1] = 4;
	for(int i = 2;i <= (int)1e6; i++)
		Log5[i] = (Log5[i - 1] * 5) % mod, Log4[i] = (Log4[i - 1] * 4) % mod;
	int m = read();
	while(m--){
		int l = read(), r = read(); cin >> a;
		for(int i = l;i <= r; i++){
			num[s[i] - '0']--; num[a[i - l] - '0']++; s[i] = a[i - l];
		}
		printf("%d %d %lld\n", num[1], num[1] + (num[4] << 2) + (num[5] * 5) % mod, (long long)Log4[num[4]] * Log5[num[5]] % mod);
	}
	return 0;
}
```


---

## 作者：Into_qwq (赞：1)

日常写题解

咳咳，我最喜欢用的STL容器就是$map$了，这题我就用了$map$

$map$，也就是红黑树，表现的是键->值的映射

$map$重点：

1.头文件：万能头 或用 #$include$<$map$>

2.定义方式：$map$ <类型，类型> 名称;//类型指随意类型，比如说：$int$，$bool$，$string$...

$e.g.$ $map$<$int,char$> $p$; 　 $map$<$string,char$> $p$;

3.$map$容器最大的优点就在于它可以快速定位并读取某一键值的元素

4.用下标访问$map$中不存在的元素时，将导致向$map$中添加该下标所指向的新元素

其值会根据类型默认值默认构造函数进行初始化（如$int$初始化为$0$,$string$初始化为""）。

代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod=99824353;

char a[1000100],b[1000100];

inline ll read(){//快读
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void output(ll x) {//快输
	if(x/10) output(x/10);
	putchar(x%10+'0');
}

ll j[1000100]={1},k[1000100]={1};//分别记录4的n次幂和5的n次幂
map<char,ll> p;//记录
int main()
{
 	scanf("%s",a);
 	ll len=strlen(a);
 	for(ll i=0;i<len;++i) ++p[a[i]];//记录
    //cout<<p['1']<<endl<<p['4']<<endl<<p['5']<<endl;
 	ll n;
 	n=read();
    for(ll i=1,s=1,t=1;i<=1000001;++i){//预处理4的n次幂和5的n次幂
		s=s*4%mod;
		t=t*5%mod;
        j[i]=s;
        k[i]=t;
	}
 	while(n--)
 	{
 		ll l,r;
 		l=read(),r=read();
 		scanf("%s",b);
 		for(ll i=l-1;i<=r-1;++i){
 			--p[a[i]];
            //cout<<p['1']<<endl;
 			++p[b[i-l+1]];
            //cout<<p['1']<<endl;
 			a[i]=b[i-l+1];
		}
		output(p['1']);
        putchar(' ');
        output((p['1']+p['4']*4+p['5']*5)%mod);
        putchar(' ');
        output(j[p['4']]*k[p['5']]%mod);
        puts("");
    }
 	return 0;
}

```

---

## 作者：happybob (赞：0)

这里提供一种无脑的非数据结构方法。

很明显不能暴力，我们尝试记录下字符串 `1`、`4`、`5` 出现次数，这样单次修改时可以做到最坏 $O(n)$ 的复杂度，与暴力一样。但是询问可以做到 $O(\log_2 n)$ 复杂度，也就是快速幂的复杂度。

但是为了区别与其他题解：

我用哈希！

哈希通常是字符串哈希，但是单个字符不也可以哈希吗？因为我哈希没学好，所以我们预处理时用 `rand()` 函数随机找到一个值，在哈希时与 `char` 类型字符哈希。加上快速幂和各种玄学优化。

但是明显我们可以预处理，因为只会出现 `1`、`4`、`5`，所以考虑预处理 `1`、`4`、`5` 的哈希值，这样就无需重复计算。

至于时间，也不是很长，不开 O2 也就 $160ms$。

不过好歹能过，$100ms$ 限制有点毒瘤啊！

代码过长，点[这里](https://www.luogu.com.cn/paste/ynleg1lz)。

---

## 作者：asasas (赞：0)

这题很容易想到暴力枚举替换，然后在扫一遍，进行1,2,3操作。但观察数据范围：$n<=10^6,m<=10^3$ 暴力显然超时，于是我们需要优化。

首先，我们把原字符串中的1,4,5的个数算出。在替换的时候，就可以把替换掉后1,4,5的个数统计出来，这样就可以把一个$O(n*m)$的程序改为$o(m*(r-l+1))$的程序。这是第1,2问的答案就出来了。

然后，我们再来处理第3问。显然暴力算乘法会超时，所以我们就要用到**快速幂**去计算。

最后，请注意模数是998**24**353，而不是998**244**353，这也告诉我们：要仔细读题，不能靠自己的经验就打代码。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll mod=99824353;
ll ksm(ll a,ll b){//快速幂
	ll ans=1,p=a;
    while(b>0){
        if(b%2!=0)
        ans=ans*p%mod;
        p=p*p%mod;
        b=b>>1;   
    }
    return ans;
} 
char a[1000005],b[1000005];
int main(){
    long long y,a1=0,a2=0,a3=0,a4=0;
    cin >> a;
    int n=strlen(a);
    int m;
    scanf("%d",&m);
    for (register int i=0;i<n;i++){
    	if (a[i]=='1') a1++,a4++;
    	else if (a[i]=='4') a2++;
    	else a3++;
    }//先统计出1,4,5的个数
    while(m--){
    	long long ans=1,sum=0,now=0;
    	int l,r;
    	cin >> l >> r >> b;
    	for (register int i=l-1;i<=r-1;i++){
		    if (a[i]=='1') a1--,a4--;
		    else if (a[i]=='4') a2--;
		    else a3--;
		    a[i]=b[i-l+1];
		    if (b[i-l+1]=='1') a1++,a4++;
		    else if (b[i-l+1]=='4') a2++;
		    else a3++;//在替换的时候就改变1,4,5的个数
		}
    	printf("%lld %lld %lld\n",a4,a1+a2*4+a3*5,(ksm(4,a2)*ksm(5,a3))%mod);//输出三个问题的答案
    }
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的字符串 $s$（仅包含 $1,4,5$ 三种字符，$n$ 在本题中无需输入），有 $m$ 个操作，每次操作给定两个整数 $l,r$，再给定一个字符串 $s'$，将 $s$ 的从 $l$ 到 $r$ 的子串换成 $s'$。请在每次操作后求出：

1. 字符串中 $1$ 的个数。
2. 字符串中所有数的总和。
3. 字符串中所有数的乘积。

以上数据都要对 $9982\color{red}\text{43}\color{black}\text{53}$ 取模（注意！不是 $998244353$）。

**数据范围：$n\leqslant 10^6,m\leqslant 10^3,1\leqslant r-l+1\leqslant 10^3$。**
## Solution
这道题目看上去比较麻烦，其实只需要暴力模拟就可以搞定。

首先，我们可以看到，每次的变换范围不会超过 $10^3$，所以，我们可以考虑一种 $\mathcal{O}(m(r-l+1))$ 的算法——每次只考虑变换要变换的子串，然后更新要求的三个问题的答案。

我们可以开一个计数器 $ans_1,ans_4,ans_5$（$ans_i$ 表示 $i$ 在字符串中出现的次数），每次操作就要更新着三个计数器的值，那么三个问题的答案就是 $ans_1,ans_1+4\times ans_4+5\times ans_5,4^{ans_4}\times5^{ans_5}$（至于第三个答案为什么不需要乘 $1^{ans_1}$ 大家应该都弄得明白，在此不再赘述）。

这里幂次方取模明摆着用[快速幂](https://www.luogu.com.cn/problem/P1226)轻松搞定。

最后一点坑的就是：注意模数，不是 $998244353$，这里应该是 $99824353$，少了一个 $4$！

总体来说难度不算太大，但要考虑的细节却不少。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

typedef long long ll;
ll quickpow(ll a, ll b, ll p) {
	if(p == 1)	return 0;
	ll res = 1;
	b %= p;
	for(; b; b >>= 1) {
		if(b & 1)	res = res * a % p;
		a = a * a % p;
	}
	return res;
} 
ll n, m, sum1, sum, mul = 1, aa[17];
char s[1000007];

void test1() {
	printf("%lld %lld %lld\n", aa[1], aa[4], aa[5]);
}

int main() {
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	for(int i = 1; i <= n; ++i)	aa[s[i] - '0']++;
//	test1();
	while(m--) {
		char tmp[1007];
		int xx, yy;
		scanf("%d%d%s", &xx, &yy, tmp + 1);
		for(int i = 1; i <= yy - xx + 1; ++i) {
//			printf("%c %c\n", s[xx + i - 1], tmp[i]);
			aa[s[xx + i - 1] - '0']--;
			aa[tmp[i] - '0']++;
			s[xx + i - 1] = tmp[i];
		}
//		test1();
		printf("%lld %lld %lld\n", aa[1], (aa[1] + aa[4] * 4 + aa[5] * 5) % 99824353, (quickpow(4, aa[4], 99824353) * quickpow(5, aa[5], 99824353)) % 99824353);
	}
	return 0;
}
```

---

## 作者：Error_Eric (赞：0)

日常题解。

~~为什么巨佬都是用线段树等高端操作做的啊？线段树是普及-难度？~~

思路：模拟就可以了，用num记录每个数字出现的次数，然后用记忆化搜索的思路优化一下4,5的n次幂 ~~（明明是不会快速幂）~~。

具体看代码：

```
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define modd 99824353
string gt,w;//gt是用于更换的字符串,w是用于存储的字符串。
long long  num1=0,num4=0,num5=0;
//num[i]存储i出现的次数，由于i只有三个就不开数组了。
long long  f4[10000000]={1,4,16},f5[10000000]={1,5,25};
//f4[i]存储4的i次幂,f5[i]存储5的i次幂。
inline long long q4(long long x){//4的x次幂
	if(f4[x]) return f4[x];//已经计算过
	else return f4[x]=q4(x-1)*4%modd;//没有计算过
}
inline long long q5(long long x){//5的x次幂
	if(f5[x]) return f5[x];//已经计算过
	else return f5[x]=q5(x-1)*5%modd;//没有计算过
}
inline long long readln(){//快速输入
    long long  x=0;
    char ch=getchar();
    while(ch<'0' or ch>'9')
        ch=getchar();//没有负数,无需特判'-'
    while(ch>='0' and ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
void solve(){//核心代码
	long long  l=readln(),r=readln();//输入l,r
	cin>>gt;//输入字符串
	for(long long  i=0;i<=r-l;i++){
		switch(gt[i]){//如果gt[i]是...
			case '1': ++num1;break;//...1,那么1的个数增加一个
			case '4': ++num4;break;//...4,那么4的个数增加一个
			case '5': ++num5;break;//...5,那么5的个数增加一个
			default: break; 
		}
		switch(w[l+i-1]){//原来的字符串w[i]是...
			case '1': --num1;break;//...1,那么1的个数减少一个
			case '4': --num4;break;//...4,那么4的个数减少一个
			case '5': --num5;break;//...5,那么5的个数减少一个
			default: break; 
		}
		w[l+i-1]=gt[i];//更换字符
	} 
	printf("%lld %lld %lld\n",num1%modd,(num1+num4*4+num5*5)%modd,q4(num4)*q5(num5)%modd);//输出
	
}
int main(){
	cin>>w;//输入原有字符串
	for(long long i=0;i<w.length();i++){//初始化
		switch(w[i]){
			case '1': ++num1;break; 
			case '4': ++num4;break;
			case '5': ++num5;break;
			default: break;
		}
	}
	long long  m=readln();
	while(m--)
		solve();//更换+输出
	return 0;
} 
```

---

## 作者：KadiaNEFU (赞：0)

看完dalao的题解，觉得我的题解就很呆????

一看n=1e6，这是要线段树呀，再看每次替换的1e3（嗷 还好还好）。

**思路：暴力，计算每一种数替换后出现的个数，由于每次只改变了一部分，所以只需要算改动的这一部分的变化就行**

核心：

- 记录1、4、5出现的次数

- replace函数的使用

- 快速幂的运用 (此处注意乘积取模=分别取模再乘起来取模)

**code中有详细注释**

```cpp
#include <bits/stdc++.h>

using namespace std;
const int mod=99824353;
long long ksm(long long x,int y,int m)
{
    if(y==0)
        return 1;
    int t;
    t=ksm(x*x%m,y/2,m)%m;
    if(y&1)
        t=(t*x)%m;
    return t%m;
}
int main()
{
    string stds,s;
    stds="0";//顺便用个字符占0的位置，方便操作
    cin >> s;
    stds+=s;//形成初始字符串
    int m;
    cin >> m;
    int a,b;
    int ans1=0,ans2=0,ans3=0;//分别表示1、4、5出现的次数
    for(int i=1; i<stds.size(); i++)
    //计算初始字符串中的1、4、5出现的次数
    {
        if(stds[i]=='1')
            ans1++;
        if(stds[i]=='4')
            ans2++;
        if(stds[i]=='5')
            ans3++;
    }
    for(int i=1; i<=m; i++)
    {
        cin >> a >> b >> s;
        for(int i=a;i<=b;i++)//将原字符串中1、4、5减去
        {
            if(stds[i]=='1')
                ans1--;
            if(stds[i]=='4')
                ans2--;
            if(stds[i]=='5')
                ans3--;
        }
        for(int i=0;i<s.size();i++)//添加新字符串中1、4、5
        {
            if(s[i]=='1')
                ans1++;
            if(s[i]=='4')
                ans2++;
            if(s[i]=='5')
                ans3++;
        }
        stds.replace(a,b-a+1,s);//更新字符串
        cout << ans1 << " " << ans1+ans2*4+ans3*5 << " " << (ksm(4,ans2,mod)*ksm(5,ans3,mod))%mod << endl ;//计算结果
    }
    return 0;
}

```


---

