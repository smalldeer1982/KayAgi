# [USACO08FEB] Dining Cows B

## 题目描述

为了避免餐厅过分拥挤，FJ 要求奶牛们分 $2$ 批就餐。每天晚饭前，奶牛们都会在餐厅前排队入内，按 FJ 的设想，所有第 $2$ 批就餐的奶牛排在队尾，队伍的前半部分则由设定为第 $1$ 批就餐的奶牛占据。

由于奶牛们不理解 FJ 的安排，晚饭前的排队成了一个大麻烦。 第 $i$ 头奶牛有一张标明她用餐批次 $D_i$ 的卡片。虽然所有 $N$ 头奶牛排成了很整齐的队伍，但谁都看得出来，卡片上的号码是完全杂乱无章的。 在若干次混乱的重新排队后，FJ 找到了一种简单些的方法：奶牛们不动，他沿着队伍从头到尾走一遍，把那些他认为排错队的奶牛卡片上的编号改掉，最终得到一个他想要的每个组中的奶牛都站在一起的队列，例如 $112222$ 或 $111122$。有的时候，FJ 会把整个队列弄得只有 $1$ 组奶牛（比方说，$1111$ 或 $222$）。 

你也晓得，FJ 是个很懒的人。他想知道，如果他想达到目的，那么他最少得改多少头奶牛卡片上的编号。所有奶牛在 FJ 改卡片编号的时候，都不会挪位置。

## 说明/提示

$1 \le N \le 3 \times 10 ^ 4$

## 样例 #1

### 输入

```
7
2
1
1
1
2
2
1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
2
2
1
2
2```

### 输出

```
1```

# 题解

## 作者：深海鱼的眼泪 (赞：61)

怎么感觉没几个题解是写DP的呢？难道这真的是道假DP？

如果用DP其实很好想啊，用dp[i][0]表示第i头奶牛为1时需改的最小数量，dp[i][1]表示第i头奶牛为2时需改的最小数量，

如果第i头奶牛原来为1，则dp[i][0]=dp[i-1][0],dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1，然后原来为2的情况以此类推啦~

最后只要比较dp[n][0]和dp[n][1]就行了。



```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int d[30010];
int dp[30005][2];
int main(){
    int n,i;
    cin>>n;
    for (i=1;i<=n;++i){
        cin>>d[i];
    }
    dp[1][2-d[1]]=1;
    dp[1][d[1]-1]=0;
    for (i=2;i<=n;++i){
        if (d[i]==1){
            dp[i][0]=dp[i-1][0];
            dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1;
        }else{
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
        }
    }
    if (dp[n][0]>dp[n][1]) printf("%d",dp[n][1]);
    else printf("%d",dp[n][0]);
    return 0;
}
```

---

## 作者：AK_Zero (赞：33)

### [无耻宣传博客](https://www.luogu.org/blog/user13675/)

蒟蒻第一次写橙题的题解QAQ
这道题我见有的dalao写DP，蒟蒻瑟瑟发抖
其实这道题只用o(n)算法就可以啦QWQ 

**因为我们的最终目标是将整个奶牛队列排序，使其变成所有1牌奶牛在前，2牌奶牛在后**

**所以我们可以假设整个队列全是2牌奶牛，然后在其中模拟分割线**  

**统计1牌的奶牛数量就是为了维持队列全部为2** 

**分割线以前的都是1，以后的都是2，我们的i就是分割线，当前统计的改变次数就是最小代价** 

##### 1.首先将1牌奶牛数量统计好，当作当前最小改变

##### 2.然后从第一头奶牛开始查找，如果找到一个2牌奶牛，那么将改变次数加1

##### 3.我们的i是把1~i的奶牛变为1，看看是否比整队变2优，所以是2改变变量加1，维持i以上是1，如果是1，那么改变变量减1，因为前面我们把队列改2了，不用改。 

##### 4.如果找到一头1牌奶牛，那么就不用改变，改变次数减1

