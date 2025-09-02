# [ABC085C] Otoshidama

## 题目描述

在日本常用的纸币有 $10000$ 日元、$5000$ 日元、$1000$ 日元。以下所说的“纸币”仅指这三种。

据青桥同学说，他从祖父那里收到的压岁钱袋里有 $N$ 张纸币，总金额为 $Y$ 日元，但这也可能是谎言。请判断是否存在这样的情况，如果存在，请找出一种可能的压岁钱袋内纸币的组合。假设他的祖父非常富有，压岁钱袋也足够大。

## 说明/提示

### 限制条件

- $1 \leq N \leq 2000$
- $1000 \leq Y \leq 2 \times 10^7$
- $N$ 是整数。
- $Y$ 是 $1000$ 的倍数。

### 样例解释 1

如果压岁钱袋里有 $10000$ 日元纸币 $4$ 张和 $1000$ 日元纸币 $5$ 张，则总共 $9$ 张纸币，总金额为 $45000$ 日元。也有可能是 $5000$ 日元纸币 $9$ 张，因此 `0 9 0` 也是正确输出。

### 样例解释 2

如果总共 $20$ 张纸币，全部为 $10000$ 日元纸币时总金额为 $200000$ 日元，否则总金额不会超过 $195000$ 日元，因此 $196000$ 日元这个总金额是不可能的。

### 样例解释 3

除此之外还有许多其他可能的组合。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9 45000```

### 输出

```
4 0 5```

## 样例 #2

### 输入

```
20 196000```

### 输出

```
-1 -1 -1```

## 样例 #3

### 输入

```
1000 1234000```

### 输出

```
14 27 959```

## 样例 #4

### 输入

```
2000 20000000```

### 输出

```
2000 0 0```

# 题解

## 作者：tZEROちゃん (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT3853)。

暴力枚举题。

**分析**

Step 1：定义两个变量，$n$和$y$。
```cpp
	int n,y;
	cin>>n>>y;
```

Step 2：使用**二重循环**进行暴力枚举。
```cpp
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n-i;j++)
			if(i*10000+j*5000+(n-i-j)*1000==y)
				cout<<i<<' '<<j<<' '<<n-i-j<<'\n',exit(0);

```

在这一步上很多大佬使用了**三重循环**，其实用二重循环就可以解决了。

Step 3：找完了还是没有符合要求的数。直接输出`-1 -1 -1`并结束程序。
```cpp
	cout<<"-1 -1 -1\n";
```


**完整代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,y;
	cin>>n>>y;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n-i;j++)
			if(i*10000+j*5000+(n-i-j)*1000==y)
				cout<<i<<' '<<j<<' '<<n-i-j<<'\n',exit(0);
	cout<<"-1 -1 -1\n";
	return 0;
}
```

**若题解有问题请私信我。**

---

## 作者：一只书虫仔 (赞：1)

[AT3853 [ABC085C] Otoshidama](https://www.luogu.com.cn/problem/AT3853)

[AC记录~](https://www.luogu.com.cn/record/32432033)

算法 ：**暴力枚举**

思路 ：用两层循环枚举 $10000,5000$ 和 $1000$ 的个数，用两层循环即可，然后枚举 $i\cdot 10000+j\cdot 5000+(n-i-j)\cdot 1000$ ，看是不是等于 $y$ ，是的话立刻退出程序，然后到最后没有退出程序输出 `-1` 。

Tips : 标程别抄，太过玄学，按照这个思路标程不是对的，不知道怎么回事 AC 了（

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, y;
    scanf("%d%d", &n, &y);
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n - i + 1; j++)
            if (i * 10000 + j * 5000 + (n - i - j) * 1000 == y) {
            	int coin = n - i - j;
            	printf("%d %d %d", i, j, coin);
            	return 0;
			}
    printf("-1 -1 -1");
    return 0;
}
```

---

## 作者：The_Tarnished (赞：0)

# 大水题！！！
一道暴力枚举入门题，枚举每一种money的数量
- 如果**数量和=N，钱总和=Y**，那么这就是一个可行的解
- 如果没有一种满足，那么久输出-1 -1 -1


------------
### 优化：
- 枚举可以从10000的money开始枚举，~~这样枚举次数可能会少一点点（就一点点）~~
- 枚举时如果钱总数已经大于Y，就可以不用做了，不需要等到钞票数>N时，~~这样枚举次数可能会少一点点（也就一点点）~~

 _上代码_ 

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n,y;

int main(){
	scanf("%d%d",&n,&y);
	for(int i=0;i<=n&&10000*i<=y;i++)//钱总数大于Y，停止
	    for(int j=0;i+j<=n&&10000*i+5000*j<=y;j++)//钞票数大于N，停止 或 钱总数大于Y，停止
	        if((y-10000*i-5000*j)%1000==0&&(y-10000*i-5000*j)/1000==n-i-j){
            //N-I-J的就是1000的数量，如果可以就找到解啦
	        	printf("%d %d %d\n",i,j,(y-10000*i-5000*j)/1000);
	        	return 0;
			}
	//如果一组解也没有，那我也没办法。。。
	printf("-1 -1 -1\n");
	return 0;
}

```


