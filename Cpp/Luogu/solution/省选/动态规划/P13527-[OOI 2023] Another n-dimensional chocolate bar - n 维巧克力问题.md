# [OOI 2023] Another n-dimensional chocolate bar / n 维巧克力问题

## 题目背景

CF1801F

## 题目描述

妈妈给小男孩瓦夏买了一块 $n$ 维巧克力，这块巧克力是一个 $n$ 维立方体，每条边的长度都是 $1$。这块巧克力已经被标出了分割线。在第 $i$ 个维度上，可以用超平面将巧克力沿该维度分成 $a_i$ 份相等的小块。因此，巧克力总共被分成 $a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n$ 块，每一小块在第 $i$ 个维度上的长度都是 $\frac{1}{a_i}$，因此每一小块的体积为 $\frac{1}{a_1 a_2 \cdots a_n}$。

瓦夏和他的朋友们想要把巧克力切成至少 $k$ 块，并且希望最小的那一块的体积尽可能大。巧克力只能在原本小块的连接处切割，每一次切割都必须是沿着参与形成小块的某个超平面，且每次切割都要贯穿整个巧克力。所有切割都完成后，瓦夏才将巧克力分成小块。

更正式地说，瓦夏需要选择 $b_1, b_2, \dots, b_n$ 这 $n$ 个数（$1 \le b_i \le a_i$），表示在第 $i$ 个维度上将巧克力切成 $b_i$ 份。需要满足 $b_1 \cdot b_2 \cdot \ldots \cdot b_n \ge k$，这样切割后才能得到不少于 $k$ 块巧克力。可以注意到，在最优切割方案下，最小的一块包含 $\lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor$ 个小块，其体积为 $\lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n}$。

瓦夏希望得到的答案是：最小一块体积的最大可能值乘以 $k$，也就是最大化 $\lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} \cdot k$。请你帮他实现这个目标。


## 说明/提示

### 样例解释

在第一个样例中，一维的巧克力可以这样切割：

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/4yyiz7gv.png)
:::

此时答案为 $\frac{2}{5} \cdot 2 = 0.8$。

在第二个样例中，巧克力可以这样切割：

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/mj5ryu3a.png)
:::

此时答案为 $\frac{2}{5} \cdot \frac{3}{10} \cdot 6 = 0.72$。

在第三个样例中，巧克力可以这样切割：

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/nnpu0bhr.png)
:::

此时答案为 $\frac{2}{4} \cdot \frac{1}{4} \cdot 7 = 0.875$。

### 评分说明

本题的测试数据分为 8 组。只有通过某一组的全部测试点，且通过部分之前组的全部测试点后，才能获得该组的分数。注意，有些分组不需要通过样例中的测试点。“离线评测”表示该组的测试结果只会在比赛结束后公布。

| 组别 | 分值 | $n$ | $k$ | $a_i$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:-----:|:------------:|:----:|
| 0    | 0    | --  | --  | --    | --           | 样例测试点 |
| 1    | 10   | $n \le 2$ | -- | -- | -- |  |
| 2    | 12   | --  | $k \le 500$ | $a_i \le 500$ | 0 |  |
| 3    | 13   | --  | $k \le 20\,000$ | $a_i \le 2000$ | 0, 2 |  |
| 4    | 12   | --  | $k \le 40\,000$ | -- | 0, 2, 3 |  |
| 5    | 10   | --  | $k \le 200\,000$ | -- | 0, 2, 3, 4 |  |
| 6    | 11   | --  | $k \le 4 \cdot 10^6$ | $a_i \le 2000$ | 0, 2, 3 |  |
| 7    | 15   | --  | $k \le 5 \cdot 10^6$ | -- | 0, 2 -- 6 |  |
| 8    | 17   | --  | --  | --    | 0 -- 7        | **离线评测** |

## 样例 #1

### 输入

```
1 2
5```

### 输出

```
0.8```

## 样例 #2

### 输入

```
2 6
5 10```

### 输出

```
0.72```

## 样例 #3

### 输入

```
2 7
4 4```

### 输出

```
0.875```

## 样例 #4

### 输入

```
2 3
4 5```

### 输出

```
0.75```

## 样例 #5

### 输入

```
4 444
57 179 239 2```

### 输出

```
0.97557326850704739751```

## 样例 #6

### 输入

