# [USACO1.3] 滑雪课程设计Ski Course Design

## 题目描述

农民约翰的农场里有 $n$ 座山峰，每座山都有一个在 $0$ 到 $100$ 之间的整数的海拔高度。在冬天,因为山上有丰富的积雪，约翰经常开办滑雪训练营。

不幸的是，约翰刚刚得知税法在滑雪训练营方面有新变化，明年开始实施。在仔细阅读法律后，他发现如果滑雪训练营的最高和最低的山峰海拔高度差大于 $17$ 就要收税。因此，如果他改变山峰的高度（使最高与最低的山峰海拔高度差不超过 $17$ ），约翰可以避免支付税收。

如果改变一座山 $x$ 单位的高度成本是 $x^2$ 单位，约翰最少需要付多少钱才能使海拔最高的山峰与海拔最低的山峰的高度之差不超过 $17$ 约翰只愿意改变整数单位的高度。

## 说明/提示

#### 样例输入输出 1 解释

约翰保持高度为 $4$、$20$ 和 $21$ 的山的高度。他增高高度为 $1$ 的山，变成高度 $4$ ，花费 $3^2 = 9$。他降低了高度为 $24$ 的山变成高度 $21$，也花费 $3 ^ 2 = 9$。因此总共花费 $9 + 9 = 18$。

---

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 1000$，$0 \leq a_i \leq 100$。

## 样例 #1

### 输入

```
5
20
4
1
24
21```

### 输出

```
18```

# 题解

## 作者：xfydemx (赞：45)

这题思路很清晰，暴力出奇迹

我就再说一下枚举的细节吧：

-找出上下界限

-以界限为界判断高低，若高于则全部削去，低于则削去差大于17的部分

上代码：


    
    
    
 

```cpp
#include<bits/stdc++.h>
using namespace  std;
int a[100000],n,minn,s=1e9+1,sum;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i];
    sort(a+1,a+n+1);//找出最大和最小情况，这里用sort只是我强行偷懒
    for(int j=a[1];j<=a[n];j++)
    {
        sum=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]-j>17) sum+=(a[i]-j-17)*(a[i]-j-17);   //若高于则全部削去，低于则削去差大于17的部分
            if(a[i]<j) sum+=(a[i]-j)*(a[i]-j);
        }    
        s=min(sum,s);  //维护结果
    }
    cout<<s;
}
```

---

## 作者：「QQ红包」 (赞：23)

先枚举山的高度，然后再去带进去算费用，求min，简单粗暴。

```cpp
#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#define LL unsigned long long
using namespace std;
int n;//山峰数量
int a[1010];//存没做山峰的海拔高度 
int w;//每次枚举时修改山峰高度的花费 
int m;//需要的最小的花费 
int i,j;//循环控制变量 
int main() 
{
    freopen("skidesign.in","r",stdin);
    freopen("skidesign.out","w",stdout); 
    scanf("%d",&n);//读入山峰数量 
    m=200000000;
    for (i=1;i<=n;i++)//读入每个山峰的高度 
        scanf("%d",&a[i]);
    for (i=0;i<=84;i++)//枚举，因为所有山峰高度都在100一下所以只需搜到84
    {//山峰高度修改后范围：i<a[j]<i+17
        w=0;//w一定要清零 
        for (j=1;j<=n;j++)//统计 
        {
            if (a[j]<i)//如果山峰j高度小于i
                w+=(i-a[j])*(i-a[j]);//加上改这座山所需的费用
            if (a[j]>i+17)//如果这座山房高度大于i+17
                w+=(a[j]-(i+17))*(a[j]-(i+17)); 
        }
        if (w<m) m=w;//如果所需费用小于min 
    } 
    cout<<m<<endl; 
    return 0;
}
```

---

## 作者：yummy (赞：10)

（本蒟蒻第一次发题解）
讲真这道题挺简单的。
求出最高峰和最低峰，
依次搜索区间从
最低峰高度~最低峰高度+17，
最低峰高度+1~最低峰高度+18，
......
最高峰高度-17~最高峰高度,。
```cpp
#include<iostream>
using namespace std;
int a[1005]={0};//记录山峰高度
int h=0,l=100,n,b,p;
//h=最高峰，l=最低峰，b=最好价格，p=每次价格。
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>h)
            h=a[i];
        if(a[i]<l)
            l=a[i];
    }
	//输入并判断
    for(int i=l;i<h-16;i++)
    {
        p=0;
        for(int j=1;j<=n;j++)
        {
            if(a[j]<i)
                p+=(i-a[j])*(i-a[j]);
            if(a[j]>i+17)
                p+=(a[j]-i-17)*(a[j]-i-17);
            //计算价格
        }
        if(i==l||p<b)
            b=p;
    }
    cout<<b;
    return 0;
}

```


