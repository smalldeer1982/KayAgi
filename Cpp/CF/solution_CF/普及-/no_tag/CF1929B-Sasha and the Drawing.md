# Sasha and the Drawing

## 题目描述

即使在幼儿园，Sasha 也喜欢一个女孩。因此，他想给她一幅画，并吸引她的注意力。

作为绘画，他决定绘制一个大小为 $n\times n$ 的正方形网格，其中染色的一些单元格。但是着色单元格很困难，因此他希望尽可能少地染色。但与此同时，他希望至少有 $k$ 条对角线至少有一个染色单元格。注意，大小为 $n \times n$ 的正方形网格总共有 $4n - 2$ 条对角线。

帮助小 Sasha 让女孩爱上他，并告诉他需要染色的最少单元格数。

## 说明/提示

下面的图片中，黑色标记染色单元格，所有对角线标记为紫色。

在第一个测试用例中，您可以染色 $2$ 个单元格，以使 $4$ 条对角线包含至少一个染色单元格。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929B/4864b78fe9eb050caf4657b8002f6908e15fc9d0.png)

在第三个测试用例中，您可以染色 $6$ 个单元格，以使所有 $10$ 条对角线都包含至少一个染色单元格。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929B/739c9b82a674c23c09f172f9a61b92f42e5cc20b.png)

## 样例 #1

### 输入

```
7
3 4
3 3
3 10
3 9
4 7
7 11
2 3```

### 输出

```
2
2
6
5
4
6
2```

# 题解

## 作者：CaoXian (赞：9)

发现一个格子恰好会被两条对角线经过，所以选择格子的时候我们会贪心地先选**经过格子的两条对角线都还没被覆盖的格子**，也就是选择会对**总覆盖对角线数**产生 $2$ 的贡献的格子。

但是选了一些格子后，剩下的格子最多只会对总覆盖对角线数产生 $1$ 的贡献了，但是具体是选了多少格子后？因为一组同向对角线共有 $2n - 1$ 条，而在这一组中两条只占一个格子的对角线只经过同一条异向对角线，这两个格子不可能同时产生 $2$ 的贡献，而其它的都可以。所以我们在选了 $2n - 1 - 1 = 2n - 2$ 个格子后，剩下的格子只会对总覆盖对角线数产生 $1$ 的贡献了。

这一点体现到方案上就是：先选最上面一排的格子，再选最下面一排除了两端的格子，最后选最下面一排两端的格子。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t, n, k;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> n >> k;
		if(k <= 4 * n - 4) cout << ((k + 1) >> 1) << '\n';
		else cout << 2 * n - 2 + k - 4 * n + 4 << '\n';
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：5)

$n\times n$ 的正方形网格中，求至少要涂黑多少个格子，使得网格有至少 $k$ 条从左上到右下或从右上到左下的对角线，至少一个它经过的格子是黑色的。$n\times n$ 的正方形网格一共有 $4n-2$ 条对角线。

$n\le10^8$，$k\le4n-2$。

---
容易发现，一个格子涂黑，最多使两条对角线有黑色格子。

分类讨论。当 $k<4n-2$ 时，考虑让每条对角线都只有一个黑色格子，即只涂第一行和最后一行，此时答案的是 $\lceil\dfrac{n}{2}\rceil$。

当 $k=4n-2$ 时，每条对角线都要有一个黑色格子，而从 $(1,1)$ 到 $(n,n)$ 的对角线和从 $(1,n)$ 到 $(n,1)$ 的对角线要有两个黑色格子。把角上四个格子剔除掉，有黑色格子的对角线只剩下 $4n-8$ 个，此时需要涂黑 $2n-4$ 个格子。加上角上四个就是 $2n$ 个。当第一行和最后一行全部涂满时可以取到。

---

## 作者：All_Unluck_Beginning (赞：1)

# CF1929B

## 题意

给定一个 $n\times n$ 的正方形，已知正方形最多有 $4\times n-2$ 条对角线，要求要有至少 $k$ 条对角线经过至少一块黑色方格，求至少要将几条对角线涂成黑色。

## 分析

### 分类讨论：
- 当 $k<=4\times n-4$ 时，就只需要在上下两侧图就行，所以答案是 $[\frac{k}{2}]$。
- 当 $k>4\times n-4$ 时，则答案是 $k-2\times n+2$。

