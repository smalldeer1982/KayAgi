# SwapSort

## 题目描述

In this problem your goal is to sort an array consisting of $ n $ integers in at most $ n $ swaps. For the given array find the sequence of swaps that makes the array sorted in the non-descending order. Swaps are performed consecutively, one after another.

Note that in this problem you do not have to minimize the number of swaps — your task is to find any sequence that is no longer than $ n $ .

## 样例 #1

### 输入

```
5
5 2 5 1 4
```

### 输出

```
2
0 3
4 2
```

## 样例 #2

### 输入

```
6
10 20 20 40 60 60
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
101 100
```

### 输出

```
1
0 1
```

# 题解

## 作者：AlicX (赞：3)

### 题意

让你通过不超过 $n$ 次交换，使原数组成为不递减数组。

### 思路
因为要使原数组成为不递减数组，所以我们需要先将原数组排序，再用原数组去遍历，因为每一位都是确定好的（由排序数组确定），我们就去遍历后面的数（注意：只遍历后面的数，因为前面的数已经排好序了），看后面的哪一个数等与这个数，就将他们交换，记录一下就可以了。总体时间复杂度为 $O(n^2)$，由于 $n \leq 3000$，不会超时。在这里也提示一下 $O(n)$ 做法，将每一位的数所在的位置映射出来，最后交换，就可以不用遍历了。注意判重即可。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=3010;
int n;
pii ans[N];
int a[N],b[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];//a数组用来排序，b是原数组 
	sort(a+1,a+n+1);//排序 
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(b[i]!=a[i]){//如果这一位与排序后的数不同 
			for(int j=i+1;j<=n;j++){
				if(b[j]==a[i]){//找到了 
					swap(b[i],b[j]),ans[++cnt]={i-1,j-1};//交换一下，记录下来 
					break;
				}
			}
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<ans[i].x<<" "<<ans[i].y<<endl;//输出 
	return 0;//Bye~ 
}
```
可能会有些不足的地方，请大家指出，谢谢！

---

## 作者：zwye (赞：3)


~~这道题太简单了~~
## 题意
就是给一个数串，不超过 $ n $ 次的交换将这个数串从小到大排序。

## 思路
我们很容易想到排序，用 sort 就可以（也可以用选择排序）。
然后从原数列的第一个数开始，看一看这个数是不是它对应位置中的那个数，如果不等于，则从它的下一个数继续找，知道找到数组中的那个数，然后记录，如果等于，则不管它。

## 然后上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],b[100005],c[100005],d[100005],u;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=b[i])
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[j]==b[i])
				{
					swap(a[i],a[j]);
					c[++u]=i,d[u]=j;
					break;
				}
			}
		}
	}
	cout<<u<<endl;
	for(int i=1;i<=u;i++)
		cout<<c[i]-1<<" "<<d[i]-1<<endl;
    return 0;
}
```
本人第一篇题解，如果有错请指正 。 

---

## 作者：scplzy (赞：2)

# 题意
 就是让我们只用交换一种方式完成排序，并且输出被排序过的编号。
# 想法
 在每一次循环中求出比当前小，且最小的数，然后与当前的数交换，并且记录被交换的两个数的编号（注意要从 $0$ 开始） 
