# fLIP

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-quala/tasks/code_festival_2017_quala_b

$ N $ 行 $ M $ 列のマス目があり、最初は全てのマスが白いです。

各行各列には $ 1 $ つずつボタンがあります。 ある行のボタンを押すと、その行のマスの色が全て反転します。すなわち、白なら黒、黒なら白に色が変わります。 また、ある列のボタンを押すと、その列のマスの色が全て反転します。

高橋君は、ボタンを押す操作を好きな回数行うことができます。黒く塗られたマスの個数をちょうど $ K $ 個にすることができるかどうか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 1000 $
- $ 0\ \leq\ K\ \leq\ NM $

### Sample Explanation 1

$ 1 $ 行目、 $ 1 $ 列目の順にボタンを押せばよいです。

### Sample Explanation 3

$ 1 $ 列目、$ 3 $ 列目、$ 2 $ 行目、$ 5 $ 列目の順にボタンを押せばよいです。

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2 1```

### 输出

```
No```

## 样例 #3

### 输入

```
3 5 8```

### 输出

```
Yes```

## 样例 #4

### 输入

```
7 9 20```

### 输出

```
No```

# 题解

## 作者：lgvc (赞：5)

假设我们对 $i$ 行进行了反转，对 $j$ 列进行了反转。

则会有 $i \times m+j \times n -2 \times i \times j$ 个黑色格子。

枚举 $i$，$j$ 来找出解，有解则输出 ```Yes```，否则输出 ```No```。

时间复杂度为 $O(nm)$。

代码：

```cpp
#include <bits/stdc++.h>
int N,M,K;
signed main(void) {
	scanf("%d %d %d",&N,&M,&K);
	for(int i=0;i<=N;i++) {
		for(int j=0;j<=M;j++) {
			if(i*M+j*N-2*i*j==K) {
				printf("Yes");
				return 0;
			}
		}
	}
	printf("No");
    return 0;
}

```


---

## 作者：李思远 (赞：2)

### $\Theta\left( n\right)$复杂度 

看样子，是一道模拟，实际想一想就可以推出公式。（实际好像还是模拟）

#### 简化题意：
有一张 $ M * N $ 的图，初始全为**0**，每次操作对一行或一列进行**取反**，求进行任意次操作后能否有 $ K $ 个点为**1**。

#### 解法：

先明确一下，如果对某一行（列）操作两次就等于没操作，所以以下不考虑对同一行或列重复操作。

如果先对一行进行操作，那么就一共有 $ M $ 个点。
同理对 $ X $ 行进行操作，就有 $ X*M $ 个点（不考虑列）。
在这个基础上，对一列进行操作会增加 $ N-X $ 个点，但在这同时却破坏了每一行的一个点。

根据这个就可以推导出一共有 $ (M-y)\times x+(N-x)\times y $ 个点.

（ $ M $ 是总行数， $ N $ 是总列数， $ x $ 是对 $ x $ 行进行操作， $ y $ 是对 $ y $ 行进行操作）。

化简为 $ X*M+Y*N-2XY $。

那么我们只需要枚举 $ X $ 和 $ Y $ 便可以判断。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int m,n,k;
	bool ans=0;
	cin>>m>>n>>k;
	for(int x=0;x<=n;x++)//枚举x
		for(int y=0;y<=m;y++)//枚举y
		{
			if(x*m+y*n-2*x*y==k)//判断
			{
				x=m+2;y=n+2;//一次跳出两层循环
				ans=1;//成立
			}
		}
	if(ans)cout<<"Yes";
	else cout<<"No";
	return 0;//圆满收工
}
```

---

## 作者：珅肐 (赞：2)

提供一篇$O(n)$的题解

首先我们知道，翻转次数的上界是$n+m$，因为如果超过$n+m$，必有一行或一列翻转了两次，这就做了重复操作。

由此我们想到了$O(n*m)$的做法，因为翻转i行j列时黑格个数可以算，是$i*m+j*n-i*j-i*j$（画图有助于理解），枚举$i,j$就可以做了。

