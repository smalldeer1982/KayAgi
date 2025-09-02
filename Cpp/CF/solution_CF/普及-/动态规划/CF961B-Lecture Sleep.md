# Lecture Sleep

## 题目描述

Your friend Mishka and you attend a calculus lecture. Lecture lasts $ n $ minutes. Lecturer tells $ a_{i} $ theorems during the $ i $ -th minute.

Mishka is really interested in calculus, though it is so hard to stay awake for all the time of lecture. You are given an array $ t $ of Mishka's behavior. If Mishka is asleep during the $ i $ -th minute of the lecture then $ t_{i} $ will be equal to $ 0 $ , otherwise it will be equal to $ 1 $ . When Mishka is awake he writes down all the theorems he is being told — $ a_{i} $ during the $ i $ -th minute. Otherwise he writes nothing.

You know some secret technique to keep Mishka awake for $ k $ minutes straight. However you can use it only once. You can start using it at the beginning of any minute between $ 1 $ and $ n-k+1 $ . If you use it on some minute $ i $ then Mishka will be awake during minutes $ j $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961B/74a70105e36a7144196883409708a1b859a35796.png) and will write down all the theorems lecturer tells.

You task is to calculate the maximum number of theorems Mishka will be able to write down if you use your technique only once to wake him up.

## 说明/提示

In the sample case the better way is to use the secret technique at the beginning of the third minute. Then the number of theorems Mishka will be able to write down will be equal to $ 16 $ .

## 样例 #1

### 输入

```
6 3
1 3 5 2 5 4
1 1 0 1 0 0
```

### 输出

```
16
```

# 题解

## 作者：爬行者小郑 (赞：3)

## 这题可以考虑双指针来解决

双指针主要适合单调区间的求和等问题。

我们先来了解一下一个简化版双指针问题：

### 对于一个长度为n数列，输出所有长度为m的子序列，其中所有元素的和。

例如$5,9,1,4,2$这个序列，求出长度为m的子序列的元素的和。

就分别是

5+9+1=15,

9+1+4=14,

1+4+2=7;

如果是暴力求和，那么$O(n*m)$的效率，在大多数题里面是不会过的，那么怎么优化呢？

我们会发现，在起始点相邻的两个区间中，只有黄色的部分修改了，其余的部分没有变化。
![](https://cdn.luogu.com.cn/upload/image_hosting/r8yo7jc3.png)
那么我们就可以在$O(1)$的时间内求出下一个区间的和，第一个区间用$O(m)$的时间初始化即可。

### 回归正题

这道题有些地方的t值已经是1，那么先把没有使用变化的和先求出来，再用刚才的思想更新每次又多出来多少即可。

具体请看代码：
```cpp
#include <iostream>//基本输入输出流
using namespace std;
int n,k;//题目中的n,k
int sum;//每次的总和
int a[100005],t[100005];//题目中的两个数组
int ans;//答案的最大值
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>t[i];//输入
	int r=k;//第一个区间的右端点为k
	for(int i=1;i<=k;i++)
	{
		sum+=a[i];
	}//初始化第一个区间，将t[1]到t[k]变为1
	for(int i=k+1;i<=n;i++)sum+=a[i]*t[i];//后面的数没有变化，直接算
   	//到此初始化完成
	for(int l=1;l<=n-k+1;l++)//枚举左端点
	{
		ans=max(ans,sum);//更新最大值
		if(!t[l])sum-=a[l];//如果要删掉的左端点本来没有值，但是因为t[l]变成了1，有了值，所以要减回去
		if(!t[r+1])sum+=a[r+1];//新加入的右端点如果t为零，那么更新后就把数加上，否则无需变化
		r++;//更新右端点
	}
	cout<<ans<<endl;//输出最大值
	return 0;//养成好习惯
}
```
谢谢大家


---

## 作者：yuangq (赞：3)

# 法一

双重循环暴力累加

~~~
#include<bits/stdc++.h>
using namespace std;
long long n,k,maxs=-2147483647;
long long a[100005],t[100005];
int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
    	cin>>a[i];
    }
    for(int i=0;i<n;i++)
    {
    	cin>>t[i];
    }
    for(int i=0;i<n-k+1;i++)
    {
        long long s=0;
        for(int j=0;j<n;j++)
        {
            if(j>=i && j<i+k)
            {
                s=s+a[j];
            }
            else
            {
                s=s+a[j]*t[j];
            }
        }
        maxs=max(maxs,s);
    }
    cout<<maxs;
    return 0;
}

