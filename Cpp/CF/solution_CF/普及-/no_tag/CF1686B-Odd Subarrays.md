# Odd Subarrays

## 题目描述

For an array $ [b_1, b_2, \ldots, b_m] $ define its number of inversions as the number of pairs $ (i, j) $ of integers such that $ 1 \le i < j \le m $ and $ b_i>b_j $ . Let's call array $ b $ odd if its number of inversions is odd.

For example, array $ [4, 2, 7] $ is odd, as its number of inversions is $ 1 $ , while array $ [2, 1, 4, 3] $ isn't, as its number of inversions is $ 2 $ .

You are given a permutation $ [p_1, p_2, \ldots, p_n] $ of integers from $ 1 $ to $ n $ (each of them appears exactly once in the permutation). You want to split it into several consecutive subarrays (maybe just one), so that the number of the odd subarrays among them is as large as possible.

What largest number of these subarrays may be odd?

## 说明/提示

In the first and third test cases, no matter how we split our permutation, there won't be any odd subarrays.

In the second test case, we can split our permutation into subarrays $ [4, 3], [2, 1] $ , both of which are odd since their numbers of inversions are $ 1 $ .

In the fourth test case, we can split our permutation into a single subarray $ [2, 1] $ , which is odd.

In the fifth test case, we can split our permutation into subarrays $ [4, 5], [6, 1, 2, 3] $ . The first subarray has $ 0 $ inversions, and the second has $ 3 $ , so it is odd.

## 样例 #1

### 输入

```
5
3
1 2 3
4
4 3 2 1
2
1 2
2
2 1
6
4 5 6 1 2 3```

### 输出

```
0
2
0
1
1```

# 题解

## 作者：skyskyCCC (赞：3)

**前言。**

