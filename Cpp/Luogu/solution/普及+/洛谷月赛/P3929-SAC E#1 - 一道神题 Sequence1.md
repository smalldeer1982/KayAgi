# SAC E#1 - 一道神题 Sequence1

## 题目背景

小强和阿米巴是好朋友。


## 题目描述

小强很喜欢数列。有一天，他心血来潮，写下了一个数列。

阿米巴也很喜欢数列。但是他只喜欢其中一种：波动数列。

一个长度为 $n$ 的波动数列满足对于任何 $i\ (1 \le i < n)$，均满足以下两个条件至少一个：

- $a_{2i-1} \le a_{2i}$ 且 $a_{2i} \ge a_{2i+1}$（若存在）。
- $a_{2i-1} \ge a_{2i}$ 且 $a_{2i} \le a_{2i+1}$（若存在）。

阿米巴把他的喜好告诉了小强。小强便打算稍作修改，以让这个数列成为波动数列。他想知道，能否通过仅修改一个数（或不修改），使得原数列变成波动数列。


## 说明/提示

### 数据范围及约定

- 对于 $30\%$ 的数据，$1\le n \le 10$。
- 对于另外 $30\%$ 的数据，$1\le m \le 1000$。
- 对于 $100\%$ 的数据，$1\le n \le 10^5$，$m \le 10^9$。

其中 $m = \max|a_i|$（数列中绝对值的最大值）


## 样例 #1

### 输入

```
5
1 2 3 2 1
5
1 2 3 4 5
```

### 输出

```
Yes
No```

# 题解

## 作者：kkksc03 (赞：31)

部分分：

如果给定一个序列，可以很容易的在 O(n) 时间内判断该序 列是否为波动序列。 首先判断该序列是否为波动序列，如果是，则直接输 出”Yes“。 否则，枚举修改哪一个数。 可以发现如一个数要被修改，则将其改为 ∞ 或 −∞ 一定不 会比修改为别的数不优。 所以将其修改为 ∞ 或 −∞ 后再次判断。 总复杂度 O(n^2)。

AC：
由于波动序列本质上只有 2 种，所以对于每一种波动序列， 求出将原序列变为这种波动序列最少需要修改几次。

如果两 个值的较小值不大于 1，则输出”Yes“，否则输出”No“。

问题变为求原序列变为某种波动序列需要的最小修改次数。 从前向后扫，如果遇到某个元素不满足要求，则将该元素修 改为 ∞ 和 −∞ 中满足要求的那个，并将计数器加一。

最后计数器的值就是修改需要的最小次数。 总复杂度 O(n)。


---

## 作者：mrsrz (赞：6)

贪心地扫一遍即可。一共只有两种情况。


我们对于每种队列，记录下它前一个元素和当前元素，如果它不符合当前队列要求，就使计数器加1，并把它改成±∞（改成最大或最小值肯定能满足后面一个数的条件，因此不需要考虑后一个数）。


然后两个计数器当中有一个<2就输出Yes，否则No。


时间复杂度O(n)。

