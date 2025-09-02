# Dividing the numbers

## 题目描述

Petya has $ n $ integers: $ 1,2,3,...,n $ . He wants to split these integers in two non-empty groups in such a way that the absolute difference of sums of integers in each group is as small as possible.

Help Petya to split the integers. Each of $ n $ integers should be exactly in one group.

## 说明/提示

In the first example you have to put integers $ 1 $ and $ 4 $ in the first group, and $ 2 $ and $ 3 $ in the second. This way the sum in each group is $ 5 $ , and the absolute difference is $ 0 $ .

In the second example there are only two integers, and since both groups should be non-empty, you have to put one integer in the first group and one in the second. This way the absolute difference of sums of integers in each group is $ 1 $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
0
2 1 4 
```

## 样例 #2

### 输入

```
2
```

### 输出

```
1
1 1 
```

# 题解

## 作者：Light_az (赞：2)

## 暴力

首先在看到这道题后，我们要知道对于一个长度为 $4$ 的序列，它的差值是 $0$，为什么？对于这个序列来说，一共有 $4$ 个数： $x$，$(x-1)$，$(x-2)$，$(x-3)$。根据观察我们发现：第 $1$ 个数与第 $4$ 个数的和等于第 $2$ 个数与第 $3$ 个数的和，也就是说，只要输入的 $n$ 大于 $4$ 时，我们便可以取模于 $4$，输出可以为第一个数和第四个数，也可以是第二个数和第三个数，同时我们需要一个计数板去统计出现次数。那么如果取模后还剩下一些数怎么办？

- 当剩下的数是 $1$，次数加一，输出 $1$，因为前面的数差值为 $0$，此时 $1$ 在哪里都不受影响。

- 当剩下的数是 $2$，次数加一，输出 $2$，因为将 $1$ 和 $2$ 分别放入一个序列中，差值会改变为 $2$ 减 $1$ 即为 $1$。

- 当剩下的数是 $3$，次数加二或一，输出 $1$ 和 $2$ 或 $3$，因为将 $1$ 和 $2$ 放入一个序列中，再将 $3$ 放入一个序列中,差值便不会改变。

因此，我们有了一下代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,cnt=0,t=0,k,x,y;
const int N=1e5+10;
int a[N];
char b[N]={' ','1','1','3'};//n取模后的特判 
string s;
void print(int n){//余数规律 
	if(n%4==0||n%4==3){
		cout<<0<<endl;
	}
	else{
		cout<<1<<endl;
	}
}
int main(){
	cin>>n;
	print(n);//输出余数 
	while(n>=4){//对n取模并记录数字 
		cnt+=2;
		a[++t]=n;//第一个数 
		a[++t]=n-3;//第二个数 
		n-=4;
	}
	if(n){//取模剩下的数的特判 
		cnt++;
		a[++t]=b[n]-'0';
	}
	cout<<cnt<<" ";//输出总数 
	for(int i=1;i<=t;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```


---

## 作者：yzy041616 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF899C)

## Part.1 题目

将 ${1,2, \dots n}$ 的集合任意划分为两个子集，每个子集都有一个和，使这两个和之差的绝对值最小。第一行输出这个最小的差，第二行先输出**其中任意一个子集**的元素个数，然后再输出这个子集里的所有元素，可以不考虑顺序。

例：若 $n=7$ 则可以分成 $\{3,4,7\}$ 和 $\{1,2,5,6\}$，$\{3,4,7\}$ 的和是 $14$，$\{1,2,5,6\}$ 的和也是 $14$。这两个和之差的绝对值为 $0$，是最小了。所以第一行输出这个差，$0$，第二行选一个子集，假设选到了 $\{3,4,7\}$，就要先输出它的元素个数，$3$，然后再输出 $3$ $4$ $7$。可以不考虑顺序，所以 $3$ $7$ $4$，$4$ $3$ $7$，$4$ $7$ $3$，$7$ $3$ $4$，$7$ $4$ $3$ 都会算你对的。

## Part.2 思路

这是一道数学题。如果 $n$ 比较大的话，就先拿最大的四个数，这四个数是 $n,n-1,n-2,n-3$，因为 $n+(n-3)=(n-1)+(n-2)$，所以这四个数可以当作没有，两个子集元素个数也一样，$n$ 个数的状态转化成 $n-4$ 个数。

