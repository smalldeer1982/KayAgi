# Alice, Bob and Chocolate

## 题目描述

Alice and Bob like games. And now they are ready to start a new game. They have placed $ n $ chocolate bars in a line. Alice starts to eat chocolate bars one by one from left to right, and Bob — from right to left. For each chocololate bar the time, needed for the player to consume it, is known (Alice and Bob eat them with equal speed). When the player consumes a chocolate bar, he immediately starts with another. It is not allowed to eat two chocolate bars at the same time, to leave the bar unfinished and to make pauses. If both players start to eat the same bar simultaneously, Bob leaves it to Alice as a true gentleman.

How many bars each of the players will consume?

## 样例 #1

### 输入

```
5
2 9 8 2 7
```

### 输出

```
2 3
```

# 题解

## 作者：Loner_Knowledge (赞：10)


---

根据题意模拟过程即可。

```cpp
#include<cstdio>
int num[100002];
int main() {
	int n,p1,p2;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",num+i);
	p1=1;	//p1记录A吃到的位置
	p2=n;	//p2记录B吃到的位置
	for(int sum1=0,sum2=0;p1<=p2;) {	//模拟过程
		if(sum1<=sum2)
			sum1+=num[p1++];
		else
			sum2+=num[p2--];
	}
	printf("%d %d",p1-1,n-p2);	//注意输出
	return 0;
}
```

---


---

## 作者：锦瑟，华年 (赞：8)

我又来水题解了。

本题思路：模拟。用一个While循环便可解决，唯一一个要注意的便是结束条件。因为如果两人同时开始吃一个糖果，A会让给B，所以当$A==B$时，就要从While循环里跳出来，并把$B++$ ，当然，我代码中的那种方法也是可以的。

代码：

	#include<stdio.h>
	using namespace std;
	int a[1000005];//数组
	int main(){
		int n,i,h,h1;
		scanf("%d",&n);//读入
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		h=1;h1=n;//分别表示A,B的指针，即吃到哪了
		while(h1-h>1){//主过程，注意循环条件，也可写作h<h1
			if(a[h]<a[h1]){//三个判断，比较简单，自己理解
				a[h1]-=a[h];h++;continue;
			}
			if(a[h]>a[h1]){
				a[h]-=a[h1];h1--;continue;
			}
			if(a[h]==a[h1]){
				h++;h1--;continue;
			}
		}
		printf("%d %d",h,n-h);//输出，注意，因为吃同一个时，A让给B，所以要B++，不过在此A吃的量已经确定，所以只要减一下即可算出B的值，省去了判断。
		return 0;
	}
    
好了，结束，拜拜~~~

---

## 作者：封禁用户 (赞：5)

