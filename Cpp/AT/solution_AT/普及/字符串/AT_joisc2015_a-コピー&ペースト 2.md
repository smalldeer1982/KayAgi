# コピー&ペースト 2

## 题目描述

### 题意描述

最初 JOI 君给了你一个字符串 $s$，现在对这个字符串进行 $n$ 次操作，每次操作使得位置 $a_i$ 到 $b_i$ 的子串挪到位置 $c_i$。这里的位置可以这样理解：第 $i$ 个位置就是这个字符串的第 $i$ 个字符与第 $i+1$ 个字符之间的空隙。

但是，JOI 君怕复制的东西太多，所以他觉得如果字符数超过 $m$ 个就清除第 $m$ 个字符之后的所有字符。

现在，JOI 君想知道通过这样的复制粘贴得到的最终的字符串的前 $k$ 个字符。

对于 $100\%$ 的数据，$1\le k\le 200$，$1\le m\le 10^9$，$k\le |s|\le \min\{m,2\times 10^5\}$，$1\le n\le 2\times 10^5$。

## 说明/提示

- 对于 $40\%$ 的数据，$1\le N,M\le 2000$；
- 对于 $100\%$ 的数据，$1\le K\le 200$，$1\le M\le 10^9$，$S$ 的每个字符都是小写英文字母，$K\le |S|<=\min(M,2\times 10^5)$，$1\le N\le 2\times 10^5$，设第 $i$ 次操作前的字符串长度为 $L_i$，那么 $0\le A_i<B_i\le L_i$ 且 $0\le C_i\le L_i\ (1\le i\le N)$。

# 题解

## 作者：Star_F (赞：9)

# 题目描述：

最初 JOI 君给了你一个字符串 $s$，现在对这个字符串进行 $n$ 次操作，每次操作使得位置 $a_i$ 到 $b_i$  的子串挪到位置 $c_i$。这里的位置可以这样理解：第 $i$ 个位置就是这个字符串的第 $i$ 个字符与第  $i+1$ 个字符之间的空隙。

但是，JOI 君怕复制的东西太多，所以他觉得如果字符数超过 $m$ 个就清除第 $m$ 个字符之后的所有字符。

现在，JOI 君想知道通过这样的复制粘贴得到的最终的字符串的前 $k$ 个字符。

对于 $100\%$ 的数据，$1\le k\le 200$，$1\le m\le 10^9$，$k\le |s|\le \min\{m,2\times 10^5\}$，$1\le n\le 2\times 10^5$。


# 题目分析：

~~哎呀呀，说起这个 JOI 君啊，可真是够折腾人的！给他一个字符串，还要进行那么多操作，真是比隔壁班的数学老师还要“丧心病狂”啊！不过没关系，咱们就是喜欢这种挑战！~~

看到这道题目，我首先想的就是动态规划：

## 定义：
首先呢，咱们得建立一个动态规划的数组 $dp$，这个数组的作用就是记录每个位置在经过一系列操作后的最终位置。一开始呢，我们把每个位置的最终位置都设为它本身，也就是  $dp[i]=i$。

## 转移：

接下来呢，就是模拟操作的过程了。每次操作，JOI 君都会告诉我们从哪个位置到哪个位置的子串要挪到哪个位置。这时候，我们就要根据具体情况来更新  $dp$ 数组。

比如说，如果是一个插入操作，就是把位置 $i$ 到 $j$ 插入到 $c$ 这时候，我们就要把位置 $i$ 到 $j$ 之后的子串向右移动一位，也就是更新  $dp[i+j+1]=dp[i+j+1]+1$。

那如果是覆盖操作呢？这就需要我们根据覆盖范围和当前位置的关系来分类讨论了！

- 如果当前位置 $i$ 在覆盖范围内，也就是 $a \leq i \leq b$，那么我们将位置 $i$ 的最终位置更新为  $dp[i+a-c]$。

------------

- 如果当前位置 $i$ 在覆盖范围之前，也就是 $i < a$，那么我们将位置 $i+b+1$ 的最终位置更新为  $dp[i+b+1] - (b-a+1)$。

------------

- 如果当前位置 $i$ 在覆盖范围之后，也就是 $i > b$，那么我们将位置 $i-a+c+1$ 的最终位置更新为 $dp[i-a+c+1] + (b-a+1)$。


哎呀，经过这么一番操作，$dp$ 数组就建立好了！现在 JOI 君想知道最终字符串的前 $k$ 个字符，那我们就直接从 $dp$ 数组中取出前 $k$ 个字符就行了！这回 JOI 君可算是满意了，咱们也顺利解决了这道题目！

