# Recover Polygon (easy)

## 题目描述

The zombies are gathering in their secret lair! Heidi will strike hard to destroy them once and for all. But there is a little problem... Before she can strike, she needs to know where the lair is. And the intel she has is not very good.

Heidi knows that the lair can be represented as a rectangle on a lattice, with sides parallel to the axes. Each vertex of the polygon occupies an integer point on the lattice. For each cell of the lattice, Heidi can check the level of Zombie Contamination. This level is an integer between $ 0 $ and $ 4 $ , equal to the number of corners of the cell that are inside or on the border of the rectangle.

As a test, Heidi wants to check that her Zombie Contamination level checker works. Given the output of the checker, Heidi wants to know whether it could have been produced by a single non-zero area rectangular-shaped lair (with axis-parallel sides). ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690B1/6a1d528b09269e46ea8342fade1ffbca11000e9c.png)

## 说明/提示

The lair, if it exists, has to be rectangular (that is, have corners at some grid points with coordinates $ (x_{1},y_{1}) $ , $ (x_{1},y_{2}) $ , $ (x_{2},y_{1}) $ , $ (x_{2},y_{2}) $ ), has a non-zero area and be contained inside of the grid (that is, $ 0<=x_{1}<x_{2}<=N $ , $ 0<=y_{1}<y_{2}<=N $ ), and result in the levels of Zombie Contamination as reported in the input.

## 样例 #1

### 输入

```
6
000000
000000
012100
024200
012100
000000
```

### 输出

```
Yes
```

# 题解

## 作者：xiazha (赞：4)

## 思路:暴力
因为此题数据很良心，$n\le50$ ，所以用 $(n^2)$ 的暴力方法是能过的，只需枚举每个点，如果不是就统计四面不是 $0$ 的个数，判断个数是否与本点的数一样即可，如果不一样，那整个数组都不合法，直接输出 No 然后停止运行就完事了。

另外，这里我是用字符读入的，大家也可以用数字读入，都行。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,nxt[4][2]={1,1,-1,-1,-1,1,1,-1};//nxt是用来控制方向的数组 
char a[55][55];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];//读入字符 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]=='0') continue;//不是大于0的数就跳过 
            int cnt=0;//定义计数变量 
            for(int k=0;k<=3;k++)//用循环判断周围的点是不是0 
                if(a[i+nxt[k][0]][j+nxt[k][1]]!='0')
                    cnt++;//计数++ 
            if(a[i][j]-'0'!=cnt)//a[i][j]-'0'是为了将字符转数字,方便判断 
            {
                cout<<"No";
                return 0;//有一个不合法就直接输出并且停止运行 
            }
        }
    cout<<"Yes";//都合法就输出Yes 
    return 0;//好习惯 
}
```


---

## 作者：wuyixiang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF690B1)

题目大意：判断是否所有的 $a_{i,j} \neq 0$，它的四角不等于 $0$ 的个数等于 $a_{i,j}$。

分析：暴力，直接判断四角，如果不等于直接退出即可。

## AC Code:

```cpp
#include <iostream>
using namespace std;
int n;
char a[555][555];
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= n;j ++)cin >> a[i][j];
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= n;j ++)
            if(a[i][j] != '0')
            {
                int ans = 0;
                if(a[i - 1][j - 1] != '0' && i > 1 && j > 1)ans ++;//左上
                if(a[i - 1][j + 1] != '0' && i > 1 && j < n)ans ++;//左下
                if(a[i + 1][j + 1] != '0' && i < n && j < n)ans ++;//右下
                if(a[i + 1][j - 1] != '0' && i < n && j > 1)ans ++;//右上
                if(ans != a[i][j] - '0')//判断
                {
                    cout << "No";
                    return 0;
                }
            }
    cout << "Yes";
}
```

---

## 作者：12345678hzx (赞：1)

## 题目大意
求矩阵 $a$ 是否合法。

如果对于每个 $a_{i,j}$，如果 $a_{i,j}\ne0$，则如果 $a_{i,j}$ 的四角的数不为 $0$ 的个数不等于 $a_{i,j}$，则称这个矩阵是不合法的。（越界不算）
## 思路
由于本题的 $n$ 很小，所以可以考虑遍历。

在此，为了代码的简洁，可以引用类似 BFS 时的方向数组。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,a[55][55],dx[5]={0,1,-1,1,-1},dy[5]={0,1,-1,-1,1}; 
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
    	char c;
    	cin>>c;
    	a[i][j]=c-'0';
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
		int sum=0;
		for(int k=1;k<=4;k++) sum+=a[i+dx[k]][j+dy[k]]!=0;
		if(sum!=a[i][j]&&a[i][j]!=0) {
			cout<<"No";
			return 0;
		} 
	}
	cout<<"Yes";
	return 0; 
}
```

