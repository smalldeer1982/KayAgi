# Co-prime Array

## 题目描述

给你一个n个元素的数组，你必须尽可能少的添加元素使得该序列成为一个co-prime数组。

每次可以插入任何正整数不大于10^9在数组的任意位置。

如果一个数组的任意两个相邻的数是互质的，那么这个数组就是co-prime。

## 样例 #1

### 输入

```
3
2 7 28
```

### 输出

```
1
2 7 9 28
```

# 题解

## 作者：shame_djj (赞：4)

这题 n 是 1e3 ，但是我想不出 O（n2） 算法，滑稽滑稽

原题链接[【Co-prime Array】](https://www.luogu.org/problem/CF660A)

构造题，随便构造一种合理的简单的方案就好了

我的思路和楼上一样，不互质的插入一个 1 就都互质了

关于构造题，我们应该做的是，

		用最简单的方法构造出最简单的但又得是符合条件的方案

本题比较水，我就直接上代码了

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e6 + 10;

inline int gcd (int a, int b) {
	return b == 0 ? a : gcd (b, a % b);
}

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
	for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}

int a[maxn], b[maxn];
int n, ans, cnt;

void djj_lxy () {
	n = read();
	for (register int i = 1; i <= n; i ++)
		a[i] = read();
	for (register int i = 1; i < n; i ++) {
		b[++ cnt] = a[i];
		if (gcd (a[i], a[i + 1]) > 1)
			ans ++, b[++ cnt] = 1;
	}
	b[++ cnt] = a[n];
	printf ("%d\n", ans);
	for (register int i = 1; i <= cnt; i ++)
		printf ("%d ", b[i]);
}

int main () {
	djj_lxy ();
}
```

时间复杂度 O（n log x），空间复杂度 O （n），可以过掉 1e6 的数据

当然了，如果不是要求先输出插入次数，空间复杂度其实是可以弄成 O （1）的

~~我本来想现写一份空间复杂度为 O（1）的代码，写完了才发现不能做，滑稽滑稽~~

离 CSP-S 还有十来天，祝大家 rp ++

也希望自己能更努力一些，加油

---

## 作者：FP·荷兰猪 (赞：3)

刚开始理解的是要大于前一项小于后一项，判断了半天，结果超时。。其实这道题还是So Easy的，毕竟是CF的A题。。既然要让这个数列的元素满足两两互质，那么直接在不互质的两个元素之间插入1不就OK了？！！白白浪费那么多时间。。

代码如下：
```cpp
#include <bits/stdc++.h>  
using namespace std; 
int a[1010],b[1010];
int gcd(int x,int y){
	if(y==0)
		return x;
	return gcd(y,x%y);
}//求最大公约数 
int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		int ans=0;//用来记录步数 
		int k=0;//记录数列b的个数 
		for(int i=0;i<n-1;i++){
			if(gcd(a[i],a[i+1])==1)
				b[k++]=a[i];//如果互质则直接将该元素赋值给数列b 
			else{
				ans++;
				b[k++]=a[i];//不互质的两个数中第一个数仍赋值给b 
				b[k++]=1;//在不互质的第一个数后插入1 
			}//不互质的第二个数在下一步操作中处理 
		}
		b[k++]=a[n-1];//最后一个数，在循环中没考虑到！！ 
		printf("%d\n%d",ans,b[0]);
		for(int i=1;i<n+ans;i++){
			printf(" %d",b[i]);//输出格式 
		}
		printf("\n");
	}
    return 0;  
}
```

---

## 作者：封禁用户 (赞：1)

题目传送>>[CF660A](https://www.luogu.com.cn/problem/CF660A)。  
### 题意简述:  
- 给定一 $n$ 元素数组，求尽可能少的添加元素使得成为相邻元素两两互质的数组，输出最小添加数和操作后的数组。  
- $1 \leq n \leq 1000$，$1 \leq  n \leq 10^9$。  

### 题目分析：  
互质即两数公约数为 $1$，所以我们只需对数组中每相邻两数求其最大公约数是否为 $1$ 来进行判断是否需添加数，而要添加数使得数组所有相邻两数互质，我们据互质定义可知丢个 $1$ 在两数间即可。  
### Code：  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,ans=0;   //定义数组元素数，需添数个数
int a[1001];
int gcd(int m,int n)  //定义求最大公约数函数
{
	return n==0? m:gcd(n,m%n);
}
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) ans+=gcd(a[i],a[i+1])==1? 0:1;   //统计需添数个数
	cout<<ans<<endl;
	for(int i=1;i<n;i++)
	{
		cout<<a[i]<<" ";
		if(gcd(a[i],a[i+1])!=1) cout<<"1"<<" ";   //注意输出数间空格
	}
	cout<<a[n];  //输出数组中最后一数
	return 0;
}
```
### 结果(未吸氧):  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/9l6nz0z2.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：LordLaffey (赞：1)

##### 这道题其实非常水，就是可能有点不好想到

这道题首先要判断两个数是否互质，我们肯定都会想到求两个数的最大公约数，如果不是1，那么就不互质，就需要在这两个数之间加入一个数

