# Divide and Summarize

## 题目描述

Mike received an array $ a $ of length $ n $ as a birthday present and decided to test how pretty it is.

An array would pass the $ i $ -th prettiness test if there is a way to get an array with a sum of elements totaling $ s_i $ , using some number (possibly zero) of slicing operations.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461D/bacc5f6e8a5007e7b78d11e0dd09c5d277e67ed2.png)An array slicing operation is conducted in the following way:

- assume $ mid = \lfloor\frac{max(array) + min(array)}{2}\rfloor $ , where $ max $ and $ min $ — are functions that find the maximum and the minimum array elements. In other words, $ mid $ is the sum of the maximum and the minimum element of $ array $ divided by $ 2 $ rounded down.
- Then the array is split into two parts $ \mathit{left} $ and $ right $ . The $ \mathit{left} $ array contains all elements which are less than or equal $ mid $ , and the $ right $ array contains all elements which are greater than $ mid $ . Elements in $ \mathit{left} $ and $ right $ keep their relative order from $ array $ .
- During the third step we choose which of the $ \mathit{left} $ and $ right $ arrays we want to keep. The chosen array replaces the current one and the other is permanently discarded.

You need to help Mike find out the results of $ q $ prettiness tests.

Note that you test the prettiness of the array $ a $ , so you start each prettiness test with the primordial (initial) array $ a $ . Thus, the first slice (if required) is always performed on the array $ a $ .

## 说明/提示

Explanation of the first test case:

1. We can get an array with the sum $ s_1 = 1 $ in the following way: 1.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.2 $ a = [1, 2, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 2] $ , $ right = [3] $ . We choose to keep the $ \mathit{left} $ array.
  
   1.3 $ a = [1, 2] $ , $ mid = \frac{1+2}{2} = 1 $ , $ \mathit{left} = [1] $ , $ right = [2] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 1 $ .
2. It can be demonstrated that an array with the sum $ s_2 = 8 $ is impossible to generate.
3. An array with the sum $ s_3 = 9 $ can be generated in the following way: 3.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
4. It can be demonstrated that an array with the sum $ s_4 = 12 $ is impossible to generate.
5. We can get an array with the sum $ s_5 = 6 $ in the following way: 5.1 $ a = [1, 2, 3, 4, 5] $ , $ mid = \frac{1+5}{2} = 3 $ , $ \mathit{left} = [1, 2, 3] $ , $ right = [4, 5] $ . We choose to keep the $ \mathit{left} $ with the sum equalling $ 6 $ .

Explanation of the second test case:

1. It can be demonstrated that an array with the sum $ s_1 = 1 $ is imposssible to generate.
2. We can get an array with the sum $ s_2 = 2 $ in the following way: 2.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ \mathit{left} $ array with the sum equalling $ 2 $ .
3. It can be demonstrated that an array with the sum $ s_3 = 3 $ is imposssible to generate.
4. We can get an array with the sum $ s_4 = 9 $ in the following way: 4.1 $ a = [3, 1, 3, 1, 3] $ , $ mid = \frac{1+3}{2} = 2 $ , $ \mathit{left} = [1, 1] $ , $ right = [3, 3, 3] $ . We choose to keep the $ right $ array with the sum equalling $ 9 $ .
5. We can get an array with the sum $ s_5 = 11 $ with zero slicing operations, because array sum is equal to $ 11 $ .

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
8
9
12
6
5 5
3 1 3 1 3
1
2
3
9
11```

### 输出

```
Yes
No
Yes
No
Yes
No
Yes
No
Yes
Yes```

# 题解

## 作者：Lynkcat (赞：4)

暴力题，从没见过这么暴力的 2D。

考虑暴力的复杂度为什么是对的，我们发现 $a_i$ 的值域很小，仅仅只有 $10^6$ ，也就是说，我们满打满算最后跑出来的区间数也只有 $10^6 \times \log{10^6}$ 个，完全可以做这道题。

```c++
int T,n,q,a[N],s[N],x;
map<int,int>Mp;
void dfs(int l,int r)
{
	if (l>r) return;
	int mid,l1,r1,mid1,nowcut;
	Mp[s[r]-s[l-1]]=1;
	mid=(a[l]+a[r])/2;
	l1=l,r1=r;
	nowcut=r+1;
	while (l1<=r1)
	{
		mid1=l1+(r1-l1)/2;
		if (a[mid1]>mid) nowcut=mid1,r1=mid1-1; else l1=mid1+1;
	}
	if (nowcut==r+1) return;
	dfs(l,nowcut-1);//暴力跑左边的区间
	dfs(nowcut,r);//暴力跑右边的区间
}
signed main()
{
	T=read();
	while (T--)
	{
		Mp.clear();
		n=read(),q=read();
		for (int i=1;i<=n;i++) a[i]=read();
		sort(a+1,a+n+1);
		for (int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		dfs(1,n);
		while (q--)
		{
			x=read();
			if (Mp[x]) puts("Yes"); else puts("No");
		}
	}
}

---

## 作者：2021sunzishan (赞：1)

知道这题的正解后，用数论做了半天的我默默摔烂了我的鼠标……

题意非常好理解，这里就不概括了。

## 思路：

暴力！！！

不要怕超时，不会超的。

我们打一个 dfs，求出所有可能的和值，放进一个 set 里。

注意，不能开桶，和值非常大。

然后每次读入，判断这个数在不在 set 里面就好。

以上就是本题的思路了。是不是非常简单？

如果还有不懂的，就看代码吧！

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//要开long long
int n,m,t;
int a[200005],s[200005];
set<int>q;
inline int read() {//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
void dfs(int l,int r) {
	q.insert(s[r]-s[l-1]);//把和放进set里
	if(l==r)return;//终止条件
	int mid=upper_bound(a+l,a+1+r,(a[l]+a[r])/2)-a-1;//求出中间数的下标
	if(mid>=r)return;//注意判断边界
	dfs(l,mid);
	dfs(mid+1,r);
}
main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--) {
		memset(a,0,sizeof(a));
		memset(s,0,sizeof(s));
		q.clear();
		n=read(),m=read();
		for(int i=1; i<=n; i++)a[i]=read();
		sort(a+1,a+1+n);//排序
		for(int i=1; i<=n; i++)//求前缀和
			s[i]=s[i-1]+a[i];
		dfs(1,n);
		for(int i=1; i<=m; i++) {
			int t=read();
			if(q.count(t))//判断是否存在
				printf("Yes\n");
			else
				printf("No\n");
		}
	}
	return 0;
}

