# Trees

## 题目描述

On Bertown's main street $ n $ trees are growing, the tree number $ i $ has the height of $ a_{i} $ meters ( $ 1<=i<=n $ ). By the arrival of the President of Berland these trees were decided to be changed so that their heights formed a beautiful sequence. This means that the heights of trees on ends (the $ 1 $ st one and the $ n $ -th one) should be equal to each other, the heights of the $ 2 $ -nd and the $ (n-1) $ -th tree must also be equal to each other, at that the height of the $ 2 $ -nd tree should be larger than the height of the first tree by $ 1 $ , and so on. In other words, the heights of the trees, standing at equal distance from the edge (of one end of the sequence) must be equal to each other, and with the increasing of the distance from the edge by $ 1 $ the tree height must also increase by $ 1 $ . For example, the sequences "2 3 4 5 5 4 3 2" and "1 2 3 2 1" are beautiful, and '1 3 3 1" and "1 2 3 1" are not.

Changing the height of a tree is a very expensive operation, using advanced technologies invented by Berland scientists. In one operation you can choose any tree and change its height to any number, either increase or decrease. Note that even after the change the height should remain a positive integer, i. e, it can't be less than or equal to zero. Identify the smallest number of changes of the trees' height needed for the sequence of their heights to become beautiful.

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 2 2 1
```

### 输出

```
0
```

# 题解

## 作者：Tune_ (赞：18)

这题呢，其实不难，关键是思路要对。

想最少改多少不方便，那我们就反过来想，算最多不改多少。

我们将数位编号，第i位如果是左半边，编号为i，如果是右半边，编号为n-i+1。

例子如下：

一个beautiful的数列：2 3 4 4 3 2

将它的数与数位编号对齐，是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/pv5nahk3.png)

不难发现，一个beautiful的数列，每一位上的数字和编号的差都相等，可以用这个规律判断。

判断每个数，算出这个数与编号的差，用桶记录每种差的个数，找最大的，以这种差为标准造beautiful数列时，修改的数最少。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int a,n,t[100005],s=0; //t记录每种差的个数
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		a-=min(i,n-i+1);//算差
		if(a>=0)//小于0就一定要改
		{
			t[a]++;//这种差的多一个
			s=max(s,t[a]);//更新答案
		}
	}
	cout<<n-s;//因为算的是不改的，所以要用n减。
	return 0;//拜了个拜~
}

```
走过路过，点个赞鸭~

QWQ

---

## 作者：_HCl_ (赞：5)

# CF58C Trees题解

这道题似乎与Tree没什么关系.....

[CF58C Trees](https://www.luogu.com.cn/problem/CF58C)

**题意简述**

给定一个序列，问修改其中几个值能使序列回文且左半部分为连续递增的的正整数

**思路**

这里有几个关键点：

- 回文
- 递增
- 连续
- 正整数

构造符合要求的最简单的序列，比如 $[1,2,1]$，$[1,2,3,2,1]$ 等。这些以1开头的序列我们把它称之为“简单序列”。

我们可以把简单序列中的每一个数都加上一个 $d$，原序列又会变成一个新的序列。而新的序列也是符合要求的。

这时，我们就可以得出一个重要的结论：

**任意一个符合要求的序列和与其长度相等的简单序列的每一位数差值相等。**

举个栗子：
![](https://cdn.luogu.com.cn/upload/image_hosting/9q07okod.png)


现在我们再回到题目。题目让我们回答最小的修改个数，而这个问题就等价于最多的不变的个数。

再看看刚刚得出的结论，那些数是不需要变的呢？假设我们已经知道了差值 $d$，那么不变的数就是这个数和简单序列中对应的数差值已经是 $d$ 的数。

但是最终这个 $d$ 还是自己定的，因为我们要让不变的数最多，所以 $d$ 就是所有差值的众数（所有差值中最多的一个）。而不用修改的数量就是众数的出现次数。

下面，就可以开始思考如何实现了。

**实现**

大概又这么几个步骤：

1. 读入
1. 构造长度为 $n$ 的简单序列
1. 计算差值
1. 找出差值众数和众数的出现次数
1. 输出

其中，构造简单序列的这一步可以简化。简单序列的第 $i$ 位就是  $\min(i,n-i+1)$。

3和4可以合并，用桶去储存该差值的数量， 桶中的数大于 $maxn$ 时就更新 $maxn$。

最后，因为 $manx$ 储存的是不用修改的数量，所以输出 $n-maxn$。

另外，当差值为负数时直接跳过，因为题目要求是正整数。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000001],b[100001],c[100001];
int cnt,maxn;
int main()
{
	cin>>n;//读入
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];//读入
	}
	for(int i=1;i<=n;++i)
	{
		//min(i,n-i+1)是简单序列第i位值
		if(a[i]-min(i,n-i+1)<0)continue;//如果差值是负数，直接跳过
		c[a[i]-min(i,n-i+1)]++;//将桶中的数量增加
		if(c[a[i]-min(i,n-i+1)]>maxn)//如果桶中的数量大于maxn
		{
			maxn=c[a[i]-min(i,n-i+1)];//更新
		}
	}
	cout<<n-maxn;//输出
}
```


---

## 作者：墨舞灵纯 (赞：5)

一道非常巧妙的题，运用逆向思维（居然没人写题解）

题目求$\color{red}\small\text{最少}$修改多少，那么我们就反着想$\color{red}\small\text{最多}$不修改多少。每次只要计算一下需要改成的值，并把个数用桶记一下，取最大值就行了。

$\color{lightgreen}\text{Code:}$

```
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1000005;
int a[N],n,x,ans; 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		x-=min(i,n-i+1);
		if(x>=0)
		{
			++a[x];
			ans=max(ans,a[x]);
		}
	}
	printf("%d",n-ans);
	return 0;
}