题意：[题目传送门](https://www.luogu.com.cn/problem/CF1686B)

题意描述的似乎不太明白。  
其实就是有 $t$ 组数据，每次输入一个长度为 $n$ 的序列，将这个序列分成连续的序列——使得在这些序列中逆序对的数量为奇数的序列最多，输出其中逆序对为**奇数**的数量。

**分析。**
- 第一步：

首先要知道：
>You are given a permutation $[p_1, p_2, \ldots, p_n]$ of integers from $1$ to $n$ (each of them appears exactly once in the permutation).

翻译：给你的 $p$ 序列中**每个数的取值范围为从 $1$ 到 $n$ 且从 $1$ 到 $n$ 每个数只出现一次**。

- 第二步：

按照题目要求，为了分成较多的序列段，我们先将序列 $p$ 中的每个数都单独分成一个序列段，即 $[ p_1 ] \ [ p_2 ] \ [ p_3 ] \dots\ [ p_n]$ 的一个个序列段，这样显然序列段数最多，这样可以减少我们的思维跳跃度。

- 第三步：

考虑贪心。  
根据第一步可以知道，这个序列中最小值为 $1$ 而且它是一个奇数，所以显然当 $p_{i+1}<p_i$ 时，将 $p_{i+1}$ 与 $p_i$ 两个数组合成为一个序列时可以增加奇数序列数的数量，同时序列数剩下的将会较多，使得奇数的序列数可以保证较多。  
由上可得：当 $b_i > b_{i+1}$ 时，将这两个数组合成一个序列时，会形成局部最优解，贪心证明完毕。
- 第四步：

根据上述过程写代码，详细过程见代码。

代码如下，仅供参考：
```cpp
#include<iostream>
using namespace std;
int t,n,a[100005],ans[100005],tot,sum;//定义
int main(){
	cin>>t;//输入数据组数
	while(t--){
		cin>>n;//输入序列中的数的个数
		sum=0;//记录形成的奇数的序列个数
		for(int i=1;i<=n;i++){
			cin>>a[i];//输入数组
			if(a[i]<a[i-1]){//见第三步
				sum++;//出现了一个，记录
				if(i<n){
				    cin>>a[i+1];//输入下一个数
				}
				i++;//进入下一层循环
			}
		}
		tot++;//记录答案顺序
		ans[tot]=sum;//记录答案
	}
	for (int i=1;i<=tot;i++){
		cout<<ans[i]<<"\n";//输出，别忘了换行
	}
	return 0;
}
```
**后记。**

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：windflower (赞：2)

简要题意：
>将 $1\sim n$ 的一个排列分划成若干连续子序列，使得逆序对数为奇数的子序列数量最多.

我们考虑其中一个数 $a_i$ 以及一个最小的满足 $a_j<a_i$ 的 j，现在考虑区间 $(i,j)$。显然，对于任意的 $i<k<j$ 必有 $(a_k,a_j)$ 是一对逆序对。此时将该区间进一步划分为 $(i,j-2)$ 和 $(j-1,j)$，则 $(j-1,j)$ 必然是一个逆序对数为奇数的子序列，即这样划分成两个区间后，逆序对数为奇数的子序列数一定比之前的划分多。因此，我们最终只需要统计满足 $a_i>a_{i+1}$ 的配对个数即可，注意这里的每个 $a_i$ 只能使用一次，比如 $\{3,2,1\}$，这里的 2 要么与左边的 3 配对，要么与右边的 1 配对，不能同时与两边配对，即此情况配对的个数应为 1 而非 2。 

附 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,p[100005],ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=0;i<n;i++)cin>>p[i];
		for(int i=0;i<n-1;i++){
			if(p[i]>p[i+1]){
				ans++;
				i++;//防止重复配对
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：zyl1543130456 (赞：1)

## 题目大意

给你 $ t $ 组数据，每组数据中给你一个长度为 $ n $ 的序列 $ b $ ，你可以将 $ b $ 分成一些连续的序列（或一个），从而使得在这些序列中逆序对数为奇数的序列最多，输出其中逆序对对数为奇数对数。

## 解题思路

首先，题目讲了要找到尽可能多的逆序对数为奇数的段，为了分成尽可能多的段，我们先将序列 $ b $ 中的每个数都单独分成一段  $ [ b_1 ] \ [ b_2 ] \ [ b_3 ] \ ... \ [ b_n ] $ ，这样显然序列数最多。

接下来考虑如何将这些序列组合起来时的出现逆序对数为奇数的段，由于 $ 1 $ 是奇数，所以显然当 $ b_i > b_{i+1} $ 时，将这两个数组合成一个序列可以增加逆序对数为奇数序列数的数量，同时剩下的序列数会尽可能的多，使得逆序对数为奇数的序列数可以保证尽可能多。

所以我们考虑贪心，当 $ b_i > b_{i+1} $ 时，将这两个数组合成一个序列，答案加一。结束。

## 代码 

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;
const int N=1e5+10;
int t;
int n;
int a[N];

int main(){
	scanf("%d",&t);
	while(t--){
		int ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]<a[i-1]){
				ans+=1;
				if(i<n)scanf("%d",&a[i+1]);
				i+=1;
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：legend_cn (赞：0)


## 简化题意
将 $1$ 到 $n$ 的一个排列分成若干连续的区间， 要让逆序对为奇数的区间最多。

## 分析
我们现在有每一个数 $a_i$。首先要求出一个最小的满足 $a_j <a_i$ 的 $j$。我们来看一下区间 $(i,j)$。对于任何 $i<k<j$ 的 $k$，$(a_k,a_j)$ 一定是一对逆序对。此时将这个区间再次划分为区间 $(i,j-2)$ 还有区间 $(j-1,j)$。可知，区间 $(j-1,j)$ 一定是一个逆序对数量为奇数的区间。如果这样划分，逆序对个数为奇数的区间可以达到最优。

## 解法
通过上述分析，只需要统计满足 $a_i>a_{i+1}$ 的配对个数就可以了。每一个 $a_i$ 只能被使用一次。比如这一个排列为 $(1,2,3)$，$2$ 只能与 $1$ 和 $3$ 中的一个配对。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int ans=0;
		for(int i=0;i<n;i++)
			cin>>a[i];
		for(int i=0;i<n-1;i++)
		{
			if(a[i]>a[i+1])
			{
				ans++;
				i++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：云裳 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1686B)

**思路**

如果这个数比最大值小，就可以构成一个题目中要求的子阵列，将最大值设为 -1 。

如果不比前面的数小，就不能构造要求的子阵列，重新开一个子阵列，同时将最大值设为这个数。


------------

举给例子，5 7 2 3。

- 将 5 设为最大值。

- 7 比 5 大，将 5 设为一个子阵，同时将 7 设为最大值。

- 2 比 7 小，可以构成，答案加一。

- 3 是最后一个数，无法构成子阵列。

所以，答案为 1。


------------

再比如 4 5 6 1 2 3，

- 将 4 设为最大值

- 5 比 4 大，将 4 设为一个子阵，同时将 5 设为最大值。

- 6 比 5 大，将 5 设为一个子阵，同时将 6 设为最大值。

- 1 比 6 小，将 6 和 1 设为一个子阵，最大值归为-1。

- 2 和 3 同上面 5 和 4 的步骤。

虽然我们划分了很多子阵列，但答案不变，为 1。

------------
**代码实现**

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define INF 0x7fffffff
typedef long long ll;
using namespace std;
ll read() {//快读
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
void write(ll x) {//快写
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void write_kong(ll x) {//空格快写
	write(x);
	cout<<" ";
}
void write_endl(ll x) {//换行快写
	write(x);
	cout<<"\n";
}
void work() {
	ll n=read(),a[maxn],ans=0,maxx=-1;//初始化 n 子阵列 答案 最大值
	for(ll i=1; i<=n; i++) a[i]=read();//读入
	for(ll i=1; i<=n; i++) {
		if(maxx<a[i]) maxx=a[i];
		//如果这个数比最大值大，重新开一个子阵列，最大值为当前值
		else {//如果比最大值小
			maxx=-1;//开一个奇数子阵列，最大值为-1
			ans++;//答案增加一个
		}
	}
	write_endl(ans);//输出
}
int main() {
	ll t=read();//数据组数
	while(t--) work();
	return 0;
}

```

---

