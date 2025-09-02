# Haar Features

## 题目描述

The first algorithm for detecting a face on the image working in realtime was developed by Paul Viola and Michael Jones in 2001. A part of the algorithm is a procedure that computes Haar features. As part of this task, we consider a simplified model of this concept.

Let's consider a rectangular image that is represented with a table of size $ n×m $ . The table elements are integers that specify the brightness of each pixel in the image.

A feature also is a rectangular table of size $ n×m $ . Each cell of a feature is painted black or white.

To calculate the value of the given feature at the given image, you must perform the following steps. First the table of the feature is put over the table of the image (without rotations or reflections), thus each pixel is entirely covered with either black or white cell. The value of a feature in the image is the value of $ W-B $ , where $ W $ is the total brightness of the pixels in the image, covered with white feature cells, and $ B $ is the total brightness of the pixels covered with black feature cells.

Some examples of the most popular Haar features are given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/3d348e10da05febca9a35d1c282ccc79140e13d5.png)Your task is to determine the number of operations that are required to calculate the feature by using the so-called prefix rectangles.

A prefix rectangle is any rectangle on the image, the upper left corner of which coincides with the upper left corner of the image.

You have a variable $ value $ , whose value is initially zero. In one operation you can count the sum of pixel values ​​at any prefix rectangle, multiply it by any integer and add to variable $ value $ .

You are given a feature. It is necessary to calculate the minimum number of operations required to calculate the values of this attribute at an arbitrary image. For a better understanding of the statement, read the explanation of the first sample.

## 说明/提示

The first sample corresponds to feature $ B $ , the one shown in the picture. The value of this feature in an image of size $ 6×8 $ equals to the difference of the total brightness of the pixels in the lower and upper half of the image. To calculate its value, perform the following two operations:

1. add the sum of pixels in the prefix rectangle with the lower right corner in the $ 6 $ -th row and $ 8 $ -th column with coefficient $ 1 $ to the variable $ value $ (the rectangle is indicated by a red frame); ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/2a4a67a2e1ced99b2d41037631914ffb613316f1.png)
2. add the number of pixels in the prefix rectangle with the lower right corner in the $ 3 $ -rd row and $ 8 $ -th column with coefficient $ -2 $ and variable $ value $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549D/f32eba3b14c07c0be2e93f2b2793934534ce56fc.png)

Thus, all the pixels in the lower three rows of the image will be included with factor $ 1 $ , and all pixels in the upper three rows of the image will be included with factor $ 1-2=-1 $ , as required.

## 样例 #1

### 输入

```
6 8
BBBBBBBB
BBBBBBBB
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
WBW
BWW
WWW
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6
WWBBWW
WWBBWW
WWBBWW
```

### 输出

```
3
```

## 样例 #4

### 输入

```
4 4
BBBB
BBBB
BBBB
BBBW
```

### 输出

```
4
```

# 题解

## 作者：_qingshu_ (赞：2)

# 题意：

给定一个 $ n \cdot m $ 的由 ```B``` 和 ```W``` 组成的目标矩阵，求至少经过多少次将 $(1,1)$ 到 $(x,y)$ 全部加上一个数的操作可以将初始全为 $0$ 的矩阵变成目标矩阵。

# 思路：

上面题意有部分与原文不一样，因为本题中 ```B``` 和 ```W``` 的具体取值是多少对于答案没有任何影响，所以可以直接将其看作一个不相等的任意值。

因为每一次操作会将 $(1,1)$ 到 $(x,y)$ 全部加上一个数，所以如果正序遍历前面的值会被覆盖导致不符，所以考虑倒序遍历也就是从 $(n,m)$ 到 $(1,1)$ 依次寻找当前矩阵和目标矩阵不匹配的点，将 $(1,1)$ 到 $(x,y)$ 全部加上该点与目标点的差就行了。

