# Santa Claus and Candies

## 题目描述

圣诞老人有$n$ 个糖果，他想要把这些作为礼物送给孩子们。

如果圣诞老人想要每个孩子得到的糖果数都是不同的正整数，那他最多能将糖果分给多少个孩子。圣诞老人（Santa Class — 错误的原文）想把他有的$n$ 个糖果都送出去。

## 样例 #1

### 输入

```
5
```

### 输出

```
2
2 3
```

## 样例 #2

### 输入

```
9
```

### 输出

```
3
3 5 1
```

## 样例 #3

### 输入

```
2
```

### 输出

```
1
2 
```

# 题解

## 作者：wpy233 (赞：3)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/woeeeeee/solution-cf753a)

本题已有的几篇题解解释得不是很详细，使用的方法几乎相同，因此有了这篇题解。

### 题目解读

乍一看，本题的样例杂乱得很。

其实读过题目后，发现要让收到糖果的孩子最多，每个孩子收到的糖果数目要尽量少。

因为其中一个孩子分得了更多的糖果的话，后面的孩子就没有足够的糖果继续分了。

但是糖果数量为正整数且互不相同，易想出分得的糖果数目应为 $1$ $2$ $3$ …

所以，本题最贴心的样例应该是这样的：

输入： $9$

输出： 

$3$

$1$ $2$ $6$
### 实现细节

**①对于** $k$ **的计算**

可套用高斯求和公式，通过解方程

$$ \dfrac{k(k+1)}{2} = n$$

可得

$$k = \sqrt{2n+0.25} - 0.5$$

据此计算，下取整即可。

当然，也可通过循环计数累加的方法求得。（该代码将在代码部分的②贴出）

**②输出的合法方案**

$k$ 的值已经求出。那么就可借此循环输出了。

第一行 $k$ 不必多说。

第二行中的最后一个数应为 $n-\dfrac{(k-1)k}{2}$。

### 代码

