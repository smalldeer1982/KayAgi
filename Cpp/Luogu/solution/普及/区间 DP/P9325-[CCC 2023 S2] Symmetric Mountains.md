# [CCC 2023 S2] Symmetric Mountains

## 题目描述

Rebecca 是一名导游，正在为她的杂志推广落基山脉。她最近拍了一张包含 $N$ 座山的美丽照片，其中从左到右第 $i$ 座山的高度为 $h_i$。她将为她的杂志裁剪这张照片，可能会从照片的左侧移除一些山，也可能会从照片的右侧移除一些山。也就是说，裁剪包括从第 $l$ 座山到第 $r$ 座山的连续山峰，其中 $l \leq r$。为了取悦她的杂志读者，Rebecca 将尝试找到最对称的裁剪。

我们将裁剪的不对称值定义为从裁剪的中点开始，每对等距山峰的高度差的绝对值之和。为了帮助理解这个定义，注意到一个数 $v$ 的绝对值，记为 $|v|$，是 $v$ 的非负值：例如 $|-6| = 6$ 和 $|14| = 14$。裁剪的不对称值是所有 $|h_{l+i} - h_{r-i}|$ 的和，其中 $0 \leq i \leq \frac{r-l}{2}$。换句话说，我们从外向内配对山峰，计算每对山峰高度差的绝对值，并将它们相加。

因为 Rebecca 不知道照片需要多宽，所以对于所有可能的裁剪长度，找到不对称值最小的裁剪（即最对称的裁剪）。

## 说明/提示

对样例输入 1 的输出解释：

我们将展示为什么从左数第五个值是 2。让我们尝试计算所有长度为 5 的裁剪的不对称值。

第一个裁剪中山的高度是 $[3, 1, 4, 1, 5]$。这个裁剪的不对称值是 $|3 - 5| + |1 - 1| + |4 - 4| = 2$。

第二个裁剪中山的高度是 $[1, 4, 1, 5, 9]$。这个裁剪的不对称值是 $|1 - 9| + |4 - 5| + |1 - 1| = 9$。

最后一个裁剪中山的高度是 $[4, 1, 5, 9, 2]$。这个裁剪的不对称值是 $|4 - 2| + |1 - 9| + |5 - 5| = 10$。

因此，长度为 5 的最对称裁剪是不对称值为 2 的裁剪。

对样例输入 2 的输出解释：

这个样例满足第二个子任务。注意，唯一长度为 4 的裁剪是 $[1, 3, 5, 6]$，其不对称值为 $|1 - 6| + |3 - 5| = 7$。

**本题采用捆绑测试**：

- 子任务 1（5 分）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- 子任务 2（5 分）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- 子任务 3（5 分）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
0 2 0 5 2 10 10```

## 样例 #2

### 输入

```
4
1 3 5 6```

### 输出

```
0 1 3 7```

# 题解

## 作者：Loser_Syx (赞：28)

## 思路

看到题目，首先第一眼想到暴力。

最朴素的暴力方法肯定是先枚举长度 $i$，再枚举左右端点，最后计算差值，这样的复杂度是 $O(n^3)$ 的，肯定超时。

暴力代码：

```cpp
#include <iostream>

using namespace std;
typedef long long ll;
#define int long long

int a[10101];

signed main(){
	int n;
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%lld", &a[i]);
	}
	for(int len = 1; len <= n; ++len){
		int l = 1, r = len;
		int cz = 1e15;
		while(r <= n){
			int L = l, R = r, nowcz = 0;
			while(L <= R){
				nowcz += abs(a[L] - a[R]);
				L++;
				R--;
			}
			++l;++r;
			cz = min(cz, nowcz);
		}
		printf("%lld ", cz);
	}
	return 0;
}
```

接下来就是本篇的重点：优化（当然我也不会和你说什么 dp 和双指针之类的）。

我们不妨举个例子：

初始时假设 $h = \{1,2,3,4,5,6,7\}$，我们先将长度为 $1$ 的算出来，很显然，都是 $0$，接下来不用着急算 $i = 2$ 的情况，算 $i = 3,5,7$ 的，我们会发现，在算其中的除了 $l$ 和 $r$ 端点外，其它的例如下标为 $4 \sim 4$ 的啊，$3 \sim 5$ 的都被之前给计算过了，于是我们大可开一个数组记录之前算过的差值，这样可以使得每次计算是 $O(1)$ 的复杂度。

由于奇偶性不同，$i$ 是偶数的情况也得分开记录差值。

复杂度是 $O(n^2)$ 的，超时不了，还是目前的最优解。

```cpp
#include <iostream>

