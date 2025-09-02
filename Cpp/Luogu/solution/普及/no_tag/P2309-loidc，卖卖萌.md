# loidc，卖卖萌

## 题目背景

loidc 萌萌哒。

他最近一直在靠卖萌追求他的真爱——vivym，经过几轮攻势后 vivym 酱眼看就要被他所攻略。擅长数据结构的 vivym 决定利用强大的数据结构之力帮助自己逃脱。

## 题目描述

vivym 给了 loidc 一串阿拉伯数字。他将一个数串的每个数字之和定义为该数串的数串和，vivym 要求 loidc 求出数串中有多少个子串的数串和为正数。他想了半天总是解决不好，于是他便将这一棘手的问题交给了编程能力极强的你，他希望你能在 1 s 内解决。不然 vivym 就要闪现过墙幽灵疾步跑掉了。

## 说明/提示

- 对于 $30\%$ 的数据：$n\leq 10^3$；
- 对于 $100\%$ 的数据：$1 \leq n\leq 10^5$。

题目读入的其他变量均介于 $-100\ldots 100$ 之间。

## 样例 #1

### 输入

```
3
8 -9 2
```

### 输出

```
3```

# 题解

## 作者：Otomachi_Una_ (赞：10)

## 题目简述
- 给定长度为 $n$ 的数列 $a$。
- 求有多少对 $(l,r)$ 使得 ：
$$\sum_{i=l}^ra_i>0$$

## 题目分析

假设 $s_i$ 为前缀和，本题即求有多少对 $(l,r)$ 使得： 

$$l<r,s_l<s_r$$

