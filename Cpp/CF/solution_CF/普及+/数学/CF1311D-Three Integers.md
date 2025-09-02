# Three Integers

## 题目描述

题目给出三个整数 $a \le b \le c$。

在一次操作中，你可以给这三个数中任意一个数 $+1$ 或 $-1$。你可以用同一个数字做这样的操作任意次。但你要保证，变换过后的数，是一个正数。

你想要用最小操作步数使得三个整数 $A \le B \le C$ 能够符合：$B$ 能被 $A$ 整除， $C$ 能被 $B$ 整除。

你需要回答 $t$ 组询问。

## 样例 #1

### 输入

```
8
1 2 3
123 321 456
5 10 15
15 18 21
100 100 101
1 22 29
3 19 38
6 30 46```

### 输出

```
1
1 1 3
102
114 228 456
4
4 8 16
6
18 18 18
1
100 100 100
7
1 22 22
2
1 19 38
8
6 24 48```

# 题解

## 作者：andyli (赞：8)

### 解法1：  
暴力枚举三元组$(x,y,z)$并统计答案，注意到$y$一定是$x$的倍数，$z$也一定是$y$的倍数，所以枚举$y$和$z$时只需枚举$x(y)$的倍数即可。枚举上限为$2c$。  
注意，若只枚举到$c$，`37 10000 10000`这组数据是不能通过的。  
时间复杂度$\mathcal O(c\log^2c)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int a, b, c;
        io.read(a, b, c);
        int ans = -1u / 2, ansa = 0, ansb = 0, ansc = 0;
        for (int i = 1; i <= (c << 1); i++)
            for (int j = i; j <= (c << 1); j += i)
                for (int k = j; k <= (c << 1); k += j) {
                    int t = abs(a - i) + abs(b - j) + abs(c - k);
                    if (t < ans)
                        ans = t, ansa = i, ansb = j, ansc = k;
                }
        writeln(ans);
        writeln(ansa, " ", ansb, " ", ansc);
    }
    return 0;
}
```

### 解法2：  
考虑只枚举$y$，则只需在$y$的约数中找到一个距离$a$最近的数$x$即可。同理，也可在$y$的倍数中找到一个距离$c$最近的数$z$，并统计三元组$(x,y,z)$对答案的贡献。仿照解法1，$y$的枚举上限也为$2c$。  
时间复杂度 $\mathcal O(c\log c)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxc = 10000;

vector<int> divisors[(maxc << 1) + 5];
int main()
{
    int q;
    io.read(q);
    for (int i = 1; i <= (maxc << 1); i++)
        for (int j = i; j <= (maxc << 1); j += i)
            divisors[j].push_back(i);
    while (q--) {
        int a, b, c;
        io.read(a, b, c);
        int ans = -1u / 2, ansa = 0, ansb = 0, ansc = 0;
        for (int y = 1; y <= (c << 1); y++) {
            // 在y的约数中找到一个与a最接近的数x
            int x;
            auto it = lower_bound(divisors[y].begin(), divisors[y].end(), a);
            if (it != divisors[y].end())
                x = *it;
            else
                x = *(it - 1);
            if (it != divisors[y].begin() && a - *(--it) < x - a)
                x = *it;
            // 在y的倍数中找到一个与c最接近的数z
            int z = y + (c - y) / y * y;
            if (abs((y + (c - y) / y * y + y) - c) < abs(z - c))
                z = (y + (c - y) / y * y + y);
            // 统计对答案的贡献
            int t = abs(a - x) + abs(b - y) + abs(c - z);
            if (t < ans)
                ans = t, ansa = x, ansb = y, ansc = z;
            if (!ans)
                break;
        }
        writeln(ans);
        writeln(ansa, " ", ansb, " ", ansc);
    }
    return 0;
}
```

---

## 作者：ix35 (赞：3)

解法不想说了，就说一下上界。

因为我很菜，所以只能先估一个 $15000$ 的上界。

证明：

首先，设 $t$ 为 $a,b,c$ 的中位数，令 $A=B=C=t$，显然是一种合法方案，且代价为 $\max(a,b,c)-\min(a,b,c) < 10000$。

