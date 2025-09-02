# Diverse Permutation

## 题目描述

## 题面翻译
构造一个 $n$ 的排列，使得 $|a_i-a_{i+1}|\ (1\leq i<n)$ 恰有 $k$ 个不同的值。

本题有 Special Judge。

## 说明/提示

$1\leq k < n \leq 10^5$.

## 样例 #1

### 输入

```
3 2
```

### 输出

```
1 3 2
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1 2 3
```

## 样例 #3

### 输入

```
5 2
```

### 输出

```
1 3 2 4 5
```

# 题解

## 作者：菜鸡gyf (赞：37)

本蒟蒻又来~~水~~（蒟蒻的事情，那能叫水吗）写题解了。
## 题意：
构造一个n的排列,使将排列相邻两数相减取绝对值所得到的序列中刚好有k种值。
## 分析
这道题只让我们给出一个数列，也就是说：我们只用找到一个正确答案即可，我们不妨从m=1的情况开始推导。

m=1:1，2，3，4，5……

m=2:1，n，n-1，n-2，n-3……

m=3:1，n，2，3，4，……

其实我们只需要构造前m个数即可，后面的数只需要根据第m个数递增或递减即可，而前m个数可以是1，n，2，n-1，这样的规律。

因此我们可以得出代码（我知道你们是来看这个的）：
```
#include<cstdio>
using namespace std;
int main()
{
	int n,m,i,j,a,b;
	scanf("%d%d",&n,&m);
	a=1;b=n;// a,b两数表示前m个数是1~a,和b~n 
	for(i=1;i<=n;++i)
	{
		if(i<m)
		{
			if(i%2==1)
			{
				printf("%d ",a);
				a++;
			}
			else
			{
				printf("%d ",b);
				b--;
			}
		}
		else
		{
			if(m%2==1)
			for(j=a;j<=b;++j)
			printf("%d ",j);
			else
			for(j=b;j>=a;--j)
			printf("%d ",j);//第m个数两大种用两种输出 
			return 0;
		}
	}
	return 0; 
}
```
请把你的%，带回你的家，请把你的赞留下~

写题解不易，还望管理大大通过。

---

## 作者：pomelo_nene (赞：9)

对于这道题 我们可以直接构造一个序列满足k

我们首尾交替，肯定能够得到k-1个不同的差值绝对值

然后后面的全部选1，我们的序列就是正确的

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[100005],n,k;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1,l=1,r=n;i<=k;++i)
	{
		if(i&1)	a[i]=l,++l;
		else	a[i]=r,--r;
	}
	for(int i=k+1;i<=n;++i)
	{
		if(k&1)	a[i]=a[i-1]+1;
		else	a[i]=a[i-1]-1;
	}
	for(int i=1;i<=n;++i)	printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：yu__xuan (赞：4)

