# Anatoly and Cockroaches

## 题目描述

Anatoly lives in the university dorm as many other students do. As you know, cockroaches are also living there together with students. Cockroaches might be of two colors: black and red. There are $ n $ cockroaches living in Anatoly's room.

Anatoly just made all his cockroaches to form a single line. As he is a perfectionist, he would like the colors of cockroaches in the line to alternate. He has a can of black paint and a can of red paint. In one turn he can either swap any two cockroaches, or take any single cockroach and change it's color.

Help Anatoly find out the minimum number of turns he needs to make the colors of cockroaches in the line alternate.

## 说明/提示

In the first sample, Anatoly has to swap third and fourth cockroaches. He needs $ 1 $ turn to do this.

In the second sample, the optimum answer is to paint the second and the fourth cockroaches red. This requires $ 2 $ turns.

In the third sample, the colors of cockroaches in the line are alternating already, thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
rbbrr
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
bbbbb
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
rbr
```

### 输出

```
0
```

# 题解

## 作者：_Aoi_ (赞：4)

[（题目传送门）](https://www.luogu.com.cn/problem/CF719B)
### 思想：
一共只有两种模式，一种brbrbr... 另一种rbrbrb... 只需要统计这两种模式下，需要的两种操作数中最小的一个，即是答案。

那怎么统计呢？

```cpp
for(int i=0;i<n;i++)
{
	if(i%2==0)
		if(a[i]=='r')
			s1++;
	else
		if(a[i]=='b')
			s2++;
  	x=max(s1,s2);
   //计算变成brbrbr...的代价
}
```

为什么是对的呢？

我们知道：

1.将r变b或者b变r; 

2.选择任意位置上的r和b交换

我们先统计**不在自己位置上**r,b的个数，将其中min(s1,s2)对r和b交换到**自己位置**上，次数为:**min(s1,s2)**
再将还没有归位的r或者b**直接替换**为正确的字母，次数为:**max(s1,s2)-min(s1,s2)**，那么它所需要的操作次数为：**max(s1,s2)** 。

rbrbrb...同理

AC代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
long long x,y,ans,n,sr1,sr2,sb1,sb2;
char a[100010];
int main()
{
	cin>>n;
	scanf("%s",a);//整体读入 
	for(int i=0;i<n;i++)//从0开始 
	{
		if(i%2==0)//判断位置 
		{
			if(a[i]=='r')
				sr1++;
			else 
				sb1++;
		}
		else{
			if(a[i]=='r')
				sr2++;
			else
				sb2++;
		}
	}
	x=max(sb1,sr2);//rbrbrb...  
	y=max(sr1,sb2);//brbrbr... 
	ans=min(x,y);
	cout<<ans;
	return 0;
 } 
```

---

## 作者：OI_AKed_me (赞：1)

# CF719B Anatoly and Cockroachesty题解 #
[原题传送门](https://www.luogu.com.cn/problem/CF719B)

## 思路 ##
首先先模拟几组小数据

``` 
rbrrrbr 
```
两种目标分别为
```
rbrbrbr
```
或
```
brbrbrb
```
若要变成第一种，则 
```
rbrrrbr
   _
```
共有$ 1 $ 个 ``` r ``` 有变动,把它变成 ``` b ``` 即可。

若要变成第二种，则
```
rbrrrbr
___ ___
```
共有$ 3 $ 个 ``` r ``` 和 $ 3 $ 个 ``` b ``` 有变动,把它们互换即可即可。

也就是说只需要看有多少个 ``` r ``` 要变动，有多少个 ``` w ``` 要变动，去大者即可。

## 代码 ##
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ss stable_sort
#define inf INT_MAX
#define re register
#pragma GCC opitimize(3)
using namespace std;
int rnum1=0,bnum1=0,rnum2=0,bnum2=0,n;
char a[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i%2){
			rnum1+=(a[i]!='r');
			bnum2+=(a[i]!='b');
		}else{
			bnum1+=(a[i]!='b');
			rnum2+=(a[i]!='r');
		}
	}
//	cout<<rnum1<<' '<<bnum2<<' '<<rnum2<<' '<<bnum2<<endl;
	cout<<min(max(rnum1,bnum1),max(bnum2,rnum2));
//	cout<<endl<<clock();
	return 0;
}
```

---

## 作者：Fleeing_loser (赞：1)

题目要求求将一个字符串变换成波浪型所需的最小步数。

举个例子来说：

原字符串
```
bbbbb
```
第一步
```
brbbb
```
第二步
```
brbrb
```
这样就转换完成了，最少次数 $1+1=2$。

先存储字符串，然后再对两种字符分别处理，并将处理的次数记录下来，最后再取最小值，字符串的波浪形式有两种，计算出两种情况分别需要的次数，取个最小值就行了。


代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100001];
int n,ans1,js1,ans2,js2,maxn;
int main()
{	
	cin>>n;	
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		if(i%2)
		{
			if(a[i]=='r') ans1++;//每次若ans增加说明有字符‘r’
			else js1++;//每次若js增加说明有字符‘b’
		}
		else 
		{
			if(a[i]=='r') ans2++;
			else js2++;
		}
	}
	maxn=min(max(ans1,js2),max(ans2,js1));//max(ans1,js2)与max(ans2,js1)分别表示“rb”与“br”两种波浪的情况
	cout<<maxn<<endl;//最后取最小值即可
	return 0;
}
```


