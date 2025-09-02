# Equalize by Divide

## 题目描述

给您一个 $a_1,a_2,\dots a_n$ 这样的正整数数组，您可以对它进行多次（可以是零次）这样的操作：
* 选择两个索引 $i,j(1 \leq i,j \leq n,i \neq j)$；
* 将 $a_i$ 赋值为 $\lceil \frac{a_i}{a_j}\rceil$。这里的 $\lceil x \rceil$ 表示将 $x$ 取值到最小的大于等于 $x$ 的整数上。

有可能将通过这样的操作使数组的所有元素相等吗（或许为空）？如果可以，打印任何一种操作次数小于等于 $30n$ 的操作方法。

可以证明，在问题约束下，如果存在让数组所有元素相等的操作方法，那么操作次数最多 $30n$ 次。

## 样例 #1

### 输入

```
10
1
100
3
1 1 1
2
2 1
2
5 5
3
4 3 2
4
3 3 4 4
2
2 100
5
5 3 6 7 8
6
3 3 80 3 8 3
4
19 40 19 55```

### 输出

```
0
0
-1
0
2
1 3
2 1
4
3 1
4 2
1 3
2 4
6
2 1
2 1
2 1
2 1
2 1
2 1
8
5 2
4 2
3 2
1 3
1 3
2 1
4 1
5 1
4
5 1
3 1
3 1
3 1
9
4 2
2 1
1 2
1 2
3 2
3 2
1 4
2 4
3 4```

# 题解

## 作者：SunnyYuan (赞：7)

