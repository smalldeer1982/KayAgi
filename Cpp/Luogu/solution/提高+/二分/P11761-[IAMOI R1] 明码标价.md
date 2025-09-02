# [IAMOI R1] 明码标价

## 题目背景

小 C 拉小 L 去买东西。

## 题目描述

商场里有 $n$ 个商品，第 $i$ 个商品的价格为 $a_i$。由于小 C 具有选择困难症，所以小 L 想通过以下方式挑选购买一个商品：

小 L 既不想要选择最便宜的商品（质量差），也不想要选择最贵的商品（性价比低），于是，他定义 $m$ 个商品价格的中位数为按照价格从小排序后最中间的商品价格。具体的说，排序后第 $\lfloor\frac{m+1}{2}\rfloor$ 个商品的价格就是这 $m$ 个商品价格的中位数。

同时，小 L 准备把这 $n$ 个商品按照用处分为连续的 $k$ 段，并在每段中取出价格为中位数的商品。接下来，他再次取出这些商品之中价格为中位数的商品，选出这个唯一的商品购买。

然而小 C 似乎并不同意这个方案，原因是小 C 的划分与小 L 的划分并不相同。于是，他们决定各退一步，采取最公平的方式选择商品。具体的，他们找出按照**任意划分方案**而得出的商品价格（可能存在一个商品被找出多次，也要计算多次），再次取出价格为中位数的商品，选出这个唯一的商品购买。

然而划分的方案可能有很多种，小 L 和小 C 被绕晕了。所以，他们想请你帮忙，他们最后选出的商品价格是多少？

### 形式化题意

定义 $\operatorname{mid}(\{a_1,a_2,\cdots,a_n\})$ 表示在可重集合中 $a_1\sim a_n$ 的中位数。形式化地来说，$a_1\sim a_n$ 的中位数为将 $a_1$ 到 $a_n$ 从小到大排序后， $a_{\lfloor\frac{n+1}{2}\rfloor}$ 的值。

现有一个长度为 $n$ 的数列 $a_1\sim a_n$。定义了 $f(l,r)=\operatorname{mid}(\{a_l,a_{l+1},\cdots,a_r\})$。

定义划分和划分的权值：

+ 一个划分被定义为一个长度为任意一个在 $[0,n]$ 的整数 $k$ 的序列 $l$，满足 $1\ {\color{red}{\le}}\ l_1<l_2<\cdots<l_k<n$。

+ 两个划分不同当且仅当两个划分的 $k$ 不相同或者存在一个位置使得两个划分的 $l$ 不相同。

+ 当 $k\not=0$ 时，划分的权值是 $\operatorname{mid}(\{f(1,l_1),f(l_1+1,l_2),\cdots,f(l_k+1,n)\})$。

+ 否则，划分的权值是 $\operatorname{mid}(\{f(1,n)\})$。

求所有互不相同的划分权值的可重集合的 $\operatorname{mid}$。

## 说明/提示

### 样例解释

共有 $4$ 种划分方案，分别为 $\{\{1\},\{2\},\{3\}\},\{\{1,2\},\{3\}\},\{\{1\},\{2,3\}\},\{\{1,2,3\}\}$，其中：

$\operatorname{mid}(\{1\})=1,\operatorname{mid}(\{2\})=2,\operatorname{mid}(\{3\})=3,\operatorname{mid}(\{1,2\})=1,\operatorname{mid}(\{2,3\})=2,\operatorname{mid}(\{1,2,3\})=2$；

这 $4$ 种划分的权值分别为 $\operatorname{mid}(\{1,2,3\})=2,\operatorname{mid}(\{1,3\})=1,\operatorname{mid}(\{1,2\})=1,\operatorname{mid}(\{2\})=2$；

最终答案即为 $\operatorname{mid}(\{1,1,2,2\})=1$。

### 数据范围

**本题采用捆绑测试。**

| Subtask | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $15$ | 无 | $13$ |
| $2$ | $40$ | A | $17$ |
| $3$ | $40$ | 无 | $20$ |
| $4$ | $100$ | A | $23$ |
| $5$ | $100$ | 无 | $27$ |

特殊性质 A：保证 $a$ 为一个 $1\sim n$ 的排列。

对于所有数据，保证 $2\le n\le 100$，$1\le a_i\le 10^9$。

