# Georgia and Bob

## 题目描述

有一个无限长的棋盘，从左到右编号为 $1,2,3,\cdots$。有 $n$ 个棋子在棋盘上，定义一次操作为把一枚棋子向左移动至少一格，不可以逾越其他棋子，不可与其他棋子重合，不可移出棋盘。

告诉你这 $n$ 个棋子的位置（不保证顺序且保证没有棋子重合），Georgia 和 Bob 轮流进行操作，Georgia 先手，谁无法操作谁输。问最后谁会赢？

![](https://cdn.luogu.com.cn/upload/image_hosting/tti7635d.png)

## 样例 #1

### 输入

```
2
3
1 2 3
8
1 5 6 7 9 12 14 17```

### 输出

```
Bob will win
Georgia will win```

# 题解

## 作者：fish_love_cat (赞：8)

我居然过了以后没写这题题解诶？来补了来补了。

话说这题当时我写的时候还没有题解来着，怎么转眼这么多了。

---

只看每个点的移动是不好做的，我们试图想一个办法描述当前局面并从中寻找性质。

一个很好的方法是用点与点之间的间隔数来描述，每个棋子移动时都会减少左侧的间隔，并在右侧扩大相同的数目。

如果你学习过阶梯 nim 并做过 P3480，那么你已经会做了。

把每个间隔看成一堆有着对应数目的石子，每次操作会从左侧拿取若干并放到右侧的堆中，最后把所有石子堆在最右侧的人获胜。

这就是阶梯 nim 最标准的形式啊！

根据阶梯 nim 的经典结论我们知道：先手必败当且仅当奇数堆中的石子数异或和为 $0$。

套结论就做完了，代码略。

---

不给证明会被骂的吧。

我们注意到如果必败方对偶数堆进行操作，必胜方一定可以再移回偶数堆。

于是偶数堆没用，移到偶数堆相当于弃置。

那么奇数堆就等价于可以任意拿走若干石头，此时就是标准的 nim 游戏的形式了。

证明完毕。

---

## 作者：cybermage_liu (赞：3)

# 思路
Upd：修改了错别字并补充了部分内容。

前置芝士：[阶梯博弈](https://www.cnblogs.com/fu3638/p/7471184.html)

阶梯博弈结论：奇数阶梯（从 $0$ 开始编号）上的石子异或和非零则先手必胜，反之则后手必胜。

如题，每个棋子都只能向左走，不能逾越其它棋子。

这条性质很像阶梯博弈，但是棋子可以向左移动若干步，这并不利于阶梯博弈。

那怎么办？当然是考虑没放棋子的空格，假设当前考虑到第 $i$ 枚棋子。

* 不能逾越其它棋子，那么空格只能从 $i-1$ 和 $i$ 之间移动到 $i$ 和 $i+1$ 之间。  
* 棋子可向左移动 $a_i-a_{i-1}-1$ 步，那么当前有 $a_i-a_{i-1}-1$ 个空格可以移动。  

所有棋子最后移到所有空格的左边，也就是所有空格最后移到所有棋子的右边。

这不就是典型的阶梯博弈吗？每相邻两个棋子中间（第一个棋子前边）的空格为一个阶梯，倒序判断奇偶就可以过了。

时间复杂度 $O(Tn\log n)$。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010]; 
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+1+n);//注意排序
		a[0]=0;
		for(int i=n;i>=1;i-=2) ans^=a[i]-a[i-1]-1;//倒序判奇偶
		puts(ans?"Georgia will win":"Bob will win");
	}
}
```

---

## 作者：粥2414 (赞：2)

# 思路
## 本题
题目中对于棋子移动的要求相当苛刻，如下：
> 把一枚棋子向左移动至少一格，不可以逾越其他棋子，不可与其他棋子重合，不可移出棋盘。

模拟几次后发现，这样移动相当于将一个棋子左边的空格移动到其右边。发现其为阶梯 NIM，只要将棋子排序之后差分，转换为阶梯 NIM 之后就可以做了。
## 阶梯 NIM
如果你不知道怎么做阶梯 NIM，那么我再讲一下阶梯 NIM。

阶梯 NIM 定义如下：
> 每次可以从一个阶梯上拿掉任意数量石子放到下一层阶梯，不能操作的为输。

它的解法如下：  
只考虑奇数位上的石子，把其当作普通的 NIM 博弈做即可。

原因是如果操作偶数位上的石子，那么完全可以将其向下再挪回偶数堆。也就是对于偶数堆的操作是完全不会影响到奇数堆的。而对于奇数堆的操作，挪到第 $0$ 堆时就无法再移动。所以只有奇数堆会影响胜负。

严格的证明~~我不会~~，读者可以到网上查阅资料。

对于本题，由于我们是倒着做阶梯 NIM，所以需要根据 $n$ 的奇偶来决定是考虑奇数位还是偶数位。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read() {
	int x = 0, f = 1;
	char ch;
	while ((ch = getchar()) < 48 || ch > 57)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
const ll N=1e6+9;
ll t,n,a[N];
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		sort(a+1,a+n+1);
		for(int i=n;i>0;i--){
			a[i]=a[i]-a[i-1]-1;
		}
		ll che=n%2;
		ll ans=0;
		for(int i=che;i<=n;i+=2){
			ans^=a[i];
		}
		puts(ans==0?"Bob will win":"Georgia will win");
	}
	return 0;
}
```