```
完结~


---

## 作者：__O_v_O__ (赞：0)

首先，我们先把原数组排序。

定义一个函数 $f(l,r)$ 表示当前已经舍弃了原数组其他部分，只剩下 $l$ 到 $r$ 的区间。

因为原数组有序，所以 $l$ 到 $r$ 的最小值为 $a_l$，最大值为 $a_r$，容易求出 $mid$ 是 $(a_l+a_r)/2$。

然后，我们二分出 $mid$ 在原数组中的位置 $midpos$，递归 $f(l,midpos)$ 和 $f(midpos+1,r)$。

但是这样只能枚举所有区间，如何判断区间和能否达到 $s_i$ 呢？很简单，因为我们已经枚举了所有区间 $[l,r]$，只需使用一个桶，把 $l$ 到 $r$ 的区间和作为下标，置为 $1$ 即可。

区间和可以使用前缀和维护。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int t,n,q,a[100001],su,s[100001];map<int,int>m;//m是桶
void f(int l,int r){
	if(l==r){m[a[l]]=true;return;}
	if(l>r)return;//判断非法
	m[s[r]-s[l-1]]=true;//记录当前的和
	if(a[l]==a[r])return;
	int mi=a[l]+a[r]>>1,l1=l,r1=r,ans=l;
	while(l1<=r1){//二分
		int mid=l1+r1>>1;
		if(a[mid]<=mi)ans=mid,l1=mid+1;
		else r1=mid-1;
	}
	f(l,ans),f(ans+1,r);//递归
}
signed main(){
	ios::sync_with_stdio(0),cin>>t;
	afor(i,1,t,STB){
		cin>>n>>q,m.clear(),memset(s,0,sizeof s),su=0;//多测清空
		afor(j,1,n,STB)cin>>a[j];
		sort(a+1,a+n+1);//排序
		afor(j,1,n,STB)s[j]=s[j-1]+a[j];//前缀和
		f(1,n);//分治
		afor(j,1,q,STB){
			int s;cin>>s;
			if(m[s])cout<<"Yes\n";//判断
			else cout<<"No\n";
		}
	}return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

DFS+set

首先对 $a$ 数组排序。

然后模拟二分切割的过程（计算 $mid$ 时需要二分查找或调用 upper_bound），但不舍弃任何一个部分，而是计算出每次切割后两部分的和值，并将和值放入 set 或 Hash_map 中备查（由于切割的方式是二分，所有最多有 $2 \times N$ 个不同的值），计算和值是需要使用前缀和优化。

对于每个询问的 $s$ 只需在 set 或 Hash_map 中查找，如果存在则输出 `Yes`，否则输出 `No`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,q,a[200005];
ll sum[200005],t;
set<ll> s;
inline void dfs(int l,int r)
{
    s.insert(sum[r]-sum[l-1]);
    if(l==r) return;
    int mid=a[l]+a[r]>>1;
    int pos=upper_bound(a+l,a+1+r,mid)-a-1;
    if(pos>=r) return;
    dfs(l,pos);
    dfs(pos+1,r);
    return;
}
int main()
{
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;++i)
    {
        sum[i]=sum[i-1]+a[i];
    }
    dfs(1,n);
    while(q--)
    {
        scanf("%lld",&t);
        if(s.count(t)) printf("Yes\n");
        else printf("No\n");
    }
	return 0;
}

```

---

## 作者：IIIIndex (赞：0)

### 题意：

​	给你一个长度为$n$的数组$a$，取$mid=\lfloor \frac{max+min}{2} \rfloor$，按照元素和$mid$的大小关系（小于等于$mid$的进入左数组，大于$mid$的进入右数组）将数组分为两块（两个新数组内元素均保持它们在原数组内的先后次序），然后任取一块抛弃。接下来是$m$次查询，查询是否存在某个数组，其元素和为$q$

### 思路：

​	因为我们仅仅只是对元素进行**求和**，所以说数组内元素的顺序实际上和我们的结果没有多大关系，为了减小我们在将数组分块的时候的工作量，我们考虑先将初始数组$a$进行排序。

​	由于我们的数组是有序的，所以说我们在将大数组分为左右小数组时，就**不会**对其中元素的位置进行更改，只需要改变我们的开头结尾即可。

​	所以说，我们可以利用**递归函数**（出口为数组内所有元素相等，即$a[l]\equiv a[r]$）直接对数组进行分块的模拟，然后用**前缀和**来统计小数组内元素之和，并将其记录。

​	为了便于以后的查找，我们将记录数组进行排序（当然，这里也可以用set来进行记录），然后对于每个查询，我们用二分法寻找记录数组里面是否存在我们查询的元素即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int inf=1e9+7;
const int maxn=1e6+100;
ll a[maxn],can[maxn],qzh[maxn],cnt=0;				//can数组存元素和，cnt统计can数组内元素个数，qzh是前缀和qaq
 
void find(int l,int r){
    if(l==r){
        can[cnt++]=a[l];
        return;
    }
    else if(l>r)return;
    int maxi=r,mini=l;
    can[cnt++]=qzh[r]-qzh[l-1];
    if(a[maxi]==a[mini])return;						//这里代码可以简化，我写的比较冗杂
    int mid=(a[maxi]+a[mini])/2;
    int midd=l;
    int left=l,right=r;
    while(left<=right){								//二分查找mid位置
        int midium=(left+right)/2;
        if(a[midium]<=mid){
            left=midium+1;
            midd=midium;
        }
        else{
            right=midium-1;
        }
    }
    find(l,midd);
    find(midd+1,r);
}
 