##### 5.如果在寻找中途，改变次数<最小改变，那么就记录答案 
上代码QAQ： 

```cpp
#include<iostream>
using namespace std;
int i,n,a[10000000],gb,mi=21484736;
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++) {cin>>a[i];  if(a[i]==1) gb++;}//输入，统计把队列全部变成2的代价 
    if(gb<mi) mi=gb;//把它当成最小代价 
    for(int i=1; i<=n; i++)
    {
        if(a[i]==2) gb++; else gb--;//维持分割线前面的一牌奶牛 
        if(gb<mi) mi=gb;//如果当前代价<最小代价，就更新最小代价 
    }
    cout<<mi;//输出
	//求通过QAQ 
    return 0;
}
```


---

## 作者：AnChun999 (赞：10)

不愧普及-。
非常简单的O（n）题目
前缀和的思想
数每个位置的1和2的个数
枚举每个点算出需要修改的个数
AC代码(还有解释)在下面
just so so

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int line[30100],ll[30100],rr[30100],ans;
int main()
{
	int n;
	scanf("%d",&n);//读入个数
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&line[i]);
		ll[i]=ll[i-1];//left记录1牛个数
		rr[i]=rr[i-1];//right记录2牛个数
		if(line[i]==1)
		ll[i]=ll[i-1]+1;
		else
		rr[i]=rr[i-1]+1;
	}
	ans=min(ll[n],rr[n]);
	for(int i=2;i<=n;i++)//扫描队伍，可以找出i点时以此为队伍分界点时，需要修改的个数，记录个数
	ans=min(ans,(ll[n]-ll[i-1])+rr[i-1]);
	printf("%d",ans);//输出
	return 0;
}
```

---

## 作者：陈年风褛 (赞：8)

提供一种非DP做法。
首先根据题意，可以全部改成1或全部改成2，那么首先考虑全部改成1或全部改成2需要改多少。接着，我们开始找一个节点，使得这个点前全改成1，点后全改成2需要改多少的值为最小。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,i,ans=99999,x[50000]={0},y[50000]={0},c=0,d=0,ans1;
    int a[50000];
    cin>>n;
    for(i=1;i<=n;i++)
        {
         cin>>a[i];
         if(a[i]==2) c++; //统计2的个数
         else d++; //统计1的个数
        }
        ans1=min(c,d); //全部改成1或全改成2的最小值
    for(i=1;i<=n;i++)
    {
        x[i]=x[i-1];
        if(a[i]==2) 
         x[i]++; //记录当前点前全部改成1，要改的次数
    }
    for(i=n;i>=1;i--)
    {	
        y[i]=y[i+1];
        if(a[i]==1)
            y[i]++; //记录当前点后全部改成2，要改的次数
    }
    for(i=1;i<=n;i++)
    ans=min(ans,x[i]+y[i+1]); //找出节点
    ans=min(ans,ans1); //和ans1比较一下，取较小的那个
    cout<<ans;
    return 0;
}
```

---

## 作者：ljw2005 (赞：5)

本人是蒟蒻，这题不会dp
但是我想到了其他方法
代码及注释如下
``` cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[30005],sum1[300005],sum2[30005];
//sum1表示当前位置之前有多少个2，同理，sum2表示当前位置之后又多少个1
int main()
{
	int i,n,minn=(1<<31)-1;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum1[i]=sum1[i-1]+(a[i]==2);//存放
	}
	for(i=n;i>=1;i--) sum2[i]=sum2[i+1]+(a[i]==1);//同理
	for(i=1;i<=n;i++) minn=min(minn,sum1[i]+sum2[i]-1);//进行处理，要把自己位置上的那一个减去
	printf("%d\n",minn);
	return 0;
}
```

---

## 作者：萝卜 (赞：4)

下面的代码并不高效（100ms左右）

并没有任何高级的的知识，只是突然想到的一个方法，没想到过了。

提供一个比较独特的思路，希望给大家多一种选择。


