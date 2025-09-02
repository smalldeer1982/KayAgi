# Zigzag

## 题目描述

宫廷巫师 Zigzag 想要成为一名著名的数学家。为此，他需要他自己的定理，正如柯西定理，或者他的和，正如闵可夫斯基和。但他最想要的是拥有他自己的序列，正如斐波那契数列，和他的函数，正如欧拉函数。

zigzag 因子为 $z$ 的 Zigzag 序列是一个无穷序列 $S_i^z$（$i\ge 1; z\ge 2$），它的定义如下：

- $S_i^z = 2$，当 $(i \bmod 2(z - 1)) = 0$ 时；
- $S_i^z = (i \bmod 2(z - 1))$，当 $0 < (i \bmod 2(z - 1)) \le z$ 时；
- $S_i^z = 2z - (i \bmod 2(z - 1))$，当 $(i \bmod 2(z - 1)) > z$ 时。

运算 $x \bmod y$ 表示取数 $x$ 除以数 $y$ 的余数。例如，序列 $S_i^3$（zigzag 因子为 $3$）的开头如下所示：$1, 2, 3, 2, 1, 2, 3, 2, 1$。

给定一个由 $n$ 个整数组成的数组 $a$，将数组中编号为 $i$（$1 \le i \le n$) 的元素记为 $a_i$。Zigzag 函数是函数 $Z(l, r, z) = \sum_{i=l}^{r} a_i \cdot S_{i-l+1}^z$，其中 $l, r, z$ 满足不等式 $1 \le l \le r \le n, z \ge 2$。

为了更好地熟悉 Zigzag 序列和 Zigzag 函数，巫师要求你在给定的数组 $a$ 上实现以下操作。

1.  赋值操作。操作参数是 $(p, v)$。该操作表示将值 $v$ 赋给数组的第 $p$ 个元素。应用该操作后，数组元素 $a_p$ 的值等于 $v$。
2.  Zigzag 操作。操作参数是 $(l, r, z)$。该操作表示计算 Zigzag 函数 $Z(l, r, z)$。

探索 zigzag 的神奇力量，实现所描述的操作。

## 说明/提示

样例解释：

- 第一次操作的结果是 $Z(2, 3, 2) = 3\cdot 1 + 1\cdot 2 = 5$。
- 第二次操作的结果是 $Z(1, 5, 3) = 2\cdot 1 + 3\cdot 2 + 1\cdot 3 + 5\cdot 2 + 5\cdot 1 = 26$。
- 第三次操作后，数组 $a$ 变为 $2, 3, 5, 5, 5$。
- 第四次操作的结果是 $Z(1, 5, 3) = 2\cdot 1 + 3\cdot 2 + 5\cdot 3 + 5\cdot 2 + 5\cdot 1 = 38$。

## 样例 #1

### 输入

```
5
2 3 1 5 5
4
2 2 3 2
2 1 5 3
1 3 5
2 1 5 3
```

### 输出

```
5
26
38
```

# 题解

## 作者：AladV (赞：5)

## 题意分析
题目的公式写的还是很长的，其实总结下来就一个需要计算的 $S$ 数组和一个基于 $S$ 数组的 $Z$ 函数。事实上，看到这道题就可以想到一个线段树或者树状数组的维护。本人不太擅长树状数组，所以本题解为线段树题解。

## 做法分析
我们首先观察到一个非常离奇的数据范围 $:\ \ 2\le z\le 6$，我们从这里切入。即，根据计算公式计算一个周期性的值，且种类非常少。

