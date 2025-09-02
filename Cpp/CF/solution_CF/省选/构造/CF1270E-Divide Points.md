# Divide Points

## 题目描述

You are given a set of $ n\ge 2 $ pairwise different points with integer coordinates. Your task is to partition these points into two nonempty groups $ A $ and $ B $ , such that the following condition holds:

For every two points $ P $ and $ Q $ , write the [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance) between them on the blackboard: if they belong to the same group — with a yellow pen, and if they belong to different groups — with a blue pen. Then no yellow number is equal to any blue number.

It is guaranteed that such a partition exists for any possible input. If there exist multiple partitions, you are allowed to output any of them.

## 说明/提示

In the first example, we set point $ (0, 0) $ to group $ A $ and points $ (0, 1) $ and $ (1, 0) $ to group $ B $ . In this way, we will have $ 1 $ yellow number $ \sqrt{2} $ and $ 2 $ blue numbers $ 1 $ on the blackboard.

In the second example, we set points $ (0, 1) $ and $ (0, -1) $ to group $ A $ and points $ (-1, 0) $ and $ (1, 0) $ to group $ B $ . In this way, we will have $ 2 $ yellow numbers $ 2 $ , $ 4 $ blue numbers $ \sqrt{2} $ on the blackboard.

## 样例 #1

### 输入

```
3
0 0
0 1
1 0
```

### 输出

```
1
1 ```

## 样例 #2

### 输入

```
4
0 1
0 -1
1 0
-1 0
```

### 输出

```
2
1 2 ```

## 样例 #3

### 输入

```
3
-2 1
1 1
-1 0
```

### 输出

```
1
2 ```

## 样例 #4

### 输入

```
6
2 5
0 3
-4 -1
-5 -4
1 0
3 -1
```

### 输出

```
1
6 ```

## 样例 #5

### 输入

```
2
-1000000 -1000000
1000000 1000000
```

### 输出

```
1
1 ```

# 题解

## 作者：__OwO__ (赞：17)

发现题解取都是四染色,
发一个二染色的方法.

考虑对格子黑白染色,
坐标和为偶数的染为黑色.
这里我们先假设黑白色都有.

如果所有点分为黑白两组,
满足组间的边为黄色,
组内的边为蓝色,
那么黄色的边平方一定是奇数,
蓝色边的平方一定是偶数,
满足题目条件.

那么我们直接输出即可.

如果只存在一种颜色的点,
假设只存在黑点,
如果只有白点可以全部下移一格转为全为黑点.

现在我们把所有点的坐标由 $(x,y)$ 变为 $(\frac {x+y} 2,\frac{x-y}2)$ ,
即进行旋转,
因为全都是黑点那么不会出现小数,
那么如果这时候分为了黑白点就可以由之前的方法解决,
如果还是只有一种颜色就继续递归旋转

现在证明递归的次数为 $\mathcal O(\log A)$ 次,
其中 $A$ 为值域大小.

我们发现旋转一次一个点到原点的距离的平方除以了二,
但是一个点永远不会变成原点,
且一直是整点,
所以最多会旋转 $\mathcal O(\log A)$ 次.

代码

```cpp
#include <bits/stdc++.h>
#define il inline
#define _for(i, a, b) for (int i = (a); i <= (b); ++i)
#define _fore(i, u) for (int i = hd[u], v; v = tg[i], i; i = nx[i])
using namespace std;
struct {
    template <typename T>
    il operator T() {
        T x = 0, f = 1;
        char c = getchar();
        while (!isdigit(c)) (c == '-') && (f = -1), c = getchar();
        while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
        return f * x;
    }
} gi;
const int N = 1e3 + 5;
int n, x[N], y[N];
int s[N], ts;
int main() {
    n = gi;
    for (int i = 1; i <= n; ++i) x[i] = gi, y[i] = gi;
    while (1) { // 循环递归旋转
        int _a0 = 1, _a1 = 1; // _a0 : 是否全为黑点, _a1 : 是否全为白点
        for (int i = 1; i <= n; ++i) _a0 &= !((x[i] + y[i]) & 1), _a1 &= (x[i] + y[i]) & 1;
        if (!_a0 && !_a1) { // 如果黑白点都有
            for (int i = 1; i <= n; ++i)
                if ((x[i] + y[i]) & 1) s[++ts] = i; // 存答案
            break;
        }
        if (_a1) // 如果全是白点, 那么下移一格(上移也可)
            for (int i = 1; i <= n; ++i) x[i]--;
        for (int i = 1, x0, y0; i <= n; ++i) x0 = x[i], y0 = y[i], x[i] = (x0 + y0) >> 1, y[i] = (x0 - y0) >> 1;
        // 旋转
    }
    printf("%d\n", ts);
    for (int i = 1; i <= ts; ++i) printf("%d ", s[i]);
    return 0;
}
```

