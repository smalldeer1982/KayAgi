# Worms

## 题目描述

现在是鼹鼠的午餐时间，他的好友土拨鼠，为他准备了一个游戏。

土拨鼠带来了成堆的蚯蚓，使第 $i$ 堆中有 $a_i$ 条蚯蚓。它用连续整数给所有这些蚯蚓打标签：第一堆蚯蚓用数字 $1$ 到 $a_1$ 标记，第二堆蚯蚓用数字 $a_1 + 1$ 到 $a_1 + a_2$ 标记 ...... 以此类推。

鼹鼠吃不掉所有的蚯蚓 （土拨鼠带来了一大堆） ，而且我们都知道，鼹鼠是是看不见东西的，所以土拨鼠会告诉鼹鼠多汁蚯蚓的标签。如果鼹鼠正确地说出这个蚯蚓在哪个堆里，土拨鼠就会给鼹鼠一条蚯蚓。

可怜的鼹鼠向你求助，希望你能告诉鼹鼠正确的答案。

## 样例 #1

### 输入

```
5
2 7 3 4 9
3
1 25 11
```

### 输出

```
1
5
3
```

# 题解

## 作者：xiaomuyun (赞：5)

# CF474B Worms 题解
[题目传送门](https://www.luogu.com.cn/problem/CF474B)

~~蒟蒻一枚，多多指教~~
## 解法：二分
我们只需要在输入时做一点前缀和（区间和做法），即把每个 $a_i$ 增加 $a_{i-1}$，这样第 $i$ 堆蚯蚓就会被数字 $a_i-a_{i-1}$ 标记。这时我们就可以先排序，然后用二分找出第一个**严格大于** $q_i$ 的 $a_j$。之所以用严格大于，是因为这句话：

> 第一堆蚯蚓用数字 $1$ 到 $a_1$ 标记，第二堆蚯蚓用数字 $a_1+1$ 到 $a_1+a_2$ 标记 $\dots\dots$ 以此类推。

如果正好是 $a_i$ 的话，那应该是第 $a_{i-1}$ 堆蚯蚓。所以代码呼之欲出：
```cpp
#include<algorithm>
#include<iostream>

using namespace std;

int n,m,a[100001],q[100001];

int b_c(int k){//手打二分 
	int l=1,r=n;
	while(l<r){
		int mid=(l+r)/2;
		if(a[mid]>=k) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		a[i]+=a[i-1];//前缀和 
	}
	sort(a+1,a+1+n);
	cin>>m;
	for(int i=1;i<=m;++i){
		int q;
		cin>>q;
		cout<<b_c(q)<<endl;
	}
	return 0;
}
```
然后做了点优化：
```cpp
#include<algorithm>
#include<cstdio>

using namespace std;

int n,m,a[100001],q[100001];

inline int b_c(int k){//手打二分 
	register int l=1,r=n;
	while(l<r){
		register int mid=(l+r)/2;
		if(a[mid]>=k) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		a[i]+=a[i-1];//前缀和 
	}
	sort(a+1,a+1+n);
	scanf("%d",&m);
	for(register int i=1;i<=m;++i){//回答m个问题 
		register int q;
		scanf("%d",&q);
		printf("%d\n",b_c(q));//调用二分并输出即可 
	}
	return 0;
}
```
时间竟然从 $11.65s$ 卡到了 $1.56s$！（~~不要尝试去找我的提交记录，找不到的，我隐藏了~~）
## 结束语
又和大家一起度过了一篇短短的文章，本蒟蒻对二分的理解又深了。希望大家也能有所收获。最后不要忘了点个赞，制作不易~

---

## 作者：Forever1507 (赞：3)

~~我第一眼其实先看的是数据范围。。。~~

**思路不同于已有的任何题解**

$10^5$ , 一眼看上去就是 $n log n$ 的时间复杂度，马上想到可以先把已有的多汁蚯蚓序列快排一下，然后从第一堆的蚯蚓数开始累加，达到一个多汁蚯蚓的标签就记一下，当然不能直接输出，排序之后顺序会改变，所以我们要弄一个结构体把值和顺序都记一下，记答案的时候就记原来的序号就行了。

其他的解释看注释吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int q,num;//q为值,num为原序号
}q[100005];
int n,m,a[100005],ans[100005];
bool cmp(node a,node b){
	return a.q<b.q;//按值排序
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++){
		int s;
		cin>>s;
		q[i].q=s;
		q[i].num=i;
	}
	sort(q+1,q+1+m,cmp);
	int cur=1,cnt=a[1];//从第一个开始累加
	for(int i=1;i<=m;i++){
		while(cnt<q[i].q){//没到值就一直累加
			cur++;
			cnt+=a[cur];
		} 
		ans[q[i].num]=cur;//记答案
        //下标要用原来的序号哦
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
}
```


---

## 作者：_Harrisonwhl_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF474B)
这题的数据:$1 \leqslant n \leqslant 10^5$ 且 $1 \leqslant m \leqslant 10^5$，我暴力搜索 $n$ 个堆看哪个堆包含当前多汁蚯蚓时间复杂度为 $O(n^2)$,是不行的，此时有两个解决方法：
1. 二分

2. 预处理存储后暴力

很明显第二种更好写，二分的话细节很多，稍有偏差就会 WA,于是就打了个预处理暴力，预处理每个蚯蚓在第几堆，到时候查的时候直接用就行了，最坏情况下运行 $2*10^5+10^6$ 次，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,t1,t2,last = 0/*用来存上一个堆堆到几号蚯蚓了*/,b[1000005];
int main()
{
    cin >> n;
    for (int i = 1;i <= n;i++)
    {
    	cin >> t1;
    	for (int j = last + 1;j <= t1 + last;j++)//从上一个蚯蚓+1到比上一次多本堆个数号的蚯蚓标记在第i堆。
    		b[j] = i;
    	last = t1 + last;//更新一下这一个堆堆到几号蚯蚓了
    }
    cin >> m;
    for (int i = 1;i <= m;i++)
    {
    	cin >> t2;
    	cout << b[t2] << endl;
    }
    return 0;
}
```


