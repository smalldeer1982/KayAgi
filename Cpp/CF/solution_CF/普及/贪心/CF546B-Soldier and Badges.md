# Soldier and Badges

## 题目描述

Colonel has $ n $ badges. He wants to give one badge to every of his $ n $ soldiers. Each badge has a coolness factor, which shows how much it's owner reached. Coolness factor can be increased by one for the cost of one coin.

For every pair of soldiers one of them should get a badge with strictly higher factor than the second one. Exact values of their factors aren't important, they just need to have distinct factors.

Colonel knows, which soldier is supposed to get which badge initially, but there is a problem. Some of badges may have the same factor of coolness. Help him and calculate how much money has to be paid for making all badges have different factors of coolness.

## 说明/提示

In first sample test we can increase factor of first badge by $ 1 $ .

In second sample test we can increase factors of the second and the third badge by $ 1 $ .

## 样例 #1

### 输入

```
4
1 3 1 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 2 3 2 5
```

### 输出

```
2```

# 题解

## 作者：test_check (赞：7)

[$\huge CF546B  \ Soldier  \ and  \ Badges$](https://www.luogu.org/problem/CF546B)   
这道题看到许多大佬使用了```sort```，十分高端，本蒟蒻表示$\%\%\%$，但是，我们还可以用一种更快也更容易想到的方法解决这道题。所以，本题解就来介绍这种方法来$A$了这道题。

------------
$$First:\text{数据存储}$$
本题解使用的这种方法的思想可以被近似的看成**桶排序**。   
我们建一个数组为原数组，就是要输入的数组，不妨设为$a[]$，因为题目中的数据要求是$(1 \leq n \leq 3000)$,所以，$a[]$数组大小应该是$a[3005]$。   
我们再设一个类似于**桶**的数组，即$flag[]$，**$flag$数组的作用是统计某个数出现的次数** ，题目又规定$(1 \leq a_i \leq n)$,所以，**（注意了,** **注意了,** **注意了）** 这里$flag$数组的大小应设为$n$的$2$倍，为什么呢？应为$flag$数组的作用是统计某个数出现的次数，而题目又规定每进行一次操作可以将一个数$+1$,而我们考虑最差的情况，就是$n$为最大，即$3000$,而每一个数$a_i$又都是跟$n$一样的，此时，数$a_i$最大为$6000$,所以，$flag$数组应成跟$n \times 2$这么大，即开成$flag[6001]$。    
~~如果你一意孤行，$flag[]$坚持开成$3000$，那么，你将会得到一个完美的结果~~：$\colorbox{purple}{\color{white}RE}$.   
至于代码实现十分简单，如下：
```cpp
int n,flag[6001],a[6001];   //a[]是要输入的数组，flag[]为桶
cin>>n;
for(int i=1;i<=n;i++)
{
    cin>>a[i];  //输入
    flag[a[i]]++;  //桶中每个元素出现的次数++
}
```    
好了，就此，我们把数据存储的问题解决了，接下来，我们再来实际解决问题。$(QAQ)$。

------------
$$Second:\text{正式解决问题}$$
其实本题通过简单的枚举就可以做出来了，枚举的范围应该为$n \times 2$，至于原因前文已经阐述过了，原因和前面一样，为了考虑最差的情况吗。其他解释都在$code$里，自己慢慢查看$qwq$,(其中$sum$的含义是要进行几次操作）
```cpp
    for(int i=1;i<=n*2;i++)  //开始枚举
    {
        if(flag[i]>1)  //又两个及以上元素
        {
            flag[i+1]+=(flag[i]-1);//多了几个数就下一个桶就加几
            sum+=(flag[i]-1);  //多了几个数就要进行几次操作
            flag[i]=1;  //清除多余的次数
        }
    }
```    


------------
好了，本题解就结束了，希望大家都明白了该算法的精妙之处并会灵活运用，(关键还是要理解算法的思想），下面给出完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,flag[6001],a[6001],sum=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        flag[a[i]]++;
    }
    for(int i=1;i<=n*2;i++)
    {
        if(flag[i]>1)
        {
            flag[i+1]+=(flag[i]-1);
            sum+=(flag[i]-1);
            flag[i]=1;
        }
    }
    cout<<sum;
    return 0;
}
```

---

## 作者：tryrtj (赞：3)

这题不要想麻烦了，第一个发题解的大佬说复杂了点，其实只需要一个sort就可以搞定了

首先，只能向上加，那么最后最小的一定是开始时最小的，那么我们就可以先把它排下序，然后在从前向后找，可能会有相邻的相等的情况，那么我们需要一个变量来表示这个位置所需的最小值，再一减就可以算出来了。

代码如下

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[3005];//存数
int main(){
	int n;
	int zong=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n);//排序
	int q=a[0];//找出最小值
	for(int i=1;i<n;i++){
		if(a[i]>q){//
			q=a[i];//如果递增则改变变量值
		}
		else {
			zong+=q+1-a[i];//计数器增加
			q++;//变量更改
		}
	}
	cout<<zong;//输出最少的次数
	return 0;//已经蛮短了，建议自己再敲一遍代码
}//by tryrtj
```

---

## 作者：ShaeKnight (赞：1)

## 思路分析

我看别的大佬基本上都是用类似桶排序的思想

这里我给大家开拓一下思维

既然每个数要都不一样，那就把一样的数加上一个

排序后进行处理，有相同的数就$ a[i]++ $,并同时累加$cnt$

最后双循环结束后的$cnt$即为答案

### 代码部分
```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cctype>
using std::sort;  //要用到sort
#define ll long long
#define fr(c,a,b) for(int c=a;c<=b;c++)
#define rf(c,a,b) for(int c=a;c>=b;c--)
int max(int x,int y){return x>y?x:y;}
int min(int x,int y){return x<y?x:y;}
int abs(int x){return x>0?x:-x;}
const int Max=1e6;
const int Min=-1;
inline int read()
{
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
inline void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}                //快读快写不解释
int n=read(),a[30005],cnt;
int main()
{
	fr(i,1,n)a[i]=read();//读入
	sort(a+1,a+1+n);     //排序
	fr(i,1,n-1)
		fr(j,i+1,n)      //注意,从i+1开始循环，不然cnt会比正确答案大
		{
			if(a[j]==a[i])a[j]++,cnt++; 
                   //前后相同时 把后面的数++，同时计数++
		}
	write(cnt);         //输出
	returm 0;
}
```
### 珍爱生命 远离抄袭

---

## 作者：yu__xuan (赞：1)

### 题目
[CF546B Soldier and Badges](https://www.luogu.org/problem/CF546B)

### 思路

贪心。

贪心策略：从 $1 \sim n$ 一个一个加。

如果 $a$ 在这个序列中出现了多次($k$次)，我们就让其变为 $a,a+1,a+2,...,a+k-1$ ,这样操作一次的花费为：
$$\large\sum_{i=1}^{k} i$$
sigma函数就是来求这个的。

流程：读入的时候记下每个数出现的次数，然后从$1\sim maxx \text{(读入时出现的最大的数)}$遍历然后进行上面的操作。进行上面的操作后 $a+1,a+2,...,a+k-1$ 出现的次数要加一


### $Code$
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,a[3001],cnt[60002];

int sigma(int x) {
	int ans=0;
	for(int i=1;i<=x;++i) ans+=i;
	return ans;
}

int main() {
	read(n);
	int maxx=0,ans=0;
	for(int i=1;i<=n;++i) {
		read(a[i]);++cnt[a[i]];
		if(a[i]>maxx) maxx=a[i];
	}
	for(int i=1;i<=maxx;++i) {
		if(cnt[i]>1) {
			int ad=cnt[i]-1;ans+=sigma(ad);
			if(i+ad>maxx) maxx=i+ad;
			for(int j=i+1;j<=i+ad;++j) ++cnt[j];
		}
	}
	std::cout<<ans<<'\n';
	return 0;
}
```
讲的不好请感性理解，也可以发评论问。

---

## 作者：xiaoyao (赞：1)

## 论这个@！#%￥&*&*的题目
话说其实这个~~东东~~
~~（不对应该叫题目~~

##### **~~不难~~**

好了当我什么也没说。。。

因为是使这n个数互不相同，最少的操作步数

 呐比如我们可以把
####  每个数出现的次数都存到一个计数的数组里去####

~~（类似计数排序？~~

#### 如果次数大于1就再建一个循环，把多出来的数分别加一，然后下一个计数数组再加一，以此类推……

#### 菜鸟的我胡乱搞了几行程序（？？

~~（时间复杂度貌似蛮高的？~~

 ~~好吧那不是重点~~

  ~~毕竟我还是个弱鸡~~
  
####  下面附上超水的AC代码。。。
```
#include<iostream>
using namespace std;
int n,i,j,a[3001],b[10001]={0},s=0;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;  //计数
	}
	for(i=1;i<=10000;i++)  //天知道我之前设小了，结果一大堆的AC，最后……WA。。事实证明数组设大一点只要不超空间总没毛病
	{
		if(b[i]>1)  //如果有数据重复
		{
			int t=b[i];
			for(j=1;j<=t-1;j++)  //把多于1的数据都+1
			{
				b[i]--;
				b[i+1]++;
				s++;  //记录+1的次数
			}
		}
	}
	cout<<s;
	return 0;
}
```
本人一只~~蒟蒻~~，望见谅~~

---

## 作者：yuangq (赞：1)

这题就是一个简单的模拟

~~~
#include<bits/stdc++.h>
using namespace std;
int a[4000],s;
int main()
{
	int n;
	cin>>n;
	
	for(int i=0;i<n;i++)
	{
		cin>>a[i];//输入 
	}
	sort(a,a+n);//从小到大排序 
	for(int i=1;i<n;i++)
	{
		if(a[i]<=a[i-1])//如果不符合条件 
		{
			s=s+a[i-1]-a[i]+1;//就将它补到a[i]+1 
			a[i]=a[i-1]+1;
		}
	}
	cout<<s;
	return 0;
}
~~~

---

## 作者：Shikita (赞：1)

# 题目大意
就是为了让每个勋章都不一样，那么可以从头开始慢慢往后推，记录下变化前和变化之后的总和，两者相减就是答案
## 代码
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
int n;
int a[3005];
int sum1=0,sum2=0;
int main()
{
    n=read();
    int sum1=0,sum2=0;
    for(int i=1;i<=n; ++i)
    {
        a[i]=read();
        sum1+=a[i];//先记录下变化之前的总和
    }
    sort(a+1,a+1+n);//排序
    sum2=a[1];
    for(int i=2;i<=n;++i)
    {
        if(a[i]==a[i-1]) a[i]++;//往后爬
        else if(a[i]<a[i-1])//如果出现逆序对
        a[i]+=(a[i-1]-a[i])+1;//那么就把当前这个变为之前那个+1
        sum2+=a[i];//再次总和
    }
    cout<<sum2-sum1;
}
```
就上面代码已经很清楚了，如果有看不懂的就继续下拉




