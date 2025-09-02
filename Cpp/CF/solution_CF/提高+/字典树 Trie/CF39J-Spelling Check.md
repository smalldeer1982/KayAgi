# Spelling Check

## 题目描述

Petya发现，当他用键盘打字时，他经常多打出一个字母。他想要发明一个自动改正单词的程序，能够将他打出的单词删去一个字母，改为字典中对应的正确单词。请你帮助他写一个程序，从打出的单词中删去哪一个字母，才能改为字典中的那个单词？

## 样例 #1

### 输入

```
abdrakadabra
abrakadabra
```

### 输出

```
1
3
```

## 样例 #2

### 输入

```
aa
a
```

### 输出

```
2
1 2
```

## 样例 #3

### 输入

```
competition
codeforces
```

### 输出

```
0
```

# 题解

## 作者：OHYEP (赞：9)

for循环跑一遍第一个字符串，遇到不匹配的时候忽略掉（跳过），并且做好标记

![](https://cdn.luogu.com.cn/upload/image_hosting/2zwisrgg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果出现不止一个不一样的，那就肯定无解了。

![](https://cdn.luogu.com.cn/upload/image_hosting/m7tg3yns.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当有解时，这些解必定是连在一起，并且这些解和做标记的字母是一样的

![](https://cdn.luogu.com.cn/upload/image_hosting/g1nznrp5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

证明：比较好理解
如果s1[x]或s1[y]删除后，两个字符串匹配，（x<y&&x！=y+1&&x！=y-1&&x，y中间没有其它解），可得到:

s1[x+1]==s2[x],s1[y]==s2[y]
s1[x]==s2[x],s1[y+1]==s2[y]

乍一看没什么问题，品，你细品

![](https://cdn.luogu.com.cn/upload/image_hosting/pzdyd9rc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因为去掉s1[y]同样匹配，我们还可以知道，

s1[x+1]==s2[x+1]，s1[x+2]==s2[x+2]·······

发现事情不打对劲了没有？

x+1好像也是解w喔

![](https://cdn.luogu.com.cn/upload/image_hosting/l8y4fw9v.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

就这样这样我们一直推，发现 

x==x+1==x+2==······y

如此，得证

这就好办了，我们仔细看看，之前的标记，是不是很像上文证明中的y呢，那么从标记往前搜便是求解，下面是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s1[1000010],s2[1000010];
int len1,len2;
int an;
int main()
{
	scanf("%s",s1+1);len1=strlen(s1+1);
	scanf("%s",s2+1);len2=strlen(s2+1);
	int t=1,bj=0,ans=0;
	for(int i=1;i<=len1;i++)
	{
		if(s1[i]==s2[t])
		{
			t++;
		}
		else
		{
			an=i;bj++;
		}
	}
	if(bj>1)
	{
		printf("0");
		return 0;
	}
	for(int i=an-1;i>=1;i--)
	{
		if(s1[i]==s1[an])
		{
			ans++;
		}
		else break;
	}
	printf("%d\n",ans+1);
	for(int i=an-ans;i<=an;i++) printf("%d ",i);
	return 0;
}
```


---

## 作者：湫泷 (赞：7)

我提供另一种算法，没用hash，也没用前后缀

用两个指针模拟即可

两个指针，sta_1,sta_2分别指向字符串s1,s2的开头，从前往后查找

如果有不同的，就把sta_1这个位置记录下来

再跳过sta_1继续往后查找，重复上述操作

如果记录下的sta_1的个数超过1个，那么肯定不能通过删除一个字母的方式改正

在从sta_1往前查找把每一个连续且与s1[sta_1]相同的字符位置记录下来

最后输出即可

```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[1000100],s2[1000100];
int len1,len2,ans[1000100];
int main(){
	scanf("%s%s",s1+1,s2+1);
	len1=strlen(s1+1);
	len2=strlen(s2+1);
	int sta_1=0,sta_2=0,top=0;
	while(sta_1<=len1){
		if(s1[sta_1]==s2[sta_2]){
			sta_1++;
			sta_2++;
		}
		else{
			ans[++top]=sta_1;
			sta_1++;
		}
	}
	if(top>1){
		printf("0\n");
		return 0;
	}
	for(int i=ans[top]-1;i>=1;i--){
		if(s1[ans[top]]==s1[i]){
			ans[++top]=i;
		}
		else{
			break;
		}
	}
	sort(ans+1,ans+1+top);
	printf("%d\n",top);
	for(int i=1;i<=top;i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：little_cindy (赞：4)

## 算法

显然，是 [$\colorbox{purple}{\color{white}\text{哈希,HASH}}$](https://www.luogu.com.cn/problem/list?tag=235&page=1) 。

## Hash预备知识

在做此题之前，有几个知识是必须要知道的。

### 预备知识1：如何求字符串 $s$ 的某个字串的Hash?
假设这个子串是从 $s$ 的第 $L$ 位至第 $R$ 位，也就是 $s$ 在 $[L,R]$ 的范围的子串。

那么，这个子串的哈希值就一定像前缀和一样是大的减小的的。

大的，很显然是 $Hash_R$。

小的，肯定是包含 $Hash_{L-1}$，但是不仅如此，还需要乘上一个 $base^{R-(L-1)}$ 也就是 $base^{R-L+1}$ 来补齐空位。

所以，这个子串的哈希值是 $Hash_R-Hash_{L-1}\times base^{R-L+1}$。

而这里的 $base^{R-L+1}$ 为了方便计算，我们用一个数组 $power$ 储存下来。其中，$power_i=base^i$。

用c++写成一个函数：
```cpp
ull get(int L,int R){
	return hash[R]-hash[L-1]*power[R-L+1];
}
```

### 预备知识2：在字符串 $s$ 的区间 $[L,R]$ 中，删掉第 $p$ 个字符后的哈希值是多少？
我们可以把这个字符串分成两段：$[L,P-1]$ 和 $[P+1,R]$。

$$\fcolorbox{black}{white}{{\color{white}+}L{\color{white}+}}\fcolorbox{black}{white}{{\color{white}L+}\dots{\color{white}L+}}\fcolorbox{black}{white}{{\color{white}+}P-1{\color{white}+}}\ \fcolorbox{black}{white}{{\color{white}+}P+1{\color{white}+}}\fcolorbox{black}{white}{{\color{white}L+}\dots{\color{white}L+}}\fcolorbox{black}{white}{{\color{white}+}R{\color{white}+}}$$

第一段的值需要乘 $base^{R-p}$ 才能刚好拼接在一起。

所以，在字符串 $s$ 的区间 $[L,R]$ 中，删掉第 $p$ 个字符后的哈希值是（我们这里使用一下预备知识1的结论） $get(L,p-1)\times base^{R-p}+get(p+1,R)$。

写成一个函数即为
```cpp
ull re_hash(int L,int R,int p){
	return get(L,p-1)*power[R-p]+get(p+1,R);
}
```

## 思路

推完这么多，思路就十分简单了。

枚举断点 $p$，再用得出的结论二求出来删除第 $p$ 位后的字符串 $a$ 的哈希值与 $b$ 的哈希值比较即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int base=233,N=1000005;
string a,b;
ull hs1[N],hs2[N],power[N];//
int lena,lenb,tot,ans[N];
ull get(int L,int R){//得到字符串a在[L,R]范围的字串哈希值
	return hs1[R]-hs1[L-1]*power[R-L+1];
}
ull re_hash(int L,int R,int p){//字符串a中，[L,R]的区间内删除第p位的哈希值
	return get(L,p-1)*power[R-p]+get(p+1,R);
}
int main(){
	cin>>a>>b;
	lena=a.size();
	lenb=b.size();
	a="0"+a;//方便计算，在前面补个零
	b="0"+b;
	power[0]=1;//初始化base的0次方为1
	for(int i=1;i<=max(a.size(),b.size());i++){//预处理base的幂
		power[i]=base*power[i-1];
	}
	for(int i=1;i<=lena;i++){//生成字符串a的哈希值
		hs1[i]=hs1[i-1]*base+a[i];
	}
	for(int i=1;i<=lenb;i++){//生成字符串b的哈希值
		hs2[i]=hs2[i-1]*base+b[i];
	}
	ull val=hs2[lenb];//字符串b的哈希值 
	for(int i=1;i<=lena;i++){
		if(re_hash(1,lena,i)==val){//删掉字符串a的第i位得到字符串的哈希值是否与字符串b的哈希值相同
			ans[++tot]=i;//满足条件就记录下来
		}
	}
	cout<<tot<<endl;//输出
	for(int i=1;i<=tot;i++){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

## 总结
这篇代码使用的是自然溢出的方法来求得答案的，整体代码时间复杂度为 $O(n)$，不加任何优化使用的最大时间为 $520ms$，整体还是很快的。

---

## 作者：黑影洞人 (赞：1)

很显然，这道题我们只需要快速判断字符串是否相等。

马上想到字符串哈希，哈希算法可以 $O(1)$ 匹配字符串。

对于字符串哈希，我们先预处理出 $base$ 的 $k$ 次方，不用担心溢出，因为这样更好避免重复。

```cpp
/*
对于base来说，一般取100上下的质数，常见的有97，131等。
*/
void csh_hash(){
	fi[0]=1;
	for(int i=1;i<=1919810;i++)fi[i]=fi[i-1]*base;
}
struct string_hash{
	int h[N];
	void set(string s){
		int n=s.size();
		for(int i=0;i<n;i++)h[i]=h[i-1]*base+(s[i]-'a'+1);
	}
	int query(int l,int r){return h[r]-h[l-1]*fi[r-l+1];}
}a,b;
```
现在我们可以完美的匹配两个完整的字符串了。

但是对于删除字母操作，我们要特别注意一下：

```cpp
struct string_hash{
	int h[N];
	void set(string s){
		int n=s.size();
		for(int i=0;i<n;i++)h[i]=h[i-1]*base+(s[i]-'a'+1);
	}
	int query(int l,int r){return h[r]-h[l-1]*fi[r-l+1];}
	int queryp(int l,int r,int i){return query(l,i-1)*fi[r-i]+query(i+1,r); }
}a,b;
```
删除操作，我们先查询删除位置前的哈希值，再乘以 $base^{r-i}$ 得到的值与删除位置后的哈希值相加，就可以得到删除位置 $i$ 后的哈希值。

为什么？

因为哈希在 `set` 中已经预处理出了哈希数组 $h$ ，我们模拟完成段查询的操作：

```cpp
return h[r]-h[l-1]*fi[r-l+1];
```
现在只需要删除其中一个点，就把前半段看成一个整体，乘以与后面的位数差即可，删除了 $i$ 所以要少一位，不用额外加一了。

于是我们可以完美的解出这道题了。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#define N 1919810
using namespace std;
int fi[N],ps[N],tot,base=131;
string l,z;
void csh_hash(){
	fi[0]=1;
	for(int i=1;i<=1919810;i++)fi[i]=fi[i-1]*base;
}
struct string_hash{
	int h[N];
	void set(string s){
		int n=s.size();
		for(int i=0;i<n;i++)h[i]=h[i-1]*base+(s[i]-'a'+1);
	}
	int query(int l,int r){return h[r]-h[l-1]*fi[r-l+1];}
	int queryp(int l,int r,int i){return query(l,i-1)*fi[r-i]+query(i+1,r); }
}a,b;
signed main(){
	cin>>l>>z;
	csh_hash();
	a.set(l),b.set(z);
	if(l.size()-1!=z.size())return puts("0"),0;
	int len=l.size(),ll2=z.size();
	for(int i=0;i<len;i++){
		if(a.queryp(0,len-1,i)==b.query(0,ll2-1))ps[++tot]=i+1;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d ",ps[i]);
	return 0;
}
```

管理员同志审核题解辛苦了。


---

## 作者：__Hacheylight__ (赞：1)

我提供一种新的算法，代码简短，不用哈希

我们r表示s1和s2的公共前缀，l表示s1和s2的公共后缀

易知如果l>=r，那么左右两边都有差别，肯定无解（例如样例3）

如果r>l,那么答案肯定是l+2~r+1区间内，且方案总数一共r-l种

代码：
```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 1000010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

char s1[N], s2[N] ;

signed main(){
	scanf("%s %s", s1, s2) ;
	int l = strlen(s2), r = 0 ;
	while (s1[r] == s2[r]) r++ ;
	while (s1[l + 1] == s2[l] && l >= 0) l-- ;
	if (r > l) printf("%d\n", r - l) ;
	else print(0) ;
	for (int i = l + 1; i <= r; i++) printf("%d ", i + 1) ;
}

```

---

## 作者：wz20201136 (赞：1)

# 思路
我们暂时称“第一字符”为第一个 $s1$ 与 $s2$ 对应不相等等的字符（如样例一：为 $d$ ；样例三：为 $m$ ）

因为题目中说只会删除一个字符，所以如果满足条件，删除的字符一定与第一字符相等，且在此字符与第一字符之间没有其余字符。

所以我们只要确定第一字符，之后检查删除字符后的字符串是否与第二个字符串相等；如果符合条件，那么就分别向前向后检查相等的字符。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[1000005],s2[1000005];
int n,wz=-1;
int main()
{
	cin>>(s1+1)>>(s2+1);
	n=strlen(s1+1);
	for(int i=1,j=1;i<=n;i++,j++)
	{
		if(i==n&&wz==-1&&s1[i]==s2[i-1]) break;//当检查到最后字符时全部字符都相同的情况
		if(s1[i]==s2[j]) continue;
		if(wz!=-1)//之前出现过第一字符
		{
			cout<<0;
			return 0;
		}
		wz=i;
		j--;//与i++,j++叠加就是i++,j不变；相当于删除当前字符
	}
	if(wz==-1)//全部字符都相同的情况
	{
		cout<<n<<endl;
		for(int i=1;i<=n;i++) cout<<i<<' ';
		return 0;
	}
	int sum=0,j;
	for(int i=wz;s1[i]==s1[wz];i++) sum++;//向前寻找
	for(j=wz-1;s1[j]==s1[wz];j--) sum++; //向后寻找
	cout<<sum<<endl;
	for(++j;j<wz;j++) cout<<j<<' ';
	for(int i=wz;s1[i]==s1[wz];i++) cout<<i<<' ';
	return 0;
}
```

---

## 作者：徐天乾 (赞：0)

## 前记
看了一下题解，居然没人写哈希，~~于是我水一发~~。
## 思路
假设你已经会了哈希。不会的同学点[这里](https://www.luogu.com.cn/problem/P3370)。

首先对两个字符串进行处理，之后枚举删除的位置，接着用哈希进行判断，如果可以就放入答案，最后直接输出。（哈希 yyds）
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll const H=233,mod=(1e9)+7,Max=(1e6);  
ll Pow[Max+100],A[Max],B[Max];
int i,n,m,cnt,Q[Max];
char a[Max],b[Max];
ll Hash_A(int l,int r){
	if (l>r) return 0;
	return (A[r]-A[l-1]*Pow[r-l+1]%mod+mod)%mod;
}
ll Hash_B(int l,int r){
	if (l>r) return 0;
	return (B[r]-B[l-1]*Pow[r-l+1]%mod+mod)%mod;
}
int main(){
	scanf("%s",a+1);n=strlen(a+1);
	scanf("%s",b+1);m=strlen(b+1);
	for (Pow[0]=1,i=1;i<=Max;i++) Pow[i]=Pow[i-1]*H%mod;
	for (i=1;i<=n;i++) A[i]=(A[i-1]*H+a[i])%mod;
	for (i=1;i<=m;i++) B[i]=(B[i-1]*H+b[i])%mod;
	for (i=1;i<=n;i++)
		if (Hash_A(1,i-1)==Hash_B(1,i-1)&&Hash_A(i+1,n)==Hash_B(i,m))
			Q[++cnt]=i;
	printf("%d\n",cnt);
	for (i=1;i<=cnt;i++)
		printf("%d ",Q[i]);
	return 0; 
} 
```
## 后记
最慢的一个点跑了 624ms，相对题目的 2.00s 的时限，还是绰绰有余的。


---

