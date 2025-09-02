# Captain Flint and Crew Recruitment

## 题目描述

如果一个正整数能写成两个不同质数的积，那么我们称它为类质数。

给定一个自然数 $n$，请问是否能将 $n$ 写成四个**互不相同**的正整数的和，并满足这四个正整数中**至少**有三个是类质数。如果能，请给出一种方案。

## 样例 #1

### 输入

```
7
7
23
31
36
44
100
258```

### 输出

```
NO
NO
YES
14 10 6 1
YES
5 6 10 15
YES
6 7 10 21
YES
2 10 33 55
YES
10 21 221 6```

# 题解

## 作者：houpingze (赞：6)

~~沉迷枚举选手在线教你极限卡常~~

## 思路：

就是暴力枚举四个数，判断它们四个是否有三个以上的数是类质数，是输出`YES`和解，不是输出`NO`

~~闭着眼睛用脚指头算都知道会TLE~~

## 优化
### 埃氏筛

预处理把质数都算一遍

**这种方法更重要：当我们枚举了$i,j$时，可以先判断$i,j$是不是类质数，如果都不是，意味着不可能出现$l,k$使得它们四个数有三个数都是类质数，当枚举到$k$时同理。**

更详细的思路见CODE：
```cpp
#include<iostream>
typedef unsigned long long ull;
using namespace std;
int n,cnt,m;
bool a[10000001];//a数组用于 存放i是不是质数，是的值为1，不是的值为0 
void ass(){//埃氏筛求素数 
	a[1]=1;//特判，1不是质数 
	for(int i=2;i*i<=10000000;i++){
		if(a[i]==0){
			for(int j=i*i;j<=10000000;j+=i){
				a[j]=1;//有因数，标记为不是  
			}
		}
	}
}
bool jh(int n){//判断类质数 
	for(int i=2;i*i<=n;i++){
		if(n%i==0&&i!=n/i){
			if(a[i]==0&&a[n/i]==0) return true; //可以拆成a*(n/i) 
		}
	}	
	return false;//不符合条件 
}
int main(){
	ass();
	int t;
	cin>>t;
	while(t--){//多组数据 
		cin>>n;
		int f=0;
		int t1,t2,t3,t4;
		for(int i=1;i<n;i++){
			t1=jh(i);//存储i是不是类质数 
			for(int j=1+i;j<n;j++){
				t2=jh(j);//存储j是不是类质数 
				if(t1==0&&t2==0) continue;//如果i，j都不是类质数，表示肯定不会存在四个数里面有三个类质数的情况。continue 
				for(int k=1+j;k<n;k++){
					t3=jh(k);//同上 
					if(t3==0&&t2==0) continue;//同上
					int l=n-i-j-k;//优化，直接算出第四个数 
					t4=jh(l);
					if(l>0&&i!=j&&i!=k&&i!=l&&j!=k&&j!=l&&k!=l){//判断是不是有相等的数 
						int c=t1+t2+t3+t4;//i，j，k，l中的类质数个数 
						if(c>=3){//符合条件 
							cout<<"YES\n";//输出YES 
							f=1;
							cout<<i<<' '<<j<<' '<<k<<' '<<l<<endl;
							break;//输出解，跳出 
						}
					}
				}
				if(f==1) break;
			}
			if(f==1) break;
		}
		if(f==0) cout<<"NO\n";//没有解，输出NO 
	}
}
```

---

## 作者：Thomas_Cat (赞：2)

思路：

- 输入并且循环输入判断
- 找出三个最小的可以被分成质数乘积的数字 $2 \times 3 =6 ,2 \times 5=10,2 \times 7=14$

- 如果输入的 $n < 6+10+14(30)$ ，输出 `NO` ，反之输出 `YES` 以及 $n - 30$

