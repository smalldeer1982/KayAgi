# Inna and Binary Logic

## 题目描述

Inna is fed up with jokes about female logic. So she started using binary logic instead.

Inna has an array of $ n $ elements $ a_{1}[1],a_{1}[2],...,a_{1}[n] $ . Girl likes to train in her binary logic, so she does an exercise consisting of $ n $ stages: on the first stage Inna writes out all numbers from array $ a_{1} $ , on the $ i $ -th $ (i>=2) $ stage girl writes all elements of array $ a_{i} $ , which consists of $ n-i+1 $ integers; the $ k $ -th integer of array $ a_{i} $ is defined as follows: $ a_{i}[k]=a_{i-1}[k] AND a_{i-1}[k+1] $ . Here AND is bit-wise binary logical operation.

Dima decided to check Inna's skill. He asks Inna to change array, perform the exercise and say the sum of all ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400E/150441d31156a32e0b2da63844d600138a543898.png) elements she wrote out during the current exercise.

Help Inna to answer the questions!

## 样例 #1

### 输入

```
3 4
1 1 1
1 1
2 2
3 2
1 2
```

### 输出

```
6
4
7
12
```

# 题解

## 作者：AladV (赞：1)

## 题意分析
没什么好分析的，都能读懂题。
## 做法分析
本题解为线段树题解，对线段树不太熟悉的同学可以先[学习线段树](https://www.cnblogs.com/juruo-wsy/p/14728124.html)。

我们考虑这道题给出的 and 算法。很明显，是需要进行位运算的，即，对于每个数的每个二进制位单独进行计算，而且这些二进制位之间是互相不影响的，最后统计结果的时候，如果某一个二进制位是 1，那么 ans 就可以加上 1<<k，k 是这个位置。当然这是口胡，然后我们来看一下实现。

我们首先观察一下这个数列。如果我给出一个 $a_1={1,1,1,1,0,1,1,1}$ ,那么我们来看一下剩下的数列是什么：

```
    0 0 0 0   
   1 0 0 0 0  
  1 1 0 0 0 1
 1 1 1 0 0 1 1
1 1 1 1 0 1 1 1
```
到这里就足够了，我们发现最后这些 1 都是会被 0 吞噬的，然后我们发现1的出现形式是以一连串的 1 为底，向上成一个等边三角形。这样只要我们知道这一长串1的长度，我们就可以求出这个三角形的大小。

我们维护18棵线段树，因为 $2^{18}>10^5$ 也就是题目中 $a_i$ 的数据范围。每棵线段树维护一个二进制位。之后呢，对于每个线段树节点，我们维护一个 lmax 一个 rmax ，分别代表当前节点所负责的区间中，最左边的一长串 1 和最右边的一长串 1 的长度。这道题的核心点在于 pushup 函数，这里重点讲一下。

首先对于线段树的节点 p ，我们先把 $t_p.lmax$ 置成 $t_{p<<1}.lmax$ ，即，显而易见他的左儿子的左侧最长可以直接给爸爸拿来用。之后我们考虑，如果他的整个左儿子区间都被1填满，即， $t_{p<<1}.lmax=t_{p<<1}.r-t_{p<<1}.l+1$ ，那么我们就发现它可以跟这个爸爸的右儿子的 lmax 连上！！！重大的惊人发现！于是我们特判，在这种情况下，把 $t_p.lmax+=t_{p<<1|1}.lmax$ ，即加上右儿子的左侧 max 。同理，我们在处理 $t_p.rmax$ 的时候也是使用相同的方法。还记不记得我们之前记录了一个 sum ？这个 sum 记录的是什么呢？是这个区间内以这一大坨 1 为底的三角形的大小。

如何计算 sum ？我们首先把 $t_p.sum$ 置成 $t_{p<<1}.sum+t_{p<<1|1}.sum$ 。完了之后呢我们考虑一下，有可能左儿子的 rmax 和右儿子的 lmax 连上了，这个时候我们就先让 $t_p.sum$ 减去左儿子的 rmax 和右儿子的 lmax ，之后再加上这两个连起来的大小。

建树和 modify 和正常的线段树没什么两样，如果对多棵线段树不熟悉的同学可以去练习几道题。其他的具体细节见代码：

```cpp
//Copyright: AladV
//Finish Time: 2021.5.10 18:38
//Editor: CP-Editor
//Time Usage: 1746 ms
//Memory Usage: 255100kib
#include<bits/stdc++.h>
#define int long long
#define lson p<<1
#define rson p<<1|1
using namespace std;
const int N=1e5+5;
struct SegTree
{
	int sum,lmax,rmax,bit;
}t[20][N<<2];
int n,m;
int a[N];
int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
// int bit[N];
void pushup(int b,int p,int len)
{//wsy
	t[b][p].lmax=t[b][lson].lmax;
	if(t[b][lson].lmax==(len-(len>>1))) t[b][p].lmax+=t[b][rson].lmax;
	t[b][p].rmax=t[b][rson].rmax;
	if(t[b][rson].rmax==(len>>1)) t[b][p].rmax+=t[b][lson].rmax;
	
	t[b][p].sum=t[b][lson].sum+t[b][rson].sum;
	if(t[b][lson].rmax && t[b][rson].lmax)
	{
		int llen=t[b][lson].rmax,rlen=t[b][rson].lmax;
		t[b][p].sum-=llen*(llen+1)/2;
		t[b][p].sum-=rlen*(rlen+1)/2;
		t[b][p].sum+=(llen+rlen)*(llen+rlen+1)/2;
	}
}
void BuildTree(int b,int p,int l,int r)
{
	if(l==r)
	{
		t[b][p].sum=t[b][p].lmax=t[b][p].rmax=(a[l]&(1<<b)?1:0);
		return ;
	}
	int mid=(l+r)>>1;
	BuildTree(b,lson,l,mid);
	BuildTree(b,rson,mid+1,r);
	pushup(b,p,r-l+1);
}
void Modify(int b,int p,int l,int r,int pos,int val)
{
	if(l==r)
	{
		t[b][p].sum=t[b][p].lmax=t[b][p].rmax=(val&(1<<b)?1:0);
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) Modify(b,lson,l,mid,pos,val);
	else Modify(b,rson,mid+1,r,pos,val);
	pushup(b,p,r-l+1);
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=0;i<18;i++)
	{
		// bit[i]=i;
		BuildTree(i,1,1,n);
	}
	while(m--)
	{
		int pos=read(),val=read();
		int ans=0;
		for(int i=0;i<18;i++)
		{
			Modify(i,1,1,n,pos,val);
			ans+=(1<<i)*t[i][1].sum;
		}
		printf("%lld\n",ans);
		// cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：SFlyer (赞：0)

提供一个非线段树做法。其实本质一样。

考虑到计算每一位的答案，再求和。这样就变成了若干个 $0,1$ 的问题了。因为 $0$ 会使后面无法再次产生贡献，我们只能在 $1$ 之间操作。一段长度为 $l$ 的连续 $1$ 每次操作过后长度会减少 $1$，因此产生的贡献是 $\frac{l(l+1)}{2}$ 次。

修改操作就是把一个 $0$ 变成 $1$ 或者 $1$ 变成 $0$，前者是把两边的连起来，后者是分开。因此我们直接用 set 来维护所有 $0$ 的位置就可以了。

代码很简单，但是要较长时间。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+5;

ll n,q,a[N],ans;
set<int> z[18];

void upd(int w,int id,int to){
	to=(to==1?1:-1);
	int l=id-*(--z[w].lower_bound(id))-1;
	int r=*z[w].upper_bound(id)-id-1;
	#define cn2(x) (1ll*(x)*(x+1)/2)
	ans+=1ll*(1<<w)*to*(cn2(l+r+1)-cn2(l)-cn2(r));
	if (to==1){
		z[w].erase(id);
	}
	else{
		z[w].insert(id);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>q;
	for (int i=0; i<17; i++){
		for (int j=0; j<=n+1; j++){
			z[i].insert(j);
		}
	}
	for (int i=1; i<=n; i++){
		cin>>a[i];
		for (int j=0; j<17; j++){
			if (a[i]>>j&1){
				upd(j,i,1);
			}
		}
	}
	while (q--){
		int p,v;
		cin>>p>>v;
		for (int j=0; j<17; j++){
			if ((a[p]^v)>>j&1){
				upd(j,p,v>>j&1);
			}
		}
		cout<<ans<<"\n";
		a[p]=v;
	}
	return 0;
}
```

---

