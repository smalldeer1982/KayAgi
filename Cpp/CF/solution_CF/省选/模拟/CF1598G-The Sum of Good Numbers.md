# The Sum of Good Numbers

## 题目描述

Let's call a positive integer good if there is no digit 0 in its decimal representation.

For an array of a good numbers $ a $ , one found out that the sum of some two neighboring elements is equal to $ x $ (i.e. $ x = a_i + a_{i + 1} $ for some $ i $ ). $ x $ had turned out to be a good number as well.

Then the elements of the array $ a $ were written out one after another without separators into one string $ s $ . For example, if $ a = [12, 5, 6, 133] $ , then $ s = 1256133 $ .

You are given a string $ s $ and a number $ x $ . Your task is to determine the positions in the string that correspond to the adjacent elements of the array that have sum $ x $ . If there are several possible answers, you can print any of them.

## 说明/提示

In the first example $ s[1;2] = 12 $ and $ s[3;3] = 5 $ , $ 12+5=17 $ .

In the second example $ s[2;3] = 54 $ and $ s[4;6] = 471 $ , $ 54+471=525 $ .

In the third example $ s[1;1] = 2 $ and $ s[2;2] = 3 $ , $ 2+3=5 $ .

In the fourth example $ s[2;7] = 218633 $ and $ s[8;13] = 757639 $ , $ 218633+757639=976272 $ .

## 样例 #1

### 输入

```
1256133
17```

### 输出

```
1 2
3 3```

## 样例 #2

### 输入

```
9544715561
525```

### 输出

```
2 3
4 6```

## 样例 #3

### 输入

```
239923
5```

### 输出

```
1 1
2 2```

## 样例 #4

### 输入

```
1218633757639
976272```

### 输出

```
2 7
8 13```

# 题解

## 作者：Butterfly_qwq (赞：4)

听说是到经典卡哈希题，于是就来用哈希做了。

使用五模哈希，但是没有用随机，拼劲全力终于战胜！

---

$a$ 位数和 $b$ 位数加起来是 $c$ 位数有两种可能：

1. $a=b=c-1$；
2. $\max(a,b)=c$。

第一种情况显然只有 $O(n)$ 种。

第二种情况，考虑枚举长度和 $x$ 一样的串，设其为 $p$，那么我们先求出 $p$ 和 $x$ 的 LCP 长度 $d$，这可以用 exKMP（好像大家都叫 Z 函数）求出。显然剩下那个字符串的长度只能是 $c-d$ 或 $c-d-1$。再枚举一下在前面还是后面就行了，同样只有 $O(n)$ 种，只需判断即可。

判断的话，直接高精加会达到平方级别，炸完了。考虑可以使用哈希算法判断是否相同。

听说很卡哈希，所以上来就拍了个五模，然后一遍过了。

