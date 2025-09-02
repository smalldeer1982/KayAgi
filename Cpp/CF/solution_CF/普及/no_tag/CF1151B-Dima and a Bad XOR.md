# Dima and a Bad XOR

## 题目描述

来自克雷姆兰德的学生迪马有一个大小为 $n \times m$ 的矩阵，其中只包含非负整数。

他希望从矩阵的每一行中选出一个整数，使得所选整数的按位异或严格大于零。

也就是说，他想选择一个整数序列 $c_1,c_2,\dots,c_n$ $(1\leq c_j \leq m)$ 使得不等式 $a_{1,c_1}\oplus a_{2,c_2}\dots \oplus a_{n,c_n} > 0$成立，其中 $a_{i,j}$ 是第 $i$ 行和第 $j$ 列的矩阵元素。

$x\oplus y$ 表示 $x$ 和 $y$ [按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)，这里是他的定义。

## 说明/提示

在第一个例子中，矩阵中的所有数字都是0，因此不可能在表的每一行中选择一个数字，以使它们的按位异或严格大于零。

在第二个例子中，所选数字是 $7$（第一行中的第一个数字）和$10$（第二行中的第三个数字），$7 \oplus 10 = 13$ , $13$ 大于 $0$ ，因此找到了答案。

## 样例 #1

### 输入

```
3 2
0 0
0 0
0 0
```

### 输出

```
NIE
```

## 样例 #2

### 输入

```
2 3
7 7 7
7 7 10
```

### 输出

```
TAK
1 3 
```

# 题解

## 作者：Karnage (赞：9)

# CF1151B Dima and a Bad XOR

[**题目链接**](https://www.luogu.org/problemnew/show/CF1151B)

题意简述：给定$n, m(1≤n,m≤500)$和大小为$n*m$的矩阵，问能否在每一行选出一个数，使选出的$n$个数异或和大于$0$，输出方案。

观察到$n,m$并不大，考虑**随机大法**。

从每一行**随机**选出一个数，将**随机选出**的$n$个数求异或和，判断是否满足大于$0$，这样做一次复杂度是$O(n)$的。

只做一次存在较大偶然性，但是我们做$50000$次就能妥妥$AC$啦！

## Code

```cpp
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 505;
int n, m, a[N][N], f[N];

int main() {
    srand(326);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
    for (int oo = 1; oo <= 50000; ++oo) {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            f[i] = rand() % m + 1;
            res ^= a[i][f[i]];
        }
        if (res > 0) {
            puts("TAK");
            for (int i = 1; i <= n; ++i) printf("%d ", f[i]);
            return puts(""), 0;
        }
    }
    puts("NIE");
    return 0;
}
```

---

## 作者：fuxuantong123 (赞：5)

# CF1151B Dima and a Bad XOR 题解
## 思路
构造题，不建议随机化（虽然能过）。

首先，把每一行的第一列异或起来，如果不为 $0$ 就直接输出。

否则，考虑将序列中一个数更换为一个不同的。若有，则一定可行。

就是在每行中找一个与这一行第一个数不同的数，有就直接输出，都没有就无解。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[510][510];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	x=a[1][1];
	for(int i=2;i<=n;i++){
		x^=a[i][1];
	}
	if(x>0){
		printf("TAK\n");
		for(int i=1;i<=n;i++){
			printf("1 ");
		}
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(a[i][j]!=a[i][1]){
				printf("TAK\n");
				for(int x=1;x<i;x++){
					printf("1 ");
				}
				printf("%d ",j);
				for(int y=i+1;y<=n;y++){
					printf("1 ");
				}
				return 0;
			}
		}
	}
	printf("NIE");
