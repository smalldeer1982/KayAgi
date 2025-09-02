# [COCI 2013/2014 #1] ORGANIZATOR

## 题目背景

有一场比赛，要求你算出参加决赛的人数。

## 题目描述

参加决赛的人数满足以下描述：

现有 $n$ 个整数，分别为 $A_1,A_2,\cdots,A_n$。

需要找到一个正整数 $x$，假设有 $m(m \geq 2)$ 个 $A_i$ 是 $x$ 的倍数，则参加决赛的人数是 $s$，他的值为 $m\cdot x$。

请注意，对于一个正整数 $x$，如果其对应的 $m$ 值为 $1$，则该方案不合法。

请找出令 $s$ 尽可能大的 $x$，并输出 $s$。

## 说明/提示

#### 样例 1 解释
令 $x=2$，此时 $A_{2,3}$ 满足条件，答案为 $2\times 2=4$。

#### 【数据规模与约定】
- 对于 $30\%$ 的数据，$n<1000$。
- 对于 $100\%$ 的数据，满足 $2\le n\le 2\times 10^5$，$1\le A_i\le 2\times 10^6$。

-----
#### 【说明】
**题目译自 [COCI2013-2014](https://hsin.hr/coci/archive/2013_2014/) [CONTEST #1](https://hsin.hr/coci/archive/2013_2014/contest1_tasks.pdf)  _T5 ORGANIZATOR_。**

## 样例 #1

### 输入

```
3
1 2 4```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 5```

### 输出

```
2```

## 样例 #3

### 输入

```
5
4 6 3 8 9```

### 输出

```
9```

# 题解

## 作者：L_zaa_L (赞：6)

## 分析
乍一眼一看可能会感觉到复杂，所以简化了之后，就大概是这样：找到一个数，求数列中是它的倍数的数之和乘以这个数的最大值。

还算蛮简单的，暴力都可以过，于是只用枚举这个数，并计算倍数的个数，就行了。

# Code
```
#include<stdio.h>
int n,a,b[2000010],maxx;
long long s;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		b[a]++;//统计每个数出现的次数，以便后面去找倍数的个数
		maxx<a?maxx=a:a;//找到最大值
	}
	for(int i=1;i<=maxx;i++){//只用枚举到最大值，毕竟后面的数没有倍数在数列中了
		long long m=0;
		for(int j=i;j<=maxx;j+=i) m+=b[j];//统计倍数个数
		if(m>1) s<m*i?s=m*i:m;//找到最大值
	}
	printf("%lld",s);
	return 0;
}
```

---

## 作者：Utilokasteinn (赞：6)

感觉这只是一道普及难度题。但有些人可能看不懂题目的意思，但看懂了就很简单。

题目大意：给出n个数，找出一个数x，定义一个s储存为x倍数的数个数，再定义一个ans储存m*x，找出最大的ans输出。

解法很简单，用一个桶来储存是a[i]出现的的次数，然后直接暴力枚举x，枚举到n个数中最大的数即可，(但是速度比较慢，由于数据够水，可以过此题)。接着找出为x倍数的数，比较大小，找出最大的ans，最后输出。

代码如下(不吸氧实测5.83ms):
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long n,a[2000001],b[2000001],ans,s,maxn;
//n代表数的个数，a[i]用来储存每个数
//b[i]用来储存数列中i的个数，ans用来储存答案
//s代表倍数的个数，maxn代表枚举的最大值 
int main()
{
	cin>>n;//输入n 
	for(int i=1;i<=n;maxn=max(maxn,a[i++]))
	{//更新a数列中的最大值，并且i++ 
		cin>>a[i];//输入n个数 
		b[a[i]]++;//a[i]的倍数加一 
	}
	for(int i=1;i<=maxn;i++,s=0)
	{//枚举x，枚举到maxn就好了，记得s要清零 
		for(int j=i;j<=maxn;j+=i)s+=b[j];
		//把是i的倍数的个数全部加起来 
		if(s>1)ans=max(s*i,ans);
		//题目中有些s要大于等于2，所以还要加一个if
		//找出ans的最大值 
	}
	cout<<ans;//输出ans 
	return 0;//程序结束 
}
```
最后附上无注释代码(挺精简的，只有333B)：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000001],b[2000001],ans,s,maxn;
int main()
{
	cin>>n;
	for(int i=1;i<=n;maxn=max(maxn,a[i++]))
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=maxn;i++,s=0)
	{
		for(int j=i;j<=maxn;j+=i)s+=b[j];
		if(s>1)ans=max(s*i,ans);
	}
	cout<<ans;
	return 0; 
}
```
谢谢观赏。

---

## 作者：Thomas_Cat (赞：3)

本题其实就是一个pj难度的题 恶评（？）

---

看题。

有人可能没看懂题目，我来简单解释一下，或者说是说明一下做题的思路。

- 输入的时候注意去标记每一个数的倍数的数量，因为我们要求最大值最后判断
- 利用桶排序的思想来找到最大值最后输出即可
- 因为本题数据有点~~毒瘤~~，所以需要开 $long long$


---

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,flag[1000001],MAX_m=-1;
    cin>>n;
    for(int i=1;i<=n;i++){//通过循环输入
        long long tmp;//因为输入的数据后面不会用到，直接用tmp输入即可
        cin>>tmp;
        flag[tmp]++;//标记如果是这个数的倍数的话flag[tmp]++
        MAX_m=max(MAX_m,tmp);//找到最大值方便之后用
    }
    int sum=0,MAXN=-1;
    for(int x=1;x<=MAX_m;x++){//循环暴力枚举x即可
        //这个时候sum注意清零，因为本人在这里卡了好多次
        sum=0;
        for(int i=x;i<=MAX_m;i+=x)//因为我们这里是循环加到max，所以写成这样的形式、
            sum+=flag[i];//这里循环加上所有到max的倍数
        if(sum>1)//特判如果sum大于1
            MAXN=max(sum*x,MAXN);//判断大小，找到最大
    }
    cout<<MAXN;
    //输出最大值
    return 0;    
}
```

