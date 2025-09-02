# [JOIG 2024] ダンス / Dance

## 题目描述

一所中学的一个班级有 $2N$ 名学生，第 $i(1\le i\le 2N)$ 名学生的身高是 $A_i$。

在即将开始的体育课上，学生们将两两配对，形成 $N$ 组进行舞蹈。

要跳出优美的舞蹈，每一对舞伴之间的身高差必须小于或等于 $D$。

给定每个学生的身高，确定能否跳出优美的舞蹈。

## 说明/提示

#### 【样例解释 #1】

只有一种配对方案，满足 $|2-7|\le 5$，符合条件。

该样例满足子任务 $1,3$ 的限制。

#### 【样例解释 #2】

无论如何都没法进行配对，使得任意一对舞伴的身高差 $\le 0$。

该样例满足子任务 $2,3$ 的限制。

#### 【样例解释 #3】

考虑如下配对方案：

- 身高 $39$ 的学生和身高 $42$ 的学生配对；
- 身高 $22$ 的学生和身高 $23$ 的学生配对；
- 身高 $16$ 的学生和身高 $17$ 的学生配对；
- 身高 $32$ 的学生和身高 $36$ 的学生配对；
- 身高 $15$ 的学生和身高 $18$ 的学生配对；
- 身高 $30$ 的学生和身高 $30$ 的学生配对。

符合条件。

该样例满足子任务 $3$ 的限制。

#### 【数据范围】

- $1\le N\le 100$；
- $0\le D\le 100$；
- $1\le A_i\le 100(1\le i\le 2N)$。

#### 【子任务】

1. （$20$ 分）$N=1$；
2. （$40$ 分）$D=0$；
3. （$40$ 分）无附加限制。

## 样例 #1

### 输入

```
1 5
2 7```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 0
10 10 10 11 10 10```

### 输出

```
No```

## 样例 #3

### 输入

```
6 4
22 15 32 36 16 30 42 30 39 23 17 18```

### 输出

```
Yes```

# 题解

## 作者：ARIS1_0 (赞：8)

十分简单的贪心题。

利用贪心思想，对所有人的身高从小到大进行排序。随后将相邻的两个元素划分进一组进行比较，若不符合条件，直接输出 `No`，若符合则选择下两个相邻的元素并重复上述流程。

为什么这是对的？设比较之后的数组为 $A$，$D$ 为容许的身高误差。显然有 $A_1 \le A_2 \le A_3 \le \dots \le A_{2\times n-1} \le A_{2\times n}$。若有 $A_{i+2}-A_i \le D$，则必有 $A_{i+1}-A_i\le D$，但是如果将 $(A_{i+2},A_i)$ 配对，那么剩下的 $A_{i+1}$ 就需要去和身高更高或更矮的学生进行配对，那么此时可能得到的身高误差就一定不会小于用 $A_{i+2}$ 去配对更高的学生得到的身高误差或者用 $A_{i-1}$ 去配对更矮的学生得到的身高误差。为了满足题目的条件，我们必须将每一组学生的身高误差都尽可能缩小，故将 $(A_{i+1},A_i)$ 配对是优于将 $(A_{i+2},A_i)$ 配对的。

不符合条件的情况也很显然。注意到 $A_{i+1}-A_i > D$，那么一定有 $A_{i+2}-A_i>D$，所以此时无解。

代码就不放了，个人觉得讲的还算清晰。

---

## 作者：liaoxingrui (赞：5)

## Content

给你一个 $n$，有 $2 \times n$ 个数，将两个数进行组合。

如果能有能保证每个组合差距小于等于 $d$ 的方法，则输出 `Yes`，否则输出 `No`。

## Solution

这题可以用 $O(n^2)$ 的暴力，也可以用排列做到更优。

排序过后，就看两两相差是否小于等于 $d$，不是则输出 `No`，因为前面以及组合好了，而后面也只有更大的，所以直接输出 `No` 即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e2+5;
int n,m;
int a[N];
int main(){
	cin>>n>>m;
	n<<=1;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i+=2)
		if(a[i]+m<a[i+1]){
			puts("No");
			return 0;
		}
	puts("Yes");
	return 0;
}
```

---

## 作者：cy20110922 (赞：4)

