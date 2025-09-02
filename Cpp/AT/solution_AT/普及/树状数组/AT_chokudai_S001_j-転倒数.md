# 転倒数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

数列 $ a $ をバブルソートした時、スワップが何回発生するかを出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
0```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
21```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
114```

# 题解

## 作者：da32s1da (赞：16)

我们用树状数组完成此题。因为冒泡次数为每个数前面比他大的数之和。
```
#include<cstdio>
int n,m,ans;
int a[10005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&m);
		for(int j=m;j;j-=(j&(-j)))ans-=a[j];ans+=i-1;
		for(int j=m;j<=n;j+=(j&(-j)))a[j]++;
	}
	printf("%d\n",ans);
}
```

---

## 作者：Diamiko (赞：15)

## 这道题就是求逆序对的个数

### 什么是逆序对？

逆序对就是在数列中满足`i<j` 且`a[i]>a[j] `的一对数

我们都会冒泡排序，事实上在冒泡排序的过程中，我们就是不断找逆序对，交换他们

所以只要模拟一遍冒泡排序就可以统计出来逆序对的数量

根据逆序对的定义，很容易写出$O(n^2)$算法

```cpp
for(int i=1;i<=n;i++)
{
	for(int j=i+1;j<=n;j++)
	{
		if(a[i]>a[j])
		{
			ans++;
		}
	}
}
```
但一定会超时的，考虑更优方法

常用的求逆序对的方法有两种，一种是归并排序，一种是利用树状数组

我看了下现有的题解，大部分都是归并排序，有一个树状数组的题解不好理解，所以我写一个题解

### 树状数组求逆序对

#### 注意，此题解适合已有树状数组基础的朋友

我们可以先开一个大小为$a$的最大值的树状数组$c$

每当读入一个数时，我们可以用桶排序的思想，将`c[a[i]]`加上$1$

然后我们统计`c[1]-c[a[i]]` 的和ans

$ans - 1$（除掉这个数本身）就是在这个数前面有多少个数比它小

遍历 $i$ 从 $1$ 到 $n$ 我们只要用 `i-ans` 就可以得出前面有多少数比它大，也就是逆序对的数量

#### 但是！

#### 有时候，a的最大值可能到达你开c数组会直接炸掉的地步

那我们就要引入一个奇技淫巧——离散化

（在这里不详细介绍离散化，只是作为一个技巧来使用，如果想学习的建议去百度）

我们可以在读完数数据后对他进行从小到大排序

我们用排完序的数组的下标来进行运算

这样可以保证小的数依旧小，大的数依旧大

话不多说，上代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
struct Number
{
	int order;//序号
	int value;//值
}a[100005];
int lsh[100005];//离散化后的数组
int c[100005];
int n;
int lowbit(int x)//熟悉的lowbit
{
	return x&-x;
}
void update(int x,int k)//熟悉的增值函数
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		c[i]+=k;
	}
}
int getSum(int x)//熟悉的求和函数,求前面和多少就是小于它数的个数
{
	int res=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		res+=c[i];
	}
	return res;
}

/*
以上我相信不用多说，只要有树状数组的基础就可以明白
如果不熟悉的，其实没必要看这篇题解
*/
bool cmp(Number x,Number y)
{
	return x.value<y.value;
}
//排序函数
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].value;
		a[i].order=i;//记录原序
	}
	sort(a+1,a+n+1,cmp);//快排
	for(int i=1;i<=n;i++)
	{
		lsh[a[i].order]=i;//离散化的过程
	}
	long long ans=0;//不开longlong见祖宗
	for(int i=1;i<=n;i++)
	{
		update(lsh[i],1);
		ans+=i-getSum(lsh[i]);//减去小于的数即为大于的数即为逆序数
	}
	cout<<ans<<endl;
	return 0;
}
```
不过，据说这题不用离散化也能过，我没试
### 温馨提示：不开$long long$见祖宗
写题解不易，求多支持，谢谢各位

---

## 作者：冽酒灬忄 (赞：7)

这个题实质上是让你求逆序对

楼下用的树状数组求

那我就来一手归并排序求逆序对

