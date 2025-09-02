# [POI 2009] TAB-Arrays

## 题目描述

Consider an $n \times m$ table filled with **distinct** integers. The following operations can be performed on the table:  

1. Swapping two rows.  
2. Swapping two columns.  

We say that two tables are **similar** if, by applying some sequence of the above operations to the first table, we can obtain the second table.  

Write a program that determines for a given set of table pairs which pairs contain similar tables.  

## 样例 #1

### 输入

```
2
4 3
1 2 3
4 5 6
7 8 9
10 11 12
11 10 12
8 7 9
5 4 6
2 1 3
2 2
1 2
3 4
5 6
7 8
```

### 输出

```
TAK
NIE
```

# 题解

## 作者：_zy_ (赞：9)

## [题目传送门](https://www.luogu.com.cn/problem/P3492)

题目大意：

判断一个 $nm$ 的矩阵能否通过整行整列更改成目标矩阵。

------
我们很显然能知道的是：

对于一行数而言：

- 如果通过整行更改只改变了位置，并不会有什么其它改变；

- 而整列更改则会改变这一行数的顺序，并不会引起其他变化。

**总之，不论怎么变换，一行数到底是由哪几个数组成，是不会变化的！**

一列数同理。

所以我们只需要 $Judge$ 目标矩阵的每一行,每一列是不是在原矩阵中出现过即可。

-----

考虑每一列，每一行的数字组成映射成为一个数字。

显然可以构造：

###  $K= \sum_{i=1}^{n(m)}+\prod_{i=1}^{n(m)} $

来映射这一行或这一列的数字组成。

然后用 $map$ 来存储。

时间复杂度 $O_{Tmn}$.

**小细节：**

不要忘记开 $long$  $long$ ，亲测 $40$。

不要忘记清空 （数据应该没有卡这一部分。

目标数组没有出现所有在原矩阵的值也不可以。

~~分行列~~(~~其实题目中说明了元素两两不同，这个其实没有必要~~)

$//Updating$