---

## 作者：LawrenceSivan (赞：11)

# CF1270E Divide Points

妙题！


## 题意简述

> 给你 $n$ 个点和它们的坐标，现在给它们两两连上边，如果在同一组为黄色，不同组为蓝色。现在让你给出任意一种分组方案，使得所有长度相同的边颜色相同。
>
> $2 \le n \le 10^3$

## sol

构造题。

我个人认为题目翻译写的稍微有点难懂。

首先进行题意转化。

长度相同一定颜色相同，颜色不同一定意味着长度不同。

那么题意就转化为将 $n$ 个点分成两组，使得不同组中的点的距离一定不等于同一组中点的距离。

要注意本题中提到的距离都是**欧几里得**距离。

考虑按照横坐标与纵坐标奇偶分类。

将点分成四类：

- 横坐标是奇数，纵坐标是奇数，我们记作 $A_{1,1}$。

- 横坐标是奇数，纵坐标是偶数，我们记作 $A_{1,0}$。

- 横坐标是偶数，纵坐标是奇数，我们记作 $A_{0,1}$。

- 横坐标是偶数，纵坐标是偶数，我们记作 $A_{0,0}$。

假设分出的两个集合分别是 $X,Y$。

 考虑欧几里得距离公式：

$$dis(a,b)=\sqrt{(x_a-x_b)^2+(y_a-y_b)^2}$$

之后我们把里面拆开：

$$x_a^2-2x_ax_b+x_b^2+y_a^2-2y_ay_b+y_b^2$$

稍微整理一下，得：

$$x_a^2+x_b^2+y_a^2+y_b^2-2\times(x_ax_b+y_ay_b)$$

之后考虑 $a,b$ 坐标的奇偶性。

- 当 $a,b$ 横纵坐标都是奇数：

  由于奇数的平方仍然是奇数，奇数与奇数的和是偶数，偶数与偶数的和是偶数，所以 $x_a^2+x_b^2+y_a^2+y_b^2$ 是偶数，自然后面 $2\times(x_ax_b+y_ay_b)$ 也是一个偶数，那么整个式子就是偶数。

  由于式子前半部分相当于两个偶数的和，后半部分由于 $x_ax_b+y_ay_b$ 相当于两个奇数的和，即偶数，$2\times(x_ax_b+y_ay_b)$ 是偶数与 $2$ 的积，所以整体可以被 $4$ 整除。

- 当 $a,b$ 横纵坐标都是偶数：

  偶数的平方仍然是偶数，偶数与偶数和仍是偶数，所以整个式子依旧是偶数，并且能够被 $4$ 整除。

- 当 $a,b$ 横纵坐标一个全奇，一个全偶：

  假设 $a$ 全奇，$b$ 全偶，可以证明这并不影响答案。

  $x_a^2,y_a^2$ 中 都是奇数，加起来是偶数，$x_b^2,y_b^2$ 都是偶数，加起来是偶数。所以和仍是偶数，整体也是偶数。

  由于两个互异的完全平方奇数的和只能被 $2$ 整除，不能被 $4$ 整除，前面我们可以认为是一个 $2\times(balabalabala)$ 的形式。（其中 $balabalabala$ 是一个奇数）

  后面 $x_ax_b+y_ay_b$ 相当于偶数和偶数的和，还是偶数，$2\times(x_ax_b+y_ay_b)$ 相当于偶数与 $2$ 的积，整体可以写成 $2\times(奇数-偶数)$ ，所以整体只能被 $2$ 整除。

