# Yet Another Card Deck

## 题目描述

You have a card deck of $ n $ cards, numbered from top to bottom, i. e. the top card has index $ 1 $ and bottom card — index $ n $ . Each card has its color: the $ i $ -th card has color $ a_i $ .

You should process $ q $ queries. The $ j $ -th query is described by integer $ t_j $ . For each query you should:

- find the highest card in the deck with color $ t_j $ , i. e. the card with minimum index;
- print the position of the card you found;
- take the card and place it on top of the deck.

## 说明/提示

Description of the sample:

1. the deck is $ [2, 1, 1, 4, \underline{3}, 3, 1] $ and the first card with color $ t_1 = 3 $ has position $ 5 $ ;
2. the deck is $ [3, \underline{2}, 1, 1, 4, 3, 1] $ and the first card with color $ t_2 = 2 $ has position $ 2 $ ;
3. the deck is $ [2, 3, \underline{1}, 1, 4, 3, 1] $ and the first card with color $ t_3 = 1 $ has position $ 3 $ ;
4. the deck is $ [\underline{1}, 2, 3, 1, 4, 3, 1] $ and the first card with color $ t_4 = 1 $ has position $ 1 $ ;
5. the deck is $ [1, 2, 3, 1, \underline{4}, 3, 1] $ and the first card with color $ t_5 = 4 $ has position $ 5 $ .

## 样例 #1

### 输入

```
7 5
2 1 1 4 3 3 1
3 2 1 1 4```

### 输出

```
5 2 3 1 5```

# 题解

## 作者：德布劳内yyds (赞：6)

# CF1511C题解

这道题看着唬人，其实就是一道模拟（~~卡本蒟蒻了半天~~）
### 思路：从上往下找，有一个就停，并将之置顶
### 注意：$a_i$ 不需要开数组，实时处理即可，不然空间不够
（~~别问我怎么知道的，我总不会告诉你我wa了n次吧~~）

### 样例解释：

输入 

7 5

2 1 1 4 3 3 1

3 2 1 1 4

输出

5 2 3 1 5

第二行表示现有卡片，最后是要找的卡片。

第一个找三，在第五位，输出五，并将三置顶，数列就变成了这样

3 2 1 1 4 3 1

第二个找2，在第二个，输出二，数列变为 2 3 1 1 4 3 1

------------
## 大体方法
开双重循环，第一重q，输入t，第二重n，即先确定 $t_i$ ，然后再a数组中寻找相等的数，找到后置顶

### 置顶方法
不要管要找的数以后的以后的，例如

2 1 1 4 3 3 1

3

三在第五个，将3提出来，变成 2 1 1 4 （ ） 3 1

从（）以前开始操作【2 1 4 （ ）】，滚筒式向后位移一格，变为
【( )2114】

把三放在最前面,并将后面的加上：3 2 1 1 4 3 1

### 置顶代码
```
for(int i=x;i>0;i--) /* x为目标数位置 */
{
	a[i]=a[i-1];
}
a[0]=t; /* 将找到的数置顶 */
```
下面上代码
## AC CODE
```
#include<bits/stdc++.h>
using namespace std;

int a[300006];

int main()
{
	int n,q,t,x;
	cin>>n>>q;
	for(int i =0;i<n;++i)
	{
		cin>>a[i];
	}
	for(int i =0;i<q;++i)
	{
		cin>>t;
		for(int j =0;j<n;++j)
		{
			if(t==a[i])
			{
				cout<<j+1<<' ';
				x =j;
				break;
			}
		}
		for(int k=x;k>0;k--) //置顶 
		{
			a[i]=a[i-1];
		}
		a[0]=t;
	}
	cout<<endl;
	return 0;
}
```
# 感谢大佬观看

---

## 作者：_xbn (赞：4)

相对于其他题解的做法，我的做法相对比较暴力。但比较好写。

既然答案为某个数的位置，那我们就开一个数组存储每个数第一次出现的位置，

每次修改操作，把被修改的数对于的位置设为一，在修改之前位于它前面的数

全部向后移动一格。直接模拟就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,p[1000001],a[1000001],o=0;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
	   cin>>a[i];
	   o=max(o,a[i]);
	   if(!p[a[i]])p[a[i]]=i;
	}
	int x;
	for(int i=1;i<=q;i++)
	{
		cin>>x;
		cout<<p[x]<<" ";
		for(int j=1;j<=o;j++)
		   if(p[j]<p[x])p[j]++;
		p[x]=1;	
	}
	return 0;
}


