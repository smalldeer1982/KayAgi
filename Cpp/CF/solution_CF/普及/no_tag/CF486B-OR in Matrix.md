# OR in Matrix

## 题目描述

Let's define logical $ OR $ as an operation on two logical values (i. e. values that belong to the set $ {0,1} $ ) that is equal to $ 1 $ if either or both of the logical values is set to $ 1 $ , otherwise it is $ 0 $ . We can define logical $ OR $ of three or more logical values in the same manner:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/406211f13f2a7c95dc14e24b4ae950d102f218cc.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/83308fae1dcded561005b623c7c1ed2fdfdfe04f.png) is equal to $ 1 $ if some $ a_{i}=1 $ , otherwise it is equal to $ 0 $ .

Nam has a matrix $ A $ consisting of $ m $ rows and $ n $ columns. The rows are numbered from $ 1 $ to $ m $ , columns are numbered from $ 1 $ to $ n $ . Element at row $ i $ ( $ 1<=i<=m $ ) and column $ j $ ( $ 1<=j<=n $ ) is denoted as $ A_{ij} $ . All elements of $ A $ are either 0 or 1. From matrix $ A $ , Nam creates another matrix $ B $ of the same size using formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/157692e348a7a47f249e1d0e7ed60b12dc8cb619.png).

( $ B_{ij} $ is $ OR $ of all elements in row $ i $ and column $ j $ of matrix $ A $ )

Nam gives you matrix $ B $ and challenges you to guess matrix $ A $ . Although Nam is smart, he could probably make a mistake while calculating matrix $ B $ , since size of $ A $ can be large.

## 样例 #1

### 输入

```
2 2
1 0
0 0
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 3
1 1 1
1 1 1
```

### 输出

```
YES
1 1 1
1 1 1
```

## 样例 #3

### 输入

```
2 3
0 1 0
1 1 1
```

### 输出

```
YES
0 0 0
0 1 0
```

# 题解

## 作者：珅肐 (赞：5)

提供简洁的代码

首先若$B[i][j]$是$0$，则$A$矩阵的第$i$行和第$j$列一定都是$0$。

按照这一点模拟即可。

### 详见代码：

```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
bool b[107][107],vh[107],vl[107],ah[107],al[107];
//b为B矩阵，vh[i]=1表示A矩阵第i行为0，vl[j]=1表示A矩阵第j列为0，ah[i]表示A矩阵第i行的或和，al[j]表示A矩阵第j列的或和
int main(){
	int n=read(),m=read();
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){//读入
		b[i][j]=read();
        if(!b[i][j])vh[i]=vl[j]=1;//如上述，i行j列都为0
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)ah[i]|=(!vl[j]&!vh[i]),al[j]|=(!vh[i]&!vl[j]);
    //!vh[i]&!vl[j]表示a[i][j]，因为只有第i行和第j列都不为0，a[i][j]才不为0
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(b[i][j]!=(ah[i]|al[j])){puts("NO");return 0;}//如果由A推出的B与输入的不相符，不合法退出。
    puts("YES");//否则合法
    for(int i=1;i<=n;++i,puts(""))for(int j=1;j<=m;++j)printf("%d ",((!vh[i])&(!vl[j])));//输出结果
	return 0;//好习惯
}
```


---

## 作者：asasas (赞：2)

这题乍一看似乎很难，但仔细分析一下，不算太难。

首先我们把答案数组($ans)$全部赋值为1。
如果这个位置为0，那么这一行，这一列所有的数一定都是0（否则$or$一下一定会为1）。

而当我们找到这个位置为1的时候，我们在这个数所在的行和列扫一遍，如果这些数全部都为0，那就说明无解，退出循环，输出NO，然后结束程序。否则输出YES，并把答案数组输出。（这种做法能保证有最多的$1$，代码也不长，思路也不是很难）

