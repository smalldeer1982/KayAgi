# Vupsen, Pupsen and 0

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$ ，寻找一个长度为 $n$ 序列 $b_1,b_2,\dots,b_n$ ，满足 $\forall i\in\left[1,n\right]b_i\not=0,\ \ \sum\limits_{i=1}^n |b_i|\le10^9,\ \ \sum\limits_{i=1}^n a_i\times b_i=0$ ，可以证明答案一定存在。

## 说明/提示

$1\le t\le100,2\le n\le10^5,2\le\sum n\le2\times10^5,-10^4\le a_i\le10^4,a_i\not=0$ 。

## 样例 #1

### 输入

```
3
2
5 5
5
5 -2 10 -9 4
7
1 2 3 4 5 6 7```

### 输出

```
1 -1
-1 5 1 -1 -1
-10 2 2 -3 5 -1 -1```

# 题解

## 作者：Alex_Wei (赞：9)

1582D. [Vupsen, Pupsen and 0](https://codeforces.com/contest/1582/problem/D)

对于两个数 $a,b$，只要令它们前面的系数为 $x=b$ 和 $y=-a$ 就能满足 $xb+yb=ab-ab=0$。若 $n$ 为奇数还需考虑三个数 $a,b,c$ 的情况。此时我们必然能找到两个数使得它们和不为 $0$，不妨设为 $b,c$，那么令 $x=b+c$，$y=-a$，$z=-a$ 即可做到 $xa+yb+zc=(b+c)a-ab-ac=0$。注意虽然 $|x|$ 可能 $>10^4$ 但 $n<10^5$ 且 $|x|\leq 2\times 10^4$ 因此仍然有绝对值总和 $\leq 10^9$。

```cpp
const int N = 1e5 + 5;
int T, n, a[N];

int main() {
	cin >> T;
	while(T--) {
		int bg = 1; cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		if(n & 1) {
			if(a[2] + a[3]) cout << a[2] + a[3] << " " << -a[1] << " " << -a[1] << " ";
			else if(a[1] + a[2]) cout << -a[3] << " " << -a[3] << " " << a[1] + a[2] << ' ';
			else cout << -a[2] << " " << a[1] + a[3] << " " << -a[2] << " ";
			bg = 4;
		} for(int i = bg; i <= n; i += 2) cout << a[i] << " " << -a[i + 1] << " ";
		cout << endl;
	}
	return 0;
}
```

如果限制了总和 $\leq n\times 10^4$ 怎么办？

对于三个数 $a,b,c$ 的情况，我们令 $x=b$，此时变为 $(a+y)b+zc=0$ 即两个数的情况。令 $y=c-a,z=-b$。但此时可能 $|c-a|>10^4$，没关系，对 $x$ 取个反变为 $-b$，那么 $y$ 就变成了 $c+a$，显然 $|c+a|\leq 10^4$ 和 $|c-a|\leq 10^4$ 至少满足一个，故合法。

还有一些情况需要特判：$c=a$ 和 $c=-a$，这是 trival 的，因为可以看成两个数来做。综上，我们保证了 $\sum |x_i|\leq n\times 10^4$（一些细节优化之后可以做到 $|x_i|\leq 10^4$），是一个更强的算法。以下是赛时代码。

```cpp
void solve(int a,int b){cout<<b<<" "<<-a<<" ";}
void solve(int a,int b,int c){
	if(a==b&&b==c)cout<<"1 1 -2 ";
	else if(a==c){
		int coef=-b,x,y;
		if(coef<0)x=1,y=coef-1;
		else x=-1,y=coef+1;
		cout<<x<<" "<<a<<" "<<y<<" ";
	} else if(a==-c){
		int coef=b,x,y;
		if(coef<0)y=-1,x=coef-1;
		else y=1,x=coef+1;
		cout<<x<<" "<<-a<<' '<<y<<" ";
	}
	else if(abs(c-a)<=1e4)
		cout<<b<<" "<<c-a<<" "<<-b<<" ";
	else cout<<-b<<' '<<c+a<<" "<<-b<<" ";
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n%2==0)for(int i=1;i<=n;i+=2)solve(a[i],a[i+1]);
	else{
		solve(a[1],a[2],a[3]);
		for(int i=4;i<=n;i+=2)solve(a[i],a[i+1]);
	}
	cout<<endl;
}
```

---

## 作者：Lynkcat (赞：7)

这里是阴间人的做法。

首先 $n$ 为偶数很好做，直接两两配对 $x,y$ 两个数分别填上 $-y$ 和 $x$ 即可。

当 $n\leq 2\times 10^4$ 时，随便挑三个数出来，$x,y,z$ 填 $\frac{\text{lcm}(x,y,z)}{x},\frac{\text{lcm}(x,y,z)}{y},-2\times\frac{\text{lcm}(x,y,z)}{z}$ 即可。可以看出这样子无论这三个数怎么选不会超过绝对值 $1e9$ 的限制。

当 $n>2\times 10^4$ ，上面的数就不能随便选了，可以发现必然存在一个值出现了 $3$ 次，把那个值出现的三个位置当成上面那个做法即可。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 200005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int T,n,a[N],b[N],c[N];
map<int,int>Mp;
bool cmp(int x,int y)
{
	return (Mp[a[x]]^Mp[a[y]])?(Mp[a[x]]<Mp[a[y]]):a[x]<a[y];
}
signed main()
{
	T=read();
	while (T--)
	{
		n=read();
		for (int i=1;i<=n;i++) a[i]=read();
		if (n%2==0)
		{
			for (int i=1;i<=n;i+=2)
				b[i]=a[i+1],b[i+1]=-a[i];
		} else
		{
			for (int i=1;i<=n;i++) Mp[a[i]]++;
			for (int i=1;i<=n;i++) c[i]=i;
			stable_sort(c+1,c+n+1,cmp);
			for (int i=1;i<=n-3;i+=2)
			{
				b[c[i]]=a[c[i+1]],b[c[i+1]]=-a[c[i]]; 
			}
			int x=a[c[n-1]]*a[c[n]]/__gcd(a[c[n-1]],a[c[n]]);
			x=x*a[c[n-2]]/__gcd(a[c[n-2]],x);
			b[c[n-2]]=x/(a[c[n-2]]);
			b[c[n-1]]=x/(a[c[n-1]]);
			b[c[n]]=-x/(a[c[n]])*2;
		}
		for (int i=1;i<=n;i++) writesp(b[i]);
		puts("");
		Mp.clear();
	}
			
		
}
/*

*/
```


---

## 作者：Cht_master (赞：3)

- 题意简述：给定数列 $a$，构造数列 $b$ 满足 $\sum a(i)\cdot b(i)=0$，$\sum|b(i)|\le10^9$，$b(i)\ne0$。多组数据，$1\le t\le 100$，$2\le n\le 10^5$，$\sum n\le2\cdot 10^5$，$-10^4\le a(i)\le10^4$。

- 题目简析：

  - 直觉是让两个数互相抵消，即用 $b(i)=-a(i+1),b(i+1)=a(i)$ 来抵消。由于 $-10^4\le a(i)\le10^4$，所以对应的 $b(i)$ 也满足 $-10^4\le b(i)\le10^4$。

  - 长度为偶数可以直接按照上面的方法构造。现在考虑长度为奇数。可以想到用某 3 个数来抵消，令这 3 个数是 $a,b,c$。那我们需要找到满足下列方程的一组解：
    $$
    a\cdot x+b\cdot y=-c\cdot z
    $$
    发现当 $a+b\ne0$ 时取 $x=y=-c,z=a+b$ 即可，若 $a+b=0$ 交换 $b,c$ 即可。~~话说这构造挺巧妙的，因为我怎么会告诉你我最开始用扩欧做结果一直 WA 呢。~~

- ```cpp
  //核心是让两个数互相抵消.
  //但若数组长度是奇数,就让某三个数a,b,c互相抵消,解不定方程a*x+b*y=-c*z即可.
  //讨论当a(1)+a(2)!=0:则令x=-a(3),y=-a(3),z=a(1)+a(2)即可.
  #include<bits/stdc++.h>
  using namespace std;
  const int mxN(2e5);
  int n,a[mxN+5];
  int main(){
  	int T,s;scanf("%d",&T);
  	while(T--){
  		s=1,scanf("%d",&n);for(int i(1);i<=n;++i)scanf("%lld",&a[i]);
  		if(n&1){
  			s=4;
  			if(a[1]+a[2]!=0)printf("%d %d %d ",-a[3],-a[3],a[1]+a[2]);
  			else if(a[2]+a[3]!=0)printf("%d %d %d ",a[2]+a[3],-a[1],-a[1]);
  			else printf("%d %d %d ",-a[2],a[1]+a[3],-a[2]);
  		}
  		for(int i(s);i<=n;i+=2)printf("%d %d ",-a[i+1],a[i]);
  		putchar('\n');
  	}
  	return 0;
  }
  ```

  



---

## 作者：S00021 (赞：2)

## 题意：

给出一个长度为 $n$ 的 $a$ 数组，你需要构造一个长度为 $n$ 的 $b$ 数组，使得 $\sum{a_ib_i}=0$ ，其中 $n \le 10^4,a_i \le 10^5 $  ，你构造出的 $b$ 数组必须满足 $\sum|b_i| \le 10^9$ ，容易发现一定有解。

## Sol

似乎和官解很不一样呢。

题目中最关键的一句话是“容易发现一定有解”，那么我们必须要找出一种满足所有限制的通法，这看似很难，但让我们一步步来分析。

首先，我们拿到题目的第一个问题是 $a_i$ 不为 $0$ 这一条件怎么用，这很容易让我们想到一种构造方法，如果 $a_i$ 不等于 $0$ ，那么只要对 $a_i$ 两两分组，设第 $i$ 组中的数为 $p_i,q_i$ ，只需要将对应的 $b$ 赋成 $\dfrac{\text{lcm}(p_{i},q_i)}{p_i}$，$\dfrac{\text{lcm}(p_i,q_i)}{q_i}$，容易发现这样构造可以满足 $\sum|b_i| \le 10^9$ 的限制。

但是这样遗留下了一个问题，如果 $n$ 为奇数，那也就是说最后会剩下一个孤立点，我们肯定是要把这个孤立点合并进某一组中，方便起见，我们令 $a_{2i-1},a_{2i}$ 分做一组，将这个孤立点 $a_n$ 分进 $a_{n-2},a_{n-1}$ 这一组中。

不妨设 $x=a_{n-2} ,y=a_{n-1},z=a_{n}$ ，我们要解决的问题本质上是解一个三元一次方程 $ax+by+cz=0$ （**$a,b,c$ 为未知数，不是数组的名字**），我们需要构造一组解使得 $\sum|b_i| \le 10^9$ 的条件依然满足。

接下来有两种情况：

- 若 $x$ 不等于 $y$ ，那么直接令 $a=-z,b=z,c=x-y$，容易验证这一定合法。

- 若 $x$ 等于 $y$ ，模仿上面的思路，我们记 $s1=\dfrac{\text{lcm}(x,z)}{x},s2=\dfrac{\text{lcm}(x,z)}{z}$

	我们现在可以确定 $s2$ 可以为 $c$ ，并且不难发现这样一定是最优的，那么我们现在要解决的问题变成 :
    
    解方程 $ax+by+\text{lcm}(x,z)=0$ 并构造一组可行解。
    
    接下来又有两种情况（事实上可以化归成一种，但严谨起见，还是列出来）：
    
    + $s1 < 0$，此时很直接的我们想到将 $a$ 赋成 $-1$，$b$ 赋成 $s1+1$ 即可解决问题，很不幸，这是错的，形如 `-1 -1 -1 -1 -1` 这种数据可以卡掉它，所以我们还需要对 $s1=-1$ 的情况加入一个特判。
    
    + $s1 > 0$，此时可以将 $a$ 赋成 $1$ ，$b$ 赋成 $s1-1$ ，类似的还是要判 $s1=1$ 的情况。
    
 另外注意你很有可能因为某一些奇怪的越界或是 $int$ 类型的特性造成奇奇怪怪的错误，测一下`5
10000 9999 10000 10000 -9999` 这组数据应该可以查出来。

最后，如果你想要严谨的分析为什么 $\sum|b_i| \le 10^9$ 在任意条件下一定满足，你可以列几个比较复杂的不等式，但在这里不做赘述，感性理解即可。

当然，这是一道很有意思的构造题，方法很小清新，但是需要严谨的分类讨论 ，是近期 CF 出的最好的一道 2D 之一，~~相信可以给逐梦于OI之路上的你，提供一个有力的援助~~，会让你收获 $3-6$ 发罚时不等的好成绩。

相信你如果看懂了上文，代码也不难写出。

```cpp
#include<bits/stdc++.h>
#define MAXN 300010
#define int long long
using namespace std;
int T,n,a[MAXN+5];
int gcd(int x,int y){return (!y)?(x):gcd(y,x%y);}
int lcm(int x,int y){return x*y/gcd(x,y);}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		if(n%2==0){
			for(int i=1;i<=n;i+=2)
				printf("%lld %lld ",lcm(a[i],a[i+1])/a[i],-lcm(a[i],a[i+1])/a[i+1]);
			puts(""); continue;
		}for(int i=1;i<=n-3;i+=2) printf("%lld %lld ",lcm(a[i],a[i+1])/a[i],-lcm(a[i],a[i+1])/a[i+1]);
		int x=a[n-2],y=a[n-1],z=a[n];
		if(x!=y) printf("%lld %lld %lld\n",-z,z,x-y);
		else{
			int aandb=lcm(x,z)/x,ansc=lcm(x,z)/z;
			if(aandb<0){
				if(aandb==-1) printf("1 -2 ");
				else printf("-1 %lld ",aandb+1);
			}else{
				if(aandb==1) printf("-1 2 ");
				else printf("1 %lld ",aandb-1);
			}printf("%lld\n",-ansc);
		}
	}return 0;
}/*
7
-1 -1 -1 -1 -1 -1 -1
5
10000 9999 10000 10000 -9999
*/
```


---

## 作者：L0vely_NaiL0ng (赞：1)

对于 $n$ 为偶数，可以两两配对消去，具体而言对于一个奇数 $i$，构造 $b_i = a_{i + 1}, b_{i + 1} = -a_i$。

对于 $n$ 为奇数，可以留下最后 $3$ 个数，前面的两两消去。我们考虑最后 $3$ 个数是 $a_i,a_{i + 1},a_{i + 2}$，显然可以令 $b_i = a_{i + 2}, b_{i + 1} = a_{i + 2}, b_{i + 2} = -a_i - a_{i + 1}$，但是有一个问题如果 $b_{i + 2} = 0$ 怎么办呢？

- Case 1：$a_i + a_{i + 2} \ne 0$，可以 $b_i = a_{i + 1}, b_{i + 1} = -a_i - a_{i + 2}, b_{i + 2} = a_{i + 1}$。

- Case 2：$a_i + a_{i + 2} = 0$，我们断言此时有 $a_{i + 1} + a_{i + 2} \ne 0$，因为 $a_i + a_{i + 2} = 0, a_i + a_{i + 1} = 0$ 得到 $a_{i + 1} = a_{i + 2}$，因为 $a_{i + 1} \ne 0, a_{i + 2} \ne 0$，所以 $a_{i + 1} + a_{i + 2} \ne 0$，令 $b_i = -a_{i + 1} - a_{i + 2}, b_{i + 1} = a_i, b_{i + 2} = a_i$。

但是会有人问了，万一 $\sum_{i = 1}^n |b_i| > 10^9$ 怎么办？其实并不会出现这种情况，因为 $\sum_{i = 1}^n |b_i| \le (n + 1) \times 10^4$，当 $n$ 为奇数且 $\forall i \in [1, n], |a_i| = 10^4$ 时取等，$n$ 最大取 $2 \times 10^5 - 1$，此时上式刚好取到 $10^9$，$n$ 为偶数时更简单，$n = 2 \times 10^5$ 时取到 $10^9$。

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个长度为 $n$ 的不含 $0$ 的数组 $a$，$2\le n\le 10^5$，$|a_i|\le10^4$，需要构造一个不含 $0$ 的数组 $b$，使得 $\sum a_ib_i=0$，要求 $\sum b_i\le10^9$。
# 题目分析
首先如果 $n$ 是偶数时比较简单，只需要两两分成一组，$b_i=a_{i+1}$，$b_{i+1}=-a_i$ 即可。如果 $n$ 为奇数，考虑重新构造最后三个数的 $b$，$b_{n-2}=b_{n-1}=a_n$，$b_n=-(a_{n-1}+a_{n-2})$，这样还是满足和的条件。但是 $b_n$ 有可能为 $0$，可以换作 $b_{n-1}$ 或 $b_{n-2}$ 取另两个 $a$ 的和的相反数，必定有一种情况不是 $0$，输出这种情况即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[100001],b[100001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n)
			a[i]=read();
		if(n&1)
		{
			For2(i,1,n-1,2)
			{
				b[i]=a[i+1];
				b[i+1]=-a[i];
			}
			b[n-2]=b[n-1]=a[n];
			b[n]=-(a[n-2]+a[n-1]);
			if(b[n]==0)
			{
				b[n]=b[n-2]=a[n-1];
				b[n-1]=-(a[n]+a[n-2]);
				if(b[n-1]==0)
				{
					b[n]=b[n-1]=a[n-2];
					b[n-2]=-(a[n]+a[n-1]);
				}
			}
		}
		else
		{
			For2(i,1,n,2)
			{
				b[i]=a[i+1];
				b[i+1]=-a[i];
			}
		}
		For(i,1,n)
			printf("%d ",b[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

一道非常容易想出来的构造题。

首先，依次对于两个数进行构造，使他们所产生的代价为 $0$，本质上是对于两个数进行抵消。一种很显然的构造方法是：对于 $a_i$ 和 $a_{i+1}$，$b_i=a_{i+1},b_{i+1}=-a_i$。

若 $n$ 是偶数，我们采用以上方法构造即可。

若 $n$ 是奇数，这是我们必然会剩下一个数，但由于 $b$ 数组不能为 $0$，所以我们选取前 $n-3$ 个数按以上方法构造，剩下 $3$ 个数单独构造。

设剩下三个数为 $a,b,c$，不难列一个不定方程：$ax+by+cz=0$，即 $by+cz=-ax$。当 $b+c \neq 0$ 时，取 $y=z=-a,x=b+c$。当 $b+c=0$ 时，式子转化成 $b(y-z)=-ax$，可以取 $x=b,y-z=-a$。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e5+5;
int T,n,a[N],b[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=(n-2)/2*2;i+=2) b[i]=a[i+1],b[i+1]=-a[i];
		if(n&1) 
		{
			if(a[n]+a[n-1]==0) b[n-2]=a[n-1],b[n-1]=1e8,b[n]=1e8+a[n-2];
			else b[n-2]=a[n-1]+a[n],b[n-1]=b[n]=-a[n-2];
		}
		else b[n-1]=a[n],b[n]=-a[n-1];
		for(int i=1;i<=n;i++) printf("%d ",b[i]);
		puts("");
	}
	return 0;
}
```

---

