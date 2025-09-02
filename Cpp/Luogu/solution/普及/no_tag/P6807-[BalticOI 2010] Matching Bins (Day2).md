# [BalticOI 2010] Matching Bins (Day2)

## 题目描述

给定一行 $N$ 个整数 $A_1,A_2,\dots,A_N$。 $M=\max\{A_1,A_2,\dots A_N\}$。

你需要找到一个最大的整数 $K$，使得从左至右共 $K$ 个数都小于接下来的 $K$ 个数。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\le M\le 2\times 10^3$，$1\le N\le 2\times 10^4$，$1\le A_i\le M$。

----

**题目译自 [BalticOI 2010](https://www.luogu.com.cn/problem/U125995) [Day2](https://boi.cses.fi/files/boi2010_day2.pdf) *T1 Matching Bins***。

## 样例 #1

### 输入

```
5 10
2 2 1 4 3 2 5 4 2 3```

### 输出

```
4```

# 题解

## 作者：yewanxingkong (赞：7)

我第一眼看到这个题时，立马就想到了暴力。

枚举 $k$ ，把前 $k$ 个数和接下来 $k$ 个数从小到大排序然后一一比大小，出现前面 $k$ 个里的第几个数大于等于后面 $k$ 个里的第几个数就排除掉。

然后想到优化：

1. 从后往前枚举，最先找到的正确的那个就是答案。

2. $k$ 的最大值为 $n/2$  ，因为如果大于这个数，加下来的数就凑不齐k个了。

3. 既然给了 $m$ 那就一定是有用的，记录下最早的那个 $m$ , $k$ 值一定是比这个 $m$ 所在序号小的，因为后面不可能到比最大值还大的数。

4. 用桶排。 $sort$ 一定是会炸的。

就下来就是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int m,n,ji=1000000000,f[20010],fa[2010],fb[2010],chu,o;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int check(int x){
    int oo=1;
	for(int i=1;i<=x;i++)
		fa[f[i]]+=1;
	for(int i=x+1;i<=2*x;i++)
		fb[f[i]]+=1;
	int a=1,b=1;
	for(int i=1;i<=x;i++){
		while(!fa[a])a++;
		while(!fb[b])b++;
		if(a>=b)oo=0;
		fa[a]--;
		fb[b]--;
	}
	return oo;
}
int main(){
	m=read();
	n=read();
	for(int i=1;i<=n;i++){
		f[i]=read();
		if(f[i]==m&&o==0){
			o=1;
			ji=i;
		}
	}
	ji=min(ji-1,n/2);
	for(int i=ji;i>=1;i--)
		if(check(i)){
			chu=i;
			break;
		}
	cout<<chu;
	return 0;
}
```


---

## 作者：chl090410 (赞：1)

## The Solution to P6807 [BalticOI 2010 Day2] Matching Bins

### 题目大意

找最大的整数 $K$，使得从左至右共 $K$ 个数都能在接下来的 $K$ 个数中找到一个数比它小（一个数只能用一次）。

### 分析

因为当 $K>N/2$ 时，接下来的数就不足 $K$ 个了，所以 $K$ 的最大值为 $N/2$。 

我们很容易想到暴力方法：从 $1$ 到 $N/2$ 枚举 $K$，每次分别对前 $K$ 个数和接下来的 $K$ 个数排序，再分别比对每个位置上的值是否满足要求。 

但该算法最坏时间复杂度为 $O(N^2)$，而 $N\le2\times10^4$，会超时，所以考虑优化。

优化方法如下：

- 题目中的信息不会白给，每个信息都必定有用。仔细观察题目，我们会发现还有一个信息 $M\le2\times10^3$ 没用。外层的枚举 $K$ 无法优化，所以我们考虑优化排序与比对。桶排的时间复杂度为 $O(M)$，在本题中远比 ```sort``` 快。所以我们考虑用桶排对数组进行排序。

- 比对两个数组中数的大小时也可以用桶进行优化。我们分别用两个桶记录前 $K$ 个数和接下来的 $K$ 个数，再遍历两个桶，比对两个数组每个位置上的值出现的先后，后出现的大于先出现的。这样，时间复杂度就由 $O(N)$ 降到了 $O(M)$。

优化后，总时间复杂度降到了 $O(N\times M)$，循环次数降到了约 $4\times10^7$ 次，就不会超时了。

### 完整代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int m,n,a[20005],b[20005],t[20005],f,mx,l,r;
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n/2;i++){
		t[a[i]]--;
		b[a[i]]++;
		t[a[2*i]]++;
		t[a[2*i-1]]++;
		for(int j=1;j<=m;j++){
			if(l-r<t[j]){
				f=1;break;
			}
			l+=b[j];r+=t[j];
			if(l>=i){
				break;
			}
			if((r!=0 && r>l)){
				f=1;
				break;
			}
		}
		if(f!=1){
			mx=i;
		}
		f=0;l=0;r=0;
	}
	cout<<mx;
	return 0;
}


---

## 作者：Sun_wtup (赞：1)

# P6807 [BalticOI 2010 Day2] Matching Bins 题解
[题目传送](https://www.luogu.com.cn/problem/P6807)
## 题意
给出 $n$ 个整数以及这 $n$ 个整数中的最大值 $m$，求最大整数 $k$，使得前 $k$ 个数一一对应得都小于接下来的 $k$ 个数。
## 分析与思路
这是一道很明显的暴力枚举。我们要枚举 $k$，首先我们要找枚举（从大往小枚举，也就是从后往前）起点，要让枚举的次数尽量小，然后从大向小开始枚举（为了使 $k$ 尽量大），对于每一个 $k$，处理出前 $k$ 个和接下来的 $k$ 个，排序，然后依次比较，看是否符合题目要求如果满足，就输出当前 $k$，如果不满足，就继续枚举。如果到最后也不满足，就输出 $0$。
## 实现
首先枚举起点显然要小于等于 $n\div 2$，但为了不超时，就再看一下最大值的位置，如果最大值的位置小于 $n\div2$，我们就从最大值位置再减 1 开始枚举（因为为了尽量满足题目，这样最大值就只能在接下来的 $k$ 个中）。然后枚举 $k$，给前 $k$ 个和接下来的 $k$ 个进行排序，不要用 `sort`，用桶排因为 $A_i\leqslant2\times10^3$，可以开数组，而且桶排快，用 `sort` 会炸（别问我咋知道的）。排完序后再开一个数组存起来，因为同样是 $k$ 个，直接比较就行，最终满足题意就输出，不满足就继续。
温馨提示：$k$ 可能等于 $0$。
## Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
int a[20005];
int barrel1[20005];
int barrel2[20005];
int x[20005],y[20005];
int beginn=0x7fffffff;
void cler(){//清零
	for(int i=1;i<=2000;i++)barrel1[i]=0;
	for(int i=1;i<=2000;i++)barrel2[i]=0;
}
bool bucket(int n){
	cler();
	for(int i=1;i<=n;i++){//桶排
		barrel1[a[i]]++;
	}
	for(int i=n+1;i<=2*n;i++){//桶排
		barrel2[a[i]]++;
	}
	int cnt1=0,cnt2=0;
	for(int i=1;i<=2000;i++){
		if(barrel1[i]!=0){
			cnt1++;
			x[cnt1]=i;
			barrel1[i]--;
			if(barrel1[i]>0)i--;
		}
	}
	for(int i=1;i<=2000;i++){
		if(barrel2[i]!=0){
			cnt2++;
			y[cnt2]=i;
			barrel2[i]--;
			if(barrel2[i]>0)i--;
		}
	}//分别处理到两个数组里
	for(int i=1;i<=cnt1;i++){
		if(x[i]>=y[i])return 0;
	}//比较
	return 1;
}
int main()
{
	//  freopen("Luogu_P_6807.cpp.in","r",stdin);
	//  freopen("Luogu_P_6807.cpp.out","w",stdout);
	int maxn,n;
	cin>>maxn>>n;
    bool flag=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==maxn and flag==0){
            flag=1;
			beginn=i;
		}
	}
    beginn=min(beginn,n/2);//找枚举起点
	for(int k=beginn;k>=1;k--){//求最大，从大往小枚举
		if(bucket(k)){
            cout<<k<<endl;
            return 0;
		}
	}
    cout<<0<<endl;
	//  fclose(stdin);
	//  fclose(stdout);
	return 0;
}
```

---

## 作者：hubin1 (赞：1)

# Matching Bins

## 题目描述
找到一个最大的整数 $K$，使得从左至右共 $K$ 个数都小于接下来的 $K$ 个数。

## 思路
1. 暴力枚举。
2. 选择起点。从左到右 $K$ 个数要小于它们后边的 $K$ 个数，所以最大数 $M$ 就应该在右边，因为它是最大的数。我们应该从 $K$ 最大的时候开始枚举，即 $N/2$ 这个位置。综上所述，取这两个值的最小值。
3. 排序后比较。如果对应的不行，其他的也不行。因为还要考虑其他的数。排序要用桶排，这点很重要。
4. 最后不要忘记 $K$ 等于 $0$ 的情况。

## Code

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=1e5+10;
int a[MAX];
int temp_a[MAX],temp_b[MAX];
int h[MAX],b[MAX];
signed main()
{
    int n,m;
    int maxx_id;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        if(a[i]==n)
            maxx_id=i;
    }
    int s=min(m/2,maxx_id);
    bool flag=0;
    for(int i=s;i>=1;i--)
    {
        flag=0;
        for(int j=1;j<=i;j++)
        {
            temp_a[a[j]]++;
            temp_b[a[j+i]]++;
		} 
        int len_a=0,len_b=0;
        //h,b 这两个数组不用清空，因为没有必要。
        for(int j=1;j<=n;j++)
        {
            while(temp_a[j])
            {
                temp_a[j]--;
                h[len_a++]=j;
            }
            while(temp_b[j])
            {
                temp_b[j]--;
                b[len_b++]=j;
            }
        }
        //桶排
        for(int j=0;j<i;j++)
        {
            if(h[j]>=b[j])//比较
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<0<<endl;//这个0是非常重要的。
    
    return 0;
}

```

---

## 作者：Starlight_Glimmer (赞：1)

[My Blog](https://www.cnblogs.com/lyttt/p/14050220.html)

[题目链接](https://www.luogu.com.cn/problem/P6807)

### 题目解析

是考试的题目。

~~虽然是个签到题但我还是挣扎了很久，而且我个智障把文件名打错了，签到失败嘤嘤嘤~~

------

首先简化一下题意：找到一个最大的$k$，使得$a[k+1]$至$a[2k]$中的数都能在$a[1]$到$a[k]$中匹配到一个比它严格小的数（每个数都只能和一个数匹配）。如果没有这样的$k$，输出$0$。

（也可以理解成左半边的数去在右半边找一个比它大的数，是一样的，不过题意理解不同后面的思考分析应该也会相应有所变化）

首先考虑暴力枚举$k$，从大到小枚举，然后去$check$它是否符合情况。

$k$的范围是$min(\frac n 2,pos)$ 

$pos$是最大值第一次出现的位置，因为最大值不可能出现在前半部分，没有箱子可以装它。注意存在整个数列没有$m$的数据。

------

下面来考虑一下这个$check$该怎么写。

贪心地想，我们应该给每个右半部分的数安排一个小于它的最大的数，暴力做这个的话，我们就要每次排序，然后$lower\_bound$，想想就很可怕。

对于这种查找左边小于某个数的问题，我们可以考虑一下权值树状数组。

我们把左半边的数插进权值$BIT$里面，然后对于右半边的数查询有多少个比它小的值。
由于左半边的数可能会被“用掉”，所以我们把右半边的数从小到大排序，然后查询有多少个比它小的左半边的数。
而对于第$i$个数而言，它前面有$i-1$个数用掉了左半边的一些数，而且用掉的这些数一定是小于它自己的（用掉的这些数小于它前面的数），所以查到的数的个数减去$i-1$是第$i$个数可以用到的数，如果这个数值小于$0$，那么这个$k$是不可行的。

然后你就得到了$75pts$的好成绩。

```cpp
bool check(int x)
{
	if(x==0) return 1;
	//memset(tree,0,sizeof(tree));
	//for(int i=1;i<=x;i++)
	//	Update(a[i],1);
	if(x!=lim) Update(a[x+1],-1);
	memcpy(b,a,sizeof(a));
	sort(b+x+1,b+2*x+1);
	for(int i=x+1;i<=2*x;i++)
	{
		int tmp=Query(b[i]-1)-(i-x-1);
		if(tmp<=0) return 0;
	}
	return 1;
}
```

而整个$k$变化的过程中，左半边的数可以通过权值$BIT$维护，可以可持续发展。但是右边的数的话，我们每次要排序，要查询，最坏复杂度可以达到$n^2$。而我们又必须要重新排序再枚举右半边的数才能知道它具体能不能匹配得到一个数字。

------

我们想想能不能让右半边的数也可持续发展一下，换句话说，能不能让查询与排序无关。

还是利用权值$BIT$，把右边的数的查询变成一个修改$(a[i]-1,-1)$，而现在$k$的变化只会影响到这些位置：（假设$k-1$变成$k $，这里显然顺着做要顺一点，不用提前插入一些元素

1. $a[2k-1],a[2k]$加入右半部分
2. $a[k]$从前半部分跳到了右半部分

对应一下修改：

1. $(a[2k-1]-1,-1)$
2. $(a[2k]-1,-1)$
3. $(a[k]-1,1)$（$a[k]$跑走了，所以把它之前的查询撤回
4. $(a[k],1)$

如何判断当前的$k$是否可行呢？

查询权值$BIT$的每一个位置（的前缀和），如果有小于零的地方，说明有一个右半部分的数找不到匹配的数，不可行，否则就可行。

所有可行解取$max$即可。

------

看了一圈没有和我写法一样的，倒是有两位初三的同学写了权值线段树，一个$60pts$，一个$100pts$，不过我看了一下，修改的查询的$±1$正好和我是相反的，大概是因为权值线段树是区间加减，所以较大的区间应该为$+1$才能保证某一段区间和小于零时不成立吧。

别人的写法好巧妙的，但对于我来说不太自然。

瞪了好久才想到优化，不过最后自己独立瞪出来了，~~还顺手拿了个最优解~~，~~在洛谷享受到了coding的快乐~~（虽然这题很水

理论复杂度应该是$O(nmlogm)$，跑得比$O(nm)$的算法快我也不知道为什么。

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 20005
#define M 1005
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
int m,n,lim=-1,ans=0;
int a[N],b[N];
int tree[M];
inline int lowbit(int x)
{
	return x&(-x);
}
inline int Query(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=tree[x];
	return res;
}
inline void Update(int x,int val)
{
	for(;x<M-5;x+=lowbit(x))
		tree[x]+=val;
}
int main()
{
	//freopen("bins.in","r",stdin);
	//freopen("bins.out","w",stdout);
	m=rd(),n=rd();
	m++; 
	for(int i=1;i<=n;i++)
	{
		a[i]=rd()+1;
		if(a[i]==m&&lim==-1)
			lim=i;
	}
	lim=min(lim,n/2);
	//if(lim==-1) lim=n/2;
	//数据里居然有整个数列都没有m的 出题人大骗子嘤嘤嘤
	//其实这个m就是来告诉你值域很小的吧 可这也不需要专门输入一个m啊 直接在数据范围里说不好么233 
	for(int k=1;k<=lim;k++)
	{
		Update(a[2*k]-1,-1);
		Update(a[2*k-1]-1,-1);
		Update(a[k]-1,1);//a[k]不在后半部分了 得撤回
		Update(a[k],1);
		bool flag=0;
		for(int i=1;i<=m;i++)
		{
			int tmp=Query(i);
			if(tmp<0)
			{
				flag=1;
				break;
			}
		}
		if(!flag) ans=max(ans,k);
	}
	printf("%d\n",ans);
	return 0;
}
```

### ►Code View 75pts TLE

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 20005
#define M 1005
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
int m,n,lim=-1;
int a[N],b[N];
int tree[M];
inline int lowbit(int x)
{
	return x&(-x);
}
inline int Query(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=tree[x];
	return res;
}
inline void Update(int x,int val)
{
	for(;x<M-5;x+=lowbit(x))
		tree[x]+=val;
}
bool check(int x)
{
	if(x==0) return 1;
	//memset(tree,0,sizeof(tree));
	//for(int i=1;i<=x;i++)
	//	Update(a[i],1);
	if(x!=lim) Update(a[x+1],-1);
	memcpy(b,a,sizeof(a));
	sort(b+x+1,b+2*x+1);
	for(int i=x+1;i<=2*x;i++)
	{
		int tmp=Query(b[i]-1)-(i-x-1);
		if(tmp<=0) return 0;
	}
	return 1;
}
int main()
{
	//freopen("bins.in","r",stdin);
	//freopen("bins.out","w",stdout);
	m=rd(),n=rd();
	for(int i=1;i<=n;i++)
	{
		a[i]=rd();
		if(a[i]==m&&lim==-1)
			lim=i;
	}
	lim=min(lim,n/2);
	if(lim==-1) lim=n/2; 
	for(int i=1;i<=lim;i++)
		Update(a[i],1);
	for(int k=lim;k>=0;k--)
	{
		if(check(k))
		{
			printf("%d\n",k);
			break;
		}
	}
	return 0;
}
```



---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6807)

## 题意：

找最大的整数 $K$，使得从左至右共 $K$ 个数都能在接下来的数中找到一个数比它小。

## 思路：

暴力枚举，桶排序。

枚举时把左边和右边都排一下序，然后再从 $1$ 到 $K$ 比较左右两边，如果当前右边 $\le$ 左边，直接 continue；若没有问题，就输出然后 return。

---

## 作者：__Ginka__ (赞：0)

# Matching Bins

### 大致题意：
给一行 $N$ 个整数 $ A_i $。$M$ 为$A$ 数组中最大的数字。

然后需要找到一个最大的 $K$，让接下来的 $K$ 个数都大于从左至右的 $K$ 个数。

### 简略思路
## 思路概述

1. **枚举 K 值**：
   - 从 $ N \div 2 $ 开始倒序枚举 $ K $，寻找最大的 $ K $。

2. **计数与存储**：
   - 使用两个计数数组 $ bl $ 和 $ br $ 来存储左边和右边部分的数字出现次数。
     - $ bl[j] $：左边部分数值为 $ j $ 的元素数量。
     - $ br[j] $：右边部分数值为 $ j $ 的元素数量。
   - 使用两个数组 $ zuo $ 和 $ you $ 来存储左边和右边部分的元素。

3. **生成排序后的数组**：
   - 将数据转换为实际的元素数组：
     - 从 $ 1 $ 到 $ M $，将 $ bl $ 和 $ br $ 中的计数转化为具体的元素放入 $ zuo $ 和 $ you $ 中。

### 复杂度

- **时间复杂度**：
  - 主循环为 $ O(N \div 2) $ 次迭代，每次迭代中有 $ O(M) $ 的操作，因此总的时间复杂度约为 $ O(N  M) $。


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX_N=22333;
long long m,n,a[MAX_N],zuo[MAX_N],you[MAX_N];
int main()
{
    scanf("%lld%lld",&m,&n);
    for(long long i=1;i<=n;i++)
	{
        scanf("%lld",&a[i]);
    }
    //从N/2到1枚举K
    for(long long k=n/2;k>=1;k--)
	{  
		long long bl[2233],br[2233],aa=0,bb=0;
        //重置一下左右计数数组
        for(long long j=1;j<=m;j++)
		{
            bl[j]=0;
            br[j]=0;
        }
        //将前K个数和接下来的K个数分别存入计数数组
        for(long long j=1;j<=k;j++)
		{
            br[a[j+k]]++;
            bl[a[j]]++;
        }
        //将计数转换为排序后的数组
        for(long long j=1;j<=m;j++)
		{
            while(br[j]>0)
			{
                br[j]--;
                you[++bb]=j;//右
            }
            while(bl[j]>0)
			{
                bl[j]--;
                zuo[++aa]=j;//左 
            }
        }
        //比较左边和右边
        bool v=0; //开个boll标记是否找到不匹配的 
        for(long long j=1;j<=k;j++)
		{
            if(zuo[j]>=you[j])
			{
                v=1;//找到不满足条件的情况
                break;
            }
    	}
        //v没变说明找到了 
        if(!v)
		{
            printf("%lld\n", k);
            return 0;
        }
    }
    //循环都结束了肯定无解,输出 0
    printf("0");
    return 0;
}

```

---

## 作者：Daniel_xu (赞：0)

# P6807 [BalticOI 2010 Day2] Matching Binst 题解
## 题意
对于 $n$ 个整数 $a_1,a_2,a_3, \dots ,a_n$ 找出一个最大的 $k$，使得前 $k$ 个数中的每个数都**小于（不是小于或等于）**$k+1$ 之后的 $k$ 个数中的一个（每次不能重复）。若无解，请输出 `0`。
## 思路
用暴力枚举。对于枚举的每一个 $k$，比较最小的与最小的，次小的与次小的……即可得到答案。\
上述方法需要用到排序，如果使用 sort 函数，时间复杂度 $O(n^2 \log{n})$，不可。题目要求 $M \le 2 \times 10^3$，如果使用桶排序，依次比较，时间复杂度 $O(NM)$，可通过本题。\
具体实现细节见代码注释。
## AC代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e4+5,M=2e3+5;
int a[N];
int t1[M],t2[M];//建两个桶 
int n,m;
bool ok(int k){//判断是否符合要求
	//清空桶 
	memset(t1,0,sizeof(t1));
	memset(t2,0,sizeof(t2));
	for(int i=1;i<=k;i++){//将数据存入桶中 
		t1[a[i]]++;
		t2[a[k+i]]++;
	}
	for(int a=1,b=1,i=1;i<=k;i++){//O(M)
		//寻找下一个最小的数字 
		while(!t1[a])a++;
		while(!t2[b])b++;
		if(a>=b)return false;//既a<b不成立，不符合要求 
		//消除当前数字 
		t1[a]--;
		t2[b]--;
	}
	//符合要求 
	return true;
}
int main(){
	//输入 
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int k=n>>1;k>=1;k--){//依次枚举每一个k，O(NM) 
		if(ok(k)){//符合要求 
			cout<<k;
			return 0;
		}
	}
	//不符合 
	cout<<0;
	return 0;
}
```

---

## 作者：run_away (赞：0)

## 题意

~~这个翻译有点小坑，还不如自己看原文。~~

给定一个长度为 $N(N\le 2\times 10^4)$ 的整数序列 $A$，求一个最大的 $K$，满足前 $K$ 个数能在接下来 $K$ 个数中找到一个比他大的数，且每个数能且只能匹配一次。

## 分析

$N$ 的范围卡掉了 $O(N^2\log N)$ 的做法，sort 排序光荣去世。

再看这个 $M(M\le 2\times 10^3)$，小范围加输入提示明显告诉用桶排。

因为总共 $2K$ 个数，所以从 $\frac{n}{2}\sim 1$ 枚举 $K$。

枚举时把左边和右边都排一下序，然后再从 $1$ 到 $K$ 比较左边和右边，如果当前右边小于等于左边，直接 continue；若没有问题，就输出、return。

最后别忘了 $K$ 无解的情况，输出一个 0。

总时间复杂度 $O(N^2)$。

## Code

```cpp
#include<bits/stdc++.h>  
typedef long long ll;  
using namespace std;  
#define read(x) scanf("%lld",&x)  
ll m,n,a[20005],bl[2005],br[2005],l[20005],r[20005];  
signed main(){  
    read(m),read(n);  
    for(ll i=1;i<=n;++i)read(a[i]);  
    for(ll i=n/2;i>=1;--i){  
        bool vis=0;  
        for(ll j=1;j<=i;++j){  
            bl[a[j]]++;//左边++  
            br[a[j+i]]++;//右边++  
        }  
        ll la=0,lb=0;  
        for(ll j=1;j<=m;++j){  
            while(bl[j])--bl[j],l[++la]=j;  
            while(br[j])--br[j],r[++lb]=j;  
        }//最终还原排序后数组  
        for(ll j=1;j<=i;++j){  
            if(l[j]>=r[j]){//右边小于等于左边  
                vis=1;  
                break;  
            }  
        }  
        if(vis==0){  
            printf("%lld\n",i);  
            return 0;  
        }//没问题直接输出  
    }  
    puts("0");//无解情况  
    return 0;  
}
```

---

## 作者：wzkdh (赞：0)

首先这个题的翻译很令人迷惑，我也是看了很久又参考原题目才看懂的。

题意指的是开始的k个数在接下来的k个数里，每一个都可以找到一个大于这个数的数，例如样例，当$k$=4时，2 2 1 4这四个数都可以在之后3 2 5 4这四个数里找到一个更大的数![样例说明](https://cdn.luogu.com.cn/upload/image_hosting/txwe42yd.png)
而当$k$=5时，无论如何都有至少一个数在之后的k个数中找不到更大的数。

所以这道题的做法就很明显了，从大到小枚举$k$，然后将前k个数b[ k ]与k+1到2 * k这k个数c[ k ]排序，如果每一个b[i]都小于c[i]，则合法，k为答案，否则继续向下枚举。

但是这样写会t掉，所以我们来考虑优化，首先k不必从最后开始枚举，最大从中间开始即可，因为当k大于数字数量一半的时候，剩下的数的个数小于k，肯定不会有k个大于前面的数。

其次，当前半段有最大值的时候必定是不可能的，因为后面最大也只能和他相等，不可能有比它大的数，否则最大值就不是它了。

综上所述，我们可以从中点与最大值所在点较靠前者开始枚举，但是加上这个优化后还是会t两个点，剩下唯一可以优化的就只有排序了，我们使用桶排序代替sort，就可以a掉这道题了。

具体细节可以参考代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int m,n,a[20010],maxn=-1,maxx,b[20010],c[20010],bj;//a为原数组，tb，tc为桶排序数组，b，c为排序之后的前k个数与之后的k个数
int tb[20010],tc[20010]; 
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]>maxn)
		{
			maxn=a[i];
			maxx=i;
		}
	}
	int st=min(maxx,n/2);
	for(int i=st;i>=0;i--)
	{
		for(int j=0;j<i;j++)
			tb[a[j]]++;
		for(int j=i;j<i*2;j++)
			tc[a[j]]++;
		int cnt=0;
		for(int j=0;j<=maxn;j++)
		{
			
			while(tb[j])
			{
				tb[j]--;
				b[cnt++]=j;
			}
		}
		cnt=0;
		for(int j=0;j<=maxn;j++)
		{
			while(tc[j])
			{
				tc[j]--;
				c[cnt++]=j;
			}
		}
		for(int j=0;j<i;j++)
		{
			if(b[j]>=c[j])
			{
				bj=1;
				break;
			}
		}
		if(bj)
		{
			bj=0;
			continue;
		}
		cout<<i;
		return 0;
	}
	return 0;
} 

---

## 作者：JK_LOVER (赞：0)

## 题意
找到一个最大的整数 $K$ ，使得从左至右共 $K$ 个数都总能在接下来的 $K$ 个数找到大于它的数字，要求一一对应。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6807)
## 分析
- 这个值域是可以开个桶来记录的。那么我们可以考虑什么时候是一定有解的。那么有个初步的想法。

- 枚举 $K$ ，把左边的数字排序，由大到小考虑是否可以在右边找到一个比它大的。时间复杂度为 $O(n^2m)$ 。考虑如何优化这个过程，

- 那么根据不等号的传递性，鸽巢原理。如果做一个后缀和 $sumL_i,sumR_i$ 分别从 $m$ 到 $i$ 的个数，如果对于每一个数都满足 $sumL_i \le sumR_{i+1}$ 那么这个就是可行的 $K$ 。那么我们从大到小枚举 $K$ ，找到合法的就退出，这一定是最优的。
## 代码

```cpp


#include<bits/stdc++.h>
using namespace std;
const int N = 4e6+1000;
int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;

}
int l[N],r[N],c[N][2],n,m,a[N];
int main()
{
	m = read();n = read();
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = 1;i <= n/2;i++) l[a[i]]++,r[a[i+n/2]]++;
	for(int i = n/2;i;i--){
		int vis = 0;
		for(int j = m;j >= 1;j--)
		{
			c[j][0] = c[j+1][0] + l[j];
			c[j][1] = c[j+1][1] + r[j]; 
		}
		for(int j = m;j >= 1;j--){
			if(c[j][0] > c[j+1][1]) vis=1;
		}
		if(!vis) {
			cout << i << endl;
			return 0;
		}
		l[a[i]]--;r[a[i]]++;
		r[a[i*2]]--;r[a[i*2-1]]--;
	}
	cout << "0" <<endl;
	return 0;
}






```



---

