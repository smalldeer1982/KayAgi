# Group of Students

## 题目描述

有一些学生考了试，他们在考试中获得了$1$~$m$的分数，获得 i 分的有 $C_i$人。\
你需要求出一个分数线，满足低于分数线的人数和高于分数线(含)的人数均在$[x,y]$范围之内

## 样例 #1

### 输入

```
5
3 4 3 2 1
6 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
0 3 3 4 2
3 10
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
2 5
3 6
```

### 输出

```
0
```

# 题解

## 作者：Larryyu (赞：3)

## _Description_
给定 $m$ 个数 $c_1,c_2\dots c_m$，其中 $c_i$ 表示分数为 $i$ 的人有 $c_i$ 个。求一个数 $k$，使得 $\sum\limits_{i=k}^mc_i$ 及 $\sum\limits_{i=1}^{k-1}c_i$ 均在 $[x,y]$ 范围内。

保证$c_i$ 均为非负整数。

无解输出 $\texttt{0}$。
## _Solution_
看到一段数值的和，自然想到前缀和。

先遍历 $k$，如果两值均在范围内，则输出 $k$。

如果 $\sum\limits_{i=1}^{k-1}c_i>y$ 或 $\sum\limits_{i=k}^mc_i<x$，那么再继续遍历无意义，因为其中一个已经出了范围（前缀和单调递增，$c_i\ge0$），直接退出循环即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,x,y;
int a[110];
int sum[110];
int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];  //求前缀和
    }
    cin>>x>>y;
    for(int i=1;i<=m;i++){
        if(sum[i-1]>=x&&sum[i-1]<=y&&(sum[m]-sum[i-1])>=x&&(sum[m]-sum[i-1])<=y){  //满足条件
            printf("%d\n",i);
            return 0;
        }
        if((sum[m]-sum[i-1])<x||sum[i-1]>y){  //绝对不在范围内
            printf("0\n");
            return 0;
        }
    }
    printf("0\n");  //遍历完了也没有满足条件
    return 0;
}
```
#### _完结撒花！！_

---

## 作者：HadrianZhang (赞：0)

# 思路

本题可以用前缀和解决。设 $pre_i$ 表示分数小于等于 $i$ 的人数。

对于每个在 $1$ 到 $m$ 之间的分数 $i$，

低于该分数的人数：$pre_{i-1}$

高于或等于该分数的人数：$pre_m-pre_{i-1}$

只需判断这两个数是否在 $[x,y]$ 中即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],pre[105],x,y;
bool in(int p)
{
	return p>=x&&p<=y;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],pre[i]=pre[i-1]+a[i];
	cin>>x>>y;
	for(int i=1;i<=n;i++)
	{
		int p=pre[i-1],q=pre[n]-pre[i-1];
		if(in(p)&&in(q))
		{
			cout<<i;
			return 0;
		}
	}
	cout<<0;
	return 0;
} 
```

---

## 作者：happy_zero (赞：0)

### 思路
输入 $m$，$a_i$（$1 \le i \le n$)，$x$，$y$，由于题目要求“低于分数线的人数和高于分数线(含)的人数”求的是人数和，便想到用前缀和统计。我们用 $s_i$ 统计前 $i$ 分的学生共有多少人，要求分数线，我们可以依次遍历 $\left[1,m\right]$，每次用 $s$ 数组查询低于分数线的人数和高于分数线(含)的人数，如果在 $\left[x,y\right]$ 范围内便直接输出。

特别的，因为 $0 \le a_i$，所以 $s$ 数组一定是单调递增的。如果在某一分数线，低于分数线的人数大于 $y$，或者高于分数线的人数小于 $x$，那么再往下遍历只会使得低于分数线的人数越来越多，高于分数线的人数越来越少，不可能有符合条件的分数线，这时我们便直接跳出循环输出零即可。
#### 放上代码：
```
#include<bits/stdc++.h>
using namespace std;
int m,x,y;
int a[105],s[105];
int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
        //cout<<s[i]<<" ";
    }
    cin>>x>>y;
    for(int i=1;i<=m;i++){
        int minn=s[i-1],maxx=s[m]-s[i-1];
        if(minn>=x&&minn<=y&&maxx>=x&&maxx<=y){
            cout<<i<<endl;
            return 0;
        }
        if(minn>y||maxx<x)break;
    }    
    cout<<0<<endl;
    return 0;
}
```


