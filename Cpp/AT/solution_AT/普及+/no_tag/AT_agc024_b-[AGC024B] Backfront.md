# [AGC024B] Backfront

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_b

$ 1 $ 以上 $ N $ 以下の整数を並び替えてできる数列 $ (P_1,P_2,...,P_N) $ が与えられます。 次の操作を繰り返してこの列を昇順に並び替えるとき、操作の回数の最小値を求めてください。

- 数列の要素を $ 1 $ つ選び、その要素を列の先頭または末尾のうち好きなほうに移動する

なお、この操作によって与えられた列を昇順に並び替えられることは証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ (P_1,P_2,...,P_N) $ は $ (1,2,...,N) $ の並び替えである
- 入力はすべて整数である

### Sample Explanation 1

例えば、以下の操作によって列を昇順に並び替えることができます。 - $ 2 $ を先頭に移動する。新しい数列は $ (2,1,3,4) $ となる。 - $ 1 $ を先頭に移動する。新しい数列は $ (1,2,3,4) $ となる。

## 样例 #1

### 输入

```
4
1
3
2
4```

### 输出

```
2```

## 样例 #2

### 输入

```
6
3
2
5
1
4
6```

### 输出

```
4```

## 样例 #3

### 输入

```
8
6
3
1
2
7
4
8
5```

### 输出

```
5```

# 题解

## 作者：_32bit_Silentnight (赞：5)

## 题目分析
题目要我们使不进行移动的数字数量最大化。怎么让移动的次数最少呢？

我们用一个极端的样例试一试：

```cpp
输入    输出
5		4
5
4
3
2
1
```

简述一下移动过程：
$$5\space4\space3\space2\space 1 \Rightarrow 5\space4\space3\space1\space 2 \Rightarrow5\space4\space1\space2\space 3 \Rightarrow 5\space1\space2\space3\space 4 \Rightarrow1\space2\space3\space4\space 5 $$
$4$ 次。

所以，最多的移动次数为 $n-1$ 次！

我们给出证明：定义 $A$ 为那个序列，（在最坏情况）我们指定 $v$ 为数列第 $i$ 小的数，那么在第 $i-1$ 次移动到最后面。而 $A$ 中最小的数不用动，因为其他的序列元素向最后移动，到了序列 $A$ 的最大数字，$A$ 中最小的数自动成了 $A_1$。

但是有一些特殊的，例如下面的：1 8 4 2 7 3
$$1\space8\space4\space2\space7\space3 \Rightarrow 1\space8\space2\space7\space3\space4\Rightarrow1\space8\space2\space3\space4\space7\Rightarrow1\space2\space3\space4\space7\space8 $$

$3$ 次？！

为什么呢？1 2 3 可以永远不动，只需要 4 7 8 挨个往后移！ 

