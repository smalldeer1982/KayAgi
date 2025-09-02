# [ARC139C] One Three Nine

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc139/tasks/arc139_c

正の整数 $ N,M $ が与えられます。

以下を満たす整数の組の列 $ ((X_1,Y_1),(X_2,Y_2),\dots,(X_K,Y_K)) $ を**素晴らしい整数の組の列**ということとします。

- $ 1\ \le\ X_i\ \le\ N $
- $ 1\ \le\ Y_i\ \le\ M $
- $ i\ \neq\ j $ ならば $ X_i+3Y_i\ \neq\ X_j+3Y_j $ かつ $ 3X_i+Y_i\ \neq\ 3X_j+Y_j $

素晴らしい整数の組の列のうち、長さ $ K $ が最大であるものを $ 1 $ 個構築してください。

## 说明/提示

### 制約

- $ 1\ \le\ N,M\ \le\ 10^5 $
- 入力は全て整数である。

### Sample Explanation 1

$ N=3,M=4 $ の時、長さ $ 11 $ 以上の素晴らしい整数の組の列は存在せず、かつ上記の出力は素晴らしい整数の組の列であるためこの出力は正当です。

## 样例 #1

### 输入

```
3 4```

### 输出

```
10
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
3 4```

# 题解

## 作者：EuphoricStar (赞：4)

