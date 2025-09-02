# String Transformation

## 题目描述

设 $s$ 为一个长度为 $n$ 的字符串，其字符编号为 $0$ 到 $n-1$，$i$ 和 $j$ 为整数，满足 $0 \leq i < j < n$。我们定义函数 $f$ 如下：

$$
f(s, i, j) = s[i+1\ldots j-1] + r(s[j\ldots n-1]) + r(s[0\ldots i])
$$

其中 $s[p\ldots q]$ 表示字符串 $s$ 的一个子串，起始于位置 $p$，终止于位置 $q$（包含两端）；“+” 表示字符串拼接操作；$r(x)$ 表示将字符串 $x$ 的字符顺序反转后得到的字符串。如果 $j = i+1$，则子串 $s[i+1\ldots j-1]$ 视为空串。

现给定两个字符串 $a$ 和 $b$。请你找到一组 $i$ 和 $j$，使得 $f(a, i, j) = b$。其中 $i$ 应尽可能大；若对于该 $i$ 存在多个合法的 $j$，则选择最小的 $j$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
Die Polizei untersucht eine Straftat im IT-Bereich.
untersucht eine Straftat.hciereB-TI mi  ieziloP eiD
```

### 输出

```
11 36
```

## 样例 #2

### 输入

```
cbaaaa
aaaabc
```

### 输出

```
4 5
```

## 样例 #3

### 输入

```
123342
3324212
```

### 输出

```
-1 -1```

# 题解

## 作者：Piwry (赞：3)

## 解析

考虑枚举 $i$

首先考虑 $A[0..i]$ 的限制，

不难发现这东西总是 $R(A)$ 的前缀和 $R(B)$ 的前缀匹配，于是直接模拟求出 $i$ 的最大值即可

接着考虑 $A[(i+1)..(j-1)]$ 的限制，

（要求 $A[(i+1)..(j-1)]$ 和 $B[0..((j-1)-(i+1)+1-1)]=B[0..(j-i-2)]$ 是匹配的）

发现两个子串在两个字符串（$A, B$）内的**起点**都是固定，于是不难想到 z-algorithm。具体来说，设 $z[i]$ 表示 $B$ 的前缀和 $A$ 从 $i$ 开始的子串的最长公共串长；接着只需检查下是否满足有 $j-i-1\leq z[i+1]$ 即可。也就是说，对于每个 $i$，仅在 $A[(i+1)..(j-1)]$ 的限制下，$j-i-1$ 的取值只要不超过（**最大值**）$z[i+1]$ 即可（即取值范围为 $[0, z[i+1]]$）

最后考虑 $A[j..(n-1)]$ 的限制，

一个直接的想法是，先考虑也枚举 $j$，然后再优化枚举。对于确定的 $i, j$，要求 $A[j..(n-1)]$ 和 $B[(j-i-1)..(n-i-2)]$ 是匹配的，而想优化这个非常麻烦（且最后得到的复杂度也不是很优）

考虑换一个思路。因为刚才给出的 $j$ 的取值都是**连续的**，且下界就是 $j$ **按照定义给出的下界**（即$j=i+1$），因此考虑直接求出 $j$ 的**最小值**。发现两个子串在两个字符串内的**终点**都是固定的，再联想一下，可以想到用 kmp。具体来说，设 $\pi[i]$ 表示 $R(A)$ 的前缀和 $B$ 在 $i$ 结束的子串的最长公共串长；接着 $(n-i-2)-\pi[n-i-2]+1$ 即为 $i-j-1$ 的最小值

此外还有一些边界情况要注意（例如 $i$ 的最大值为 $n-2$ 等）

## CODE

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using std::vector;
using std::min;
using std::max;

const int MAXN =1e6+20;

/*------------------------------IO------------------------------*/

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

struct string{
	char data[MAXN];
	int len;
	
	int size() const{
		return len;
	}
	void reverse(){
		std::reverse(data, data+len);
	}
	
	char & operator [] (const int &index){
		return data[index];
	}
	char operator [] (const int &index) const{
		return data[index];
	}
};

void read_string(string &s){
	char ch =getchar();
	while(ch < 32 || ch > 126)
		ch =getchar();
	s.len =0;
	while(ch >= 32 && ch <= 126)
		s[s.len++] =ch, ch =getchar();
}

/*------------------------------Kmp------------------------------*/

vector<int> kmp(const string &s1, const string &s2, const vector<int> &pi_s2_init =vector<int>(1, -1)){
	const int n1 =s1.size(), n2 =s2.size();
	vector<int> pi(n1, 0);
	const vector<int> &pi_s2 =(pi_s2_init[0] != -1) ? pi_s2_init : pi;
	pi[0] =(&s1 == &s2) ? 0 : (s1[0] == s2[0]);
	for(int i =1; i < n1; ++i){
		int j =pi[i-1];
		if(j == n2)
			j =pi_s2[0+j-1];
		while(j && s2[0+j-1+1] != s1[i])
			j =pi_s2[0+j-1];
		pi[i] =j+(s2[0+j-1+1] == s1[i]);
	}
	return pi;
}

/*------------------------------Z-Algorithm------------------------------*/

vector<int> z_algorithm(const string &s1, const string &s2, const vector<int> &z_s2_init =vector<int>(1, -1)){
	const int n1 =s1.size(), n2 =s2.size();
	vector<int> z(n1, 0);
	const vector<int> &z_s2 =(z_s2_init[0] != -1) ? z_s2_init : z;
	while(z[0] < n2 && s1[z[0]] == s2[z[0]])
		++z[0];
	for(int i =1, l =0, r =0; i < n1; ++i){
		if(i < r)
			z[i] =min(r-i, z_s2[i-l]);
		while(z[i] < n2 && i+z[i] < n1 && s1[i+z[i]] == s2[z[i]])
			++z[i];
		if(r < i+z[i])
			l =i, r =i+z[i];
	}
	return z;
}

/*------------------------------Main------------------------------*/

int main(){
	string A, B;
	read_string(A), read_string(B);
	
	auto Ans =[&](const int &i, const int &j){
		if(i == -1)
			puts("-1 -1");
		else
			write(i), putchar(' '), write(j);
		return 0;
	};
	
	if(A.size() != B.size())
		return Ans(-1, -1);
	const int n =A.size();
	
	string RA =A;
	RA.reverse();
	const vector<int> z_A_B =z_algorithm(A, B, z_algorithm(B, B)), pi_B_RA =kmp(B, RA, kmp(RA, RA));
	/**
	 *  z_A_B[i+1]: 最长的 A[i..j] 的长度 //
	 *  pi_B_RA[n-1-(i+1)]: 最长的 A[j..(n-1)] 的长度 //
	**/
	
	int init_i =0;
	while(init_i < n && A[init_i] == B[n-1-init_i])
		++init_i;
	for(int i =min(n-2, init_i-1); i >= 0; --i){
		const int len_pre =i+1;
		// 这里的 "j" 是指 j 对应的在 B 的下标 //
		// 即 "j" =j-len_pre //
		const int j_min =(n-1-len_pre)-pi_B_RA[n-1-len_pre]+1;
		const int j_max =0+z_A_B[i+1];
		if(j_max >= j_min)
			return Ans(i, i+((j_min-1)-0+1)+1);
	}
	
	return Ans(-1, -1);
}
```