代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+6,p[]={104857601,167772161,377487361,469762049,754974721};
int n,m,l,r,pw[N][5],hx[5],hs[N][5],z[N];string s,x;
int gethash(int l,int r,int x){return (hs[r][x]-hs[l-1][x]*pw[r-l+1][x]%p[x]+p[x])%p[x];}
void check(int l1,int r1,int l2,int r2)
{
	if(l1>r1||l2>r2||l1<1||r1>n||l2<1||r2>n)return;
	for(int i=0;i<5;i++)if((gethash(l1,r1,i)+gethash(l2,r2,i))%p[i]!=hx[i])return;
	cout<<l1<<' '<<r1<<'\n'<<l2<<' '<<r2;exit(0);
}
signed main()
{
	cin>>s>>x;n=s.size();m=x.size();s="#"+s;x="%"+x;
	for(int i=0;i<N;i++)for(int j=0;j<5;j++)pw[i][j]=i?pw[i-1][j]*10%p[j]:1; 
	for(int i=1;i<=m;i++)for(int j=0;j<5;j++)hx[j]=(hx[j]*10+x[i]-'0')%p[j];
	for(int i=1;i<=n;i++)for(int j=0;j<5;j++)hs[i][j]=(hs[i-1][j]*10+s[i]-'0')%p[j];
	x+=s;z[1]=n+m+1;
	for(int i=2;i<=n+m+1;i++)
	{
		if(i<=r&&z[i-l+1]<r-i+1)z[i]=z[i-l+1];
		else
		{
			z[i]=max(0ll,r-i+1);
			while(i+z[i]<=n+m+1&&x[i+z[i]]==x[z[i]+1])z[i]++;
		}
		if(i+z[i]-1>r)
		{
			l=i;
			r=i+z[i]-1;
		}
	}
	for(int i=1,lcp;i<=n;i++)
	{
		lcp=z[m+1+i];
		check(i,i+m-2,i+m-1,i+2*m-3);
		check(i,i+m-1,i+m,i+2*m-lcp-1);
		check(i,i+m-1,i+m,i+2*m-lcp-2);
		check(i-m+lcp,i-1,i,i+m-1);
		check(i-m+lcp+1,i-1,i,i+m-1);
	}
}
```

当然，凡是哈希都会有 hack，本代码的 hack 也很容易构造：

```
518149699298727357728665216133623692667125981111111111111111111111111111111111111111111155555555555555555555555555555555555555555555555555555555555555555555555555555555555556
11111111111111111111111111111111111111111111
```

正确输出是：

```
89 131
131 174
```

而我的输出是：

```
1 44
45 88
```

构造原理不难。

---

## 作者：ZaireEmery (赞：2)

考虑和为 $x$ 的两个数是 $a$ 和 $b$，且 $a \geq b$。显然，$|a|=|x|$ 或 $|a|=|x|-1$。

先考虑 $|a|=|x|-1$ 的情况，此时肯定有 $|b|=|x|-1$。只要枚举两个连续的长度都是 $|x|-1$ 的字符串即可。

再考虑 $|a|=|x|$ 的情况，设 $lcp$ 为 $a$ 和 $x$ 的最长公共前缀长度（可以用 Z 函数求出）。此时有 $|b|=|x|-lcp$ 或 $|b|=|x|-lcp-1$，再枚举一下 $b$ 在 $a$ 的前面还是后面即可。

至此，我们已经在 $O(n)$ 的时间里求出了所有可能成为答案的 $a$ 和 $b$，只需一一检验。朴素的高精度算法显然不够优秀，我们可以用字符串哈希解决。**注意哈希一定要用随机模数，否则分分钟被卡掉。**

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500010
using namespace std;
int n,m,z[N*2];
char s[N],x[N*2];
vector<int> mods,valx,h[N],p10[N];
bool isprime(int x){
	for(int i=2;i*i<=x;i++)
		if(!x%i) return 0;
	return 1;
}
vector<int> geth(int l,int r){
	vector<int> res;
	for(int i=0;i<5;i++) res.push_back((h[r][i]-h[l-1][i]*p10[r-l+1][i]%mods[i]+mods[i])%mods[i]);
	return res;
} 
void check(int l1,int r1,int l2,int r2){
	if(l1>r1||l2>r2||l1<1||r1>n||l2<1||r2>n) return;
	vector<int> a=geth(l1,r1),b=geth(l2,r2);
	for(int i=0;i<5;i++)
		if((a[i]+b[i])%mods[i]!=valx[i]) return;
	printf("%d %d\n%d %d\n",l1,r1,l2,r2);
	exit(0);
}
signed main(){
	srand(time(NULL));
	while(mods.size()<5){
		int r=(rand()*233333&((1<<30)-1))+1e8;
		if(isprime(r)) mods.push_back(r);
	}
	scanf("%s%s",s+1,x+1);
	n=strlen(s+1);m=strlen(x+1);
	for(int i=0;i<=n;i++) h[i].resize(5,0);
	for(int i=1;i<=n;i++)
		for(int j=0;j<5;j++)
			h[i][j]=(h[i-1][j]*10+s[i]-'0')%mods[j];
	valx.resize(5,0);
	for(int i=1;i<=m;i++)
		for(int j=0;j<5;j++) valx[j]=(valx[j]*10+x[i]-'0')%mods[j];
	for(int i=0;i<=n;i++) p10[i].resize(5,1);
	for(int i=1;i<=n;i++)
		for(int j=0;j<5;j++) p10[i][j]=p10[i-1][j]*10%mods[j];
	x[m+1]='#';
	for(int i=1;i<=n;i++) x[m+1+i]=s[i];
	z[1]=n+m+1;
	int l=0,r=0;
	for(int i=2;i<=n+m+1;i++){
		if(i<=r&&z[i-l+1]<r-i+1) z[i]=z[i-l+1];
		else{
			z[i]=max(0ll,r-i+1);
			while(i+z[i]<=n+m+1&&x[i+z[i]]==x[z[i]+1]) z[i]++;
		}
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
	for(int i=1;i<=n;i++){
		check(i,i+m-2,i+m-1,i+2*m-3);
		int lcp=z[m+1+i];
		check(i,i+m-1,i+m,i+m+(m-lcp)-1);
		check(i,i+m-1,i+m,i+m+(m-lcp-1)-1);
		check(i-(m-lcp),i-1,i,i+m-1);
		check(i-(m-lcp-1),i-1,i,i+m-1);
	}
	return 0;
}
```


