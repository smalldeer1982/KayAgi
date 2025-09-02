# Color the Carpet

## 题目描述

Even polar bears feel cold when lying on the ice. Therefore, a polar bear Alice is going to make a carpet. The carpet can be viewed as a grid with height $ h $ and width $ w $ . Then the grid is divided into $ h×w $ squares. Alice is going to assign one of $ k $ different colors to each square. The colors are numbered from 1 to $ k $ . She may choose not to use all of the colors.

However, there are some restrictions. For every two adjacent squares (squares that shares an edge) $ x $ and $ y $ , there is a color constraint in one of the forms:

- $ color(x)=color(y) $ , or
- $ color(x)≠color(y) $ .

Example of the color constraints:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/535d1d4ec9a1bcb4f1f5ac12060cde0f65471360.png)Ideally, Alice wants to satisfy all color constraints. But again, life in the Arctic is hard. It is not always possible to satisfy all color constraints. Fortunately, she will still be happy if at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/c7b5e8f543c3882ba6f2a662e01781b4de30f8c7.png) of the color constraints are satisfied.

If she has $ 4 $ colors she can color the carpet in the following way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/84535e9e280c4fb80d9cbe6a8b779a69a879098d.png)And she is happy because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/050547ba0080dee4ce4e2010a283122ee46b002c.png) of the color constraints are satisfied, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/93a2fe0ea2a5cac28f71987aac7a9527d1566697.png). Your task is to help her color the carpet.

## 样例 #1

### 输入

```
3 4 4
ENE
NNEE
NEE
ENEN
ENN
```

### 输出

```
YES
1 1 2 2
3 4 1 1
3 3 2 4```

# 题解

## 作者：Kappa6174 (赞：3)

## Statement

有一个 $h \times w$ 的网格，相邻的格子间有 `E` 和 `N` 两种关系之一，分别表示这两个格子的颜色相同/不同。问能否给每个格子染上 $1 \sim k$ 中的一种颜色，使至少 $\dfrac{3}{4}$ 的关系被满足。如果可以输出 `YES` 和方案，否则输出 `NO`。

## Solution

给一个不同的做法。

本文定义构造的网格行数为 $n$，列数为 $m$，颜色数为 $k$。

如果 $k=1$ 直接判掉。

接下来只用考虑 $n\leq m$ 的情况，因为 $n\gt m$ 的网格我们只要将其旋转即可转化成 $n\leq m$ 的情况。（为何要转化成这样的原因见下文）

结论：$k\geq 2$ 时一定有解。

证明：对于 $k=2$ 考虑如下构造：先将涂蓝色的方格填上 `1` 或 `2`，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/jxppdfb3.png)

容易发现一定有一个方案满足所有蓝色格之间的限制。

接着考虑橙色方格，可以先填旁边三个方格已知的方格，容易发现一定会有一种填法至多新产生 $1$ 个冲突，如果有 $x$ 个橙色方格，那么至多有 $x$ 个关系不满足。

总共有 $(n-1)m+n(m-1)$ 个方格，橙色方格有 $(n-1)\times\left \lfloor \dfrac{m}{2}\right \rfloor $ 个，即至多有 $(n-1)\times\left \lfloor \dfrac{m}{2}\right \rfloor$ 个冲突，现在只需要证：

$$ \frac{(n-1)\times\left \lfloor \dfrac{m}{2}\right \rfloor }{(n-1) m+n(m-1)}\leq \frac{1}{4}$$
即可。

若 $m$ 为奇数，$n$ 一定时，比值一定比 $m-1$ 小，因此只需要证 $m$ 为偶数的情况，即：
$$ \frac{(n-1)\times \dfrac{m}{2}}{(n-1)m+n(m-1)}\leq \frac{1}{4}$$
$$2(n-1)m\leq(n-1)m+n(m-1)$$

$$(n-1)m\leq n(m-1)$$

$$n\leq m$$

因为一开始保证了 $n\leq m$ ，所以保证了这样构造是对的。