---

## 作者：nj_peak (赞：0)

[返回题目 Recover Polygon (easy)](https://www.luogu.com.cn/problem/CF690B1)
# 题面翻译

求二维数组 $ a_{i,j}(0\leq i,j \leq n)$ 是否合法。

若 $a_{i,j} \neq0$，就求 $a_{i,j}$ 的四角中不越界且值不为 $0$ 的个数 $ans$，若 $a_{i,j} \neq ans$，则称二维数组 $ a_{i,j}$ 不合法。
# 思路
暴力。

因为 $5\le n\le20$，所以我们只用暴力遍历每一个数就可以了！

不知道为什么，我就是想加上类似 BFS 的方向数组（其实是因为不加上的话，没遍历会很难，懒得写）。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;

int n,s[4][2]= {1,1,-1,-1,-1,1,1,-1};
char a[N][N];

int main() {
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int ans=0;
			if(a[i][j]=='0') continue;
			for(int k=0;k<=3;k++){	
				if(a[i+s[k][0]][j+s[k][1]]!='0') ans++;
			}
			if(a[i][j]-'0'!=ans) {printf("No\n");return 0;}
		}
	}
	printf("Yes\n");
	return 0;
}
```


---

## 作者：LEle0309 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF690B1)

作为一名打完 CSP 后默默哭泣的蒟蒻，写一篇题解来安慰安慰自己……


#### 题目分析：

这题有绿？

思路：**暴力**（良心的数据范围：$ N \le 50 $）。

当 $ a_{i,j}=0 $ 时跳过。

然后统计出**四个角**（不是上下左右四个数）中非零数的个数，判断是否等于 $ a_{i,j} $ 即可。

如果不相等，则输出不合法，结束程序。

这里推荐使用搜索是用的行列偏移量来计算。

由于输入两数之间没有空格，这里采用字符类型进行存储。

```cpp
#include<iostream>
using namespace std;
const int maxn=5e1+3;
int dx[]={0,-1,-1,1,1};//行偏移量
int dy[]={0,-1,1,-1,1};//列偏移量
int n;char a[maxn][maxn];//字符型
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]=='0')continue;//我们要统计不为零的数
			int x=0;//非零数个数，注意赋初始值
			for(int t=1;t<=4;t++)
				if(a[i+dx[t]][j+dy[t]]!='0')x++;//统计个数
			if(a[i][j]-'0'!=x)//不满足
			{
				cout<<"No";
				return 0;
			}
		}
	cout<<"Yes";//合法数组
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# CF690B1 Recover Polygon (easy) 题解

## 思路
大水题一道，因为 $(n \le 50)$ 所以直接 $O(n^2)$ 判断就可以了，建议从 $1$ 开始存，数组开大 $1$ 这样越界的坐标也在数组内，值为 $0$ 不用特殊判断 ~~懒人一个~~。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
#define il inline
#define endl '\n'
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x<0?-x:x)
#define fast_io ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int maxn=52;
int n,a[maxn][maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	fast_io;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char ch;
			cin>>ch;
			a[i][j]=ch-'0';
		}
	}
	bool flag=true;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==0)
			{
				continue;
			}
			int cnt=0;
			if(a[i-1][j-1])
			{
				cnt++;
			}
			if(a[i-1][j+1])
			{
				cnt++;
			}
			if(a[i+1][j-1])
			{
				cnt++;
			}
			if(a[i+1][j+1])
			{
				cnt++;
			}
			if(cnt!=a[i][j])
			{
				flag=false;
			}
		}
	}
	cout<<(flag?"Yes":"No")<<endl;
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 题意
就给个二维数组啊，说只要 $a_{i,j}$ 不等于他四个角的 $0$ 的个数，就是“不合法”的，如果全都对就合法。

# 思路
数据水的离谱啊，$n \le 50$。


这 $n^4$ 怕不都过的了。

直接 $n^2$ 枚举，一个一个扫就好了。

