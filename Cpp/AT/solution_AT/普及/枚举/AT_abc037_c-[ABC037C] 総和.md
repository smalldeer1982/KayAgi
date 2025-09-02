# [ABC037C] 総和

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc037/tasks/abc037_c

長さ $ N $ の数列 $ \{a_i\} $ と$ 1 $ 以上 $ N $ 以下の整数 $ K $ が与えられます。 この数列には長さ $ K $ の連続する部分列が $ N-K+1 $ 個あります。これらのそれぞれ部分列に含まれる値の合計の総和を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ 10^8 $
- $ a_i $ は整数である。

### 部分点

- 50 点分のテストケースでは、 $ N\ \leq\ 10^3 $ である。

### Sample Explanation 1

$ (1+2+4)+(2+4+8)+(4+8+16)=49 $ なので、答えは $ 49 $ です。

### Sample Explanation 2

オーバーフローに注意してください。

## 样例 #1

### 输入

```
5 3
1 2 4 8 16```

### 输出

```
49```

## 样例 #2

### 输入

```
20 10
100000000 100000000 98667799 100000000 100000000 100000000 100000000 99986657 100000000 100000000 100000000 100000000 100000000 98995577 100000000 100000000 99999876 100000000 100000000 99999999```

### 输出

```
10988865195```

# 题解

## 作者：wdcxz (赞：9)

就按照题目自己直接模拟就行了
## 但是
大佬们说会炸，神奇的是：
# 过了
### 呵呵，上代码：
```cpp
#include <iostream>//c++头文件
using namespace std;
long long n,k,a[100009],ans;//long long 确保不会超，用int 会炸
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n-k+1;i++)
        for(int j=i;j<=i+k-1;j++)//枚举所有情况，暴力出奇迹
            ans+=a[j];//加上加上
    cout<<ans<<endl;
    return 0;//end
}
//巨硬制造，慧及全球
//巨硬万岁
```
小朋友不要学坏哟！

---

## 作者：da32s1da (赞：6)

这个题当然可以用暴力做，但是我们观察一下……
```
a[i]被加的次数为min(min(i,n-i+1),min(m,n-m+1))
```
所以就OK了。
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a,b,tot;
int main(){
	cin>>n>>m;b=n-m+1;
	for(long long i=0;i^n;i++)
	cin>>a,tot+=a*(min(min(i+1,n-i),min(m,b)));
	cout<<tot<<endl;
	return 0;
}
```

---

## 作者：kingder_man (赞：4)

背景:我正在用颤抖的双手发布我人生第一篇题解

虽然这是一道红题,但我认为它应该是橙题(可能是我太蒻)

言归正传,我看了好几位大佬的题解,什么线段树......我眼中只有ORZ

这道题，~~牛逼~~蒟蒻的我用前缀和搞定。

虽然可以用暴力解决，但那终究是不太好的方法（虽然我很喜欢OwO）

所谓前缀和，就是x之前的所有的数的和；

假如有一个数列：1，2，3，4，5，6

那么，它们对应的前缀和就是：1，3，6，10，15，21

也就是说，对于一个数列：a[1]，a[2] ..... a[n-1]，a[n]

它的第x个数的前缀和为 ：a[1]+a[2]+....+a[x-1]+a[x]

第（x-1）个数的前缀和为：a[1]+a[2]+....+a[x-2]+a[x-1]

所以不难发现，第x个数的前缀和就是 a[x]+（ a[x-1]的前缀和）


------------
介绍完前缀和，我们开始正式做这道题

这道题说白了就是要求区间的值，这对前缀和来说是最实用的地方。

要想求一个区间的值，只需要将区间尾的前缀和减去区间首的前缀和就行了！

所以~~废话不多说~~，直接上代码
```cpp
#include<bits/stdc++.h>//众所周知的万能头文件

using namespace std;

long long a[100010],num[100010]={0};
 //不要忘了初始化为0(我是不会告诉你我因为没初始化WA了3次)
  
long long n,k,sum=0;
  
//以上为定义(要long long否则会爆int)

//a[]表示输入的数列,num[i]表示a[i]的前缀和;
//n,k如题,sum为最后的答案