~~闲话：做这场的 B 用时跟 C 差不多![](//图.tk/6)~~

不会直接构造，因此这是一个无脑做法。

考虑对于 $\forall x \in [1, n], y \in [1, m], (x + 3y, 3x + y)$ 看成一个点，那么选择的 $(x, y)$ 要满足，不存在一行或一列有超过 $1$ 个点。

这启发我们对于合法的点 $(a, b)$，行和列连边，即 $a \to b$，那么就是要构造出这个二分图的一个最大匹配。

考察合法的连边，$a, b$ 应满足什么条件。不难推出：

- $8 \mid (3a - b)$；
- $\max(3a - 8m, \frac{a + 8}{3}) \le b \le \min(3a - 8, \frac{8n + a}{3})$。

所以如果知道了 $a$，那么 $a$ 连出去的 $b$ 模 $8$ 都相等，并且在所有模 $8$ 与它相等的数中是一段区间，并且由式子可得 $a$ 越大这个区间越靠后。

因为 $a$ 有 $O(n + m)$ 个，所以直接枚举 $a$，贪心取出最小的满足要求的 $b$，即可构造。实现时可以开 $8$ 个 `set`。

时间复杂度 $O((n + m) \log (n + m))$。

[code](https://atcoder.jp/contests/arc139/submissions/41643911)

---

## 作者：hhhh531889330 (赞：3)


## 题目大意

给你两个数 $N,M$，现在需要你构造尽可能多的有序数对，设第 $i$ 对数表示为 $(X_i,Y_i)$，则它要满足以下条件
$$\forall 1 \leq i \leq n,1 \leq X_i \leq n,1 \leq Y_i \leq m$$
$$\forall 1 \leq i,j \leq n,i \neq j,3 \times X_i+Y_i \neq 3 \times X_j+Y_j$$
$$\forall 1 \leq i,j \leq n,i \neq j,X_i+3 \times Y_i \neq X_j+3 \times Y_j$$


## 数据范围

$1 \leq n,m \leq 10^5 $

## 解题思路
我们先考虑答案上界。很显然，对于题目给的式子，我们容易将它化成下面这种形式
$$\forall 1 \leq i,j \leq n,i \neq j,\frac{X_i-X_j}{Y_i-Y_j} \neq -3$$
$$\forall 1 \leq i,j \leq n,i \neq j,\frac{Y_i-Y_j}{X_i-X_j} \neq -3$$
也就是占据了两条直线，如果我们将 $n,m$ 互换，对答案显然没有任何影响，因此，我们不妨假设 $n\leq m$ ，容易发现这两条直线具有对称性，因此 $3X_i+Y_i$ 与 $X_i+3Y_i$是等价的。

观察 $3X_i+Y_i$ 的性质，不难发现有 $4\leq 3X_i+Y_i\leq3n+m (n\leq m)$，因此，答案有上界 $3n+m-3$，但并非所有情况下都能取到这一上界，当 $n=m$ 且 $n$ 为偶数时，可以发现答案要减一。
实际上，当 $n=m$ 且 $2|n$ 时，选择的答案等价于以下这个问题的答案

我们以 $(1,3)$ 为起点，不断重复以下四种操作（可以暂时走出范围）

- 从 $(x,y)$ 移动到 $(x-1,y+3)$
- 从 $(x,y)$ 移动到 $(x-3,y+1)$
- 从 $(x,y)$ 移动到 $(x+1,y-3)$
- 从 $(x,y)$ 移动到 $(x+3,y-1)$

当 $n\neq m$ 或 $n,m$ 中有奇数的时候，$3X+Y$的值和$3Y+X$的值均有$\frac{n}{2}$种，但 $n=m$ 且 $2|n$ 时，虽然 $3X+Y$ 的值有 $\frac{n}{2}$ 种，但 $3Y+X$ 的值却只有$\frac{n}{2}-1$ 种，因此答案的上界应为 $3n+m-4$ 种。

此题的方案构造有多种方案，这里提供其中一种：
```
oooxxxxxxxxxxxx
oooxxxxxxxxxxxx
oooooxxxxxxxxxx
xxoooxxxxxxxxxx
xxoooooxxxxxxxx
xxxxoooxxxxxxxx
xxxxooooooooooo
```
其中 $o$ 为选择的位置，不难发现如图所示的构造能够满足答案上限。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,k,l,o,p;
inline int read()
{
	int f(1),x(0);
	char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f*=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return f*x;
}
int ans[500005][2],num;
inline void print(int x,int y,bool zl)
{
	if (x>n||y>m) return ;
	if (zl) swap(x,y);
	ans[++num][0]=x,ans[num][1]=y;
}
inline void bxl()
{
	printf("%d\n",num);
	for (i=1;i<=num;i++) printf("%d %d\n",ans[i][0],ans[i][1]);
}
int main()
{
	n=read(),m=read();
	if (n>m) swap(n,m),o=1;
	if (m<=3) {for (i=1;i<=n;i++) for (j=1;j<=m;j++) print(i,j,o); bxl(); return 0;}
	if (n<=3) { for (i=1;i<n;i++) for (j=1;j<=3;j++) print(i,j,o); for (j=1;j<=m;j++) print(n,j,o); bxl(); return 0; }
	for (i=2,print(1,1,o),print(1,2,o),print(1,3,o),j=1;i<=n;i+=2,j+=2)
	{
		print(i,j,o),print(i,j+1,o),print(i,j+2,o);
		print(i+1,j,o),print(i+1,j+1,o),print(i+1,j+2,o),print(i+1,j+3,o),print(i+1,j+4,o);
	}
	i-=2,j-=2;
	if (i==n-1) ++i,j+=2;
	j+=3;
	for (j;j<=m;++j) print(n,j,o);
	bxl();
}
```

---

## 作者：WRuperD (赞：1)

怎么没有官方题解做法，这就来搬运一下，感觉非常 Edu。

首先假设 $n \leq m$。

发现 $3X_i+Y_i$ 的最小值为 4 且最大值为 $3n+m$。于是我们得到了一个答案的上界为 $3n+m-3$。怎么构造呢？

考虑我们每选一对数相当于在棋盘上面放一枚棋子。我们最终希望从左上角 $(1,1)$ 走到右下角 $(n,m)$。而每一步我们都希望 $3X_i+Y_i$ 刚好增加 $1$。我们可以通过这两种走法轻易得到这样的一条路径：

- 从 $(i,j)$ 走到 $(i,j+1)$。
- 从 $(i,j)$ 走到 $(i + 1,j - 2)$。

注意，这个移动还是有一定限制的，就是我们不能走到某个已走格子 $(i,j)$ 的 $(i + 3, j - 1)$。

所以对于 $n$ 为奇数或者 $n \neq m$ 的情况，显然我们有如下顶满上届的答案：


```
oooxxxxxxxxxxxx
oooxxxxxxxxxxxx
oooooxxxxxxxxxx
xxoooxxxxxxxxxx
xxoooooxxxxxxxx
xxxxoooxxxxxxxx
xxxxooooooooooo
```

但是这个方法在 $n=m$ 且 $2 \mid n$ 的情况失效了。


```
oooxxx
oooxxx
ooooox
xxooox
xxoooo
xxxxoo
```

发现这样子是 $3n+m-4$ 的。

官方题解中归纳证明了事实上在这种情况下答案的上界确实就在这了。

做完了。


```cpp
// Problem: [ARC139C] One Three Nine
// URL: https://www.luogu.com.cn/problem/AT_arc139_c
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
map <pair<int,int>, bool> mp;

void solve(){
	int n = read(), m = read();
	bool fl = 0;
	write(3 * n + m - 3), endl;
	if(n > m)	swap(n, m), fl = 1;	
	vector <pair<int,int>> ans;
	int nowj = 1;
	for(int i = 1; i <= n; i += 2){
		for(int nowi = i; nowi <= i + 2; nowi++){
			for(int j = nowj; j <= nowj + 2; j++){
				if(nowi <= n and j <= m and !mp.count(make_pair(nowi, j))){
					if(!fl)	ans.pb(make_pair(nowi, j));
					else ans.pb(make_pair(j, nowi));
					mp[make_pair(nowi, j)] = 1;
				}
			}
		}
		nowj += 2;
	}
	for(int i = nowj; i <= m; i++){
		if(!mp.count(make_pair(n, i))){
			if(!fl)	ans.pb(make_pair(n, i));
			else ans.pb(make_pair(i, n));
		}
	}
	write(ans.size()), endl;
	for(int i = 0; i < ans.size(); i++){
		write(ans[i].first), put(), write(ans[i].second), endl;
	}
	return ;
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：Inui_Sana (赞：1)

会正解做法之后还以为 `10 10` 答案是 $37$……

钦定 $n\le m$，从 $3x+y$ 与 $x+3y$ 的匹配的角度考虑。考虑对于一对 $x,y$，我们保持 $3x+y$ 不变，$x\to x-1$，$x+3y$ 如何变化。发现 $x+3y\to (x-1)+3(y+3)=x+3y+8$。于是对于一个 $3x+y=p$，符合条件的 $x+3y=q=8k+z$，$z$ 为定值且 $k$ 为一个区间。

再进一步，设 $k\in[l,r]$，容易发现对于 $3x'+y'=p-8$，$z$ 不变，但是 $l,r$ 变化。具体地 $l'\le l,r'\le r$。则贪心地想，从小到大枚举 $p$，每个 $3x+y$ 都选择最小的满足条件的 $k$（即选择能匹配的最小的 $x+3y$），这样一定是不优的。开个数组对每个 $z$ 记录当前已经选了的最大的 $k$，从前往后扫 $p$，从 $k+1$ 开始判断是否可行。

由于 $\forall p'\le p,l'\le l,r'\le r$ 所以这个贪心是正确的。

code：

```cpp
int n,m;
int b[12]={0,0,0,0,4,7,10,5,8,11,6,9};
void Yorushika(){
	scanf("%d%d",&n,&m);
	bool fl=0;
	if(n<m){
		swap(n,m);
		fl=1;
	}
	vector<pii> ans;
	rep(i,4,m*3+n){
		int p=(i-4)%8+4;
		int &j=b[p];
		int x=((i+j)/4-(i-j)/2)/2,y=(i-x)/3;
		while(x<1||y>m){
			j+=8;
			x=((i+j)/4-(i-j)/2)/2,y=(i-x)/3;
		}
		if(x<=n&&y>=1){
			if(fl){
				swap(x,y);
			}
			ans.eb(x,y);
		}
		j+=8;
	}
	printf("%d\n",ans.size());
	for(auto [i,j]:ans){
		printf("%d %d\n",i,j);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