---

## 作者：幻蓝 (赞：0)

P党代码绝无仅有（笑）

```pascal
var
  n,y,i,j,k:longint;
begin
  readln(n,y);
  if (y div n=10000) then//以下为特殊判断，会快很多
  begin
     writeln(n,' ',0,' ',0);
     halt;
  end;
  if (y div n=5000) then
  begin
    writeln(0,' ',n,' ',0);
    halt;
  end;
  if (y div n=1000) then
  begin
    writeln(0,' ',0,' ',n);
    halt;
  end;
  if (n*10000<y) then
  begin
    writeln('-1 -1 -1');
    halt;
  end;
  if (n*1000>y) then
  begin
    writeln('-1 -1 -1');
    halt;
  end;
  if (y mod 1000<>0) then
  begin
    writeln('-1 -1 -1');
    halt;
  end;//暴力开始！
  for i:=0 to y div 10000 do//从不选到至少选多少个，这样时间复杂度会少，最重要！
  for j:=0 to n-i do//n-i去重，减时间，不然过不去
  if (i*10000+j*5000+(n-i-j)*1000=y) //判断这个方案是否成立
  then begin
     writeln(i,' ',j,' ',n-i-j);//成立输出
     halt;//结束所有程序
  end;
  writeln('-1 -1 -1');//如果不成立那么他就不会结束程序，就可以输出不成立的结果拉
end.
```

---

## 作者：chengni (赞：0)

稍加判断，然后大力循环

枚举三种钞票的数量，并且进行剪枝

确实非常暴力，但很管用

代码如下
```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
int main(){
    int m,n;
    scanf("%d%d",&m,&n);
    
    if(m*10000<n){
        printf("-1 -1 -1");
        return 0;
    }
    if(m*1000>n){
        printf("-1 -1 -1");
        return 0;
    }
    if(n%1000!=0){
        printf("-1 -1 -1");
        return 0;
    }
    for(int i=0;i<=m;i++)
     for(int j=0;j<=m;j++)
      for(int k=0;k<=m,i+j+k<=m;k++)
       {
       		if(i+j+k==m && i*1000+j*5000+k*10000==n)
       		{
       			printf("%d %d %d",k,j,i);
                return 0;	
            }
       }
    printf("-1 -1 -1");
    return 0;
}
```

---

## 作者：Teddy·Bear (赞：0)

感谢楼下大佬提示，我给他的代码优化了一下！！！无需加特判，因为下面循环就是特判！！！
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m;i++)
     for(int j=0;j<=m;j++)
      for(int k=0;k<=m,i+j+k<=m;k++)
       {
            if(i+j+k==m && i*1000+j*5000+k*10000==n)
            {
                printf("%d %d %d",k,j,i);
                return 0;   
            }
       }
    printf("-1 -1 -1");
    return 0;
}
```
其实这题不够严谨，样例有多种情况，比如样例1，它的情况有多种，建议更改QAQ

---

