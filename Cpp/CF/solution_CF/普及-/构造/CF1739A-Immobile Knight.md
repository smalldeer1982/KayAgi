# Immobile Knight

## 题目描述

There is a chess board of size $ n \times m $ . The rows are numbered from $ 1 $ to $ n $ , the columns are numbered from $ 1 $ to $ m $ .

Let's call a cell isolated if a knight placed in that cell can't move to any other cell on the board. Recall that a chess knight moves two cells in one direction and one cell in a perpendicular direction:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)Find any isolated cell on the board. If there are no such cells, print any cell on the board.

## 说明/提示

In the first testcase, all cells are isolated. A knight can't move from any cell of the board to any other one. Thus, any cell on board is a correct answer.

In the second testcase, there are no isolated cells. On a normal chess board, a knight has at least two moves from any cell. Thus, again, any cell is a correct answer.

In the third testcase, only the middle cell of the board is isolated. The knight can move freely around the border of the board, but can't escape the middle.

## 样例 #1

### 输入

```
3
1 7
8 8
3 3```

### 输出

```
1 7
7 2
2 2```

# 题解

## 作者：zhujiangyuan (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1739A)
### 题意
给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则输出任意一个格子。
### 分析
我们是首先要知道在国际象棋中马的走法：横向走 $1$ 个格子，纵向走 $2$ 个格子 或者 横向走 $2$ 个格子，纵向走 $1$ 个格子。

- 当棋盘大小为 $1\times n$ 时，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/bvfzpbph.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

不论马放在何处，都只能向一个方向走，不符合马的走法，所以输出任意坐标，我们输出 $(1,1)$ 即可。

- 当棋盘大小为 $2\times n$ 时
1. $2\times 2$，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/01c6ujqe.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果放在 $(2,2)$ 必定不能走，因为向任何方向都只能走 $1$ 个格子，不符合马的走法，输出 $(2,2)$。

2. $2\times n(n>2)$，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/kafqsohm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

马放在任何地方都可以走，因为放在任何地方横向都可以走 $1$ 个格子，纵向走 $2$ 个格子，符合马的走法。所以输出任意坐标即可，为了统一，我们也输出 $(2,2)$。

- 当棋盘大小为 $3\times n$ 时
1. $3\times 3$，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/q2rbgx22.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果放在 $(2,2)$ 必定不能走，因为向任何方向都只能走 $1$ 个格子，不符合马的走法。

2. $3\times n$，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/no1vjm67.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

马放在任何地方都可以走，因为放在任何地方横向都可以走 $1$ 或 $2$ 个格子，纵向走 $2$ 个格子，符合马的走法。所以输出任意坐标即可，为了统一，我们也输出 $(2,2)$。
- 当棋盘横纵大小都大于 $3$ 时，则任意位置都可以走。因为不管放在哪，横向和纵向都能至少移动 $2$ 个格子。为了统一，我们还输出 $(2,2)$。
#### 总结一下：如果 $n$ 或 $m$ 为 $1$，输出 $(1,1)$ 即可，其他输出 $(2,2)$ 即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
       int n,m;
       cin>>n>>m;
       if (n==1||m==1) cout<<1<<' '<<1<<endl;
       else cout<<2<<' '<<2<<endl;
    }
    return 0;
}
```

---

## 作者：L_zaa_L (赞：5)

## 分析
由于数据很水，$1 \le n,m \le 8$,于是可以通过暴力来解决这道题。首先我们先将坐标设为一个随便的数（就 $x=1,y=1$ 吧），然后呢，一个一个格子的判断，也就是判断 $(x-1,y-2),(x+1,y-2),(x-1,y+2),(x+1,y+2),(x-2,y-1),(x+2,y-1),(x-2,y+1),(x+2,y+1)$，这八个地方是否越界，只要有一个没越界，这个地方马就是可以跳走的。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,t,m;
int main(){
	cin>>t;
	for(int s=1;s<=t;s++){
		cin>>n>>m;
		int x=1,y=1;//随便设一个
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if((i-2>=1&&j+1<=m)||(i+2<=n&&j+1<=m)||(i-2>=1&&j-1>=1)||(i+2<=n&&j-1>=m)||(i-1>=1&&j+2<=m)||(i+1<=n&&j+2<=m)||(i-1>=1&&j-2>=1)||(i+1<=n&&j-2>=m))//判断是否越界
					continue;
				else{
					x=i,y=j;//只用一个就行了
					break;
				}
			}
		cout<<x<<" "<<y<<endl; 
	} 
	return 0;
}
```