---

## 作者：StaroForgin (赞：2)

## 题解

~~这种高精加法哈希比较的题真的很臭呀，赛后一群人在那里卡模数，真的吐了~~

我们考虑如何快速比较两个大整数的和，显然，哈希是一种很好的方法，所以我们可以将比较两个很长的大整数的和转换成比较它们哈希值的和。

由于我们所有的数都是 *"好数"* ,也就是不含 $0$ 的数，所以它的进位一定是比较少的，其进位最多只会比做加法的两个数多出 $1$ 位。

所以我们加的两个数要么是长度几乎相当，都是 $|x|$ 或 $|x|-1$，要么较长的为 $|x|$，其前缀的大部分都与我们目标的$x$相同。

对于前面的都是 $|x|$ 或 $|x|-1$ 的情况，我们可以特殊记录一下，从每个点开始的长度为 $|x|$ 或者 $|x|-1$ 的前缀的哈希值，将相邻的两个加起来，判断它的哈希值是否等于我们目标 $x$ 的哈希值。

对于第二种情况，我们可以猜测大部分情况下与前缀大部分与我们目标 $x$ 相同的数是比较少，对于每个这样的前缀就暴力枚举其往前扩散与往后扩散的哈希值，看是否存在一个使得加起来可以达到我们目标的 $x$。

由于赛后一群人在那里卡哈希，把笔者都给卡吐了，所以笔者用的是随机的哈希数，也就是先列出一大堆哈希数，每次从里面随机出两个作为这次的哈希模数。

~~也许常数会有点大。~~

时间复杂度 $O\left(|s|+|x|\right)$。

## 源码
update：随机模数都有人把所有模数打出来hack，真的吐了，不过换几个模数就过了。