假设出现了几个个相同的值 a,b,c,d
当前的i指向b;

那么b++

当做到c时发现了逆序对

那么就要让自己往后走

至少+1

这就是这个代码的意思
```
if(a[i]==a[i-1]) a[i]++;//往后爬
else if(a[i]<a[i-1])//如果出现逆序对
a[i]+=(a[i-1]-a[i])+1;//那么就把当前这个变为之前那个+1
  ```


---

## 作者：wangjunze (赞：1)

本~~蒟蒻~~第2次发题解，还请大佬们多多指点
话说这道题不难，按题意举个例子
###
**for example**：
4    **1 2 1 3**（4是个数）
思路：先把1 2 1 3扔进vector<int> v里，在sort一下，变成1 1 2 3，再把每一个数和他后面的一个进行比较，如果这个数一个大于等于（一定要大于等于，否则有些情况下会出错）他后面的那个，后一个数就加上那个数与后一个数的差+1，在例子中有两个1在一起，就用1（后一个）+1（前一个）-1（后一个）+1，那么整个v就变成了1 2 2 3······（省略之后的步骤）
  话说了这么多了，上代码
  

------------

  ```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int ans=0;
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		int a;
		cin>>a;
		v.push_back(a);
	}
	sort(v.begin(),v.end());
	vector<int> pre;
	for(int i=0;i<v.size();i++)
	{
		pre.push_back(v[i]);//储存一下未处理的数组，以便比较
	}
	for(int i=0;i<v.size();i++)
	{
		if(v[i]>=v[i+1])
		{
			v[i+1]+=v[i]-v[i+1]+1;
		}
	}
	int cnt1=0;
	int cnt2=0;
	for(int i=0;i<v.size();i++)
	{
		cnt1+=v[i];//本蒟蒻用两个cnt记录变前和变后的数值
		cnt2+=pre[i];
	}
	ans=cnt1-cnt2;//在用处理后的减去处理前的，就是你加上的数值
	cout<<ans;
	return 0;
 } 
```