---

## 作者：_ouhsnaijgnat_ (赞：2)

这道题的描述个人感觉有点难懂，花了十分钟才完全理解。

## 思路

我用的是两层循环，提交了一下，居然过了。

我的方法是找出这 $n$ 个数字中的最大值，再从 $1$ 枚举到最大值，这里枚举的是题中的 $x$，再从当前枚举到的 $i$ 枚举 $i$ 的倍数，但不能大于最大值，这样来找出 $m$ 的值，再用 $ans$ 记录下最大值，最后输出。

思路这么简单，就来看一下代码吧。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long m,s,a[200003],vis[2000003],mx;
int main(){
   int n;
   cin>>n;
   for(int i=1;i<=n;i++){
       cin>>a[i];
       vis[a[i]]++;//用桶记录出现情况 
       mx=max(mx,a[i]);//找出最大值 
   }
   for(int i=1;i<=mx;i++){//枚举x。 
       m=0;
       for(int j=1;j<=mx/i;j++)//枚举i的倍数。 
           m+=vis[j*i];
       if(m>1)s=max(s,m*i);//判断如果m>1就打擂台。
   }
   cout<<s;
   return 0;
}
```


---

## 作者：LinkZelda (赞：2)

- ###  本题思路：

**方法一**：

我们可以用一个桶来记录每一个数出现的次数，然后暴力统计答案，这个方法实现其他题解已经写得很清楚了，这里不加赘述。

**方法二**：

这题的数据范围**足够弱**，于是我们可以用来练习二分的 $STL$ 。先对整个数组排一次序，然后枚举每一个数并二分找大于这个数的第一个数和小于这个数的第一个数，然后`(upper_bound(a+1,a+n+1,i)-lower_bound(a+1,a+n+1,i))` 就是 $i$ 这个数出现的次数了。

- ###  代码实现：

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

long long a[200005],n,maxx,ans,bin[200005];//bin[i]:i出现的次数

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		{
			scanf("%lld",a+i);
			maxx=max(a[i],maxx); 
		} 
		
	sort(a+1,a+n+1);
	
	for(int i=1;i<=maxx;i++)bin[i]=(long long)(upper_bound(a+1,a+n+1,i)-lower_bound(a+1,a+n+1,i));//计算
	
	for(int i=1;i<=maxx;i++)//暴力统计答案
	{
		int cnt=0;
		for(int j=i;j<=maxx;j+=i)
		{
			cnt+=bin[j];
		}
		if(cnt>=2)ans=max(ans,(long long)cnt*i);
	}
	
	printf("%lld",ans);
	return 0;
 } 
```

