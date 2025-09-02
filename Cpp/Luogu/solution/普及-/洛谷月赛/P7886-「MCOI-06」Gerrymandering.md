# 「MCOI-06」Gerrymandering

## 题目描述

给定正整数 $n,m,k$，能否将一个 $n\times m$ 表格染色，使得每一个颜色形成恰好一个连通块，并且每一个连通块大小为 $k$？

如果存在，请构造一个合法方案。

## 说明/提示

#### 样例 1 解释

数据组 3 的合法输出之一：

![](https://cdn.luogu.com.cn/upload/image_hosting/xxqa4azm.png)

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（20 pts）：$k=1$。
 - Subtask 2（30 pts）：$n=1$。
 - Subtask 3（50 pts）：没有特殊限制。

对于 $100\%$ 的数据，$1\le n,m,k,T,\sum nm\le10^{6}$。

## 样例 #1

### 输入

```
3
3 3 3
3 3 33
6 6 4```

### 输出

```
YES
1 1 2
1 2 2
3 3 3
NO
YES
1 1 2 2 3 3
1 2 2 4 4 3
1 5 5 4 6 3
5 5 7 4 6 6
8 7 7 7 9 6
8 8 8 9 9 9```

# 题解

## 作者：C_S_L (赞：4)

考虑如何染色。

我们先把每种颜色依次一行一行染下去，如下图（以样例 $1$ 的第 $3$ 个数据为例）：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/ngjit2qi.png)

此时，$2,5,8$ 三个数字是不联通的。

我们要在保证其他数字仍然联通的情况下使得这三个数字联通。

我们可以使用另一种染色方式：奇数行从前往后染，偶数行从后往前染。这样，若某个数字在同一行里，那么一定联通，若不在一行里，也一定联通，因为相邻两行中的这个数字联通。

如图：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/r41lupzj.png)

注意特判不可行的情况，即 $k\nmid nm$ 。

