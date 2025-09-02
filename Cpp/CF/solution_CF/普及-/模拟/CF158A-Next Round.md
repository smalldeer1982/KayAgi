# Next Round

## 题目描述

# CF158  Next Round 下一轮   
# 题意简述  
有$n$个人参加一场比赛，其中分数排名前$k$位的人将被选入下一轮（选入下一轮的人分数必须为正，见样例#2），特别的，如果几个人分数相同且刚好并列处于第$k$名（或是并列$k-i$名，但是全部算入后选入下一轮的人数超过$k$人），这几个人都将被选入下一轮（见样例#1），题目要求你输出进入下一轮的人数。输入保证已经按分数从大到小排序。

## 说明/提示

在样例#1中，第五位和第六位参赛者都获得了七分，所以有六人进入下一轮。  
在样例#2中，没有人得到大于0的评分。  

翻译提供者：n0000000000o

## 样例 #1

### 输入

```
8 5
10 9 8 7 7 7 5 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 2
0 0 0 0
```

### 输出

```
0
```

# 题解

## 作者：Soshine_溯闪 (赞：5)

我 **第九次** 传题解。      
这题是简单的模拟。       
# 整体思路
分两个部分。     
1. 前 $k$ 个：   
如果非零答案数就加一，否则，直接输出，因为这是一个从大到小的数列，后面的数一定也是零。    
2. 后面的 （ $k+1$ 到 $n$ ） ：     
如果是并列 （跟第 $k$ 个一样），也能晋级，否则直接输出，因为这是一个有序数列，后面比前面小。      
坑点：
别忘最后在输出一遍答案，如果这 $n$ 都并列，在第二部分就输出不了，最后再输出一遍，不然有些样例就没输出。      
#  程序
```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
int n,k,a[55],ans;
int main(){
	cin>>n>>k;		 
	for(int i=1;i<=n;i++) cin>>a[i];		//读入 
	for(int i=1;i<=k;i++) {		//前k个 
		if(a[i]>0) ans++;		//不是，就加上 
		else {		//是0，就退出 
			cout<<ans<<endl;
			return 0;
		}
	}
	for(int i=k+1;i<=n;i++){		//后面的 
		if(a[i]==a[k]) ans++;		//如果是并列，也算上 
		else{		//否则，就直接输出 
			cout<<ans<<endl;
			return 0;
		}
	}
	cout<<ans<<endl;		//如果n个都并列，也输出上 
	return 0;
}
```
跪求管理员给过！

---

## 作者：BlueSu (赞：4)

这道题说实在的有这么几个注意点：

- 1.只能录取正整数的分数

- 2.如果出现相同分数那么都录取
- 3.k为排名第几，也就是说要算上之前的所有人

那么，对于每个点，模拟一下就行了。

对于第一个点，加上特判：

```cpp
for(int i = 1; i <= score; i++)//range(1, score)
	if(a[i])//if score is above zero -> answer + 1
		ans++;
	else{//otherwise
		cout << ans << endl;//output answer
		exit(0);//broke program
	}
```

对于第二个点，用while，但是不要忽略0

```cpp
while(a[score] == a[score + 1] && a[score] != 0)//while next is same value && isn't zero
	score++, ans++;//move array place, put into answer
```

对于第三个点，脑子里记着就行了。

贴代码：
```cpp
//注释之前已经写过了，这里就不再写了
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int a[1000 + 5];
int tmp, ans, n, score, cnt;

int main(){
	
	cin >> n >> score;
	
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	
	for(int i = 1; i <= score; i++)
		if(a[i])
			ans++;
		else{
			cout << ans << endl;
			exit(0);
		}
	
	while(a[score] == a[score + 1] && a[score] != 0)
		score++, ans++;
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Chtholly_L (赞：1)

# 题解CF158A 【Next Round】
###### ~~大家好，本奆蒟蒻又来写题解了！~~

我最近刚刚注册了一个 $CF$ 账号，刷了几道水题，就来到洛谷上刷这些题了 ~~我还是太弱了QAQ~~  。

---
废话不多说，进入正题，开始讲解

### 题意简化：

有 $N$ 个人参加比赛，只要参赛者的得分为正，则得分等于或大于第 $k$ 名的选手将晋级到下一轮，那么有多少人能晋级到下一轮？

### 输入格式：

输入的是 $N$ 和 $k$ ，接下来 $N$ 组数据。 

### 题意分析

其实很简单，先定义一个数组，储存数据，再读取数据，然后定义一个计数器，再将数组枚举，只要满足大于等于第 $k$ 名的分数，并且分数是正数，就将计数器加一。

更详细的解释在代码里。

## $Ac$ $Code$
```cpp
#include<iostream>
using namespace std;
int a[51];  //定义数组
int main()
{
	int n,k;  //n,k 如题
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];  //读入数组
	}
	int ans=0;  //计数器
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=a[k]&&a[i]>0)ans++;  //如果满足大于第 k 名的分数，并且是正数，计数器就加一
	}
	cout<<ans;  //输出
	return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/46824081)

