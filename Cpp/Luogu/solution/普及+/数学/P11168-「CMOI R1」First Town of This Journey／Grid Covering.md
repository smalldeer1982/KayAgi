# 「CMOI R1」First Town of This Journey／Grid Covering

## 题目背景

![Link:First Town of This Journey](bilibili:BV1ka411G78Y)$\small\color{white}/10^{\text{th}}\text{Problem by AtC}.$

本题中认为两个点间的连线为以这两个点作为端点的线段。

## 题目描述

$\text{BiOI}$ 有一个 $n$ 行 $m$ 列的网格。你需要选出最少的格点，使得任意两个**不同的**格点的连线至少经过一个被选中的点（这里我们认为一条线段**经过了**它的两个端点）。

$\text{CmOI}$ 觉得这个问题太简单了，所以他会另外给定 $a,b,x$，表示第 $a$ 行第 $b$ 列的格点必须被或不被选中：

* $x=0$ 时该格点不可选中；
* $x=1$ 时该格点必须选中。

你只需要求出最少选出几个格点，$\text{BiOI}$ 和 $\text{CmOI}$ 会把网格和你的答案一起丢给 $\text{ArCu}$ 让他构造方案。

## 说明/提示

$\text{Details about Subtasks}:$

所有数据满足 $1\leq n,m<2^{32},1\leq a\leq n,1\leq b\leq m,0\leq x\leq 1$。

* $\text{Subtask 1}:1\leq n,m\leq 10,\text{5 points.}$
* $\text{Subtask 2}:x=0,\text{25 points}.$
* $\text{Subtask 3}:x=1,\text{30 points.}$
* $\text{Subtask 4}:\text{40 points.}$

$\text{Sample Explanation}:$

* $\text{Sample 1}:$

此时网格有 $3$ 行 $3$ 列，要求第 $2$ 行第 $2$ 列的格点必须被选中。

最优方案如下（黑色是被选中的格点）：