## 代码如下↓
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3010],ans,b[3010],c[3010],zx,bh;
int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n-1;i++)
	{
		zx=a[i],bh=i;
		for(int j=i+1;j<n;j++)
			if(a[j]<zx)
			{
				zx=a[j];
				bh=j;
			}
		if(bh!=i)
		{
			swap(a[i],a[bh]);
			ans++,b[ans]=i,c[ans]=bh;
		}	
		cout<<ans<<endl;
		for(int i=1;i<=ans;i++)
			cout<<b[i]<<" "<<c[i]<<endl;
	}
	return 0;
} 
```

---

## 作者：yghjsk (赞：1)

# 题意：
给出一个序列 $a_i$ ，要将这序列从小到大排序，输出最少的次数以及交换方法（具体到哪两个数进行交换）。
# 思路：
从第 $0$ 位开始查看，看一下每个数是不是自己排序后对应位置中的那个数，如果相等，直接记录，如果不相等，就从它的下一个数继续找，直到找到数组中的那个数，然后记录方案，否则不管它，继续循环查找。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],b[10005],a1[10005],b1[10005],sum;//定义数组变量 
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i],b[i]=a[i];//输入 
    sort(b,b+n);//排序方便进行查找 
    for(int i=0;i<n;i++){//一个个逐一查找 
    	if(a[i]!=b[i]){ //如果排序前与排序后的情况不同 
    		for(int j=i+1; j<n; j++)
                if(a[j]==b[i]){//找到排序前的这个数现在排序后的位置 
					swap(a[i],a[j]);//交换 
					a1[sum]=i,b1[sum]=j,sum++;//记录交换方案 
					break;//退出循环 
				}
    	}
            
    }
    cout<<sum<<endl;//输出 
    for(int i=0;i<sum;i++)cout<<a1[i]<<" "<<b1[i]<<endl;//输出方案 
    return 0;
}
```


---

## 作者：WilliamFranklin (赞：1)

这道题太简单了。

### 主要思路

我们可以建一个 $b$ 数组存下原数组（也就是 $a$ 数组）排序后的数列，然后从原数列的第一个元素开始，看一看这个数是不是它对应位置的 $b$ 中的那个数，如果不等于，则从它的下一个数开始找，知道找到 $b$ 中的那个数，然后记录下来，如果等于，则不管。

好啦，贴代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005], b[100005];
int ans1[100005], ans2[100005], sum;
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] != b[i]) {
			for (int j = i + 1; j <= n; j++) {
				if (a[j] == b[i]) {
					swap(a[i], a[j]);
					ans1[++sum] = i;
					ans2[sum] = j;
					break;
				}
			}
		}
	}
	cout << sum << endl;
	for (int i = 1; i <= sum; i++) {
		cout << ans1[i] - 1 << ' ' << ans2[i] - 1 << endl;
	}
    return 0;
}
```
$O(n^2)$ 算法，不会超时，因为：$1\le n\le 3000$。

可能会有些不足的地方，请大家指出，谢谢！

---

## 作者：zhouzhitong6 (赞：0)

## 题意
给 $ n $ 个数（下标从零开始），要将这些数从小到大排序，输出最少的次数以及交换方法（具体哪两个数交换）。
## 思路
从第 $ 0 $ 个开始，看一下每个数是不是自己对应位置中的那个数，如果不等于，则从它的下一个数继续找，直到找到数组中的那个数，然后记录，否则不管它。
## AC代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[3005],b[3005],c[3005],d[3005],s;
int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        scanf("%d",&a[i]),b[i]=a[i];
    sort(b,b+n);
    for(int i=0; i<n; i++)
        if(a[i]!=b[i])
            for(int j=i+1; j<n; j++)
                if(a[j]==b[i]){swap(a[i],a[j]),c[s]=i,d[s]=j,s++; break;}
    cout<<s<<endl;
    for(int i=0; i<s; i++)
        printf("%d %d\n",c[i],d[i]);
    return 0;
}
```


---

## 作者：CCDYJXZ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF489A)。

**题意**：

将一个长度为 $n$ 的序列，通过不超过 $n$ 次的操作，每次交换两个数的位置，将它变成一个单调递增的序列。输出操作的次数以及每次交换的两数的下标。

**思路**：