~~~


# 法二

先输入两个数组

用s存下从a0——ak-1改变的值

然后从i=1开始往后延直到i=n-k时停止，每次计算它的变化值

最后计算最大值即可

~~~
#include<bits/stdc++.h>
using namespace std;
long long n,k,maxs=-2147483647;
long long a[100005],t[100005];
int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
    	cin>>a[i];
	}
	for(int i=0;i<n;i++)
    {
    	cin>>t[i];
	}
	long long s=0;
	for(int i=0;i<n;i++)
	{
		if(i<k)
		{
			s=s+a[i];
		}
		else
		{
			s=s+a[i]*t[i]; 
		}
	}
	maxs=s;
	for(int i=1;i<n-k+1;i++)
	{
		s=s-a[i-1];
		s=s+a[i-1]*t[i-1];
		s=s-a[i+k-1]*t[i+k-1];
		s=s+a[i+k-1];
		maxs=max(maxs,s);
	}
	cout<<maxs;
	return 0;
}

~~~

---

## 作者：UperFicial (赞：2)

# 简单题

### 前言

这里讲一个楼下没有讲过的做法。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF961B)

$AC$ 记录：[$\text{Link}$](https://www.luogu.com.cn/record/42073460)

目前是最优解（不开 $O2$）

### 题目大意

给定长度为 $n$ 的数列 $a$ 和只含 $0,1$ 的数列 $t$。

你可以将 $[i,i+k-1]$ 这一区间的 $t_i$ 都变为 $1$。（只能用一次）

求 $\sum_{i=1}^na_it_i$ 的最大值。

$1\le n\le 10^5,1\le a_i\le 10^4$。

### 解题思路

不难想到，既然要求出 $\sum_{i=1}^na_it_i$ 这个柿子的最大值，那么我们肯定是要将上述操作放在有 $0$ 的区间里的，毕竟没有 $0$ 的话就跟啥都没干是一样的。

我们便可以对于每个 $t_i=0$ 的位置 $i$ 挨个进行操作，如果在 $[i,i+k-1]$ 这个区间进行操作后，它的贡献会是多少。

显然，对于每个 $t_i=1$ 的位置肯定是要算上这个位置的 $a_i$，而在这个区间的每个 $t_i=0$ 的位置上的 $a_i$ 也要算上。

但这样最坏情况下复杂度为 $O(n^2)$。

但这显然是个求和的问题，可以通过前缀和来做，$sum_i$ 为所有 $t_i=1$ 上的 $a_i$ 的和，$h_i$ 为所有 $t_i=0$ 上的 $a_i$ 的和，这样对于区间 $[i,i+k-1]$ 进行操作产生的贡献就是：

$$sum[n]+h[i+k-1]-h[i-1]$$

去个最大值即可，但有两个问题要注意：

- $i+k-1$ 可能 $>n$，所以需要特判。

- 如果所有 $t_i$ 都等于 $1$，那么根本不会进行取最大值的操作，于是可以将 $h[i+k-1]-h[i-1]$ 中取个最大值，最后输出时 $+sum[n]$。

但是还可以优化，比如 $n=1e5$ 而只有一个 $t_i=0$ 则在枚举的时候浪费了太多的时间，所以可以做一个类似单向链表的东西存所有 $t_i=0$ 的位置。

[$code$](https://paste.ubuntu.com/p/srNthPF9qQ/)

去掉读入的时间复杂度：$O(num_0)$（$num_0$ 为 $t_i=0$ 的个数）

空间复杂度：$O(n)$。

$$\texttt{The End.by UF}$$

---

## 作者：tribool4_in (赞：1)

首先可以暴力枚举每段区间修改后的结果，然而复杂度 $O(n^2)$，荣获 TLE；

那么考虑优化。只需枚举每段区间并通过上次的结果获取当前区间修改后的值即可，复杂度 $O(n)$。

程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long n, k, maxn = -2147483647;
long long a[N], t[N];
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    long long tmp = 0;
    for (int i = 0; i < n; i++) {
        if (i < k) {
            tmp = tmp + a[i];
        } else {
            tmp = tmp + a[i] * t[i];
        }
    }
    maxn = tmp;
    for (int i = 1; i < n - k + 1; i++) {
        tmp = tmp - a[i - 1];
        tmp = tmp + a[i - 1] * t[i - 1];
        tmp = tmp - a[i + k - 1] * t[i + k - 1];
        tmp = tmp + a[i + k - 1];
        maxn = max(maxn, tmp);
    }
    cout << maxn << endl;
    return 0;
}

```


---

## 作者：smallfang (赞：1)


# CF961B

我们先来分析思路(qwq).

## 暴力

先上图:

![image1](https://i.loli.net/2019/06/05/5cf7c456da48538137.png)

这张图表示了枚举的总过程.

然后我们可以~~轻松愉悦的~~敲出暴力代码,**然后成功的tle了**.


------------


**为啥T了呢?**

答:进行了**重复**的操作.

那怎么避免**重复**呢,我们可以把单独的2个区间提出来:

![image2](https://i.loli.net/2019/06/05/5cf7c595264aa38873.png)

我们可以发现两个方框只有收尾两个位置在变化.(如图)

![image3.png](https://i.loli.net/2019/06/05/5cf7c6a21409832606.png)

那么我们只用看头尾的两个数就行了(少头多尾)

所以只用开头预处理一遍,然后每次修改就行了

------------

## 关于一些奇奇怪怪的问题

### 1 关于t数组和头尾

如果t头是0的话,说明我们在上一次加上了他,就应该减去.

如果t头是1的话,说明他本来就有,不用动

如果t尾是0的话,说明他没有被算上,就应该加上

如果t尾是1的话,说明已经早被算上,就用管了.

后面有代码,可能可以理解的更深一些qwq.

## 关于代码

可能码风清奇,但是能凑活着看.qwq.

如果有啥疑问,欢迎在评论区提出.qwq.

~~(当时做题的时候,还以为关前缀和的事,所以写了一个q数组,但是没用为了防作弊就不删了吧qwq)~~

```cpp

#include <iostream>
#include <cstdio>

using namespace std;

int a[100001],t[100001],q[100001];

int n,k;

int check(int start)
{
    int end,cans=0;
    end=start+k-1;
    for(int i=1;i<=n;i++)
    {
        if(i>=start && i<=end)
        {
            cans=cans+a[i]*1;
        }
        else
        {
            cans=cans+a[i]*t[i];
        }
    }
    return cans;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i]);
        q[i]=q[i]+q[i-1]+(!t[i])*a[i];
    }
    int ans=0;
    ans=check(1);
    int sum=ans;
    for(int end=k+1;end<=n;end++)
    {
        int start=end-k+1;
        if(t[start-1]==0)
        {
            sum=sum-a[start-1];
        }
        if(t[end]==0)
        {
            sum=sum+a[end];
        }
        ans=max(ans,sum);
    }
    cout<<ans;
    return 0;
}