---

## 作者：wdgm4 (赞：0)

这是一道大水题。

~~题目其实翻译得有点问题，但由于我英语不好，只能用百度翻译了。~~

------------
## 题意

有一些学生考了试，他们在考试中获得了 $1$ ~ $m$ 的分数，获得 $i$ 分的有 $C_i$ 人。
你需要求出一个分数线，满足低于分数线的人数和高于分数线(含)的人数均在 $[x,y]$ 范围之内。

## 输入格式
第一行一个整数，$m$；

第二行 $m$ 个整数，为 $C_1$~$C_m$；

第三行两个整数 $x,y$。

## 输出格式
(此为百度翻译)

如果不可能使每个结果组的大小最少为 $x$，最多为 $y$ 的方式选择通过率，请输出 $0$。否则，输出1到 $m$ 的整数 $-$ 您希望的通过率。如果有多个可能的答案，请输出其中任何一个。

------------

我用的是前缀和，这样求过分数线的人数和没过分数线的人数只需 $O(1)$ 的时间复杂度。求出后只需判断该分数线是否符合要求就行了。

其实题目要求的是输出任意符合要求的分数线，~~但题意翻译没说~~，所以我是直接输出第一个符合要求的分数线。

时间复杂度：$O(n)$。

------------
## code

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define yee 1919810

using namespace std;
int n,a[110],x,y;
int b[110];//前缀和 
int ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=b[i-1]+a[i];//计算前缀和 
	}
	cin>>x>>y;
	int l;//没过分数线的人数 
	int r;//过分数线的人数
	for(int i=1;i<=n;i++){
		l=b[i-1];
		r=b[n]-b[i-1];
		if(l<=y and l>=x and r<=y and r>=x){
			cout<<i<<endl;//由于是让输出任意一个，直接找到就输出
			return 0;
		}
	}
	cout<<"0";//运行到这里说明前面没有输出，那就输出0 
	return 0;
}

```


---

## 作者：Arvin2018 (赞：0)


捉到没人发题解的水题赶紧来一发2333

[题目传送门](https://www.luogu.org/problemnew/show/CF357A
)

---

## 题目大意：

有一些学生考了试，他们在考试中获得了 $1$ ~ $m$ 的分数，获得 $i$ 分的有 $C_i$ 人。

要求将他们以分数分成两组，一组是分数小于 $a$ 分的人，另一组是分数大于等于 $a$ 分的人。要求两组的人都不小于 $x$ 并且不大于 $y$ ，求 $a$ 的值。

## 输入格式

第一行一个整数 $m$ 。
第二行 $m$ 个整数，第 $i$ 个整数代表 $C_i$ 。
第三行两个整数，分别代表 $x$ 和 $y$ 。

## 输出格式

一行一个整数 $a$ 。

如果没有合适解，输出0。

---

按照题目模拟，先输入，再用循环找出 $a$ 。

解释在代码中qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int m;
	cin >> m;//输入
	int c[m+5];//c数组
	int cnt_b = 0, cnt_i = 0;//两个班的人数
	for(int i = 1; i <= m; i++){
		cin >> c[i];//输入每种分数的人数
		cnt_i += c[i]; //初始化
	}
	int x, y;
	cin >> x >> y;//输入x，y
	for(int i = 1; i <= m; i++){
		if(cnt_b >= x && cnt_b <= y && cnt_i >= x && cnt_i <= y){//如果满足条件不小于x和不大于y
			cout << i;//输出分数线
			return 0;//结束程序
		}
		cnt_b += c[i];//否则继续提高分数线
		cnt_i -= c[i];
	}
	cout << 0;//如果到最后都没有找到合适的分数线则输出0
	return 0;
}

```


---