- 当 $a,b$ 横纵坐标都是一奇一偶，$a,b$ 横纵坐标奇偶性一致：

  意思是 $a,b$ 都属于 $A_{0,1}$ 或者都属于 $A_{1,0}$。

  同样的，这样 $x_a^2,x_b^2,y_a^2,y_b^2$ 会出现两个奇数与两个偶数。

  于是相加的和仍然是偶数。

  于是整体还是偶数。

  前面依然看作两个互异的完全平方奇数的和只能被 $2$ 整除，不能被 $4$ 整除，于是我们可以认为是一个 $2\times(balabalabala)$ 的形式。（其中 $balabalabala$ 是一个奇数），后面 $x_ax_b+y_ay_b$，是个奇数，整体就是 $2\times(奇数-奇数)$， 可以被 $4$ 整除。

- 当 $a,b$ 横纵坐标都是一奇一偶，$a,b$ 横纵坐标奇偶性不一致：

  意思是 $a,b$ 一个属于 $A_{0,1}$ 另一个属于 $A_{1,0}$ 或者 一个属于 $A_{1,0}$ 另一个属于 $A_{0,1}$ 。

  同样的，这样 $x_a^2,x_b^2,y_a^2,y_b^2$ 会出现两个奇数与两个偶数。

  于是相加的和仍然是偶数。

  于是整体还是偶数。

  前面依然看作两个互异的完全平方奇数的和只能被 $2$ 整除，不能被 $4$ 整除，于是我们可以认为是一个 $2\times(balabalabala)$ 的形式。（其中 $balabalabala$ 是一个奇数），后面 $x_ax_b+y_ay_b$，是个偶数，整体就是 $2\times(奇数-偶数)$， 只能被 $2$ 整除。

- 当 $a,b$ 横纵坐标有一个一奇一偶，另一个都是奇数（或者都是偶数，通过上面的分析发现其实从结果来看是一样的）：

  这里 $a$ 的横纵坐标一奇一偶与 $b$ 的横纵坐标一奇一偶其实是等价的，我们这里假设 $a$ 的坐标一奇一偶。

  这时 $x_a^2,x_b^2,y_a^2,y_b^2$ 中会出现 $x_a^2,y_a^2$ 中一奇一偶，$x_b^2,y_b^2$ 两个偶数，于是 $x_a^2+x_b^2+y_a^2+y_b^2$ 这个整体是奇数，减去后面的偶数，整体是个奇数。

接下来形势就比较明朗了。

由于距离还需要开根号，是不好处理且比较麻烦的，所以下面我们只讨论**距离的平方**。

于是分情况考虑：

- 当 $A_{1,1} \cup A_{0,0}$ 和 $A_{0,1} \cup A_{1,0}$ 都非空，那么我们可以令 $X=A_{1,1} \cup A_{0,0},Y=A_{0,1} \cup A_{1,0}$。

  根据上面的讨论可以发现，对于 $X$ 中的点，距离的平方必定是个偶数，对于 $Y$ 中的点，距离的平方也必定是偶数。

  接下来看跨越两个集合的边。恰好符合上面提到的一个一奇一偶，另一个全奇或全偶，所以距离的平方是个奇数。

  于是满足了不同组中的点的距离一定不等于同一组中点的距离。

- 当 $A_{1,1},A_{0,0}$ 都非空，那么我们可以令 $X=A_{1,1},Y=  A_{0,0}$。

  对于 $X$，内部的点距离的平方一定都是偶数，并且被 $4$ 整除。

  对于 $Y$，内部的点距离的平方一定都是偶数，并且被 $4$ 整除。

  对于跨越两个集合的点，距离的平方一定是偶数，但是只能被 $2$ 整除。

  满足了不同组中的点的距离一定不等于同一组中点的距离。