```c++
#include<bits/stdc++.h>
using namespace std;
#define MAXN 500005
#define MAXM (1<<20)+5
#define lowbit(x) (x&-x)
#define reg register
#define pb push_back
#define mkpr make_pair
#define fir first
#define sec second
#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;
typedef unsigned long long uLL;     
const int INF=0x3f3f3f3f;  
const int inv2=499122177;
const int jzm=2333;
const int n1=50;
const int zero=10000;
const int orG=3,invG=332748118;
const double Pi=acos(-1.0);
const double eps=1e-5;
typedef pair<LL,int> pii;
template<typename _T>
_T Fabs(_T x){return x<0?-x:x;}
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}
	x*=f;
}
template<typename _T>
void print(_T x){putchar('\n');while(x>9){putchar((x%10)|'0');x/=10;}putchar(x|'0');}
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
int add(int x,int y,int p){return x+y<p?x+y:x+y-p;}
void Add(int &x,int y,int p){x=add(x,y,p);}
int qkpow(int a,int s,int p){int t=1;while(s){if(s&1LL)t=1ll*a*t%p;a=1ll*a*a%p;s>>=1LL;}return t;}
int lens,lenx,mod1,mod2;pii nowx,sum1[MAXN],sum2[MAXN];
int mp[15]={99990571,99990337,99999941,99999931,99999847,99999839,99999827,99999821,99999787,99999773,99999721,};
char str[MAXN],x[MAXN];
pii operator + (pii x,pii y){return mkpr(add(x.fir,y.fir,mod1),add(x.sec,y.sec,mod2));}
bool operator == (pii x,pii y){return x.fir==y.fir&&x.sec==y.sec;}
signed main(){
	scanf("%s\n%s",str+1,x+1);
	mt19937 e(time(0));uniform_int_distribution<int> g(0,10);
	int u=g(e),v=g(e);mod1=mp[u];mod2=mp[v];
	lens=(int)strlen(str+1);lenx=(int)strlen(x+1);pii num1=mkpr(1,1),num2=mkpr(1,1);
	for(int i=1;i<=lenx;i++)nowx.fir=(10ll*nowx.fir+(x[i]-'0'))%mod1,nowx.sec=(10ll*nowx.sec+(x[i]-'0'))%mod2;
	for(int i=1;i<=lenx;i++)num1.fir=10ll*num1.fir%mod1,num1.sec=10ll*num1.sec%mod2;
	for(int i=1;i<lenx;i++)num2.fir=10ll*num2.fir%mod1,num2.sec=10ll*num2.sec%mod2;
	for(int i=1;i<=lenx;i++)
		sum1[lenx].fir=(10ll*sum1[lenx].fir+1ll*(str[i]-'0'))%mod1,
		sum1[lenx].sec=(10ll*sum1[lenx].sec+1ll*(str[i]-'0'))%mod2;
	for(int i=1;i<lenx;i++)
		sum2[lenx-1].fir=(10ll*sum2[lenx-1].fir+1ll*(str[i]-'0'))%mod1,
		sum2[lenx-1].sec=(10ll*sum2[lenx-1].sec+1ll*(str[i]-'0'))%mod2;
	for(int i=lenx+1;i<=lens;i++)
		sum1[i].fir=(10ll*sum1[i-1].fir+1ll*(str[i]-'0')-1ll*num1.fir*(str[i-lenx]-'0')%mod1+1ll*mod1)%mod1,
		sum1[i].sec=(10ll*sum1[i-1].sec+1ll*(str[i]-'0')-1ll*num1.sec*(str[i-lenx]-'0')%mod2+1ll*mod2)%mod2;
	for(int i=lenx;i<=lens;i++)
		sum2[i].fir=(10ll*sum2[i-1].fir+1ll*(str[i]-'0')-1ll*num2.fir*(str[i-lenx+1]-'0')%mod1+1ll*mod1)%mod1,
		sum2[i].sec=(10ll*sum2[i-1].sec+1ll*(str[i]-'0')-1ll*num2.sec*(str[i-lenx+1]-'0')%mod2+1ll*mod2)%mod2;
	for(int i=lenx+lenx-2;i<=lens;i++){
		if(i>=lenx+lenx&&sum1[i]+sum1[i-lenx]==nowx){printf("%d %d\n%d %d\n",i-lenx-lenx+1,i-lenx,i-lenx+1,i);return 0;}
		if(lenx>1&&i>=lenx+lenx-1&&sum1[i]+sum2[i-lenx]==nowx){printf("%d %d\n%d %d\n",i-lenx-lenx+2,i-lenx,i-lenx+1,i);return 0;}
		if(lenx>1&&i>=lenx+lenx-1&&sum2[i]+sum1[i-lenx+1]==nowx){printf("%d %d\n%d %d\n",i-lenx-lenx+2,i-lenx+1,i-lenx+2,i);return 0;}
		if(lenx>1&&sum2[i]+sum2[i-lenx+1]==nowx){printf("%d %d\n%d %d\n",i-lenx-lenx+3,i-lenx+1,i-lenx+2,i);return 0;}
	}
	for(int i=lenx+1;i<=lens;i++){
		bool flag=0;
		for(int j=1;j<=min(10,lenx);j++)if(str[i-lenx+j]^x[j])flag=1;
		if(flag&&lenx>10)continue;pii summ=mkpr(0,0),num=mkpr(1,1);
		for(int j=1;j<=min(lenx,i-lenx);j++){
			summ.fir=(1ll*summ.fir+1ll*num.fir*(str[i-lenx-j+1]-'0'))%mod1;
			summ.sec=(1ll*summ.sec+1ll*num.sec*(str[i-lenx-j+1]-'0'))%mod2;
			if(sum1[i]+summ==nowx){printf("%d %d\n%d %d\n",i-lenx-j+1,i-lenx,i-lenx+1,i);return 0;}
			num.fir=10ll*num.fir%mod1;num.sec=10ll*num.sec%mod2;
		}
		summ=mkpr(0,0);
		for(int j=1;j<=min(lenx,lens-i);j++){
			summ.fir=(10ll*summ.fir+str[i+j]-'0')%mod1;
			summ.sec=(10ll*summ.sec+str[i+j]-'0')%mod2;
			if(sum1[i]+summ==nowx){printf("%d %d\n%d %d\n",i-lenx+1,i,i+1,i+j);return 0;}
		}
		num=mkpr(1,1);summ=mkpr(0,0);
		for(int j=1;j<=min(lenx-1,i-lenx+1);j++){
			summ.fir=(1ll*summ.fir+1ll*num.fir*(str[i-lenx-j+2]-'0'))%mod1;
			summ.sec=(1ll*summ.sec+1ll*num.sec*(str[i-lenx-j+2]-'0'))%mod2;
			if(sum2[i]+summ==nowx){printf("%d %d\n%d %d\n",i-lenx-j+2,i-lenx+1,i-lenx+2,i);return 0;}
			num.fir=10ll*num.fir%mod1;num.sec=10ll*num.sec%mod2;
		}
		summ=mkpr(0,0);
		for(int j=1;j<=min(lenx-1,lens-i);j++){
			summ.fir=(10ll*summ.fir+str[i+j]-'0')%mod1;
			summ.sec=(10ll*summ.sec+str[i+j]-'0')%mod2;
			if(sum2[i]+summ==nowx){printf("%d %d\n%d %d\n",i-lenx+2,i,i+1,i+j);return 0;}
		}
	}
	return 0;
}
```

