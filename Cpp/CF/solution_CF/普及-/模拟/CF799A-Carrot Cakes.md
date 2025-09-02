# Carrot Cakes

## 题目描述

一共需要烤 $n$ 个蛋糕，用一个烤箱烤 $k$ 个蛋糕需要 $t$ 分钟。现有一个烤箱，可以再用 $d$ 分钟建一个。建烤箱时正在建的烤箱不能工作，但另一个烤箱可以。问：新建烤箱烤完 $n$ 个蛋糕的时间是否比不新建要严格快（即不能等于）？

## 样例 #1

### 输入

```
8 6 4 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8 6 4 6
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
10 3 11 4
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4 2 1 4
```

### 输出

```
YES
```

# 题解

## 作者：_byta (赞：4)

很显然，我们可以比较加了 x 个烤箱之后的平均烧烤速度与不加烤箱的平均烧烤速度。对于加了烤箱之后，平均速度即为 $(n-1)/k*t$,与 d 比较一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
   int n,t,k,d;
   cin>>n>>t>>k>>d;
   cout<<((n-1)/k*t>d?"YES":"NO");
}
```




---

## 作者：⊱⋛赫宇⋚⊰ (赞：3)


简单的一道公式题目，讲解在注释里面
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n,t,k,d;
    cin >> n >> t >> k >> d;
    //计算不用建烤箱所要的时间
    int T1 =  t*( (n/k) + (n%k!=0));
    //计算需要烤箱所要的时间，在此过程中要注意，在建造的过程中也可以用烤箱
    int T2 =  d + t*(( n-(d/t)*k )/(2*k) +(( n-(d/t)*k )%(2*k)!=0));
    if(T2 < T1)puts("YES");
    else puts("NO");
    return 0;
}
```


---

## 作者：Anonymous__user (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF799A)。

**题目大意**：  一共需要烤 $n$ 个蛋糕，用一个烤箱烤 $k$ 个蛋糕需要 $t$ 分钟。现有一个烤箱，可以再用 $d$ 分钟建一个。建烤箱时正在建的烤箱不能工作，但另一个烤箱可以。问：新建烤箱烤完 $n$ 个蛋糕的时间是否比不新建要严格快（即不能等于）？

**输入格式**：
一行，四个数，分别是 $n$ , $t$ , $k$ , $d$。

**思路**：比较加烤箱后的平均速度与不加烤箱的平均速度，即比较 $\frac{(n-1)t}{k}$ 与  $d$ 的大小。

**代码**：

```c
#include<bits/stdc++.h>
using namespace std;
long long n,t,k,d;
double v;
int main(){
	cin>>n>>t>>k>>d;
	v=(n-1)*t/k;
	if(v>d)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```


---

## 作者：cst_123 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF799A)


------------

### 思路

只要比较加若干个烤箱后的平均速度与不加的平均速度进行比较，就可以了。

平均速度是 $\frac{(n-1)t}{k}$ ，当平均速度若大于做的时间，那就是YES，反之亦然。

### 核心代码
```cpp
if((n-1)/k*t>d)
		printf("YES\n");
else printf("NO\n");
```

---

## 作者：sandwave114514 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF799A)

题目大意

烤蛋糕 $n$ 个，用一个烤箱烤 $k$ 个蛋糕需要 $t$ 分钟。现有一个烤箱，可以再用 $d$ 分钟建一个。建烤箱时正在建的烤箱不能工作，但另一个烤箱可以，新建烤箱烤完 $n$ 个蛋糕的时间那个快.

解题思路

我们可以算出加烤箱后的平均速度，他的平均速度是 $\left (n-1  \right )/k \times t$ ,再和 $d$ 比较一下即可.

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read() {
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
long long n,t,k,d;
int main(){
    n=read();t=read();k=read();d=read();//输入 
    if((n-1)/k*t>d)cout<<"YES";//算出加烤箱后的平均速度，比较 
    else cout<<"NO";
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

## 题意&&思路
比较新建烤箱和不新建烤箱的时间。若新建烤箱时间小于不新建烤箱时间，输出是；否则输出不是。
首先我们要算出一个烤炉需要几个 $t$ 才能完成，然后总时间减掉 $d$ 算出这段时间第二个烤炉的工作量再加上一直在工作的第一个烤炉的量，若比之前多则为是。
## 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    cin>>n>>t>>k>>d;
    int c,q,l;
    if(n%k)
    
    n+=k-n%k;
    c=n/k;
    q=c*t-1;//t==d且x==2时为NO
    l=(q-d)/t+q/t;
    
    if(l>=c)
    cout<<"YES"<<endl;
    else
    cout<<"NO"<<endl;
    return 0;
}
```
### 完结撒花
###### ~~管理员行行好~~

---

## 作者：xmkevin (赞：0)

本题比较简单，直接在代码中注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
   int n, k, t, d;
   cin>>n>>t>>k>>d;//输入
   if((n - 1) / k * t > d) {//加入烤箱后的平均速度为(n - 1) / k * t，和建造时间d进行比较即可，如果加入烤箱后的平均速度比建造时间大，那么输出YES，否则建造将会得不偿失，输出NO。
   	cout << "YES";
   }
   else cout << "NO";//输出yes或no
}
```

---

## 作者：Vibration886 (赞：0)

### [CF799A Carrot Cakes](https://www.luogu.com.cn/problem/CF799A)

## 题意

一共需要烤 $n$ 个蛋糕，用一个烤箱烤 $k$ 个蛋糕需要 $t$ 分钟。现有一个烤箱，可以再用 $d$ 分钟建一个。建烤箱时正在建的烤箱不能工作，但另一个烤箱可以。比较新建烤箱烤完 $n$ 个蛋糕的时间是否大于不新建的时间。

## 思路

比较加烤箱后的平均速度和新建烤箱的时间即可。

加烤箱后的平均速度可以算出来：$\frac{(n-1)t}{k}$。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,k,d; 
int main()
{
	ios::sync_with_stdio(false); 
	cin>>n>>t>>k>>d;
	if((n-1)/k*t>d)
	{
	    cout<<"YES";
	    return 0;
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：cdhh (赞：0)

只需要比较平均速度 $\frac{(n-1)t}{k}$ 与做一个的时间 $d$ 即可
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,t,k,d; 
int main()
{
	cin>>n>>t>>k>>d;
	if((n-1)/k*t>d) cout<<"YES";
	else cout<<"NO";
	return 0;
}

```


---

