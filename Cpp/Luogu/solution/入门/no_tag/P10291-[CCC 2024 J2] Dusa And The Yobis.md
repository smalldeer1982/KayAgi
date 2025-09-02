# [CCC 2024 J2] Dusa And The Yobis

## 题目描述

Dusa 吃 Yobi，但是只吃大小在某个范围里的 Yobi。

如果 Dusa 遇到了一个大小比它小的 Yobi，它会吃掉这个 Yobi 并把它的大小吞并。（即令自己的大小加上这个 Yobi 的大小。）

例如，如果 Dusa 的大小是 $10$，并且遇到了一个大小是 $6$ 的 Yobi，Dusa 会吃掉这个 Yobi 并且大小变大为 $10 + 6 = 16$。

如果 Dusa 遇到了一个和它一样大或者甚至比它更大的 Yobi，Dusa 会选择逃跑并且不吃掉 Yobi。

Dusa 现在遇到了一列 Yobi 并且按照顺序遇到它们。保证 Dusa 必定会遇到一个 Yobi 导致它逃跑。你需要确定 Dusa 逃跑时的大小。

![](https://cdn.luogu.com.cn/upload/image_hosting/oq4z4sne.png)

## 说明/提示

**【样例 1 解释】**

Dusa 可以吃掉大小为 $3$ 的 Yobi 并使得 Dusa 的大小变为 $8$。Dusa 可以吃掉大小为 $2$ 的 Yobi 并使得 Dusa 的大小变为 $10$。Dusa 可以吃掉大小为 $9$ 的 Yobi 并使得 Dusa 的大小变为 $19$。大小为 $20$ 的 Yobi 导致了 Dusa 逃跑。

**【样例 2 解释】**

大小为 $10$ 的 Yobi 导致了 Dusa 逃跑，它的大小没有改变。

**【数据范围】**

对于所有数据，保证输入的所有数不超过 $5 \times 10^5$，输入的总行数不超过 $2 \times 10^5$。

## 样例 #1

### 输入

```
5
3
2
9
20
22
14```

### 输出

```
19```

## 样例 #2

### 输入

```
10
10
3
5
13```

### 输出

```
10```

# 题解

## 作者：xyx404 (赞：7)

## 思路：
先输入，然后模拟，当 Yobi 的大小大于等于 Dusa 时输出 Dusa 现在的大小，并结束。

因为题目没有告诉我们有几个 Yobi 所以这样输入：
```cpp
while(cin>>a[cnt++]);
```


##  代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define CPPname using namespace std
CPPname;
LL Dusa;
int cnt=1,a[200010];
int main(){
	int d;cin>>d;
	Dusa=d;
	while(cin>>a[cnt++]);
	for(int i=1;i<cnt;i++){
		if(Dusa>a[i])Dusa+=a[i];
		else{
			cout<<Dusa;
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：_little_Cabbage_ (赞：3)

# P10291 [CCC 2024 J2] Dusa And The Yobis 题解
水题。

模拟，每一次如果 $d>x$，$d$ 就加上 $x$，否则直接输出 $d$，并结束程序。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
	int d;
	cin>>d;
	int x;
	while(cin>>x)
	{
		if(d<=x)
		{
			cout<<d;
			return 0;
		}
		else
		{
			d+=x;
		}
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：3)

### 思路
这道题十分简单,我们可以边读入边处理。读入一个 Yobi 的大小：
- 如果这个 Yobi 比当前的 Dusa 小并且之前没有遇到过和 Dusa 一样大的或者更大的 Yobi，那么 Dusa 的大小加上 Yobi 的大小。
- 如果这个 Yobi 比当前的 Dusa 小并且之前遇到过和 Dusa 一样大的或者更大的 Yobi，那么跳过。
- 如果这个 Yobi 和当前的 Dusa 一样大或者更大，则标记已经遇到过和 Dusa 一样大的或者更大的 Yobi。

最后输出 Dusa 的大小。
### 代码
```cpp
#include<iostream>
int main(){
    int d;std::cin>>d;
    int x;
    bool f=0;
    while(std::cin>>x){
        if(x<d&&!f)d+=x;
        if(x<d&&f)continue;
        if(x>=d)f=1;
    }  
    std::cout<<d;
}
```

---

## 作者：PengDave (赞：1)

模拟即可。设 $d$ 表示 Dusa 的大小，不断读入 Yobi 的大小，若 Yobi 的大小小于 $d$，将 $d$ 加上 Yobi 的大小，否则跳出循环。最后输出 $d$。
```cpp
#include<iostream>
using namespace std;
int main(){
    //cin读入优化
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    long long d;
    cin>>d;
    long long tmp;//Yobi的大小
    while(cin>>tmp){//不断读入入直到没有Yobi
        if(d>tmp){
            d+=tmp;
        }else{
            break;
        }
    }
    cout<<d<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10291)

## 思路

水。

先输入 $D$，再用 `while` 循环反复输入 $n$，如果 $D>n$ 就让 $D$ 加上 $n$，否则直接输出 $D$ 结束程序。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int x;
    while (cin >> x) {
        if (n > x) n += x;
        else {
            cout << n << endl;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：cmask4869 (赞：0)

## 思路
本题可以确定一个变量 $a1$ 作为 Dusa 的大小，每次和 Yobi 的大小作对比。如果大于他的大小，那么加上他的大小继续对比。否则输出当前 Dusa 的大小。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
int a2 ;
int main(){
	int a1 ;
	cin >> a1 ;
	while(~scanf("%d",&a2)){ //读入的方法
		if (a1>a2) a1+=a2 ; //如果大于的话，就把他并入
		else{
			cout << a1 ; //如果小于，直接输出
			return 0 ;
		}
	}
	return 0 ;
}
```

---

## 作者：lpx666666 (赞：0)

~~又是一道水题~~
## 题目描述
一个怪物的大小为 $D$ 的前面有很多大小为 $a_i$ 怪物，如果前面的怪物比他大，那他就会逃跑，如果比他小就会吞噬，它会变成大小为 $D + a_i$ 的怪物，输出第一次逃跑的大小。
## 思路
直接暴力他前面的所有怪物，如果比他小就吞噬，比他大就逃跑。
### 注意
有无数次输入。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int d,p=0;
int main(){
	cin>>d;
	int a;
	while(cin>>a){
		if(p!=0){//记录后后面无须做任何运算 
			continue;
		}
		if(a>=d){//跑 
			p=d;
		}
		else{//吞 
			d+=a;
		}
	}
	cout<<p;//华丽收尾 
	return 0;
}

```

---

## 作者：Eason_cyx (赞：0)

当 Dusa 逃跑后，剩余的所有 Yobi 它都无法得到。

因为 $x$ 的个数无法确定，所以使用 `while` 循环读入。

读入后，如果可以吃掉，就吃；否则直接 `break`。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int d; cin >> d;
    int x;
    while(cin >> x) {
        if(x >= d) break;
        else d += x;
    }
    cout << d << endl;
    return 0;
}
```

---

## 作者：wrongaaa (赞：0)

## 思路
输入了 $n$ 之后，随后一直输入 $w$，并且判断 $n$ 和 $w$，大于就吞了下一个，小于等于就溜。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[200005];

int main() {
	cin >> n;
	int w;
	while (cin >> w) {
		if (n > w)
			n += w;
		else {
			cout << n << endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

## 思路

首先输入 Dusa 的身高，然后使用 `while` 循环输入 Yobi 的身高，如果 Dusa 身高 $\leq$ Yobi 的身高，那么跳出循环结束程序，否则 Dusa 与 Yobi 身高相加，进入下一次循环。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll d;
ll x;
int main(){
	cin >>d;
	while(cin >>x){
		if(x>=d)break;
		d+=x;
	}
	cout <<d;
	return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：0)

也没什么好解释的，只要读清了题都能做。

本题要注意的两个点：

1. 注意开 ``long long``。

2. 本题的输入没有给出 Yobi 的个数，所以我们要不断读入直到读入 ``EOF`` 为止。

在这里给出输入代码：

```cpp
	while(cin >> a[++n]);
    n--;
```

# 完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 9;
int D;
int a[N],n;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> D;
	while(cin >> a[++n]);
    n--;
	for(int i = 1;i <= n;i++){
		if(D > a[i])
			D += a[i];
		else
			break;
	}
	cout << D;
}
```

---

## 作者：LG086 (赞：0)

### 分析

第一行输入一个数 $D$，接下来再输入若干个数 $x$。  
如果某行的 $x$ 大于等于此时的 $D$，输出 $D$。  
如果该行的 $x$ 小于此时的 $D$，则 $D\to D+x$。

------------
### 代码

```cpp
#include<iostream>
#define int long long
#define LG086 signed
LG086 main(){
    int a,b;std::cin>>a;
    while(std::cin>>b)
        if(b<a)a+=b;
        else return std::cout<<a,0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10291)
## 解题思路
模拟。

先输入 Dusa 的大小 $n$，再一直输入 Yobi 的大小 $x$，然后分类讨论：
- 如果 $n>x$，Dusa 吃掉 Yobi，$n \gets n+x$；
- 如果 $n \le x$，Dusa 逃跑，输出 $n$。

那我就~~心血来潮~~写了个 `main()` 递归：

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n=-1,x;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(n==-1)cin>>n;//没输入过，输入 n
	cin>>x;
	if(n<=x)
	{
		cout<<n;
		exit(0);
	}
	else
	{
		n+=x;
		main();
	}
	return 0;
}

```

---

## 作者：_Jocularly_ (赞：0)

按照题意模拟即可，循环输入，如果小于它就加上并继续，如果大于等于它就退出循环输出答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin >> n;
	int t;
	while(cin >> t){
		if(n > t) n += t;
		else break;
	}
	cout << n;
	return 0;
}

```

---

## 作者：2021zjhs005 (赞：0)

入门模拟。

每次读入 Yobi 的大小 $x$ 有如下两种情况：

- $D > x$，则 $D\gets D+x$。

- $D\leq x$，直接输出 $D$ 并结束程序。

最后，如果输入完毕还没有结束程序，输出 $D$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int D,x;

signed main(){
  D=read();
  while(sc("%lld",&x)!=EOF){
    if(D>x) D+=x;
    else{
      pr("%lld\n",D);
      exit(0);
    }
  }
  pr("%lld\n",D);//所有 Yobi 都打不过 Dusa，最后输出 D。
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10291)

## 题意

输入一个数 $D$，接着输入若干个数 $R$，如果 $D$ 大于 $R$，就加 $R$，否则输出。

## 思路

不停输入 $a$，如果小于 $n$ 就吞并，否则输出 $n$，结束。

## [AC代码](https://www.luogu.com.cn/record/153149571)

```
#include<bits/stdc++.h>
using namespace std;
int n,a;
int main(){
	cin>>n;
    while(1){
    	cin>>a;
    	if(a<n)n+=a;
    	else break;
	}
	cout<<n;
}
```

~~话说为啥对了只有那么点分~~

---

## 作者：xd244 (赞：0)

又是水题一道。

用 $d$ 记录 Dusa 目前的大小，用 $a$ 表示当前这个 Yobi 的大小，那么当 $d>a$ 时 $d$ 增加 $a$，不满足就输出 $d$ 并结束程序。

代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    int d,a;cin>>d;
    while(cin>>a){
        if(d>a)d+=a;
        else{
            cout<<d;return 0;
        }
    }
}
```

---

