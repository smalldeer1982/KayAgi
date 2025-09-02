# Suffix Operations

## 题目描述

给你一个整数序列，其中有$n$个元素。你需要对这个序列进行操作。

1 在所有操作开始前，你可以选择一个数，并修改他的值，这个值你可以自己定。本操作无花费。

2 选择一个下表$i$，将所有下表不大于$i$的元素加上一个整数$x$,$x$可以你自己定。这次操作花费为$x$的绝对值。

本题给你一个序列，要你求要将这个序列中的元素统一，至少花费多少。

## 样例 #1

### 输入

```
7
2
1 1
3
-1 0 2
4
99 96 97 95
4
-3 -5 -2 1
6
1 4 3 2 4 1
5
5 0 0 0 5
9
-367741579 319422997 -415264583 -125558838 -300860379 420848004 294512916 -383235489 425814447```

### 输出

```
0
1
3
4
6
5
2847372102```

# 题解

## 作者：Little09 (赞：3)

update 原先的代码在复制的时候**少了两行**，我也不知道咋回事。（否则样例都过不了）感谢评论区指出。

------------


这题花了我 16 min 才搞定，还是太菜了。

题目是说给你一个数列，每次可以选择一个位置，此位置及其后面的所有数可以加上 $x$，请问使数列所有数相同，所有 $|x|$ 的和最小值的多少。开始之前还可以修改一个数的值。

先不考虑修改，答案显然为所有相邻两数差的绝对值的和。可以手推一下，很好证明。

然后枚举一下修改哪个数算一下贡献。例如修改第 $x$ 个数，就会由原来的 $|a_{x-1}-a_x|+|a_x-a_{x+1}|$ 变为 $|a_{x-1}-a_{x+1}|$。边界特判一下就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],b[200005],ans,c[200005]; 
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	int T=read();
	while (T--)
	{
		int n=read();
		for (int i=1;i<=n;i++) a[i]=read();
		for (int i=2;i<=n;i++) b[i]=a[i]-a[i-1];
		for (int i=2;i<=n;i++) b[i]=abs(b[i]);
		ans=0;
		for (int i=2;i<=n;i++) ans+=b[i];
		long long tot=ans;
		for (int i=2;i<n;i++)
		{
			ans=min(ans,tot-b[i]-b[i+1]+abs(a[i+1]-a[i-1]));
		}
		ans=min(ans,tot-b[2]);
		ans=min(ans,tot-b[n]);
		cout << ans << endl;
	}
 	return 0;
}
```


---

## 作者：shenmadongdong (赞：3)

说句闲话，好久没有看到过这么难的div2B题了(个人感觉这题比D难)

首先，有个~~显而易见~~的结论：所需要的操作次数为最终序列中两个相邻的数的差的绝对值之和

证(shuo)明(li)：  
  - 首先操作必须从左向右进行  
  - 考虑对于 $a_i$，必须使它与 $a_{i-1}$ 相等，这必须要花费 $|a_i- a_{i-1} |$ 步  
  - 而这步操作之后，$a_{i+1}-a_i$ 的值不变  
  - 由此类推可得出结论

因此，我们只需改变一个数的值，使结果最小即可

对于$\forall i \in [2,i-1]$，$a_i$ 对结果的贡献是 $|a_i-a_{i-1}|+|a_i-a_{i+1}|$，而如果我们改变 $a_i$，可以将贡献额减小到 $|a_{i+1}-a_{i-1}|$

而对于 $i=1\ or\ n$，$a_i$ 的贡献值就是与旁边相邻的数的差的绝对值，而我们只要使它和旁边的数相等就可以把贡献值减到 $0$

因为我们要求结果最小，所以只要让贡献减小额最大化即可，具体实现可以看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200010],ans,mx,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		ans=mx=0;//多测别忘清零
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=2;i<=n;i++) ans+=abs(a[i]-a[i-1]);//统计原来答案
		for(int i=2;i<n;i++) mx=max(mx,abs(a[i]-a[i-1])+abs(a[i+1]-a[i])-abs(a[i+1]-a[i-1]));//统计2~n-1中的最大贡献减小额
		mx=max(mx,max(abs(a[n]-a[n-1]),abs(a[2]-a[1])));//统计1和n的贡献减小额
		ans-=mx;//将原答案减去最大的贡献减小额
		cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：young1199 (赞：1)

这道题没有太大的代码难度，主要是分析一下怎样处理第一次操作才能最佳。

分析题意：首先假设没有第一次无代价操作，那么最小的代价就应该为每相邻两元素的差值之和。而我们要做的就是充分利用第一次无代价操作，让第一次省去的代价最大。

分析数据：
就拿题中样例的一组数据举例。

${1 , 4 , 3 , 2 , 4 , 1}$

不难发现原最小代价（无第一次无代价操作时）为 $10$，而我们第一次将第 $5$ 个元素改为 $1$，此时它与左边数字差值少了 $1$ ，与右边数字差值少了 $3$，总差值少了 $4$，因此最小代价为 $10 - 4=6$。

对于每个元素求出将他修改之后能省去的最大代价，然后再在其中取最大值减去，就可以得到正确答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long  
const int N=2e5+10;
ll a[N];
ll cf[N];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;ll sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(i!=1){
				sum+=abs(a[i]-a[i-1]);//累加不算第一次操作的最小答案
			}
		}
		ll maxn=0;
		
		cf[1]=abs(a[1]-a[2]);
		cf[n]=abs(a[n]-a[n-1]);
		//第1和n个元素分别只能变成第2和n-1个元素
		maxn=max(cf[1],cf[n]);
		for(int i=2;i<n;i++){
			cf[i]=max(abs(a[i]-a[i-1])+abs(a[i]-a[i+1])-abs(a[i-1]-a[i+1]),abs(a[i]-a[i+1])+abs(a[i]-a[i-1])-abs(a[i-1]-a[i+1]));
			//对于每个元素，它可以选择变为他的左右两个元素之一，用max()函数取最大值
			maxn=max(cf[i],maxn);
		}
		cout<<sum-maxn<<'\n';
		
	}
} 


```

