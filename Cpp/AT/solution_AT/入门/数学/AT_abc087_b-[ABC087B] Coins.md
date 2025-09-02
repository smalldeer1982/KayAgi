# [ABC087B] Coins

## 题目描述

你有500日元硬币A枚、100日元硬币B枚、50日元硬币 C枚。 现在，从这些硬币中挑出数枚硬币，各个硬币价格之和刚好等于X日元的组合有多少种。 需要注意的是：

同种类（面值）的硬币是没有区别的
不同的组合方式以某个面值的硬币数量不同来区分
0 ≤ A, B, C ≤ 50
A + B + C ≥ 1
50 ≤ X ≤ 20,000
A, B, C 一定是整数
X 一定是50的倍数

## 样例 #1

### 输入

```
2
2
2
100```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1
0
150```

### 输出

```
0```

## 样例 #3

### 输入

```
30
40
50
6000```

### 输出

```
213```

# 题解

## 作者：Komorebi_shine (赞：4)

这题就是一道基础模拟题，直接循环各种面值数量即可。

当然也可以只枚举前两种，因为题目保证k%50==0，只要判断去掉前两种钱之后的钱是否在50的钱所能达到的范围即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,i,j,n,s;
int main()
{
    scanf("%d%d%d%d",&a,&b,&c,&n);
    for (i=0;i<=a;i++)
     for (j=0;j<=b;j++)
      if ((n-i*500-j*100>=0)&&(n-i*500-j*100<=c*50)) ++s;
    printf("%d\n",s);
    return 0;
}
```

---

## 作者：失之_连心 (赞：3)

这道题直接就可以暴力枚举过，枚举500,100,50的硬币个数，再判断是否为x

代码:
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	long long x,a,b,c,ans=0;//long long保险
	cin>>a>>b>>c>>x;//输入这四个数
	for(int i=0;i<=a;i++)//枚举500硬币的个数
	    for(int j=0;j<=b;j++)//枚举100硬币的个数
	        for(int z=0;z<=c;z++){//枚举50硬币的个数
	        	int k=i*500+j*100+z*50;//定义k为此时硬币总值
	        	if(k==x)//如果就是x
	        	   ans++;//计数器加一
	        	if(k>x)//这是一个优化，如果k值已经超过了x，后面的z到c时k的值一定大于x，肯定不等于x，所以可以直接退出当前循环
	        	   break;//退出当前循环
	        }
	cout<<ans<<endl;//输出ans的值(AT题都要打换行)
	return 0;
}
```


---

## 作者：林家三少 (赞：2)

一道基础模拟题，

~~所以我还能说什么呢？~~

[$\color{black}\text{AC证据}$](https://www.luogu.org/record/25476059)

直接上代码吧：

```cpp
#include<bits/stdc++.h>  //万能头文件是好东西
using namespace std;
int a,b,c,i,j,n,s;  //定义
int main()
{
    scanf("%d%d%d%d",&a,&b,&c,&n);  //输入
    for(i=0;i<=a;i++)  //开始循环
     for(j=0;j<=b;j++)
      if((n-i*500-j*100>=0)&&(n-i*500-j*100<=c*50)) s++;  //判断然后s++
    printf("%d\n",s);  //最后直接输出+换行
    return 0;
}
```


---

## 作者：linhongzhao321 (赞：2)

有一个坑，题目下方事例，数量为0的就没有输出。我以为为0的就不用输出，特意加了判断。结果有4道题WA，去掉了那个判断才AC

### 翻译如下
你有500日元硬币A枚、100日元硬币B枚、50日元硬币 C枚。 现在，从这些硬币中挑出数枚硬币，各个硬币价格之和刚好等于X日元的组合有多少种。 需要注意的是：

1. 同种类（面值）的硬币是没有区别的
2. 不同的组合方式以某个面值的硬币数量不同来区分
3. 0 ≤ A, B, C ≤ 50
4. A + B + C ≥ 1
5. 50 ≤ X ≤ 20,000
6. A, B, C 一定是整数
7. X 一定是50的倍数
输入格式

A枚500日元硬币

B枚100日元硬币

C枚50日元硬币

组合价值之和等于X元

输出格式

组合的方式个数

### 题解
其实题看懂了，就好做了

需要注意的是，不要N^2了，分分钟超时。后面要加个判断，当前循环已经超了就不用继续模拟了。这样可以减到N²/2
```c
#include <stdio.h>

