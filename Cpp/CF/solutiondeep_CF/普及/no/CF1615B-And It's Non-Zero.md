# 题目信息

# And It's Non-Zero

## 题目描述

You are given an array consisting of all integers from $ [l, r] $ inclusive. For example, if $ l = 2 $ and $ r = 5 $ , the array would be $ [2, 3, 4, 5] $ . What's the minimum number of elements you can delete to make the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the array non-zero?

A bitwise AND is a binary operation that takes two equal-length binary representations and performs the AND operation on each pair of the corresponding bits.

## 说明/提示

In the first test case, the array is $ [1, 2] $ . Currently, the bitwise AND is $ 0 $ , as $ 1\ \& \ 2 = 0 $ . However, after deleting $ 1 $ (or $ 2 $ ), the array becomes $ [2] $ (or $ [1] $ ), and the bitwise AND becomes $ 2 $ (or $ 1 $ ). This can be proven to be the optimal, so the answer is $ 1 $ .

In the second test case, the array is $ [2, 3, 4, 5, 6, 7, 8] $ . Currently, the bitwise AND is $ 0 $ . However, after deleting $ 4 $ , $ 5 $ , and $ 8 $ , the array becomes $ [2, 3, 6, 7] $ , and the bitwise AND becomes $ 2 $ . This can be proven to be the optimal, so the answer is $ 3 $ . Note that there may be other ways to delete $ 3 $ elements.

## 样例 #1

### 输入

```
5
1 2
2 8
4 5
1 5
100000 200000```

### 输出

```
1
3
0
2
31072```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由区间 $[l, r]$ 内的所有整数组成的数组。例如，若 $l = 2$ 且 $r = 5$，则数组为 $[2, 3, 4, 5]$。问：最少需要删除多少个元素，才能使该数组的[按位与](https://en.wikipedia.org/wiki/Bitwise_operation#AND)结果不为零？

按位与是一种二元操作，它对两个等长的二进制表示进行逐位与运算。

#### 说明/提示

在第一个测试用例中，数组为 $[1, 2]$。当前按位与结果为 $0$，因为 $1\ \&\ 2 = 0$。然而，删除 $1$（或 $2$）后，数组变为 $[2]$（或 $[1]$），按位与结果变为 $2$（或 $1$）。这可以证明是最优解，因此答案为 $1$。

在第二个测试用例中，数组为 $[2, 3, 4, 5, 6, 7, 8]$。当前按位与结果为 $0$。然而，删除 $4$、$5$ 和 $8$ 后，数组变为 $[2, 3, 6, 7]$，按位与结果变为 $2$。这可以证明是最优解，因此答案为 $3$。注意，可能存在其他删除 $3$ 个元素的方式。

#### 样例 #1

##### 输入

```
5
1 2
2 8
4 5
1 5
100000 200000
```

##### 输出

```
1
3
0
2
31072
```

### 算法分类

位运算、前缀和

### 题解分析与结论

该题的核心思想是通过位运算和前缀和优化，找到在区间 $[l, r]$ 内，使得按位与结果不为零的最小删除次数。所有题解都围绕这一核心展开，但实现方式和优化程度有所不同。

### 所选高星题解

#### 1. 作者：caibet (5星)

**关键亮点：**
- 使用前缀和优化，将时间复杂度从 $O(n)$ 降低到 $O(\log n)$。
- 详细解释了如何通过统计每个二进制位上的 $1$ 的数量来找到最优解。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define return while(1)
const int lim=2e5+1;
int T,l,r,s[lim][19],lg[lim];

template<class T=unsigned> inline T readu(){
	T x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

void bits(int x){
	int t=x;
	while(x){
		s[t][lg[x&-x]]++;
		x^=x&-x;
	}
}
int main(){
	T=readu();
	s[1][0]=1;
	for(int i=2;i<lim;i++){
		lg[i]=lg[i>>1]+1;
		bits(i);
		for(int j=0;j<19;j++) s[i][j]+=s[i-1][j];//前缀和预处理
	}
	while(T--){
		l=readu();r=readu();
		int ans=0;
		for(int i=0;i<19;i++) ans=max(ans,s[r][i]-s[l-1][i]);//求 l~r 在某一二进制位上为 1 数的最大值
		printf("%d\n",r-l+1-ans);
	}
	return 0;
}
```

#### 2. 作者：activeO (4星)

**关键亮点：**
- 通过枚举每个二进制位，计算在该位上为 $1$ 的数的个数，利用快速幂优化计算。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res*=x;
		x*=x;
		y>>=1;
	}
	return res;
}

int calc(int x,int j){
	int tmp=qpow(2,j),ans=x/tmp*(tmp/2);
	if((x%tmp)>(tmp/2)) ans+=(x%tmp)-(tmp/2);
	return x-ans;
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int l,r;
		scanf("%d %d",&l,&r);
		int ans=r;
		for(int j=0;j<=18;j++){
			ans=min(ans,calc(r+1,j)-calc(l,j));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

#### 3. 作者：清烛 (4星)

**关键亮点：**
- 使用前缀和预处理，快速计算每个二进制位上的 $1$ 的数量。
- 代码简洁，时间复杂度低。

**核心代码：**
```cpp
const int maxn = 2e5 + 5, maxlog = 19, N = 2e5;
int sum[maxn][maxlog];

int main() {
    int T; read(T);
    FOR(i, 1, N) {
        FOR(j, 0, 18) {
            sum[i][j] = sum[i - 1][j] + ((i >> j) & 1);
        }
    }
    while (T--) {
        int l, r; read(l, r);
        int ans = r - l + 1;
        FOR(j, 0, 18) chkmin(ans, r - l + 1 - (sum[r][j] - sum[l - 1][j]));
        print(ans);
    }
    return output(), 0;
}
```

### 最优关键思路或技巧

1. **前缀和优化**：通过预处理每个二进制位上的 $1$ 的数量，将查询时间复杂度从 $O(n)$ 降低到 $O(\log n)$。
2. **位运算**：利用位运算快速计算每个数在二进制位上的 $1$ 的数量，减少计算量。
3. **枚举二进制位**：通过枚举每个二进制位，找到在该位上为 $1$ 的数最多的位，从而确定最小删除次数。

### 可拓展之处

- 类似的问题可以通过前缀和和位运算优化，如统计区间内满足某些二进制条件的数的个数。
- 可以扩展到其他位运算问题，如按位或、按位异或等。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得摘录

- **caibet**：通过前缀和优化，将时间复杂度从 $O(n)$ 降低到 $O(\log n)$，解决了TLE问题。
- **activeO**：通过快速幂优化计算，简化了代码，提高了效率。
- **清烛**：使用前缀和预处理，快速计算每个二进制位上的 $1$ 的数量，代码简洁且高效。

---
处理用时：42.10秒