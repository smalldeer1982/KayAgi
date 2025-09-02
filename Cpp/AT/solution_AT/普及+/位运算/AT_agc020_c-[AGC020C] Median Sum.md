# [AGC020C] Median Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc020/tasks/agc020_c

$ N $ 個の整数 $ A_1 $, $ A_2 $, ..., $ A_N $ が与えられます。

$ A $ のすべての空でない部分列について、それぞれの和を考えます。このような和は $ 2^N\ -\ 1 $ 個存在し、この個数は奇数です。

これらの和を昇順に並べたものを $ S_1 $, $ S_2 $, ..., $ S_{2^N\ -\ 1} $ とします。

これらの中央値、$ S_{2^{N-1}} $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ A_i\ \leq\ 2000 $
- 入力値はすべて整数である。

### Sample Explanation 1

この場合、$ S\ =\ (1,\ 1,\ 2,\ 2,\ 3,\ 3,\ 4) $ となり、中央値は $ S_4\ =\ 2 $ です。

### Sample Explanation 2

この場合、$ S\ =\ (58) $ となります。

## 样例 #1

### 输入

```
3
1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
1
58```

### 输出

```
58```

# 题解

## 作者：紫题 (赞：14)

01背包的思想+bitset优化

设$f[i][j]$为用前i个数，能否组成数字$j$ $(f[i][j]∈{0,1})$

转移：$f[i][j]=(f[i-1][j-a[i]])|(f[i-1][j])$

省去第一维，再用bitset进行整体的转移

再看中位数的选取

设所有数的总和为$sum$，如果$f[x]=1$，那一定有$f[s-x]=1$

所以$f[]$是对称的

直接从$sum/2$开始扫即可

```cpp
#include<iostream>
#include<bitset>
using namespace std;
int n,x,sum;
bitset<2000007>f;
int main(){
	cin>>n;
	f[0]=1;
	for(int i=1;i<=n;i++){
		cin>>x;
		f|=f<<x;
		sum+=x;
	}
	for(int i=(sum+1)/2;i<=sum;i++){
		if(f[i]) {cout<<i<<endl;break;}
	}
	return 0;
}
```

---

## 作者：ezoixx130 (赞：7)

## 题意：

给你一个长度为$n$的正整数序列$a$，它包含$2^n-1$个非空子序列，求所有非空子序列的权值的中位数。

一个子序列的权值为子序列内所有元素权值之和。

## 题解：

我们记所有元素权值的和为$s$。

那么如果把空序列也考虑进来的话，对于任意一个权值为$x$的子序列，一定能找到一个权值为$s-x$的子序列。

也就是说，所有子序列的权值在$\lfloor \frac{s}{2}\rfloor$左右两边是对称的。

然而我们不考虑空序列，所以中位数一定是权值小于等于$\lfloor \frac{s}{2}\rfloor$的子序列中权值最大的那一个子序列的权值。

那么我们记一个$f$，其中$f[i]$代表$i$是否是其中一个子序列的权值。

对于一个元素$x$，转移就是$f|=f<<x$。

时间复杂度$O(\frac{ns}{64})$，然而常数极小。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 2010

