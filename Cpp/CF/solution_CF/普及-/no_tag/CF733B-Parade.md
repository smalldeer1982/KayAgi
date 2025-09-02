# Parade

## 题目描述

Very soon there will be a parade of victory over alien invaders in Berland. Unfortunately, all soldiers died in the war and now the army consists of entirely new recruits, many of whom do not even know from which leg they should begin to march. The civilian population also poorly understands from which leg recruits begin to march, so it is only important how many soldiers march in step.

There will be $ n $ columns participating in the parade, the $ i $ -th column consists of $ l_{i} $ soldiers, who start to march from left leg, and $ r_{i} $ soldiers, who start to march from right leg.

The beauty of the parade is calculated by the following formula: if $ L $ is the total number of soldiers on the parade who start to march from the left leg, and $ R $ is the total number of soldiers on the parade who start to march from the right leg, so the beauty will equal $ |L-R| $ .

No more than once you can choose one column and tell all the soldiers in this column to switch starting leg, i.e. everyone in this columns who starts the march from left leg will now start it from right leg, and vice versa. Formally, you can pick no more than one index $ i $ and swap values $ l_{i} $ and $ r_{i} $ .

Find the index of the column, such that switching the starting leg for soldiers in it will maximize the the beauty of the parade, or determine, that no such operation can increase the current beauty.

## 说明/提示

In the first example if you don't give the order to change the leg, the number of soldiers, who start to march from the left leg, would equal $ 5+8+10=23 $ , and from the right leg — $ 6+9+3=18 $ . In this case the beauty of the parade will equal $ |23-18|=5 $ .

If you give the order to change the leg to the third column, so the number of soldiers, who march from the left leg, will equal $ 5+8+3=16 $ , and who march from the right leg — $ 6+9+10=25 $ . In this case the beauty equals $ |16-25|=9 $ .

It is impossible to reach greater beauty by giving another orders. Thus, the maximum beauty that can be achieved is 9.

## 样例 #1

### 输入

```
3
5 6
8 9
10 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
6 5
5 6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
5 9
1 3
4 8
4 5
23 54
12 32
```

### 输出

```
0
```

# 题解

## 作者：N_z_ (赞：6)

## 思路
要求的答案是改变后的$|\sum a-\sum b|$的最大值。

$$\begin{aligned}
|\sum a-\sum b|_ {\max}&=|(\sum a-a_i+b_i)-(\sum b+a_i-b_i)|_ {\max}\\
&=|(\sum a-\sum b)-2*(a_i-b_i)|_ {\max}\\
&=\max(|\sum a-\sum b-2*(a_i-b_i)_ {\max}|,|\sum a-\sum b+2*(b_i-a_i)_ {\max}|)
\end{aligned}$$

那么对于一对$a_i$和$b_i$，它成为答案的必要条件是：
* $a_i$如果大于$b_i$，$a_i-b_i$应该大于等于所有$a_j-b_j(1≤j≤n,j≠i)$。
* $a_i$如果小于$b_i$，$b_i-a_i$应该大于等于所有$b_j-a_j(1≤j≤n,j≠i)$。

我们可以得到两组数，分别是$(a_i-b_i)_ {\max}$和$(b_i-a_i)_ {\max}$。