using namespace std;
typedef long long ll;

ll h[10101];
ll a[10101], b[10101];

int main(){
	int n;
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++i) scanf("%lld", &h[i]);
	printf("0 ");
	for(int i = 2; i <= n; ++i){
		if(i % 2 == 1){
			int l = n-i+1, r = n;
			ll cz = 1e15;
			while(r >= i){
				a[r] = a[r-1] + abs(h[r] - h[l]);
				cz = min(cz, a[r]);
				--l;--r;
			}
			printf("%lld ", cz);
		}else{
			int l = n-i+1, r = n;
			ll cz = 1e15;
			while(r >= i){
				b[r] = b[r-1] + abs(h[r] - h[l]);
				cz = min(cz, b[r]);
				--l;--r;
			}
			printf("%lld ", cz);
		}
	}
	return 0;
}
```

---

## 作者：玄学OIER荷蒻 (赞：14)

一眼区间 DP。

与以往区间 DP 不同的是，这次要提前预处理长度 $0$ 和 $1$ 的所有区间（其实没必要预处理，反正也都是 $0$，为初始值）。

至于剩下的，设 $dp_{i,j}(1 \le i \le j \le n)=\sum^{\lfloor \frac{i+j}{2} \rfloor}_{k=i}{|h_{i+j-k}-h_k|}$。

则有 $\forall 2 \le i+1 \le j-1 \le n-1, dp_{i,j}=dp_{i+1,j-1}+|h_i-h_j|$（$\forall$ 里的意思是在正常要求下再加一个长度 $len \ge 2$）。

很明显复杂度 $O(n^2)$，另外希望管理大大加上区间 DP 的 tag。

### 代码

```
#include <bits/stdc++.h>
#define magic ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); //虽然输入输出量小，但还是加一点好
using namespace std;
int dp[5010][5010],h[5010],minn[5010],n;
int main()
{
    magic
    cin>>n;
    for (register int i=1;i<=n;i++) cin>>h[i];//开点register总是好的
    for (register int j=2;j<=n;j++){
        minn[j]=250000000;//答案最大可能值，不会爆int
        for (register int i=1;i<=n-j+1;i++){
            dp[i][i+j-1]=dp[i+1][i+j-2]+abs(h[i]-h[i+j-1]);//如果j=2,长度为2，此时可能会出现类似 dp[2][1] 的情况，不用担心，那只是长度为0的区间而已
            minn[j]=min(minn[j],dp[i][i+j-1]);
        }
    }
    for (register int i=1;i<=n;i++) cout<<minn[i]<<' ';
    return 0;
}
```

去除注释和优化以后代码长度 426B，(目前）全谷最短解。

---

## 作者：ZepX_D (赞：11)

两篇题解都想麻烦了，因为我们要求不对称性，那么枚举中间的对称点然后向左右两边扩展即可，时间复杂度 $ O(n^2) $，但因为是向左右扩展，根本跑不满，所以跑的飞快。

具体就是枚举对称点 $ i $，左右端点 $l,r$ 依次扩展，求出当前不对称性 $ s $，设 $ ans_i $ 为长度为 $i$ 的截图的最小不对称性，那么 $ ans_{r-l+1} = \min(ans_{r-l+1},s) $。一次求长度为奇数的，一次求长度为偶数的，然后就完了。具体实现非常简单，请看代码。

### 代码
```cpp
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int h[5010],ans[5010],l,r,s;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int n;cin >> n;
	memset(ans,0x3f,sizeof(ans));
	for (int i = 1;i <= n;i++) cin >> h[i];
	for (int i = 1;i <= n;i++)
	{
		s = 0,l = r = i;
		while(l && r <= n)
		{
			ans[r-l+1] = min(ans[r-l+1],s);
			l--,r++,s += abs(h[r]-h[l]);
		}

		s = abs(h[i+1]-h[i]),l = i,r = i+1;
		while(l && r <= n)
		{
			ans[r-l+1] = min(ans[r-l+1],s);
			l--,r++,s += abs(h[r]-h[l]);	
		}
	}
	for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
	return 0;
}
```


---

## 作者：Jorisy (赞：4)

易想到 $O(n^3)$ 的暴力，考虑优化。

如果令计算答案的函数为 $d(l,r)$，那么 $d(l,r)=\begin{cases}0&(l>r)\\|a_l-a_r|+d(l+1,r-1)&(l\le r)\end{cases}$。

从而想到记忆化计算过的答案。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[5005],c[5005][5005],f[5005][5005];

int d(int l,int r)
{
	if(f[l][r]!=-1) return f[l][r];//记忆化
	if(l>r) return 0;
	return f[l][r]=c[l][r]+d(l+1,r-1);//记忆化
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			c[i][j]=abs(a[i]-a[j]);
		}
	}
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		int ans=INT_MAX;
		for(int j=1;j+i-1<=n;j++)
		{
			ans=min(ans,d(j,j+i-1));
			//cerr<<"D "<<i<<' '<<s<<endl;
		}
		printf("%d ",ans);
	}
 	return 0;
}
```

