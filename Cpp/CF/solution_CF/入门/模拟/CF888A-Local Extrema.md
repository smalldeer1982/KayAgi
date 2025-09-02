# Local Extrema

## 题目描述

You are given an array $ a $ . Some element of this array $ a_{i} $ is a local minimum iff it is strictly less than both of its neighbours (that is, $ a_{i}<a_{i-1} $ and $ a_{i}<a_{i+1} $ ). Also the element can be called local maximum iff it is strictly greater than its neighbours (that is, $ a_{i}>a_{i-1} $ and $ a_{i}>a_{i+1} $ ). Since $ a_{1} $ and $ a_{n} $ have only one neighbour each, they are neither local minima nor local maxima.

An element is called a local extremum iff it is either local maximum or local minimum. Your task is to calculate the number of local extrema in the given array.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
1 5 2 5
```

### 输出

```
2
```

# 题解

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/18/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces888A%20Local%20Extrema)

### Solution

题目怎么说我们怎么做就可以了，循环直接从$2 \to n - 1$进行枚举。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 1005;
int n, a[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 2; i < n; i++)
        if (a[i] > a[i - 1] && a[i] > a[i + 1] || a[i] < a[i - 1] && a[i] < a[i + 1]) ans++;//按题目模拟
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：yxy666 (赞：0)

## 题解 CF888A Local Extrema

这道题目貌似比较简单。只要当前这个数大于前面的数并且大于后面的数或者当前这个数小于前面的数并且小于后面的数，那么，就多了一个局部极值。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[1005]; 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}	
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<n;i++)if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1]))ans++;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：RBI_GL (赞：0)

### 题意：
 
输入 $n$ 个数，求其中有多少个数 $a_i$ 满足：

![](https://cdn.luogu.com.cn/upload/image_hosting/5k1truha.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即：

```cpp
a[i]>a[i-1]&&a[i]>a[i+1] || a[i]<a[i-1]&&a[i]<a[i+1]
```

**以上就是核心判断代码，如果满足计数器就加一，最后输出答案。**


------

### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[1005];
int ans = 0;
int main() {
	cin>>n;  
	for(int i=1; i<=n; i++) cin>>a[i]; //输入 
	for(int i=2; i<=n-1; i++) {
		if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1])) { //按照题目中的条件进行判断 
			ans++; //如果有符合的，计数器就加一 
		}
	}
	cout<<ans; //输出答案 
	return 0;
}
```






---

## 作者：开心的猪 (赞：0)

这道题看了LOCAL Extreme 的定义和数据范围后发现可以直接模拟。

下面是代码：

```c
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	int ans=0;
	for(int i=1; i<n-1; i++)
	{
		if(a[i]>a[i-1]&&a[i]>a[i+1])
		{
			ans++;
		}
		if(a[i]<a[i-1]&&a[i]<a[i+1])
		{
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：陈洋琛 (赞：0)

这题很简单，直接跟着题意模拟去做就好了

下面献上代码：
~~~
#include <iostream>
using namespace std;
int main()
{
    int n,a[1010],ans=0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]; //输入
    for(int i=2;i<=n-1;i++) //注意要从第二个数到第n-1个数，否则会数组越界
        if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1]))
            ans++;  //当满足条件时，就将个数加一
    cout<<ans<<endl; //输出
    return 0; //结束程序
}
~~~

---

## 作者：树下 (赞：0)

# 直接一个简单的模拟就好了，看代码：
## 一个for循环就好了
```
#include<bits/stdc++.h>
using namespace std;
int tot,n;
int a[1005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);//输入
	for(int i=2;i<n;i++)
	if((a[i]<a[i-1]&&a[i]<a[i+1])||(a[i]>a[i-1]&&a[i]>a[i+1]))
	tot++;//每当满足条件就让方案数加一
	printf("%d",tot);//输出
    return 0;//完美收尾
} 
```

---

