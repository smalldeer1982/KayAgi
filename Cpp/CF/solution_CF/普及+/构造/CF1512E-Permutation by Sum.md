# Permutation by Sum

## 题目描述

A permutation is a sequence of $ n $ integers from $ 1 $ to $ n $ , in which all the numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ are permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ are not.

Polycarp was given four integers $ n $ , $ l $ , $ r $ ( $ 1 \le l \le r \le n) $ and $ s $ ( $ 1 \le s \le \frac{n (n+1)}{2} $ ) and asked to find a permutation $ p $ of numbers from $ 1 $ to $ n $ that satisfies the following condition:

- $ s = p_l + p_{l+1} + \ldots + p_r $ .

For example, for $ n=5 $ , $ l=3 $ , $ r=5 $ , and $ s=8 $ , the following permutations are suitable (not all options are listed):

- $ p = [3, 4, 5, 2, 1] $ ;
- $ p = [5, 2, 4, 3, 1] $ ;
- $ p = [5, 2, 1, 3, 4] $ .

 But, for example, there is no permutation suitable for the condition above for $ n=4 $ , $ l=1 $ , $ r=1 $ , and $ s=5 $ .Help Polycarp, for the given $ n $ , $ l $ , $ r $ , and $ s $ , find a permutation of numbers from $ 1 $ to $ n $ that fits the condition above. If there are several suitable permutations, print any of them.

## 样例 #1

### 输入

```
5
5 2 3 5
5 3 4 1
3 1 2 4
2 2 2 2
2 1 1 3```

### 输出

```
1 2 3 4 5 
-1
1 3 2 
1 2 
-1```

# 题解

## 作者：gi_A (赞：5)

可以知道，对于区间 $[l,r]$ 之外的数字没有要求，把题目稍微简化一下就是：在 $[1,n]$ 中选取 $r-l+1$ 个不重复的数字，使他们和为 $s$，并构造出一组方案。


------------


有一个结论：

在 $[1,n]$ 中选取 $k$ 个不重复的数字之和的值域为一段区间 $[L_k,R_k]$，$L_k=1+2+...+k,R_k=n+(n-1)+...+(n-k+1)$。

~~感性地~~ 证明：

- 不会有选取方案使得数字之和大于 $R$ 或者小于 $L$。

- 设当前选取的方案为序列 $\{ a_1,a_2...a_k \}$（按从小到大排列）。当 $\sum a < R$ 时，一定可以找到一个 $a_i$ 有 $a_i+1$ 没有被选择，将最大的 $a_i$ 变成 $a_i+1$ 可以使得和增加一，且排列顺序不改变（仍然有 $a_{i-1}<a_i<a_{i+1}$）。

因此，我们就可以快速判断 $s$ 是否合法了。


------------


然后考虑如何构造一组方案：

假设当前还剩 $k$ 个空位，从小到大枚举每一个数 $x$ 判断是否可以被选择，即 $s-x$ 是否可以被 $k-1$ 个数构造出来。如果可以，从 $s$ 中减去 $x$ 并将 $k$ 减 $1$。

若最后选择的数字个数不是 $r-l+1$ 就说明无解。