- 当 $A_{0,1},A_{1,0}$ 都非空，那么我们可以令 $X=A_{0,1},Y=  A_{1,0}$。

  对于 $X$，内部的点距离的平方一定都是偶数，并且被 $4$ 整除。

  对于 $Y$，内部的点距离的平方一定都是偶数，并且被 $4$ 整除。

  对于跨越两个集合的点，距离的平方一定是偶数，但是只能被 $2$ 整除。

  满足了不同组中的点的距离一定不等于同一组中点的距离。

- 当不满足上述任何条件，我们将左右的点横纵坐标除以 $2$，也就是把图缩小一倍。

  虽然缩小了一倍，但是对应关系并没有变化，并且经过至多 $\mathcal{O(\log SIZE)}$ 次缩小之后，一定可以得到答案。

  $\mathcal{SIZE}$ 是值域大小。

复杂度 $\mathcal{O(n\log SIZE)}$

## CODE:

```cpp
//#define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register

const int maxn=1e3+5;
const int maxm=1;

int n;

int x[maxn],y[maxn];

int cnt[2][2];

vector <int> ans;

namespace IO{
	template<typename T>
	inline void read(T &x){
		x=0;T f=1;char ch=getchar();
		while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
		while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
		x*=f;
	}

	template <typename T, typename... Args>
	inline void read(T& t, Args&... args){
		read(t); read(args...);
	}

	template<typename T>
	void write(T x){
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}

	template<typename T,typename... Args>
	void write(T t,Args... args){
		write(t);putchar(' ');write(args...);
	}
}

using namespace IO;

signed main(){
#ifdef LawrenceSivan
	freopen("aa.in","r", stdin);
	freopen("aa.out","w", stdout);
#endif
	read(n);
	for(re int i=1;i<=n;i++){
		read(x[i],y[i]);
	}

	while(true){	
		memset(cnt,0,sizeof(cnt));
		for(re int i=1;i<=n;i++){
			cnt[x[i]&1][y[i]&1]++;
		}

		if((cnt[0][0]|cnt[1][1])&&(cnt[1][0]|cnt[0][1])){
			for(int i=1;i<=n;i++){
				if((x[i]&1)==(y[i]&1))ans.push_back(i);
			}
			write(ans.size()),puts("");
			for(auto i:ans)write(i),putchar(' ');
			puts("");
			return 0;
		}

		else if((cnt[0][0]&&cnt[1][1])||(cnt[0][1]&&cnt[1][0])){
			for(int i=1;i<=n;i++){
				if(x[i]&1)ans.push_back(i);
			}
			write(ans.size()),puts("");
			for(auto i:ans)write(i),putchar(' ');
			puts("");
			return 0;
		}

		else for(re int i=1;i<=n;i++)x[i]>>=1,y[i]>>=1;
	}


	return 0;
}
```

---

## 作者：tzc_wk (赞：6)