我们考虑，如果正常维护线段树的话肯定是不行的，因为他这个 $Z$ 函数的参数 $z$ 是动态给出的，无法固定维护，所以我们需要另寻他路。我们用一个 $s$ 数组来预处理 $S$ 数列，其中，$s_{i,j}$ 表示当 $S$ 数列的计算参数 $z=i$ 的时候，此时的余数为 $j$ ，这个时候的 $S$ 数组的值，说白了就是$S^i_{j}$的值。这个预处理非常的简单，我们只需要枚举一下 $i$ 和 $j$ ，然后根据题目中提供的计算公式即可计算。具体的代码如下：
```cpp
void Init()
{
	for(int i=2;i<=6;i++)
	{
		for(int j=0;j<2*(i-1);j++) 
		{
			if(!j) s[i][j]=2;
			else if(j<=i) s[i][j]=j;
			else if(j>i) s[i][j]=2*i-j;
		} 
	}
}
```
预处理完了之后我们就可以个根据我们预处理出来的这个东西来建树了。相较于普通线段树，我们对于每个线段树节点维护一个 $sum_{i,j}$，表示当前的模数参数 $z=i$ 时，当前区间的第一个数字模 $z=j$ 时的和。显然，这个东西在建树中可以根据 $s$ 数组和输入的 $a$ 数组来计算，具体计算方式如下：
```cpp
void BuildTree(int u,int l,int r)
{
	t[u].l=l,t[u].r=r;
	if(l==r)
	{
		for(int i=2;i<=6;i++) for(int j=0;j<2*(i-1);j++) t[u].sum[i][j]=(long long)(a[l]*s[i][j]);
		return ;
	}
	int mid=(l+r)>>1;
	BuildTree(u*2,l,mid);
	BuildTree(u*2+1,mid+1,r);
	pushup(u);
}
```
顺便讲一下本题有一点点与众不同的 pushup 。我们观察这个 $S$ 数列，他不管 $z$ 等于多少，其元素都是成周期性回文分布的。比如 1，2，3，2，1，2，3，2.......，所以，我们这道题的左儿子维护的是这个周期的左边一半，右儿子就是右边一半。因为两边是一样长的，所以我们在 pushup 函数里便用计算出来的左儿子的长度来推算右儿子的 $sum_{i,j}$ 的 $j$ 。
```cpp
void pushup(int u)
{
	int lson=u*2,rson=u*2+1;
	for(int i=2;i<=6;i++)
	{
		for(int j=0;j<i*2-2;j++)
		{
			int len=t[lson].r-t[lson].l+1;
			t[u].sum[i][j]=(t[lson].sum[i][j]+t[rson].sum[i][(j+len)%(2*(i-1))]);
		}
	}
}
```
之后就是一个 modify ，本题的 modify 函数较为容易，就是一个单点的覆盖式修改，只需记得每次修改时更新整个 sum 数组即可。代码会在之后的完整代码中给出。

query 的部分比较有意思，因为我们这道题的 sum 存在 $2$ 个维度，所以我们在 query 的时候要记得额外加上一个参数 res 表示 $sum_{i,j}$ 的 $j$。