注：这里需要特判一下，如果剩下的那一个数字是 $6 , 10 , 14$ 的时候我们需要特判，因为题目中说了是 **互不相同** 的数字，因此我们找到一个小一些的质数 $3 \times 5 = 15$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        if(n<=30) cout<<"NO"<<endl;
        if(n==36||n==40||n==44) cout<<"YES"<<endl<<"6 10 15 "<<n-31<<endl;
        else cout<<"YES"<<endl<<"6 10 14 "<<n-30<<endl;
    }
    return 0;
}
```

---

## 作者：HC20050615 (赞：1)

//蒟蒻第一次参加CF比赛，希望管理员通过此篇题解
# 题意分析 
定义：近似素数为两个不同质数之积为近似素数
给定一个整数n，将其分解为3个近似素数与一个任意自然数（四个数互不相等）
# 思路
本题只需要提供一种分解方法。 

我们可以令这三个近似素数为最小的三个6、10、14（前面的属于小，后面的数就有更大的选择空间），然后第四个数为k=n-6-10-14

如果n<=6+10+14=30,则无论如何也不可能得到答案

但是,如果得到的第四个数k==6\10\14时（即n=36、40、44）怎么办呢?
我们可以特判。

当n=36、40、44时，把14换成15，这样就不会重复了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n;
		cin>>n;
		if(n<=30)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			if(n==36||n==40||n==44)
			{
				cout<<"YES"<<" "<<6<<" "<<10<<" "<<15<<" "<<n-31<<endl;
			}
			else
			{
				cout<<"YES"<<" "<<6<<" "<<10<<" "<<14<<" "<<n-30<<endl;
			}
		}
	}
	return 0;
}
```



---

## 作者：PanH (赞：1)

 WA  了好几发，身败名裂。
 
 ## 题意
 
 定义两个不同质数乘积为**近质数**。你需要判断给出的一个正整数是否能分解为四个不同的正整数之和，其中至少三个为近质数，并输出方案。
 
 ## 题解
 
 首先发现最小的三个近质数为 $6,10,14$ 。所以小于等于 $30$ 的数肯定不符要求。
 
 那么答案不就是 $6,10,14,n-30$ ？注意到要分解为不同的四个正整数，若 $n-30$ 与之前的数重复则会出问题。
 
 考虑特判这种情况，另一个比较小的近质数是 $15$ 。产生重复时，我们把 $14$ 换成 $15$，就可以完美解决问题。
 
 code：
 ```
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
int main()
{
	int T;read(T);
	while(T--)
	{
		int n;read(n);
		if(n<=30)	puts("NO");
		else
		{
			int x=n-30;
			if(x==14||x==6||x==10)
			{
				puts("YES");
				cout<<"6 10 15 "<<n-31<<endl;
			}
			else
			{
				puts("YES");
				cout<<"6 10 14 "<<n-30<<endl;
			}
		}
	}
}
```


---

## 作者：fls233666 (赞：0)

题意简述：

定义由两个不同质数相乘得到的数叫做“近似质数”，现在给出一个数字 $n$，求这个 $n$ 是否可以被拆成四个不同的数的和，其中至少有三个数是“近似质数”。


------------


~~在现场，想了很久，然后发现自己很菜~~。

既然它对于最后一个数没有任何要求，那可以直接**手算出最小的三个“近似质数”，把 $n$ 减掉这三个数**即可。

但是，题目有要求，要**四个不同的数**。显然，对于一部分的数字$n$，再减掉最小的三个“近似质数”之后，得到的数字会与最小的三个“近似质数”重复。为了避免这个问题，我们的解决方案如下：

**算出第四小的“近似质数”，然后替换第三小的“近似质数”，更新结果。**

