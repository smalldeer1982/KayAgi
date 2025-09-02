# Maximal AND

## 题目描述

Let $ \mathsf{AND} $ denote the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \mathsf{OR} $ denote the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

You are given an array $ a $ of length $ n $ and a non-negative integer $ k $ . You can perform at most $ k $ operations on the array of the following type:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) and replace $ a_i $ with $ a_i $ $ \mathsf{OR} $ $ 2^j $ where $ j $ is any integer between $ 0 $ and $ 30 $ inclusive. In other words, in an operation you can choose an index $ i $ ( $ 1 \leq i \leq n $ ) and set the $ j $ -th bit of $ a_i $ to $ 1 $ ( $ 0 \leq j \leq 30 $ ).

Output the maximum possible value of $ a_1 $ $ \mathsf{AND} $ $ a_2 $ $ \mathsf{AND} $ $ \dots $ $ \mathsf{AND} $ $ a_n $ after performing at most $ k $ operations.

## 说明/提示

For the first test case, we can set the bit $ 1 $ ( $ 2^1 $ ) of the last $ 2 $ elements using the $ 2 $ operations, thus obtaining the array \[ $ 2 $ , $ 3 $ , $ 3 $ \], which has $ \mathsf{AND} $ value equal to $ 2 $ .

For the second test case, we can't perform any operations so the answer is just the $ \mathsf{AND} $ of the whole array which is $ 4 $ .

## 样例 #1

### 输入

```
4
3 2
2 1 1
7 0
4 6 6 28 6 6 12
1 30
0
4 4
3 1 3 1```

### 输出

```
2
4
2147483646
1073741825```

# 题解

## 作者：Nt_Tsumiki (赞：5)

## 题意