```




---

## 作者：pitiless0514 (赞：1)

因为值域很小，所以可以从值域上来考虑。

发现每次只需要找到每个数第一次出现的位置，那么就可以开一个数组来存储每个数第一次出现的位置。

每次询问就将出现位置比这个数小的位置往后移一位。然后将这个数的位置改为 $1$ 。

```cpp
/*****************
  | @author:Pitiless0514 |
  | @qq:3071106789       |
  | @                    |  
********************/
#include<bits/stdc++.h>
using namespace std;
const int N = 3e6;
int T,l,r;
int q,n,a[N],b[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!b[a[i]]) b[a[i]]=i;
	}
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		cout<<b[x]<<" ";
		for(int j=1;j<=50;j++){
			if(b[j]<b[x]) b[j]++;
		}
		b[x]=1;
	}
	return 0;
}
```


---

## 作者：云浅知处 (赞：1)

不难发现对于每种颜色的卡片，实际上被操作了的只有最上面的那一个。

那我们先预处理出来每种颜色的卡片中位置最靠上的那个。

（然后颜色数 $\le 50$ 那不是随便乱搞）

接下来对于每次修改，把修改的那个数的位置设成 $1$，再把修改时位于它前面的数的位置全部往后挪一格即可。

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<map>

#define int long long
#define MAXN 300005

using namespace std;

int n,q,a[MAXN],t[MAXN];
int p[100];

signed main(void){

    cin>>n>>q;
    int maxx=0;
    for(int i=1;i<=n;i++)cin>>a[i],maxx=max(maxx,a[i]);
    for(int i=1;i<=n;i++){
        if(!p[a[i]])p[a[i]]=i;//p[i] 表示 i 第一次出现的位置
    }

    for(int i=1;i<=q;i++){
        cin>>t[i];
    }

    for(int i=1;i<=q;i++){
        cout<<p[t[i]]<<" ";
        for(int j=1;j<=maxx;j++){
            if(j==t[i])continue;
            if(p[j]<p[t[i]])p[j]++;
        }
        p[t[i]]=1;
    }

    return 0;
}
```

---

## 作者：Warriors_Cat (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1511C) & [CF 题面传送门](http://codeforces.com/problemset/problem/1511/C)。

题意简述：

* 有 $n$ 张卡片，下标为 $i$，分别有颜色 $a_i$，摞成一个栈。

* $q$ 次操作，每次操作给定一个颜色 $k$，将颜色为 $k$ 的下标最小的卡片拿出来，放到栈顶，并输出每次拿出来的卡片当前下标。

* $n, q \le 3\times 10^5$，$a_i \le 50$。

经典“暴力可过”，一个月前的 CF 好像也出了这种题。

---

### Solution：

首先注意到每种颜色都只会移一开始时最上面的那张，于是只需要考虑每种颜色最上面的那张就行。

所以每次移动只需要考虑 $50$ 张卡片的变化就行了，这可以直接模拟，时间复杂度为 $O(n+50q)$。

当然如果像我刚开始一样蠢的话可以直接考虑暴力，直接维护每个颜色的卡片下标，然后每次操作直接暴力处理卡片下标即可。

这样做乍一看是 $O(nq)$ 的，但仔细想想会发现，每一种颜色的卡片第一次会使其它卡片移动 $O(n)$ 的次数，可第二次以后它的上面至多只有 $50$ 张，所以会使其它卡片移动 $O(50)$ 的次数。这样时间复杂度就应该是 $O(50(n+q))$。

---

### Code：

