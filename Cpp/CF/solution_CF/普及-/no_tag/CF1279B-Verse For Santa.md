# Verse For Santa

## 题目描述

### 题意简述

给定正整数 $n$，$s$ 和长为 $n$ 的整数数列 $a_1,a_2,...,a_n$。

求一个最大的 $i$，使得存在一个 $j$ 满足 $1\leq j\leq i$，让 $(\sum_{k=1}^{i} a_k) -a_j \leq s$ 。

## 样例 #1

### 输入

```
3
7 11
2 9 1 3 18 1 4
4 35
11 9 10 7
1 8
5
```

### 输出

```
2
1
0
```

# 题解

## 作者：幻想繁星 (赞：3)

这道题我第一眼自然是想到了枚举，我们可以枚举 $i$ 和 $j$，用时间复杂度为 $O(n ^ 2)$ 的暴力算法求解。然而看了看数据范围 $1≤n≤10^5$，TLE是肯定的啦

------------

所以我们要想其他的算法来枚举，经过一番思考，我想到了：  
可以用前缀和来优化 $\sum \limits _ {k = 1} ^ i a _ k $，就只用枚举 $i$，此时的时间复杂度就达到了 $O(n)$ 级别，再根据题面：“如果 $\sum_{i=1}^{n} a_i \leq s$，输出 $0$”，进行特判，最后打打代码就可以AC了。

------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long t,n,s,maxn,ans,count,sum,a[100001];
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>s;
		maxn=ans=count=sum=0;//初始化
		for(int j=1;j<=n;j++) cin>>a[j];
		for(int j=1;j<=n;j++)
		{
			sum+=a[j];//计和 
			if(maxn<a[j])//统计最大值 
			{
				maxn=a[j];
				count=j;
			}
			if(s+maxn>=sum) ans=count;//替换答案 
		}
		if(sum<=s) ans=0;//特判 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：卷王 (赞：3)

我的第一篇题解，希望能给大家帮助。

这一题最多评橙，其实很简单。

[传送门](https://www.luogu.com.cn/problem/CF1279B)

对于一些人来说，题目可能有点绕人（比如说我）。

------------

下面进入正题：

观察数据范围，发现 $n$ 的数据范围是 $10^5$ ，用 $O(n^2)$ 的时间复杂度直接暴力肯定不行，那么有没有其他的办法呢？


------------

思路：

暴力是不行的，那么我们就必须用到前缀和！

前缀和是指某序列的前 $n$ 项和，可以把它理解为数学上的数列的前 $n$ 项和。

如果在看的各位还不了解前缀和，建议可以看看  P1115 了。

相信很多人都了解了前缀和，现在我们来分析题目。

我们用前缀和思想，可以将时间复杂度优化到 $O(n)$ ，我们用一个变量 $k$ 表示当前循坏到的得房，再用一个变量 $sum$ 表示$\sum\limits_{i=1}^ka[i]$，如果发现和在加上当前的这个数之前并没有大于 $s$，而现在满足要求，那么就加上这个数。

其余的细节请看代码。



------------

AC代码：

```cpp
//请勿抄袭，共建美好洛谷！
//made in china 

#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

typedef long long ll;

ll t,n,s,maxx=0,ans=0,count=0,sum=0;

ll a[1000001];

inline void ready()
{
	sum=0;
	maxx=0;
	ans=0;
	count=0;
}

inline int read();

int main()
{
	t=read();
	
	for(int i=1;i<=t;i++)
	{
		n=read();
		
		scanf("%ld",&s); //码风丑勿喷~~ 
		
		ready();
		
		for(int j=1;j<=n;j++) a[j]=read();
		
		for(int j=1;j<=n;j++)
		{
			sum+=a[j]; //前缀和优化 
			
			if(maxx<a[j])
			{
				
				maxx=a[j];
				
				count=j;
				
			}
			
			if(s+maxx>=sum)
			{
				ans=count;
			}
		}
		
		if(sum<=s)
		{
			ans=0;
		}
		
		printf("%ld\n",ans);
	}
	return 0;
}

inline int read()
{
	int x=0,f=1;
	
	char ch=getchar();
	
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		
		ch=getchar();
	}
	
	while(ch>='0' && ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		
		ch=getchar();
	}
	
	return x*f;
}
```

---

## 作者：櫻尘ིོི༹ (赞：2)

~~最近十分喜爱 CF 的题，再来一发题解。~~

**Part 1 方法**

数据范围为   $n \leq 10^5$，自然不可能  $ O (n^2) $  暴力，想一个前缀和思想，直接  $O(n)$  解决！

**Part 2 具体思路**

由题意，可以知道，在最大的  $ i $  的情况下，如果只有一个   $ j $，那一定是前面最大的那一个   $a[k](k\in \{ 1,2,3 \cdots  i-1, i \})$。 

所以，只需要在从开头到结尾的枚举中，将每一个权值加在一起，同时计算最大的一个数，并记录位置，最后输出最后一次记录的位置。特别的，在     $\sum\limits_{i=1}^na_i \ge s$ 时，直接输出   $ 0 $。

**Part 3 Code**

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN (int)1e5+5 
using namespace std;
int t;
int n,s;
int a[MAXN];
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>s;
		for(int i=1;i<=n;++i)cin>>a[i];
		int sum=0,smax=0,ans=0,num=0;
		for(int i=1;i<=n;++i){
			if(smax<a[i]){
				smax=a[i];
				num=i;
			}
			sum+=a[i];
			if(sum-smax<=s)ans=num;
		}
		if(sum<=s)ans=0;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：2)