### 题目
[CF482A Diverse Permutation](https://www.luogu.org/problem/CF482A)

### 思路
我们让$1 \sim n$中的最大与最小交替出现$k$，这样可以构造出一个有$k-1$个不同的差值序列，只要让后面的差值都为$1$即可。
```
example:

5 2

1 5 4 3 2 1

我们让最大与最小交替出现了2次是1 5这一段。
我们让后面的差值都为1即可

```

### $Code$ 
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

inline void write(int x) {
	if(x<0) putchar('-'),write(-x);
	else {
		if(x/10) write(x/10);
		putchar(x%10+'0');
	}
}

int n,k;

int main() {
	read(n),read(k);
	int head=1,tail=n;
	for(int i=1;i<=k;++i) {
		if(i&1) {
			write(head);printf(" ");
			++head;
		}else {
			write(tail);printf(" ");
			--tail;
		}
	}
	if(k&1) {//注意奇偶性
		while(head<=tail) {
			write(head);printf(" ");
			++head;
		}
	}else {
		while(tail>=head) {
			write(tail);printf(" ");
			--tail;
		}
	}
	return 0;
}
```

---

## 作者：lhjy666 (赞：2)

### 找到了个规律：从第n-（m-1）位开始每2位分别是当前最大数和当前最小数（如果看不懂那就看代码吧） 
### 所以就免了深搜了 
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[10000005];
int main()
{
	ll n,m,t=0,n1,m1;
	scanf("%lld%lld",&n,&m);
	m1=n;
	for (ll i=1;i<=n;i++)
	{
		a[i]=i;
		if(i==n-(m-1))//从这一位开始位置改变 
		{
			n1=i;
			t++;
		}
		if(t!=0)
		{
			if(t%2==1)
			{
				a[i]=m1;
				m1--;
			}
			else
			{
				a[i]=n1;
				n1++;
			}
			t++;
		}
	}
	for (ll i=1;i<=n;i++)
	{
		printf("%lld ",a[i]);
	}
	return 0;
}
```

---

## 作者：K2sen (赞：1)

## CF482A

### 题目大意 :
构造一种n的序列，让着n个数中间差值的绝对值有k种.

### 解题思路：
显然我们有n个数最多可以组成n-1种不同的差值(感性的意会一下)

然后我们可以知道前k + 1个人可以组成k种不同的差值，然后我们可以第一个放上1

第二个，放上k + 1，第三个放到2，第四个放到k.....

然后我们我们就可以得到一个k，k-1，k-2...的差值，最后的时候放完了k个数之后.

我们就把没放上的数从小到大依次放上，我们可以发现此时，剩下的数

组成的差值一定在上边放上的出现过，而且剩下的那些依次放的时候

可以发现后边的差值都是1.

#### code:
```cpp
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define N 100010
#define M 1010

using namespace std;
int n, m, num[N], cnt;
map<int, bool> ma;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

int main() {
	n = read(), m = read();
	if (m == 1) {//特殊情况
		for (int i = 1; i <= n; i++) cout << i << " ";
		return 0;
	}
	cnt = 1, num[1] = 1;
	int j = ++m, i = 1; ma[1] = 1;
	while (cnt <= m) {
		if (ma[j - 1]) break;
		num[++cnt] = j--;
		ma[num[cnt]] = 1;
		if (ma[i + 1]) break;
		if (cnt < m) num[++cnt] = ++i, ma[i] = 1;
	}
	if (cnt >= n) 
		for (int i = 1; i <= n; i++) cout << num[i] << " ";
	else {
		int last = 2;
		for (int i = cnt + 1; i <= n; i++)
			for (int j = last; j <= n; j++)
				if(ma[j] == 0) {
					num[i] = j;
					last = j;
					ma[j] = 1;
					break;
				}
		for (int i = 1; i <= n; i++)
			cout << num[i] << " ";
	}
}
```


---

## 作者：羽儇 (赞：1)

[CF482A](https://www.luogu.org/problem/CF482A)

---

$Solution$

构造题,一般来说打个表会有助于找到规律

下面数据，$N = 8 , M = [1,8]$ 的某些排列

显然[1,N-M]直接输出即可

后面就是尾和头依次往里

```cpp

i   =    1
1  2  3  4  5  6  7  8  

i   =    2
1  2  3  4  5  6  8  7  

i   =    3
1  2  3  4  5  8  6  7  

i   =    4
1  2  3  4  8  5  7  6  

i   =    5
1  2  3  8  4  7  5  6  

i   =    6
1  2  8  3  7  4  6  5  

i   =    7
1  8  2  7  3  6  4  5  

i   =    8

```


---
正解

~~题解区最短代码？~~

```cpp
#include <cstdio>
using namespace std;
int N,M,s,t;
int main()
{
	scanf("%d%d",&N,&M);
	for(int i = 1 ; i <= N - M ; i ++ )
	printf("%d ",i);s = N - M + 1;t = N ; 
	for(int j = N - M + 1 ;  j <= N ; j ++ )
	{
		printf("%d ",t);t -= 1;
		if(++j <= N)
		printf("%d ",s);s += 1;
	}
	return 0;
}
```
---

打表的时候可以参考一下下面代码

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std ;
int a[10];		
bool vis[10];
int main()
{
	freopen("CF2.out","w",stdout);
	for(int i = 1 ; i <= 8 ; i ++ )
	{
		a[i] = i;
	}
	for(int i = 1 ; i <= 8 ; i ++ )
	{
		cout<<endl;
		cout<<"i   =    "<<i <<endl;
		do
	    {
	    	memset(vis,false,sizeof(vis));
	    	int dif = 0;
		    for(int j = 1 ;  j <= 7 ; j ++ )
		    if(!vis[abs(a[j] - a[j + 1])])vis[abs(a[j] - a[j + 1])] = true , dif ++ ;
		    if(dif != i)continue;
		    for(int j = 1 ; j <= 8 ; j ++)
		    cout<<a[j]<<"  ";
		    cout<<endl;
		    break;
	    }while(next_permutation(a + 1 ,a + 1 + 8 ) );
	}
	
	return 0;
}
```


---

## 作者：_Felix (赞：1)

看题解之前，希望大家先自己列张表，会发现规律哦~

用递归
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[100005];//保存答案，当然你也可以直接输出（假如你能做到的话）
int hhh(int N,int K)
{
	if(N-K>=2)
	{
		a[N]=N;
		hhh(N-1,K);
	}
    /* 例如n=4 k=3时，数列可以是:1 4 2 3
         而n=5 k=3时         是:1 4 2 3 5
     */
	else
	{
		a[1]=1;
		for(int i=2;i<=N;i++)
		{
			if(i%2==0)
				a[i]=a[i-1]+K;//别看我，看⬇
			else
				a[i]=a[i-1]-K;//别看我，看⬇
			K--;
		}
        /* 比如n=2 k=1时:1 2
                 3   2时:1 3 2
                 4   3时:1 4 2 3
                 5   4时:1 5 2 4 3
        */
	}
	return 0;
}
int main()
{
	int n,k;
	cin>>n>>k;//读入
	hhh(n,k);//看⬆啦
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;//输出
	return 0;	
}
```
其实只要列张表就懂了，是不是后悔看题解了呢~


**By 12岁小萌新——你们可爱的czy**

---

## 作者：xyf007 (赞：0)

# 不同的数可在开头处理(首尾交替)
# 剩下只要按序输出，差为一
## 记得处理奇偶
```
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	int l=1,r=n;
	if(k%2==0)
	  {
	    for(int i=1;i<=k;i++)
	      if(i&1)
	        {
	          printf("%d ",r);
	          r--;
		    }
	      else
	        {
	          printf("%d ",l);
	          l++;
		    }
	    for(int i=l;i<=r;i++)
	      printf("%d ",i);
	    return 0;
	  }
	else
	  {
	    for(int i=1;i<=k;i++)
	      if(i&1)
	        {
	          printf("%d ",l);
	          l++;
		    }
	      else
	        {
	          printf("%d ",r);
	          r--;
		    }
	    for(int i=l;i<=r;i++)
	      printf("%d ",i);
	    return 0;
	  }
}
```

---