---

## 作者：saixingzhe (赞：3)

# 思路
我们发现在一个大于 $3\times3$ 矩阵中不存在使得马在上面不能走到其它格子的点。

在 $n\times1$ 的矩阵中每一个点都符合要求，因此我们输出 $(1,1)$。

还有一种情况，在 $2\times2$ 或 $2\times3$ 的矩阵中有 $(2,2)$ 满足要求，又因为题目中说不存在则输出任意一个格子所以当在 $n\times1$ 的矩阵中我们输出 $(1,1)$，其他输出 $(2,2)$ 即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
int main(){
    cin>>t;
    while(t--){
       cin>>n>>m;
       if(n==1||m==1) cout<<1<<' '<<1<<endl;
       else cout<<2<<' '<<2<<endl;
    }
    return 0;
}
```

---

## 作者：undefined_Ryan (赞：1)

还是比较水的一道入门题，方法很多，这里列出两种思路。

1. 一般思路，考虑具有不能移动的格子的棋盘大小。假设棋盘大小为 $n\times m$（$n$ 行 $m$ 列）。不妨 $n\ge m$，分几种情况讨论：
> - 如果 $m=1$，那么一定存在，取任意一格（参考样例）。
> - 如果 $m=2$，那么在 $n\le3$ 时存在，取第 $2$ 行任意一格。
> - 如果 $m=3$，那么在 $n=3$ 时存在，取第 $2$ 行第 $2$ 列。

由此，可以归纳成 $3$ 种情况（这里不假设 $n\ge m$）：
- 当 $n=1$ 或 $m=1$ 时，存在，取任意一格，比如 `1 1`。
- 当 $2\le n\le3$ 且 $2\le m\le 3$ 时，存在，取 `2 2`。
- 当 $n\ge4$ 或 $m\ge4$ 时，不存在，取任意一格。

最简单的写法为第三种情况取 `2 2`，代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
int main() {
	cin>>t;
    for (int i=1;i<=t;i++) {
    	cin>>n>>m;
        if (n==1||m==1) cout<<"1 1\n";
        else cout<<"2 2\n";
    }
    return 0;
}
```

2. 提供另一种思路。在棋盘中的一格中，若从它开始不可移动，那么即相当于在它把棋盘划分成的四个区域中没用足够移动的空间。（如图，图中点即为棋盘上的格子）

