# Yaroslav and Permutations

## 题目描述

Yaroslav has an array that consists of $ n $ integers. In one second Yaroslav can swap two neighboring array elements. Now Yaroslav is wondering if he can obtain an array where any two neighboring elements would be distinct in a finite time.

Help Yaroslav.

## 说明/提示

In the first sample the initial array fits well.

In the second sample Yaroslav can get array: $ 1 $ , $ 2 $ , $ 1 $ . He can swap the last and the second last elements to obtain it.

In the third sample Yarosav can't get the array he needs.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
7 7 7 7
```

### 输出

```
NO
```

# 题解

## 作者：蓝__ (赞：1)

发一个Python 3题解

------------

这道题可以用**桶排序**来做，具体看注释

```cpp
n=int(input())
list1=[]
t=[0]*10000 #建桶
flag=1 #判断标识
str1=input() #读入
list2=str1.split(" ")
list2_length=len(list2)
i=0
while i<=list2_length-1:
    list1.append(int(list2.pop()))
    i+=1
list1.reverse()
for j in range(0,n): #桶排序
    x=list1[j]
    t[x]+=1
    if t[x]>(n+1)/2: #判断有没有超过
        flag=0
if flag==1: #输出
    print("YES")
else:
    print("NO")
```

泪目，~~Python 3读入太麻烦了~~

---

## 作者：wangkangyou (赞：0)

### 简述一下思路：
找到数列中的最多的数，判断是否有 $\dfrac{n + 1}{2}$ 个即可。

有人会问，为什么呢？

其实我们发现，要想让每两个相邻的数不等，最优情况其实就是：

$$X,a_1,X,a_2,X,a_3,X,a_4……$$

其中 $X$ 表示数量最多的数。

而结尾一定是 $……a_k, X$ 或 $……X,a_k$。

当序列以 $X$ 开头且以 $X$ 结尾时，该序列能包含的 $X$ 的数量显然一定是最多的，数量为 $\dfrac{n + 1}{2}$ 个。那么我们连 $\dfrac{n + 1}{2}$ 个都能做到，那么更少的 $\dfrac{n + 1}{2} - 1, \dfrac{n + 1}{2}-2,……$ 显然也能够满足条件。

这里用了一个桶来统计数量最多的数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define File(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
using namespace std;
int read(){
	int sum = 0, f = 1;
	char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -f;
	for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * f;
}
void write(int x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
	return;
}
const int N = 1e6 + 10;
int a[N], v[N];
signed main(){
	int n = read();
	for(int i = 1; i <= n; ++ i){
		a[i] = read();
		v[a[i]] ++;
	}
	int maxn = 0; 
	for(int i = 1; i <= 10001; ++ i){
		maxn = max(maxn, v[i]); 
	}
	puts(maxn <= (n + 1) / 2 ? "YES":"NO");
	return 0;
}

```

---

## 作者：ruruo (赞：0)

# CF296A题解

这道题只要统计出出现次数最多的数字，数量是否超过 $(n + 1) / 2$ 即可，因为如果不超过 $(n + 1) / 2$，就可以通过操作把数组变成 $max,a,max,b,…,max,x,max,y,max,z(,max)$。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt[1005], n; // cnt 数组作为桶

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    sort(cnt + 1, cnt + 1001); // 对 cnt 数组进行排序，取最大值
    if(cnt[1000] <= (n + 1) / 2) cout << "YES";
    else cout << "NO";
    return 0;
}
```


---

## 作者：TheCliffSwallow (赞：0)


### 思路
当 $n$ 为偶数时，相同数字最大出现次数为 $n/2$ 次，可表示为：$k_1,a,k_2,a,k_3... ,a$。

当 $n$ 为奇数时，相同数字最大出现次数为 $(n+1)/2$ 次，可表示为：$a,k_1,a,k_2,a,k3,...,a$。

所以当最多的相同数字出现次数小于等于 $(n+1)/2$ 时，可以使数组中没有数字相同的相邻元素。（当 $n$ 为偶数时 $n/2=(n+1)/2$ ）

因为数据中 $a_i \leq 1000$，数据较小，可以用桶记录每个数字出现次数，把出现次数最多的与 $(n+1)/2$ 进行比较即可。

### AC CODE
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#define int long long
using namespace std;
int n,a[105],buskets[1005],maxn;//buskets数组为桶，maxn记录最大值
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=i;i<=n;i++){
		cin>>a[i];
		buskets[a[i]]++;
		if(buskets[a[i]]>maxn){//寻找最高次数
			maxn=buskets[a[i]];
		}
	}
	if(maxn>(n+1)/2)	cout<<"NO";//相同数字出现次数比(n+1)/2大输出NO
	else	cout<<"YES";//相同数字出现次数比(n+1)/2小输出YES
	return 0;
}
```