**代码如下：**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define int long long 
#define N 10010
#define MOD 10000007
using namespace std;
int re() {
	int p=0,f=1; char i=getchar();
	while(i<'0'||i>'9')	{if(i=='-')  f=-1;i=getchar();}
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return f*p;
}
int T,n,m,cnt;
int a[N][N],f[N];
map<int , bool > v_x,v_y,u_x,u_y;
bool Judge() 
{
	u_x.clear();
	u_y.clear();
	for(int i=1;i<=n;i++)
	{
		int mul=1,sum=0;
		for(int j=1;j<=m;j++)	{
			mul*=a[i][j];
			mul%=MOD;
			sum+=a[i][j];
		}
		u_x[sum+mul]=1;
		if(!v_x[mul+sum])	return false;
	}
	for(int j=1;j<=m;j++)
	{
		int mul=1,sum=0;
		for(int i=1;i<=n;i++)
		{
			mul*=a[i][j];
			mul%=MOD;
			sum+=a[i][j];
		}
		u_y[sum+mul]=1;
		if(!v_y[mul+sum])	return false;
	}
	for(int i=1;i<=cnt;i++)
		if(!u_x[f[i]]&&!u_y[f[i]])	return false;
	return true;
}
signed main()
{
	T=re();
	while(T--)
	{
		memset(f,0,sizeof(f));
		v_x.clear(); v_y.clear();
		cnt=0;
		n=re(); m=re();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)	a[i][j]=re();
		for(int i=1;i<=n;i++)
		{
			int mul=1,sum=0;
			for(int j=1;j<=m;j++)	{
				mul*=a[i][j];
				mul%=MOD;
				sum+=a[i][j];
			}
			f[++cnt]=mul+sum;
			v_x[mul+sum]=1;
		}
		for(int j=1;j<=m;j++)
		{
			int mul=1,sum=0;
			for(int i=1;i<=n;i++)
			{
				mul*=a[i][j];
				mul%=MOD;
				sum+=a[i][j];
			}
			f[++cnt]=mul+sum;
			v_y[mul+sum]=1;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)	a[i][j]=re();
		if(Judge())	printf("TAK\n");
		else printf("NIE\n");
	}
}
```

**如果有不妥之处，请不要吝啬您的评论.**

[双倍经验](https://www.luogu.com.cn/problem/P3593)

$qwq$

---

## 作者：Microperson (赞：5)

[题目](https://www.luogu.com.cn/problem/P3492)

### 思路：
本题和[P3593](https://www.luogu.com.cn/problem/P3593)是一样的。
（但我仍然想水一波题解/kel）
对于这个题，因为每个数都不相同,并且在每次翻转时它的每一行，每一列都是确定的，我们可以用如下方式衡量：
 
$$Heng[i]=\begin{matrix} \sum_{i=1}^n a[i][j]\end{matrix}+\begin{matrix} \prod_{i=1}^n a[i][j] \end{matrix}$$

$$Shu[i]=\begin{matrix} \sum_{i=1}^m a[i][j]\end{matrix}+\begin{matrix} \prod_{i=1}^m a[i][j] \end{matrix}$$

- $Heng[i]$表示每一横行的处理结果;
- $Shu[i]$表示每一横行的处理结果

这样的话，我们就可以通过这种方式来处理翻转前后的数组，由于累乘时，数可能大一些，我们可以对乘积取模，因为矩阵时在翻转，而不是改变某个值，所以取模可能没事（我认为。qwq。当然，如果不对，还请指正。）

### 代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
#define N 1000010
#define mod 1000000007
using namespace std;

int T,n,m,a[1010][1010],b[1010][1010],flag1,heng1[N],shu1[N],shu2[N],heng2[N],flag2,pan;

void compare()
{
	sort(heng1+1,heng1+n+1);
	sort(heng2+1,heng2+n+1);
	sort(shu1+1,shu1+m+1);
	sort(shu2+1,shu2+m+1);
	for(int i = 1; i <= n; i++)
		if(heng1[i] != heng2[i]) flag1=1;
	for(int i = 1; i <= m; i++)
		if(shu1[i] != shu2[i]) flag2=1;
	if(flag1 || flag2) pan=1;
}
signed main()
{
	scanf("%d",&T);
	while(T--)
	{
		flag1=0;flag2=0;pan=0;
		int sum1=0,sum2=0,sum3=0,sum4=0,ch1=1,ch2=1,ch3=1,ch4=1;
		memset(heng1,0,sizeof(heng1));
		memset(heng2,0,sizeof(heng2));
		memset(shu1,0,sizeof(shu1));
		memset(shu2,0,sizeof(shu2));
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= n; i++){
			sum1 = 0; ch1 = 1;
			for(int j = 1; j <= m; j++){
				scanf("%d",&a[i][j]);
				sum1 += a[i][j];
				ch1 *= abs(a[i][j]);
				ch1 %= mod;
			}
			heng1[i] = sum1 + ch1;
		}
		for(int i = 1; i <= n; i++){
			sum2 = 0; ch2 = 1;
			for(int j = 1; j <= m; j++){
				scanf("%d",&b[i][j]);
				sum2 += b[i][j];
				ch2 *= abs(b[i][j]);
				ch2 %= mod;
			}
			heng2[i] = sum2 + ch2;
		}
		for(int j = 1; j <= m; j++){
			sum3 = 0; ch3 = 1;
			for(int i = 1; i <= n; i++){
				sum3 += a[i][j];
				ch3 *= abs(a[i][j]);
				ch3 %= mod;
			}
			shu1[j] = sum3 + ch3;
		}
		for(int j = 1; j <= m; j++){
			sum4 = 0; ch4 = 1; 
			for(int i = 1; i <= n; i++){
				sum4 += b[i][j];
				ch4 *= abs(b[i][j]);
				ch4 %= mod;
			}
			shu2[j] = sum4 + ch4;
		}
		compare();
		if(pan) cout<<"NIE"<<endl;
		else cout<<"TAK"<<endl;
	}
	return 0;
}
```



