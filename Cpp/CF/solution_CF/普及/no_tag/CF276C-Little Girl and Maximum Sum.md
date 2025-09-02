# Little Girl and Maximum Sum

## 题目描述

The little girl loves the problems on array queries very much.

One day she came across a rather well-known problem: you've got an array of $ n $ elements (the elements of the array are indexed starting from 1); also, there are $ q $ queries, each one is defined by a pair of integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . You need to find for each query the sum of elements of the array with indexes from $ l_{i} $ to $ r_{i} $ , inclusive.

The little girl found the problem rather boring. She decided to reorder the array elements before replying to the queries in a way that makes the sum of query replies maximum possible. Your task is to find the value of this maximum sum.

## 样例 #1

### 输入

```
3 3
5 3 2
1 2
2 3
1 3
```

### 输出

```
25
```

## 样例 #2

### 输入

```
5 3
5 2 4 1 3
1 5
2 3
2 3
```

### 输出

```
33
```

# 题解

## 作者：AKPC (赞：8)

### 思路
给出 $a$ 数组，每次操作都是询问 $\displaystyle\sum_{i=l}^ra_i$ 的值，但是在最开始，可以给 $a$ 数组进行一次任意的排列，使得每次操作返回值的总和最大。

这显然是一道贪心题。每次询问，区间 $[l,r]$ 的值在询问总和显然会加一次，显然只有在加的次数多的位置放大数，才会让总和更大。

但是 $l,r\leq2\times10^5$，所以暴力是不可行的，~~而且 CF 没有部分分~~。那么显然能想到差分，设一个差分标记数组，给 $l$ 的位置差分标记加 $1$（一个左括号）,$r$ 的位置差分标记减 $1$（一个右括号）。加完之后给差分标记数组差分一遍得到原标记数组。根据上一段的贪心原则，排个序，给 $a$ 数组也排个序，然后计算答案即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[200001],tip[200001],l,r,ans;
signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for (int i=1;i<=m;i++) cin>>l>>r,tip[l]++,tip[r+1]--;
	for (int i=1;i<=n;i++) tip[i]+=tip[i-1];
	sort(tip+1,tip+n+1);
	for (int i=1;i<=n;i++) ans+=tip[i]*a[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：endswitch (赞：3)

简述题意：

给定一个序列和若干次询问，可以将序列重新排列，问排列后的询问总和最大值。

思路：

贪心+树状数组。维护一个初始元素均为 $0$ 的序列对于每个询问将 $[l,r]$ 这个区间加一。然后将两个序列都从大到小排序，把元素一一对应求乘积之和即可。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int lowbit(int x) {return x&-x;}
const int N=2e5+5;
int n,q,ans,a[N],c[N],t[N<<2],l,r;
inline void add(int x,int k) {
	for(;x<=n;x+=lowbit(x))
		t[x]+=k;
}
inline int gts(int x) {
	int res=0;
	for(;x;x-=lowbit(x))
		res+=t[x];
	return res;
}
signed main() {
	ios_base::sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,greater<int>());
	while(q--) cin>>l>>r,add(l,1),add(r+1,-1);
	for(int i=1;i<=n;i++)
		c[i]=gts(i);
	sort(c+1,c+1+n,greater<int>());
	for(int i=1;i<=n;i++)
		ans+=(c[i]*a[i]); 
	cout<<ans;
	return 0;
}
```


---

## 作者：Light_Star_RPmax_AFO (赞：3)



## 题目描述

给出一个序列 $a$ 和 $q$ 次询问，每次询问给出 $l$ 和 $r$，得到 $\sum_{i = l}^ra_i$，求总询问的和最大值。

## 思路

要所有询问总和最大，也就是说我们要让大的数出现次数最多。

那么我们就把问题转化为了哪个位置出现的最多，又来到了区间修改。

~~我可不会告诉你会有机房大佬写树状数组~~。

谈到区间修改，最简单的还是**差分**，于是我们使用差分查找最大出现的次数。 

把更大的放在出现次数更多的位置上。

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define Fup(i,j,k) for(int i = j;i <= k;++i)
#define Fdn(i,j,k) for(int i = j;i >= k;--i)
using namespace std;

inline int read()
{
    int x = 0,f = 1;char ch = getchar();
    while (ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}

void write(int x)
{
    if(x < 0)
       putchar('-'),x =- x;
    if(x > 9)
       write(x / 10);
    putchar(x % 10 + '0');
    return;
}

bool cmp(int x,int y){
    return x > y;
}

int a[200010],sum[200010];

signed main(){
    int n = read(),q = read();
    for(int i = 1;i <= n;i++)
        a[i] = read();
    for(int i = 1;i <= q;i++){
        int l = read(),r = read();
        sum[l]++,sum[r + 1]--;
    }
    for(int i = 1;i <= n;i++){
        sum[i] += sum[i - 1];
    }
    sort(a + 1,a + 1 + n,cmp);
    sort(sum + 1,sum + 1 + n,cmp);
    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans += a[i] * sum[i];
    }
    write(ans);
    return 0;
}
```
[XCY_OIER](https://www.luogu.com.cn/user/773915) 的树状数组代码。

# AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int lowbit(int x) {return x&-x;}
const int N=2e5+5;
int n,q,ans,a[N],c[N],t[N<<2],l,r;
inline void add(int x,int k) {
	for(;x<=n;x+=lowbit(x))
		t[x]+=k;
}
inline int gts(int x) {
	int res=0;
	for(;x;x-=lowbit(x))
		res+=t[x];
	return res;
}
signed main() {
	ios_base::sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,greater<int>());
	while(q--) cin>>l>>r,add(l,1),add(r+1,-1);
	for(int i=1;i<=n;i++)
		c[i]=gts(i);
	sort(c+1,c+1+n,greater<int>());
	for(int i=1;i<=n;i++)
		ans+=(c[i]*a[i]); 
	cout<<ans;
	return 0;
}
```

---

## 作者：Little09 (赞：3)

贪心地想，肯定是**给询问多的位置更大的数**。所以先把数排序，对于每个问题差分一下，最后求前缀和，得到每个位置的询问次数。再把询问次数排序，一一对应即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m; 
long long a[200005];
long long ans=0;
long long b[200005];
int main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++) cin >> a[i];
	sort(a+1,a+n+1);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		cin >> x >> y;
		b[x]++,b[y+1]--;
	}
	for (int i=1;i<=n;i++) 
	{
		b[i]+=b[i-1];
	}
	sort(b+1,b+n+1);
	for (int i=1;i<=n;i++) ans+=b[i]*a[i];
	cout << ans;
 	return 0;
}
```