当 $n==4,k==12$ 时：
![](https://cdn.luogu.com.cn/upload/image_hosting/hu6som4v.png)

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(k<=4*n-4)cout<<(k+1)/2;//千万不能写ceil（k*1.0）/2 
		else cout<<k-2*n+2;
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

简单的规律题。

注意到样例给的提示图：

![Image 1](https://espresso.codeforces.com/c88e80de5be4f91764dbe5bdc534c50fec115db3.png)

注意到每个格子都可以贡献两条对角线，所以答案就是 $\dfrac{k}{2}$。

那再看第二组样例：

![Image 2](https://espresso.codeforces.com/624a36083689f6fb20bf243e5d1707fdcd71ef60.png)

可以发现对于奇数要求的 $k$，显然我们会有一个格子多贡献一条对角线，答案是 $\dfrac{k}{2} + 1$。

[Submission](https://codeforces.com/contest/1929/submission/246746431)


---

## 作者：_Chjich_ (赞：0)

# 题目大意
有 $1$ 个 $n\times n$ 的方格，涂黑方格使 $k$ 条对角线要能经过黑色方格。

# 思路
- 当 $k < n \times 4 - 2$ 时，涂黑一个方格可已让两条对角线经过：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929B/4864b78fe9eb050caf4657b8002f6908e15fc9d0.png)

所以涂黑 $\lceil \frac{k}{2} \rceil$ 个方格就行。
- 当 $k = n \times 4 - 2$ 时，把上下涂黑就行：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929B/739c9b82a674c23c09f172f9a61b92f42e5cc20b.png)

所以涂黑 $n\times 2$ 个方格。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
long long T, a, b;

int main() {
	cin >> T;
	while (T--) {
		cin >> a >> b;
		if (b == a * 4 - 2) {
			cout << 2 * a << endl;
			continue;
		}
		cout << (b + 1) / 2 << endl;//不要写成ceil，否则会错。
	}
	return 0;
}
```

---

## 作者：RainCQwQ (赞：0)

# CF1929B Solution
## 思路分析
显而易见，每涂黑一个单元格，会增加两条存在染色格的对角线。

但是，特殊的，在 $k = 4n - 2$ 的时候，我们不得不涂满 $2n$ 条边才能满足条件，例如题目中的样例。

![CF1929B 样例#3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929B/739c9b82a674c23c09f172f9a61b92f42e5cc20b.png)

我们需要涂满上边界与下边界（或是左边界和右边界）才能满足条件。

整理一下：

1. $k < 4n - 2$ 时，输出 $\lceil \frac{k}{2} \rceil$。
2. $k = 4n - 2$ 时，输出 $2n$。

## Code
```cpp
#include <iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		if(k<4*n-2) cout<<(k+1)/2<<endl;
		else cout<<2*n<<endl;
	}
	return 0;
}
```

---

## 作者：yuanshen362 (赞：0)

## 题意分析

在 $n\times n$ 大小的格子里涂最少数量的格子，使得至少有 $k$ 条对角线上至少有 $1$ 个涂黑的格子。

## 题目解决

这样的题，就是找规律的。在纸上画一画，就能知道在一般情况下每两条对角线相交会有一个格子，那么就按照这样的方法涂就能求出至少涂的格子数。那么答案就是 $\lceil \frac{k}{2} \rceil$，即如果对角线不能两两相交时，就拿出一条对角线单独画格子。

但是，注意到特殊情况。你会发现当 $k$ 的值为所有格子的对角线数量，即如题目中所说的 $4n-2$，那么**必定不能**实现两两相交，这种情况下，通过实践可以发现此时的答案是 $2n$。

到这里，整个问题就结束了。下面是给刚学 OI 的同学的提醒：

不知道为什么，如果你使用 double 类型运算时，CF 平台会识别到这个数是 double 类型。但是这里输出的数是整数，所以你应该强制转换一下类型。当然，直接使用 int 类型也是可以的，就是写一个分支。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
double n, k;//使用double方便做除法 
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		if(k == 4 * n - 2)cout << int ((k + 1.0) / 2)<<endl;
		else cout << int(ceil(k / 2)) << endl;//注意要强制转换 
	}
	return 0;
}
```

---

## 作者：QoQ_ (赞：0)

- [题目传送门](https://www.luogu.com.cn/problem/CF1929B)

~~审了 n 次总该过了吧？~~

首先我们来分析一下此题：

在 $n \times n$ 的画中要有 $k$ 个对角线都包含至少 $1$ 个涂了颜色的格子，求出涂色最少且符合条件的格子数量。

我们再来观察一下样例：

在 $k$ 不等于最多对角线的情况下，如果 $k$ 是偶数，那么答案就是 $\frac{k}{2}$，如果是奇数，那么答案就是 $\frac{k}{2}+1$。

其实这也很好理解，是偶数时，一个格子涂色可以满足两个对角线的需求，一共有 $k$ 个对角线，只需要涂 $k$ 中一半的格子，故为 $\frac{k}{2}$。当 $k$ 是奇数时，先涂上 $\frac{k-1}{2}$ 个格子，你就会发现，还差一条对角线，也就是说只要再涂一个格子，这个时候如果你涂的格子满足了两条对角线，又多出了一条，所以最后这一个格子只能涂在已经有一条对角线被满足了的格子，具体如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/66h5u0zg.png)
这样这个格子就只多满足了一条对角线，所以公式为 ${\frac{k-1}{2}+1}$，因为 c++ 有自动舍去余数，所以前面的 $k-1$ 就不用了。