```

---

## 作者：櫻尘ིོི༹ (赞：1)

#### 找了半天，就看到这道题比较有意思，应该就是个规律题

**Part 1 分析**

由题，可得一二组样例是这样的：


$$2 2 2\Longrightarrow 2 3 2$$


$$1 2 2 1 \Longrightarrow 1 2 2 1$$

第二组样例不需分析，我们来康康第一组

当我们把下标，按回文的方式序列下后：

$$ 2 2 2 \Longrightarrow 2 3 2$$
$$1 2 1 \Longrightarrow 1 2 1$$

不难发现，在变为指定序列后，每一项的数字和下标的差相等

所以易得：找寻原序列数字与下标的差相同最多的差，所有为这个差的数字不需改变，其他的全都改变。由此可得最优解。

**Part 2 Code**

```
#include<bits/stdc++.h>
using namespace std;
int n,ans; 
int num[100005],a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int sum=min(i,n-i+1);//下标 
		if(a[i]-sum<0){//若序列差小于0，则不管 
			continue;
		}else{//否则将为这个差的数目加1，并同时算最大值 
			num[a[i]-sum]++;
			ans=max(ans,num[a[i]-sum]);
		}
	}
	cout<<n-ans;
	return 0;
}
```




---

## 作者：linyinuo2008 (赞：1)

好久没写了，看见这道思想不错的题，我写来记一下自己的心得。

这道题并没有用编程里面什么重要的算法，但是用了数学以及其他领域很重要的一个思想————逆向思维。

既然这道题要求我们求最少修改几个数，我们到不如把思维倒过来想一下，改成求最多不修改几个数（本人也是一开始找求最少改几个数，结果找不着规律）。

所以我们**每次输入时求差值最多，判断一下是否是负数。** 再拿一个桶来记录最大值就可以啦。

PS：不会就多模拟几遍，做这种题就得靠纸笔来模拟。

下面贴上代码：

```cpp
#include <iostream>
using namespace std;
const int maxn=1e5+1;
int maxndele,a,bucket[maxn],n;
int min(int a,int b){
	return a<b?a:b;
}
int max(int a,int b){
	return a>b?a:b; 
}
//自己写min max函数，更快
int main()
{
	int i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a;
		a-=min(i,n-i+1);
		if(a>=0)
		{
			bucket[a]++;
			maxndele=max(maxndele,bucket[a]);//更新最大值
		}
	}
	cout<<n-maxndele;//由于是不更改的，所以要拿n减去。
	return 0;
}
```
管理员大大求通过！

## 若有错误，欢迎指出！



---

## 作者：Aya_tt (赞：0)

这题问的是最少修改几次，我们不妨想想最多有几个不需要修改。


假定有一个序列 $3$，$4$，$5$，$4$，$3$，很明显，聪明的你一定发现这是一个美丽的序列，我们可以得出两个规律，前半部分单调递增，之后就是单调递减，而且关于中心对称，由此我们可以看出第二个规律，不妨让下标变成 $1$，$2$，$3$，$2$，$1$，就会发现序列的每个数和他的坐标的差相等，表示下标的方法也非常的简单，前半部分就是 $i$,后半部分就是 $n-i+1$,取他们的最小值判断一下就好了。

然后用 $cnt$ 数组统计一下数，用 $ans$ 保存一下最大值，别忘了，输出 $n-ans$，因为我们统计的是最多有几个不需要修改。

代码如下：

```c
#include<bits/stdc++.h>
using namespace std;
int n,cnt[100005],ans;
int main(){
    cin>>n;
    for(int i = 1;i <= n;i++){
        int k;
        cin>>k;
        int m = min(i , n - i + 1);//我们新建的下表
        k -= m;
        if(k < 0) continue; 
        cnt[k]++;//统计
        ans = max(ans,cnt[k]);//找最大的
    }
    cout<<n-ans;
}
```


---

## 作者：fuzhelin1984 (赞：0)

## 题意

给你一个长度为 $ n $ 的序列，现在需要通过更改最少的元素，来使这个序列满足：回文且它的左边一半是连续递增的正整数。

## 思路

可以根据原序列构造一个形如 $ 1 $ $ 2 $ $ 3 $ $ 2 $ $ 1 $ 的序列，求出各个元素与其对应位置的差，然后进行桶排。这里特别注意，如果减出的差为负，这个结果不可取，题目要求构造的序列中的元素全部为正整数。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 114514;
int a[N];
signed main()
{	
	int n,k,ans = 0;
	scanf("%lld",&n);
	for(int i = 1;i <= n;++i)
	{
		scanf("%lld",&k);
		k -= min(n-i+1,i);//理想序列的通项公式
		if(k >= 0)
		{
			a[k]++;
			ans = max(ans,a[k]);//桶排
		}
	}
	return cout<<n-ans,0;//总数减去一致部分得出结果
}

```