---

## 作者：charlieqi (赞：2)

# 分析
这是一道区间 DP 的好题。对于区间 DP，我们是有一个模板：
```cpp
for(int len=1;len<=n;len++){//枚举小区间。
    for(int j=1;j+len-1<=n;j++){//枚举起点。
        int ends=j+len-1;
        for(int i=j;i<ends;i++){//枚举分割点，更新最优解。
            dp[j][ends]=min(dp[j][ends],dp[j][i]+dp[i+1][ends]+???);
        }
    }
}
```
我们可以先推出**状态转移方程**，然后在板子上改即可。方程就是：$dp_{i,j}=dp_{i+1,j-1}+|a_i-a_j|$。


想一想：中间的区间值有了，在头和尾各加一个数，加上区间值 $|a_i-a_j|$ 是不是就出来了呢？
# code
```cpp
#include<bits/stdc++.h>
const int N=5100;
using namespace std;
int n,a[N],dp[N][N],minn;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//读入优化。
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=0;i<n;i++){
		minn=1e9;//多测要清空。
		for(int j=1;i+j<=n;j++){
			int l=i+j;//区间长度。
			dp[j][l]=dp[j+1][l-1]+abs(a[j]-a[l]);
			minn=min(minn,dp[j][l]);
		}
		cout<<minn<<' ';
	}
	return 0;
}
```

---

## 作者：songzhixin (赞：2)

### 题目大意

设起始点为 $l$，重点为 $r$，则定义这个序列的的不对称性为 

$$ \sum_{i=0}^{(l+r) \div 2} | a_{r-i} - a_{l+i} | $$

求长度为 $ 1 \sim N $ 的每个长度的序列中的最小不对称。

### 解题思路

首先想到暴力枚举每个长度和每个区间，时间复杂度 $ O(n^3) $，过不了。

但是回忆一下暴力代码怎么写的，我们在枚举中间点向两边扩张，但是扩张时至大区间的过程中是不是也计算了小区间？所以我们可以记录下来这些小区间的值，就不需要枚举区间长度了，直接枚举中间节点向两边延伸即可，可以优化掉一个 $n$，时间复杂度 $ O(n^2) $，$n$ 为 $5000$，可以过。

### 代码实现

我们可以分为长度为奇数和长度为偶数两种情况，从头开始枚举这个区间最中间的点，向两边延伸至最大，即两边有一边到了顶点，再延伸过程中时刻记录此长度的的值，与以前的相比较并取 $\max$，最后输出结果即可。

### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int a[N];
int b[N];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=0x3f3f3f3f;//先初始化为无穷大 
	}
	b[1]=0;//长度为1永远是0 
	for(int i=1;i<=n;i++){//从i节点出发的情况 
		int k=min(abs(i-1),abs(n-i));//确定左右延伸的最大长度 
		int ans=0;
		for(int j=1;j<=k;j++){
			ans+=abs(a[i+j]-a[i-j]);//记录对应的不对称性是多少 
			b[j*2+1]=min(ans,b[j*2+1]);//顺便把沿途的更新了 
		}
	}
	for(int i=1;i<n;i++){//从i和i+1中间出发的情况
		int k=min(i,n-i);//确定左右延伸的最大长度
		int ans=0;
		for(int j=1;j<=k;j++){
			ans+=abs(a[i+1-j]-a[i+j]);//记录对应的不对称性是多少
			b[j*2]=min(ans,b[j*2]);//顺便把沿途的更新了 
		}
	}
	for(int i=1;i<=n;i++){//输出答案 
		printf("%lld ",b[i]);
	}
	return 0;
}
```

---

## 作者：TheShuMo (赞：2)

## P9325 [CCC 2023 S2] Symmetric Mountains

## 题目大意

给定一个长度为 $N$ 的数列 $S$，定义一个区间的不对称性为，在区间中位于**对称位置**的若干个点差的绝对值的总和。对于 $1 \leq i \leq N$，求出长度为 $i$ 的所有区间**最小**的不对称性。

## 分析

一眼可以看出 $O(n^3)$ 的模拟做法，即对于 $1\leq i \leq N$ 枚举左右端点求出其最小不对称性。当然对于 $N \leq 5000$ 明显会超时。

考虑怎么优化求出最小不对称性的时间。

模拟一下可以发现，在同一个端点上，区间长度为 $i$ 和 $i+2$ 时，只需要把 $i$
 时求出的不对称性加上两端的数字的绝对值之差，就是长度为 $i+2$ 的同中点的区间的不对称性。
 
考虑区间DP来解决，定义 $F_{i,j}$ 表示长度为 $i$ 的区间，其中点为 $j$ 的时候，这个区间的不对称性的值。其中当 $i$ 为偶数时，该区间的中点 $j$ 取中间两个数中左边的那个数

那么转移就好表示了，令 $k = i/2$ 当 $i$ 为奇数时，
$$ F_{i,j} = F_{i-2,j} + \mid S[j-k] - S[j+k]\mid $$

当 $i$ 为偶数时， 
$$F_{i,j} =  F_{i-2,j}+ \mid S[j-k+1] - S[j+k]\mid$$ 


得到了转移方程，剩下的就是实现了。注意要把上下越界的情况搞清楚。

## 代码
```cpp#include<bits/stdc++.h>
#define int long long

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
int S[100010];
int f[5010][5010];
int res[5010];
signed main(){
    int n = read();
    memset(res,1145141919810,sizeof(res));
    for(int i = 1; i <= n; i++){
        S[i] = read();
    }
    for(int i = 2; i <= n; i++){//从2开始循环，避免越界。
        for(int j = 1; j <= n; j++){
            int k = i/2;
            if(i&1 && (j-k < 1 || j + k > n))continue;
            else if(!(i&1) && (j-k+1 < 1|| j + k > n))continue;
            else {
                if(i&1)f[i][j] = f[i-2][j] + abs(S[j-k]-S[j+k]);
                else f[i][j] = f[i-2][j] + abs(S[j+k] - S[j-k+1]);
                res[i] = min(res[i], f[i][j]);
            }
        }
    }
    printf("0 ");// 当 i = 0 时，很明显不对称性都是0，所以直接输出即可
    for(int i = 2; i <= n; i++){
        write(res[i]);printf(" ");
    }
}
```

---

## 作者：Zhl2010 (赞：1)

## 题目概括
有 $n$ 座山，算出长度为 $1$ 到 $n$ 时的最小不对称性。
## 思路
看到题目说：对于长度为 $i$ 的截图，我们一定会想到区间动态规划。

设 $f_{i,j}$ 表示以 $j$ 作为起点，长度为 $i$ 的情况的最小不对称性。

枚举长度与起点，可以得到递推式：
$$f_{l,r}=f_{i+1,r-1}+|j_r-j_l|$$

$f_{i+1,r-1}$ 表示左右长度都缩短一位的情况，$|j_r-j_l|$ 表示新增加的不对称性。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,j[5010],f[5010][5010];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&j[i]);
	}
	for(int i=0;i<n;i++){
		int ans=INT_MAX;
		for(int l=1;l<=n;l++){
			int r=i+l;
			if(r>n)break;
			f[l][r]=f[l+1][r-1]+abs(j[r]-j[l]);
			/*f_{l,r}=f_{i+1,r-1}+|j_r-j_l|*/
			ans=min(ans,f[l][r]);//长度固定，起点不固定 
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：yzysdTNT (赞：1)

### 思路
因为题目说要求多个区间的不对称值，这让我们很容易联想到区间 DP。
定义 $f_{i,j}$ 表示区间 $[i,j]$ 的不对称值，  
依题意可以得到区间 $[i,j]$ 应该由区间 $[i + 1,j - 1]$ 得到，最后 $ans_i$ 就是在所有长度为 $i$ 的区间中取最小值。
### CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int a[N],ans[N],n,f[N][N];

int main(){
	cin >> n;
	memset(ans,0x3f,sizeof ans);
	memset(f,0x3f,sizeof f);
	ans[0] = ans[1] = 0;
	cin >> a[1];
	for(int i = 2;i <= n;i++){
		cin >> a[i];
		f[i][i] = 0;
		f[i - 1][i] = abs(a[i - 1] - a[i]);
		ans[2] = min(ans[2],f[i - 1][i]);
	}
	for(int l = 3;l <= n;l++){
		for(int i = 1,j = l;j <= n;i++,j++){
			f[i][j] = f[i + 1][j - 1] + abs(a[i] - a[j]);
			ans[l] = min(f[i][j],ans[l]);
		}
	}
	for(int i = 1;i <= n;i++){
		cout << ans[i] << ' ';
	}
	return 0;
} 
```

