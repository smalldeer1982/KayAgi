# Chessboard

## 题目描述

Magnus decided to play a classic chess game. Though what he saw in his locker shocked him! His favourite chessboard got broken into $ 4 $ pieces, each of size $ n $ by $ n $ , $ n $ is always odd. And what's even worse, some squares were of wrong color. $ j $ -th square of the $ i $ -th row of $ k $ -th piece of the board has color $ a_{k,i,j} $ ; $ 1 $ being black and $ 0 $ being white.

Now Magnus wants to change color of some squares in such a way that he recolors minimum number of squares and obtained pieces form a valid chessboard. Every square has its color different to each of the neightbouring by side squares in a valid board. Its size should be $ 2n $ by $ 2n $ . You are allowed to move pieces but not allowed to rotate or flip them.

## 样例 #1

### 输入

```
1
0

0

1

0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
101
010
101

101
000
101

010
101
011

010
101
010
```

### 输出

```
2
```

# 题解

## 作者：hgoicjl (赞：2)

## 题意&&翻译：

马格纳斯决定玩一个经典的国际象棋游戏。尽管他在储物柜里看到的东西震惊了他！他最喜欢的棋盘被分成了4块，每个棋盘的大小N总是奇数。更糟糕的是，有些正方形的颜色不对。第i排第j个数字为1表示该格子为黑色，0为白色。

现在马格纳斯想要改变一些方块的颜色，这样他就可以重新给最小的方块编号，使得相邻的方块颜色不同。其边长应为2n。**允许移动方块，但不允许旋转或翻转方块。** 求他最小需要改变方块的颜色数。

## 思路：
我们发现**n一定是奇数**，且棋盘不允许旋转或者翻转所以棋盘一定是下面两种形态之一

①
|0  |1  |0  |1  |...  |
| -----------: | -----------: | -----------: | -----------: | -----------: |
|1  |0  |1  |0  |...  |
|0  | 1 |  0|  1| ... |
|  1|  0|  1| 0 | ... |
|  ...| ... | ... | ... | ... |

②
|1  |0  |1  |0  |...  |
| -----------: | -----------: | -----------: | -----------: | -----------: |
|0  |1  |0  |1  |...  |
|1  | 0 |  1| 0| ... |
|  0|  1|  0| 1 | ... |
|  ...| ... | ... | ... | ... |

拼成的大棋盘两种情况如下所示

|  1|  0|  1|  .| 0 | 1 | 0 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 0 | 1 | 0 | . | 1 | 0 | 1 |
| 1 | 0 | 1 | . | 0 |1  |0  |
|  .| . | . | . |.  | . | . |
| 0 |  1| 0 |  .| 1 | 0 | 1 |
| 1 |0  |  1|  .| 0 | 1 | 0 |
| 0 | 1 | 0 | . | 1 | 0 | 1 |

即

|② | ① |
| -----------: | -----------: |
| ① | ② |

或是

|  0|  1| 0|  .| 1 | 0 | 1 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 0 | 1 | . | 0 | 1 | 0 |
| 0 | 1| 0 | . | 1 |0  |1 |
|  .| . | . | . |.  | . | . |
| 1 |  0|1 |  .| 0 | 1 | 0 |
| 0 |1  | 0|  .| 1 | 0 | 1 |
| 1 | 0 | 1| . | 0 | 1 | 0 |

即

| ① | ② |
| -----------: | -----------: |
| ② | ①|


~~当然两种棋盘是一样的~~，组合成一个大棋盘需要**每种形态各两个**

记录每个棋盘变成两种形态分别所需的代价（具体见代码注释）

通过枚举输出最小值即可

### AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//作者@hgoicjl
int main()
{
	int a,b[5][2]={0};//b[i][0]表示变为棋盘①所需的代价
	char k;
	cin>>a;
	for(int j=1;j<=4;j++)
		for(int i=1;i<=a*a;i++)
		{
			cin>>k;
			if(k=='0'+i%2)
//因为a是奇数，满足棋盘①输入的是01010101.....,棋盘②同理
				b[j][0]++;
//不满足棋盘①，则b[j][0]++，若满足棋盘①则不满足棋盘②，则b[j][1]++
			else
				b[j][1]++;
		}
	cout<<min(b[1][0]+b[2][0]+b[3][1]+b[4][1],
    	min(b[1][0]+b[3][0]+b[2][1]+b[4][1],
    	min(b[1][0]+b[4][0]+b[3][1]+b[2][1],
    	min(b[2][0]+b[3][0]+b[1][1]+b[4][1],
    	min(b[2][0]+b[4][0]+b[1][1]+b[3][1],
   	    b[3][0]+b[4][0]+b[1][1]+b[2][1])))));//求所有组合的最小代价
	return 0;	
}
```


---

## 作者：daklqw (赞：1)

分别计算出每个块转换成左上角是0或1的代价  
因为块边长是奇数，所以很容易发现四个矩阵中，肯定有两个做左上角是0，另外两个左上角是1  
那么枚举每个矩阵的左上角的不就好啦  
时间复杂度$O(n^2)$
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN 110
int n,f[2][4],map[MAXN][MAXN];
char buf[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0;i<4;++i){
		for(int j=1;j<=n;++j){
			scanf("%s",buf);
			for(int k=1;k<=n;++k)
				f[0][i]+=((j&1)^(k&1))^(buf[k-1]=='0'),
				f[1][i]+=((j&1)^(k&1))^(buf[k-1]=='1');
		}
	}
	printf("%d\n",
		min(f[0][0]+f[0][1]+f[1][2]+f[1][3],
		min(f[0][0]+f[1][1]+f[0][2]+f[1][3],
		min(f[1][0]+f[0][1]+f[0][2]+f[1][3],
		min(f[0][0]+f[1][1]+f[1][2]+f[0][3],
		min(f[1][0]+f[0][1]+f[1][2]+f[0][3],
		min(f[1][0]+f[1][1]+f[0][2]+f[0][3],
			0x7fffffff)))))));
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有一个国际象棋棋盘被分成了 4 块，每块大小 $n\times n(1\le n\le 100)$，$n$ 是奇数。$a_{k(i,j)}$ 表示第 $k$ 份在位置 $(i,j)$ 的颜色，1 表示黑色，0 表示白色。你需要求出最少修改多少位置，才能使得棋盘能够拼回成一个标准的国际象棋棋盘。(四块棋盘可以任意平移组合，但是不能旋转。)

## 思路1

由于 $n$ 为奇数，因此在这四块棋盘中，必定有两块是左上角为 0 的，另两块左上角必定为 1。这样才能拼成(大家自行画图理解)。

因此我们可以分块判断，分别计算出将此块变成左上角为 0 和 1 所需要改变的位置总数。若左上角为 0，则横纵坐标之和 $i+j$ (二维数组)或循环变量 $i$ (一维数组)为偶数时是 0，为奇数时是 1，否则总数加一。同理，若左上角为 1，则横纵坐标之和 $i+j$ (二维数组)或循环变量 $i$ (一维数组)为偶数时是 1，为奇数时是 0，否则总数加一。

然后将四块总共六种组合进行枚举，结果就是它们中的最小值。

## 代码1

接下来放上我的代码，这种方法输出较为麻烦。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[5][5];
char c[10005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int k=1;k<=4;k++){
	for(int i=0;i<n*n;i++){
	    cin>>c[i];
            b[k][0]+=(c[i]-'0'==i%2);
            b[k][1]+=(c[i]-'0'==(i+1)%2);
	}
    }
    cout<<min(b[1][0]+b[2][0]+b[3][1]+b[4][1],min(b[1][0]+b[3][0]+b[2][1]+b[4][1],min(b[1][0]+b[4][0]+b[3][1]+b[2][1],min(b[2][0]+b[3][0]+b[1][1]+b[4][1],min(b[2][0]+b[4][0]+b[1][1]+b[3][1],b[3][0]+b[4][0]+b[1][1]+b[2][1])))))<<endl;
    return 0;
}
```