**所以，次数为：$n$ 减最长挨个上升的“子序列”的长度！**

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b[200001]={0},i,m=-1,k=0,x;scanf("%d",&a);//定义变量。
   /*
   为什么要 b[200001]={0}？因为：第 8 句涉及到 b[0]。
   m=-1 是保险起见。
   */
	for(i=1;i<=a;i++){
		cin>>x;
		b[x]=b[x-1]+1;//关键，求“最长上升子序列”。
		m=max(m,b[x]);//更新。
	}
	cout<<a-m;
}
```

---

## 作者：tanghairong (赞：4)

首先分析一下，最多 $n-1$ 次可以将数组变成有序的（指定一个数，将比这个数小的数按降序依次放到左边，将比这个数大的数按升序依次放到右边）

那么，在什么情况下，不需要 $n-1$ 次调整呢？

如果在原数组中有一段本身就是一个一个递增的话，那么这几个数就不要做任何处理。比方说样例 2（$n=6$ ）的序列：

这时我们发现， $5,6$ 就是一个每次递增一个的子序列，而且这也是最长的一个子序列。那么，除去 $5,6$ 不动，其它的按照上面的方法进行排序，总共进行 4 次移动，就可以把原序列变得有序。

所以，我们就只需要求出原序列中最长的每次严格递增一个的子序列，用原序列长度 $n$ 减去最长子序列长度 $ans$ 即可。

那么，我们如何求出这个 $ans$ 呢？

我们定义一个数组 $k$，表示在原数组中每个数的出现位置。

还是用样例 2 的栗子： 3 2 5 1 4 6

3 的出现位置是 1，所以 $k[3]=1$ ；

4 的出现位置是 5，所以 $k[4]=5$；

以此类推。

可以得知，$k$ 数组的连续最长上升子序列长度就是 $ans$。

code：
```cpp
#include<iostream>
using namespace std;
int n,k,s=1,ans,p[200005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k;
        p[k]=i;
    }
    for(int i=1;i<n;i++){
	if(p[i+1]>p[i])s++;
    	    else{
	        ans=max(ans,s);
	        s=1;
	    }
    }
    ans=max(ans,s);
    cout<<n-ans;
    return 0;
}
```
看完之后，如果觉得有帮助，点个赞呗。

管理员大大求过qwq

---

## 作者：zjyqwq (赞：4)

### AT3959 [AGC024B] Backfront题解
Pascal题解来一发！！！


------------
#### 解题思路

观察此题，注意到 $n<=2 \times 10^5$，也就是 $200000$,考虑 $O(n)$。

通过证明~~瞎搞~~可得，此数列最多只需 $n$ 次操作。

具体操作：将 $n$~$1$ 各个数分别放到最前，便可得到。

略加思索，不难发现只要从序列中任选一数 $x$ 作为基准，将比他小的数按 $x-1$ 到 $1$ 的顺序放到 $x$ 前面，将比他大的数按 $x+1$ 到 $n$ 的顺序放到 $x$ 后面，这样一来 $x$ 便无需移动，整个序列只需 $n$-$1$ 次移动。

既能使一个数不动，那也能使一个序列不动。哪些序列可以像一个数一样可以不动呢？我们来举一个例子。

 样例#1
```
4
1
3
2
4
```
此样例我们来试一下。

第0次```1324```

第1次```2134```

第2次```1234```

这种方法用了2次将序列排好了，分别把 $2$、$1$ 按顺序放到队首。

这里 $3$、$4$ 都没有动啊！！！

我们再自己试一下，可以得出一个结论：

 当一段数字为单调的，且这段数字的位置也是按数字单调顺序（上升或下降）时，这一坨数字便可以抱团组在一起，不需要移动。

现在，我们只要用 $O(n)$ 循环跑一遍，读入数字，用桶记录下标，再跑一遍循环，找到可以抱团的最长序列，记录长度，最后输出 $n$ 减去长度就可以了。

本人蒟蒻，如果有没讲明白的，请多画图，多模拟。再不理解……参考我的程序！

#### AC code
```pascal
uses math;//使用max函数，需要用到的库。
var
n,i,x,t,ans:longint;
a:array[0..200005]of longint;//定义部分，由于输入序列为1~n的序列，所以下标只要根据n就好了。
 begin
  readln(n);
  for i:=1 to n do
   begin
    readln(x);//原数字不需要保存，用x代替。
    a[x]:=i;
   end;
  t:=1;ans:=1;//注意！！！这里要赋初值，这个数列个数至少为一。
  for i:=2 to n do
   if a[i]>a[i-1]then
    begin
     t:=t+1;
     ans:=max(ans,t);
    end//找我们想要的最长序列序列。
   else t:=1;
  write(n-ans);//输出即可！！！
 end.
```


---

## 作者：fish_love_cat (赞：3)

黄着实有些低了，绿差不多。

---

阅读题面，可以知道题目要我们使不进行移动的数字数量最大化。但是我们应该如何做才能让移动尽量少呢？我们可以设计一个极端的样例推一遍。

读入：

```
5
5 4 3 2 1
```

输出：

```
4
```

这是一个最遭的情况，从中我们可以知道，答案最多就是 $n-1$。因为其他数字都排好了，剩下的数字也就等于排好了。

---

同理，观察样例 1 可发现，只需要把 3 和 4 往后排好了，那么 1 就会和 2 碰上，自动排好了。

欸？有没有发现什么呢？对于一段每次递增一个上升的子序列，在排好其他数字的同时，这个子序列也会自动排好。如果这个子序列越长，需要排的数字就会越少。既然如此，这道题就变成了：

给你一串数字，求里面最长的每次递增一个上升的子序列的长度，记作 $len$，输出 $n-len$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int maxx=-1;//求len的最大值
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        a[x]=a[x-1]+1;//继承它的上一个数字连续的数量，再加上自己
        maxx=max(maxx,a[x]);//最大值
    }
    cout<<n-maxx<<endl;//n-len
    return 0;
}
```