---

## 作者：GeXiaoWei (赞：0)

# P9325 [CCC 2023 S2] Symmetric Mountains
## 解析
先想暴力，枚举左右断点求解最小不对称性，时间复杂度 $O(n^{3})$，必定超时。

再想动态规划，设 $dp_{i,j}$ 表示区间 $[i,j]$ 的不对称性，而这段区间则与区间 $[i+1,j-1]$ 有关系，则可得 $dp_{i,j}=dp_{i+1,j-1}+|a_{i}-a_{j}|$。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[5005][5005],a[5005],n,minn[5005];
int main(){
	scanf("%lld",&n);memset(minn,0x3f3f3f3f,sizeof(minn));
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int len=1;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			dp[l][r]=dp[l+1][r-1]+abs(a[l]-a[r]);
			minn[len]=min(minn[len],dp[l][r]);
		}
	}
	for(int i=1;i<=n;i++) printf("%lld ",minn[i]);
	return 0;
} 
```

---

## 作者：HHC883 (赞：0)

# 题目分析
容易发现，区间 $[i,j]$ 的不对称性与区间 $[i+1,j-1]$ 的不对称性有关。具体地，设区间 $[i,j]$ 的不对称性为 $dp_{i,j}$，则有 $dp_{i,j}=dp_{i+1,j-1}+|h_i-h_j|$。用区间 DP 实现即可。

时间复杂度为 $O(n^2)$。
# 参考代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,h[5005],dp[5005][5005];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=n;i++) dp[i][i]=0,dp[i][i+1]=abs(h[i]-h[i+1]);
	for(int len=1;len<=n;len++){
		int ans=0x7fffffff;
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(len>=3) dp[i][j]=dp[i+1][j-1]+abs(h[i]-h[j]);
			ans=min(ans,dp[i][j]);
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：leiaxiwo (赞：0)

# 题解：P9325 [CCC 2023 S2] Symmetric Mountains
[传送门](https://www.luogu.com.cn/problem/P9325)
### 题目分析
给定一个长度为 $n$ 的数列 $S$，假设我们截取 $S_l \sim S_r$ 到序列 $Q$，$Q$ 的「不对称性」就定义为：位于 $Q$ 上**对称**位置的值**绝对差**总和，由基本初中数学，我们有

$$ \sum_{i = 1}^{\lceil |Q| \div 2 \rceil} |Q_i - Q_{|Q| - i + 1}| $$

这就是位于 $Q$ 上**对称**位置的值**绝对差**总和求和公式了。

求：$\forall i \in [1, n]$，长度为 $i$ 的的**最小**「不对称性」。

首先要有判断是否**已经计算过**的部分。这边重新开个 `bool` 二维数组 $vis$，如果 $vis_{i, j}$ 为**真**，直接返回答案 $ans(i, j)$；否则再递归计算并赋值 $vis_{i, j}$ 为**真**。

很明显，对于 $A_l \to A_r$，其「不对称性」$= |high_l - high_r| + ans(i + 1, j - 1)$，所以就可以 dp 地采用上一次的结果。

这种题目在推完之后代码实现是很显然的，那么本题就结束战斗了。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int high[5005],ans[5005][5005];
bool vis[5005][5005];//二维数组按说不能开这么大，大家酌情开小一点
int query(int x,int y){
	vis[x][y]=1;
	if(y<=x){
		return 0;
	}
	return ans[x][y]=abs(high[x]-high[y])+(vis[x+1][y-1]?ans[x+1][y-1]:query(x+1,y-1));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&high[i]);
	}
	printf("0 ");
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!vis[i][j]){
				ans[i][j]=query(i,j);
			}
		}
	}
	for(int i=2;i<=n;i++){
		int answer=0x7fc00000;//这里要开大一点，不然调试很久也找不出问题
		for(int j=1;j<=n-i+1;j++){
			answer=min(answer,ans[j][i+j-1]);
		}
		printf("%d ",answer);
	}
	return 0;
}
```