---

## 作者：Colead (赞：0)

本题应该十分简单了。本来以为会有交换次数的限制条件。（那样请读者自己思考），但是没有。换而言之，你想怎么换怎么换。

根据冒泡排序的原理，经过“有限次”交换，其实就相当于你对数组中任意两个数进行调换。

也就是说，你可以重排数组顺序。

那么如果出现最多的数字多到不可能让他们不相邻，也就是其数量 $p_i \geq (n+1)/2$ ，那么就是不符合条件的。

反之则一定可以找到一组解。

```
#include<bits/stdc++.h>
using namespace std;
long long n,p;
long long a[1005]={};
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p;
		a[p]++;
	}
	long long maxn=*max_element(a+1,a+1004);
	if(maxn<=(n+1)/2)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```
注意求最大值的时候不要写成：

```
long long maxn=*max_element(a+1,a+n+1);
```

我就被坑了一下。

祝大家 AC 快乐！元旦快乐！

---

## 作者：ztxtjz (赞：0)

## 【题意】
有$n$个数，求能否通过调整顺序使相邻两数不相等。能输出$\text{YES}$，不能输出$\text{NO}$。
## 【思路】
将相同的数间隔一个放一个，其他的数插空放置。

举个例子，$n=5$，分别为$5,5,5,7,2$，可调整为$5,2,5,7,5$。

由此可见，$n$个数中相等的数的个数$≤(n+1)/2$时，都能达成要求。
## 【代码】
```cpp
#include <cstdio>
int n,maxn,a[1001];
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),a[x]++,maxn=maxn<a[x]?a[x]:maxn;  //maxn记录一个数出现的最大次数
	if(maxn<=(n+1)/2) printf("YES");
	else printf("NO");
	return 0;
}
```

---

## 作者：tryrtj (赞：0)

此题又是一道我的一条龙服务：翻译加第一次AC+题解；

进入正题，题目很简单的，就是让相邻的元素没有相等的，那么两个相等的数字之间必然至少有一个其他的数，那么我们将数组分成两部分0，2，4，6，8...与1，3，5，7，9；那么很容易发现，只要所有的同一种数字可以被安排在同一组，那么就是可行的，所以同一种数字的个数应当小于等于(n+1)/2，此处+1是因为除法舍弃尾数，详见样例#1&2；

完整代码：

```
#include<iostream>
using namespace std;
int a[105],b[105],c[105];//a存读入，b存数字种类，c存同一种数字出现次数
int u1=0;//指针
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		bool g=false;//判断是否有过的标志
		for(int j=0;j<u1;j++){
			if(b[j]==a[i]){
				g=true;//标记
				c[j]++;//计数++
				break;
			}
		}
		if(g==false){
			b[u1]=a[i];//存入新数
			c[u1]++;//别忘了初始为1
			u1++;//指针++
		}
	}
	for(int i=0;i<n;i++){
		if(c[i]>((n+1)/2)){//判断是否存的下
			cout<<"NO"<<endl;//输出结果
			return 0;
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

思路
---
这道题只需要统计出现最多的数的数量，判断是否小于 $(n+1)/2$ 。\
简单证明一下: 设最大数为 $k$ ，$k$ 最大化利用的情况就是：  $k,a,k,b,k,...,k,z,k$ ，即 $k$ 出现 $(n+1)/2$ 次。只要出现最多的数的数量在 $(n+1)/2$ 及以内，就可以构造成功。

代码
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105],mx=-1;//mx存储最大值，数组大小必须大于数据范围
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		a[k]++;//存储每个元素数量
		if(sum<a[k])//如果小于当前数量
		{
		    sum=a[x];//把目前最大数量和当前数量比较
		}
	}
	if(sum<=(n+1)/2) //已证明
	{
	    cout<<"YES";
	}
	else 
	{
	    cout<<"NO";
	}
	
	return 0;
}
```


---