[Codeforces 题目传送门](https://codeforces.com/contest/1270/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1270E)

显然，直接暴力枚举是不可能的。

考虑将点按横纵坐标奇偶性分组，记 $S_{i,j}=\{t|x_t\equiv i\pmod{2},y_t\equiv j\pmod{2}\}(i,j\in[0,1])$，说白了就是横坐标为偶数、纵坐标为偶数；横坐标为偶数、纵坐标为奇数；横坐标为奇数、纵坐标为偶数；横坐标为奇数、纵坐标为奇数的点集。

然后考虑以下算法：

- 若 $S_{0,0},S_{1,1}$ 以及 $S_{0,1},S_{1,0}$ 中至少各有一个集合非空，那么我们令 $A=S_{0,0}\cup S_{1,1},B=S_{1,0}\cup S_{0,1}$ 即可，因为对于 $S_{0,0},S_{1,1}$ 中任意两点，它们距离的平方要么模 $4$ 余 $0$，要么模 $4$ 余 $2$，$S_{0,1},S_{1,0}$ 也同理；而对于 $S_{0,0},S_{1,1}$ 与 $S_{0,1},S_{1,0}$ 之间的点，距离的平方模 $4$ 余 $1$，符合题目要求。
- 若 $S_{0,0}$ 以及 $S_{1,1}$ 均非空，那么我们令 $A=S_{0,0},B=S_{1,1}$ 即可。因为对于 $S_{0,0}$ 中的任意点它们距离的平方模 $4$ 余 $0$，$S_{1,1}$ 也同理；对于 $S_{0,0}$ 与 $S_{1,1}$ 之间的点它们距离的平方模 $4$ 余 $2$。满足两两不同的条件。

- 若 $S_{1,0}$ 以及 $S_{1,0}$ 均非空，类比 $S_{0,0}$ 以及 $S_{1,1}$ 非空的情况即可。
- 若以上条件均不满足，即 $S_{0,0},S_{0,1},S_{1,0},S_{1,1}$ 中恰有一个非空，那么我们令所有点横纵坐标除以 $2$，再重复以上操作即可，因为我们总能找到一个时刻使得 $S_{0,0},S_{0,1},S_{1,0},S_{1,1}$ 不止一个非空。

这样即可通过此题。

---

你可能会疑惑我为什么要为这道 *2300 的题专门写篇题解，题目本身虽然简单，但也能从中学到一个解决构造题的技巧：观察题目中奇偶性。有不少构造题都是以奇偶性为突破口解决的，当然有时候解构造题的关键不仅仅局限于奇偶性，包括题目中给定的一些特殊的条件等，总而言之解决构造题的技巧说白了只有一点，那就是观察题目中的性质。~~u1s1 我构造题做不出来大概也就是因为我不具备猜结论的能力罢~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e3; 
int n,x[MAXN+5],y[MAXN+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	while(1){
		static int cnt[2][2];memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++) cnt[x[i]&1][y[i]&1]++;
		if(cnt[0][0]+cnt[1][1]>0&&cnt[0][1]+cnt[1][0]>0){
			vector<int> ans;
			for(int i=1;i<=n;i++) if((x[i]&1)^(y[i]&1)) ans.pb(i);
			printf("%d\n",ans.size());
			for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
			printf("\n");return 0;
		} else if(cnt[0][0]>0&&cnt[1][1]>0||cnt[0][1]>0&&cnt[1][0]>0){
			vector<int> ans;
			for(int i=1;i<=n;i++) if(x[i]&1) ans.pb(i);
			printf("%d\n",ans.size());
			for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
			printf("\n");return 0;
		}
		for(int i=1;i<=n;i++) x[i]>>=1,y[i]>>=1;
	}
	return 0;
}
```



---

## 作者：zxh923 (赞：2)

# CF1270E Divide Points 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1270E)

### 思路

我们可以想到按照坐标奇偶性分类，下面证明一下正确性。

首先，我们把第 $i$ 个点记为 $(x_i,y_i)$，接下来进行分类。

+ $x_i+y_i$ 为偶数，此时在这个集合内的连边的长度都为偶数，因为偶数减去偶数再平方还是偶数，两个偶数加起来还是偶数。

+ $x_i+y_i$ 为奇数，此时在这个集合内的连边的长度都为偶数，因为奇数减去奇数再平方是偶数，两个偶数加起来还是偶数。

若两个点分别在两个集合中，可以发现此时边的长度为奇数，与同集合内的边的长度为偶数同理。

于是我们发现，两条边的长度相等则他们的奇偶性相同，而奇数长度边都被染为蓝色，偶数长度边都被染为黄色，显然不会出现黄色边和蓝色边的长度相等的情况。

所以，如果这两种点同时存在，按照上述方法分配是正确的。

接下来我们看如何应对只有一种点存在的情况。

我们以 $x_i+y_i$ 为奇数的点为例，另一种情况不用进行第一次变换，更加简单。

我们考虑因为只有这一种点，所以将所有点全部向某一个方向移动若干个是不会造成影响的，于是这里我们将 $x_i$ 变为 $x_i+1$，当然变换 $y_i$ 也是可行的。

但是发现做这个操作只是变换了点的类型，于是我们还要继续变换。

我们考虑将所有的点都顺时针旋转 $90$ 度，当然一些其他角度同样可行，比如逆时针旋转 $90$ 度，前提是变换后的坐标不会出现小数。

根据[公式](https://www.cnblogs.com/fangsmile/p/8622421.html)，点 $(x_i,y_i)$ 会变为 $(\dfrac{x_i+y_i}{2},\dfrac{x_i-y_i}{2})$，根据上面的描述，同时旋转同一个角度也是不会造成影响的。

于是在特殊情况下的变换方式也是正确的。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1005
using namespace std;
int n,x[N],y[N],res[N],cnt;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	while(1){
		int a=1,b=1;
		for(int i=1;i<=n;i++){
			if((x[i]+y[i]&1))b=0;
			else a=0;
		}
		if(!(a+b)){
			for(int i=1;i<=n;i++){
				if((x[i]+y[i])&1){
					res[++cnt]=i;
				}
			}
			cout<<cnt<<'\n';
			for(int i=1;i<=cnt;i++){
				cout<<res[i]<<' ';
			}
			break;
		}
		if(a){
			for(int i=1;i<=n;i++){
				x[i]++;
			}
		}
		for(int i=1;i<=n;i++){
			int X=x[i],Y=y[i];
			x[i]=X+Y>>1;y[i]=X-Y>>1;
		}
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

首先有一个很简单的做法就是对所有坐标点做奇偶染色，然后奇数点放在 $A$ 集合偶数点放在 $B$ 集合。但是若 $A,B$ 集合中存在一个空集合就爆了。

然后可以考虑到调整坐标，若存在空集合就把所有点的横纵坐标都除以 $2$ 然后再来跑上面的算法，直到跑出来解为止。但是可以被样例 $2$ 给 hack。

于是考虑到一个比较巧妙的手法：考虑把 $(x,y)$ 坐标映射到 $(\frac{x+y}2,\frac{x-y}2)$ 坐标，然后跑上面的算法直到跑出解为止。可以证明到坐标原点的距离每一次除以 $2$，期望最多除 $\log$ 次。因此时间复杂度为 $O(n\log n)$ 可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
int x[N], y[N];
signed main() {
    cout << fixed << setprecision(15);
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }
    while (1) {
        int c1 = 0, c2 = 0;
        for (int i = 1; i <= n; ++i)
            if ((x[i] + y[i]) & 1) ++c1;
            else ++c2;
        if (c1 && c2) {
            vector<int> v;
            for (int i = 1; i <= n; ++i)
                if ((x[i] + y[i]) & 1) v.emplace_back(i);
            cout << v.size() << '\n';
            for (int &i : v) cout << i << ' ';
            cout << '\n';
            return 0;
        } else {
            for (int i = 1; i <= n; ++i) {
                if (c1) ++x[i];
            }
            for (int i = 1; i <= n; ++i) {
                int _x = x[i], _y = y[i];
                x[i] = (_x+_y) / 2, y[i] = (_x-_y) / 2;
            }
        }
    }
    return 0;
}
```