这是一道贪心模拟题，主过程使用 while 即可。  
题目传送>>[CF6C](https://www.luogu.com.cn/problem/CF6C)
### 题意简述：  
Alice 和 Bob 两人吃 $n$ 块巧克力，两人分别从巧克力排列两端推进吃，当两人同遇一块巧克力时，Bob 会让给 Alice，求最终两人分别吃到的巧克力数。  
### 题目分析：  
Alice 从前往后贪心，Bob 从后往前贪心，即吃完当前位置巧克力所花时间最少者可继续推进，两者相遇即吃完巧克力。  
### Code:
```cpp
#include<iostream>
using namespace std;
int	c[100001];   //开数组存每块巧克力吃完需要的时间 
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出 
	int n,a=0,b=0,q,h;   //定义巧克力数、Alice吃当巧克力耗时、Bob吃当前巧克力耗时、Alice从前吃巧克力的位置、Bob从后吃巧克力的位置 
	cin>>n;
	q=1,h=n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
	}
	while(q<=h)   //未吃完即执行主过程 
	{
		if(a<=b)   //Alice用时短和两人用时相等刚吃同一块巧克力时绅士礼让女士 
		{
			a+=c[q++];
		}
		else
		{
			b+=c[h--];
		}
	}
	cout<<q-1<<" "<<n-h;   //最终两人分别吃的巧克力数 
	return 0;   //结束整个程序 
 } 
```
### 评测结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/mhhax1hg.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：wpj20241021005 (赞：5)

这一道题的正解当然是模拟啦，但本人非常的懒，不想打那么长的代码，于是乎，就想用一种更简单的方法取解决这道题。

这道题说的是双方一个从头开始吃，一个从尾开始吃，而且必须要按顺序，吃完第一个才可以吃第二个，所以双方吃的时间总和一定所有糖的时间总和。而只有两个人吃，我们就可以先记录总共的时间，然后寻找到双方的分界线（大于总时间/2的地方），然后用if判断，就可以得出双方各吃了多少了。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,a[10010],ans,k,i;//定义
double sum;
int main(){
	cin>>n;//输入;
	for(i=1;i<=n;i++){//循环输入
		cin>>a[i];
	 	sum+=a[i]; //记录糖果总时间
	} 
	for(i=1;i<=n;i++){//找一半出
		k+=a[i];
		ans++;
		if(k>sum/2) break;//跳出循环
	}
	if(sum-k>=k-a[ans]) cout<<ans<<" "<<n-ans;//如果a吃的时间小于或等于b吃的时间，输出
	else cout<<ans-1<<" "<<n-ans+1;//如果a吃的时间大于b吃的时间,输出
} 
```


---

## 作者：ahawzlc (赞：2)

~~没错这道 C 题是橙难度~~

-----

我们可以统计前缀和与后缀和，在找后缀和的同时标记哪块糖果是有争议的（说白了就是**最后一个被吃的糖**），然后比较**吃到**这块糖 a,b 两人所用的时间，根据题目要求决定这个糖谁来吃。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int t[100005],qa[100005],qb[100005],mid;
int main() {
	int n,a,b;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>t[i];
		qa[i]=qa[i-1]+t[i]; 
	}
	for(int i=n;i>=1;i--) {
		qb[i]=qb[i+1]+t[i];
		if(qb[i]>qa[n]/2&&!mid) mid=i;//标记
	}
	if(qa[mid-1]>qb[mid+1])
		cout<<mid-1<<' '<<n-mid+1;
	else
		cout<<mid<<' '<<n-mid; //绅士风范
	return 0;
}
```

---

## 作者：胡金梁 (赞：1)

直接模拟，说白了就是双指针，一个指向A正在吃的那块糖，一个指向B正在吃的那块糖，在定义两个变量，一个表示A吃了多长时间，一个表示B吃了多长时间。然后就没然后了。
```cpp
#include<iostream>
using namespace std;
int num[100002];
signed main()
{
	int n,pA,pB;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>num[i];
	}
	pA=1;
	pB=n;
	for(int sA=0,sB=0;pA<=pB;)
	{
		if(sA<=sB)
		{
			sA+=num[pA++];
		}
		else
		{
			sB+=num[pB--];
		}
	}
	cout<<pA-1<<" "<<n-pB;
}
```


---

## 作者：PrincessYR✨～ (赞：1)

一道比较有趣的模拟题

就是同时从头开始走，从尾开始走，如果一个花费的时间大于另一个花费的时间，那么花费时间少的再吃下一个。

具体讲解见代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],numa,numb,coa,cob,tota,totb;
int main()
{
	cin>>n;
	numa=0;numb=n+1;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(1)
	{
		if(coa==cob)//如果a，b同时吃完他们正在吃的糖，那么他们就可以同时开始吃下一个糖 
		{
		    numa++; 
		    numb--;
		    if(numa==numb)//如果a,b同时吃完，并且接下里吃的都是同一颗，那么就如题目所说，让给a 
			{
				tota++;
				break;
			} 
			else //否则，同时吃下一颗 
			{
				tota++;
				totb++;
			    coa+=a[numa];
			    cob+=a[numb];
			}
		}
		else if(coa>cob)//如果b花费的时间少，也就是b先吃完正在吃的这一颗，那么b吃下一颗，a继续吃原来那一颗 
		{
			totb++;
			numb--;
			cob+=a[numb];
		}
		else if(coa<cob)//如果a花费的时间少，也就是a先吃完正在吃的这一颗，那么a吃下一颗，b继续吃原来那一颗 
		{
			tota++;
			numa++;
			coa+=a[numa];
		}
		if(numb-1==numa)//如果a与b之间没有多与的糖了，也就是a,b吃完再也没有糖了 
		{
			break;//结束 
		}
	}
	cout<<tota<<" "<<totb;
	return 0;
}
```


---

## 作者：Mr_WA的大号 (赞：1)

AC程序，人人有责，小学生又来发题解了！

题号：CF6C

难度：★★★

算法：纯模拟

## 开课了！

这道题，一看题目就 **~~不会做~~** 知道是纯模拟。C++纯模拟时间复杂度正好是10^8次方，所以——

## 暴力出奇迹

一起模拟吧！

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
int n,a[100010],t[100010],A,B,ag,bg;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
   	A=1;//A代表a当前在吃哪颗糖
	B=n;//B代表b当前在吃哪颗糖
    ag=1;//ag为a吃的糖数
    bg=1;//bg为b吃的糖数
	if(n==1){cout<<"1 0";return 0;}//特判
	while(ag+bg<n)//如果他们一共都没有吃够糖，就执行
	{
		a[A]--;//a当前吃糖的时间少1
        a[B]--;//b当前吃糖的时间少1
		if(!a[A]&&a[A+1])A++,ag++;//如果a的糖吃完了且下一个糖没被吃完，就吃下一个
		if(!a[B]&&a[B-1])B--,bg++;//如果b的糖吃完了且下一个糖没被吃完，就吃下一个
	}
	cout<<ag<<" "<<n-ag;//输出
	return 0;
}
```
祝大家能AC！

