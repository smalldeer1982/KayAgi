# Minimize The Integer

## 题目描述

You are given a huge integer $ a $ consisting of $ n $ digits ( $ n $ is between $ 1 $ and $ 3 \cdot 10^5 $ , inclusive). It may contain leading zeros.

You can swap two digits on adjacent (neighboring) positions if the swapping digits are of different parity (that is, they have different remainders when divided by $ 2 $ ).

For example, if $ a = 032867235 $ you can get the following integers in a single operation:

- $ 302867235 $ if you swap the first and the second digits;
- $ 023867235 $ if you swap the second and the third digits;
- $ 032876235 $ if you swap the fifth and the sixth digits;
- $ 032862735 $ if you swap the sixth and the seventh digits;
- $ 032867325 $ if you swap the seventh and the eighth digits.

Note, that you can't swap digits on positions $ 2 $ and $ 4 $ because the positions are not adjacent. Also, you can't swap digits on positions $ 3 $ and $ 4 $ because the digits have the same parity.

You can perform any number (possibly, zero) of such operations.

Find the minimum integer you can obtain.

Note that the resulting integer also may contain leading zeros.

## 说明/提示

In the first test case, you can perform the following sequence of operations (the pair of swapped digits is highlighted): $ 0 \underline{\textbf{70}} 9 \rightarrow 0079 $ .

In the second test case, the initial integer is optimal.

In the third test case you can perform the following sequence of operations: $ 246 \underline{\textbf{43}} 2 \rightarrow 24 \underline{\textbf{63}}42 \rightarrow 2 \underline{\textbf{43}} 642 \rightarrow 234642 $ .

## 样例 #1

### 输入

```
3
0709
1337
246432
```

### 输出

```
0079
1337
234642
```

# 题解

## 作者：御前带刀侍卫 (赞：8)

### 0.题目链接

