# Karen and Neighborhood

## 题目描述

It's been long after the events of the previous problems, and Karen has now moved on from student life and is looking to relocate to a new neighborhood.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815E/8bd2a5609d0d80a04305caa2f81f70648ac35159.png)The neighborhood consists of $ n $ houses in a straight line, labelled $ 1 $ to $ n $ from left to right, all an equal distance apart.

Everyone in this neighborhood loves peace and quiet. Because of this, whenever a new person moves into the neighborhood, he or she always chooses the house whose minimum distance to any occupied house is maximized. If there are multiple houses with the maximum possible minimum distance, he or she chooses the leftmost one.

Note that the first person to arrive always moves into house $ 1 $ .

Karen is the $ k $ -th person to enter this neighborhood. If everyone, including herself, follows this rule, which house will she move into?

## 说明/提示

In the first test case, there are $ 6 $ houses in the neighborhood, and Karen is the fourth person to move in:

1. The first person moves into house $ 1 $ .
2. The second person moves into house $ 6 $ .
3. The third person moves into house $ 3 $ .
4. The fourth person moves into house $ 2 $ .

In the second test case, there are $ 39 $ houses in the neighborhood, and Karen is the third person to move in:

1. The first person moves into house $ 1 $ .
2. The second person moves into house $ 39 $ .
3. The third person moves into house $ 20 $ .

## 样例 #1

### 输入

```
6 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
39 3
```

### 输出

```
20
```

# 题解

## 作者：Leap_Frog (赞：2)

### P.S.
**可怜场压轴题题解一血！！！**  

### Description.
可怜在一条 $n(n\le 10^{18})$ 栋房子的街上。  
有 $K$ 个人住了进来，每个人会选择到目前已经有人的所有房间最短距离最大的那个房子住进去。  
如果有多个，就选择最靠左的那个房子。  
可怜前面有 $K-1$ 个人，问可怜住在第几个房子。  
~~我是狗仔队！！！！~~  

### Solution.
定义符号 $[k]$ 表示一个长度为 $k$ 的区间（（。  

首先，第一个人会住在 $1$ 号房间，第二个人会住在 $n$ 号房间，直接特判。  
然后接下来相当于有一个区间 $(1,n)$，每次取偏左的中点，砍成两个区间。  
这样砍 $O(\log n)$ 次就可以把整个区间砍完，然后就找到了可怜的家。  

**但是这个做法是假的。** 因为每次砍区间不一定是从左到右。  
$[10]\rightarrow[4],[5]$，此时会先切割 $[5]$ 然后切割 $[4]$，所以无法直接处理。  
所以我们用上文方法只能在 $O(\log n)$ 的时间内求出 $(n)$ 的序列被切成了几个长度 $\ge k$ 的序列。  

有一个性质，是我们像刚刚这样划分区间，每次对所有区间切割，所有区间长度个数是 $O(1)$ 的，最多可能有两个。（显然  
还有一个性质，就是如果 $\left\lfloor\frac {n-1}2\right\rfloor\ne \left\lfloor\frac {m-1}2\right\rfloor$ 且 $n<m$，那 $(m)$ 肯定比 $(n)$ 先被切割。  
所以它具有单调性，我们可以用 $O(\log ^2n)$ 的复杂度（一个 $\log$ 是上文切割）求出答案的长度（误差不超过 $1$。  

然后，我们找到了答案的长度，接下来直接处理整个序列（记录位置。  
每次肯定是形如把右边大于当前的消掉，然后把左边等于当前的消掉，然后把右边等于当前的消掉。  
然后以上三个的数量是可以 $O(\log n)$ 求的，所以可以判断当前是在那个位置。  
然后就继续往那边递归即可。  

### Coding.
```cpp
inline ll solve(ll n,ll w)
{//这个是 log 查
	ll x=n,y=n-1,s1=1,s2=0,tt=0;if(x<=w*2) return 0;
	for(;y>=w*2;x/=2,y=x-1)
	{
		if(y==w*2) return tt+s1;else tt+=s1+s2;
		if(x&1) s1=2*s1+s2;else s2=2*s2+s1;
	}return tt;
}
inline ll work(ll l,ll r,ll p,ll k)
{//这个是找答案
	ll md=(l+r)>>1;if(k==1) return md;
	ll v1=solve(md-l,p),v2=solve(r-md,p+1);
	if(k>v1+v2+1) return work(md+1,r,p,k-v1-1);
	else return work(l,md-1,p,k-v2-1);
}
int main()
{
	int n,K;read(n,K);if(K==1) return puts("1"),0;
	if(K==2) return printf("%lld\n",n),0;else K-=2;
	ll l=1,r=n/2+1,rs=0;while(l<=r)
		{ll md=(l+r)>>1;if(solve(n-2,md)>=K) rs=md,l=md+1;else r=md-1;}
	return printf("%lld\n",work(2,n-1,rs,K)),0;
}
```

---

