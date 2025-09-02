# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots,p_n] $ , which contains every integer from $ 1 $ to $ n $ (inclusive) and, moreover, each number appears exactly once. For example, $ p=[3,1,4,2,5] $ is a permutation of length $ 5 $ .

For a given number $ n $ ( $ n \ge 2 $ ), find a permutation $ p $ in which absolute difference (that is, the absolute value of difference) of any two neighboring (adjacent) elements is between $ 2 $ and $ 4 $ , inclusive. Formally, find such permutation $ p $ that $ 2 \le |p_i - p_{i+1}| \le 4 $ for each $ i $ ( $ 1 \le i < n $ ).

Print any such permutation for the given integer $ n $ or determine that it does not exist.

## 样例 #1

### 输入

```
6
10
2
4
6
7
13```

### 输出

```
9 6 10 8 4 7 3 1 5 2 
-1
3 1 4 2 
5 3 6 2 4 1 
5 1 3 6 2 4 7 
13 9 7 11 8 4 1 3 5 2 6 10 12```

# 题解

## 作者：天南星魔芋 (赞：8)

提供一种船新的打表的做法。


------------

菜鸡的我数论并不好，所以看了半天自己没有推出其他大佬所说的那个**结论，

不过倒是找到了另一种线性构造方案，

手算一下小数据，不难发现 $n==5$ 时刚好可以无限循环（如下图），

![](https://cdn.luogu.com.cn/upload/image_hosting/fv9gayb7.png)


循环节长度为 $5$ 循环节为 $(1,3,5,2,4)$，

两个连接时就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/36o89rny.png)


那么当 $n\%5==0$ 时，我们就解决问题了。

当 $n\%5!=0$ 时，我们分类讨论出最后一个循环节的方案打表，

讨论 $n\%5!=0$ 的情况：

* $n\%5==1$ 时，因为只有一个 $1$，且 $1$ 与前一个数符合要求，所以直接加后面就行了，此时循环节是 $(1)$。

* $n\%5==2$ 时，因为多出来的 $2$ 个数不可能自己排列后符合要求，所以要借用前一个循环节，通过手推可以求出为 $(1,3,7,5,2,4,6)$，当然若前面没有循环节的话$(n<5)$，就不合法。

* $n\%5==3$ 时，因为多出来的 $3$ 也不可能自己排列后符合要求，所以要借用前一个循环节，通过手推可以求出为 $(1,3,7,5,2,4,6,8)$，当然若前面没有循环节的话$(n<5)$，就也不合法。

* $n\%5==4$ 时，手推多出来的 $4$ 可以自己排列后符合要求，通过手推可以求出为 $(2,4,1,3)$。


总结时发现，有的要前面的循环节而有的不用，那我们都要它要前面的循环节就好了（好算呗），对于 $n<5$ 的数据，特判就行了。

总结后：

* $n<5$

	* $n\%5==0$ $()$ 为空（数据不存在）

	* $n\%5==1$ $(1)$（数据不存在）

	* $n\%5==2$ $(-1)$（不存在方案）

	* $n\%5==3$ $(-1)$（不存在方案）

	* $n\%5==4$ $(2,4,1,3)$



* $n>=5$

	* $n\%5==0$ $(1,3,5,2,4)$

	* $n\%5==1$ $(1,3,5,2,4,6)$

	* $n\%5==2$ $(1,3,7,5,2,4,6)$

	* $n\%5==3$ $(1,3,7,5,2,4,6,8)$

	* $n\%5==4$ $(1,3,5,2,4,7,9,6,8)$


$$$$



#### code:




```cpp
#include<bits/stdc++.h>
using namespace std;
int base[20]={0,1,3,5,2,4};//表×5 
int base6[20]={0,1,3,5,2,4,6};
int base7[20]={0,1,3,7,5,2,4,6};
int base8[20]={0,1,3,7,5,2,4,6,8};
int base9[20]={0,1,3,5,2,4,7,9,6,8};
//------------------------------------------------//表的输出 ↓ 
void base_print(int x){
	for(int i=1;i<=5;i++){
		printf("%d ",base[i]+x);
	}
}
void print_6(int x){
	for(int i=1;i<=6;i++){
		printf("%d ",base6[i]+x);
	}
}
void print_7(int x){
	for(int i=1;i<=7;i++){
		printf("%d ",base7[i]+x);
	}
}
void print_8(int x){
	for(int i=1;i<=8;i++){
		printf("%d ",base8[i]+x);
	}
}
void print_9(int x){
	for(int i=1;i<=9;i++){
		printf("%d ",base9 [i]+x);
	}
}
//------------------------------------------------//表的输出 ↑ 
void js(int x){
	if(x<5){//若小于5 
		if(x==1)printf("1");//x为 1 
		if(x==4)printf("3 1 4 2");// x为 4 
		else printf("-1");//不成立 
	}
	int y=0;
	while(y+10<=x){//还不到最后循环节 
		base_print(y);//每次输出 base 基础循环节 
		y+=5;
	}
	int pd=x-y;
	if(pd==5)base_print(y);// 恰好为 5，直接输出 base 就好了 
	else if(pd==6)print_6(y);//分类打表 
	else if(pd==7)print_7(y);
	else if(pd==8)print_8(y);
	else if(pd==9)print_9(y);
}
int main(){
	int T;
	cin>>T;//读入 
	while(T){
		T--;
		int n;
		scanf("%d",&n);
		js(n);//计算 
		putchar('\n');//记得输出换行 
	}
}
```





---

## 作者：奇米 (赞：7)

## $\mathrm{CF1352G\ Special \ Permutation }$


### **题目意思**