代码：
```cpp
#include <stdio.h>
int p[105][105],ans[105][105];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for (register int i=1;i<=n;i++){
		for (register int j=1;j<=m;j++){
			scanf("%d",&p[i][j]);
			ans[i][j]=1;//先全部赋值为1
		}
	}
	int qwq=0,ok=0;
	for (register int i=1;i<=n;i++){
		for (register int j=1;j<=m;j++){
			if (p[i][j]==0){//为0的情况
				for (register int k=1;k<=n;k++) ans[k][j]=0;
				for (register int k=1;k<=m;k++) ans[i][k]=0;
				qwq++;//这一行，一列全部赋值为0
			}
		}
	}
	for (register int i=1;i<=n;i++){
		for (register int j=1;j<=m;j++){
			if (p[i][j]==1){
				bool qo=0;
				for (register int k=1;k<=m;k++){
				    if (ans[i][k]) qo=1;
				}
				for (register int k=1;k<=n;k++){
				    if (ans[k][j]) qo=1;
				}
				if (!qo){//如果一行一列中一个1都没有，就说明无解
					printf("NO");
					return 0;
				}
			}
		}
	}
	qwq=0;
puts("YES");//否则说明有解
	for (register int i=1;i<=n;i++){
		for (register int j=1;j<=m;j++){
			printf("%d ",ans[i][j]);
		}
         puts("");
	 }
}
```



---

## 作者：muyang_233 (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF486B)  
  
   
  我们注意到，由于 **或** 运算的运算法则 ， 当 $B_{i}{_j} == 0$ 时，必须满足 $A{_i}_{1..m}$ 和 $A_{1..n}{_j}$ 全部为 $0$ 。  
  而在这种情况下，我们只要保证 $B_i{_j} == 1$ 的情况满足就可以了，那么为了尽可能的满足更多的情况，不妨把未填写的 $A_i{_j}$ 全部设为 $1$ 。  
  之后判断根据构造出的矩阵 $A$ 合成出的矩阵 $B'$ 是否与矩阵 $B$ 相等就可以了。  
  代码：
  ```cpp
  #include <cstdio>
using namespace std;
int n,m;
bool ok=true;
int a[105][105];
int b[105][105];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			a[i][j]=1;
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			scanf("%d",&b[i][j]);
			if (!b[i][j]){
				for (int k=1;k<=n;k++){
					a[k][j]=0;
				}
				for (int k=1;k<=m;k++){
					a[i][k]=0;
				} 
			}
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (b[i][j]){
				bool now=false;
				for (int k=1;k<=n;k++){
					if (a[k][j]) {
						now=true;
						break;
					}
				}
				for (int k=1;k<=m;k++){
					if (a[i][k]) {
						now=true;
						break;
					}
				}
				ok&=now;
				if (!ok){
					i=n;
					break;
				}
			}
		}
	}
	if (!ok){
		printf("NO");
	}
	else{
		puts("YES");
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				printf("%d ",a[i][j]);
			}
			puts("");
		}
	}
	return 0;
}

  ```
  ~~这里有AC代码哦，但我相信你不会抄题解的！~~

---

## 作者：伟大的王夫子 (赞：1)

此题难度也许配不上蓝

因为只是一个比较一般的模拟+贪心

首先$x \,\, or\,\, y$当$x$或$y$中有一个为$1$时，值便为$1$,要为$0$必须全部都为$0$

因为$B_{i,j} = (\sum_{k=1}^nA_{i, k} ) \,\,or \,\,(\sum_{k =1}^m A_{k, j})$

其中$\sum$先不表示求和，表示或运算

若$B_{i,j}=0$

那么$\forall k \in [1,n]\,\, A_{i, k} = 0$并且$\forall k \in [1,m] \,\, A_{k, j} = 0$

那样便能保证$B_{i,j}=0$

那么其余的$A_{i,j}$我们随便赋值，最好赋$1$,这样便有利于那些为$1$的$B_{i,j}$并对于值为$0$的也不影响