①题解方法

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	double k=sqrt(2.0*n+0.25)-0.5;//公式计算k
	int kk=(int)k;
	cout<<kk<<endl;//下取整
	for(int i=1;i<=kk-1;i++)
		cout<<i<<" ";
	cout<<n-(kk-1)*kk/2<<endl;//依次输出即可
	return 0;
}
```
②循环计数方法
```
//注：不为题解方法，无注释，放心抄
#include <bits/stdc++.h>
using namespace std;
int mian()
{
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;;i++)
	{
		if(n>=i) 
		{
			ans++;
			n-=i;
		}
		if(n<i+1)
			break;
	}
	cout<<(int)(sqrt(a*n-0.25))<<endl;
	for(int i=1;i<=ans-1;i++)
		cout<<i<<" ";
	cout<<n+ans<<endl;
	return 0;
}
```

---

## 作者：diqiuyi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF753A)

**思路**

贪心思想，为了分给尽可能多的小朋友，每个小朋友分到的应当尽可能的少。所以第 $i$ 个小朋友应当分到 $i$ 个。不过考虑到要把所有糖果分完，最后一个小朋友的糖果数量会增加一些。

设最终能分给 $x$ 个小朋友，则 $1+2+3+\cdots+x=\dfrac{x(x+1)}{2} \le n$。

既然 $n$ 已知，那么可以从 $1$ 开始枚举得到 $x$ 的值。不过其实可以直接利用求根公式得出 $x \le \dfrac{-1+\sqrt{1+8n}}{2}$，直接算出该式即可，因为 C++ 会帮你下取整。

那么我们可以轻松求出出前面的 $x-1$ 项，最后一项就是 $n-\dfrac{x(x-1)}{2}$。

**MAIN CODE**
```cpp
ans=((sqrt((n<<3)+1)-1)/2)
```
```cpp
printf("%d\n",n-((ans-1)*ans>>1));
```
~~又水了一篇题解。~~

---

## 作者：江山_远方 (赞：1)

### 题意简述  
有 $n$ 颗糖果，分给 $k$ 个人，且每个人收到的糖果数不同。现已知 $n$，求最大的 $k$ 及其方案。
### 数据范围
$n\leq1000$  

------------

### 题目分析  
为了使分到的人尽可能多，应使每个人拿到的糖果尽可能少，可以考虑自第一个人开始，每个人拿的糖数构成一个首项、公差皆为1的等差数列。

考虑到可能会产生最后有剩余的情况 全部给最后一个人即可


------------
### 代码
Tip:在食用代码前，可尝试自行解决
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[1000];
int main()
{
	cin>>n;
	for(int i=1;n;i++)//这里的n表示n>0，其实也可以不写，因为下文有判断
	if(n>=i)n-=i,a[++t]=i;//当剩下的糖果足够分时，分出去并记录
	  else break;//若不够分，则惊进行下一步处理
	a[t]+=n;//将余下的糖果全部分给最后一个人
	cout<<t<<endl;
	for(int i=1;i<=t;i++)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题意

圣诞老人有 $n$ 个糖果，他想要把这些作为礼物送给孩子们。

如果圣诞老人想要每个孩子得到的糖果数都是不同的正整数，那他最多能将糖果分给多少个孩子。想把他有的 $n$ 个糖果都送出去。

# 思路

题目的要求是尽可能分给更多的孩子，每个孩子得到的糖果数都是不同的正整数。那么最好的情况是第 $1$ 个孩子拿 $1$ 
糖果，第 $2$ 个孩子拿 $2$ 糖果，以此类推，最后多余的糖果给最后一个孩子。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int a[1000];
int main()
{
	cin>>n;
	for(int i=1; i<=10000000; i++)
	{
	    if(n<i) break;
	    else n-=i,a[++ans]=i;
	}
	a[ans]+=n;
	cout<<ans<<endl;
	for(int i=1; i<=ans; i++)cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：Na2_CuCl4 (赞：0)

这道题还是一如既往的简单。

事实上，这道题直接套公式  $ n(n+1)/2 $  就好了，但是最近做多了 dfs 的我表示：递归一下就好了

于是我们就有了这样一个函数：
```cpp
int slove(int x,int step){
	ans+=step;//记录共step个人时需要的糖果数目
	if(ans+step+1<=x)return slove(x,step+1);//记录下一个人来了以后还能不能分到，如果可以继续
                           
	else return step;//否则停止循环
}
```

然后，我们看到题干里要求随便输出一个方案，那我们直接选择第一个人分一个，第二个人分两个……直到第 $answer-1$ 这个方案。

于是又有了这一段代码：

```cpp
for(int i=1;i<=anst;i++){//anst是最多人数
    	if(i!=anst){
		    cout<<i<<" ";
		    n-=i;//剩余糖果数
	    }
    	else cout<<n<<endl;
	}
```

综上，以下是总代码

```cpp
#include<iostream>
using namespace std;
int ans=0;
int slove(int x,int step){/**/
	ans+=step;
	if(ans+step+1<=x)return slove(x,step+1);
	else return step;
}
int main(){
    int n;
    cin>>n;
    int anst=slove(n,1);
    cout<<anst<<endl;
    for(int i=1;i<=anst;i++){
    	if(i!=anst){
		    cout<<i<<" ";
		    n-=i;
	    }
    	else cout<<n<<endl;
	}
	return 0;
}

```

谢谢！




---

## 作者：清清老大 (赞：0)

## 思路

分给每个孩子们的糖果越少，能分到糖果的孩子就越多。可以先给第一个孩子 $1$ 颗糖果，每往后一个孩子就多给一个，把最后剩下的糖果都给最后一个孩子。

## 代码

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,tot = 0; // tot记录已分的糖果数量
    cin >> n;
    for(int i = 1;;i ++)
    {
        if(n < i)
        {
            break;
        }
        tot ++;
        n -= i; //分走了i个糖果
    }
    cout << tot << endl;
    for(int i = 1;i < tot;i ++)
    {
        cout << i << " ";
    }
    cout << tot + n; //把剩余的n个糖果给最后一个人
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
圣诞老人有 $n$ 颗糖果，他想把这些糖果分发给一些小孩子，并想要每个孩子都能得到不同的糖果数目。求能得到糖果的孩子的最大数目，以及他们各自得到的糖果数。

**数据范围：$1\leqslant n\leqslant 1000$。**
## Solution
我们可以往下枚举每个小孩的糖果数目，然后不断地深入搜索，然后得到的第一个合法的方案就是我们想要的得到糖果的孩子的最大数目，直接输出方案即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int n, vis[1007];

void dfs(int x) {
	if(!x) {
		int ans = 0;
		for(int i = 1; i <= n; ++i)	ans += vis[i];
		printf("%d\n", ans);
		for(int i = 1; i <= n; ++i)
			if(vis[i])	printf("%d ", i);
		exit(0);
	}
	for(int i = 1; i <= x; ++i) {
		if(!vis[i]) {
			vis[i] = 1;
			dfs(x - i);
			vis[i] = 0;
		}
	}
}

int main() {
	scanf("%d", &n);
	dfs(n);
}
```