只要四角的 $0$ 个数不等于 $a_{i,j}$，就错了，输出 ``No`` 就好了。如果都对就输出 ``Yes`` 就好啦。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int a[51][51]={},n;
string aa;
signed main(){
	cin>>n;
	f(i,1,n){
		cin>>aa;
		f(j,0,n-1){
            a[i][j+1]=aa[j]-'0';
        }
	}
	f(i,1,n){
		f(j,1,n){
			if(a[i][j]!=0){
				int u=0;
                u=(a[i-1][j-1]!=0)+(a[i-1][j+1]!=0)+(a[i+1][j-1]!=0)+(a[i+1][j+1]!=0);
				if(u!=a[i][j]){
					cout<<"No";
					return 0;
				}
			}
        }
    }
	cout<<"Yes";
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# Recover Polygon (easy)

## [题面](https://www.luogu.com.cn/problem/CF690B1)

## 思路

暴力做就完了。

遍历每一个点，按题目要求判断就行。

如果不合法，直接输出 ``No`` 结束程序就行。

最后输出 ``Yes`` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[55][55];
string s;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<n;j++) a[i][j+1]=s[j]-'0';
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]!=0){
				int tmp=0;
				if(a[i-1][j-1]!=0) tmp++;
				if(a[i-1][j+1]!=0) tmp++;
				if(a[i+1][j-1]!=0) tmp++;
				if(a[i+1][j+1]!=0) tmp++;
				if(tmp!=a[i][j]){
					printf("No");
					return 0;
				}
			}
	printf("Yes");
	return 0;
}

```

---

## 作者：xmkevin (赞：0)

这道题的 $n$ 只有 $50$，所以 $O(n^2)$ 的暴力是能过的。

对于 $a_{i,j}(0 \leq i, j \leq n)$，如果 $a_{i, j} ≠ 0$，那么我们只需判断它的四个角 $a_{i + 1, j - 1}, a_{i + 1, j + 1}, a_{i - 1, j - 1}, a_{i - 1, j + 1}$，然后用 $cnt$ 来计算其中不为 $0$ 且不越界的个数，如果 $cnt ≠ a_{i, j}$，那么直接输出 `No` 并退出程序，如果最后没有退出程序就是全部符合条件，输出 `Yes`。

P.S.

1、这里的 $a$ 数组需要先用字符串数组存，然后进行转换。

2、可以使用全局数组，利用初始值 $0$ 省去判断越界的代码。

代码如下：

```
#include <iostream>
using namespace std;
char b[55][55], a[55][55];
int n;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> b[i][j];
			a[i][j] = int(b[i][j] - '0');
		}
	}
	int flag = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(a[i][j]) {
				int cnt = 0;
				if(a[i - 1][j - 1] != 0) cnt++;
				if(a[i - 1][j + 1] != 0) cnt++;
				if(a[i + 1][j - 1] != 0) cnt++;
				if(a[i + 1][j + 1] != 0) cnt++;
				if(cnt != a[i][j]) {
					cout << "No\n";
					return 0;
				}
			}
		}
	}
	cout << "Yes\n";
}
```

---

## 作者：duchengjun (赞：0)

# 题意

求二维数组 $a$ 是否合法。

判断合法的方法：若 $a[i][j]\neq 0$，就求 $a[i][j]$ 的四角中不越界且值不为 0 的个数 $ans$，若 $a[i][j]\neq ans$ 则二维数组 $a$ 不合法。

# 分析

枚举每一个 $a[i][j]\neq 0$ 的点，判断合法即可。

运用方向数组，求个数即可。

方向数组可以化简代码，原来要写 4 个判断，现在只需要写一个循环就行了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[60][60];
int dir[4][2]={1,1,1,-1,-1,1,-1,-1};
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%1d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(a[i][j]==0)
				continue;
			int ans=0;
			for(int k=0;k<4;k++)
				if(a[i+dir[k][0]][j+dir[k][1]])
					ans++;
			if(a[i][j]!=ans){
				cout<<"No";
				return 0;
			}
		}
	cout<<"Yes";
	return 0;
}


```


---

## 作者：　　　吾皇 (赞：0)

#### 简述题意：

首先读入 $n$，表示一个二维数组 $S$ 的长度和宽度，然后读入这个二维数组 $S$。如果对于任意 $0 \le i \le n-1$，$0 \le j \le n-1$，有 $S_{i,j} \ne 0$ 且 $S_{i,j}$ 四个角不为 $0$ 的数量恰好等于 $S_{i,j}$ ，那么 $S$ 是合法的，输出 `Yes`。否则输出 `No`。

#### 分析：

暴力。

只要扫一遍这个数组，判断每个 $S_{i,j}$ 是否符合题意即可。注意如果从 $0$ 开始读可能越界，需要判断。这里可以使用方向数组简便代码。

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,s[51][51];
const int fx[]={1,1,-1,-1};
const int fy[]={-1,1,-1,1};//方向数组
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%1d",&s[i][j]);//scanf("%xd",&t) 表示读入x位。即不需要读入字符串再转换。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(s[i][j]==0) continue;//如果为0，那么无需判断。
			int sum=0;
			for(int k=0;k<4;k++) if(s[i+fx[k]][j+fy[k]]) sum++;//由于我是从1开始，设的是全局变量，所以即使在边界也无需担心sum会++。
			if(s[i][j]!=sum) return puts("No"),0;//如果不满足题意直接结束程序。
		}
	puts("Yes");
}
```


---