![](https://i.loli.net/2019/01/06/5c315dee39b23.bmp)

有没有更快的方法？

根据这个式子我们知道，当$i$不变，$j$增加$1$时，黑格子个数增加的是定值$n-i-i$，于是我们可以枚举$i$，判断剩下的$k$是否能整除$n-i-i$，如果可以，就说明可以组成。

当然，这里剩下的$k$和$n-i-i$必须同号，如果$k>0$但是$n-i-i<0$的话，加多少都是到不了$k$的。

---------------代码在这里---------------
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstdlib>
using namespace std;
inline int read(){//快读,很快！
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
inline void Yeah(){puts("Yes");exit(0);}//可以得到
int main(){ 
	int n=read(),m=read(),k=read();//读入
	for(int i=1;i<=n;++i){
		int kk=(k-i*m),a=n-i-i;//kk是剩下的要变成黑色的格子,a是每次增加的黑格子
		if(!kk || a && (kk>>31&1)==(a>>31&1) && kk%a==0 && kk/a<=m)Yeah();
        //!kk说明已经填完了，可以直接输出。
        //a不能等于0,否则%0会报错，
        //(kk>>31&1)==(a>>31&1)这句是判断kk和a是否同号,二进制表示的负数第一位是1
        //kk%a==0前面已经说过，就是可以组成的情况
        //kk/a必须小于等于m,因为j最多加m次
	}
	puts("No");
	return 0;
}
```

总感觉这题有$O(1)$的做法，有兴趣的可以自己思考一下。

---

## 作者：Holy_King (赞：1)

## 题意的一些点
1.按钮**无论按几次**，都只有按和不按两种状态，偶数次的按按钮等同于不按

2.无论按哪一行/列，都是一样的，所以只要枚举有多少行/列就可以了

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N,M,K;

int bg(int x,int y)//当前黑色格子数
{
	return x*M+y*N-2*x*y;
}

int main()
{
	cin >> N >> M >> K;
  //注:i,j要从0开始，表示可以不按按钮
	for (int i=0; i<=N; i++)
	{
		for (int j=0; j<=M; j++)
		{
			if (bg(i,j)==K)//判断是否可以达成K个格子
			{
				cout << "Yes";
				return 0;
			} 
		}
	}
	cout << "No";
	return 0;
}
```


---

## 作者：Yikara (赞：1)

# 题意
给你一个 $m\times n$ 的方阵，方阵只有两种状态 $0$ 和 $1$，每次可以反转一行或一列，请问能否能使得指定数量的方格为 $1$ 。

# 思路
乍一看似乎很复杂，但是如果举例看，就会简单很多：比如我们反转 $1$ 行 $1$ 列，可以发现无论以什么顺序，只要反转的行列相同，那么为 $1$ 的方格数量是相同的。

每一行和每一列只有反转和不反转两种状态，结合数据范围，我们可以模拟所有可能的情况，从零开始枚举翻转的行数和列数，每次判断是否符合条件。

AC代码：

```cpp
#include<iostream>
using namespace std;
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(register int i=0;i<=n;++i){//枚举反转的行和列 
    	for(register int j=0;j<=m;++j){
        	if(i*m+j*n-2*i*j==k){//计算总数是否符合 
                puts("Yes");
                return 0;
            }
		}
	}
    puts("No");//不符合 
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

其实这题就是一个纯模拟。

只要枚举一下要反转的行和列，判断黑色的个数，等于 $k$ 就输出 $Yes$ 并直接结束，否则输出继续。到循环结束就输出 $No$ 。

判断黑色的个数也很简单。

因为一个小方块最多会被反转两次，只有行和列都被反转的才会被反转两次，也就变回了白色，而只反转一次的就是黑色。

只要用总的反转次数减去反转两次的小方块个数，就是黑色的个数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            if(i*m+j*n-2*i*j==k){
                cout<<"Yes"<<endl;
                return 0;
            }
    cout<<"No"<<endl;
    return 0;
}
```

---

## 作者：Fengxiang008 (赞：0)

## 题意理解与分析
这是一道模拟题。

大致操作：
枚举需转的**行和列**，判断在操作中变成黑色的个数，若运行中等于  k  就输出  Yes  直接结束程序（因为这里如果错了，后面就不需要再去验证，直接结束），否则继续。到循环结束就输出 No 。

判断黑色的个数的方法：

$\therefore $ 一个小方块最多会被反转两次 ( 有题意得 ) ，当且仅当行和列都被反转的才会被反转两次，才会变回了白色，若反转一次则是黑色。

$ \because $
用反转次数减去反转两次的小方块个数，就是黑色的个数。

## 代码演示

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main()//具体操作已说明 
{
    cin>>n>>m>>k;
    for(int i=0;i<=n;i++)
    {
    	for(int j=0;j<=m;j++)
    	{
    		if(i*m+j*n-2*i*j==k)
			{
                cout<<"Yes"<<endl;//记得换行
                return 0;
			}
		}       
	}   
    cout<<"No"<<endl;//记得换行 
    return 0;
}

```


---

## 作者：Victory_Defeat (赞：0)

一道水题

思路如下：

我们考虑枚举每一行和每一列，看应该怎么做，这样的话复杂度是$O(2^{nm})$

随后，进行考虑，发现哪一行哪一列开关与结果无关，只需知道**行与列的总开关数**即可，考虑$O(mn)$枚举，能想到打开$i$行$j$列开关打开时黑格个数即可$AC$

那么打开$i$行$j$列开关打开时黑格个数是多少呢？

回答是$m*i+(n-i*2)*j$为什么呢？

因为打开$i$行就有$m*i$个黑格，再打开$j$个行时，就会减少$i*j$并增加$(n-i)*j$，合并后就会得到上面的式子

因此，模拟思路完全出来了，下面，上代码：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
typedef double lf;
typedef unsigned un;
typedef int in;
#define mian main
#define maxn 10000+10
#define maxm 10000+10
#define _(a) read(a)
#define non void
#define inf 2147483647
#define bre break
#define con continue
#define prq priority_queue
#define re register
#define bu bool
#define cz char
#define cst const
#define ope operator
#define inl inline
#define upp upper_bound
#define low lower_bound
#define next_per next_permutation
cz obuf[1<<23],*O=obuf,buf[100000],*L=buf,*R=buf;
inl cz gc(){return L==R&&(R=(L=buf)+fread(buf,1,100000,stdin),L==R)?EOF:*L++;}
template<typename T>inl T Max(T a,T b){return a>b?a:b;}
template<typename T>inl T Min(T a,T b){return a<b?a:b;}
template<typename T>inl T Abs(T a){return a<0?-a:a;}
template<typename T>inl non read(T &a){a=0;T k=1;char c=gc();while(c<'0'||c>'9')k=c=='-'?-1:k,c=gc();while(c>='0'&&c<='9')a=a*10+(c^48),c=gc();if(c!='.'){a*=k;return;}T t=0.1;while(c<'0'||c>'9')c=gc();while(c>='0'&&c<='9')a+=t*(c^48),c=gc(),t*=0.1;a*=k;}
template<typename T>non print(T x){if(x>9)print(x/10);*O++=x%10+'0';}
template<typename T>non out(T a,cz t=' '){print(a);*O++=t;}
non fresh(){fwrite(obuf,O-obuf,1,stdout);}
in n,m,k;
//到这儿不用管
in main()
{
	read(n),read(m),read(k);
   //输入
	for(in i=0;i<=n;++i)
	{
        in t=m*i;
        for(in j=0;j<=m;++j)
		{
            if(t+(n-(i<<1))*j==k)
			{
                *O++='Y';*O++='e';*O++='s';fresh();
                return 0;
            }
        }
    }
    //模拟，请别管*O++那一块，当做cout<<"Yes"和cout<<"No"即可
    *O++='N';*O++='o';
    fresh();
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
}
```

---

