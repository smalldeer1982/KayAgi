# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2
9 3
100 200 300 400 500 600 700 800 900
5 4
100 100 100 100 100```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900
100 / 100 / 100 / 100 100```

# 题解

## 作者：dqa2022 (赞：4)

本人对此题目的翻译：
**【题目描述（大意）】** 有m本书（每一本书都有一定的页数）和k台誊抄机器。一台机器只能够誊抄连续的若干本书，每本书只能由一台机器誊抄，每一台机器都必须有誊抄任务，誊抄机器可以同时工作。要求给出满足上述条件的工作分配方式，使得誊抄工作最早完成（即誊抄页数最多的机器誊抄页数最少）。 
**【输入格式】 **第一行有一个正整数N，表示数据组数。 接下来有N组数据，第一行为两个整数m和k，接下来一行有m个整数p1~pm，第i个表示第i本书的页数。 
**【输出格式】** 对于每组数据，输出工作分配方式，如果有多种工作分配方式，则输出机器誊抄页数字典序最靠前的那一种（这种分配方式要让誊抄靠前书本的机器分配到的页数尽量少）。
**【数据范围】** N大约为200；1<=k<=m<=500；pi<=10,000,000。

这一道题最初想到了DP，设dp[i][j]表示第i本书被第(j+1)台机器誊抄的答案，sum[i]=p[1]+p[2]+...+p[i]，那么就有状态转移方程：dp[i][j]=min{dp[i'][j-1]+sum[i]-sum[i']|j-1<=i'<i}。
写出来测了一下，过了样例。然后就去写了一个暴力来对拍。
然而暴力写错了，于是就直接交了上去，得到了一个WA的结果。
后来把暴力调出来了。对拍时发现对于这种记录方案的题目，DP是不可行的。
然后就去吃饭了。吃饭的时候想到二分答案+贪心验证是可行的（而且效率还更高）。
饭后就把代码写了出来。对拍了一下，没有发现问题。
交了上去，得到了AC的结果。
想了想，如果只要输出最短时间或者删去“如果有多种工作分配方式，则输出机器誊抄页数字典序最靠前的那一种（这种分配方式要让誊抄靠前书本的机器分配到的页数尽量少）”并开spj，DP是可行的（DP只能够找到正确答案和一种解法，给出的那种解法一定程度上可以人为控制，但是我们无法做到保证它能够满足应输出解的要求）。
由对拍结果可知，该结论应该没有问题。

**附件一：AC代码**
```cpp
#include<cstdio>
#include<cstring>
int T,n,m,p[510],l,r,mid,tot;
bool mark[510]; //记录该书是否为誊抄它的机器誊抄的最右边那本书
bool check(int x) //贪心验证
{
	int used=0,sum=x;
	for (int i=1;i<=n;i++)
	{
		if (p[i]>x) //如果有书的页数大于x就一定不行
			return false;
		if (sum+p[i]<=x) //如果这台机器能够在不大于x的时间内誊抄完这本书就贪心地让它来誊抄
			sum+=p[i];
		else //否则就要让下一台机器来誊抄
		{
			sum=p[i];
			used++;
			if (used>m) //如果当前所需机器数量最小值都大于机器总数也一定不行
				return false;
		}
	}
	return true; //通过了层层检查，可行
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		tot=0; //多组数据时初始化不能忘记；tot表示所有书的总页数
		memset(mark,false,sizeof mark);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			scanf("%d",p+i),tot+=p[i]; //p+i相当于&p[i]
		l=1,r=tot; //因为所有书本页数都为正数，所以下界为1；因为所有书本总页数为tot，所以上界为tot
		while (l<r)
		{
			mid=l+r>>1;
			if (check(mid)) //如果可行，范围缩小到[l,mid]
				r=mid;
			else //否则范围缩小到[mid+1,r]
				l=mid+1;
		}
		printf("%d\n",l); //此时l=r，为可行的最短时间
		int used=0,sum=l; //这里与check函数有类似之处
		for (int i=n;i;i--) //“如果有多种工作分配方式，则输出机器誊抄页数字典序最靠前的那一种（这种分配方式要让誊抄靠前书本的机器分配到的页数尽量少）”，因此应该在可行范围内让靠后的机器誊抄尽量多的书本
			if (sum+p[i]>l||m-used==i) //有可能不需要m台机器就可行，但是题目要求全部都要用上，因此把所有剩下的机器安排在前面
			{
				used++;
				sum=p[i];
				mark[i]=true; //记录为誊抄它的机器誊抄的最右边那本书
			}
			else
				sum+=p[i];
		for (int i=1;i<n;i++)
		{
			printf("%d ",p[i]);
			if (mark[i]) //如果是誊抄它的机器誊抄的最右边那本书，则在后面输出分隔
				printf("/ ");
		}
		printf("%d\n",p[n]); //最后一本后面不需要分隔；另外不知道SPOJ行末是否允许有空格
	}
	return 0;
}
```
**附件二：WA代码（这一份代码能够得出最短时间以及不一定符合输出要求的一种方案，有想知道DP方法怎么写的看这里）**
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m,dp[510][510],sum[510],pre[510][510]; //pre[i][j]为最合适dp[i][j]的i'（之一）
bool mark[510]; //意义与AC代码相同
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		memset(dp,0x2a,sizeof dp); //多组数据初始化
		memset(mark,false,sizeof mark);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",sum+i);
			sum[i]+=sum[i-1];
			dp[i][0]=sum[i]; //预处理
		}
		for (int j=1;j<m;j++)
			for (int i=1;i<=n;i++)
				for (int ii=j-1;ii<i;ii++)
					if (max(dp[ii][j-1],sum[i]-sum[ii])<dp[i][j]) //状态转移
						dp[i][j]=max(dp[ii][j-1],sum[i]-sum[ii]),pre[i][j]=ii;
