# Bogosort

## 题目描述

You are given an array $ a_1, a_2, \dots , a_n $ . Array is good if for each pair of indexes $ i < j $ the condition $ j - a_j \ne i - a_i $ holds. Can you shuffle this array so that it becomes good? To shuffle an array means to reorder its elements arbitrarily (leaving the initial order is also an option).

For example, if $ a = [1, 1, 3, 5] $ , then shuffled arrays $ [1, 3, 5, 1] $ , $ [3, 5, 1, 1] $ and $ [5, 3, 1, 1] $ are good, but shuffled arrays $ [3, 1, 5, 1] $ , $ [1, 1, 3, 5] $ and $ [1, 1, 5, 3] $ aren't.

It's guaranteed that it's always possible to shuffle an array to meet this condition.

## 样例 #1

### 输入

```
3
1
7
4
1 1 3 5
6
3 2 1 5 6 4```

### 输出

```
7
1 5 1 3
2 4 6 1 3 5```

# 题解

## 作者：C　C　A (赞：8)

# $CF1312B\ Bogosorts'\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$给定$a$数组，给它重新排序，使其对于任意$i,j(i\not = j\&\&i,j<=n),i-a[i]\not =j-a[j]$。

## $Solution$

$\qquad$前两天才在$AT$上做过一个差不多的。

$\qquad$因为$i$严格单调递增，于是我们考虑让$a$单调不增，这样$i-a[i]$就严格单调递减，其为对于任意$i,j(i\not =j\&\&i,j<=n),i-a[i]\not=j-a[j]$的充分条件。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;

int T , n , a[N];

int main(){
	scanf("%d" , &T); while(T--){
		scanf("%d" , &n);
		for(int i = 1; i <= n; i++)
			scanf("%d" , &a[i]);
		sort(a + 1 , a + n + 1);
		for(int i = n; i >= 1; i--)
			printf("%d " , a[i]);
		puts("");
	}
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：do_while_false (赞：3)

[题目](https://www.luogu.com.cn/problem/CF1312B)

题目大意:
- 构造一个 $a$ 序列
- 使得 $j-a_j≠i-a_i (i<j)$

由于这题是SPJ，所以我们只要用构造的方法构造出一个序列即可。

我们只要排序后再翻转(我是懒得写比较函数)，这样 $i$ 越来越大，而 $a_i$ 越来越小，则 $j-a_j$ 必定大于 $i-a_i$，因为 $i<j$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define MAXN 100 + 10
using namespace std;
int t,n,a[MAXN],b[MAXN];
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
inline void write(int x) {//快输 
	char ch[20];int len=0;
	if(x<0){putchar(45);x=~x+1;}
	do{ch[len++]=x%10+48;x/=10;}while(x>0);
	for(int i=len-1;i>=0;i--) putchar(ch[i]);
	putchar(' ');
}
int main(void) {
	t=read();
	while(t--) {
		n=read();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++) a[i]=read();
		stable_sort(a+1,a+n+1);//排序 
		reverse(a+1,a+n+1);//翻转 
		for(int i=1;i<=n;i++) write(a[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：2)

### 题目翻译

给定一个无序数组$a$，将$a$数组重新排序使得对于任意$i,j(i\leqslant j)$，满足 $j-a_j\ne i-a_i$

### 思路分析

将$j-a_j \ne i-a_i$移项得

$j-i \ne a_j-a_i$

$\because i \leqslant j $

$\therefore j-i \geqslant0$

既然等式左边一定为非负数，所以我们只需要使得等式右边为负数即可

$\therefore a_j-a_i<0$

$\therefore a_j<a_i$

所以我们只需要将原先的$a$数组从大到小排序

### *Code:*

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[101];
bool cmp(int x,int y){
	return x>y;
}
bool f;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
			printf("%d ",a[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：2)

这题放到考场上还是很有意思的，主要考察选手对于题目条件的把握。


------------
先说结论：**将原数组倒序排列并输出**


------------
再说原因：对于一个倒序排列的数组$a$，那么对于任意一组$i<j$，$a_{i}>=a_{j}$。显然$j-a_{j}>i-a_{i}$，满足要求。


------------
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define fo(i,x,y) for(register int i=x;i<=y;++i)//宏定义简化for循环
using namespace std;

inline int read(){//快读
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

bool cmp(int x,int y){//从大到小排序
	return x>y;
}

const int maxn=105;
inline void work(){//对于每组数据
	int n=read(),a[maxn];
	fo(i,1,n) a[i]=read();//读入数组
	sort(a+1,a+1+n,cmp);//倒序排列
	fo(i,1,n) printf("%d ",a[i]);//输出
	printf("\n");
}

int main(){
	int t=read();
	while(t--){//t组数据
		work();
	}
	return 0;
}
```


---

## 作者：Andrewzdm (赞：1)

# [CF1312B Bogosort](https://www.luogu.com.cn/problem/CF1312B)
这道题和[CF1305A Kuroni and the gifts](https://www.luogu.com.cn/problem/CF1305A)有相似之处。

为了让任何一组 $i,j(i<j)$ 满足 $i-a_i \neq j-a_j$ （这里利用不等式的对称性把原题目中的条件稍作调整），我们只要倒着排序就可以了。

这样的话 $i$ 递增， $a_i$ 递减，一定能满足题目条件。

代码如下：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[105];
bool cmp(int x, int y)
{
	return x > y;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1; i <= n; i++)
			cout << a[i] << ' ';
		cout << endl; 
	}
	return 0;
}
```
完事！

---

## 作者：GoldenFishX (赞：1)

### 题目大意：

给你一个数组，你能否改变里面的数字的位置让任意一个 $i-a_i≠j-a_j$ 。


------------


### 思路

可以发现，只要从大到小排个序就OK了。



------------

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
bool cnt(int a,int b)
{
	return a>b;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
		}
		sort(a,a+n,cnt);
		for(int i=0;i<n;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：lgnotus (赞：1)

爆搜选手的福利。。

考虑$dfs$,注释在代码里。。

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,a[101];
bool flag=0;

bool check(){//判断是否达到目标状态
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i-a[i]==j-a[j])return 0;
        }
    }
    return 1;
}

void print(){
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    cout<<'\n';
}

void dfs(int cur){
    if(check()){
        print();//输出
        flag=1;
        return;
    }
    for(int i=1;i<=n;i++){//枚举将要交换的两个下标
        for(int j=i+1;j<=n;j++){
            if(i-a[i]==j-a[j]){
                swap(a[i],a[j]);//交换
                dfs(cur+1);
                swap(a[i],a[j]);//回溯
                if(flag)return;
            }
        }
    }
}

int main(){
    cin>>t;
    while(t--){
        flag=0;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        dfs(1);
    }
    return 0;
}
```

---

## 作者：AmamiyaYuuko (赞：0)

题目大意：重新排列序列使得 $\forall i < j, i - a_i \neq j - a_j$。

因为 $i < j$，所以当 $a_i \geq a_j$ 时就可以确保条件 $i - a_i \neq j - a_j$ 一定成立。

所以对于每个序列，将其降序排序后输出即可。

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

template <class T>
inline void read(T &x)
{
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return;
}

int a[110];
int t, n;

int main()
{
    read(t);
    while (t--)
    {
        read(n);
        for (int i = 1; i <= n; ++i)    read(a[i]);
        std::sort(a + 1, a + n + 1);
        for (int i = n; i >= 1; --i)    printf("%d ", a[i]);
        puts("");
    }
    return 0;
}
```

---