最后还得验证一下，因为有可能不存在

code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, a[110][110];
int b[110][110];
int main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			cin >> b[i][j], a[i][j] = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j) {
			if (!b[i][j]) {
				for (register int k = 1; k <= m; ++k) a[i][k] = 0;
				for (register int k = 1; k <= n; ++k) a[k][j] = 0;
			}
		}
//	for (register int i = 1; i <= n; ++i) {
//		for (register int j = 1; j <= m; ++j)
//			cout << a[i][j] << ' ';
//		puts("");
//	}
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j) {
			int val = 0;
			for (register int k = 1; k <= m; ++k) val |= a[i][k];
			for (register int k = 1; k <= n; ++k) val |= a[k][j];
			if (val != b[i][j]) {
				puts("NO");
				return 0;
			}
		}
	puts("YES");
	for (register int i = 1; i <= n; ++i) {
		for (register int j = 1; j <= m; ++j)
			cout << a[i][j] << ' ';
		puts("");
	}
}
```

---

## 作者：杳冥 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF486B)

首先要知道 **或运算**的运算方式

或运算：只有**全部的**操作数为$false$ 结果才为$false$；

所以 若给定的$B$矩阵中$B[i][j]$为0，则$A$矩阵中的第$i$行与第$j$列都为0。

得出了这个结论，剩下的就只是代码实现的问题啦。

细节见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[110][110],b[110][110];
bool flag=true;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){  //输入矩阵 
		for(int j=1;j<=m;++j){
			scanf("%d",&a[i][j]); 
		}
	}
	for(int i=1;i<=n;++i){    // 先将所求的矩阵全部初始化为1 
		for(int j=1;j<=m;++j){
			b[i][j]=1;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!a[i][j]){    // 如果给定矩阵中有0 则将所求矩阵对应的行与列全赋值为0 
				for(int z=1;z<=m;++z){
					b[i][z]=0;
				}
				for(int z=1;z<=n;++z){
					b[z][j]=0;
				}
			}
		} 
	}
	for(int i=1;i<=n;++i){   // 再验证一次 
		for(int j=1;j<=m;++j){
			if(a[i][j]){
				bool zkw=false; 
				for(int z=1;z<=m;++z){
					if(b[i][z]) zkw=true;
				}
				if(!zkw){
					for(int z=1;z<=n;++z){
					    if(b[z][j]) zkw=true;
				    }
				}
				if(!zkw){   // 若果验证失败 则不存在份符合要求的矩阵 
					printf("NO");
					return 0;
				}
			}
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：yu__xuan (赞：1)

%%%[珅肐](https://www.luogu.org/user/56653)

### 题目

[CF486B OR in Matrix](https://www.luogu.org/problem/CF486B)

### 思路
前置芝士 
* 0 or 1 = 1 
* 0 or 0 = 0
* 1 or 1 = 1

由
>B [i][j]是由 A 矩阵的第 i 行的所有元素和第 j 列的所有元素 或运算（or）得到。

可知
* 如果$\texttt{B[i][j]=0}$，那么 $A$ 的第 $i$ 行与第 $j$ 列都为零。

* 如果$\texttt{B[i][j]=1}$，那么 $A$ 的第 $i$ 行与第 $j$ 列的所有元素中只要有一个为 $1$ 即可。

我们先将答案矩阵都格式化为 $1$ 。
* 如果$\texttt{B[i][j]=0}$就将答案数组的第 $i$ 行与第 $j$ 列全都赋值为 $0$。这是优先处理的

* 将上面的操作做完后我们再扫一遍 $B$ 如果$\texttt{B[i][j]=1}$ 我们就去看答案数组的第 $i$ 行与第 $j$ 列是否都是 $1$即可

### $Code$
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

inline void write(int x) {
	if(x<0) putchar('-'),write(-x);
	else {
		if(x/10) write(x/10);
		putchar(x%10+'0');
	}
}

int n,m,mat1[101][101],mat2[101][101];

void work(int x,int y) {
	for(int i=1;i<=n;++i) mat2[i][y]=0;
	for(int i=1;i<=m;++i) mat2[x][i]=0;
}

int main() {
	for(int i=1;i<=100;++i) {
		for(int j=1;j<=100;++j) {
			mat2[i][j]=1;
		}
	}
	read(n),read(m);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			read(mat1[i][j]);
			if(!mat1[i][j]) work(i,j);
		}
	}
	bool f=1;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(mat1[i][j]) {
				int sum=0;
				for(int k=1;k<=n;++k) {
					if(!mat2[k][j]) ++sum;
				}
				for(int k=1;k<=m;++k) {
					if(!mat2[i][k]) ++sum;
				}
				if(sum==m+n) {f=0;break;}
			}
		}
	}
	if(!f) {puts("NO");return 0;}
	puts("YES");
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			write(mat2[i][j]);
			printf(" ");
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Elma_ (赞：0)

如果 $B_{i,j}$ 是 $0$，那么 $A$ 的第 $i$ 行和第 $j$ 列一定都是 $0$，对于这一部分我们先处理完。

显然 $A$ 中剩下的元素都赋值为 $1$ 一定是最优的，因此只需要判断在这个情况下有没有解即可。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define mp make_pair
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e2 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int n, m, a[maxn][maxn], b[maxn][maxn];

int main(void) {
	n = read(), m = read();
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			a[i][j] = read(), b[i][j] = 1;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (a[i][j] == 0) {
				for (int k = 1;k <= m;k++) b[i][k] = 0;
				for (int k = 1;k <= n;k++) b[k][j] = 0;
			}
		}
	}
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			if (a[i][j] == 1) {
				int flag = 0;
				for (int k = 1;k <= m;k++) if (b[i][k] == 1) flag = 1;
				for (int k = 1;k <= n;k++) if (b[k][j] == 1) flag = 1;
				if (!flag) return puts("NO"), 0;
			}
		}
	}
	puts("YES");
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			printf("%d%c", b[i][j], " \n"[j == m]);
	return 0; 
}
```


