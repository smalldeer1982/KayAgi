# Plus-Minus Split

## 题目描述

You are given a string $ s $ of length $ n $ consisting of characters "+" and "-". $ s $ represents an array $ a $ of length $ n $ defined by $ a_i=1 $ if $ s_i= $ "+" and $ a_i=-1 $ if $ s_i= $ "-".

You will do the following process to calculate your penalty:

1. Split $ a $ into non-empty arrays $ b_1,b_2,\ldots,b_k $ such that $ b_1+b_2+\ldots+b_k=a^\dagger $ , where $ + $ denotes array concatenation.
2. The penalty of a single array is the absolute value of its sum multiplied by its length. In other words, for some array $ c $ of length $ m $ , its penalty is calculated as $ p(c)=|c_1+c_2+\ldots+c_m| \cdot m $ .
3. The total penalty that you will receive is $ p(b_1)+p(b_2)+\ldots+p(b_k) $ .

If you perform the above process optimally, find the minimum possible penalty you will receive.

 $ ^\dagger $ Some valid ways to split $ a=[3,1,4,1,5] $ into $ (b_1,b_2,\ldots,b_k) $ are $ ([3],[1],[4],[1],[5]) $ , $ ([3,1],[4,1,5]) $ and $ ([3,1,4,1,5]) $ while some invalid ways to split $ a $ are $ ([3,1],[1,5]) $ , $ ([3],[\,],[1,4],[1,5]) $ and $ ([3,4],[5,1,1]) $ .

## 说明/提示

In the first test case, we have $ a=[1] $ . We can split array $ a $ into $ ([1]) $ . Then, the sum of penalties of the subarrays is $ p([1]) = 1 $ .

In the second test case, we have $ a=[-1,-1,-1,-1,-1] $ . We can split array $ a $ into $ ([-1],[-1],[-1],[-1],[-1]) $ . Then, the sum of penalties of the subarrays is $ p([-1]) + p([-1]) + p([-1]) + p([-1]) + p([-1]) = 1 + 1 + 1 + 1 + 1 = 5 $ .

In the third test case, we have $ a=[1,-1,1,-1,1,-1] $ . We can split array $ a $ into $ ([1,-1,1,-1],[1,-1]) $ . Then, the sum of penalties of the subarrays is $ p([1,-1,1,-1]) + p([1,-1]) = 0 + 0 = 0 $ .

## 样例 #1

### 输入

```
5
1
+
5
-----
6
+-+-+-
10
--+++++++-
20
+---++++-+++++---++-```

### 输出

```
1
5
0
4
4```

# 题解

## 作者：xu_zhihao (赞：1)

### 题目理解：
   - 这道题主要考察的是思维转换，题目所说将 $A$ 数组拆分为 $k$ 个非空数组，那也，就是说我们最终要达成的目标就是使每个数组的和最小，长度最短。就可以将 $+,-$ 抵消，将剩下来的字符全部单成一个数组，即这个数组付出的代价为 $1$，最后输出结果即可。


### AC 代码 ：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[5010];
int i;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		scanf("%d",&n);
		scanf("%s",s);
		int jia=0,jian=0;
		int mp=0;
		for(i=0;i<n;i++)
		{
			if(s[i]=='+')
			{
				jia++;
			}
			else
			{
				jian++;
			}
		}
		cout<<n-min(jia,jian)*2<<endl;
	}	
}
```

---

## 作者：Cynops (赞：1)

注意到和为 $0$ 的极长连续段一定会被消掉，最后剩下的一个一个消显然优于一起消。

所以答案为 $|\sum a_i|$，时间复杂度 $O(n)$，[代码](https://codeforces.com/contest/1919/submission/240514468)。

---

## 作者：Zemu_Ooo (赞：1)

简单动规题。

对于此题，我们的目标是找到一种方法，将数组 $a$ 分割成多个子数组，以使总罚金最小。

定义一数组 `dp[]`，其中 `dp[i]` 表示处理到第 $i$ 个元素时可能得到的最小罚金。为了找到 `dp[i]` 的值，我们需要考虑所有可能的分割方式，即考虑所有的 $j$（$0 \leq j < i$），将数组分为 `a[0..j]` 和 `a[j+1..i]`。现阶段目的是需要计算这两部分的罚金并相加，取所有可能分割中的最小值。

罚金的计算方式是子数组的和的绝对值乘以子数组的长度。我们可以在遍历数组时维护一个当前和，以便快速计算子数组的和。

当数组的和为零时，罚金为 $0$。因此，我们的目标应该是尽可能多地创建和为 $0$ 的子数组，以此来最小化总罚金。通过维护前缀和来实现即可，没什么好说。

对于每个位置 $i$，我们需要找到最小的位置 $j$（$j < i$），使得 `prefix_sum[i] == prefix_sum[j]`。这意味着从 $j+1$ 到 $i$ 的子数组的和为 $0$。我们可以通过这种方式最小化从开始到当前位置的罚金。


```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