读入时处理然后判断即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int nowl=0,nowr=0,n,nowlid=1,nowrid=1,suml=0,sumr=0;
    cin>>n;
    for(int x=1;x<=n;x++)
    {
        int y,z;
        cin>>y>>z;
        if(y>z&&y-z>=nowl)nowl=y-z,nowlid=x;
        if(y<z&&z-y>=nowr)nowr=z-y,nowrid=x;
        suml+=y;
        sumr+=z;
    }
    //cout<<nowl<<','<<nowr<<','<<nowlid<<','<<nowrid<<','<<suml<<','<<sumr<<endl;
    if(nowl*nowr==0)cout<<0<<endl;
    else if(abs(suml-sumr-2*nowl)>=abs(suml-sumr+2*nowr))cout<<nowlid;
    else cout<<nowrid;
}
```

---

## 作者：Zhl2010 (赞：2)

## 题目概括
有两个序列 $l$ 和 $r$，可以交换它们任意一个相同位置上的数，问：怎样才能让 $l$ 的和和 $r$ 的和差的绝对值最大？

## 思路
**方法**：设 $x_1$ 是序列 $1$ 的和，$x_2$ 是序列 $2$ 的和，找到最大的 $x_1-x_2+r_i-l_i$ 和 $x_1-x_2+l_i-r_i$，进行比较，确定答案。

**证明**：首先，这题是求：
$$\max(|\sum l-\sum r|)$$

其次，我们可以进行如下操作：

交换 $l_i$ 和 $r_i$。

所以，交换后:

$$\sum l=\max(|\sum l-l_i+r_i|)$$
$$\sum r=\max(|\sum r+l_i-r_i|)$$

将其代入原式：

$$\max(|\sum l-\sum r|)=\max((|\sum l-l_i+r_i|)+(|\sum r+l_i-r_i|))$$

因为 $i$ 不是定值，可以 $l$ 大，也可以 $r$ 大，所以这个式子有两种情况。

$$|\sum l-\sum r-\max(2*(l_i-r_i))|$$

和

$$|\sum l-\sum r+\max(2*(r_i-l_i))|$$

最后的答案当然要取最大值，是：

$$\max(|\sum l-\sum r-\max(2*(l_i-r_i))|,|\sum l-\sum r+\max(2*(r_i-l_i))|)$$

证毕。

## 代码+注释
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r;
int x1=0,x2=0;//序列大小 
int a1/*最大的l-r*/,a2/*最大的r-l*/;
int ans1,ans2;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l,&r);
		if(a1<l-r){//取l-r的最大值 
			a1=l-r,ans1=i;//abs(x1-x2-2*a1)的情况 
		}if(a2<r-l){//取r-l的最大值 
			a2=r-l,ans2=i;//abs(x1-x2+2*a2)的情况 
		}
		x1+=l,x2+=r;//更新序列 
	}
	if(abs(x1-x2-2*a1)>=abs(x1-x2+2*a2))cout<<ans1<<endl;//刚刚的式子 
	else cout<<ans2<<endl;
	return 0;
}
```

---

## 作者：xiexinzhe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF733B)

比较水的暴力题，只要把每一步都试一遍就可以了。

## 分步①
首先，输入，并记下最开始和之差的绝对值：
```cpp
scanf("%d",&n);//输入n
int ll=0,rr=0;//和，设初值
for(int i=1;i<=n;i++)
{
	scanf("%d%d",&l[i],&r[i]);//输入l和r
	ll+=l[i];//累加l
	rr+=r[i];//累加r
}
mx=abs(ll-rr);//最开始和之差的绝对值
```

## 分步②
每一次都统计一下，并比较，最后求出最大值。 
```cpp 
for(int i=1;i<=n;i++)
{
	ll-=l[i];//|
	ll+=r[i];//|
	rr+=l[i];//|改变值 
	rr-=r[i];//|
	if(abs(ll-rr)>mx)//判断是否小于和之差的绝对值
	{
		mx=abs(ll-rr);//把值赋给mx 
		mxid=i;//记录位置 
	}
	ll+=l[i];//|
	ll-=r[i];//|
	rr-=l[i];//|变回来 
	rr+=r[i];//|
}
```

## 完整代码
```cpp
#include<bits/stdc++.h>//完美的万能头 
using namespace std;
int l[100001],r[100001];//定义 
int mx,mxid;
int main()
{
	int n;
	scanf("%d",&n);//输入n
	int ll=0,rr=0;//和，设初值
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);//输入l和r
		ll+=l[i];//累加l
		rr+=r[i];//累加r
	}
	mx=abs(ll-rr);//最开始和之差的绝对值
	for(int i=1;i<=n;i++)
	{
		ll-=l[i];//|
		ll+=r[i];//|
		rr+=l[i];//|改变值
		rr-=r[i];//|
		if(abs(ll-rr)>mx)
		{
			mx=abs(ll-rr);//把值赋给mx 
			mxid=i;//记录位置 
		}
		ll+=l[i];//|
		ll-=r[i];//|
		rr-=l[i];//|变回来
		rr+=r[i];//|
	}
	printf("%d\n",mxid);//输出 
	return 0;//完结撒花 
}
```

