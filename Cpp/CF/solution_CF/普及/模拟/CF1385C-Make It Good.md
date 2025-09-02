# Make It Good

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to find the length of the smallest (shortest) prefix of elements you need to erase from $ a $ to make it a good array. Recall that the prefix of the array $ a=[a_1, a_2, \dots, a_n] $ is a subarray consisting several first elements: the prefix of the array $ a $ of length $ k $ is the array $ [a_1, a_2, \dots, a_k] $ ( $ 0       \le k \le n $ ).

The array $ b $ of length $ m $ is called good, if you can obtain a non-decreasing array $ c $ ( $ c_1 \le c_2 \le \dots \le c_{m} $ ) from it, repeating the following operation $ m $ times (initially, $ c $ is empty):

- select either the first or the last element of $ b $ , remove it from $ b $ , and append it to the end of the array $ c $ .

For example, if we do $ 4 $ operations: take $ b_1 $ , then $ b_{m} $ , then $ b_{m-1} $ and at last $ b_2 $ , then $ b $ becomes $ [b_3, b_4, \dots, b_{m-3}] $ and $ c =[b_1,       b_{m}, b_{m-1}, b_2] $ .

Consider the following example: $ b = [1, 2, 3, 4, 4, 2, 1] $ . This array is good because we can obtain non-decreasing array $ c $ from it by the following sequence of operations:

1. take the first element of $ b $ , so $ b = [2, 3, 4, 4,         2, 1] $ , $ c = [1] $ ;
2. take the last element of $ b $ , so $ b = [2, 3, 4, 4,         2] $ , $ c = [1, 1] $ ;
3. take the last element of $ b $ , so $ b = [2, 3, 4, 4] $ , $ c = [1, 1, 2] $ ;
4. take the first element of $ b $ , so $ b = [3, 4, 4] $ , $ c = [1, 1, 2, 2] $ ;
5. take the first element of $ b $ , so $ b = [4, 4] $ , $ c         = [1, 1, 2, 2, 3] $ ;
6. take the last element of $ b $ , so $ b = [4] $ , $ c =         [1, 1, 2, 2, 3, 4] $ ;
7. take the only element of $ b $ , so $ b = [] $ , $ c = [1,         1, 2, 2, 3, 4, 4] $ — $ c $ is non-decreasing.

Note that the array consisting of one element is good.

Print the length of the shortest prefix of $ a $ to delete (erase), to make $ a $ to be a good array. Note that the required length can be $ 0 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, the array $ a $ is already good, so we don't need to erase any prefix.

In the second test case of the example, the initial array $ a $ is not good. Let's erase first $ 4 $ elements of $ a $ , the result is $ [4, 5, 2] $ . The resulting array is good. You can prove that if you erase fewer number of first elements, the result will not be good.

## 样例 #1

### 输入

```
5
4
1 2 3 4
7
4 3 3 8 4 5 2
3
1 1 1
7
1 3 1 4 5 3 2
5
5 4 3 2 3```

### 输出

```
0
4
0
2
3```

# 题解

## 作者：JACK_POT (赞：15)

### 题意
给你一个有$n$个正整数的数列$a$，一个好的数列是每次取它的首元素或尾元素，取出后依次放入一个新的数列，并在原数列中删除，可以得到一个单调非递减序列。问数列$a$的**最长的好的**后缀数组从哪里开始取

### 思路
先上一个模拟过程