---

## 作者：Sea_Level (赞：5)

这题就是枚举。很简单。直接上代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>//我习惯多写点头文件
using namespace std;
int a[1005];//用来存山峰的高度
int main() {
    int n;//共有n座山峰
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 1e9;//1e9就是10的9次方的意思，是一个很大的数。
    for (int low = 0; low + 17 <= 100/*枚举山峰的最低高度，最低高度+17不能大于100*/; low++) {
        int high = low+17;//最高高度不用枚举，直接加17就可以了。因为要用到最高高度，所以前面最低高度+17必须小于等于100。
        int sum = 0;//sum用来存费用和。
        for (int i = 0; i < n; i++) {//还要枚举一遍a数组
            if (a[i] < low) {//如果太小
                sum += (low - a[i])*(low - a[i]);//增加到最低高度，因为这样花费最少
            }
            if(a[i] > high){//如果太大
                sum += (a[i] - high)*(a[i] - high);//减少到最高高度，因为这样花费最少
            }
        }
        if(sum < ans){//如果现在的花费比原先的最小花费还小
            ans = sum;//更新答案，因为我们答案要的是最小花费
        }
    }
    cout << ans << endl;//输出
    return 0;//功德圆满，华丽结束
}
```


---

## 作者：phil071128 (赞：5)

## 因为我是**蒟蒻**，所以发一个蒟蒻能看得懂的代码

### 思路：简单DFS

暴力枚举所有可能的标准（这题不会超时的）

- 把所有高于标准的都削去

- 低于标准-17的都加上（直到加到标准-17）

基本每行都有注释了
```cpp
#include <bits/stdc++.h> 
using namespace std;
int a[10000]; //存每座山峰的高度 
int n;	//山峰总共的个数 
int mi=0x7ffffff;//这里0x7ffffff是一个很大的数，也就是int的最大值 
void dfs(int k){
	int sum=0;  //当前以k为标准，当前的所有花费 
	//大于k的都减去，小于k的都加去 
	for(int i=1;i<=n;i++){
		if(a[i]>k+17){
			//这个山峰大于标准，减去
			sum+=pow(a[i]-k-17,2); //费用是减去的高度 的平方（仔细读题） 
		}
		if(a[i]<k){
			//这个山峰小于标准，加上
			sum+=pow(k-a[i],2);//费用是增加的高度 的平方（仔细读题） 
		}
	} 
	//这里我们不能让老实人农民约翰多花钱，所有就要更新最小的费用 
	mi=min(mi,sum);
	return ; 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];//华丽的输入了每一个山峰的高度 
	}  
	sort(a+1,a+1+n);//快速排序（这里下标是从1开始的，可以学习一下写法） 
	for(int i=a[1];i<=a[n];i++){//因为这题本来就是水题（划掉）可以暴力，从最小山峰高度到最大山峰的高度之间的所有设为标准的话都不会爆
		//这里挺好想的，你要设标准总不可能比最小的还小，最大的还大吧？另外这之间的所有（注意是所有）都可能成为标准
		//不一定只有山峰的高度才会是标准 
		dfs(i);
	}
	cout<<mi;
	return 0;
} 
```
再次感谢管理大大能够通过


---

## 作者：Zimo (赞：5)

菜OJ题号：1814 http://caioj.cn/problem.php?id=1814

洛谷题号：P3650 https://www.luogu.org/problemnew/show/P3650

这题暴力就过了。。。

##### 我的思路：

先给所有山排序（从小到大），for i从最低的山的高度到最高的高度

i代表最后保留的最低的山，把所有低于i的都补上，把所有高过i+17的都搞掉

用min保存最低的消费（即答案）。

##### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1001],n;
int sqr(int a) {return a*a;}
main()
{
	int min=999999999;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=a[1];i<=a[n];i++)
	{
		int s=0;
		for(int j=1;j<=n;j++)
		{
			if(a[j]<i) s+=sqr(i-a[j]);
			else if(a[j]>i+17) s+=sqr(a[j]-i-17);
		}
		if(s<min) min=s;
	}
	printf("%d\n",min);
	return 0;
}
```

---

## 作者：xiaoniu142857 (赞：3)