我们可以先直接将原序列排序并记录，再找每一个经过排序后的数在原序列的位置。找到后，如果位置不一致，就将实际位置与排序后应在的位置现在的数交换并记录此次交换的两个位置，以及交换次数加一。最后先输出交换的次数，再将记录的每次交换的两个位置依次输出。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int aa[3001],ss[3001],a,s,d=0; 
int dd[3001][2];//用来记录每次交换的两个位置。 
int main(){	
	cin>>a;
	for(int i=1;i<=a;i++)
		cin>>aa[i],ss[i]=aa[i];//将另一个用来排序的数组赋值。 
	sort(ss+1,ss+a+1);//排序。 
	for(int i=1;i<=a;i++)
		if(aa[i]!=ss[i]){//如果原序列与排序后的序列不同。 
			int j=i+1;
			for(;j<=a;j++)
				if(aa[j]==ss[i])//找到了在原序列中对应的位置。 
					break;
			swap(aa[i],aa[j]);//交换两个数。 
			dd[++d][0]=i-1;
			dd[d][1]=j-1;//次数加一，并记录交换的两个位置。 
		}
	cout<<d<<endl;//输出次数。 
	for(int i=1;i<=d;i++)
		cout<<dd[i][0]<<' '<<dd[i][1]<<endl;//输出每次交换的两个位置。 
	return 0;
}
```
蒟蒻的一篇题解，如有不满敬请见谅。

---

## 作者：The_FAKIR (赞：0)

## 大意

给定一个长度为 $n$ 的序列，用不超过 $n$ 次交换任意两个元素排序序列。输出交换方案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3005],a1[3005],a2[3005],k;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
        int mina=INT_MAX,minb;
		for(int j=i+1;j<=n;j++){
			if(a[j]<a[i]&&mina>a[j]){
				mina=a[j];
				minb=j;
			}//算最小的。
		}
		if(mina!=INT_MAX){
			swap(a[i],a[minb]);
			k++;
			a1[k]=i;
			a2[k]=minb;
		}//交换储存。
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++){
   		cout<<a1[i]-1<<" "<<a2[i]-1<<endl;
   	}//下标从0开始。
    return 0;
}
```


---

## 作者：19x31 (赞：0)

## 题意
给出序列 $a_{1...n}$，只用交换将其变成有序之后输出交换的编号及次数。

## 思路
大家看一下题目要求，只用交换的排序，而且 $1 \le n \le 3000$。那么很明显，选择排序是可行的，选排指用 $i$ 变量遍历整个数组，每一次又要用 $j$ 遍历 $a_{i...n}$。然后比较 $a_i$ 和 $a_j$，如果 $a_i$ 大于 $a_j$ 则交换 $a_i$ 和 $a_j$。

但是，因为本题要求交换次数不超过 $n$，要进行优化：用 $j$ 遍历时找到小于 $a_i$ 的 $a_j$ 中最小的一个即可。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3005],ans1[3005],ans2[3005],k;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
        int mina=INT_MAX,minb;
		for(int j=i+1;j<=n;j++){
			if(a[j]<a[i]&&mina>a[j]){
				mina=a[j];
				minb=j;
			}//算小于a[i]的a[j]中最小的。
		}
		if(mina!=INT_MAX){
			swap(a[i],a[minb]);
			k++;
			ans1[k]=i;
			ans2[k]=minb;
		}//交换并储存。
	}
	cout<<k<<endl;
	for(int i=1;i<=k;i++){
   		cout<<ans1[i]-1<<" "<<ans2[i]-1<<endl;
   	}//这里减一是因为数组下标从0开始。
		
    return 0;
}
```


---

## 作者：WaterSky (赞：0)

[CF489A SwapSort](https://www.luogu.com.cn/problem/CF489A)

这一道题有很多的做法，我浅谈一种。

我用的方法应该是贪心，不太确定。

## 简要题目：
从小到大排序一个数列，输出最小的交换次数，和交换步骤。

我的方法是：从第一个开始，对于每一个数，都找一找自己后面有没有比自己小的，如果有，找最小的与自己交换，就是最优的方案。

因为在每一个数的前面都已经排序好了，不需要再找前面的数了。

## 证明：
对于每一个位置有两种不同的情况。
### 第一种情况：
自己位置不是这一个位置的数。这一种情况最少交换的次数是多少？很明显，交换 $1$ 次，就可以让这一个位置的数正确。

### 第二种情况：
自己位置是这一个位置的数。不用问了吧！一次也不需要交换。

而我使用的方法两种情况的次数都是一次，甚至还规避了一些次数，所以贪心成立。

我太蒻了，所以没想出更好的方法，代码放在这里：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[10005],minx,mix,ans;
struct wbx{//这里我用结构体记录交换的步骤。
	long long x,y;
}A[10005];
int main(){
    cin>>n;
    for(int i=0;i<n;i++)//题目中说下标从0开始，注意。
        cin>>a[i];
    for(long long i=0;i<n;i++)//题目中说下标从0开始，注意。
    {
		minx=1e10;//记得初始化。
		for(int j=i;j<n;j++) if(minx>a[j]) minx=min(minx,a[j]),mix=j;//找后面的最小值，并记录。
		if(minx!=a[i]) swap(a[i],a[mix]),A[++ans].x=i,A[ans].y=mix;//如果满足第一种情况，那么交换一次，记录交换的两个数。
	}
	cout<<ans;
	for(int i=1;i<=ans;i++)
	cout<<endl<<A[i].x<<" "<<A[i].y;
    return 0;
}
```

