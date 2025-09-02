# Picking Up

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019-2/tasks/diverta2019_2_b

$ 2 $ 次元平面上に $ N $ 個のボールがあり、$ i $ 番目のボールは $ (x_i,\ y_i) $ にあります。

まず、$ p\ \neq\ 0 $ または $ q\ \neq\ 0 $ を満たす $ 2 $ つの整数 $ p,\ q $ を決め、その後以下の操作を繰り返してボールを全て回収します。

- 残っているボールを $ 1 $ つ選んで回収する。このボールの座標を $ (a,\ b) $ とする。この時、直前に選んだボールの座標が $ (a\ -\ p,\ b\ -\ q) $ である時コスト $ 0 $ 、そうでない時コスト $ 1 $ かかる。ただし、$ 1 $ つ目に選んだボールについては必ずコスト $ 1 $ かかる。

$ p,\ q $ を最適に選んだ場合にボールを全て回収するのにかかるコストの和の最小値を計算してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ |x_i|,\ |y_i|\ \leq\ 10^9 $
- $ x_i\ \neq\ x_j $ または $ y_i\ \neq\ y_j\ (i\ \neq\ j) $
- 入力は全て整数である

### Sample Explanation 1

$ p\ =\ 1,\ q\ =\ 1 $ とすると、$ (1,\ 1) $ のボール、$ (2,\ 2) $ のボールの順に選ぶことでコスト $ 1 $ でボールを全て回収することができます。

### Sample Explanation 2

$ p\ =\ -3,\ q\ =\ -2 $ とすると、$ (7,\ 8) $ のボール、$ (4,\ 6) $ のボール、$ (1,\ 4) $ のボールの順に選ぶことでコスト $ 1 $ でボールを全て回収することができます。

## 样例 #1

### 输入

```
2
1 1
2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 4
4 6
7 8```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 1
1 2
2 1
2 2```

### 输出

```
2```

# 题解

## 作者：Tsz1024_AK (赞：0)

### 题意解析
有 $n$ 个球，其坐标为 $(x_i,y_i)$，选定一个二元组 $(p,q)$ 满足 $p ≠ 0$，则进行以下操作：

每次选择一个 $a,b$，收集所有在坐标上 $(a-kp,b-kq)(k∈z)$ 的球，一共花费代价 $1$。求收集所有球所需最小代价。

数据范围：$n \le 100$。
### 题目思路
看到数据范围 $n \le 100$，就可以得知四重循环 $O(n^4)$ 都能过，那我们就按照题目意思模拟即可。此外，这道题可以使用结构体来存储变量，比较方便。

首先我们得出 $p,q$，接下来遍历一下每个点，求出它是否可被收集，最后统计答案即可。

我们可以根据题目描述先求出 $p,q$，代码如下：

```cpp
int p=arr[i].x-arr[j].x;
int q=arr[i].y-arr[j].y;
```

再定义两个变量 $xx,yy$ 来计算，代码如下：

```cpp
int xx=arr[k].x;
int yy=arr[k].y;
```

最后一重循环再根据条件判断一下即可，代码如下：

```cpp
if(xx+p==arr[t].x&&yy+q==arr[t].y){
    cnt=0;
    break;
}
```

其他地方还需要进行累加等简单运算，这里不再展示。

---

## 作者：Alvin0228 (赞：0)

### 题意描述

给出 $n$ 个点，每次收集 $(a−kp,b−kq)$ 上的点，求最少的收集次数。

### 题目分析

看到数据范围很小，我们可以使用较为朴素的做法。

首先我们求出 $p$ 和 $q$，然后对于每个点求出是否可被收集，最后统计答案即可。

需要注意的是，答案的初值不能设为 $+\infty$，要设为 $n$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[60][2];
int main ()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i][0]>>a[i][1];
	}
	int minn=n;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)//i，j枚举点的位置 
		{
			int q=a[i][1]-a[j][1],p=a[i][0]-a[j][0];
			if (q==0&&p==0) continue;//相当于i和j不相等 
			int ans=1;
			for (int k=1;k<=n;k++)//找起始点 
			{
				if (k==i) continue;
				ans++;
				for (int l=1;l<=n;l++)//找起始点可以触及到的点 
				{
					if (l==k) continue;
					if (a[k][0]+p==a[l][0]&&a[k][1]+q==a[l][1])
					{
						ans--;//少用一次
						break;
					}
				}
			}
			minn=min(minn,ans);
		} 
	}
	cout<<minn;
	return 0;
}

```

---

## 作者：Lvlinxi2010 (赞：0)

看到数据范围 $n \le 50$，考虑搜索。

枚举两个球 $i$，$j$ 的坐标，算出对应的 $p$，$q$，然后遍历所有的球求价值，取价值的最小值，时间复杂度 $O(n^4)$，时间限制两秒，可以通过本题。

附代码：
```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 50 + 10;
struct node{
    int x,y;
}a[MAXN];

int main(){
	int n;
    scanf("%d",&n);
    FL(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
    int minn=n;
    FL(i,1,n){
        FL(j,1,n){
            if(i==j) continue;
            int now=1;
            int p=a[i].x-a[j].x;
            int q=a[i].y-a[j].y;
            FL(k,1,n){
                if(k==i) continue;
                int cx=a[k].x;
                int cy=a[k].y;
                int tmp=1;
                FL(l,1,n){
                    if(l==k) continue;
                    if(cx+p==a[l].x&&cy+q==a[l].y){
                        tmp=0;
                        break;
                    }
                }
                now+=tmp;
            }
            minn=min(minn,now);
        }
    }
    printf("%d\n",minn);
    return 0;
}

```

---