# 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int a[110][110];
int now[110][110];
void change(int x,int y,char flag){
	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			now[i][j]+=flag;
		}
	}
}
char k;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>k;
			a[i][j]=k;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(now[i][j]!=a[i][j]){
				change(i,j,a[i][j]-now[i][j]);
				ans++;
			}
		}
	}
	cout<<ans;
}
```

update：

23.12.20：修改了数字与中文之间无空格

---

## 作者：King_and_Grey (赞：1)

# [洛谷CF549D](https://www.luogu.com.cn/problem/CF549D)


## 题目简述

给定一个 $ n $ 行 $ m $ 列的由 $ B $ 和 $ W $ 组成的目标矩阵，求至少经过多少次将 $ (1,1) $ 到 $ (x,y) $ 全部加上一个数的操作可以将初始全为 $ 0 $ 的矩阵变成目标矩阵。

## 思路
我们不用管 $ B $ 和 $ W $，$ B $ 代表 $ -1 $，$ W $ 代表 $ 1 $，$ -1 $ 和 $ 1 $ 一个比 $ 0 $ 多 $ 1 $，一个比 $ 0 $ 少 $ 1 $，都差 $ 1 $ 。这题要求变化次数最少，我们可以从最后一位来枚举，若当前值不同于目标矩阵，则将 $ (n,m) $ 到  $ (1,1) $ 的每一个元素加上目标值与当前值之差，将该矩阵变为目标矩阵。
 
时间复杂度 $ O(n^2m^2) $，可以通过此题。

但是如果数据范围再大一些，就只能使用**二维线段树**或**二维树状数组**来进行区间处理[详见P4514。](https://www.luogu.com.cn/problem/P4514)


### 最后奉上AC代码（内有注释）


```cpp
#include <bits/stdc++.h>// 头文件你好，头文件再见
using namespace std;
#define int long long
#define AC return 0
const int N = 105;
int n,m,ans,a[N][N],now[N][N];
char s;
//定义修改函数
void Update(int x,int y,char flag){
	for(int i = 1; i <= x ; i++){
		for(int j = 1;j <= y; j++){
			now[i][j] += flag;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);// 加快cin和cout的速度，详见文章 https://www.luogu.com.cn/article/ugl00xfz
	cin >> n >> m;
	//输入
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> s;
			a[i][j] = s;
		}
	}
	for(int i = n; i >= 1; i--) { // 倒序判断
		for(int j = m; j >= 1; j--) {
			if(now[i][j] != a[i][j]) {
				Update(i,j,a[i][j] - now[i][j]); // 逐个修改,并记录
				ans++;
			}
		}
	}
	cout << ans << "\n";
	AC;
	//华丽收场
}
```

谢谢观看

---

## 作者：lgydkkyd (赞：1)

差点被绿题吓到了，后来发现其实可以用暴力的解法写，注意看数据：$n \le 100$，所以我们可以用最朴素的四层循环来解决这道题。

------------

但是为什么要从后往前遍历呢？因为正序遍历最大的问题在于覆盖，会把原本正确的答案覆盖掉，因此要倒着遍历。在遍历过程中如发现与该位置的目标不同，则进行修改，并累加答案，最后输出即可。

------------
```cpp
#include<bits/stdc++.h>//万能头最好啦 
#define int long long
using namespace std;
inline void read(int &a){
	a=0;
	char c;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') a=a*10+c-'0',c=getchar();
}
inline void write(int a){
	if(a>9)write(a/10);
	putchar(a%10+'0');
}
int n,m,ans,mb[101][101],cs[101][101];
char op;
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>op;
			if(op=='B')mb[i][j]=-1;
			if(op=='W')mb[i][j]=1;
		}
	}
	for(int i=n;i>=1;i--){//倒序遍历行 
		for(int j=m;j>=1;j--){//倒序遍历列 
			if(cs[i][j]!=mb[i][j]){//与目标不同 
				ans++;//操作次数累加 
				for(int k=1;k<=i;k++){
					for(int l=1;l<=j;l++){
						cs[k][l]+=(mb[i][j]-cs[i][j]);//修改矩阵 
					}
				}
			}
		}
	}
	write(ans);//输出答案 
	return 0;//华丽结束~~~
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

说实话，就这种题，不证明正确性等于白干。思路很简单啊，从右下向左上枚举，发现不同就将左上的全部更改。

但是，正确性存疑：如果出现这样三个坐标 $P(x_1,y_1),A(x_2,y_1),B(x_1,y_2)$，满足坐标本身合法且 $x_1<x_2,y_1<y_2$。这时候 $A,B$ 位置为 $B$，$C$ 位置为 $W$，那么先枚举 $A$ 和先枚举 $B$ 就会产生差别。

然而事实真的都是这样的吗？