![图片](https://cdn.luogu.com.cn/upload/image_hosting/00935ap8.png)

图中以紫色线段为分界，$4\times5$ 的棋盘被划分成了四个区域。只用考虑黄色部分，其余区域在两个维度均不超过黄色区域。而蓝色点在黄色区域中可以到达两个其他点，因此蓝色点不是不可移动的。

考虑将蓝色点上升一个方格，若如此做，则右上角区域依然是最大的，但它在两个维度均不超过原来区域。因此，如果一个图中存在不可移动的格子，那么最靠近中心的格子必定不可移动。

如果不存在，输出最靠近中心的格子也没有问题。贴上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
int main() {
	cin>>t;
	for (int i=1;i<=t;i++) {
		cin>>n>>m;
		cout<<(n+1)/2<<' '<<(m+1)/2<<endl;
	}
    return 0;
}
```

---

## 作者：0zhouyq (赞：1)

### CF1739A 题解

[传送门](https://www.luogu.com.cn/problem/CF1739A)

### 思路：

分类讨论：

1. $n$ 为 $1$ 或 $m$ 为 $1$。输出答案为（$1,1$）即可。

2. $n>3$ 且 $m>3$，输出答案为任意一点，可以为（$2,2$）。

3. $n$ 为 $2$ 或 $m$ 为 $2$，因为 $n$ 和 $m$ 都是大于 $2$ 的，所以可以直接输出（$2,2$），因为如果 $m\le3$，（$2,2$）是符合答案的，而当 $m>3$ 时，可以直接输出任意一点，也可以输出（$2,2$）。

4. $n$ 为 $3$ 或 $m$ 为 $3$，同上，无论如何（$2,2$）都是符合要求的。

所以整个题目只需要判断一下即可：如果 $n,m$ 均大于 $1$，直接输出（$2,2$）；否则输出（$1,1$）。

### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int a,b;
		scanf("%lld %lld",&a,&b);
		if(a>=2&&b>=2) cout<<"2 2\n";
		else cout<<"1 1\n";
	}
	return 0;
}
```

---

## 作者：zzy0618 (赞：0)

### 题目描述

给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则输出任意一个格子。

### 大体思路

题目虽然可以考虑暴力，但不是我们的主要内容

[暴力代码](https://www.luogu.com.cn/paste/v4s67qec)

我们可以讨论分类讨论一下

1. 首先考虑比 $n,m\ge 4$ 的情况，此时，无论马在哪个格子，它都能走到其它格子。

2. 然后是 $n$ 或 $m$ 为 $1$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ozt4fif.png)

此时，无论马处于何处，都无法走到其它格子，但为了保险起见，输出 $(1,1)$ 的位置绝对没问题。

3. $n,m $ 为 $2$ 或 $3$，但不超过 $4$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/clggztwm.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/mka3fod7.png)

我们会发现无论如何，马在 $(2,2)$ 的位置都无法走到其它格子。

此时我们总结一下：

- $n$ 或 $m$ 为 $1$，输出 $(1,1)$。

- 因为题目说过，不存在合理情况则任意输出一个格子，所以对于任何 $n,m \ge 2$ 的情况，我们都可以输出 $(2,2)$

- 由于此题多组数据，且输出较简单，可以考虑优化读入和输出。


### 完整代码