![](https://cdn.luogu.com.cn/upload/image_hosting/undhlbbp.png)

由于是从两端开始取，又需要取到的数值单调不下降，所以一个好的数列应该是两边小中间大的（就像一个山峰）

这样可以

![](https://cdn.luogu.com.cn/upload/image_hosting/aht5zm5d.png)

或者这样

![](https://cdn.luogu.com.cn/upload/image_hosting/1t42ayl8.png)

但这样就不行

![](https://cdn.luogu.com.cn/upload/image_hosting/gj2wnuk4.png)

所以我们可以把a从后往前扫描，直到一个数不满足单调非递减（峰值），再从山峰开始往前扫描，直到一个数不满足单调非递增，答案即为这个数的下标（当然如果全部扫完了就不用扫了）

### 代码

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,a,b) for(int i=a;i<=b;i++)
#define fo(i,a,b) for(int i=a;i>=b;i--)
#define PII pair<int,int>
#define il inline
const int M=200005;
int t,n,a[M];
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		fr(i,1,n) scanf("%d",&a[i]);
		int k=n;//初始为n
		while(a[k-1]>=a[k]&&k>1) k--;//上山，直到山顶
		while(a[k-1]<=a[k]&&k>1) k--;//下山
        //注意这里的k-1是确定满足的答案
		printf("%d\n",k-1);
	}
    return 0;
}

```


---

## 作者：zhaoyp (赞：2)

根据题意，我们不难得出，在删除了a数组的一个前缀后，只要剩下的数字构成一个单峰序列（先单调不降，再单调不升），那么就可以成为 good array。

即在数组右端找到一个最长的单峰序列，剩下长度即为答案。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[200005],t;
int up(int le)//寻找从右端起最长单调不降序列
{
	while(le)
	{
		if(p[le] <= p[le-1])	le--;
		else 	break;
	}
	return le;
}
int down(int le)//寻找从右端起最长单调不升序列
{
	while(le-1)
	{
		if(p[le] >= p[le-1])	le--;
		else 	break;
	}
	return le;
}
void work(int len)//寻找单峰序列
{
	len = up(len);
	len = down(len);
	cout << len-1 << endl;//由于len是单峰序列最左端点，所以要-1 
}
void inp()//读入数据 
{
	cin >> t;
	for(int i = 1;i <= t;i++)
	{
		cin >> n;
		for(int j = 1;j <= n;j++)
			cin >> p[j]; 
		work(n);
	}
}
int main()
{
	inp();
}
```


---

## 作者：iMya_nlgau (赞：2)

#### 题目大意

如果一个序列是单峰的（先递增，后递减），我们称该序列是 good array。给你一个长度为 $n$ 的序列 $a$，求需要删除的 $a$ 最短前缀的长度，使它成为 good array。

问题可以转化成求 $a$ 的最长单峰后缀，简单的模拟就可以求解，时间复杂度 $O(n)$。

代码：

```cpp
#include<cstdio>
int a[200010];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int k=n;
		while(a[k-1]>=a[k]&&k>1) k--;
		while(a[k-1]<=a[k]&&k>1) k--;
		printf("%d\n",k-1);
	}
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：2)

贪心。

题目中所给的 good 检验其实就是要求这个数列是一个山峰，也就是说，中间大两边依次减小，这样才能达到要求。

由于删数只能在左边删，所以只用在右边找最长的山峰即可。

两遍 while 就结束了。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[200002],ans;
int main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read();
		re int x=n;
		while(x&&a[x]<=a[x-1])--x;
		while(x&&a[x]>=a[x-1])--x;
		if(x)--x;
		printf("%d\n",x);
	}
}
```


---

## 作者：庄nnnn额 (赞：0)

### 简化版题意：
>有一个数列 $A$，请求出最小的 $x$，去掉 $A$ 的前 $x$ 个元素，能每次去掉 $A$ 的首项或末项，放在一开始为空的数列 $B$ 的末尾，使 $B$ 成为不降数列。
### 分析：
既然要成为不降序列，那么一定得先去掉小的，后去掉大的。那这个 $A$ 数列的元素一定是前后小，越往中间越大（也可能没有前或后）。

突然明白过来，这不就是**双调序列**吗？又由于是去掉前面的元素，所以这个双调序列就是 $A$ 的后缀。

所以，题目就变为了：

>有一个数列 $A$，它的长度为 $l$，请求出最小的 $x$，使 $A$ 的长为 $l-x$ 的后缀是双调序列。

那么，我们只需把这个双调序列的长求出来，就可以求出 $x$ 了。

具体实现细节看代码吧。
### Code(C++):
```c++
#include <bits/stdc++.h>
using namespace std;
int a[200005]；
int main(){
	int t，n;
	scanf("%d",&t);
	a[0]=1e9;
	for(int ii=0;ii<t;ii++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		while(a[n]!=1e9&&a[--n]>=a[n+1])；//求出双调序列的波峰
		while(a[n]!=1e9&&a[--n]<=a[n+1])；//求出双调序列的开头
		printf("%d\n",n);
	}
	return 0;
}
```
[我已成功！](https://www.luogu.com.cn/record/66921275)

---

## 作者：5加1 (赞：0)

咱们试试看

```data
4 3 3 8 4 5 2
```

那么删掉前面 4 个数 `4 3 3 8` 就能使后面的 `4 5 2` 成立，因为通过上面那个操作能把 `4 5 2` 变成 `2 4 5` 。

左面的是原来的序列，右面的是新产生的数列。

```
[4 5 2] / []
[4 5] / [2]
[5] / [2 4]
[] / [2 4 5]
```

`2 4 5` 就是~~什么~~Good数列。

其实可以把像 `4 5 2` 这样的数列想象成 $4<=5>=2$ 即 $a_1<=...<=a_{i-1}<=a_{i}>=a_{i+1}>=...>=a_n$

所以这题用~~模拟~~指针的方法去做比较容易。

因为这个题要从前面往后面删除数，所以应该从后面开始算。

先用一个循环去算 $a_i$ 到 $a_n$ 之间，然后再用一个循环去算 $a_i$ 到 $a_{del}$ 之间（这里的 $del$ 代指的是要删除的位置后一个位置）

所以这两个循环就是这样的

```cpp
while (n > 1 && a[n - 1] >= a[n]) -- n;
while (n > 1 && a[n - 1] <= a[n]) -- n;
```

上面说的 $del$ 其实就是现在这两个 `while` 之后算出来的 $n$ 。

Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t, n, a[200005];
int main ()
{
	scanf ("%d", &t);
	while (t --)
	{
		scanf ("%d", &n);
		for (int i = 1; i <= n; i ++)
			scanf ("%d", &a[i]);
		while (n > 1 && a[n - 1] >= a[n]) -- n;
		while (n > 1 && a[n - 1] <= a[n]) -- n;
		printf ("%d\n", n - 1);
	}
	return 0;
}
```

---

## 作者：WanderOvO (赞：0)

## 题意

有一个序列$a$，我们每次可以从序列的左端或者右端拿出一个元素，放在序列$c$的末尾（序列$c$最开始为空），直到序列$a$的元素被全部放到$c$中。如果$c$序列是单调不降的，那么我们称$a$序列是好的。显然对于不同的输入，$a$序列不总是好的，所以我们考虑删除掉序列$a$的前$x$个元素（即长为$x$的前缀），使得序列剩下的部分按照上面的规则能够生成单调不降的序列$c$。求需要删除的前缀的最小长度。

## 思路来源

首先膜一波$O(n)$算法就能搞定的大佬们，我确实没想到$O(n)$的做法。

我之前有见过类似的问题，就是有一个序列，要求我们删除多少个之后还能满足什么性质，求最小删除个数，所以在这里我最开始也是直接把它归为这类问题了，**一般这类问题总会有贪心或者单调性之类的性质**。

我们要求最小删除个数。假设最少要删除$x$个，那么我们删除$0,1…x-1$个肯定都是不能保证满足能够从两头拿数生成的数列$c$是单调不减的。再考虑如果删除多了会是什么情况，这个时候还能不能生成单调不降的$c$呢？事实上还是可以的。考虑到删除$x$个的情况，这个时候生成的数列我们叫做$c$。假设删除了$x+cnt$个元素，那么我们敢肯定的是，$c$中元素的相对顺序是不会变的，只不过我们要从$c$中拿去几个元素，拿去之后得到的新的$c$仍然是满足题意的。所以，这道题的答案有单调性，可以用二分来做。

在$check$的过程中，我们要尝试生成$c$序列，这个时候可以每次优先选择两端中比较小的端放入$c$中，并且实时比较一下当前元素是不是不比上一次的元素小就好了。

复杂度$O(nlogn)$，跑$2e5$的数据还是可以通过的。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 99999999999
using namespace std;
const int N=2e5+9;
ll t,n,a[N];
bool check(ll k);
int main(){
	ll l,r,mid,ans;
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		l=1;
		r=n;
		ans=n;
		if(check(0)){
			printf("0\n");
			continue;
		}
		while(l<=r){
			mid=(l+r)/2;
			if(check(mid)){
				r=mid-1;
				ans=min(ans,mid);
			} else {
				l=mid+1;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
bool check(ll k){
	ll l=k+1,r=n,now=0;
	if(l>n) return true;
	while(l<=r){
		if(a[l]<now && a[r]<now){
			return false;
		}
		if(a[l]<=a[r]){
			if(a[l]>=now){
				now=a[l];
				l++;
			} else {
				now=a[r];
				r--;
			}
		} else {
			if(a[r]>=now){
				now=a[r];
				r--;
			} else {
				now=a[l];
				l++;
			}
		}
	}
	return true;
}
```



---

## 作者：suyue1098765432 (赞：0)

### 题目大意：

定义good数组：如果一个数组$b$,每次从队首或队尾取数，取出的数能构成一个单调递增序列，则称这个序列为good数组。

有t组询问，每次询问给出一个数列，问最少从开头删多少个数能使它成为一个good数组。

### 做法：
这个题可以用二分答案的思想，算出答案,

对于检验删除前$k$个数，直接根据题意模拟，设输入的数组为$sl$,删掉$k$个数之后头指针$head=k+1$尾指针$tail=n$,然后不断从数组中取数，取出$min(sl[head],sl[tail])$然后把它加入到一个数组$a$中，如果取出的数大于$a[lena]$(lena代表$a$元素个数)，则不成立。如果把$sl$取完了仍然没有不成立，则取前k个数成立。

复杂度O($\Sigma nlogn$),比最有复杂度O($\Sigma n$)稍逊色一点，但仍能通过此题。

### 代码：

###### c:
```c
#include<stdio.h>
int a[200001],sl[200001],lena;
int n,t,m;
int read(){
	int zf=1,res=0;
	char ch;
	while((ch=getchar())<48||ch>57)if(ch=='-')zf=!zf;
	res=ch^48;
	while((ch=getchar())>=48&&ch<=57)res=(res<<3)+(res<<1)+(ch^48);
	return zf?res:(-res);
}
int check(int k){
	if(k==n)return 1;
	lena=0;
	int head=k+1,tail=n;
	while(head<=tail)
		if(sl[head]<=sl[tail])if(sl[head]>=a[lena])a[++lena]=sl[head++];else return 0;
		else if(sl[tail]>=a[lena])a[++lena]=sl[tail--];else return 0;
	return 1;
}

int main(){
	t=read();
	int l,r;
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)sl[i]=read();
		l=1;r=n-1;
		if(check(0)){printf("0\n");continue;}
		while(l<=r){
			int mid=(l+r)>>1;
			if(!check(mid))l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
}
```

###### pascal:
```pascal
var
    a,sl:array[0..200000]of longint;
    lena,n,t,m:longint;
function check(k:longint):boolean;
var head,tail:longint;
begin
    if k=n then exit(true);
    lena:=0;
    head:=k+1;tail:=n;
    while head<=tail do
        if sl[head]<=sl[tail] then begin
            if sl[head]>=a[lena] then begin
                lena:=lena+1;
                a[lena]:=sl[head];
                head:=head+1;
            end else exit(false);
            end
        else begin
            if sl[tail]>=a[lena] then begin
                lena:=lena+1;
                a[lena]:=sl[tail];
                tail:=tail-1;
            end else exit(false);
        end;
    exit(true);
end;
var l,r,j,i,mid:longint;
begin
    read(t); 
    for j:=1 to t do begin
        read(n);
        for i:=1 to n do read(sl[i]);
        l:=1;r:=n-1;
        if check(0) then begin writeln(0);continue;end;
        while l<=r do begin
            mid:=(l+r)div 2;
            if check(mid) then r:=mid-1
            else l:=mid+1;
        end;
        writeln(l);
    end;
end.           
```


我可能写的不好，如果有问题请各位dalao不吝赐教，谢谢。


---

## 作者：chenxia25 (赞：0)

>### [CF题目页面传送门](https://codeforces.com/contest/1385/problem/C)

>题意紫帆。

不难发现一个数列是好的当且仅当它非严格单峰。自证不难。又发现，删掉前缀相当于留下后缀（这个出题人迷惑的太失败了），右端点是不变的。于是贪心，从右往左找到最左边的一个可以当峰值的位置，然后再从峰值往左边找到最左边的左端点。最终答案就是左端点减一。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200000;
int n;
int a[N+1];
void mian(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	int las;
	for(int i=n;i;i--){//找最左峰值 
		if(i<n&&a[i]<a[i+1])break;
		las=i;
	}
	int las0;
	for(int i=las;i;i--){//找最左左端点 
		if(i<las&&a[i]>a[i+1])break;
		las0=i;
	}
	cout<<las0-1<<"\n";
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