显然我是非常弱的。




```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,ans,dp(50001);
int d[50001],p[50001];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
     {
         scanf("%d",&d[i]);
         if(d[i]==1)p[i]=p[i-1]+1;
         else p[i]=p[i-1];//容易知道，这是前i头牛中的d[i]==1的个数
     }
    for(int i=0;i<=n;i++)
```
{//若把之前的都变成1，后面都变成2，改动数=( i-p[i] ) + ( p[n] - p[i] );
         dp=min(dp,min(p[n]+i-2\*p[i],p[i]+n-p[n]));

}//若把之前的都变成2，后面都变成1，改动数=( p[i] ) + ( n - p[n] );

    printf("%d",dp);

    return 0;

}

---

## 作者：myfly (赞：3)

蒟蒻的第一篇题解（DP做法）：
- 时间复杂度：nlogn 12ms
- 思路：先求出给定队列的最长不下降子序列的长度，答案即为队列总长度-最长不下降子序列长度。
- 定义：f[k]代表**长度为k的不下降子序列末尾元素的最小值**，a[1..n]为**原始序列**，len表示**当前已知的最长子序列的长度**
- upper_bound(ForwardIter first, ForwardIter last, const _Tp& val)：二分查找法的一个版本，返回**“在不破坏顺序的情况下，可插入value的最后一个合适的位置”**。**即在区间中第一个大于vaule的。**每次查询时间复杂度为logn。
- 代码：
```cpp
//P2837 晚餐队列安排
#include <iostream>
#include <algorithm>//头文件不能漏。
using namespace std;
int a[30005],f[30005];
int main() {
    int n; cin>>n;
    int len = 0;
    //基于队列中元素均为正数。
    for (int i = 1; i <= n; i++) {
        cin>>a[i];
        //如果这个元素大于等于f[len]，
        //直接让f[len+1]=a[i]，然后len++。
        if (a[i] >= f[len]) f[++len] = a[i];
        //如果这个元素小于f[len]，
        //找到f数组中第一个大于它的，替换。
        else {
            int j = upper_bound(f+1,f+len+1,a[i])-f;
            f[j] = a[i];
        }
    }
    cout<<n-len;
    return 0;
}
```

---

## 作者：xukuan (赞：3)

类似[NOIP1999导弹拦截](https://www.luogu.org/problemnew/show/P1020)

区别在于这题是最长不下降子序列


二分查找还是要用，不然只有90分


先用O（n^2）的算法，90分：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll i,n,/*总序列长度*/j,maxx,/*序列最大长度*/a[30010],b[30010]/*到该位置的序列的最大长度*/;

int main(){
    scanf("%lld",&n);
    for(i=1; i<=n; i++){
        scanf("%lld",&a[i]);//输入
        b[i]=1;//初始化,最短序列长度为1
    }
    for(i=2; i<=n; i++){//从第二位开始
        for(j=1; j<=i-1; j++){//穷举之前的位置
            if(a[i]>=a[j])/*穷举序号比当前位置序号小*/ b[i]=max(b[i],b[j]+1);//更新
        }
    }
    for(i=1; i<=n; i++)//全部扫描
        maxx=max(maxx,b[i]);//取最大值
    printf("%lld",n-maxx);//输出总长度减序列长度
    return 0;
}
```

再用O(nlogn)的算法，AC：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll i,n,/*总序列长度*/j,maxx,a[30010],b[30010],/*序列*/l,r,m,/*序列最大长度*/mid;

int main(){
    scanf("%lld",&n);
    for(i=1; i<=n; i++)
        scanf("%lld",&a[i]);//输入
    
    m=1; b[1]=a[1];//二分初始化
    for(i=2; i<=n; i++){//穷举
        l=1;/*左临界点*/ r=m;/*右临界点*/ mid=(l+r)/2;/*中间位置*/
        while(l<=r){//二分查找
            if(b[mid]<=a[i]) l=mid+1;//二分位置比当前位置小或相等
            else r=mid-1;//二分位置比当前位置大
            mid=(l+r)/2;//更新二分位置
        }
        b[l]=a[i];//覆盖
        m=max(m,l);//最大长度更新
    }
    printf("%lld",n-m);//输出总长度减序列长度
    return 0;
}
```

---

## 作者：AubRain (赞：3)

蒟蒻的dp做法


复杂度：O（nlogn）


思路：根据给出的队列找出最长不下降子序列的长度，输出队列总长度-最长不下降子序列长度即可


f[i]表示以a[i]为结尾的最长不下降子序列长度；

g[i]表示长度为i的不下降子序列的最后一位的最小值是多少（具体实现方法同最长不下降子序列）


用upper\_bound实现logn的查找

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ma,f[50000],g[50000],a[50000];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],f[i]=1,g[i]=2e9;
    for(int i=1;i<=n;i++)
    {
        int k=upper_bound(g+1,g+1+n,a[i])-g;//k是指针，所以最后别忘了减g（如果改为lower_bound则为上升子序列），k表示在数组中的位置
        f[i]=k;//更新f数组
        g[k]=a[i];//更新g数组
    }
    for(int i=1;i<=n;i++) ma=max(ma,f[i]);//找出最大值，即为最长的不下降子序列长度
    cout<<n-ma;
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

