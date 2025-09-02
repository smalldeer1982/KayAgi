# Toy Machine

## 题目描述

There is a toy machine with toys arranged in two rows of $ n $ cells each ( $ n $ is odd).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1817D/94d0c52f63bc0e7f013e6cc3463bef573e7be445.png) Initial state for $ n=9 $ .Initially, $ n-2 $ toys are placed in the non-corner cells of the top row. The bottom row is initially empty, and its leftmost, rightmost, and central cells are blocked. There are $ 4 $ buttons to control the toy machine: left, right, up, and down marked by the letters L, R, U, and D correspondingly.

When pressing L, R, U, or D, all the toys will be moved simultaneously in the corresponding direction and will only stop if they push into another toy, the wall or a blocked cell. Your goal is to move the $ k $ -th toy into the leftmost cell of the top row. The toys are numbered from $ 1 $ to $ n-2 $ from left to right. Given $ n $ and $ k $ , find a solution that uses at most $ 1\,000\,000 $ button presses.

To test out the toy machine, a [web page](https://assets.codeforces.com/files/56ff21637146a30d/game.html) is available that lets you play the game in real time.

## 说明/提示

In the first example, there will be $ 5-2 = 3 $ toys. The first toy needs to end up in the leftmost cell of the top row. The moves RDL will achieve this, see the picture for a better understanding. Another possible solution would be to do one button press L.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1817D/66c2e50f9847246b23ba3d60d2f2f351991761fb.png) Visualization of the moves for the first example.

## 样例 #1

### 输入

```
5 1```

### 输出

```
RDL```

## 样例 #2

### 输入

```
7 2```

### 输出

```
RDL```

# 题解

## 作者：ZMQ_Ink6556 (赞：8)

## 题解：CF1817D Toy Machine

一道比较水的**构造**。

### 解题思路

