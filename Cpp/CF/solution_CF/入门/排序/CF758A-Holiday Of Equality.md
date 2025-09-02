# Holiday Of Equality

## 题目描述

## 题目大意
今天是Berland的平等节。为了庆祝节日，国王决定用国库里的钱来使Berland所有公民的福利均等。

在Berland，有$N$个公民，每个人的福利都被估计为一个整数$a_{i}$ burle（burle是Berland的货币）。

你是皇家财政管理员，你需要计算国王为此要付出的最低费用。国王只能给公民们钱，他没有权力夺走任何钱财。

## 说明/提示

第一个样例中，如果我们给第一个公民4 burles，第二个3 burles，第三个2 burles，第四个1 burle，那么所有公民的福利都等于4 burles。

第二个样例中，我们只需要给第三个公民1 burle就可以使得福利均等。

第三个样例中，我们需要分别给第一个和第三个公民2 burles，使得福利都等于3 burles。

第四个样例中，我们不需要给任何人钱因为所有人的福利都是12 burles。


对于100%的数据，$1 \leq n \leq 100$，$0 \leq a_{i} \leq 10^{6}$。

翻译提供者：Simpson561

## 样例 #1

### 输入

```
5
0 1 2 3 4
```

### 输出

```
10```

## 样例 #2

### 输入

```
5
1 1 0 1 1
```

### 输出

```
1```

## 样例 #3

### 输入

```
3
1 3 1
```

### 输出

```
4```

## 样例 #4

### 输入

```
1
12
```

### 输出

```
0```

# 题解

## 作者：Alex_Wei (赞：16)

#### 题目其实就是求一个数列的最大数，减去这个数列所有数的差 之和

假设这个数列的最大数为 $m$，则答案

$$=(m-a_1)+(m-a_2)+(m-a_3)+\dots+(m-a_n)$$

$$=m*n-\sum_{i=1}^{n}a_i$$

我们可以边读边做，一边求出最大值，一边求出数列的和，这样就不用数组了

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,s,n,a;//m是最大数，s是数列的和
int main()
{
	cin>>n;
	for(int x=1;x<=n;x++)cin>>a,m=max(m,a),s+=a;
	cout<<n*m-s;
	return 0;
}
```
如果有错误欢迎在右侧评论区留言或私信

$\mathrm{Upd\ 2019.11.13:}$ 美化文章，添加 $\LaTeX$（话说这还是我老早以前写的题解）

---

## 作者：whose (赞：7)

这其实是一道非常水的模拟题，只需要找到最大的福利，然后与每个福利相减得到差，再将这些差累加即可。
## 话不多说上代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[101];
int ans;
int main(){
	scanf("%d",&n);//输入
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);//先将所以福利排序，得到最大的福利
	for(int i=1;i<n;i++){
		ans+=a[n]-a[i];//累加每个福利与最大福利之间的差
	}
	printf("%d",ans);//输出
	return 0;
} //圆满结束，请勿抄袭！！！
``` 

---

## 作者：Ca2ng (赞：1)

~~这是道水题~~  
# 思路如下： 
⒈定义  
⒉输入  
⒊寻找最大值（max）  
⒋计数器（s）累加每个值（a[i]）与最大值（max）的差值  
⒌输出差值  
⒍结束


# 代码↓↓↓  

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main()
{
	int n,max=0,s=0;//⒈分别定义个数，最大值和计数器，注意计数器是要归零的 
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];//⒉输入数据 
	for(int i=0;i<n;i++)
		if(a[i]>max) max=a[i];//⒊循环+判断找最大值 
	for(int i=0;i<n;i++)
		if(a[i]<max) s=s+max-a[i];//⒋计数器累加每个值与最大值之间的差 
	cout<<s;//输出差值 
	return 0;//结束 
}
```



---

## 作者：tryrtj (赞：1)

大佬们做一道红题怎么能用数组呢？

并且由两次提交实测了一个事实

[cin读入](https://www.luogu.org/record/show?rid=13644144)

[scanf读入](https://www.luogu.org/record/show?rid=13644209)

由提交可知scanf消耗内存较大，而cin消耗时间较多，所以以后内存卡的严就用cin，时间紧就scanf

接下来回归正题，不用数组的解法


```
#include<iostream>
using namespace std;
int main(){
	int n,w,maxn=0,zong=0;//初始化最大值为0，总值为0
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d",&w);//读入
		zong+=w;//求现在手里一共多少钱
		if(w>maxn)maxn=w;//求最大值
	}
	cout<<maxn*n-zong;//需要的钱就是n倍最大值减
    //去现有的钱，因为n个人最后都要拿到maxn数量的钱
	return 0;//走人了
}
```

用cin是可以0MB过的

---

## 作者：OdtreePrince (赞：1)

# -纯模拟-

>其实没什么难度，只要取max再求差，把差相加即为ans

注：max为取较大值函数  >_<

~~~
#include<bits/stdc++.h>
using namespace std;
int maxx,a[1000005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        maxx=max(maxx,a[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=maxx-a[i];
    }
    cout<<ans;
    return 0;
}
~~~

---

## 作者：一滴小水滴 (赞：0)

这道题其实就只需要求出最大值，并且暴力一个个的将这个数与最大数的差累加起来就可以了（找最大值本人懒惰，用的sort）。可以用快读快写优化时间（虽然不会TLE）

直接上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,w=0;
	char ch=0;
	while(!isdigit(ch))
	{
		w|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return w? -x:x;
}
inline void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}     //快读快写。
int n,ans=0,a[105];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+1+n);   //输入之后sort找出最大值。
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[n])ans+=a[n]-a[i];
	}     //将每个数与最大数的差累加起来。
	write(ans);   //最后输出答案。
	return 0;
}
```