---

## 作者：zpyyy (赞：1)

~~翻译来自本机房巨佬zyk~~

**思路:**

先算变成rbrbrbrb...的代价，在和brbrbrbr的代价取个min

怎么算这个rbrbrbrb的代价呢？见下

```cpp
    for(int i=1;i<=n;i+=2){
      if(a[i]!='r') s1++;
    }
    for(int i=2;i<=n;i+=2){
      if(a[i]!='b') s2++; 
    } 
    ans=max(s1,s2);
```
为什么是对的呢？因为小的s(假设是s1)一定可以和s2交换而来，而多出的部分可以直接变过来，所以就是max(s1,s2).
算brbrbr也一样.
Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100005];
int main(){
    int n,i,s1=0,s2=0,ans=0;
    scanf("%d",&n);
    scanf("%s",a+1);
    for(int i=1;i<=n;i+=2){
      if(a[i]!='r') s1++;
    }
    for(int i=2;i<=n;i+=2){
      if(a[i]!='b') s2++; 
    } 
    ans=max(s1,s2);
    s1=s2=0;
    for(int i=1;i<=n;i+=2){
      if(a[i]!='b') s1++;
    }
    for(int i=2;i<=n;i+=2){
      if(a[i]!='r') s2++; 
    } 
    ans=min(ans,max(s1,s2));
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Node_Edge (赞：0)

把一个字符串变成波浪状，有两种最终形态：

1. $rbrbrb...$
2. $brbrbr...$

有两种操作：
1. 将 $r$ 变 $b$ 或者 $b$ 变 $r$；
2. 选择任意位置上的 $r$ 和 $b$ 交换。

思路：

先统计不在正确位置上 $r$ 和 $b$ 的个数，再进行交换，需要交换 $\min(x,y)$ 次，然后进行替换，次数为 $\max(x,y)-\min(x,y)$ 次，两者相加得 $\max(x,y)$ 次，最后判断两种最终形态哪个修改次数少。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int r1,b1,r2,b2,ans;
//r1:第一种最终形态不在正确位置上r的个数
//b1:第一种最终形态不在正确位置上b的个数
//r2:第二种最终形态不在正确位置上r的个数
//b2:第二种最终形态不在正确位置上b的个数
int main(){
    int n;
    cin>>n;
    cin>>s;
    //第一种最终形态
    for(int i=0;i<n;i+=2){
        if(s[i]=='r') r1++;
    }
    for(int i=1;i<n;i+=2){
        if(s[i]=='b') b1++;
    }
    //第二种最终形态
    for(int i=0;i<n;i+=2){
        if(s[i]=='b') b2++;
    }
    for(int i=1;i<n;i+=2){
        if(s[i]=='r') r2++;
    }
    cout<<min(max(r1,b1),max(r2,b2));
    return 0;
}
```


---

## 作者：fjy666 (赞：0)

### 0x01 思路
设原串为 $str$。  
由于只有两种长度为 $n$ 的波浪串：
- $\texttt{rbrbrb......} = Ans_0$
- $\texttt{brbrbr......} = Ans_1$

定义到 $Ans_0$ 的代价为 $Cost_0$ ，到 $Ans_1$ 的代价为 $Cost_1$。
> 代价为从一个字符串变成另一个所需的**最小**操作次数。

那么，答案就是 $\min(Cost_0,Cost_1)$。

#### 怎么计算代价？
定义两个计数器 $cnt\_r,cnt\_b$ ，  
对于每个位置 $i (1 \le i \le n)$ ，  
若 $str_i \neq Ans_i$，
> 若 $str_i = \texttt{r},cnt\_r \gets cnt\_r+1$  
> 若 $str_i = \texttt{b},cnt\_b \gets cnt\_b+1$ 

代价就是 $\max(cnt\_r,cnt\_b)$

为什么？
不妨设 $cnt\_r \le cnt\_b$。  
则每个不同的 $r$ 都可找到对应的 $b$ ，与之交换并抵消。  
操作次数就是 $(cnt\_b-cnt\_r)+cnt\_r$，也就是 $cnt\_b$。  
反之亦然。  
时间复杂度：$\Theta(n)$ 。

------------
### 0x02 代码
```cpp
#include <cstdio>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define rtn return
 
typedef long long ll;
const int kMaxn = 100005;
const char CharSet[]="rb";
char str[kMaxn],Ans[2][kMaxn];
 
int max_(int a,int b)
{
    rtn a>b?a:b;
}
 
int main()
{
    int n,ans = 0x7fffffff;
    scanf("%d",&n);
    scanf("%s",str+1);
    fo(j,0,1)
        fo(i,1,n)
            Ans[j][i]=CharSet[i&1^j];
//  printf("%s\n%s\n---\n",Ans[0]+1,Ans[1]+1);
    fo(j,0,1)
    {
        int cnt_diffrent_r = 0,
            cnt_diffrent_b = 0;
        fo(i,1,n)
            if(Ans[j][i]!=str[i])
            {
                if(str[i] == 'r')++cnt_diffrent_r;
                if(str[i] == 'b')++cnt_diffrent_b;
            }
        if(ans > max_(cnt_diffrent_r,cnt_diffrent_b))
            ans = max_(cnt_diffrent_r,cnt_diffrent_b);
    }
    printf("%d",ans);
    rtn 0;
}

---

## 作者：orange166 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF719B)   
## 思路： 
由于只有两种构造方式，所以分别统计不在正确位置的 $b$ 和 $r$ 即可。  

对于每一对不在正确位置的 $b$ 和 $r$，将他们移回正确位置的代价为 $1$。剩下不在正确位置上的 $b$ 或 $r$，每移回正确位置一个代价为 $1$。   

显而易见，方法的代价为不在正确位置的 $b$ 和 $r$ 的最大值。
  
最后求出两种构造方式的最小代价即可。  
##  
## 代码：  
```python
a=int(input())
b=input()  #字符串
s1=0; s2=0; ss1=0; ss2=0
for i in range(0,a):  #下标从0开始
    if b[i]=='r' and i%2==1:  #第偶数个字符 第一种方式应为b，第二种应为r
        s1+=1
    elif b[i]=='r':  #两种构造方式相反
        ss1+=1
    elif b[i]=='b' and i%2==0:  #第奇数个字符 第一种方式应为r，第二种应为b
        s2+=1
    else:
        ss2+=1
s=min(max(s1,s2),max(ss1,ss2))  #显而易见，方法的代价为不在正确位置的 $b$ 和 $r$ 的最大值。
print(s)
    

```
[AC](https://www.luogu.com.cn/record/41379284)

---

## 作者：Jr_Zlw (赞：0)

## 一道贪心题

这道题其实只要想到思路实际上非常的水。它既没有需要输出交换的顺序，还没有让你输出顺序，而甚至只有 $2$ 种字符，也没有各种恶心的字符串操作，在这种特殊的情况下，应该很容易想到可以用贪心做。

### 贪心的思路

因为这道题只有两种简单的操作——直接修改 和 交换位置。目标字符串也只用两种，"$brb...$"和"$rbr...$"。

我们发现，直接修改简单粗暴，可以无脑把全部错误的地方全部改正，那么如果只是直接修改，我们就只需要记录两种排列方式中错误的个数并且比较就能算出在这种情况下需要改多少个才能得到合法的字符

而交换修改较直接修改有一个优点，就是交换一次可能可以得到两个合法的字符，这样的效率就比直接修改快了一倍，所以我们贪心的目的就是要尽可能多地用交换而不用直接修改。

此时非常惊喜的发现，管它交换哪里呢，只要记录好有多少个可以交换的就全部交换不久好了吗。所以我们就直接记下两种情况下错误的"$r$"的个数和错误的"$b$"的个数，用$min(b,r)$次交换使"$b$"或"$r$"全部正确，剩下的也就没得交换了，只能一个一个修改。那么到最后就得到一个推论：

$ans=min(b,r)+max(b,r)-min(b,r)=max(b,r)$

那么由于有两种目标情况，我们就需要分类讨论（其实不过是用多 $2$ 个计数器），取最小值即可，也就是：

$ans=min(max(b1,r1),min(b2,r2))$

_(注：公式中的 $b1,r1,b2,r2,b,r$为需要修改的 "$b$" 或 "$r$" 的个数)_

### 代码实现

（很简单）

```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(int c=(a);c<=(b);++c)
using namespace std;
char c[1000001];
int t1wr,t1wb,t2wr,t2wb;
int main()
{
	int n;cin>>n;
	rep(1,n,i)
	{
		cin>>c[i];
		if((i&1)&&c[i]=='r')t2wr++;
		if(!(i&1)&&c[i]=='r')t1wr++;
		if((i&1)&&c[i]=='b')t1wb++;
		if(!(i&1)&&c[i]=='b')t2wb++;
	}
	
	int ans=min(max(t1wr,t1wb),max(t2wr,t2wb));
	cout<<ans;return 0;
}
```


---

