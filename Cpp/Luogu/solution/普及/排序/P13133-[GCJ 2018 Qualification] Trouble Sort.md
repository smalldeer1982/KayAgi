# [GCJ 2018 Qualification] Trouble Sort

## 题目描述

在 Code Jam 的秘密算法实验室里，我们花费了无数小时，致力于解决当今最复杂的问题之一：高效地将一个整数序列按非递减顺序排序。我们仔细研究了经典的冒泡排序算法，并很高兴地宣布一种新变体。

标准冒泡排序算法的基本操作是检查一对相邻的数字，如果左边的数字大于右边的数字，则交换这对数字。而我们的算法会检查一组三个相邻的数字，如果最左边的数字大于最右边的数字，就将整个三元组反转。由于我们的算法是“三元组冒泡排序”，我们将其简称为 Trouble Sort。

```
  TroubleSort(L): // L 是一个从 0 开始编号的整数列表
    let done := false
    while not done:
      done = true
      for i := 0; i < len(L)-2; i++:
        if L[i] > L[i+2]:
          done = false
          reverse the sublist from L[i] to L[i+2], inclusive
```

例如，对于 $L = 5\ 6\ 6\ 4\ 3$，Trouble Sort 的执行过程如下：

- 第一轮：
    - 检查 $5\ 6\ 6$，无需操作：$5\ 6\ 6\ 4\ 3$
    - 检查 $6\ 6\ 4$，发现 $6 > 4$，反转三元组：$5\ 4\ 6\ 6\ 3$
    - 检查 $6\ 6\ 3$，发现 $6 > 3$，反转三元组：$5\ 4\ 3\ 6\ 6$
- 第二轮：
    - 检查 $5\ 4\ 3$，发现 $5 > 3$，反转三元组：$3\ 4\ 5\ 6\ 6$
    - 检查 $4\ 5\ 6$，无需操作：$3\ 4\ 5\ 6\ 6$
    - 检查 $5\ 6\ 6$，无需操作：$3\ 4\ 5\ 6\ 6$
- 第三轮检查所有三元组均无需操作，算法终止。

我们原本期待在夏威夷举办的排序特别兴趣小组会议上展示 Trouble Sort，但我们的一个实习生刚刚指出了一个问题：Trouble Sort 可能无法正确地对序列进行排序！例如，考虑序列 $8\ 9\ 7$。

我们需要你的帮助来进一步研究。给定一个长度为 $\mathbf N$ 的整数序列，判断 Trouble Sort 是否能将该序列正确地按非递减顺序排序。如果不能，请在算法结束后找出第一个排序错误的位置（从 0 开始计数）：即第一个比其后一个数大的数的下标。

## 说明/提示

**样例解释**

样例 Case #1 与题目描述中的第一个例子类似。Trouble Sort 能正确排序该序列，因此输出 ok。

样例 Case #2 是题目描述中的第二个例子。Trouble Sort 无法正确排序该序列，最终结果为 $7\ 9\ 8$。$9$ 是第一个比下一个数大的数，因此第一个排序错误的下标为 $1$。

**数据范围**

- $1 \leq T \leq 100$。
- 对所有 $i$，$0 \leq V_i \leq 10^9$。

**测试点 1（8 分，可见）**

- $3 \leq N \leq 100$。
- 整个测试点的时间限制：10 秒。

**测试点 2（15 分，隐藏）**

- $3 \leq N \leq 10^5$。
- 整个测试点的时间限制：20 秒。

**特别说明**

注意，本题的测试点 2 输入量很大，因此使用非缓冲输入可能导致读取速度较慢。此外，请注意某些编程语言默认的输入缓冲区较小。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
5 6 8 4 3
3
8 9 7```

### 输出

```
Case #1: OK
Case #2: 1```

# 题解

## 作者：chinazhanghaoxun (赞：1)

# P13133 Trouble Sort - Solution

## Problem Statement