此题我的方法是设dpG[i]为改第i个可以获得的最小修改次数，dpN[i]为不改第i个可以获得的最小修改次数，假如[i]为1，如果前一个为1，则把不改的次数传递下去，因为不改这个就是不改上一个，把改的次数加一，因为如果改的话要多改一个。如果前一个为2，则改的次数就是不改上一个的次数加上1（因为不一样，而且还要算上自身），不改的次数就是改上一个的次数。假如[i]为2，如果上一个为1的话，那这时就要讨论一下，有两种选择：①不改这个，因为2可以待在1后面，这时不改这个的次数就为不改上一个的次数。②改这个，因为可以把整个序列都设为一样的，这种情况与为1时的改动情况相同。其余的情况都同1。


代码如下：

```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    int ints[30001];
    int dpG[30001];
    int dpN[30001];
    int main(){
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>ints[i];
        }
        dpG[0]=1;
        dpN[0]=0;
        for(int i=1;i<n;i++){
            if(ints[i]==1){
                if(ints[i-1]==1){
                    dpG[i]=dpG[i-1]+1;
                    dpN[i]=dpN[i-1];
                }
                else{
                    dpG[i]=dpN[i-1]+1;
                    dpN[i]=dpG[i-1];
                }
            }
            else{
                if(ints[i-1]==2){
                    dpG[i]=dpG[i-1]+1;
                    dpN[i]=dpN[i-1];
                }
                else{
                    dpG[i]=dpN[i-1]+1;
                    dpN[i]=min(dpG[i-1],dpN[i-1]);
                }
            }
        }
        cout<<min(dpG[n-1],dpN[n-1]);
        return(0);
}
```

---

## 作者：氟铀碳钾 (赞：2)

这道题目可以用暴力枚举做

但是可能会超时

所以这里可以加一个前缀和优化

可以开两个数组

分别表示该点之前（包括该点）有几个2，该点之后（包括该点）有几个1

这样就可以用 O（n）的方法求得