```
2 5
2 2```

### 输出

```
0```

# 题解

## 作者：FFTotoro (赞：2)

其实是数论基础题。

考虑状态的设计：$f_{i,P}$ 表示考虑了前 $i$ 个元素，要求 $\prod\limits_{j=i+1}^n b_j\ge P$ 的最大答案。由于 $P$ 必然形如  $\left\lceil\frac{k}{x}\right\rceil$，根据整除分块的理论可能的 $P$ 个数是 $O(\sqrt{k})$ 的——于是状态数变为 $O(n\sqrt{k})$，直接暴力枚举 $b_i$ 转移时间复杂度为 $O(n\sqrt{k}\max a_i)$，可以获得 $25$ 分。

发现对于某一些 $b_i$，$\left\lceil\frac{P}{b_i}\right\rceil$ 的值是一样的，也就是说可以对于 $[1,P]$ 内的值再套一层整除分块！这样的时间复杂度是 $O\left(n\left(\sum\limits_{m=1}^{\sqrt{k}}\sqrt{m}+\sqrt{\left\lceil\frac{k}{m}\right\rceil}\right)\right)=O(nk^{\frac{3}{4}})$，证明可以参考 [杜教筛 - OI Wiki](https://oi-wiki.org/math/number-theory/du/#%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6)。于是本题得以解决。

实现时注意到 $\left\lceil\frac{k}{x}\right\rceil=\left\lfloor\frac{k-1}{x}\right\rfloor+1$，所以可以转换为 $k-1$ 的下取整整除分块。这里注意特判 $\left\lfloor\frac{k-1}{x}\right\rfloor=0$ 的情况，转移时单独提出来处理。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,k; cin>>n>>k,k--;
  vector<int> a(n),w;
  for(auto &i:a)cin>>i;
  for(int l=1,r;l<=k;l=r+1)
    w.emplace_back(k/l),r=k/(k/l);
  w.emplace_back(0); // 预处理第二维的可能值
  vector<int> p(k+1,-1);
  for(int i=0;i<w.size();i++)
    p[w[i]]=i; // 记一下位置方便转移时快速查找
  vector<double> f(w.size());
  f[0]=k+1;
  for(int x:a){
    vector<double> g(w.size());
    for(int i=0;i<w.size();i++)
      if(f[i]){
        for(int l=1,r;l<=w[i];l=r+1){
          int v=w[i]/l;
          g[p[v]]=max(g[p[v]],f[i]*(x/l)/x),r=w[i]/v;
        } // 整除分块进行转移
        g.back()=max(g.back(),f[i]*(x/(w[i]+1))/x);
        // 特判值为 0
      }
    f=move(g); // 使用滚动数组
  }
  cout<<fixed<<setprecision(11)<<f.back()<<endl;
  return 0;
}
```

---

## 作者：Kingna (赞：1)

定义 $dp_{i,j}$ 表示前 $i$ 块巧克力，$b_{i+1}\times b_{i+2}\times \dots \times b_n\geq j$ 的前提下答案的最大值。

初始化 $f_{0,k}=1$。转移有 $f_{i,⌈ \frac{j}{x}⌉}=\max\{f_{i-1,j}\times ⌊\frac{a_i}{x}⌋\times \frac{1}{a_i}\}$。最终答案 $f_{n,1}$。

我们发现 $⌈ \frac{j}{x}⌉$ 很难处理，考虑转化成 $⌈ \frac{j}{x}⌉=⌊\frac{j-1}{x}⌋+1$。

同时满足相当好的性质：$⌈\frac{⌈ \frac{j}{x}⌉}{y}⌉=⌊\frac{j-1}{xy}⌋+1$。意味着状态第二位均是 $⌊\frac{j-1}{k}⌋$，其中 $1\leq k\leq j$。$⌊\frac{j-1}{k}⌋$ 不同种类的数只有 $\sqrt k$ 个，使用整除分块先存到一个数组中，然后遍历 $j$ 的时候直接遍历这个数组即可。

现在我们在 $O(n\sqrt k)$ 的时间内遍历了所有状态 $(i,j)$，现在需要对每个状态快速枚举 $x$。同理使用整除分块去寻找所有 $⌊\frac{j}{x}⌋$，对于相同的 $⌊\frac{j}{x}⌋$ 我们使用最小的 $x$，这样会使得 $⌊\frac{a_i}{x}⌋$ 更大。注意 $x$ 还可以等于 $j+1$。

哎 $⌈\frac{⌈ \frac{j}{x}⌉}{y}⌉=⌊\frac{j-1}{xy}⌋+1$ 后面不是还加了一个 $1$ 吗？因为全部存储到同一纬度 $j$，全部加 $1$ 相当于平移，等于没有。

时间复杂度：$O(n\times \sum \limits_{i=1}^{\sqrt k}(\sqrt i+\sqrt \frac{k}{i}))=O(nk^{0.75})$。

::::info[代码]
```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
//#define int long long