假设上界超过了 $15000$，那么 $B>15000$，由于 $B|C$，所以 $C>15000$，又由于 $b,c\leq 10000$，所以花在这两个数的代价就已经超过了 $10000$，一定不是最优解。

事实上的上界应该远比这要小，希望有人能给出个更紧一些的上界。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=30010;
int t,a,b,c,ansa,ansb,ansc;
vector <int> v[MAXN];
int main () {
	scanf("%d",&t);
	for (int i=1;i<=30000;i++) {
		for (int j=1;j*j<=i;j++) {
			if (!(i%j)) {
				v[i].push_back(j);
				if (j*j<i) {v[i].push_back(i/j);} 
			}
		}
	}
	for (int ii=1;ii<=t;ii++) {
		scanf("%d%d%d",&a,&b,&c);
		int ans=30000;
		for (int i=1;i<=15000;i++) {
			int tmp1=30000,tmp2=30000,tmpa=0,tmpc=0;
			for (int j=0;j<v[i].size();j++) {
				if (tmp1>abs(a-v[i][j])) {tmp1=abs(a-v[i][j]),tmpa=v[i][j];}
			}
			int k=c/i;
			if (c-i*k<i*(k+1)-c) {
				tmp2=c-i*k,tmpc=i*k;
			} else {
				tmp2=i*(k+1)-c,tmpc=i*(k+1); 
			}
			if (tmp1+tmp2+abs(b-i)<ans) {
				ans=tmp1+tmp2+abs(b-i),ansa=tmpa,ansb=i,ansc=tmpc;
			}
		}
		printf("%d\n%d %d %d\n",ans,ansa,ansb,ansc);
	}
	return 0;
}
```


---

## 作者：2huk (赞：2)

## D. [Three Integers](https://codeforces.com/contest/1311/problem/D)

### Description

给定 $3$ 个整数 $a, b, c$。

你需要求 $3$ 个数 $A, B, C$，满足 $A \mid B$，$B \mid C$，且 $|a - A| + |b - B| + |c - C|$ 的值最小。

$A \le B \le C \le 10^4$。

### Solution

如果已知了 $B$，那么 $A$ 和 $C$ 都很好求。也就是 $A$ 是 $B$ 的约数，$C$ 是 $B$ 的倍数。

观察到数据范围其实不大，那么我们可以枚举中间值 $B$，并求出与 $a$ 差值最小的约数和与 $c$ 差值最小的倍数。然后更新最小值即可。

找到一个数的约数和倍数可以预处理，用 `vector` 存储。

关于 $3$ 个数的上限，~~其它题解说~~最大为 $1.5 \times 10^4$。我赛时不会推就直接枚举到 $10^5$ 了。

### Code

```cpp
void init(int n)
{
	for (int i = 1; i <= n; ++ i )
		for (int j = i; j <= n; j += i )
			d[j].push_back(i),
			m[i].push_back(j);
}