本蒟蒻学习了[jiangly](https://codeforces.com/profile/jiangly)大佬的思想，来发一个题解。

大致题意：

> 给定一个 $n$ 个元素的数组 $a$，每次可以选择 $a[i]$ 和 $a[j]$，然后使 $a[i] = \lceil \frac{a_i}{a_j} \rceil$，如果最后可以使数组中的所有元素都相等，那么输出`Yes`，并输出每一个操作$i, j$；否则输出`No`。

本人不擅长使用Markdown，详细思路写在代码里面了。

```cpp
// 思路：
// 1. 如果所有数字都相等，那么什么也不用干。
// 接下来的所有判断都假定所有数字不相等
// 2. 如果数组中有1，一定不可行，因为任何数字除以它还是它自己，用1除以任何数字却还是1，所以数组中有了1，就妄图改变数组中的任何一个数字。
// 3. 固定a[1], 不断地用别的数字a[i]和a[1]如以下方式操作，直到整个数组变为a[1]或者出现了2。
//	3. 1. 如果a[1] < a[i]，那么a[1] = a[1] / a[i] 上取整。
//	3. 2. 否则，a[i] = a[i] / a[1] 上取整。
// 4. 如果，整个数组变为a[1]，直接输出当前处理的步骤。
// 5. 否则，就将数组中不是2的元素，一个一个与2进行操作，再输出所有步骤。

// C++新语法：
// count(a, b, c) (a, b)的区间内c的个数
// find(a, b, c) 在(a, b)区间内找c并返回其指针

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;

const int N = 110;

int n;
int a[N];
PII ans[N * 35];
int cnt;

void solve() {
	cnt = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	if (count(a + 1, a + n + 1, a[1]) == n) {
		cout << 0 << '\n';
		return;
	}
	
	if (count(a + 1, a + n + 1, 1) >= 1) {
		cout << -1 << '\n';
		return;
	}
	
	while (count(a + 1, a + n + 1, a[1]) < n && count(a + 1, a + n + 1, 2) == 0) {
		int pos = 2;
		while (a[pos] == a[1]) {
			pos++;
		}
		
		if (a[pos] > a[1]) {
			if (a[pos] % a[1]) a[pos] = a[pos] / a[1] + 1;
			else a[pos] = a[pos] / a[1];
			ans[++cnt] = {pos, 1};
		}
		else {
			if (a[1] % a[pos]) a[1] = a[1] / a[pos] + 1;
			else a[1] = a[1] / a[pos];
			ans[++cnt] = {1, pos};
		}
	}
	
	if (count(a + 1, a + n + 1, a[1]) < n) {
		int pos2 = find(a + 1, a + n + 1, 2) - a;
		for (int i = 1; i <= n; i++) {
			while (a[i] != 2) {
				if (a[i] & 1) a[i] = a[i] / 2 + 1;
				else a[i] = a[i] / 2;
				ans[++cnt] = {i, pos2};
			}
		}
	}
	
	cout << cnt << '\n';
	for (int i = 1; i <= cnt; i++) cout << ans[i].first << ' ' << ans[i].second << '\n';
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

## 作者：yimuhua (赞：6)

## 题意

定义一次操作为选定两个下标 $i,j\ (i\ne j)$，将 $a_i$ 变为 $\left\lceil\dfrac{a_i}{a_j}\right\rceil$，问是否能将序列中所有数变得相等，输出方案。

## 思路

首先判断每个数是否已经相等，若是则输出 $0$。

然后判断无解，显然若序列中有 $1$ 则无解。

剩下的情况必然有解，因为显然当序列不完全相等时，每次可以将最大值与最小值进行操作。

#### 证明：

设最小值为 $x$，则最大值在与最小值操作后的值最小时为 $x+1$。

$\because \left\lceil\dfrac{x+1}{x}\right\rceil=2$

$\therefore$ 每次都可以完成操作

$\therefore$ 有解

#### 证毕。

时间复杂度为 $O(n^2\log V)$，$V$ 为 $a$ 的值域。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
	int x, y;
};
vector<node> ans;
int t, n, a[105];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--) {
		cin >> n, ans.clear();
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		if(*min_element(a + 1, a + n + 1) == *max_element(a + 1, a + n + 1)) {
			cout << "0\n";
			continue;
		}
		if(*min_element(a + 1, a + n + 1) == 1) {
			cout << "-1\n";
			continue;
		}
		while(*min_element(a + 1, a + n + 1) != *max_element(a + 1, a + n + 1)) {
			int p = min_element(a + 1, a + n + 1) - a, x = a[p];
			for(int i = 1; i <= n; i++)
				if((a[i] - 1) / x + 1 > 1)
					a[i] = (a[i] - 1) / x + 1, ans.push_back((node){i, p});
		}
		cout << ans.size() << '\n';
		for(auto i : ans)
			cout << i.x << ' ' << i.y << '\n';
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：3)

**Solution**

如果 $\min(a) = 1$，那么：

+ 如果 $a_1=a_2=a_3=\ldots=a_n=1$，那么不用进行任何操作。
+ 否则，无法对于每一个大于 $1$ 的 $a_i$ 执行操作使他变成 $1$。

否则，必然有 $\min(a)>1$：

+ 如果 $a_1=a_2=a_3=\ldots=a_n$，那么不用执行任何操作。
+ 否则，我们可以选择 $a$ 数组中最大的元素为 $i$，最小的元素为 $j$，执行一次操作，循环上面的步骤，一直到 $a_1=a_2=a_3=\ldots a_n$ 为止。

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定长度为 $n$ 的序列，每次操作从序列中选出两个的数 $i,j$，使 $a_i=\left\lceil \frac{a_i}{a_j}\right\rceil$。请你构造一组操作方案，让序列中的所有数相等。若不行，输出 ```-1```。

### 题目分析：

我们考虑一种构造策略，每次按元素大小对序列进行排序，让每个数不断去除排序后序列第一个数，直到这个数**小于等于**第一个位置的数。不断重复这种操作，直到序列中每个数相等为止。

当然，无解的情况就是当且仅当序列中存在 $1$ 时。当然，序列中全是 $1$ 或者只有一个数是两种特殊情况。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;int n;
const int N=110;
struct node{int x,id;};
node a[N];
pair<int,int> st[N<<5];int tp=0;
bool cmp(const node &x,const node &y){return x.x<y.x;}
bool check1(){
	bool flag=false;
	for(int i=1;i<=n;i++)
		if(a[i].x!=1){
			flag=true;
			break;
		}
	if(!flag){
		puts("0");
		return false;
	}
	for(int i=1;i<=n;i++)
		if(a[i].x==1){
			puts("-1");
			return false;
		}
	return true;
}int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);tp=0;
		for(int i=1;i<=n;i++){scanf("%d",&a[i].x);a[i].id=i;}
		if(n==1){puts("0");continue;}
		if(!check1()) continue;
		while(true!=false){
			sort(a+1,a+n+1,cmp);bool flag=false;
			for(int i=2;i<=n;i++){
				if(a[i].x>a[1].x) flag=true;
				while(a[i].x>a[1].x){
					st[++tp]={a[i].id,a[1].id};
			//	printf("%d %d\n",i,1);
					a[i].x=ceil(1.0*a[i].x/a[1].x);
				}
			}if(!flag) break;
		}
		printf("%d\n",tp);
		for(int i=1;i<=tp;i++)
			printf("%d %d\n",st[i].first,st[i].second);
	}return 0;
}
```

---

