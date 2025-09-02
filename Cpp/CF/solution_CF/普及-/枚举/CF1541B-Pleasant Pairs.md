# Pleasant Pairs

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ consisting of $ n $ distinct integers. Count the number of pairs of indices $ (i, j) $ such that $ i < j $ and $ a_i \cdot a_j = i + j $ .

## 说明/提示

For the first test case, the only pair that satisfies the constraints is $ (1, 2) $ , as $ a_1 \cdot a_2 = 1 + 2 = 3 $

For the second test case, the only pair that satisfies the constraints is $ (2, 3) $ .

For the third test case, the pairs that satisfy the constraints are $ (1, 2) $ , $ (1, 5) $ , and $ (2, 3) $ .

## 样例 #1

### 输入

```
3
2
3 1
3
6 1 5
5
3 1 5 9 2```

### 输出

```
1
1
3```

# 题解

## 作者：itisover (赞：16)

在暴力的基础上可以先把a数组从小到大排序，然后在枚举 $i,j$ 时加上 $a_i \times a_j<=2n$ 的条件，就可以了。

相当于只枚举 $i,j$ 满足 $a_i\times a_j<=2n$ 的情况。

为什么呢？因为满足 $a_i\times a_j<=2n$ 的 $(i,j)$ 个数最多有 $nlogn$ 个。

又为什么呢？因为当枚举了一个 $i$ 时，$j$ 就有 $\frac{2n}{a_i}$ 种可能，最坏就是 $\frac{2n}{1}+\frac{2n}{2}+\frac{2n}{3}+...+\frac{2n}{n}=2n\times (\frac{1}{1}+\frac{1}{2}+\frac{1}{3}+...+\frac{1}{n})$ 看出是调和级数，所以时间复杂度为 $O(nlogn)$ 可以过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T;
int a[N],b[N];
void solve(){
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
	cin>>a[i];
	b[a[i]]=i;
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n&&a[i]*a[j]<=2*n;j++){
	    if(a[i]*a[j]==b[a[i]]+b[a[j]]) ans++;
	}
    }
    cout<<ans<<endl;
}
signed main(){
    cin>>T;
    while(T--){
	solve();
    }
    return 0;
}
```



---

## 作者：Acc_Robin (赞：4)

#### 题意

给你一个长度为 $n$ 的序列，且元素两两不同，你需要求出满足 $i<j$ 且 $i+j=a_i\cdot a_j$ 的数对个数。

$n\le 10^5 , 1\le a_i \le 2n $

多组数据，$\sum n \le 2\times 10^5$

#### 题解

注意到，$i<j$ 的限制相当于没有，又注意到元素两两不同，并且值域很小，所以考虑开个桶，桶中存储一个值对应的下标。

我们记这个桶为 $b$，那么 $b_i$ 表示原序列中值为 $i$ 的数的在原序列中的下标。

那么在桶 $b$ 中，问题就转化成了 $ij=b_i+b_j$ 的数对的个数。

我们发现，$ij=b_i+b_j\le 2n$，也就是说，我们从 $1\sim n$ 枚举一个 $i$，再枚举 $j$，注意这里 $j$ 的上界就是 $\lfloor\frac{2n}{i}\rfloor$，那么复杂度就是

$$
2n+\frac{2n}{2}+\frac{2n}{3}+\cdots=O(n\log m 
)
$$

#### 复杂度分析

时间复杂度就是 $O(n\log m)$，其中 $m$ 为值域。

空间复杂度为 $O(n+m)$。

#### 代码实现

这个代码很好写，注意多组数据要清零。

```cpp
```#include<bits/stdc++.h>
using namespace std;
namespace Acc{
#define int long long
    const int N = 1e6+10;
    int a[N],b[N],n,m,r;
    void work(){
        cin>>n,r=m=0;
        for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]=i,m=max(m,a[i]);
        for(int i=1;i<=m;i++)if(b[i])for(int j=i+1;j<=m && i*j<=2*n;j++)if(b[j] && i*j==b[i]+b[j])r++;
        for(int i=1;i<=n;i++)b[a[i]]=0;
        cout<<r;
    }
#undef int
}
int main(){
	int T;
	for(cin>>T;T--;puts(""))Acc::work();
}

---

## 作者：LinkZelda (赞：3)

- **题意**：

$t$ 组询问，每次给定一个长度为 $n$ 的序列，序列中的数两两不同，求满足 $i<j,a_i\times a_j=i+j$ 的数对 $(i,j)$ 个数。

$1\leq t\leq 10^4,2\leq n\leq10^5,\sum n\leq 2\times 10^5$。
$1\leq a_i\leq 2\times n$，$a_i$ 两两不同。

- **做法**：

考虑暴力，直接对于每一个位置的数统计答案，但是这样是 $O(n^2)$ 的。

我们定义 $k_i=\left\lfloor \frac{2\times n}{a_i}\right\rfloor$ ，容易发现 $\forall i,j,i+j\leq 2\times n$ ，那么对于每个 $a_i$ ，可能对答案产生贡献的只有值 $\leq k_i$ 的位置。

所以我们可以开一个桶记录每个值所在的位置，然后直接对于每个位置统计值$\leq k_i$ 的答案，由调和级数的结论，时间复杂度为 $O(\sum_{i=1}^n\left\lfloor \frac{2\times n}{a_i}\right\rfloor)=O(n\log n)$。

- [代码](https://www.luogu.com.cn/paste/xrkhd9r0)

---

## 作者：_Veritas (赞：2)

将原式 $i+j=a_i \cdot a_j$ 变形为 $a_j=\frac{i+j}{a_i}$ .

于是$(i,j)$为Pleasant Pairs的必要条件是 $a_i \mid i+j$

考虑先枚举 $i$ ，然后枚举 $j$ 并保证 $a_i \mid i+j$ 。

代码：
```cpp
for(int i=1;i<=n;++i)
	for(int j=a[i]-i;j<=n;j+=a[i]){
    	if(i>=j) continue;
        if(1ll*a[i]*a[j]==0ll+i+j) ++cnt;
    }