## 题意
给你一个字符串，问你前若干个数字之和可以大于 $s$ 的小数组中，最大的数是哪个。
## 思路
没有错又是最优解。     
用一个变量 $sum$ 保存从开始到当前的的总和，如果发现和在加上当前的这个数之前并没有大于 $s$,那么就对当前的数字取最大，并把 $sum$ 加上当前的数。    
之所以是最优解，是应为我没用数组。    

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,sum,ma,h,x,i;
int main(){
	scanf("%d",&T);//T组数据
	while (T--){
		scanf("%d%d",&n,&m);
		sum=0;ma=0;h=0;//清空
		for (i=1;i<=n;i++){//n个数字
			scanf("%d",&x);//读入
			if (sum<=m){
				sum+=x;if (x>=ma) ma=x,h=i;//累加+保存最大值
			}
		}
		printf("%d\n",(sum>m?h:0));//输出，如果总和没超过,那么输出0，不然就输出最大的数的位置
	}	
	return 0;
}

```


---

## 作者：codemap (赞：1)

第一次参加$Codeforces$比赛,来写一篇题解(~~比赛时间也太晚了吧~~)

做法:

枚举一遍,用一个计数器$k$枚举当前的前缀和

再记录一下目前为止的最大值和最大值的位置

如果$k>s$,将$flag$记为$1$,并跳出循环

若$flag==0$ 输出$0$

否则,输出最大值的位置

最后注意要在枚举前初始化

上代码
```cpp
#include<iostream>
using namespace std;
int a[100001];
int main()
{
	int t,n,s,i,k,mmax,p;//mmax为最大值,p为位置
	bool f;//flag
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		for(i=1;i<=n;i++)
			cin>>a[i];
		k=0;//初始化
		mmax=0;
		f=0;
		for(i=1;i<=n;i++)
		{
			k+=a[i];//计数器累加
			if(a[i]>=mmax)//如果比最大值还大
			{
				mmax=a[i];//更新最大值
				p=i;//更新最大值位置
			}
			if(k>s)//如果已经超过s
			{
				f=1;//flag记为1
				break;//跳出循环
			}
		}
		if(!f)//如果flag还是0
			cout<<0<<endl;//输出0
		else//否则
			cout<<p<<endl;//输出最大值位置
	}
	return 0;
}
```
# 请勿抄袭

---

## 作者：LiaoYF (赞：0)

这题其实比较简单。


首先，暴力解，可以枚举每一个 $i$ 和 $j$，求和，时间复杂度 $O(n^3)$。看数据范围，肯定会[TLE](https://codeforc.es/contest/1279/submission/171580334)。

所以，**需要优化**。

这题中多次对数组中的一段求和，考虑使用[**前缀和**](https://oiwiki.org/basic/prefix-sum/)优化。使用一个数组储存前缀和，查询 $\sum_{i=1}^{n} a_i $ 的复杂度就降低到了 $O(1)$，这样时间复杂度 $O(n)$，就不会TLE了。

## Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
ll t,n,s,a[100005],sum[100005];//sum:前缀和数组
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>s;
        int maxn=-1,maxi=0,ans=0;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum[i]=sum[i-1]+a[i];//计算前缀和
        }
        if(sum[n]<=s){//特判直接输出0的情况
            cout<<0<<"\n";
            continue;
        }
        for(int i=1;i<=n;i++){//枚举i
            if(maxn<a[i]){//计算最大的数
				maxn=a[i];
				maxi=i;
			}
            if(sum[i]-maxn<=s){//找到一组解
                ans=maxi;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
[record](https://codeforc.es/contest/1279/submission/171582755)

---

## 作者：YuanZihan1225 (赞：0)

最近经常做CF的暂无评定，正好也来水一篇题解（又是一个最优解）。

[题目传送门](https://www.luogu.com.cn/problem/CF1279B)

[可能更好的阅读体验](https://yzhnb.blog.luogu.org/solution-cf1279b)

# 进入正题

## solution 1:

我们可以枚举 $i$  和 $j$，用时间复杂度为 $O(tn ^ 2)$ 的暴力算法求解。但由于 $1 \leq t \leq 100, \sum n \leq 10 ^ 5$，所以显然，我们可以优化。

## solution 2:

于是我们能够发现：可以用前缀和来优化 $\sum \limits _ {k = 1} ^ i a _ k$，就只用枚举 $i$，时间复杂度就被优化为了 $O(tn)$，然后我们就找出了正解！代码见下：

## AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//用来解决卡常的问题，顺便拿了个最优解
{
	int x = 0, f = 1;
    char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	return x * f;
}
void write(int x)
{
	if(x < 0)
		putchar('-'), x = -x;
	if(x >= 10)
		write(x / 10);
	putchar(x % 10 + '0'); 
}
int t, n, s, sum, maxn, maxi;//定义变量，因为前缀和只用i - 1上的，所以就滚动掉了
signed main()
{
	t = read();
	while(t--)
	{
		n = read(), s = read();
		sum = 0, maxn = -1, maxi = 0;//初始化变量
		for(int i = 1; i <= n; i++)
		{
			int x = read();
			if(sum <= s)//更新的前提是sum比s小
			{
				sum += x;
				if(x >= maxn)//要求最大的i，就更新max
					maxn = x, maxi = i;//maxi记录下标
			}
		}
		write(sum > s ? maxi : 0), putchar('\n');//如果sum大于s，说明更新过了，输出maxi，否则输出0。
	}
	return 0;
}
```

### 完美地结束

所以，~~A了这道题，祝你们成功！~~





---

