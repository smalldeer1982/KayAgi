# Interesting Game

## 题目描述

【问题描述】

小 A 拿来了一堆 $n$ 个石子，邀请小 B 一起玩取石子游戏，规则是每人每次可以取不超过 $3$ 个石子，谁先取完谁获胜。

小 B 看了一眼石子的个数，在飞快的心算过后，明白了小 A 存心要坑他，于是小 B 提出了一个新的游戏规则：

每个人每步可以将一堆石子分成 $k$ 堆（$k \ge 2$），由于小 B 非常喜欢等差数列，尤其喜欢公差为 $1$ 的等差数列，故要求这 $k$ 堆石子排成一个公差为 $1$ 的等差数列。换句话说，如果分出来的每堆石子有 $a_1, a_2, \ldots, a_n$ 个（不妨 $a_1 \le a_2 \le ... \le a_n$），那么需要满足：
$a_{2} - a_{1} = a_{3} - a_{2} = \ldots = a_{n} - a_{n-1}=1$

无法操作的玩家则失败。

小 B 为了显示出自己的友善，让小 A 先取石子。小 A 觉得小 B 也别有用心，但是他自 己并无法一眼看出这个状态是否有必胜方案，于是他找了你，想知道他是否有必胜策略。

小 A 发现，得知是否有必胜策略还不够，他还需要知道先手第一步该如何操作。由于把 石头搬来搬去很累，所以小 A 想知道，若有必胜策略，先手第一步最少分成几堆可以必胜？

## 样例 #1

### 输入

```
3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
100
```

### 输出

```
8
```

# 题解

## 作者：lfxxx (赞：2)

考虑自然根号一个经典结论，公差为 $1$ 的等差数列项数至多为 $\sqrt {sum}$，因为最差情况下是 $1+2+3+...+k = \frac{k^2+k}{2}$。

于是考虑暴力找出所有转移，枚举各个堆的大小分别是 $l,l+1,l+2,...,r$，然后这个转移将局面分成了 $r-l+1$ 个子游戏，因此其 SG 函数值为 $\oplus_{i=l}^r SG_i$，这一步可以通过处理 SG 函数前缀异或快速计算，对于一个大小为 $x$ 的堆，求解其 SG 函数值就找出所有转移到其的转移边，将所有转移边的 SG 函数值取 MEX 即可。

