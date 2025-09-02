# Double Happiness

## 题目描述

给定闭区间 $ [l,r] $，找出区间内满足 $  t=a^{2}+b^{2} $ 的所有素数 $ t $ 的个数（$ a,b $ 为任意正整数）。

## 样例 #1

### 输入

```
3 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 66
```

### 输出

```
7
```

# 题解

## 作者：くろねこ (赞：4)

首先了解一个定理
#### 费马二平方定理
1. 除2以外的所有的素数都可以分为两类:4k + 1,4k + 3
2. 4k + 1可以表示为2个整数的平方和,但4k + 3不行

然后就可以愉快的开始筛素数啦~

由于数据量过大int存不下,故采用bitset(按位存储,空间优秀)


------------

```cpp
#include <bitset>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rg register
int tot,pri[23333333],ans;
bitset <300005005> flag;//我觉得bitset是个好东西 
void make_prime_list(int r)
{
    for (rg int i = 2;i <= r;++i)
    {
        if (!flag[i]) pri[++tot] = i;
        for (rg int j = 1;j <= tot && pri[j] * i <= r;++j)
        {
            flag[i * pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
}
int l,r;
int main()
{
    scanf("%d%d",&l,&r);
    make_prime_list(r);
    for (rg int i = 1;i <= tot;++i)
    {
    	//费马二平方定理: 除2以外的所有的素数都可以分为两类:4k + 1,4k + 3
		//4k + 1可以表示为2个整数的平方he,但4k + 3不行 
        if (pri[i] < l) continue;
        if (pri[i] % 4 == 1) ++ans;
    }
    if (l <= 2 && r >= 2) ++ans;
    printf("%d",ans);
}
```

---

## 作者：Patrickpwq (赞：3)

经过手算枚举过后...我们首先可以发现 符合题目中要求的素数 是可以以4k+1的形式表现出来的
那么问题又回到了更根本的地方 我们只需要筛出l~r里面的素数有哪些 再判断每个素数是不是符合4k+1的形式
这个地方我选择了欧拉线性筛素数 
另外 数据很大 int开不下 只能选用bitset
```cpp
#include<stdio.h>
#include<bitset>
using namespace std;
int ans=0;
int prime[20000005],l,r,cnt;
bitset <300000005>	is;
inline void Euler_shai(int l,int r)
{
	is[0]=is[1]=1;//1代表不是 
	for(register int i=2;i<=r;i++)
	{
		if(is[i]==0)	prime[++cnt]=i;
		for(register int j=1;j<=cnt&&i*prime[j]<=r;j++)
		{
			is[i*prime[j]]=1;
			if(i%prime[j]==0)	break;//已经筛过 
		}
	} 
}
int main()
{ 
	scanf("%d%d",&l,&r);
	Euler_shai(l,r);
	
	for(register int i=5;i<=r;i+=4)
	{
		if(i>=l&&is[i]==0)	++ans;
	}
	if(l<=2&&r>=2)	ans+=1;//特判2的情况
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：yx666 (赞：0)

# CF113C Double Happiness 题解
$$\text{Description}$$

给定闭区间 $[l,r]$，找出区间内满足 $t=a^2+b^2$ 的所有素数 $t$ 的个数（$a,b$ 为任意正整数）。

其中 $1\le l\le r\le 3\times10^8$。

$$\text{Solution}$$

首先，我们需要知道**费马二平方定理**：

> 奇素数 $p$ 可以写成两个正整数的平方，当且仅当：
>
> $$p\equiv1\pmod4.$$

证明在这里：[link](https://zhuanlan.zhihu.com/p/382712118)。

但是注意，还有一个偶素数 $2$，满足 $2=1^2+1^2$，需要特判。

整理一下思路：

1. 读入 $l,r$，用[欧拉筛](https://www.luogu.com.cn/problem/P3383)，筛出 $[2,r]$ 之间的素数。

2. 遍历 $[l,r]$ 之间的素数 $p$，$ans$ 累加当且仅当：$p=2$ 或 $p\equiv1\pmod4$。

3. 输出 $ans$。

$$\text{Code}$$

采用欧拉筛加二分，时间复杂度 $O(r+\log cnt+r-l)$，其中 $l,r$ 与题意相同，$cnt$ 是 $[2,r]$ 之间素数的数量。

坑点：

注意空间，`pri_list` 不要开太大，`vis` 用 `bitset` 优化。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define N 300000005

bitset<N>vis;
int cnt=0,pri_list[20000000];			// pri_list 范围：[0,cnt) 左闭右开
static inline void Euler(int n){		// 正常欧拉筛
	vis[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]) pri_list[cnt++]=i;
		for(int j=0;j<cnt;++j){
			int t=pri_list[j]*i;
			if(t>n) break;
			vis[t]=1;
			if(i%pri_list[j]==0) break;
		}
	}
}

int l,r;
signed main(){
	scanf("%d %d",&l,&r);
	Euler(r);			// 预处理 [2,n] 之间的素数
	
	int ans=0;
	if(l<=2&&r>=2)		// 特判 2 
		++ans;
	for(int i=lower_bound(pri_list,pri_list+cnt,l)-pri_list;i<cnt;++i)		// 利用二分找到 [l,r] 中最小的素数
		if(pri_list[i]%4==1) ++ans;
	
	printf("%d",ans);
	return 0;
}
```