# 最后，祝大家AC
### [AC记录](https://www.luogu.com.cn/record/161540356)

### 管理大大求通过！

---

## 作者：Andy_WA (赞：1)

~~水题一道，但本蒟蒻还是卡了差不多十分钟（有五分钟卡测评上了。。。~~
## 水题分析
题目简化后，就是要我们求：
$$\max{\left|~\sum_{i=1}^{n}{l_i}-\sum_{i=1}^{n}{r_i}~\right|}$$
然后：$l_i$ 可以与 $r_i$ 交换。

哦？$n$ 最大才 $10^5$，枚举枚举！
## 水题思路
~~暴力枚举呗。~~

枚举每一个 $i$，对比交换与不交换的价值，时间复杂度 $O(n)$。
## 水题代码
```cpp
#include<bits/stdc++.h>
using namespace std;
/*Optimization series
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
*/
const long long MaxN=1e5+10;
long long l[MaxN];//l 数组 
long long r[MaxN];//r 数组 
long long n,SumL,SumR;//SumL 表示 l 的累加和，SumR 表示 r 的累加和， 
long long range;//当前最大的 |SumL-SumR| 
long long NowI=0;//当前的 i 
int main(){
	cin>>n;//输入 
	for(long long i=0;i<n;i++){
		cin>>l[i]>>r[i];
		SumL=SumL+l[i];//计算 l 的累加和 
		SumR=SumR+r[i];//计算 r 的累加和
	}
	range=abs(SumL-SumR);//计算初始的 |SumL-SumR| 
	for(long long i=0;i<n;i++){//枚举 i 
		long long TempL_Swap=SumL-l[i]+r[i];//计算交换后的 SumL 
		long long TempR_Swap=SumR-r[i]+l[i];//计算交换后的 SumR
		if(range<abs(TempL_Swap-TempR_Swap)){//比较价值 
			range=abs(TempL_Swap-TempR_Swap);//交换 
			NowI=i+1;//记录下标为答案 
		}
	}
	cout<<NowI<<endl;//输出答案 
	return 0;
}
```
最后，送大家一句话：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

## 作者：lkrabc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF733B)

## 题面解释

现在又两个长度均为 $n$ 的数组 $l,r$。然后我们要求选择一个 $l_i,r_i(1 \le i \le 500)$ 进行交换（当然也可以不选），使得两个数组的总和的差的绝对值最大。

## 思路

我们这道题要求 $ \Big \lvert \sum l - \sum r \Big \rvert_{max} $ 的值。

又因为我们只会选择一对（或者不选）$l_i,r_i$ 来进行交换 ，所以我们可以暴力枚举每一对 $l_i,r_i$。

但要记录差的变化，所以在开始的时候我们应该分别记录 $l$ 数组的和与 $r$ 数组的和（在输入时就可以累加）。然后我们令 $sum = \sum l - \sum r$，让 $sum$ 作为差的标准。

接下来我们执行暴力枚举：每次取出 $l_i,r_i$，然后进行判断：

如果 $sum$ 减去每次的变化值的 $2$ 倍，即 $2 \times (l_i-r_i)$ 的绝对值大于 $ans$ (记录到 $i$ 为止，和最大的差值)。

那么将 $ans$ 更改为此数，$pos$ 记录当前下标。

最后输出一下 $pos$ 就做完了。

### tips：我来解释一下为啥要减去变化值的2倍:

因为我要交换 $l_i,r_i$ 的值，其实就等价于在 $sum$ 中将这个差值乘以 $-2$。

举个例子：

若 $sum = 7,l_i - r_i=1$，则交换后的 $sum = 7+(r_i-l_i)-(l_i-r_i)=7+(-1)-1=5$ 。