---

## 作者：Luogu_AFOer (赞：0)

第一行的输出是一个数，表示最多能装多少个数，因为要先输出，所以我们可以用一个函数求出来，之和在输入 $n$ 的时候就直接输出，用 $k$ 表示。第二行的输出是 $k$ 个数，表示能装的几个数，可以从 $1$ 开始加，如果还有 $2$ 个数就加不动了的话就要跳出循环。
```
#include<iostream>
using namespace std;
int n,ans=0;
int f(int x){//求出最多能装多少个数 
	int sum=0;
	for(int i=1;;++i){
		sum+=i;
		if(sum+i+1>x) return i;//是sum+i+1，因为要判断能否装下下一个数 
	}
}
int main(){
	cin>>n;
	cout<<f(n)<<endl;//先输出 
	for(int i=1;;++i){	
		if(ans+i*2+1>n) break;//如果不能再装2个数的话，跳出循环 
		ans+=i; 
		cout<<i<<" ";//空格别忘了 
	}
	cout<<n-ans;//最后剩下的数要输出 
	return 0;
}
```


---

## 作者：yuangq (赞：0)

这是一道数学题

详情请见代码

~~~
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,s=0;
	cin>>n;//输入 
	for(int i=1;;i++)
	{
		s++;//因为糖果数量需要不同，所以前面的尽可能少 
		n=n-i;
		if(n<(i+1))//如果下一个装不下了则停止 
		{
			break;
		}
	}
	cout<<s<<endl;
	for(int i=1;i<s;i++)
	{
		cout<<i<<" ";//前面尽可能小就是为1,2,3,4,5…… 
	}
	cout<<n+s;//最后一个把其余补上 
	return 0;
}

~~~

---

## 作者：damage (赞：0)

# 简单的数学题

---

我们都知道，$n$个正数的和最小就是$\sum^{n}_{i=1}i = \frac{n(n+1)}{2}$，所以答案就是$\sqrt{2n}$。

但是若出现像$2\times{2} = 4$是平方数，$\sqrt{4} = 2$，而实际答案却是$1$，我们需要将答案$-1$，简单来说就是设$m = \sqrt{2n}$，若$\frac{m(m+1)}{2}\gt{n}$则```m--```。

因为是```Special Judge```，所以前$n-1$个小朋友分别拿$1$~$n-1$颗糖，最后一个小朋友分$n-\sum^{m-1}_{i=1}i = n-\frac{m(m-1)}{2} = \text{...}$，其实直接循环输出，在过程中把$n$减掉就行了

### 注意特判$n = 1$时的情况
---

代码：

```cpp
#include<stdio.h>
#include<cmath> //根号头文件
int n,m;
int main()
{
	scanf("%d",&n);
	if(n==1) //特判n=1时
	{
		printf("1\n1\n");
		return 0;
	}
	m=sqrt(2.0*n); //计算m
	if((m*(m+1)>>1)>n) --m; //如上文所说
	printf("%d\n",m); //先输出小孩个数
	for(register int i=1;i<m;++i) //循环输出糖果数，注意循环m-1次
	{
		printf("%d ",i);
		n-=i; //记得减去
	}
	printf("%d\n",n); //最后输出剩下的糖果数n
	return 0;
}
```

---