并不是。这时候如果你对点 $O(x_2,y_2)$ 进行分讨的话，你就会发现这并无影响。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans[105][105], ant[105][105], cnt; char c;
inline void chg(const int& px, const int& py, const int& cv) {
	for (int i = px; i; i--)
		for (int j = py; j; j--)
			ant[i][j] += cv;
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			ans[i][j] = (cin >> c, c);
	for (int i = n; i; i--)
		for (int j = m; j; j--)
			if (ans[i][j] ^ ant[i][j])
				chg(i, j, ans[i][j] - ant[i][j]), cnt++;
	cout << cnt << endl;
	return 0;
}
```

---

## 作者：Lijunzhuo (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF549D)。
### 题意
给定一个二维数组，每次可以选定一个点，把它左上角的全部元素都加上一个相同的数，问使这个数组全变为 $0$ 的最小的操作数。
### 思路
这道题主要的难点在于如何处理操作后对之前点的影响。如果正着遍历，那么就会导致之前的点多次被修改，就不会变为 $0$。那就考虑倒着遍历，这样就不会出现对之前点的影响了。
### 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100;
int A[N][N],n,m,ans;
char c;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>c; //一定要用cin
			if(c=='B') A[i][j]=-1;
			else A[i][j]=1;
		}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
		{
			if(A[i][j]!=0)
			{
				int p=A[i][j];
				for(int x=1;x<=i;x++)
					for(int y=1;y<=j;y++)
						A[x][y]-=p;
				ans++;
			}
		}
	printf("%d\n",ans);
	return 0; 
}
```
[记录详情](https://www.luogu.com.cn/record/169740481)。
### 没必要的优化
每次操作的修改造成的时间复杂度太大了，我们可以考虑打标记，每次进行操作时只更新它相邻的左上角的元素，并打上标记。这样做可使时间复杂度大大减小。

---

## 作者：Tulip_ (赞：0)

### 题意

有一个 $n\times m$ 的目标矩阵是由 `B` 和 `W` 组成，问你至少多少次才可以将 $(1,1)$ 到 $(x,y)$ 全部加上一个数的操作可以将初始全为 $0$ 的矩阵变成目标矩阵。

### 思路

当我们理解意思后，你可能会思考怎么做。

但看范围 $1 \le n,m \le 100$，可以写暴力呀。

~~那这道题就是简单的水题啦！~~

但为了不用担心正确性，就从最后一位开始改变当前矩阵。

1. 将 `B` 改为 `-1`，`W` 改为 `1`。

2. 然后进行 $O(n^4)$ 的循环判断。

循环判断：从 $(1,1)∼(i,j)$ 时，判断 $(i,j)$ 的值是否与目标矩阵的 $(i,j)$ 是否相同，再给整个矩阵加值。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,z,ans;
int o[105][105],p[105][105];
char c;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='B')o[i][j]=-1;
			else o[i][j]=1;//第一步 
		}

	for(int i=n;i>=1;i--)//第二步 
		for(int j=m;j>=1;j--)
			if(p[i][j]!=o[i][j]){//循环判断 
				z=o[i][j]-p[i][j];
				for(int k=1;k<=i;k++)
					for(int l=1;l<=j;l++)p[k][l]+=z;
				ans++;
			}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

数据范围挺小，考虑暴力。

$O(nm)$ 枚举 $x,y$ 即可，然后暴力修改。注意要倒序枚举，否则会改变本来已经改好的值。

复杂度 $O(n^2m^2)$。