---

## 作者：Exp10re (赞：1)

典，太典了。

不太能理解其他题解为什么判断这么复杂，因此自己写一个。

## 解题思路

容易证明把其中一个矩阵通过若干次交换两行或者交换两列的操作变成另外一个矩阵的充分必要条件是：对于第一个矩阵中的每一行都能在第二个矩阵中找到其中一行使得其元素集相同，列同理。

此处不再证明，考虑做法。

注意到两个集合完全相同的必要条件是其异或和相同，那么考虑算出第一个矩阵每一行的异或和以及第二个矩阵每一行的异或和，列同理，分别排序后判断是否相同即可。

这一种做法将无解的情况判断为有解的机率是 $\frac {1} {2^k}$，其中 $k=\lceil\log_2 L\rceil$，$L$ 为值域，可以接受。

按理来说这种做法只需要一点小小的构造就能够卡掉（即：生成数据时生成两行不相同，但异或和相等），但是没卡。如果卡了就可以考虑对于每一个数生成一个唯一对应的随机数来进行判断，错判的几率依旧是 $\frac {1} {2^k}$。

单组数据时间复杂度 $O(n^2\log n)$，优化只加了一个快读，但是因为常数小暂时是[最优解](https://www.luogu.com.cn/record/list?pid=P3492&orderBy=1&status=&page=1)。

## 代码

码风问题看起来很长，实际上只有 1KB 多一点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1010;
int n,m,l1[MAXN],r1[MAXN],l2[MAXN],r2[MAXN];
int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ans=ans*10+c-'0';
		c=getchar();
	}
	return f*ans;
}
void work()
{
	memset(l1,0,sizeof(l1));
	memset(r1,0,sizeof(r1));
	memset(l2,0,sizeof(l2));
	memset(r2,0,sizeof(r2));
	int t,i,j;
	n=read();
	m=read();
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			t=read();
			l1[i]^=t;
			r1[j]^=t;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			t=read();
			l2[i]^=t;
			r2[j]^=t;
		}
	}
	sort(l1+1,l1+n+1);
	sort(l2+1,l2+n+1);
	sort(r1+1,r1+m+1);
	sort(r2+1,r2+m+1);
	for(i=1;i<=n;i++)
	{
		if(l1[i]!=l2[i])
		{
			printf("NIE\n");
			return;
		}
	}
	for(i=1;i<=m;i++)
	{
		if(r1[i]!=r2[i])
		{
			printf("NIE\n");
			return;
		}
	}
	printf("TAK\n");
	return;
}
int main()
{
	srand(time(0));
	int T;
	T=read();
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P3492)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-jie-p3492-poi2009tab-arrays)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

题目要求对于一个 $n \times m$ 的矩阵 $A$，能否通过交换某两行或某两列的元素得到另一个矩阵 $B$。注意到原矩阵的变换只改变了元素位置，并未改变元素本身，而且元素本身不重复，所以自然想到 $B$ 中的元素如果在 $A$ 中未出现过，那肯定就不能通过其变换而来。

同时发现每一行以及每一列的元素不会因为交换元素位置而改变，所以我们可以通过判断在 $A$ 中为同一行或同一列的元素是否也在 $B$ 中为同一行或同一列的元素来判断（好像楼上也是这么做的），虽然结论显然，但下面给出~~简短的~~证明。