void Solve()
{
	int a = read(), b = read(), c = read();
	int res = INF, resa, resb, resc;
	for (int B = 1; B <= 1e5; ++ B )
	{
		int A = INF, C = INF;
		for (auto i : d[B]) 
			if (abs(i - a) < abs(A - a))
				A = i;

		for (auto i : m[B]) 
			if (abs(i - c) < abs(C - c))
				C = i;
				
		
		int k = abs(A - a) + abs(B - b) + abs(C - c);
		if (k < res)
		{
			res = k;
			resa = A, resb = B, resc = C;
		}
	}
	
	cout << res << '\n' << resa << ' ' << resb << ' ' << resc << '\n';
}
```

---

## 作者：ShineEternal (赞：2)

[更佳的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/104505461)

## description：
- 给定你三个数 $a,b,c$ ，保证 $a\le b\le c$。
- 一次操作中，你可以将任何一个数 $+1$ 或者 $-1$ 。
- 问你最少要用多少次操作，可以使得 $a$ 是 $b$ 的因数， $b$ 是 $c$ 的因数。
- **多组数据**，数据组数不大于 $100$，$1\le a,b,c\le 10^4$。
- 先输出最少的操作次数，再输出最终的方案。（方案如果有多组可输出任意一组。）

## solution：
我们发现中间的数 $b$ 是一个与其他两个数都有直接关系的数，所以考虑对 $b$ 进行枚举。

观察数据范围，我们枚举到 $1.5\times 10^4$ 就够了。

然后我们枚举每一个 $b$ 的所有因数，每一个 $b$ 的所有倍数，找到最少的操作次数即可。
## code：
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int Abs(int x)
{
	if(x<0)return -x;
	return x;
}
int Min(int x,int y)
{
	if(x<y)return x;
	return y;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int aa,b,c;
		scanf("%d%d%d",&aa,&b,&c);
		int AAA,BBB,CCC;
		int sum=0x3f3f3f3f;
		for(int i=1;i<=15000;i++)
		{
			int ans=0;
			int Zuo,You;
			
			int tmp=0x3f3f3f3f;
			int qaq=sqrt(i);
			ans=Abs(b-i);
			for(int j=1;j<=qaq;j++)
			{
				if(i%j!=0)
				{
					continue;
				}
				if(Abs(aa-j)<tmp)
				{
					tmp=Abs(aa-j);
					Zuo=j;
				}
				if(Abs(aa-(i/j))<tmp)
				{
					tmp=Abs(aa-(i/j));
					Zuo=i/j;
				}
			}
			ans+=tmp;
			tmp=0x3f3f3f3f;
			for(int j=i;j<=32000;j+=i)
			{
				if(Abs(c-j)<tmp)
				{
					You=j;
					tmp=Abs(c-j);
				}
			}
			ans+=tmp;
			if(ans<sum)
			{
				sum=ans;
				AAA=Zuo;
				BBB=i;
				CCC=You;
			}
		}
		printf("%d\n",sum);
		printf("%d %d %d\n",AAA,BBB,CCC);
	}
	return 0;
}
```

---

## 作者：Ludo (赞：2)

## Part I. 思考过程

其实就是暴力就行了。

然而比赛时没写出来。

枚举每一个符合题目条件的三元组。

然后小就取，这样就好了。

而且还好调。

枚举每一个数 $i$，表示答案中 $a$ 的取值范围，范围当然是 $[1,10000+k_1]$的整数，因为 $a \in [1,10000], a \in N_+$，因此答案有可能超过 $10000$，加个常数 $k_1$ 保障就可以了。$k_1$ 可以取 $1000$。

然后枚举 $j$，$j$ 表示答案中 $b$ 的取值范围，因此根据题目 $j$ 必须是 $i$ 的倍数可得 $b \in [i,k_2i], b \in N_+, k_2i \leq 10000+k_1$。

$k$ 同理。

## Part II. 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t,a,b,c;
int ans,ansi,ansj,anssk;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&a,&b,&c);
		ans=1100000000;
		for (int i=1;i<=11000;i++)
		{
			for (int j=i;j<=11000;j+=i)
			{
				for (int k=j;k<=11000;k+=j)
				{
					if (abs(a-i)+abs(b-j)+abs(c-k)<ans)
					{
						ans=min(ans,abs(a-i)+abs(b-j)+abs(c-k));
						ansi=i;ansj=j;anssk=k;
					}
				}
			}
		}
		printf("%d\n%d %d %d\n",ans,ansi,ansj,anssk);
	}
}
```


---

## 作者：gyh20 (赞：1)

观察此题，发现数据范围不大，所以不考虑结论，直接上暴力。

令输入为 $a,b,c$ 答案为 $A,B,C$。

先枚举 $A$，再枚举 $A$ 的每一个倍数 $B$,最后的 $C$ 肯定等于 $c/B \times B$ 或 $(c/b+1) \times B$ 进行枚举即可。

但还有一点，在极限数据中 $B$ 的值可能大于 $10000$ 所以 $B$ 的上界最好开大一点（好像 $10050$ 就够了）。

比如当 $a=137,b=10000,c=10000$ 时，答案为 $A=137,B=10001,C=10001$，此时 $B$ 就大于 $10000$。~~（因此错失 rank9）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,a,b,c,d,e,f,ans,x,y;
int main(){
	t=read();
	while(t--){
		ans=1e9;
		a=read();
		b=read();
		c=read();
		for(re int i=1;i<=10000;++i){
			for(re int j=i;j<=10000;j+=i){
				int tmp=c/j;
				if(abs(tmp*j-c)<abs((tmp+1)*j-c))x=tmp*j;
				else x=(tmp+1)*j;
				if(abs(i-a)+abs(j-b)+abs(x-c)<ans){
					ans=abs(i-a)+abs(j-b)+abs(x-c);
					d=i,e=j,f=x;
				}
			}
		}
		printf("%d\n%d %d %d\n",ans,d,e,f);
	}
}
```


