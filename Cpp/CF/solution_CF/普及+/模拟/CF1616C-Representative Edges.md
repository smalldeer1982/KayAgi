# Representative Edges

## 题目描述

An array $ a_1, a_2, \ldots, a_n $ is good if and only if for every subsegment $ 1 \leq l \leq r \leq n $ , the following holds: $ a_l + a_{l + 1} + \ldots + a_r = \frac{1}{2}(a_l + a_r) \cdot (r - l + 1) $ .

You are given an array of integers $ a_1, a_2, \ldots, a_n $ . In one operation, you can replace any one element of this array with any real number. Find the minimum number of operations you need to make this array good.

## 说明/提示

In the first test case, the array is good already.

In the second test case, one of the possible good arrays is $ [1, 1, \underline{1}, \underline{1}] $ (replaced elements are underlined).

In the third test case, the array is good already.

In the fourth test case, one of the possible good arrays is $ [\underline{-2.5}, -2, \underline{-1.5}, -1, \underline{-0.5}, 0] $ .

## 样例 #1

### 输入

```
5
4
1 2 3 4
4
1 1 2 2
2
0 -1
6
3 -2 4 -1 -4 0
1
-100```

### 输出

```
0
2
0
3
0```

# 题解

## 作者：0xFF (赞：3)

#### 题目大意


------------
给定一个数列 $a$ 问最多改动几次序列中的元素使得这个序列满足对于每一个区间 $[l,r]$ 都有 $a_{l}+a_{l+1}+\ldots+a_{r}=\frac{1}{2}\left(a_{l}+a_{r}\right) \cdot(r-l+1)$。

#### 题目分析


------------
观察等式右边不难发现这个式子实际上就是等差数列的求和公式，也就是说要满足这个序列是一个等差序列。

所以题目可以转化为最少改动 $a$ 序列中的几个元素可以满足 $a$ 是一个等差数列。

正难则反。

考虑找出 $a$ 序列中最多有多少个元素是不需要改动的，即有多少段区间的公差相等，所以题目可以转化为找出最多有多少段不用修改的的区间，由于这些区间一定满足单调性，故题目转化为求满足 $\frac{a_{k}-a_{i}}{k-i}=\frac{a_{k}-a_{j}}{k-j}$ 的组数，记录下答案 ```ans```，最后输出 ```n - ans``` 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int N = 100;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int a[N];
signed main(){
	int T = read();
	while(T--){
		int n = read() , ans = 1;
		for(int i=1;i<=n;i++) a[i] = read();
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				int res = 0;
				for(int k=1;k<=n;k++){
					if(k==i||k==j){
						res++;
						continue;
					}
					if((a[k]-a[i])*(k-j)==(a[k]-a[j])*(k-i)) 
						res++;
				}
				ans = max(ans,res);
			}
		}
		printf("%lld\n",n - ans);
	}
	return 0;
} 
```


---

## 作者：activeO (赞：2)

## 题目大意

修改尽量少的元素，使得对于任意一段区间都是等差数列。

## 思路

当你看懂题目的时候，本题就已经很简单了。

我们可以反过来求最多有多少段不用修改的，也就是公差一样的区间，即：

$ \frac{a_k-a_i}{k-i} = \frac{a_k-a_j}{k-j} $，程序中要转为乘法形式。

求最多不用修改的区间 res，最后答案是 $ n - res $。

时间复杂度：$ O(t \cdot n^3) $ 可以通过此题。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=80;
int a[maxn];

int main(){
	
	int t;
	
	scanf("%d",&t);
	
	while(t--){
		int n,ans=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				int res=0;
				for(int k=1;k<=n;k++){
					if(k==i||k==j||(a[k]-a[i])*(k-j)==(a[k]-a[j])*(k-i)) res++;
				}
				ans=max(ans,res);//不用修改的越多越好
			}
		}
		printf("%d\n",n-ans);
	}
	
	return 0;
}
```


---

## 作者：JCLinux (赞：1)

## 思路：

翻译一下题目中的等式的意思：任何一个区间的**首尾的平均值**就是这个区间的**平均值**。

当区间长度为 $1$ 或者 $2$ 时，任何区间都满足这个性质，当区间长度为 $3$ 时，这说明什么？

这说明~~中间那个数是首位的平均值~~，那么这三个数构成的数列是一个**等差数列**。

因为整体序列要满足这个性质，则它**所有的子序列**都要满足这个性质，因此这个性质被推广到**整个序列**。

也就是说，一个“好的”序列一定是一个等差序列。

那我们现在只需要修改其中的一些元素，让整个序列成为等差序列就好，怎么样才能修改最少个数呢？

我们尽可能地找最多的已经“成型”的元素，把剩下的改好这样不就行了吗？

对于一个等差数列，我们只要知到任意两项，和这两项之间的距离，我们就可以举出整个序列。

我们注意到 $n$ 最大只有 $70$，因此我们可以暴力枚举这两项，然后判断以这两项作为被选定项，剩下能有多少元素能够吻合就 OK 了，注意变化一下判断的式子，不要出现浮点型，以免有误差。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int arr[75];
int test(int a,int b)
{
    int num=0;
    //arr[i]+(arr[b]-arr[a])/(b-a)*(a-i)==arr[a]      原式子
    //arr[i]*(b-a)+(arr[b]-arr[a])*(a-i)==arr[a]*(b-a)   变换式子，避免了浮点型
    for(int i=1;i<=n;i++)
        if(arr[i]*(b-a)+(arr[b]-arr[a])*(a-i)==arr[a]*(b-a)) num++;
    return num;
}
int main()
{
    cin.sync_with_stdio(false);
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i=1;i<=n;i++) cin >> arr[i];
        int mmax=0;
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++)
                mmax=max(mmax,test(i,j));
        if(n>1)cout << n-mmax << "\n";
        else cout << "0\n";//特判1
    }
    return 0;
}

