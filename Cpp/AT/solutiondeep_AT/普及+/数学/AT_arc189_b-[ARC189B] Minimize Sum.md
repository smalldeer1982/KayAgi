# 题目信息

# [ARC189B] Minimize Sum

## 题目描述

数轴上有 $N$ 个棋子，最初所有棋子都放置在不同的坐标上，第 $i$ 个棋子放置在坐标 $X_i$ 上。

你可以进行以下操作若干次（可以为 $0$ 次）：

- 选择一个 $i$ 满足 $1\le i\le N-3$，并设 $M$ 为 $X_i$ 与 $X_{i+3}$ 的中点坐标。

- 然后，分别将坐标为 $X_{i+1}$ 与 $X_{i+2}$ 的两颗棋子放在原坐标关于 $M$ 对称的坐标，最后，使坐标较小的棋子的坐标为 $X_{i+1}$，另外一个棋子的坐标为 $X_{i+2}$。

- 可以证明无论如何重复操作，所有的棋子都放置在不同的坐标处。

请找出若干次操作后，$\sum_{i=1}^N X_i$ 的最小值。

## 样例 #1

### 输入

```
4

1 5 7 10```

### 输出

```
21```

## 样例 #2

### 输入

```
6

0 1 6 10 14 16```

### 输出

```
41```

# AI分析结果

### 题目重写
【题目内容】
# [ARC189B] Minimize Sum

## 题目描述

数轴上有 $N$ 个棋子，最初所有棋子都放置在不同的坐标上，第 $i$ 个棋子放置在坐标 $X_i$ 上。

你可以进行以下操作若干次（可以为 $0$ 次）：

- 选择一个 $i$ 满足 $1\le i\le N-3$，并设 $M$ 为 $X_i$ 与 $X_{i+3}$ 的中点坐标。

- 然后，分别将坐标为 $X_{i+1}$ 与 $X_{i+2}$ 的两颗棋子放在原坐标关于 $M$ 对称的坐标，最后，使坐标较小的棋子的坐标为 $X_{i+1}$，另外一个棋子的坐标为 $X_{i+2}$。

- 可以证明无论如何重复操作，所有的棋子都放置在不同的坐标处。

请找出若干次操作后，$\sum_{i=1}^N X_i$ 的最小值。

## 样例 #1

### 输入

```
4

1 5 7 10```

### 输出

```
21```

## 样例 #2

### 输入

```
6

0 1 6 10 14 16```

### 输出

```
41```

### 综合分析与结论
本题的核心在于通过操作改变棋子的位置，使得最终所有棋子的坐标和最小。通过分析操作的性质，发现每次操作实际上是对差分数组的奇偶位进行交换。因此，可以通过将差分数组的奇偶位分别排序，从而得到最小的坐标和。

### 所选高分题解
#### 题解1：作者：ARIS2_0 (赞：9)
- **星级**：5星
- **关键亮点**：通过差分数组的奇偶位交换性质，将问题转化为对奇偶位分别排序，思路清晰，代码简洁。
- **个人心得**：作者在比赛中通过思考差分数组的性质，最终找到了问题的解决方案，体现了对问题的深入理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e16,maxn=2e5+10;
int a[maxn],p[maxn],p1[maxn],p2[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)p[i]=a[i+1]-a[i];
	for(int i=1;i<n;i++){
		if(i%2)p1[(i+1)/2]=p[i];
		else p2[i/2]=p[i];
	}
	sort(p1,p1+(int)ceil((n-1)*1.0/2)+1);
	sort(p2,p2+(n-1)/2+1);
	for(int i=1;i<n;i++){
		if(i%2)p[i]=p1[(i+1)/2];
		else p[i]=p2[i/2];
	}
	int ans=a[1];
	for(int i=2;i<=n;i++)a[i]=a[i-1]+p[i-1],ans+=a[i];
	cout<<ans;
	return 0;
}
```

#### 题解2：作者：MspAInt (赞：1)
- **星级**：4星
- **关键亮点**：通过差分数组的交换性质，将问题转化为对奇偶位分别排序，思路清晰，代码实现简洁。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=2e5+10;
int n;
LL a[N],b[N],c[N];
LL sum,ans;

signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=n;i>=1;i--)a[i]-=a[i-1];
    for(int i=2;i<=n;i++)if(i&1)b[i/2]=a[i];else c[i/2]=a[i];
    sort(b+1,b+(n-1)/2+1);sort(c+1,c+n/2+1);
    sum=ans=a[1];
    for(int i=2;i<=n;ans+=sum,i++)if(i&1)sum+=b[i/2];else sum+=c[i/2];
    printf("%lld\n",ans);
    return 0;
}
```

#### 题解3：作者：dingxiongyue (赞：1)
- **星级**：4星
- **关键亮点**：通过差分数组的交换性质，将问题转化为对奇偶位分别排序，思路清晰，代码实现简洁。

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n;
int ans;
int a[N];
int d[N], s[N];
int d1[N], d2[N];
signed main() {
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), d[i] = a[i] - a[i - 1];
	for (int i = 1; i <= n; i++) {
		if (i & 1) d1[i / 2] = d[i];
		else d2[i / 2] = d[i];
	}
	sort(d1 + 1, d1 + 1 + (n - 1) / 2);
	sort(d2 + 1, d2 + 1 + n / 2);
	for (int i = 1; i <= n; i++) {
		if (i & 1) d[i] = d1[i / 2];
		else d[i] = d2[i / 2];
	}
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + d[i];
		ans += s[i];
	}
	write(ans);
	printf("\n");
	return 0;
}
```

### 最优关键思路或技巧
1. **差分数组的奇偶位交换**：通过分析操作的性质，发现每次操作实际上是对差分数组的奇偶位进行交换，从而将问题转化为对奇偶位分别排序。
2. **贪心策略**：将差分数组的奇偶位分别排序，使得较小的差分值尽量靠前，从而最小化坐标和。

### 可拓展之处
1. **类似题目**：类似的问题可以通过分析操作对差分数组的影响，转化为对差分数组的排序或交换问题。
2. **贪心算法的应用**：在需要最小化或最大化某些值的问题中，贪心策略常常是有效的解决方案。

### 推荐题目
1. [P7962 [NOIP2021] 方差](https://www.luogu.com.cn/problem/P7962)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得总结
通过分析操作对差分数组的影响，将问题转化为对差分数组的奇偶位分别排序，从而找到最小化坐标和的解决方案。这一思路体现了对问题的深入理解和灵活运用差分数组的性质。

---
处理用时：59.87秒