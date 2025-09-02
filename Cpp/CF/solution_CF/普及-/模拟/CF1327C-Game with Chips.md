# Game with Chips

## 题目描述

Petya 有一个大小为 $n×m$ 的矩形版。一开始，在板子上有 $k$ 个芯片，第 $i$ 个芯片位置位于第 $sx$ 行与第 $sy$ 列的相交点上。

在一次操作中， Petya 可以把所有的芯片向左、向右、向下或者向上移动一格。

如果芯片在 $(x, y)$ 格中，则在操作之后：

- 往左：坐标为 $(x, y - 1)$;
- 往右：坐标为 $(x, y + 1)$;
- 往下：坐标为 $(x + 1, y)$;
- 往上：坐标为 $(x - 1, y)$;

如果现在芯片在版的边缘上，然而 Petya 将其移向边缘，那么芯片的位置保持不变。

对于每一个芯片， Petya 选择了他应该到达的位置。注意：芯片不须在这个地方停下来。

由于 Petya 时间不多， 总操作数不能超过 $2nm$。

你需要求出 Petya 应该做的操作：在不超过 $2nm$ 的操作里让每个芯片走过 Petya 选定的位置一遍。或者说明是不可能达到目的的。

## 样例 #1

### 输入

```
3 3 2
1 2
2 1
3 3
3 2```

### 输出

```
3
DRD```

## 样例 #2

### 输入

```
5 4 3
3 4
3 1
3 3
5 3
1 3
1 4```

### 输出

```
9
DDLUUUURR```

# 题解

## 作者：AutumnKite (赞：13)

考场上的我甚至想过把坐标旋转 $x,y$ 独立等等奇怪的玩意。

在想这东西的时候，发现这东西是有边界的，而且到边界他就不会继续走了。

于是我不会了。

转念一想，既然可以走 $2nm$ 步，好像直接把所有点移到 $(1,1)$，然后把所有点走一遍就好了！

移到 $(1,1)$ 需要 $n+m-2$ 步，遍历所有点需要 $nm-1$ 步，步数显然是不超过 $2nm$ 的。

代码里移动到 $(1,1)$ 用了 $n+m$ 步。

```cpp
int n, m, k;
void solve(){
	read(n), read(m), read(k);
	for (register int i = 1, x, y; i <= k; ++i) read(x), read(y);
	for (register int i = 1, x, y; i <= k; ++i) read(x), read(y);
	print(n + m + n * m - 1);
	for (register int i = 1; i <= n; ++i) putchar('U');
	for (register int i = 1; i <= m; ++i) putchar('L');
	for (register int i = 1; i <= n; ++i){
		for (register int j = 1; j < m; ++j) putchar(i & 1 ? 'R' : 'L');
		if (i < n) putchar('D');
	}
	putchar('\n');
}
```

---

## 作者：ix35 (赞：4)

很神奇的题。

我们可以这样构造：先将所有点重叠到一个位置上，然后这个位置在整个地图上都扫一遍，这样每个点一定经过至少一次目标位置了。

具体方案就是：我们先做 $n-1$ 次 $D$，这样所有点都在最后一行，再做 $m-1$ 次 $R$，这样所有点都在右下角。

接下去按照蛇形将这个地图扫描一遍即可。

看一下用了几步，移到右下角的步数为 $n+m-2$，接下来扫地图的步骤为 $nm-1$，所以总的是 $n+m+nm-3<2nm$，可以通过。

于是我们只读入了两个数（我写的时候就顺带读了 $k$...），解决了这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k,n,m;
int main () {
	scanf("%d%d%d",&n,&m,&k);
	printf("%d\n",n+m-2+n*m-1);
	for (int i=1;i<=n-1;i++) {printf("D");}
	for (int i=1;i<=m-1;i++) {printf("R");}
	for (int i=n;i>=1;i--) {
		if ((i&1)==(n&1)) {
			for (int j=m;j>=2;j--) {
				printf("L");
			}
		} else {
			for (int j=1;j<=m-1;j++) {
				printf("R");
			}
		}
		if (i!=1) {printf("U");}
	}
	printf("\n");
	return 0;
}
```


---

## 作者：Andrewzdm (赞：2)

# [CF1327C Game with Chips](https://www.luogu.com.cn/problem/CF1327C)

这里我要感谢下比赛时候的弹窗：
> We don't have to minimize the number of operations in problem C.

所以其实这道题的 $k,sx,sy,fx,fy$ 都用不到！（惊不惊喜意不意外）

由于最大移动次数限制是 $2nm$，所以我们可以把整个棋盘全部走一遍。  

我的做法是这样的：  
首先先从右上角出发，不断向下，走到底再向左走一步，不断向上，走到顶再向左走一步，不断向下……一直走到左下角/左上角。  
然后从左下角/左上角出发，与刚才的做法类似，一直走到最右端。  
（读者可根据代码理解）

把整个棋盘全部走一遍之后，所有的chip一定能够经过目标。

这是因为我们的操作实际上相当于把所有的chip都利用墙壁堆到了左上角或左下角，然后再带着所有的chip遍历棋盘。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, tmp
    cin >> n >> m >> tmp;
    for(int i = 1; i <= 4 * k; i++)
    	cin >> tmp;
    //大大简化了空间复杂度
    string ans = "";
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j < n; j++)
            if((m - i) % 2 == 0)
                ans += 'D';
            else
                ans += 'U';
        if(i != m)
            ans += 'L';
    }
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j < n; j++)
            if(i % 2 == 0)
                ans += 'D';
            else
                ans += 'U';
        if(i != m)
            ans += 'R';
    }
    cout << ans.size() << endl << ans << endl;
    return 0;
}
```
时间复杂度 $O(n \times m)$，空间复杂度 $O(1)$。