```


---

## 作者：XiaoQuQu (赞：0)


观察一下题目，发现这个限制可以被等价的转换为使得这个 $a$ 为一个等差序列。然后我们发现，有一个显然的性质是，我们的最终的等差序列的公差 $d$ 一定是**保留某两个元素 $i,j$，构造出 $d=\frac{(a_j-a_i)}{j-i}$**。

于是枚举两个元素 $i,j$，计算出公差 $d$，然后计算一下有多少个元素需要修改。

注意判断的时候设一个精度 $eps$。

```cpp
const int MAXN = 100 + 5;
const long double eps = 1e-9;
int n;
long double a[MAXN];

auto cmp(long double x, long double y) {
	if (abs(x - y) <= eps) return true;
	return false;
}

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	if (n == 1)
		return cout << 0 << endl, void();
	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			long double d = (a[j] - a[i]) * 1.0 / (j - i);
			int cnt = 0;
			for (int k = 1; k < i; ++k)
				if (!cmp(a[i], a[k] + (i - k) * d)) ++cnt;
			for (int k = i + 1; k <= n; ++k)
				if (!cmp(a[k], a[i] + (k - i) * d)) ++cnt;
			ans = min(ans, cnt);
		}
	}
	cout << ans << endl;
}
```

---

## 作者：Retired_lvmao (赞：0)

#### 题意

定义一个序列是好的，当且仅当对于任意的 $l,r\in{[1,n]}$ 都有 $l>r$ 或 $\sum_{i=l}^r A_i=\frac{1}{2}(A_l+A_r)\times(r-l+1)$。

给定一个序列 $A$，求至少要替换掉多少个数，才能使得 $A$ 是好的。

$T\leq 100$，$n\leq 70$

#### 题解

容易发现一个序列是好的，当且仅当这个序列是一个等差数列。又因为数据范围很小，故可以钦定序列中两个数不变，然后暴力计算剩下的数是否需要替换，对所有情况取最小值即可。复杂度 $O(Tn^3)$

#### 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int n;
double a[100010];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lf",&a[i]);
		if(n<=2)
		{
			puts("0");
			continue;
		}
		int ans=1e9;
		for(int i=1;i<=n;i++)
		{
			for(int s=1;s<=n;s++)
			{
				int tmp=0;
				double j=s==i?0:1.0*(a[s]-a[i])/(s-i);
				double sumr=a[i]+j,suml=a[i]-j;
				int flag=0;
				for(int k=i+1;k<=n;k++)
				{
					if(fabs(sumr-a[k])>1e-6)
						tmp++;
					sumr+=j;
				}
				for(int k=i-1;k>=1;k--)
				{
					if(fabs(suml-a[k])>1e-6)
						tmp++;
					suml-=j;
				}
				ans=min(ans,tmp);	
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：lijinghui (赞：0)

# 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1616C)
## 分析

很容易看出，题目中的公式实际上就是等差数列求和公式，所以我们只需要是数列成为等差数列即可。

而每次可以替换一个整数（替换的数可以是任意有理数），所以我们只需要找到数组中最长的子数组，满足：

下标为等差数列，且元素也为等差序列。

再用原数组元素个数减该子数组元素个数，即可求出最少操作次数。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e2;
int a[N];
void run()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=1;
	for(int d=1;d<=n;d++)
	{
		for(int j=1;j<=n;j++)
		{
			int cnt=0;
			for(int i=j;i<=n;i++)if(0.0+a[i]-a[j]==1.0*(a[j+d]-a[j])*(i-j)/d)cnt++;
			for(int i=j;i>=1;i--)if(0.0+a[j]-a[i]==1.0*(a[j+d]-a[j])*(j-i)/d)cnt++;
			ans=max(ans,cnt-1);
		}
	}
	cout<<n-ans<<endl;
	return;
}
int main()
{
	int t;
	cin>>t;
	while(t--)run();
	return 0;
}
```

---

## 作者：hcywoi (赞：0)

#### 分析
要满足 $\sum_{i=l}^{r}a_i = \frac{1}{2}(a_r - a_i)(r - l + 1)$,也就是要满足这个序列为等差数列。

我们设长度最长的等差序列的元素个数为 $cnt$， 则答案就为 $n - cnt$。因为题目说任意实数，所以如果最长的等差序列固定一定能修改成等差序列。

这题的 $n \le 70$，所以最长等差数列可以 $O(n^3)$ 暴力枚举。那么就先确定两个数 $i, j$，在枚举 $k$，如果合法就满足 $\frac{a_i-a_j}{i-j} = \frac{a_k - a_j}{k - j}$

#### Ac Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 80;

int n;
int a[N];

int main()
{
    int T;
    cin >> T;
    while (T -- )
    {
        cin >> n;
        for (int i = 0; i < n; i ++ ) cin >> a[i];

        int res = 1; // 一个数也能构成等差数列，所以初值为1
        for (int i = 0; i < n; i ++ )
            for (int j = i + 1; j < n; j ++ )
            {
                int cnt = 2;
                for (int k = j + 1; k < n; k ++ ) // 如果k < j，那么一定会被前面枚举到，所以k从j+1开始
                    if ((a[i] - a[j]) * (k - j) == (a[k] - a[j]) * (i - j)) // 因为精度问题，所以把除法变成乘法
                        cnt ++ ;
                
                res = max(res, cnt);
            }

        cout << n - res << endl;
    }
    
    return 0;
}
```

---