~~双倍经验（P1908）~~
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
long long n,ans=0,rank[100001],a[100001];
void guibing(long long l,long long r){
	if(l==r)
		return ;
	long long mid=(l+r)/2;
	guibing(l,mid);
	guibing(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j])
			rank[k++]=a[i++];
		else{
			ans=ans+mid-i+1;//灵魂语句
			rank[k++]=a[j++];
		}
	}
	while(i<=mid){
		rank[k++]=a[i++];
	}
	while(j<=r){
		rank[k++]=a[j++];
	}
	for(int p=l;p<=r;p++)
		a[p]=rank[p];
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	guibing(1,n);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

### 典型的求逆序对。

拿到这题，我想到用冒泡排序模拟。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n-1;i++)
	  for(int j=i+1;j<=n;j++)
		if(a[i]>a[j]) {
			swap(a[i],a[j]);
			sum++;
		}
	cout<<sum<<endl;
	return 0;
}
```

结果。。。只有四个点AC

正解是**求逆序对**。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[999999],r[999999],ans=0;
void mer(int s,int t)
{
	if(s==t) return ;
	int mid=(s+t)/2;
	mer(s,mid);
	mer(mid+1,t);
	int k=s,i=s,j=mid+1;
	while(i<=mid&&j<=t) {
		if(a[i]>a[j]) {
			r[k]=a[j];
			k++;
			j++;
			ans+=mid-i+1;
		} else {
			r[k]=a[i];
			k++;
			i++;
		}
	}
	while(i<=mid) {
		r[k]=a[i];
		i++;
		k++;
	}
	while(j<=t) {
		r[k]=a[j];
		k++;
		j++;
	}
	for(int q=s; q<=t; ++q)
		a[q]=r[q];

}
int main() {
	long long n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	mer(1,n);
	cout<<ans<<endl;
	return 0;
}
```

别忘开氧哦（逃

---

## 作者：tommychen (赞：1)