显然可以直接 $O(n \sqrt n)$ 暴力转移。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
vector< pair<int,int> > E[maxn];//转移边
int dp[maxn],pre[maxn];
int n;
int main(){
    cin>>n;
    for(int l=0;l<=n;l++){
        int sum=0;
        for(int r=l;r+sum<=n;r++){
            sum+=r;
            if(r-l+1>=2) E[sum].push_back(make_pair(l,r));
        }
    }
    dp[0]=0;
    pre[0]=0;
    dp[1]=0;
    pre[1]=0;
    for(int i=2;i<n;i++){
        unordered_map<int,int> cnt;
        for(pair<int,int> now:E[i]){
            cnt[pre[now.second]^pre[now.first-1]]++;
        }
        while(cnt[dp[i]]!=0) dp[i]++;
        pre[i]=pre[i-1]^dp[i];
    }
    int ans=n+1;
    for(pair<int,int> now:E[n]){
        if((pre[now.second]^pre[now.first-1])==0) ans=min(ans,now.second-now.first+1);
    }
    cout<<(ans<=n?ans:-1)<<'\n';
    return 0;
}
```

---

## 作者：2018ty43 (赞：1)

## 思路
博弈论题目，首先考虑 SG 函数。  
一个状态的 SG 为所有后继状态（分一次后可达到的状态） SG 的 mex（最小未出现自然数）。  
考虑一堆大小为 $k$ 的石头的所有后继状态，设 $x$ 为分成的项数，$y$ 表示首项，则 $y=\frac{k}{x}-\frac{x-1}{2}$。因为 $y$ 为整数，当 $x$ 为奇数，则 $k\bmod x=0$，当 $x$ 为偶数，则 $k\bmod x=\frac{x}{2}$，因此可以直接筛出每个状态的后继状态，复杂度调和级数 $O(n\log n)$。  
因为后继状态是从大小 $y$ 至 $y+x-1$ 的石子堆，其 SG 为所有石子堆的 SG 异或和，可以通过维护 SG 函数的前缀和求出该后继状态的 SG。再通过数据结构可以求出 mex，即该点的 SG。  
如果大小 $n$ 的石子 SG $= 0$ 则必败。否则枚举后继状态，SG 为零的后继状态为必胜策略。

## 代码
```cpp
#include<cstdio>
#include<vector>
#include<set>
#include<assert.h>
int n;
std::vector<int>tt[100009];
int sg[100009],sgs[100009];
std::set<int>as;
int main()
{
	scanf("%d",&n);
	for(int i(2);i<=n;++i)
	{
		if(i&1)for(int j(i+i);j<=n;j+=i)tt[j].push_back(i);//筛出可以分成i项的石子堆
		else for(int j(i+(i>>1));j<=n;j+=i)tt[j].push_back(i);
		as.clear();
		for(int j:tt[i])
		{
			int y((i+i+j-(long long)j*j)/(j+j));
			if(y>0)as.insert(sgs[y-1]^sgs[y+j-1]);//枚举后继状态
		}
		int ii(0);
		while(as.count(ii))++ii;//找出mex
		sg[i]=ii;
		sgs[i]=sgs[i-1]^ii;
	}
	if(sg[n]==0)
	{
		puts("-1");
		return 0;
	}
	for(int j:tt[n])
	{
		int y((n+n+j-(long long)j*j)/(j+j));
		if(y>0&&(sgs[y-1]^sgs[y+j-1])==0)
		{
			printf("%d\n",j);
			break;
		}
	}
}
```


---

## 作者：灵茶山艾府 (赞：0)

SG 函数的应用。

题目中的约束条件等价于把 $n$ 分拆为 $k$ 个连续的正整数（$k\ge2$）。

然后就是套用 SG 函数了，例如某个 $n$ 有两种分拆方式 ${a_k}$ 和 ${b_{k'}}$，则有

$$ SG_n = mex\{SG_{a_1}\ xor\ SG_{a_2}\ xor\dots\ xor\ SG_{a_k},\  SG_{b_1}\ xor\ SG_{b_2}\ xor\dots\ xor\ SG_{b_{k'}}\} $$

若 $SG_n>0$ 则先手必胜，否则先手必败。

先手必胜时，返回满足 $SG_{a_1}\ xor\ SG_{a_2}\ xor\dots\ xor\ SG_{a_k}=0$ 的最小分拆长度。

实现时，可以先初始化 $[3,n]$ 的所有连续分拆，然后用递推来做。

此外，由于 SG 取值是连续的，可以用异或前缀和加速。

初始化部分是个调和级数之和，故时间复杂度为 $O(n\log n)$。

AC 代码（Golang）:

```go
package main

import . "fmt"

func main() {
	type pair struct{ a1, len int }
	const mx = 1e5 + 5
	ps := [mx][]pair{}
	sgSum := [mx]int{}

	var n int
	Scan(&n)

	// 初始化 [3,n] 的所有连续分拆
	for len := 2; (len+1)*len/2 <= n; len++ {
		for a1 := 1; ; a1++ {
			s := (2*a1 + len - 1) * len / 2
			if s > n {
				break
			}
			ps[s] = append(ps[s], pair{a1, len})
		}
	}

	for i := 3; i <= n; i++ {
		mex := map[int]bool{}
		for _, p := range ps[i] {
			s := sgSum[p.a1] ^ sgSum[p.a1+p.len]
			if i == n && s == 0 {
				Print(p.len)
				return
			}
			mex[s] = true
		}
		sg := 0
		for ; mex[sg]; sg++ {
		}
		sgSum[i+1] = sgSum[i] ^ sg // SG 前缀和
	}
	Print(-1)
}
```


---