---

## 作者：hanyipu1414 (赞：0)

# 一、题意
称一个序列是美丽的当且仅当：

1. 它是回文的。
2. 它的左边一半是连续递增的正整数。

给定一个长为 $n$ 的序列，问至少修改几个数可以使它变成美丽的。
# 二、思路
我们可以先构造一个长度为 $n$ 且从 $1$ 开始，每两项之间的差为 $1$ 的回文数列。不难发现，这个数列与符合要求的数列的每一项的差相等。

所以我们可以先构造一个长度为 $n$ 且从 $1$ 开始，每两项之间的差为 $1$ 的回文数列，并与给出的数列的对应项做差。然后桶排找出答案就可以了。
# 三、Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=114514;
int n,a[maxn],b[maxn],c[maxn];
signed main()
{
	cin>>n;
   int i,j;
	for(i=1,j=n;i<=n/2;i++,j--) b[i]=i,b[j]=i;
	if(n%2==1) b[n/2+n%2]=i;//22-23:构造标准数列
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) c[a[i]-b[i]]++;
	sort(c,c+n);//桶排序找出不用调整的数
	cout<<n-c[maxn-1]<<"\n";//最后输出就行了
	return 0;
}
```


---

## 作者：wangyixuan_s_father (赞：0)

## CF58C题解
#### 题意
给一个正整数列，求改动多少数才能使整个数列回文且前半部分严格递增。
#### 思路
首先，暴力肯定不行 ~~伤心~~，要用其他方法使不改动的数的个数最大。

这样，就肯定能找到一个第一个数为 $1$ 的符合要求的模板数列（如 $121$，$1221$ 等）。然后就能用原数列中每一个数减去模板数列对应位置的数，再把差桶排后用 $n$ 减去最大值输出即可。

备注：因为要求正整数列，所以 $1$ 打头的一定是符合要求的最小数列，所以如果有数比对应的模板数都小就一定要改。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[100001],b[100001];
int main() 
{
	cin>>n;
	x=n/2;//前半和后半的分隔线
	for(int i=1;i<=x;i++)//上半部分
	{
		cin>>b[i];
		if(b[i]>=i)a[b[i]-i]++;//简单亲民的桶排
	}
	if(n%2!=0)//奇数个数的特殊处理
	{
		cin>>b[++x];
		if(b[x]>=x)a[b[x]-x]++;
	}
	int y;
	for(int i=x+1;i<=n;i++)//下半部分
	{
		cin>>b[i];
		y=n-i+1;
		if(b[i]>=y)a[b[i]-y]++;//又一个桶排
	}
	sort(a,a+100000+1,greater<int>());
	cout<<n-a[0];
	return 0;//完结撒花
}
```


---

## 作者：zythonc (赞：0)

~~这题顶多黄题水平吧~~

先来梳理基本思路：

- 两边（因为回文，即对称）都是**连续递增**的**正**整数。

被卡住的同学可以试试下面这组数据：

```
in
5
1 1 2 1 1
```
```
out
3
```
~~我就被卡了几次。~~

考虑要求连续递增，我们发现我们输入的数据的下标也是连续递增的（因为对称，下标超过$n$的一半我们默认减去一半）。

这也就是说在完美情况下（即输出为0的情况下）下标与每个数据差值一定。

所以我们统计哪个差值出现次数最多，特判一下负数即可。

差值最多相当于不用修改的最多，而题目要求输出**最少修改数**，所以要用$n$减去

下面是完整代码（$map$用不用都行）。
```
#include<iostream>
#include<map>
using namespace std;
int n,a[100001],ans,i2;
map<int,int>b;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		i2=i;
		if(i2>(n/2+n%2))
			i2=n-i2+1;
		if(a[i]<i2) continue;
		b[a[i]-i2]+=1;
		ans=max(ans,b[a[i]-i2]);
	}
	cout<<n-ans;
}
```

---

