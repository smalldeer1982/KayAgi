# [ABC071C] Make a Rectangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc071/tasks/arc081_a

太さが無視できる棒が $ N $ 本あります． $ i $ 番目の棒の長さは $ A_i $ です．

すぬけ君は，これらの棒から $ 4 $ 本の異なる棒を選び，それらの棒を辺として長方形（正方形を含む）を作りたいです． 作ることができる最大の長方形の面積を求めてください．

## 说明/提示

### 制約

- $ 4\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ A_i $ は整数

### Sample Explanation 1

$ 1\ \times\ 2 $ の長方形を作ることができます．

### Sample Explanation 2

長方形を作ることはできません．

## 样例 #1

### 输入

```
6
3 1 2 4 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
10
3 3 3 3 4 4 4 5 5 5```

### 输出

```
20```

# 题解

## 作者：peppaking8 (赞：7)

## 思路：
此题的大意是：让你在 $N$ 个木棒中选出 $4$ 个，长度分别为 $a,a,b,b$，使得 $a\times b$ 取到最大值。

$a\times b$取到最大值，也就是 $a,b$ 分别取到最大值。考虑所有满足条件（即有两个及以上相同长度的）的长度，取**最大值和次大值**即可。

这道题就做完了吗？没有！

仔细看题：用这些棒子做个矩形 **（包括正方形）**。正方形是什么意思？四个棒子长度都相同！

这样，就判断如果一个长度的棒子大于等于四根，就算两个。

由于棍子的长度 $\in 1-10^9$，所以不能针对棍子的长度进行处理。所以考虑**排序**。

如果 ```a[i]=a[i-1]```，那么就说明这个长度有两个及以上的棍子。将它们标记。如果还存在 ```a[i-2]=a[i-3]``` ，那么这个长度就算两次。

还有一种写起来比较短的方法：**倒序遍历**，如果判断出 ```a[i]=a[i-1]```，则循环中 ```i=i-1```，就不用考虑重复的情况了。

## CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
//要开 long long 哦
using namespace std;
const int N=100005;
int n;
int a[N];
int cnt[3],tot=0;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);//从小到大排序
	for(int i=n;i>=1;i--){//倒序遍历
		if(a[i]==a[i-1]){
			cnt[++tot]=a[i];
			i--;
			if(tot==2) break;//找到了最大和次大值，退出循环
		}
	} 
	printf("%lld\n",cnt[1]*cnt[2]);
    //如果没有最大值或次大值，则cnt[1]和cnt[2]中会有一个是0，乘起来就是0，满足题目要求。不用特判。
	exit(0);//程序拜拜~
}
```

写题解不容易，别忘了点一个赞再走啊~

---

## 作者：reclusive (赞：1)

这道题其实不算太难。

先来看看题目意思。

他说给你很多根棒子，让你从中选四个棒子来组成矩形。

我们知道，矩形是对边相等的，所以我们只需要找长度最长和长度第二长的棒子分别两根。

所以这题思路就很明显了。

一开始我想用桶来记录个数，但我看了一下数据范围。

1 <= A <= 10^9。

这个范围用桶肯定是不行的。

所以我改用了快排。

排序后，我们从后面开始枚举（因为是从小到大排序的）。

如果前后两个数相等，就给他记录下来。

但是我们注意到。

题目说的是：用这些棒子做个矩形(包括正方形)。

也就是还包括四根棒子的情况。

所以我们判断完相邻两根棒子后，还应该 I--。

这样的话。

我们一开始 1 和 2 进行比较。

I-- 后 3 和 4 进行比较。

就可以有效判断出正方形。

注意：样例 2 中是没有输出的，这里我们要输出 0。

这题还是比较简单，应该看得懂吧。

# AC Code：

```cpp
#include<algorithm>//快排的头文件 
#include<iostream>
using namespace std;
long long A[100001],ANS[100001];//数据很大，只能用longlong 
int main()
{
	int N,X=0;
	cin>>N;
	for(int I=1;I<=N;I++)
	{
		cin>>A[I];
	}//输入部分 
	sort(A+1,A+N+1);//进行从大到小的排序 
	for(int I=N;I>=1;I--)//从后开始枚举 
	{
		if(A[I]==A[I-1])//当前的棒子有至少两根可以取 
		{
			X++;
			ANS[X]=A[I];//可以取就记录下来 
			I--;//减1后可以判断够不够4根棒子 
		}
		if(X==2)
		{
			break;//够两组就可以跳出循环 
		}
	}
	cout<<ANS[1]*ANS[2]<<endl;//输出部分 
	return 0;
}
```


---

## 作者：hyc1026 (赞：0)

直接做就行了，一个排序搞定。

在循环内查找有没有一样的即可，从大到小查找。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[100010];
int maxn[3];

bool cmp(int x,int y){ return x > y; } //cmp从大到小排序

int main()
{
    int n;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+1,a+n+1,cmp);
    int have = 0;
    for(int i=1; i<=n; i++)
    {
        if(a[i] == a[i+1]) //如果相等：
        {
            have++; //计数
            maxn[have] = a[i]; //标记
            i++; //跳过i+1，避免重复
        }
        if(have == 2) break; //个数满2，跳出循环
    }
    cout << 1ll * maxn[1] * maxn[2] << endl; //开 long long
    return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
题目要我们构成一个长方形，我们需要选两对相同长度的小木棍。而他又需要我们求出面积最大的。所以只需要从输入的数中选出两对相同的数，且这两对数的数值尽量的大就可以达到要求了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[100005],a[100005],p,q;//注意要开long long
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
    	cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--){
		if(a[i]==a[i+1]){
			if(p){
				q=a[i];
				break;
			}
			else{
				p=a[i];
            }
			a[i]=a[i+1]=0;
		}
	 } 
	cout<<p*q<<endl;
} 

```

---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2696)

### 思路

这个题目还是比较简单的，只要知道长方形对边相等这个性质就看可以做了。

显然，要构成一个长方形，我们需要选两对相同长度的小木棍。而他又需要我们求出面积最大的，所以简单来说，就是从 $a$ 序列中选出两对相同的数，且这两对数的数值尽量的大。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
//int vis[100005];
long long a[100005];
long long p,q;//不开long long 见祖宗
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	cin>>a[i];//输入
	sort(a+1,a+n+1);//排序
	for(int i=n;i>=1;--i)//从大到小枚举，是的先枚举道德都是最大的
	{
		if(a[i]==a[i+1])//如果这两个数相同
		{
        //对p,q(长和宽)分别赋值
			if(p)
			{
				q=a[i];
				break;
			}
			else
			p=a[i];
			a[i]=a[i+1]=0;//这两个数已经选出，标记为0
		}
	}
	cout<<p*q<<endl;//直接输出长×宽
} 
```

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

题目所要求的东西：在一堆棒子中找到两对棒子，要求是每对长度相等，然后棒子长度的乘积最大是多少。

知道了题目要求什么，代码就很简单了。首先将所有棒子进行排序，找出两对长度相等且尽量长的棒子，然后将他们的长度相乘，即为所求的最大面积。

思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,a[100010],b1,b2;//变量定义
int main()
{
	cin>>n;//读入有多少根棒子
	for(int i=1; i<=n; i++)scanf("%lld",&a[i]);//读入每根棒子的长度
	sort(a+1,a+1+n);//将棒子长度由小到大排序
	for(int i=n; i>1; i--)//从最长那一根棒子开始找
	{
		if(a[i]==a[i-1]&&a[i]>b1)//第一对长度相等且尽量长的棒子
		{
			b1=a[i],i--;
			continue;
		}
		if(a[i]==a[i-1])//第二对长度相等且尽量长又不与第一对棒子重复找的棒子
		{
			b2=a[i];
			break;
		}
	}
	printf("%lld\n",b1*b2);//输出最大面积，记得换行
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：大头leo (赞：0)

### 思路：
   题目就是说：~~有一个人闲得慌~~，找出了n个小棒，想做一个**最大**的矩形。矩形呢有长和宽。也就是你要找出两个同样长的小棒，两组。且最大即可。
   
   我们只需要给小棒排个序，然后**从大到小**开始找就可以了，若没找到肯定就是构造不出矩形来，输出0。
   
### 注意点：
1. 矩形包含正方形，也就是四个相同的小棒，但是依然可以分成两组，按照这种思路，不需要特殊判断正方形。

1. 由于是从大到小找的，所以只需要找出前两组相同小棒即可，它们必然是最大的（包括正方形），找出后就能结束循环了。

1. 因为可能存在三个小棒相同的情况，找出第一组后循环变量i就需要-1。而找出第一组后需要作标记，防止重复计算。（本条请结合程序阅读）

1. 输出时，若没找到输出0即可。而此时第一组小棒或第二组小棒至少有一个是空的，也就是0。所以他们相乘起来任然是0，符合题意，无需特判。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100001],n,t1,t2,f=1;		//t1,t2分别为矩形两条边的长度，f为标记。 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];	//正常读入排序。 
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--)
	{
		if(a[i]==a[i-1]&&f==0)		//第二次找到，判断标记后记录，即可退出循环。 
		{
			t2=a[i];
			break;
		}
		if(a[i]==a[i-1]&&f==1)		//第一次找到，i--并标记。 
		{
			t1=a[i];
			i--;
			f=0;
		}
	}
	cout<<t1*t2; 		//注意点四讲过。 
}	

```