---

## 作者：100Accepted (赞：2)

性质：阶梯 Nim。 
 
所有的棋子均无法越过左边的棋子，所以以所有棋子左边的空格数为阶梯 Nim 的各级数，当第 $i$ 个棋子向左移动时，阶梯第 $i$ 级台阶上的数减少，第 $i+1$ 级台阶上的数增加相同数量，最终的结果为前 $n-1$ 级台阶上的数为 $0$，即为倒反的阶梯 Nim，求其与 $n$ 相同奇偶性的台阶上的数的位异或和，和为 $0$，Bob 胜，否则 Georgia 胜。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t,n,z[1002],i,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%d",&n);
		for(i=1;i<=n;i++){
			scanf("%d",&z[i]);
		}
		sort(z+1,z+n+1);
		for(i=n;i>=1;i-=2)ans^=(z[i]-z[i-1]-1); //求棋子左边的空格数 
		if(ans)printf("Georgia will win\n");
		else printf("Bob will win\n");
	}
    return 0;
}
```

---

## 作者：MoonCake2011 (赞：2)

先对棋子的坐标排序。

$x_i-x_{i-1}-1$ 就是最开始棋子能移动的距离。

于是移动第 $i$ 个棋子，相当于将 $i+1$ 的移动范围扩大。

变为了一个台阶 nim 博弈。

每个台阶上的石子个数为 $x_i-x_{i-1}-1$，每次可以从 $i$ 推向 $i+1$。

直接变为判断所有奇数级台阶的异或值是否为 $0$。

## 证明

首先，只有奇数级台阶上没有石子时，对手推一些石子到奇数级台阶上，我们又把它们推到偶数级台阶上，所以先手必输。

奇数级台阶上没有石子，异或起来等于 $0$。

如果奇数级台阶上异或起来等于 $0$，那么下一步，不管推奇数台阶还是偶数台阶，都不能使奇数级台阶上异或起来等于 $0$。

奇数级台阶上异或起来不等于 $0$，是可以让奇数级台阶上异或起来等于 $0$。

故成立。

于是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100010];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=n;i>=1;i-=2) ans^=a[i]-a[i-1]-1;
	if(ans) cout<<"Georgia will win\n";
	else cout<<"Bob will win\n";
	return;
} 
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：HirasawaYuii (赞：1)

# P10507 Georgia and Bob 题解

[题目链接](https://www.luogu.com.cn/problem/P10507)

## 题目大意

一个一行的棋盘，棋盘上有 $n$ 个棋子，两人轮流选择一枚棋子向左移动若干格（会被其他棋子阻拦），询问谁必赢。

## 解题思路

显然为博弈论。注意到对于两个相邻（指棋子，不是位置）的棋子，若先手移动了左边的棋子若干格，后手也能移动右边的棋子相同的步数，所以对于相邻两对棋子中间的间隔是对结果没有影响的（先后手一人一次解决）。于是问题转化为了怎么处理一对棋子的间隔。显然，一对棋子间的间隔可以类比为石子，转化为 Nim 游戏。特别的，若棋子数为单数，则将第一枚棋子与边界 $0$ 组成一对。

为便于读者理解，给出一个具体的游戏过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/7if40zym.png)

于是，问题就转为了计算一对棋子间隔的 Nim 游戏，将奇数位置的间隔取异或和再判断是否为 $0$ 即可。

## 代码

```c++
// Problem: P10507 Georgia and Bob
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10507
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Date: 2025-02-07 09:49:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define mst(x, y) memset(x, y, sizeof(x))
#define pii pair<int, int>
#define fi first
#define se second
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)