* [CF1352G](https://www.luogu.com.cn/problem/CF1352G)

### $\mathrm{Sol}$

* 一道$sb$构造题，不知道出$G$什么用意

* 考虑到一个特殊性质:$|a_i-a_{i-1}|∈[2,4]$。我们不需要去构造最优情况。我们分奇偶来考虑。

* 对于$n$为偶数，我们首先把所有偶数从大往小选，即$n,n-2..2$。然后我们为了满足$|a_i-a_{i-1}|∈[2,4]$并且要填奇数，所以我们先填$5$,再从小到大填上去,即$1,3,7...n-1$（所以说$\leq 4$这个性质很重要）。

* 那么对于$n$为奇数同理。以及对于$n\leq 4$特判（因为此时奇数取不到$5$）

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

int Q,n,a[10005],cnt;

int main()
{
	Q=read();
	for (;Q--;)
	{
		n=read();
		cnt=0;
		if(n==4)
		{
			puts("3 1 4 2");
			continue;
		}
		if(n<=3) 
			printf("-1");
		else 
		{
			if(n&1)
			{
				for ( int j=n;j>=1;j-- ) 
					if(j&1) a[++cnt]=j;
				a[++cnt]=4,a[++cnt]=2;
				if(n>=6)
					for ( int j=6;j<=n;j++ ) 
						if(j%2==0) a[++cnt]=j;
			}
			else 
			{
				for ( int j=n;j>=1;j-- ) 
					if(j%2==0) a[++cnt]=j;
				a[++cnt]=5,a[++cnt]=1,a[++cnt]=3;
				if(n>=7)
					for ( int j=7;j<=n;j++ ) 
						if(j&1) a[++cnt]=j;	
			}
			for ( int i=1;i<=cnt;i++ ) printf("%d ",a[i]);
		}
		puts(""); 
	}
}
			
				
			
```


---

## 作者：小蒟蒻皮皮鱼 (赞：6)

## CF1352G Special Permutation
一道巧妙的构造题。
首先对于$n<4$，经过手算可以发现是没有这样的一组数据的。那么也就是找找$n \geq 4$的情况。

注意到这道题构造的特点是$2\leq|p_i-p_{i+1}|\leq 4$。那么$2$和$4$是什么呢？构造题按照套路奇偶性一般都是要考虑的。那么$2$其实就是相邻两个奇(偶)数的差，$4$也就是中间隔着一个的两个奇(偶)数的差。

举个例子，当$n=9$时，奇数有$1,3,5,7,9$，偶数有$2,4,6,8$。不妨考虑先把奇数从小到大排好，这样每两个数的差都是$2$，满足条件。如果我们之后再将偶数从大到小排序，构成$1,3,5,7,9,8,6,4,2$，中间两个数的差就是$1$，显然不满足。这时如果我们将$6,8$交换位置，原数列变成了$1,3,5,7,9,6,8,4,2$就可以了。

当$n=10$时，奇数有$1,3,5,7,9$，偶数有$2,4,6,8,10$。这时先排奇数不行了，我们考虑先排偶数再排奇数。$1,3,5,7,9,10,8,6,4,2$。这样的话按照之前的策略交换$8,10$也是可以满足的，交换以后的数列变成$1,3,5,7,9,8,10,6,4,2$

于是总的策略就是先分奇偶，再按照上面的方法进行构造。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
void work1(int x)
{
	for(int i = 2; i <= x; i += 2) printf("%d ", i);
	printf("%d %d ", x - 3, x - 1);
	for(int i = x - 5; i >= 1; i -= 2) printf("%d ", i);
	printf("\n");
}
void work2(int x)
{
	for(int i = 1; i <= x; i += 2) printf("%d ", i);
	printf("%d %d ", x - 3, x - 1);
	for(int i = x - 5; i >= 2; i -= 2) printf("%d ", i);
	printf("\n");
}
int main()
{
	scanf("%d", &t);
	while(t --)
	{
		int n;
		scanf("%d", &n);
		if(n < 4) printf("-1\n");
		else
		{
			if(n % 2 == 0) work1(n);
			if(n % 2 == 1) work2(n);
		}
	}
}
```

---

## 作者：SpeedStar (赞：5)

### 算法分析
一道比较水的构造题。

首先$n<4$时无解。否则，
先降序输出所有奇数，再输出4和2，最后升序输出其他的偶数。


### C++代码
```cpp
#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		if (n < 4) {
			cout << -1 << '\n';
			continue;
		}
		for (int i = n; i >= 1; --i) {
			if (i & 1) cout << i << ' ';
		}
		cout << 4 << ' ' << 2 << ' ';
		for (int i = 6; i <= n; i += 2) {
			cout << i << ' ';
		}
		cout << '\n';
	}
	
	return 0;
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定义一个 $n$，输出 $1-n$ 的一个排列满足任意两个数的差 $∈ [2,4]$。
若无满足条件的排列输出 $-1$。

#### 题目分析


------------
本题唯一的难点在于如何排列这 $n$ 个数字使得相邻的数字的差满足题设条件。

观察样例并不能很好的发现规律，而暴力枚举的复杂度让人望而却步。

想要解决一道构造题就要从题干中找出关键信息并将关键信息整合成对于解题有帮助的线索。首先从这一列数的性质入手可以发现满足两个数字的差 $\ge 2$ 的数字组合中最容易想到的就是奇数与偶数天生的性质。很容易便可以进一步想到要分别枚举 $\le n$ 的所有的奇数和偶数，但是如何处理奇数和偶数的边界成了解决此题的最大障碍。

分别考虑 $n = 7$ 和 $n = 8$ 的情况：

- 当 $n = 7$ 时，$\le n$ 的奇数有 $1,3,5,7$，偶数有 $2,4,6$。如果直接将这两个序列拼接起来显然是不行的，我们可以考虑将这两个序列其中的一个翻转过来例如翻转前一个序列变成 $7,5,3,1$ 但是这时候直接和第二个序列拼接也是不行的，所以我们考虑两个不相邻的奇数和偶数的差为 $3$ 这一性质可以想到将未翻转的序列交换前两个数字所以 $n = 7$ 的时候，序列就可以为 $7,5,3,1,4,2,6$

- 当 $n = 8$ 时，沿用上述方式，奇数有 $1,3,5,7$，偶数有 $2,4,6,8$。序列可以变为 $7,5,3,1,4,2,6,8$。

到这里我们已经完成了此题的绝大部分，但是还有一种 $-1$ 的情况没有考虑，根据我们构造的方式，当 $n \le 3$ 时无论如何都不可能满足题设条件，故可以直接输出 $-1$。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 10010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int main(){
	int T = read();
	while(T--){
		int n = read();
		if(n < 4){
			printf("-1\n");
			continue;
		}
		if(n % 2 == 0){
			for(int i = 2;i <= n;i += 2){
				printf("%d ",i);
			}
			printf("%d %d ",n-3,n-1);
			for(int i = n-5;i >= 1;i -= 2){
				printf("%d ",i);
			}
			printf("\n");
		}
		if(n % 2 == 1){
			for(int i = 1;i <= n;i += 2){
				printf("%d ",i);
			}
			printf("%d %d ",n-3,n-1);
			for(int i = n - 5; i>= 2;i -= 2){
				printf("%d ",i);
			} 
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：dingcx (赞：1)

~~Div4 就是水啊~~

## 思路

看到差的绝对值可以 $=2$，就想到可以先**从 $1$ 顺到 $n$**，然后**顺回来**。

但是这样显然不行，以 $n=6$ 为例，$[1,3,5,6,4,2]$ 中的 $[5,6]$ 不满足要求。但这也很好处理，把这里的 $3$ 和 $5$ **调一下位置**就好了，这样 $5-1,5-3,6-3$ 都在 $[2,4]$ 范围内。

总结：初始点是与 $n$ **不同奇偶的最小数**（$n$ 是奇数就是 $2$，偶数就是 $1$），然后每次 $+2$，**最后两个是 $n-1$ 和 $n-3$**，然后从 $n$ 往下减就好了。

注意 $n=2,3$ 要**特判** $-1$。

## 代码

```cpp
#include<cstdio>
using namespace std;
int read(){//快读
	int num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
int main(){//主函数
	int T=read();
	while(T--){
		int n=read();
		if(n==2||n==3){printf("-1\n");continue;}//特判
		for(int i=n%2+1;i<n-4;i+=2) printf("%d ",i);//从 1 到 n，注意初始点结束点
		printf("%d %d ",n-1,n-3);//输出改变顺序的两个
		for(int i=n;i>0;i-=2) printf("%d ",i);//从 n 到 1
		printf("\n");
	}
	return 0;//华丽结束
}
```
别忘了点个赞哦

---

## 作者：Refined_heart (赞：1)

题目大意：求一个$n$的排列使得相邻两个数的差距在$2\to 4$之间。

$\text{Solution:}$

对于小的数据我们直接输出即可。我们直接讨论大于等于$6$的数据。

我们可以发现一个规律：$5,1,3,6,2,4$这样的排列是刚好满足题意的。而且，我们可以在$5$后面按照顺序增加奇数，在$4$后面按照顺序增加偶数，这样恰好满足题意。

其它的手算就可以了。代码中也有。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200100];
vector<int>Ans;
int main(){
	scanf("%d",&T);
	while(T--){
		Ans.clear();
		scanf("%d",&n);
		if(n==2||n==3){
			puts("-1");
			
			continue;
		}
		if(n==4){
			printf("3 1 4 2\n");
			continue;
		}
		if(n==5){
			printf("3 1 5 2 4\n");
			continue;
		}
		for(int i=n;i>=1;--i){
			if(i%2==1&&i!=3&&i!=1)Ans.push_back(i);
			if(i==3){
				Ans.push_back(1),Ans.push_back(3);
				break;
			}
		}
		Ans.push_back(6);
		Ans.push_back(2);
		Ans.push_back(4);
		for(int i=8;i<=n;++i){
			
			if(i%2==0)Ans.push_back(i);
		}
		for(int i=0;i<Ans.size();++i)cout<<Ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：b6e0_ (赞：1)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/G) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352G) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352G)

首先，$n<4$时无解。

对着样例看了好久，终于发现一种方法：先倒序输出$n$~$6$之间的奇数，然后输出$3$ $1$ $4$ $2$（$n=4$时的解决方法），然后正序输出$6$~$n$之间的偶数。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,i;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n<4)//特判-1
		{
			cout<<"-1\n";
			continue;
		}
		if(n&1)//分奇偶
			for(i=n;i>4;i-=2)
				cout<<i<<' ';
		else
			for(i=n-1;i>4;i-=2)
				cout<<i<<' ';
		cout<<"3 1 4 2 ";
		for(i=6;i<=n;i+=2)
			cout<<i<<' ';
		cout<<endl;
	}
	return 0;
}
```
其实这种方法等价于：先倒序输出$n$~$1$之间的奇数，然后输出$4$ $2$，最后正序输出$6$~$n$之间的偶数。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,i;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n<4)//特判-1
		{
			cout<<"-1\n";
			continue;
		}
		if(n&1)//分奇偶
			for(i=n;i>0;i-=2)
				cout<<i<<' ';
		else
			for(i=n-1;i>0;i-=2)
				cout<<i<<' ';
		cout<<"4 2 ";
		for(i=6;i<=n;i+=2)
			cout<<i<<' ';
		cout<<endl;
	}
	return 0;
}
```
时间复杂度都为$O(tn)$。

---

## 作者：ttq012 (赞：0)

**Solution**

简单的构造题。

当 $n = 1$ 的时候，序列为 $1$。

当 $n = 2, 3$ 的时候，序列不存在。

当 $n = 4$ 的时候，序列为 $\text{2 4 1 3}$。

当 $n = 5$ 的时候，序列为 $\text{1 3 5 2 4}$。

否则，我们可以找规律：当 $n$ 为奇数的时候，我们可以先输出所有的奇数，然后应该输出偶数了。所以我们可以先输出 $n - 5$，然后输出 $n - 3$，然后输出 $n - 7$，最后输出剩下的偶数即可。同理 $n$ 为偶数的时候，我们可以先输出所有的奇数，然后输出偶数的时候，先输出 $n - 4$，然后输出 $n$，然后输出 $n - 2$，然后输出 $n - 6$，最后输出剩下的偶数即可。这样做的巧妙在于：我们跳着输出一部分偶数，巧妙的将较大的偶数全部填完，最后输出剩下较小的偶数。

时间复杂度：$\mathcal O(T\cdot n)$。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n;
        cin >> n;
        if (n == 1)
            puts("1");
        else if (n == 2)
            puts("-1");
        else if (n == 3)
            puts("-1");
        else if (n == 4)
            puts("2 4 1 3");
        else if (n == 5)
            puts("1 3 5 2 4");
        else {
            int i;
            if (n & 1) {
                for (i = 1; i <= n; i += 2)
                    cout << i << ' ';
                i -= 2;
                cout << i - 3 << ' ' << i - 1 << ' ';
                i -= 5;
                for (; i >= 2; i -= 2)
                    cout << i << ' ' << ' ';
                cout << '\n';
            } else {
                for (i = 1; i <= n; i += 2)
                    cout << i << ' ';
                i -= 2;
                cout << i - 3 << ' ' << i + 1 << ' ' << i - 1 << ' ';
                i -= 5;
                for (; i >= 2; i -= 2)
                    cout << i << ' ';
                cout << '\n';
            }
        }
    }
    return 0;
}

```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1600}$
---
### 解题思路：