---

## 作者：zfn07 (赞：0)

此题的思路是：先从大到小排序，接着判断哪两对棒子长度相等，然后求出面积即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int cmp(int x,int y){//使sort函数从大到小排序
	return x>y;
}
int main(){
	int n,a[100005],i;
	long long ansc=0,ansk=0;//ansc表示长方形的长，ansk表示长方形的宽。(一定要用long long!!!)
	bool use[100005]={0};//use数组用来判断第i根木棍是否已被使用。
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,cmp);//排序
	for(i=1;i<=n;i++){
		if(a[i]==a[i-1]&&use[i-1]==0){//如果第i根木棍和第i-1根木棍长度一样且都没被使用
			if(ansc!=0){//如果ansc已经存储了值
				ansk=a[i];//存储宽的长度
				cout<<ansc*ansk;//输出面积
				return 0;
			}
			else {
				use[i-1]=1;//标注i-1已被使用
				use[i]=1;//标注i已被使用
				ansc=a[i];//存储宽的长度
			}
		}
	}
	cout<<ansc*ansk;//如果无法组成面积，可输出ansc*ansk。因为ansk一定为0，所以ansc*ansk=0。
	return 0;
}
```


---

## 作者：Vector_ (赞：0)

思路：

因为矩形对边相等

所以可以先排序，然后从大到小判断有没有相等的两对整数

如果有两对那么显然它一定是最大矩形的两对对边，进而可以求出面积

如果没有则显然无法构造矩形。

上$AC$代码:

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010];
int main()
{
    int n;
    long long ans,a1=-2,a2=-2;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];//读入
    sort(a+1,a+1+n);
    for(int i=n;i>=2;i--) if(a[i]==a[i-1]) {a1=a[i],a[i]=a[i-1]=-1;break;}//设置为-1表示去掉，不在第二次里面再找到一次
    for(int i=n;i>=2;i--) if(a[i]==a[i-1]&&a[i]!=-1) {a2=a[i];break;}
    if(a1!=-2&&a2!=-2) cout<<a1*a2<<endl; else cout<<0<<endl;//无解输出0
    return 0;//结束
}
```

---

