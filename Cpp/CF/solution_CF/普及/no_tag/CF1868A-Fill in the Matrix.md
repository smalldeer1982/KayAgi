# Fill in the Matrix

## 题目描述

There is an empty matrix $ M $ of size $ n\times m $ .

Zhongkao examination is over, and Daniel would like to do some puzzle games. He is going to fill in the matrix $ M $ using permutations of length $ m $ . That is, each row of $ M $ must be a permutation of length $ m^\dagger $ .

Define the value of the $ i $ -th column in $ M $ as $ v_i=\operatorname{MEX}(M_{1,i},M_{2,i},\ldots,M_{n,i})^\ddagger $ . Since Daniel likes diversity, the beauty of $ M $ is $ s=\operatorname{MEX}(v_1,v_2,\cdots,v_m) $ .

You have to help Daniel fill in the matrix $ M $ and maximize its beauty.

 $ ^\dagger $ A permutation of length $ m $ is an array consisting of $ m $ distinct integers from $ 0 $ to $ m-1 $ in arbitrary order. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,1,3] $ is also not a permutation ( $ m-1=2 $ but there is $ 3 $ in the array).

 $ ^\ddagger $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, $ \operatorname{MEX}(2,2,1)=0 $ because $ 0 $ does not belong to the array, and $ \operatorname{MEX}(0,3,1,2)=4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ appear in the array, but $ 4 $ does not.

## 说明/提示

In the first test case:

- $ v_1=\operatorname{MEX}(1,0,1,0)=2 $ ;
- $ v_2=\operatorname{MEX}(0,2,0,2)=1 $ ;
- $ v_3=\operatorname{MEX}(2,1,2,1)=0 $ .

Therefore, $ s=\operatorname{MEX}(2,1,0)=3 $ .

It can be shown that $ 3 $ is the maximum possible beauty of $ M $ .

In the second test case, any permutation will make $ s=2 $ .

In the third test case:

- $ v_1=\operatorname{MEX}(3,5,1,4,4,2)=0 $ ;
- $ v_2=\operatorname{MEX}(0,2,3,1,2,4)=5 $ ;
- $ v_3=\operatorname{MEX}(1,1,2,3,5,0)=4 $ ;
- $ v_4=\operatorname{MEX}(4,0,4,2,3,5)=1 $ ;
- $ v_5=\operatorname{MEX}(2,4,5,5,0,1)=3 $ ;
- $ v_6=\operatorname{MEX}(5,3,0,0,1,3)=2 $ .

Therefore, $ s=\operatorname{MEX}(0,5,4,1,3,2)=6 $ .

## 样例 #1

### 输入

```
4
4 3
1 16
6 6
2 1```

### 输出

```
3
1 0 2
0 2 1
1 0 2
0 2 1
2
14 7 15 4 10 0 8 6 1 2 3 5 9 11 12 13 
6
3 0 1 4 2 5 
5 2 1 0 4 3 
1 3 2 4 5 0 
4 1 3 2 5 0 
4 2 5 3 0 1 
2 4 0 5 1 3
0
0
0```

# 题解

## 作者：SunnyYuan (赞：12)

## 前言

感谢 @Ziqqurat 发现错别字。

## 思路

### 情况 1

如果 $m \le n$，那么一定能构造出答案为 $m$ 的数组。

我们让每一列凑出来的 $\text{MEX}$ 合在一起为 $0 \sim m - 1$ 即可，这样整个数组可以凑出来的 $\text{MEX}$ 就为 $m$ 了。

我们可以让 $0 \sim m$ 组成一个长度为 $m + 1$ 的数组，然后不断循环：

比如 $m = 5$：

原始数组：$0, 1, 2, 3, 4$

不断循环：

$0, 1, 2, 3, 4$

$1, 2, 3, 4, 0$

$2, 3, 4, 0, 1$

$3, 4, 0, 1, 2$

$4, 0, 1, 2, 3$

然后我们将这一行行数字塞到每一列中（从第二个数字开始），将第一个数字看成 $\text{MEX}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/eekbfpre.png)

如果 $n$ 行没有装满，我们就可以随便复制前面的一行。

将最上面一行的 $\text{MEX}$ 再求 $\text{MEX}$，就可以得到最终答案 $m$。

## 情况 2

如果 $m > n$，那么我们就可以凑出 $\text{MEX}$ 为 $n + 1$。

一样的，我们构造一个 $0 \sim n + 1$ 的长度为 $n + 2$ 的数组，然后不断循环。