int read(){int x = 0, f = 1;char c = getchar();while(c < '0' || c > '9'){if(c == '-') f = -1;c = getchar();}while(c >= '0' && c <= '9'){x = 10*x+c-'0';c = getchar();}return f*x;}
void writ(int x){if(x < 0){putchar('-');x = -x;}if(x > 9) writ(x/10);putchar(x%10 | 0x30);return;}
void write(int x){writ(x);puts("");}
void wr(int x){writ(x);putchar(' ');}
const int N = 1005, inf = 0x3f3f3f3f;

int n, a[N], t, res;

void init(){
	t = read();
}
void solve(){
	while(t--){
		n = read(), res = 0;
		for(int i = 1;i <= n;i++) a[i] = read();
		sort(a+1, a+1+n);
		if(n&1) for(int i = 1;i <= n;i += 2) res ^= (a[i]-a[i-1]-1);
		else for(int i = 2;i <= n;i += 2) res ^= (a[i]-a[i-1]-1);
		if(res) puts("Georgia will win");
		else puts("Bob will win");
	}
}

signed main(){
	init();
	solve();
	return 0; 
}
```

---

## 作者：Wilderness_ (赞：1)

## 思路
一道阶梯 Nim 游戏。

我们不难想到两颗棋子相邻是一种必败状态，所以我们可以先将棋子排序后两两绑定。然后我们可以将每组两个棋子之间的空格看作一堆石子。这就变成 Nim 游戏的形式，对于其中的第 $i$ 组棋子，将右端点的棋子向左移动 $x$ 格就相当于 Nim 游戏中从第 $i$ 堆石子中取走 $x$ 颗。

然而，第 $i$ 组棋子左端点的棋子向左移动 $x$ 格相当于 Nim 游戏中在第 $i$ 堆石子中加入 $x$ 颗石子。这显然与普通 Nim 游戏不相同。但是，即使石子的数量增加了，只要将右端点也左移 $x$ 颗，这一堆石子就回到原先的状态。因此，移棋子的胜负状态应该和类比出来的 Nim 的胜负状态是一样的。

对于 $n$ 为偶数的情况，直接如上求 Nim 和；对于 $n$ 为奇数的情况，我们可以在序列前端加入一个 $0$ 号棋子（也就是将 $1$ 号棋子的左边也算作一堆石子）即可。
## Code：
```cpp
#include<bits/stdc++.h>
#define M 21414
using namespace std;
int v[M];
int main()
{
    int T,n,ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&v[i]);
        sort(v+1,v+n+1);
        if(n&1)
        {
            ans=v[1]-1;
            for(int i=3;i<=n;i+=2)
                ans=ans^(v[i]-v[i-1]-1);
        }
        else
        {
            ans=v[2]-v[1]-1;
            for(int i=4;i<=n;i+=2)
                ans=ans^(v[i]-v[i-1]-1);
        }
        puts(ans?"Georgia will win":"Bob will win");
    }
    return 0;
}
```
对于中间的分类讨论实际上可以缩减如下：
```cpp
while(T--)
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&v[i]);
    ans=0;
    if(n&1)v[++n]=0;
	sort(v+1,v+n+1);
    for(int i=2;i<=n;i+=2)
        ans=ans^(v[i]-v[i-1]-1);
    puts(ans?"Georgia will win":"Bob will win");
}
```

---

## 作者：Charles_with_wkc (赞：1)

### 前置知识：
[Nim 游戏](https://www.luogu.com.cn/problem/P2197) /[Nim 游戏相关内容](https://www.cnblogs.com/BigSmall-En/p/nim.html)

### 分析：
这道题目首先要对棋子的坐标进行排序。我们不难发现，其实本道题目就是一个台阶Nim博弈。每个台阶上的石子数，我们可以推一下，结果是 $a_i-a_{i-1}-1$，直接变为判断所有**奇数级**台阶的**异或值** $=0$ 还是 $\ne 0$。

### 证明：
如果奇数级台阶上**没有**棋子，对手将棋子推到奇数级台阶上，我们不棋子推到偶数级台阶上，先手必输。奇数级台阶上**异或**起来 $=0$。  
如果奇数级台阶上**有**棋子，对手将棋子推到偶数级台阶上，我们就可以将棋子推到奇数级台阶上。这样奇数级台阶的**异或**结果一定 $=0$。  
在这种情况下是**不存在**输出  $\text{Not}$ $\text{sure}$ 只要异或结果 $\ge 1$，我们就获胜，否则对手赢。

### 核心代码：
```cpp
sort(dp+1,dp+1+n);//排序 
dp[0]=0;//利用dp[0]来存储 
for(int i=n;i>=1;i-=2){//奇数级台阶 
dp[0]^=dp[i]-dp[i-1]-1;//台阶 Nim 游戏 
}
if(dp[0]>=1){//等价于if(dp[0]) 
cout<<"Georgia will win\n";
}
else{
cout<<"Bob will win\n";
}
```
完整代码，没有注释[链接](https://www.luogu.com.cn/paste/ig0yp7vt)。

---

## 作者：Camellia2025 (赞：0)

## solution

发现若只有两个棋子，当它们挨在一起的时候，是一个先手必败的局面，因为先手只能移动前一个棋子，后手只需移动和先手一样的距离，保持跟在先手后面一个格子，那么最后先手无路可走。

那么考虑两两拆分，若棋子数为奇数则添一个为零的棋子，那么对于每一对棋子，只需要计算它们间的间隔，就类似于 Nim 游戏，看它们的异或和，为零就先手必败，否则就先手必胜。

## code

```
#include <bits/stdc++.h>
using namespace std;