---

## 作者：IdnadRev (赞：1)

比较简单的题，可能是因为卡哈希被评到了 \*3200。

## 题意

给定一个不含 `0` 的字符串，给你一个整数 $x$，找到两个相邻且和为 $x$ 的子串，保证有解。

$2\leqslant |S|\leqslant 5\times 10^5,2\leqslant x\leqslant 10^{200000}$。

## 分析

令这两个子串为 $A,B$，容易发现 $\max(|A|,|B|)\geqslant |x|-1$。

若 $\max(|A|,|B|)=|x|-1$，那么一定有 $|A|=|B|$，直接判断即可。

若 $\max(|A|,|B|)=|x|$，那么对于长的那个串与 $x$ 求个 lcp，就可以知道 $|B|$ 的长度了（可能会有 $1$ 的误差），直接跑一边 exkmp 解决。

时间复杂度 $O(n)$。

## 代码

这道题卡哈希，需要随机模数。

```
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
const int maxn=500005;
int n,m,mds;
int mod[5],hshs[maxn][5],hsht[maxn][5],z[maxn<<1],mul[maxn][5];
string s,t;
int check(int x) {
	if(x<=2)
		return x==2;
	for(int i=2; i*i<=x; i++)
		if(x%i==0)
			return 0;
	return 1;
}
void Z_function(string s) {
	int n=s.size(),l=0,r=0;
	s=" "+s,z[1]=n;
	for(int i=2; i<=n; i++) {
		if(i<=r)
			z[i]=min(z[i-l],r-i+1);
		else z[i]=0;
		while(i+z[i]<=n&&s[i+z[i]]==s[1+z[i]])
			z[i]++;
		if(i+z[i]-1>r)
			l=i,r=i+z[i]-1;
	}
}
void calc(int al,int ar,int bl,int br) {
	if(1<=al&&al<=ar&&ar<=n&&1<=bl&&bl<=br&&br<=n) {
		for(int i=1; i<=4; i++) {
			int va=(hshs[ar][i]-1ll*hshs[al-1][i]*mul[ar-al+1][i]%mod[i]+mod[i])%mod[i];
			int vb=(hshs[br][i]-1ll*hshs[bl-1][i]*mul[br-bl+1][i]%mod[i]+mod[i])%mod[i];
			if((va+vb)%mod[i]!=hsht[m][i])
				return ;
		}
		printf("%d %d\n%d %d\n",al,ar,bl,br);
		exit(0);
	}
}
int main() {
	while(mds<4) {
		int x=1ll*rand()*rand()%99900000+100000;
		if(check(x))
			mod[++mds]=x;
	}
	cin>>s>>t,n=s.size(),m=t.size(),Z_function(t+"#"+s),s=" "+s,t=" "+t;
	for(int i=1; i<=4; i++)
		mul[0][i]=1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=4; j++)
			mul[i][j]=mul[i-1][j]*10%mod[j];
	for(int i=1; i<=4; i++)
		hshs[0][i]=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=4; j++)
			hshs[i][j]=(hshs[i-1][j]*10+s[i]-48)%mod[j];
	for(int i=1; i<=4; i++)
		hsht[0][i]=0;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=4; j++)
			hsht[i][j]=(hsht[i-1][j]*10+t[i]-48)%mod[j];
	for(int i=1; i<=n; i++) {
		int len=z[m+i+1];
		calc(i,i+(m-1)-1,i+(m-1),i+(m-1)+(m-1)-1);
		calc(i,i+m-1,i+m,i+m+(m-len)-1),calc(i,i+m-1,i+m,i+m+(m-len-1)-1);
		calc(i-1-(m-len)+1,i-1,i,i+m-1),calc(i-1-(m-len-1)+1,i-1,i,i+m-1);
	}
	return 0;
}
```