---

## 作者：毕瑞成 (赞：2)

**前言：** 其实这道题是一道很水的题，唯一的难点在于容易一直想因数分解等等（可能只有我一开始这样想了）

**题目分析：** 我们考虑开一个桶$b$，存序列中每个数出现的次数

然后枚举当前的正整数$x$，则当前的$m=\sum_{i=1}^{\lfloor max/x \rfloor }b_{i\times x}(max$是$A$数组的最大数，原理是不存在大于$max$的数，所以更不存在大于$max$的$x$的倍数)

附代码：
```cpp
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn(2e5+5);
long long n,a[maxn],b[maxn*10],ans,now,maxx=0;
long long read(){
	char ch=getchar();
	long long x=0,f=1;
	while(ch<'0' || ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),b[a[i]]++,maxx=max(maxx,a[i]);
	for(int i=1;i<=maxx;i++){
		now=0;
		for(int j=i;j<=maxx;j+=i) now+=b[j];
		if(now>1) ans=max(now*i,ans);//这里的now就是分析中的m
	}
	printf("%lld\n",ans);
	return 0;
}
```

**贴士：** 此题爆$int$（最坏情况$ans=2\times 10^{5}\times 2\times 10^{6}=4\times 10^{11}$，结果需要开$long\ long$


---

## 作者：az__eg (赞：1)

**题意**：

对于一个序列 $a$ 求出一个数 $x$ 使 $a$ 中元素能被 $x$ 整除的数量乘 $x$ 的结果尽量大。

**解法**：

对于每个 $a_i$，我们可以用 $O(\sqrt{n})$ 的时间求出他的所有因数，求出所有数的因数复杂度为 $O(n \sqrt{n})$，我们可以考虑维护一个数组，数组的第 $j$ 位的值表示有几个数的因数中包含 $j$。由于 $1 \leq a_i \leq 2 \times 10^6$，显然这个数组最大只要开到 $2 \times 10^6$ 即可，再从 $1$ 到 $n$ 枚举一遍以 $i$ 作为因数的情况，找出最大的答案。综上所述，时间复杂度为 $O(n \sqrt{n}+\max{a_i})$

