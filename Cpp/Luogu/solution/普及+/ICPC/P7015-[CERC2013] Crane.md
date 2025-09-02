# [CERC2013] Crane

## 题目描述

有 $n$ 个箱子等着装上船。箱子的编号是 $a_1,a_2,\cdots,a_n$。你的工作是通过若干次交换，将它们从小到大排列。你每次可以选择一个区间，将它的前半部分与后半部分交换，两半内部的顺序保持不变。你最多可以交换 $531441$ 次。

## 样例 #1

### 输入

```
2
6
5 4 6 3 2 1
5
1 2 3 4 5
```

### 输出

```
5
1 2
4 5
5 6
4 5
1 6
0
```

# 题解

## 作者：Lemansky (赞：2)

## 题意

翻译其实蛮清楚了，每次选择一段区间，将其前半部分与后半部分直接交换，从而把序列从小到大排序。构造一个操作序列即可。

这里补充一下原题面的点：序列是个 $1$ 到 $n$ 的排列。

## 思路

对于每组数据：

- 考虑一种贪心的暴力操作方法：把 $1$ 到 $n$ 从小到大依次**归位**（$a_i=i$），其合理性在于后面对右边数的操作不会影响左边已归位的数。

- 如果当前把 $i$ 归位，尽可能优的方法是选区间 $[i,pos_i]$，$pos_i$ 是 $i$ 当前的位置，这样每次就能向终点前进大约一半。

- 举个例子，序列是 $\{4,3,2,1\}$，先操作 $[1,4]$ 变为 $\{2,1,4,3\}$，再操作 $[1,2]$ 变为 $\{1,2,4,3\}$。这样 $1$ 就归位了，恰好 $2$ 也归位，再操作 $[3,4]$ 即可。

- 但是注意操作序列中的区间长度必须是偶数，因此需要微调区间的选择（即 $[i+1,pos_i]$）。

具体可以见代码。

## 复杂度和操作分析

对于每组数据：

- 注意到每次归位一个数大约需要 $\log n$ 次操作（每次归一半），因此估计最坏也就 $n\log n$ 次操作，$n\le 10^4$ 对于题目的限制来说完全够用了。

- 至于时间复杂度，~~SPJ 能跑过去那我们肯定可以~~每次归位最多产生 $n$ 次单位交换，暴力最坏是 $O(n^2)$ 的复杂度，但其实远远到不了，直接操作就过了。

注意本题的多测限制。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[10005],b[10005];//b数组存位置
int s,l[114514],r[114514];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n,m=1,s=0;
		for(int i=1;i<=n;++i) cin>>a[i],b[a[i]]=i;
		while(1){
			while(b[m]==m) ++m;
			if(m>n) break;
			while(b[m]!=m){//还没归位
				++s,l[s]=m+(b[m]-m+1)%2,r[s]=b[m];
				int w=(l[s]+r[s])/2;
				for(int i=l[s];i<=w;++i){
					swap(a[i],a[i+w-l[s]+1]);
					swap(b[a[i]],b[a[i+w-l[s]+1]]);
				}
			}
		}
		cout<<s<<'\n';
		for(int i=1;i<=s;++i) cout<<l[i]<<' '<<r[i]<<'\n';
	}
    return 0;
}
```

---

## 作者：mahaorui2012 (赞：1)

很好玩的构造。

# 题意补充

$a$ 是 $1$ 到 $n$ 的排列。

翻转的区间需长度为偶数。

# 思路

可以仿照类似冒泡排序的思路，第 $i$ 轮将 $i$ 归位，这样下一轮就影响不到这个元素了。

此时需要用 $\log n$ 次操作将一个元素归位。

设 $i$ 位于 $p_i$，则第 $i$ 轮可以使用类似二分的一种方法：

第一步，若 $\frac{n}{2}\le p_1$，交换 $[1+((n-i+1) \bmod 2),n]$，此时 $p_1\in [1,\frac{n}{2}]$。（加上模是因为长度需为偶数）

第二步，若 $\frac{n}{4}\le p_2$，交换 $[1+((\frac{n}{2}-i+1) \bmod 2),\frac{n}{2}]$，此时 $p_2\in [1,\frac{n}{4}]$。 

第 $i$ 步，若 $\frac{n}{2^i}\le p_i$，交换 $[1+((\frac{n}{2^i-1}-i+1) \bmod 2),\frac{n}{2^{i-1}}]$，此时 $p_i\in [1,\frac{n}{2^i}]$。

在第 $\log n$ 步后，保证 $p_i\in [1,1]$ 即 $p_i=i$。

此时可以开始下一轮归位，总归位次数小于 $n\log n$，可满足本题要求。

查询元素所在地点可以用哈希来使时间复杂度降至 $\operatorname{O}(1)$，交换长度为 $l$ 的区间的时间复杂度为 $\operatorname{O}(l)$，每一轮交换的总区间长度为 $\sum_{i = 0}^{n} \frac{n}{2^i}=2\times n$，所以总时间复杂度为 $\operatorname{O}(n^2)$，可通过此题。

# AC CODE

```C++
#include <iostream>
using namespace std;

int arr[10005];
int hsh[10005];

void mswap(int l,int r){
	int len=(r-l+1)/2;
	for(int i=0;i<len;++i){
		swap(arr[l+i],arr[l+i+len]);
		swap(hsh[arr[l+i]],hsh[arr[l+i+len]]);
	}
}

struct oper{
	int l,r;
} oparr[140005];
int p=0;

int main(){
	int t;
	cin>>t;
	while(t--){
		p=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>arr[i];
			hsh[arr[i]]=i;
		}
		for(int i=1;i<=n;++i){
			int r=n;
			while(r-i>=1){
				int mid=(i+r-(r-i)%2)/2;
				if(hsh[i]>mid){
					mswap(i+(r-i+1)%2,r);
					oparr[++p].l=i+(r-i+1)%2;oparr[p].r=r;
				}r=mid;
			}
		}
		cout<<p<<'\n';
		for(int i=1;i<=p;++i){
			cout<<oparr[i].l<<' '<<oparr[i].r<<'\n';
		}
		 
	}return 0;
} 
```

---