---

## 作者：NKL丶 (赞：0)

## Description

给出二维平面上的 $n$ 个整点，将这些整点分为两个非空集合 $A,B$，然后将这些点两两连边，边长为两点的欧几里得距离，同一组的边为黄色，不同组为蓝色，求一种分组方案，使得长度相同的边颜色相同。（$1 \le n \le 10^3$）

## Solution

将所有边长平方，发现对于所有的点，$x+y$ 奇偶性相同的点才有可能形成长度相同的边，这启发我们将所有点按照 $x+y$ 的奇偶性划分，若两个集合均有点则直接输出，反之此时所有点 $x+y$ 奇偶性相同，若为偶数则将 $\{x,y\} \leftarrow \{\frac{x+y}{2},\frac{x-y}{2}\}$，若为奇数则将 $x \leftarrow x+1$，转化为前一种情况然后继续划分。容易发现这种划分只会进行 $\log A$ 次，因此复杂度为 $n \log A$。

## [Code](https://www.luogu.com.cn/paste/nzez8nz8)

---

## 作者：liuyz11 (赞：0)

# 题解 CF1270E 【Divide Points】

**该场比赛的所有题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12161998.html)**

题目大意：给你n个点和它们的坐标，现在给它们两两连上边，如果在同一组为黄色，不同组为蓝色。现在让你给出任意一种分组方案，使得所有长度相同的边颜色相同。