[Code](https://www.luogu.com.cn/paste/ve8cnui4)。

---

## 作者：Miko35 (赞：2)

看题就觉得这个 $\frac{3}{4}$ 非常不对劲，一定有什么奇怪的做法，最后在学  whk 的时候忽然想到的。

先说结论：如果只有一种颜色可选，那就只能全填上进行判断；如果有两种及以上，只用两种颜色即可满足题意。考虑利用 $\frac{3}{4}$ 进行构造，$\frac{3}{4}$ 可以通过 $\frac{1}{2}+\frac{1}{4}$ 来得到：若行比列长，则行上条件可以全部满足，列上条件满足至少一半；反之，全部满足列上条件，行上满足至少一半。

这里以行比列长来举例说明，用 `0` 和 `1` 来代表两种颜色。注意，这种填色方案必须保证满足所有行上的条件。

第一行不妨随便构造一种可行的方案。如图。

![D.png](https://i.loli.net/2020/10/26/puLTk5NviDcHK6g.png)

我们考虑一行一行向下填色，因为必须第二行上条件必须随便满足，第二行就产生了**以1为首**与**以0为首**的两种填色方案。如图。

![E.png](https://i.loli.net/2020/10/26/Du8eIhbPoEzvtsl.png)

易知这两种方案一定是完全取反的（如上图的 `00110110` 与 `11001001`）。因此，对于第二行中每一个元素，总是有一种填法会满足它头上的条件，另一种不满足（如图，红色表示满足，绿色表示不满足）。也就是，不妨设夹在第一行与第二行中的竖着的条件有 $k$ 个，则在两种方案中，每个条件一定在且仅在一个方案中被满足，**即两种方案分别在这里满足的条件数之和为** $k$。又因为满足的条件数为非负整数，所以其中必有一种方案，在这里满足的条件 $≥ \frac{k}{2}$。对于每一行，我们都选择满足其头上条件较多的填法，这样可以保证在所有列上条件中，必定至少满足一半。

需要注意的地方：

- 只有一种颜色可选需要特判。

- 读入需要开两倍大小。

- 读入量大，不可以直接 `cin` 读入。

- 当列数大于行数时，必须选择交换行与列，否则不一定能满足条件，原因不赘述。

丑陋的代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int ans;
string s[2010],s2[2010];
int a[1010][1010],x[1010][1010],y[1010][1010];
int ena,flg;
int main(){
	ios::sync_with_stdio(0); 
	cin>>n>>m>>k;
	for(int i=1;i<2*n;i++){
		cin>>s2[i];
	}
	if(m<n){
		for(int i=1;i<2*n;i++){
			for(int j=0;j<s2[i].size();j++){
				s[2*(j+1)-((i&1)^1)]+=s2[i][j];
			}
		}
		swap(m,n),flg=1;
	}
	else{
		for(int i=1;i<2*n;i++){
			s[i]=s2[i];
		}
	}
	for(int i=1;i<2*n;i++){
		if(i&1){
			for(int j=0;j<s[i].size();j++){
				x[i/2+1][j+1]=(s[i][j]=='E'?0:1);
				ena+=(s[i][j]=='E');
			}
		}
		else{
			for(int j=0;j<s[i].size();j++){
				y[i/2][j+1]=(s[i][j]=='E'?0:1);
				ena+=(s[i][j]=='E');
			}
		}
	}
	if(k==1){
		if(ena*4>=3*n*(m-1)+3*m*(n-1)){
			cout<<"YES"<<'\n';
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					cout<<"1 ";
				}
				cout<<'\n';
			}
		}
		else cout<<"NO";
		return 0;
	}
	cout<<"YES"<<'\n';
	for(int i=1;i<=n;i++){
		a[i][1]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			a[i][j]=a[i][j-1]^x[i][j-1];
		}
	}
	for(int i=2;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=m;j++){
			cnt+=a[i][j]^a[i-1][j]^y[i-1][j]^1;
		}
		if(cnt<m-cnt){
			for(int j=1;j<=m;j++){
				a[i][j]^=1;
			}
		}
	}
	if(!flg){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cout<<a[i][j]+1<<' ';
			}
			cout<<'\n';
		}
	}
	else{
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				cout<<a[j][i]+1<<' ';
			}
			cout<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：Komomo (赞：0)

首先看到这种给了 $k$ 的更宽限制还让你判无解的东西，直接蒙 $k\ge 2$ 必有解，否则判断是否有解就已经是很玄学的东西了。

套路性的，我们使用调整法，先固定第一行，然后再依次满足下面的限制。

考虑我们在满足第 $i,i+1$ 行之间的 $m$ 个限制和第 $i+1$ 行的 $m-1$ 个限制，我们先把 $i,i+1$ 行之间的限制全部填满足，此时最大的无效限制数为 $m-1$，这说明需要调整。

如果对于限制 $(i+1,j-1)\leftrightarrow(i+1,j)$ 和 $(i+1,j)\leftrightarrow(i+1,j+1)$ 都不满足，我们只要 flip $(i+1,j)$ 的元素，这两个限制都会满足，而 $(i,j)\leftrightarrow(i+1,j)$ 会变得不满足。

分析一下，现在的不满足限制上限为 $\left\lfloor\dfrac m 2\right\rfloor$，总的占比是 $\dfrac{\left\lfloor\dfrac m 2\right\rfloor}{2m-1}$，发现分母那里还差 $1$。回头发现，第一行的所有 $m-1$ 个限制一定是被满足的，只要这 $m-1$ 个限制能均分到下面 $n-1$ 行即可，这个只要翻转一下矩阵就好了。

---

