# [ARC058C] こだわり者いろはちゃん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc058/tasks/arc058_a

いろはちゃんはこだわりもので、嫌いな数字が $ K $ 個あり、それぞれ $ D_1,\ D_2,\ ...,\ D_K $ です。

いろはちゃんはお店でお買い物をしていて、 $ N $ 円の品物を買おうとしています。 もちろん、この品物は $ N $ 円以上のお金を支払えば買うことができます。 しかし、先ほど述べたようにいろはちゃんは強いこだわりがあるので、自分がお店に支払う金額の $ 10 $ 進表記にいろはちゃんの嫌いな数字が出現しないような最も少ない金額を支払おうとします。

いろはちゃんが支払う金額を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ <\ 10000 $
- $ 1\ ≦\ K\ <\ 10 $
- $ 0\ ≦\ D_1\ <\ D_2\ <\ …\ <\ D_K≦9 $
- $ \{D_1,D_2,...,D_K\}\ ≠\ \{1,2,3,4,5,6,7,8,9\} $

### Sample Explanation 1

嫌いでない数字は $ 0 $ と $ 2 $ のみです。 $ N=1000 $ 以上の整数で、桁に $ 0 $ と $ 2 $ のみが含まれる最小の整数は $ 2000 $ なのでそれを出力してください。

## 样例 #1

### 输入

```
1000 8
1 3 4 5 6 7 8 9```

### 输出

```
2000```

## 样例 #2

### 输入

```
9999 1
0```

### 输出

```
9999```

# 题解

## 作者：b6e0_ (赞：4)

这题枚举就可以通过。

用一个桶记录每一个数字是不是讨厌的，然后从$n$往后枚举，每一个枚举到的数做数位拆分，看有没有讨厌的数。如果每一位都没有的话就输出。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool d[15];//记录讨厌的数的桶
int main()
{
	int n,k,i,x;
	cin>>n>>k;
	for(i=0;i<k;i++)
	{
		cin>>x;
		d[x]=true;//打标记，放入桶中
	}
	while(1)
	{
		x=n;//这里要记录一下，不然后面就会更改n的值，影响后面的枚举
		while(x)//做数位分解
		{
			if(d[x%10])
				break;
			x/=10;
		}
		if(!x)
			break;//如果这儿x是0的话，说明一定每一位都不是讨厌的数，不然上面break时x就不会分解到0。
		n++;//继续往后枚举
	}
	cout<<n;//输出
	return 0;
}
```

---

## 作者：Cambridge (赞：1)


蒟蒻又来发题解了！

废话不多说我们来讲讲思路。思路其实很简单，暴力枚举就好了。所用的钱数从n开始，逐个枚举，直到所用钱数中没有包含讨厌的数字为止。至于如何判断所用钱数中有没有包含讨厌的数字，我们先看各位数字，如果可以，除以10，继续看，直到这个数小于等于0或者找到讨厌的数字为止为止。代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
int n,k,a[100010],f[1010];
int pd(int x)//判断数字中有没有讨厌的数字
{
	while(x>0)//逐位份解
	{
		if(f[x%10])return 1;
		x/=10;
	}
	return 0;
}
int main()
{
    cin>>n>>k;
    for(int i=1; i<=k; i++)
    {
    	cin>>a[i];
    	f[a[i]]=1;//记录
	}
	for(int i=n; ; i++)
	{
		if(!pd(i))//判断
		{
			cout<<i<<endl;//输出结果，记得换行
			return 0;
		}
	}
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：oimaster (赞：0)

本题直接枚举即可。每次枚举一个数时做数位拆分。如果发现这个数中有恶臭的数字时我们就枚举下一个。

分析一下能不能过。

首先，数位拆分一次最多 $6$ 次循环，几乎可以视为常数。

然后，我们发现不管如何枚举，最后的结果总是少于 $999999$。如果 $N$ 有 $d$ 位数字，答案一定会小于任何一个 $d+2$ 位数。

原因：我们一定会喜欢至少一个数，这个数字一定可以组成一个多位数满足我们的要求。例如，我们要花 $99999$ 日元，只喜欢数字 $3$，我们就会花 $333333$ 日元。这就是一个上限。

核心部分循环次数：$6\times 999999$（最多，实际不可能达到这么多），可以通过。

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	bool b[10]={0,0,0,0,0,0,0,0,0,0};
	for(int i=1;i<=m;++i){
		int tmp;
		cin>>tmp;
		b[tmp]=true;
	}
	int i=n;
	while(true){
		int p=i;
		bool flag=false;
		while(p){
			if(b[p%10]==true){
				flag=true;
				break;
			}
			p/=10;
		}
		if(flag==false){
			cout<<i<<endl;
			return 0;
		}
		++i;
	}
}
```