相信大家看到这题目想的都是二分图啊，并查集啊……但我不一样，我想的是：这题目能做嘛……

大佬的做法真是高超，先放上题解里截来的图。

![](https://images.cnblogs.com/cnblogs_com/nblyz2003/1329739/o_200107111230Snipaste_2020-01-07_19-12-14.png)

主要思路就是奇偶分类。

我们将点按照横纵坐标的奇偶性，分成4个集合。

![](https://images.cnblogs.com/cnblogs_com/nblyz2003/1329739/o_200107111821%E6%97%A0%E6%A0%87%E9%A2%98.png)

其中点上的0,1表示坐标的奇偶性，边上的0,1表示长度平方的奇偶性。

不难得出以上不同集合的点的关系，另外同一集合中的边当然也为0。

那么我们只要将(0,0)和(1,1)放入一组，(0,1)和(1,0)放入另一组，那么偶边（即长度平方为偶数的边）必定是同一组的两点，奇边必定是不同组的两点。当然这有个前提，就是每组都不能为空。

那若是有一组为空呢，图片就变成了这个样子

![](https://images.cnblogs.com/cnblogs_com/nblyz2003/1329739/o_200107112903%E6%97%A0%E6%A0%87%E9%A2%98.png)

两个集合连起来也是偶边，自己集合连自己集合也是偶边，似乎无法连接了。

但是我们发现自己连自己横坐标差和纵坐标差都为偶数，和别的集合连得差都为偶数。

我们设同一集合的横坐标差为2k1，纵坐标差为2k2，不同集合的横坐标差为2k1+1，纵坐标差是2k2+1

根据距离公式d = √((x1 - x2) × (x1 + x2) + (y1 - y2) × (y1 - y2))进行计算（方便起见，直接算边长度的平方）。

同一集合相连 = (2k1)2 + (2k2)2 = 4(k12 + k22)

不同集合相连 = (2k1 + 1)2 + (2k2 + 1)2 = 4(k12 + k22 + k1 + k2) + 2

很显然这两个是不会相等的。

那么如果不符合上一个情况，那么按x的奇偶性分组。

可是万一数据只有一个集合呢？

没事把数据缩小一倍就好了，到时候一定会有答案因为点坐标两两不同。

这样为什么可行呢？

因为同一个集合中的点的奇偶性都是相同的，那么我们将它们的最后一位舍弃也是符合原来的大小情况。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 1005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

vi ans;
int x[MAXN], y[MAXN], cnt[2][2];

int main(){
	int n;
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d%d", &x[i], &y[i]);
	while(1){
		clr(cnt, 0);
		rep(i, 1, n) cnt[x[i] & 1][y[i] & 1]++;
		if(cnt[0][1] + cnt[1][0] > 0 && cnt[0][0] + cnt[1][1] > 0){
			rep(i, 1, n)
				if((x[i] & 1) ^ (y[i] & 1)) ans.pb(i);
			printf("%d\n", SZ(ans));
			rep(i, 0, SZ(ans) - 1) printf("%d ", ans[i]);
			puts("");
			return 0;
		}
		if(cnt[0][0] + cnt[0][1] > 0 && cnt[1][0] + cnt[1][1] > 0){
			rep(i, 1, n)
				if(x[i] & 1) ans.pb(i);
			printf("%d\n", SZ(ans));
			rep(i, 0, SZ(ans) - 1) printf("%d ", ans[i]);
			puts("");
			return 0;
		}
		rep(i, 1, n){
			x[i] >>= 1;
			y[i] >>= 1;
		}
	}
    return 0;
}
```

---