## 思路2

棋盘一共四块，我们用
```cpp
next_permutation(u,u+4)
```
列出所有方案，将四块棋盘拼在一起，整体进行判断(判断方法与思路 1 相同)，用 $ans$ 存储答案。

## 代码2

下面放上代码，拼棋盘过程稍长些，输出很简单。
```cpp
#include<bits/stdc++.h>
using namespace std;
char in[4][105][105];
char cur[205][205];
int u[4];
int main() {
    int N, i, j, k;
    scanf("%d", &N);
    for (i = 0; i < 4; i++) for (j = 0; j < N; j++) scanf("%s", in[i][j]);
    for (i = 0; i < 4; i++) u[i] = i;
    int ans = INF;
    do {
	for (i = 0; i < 4; i++) {
	    for (j = 0; j < N; j++) for (k = 0; k < N; k++) cur[(i / 2)*N + j][(i % 2)*N + k] = in[u[i]][j][k];
	}
	int cnt = 0;
	for (i = 0; i < 2 * N; i++) {
	    for (j = 0; j < 2 * N; j++) {
		char c = '0' + (i + j) % 2;
		if (c != cur[i][j]) cnt++;
    	    }
	}
	ans = min(ans, cnt);
    } while (next_permutation(u, u + 4));
    return !printf("%d\n", ans);
}
```


---

## 作者：hswfwkj_ (赞：0)

## 题意简述：
有四个 $n\times n$ 矩阵，可以把它们拼成一个 $2n\times 2n$ 的矩阵，可以改变拼成的矩阵中的数字，使这个矩阵中的任意两个相邻的数字不同，求出最小的改变数字的次数。
## 思路：
第一眼，我们可以直接模拟啊！

我们模拟每一个新拼成的矩阵，然后新生成两个矩阵。

一个左上角为 $1$，另一个左上角为 $0$，然后扩展出一个相邻两个数都不同的矩阵。

我们对每一个拼成的矩阵，与这两个矩阵进行对比，看哪个需要的更改数字的次数最少。

最后在所有的拼成矩阵中选最小次数即可。

## 参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=INT_MAX;
char c[5][205][205];
int check_array[205][205];
int check(int x)
{
	int cnt=0;
	int w[205][205];
	for(int i=1;i<=2*n;i++)
		for(int j=1;j<=2*n;j++)
		{
			if((i+j)%2==0)w[i][j]=x;
			else w[i][j]=(x^1);
		}
   //生成矩阵
	for(int i=1;i<=2*n;i++)
		for(int j=1;j<=2*n;j++)
			if(w[i][j]!=check_array[i][j])
				cnt++;
   //将生成矩阵与拼成矩阵进行对比
	return cnt;
}
void ping(int x1,int x2,int x3,int x4)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			check_array[i][j]=c[x1][i][j]-'0';
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=2*n;j++)
			check_array[i][j]=c[x2][i][j-n]-'0';
	for(int i=n+1;i<=2*n;i++)
		for(int j=1;j<=n;j++)
			check_array[i][j]=c[x3][i-n][j]-'0';
	for(int i=n+1;i<=2*n;i++)
		for(int j=n+1;j<=2*n;j++)
			check_array[i][j]=c[x4][i-n][j-n]-'0';
   //拼成矩阵
	ans=min(ans,min(check(0),check(1)));	
   //记录答案
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int cnt=1;cnt<=4;cnt++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>c[cnt][i][j];
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++)
				for(int l=1;l<=4;l++)
					if(i!=j&&i!=k&&i!=l&&j!=k&&j!=l&&k!=l)
						ping(i,j,k,l);//四种循环枚举所有能拼成的矩阵
	cout<<ans;
	return 0;
}
```

---