[Accepted](https://www.luogu.com.cn/record/109666121)

代码不难，重在思路 qwq

---

## 作者：xiaozeyu (赞：3)

这道题的大致意思：

有一个长为 $n$ 的序列

有两个操作:

将一个数移到最后或将一个数移到最前

问将排列排序最少要几次操作

其实只要推推就会发现，只要求出已经有序的最长长度即可

代码实现如下：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register long long i=a;i<=b;i++)
#define Rep(i,a,b) for(register long long i=a;i>=b;i--)
using namespace std;
inline long long read()
{
	char c=getchar();long long x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
long long x,a[200010],n,ans=-0x3f3f3f,sum=1;
int main()
{
	n=read();
	For(i,1,n)
	{
		x=read();
   		a[x]=i;
  	}
    For(i,1,n-1)
    {
    	if(a[i+1]>a[i]) sum++;
    	else ans=max(ans,sum),sum=1;
	}	
    ans=max(ans,sum);
    cout<<n-ans;
}

```

---

## 作者：SalN (赞：2)

### 题目描述

给定一个 $1$ 到 $N$ 的排列，通过不断选择该序列中的元素，并将其放到序列的开头或末尾来对其进行排序

求最少需要几次这样的操作才能使得序列有序

其中 $1\le N\le 2\times 10^5$

注意这里 ⌈ 有序 ⌋ 指的是 $1,2,...,N$ 这样单调递增哈

----

### 解题思路

首先最为暴力的，我们会想到将每一个数分别放到两端之一，这样要 $n$ 次，虽然这样可能出现放了之后跟原来一样的愚蠢情况 qwq

我们可以发现，其实这么做一般而言有点多余

因为原来的序列可能存在不断 $+1$ 的子序列，对于这部分我们可以移动走插在其中的其它数，然后就不用对其中的数进行操作，这样无疑为我们省下了很多步骤

比如 $1,5,2,4,3$，我们分别将 $4,5$ 放到最后面即可

这样省下来的次数正好是这个不断 $+1$ 的子序列长度哦

事实上，我们只能让一个这种不断 $+1$ 的子序列保持不动，两个的话就不可能啦，因为其中的数肯定存在逆序，必须要移动！

那么我们自然选择贡献最好的也就是最长的这种不断 $+1$ 的子序列

那么最长不断 $+1$ 的子序列怎么求呢？注意到是 $1$ 到 $N$ 的一个 排列，我们可以考虑设 $f[x]$ 表示以数值 $x$ 结尾的最长不断 $+1$ 的子序列长度最大值，如果在之前出现过 $x-1$，显然 $f[x]=f[x-1]$，否则 $f[x]=1$

具体实现的时候我们可以初始化 $f[k]=0$ 然后直接递推，结果是一样的

复杂度那当然是 $O(N)$ 啦

----

### 代码实现

代码超级短哦

```cpp
#include<bits/stdc++.h>
#define MN 201000

using namespace std;

int n, a[MN];
int f[MN], qwq;

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) {
		scanf("%d", a+i);
		f[a[i]]=f[a[i]-1]+1;
		qwq=max(f[a[i]],qwq);
	}
	printf("%d\n", n-qwq);
	return 0;
}
```


---

## 作者：yyz_100110 (赞：1)

**前言：**请问这是绿题，我对此难度深感怀疑，建议降难度。其次翻译不完整，没有详细说明是要递进排序，所以很容易全错。      
**思路：**没思路怎么办，拿着样例去算算就会明白。
~~~cpp
输入   输出
4      2
1
3
2
4
~~~
这种题有一点像抽屉原理，但不同的是他是要最少操作数。所以我们需要使用到 ```max``` 去判断最大值，并且计算上他自己本身去排列，然后将 ```n-maxn``` 就可以得出了。         
##  _ACCode_ 
```cpp
#include<iostream>
using namespace std;
int a[200086],maxn=-1,k,n;
//maxn 用来存操作数，防止和 max 混在一起，这里的数组要设大一点，要不烂容易 RE，本人亲测。
int main(){
    scanf("%d\n",&n);//输入
    for(int i=1;i<=n;i++){
        scanf("%d\n",&k);
        a[k]=a[k-1]+1;//计算自己
        maxn=max(maxn,a[k]);//用 max 去计算最大值
    }
printf("%d\n",n-maxn);//输出，计算出操作数
return 0;//比赛要写
}
```

---

## 作者：water_tomato (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT3959) [博客版本](https://code.watertomato.com/at3959-agc024b-backfront-%e9%a2%98%e8%a7%a3/)

## 题意

从一个 $1 \sim n $ 的排列中不断选择元素放在头或尾，最终使其有序，询问操作次数。

## 解析

首先容易发现，至多操作 $n$ 次一定能够使其有序（一个一个拎出最小的或最大的）。

然后我们发现，$n$ 次可以变为 $n-1$ 次，我们先随意确定一个数，比它小的按顺序拎到它左边，后边亦然。

接着我们考虑，能否从确定一个数变为确定一个序列呢？显然，如果有一段序列，其数字是严格一个一个递增的，位置也是递增的（例如：$1,4,2,5,6,3$ 中的 $1,2,3$）。我们可以永远不选择这些数，而按照前面所叙述的原则将其他数按顺序拎到左边或右边即可，答案即为这个最长递增子序列的长度。

那么怎么求呢？只需要把每一个数字对应的位置记录下来，然后按数字大小遍历并判断是否大于前一个即可，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],b[N];
int ans,tmp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[a[i]]=i;//记录位置 
	}
	tmp=ans=1;
	for(int i=2;i<=n;i++){//寻找最长递增子序列 
		if(b[i]>b[i-1]){//如果连续的几个数，位置递增，显然是一个递增子序列 
			tmp++;
			ans=max(ans,tmp);
		}
		else tmp=1;
	}
	printf("%d\n",n-ans);
	return 0;
} 
```