# Code:

```cpp
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define end cout<<endl;
#define en cout<<" ";
#define LL long long
#define U unsigned
using namespace std;
template<class T>
inline void read(T &a){ register U LL x=0,t=1; register char ch=getchar(); while(ch<'0'||ch>'9'){ if(ch=='-') t=-1; ch=getchar();} while(ch>='0'&&ch<='9'){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } a=x*t;}
inline void print(LL x){if(x<0)putchar('-'),x=-x;if(x>9) print(x/10);putchar(x%10+'0');}
void sovle(){
    int k, m, n, a[200005], b[200005], c[200005], ans[205]; 
    string s; 
    cin >> k >> m >> s >> n; 
    FOR(i,1,n)
        read(a[i]),read(b[i]),read(c[i]);
   	FOR(i,1,k) // 将答案数组初始化为升序排列的1到k
        ans[i] = i;
    ROF(i,n,1){ // 从最后一个元素开始，每次循环从输入中读取一个元素
        FOR(j,1,k) {
            if (ans[j] <= c[i]) { // 如果答案数组中的元素小于等于当前元素的值，则跳过此次操作
                continue;
            }
            if (ans[j] <= c[i] + b[i] - a[i]) { // 如果答案数组中的元素小于等于当前元素的值加上当前元素的第二个值减去第一个值，则交换两个元素的位置
                swap(ans[j], ans[ans[j] - c[i]]);
            }
            else { // 否则，找到答案数组中第一个大于当前元素的值加上当前元素的第二个值减去第一个值的元素，并交换两个元素的位置
                int index = lower_bound(ans + 1, ans + k + 1, c[i] + b[i] - a[i]) - ans;
                swap(ans[j], ans[index]);
            }
        }
    }
    FOR(i,1,k) {   //输出 
        cout << s[ans[i] - 1];
    }
	end;
}

signed main(){
    sovle();
 	return 0;
}

```

---

## 作者：ylch (赞：4)

# AT_joisc2015_a コピー&ペースト 2 题解