int minPenal(const string& s, int n) {
    vector<int> dp(n + 1, 0);
    unordered_map<int, int> lastSum;  // 存储前缀和最后出现
    lastSum[0] = 0;  // 的位置为0
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += (s[i - 1] == '+' ? 1 : -1);
        if (lastSum.count(sum)) {
            dp[i] = dp[lastSum[sum]];
        } else {
            dp[i] = dp[i - 1] + 1;
        }
        lastSum[sum] = i;
    }
    return dp[n];
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << minPenal(s, n) << endl;
    }
    return 0;
}
```

交了一遍，发现思路无误，但是超时。

那么，就简单地优化下前缀和的计算，并减少不必要的哈希查找即可，这样能避免哈希表操作的开销。


```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int minPenal(const string& s, int n) {
    vector<int> dp(n + 1, 0);
    vector<int> lastSum(2 * n + 1, -1); // 范围 [-n, n]
    lastSum[n] = 0; // 的初始位置
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += (s[i - 1] == '+' ? 1 : -1);
        int norSum = sum + n; // 将前缀和规范化到非负索引
        if (lastSum[norSum] != -1) {
            dp[i] = dp[lastSum[norSum]];
        } else {
            dp[i] = dp[i - 1] + 1;
        }
        lastSum[norSum] = i;
    }
    return dp[n];
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << minPenal(s, n) << endl;
    }
    return 0;
}
```

---

## 作者：WAis_WonderfulAnswer (赞：0)

## 题目大意

您将得到一个字符串 $s$，长度为 $n$。您还有一个数组 $a$，如果 $s_i$ 为 ```+```，那么 $a_i = 1$，如果 $s_i$ 为 ```-```，那么 $a_i = - 1$。您可以将 $a$ 分为若干个子序列，定义一个子序列的惩罚值为 **该子序列所有数的和的绝对值乘以该子序列长度** 的结果。$a$ 的惩罚值为 **它分出的所有子序列的惩罚值的和**。现在你需要求出 $a$ 的最小惩罚值。

## 基本思路

其实在 $a$ 数组中，有些 $1$ 与 $- 1$ 是可以相互抵消的，所以我们把这些抵消的数分到一个子序列里，这样它们相加起来得 $0$，即使乘上子序列长度也是 $0$。

显然剩下的要么全是 $1$，要么全是 $- 1$ 了，显然要想让惩罚值最小，必须每一个数分为一个子序列，这样惩罚值就为这些数的绝对值相加起来的结果了。

举个例子，对于 $a = [- 1,1,- 1,1,- 1,- 1,- 1]$，我们先将其分为 $[- 1,1,- 1,1],[- 1,- 1,- 1]$，显然第一段惩罚值为 $0$，我们把第二段再分为 $[- 1],[- 1],[- 1]$，这样惩罚值就为 $3$，总惩罚值也为 $3$，显然这是最小惩罚值。

所以做法就出来了，我们把 $a$ 中的所有数相加，再取个绝对值就是答案了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int _;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		int n;
		string s;
		cin>>n>>s;
		int tmp=0;
		for (int i=0;i<(int)s.size();i++) tmp+=(s[i]=='+'?1:-1);
		cout<<abs(tmp)<<'\n';
	}
	return 0;
}
```


---

## 作者：_O_v_O_ (赞：0)

诈骗。

首先，我们考虑一段全是 `+` 或 `-` 的字符串。

可以看出，必须一个字符一段，才能让代价最小。

因为这样每个字符对答案的贡献只有 $1$，如果多个分成一组，每个贡献会更多。

我们继续考虑形如 `-+-++++` 有多个符号的的字符串。

这样还是一个字符一段最好。

因为在上述字符串中一个 `-` 只能“抵消”一个 `+` 的效果，而抵消可以将 `-` 和 `+` 每个分成一段。而抵消后，有变成上述「清一色」的字符串了。

---

## 作者：CheZiHe929 (赞：0)

# CF1919B 题解

### 题目链接