注：在 C++ 语言中，你可以使用类型 `__int128` 来存储范围在 $-2^{128}\sim 2^{128}-1$ 的整数。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1```

# 题解

## 作者：Down_syndrome (赞：4)

## subtask 1

可以发现划分可以理解成插板，故共有 $2^{n-1}$ 种划分方式。暴力 $O(n2^n\log n)$。

## subtask 2

发现题目中有三重 $\operatorname{mid}$，我们一重一重考虑。

首先对于第一重，我们考虑预处理出所有区间 $[l,r]$ 的中位数。因为数据范围较小，$O(n^3)$ 处理即可。

然后对于第二重，我们求算出对于每个商品在第二重中取到中位数的次数。具体的，令 $f_{i,j,k,l}$ 表示第 $i$ 个商品在划分了前 $j$ 个商品后，有 $k$ 个区间中位数比它大，有 $l$ 个区间中位数比它小的方案数。注意等于比较难处理，所以依托于排列的性质。转移为：

$$f_{i,j,k,l}=\sum\limits_{p=0}^{j-1} [\operatorname{mid}(a_{p+1},\dots,a_j)<a_i]f_{i,p,k-1,l}+[\operatorname{mid}(a_{p+1},\dots,a_j)>a_i]f_{i,p,k,l-1}$$

同样处理出 $g_{i,j,k,l}$ 表示第 $i$ 个商品在划分了后 $j$ 个商品后，有 $k$ 个区间中位数比它大，有 $l$ 个区间中位数比它小的方案数。

假设现在有 $m$ 个数，对于一个数 $x$，令比它小的数的个数为 $p$，比它大的数的个数为 $q$，则 $x$ 是中位数的充要条件是 $p=q$ 或 $p+1=q$。

因此，一个中位数为 $a_i$ 的区间 $[l,r]$ 成为了多少次第二重的中位数的个数就是 $\sum f_{i,l-1,a,b}\times g_{i,r+1,c,d}(a+c=b+d\lor a+c+1=b+d)$。

于是我们就在 $O(n^5)$ 的时间复杂度算出了答案。

## subtask 3

容易发现给原序列离散化一下就好了。

## subtask 4

注意我们的限制是 $a+c=b+d\lor a+c+1=b+d$，可以写成 $a-b=d-c\lor a-b+1=d-c$。也就是说，单独对于前缀而言，我们不关心 $a,b$ 的值具体是多少，我们只关心它们的差，于是只用把差记录下来即可，再类似地转移就行。后缀亦然。时间复杂度 $O(n^4)$，但是实际跑的很快，所以也能通过。

同时注意 dp 值可以达到 $2^{n-1}$，需要使用 `__int128`。

## subtask 5

subtask 4 加上离散化。

## 更优做法

因为不能超过 `__int128` 的存储极限，所以数据不太能造大，而且在此数据下的 $O(n^4)$ 做法跑的挺快，于是便放过了。

以下是 $O(n^3\log n)$ 的做法：

考虑处理中位数的套路二分，二分答案为 $mid$，将序列中大于等于 $mid$ 的设为 $1$，将序列中小于 $mid$ 的设为 $0$，再次按照上述过程 dp 便能求出答案是否大于等于 $mid$。

因此第一维便减小到了 $O(1)$，复杂度降为 $O(n^3\log n)$。

---

## 作者：sbno333 (赞：3)

中位数二分来的实惠。

考虑小于等于 $mid$ 的记作 $-1$，否则记作 $1$，我们查看此时中位数是否是 $-1$，容易证明单调性。

这有个很好的性质，就是一个这样的序列 $-1$ 是中位数，当且仅当序列和小于等于 $0$。

考虑 dp。

设 $dp_{i,c}$ 表示在 $i$ 的前缀中，每一段的中位数的和等于 $c$ 的方案数。

转移考虑枚举 $j$，表示最后一段的第一个数的下标，然后计算这一段中位数，然后把 $dp_{j-1,-n\sim n}$ 直接拿过来转移就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[109];
int b[109];
int n;
__int128 dp[109][209];//第二维都多加了 100，这里的 dp[i][j] 表示实际上的 dp[i][j-100}
int check(){
	dp[0][100]=1;
	for(int i=1;i<=n;i++){
		int sum;
		sum=b[i];
		for(int c=0;c<=200;c++){
			dp[i][c]=0;
		}
		for(int j=i-1;j>=0;j--){
			if(sum<=0){
				for(int c=0;c<=200;c++){
					dp[i][c]+=dp[j][c+1];
				}
			}else{
				for(int c=1;c<=200;c++){
					dp[i][c]+=dp[j][c-1];
				}
			}
			sum+=b[j];
		}
	}
	__int128 ans;
	ans=0;
	for(int i=0;i<=200;i++){
		ans+=dp[n][i]*(i<=100?-1:1);
		
	}
	return (ans<=0?-1:1);
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l,r;
	l=1,r=1000000000;
	while(l<r){
		int mid;
		mid=l+r;
		mid>>=1;
		for(int i=1;i<=n;i++){
			b[i]=(a[i]<=mid?-1:1);
		}
		if(check()==-1){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}
```

## 更优解

注意到这个解法的性质过于优秀，我们尝试冲击平方。

回想一下我们 DP 有哪些比较普通的优化方法。

其中一个就是拿之前做的省掉一部分工序。