[题目传送门](https://www.luogu.com.cn/problem/CF1669H)

给你数组 $a$，将每一个 $a_i$ 按位或 $2^j$ 后，输出 $a_1$ 按位与 $a_2$ 按位与 $…… a_n$ 的最大值。 

## 做法

明显大模拟，从高位依次枚举使得答案的二进制的每一位均为 $1$ 即可。

因为按位与的性质，所以只需要将第 $j$ 位为 $0$ 最后出现的那个 $a_i$ 的第 $j$ 位改变即可（可能有点绕，感性理解）。

注意多组数据。

## Code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int N=1e6;
int t,n,k,a[N];

signed main() {
    scanf("%d",&t);
    for (int l=1,ans=0;l>=t;l++) {
        cin>>n>>k;
        for (int i=1;i<=n;i++) scanf("%d",a+i);
        for (int i=30,tmp=0;i>=0;i--) {
            for (int j=1;j<=n;j++) tmp+=(a[j]>>i&1^1);
            if (k>=tmp) {
                k-=tmp;
                ans|=1<<i;
            }
        }   
        printf("%d\n",ans);
    }
}

```

---

## 作者：2huk (赞：4)

## Descrition

给定一个长度为 $n$ 的序列 $a$，你可以进行最多 $k$ 次操作，每次操作可以将某个 $a_i$ 的某二进制位设为 $1$。问最后 $\operatorname{And}_{i = 1}^n a_i$ 的最大值。其中 $\operatorname{And}$ 表示[按位与](https://oi-wiki.org/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96)运算。

## Solution

首先，对于某一位 $j$，如果存在一个 $a_i$ 的第 $j$ 位不为 $1$，那么它们与起来的第 $j$ 位也一定不为 $1$。因此我们尽量一次让所有的 $a_i$ 的第 $j$ 位同时为 $1$。

那么我们应该选择哪一个 $j$ 呢？显然我们应该选择较大的 $j$，即从 $j = 30$ 开始填，把所有的 $a_i$ 的第 $j$ 位都填成 $1$。如果可以填完，那么全部填满并继续尝试填下一位，否则就干脆这一位啥也不填。然后统计答案即可。

我们可以维护一个桶，$t_j$ 表示有多少个 $a_i$ 的第 $j$ 位为 $1$，那么在填第 $i$ 位时只需要填 $n - t_j$ 个值。

## Code

```cpp
int n, k, x, t[31];

int Solve()
{
	n = read(), k = read();
	memset(t, 0, sizeof t);
	
    for (int i = 1; i <= n; ++ i )
	{
		x = read();
		for (int j = 0; j <= 30; ++ j )
			if (x >> j & 1)
				++ t[j];
	}
	
	int res = 0;
    for (int i = 30; i >= 0; -- i )
		if (k >= n - t[i])
			res |= 1 << i,
			k -= n - t[i];
	
	return res;
}
```

---

## 作者：JS_TZ_ZHR (赞：2)

## 题意：

给定一个长为 $n$ 的数组 $a$，你可以进行 $k$ 次操作，每次可以选取一个 $a_i$ 使得 $a_i$ 变为 $a_i \text{ OR } 2^j$ ，其中 $0
\le j\le 30$。问最后 $ a_1 $ $ \mathsf{AND} $ $ a_2 $ $ \mathsf{AND} $ $ \dots $ $ \mathsf{AND} $ $ a_n $ 最大多少。

## 题解：

考虑到 $2^j\ge \sum\limits_{i=1}^{j-1}2^i$ 以及每一位互不干扰，$j$ 从大到小贪心即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int T,n,a[N],k,ans,cnt[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		ans=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=0;i<=30;i++){
			cnt[i]=0;
			for(int j=1;j<=n;j++){
				if(!(a[j]&(1<<i)))cnt[i]++;
			}
		}
		for(int i=30;i>=0;i--)if(k>=cnt[i])k-=cnt[i],ans+=(1<<i);
		cout<<ans<<endl;
	}
} 
```


---

## 作者：cff_0102 (赞：1)

要最后的结果最大，明显需要尽量的选择高位来更新。

设每一步的剩余操作次数是 $k'$。先从最高位开始，假如 $a$ 数组中这一位有超过 $k$ 个 $0$，那么替换掉其中的 $k$ 个也无法让这一位最终的答案变为 $1$，所以就直接跳过这一位。假如这一位 $0$ 的数量小于等于 $k$，那么就可以把所有数的这一位替换成 $1$，然后继续看下一位。

剩下的位数也一样，假如 $a$ 数组中这一位有超过 $k'$ 个 $0$，那么替换掉其中的 $k'$ 个也无法让这一位最终的答案变为 $1$，所以就直接跳过这一位。假如这一位 $0$ 的数量小于等于 $k'$，那么就可以把所有数的这一位替换成 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[229028];
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n,k;cin>>n>>k;
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		int ans=0;
		for(int i=30;i>=0;i--){
			int s=0;//记录这一位上有几个 1
			for(int j=0;j<n;j++){
				s+=(a[j]>>i)&1;//a[j] 在 2 进制上的第 i 位 
			}
			if(k>=(n-s)){//总共 n 个数，其中 s 个 1，(n-s) 个 0
				k-=(n-s);//将这一位的 0 全部换成 1 
				s=n;
			}if(s==n){
				ans+=1<<i;//此时最终答案中第 i 位二进制为 1 
			}
		}
		cout<<ans<<endl;//别忘了换行 
	}
	return 0;
}
```

---

## 作者：Shadow_T (赞：1)

### 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF1669H)

有一个长度为 $n$ 的数列 $a$，有 $k$ 次操作，每次操作可以将将一个数的其中一个二进制位变 $1$。求操作后 $a_1 \operatorname{AND} a_2 \operatorname{AND} … \operatorname{AND} a_n$ 的最大值。

### 做法分析

用贪心的思想。按位与运算必须要两个二进制位都是 $1$，才能得到 $1$。所以要结果最大，那么就要选择高位来更新。所以只需要将第 $j$ 位为 $0$ 最后出现的那个 $a_i$ 的第 $j$ 位改变即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k,a[1000001];
int solve()
{
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int t=0;
		for(int j=1;j<=n;j++) 
		t+=(a[j]>>i&1^1);//核心所在 
		if(k>=t) k-=t,ans|=1<<i;
	}
	return ans;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		scanf("%d",a[i]);
		cout<<solve()<<'\n';
	}
}
```

---

## 作者：ncwzdlsd (赞：0)

考虑按位与运算的性质，先要尽量把高位统一修改为 $1$。

统计修改每一位全部为 $1$ 需要花费的操作次数 $cnt_i$，从高位考虑修改即可。如果当前需要的修改次数大于剩余的可操作次数，则当前位为 $0$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+5;
int a[maxn],cnt[35];