---

## 作者：xzy__xzy (赞：1)

翻译

小 A 有一个双向队列，队列里有数字 1-N 这 N 个数字，每次可以从队列中任意拿出一
个数字，将其放在队列的头部或者队列的尾部，不停这样操作，直到队列变成升序，求最小
操作次数。


找出最长递增子序列的长度len，答案为n-len;

代码






```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[50005],pos[50005];
void dfs(int sz,int wz,int cnt)
{
	if(pos[sz+1]<wz)
	{
		ans=max(ans,cnt);
		return;
        }
	else dfs(sz+1,pos[sz+1],cnt+1);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i;
    for(int i=1;i<=n;i++) dfs(i,pos[i],1);
    cout<<n-ans;
    return 0;
}
```



---

## 作者：ylch (赞：0)

# 洛谷 [AT_agc024_b](https://www.luogu.com.cn/problem/AT_agc024_b) 题解

和 [CF605A](https://www.luogu.com.cn/problem/CF605A) 重题了，大家可以去刷，一道题目，双倍经验！

## 解题思路

不难发现，每次排序的操作都是有规律的：

- 对于排好序的有序序列（可能是中间间断的），我们不予改动。

- 对于乱序的数字，我们要按照从大到小的顺序把乱序的数字挪到队头（或队尾），使得有序的间断序列变成连续序列，这样最终就形成有序序列。

比如样例 $\texttt{325146}$，其排序过程如下：

$\texttt{325146} \rightarrow \texttt{432516} \rightarrow \texttt{342516} \rightarrow \texttt{234516} \rightarrow \texttt{123456}$

开始我们发现有序序列为 $\texttt{32\color{red}5\color{black}14\color{red}{6}}$，那么就要把有序序列中间的无关数字挪开，按照从大到小的顺序依次挪动 $\texttt{4},\texttt{3},\texttt{2},\texttt{1}$，这样就使数列归位了。

再比如数列 $\texttt{153642}$：

有序数列为 $\texttt{\color{red}1\color{black}5364\color{red}2}$，那么要依次挪动 $\texttt{3,4,5,6}$，就可以得到有序序列。具体步骤如下：

$\texttt{153642} \rightarrow \texttt{156423} \rightarrow \texttt{156234} \rightarrow \texttt{162345} \rightarrow \texttt{123456}$

综上所述，我们的方法是正确的。

同时发现，两个例子的调换次数都是 $n - \text{开始有序序列长度}$，那么问题就转化成求初始状态下的最长有序序列长度，再用 $n$ 减去初始状态下的最长有序序列长度，就得出了答案。

## AC 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int n,x;
int ans = -1;
int a[200005];

signed main()
{
	cin >> n;
	for (int i=1; i<=n; i++)
	{
		cin >> x;
		a[x] = a[x-1] + 1;
		ans = max(ans, a[x]);
	}
	cout << n-ans << endl;
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！祝大家 AC！

---

## 作者：Dr_Octopus (赞：0)

### 题意

给定一个 $1 \sim n$ 的数列，你需要不断选择其中的元素放到序列开头或末尾，直到序列递增，问最少要操作几次。

------------

### 思路

我们拟定一个数列，比如说 $1$ $8$ $5$ $2$ $6$ $3$。
仔细想想，想要使这个数列变成递增的，该怎么做呢。

通过观念可以发现只看数列中的 $1$ $2$ $3$，这三个数其实已经满足递增了。而在这道题目中，我们移动一个数字，后面数相当于会自动向前补位，所以对原先就满足递增的数不会造成影响。

于是，实际上我们只需求出对与一段连续的数它在排列中已经有序的最长长度，剩下的数暴力放到最前 $/$ 最后即可。

**结论**：答案为 $n$ 减最长上升子序列的长度......

------------

### code
```cpp
#include <bits/stdc++.h>
const int N = 10e5 + 10;
using namespace std;

int n, k, ans, len = 1;
int a[N];

signed main() {
    
    cin >> n;
    for (int i = 1;i <= n; i ++ ) {  cin >> k; a[k] = i;  }
    for (int i = 1;i <= n - 1; i ++ ) {
    	if (a[i + 1] > a[i]) len ++ ;
        else {
        	ans = max(ans, len);
        	len = 1;
		}
	}
    int v = n - max(ans, len);
	printf("%d\n", v);
    
    return 0;
}
```



---

## 作者：Bc2_ChickenDreamer (赞：0)

## AT_agc024_b [AGC024B] Backfront 题解

### 题目分析

我们首先可以发现一段严格上升子序列，在移动其他数字的同时，这个序列也会排序好。

那么我们就可以把问题简化成输出 $n$ 减去数组内最长的严格上升的子序列长度。那我们可以用 dp 来解决。那么他的动态转移方程为：

$$ f_{a_i} = f_{a_i - 1} + 1$$

这样子代码就出炉了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define qwq ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)  
const int N = 200020;
int n, a[N], b[N], f[N], len = -1, x;
map<int, int> c;

signed main()
{
	qwq;
    cin >> n;//输入 
    for (int i = 1; i <= n; ++ i)//循环读入 
    {
    	cin >> a[i];//读入 a[i] 
    	b[i] = a[i];
		c[a[i]] = i;
		f[i] = 0;
	}
	sort(b + 1, b + n + 1);//给 b 数组排序 
	for (int i = 1; i <= n; ++ i)
	{
		a[c[b[i]]] = i;
	} 
	for (int i = 1; i <= n; ++ i)//dp 递推 
	{
		f[a[i]] = f[a[i] - 1] + 1;//状态转移方程
		len = max(len, f[a[i]]);//取最大值 
	}
	cout << n - len << endl;//输出 
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 用线性复杂度切掉这道题。

## 题意
有一个 $\text{1}$ 到 $n$ 的排列，每次操作从排列中任选一个数放在排列的最前或最后，求使排列有序的最少操作次数。

## 分析
首先，长度为  $ n $  的数列一定能够在至多  $ n $ 次操作内排好序。

并不严谨的证明：先在下标 $\text{1}$ 到 $n$ 中找出最大的数提到前面，接着在 $\text{2}$  到  $n$ 中找到最大的数提到前面，以此类推，一定能够在  $ n $ 次内完成排序。并且，如果想要一直移动到队尾，那么只需找最小的数即可。

那么怎么找到最小步数呢？

注意到数列是一个  $\text{1}$  到   $n$  的排列。假设在数组中可以找到一个连续递增的子序列（下标不一定连续），那么将其他数分成三类：

$\text{1：}$ 比这个连续的子序列中最小的数小。

$\text{2：}$ 在这个连续的子序列中。

$\text{3：}$ 比这个连续的子序列中最大的数大。

我们只需要保证 $\text{2}$ 不变，把所有的 $\text{1}$ 用上述证明的方法往前面提，把所有的 $\text{3}$ 用同样的方法往后面提，用 $\text{1}$ 和 $\text{3}$ 数个数总和的次数就可以使原序列有序。

于是原问题转化为求最长连续递增的子序列。设 $f[x]$ 为以数值 $x$ 所在下标结尾的连续递增子序列的长度，我们只需要在读入数列时，判断比当前读入的数小 $\text{1}$ 的数是否出现过，若出现过则 $f[x]=f[x-1]+1$，没有出现过则赋为  $\text{1} $。

时间复杂度 $O(n)$。

## $ \text{Code}$
```
#include<bits/stdc++.h>

#define youhua ios::sync_with_stdio(0);cin.tie(0), cout.tie(0);

using namespace std;

const int maxn=2e5+5;
int f[maxn];
int n, ans = 0;

int main()
{
	youhua//输入输出优化
	
	cin >> n;
	for(int i = 1;i <= n;i ++) {
		int x;
		cin >> x;
		f[x] = f[x - 1] + 1;
		ans = max(ans, f[x]);
	}
	cout << n - ans; 
	return 0;
}
```

---