最后来讲讲当 $k$ 刚好等于最多对角线的情况，如果刚好等于，我们可以把左右两侧涂色，刚好满足了所有的对角线，而左边与右边正好为画的边长，为 $n$，那么两边加起来，也就是 $2n$。

### code 参考

```
#include<bits/stdc++.h>
using namespace std;
int n,k,T;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        if(n*4-2==k){
            printf("%d\n",n*2);
        }else if(k%2==0){
            printf("%d\n",k/2);
        }else if(k%2!=0){
            printf("%d\n",k/2+1);
        }
    }
    return 0;
}
```
没有注释，~~方便食用~~。

这也是本蒟蒻的第一篇题解，求过 QAQ~

---

## 作者：Jorisy (赞：0)

发现一个黑色格子可以使两条方向相反的对角线合法。

因此 $k<4n-2$ 时，每两条线就可以将一个格子涂黑，故答案为 $\left\lceil\dfrac k2\right\rceil$。

$k=4n-2$ 时，我们可以在最左列、最右列全部涂黑，因此答案就是 $2n$。

---

## 作者：无名之雾 (赞：0)

# Sasha and the Drawing 题解

## 思路

我们可以粗略的将格子中每个格子被对角线穿过的最大次数标记如下，按照以下表格模拟即可。

当 $n$ 为奇数时：
```
2  2  2
0  0  0 
1  2  1
```
当 $n$ 为偶数时：
```
2  2  2  2
0  0  0  0
0  0  0  0
1  2  2  1


```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[105];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main(){
	int t=read();
	while(t--){
		n=read(),k=read();
		int x=n*2;
		if(x>=k){
			if(k%2==1)cout<<k/2+1;
			else cout<<k/2;
		}
		else{
			k-=x;
			int y=2*(n-1);
			if(y>k){
				if(k%2==1)cout<<n+k/2+1;
				if(k%2==0)cout<<n+k/2;
			}
			else if(y==k)cout<<n+k/2+1;
			else{
				k-=y;
				cout<<2*n+k;
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/1929/B)|[链接](https://www.luogu.com.cn/problem/CF1929B)

### 题目大意

给出 $n \times n$ 的方格，求最少染色多少个方格，使得有至少 $k$ 条对角线穿过了染色方格。

### 题目分析

若 $k \le 4n-4$，答案为 $\lceil\frac{k}{2}\rceil$。否则为 $k-2n+2$。

画图分析。

![](https://cdn.luogu.com.cn/upload/image_hosting/rmth8itz.png)

图中的 $2n-2$ 个红格子可以使 $2$ 条紫对角线满足要求，此时最多有 $4n-4$ 条对角线满足要求，为情况 $1$。

若填完红格子后仍需对角线，只需填涂蓝格子，每格可以使 $1$ 条粉对角线满足要求，最多 $4n-2$ 条对角线。格数 $\frac{4n-4}{2}+k-(4n-4)$，化简后为 $k-2n+2$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		printf("%d\n",k<=4*n-4?(k+1)>>1:k-2*n+2);
	}
	return 0;
}
```
感谢阅读。

---

## 作者：Lemon_zqp (赞：0)

### 思路
这题简单结论题。首先我们可以发现每个彩色格子至多可以让两条对角线有至少一个彩色格子（两个边角只能让三条对角线有至少一个彩色格子）并且只要对最上面那一行和最下面那一行上色，在其它地方上色就等于浪费。所以，当 $k = 4 \times n - 2$ 时，代表所有对角线都要有至少一个彩色格子。不难发现，我们如果要让所有对角线都至少有一个彩色格子，必须把第一行和最后一行全部涂成彩色的。当其它情况时，我们知道，每个格子可以让两条线满足要求，只要看一下要涂多少个格子满足要求即可，并且选的时候尽量不选四个边角，才能使涂颜色的格子最少。也就是说，如果 $k \le 2 \times (n-2)$，只需要涂 $\left \lceil \frac{k}{2}  \right \rceil $ 个格子，如果涂 $\left \lfloor \frac{k}{2} \right \rfloor $ 就会不满足 $k$ 条，只要加一也可以解决。如果 $k > 2 \times (n-2)$，那么涂一个边角格子共增加 $2$ 条边，涂两个边角格子共增加 $3$ 条边，涂三个边角格子共增加 $5$ 条边，涂四个边角格子共增加 $6$ 条边。所以可以发现，即使 $k > 2 \times (n-2)$ 答案跟  $k > 2 \times (n-2)$ 情况下的还是一样，不用特别判断。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		if(m == (n * 4 - 2)){
			cout << 2 * n << endl;
			continue;
		} 
		if(m % 2 == 0){
			cout << m / 2 << endl;
		}
		else{
			cout << (m / 2) + 1 << endl;
		}
	}
	return 0;
}
```


---