[使用快读真的很快](https://www.luogu.com.cn/record/101905839)


```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}//快读模板 
int main() {
	register int t, n, m;
	t = read();
	while (t--) {
		n = read(); m = read();
		if (n == 1 || m == 1) {// n 或 m 为 1 的情况 
			putchar('1'); putchar(' ');
			putchar('1'); putchar('\n');//加快输出 
		}
		else {// 大于等于 2 的情况 
			putchar('2'); putchar(' ');
			putchar('2'); putchar('\n');
		}
	}
	return 0;
}
```



---

## 作者：Leaves_xw (赞：0)

**大意：**

给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则输出任意一个格子。

**思路：**

我们可以把马放在角上，一个一个的判断(马走“日”字形)。

如果 $n=1,m=1$，马站在角上是不行的。

再判断，如果 $n=1,m=2$，的话，也是不行的。

如此等等。

最后，我们可以得出，如果 $n=1$ 或 $m=1$,输出 $(1,1)$ ，否则输出 $(2,2)$。

**code:（c++）**

```
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t,n,m;
    cin>>t;
    for(int i=1;i<=t;i++)//循环
    {
       cin>>n>>m;
       if(n==1||m==1)cout<<1<<' '<<1<<endl;//判断n=1或m=1
       else cout<<2<<' '<<2<<endl;
    }
    return 0;
}
```

**code:(c)**

```
#include<stdio.h>

int main()
{
    int t,n,m;
    cin>>t;
    for(int i=1;i<=t;i++)//循环
    {
       cin>>n>>m;
       if(n==1||m==1)cout<<1<<' '<<1<<endl;//判断n=1或m=1
       else cout<<2<<' '<<2<<endl;
    }
    return 0;
}
```

管理员求过！

---

## 作者：maomao233 (赞：0)

### 题意
给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则**输出任意一个格子**。


### 分析
我们从 $1$ 开始枚举

- 当 $n$ 或 $m$ 为 $1$ 时，那马就没法跳“日”字，无解，**随便输出一个坐标**。

- 当 $n$ 和 $m$ 都为 $2$ 时，棋盘是个田字格，那还是走不了，无解，**随便输出一个坐标**。

- 当 $n$ 和 $m$ 都为 $3$ 时，就是个井字格，马只有站在**正中间**才不能到达其他格子，所以**输出最中间的格子。**

- 当 $n$ 和 $m$ 都大于 $3$ 时，那马无论站在哪个位置都可以走，此时也无解了，**随便输出一个坐标**。

至此我们就知道了，只有当 $n$ 和 $m$ 都为 $3$ 时才有解。那既然其他的都可以随便输出，那只需要判断 $n$ 和 $m$ 都为 $3$ 的情况了，直接输出 $(2,2)$ 即可，其余的输出 $(1,1)$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
    cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		if((n==1||m==1)||(n==2&&m==2)||(n>3&&m>3))
		{
			puts("1 1");
		}
		else
		{
			puts("2 2")
		}
	}
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1739A)        
简单构造。     
我们举一些例子：     
如果 $n=1$ 的话，$m$ 不管多大，在 $(1,1)$ 总是不能的。$m=1$ 同理。    
在 $n=2$ 和 $m=2$ 的情况下，我们可以发现放在 $(1,1)$ 也总是不能移动。    
其他情况，放在 $(2,2)$ 就可以了。      
CODE：    
```cpp
#include <iostream>
using namespace std;
int t,a,b;
int main(void){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if((a<=2&&b<=2)||a==1||b==1){
			cout<<"1 1"<<endl;
		}else{
			cout<<"2 2"<<endl;
		}
	}
}
```


---

## 作者：binaryBard (赞：0)

