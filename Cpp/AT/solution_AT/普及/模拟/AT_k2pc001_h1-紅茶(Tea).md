# 紅茶(Tea)

## 题目描述

一天，$\mathrm{kagamiz}$ 一边喝红茶，一边尝试解答如下的问题：

当由两个正整数所组成的正整数组以如下方式排列时，$(m,n)$ 是这个数列里的第几组？

$$(1,1),(2,1),(1,2),(3,1),(2,2),(1,3),(4,1),(3,2),(2,3),(1,4),(5,1),\cdots$$

这个问题对他来说太简单了，所以他更深入地考虑了以下这个问题：

当上述数列中的 $i$ 个组为 $(a_i,b_i)$，第 $j$ 个组为 $(a_j,b_j)$ 时，$(a_i+a_j,b_i+b_j)$ 是这个数列里的第几组？

你的任务就是帮助他解答这个问题。

## 说明/提示

对于所有测试数据，$1\leq i,j\leq10^8$，且 $i,j$ 可能相等。

# 题解

## 作者：hjfjwl (赞：8)

这是一道简单的找规律的题目，我们可以把它们按照它们的和进行分组，就会发现第 $i$ 个数对是整个序列的第 $b_i + \sum_{j = 1}^{a_i + b_i - 2}{j}$ 个，它的 $b_i$ 就是它在这组的第几个，它的 $a_i$ 就是它所在的组数 $+ 1 - a_i$。我们可以通过枚举题目中的第 $i$ 个数和第 $j$ 个数分别是什么。
```cpp
//求出第i个数的a[i]和b[i]
for(int k = 1;k;k++)//枚举组数
{
	a+=k;
	if(a >= i)//当a大于i是i就在第k组
	{
		ta = k;//存一下它所在的组数
		break;
	}
}
a -= ta;//除了这组外的前面的个数和
int d = i - a;
int c = 1 + ta - d;
```
算出 $a_i,b_i,a_j,b_j$，新的数对 $k$ 的 $a_k = a_i + a_j$ 和 $b_k = b_i + b_j$，数对 $k$ 就是第 $\sum_{z = 1}^{a_k + b_k - 2}{z} + b_k$ 个。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int tt,ttt;
	cin >> tt >> ttt;
	int a = 0,b = 0;//除去它所在的组外的个数
	int ta = 0,tb = 0;//存储它们在第几组
	for(int k = 1;k;k++)//枚举组数
	{
		a+=k;
		if(a >= tt)
		{
			ta = k;
			break;
		}
	}
	for(int k = 1;k;k++)
	{
		b += k;
		if(b >= ttt)
		{
			tb = k;
			break;
		}
	}
	a -= ta;
	b -= tb;
	int d = tt - a;//b[i]
	int c = 1 + ta - d;//a[i]
	int f = ttt - b;//b[j]
	int e = 1 + tb - f;//a[j]
	c += e;
	d += f;
	int cnt = 0;
	for(int k = 1;k < c + d - 1;k++)
	{
		cnt += k;
	}
	cnt += d;
	cout << cnt << endl;//结果
	return 0;
}

```

---

## 作者：Eismcs (赞：5)

找规律的题，尽量不死推。

我们在找一个数对是第几个时，可以运用他们的和来分组，这样即可得到规律，第n组也就有n个元素。这样快一点，不用一个个模拟。
而每个数对的第二个数就是它在本组的序号。

下面是蒟蒻的AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int j,k,s=0;
void acd(int z){
	int i=2,t=1;
    //i为本组的和，t为本组的第二个数，也就是这个数对在本组的序号。
	while(z>1){
		t++;
		if(i<=t){
		i++;t=1;}
		z--;
	}
	j=i-t,k=t;
	return;
}//模拟，用于找第几个的两个数。
int main(){
	int x,y,a,b,c,d;
	cin>>x>>y;
	acd(x);
	a=j,b=k;
	acd(y);
	c=j,d=k;
	a+=c;
	b+=d;
	for(int i=1;i<a+b-1;i++){
		s+=i;
	}//算出这个数对的组的前面有多少个元素。
	cout<<s+b<<endl;//加上它在本组的序号
}
```

---

## 作者：Le_Saint_Chevalier (赞：1)

# 参考题目：[P1014 Cantor 表](https://www.luogu.com.cn/problem/P1014)
题目中给的表不太好看，这里解释一下：
其实就是**倒过来的 Cantor 表**。注意，不是原本的 Cantor 表，也就是说，不需要判断是否为奇偶行，直接模拟即可。


```cpp
(1,1)
(2,1),(1,2)
(3,1),(2,2),(1,3)
(4,1),(3,2),(2,3),(1,4)
(5,1),(4,2),(3,3),(2,4),(1,5)
```

