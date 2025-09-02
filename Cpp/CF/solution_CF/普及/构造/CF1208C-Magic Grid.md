# Magic Grid

## 题目描述

我们定义“魔法网格”为一个满足以下两个条件的大小为 $n \times n$ 的整数方阵：

 $1.$ 从 $0$ 到 $n^2-1$ 的所有整数都在矩阵中出现过恰好一次。

 $2.$ 矩阵中的每行元素的按位异或和与每列元素的按位异或和都相等。

按位异或，即 $C/C++$ 中的 $\wedge$ 运算符或 $Pascal$ 中的 $xor$ 运算符。

现在给你一个 $n$ ，保证 $n$ 是 $4$ 的倍数。请构造一个“魔法网格”。

## 样例 #1

### 输入

```
4
```

### 输出

```
8 9 1 13
3 12 7 5
0 2 4 11
6 10 15 14```

## 样例 #2

### 输入

```
8
```

### 输出

```
19 55 11 39 32 36 4 52
51 7 35 31 12 48 28 20
43 23 59 15 0 8 16 44
3 47 27 63 24 40 60 56
34 38 6 54 17 53 9 37
14 50 30 22 49 5 33 29
2 10 18 46 41 21 57 13
26 42 62 58 1 45 25 61```

# 题解

## 作者：兮水XiShui丶 (赞：4)

题目中给出的是$4$的倍数,所以我们可以考虑将原来的矩形分成四块考虑(我也不知道为什么要这么考虑).那么我们想一下,如果不考虑从$0$到$n^2-1$的话,如果矩形长成下面这个亚子,那么它的异或值一定为0  

![qwq.png](https://i.loli.net/2019/08/26/DIm3KHdLesby6NJ.png)  

但是题目中要求每个数字都要被使用一次,怎么办呢?  

我们考虑一下,对于每一轮我们填入$0 \ 1 \ 2 \ 3$之后,如果我们每一次对下一个要填入的$0 \ 1 \ 2 \ 3$全部加上$4$,那么这些加上的$4$在异或之后显然都会变成对答案没有影响的$0$.这样,我们就可以愉快的构造了.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,cnt;
int mp[N][N];
int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n/2;i++)
		for(int j=1;j<=n/2;j++){
		mp[i][j]=cnt*4;
		mp[i][j+n/2]=cnt*4+1;
		mp[i+n/2][j]=cnt*4+2;
		mp[i+n/2][j+n/2]=cnt*4+3;
		cnt++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		  printf("%d ",mp[i][j]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：2)

提供一种极其简洁的做法。

## 思路

首先对于一个 $2 \times 4$ 的矩阵，可以构造出这样的一个方案：

$\text{0 1 0 1}$

$\text{2 3 2 3}$

$\text{0 1 0 1}$

$\text{2 3 2 3}$

此时每行异或之后都为 $0$。

但是每个数只让用一次，所以我们可以对每个 $2 \times 2$ 的矩阵加上 $4$。这样，它们其他的位置是相同的，异或之后也为 $0$，对结果没有影响。即：

```
0  1  4  5
2  3  6  7
8  9  12 13
10 11 14 15
```

然后我们发现这是容易证明的：前两个数和后两个数的异或值相同，异或之后就为 $0$。因此每行每列异或都为 $0$。

这个代码也异常好写 qwq

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1005][1005];
int main()
{
	int n,cnt=-1; cin>>n;
	for(int i=1;i<=n/2;i++)
		for(int j=1;j<=n/2;j++)
		{
			a[i*2-1][j*2-1]=++cnt;
			a[i*2-1][j*2]=++cnt;
			a[i*2][j*2-1]=++cnt;
			a[i*2][j*2]=++cnt;
		}
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=n;j++)
			printf("%d ",a[i][j]);
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：1)

### 思路

题目有 $n$ 是 $4$ 的倍数，所以整个方阵应该可以被分成若干个 $4\times 4$ 的矩阵，每个矩阵每行每列异或和相同。

所以先来看 $n=4$ 的情况：

先二进制拆位：

```example
0000 0001 0010 0011
0100 0101 0110 0111
1000 1001 1010 1011
1100 1101 1110 1111

0 1 2 3
4 5 6 7 
8 9 10 11
12 13 14 15
```

发现其实就这样每行每列的异或和就是 $0$ 了。

然后 $n>4$ 的呢？

