# [NWRRC 2015] Lucky Chances

## 题目描述

幸运机会是一种彩票游戏。每张彩票都有一个游戏区域和一个刮刮区。游戏区域是一个 $r \times c$ 的矩形区域，填满了数字。刮刮区隐藏了指定投注单元格的行号和列号。

有四种可能的获胜方向：上、下、左和右。如果从投注单元格开始的某个方向上的所有数字都严格小于投注单元格中的数字，那么你就赢得了这个方向。如果投注单元格位于网格的边缘，你将自动赢得相应的方向！

未刮开的票

刮开的票 1

刮开的票 2

拉里想选择一张在所有可能的投注单元格中获胜方向总数最多的票。编写一个程序来确定给定网格的这个数字。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 4
5 3 9 10
1 8 8 2
4 3 4 3
```

### 输出

```
25
```

# 题解

## 作者：柠檬布丁吖 (赞：3)

**Updata** 再次阅读完[题解攻略](https://studyingfather.blog.luogu.org/blog-written-guide)后对题解进行格式和代码注释的修改

一个名为幸运的机会的游戏，根据图片的提示，我们选择模拟。~~模拟大法好~~

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/2.png)

这篇题解主要讲一下这道题的细节。

1. 扫描某个方向是全是**严格小于**选择方块的数，等于的不算

2. **不是**方块所在的横或者列。

3. 可以选择方格某一方向（**当然不包括此方格**）逐个枚举，若有一个方块 $\geq$ 当前选择方块则此方向 pass 
 
2. 关于边界的处理，其实此题可以不做过多处理。

**ACCode:**

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m;
int Map[1100][1100];
//建议大家不要同“Map”这样设置变量名，容易让人产生歧义而想起STL中的map；希望大家可以避免错误。
int ans=0;//ans存储答案

int main() {

	cin>>n>>m;

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>Map[i][j];
		}
	}

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			bool k=false;
			for(int l=i-1; l>=1; l--) {
				if(Map[l][j]>=Map[i][j]) {
					k=true;
					break;
				}
			}
			if(k==false) {
				ans++;//某一方向达成条件
			} else {
				k=false;
			}


			for(int l=j-1; l>=1; l--) {
				if(Map[i][l]>=Map[i][j]) {
					k=true;
					break;
				}
			}
			if(k==false) {
				ans++;
			} else {
				k=false;
			}


			for(int l=i+1; l<=n; l++) {
				if(Map[l][j]>=Map[i][j]) {
					k=true;
					break;
				}
			}
			if(k==false) {
				ans++;
			} else {
				k=false;
			}


			for(int l=j+1; l<=m; l++) {
				if(Map[i][l]>=Map[i][j]) {
					k=true;
					break;
				}
			}
			if(k==false) {
				ans++;
			} else {
				k=false;
			}

		}
	}

	printf("%d\n",ans);

	return 0;
}
```


 _qwq蒟蒻第一次独立发题解祭祀_ 

---

## 作者：Gaogao2011 (赞：2)

### 题意

有一个叫 Lucky chances 的游戏，游戏给出 $r×c$ 的矩阵，任选一个元素，任选上、下、左、右中的一个方向，如果在这个方向上每个元素都小于所选元素，即为一种赢法。现求所有元素的能够使得你赢得游戏的方向的总和。~~题目翻译不错~~

### 思路

~~看着“普及-”标签直接枚举~~

根据题意，很容易想到枚举策略。

即遍历矩阵的每一个元素，检查该元素的上、下、左、右四个方向上的所有元素是否全部小于（且根据题意“严格小于”得知不能等于）该元素。

写代码时需要注意：在二维数组中某元素的上、下、左、右四个元素的表示。

比如，有二维数组 $a[100][100]$ 其中的一个元素为 $a[i][j]$。

则数组元素 $a[i][j]$ 的上、下、左、右四个方向的**第一个**元素分别为：

$a[i+1][j]$、$a[i-1][j]$、$a[i][j-1]$、$a[i][j+1]$。

在写代码时根据上述方向遍历、比较即可。

### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 107;
int a[MAXN][MAXN];
int main() {
	int r, c, sum = 0;
	scanf("%d%d", &r, &c);
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			bool flag = true;
			for (int k = i + 1; k <= r; k++) {
				if (a[k][j] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag == true) sum = sum + 1;
			else flag = true;
			for (int k = i - 1; k >= 1; k--) {
				if (a[k][j] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag == true) sum = sum + 1;
			else flag = true;
			for (int k = j + 1; k <= c; k++) {
				if (a[i][k] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag == true) sum = sum + 1;
			else flag = true;
			for (int k = j - 1; k >= 1; k--) {
                if (a[i][k] >= a[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag == true) sum = sum + 1;
            else flag = true;
		}
	}
	printf("%d\n", sum);
	return 0;
}


```

直接复制可AC，但建议重新照着思路敲一遍。

~~我不会写快读那就不写 反正没必要~~


---

## 作者：Eason_AC (赞：2)

## Content
有一个名叫 Lucky chances 的游戏，游戏一开始给出一个 $r\times c$ 的矩阵，你可以选定矩阵中任意一个元素以及上、下、左、右四个方向中的任意一个方向进行游戏。如果这个方向上的任意一个元素都**严格小于**所选的元素，那么你就赢了。

试求出所有元素的能够使得你赢得游戏的方向的总和。

**数据范围：$1\leqslant r,c\leqslant 100$，矩阵内的每个元素不超过 $1000$。**
## Solution
我们直接每个方向直接模拟，看能否赢得游戏，能的话就把它加入到答案里面。
## Code
```cpp
int r, c, a[107][107], ans;

int main() {
	r = Rint, c = Rint;
	F(i, 1, r) F(j, 1, c) a[i][j] = Rint;
	F(i, 1, r) F(j, 1, c) {
		int flag = 1;
		R(k, i - 1, 1) if(a[k][j] >= a[i][j]) {flag = 0; break;}
		ans += flag, flag = 1;
		F(k, i + 1, r) if(a[k][j] >= a[i][j]) {flag = 0; break;}
		ans += flag, flag = 1;
		R(k, j - 1, 1) if(a[i][k] >= a[i][j]) {flag = 0; break;}
		ans += flag, flag = 1;
		F(k, j + 1, c) if(a[i][k] >= a[i][j]) {flag = 0; break;}
		ans += flag;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Struggle_ong (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7059)

### 题目大意：

有一个叫 Lucky chances 的游戏，游戏给出 $ r\times c $ 的矩阵，任选一个元素，任选上、下、左、右中的一个方向，如果在这个方向上每个元素都小于所选元素，即为一种赢法。现求所有元素的能够使得你赢得游戏的方向的总和。

### 解决：

直接枚举每个元素，每个方向，判断即可。将符合的加到 $ ans $ 中。

#### 代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
using namespace std;
inline int read()
{
	int s=0,w=-1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*w;
}
const int N=1e2+10;
int a[N][N];
int main()
{
    int r=read(),c=read(),ans=0;
    for(int i=1;i<=r;i++)
     for(int j=1;j<=c;j++)
      a[i][j]=read();
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            int f=1;
            for(int k=i+1;k<=r;k++)if(a[k][j]>=a[i][j]){f=0;break;}
            if(f)ans+=1;
            f=1;
            for(int k=i-1;k>=1;k--)if(a[k][j]>=a[i][j]){f=0;break;}
            if(f)ans+=1;
            f=1;
            for(int k=j+1;k<=c;k++)if(a[i][k]>=a[i][j]){f=0;break;}
            if(f)ans+=1;
            f=1;
            for(int k=j-1;k>=1;k--)if(a[i][k]>=a[i][j]){f=0;break;}
            if(f)ans+=1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
~~直接提交源代码有惊喜！~~

---

## 作者：andyli (赞：1)

枚举每个点，分别向四个方向遍历判断每个方向上的任意一个元素是否都严格小于当前的元素，如果满足则累加答案。
```python
(n, m), *a = [[*map(int, s.split())] for s in open(0)]
ans = 0
for i in range(n):
    for j in range(m):
        ans += all(a[k][j] < a[i][j] for k in range(i)) # 左 
        ans += all(a[k][j] < a[i][j] for k in range(i+1, n)) # 右
        ans += all(a[i][k] < a[i][j] for k in range(j)) # 上
        ans += all(a[i][k] < a[i][j] for k in range(j+1, m)) # 下
print(ans)

```

---

## 作者：Igallta (赞：0)

题意：给你一个 $r\times c$ 的棋盘，跟你说：任取一个元素 $a_{i,j}$ 你要保证他的上下左右的元素都比它小，然后就算一种赢法，现求所有元素的能够使得你赢得游戏的方向的总和。

首先，我们看数据范围：$1\leqslant r,c \leqslant 100$，我们直接想到枚举。

整理思路：$a_{i,j}$ 的上下左右分别是 $a_{i-1,j}$，$a_{i+1,j}$，$a_{i,j-1}$，$a_{i,j+1}$。我们就判断他们是否小于 $a_{i,j}$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 101;
int a[MAXN][MAXN],r,c,sum;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>r>>c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin>>a[i][j];
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			bool flag = true;
			for (int k = i + 1; k <= r; k++) {
				if (a[k][j] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag)++sum;
			else flag = true;
			for (int k = i - 1; k >= 1; k--) {
				if (a[k][j] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag)++sum;
			else flag = true;
			for (int k = j + 1; k <= c; k++) {
				if (a[i][k] >= a[i][j]) {
					flag = false;
					break;
				}
			}
			if (flag)++sum;
			else flag = true;
			for (int k = j - 1; k >= 1; k--) {
                if (a[i][k] >= a[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag)++sum;
            else flag = true;
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：xiaoming007 (赞：0)

## 思路

还是说一说细节吧：

- 首先一定是**严格小于的**，并不是小于等于。

- 如果所选方格在边界上且所选方向进行遍历一个数字都没有，也算一种方法。

剩下直接按题意枚举每一个点及方向便可以，复杂度不会超时。

## 代码

```cpp
#include <iostream>
using namespace std;
int a[1010][1010], n, m;
bool up(int i, int j){
    for(int k = i-1; k >= 1; --k){
        if(a[k][j] >= a[i][j]) return 0;
    }
    return 1;
}
bool down(int i, int j){
    for(int k = i+1; k <= n; ++k){
        if(a[k][j] >= a[i][j]) return 0;
    }
    return 1;
}
bool left(int i, int j){
    for(int k = j-1; k >= 1; --k){
        if(a[i][k] >= a[i][j]) return 0;
    }
    return 1;
}
bool right(int i, int j){
    for(int k = j+1; k <= m; ++k){
        if(a[i][k] >= a[i][j]) return 0;
    }
    return 1;
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            ans = ans + up(i, j) + down(i, j) + left(i, j) + right(i, j);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Trump__Biden (赞：0)

### [传送门](https://www.luogu.com.cn/problem/P7059)

### 题意：
如果一个元素上、下、左、右四个方向中**任意**一个方向上**任意**一个数**严格小于**该元素，则赢。

### 思路：
直接枚举该元素所处的横行、竖列，进行判断。如果不符合条件则记标记为假。如果枚举完某一行或列后，符合条件，标记为真，则答案加一，再将标记还原成真，然后继续枚举，直至枚举完整个矩阵。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,ans,a[110][110];
bool flag;
int main(){
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			flag=true;
			for(int q=i+1;q<=r;++q){
				if(a[q][j]>=a[i][j]){
					flag=false;
				}
			}
			if(flag==true){
				ans++;
			}
			flag=true;
			for(int q=i-1;q>=1;--q){
				if(a[q][j]>=a[i][j]){
					flag=false;
				}
			}
			if(flag==true){
				ans++;
			}
			flag=true;
			for(int q=j-1;q>=1;--q){
				if(a[i][q]>=a[i][j]){
					flag=false;
				}
			}
			if(flag==true){
				ans++;
			}
			flag=true;
			for(int q=j+1;q<=c;++q){
				if(a[i][q]>=a[i][j]){
					flag=false;
				}
			}
			if(flag==true){
				ans++;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：ljm1621 (赞：0)

模拟水题，建议评橙。

# 思路

输入不用说：

```cpp
for(int i=1;i<=r;i++)
{
    for(int j=1;j<=c;j++)
    {
        cin>>a[i][j];
    }
}
```

输入后，循环枚举上下左右四个方向，如果在循环中没有把flag赋值为false并break的话就把最后的答案加$1$。最后输出答案即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105][105];
int main()
{
    int r,c,sum=0;
    cin>>r>>c;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            bool flag=true;
            for(int k=i+1;k<=r;k++)
            {
                if(a[k][j]>=a[i][j])
                {
                    flag=false;
                    break;
                }
            }
            if(flag)    sum+=1;
            flag=true;
            for(int k=i-1;k>=1;k--)
            {
                if(a[k][j]>=a[i][j])
                {
                    flag=false;
                    break;
                }
            }
            if(flag)    sum+=1;
            flag=true;
            for(int k=j+1;k<=c;k++)
            {
                if(a[i][k]>=a[i][j])
                {
                    flag=false;
                    break;
                }
            }
            if(flag)    sum+=1;
            flag=true;
            for(int k=j-1;k>=1;k--)
            {
                if(a[i][k]>=a[i][j])
                {
                    flag=false;
                    break;
                }
            }
            if(flag)    sum+=1;
        }
    }
    cout<<sum<<endl;
    return 0;
}
```

[亲测AC](https://www.luogu.com.cn/record/45978653)


---

## 作者：yxy666 (赞：0)

题意：给我们一个 $r*c$ 的矩阵，然后我们可以任意选择一个点，看一下四个方向是否全是比我小的数，如果是，那我就赢了。问我们最多能赢的次数。

思路：很明显，我们可以枚举一个点，然后再枚举一个方向，再接下来我们就可以一路扫过去，判断一下是否都是小于的。如果都是小于的话那就答案累加。否则就换个方向或位置继续。时间复杂度为 $O(r*c*max(r,c)*4)$ ，$4*10^6$,妥妥的解下来了。

$code $ :
```cpp
#include<bits/stdc++.h>//0->  1<-  2↑3↓
using namespace std;
const int maxn=105;
int f[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
int n,m,Ans,a[maxn][maxn];
bool flg; 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
void bfs(int x,int y,int k){
	if(k==0){for(int j=y+1;j<=m;j++)if(a[x][j]>=a[x][y]){flg=1;break;}}
	else if(k==1){for(int j=1;j<y;j++)if(a[x][j]>=a[x][y]){flg=1;break;}}
	else if(k==2){for(int i=1;i<x;i++)if(a[i][y]>=a[x][y]){flg=1;break;}}
	else if(k==3){for(int i=x+1;i<=n;i++)if(a[i][y]>=a[x][y]){flg=1;break;}}
	Ans+=!flg;flg=0;
}//从这个方向遍历过去，如果有符合题目描述的，Ans++
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)a[i][j]=read();//输入
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)//枚举点
	for(int k=0;k<4;k++)bfs(i,j,k);//枚举方向+遍历
	printf("%d\n",Ans);//输出
	return 0;
} 
```


---