---

## 作者：yaoyuchen2021 (赞：2)

# 题目大意
给出 $n$ 个数， $q$ 个询问，每个询问求区间 $[l,r]$ 的和，改变 $n$ 个数的位置，使询问的总和最大，输出这个值。

# 解题思路
考虑 **贪心** 。先使用 $s$ 数组记录每个位置的询问次数，显然询问次数多的位置放大的数更优。所以对 $s$ 数组从大到小排序，在对输入的 $a$ 数组从大到小排序，最后输出 $\sum_{i=1}^n\ s_i\times a_i$ 即为所求。

那么如何维护 $s$ 数组呢？可以使用**差分**。具体代码为：
```cpp
for(int i=1;i<=q;i++)//差分维护s数组
{
	cin>>l>>r;
	s[l]++;s[r+1]--;
}
```

~~最后，别忘了不开 long long 见祖宗呜呜呜~~

# AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[200005],s[200005],l,r,ans;
bool cmp(int x,int y)//从大到小排序
{
	return x>y;
}
signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=q;i++)//差分维护s数组
	{
		cin>>l>>r;
		s[l]++;s[r+1]--;
	}
	for(int i=1;i<=n;i++)s[i]+=s[i-1];//求原数组
	sort(a+1,a+1+n,cmp);
	sort(s+1,s+1+n,cmp);
	l=0;while(s[++l])ans+=s[l]*a[l];//求和（这里有一个小小的优化，当s[l]=0时，就不用算下去了，退出循环
	cout<<ans;
	return 0;
}
```

---

## 作者：ccrui (赞：2)

## 简述题意：

给定一个序列 $a$ 和 $q$ 次询问，可以将序列重新排列，求排列后每次询问的总和的最大值。

## 思路：

**贪心+线段树/树状数组**。  
我们可以记录每个点被区间覆盖的次数作为它的权重（记为 $q_i$）（这时要用到线段树/树状数组的区间修改），则询问的总和为：

$$\sum_{i=1}^{n} q_i\times a_i$$

显而易见，要让大的 $q_i$ 配上大的 $a_i$，这样值才可能最大。  

举个例子：$4\times 5+3\times 2>4\times 2+3\times 5$。  
再举个例子：
![图](https://cdn.luogu.com.cn/upload/image_hosting/v72hn7a1.png)

在这个情况下，我们就要 $4$ 配上大的 $a_i$，然后再把 $3$ 配上较大的 $a_i$，依次类推，$1$ 陪到的就是最小的几个 $a_i$ 了。


所以我们可以将序列和每个点的权重排序（线段树/树状数组要先查询并记录每个点的值），让权重大的点配到尽可能大的数，最后再计算最大值即可。

## 线段树代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,l,r; 
long long a[114514*3],b[114514*3];//b保存线段树每个点的权重
long long ans=0;
inline int read(){
	int x=0,f=1;char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(int x) {
  static int st[35];
  int top=0;
  do{
    st[top++]=x%10,x/=10;
  }while(x);
  while(top)putchar(st[--top]+48);
}//快读快写 
struct stree{
	long long l,r;
	long long sum,tag;
}t[114514*8];//线段树 
void build(int x,int l,int r){
	t[x].l=l,t[x].r=r;//传递区间[l,r] 
	if(l==r){ 
		t[x].sum=a[l];
		return;
	}//此点如是叶子节点则结束递归 
	int mid=(l+r)>>1;//区间中点 
	build(x*2,l,mid);//构造左子树 
	build(x*2+1,mid+1,r);//构造右子树 
	t[x].sum=t[x*2].sum+t[x*2+1].sum;//从下往上传值
}
void down(int x){
  	if(t[x].tag){//如果有标记 
  		t[x*2].tag+=t[x].tag;//下传左子树 
  		t[x*2+1].tag+=t[x].tag;//下传右子树 
  		t[x*2].sum+=(t[x*2].r-t[x*2].l+1)*t[x].tag;//左子树和增加 
		t[x*2+1].sum+=(t[x*2+1].r-t[x*2+1].l+1)*t[x].tag;//右子树和增加 
  		t[x].tag=0;//清空标记 
  	}
}
void change(int x,int l,int r,int a){
	if(t[x].l>=l&&t[x].r<=r){//完全包含 
		t[x].tag+=a;//标记区间 
		t[x].sum+=(t[x].r-t[x].l+1)*a;//区间 和增加 
		return;
	}
	if(t[x].l==t[x].r)return;//到叶子节点直接返回 
	down(x);//这时还没有操作就需下传标记 
	int mid=(t[x].l+t[x].r)>>1;//区间中点 
	if(mid>=l)change(x*2,l,r,a);//访问左半部分 
	if(mid<r)change(x*2+1,l,r,a);//访问右半部分
	t[x].sum=t[x*2].sum+t[x*2+1].sum;//刷新值
}
int ask(int x,int l,int r){
	if(l<=t[x].l&&r>=t[x].r)return t[x].sum;//完全包含 
	down(x);//只多了一个下传标记 
	int mid=(t[x].l+t[x].r)>>1;//区间中点 
	int sum=0; 
	if(mid>=l)sum+=ask(x*2,l,r);//访问左半部分 
	if(mid<r)sum+=ask(x*2+1,l,r);//访问右半部分 
	return sum;
}
signed main(){
	n=read();
	m=read(); 
	build(1,1,n);//建树 
	for(int i=1;i<=n;i++){
		a[i]=read();
		//add(i,0);
	}
	sort(a+1,a+n+1);//a排序 
	for(int i=1;i<=m;i++){
		cin>>l>>r;
		change(1,l,r,1);//权重增加 
	}
	for(int i=1;i<=n;i++){
		b[i]=ask(1,i,i);//记录权重，方便排序	
	}
	sort(b+1,b+1+n);//b排序
	for(int i=1;i<=n;i++){
		ans+=b[i]*a[i];//计算最大值 
	}	
	write(ans);
 	return 0;
}
```
## 树状数组代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,l,r; 
long long a[114514*2],b[114514*2];
long long ans=0,t[1919810];
inline int read(){
    int x=0,f=1;char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void write(int x) {
  static int st[35];
  int top=0;
  do{
    st[top++]=x%10,x/=10;
  }while(x);
  while(top)putchar(st[--top]+48);
}//快读快写 
int add(int x,int y){
	while(x<=n){
		t[x]+=y;
		x+=x&-x;	
	}
}//修改/加点 
int ask(int x){
	int val=0;
	while(x>0){
		val+=t[x];
		x-=x&-x;	
	}
	return val;
}//查询 
signed main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		add(i,0);//树状数组加点
	}
	sort(a+1,a+n+1);//a排序
	for(int i=1;i<=m;i++){
		cin>>l>>r;
		add(l,1);
		add(r+1,-1);//权重增加（树状数组修改） 
	}
	for(int i=1;i<=n;i++){
		b[i]=ask(i);	
	}
	sort(b+1,b+1+n);//b排序
	for(int i=1;i<=n;i++){
		ans+=b[i]*a[i];	//计算最大值
	}
	write(ans);
 	return 0;
}
```


---

## 作者：da32s1da (赞：2)

对询问差分一下，最后求一遍前缀和，得到每个数被询问多少次。

把读入的数列排序。

然后乘一下。
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+50;
typedef long long LL;
int n,m,a[N],b[N],x,y;
LL ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);//把读入的数列排序
	for(int i=1;i<=m;i++)
	scanf("%d%d",&x,&y),b[x]++,b[y+1]--;//差分
	for(int i=1;i<=n;i++)b[i]+=b[i-1];//前缀和
	sort(b+1,b+n+1);//排序
	for(int i=1;i<=n;i++)ans+=1ll*a[i]*b[i];//乘
	printf("%I64d\n",ans);
}
```