---

## 作者：极寒神冰 (赞：0)

先处理出小于$4e4$的数的因子

对于每一组$(a,b,c)$，考虑枚举$b$，每次二分出合法且最小的$a$，算出最小的$c$,取最小的一组即可。

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define Max(a,b) ((a>b)?a:b)
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=4e4+4;
std::vector<int> fac[N];
int _,a,b,c,res,A,B,C;
inline void init()
{
	for(int i=1;i<(int)4e4;i++) 
		for(int j=i;j<(int)4e4;j+=i) fac[j].pb(i);
}
signed main()
{
	init();
	for(_=read();_;_--)
	{
		a=read(),b=read(),c=read(),res=(int)1e9;
		for(int i=1;i<b+res;i++)//枚举b
		{
			int tmpa,tmpc;
			int it=lower_bound(fac[i].begin(),fac[i].end(),a)-fac[i].begin();
			if(it==(int)fac[i].size()) tmpa=fac[i][it-1];
			else if(!it) tmpa=fac[i][0];
			else if(fac[i][it]-a<a-fac[i][it-1]) tmpa=fac[i][it];
			else tmpa=fac[i][it-1];
			//选最近且合法的A
			if(c%i<i-c%i) tmpc=c/i*i;
			else tmpc=c/i*i+i;
			int ans=abs(tmpa-a)+abs(i-b)+abs(tmpc-c);
			if(ans<res) res=ans,A=tmpa,B=i,C=tmpc;
		}
		printf("%lld\n%lld %lld %lld\n",res,A,B,C);

	}
}
```


---

## 作者：L2_sheep (赞：0)

题意：
输入三个数a,b,c,满足a<=b<=c。可以对三个数进行任意次+1或-1的操作。使其满足b能被a整除,c能够被b整除
输出最小的操作次数，和改变后的A,B,C

以当前的答案（变量min）作为上界，从中间（最靠近a,b,c的数）向两边搜索。
具体代码如下：

```cpp
int main()
{		
	
			
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &a, &b, &c);
		min = 111111111;
		for(i = a, da = 0; da < min; i++, da++){
			j = b / i * i;
			db = b - j;
			for( ; j >= i && da + db < min; j -= i, db += i){
				k = c / j * j;
				dc = c - k;
				if(k >= j && (s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
				k += j, dc = k - c;
				if((s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
			}
			j = b / i * i + i, db = j - b;
			for( ; da + db < min; j += i, db += i){
				k = c / j * j;
				dc = c - k;
				if(k >= j && (s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
				k += j, dc = k - c;
				if((s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
			}
		}
		for(i = a - 1, da = 1; i > 0 && da < min; i--, da++){
			j = b / i * i;
			db = b - j;
			for( ; j >= i && da + db < min; j -= i, db += i){
				k = c / j * j;
				dc = c - k;
				if(k >= j && (s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
				k += j, dc = k - c;
				if((s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
			}
			j = b / i * i + i, db = j - b;
			for( ; da + db < min; j += i, db += i){
				k = c / j * j;
				dc = c - k;
				if(k >= j && (s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
				k += j, dc = k - c;
				if((s = da + dc + db) < min){
					min = s, A = i, B = j, C = k;
				}
			}
		}
		printf("%d\n%d %d %d\n", min, A, B, C);
	}
			
	return 0;
}
```


---

## 作者：zhmshitiancai (赞：0)

[门](https://codeforces.ml/contest/1311/problem/D)

题意，给三个数$a,b,c$，每次操作使一个数$+1$或$-1$，但不能使一个数变成负数或$0$，问最少多少次操作，使得$b$是$a$的倍数，$c$是$b$的倍数。

$a \leq b \leq c \leq  2*10^4$

做法，设最后答案为$A$，$B$，$C$，且$A \leq B \leq C$

枚举$A$,从$1 \to 2a$ 显然$A\leq 2a$，不然就令$A=1$，这样显然更优。

再枚举$B$,从$1\to2b$，且$B$是$A$的倍数。

最后由$B$确定$C$，是$O(1)$的。

由于调和级数，总复杂度是$O(n log n)$


**code**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f;
int n;
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,T,j;
	cin>>T;
	while(T--)
	{
		int a,b,c;
		int x,y,z;
		cin>>a>>b>>c;
		int ans=INF,A,B,C;
		for(x=1;x<=2*a;x++)
		{
			for(j=1;j*x<=2*b;j++)
			{
				y=j*x;
				int z1=(c/y)*y,z2=(c/y+1)*y;
				if(abs(z1-c)<abs(z2-c))
					z=z1;
				else 
					z=z2;
				if(abs(x-a)+abs(y-b)+abs(z-c)<ans)
				{
					A=x;B=y;C=z;
					ans=abs(x-a)+abs(y-b)+abs(z-c);
				}
			}
		}
		printf("%d\n",ans);
		printf("%d %d %d\n",A,B,C);
	}
}
```

---

## 作者：riker_moon (赞：0)

这题其实只需要枚举A和B然后通过B算出C，这样应该会更快一点吧

目前最优解rk1

### 大体思路：
首先枚举A,B，然后贪心一下，因为要让变化的最少所以C必然是B的 $(C / B) $ 倍或$ (C / B + 1) $倍，所以用B算出C取最小值即可

代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<cmath>
#define maxn 10007
#define ll long long  
using namespace std;
int T,n,a,b,c,ans1,ans2,ans3,ans,sum,maxx; 
inline int read()
{
	int x = 0;
	int flag = 1;
	char ch;
	ch = getchar();
	while(!isdigit(ch)) 
	{
		if(ch == '-') flag = -1;
	ch = getchar();
	} 
	while(isdigit(ch))
	{
		x = (x<<1) + (x<<3) + ch - 48;
		ch = getchar();
	}
	return x * flag;
}


int main()
{
	T = read();
	while(T--)
	{
		a = read();
		b = read();
		c = read();
		maxx = c + 100;
		ans = 1e9;
		for(register int i = 1;i <= maxx;i++)
		{
			for(register int j = i;j <= maxx;j += i)
			{
				sum = abs(i - a) + abs(j - b) + min(c % j,j - (c % j));
				if(sum < ans)
				{
					ans = sum;
					ans1 = i;
					ans2 = j;
					ans3 = (c % j) < (j - (c % j)) ? c - (c % j) : c + j - (c % j);
				}
			}
		}
		printf("%d\n%d %d %d\n",ans,ans1,ans2,ans3);
	}
	
	return 0;
}

```

不过我好菜啊E题直接懵掉最后rank183


---

## 作者：Trilliverse (赞：0)

~~题目翻译已经给出，在此就不再赘述了~~
### 题目分析
- 由题意可得，$A$ 是 $B$ 的因子，$C$ 是 $B$ 的倍数，枚举满足条件的一组3个数，然后不断更新最小的代价即可.~~楼上大佬已经说的很清楚了，orz~~

### 题目代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int INT_INF = 0x3f3f3f3f;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int a,b,c;
		cin >> a >> b >> c;
		int ans = INT_INF;
		int ansa,ansb,ansc;
		
		for(int i=1;i<=10010;i++) {
			for(int j=i;j<=10010;j+=i) {
				for(int k=j;k<=10010;k+=j) {
					int t = abs(a-i) + abs(b-j) + abs(c-k);
					if(t < ans) {
						ans = t;
						ansa = i;
						ansb = j;
						ansc = k;
					}
				}
			}
		}
		cout << ans << endl;
		cout << ansa << " " << ansb << " " << ansc << endl;
	}
	return 0;
}
```


---

