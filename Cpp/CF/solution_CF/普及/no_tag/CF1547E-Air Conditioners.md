# Air Conditioners

## 题目描述

On a strip of land of length $ n $ there are $ k $ air conditioners: the $ i $ -th air conditioner is placed in cell $ a_i $ ( $ 1 \le a_i \le n $ ). Two or more air conditioners cannot be placed in the same cell (i.e. all $ a_i $ are distinct).

Each air conditioner is characterized by one parameter: temperature. The $ i $ -th air conditioner is set to the temperature $ t_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1547E/cf6634601d8b404820c7eae42e10e4cc87878a8e.png)Example of strip of length $ n=6 $ , where $ k=2 $ , $ a=[2,5] $ and $ t=[14,16] $ .For each cell $ i $ ( $ 1 \le i \le n $ ) find it's temperature, that can be calculated by the formula $ $$$\min_{1 \le j \le k}(t_j + |a_j - i|), $ $ </p><p>where  $ |a\_j - i| $  denotes absolute value of the difference  $ a\_j - i $ .</p><p>In other words, the temperature in cell  $ i $  is equal to the minimum among the temperatures of air conditioners, increased by the distance from it to the cell  $ i $ .</p><p>Let's look at an example. Consider that  $ n=6, k=2 $ , the first air conditioner is placed in cell  $ a\_1=2 $  and is set to the temperature  $ t\_1=14 $  and the second air conditioner is placed in cell  $ a\_2=5 $  and is set to the temperature  $ t\_2=16 $ . In that case temperatures in cells are:</p><ol> <li> temperature in cell  $ 1 $  is:  $ \\min(14 + |2 - 1|, 16 + |5 - 1|)=\\min(14 + 1, 16 + 4)=\\min(15, 20)=15 $ ; </li><li> temperature in cell  $ 2 $  is:  $ \\min(14 + |2 - 2|, 16 + |5 - 2|)=\\min(14 + 0, 16 + 3)=\\min(14, 19)=14 $ ; </li><li> temperature in cell  $ 3 $  is:  $ \\min(14 + |2 - 3|, 16 + |5 - 3|)=\\min(14 + 1, 16 + 2)=\\min(15, 18)=15 $ ; </li><li> temperature in cell  $ 4 $  is:  $ \\min(14 + |2 - 4|, 16 + |5 - 4|)=\\min(14 + 2, 16 + 1)=\\min(16, 17)=16 $ ; </li><li> temperature in cell  $ 5 $  is:  $ \\min(14 + |2 - 5|, 16 + |5 - 5|)=\\min(14 + 3, 16 + 0)=\\min(17, 16)=16 $ ; </li><li> temperature in cell  $ 6 $  is:  $ \\min(14 + |2 - 6|, 16 + |5 - 6|)=\\min(14 + 4, 16 + 1)=\\min(18, 17)=17 $ . </li></ol><p>For each cell from  $ 1 $  to  $ n$$$ find the temperature in it.

## 样例 #1

### 输入

```
5

6 2
2 5
14 16

10 1
7
30

5 5
3 1 4 2 5
3 1 4 2 5

7 1
1
1000000000

6 3
6 1 3
5 5 5```

### 输出

```
15 14 15 16 16 17 
36 35 34 33 32 31 30 31 32 33 
1 2 3 4 5 
1000000000 1000000001 1000000002 1000000003 1000000004 1000000005 1000000006 
5 6 5 6 6 5```

# 题解

## 作者：Gokix (赞：17)