于是到这里问题就被解决了，下面是我~~在现场~~的代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define rgt register int
using namespace std;
int main(){
	int test,n,c1=6,c2=10,c3=14,c4=15,dn;
   //c1,c2,c3,c4分别是前四小的近似质数
	scanf("%d",&test);
	while(test--){
		scanf("%d",&n);
		c1=6;
		c2=10;
		c3=14;
        
		if(c1+c2+c3>=n)  //如果n比最小的三个数还要小，无解
			printf("NO\n");
		else{
			dn=n-c1-c2-c3;  //否则计算第四个数
			if(dn==c1||dn==c2||dn==c3){  //如果重复，替换其中一个数
				dn--;
				c3=c4;
			}
			printf("YES\n%d %d %d %d\n",c1,c2,c3,dn);  //得到答案
		}
	}
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 前言
安利自己首场 CF 的[游记](https://www.luogu.com.cn/blog/PsephurusGladius-zdx/codeforces-round-660-div-2-post)（其实啥也没写）。

## 题目分析
开始的时候把我吓了一跳——差点以为要筛出所有的 Nearly Prime 再进行求解。后面冷静下来后发现只需要给出一组方案即可。那么我们可以贪心地选择最小的三个 Nearly Prime（$6,10,14$）和另一个数搭配凑出当前数。若当前数不大于这三个数之和，显然是不可能凑出的。  

但需要注意四个数要互不相同。当第四个数与这三个数中某一个相同时，只需要把 $14$ 换作 $15$ 再进行求解即可。

## 代码
```cpp
#include<cstdio>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n<=30)
		{
			puts("NO");
			continue;
		}
		else if(n==36)
		{
			puts("YES");
			printf("%d %d %d %d\n",6,10,15,5);
		}
		else if(n==40)
		{
			puts("YES");
			printf("%d %d %d %d\n",6,10,15,9);
		}
		else if(n==44)
		{
			puts("YES");
			printf("%d %d %d %d\n",6,10,15,13);
		}
		else
		{
			puts("YES");
			printf("%d %d %d %d\n",6,10,14,n-30);
		}
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

题目大意就是判断给出的一个正整数是否能分解为四个不同的正整数之和，其中至少三个为nearly prime。nearly prime是两个不同质数的积。

易知最小的三个nearly prime为$6=2\times3,10=2\times5,14=2\times7$，而题目中对第四个数没有限制，只是与已有的数不同，那么对于每个$n$，若$n\le 30(=6+10+14)$则输出NO，否则肯定输出YES，并输出$6$ $10$ $14$ $(n-30)$。

要求输出的四个数不同，我们只需在$n=36/40/44$时特判一下，把$14$换成$15=3\times5$，输出$6$ $10$ $15$ $(n-31)$即可。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&x);
		if(x<31)
		    printf("NO\n");
		else
		{
			printf("YES\n");
			int y=x-30;
			if(y==6)
				printf("5 6 10 15\n");
			else if(y==10)
			    printf("6 9 10 15\n");
			else if(y==14)
			    printf("6 10 13 15\n");
			else
			    printf("6 10 14 %d\n",y);
		}
	}
	return 0;
}
```
~~我竟然第一次提交时没输出YES，还好第一个就WA了不扣分。~~

---

## 作者：wmy_goes_to_thu (赞：0)

首先，$6,10,14$ 是最小的三个 Nearly Prime。如果 $a \leq 30$，显然是不行的。那么如果 $a \gt 30$，可以构造一组解 $6,10,14,a-30$，但是如果 $a=36,40,44$，会有重复的情况，所以我们在这三个情况采用 $6,10,15,a-31$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int np[31]={0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0};
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a;
		cin>>a;
		if(a>30)
		{
			if(a==36)
			{
				cout<<"YES"<<endl<<"5 6 10 15"<<endl;
			}else if(a==40)
			{
				cout<<"YES"<<endl<<"6 10 15 9"<<endl;
			}else if(a==44)
			{
				cout<<"YES"<<endl<<"6 7 10 21"<<endl;
			}else cout<<"YES"<<endl<<"6 10 14"<<" "<<a-30<<endl;
		}else cout<<"NO"<<endl;
	}
	return 0;
}
```

---