---

## 作者：Fkxxx (赞：1)

这道题的思路非常简单，经过对样例的分析，我们发现，所有区间的总和为：

$\sum_{i = 1}^{n} a_i \times d_i $（其中 $a_i$ 为原数组的第 $i$ 项，$d_i$ 为第 $i$ 个元素被区间覆盖的次数）

这里有一个小细节：对于某一个元素被覆盖的次数我们可用差分进行优化。

所以，
```cpp
sort(a + 1,a + 1 + n)
sort(q + 1,q + 1 + n)
```
对数组进行排序后，求得 $\sum_{i = 1}^{n} a_i \times d_i $ 并输出即可。

接下来是代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , q , a[200005] , l , r , d[200005] , ans ;
signed main(){
	cin >> n >> q ;
	for( int i = 1 ; i <= n ; i ++ ){
		cin >> a[i] ;
	}
	sort( a + 1 , a + 1 + n ) ;
	for( int i = 1 ; i <= q ; i ++ ){
		cin >> l >> r ;
		d[l] ++ ;
		d[r + 1] -- ;
	}
	for( int i = 1 ; i <= n ; i ++ ){
		d[i] += d[i - 1] ;
	}
	sort( d + 1 , d + 1 + n ) ;
	for( int i = 1 ; i <= n ; i ++ ){
		ans += d[i] * a[i] ;
	}
	cout << ans ;
	return 0 ;
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

这道题很显然先将 $a$ 排序，然后第 $k$ 大的数对应出现次数第 $k$ 多的位置。

然后我们先打一份暴力程序。

## 代码（暴力）

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,q,a[200001],l,r,ans,cnt[200001];
signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1,greater<int>());//排序
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        for(int j=l;j<=r;j++)//更新次数
            cnt[j]++;
    }
    sort(cnt+1,cnt+n+1,greater<int>());//排序
    for(int i=1;i<=n;i++)
        ans+=cnt[i]*a[i];//高次对大数
    cout<<ans;
    return 0;
}
```
第 $7$ 个测试点 `TLE` 了。

分析：主要时间花在了大量的“更新次数”，既然这样相邻的差变化很少，我们可以顺理成章的想到差分（详见附录）。


## 新代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,q,a[200001],l,r,ans,h[200001],b[200001];
signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        h[l]++,h[r+1]--;//进行差分
    }
    for(int i=1;i<=n;i++)
        b[i]=b[i-1]+h[i];//前缀和求次数
    sort(b+1,b+n+1,greater<int>());
    for(int i=1;i<=n;i++)
        ans+=a[i]*b[i];//次数与数值
    cout<<ans;
    return 0;
}
```