bitset<2000010> f;
int a[MAXN],n,sum;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",a+i),sum+=a[i];
    f[0]=1;
    for(int i=n;i>=1;--i)f|=f<<a[i];
    for(int i=(sum+1)>>1;i<=sum;++i)
        if(f[i])
        {
            printf("%d\n",i);
            return 0;
        }
}
```

---

## 作者：WeLikeStudying (赞：3)

- 这好题不得加入肯德基豪华套餐？

**题意**
- 给 $n$ 个正整数 $a_1,a_2,\cdots a_n$。
- 这个数列有 $2^{n}-1$ 个非空子序列，我们将每个子序列内元素的和当成一个数列。
- 求这个数列的中位数。
- $1\le n,a_i\le 2000$。

**思路**
- 首先有一个很重要的性质，设 $S=\sum_{i=1}^na_i$，如果 $A$ 能够被拼出来，那么对原先的方案反选， $S-A$ 显然也能够被拼出来。
- 所以如果算上 $0$ 的话，本题中位数可能的分布是对称的，而我们选取的是最靠右的那个，接下来问题就在于这样的数是否存在，我们可以用布尔数组标记，时间复杂度 $\Theta(\sum_{i=1}^n(n-i)\cdot a_i)$，无法通过此题。
- [代码实现](https://www.luogu.com.cn/paste/4on27jno)。
- 然后我们知道，用位图可以快速地处理 $\text{bool}$ 数组，甚至可以快速进行类似整数位运算的操作……
- 然后就 $\text{AC}$ 了，真是难以想象，可见位图优化还是很实用的。
- [代码实现](https://www.luogu.com.cn/paste/dre6lbvx)。

---

## 作者：华为2X (赞：3)

今日神犇Au选手毕克来给我们上课啦！！！

然后，然后，NOIP集训班，就被他强行提高档次，变成了NOI金牌冲刺班(奔泪）

  这道题就是他讲的毒瘤题目中的一道（大哭)！！！

-------------------~~华丽丽的分割线~~-------------------
--
 
让我们先来看一下题目

## 给定一个N个数的集合，那么它的子集就有（2^N-1）个，第i个子集的元素和为Si，求S序列的中位数

犇犇教我们用二进制数来写这道题

用一个数组f[i]来判断是否存在i属于S，若i存在则f[i]==1,否则f[i]==0

让我们看看代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<4000020> f;//最多2000个数，每个数最大值为2000
int n,s;//n为个数，s记录总集合的元素和
int main()
{
	scanf("%d",&n);
	int x;
	f[0]=1;//空集为元素和为0，所以f[0]=1
	for(int i=1;i<=n;i++)
	 {
	  scanf("%d",&x);
//	  cout<<f<<endl;
//	  cout<<(f<<x)<<endl//测试数据用的，你也可以试试，就知道为什么要用二进制数判断元素和是否存在了
	  f|=f<<x;//只可意会不可言传，位运算累加答案
//	  cout<<f<<endl;
	  s+=x;//总和增加
//	  cout<<s<<endl;
	 }
	for(int i=(s+1)/2;i<=s;i++)//(s+1)/2从中间位置开始枚举，f集合具有对称性
	 if(f[i])//如果存在i
	  {
	   printf("%d\n",i);
	   break;
	  }
	return 0;
}

```

### 写在后面
语文表达能力不得，不喜勿喷(呲牙)

---

## 作者：Butterfly_qwq (赞：2)

设 $dp_{i,j}$ 表示是否可以用前 $i$ 个数表示数字 $j$。

则易得 $dp_{i,j}=dp_{i-1,j}|dp_{i-1,j-a_i}$。

可以考虑优化掉一维，还可以用 bitset 整体修改。

即原来的 $dp_{i,j}$ 变成 $dp_j$。

则易得 $dp_j=dp_{(\sum\limits_{i=1}^n a_i)-j}$。

所以从 $\frac{(\sum\limits_{i=1}^n a_i)+1}{2}$ 开始扫描即可。

Code:a_i

```
#include<bits/stdc++.h>
using namespace std;
bitset<4000005>dp;
int main()
{
	int n,s=0;
	cin>>n;
	dp[0]=1;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		s+=x;
		dp|=dp<<x;
	}
	for(int i=(s+1)/2;i<=s;i++)if(dp[i])
	{
		cout<<i;
		return 0;
	}
}
``` 

---

## 作者：AsunderSquall (赞：2)

这里的复杂度默认 $\max a_i$ 与 $n$ 同阶。

目前所有的题解都是 $O(\dfrac{n^3}{\omega})$，我来口胡一个巨大常数 $O(n^2 \log n)$ 而且肯定通不过此题的屑做法。  

先简述一下 $O(\dfrac{n^3}{\omega})$ 的做法：  
设 $m=\sum a_i$。  

考虑对于一个子集合 $S_1$，存在它的补集 $S_2$，使得 $\sum_{x\in S_1}=m-\sum_{x \in S_2}$，除了 $S_1$ 是全集的情况。  
也就是说 $\forall x\in\left[1,m-1\right]$，子集和的集合 $S$ 中 $x$ 和 $m-x$ 的数量一样。  
我们分 $m$ 的奇偶讨论。  

如果 $m$ 为奇数，那么 $\left[1,\dfrac{m-1}2\right]$ 和 $\left[\dfrac{m+1}2,m-1\right]$ 的数一一对应，然后还有一个 $m$ 在 $S$ 中（全集）。  
所以 $\left[\dfrac{m+1}2,m\right]$ 中的第一个出现次数不为 0 的数就是答案。  