---

## 作者：JacoAquamarine (赞：0)

前置知识:

费马二平方和定理

内容如下：

1. 除 $2$ 以外的素数 $x$ 都可以表示成 $x\equiv 1 \pmod{4}$ 或 $x\equiv 3 \pmod{4}$。
2. 当且仅当素数 $x$ 可以表示成 $x\equiv 1 \pmod{4}$ 时， $x$ 为两数平方之和。

为了更高效，筛素数时使用欧拉筛，注意到 `int` 会爆，所以用 `bitset`。

欧拉筛部分代码如下
```cpp
for(int i=2;i<=x;i++){
	if(!vis[i])isp[++sum]=i;
	for(int j=1;j<=sum&&i*isp[j]<=x;j++){
		vis[isp[j]*i]=1;
		if(i%isp[j]==0)break;
	}
}
```
最后累计答案并输出，注意要特判!
```cpp
for(register int i=1;i<=sum;i++)
    if (isp[i]%4==1&&isp[i]>=l)
		ans++;
if(l<=2&&r>=2)ans++;


```

---

## 作者：FReQuenter (赞：0)

在数学中，有一个费马二平方定理。简单来说就是：
除2以外的所有的素数都可以分为 $4x+1$ 和 $4x+3$ 两类。其中 $4x+1$ 可以表示为 $2$ 个整数的平方和。

证明：<https://zhuanlan.zhihu.com/p/382712118>

那么题目就变成了让我们求 $[l,r]$ 之间有多少素数满足 $t=4x+1$。

这样直接欧拉筛法筛一下素数，然后挨个判断即可。

筛素数模板：<https://www.luogu.com.cn/problem/P3383>

注意时间和空间都非常卡。`bool` 类型开不下 $3\times 10^{8}$ 可以用 `bitset`。

## 代码

```cpp
#include<cstdio>
#include<bitset>
#define max(a,b) ((a)>(b)?(a):(b))
#define re register int
#pragma GCC optimize(2,3,"inline","-Ofast")
int prime[20000005],cnt,l,r,ans,i,j;
std::bitset<300000001> is_prime;
inline gnt(int l){
    while(l%4!=1) ++l;
    return max(5,l);
}
int main(){
	scanf("%d%d",&l,&r);
	for(i=2;i<=r;++i){
		if(!is_prime[i]) prime[++cnt]=i;
		for(j=1;j<=cnt&&i*prime[j]<=r;++j){
        	is_prime[i*prime[j]]=1;
        	if(i%prime[j]==0) break;
		}
	}
   //筛素数
	for(i=gnt(l);i<=r;i+=4) if(is_prime[i]==0) ++ans;
	printf("%d",ans+(l<=2&&r>=2));//加上1^2+1^2=2
	return 0;
   //这份代码要 C++20 才能过
}
```

---

## 作者：Cuiyi_SAI (赞：0)

## 解题思路

> 高斯素数，可以理解为一类值为实数但是扩展到了复数域的素数。其不能被分解为如 $(a+b\mathrm{i})(a-b\mathrm{i})$ 这样的共轭乘积的形式，在实数上的意义就是不能被分解成 $a^2+b^2$ 的形式。

显然，题目就是让我们求，在 $[l,r]$ 区间中，有多少个是素数，但是却不是高斯素数的数。

对于此问题，有一个非常著名的定理，费马二平方和定理：

> 对于任意大于 $2$ 的素数 $p$ ，都属于 $p\equiv1\pmod 4$ 和 $p\equiv 3\pmod 4$ 中的一类。若这个素数是高斯素数，当且仅当这个素数 $p\equiv3\pmod 4$。

此定理较为容易理解的证明过程很长，这里无法很好地写出，此题解提供一个 [link](https://www.bilibili.com/video/BV1YT4y1L7Mb?spm_id_from=333.337.search-card.all.click)，感兴趣可以自己去了解。

有了费马二平方和定理作为基础，我们就可以知道答案就是 $[l,r]$ 中模 $4$ 同余 $1$ 的素数个数，直接使用欧拉筛筛出所有素数进行统计即可。

注意，$2$ 并不是高斯整数，因为其可以表示为 $2=(1+\mathrm{i})(1-\mathrm{i})$。

## CODE:

```cpp
#include  <bits/stdc++.h>
using namespace std;
int l,r,ans=0;
int prime[20000010],tot=0;
bitset<int(4e8)> vis;
void p()
{
	vis[1]=1;
	for(int i=2;i<=r;i++)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			if(i>=l) ans+=(i%4==1||i==2);
		}
		for(int j=1;j<=tot&&prime[j]*i<=r;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>l>>r; 
	p();
	cout<<ans;
	return 0;
}
```


---