int main()
{
	cin>>n>>k;
	for(int  i=1;i<=n;i++)//读入数列
	{
		cin>>a[i];
		num[i]=num[i-1]+a[i];//计算a[i]的前缀和
	}//预处理完毕!
	for(int i=k;i<=n;i++)//这里i从k开始循环,a[i]代表区间的末尾,num[i]代表区间末尾的前缀和
	{
		sum+=num[i]-num[i-k];
	}
	cout<<sum<<endl;//可爱地输出答案
	return 0;
}
```
大家明白了吗?

有问题的欢迎提问!(如果我有问题也欢迎指出QAQ!!!)



---

## 作者：LeeChain (赞：3)

看到dalao们都没有用线段树的，那我就来一发吧（逃）

~~很显然的区间求和~~

```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll n,k;
ll sum[N*4];
void update(int now)
{
	sum[now]=sum[now*2]+sum[now*2+1];
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		cin>>sum[now];
	//	cout<<sum[now]<<endl;
		return;
	}
	int mid=(l+r)>>1;
	build(now*2,l,mid);
	build(now*2+1,mid+1,r);
	update(now);
}
ll query(int now,int l,int r,int cl,int cr)
{
	ll ans=0;
	if(l>cr||r<cl)return 0;
	if(cl<=l&&r<=cr)
	{
		return sum[now];
	}
	int mid=(l+r)>>1;
	ans+=query(now*2,l,mid,cl,cr);
	ans+=query(now*2+1,mid+1,r,cl,cr);
	return ans;
}
ll ans;
int main()
{
	cin>>n>>k;
	build(1,1,n);
	for(int i=1;i<=n-k+1;i++)
	{
		ans+=query(1,1,n,i,i+k-1);
		//cout<<ans<<endl;
	}
	cout<<ans<<endl;
}
```

不要忘了开


**long long**

---

## 作者：cq_loves_Capoo (赞：2)

>这题用一个尺取法就可以AC了吧~
>
>不多说了，AC代码直接送上。
>
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>//头文件不解释
using namespace std;
long long n,m,sum,ans,s[111111];//一定要用long long，不然后果自负
int main(){
	scanf("%lld%lld",&n,&m);//输入（本人习惯用scanf）
	for(int i=1;i<=n;i++) scanf("%lld",&s[i]);
    //输入，不解释那么多了
	for(int i=1;i<=m;i++) sum+=s[i];
    //非常关键的第一段
	for(int i=2;i<=n-m+1;i++){//循环
		ans+=sum;//累加每段的和
		//sum=sum-s[i-1]+s[i+m-1];
        sum-=s[i-1];
        //减去前一段不重叠的那个数
        sum+=s[i+1];
        //再加上这一段的最后那个数
	}
	ans+=sum;//加上最后一段
	printf("%lld\n",ans);//输出
    return 0;//好习惯
}

```


---

## 作者：liulif (赞：2)

**看了下题解，发现我的做法跟别人还是有那么点不一样（~~虽然这题很水，虽然可能审核不会通过，但蒟蒻还是想水一篇，不要问我为什么~~）**

直接上代码：
```cpp
#include<iostream>
using namespace std;
const int maxn=1e5+5;
int n,k,a[maxn];
long long sum,ans;
int main()
{
    cin>>n>>k;
    for(int i=1;i<k;i++)
    {
        cin>>a[i];		//先输入前k-1个数，避免判断
        sum+=a[i];		//此时的sum就是前k-1项的和
    }
    for(int i=k;i<=n;i++)
    {
        cin>>a[i];		
        sum+=a[i];		//第一次执行时，sum更新为前k项的和（之后每次sum更新为连续k项的和）
        ans+=sum;		//将sum累加至答案中
        sum-=a[i-k+1];	//减去当前连续k项和的第一个数，更新为下一次连续k项和的前k-1项
    }
    cout<<ans<<endl;	//输出答案
    return 0;
}
```

---

## 作者：Violet9567 (赞：2)

可以用**简单的数论**，**o（n）**的复杂度。
就拿样例1说，你要求4,8,16的和就要把所有数的和减去1,2的和，可以的到公式**ans=sum[i]-sum[i-k]**。
 _sum[i]是前i项的和_ ， _sum[i-k]是前i-k项的和_ ，前提是要i-k大于等于0，最后把ans加起来就可以了
代码如下：
```cpp
#include<iostream>//头文件
using  namespace std;
const int N=1e5+1;
long long sum[N];
int main()
{
	int n,k;
	cin>>n>>k;
	long long ans=0;
	for(int i=1;i<=n;++i)
	{
		int c=0;
		cin>>c;
		sum[i]=sum[i-1]+c; 
		if(i-k>=0)
			ans+=sum[i]-sum[i-k];//利用公式得出答案
	}
	cout<<ans;
	return 0;
｝
```

---

## 作者：迷残云 (赞：1)

连线段树都有了，树状数组怎么不来一波呢

~~一道入门题被玩成这个样子好么~~