暴力代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,a[101][101],b[101][101];char c;
void update(int x,int y,int p){for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)b[i][j]+=p;}//修改
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>c,a[i][j]=(c=='W'?1:-1);//输入并赋值
    for(int i=n;i;i--)for(int j=m;j;j--)if(b[i][j]!=a[i][j])update(i,j,a[i][j]-b[i][j]),ans++;//与目标矩阵不符则需修改
    return cout<<ans,0;
}
```

若本题的数据再大一些，让 $O(n^2m^2)$ 的算法无法通过，则可以使用二维线段树或二维树状数组来进行区间加，复杂度 $O(nm\log(nm))$，可参照 P4514。

---

## 作者：MithrilSword_XIV (赞：0)

## 题目大意
对一个初始值全是 `0` 的矩阵，可以将 $(1,1)$ 到 $(x,y)$ 加上一个数，求最少次数改变为目标矩阵。

我们可以把 `B` 看作 `-1`，`W` 看作 `1`。

## 思路

做题首先看数据范围：$n,m \le 100$，故我们可以使用暴力方法来解决。

要求变化次数最少，我们可以从最后一位来枚举，每次判断目前矩阵的 $(i,j)$ 是否与目标矩阵的 $(i,j)$ 相等，如果不，则将目前矩阵的 $(1,1)$ 到 $(i,j)$ 都变化为目标矩阵的 $(i,j)$，即加上两数的差值。这样可以保证变化次数最少。

因为需要遍历比较矩阵并进行 $(1,1)$ 到 $(x,y)$ 的矩阵改变，所以时间复杂度为 $\mathcal{O}(n^4)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,End[105][105],change[105][105],ans,tmp;
char ch;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>ch;
            End[i][j]=(ch=='B'?-1:1);
        }
    }
    for(int i=n;i>=1;i--)//遍历
        for(int j=m;j>=1;j--){
            tmp=End[i][j]-change[i][j];
            if(change[i][j]!=End[i][j]){
                for(int x=1;x<=i;x++)for(int y=1;y<=j;y++)//(1,1)到(x,y)的矩阵加
                    change[x][y]+=tmp;
                ans++;
            }
        }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：wang_freedom (赞：0)

### 思路：
数据范围较小，所以考虑模拟。

从右下角开始，一直到左上角枚举 $(i,j)$，若当前值不同于目标矩阵，则将 $(1,1)$ 到 $(i,j)$ 的每一个元素加上目标值与当前值之差，将该矩阵变为目标矩阵。

时间复杂度为 $O(n^4)$，可以通过本题。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
ll n,m,ans;
int a[105][105],b[105][105];
char c;
void add(int u,int v,int k){
	rep(i,1,u)	
		rep(j,1,v)
			b[i][j]+=k;
}
signed main(){
	cin.tie(0);cout.tie(0);std::ios::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,n)
		rep(j,1,m){
			cin>>c;
			if(c=='B')
				a[i][j]=-1;
			else
				a[i][j]=1; 
		}
	per(i,n,1)
		per(j,m,1)
			if(b[i][j]!=a[i][j]){
				add(i,j,a[i][j]-b[i][j]);
				ans++;
			}
	cout<<ans;
	return 0;
}
/*

*/
```
[AC 记录](https://www.luogu.com.cn/record/125171992)

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF549D) $|$ 
[题目传送门](/problem/CF549D) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------
${\large\color{#00CD00}\text{题意}}$

一个 $n\times m$ 的矩阵，初始值都为 $0$，每次操作可以将矩阵中 $(1,1)$ 到 $(x,y)$ 的每个元素加上一个值（当然可以为负数），使得经过若干次操作后该矩阵变成给定的矩阵（其中的 $\tt B$ 表示 $-1$，$\tt W$ 表示 $1$），求最小的操作次数。

------------

${\large\color{#00CD00}\text{思路}}$

由于 $1 \le n,m \le 100$，因此可以考虑模拟。  
具体做法：**从右下角到左上角**依次枚举每一个 $(i,j)$，如果当前的值与目标矩阵中的值不相同，就将 $(1,1)$ 到 $(i,j)$ 的每一个元素加上目标值与当前值的差。最终该矩阵会变成目标矩阵。

不难看出该算法的时间复杂度为 $O(n^4)$，可以勉强通过此题。当然也可以使用二维树状数组等数据结构优化至 $O(n^2\log^2 n)$。~~（然而我懒得搞了）~~

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,cnt;
int a[105][105],b[105][105];
void add(int x,int y,int k)//将(1,1)到(x,y)加上k
{
	for(int i=1;i<=x;i++)
		for(int j=1;j<=y;j++)
			b[i][j]+=k;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>ch;
			if(ch=='B')a[i][j]=-1;
			else a[i][j]=1;
		}
	for(int i=n;i>=1;i--)//从右下角到左上角枚举
		for(int j=m;j>=1;j--)
		{
			if(b[i][j]!=a[i][j])
			{
				add(i,j,a[i][j]-b[i][j]);//加上目标值与当前值的差
				cnt++;
			}
		}
	cout<<cnt;
	return 0;
}
```

---

## 作者：_maple_leaf_ (赞：0)

### [luogu](https://www.luogu.com.cn/problem/CF549D)$\&$[原题链接](https://codeforces.com/problemset/problem/549/D)

## 题意
由于懒得写了，可以直接看[这位的](https://www.luogu.com.cn/article/zj8nx4no)题意

## 思路
- 首先我们可以发现，$n,m\le 100$，因此可以考虑暴力；
- 接着，我们可以从最后一位开始改变当前矩阵，由于后面在该遍矩阵时并不会改变当前这一位，因此不用担心正确性；
- 然后，我们在给从起点到当前位置的矩阵，即当前矩阵的 $(1,1)\sim(i,j)$,加值时，可以判断 $(i,j)$ 的值是否与目标矩阵的 $(i,j)$ 是否相同，再给整个矩阵加值；
- 最后，时间复杂度 $O(n^4)$，可以通过这道水题。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,e[114][514],qwq[114][514],ans;
char c;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			e[i][j]=(c=='B'?-1:1);赋值
		}
	}
	for(int i=n;i>=1;i--){开始枚举
		for(int j=m;j>=1;j--){
			if(qwq[i][j]!=e[i][j]){判断
				int t=e[i][j]-qwq[i][j];加的值
				for(int k=1;k<=i;k++){
					for(int l=1;l<=j;l++)qwq[k][l]+=t;
				}ans++;增加答案
			}
		}
	}cout<<ans<<endl;输出
	return 0;
}
```

---