对于矩阵 $A$ 中的两个同行元素 $A(i,j)$ 和 $A(i,k)$，若第 $i$ 行的元素交换到了第 $i'$ 行，则 $A(i,j)$ 的位置变为 $(i',j)$，$A(i,k)$ 的位置变为 $(i',k)$，依然位于同一行；若第 $j$ 列的元素交换到了第 $j'$ 列，则 $A(i,j)$ 的位置变为 $(i,j')$，$A(i,k)$ 的位置不变，依然位于同一行。同理可得两个同列元素变换位置后依然位于同一列。又因为所有元素互不相同，所以保证某一个元素的行数和列数具有唯一性。

$\Large\mathscr{Part\,\,2\;\;}\text{Code\qquad}$


```cpp
#include <cstdio>
#include <map>
using std::map;
const int N=1005;
int T,n,m,a[N][N],b[N][N]; // 存储矩阵
bool can=1; // 判断是否可行
map<int,int> x,y;
int main(){
	scanf("%d",&T); // 多组数据
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				scanf("%d",&a[i][j]);
				x[a[i][j]]=i; // 记录元素所在行数
				y[a[i][j]]=j; // 记录元素所在列数
			}
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				scanf("%d",&b[i][j]);
				if(x[b[i][j]]==0||y[b[i][j]]==0||x[b[i][j]]!=x[b[i][1]]||y[b[i][j]]!=y[b[1][j]]){ // 如果在 A 中没有这个元素或是这个元素与在 B 中同一行或同一列的元素在 B 中不在同一行或同一列
					can=0; // 则不可行
				}
			}
		}
		if(!can){ // 若不可行
			can=1;
			printf("NIE\n");
		}else{ // 反之
			printf("TAK\n");
		}
		x.clear(); y.clear(); //清空
	}
	return 0;
}

```

时间复杂度 $\Theta (Tnm)$，不卡常还是能[$\color{black}\text{过}$](https://www.luogu.com.cn/record/34061036)的。

---

## 作者：小手冰凉 (赞：1)

一个很显然的结论：无论如何交换，任何一列的元素或任何一行的元素是不会变的。


所以暴力判断即可


时间复杂度O(n\*n\*t)


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000005;
const int A=1000000;
int x[N];
int y[N];
int a[1005][1005];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    int T;
    T=read();
    while(T--){
        int n=read();
        int m=read();
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                int xxx=read();
                x[xxx+A]=i;
                y[xxx+A]=j;
            }
        bool b=true;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                a[i][j]=read();
                if(x[a[i][j]+A]!=x[a[i][1]+A]||x[a[i][j]+A]==0)b=false;
                if(y[a[i][j]+A]!=y[a[1][j]+A]||y[a[i][j]+A]==0)b=false;
            }
        }
        if(!b)printf("NIE\n");
        else printf("TAK\n");
    }
    return 0;
}
```

---

## 作者：羊羊君的幻想 (赞：0)

## 题意
给出两个 $n$ 行 $m$ 列的矩阵（$n,m\leq 150$），保证每个矩阵内元素互不相同且权值均在 $[-10^6,10^6]$ 之间，你需要报告能否把其中一个矩阵通过若干次交换两行或者交换两列的操作变成另外一个矩阵。

## 题解

我们通过模拟不难发现，无论我们怎么交换，最终都会符合以下结论：

- 从每一列来看，我们把初始矩阵的每一列编个号，然后随便交换每行或每列，交换之后，编号显然是错乱的，不过，对于初始矩阵和交换后的矩阵，我们发现，对于编号相同的一列，里面的数字顺序不一定相同，但包含的数字一定都相同。

- 从每一行来看，也同理。

- 综上，我们不难得出有解的充要条件。初始矩阵每一行或每一列出现的所有数字，目标矩阵都能找到对应的一行或一列的数字完全相同，那么就一定有解。

考虑怎么快速判断这个东西。不难发现，我们可以使用**和哈希**，这个东西在 CSP-S 2022 之后已经成为了广为人知的 Trick。

具体说来，对于每一个绝对值 $\leq10^6$ 的数，分配一个随机权值，把每一行或每一列的权值加起来，就是这一行或这一列的哈希值了，然后随便对比即可。

## 代码
```
int n,m;
unordered_map<int,int> dat;
int a[N],b[N];
int sumx[N],sumy[N];
int numx[N],numy[N];
void work(){
	n=read();m=read();
	memset(sumx,0,sizeof(sumx));
	memset(sumy,0,sizeof(sumy));
	memset(numx,0,sizeof(numx));
	memset(numy,0,sizeof(numy));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();		
			sumx[i]+=dat[x];
			sumy[j]+=dat[x];
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();		
			numx[i]+=dat[x];
			numy[j]+=dat[x];
		}
	}
	
	for(int i=1;i<=n;i++){
		a[i]=sumx[i];
	}
	for(int i=1;i<=n;i++){
		b[i]=numx[i];
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]){
			puts("NIE");
			return;		
		}
	}
		
	for(int i=1;i<=m;i++){
		a[i]=sumy[i];
	}
	for(int i=1;i<=m;i++){
		b[i]=numy[i];
	}
	sort(a+1,a+1+m);
	sort(b+1,b+1+m);
	for(int i=1;i<=m;i++){
		if(a[i]!=b[i]){
			puts("NIE");
			return;		
		}
	}
	puts("TAK");
	return;
}
mt19937 rnd(time(0));
signed main(){
	int t=read();
	for(int i=(int)-1e6;i<(int)1e6;i++){
		dat[i]=rnd();
	}
	while(t--){
		work();
	}


return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

[cnblogs 推销](https://www.cnblogs.com/xlpg-0713/articles/17803529.html)

## 题意：
$n$ 行 $m$ 列的矩阵，只能交换两行或交换两列，问能否从一个矩阵变成另一个。

## 分析：
交换两行，这两行内部不会有数字改变；交换两列，只会改变一行内的数字顺序，列同理。可以得出：交换之后原本一行和一列的数字是不会改变的。

所以判断结果矩阵的每行和每列是否和原矩阵的内容相等。如果不等是不可能的；如果相等，发现问题中的行和列是相互约束的，所以一定成立。

所以只用判断这些就可以了，按理说该用哈希的。但是他既然保证了元素不重而且是真的啥都不卡，我用了 map（乐）。

代码是易于理解的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, a[10010][10010];
map <map<int, bool>, int> sx, sy, tx, ty; //纯偷懒（乐子人）
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    cin >> t; while(t--){
        cin >> n >> m; sx.clear(), sy.clear(), tx.clear(), ty.clear();
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];
        for(int i = 1; i <= n; i++){ map<int, bool>mp; mp.clear();
            for(int j = 1; j <= m; j++) mp[a[i][j]] = 1; sx[mp]++;}
        for(int j = 1; j <= m; j++){ map<int, bool>mp; mp.clear();
            for(int i = 1; i <= n; i++) mp[a[i][j]] = 1; sy[mp]++;}
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> a[i][j];
        for(int i = 1; i <= n; i++){ map<int, bool>mp; mp.clear();
            for(int j = 1; j <= m; j++) mp[a[i][j]] = 1; tx[mp]++;}
        for(int j = 1; j <= m; j++){ map<int, bool>mp; mp.clear();
            for(int i = 1; i <= n; i++) mp[a[i][j]] = 1; ty[mp]++;}
        cout << (sx==tx&&sy==ty?"TAK\n":"NIE\n"); //map是有内置判断等于的
    }
}
```

---

## 作者：Leowang2009 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3492)
# 思路
个人感觉这个题还是比较水的，直接用哈希就可以水过。

首先是为什么可以用哈希。~~（这个应该还是比较显然的吧）~~

其实这道题只用比较目标矩阵和初始矩阵每行和每列元素是否一样就可以了，甚至不用在乎顺序，因为就算顺序不对也可以再调。

接下来思考如何快速比较每行每列元素是否相同，容易想到用哈希。具体做法是将不同的数赋值，这一步可以用 ```mt19937``` 实现。具体代码如下：
```cpp
mt19937 myrand(time(0));
for(int i=1;i<2e6+10;i++) h[i]=myrand();
```
然后分别计算初始矩阵与目标矩阵每行每列的哈希值，然后排序（这步很重要，因为可以通过交换改变其顺序），最后比较。如果发现不同直接返回。
# 代码实现
题目中说明矩阵取值可能为负数，需要将所有值加上一个足够大的数将其变为非负数，还有记得要开 ```long long```。
## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+5,M=1e6+5;
int t,n,m,a,h[2*M];
unsigned long long cola[N],rowa[N],colb[N],rowb[N];
signed main(){
	mt19937 myrand(time(0));
	for(int i=1;i<2*M;i++) h[i]=myrand();//给数赋值
	scanf("%lld",&t);
	while(t--){
		memset(cola,0,sizeof cola),memset(colb,0,sizeof colb);
		memset(rowa,0,sizeof rowa),memset(rowb,0,sizeof rowb);//多组数据需要初始化
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%lld",&a),cola[j]+=h[a+M],rowa[i]+=h[a+M];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%lld",&a),colb[j]+=h[a+M],rowb[i]+=h[a+M];//输入的同时计算哈希值，还有要将负数变为正数
		sort(cola+1,cola+m+1),sort(rowa+1,rowa+n+1);
		sort(colb+1,colb+m+1),sort(rowb+1,rowb+n+1);//排序
		for(int i=1;i<=m;i++) if(cola[i]!=colb[i]) goto NIE;
		for(int i=1;i<=n;i++) if(rowa[i]!=rowb[i]) goto NIE;//如果不同直接返回
		printf("TAK\n");continue;
		NIE:printf("NIE\n");
	}
	return 0;
}
```
完结撒花！

