# The Minimum Number of Variables

## 题目描述

You've got a positive integer sequence $ a_{1},a_{2},...,a_{n} $ . All numbers in the sequence are distinct. Let's fix the set of variables $ b_{1},b_{2},...,b_{m} $ . Initially each variable $ b_{i} $ $ (1<=i<=m) $ contains the value of zero. Consider the following sequence, consisting of $ n $ operations.

The first operation is assigning the value of $ a_{1} $ to some variable $ b_{x} $ $ (1<=x<=m) $ . Each of the following $ n-1 $ operations is assigning to some variable $ b_{y} $ the value that is equal to the sum of values that are stored in the variables $ b_{i} $ and $ b_{j} $ $ (1<=i,j,y<=m) $ . At that, the value that is assigned on the $ t $ -th operation, must equal $ a_{t} $ . For each operation numbers $ y,i,j $ are chosen anew.

Your task is to find the minimum number of variables $ m $ , such that those variables can help you perform the described sequence of operations.

## 说明/提示

In the first sample, you can use two variables $ b_{1} $ and $ b_{2} $ to perform the following sequence of operations.

1. $ b_{1} $ := $ 1 $ ;
2. $ b_{2} $ := $ b_{1}+b_{1} $ ;
3. $ b_{1} $ := $ b_{1}+b_{2} $ ;
4. $ b_{1} $ := $ b_{1}+b_{1} $ ;
5. $ b_{1} $ := $ b_{1}+b_{2} $ .

## 样例 #1

### 输入

```
5
1 2 3 6 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 6 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6
2 4 8 6 10 18
```

### 输出

```
3
```

# 题解

## 作者：C20203030 (赞：5)

## 一、题目
**题目描述**

有$n$个数$a_i$，还有$m$个容器，第一步把$a_1$赋值给某一个容器，然后每一步的赋值操作就是选两个容器的和赋值给一个容器（随便选，不要求容器不同，但求和容器必须有值），第$i$步赋值操作的返回值必须等于$a_i$（从$2$开始算），求$m$的最小值，没有这样的$m$输出$-1$。

**数据范围**

$n\leq 23$，$1\leq a_i\leq 1e9$
## 二、解法
这个数据范围很容易联想到状态压缩吧，我们设$dp[s]$为我们把当前状态$a_i$一定出现在容器里的为$1$，不一定在容器里的为$0$，那么最终需要状态为$dp[2^n]$，也就是$a_n$一定在容器里，初始化$dp[2^1]$为$1$，一开始$a_1$一定在容器里（具体实现时需要从$0$开始存）