这显然是正序对个数，直接归并求解即可（如果不会逆序对的同学可以[点这里](https://www.luogu.com.cn/problem/P1908)）。

## 代码

```cpp
#include<iostream>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int n,a;
int s[MAXN];
int t[MAXN];
ll ans=0;
void msort(int l,int r){
	if(l==r)
		return;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	int p=l,q=mid+1,k=l;
	while(p<=mid&&q<=r){
		if(s[p]>=s[q])
			t[k++]=s[q++]; 
		else
			t[k++]=s[p++],ans+=r-q+1;
	}
	while(p<=mid)
		t[k++]=s[p++];
	while(q<=r)
		t[k++]=s[q++];
	for(int i=l;i<=r;i++)
		s[i]=t[i];
	return; 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		s[i]=s[i-1]+a;
	}
	msort(0,n);
	//for(int i=1;i<=n;i++)
	//	cout<<s[i]<<" ";
	cout<<ans;
}
```


---

## 作者：Mr_QwQ (赞：9)

终于AC的我来发题解啦！本题第一个题解，占坑~

首先我们会想到什么？暴力【滑天下之大稽】$O(n^3)$，你给我弄一个试试。

我们很容易想到另外一种方法：对于数组a，计算出前缀和$s_i$，之后一遍二重循环就可以计算子段和。这样是一个很大的进步，然而仍然不能通过。

那么我们该怎么办呢？

让我们看一下，我们实质上要找到数对$(i,j)$的组数，它们都满足：

$s_i-s_j<0,1\leq j\leq n,0\leq i\leq n-1$

移项，得$s_i<s_j$。

所以……这不是一个裸~~逆序对~~正序对吗……

读入时，将所有数值取其相反数，跑逆序对即可。

另外要注意：因为i可以为0（就是从开头开始的一段区间），最后还要加上$s_i$中负数的个数。

~~因为逆序对问题是普及-的，所以这题我给了普及-。~~

刨掉逆序对以后的代码如下：

```cpp
        scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];
        a[i-1]=-s[i-1];
        if(a[i-1]<0)++ans;
    }
    a[n]=-s[n];
    if(a[n]<0)++ans;
    merge(1,n);
    printf("%lld",ans);
    return 0;
```
祝大家能够从中得到启发。再见~~


---

## 作者：zhengrunzhe (赞：7)

目前题解里只有归并排序的 提供一个树状数组

子串和想到前缀和

sum[l,r]=sum[r]-sum[l-1] (l<=r)

若sum[l,r]>0则sum[r]-sum[l-1]>0即sum[r]>sum[l-1]

对sum数组求正序对即可

```cpp
#include<cstdio>
#include<algorithm>
using std::sort;
using std::unique;
using std::lower_bound;
typedef long long ll;
const int N=1e5+10;
int sum[N],sm[N],n,tot;
ll ans;
class Binary_Index_Tree
{
	private:
		int sum[N];
		inline const int lowbit(int x)
		{
			return x&-x;
		}
	public:
		inline const void insert(int x)
		{
			for (;x<=tot;x+=lowbit(x))sum[x]++;
		}
		inline const int query(int x)
		{
			int y=0;
			for (;x;x-=lowbit(x))y+=sum[x];
			return y;
		}
}bit;
int main()
{
	scanf("%d",&n);
	for (int x,i=1;i<=n;i++)scanf("%d",&x),sm[i]=sum[i]=sum[i-1]+x;
	sort(sm,sm+n+1);tot=unique(sm,sm+n+1)-sm;
	for (int p,i=0;i<=n;i++)
		p=lower_bound(sm,&sm[tot-1]+1,sum[i])-sm+1,
		ans+=bit.query(p-1),
		bit.insert(p);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Remake_ (赞：2)

考虑到区间和能够转换为前缀和相减，所以我们可以先把前缀和预处理出来，转化为求其顺序对数量。

以为又要写归并了，一看数据，$\text{1e5}$，只会用```vector```瞎水的我啪的一下就站起来了，很快啊：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<long long> v;
long long n, a, qzh, ans;
int main()
{
    cin >> n;
    v.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        qzh += a;
        ans += lower_bound(v.begin(), v.end(), qzh) - v.begin();
        v.insert(lower_bound(v.begin(), v.end(), qzh), qzh);
    }
    cout << ans;
}
```


---

## 作者：lmrttx (赞：1)

~~介绍详细的~~本文注重讲解如何把题目转化成求逆序对问题和如何用归并求解逆序对。请先掌握[前缀和](https://www.cnblogs.com/-Ackerman/p/11162651.html)。


------------

暴力枚举三个点，时间 $O(n^3)$,肯定会爆炸。

字串的每一个数之和就相当于**区间之和**，当区间之和为正数时，就符合条件。于是用前缀和建立一个数组 $b$。用这个数组跑一遍循环，因为前缀和中,$b[r]-b[l-1]$ 表示区间 $[l,r]$ 的区间和，所以时间为 $O(n^2)$。因为 $n$ 最大为 1e5,所以也会超时。

那怎样和年轻人一样快呢？？？

颓柿子吧。

当满足这个式子的时候，不能计入答案：

$$b[r]-b[l-1]<0$$

变化得：

$$b[r]<b[l-1]$$

于是题目变成了正序对。

但是蒟蒻只会逆序对，怎么办呢？？？

想到优先队列中小根堆和大根堆的转化和不等式的性质，只要将数乘上-1，再求逆序对，就不影响答案了。



------------


到此思路完结。实现我们靠归并，因为~~我发现归并的题解较少~~树状数组的代码更长一些。不过本文末尾还是会贴上树状数组求逆序对的代码的。会用归并求逆序对的读者可以自行跳过这块。


归并排序的基本思路就是分而治之。就是将一个数组先分解成一半，再分解成四分之一，一直到只剩叶节点，即每一段都只有一个数时，合并，并在合并时交换数据位置。

归并排序需要辅助数组。

图解：

![](https://pic3.zhimg.com/80/v2-a06fa28500a357b6032aa0e58e3e37bf_qhd.jpg)

由于逆序对是**大的在前，小的在后**，所以合并时，交换次数就是逆序对个数（此时归并排序是按从小到大进行排序的）。

代码：

```cpp
void msort(int l,int r){
	if(l==r){
		return;
		//分解成一个数时返回 
	}
	int mid=(l+r)>>1;
	//取区间中点
	msort(l,mid);msort(mid+1,r);//递归
	int i=l,j=mid+1,k=r;//准备合并
	while(i<=mid&&j<=r){//这个是边界条件
	//a为原数组，r为辅助数组，r最后就是原数组排序后的数列 
		if(a[i]<=a[j]){
			r[k]=a[i];k++;i++;
		}else {//从小到大 
			r[k]=a[j];k++;j++;
			ans+=mid-i+1;//统计逆序对数量 
		}
	} 
	while(i<=mid){
		r[k]=a[i];k++;i++;
	}
	while(j<=r){
		r[k]=a[j];k++;j++;
	}
	//分别处理左右剩余的部分 
	//最后可以根据需要，看看要不要把r数组的值赋给a数组 
}
```

题目就这样做完啦！！！


------------

福利：用树状数组求逆序对数量的代码。题目是[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)，偷偷地告诉你，这是一道双倍经验的题目！

```cpp
#include<bits/stdc++.h>
using namespace std;
int lowbit(int x){return x&-x;}
#define maxn 500010
#define int long long
int a[maxn],b[maxn],tree[maxn],ans,n;
bool cmp(int x,int y){
	return a[x]==a[y] ? x>y :a[x]>a[y];
}
int find_(int x){
	int res=0;
	for(int i=x;i>0;){
		res+=tree[i];
		i-=lowbit(i);
	}
	return res;
}
void change(int x){
	for(int i=x;i<=n;){
		tree[i]++;
		i+=lowbit(i);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=i;
	}
	sort(b+1,b+n+1,cmp);
	for(register int i=1;i<=n;i++){
		change(b[i]);
		ans+=find_(b[i]-1);
	}
	cout<<ans;
	return 0;
}
```

可以看出，用树状数组求逆序对的思路和归并一样。





------------

谢谢阅读！！！如果本文有不足，可以再评论区指出qwq！ 

---

## 作者：syf2008 (赞：1)

本蒟蒻来发题解啦！

这题做法有3种

1. 正序对+前缀和
1. 树状数组1
1. 树状数组2

如果不会逆序对，请看[这里](https://www.luogu.com.cn/blog/shenyufan2008/ni-xu-dui)

思路：
读入时，将所有数值取其相反数，跑正序对即可。

后2种题解里有，我就不写了

下面上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005],s[100005],tmp[100005];
long long que_sort(int l,int r)//逆序对的变形——正序对
{
	if(l==r)//逆序对是>=返回0，正序对是==返回0。
	return 0; 
	int mid=l+r>>1;
	long long ans=que_sort(l,mid)+que_sort(mid+1,r);
	int k=l,i=l,j=mid+1;
	while(i<=mid&&j<=r)
	{
	if(s[i]>s[j])//正序对找s[i]>s[j],逆序对找s[i]<=s[j]。其余和逆序对一样。
	{
	ans+=mid-i+1;
	tmp[k]=s[j++];
	}
else tmp[k]=s[i++];
	k++;
	}//解释下这段,如果q[i]>q[j],意味着q[i]及其之后的值都大于q[j]，所以t=mid-i+1。
	while(i<=mid)
	tmp[k++]=s[i++];
	while(j<=r)
	tmp[k++]=s[j++];
	for(int i=l;i<=r;i++)
	s[i]=tmp[i];
	return ans;
}
int main()
{
	long long n,ans=0;//不开long long 见祖宗
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>a[i];
	s[0]=a[0];
	for(int i=1;i<n;i++)
	s[i]=s[i-1]+a[i];//前缀和处理
	for(int i=0;i<n;i++)
	{
	s[i]=-s[i];因为负负得正，所以s[i]是正数就变负数，s[i]是负数就变正数。
	if(s[i]<0)
	ans++;
	}//计算有几个负数，加上
	cout<<que_sort(0,n-1)+ans<<endl;//输出结果
	return 0;
}
```

---

## 作者：破忆 (赞：1)

### 题目大意
求和为正数的连续数列的数量


------------

### 分析
首先考虑暴力枚举

枚举起点，终点，再逐个相加，O（n³）

在这个基础上优化，第三层循环可以用前缀和优化下来

也就是求前缀和相减为正数的对数，仍然需要O（n²）的复杂度

设s[i]表示a[1]+a[2]...+a[i]

就是求s[i]<s[j]（0<=i<j<=n）的对数

也就是求正序对的数量


------------

### 解法
二分排序求正序对


------------

### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn=1e5+5;
int n;
int s[maxn],p[maxn];
LL ans;//注意答案可能会很大
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void msort(int L,int R){//递归写法
	if(L>=R) return;
	int mid=L+R>>1;
	msort(L,mid),msort(mid+1,R);//把当前区间分成2个小区间，暂且称为左和右，假设小区间已经排序完成
	for(int i=L;i<=R;i++) p[i]=s[i];//先用辅助数组p存下s
	for(int i=L,j=mid+1,k=L;k<=R;k++){
		if(i<=mid&&(j>R||p[i]<p[j])) ans+=R-j+1,s[k]=p[i++];//左边没取完并且右边取完了或者左边小，此时第i个数就可与右边R-j+1个数可以组成正序对
		else s[k]=p[j++];//否则取右边
	}
   //这样[L,R]就完成了排序
}
int main(){
	freopen("P2309.in","r",stdin);
	freopen("P2309.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) s[i]=s[i-1]+read();//前缀和
	msort(0,n);//注意从0到n
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：「ゲームとOI」 (赞：1)

上一个题解代码貌似没附求逆序对的代码部分，蒟蒻补充：
思路很~~-简单-~~难啦
简单来说
就是在归并排序的时候出现逆序（下一个放入的是右侧时）
把左侧余剩的数据数量（ans += mid - lp + 1;）加上
也就是指当前所选择的右侧数据与所有左侧数据成逆序对
就这么~~-简单-~~难
代码很~~短~~  长

```cpp
#include <bits/stdc++.h>
using namespace std;

int num[100005];
int fir[100005];
int t[100005];

long long MergeSort(int l,int r) {
	int mid = (l + r) / 2;
	int p = l,lp = l,rp = mid + 1;
	long long ans = 0;
	if(l == r) return 0; 
	ans = MergeSort(l,mid) + MergeSort(mid + 1,r);
	while(lp <= mid && rp <= r) {
		if(fir[lp] > fir[rp]) {
			ans += mid - lp + 1;
			t[p] = fir[rp ++];
		}
		else {
			//ans += r - rp + 1;
			t[p] = fir[lp ++];
		}
		p ++;
	}
	while(lp <= mid) {
		t[p ++] = fir[lp ++];
	}
	while(rp <= r) {
		t[p ++] = fir[rp ++];
	}
	for(int i = l;i <= r;i ++) {
		fir[i] = t[i];
	}
	return ans;
}

int main(void) {
	long long n,ans = 0;
	cin >> n;
	for(int i = 0;i < n;i ++) {
		cin >> num[i];
	}
	fir[0] = num[0];
	for(int i = 1;i < n;i ++) {
		fir[i] = fir[i - 1] + num[i];
	}
	for(int i = 0;i < n;i ++) {
		fir[i] = -fir[i];
		if(fir[i] < 0) ans ++;
	}
	cout << MergeSort(0,n - 1) + ans << endl;
	return 0;
}
```

---

## 作者：Иɔlɔ (赞：1)

考虑到所有偶数点都有棋子那么一定能跳到最右边。

### 第一问

考虑三种情况：

- 有不少于两个红格子连着。可以一直在行动中放，从而到达任意一个格子，过程可自行模拟。第一问答案为 $0$。注意连着的两个红格子不能有 $1$。
- 一个白格子一个红格子。在红格子上放一个棋子就可以用白格子上的棋子跳过去，代价为 $1$。
- 两个白格子，在偶数点上放是最优的，代价为 $1$。

累加这几种情况的答案即可。

### 第二问

- 如果这个点能被红格子上的棋子跳到，从红格子去跳。
- 如果不能，就放棋子。

如果只有一个情况为第一种情况，可以暴力更新。

否则，求这个点被跳到的最小代价。发现第一种情况的代价是斐波那契数列，从左至右从右至左各更新一次即可。

时间复杂度 $O(n)$。

$\text{Code}$：

```cpp
const int N = 1005;

int n, x, cnt;
ll dp[N];
ll inf, sum;

int main() {
	memset(dp, 0x3f, sizeof dp);
	inf = dp[1];
	qread(n, x);
	rep(i, 2, n) { // for(int i = 2; i <= n; i++)
		qread(x);
		if(x) dp[i] = 1;
	}
	rep(i, 2, n) To_min(dp[i], dp[i - 1] + dp[i - 2]);
	per(i, n, 2) To_min(dp[i], dp[i + 1] + dp[i + 2]); // for(int i = n; i >= 2; i--)
	for(int i = 2; i <= n; i += 2) dp[i] == inf ? ++cnt : sum += dp[i];
	printf("%d\n%lld\n", cnt, sum);
 	return 0;
}
```


---

## 作者：UnyieldingTrilobite (赞：0)

提供树状数组的另一种做法，和归并排序/可持久化线段树/二分查找+树状数组/离散化一样珂以处理值域更大的情况。

首先，题目珂以转化为求前缀和“顺序对”数量。

为什么这么转化可行其他dalao们已经说得很清楚了，不再赘述。

“顺序对”珂以用树状数组解，不会的珂以右转[这里](https://www.luogu.com.cn/problem/P1908)。

然后，为了缩小值域，**我们按照值来排序，把下标插入树状数组。**

排序时固然珂以手写struct,但~~像我一样~~想偷懒的珂以用STL pair.

注意：第一关键字过后,pair是按照顺序排第二关键字（下标）的。

但按照这里的需求应该逆序排（想想为什么？）。

缩以存取时取个相反数。

Over.

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long//珂能爆int
using namespace std;
int bit[1000009];
pair<int,int>k[1000009];
int n;
inline void insert(int x){
	for(;x<=n+1;x+=x&-x)++bit[x];
}
inline int query(int x){
	int ret=0;
	for(;x;x&=x-1)ret+=bit[x];
	return ret;
}
int ans;
signed main(){
	cin>>n;
	k[1]=make_pair(0,-1);//前0项前缀和，不加的话无法识别前缀和为正的情况
	for(int i=1,s;i<=n;++i)cin>>s,s+=k[i].first,k[i+1]=make_pair(s,-i-1);
	sort(k+1,k+n+2);//按值排序
    for(int i=1;i<=n+1;++i){
		insert(-k[i].second);
		ans+=query(-k[i].second-1);
	}
	cout<<ans<<endl;
	return 0;
}
```
好了，祝大家AC！

最后~~厚颜无耻地~~宣传一波[blog](https://www.luogu.com.cn/blog/2007100723874wxz/)和[神奇的编程语言（~~求个赞~~）](https://www.luogu.com.cn/blog/2007100723874wxz/define)。

---

## 作者：梧桐灯 (赞：0)

我的思路不太一样……题目是让我们求$sum[r] - sum[l - 1] > 0$的$(l,r)$数，那么对于每一个sum[r]，我们都可以查询前面前缀和中**严格小于**它的数的个数。

于是树状数组的做法就自然出来了。

注：下标可能为负，加上一个数即可(我取得是${10}^7+1$)，视题目范围而定，如果太大就用~~平衡树~~动态开点线段树维护一下。

代码：（树状数组）

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
inline void read (int& s) {
	s = 0; int f = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') {if (c == '-') f = 1; c = getchar ();}
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	s = f ? -s : s; return ;
}

const int N = 100003, M = 20000009;
int n, a[N];
int sum[M];
ll ans;

inline void add (int x, const int y) {
	while (x < M) {
		sum[x] += y;
		x += x & (x ^ x - 1);
	}
	return ;
}

inline int ask (int x) {
	int s = 0; while (x) {
		s += sum[x];
		x &= x - 1;
	}
	return s;
}

int main () {
	read (n); int i, x, now = 0;
	add (10000001, 1);
	for (i = 1; i <= n; ++i) {
		read (x);
		now += x;
		ans += ask (now + 10000000);
		add (now + 10000001, 1);
	}
	cout << ans << '\n';
	return 0;
}

```

动态开点线段树（由于是单点修改不需要传标记也挺方便QwQ）：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
inline void read (int& s) {
	s = 0; int f = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') {if (c == '-') f = 1; c = getchar ();}
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	s = f ? -s : s; return ;
}

const int N = 100003, M = 20000009, inf = 100000000;
int n, a[N], k;
int sum[M], root, lc[M], rc[M];
ll ans;

void chan (int& v, const int L, const int R, const int x) {
	if (!v) v = ++k;
	if (L == R) {
		++sum[v];
		return ;
	}
	int mid = L + R >> 1;
	if (mid >= x) chan (lc[v], L, mid, x);
	else chan (rc[v], mid + 1, R, x);
	sum[v] = sum[lc[v]] + sum[rc[v]];
	return ;
}

int ask (const int v, const int L, const int R, const int x, const int y) {
	if (!v) return 0;
	if (L >= x && R <= y) return sum[v];
	int mid = L + R >> 1, t = 0;
	if (mid >= x) t = ask (lc[v], L, mid, x, y);
	if (mid < y) t += ask (rc[v], mid + 1, R, x, y);
	return t;
}

int main () {
	read (n);
	int i, x, now = 0;
	chan (root, -inf, +inf, 0);
	for (i = 1; i <= n; ++i) {
		read (x);
		now += x;
		ans += ask (root, -inf, +inf, -inf, now - 1);
		chan (root, -inf, +inf, now);
	}
	cout << ans << '\n';
	return 0;
}
```


---

