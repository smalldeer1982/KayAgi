# Errich-Tac-Toe (Hard Version)

## 题目描述

The only difference between the easy and hard versions is that tokens of type O do not appear in the input of the easy version.

Errichto gave Monogon the following challenge in order to intimidate him from taking his top contributor spot on Codeforces.

In a Tic-Tac-Toe grid, there are $ n $ rows and $ n $ columns. Each cell of the grid is either empty or contains a token. There are two types of tokens: X and O. If there exist three tokens of the same type consecutive in a row or column, it is a winning configuration. Otherwise, it is a draw configuration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450C2/39afc6239351b009b5f556b0fc6f685f7842a873.png) The patterns in the first row are winning configurations. The patterns in the second row are draw configurations. In an operation, you can change an X to an O, or an O to an X. Let $ k $ denote the total number of tokens in the grid. Your task is to make the grid a draw in at most $ \lfloor \frac{k}{3}\rfloor $ (rounding down) operations.

You are not required to minimize the number of operations.

## 说明/提示

In the first test case, there are initially three 'O' consecutive in the second row and the second column. By changing the middle token to 'X' we make the grid a draw, and we only changed $ 1\le \lfloor 5/3\rfloor $ token.

In the second test case, the final grid is a draw. We only changed $ 8\le \lfloor 32/3\rfloor $ tokens.

In the third test case, the final grid is a draw. We only changed $ 7\le \lfloor 21/3\rfloor $ tokens.

## 样例 #1

### 输入

```
3
3
.O.
OOO
.O.
6
XXXOOO
XXXOOO
XX..OO
OO..XX
OOOXXX
OOOXXX
5
.OOO.
OXXXO
OXXXO
OXXXO
.OOO.```

### 输出

```
.O.
OXO
.O.
OXXOOX
XOXOXO
XX..OO
OO..XX
OXOXOX
XOOXXO
.OXO.
OOXXO
XXOXX
OXXOO
.OXO.```

# 题解

## 作者：Resurgammm (赞：14)

$update:$ 增加了 $\text{Reference}$

> 棋盘上有一些棋子，可以把 `X` 变成 `O`，也可以把 `O` 变成 `X`，从而使棋盘上横竖没有连续三个相同的棋子。

发现操作次数至多 $\lfloor\frac{k}{3}\rfloor$ 满足 **抽屉原理** 的格式，那么应用这个原理，问题就转化为了构造三个方案，使每个方案都为平局且操作总数为 $k$。

将所有格子分成三类，第 $i\ (i\in[0,3))$ 类包含所有的格子 $(x+y)\bmod 3=i$。

不难发现只要一类格子全是 `X`，另一类格子全是 `O` 就合法。

那么有三种构造方案：

* 把第 $0$ 类格子上的 `X` 全改为 `O`，第 $1$ 类格子上的 `O` 全改为 `X`。

* 把第 $1$ 类格子上的 `X` 全改为 `O`，第 $2$ 类格子上的 `O` 全改为 `X`。

* 把第 $2$ 类格子上的 `X` 全改为 `O`，第 $0$ 类格子上的 `O` 全改为 `X`。