**代码**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int a[2000001];
int gs[2000001];
int mx;
signed main()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mx = max(a[i],mx);
		for(j=1;j*j<=a[i];j++)//求因数
		{
			if(a[i]%j==0)
			{
				if(j*j==a[i])
				{
					gs[j]+=1;
					continue;
				}
				gs[a[i]/j]+=1;
				gs[j]+=1;
			}
		}
	}
	long long ans = 0;//注意开longlong
	for(i=1;i<=mx;i++)
	{
		if(gs[i]>=2)
		ans = max(ans,(long long)gs[i]*(long long)i);//枚举答案
	}
	printf("%lld",ans);
}
```


---

## 作者：skyskyCCC (赞：1)

**前言。**

找倍数。

**分析。**

首先，我们可以运用桶排的思想。

我们将数输入，然后将他们放进相应数（该数的倍数）的桶里，统计个数，再找到所有数中的最大值。

我们统计最大值中的所有数，将计数器每次清零，再循环所有的 $i$ 的倍数，加起来，如果答案比一大，就判断是不是比 $ans$ 大，如果是， $ans$ 变成 $sum$ 输出。

为什么倍数就要加 $i$ 呢？

我们知道，一个数的倍数就是该数乘一个比 $0$ 大的数，也就是说，一个数的倍数永远是前一个数的两倍。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
using namespace std;
long long n,a[2000005],b[2000005],maxx,ans,sum;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        b[a[i]]++;
        maxx=max(a[i],maxx);
    }
    for (int i=1;i<=maxx;i++){
        sum=0;
        for (int j=i;j<=maxx;j+=i){
            sum+=b[j];
        }
        if(sum>1){
            ans=max(sum*i,ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

**后记。**

所有定义必须使用 ```long long``` 类型。

---

## 作者：SUPERRYX (赞：1)

# 解题思路：

用一个桶 b 来记录每个数出现次数 ，然后再枚举 x ，去找 a 数列中最大的数 ，之后就去找到 x 的倍数 ，打擂台比较  ，得出最大的答案 ，输出即可 ( 详细解释请看代码 ) 

不过要注意几点：
- 本题数据用 int 会爆 ,所以不开 long long 见祖宗
- 注意数组下标 ，开小了会越界
- 枚举x的循环里 ，每一轮的 m 必须清零


# AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,maxn=0,n,a[200001],t[2000001];//注意要long long 
//s为最终的答案， maxn为a数列里的最大值，n为a数列的个数
//a[i]为数列中的每个数，b[i]用来记录每个数出现次数
int main(){
	cin>>n;//输入 
	for(int i=1;i<=n;i++){
		cin>>a[i];//循环输出 
		t[a[i]]++;//用一个桶记录这个数出现次数 
		maxn=max(maxn,a[i]);//更新每一轮的最大值，为方便之后枚举x和找x的倍数 
	}
	for(int x=1;x<=maxn;x++){//暴力枚举x 
		long long m=0;//m为记录x的倍数个数，注意清零 
		for(int j=x;j<=maxn;j+=x)
			m+=t[j];//累加所有x的倍数的个数 
		if(m>1)//根据题目要求，m必须大于1，所以还要判断 
			s=max(s,m*x);//打擂台，求出s的最大值 
		 
	}
	cout<<s<<endl;//最后输出s 
	
	return 0;//结束qwq 
}

```

---

## 作者：Catcats (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6539)

### 题目解法

维护 $3$ 个变量（组）：$maxn,cnt,ans$，其中 $maxn$ 代表题目中 $A$ 中最大值，数组 $cnt$ 代表每个 $A_i$ 的出现次数，$ans$ 即为 $s$。

那么：先预处理  $maxn$ 和 $cnt$，然后循环模拟（$i$ 从 $0$ 到 $maxn$，数有几个 $A_i$ 满足 $i|A_i$，记为 $m$，然后用 $m$ 更新 $ans$。

**注意：$2\times10^5\times2\times10^6>2147483647$，所以要开 `long`。**

### AC 代码
```cpp 
#include<bits/stdc++.h>
using namespace std;
#define int long//个人习惯
int cnt[2174783];
signed main(){
	int n,maxn=-114514,ans=0;cin>>n;
	int a[n+1];
	for(int i=0;i<n;i++){
    	cin>>a[i+1];
    	cnt[a[i+1]]++;//统计a[i]次数，没有就是0
    	maxn=max(maxn,a[i+1]);
	}
	for(int i=1;i<=maxn;i++){
    	int m=0;
		for(int j=i;j<=maxn;j+=i)m+=cnt[j];//统计有几个 a[i] 满足 i|a[i]
    	if(m!=1&&m)ans=max(ans,m*i);//特判 m!=1
	}
	cout<<ans;
}
```

---