~~好，既然第一次被打回来，那我就交第二次
~~

好，于是我们~~愉快的~~来讲一下树状数组。

树状数组是一种支持单点修改区间查询的数据结构，实际上它也能支持区间修改，但是要用到差分，~~还不如码线段树~~。

基本思想：，区间$ [1,x] $可以被分为$ O(logx) $ 个小区间。

e.g：

1. 长度为$ 2^4 $的区间$[1, $   $ 2^4]$

2. 长度为 $ 2^2 $的小区间$[2^4+1,2^4+2^2]$

3.长度为$ 2^0 $的小区间 $[2^4+2^2+1 ,2^4+2^2+2^0]$

于是：~~不~~显然的我们得到一个二进制的 $ lowbit $函数，如下代码：

##### 单点修改

就是从下往上找父亲，代码：

```cpp
void update(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
	   c[i]+=v;
}
```
时间复杂度$ O(logN) $

##### 前缀和查询

从上往下累加一个叫 $ c[x] $数组和它子孙的和

时间复杂度同上

代码：
```cpp
int sum(int x)
{
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i))
	    sum+=c[i];
	return  sum;
}
```


##### 区间查询
类似于前缀和的思想，区间查询就是$ [l,r] $中前 $ r $个数的前缀和$ - $前$ l-1 $个数的前缀和

注意，前$ l-1 !!$


最后：


## 记住！！

**AT的题一定要换行换行换行**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int c[maxn];
int n,q;
int  lowbit(int x)
{
    return x&(-x);
}
//单点更新
void update(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
	   c[i]+=v;
}
//求前缀和1-x
```cpp
int sum(int x)
{
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i))
	    sum+=c[i];
	return  sum;
}
//求区间和
int query(int x,int y)
{
	return sum(y)-sum(x-1);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		update(i,a[i]);
}
	int ans=0;
	for(int i=1;i<=n-q+1;i++)
    {
    	ans+=query(i,i+q-1);
			//printf("%lld\n",query(i,i+q-1));
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：wushuang0828 (赞：1)

#### **我的奇葩思路**

Pascal的AC代码：
```pascal
var
 n,k,i,j:longint;
 s,ss:int64;
 a:array[0..100001] of longint;
begin
 readln(n,k);
 for i:=1 to k do//先输入前k个数
  begin
   read(a[i]);
   s:=s+a[i];//将前k个数加起来
  end;
 j:=1;
 ss:=s;
 for i:=k+1 to n do//输入剩下的数
  begin
   read(a[i]);
   ss:=ss-a[j]+a[i];
   //可能不好理解，例：原来是1~k这一段，现在j=1,ss-a[j]就等于2~k，
   //i=k+1，加上a[i]，ss就等于2~k+1
   s:=s+ss;//s再加上新的一段
   inc(j);//累加j，就等于j:=j+1;
  end;
 writeln(s);//输出
end.
```

---

## 作者：珅肐 (赞：1)

就是一道模拟
但是直接模拟绝对跑不过

加一点优化，不然会炸
#### 代码：
```c
#include<iostream>
using namespace std;
int n,k,a;
long long sum,ans[100007];//ans数组前缀和，计算从一到i的和
//注意数据范围,一定要开long long，不然死的很惨
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i)
    {
    	cin>>a;
        ans[i]=ans[i-1]+a;
    }
    //因为输入的数只在前缀和用一次，我就没有保存，节省空间
	for(int i=k;i<=n;++i)
    	sum+=ans[i]-ans[i-k];//累加和
	cout<<sum<<endl;//现在的ATCoder好像不用加恶心的回车也能过了
	return 0; //好习惯
}
```

---

## 作者：Hola_chen (赞：1)

# 非喜勿喷
```cpp

#include<bits/stdc++.h>//万能头 
using namespace std;
int a[100001];
int main()
{
    int n,k;//赋值 
    cin>>n>>k;//输入n和k 
    for(int i=1;i<=n;i++)//for循环从1到n 
    {
    	cin>>a[i];//输入一组数据 
	}
	long long sum=0;//sum要longlong，不然会爆！ 
	for(int i=1;i<=n-k+1;i++)//for循环从1到n-k+1，防止加到空的数据 
	{
		int j;//赋值j，统计数字 
		j=i;//j每次从i开始 
		while(j<k+i)//while循环取k得区间 
		{
			sum=sum+a[j];//sum把区间内的数字加上 
			j++;//j要加加 
		}
	}
	cout<<sum<<endl;//输出sum并且换行 
    return 0;//清零，退出 
}


```


---

