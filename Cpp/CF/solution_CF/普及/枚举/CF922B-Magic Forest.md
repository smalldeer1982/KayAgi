# Magic Forest

## 题目描述

### 题目大意

给定一个正整数$n$ ，求满足如下条件的三元组$(a,b,c)$ 的个数：

- $1 \le a \le b \le c \le n$ 
- $a \space xor \space b \space xor \space c=0$ 
- 存在一个边长分别为$a,b,c$ 的三角形。

## 样例 #1

### 输入

```
6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
```

### 输出

```
2
```

# 题解

## 作者：durex_com (赞：2)

## 很看不懂那些$O(n^3)$的做法。

a xor b xor c==0为什么要用三重循环？

只需要枚举两项，另一项直接表示不就行了。(？？)

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	int cnt=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i-1;j++)
	{
		if(((i+j)>(i^j))&&((i-j)<(i^j))) 
		{
			if ((i^j)>i||(i^j)>j) continue;
			cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：TLMPEX (赞：1)

因为数据水，所以可以枚举三个量，并判断能否成三角形就可以了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,i,j,k,z=0;
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			for(k=j;k<=n;k++)//枚举
				if(!(i^j^k)&&i+j>k)z++;//判断是否成三角形并是否异或为0
	cout<<z;
}
```


---

## 作者：zljhenry (赞：0)

先来解释一下题义：

- $xor$ 这东西初赛你应该见过，异或的意思，在程序里用 " ^ " 来表示。
这个东西的意思是按位比较，如果相同，值是0；不相同，值是 1 。


那么就可以写一个暴力了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
   //freope(".in","r",stdin);
   //freope(".out","w",stdout);
   int n;
   cin>>n;
   int ans=0;
   for(int a=1;a<=n;a++){
      for(int b=a;b<=n;b++){
         for(int c=b;c<=n;c++){//三重循环枚举
            int m=a^b^c;
            if(m==0&&a+b>c&&a+c>b&&b+c>a)ans++；
         }
      }
   }
   cout<<ans;
   //fclose(stdin);fclose(stdout);
   return 0;
}

```
没想到竟然 AC 了。。。

![1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922B/eea79d64d5bc09a90f356e81b9be908191dfc1cd.png)


但还能不能再优化呢？

我们发现 $a$ 异或 $b$ 那个数肯定和 $a$ 异或为0，和 $b$ 异或为0 。

所以我们就可以去掉一层循环，然后把 $c$ 表示出来。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
   //freope(".in","r",stdin);
   //freope(".out","w",stdout);
   int n;
   cin>>n;
   int ans=0;
   for(int a=1;a<=n;a++){
      for(int b=a;b<=n;b++){
         if(a^b==0){
            int c=a^b;
            if(a+b>c&&a+c>b&&b+c>a&&c>=b&&c<=n){
               cout<<a<<' '<<b<<' '<<c<<endl;
               ans++;
            }
         }
      }
   }
   cout<<ans;
   //fclose(stdin);fclose(stdout);
   return 0;
}
```



---

## 作者：happybob (赞：0)

真的想问CF的评测机速度有多快，O($n^3$)都能过

代码：

```cpp
#include <stdio.h>

int main()
{
    int n, cnt = 0;
    scanf("%d", &n);
    for(register int i = 1; i <= n; i++)
    {
        for(register int j = i; j <= n; j++)
        {
            for(register int x = j; x <= n && i + j > x; x++)
            {
                cnt += !(i ^ j ^ x);
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
```
# bye

---

## 作者：hensier (赞：0)

$n \le 2500$，何必不$O(n^3)$？不过事实上是不会达到$O(n^3)$，因为如果真的$O(n^3)$，则时间复杂度可以达到$O(2500^3)=O((2.5\times 10^3)^3)$，即$O(15.625\times 10^9)$，即大约$O(1.5625\times 10^{10})$，因此只需要$a∈[1,n],b∈[a,n],c∈[b,n]$的循环即可，反正$O($能过$)$，个人测试的耗时最高数据点也不到$800ms$。~~数据水？~~

直接上~~暴力~~$AC$代码：

```cpp
#include<cstdio>
int n,a,b,c,s;
int main()
{
    scanf("%d",&n);//输入n
    for(a=1;a<=n;a++)
    {
        for(b=a;b<=n;b++)
        {
            for(c=b;c<=n;c++)
            {
                if(a^b^c)continue;//如果异或值不为0就跳到下一次循环
                if(a+b<=c)continue;//因为a<=b<=c，所以如果a+b<=c就无法构成三角形
                s++;
            }
        }
    }
    printf("%d",s);
}
```

---

## 作者：PC_DOS (赞：0)

其实只需要枚举并判断三个数的异或是不是0就可以了，甚至连判断三角形都不需要。

假定循环变量为i，j，k，循环体为:
```
for (i = 1; i <= iEnd; ++i){
	for (j = i; j <= iEnd; ++j){
		for (k = j; k < min(i + j,iEnd+1); ++k){
			//执行语句
		}
	}
}
```
可以看到，由于i+j>k>=j>=i，所以k+i>j，i+j>k，k+j>i，必定满足三角形的构成要件，因此，不需要判断i，j，k能不能构成三角形。

但是需要注意，因为C++中异或运算符"^"优先级低于比较运算符"=="，所以判断表达式必须写为:
```
if ((i^j^k)==0){
	//执行语句
}
```

此外，循环时，k的终止条件需要同时考虑输入的iEnd与i+k，即应当为k<min(i + j,iEnd+1)。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int i, j, k, iEnd,nCount=0; //i、j、k-循环计数器，iEnd-i、j、k的最大值，nCount-符合要求的数对的(i,j,k)的个数
	cin >> iEnd; //读入最大值
	for (i = 1; i <= iEnd; ++i){ //开始枚举
		for (j = i; j <= iEnd; ++j){
			for (k = j; k < min(i + j,iEnd+1); ++k){ //k的终止条件需要同时考虑输入的iEnd与i+k，即应当为k<min(i + j,iEnd+1)
				if (((i^j^k) == 0)) //如果满足题意，注意，因为C++中异或运算符"^"优先级低于比较运算符"=="，所以判断表达式必须写为:(i^j^k)==0
					++nCount; //计数器加一
			}
		}
	}
	cout << nCount; //输出答案
	return 0; //结束
}
```

---