int main () {
	int t;
	cin >> t;
	while (t--) {
		int n, a[100010] = {}, sum = 0;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		sort (a + 1, a + 1 + n); 
		for (int i = n; i > 0; i -= 2) sum ^= (a[i] - a[i - 1] - 1);
		if (sum) cout << "Georgia will win";
		else cout << "Bob will win";
		cout << endl;
	}
	return 0;
} 
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Analysis]}}$

> 这是一道很好的博弈论的题目。

首先，不难发现这题最极端的必败情况是所有的石子都两两相邻。因为两两相邻的话先手无论对哪一堆石子进行多少距离的移动，后手都可以对开始时**在它后面和它相邻**（可以发现一定有，因为两堆相邻的石子必然只能移动前面的那一堆）的那一堆石子移动**相同的**距离，这样，两堆石子仍然相邻，且先手一定更先无路可走。

那就都往这个方向靠。既然石子被移动到两两相邻的状态后的最终输赢已经和移动方案无关，那么胜负就取决于谁最后一次移动把石子移动到这个状态。把石子两两相邻的状态成为**决定状态**。设 $p_{i}$ 表示第 $i$ 堆石子的位置。

- 如果 $n$ 为偶数，那么**决定状态**一定是第 $1,2$ 两堆石子相邻，第 $3,4$ 两堆石子相邻，……，第 $(n-1),n$ 两堆石子相邻。问题进一步抽象后，相当于有 $p_{2}-p_{1}-1,p_{4}-p_{3}-1,\dots,p_{n}-p_{n-1}-1$ 共 $\dfrac{n}{2}$ 堆“石子”，两人轮流操作，可以在任意一堆取任意多，谁最后一个操作谁赢。这就是典型的 Nim 游戏。