这个代码的时间复杂度是 $\Omicron(n) $ 的 ，$1 \le n \le 10^5$ , 所以随便过。
## Code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+10;
int n;
int suml,sumr; //记录l,r数组的和 
int ans,pos; // 最大差值和其位置 
int l[N],r[N];

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) { //基本输入&&累加和 
		int l1,r1;
		cin >> l1 >> r1;
		suml+=l1;
		sumr+=r1;
		l[i]=l1;
		r[i]=r1;
	}
	int sum=suml-sumr; // 记录初始差 
	ans = sum; // 一定要加ans最开始定为sum!!! 
	for(int i = 1; i<=n; i++) {
		if(abs(sum-2*(l[i]-r[i]))>abs(ans)) { // 刚刚说的 
			ans = sum - 2*(l[i]-r[i]); //更改最大值 
			pos = i; // 更改下标 
		}
	}
	cout << pos;
	return 0;
}
```

---

## 作者：KyleShen1213 (赞：0)

## 解题思路
~~水题一道~~

分别计算两个序列的和，循环每一个下标，计算互换此下标的数所得的两个差，如果比之前的都大，就记录差和下标，最后就能求出最大的差。

话不多说，直接上代码～～～

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[100005],r[100005],maxcha=0,maxplace,suml=0,sumr=0;
//maxcha记录最大差值，maxplace记录最大差值的下标，suml和sumr分别求两序列的和 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>l[i]>>r[i];
		suml+=l[i];sumr+=r[i];//求和 
	}
	maxcha=abs(suml-sumr);//求出初始差值 
	for(int i=1;i<=n;i++)//循环求最大差 
	{
		if(abs((suml-l[i]+r[i])-(sumr-r[i]+l[i]))>maxcha)
		//若互换此下标的数所得的差大于前面最大的的差，就记录 
		{
			maxcha=abs((suml-l[i]+r[i])-(sumr-r[i]+l[i])); 
			maxplace=i;
		}
	}
	cout<<maxplace<<endl;
	return 0;
}
```

---

## 作者：wangzihan_ (赞：0)

### 题目解析
给你 $N$ 个 $L$ 和 $R$，通过交换任意一个 $L$ 与 $R$，使得 $L$ 的总和和 $R$ 的总和的差最大
### 想法
拿到这个题，发现数据范围只有 $10^5$？于是可以考虑暴力
先预处理出 $L$ 和 $R$ 的和。从头到尾扫一遍，交换 $L_i$ 和 $R_i$。也就是把 $sum_l-l+r$，$sum_r-r+l$。统计最大值即可。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
int l[100005],r[100005];
int suml,sumr;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		suml+=l[i];//统计l的总和 
		sumr+=r[i];
	}
	int ans=0,cnt=abs(suml-sumr);//先预处理初值，不用改时直接输出ans=0 
	for(int i=1;i<=n;i++)
	{
		int nowsuml=suml-l[i]+r[i];//交换l和r，也就是把总和减去l，加上r 
		int nowsumr=sumr-r[i]+l[i];//同理 
		if(abs(nowsuml-nowsumr)>cnt)//打擂台更新ans和cnt值 
		{
			cnt=abs(nowsuml-nowsumr);
			ans=i;
		}
	}
	printf("%d",ans);
}
```

---

## 作者：a18981826590 (赞：0)

# [Parade](https://www.luogu.com.cn/problem/CF733B)
## 解题思路
为了使两序列交换后的和之差最大，应该交换差最大的两个。

可以记录两个下标 $i$，$j$ 满足 $a_{i}-b_{i}$ 大于等于所有 $a_{k}-b_{k}(1 \le k \le n)$，$b_{j}-a_{j}$ 大于等于所有 $b_{k}-a_{k}(1 \le k \le n)$。

最后分别求出这两种交换后两序列的和之差，取最大值。
## 解题方法
可以在输入时用打擂法找到 $(a_{i}-b_{i})_ {\max}$ 及 $(b_{j}-a_{j})_ {\max}$，并记录 $i$ 及 $j$。最后分别求出这两种交换后两序列的和之差，取最大值输出下标即可。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f,g,h,n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		c+=a;
		d+=b;
		if(a-b>e){
			e=a-b;
			g=i;
		}
		if(b-a>f){
			f=b-a;
			h=i;
		}
	}
	if(abs(c-d-2*e)>=abs(c-d+2*f)) cout<<g;
	else cout<<h;
	return 0;
}
```

---