正确性：[（真·感性地证明）](https://www.luogu.com.cn/paste/4nv0nnmi)

具体见代码：

```cpp
int main()
{
	int T=read();
	while(T--){
		int n=read();
		int l=read();
		int r=read();
		int s=read();
		int len=r-l+1,L=l;//len:还要选多少个数字 
		mn[0]=mx[0]=0;
		for(int i=1;i<=n;i++){//mn,mx表示在n中选i个数之和最小/最大值 
			mn[i]=(i+1)*i/2;
			mx[i]=(n+n-i+1)*i/2;
		}
		for(int i=1;i<=n;i++)v[i]=0;//v: 标记已选的数 
		for(int i=1;i<=n;i++)//枚举选择的数，并更新s，len，a。a:最终的答案 
			if(s-i>=mn[len-1]&&s-i<=mx[len-1]){
				a[l++]=i;len--;s-=i;v[i]=1;
			}
		if(l!=r+1){cout<<-1<<"\n";continue;}//无解 
		tot=0;
		for(int i=1;i<=n;i++)//将没有选的数依次填
			if(!v[i]){if(tot==L-1)tot=r;a[++tot]=i;}
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：3)

## 题意

一句话题意：$T$ 组数据，每组数据由互相独立的 $n,l,r,s$ 组成，求 $\{a\}$，$\{a\}$ 是 $1$ 到 $n$ 的一个排列使得 $\sum_{i = l}^ra_i = s$，并输出这个排列，如果无法找到这样的排列输出 `-1`。

## 分析

这是这场比赛的又双叒叕的一道构造题，还是那句话，构造题中不用把所有东西的完美的构造出来，只要保证有用的一部分的构造就行了。

考虑这道题：$l$ 和 $r$ 的位置无所谓，只要关注 $r - l + 1$ 的长度就行了，转换成满足 $\sum_{i=1}^{r-l+1}=s$。

考虑令 $m = r - l + 1$，然后构造长度为 $m$ 的子序列，先让 $\{a_1 = 1,a_2 = 2,\cdots,a_m = m\}$，然后贪心的想法，只要满足 $(\sum_{i = 1}^m a_i) + n - m \le s$，就将 $\{a\}$ 中未被修改过的部分的最大值定义为 $\max\{a\}$， 将 $\max\{a\}$ 修改成 $\max(x)(x\in\{b\}, x\not\in\{a\})$，使之后不会再有修改这个值的情况， 剩下的不满足 $(\sum_{i = 1}^m a_i) + n - m \le s$ 的一点零头做个减法就行了。最后要记得将几种不可能满足的情况判断一下，这个代码里面会有注释。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 505;

int T;
int N, L, R, S;
int A[maxn], now;
bool vis[maxn];

int main () {
	cin >> T;
	while (T--) {
		cin >> N >> L >> R >> S;
		memset (vis, 0, sizeof vis);
		for (register int i = L; i <= R; i++)
		A[i] = i - L + 1, vis[A[i]] = true, S -= A[i];
		if (S < 0) {printf ("-1\n"); continue;}
		for (register int i = R; i >= L; i--) {
			if (S >= N - R + L - 1) {
				S -= N - R + L - 1;
				vis[A[i]] = false;
				A[i] += N - R + L - 1;
				vis[A[i]] = true; // 前面的判断，因为没有设 M 所以有点复杂
				continue;
			}
			vis[A[i]] = false;
			A[i] += S; S = 0;
			vis[A[i]] = true;// 这里 vis 多次修改是为了维护那些数字在 {a} 中。
			break;
		}	now = 0;
        // 在前面的循环结束的时候如果有解的话 S 一定为 0。
		if (S != 0) {printf ("-1\n"); continue;}
		for (register int i = 1; i <= N; i++) {
			if (L <= i && i <= R) continue;
			while (vis[++now]); A[i] = now;
		} // 构造其他的数字
		for (register int i = 1; i <= N; i++) printf ("%d%c", A[i], i == N ? '\n' : ' ');
	}
	return 0;
}
```

---

## 作者：haokee (赞：1)

补充一种非贪心的另类 dp 解法。

根据题目，不难发现只有 $l\sim r$ 的数字是有要求的，需要和为 $s$，而其它地方只需要把剩下的数填进去就行了。因此不妨令 $m=r-l+1$，那么就需要在 $1\sim n$ 当中选择 $m$ 个数加起来等于 $s$。

于是，我们便可以将这 $n$ 个数看成 $n$ 个物品，构造出 01 背包。令 $f_{i,j,k}$ 表示为在 $1\sim i$ 当中选择了 $j$ 个不同的数，加起来能否等于 $k$，那么这个数可以由 $n$ 个数转移来，便是 $f_{i,j,k}=\max\limits_{w=1}^n f_{i-1,j-1,k-w}$

但是这个办法需要开 $n\times m\times s$ 的数组，空间复杂度 $\mathcal O(n^4)$，而本题 $n\le 500$，自然会超出内存限制。但是，我们可以通过压数组的手段来讲第一维去掉。因为 $f_i$ 只会依赖 $f_{i-1}$，而 $j$ 这个维度也只会访问 $j-1$，因此我们只需要将 $j$ 倒序枚举即可。

这样做空间能够得到有效的优化，但时间复杂度仍然是 $\mathcal O(n^4)$。考虑优化时间，比如当答案 $f_{m,s}$ 已经计算出来了的时候，就退出 dp。但是最有效的方法还是直接在循环外面判断解是否合法，如果 $1\sim m$ 加起来都比 $m$ 大或者 $n-m+1\sim n$ 加起来都比 $s$ 要小，那么肯定是满足不了条件的，因此直接输出无解。

注意这题需要输出答案，因此 dp 需要记录前驱状态。但是实际上并不用开两个数组，只需要记录当前状态是加了多少就行了。一秒半大常数过题。

```cpp
#include <iostream>
#include <set>

using namespace std;

const int kMaxN = 505, kMaxS = kMaxN * (kMaxN + 1) / 2;

int dp[kMaxN][kMaxS], f[kMaxN], p, t, n, m, l, r, s;
set<int> st;

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> l >> r >> s;
    m = r - l + 1, p = 1;
    if ((n - m + 1 + n) * m / 2 < s || (1 + m) * m / 2 > s) {
      cout << "-1\n";
      continue;
    }
    fill(f + 1, f + n + 1, 0);
    for (int i = 1; i <= m; i++) {
      for (int j = i; j <= s; j++) {
        dp[i][j] = 0;
      }
    }
    dp[0][0] = 1, st.clear();
    for (int i = 1; i <= n; i++) {
      if (dp[m][s]) {
        break;
      }
      for (int j = min(m, i); j >= 1; j--) {
        for (int k = i; k <= min(s, i * (i + 1) / 2); k++) {
          dp[j - 1][k - i] && !dp[j][k] && (dp[j][k] = i);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      st.insert(i);
    }
    for (int i = m, j = s; i; j -= dp[i][j], i--) {
      f[l + i - 1] = dp[i][j];
      st.erase(dp[i][j]);
    }
    for (int i = 1; i <= n; i++) {
      if (f[i]) {
        cout << f[i] << ' ';
      } else {
        cout << *st.begin() << ' ';
        st.erase(st.begin());
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Milthm (赞：1)

## CF1512E 题解

### 前置知识

- 构造

### 题目解法

很明显拿到题目，先想想怎么判断无解。然后我们发现，如果你取一个 $1$ 到 $n$ 的序列中最后 $r-l+1$ 个，加起来仍然小于 $s$，那么一定无法构造出来（因为最大的也达不到 $s$）。

同理，如果 $1$ 到 $r-l+1$ 的数的加和大于了 $s$，也是无法构造出来的。

否则，我们这样去构造：

首先假设构造的序列就是 $1$ 至 $r-l+1$，然后累加一个和。判断一下这个和与 $s$ 相差多少，然后从后面开始一个一个数不断 $+1$，直到加和等于 $s$。

接下来，先将前 $l-1$ 个数正常输出，随后输出改变后那一段的值，最后输出剩下的值，就好了。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int t,n,l,r,s,q[1005],sum,quo;
int main(){
	cin>>t;
	while(t--){
		sum=0;
		cin>>n>>l>>r>>s;
		int len=r-l+1;
		if(s>(n-len+1+n)*len/2||s<(1+len)*len/2){
			cout<<"-1\n";//判断无解
		}
		else{
			for(int i=1;i<=len;++i){
				q[i]=1;//先标记一下
				sum+=i;
			}
			quo=n;
			for(int i=len;sum!=s;--i,--quo){//这个是不停加一的过程
				int syx=i;
				while(sum!=s&&syx<quo){
					q[syx]=0;
					q[++syx]=1;
					sum++;
				}
			}
			quo=0;
			if(l==1)goto R;//特判一下起点位置
			for(int i=1;i<=n;++i){
				if(q[i]==0){
					quo++;
					cout<<i<<" ";//先输出前面的
					q[i]=2; 
					if(quo==l-1)break;
				}
			}
			R:;
			for(int i=1;i<=n;++i){
				if(q[i]==1){
					cout<<i<<" ";//再输出中间的
					q[i]=2;
				}
			}
			for(int i=1;i<=n;++i){
				if(q[i]==0)cout<<i<<" ";//最后输出后面的
				q[i]=0;
			}
			cout<<endl;
		}
	}
	
	return 0;
}
```


---