第一反应是用连续的奇数和偶数进行一个比较一般的构造。

由于到顶之后切换点不一样，就先随便考虑一个稍微大一点的偶数和奇数。

例如 $10$ 和 $11$，分别写一种可行的构造方案： 

$10$：$2,4,6,8,10,7,9,5,3,1$。

$11$：$1,3,5,7,9,11,8,10,6,4,2$。

然后最高点的转化就很清楚了。

不过这样的一个转化需要用到 $x-5$，特殊讨论一下 $4$ 和 $5$ 就行了。

注意 $n\le3$ 的时候无解。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		if(n<=3){printf("-1\n");continue;}
		if(n==4){printf("3 1 4 2\n");continue;}
		if(n==5){printf("1 3 5 2 4\n");continue;}
		if(n&1){
			for(int i=1;i<=n;i+=2)printf("%d ",i);
			printf("%d %d %d",n-3,n-1,n-5);
			for(int i=n-7;i>=1;i-=2)printf(" %d",i);
			printf("\n");
		}
		else{
			for(int i=2;i<=n;i+=2)printf("%d ",i);
			printf("%d %d %d",n-3,n-1,n-5);
			for(int i=n-7;i>=1;i-=2)printf(" %d",i);
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：Cutest_Junior (赞：0)

## 题解 CF1352G 【Special Permutation】

### 题意

+ 给出 $n$，求一个长度为 $n$ 的排列，要求相邻两个元素绝对差大于等于 $2$ 小于等于 $4$；
+ 多组数据，$n\le1000$。

### 做法

特判 $n<4$。

因为绝对差大于等于 $2$，容易想到先奇数后偶数，具两个例子：  
10：1 3 5 7 9 6 10 8 4 2   
9：1 3 5 7 9 6 8 4 2

具体实现方法比较难描述，可以看代码。

特批 $n=4$。

### 代码

```cpp
#include <cstdio>

using namespace std;

void run() {
	int n;
	scanf("%d", &n);
	if (n < 4) {
		printf("-1\n");
		return;
	}
	if (n == 4) {
		printf("3 1 4 2\n");
		return;
	}
	int i;
	for (i = 1; i <= n; i += 2) {
		printf("%d ", i);
	}
	i -= 2;
	printf("%d ", i - 3);
	if (i < n) {
		printf("%d ", i + 1);
	}
	printf("%d ", i - 1);
	for (i -= 5; i; i -= 2) {
		printf("%d ", i);
	}
	printf("\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：btng_smith666 (赞：0)

复读：简单构造题（

不过确实没什么好说的，思路就是看样例找规律，首先只要读懂题了就能知道：如果 $n\in\{2,3\}$ 是肯定不存在答案的，直接输出`-1`即可，然后就是构造，不难发现全排列 $p$ 的一种解是先倒序输出 $n\sim1$ 的奇数，然后输出 $4,2$（每组答案都有 $4,2$ 可由样例得出），然后正序输出 $1\sim n$ 的偶数，这样就能构造出每个 $p$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(n<=3)
		{
			puts("-1");
			continue;
		}
		for(int i=n;i;i--)
			if(i&1)
				printf("%d ",i);
		printf("4 2 ");
		for(int i=6;i<=n;i++)
			if(!(i&1))
				printf("%d ",i);
		puts("");
	}
	return 0;
}
```


---

## 作者：HoshizoraZ (赞：0)

看到题面：迷茫

~~看到样例：？？？~~

------------

首先 $n \le 3$ 时答案肯定是不存在的，关键是 $n \ge 4$ 的情况。

可以分析一下：对于**已经成立**的一个 $n$ 的排列 $[p_1,p_2,...,p_n]$，我们是否有办法可以插入数 $n+1$ 变成一个新的合法排列？

如果 $n-3 \le p_1 < n$，那么我们就可以把 $n+1$ 插入序列的开头，变成 $[n+1,p_1,p_2,...,p_n]$。

继续，如果要插入 $n+2$ 应该怎么办？

对于这种情况，我们肯定不能插到队首了，所以如果 $n-2 \le p_n \le n$，就可以将这个数插到队尾。

假设还有 $n+3$，因为队首是 $n+1$，所以刚好能插进去。更长的序列都可以这么推出。

如果如上的条件都成立，那么对于任何一个大于 $3$ 的正整数 $n$，我们都可以在原有的序列轮流在队首和队尾插入序列。

对于 $n=4$ 的样例，输出的是 $[3,1,4,2]$，观察这个序列，发现刚好可以将 $5$ 插在 $3$ 前面，然后把 $6$ 插在 $2$ 后面，以此类推。

使用如上方法构造，就可以这道题解决了。

---

## 作者：do_while_true (赞：0)

在纸上手玩可以得知 $n\leq 3$ 时无解。

如果 $n=4$ 则输出 $3,1,4,2$ 即可。（随意构造）

如果 $n=5$ 则输出 $5,3,1,4,2$ 即可。（随意构造）

如果 $n=6$ 则输出 $4,1,5,2,6,3$ 即可。（构造两边的数差值为 $1$）

当 $n \geq 7$ 时，规律就来了，我们讲 $7$ 到 $n$ 依次往上面的 $4,1,5,2,6,3$ 的两边加，$7$ 可以填到 $3$ 一侧(差值为 $4$)，$8$ 可以填到 $4$ 一侧 (差值为 $4$)，$9$ 则填到 $3$ 一侧也就是 $7$ 的后面.(差值为 $2$)$...$ 可以看出以后的填数的左右两侧的差值都为 $2$ 。

也就是交叉两侧填数。当然每个人手玩出的结果可能都不一样，结果仅供参考，重要的为做的思路。


[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79572884)

---