[博客食用更佳](https://www.luogu.com.cn/blog/maxsuper/)

---

## 作者：Konnyaku_Alan (赞：1)

这其实是一道比较水的题，但有一个比较坑的注意点

#### 如果分数为0，那也是没有晋级

理解了这一点，解题就很容易了

## 解题思路

就是一个暴力，把分数线求出来，在遍历一遍就好了

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
int n, k, a[51], x, ans;//x为分数线，ans为晋级人数 
int main ()
{
	std::ios::sync_with_stdio(false);
	cin >> n >> k;
	for ( int i = 1; i <= n; i++ )
		cin >> a[i];
	x = a[k];//求出分数线 
	for ( int i = 1; i <= n; i++ )
		ans += x <= a[i] && a[i];
	/*
	x <= a[i]表示分数是否达到分数线，
	a[i](a[i] != 0)代表分数是否为0，
	如果两个都符合就+1
	*/ 
	cout << ans << endl;//输出 
	return 0;
}
```
### 求过

---

## 作者：houpingze (赞：1)

## 本题解提供一种桶的写法
### 思路：

先定义个桶：

```int a[105];```

注意：桶的大小是根据$a[i]$的数据范围来的，本题$a[i]$最大只有100

把输入存到桶里：

```cpp
for(int i=1;i<=n;i++){
	cin>>t;
	a[t]++;
}
```

从大到小枚举，只要参赛人数一够就输出，结束：

```
for(int i=100;i>=1;i--){
	if(a[i]){//有人得i分
		k-=a[i];
		cnt+=a[i];//cnt是晋级人数
		if(k<=0){
			cout<<cnt;//输出
			return 0;//结束
		}
	}
}
```
## AC CODE：
```cpp
#include<iostream>
using namespace std;
int n,cnt,k,a[105],t;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>t;
		a[t]++;//存桶
	}
	for(int i=100;i>=1;i--){
		if(a[i]){//有人得i分
			k-=a[i];
			cnt+=a[i];//cnt是晋级人数
			if(k<=0){
				cout<<cnt;//输出
				return 0;//结束
			}
		}
	}
	cout<<cnt;
}
```

完结撒花！*★,°*:.☆(￣▽￣)/$:*.°★* 。


---

## 作者：GaryH (赞：1)

# 本蒟蒻又来发题解啦！

### 其实此题并不难,这里提供两种方法：


1. 通过边输入边进行排名，最后用一个for查找，时间复杂度为O(2n+k)到(3n)；

**代码如下：**

```cpp
#include<iostream>
using namespace std;
int n,k,a[101][2],ans;
/*n,k为输入,a[i][1]代表第i人分数,a[i][0]代表第i人排名*/
int main(){
	std::cin>>n>>k;
	for(register int i=1;i<=n;i++){
		std::cin>>a[i][1];
		if(i==1){
			a[i][0]=1;
  			//把第一名统计进数组
		}else{
			if(a[i][1]==a[i-1][1]){
				a[i][0]=a[i-1][0];
			}else{
				a[i][0]=i;
			}/*统计排名*/
		}
	}
	for(register int i=1;i<=n;i++){
		if(a[i][1]<=0){
			std::cout<<ans;return 0;
			//是零直接输出且退出
		}
		if(a[i][0]>k){
			std::cout<<ans;return 0;
  			//排名大于k也直接输出且退出
		}
		ans++;
  		//统计答案
	}
	std::cout<<n;
  	//若在前面for中未return 0则输出n
	return 0;
}
```

2. 通过边输入边查找是否有0，最后用while从k个开始查找，时间复杂度为O(n+k)到(2n)；

**代码如下：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[101][2],p=0;
int main(){
	//此处就不详细解释了 
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i][1];
		if(a[i][1]<=0)a[i][0]=1;
	}
	for(int i=1;i<=k;i++){
		if(a[i][0]==1){
			cout<<i-1;
			//有零就直接输出 
			return 0;
		}
	}
	int i=k;
	while(1){
		if(a[i][1]==a[i+1][1]&&a[i][0]==0)i++;//排名一样就加1 
		else break;//不然退出 
	}
	cout<<i;
	//输出 
	return 0;
}
```
放一下评测记录：

[AC记录#1](https://www.luogu.org/record/26594932)

## 好了各位，下次再见！


---

## 作者：打表大蒟蒻 (赞：1)

一道~~大水~~题

这道题其实是一道模拟题，从1至n逐个模拟，定义计数器s，如果a[i]<=0，直接就可以结束程序了，接下来考虑另一种情况，如果s>k（就是a[i]的i已经超过k了），有两种情况，如果有并列的，s继续累加（这就是循环到n的原因），如果不并列，直接退出循环，把s输出就over了。

下附程序（C/C++）
```cpp
#include <stdio.h>
int a[51];
int main ()
{
    int n, k, s=0;
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    int p=a[k];  //设定变量，便于比较
    for(int i=1;i<=n;i++) 
	{
		if(a[i]<=0) {
			printf("%d",s);  //如果有非正的情况出现，直接输出
			return 0;  //结束程序
		}
		if(s>=k){
			if(p==a[i]) s++;  //考虑并列的情况
			else break;  //不并列就退出
		}  
		else s++;  //把s累加
	}	
	printf("%d",s);  //输出
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个人参加比赛，第 $i$ 名在第一轮的分数是 $a_i$（保证 $a_i\geqslant a_{i+1}$）已知下一轮预计能进 $k$ 人，当然如果有并列的第 $k$ 名，则他们都能够进入下一轮。但是，没有得分的人尽管是前 $k$ 名，都不能够进入下一轮。求能够进下一轮的人数。

**数据范围：$1\leqslant k\leqslant n\leqslant 50,0\leqslant a_i\leqslant100$。**
## Solution
我们一个一个读入并判断，当人数已经达到 $k$ 的时候，我们就开始判断是否与前面那一名的分数相等，一不相等我们就直接退出去输出结果。

当然要特判分数是否大于 $0$。
## Code
```cpp
#include <cstdio>
using namespace std;

int n, k, pre, ans;

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
//		printf("%d %d\n", pre, x);
		if(!x || (x != pre && ans >= k))	break;
		ans++;
		pre = x; 
	}
	printf("%d", ans);
}
```

---