可以发现规律：**每行的数对个数等于每个数对中两个元素的和减一，也等于当前行的编号,而 $y$ 则为当前数对所在列数。**


运用这个规律，可以写出如下代码：


```cpp
	while (n - ans > 0)
    	{//ans 为当前行数
		n -= ans;
		ans++;
	}
    	ans++;
    	b = n;
    	a = ans - n;
    	ans = 1;//请手推
```

这段代码用于确定 $(a_i,b_i)$ 和 $(a_j,b_j)$。分别求出上述两者后,再求出题目要求的 $(a_i+b_i,a_j+b_j)$。


接下来，再用如下代码段求出 $(a_i+b_i,a_j+b_j)$ 所在的位置：


```cpp
while (ans+1 < x + y)
	{//见上述规律
		k += ans;
		ans++;
	}
	k += y;//最后加上所在列数 y
```

# $ACCode$
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n, m, a, b, a1, b1, x, y, k;
int main() {
	scanf("%lld%lld", &n, &m);
	ll ans = 1;
	while (n - ans > 0) {
		n -= ans;
		ans++;
	}
	ans++;
	b = n;
	a = ans - n;
	ans = 1;
	while (m - ans > 0) {
		m -= ans;
		ans++;
	}
	ans++;
	b1 = m;
	a1 = ans - m;
	x = a + a1;
	y = b + b1;
	ans = 1;
	while (ans + 1 < x + y) {
		k += ans;
		ans++;
	}
	k += y;
	printf("%lld\n", k);
	return 0;
}
```

# [AC 力！](https://www.luogu.com.cn/record/89785439)


第三篇题解祭。

---

## 作者：Lixiuyu198 (赞：0)

### 思路:

数对可以分成

|($1,1) = 2$|
| :----------: |
|$(2,1)(1,2) = 3$ |
| $(3,1)(2,2)(3,3) = 4$ |
这种组；

可以发现，只需要找到序号 $i$ 属于哪组或 $a,b$ 数对属于哪组，就可以找出对应的序号 $i$ 或 $a,b$ 数对。
### ACcode
```cpp
#include <bits/stdc++.h>
using namespace std;
long long A(int a,int b) {//计算a,b数对属于那个组
	return ((long long)(a+b) * (long long)(a+b-1) / 2 ) + 1 - a;
   //先计算数对所属的组,在减上a,加1是因为第一个数对和不是1
}
auto x(long long ans){//用来找到第i个数对是什么,auto可以自动推断类型
	pair<int,int> ab;//创建pair数对
	long long sum ,g;
	for(int i = 1 ; sum<ans;++i){ //找到ta所在的组
		sum = (long long)(i +1) * (long long)(i) / 2;//公式用于遍历每一个组
		g=i	;}
	int s;
	ab.first = 1,ab.second = g;//对ab数对初始化成最高位
	s = ans -(sum - g) + 1; // 计算i在组中的位置
	for(int i = g ; i>=s ; --i){
		++ab.first,--ab.second;//慢慢遍历
	}
	return ab;//返回答案
}
signed main() {
	long long ans; cin >> ans;
	pair<int,int> a = x(ans); cin >> ans;//读入i和j
	pair<int,int> b = x(ans);
	pair<int,int> c;//答案
	c.first = a.first + b.first;//对应a_i+b_i
	c.second = a.second + b.second;//对应b_i+b_j
	cout << A(c.first,c.second) << endl;//别忘了换行
}
```


---

## 作者：fls233666 (赞：0)

我们先来看一下题目中的正整数对有什么性质。为了方便观察，我们把这些数对写成下面这个形式。

	(1,1)
    (2,1),(1,2)
    (3,1),(2,2),(1,3)
    (4,1),(3,2),(2,3),(1,4)
    ...
    
与题目相同，我们把每个正整数对记为 $(a,b)$。于是我们可以发现两件事：

- 每行的正整数对的两个数字之和是**相同的**。第 $n$ 行的正整数对满足 $a+b=n+1$，第 $n$ 有 $n$ 个数对。
- $b$ 与正整数对所在的列数**相同**。

发现这两件事后，接下来的事情就比较简单了。

对于输入的 $i$，我们可以先定位它们代表的数对在第几行，再定位它们在第几列。具体的，因为第 $n$ 行有 $n$ 个数对，我们可以循环不断减少 $i$，直到下一行的数对数量比 $i$ 多。此时又因为 $b$ 与正整数对所在的列数相同，就有了 $b=i$，又因为每行的和是固定的，就可以直接确定 $a$，对于输入的 $j$ 也是同样处理。

求出了 $(a_i,b_i)$ 与 $(a_j,b_j)$，就可以得到 $(a_i+a_j,b_i+b_j)$。运用与上述方法大致相同的一个过程，就能确定 $(a_i+a_j,b_i+b_j)$ 为第几个数对。

具体代码实现如下：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

ll ni,nj,ai,aj,aij,bi,bj,bij,ij;

int main(){
	scanf("%lld%lld",&ni,&nj);
    
	ll cnt=1;
	while(ni-cnt>0){
		ni-=cnt;
		cnt++;
	}  //确定第 i 个数对所在第 cnt 行
	cnt++;  //cnt+1 为这行数对 a+b 的和
	bi=ni;  //确定这个数对在第 bi 列
	ai=cnt-ni;  //获得 ai
	
	//同样的方法处理 j
    cnt=1;
	while(nj-cnt>0){
		nj-=cnt;
		cnt++;
	}
	cnt++;
	bj=nj;
	aj=cnt-nj;
	
	aij=ai+aj;
	bij=bi+bj;
	cnt=1;
	while(cnt<aij+bij-1){
		ij+=cnt;
		cnt++;
	}  //确定(ai+aj,bi+bj) 前面几行有几个数对
	ij+=bij;  //(ai+aj,bi+bj) 所在行前面有几个数对
	
	printf("%lld\n",ij);
	return 0;
}
```