那么究竟需要在这两个数之间加入什么数能符合要求呢¿  
**其实只需要在这两个数之间加入一个1就行**

至于为什么，其实我们可能会受到我们“两个数不能互相整除的数互质”的错误想法的限制，但真正的互质定义是
>互质是公约数只有1的两个数，叫做互质数

然后这道题就完美AC了  
下面贴代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1010];
int ans[2020];

int gcd(int x,int y){

    while(y!=0)
    {
        int t=x%y;
        x=y;
        y=t;
    }
    return x;

}

int main(){

    int n;
    scanf("%d",&n);

    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    int k=0,len=0;
    for(int i=1;i<n;i++)
    {
        ans[++len]=a[i];
        if(gcd(a[i],a[i+1])>1)
        {
            k++;
            ans[++len]=1;
        }
    }
    
    cout<<k<<endl;
    for(int i=1;i<=len;i++)
        cout<<ans[i]<<" ";
    cout<<a[n];

    return 0;

}
```
完结撒花✿✿ヽ(°▽°)ノ✿


---

## 作者：happybob (赞：0)

# 题意

给定 $n$ 和一个 $n$ 个元素的序列 $a_1, a_2, ……, a_n(a_1, a_2, ……, a_n \le 10^9)$，可以在任意一个 $i, i + 1$ 中间插入一个数 $x$，其中 $1 \le x \le 10^9$。现在要尽量插入较少的次数，使得任意 $\gcd(a_i, a_{i+1}) = 1$。

# 分析

先给个[质数表](https://blog.csdn.net/shiyongyang/article/details/78079109?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164441454416780269867446%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=164441454416780269867446&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-78079109.first_rank_v2_pc_rank_v29&utm_term=hash%E5%A4%A7%E8%B4%A8%E6%95%B0&spm=1018.2226.3001.4187)。

明显，一个质数 $x$ 只有 $1$ 和 $x$ 两个因数，所以对于任意一个 $p(1 \le p < x)$，$\gcd(p,x)=1$，而与 $x$ 不互质的数有 $x * k(k \ge 1)$，那么我们只需要在一个 $\gcd(a_i, a_{i+1}) \not = 1$ 中间插入一个大质数，例如 $917120411$，而 $2 \times 917120411 = 1834240822 > 10^9$。

但是有一种会被 hack，假设 $a_1, a_2, ……, a_n$ 中有 $a_i = 917120411$，那么就不行，那么就输出 $1$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int a[N];

int main()
{
    int n, cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 2; i <= n; i++)
    {
        cnt += (__gcd(a[i], a[i - 1]) != 1);
    }
    printf("%d\n", cnt);
    for (int i = 1; i < n; i++)
    {
        printf("%d ", a[i]);
        if (__gcd(a[i], a[i + 1]) != 1)
        {
            if (a[i] == 917120411) printf("1 ");
            else printf("917120411 ");
        }
    }
    printf("%d ", a[n]);
    return 0;
}
```



---

## 作者：thomas_zjl (赞：0)

这道题考的是数学基础，但我们要玩好玩的。

我看到 $a_i$ 小于 $10^9$ 时。

我就寻找 $10^9$ 以下最大的质数。

寻找代码如下。

```
#include<bits/stdc++.h>
using namespace std;
inline bool zs(int x){
	for(int i=2;i<=sqrt(x);i++)if(x%i==0) return 0;
	return 1;
}  
int main(){
	ios::sync_with_stdio(false);
	for(int i=1000000000;i>=0;i--)if(zs(i)==1) {cout<<i;return 0;}
	return 0;
}
```
发现最后输出的是 $999999937$ 。

但是防止题目出的数据中有 $999999937$ 这个数，故要特判。

我们还需判断两数是否互质，可以计算他们的最大公因数，如果是 $1$ 则互为互质数。

代码如下。
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[10086];
int b[10086];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int ans=0;
	int t=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		b[++t]=a[i];
		if(__gcd(a[i],a[i+1])!=1&&i!=n) {//判断是否互质。
			if(a[i]==999999937) b[++t]=999999938;//如果这个数是 999999937 ，那么这个数就添加 999999938。
			else b[++t]=999999937;
			ans++;	
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=t;i++) cout<<b[i]<<' ';
	return 0;
}
```


---

## 作者：pomelo_nene (赞：0)

啊啊？这道题怎么评上紫的？？？

不就是道A题嘛，构造题直接想符合题目要求并且最大化简化题目。所以做法显然，我们发现如果相邻两个数的gcd不是1，那就添加一个1不就完了？？？

时间复杂度$\Theta(n \log n)$（求gcd时间复杂度为$\Theta(\log  n)$）

```cpp
#include<cstdio>
int a[1005];
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	int t=0;
	for(int i=1;i<n;++i)	if(gcd(a[i],a[i+1])!=1)	++t;//如果不互质，答案加1然后在序列中添加1
	printf("%d\n",t);
	for(int i=1;i<n;++i)
	{
		printf("%d ",a[i]);
		if(gcd(a[i],a[i+1])!=1)	printf("1 ");
	}
	printf("%d\n",a[n]);
	return 0;
}
```

---