------------

（纯c++）
其实可以不用记录差值，但本~~蒟蒻太菜~~，只好为了AC写的笨了点，勿喷。




---

## 作者：Terrific_Year (赞：0)

# [CF546B](https://www.luogu.com.cn/problem/CF546B)

这其实很简单，一个桶排解决。

为什么呢？

因为如果发现有相同的数，就让它只剩下这一个，也就是把其他的放到后一个没有数的桶里，然后下一个有检查一下。

附上$AC$ $Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[10000],j,i;//a为桶
long long s;//s为答案
int main(){
	cin>>n;
	int max=0;//最大值
	for(i=0;i<n;i++){
		cin>>t;
		a[t]++;//当前数的个数增加
		if(t>max)max=t;//更新最大值
	}
	for(i=1;i<=max;i++)
		while(a[i]>1){
			if(i>j)j=i+1;
			while(a[j]>0)j++;//找到可以不同的
			a[j]++;//移过去
			s=s+j-i;//答案加
			a[i]--;//少一个数
		}
	cout<<s;//输出答案
	return 0;//完美AC
}
```

---

## 作者：Randolph、 (赞：0)

## [CF546B Soldier and Badges](https://www.luogu.org/problem/CF546B)

简单的贪心qwq

排个序，如果当前数与之前的数相重，已经用过，则加到一个之前没有用过的数

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,ans,a[3005];
int main() {
	scanf("%d",&n);
	for (int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a,a+n);
	for (int i=1,last=a[0]; i<n; i++)
		if (a[i]>last) last=a[i];
		else ans+=last-a[i]+1,last++;
	printf("%d",ans);
}
```

---