读题点 [这里](https://www.luogu.com.cn/problem/CF1739A)

更好的阅读体验点 [这里](https://blog.jerryz.com.cn/article/solution-CF1739A)

# 题意简述

给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则输出任意一个格子。

# 思路分析

假设马现在在 $(x,y)$，那么下一步它可以跳到 $(x \pm 1,y \pm 2)$ 或 $(x \pm 2,y \pm 1)$。

那么，共分为三种情况：

1. 当 $n,m \le 2$ 时，马无法跳到任何格子，任意格子都满足条件。

2. 当 $n=m=3$ 时，马只有在最中间的方格才无法跳到任何一个格子。

3. 当 $n,m>3$ 时，马无论在任何位置，都可以跳到其它格子，无解，输出任意一个坐标即可。

故输出方格中间的数一定满足条件

# 代码

```C++
#include<bits/stdc++.h>
using namespace std;

int T,n,m;

int main(){
    cin>>T;
	while(T--){
		cin>>n>>m;
		cout<<(n+1)/2<<" "<<(m+1)/2<<endl;
	}
	//system("pause");
	return 0;
}
```

---

## 作者：_k_e_v_i_n_ (赞：0)

# 题目简述

给定一个 $n\times m$ 的国际象棋棋盘，求一个格子使得马在上面不能走到其它格子。不存在则输出任意一个格子。（~~多了个句号~~）

# 思路

不难发现，除如下几种情况马不能走到其它格子以外，其余的都可以。

![](https://cdn.luogu.com.cn/upload/image_hosting/lg01lapm.png)

规律：

- $N,M \ge 2$，输出 ```2 2```（不存在输出任意一个格子）。

- $N=1$ 或 $M=1$，输出 ```1 1``` （~~你输出啥都行~~，只要第一个数 $\le N$ 且第二个数 $\le M$）。

# AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int t, a, b;
int main(){
	cin >> t;
	while (t--){
		cin >> a >> b;
		if (a == 1 || b == 1){
			cout << "1 1" << "\n";
		}else{
			cout << "2 2" << "\n";
		}
	}
	return 0;
}

```

---

## 作者：zbk233 (赞：0)

## 思路

考虑分类讨论。

假设马现在在 $(x,y)$，那么下一步它可以跳到 $(x \pm 1,y \pm 2)$ 或 $(x \pm 2,y \pm 1)$。

1. 当 $n \le 2$ 且 $m \le 2$ 时，由于 $x$ 或 $y$ 可以加减 $2$，所以任意格子都能成立。

2. 当 $2 < n \le 3$ 且 $2 < m \le 3$ 时，此时取方格中间的数才是最优的，也就是 $(2,2)$，易证这个格子是成立的。

3. 当 $3 < n$ 且 $3 < m$ 时，此时显然无解，可以输出任何一个坐标。

综上，实际只需要输出 $(\min(2,n),\min(2,m))$ 就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m;
	cin>>t;
	while(t--){
		cin>>n>>m;
		cout<<min(2,n)<<' '<<min(2,m)<<'\n';
	}
	return 0;
}
```


---

## 作者：小明小红 (赞：0)

# CF1739A

 [题目传送门](https://www.luogu.com.cn/problem/CF1739A)
 
 
题目思路：思维题。
 
分情况讨论：

若最终存在点满足，那中点定能满足（~~这是长方形~~）。

若没有点满足，输出重点还是可以。

综上所述，输出中点。
## code

```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,T;
int main()
{
	cin>>T;
	while(T--)//T组数据
	{
		cin>>n>>m;
		cout<<(n+1)/2<<' '<<(m+1)/2<<endl;//输出中点
	}
	return 0;
}
```


---

## 作者：abensyl (赞：0)

## 思路

当 $n$ 或 $m$ 中有一个大于 $3$ 时，必定每一个格子马都能跳，所以这种情况可以任意直接输出一个格子。

当格子数在规定范围内时，可以直接输出中心格子，这样就可以保证既不出界，也能选择一个正确的格子。

经各种检验（你可以把九种情况都枚举一遍试试），这个方法是切实可行的。

有解情况下，输出 $n+1\over 2$ 和 $m+1\over 2$ 即可。

而还有一种有解情况，当 $n=1$ 或 $m=1$ 时，期盼只有一行或一列，必定有解。

通过这一题，我也想叫个为一个方法，就是当情况较少时，枚举反而有时是最快的证明方法。

## 简单构造

```cpp
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>

using namespace std;

const int N = 1e5+3;

int main() {
  #ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
  #endif
  int t;
  cin>>t;
  while(t--) {
    int a,b;
    cin>>a>>b;
    if(b<=3&&a<=3) cout<<(a+1)/2<<' '<<(b+1)/2<<'\n';
    else cout<<"1 1\n";
  }
  return 0;
}
```


---

## 作者：luo_shen (赞：0)

### 题目描述
给定一个 $n \times m$ 大小的棋盘，问棋盘上是否有一个格子，使得在上面放一个马，马不能走到一个其它的格子上去，有则输出这个格子，没有则随意输出一个格子。
### 题目分析
若存在这样一个格子，那么它一定是往任意一个格子都走不了两格，或往某一个方向走得了两格，但不能往相邻方向走。显然，这个格子处于棋盘正中间。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
signed main(){
    int t,n,m;
    t=read();
    while(t--){
        n=read(),m=read();
        printf("%d %d\n",(n+1)>>1,(m+1)>>1);
    }
    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

暴力枚举每一个马能走到的位置，判断它是否在棋盘上。如果一个点马走到的八个点都不在棋盘上，记录这个点。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
bool check(int x,int y)//判断它是否在棋盘上
{
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		int x=1,y=1;
		for(int i=1;i<=n;i++)//枚举所有点
			for(int j=1;j<=m;j++)
			{
				int flag=1;
				for(int k=0;k<8;k++)//枚举马能走到的位置
					if(check(i+dx[k],j+dy[k]))
						flag=0;
				if(flag)
					x=i,y=j;
			}
		cout<<x<<" "<<y<<"\n";
	}
}
```


---