到最后，$n$ 变成 $n\%4$，只剩下 $4$ 种状态：

$1.$ $n=0$，这时候就没有数，差为 $0$。  
$2.$ $n=1$，有一个数是 $1$，只能分在一组里，所以差为 $1$。  
$3.$ $n=2$，两个数分别是 $1,2$，可以分在两组里，但是差最小还是 $1$。  
$4.$ $n=3$，三个数， $1,2,3$，第一组分 $3$，第二组分 $1,2$，差为 $0$。

第一行的输出搞定了。

对于第二行的子集元素个数，在一开始把 $n$ 变成 $n\%4$ 的时候，两个子集元素个数一直是相等的，到最后分类讨论的时候，元素个数相差也不超过 $1$，所以总是有一个子集元素个数为 $n/2$，最后输出元素的时候也要输出那个个数少的。

对于构造子集，因为一开始删数的时候总是 $n$ 和 $n-3$ 分在一组，所以每次都要输出 $n$ 和 $n-3$。

到了最后分类讨论，要记住输出元素少的那一组。$n=0$ 时没有元素。$n=1$ 时也没有元素。$n=2$ 时有一个元素是 $1$。$n=3$ 时有一个元素是 $3$。

## Part.3 代码

```cpp
#include<iostream>
using namespace std;
int diff[4]={0,1,1,0};
string start[4]={" "," "," 1 "," 3 "};
int main(){
	int n;cin>>n;
	cout<<diff[n%4]<<endl;
	cout<<n/2<<start[n%4];
	for(;n>3;n-=4)cout<<n<<" "<<n-3<<" ";//改成n-1和n-2也行
}
```

---

## 作者：__Hacheylight__ (赞：0)

题意：将1到n的排列任意划分为两个集合，使他们的绝对值差最小，输出绝对值差和方案。

总和是n*(n+1)/2,如果答案/2=0的话就是0，不然的就是1.之后就输出集合就行了。

生成集合的应该是简单的，分组时将1留下，两个数一组，并且大小交替拿出来放在一组。

Code:
```cpp
#include<bits/stdc++.h>  
using namespace std;  
int main()  
{  
    int n,sum,cnt,j;  
    cin>>n ; 
        cnt=0;sum=n*(n+1)/2;  
        if(sum%2==0) puts("0");  
        else puts("1");  
        cout<<n/2<<" ";  
        for(int i=n;i>1;i-=2)  
        {  
            if((++cnt)%2) j=0;  
            else j=1;  
            cout<<i-j<<" ";  
        }  
        puts("\n");  
    return 0;  
}
```

---

## 作者：HuZHUNZHUN (赞：0)

### 本蒟蒻的第三篇题解QAQ

本题思路：

设 $f(x)$ 表示 $n=x$ 时问题的答案。

1) 当 $x=0$ 时，显然最小绝对值为 $0$，因此 $f(x)=0$。

2) 当 $x=1$ 时，显然最小绝对值为 $1$，因此 $f(x)=1$。

3) 当 $x=2$ 时，显然最小绝对值为 $2-1=1$，因此 $f(x)=1$。

4) 当 $x-3$ 时，显然最小绝对值为 $3-(2+1)=0$，因此 $f(x)=0$。

5) 当 $x\ge4$ 时，注意到 $x+(x-3)=(x-1)+(x-2)$，这四项可以相互抵消，因此 $f(x)=f(x-4)$。

按照 $n$ 模 $4$ 的值分类讨论即可。

无注释代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	if(n%4==0)
	{
		cout<<"0\n"<<n/2<<" ";
		for(int i=0;i<n/4;i++) cout<<4*i+1<<" "<<4*i+4<<" ";
	}
	else if(n%4==1)
	{
		cout<<"1\n"<<n/2<<" ";
		for(int i=0;i<n/4;i++) cout<<4*i+2<<" "<<4*i+5<<" "; 
	}
	else if(n%4==2)
	{
		cout<<"1\n"<<n/2<<" 1 ";
		for(int i=0;i<n/4;i++) cout<<4*i+3<<" "<<4*i+6<<" ";
	}
	else
	{
		cout<<"0\n"<<n/2<<" 3 ";
		for(int i=0;i<n/4;i++) cout<<4*i+4<<" "<<4*i+7<<" ";
	}
	return 0;
}

```

---