---

## 作者：Alex_Wei (赞：0)

> [P3492 [POI2009]TAB-Arrays](https://www.luogu.com.cn/problem/P3492)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/poi.html)。

因为任何操作不改变每一行和每一列由哪些数组成，只是改变它们的顺序，故只需判断 $a, b$ 每一行和每一列的数字能否对应上，即对于 $a$ 的每一行 $a_i$，存在 $b$ 的某一行 $b_j$，使得 **可重集** $\{a_i\} = \{b_j\}$，且一行 $a_i$ 与一行 $b_j$ 唯一对应，对于列同理。

由于数字无序，可以排序后哈希（如字符串哈希），也可以使用不依赖于数字顺序的哈希方法（如 $\sum a_{i, k} + \prod a_{i, k}$），再看 $a, b$ 的每一行（列）的哈希值是否能够一一对应（简单的检查方法是排序后相同排名的数相等）。前者时间复杂度是 $\mathcal{O}(nm(\log  n + \log m))$，后者时间复杂度是 $\mathcal{O}(nm + n\log n + m\log m)$。效率差距较大。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}

#define ull unsigned long long 
const int N = 1e3 + 5;
const ull base = 1e9 + 7;
ull h1[N], h2[N];
int T, n, m, a[N][N], b[N][N];
void solve() {
	cin >> n >> m, memset(h1, 0, N << 3), memset(h2, 0, N << 3);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) b[i][j] = read();
	for(int i = 1; i <= n; i++) {
		static int v[N], w[N]; memcpy(v, a[i], N << 2), memcpy(w, b[i], N << 2);
		sort(v + 1, v + m + 1), sort(w + 1, w + m + 1);
		for(int j = 1; j <= m; j++) h1[i] = h1[i] * base + v[j], h2[i] = h2[i] * base + w[j];
	} sort(h1 + 1, h1 + n + 1), sort(h2 + 1, h2 + n + 1);
	for(int i = 1; i <= n; i++) if(h1[i] != h2[i]) return puts("NIE"), void();
	memset(h1, 0, N << 3), memset(h2, 0, N << 3);
	for(int i = 1; i <= m; i++) {
		static int v[N], w[N];
		for(int j = 1; j <= n; j++) v[j] = a[j][i], w[j] = b[j][i];
		sort(v + 1, v + n + 1), sort(w + 1, w + n + 1);
		for(int j = 1; j <= n; j++) h1[i] = h1[i] * base + v[j], h2[i] = h2[i] * base + w[j];
	} sort(h1 + 1, h1 + m + 1), sort(h2 + 1, h2 + m + 1);
	for(int i = 1; i <= m; i++) if(h1[i] != h2[i]) return puts("NIE"), void();
	puts("TAK");
}
int main() {
	int T; cin >> T; while(T--) solve();
	return 0;
}
```

---

## 作者：红尘仙 (赞：0)

### Description :

给定初始矩阵和结果矩阵，询问是否可以通过转化任意两行或两列将初始矩阵转化为结果矩阵。$n , m \leq 10^3$

### Solution : 

把 Hash 卡了，这个人写了 `unsigned long long`  被卡成了 70 分，瞅了一眼题解，然后就过了。

我们知道两道简单到不能再简单的两个性质 ： 

+ 经过若干变化，这一行或者一列是可以到达当前矩阵的任意行或者列的。
+ 不管怎么变化，一行或者一列的元素是不会变的。

所以，我们直接考虑将初始矩阵的一行或一列直接压成一个状态，我们可以用 hash 解决，即当前行的 Hash 值为 ： $k = (\prod_{i = 1}^{m}a_{i} \ \ + B )$  。 

通过添加一个特殊的 $B$ , 我们被卡掉的几率就会变小。
这里选择的 $B = \sum_{i = 1}^m B \   \ or \ \ a_i$ 。

同样的，我们将结果矩阵也是按照这样处理，同样可以得到当前行列的 Hash 值，将此 Hash 值在行或者列形成 `map` 中一查就好了。

### Notice : 
+ 一定要加特殊的值 $B$ , 如果不加，只将 $k = \prod_{i = 1}^{m} a_i$ 尽管你用 `unsigned long long` 自然溢出，也会被卡成 70 分。

+ 行和列分别开一个 `map` ， 不能将行和列混淆 。

+ [双倍经验](https://www.luogu.com.cn/problem/P3593)

### Code :

```
//
/*
Author : Zmonarch
Knowledge :
*/
#include <bits/stdc++.h>
#define int long long
#define inf 2147483647
#define qwq register
#define qaq inline
#define ull unsigned long long 
using namespace std ;
const int kmaxn = 1e3 + 10 ;
qaq int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
int n , m ; 
map<ull , bool> h , l ;
int a[kmaxn][kmaxn] ; 
qaq bool Check() {
	for(qwq int i = 1 ; i <= n ; i++)
	{
		ull A = 1 , B = 0;
		for(qwq int j = 1 ; j <= m ; j++) 
		 A *= a[i][j] , B = B ^ a[i][j] ; 
		A += B ; 
		if(h.find(A) == h.end()) return false ; 
	}
	for(qwq int j = 1 ; j <= m ; j++) 
	{
	 	ull A = 1 , B = 0; 
		for(qwq int i = 1 ; i <= n ; i++) 
		 A *= a[i][j] , B = B ^ a[i][j] ;  
		A += B ; 
		if(l.find(A) == l.end()) return false ;	
	}
	return true ; 
}
signed main() {
	int T = read() ; 
	for(qwq int oi = 1 ; oi <= T ; oi++) 
	{
		n = read() , m = read() ; h.clear() , l.clear() ;
		for(qwq int i = 1 ; i <= n ; i++) 
		 for(qwq int j = 1 ; j <= m ; j++) 
		  a[i][j] = read() ; 
		for(qwq int i = 1 ; i <= n ; i++) 
		{
			ull A = 1 , B = 0; 
			for(qwq int j = 1 ; j <= m ; j++) 
			 A *= a[i][j] , B = B ^ a[i][j] ; 
			A += B ; 
			h[A] = 1 ; 
		}
		for(qwq int j = 1 ; j <= m ; j++) 
		{
			ull A = 1 , B = 0 ; 
			for(qwq int i = 1 ; i <= n ; i++)
			 A *= a[i][j] , B = B ^ a[i][j] ;   
			A += B ; 
			l[A] = 1 ; 
		}
		for(qwq int i = 1 ; i <= n ; i++) 
		 for(qwq int j = 1 ; j <= m ; j++) 
		  a[i][j] = read() ;
		if(Check()) printf("TAK\n") ; 
		else printf("NIE\n") ; 
	}
	return 0 ;
}
```

---