void solve()
{
    int ans=0;
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(cnt,0,sizeof cnt);
    for(int i=0;i<=30;i++)
        for(int j=1;j<=n;j++) if(!((a[j]>>i)&1)) cnt[i]++;
    for(int i=30;i>=0;i--) 
        if(k>=cnt[i])
            k-=cnt[i],ans+=(1<<i);
    cout<<ans<<endl;
}

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：FBW2010 (赞：0)

# 思路
首先，题目要求所有数按位与的最大值，显然可以贪心。我们从最高位开始，每次尝试把那一位变成一，如果操作次数在 $k$ 以内，就把 $k$ 减去操作数，再累加答案，否则继续看下一位。

# 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int t,n,k,a[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		int ans=0;
		for(int i=30;i>=0;i--){
			int sum=0;
			for(int j=1;j<=n;j++){
				if((a[j]>>i)%2)sum++;
			}
			if(n-sum<=k){
				ans+=1<<i;
				k-=n-sum;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
我们可以按位考虑。

有一个显然的性质：如果答案二进制表示的第 $i$ 位为 $1$，则 $a$ 中所有数二进制表示的第 $i$ 位都为 $1$，这个由与运算的定义即可得到。

那么我们就可以处理出来一个 $p$ 数组，$p_i$ 表示把 $a$ 中数二进制表示第 $i$ 位全变成 $1$ 的操作数，$p_i=n-a$ 中二进制表示第 $i$ 位为 $1$ 的数的数量。

接下来考虑分配操作，因为我们想让答案尽量大，所以应该从高位向低位枚举一个位数 $i$，如果 $k>p_i$，答案就加上 $2^i$ 同时 $k=k-p_i$，然后依次求解即可。

这样做为什么是对的呢？因为如果 $k$ 能让答案第 $i$ 位变为 $1$，而我们不进行操作，那么即使比 $i$ 低的所有位都为 $1$，对答案的贡献也仅有 $2^i-1<2^i$，所以尽量把操作放在高位一定是最优的。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2e5+5;
int a[maxn],p[35],n,k,ans;
void solve(){
	ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=30;i++) p[i]=0;
	for(int j=0;j<=30;j++)
		for(int i=1;i<=n;i++)
			if((a[i]&(1<<j))) p[j]++;
	for(int i=0;i<=30;i++) p[i]=n-p[i];
	for(int i=30;i>=0;i--){
		if(k>=p[i]){
			k-=p[i];
			ans+=(1<<i);
		}
	}
	printf("%d\n",ans);
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 题意简述：

有一个长度为 $n$ 的数组，有 $k$ 次操作，每次操作可以把任意一个数的位数小于等于 $30$ 的二进制位变为一，求整个数组的按位且。

## 大致思路：

一个非常基础的想法：每次更新必然把数组中所有数的那一位变为 $1$，否则对于答案没有贡献。

首先我们要知道，$2^k> \sum_{i=0}^{k-1}2^i$。证明可使用数学归纳法，这里我就不细讲了。

既然知道了这个性质，我们就想到了一种贪心策略，那就是尽量选择高位来更新，这样能保证最终的值最大。

具体地，我们统计每个数有哪些位已经被更新，也就是说每个数的二进制值中有哪些位为 $1$。

我们将每一位已经被更新过的数量统计，这样我们这一位需要被更新的数量就已明了，剩下的就是贪心了。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int t = read();
signed main() {
	while (t--) {
		int n = read(), b[50], k = read(), ans = 0;
		memset(b, 0, sizeof(b));
		for (int i = 1; i <= n; i++) {
			int a = read();
			for (int j = 30; j >= 0; j--) {
				if (a >= (1 << j)) {
					a -= (1 << j);
					b[j]++;
				}
			}
		}
		for (int i = 30; i >= 0; i--) {
			if (k >= n - b[i]) {
				k -= n - b[i];
				ans += (1 << i);
			}
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Phartial (赞：0)

显然，要使得答案其中一位（二进制）为 $1$，那么这个序列里的所有数这一位都必须是 $1$，而低位再怎么选择也超过不了高位，所以我们可以从大到小枚举答案的第 $i$ 位，如果当前剩余操作次数可以把这一位变成 $1$，那么我们肯定会选择将这一位变成 $1$，否则跳过。

```cpp
#include <iostream>

using namespace std;

const int kN = 2e5 + 1;

int t, n, k, a[kN], ans;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    ans = 0;
    for (int i = 30; i >= 0; --i) {  // 从高到低枚举答案的第 i 位
      int c = 0;
      for (int j = 1; j <= n; ++j) {
        c += a[j] >> i & 1 ^ 1;  // 统计数列中有多少个数这一位为 0（即统计需要操作多少次）
      }
      if (k >= c) {             // 如果可以把这一位变成 1
        k -= c, ans |= 1 << i;  // 那么把这一位变成 1 肯定会更优
      }
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：ylinxin2010 (赞：0)

## CF1669H题解

**题目翻译：**

给你一个数组，可以将 $a_i$ 的某个二进制为设为 1，求最大的 $a_1\ \mathsf{AND}\ a_2\ \mathsf{AND} \dots\ \mathsf{AND}\ a_n$，多组数据，数组大小的和不超过 $2 \times 10^5$。

**本题思路：**

由于第 $2^i > \sum \limits_{j = 0}^{i - 1} 2^j$，所以可以考虑贪心。

1. 统计已有位数。
2. 从大到小枚举修改的位。
3. 判断此位能否修改，并累加。

**复杂度分析：**

时间： $O(\min(T \cdot N, 2 \times 10^5))$。

空间： $O(N)$。

接下来——上代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5, L = 31;

int n, k, t, a[N], h[L];

int main() {
  cin >> t;
  for (; t; t--) {
    int r = 0;
    memset(h, 0, sizeof(h));
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      for (int j = 0; j < 31; j++) { // 统计已有位数
        h[j] += a[i] >> j & 1;
      }
    }
    for (int i = 30; i >= 0; i--) {
      if (n - h[i] <= k) { // 判断能否统计
        k -= n - h[i];
        r += 1 << i; // 删去操作数并累加
      }
    }
    cout << r << '\n';
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题目描述

[Maximal AND](https://www.luogu.com.cn/problem/CF1669H)

题目是求每一个 $a_i$ 按位或 $2^j$ 后，$a_1$ 按位与 $a_2$ 按位与……按位与 $a_n$ 的最大值。

## 注意事项

这题需要用到按位与，不懂按位与的用法和性质的同学可以[点这里](https://blog.csdn.net/m0_61567378/article/details/121991196?spm=1001.2014.3001.5506)了解一下按位与。

这题需要用到按位或，不懂按位与的用法和性质的同学可以[点这里](https://blog.csdn.net/weixin_42837024/article/details/98745019?ops_request_misc=&request_id=&biz_id=102&utm_term=%E6%8C%89%E4%BD%8D%E6%88%96&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~sobaiduweb~default-4-98745019.268^v1^control&spm=1018.2226.3001.4450)了解一下按位或。

# 算法思路

看到题目，一下子就想到了**模拟**，要使得答案的二进制每一位都是 $1$，根据按位或的特点，只要找出最后出现的第 $j$ 位是 $0$ 的 $a_i$，把 $a_i$ 的第 $j$ 位变成 $1$ 就行了。

### 时间复杂度：$O(\log \max{a_i} \times t \times n)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=200010; 
ll t,n,k,a[N],ans,daan;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)//t组数据 
	{
		ans=0;//归零，我差点忘记 
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=30;i>=0;i--)
		{
			daan=0;
			for(int j=1;j<=n;j++)
			{
				daan+=(a[j]>>i&1^1);//本题精髓 
			}
			if(k>=daan)
			{
				k-=daan;
				ans|=1<<i;
			}
		}   
		cout<<ans<<"\n";//输出答案 
	}
	return 0;
}
```


---

## 作者：user470883 (赞：0)

## 思路：

### 前置知识：
按位或：

将一个 $10$ 进制数转换成二进制，将末尾对齐做按位或，只要几个数有 `1`，直接置为 `1`，否则为 `0`。

例如：
```
1 0 0 1
1 1 0 1
———————
1 1 0 1
```
从右往左，第一位 $2$ 个 `1`，结果为 `1`，第二位都是 `0`，结果才能是 `0`。

### 正篇：

贪心。

根据上面的按位或，我们很显然想到“一列”里面必然全是 $1$，要不然就是徒劳（答案为 $0$）。

然后我们不难想到我们尽量选择高位进行更新（也就是尽量在 $0$ 多的位置上填，少填 $1$）。

我们接着统计数的哪些位已经变成 $1$，再来贪心即可。

模拟。

这题用暴力来模拟也可以，从高往底一次枚举，就不详细讲了。

代码太丑，略。

---