---

## 作者：lilong (赞：0)

这题要求用不超过 $n$ 次的交换将 $n$ 个整数从小到大排序。很显然，在最坏的情况下，为了满足条件，我们需要使每个数一步到位，即只与要到达的那个位置上的的数交换一次。

那么我们很容易想到用选择排序了。先回顾一下选择排序，核心代码如下：
```cpp
for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
		if(a[i]>a[j])
			swap(a[i],a[j]);
```

我们很容易发现：当到达第 $i$ 个位置时，前面的 $i-1$ 个数已经有序了，因此我们只需求出 $ \min(a_{i+1},a_{i+2},\cdots,a_n)$ 的位置，将此位置上的数与 $a_i$ 交换，记录答案即可。特别地，若两数的位置相同，则说明 $a_i$ 的位置是正确的，没有必要交换。

实现时注意数组下标从 $0$ 开始，代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int a[10001],n;
int ans,x[10001],y[10001];
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n-1;i++)
	{
		int mi=a[i],id=i;
		for(int j=i+1;j<n;j++)
			if(a[j]<mi)
			{
				mi=a[j];
				id=j;
			}
		if(id!=i)
		{
			swap(a[i],a[id]);
			ans++;
			x[ans]=i;
			y[ans]=id;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
		cout<<x[i]<<' '<<y[i]<<endl;
	return 0;
}
```


---

## 作者：TheSky233 (赞：0)

## Description

给定序列 $a_{1 \cdots n}$，求这个序列最少要交换几次才能变成有序序列，并输出交换方案。

## Solution

### 思路

观察数据范围 $n \leq 3000$，所以可以用时间复杂度为 $O\left(n^2 \right)$ 的冒泡排序，选择排序以及插入排序，这里本人用的是选择排序。

选择排序基本思想：(摘自[这里](https://zhuanlan.zhihu.com/p/29889599))

>选择排序（Selection sort）是一种简单直观的排序算法。其基本思想是：首先在未排序的数列中找到最小元素，然后将其存放到数列的起始位置；接着，再从剩余未排序的元素中继续寻找最小最大元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

最后把每次交换的两个数组下标保存一下即可。

### 正确性证明

题目中说：

>In this problem your goal is to sort an array consisting of $n$ integers in at most $n$ swaps. 

意为最多不能超过 $n$ 次交换。

容易发现，选择排序每次使得数组中第 $k$ 小的元素排在第 $k$ 个，所以选择排序最多排 $n$ 次，证毕。

### 一些小细节
注意数组下标从 $0$ 开始。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}

const int N=3e3+5;
int n,a[N],minn,pos_j;
vector<pair<int,int> > v; 

int main(){
	read(n);
	for(int i=0;i<n;i++) read(a[i]);
	
	for(int i=0;i<n;i++){//选择排序模板
		minn=INT_MAX;
		for(int j=i;j<n;j++){
			if(a[j]<minn){
				minn=a[j];
				pos_j=j;
			}
		}
		if(i!=pos_j){//自己不应和自己交换
			v.push_back(make_pair(i,pos_j));
			a[i]^=a[pos_j]^=a[i]^=a[pos_j];//用^比用swap快！
		}
	}
	
	write(v.size()),puts("");
	for(int i=0;i<v.size();i++) write(v[i].first,v[i].second),puts("");
	return 0;
}

```
## Conclusion
以 $75ms$ 排在最优解第二，祝大家 $\color{green}\texttt{AC}$ 愉快！

---

## 作者：_easy_ (赞：0)

# 思路
这题就是冒泡。

先将输入的原数组排序，再与原数组的备份进行比较。如果一样就不变，否则就在后面找到这个数并交换，记录。由冒泡排序的复杂度可以得知不会超时。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[3005],b[3005],ans,c[3005],d[3005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];//备份数组
	}
	sort(b+1,b+n+1);//将一个排序。
	for(int i=1;i<=n;i++){
		if(a[i]^b[i]){
			for(int j=i+1;j<=n;j++){
				if(a[j]==b[i]){
					swap(a[i],a[j]);
					ans++;
					c[ans]=i;
					d[ans]=j;
					break;//找到就直接记录+退出。
				}
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++){
		cout<<c[i]-1<<" "<<d[i]-1<<endl;
	}
	return 0;
}
```

---

## 作者：Ninelife_Cat (赞：0)

贪心。

从前往后枚举，如果一个位置上的数排序前后是一样的，那么说明它已经有序，就不用管它了，否则我们在这个位置后面的无序序列中找到它排序后对应的数，交换它俩的位置就行。

最坏情况交换次数不会超过 $n$ 次，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define fir first
#define sec second
#define ri register
#define mp make_pair
#define pb push_back
#define int long long
#define inf 2147483647
#define Swap(x,y) (x)^=(y)^=(x)^=(y)
#define fastcin ios::sync_with_stdio(0)
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	ri int x=0,f=0;ri char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return f?-x:x;
}
const int N=5e3+10;
int n,a[N],b[N],cnt;//b为排序完的序列
vector<pair<int,int> > ans;
signed main()
{
	n=read();
	for(ri int i=0;i<n;++i)
		a[i]=b[i]=read();//下标从0开始(题目要求)
	sort(b,b+n);
	for(ri int i=0;i<n;++i)
		if(a[i]!=b[i])//如果有一个位置排序前后的数不一样,说明它需要交换
			for(ri int j=i+1;j<n;++j)//寻找排序后对应的数
				if(a[j]==b[i]) {Swap(a[i],a[j]),ans.pb(mp(i,j)),++cnt;break;}//交换
	cout<<cnt<<endl;
	for(ri int i=0;i<ans.size();++i)
		cout<<ans[i].fir<<" "<<ans[i].sec<<endl;
	return 0;
}
```

---

## 作者：sto_lzy_orz (赞：0)

## 题意
给 $ n $ 个数（下标从零开始），要将这些数从小到大排序，输出最少的次数以及交换方法（具体哪两个数交换）。
## 思路
从第 $ 0 $ 个开始，看一下每个数是不是自己对应位置中的那个数，如果不等于，则从它的下一个数继续找，直到找到数组中的那个数，然后记录，否则不管它。
## AC代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[3005],b[3005],c[3005],d[3005],s;
int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        scanf("%d",&a[i]),b[i]=a[i];
    sort(b,b+n);
    for(int i=0; i<n; i++)
        if(a[i]!=b[i])
            for(int j=i+1; j<n; j++)
                if(a[j]==b[i]){swap(a[i],a[j]),c[s]=i,d[s]=j,s++; break;}
    cout<<s<<endl;
    for(int i=0; i<s; i++)
        printf("%d %d\n",c[i],d[i]);
    return 0;
}
```

---