```



---

## 作者：liukangyi (赞：0)

# 题目大意
给你一个数字 $n$ 与 $k$ 与两个长度为 $n$ 的 $a$ 数组以及 $t$ 数组，现在你可以选择 $t$ 数组中长度为 $k$ 的**连续一段**数据变为 $1$，然后要你输出进行上述操作后 $\sum_{i=1}^na_it_i$ 的最大值。


------------

# 分析
这道题我们用 $pre1_i$ 来表示 $t$ 数组前 $i$ 个数据为 $1$ 的地方在 $a$ 数组对应位置的和，用 $pre01_i$ 来表示 $a$ 数组前 $i$ 个数据的总和。并枚举变为 $1$ 的那一段，且通过两个前缀和数组求出将 $t$ 数组的某一段全变为 $1$ 后 $\sum_{i=1}^na_it_i$ 的值然后刷新最大值，最后输出最大值即可。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
int a[100010],t[100010],pre01[100010],pre1[100010]; //定义数组，pre01与pre1数组为前缀和数组 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pre01[i]=pre01[i-1]+a[i]; //累加a数组的值到pre01数组里 
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&t[i]);
		pre1[i]=pre1[i-1];
		//如果t数组当前位置的值为1的话，那么a数组对应位置的值加入pre1数组中 
		if(t[i]==1)
			pre1[i]+=a[i];
	}
	for(int i=1;i<=n-k+1;i++)
		ans=max(ans,pre1[i-1]+pre1[n]-pre1[i+k-1]+pre01[i+k-1]-pre01[i-1]); //求出将某一段变为1后的值并刷新最大值 
	cout<<ans;
	return 0;
} 
```