---

## 作者：开心的猪 (赞：0)

每个人最终的福利就是最初所有人中福利最丰厚的那个人的福利。于是可以得到下面这个公式：

一个人得到的福利=最大值-原来的福利。

下面是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a;
	scanf("%d", &a);
	char b[100]={0};
	for(int i=0; i<a; i++)
	{
		cin>>b;
		if(strlen(b)>10)
		{
			printf("%c%d%c\n", b[0], strlen(b)-2, b[strlen(b)-1]);
		}
		else
		{
			printf("%s\n", b);
		}
	}
	return 0;
}
```


---

## 作者：打表大蒟蒻 (赞：0)

这道题很水，中心思想是把他们的每一个a[i]作差，具体注释代码里有
```cpp
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
int a[101], maxv, answer;     //定义全局数组和变量，因为在主函数外定义，所以不用初始化为0 
int main ()
{
	int n;
	scanf("%d",&n);  //读入n 
	if(n==0) return 0; 
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);    //读入a[i] 
		maxv=max(maxv,a[i]);  //打擂台求最大值，排序也可
		//或者写成  if(maxv<a[i])  maxv=a[i]; 
	}
	
	for(int i=1;i<=n;i++)
		answer+=(maxv-a[i]);     //最终答案加上最大值减去每一个a[i]
		
	cout<<answer<<"\n";   //输出 
	return 0;   //完美结束 
}
```


---

## 作者：爬行者小郑 (赞：0)

# 主要思路很重要


------------
因为要平均，所以取最大的（max）乘上人数（n）就是目标。

所以得到：

------------

## $ans=max*n-sum$



其中，


------------

$sum=\displaystyle\sum_{i=1}^{n}a_i$



------------
也就是：


------------
$sum=a_1+a_2+a_3+\dots+a_n$

------------

好了，废话不多说，


------------

### 下面用~~C++~~ C来解决这个问题：
```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,a[105],m,sum,ans;
	int i,j;                      //必须在外面定义
	m=0;
	sum=0;
	scanf("%d！",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);    //输入
	}
	for(i=1;i<=n;i++)
	{
		sum=sum+a[i];         //求和
	}
	for(i=1;i<=n;i++)
	{
		if(a[i]>m)
		{
			m=a[i];       //找到最大
		}
	}
	ans=(m*n)-sum;                //中心公式
	printf("%d",ans);             //输出
	return 0;
}
```
不是很难吧，886！




---

## 作者：judgejudge (赞：0)

# 分三种情况来走！！！
首先我们必须要判断这些数字**是否全部相等**或**只有一个数字**，因为在这两种情况下**答案都为0！！！**

所以我们先进行判断：
```cpp
cin>>n;
	for(i=1;i<=n;i++){
	    cin>>a[i];
	    if(i>1){//这里等到i>1时再判断，目的是判断之前那一个数
	    	if(a[i]!=a[i-1])k++;//如果不相等，k++
		}
		if(a[i]>max)max=a[i];//这里负责确定最大值，之后会讲解
	}
	if(k==0){//k=0说明全部数各自相等
		cout<<0<<endl;
		return 0;
	}
	if(n==1){//总量为1
		cout<<0<<endl;
		return 0;
	}
```
上面提到**确定最大值**的问题，其实就是**中心思想**：

## 找到最大值，求最大值与所有数字差的和！！！
那么AC代码就出来了:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000];
int sum=0;
int main(){
	int i,j,k=0,n,max=0;
	cin>>n;
	for(i=1;i<=n;i++){
	    cin>>a[i];
	    if(i>1){
	    	if(a[i]!=a[i-1])k++;
		}
		if(a[i]>max)max=a[i];
	}
	if(k==0){
		cout<<0<<endl;
		return 0;
	}
	if(n==1){
		cout<<0<<endl;
		return 0;
	}
	for(i=1;i<=n;i++)sum+=(max-a[i]);//就是找到最大值，求最大值与所有数字差的和！！！
	cout<<sum<<endl;//输出最大值
	return 0;
}
```

---

## 作者：Ace_Radom (赞：0)

首先，这题要分析一下

	就是说，每个公民都有一个基础福利，要让他们品等
    
【“每个人的福利都被估计为一个整数”就是每个人的福利初值啦】

# 那么