于是，我们以 $\Theta(\sum nm)$ 的时间复杂度解决了此题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,a[10000][10000];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		if(n*m%k!=0){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		int cnt=k-1;
		for(int i=1;i<=n;++i){
			if(i%2==1){
				for(int j=1;j<=m;++j){
					a[i][j]=(++cnt)/k;
				}
			}
			else{
				for(int j=m;j>=1;--j){
					a[i][j]=(++cnt)/k;
				}
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：3)

#### Description

> 给定一个 $n \times m$ 的矩阵，询问是否能将其分为 $k$ 个大小相同连通块，能的话给出构造方案。

#### Solution

显然，只有 $n\times m$ 整除 $k$ 的时候才有解。

可以考虑如下的构造：

- 从左往右一行构造，直到头；
- 到头之后拐弯，再往回构造；
- 依次类推 ……

不清楚的话可以看一下对于样例 2 下面的构造：

```cpp
1 1 1 1 2 2
3 3 3 3 2 2
4 4 4 4 5 5
6 6 6 6 5 5
7 7 7 7 8 8
9 9 9 9 8 8
```

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[5005][5005];
int change = 1;
int x = 1, y = 1;

int main () {
	int t;
	scanf("%d", &t);
	while (t--) {
		x = 1, y = 1, change = 1;
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		if (n * m % k != 0) {
			puts("NO");
			continue;
		} else puts("YES");
		for (int i = 1; i <= n * m / k; i++)
			for (int j = 1; j <= k; j++) {
				a[x][y] = i;
				y += change;
				if (y > m) x++, y = m, change = -1;
				if (y < 1) x++, y = 1, change = 1;
			}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				printf("%d ", a[i][j]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：言琢დ (赞：3)

首先猜一手结论。

由于 $n\times m\mod k\ne0$ 时最终一定铺不完整，所以一定无解。

那么猜测 $n\times m\mod k=0$ 就一定有解。

---

下面来看看怎么构造解：

$n=1$ 提示了正解。

首先考虑只有一行时：不难发现答案为按顺序这样铺下去：（假设这里 $k=3$）

$$\tt \color{red}aaa\color{blue}bbb\color{red}ccc\color{blue}ddd\color{red}...$$

那么如果我们有很多行，首先的一部分一定是这样铺，那么后面多出来的先铺着。

然后等于还是多了一部分，比如这样：（假如 $n=10,m=3,k=3$）

$$\tt \color{red}aaa\color{blue}bbb\color{red}ccc\color{blue}dd$$

这里的第一行铺好了，还剩下一个 $\tt\color{blue}d$ 没有地方安置。

那么自然想到紧贴下一行安置它。

最终可以得到这个矩阵的解法：

$$\begin{aligned}&\tt\color{red}aaa\color{blue}bbb\color{red}ccc\color{blue}dd\\&\tt\color{blue}h\color{red}ggg\color{blue}fff\color{red}eee\color{blue}d\\&\tt\color{blue}hh\color{red}iii\color{blue}jjj\color{red}kkk\end{aligned}$$

字母的字典序同样代表了正确的铺法中铺的顺序。

最后模拟一下我们得到的答案即可：

```cpp
#include<map>
#include<cstdio>
inline int in();
inline void wr(int);
const int N=(int)1e6+5;
int str[N];
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	register int T=in();
	while(T--){
		register int n=in(),m=in(),k=in();
		if((n*m)%k){
			puts("NO");
			continue;
		}
		puts("YES");
		register int id=1,now=1;
		//下一个要填的格子是第 id 个连通块的第 now 个格子
		for(register int i=1;i<=n;++i,putchar('\n')){
			if(i&1){
				for(register int j=1;j<=m;++j){
					str[j]=id;
					if(++now>k)++id,now=1;
				}
			}
			else{
				for(register int j=m;j>=1;--j){
					str[j]=id;
					if(++now>k)++id,now=1;
				}
			}
			for(register int j=1;j<=m;++j)
				wr(str[j]),putchar(' ');
		}
	}
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：SUNCHAOYI (赞：1)

由题意可知，假设对于一个 $n \times m$ 的表格，我们用了 $p$ 种颜色去染色，显然有 $n \times m = p \times k$。移项可知，$p = n \times m \div k$。又因为 $p$ 是整数，所以需要满足 `n * m % k == 0` 时才有解。

那么对于一张存在解的表格，可以考虑蛇形方阵式的染色。从左上角开始染色，然后向右直到染色至边界，然后向下，再向左至边界……以此类推，直到染完为止。为了放置爆空间，本题解选择逐行输出答案（当然也可以使用 `vector`）。

最后核心代码如下：

```
while (no <= num)
{
	++cnt;
	if (ty == 1)//从左往右
	{
		if (dx <= m) ans[dx] = no,++dx;
		else//整一行已经染色完毕
		{
			for (int i = 1;i <= m;++i) printf ("%d ",ans[i]),ans[i] = 0;
			puts ("");
			ty = 2;dx = m;
			ans[dx] = no;--dx;
		}
	}
	else if (ty == 2)//从右往左
	{
		if (dx >= 1) ans[dx] = no,--dx;
		else
		{
			for (int i = 1;i <= m;++i) printf ("%d ",ans[i]),ans[i] = 0;
			puts ("");
			ty = 1;dx = 1;ans[dx] = no;++dx;
		}
	}
	if (cnt % k == 0) ++no;//一种颜色的连通块大小为 k
}
for (int i = 1;i <= m;++i) printf ("%d ",ans[i]);//最后一行
puts ("");
```

---

## 作者：_lfxxx_ (赞：1)

**题目传送门：[P7886 「MCOI-06」Gerrymandering](https://www.luogu.com.cn/problem/P7886)**
### 题意：
给出 $n,m,k$，问你能不用若干个大小为 $k$ 的连通块**不重不漏**地覆盖一个 $n\times m$ 的矩阵。

若可以，给出方案。
### 思路：
一道构造题。

显然，只有在 $k\mid n\times m$ 的时候，才可能有解。

我们可以一行一行去填连通块，填完这行在逆着填（蛇形）下一行，直到填完。

如样例所给的两个有解的数据，我构造的分别是：
$$
\begin{matrix}
1,1,1\\
2,2,2\\
3,3,3
\end{matrix}
$$
和
$$
\begin{matrix}
1,1,1,1,2,2\\
3,3,3,3,2,2\\
4,4,4,4,5,5\\
6,6,6,6,5,5\\
7,7,7,7,8,8\\
9,9,9,9,8,8
\end{matrix}
$$
显然，这样做是一定有解的，接下来就只是模拟了。

时间复杂度 $\Theta(\sum nm)$
### 代码：
由于是一行一行填，所以只用开个滚动的一维数组就行了。
```cpp
while(T--){
	read(n),read(m),read(k);
	if(n*m%k)
		puts("NO");
	else{
		puts("YES");
        f=1;
		for(int i=1,x=0,t=n*m/k;i<=t;++i){
			for(int j=1;j<=k;++j){
				a[x+=f]=i;
               	if(x==m&&f==1||x==1&&f==-1){
					for(int l=1;l<=m;++l)
						write(a[l]),putchar(' ');
					putchar('\n');
                    x+=f;
					f=-f;
				}
			}
		}
	}
}
```


---

## 作者：EgLund (赞：0)

忠告：构造题一定不要看样例！

------------------------

显然的蛇形填法，只是一点输出的小 trick。

我们设一个数组 `output` 表示行，然后一行一行输出。

为了实现蛇形，讨论行的奇偶性，判断正反输出方式。

注意无解。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m,k;int color,c;
int output[1000009];
signed main()
{
	int T;cin>>T;while(T--)
	{
		cin>>n>>m>>k;
		if(n*m%k)cout<<"NO\n";else
		{
			cout<<"YES\n";
			color=1,c=0;
			for(int i=1;i<=n;i++)
			{
				if(i%2)
				{
					for(int j=1;j<=m;j++)
					{
						output[j]=color;
						if(c==k-1)color++,c=0;
						else c++;
						//cout<<color<<' '<<c<<endl;
					}
					for(int j=1;j<=m;j++)cout<<output[j]<<' ';cout<<endl;
				}
				else
				{
					for(int j=m;j>0;j--)
					{
						output[j]=color;
						if(c==k-1)color++,c=0;
						else c++;
						//cout<<color<<' '<<c<<endl;
					}
					for(int j=1;j<=m;j++)cout<<output[j]<<' ';cout<<endl;
				}
			}
		}
	}
}
```

---