给定一个整数序列 $V$，现在对 $V$ 中的每一组 $V_i$ 和 $V_{i+2}$ 进行排序操作，其中 $i\in [1,n-2]$。

问按照这个方式排序出来的序列是否有序，如果无序，求出第一个错误的下标 $i$。

## Analysis

不难发现，这样的排序方法其实就是分别将奇数下标的元素排序，偶数下标的元素排序，我们只需要判断是否会产生冲突就可以了。

## Approach

读入时直接分别加入到 $odd$ 和 $even$ 两个数组，分别排序，然后再合并到同一个数组中。要考虑 $N$ 的奇偶性，注意细节。然后判断这是否是一个顺序正确的序列即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	cin>>t;
	for(int cs=1;cs<=t;cs++){
		vector<int> a,b; 
		cin>>n;
		a.push_back(-1); //用于占位 
		b.push_back(-1);
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			if(i%2) a.push_back(x); //奇数下标给 a 
			else b.push_back(x); //偶数下标给 b 
		}
		sort(a.begin(),a.end()); //分别排序 
		sort(b.begin(),b.end());
		vector<int> c;
		for(int i=1;i<=n/2;i++){ //合并操作 
			c.push_back(a[i]);
			c.push_back(b[i]);
		}
		if(n%2) c.push_back(a[n/2+1]); //剩下一个手动加入 
		
		printf("Case #%d: ",cs);
		bool fl=0;
		for(int i=0;i<c.size()-1;i++){
			if(c[i]>c[i+1]){ //发现错误 
				cout<<i<<endl;
				fl=1;
				break;
			}
		}
		if(!fl)
			puts("OK");
	}
	return 0;
}
```

---

## 作者：ALLIN2624 (赞：1)

## Meaning

对一个序列 $a_n$ 按照以下方式排序：遍历整个序列，对于下标 $i(\leq n-2)$，如果 $a_i>a_{i+2}$ 则交换 $a_i$ 和 $a_{i+2}$，若遍历完成后且本次遍历有交换操作则重新进行上述操作，否则完成排序。

判断对于 $a_n$ 排序可不可以使得 $a_n$ 变为升序。

## Solution

注意到交换操作只对下标奇偶性相同的元素有效，即排序后使得下标为奇数的元素有序，下标为偶数的元素有序，做法呼之欲出。

## Code

```cpp
// Problem: P13133 [GCJ 2018 Qualification] Trouble Sort
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13133
// Memory Limit: 1 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

void solve(int id) {
	int n;
	scanf("%d", &n);
	vector<int> a, b, c;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if (i & 1) a.push_back(x);
		else b.push_back(x);
	}
	sort(a.begin(), a.end()), sort(b.begin(), b.end());
	for (int i = 0, j = 0; i < a.size() || j < b.size(); i++, j++) {
		if (i < a.size()) c.push_back(a[i]);
		if (j < b.size()) c.push_back(b[j]);
	}
	printf("Case #%d: ", id);
	for (int i = 0; i < n - 1; i++) {
		if (c[i] > c[i + 1]) {
			printf("%d\n", i);
			return;
		}
	}
	puts("OK");
}