---

## 作者：Lucifer_Bartholomew (赞：1)

# ~~模拟~~
先算出平均每人能吃几个，然后从前往后一个一个搜，搜到第一个人刚好吃不了时，处理答案输出。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100005];
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
	int n=read(),sum=0;
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		sum+=a[i];
	}
	int ssum=sum>>1/*第一个人最多能吃几个*/,summ=ssum,i=1;
	for(;i<=n;++i)//搜
	{
		if(ssum>=a[i])ssum-=a[i];
		else break;
	}
	summ-=ssum;
	int sumt=sum-summ-a[i];//计算最中间的糖谁吃
	if(sumt<summ)printf("%d %d\n",i-1,n-i+1);//答案输出
	else printf("%d %d\n",i,n-i);
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：Allanljx (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF6C)

[CF传送门](https://codeforces.com/problemset/problem/6/C)

## 思路
用前缀和和后缀和记录 $a$ 和 $b$ 吃到中间的那块： $c$， 时用了多长时间，再处理 $c$ 。如果 $b$ 先吃完 $c$ 的后面那块，则 $b$ 可以吃到 $c$ ，否则 $a$ 可以吃到 $c$ 。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],qz[100005],hz[100005],mid;//qz:前缀和,hz:后缀和 
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)//前缀和 
	{
		qz[i]=qz[i-1]+a[i];
	}
	for(int i=n;i>=1;i--)//后缀和 
	{
		hz[i]=hz[i+1]+a[i];
		if(hz[i]>qz[n]/2&&mid==0) mid=i;//求中点 
	}
	if(qz[mid-1]>hz[mid+1])//如果a吃完前一颗糖的时间大于b吃完后一颗糖，那么b可以吃到这颗糖 
	{
		cout<<mid-1<<' '<<n-mid+1;
	}
	else//否则会让给a 
	{
		cout<<mid<<' '<<n-mid;
	}
	return 0;
}
```


---