//		printf("%d\n",dp[n][m]); //最短时间
		for (int j=m-1,i=n;j;j--) //利用pre数组一个一个往前跳并记录
		{
			i=pre[i][j];
			mark[i]=true;
		}
		for (int i=1;i<n;i++) //输出方式大致同AC代码
		{
			printf("%d ",sum[i]-sum[i-1]); //利用前缀和得到p[i]
			if (mark[i])
				printf("/ ");
		}
		printf("%d\n",sum[n]-sum[n-1]);
	}
	return 0;
}
```
**附件三：暴力代码（可以参考一下我对拍此类题目的暴力的写法）**
```cpp
#include<cstdio> //为了方便写，这里采用了状态压缩的方法，速度比较慢（用dfs虽然常数大且比较难写，但是更快），只能够过书本数<=11的数据，不过这种题小数据不会出错大数据也应该不会有错，因此我认为这样写暴力可行
#include<iostream>
using namespace std;
int tot[2000],t,n,m,a[510],ans,last,total,ansn; //last为上一台机器誊抄的最右边的那本书的位置；total为单个情况答案；ansn为答案的情况
int main()
{
	for (int i=0;i<(1<<10);i++) //线性求一个数在二进制下“1”的个数，方法本人原创
		tot[i]=tot[i>>1]+(i&1);
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			a[i]+=a[i-1]; //前缀和
		}
		ans=0x7fffffff;
		ansn=0;
		for (int i=0;i<(1<<n-1);i++) //状压每本书是否为誊抄它的机器誊抄的最右边那本书；最后本书一定是一台机器誊抄的最右边那本书，所以只需要考虑前面的情况
			if (tot[i]==m-1) //除最后一本书外共有(m-1)本书是一台机器誊抄的最右边那本书
			{
				total=0;
				last=0;
				for (int j=1;j<n;j++) //拆分该二进制数计算该情况的时间
					if ((i>>j-1)&1)
						total=max(a[j]-a[last],total),last=j;
				total=max(total,a[n]-a[last]);
				if (total<ans)
					ans=total,ansn=i;
			}
		printf("%d\n",ans);
		for (int i=1;i<n;i++)
		{
			printf("%d ",a[i]-a[i-1]); //除变量名，同DP代码
			if ((ansn>>i-1)&1) //同样是拆分二进制数，以判断是否要输出间隔
				printf("/ ");
		}
		printf("%d\n",a[n]-a[n-1]);
	}
	return 0;
}
```

希望这篇题解对大家有帮助！

---

## 作者：Instudy (赞：3)

这道题同[P1281书的复制](https://www.luogu.com.cn/problem/P1281)

典型的区间 $ dp $+贪心（输出）

用$ f[i][j] $表示i个人复制前j本书的最短时间

穷举最后一个人从哪开始复制,k是最后一个人开始复制的位置

$ f[i][j] = min(f[i][j], max(f[i-1][k-1], Sum[j] - Sum[k-1])); $

最后递归贪心输出答案即可

---

## 作者：YBJ1006 (赞：1)

看到什么最多的什么最少，想到二分答案。

思路：先二分出一个最小满足要求的答案。

检查函数：用贪心的思想从第一个人开始，能多抄就多抄。

最后答案因为要求前面的机器尽可能少，但又不能不超，所以从后往前贪心：能多抄就多抄。

注意：如何保证让前面的机器至少有一个抄呢？要记录一下前面还有多少个机器，如果剩余抄的书的数量等于前面未分的机器的数量，那么就给前面的每个机器分一本。

**上代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int m, k, a[550];
bool check(int x)
{
    int sum = 0;
    int cnt = 1;
    for (int i = 1; i <= m; i++)
    {
        if (a[i] > x)
            return false; //细节
        if (sum + a[i] <= x)
        {
            sum += a[i];
        }
        else
        {
            sum = a[i];
            cnt++;
        }
    }
    return  cnt <= k;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> m >> k;
        ll s = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> a[i];
            s += a[i];
        }
        ll l = 1, r = s, best = -1;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (check(mid))
            {
                best = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        pair<int, int>p[550];
        p[1].second = m;
        int t = 1;
        int sum = 0;
        for (int i = m; i >= 1; i--)
        {
            if (a[i] + sum > best || k-t==i)
            {
                p[t].first = i + 1;
                sum = a[i];
                p[++t].second = i;
            }
            else
            {
                sum += a[i];
            }
        }
        p[t].first = 1;
        int f = 1;
        for (int i = t; i >= 1; i--)
        {
            if (!f)
                cout << "/ ";
            f = 0;
            for (int j = p[i].first; j <= p[i].second; j++)
            {
                cout << a[j] << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：sad_lin (赞：0)

很显然看到要求区间和的最大值最小就可以想到二分答案，然后依次判断长度是否合法。

这题的输出比较特殊，越靠前的区间长度要越小，所以我们要将最后得到的答案从后向前依次划分区间即可。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=510; 
int t;
int n,k;
int a[N];

int check(int x){
	ll sum=0;
	int cnt=1;
	for(int i=1;i<=n;i++){
		if(sum+a[i]<=x){
			sum+=a[i];
		}
		else{
			sum=a[i];
			cnt++;
		}
	}
	return cnt<=k;
} 
int p[N];
void print(int x){
	ll sum=0;
	int cnt=k;
	memset(p,0,sizeof p);//标记是否需要划分 
	
	for(int i=n;i>=1;i--){//从后向前划分 
		if(cnt>i){
			p[i]=1;
			cnt--;
		}
		else if(a[i]+sum>x){
			sum=a[i];
			p[i]=1;
			cnt--;
		}
		else{
			sum+=a[i];
		}
	}
	
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
		if(p[i]){
			cout<<"/ ";
		}
	}
	cout<<"\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
    	cin>>n>>k;
		
		ll l=0,r=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			l=max(l,(ll)a[i]);//最小的答案也不能小于最大的a[i] 
			r+=a[i];//最大的答案是长度总和
		}
    	while(l<=r){
    		int mid=(l+r)>>1;
    		if(check(mid)){
    			r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
//    	cout<<l<<"\n";
    	print(l);
	}
    return 0;
}

```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
很容易想到 $dp$，考虑到要求字典序最下，所以还需要贪心。