以下是 $O(50(n+q))$ 的做法。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = y; i >= x; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define mpr make_pair
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 300010, M = 55;
int n, m, x, a[N], b[N], L[N], R[N]; 
inline void mian(){
	n = read(); m = read();
	L[1] = 1; R[50] = 50;
	rep(i, 1, n) a[i] = read();
	rep(i, 1, 50){
		rep(j, 1, n){
			if(a[j] == i){
				b[++R[i]] = j;
			}
		}
		L[i + 1] = R[i] + 1;
		R[i + 1] = R[i];
	}
	rep(i, 1, m){
		x = read();
		printf("%d ", b[L[x]]);
		rep(j, 1, 50){
			if(j == x) continue;
			int p = L[j];
			while(p <= R[j] && b[p] < b[L[x]]){
				++b[p]; ++p;
			}
		}
		b[L[x]] = 1;
	}
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```

---

## 作者：FutaRimeWoawaSete (赞：0)

第一眼不会做（             

观察到值域小后就显了。           

考虑先记录下每个数第一个出现的位置，然后这种数输出的答案只有可能是这个数的位置了。            

然后每次把数放到前面去的时候顺便维护一下其它数的位置就好了。        
```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5;
int n,m,fir[55],a[Len]; 
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		if(!fir[a[i]]) fir[a[i]] = i;
	}
	for(int i = 1 ; i <= m ; i ++) 
	{
		int x;scanf("%d",&x);
		printf("%d\n",fir[x]);
		for(int j = 1 ; j <= 50 ; j ++) if(fir[j] < fir[x]) fir[j] ++;
		fir[x] = 1;
	}
	return 0;
}
```

---

## 作者：翼德天尊 (赞：0)

这种题往往要考虑每一个元素对于答案的贡献。

由于每种颜色的卡片只会取最上面的一个，所以每种颜色只有最上面的一个卡片是对答案有贡献的，则其它卡片可以直接忽略。

考虑使用 $col_i$ 表示第 $i$ 种颜色的卡片最上面的一张卡片在栈中的位置，在每次询问时输出询问的颜色目前的位置并维护 $col$ 数组即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,col[55];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	n=read(),q=read();
	for (int i=1;i<=n;i++){
		int a=read();
		if (!col[a]) col[a]=i;
	}
	while (q--){
		int a=read();
		printf("%d ",col[a]);
		for (int i=1;i<=50;i++){
			if (col[i]<col[a]) col[i]++;
		}
		col[a]=1;
	}
	return 0;
}
```


---

## 作者：EDqwq (赞：0)

### 思路：

显然的一点是，每一个数的卡，只有最上面的那一个才会被用，其他的不可能会被用到。

所以我们输入的时候维护一下输入的第一个不同数的卡的位置。

修改的时候，在它前面的卡，全部+1，它自己设为1。

复杂度$O(50n)$

***

### 代码

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m;
int q[60];
int cnt;

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++){
		int x;
		x = read();
		if(!q[x]){
			q[x] = i;
		}
	}
	while(m --){
		int x;
		x = read();
		//for(int i = 1;i <= 4;i ++)cout<<"q[i] = "<<q[i]<<endl; 
		cout<<q[x]<<" ";
		for(int i = 1;i <= 50;i ++){
			if(i != x && q[i] < q[x])q[i] ++;
		}
		q[x] = 1;
	}
	return 0;
}
```

---

## 作者：Mophie (赞：0)

首先看到值域这么小可以去想与值域有关的做法。

然后发现每种卡牌只有第一张有用。把那些无用的忽略，然后记录每种卡牌的位置

然后直接暴力即可，每次暴力提前然后把先前在它前面的所有卡牌的位置往后移。

时间复杂度 $O(50(n+q))$

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
int n,q,a[300009],pos[59],x;
signed main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i>=1;i--)pos[a[i]]=i;
	for(int i=1;i<=q;i++)
	{
		x=read();printf("%d ",pos[x]);
		for(int j=1;j<=50;j++)
			if(pos[j]!=0&&pos[j]<pos[x])pos[j]++;
		pos[x]=1;
	}
	return 0;
}

```


---

## 作者：dead_X (赞：0)

## 题意
有 $n$ 张卡片，第 $i$ 张的颜色为 $a_i$，下标为 $i$。

你需要执行 $m$ 次操作，第 $i$ 次操作将颜色为 $x_i$ 且下标最小的卡片的下标输出。输出后，将下标为 $[1,i)$ 的卡片下标增加 $1$，将这张卡片下标设为 $1$。

$n\leq 10^5,\max\{a_i\}\leq 50$。
## 思路
注意到下标最小的卡片是哪一张已经固定，因此我们只需要维护每种颜色下标最小的卡片对应的下标即可。

注意到 $\max\{a_i\}\leq 50$，因此我们可以直接模拟题目中的操作。
## 代码
```cpp
// Problem: C. Yet Another Card Deck
// Contest: Codeforces - Educational Codeforces Round 107 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1511/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
int a[1000003],f[103];
signed main()
{
    	int n=read(),q=read();
    	for(int i=1; i<=50; ++i) f[0]=0;
    	for(int i=1; i<=n; ++i) a[i]=read();
    	for(int i=1; i<=n; ++i) if(!f[a[i]]) f[a[i]]=i;
    	for(int i=1; i<=q; ++i)
    	{
    		int x=read();
    		printf("%lld ",f[x]);
    		for(int i=1; i<=50; ++i) if(f[i]<f[x]) ++f[i];
    		f[x]=1;
    	}
	return 0;
}

```

---

