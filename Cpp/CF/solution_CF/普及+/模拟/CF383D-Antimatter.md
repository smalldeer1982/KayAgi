# Antimatter

## 题目描述

给定长度为n的序列，可以给任意一个数加上正号或者负号，求有多少种连续子段和为0的情况

## 说明/提示

样例1可能的情况为[1+, 2-], [1-, 2+], [2+, 3-], [2-, 3+], [3+, 4-], [3-, 4+], [1+, 2+, 3-, 4-], [1+, 2-, 3+, 4-], [1+, 2-, 3-, 4+], [1-, 2+, 3+, 4-], [1-, 2+, 3-, 4+]，[1-, 2-, 3+, 4+]

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
12
```

# 题解

## 作者：JacoAquamarine (赞：3)

可以看出本题可以使用DP。

可将前 $i$ 个和为 $j$ 的方案数表示为 $f_{i,j}$ ,则每次状态转移需要考虑减 $a_i$ 或加 $a_i$。

显而易见状态转移方程如下:

$f_{i,j}=f_{i,j}+f_{i-1,j \pm a_i}$

由于可能有负数，则需要平移。

具体代码如下:

```cpp
#include<iostream>
using namespace std;
const int M=1000000007;
int n,m,f[1005][20005],ans;
int a[500005];
int main() {
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
		f[i][10000+a[i]]++;
		f[i][10000-a[i]]++;
        for (int j=0;j<=20000;j++){
			if(j-a[i]>=0){
				f[i][j]=(f[i][j]+f[i-1][j-a[i]])%M;
            }
            if(j+a[i]<=20000){
            	f[i][j]=(f[i][j]+f[i-1][j+a[i]])%M;
			}
        }
	}
    for(int i=1;i<=n;i++)ans=(ans+dp[i][10000])%M;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：reyik (赞：2)

简单$DP$

记$dp[i][j]$代表前$i$个数，前缀和为$j$的方案数

那么显然枚举$i$,$j$

那么如果取$a[i]$那么转移方程是$dp[i][j]+=dp[i-1][j-a[i]]$

那么如果取$-a[i]$那么转移方程数$dp[i][j]+=dp[i-1][j+a[i]]$

然后因为有负数，平移以下就可以了

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int mod=1e9+7;
int n,m,ans=0,dp[1005][20005];
int a[500005];
int read() {
        register int x=0,w=1;char ch=getchar();
        while(!isdigit(ch)) ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return x*w;
}
int main() {
        n=read();
        for (int i=1;i<=n;++i) a[i]=read();
        for (int i=1;i<=n;++i) {
                dp[i][a[i]+10000]++,dp[i][-a[i]+10000]++;
                for (int j=0;j<=20000;++j) {
                        if(j+a[i] <= 20000) dp[i][j]=(dp[i][j]+dp[i-1][j+a[i]])%mod;
                        if(j-a[i]>=0) dp[i][j]=(dp[i][j]+dp[i-1][j-a[i]])%mod;
                }
        }
        for (int i=1;i<=n;++i) {
                ans=(ans+dp[i][10000])%mod;
        }
        printf("%d\n",ans);
        return 0;
}


```

---

## 作者：No21 (赞：1)

### 解题思路

DP 应该是不难看出来的，问题是怎么设置状态。

首先第一个状态 $i$ 肯定是当前处理到第 $i$ 个数，那么还有没有别的状态呢？如果有，那么第二个状态是什么？首先只有第一个状态显然是没法 DP 的，所以我们需要第二个状态，考虑我们求的是连续子段和，所以我们第二个状态 $j$ 设为当前前缀和为 $j$。

我们已经找到了状态，现在我们考虑怎么转移，本题的转移方程是显而易见的：

$$dp_{i,j}=dp_{i-1,j \pm a_i}+dp_{i,j}$$

注意 $j \pm a_i$ 的范围，另外由于前缀和有可能是负数，用来做 DP 的数组记得开两倍。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=1021,mod=1e9+7;
    int n;
    int a[N],dp[N][N*20];
    int mian()
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
        {
            dp[i][10000+a[i]]++;
            dp[i][10000-a[i]]++;
            for(int j=0;j<=20000;j++)
            {
                if(j-a[i]>=0)
                    dp[i][j]=(dp[i-1][j-a[i]]+dp[i][j])%mod;
                if(j+a[i]<=20000)
                    dp[i][j]=(dp[i-1][j+a[i]]+dp[i][j])%mod;
            }
        }
        for(int i=1;i<=n;i++)
            dp[0][10000]=(dp[i][10000]+dp[0][10000])%mod;
        cout<<dp[0][10000];
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：Laolizi (赞：1)

这道题的思路比较容易想。

对于每一个 $a_i$ 来说有两条路选：

第一条：重开一个新的子序列 $a_i$ 是第一个。

第二条：跟着上一个子序列加或是减去 $a_i$ 。

对于第二条来说我们可以开 $n$ 个桶，从 $-10000 $ 到 $10000 $ ：

用来存储有多少种方案可以使得子序列的结果为 $t_{ij}$ 。

负数可以用 $0$ 到 $9999$ 来表示 , 正数则是 $10001$ 到 $20000$。

最后统计所有 $t_{i0}$ 的和即可。

上代码：

```c
#include<bits/stdc++.h>
using namespace std;

const int P=1e9+7,O=10000;
int n,m,ans,dp[1005][20005];
int a[1005];

int main() {
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i];
	for(int i=1; i<=n; ++i) {
		++dp[i][a[i]+O],++dp[i][-a[i]+O];
		for(int j=0; j<=20000; ++j) {
			if(j+a[i]<=20000) dp[i][j]=(dp[i][j]+dp[i-1][j+a[i]])%P;
			if(j-a[i]>=0) dp[i][j]=(dp[i][j]+dp[i-1][j-a[i]])%P;
		}
	}
	for(int i=1; i<=n; ++i) ans=(ans+dp[i][O])%P;
	cout<<ans;
}
```

（~~不要忘记模数~~）

---

## 作者：splendore (赞：0)

看到题目数据范围 $O(nk)$（$k$ 为值域）能过，

那么可以考虑 DP：

设 $f_{i,j}$ 为前 $i$ 个和为 $j$ 的方案数。

对于每个 $a_i$，可以单独作为一个序列，

$a_i$ 取正数时，有 $f_{i,a_i}+=1$

$a_i$ 取负数时，有 $f_{i,-a_i}+=1$

而 $1$ 至 $i-1$ 的所有序列都可在末端接上 $a_i$

那么就有：

$$f_{i,j}+=f_{i-1,j-a_i}$$

值得注意的是 $j$ 的取值范围可能为负数，需要将区间整体平移，代码实现上表现为 $f$ 数组的第二维统一加上 $k$（$k$ 为值域）。

还有题目要求要取模，因为实现上很简单，这里就不细说了。

---

## 作者：shao0320 (赞：0)

CF383D Antimatter

考虑 dp ，$f(i,j)$ 表示前 $i$ 个和为 $j$ 的方案数，那么每次的转移就是考虑加上 $a_i$ 还是减去 $a_i$，特殊考虑 $i$ 是第一个取的即可，最后答案就是 $\sum f(i,0)$。由于第二维可能是负数，那么需要区间整体平移。

---