return 0;
}
```


---

## 作者：da32s1da (赞：3)

考虑一个有趣的做法

我们将矩阵每一行$\mathrm{random\_shuffle}$一下，然后只取每一列看异或是否为0。

这种做法大数据是不容易卡掉的，反倒是小数据容易卡。实测做**3**次即可AC

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=505;
typedef pair<int,int> pr;
int n,m,x;
pr a[N][N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)scanf("%d",&a[i][j].first),a[i][j].second=j;
	for(int k=1;k<=3;k++){//做少了容易被卡
		for(int i=1;i<=n;i++)random_shuffle(a[i]+1,a[i]+m+1);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)x^=a[j][i].first;
			if(x){
				puts("TAK");
				for(int j=1;j<=n;j++)printf("%d ",a[j][i].second);
				return 0;
			}
		}
	}
	puts("NIE");
}
```

---

## 作者：_Fontainebleau_ (赞：3)

## CF1151B Dima and a Bad XOR

### 分析

随机方法固然很强，但是如果题目改成输出字典序最小的答案，就得 GG 。

其实有一个很显然的做法:

- 先算 $val=a_{1,1}\oplus a_{2,1}\oplus a_{3,1} \oplus \cdots \oplus a_{n,1}$ 是否为 $0$ 。

- 若是，直接输出，结束。若否，因为是字典序最小，所以我们从最后一行从 $1$ 到 $m$ 枚举，若有符合条件就输出。否则都不符合条件，就意味着当前这一行所有元素都相等，那么 $c_k=1$（ $k$ 表示当前第几行），然后按照上述操作遍历第 $k-1$ 行直到 $val \not = 0$。

- 若最后依旧 $val=0$，那么就输出 `NIE` 。

容易发现上述算法是 $O(nm)$ 的，可以通过此题。

此时输出的是字典序最小的一组答案，自然一定是满足题意的答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int tc,n,m;
int p[502],a[502][502];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	int val=0;
	n=read(),m=read();
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		val^=a[i][1],p[i]=1;
	bool flag=true;
	if(!val)
	{
		flag=false; 
		for(int i=n;i>=1;i--)
		{
			for(int j=2;j<=m;j++)
				if(a[i][j]!=a[i][1])
				{
					flag=true;
					p[i]=j;
					break;
				}
			if(flag)	break;
		}	
	}
	if(flag)
	{
		puts("TAK");
		for(int i=1;i<=n;i++)
			printf("%d ",p[i]);
		puts(""); 
	}
	else	puts("NIE");
	return 0;
}