- 如果 $n$ 为奇数。最终第 $1$ 堆石子一定被移动到第 $1$ 号格子，可以理解成在第 $0$ 号格子还有一堆“石子”。**决定状态**是第 $0,1$ 两堆石子相邻，第 $2,3$ 两堆石子相邻，……，第 $(n-1),n$ 两堆石子相邻。相当于有 $p_1-1,p_{3}-p_{2}-1,\dots,p_{n}-p_{n-1}-1$ 共 $\dfrac{n+1}{2}$ 堆石子，依然是一个 Nim 游戏。

很巧妙的转化，很不错的题目。

$\color{blue}{\text{Code}}$

```cpp
const int N=1010;

int n,Nim,pos[N],T;

int main(){
	for(int Case=1,T=read();Case<=T;Case++){
		Nim=0;
		
		n=read(); 
		for(int i=1;i<=n;i++)
			pos[i]=read();
		
		sort(pos+1,pos+n+1);
		
		for(int i=n;i>=1;i-=2)
			Nim^=(pos[i]-pos[i-1]-1);
		
		if (Nim==0) puts("Bob will win");
		else puts("Georgia will win");
	}
	
	return 0;
}
```

---

## 作者：w9095 (赞：0)

[P10507 Georgia and Bob](https://www.luogu.com.cn/problem/P10507)

这篇题解的注重点不是结论的证明，而是发现结论的思路，所以比较偏感性。证明人人都会，而发现结论的思路才是这题真正值得思考的地方。

感觉这道题不知道阶梯 NIM 自己推出来也不难，在这个建模下思路挺顺的。感觉讲解阶梯 NIM 可以采用这个模型。

显然的博弈论题目，但是局面不好表示，这种情况经典的转化是寻找一个可以刻画局面的特殊量。

考虑到每一次移动棋子只与它与它的前驱之间的距离有关，因此不难想到本题刻画局面的特殊量与相邻元素的差分有关。于是，我们在差分数组上进行分析。

我们又想到，如果先手某一次移动了某一个棋子，那么后手一定可以把这个棋子的后继棋子移动相同的距离。而这个时候，除了这个棋子与这个棋子的后继棋子的后继棋子的差分，其余的差分值是都没有改变的。不考虑这两个棋子的改变，这种操作就是无意义的，因为它什么都没有改变。而且这种情况下后手一定可以这么操作，因为不劣。我们希望构造一个特征量这种操作无意义，因为可以简化局面。

我们再来考虑改变的两个棋子有什么性质。我们发现这两个棋子的排名奇偶性相同，这引导我们思考把棋子按照排名奇偶性分类。再结合希望可以使这种操作无意义，我们希望能构造出一种刻画局面的方式使排名为奇数或者偶数的棋子的差分在某一次操作中的改变可以被忽略。

注意到希望可以被忽略改变的棋子正好也是被先手操作的棋子，而先手又不会操作这些棋子，因为这种操作是无意义的，不优。那我们为什么不直接在局面中删去奇数或偶数棋子中一个的差分呢？

由于最后一个棋子的影响不能忽略，那我们选取从后往前排名为偶数的棋子的差分忽略。这样，每一次操作只能对奇数棋子操作。如果对偶数棋子操作，后手可以立刻对后继棋子进行相同的操作。由于这个棋子与这个棋子的后继棋子的后继棋子都是偶数，它们差分的改变刚好可以被忽略。于是，我们只使用奇数棋子的差分刻画了状态。

最后，再来考虑奇数棋子怎么拿。我们发现在它的差分减一范围内可以随便取多少，因为不会超过上一个偶数棋子。因此，奇数棋子就相当于 NIM 游戏里的一堆石子，这一堆里共有它的差分减一个石子。至此，我们成功将问题转化为了经典的 NIM 博弈问题。

想看理性证明的可以去看别的题解，写的绝对比我这个胡说八道的感性理解好。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[10000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	   	sort(a+1,a+n+1);
	   	long long sum=0;
	   	for(int i=n;i>=1;i-=2)sum^=(a[i]-a[i-1]-1);
	   	if(sum)printf("Georgia will win\n");
	   	else printf("Bob will win\n");
	   }
	return 0;
}
```

---

## 作者：DDF_ (赞：0)

这题我其实也想了很久，正巧最近学了 NIM 博弈，所以来交一发。

## 题面

在一个 $1$ 行无限长的棋盘上，每个格子上有棋子。先后操作，把棋子往左移，不超越边界和其他棋子，最后无法操作的人输，求赢家。

## 题解

很容易可以想到这是一题博弈论。

首先，如果一个棋子往左移，很容易想到它左边的棋子与它的间距会变小，而它与它右边的棋子的间距会变大。

这是我们就可以想到阶梯 NIM 游戏：

> 有 $n$ 堆石子，先后操作，每次把第 $i$ 堆的石子移动到第 $i-1$ 堆，求赢家。

可以看到，这个题目就是阶梯 NIM 反过来了，然后石子数为棋子之间的间距而已。

定义 NIM 和为数的异或和，则有阶梯 NIM 游戏的结论：先手存在必胜策略，当且仅当奇数位的石子数 NIM 和不是 $0$。

如何证明？这时就要想到 NIM 游戏三个定理：

- 没有后继状态的状态为必败状态。
- 后继状态皆为必胜状态的为必败状态。
- 后继状态有一个必败状态的为必胜状态。

首先，所有石子都在第 $0$ 个格子，为必败状态，此时奇数位的 NIM 和为 $0$。

其次，假设有一个必败状态为后继状态，那一定有一种移动使得对方必败，而根据 NIM 和的定义，假设此时 NIM 和不为 $0$，则此时肯定有一个 $k$ 使得原先的 NIM 和异或 $k$ 为 $0$。

再来，假设后继状态都为必胜状态，则此时我方必败，而根据 NIM 和的定义，假设 NIM 和为 $0$，使得 NIM 和继续为 $0$ 的方案只有不动任何石子。

在阶梯 NIM 中，如果一方移动，使奇数位 NIM 和为 $0$，那么另一方此时进入了必败状态。如果他移动奇数位的石子，则一定会使奇数位的石子 NIM 和不为 $0$，使自己必败；如果他移动偶数位的石子，则可以将他移过来石子往下再移动一位，使得他再次陷入必败状态。

那么对于此题，就可以推出类似的结论。

时间复杂度 $O(T \times n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[1002],p;
void solve() {
    scanf("%d",&n);
    p=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(int i=n;i>0;i-=2) p^=a[i]-a[i-1]-1;
    if(p) puts("Georgia will win");
    else puts("Bob will win");
    return;
}
int main() {
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}

---

## 作者：封禁用户 (赞：0)

## 思路

对棋子坐标排序，$x_{i}-x_{i-1}-1$ 就是棋子可以移动的距离。

移动第 $i$ 个棋子，相当于将 $i+1$ 的移动范围扩大。

这于是变形成了一个台阶 nim 博弈论。

易得，这道题直接变成判断所有奇数级台阶。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100010];
int main() {
	int t;
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=n; i>=1; i-=2) ans^=a[i]-a[i-1]-1;
		if(ans) cout<<"Georgia will win\n";
		else cout<<"Bob will win\n";
	}
	return 0;
}

```

---

## 作者：ggylz49 (赞：0)

## 解法
阶梯 Nim。

首先观察到**不保证顺序且保证没有棋子重合**，首先进行**排序**。

对于表示棋子位置的序列 $a$，$a_i-a_{i-1}-1$ 就是最开始棋子能向左移动的距离。若我们移动 $i$ 号棋子，则第 $i+1$ 号棋子的移动范围变大。对于这个台阶 Nim，每个台阶上的石子有 $a_i-a_{i-1}-1$ 颗。

假设所有奇数级台阶上都没有石子，异或起来是 $0$。

对手将石子移动到奇数级台阶上时，我们就可以把石子又移动到偶数级台阶上，于是先手必输。所以奇数级台阶异或后的值为 $0$，先手输，`Bob` 胜利；否则 `Georgia` 胜利。
## Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,ans=0,a[10010];
        cin>>n;
        for (int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1);//排序
        for (int i=n;i>0;i-=2)ans^=(a[i]-a[i-1]-1);//计算异或值
        if (ans!=0)puts("Georgia will win");//异或值不是0，先手胜
        else puts("Bob will win");//否则后手胜
    }
    return 0;
}
```

---