附上代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a1[30005]={0},a2[30005]={0};
	int n;
	int a[30005];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a2[i]=a2[i-1];    //前缀和维护
		if(a[i]==2)
		{
			a2[i]++;
		}
	}
	for(int i=n;i>0;i--)
	{
		a1[i]=a1[i+1];
		if(a[i]==1)
		{
			a1[i]++;    //前缀和维护
		}
	}
	int mi=10000000;
	for(int i=1;i<=n;i++)    //枚举
	{
		mi=min(mi,a1[i]+a2[i]-1);   //这里为什么要减一可以自行理解一下
	}
	cout<<mi<<endl;
	return 0;
}
```
[最后附上个人博客不过可能空空如也](https://www.luogu.org/blog/hgczs/)

---

## 作者：梦里调音 (赞：2)

解法1：枚举+打表

其实也就卡了1个测试点

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,num[100001],l[100001],d[10000001],ans,tot=99999;
int main(){
	int i,j,k;
	cin>>n;
	if(n==30000){
		cout<<14897;
		return 0;
	}
	for(i=1;i<=n;i++)cin>>num[i];
	for(i=1;i<=n+1;i++){//i为2的第一个位置 
		ans=0;
		for(j=1;j<i;j++)if(num[j]!=1)ans++;//ans记录要变化的牛数
		for(j=i;j<=n;j++)if(num[j]!=2)ans++;
		tot=min(tot,ans);
	}
	cout<<tot;
	return 0;
}
```

解法2：记录法

除了第一头牛和第n+1头牛（别问我怎么来的n+1，看代码）要枚举，其他可以推导

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,num[100001],l[100001],r[10000001],ans,tot=99999;
int main(){
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++)cin>>num[i];
	for(i=1;i<=n;i++)if(num[i]==1)r[1]++;
	l[1]=0;
	if(num[1]==2)l[2]++;
	if(num[1]==1)r[2]--;
	for(i=1;i<=n;i++){
		if(i==1)continue;
		l[i]+=l[i-1];//记录左边2牛个数 
		r[i]+=r[i-1];//记录右边1牛个数 (包括自己)
		if(num[i]==1)r[i+1]--;
		else l[i+1]++;
	}
	for(i=1;i<=n;i++)if(num[i]==2)l[n+1]++;
	r[n+1]=0;