---

## 作者：ForgotMe (赞：2)

一道 kmp+hash 的好题，值得一做。

先定义几个函数 $\operatorname{Z(a,b)}$ 表示字符串 $\operatorname{a}$ 的前缀与字符串 $\operatorname{b}$ 的后缀相同的最大长度（也就是求一个最大长度 $len$ 使得字符串 $\operatorname{a}$ 的长度为 $len$ 的前缀与字符串 $\operatorname{b}$ 的长度为 $len$ 的后缀相等），规定字符串的编号从 $1$ 开始，且题目中的函数为 ~~(不要问我为什么要这样子规定，题目原来的看起来不爽)~~：

$$
\operatorname{F(s,i,j)=s[i...j]+R(s[j+1...n])+R(s[1..i-1])}
$$

初看题目看起来很恶心，这个 $\operatorname{R}$ 函数导致这个题目直接做一点也不好做。

显然如果字符串长度不同肯定无解。

考虑把串 $\operatorname{A}$ 翻转得到字符串 $\operatorname{C}$，然后你会发现一些神奇的东西。

举个例子，就拿第一个例子来说，

串 `A`：Die Polizei untersucht eine Straftat im IT-Bereich.   
串 `B`：untersucht eine Straftat.hciereB-TI mi  ieziloP eiD    
串 `C`：.hciereB-TI mi tatfartS enie thcusretnu ieziloP eiD