---

## 作者：wangyinghao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF961B)

考虑到如果用本题的题目翻译解释此题会比较难理解，因此提供一下自己的翻译。

### 题意

你的朋友 Mishka 和你一起参加了一个微积分课程，这个课程总共 $n$ 分钟，第 $i$ 分钟会讲授 $a_i$ 条定理。 


Mishka 对这个课程非常有兴趣，但他无法保证在课上的每分钟都保持清醒状态。现在给定你一个序列 $t$，用来描述 Mishka 每分钟的状态。如果 Mishka 在第 $i$ 分钟处于昏睡状态，$t_i$ 等于 $0$，处于清醒状态 $t_i$ 等于 $1$。如果 Mishka 第 $i$ 分钟处于清醒状态，他会记下第 $i$ 分钟讲授的 $a_i$ 条定理，否则他什么都不会记下。

你知道一条秘籍可以使 Mishka 保持清醒 $k$ 分钟，但你只能使用 $1$ 次，在 $1$ 至 $n-k+1$ 区间内的每分钟开始时都可以使用。

你的任务是使用秘籍使 Mishka 记下最多的定理。

### 思路

最笨的方法就是对于 $1$ 至 $n-k+1$，每一分钟试一下去使用秘籍，最后找出最优方案，复杂度 $O(nk)$，很显然不能过，因此这道题目可以考虑用**双指针法**来解决。

我们定义两个指针 $x$ 和 $y$，代表左指针和右指针，而这两个指针中间的区域就是我们使用秘籍的地方。

使用秘籍的最优方案应该是在 Mishka **错过**最多定理的 $k$ 分钟内使用秘籍，这样就能使 Mishka 听到尽可能多的定理。

### AC Code