设 $dp[i][k]$ 表示第 $i$ 个人复制前 $k$ 本书所需的最小时间，$j$ 表示上一个人做完后的书的下一本，那么，我们很容易想到这样一个方程 $dp[i][j]=min(dp[i][j],max(dp[i-1][j-1],s_k-s_{j-1}))$，其中 $s_k-s_{j-1}$ 表示从上一个人复制的最后一本书开始，到当前这个人复制的最后一本数结束，所需要的时间，$s_i$ 表示复制前 $i$ 本书所需的时间之和。该方程表示，当前这个人所需要的最短时间是他本来需要的时间和上一个人复制后他复制所需的时间，因为 $n$ 极小，所以暴力枚举即可，若 $n$ 较大，则需考虑斜率优化、四边形不等式优化等 $dp$ 优化方式。

---

## 作者：tmp_get_zip_diff (赞：0)

双倍经验：[P1281](https://www.luogu.com.cn/problem/P1281)。

首先，字典序小 $\to$ 前面的少写 $\to$ 后面的多写。

少些不好处理，多写的话能写就写。

二分时间，`check` 中倒序，贪心的让后面多写，并统计答案，最后输出即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;

const int N=505;
int m,k,a[N],sum,L[N],R[N];

int ll[N],rr[N];
bool check(int x)
{
	int sum=0,tot=k;
	rr[tot]=ll[tot]=m;
	for(int i=m;i>=1;i--)
	{
		if(sum+a[i]<=x)
		{
			sum+=a[i];
			ll[tot]=i;
		}
		else
		{
			tot--;
			if(tot==0)
				return false;
			rr[tot]=ll[tot]=i;
			sum=a[i];
		}
	}
	for(int i=1;i<=m;i++)
		L[i]=ll[i],R[i]=rr[i];
	return true;
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>m>>k;
		for(int i=1;i<=m;i++)
		{
			cin>>a[i];
			sum+=a[i]; 
		}
		int lt=0,rt=sum+1;
		while(lt+1<rt)
		{
			int mid=(lt+rt)>>1;
			if(check(mid)==true)
				rt=mid;
			else
				lt=mid;
		}
		for(int i=1;i<=k;i++)
		{
			for(int j=L[i];j<=R[i];j++)
				cout<<a[j]<<" ";
			if(i!=k)
				cout<<"/ ";
		}
		puts("");
	}
	return 0;
}
```

---