---

## 作者：MilkyCoffee (赞：0)

这道题可以直接向下无限枚举，由 $N < 10000$ 且 ${D_1, D_2, ..., D_K}\ != {1, 2, 3, 4, 5, 6, 7, 8, 9}$ ，可以推出在一定的范围内一定有解。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, tmp;
bool t[15];

bool chk(int x) { // check
	while (x) {
    	int CoL = x % 10;
    	if (t[CoL]) return false;
    	x /= 10;
    }
    return 1;
}

int main() {
	scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
    	scanf("%d", &tmp);
        t[tmp] = 1;
    }
    
    while (n) {
    	if (f(i)) {printf("%d\n", i); break;}
        n++;
    }
	return 0;
}

```

由于未知原因，此题博主提交时无端CE（尚未返回编译信息）

---

## 作者：Brian_WBY (赞：0)

题解区都是 `cpp` 的大佬啊，我来发一篇 `py` 的。

这道题的数据范围不大，可以采用暴力枚举的方法过，方法如下。

使用一个 `w` 数组记录买家是否讨厌某个数（$w_x$为 `True` 表示买家讨厌 $x$）。

然后从 $n$ 开始枚举所花的钱数，并对其进行检验，如果某个数里没有买家讨厌的数，那么这个数就是答案，否则，将这个数 $+1$，继续检验。

检验方法：拆分某数的数位（先判断最低位，如果讨厌最低位，则说明这个数不行，如果最低为不被讨厌，将这个数除以 $10$（向下取整），继续判断新数）即可。

代码如下：

```python
n, k = map(int, input().split())
d = list(map(int, input().split()))//以上为输入过程
w = [False] * 10//先把 w 数组开出来，再标记
for i in d:
	w[i] = True//扫描买家讨厌的数的列表，并将其标记为 True
def check(n)://检验
	while n:
		if w[n % 10]://首先检验最低位
			return False//如果讨厌，这个数不行
		n //= 10//最低为可以，将这个数除以 10（向下取整）（相当于舍弃最低位），继续判断
	return True//所有位数都不被讨厌，说明这个数可以
ans = n//从 n 开始枚举
while not check(ans)://一个数检验不成功就检验下一个
	ans += 1
print(ans)//输出答案
```


---

## 作者：chufuzhe (赞：0)

这道题可以用桶来记录这个数是不是讨厌的数字，然后从n开始往后枚举，如果这个数中没有讨厌的数字，就输出并结束枚举。
```cpp
#include<bits/stdc++.h> //头文件
using namespace std; //定义数组桶
bool f(int n) //判断是否没有讨厌的数字
{
	while(n>0) //枚举每一位
	{
		if(a[n%10]) return 0; //有讨厌的数字
		n/=10; //枚举下一位
	}
	return 1; //没有讨厌的数字
}
int main()
{
	ios::sync_with_stdio(false); //输入输出优化流
	int n,k,d; //定义
	cin>>n>>k; //输入
	for(register int i=1;i<=k;i++)
	{
		cin>>d;
		a[d]=1; //标记
	}
	for(register int i=n;;i++) //从n开始往后枚举
	{
		if(f(i)) //判断有没有讨厌的数字
		{
			cout<<i<<endl; //输出
			break; //结束枚举
		}
	}
	return 0; //结束
}

```


---

## 作者：judgejudge (赞：0)

# 利用数组
**我们先把现金k的每一位用数组来表示，然后在数组当中加减，予以判断。**

此处需要注意：数组还牵扯到进位的问题，因此需要注意。

下面奉上AC代码并予以讲解：
```cpp
#include <iostream>
using namespace std;
int a[1000],b[1000],leng=0;
int f(){
	int i,j;
	for(i=1;i<=leng;i++)
	if(b[a[i]]>0)return 1;//判断是否是厌恶的数字
	return 0;
}
int main(){
	int i,j,l;
	long long k,n,m;
	cin>>k>>n;
	for(i=1;i<=n;i++)cin>>l,b[l]++;//此处用桶来记录，方便判断是否是厌恶的数字
	m=k;
	while(m>0){
		a[++leng]=m%10;
		m/=10;
	}//此处我们把k的每一位储存到数组当中去
	while(f()){
		int s1=f();//注意：一定要从第一位开始，因为之后会有变动，此处写s1=f()可以替换成s1=1
		a[s1]++;//那一位上的数字++
		k++;
		while(a[s1]>=10)a[s1]=0,s1++,a[s1]++;//注意：此处如果发现需要进位，那么就根据加法的原理
		leng=max(leng,s1);//注意！最高位如果有进位的情况，leng也要随之++，此处刚好利用s1一定是最高位的巧合
	}
	cout<<k<<endl;
	return 0;
}
```


---