### ~~似乎结束了诶~~

#### ~~再皮几句吧~~

从“他没有权力夺走任何钱财”中可得，最少的只能向最多的靠拢

那么中心思路就是：

	算出一个最大值，一个一个作差，加起来就是答案
    
Code：

```
#include<bits/stdc++.h>
using namespace std;
long long maxn = -2E64+1;  
//求最大值，初值赋大一点
//2E64就是2的64次方【-2E64+1是long long的最小值】
//所以用Dev-C++5.10会警告，不用管
void maxx( int n , int i ){  //一个简单的max
//i其实不用读入的啦【滑稽】
	if ( n > maxn )
	{
		maxn = n;
	}
	return;  //这个有无都可
}
int Pss( int n ){
	return maxn - n;  
    //我把作差的东西都写成函数了【二次滑稽】
}
int main(){
	int n,i,a[101];
	cin >> n;
	for ( i = 1 ; i <= n ; i++ )
	{
		cin >> a[i];
		maxx( a[i] , i );
        //在读入同时即可算最大值了
        //由于maxn是全局变量，就用void即可
	}
	int ans = 0;  //不是全局变量，必须要赋初值
    //不赋初值会很鬼畜的【三次滑稽】
	for ( i = 1 ; i <= n ; i++ )
	{
		ans += Pss( a[i] );  
        //向土豪靠拢【四次滑稽】，并把缺的钱++
	}
	cout << ans;
	return 0;  //不打CE【五次滑稽】
}
```

---

## 作者：wlyzzhaoyilin (赞：0)

水体一道，如果按花最少的钱来算的话，最有钱的公民是不用给的，
给穷人们补差价就行了~~滑稽~~，
```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int main()
{
	int n,sum=0,max=-99999;//max往小了定义，
	int a[9999];//开一个大数组
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	    if(a[i]>max)
	    max=a[i];//找到最有钱的
	}
	for(int i=1;i<=n;i++)
	  sum+=(max-a[i]);//累计补的差价
	cout<<sum;//输出
	return 0;
}
```
~~本人蒟蒻一个，求过~~
作为萌新可以多做水题哟，为以后漫漫OI路铺垫

---

## 作者：dl__hh6 (赞：0)

~~**啊，尽然没p党出没，我来打头！！**~~

这题其实是一道模拟题；；

话不多说，进入正题：

题意：分钱，有分给每人相同数量的钱；

注释详见代码中：
```pascal
var
  n,max,min,i,j:longint;
  a:Array[1..1000]of longint;
begin
  read(n);//读入，（不用讲了吧！）
   for i:=1 to n do
  begin
    read(a[i]);
  end;
 max:=0;//赋初值；
for i:=1 to n do 
  if max<a[i] then max:=a[i];//找到那个最大的；因为付
  出去的钱要少，所以不要给最多的，要以最多为标准来
  分钱；
   for i:=1 to n do begin
    if a[i]<>max then begin
    min:=min+max-a[i];//循环找在那些少的的钱中补到最多
    的那个最多的钱的数量；
   end; //min为计数器；
end;
write(min);
end.
```
~~**拒绝抄题，从我做起**~~

---

## 作者：hzx1 (赞：0)

思路：求出序列中最大的数，用这个数减去序列中其他的数，这些差累计起来即为答案。（因为国王不会夺走公民的钱财，又想花最少的钱，所以公民中钱最多的人国王不会再给，只需将其他人的钱财加到与最多钱的公民相等即可）

~~好吧，有点啰嗦了~~

接下来上代码

```cpp
#include<iostream>//头文件不说
using namespace std;
const int MAXN=10001;
int main(){
    int a[MAXN];      //定义10001个数组元素
    int i,n,maxa,sum=0;
    cin>>n;            //输入
    for(i=1;i<=n;i++)
      cin>>a[i];        //读入n个数，并存储到a[1]~a[n]中
    maxa=a[1];       //赋最大值初值和初始位置
    for(i=2;i<=n;i++) //枚举数组(a[2]~a[n-1])，找到最大数和位置
      if(a[i]>maxa){  //比前面数据更大，更新最大值及其下标
        maxa=a[i];  //记下值
    }
    for(i=1;i<=n;i++){
    	sum+=(maxa-a[i]); //钱最多的公民的钱财减去其他人的钱财，并累加起来
	}
    cout<<sum;           //输出答案
    return 0;            //结束
}
```

祝各位AC…  >_<

---

## 作者：HNYLMS_MuQiuFeng (赞：0)

~~又是一道水题呢~~

这道题就是找到最大值然后把没有达到最大值的补成最大值，求需要补多少。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxn,sum;
int main()
{
    cin>>n;int a[n+1];
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>maxn)//记录最大值
        maxn=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        sum+=abs(maxn-a[i]);//每一项还差多少就加多少
    }
    cout<<sum;
    return 0;//输出，愉快的AC啦！锵锵！
}
```
# 杜绝抄袭，从我做起！！！！
~~（又水一篇CF题解真舒服）~~

---

