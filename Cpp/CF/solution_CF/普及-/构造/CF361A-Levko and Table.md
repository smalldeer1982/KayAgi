# Levko and Table

## 题目描述

Levko loves tables that consist of $ n $ rows and $ n $ columns very much. He especially loves beautiful tables. A table is beautiful to Levko if the sum of elements in each row and column of the table equals $ k $ .

Unfortunately, he doesn't know any such table. Your task is to help him to find at least one of them.

## 说明/提示

In the first sample the sum in the first row is $ 1+3=4 $ , in the second row — $ 3+1=4 $ , in the first column — $ 1+3=4 $ and in the second column — $ 3+1=4 $ . There are other beautiful tables for this sample.

In the second sample the sum of elements in each row and each column equals $ 7 $ . Besides, there are other tables that meet the statement requirements.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
1 3
3 1
```

## 样例 #2

### 输入

```
4 7
```

### 输出

```
2 1 0 4
4 0 2 1
1 3 3 0
0 3 2 2
```

# 题解

## 作者：zhang_kevin (赞：9)

# 题意简述

给定 $n$ 和 $k$，你需要构造出一个长宽都是 $n$ 且每行每列的和都是 $k$ 的矩阵。

# 解题思路

题目要求每行每列的和要等于 $k$，最简单的思路就是每行每列**恰有一个** $k$，其余位置**均为** $0$。

换句话说，我们输出的矩阵要是这样的：

```
k 0 ··· 0 0
0 k ··· 0 0
·····k·····
0 0 ··· k 0
0 0 ··· 0 k 
```

观察矩阵，不难发现第 $(i,j)$ 个位置如果满足 $i = j$ 则值为 $k$，否则为 $0$。

这样，这道题的代码就呼之欲出了。

# AC 代码

```cpp
#include<cstdio>
int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i == j){
				printf("%d ", k);
			}else{
				printf("0 ");
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：REAL_曼巴 (赞：2)

此题是一道模拟题，让行列结果都一样。因题目要求低，不需要考虑重复情况。这就简单了许多。我们可以推出最简单的情况，没错，就是以下这个，对角线上放置数字和，其他地方全放零，避免影响结果。此题还要通过循环嵌套控制行列，得到位置输出。丑图献上！

![](https://cdn.luogu.com.cn/upload/image_hosting/zdjlha4x.png)

```cpp
#include <iostream>
using namespace std;
int n,k;//全局变量好习惯
int main (){
    cin>>n>>k;//输入
    for(int i=1;i<=n;i++){//通过循环嵌套控制行列
        for(int j=1;j<=n;j++){
            if(i==j)//得到对角线上的点
                cout<<k<<' ';//打印k
            else
                cout<<'0'<<' ';
            }
            cout<<endl;//结束一轮，换行别忘记
        }
    return 0;
}


```


---

## 作者：yuangq (赞：1)

我们发现将对角线上的数都设为k其他为数为0，就可以了

如
~~~
n=4  k=4
4 0 0 0
0 4 0 0
0 0 4 0
0 0 0 4
~~~

代码如下
~~~
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<climits>
#include<vector>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(i==j)
    		{
    			cout<<k;
    		}
    		else
    		{
    			cout<<0;
    		}
    		cout<<" ";
    	}
    	cout<<endl;
    }
    return 0;
}

~~~

---

## 作者：ttq012 (赞：1)

**Solution**

水题。

我们可以在每一行选择一个互不相同的位置，让这一个位置的值为 $k$，其他位置的值为 $0$。

通过生日悖论可以推出如果构造 $100$ 组不同的排列，基本上 $100\%$ 会有一组满足是幻方的排列了。

时间复杂度 $\mathcal O(100\cdot N^2)$。

**AC Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[10010];
int n, k;
bool check() {
    bool hang[122], lie[122];
    memset (hang, false, sizeof hang);
    memset (lie, false, sizeof lie);
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (a[i] == j) {
                if (hang[i] || lie[j])
                    return false;
                hang[i] = lie[j] = true;
            }
    return true;
}

signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) a[i] = i;
    for (int i = 1; i <= 100; i ++) {
        random_shuffle(a + 1, a + n + 1);
        if (!check())
            continue ;
        for (int i = 1; i <= n; i ++, puts(""))
            for (int j = 1; j <= n; j ++)
                if (a[i] == j)
                    printf ("%d ", k);
                else
                    printf ("0 ");
        break;
    }
    return 0;
}

```


---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
Levko 很喜欢幻方，他想构造一个长宽都是 $n$ 且每行每列的和都是 $k$ 的幻方，请你帮帮他.  
## $\text{Solution}$
每个 $(i,i)$ 的点填 $m$ 剩下全填 $0$ 即可.  
我写的是对角填 $m-n+1$ 其他地方填 $1$，但都是一个道理.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=25;
#define r rand()
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;

int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      if(i==j) printf("%d ",m-n+1);
      else printf("1 ");
    }
    putchar('\n');
  }
}

```


---

## 作者：zbk233 (赞：0)

## 解题思路

这道题中只要求了每行每列的和为 $k$，那么我们就可以先把整个矩阵放上 $0$，之后再把对角线上的数都变成 $k$ 就行了。

## 参考代码

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=n;j++)
			cout<<(i==j?k:0)<<' ';
	return 0;
}
```


---

## 作者：sunkuangzheng (赞：0)

### 思路

题目描述的已经很清楚了，那我们考虑如何去构造。

既然要构造一个每行每列的和都是 $k$ 的矩阵，我们考虑如下方案：

每行有且只有一个 $k$。这样首先每行的和为 $k$，而要做到每列的行也为 $k$，则需要使每行放置 $k$ 的位置都不重复。

显然可以按照以下方案放置 $k$：

（下表为 $n = 4$ 时的例子）

| $k$ | $0$ | $0$ | $0$ |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $k$ | $0$ | $0$ |
| $0$ | $0$ | $k$ | $0$ |
| $0$ | $0$ | $0$ | $k$ |

即当 $i = j$ 时输出 $k$，否则输出 $0$。

### 完整代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int main(){
    int n,k;
    cin >> n >> k;
    for(int i = 1;i <= n;i ++){
    	for(int j = 1;j <= n;j ++){
    		if(j == i){cout << k << " ";}
    		else {cout << "0 ";}
		 }
		 cout << "\n";
	}
	return 0;
}
```




---

## 作者：wssdl (赞：0)

新思路！！！

题目要满足每行每列和要等于 $K$ 。

那么最简单暴力的做法肯定就是每列填一个 $K$ ，并且同一行不能出现多个 $K$ 。

假设有一个 $4\times 4$ 的矩阵。

方案 $1$ ：

```cpp
K 0 0 0
0 K 0 0
0 0 K 0
0 0 0 K
```

方案 $2$ ：

```cpp
0 0 0 K
0 0 K 0
0 K 0 0
K 0 0 0
```

方案 $3$ ：

```cpp
0 K 0 0
K 0 0 0
0 0 0 K
0 0 K 0
```

当然还有很多方案，我们使用 方案 $1$ 。

我们可以定义一个数组 $a$ 来存结果，初始化为 $0$ ，然后我们发现这四个点依次为：

$1+0,1+0$

$1+1,1+1$ 

$1+2,1+2$

$1+3,1+3$

所以我们循环加数即可，范围是： $0\le i\le n-1$ ，把这几个点标为 $K$ 即可。 

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, k;
int a[N][N];  //main上面自动初始化为0
int main() {
  cin >> n >> k;
  for (int i = 0; i <= n - 1; i++) {  //循环加数
    a[1 + i][1 + i] = k;              //标为k
  }
  for (int i = 1; i <= n; i++) {  //输出
    for (int j = 1; j <= n; j++) {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
```

如果有笔误或不懂，请私信。

---

