# [GCJ 2021 #1A] Prime Time

## 题目描述

你正在玩一款名为**质数时刻**的新单人纸牌游戏。你有一副卡牌，每张牌上写有一个质数，不同牌可能写有相同的数字。

游戏目标是将所有卡牌分成两组：第一组卡牌上的数字之和等于第二组卡牌上的数字之积。每张牌必须属于其中一组，且每组至少包含一张牌。若某组仅有一张牌，则该组的和或积即为该牌上的数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/n1zowb5r.png)

例如上图中，左侧卡牌数字之和为 $25$，右侧卡牌数字之积也为 $25$，因此这是一个有效的分组方案。

你的得分等于第一组数字之和（即第二组数字之积），若无法完成这样的分组则得分为 $0$。你能获得的最高得分是多少？


## 说明/提示

**样例解释**

在样例 #1 中，最优分组为 $11 + 2 + 7 + 3 + 2 = 5 \cdot 5$。另一可行分组 $5 + 7 + 3 + 2 + 5 = 11 \cdot 2$ 得分较低。

在样例 #2 中，注意相同数字的卡牌可以分到不同组。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$
- $1 \leq \mathbf{M} \leq 95$（在 2 至 499 之间的质数共 95 个）
- $2 \leq \mathbf{P}_i \leq 499$（均为质数）
- $\mathbf{P}_i < \mathbf{P}_{i+1}$（质数按严格递增顺序给出）
- $1 \leq \mathbf{N}_i$

**测试集 1（7 分，可见判定）**
- 总卡牌数 $2 \leq \sum \mathbf{N}_i \leq 10$

**测试集 2（13 分，可见判定）**
- 总卡牌数 $2 \leq \sum \mathbf{N}_i \leq 100$

**测试集 3（15 分，隐藏判定）**
- 总卡牌数 $2 \leq \sum \mathbf{N}_i \leq 10^{15}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
5
2 2
3 1
5 2
7 1
11 1
1
17 2
2
2 2
3 1
1
2 7```

### 输出

```
Case #1: 25
Case #2: 17
Case #3: 0
Case #4: 8```

# 题解

## 作者：Milthm (赞：1)

题目相当于求一个集合的子集使得子集内元素之积等于不在子集内元素之和（这里的集合都指可重集），如果直接 dfs 的话很容易 TLE，所以应该还有一点性质要我们发现。

设 $S=\sum P_iN_i$，所选子集的和为 $S_2$，积为 $Q$，则要满足：$Q=S-S_2$。我们发现此时 $Q<S$，又因为质数至少为 $2$，所以满足条件的子集的大小最多是 $O(\log S)$ 的，从而得出 $S_2$ 最多为 $O(P\log S)$，其中 $P=\max p_i$。

所以我们枚举 $S_2$，同时可以得到 $Q$（或限定范围枚举 $Q$ 也可，代码采用这种写法），然后判断 $Q$ 是否可以被拆成原本集合中存在的数的乘积，这样我们就做完了。时间复杂度 $O(TMP\log S)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 105
using namespace std;
int T,n,p[N],num[N],sum,ans,cnt;
signed main(){
	cin>>T;
	for(int c=1;c<=T;++c){
		cin>>n;sum=0;ans=0;cnt=0;
		for(int i=1;i<=n;++i)cin>>p[i]>>num[i],sum+=p[i]*num[i];
		for(int i=sum;i>=max(2.0,sum-3e4);--i){
			int x=i,f=0,s=0;
			for(int j=1;j<=n;++j){
				int cnt=0;
				while(x%p[j]==0)++cnt,x/=p[j],s+=p[j];
				if(cnt>num[j]){
					f=1;break;
				}
			}
			if(f||x>1)continue;
			if(sum-s==i){
				ans=i;break;
			}
		}
		cout<<"Case #"<<c<<": "<<ans<<'\n';
	}
	return 0;
}

```

---