```

完结撒花~


---

## 作者：jdsb (赞：2)

## 题意
- 给定一个 $n\times m$ 的矩阵 $a$，判断是否存在一种方案，使得每行选出一个数后的异或和不为 $0$，要求输出方案。
- $1 \le n,m\le 500,1\le a_{i,j}<1024 $

## 分析
考虑值域只有 $2^{10}$ 的大小，我们可以直接直接记录每种状态能否出现，然后就可以考虑一个最朴素的 $\text{DP}$，设 $f(i,s)$ 表示做到第 $i$ 行，异或值为 $s$ 是否出现过，如果为 $1$ 则为出现过，否则没出现过，转移显然，$f(i,s \ \text{xor}\  t)|=f(i-1,s)\ (t$ 在第 $i$ 行出现过 $)$，在转移时顺便记录转移路径，然后倒序输出即可。时间复杂度为 $O(n\times2^{20})$，但有效状态有限，实测跑起来很快。

## 代码
```cpp
#include<bits/stdc++.h>
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1;c=getchar(); }
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=505,S=1024;
int n,m,a[N][N],f[N][S],v[N][S],pre[N][S];
inline void print(int k,int s){
	if(!k) return;
	print(k-1,s^pre[k][s]);
	printf("%d ",v[k][pre[k][s]]);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			v[i][read()]=j;
	for(int i=0;i<S;i++) f[1][i]=v[1][i],pre[1][i]=i;
	for(int i=2;i<=n;i++)
		for(int s=0;s<S;s++) if(f[i-1][s])
			for(int t=0;t<S;t++)
				if(v[i][t]) f[i][s^t]=1,pre[i][s^t]=t;
	for(int i=1;i<S;i++) if(f[n][i]){
		puts("TAK");
		print(n,i);
		return 0;
	}
	puts("NIE");
	return 0;
}
```


---

## 作者：litble (赞：2)

# 题目分析

把行分成两种——只有一种数字的行称为A类行，而至少有两种不同数字的行称为B类行。

对于A类行，显然，无论选这行的哪一列，最后选中的数字都是一样的，就提前将在A类行选数字得到的异或和处理出来，得到$X$。

若所有行都是A类行，且$X$等于0，则无解。

接下来考虑B类行，当前已经选好列的行，带来的异或和是$X$。若这一行第一种数为$X$，则选第二种数。若第二种数为$X$，则选第一种数。若都不为$X$，选哪个都行。这样可以保证最终的异或和一定不为0。

复杂度$O(nm)$（也就是读入复杂度）

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int n,m,now,ans;
int v1[505],id2[505],v2[505],kans[505];

int main()
{
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=n;++i) {
		scanf("%d",&v1[i]),v2[i]=-1;
		for(RI j=2;j<=m;++j) {
			int x;scanf("%d",&x);
			if(x!=v1[i]) v2[i]=x,id2[i]=j;
		}
		if(v2[i]==-1) now^=v1[i];
	}
	for(RI i=1;i<=n;++i) {
		if(v2[i]==-1) kans[i]=1;
		else {
			if((now^v1[i])==0) now^=v2[i],kans[i]=id2[i];
			else now^=v1[i],kans[i]=1;
		}
	}
	if(now==0) puts("NIE");
	else {
		puts("TAK");
		for(RI i=1;i<=n;++i) printf("%d ",kans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：djh123 (赞：1)

由于是异或操作，我们按位考虑。

如果我们让第$i$位是一，那么第$i$位是一的数要出现奇数次，那么我们可以把每一行的数位统计出现次数。

对于这个数位，对于所有行，我们要取奇数个值，就先取必须要取的行，若为奇数，则合法，再考虑可以取也可以不取的情况，如果有这种情况，也是合法的解，输出解直接记录一下就行。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int uint;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair
#define rep(x, a, b) for(int x = (a); x <= (b); ++ x)
#define per(x, a, b) for(int x = (a); x >= (b); -- x)
#define rop(x, a, b) for(int x = (a); x < (b); ++ x)
#define por(x, a, b) for(int x = (a); x > (b); -- x)
#define forE(x, a) for(int x = head[a]; x; x = nxt[x])

#ifdef DEBUG
#define debug(x) cerr << #x << ": " << x << '\n'
#else
#define debug(x)
#endif

void open(const char *s){
	#ifdef DEBUG
    char str[100];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
	sprintf(str,"%s.my",s);
	freopen(str,"w",stdout);
	#endif
}

const db eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int Minf = 0x7f7f7f7f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
const LL MINF = 0x7f7f7f7f7f7f7f7fll;

const int N = 1050;

int f[N][N];
int num[N][N];
int vis[N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	rep(i, 1, n) rep(j, 1, m) scanf("%d", &f[i][j]);
	if(m == 1) {
		int tmp = 0;
		rep(i, 1, n) tmp ^= f[i][1];
		if(tmp > 0) { puts("TAK"); rep(i, 1, n) printf("1 "); }
		else puts("NIE");
		return 0;
	}
	rep(i, 1, n) rep(j, 1, m) rep(k, 0, 31) if((f[i][j] >> k) & 1) ++ num[i][k];
	int anspos = -1;
	rep(i, 0, 31) {
		int cntf = 0, cnt0 = 0, cnt = 0;
		rep(j, 1, n) {
			if(num[j][i] == 0) ++ cnt0;
			else if(num[j][i] == m) ++ cntf;
			else ++ cnt;
		}
		if(cntf & 1) {
			rep(j, 1, n) if(num[j][i] == m) vis[j] = 1;
			anspos = i;
			break;
		}
		if(cnt) {
			anspos = i;
			rep(j, 1, n) if(num[j][i] == m) vis[j] = 1;
			rep(j, 1, n) if(num[j][i] != m && num[j][i] != 0) { vis[j] = 1; break; }
			break;
		}
	}
	if(anspos == -1) puts("NIE");
	else {
		puts("TAK");
		rep(i, 1, n) {
			if(vis[i]) {
				rep(j, 1, m) if((f[i][j] >> anspos) & 1) { printf("%d ", j); break; }
			}
			else {
				rep(j, 1, m) if(((f[i][j] >> anspos) & 1) == 0) { printf("%d ", j); break; }
			}
		}
	}
	return 0;
}

```