```cpp
#include<cstdio>
using namespace std;
int n;
int main(){
    while(~scanf("%d",&n)){
        int cnt1=0,pre1,pre2,cnt2=0;
        scanf("%d",&pre2);
        pre1=pre2;
        for(int i=2;i<=n;++i){
            int now;
            scanf("%d",&now);
            if((i&1)&&now>pre1){
                ++cnt1;
                pre1=-0x3f3f3f3f;
            }else
            if((i&1^1)&&now<pre1){
                ++cnt1;
                pre1=0x3f3f3f3f;
            }else
            pre1=now;
            if((i&1)&&now<pre2){
                ++cnt2;
                pre2=0x3f3f3f3f;
            }else
            if((i&1^1)&&now>pre2){
                ++cnt2;
                pre2=-0x3f3f3f3f;
            }else
            pre2=now;
        }
        if(cnt1<2||cnt2<2)puts("Yes");else
        puts("No");
    }
    return 0;
}
```
[blog](http://www.cnblogs.com/Mrsrz/p/7665646.html)


---

## 作者：血色黄昏 (赞：5)

看到有这么水的绿题赶紧来水一发题解~

思路就是简单的贪心，每次看符不符合两个中的一个，不符合就改成max或者min，最后看修改次数是不是有一个小于2就行了

因为太简单了，直接上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000000], n, p1 = 0, p2 = 0;#p1p2记录次数
int main()
{
	while(~scanf("%d",&n))#一直读入
	{
		for(int i = 0;i < n;i ++)scanf("%d", &a[i]);#读入数字个数
		for(int i = 1;i < n - 1;i ++)#从第二个到倒数第二个
		{
			if(a[i - 1] == a[i] or a[i + 1] == a[i])continue;#相等就不用管了，因为肯定符合
			if(a[i - 1] < a[i])#看符不符合a[i-1]<a[i]>a[i+1]
			{
				if(a[i + 1] > a[i])
				{
					p1 += 1;
					a[i] = 1000000001;#不符合就改成符合的，次数加一
				}
			}
			if(a[i - 1] > a[i])#看符不符合a[i-1]>a[i]<a[i+1]
			{
				if(a[i + 1] < a[i])
				{
					p2 += 1;
					a[i] = -1000000001;#同上
				}
			}	
		}
		if(p1 < 2 or p2 < 2)cout<<"Yes"<<endl;#有一个符合就输出yes
		else cout<<"No"<<endl;#不然输出no
		p1 = 0;
		p2 = 0;#初始化
	}
	return 0;
}
```

赶在期末考之前写的，祝大家AK期末考~

---

## 作者：Elegy_of_Green_Kite (赞：4)

首先，对于一个波动序列，首先要想到的是可以直接预判它的形式。

先不看这道题目，先考虑另外一道题目（~~非常简单~~）：

**如果有一个 $01$ 序列，每次可以把 $0$ 改成 $1$，或者把 $1$ 改成 $0$，成为一次操作，那么这个序列经过多少次操作可以变成一个 $01$ 交替出现的序列**

这道题的思路是读入后直接构造两个 $01$ 序列，一个是 $01010$...，另一个是 $10101$...，直接一遍扫过去，比较这两个序列和原数据，用两个计数器分别记录它们与原数据的不同的元素个数，答案就是较小的那个。

再来看[这道题](https://www.luogu.com.cn/problem/P3929)，其实是上面这道题的加强版。

因为这道题的波动方法有两种

> $a_{2i-1}$ $\le$ $a_{2i}$ 且 $a_{2i}$ $\ge$ $a_{2i+1}$（若存在） 

或者

> $a_{2i-1}$ $\ge$ $a_{2i}$ 且 $a_{2i}$ $\le$ $a_{2i+1}$（若存在）

首先直接扫一遍，同时分别用 $cnt1$ 与 $cnt2$ 记录两种不同的波动序列的不满足当前波动性的数量，比如说，如果现在的波动序列需要满足 $a_{2i-1}$ $\le$ $a_{2i}$ 且 $a_{2i}$ $\ge$ $a_{2i+1}$，但是原序列是 $a_{2i-1}$ $\le$ $a_{2i}$ $\le$ $a_{2i+1}$，这就是一个不满足的情况。

对于每一个不满足的情况，由于一个元素的数值会影响下一次的判断，所以我们在计数器加一以外还需要尝试修改这个不满足的值。比如上面的这个例子，我们尝试修改 $a_{2i+1}$，显然修改成别的值不会比修改成最小值更优，因此可以直接修改为 $-2147483647$。修改另一个值的值亦然。

注意，不能直接在原数据修改，因为我们还需要比较另一种波动序列的情况，数据不能改变，可以定义一个新变量来记录。

代码如下（参考了楼上比较好的写法）

```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
const int inf=0x7fffffff;
int n;
int main()
{
	while(~scanf("%d",&n))
	{
		int cnt1=0,cnt2=0,pre1,pre2;
		scanf("%d",&pre2),pre1=pre2;
		for(int i=2;i<=n;++i)
		{
			int now;
			scanf("%d",&now);
            
			if((i&1) && now>pre1)  cnt1++,pre1=-inf;
			else if((i&1^1) && now<pre1)  cnt1++,pre1=inf;
			else  pre1=now;
			
			if((i&1) && now<pre2)  cnt2++,pre2=inf;
			else if((i&1^1) && now>pre2)  cnt2++,pre2=-inf;
			else  pre2=now;
		}
		if(cnt1<2 || cnt2<2)  printf("Yes\n");
		else  printf("No\n");
	}
return 0;
}
```


---

## 作者：封禁用户 (赞：2)

# P3929 SAC E#1 - 一道神题 Sequence1 题解
## 思路
可以发现如一个数要被修改，则将其改为 $∞$ 或 $−∞$ 一定不会比修改为别的数不优。

由于波动序列本质上只有两种，所以对于每一种波动序列，求出将原序列变为这种波动序列最少需要修改几次。如果两个值的较小值不大于一，则输出 ```Yes``` ，否则输出 ```No```。问题变为求原序列变为某种波动序列需要的最小修改次数。

从前向后扫，如果遇到某个元素不满足要求，则将该元素修改为 $∞$ 和 $−∞$ 中满足要求的那个，并将计数器加一。

暴力查看上一次的最后一个，不满足就把当前的改成 $∞$ 或 $−∞$。直接判断计数器是否小于一就可以了。
```cpp
#include<bits/stdc++.h>
#define ll long long//骚操作
using namespace std;
const int maxn=1e5+2333;
const int INT=1e9+233;
inline int read(){
    int an=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){an=an*10+ch-'0';ch=getchar();}
    return an*f;
}
int n;
int a[maxn];
int main(){
    while(cin>>n){
        for(int i=1;i<=n;i++)a[i]=read();
        int tot1=0,tot2=0;
        int last1=-INT,last2=INT;
        int flag=1;
        for(int i=1;i<=n;i++){
        flag^=1;
            if(flag){
                if(last1>=a[i]){//下降 
                last1=a[i];}
                else{
                    last1=-INT;tot1++;//到最低 
                }
                if(last2<=a[i]){//升 
                last2=a[i];
                }
                else {
                    last2=INT;tot2++;
                }
            }
            else {
                if(last1<=a[i]){
                    last1=a[i];}
                else{
                    last1=INT;tot1++;}
                if(last2>=a[i]){
                    last2=a[i];
                }
                else {
                    last2=-INT;tot2++;
                }
            }
        }
        if(tot1<=1||tot2<=1)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：alvis (赞：1)

## 题意
给一个长度为 $n$ 的序列，问能否通过修改一个数或不修改数，使这个序列中的值（波浪起伏？）变为波动序列。~~感觉这个题意不好说，还是直接看[题面](https://www.luogu.com.cn/problem/P3929)吧~~。
## 解决

观察波动序列的性质：

对于一个位置 $i$，总有

$ a_{2i-1} \ge a_{2i}\le a_{2i+1} $（若存在）  

或者

$a_{2i-1} \le a_{2i} \ge a_{2i+1}$ （若存在）

所以我们可以考虑一个位置的奇偶，从而进行分别计算。

容易发现，一共只有两种波动序列。

所以，我们可以分别计算两种方案与当前序列的差距。

最后，用两种方案的差距的最小值作为答案。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+101, MAXN = 1e9;
int n;
int a[N], b[N]; 

int main() {
	//这种输入方式适合于无明确输入数据组数
	while(scanf("%d", &n) != EOF) {
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		for(int i = 1;i <= n;i ++) {
			cin >> a[i];
		}
		//拷贝数组，对两种方式分别计算
		memcpy(b, a, sizeof a);
		int res1 = 0, res2 = 0;
		for(int i = 2;i <= n;i ++) {
        		//对于奇偶位置分别计算。
			if(i % 2) {
				if(a[i-1] > a[i]){
					a[i] = MAXN;
					res1 ++;
				}
				if(b[i-1] < b[i]) {
					b[i] = -MAXN;
					res2 ++;
				}
			} 
			else {
				if(a[i-1] < a[i]) {
					a[i] = -MAXN;
					res1 ++;
				}
				if(b[i-1] > b[i]) {
					b[i] = MAXN;
					res2 ++;
				}
			}
			
		}
		if(res1 < 2 || res2 < 2) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
} 
```


---

## 作者：suyi1111 (赞：0)

注意到，波动数列只有  
$a_1,\le a_1,\ge a_2,\le a_3\cdots$ 和  
$a_1,\ge a_1,\le a_2,\ge a_3\cdots$  
两种。

对于每一种，判断要修改几次，这是 $O(n)$ 的，如果其中一个次数 $=0$ 或 $=1$ 就输出“Yes”。另外，注意到只有改成正负无穷大最优，剩余见代码。
```
#include<bits/stdc++.h>
using namespace std;
int a[100002],b[100002],n;
int main(){
	while(cin>>n){
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i];
		}
		int sum1=0,sum2=0;
		for(int i=2;i<=n;i++){
			if(i%10==1||i%10==3||i%10==5||i%10==7||i%10==9){//奇数 
				if(a[i]>a[i-1]){//数列1 
					a[i]=-1000000001;
					sum1++;
				}
				if(b[i]<b[i-1]){//数列2 
					b[i]=1000000001; 
					sum2++;
				}
			}else{//偶数
				if(a[i]<a[i-1]){//数列1
					a[i]=1000000001; 
					sum1++;
				} 
				if(b[i]>b[i-1]){//数列2
					b[i]=-1000000001;
					sum2++;
				}
			}
		}
		if(sum1==0||sum2==0||sum1==1||sum2==1){
			cout<<"Yes"<<endl;
		}else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：ZDQ2011 (赞：0)

## Part 1

原题戳[这里。](https://www.luogu.com.cn/problem/P3929)

题目要求一个序列能否通过几次修改变成一个波动序列，序列各项满足下列其中一项。

$$

a_{2i-1} \le a_{2i} \text{且} a_{2i} \ge a_{2i+1}

$$
$$

a_{2i-1} \ge a_{2i} \text{且} a_{2i} \le a_{2i+1}

$$

## Part 2

由题目可知，操作只要都取一个最值就肯定可以满足以后的条件，所以其实每次只要我们操作 $i$ 时都设置成一个极大或极小值，就一定是最优情况。

则直接遍历序列，如果当前项满足题目条件则不修改，否则设置成极大或极小值，统计下操作的次数，分为最大和最小两个计数器。那么操作结束时如果有一个计数器满足小于等于一的题目条件则可以，否则就不可以。

## Part 3

~~码风清奇~~

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int inf = 0X3f3f3f3f;
ll n , c1 , c2 , l1 , l2 , a;
int main(){
    while (cin>>n){
        c1 = 0;c2 = 0;
        cin >> l2;
        l1 = l2;
        for (int i = 2 ; i <= n ; i++){
            cin >> a;
            if (( i & 1 ) && a > l1 ){
                c1 ++; l1 = -inf;
            }else if (( i & 1 ^ 1 ) && a < l1){
                c1 ++; l1 = inf;
            }else{
                l1 = a;
            }
            if(( i & 1 ) && a < l2){
                c2 ++; l2 = inf;
            }else if(( i & 1 ^ 1 ) && a > l2){
                c2 ++; l2 = -inf;
            }else{
                l2 = a;
            }
        }
        if( c1 < 2 || c2 < 2 ){ cout << "Yes\n"; } else { cout << "No\n"; }
    }
}
```

---

## 作者：ChampionCyan (赞：0)

## 前言

[闲话](https://www.luogu.com/paste/p11xf7jb)。

[更美观清晰的体验](https://www.luogu.com/paste/idhrznim)。

## 做法

显然，对于一个波动数列，改动一个数之后要么让两边的数比它大，要么比它小，所以可以简化成要么改为 $\infty$，要么改为 $-\infty$。

考虑到波动数列可以抽象成：

↑↓↑↓↑↓……

和

↓↑↓↑↓↑……

两种，所以我们可以分别考虑它们。

时间复杂度 $\mathcal{O(n)}$，空间复杂度 $\mathcal{O(1)}$。因为我们只需要知道前一个和当前这个。

Code:

```cpp
#include <stdio.h>
int main() {
    int n;
    while (~scanf("%d", &n)) {
        int las1, las2;
        int ans1, ans2;
        ans1 = ans2 = 0;
        scanf("%d", &las1), las2 = las1;
        for (int i = 2; i <= n; i++) {
            int tmp;
            scanf("%d", &tmp);
            if (i % 2 && tmp > las1)
                ans1++, las1 = -2e9;
            else if (!(i % 2) && tmp < las1)
                ans1++, las1 = 2e9;
            else
                las1 = tmp;
            if (i % 2 && tmp < las2)
                ans2++, las2 = 2e9;
            else if (!(i % 2) && tmp > las2)
                ans2++, las2 = -2e9;
            else
                las2 = tmp;
        }
        if (ans1 < 2 || ans2 < 2)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
```

---

## 作者：ainivolAGEM (赞：0)

**前情提要：[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-p3929)**

## 题目大意

[题目](https://www.luogu.com.cn/problem/P3929)要求一个序列能否通过一及以下次修改变成一个波动序列，序列别个项满足如题目所示的条件。

## 题目分析

可以发现，我们其实能直接对每个项进行扫描后得出结果。枚举每一个 $i$，如果符合题目条件就直接下一项，否则就将本项修改为最大值或最小值（改成最大值或最小值肯定可以满足后面数的条件，所以最优）。接下来根据最大值或最小值更改两个计数器。如果最后两个计数器中有一个小于或等于 $1$ 则符合，否则不符合。

根据要求扫一遍数组，每次记录前后项，时间复杂度 $O(N)$。

**记得多组数据要清空！**

## AC code

- 采用位运算，确实节省了很多时间。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=0X3f3f3f3f;
ll n,c1,c2,l1,l2,a;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n){
		c1=c2=0;
		cin>>l2;
		l1=l2;
		for(int i=2;i<=n;i++){
			cin>>a;
			if((i&1)&&a>l1){
				c1++;
				l1=-inf;
			}else if((i&1^1)&&a<l1){
				c1++;
				l1=inf;
			}else{
				l1=a;
			}
			if((i&1)&&a<l2){
				c2++;
				l2=inf;
			}else if((i&1^1)&&a>l2){
				c2++;
				l2=-inf;
			}else{
				l2=a;
			}
		}
		if(c1<2||c2<2){
			cout<<"Yes\n";
		}else{
			cout<<"No\n";
	   	}
	}
}
```

---