---

## 作者：Lynkcat (赞：1)

考虑建立差分数组 $b_i=a_i-a_{i+1}$ 。

然后考虑每个数与左边相同或与右边相同对 $\sum b_i$ 的影响，若与左边相同对答案的影响为 $|b_{i-1}|+|b_i]|-|a_{i-1}-a_{i+1}|$ ，同理与右边相同时对答案的影响为 $|b_{i-1}|+|b_i]|-|a_{i+1}-a_{i-1}|$ 。

每个 $i$ 扫过去找一个最大的影响减掉就好了。

```c++
int T,n,a[200005],b[200005],sum,mx;
signed main()
{
	T=read();
	while (T--)
	{
		n=read();mx=0;sum=0;
		for (int i=1;i<=n;i++) a[i]=read();
		b[n]=0;b[0]=0;
		for (int i=n-1;i>=1;i--) b[i]=a[i]-a[i+1];
		mx=max(mx,abs(b[1]));
		mx=max(mx,abs(b[n-1]));
		for (int i=2;i<n;i++)
		{
			sum+=abs(b[i-1]);
			mx=max(mx,abs(b[i-1])+abs(b[i])-abs(a[i-1]-a[i+1]));
			mx=max(mx,abs(b[i])+abs(b[i-1])-abs(a[i+1]-a[i-1]));
		}
		sum+=abs(b[n-1]);
		writeln(sum-mx);
	}
}
```

---

## 作者：血色黄昏 (赞：0)

当时的毒瘤 B ，写了三十分钟！~~要不是我不怎么会期望早就先去写后面的题了~~

这题是道思维题，代还码是非常好写的。

首先我们可以发现由于每次改小于 x 的，那么我们想让两个数变为相同的数就要花费两个数绝对值差的次数，这可以从样例中很显然的猜出，然后手玩一下就会发现是正确的，很好证，~~但我当时就是搞了十五分钟~~。实在不会的可以去看 LYC 神仙的题解 qwq

最后还要注意一点，因为题目允许我们改一个节点的值，那么我们就要改掉对结果贡献最大的点了，也就是和两边相差大的点，具体可以看代码。解释得很详细。

注意边界条件。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n, m, a[1000010], maxn = -0x7f7f7f7f;//如题意
long long sum = 0;
int main()
{
    cin>>T;
    while(T--)//多测记得清空
    {
    	sum = 0;//重置
    	maxn = -0x7f7f7f7f;//置为最小值
    	cin>>n;
    	for(int i = 0;i < n;i ++)cin>>a[i];//读入
    	for(int i = 1;i < n;i ++)sum += abs(a[i] - a[i - 1]);//先将全部和加起来
    	maxn = abs(a[1] - a[0]);//初始化
    	maxn = max(maxn, abs(a[n - 1] - a[n - 2]));//提前更新答案，避免边界问题
    	for(int i = 1;i < n - 1;i ++)//从1到n-2
		{
			maxn = max(maxn, abs(a[i] - a[i - 1]) + abs(a[i] - a[i + 1]) - abs(a[i - 1] - a[i + 1]));//判断改哪一个最优
		}
		cout<<abs(sum - maxn)<<endl;//取绝对值
	}
	return 0;
}
```

祝大家 CF 天天上分 awa


---