对于 $n>4$，显然一共有 $n^2$ 个数，也就是说其实每个矩阵只是对第一个矩阵的每一个元素加上若干个 $16$，不会影响后四位，然后异或就全抵消了，能确保每行每列异或和为 $0$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
int ans[maxn][maxn];
int n;
int main(){
	scanf("%d",&n);
	int nw=0;
	for(int i=0;i<n;i+=4){
		for(int j=0;j<n;j+=4){
			for(int k=1;k<=4;k++){
				for(int l=1;l<=4;l++){
					ans[i+k][j+l]=nw++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",ans[i][j]);
		}
		printf("\n");
	}
}
```

---

## 作者：Coding__QAQ (赞：1)

（管理员大大抱歉，之前这篇题解交错了）

显然，此题考查我们的构造能力。

做法：假设n=2时（虽然n得是4的倍数）
矩阵应为

0 1

2 3

将其转换为2进制
，应为

00 01

10 11

易发现若两个数转化后只有一位数不同（如0和1，2和3）他们异或后的值为1，我们如果把偶数对这样的数放在一排（如0,1，2,3）它们的异或和必定为0。

所以我们只要把转化后满足仅最后一位不同的两个数放在一起（题目中的n满足是4的次幂）。例如当n=4时，构造的矩阵应为

0 1 2 3

4 5 6 7

8 9 10 11

12 13 14 15

发现规律了吗？这样做理论上是每行异或和为0的。

其实只要两个for循环（或者一个）把所有数一次输一遍就行了
！

但是，CF上数据为1000（这是它的最大范围……）的时候会蜜汁WA，本人在本机上亲测每行异或和都为0……emmm,暂时就当一种想法分享给大家吧

---

## 作者：_smart_stupid_ (赞：0)

题面简述：给定 $N$ 为 $4$ 的倍数，求一个矩阵使得矩阵每一行分别异或的结果与每列分别异或的结果相等。

我们看到 $N$ 为 $4$ 的倍数，一定暗藏玄机，所以每 $16$ 个为一组，为 $4\times 4$ 的正方形。分 $\frac {N^2}{16}$ 组，每组（用二进制表示）后四位不相等，前面几位都相等。

先让每一排的异或和相等。相邻 $4$ 个数（$4k,4k+1,4k+2,4k+3$）异或和一定为 $0$，可以放到同一排。考虑每一列的异或和。

发现这样分配后，每一列的元素倒数三四位分别为`00,01,10,11`，所以只用考虑后二位。由于每一排刚好可以贡献一个后二位为 `00,01,10,11` 的数，所以让每列分别得到一个后二位为 `00,01,10,11` 的数即可满足条件。

给出一个看起来很美观的构造：

```text
第一组，后面几组以此类推。
0  1  2  3
5  6  7  4
10 11 8  9
15 12 13 14
```

每一组行列异或和都为 $0$，答案一定成立。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int mat[1010][1010];
int n;
void out() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << mat[i][j] << ' ';
		cout << '\n';
	}
}
bool solve() {
	int idx = 0;
	for (int i = 0; i < n; i += 4) {
		for (int j = 0; j < n; j += 4) {
			int temp = 0;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					mat[i + k][j + l] = idx + k * 4 + (l + temp) % 4;
				}
				temp++;
			}
			idx += 16;
		}
	}
	return 1;
}
int main() {
	cin >> n;
	solve();
	out();
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

首先，我们天真地发现对于 $n=4$ 以下矩阵满足条件：
```
0 1 2 3
4 5 6 7
8 9 10 11
12 13 14 15
```
换成二进制就是：
```
0000 0001 0010 0011
0100 0101 0110 0111
1000 1001 1010 1011
1100 1101 1110 1111
```
于是，天真的我认为只要输出 $0$ 到 $n^2-1$ 即可。
![](https://cdn.luogu.com.cn/upload/image_hosting/ajwu7ctb.png)
**Too young too naive!**  
不过这帮助了我们的思考，对于每个 $4 \times 4$ 的子矩阵是否可以都如此排布？观察到原矩阵异或和为 $0$，所以如此构造的矩形满足异或和的条件。  
不过由于一个数只能使用一次，我们发现处理完一个子矩阵后编号增加 $16$，而 $16$ 在二进制下有 $5$ 位，所以不影响后面几位，下面是只加一次的示例。
```
10000 10001 10010 10011
10100 10101 10110 10111
11000 11001 11010 11011
11100 11101 11110 11111
```
可以发现不管如何第 $5$ 位及以上在子矩阵中永远相同，异或结果为 $0$，逐个矩阵构造即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,idx,ans[1010][1010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i+=4)
		for(int j=1;j<=n;j+=4)
			for(int st=i;st<=i+3;st++)
				for(int ed=j;ed<=j+3;ed++)
					ans[st][ed]=idx++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<' ';
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1208C)

## 题目分析

对于这道题，我们发现 对于一个 $4 \times 4$ 的矩阵，如果这样构造：

$$0,1,0,1$$

$$2,3,2,3$$

$$0,1,0,1$$

$$2,3,2,3$$

可以做到异或和都为 $0$ 。

由于每个数都只能用一次，所以我们对每一个 $2 \times 2$ 的矩阵加上 $4$ ，它们直接的异或和就会变为 $0$ ，对答案没有影响。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ass assign
#define fst first
#define sec second
#define lb lower_bound
#define ub upper_bound
using namespace std;
const int maxn=1002;
int n,a[maxn][maxn];
int tot=-1;
void init(){cin>>n;}
void duel(){
	for(register int i=1;i<=n/2;++i){
		for(register int j=1;j<=n/2;++j){
			a[i*2-1][j*2-1]=++tot;
			a[i*2-1][j*2]=++tot;
			a[i*2][j*2-1]=++tot;
			a[i*2][j*2]=++tot;
		}
	}
}
void print(){
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main(){
    init();
    duel();
    print();
}
```

---

## 作者：foreverlasting (赞：0)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### C Magic Grid

题意：给一个$n$，需要构造一个$n*n$的矩阵，包含$0,...,n^2-1$，且每行每列的异或和相等。$4\leq n\leq 4000,4|n$。

做法：每$4*4$的为一组，显然可以构造出都为$0$的情况，复杂度$O(n^2)$。

code:
```cpp
//2019.8.24 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
//inline int read() {
//    res s=0,ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
inline int read() {
    res s=0,ch=gc(),w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s*w;
}
inline LL Read() {
    RG LL s=0;
    res ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
//const int N=1e6+10;
namespace MAIN{
    const int N=2005;
    int M[N][N],n,c;
    void solve(res l,res r,res ql,res qr){for(res i=l;i<=r;i++)for(res j=ql;j<=qr;j++)M[i][j]=c++;}
    inline void MAIN(){
        scanf("%d",&n);
        for(res i=1;i<=n>>2;i++)for(res j=1;j<=n>>2;j++)solve((i-1)*4+1,i*4,(j-1)*4+1,j*4);
        for(res i=1;i<=n;i++){
            for(res j=1;j<=n;j++)
                printf("%d ",M[i][j]);
            puts("");
        }
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