---

## 作者：·糯· (赞：0)

## 题目分析
此题我们要先求出两组数，这两组数的求法我们需要先观察原数列，如果按一组数中的两数之和分类的话，可以发现每一类中的组的数量形成了一个公差为 1 的等差数列，所以我们可以利用这一点，结合等差数列求和，求出两组中的两数，具体详见代码。而求出两组数中的两数分别的和以后，就可以用类似上面的方法求出在第几组。题目其实不难，主要是有许多细节需要注意。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j;
int cnt;
int main(){
	cin>>i>>j;
	while(1){
		if(cnt*(cnt+1)/2>=i)//求最近的等差数列
			break;
		cnt++;
	}
	cnt--;
	int x1,y1;
	x1=cnt+1;
	y1=1;
	for(int g=cnt*(cnt+1)/2+1;g<i;g++){
		x1--;
		y1++;//按题意操作
	}
	cnt=0;
	while(1){
		if(cnt*(cnt+1)/2>=j)
			break;
		cnt++;
	}
	cnt--;
	int x2,y2;
	x2=cnt+1;
	y2=1;
	for(int g=cnt*(cnt+1)/2+1;g<j;g++){
		x2--;
		y2++;
	}
	cnt=0;//以上为求出两组数
	int x3=x1+x2,y3=y1+y2;
	int all=x3+y3;
	int sum=0;
	all--;
	sum+=all*(all-1)/2;
	sum+=y3;
	cout<<sum<<endl;//以上为求出题目要求的组的位置
	return 0;
}
```


---

## 作者：Edmundino (赞：0)

# 题意

先给你两个数$i,j$

求第$i$个数与第$j$个数的各个数位的和的有序数对排在第几位

# 分析

这明显是道找规律的题目

我们先看看他给的前几个数对

```
(1,1),(2,1),(1,2),(3,1),(2,2),(1,3),(4,1),(3,2),
(2,3),(1,4),(5,1),…
```
仔细观察

我们可以发现

我们可以按照第一个数与第二个数的和来分类

和为$2$有$1$组

和为$3$有$2$组

和为$4$有$3$组

……

和为$n$有$n-1$组

所以我们可以按照这个规律来定位

我们先把$i,j$分好类，看他是和为几的数对

分好类后

我们还要看每组里的数对的规律

和为$2$：第一个数对$(1,1)$

和为$3$：第一个数对$(2,1)$，第二个数对$(1,2)$

和为$4$：第一个数对$(3,1)$，第二个数对$(2,2)$，第三个数对$(1,3)$

和为$5$：第一个数对$(4,1)$，第二个数对$(3,2)$，第三个数对$(2,3)$，第四个数对$(1,4)$

……

和为$n$：第一个数对$(n-1,1)$，第二个数对$(n-2,2)$，第三个数对$(n-3,3)$……

这时候我们就可以求出$i,j$的数对的和了

求出后，我们假设是为$(a,b)$，排在第$s$位

然后根据前面的规律，我们可以用$a+b-1$知道这是第几组的数对，我们设为是第$t$组吧

然后$s$可以把$1-(t-1)$先加一遍

然后$(a,b)$又是这组的第$b$位数

所以$s=s+b$就是最后的解了

# 代码

**找第$i$个数对是啥的代码**

```cpp
void findd(int x,int &a,int &b)
{
	int y=x,g,i=1;
	for(;;)
	{
		if(y>i) y=y-i,i++;
		else
		{
			g=i;
			break;
		}
	}
	b=y;
	a=g+1-b;
	return;
}
```

**找$(a,b)$排在第几位的代码**

```cpp
void finde(int a,int b)
{
	int g=a+b-1;
	for(int i=1;i<g;i++)
	{
		s+=i;
	}
	s+=b;
}
```

**最后送上$AC$完整代码**

###### 别忘了最后打换行

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

int x,y,a,b,c,d,e,f,s;

void findd(int x,int &a,int &b)
{
	int y=x,g,i=1;
	for(;;)
	{
		if(y>i) y=y-i,i++;
		else
		{
			g=i;
			break;
		}
	}
	b=y;
	a=g+1-b;
	return;
}

void finde(int a,int b)
{
	int g=a+b-1;
	for(int i=1;i<g;i++)
	{
		s+=i;
	}
	s+=b;
}

int main()
{
	cin>>x>>y;
	findd(x,a,b);
	findd(y,c,d);
	e=a+c;
	f=b+d; 
	finde(e,f);
	cout<<s<<endl;
	return 0;
}
```