[Codeforces](https://codeforces.com/contest/1919/problem/B)

[Luogu](https://www.luogu.com.cn/problem/CF1919B)

### 简要题意

每次给定一个长度为 $n$ 的字符串 $s$，如果 $s_i$ 为 `-` 则代表对应的 $a_i$ 的值为 $-1$，为 `+` 则值为 $1$。

我们可以将 $a$ 数组划分为若干个子序列（不要求连续），每段子序列的惩罚为该子序列内所有数的和的绝对值，求最小的惩罚和。

### 简要思路

可知 $a$ 序列中只有 $1$ 和 $-1$ 两个数，所以我们要尽可能地让越多的 $1$ 和 $-1$ 在一起，使得绝对值为 $0$，那么最终的答案就是 $-1$ 和 $1$ 的数量的差的绝对值。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int T,n;
char c;

signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin>>T;
	while(T--){
		std::cin>>n;
		int cntf=0,cntz=0;//-1 和 1 的数量
		
		for(int i=1;i<=n;i++){
			std::cin>>c;
			if(c=='-')cntf++;
			else cntz++;
		}
		std::cout<<std::abs(cntf-cntz)<<endl;
	}

	return 0;
}
```

**THE END.**

**THANK YOU.**

---

## 作者：yyrwlj (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1919B)

## 题意简述

把一个由 $1$ 和 $-1$ 构成的序列分成若干段，使每段和的绝对值乘上段长的和最小，求出这个最小值。

## 思路

显然，最好让段内的和等于 $0$，因为这样就会让这一段的贡献为 $0$。

要是段内的和等于 $0$，段内 $1$ 和 $-1$ 的个数就要相同。

也就是一个 $1$ 可以抵消一个 $-1$，一个 $-1$ 也可以抵消一个 $1$。

然后我们就可以用栈来解决这个问题。判断当前数是否与栈顶元素相同，相同就弹栈，不相同就把当前数加入栈。

最后的答案就是**栈内剩余的数个数**，因为剩下的无法互相抵消，**每个数单独为一段最优**。若不单独为一段，还要乘上一个大于 $1$ 的段长。

## Code

```cpp
#include <iostream>
#include <stack>
using namespace std;
char s[5005];
void work()
{
    int n;
    scanf("%d%s", &n, s + 1);
    stack<char> sta;
    sta.push(s[1]);
    for (int i=2;i<=n;i++)
    {
        if (!sta.empty() && sta.top() != s[i])
            sta.pop();
        else
            sta.push(s[i]);
    }
    printf("%d\n", sta.size());
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：SamHJD (赞：0)

## [Plus-Minus Split](https://www.luogu.com.cn/problem/CF1919B)

### 题意

给出数组 $a$ 满足 $a_i\in \{1,-1\}$。将其分为若干段，设某一段为 $(l,r)$，则其贡献为 $(r-l+1)\times|\sum\limits_{i=l}^{r}a_i|$。

求最小贡献和。

---

### 解法

首先，对于一段相同的值，其最小贡献为其长度，证明如下：

设两个区间 $(l,m),(m+1,r)$，其长度为 $L_1,L_2$，则分开计算的贡献为 $L_1^2+L_2^2$，合起来计算的贡献为 $(L_1+L_2)^2=L_1^2+L_2^2+2L_1L_2$。显然 $2L_1L_2>0$，即分开计算贡献更小。于是最优方案为分成若干个长度为 $1$ 的区间，总贡献为区间长度。

注意到若一个区间中的 $-1,1$ 个数相同，其贡献为 $0$，于是可以贪心找和为 $0$ 的区间。将这些区间去掉后一定没有 $1$ 或 $-1$ 剩余。剩下的部分根据上面的结论最小贡献为数的个数。

于是答案为 $|\sum\limits_{i=1}^{n}a_i|$。

---

### [代码](https://codeforces.com/contest/1919/submission/240630968)


---

## 作者：thh_loser (赞：0)

# CF1919B Plus-Minus Split

## 题意
给你一个只包含 $1$、$-1$ 的数组，将这个数组再不改变顺序的情况下分为若干个非空子集，每个子集的价值是所有元素之和的绝对值与长度之积，求最小价值。

## 思路
由于每一个子集的价值都与长度有关，那么如同 $[-1,-1,-1]$ 的数组分为三个 $1$ 分别乘上 $1$ 一定比放在一起乘上 $3$ 更小。

因此我们可以得到：对于每一组能合并的数，将它们合并为 $0$，不能合并的数就一个数一个数累加，即答案就是 $1$ 与 $-1$ 个数之差的绝对值。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char s;
int main(){
	scanf("%d",&t);
	while(t--){
		int zh=0,fu=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			cin>>s; 
			if(s=='+'){//储存1和-1的个数 
				zh++;
			}
			else{
				fu++;
			}
		}
		printf("%d\n",abs(zh-fu));//输出两者之差的绝对值即可 
	}
	return 0;
} 
```

---