```

由于元素互不相同 可以证明时间复杂度为 $O(n\log n)$

---

## 作者：Temperature_automata (赞：2)

楼下大佬的题解仍有需要修改的地方，这里我来为大家讲解一下

不难发现 $i+j<2 \ast n$ （很多大佬错在这里，这里不能取等，因为$i<j$）

因为 $a_i \ast a_j=i+j$

所以 $a_i \ast a_j<2 \ast n$

所以 $a_j<2 \ast n/a_i$

可以开一个桶存储每个 $a_i$ ，然后枚举 $a_j$ 的范围

那么为什么各位大佬加等的程序也能过呢？

那是因为数据中没有 $2 \ast n/a_i$ 可以整除的数据。

如果不能整除，那么向下取整后的值也是可以取到的。

正确的代码如下：

```cpp
// Problem: B. Pleasant Pairs
// Contest: Codeforces - Codeforces Round #728 (Div. 2)
// URL: https://codeforces.com/contest/1541/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>

using namespace std ;

const int maxn = 2e5+5 ;
int a[maxn] ;
int T ;
int b[maxn] ;
  
int main ( ) {
  ios::sync_with_stdio(false) ;
	cin >> T ;
	while(T--) {
		int n ;
		cin >> n ;
		for ( int i = 1 ; i <= 2*n ; i ++ ) {
			b[i]=0;
		}
		for ( int i = 1 ; i <= n ; i ++ ) {
			cin >> a[i] ;
		}
		
		/*
			不难发现i+j<2*n
			则因为ai*aj=i+j
			所以ai*aj<2*n
			所以aj<2*n/ai
			可以开一个桶存
		*/
		
		int ans = 0 ;
		
		for ( int i = 1 ; i <= n ; i ++ ) {
			if(int(2*n/a[i])*a[i]==2*n) {
				for ( int j = 1 ; j < 2*n/a[i] ; j ++ ) {
					if(b[j]&&i!=b[j]&&i+b[j]==a[i]*j)
						ans ++ ;
				}
				b[a[i]]=i;//没有重复数值，可以利用桶来储存数值对应的编号
			}
			else {
				for ( int j = 1 ; j <= (2*n/a[i]) ; j ++ ) {/*2*n/a[i]向下取整需要取等*/
					if(b[j]&&i!=b[j]&&i+b[j]==a[i]*j)
						ans ++ ;
				}
				b[a[i]]=i;//没有重复数值，可以利用桶来储存数值对应的编号
			}
		}
		
		cout << ans << endl ;
	
	}
  return 0 ;
}

```

---