什么意思？就是转移可能有重复的，我们不想重复做。

我们试试？

注意到计数器 $sum$ 变为 $0$ 时似乎情况出现了些许不同。

此时继续下去与此时的 $dp_{j,-c\sim c}$ 转移的时候是一致的。

我们可以直接省掉，把 $dp_{j,-c\sim c}$ 的成果直接拿过来。

当然别忘了特判 $j=0$，这时候的转移可不太一样。

添加这条语句。

```cpp
if(sum==0&&j){
  for(int c=0;c<=200;c++){
    dp[i][c]+=dp[j][c];
  }
  break;
}
```

虽然复杂度没变，但是代码却有了下限，如果 $1$ 和 $-1$ 随机生成，效果会非常好。

事实上我们增加这段后时间从 $80$ 毫秒来到了 $69$ 毫秒，可以说确实有了进步。

我们继续探索，我们发现如果计数器 $sum$ 变成了 $0$，在此之前其正负性一定不变，因为之前每次就加一或者减一，然后就判定，来不及改变。

而对于正负性相同的 $sum$，我们转移是一样的啊！

所以可以直接前缀和优化这部分。

至于判断是正的还是负的，我们看 $sum$ 最开始的值即可。

不过还有个难点就是如何确定在哪个位置 $sum$ 最早取到 $0$。

我们考虑 $i$ 移动时，每次会让每个 $sum$ 都增加一个数，我们转换成 $sum$ 没加就是目标从 $0$ 转换成了另一个数。

具体的，我们维护 $jj_i$ 表示增加的数的前缀和为 $i$ 的最大的 $j$。

为啥是前缀和？这个好维护。

然后在增加一个数增加多少，指针就增加多少。

然后算上自己就行。

如下所示，第一个是维护指针，第二个算自己的语句，实际写的时候二者并不会写在一起。

当然，细节较多，别忘了 $sum$ 可能取不到 $0$。

```cpp
zz+=b[i];//zz 表示指针
jj[zz]=i;
```

然后我们就得到了一个复杂度 $O(n^2\log n)$ 的算法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[109];
int b[109];
int n;
__int128 dp[109][209];
__int128 qz[109][209];
int jj[209];
int zz;
int check(){
	dp[0][100]=1;
	for(int i=0;i<=200;i++){
		jj[i]=-1;//sum 取不到 0 的情况认为是 -1
	}
	jj[100]=0;
	zz=100;
	qz[0][100]=1;
	for(int i=1;i<=n;i++){
		zz+=b[i];
		for(int c=0;c<=200;c++){
			dp[i][c]=0;
		}
		if(jj[zz]==-1){
			if(b[i]<=0){
				for(int c=0;c<=200;c++){
					dp[i][c]+=qz[i-1][c+1];
				}
			}else{
				for(int c=1;c<=200;c++){
					dp[i][c]+=qz[i-1][c-1];
				}
			}
		}else{
			if(b[i]<=0){
				for(int c=0;c<=200;c++){
					dp[i][c]+=qz[i-1][c+1]-qz[jj[zz]][c+1];
				}
			}else{
				for(int c=1;c<=200;c++){
					dp[i][c]+=qz[i-1][c-1]-qz[jj[zz]][c-1];
				}
			}
			for(int c=0;c<=200;c++){
				dp[i][c]+=dp[jj[zz]][c+1];
			}
			if(jj[zz]){
				for(int c=0;c<=200;c++){
					dp[i][c]+=dp[jj[zz]][c];
				}
			}
		}
		jj[zz]=i;
		for(int c=0;c<=200;c++){
			qz[i][c]=dp[i][c]+qz[i-1][c];
		}
	}
	__int128 ans;
	ans=0;
	for(int i=0;i<=200;i++){
		ans+=dp[n][i]*(i<=100?-1:1);
		
	}
	return (ans<=0?-1:1);
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l,r;
	l=1,r=1000000000;
	while(l<r){
		int mid;
		mid=l+r;
		mid>>=1;
		for(int i=1;i<=n;i++){
			b[i]=(a[i]<=mid?-1:1);
		}
		if(check()==-1){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}
```

这样我们的代码虽然常数很大，但是复杂度在那里，所以只需要跑 $20$ 毫秒，可以进入最优解第一页。

但是这道题还是受到整数类型影响，导致 $n$ 最大开到 $100$，挺可惜的。

---

## 作者：cxyMOI (赞：2)

显然可以 $O(n\log n)$ 求出给定划分方案的每段中位数的中位数。考虑随机化。对每个位置 $i\in[1,n)$，随机确定是否在 $a_i$ 后分割，并求出这组划分对应的得数。随机 $5000$ 组划分方案后再取这 $5000$ 个得数的中位数即可。

AC 代码：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;
int a[100];
int median(int l,int r){//[l,r)上的中位数
    vector<int> v;
    for(int i=l;i<r;i++){
        v.push_back(a[i]);
    }
    nth_element(v.begin(),v.begin()+(r-l-1)/2,v.end());
    return v[(r-l-1)/2];
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    mt19937 eng;
    vector<int> res;
    for(int t=0;t<5000;t++){
        int li=0;
        std::vector<int> v;
        for(int i=1;i<n;i++){
            if(eng()&1){
                v.push_back(median(li,i));
                li=i;
            }
        }
        v.push_back(median(li,n));
        nth_element(v.begin(),v.begin()+(v.size()-1)/2,v.end());
        res.push_back(v[(v.size()-1)/2]);
    }
    nth_element(res.begin(),res.begin()+(res.size()-1)/2,res.end());
    cout<<res[(res.size()-1)/2]<<endl;
    return 0;
}
```

---

## 作者：dyc2022 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dyc2022/p/18730867)
***
考虑一个非常经典的中位数 trick。

二分中位数 $mid$，将序列中 $\le mid$ 的位置钦定为 $-1$，$>mid$ 的位置钦定为 $1$。那么对于一个只包含 $\pm 1$ 的数列，它的中位数为 $-1$ 当且仅当序列之和 $\le 0$。

这是非常好的，因为我们已经把一个难以刻画的中位数转换成了易于转移的和。

二分出 $mid$ 后，考虑设计 $dp_{i,j}$ 表示在前 $i$ 个数字中任意分段，且每一段的中位数之和 $= j$ 的方案数。转移是简单的，$O(n)$ 的转移都能接受。只需要枚举 $i$ 所属的这一段的第一个位置，对替换成 $\pm 1$ 的序列做一个前缀和即可。

这里选择用一个 `std::unordered_map` 来存储 dp 数组，复杂度应当是 $O(n^3 \log n)$ 的。

那么这道题就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 106
using namespace std;
int n,a[N],b[N],sum[N];
unordered_map<int,__int128> dp[N];
int check(int mid)
{
    for(int i=1;i<=n;i++)
        b[i]=(a[i]>mid?1:-1),sum[i]=sum[i-1]+b[i];
    for(int i=0;i<=n;i++)dp[i].clear();
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=-i;j<=i;j++)
            for(int k=1;k<=i;k++)if(sum[i]-sum[k-1]>0)
                dp[i][j]+=dp[k-1][j-1];
            else dp[i][j]+=dp[k-1][j+1];
    __int128 ans=0;
    for(int i=-n;i<=n;i++)
        ans+=(i>0?1:-1)*dp[n][i];
    return ans>0;
}
main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    int l=1,r=2e9,ans;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid))l=mid+1;
        else ans=mid,r=mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：1)