---

## 作者：dead_X (赞：1)

记 $s$ 的长度为 $n$，记 $x$ 的长度为 $m$。

考虑到答案只有以下三种情况：

* 第一个串长度为 $m$。
* 第二个串长度为 $m$。
* 两个串的长度均为 $m-1$。

对于前两种情况，我们可以枚举对应的串，然后和 $x$ 求一个 LCP，就可以算出另外一种情况了。

LCP 可以使用 Z 函数或者一些后缀数据结构，也可以哈希。

于是我们得到了 $O(n)$ 个可能的答案。

对于每个答案，如果我们暴力加的复杂度是 $O(\frac{n^2}{C})$，$C$ 是压位高精的常数，约等于 $18$，加上一些优化我也不知道过不过的去。

所以我们考虑一个非完美的算法：随机选一个模数 $p$，把三个数模 $p$ 的值求出来，先进行一轮判断。

容易发现在模数范围很大时，hash 的准确率很高（因为输入的字符串不能含 $0$），因此时间复杂度近似与 $O(n)$。

代码没写，因为太恶心了。

---

## 作者：RAND_MAX (赞：0)

很厉害的一个题啊。

## 题意简述
给两个由数字组成的字符串 $s,t$，找到 $s$ 中连续的两个子串 $s_{a....b}$ 与 $s_{b+1...c}$ 使它们表示的数相加等于 $t$ 表示的数。