下面给出完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010;
struct SegTree
{
	int l,r;
	long long sum[7][10];
}t[N<<2];
int s[7][10],n,m,a[N];
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void Init()
{
	for(int i=2;i<=6;i++)
	{
		for(int j=0;j<2*(i-1);j++) 
		{
			if(!j) s[i][j]=2;
			else if(j<=i) s[i][j]=j;
			else if(j>i) s[i][j]=2*i-j;
		} 
	}
}
void pushup(int u)
{
	int lson=u*2,rson=u*2+1;
	for(int i=2;i<=6;i++)
	{
		for(int j=0;j<i*2-2;j++)
		{
			int len=t[lson].r-t[lson].l+1;
			t[u].sum[i][j]=(t[lson].sum[i][j]+t[rson].sum[i][(j+len)%(2*(i-1))]);
		}
	}
}
void BuildTree(int u,int l,int r)
{
	t[u].l=l,t[u].r=r;
	if(l==r)
	{
		for(int i=2;i<=6;i++) for(int j=0;j<2*(i-1);j++) t[u].sum[i][j]=(long long)(a[l]*s[i][j]);
		return ;
	}
	int mid=(l+r)>>1;
	BuildTree(u*2,l,mid);
	BuildTree(u*2+1,mid+1,r);
	pushup(u);
}
void Modify(int u,int pos,int d)
{
	if(t[u].l==t[u].r && t[u].l==pos)
	{
		for(int i=2;i<=6;i++) for(int j=0;j<2*(i-1);j++) t[u].sum[i][j]=(long long)(s[i][j]*d);
		return ;
	}
	int mid=(t[u].l+t[u].r)>>1;
	if(pos<=mid) Modify(u*2,pos,d);
	else Modify(u*2+1,pos,d);
	pushup(u);
}
long long Query(int u,int l,int r,int z,int res)
{
	if(l==t[u].l && t[u].r==r) return t[u].sum[z][res];
	int mid=(t[u].l+t[u].r)>>1;
	if(r<=mid) return Query(u*2,l,r,z,res);
	else if(mid<l) return Query(u*2+1,l,r,z,res);
	else return Query(u*2,l,mid,z,res)+Query(u*2+1,mid+1,r,z,(res+(mid-l+1))%(2*(z-1)));
}
signed main()
{
	Init();
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	BuildTree(1,1,n);
	int cnt=0;
	m=read();
	while(m--)
	{
		cnt++;
		// cout<<cnt<<endl;
		int op=read();
		if(op==1)
		{
			int pos=read(),d=read();
			Modify(1,pos,d);
			// cout<<"djd"<<endl;
		}
		if(op==2)
		{
			// cout<<cnt<<" ";
			int l=read(),r=read(),z=read();
			printf("%lld\n",Query(1,l,r,z,1));
		}
	}
	return 0;
}
```
感谢各位阅读！

---

## 作者：shinzanmono (赞：1)

考虑 $2\leq z\leq 6$ 和 $S$ 的生成方式可以推出，$S^z$ 序列形如 $1,2,\ldots,z,\ldots,2,1,2,\ldots$，可以发现其以 $2z$ 为循环节，那么我们可以开 $z\times 2z$ 棵线段树或树状数组，第 $i$ 行第 $j$ 列的线段树表示当前的 $z=i$，起点为 $S^z_j$，然后查询的时候在相应的树上查询即可。时间复杂度 $O(qz^2\log n)$，空间复杂度 $O(nz^2)$。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=1e5+10;
ll S[6][10],a[sz];
struct ST{
    ll tree[6][10][sz<<2];
    void build(int p,int ln,int rn){
        if(ln==rn){
            for(int i=1;i<=5;i++)
                for(int j=0;j<2*i;j++)
                    tree[i][j][p]=a[ln]*S[i][(j+ln-1)%(2*i)];
            return;
        }
        int mid=ln+rn>>1;
        build(p<<1,ln,mid);
        build(p<<1|1,mid+1,rn);
        for(int i=1;i<=5;i++)
            for(int j=0;j<2*i;j++)
                tree[i][j][p]=tree[i][j][p<<1]+tree[i][j][p<<1|1];
    }
    void change(int p,int ln,int rn,int pos,int val){
        if(ln==rn){
            for(int i=1;i<=5;i++)
                for(int j=0;j<2*i;j++)
                    tree[i][j][p]=val*S[i][(j+ln-1)%(2*i)];
            return;
        }
        int mid=ln+rn>>1;
        if(pos<=mid)change(p<<1,ln,mid,pos,val);
        else change(p<<1|1,mid+1,rn,pos,val);
        for(int i=1;i<=5;i++)
            for(int j=0;j<2*i;j++)
                tree[i][j][p]=tree[i][j][p<<1]+tree[i][j][p<<1|1];
    }
    ll query(int p,int ln,int rn,int l,int r,int z){
        if(ln>=l&&rn<=r)return tree[z/2][((2-l)%z+z)%z][p];
        int mid=ln+rn>>1;
        ll res=0;
        if(l<=mid)res+=query(p<<1,ln,mid,l,r,z);
        if(r>mid)res+=query(p<<1|1,mid+1,rn,l,r,z);
        return res;
    }
}st;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q;
    std::cin>>n;
    for(int i=1;i<=n;i++)std::cin>>a[i];
    for(int i=1;i<=5;i++){
        int t=2*i;
        for(int j=0;j<t;j++){
            if(j%t==0)S[i][j]=2;
            else S[i][j]=j%t<=i+1?j%t:2*i-j%t+2;
        }
    }
    st.build(1,1,n);
    std::cin>>q;
    while(q--){
        int op,x,y,z;
        std::cin>>op>>x>>y;
        if(op==1)st.change(1,1,n,x,y);
        else std::cin>>z,z=2*z-2,std::cout<<st.query(1,1,n,x,y,z)<<"\n";
    }
    return 0;
}
```

---