# [[IAMOI R1] 明码标价](https://www.luogu.com.cn/problem/P11761)

对于第一个中位数操作，考虑记录 $t(l,r)$ 为**区间 $[l,r]$ 的中位数的下标，如果有多个，取最小的下标。**

可以暴力枚举区间 $[l,r]$，将数对 $(a_i,i),i\in[l,r]$ 排序，取中间的那一个。

计算 $t(l,r)$ 的复杂度为 $O(n^3\log n)$。

---

设一种划分长度为 $k$，其中区间为 $[l_1,r_1],[l_2,r_2],\dots,[l_k,r_k]$。

定义一个区间的权值 $c(l,r)$ 为数对 $(a_{t(l,r)},t(l,r))$，这个划分的**中区间**为每一个区间按 $c$ 排序后的中位数。

这个划分的**中中位数**为划分的中区间的 $t(l,r)$。

$cnt_i$ 表示**下标 $i$ 作为划分的中中位数**的划分数量，可以 `dp` 求。

定义 $f_{j,k,l}$ 表示考虑前 $j$ 个数，此时划分的区间权值小于 $(a_i,i)$ 的数量为 $k$，大于 $(a_i,i)$ 的数量为 $l$ 的方案数。

同理，定义 $g_{j,k,l}$ 表示后 $j$ 个数，此时划分的区间权值小于 $(a_i,i)$ 的数量为 $k$，大于 $(a_i,i)$ 的数量为 $l$ 的方案数。

转移：
$$
f_{j,k,l}=\sum_{lst=0}^{j-1}[c(lst+1,i)>(a_i,i)]f_{j,k,l-1}+\sum_{lst=0}^{j-1}[c(lst+1,i)<(a_i,i)]f_{j,k-1,l}\\
g_{j,k,l}=\sum_{lst=j+1}^{n+1}[c(i,lst-1)>(a_i,i)]g_{j,k,l-1}+\sum_{lst=j+1}^{n+1}[c(i,lst-1)<(a_i,i)]g_{j,k-1,l}\\
$$
转移完后计算 $cnt_i$。
$$
cnt_i=\prod_{i\in[l,r],t(l,r)=i} [(a-b)+(c-d)=0 \vee  (a-b)+(c-d)=-1]f_{l-1,a,b}\times g_{r+1,c,d}
$$