```cpp
#include<iostream>
using namespace std;
int a[100005];
int t[100005];

int main(){
	int n,k,x,y,cnt=0,maxx=0,maxt,maxw;//cnt是使用秘籍的区间ti=0时ai的和
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=k;i++){
		if(t[i]==0) cnt+=a[i];//预处理
	} 
	x=1;
	y=k;
	while(x<=n-k+1){
		if(cnt>maxx){//打擂台求最优方案
			maxx=cnt;
			maxt=x;//记录这个使用秘籍的区间
			maxw=y;
		}
		if(t[x]==0) cnt-=a[x];//删掉左端点 Mishka在睡觉 错过了这些定理
		x++;
		y++;
		if(t[y]==0) cnt+=a[y];//新加入右端点 Mishka不再睡觉 多记了一些定理
	}
	for(int i=1;i<=n;i++){
		if(i>=maxt && i<=maxw && t[i]==0) continue;//区间内ti=0的情况已经算过了
		maxx+=a[i]*t[i];//没算的再加
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：PeaceSunset (赞：0)

看到诸位大佬用着什么单调队列、双指针，身为蒟蒻的我只能默默用出了**前缀和**。

### 思路：

直接暴力，设 $ans1$ 为原总和，$ans2$ 为增加值的和。

- $ans1$ 的值大家都会求：在遍历数组时，如果 $t_i$ 为零就在 $ans1$ 中加上 $a_i$。

- $ans2$  的值也是通过遍历求得：从 $1$ 到 $(n-k+1)$，通过前缀和比较哪一段的 $\sum_{i}^{i+k-1}{a_i}$ 最大，而 $ans2$ 的值就是那一段的总和。

最后输出 $ans1+ans2$ 即可。

注：`cout` 要是会超时的话就用 `printf` 吧。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N],t[N],n,k,ans1,ans2;
signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
    for(int i=1;i<=n;i++){
        if(t[i]==0)a[i]+=a[i-1];
        else ans1+=a[i],a[i]=a[i-1];
    }
    for(int i=1;i<=n-k+1;i++)ans2=max(ans2,a[i+k-1]-a[i-1]);
    printf("%lld",ans1+ans2);
return 0;
}
```


---

## 作者：caohan (赞：0)

# 一 题意
其实就是  @huhao   _JULAO_   给我们翻译的。
# 二 思路
## 首先明确暴力思想
$O(n^2)$   暴力方法就是每次枚举点 $i$ 的值，在反复求全部的和，得出最大值。
核心代码如下：
```cpp
int ans=0;
for（int i=1;i<=n-k+1;i++)
{
  for(int j=1;j<=n;j++)
	{
		ans+=a[j]*t[j];
		if(t[j]==0&&j>i&&j-i<k)
     	ans+=a[j];
	}
}
```
## 其次明确正解
正解为尺取法：常见于频繁对定长部分求和，差，积等等