---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF486B)

[CF's link](http://codeforces.com/problemset/problem/486/B)

#### 题意：

矩阵 $B$ 的 $B_{i,j}$ 是由矩阵 $A$ 的第 $i$ 行的所有元素和第 $j$ 列的所有元素 $OR$ 得到

给定矩阵 $B$，求是否存在一个矩阵 $A$。

#### Solution：

如果矩阵 $B_{i,j}$ 为 $0$，那么矩阵 $A$ 整行整列都是 $0$。

如果矩阵 $B_{i,j}$ 为 $1$，那么如果矩阵 $A$ 整行整列都是 $0$，即为不合理的情况。

注意最好先处理为 $0$ 的状况，再处理为 $1$ 的状况。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-15 20:16:48 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-15 20:30:30
 */
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=105;
int n,m,a[N][N],b[N][N];
void work(int x,int y){
	FOR(i,1,m) b[x][i]=0;
	FOR(i,1,n) b[i][y]=0;
}
bool pd(int x,int y){
	bool flag=0;
	FOR(i,1,m) if(b[x][i]==1) flag=1;
	FOR(i,1,n) if(b[i][y]==1) flag=1;
	if(!flag) return 0;
	return 1;
}
int main(){
	n=read();m=read();
	FOR(i,1,n) FOR(j,1,m) a[i][j]=read(),b[i][j]=1;
	FOR(i,1,n) FOR(j,1,m) if(a[i][j]==0) work(i,j);
	FOR(i,1,n){
		FOR(j,1,m){
			if(a[i][j]==1){
				if(!pd(i,j)){
					puts("NO");
					return 0;
				}
			}
		}
	}
	puts("YES");
	FOR(i,1,n){
		FOR(j,1,m){
			write(b[i][j]);
			putchar(' ');
		}
		puts("");
	}
	return 0;
}
```



---

## 作者：KEBrantily (赞：0)

## 扯在前面
本人找规律找了很长时间，然后发现找到规律之后其实是lj题，于是五分钟敲完代码，然后WA了两发

~~看到题解区还有我的一席之地~~特来分享

排版真的很难管理大大给过吧球球了

------------


# 正文
## 题意：

A, B 都是 n*m 的 01 矩阵，已知 B 矩阵是由A矩阵以一种规则生成

Bij 是由 A 矩阵的第 i 行行的所有元素和第 j 列列的所有元素进行 或运算 得到

给定B矩阵，求是否存在一个矩阵A能被合理生成；

不懂的同学可以先了解一下或运算

### [传送门](https://blog.csdn.net/qq_39416311/article/details/102762635)

------------

## 分析：
因为我们已知以下关系且每次参与运算的是一整行和一整列的所有数
```
0|0=0；  0|1=1；  1|0=1；  1|1=1；
```
**所以**
- 当某个位置只要出现一个零，那么他对应矩阵所在的整行或整列如果是零都会是零，因为只要出现一个一，他就不可能是零；
- 这样的话当然我们也会知道知道，当某行或某列出现一个一时，那他的整行整列必定会出现至少一个一，因为只要有一参与或运算就会是一


------------

## 做法

知道这两个结论之后我们就可以用简单的方法做题了

根本不用或运算符|，而是另一种方法：
1. 先把A矩阵赋值为只有1的矩阵，然后填零
1. 当在B矩阵中找到某个位置是0时，就把A矩阵对应的整行整列都赋值成0
1. 当在B矩阵中找到某个位置是1时，就查看一下A矩阵对应的行与列是否有1，若没有则为NO
1. 剩下的输出YES
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring> 
#include<cmath>
#include<algorithm>
#define maxn 500
using namespace std;
int n,m,b[maxn][maxn],a[maxn][maxn];
int cnt;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>b[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(b[i][j]==0){
                for(int k=1;k<=n;k++)
                    a[k][j]=0;
                for(int k=1;k<=m;k++)
                    a[i][k]=0;
            } 
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(b[i][j]==1){
                for(int k=1;k<=n;k++)
                    if(a[k][j]==1){
                        cnt++;
                        break;
                    }
                for(int k=1;k<=m;k++)
                    if(a[i][k]==1){
                        cnt++;
                        break;
                    }
                if(cnt==0){
                    cout<<"NO";
                    return 0;
                }
            }
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
} 
```
制作不易，请各位批评指正

---

## 作者：Suzt_ilymtics (赞：0)

# “日拱一卒，功不唐捐”

## [-->题目传送门飘过~~<--](https://www.luogu.com.cn/problem/CF486B)

## [-->博客食用更佳哦~<--](https://www.luogu.com.cn/blog/Silymtics/cf486b-or-in-matrix-ti-xie)

------------

## Solution
题意让我们通过矩阵B求矩阵A，因为B是由A进行或运算（[何为或运算？](https://www.cnblogs.com/Silymtics/p/13765258.html)）得到的，根据或运算法则：
### 参加运算的两个对象只要有一个为1，其值为1

那么如果在B数组当接收到一个0时，就证明在A数组中对应行和对应列都应为0
```cpp
void paint(int x,int y){//x和y为接收到0的位置
	for(int i=1;i<=n;++i) stt[i][y] = 0;
	for(int i=1;i<=m;++i) stt[x][i] = 0;
}
```
先把关于0的处理完后在用check函数判断1的是否和法
只要出现1就check一下，

### 注意合法条件：在对应行或对应列出现一个1即可
```cpp
bool check(int x,int y){
	int flag = 0;
	for(int i=1;i<=n;++i) if(stt[i][y]) {flag++;break;}
	for(int j=1;j<=m;++j) if(stt[x][j]) {flag++;break;}
	if(flag) return true;
	return false;
}
```
最后根据判断情况直接输出即可

本人原来在代码中开的是end[]数组结果CE
![](https://cdn.luogu.com.cn/upload/image_hosting/ykwrr3cg.png)
所以大家少开end[]数组

------------


## 附上AC代码：
```cpp
/*
Work by:Suzt_ilymtics
*/
#include<iostream>
#include<cstdio>
using namespace std;
int n, m;
bool ed[102][102];
bool stt[102][102];

void paint(int x,int y){
	for(int i=1;i<=n;++i) stt[i][y] = 0;
	for(int i=1;i<=m;++i) stt[x][i] = 0;
}

bool check(int x,int y){
	int flag = 0;
	for(int i=1;i<=n;++i) if(stt[i][y]) {flag++;break;}
	for(int j=1;j<=m;++j) if(stt[x][j]) {flag++;break;}
	if(flag) return true;
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			stt[i][j] = 1;

	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&ed[i][j]);
			if(!ed[i][j]){paint(i,j);}
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(ed[i][j]) 	
				if(!check(i,j)){
					printf("NO");
					return 0;
				}
	printf("YES\n");
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) printf("%d ",stt[i][j]);
		printf("\n");
	}
	return 0;
}
```


------------


~~华丽结束~~

#### 如果您在阅读过程中对本题解有疑问，欢迎私信或者评论区指出


---

## 作者：yuzhechuan (赞：0)

一道有趣的思维题

---

由于or的性质可知只要a[i][j]为1那么b中第i行，第j列将都变成1

相反的，如果b[i][j]是0那么a中第i行，第j列都必须是0

根据第二个性质我们可以构造出a矩阵

但b能否由a反向得到呢？

由于or的唯一性，模拟匹配即可，注意代码效率

---

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[105][105],b[105][105],h[105],z[105],ah[105],az[105];
signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            a[i][j]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&b[i][j]);
            if(b[i][j]) continue; //是1就不管
            if(!z[j])for(int k=1;k<=n;k++) a[k][j]=0; //z是"纵"，下同
            if(!h[i])for(int k=1;k<=m;k++) a[i][k]=0; //h是"横"，下同
            h[i]=z[j]=1; //这一行，这一列都已经清过零了
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            ah[i]|=a[i][j]; //a中第i行是否有1
            az[j]|=a[i][j]; //a中第j列是否有1
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) if(b[i][j]^(ah[i]|az[j])){ //与b不匹配
            puts("NO");
            return 0;
        }
    puts("YES");
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=m;j++)
            printf("%d ",a[i][j]);
}

```

---

## 作者：da32s1da (赞：0)

首先若$B[i][j]$是$0$，则$A[i][...],B[...][j]$一定是$0$。

那我们可以设$A[i][j]$全是$1$，然后根据读入的$B$矩阵调整。

调整过后，我们推一遍$B$矩阵，看是否与读入的相同。
```
#include<cstdio>
const int N=105;
int n,m,a[N][N],b[N][N],c[N][N];
int x,bj,vis1[N],vis2[N],d1[N],d2[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&x);
		if(x==0){
			if(!vis1[i])
				for(int k=1;k<=m;k++)a[i][k]=0;
			if(!vis2[j])
				for(int k=1;k<=n;k++)a[k][j]=0;
            //调整A矩阵
			vis1[i]=vis2[j]=1;
		}else b[i][j]=1;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	d1[i]|=a[i][j],d2[j]|=a[i][j];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(b[i][j]!=(d1[i]|d2[j])){
		puts("NO");return 0;
        //自己求的与读入不符
	}
	puts("YES");
	for(int i=1;i<=n;i++,putchar('\n'))
	for(int j=1;j<=m;j++)
	printf("%d ",a[i][j]);
}
```

---

