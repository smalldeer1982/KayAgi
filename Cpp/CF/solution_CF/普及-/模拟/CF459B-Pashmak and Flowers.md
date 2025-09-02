# Pashmak and Flowers

## 题目描述

Pashmak 想要给 Parmida一对花。有n朵花在花园里，每朵花都有一个魅力值bi，Pashmak想要两朵魅力值相差最大的花，问有多少种方案？

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1 1```

## 样例 #2

### 输入

```
3
1 4 5
```

### 输出

```
4 1```

## 样例 #3

### 输入

```
5
3 1 2 3 1
```

### 输出

```
2 4```

# 题解

## 作者：Accepted_Z (赞：2)

打个小广告：[点我](https://www.luogu.org/blog/hhhh123/)
### 思路
用m来记录最大值，用s来记录最小值。

用x来记录最大值的个数，用y来记录最小值的个数。

初始化m和s的值，输入的时候边读边判断，找到当前最大值，以后的话如果有数与当前最大值相同，就把当前最大值的个数加一，如果当前数大于最大值，就把最大值更新，最大值个数变为1，最小值同理。最后，m-s的值就是最大差值，又根据乘法原理，方案数就是x*y的积(这里有一种特殊情况，在下文中会说明)
### 注意
(1)如果m等于s，那么所有的花都可以取，就有n(n-1)种取法。又因为每次是取两朵花，所以最终就有n(n-1)/2种取法。

(2)此题数据范围较大，需要开long long，否则要么[这样](https://www.luogu.org/recordnew/show/15724778)
，要么[这样](https://www.luogu.org/recordnew/show/15724932)

(3)累加最大值个数和找当前最大值的顺序不能交换，否则就会[这样](https://www.luogu.org/recordnew/show/15725750)
### 代码
以下是我的蒟蒻版AC代码
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
long long n,x,y,m=-1,s=1000000005,a[500000];//初始化m和s的值
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==m) x++;//如果与当前最大值相同，就把最大值的个数加一
		if(a[i]>m) m=a[i],x=1;//如果大于最大值，就更新，把x的值变为1
        if(a[i]==s) y++;//如果与当前最小值相同，就把最小值的个数加一
		if(a[i]<s) s=a[i],y=1;//如果小于最小值，就更新，把y的值变为1
    }
    if(m==s) cout<<0<<" "<<n*(n-1)/2;//特判m等于s的情况
    else cout<<m-s<<" "<<x*y;//否则就直接输出
    return 0;//233啦
}

```

---

## 作者：迷残云 (赞：1)

好，这显然是道找最大值最小值的问题。

于是我们想到了~~万能的线段树~~来维护最大值

如果您不会线段树，请看[这里](https://www.luogu.com.cn/problem/P3372)您只要把单点修改去了，再把区间查询和改为区间查询最大值就可以了。

放个查询一个值出现多少次代码：（权值线段树[入门](https://www.cnblogs.com/LZA119/p/11286409.html)）

```cpp
int find(int l,int r,int v,int x)
	{
		if(l==r) 
		    return f[v];
		else
		{
			int mid=(l+r)/2;
			if(x<=mid) 
			    return find(l,mid,v*2,x); 
			else 
			    return find(mid+1,r,v*2+1,x);
		}
	}
```

再放个区间查询最大值和建树代码：

```cpp
void build(int node,int left,int right)
{
	if(left==right) //是否到达叶子节点 
	{
	    segtree[node]=a[left];	
	    return ;
	} 
	int mid=(left+right)/2;
	build(2*node,left,mid);     //递归构建左孩子 
	build(2*node+1,mid+1,right);//右递归构建右孩子 
	
	//等左右子树构建好以后，维护下父亲节点的最小值； 
	segtree[node]=max(segtree[2*node],segtree[2*node+1]);
}


int  query(int node,int left,int right,int x,int y)
{
	//当前线段树节点控制的区间[left,right] 在查询区间[x,y]范围之内
	// 形如：  x <=  left  <=   right   <=y 
    if(left>=x && right<=y)
	{
	    return segtree[node];	
	}	
	int mid=(left+right)/2;
	int maxn=0;
	//  如果：   x  <=  mid   
	if(x<=mid)maxn=max(maxn,query(2*node,left,mid,x,y));
		
	// 如果：    mid <= y   
	if(y>mid)
maxn=max(maxn,query(2*node+1,mid+1,right,x,y));
	return maxn;
} 

```


于是这道题把上面结合一下就可以过了这道题了，大家自己结合一下

---

## 作者：ygl666666 (赞：0)

## 题意
找两朵魅力值相差最大的花，和方案数。
## 思路
先排序，找出第一个数和最后一个数，求他们的差，再统计有多少和第一个数和最后一个数相等的数。如果他们相等，证明所有数相等，差就是0，方案数就是花数量*（花数量-1）/2;如果不相等方案数就是最小数的个数*最大数的个数。
## Code
```
/**/
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000001],ansa,ansb;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n);//排序
	int c=a[0],d=a[n-1]; //把第一个数和最后一个数的值赋给c,d
	for(int i=0;i<n;i++){
		if(a[i]==c){
			ansa++;//统计第一个数有多少个
		}
		if(a[i]==d){
			ansb++; //最后一个多少个
		}
	}
	if(c==d){//如果相等
		cout<<d-c<<" "<<n*(n-1)/2<<endl;
		return 0;
	}//不相等
	cout<<d-c<<" "<<ansa*ansb<<endl;
	return 0;
}
```
## End


---

## 作者：米奇奇米 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//用一下快读，输入优化一下
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,mx,mn;
int a[200010];//一定要按题意大小来开数组
long long ans,m1,m2;
int main()
{
	n=read();
	for (int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);//排一遍序，非常重要
	mn=a[1];
    mx=a[n];
	for (int i=1;i<=n;i++)
	{
	  if (a[i]==mx)m1++;//统计最小数个数
	  if (a[i]==mn)m2++;//统计最大数个数
	}
	ans=m1*m2;//利用乘法原理来统计方案数量
    if (mx==mn)
    ans=(long long)(n-1)*n/2;//要不然就利用这个公式
	printf("%d %lld",mx-mn,ans);//按照题目意思输出即可
}
```

---