[-题目传送门-](https://www.luogu.com.cn/problem/AT_joisc2015_a)

[-优秀题目翻译-](https://www.luogu.com.cn/discuss/41095)

### 前言

受到楼上 ALLTOZERO 大神的启发，写了这篇题解。

思路和 Ta 的差不多，不过我是用数组存起来了，大家可以结合 Ta 的代码自行理解。

### 思路

由于最后一个操作后的位置是固定的，但是从哪里来不确定，我们可以用逆推倒着做。

首先设 $x$ 为当前第 $i$ 位在第 $j$ 次操作的位置，初始值明显是 $i$。

追根溯源，每遇到一个范围 $a$ 到 $b$ 进行插入到 $c$，因为是从原串复制粘贴的，所以可以分类一下。

第一种情况就是粘贴过来覆盖了这个位置，第二种情况就是粘贴到了这个位置的前面，然后转移方程就显而易见了。

如果是第一种情况，$i=i+a-c$；

第二种情况，$i=i-b-a$。

如此往复，我们就推出了答案。

### 代码

```cpp
#include<iostream>
using namespace std; 

int n,m,k;
string s;
int a[200005],b[200005],c[200005],ans[205];

int main()
{
    cin >> k >> m >> s >> n;
    for (int i=1; i<=n; i++)
        cin >> a[i] >> b[i] >> c[i];
    for(int i=1; i<=k; i++)
		ans[i] = i;
    for (int i=n; i>=1; i--)
    {
    	for (int j=1; j<=k; j++)
        {
            if(ans[j] <= c[i])	continue;
            if(ans[j] <= c[i]+b[i]-a[i])	ans[j] = ans[j]+a[i]-c[i];
            else	ans[j] -= b[i]-a[i];
        }
	}
    for (int i=1; i<=k; i++)
		cout << s[ans[i]-1];
	return 0;
}
```

### 总结

还是一道很有难度的找规律 + 逆推，希望大家静下心来认真思考，相信你一定能得出答案（实在不行也可以看题解）。

End
-------------------------------
管理员大大辛苦啦~

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：_determination_ (赞：2)

比较有思维含量，真感觉不止黄吧，建议升绿。

考虑到 $k$ 很小，发现 $O(nk)$ 是完全合理的。猜测复杂度就是 $O(nk)$。

$nk$ 是什么，$k$ 是输出串的每一个字符，$n$ 是操作次数。我们对于每一个字符找到所有操作以前字符的位置，直接倒序开搞即可，具体看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
int K,m,n;
string s;
int l[200010],r[200010],k[200010];
int calc(int x,int p)
{
	if(p==0)return x;
	if(x<=k[p])return calc(x,p-1);
	if(x<=k[p]+r[p]-l[p]+1)return calc(x-k[p]+l[p]-1,p-1);
	return calc(x-(r[p]-l[p]+1),p-1);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> K >> m >> s >> n;
	s=" "+s;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> l[i] >> r[i] >> k[i];
		l[i]++;
	}
	for ( int i = 1 ; i <= K ; i++ )cout << s[calc(i,n)];
	return 0;
}
```

---

## 作者：ALLTOZERO (赞：1)

这题还没有代码

所以我就只放代码了

```cpp
#include<bits/stdc++.h>

using namespace std;

int K;
/**
 * 从1<=M<=1e9可以看出与M无关. 
 */
int tmp;
string S;
int N;
int *A, *B, *C;
string ans;
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> K >> tmp >> S >> N;
	A = new int[N]();
	B = new int[N]();
	C = new int[N]();
	for(int i = 0; i != N; i++)
	{
		cin >> A[i] >> B[i] >> C[i];
	}
	for(int k = 0; k != K; k++)
	{
		tmp = k;
		/**
		 * 找到k在原串中是第几个. 
		 * 倒着扫, 还原修改的过程. 
		 * 然后倒推. 
		 */
		for(int i = N - 1; i != -1; i--)
		{
			/**
			 * 因为只有添加, 没有删除. 
			 * 所以k在原串中是比此时的C[i]靠后. 
			 */
			if(tmp < C[i])
			{
				continue;
			}
			/**
			 * 如果在添加的串之中. 
			 */
			if(tmp < C[i] + B[i] - A[i])
			{
				tmp += A[i] - C[i];
			}
			/**
			 * 否则减去添加的串的长度
			 */
			else
			{
				tmp -= B[i] - A[i];
			}
		}
		cout << S[tmp];
	}
	delete []A;
	delete []B;
	delete []C;
	cout << endl;
	return 0;
}
```


---

## 作者：da32s1da (赞：1)

```
T1复制&粘贴2题解
算法一：
直接模拟每一次的操作；
将要粘贴的那一段临时扔到一个数组里，然后将插入的位置后面的字符串右移，在将粘贴的部分复制进去就好了；
每次操作是O(len)=O(m)的，共操作n次，时间复杂度O(nm)；
注意数组越界问题，可以拿到40分；
算法二：
注意到题中所给的K非常小，所以我们设状态f[i][j]表示，最后在第j位置上的元素在第i次操作之后在f[i][j]位置上；
边界为f[n][j]=j，然后倒着递推回去；
每次操作有可能是不变，从某处粘贴过来，或者是向右平移；
讨论一下转移即可，最后得到了f[0][j]输出即是答案；
时间复杂度O(nK)，由于第一维可以滚动，所以空间复杂度O(m)；
```

---

## 作者：CodingOIer (赞：0)

## AT JOISC 2015 A コピー&ペースト 2 题解

### 思路分析

**约定：下文中将 $l$ 和 $x$ 的值均加一，这样表示把从 $l \sim r$ 的字符复制到 $x$ 的位置上。**

发现 $k$ 很小，考虑分别计算每一个需要输出的字符。

枚举初始位置 $w \in [1, k]$，记 $len = r - l + 1$，倒序处理所有的操作，有以下 $3$ 情况。

- $w < x$，不受影响。
- $x \le w < x + len$，当前位置是被复制过来的，$w \gets l + (w - x)$。
- $x + len \le w$，当前位置被复制过来的内容向右移动了 $len$ 位，$w \gets w + len$。

枚举完所有的操作后，初始字符串的第 $w$ 位就是这一位的最终字符。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m, k;
char s[MaxN];
std::vector<std::tuple<int, int, int>> v;
int main()
{
    scanf("%d%d", &k, &m);
    scanf("%s", s + 1);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        l++;
        x++;
        v.push_back({l, r, x});
    }
    std::reverse(v.begin(), v.end());
    for (int i = 1; i <= k; i++)
    {
        int w = i;
        for (auto [l, r, x] : v)
        {
            int len = r - l + 1;
            if (w < x)
            {
                continue;
            }
            else if (w < x + len)
            {
                w = l + (w - x);
            }
            else
            {
                w -= len;
            }
        }
        printf("%c", s[w]);
    }
    printf("\n");
    return 0;
}
```

---