---

总划分的数量是好求的，即在 $n-1$ 个间隔中任选，总共 $2^{n-1}$ 种方案。

把这 $2^{n-1}$ 种方案排序，求出其中第 $2^{n-2}$ 个位置的数，这个数即为答案。

把 $(a_i,i)$ 排序，不断累加 $cnt_i$，直到 $sum\ge 2^{n-2}$，则当前的 $a_i$ 即为答案。

复杂度 $O(n^5)$，瓶颈在转移和统计答案。

发现只需要记录 $k-l$ 的值即可。可以降一维，复杂度 $O(n^4)$，常数很小，可以通过。

## Code

```cpp
#include<bits/stdc++.h>
#define ll __int128
#define Pair pair<int,int>
using namespace std;
const int MAXN=100+5;
int n,a[MAXN],t[MAXN][MAXN];
inline int calc(int l,int r){
	static Pair Now[MAXN];static int tmp;
	tmp=0;
	for(int i=l;i<=r;i++)Now[++tmp]=Pair(a[i],i);
	sort(Now+1,Now+tmp+1);
	return Now[(tmp+1)/2].second; 
} 
ll F[MAXN][MAXN*2],G[MAXN][MAXN*2],cnt[MAXN];
ll *f[MAXN],*g[MAXN];Pair id[MAXN];
inline bool cmp1(int x,int y){
	return Pair(a[x],x)>Pair(a[y],y);
}
inline bool cmp2(int x,int y){
	return Pair(a[x],x)<Pair(a[y],y);
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int l=1;l<=n;l++)for(int r=l;r<=n;r++)t[l][r]=calc(l,r);
	
	for(int i=0;i<=n+1;i++)f[i]=&F[i][MAXN],g[i]=&G[i][MAXN];
	for(int now=1;now<=n;now++){
		memset(F,0,sizeof F),memset(G,0,sizeof G);
		f[0][0]=1,g[n+1][0]=1;
		for(int i=1;i<=n;i++){
			for(int del=-n;del<=n;del++){
				for(int j=0;j<i;j++){
					if(cmp1(t[j+1][i],now))f[i][del-1]+=f[j][del];
					if(cmp2(t[j+1][i],now))f[i][del+1]+=f[j][del];
				}
			}
		}
		for(int i=n;i>=1;i--){
			for(int del=-n;del<=n;del++){
				for(int j=i+1;j<=n+1;j++){
					if(cmp1(t[i][j-1],now))g[i][del-1]+=g[j][del];
					if(cmp2(t[i][j-1],now))g[i][del+1]+=g[j][del];
				}
			}
		}
		for(int l=1;l<=now;l++)for(int r=now;r<=n;r++)if(t[l][r]==now){
			for(int k=-n;k<=n;k++){
				cnt[now]+=f[l-1][k]*g[r+1][-k]+f[l-1][k]*g[r+1][-k-1];
			}
		}
	}
	for(int i=1;i<=n;i++)id[i]=Pair(a[i],i);sort(id+1,id+n+1);
	ll all=0,res=1;for(int i=1;i<=n-2;i++)res=res*2;
	for(int _=1;_<=n;_++){
		int i=id[_].second;
		all+=cnt[i];
		if(all>=res-1){
			cout<<a[i]<<"\n";
			return 0;
		}
	}
}
```

---

## 作者：buowen123 (赞：1)

为什么各位的 DP 写得这么奇怪，我觉得很显然喵？

## 题目大意

给定一个长度为 $n$ 的序列 $a$，定义 $m$ 个数的中位数为其中第 $\left\lfloor \frac m 2\right\rfloor$ 大的数。

考虑将这个序列划分成若干段的所有方案。对于某种方案，求出每一段内 $a_i$ 的中位数，这些中位数的中位数就是该方案的权值。

求所有方案权值的中位数，$1\le n\le 100$。

## 题目解决

发现直接做不好做。二分答案 $x$，表示答案能否 $\ge x$，将 $\ge x$ 的数改为 $1$，$\le x$ 的数改为 $-1$。**此时，若干个数的中位数 $\ge x$ 即等价于修改之后这些数的和 $\gt0$。**

再将区间的权值按照是否 $\ge x$ 修改定义为 $1$ 或 $-1$，根据上文性质可以推出，所有方案的权值和 $\gt0$ 即等价于答案可以做到 $\ge x$。

设修改后的数组为 $c_i$。计算一种划分方案的权值，此时只需要看这种方案的以下两个信息：
- 计算该方案将序列划分的段数，设为 $x$；
- 有多少段的和 $\gt0$（根据上文性质），设为 $y$。

则和 $\le0$ 的段数为 $x-y$，方案权值为 $1$ 当且仅当 $y-(x-y)>0$，即 $y>2x$。