![](https://cdn.luogu.com.cn/upload/image_hosting/rll3kwah.png)

将最上面一行的 $\text{MEX}$ 再求 $\text{MEX}$，就可以得到最终答案 $n + 1$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;

void solve() {
	cin >> n >> m;
	if (m == 1) {
		cout << "0\n";
		for (int i = 1; i <= n; i++) cout << "0\n";
		return;
	}
	if (n == 1) {
		cout << "2\n";
		for (int i = 0; i < m; i++) cout << i << ' ';
		cout << '\n';
		return;
	}
	vector<vector<int> > a(n + 1);
	for (int i = 0; i <= n; i++) {
		for (int j = -1; j < m; j++) {
			a[i].push_back(j);
	    }
	}
	if (n < m) {
		for (int j = 1; j <= n + 1; j++) {
			for (int i = 0, st = j; i <= n; i++, st++) {
				a[i][j] = st % (n + 1);
			}
		}
		cout << n + 1 << '\n';
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << a[i][j] << ' ';
			}
			cout << '\n';
		}
	}
	else {
		for (int j = 1; j <= m; j++) {
			for (int i = 0, st = j; i < m; i++, st++) {
				a[i][j] = st % m;
			}
		}
		cout << m << '\n';
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << a[min(i, m - 1)][j] << ' ';
			}
			cout << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 0: 题面翻译
> 注：这个翻译为机翻，仅供读者理解

有一个大小为 $n\times m$ 的空矩阵 $M$。

中考结束了，丹尼尔想做一些益智游戏。他要用长度为 $m$ 的排列填入矩阵 $M$。也就是说，$M$ 的每一行都必须是长度为 $m^\dagger$ 的排列。

将 $M$ 中第 $i$ 列的值定义为 $v_i=\operatorname{MEX}(M_{1,i},M_{2,i},\ldots,M_{n,i})^\ddagger$。因为丹尼尔喜欢多样性，所以 $M$ 的美丽程度是 $s=\operatorname{MEX}(v_1,v_2,\cdots,v_m)$。

你必须帮助丹尼尔填入矩阵 $M$ ，并**最大化**它的美丽程度。

$^\dagger$ 长度为 $m$ 的排列是一个由$m$个不同的整数组成的数组，这些整数从 $0$ 到 $m-1$ 依次排列。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是一个排列（$1$ 在数组中出现了两次），$[0,1,3]$ 也不是一个排列（$m-1=2$ 但在数组中有 $3$）。

$^\ddagger$ 数组的 $\operatorname{MEX}$ 是不属于数组的最小非负整数。例如，$\operatorname{MEX}(2,2,1)=0$ 是因为 $0$ 不属于数组，而 $\operatorname{MEX}(0,3,1,2)=4$ 是因为 $0$、$1$、$2$ 和 $3$ 出现在数组中，但 $4$ 不属于数组。

## Part 1：主要思路
我们考虑对整个矩阵进行构造。

首先我们先考虑一个最简单的情况：$n=m-1$ 的情况（具体为什么是 $n=m-1$，因为对于每一列，我们既然要求它的 $\operatorname{MEX}$，那么我们就每列就必须少一个数字（也就是这一列的 $\operatorname{MEX}$），所以我们考虑 $n=m-1$ 的情况）。

例如，当 $n = 4$，$m = 5$ 时，我们考虑让第 $i$ 列的 $\operatorname{MEX}$ 等于 $i-1$，不难发现，我们可以构造出一个答案为 $5$ 的情况：
```
1 2 3 4 0 
2 3 4 0 1 
3 4 0 1 2 
4 0 1 2 3 
```
同时，我们也可以发现，当 $n$ 和 $m$ 中只有一个数扩大的时候，这种情况仍然是最优解。

那么这个时候，问题也就迎刃而解了，当 $n \leq m-1$ 时，我们先构造出大小为 $(n,n+1)$ 的矩阵，接着剩下的列，对于第 $i$ 列，将所有的数填上 $i-1$ 即可。

而当 $n > m-1$ 时，我们先构造出大小为 $(m-1,m)$ 的矩阵，接着剩下的行，填入和第一行一样的数字即可。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n, m;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> m; // 输入
        if(m == 1){ // 记得特判一下 m = 1 的情况
            cout << 0 << endl;
            for(int i = 1; i <= n; i++){
                cout << 0 << endl;
            }
            continue;
        }
        if(m >= n + 1){ // 第一种情况
            cout << n + 1 << endl; // 先输出答案
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n + 1; j++){
                    cout << (i + j - 1) % (n + 1) << " ";
                } // 输出我们构造出来的矩阵
                for(int j = n + 2; j <= m; j++){
                    cout << j - 1 << " ";
                } // 接着把剩下的列补上
                cout << endl;
            }
        }else{ // 第二种情况
            cout << m << endl;
            int n0 = n;
            n = m - 1;
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n + 1; j++){
                    cout << (i + j - 1) % (n + 1) << " "; // 先输出构造出的矩阵
                }
                cout << endl;
            }
            for(int i = n + 1; i <= n0; i++){
                for(int j = 1; j <= m; j++){
                    cout << j % m << " ";
                }
                cout << endl;
            } // 再把最后几行填上
        }
    }
    return 0;
}
```


---

