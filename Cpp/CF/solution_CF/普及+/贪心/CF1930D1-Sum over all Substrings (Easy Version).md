# Sum over all Substrings (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

For a binary $ ^\dagger $ pattern $ p $ and a binary string $ q $ , both of length $ m $ , $ q $ is called $ p $ -good if for every $ i $ ( $ 1 \leq i \leq m $ ), there exist indices $ l $ and $ r $ such that:

- $ 1 \leq l \leq i \leq r \leq m $ , and
- $ p_i $ is a mode $ ^\ddagger $ of the string $ q_l q_{l+1} \ldots q_{r} $ .

For a pattern $ p $ , let $ f(p) $ be the minimum possible number of $ \mathtt{1} $ s in a $ p $ -good binary string (of the same length as the pattern).

You are given a binary string $ s $ of size $ n $ . Find $ $$$\sum_{i=1}^{n} \sum_{j=i}^{n} f(s_i s_{i+1} \ldots s_j). $ $  In other words, you need to sum the values of  $ f $  over all  $ \\frac{n(n+1)}{2} $  substrings of  $ s $ .</p><p> $ ^\\dagger $  A binary <span class="tex-font-style-it">pattern</span> is a string that only consists of characters  $ \\mathtt{0} $  and  $ \\mathtt{1} $ .</p><p> $ ^\\ddagger $  Character  $ c $  is a mode of string  $ t $  of length  $ m $  if the number of occurrences of  $ c $  in  $ t $  is at least  $ \\lceil \\frac{m}{2} \\rceil $ . For example,  $ \\mathtt{0} $  is a mode of  $ \\mathtt{010} $ ,  $ \\mathtt{1} $  is not a mode of  $ \\mathtt{010} $ , and both  $ \\mathtt{0} $  and  $ \\mathtt{1} $  are modes of  $ \\mathtt{011010}$$$.

## 说明/提示

In the first test case, the only $ \mathtt{1} $ -good string is $ \mathtt{1} $ . Thus, $ f(\mathtt{1})=1 $ .

In the second test case, $ f(\mathtt{10})=1 $ because $ \mathtt{01} $ is $ \mathtt{10} $ -good, and $ \mathtt{00} $ is not $ \mathtt{10} $ -good. Thus, the answer is $ f(\mathtt{1})+f(\mathtt{10})+f(\mathtt{0}) = 1 + 1 + 0 = 2 $ .

In the third test case, $ f $ equals to $ 0 $ for all $ 1 \leq i \leq j \leq 5 $ . Thus, the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
1
1
2
10
5
00000
20
11110110000000111111```

### 输出

```
1
2
0
346```

# 题解

## 作者：selcouth (赞：3)

### CF1930D1 Sum over all Substrings (Easy Version)

#### 题目大意

有两个 01 串 $p$ 和 $q$，$p_i$ 为 $q$ 在区间 $[l, r]$ 的区间众数，并且满足 $l \le i \le r$。使用 $|q|$ 表示 01 串 $q$ 中 $1$ 的个数，我们需要求出给出的 01 串 $s$ 中每个字串对应的 $1$ 个数最小的 $q$ 的 $1$ 个数之和。  



#### 大体思路

由于本题数据大小，对于小数据，我们可以使用贪心的思路解决。

先考虑以下的情况：当 $p$ 为 $111$ 时，我们可以发现 $|q|$ 最小的 $q$ 为 $010$；当 $p$ 为 $100$ 时，我们也可以让 $q$ 为 $010$。$p_1$ 对应区间 $q[1, 2]$，$p_2$ 对应区间 $[2, 3]$ 或 $[1,2]$，$p_3$ 对应区间 $[2, 3]$。

因此我们不难发现，当 $p_i$ 为 $1$ 时，我们可以跳过考虑其后 $2$ 位的值，因为只需要让 $q_{i+1}=1$ 可以同时满足 $p_i$，$p_{i+1}$，$p_{i+2}$。

这样我们就可以暴力枚举子串，执行贪心策略，时间复杂度为 $O(n^3)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> s;
        int ans = 0;
        s = ' ' + s;
        for(int i = 1; i<=n; i++)
        {
            for(int j = i; j<=n; j++)
            {
                string p = s.substr(i, j);
                int st = 0;
                p = ' ' + p;
                for(int k = 1; k<=j-i+1; k++)
                {
                    if(p[k] == '1')
                    {
                        ans++;
                        k += 2;
                    }
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
```

另外，对于本题的数据加强版：[Sum over all Substrings (Hard Version)](https://www.luogu.com.cn/problem/CF1930D2)，需要用到 dp 的做法。

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
定义两个 01 串 $p$ 和 $q$，对于所有的 $p_i$，存在 $q$ 中有一个区间使得 $p_i$ 是这个区间的众数，这个 $q$ 被称为好的串，求所有 $p$ 的子串中 $1$ 最少的 $q$ 里的 $1$ 的个数之和。
## 大体思路
因为本题 $n$ 较小，我们可以贪心用 $O(n^2)$ 过掉。

我们反向思考一下，题目就是就是求在 $q$ 取最少的 $1$ 的情况下，能够换掉最多的 $p$。

对于每一个 $q$ 中的 $1$，都可以最多让 $p$ 中连续的三个位置取到 $1$，简单来说就是最多换掉 $p$ 中三个连续的 $1$（它本身，他左边那个和他右边那个）。那么我们从前往后从 $p$ 上贪心，如果遇到一个没有被换掉的 $1$，就在他的下一个位置所对应的 $q$ 中的位置放一个 $1$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		s=' '+s;//让大串1下标 
		int ans=0;//一定要记住q和p长度是一样的 
		for(int i=1;i<=n;i++){//枚举一下子串 
			int sum=0;
			int x=2;//先给第一个1 安排上一个 
			for(int j=i;j<=n;j++){
				x++;//离上一个q中1的距离加1 
				if(s[j]=='1'&&x>2){//是1且可以前面也有一个以上的1 
					x=0;//答案加一，距离清零 
					sum++;
				}
				ans+=sum;//答案加上每一个子串的贡献 
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