---

## 作者：彭天宇 (赞：0)

这题还是有一些难度的，不过要了解异或的性质也就好说了。
### 审题
题目要求我们每一行选出一个数，异或和“严格大于零”，其实就是大于零。因为全部是正数，所以只能是等于零或者大于零。
### 随机方法
一看，大于零的数（此处有1023个）远远比零的个数多（只有一个啊），那就随机选取，极大概率选出的数异或后非零。

因为数据总会有NIE的，那就多随机几次，怎么随机都不行的那就不行。（除非你脸真的太黑）
### 正确，有保证的方法
要想异或得到的数大于零，其实只要**二进制下任意一位数字不是0就行。**

那么我们每次都把矩阵扫描一遍，统计他的最后一位，并且除以二（向右位移）

对于每一行，我们都统计最后一位数字是1的数字的个数，如果为0（叫做A类）或m（叫做B类），那这一行相当于没得选择，默认选第一个。

如果只有上述两种，且B类有奇数个，就可以得出一个方案并输出。否则下一次循环（所有数字都变成0才能结束，不要冲动）。

当然还有这一行最后一位数字是1的个数大于0小于m的情况（叫做C类），这样就有自主选择的机会，一定有解了。其他所有行默认选第一个，这一行根据选择得到1的个数调配奇偶即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,m,a[N][N],b[N][N],tj[N];
bool check(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j])return true;
	return false;
}
void shuchu(int x){
	int cnt=0;
	int ans[N];
	for(int i=1;i<=n;i++)
		if(i!=x){
			if(b[i][1]&1)cnt++;
			ans[i]=1;
		}
	if(cnt&1){
		for(int i=1;i<=m;i++){
			if((b[x][i]&1)==0){
				ans[x]=i;
				break;
			}
		}
	}
	else{
		for(int i=1;i<=m;i++)
			if(b[x][i]&1){
				ans[x]=i;
				break;
			}
	}
	printf("TAK\n");
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			b[i][j]=a[i][j];
		}
	while(check()){
		for(int i=1;i<=n;i++)tj[i]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				tj[i]+=a[i][j]&1;
				a[i][j]>>=1;
			}
		}
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(tj[i]>0&&tj[i]<m){
				shuchu(i);
				return 0;
			}
			else if(tj[i]==m)cnt++;
		}
		if(cnt%2==1){
			printf("TAK\n");
			for(int i=1;i<=n;i++)printf("1 ");
			return 0;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)b[i][j]>>=1;
	}
	printf("NIE\n");
	return 0;
}

```

---

## 作者：Erusel (赞：0)

一道不错的思维题

我们不需要刻意地去考虑$xor$的性质

我们只要知道以下几条：

1.不同的数$xor$同一个数得出的结果是不同的

2.两个相同的数$xor$得0

3.两个不同的正整数$xor$为正整数

也就是说，当我们定好一个标准（比如每行的最后一项）只要保证有不同的项即可。

再次之前，要判断我们的标准是否已经符合

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define N 505

using namespace std;

int n,m;
int a[N][N];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int check(int r)
{
	int f=0;
	for(int j=1;j<=n;j++)if(a[r][j]!=a[r][1])f=-1;
	return (!f)?a[r][1]:f; 
}

int main()
{
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			rd(a[i][j]);
	int f=0;
	for(int i=1;i<=n;i++)f^=a[i][m];
	if(f)
	{
		printf("TAK\n");
		for(int i=1;i<=n;i++)printf("%d ",m);printf("\n");return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			if(a[i][j]!=a[i][m])
			{
				printf("TAK\n");
				for(int k=1;k<=n;k++)if(k==i)printf("%d ",j);else printf("%d ",m);
				printf("\n");
				return 0;
			}
	printf("NIE\n");
	
    return 0;
}
```

---