如果 $m$ 为偶数，那么 $\left[1,\dfrac m 2-1\right]$ 和 $\left[\dfrac m 2+1,m-1\right]$ 的数一一对应，并且 $\dfrac m 2$ 的数量必然为偶数，然后还有一个 $m$ 在 $S$ 中（全集）。
如果 $\dfrac m 2$ 的数量为 0，那么答案为 $\left[\dfrac m 2 ,m\right] $ 中的第一个出现次数不为 0 的数。如果 $\dfrac  m 2$ 的数量不为 0，那么答案为 $\dfrac m 2$。

综上所述，答案为 $\left[\lfloor \dfrac {m+1} 2\ \rfloor ,m\right]$ 中第一个出现次数不为 0 的数。

然后因为只要考虑能不能取到，所以可以用 `bitset` 优化，时间复杂度为 $O(\dfrac{n^3}{\omega})$。

代码：
```cpp
int m,n;
int a[N];
bitset<N> b;
signed main()
{
   rd(n);
   for (int i=1;i<=n;i++) rd(a[i]),m+=a[i];
   b.set(0);
   for (int i=1;i<=n;i++) b|=(b<<a[i]);
   for (int i=(m+1)/2;i<=m;i++) if (b[i]) {cout<<i<<endl;return 0;}
}
```

然后我们发现，求最终的每个数的出现次数就是若干个多项式的乘积。  
具体来说，就是 $\prod (1+x^{a_i})$ 。  
我们可以用 多项式 ln 和 exp 优化。  
考虑 付公主的背包 的那个套路，把相同的 $a_i$ 放在一起算贡献，然后手动 ln。  
$$ \ln(1+x^k)=x^k-\dfrac {x^{2k}} 2 +\dfrac{x^{3k}} 3 -\dfrac{x^{4k}}{4}+\cdots$$  
只要算到 $m$ 项就行了，$m \le 4\times 10^6$。  
然后跑一遍 $m$ 项的多项式 exp。等等…… $4e6$ 的多项式 exp？还是算了吧。  
现在你肯定知道为什么这个算法通不过此题了，还是用 `bitset` 吧。

---

## 作者：kouylan (赞：2)

## 题解 AT3857 【[AGC020C] Median Sum】