考虑设 $f_{i,x,y}$ 表示前 $i$ 个数分为 $x$ 段，有 $y$ 段和 $\gt0$ 的方案数。

转移枚举 $j$，设最后一段为 $[j+1,i]$。分类讨论：
- 若 $c_{j+1}+c_{j+2}+\dots+c_i\gt0$，则 $f_{i,x,y}\gets f_{j,x-1,y-1}$；
- 否则，有 $f_{i,x,y}\gets f_{j,x-1,y}$。

初始状态为 $f_{0,0,0}=1$。对 $c$ 前缀和优化可以做到 $O(n^4)$。事实上可以优化到 $O(n^3\log n)$ 或 $O(n^3)$，但编写难度较大。

最后对于每个 $(x,y)$，根据 $x,y$ 的关系，求出这样的区间的权值，乘以这类区间的个数 $f_{n,x,y}$，再求和即可。

时间复杂度？总时间复杂度 $O(n^4\log n)$，但由于 $x\le i,y\le x,j\le y$，实际上会带上一个 $\le1$ 的常数，跑得飞快。

代码中的判断方式可能与上文不尽相同。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define i1 __int128
const int maxn=100+5;
int n,a[maxn],c[maxn],b[maxn];
i1 f[maxn][maxn][maxn];
bool chk(int x){
	for(int i=1;i<=n;i++)
		c[i]=(a[i]>=x ? 1 : -1)+c[i-1];	
	memset(f,0,sizeof(f)); 
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int x=1;x<=i;x++){
			for(int y=0;y<=x;y++){
				for(int j=0;j<i;j++){
					f[i][x][y]+=f[j][x-1][y-(c[j]<c[i])];
				}
			}
		}
	}
	i1 ans1=0,ans2=0;
	for(int x=1;x<=n;x++){
		for(int y=0;y<=x;y++){
			ans1+=f[n][x][y]*(y*2>x);
			ans2+=f[n][x][y]*(y*2<=x);
		}
	}
	return ans1>ans2;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-(b+1);
	int l=1,r=len;
	while(l<r){
		int mid=l+r+1>>1;
		if(chk(b[mid])) l=mid;
		else r=mid-1;
	}
	cout<<b[l]<<'\n';
}
```

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[IAMOI R1] 明码标价](https://www.luogu.com.cn/problem/P11761)
~~赛时犯了一个很脑瘫的错误：离散化后输出答案时没有还原为原数，这下糖丸了~~

本题只需要考虑每个数的相对大小，因此可以离散化缩小值域。特殊的，若两数相同，定义位置靠后的数字较大。

首先我们考虑划分后的**每一段的中位数数中的中位数**会在哪一段中。

首先预处理 $mid_{l,r}$ 表示区间 $\left[l,r\right]$ 的中位数。

若划分后的**每一段的中位数数中的中位数**在区间 $\left[l,r\right]$ 这一段中，则 $\left[1,l-1\right]$ 和 $\left[r+1,n\right]$ 划分出的若干区间一定满足其中**中位数 $<mid_{l,r}$ 和中位数 $>mid_{l,r}$ 的区间个数相同**或**中位数 $<mid_{l,r}$ 比中位数 $>mid_{l,r}$ 的区间个数恰好少 $1$**。

这个时候我们可以发现这是一个对前缀/后缀的约束。

令 $pre_{i,j,k}$ 表示将前缀 $1\sim i$ 划分为若干段，其中中位数比 $j$ 小的和比 $j$ 大的段的数量差为 $k$（此处差特指比 $j$ 小的 $-$ 比 $k$ 大的）的方案数。

同理，定义 $suf_{i,j,k}$ 用来满足后缀约束。

不难发现 $pre$ 和 $suf$ 可以 DP 推出。

$pre_{i,j.k}=\sum\limits_{l=0}^{i-1}pre_{l,j,k-\left[mid_{l+1,i}<j\right]}$

同理可推出 $suf$。

接下来我们枚举每一个区间，计算出划分后的**每一段的中位数数中的中位数**在该区间中的方案数。

不难发现，对于任意一个区间 $\left[l,r\right]$，这样的方案数为 $\sum\limits_{i}pre_{l-1,mid_{l,r},i}\times \left(suf_{r+1,mid_{l,r},-i}+\times suf_{r+1,mid_{l,r},-i-1}\right)$。

这样可以求出每一个区间的中位数作为划分后的**每一段的中位数中的中位数**的方案数。把所有区间的中位数按照大小排序，并依次累加即可。

时间复杂度是 $O\left(n^4\right)$。

共有 $2^{n-1}$ 种划分方案，因此若累加的数 $\ge \lfloor\frac{2^{n-1}+1}{2}\rfloor$，则当前即为答案，直接输出即可。**注意千万别忘记还原为原数！！！**

代码：

```cpp
#include <bits/stdc++.h>
#define int __int128
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[105];

