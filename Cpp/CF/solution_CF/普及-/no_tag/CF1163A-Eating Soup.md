# Eating Soup

## 题目描述

The three friends, Kuro, Shiro, and Katie, met up again! It's time for a party...

What the cats do when they unite? Right, they have a party. Since they wanted to have as much fun as possible, they invited all their friends. Now $ n $ cats are at the party, sitting in a circle and eating soup. The rules are simple: anyone having finished their soup leaves the circle.

Katie suddenly notices that whenever a cat leaves, the place where she was sitting becomes an empty space, which means the circle is divided into smaller continuous groups of cats sitting next to each other. At the moment Katie observes, there are $ m $ cats who left the circle. This raises a question for Katie: what is the maximum possible number of groups the circle is divided into at the moment?

Could you help her with this curiosity?

You can see the examples and their descriptions with pictures in the "Note" section.

## 说明/提示

In the first example, originally there are $ 7 $ cats sitting as shown below, creating a single group:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/582841c5dfb385439eea8c43d7ec4b1600b2e8bf.png)At the observed moment, $ 4 $ cats have left the table. Suppose the cats $ 2 $ , $ 3 $ , $ 5 $ and $ 7 $ have left, then there are $ 3 $ groups remaining. It is possible to show that it is the maximum possible number of groups remaining.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/b09fab4219f78478e7216cc25f298db91c1649f6.png)In the second example, there are $ 6 $ cats sitting as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/44c3b731251174253272f06b55bec85d62ac7660.png)At the observed moment, $ 2 $ cats have left the table. Suppose the cats numbered $ 3 $ and $ 6 $ left, then there will be $ 2 $ groups remaining ( $ \{1, 2\} $ and $ \{4, 5\} $ ). It is impossible to have more than $ 2 $ groups of cats remaining.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163A/b113b3b66afa92745963d53380bedced5a41e1a8.png)In the third example, no cats have left, so there is $ 1 $ group consisting of all cats.

In the fourth example, all cats have left the circle, so there are $ 0 $ groups.

## 样例 #1

### 输入

```
7 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 0
```

### 输出

```
1
```

## 样例 #4

### 输入

```
2 2
```

### 输出

```
0
```

# 题解

## 作者：expnoi (赞：2)

这题很水，但是很多人都会理解成模拟题。


题意：给出结点数$n$结点两两相连成一个环,再给出$m$求在环中去掉$m$个点,使得联通块最大,输出最大联通块。


解析：在$n / 2$、$n-m$、$m$三个数中取最小值，结果受这三个值限制。但是$m$==$0$的情况需要特判,输出1。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    cout<<(m==0?1:min(m,n-m));//三目运算
    return 0;//好习惯
}
```

---

## 作者：chinaxjh (赞：0)

看到没人发题解，就来水一发

这道题非常的简单（看懂题目的人都会做）

#### 就是一个n个节点的环，去掉m个之后的最大组数

可以把这题看做一个贪心题，
### 隔一个去掉就是贪心的核心
，再稍微逻辑推算一下就可以得出在m小于等于n/2(取整)的情况下，就是m组

再考虑大于的情况，发现在偶数的情况下每多一个去掉就会比最大情况下（n div 2）少一组，奇数时先去掉一个不会比（n div 2）少，再去掉一个就开始少了

整理一下发现两个情况下都是n-m(因为奇数本来就多一)

这样就解决掉了这道红题

上代码
```
var
  n,m,k:longint;
begin
  readln(n,m);//scanf("%d%d",&n,&m);
  if m=0 then//特判为0的情况，直接输出1
  begin
    writeln(1) ;
    halt;
  end;
  k:=n div 2;
  if m<=k then writeln(m)
  else begin
    writeln(n-m);
  end;//上文所说的两种情况
end.//用pascal是因为pascal跑得快
```


---

## 作者：xh39 (赞：0)

找规律(也可以贪心)

思路:把1,3,5,...依次移除,每移除一个就多一个组。如果还不够就2,4,6,8,...依次移除,每移除一个就少一个组。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,i,j;
	cin>>n>>m;
	if(m==0){ //特判。
		cout<<1;
	}else if(m<=(n>>1)){ //1,3,5,7,...够移除。(n>>1)相当于快速的计算n/2;
		cout<<m;
	}else{
		cout<<n-m; //1,3,5,7,...不够移除。
	}
	return 0;
}

```


---

