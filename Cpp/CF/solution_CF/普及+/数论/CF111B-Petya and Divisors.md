# Petya and Divisors

## 题目描述

**Petya**喜欢寻找数字的因子。有一天他看到了这样的一条题目$:$

有$n$个形如$[x,y]$的二元组，对于每一个二元组，**Petya**希望找到有多少个$x_i$的因子，使得在$[x_{i-y_i},x_{i-y_i+1},\cdots,x_{i-1}]$中的每一个数都不能整除它。帮帮他解决这个问题吧。

## 说明/提示

样例一中前五个数的符合条件的因子如下:

- $1)$  $1,2,4$
- $2)$  $3$
- $3)$  $5$
- $4)$  $2,6$
- $5)$  $9,18$

## 样例 #1

### 输入

```
6
4 0
3 1
5 2
6 2
18 4
10000 3
```

### 输出

```
3
1
1
2
2
22
```

# 题解

## 作者：dfadfsafsdaf (赞：1)

题意

给你n次询问，每次给你一个x,y

然后让你输出，x这个数中的因子有多少个并没有在这个数的前y个数中出现过

题解：

对于每次询问，我们直接暴力统计因子个数

对于每一个因子，我们都记录一下这个因子最后出现在在什么时候，然后我们再判断是否ans++就好了

```cpp
#include<iostream>
#include<stdio.h>
#include<map>
using namespace std;

map<int,int> H;
int check(int x,int y,int z)
{

    int flag = 1;
    if(H[z]>=x-y)
        flag = 0;
    H[z]=x;
    //cout<<x<<" "<<y<<" "<<z<<" "<<flag<<endl;
    if(flag==0)
        return 0;
    return 1;
}
int main()
{
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        int ans = 0;
        for(int j=1;j*j<=x;j++)
        {
            if(x%j==0)
            {
                if(check(i,y,j))
                    ans++;
                if(x/j!=j)
                {
                    if(check(i,y,x/j))
                        ans++;
                }
            }
        }
        printf("%d\n",ans);
    }
}
```


---

## 作者：小杨小小杨 (赞：0)

## 题意
给你 $n$ 次询问，每一次给你两个数 $x$ 和 $y$，让你计算在 $x$ 的因子中，有多少个不存在 $x-y+1$ 到 $x-1$ 中的任意数？
## 思路
暴力。记录每一个的因子的最后出现位置，优化，那么时间复杂度就在许可范围内了。   
通过对最后一个位置的判断，也可以判断当前因子是否合法。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,ans,i,j;
map<int,int> ma;
bool pd(int x,int y,int z){
	if (ma[z]>=x-y) {ma[z]=x;return false;}//不成立也要保存
	ma[z]=x;//判断因子最后出现的位置
	return true;
}
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		ans=0;
		for (j=1;j*j<=x;j++)
			if (x%j==0){//取出因子
				ans+=pd(i,y,j);//累加
				if (x!=j*j) ans+=pd(i,y,x/j);//另一个因子
			}
		printf("%d\n",ans); 
	}
	return 0;
}

```


---