# 题意
输入 $2n$ 个学生的身高，要求找出一种方法让他们两两配对使每队的两个人身高差不超过 $D$ 。
# 方法
先输入 $n$ 和 $D$ 然后读入数组。将数组排序之后从开头两两对比。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n[120000];
int main(){
	int x,y;
	cin >> x >> y;
	for(int i=1;i<=x*2;i++){
		cin >> n[i];
	}
	sort(n+1,n+2*x+1);
	for(int i=1;i<x*2;i+=2){
		if(n[i+1]-n[i]>y){
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：Anins (赞：2)

## [[JOIG 2024 Open] ダンス / Dance](https://www.luogu.com.cn/problem/P11199)

### 思路：
我们对 $2N$ 个学生身高进行排序，每相邻两个为一组，若有一组或以上身高差大于 $D$，则不合法，否则合法。

原因：设 $a$，$b$，$c$，$d$ 身高顺序不递减，要保证 $a$ 所在组合合法，$a$ 与 $b$ 搭配最佳，$c$ 同理应与 $d$ 搭配。

注意 $1 \le N \le 100$，那么数组大小要开到至少 $200$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int N, D;
int A[205];
int main() {
	cin >> N >> D;
	for(int i=1; i<=2*N; i++) cin >> A[i];
	sort(A+1, A+(2*N)+1);
	for(int i=1; i<=2*N; i+=2) {
		if(A[i+1]-A[i]>D) {
			cout << "No";
			return 0;
		} 
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：banglee (赞：1)

## P11199 [JOIG 2024 Open] ダンス / Dance 题解
[题目传送门](https://www.luogu.com.cn/problem/P11199)

## 正文
一道模拟题。

因为题目要求每一对舞伴之间的身高差必须小于或等于 $D$，所以可以考虑排序，身高越相近，差越小。

然后从排序后的数组中相邻的两个学生配对并检查身高差是否小于等于 $D$。

这题就解决了。

## 核心代码
```cpp
for(int i=1;i<=2*n;i+=2) //每两个学生配对在一起
  if(a[i+1]-a[i]>d) {cout<<"No"; return 0;} //跳不出优美的舞蹈
cout<<"Yes";
```

---

## 作者：fwtv_24 (赞：1)

## 题目大意
给你两个数 $n,d$ ，并给你一段长度为 $2n$ 的数列，并在其中两两配对，问是否存在一种情况使每组之间的差值小于 $d$ 。

## 分析
我们可以先对数列进行排序，再进行两两配对。若两个的差值大于 $d$ ，则一定不能满足条件。以下给出证明。

#### 证明
给定一串数列 $a=[a_1,a_2,a_3,... ,a_{2n-1},a_{2n}]$ $(a_1≤a_2≤...≤a_{2n})$ 

那么配对配对结果为 $(a_1,a_2),(a_3,a_4),...,(a_{2n-1},a_{2n})$

若 $a_2-a_1>d,a_3-a_2<d$ 那么根据题意，我们就应将 $a_2,a_3$ 分为一组。

但是此时因为 $a_1≤a_2≤a_3$ ，所以 $a_3-a_1>d$ ，则不成立。

所以我们只需根据排序后分组即可。


## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a[1000005];
signed main()
{
	cin>>n>>d;
	for(int i=1;i<=2*n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+2*n+1);//先排序
	for(int i=1;i<=2*n;i+=2)//两两分组
	{
		if(a[i+1]-a[i]>d)//若分组不符合题意
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes"; 
	return 0;//养成好习惯QwQ
}
```

---

## 作者：__AFO__ (赞：0)

# P11199 [JOIG 2024 Open] ダンス / Dance 题解

### 题目大意

有 $2N$ 个数，两两组队，使他们之间的差都不超过 $D$，判断是否可以完成组队。

### 本题思路

要想两个数之间的差尽可能的小，那么最优策略必定是选择大小最接近的两个数，所以我们将所有数进行排序，从小到大依次排序，然后两两组队，判断是否能完成题目要求即可。

### 代码实现:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,a[555];
int main(){
	scanf("%lld%lld",&n,&d);
	for(long long i=1;i<=2*n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+2*n);//根据思路从小到大排序 
	for(long long i=1;i<=2*n;i+=2){
		if(a[i+1]-a[i]>d){//判断是否满足题目要求 
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	
	
	
	return 0;
}
```

完结撒花。

---

## 作者：Vct14 (赞：0)

我们按身高排序之后选择身高相邻的学生配对即可。如果连某两个相邻的两个学生都无法配对，那么这些学生一定无法成功配对。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[202];

int main(){
	int n,d;cin>>n>>d;
	for(int i=1; i<=2*n; i++) cin>>a[i];
	sort(a+1,a+1+2*n);
	for(int i=1; i<2*n; i+=2){
		if(abs(a[i]-a[i+1])>d){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：3Luby3 (赞：0)

## 题目大意
输入 $n$ 组学生，共 $2n$ 名学生。现在要两两配对，他们之间所有的差不能大于 $d$。
## 思路
这道题我们考虑**贪心**。

我们将所有学生的身高进行排序，从最矮的学生开始，依次配对身高差不超过 $d$ 的学生。如果能够成功配对所有学生，则输出 `Yes`，否则输出 `No`。

## 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,a[1005];//定义
signed main() {
    cin>>n>>d;//输入
    for(int i=0;i<2*n;i++) cin>>a[i];
    sort(a,a+2*n);//按身高排序
    for(int i=0;i<n;i++)
        if(a[i*2+1]-a[i*2]>d){//差大于d，匹配不成功
            cout<<"No";//输出No
			return 0; 
        }
    cout<<"Yes";//全部匹配成功
    return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

一开始因为数组开小过不掉，警钟长鸣。

本题是一道贪心题目。

因为我们要保证每对舞伴的身高只差尽量小，所以我们要对每个没有配对的找一个同样没有配对且绝对值差最小的和他配对，判断是否可以即可。

然后就没有然后了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[205];
bool vis[205];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,k;
	cin>>n>>k;
	n=n*2;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		if (vis[i]) continue;
		bool f=1;
		for(int j=i+1;j<=n;j++){
			if (vis[j]) continue;
			if (a[j]-a[i]<=k) {
				f=0;
				vis[i]=vis[j]=1;
				break;
			}
		}
		if (f) {
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：ny_jerry2 (赞：0)

## 思路
我们可以将数组排序，然后从前往后两个两个分组，这样就可以得到正解了。

为什么是对的？这里我可以简单证明一下（如果有问题可以指正）。

设有 $4$ 个数 ${a,b,c,d}$，其中满足：  
$$
a < b < c <d
$$
显然，我们的问题是让最大的差尽量小（但别想到二分去了）。

分几种情况讨论：

- ${a,b}$ 为一组，${c,d}$ 为一组。

  显然，最大的差为：$\max(b-a,d-c)$。

- ${a,c}$ 为一组，${b,d}$ 为一组。

  显然，最大的差为：$\max(c-a,d-b)$。

- ${a,d}$ 为一组，${b,c}$ 为一组。

  显然，最大的差为：$d-a$。因为 $d-a>c-b$。

显然，第一种最优，即我们上面所说的方案。

## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[110];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=2*n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+2*n+1);
	for(int i=1;i<=2*n;i+=2){
		if(a[i+1]-a[i]>k){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：songzhixin (赞：0)

### 题目大意

把 $2 \times n$ 个数分为 $n$ 组，问是否有一种分组满足任意一组内两个数的差的绝对值小于等于 $D$。

### 解题思路

我们可以先将 $a$ 数组排序，则我们的最优分组一定是两个相邻的数。

不难发现,若不是相邻的数，则这两个数的差一定是大于等于把它换为相邻的两个数后的差。

举个例子，排序后为 $a,b,c,d$，其中 $a \le b \le c \le d$，则选 $a,c$ 和 $b,d$ 或者 $a,d$ 和 $b,c$
 一定不如 $a,b$ 和 $c,d$ 更优，因为 $a \le b \le c \le d$。

因此我们只需要让 $a_1,a_2$ 一组，$a_3,a_4$ 一组，一直到 $a_{2 \times n-1},a_{2 \times n}$ 一组，这样子分是最优的。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int n,d;
int a[N];
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n*2;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n+n);
	for(int i=1;i<=n*2;i+=2){
		if(a[i+1]-a[i]>d){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}
```

---