---

## 作者：gyh20 (赞：1)

本来以为是道难题，结果发现是道水题。

看到说不需要最优，想一想怎么在 $2nm$ 次内做出来。

很明显，遍历全图只需要 $nm-1$ 次，移到某一个点只需要 $n+m-2$ 次（虽然我用了 $n+m$ 次）。

于是，我们可以将所有物品移到某一个角落，然后遍历全图。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,k,x,lst;
signed main(){
	n=read();m=read();k=read();
	for(re int i=1;i<=k;++i)x=read(),x=read();
	printf("%d\n",n+m+n*m-1);
	for(re int i=1;i<=n;++i){
		putchar('U');
	}
	for(re int i=1;i<=m;++i)putchar('L');
	for(re int i=1;i<=n;++i){
		if(i&1){
			for(re int i=1;i<m;++i)putchar('R');
		}
		else for(re int i=1;i<m;++i)putchar('L');
		if(i!=n)putchar('D');
	}
}
```


---

## 作者：_zhx (赞：0)

## 思路

因为不需要最优，所以在 $2nm$ 次内做出来就行了。

遍历全图只需要 $nm-1$ 次，移到某一个点最多只需要 $n+m-2$ 次。

于是，我们可以将所有物品移到右上角 （$1,1$） 点，然后遍历全图。
 
### 做法


先先从右上角 （$1,1$） 点出发，不断向下，走到底再向左走一步。


再不断向上，走到顶再向左走一步。再不断向下……


一直走到左下角/左上角（$n$ 是奇数时是左下角，$n$ 是偶数时是左上角）。


最后在倒着走回去就行了。


（其实 $k$，$sx$，$sy$，$fx$，$fy$ 根本没有用)

AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t;string s="";
int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=4*k;i++) cin>>t;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if((m-i)%2==0) s+='D';
            else s+='U';
		}
        if(i!=m) s+='L';
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(i%2==0) s+='D';
            else s+='U';
		}
        if(i!=m) s+='R';
    }
    cout<<s.size()<<'\n'<<s;//两行输出
    return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出一个矩形板上的 $k$ 个点.  
每次可以使整体向上下左右移动一个方向（到了边界则不移动）.  
每个点都有一个特殊点，要求每个点都需要经过至少一次自己的特殊点.  
要求在 $2nm$ 的操作次数内满足所有条件.
## $\text{Solution}$
直接全放到左上角然后蛇形扫一遍即可.  
次数是 $n-1+m-1+n\times m-1$.  
甚至不用把数读完，读 $n,m$ 即可.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5e5+100;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
char s[N];
int tot;
int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<m;i++) s[++tot]='L';
  for(int i=1;i<n;i++) s[++tot]='U';
  for(int i=1;i<=n;i++){
    for(int j=1;j<m;j++){
      if(i&1) s[++tot]='R';
      else s[++tot]='L';
    }
    if(i<n) s[++tot]='D';
  }
  printf("%d\n%s\n",tot,s+1);
  return 0;
}
/*

*/

```


---

## 作者：李白莘莘学子 (赞：0)

# 1.题意理解

通过读翻译，我们能够知道：题目提供一个 $n \times m$ 大小的矩阵，矩阵中有一些点，每个点有一个目标位置，你可以对整个矩阵中的点同时进行上下左右移动操作，要求每个点都到或者曾经到过目标位置。


------------

# 2.找思路

### AC方案之外的话：

~~根据题目描述，我突然想到一个题外东西：~~