显然这三种都能使局面变成平局，且操作总数为 $k$，所以操作次数最少的方案一定 $\leq \lfloor\frac{k}{3}\rfloor$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))

	const int maxn=305;
	
	int T,n,k,cnt1,cnt2,cnt3;
	int uid[maxn][maxn];
	char mp[maxn][maxn],ans1[maxn][maxn],ans2[maxn][maxn],ans3[maxn][maxn];
	inline void print(char s[maxn][maxn]){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) printf("%c",s[i][j]);
			puts("");
		}
	}
	inline void init(){
		fill(mp,'\0'),fill(ans1,'\0'),fill(ans2,'\0'),fill(ans3,'\0');
		k=cnt1=cnt2=cnt3=0;
	}
	
	inline int main(){
		T=read();
		while(T--){
			n=read();
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					char ch=getchar();
					while(ch!='O' && ch!='X' && ch!='.') ch=getchar();
					if(ch!='.') k++;
					mp[i][j]=ch;
					uid[i][j]=(i+j)%3;
				}
			copy(ans1,mp),copy(ans2,mp),copy(ans3,mp);
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(uid[i][j]==0 && mp[i][j]=='O') ans1[i][j]='X',cnt1++;
					if(uid[i][j]==1 && mp[i][j]=='X') ans1[i][j]='O',cnt1++;
				}
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(uid[i][j]==1 && mp[i][j]=='O') ans2[i][j]='X',cnt2++;
					if(uid[i][j]==2 && mp[i][j]=='X') ans2[i][j]='O',cnt2++;
				}
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(uid[i][j]==2 && mp[i][j]=='O') ans3[i][j]='X',cnt3++;
					if(uid[i][j]==0 && mp[i][j]=='X') ans3[i][j]='O',cnt3++;
				}
			if(cnt1<=k/3) print(ans1);
			else if(cnt2<=k/3) print(ans2);
			else if(cnt3<=k/3) print(ans3);
			init();			
		}
		return 0;
	}
}
signed main(){return CL::main();}
```

 ## $\text{Reference}$
 
 $2021$ 国家集训队论文 《信息学竞赛中构造题的常用解题方法》—蒋凌宇

---

## 作者：AsunderSquall (赞：10)

# 题意  
你有一个棋盘，上面有一些棋子。你需要使一些 X 变成 O，使一些 O 变成 X，从而使棋盘上没有连续的 $3$ 颗相同的棋子（只考虑横竖，不考虑斜线）。  
你改变的棋子数量不能超过总棋子数量的 $\dfrac{1}{3}$。
# 题解  
~~遇到构造题我就降智~~

我们回想到不久前有一场CF（因为unrated了所以印象特别深刻），C题可以用奇偶判断来避免相邻的两个相同。  
然后我们考虑到能连成 $3$ 个相邻的棋子，它们的横纵坐标之和一定构成一个模 $3$ 的完全剩余系。  
我们把横纵坐标之和模 $3$ 余数相同的棋子归为一类。  
$S_i=\{(x_j,y_j)|(x_j+y_j) \bmod 3=i\ \}$  
那我们只需要钦定一下每一类的棋子是哪种就行了。 
除此之外，还需要满足改变棋子不超过 $\dfrac{1}{3}$ 的限制。  
[Easy版本](https://www.luogu.com.cn/problem/CF1450C1)  
在这个版本中，由于所有棋子初始都相同，所以一定存在这么一类棋子，它的个数不多于总棋子个数的 $\dfrac{1}{3}$，那么我们都试一下就行了。  
代码  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=2005+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
 
int n,m,k;
char ch[N][N];
char bb[N][N];
void print()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) cout<<bb[i][j];
		cout<<endl;
	}
}
bool get(string s)
{
	int cnt=0,cnt1=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (ch[i][j]!='.') bb[i][j]=s[(i+j)%3]; else bb[i][j]='.';
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (ch[i][j]!='.') cnt+=(ch[i][j]!=bb[i][j]),cnt1++;
	return cnt<=cnt1/3;
}
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		rd(n);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) cin>>ch[i][j];
		if (get("OXX")) print();
		else if (get("XOX")) print();
		else if (get("XXO")) print();
	}
}
```  
然后我们考虑 Hard版本 怎么做。  
我们发现，我们并不需要钦定那么多棋子。只需要让任意 $3$ 个相邻的棋子有 $2$ 个不同的就行了，剩下的那一个就让它按照原来的那样，这样可以节省改变步数。  

一定存在一类棋子，个数不少于总个数的 $\dfrac{1}{3}$。  
我们钦定这一类棋子不改变，然后剩下的两类棋子个数之和一定不超过总共的 $\dfrac{2}{3}$。  
我们钦定其中一种为 X，另一种为 O；或者钦定其中一种为 O，另一种为 X，它们的改变棋子数量之和一定为 这两类棋子的个数之和。  
也就是说，一定存在一种钦定方式，使这两类棋子的改变数量之和不多于总数的 $\dfrac23\times \dfrac12=\dfrac13$。  
找到这种钦定方式还是太麻烦了，不过我们证明了它是存在的，那么枚举就行了。  