## 题意概述
给定一个长度为 $n$ 的数列 $\{a_n\}$，将 $a_i$ 改为 $b$ 所需的代价是 $(a_i-b)^2$。求使得 $\max(\{a_n\})-min(\{a_n\})\le17$ 所需的最小代价。
## 解题思路
看到平方，我第一时间想到的就是三分。  
如果不会三分法，右转 [OI Wiki](https://oi.wiki/basic/binary/#%E4%B8%89%E5%88%86%E6%B3%95) 学一学。

设要将数列的所有元素修改到 $[x,x+17]$ 区间内，问题转换为 $x$ 在某个取值下总代价最小，求这个最小总代价。  

于是有 $x\in [\min(\{a_n\}),\max(\{a_n\})-17]$，因为若 $[x,x+17]$ 的范围超出了数列的取值范围，则一定不会更优。  

对于一个元素 $a_i$ 所需的代价为：
$$\text{cost}_i=
\begin{cases}
   (a_i - x)^2&(a_i<x),\\
   0&(x\leq a_i\leq x + 17),\\
   (a_i - x - 17)^2&(a_i>x + 17).
\end{cases}
$$
以 $x$ 为自变量画出 $\text{cost}_i$ 的图像，长这个样子:  
![](https://cdn.luogu.com.cn/upload/image_hosting/gz3u6fmz.png)  
很显然，这是一个单谷函数。  

而总代价即为：
$$
\sum_{i = 1}^{n}\text{cost}_i
$$
单谷函数的和还是单谷函数，可以直接使用三分法求最小代价。时间复杂度 $O(n\log n)$，32ms 跑得飞起。
## Code
```cpp
#include <iostream>
using namespace std;
const int N=1000;
const int INF=0x3f3f3f3f;
int a[N],n;
int f(int x)  // 计算区间取[x,x+17]时总代价
{
    int s=0;
    for(int i=0;i<n;++i)
    {
        if(a[i]<x) s+=(x-a[i])*(x-a[i]);
        else if(a[i]>x+17) s+=(a[i]-x-17)*(a[i]-x-17);
    }
    return s;
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int l=INF,r=-INF,m1,m2;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        l=min(l,a[i]);
        r=max(r,a[i]);
    }
    r-=17;
    while(l<r)  // 三分
    {
        m1=(l+r>>1),m2=m1+1;
        if(f(m1)<f(m2)) r=m2-1;
        else l=m1+1;
    }
    cout<<f(l);
    return 0;
}
```
Update 2025.2.11：笔误，`单峰函数` $\to$ `单谷函数`。

---

## 作者：eegg (赞：2)

```cpp
	#include<cstdio>
    using namespace std;
  	int a[999999];
 	int main()
  	{
      	int sum,max=0,x=0,min=99999999,n,i,j,k;
      	scanf("%d",&n);
      	for(i=0;i<n;i++)
          	scanf("%d",&a[i]);
      	x=99999999;
      	for(i=0;i<=83;i++)
      	{
          	k=i+17;//最高山
          	sum=0;//清零
          	for(j=0;j<n;j++)//第j个山
          	{
              	if(a[j]<i)//统计一共需要多少钱
                  	sum=sum+(i-a[j])*(i-a[j]);//统计一共多少钱
              	if(a[j]>k)//统计一共需要多少钱
                  	sum=sum+(k-a[j])*(k-a[j]);//统计一共多少钱
          	}
          	if(sum<min)//找到花钱最少的方法
              	min=sum;
      	}
      	printf("%d",min);
      	return 0;
  	}
 ```

---

## 作者：Celebrate (赞：1)

这一题从最矮的一次最矮山峰的高度到最高山峰的高度

每次枚举都搜索1-n座山峰，

多余则把多余i的部分全部削去

少于i-17则补到i-17

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
int n,a[1100];
int minn=999999999;
inline int cmp(const void *xx,const void *yy)//排序 
{
	int x=*(int*)xx;
	int y=*(int*)yy;
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
inline int _(int x){return x*x;}//输出他们的平方 
int main()
{
	 int i,j;scanf("%d",&n);
	 for(i=1;i<=n;i++) scanf("%d",&a[i]);//输入 
	 qsort(a+1,n,sizeof(int),cmp);//排序 
	 for(i=a[1];i<=a[n];i++)//从最矮的一次最矮山峰的高度到最高山峰的高度
	 {
	 	int s=0;
	 	for(j=1;j<=n;j++)//每次枚举都搜索1-n座山峰
	 	{
	 		if(a[j]>i)    s=s+_(a[j]-i);//对于 
	 		if(a[j]<i-17) s=s+_(i-17-a[j]);//少于 
	 	}
	 	minn=min(minn,s);//求最右值 
	 }
	 printf("%d\n",minn);//输出 
	 return 0;
}
```

---

## 作者：huxulin (赞：1)

...我们暴力枚举修改后的山峰高度的最大值再跑一遍每次算一个最小值就可以了.


```cpp

#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

int A[maxm];
int n,sum,maxd,ans=INF,mind=INF;

int sqr(int x){
    return x*x;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]),maxd=max(maxd,A[i]);

    for(int h=0;h<=maxd;h++){
        sum=0;
        for(int i=1;i<=n;i++){
            if(A[i]<h&&h-A[i]>17)sum+=sqr(h-A[i]-17);
            if(A[i]>h)sum+=sqr(A[i]-h);
        }
        ans=min(ans,sum);
    }
    
    printf("%d\n",ans);

    return 0;
}

```

---

## 作者：zzqDeco (赞：1)

### 看了的神的题解发现自己的好低能。~~我一个筠蒻~~
### 不富创意的题解见下（实质是把一样都是最高最低的搞到一起,然后一起向中间走）
```cpp
#include<iostream>
#include<algorithm>
//头文件（不喜欢万能头文件）
using namespace std;

int N,a[1010],ans,l,r,m[1010];//ans为答案，m为花费（其实是改造的高度）

bool cmp(int a,int b)
{
	return a<b;
}//比较函数

bool Compare()
{
	int x=0,y=0;
	for(int i=1;i<=N;i++)
	{
		if(i<=l)
		x+=(m[i]+1)*(m[i]+1);
		else
		x+=m[i]*m[i];
	}
	for(int i=N;i>=1;i--)
	{
		if(i>=r)
		y+=(m[i]+1)*(m[i]+1);
		else
		y+=m[i]*m[i];
	}
	return x<=y;
}//比较从高处和低处修的成本
void work()
{	
	while(1)
	{
		if(a[N]-a[1]<=17)
    	{
        	return;
        }//直到小于17才返回
		if(Compare())
		{
			for(int i=1;i<=l;i++)
			{
				m[i]++;
				a[i]++;
			}//改变高度
			for(int i=l+1;i<=N;i++)
			{
				if(a[i]==a[1])
				l++;
				else
				break;
			}//将指针右移
		}
		else
		{
			for(int i=N;i>=r;i--)
			{
				m[i]++;
				a[i]--;
			}
			for(int i=r-1;i>=1;i--)
			{
				if(a[i]==a[N])
				r--;
				else
				break;
			}
		}//同上
	}
}

int main()
{
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>a[i];
	}
	l=1;
	r=N;
	sort(a+1,a+N+1,cmp);//排序
	for(int i=2;i<=N;i++)
	{
		if(a[i]==a[1]) l++;
		if(a[i]!=a[1]) break;
	}
	for(int i=N-1;i>=1;i--)
	{
		if(a[i]==a[N]) r--;
		if(a[i]!=a[N]) break;
	}//初始化指针
	work();
	for(int i=1;i<=N;i++)
	{
		ans+=m[i]*m[i];
	}//计算和
	cout<<ans;
}
```
### 解释一下：
### l，r指针表示左右界限（表示最高数和最低数，及把相同的最高数和最低数合并）
### m只表示改变的高度，不是最终的结果。
### Compare的返回值，1为从低往高修，0为从高往低修。
### 希望大牛提意见。
（管理。。。原来的题解改了一点点为什么就过不了了）

---

## 作者：卑微的绝望 (赞：1)

枚举用来练练手，可是第一遍居然错了，80分，很无解啊，如此之简单的题目我这个蒟蒻做不出来，看来连普及组二等奖都危险啊！！！！！！！！！！告诉大家一下，我想只要一提，都知道，是要枚举山峰高度，而我只是枚举了山的高度，看来还是考虑问题不全面，大家不要像我学习！！！！！！！

手打AC代码，不足之处请见谅：

```cpp
#include <iostream>
using namespace std;
int a[1500];
int main(){
    long long t,n,i,j,ans=0x7f7f7f7f,c;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    for(i=0;i<84;i++){
        c=0;
        t=i+17;
        for(j=1;j<=n;j++){
            if(a[j]>t){
                c+=(a[j]-t)*(a[j]-t);
            }
            else if(a[j]<i){
                c+=(i-a[j])*(i-a[j]);
            }
        }
        if(c<ans){
            ans=c;
        }
    }
    cout<<ans;
    return 0;
}
```

---