---

## 作者：_Ayanami_ (赞：0)

~~这是一道很臭的题所以这份题解也有点臭~~

观察一下应该都能发现规律

1,1

2,1 1,2

3,1 2,2 1,3

4,1 3,2 2,3 1,4

可以看出每一组a+b的和都是固定的
a不断递减
b不断递增

于是乎直接暴力枚举

第一重循环k枚举a+b的和

第二重从小到大枚举b（或从大到小枚举a也可）

这样先找到ai,bi和aj,bj

然后就可以找到ai+aj,bi+bj的位置

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,a=0,b=0,c=0,k=1,t=0;
int main()
{
	n=114514;
	m=1919810;
	scanf("%d%d",&n,&m);
	while(k)//不 要 停 下 来 啊（指枚举）
	{
		k++;//k枚举a+b的和
		for(int i=1;i<k;i++)//我是枚举b
		{
			t++;//组数++
			if(t==n)//找到ai,bi
			{
				a+=k-i;
				b+=i;
				c++;
			}
			if(t==m)//找到aj,bj
			{
				a+=k-i;
				b+=i;
				c++;
			}
			if(a==k-i&&b==i&&c==2)//找到答案
			{
				printf("%d\n",t);
				return 0;//还是停下来吧
			}
		}
	}
}
```


---

## 作者：MZY666 (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT249)。
[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-at249)。

### 【题意概括】

给定一个数列，输入 $i$，$j$。

若第 $i$ 项是 $(i_1,j_1)$，第 $j$ 项是 $(i_2,j_2)$。

输出 $(i_1+j_1,i_2+j_2)$ 是第几项。

此数列为：

$(1,1),(2,1),(1,2),(3,1),(2,2),(1,3),(4,1),(3,2),(2,3),(1,4),(5,1),…$

### 【 思路 】

要想把这题做出来，肯定要先把数列的规律观察出来。

第一个数：$1,\ 2,1,\ 3,2,1,\ 4,3,2,1...$

第二个数：$1,\ 1,2,\ 1,2,3,\ 1,2,3,4...$

已经很明显了吧$-v-$.

为了下文叙述方便，我们令 $(1,1)$ 为第 $1$ 组， $(2,1),(1,2)$ 为第 $2$ 组，$(3,1),(2,2),(1,3)$ 为第 $3$ 组$...$

很明显，第 $k$ 组会有 $k$ 项。而且在第 $k$ 组中每一项的 $k_i+k_j=k$。

好的，那么下面是时候让我们进入代码实现的环节了！

### 【 代码实现+注释 】

```cpp
#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯 
int main(){
	ll i,j,i1,i2,j1,j2,zu,ans=0;
	//zu表示目前有多少组
	//ans用于储存答案
	scanf("%lld%lld",&i,&j);//输入
    
	for(zu=1;i>zu;zu++)i-=zu;//算之前有几组，不可取等（自己想想？）
	//i-=zu的原因第zu组有zu个数，这样一直减直到i<=zu为止。
	zu++;//再加一组
	i1=zu-i;//转换得到i1
	j1=zu-i1;//转换得到j1
	
	for(zu=1;j>zu;zu++)j-=zu;
	zu++;
	i2=zu-j;
	j2=zu-i2;//同理
	
//	printf("i1=%lld j1=%lld i2=%lld j2=%lld\n",i1,j1,i2,j2);//测试用
	i=i1+i2;//加起来，得到新的i
	j=j1+j2;//加起来，得到新的j
	
	for(zu=2;zu<i+j;zu++)ans+=zu-1;
	//算除(i,j)所在组的之前有多少项
    
	printf("%lld\n",ans+j);
	//输出，j即(i,j)所在改组的第几项，所以再加上j即可
	
	return 0;//over~
}
```

作者已自愿禁言，如果有建议请私信，否则将**无法**回复您哟！

管理审核辛苦了AOA.

完结撒花~（疯狂暗示$-v-$.

---