[CF1547E](https://www.luogu.com.cn/problem/CF1547E)

这题做法老多了，深搜、广搜、奇怪 DP、线段树……


搜索及其容易超时，错误的 DP 常数大了会被叉（这场老多叉人都是叉 E 的大常数），线段树大炮轰蚊子又码亮大，显然在 div3 不可取。

如果您用的是上述做法，那您可能看了下面这个做法，就会赞叹于它的短小精悍。

------------

先考虑暴力，无非就是对于每个格子，枚举所有空调，取答案最小值。

显然时间复杂度不可接受，尝试直接在此基础上优化。

注意到每个格子最终答案只可能是所有空调的某一个决定的。那我们记 $f_i$ 表示第 $i$ 个位置上的答案，有比较好想的初始化：一开始有空调的位置 $f$ 值等于空调温度，否则为正无穷。

然后考虑 DP 转移。考虑 $f_i$ 一定被其左面某个空调或右面某个空调更新（如果原来 $i$ 有空调的话可能不被更新，但无妨我们下面的操作）。那不妨如下：假设我们已经求出 $f_{i-1}$ 和 $f_{i+1}$，那么 $f_i=\min{(f_i,f_{i-1},f_{i+1})}$。

但是显然不可能在更新 $f_i$ 同时知道 $f_{i-1}$ 和 $f_{i+1}$，这不满足无后效性。

但是注意到如果 $f_{i-1}$ 某一次更新不了 $f_i$，那无论之后 $f_{i-1}$ 怎么变，它也更新不了 $f_{i}$。$f_{i+1}$ 同理。

或者您可以理解为 $f_{i}$ 不会被自己更新的数更新。

这也就表明我们可以把 $f_{i-1}$ 的更新和 $f_{i+1}$ 的更新分开算，它们之间互不影响，即：

$$f_i=\min(f_i,f_{i-1}+1),i:1 \to n$$

$$f_i=\min(f_i,f_{i+1}+1),i:n \to 1$$

结束！

------------

CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

long long t,n,m,f[300010],id[300010],w[300010];

int main(){
	long long i,j,u,v;
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(i=1;i<=n;i++) f[i]=10000000000000000;
		for(i=1;i<=m;i++) cin>>id[i];
		for(i=1;i<=m;i++) cin>>w[i];
		for(i=1;i<=m;i++){
			u=id[i];v=w[i];
			f[u]=v;
		}
		for(i=2;i<=n;i++) f[i]=min(f[i],f[i-1]+1);
		for(i=n-1;i>=1;i--) f[i]=min(f[i],f[i+1]+1);
		for(i=1;i<=n;i++) cout<<f[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

------------

然后就是注意一下这题最大值不是 $10^9$，而是 $10^9+maxN$。原因的话看一下题目样例的第 4 组就明白了。

---

## 作者：xuanyuan_Niubi (赞：3)

# 题目大意：

有 $ q $ 组数据，每组第一排表示有 $ n $ 个方格和 $ k $ 个空调，第二排是每个空调的位置 $ a_i $，第三排是每个空调的温度 $ t_i $。

每个空调对周围的影响是递减的，所以一个空调周围的温度是公差为 $ 1 $ 的递增等差数列。如果一个方格同时被多个空调影响，那么取最小值。空调所在的方格温度就是空调的温度。

求所有方格的温度。

# 分析：

最开始想的是直接模拟。最开始所有的方格的温度都赋值为 INF，对于每个空调都向左向右逐次 $ +1 $，如果应该变成的数比原来有的数小，那么就改。但是如果更大，那么再往那边也不可能更小了。

看个例子吧！如果最开始是这个样子（ INF 没有写）：

![](https://cdn.luogu.com.cn/upload/image_hosting/oacxcqdo.png)

先将 $ 14 $ 往左扩展。

![](https://cdn.luogu.com.cn/upload/image_hosting/kcjqhhib.png)

然后向右扩展。发现经过第 $ 9 $ 个格子的时候是 $ 17 $，但第 $ 9 $ 个格子本身是 $ 16 $，再向右扩展也肯定比 $ 16 $ 向右扩更劣。就是这样，可以优化一点点。但是还是在第 8 个点 TLE 了。

于是考虑怎么再优化。发现第 $ i $ 个格子的温度仅由 $ i-1 $ 和 $ i+1 $ 决定，考虑像刚才一样先向左再向向右扩展，如果扩的时候遇到了一个更优的，那么就可以把这个相对更劣的给忽略掉了。

例如上面的第 $ 1 $ 个格子 $ 14 $ 向右扩到第 $ 4 $ 个格子的时候应该是 $ 17 $，但是本来这里有个 $ 16 $，比 $ 17 $ 更优。
![](https://cdn.luogu.com.cn/upload/image_hosting/iv0glupl.png)

所以在第 $ 4 $ 个格子将 $ 16 $ 向右扩就可了。

所以就变成了 DP。令 $ f_i $ 是这个格子的温度。

从前往后扫的时候，$ f_i=\min(f_i,f_{i-1}+1) $。

从后往前扫的时候，$ f_i=\min(f_i,f_{i+1}+1) $。

# 代码：

```c++
#include<stack>
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=3e5+5;
inline int read(){
	char c=getchar();int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
inline int abs(int x){return x>0?x:-x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
inline void swap(int &a,int &b){a^=b^=a^=b;}
int a[M],b[M],c[M];
bool vis[M];
int main(){
	int T=read();
	while(T--){
		int n=read(),m=read();
		for(int i=1;i<=n;i++)c[i]=0x3f3f3f3f;//初始化最大值
		for(int i=1;i<=m;i++)a[i]=read();
		for(int i=1;i<=m;i++)b[i]=read();
		for(int i=1;i<=m;i++){
			c[a[i]]=b[i];//有空调的地方温度先暂时是空调的温度来转移
		}
		for(int i=2;i<=n;i++)c[i]=min(c[i],c[i-1]+1);//从前往后扫
		for(int i=n-1;i>=1;i--)c[i]=min(c[i],c[i+1]+1);//从后往前扫
		for(int i=1;i<=n;i++)printf("%d ",c[i]);puts("");
	}
	return 0;
} 
```



---

## 作者：_ajthreac_ (赞：2)

题目中给出的式子有一个绝对值，不难想到对于左边和右边分类讨论，这样就可以消除绝对值：
1. 对于 $i$ 左边的空调，答案为 $\min\{t_j-a_j\}+i$；
2. 对于 $i$ 右边的空调，答案为 $\min\{t_j+a_j\}-i$。

那么我们对于每个空调分别维护 $t_j-a_j$ 和 $t_j+a_j$，然后预处理出前后缀最小值即可。  
核心代码：
```cpp
const int N=300010;
int T,n,k,a[N],t[N],L[N],R[N];
int main(){
  Read(T);
  while(T--){
    Read(n),Read(k);
    memset(L,0x3f,sizeof L),memset(R,0x3f,sizeof R);
    for(rg int i=1;i<=k;i++)Read(a[i]);
    for(rg int i=1;i<=k;i++){
      Read(t[i]);
      L[a[i]]=t[i]-a[i],R[a[i]]=t[i]+a[i];
    }
    for(rg int i=1;i<=n;i++)L[i]=min(L[i-1],L[i]);
    for(rg int i=n;i>=1;i--)R[i]=min(R[i+1],R[i]);
    for(rg int i=1;i<=n;i++){
      int lft=L[i]+i,rgt=R[i]-i;
      cout<<min(lft,rgt)<<" ";
    }
    puts("");
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：Dragonbell_exp (赞：1)

这道题的要求不少方法都能实现，但是用 DP 来做是最优的。

### 分析

既然是 DP，我们就要考虑「状态」与「转移」。

略微读题可知，状态就是格子的温度。

我们发现，一个格子温度只会被它左右的温度所刷新，也有可能不会被刷新。

知道了这一点，就能明白转移即是当前格子与前后两个格子温度的最小值。

### 实现：

开一个 DP 数组用来存储每个格子的温度。

有空调的格子温度暂时是当前格子上空调的温度，没有空调的格子温度暂时未知，所以设为无穷大。这算是初始化。

从前后分别扫一遍，得出结果。

为什么需要扫两遍？

众所周知，一个格子的温度不可能同一个空调更改多次。

第一遍从左到右扫，可以处理所有空调右侧的温度；
第二遍从右到左扫，可以处理所有空调左侧的温度。

同一个空调对于一个格子的温度是固定的，而我们要做的是从这些空调的温度中选择最小的。

也就是说，只有确定了所有空调对于每一个格子的温度，才可以保证每一个格子的温度都是最小的。

这里的思路和暴力有点像，但是需要用到 DP 来实现。

### 代码：

```c
#include<iostream>
#include<cmath>
using namespace std;
int q;//数据数 
int n,k;//格子数和空调数 
int a[300005];//空调的位置 
int t[300005];//空调的温度 
int dp[300005];//格子的温度，用于DP 
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		cin>>k;
		for(int i=0;i<=n+1;i++){//初始化所有格子温度无穷大 
			dp[i]=0x3fffffff;
		}
		for(int i=1;i<=k;i++){//读入空调的位置 
			cin>>a[i];
		}
		for(int i=1;i<=k;i++){//读入空调的温度 并对应到格子里 
			cin>>t[i];
			dp[a[i]]=t[i];
		}
		for(int i=1;i<=n;i++){//从左到右扫一遍 
			dp[i]=min(dp[i],dp[i-1]+1);
			dp[i]=min(dp[i],dp[i+1]+1);
		}
		for(int i=n;i>=1;i--){//从右到左扫一遍 
			dp[i]=min(dp[i],dp[i-1]+1);
			dp[i]=min(dp[i],dp[i+1]+1);
		}
		for(int i=1;i<=n;i++){//输出答案 
			cout<<dp[i]<<" ";
		}
	}
	return 0;
}
```




---

## 作者：Infinity_Detail (赞：0)

题目传送门：[CF1547E](https://www.luogu.com.cn/problem/CF1547E)




作为 CF 比赛里 div3 的 $E$ 题，这题并不是很难。


### 思路：



#### 比赛打多了，碰到这种题，第一种想法就是思考暴力该怎么做。


从暴力的角度来思考一下：这道题的本质就是，空调对周围格子的影响递减，
#### 也就是说周围格子的温度是几个上升的等差序列。

#### 每个格子都有 $k$ 个可能可取的值（因为有 $k$ 个空调）。
根据这个思路，暴力枚举所有格子分别可能拥有的 $k$ 个值后，再暴力枚举一遍，判断最小值，存到答案数组里。

但是对于极大的数据范围还有 CF 阴间的评测方式，暴力的时间复杂度和空间复杂度都会非常的高。所以暴力去做这道题显然不可取。这时我们就要考虑怎样用非暴力的方式解决。

既然是DP，那我们就可以立刻想到**状态和转移**。

### 状态：
 设$f_i$为第$i$个格子当前的温度。

### 转移：
我们不难想到，一个空调的影响是整体的，所以它会影响左边和右边两个方面的所有格子。所以需要考虑一个空调对它左边与右边的影响，也就是先从左往右扫一遍，处理所有空调对它右边格子的温度影响；再从右往左扫一遍，处理所有空调对它左便格子的温度影响，然后取完之后与它原来的值取最小值 $min$ 即可。



### 有了以上思路，不难想到转移方程：



------------

#### 从左往右扫：$f_i=min(f_i$,$f_{i-1}+1)$;

#### 从右往左扫：$f_i=min(f_i$,$f_{i+1}+1)$。

#### 为了取 $min$ 更方便，我们可以在每轮dp开始前把数组赋成极大值。

思路很明确了吧，直接上代码：

### Code：

```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long a[10000005],b[10000005],c[10000005];
bool vis[1000005];
long long t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++)    cin>>a[i];
		for(int i=1;i<=m;i++)    cin>>b[i];
		for(int i=1;i<=n;i++)    c[i]=0x7fffffff;
		for(int i=1;i<=m;i++)    c[a[i]]=b[i];
		for(int i=2;i<=n;i++)    c[i]=min(c[i],c[i-1]+1);
		for(int i=n-1;i>=1;i--)  c[i]=min(c[i],c[i+1]+1);
		for(int i=1;i<=n;i++)    cout<<c[i]<<" ";
	}
	return 0;
}
```


---

## 作者：dalao_see_me (赞：0)

## 题目大意
一排有 $n$ 个格子，一共有 $m$ 台空调，设第 $i$ 台的位置为 $p_i$，温度为 $t_i$，则他对第 $k$ 格的贡献为 $|k-p_i|+t_i$，每个格子的温度是所有空调对该格子贡献的最小值。求每个格子的度数。
## 做法
将能给一个格子贡献的区域拆为左边和右边。我们先看左半部分。

既然一个格子的温度是要求最小值，那我们就要去维护它，如何维护呢？

记 $l$ 为当前左半部分最优空调的位置， $p$ 为最优空调自身的度数。当我们从左往右扫过来时，设当前这个位置为 $i$，空调温度为 $t$，若 $p+i-l>t$，则当前空调一定更优，~~读者自证不难~~，此时将 $p$ 更新为 $t$，$l$ 更新为 $i$。

右半部分也同理，只需要将 $p+i-l>t$ 改为 $p+l-i>t$ 就好了。

然后就做完了，上代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int _, n, m;
int d[N], a[N], t[N];
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
int main() {
	_ = read();
	while (_--) {
		n = read(); m = read();
		memset(d, 0x7f, sizeof(d));
		memset(t, 0x7f, sizeof(t));
		for (int i = 1; i <= m; i++) a[i] = read();
		for (int i = 1; i <= m; i++) {
			int x = read();
			t[a[i]] = x;
		}
		int mn = 2e9, lst = 0;
		for (int i = 1; i <= n; i++) {
			if (mn + i - lst > t[i]) {
				mn = t[i];
				lst = i;
			}
			d[i] = min(d[i], mn + i - lst);
		}
		mn = 2e9, lst = n + 1;
		for (int i = n; i; i--) {
			if (mn + lst - i > t[i]) {
				mn = t[i];
				lst = i;
			}
			d[i] = min(d[i], mn + lst - i);
		}
		for (int i = 1; i <= n; i++) printf("%d ", d[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Meaninglessness (赞：0)

## E. Air Conditioners
**题目大意:**
> 一共有 $n$ 个位置和 $k$ 个空调，分别给出空调的位置 $a_i$ 和空调的温度 $t_i$。
> 对于每一个位置 $i$，它的温度为 $\min\limits^k_{j=1}(t_j+\operatorname{abs}(a_j-i))$。求每个位置的温度。

**解题思路:**

这题与 [P7594 Clear Up](https://www.luogu.com.cn/problem/P7594) 的想法有点类似。

我们稍微转化一下，记 $t_{a_j}$ 为第 $a_j$ 位置上的空调温度。

可将要求式子转化为：$\min\limits^k_{j=1}(t_j+\operatorname{abs}(j-i))$
- 若 $j\le i$ 实际求 $t_j+j-i$
- 若 $j>i$ 实际求 $t_j-j+i$

则我们可以预处理如下数组：

$sum1_i=\min\limits^n_{j=i}(t_j+j)$

$sum2_i=\min\limits^i_{j=1}(t_j-j)$

则第 $i$ 位的温度即为：$\min(sum1_i-i,sum2_i+i)$。

**代码实现:[Code](https://www.luogu.com.cn/paste/2o2nlngf)　时间复杂度$O(Tn)$**

---

