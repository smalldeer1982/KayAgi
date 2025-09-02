# Three Friends

## 题目描述

有三个人站在一个平面直角坐标系的$x$轴上，他们的纵坐标分别为$a,b,c$  
定义这三个的距离和为$|a-b|+|b-c|+|a-c|$

接下来的一分钟，他们每一个人可以选择：向左走一个单位长度 或 向右走一个单位长度，求一分钟后的三个人的最小距离和

## 说明/提示

$1\leq q \le 1000$  
$1\leq a,b,c \le 10^9$  
感谢 @_Wolverine  提供的翻译

## 样例 #1

### 输入

```
8
3 3 4
10 20 30
5 5 5
2 4 3
1 1000000000 1000000000
1 1000000000 999999999
3 2 5
3 2 6
```

### 输出

```
0
36
0
0
1999999994
1999999994
2
4
```

# 题解

## 作者：Rainbow_qwq (赞：3)

[CF1272A Three Friends](https://www.luogu.com.cn/problem/CF1272A)

---

给一个简单的$O(1)$思路。

先对$3$个数排序。假设$a\leq b\leq c$：

1. 若$c-a\leq 2$，那$3$个人最后肯定能走到同一位置，答案为$0$；
2. 否则$c$向左走，$a$向右走。因为$b$在$a,c$中间，答案为$((c+1)-(a-1))+((c+1)-b)+(b-(a-1))=((c-1)-(a+1))\times 2$

代码部分：
```cpp
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
void work()
{
	int a=read(),b=read(),c=read();
	if(a>b)swap(a,b);if(a>c)swap(a,c);if(b>c)swap(b,c);//排序
	if(c-a<=2)puts("0");
	else printf("%d\n",((c-1)-(a+1))*2);
}
```

---

## 作者：AmamiyaYuuko (赞：2)

这道题给出了三个数 $a, b, c$，每个数可以加上 $1$ 或减去 $1$，问 $|a - b| + |a - c| + |b - c|$ 的最小值。

这里给出一种较为暴力的方法。对于每个人分别枚举加 $1$，减 $1$，和不加也不减的情况，然后更新答案。

由于总共只有 $27$ 种情况，所有并不会超时。

要记得在更新答案后要把每个数还原，以免出现错误。

在代码中的排序是不必要的，因为做这道题的时候没有睡醒。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

const int dx[] = {1, -1, 0};

int a[5];
int q;

long long dis(int a, int b, int c)
{
    return abs(b - a) + abs(c - a) + abs(c - b);
}

int main()
{
    std::cin >> q;
    while (q--)
    {
        long long ans = 0x7f7f7f7f;
        std::cin >> a[1] >> a[2] >> a[3];
        std::sort(a + 1, a + 4);
        for (int i = 0; i < 3; ++i)
        {
            a[1] += dx[i];
            for (int j = 0; j < 3; ++j)
            {
                a[2] += dx[j];
                for (int k = 0; k < 3; ++k)
                {
                    a[3] += dx[k];
                    ans = std::min(ans, dis(a[1], a[2], a[3]));
                    a[3] -= dx[k];
                }
                a[2] -= dx[j];
            }
            a[1] -= dx[i];
        }
        std::cout << ans << std::endl;
    }   
    return 0;
}
```

---

## 作者：　　　吾皇 (赞：1)

感觉翻译没有说明白啊 明明可以不走的。

显然可以通俗易懂暴力做，因为每个人都有三种可能的情况，所以总复杂度为 $O(q \times 3^3)$ 不会超时。

### 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll ans,a,b,c,q;//ans存储当前距离的最小值，a、b、c如题意，开long long防爆 
int main(){
	scanf("%d",&q);//读入数据组数
   	while(q--){
    	ans=3000000000;//先赋一个大的初值
   		scanf("%d%d%d",&a,&b,&c);
        	for(ll i=a-1;i<=a+1;i++)
            	for(ll j=b-1;j<=b+1;j++)
                    for(ll k=c-1;k<=c+1;k++)
                        ans=min(ans,abs(i-j)+abs(i-k)+abs(j-k));//直接暴力枚举求最小值 
        printf("%d\n",ans);
    }
}

```


---

## 作者：codemap (赞：0)

~~一道水题~~

这道题我用了一个数组来存,主要是因为排序方便

一共分四类:

1. $a[1]=a[2]=a[3]$

直接输出0即可

2. $a[1]=a[2]<a[3]$

此时$a[1]$和$a[2]$向右走,$a[3]$向左走

答案是$a[3]-a[2]-2+a[3]-a[1]-2$

3. $a[1]<a[2]=a[3]$

此时$a[2]$和$a[3]$向左走,$a[1]$向右走

答案是$a[2]-a[1]-2+a[3]-a[1]-2$

4. $a[1]<a[2]<a[3]$

此时$a[1]$向右走,$a[3]$向左走

答案是$a[3]-a[2]-1+a[2]-a[1]-1+a[3]-a[1]-2$

注意$2,3,4$这三种情况有可能答案$<0$,要与$0$取$max$

上代码

```
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int q,a[4];
	cin>>q;
	while(q--)
	{
		cin>>a[1]>>a[2]>>a[3];
		sort(a+1,a+4);//排序
		if(a[1]==a[2])
		{
			if(a[2]==a[3])//第一种
				cout<<0<<endl;//输出0
			else//第二种
				cout<<max(a[3]-a[2]-2+a[3]-a[1]-2,0)<<endl;//取max
		}
		else if(a[2]==a[3])//第三种
			cout<<max(a[2]-a[1]-2+a[3]-a[1]-2,0)<<endl;//取max
		else//第四种
			cout<<max(a[3]-a[2]-1+a[2]-a[1]-1+a[3]-a[1]-2,0)<<endl;//取max
	}
	return 0;//结束
}
```
# 请勿抄袭

---