我们可以打开[英文题面给的链接](https://assets.codeforces.com/files/56ff21637146a30d/game.html)，实践几次，就可以更快得到结论。

通过实践，我们发现，若 $k$ 在图形前一半，也就是 $k \le \lfloor\frac{n}{2}\rfloor$ 时，可以通过每轮操作将其左移一位来移动到左端，也就是 `LDRU`，如图：

![1](https://cdn.luogu.com.cn/upload/image_hosting/uwnjcsnb.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

经过操作，可以用下面的槽位将原有的第一位扔到后面，从而让第二个成为第一个，我们可以重复多轮这样的操作，使得第 $k$ 个成为第一个。

但是不要认为这题就这么简单，比如在 $n = 5$ 时，$k = 4$ 或 $k = 5$ 的方块都不能转到位置。而是 `a`、`b` 和 `c` 原地打转。

所以在 $k > \lfloor\frac{n}{2}\rfloor$ 时，我们得推新的方法。比如说让这个方块先放到最右端：

![2](https://cdn.luogu.com.cn/upload/image_hosting/9d9z8k3o.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

同样是通过重复操作，使第 $k$ 个方块到达最后一位，然后进行压缩，让所有方块都聚集在右边，形如：

![3](https://cdn.luogu.com.cn/upload/image_hosting/xxamms3p.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

然后按一下左后，这情况好像很熟悉，$k$ 不就是第一种情况时最大的符合条件的位置吗？所以剩下的就可以按照第一种的方法做了。

总结第二种情况的思路：先是 $n - k - 2$ 次 `RDLU`，再是 $\lfloor \frac{n}{2} \rfloor$ 次 `RDRU`，最后是 $\lfloor \frac{n}{2} \rfloor - 1$ 次 `LDRU`，最后一个 `L`，将第 $k$ 个物品推到第一格。

这道题整体思维偏难，但代码非常简单，~~又可以水一道紫题~~。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , k , go_right;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	n -= 2;
	if(k <= n / 2 + 1)
	{
		for(int i = 1 ; i < k ; i++)
		{
			cout << "LDRU";
		}
		cout << "L";
		return 0;
	}
	if(k > n / 2 + 1)
	{
		go_right = n - k;
		for(int i = 1 ; i <= go_right ; i++)
		{
			cout << "RDLU";
		}
		for(int i = 1 ; i <= n / 2 ; i++)
		{
			cout << "RDRU";
		}
		for(int i = 1 ; i <= n / 2 ; i++)
		{
			cout << "LDRU";
		}
		cout << "L";
	}
	return 0;
}
```

感谢浏览。

---

## 作者：Alex_Wei (赞：7)

#### [CF1817D Toy Machine](https://www.luogu.com.cn/problem/CF1817D)

烂烂 烂烂 烂烂 烂烂 烂烂 烂烂 烂烂 烂烂 烂烂 烂烂。

烂烂 Ad-hoc。

对于 $k = 2$，考虑把 $1$ 搞到它后面，容易想到执行 `LDRU`，发现 $2\sim \frac {n - 1} 2$ 向前移动了一位。因此，设 $m = \frac {n - 1} 2$，对于 $k\leq m$，执行 $k - 1$ 次 `LDRU` 和一次 `L`。

那后半部分怎么办？考虑先用对称的方法将 $k$ 挪到最右边，然后不断执行 `RDRU` 直到所有数全部堆在右半部分，且 $k$ 在右上角，再执行一次 `LU`，$k$ 就变到了原来 $m$ 的位置。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1817/submission/204420427)。

---

## 作者：FireFy (赞：2)

## CF1718D Toy Machine

**水紫**

其实你多找几组数据然后对着[这个](https://assets.codeforces.com/files/56ff21637146a30d/game.html)手模就行了。

不过还是讲讲大体思路和推导出的规律。

### Case 1

当 $K<\frac{n}{2}$ 时，就非常简单了。

只需要不断地 `LDRU` 其实就行了。

**举个栗子**：

当 $n=7,k=2$ 时，玩具机长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/dmwcokgo.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我们可以发现，每 `LDRU` 一次，都可以使得左面的字母块往右移动一位。

`LDRU` 一次：

![](https://cdn.luogu.com.cn/upload/image_hosting/n15ikpv6.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

当你使得想要的字母块已经在第一位时，再 `L` 一下就可以啦！

再找一些栗子一推，我们的公式就出来啦：

因为每 `LDRU` 一次都会使字母块往前移一格，所以先 `LDRU` $k-1$ 次，然后在 `L` 一下即可。



### Case 2

当 $K=\left \lceil \frac{N}{2}  \right \rceil $ 时，就更简单了。

相当于要你求的方块在正中间。

直接 `DL` 就行了。



### Case 3

当 $K>\frac{n}{2}$ 时，就会变得很难，思维难度较大。

我的思路是用 `RDLU` 与 `RDRU` 先将要求的方块与其他方块团成一坨。

因为 `RDLU` 其实就是 `LDRU` 的反操作，所以要令所需的字母块处于最右边，必须先 `RDLU` $n-k$ 次。

达到最右边之后，将问题转化为 `LDRU` 可以解决的问题，不难发现只要将要求的字母块放在第二行第二个即可 `LDRU` 解决了。所以我们使用 `RDRU` 将目标字母块放到目标位置，然后在将目标方块移动至左边，`LDRU` 解决。

这么说有些抽象，还是举栗子：

当 $n=9 , k=6$ 时，玩具机长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/z01dfxvx.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

`RDLU` 一次：

![](https://cdn.luogu.com.cn/upload/image_hosting/mrfkevp5.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

接着 `RDLU`，直到变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2dcaqygv.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

再接着 `RDRU`，最终会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9x6cs53t.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

好了，已经团成一坨了，接下来就是把目标方块转移到左边。

简单的几次 `LDRU` 就可以变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/qikv10h2.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

然后在 `L` 一下就可以啦。

老样子，多手模几个栗子然后推答案就行了。

总结一下：

先`RDLU` $n-k$ 次，在 `RDRU` $n$ 次（其实多出来步数没关系）

最后在 `LDRU` $\left\lfloor\frac{N}{2}\right\rfloor$ 次然后 `L` 一下就行啦！

### 小细节 

因为游戏机是 $N$ 个格子，但是本题解所说的 $N$ 实为方块个数，所以请记得 $n-2$。

## 上代码！！！

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int i,j,k,n,m;
	cin>>n>>m;
	n-=2;
	if(m<=n/2+1)
	{
		m--;
		while(m--) cout<<"LDRU"; 
		cout<<"L";
	}
	else
	{
		for(i=1;i<=n-m;i++) cout<<"RDLU";
		for(i=1;i<=n/2;i++) cout<<"RDRU";
		for(i=1;i<=n/2;i++) cout<<"LDRU";
		cout<<"L"<<endl;
	}
 } 
```

---

## 作者：hongshixiaobai (赞：2)

# CF1817D Toy Machine 题解
[传送门](https://www.luogu.com.cn/problem/CF1817D)
## 思路
用[题面上的这个网页](https://assets.codeforces.com/files/56ff21637146a30d/game.html)手模一下可得：

- $k<\frac{n}{2}$ 时可以通过 $k$ 次 `LDRU` 后按 `L` 到达第一行最左边。
- 正中间的方块直接 `DL` 即可到达第一行最左边。
- $k>\frac{n}{2}$ 时可以通过 $n-k$ 次 `RDLU` 后成为第一行的最后一个，然后 $\lfloor \frac{n}{2}\rfloor$ 次 `RDRU` 到达第一行最右边，最后 $\lfloor \frac{n}{2}\rfloor$ 次 `LDRU` 后按 `L` 到达第一行最左边。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n>>k;
	if(k == (n/2))
	{
		cout<<"DL";
		return 0;
	}
	else if(k<(n/2))
	{
		cout<<"L";
		for(int i = 1;i<k;i++)
		{
			cout<<"DRUL";
		}
		return 0;
	}
	else
	{
		n-=2;
		for(int i = 1;i<=n-k;i++)
		{
			cout<<"RDLU";
		}
		for(int i = 1;i<=(n/2);i++)
		{
			cout<<"RDRU";
		}
		cout<<"L";
		for(int i = 1;i<=(n/2);i++)
		{
			cout<<"DRUL";
		}
	}
}
```

---

## 作者：Otomachi_Una_ (赞：2)

奇妙 ad-hoc。

如果 $k\leq\dfrac n2$，那么我们执行 $k-1$ 次 `LDRU` 操作可以把 $k$ 顶到中间上面，再执行一次 `L` 操作可以把 $k$ 挪到最左边。


如果 $k>\dfrac n2$，那么我们和 $<\dfrac n2$ 类似的方法可以把 $k$ 挪到最右边，再执行 $n$ 次 `RDRU` 操作可以把所有元素挪到最右边一坨。$k$ 还是在右上角，我们通过一次 `LU` 操作可以把 $k$ 挪到中间，也就变成了 $k=\dfrac n2$ 的情况，套用上面的做法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
int main(){
	ios::sync_with_stdio(false);
	int n,k;cin>>n>>k;
	if(k<n/2){
		for(int i=1;i<k;i++) cout<<"LDRU";
		cout<<"L"<<endl;
	}else if(k==n/2){
		cout<<"DL"<<endl;
	}else{
		for(int i=1;i<=n-k;i++) cout<<"RDLU";
		cout<<"R";
		for(int i=1;i<=n;i++) cout<<"RDRU";
		cout<<"LU";
		for(int i=1;i<n/2;i++) cout<<"LDRU";
		cout<<"L"<<endl;
	}
}
```

---

## 作者：ricky_lin (赞：1)

一道很好玩的游戏题。

题目也非常良心，给了一个可以操作的网页：

![](https://cdn.luogu.com.cn/upload/image_hosting/cjixekud.png)

**operation 1**：我们考虑手玩一下可以发现左半部分很简单，就是 `LDRU` 即可，然后最后接一个 `L`（下图为将 `d` 挪到最左边）。



![](https://cdn.luogu.com.cn/upload/image_hosting/e943jihi.png)

关键是右半部分怎么挪动到左边？

**operation 2**：我们发现我们可以使用 `RDRU` 将所有玩具都挪到最右边，然后再用一个 `L` 将最右边的玩具挪到最左边

![](https://cdn.luogu.com.cn/upload/image_hosting/0oj5qty3.png)

**operation 3**：现在我们就需要将右半部分的玩具挪到最右边，可以模仿挪到最右边的方法 `RDLU` 即可，然后最后接一个 `R`（下图为将 `f` 挪到最右边）

![](https://cdn.luogu.com.cn/upload/image_hosting/0gj4l4dx.png)

我们的右边的玩具的挪动方法便出来了，就是先用该玩具通过 **operation 3** 挪到最右边，再使用 **operation 2** 将其挪到左半部分，最后使用 **operation 1** 将其挪到最左边。

![](https://cdn.luogu.com.cn/upload/image_hosting/oa6gedq1.png)

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	scanf("%d%d",&n,&k);
	if(k == n/2) return puts("DL"),0;
	if(k < n/2){
		for(int i = 1; i < k; ++i) printf("LDRU");//operation 1
		printf("L\n");
	}//左半边
	else{
		for(int i = k; i < n-2; ++i) printf("RDLU");//operation 3
		for(int i = 1; i <= n/2+10; ++i) printf("RDRU");//operation 2
		for(int i = 1; i < n/2; ++i) printf("LDRU");//operation 1
		printf("L");
	}//右半边
}
```

---

## 作者：Michael1234 (赞：1)

**UPD on 2024.7.29:修改一处笔误**

- 本题可以使用**找规律**和**分类讨论**的方法

- 首先，我们设当前所需处理的点的横坐标为 $x$，那么 $x=k+1$。

- 那么当 $x < \lceil \frac{n}{2} \rceil$，我们只需不断执行 `DRUL` 操作，直到该点到达位置。

- 当 $x=\lceil \frac{n}{2} \rceil$，只需执行一次 `DL` 操作即可。

- 当 $x>\lceil \frac{n}{2} \rceil$，需先执行 `D`，再不断执行 `URDL`，直到形成这种情况（此处在解决字块 `f`）：

![](https://cdn.luogu.com.cn/upload/image_hosting/v6p7h07r.png)

- 接下来不断执行 `ULDL`。直到出现这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/848nmkbr.png)

- 这时候，直接执行 `RDL` 即可。

- 过程稍有些抽象，读者可自行模拟。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>k;
	x=k+1;
	if(x<n/2+1)//情况一
	{
		for(int i=1;i<=k;i++)
		{
			cout<<"DRUL";
		}
	}
	else if(x==n/2+1)//情况二
	{
		cout<<"DL"; 
	}
	else//情况三
	{
		cout<<"D";
		while(x!=n-1)
		{
			x++;
			cout<<"URDL";
		}
		while(x!=n/2+1)
		{
			x--;
			cout<<"ULDL";
		}
		cout<<"RDL";
	}
	exit(0);
}
```

---

## 作者：AK_400 (赞：1)

我的评价是：这题就对着网页手模就行。
## 1. $k = \lceil \frac{n}{2} \rceil$
比较显然，输出 `DL` 即可。
## 2. $k < \lceil \frac{n}{2} \rceil$
你乱手模一下 $k=2$ 发现就是 `DRUL`，然后发现：![](https://cdn.luogu.com.cn/upload/image_hosting/uu97kwcq.png)![](https://cdn.luogu.com.cn/upload/image_hosting/0phkbmyx.png)![](https://cdn.luogu.com.cn/upload/image_hosting/kt5sgzqb.png)

观察到执行 $i$ 次 `DRUL` 时第 $i$ 个玩具在第一个。

也就是说执行 $k$ 次 `DRUL` 即可。
## 3. $k > \lceil \frac{n}{2} \rceil$
考虑把第 $k$ 个挪到左边，继续乱手模，发现执行足够次 `DRUR` 会变成![](https://cdn.luogu.com.cn/upload/image_hosting/h3jilhic.png)这样。

再做一次 `LD` 操作就变为第 $2$ 种情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/1enhy4kf.png)
继续观察发现第一行最右侧不受影响,也就是说想办法把指定玩具操作到第一行最右侧。

我们会把左侧的玩具弄到最左侧，那么对称一下就可以了。

即做 $n-k-1$ 次 `DLUR` 再做 $n$ 次 `DRUR` 然后做 `LD`，就变为如图。（目标玩具为 `f`）![](https://cdn.luogu.com.cn/upload/image_hosting/wx4v1zyi.png)

观察一下发现只需做一次 `RURDL` 即可。
## 4.code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
signed main(){
    ios::sync_with_stdio(0);
    // auto i1=freopen("slpjbh.in","r",stdin);
    // auto i2=freopen("slpjbh.out","w",stdout);
    cin>>n>>k;
    n-=2;
    if(k==n/2+1){
        cout<<"DL";
        return 0;
    }
    if(k<=n/2){
        while(k--)cout<<"DRUL";
        return 0;
    }
    int t=n-k+1;
    while(t--)cout<<"DLUR";
    for(int i=1;i<=n;i++)cout<<"DRUR";
    cout<<"LDRURDL";
    // cout<<
    return 0;
}
```

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

[CF1817D](https://www.luogu.com.cn/problem/CF1817D)

#  思路：

一道有难度的构造题，我们可以借助[这个](https://assets.codeforces.com/files/56ff21637146a30d/game.html)，更好地完成题目。

容易发现，我们需要借助三个障碍，完成构造。

首先，对于最中间的方块，我们只需要借助最中间的障碍方块，进行一次 `DL` 即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/3l87p062.png?x-oss-process=image/resize,m_lfit,h_170,w_180)

对于在前一半的方块，可以通过借助第一个障碍方块，完成构造。很明显的是，第一个方块只需要执行 `L` 即可。在其他的方块中，对于第 $i$ 个方块，只需要循环 $i-1$ 次 `LDRU`，再执行 `L` 即可。以第二个方块为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/jybvjpis.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于后一半的方块就比较麻烦了，我们要借助中间和最后的两个障碍方块。我们可以仿效刚刚前一半的方法，循环执行 $n-2-k$ 次 `RDLU`，把目标方块移到最右侧，最后执行一次 `R`。以倒数第二个方块为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/brzopyi2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

一通操作结束后，通过思考，我们可以把所有的方块移动到中间障碍方块的左侧，并且让目标方块保持在最右侧，这需要我们循环执行 `LDLU` 即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/5exvhfg8.png?x-oss-process=image/resize,m_lfit,h_210,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/3zduqer1.png?x-oss-process=image/resize,m_lfit,h_175,w_225)

我们很轻松就可以借助最右侧的障碍方块，完成操作。只需要执行 `RDL` 即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/3l39rjxq.png?x-oss-process=image/resize,m_lfit,h_110,w_225)

# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	if(k==n/2)
	{
		cout<<"DL";
		return 0;
	}
	else if(k==1)
	{
		cout<<"L";
		return 0;
	}
	else if(k<n/2)
	{
		for(int i=1;i<=(k-1);i++)
		{
			cout<<"LDRU";	
		}
		cout<<"L";
		return 0;
	}
	else if(k>n/2)
	{
		for(int i=1;i<=(n-2)-k;i++)
		{
			cout<<"RDLU";
		}
		cout<<"R";
		int p=(n-2)-n/2;
		for(int i=1;i<=p;i++)
		{
			cout<<"LDLU";
		}
		cout<<"RDL";
		return 0;
	}
	return 0;
}
```

---

## 作者：hfjh (赞：0)

# CF1817D Toy Machine 题解
### 题意

有一个长 $n$ 宽 $2$ 的矩形游戏机。保证 $n$ 是奇数。

游戏开始之前，有 $n - 2$ 个玩具放在第一排中间的 $n - 2$ 个位置中（两个角除外）。编号从左到右依次为 $1$ 到 $n - 2$。第二行为空，其最左、最右和中心位置是障碍物。你可以控制玩具机向左、向右、向上、向下，分别用字母 $\texttt L$、$\texttt R$、$\texttt U$ 和 $\texttt D$ 表示。

操控时，所有玩具将同时沿相应方向移动，碰到另一个玩具、墙壁或障碍物停止。您的目标是将第 $k$ 个玩具移动到第一行最左边。给定 $n$ 和 $k$，构造一个最多使用 $1000000$ 次操作的方案。

### 题解

如果 $k$ 在左边，直接 $\texttt {LURD}$ 一直循环即可。

如果 $k$ 在中间，直接 $\texttt {DR}$。

如果 $k$ 在右边，比较难搞。

- 我们先考虑 $k = n - 2$，$k$ 在最后的情况，直接循环 $\texttt{LULD}$，最后形成如同图一的情况，直接 $\texttt{RDL}$。

- 对于平凡的情况我们考虑通过循环 $\texttt{RULD}$ 把这个点移动到最后位，然后通过上面的方法做。

![图一](https://cdn.luogu.com.cn/upload/image_hosting/9wyte0e1.png)
图一

---

## 作者：timefinder (赞：0)

第一道自己切的 CF 2700(+)。

---

题面中提供了网站，我们就从玩这个游戏开始构造。

为了方便，记总玩具个数 $n-2$ 为 $N$。

首先，容易想到如果 $k \leq \frac{N+1}{2}$，我们可以不停地 $\texttt{LDRU}$，直到把 $k$ 提到最前面。其原理在于，$\texttt D$ 操作把当前的第二个元素摁到第二行，保护其不受后面 $\texttt R$ 影响。$\texttt R$ 则把首项抛到后面去，再 $\texttt U$ 就能把第二项提至首位。

每一个元素大约需要 $4$ 次操作，因此其操作数接近 $4 \times \frac{N}{2}=2N$。

接下来考虑 $k> \frac{N+1}{2}$。有前面的想法铺垫，很自然地想到可以试图把 $k$ 移到最后面去（同前面对称，进行 $\texttt{RDLU}$）。紧接着，考虑一个一个地把前面的元素填到游戏机的后一半去，如图。这里 $k=6$，也就是要 $\texttt f$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wup6034j.png)

可以通过若干次 $\texttt{DRUR}$ 来完成这个操作。

接下来，就转换为 $k=\frac{N+1}{2}$ 的状况，同上即可。

这种状况，总计最多约 $3 \times 4 \times \frac{N}{2}=6N<1000000$ 次操作，满足要求。

**code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k,t,tot;
int main(){
	scanf("%d%d",&n,&k);
	n-=2;
	if(k<=(n+1)/2){
		k--;
		while(k--) cout<<"LDRU";
		cout<<'L';
	}else{
		t=(n+1)/2;
		while(++k<=n) cout<<"RDLU";
		cout<<'R';
		for(int i=1;i<=(n+1)/2;i++) cout<<"DRUR";
		t--;
		while(t--) cout<<"LDRU";
		cout<<'L';
	}
	cout<<'\n';
}
```

---

## 作者：Semsue (赞：0)

注意，这个做法几乎没有用到任何归纳，以及任何套路的构造方法。也没有用到可能有用的置换群的构造，属于瞪眼瞪出来的。所以可扩展性极差。

一个很自然的想法是我们需要用到一些 `LRDU` 的“组合技”来让第 $k$ 块更加靠近答案。

第一步观察，当我们的块是最中间的时候，只需要一步 `DL` 即可。但似乎没什么用。

仔细思考一下，我们想把一个块不断地往前挪，等价于把它前面的一个数挪到后面去。那么很自然的想法是把数卡到第一个黑格子上面，然后不让它往下走，再把它放到右边去，也就是 `LDRU`。

你惊喜的试了几次，发现好像不断执行 `LDRU` 就好了，可是当你试到后面时候发现不太行，原因是卡到了中间黑方格或后面下不来了。

现在我们还是需要往前挪，在通过一些手玩之后，还有一步比较有用的组合：`LDLU`。这可以把一些数卡到左边下面，这样再执行一遍 `DRUR` 就可以把原先的数放到等价于中间位置的那个地方了。

你又试了几次，发现太靠后的地方还是不太行，原因是会在 `U` 的那一步被卡住。换一种思路，把需要搞得数放到最右边，其他数卡到下边。

执行若干次 `LDLU` 直到它到了中间，然受执行 `LDRD`，把所求卡到右边下面，然后不断执行 `ULDL`，这样把左边上面也卡满。发现这样最后一个一定是所求的放个，最后再执行一遍 `RDL`。

分析一下，一开始会做 $\frac{n}{2}$ 次 `LDLU`，然后会做 $\frac{n}{2}$ 次 `ULDL`，于是总次数是 $4n+O(1)$ 的。

我以为我的做法很菜，但是标算好像也是 $4n+O(1)$ 步，那没事了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int main()
{
	cin >> n >> k;
	if (k <= n / 2)
	{
		for (int i = 1; i < k; i++) printf("LDRU");
		printf("L");
	}
	else if (k <= n / 2 + (n / 2) / 2)
	{
		for (int i = 1; i < k - n / 2; i++) printf("LDLU");
		printf("DRUR");
		for (int i = 1; i < n / 2; i++) printf("LDRU");
		printf("L");
	}
	else
	{
		for (int i = 1; i < k - n / 2; i++) printf("LDLU");
		printf("LDRD");
		for (int i = 1; i < n / 2; i++) printf("ULDL");
		puts("RDL");
		
	}
	return 0;
}
```

---