signed main() {
	signed T = 1;
	cin >> T;
	for (signed id = 1; id <= T; id++) {
		solve(id);
	}
	return 0;
}
```

---

## 作者：Velya_QiDream (赞：0)

## 解题思路
根据题目描述我们可以发现，用这种排序方式来排序，只能交换两个下标差为 $2$ 的数字，也就是只能交换 $a_x$ 和 $a_{x+2}$ 两个数字。

那么有了这个结论之后，我们就可以确定题目所给的 `Trouble Sort` 只能将所有的奇数位排序，然后所有的偶数位排序。

我们直接模拟将所有的奇数位排序，然后所有的偶数位排序，最后观察这个数组是否是上升数组就好了。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >>t;
	for(int op=1;op<=t;op++){
		vector<int> a,b; 
		int n;
		cin >>n;
		a.push_back(-1);
		b.push_back(-1);
		for(int i=1;i<=n;i++){
			int x;
			cin >>x;
			if(i%2) a.push_back(x);
			else b.push_back(x);
		}
		sort(a.begin(),a.end());
		sort(b.begin(),b.end());
		vector<int> ans;
		for(int i=1;i<=n/2;i++){ 
			ans.push_back(a[i]);
			ans.push_back(b[i]);
		}
		if(n%2==1){
			ans.push_back(a[n/2+1]);
		}
		cout <<"Case #"<<op<<": ";
		bool flag=0;
		for(int i=0;i<ans.size()-1;i++){
			if(ans[i]>ans[i+1]){
				cout <<i<<endl;
				flag=1;
				break;
			}
		}
		if(flag==0){
			cout <<"OK"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：CSP_S_2023_T2 (赞：0)

不难发现，Trouble Sort 只能交换两个距离为 $2$ 的数字。

也就是只能交换偶数位或奇数位。

所以 Trouble Sort 只能将所有的奇数位排序，所有的偶数位排序。

所以按上述方法排序一遍，观察数列是否单调不降即可。

代码如下：


```cpp
#include<bits/stdc++.h>

using namespace std;

int n,a[100005],b[50005],c[50005];  //b数组存储奇数位，c数组存储偶数位

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i%2) b[i/2+1]=a[i];
		else c[i/2]=a[i]; 
	}
	sort(b+1,b+(n-1)/2+2);
	sort(c+1,c+n/2+1);
	for(int i=1;i<=n;i++){
		if(i%2) a[i]=b[i/2+1];
		else a[i]=c[i/2];
	}
	for(int i=2;i<=n;i++){
		if(a[i]<a[i-1]){
			cout<<i-2<<'\n';     //下标从 0 开始，第 i-1 个出现问题要输出 i-2
			return ;
		}
	}
	cout<<"OK\n";
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
    	cout<<"Case #"<<i<<": ";
    	solve();
	}
    return 0;  //完结撒花
}
```

[AC Record](https://www.luogu.com.cn/record/223591666)。

---

## 作者：wurang (赞：0)

> 我们的算法会检查一组三个相邻的数字，如果最左边的数字大于最右边的数字，就将整个三元组反转。

我们将排序的过程总结一下：

执行 $n-1$ 次一下操作
- 检查 $L_1$ 是否小于 $L_3$，若为否，交换 $L_1$ 与 $L_3$。
- 检查 $L_2$ 是否小于 $L_4$，若为否，交换 $L_2$ 与 $L_5$。
- 检查 $L_3$ 是否小于 $L_5$，若为否，交换 $L_3$ 与 $L_5$。
- $\cdots$
- 检查 $L_{n-2}$ 是否小于 $L_n$，若为否，交换 $L_{n-2}$ 与 $L_n$。

不难发现这相当于对 $L$ 的奇数为与偶数位排序，于是我们便得到了一个 $n \log n$ 的算法。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int T;
bool f;
int n, x;
vector<int> a, b, c;

signed main() 
{
	cin >> T;
	for (signed Case = 1; Case <= T; Case++) 
    {
        f = 1;
        a.clear(), b.clear(), c.clear();

        cin >> n;
        for (int i = 1; i <= n; i++) 
        {
            cin >> x;
            if (i % 2) a.push_back(x);
            else b.push_back(x);
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for (int i = 1; i <= n; i++) 
        {
            if (i % 2) c.push_back(a[i/2]);
            else c.push_back(b[i/2-1]);
        }
        cout << "Case #" << Case << ": ";
        for (int i = 0; i < c.size() - 1; i++) 
        {
            if (c[i] > c[i + 1]) 
            {
                cout << i << "\n";
                f = 0;
                break;
            }
        }
        if(f) cout << "OK\n";
	}
	return 0;
}
```

---