[尺取法详细讲解](https://blog.csdn.net/lxt_Lucia/article/details/81091597)
引用[这位JULAO的文章](https://blog.csdn.net/lxt_Lucia?type=blog)
就此，发现本体应用尺取法来解决，先算恒定能取到的（ $t_i$ 为一 ），再用尺取法计算在 $i$ 点使用秘籍能获取到的最大值，加起来可得答案。
# 三 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int vis[100005];
int a[100005];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>vis[i];
	}//读入，vis[i]是他清醒的状况 
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=vis[i]*a[i];
		vis[i]=!vis[i];
	}//不论用不用秘籍，总是能听见的
	long long miji=0;
	long long maxmiji=-21000000000;
	for(int j=1;j<=k;j++)
	{
		miji+=vis[j]*a[j];
	}//1分钟时，用秘籍能多听见的
	int p1=1;int p2=k;
	maxmiji=miji;
	while(p2<=n)
	{    
		int tmp=0;
		p1++;
		p2++;
		tmp+=vis[p2]*a[p2];
		tmp-=vis[p1-1]*a[p1-1];
		maxmiji=max(maxmiji,miji+tmp);
		miji+=tmp;
	}//尺取法判断增加最大值 
	cout<<ans+maxmiji;
	cout<<"For A Peace LUOGU FZTNR";
    return 0;
}
```
[正解记录]( https://www.luogu.com.cn/record/92987039)

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $ n,a_{1\dots n},t_{1\dots n} $。
 
你可以把一个区间 $ [i,i+k-1] $ 中的 $ t $ 的值都变为 1。

求最大的 $ \sum_{i=1}^n a_it_i $。

## 思路

由于 $ n \leq 10^5 $，所以我们可以把所有的情况进行枚举，然后打擂台。由于所有的数都是正的，所以我们每次枚举起点，然后找到最远的终点，算出它的结果，打擂台即可，~~没有难度~~。只需要注意出去的和进来的。

## 挑战创新

大家可以思考一下如果你有两次机会把一个区间 $ [i,i+k-1] $ 中的 $ t $ 的值都变为 1。仍然求最大的 $ \sum_{i=1}^n a_it_i $。各位有什么思路？提示：枚举分界点，两边分别用一次机会。

## 代码

~~此处就不放代码了！！~~

---

## 作者：hgoicjl (赞：0)

### 翻译：
你的朋友米什卡和你参加微积分讲座。讲座持续n分钟。

讲师在第i分钟告诉ai个定理。

米什卡真的对微积分很感兴趣，尽管在讲课的所有时间都很难保持清醒。你得到了一个表示Mishka是否清醒的数组。**如果Mishka在讲座的第i分钟睡着了，那么ti将等于0，否则它将等于1.**

**当Mishka醒来时，他写下他所知道的所有定理。否则他什么也不会写。**

你知道一些技巧让Mishka保持清醒k分钟。但是，您只能使用一次。你可以在1到n-k + 1之间的任何一分钟的开始使用它。如果你在某一分钟使用它，**那么Mishka将接下来在分钟j中保持清醒，并且将记下讲师告诉的所有定理。**

你的任务是计算Mishka能够记下的**最大定理数**，如果你只使用你的技巧一次来叫醒他。

（google翻译+略微修改）

## 题意：
给定n,a_{1...n},t_{1...n} 

你可以把一个区间[i,i+k-1]中的t的值都变为1

计算最大的∑a[i]t[i]

感谢@huhao 提供的翻译

### 思路：
我们将所讲的定理分为两类 

①一定能够听到的 ②只有使用技巧保持清醒才能听到的

显然①类t[i]=1,②类t[i]=0

我们先读入所有的数据,并用一个max1存储①类定理的数量

然后再从头到尾计算最大的②类定理（从i分钟开始，i+k-1结束）的数量，记为max2

输出max1+max2

**然后就TLE了**

怎么办想着优化下

发现
```
for(int i=1;i<=n-k+1;i++)
		max2=max(max2,su(i,i+k-1));
```
的时间复杂度是O(N2)

于是考虑在读入的时候直接处理②类，用变量max2记录从i-k+1到i分钟②类的数量

如果i分钟是睡着的那么在i-k+1使用技巧会多听的a[i]个定理，**记得处理完之后从
（i+1）-k+1分钟施展时减去i-k+1分钟使用技巧会多听的定理**

然后就有了代码2，成功AC
### 代码1(TLE)：

```cpp
#include<bits/stdc++.h>
using namespace std;
//作者@hgoicjl
int a[100005],d[100005],n,k,max1=0,max2=0;
int su(int a,int b)
{
	int sum=0;
	for(int i=a;i<=b;i++)
		sum+=d[i];
	return sum;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>d[i];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1)
		{
			max1+=d[i];
			d[i]=0; 
		} 
	}
	for(int i=1;i<=n-k+1;i++)
		max2=max(max2,su(i,i+k-1));
	cout<<max2+max1;
	return 0;
} 
```
### 代码2（AC）：
```cpp
#include<bits/stdc++.h>
using namespace std;
//作者@hgoicjl
int a[1000005],d[1000005],n,k,max1=0,max2=0,sum=0;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>d[i];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1)
			max1+=d[i];
		else
			sum+=d[i];
		max2=max(max2,sum);
		if(i>=k)
			sum-=d[i-k+1]*(1-a[i-k+1]);
	}
	cout<<max2+max1;
	return 0;
} 
```


---