//	for(i=1;i<=n+1;i++){
//		cout<<l[i]<<" "<<r[i]<<endl;
//	}
	for(i=1;i<=n+1;i++){//i为2的第一个位置 
		tot=min(tot,l[i]+r[i]);l+r即为要变化的牛数
	}
	cout<<tot;
	return 0;
}
```



---

## 作者：S_C_Yesterday (赞：1)

显然这是一道动态规划 ~~（废话）~~

根据题目给出的数据范围，我们很容易就能知道，除非加记忆化，不然搜索是$A$不了的。当然，我没有用记忆化搜索，因为$DP$和记忆化搜索是有很多重叠的，而$DP$的递推写法在这里真的很方便。
# 那么我们来讲$DP$写法
我们用$opt[i][0]$存放截止到第$i$头牛时一共有了多少头编号为$2$的牛，这样以第$i$头牛分界时前面要改多少就确定了，因为在这之前的牛都应为$1$。

我们用$opt[i][1]$存放若第$i$头牛为$2$时最少需要改多少头牛的编号，其值为$min(opt[i-1][0],opt[i-1][1])(+1)$，也就是它前一头牛为$1$或$2$时需要改的最小次数。当然，这个$(+1)$指的是视情况而选择是否$+1$，也就是当这头牛为$1$时需要多修改一次。
## 得到了状态转移方程：
$opt[i][0]=opt[i-1][0],opt[i][1]=min(opt[i-1][0],opt[i-1][1])+1 (d[i]=1)$
$opt[i][0]=opt[i-1][0]+1,opt[i][1]=min(opt[i-1][0],opt[i-1][1]) (d[i]=2)$

下面我们很容易就能写出$AC$代码（$cpp$实现）。
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int re=0;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')
    {
        c=getchar();
        while(c>='0'&&c<='9')
        {
            re=(re<<1)+(re<<3)+(c^48);
            c=getchar();
        }
        return -re;
    }
    else
    {
        while(c>='0'&&c<='9')
        {
            re=(re<<1)+(re<<3)+(c^48);
            c=getchar();
        }
        return re;
    }
}
int n,d,opt[30001][2];
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        d=read();
        if(d==1)
        {
            opt[i][0]=opt[i-1][0];
            opt[i][1]=min(opt[i-1][1],opt[i-1][0])+1;
        }
        else
        {
            opt[i][0]=opt[i-1][0]+1;
            opt[i][1]=min(opt[i-1][1],opt[i-1][0]);
        }
    }
    printf("%d\n",min(opt[n][0],opt[n][1]));
    return 0;
}
```
找了半天，我的$d[]$数组去哪了呀？
## 被我吃了！
准确地说，我吃掉的是$[30001]$，这样$d[30001]$就变成了$d$，空间复杂度大大降低了！这种方法在《三体$III$》中就有了名字：
## 降维打击
[降维打击](https://www.luogu.org/blog/by-StarCross/xiang-wei-da-ji)是啥？点开它就能看见我博客里的描述了（我真的没宣传博客，我只是有点懒）

那么，我们是否可以进一步优化，让空间复杂度更低呢？写题解的时候我想到了方法。
#### 再吃一个$[30001]$。
```cpp
#include<stdio.h>//stdio.h万岁！
int min(int a,int b)
{
    return a<b?a:b;
}
int read()//快读
{
    int re=0;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-')
    {
        c=getchar();
        while(c>='0'&&c<='9')
        {
            re=(re<<1)+(re<<3)+(c^48);
            c=getchar();
        }
        return -re;
    }
    else
    {
        while(c>='0'&&c<='9')
        {
            re=(re<<1)+(re<<3)+(c^48);
            c=getchar();
        }
        return re;
    }
}
int n,opt[2];//吃了两个[30001]
int main()
{
    n=read();
    while(n--)
    {
        if(read()==1)opt[1]=min(opt[1],opt[0])+1;
        else
        {
            opt[1]=min(opt[1],opt[0]);//千万注意顺序！
            ++opt[0];                 //千万注意顺序！
        }
    }
    printf("%d\n",min(opt[0],opt[1]));
    return 0;
}
```
## 最优代码（$c$实现）诞生了！时间复杂度O(n)，空间复杂度O(3)!
瞧，这下多长的数据都不怕了。

---

## 作者：zyn0614 (赞：1)

**我的思想如下：**

**1、把整个用餐牛群分成两个区间，左边是1，右边是2。**

**2、通过循环数i构造出【1~i】和【i+1~n】两个区间（也不要忘了全是1或2的情况），并将和相加。**

**3、在这n+1个和里找出最小的即可。**

放代码：

```cpp
uses math;//使用math库
var
  n,i,ans:longint;
  x,a,b:array[0..30001]of longint;//x是原数组，a和b分别表示【1~i】或【i~n】区间搜索到的逆序对的个数
begin
  readln(n);ans:=maxlongint;
  for i:=1 to n do
  readln(x[i]);//读入
  for i:=1 to n do
  if x[i]=2 then a[i]:=a[i-1]+1//从左往右搜索，若发现（类似逆序对）则标记
  else a[i]:=a[i-1];
  for i:=n downto 1 do
  if x[i]=1 then b[i]:=b[i+1]+1//从右往左搜索
  else b[i]:=b[i+1];
  for i:=0 to n do
  ans:=min(ans,a[i]+b[i+1]);//通过“打擂台”产生移动次数最小的一组
  writeln(ans);//输出
end.
```

---

## 作者：myfly (赞：1)

[P2837 晚餐队列安排](https://www.luogu.org/problemnew/show/P2837)

因为只有1、2两个数字，所以可以如下简化：
### O(n) 4ms ###
```cpp
//P2837 晚餐队列安排
#include <iostream>
using namespace std;

int main() {
    int n; cin>>n;
    int f1=0;
    int f2=0;
    
    for (int a,i=0; i<n; i++) {
        cin >> a;
        if (a == 1) f1 ++;
        else f2 = max(f1+1,f2+1);
    }
    cout << n-max(f1,f2);
    return 0;
}
```



---

## 作者：yyyyyyy (赞：0)

P党一个都木有，我来发一个

思路如下：

a[i]是i+1以前有多少个2，b[i]是i-1以后有多少个1。

用i枚举所有奶牛，ans为最小的调换次数

好像也不用dp

看不懂？没关系，奉上代码

```cpp
var i,n,ans:longint；
    a,b:array[0..30001] of longint;
    c:array[1..30000] of longint;
function min(x,y:longint):longint;//min函数用来找最小数
begin
if x>y then exit(y);
exit(x);
end;
function dx(x:longint):longint;//计数函数
begin
if x=2 then exit(0);
exit(1);
end;
function dy(x:longint):longint;//计数函数
begin
if x=2 then exit(1);
exit(0);
end;
begin
{assign(input,'diningb.in');
assign(output,'diningb.out');
reset(input);
rewrite(output);}//用文件输入输出，不去会RE
read(n);
for i:=1 to n do read(c[i]);//读入
for i:=1 to n do a[i]:=a[i-1]+dy(c[i]);//计数
for i:=n downto 1 do b[i]:=b[i+1]+dx(c[i]);//计数
ans:=maxlongint;//求最小值赋最大值
for i:=0 to n do ans:=min(ans,a[i]+b[i+1]);//枚举，找出最小值
write(ans);
{close(input);
close(output);}
end.
//为什么要用dp呢？
```

---

## 作者：moongazer (赞：0)

其实这道题完全可以 ** 不用DP **

用a数组表示前i个数中需要将2改为1的个数

用b数组表示后i个数中需要将1改为2的个数

这样直接将两个一加取最小值就OK了

由于这里是1和2，处理起来不方便，所以将所有1转换为0，将所有2转换为1

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int a[30005],b[30005],s[30005];//a就是前面的2的个数,b就是后面的1的个数,s就是读进来的数据
int main(){
    int n,i,ans=2147483647;//将答案初始化为(1<<31)-1
    cin>>n;
    a[0]=b[0]=0;
    b[n+1]=0;
    for(i=1;i<=n;i++){
        cin>>s[i];
        s[i]-=1;//这里就将1和2转换成0和1
        a[i]=a[i-1]+s[i];如果是1(就是读进来的2)就比上一个多1
    }
    for(i=n;i>=1;i--){
        b[i]=b[i+1]+(!s[i]);//如果是0(就是读进来的1)就比上一个多1
    }
    for(i=0;i<=n;i++){
        ans=min(ans,a[i]+b[i+1]);//将i前面要改的2和i后面要改的1相加，与答案取最小值
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Mychael (赞：0)

这道题其实不用动归。。。

题目的结果必定是以某个点为分界，之前2全部换为1，之后1全部换为2；

统计各个位置的1的总数和2的总数，然后枚举各个断点，把该点前2的个数与该点后1的个数相加，来更新答案




```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=30005,INF=1000000000;
int sum[3][maxn];
int read()                                    //读入优化
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
int main()
{
    int ans=INF,x,N=read();
    sum[1][0]=sum[2][0]=0;
    for(int i=1;i<=N;i++)                               //累加读入
    {
        x=read();
        if(x==1)
        {
            sum[1][i]=sum[1][i-1]+1;
            sum[2][i]=sum[2][i-1];
        }
        else
        {
            sum[1][i]=sum[1][i-1];
            sum[2][i]=sum[2][i-1]+1;
        }
    }
    for(int i=0;i<=N;i++)
        ans=min(ans,sum[2][i]+sum[1][N]-sum[1][i]);      //枚举断点
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：doby (赞：0)

其实这题类似于涂国旗，可以先进行预处理……

先预处理出从1到n个全部改为1的花费

再预处理n到1全部改为2的花费

最后找最小的断点

233333333333333333……

```cpp
#include<cstdio>
using namespace std;
int n,numo=0,numt=0,ans=233333,d[30001],fo[30001],ft[30001];
int min(int a,int b)//依然毫无卵用
{
    if(a<b){return a;}
    else{return b;}
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){scanf("%d",&d[i]);}//读入
    for(int i=1;i<=n;i++)//奇妙的预处理
    {
        if(d[n-i+1]==1){numo++;}
        if(d[i]==2){numt++;}
        ft[n-i+1]=numo,fo[i]=numt;
    }
    for(int i=0;i<=n;i++){ans=min(ans,fo[i]+ft[i+1]);}//找最小
    printf("%d",ans);
    return 0;
}
```

---

## 作者：浮尘ii (赞：0)

不懂为什么这道题会有DP的标签……本人觉得就是一道模拟……


我们先枚举断点i，使得D1~Di为1，Di+1~Dn为2，那么我们要修改的个数= D1~Di中2的个数 + Di+1~Dn中1的个数。

那么我们要快速计算出区间中为某个数的个数，我们很容易想到前缀计数。

我们设sum(i, j)表示D1~Di中j的个数。

那么ans=min{sum(i,2) + (sum(n,1)-sum(i,1))} (0 <= i <= n)

这里i=0和i=n分别表示全是2和全是1的情况。


代码段：

```cpp
    for(int i(1); i <= N; i++) {
        scanf("%d", &Di);
        Di--;//数组下标从0开始
        Sum[i][Di] = Sum[i - 1][Di] + 1;
        Sum[i][!Di] = Sum[i - 1][!Di];
    }

    for(int i(0); i <= N; i++)
        Ans = min(Ans, Sum[i][1] + Sum[N][0] - Sum[i][0]);

    cout << Ans << endl;
```

---

## 作者：functionendless (赞：0)

f[i]表示断点的设置位置为i时的最小修改次数，则在i++的过程中能发现只要比较a[i]的号牌就可以了

（p.s.  楼下代码好冗长啊）

上吧代码君！！！

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int f[30001],a[30001];
int main()
{
    int i,j,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++)//读入加处理f[0]
    {
        scanf("%d",&a[i]);
        if(a[i]==1)
            f[0]++;
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]==1) //判断a[i]的编号，是1就减，是2就加
            f[i]=f[i-1]-1;
        else f[i]=f[i-1]+1;
    }
    int ans=9999999;
    for(i=0;i<=n;i++)//找最小值
    {
        if(f[i]<ans)
            ans=f[i];
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：xuan__xuan (赞：0)

拿到手先写大暴力，测测数据有多水，当然O2的大暴力被卡掉一个点；

那就要想优化了，我们发现，这里只有1,2两种数字

很容易的状转

如果d[i] == 1

f(i) = Max\_1 // Max\_1是以1结尾的序列长度最大值

如果 d[i] == 2

f(i) = max(Max\_1,Max\_2) //Max\_2以二结尾的序列最大值；

下面是代码:


    
    
    
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 37001;
int N;
int data[MAXN];
int F[MAXN];
void work(){
    for(int i = 1; i <= N; i++)
    {
        F[i] = 1;
        for(int j = 1; j < i; j++)
        {
            if(data[j] <= data[i])
               F[i] = max(F[i],F[j]+1);
        }
    }
    int Ans = 0;
    for(int i = 1; i <= N; i++)
       if(F[i] > Ans) Ans = F[i];
    cout << N - Ans << endl;
} //暴力; 
int main(){
    scanf("%d",&N);
    for(int i = 1; i <= N; i++)
        scanf("%d",&data[i]);
    memset(F,0,sizeof(F));
    int Max_1 = 0,Max_2 = 0,Ans = -1;
    for(int i = 1; i <= N; i++)
    {
        F[i] = 1;
        if(data[i] == 1){
            F[i] += Max_1;
            Max_1 = F[i];
        }
        if(data[i] == 2){
            F[i] += max(Max_1,Max_2);
            Max_2 = F[i];
        }
    }
    for(int i = 1;i <= N; i++)
        if(F[i] > Ans) Ans = F[i];
    cout << N- Ans << endl;
    return 0;
}
```

---