---

## 作者：_OJF_ (赞：1)

这道题应该比较水，想到了两种方法：

1、二分

2、将每只蚯蚓所在的堆编号存起来，然后进行暴力

第二种代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n, m, a[100005], f[1000005], q[100005], cnt = 1;
int main(){
    cin>>n;
    for(int i = 1;i <= n;i++)
        cin>>a[i];
    for(int i = 1;i <= n;i++){
        for(int j = cnt;j <= cnt + a[i] - 1;j++)
            f[j] = i;
        cnt += a[i];
    }
    cin>>m;
    for(int i = 1;i <= m;i++)
        cin>>q[i], cout<<f[q[i]]<<endl;
    return 0;
}
```


---

## 作者：耶耶小朋友 (赞：1)

### 做法：
二分答案，~~不过好像暴力也能水过~~……
### 主体思路：
1.输入。

2.开始二分，$l = 1$，$r = n$。（需要特判 $x$ 在第一堆的情况）

3.如果满足条件，则返回值。

4.不满足条件就更新 $l$ 与 $r$ 的值。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
//考虑unsigned long long
typedef long long ll;
const int N = 100010;
int a[N];
int n,m;
int findd(int x){
    int l = 1;
    int r = n;
    if(a[1] >= x) {
    	return 1;
	}
	int mid;
    while(true){
        mid = (l + r) / 2;
        if(r == l + 1) {
        	return r;
		} else if(a[mid] == x) {
			return mid;
		} else {
			if (a[mid] >= x) r = mid;
	        else l = mid;
		}
    }
}
int main () {
	std::ios::sync_with_stdio(false);
	scanf("%d",&n);
    for(int i = 1;i <= n;i++){
    	scanf("%d",&a[i]);
        a[i] += a[i - 1];
    }
    scanf("%d",&m);
    int x;
    for (int i = 1;i <= m;i++) {
    	scanf("%d",&x);
    	printf("%d\n",findd(x));
	}
	return 0;
}

```


---

## 作者：chufuzhe (赞：0)

### 题意：
有 $n$ 个区间，每个区间长度为 $a_i$ ，有 $m$ 次询问，每次询问 $b_i$ 所在的区间编号。

### 思路：
每输入一个 $a_i$ ，就把 $a_i$ 个数赋值为 $i$ ，每次询问就只要输出下标为 $b_i$ 的值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000005]; //定义
int main()
{
	ios::sync_with_stdio(false);
	int n, cnt = 0; //cnt表示目前的下标
	cin >> n; //输入
	for(int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		for(int j = 1; j <= a; j++) {
			f[++cnt] = i; //把后面a个数赋值为i
		}
	}
	int m;
	cin >> m;
	while(m--) {
		int a;
		cin >> a;
		cout << f[a] << endl;
	}
	return 0;
}

```


---