int main ()
{
    int a, b, c, x, i, j, k, cnt=0;
    scanf("%d%d%d%d", &a, &b, &c, &x);
    for (i=0; i <= a && 500*i<=x; i++)
    {
        for (j=0; j <= b && 100*j+500*i<=x; j++)
        {
            for (k=0; k <= c && 50*k+100*j+500*i<=x; k++)
            {
                if (500*i+100*j+50*k==x)
                {
                    cnt++;
                }
            }
        }
    }

    printf("%d", cnt);

    return 0;
}
```

---

## 作者：bym666 (赞：0)

# AT3880 【Coins】
这道题有许多方法可以解决，但是由于数据范围较小，所以我们直接三重循环枚举个数就可以AC了。

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int a,b,c,x,ans;
int main()
{
	cin>>a>>b>>c>>x;//输入 
	for(int i=0;i<=a;i++)//从1枚举到a 
	{
		for(int j=0;j<=b;j++)//从1枚举到b 
		{
			for(int k=0;k<=c;k++)//从1枚举到c 
			{
				if(500*i+100*j+50*k==x) ans++;//如果加起来是x日元，答案数加一 
			}
		}
	}
	cout<<ans;//输出 
	return 0;//结束程序 
} 
```


---

## 作者：L2_sheep (赞：0)

这题还可以用数学方法来优化。
首先因为所有币值都是50的倍数，所以就转化为a个币值为10，b个币值为2，c个币值为1，凑成币值为x除以50的种数。
当币值10的个数确定时，2x + y = d的解的个数是比较好求解的，可以算出x的最大值，和最小值，相减加一就是解的个数，这样就只需要一重循环就可解决。
代码如下：
```cpp
#include <stdio.h>


int main() 
{
    int a, b, c, x, i, t, min, max, d, sum = 0, bb;
    
    scanf("%d%d%d%d", &a, &b, &c, &x);
    
    x /= 50, bb = b << 1;
    if(x & 1){
        if((c & 1) == 0) c--;	
    }
    else{
        if(c & 1) c--;
    }
    for(i = t = 0; i <= a && t <= x; t += 10, i++){
    	d = x - t;
    	if(bb + c < d) continue;
    	if(d > c) min = (d - c) >> 1;		
        else min = 0;
        if(d - bb >= 0) max = b;
        else max = d >> 1;
        sum += max - min + 1;
        //printf("%d %d\n", max, min);
    }
    printf("%d\n", sum);
    
    return 0;
}
```
如果打印出每个最大值，最小值，就可以发现它们是由等差数列组成的，根据这个规律，又可以等差数列求和公式来优化，于是变成了O(1)的复杂度，代码如下：
```cpp
#include <stdio.h>


int main() 
{
    int a, b, c, x, t, sum = 0, bb;
    int imin, imax, y, z;
    
    scanf("%d%d%d%d", &a, &b, &c, &x);
    
    x /= 50, bb = b << 1;
    if(x & 1){
        if((c & 1) == 0) c--;	
    }
    else{
        if(c & 1) c--;
    }
        
    imin = 0;
    t = (x - bb - c) / 10;
    if(x - bb - c > 0 && (x - bb - c) % 10 != 0) t++;
    if(t > imin) imin = t;
    imax = a;
    t = x / 10;
    if(t < imax) imax = t;
    
    if(imax < imin){
    	puts("0");
    	return 0;
    }
    sum = imax - imin + 1;
    
    if(x < c) t = -1;
    else t = (x - c) / 10;
    if(t >= imin){
    	if(t > imax) t = imax;
    	y = (x - 10 * t - c) >> 1;
    	z = (x - 10 * imin - c) >> 1;
    	sum -= ((y + z) * (t - imin + 1)) >> 1;
    }
    
    if(x >= bb) t = (x - bb) / 10 + 1;
    else t = 0;
    if(t <= imax){
        if(t < imin) t = imin;
        y = (x - 10 * t) >> 1;
        z = (x - 10 * imax) >> 1;
        sum += ((y + z) * (imax - t + 1)) >> 1;
        sum += (t - imin) * b;
    }
    else sum += (imax - imin + 1) * b;
    printf("%d\n", sum);
    
    return 0;
}
```
实现起来有点复杂，细节比较多。对于这道题，三重循环也是可以过的，但是对于大一些的数据，时间差距是很大的。如果仔细思考的话，O(1)算法也是可以实现的。

---