双倍经验！([P1908](https://www.luogu.com.cn/problem/P1908))
### 题面
给定一个数列a，进行冒泡排序，求总共进行多少轮操作。
### 思路
之所以要进行冒泡排序，是因为后面一个数比前面一个数小。这时我们就知道当$a_i$ $\gt$ $a_j$ 且$i$ $\lt$ $j$时，需要进行一次冒泡排序。

这是我们就会发现：上面的一坨~~柿子~~不正好就是逆序对么！

由此,我们就可以把题目转化成：求给定数列中，有多少对逆序对。

发现了这个，我们就可以用逆序对做题了。
### 代码
这里给出两种方法。

树状数组求逆序对：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
int n;
int t[500010],r[500050];
struct node{
	int num,val;
}a[500010];
int cmp(node a,node b){
	if(a.val==b.val)return a.num<b.num;
	return a.val<b.val; 
}
int ask(int x){
	int ans=0;
	for(;x;x-=(x&-x)){
		ans+=t[x];
	}
	return ans;
}
void add(int x,int y){
	for(;x<=n;x+=(x&-x))t[x]+=y;
}
signed main(){

	int sum=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		r[a[i].num]=i;
	}
	for(int i=1;i<=n;i++){
		add(r[i],1);
		sum+=i-ask(r[i]);
	}
	cout<<sum<<endl;
	return 0;//完结撒花！✿✿ヽ(°▽°)ノ✿
}
```
合并排序求逆序对：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=5e5+5;
int a[maxn],b[maxn],n;
int sum=0;
void msort(int s,int t){
	if(s==t){
		return;
	}
	int mid=(s+t)/2;
	msort(s,mid);
	msort(mid+1,t);
	int i=s;
	int j=mid+1;
	int k=s;
	while(i<=mid&&j<=t){
		if(a[i]<=a[j]){
			b[k++]=a[i++];
		}else{
			b[k++]=a[j++];
			sum+=(long long)mid-i+1;
		}
	}
	while(i<=mid){
		b[k]=a[i];
		k++;
		i++;
	}
	while(j<=t){
		b[k]=a[j];
		k++,j++;
	}
	for(int i=s;i<=t;i++){
		a[i]=b[i];	
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	msort(1,n);
	cout<<sum<<endl;
	return 0;//完结撒花！✿✿ヽ(°▽°)ノ✿
}
```


---

## 作者：Graphcity (赞：1)

分析一下题意吧：

在冒泡排序中，每当一个数的前面某一个数比它大的时候，就会进行一次交换。所以，求冒泡排序的总交换次数，就是求这个数列的**逆序对**个数。

逆序对的个数可以使用树状数组来求，时间复杂度 $O(n\log_2n)$ 。

不过，需要注意的是：

- 此题中数字的范围较大，需要开 long long 。
- 为了避免使用过多的空间，请先**离散化**。
- AtCoder 的特性：输出后面一定要空行。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Maxn int(1e5)
#define lowbit(x) (x&-x)
using namespace std;

ll n,ans;
ll t[Maxn+5];

inline void Update(ll x,ll y)//更新
{
	ll now=x;
	while(now<=Maxn)
	{
		t[now]+=y;
		now+=lowbit(now);
	}
}
inline ll Count(ll x)//查询
{
	ll now=x,cnt=0;
	while(now>0)
	{
		cnt+=t[now];
		now-=lowbit(now);
	}
	return cnt;
}

struct Number
{
	ll k,id,rank;
} num[Maxn+5];

namespace Discrete//离散化（这个方法可能有点不一样）
{
	inline bool cmp1(Number x,Number y)
	{
		return x.k<y.k;
	}
	inline bool cmp2(Number x,Number y)
	{
		return x.id<y.id;
	}
	
	void Run()
	{
		ll nowrank=0;
		sort(num+1,num+n+1,cmp1);
		for(register ll i=1;i<=n;++i)
		{
			if(i==1 || num[i].k>num[i-1].k)
				++nowrank;
			num[i].rank=nowrank;
		}
		sort(num+1,num+n+1,cmp2);
	}
} 

int main()
{
	scanf("%lld",&n);
	for(register ll i=1;i<=n;++i)
	{
		ll a;
		scanf("%lld",&a);
		num[i].k=a;
		num[i].id=i;
	}
	Discrete::Run();
	for(register ll i=1;i<=n;++i)
	{
		ll a=num[i].rank;
		ans+=(Count(Maxn)-Count(a));
		Update(a,1);
	}
	printf("%lld\n",ans);
    return 0;
}

```


---

## 作者：Doubeecat (赞：1)

这一题跟[P1908](https://www.luogu.org/problemnew/show/P1908)是双倍经验  
可以看出题面中的“进行冒泡排序。 输出总共进行多少次交换”是一个很明显的逆序对模型  
因为逆序对的定义是：序列中$a_i>a_j$且$i<j$的有序对  
显然，这样的一组逆序对我们就需要进行一次冒泡排序  
所以最后的次数就是冒泡排序的次数  
使用归并排序求逆序对代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1000001],r[1000001],n;
long long ans;
void msort(int s,int t)
{
    if(s==t) 
        return ;
    int mid=(s+t)/2;
    msort(s,mid);
    msort(mid+1,t);
    int i=s,j=mid+1,k=s;
    while(i<=mid&&j<=t){
        if(a[i]<=a[j])
            r[k]=a[i],k++,i++;
        else{
            r[k]=a[j],k++,j++;
            ans += mid-i+1;
        }
    }
    while(i<=mid)
        r[k]=a[i],k++,i++;
    while(j<=t)
        r[k]=a[j],k++,j++;
    for(int i=s;i<=t;i++)
        a[i]=r[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    msort(1,n);
    cout << ans;
    return 0;
}
```

---

## 作者：fjy666 (赞：0)

## 0x01 思路
经典的[**求逆序对**](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554?fr=aladdin)问题。  
我们都知道归并排序，可以考虑怎么把归并排序的思路应用到求逆序对上。  
在归并排序中，先将左子序列排序，再将右子序列排序，最后合并。  
那么，假设归并排序时已经求出左子序列和右子序列的逆序对个数之和，那么我们只要统计 **横跨** 左右子序列的逆序对个数即可。  
很简单：每当有一个右子序列的数被放到辅助数组中时，左子序列的剩下所有数 **都比这个数大** ，直接统计即可。  
这样可以保证：
- 不重  
每个逆序对 $(a_i,a_j)$ 只会被 $a_j$ 统计一次。
- 不漏  
每个逆序对 $(a_i,a_j)$ 肯定被 $a_j$ 统计。

时间复杂度：$\Theta(n\log n)$，和归并排序的复杂度相同。

## 0x02 代码
```cpp
#include <cstdio>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
using namespace std;
const int kN = 1005000;
int a[kN],b[kN];
ll cnt;
void mergeSort(int L,int R){
	if(L == R)return;
	int mid = L+R>>1;
	mergeSort(L,mid);
	mergeSort(mid+1,R);
	int pL = L,pR = mid + 1;
	_rep(i,L,R){
		if(pL <= mid && (pR > R || a[pR] >= a[pL]))b[i] = a[pL++];
		else b[i] = a[pR++],cnt += mid - pL + 1;
	}
	_rep(i,L,R)a[i] = b[i]; 
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		_rep(i,1,n)
			scanf("%d",a+i);
		cnt = 0;
		mergeSort(1,n);
		printf("%lld\n",cnt);
	}
    return 0;
}
```

---

## 作者：cjZYZtcl (赞：0)

## 树状数组的练手题
由于是冒泡排序，我们这里考虑以下方法的冒泡：
```cpp
for(int i = 1; i < n; i++){
	for(int j = n - i; j >= 1; j--){
		if(b[j] > b[j + 1]) b[0] = b[j], b[j] = b[j + 1], b[j + 1] = b[0];
	}
}
```
我们可以发现，对于每一个位置，只有它后面且比它小的位置往前移才会与它产生交换。

所以我们可以从后往前枚举每一个数字，用以值为关键字的树状数组维护，每枚举到一个位置就放进树状数组，然后求出树状数组中比它小的位置的总和，累加进sum里。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, sum;
int a[100005], tree[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
int lowbit(int x){
	return x & -x;
}
void add(int x){
	while(x <= n){
		tree[x]++;
		x += lowbit(x);
	}
}
int query(int x){
	int y = 0;
	while(x){
		y += tree[x];
		x -= lowbit(x);
	}
	return y;
}
signed main(){
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = n; i >= 1; i--){
		add(a[i]);
		sum += query(a[i] - 1);
	}
	write(sum);
}
```


---

## 作者：thhxxx (赞：0)

输入序列a，进行冒泡排序。 输出总共进行多少次交换。由题意可知~~本题可将数组进行冒泡排序，设变量cnt用于计数，每次交换cnt++~~。(TLE警告)


我们知道冒泡排序的时间复杂度为 ```O(n^2)``` 显然在这题会超时。。。。

于是我们可以利用**归并排序**的性质去求逆序对，时间复杂度被优化到了 ```O(nlogn)```，本题可过。

写法和归并排序大同小异，没学归并排序的同学可以先去学习下再回来看这题，只不过有些小细节要注意下。(记得开long long，~~不然整题白给~~)

ac程序
------------
 

```
#include <iostream>
#include <cstdio>
using namespace std;
const int N=100010;
int a[N],tmp[N],n;

long long merge_find(int l,int r)//
{
    if (l>=r) return 0;

    int mid = l+r >> 1;
    long long cnt=merge_find(l,mid)+merge_find(mid+1,r);//递归的手法去拆分区间，总的逆序对数等于左半区间的逆序对数与右半区间的逆序对数之和
    int k=0,i=l,j=mid+1;//i指向左半区间的头部，j指向右半区间的头部
    while (i<=mid&&j<=r)
    {
        if (a[i]<=a[j])
        {
            tmp[k++]=a[i++];
        }
        else
        {
            tmp[k++]=a[j++];
        cnt+=mid-i+1;//若右半区间的a[j]大于左半区间的a[i]，显然两个数是逆序对，数量为mid-i+1
        }
    }
    while (i<=mid) tmp[k++]=a[i++];
    while (j<=r) tmp[k++]=a[j++];
    for (int i=l,j=0;i<=r;i++,j++)
    {
        a[i]=tmp[j];
    }
    return cnt;
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)//读入数据
    {
        scanf("%d",&a[i]);
    }
    printf("%lld",merge_find(0,n-1));//记得long long数输出要%lld
    return 0;
}
```

---