int query(int x){									//二分查询，如果把数组保存换成set保存代码直接少一半
    int l=0,r=cnt-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(can[mid]==x)
            return true;
        else if(can[mid]<x){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return false;
}
 
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        cnt=0;
        int n,q;
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        sort(a+1,a+1+n);									//这个sort直接让我D比C低了500分
        qzh[1]=a[1];
        for(int i=2;i<=n;i++){
            qzh[i]=a[i]+qzh[i-1];
        }
        find(1,n);
        sort(can,can+cnt);
        int qq;
        for(int i=0;i<q;i++){
            scanf("%d",&qq);
            if(query(qq)){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
}
```



---

## 作者：vectorwyx (赞：0)

显然 $s$ 合法当且仅当它属于切片操作得到的所有数组和的集合。而且在进行切片操作前先对整个数组排序肯定是没有影响的。

模拟一遍这个切片操作，求出所有可能的数组和即可。每次递归只需要二分出中间位置，最坏复杂度为 $O(nlogn)$，稳过。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e7+5;
int top,a[N];
ll sum[N],ans[N];

void di(int L,int R){
	if(L==R){
		ans[++top]=a[L];
		return;
	}
	int mid=(a[L]+a[R])>>1,pos=upper_bound(a+L,a+R+1,mid)-a-1;
	if(pos==R){
		ans[++top]=sum[R]-sum[L-1];
		return;
	}
	ans[++top]=sum[pos]-sum[L-1];
	ans[++top]=sum[R]-sum[pos];
	di(L,pos);
	di(pos+1,R);
}

void work(){
	int n=read(),q=read();
	top=0;
	fo(i,1,n) a[i]=read();
	sort(a+1,a+1+n);
	fo(i,1,n) sum[i]=sum[i-1]+a[i];
	di(1,n);
	ans[++top]=sum[n];
	sort(ans+1,ans+1+top);
	fo(i,1,q){
		int s=read();
		if(binary_search(ans+1,ans+1+top,s)) puts("Yes");
		else puts("No");
	}
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：511_Juruo_wyk (赞：0)

[CF1461D Divide and Summarize](https://www.luogu.com.cn/problem/CF1461D)

由题意可见是一个非常类似于快速排序的过程。所有小于或等于 $mid$ 的数放左边，其余放右边，无论原来的序列怎样排序都不影响左右的序列以及它们的和。

先排序，再做前缀和，这样就可以 $O(1)$ 求出一段的和，把所有可能得到的和存在一个 `set` 里面，然后就可以 $O(\log n)$ 询问了。模拟快排的过程，二分切割序列。时间复杂度应该是所有递归中 $\log(r-l+1)$ 的和乘以递归次数 $V$，就是 $O(\sum\log(r-l+1)\times V)$。


**这是正解，不是什么所谓的暴力！**

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const int N = 1e5+5;
int a[N],sum[N],n,q,x;
set<int>ans;
void mer(int l,int r){
	if(l>r)return;
	ans.insert(sum[r]-sum[l-1]);
	const int mid = a[r]+a[l]>>1;
	const int poi = upper_bound(a+l,a+r+1,mid)-a;
	if(poi>r)return;
	mer(l,poi-1);
	mer(poi,r);
}
signed main(){
	int t;cin>>t;
	while(t--){
		cin>>n>>q,ans.clear();
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+a[i];
		ans.insert(sum[n]);
		mer(1,n);
		while(q--){
			scanf("%lld",&x);
			if(*ans.lower_bound(x)==x)puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

感谢 @[Liuxizai](https://www.luogu.com.cn/user/371439) 指出错误！

---