考虑转移，我们现在需要凑出$i$，那么我们枚举$i$之前的两个数（$i$之后的不可能出现），这两个数的和为$i$，然后我们把当前状态去掉$i$这一位之后添加上枚举的两个数的位置继续搜索，得到返回值之后我们和当前状态的容器数（也就是$1$的个数）取一个最大值然后更新答案即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int M = 23;
int read()
{
    int x=0,flag=1;
    char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,a[M],dp[1<<M];
int dfs(int x,int p)
{
    if(dp[x]) return dp[x];
    int c=__builtin_popcount(x),res=25;
    for(int i=0;i<p;i++)
        for(int j=0;j<=i;j++)
            if(a[i]+a[j]==a[p])
            {
                int t=dfs((x&~(1<<p))|(1<<p-1)|(1<<i)|(1<<j),p-1);
                res=min(res,max(t,c));
            }
    return dp[x]=res;
}
int main()
{
    n=read();
    for(int i=0;i<n;i++)
        a[i]=read();
    dp[1]=1;
    int t=dfs(1<<(n-1),n-1);
    if(t==25) puts("-1");
    else printf("%d\n",t);
}

```



---

## 作者：shinzanmono (赞：0)

数据范围较小，考虑状压。

设 $f_{i,S}$ 表示当前获得了 $a_i$，桶里剩余的编号集合为 $S$ 的所需最小桶数。枚举可行数对、目标点转移，时间复杂度 $O(n^42^n)$，空间复杂度 $O(n2^n)$。

可以发现 $f_i$ 的取值只与 $f_{i-1}$ 有关，所以滚动数组将空间消掉一维 $n$。

考虑两种转移，$f_{i,S\cup\{i\}}\leftarrow f_{i,S}+1$，$f_{i,(S\cup\{i\})/\{j\}}\leftarrow f_{i,S}$。不和任意转移数对有关系（除了 $S$ 中需要含有数对中的两个值）。那么不放只保留每个状态的第一次转移，这样总共只需要做 $O(n2^n)$ 转移，去除无关转移可过。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
const int inf=0x3fffffff;
int a[25],f[1<<23],g[1<<23];
bool vis[1<<23];
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin>>n;
  for(int i=0;i<n;i++)std::cin>>a[i];
  std::fill(f,f+(1<<n),inf);
  f[1]=1;
  for(int i=1;i<n;i++){
    std::fill(g,g+(1<<i+1),inf);
    std::fill(vis,vis+(1<<i+1),0);
    std::vector<std::pair<int,int>>vec;
    for(int j=0;j<i;j++)
      for(int k=j;k<i;k++)
        if(a[j]+a[k]==a[i])vec.push_back(std::make_pair(j,k));
    if(vec.empty())std::cout<<"-1\n",exit(0);
    for(auto p:vec){
      int u=p.first,v=p.second;
      for(int s=1;s<1<<i;s++){
        if(vis[s]||(s>>u&1)==0||(s>>v&1)==0)continue;
        vis[s]=true;
        g[s|(1<<i)]=std::min(g[s|(1<<i)],f[s]+1);
        for(int j=0;j<i;j++){
          if((s>>j&1)==0)continue;
          g[s^(1<<i)^(1<<j)]=std::min(g[s^(1<<i)^(1<<j)],f[s]);
        }
      }
    }
    std::swap(f,g);
  }
  int ans=inf;
  for(int i=0;i<1<<n;i++)ans=std::min(ans,f[i]);
  std::cout<<ans<<"\n";
  return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：状压，代码详细注释。
### 前言：
此题不是很难，建议自己好好想想。
### 思路：
显然对 $N$ 状压，发现后效性就是对于 $a_i$，是否用一个容器把它记下来。

设 $f[i][k]$ 中 $i$ 表示拼到 $a_i$，$k$ 二进制下第 $i$ 位是 $1$ 表示记下来，否则不记的情况下，最小容器数。

转移：
- 先枚举 $a_i$ 由哪两个 $a$ 拼起来。
  + $a_i = a_x + a_y$。
- 枚举上一次的状压情况。
- 判断枚举的状压情况是否和枚举的两个 $a$ 相符。
  + 上次这种状压情况是否存在。
  + 枚举的两个 $a$ 在这种状压情况下是否被存储下来。
- 现在的状压情况：上一次的情况加上把 $a_i$ 存下来的情况。
- 直接再开一个 $b$。
- 枚举之前的容器，找一个替换。

记得把 $f[i][k]$ 的第一位滚动掉。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 24, INF = 0x3f3f3f3f;

namespace Josh_zmf {
	
	int N, a[Maxn], f[2][1<<23];
	struct node { int x, y; };
	vector <node> have[Maxn];

	inline int lowbit(int t) { return t&(-t); }

	inline int main() {
		cin>> N;
		for(int i=0; i<N; i++)	cin>> a[i]; // 状压下标从 0 开始方便
		for(int i=0; i<N; i++) { // 预处理一下哪两个 a 可以凑出一个 a[i]
			for(int j=0; j<N; j++) {
				for(int k=j; k<N; k++) { // k = j, 因为两个一样的也可以拼
					if(a[j] + a[k] == a[i])	have[i].push_back({j, k});
				}
			}
		}
		memset(f[0], 0x3f, (1<<N)<<2), memset(f[1], 0x3f, (1<<N)<<2); // 初始化，这些情况都不合法
		f[0][1] = 1; // a[1] 必须选
		for(int i=1; i<N; i++) {
			memset(f[i&1], 0x3f, (1<<i)<<2); // 滚动数组要清空
			for(node tmp: have[i]) { // 枚举由哪两个点转移过来
				int x = tmp.x, y = tmp.y;
				for(int k=(1<<i)-1; ~k; k--) {
					if(f[(i&1)^1][k] == INF)	continue; // 不存在这种情况
					if(!((k>>x)&1) || !((k>>y)&1))	continue; // x/y 没存下来
					int now = k|(1<<i); // a[i] 必须存下来
					f[i&1][now] = min(f[i&1][now], f[(i&1)^1][k]+1); // 新添一个容器
					for(int kk=k; kk; kk-=lowbit(kk)) { // 枚举哪个容器被替换
						now = (kk-lowbit(kk))|(k&(lowbit(kk)-1))|(1<<i);
						f[i&1][now] = min(f[i&1][now], f[(i&1)^1][k]);
					}
				}
			}
		}
		int ans = INF;
		for(int k=(1<<N)-1; ~k; k--) {
			if(!((k>>(N-1))&1))	continue;
			ans = min(ans, f[(N-1)&1][k]);
		}
		if(ans == INF)	cout<< "-1";
		else 	cout<< ans;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走把。 : )

---