代码  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=2005+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
 
int n,m,k;
char ch[N][N];
char bb[N][N];
void print()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) cout<<bb[i][j];
		cout<<endl;
	}
}
bool get(string s)
{
	int cnt=0,cnt1=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (ch[i][j]!='.' && s[(i+j)%3]!='.') bb[i][j]=s[(i+j)%3]; else bb[i][j]=ch[i][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (ch[i][j]!='.') cnt+=(ch[i][j]!=bb[i][j]),cnt1++;
	return cnt<=cnt1/3;
}
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		rd(n);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) cin>>ch[i][j];
		int cnt=0;
		if (get(".XO")) print();
		else if (get("OX.")) print();
		else if (get("XO.")) print();
		else if (get("O.X")) print();
		else if (get("X.O")) print();
		else if (get(".OX")) print();
	}
}
```

---

## 作者：St_john (赞：4)

## [CF1450C2](https://www.luogu.com.cn/problem/CF1450C2)

考虑把棋盘分成三部分，像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/tezegham.png)
具体来讲是按照横纵坐标之和模 $3$ 的余数进行染色的。   


发现每组上下左右相邻三个，颜色各不相同，这是很好的性质。  
不妨对所有黄色，深红色，浅红色都各自钦定一个字符 `X` 或 `O` 或 `.`，然后进行修改。  
我们当然不会修改和钦定一样的、原来字符是 `.` 的以及要改成 `.` 的。  



------------

### 正确性的证明

分情况讨论：
1. 如果原来和要改的一样，显然正确。  
1. 不修改要改成 `.` 的，每组里还是有两个不同的。  

### 关于操作次数的上界问题
每种颜色有两类棋子的可能，共有 $3$ 种颜色。  
全部操作方案数为 $2k$。  
而我们有 $6$ 种不同的修改方式，必有一种改的数目 $\leqslant \lfloor \frac{k}{3} \rfloor$。  



------------

接下来，进行模拟即可。

```cpp
#include<cstdio>
#include<vector>
using namespace std;
#define il inline
#define pc putchar
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define Re register int
il int re(){
	int x=0;
	bool f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0')
		f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
void pr(int x){
	if(x<0) x=-x,pc('-');
	if(x>9) pr(x/10);
	pc(x%10|48);
}
const int A=300+10;
char s1[A][A],s2[A][A],s3[3];
int n,m;
bool check(){
	_for(i,1,n)
		_for(j,1,n)
			if(s1[i][j]!='.'&&s3[(i+j)%3]!='.')
				s2[i][j]=s3[(i+j)%3];
			else s2[i][j]=s1[i][j];
	int num=0;
	_for(i,1,n)
		_for(j,1,n)
			if(s1[i][j]!=s2[i][j])
				++num;
	return num<=m/3;
}
il void print(){
	_for(i,1,n){
		_for(j,1,n)
			pc(s2[i][j]);
		pc('\n');
	}
}
signed main(){
	__for(_,re(),1){
		n=re();m=0;
		_for(i,1,n){
			scanf("%s",s1[i]+1);
			_for(j,1,n)
				if(s1[i][j]!='.')
					++m;
		}
		s3[0]='.',s3[1]='O',s3[2]='X';
		if(check()){
			print();
			continue;
		}
		s3[0]='.',s3[2]='O',s3[1]='X';
		if(check()){
			print();
			continue;
		}
		s3[1]='.',s3[2]='O',s3[0]='X';
		if(check()){
			print();
			continue;
		}
		s3[1]='.',s3[0]='O',s3[2]='X';
		if(check()){
			print();
			continue;
		}
		s3[2]='.',s3[0]='O',s3[1]='X';
		if(check()){
			print();
			continue;
		}
		s3[2]='.',s3[1]='O',s3[0]='X';
		if(check()){
			print();
			continue;
		}
	
	}
	return 0;
}
```


---

## 作者：dead_X (赞：1)

## 前言
挺简单的，为啥场上过的人比 D 少啊
## 思路
注意到**对角线**的三连并不算胜利，我们考虑对对角线进行构造。

于是，我们考虑对从左上到右下的对角线依次染色。

不难发现，我们可以对第 $3i+1$ 个对角线全染成 X，第 $3i+2$ 个对角线全染成 O，第 $3i$ 个对角线不染，于是就做完了。

这样的正确性是显然的，因为任意一横/一竖的三个格子中，必定有一个格子所在的对角线染了 X，另一个格子所在的对角线染了 O。不难发现将这三个染色方法任意排列，仍然可以保证正确性。

那为什么只需要移动 $\lfloor\frac{k}{3}\rfloor$ 个棋子呢？

我们的染色法共有 $6$ 种，每个棋子显然只会将 $2$ 种方法所需要的染色次数 $+1$，因此根据抽屉原理，必然存在一种方案次数 $\leq\lfloor\frac{k}{3}\rfloor$。
## 代码
```
//愿神 zhoukangyang 指引我。
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
char s[303][303];
signed main()
{
	for(int T=read();T--;)
	{
		int n=read();
		for(int i=1; i<=n; i++)
		scanf("%s",s[i]+1);
		int C=0,G=0;
		for(int i=1; i<=n; i++) for(int j=1; j<=n; ++j) 
		if(s[i][j]!='.') ++C;
		G=C/3;
		int A0=0,B0=0,C0=0;
		int A1=0,B1=0,C1=0;
		for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) 
		{
			if((i+j)%3==0) if(s[i][j]=='O') ++A1,++C0; 
			else if(s[i][j]=='X') ++A0,++C1;
			if((i+j)%3==1) if(s[i][j]=='O') ++A0,++B1; 
			else if(s[i][j]=='X') ++A1,++B0;
			if((i+j)%3==2) if(s[i][j]=='O') ++B0,++C1; 
			else if(s[i][j]=='X') ++B1,++C0;
		}
		//printf("%d %d %d %d %d %d\n",A0,A1,B0,B1,C0,C1);
		if(A0<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==0) if(s[i][j]!='.') printf("O");
			else printf(".");
			else if((i+j)%3==1)if(s[i][j]!='.') printf("X");
			else printf(".");
			else printf("%c",s[i][j]);
		}
		else if(A1<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==0) if(s[i][j]!='.') printf("X");
			else printf(".");
			else if((i+j)%3==1)if(s[i][j]!='.') printf("O");
			else printf(".");
			else printf("%c",s[i][j]);
		}
		else if(B0<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==1) if(s[i][j]!='.') printf("O");
			else printf(".");
			else if((i+j)%3==2)if(s[i][j]!='.') printf("X");
			else printf(".");
			else printf("%c",s[i][j]);
		}
		else if(B1<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==1) if(s[i][j]!='.') printf("X");
			else printf(".");
			else if((i+j)%3==2)if(s[i][j]!='.') printf("O");
			else printf(".");
			else printf("%c",s[i][j]);
		}
		else if(C0<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==2) if(s[i][j]!='.') printf("O");
			else printf(".");
			else if((i+j)%3==0)if(s[i][j]!='.') printf("X");
			else printf(".");
			else printf("%c",s[i][j]);
		}
		else if(C1<=G)
		{
			for(int i=1; i<=n; ++i,puts("")) for(int j=1; j<=n; ++j) 
			if((i+j)%3==2) if(s[i][j]!='.') printf("X");
			else printf(".");
			else if((i+j)%3==0)if(s[i][j]!='.') printf("O");
			else printf(".");
			else printf("%c",s[i][j]);
		}
	}
    return 0;
}
```

---

## 作者：RockyYue (赞：0)

### 题意
一个 $n\times n$ 的棋盘上有一些棋子，每个为 X 或 O。你需要将一些 X 变成 O，将一些 O 变成 X，使得棋盘上没有连续三个相同棋子（横着或竖着的）。

要求操作次数不超过 $\lfloor \frac{n^2}{3} \rfloor$，请给出一种构造方案。

### 题解
Trick：构造题看到“不超过/不多于”，想抽屉原理，构造一些方案，使得其中必有一个满足条件。

想到构造三个操作次数和为 $n^2$ 的方案，于是把棋子分成三类，对于点 $(r,c)$，可以按 $(r+c)\bmod 3$ 进行分类（下面写作第 $0/1/2$ 类），这样连续三个棋子必然属于三个不同类。

于是我们只需要将一类中所有棋子设置为同一种，另一类中所有棋子设置成另一种即可，于是在这两类棋子的选取中诞生了以下三个方案：
1. 第 $0$ 类所有 X 变成 O，第 $1$ 类所有 O 变成 X；
2. 第 $1$ 类所有 X 变成 O，第 $2$ 类所有 O 变成 X；
3. 第 $2$ 类所有 X 变成 O，第 $0$ 类所有 O 变成 X；

发现这三种方案的操作次数和恰为 $n^2$，逐个判断哪一个合法即可。

---

## 作者：LCat90 (赞：0)

首先有一个错误的想法：对于每 $3$ 个连续的，我们将其中间的部分改一改。

显然是错的，因为前面改了会影响后面的，并且后面的还会影响前面。

考虑将这个棋盘交叉染黑白色。将白色的**非空点**改成 ``X``，黑色改成 ``O``，假设改 $x_1$ 次；或者将白色的改成 ``O``，黑色的改成 ``X``，假设改 $x_2$ 次。

则有 $x_1+x_2\le n$，可以推出一定有一种办法 $\le \dfrac{n}{2}$ 次。但是题目要求是 $\dfrac{n}{3}$ 次。
 
所以考虑在这个方法的基础上，改为 $3$ 染色。即将**非空点**位置 $(i,j)$ 染成 $i+j \bmod 3$ 颜色。

考虑怎么改一定满足，发现还是大同小异，只是剩下的那个颜色不变就行了。就有 $3$ 种情况：``XO.``、``.XO``、``O.X``。
 
同样的证明，推出最多有 $\dfrac{n}{3}$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, t, k;
char c[N][N];
bool pd(string s) {
	int sum = 0;
	for(int i = 1;i <= n; ++i) {
		for(int j = 1;j <= n; ++j) {
			int sb = (i + j) % 3;
			if(c[i][j] == '.' or s[sb] == '.') continue ;
			sum += s[sb] != c[i][j];
		}
	}
	if(sum > k / 3) return 0;
	for(int i = 1;i <= n; ++i) {
		for(int j = 1;j <= n; ++j) {
			int sb = (i + j) % 3;
			if(c[i][j] == '.') printf(".");
			else if(s[sb] == '.') printf("%c", c[i][j]);
			else printf("%c", s[sb]);
		}
		puts("");
	}
	return 1;
}
signed main() {
	cin >> t;
	while(t--) {
		cin >> n; k = 0;
		for(int i = 1;i <= n; ++i) {
			scanf("%s", c[i] + 1);
			for(int j = 1;j <= n; ++j) k += c[i][j] != '.';
		}
		if(pd("OX.")) continue ;
		if(pd(".OX")) continue ;
		if(pd("X.O")) continue ;
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

还比较好想。

考虑对棋盘三染色，每连着的三个必然有三种颜色。只需要将三种颜色中的其中两种分别染成 O 和 X 或 X 和 O 即可。

总共 $6$ 种染法，选最小的那个做，鸽巢原理容易发现操作次数不超过其限制。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 305;

int col[N][N];
char c[N][N];
int t, n, sum = 0;

char res[N][N], tmp[N][N];

void solve(int c1, int c2, char f1, char f2)
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			tmp[i][j] = c[i][j];
			if (c[i][j] == '.') continue;
			if (col[i][j] == c1)
			{
				if (c[i][j] != f1)
				{
					cnt++;
					tmp[i][j] = f1;
				}
			}
			else if (col[i][j] == c2)
			{
				if (c[i][j] != f2)
				{
					cnt++;
					tmp[i][j] = f2;
				}
			}
		}
	}
	if (cnt <= sum / 3)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				res[i][j] = tmp[i][j];
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--)
	{
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++) cin >> c[i][j], col[i][j] = (i + j) % 3, sum += (c[i][j] != '.');
		}
		solve(0, 1, 'O', 'X');
		solve(0, 1, 'X', 'O');
		solve(1, 2, 'O', 'X');
		solve(1, 2, 'X', 'O');
		solve(2, 0, 'O', 'X');
		solve(2, 0, 'X', 'O');
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++) cout << res[i][j];
			cout << "\n";
		}
	}

	return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17548276.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1450C2)

再不写题解社贡要掉到 $0$ 了。

## 题目分析

显然如果 $3$ 个格子构成了满足获胜条件的情况，这 $3$ 个格子模 $3$ 的余数各不相同。

那么我们将格子按模 $3$ 的余数分为 $3$ 类，只要保证相邻 $3$ 个格子中有 $2$ 个不同就行了，不需要动第 $3$ 个。

我们令格子数最多的类型为 ```.``` 而其余为 ```X``` 和 ```O```，显然 ```.``` 的个数不少于总数的 $\dfrac{1}{3}$。

剩下有 $2$ 种情况，分别是第 $1$ 类 ```X```、第 $2$ 类 ```O``` 和第 $1$ 类 ```O```、第 $2$ 类 ```X```，它们操作次数的总和一定是 ```X``` 和 ```O``` 的数量之和。根据抽屉原理，一定有一种情况操作不超过 $\lfloor \dfrac{k}{3} \rfloor$

## 贴上代码

```cpp
// Problem: Errich-Tac-Toe (Hard Version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1450C2
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define ok puts("First")
#define no puts("Second")
#define debug puts("Shima_Rin_kawaii")
#define clean fflush(stdout)
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();	
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=310;
int n;
int res;
int a[5];
char s[maxn][maxn],ans[maxn][maxn];
inline void init(){
	n=read();res=0;
	memset(a,0,sizeof(a));
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j) cin>>s[i][j];
	}
}
inline void solve(){
	init();
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			if(s[i][j]=='X') a[(i+j)%3]++;
			else if(s[i][j]=='O') a[(i+j-1)%3]++;
		}
	}
	for(register int i=0;i<3;++i){
		if(a[i]<=a[res]) res=i;
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			if(s[i][j]=='X'&&(i+j)%3==res) ans[i][j]='O';
			else if(s[i][j]=='O'&&(i+j-1)%3==res) ans[i][j]='X';
			else ans[i][j]=s[i][j];
		}
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j) cout<<ans[i][j];
		puts("");
	}
}
int main(){
//	freopen("test.out","w",stdout);
	int T=read();
	while(T--) solve();
}
```

---

## 作者：ListenSnow (赞：0)

### 思路

注意到能够构成胜局的三个位置，它们的横纵坐标和模 $3$ 的余数各不相同。考虑将所有格子依照模 $3$ 的余数分为 $3$ 类。

此时只需要保证其中两类格子互不相同，剩下一类格子不变，也就不会出现胜局了。根据这种思路，一共有 $6$ 种修改方案。每一个包含标志的格子，更改其颜色的方案有两种，那么总的更改次数就是 $2k$。根据抽屉原理，其中最小的修改次数不超过 $\lfloor \frac{k}{3}\rfloor$。

### code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=310;
char a[N][N],s[N][N];int n,m;
bool check(char t[])
{
	int cnt=0;
	for(int i=1;i<=n;i++) 
	    for(int j=1;j<=n;j++)
	    {
	    	if(t[(i+j)%3]=='O'&&s[i][j]=='X') cnt++,a[i][j]='O';
	    	else if(t[(i+j)%3]=='X'&&s[i][j]=='O') cnt++,a[i][j]='X';
	    	else a[i][j]=s[i][j];
		}
	return cnt<=m/3;
}
void print(){for(int i=1;i<=n;i++,puts("")) for(int j=1;j<=n;j++) putchar(a[i][j]);}
void solve()
{
	scanf("%d",&n);m=0;for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) m+=(s[i][j]!='.');
	if(check(".XO")) return print(),void();
	if(check(".OX")) return print(),void();
	if(check("X.O")) return print(),void();
	if(check("O.X")) return print(),void();
	if(check("XO.")) return print(),void();
	if(check("OX.")) return print(),void();
}
int main()
{
	int T;scanf("%d",&T);while(T--) solve();
	return 0;
}
```

---