---

## 作者：盐焗蛋 (赞：0)

## 思路

如果使用朴素暴力，枚举区间长度 $i$，再枚举长度为 $i$ 的每个区间，最后进行不对称值的计算，复杂度将会高达 $O(n^3)$，过不了。

因为 $n \le 5000$，我们希望优化掉一个 $n$。唯一能优化的只有不对称值的计算了，考虑先画一张表格辅助思考。

样例：

`1 2 3 4 5 6`

建立数组 $f_{i,j}$ 保存 $(i,j)$ 位置上两数的差的绝对值：

![](https://cdn.luogu.com.cn/upload/image_hosting/9a75gvhq.png)

如果要求某个区间的不对称值（目前仍然是 $O(n)$ 的），要提取的几个差值总会成一条斜线。这启发我们使用前缀和进行优化，重新设定 $f_{i,j}$ 为 $(i,j)$ 位置上斜线的前缀和值：

![](https://cdn.luogu.com.cn/upload/image_hosting/yuap3msv.png)

假设要求区间 $[2,5]$ 的不对称值，不对称值可以表示为 $(f_{5,2}-f_{1,6})/2$，因为值被重复计算了两次。易推出区间 $[t,w]$ 的不对称值为 $(f_{w,t}-f_{t-1,w+1})/2$。

至此，计算不对称值的复杂度降至 $O(1)$，总复杂度降至 $O(n^2)$。问题得到了解决。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,a[5005],f[5005][5005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){//计算 f[i][j]
			int t=i,w=j,cz=abs(a[t]-a[w]);
			f[t][w]=f[t-1][w+1]+cz;
			f[w][t]=f[w-1][t+1]+cz;
		}
	for(int i=1;i<=n;i++){//长度为 i
		ans=2147483647;
		for(int t=1;t<=n-i+1;t++){//[t,w]
			int w=t+i-1;
			ans=min(ans,(f[w][t]-f[t-1][w+1])/2);
		}
		cout<<ans<<" ";
	}
}
```

---

## 作者：_JF_ (赞：0)

[P9325 [CCC 2023 S2] Symmetric Mountains](https://www.luogu.com.cn/problem/P9325)


第一眼想到就是去枚举所有的区间，是 $O(n^2)$ 的，但是如果要求出这个区间的值要 $O(n)$，显然不行。

考虑预处理所有区间的值。因为 $n$ 较小，并且我们不可能去硬算每个区间的值，当前区间的值一定是可以被转换过来的。

我们发现这其实可以从中间往两边扩展，这样当前这个区间的值就是可以继承的了。

只用从第 $i$ 个和 $i,i+1$ 去扩展即可，这样弄出来的区间是长度为奇数和偶数的，且能覆盖到所有的区间。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5001;
#define int long long 
int a[N],s[N][N],n;
void Slove(int node){
	s[node][node]=0;
	int l=node-1,r=node+1,now=0;
	while(l>=1&&r<=n)
		now+=abs(a[l]-a[r]),s[l][r]=now,l--,r++;
}
void Slove1(int l,int r){
	s[l][r]=abs(a[r]-a[l]);
	int l1=l-1,r1=r+1,now=s[l][r];
	while(l1>=1&&r1<=n)	now+=abs(a[l1]-a[r1]),s[l1][r1]=now,l1--,r1++;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)	Slove(i);
	for(int i=1;i<n;i++)	Slove1(i,i+1);
	for(int len=1;len<=n;len++){
		int ans=INT_MAX;
		for(int i=1;i+len-1<=n;i++)	ans=min(ans,s[i][i+len-1]);
		printf("%lld ",ans);
	}
	return 0;
} 
```


---

## 作者：Lemonlwl (赞：0)

## P9325 [CCC 2023 S2] Symmetric Mountains 题解
### 题意：
对于 $N$ 个长度为 $i(1 \le i \le N)$ 的图片中，求每两个关于图片中心对称的山峰的高度的差的绝对值之和的最小值。

------------

### 分析：
首先很容易想到暴力枚举，显然会超时，所以我们需要将时间复杂度降为 $O(n^2)$，因此我们可以用区间 DP 来解决。

------------

### 思路：
根据题意我们可以得知：需要输出的是每一个长度的绝对值之和的最小值，所以我们不妨设 $dp_{i,j}$ 为当照片长度为 $i$ 且照片中心为 $j$ 时该照片的绝对值之和。

接下来需要找关于 $dp_{i,j}$ 动态转移方程，通过观察我们不难发现：当前照片的绝对值之和等于比它长度小 $2$ 且中心不变的照片的绝对值之和加上两头高度的绝对值之和。

因此我们可以得出动态转移方程：

$$dp_{i,j}= \begin{cases} dp_{i-2,j}+\left | h_{j-i/2} - h_{j+i/2} \right | & i \bmod 2 = 1 \\ dp_{i-2,j}+\left | h_{j-i/2+1} - h_{j+i/2} \right | & i \bmod 2 = 0 \end{cases}$$

注：当长度为偶数时，我们认为中心点左边的位置为中心。

------------

附上 [AC](https://www.luogu.com.cn/record/112676916) 代码：
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,ans[10005];
int h[10005];
int dp[10005][10005];
int main(){
	cin>>n;
	memset(ans,0x3f,sizeof(ans));  //找最小值需要初始化。
	for(int i=1;i<=n;i++){   //输入。
		cin>>h[i];
	}
	for(int i=2;i<=n;i++){  //长度，这里从2开始是为了防止越界。
		for(int j=1;j<=n;j++){   //中心点。
			int v=i/2;
			if(i%2==1){  //第一种情况。
				if(j-v>=1 && j+v<=n){  //在两头位置不越界的情况下，下同。
					dp[i][j]=dp[i-2][j]+abs(h[j-v]-h[j+v]);
					ans[i]=min(ans[i],dp[i][j]);  //每一个长度的图片取最小值作为答案，下同。
				}
			}
			else{   //第二种情况。
				if(j-v>=0 && j+v<=n){  //这里左端大于等于0，把中心左边的位置视为中心点。
					dp[i][j]=dp[i-2][j]+abs(h[j-v+1]-h[j+v]);
					ans[i]=min(ans[i],dp[i][j]);
				}
			}
		}
	}
	ans[1]=0;  //长度为一的图片绝对值差的和永远为0。
	for(int i=1;i<=n;i++){  //输出。
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：caohan (赞：0)

# 思路

~~很简单，只需要顺着标签就行了。~~

虽然也对，可是最朴素的暴力是不可能的。肯定需要一点优化。

这道题需要一些递归的方法。

很明显，在递归时，我们希望以函数截图的两个端点为数据递归，这样方便去计算不对称性。

设这个函数是 $g(x,y)$ 且 $x$ 为左端点。这个函数的值为：

$g(x,y)=\left\vert a_x-a_y\right\vert + \left\vert a_{x+1}-a_{y-1}\right\vert \cdots $

看到从第二项开始，式子和 $g(x+1,y-1)$ 完全相同，可以将其变为 $g(x,y)=g(x+1,y-1)+\left\vert a_x-a_y\right\vert $。这就有了递归。

并且这个结果是唯一的，这就能用 $vis$ 进一步压缩时间。

别忘了卡常。

# 代码




```cpp
#include<bits/stdc++.h>
#define mod 100003
using namespace std;
int a[5005];
char vis[5005][5005];
int res[5005][5005];
int n;
int rev(int l,int r)
{
	if(l>=r)
	{
		res[l][r]=0;//越界了 
	}
	else if(vis[l+1][r-1]==1)
	{
		res[l][r]=abs(a[l]-a[r])+res[l+1][r-1];//算过就用 
	}
	else 
	{
		res[l][r]=rev(l+1,r-1)+abs(a[l]-a[r]);//没算过就算 
	}
	vis[l][r]=1;//打好标记 
	return res[l][r];//返回 
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cout<<"0 ";//因为在大小为1时，不对称性绝对为0 
	for(int i=2;i<=n;i++)
	{
		int minn=2100000000;
		for(int j=1;j<=n-i+1;j++)
		{
			minn=min(minn,rev(j,i+j-1));//枚举找最小 
		}
		cout<<minn<<" "; 
	}
	return 0;
}
```


---

## 作者：0x282e202e2029 (赞：0)

## 红名特别篇 · P9325 [CCC 2023 S2] Symmetric Mountains ~~对称的山~~ 题解
首先，[题目传送门](https://www.luogu.com.cn/problem/P9325)安排~
### 分析
见到这种题目，蒟蒻第一眼的感觉是：看起来很简单的样子。

既然说简单，那么肯定是有一种方法来解决的，那就是——**递归计算**。这个方法很常用，并不奇怪。并且这种方法也是蒟蒻能想出的最优的。千万不要看到此题带了个模拟和枚举标签就真的去枚举，$O(N^3)$ **的复杂度……只能说谁~~第一篇题解的 StandardManager~~ 写谁知道。**

既然说到递归，那本题递推式是什么？

我们记左端为 $l$，右端为 $r$ 的截图的不对称性为 $asymmetricValue(l,r)$。根据题意，我们发现，这个函数值可以分解为**最两端的位置的山的高度差的绝对值**与**处于中间位置的函数值**之和。

自然地，我们写出递推式为 

$$asymmetricValue(l,r) = |h_l - h_r| + asymmetricValue(l + 1,r - 1)$$

那么递归计算的代码很轻松就能写出。

需要注意的是，对于这道题而言，**我们需要定义一个 vis 数组记录我们是否计算过 $asymmetricValue(l,r)$，避免重复计算 $0$ 值而 TLE。**蒟蒻就是因为这里想偷懒，结果好几次都是 $10 pts$。

![TLE](https://cdn.luogu.com.cn/upload/image_hosting/7o43desd.png)

(~~只 TLE 了一个点啊！万恶的 Subtask 捆绑测试~~）

另外，函数要判断越界！~~不怕死的可以尝试一下后果，不过应该是全 TLE。~~
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005, INF = 0x3f3f3f3f;//数组大小以及INF,老传统了 
int n, h[MAXN], rec[MAXN][MAXN], m;//rec是记录数组 
bool vis[MAXN][MAXN];//必须加这个！否则有些数要再算一遍！蒟蒻吃了亏，观众老爷们可不能！
inline int read()
{
	register char ch = getchar();
	register int x = 0;//给没见过快读的解释一下，register寄存器，用来提升效率
	char t = 0;
	while(!isdigit(ch))
	{
		t |= ch == '-', ch = getchar_unlocked();//这里的getchar_unlocked()不是线程安全的，因此比普通getchar()更快，注意有些编译器，比如DevC++是没有的
	}
	while(isdigit(ch))
	{
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar_unlocked();//模拟位移操作，提升效率
	}
	return t ? -x : x;
}//快读
int asymmetricValue(int l, int r)
{
	vis[l][r] = true;
	if(l >= r)
	{
		return 0;
	}//越界判断！如果越界了返回0 
	if(vis[l + 1][r - 1])//如果已经记录了rec[l + 1][r - 1] 
	{
		return rec[l][r] = abs(h[l] - h[r]) + rec[l + 1][r - 1];//直接计算并存储 
	}
	return rec[l][r] = abs(h[l] - h[r]) + asymmetricValue(l + 1, r - 1);//否则,递归计算 
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		h[i] = read();
	}//输入 
	printf("0 ");//长度为1时,不对称性一定为0，偷懒大师行为
	for(int i = 2; i <= n; i++)
	{
		m = INF;//保证计算最小值时一定被替换 
		for(int j = 1; j <= n - i + 1; j++)
		{
			m = min(m, asymmetricValue(j, i + j - 1));//不断重复计算并更新最小值 
		}
		printf("%d ", m);
	}
	return 0;
}
```
###### 请勿抄袭，否则您将会受到良心的谴责

[AC 记录](https://www.luogu.com.cn/record/109700192)

---