## 附录——差分

差分类似于前缀和（后缀和），每一位表示和前一位的差，因此本题可以再原来差的基础上进行差分，即对于每次被“选中”让他们的第一个数对应的差分数组加一，最后一个之后的一个减一。

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Little Girl and Maximum Sum](https://www.luogu.com.cn/problem/CF276C)

## 算法思路

#### 算法：贪心和差分

先用**差分**求出每个位置询问的次数，然后**贪心**，把 $a$ 数组中大的数和大的次数相乘，小的数和小的次数相乘，让结果更大。

### 证明

要让答案最大，我们就要把最大的数加得多，最小的加得少，这样就能使答案最大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200010;
ll n,q,l,r,a[N],sum[N],ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=q;i++)
	{
		cin>>l>>r;
		sum[l]++;
		sum[r+1]--;
	}
	for(int i=1;i<=n;i++)
	{
		sum[i]+=sum[i-1];
	}
	sort(sum+1,sum+n+1);
	for(int i=1;i<=n;i++)
	{
		ans+=a[i]*sum[i];
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](/problem/CF276C) &[CF 传送门](//codeforces.com/problemset/problem/276/C)
# 思路
这题我们可以使用差分来做，第 $i$ 个位置被选中了 $s_i$ 次。我们要让 $\sum\limits_{i=1}^ns_i\times a_i$ 最大，我们可以把 $s$ 和 $a$ 数组从大到小排序就可以了，至于为什么就看证明吧。
# 证明
$\sum\limits_{i=1}^ns_i\times a_i$ 最大，那贪心的想，就是在加数数量一定的情况下，我们肯定是想让最大的 $a_i$ 加的次数最多，最小的 $a_i$ 加的次数最少。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
typedef long long ll; //以后 long long 可以简写作 ll 
using namespace std;
ll n, q, a[200005], s[200005], l, r, sum; //定义变量 
int main () { //定义主函数 
	cin >> n >> q; //输入变量 
	for (ll i = 1; i <= n; ++ i)
		cin >> a[i]; //输入数组 
	sort (a + 1, a + 1 + n, greater <ll> ()); //a 从大到小排序 
	while (q --) {
		cin >> l >> r; //输入变量 
		++ s[l], -- s[r + 1]; //差分！ 
	}
	for (reg ll i = 2; i <= n; ++ i)
		s[i] += s[i - 1]; //做一次前缀和 
	sort (s + 1, s + 1 + n, greater <ll> ()); //s 从大到小排序 
	for (reg int i = 1; i <= n; ++ i)
		sum += s[i] * a[i]; //求和 
	cout << sum; //输出 
	return 0; //结束程序 
}
```

---

## 作者：Code_Fish_GoodBye (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF276C)

## 题目大意

通过修改序列 $a$ 中的数的顺序，使
$$
\sum_{i=1}^q\sum_{j=l}^ra[j]
$$
最大，并输出它的值。

## 思路

一道简单贪心 $+$ 差分，通过差分的优秀的 $O(1)$ 区间修改能力帮助我们求出每个位置在询问中询问的次数，进行排序，最后次数较多的就让值较大的数来，以此类推。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
long long n,q,a[MAXN],b[MAXN],s[MAXN];
long long  sum;
template <typename T> inline void read(T &in) {
	in=0;int fh=1;char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)) in=(in<<1)+(in<<3)+(ch^48),ch=getchar();
	in*=fh;
}
template <typename T,typename... Ts> inline void read(T &in,Ts&... ins) {read(in),read(ins...);}
template <typename T> inline void write(T out) {
	static char str[20];int top=0;
	if(out<0) putchar('-'),out-=2*out;
	do{str[++top]=out%10+48,out/=10;} while(out);
	while(top) putchar(str[top--]);
	putchar('\n');
}
template <typename T,typename... Ts> inline void write(T out,Ts... outs) {write(out),write(outs...);}
int main(){
	read(n,q);
	for(int i=1;i<=n;i++) read(a[i]);
	while(q--){
		int l,r;
		read(l,r);
		b[l]++;
		b[r+1]--;
	}
	for(int i=1;i<=n;i++) s[i]=s[i-1]+b[i];
	sort(a+1,a+n+1);
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++) sum=sum+(a[i]*s[i]);
	cout<<sum;
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

# Description

有 $n$ 个数字，为 $a_1 \dots a_n $，$q$ 个询问。

每次读入 $l,r$，询问 $\sum_{i=l}^ra_i$。

你可以重新排列读入的 $a$ 数组，使**询问的总和最大**。

输出这个最大值。
# Solution1
肯定想到的是贪心。

让用到次数**最多**的位置用**最大**的数。

也就是：记录加排序加求和。

注意：不开 $\texttt{long long}$ 见祖宗。
## code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, q, ans;
int arr[N];
int tong[N]; // 统计次数
signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		for (int j = l; j <= r; j++) tong[j]++;
	}
	sort(tong + 1, tong + n + 1);
	sort(arr + 1, arr + n + 1); // 都从小到大排序
	for (int i = 1; i <= n; i++) {
		ans += arr[i] * tong[i];
	}
	cout << ans;
	return 0;
}
```
本人没测过，但掐指一算，应该会TLE。
# Solution2
发现上面解法中：
```cpp
for (int i = 1; i <= q; i++) {
	int l, r;
	cin >> l >> r;
	for (int j = l; j <= r; j++) tong[j]++;
}
```
时间复杂度为 $O(n^2)$。

所以要想办法优化。

**区间变化**又**求每个数的值** 很容易想到 **差分数组优化**。

差分数组是： $b_i = a_i - a_{i - 1}$；区间变化 $[l,r]+x$ 是 $b_l = b_i + x,b_{r + 1} = b_{r + 1} - x$，这样就变成了 $O(n)$，肯定能过。
## code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, q, ans;
int arr[N];
int tong[N]; // 统计次数
int b[N]; // 差分
signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		b[l] += 1, b[r + 1] -= 1;
	}
	for (int i = 1; i <= n; i++) {
		tong[i] = tong[i - 1] + b[i];
	}
	sort(tong + 1, tong + n + 1);
	sort(arr + 1, arr + n + 1); // 都从小到大排序
	for (int i = 1; i <= n; i++) {
		ans += arr[i] * tong[i];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：U_Uzzz (赞：0)

这题给定了 $a$ 数组，求 $\sum_{i=1}^q \sum_{j=l_i}^{r_i} a_j$ 最大。

可以很容易的想到选到最多的数应该最大，这样就可以实现询问总和最大。

所以可以用差分维护每个数被选到的次数，然后排序求和即可。

代码：

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
long long a,b,c,d[200100],e[200100];
int main(){
	cin>>a>>b;
	for(int x=1;x<=a;x++) cin>>d[x];
	for(int x=1;x<=b;x++){
		long long i,j;
		cin>>i>>j;
		e[i]++,e[j+1]--;
	}
	for(int x=1;x<=a;x++) e[x]+=e[x-1];
	sort(d+1,d+a+1);
	sort(e+1,e+a+1);
	for(int x=1;x<=a;x++) c+=d[x]*e[x];
	cout<<c;
}
```


---

## 作者：xiaomimxl (赞：0)

# 题意:

给出 $n$ 项的数列 $A$ , $q$  个询问, 询问  $\left[l,r\right]$  之间项的和. 求 $A$ 的全排列中该和的最大值.

# 思路:

记录所有询问, 利用差分数列 $dq$ , 标记第 $i$ 项被询问的次数 $(每次区间增1)$

最后对 $qd$ , $A$ 进行升序排序, 对应项相乘, 求和.

理由是: 越大的数被询问覆盖的次数越多那么总和就越大.

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int val[maxn],dq[maxn],sum[maxn];
int n,q,l,r;
long long ans;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",val+i);
	while(q--){
		scanf("%d%d",&l,&r);
		dq[l]++;dq[r+1]--;
	}
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+dq[i];
	}
	sort(sum+1,sum+n+1);
	sort(val+1,val+n+1);
	for(int i=1;i<=n;i++){
		ans+=(long long)val[i]*sum[i];
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：luo_shen (赞：0)

## 思路
如果不能改变 $a$ 数组的顺序的话，那么我们完全可以用前缀和把它一次秒了。但它可以改变，那我们只能换种思路了。（~~这不是废话吗~~）。

---
首先，我们用贪心思路来看它，因为能改变 $a$ 数组的值，所以我们可以把值大的作为要询问次数多的，这样它的总和就会大（原理：在排序不等式中顺序之积大于乱序之积，乱序之积大于逆序之积）。而询问次数我们可以通过差分来计算。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200100],d[200100],l,r;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];      //输入数值
	}
	for(int i=1;i<=m;i++){
		cin>>l>>r;      //输入查询范围，
		d[l]++;
		d[r+1]--;   	 //并进行差分来求得每个位置的数的询问次数。
	}
	for(int i=1;i<=n;i++){
		d[i]+=d[i-1];  	 //前缀和辅助差分的实现
	}
	sort(d+1,d+n+1);	 //将数值进行排序
	sort(a+1,a+n+1);	 //将询问次数进行排序
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i]*d[i]; //此时已经是顺序排列了，求出来的值自然就是最大值了
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

属于一种贪心思维，我们想如果要使得和最大，那么就必须保证最大的数乘的次数越多越好，并且排序没有限制，快速累加每个位置出现的次数，所以应该使用~~线段树~~**差分**。     

然后排序最大乘最大累加。  

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n,q;
ll a[N],c[N];

int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=q;++i){
		ll l,r;
		l=read(),r=read();
		c[l]++,c[r+1]--;
	}
	for(int i=1;i<=n;++i){
		c[i]=c[i-1]+c[i];
	}
	sort(c+1,c+n+1);
	ll ans=0;
	for(int i=1;i<=n;++i) ans+=c[i]*a[i];
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定长为 $n$ 的序列，你可以对其任意排序。再给出 $m$ 个询问，每一次询问询问区间和，请制定策略使得所有询问之和最大。

# 题目分析

这是一道贪心题。

显然要在询问最多的区间放最大的数，这样能让全局最优。

所以我们先把原序列排序，然后维护一个空序列，每一次询问 $[l,r]$ 就把空序列上 $[l,r]$ 区间内的数加一，最后对这个序列也进行一次排序。答案就是 $\sum\limits_{i=1}^na_i\times b_i$。

区间加一可以用差分维护。时间复杂度 $\mathcal{O(n\log n)}$，瓶颈在排序。

注意开 `long long`。

# 代码

```cpp
//2022/3/8
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 2e5 + 5;
int a[ma],sub[ma],sum[ma];
int n,m;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	sort(a + 1,a + n + 1);
	for (register int i = 1;i <= m; ++ i) {
		int l = read(),r = read();
		sub[l] ++,sub[r + 1] --;
	}
	for (register int i = 1;i <= n; ++ i) sum[i] = sum[i - 1] + sub[i];
	sort(sum + 1,sum + n + 1);
	int ans = 0;
	for (register int i = 1;i <= n; ++ i) {
		ans += a[i] * sum[i];
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