const int N = 1e5 + 5, M = 1e7 + 5;

int n, k, a[N], sta[N], tot, vis[M];
double f[105][N]; 

signed main() {
  cin >> n >> k;
  _for(i, 1, n) cin >> a[i];
  for (int l = 1, r = 0; l <= k - 1; l = r + 1) {
    r = (k - 1) / ((k - 1) / l);
    sta[++tot] = (k - 1) / l;
    vis[(k - 1) / l] = tot;
  }
  sta[++tot] = 0; vis[0] = tot;
  f[0][1] = 1.0;
  _for(i, 1, n) _for(j, 1, tot) {
    for (int l = 1, r = 0; l <= sta[j]; l = r + 1) {
      r = sta[j] / (sta[j] / l);
      f[i][vis[sta[j] / l]] = max(f[i][vis[sta[j] / l]], f[i - 1][j] * (a[i] / l) / a[i]);
    }
    f[i][tot] = max(f[i][tot], f[i - 1][j] * (a[i] / (sta[j] + 1)) / a[i]);
  }
  printf("%.20lf", f[n][tot] * k);
}
```
::::

---

## 作者：tkdqmx (赞：1)

设 $f_{i,j}$ 表示 $b_1$ 到 $b_i$ 已经确定，且 $\prod_{k=j+1}^n b_p\geq j$ 的前提下，$\prod_{k=1}^i\lfloor \frac{a_k}{b_k}\rfloor \times \frac{1}{a_k}$ 的最大值。

考虑通过枚举 $b_i$ 转移，令 $b_i=x$，有 $f_{i,\lceil \frac{j}{x} \rceil}\leftarrow f_{i-1,j}\times \lfloor \frac{a_i}{x} \rfloor\times \frac{1}{a_i}$。

边界条件：$f_{0,i}=1$，答案即为 $f_{n,1}\times k$，时间复杂度是 $O(nk)$ 的，所以考虑优化。

考虑将式子中的向上取整统一转为向下取整，有 $\lceil \frac{k}{a} \rceil=\lfloor \frac{k-1}{a}\rfloor+1$。

接下来就可以整除分块去掉无用状态，并给予状态编号减小空间复杂度，最后的时间复杂度据说是 $O(nk^{0.75})$，代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define M 105
#define N 10000005
double dp[M][10005];
int n,k,cnt,a[M],rk[N],dy[N];
int main(){
	scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)  scanf("%d",a+i);
	for(int i=1,j;i<k;i=j+1){
		rk[++cnt]=(k-1)/i;
		j=(k-1)/((k-1)/i);
	}
	rk[++cnt]=0,reverse(rk+1,rk+1+cnt),dp[0][cnt]=1;
	for(int i=1;i<=cnt;i++)  dy[rk[i]]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=cnt;j++){
			if(!dp[i-1][j])  continue;
			for(int l=1,r;l<=rk[j];l=r+1){
				r=rk[j]/(rk[j]/l);
				dp[i][dy[rk[j]/l]]=max(dp[i-1][j]*(a[i]/l)/a[i],dp[i][dy[rk[j]/l]]);
			}
			dp[i][1]=max(dp[i][1],dp[i-1][j]*(a[i]/(rk[j]+1))/a[i]);
		}
	}
	printf("%.10lf\n",dp[n][1]*k);
}
~~~

---

## 作者：封禁用户 (赞：0)

暴力的式子是：$f_j = \max\limits_{k=1}^j{\frac{g_{\lceil{\frac{j}{k}}\rceil}\times\lfloor{\frac{a_i}{k}}\rfloor}{a_i}}$

首先，最开始的状态是 $m$，然后每次更新后的状态肯定是 $\lceil{\frac{m}{i}}\rceil$，因为整除分块所以状态数直接被缩成 $\sqrt m$ 级别的数，然后发现 $\lceil{\frac{j}{k}}\rceil$ 也是可以整除分块，所以最后做两次整除分块就可以了，这就是正解，时间复杂度是 $\mathcal{O}(n\times k^{\frac{3}{4}})$，下面来证明一下为啥是这个。

复杂度的式子是 $n\times(\sum\limits_{k=1}^{\sqrt m}\sqrt k+\sqrt{\frac{m}{k}})$，单独把后面那个东西单独拎出来积分，式子就是这样的：

$$\int_{1}^{\sqrt m}{\sqrt x}\,dx+\int_{1}^{\sqrt m}{\sqrt{\frac{m}{x}}}\,dx$$

发现左边是 $m^{\frac{3}{4}}$ 级别的式子，右边是 $m^{\frac{1}{2}}$ 级别的式子，所以总复杂度就是 $\mathcal{O}(n\times k^{\frac{3}{4}})$

最后放一下代码：

```cpp
for (int i = 0; i < S.size(); ++i) {
	if (g[i + 1] < 1e-10) continue;
	for (int l = 1, r; l <= S[i]; l = r + 1) {
		int j = id[S[i] / l];
		f[j] = max(f[j], g[i + 1] / val * (val / l));
		r = S[i] / (S[i] / l);
	}
	f[idx] = max(f[idx], g[i + 1] / val * (val / (S[i] + 1)));
}
```

---

## 作者：chen_zhe (赞：0)

记 $A$ 为 $a_i$ 的最大值。

首先，我们用动态规划以 $O(n \cdot k \cdot f(k, A))$ 的复杂度来解决本题。

令 $dp[i][j]$ 表示前 $i$ 个维度将巧克力划分为 $j$ 块时，最小块的最大可能体积。如果划分超过 $k$ 块，也将结果记入 $dp[i][k]$。在状态转移时，我们需要决定在当前维度将巧克力分成多少份。下面介绍几种做法：

- 可以用 $O(k)$ 枚举下一个状态，并据此计算当前维度需要分成多少份。这样总复杂度为 $O(n \cdot k^2)$。
- 也可以用 $O(A)$ 枚举当前维度分成多少份。
- 在 $dp[i][j]$ 状态时，可以枚举 $b_i$（即当前维度分成多少份），只要 $j \cdot b_i \leq k$。可以证明，这样的解法总复杂度为 $O(n \cdot k \cdot \ln{k})$。

**关键思想**

假设我们需要把巧克力分成 $10$ 块，而前几个维度已经分成了 $5$ 块、$6$ 块、$7$、$8$ 或 $9$ 块。对于我们来说，这些状态没有本质区别，因为无论哪种情况都还需要至少再划分成 $2$ 块。关键在于，如何统计所有这些“有意义”的状态并加以维护。这里有几种方法，下面介绍一种：

我们关心的是所有 $\lceil \frac{k}{i} \rceil$ 的值，其中 $i = 1, 2, \ldots, k$，即还需要将巧克力划分成多少份。实际上，这些值中不同的只有 $O(\sqrt{k})$ 个，因为要么 $i \leq \sqrt{k}$，要么 $\lceil \frac{k}{i} \rceil \leq \sqrt{k}$。如果把这些数作为状态，并在转移时枚举目标状态，总复杂度为 $O(n \cdot \sqrt{k} \cdot \sqrt{k}) = O(n \cdot k)$——但这还不足以解决完整问题。

**最后的观察**

如果我们处于 $dp[i][remain]$ 状态，其中 $remain = \lceil \frac{k}{i} \rceil$ 对某个 $i$ 成立——我们对这个状态应用同样的思想。此时感兴趣的转移是到 $\lceil \frac{remain}{j} \rceil$，其中 $j = 1, 2, \ldots, remain$。如果只枚举这些“有意义”的转移，最终复杂度是多少？

$$
n \cdot \left( \sum\limits_{r=1}^{\sqrt{k}}{ 2 \cdot \sqrt{r} + 2 \cdot \sqrt{\lceil \frac{k}{r} \rceil}} \right)
$$

可以证明，这一复杂度为 $O(n \cdot k^{3/4})$，能够解决本题。

---