## 思路

不妨设 $n=|s|,m=|t|,s1=s_{a....b},s2=s_{b+1...c}$。

考虑在何种情况下 $s1+s2=t$：要么 $|s1|=|s2|=m-1$，要么 $|s1|=m$ 或 $|s2|=m$。

若 $|s1|=|s2|=m-1$，我们只需枚举每对连续的长为 $m-1$ 的子串之和是否为 $t$。判断部分，若使用高精度加法则时间难以承受，于是我们选择用哈希。这部分时间复杂度为 $O(n)$。

否则不妨设 $|s1|=m$，那么此时 $|s2|$ 只能等于 $m-LCP(t,s1)$ 或 $m-\operatorname{LCP}(t,s1)-1$。其中 $\operatorname{LCP}(t,s1)$ 为 $t$ 与 $s1$ 的最长公共前缀长度。枚举 $s1$ 后分类讨论即可。对于 $|s2|=m$ 的情况同理。求 LCP 可以用 Z 函数实现。设 $n,m$ 同阶，则这部分时间复杂度也是 $O(n)$ 的。

故总时间复杂度 $O(n)$。注意若是单模哈希极其容易被卡，本人随机了五个质数作为模数，可以通过。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define gc getchar
//char buf[1<<20],*p1,*p2;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=gc();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define bs 10
#define ull unsigned long long
#define N 500010
int n,m,z[N<<1],c[N],mo[6];
ull p[N][6],a[N][6],sum[6];
string s,t,op;
ull que(int l,int r,int po)
{
	ull su=a[r][po]-a[l-1][po]*p[r-l+1][po]%mo[po]+mo[po];su%=mo[po];
	return su;
}
void chk(int i,int j,int k)
{
	for(int lp=1;lp<=5;lp++)
	{
		ull x=que(i,j,lp)+que(j+1,k,lp);x%=mo[lp];
		if(x!=sum[lp]) return;
	}
	write(i,' '),write(j,'\n'),write(j+1,' '),write(k,'\n'),exit(0);
}
void check(int i,int x)
{
	if(!x) return;
	if(i>x) chk(i-x,i-1,i+m-1);
	if(i+m+x-1<=n) chk(i,i+m-1,i+m+x-1);
}
bool chck(int x)
{
	for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
	return 1;
}
signed main()
{
	cin>>s>>t,n=s.length(),op=t+'#'+s,m=t.length(),s=" "+s,t=" "+t;
	int top=0,xxx;
	mt19937 mr(time(0));
	while(top<5)
	{
		xxx=mr();
		if(chck(xxx)) mo[++top]=xxx;
	}
	for(int i=1;i<=5;i++) p[0][i]=1;
	for(int i=1;i<=n;i++) for(int j=1;j<=5;j++) p[i][j]=p[i-1][j]*bs%mo[j];
	for(int i=1;i<=n;i++) for(int j=1;j<=5;j++) a[i][j]=a[i-1][j]*bs%mo[j]+(s[i]-'0'),a[i][j]%=mo[j];
	for(int i=1;i<=m;i++) for(int j=1;j<=5;j++) sum[j]=sum[j]*bs%mo[j]+(t[i]-'0'),sum[j]%=mo[j];
	for(int i=1;i+2*(m-1)-1<=n;i++) chk(i,i+m-2,i+2*(m-1)-1);
	for(int i=1,l=0,r=0;i<n+m+1;i++)
	{
		if(i<=r&&z[i-l]<r-i+1) z[i]=z[i-l];
		else
		{
			z[i]=max(0ll,r-i+1);
			while(i+z[i]<n+m+1&&op[z[i]]==op[z[i]+i]) z[i]++;
		}
		if(i+z[i]>r+1) l=i,r=l+z[i]-1;
	}
	for(int i=1;i<=n;i++) c[i]=z[i+m];
	for(int i=1;i<=n;i++) check(i,m-c[i]),check(i,m-c[i]-1);
	return 0; 
}
```

---

