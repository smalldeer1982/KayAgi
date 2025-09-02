# [ABC087C] Candies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc087/tasks/arc090_a

$ 2\ \times\ N $ のマス目があります。上から $ i $ 行目、左から $ j $ 列目 ($ 1\ \leq\ i\ \leq\ 2 $, $ 1\ \leq\ j\ \leq\ N $) のマスをマス $ (i,\ j) $ と表すことにします。

あなたははじめ、左上のマス $ (1,\ 1) $ にいます。 あなたは、右方向または下方向への移動を繰り返し、右下のマス $ (2,\ N) $ に移動しようとしています。

マス $ (i,\ j) $ には $ A_{i,\ j} $ 個のアメが置かれています。 あなたは移動中に通ったマスに置いてあるアメをすべて回収します。 左上および右下のマスにもアメが置かれており、あなたはこれらのマスに置かれているアメも回収します。

移動方法をうまく選んだとき、最大で何個のアメを回収できるでしょうか。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ A_{i,\ j}\ \leq\ 100 $ ($ 1\ \leq\ i\ \leq\ 2 $, $ 1\ \leq\ j\ \leq\ N $)

### Sample Explanation 1

以下のように移動するとき、回収できるアメの個数が最大となります。 - まず右に $ 3 $ 回移動する。その後下に $ 1 $ 回移動し、さらに右に $ 1 $ 回移動する。

### Sample Explanation 2

どのように移動しても回収できるアメの個数は同じになります。

## 样例 #1

### 输入

```
5
3 2 2 4 1
1 2 2 2 1```

### 输出

```
14```

## 样例 #2

### 输入

```
4
1 1 1 1
1 1 1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
7
3 3 4 5 4 5 3
5 3 4 4 2 3 2```

### 输出

```
29```

## 样例 #4

### 输入

```
1
2
3```

### 输出

```
5```

# 题解

## 作者：AubRain (赞：7)

下面的题解太麻烦，直接枚举从哪一步往下走即可

s[i][j] 是前缀和数组，记录第i行前j个的和

```cpp
#include<iostream>
using namespace std;
int n,s[3][105],x,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=2;i++)
        for(int j=1;j<=n;j++)
            cin>>x,s[i][j]=s[i][j-1]+x;
    for(int i=1;i<=n;i++)
        ans=max(ans,s[1][i]+s[2][n]-s[2][i-1]);
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：windrizzle (赞：1)

看到dalao们都用DP写这道题，萌新不得不弱弱地发声：“这难道不是一道DFS题吗？”

实际上，我认为这道题目就是赤裸裸的深度优先搜索！唯一要注意的是$n$为$0$的时候的特判。

$code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[41][101];
//bool f[41][41];
int maxx;
void dfs(int x,int y,int sum)
{
    if(x<1||x>2||y<1||y>n) return;
    if(x==2&&y==n) maxx=max(maxx,sum);//maxx取最大值
    if(x<2) dfs(x+1,y,sum+a[x+1][y]);//搜索
    dfs(x,y+1,sum+a[x][y+1]);
}
int main()
{
	//ios::sync_with_stdio(false);
	int i,j;
	cin>>n;
	for(i=1;i<=2;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	dfs(1,1,a[1][1]);
	cout<<maxx;//输出
    //system("pause");
	return 0;
}
```


---

## 作者：durbin中将 (赞：1)

这个状态转移方程就是：每一个位置ans[i][j]=左边或者上面的ans:ans[i-1][j]和ans[i][j-1]的最大值+这个数的值a[i][j]

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[510][510]={},ans[510][510]={};
int main()
{
	cin>>n;//输入有几列
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];//输入这个矩阵
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans[i][j]=max(ans[i-1][j],ans[i][j-1])+a[i][j];//状态转移方程
	cout<<ans[n][n]<<endl;//输出最终的答案
	return 0;//结束
}
```

---

## 作者：天启 (赞：0)

这题我使用深搜完成的，难度一般般

思路：读入数据后若n不等于1时dfs搜索最优解，等于1时直接相加输出答案就完
成了

时间复杂度算了一下，大概是O(n²)左右。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[101][101],n,b[101][101];
void dfs(int x,int y)
{
	long long s=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			b[i][j]=max(b[i-1][j],b[i][j-1])+a[i][j];//寻找最优解
		}
	} 
	cout<<b[n][n]<<endl;
    return;
}
int main()
{
	ios::sync_with_stdio(false);//输入输出加速
	cin>>n;
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	if(n==1) //若n==1时直接输出答案
	{
		cout<<a[1][1]+a[2][1];
		return 0;//结束程序
	}
	dfs(1,1);
}
```

---

## 作者：Kiel (赞：0)

这道题目让我想起了：

P1216 [USACO1.5]数字三角形 Number Triangles。

我是从左上角往右下角推的，其他思路和P1216差不多。

只是读入两行，只需要搜索两次，比 P1216简单很多

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100][100],f[100][100];
int main(){
    cin>>m;
    for(int i=1;i<=2;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    int i=1;
    f[1][1]=a[1][1];//叠加
    //上面第一层只需要无脑叠加，应为没有任何选择，但是还是要注意一下负数。
    for(int j=2;j<=m;j++){
        f[i][j]=max(f[i][j-1]+a[i][j],a[i][j]);
    }
    i=2;
    f[2][1]=f[1][1]+a[2][1]; //下面第一个只有从上面走，所以直接叠加。
    for(int j=2;j<=m;j++){
        f[i][j]=max(f[i-1][j]+a[i][j],f[i][j-1]+a[i][j]); //=max(f[i-1][j]+a[i][j],f[i][j-1]+a[i][j]);意思是f[i][j]=f[i-1][j]（上面一行）+上a[i][j]和f[i][j-1]（前面一行）+a[i][j]取出一个最大值。
    }
    //cout<<endl;
    cout<<f[2][m];//下标从1开始，要注意！
    return 0;
}
```

------------


---