void write(int x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int n, len, cnt, A[105], p[105], temp[105], ans[10005], l[10005], r[10005], mid[105][105], pre[105][105][205], suf[105][105][205];

struct node
{
	int val, num;
} a[10005];

bool cmp(node q, node p)
{
	return q.val < p.val;
}

int Qpow(int t, int p)
{
	int Ans = 1;
	while (p)
	{
		if (p & 1) Ans *= t;
		t *= t;
		p /= 2; 
	}
	return Ans;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		A[i] = read();
	for (int i = 1; i <= n; i++)
		temp[i] = A[i];
	sort(temp + 1, temp + n + 1);
	auto endp = unique(temp + 1, temp + n + 1);
	for (int i = 1; i <= n; i++)
		A[i] =  lower_bound(temp + 1, endp, A[i]) - temp;
	len = endp - temp - 1;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
		{
			cnt++;
			l[cnt] = i;
			r[cnt] = j;
			for (int k = i; k <= j; k++)
				p[k - i + 1] = A[k];
			sort(p + 1, p + j - i + 2);
			mid[i][j] = p[(j - i + 2) / 2];
		}
	for (int i = 1; i <= len; i++)
		pre[0][i][100] = suf[n + 1][i][100] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= len; j++)
			for (int k = 100 - i; k <= 100 + i; k++)
				for (int l = 0; l < i; l++)
				{
					int qwq = mid[l + 1][i], now = k;
					if (qwq <= j) now--;
					else now++;
					if (now < 100 - l || now > 100 + l) continue; 
					pre[i][j][k] += pre[l][j][now];
				}
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= len; j++)
			for (int k = 100 - i; k <= 100 + i; k++)
				for (int l = n + 1; l > i; l--)
				{
					int qwq = mid[i][l - 1], now = k;
					if (qwq < j) now--;
					else now++;
					if (now < 100 - l || now > 100 + l) continue;
					suf[i][j][k] += suf[l][j][now];
				}	
	for (int i = 1; i <= cnt; i++)
	{
		int L = l[i], R = r[i];
		int qwq = mid[L][R];
		int tot = 0;
		for (int j = 0; j <= 200; j++)
		{
			tot += pre[L - 1][qwq][j] * suf[R + 1][qwq][200 - j];
			if (200 - j - 1 >= 0) tot += pre[L - 1][qwq][j] * suf[R + 1][qwq][200 - j - 1];
		}	
		ans[i] = tot;
	}		
	for (int i = 1; i <= cnt; i++)
	{
		a[i].num = i;
		a[i].val = mid[l[i]][r[i]];
	}
	sort(a + 1, a + cnt + 1, cmp);
	int now = 0;
	int Mid = (Qpow(2, n - 1) + 1) / 2;
	for (int i = 1; i <= cnt; i++)
	{
		now += ans[a[i].num];
		if (now >= Mid)
		{
			write(temp[a[i].val]);
			putchar('\n');
			exit(0);
		}
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

建议评蓝。

先预处理出 $l\sim r$ 的中位数，记作 $c_{l,r}$。

二分一个最大的 $x$，使得『「每段中位数」的中位数 $\le x$ 的划分个数』小于等于『总划分个数的一半』。

这种求划分的问题，结合数据范围，考虑 dp。$f_{i,j,k}$ 表示前 $i$ 个数划分 $j$ 段，排名（这里排名定义是当前 $\le x$ 的数的个数）为 $k$ 的方案数。

枚举当前段右端点 $p$。

- 如果 $c_{i+1,r}\le x$，$x$ 的排名会加 $1$，$f_{i,j,k}\rightarrow f_{p,j+1,k+1}$。
- 否则 $x$ 的排名不变，$f_{i,j,k}\rightarrow f_{p,j+1,k}$。

若划分 $i$ 段，中位数 $\le x$，意思是 $x$ 的排名要大于 $\dfrac{i+1}2$，答案为 $\sum\limits_{i=1}^n\sum\limits_{j=\frac{i+1}2}^nf_{n,i,j}$。

单次 dp $O(n^4)$，二分一只 $\log$（答案只会是 $a$ 中的数），时间复杂度 $O(n^4\log n)$。

```cpp
int n,rs,a[N],b[N],t[N],c[N][N]; lll d[N],f[N][N][N];
lll cc(int x) {
	lll sm=0; mst(f,0),f[0][0][0]=1;
	for(int i=0;i<n;i++) for(int j=0;j<=i;j++) for(int k=0;k<=j;k++) for(int p=i+1;p<=n;p++)
		f[p][j+1][k+(c[i+1][p]<=b[x])]+=f[i][j][k];
	for(int i=0;i<=n;i++) for(int j=i+1>>1;j<=n;j++) sm+=f[n][i][j];
	return sm;
}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=b[i]=rd();
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) {
		for(int k=1;k<=j-i+1;k++) t[k]=a[i+k-1];
		sort(t+1,t+2+j-i),c[i][j]=t[j-i+2>>1];
	}
	for(int l=1,r=n,md;l<=r;) cc(md=l+r>>1)>=(lll)1<<n-2?r=(rs=md)-1:l=md+1;
	wr(b[rs],"\n");
}
```

---

## 作者：lam_dyr (赞：0)

## 题意

~~好像也没有多简化~~

给定一个长度为 $n$ 的数列 $a$。定义 $f(l, r) = \operatorname{mid}(\{a_l, a_{l+1}, \dots, a_r\})$，表示子数组 $a_l \sim a_r$ 的中位数。

一个划分被定义为一个长度为 $k$ 的序列 $l$，满足 $1 \le l_1 < l_2 < \dots < l_k < n$。

当 $k \ne 0$ 时，划分的权值是 $\operatorname{mid}(\{f(1, l_1), f(l_1+1, l_2), \dots, f(l_k+1, n)\})$。

否则，划分的权值是 $\operatorname{mid}(\{f(1, n)\})$。

求所有互不相同的划分权值的可重集的中位数。

## 思路

本题的关键在于如何有效地计算所有划分的权值，并找到这些权值的中位数。朴素的思路是枚举所有划分，计算每个划分的权值，然后求所有权值的中位数。但是 $O(2^n)$ 的复杂度让我们不得不考虑优化。

首先我们不妨换位思考。求所有划分权值的中位数，可以转化为求第 $k$ 大的划分权值。而判断一个值 $x$ 是否是第 $k$ 大的划分权值，可以通过统计有多少个划分权值 $\le x$ 来实现。

其次由于我们需要频繁计算子数组的中位数，因此可以预先计算所有子数组的中位数，这样，可以大大减少计算量。

然后可以使用动态规划来统计权值小于等于 $x$ 的划分数量。

状态定义：设 `dp[i][s][c]` 表示考虑了前 $i$ 个元素，划分成了 $s$ 段，其中有 $c$ 个段的中位数小于等于 $x$ 的划分数量。

状态转移：枚举最后一个段的结束位置 $j$，如果 $a_{i+1} \sim a_j$ 的中位数小于等于 $x$，则 $c$ 增加 $1$。

最后需要根据划分数量来判断当前值是否是中位数。由于所有可能的中位数都存在于预处理出的子数组的中位数集合中，因此只需要在这些值中二分即可。

## 时间复杂度

- 预处理：$O(n^3 \log n)$
- 动态规划：$O(n^3)$
- 二分查找：$O(\log n^2)$
- 总时间复杂度：$O(n^3 \log n + n^3 \log n) = O(n^3 \log n)$

注意本题值域较大，需要 `__int128` 存储。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 int128;
string toString(int128 x) {
    if(x == 0) return "0";
    bool neg = false;
    if(x < 0) { neg = true; x = -x; }
    string s;
    while(x > 0) {
        s.push_back('0' + (int)(x % 10));
        x /= 10;
    }
    if(neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}
int n;
int a[105];
int seg[105][105];
void init(){
    for (int l = 1; l <= n; l++){
        vector<int> temp;
        for (int r = l; r <= n; r++){
            temp.push_back(a[r]);
            vector<int> t = temp;
            sort(t.begin(), t.end());
            int len = t.size();
            int idx = (len+1)/2 - 1; 
            seg[l][r] = t[idx];
        }
    }
}
int128 count(int X) {
    static int128 dp[105][105][105];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++){
        for (int s = 0; s <= i; s++){
            for (int c = 0; c <= s; c++){
                if(dp[i][s][c] == 0) continue;
                for (int j = i+1; j <= n; j++){
                    int med = seg[i+1][j];
                    int add = (med <= X) ? 1 : 0;
                    dp[j][s+1][c+add] += dp[i][s][c];
                }
            }
        }
    }
    int128 tot = 0;
    for (int s = 1; s <= n; s++){
        int res = (s+1)/2;
        for (int c = res; c <= s; c++){
            tot += dp[n][s][c];
        }
    }
    return tot;
}
int128 total(int n) {
    int128 res = 1;
    for (int i = 1; i <= n-1; i++){
        res *= 2;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    init();
    set<int> se;
    for (int l = 1; l <= n; l++){
        for (int r = l; r <= n; r++){
            se.insert(seg[l][r]);
        }
    }
    vector<int> can(se.begin(), se.end());
    sort(can.begin(), can.end());
    int128 tot = total(n);
    int128 target = (tot + 1) / 2;
    int ans = -1;
    for (int X : can){
        int128 cnt = count(X);
        if (cnt >= target) { ans = X; break; }
    }
    cout << ans << "\n";
    return 0;
}
```

---