[CF1251C Minimize The Integer on luogu](https://www.luogu.org/problem/CF1251C)

### 1.题意

诶，英文题？

~~xx翻译一下~~

总之就是给你一个十进制数，每一位有奇有偶，相邻的两个数位如果奇偶性相异，则可以交换

然后让您通过这样的操作把这个数（序列）最小化

### 2.思考

看一遍样例，发现~~没什么特殊性质~~

发现：**奇数之间无法互换，偶数之间无法互换（敲黑板（显然））**

所以：**奇数之间的次序固定，偶数之间次序固定**

~~诶，有意思~~

我们能减少int的方法就只有 **调整奇偶数间的次序**

所以：可以 **把奇数放到一个序列里，把偶数放到一个序列里，然后用类似归并的方法由小到大归并进一个序列**

这个序列即答案

![](![](https://cdn.luogu.com.cn/upload/image_hosting/ivxwhnyq.png))


算法图解

### 3.代码

```cpp
#include<stdio.h>
#include<iostream>

using namespace std;

string s;					//初始序列
int a1,b1;

int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		cin>>s; 				
		string a,b;			//a为奇数序列，B为偶数序列
		a1=b1=0;			//a1为奇数个b1为偶数个
		int len=s.length();
		for(int i=0;i<len;i++){
			if((s[i]-'1')&1)a+=s[i],a1++;
			else b+=s[i],b1++;
		}
		a+=120;
		b+=120;				//打个末尾标记，方便归并
		for(int i=0,j=0;i<=a1&&j<=b1;){   //归并
			if(a[i]<b[j]){
				if(a[i]>='0'&&a[i]<='9')
				printf("%c",a[i]);
				i++;
			}
			else{
				if(b[j]>='0'&&b[j]<='9')
				printf("%c",b[j]);
				j++;
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：enyyyyyyy (赞：3)

## 题意：
给你一个大整数 $a$ ，它有  `a.size()` 位数字，也可能有前导零。现在给你一种操作规则：如果相邻的两个数字或奇或偶，那么你就可以交换它们。求交换最小次数。

------------
## 思路：
 
 
 
 
 
 把奇数放到一个序列里，把偶数放到一个序列里，然后用 `merge()` 自动由小到大归并进一个序列。
 
 
 
------------
## 时间复杂度：
 $O(tn)$ 。


------------

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read() {快读
    long long s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
    return s * w;
}
inline void print(long long x)//快写
{
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x>=10) print(x/10);
    putchar(x%10+'0');
    return;
}
long long t;
int main(){
	t=read();//输入
	while(t--)
	{
		string a;
		cin>>a;/输入
		string b,c;
		for(int i=0;i<a.size();i++)//判断奇偶
		{
			if(a[i]&1)
			{
				b+=a[i];
			}			
			else
			{
				c+=a[i];
			}
		}
		merge(b.begin(),b.end(),c.begin(),c.end(),a.begin());	//合并
		cout<<a<<"\n"; //输出
	}
    return 0;
}
```
[记录](https://www.luogu.com.cn/record/113131839)

---

## 作者：Mo_xue (赞：2)

 [题目传送门：Minimize The Integer](https://www.luogu.com.cn/problem/CF1251C)
[博客食用更佳](https://www.luogu.com.cn/blog/renyuhan/cf1251c-minimize-the-integer-ti-xie)
##  一、题意
给定一个可能含有前导 $0$ 的十进制数，相邻的两个数位上的数字如果**奇偶性不同**就可以交换，通过任意次操作让数字**最小化**。
## 二、思考过程

讲课老师：“首先，这是一道贪心……”

但是，怎么贪？

既然要让结果最小，那就**把大数字换到后面，把小数字换到前面**就万事大吉啦……

问题又来了，怎么换呢？

让我们先来看看题目：“你可以交换相邻位置的两个数字，如果这两个数字奇偶性不同（换言之，它们被二除的余数不同）。”

这说明什么呢？(~~重点来啦，敲黑板~~)

**说明不管怎么换，奇偶性相同的数字之间的相对位置不会改变！**

由此，我们可以想到把奇数和偶数单独挑出，分别存在两个数组中，然后用**归并排序**的思想，在**奇偶性相同的数字之间的相对位置不改变**的前提下，尽量让**小的数在前，大的数在后**，贪心的排序就好了！

如果归并排序还不明白，请[出门右转看看这篇博客](https://blog.csdn.net/weixin_45031801/article/details/127034720)

还是不明白？举个栗子：

比如 $18369$，


奇数：$1,3,9$

偶数：$8,6$

$ans$：（~~此时空空如也~~）

 _P.S. 下面用 $js_i$ 表示该数中的第 $i$ 个奇数，用 $os_j$ 表示该数中的第 $j$ 个偶数，下标从 $1$ 开始，与上面的数字一 一对应；用 $ans_k$ 表示答案的第 $k$ 位数_
 
 $i \gets 1,j \gets 1,k \gets 1$：
 
 $js_1<os_1(1<8)$，更新答案：$ans_1 \gets js_1 ,i \gets i+1,k \gets k+1$；
 
 $ans:1$
 

------------

 $i \gets 2,j \gets 1,k \gets 2$：
 
 $js_2<os_1(3<8)$，更新答案：$ans_2 \gets js_2,i \gets i+1,k \gets k+1$；
 
 $ans:13$
 

------------

 
 $i \gets 3,j \gets 1,k \gets 3$：
 
 $js_3>os_1(9>8)$，更新答案：$ans_3 \gets os_1,i \gets i+1,k \gets k+1$；
 
 $ans:138$
 

------------
 $i \gets 3,j \gets 2,k \gets 4$：
 
 $js_3<os_2(9<6)$，更新答案：$ans_4 \gets os_2,i \gets i+1,k \gets k+1$；
 
 $ans:1386$
 

------------
 $i \gets 3,j \gets 3,k \gets 5$：
 
 $j$ 已经跳出 $os$ 数组的范围，说明偶数已经放完，那就把剩下的奇数~~不管三七二十一~~全塞进去，更新答案：$ans_5 \gets js_3,i \gets i+1,k \gets k+1$；

 $ans:13869$



------------


 $i \gets 4,j \gets 3,k \gets 5$：

 $i,j$ 均已越界，遍历完成，输出 $ans$ 数组。



------------


## 三、代码

 ~~**虽然思路讲的已经很清楚，但我相信大家一定会看到这里**~~

好了，话不多说，奉上 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3 * 1e5 + 5;
int n;
string s;
int js[N], os[N], ans[N], l1, l2;
void merge_sort() {
	int i = 1, j = 1, k = 0;
	while (i <= l1 && j <= l2)
		if (js[i] < os[j]) ans[++k] = js[i++];
		else ans[++k] = os[j++];
	while (i <= l1) ans[++k] = js[i++];
	while (j <= l2) ans[++k] = os[j++];
	for (int i = 1; i <= k; i++)
		cout << ans[i];
	cout << endl;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		cin >> s;
		l1 = 0;
		l2 = 0;
		for (int i = 0; i < s.size(); i++) {
			int a = s[i] - '0';
			if (a % 2 != 0) js[++l1] = a;
			else os[++l2] = a;
		}
		merge_sort();
	}
	return 0;
}
```

本蒟蒻的第一篇题解，看完顺便点个赞呗 $\sim$（~~求通过~~）

---

## 作者：Paris_Bentley (赞：2)

题目描述：有一个数字，我们可以把其中相邻的奇数和偶数位置互换。要求得到最后的最小数字。

我们可以试一下，具有奇偶性的数字是不能换的，所以无论怎么样变换位置奇数和奇数，偶数和偶数是永远不能换的。所以，我们可以先把所有的奇数和偶数拆分为两个单独的数列，然后从队列中一个一个拿出比较大小，把小的放进去~这样把奇数或者偶数都用完后，再把剩下的另一种数接到最后就可以了。

PS：如果找不到规律的伙伴，可以直接拿样例数据入手，我们也能找到这样的规律，奇数和偶数一定不会交换，所以相对位置一定不会变化。

0709
1337
246432

0079
1337
234642


上代码
（伙伴问我的题目，帮他写的代码，没有把++写进数组下标，方便新手看~）


```
#include<iostream>
#include<cstring>
using namespace std;
char a[300010],b[300010];
string str;
int main()
{
	int tt;
	cin >> tt;
	while(tt--)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		int al=0,bl=0;//保存奇数偶数数量 
		cin>>str;
		for (int i=0;i<str.length();i++)
		{
			if (str[i]%2==1)//把奇数和偶数分别拿出来 
				{
					al++;
					a[al]=str[i];
				}
			else 
				{
					bl++;
					b[bl]=str[i];
				}
		}
		int aa=1;//两个指针 
		int bb=1;
		while(aa<=al&&bb<=bl) //把小的数字输出 
		{
			if (a[aa]<b[bb])
				{
					cout<<a[aa];
					aa++;
				}
			else 
			{
				cout<<b[bb];
				bb++;
			}
		}
		while(aa<=al)//最后只剩下奇数，循环输出剩下的部分 
		{
			cout<<a[aa];
			aa++;
		}
		while (bb<=bl)
		{
			cout<<b[bb];
			bb++;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Weakest_Konjac (赞：2)

时间复杂度：$O\left(n\right)$

前置知识：写代码

我们对操作规则进行分析

“如果相邻的两个数字的奇偶性不同，那么你就可以交换它们。”

不难发现：对于两个奇偶性相同的数字，无论如何交换，相对位置不变

即对于大整数中的两个数字$a_{i},a_{j}$，若$a_{i} \ mod \ 2=0,a_{j} \ mod \ 2=0$或$a_{i} \ mod \ 2=1,a_{j} \ mod \ 2=1$，那么操作后$a_{i}$在$a_{j}$前

所以我们就将问题转化为了：知道两个序列$num1$和$num2$，不改变序列中元素的相对位置，将两个序列合并，求合并后字典序最小的序列（就是归并排序中的归并操作）

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N=3e5+5;
string a,ans;
int T,n,num1[N],num2[N],cnt1,cnt2;
int main(){
	cin>>T;
	while (T--){
		cin>>a,n=a.length(),cnt1=cnt2=0,ans="";
		for (register int i=0;i<n;++i)
			a[i]&1?num1[++cnt1]=a[i]:num2[++cnt2]=a[i];
		int pos1=1,pos2=1;
		while (pos1<=cnt1&&pos2<=cnt2) num1[pos1]<num2[pos2]?ans+=num1[pos1++]:ans+=num2[pos2++];
		for (register int i=pos1;i<=cnt1;++i) ans+=num1[i];
		for (register int i=pos2;i<=cnt2;++i) ans+=num2[i];
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：盧鋅 (赞：0)

奇数字和偶数字之间可以互换，但同为奇数或偶数的却不可以，很明显，奇数之间的相对位置确定，偶数之间的相对位置确定。

然后我们运用类似归并排序的做法，贪心求最小值即可。

代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char su[400000],ou[400000];
signed main(){
	int _su,_ou,n;
	cin>>n;
	while(n--)
	{
		string s;
		_su=0,_ou=0;
		memset(su,0,sizeof(su));
		memset(ou,0,sizeof(ou));
		cin>>s;
		for(int i=0;i<s.length();++i)
		if(s[i]%2)su[++_su]=s[i];
		else ou[++_ou]=s[i];
		int k=1,j=1;
		while(k<=_su&&j<=_ou){
			if(su[k]<ou[j])cout<<su[k++];
			else cout<<ou[j++];
		}
		while(k<=_su)cout<<su[k++];
		while(j<=_ou)cout<<ou[j++];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：zsyyyy (赞：0)

# CF1251C题解 贪心

## 题意

给你一个大整数 $a$，它由 $n$ 位数字，也可能有前导零。现在给你一种操作规则：如果相邻的两个数字的奇偶性不同，那么你就可以交换它们。现在可以做任意次操作（可能一次都不做），求出通过这些操作可以获得的最小整数是多少。（答案可以包含前导零）

## 思路

因为只有奇偶性不同时才能交换，所以奇数内和偶数内的相对顺序是不能变的。因此，可以将奇数和偶数分成两个数组，然后利用双指针每次取出奇数的队头和偶数的队头中较小的那一个。

时间复杂度：$O(n)$


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=300005;
int T,n,a[MAX],b[MAX],ji[MAX],ou[MAX],jcnt,ocnt,jcntt,ocntt;
char aa[MAX];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		jcnt=ocnt=0;
		scanf("%s",(aa+1));
		n=strlen(aa+1);
		for(int i=1;i<=n;i++)  a[i]=aa[i]-'0';
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2)  ji[++jcnt]=a[i]; //奇数列
			else  ou[++ocnt]=a[i]; //偶数列
		}
		jcntt=ocntt=1; //双指针
		while(1)
		{
			if(jcntt==jcnt+1) //奇数已全部输出
			{
				for(int i=ocntt;i<=ocnt;i++)  printf("%lld",ou[i]);
				break;
			}
			if(ocntt==ocnt+1) //偶数已全部输出
			{
				for(int i=jcntt;i<=jcnt;i++)  printf("%lld",ji[i]);
				break;
			}
			if(ji[jcntt]<ou[ocntt]) //取奇数队头和偶数队头中较小的那一个
			{
				printf("%lld",ji[jcntt]);
				jcntt++;
			}
			else
			{
				printf("%lld",ou[ocntt]);
				ocntt++;
			}
		}
		puts("");
	}
	return 0;
}
```


---