![010111010](https://cdn.luogu.com.cn/upload/image_hosting/qltw919n.png)

注意以下方案并不合法：

* 图中给出了两种方法使得两个不同的格点间连线不经过黑点；
* 第二行第二列的格点没有被选中，输入中要求这个格点必须被选中。

![011100011](https://cdn.luogu.com.cn/upload/image_hosting/egvtdeq2.png)

以及我们认为端点在黑点上算是经过黑点。也就是说下面的这种连线经过了一个黑色格点。

![011110011](https://cdn.luogu.com.cn/upload/image_hosting/zk2d5ou2.png)

## 样例 #1

### 输入

```
3 3
2 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
2 5
1 3 0```

### 输出

```
7```

## 样例 #3

### 输入

```
4 5
3 2 0```

### 输出

```
16```

# 题解

## 作者：Grand_Dawn (赞：8)

~~虽然这篇题解很长，但大部分都在证明简单的思路为什么是对的。~~

以下记黑点是被选中的格点，白点为未被选中的格点。

### 无限制条件

当不存在某个格点必须被选中/不选中时，答案为 $nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor$。考虑以下分析过程：

考虑相邻两行中各选取一个点，会有 $m^2$ 条连线，这些连线仅经过两个端点。因此，相邻两行中必须存在一行全部被染黑。对于列同理。

在 $n$ 行中，需要满足以上条件则最少需要 $\left\lfloor\frac{n}{2}\right\rfloor$ 行被染黑。方案为第 $2,4,6,...,2\left\lfloor\frac{n}{2}\right\rfloor$ 行被染黑。

而无论选取哪些行被涂黑后，每一列剩余的白格子数量相等，故可以用同样的方式选取第 $2,4,6,...,2\left\lfloor\frac{m}{2}\right\rfloor$ 染黑。

这样选取后时满足“相邻两行中必须存在一行全部被染黑”的最优解之一。以下证明这种选取方法是正确的：

由于所有的第 $2i$ 行，第 $2j$ 列被染黑，故此图内一个格子 $(x,y)$ 为白色当且仅当 $x\equiv y\equiv 1\pmod 2$。

如果连线端点处存在黑点则条件成立。则考虑任意两个不同的白点 $(2x_1+1,2y_1+1)$ 和 $(2x_2+1,2y_2+1)$ 的连线上：

+ 考虑中点 $(x_1+x_2+1,y_1+y_2+1)$，如果此点为黑色，则该连线上存在黑点。

+ 如果中点 $(x_1+x_2+1,y_1+y_2+1)$ 为白色点，则满足 $x_1+x_2+1=2x_3+1,y_1+y_2+1=2y_3+1$，考虑使用白点 $(2x_1+1,2y_1+1)$ 和 $(x_1+x_2+1,y_1+y_2+1)$ 递归调用此过程。

显然此过程中，中点不会落在端点上，故此过程一定会结束，即存在黑色点在连线上。

由以上过程，则任意两个不同的格点的连线上至少有一个黑点。此时选取的黑色点个数为 $\left\lfloor\frac{n}{2}\right\rfloor m+n\left\lfloor\frac{m}{2}\right\rfloor-\left\lfloor\frac{n}{2}\right\rfloor\left\lfloor\frac{m}{2}\right\rfloor=nm-(n-\left\lfloor\frac{n}{2}\right\rfloor)(m-\left\lfloor\frac{n}{2}\right\rfloor)=nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor$。

### 限制条件为黑点

考虑无限制条件的方案，增加限定点为黑色一定是一个合法方案，则答案 $ans$ 一定满足 $nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor\leq ans\leq nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor+1$。

则实际上仅需要考虑是否存在无限制条件的解 $(a,b)$ 被涂黑：

分别考虑行和列，是同理的。以下考虑行：

+ 如果 $n\equiv 1\pmod 2$，则考虑相邻两行的关系共有 $n-1$ 对，而每涂黑一行仅会至多减少 $2$ 对限制。故最小值为 $\frac{n-1}{2}$ 行被涂黑。此时涂黑每一行都必须减少恰好 $2$ 对限制。因此必须填涂第 $2i(1\le i\le \left\lfloor\frac{n}{2}\right\rfloor)$ 行。

+ 如果 $n\equiv 0\pmod 2$，且 $a\equiv 0\pmod 2$，则由无限制条件的方案，该点已被涂黑。

+ 如果 $n\equiv 0\pmod 2$，且 $a\equiv 1\pmod 2$。由于 $n$ 行 $m$ 列的网格是上下对称的，则 $(a,b)$ 与 $(n+1-a,b)$ 的答案是相同的。而 $n+1-a\equiv 0\pmod 2$，故该点也可以被涂黑。

综上条件，再对于行和列的条件再取或，则不存在存在无限制条件的解 $(a,b)$ 被涂黑当且仅当 $n\equiv m\equiv a\equiv b\equiv 1\pmod 2$。

因此此时答案为 $\left\{\begin{aligned}&nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor+1,n\equiv m\equiv a\equiv b\equiv 1\pmod 2\\&nm-\left\lfloor\frac{n+1}{2}\right\rfloor\left\lfloor\frac{m+1}{2}\right\rfloor\quad\ \ \ ,\text{otherwise.}\end{aligned}\right.$。

### 限制条件为白点

考虑如果 $(a,b)$ 必须强制被涂白，则由条件“相邻两行中必须存在一行全部被染黑”，第 $a-1$ 行和第 $a+1$ 行必须全部被涂黑。第 $b-1$ 列和第 $b+1$ 列必须全部被涂黑。

考虑被涂黑行列夹着的四个区域 $\left\{\begin{aligned}&x=a\\&y<b-1\end{aligned}\right.$ $\left\{\begin{aligned}&x=a\\&y>b+1\end{aligned}\right.$ $\left\{\begin{aligned}&x<a-1\\&y=b\end{aligned}\right.$ $\left\{\begin{aligned}&x>a+1\\&y=b\end{aligned}\right.$ 和剩下 $4$ 个区域 $\left\{\begin{aligned}&x<a-1\\&y<b-1\end{aligned}\right.$ $\left\{\begin{aligned}&x<a-1\\&y>b+1\end{aligned}\right.$ $\left\{\begin{aligned}&x>a+1\\&y>b+1\end{aligned}\right.$ $\left\{\begin{aligned}&x>a+1\\&y<b-1\end{aligned}\right.$，分别以 $(a,b)$ 点（沿四个方向）向外为正方向参考无限制条件的方案构造，依然是满足条件“相邻两行中必须存在一行全部被染黑”的最优解。

此时的构造 $(x,y)$ 为白点当且仅当 $x\equiv a\pmod 2,y\equiv b\pmod 2$。使用类似前文的证明可得构造是正确的。

化简后答案为 $nm-\left\lfloor\frac{n+(a\bmod 2)}{2}\right\rfloor\left\lfloor\frac{m+(b\bmod 2)}{2}\right\rfloor$。

---

## 作者：RainySoul (赞：5)

### 题目大意

转化一下，这题就相当于：

你需要在一个 $n \times m$ 的网格图中选中若干个点涂黑，使得任意两点之间的连线都要经过至少一个黑点（这两点有一个是黑点也算）。

告诉你某个点必须涂黑或者必须不涂黑，求最少需要选多少个点涂黑。

### 解法

为了方便讨论，未涂色的点叫做白点。

你对图上的一个白点单独考虑一下，很容易想到它周围的一圈是一定不能再出现一个白点的，否则把这两个白点一连起来就是一个不合法情况，所以它是要被一圈黑点给包围起来的（边界也可以看作黑点）。

就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9azfdqrv.png)

或是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/gr9wl97o.png)

在这种情况下的最优构造是什么？我想要让白点尽可能多地出现，那么每两个离得最近白点之间都只隔了一个黑点一定是更优的对吧，这也可以很轻松地构造出。白点的上、下、左、右四个方向接下来都是黑、白、黑、白…… 就可以了。

最终效果图大概是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/1gyfelbo.png)

---

接下来看题目，当 $x=0$ 的时候就是告诉了你一个白点的位置了，你可以直接推出其他白点的位置。

```
int solve(int x,int y){
	sx=x%2,sy=y%2;
	if(sx==0)sx=2;
	if(sy==0)sy=2;//(sx,sy)就是左上角第一个白点的坐标
	return n*m-((n-sx+2)/2)*((m-sy+2)/2);
}
```

---

当 $x=1$ 的时候给你留了一些构造的空间，大部分情况下你是让黑点老老实实地待在自己的位置上，但是，存在一些情况下你输入的那个坐标 $(a,b)$ 是可以占用一个白点的位置的。

这么说可能不太清楚，结合图来看一下。

假设是一个 $3 \times 3$ 的矩阵，$(1,1)$ 这个位置必须是黑点。

![](https://cdn.luogu.com.cn/upload/image_hosting/0hxrx6oq.png)

这样构造，尽管 $(1,1)$ 这个黑点占用了一个白点的位置，它仍是最优的。

仅有 $n,m,a,b$ 均为奇的时候你才会迫不得已掏出上面那种构造。

其余时候，我们知道如果可以的话我们把左上角白色起始点位置放在 $(1,1)$ 答案一定是不劣的。你是可以小改起始点位置得到和起始点在 $(1,1)$ 一样的答案的，所以你就把起始点当作 $(1,1)$ 直接算。

然后这题你就做完了。

最后还有一个细节问题，毒瘤的 $n$ 和 $m$ 都是 $2^{32}$ 级别的，计算过程中的直接相乘就爆 `long long` 了，而 `unsigned long long` 没被爆掉，不放心的就开 `__int128`。

AC code:

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int sx,sy,n,m,x,y,op,minn;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
inline void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
	return;
}
int solve(int x,int y){
	sx=x%2,sy=y%2;
	if(sx==0)sx=2;
	if(sy==0)sy=2;
	return n*m-((n-sx+2)/2)*((m-sy+2)/2);
}
signed main(){
	n=read(),m=read(),x=read(),y=read(),op=read();
	if(op==0)write(solve(x,y));
	else if(op==1){
		if(n%2==1&&m%2==1&&x%2==1&&y%2==1)minn++;
		minn+=n*m-((n+1)/2)*((m+1)/2);
		write(minn);
	}
	return 0;
}
```

---

## 作者：晴空一鹤 (赞：4)

本题最大难点在于要开 `unsigned long long`。

要求选的黑点最少，相当于要求选的白点最多。

考虑一个白点选了之后对问题有什么影响，显然与他挨着的行与列就不能选，否则连起来是不会经过黑点的。

然后就很容易想出构造方案，选择所有 $(i,j)(i \equiv 1 \pmod 2,j \equiv 1 \pmod 2)$，画个图可以发现这显然是满足要求的。

接下来考虑指定颜色：

- 指定一个点为黑点，如果它不在我们的初始方案上就不用管，如果在，考虑能否将初始方案向右或向下平移，不能答案要加 $1$。

- 指定一个点为白点，如果它在初始方案上就不用管，否则将初始方案略微平移过来即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
ll n,m,a,b,x,ans,yyn,ym;
int main(){

  cin>>n>>m>>a>>b>>x;yyn=n,ym=m;
  if(x==0&&a%2==0)n--;
  if(x==0&&b%2==0)m--;
  if(x==1&&(a%2==1&&b%2==1&&n%2==1&&m%2==1))ans--;
  ans+=((n+1)/2)*((m+1)/2);
  cout<<yyn*ym-ans<<"\n";
}
```

---

## 作者：fanhuining (赞：3)

_~~先讲句题外话：本蒟蒻第一次发题解，求通过！！！~~_ 

## 题目大意

有一个   $n × m $ 的网格，其中我们会选出若干个点，必须满足以下条件：

1. $x=0$  时，第 $ a$  行第  $b$  列的格点不可选中。
2.  $x=1$  时，第  $a$  行第 $ b $ 列的格点必须选中。
3.  将任意两个点相连一定会经过一个被选中的点（两端也算被经过）。

## 题目分析

可以发现，当两个点都没有被选中时，如果它们所连成的线没有经过被选中的点时，这个组合是不行的。于是，我们发现，当一个矩阵被下图的图形尽可能最多地被覆盖时，这个矩阵是合法的且它是被选中的点最少的。

我拿一个 $ 5×5 $ 的表格给大家一下：
```cpp
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
```
所以，矩阵中如果一个点的横，纵坐标都是奇数，它就是一个白点。那么，如果题目中要求必须选中或不可选中的点正好对应，那么，答案就是 $ans=(n/2)×(m/2)$,（这里的除是向下整除），如果不对应：

  1.第一种可能：我们把白点除了黑点必选点外，其他的正常放。适用于 $ n,m $ 都为奇数时。

  2.第二种可能，我们把白点在原来放置的基础全部向左移，即  $(x,y)$  移至  $(x,y+1)$ 。适用于  $m$  等于偶数的情况。

  3.第三种可能，我们把白点在原来放置的基础全部向下移，即 $(x,y)$  移至 $ (x+1,y)$ 。适用于  $n$  等于偶数的情况。

## 代码（code)：

```cpp
#include<bits/stdc++.h> //万能头小宝贝
using namespace std;
unsigned long long n, m, a, b, x; //不开unsigned会爆

int main(){
	cin >> n >> m;
	cin >> a >> b >> x;
	unsigned long long a1 = (n - 1) / 2 + 1, a2 = (m - 1) / 2 + 1;
	if(x == 1){
		if(a % 2 == 1 && b % 2 == 1){
			if(n % 2 == 1 && m % 2 == 1) cout << n * m - a1 * a2 + 1;
			else cout << n * m - a1 * a2;
		}
		else cout << n * m - a1 * a2;
	}
	else{
		if(a % 2 == 1 && b % 2 == 1){
			cout << n * m - a1 * a2;
		}
		if(a % 2 == 1 && b % 2 == 0){
			if(m % 2 == 1) cout << n * m - a1 * a2 + a1;
			else cout << n * m - a1 * a2;
		}
		if(a % 2 == 0 && b % 2 == 1){
			if(n % 2 == 1) cout << n * m - a1 * a2 + a2;
			else cout << n * m - a1 * a2;
		}
		if(a % 2 == 0 && b % 2==0){
			if(n % 2 == 1){
				if(m % 2 == 1) cout << n * m - a1 * a2 + a1 + a2 - 1;
				else cout << n * m - a1 * a2 + a2;
			}
			else if(m % 2 == 1) cout << n * m - a1 * a2 + a1;
			else cout << n * m - a1 * a2;
		}
	}
    return 0; //华丽丽地结束
}
```
 _写了这么多，就点个赞呗！
此外，如有不足，欢迎大佬们来点评！！！_

---

## 作者：jnxx_liuchenxiang (赞：2)

# 题解 P11168
## 题意
有一个 $n \times 
m$ 的网格，让你选出的最少格点，使任意两个**不同的**格点至少经过一个被选中的格点（这里我们认为一条线段**经过**了它的两个端点）。

此外，题目给定 $a,b,x$,当
- $x = 0$ 时，第 $a$ 行第 $b$ 列的格点不可选中。
- $x = 1$ 时，第 $a$ 行第 $b$ 列的格点必须选中。

## 分析
可以发现，当两个点都没有被选中时，如果它们所连成的线没有经过被选中的点时，这个组合是不行的。于是，我们发现，当一个矩阵被下图的图形尽可能最多地被覆盖时，这个矩阵是合法的且它是被选中的点最少的（例如下右方的那个矩阵）。
![图1.1](https://cdn.luogu.com.cn/upload/image_hosting/qltw919n.png)       ![图1.2](https://cdn.luogu.com.cn/upload/image_hosting/xkc2wj50.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以，矩阵中如果一个点的横，纵坐标都是奇数，它就是一个白点。那么，如果题目中要求必须选中或不可选中的点正好对应，那么，答案就是 $ans = (n / 2) \times (m / 2)$ （这里的除是向下整除），如果不对应：
- $ x = 0$
   - 要求的点横坐标 $a$ 为偶数，纵坐标 $b$ 为奇数。
      - $n$ 为偶数时（即有一列余量）,答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2}$。
      - $n$ 为奇数时，答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2} - \frac{m+1}{2}$。
   - 要求的点横坐标 $a$ 为奇数，纵坐标 $b$ 为偶数。
      - $m$ 为偶数时（即有一行余量），答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2}$。
      - $m$ 为奇数时，答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2} - \frac{n+1}{2}$。
   - 要求的点横坐标 $a$ 为偶数，纵坐标 $b$ 也为偶数
      - 当 $n$ 为偶数，且 $m$ 为偶数时，答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2}$。
      - 否则，答案为 $\frac{n + 1}{2} \times \frac{m + 1}{2} - \frac{n+1}{2} - \frac{m+1}{2} + 1$。

( $x = 1$ 时也一样，只不过没余量时只需要减 $1$ ，不用减一整行或一整列，其余细节看代码。)

## 完整代码
注意本题数据量很大，要开 unsigned long long！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,m,a,b,x;
//不开unsigned会爆

int main(){
	cin>>n>>m;
	cin>>a>>b>>x;
	unsigned long long a1=(n-1)/2+1,a2=(m-1)/2+1;
	if(x==1){
		if(a%2==1 && b%2==1){
			if(n%2==1 && m%2==1)cout<<n*m-a1*a2+1;
			else cout<<n*m-a1*a2;
		}
		else cout<<n*m-a1*a2;
	}
	else{
		if(a%2==1 && b%2==1){
			cout<<n*m-a1*a2;
		}
		if(a%2==1 && b%2==0){
			if(m%2==1)cout<<n*m-a1*a2+a1;
			else cout<<n*m-a1*a2;
		}
		if(a%2==0 && b%2==1){
			if(n%2==1)cout<<n*m-a1*a2+a2;
			else cout<<n*m-a1*a2;
		}
		if(a%2==0 && b%2==0){
			if(n%2==1){
				if(m%2==1)cout<<n*m-a1*a2+a1+a2-1;
				else cout<<n*m-a1*a2+a2;
			}
			else if(m%2==1)cout<<n*m-a1*a2+a1;
			else cout<<n*m-a1*a2;
		}
	}
    return 0;
}
//时间复杂度显然是 O(1)
```

完结撒花！！!

若有不完善的地方还请各位大佬指出！！！

---

## 作者：ELECTRODE_kaf (赞：1)

正难则反，我们考虑最多选取多少白点。

在选取某个点作为白点后，它上左下右四条直线就都不能选：

![](https://cdn.luogu.com.cn/upload/image_hosting/lyb60coy.png)

因为与这些点的连线不经过其它格点。

忽略题目的特殊要求，按照这种想法构造一组解（$1$ 为白点）：

|1|0|1|0|1|
|:-:|:-:|:-:|:-:|:-:|
|0|0|0|0|0|
|1|0|1|0|1|
|0|0|0|0|0|
|1|0|1|0|1|

如果指定一个白点作为黑点：

如果行数和列数中有一个是偶数，那么就整体向下/右平移一格。

如果行数列数均为奇数，那就舍弃这个白点。

如果指定一个黑点作为白点：

同样选择整体向那个方向平移，注意平移可能使白点减少一行或一列，输出答案时特判即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define rep(i,x,y) for(int i=x;i<=y;i++)

ull n,m,x,y,ty,ans,_n,_m;

int main(){
	cin>>n>>m>>x>>y>>ty;
	_n=n;
	_m=m;	
	
	if(ty==0&&x%2==0) n--;
	
	if(ty==0&&y%2==0) m--;
	
	if(ty==1&&x%2&&y%2&&n%2&&m%2) ans--;
	
	ans+=((n+1)>>1)*((m+1)>>1);
	cout<<_n*_m-ans;
}
```

---

## 作者：jiangyunuo (赞：1)

第一篇通过的绿题，纪念一下。

### 意思：

有一个 $n \times m$ 的网格，其中我们会选出若干个点，必须满足以下两个条件：

1. 将任意两个点相连一定会经过一个被选中的点（两端也算被经过）。
2. 如果 $x=0$ 那么 $(a,b)$ 必须不被选上；如果 $x=0$ 那么 $(a,b)$ 必须被选上。

求最少需要选出的点的数量。

### 思路：
（我们用 $0$ 表示没选出，$1$ 表示选出，下文中白点指未选中的点，黑点指选中的点）当我们反复研究几个例子和思考后我们发现，当一个白点处在 $(x,y)$ 时，那么要想最优解 $(x+2,y)$、$(x-2,y)$、$(x,y+2)$、$(x,y-2)$ 都会是白点（除特殊情况，就是指定那个点选不选上），这对于每个白点都是如此，因为两个白点中间必然有一个黑点，这样也能保证写这也会包含黑点。

我们拿一个 $5 \times 5$ 的表格表示一下：

```
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
```

显然，在不考虑第二个情况下，我们将第一个白点放在 $(1,1)$ 上，接下来正常放，按上面最优解的规律。求白点数量代码：`n*m-((n+1)/2)*((m+1)/2)`。

如果想满足第二个条件，还得继续想。

如果 $x=0$ 那么就很简单了，所有点的位置已经固定了：

1. $m,n$ 都为奇数时，那么代码：`n*m-((n+1)/2)*((m+1)/2)`。
2. $m$ 为奇数时，$n$ 为偶数时，那么代码：`n*m-(n/2)*((m+1)/2)`。
3. $m$ 为偶数时，$n$ 为奇数时，那么代码：`n*m-((n+1)/2)*(m/2)`。
4. $m,n$ 都为偶数时，那么代码：`n*m-(n/2)*(m/2)`。

但是如果 $x=1$ ，且必选点在原本白点的位置，那就要花点小心思了（反之，没影响，正常算），有三种情况（默认 $a=b=1$），第一种是如一下这个 $5 \times 5$ 得看一看了：

```
1 1 0 1 0
1 1 1 1 1
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
```

如果是 $5 \times 6$：

```
1 0 1 0 1 0
1 1 1 1 1 1
1 0 1 0 1 0
1 1 1 1 1 1
1 0 1 0 1 0
```

如果是 $6 \times 5$：

```
1 1 1 1 1
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
1 1 1 1 1
0 1 0 1 0
```

对于这三种可能，我们需要选出最优的一项。

1. 第一种可能：我们把白点除了黑点必选点外，其他的正常放。适用于 $n,m$ 都为奇数时。代码：`n*m-max(((n+1)/2)*((m+1)/2)-1`。
2. 第二种可能，我们把白点在原来放置的基础全部向左移，即 $(x,y)$ 移至 $(x,y+1)$。适用于 $m$ 等于偶数的情况。代码：`((n+1)/2)*(m/2)`。
3. 第三种可能，我们把白点在原来放置的基础全部向下移，即 $(x,y)$ 移至 $(x+1,y)$。适用于 $n$ 等于偶数的情况。代码：`(n/2)*((m+1)/2)`。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	unsigned long long n,m;
	long long a,b;
	bool x;
	cin>>n>>m>>a>>b>>x;
	if(x){
		if(a%2&&b%2)cout<<n*m-max(((n+1)/2)*((m+1)/2)-1,max((n/2)*((m+1)/2),((n+1)/2)*(m/2)))<<endl;    //如果必选点在本该是白点的地方，要在三种情况中选最优解。
		else cout<<n*m-((n+1)/2)*((m+1)/2)<<endl;   //求其余情况的答案。
	}
	else{
		if(a%2){
			if(b%2)cout<<n*m-((n+1)/2)*((m+1)/2)<<endl;
			else cout<<n*m-((n+1)/2)*(m/2)<<endl;
		}
		else{
			if(b%2)cout<<n*m-(n/2)*((m+1)/2)<<endl;
			else cout<<n*m-(n/2)*(m/2)<<endl;
		}
	}    //根据必不选点的位置求答案。
	return 0;
}
```

注：求黑点时我给必选点把原本白点位置占掉的情况时，用了 `max` 求结果，但实际上可以一种种情况判断过去。

---

## 作者：kuaiCreator (赞：1)

# P11168 「CMOI R1」First Town of This Journey／Grid Covering 题解
## 题目大意
在 $n\times m$ 的网格中选任意两个交点连线，求最少有几个被选中的点，保证连线的上必须有一个被选中的点，并且要求其中某个点的状态必为选中或不选中。

以下将被选中的点称为黑点，未被选中的点称为白点。
## 解题思路
1、考虑如果无特殊点时，要保证网格中任意两点连线必经过至少一个黑点，显然应该是一个白点被黑点包围，证明的话考虑以任意点为起点的斜率方向证明。情况类似下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/cweuk5xg.png)


2、考虑加入特殊点时
- 若行，列，特殊点坐标 $(x,y)$ 不都为奇数时，情况如图中一二三四五六七所示应保证黑点摆放，尽量占最少的行数和列数，因此如果行或者列的数量为奇数时，一半向下取整的行或列摆满黑色的点，特殊位置的黑点或者白点为其中某点。
 ![](https://cdn.luogu.com.cn/upload/image_hosting/w2v42im1.png)


- 若行，列，特殊点坐标 $(x,y)$ 都为奇数时，图八看起来像是最优的，实则存在更优的图九，即当从图七中将特殊点选出改成黑点即可。这是本题需要特别注意的坑点。如果没想到这个点只有 $65$ 分，子任务一和子任务三会错误。

注意：题目中 $1\le n,m\le 2^{32}$ 需要用 `unsigned long long` 或 `__int128`。


分类讨论：
1. $x=0$ 时总行数行 $n$ 为奇数且特定位置行坐标 $a$ 也是奇数，白点的总行数为 $n/2+1$ ,否则为 $n/2$ 的,列同理。白点总数为行和列的乘积，黑点总数为全部点的总数减去白点总数。
2.  $x=1$ 时考虑行 $n,m,a,b$ 同时为奇数时，仅需要把 $(a,b)$ 改为黑点如图五。否则和之前的情况相同。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
int main() {
	ll n, m, a, b, x, cx, cy;
	cin >> n >> m >> a >> b >> x;
	if (x == 0) {
		if (n & 1 && a & 1) cx = n / 2 + 1;						//统计存在白色格子的行
		else cx = n / 2;
		if (m & 1 && b & 1) cy = m / 2 + 1;						//统计存在白色格子的列
		else cy = m / 2;
		cout << n * m - cx * cy;   								//白色越多，黑色越少
	} else {
		if (n & 1 && a & 1 && m & 1 && b & 1)
			cout << n * m - (n  / 2 + 1)  * (m  / 2 + 1) + 1;	//都为奇数时，将(a,b)位置的白点替换为黑点即可
		else
			cout << n * m - ((n + 1) / 2)  * ((m + 1) / 2);
	}
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
本来以为是动态规划，但 $n$ 和 $m$ 都很大，那么这就是显然的规律题。  
大家保险起见，最好还是开 __int128 吧，毕竟写个快读快写也不难。
## 2. 题目做法
我们将不选的点称为白点，要选的点称为黑点，那么我们需要使白点尽量多。  
观察题目限制，我们可以得出一个小结论，白点周围的八个点必定是黑点，否则会与题目冲突。  
我们便容易想出以下构造方案：  
![](https://cdn.luogu.com.cn/upload/image_hosting/16y33k3f.png)  
这样构造满足所有的题目限制条件，如果中间有白点被黑点占掉,那么最后算出后将答案加一即可。  
若限制条件为必有点为白点，则直接套公式即可。  
若限制条件为必有点为黑点，则分类讨论。  
情况一，此黑点左边和右边为白点。  
情况二，此黑点上面和下面为白点。  
情况三，此黑点左上，左下，右上，右下均为白点。  
只讨论这三种情况会得 65 分，其实还有一个隐藏情况。  
情况四，此黑点占掉了一个白点的位置。  
依次计算取最值即可。
## 3. 代码

```cpp
#include<bits/stdc++.h>
#define ll __int128
using namespace std;
const int N=110;
inline ll read()
{
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
inline void write(ll x)
{
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
ll n,m;
inline ll ask(ll a,ll b)
{
	ll h,s;
	h=(b-1)/2+(m-b)/2+1;
	s=(a-1)/2+(n-a)/2+1;
	return h*s;
}
ll a,b,x,mx;
ll sum;
int main()
{
	n=read(),m=read();
	a=read(),b=read(),x=read();
	if(x)
	{
		if(a>1)
			mx=ask(a-1,b);
		else if(a<n)
			mx=ask(a+1,b);
		if(b>1)
			mx=max(mx,ask(a,b-1));
		else if(b<m)
			mx=max(mx,ask(a,b+1));
		if(a>1&&b>1)
			mx=max(mx,ask(a-1,b-1));
		else if(a>1&&b<m)
			mx=max(mx,ask(a-1,b+1));
		else if(a<n&&b>1)
			mx=max(mx,ask(a+1,b-1));
		else if(a<n&&b<m)
			mx=max(mx,ask(a+1,b+1));
		if(a>2)
			mx=max(mx,ask(a-2,b)-1);
		else if(b>2)
			mx=max(mx,ask(a,b-2)-1);
		else if(a<n-1)
			mx=max(mx,ask(a+2,b)-1);
		else if(b<m-1)
			mx=max(mx,ask(a,b+2)-1);
		sum=n*m-mx;
	}
	else
		sum=n*m-ask(a,b);
	write(sum);
	return 0;
}
```

---

## 作者：Camellia2025 (赞：1)

题意：给定一个网格图，使其中两个点的连线都至少经过一个选中点。

## 思路

可以考虑如何构造，发现其构造规律求解。

## 考虑无限制情况

样例解释中就已经给了我们提示，可以试着用网格排列构造，它必然可行，并且易证其必然是最优方案里的一种~~其实我也不知道有没有其他最优方案~~。

大概是这样：


```
1为构造点，0为不选点。

0 1 0 1 0 1 0
1 1 1 1 1 1 1
0 1 0 1 0 1 0
1 1 1 1 1 1 1
0 1 0 1 0 1 0
```


然后看其他样例，发现也可以通过这种方法构造。

## 限制条件为给定白点

如果不选白点，应**先**考虑其边界奇偶性，如果都为偶数，那么无论不选哪个点，他都能找到相应的方案，使其答案和无限制条件一致。

```
2为限制点。

0 1 0 1    1 1 1 1   1 1 1 1
1 1 1 1    1 2 1 0   0 1 2 1
0 1 2 1    1 1 1 1   1 1 1 1
1 1 1 1    1 0 1 0   0 1 0 1
```
如果有哪一边为奇数，应考虑其白点对应坐标奇偶性，如果为偶数，那么将多选一条边。


```
1 1 1 1 1
1 0 1 0 1
1 1 1 1 1
1 2 1 0 1
1 1 1 1 1
```
因为我们不能选偶数边，而在边数奇数时，选编号为偶数的边会比选编号为奇数的边少一条，这是显而易见的。

## 限制条件为给定黑点

和上面思路一样，考虑奇偶性。

不过只有在范围和坐标都为奇数时，我们就把无限制条件的情况加一。

因为只要有一边为偶，则构造的方案总是能包含的，也就是说，无论范围的奇偶性如何，我们总是可以构造偶数编号的边。
所以如果都是限制点的坐标都是奇数，那么就将构造点个数加一。


```
任意一坐标为偶数：

0 1 0 1 0
1 1 1 1 1
0 1 0 2 0
1 1 2 2 1
0 1 0 1 0

都为奇数时加一：

0 1 0 1 0
1 1 1 1 1
0 1 2 1 0
1 1 1 1 1
0 1 0 1 0
```

接下来是代码时间。

## code

```
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
signed main() {
	int n, m, a, b, c, f = 0;
	cin >> n >> m >> a >> b >> c;
	int pastn = n, pastm = m;
	if (c == 0) { 
		if (n % 2 == 1 and a % 2 == 0) n++;
		if (m % 2 == 1 and b % 2 == 0) m++;
	} else if (a % 2 == 1 and b % 2 == 1 and n % 2 == 1 and m % 2 == 1) f = 1;
	n /= 2;
	m /= 2;
	cout << pastn * m + pastm * n - n * m + f;
} 
```
最后希望大家养成用位运算的好习惯~~因为初赛会考~~。

## code2
```
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
signed main() {
	int n, m, a, b, c, f = 0;
	cin >> n >> m >> a >> b >> c;
	int pastn = n, pastm = m;
	if (!c) { 
		if (n & 1 and !(a & 1)) n++;
		if (m & 1 and !(b & 1)) m++;
	} else if (a & 1 and b & 1 and n & 1 and m & 1) f = 1;
	n >>= 1;
	m >>= 1;
	cout << pastn * m + pastm * n - n * m + f;
} 
```

---

## 作者：_Kenma_ (赞：0)

# P11168 解题思路

## 前言

因为没开 unsigned long long 被硬控。

## 思路分析

考虑没有强制点限制的情况。

显然答案为：

$$ans=n \cdot m - (\lfloor \frac{n}{2} \rfloor + n \bmod 2) \cdot (\lfloor \frac{m}{2} \rfloor + m \bmod 2)$$

考虑构造如下：
 
$$\begin{matrix}
0,1,0,1\cdots,0,1,0,1,\cdots\\
1,1,1,1\cdots,1,1,1,1,\cdots\\
\cdots\\
0,1,0,1\cdots,0,1,0,1,\cdots\\
1,1,1,1\cdots,1,1,1,1,\cdots\\
\cdots\\
\end{matrix}$$

如果有强制点，考虑分讨：

- 强制点为黑色：
   - $x,y$ 都是奇数：此时 $(x,y)$ 是白点；
       - $n,m$ 都是奇数：将 $(x,y)$ 涂黑，$ans$ 增加 $1$；
       - $otherwise$：改变矩形 $0,1$ 的先后顺序，使 $(x,y)$ 成为黑点；
   - $otherwise$：此时 $(x,y)$ 本来就是黑点；
- 强制点为白色：
   - $x,y$ 都是奇数：此时 $(x,y)$ 本来就是白点；
   - $x,y$ 都是偶数：此时 $(x,y)$ 是黑点；
       - $n,m$ 都是奇数：将矩形第一行和第一列涂黑，使 $(x,y)$ 成为白点；
       - $n$ 是奇数，$m$ 是偶数：将矩形第一行涂黑，改变矩形每一列 $0,1$ 的先后顺序，使 $(x,y)$ 成为白点；
       - $n$ 是偶数，$m$ 是奇数：改变矩形每一行 $0,1$ 的先后顺序，将矩形第一列涂黑，使 $(x,y)$ 成为白点；
       - $n,m$ 都是偶数：改变矩形 $0,1$ 的先后顺序，使 $(x,y)$ 成为白点；
   - $x$ 是奇数，$y$ 是偶数：此时 $(x,y)$ 是黑点；
       - $m$ 是奇数：将矩形第一列涂黑，使 $(x,y)$ 成为白点；
       - $m$ 是偶数：改变矩形每一列 $0,1$ 的先后顺序，使 $(x,y)$ 成为白点；
   - $x$ 是偶数，$y$ 是奇数：此时 $(x,y)$ 是黑点；
       - $n$ 是奇数：将矩形第一行涂黑，使 $(x,y)$ 成为白点；
       - $n$ 是偶数：改变矩形每一行 $0,1$ 的先后顺序，使 $(x,y)$ 成为白点；

实现中，这样写代码一点也不优美。

观察得到：

- 当强制点为黑色时，$ans=n \cdot m - (\lfloor \frac{n}{2} \rfloor + n \bmod 2) \cdot (\lfloor \frac{m}{2} \rfloor + m \bmod 2)+[n \equiv m \equiv x \equiv y \equiv 1 \pmod{2}]$。

- 当强制点为白色时，$ans=n \cdot m - (\lfloor \frac{n}{2} \rfloor + x \bmod 2) \cdot (\lfloor \frac{m}{2} \rfloor + y \bmod 2)$。

然后会好写一点。

注意开 unsigned long long。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
unsigned int n,m,a,b,x,ans;
signed main(){
	cin>>n>>m>>a>>b>>x;
	ans=n*m;
	if(x==1){
		if(a&1 && b&1 && n&1 && m&1) ans++;
	}else{
		if(!(a&1) && n&1) n--;
		if(!(b&1) && m&1) m--;
	}
	ans-=(n/2+n%2)*(m/2+m%2);
	cout<<ans;
	return  0;
}

```

## 后记

不错的构造思维题，就是最后的分讨有点烦人。

---

