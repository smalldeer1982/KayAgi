# 题目信息

# Subtract Operation

## 题目描述

You are given a list of $ n $ integers. You can perform the following operation: you choose an element $ x $ from the list, erase $ x $ from the list, and subtract the value of $ x $ from all the remaining elements. Thus, in one operation, the length of the list is decreased by exactly $ 1 $ .

Given an integer $ k $ ( $ k>0 $ ), find if there is some sequence of $ n-1 $ operations such that, after applying the operations, the only remaining element of the list is equal to $ k $ .

## 说明/提示

In the first example we have the list $ \{4, 2, 2, 7\} $ , and we have the target $ k = 5 $ . One way to achieve it is the following: first we choose the third element, obtaining the list $ \{2, 0, 5\} $ . Next we choose the first element, obtaining the list $ \{-2, 3\} $ . Finally, we choose the first element, obtaining the list $ \{5\} $ .

## 样例 #1

### 输入

```
4
4 5
4 2 2 7
5 4
1 9 1 3 4
2 17
17 0
2 17
18 18```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

### 题目内容
# 减法操作

## 题目描述
给定一个包含 $n$ 个整数的列表。你可以执行以下操作：从列表中选择一个元素 $x$，将其从列表中删除，并从其余所有元素中减去 $x$ 的值。因此，每次操作后，列表的长度恰好减少 $1$。

给定一个整数 $k$（$k > 0$），判断是否存在某种由 $n - 1$ 次操作组成的序列，使得在应用这些操作后，列表中唯一剩下的元素等于 $k$。

## 说明/提示
在第一个示例中，我们有列表 $\{4, 2, 2, 7\}$，目标值 $k = 5$。一种实现方式如下：首先我们选择第三个元素，得到列表 $\{2, 0, 5\}$。接下来，我们选择第一个元素，得到列表 $\{-2, 3\}$。最后，我们选择第一个元素，得到列表 $\{5\}$。

## 样例 #1
### 输入
```
4
4 5
4 2 2 7
5 4
1 9 1 3 4
2 17
17 0
2 17
18 18
```
### 输出
```
YES
NO
YES
NO
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是发现经过一系列操作后，列表中任意两个数的差始终保持不变，所以问题转化为判断列表中是否存在两个数的差为 $k$。不同题解在具体实现判断这一步时采用了不同方法，有的使用排序加双指针，有的使用二分查找，有的使用 `map` 或 `set` 数据结构。

### 所选的题解
- **作者：qifan_maker (5星)**
    - **关键亮点**：思路清晰，先分析出操作中数的差不变这一关键规律，将问题转化为判断是否存在差为 $k$ 的数对，针对暴力枚举 $O(n^2)$ 复杂度会超时的难点，提出用 `map` 存储数字出现次数来优化，时间复杂度降为 $\mathcal{O}(n\log n)$，代码简洁明了。
    - **重点代码核心实现思想**：使用 `map` 记录数组中每个数字，遍历数组时检查 `map` 中是否存在当前数字加上 $k$ 的数，若存在则说明有差为 $k$ 的数对。
```c++
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,a[200100];
map<long long,long long> buc;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		cin >> n >> k;
		buc.clear();
		for (int i=1;i<=n;i++){
			cin >> a[i];
			buc[a[i]]=1;
		}
		bool flag=false;
		for (int i=1;i<=n;i++){
			if (buc[a[i]+k]){
				flag = true;
			}
		}
		if (flag){
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```
- **作者：0xFF (4星)**
    - **关键亮点**：同样准确抓住操作中数的相对差距不变这一要点，采用排序加双指针的方法来寻找差为 $k$ 的数对，代码实现较为直观。
    - **重点代码核心实现思想**：先对数组排序，然后用双指针 $i$ 和 $j$，根据 $a[i] + abs(k)$ 与 $a[j]$ 的大小关系移动指针，判断是否存在差为 $k$ 的数对。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#define int long long
using namespace std;
const int N = 200050;
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
		int n = read(), k = read();
		for(int i=0;i<n;i++){
			a[i] = read();
		}
		bool ans = false;
		if(n == 1) ans = (a[1] == k);
		else{
			sort(a,a+n);
			int i = 0, j = 1;
			while(j < n && i < n){
				if(a[i] + abs(k) == a[j]){
					ans = true;
					break;
				}
				else if(a[i] + abs(k) < a[j]) i++;
				else j++;
			}
		}
		if(ans == true){
			printf("YES\n");
		}
		else printf("NO\n");
	}
	return 0;
}
```
- **作者：Disjoint_cat (4星)**
    - **关键亮点**：通过对 $n$ 较小时的情况进行模拟，推导出最终结果是两个数的差这一结论，然后利用类似 “A - B数对” 的解法（二分查找）将时间复杂度优化到 $O(n\log n)$。
    - **重点代码核心实现思想**：先对数组排序，然后遍历数组，对于每个元素 $a[i]$，利用二分查找的思想找到第一个大于等于 $a[i] + k$ 的元素 $a[p]$，判断 $a[p]$ 是否等于 $a[i] + k$ 来确定是否存在差为 $k$ 的数对。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,k,a[200005],p;
bool ok;
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+n+1);ok=0,p=1,a[n+1]=1000000000000000;
		for(int i=1;i<=n;i++)
		{
			while(a[p]<a[i]+k)++p;
			if(a[p]==a[i]+k)
			{
				ok=1;
				break;
			}
		}
		printf("%s\n",(ok?"YES":"NO"));
	}
	return 0;
}
```

### 最优关键思路或技巧
发现操作过程中列表内任意两个数的差不变这一数学规律，将原复杂的操作问题转化为简单的判断是否存在差为 $k$ 的数对问题。在实现判断时，利用 `map`、排序加双指针、二分查找等方法优化时间复杂度。

### 拓展思路
此类题目属于通过模拟操作找规律，进而转化问题的类型。类似题目通常需要对给定操作进行分析，挖掘操作过程中不变的量或规律，从而简化问题。例如一些涉及数组元素变换，最后求特定结果的题目，都可以尝试从操作规律入手。

### 相似知识点洛谷题目
- [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)：同样是在数组中寻找差为特定值的数对问题，与本题思路类似。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：需要通过分析操作找到规律，将问题简化后求解。
- [P3957 跳房子](https://www.luogu.com.cn/problem/P3957)：通过对题目条件的分析转化，利用二分查找等方法解决问题，与本题分析问题并优化解法的思路类似。 

---
处理用时：61.43秒