你会发现题目中的 $\operatorname{R(s[1…i-1])}$ 就只能为串 `B` 与串 `C` 最长后缀的任意一个后缀。

考虑枚举串 `B` 的一个位置 $i(i\lt |B|)$，发现这个位置满足条件当且仅当 $\operatorname{Z(C[1...i],B[1...i])}\ge1$ 且 $\operatorname{B[1....i-Z(C[1...i],B[1...i])]=R(C[Z(C[1...i],B[1...i])+1...i])}$ 且 $\operatorname{B[1....i-Z(C[1...i],B[1...i])]=R(C[Z(C[1...i],B[1...i])+1...i])}$。

发现 $\operatorname{Z(C[1...i],B[1...i])}$ 可以用 kmp 算出来，于是直接枚举长度 $i$，用 hash 检验就可以了。

不过你会发现这过不了样例二，因为 $\operatorname{Z(C[1...i],B[1...i])}=i$ 的时候会炸，$\operatorname{F(s,i,j)}$ 中的 $i$ 不能等于 $1$，将 $\operatorname{Z(C[1...i],B[1...i])}$ 置为 $1$ 即可。

下面是喜闻乐见的代码。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ull unsigned long long
char a[1000005], b[1000005], c[1000005];
ull p = 131, P[1000005], A[1000005], B[1000005], C[1000005];
ull hasha(int l, int r) { return A[r] - A[l - 1] * P[r - l + 1]; }
ull hashb(int l, int r) { return B[r] - B[l - 1] * P[r - l + 1]; }
ull hashc(int l, int r) { return C[r] - C[l - 1] * P[r - l + 1]; }
int len1, len2, ans1 = -1, ans2 = -1, Nxt[1000005], Nxt2[1000005];
void Ckans(int a, int b) {
    if (ans1 == -1 && ans2 == -1)
        ans1 = a, ans2 = b;
    else {
        if (a > ans1)
            ans1 = a, ans2 = b;
        else if (a == ans1 && ans2 > b)
            ans2 = b;
    }
}
signed main() {
    gets(a + 1), gets(b + 1);
    len1 = strlen(a + 1), len2 = strlen(b + 1);
    if (len1 != len2)
        return printf("-1 -1") & 0;
    reverse(a + 1, a + len1 + 1);
    for (int i = 1; i <= len1; i++) c[i] = a[i];
    puts(c+1);
    reverse(a + 1, a + len1 + 1);
    P[0] = 1;
    for (int i = 1; i <= len1; i++) P[i] = P[i - 1] * p;
    for (int i = 1; i <= len1; i++) {
        A[i] = A[i - 1] * p + a[i];
        B[i] = B[i - 1] * p + b[i];
        C[i] = C[i - 1] * p + c[i];
    }
    for (int i = 2, j = 0; i <= len1; i++) {
        while (j && c[j + 1] != c[i]) j = Nxt[j];
        if (c[j + 1] == c[i])
            j++;
        Nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= len1; i++) {
        while (j && c[j + 1] != b[i]) j = Nxt[j];
        if (c[j + 1] == b[i])
            j++;
        Nxt2[i] = j;
    }
    for (int i = 1; i < len1; i++) {
        int now = Nxt2[i];
        if (now == 0)
            continue;
        if (now == i)
            now = 1;
        int beginc = now + 1, endc = i;
        if (hashb(1, i - now) == hasha(len1 - endc + 1, len1 - beginc + 1) &&
            hashb(i + 1, len1) == hashc(i + 1, len1))
            Ckans(len1 - i - 1, len1 - now);
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}
```

---

## 作者：HomuraAkemi (赞：0)

和 Madoka 酱 duel 到的题。然后是线性的只用到哈希的做法。

首先判掉平凡的无解情况。

然后，考虑将字符串分为如下的三段：

$$\operatorname{reverse}(t)=[1,i],[j,n],[j-1,i+1]$$
$$s=[1,i],[i+1,j-1],[j,n]$$

枚举一下 $i$。我们要找到最小的 $j$ 满足上述条件。

令 $\operatorname{hash}_s(l,r)$ 为 $s[l,r]$ 的哈希值；令 $\operatorname{hash}'_s(l,r)$ 为 $\overline{s_rs_{r-1}\cdots s_l}$ 的哈希值。然后令 $b$ 为多项式哈希里面的底数。

那么，有

$$\operatorname{hash}_s(j,n)\cdot b^{j-i-1}+\operatorname{hash}'_s(i+1,n)-\operatorname{hash}'_s(j,n)\cdot b^{j-i-1}=\operatorname{hash}_t(i+1,n)$$

也就是

$$\operatorname{hash}_s(j,n)\cdot b^{j-i-1}-\operatorname{hash}'_s(j,n)\cdot b^{j-i-1}=\operatorname{hash}_t(i+1,n)-\operatorname{hash}'_s(i+1,n)$$

也就是

$$\operatorname{hash}_s(j,n)\cdot b^{j}-\operatorname{hash}'_s(j,n)\cdot b^{j}=\operatorname{hash}_t(i+1,n)\cdot b^{i+1}-\operatorname{hash}'_s(i+1,n)\cdot b^{i+1}$$

观察到左边只和 $j$ 有关，右边只和 $i$ 有关。把左边的值塞到哈希表里面，然后每次枚举 $i$ 的时候把不合法的值删掉，然后取最小的 $j$。这样是线性的。

这题比较卡常。此外单哈希可能过不去，要开双哈希。

---

## 作者：lfxxx (赞：0)

字符串推式子题，下文 $RA$ 表示 $A$ 翻转后的串，$RB$ 表示 $B$ 翻转后的串。

题意给定等式两边都翻转一下，有 $S[0,i] + S[j,n-1] + RS[n-j,n-i-2] = RB$。

三个部分拆开，得到 $S[0,i] = RB[0,i],S[j,n-1] = RB[i+1,n+i-j],RS[n-j,n-i-2] = RB[n+i-j+1,n-1]$。

第二个式子中两边 $j$ 正负性不一致，太不牛了，变成 $RS[0,n-j-1] = B[j-i-1,n-i-2]$，这说明什么？

这说明 $RS[0,n-j-1]$ 是 $B[0,n-i-2]$ 的一个后缀！

再考虑第三个条件，这个条件显然是当 $j$ 越小时 $n-j,n+i-j+1$ 越大，由于另一端固定，所以 $j$ 越小越容易满足要求。

于是从大往小枚举 $i$，用哈希 check 第一个式子，对于$RS[0,n-j-1]$ 是 $B[0,n-i-2]$ 的一个后缀这个条件而言考虑用 kmp 处理出的失配指针动态地求出（从大往小枚举 $i$ 时相当于往串 $B[0,n-i-2]$ 后面不断加字符）最大的 $n-j-1$，此时 $j$ 取到最小值，最容易满足条件三，所以只需要再用哈希 check 一下此时最小的 $j$ 是否满足条件三即可。

于是做到了 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e6+114;
const int mod = 998244407;
const int base = 131;
int _pow[maxn];
string A,B;
string RA,RB;
int nxt[maxn];//RA 的 nxt 数组
int preA[maxn],preB[maxn],preRA[maxn],preRB[maxn]; 
int getA(int l,int r){
	if(l>r) return 0;
	if(l==0) return preA[r];
	return (preA[r]+mod-preA[l-1])%mod;
}
int getB(int l,int r){
	if(l>r) return 0;
	if(l==0) return preB[r];
	return (preB[r]+mod-preB[l-1])%mod;
}
int getRA(int l,int r){
	if(l>r) return 0;
	if(l==0) return preRA[r];
	return (preRA[r]+mod-preRA[l-1])%mod;
}
int getRB(int l,int r){
	if(l>r) return 0;
	if(l==0) return preRB[r];
	return (preRB[r]+mod-preRB[l-1])%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	getline(cin,A);
	getline(cin,B);
	RA=A,RB=B;
	if(A.size()!=B.size()){
		cout<<"-1 -1\n";
		return 0;
	}
	int n=A.size();
	reverse(RA.begin(),RA.end());
	reverse(RB.begin(),RB.end());
	_pow[0]=1;
	for(int i=1;i<maxn;i++) _pow[i]=_pow[i-1]*base%mod;
	preA[0]=A[0]*_pow[0]%mod;
	for(int i=1;i<n;i++) preA[i]=(preA[i-1]+A[i]*_pow[i]%mod)%mod;
	preB[0]=B[0]*_pow[0]%mod;
	for(int i=1;i<n;i++) preB[i]=(preB[i-1]+B[i]*_pow[i]%mod)%mod;
	preRA[0]=RA[0]*_pow[0]%mod;
	for(int i=1;i<n;i++) preRA[i]=(preRA[i-1]+RA[i]*_pow[i]%mod)%mod;
	preRB[0]=RB[0]*_pow[0]%mod;
	for(int i=1;i<n;i++) preRB[i]=(preRB[i-1]+RB[i]*_pow[i]%mod)%mod;
	nxt[0]=-1;
	for(int i=1;i<(int)RA.size();i++){
		int z=nxt[i-1];
		while(z>=0&&RA[z+1]!=RA[i]) z=nxt[z];
		if(RA[z+1]==RA[i]) z++;
		nxt[i]=z;
	}
	int p=-1;
	for(int i=n-2;i>=0;i--){
		while(p>=0&&RA[p+1]!=B[n-i-2]) p=nxt[p];
		if(RA[p+1]==B[n-i-2]) p++;
		int j=n-1-p;
		if(p==-1) continue;
		if(i<j&&getA(0,i)==getRB(0,i)&&getRA(n-j,n-i-2)*_pow[n+i-j+1]%mod==getRB(n+i-j+1,n-1)*_pow[n-j]%mod){
			cout<<i<<' '<<j<<"\n";
			return 0;
		}
	}
	cout<<"-1 -1\n";
	return 0;
}
```

---

## 作者：lzqy_ (赞：0)

挺有趣的字符串题。

如果枚举 $R(s[j\dots n])$，那么是一个不断增加的前缀，$\text{Begpos}$ 集单调不增。预处理出每个 $\text{Begpos}$ 对应的最大的 $n-j+1$，记录为 $f_{\text{Begpos}}$。

枚举 $R(s[1\dots i])$，问题转化为 $S[L\dots mid-1]+R(S[mid,\dots,n])=T'$。前一部分合法的是一段区间 $[1,lcp]$，后一段 $T$ 中位置 $loc$ 的合法条件是 $f_{loc} \ge |T|-loc+1$。

从小到大枚举 $R(s[1\dots i])$ ，$|T|$ 逐渐减小，按照 $f_{loc}+loc-1$ 排序即可。

时间复杂度 $O(n\log n)$。瓶颈在排序，用桶排就是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
const int inf=1<<30;
char s[maxn],s_r[maxn],t[maxn];
int z1[maxn],p1[maxn];
int z2[maxn],p2[maxn];
int f[maxn],n;
int ans1=-1,ans2=-1;
struct info{
	int loc,f;
}a[maxn];
bool cmp(info a,info b){return a.f+a.loc<b.f+b.loc;} 
void exKMP(char *a,char *b,int *z,int *p){
	//b与a的每一段后缀 
	a[n+1]=1,b[n+1]=2,z[1]=n;
	for(int i=2,l=0,r=0;i<=n;i++){
		if(i<=r) z[i]=min(z[i-l+1],r-i+1);
		while(b[1+z[i]]==b[i+z[i]]) z[i]++;
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
	while(s_r[1+p[1]]==t[1+p[1]]) p[1]++;
	for(int i=2,l=0,r=0;i<=n;i++){
		if(i<=r) p[i]=min(z[i-l+1],r-i+1);
		while(b[1+p[i]]==a[i+p[i]]) p[i]++;
		if(i+p[i]-1>r) l=i,r=i+p[i]-1; 
	}
}
int main(){
	cin.getline(s+1,maxn);
	cin.getline(t+1,maxn);
	if(strlen(s+1)!=strlen(t+1)){
		printf("-1 -1\n");
		return 0;
	}
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s_r[i]=s[n-i+1];
	exKMP(t,s_r,z1,p1),exKMP(s,t,z2,p2);
	for(int i=1;i<=n;i++)
		a[i].loc=i,a[i].f=p1[i];
	sort(a+1,a+1+n,cmp);
	int Mn=inf;
	for(int i=1,j=n;i<n;i++){
		if(s[i]!=t[n-i+1]) break;
		while(j&&a[j].f>=(n-i)-a[j].loc+1)
			Mn=min(Mn,a[j].loc-1),j--;
		if(Mn+i<n&&Mn<=p2[i+1])
			ans1=(i)-1,ans2=(Mn+i+1)-1;
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

还是一道很综合的 string 练手题。

先来分析一下，将 $B$ 按照答案分成三段，三段与 $A$ 都有什么关系。

第一段：$A$ 的一个子串。

第二段：$A$ 的一段后缀翻转。

第三段：$A$ 的一段前缀翻转。

我们大概率是要枚举其中一个的，其中第三段都能用 $A,B$ 的前后缀表示，考虑枚举它，也就是枚举 $i$。

下令 $len$ 为 $|A|$。

然后考虑怎样处理剩下的。发现此时第一段在 $A,B$ 中的左端点都已经确定（分别是 $i+1,0$）。于是可以考虑求出 $L=\operatorname{lcp}(A[i+1,len-1],B[0,len-1])$。剩下的要求就是 $\exists j\le L,A[i+j+1,len-1]=R(B[j,len-i-2])$。这可以看作一个和上面类似的东西，但是前面那个可以用拓展 kmp 求的东西和 kmp 是相关联的。可以得到这个式子等价于 $\operatorname{lcp}(A[i+1,len-1],B[0,len-1])+\operatorname{maxpos}(len-i-2)\ge len-i-1$。其中 $\operatorname{maxpos}(x)$ 为以 $R(A)$ 为模式串，$B$ 为文本串做 kmp，遍历到文本串第 $x$ 位时，模式串匹配了多长。于是做完了。

但是我没用 exkmp，用的是字符串 hash。

code：

```cpp
const int base[2]={13331,131313},mod[2]={(int)1e9+9,469762049};
int n,m,c[207][2],fail[N],pre[N],suf[N],f[N][2],g[N][2],pw[N][2];
char s[N],t[N],r[N];
mt19937 rnd(time(0));
void readStr(char *s,int &n){
	char c=gc();
	while(c<32||c>126)c=gc();
	while(c>=32&&c<=126)s[++n]=c,c=gc();
}
il pair<ll,ll> getHashf(int l,int r){
	if(l>r)return Mp(0,0);
	return Mp((f[r][0]-1ll*f[l-1][0]*pw[r-l+1][0]%mod[0]+mod[0])%mod[0],(f[r][1]-1ll*f[l-1][1]*pw[r-l+1][1]%mod[1]+mod[1])%mod[1]);
}
il pair<ll,ll> getHashg(int l,int r){
	if(l>r)return Mp(0,0);
	return Mp((g[r][0]-1ll*g[l-1][0]*pw[r-l+1][0]%mod[0]+mod[0])%mod[0],(g[r][1]-1ll*g[l-1][1]*pw[r-l+1][1]%mod[1]+mod[1])%mod[1]);
}
void Yorushika(){
	readStr(s,n),readStr(t,m);
	if(n!=m){puts("-1 -1");return;}
	rep(i,1,150)c[i][0]=c[i][1]=i;
	pw[0][0]=pw[0][1]=1;
	rep(i,1,n)rep(j,0,1){
		f[i][j]=(1ll*f[i-1][j]*base[j]+c[s[i]][j])%mod[j];
		g[i][j]=(1ll*g[i-1][j]*base[j]+c[t[i]][j])%mod[j];
		pw[i][j]=1ll*pw[i-1][j]*base[j]%mod[j];
	}
	rep(i,1,n){
		int l=0,r=n-i+1;
		pre[i]=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(getHashf(i,i+mid-1)==getHashg(1,mid))l=(pre[i]=mid)+1;
			else r=mid-1;
		}
	}
	rep(i,1,n)r[i]=s[n-i+1];
	rep(i,2,n){
		int &j=(fail[i]=fail[i-1]);
		while(j&&r[i]!=r[j+1])j=fail[j];
		j+=r[i]==r[j+1];
	}
	rep(i,1,n){
		int &j=(suf[i]=suf[i-1]);
		while(j&&t[i]!=r[j+1])j=fail[j];
		j+=t[i]==r[j+1];
	}
	int p=0;
	while(p<n&&s[p+1]==t[n-p])p++;
	drep(i,min(p,n-1),1){
		if(s[i]!=t[n-i+1])break;
		if(pre[i+1]+suf[n-i]>=n-i)return printf("%d %d\n",i-1,n-suf[n-i]),void();
	}
	puts("-1 -1");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