[洛谷题面](https://www.luogu.com.cn/problem/AT3857)

[Atcoder题面](https://atcoder.jp/contests/agc020/tasks/agc020_c)

我们想，如果我们把空集加上去，那么每一个集合都有唯一一个补集。设所有元素之和为 $s$，其中一个集合元素之和为 $j$，那它的补集的元素之和就是 $s-j$。并且，我们可以发现，在 $j$ 和 $s-j$ 这两个和中，必有一个小于等于 $s/2$，另一个大于等于 $s/2$。

所以问题就转化成了，在这所有集合（包括空集）的和中，第一个大于等于 $s/2$ 上取整的和是几。

那么这样，我们就很容易想到 dp 了。设 $f[i][j]$ 表示前 $i$ 个数中，能否使得一个集合的元素和为 $j$。那这样，就是一个背包问题，分成选第 $i$ 个数和不选第 $i$ 个数考虑即可。

但是我们要枚举 $i$ 和 $j$，时间复杂度就是 $n^2s$，而 $s$ 最大是 $4\times 10^6$，肯定会炸。然而，状态中存储的都是 $0$ 或 $1$，那么，我们就很容易想到用 bitset 去优化，就省去了枚举 $j$ 的时间，用位运算即可。

状态转移方程就变为：
```cpp
f[i] = f[i-1]; //不选第 i 个数
f[i] = f[i-1]<<a[i]; //选第 i 个数
```

但是这样空间也会炸，我们只需要滚动即可。

下面是 AC 代码
```cpp
/*
Atcoder AGC020C
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,a[2005],s=0;;
bitset<4000005> f[2];

signed main()
{
	cin>>n;
	for(int i=1;i<=n;cin>>a[i++]);
	for(int i=1;i<=n;i++)
		s += a[i];
	int o=0;
	f[o][0] = f[o][a[1]] = 1;
	for(int i=2;i<=n;i++)
	{
		o ^= 1;
		f[o] = f[o^1];
		f[o] |= f[o^1]<<a[i];
//		for(int j=0;j<=s;j++)cout<<f[o][j]<<' ';cout<<endl;
	}
	for(int j=(s+1)/2;j<=s;j++)
		if(f[o][j])
		{
			cout<<j<<endl;
			break;
		}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：菲斯斯夫斯基 (赞：1)

## AT_agc020_c [AGC020C] Median Sum 题解

题意明了，不再赘述。

首先需要捕捉到题目中的关键词，**中位数**：

>按顺序排列的一组数据中居于中间位置的数。

题目要求的是**非空子集的和的中位数**。

因为该集合的和不会改变，所以**子集**与**补集**的和也不会改变。

不妨将子集的和在数轴上表示，设子集和为 $sum$。

当我们选择好一个子集时，发现该子集的和与补集的和在数轴上关于 $\frac{sum}{2}$ 对称，因为 $\frac{sum}{2}$ 是两点的中点。

得出结论：$\frac{sum}{2}$ 在序列中处于中间位置。

但是又因为题目取的是**非空**子集，所以我们的答案即为第一个**大于等于** $\left\lceil\frac{sum}{2}\right\rceil$ 的可取出的子集和。

故使用 01 背包来解决本题，注意的是，$n\le2000,a_i\le2000$，需要使用 `bitset` 优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int n,sum,a[N];
bitset<N*N>dp;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),sum+=a[i];
	dp[0]=true;
	for(int i=1;i<=n;i++)
		dp|=dp<<a[i];//bitset 优化后的 01 背包
	for(int i=(sum+1)/2;i<=sum;i++)
		if(dp[i])
		{
			printf("%d",i);
			return 0;//找出答案
		}
	return 0;
}
```

---

## 作者：_sublimetext_ (赞：1)

题目大意：

一个集合由 $n$ 个整数组成，请求出它的非空子集和的中位数。

思路：

非空子集可以用 01 背包，

用 bitset 来优化转移。

再看中位数的选取：

设所有数的总和为 $m$ ，如果有 $x$ ，那一定有 $m-x$，所以 dp 数组是对称的。

直接从 $\dfrac{m}{2}$ 开始扫即可。

总复杂度：

$O(\dfrac{n \times m}{2 \times \omega})$。


### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace MAIN {
	const int N = 2000 + 5, M = 2000 * 1000 + 5;
	int n;
	bitset<M> bs;
	int main() {
		scanf ("%d", &n);
		bs[0] = 1;
		int sum = 0;
		for (int i = 1, x; i <= n; ++i) {
			scanf ("%d", &x);
			bs |= bs << x;
			sum += x;
		}
		for (int i = (sum + 1) / 2; i <= sum; ++i) {
			if (bs[i]) {
				printf("%d\n", i);
				break;
			}
		}
		return 0;
	}
}
int main() {
	return MAIN :: main();
}
```

---

## 作者：Push_Y (赞：1)

虽然目前洛谷交不了atcoder的题，但我还是想写一波题解。本题解代码正确性证明↓
![](https://cdn.luogu.com.cn/upload/image_hosting/6on09ghb.png)


### 思路

显然，如果我们已经知道了所有非空子集和，就可以轻松的找出中位数。如果我们枚举每一个非空子集和，那复杂度就炸了。

想到用二进制串来表示**一个数是否为子集和**。对于每个 $a[i]$ ，把二进制串向左移 $a[i]$ 位，就可以把原先得到的每个和加上了 $a[i]$ ，就可以避免重复去枚举计算子集和。同时为了保留之前得到的子集和，用按位或。`f |= f<<a[i]`。

### bitset

这是一个 `STL` 里自带的一个类似 $bool$ 数组的容器，可理解为二进制串，同时也非常高效。

头文件要加上 `#include <bitset>`

声明方式 `bitset<size> name`

然后直接上位运算。

### CODE

```cpp
#include <bits/stdc++.h>//万能头里包含了bitset库
using namespace std;

inline int gin(){//快读
	char c=getchar();
	int s=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*f;
}

bitset<2000005>f;//声明
int n,sum;

int main(){
	n=gin();
	f[0]=1;
	for(int i=1;i<=n;i++){
		int x=gin();//我们不需要保留a[i]，于是直接临时变量。
		sum+=x;//计算出总和，中位数一定≥(sum+1)/2
		f|=f<<x;
	}
	for(int i=(sum+1)>>1;i<=sum;i++)//中位数一定≥(sum+1)/2
		if(f[i]){
			printf("%d\n",i);
			return 0;
		}
	return 0;
}

```


---

## 作者：D2T1 (赞：0)

将空集和 $S_0$ 加入一起考虑，设 $S_0=0$。

我们可以将所有的 $S$ 两两配对，具体地，$S_i$ 与 $S_j$ 配对当且仅当两个子集交集为空，并集为全集。此时易得一个性质：$S_i+S_j=\sum A$。

下文设 $mid=\dfrac{\sum A}2$。

那么我们就可以发现 $S$ 数组每一个小于 $mid$ 的都可以和一个大于 $mid$ 的相配对。故如果存在 $=mid$ 的元素，即这个元素就是中位数；否则因为添加了 $S_0$，所以大于 $mid$ 的最小元素即为中位数。

所以问题转化为了求 $A$ 中选若干个之和大于等于 $mid$ 的最小值。显然可以背包做。但是背包的复杂度有点高，使用 `bitset` 优化即可通过此题。

```cpp
//AT_agc020_c
#include <bits/stdc++.h>
using namespace std;
 
const int N = 2010;
int n, a[N], sum;
bitset<N*N> f;
 
int main(){
	scanf("%d", &n);
	f[0] = 1;
	for(int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		sum += a[i];
		f |= (f << a[i]);
	}
	for(int i = (sum+1) / 2; i <= sum; ++ i){
		if(f[i]){
			printf("%d\n", i);
			return 0;
		}
	}
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
屑题一道，但是似乎很少有题解讲的具体，本蒟来一篇。  
### Problem  
给你一个长度为 $n$ 的数列，所有子集都有一个权值等于子集元素之和，求所有子集权值的中位数。  
为了方便理解，附上[英文原版题面](https://atcoder.jp/contests/agc020/tasks/agc020_c)。  
### Solution  
我们先设状态：$g_{i,j}$ 为用前 $i$ 个数组成 $j$ 的方案数。    
$g_{i,j}=\sum_{k=a_i}^{k\leq maxn}g_{i-1,j-a_i}$  
$maxn$ 代表当前转移下最大的有意义状态下标。  
这个转移过程实际上等于复制前面一段 $[0,maxn-a_i]$ 然后复制加到后面 $[a_i,maxn]$，这样形成的 dp 数列是从中间（$\frac {maxn}{2}$）切开左右相等的，一直如此转移那么根据归纳法就一直成立，所以我们只需要找到所有可行的组合数的中位数即可。   
 
PS：两边相等指回文，中间重合部分本质是一个序列头尾子串相加，所以还是回文。

设个 dp 状态：$f_{i,j}$ 表示前 $i$ 个数能否组成 $j$。不难发现这是个 $O(n^3)$ 的低效做法，但是我们发现这是个可行性 dp 并且转移过程能转换成位运算形式，于是我们可以利用 bitset 来过掉 2000 的数据范围，时间复杂度 $O(\frac {n^3}{w})$。算出来是 $2.5\times 10^8$ 是可以勉强过题的。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e6+10;
int n,x;bitset <N> f;int sum;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;f[0]=1;
	for(int i=1;i<=n;i++){
		cin>>x;sum+=x;
		f=f|(f<<x);
	}
	int cnt=f.count()-1;int tot=0;
	for(int i=1;i<=sum;i++){
		tot+=f[i];
		if(tot==(cnt+1)/2){
			cout<<i;return 0;
		}
	}
	return 0;
}
```


---

## 作者：Paris_Commune (赞：0)

### 分析

Bitset 优化，01 背包。

用一个 $c$ 来记录元素值之和。

子序列的值关于中位数左右对称。

定义 $v$，$v_i$ 记录是否有和为子序列 $v \leftarrow v \operatorname{or} v \times 2^x$。

常数很小，可以通过此题，注意初始化。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bitset<2000005>vis;
int n,cnt;
int main(){
    cin>>n;
    vis[0]=1;
    for(int i=1;i<=n;i++){
    	int a;
    	cin>>a;
    	vis|=vis<<a;
		cnt+=a;
	}
    for(int i=(cnt+1)>>1;i<=cnt;i++){
    	if(vis[i]){
           	cout<<i<<'\n';
            return 0;
        }
	}
    return 0;
}
```

---

