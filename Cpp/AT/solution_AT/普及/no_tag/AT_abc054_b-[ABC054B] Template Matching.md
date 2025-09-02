# [ABC054B] Template Matching

## 题目描述

给定一个 $N$ 行 $N$ 列像素排成的图像 A 和 $M$ 行 $M$ 列像素排成的图像 B。这里像素是图像的最小单位，可以看作为 $1 \times 1$ 的正方形。

图像均为二进制图像，因此可以用白色和黑色这两种颜色来表示每个像素。在输入中，字符 `.` 表示白色像素，`#` 表示黑色像素。

图像 A 用 N 个字符串 $A_1,...,A_N$ 来表示。其中字符串 $a_i$ 的第 $j$ 个字符对应图像 A 中从上数第 $i$ 行，从左数 $j$ 列的像素。

同理图像 B 用 M 个字符串 $B_1,...,B_M$ 来表示。字符串 $b_i$ 的第 $j$ 个字符对应图像 B 中从上数第 $i$ 行，从左数 $j$ 列的像素。

当仅允许图像进行平行移动时，请判断图像 B 是否能被包含在图像 A 中。

## 说明/提示

### 数据范围
$1 \le M \le N \le 50$

### 样例解释 1

因为图像 B 与图像 A 中左上角的 $2 \times 2$ 子图像以及右下角的 $2 \times 2$ 子图像相匹配，所以输出 `Yes` 。

### 样例解释 2

由于图像 A 由白色像素组成，图像 B 由黑色像素组成，所以图像 A 不包含图像 B。

## 样例 #1

### 输入

```
3 2
#.#
.#.
#.#
#.
.#```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 1
....
....
....
....
#```

### 输出

```
No```

# 题解

## 作者：zhmzhuhanming (赞：1)

# [题目传送器](https://www.luogu.com.cn/problem/AT2328)

### 题意： $n*n$ 的 $A$ 图像中是否有 $m*m$ 的 $B$ 图像

本题数据不大，只有 $50 * 50$ ，所以就可以暴力枚举了。

本人呢是枚举 $A$ 看看那个位置是否与 $B$ 的右下角相同，如果是，再与 $B$ 整体核对。

好了，这就是本人的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
char a[200][200],b[200][200];//char!char!!!不要又int来了
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			cin>>b[i][j];
		}
	}
	for(int i=m;i<=n;i++){
		for(int j=m;j<=n;j++){      //如果是看右下角的话，那（1~m-1,1~m-1）是不用枚举的（枚举了还会越界）
			if(a[i][j]==b[m][m]){    //如果B的右下角与A的这个位置相同，就可以进行下一步核对
				bool o=1;
				for(int ii=1;ii<=m;ii++){
					for(int jj=1;jj<=m;jj++){
						if(b[ii][jj]!=a[i-m+ii][j-m+jj])o=0;//如果有不一样的就标记为不是
					}
				}
				if(o){		//如果有就可以直接输出了
					cout<<"Yes\n";
					return 0;
				}
			}
		}
	}
	cout<<"No\n";
	return 0;
}
```


---

## 作者：龙潜月十五 (赞：1)

## 一、题意

有两个矩阵 $A$ 和 $B$，问 $A$ 中是否存在一个子矩阵与 $B$ 相同。

## 二、思路

由于本题的范围 $n,m\leq 50$，因此我们可以直接 $O(n^4)$ 暴力枚举 $A$ 矩阵的点，将枚举的点作为左上角的点，再与 $B$ 矩阵比较是否相同即可。

## 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

void write(ll x) {
	 if(x < 0) {
		putchar('-');
		x = -x;
	 }
	 if(x > 9)
		write(x / 10);
	 putchar(x % 10 | 48);
}

const int N = 507;
int n, m;
char a[N][N], b[N][N];
bool flag;

int main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> a[i][j];
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			cin >> b[i][j];
			
	for(int i = 1; i <= n - m + 1; i++)
		for(int j = 1; j <= n - m + 1; j++) {
			flag = true;
			for(int k = i; k <= i + m - 1; k++)
				for(int l = j; l <= j + m - 1; l++)
					if(a[k][l] != b[k - i + 1][l - j + 1])
						flag = false;
			if(flag)
				return printf("Yes\n"), 0;
		}
	
	printf("No\n");
    return 0;
}


```