![](https://cdn.luogu.com.cn/upload/image_hosting/fo6kgfwg.png)

~~虽然移动类似，但是只能帮助理解题意，且对做题没有任何帮助。。~~

开始时，我试着考虑找到一种最短方案，每一个节点的当前位置与目标位置形成的矩形，即是其曼哈顿距离，步数最小，然后搞个什么dp之类的综合考虑每一个矩形对整体步数带来的影响。后来想了半个小时，感觉~~我太菜了~~这种实现不太适合我目前的水平，所以放弃这种思路。

### 开始AC方案:

看到步数限制：$ 2\times n \times m$，翻译过来就是每个节点你最多可以把它围绕着整个矩阵在遍历每一个点的情况下走整整两趟。再看看题目描述，并没有说节点不能和其他节点重合。也就是说，在步数限制内，我们可以：

1.往左移动$ m-1 $步，往上移动$ 
n-1 $步，让全图所有点全部聚集到左上角

2.让背负着所有节点的左上角方块遍历全图

总步数：$ n-1+m-1+n \times m  $= $ n \times m+n+m-2  < 2*n*m $

也就是说，对于不同的数据，你总可以保证步数在$ 2 \times n \times m$内就能实现题目描述，且不用管题目的任何节点位置和目标位置

### Code：

```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
using namespace std;
inline int read()//快读
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int t,n,m,k,sx,sy;
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=k*2;i++)
		sx=read(),sy=read();//然而他们并没有什么用
	printf("%d\n",n+m-2+m*n);//总步数
	for(int i=1;i<m;i++)printf("L");//全部移动到最左列
	for(int i=1;i<n;i++)printf("U");//全部聚集到左上角
	int j=1;
	for(int i=1;i<=n;i++)
	{
		if(i%2==1)//一趟从右来，一趟从左来，因此以行数的奇偶来区别两种情况
		{
			for(j=1;j<m;j++)
				printf("R");
			printf("D");
		}
		if(i%2==0)
		{
			for(j=1;j<m;j++)
				printf("L");
			printf("D");
		}
	}
	cout<<endl;
	return 0;
}
		

```
完结撒花。有问题随时提出。


---

## 作者：do_while_true (赞：0)

## 题目分析

**此题不必最小化步数**

既然不必最小化步数，我们只需要保证每一个芯片都能把这所有的格子都遍历一遍即可，再加上$n,m<=200$，我们甚至不需要输入$k$个芯片。

那么我们怎样实现让所有芯片遍历所有的格子呢？因为一个格子里面可以放多个芯片，所以我们可以把所有芯片利用墙壁把它们堆到一个格子里面，然后再$nm$遍历所有格子即可。

我选择的是把所有芯片堆在左上角，离左上角最远的芯片最远只能在右下角，而右下角到达左上角只需要$(n-1)$个$\texttt{U}$和$(m-1)$个$\texttt{L}$即可。这时我们移动了$(n-1+m-1)$步。

然后遍历所有格子，如果在第$i$行第$j$列。我选择蛇形走，一行一行处理。如果在第奇数行，则输出$(m-1)$个$\texttt{R}$到达右边缘；如果在第偶数行，则输出$(m-1)$个$\texttt{L}$到达左边缘。如果当前在左右两边缘的格子，也就是我们这一行已经走了$(m-1)$步了，我们输出一个$\texttt{D}$。这时我们走了$(n*m)$步。

所以总步数为$(n-1+m-1+n*m)$。

### Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	printf("%d\n",n-1+m-1+n*m);
	for(int i=1;i<n;i++)
		printf("U");
	for(int i=1;i<m;i++)
		printf("L");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<m;j++)
			printf("%c",i%2==1?'R':'L');
		printf("D");
	}
	return 0;
}
```

---

## 作者：dead_X (赞：0)

## 1 题意简述
一堆芯片，可以将所有芯片上下左右移动，如果有一部分芯片移不了则保留原处，芯片位置可以重叠。要求在 $2nm$ 次内让所有芯片都经过一遍互相的位置。
## 2 思路简述
因为有 $2nm$ 次，所以不必写最优策略。

全部挪到右下角，叠起来，然后全部遍历一遍即可。
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;
}a[1000003];
int main()
{
	int n,m,k,x=1,y=1,p,q;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=k; i++) scanf("%d%d",&p,&q);
	for(int i=1; i<=k; i++) scanf("%d%d",&x,&y);
	printf("%d\n",n*m+n+m-2);
	for(int i=1; i<n; i++) printf("D");
	for(int i=1; i<m; i++) printf("R");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<m; j++)if(i%2) printf("L"); else printf("R");
		printf("U");
	}
	return 0;
}
```
## 4 评价
没看懂题目WA了1发。

有一点坑。

---

## 作者：WYXkk (赞：0)

非常神奇的构造题。

既然要求每一个目标都能到达指定格子至少一次，那我们直接让**所有目标遍历过所有格子**即可。

只要把所有目标先移到左上角，然后随便遍历一遍即可。

不过，我们得先看看这个操作需要多少步：$(n-1)+(m-1)+(nm-1)=nm+n+m-3$。

而 $2nm-(nm+n+m-3)=nm-n-m+3=(n-1)(m-1)+2\ge2>0$

所以步数在限制范围内。如此构造即可。

（所以这题的 $k$ 和 $sx,sy,fx,fy$ 没有用处……）

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

int n,m;
int main()
{
	rd(n);rd(m);
	cout<<n*m+n+m-3<<endl;
	F(i,1,n-1) putchar('U');
	F(i,1,m-1) putchar('L');
	F(i,1,n)
	{
		F(j,1,m-1) putchar(i&1?'R':'L');
		if(i!=n) putchar('D');
	}
	return 0;
}
```



---

