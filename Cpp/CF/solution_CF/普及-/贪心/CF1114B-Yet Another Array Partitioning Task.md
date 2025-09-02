# Yet Another Array Partitioning Task

## 题目描述

An array $ b $ is called to be a subarray of $ a $ if it forms a continuous subsequence of $ a $ , that is, if it is equal to $ a_l $ , $ a_{l + 1} $ , $ \ldots $ , $ a_r $ for some $ l, r $ .

Suppose $ m $ is some known constant. For any array, having $ m $ or more elements, let's define it's beauty as the sum of $ m $ largest elements of that array. For example:

- For array $ x = [4, 3, 1, 5, 2] $ and $ m = 3 $ , the $ 3 $ largest elements of $ x $ are $ 5 $ , $ 4 $ and $ 3 $ , so the beauty of $ x $ is $ 5 + 4 + 3 = 12 $ .
- For array $ x = [10, 10, 10] $ and $ m = 2 $ , the beauty of $ x $ is $ 10 + 10 = 20 $ .

You are given an array $ a_1, a_2, \ldots, a_n $ , the value of the said constant $ m $ and an integer $ k $ . Your need to split the array $ a $ into exactly $ k $ subarrays such that:

- Each element from $ a $ belongs to exactly one subarray.
- Each subarray has at least $ m $ elements.
- The sum of all beauties of $ k $ subarrays is maximum possible.

## 说明/提示

In the first example, one of the optimal partitions is $ [5, 2, 5] $ , $ [2, 4] $ , $ [1, 1, 3, 2] $ .

- The beauty of the subarray $ [5, 2, 5] $ is $ 5 + 5 = 10 $ .
- The beauty of the subarray $ [2, 4] $ is $ 2 + 4 = 6 $ .
- The beauty of the subarray $ [1, 1, 3, 2] $ is $ 3 + 2 = 5 $ .

The sum of their beauties is $ 10 + 6 + 5 = 21 $ .

In the second example, one optimal partition is $ [4] $ , $ [1, 3] $ , $ [2, 2] $ , $ [3] $ .

## 样例 #1

### 输入

```
9 2 3
5 2 5 2 4 1 1 3 2
```

### 输出

```
21
3 5 ```

## 样例 #2

### 输入

```
6 1 4
4 1 3 2 2 3
```

### 输出

```
12
1 3 5 ```

## 样例 #3

### 输入

```
2 1 2
-1000000000 1000000000
```

### 输出

```
0
1 ```

# 题解

## 作者：decoqwq (赞：2)

看到数据范围，考虑贪心，既然每一块都取最大的$m$个，我们就将答案设置为最大的$k\times m$个之和，然后从头到尾扫一遍，如果一块中已经出现了$m$个要取的数，划开即可
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,m;
int a[200010],b[200010];
map<int,int> mp;
int main()
{
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	long long ans=0;
	for(int i=n,j=1;j<=(k*m);i--,j++)
	{
		mp[b[i]]++;
		ans+=b[i];
	}
	cout<<ans<<endl;
	for(int i=1,now=0,qaq=0;i<=n;i++)
	{
		if(mp[a[i]])
		{
			now++;
			mp[a[i]]--;
		}
		if(now>=k)
		{
			printf("%d ",i);
			qaq++;
			now=0;
		}
		if(qaq==m-1)
		{
			return 0;
		}
	}
}
```
[这一场cf的题解，打个广告](https://decorationqwq.com/archives/324/)

---

## 作者：cannotdp (赞：1)

### 题目分析
#### 教给大家一个考场实用的小技巧：**观察数据范围**

一开始看到这道题目我把它想复杂了，以为需要用到 dp 之类的东西，但是看到数据范围后我悟了：

#### $m \times k \leq n$。

这给了我们一个至关重要的提示，于是我口胡出一个算法：

我们可以只考虑序列中的前 $m \times k$ 大的数，进行一个贪心。扫一遍序列，对于第 $i$ 个数 $a_i$，如果 $a_i$ 是前 $m \times k$ 大的数，那么负责记录个数的变量 $L$ 就加一，直到 $L=m$，这说明已经满足了条件，于是序列便从这里划分，然后负责记录的 $L$ 赋值为零进行下一轮划分，直到序列划分完毕。

### 避坑指南

每组数据的解可能是不唯一的，所以有些同学看到自己写的贪心算法过不了样例就认为自己的思路是错的，实际上样例就是一个误导。

### 代码实现

```
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#define int long long
using namespace std;
priority_queue<int>q;//使用大根堆维护前m*k大的数 
int n,m,k,ans;
const int N=2e5+10;
int a[N];
map<int,int>f;//一个桶，因为a[i]的范围过大 ，直接用数组会炸掉，所以使用map 
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);	
	int temp=m*k;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		q.push(a[i]);
	}
	int p=1;
	while(!q.empty()&&p<=temp){
		ans+=q.top(),f[q.top()]++,q.pop();//取出前m*k大的数 
		p++; 
	}
	printf("%lld\n",ans);
	int num=1,i=1,L=0;
	while(num<k&&i<=n){ 
		if(f[a[i]]>0) L++,f[a[i]]--;//当前数能选就选 
		if(L==m){//本轮划分完毕 
			printf("%lld ",i);
			L=0;//不要忘记赋零 
			num++;
		}
		i++;
	}
	return 0;
}
```


---

## 作者：Chillturtle (赞：0)

upd on 2024.9.5 20:13 修了一下格式，求管理大大通过 qwq。

首先看到数据范围，所以首先想到的就是贪心 ，既然每一块都需要取最值，所以我们就将答案设置为最大的 $ k \times m $ 个之和，然后扫一遍即可。

# AC代码

```cpp
#include <bits/stdc++.h>
  
#define int long long
  
using namespace std;
  
priority_queue<int>q;
  
int n,m,k,ans;
  
const int N=2e5+10;
  
  
int a[N];
  
map<int,int>f;
  
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);	
	int temp=m*k;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		q.push(a[i]);
	}
	int p=1;
	while(!q.empty()&&p<=temp){
		ans+=q.top(),f[q.top()]++,q.pop(); 
		p++; 
	}
	printf("%lld\n",ans);
	int num=1,i=1,L=0;
	while(num<k&&i<=n){ 
		if(f[a[i]]>0) L++,f[a[i]]--;
		if(L==m){ 
			printf("%lld ",i);
			L=0;
			num++;
		}
		i++;
	}
	return 0;
}
```

---

## 作者：Fly_AFO (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1114B)

要求“美丽度”之和最大，那么就是前 $km$ 大的数的和，分法不止一种，先把前 $km$ 大的数的和输出，然后可以用一个变量做记录，达到 $m$ 个比较大的数就输出一次，但必须特判最后一次。

对于第一小问，可以用另外一个数组将这一组数拷贝，进行排序，这样才不会影响原数组。

```cpp
for(int i=1;i<=m;i++){
	cin>>a[i];b[i]=a[i];//防止a数组被覆盖 
}
sort(b+1,b+1+m);
for(int i=m;i>=m-n*k;i--){
	flag[b[i]]++;
	summ+=b[i];//求最大值 
}
cout<<summ<<endl;
```

接着，对于每个数依次判断即可。

```cpp
for(int i=1;i<=m;i++){
	if(flag[a[i]]!=0){//是前n*k大的数 
		summ++;
		flag[a[i]]--;
	}
	if(summ==n){//是否达到输出条件 
		x++;
		cout<<i<<" ";
		summ=0;
	}
	if(x==k-1)//防止输出最后一个数 
		return 0;
}
```


---