---

## 作者：achjuncool (赞：0)

[题目](https://www.luogu.com.cn/problem/AT2328)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-at2328)

## 题目大意

给定两个边长分别为 $n$ 与 $m$ 的正方形字符矩阵 $a$ 与 $b$，判断 $b$ 是否被包含在 $a$ 中。

## 解法

暴力即可。

首先两层循环遍历 $a$ 矩阵中一个边长为 $m$ 的正方形的左上角的坐标，然后两层循环检查是否与 $b$ 相同，如果有不相同就继续遍历，如果全部相同就直接输出 ```Yes``` 并退出程序，如果遍历完了仍没退出，说明 $b$ 没有被包含在 $a$ 中，输出 ```No``` 即可。

需要注意一个地方是，前两层遍历均从 $1$ 遍历到 $n-m+1$ 即可。

因为数据范围比较小，所以不会超时。

## Code

[AC](https://www.luogu.com.cn/record/83908170)

```cpp
#include <iostream>
using namespace std;
int n, m;
char a[55][55], b[55][55];
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++) cin >> b[i][j];
	for(int x = 1; x <= n - m + 1; x++){
		for(int y = 1; y <= n - m + 1; y++){
			bool flag = true; //flag 用于存储当前正方形是否与 b 相同
			for(int _x = 0; _x < m; _x++){
				for(int _y = 0; _y < m; _y++){
					if(a[x + _x][y + _y] != b[_x + 1][_y + 1]){
						flag = false;
						break;
					}
				}
				if(!flag) break;
			}
			if(flag){
				cout << "Yes" << endl;
				return 0;
			}
		}
	}
	cout << "No" << endl;
    return 0;
}
```


---

## 作者：Raych123 (赞：0)

## 思路：二维数组，先枚举B，再比较AB！！！！！！！！！！

注：既然各位大佬不屑于写这题题解，那本蒟蒻就来写一篇简单的了！

下面直接上AC代码！！！

源代码:

```
#include<bits/stdc++.h>//万能头文件（换别的也可以）

using namespace std;


int main()

{

int n,m;

scanf("%d%d",&n,&m);

char a[51][51],b[51][51];

for (int i=1;i<=n;i++)

{

    scanf("\n");//防止a[i][j]输入换行符

    for (int j=1;j<=n;j++)

    {

        scanf("%c",&a[i][j]);//输入A

    }

}

for (int i=1;i<=m;i++)

{

    scanf("\n");//和上面一样，防换行符占位

    for (int j=1;j<=m;j++)

    {

        scanf("%c",&b[i][j]);//输入B

    }

}

for (int x=1;x<=n-m+1;x++)

{

    for (int y=1;y<=n-m+1;y++)

    {

        bool ok=true;

        for (int i=1;i<=m;i++)//四角开始找！

        {

            for (int j=1;j<=m;j++)

            {

                if (b[i][j]!=a[x+i-1][y+j-1])

                {

                    ok=false;//此角没找到？？？！！！

                }

             }

        }

        if (ok)//找到了！！！

        {

            printf("Yes\n");

            return 0;//直接结束

        }

    }

}

printf("No\n");//还是没找到！！！

return 0;//完美结束

}
```

本蒟蒻第一次写代码，点个赞再走呗？

---

## 作者：FishingStar (赞：0)

这道题难度大概普及-，思想就是枚举b在a的左上角位置是什么，之后比较就可以了，复杂度最坏是 $O(n * n * m * m)$ 


------------
```
#include<cstdio>
#include<iostream>
using namespace std; 
char s[55][55];
char a[55][55];
int n, m;
int check(int x, int y){
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= m; j++){
            if(s[i + x - 1][j + y - 1] != a[i][j]){
                return 0;
			}
		}
	}
	return 1;
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
	    for(int j = 1; j <= n; j++){
	        cin >> s[i][j];
		}
	}
	for(int i = 1; i <= m; i++){
	    for(int j = 1; j <= m; j++){
	        cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n - m + 1; i++){
	    for(int j = 1; j <= n - m + 1; j++){
	        if(check(i, j) == 1){
	            cout << "Yes";
	            return 0;
			}
		}
	}
	cout << "No";
    return 0;
}
```


---

