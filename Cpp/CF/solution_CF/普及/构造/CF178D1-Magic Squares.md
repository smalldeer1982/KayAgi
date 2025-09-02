# Magic Squares

## 题目描述

一只来自ABBYY的河狸喜欢智力游戏。他最喜欢的智力游戏之一是 “奇幻正方形” 。他想写一个程序来自动完成这个智力游戏。河狸决定让ABBYY杯的参赛者来帮他写这个程序。

 “奇幻正方形” 是一个 $n \times n$ 的矩阵，这个矩阵里面是整数。矩阵每行,每列和主对角线的数之和都等于 $s$ 。下面是一些例子：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178D1/df1aa6f903a3e44e4322a8498e9c3054e6afd786.png)

给出 $n^2$ 个数 $(a_1 \sim a_{n^2})$ ，要求把这些数放入一个大小为 $n \times n$ 的矩阵中，使它们形成一个 “奇幻正方形” 。注意，每个数必须在矩阵和原始数列中出现相同的次数。

保证输入数据有解。

## 说明/提示

对于 $20\%$ 的数据，保证 $1 \leq n \leq 3$ ；

对于 $50\%$ 的数据，保证 $1 \leq n \leq 4$ 且给出的 $n^2$ 个数中最多有 $9$ 个互不相同的数；

对于 $100\%$ 的数据，保证 $1 \leq n \leq 4$ 且 $-10^8 \leq a_i \leq 10^8$ ；

## 样例 #1

### 输入

```
3
1 2 3 4 5 6 7 8 9
```

### 输出

```
15
2 7 6
9 5 1
4 3 8
```

## 样例 #2

### 输入

```
3
1 0 -1 0 2 -1 -2 0 1
```

### 输出

```
0
1 0 -1
-2 0 2
1 0 -1
```

## 样例 #3

### 输入

```
2
5 5 5 5
```

### 输出

```
10
5 5
5 5
```

# 题解

## 作者：Fa_Nanf1204 (赞：1)

## 主要思路：dfs 和剪枝
### 分析
首先分析一下这道题的大致思路：我们可以用 dfs 来暴力枚举每个数的位置，并检查每种方案的可行性。


但是 $n=4$ 的时候，时间复杂度太高会超时，所以就有了剪枝的方法：当枚举到每一行或每一列或两条对角线的最后一个数字时，检查当前行或当前列或当前对角线上的数字的和是否合法，否则就跳出当前枚举。用这种方法就可以大大减少时间复杂度。
- - -
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,a[50],ans[10][10],f[50];
void dfs(int x,int y){
	if (x==sqrt(n) and y==sqrt(n)+1){ //判断是否可以输出答案 
		cout<<cnt<<endl;//出答案 
		for (int i=1;i<=sqrt(n);i++){
			for (int j=1;j<=sqrt(n);j++){
				cout<<ans[i][j]<<" ";
			}
			cout<<endl;
		}
		exit(0);
	}
	if (y>sqrt(n)){//边界 
		dfs(x+1,1);
		return ; 
	}
	for (int i=1;i<=n;i++){//枚举当前位置的数字 
		if (f[i]!=0) continue; //标记是否重复使用数字 
		if (y==sqrt(n)){//判断当前行的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[x][j];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n)){//判断当前列的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][y];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==1){//判断当前对角线的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][int(sqrt(n))-j+1];
			}
			if (sum!=cnt) continue;
		}
		if (x==sqrt(n) and y==sqrt(n)){//判断当前对角线的数字的和是否合法 
			int sum=a[i];
			for (int j=1;j<sqrt(n);j++){
				sum+=ans[j][j];
			}
			if (sum!=cnt) continue;
		}
		ans[x][y]=a[i];
		f[i]=1;//标记 
		dfs(x,y+1);
		f[i]=0;
	}
}
int main(){
	cin>>n;
	n=n*n;
	for (int i=1;i<=n;i++){
		cin>>a[i];//输入 
		cnt+=a[i];
	}
	cnt=cnt/sqrt(n);//求出合法的和的值 
	dfs(1,1);//搜索 
	return 0;
} 
```

---

## 作者：kimi0705 (赞：1)

因为数据范围是 $1\le n \le 4$ 所以采用 DFS 。
时间复杂度为 $O((n^2)! \times n)$（后面的 $n$ 是 check 函数的）,肯定超时。所以必须要剪枝优化。
可以做一下剪枝：
- 发现在每次一行/列算完后，可以剪枝因为如果这一行/列是错的，继续搜下去的话肯定是错的。
- 奇幻正方形的每行,每列和主对角线的数之和 $s$ 肯定是 $ \frac{\sum a_i}{n}$ , 因为每一行是一样的。
- 在 dfs 中，可以把每行/列的和加在一起，不用每次算一遍。

可以按照全排列去写，一定一定要注意优化。

code
```cpp
#include <iostream>
#include <climits>
#include <cmath>
#include <map>
#include <stack>
#include <queue>
#define int long long
using namespace std;
const int N = 100;
const int M = 5;
int n, m;
int arr[N];
int mp[M][M];
bool vis[N];
int sumh[M];
int suml[M];
bool check() {
	for (int i = 1; i <= n; i++) {
		if (sumh[i] != m)
			return 0;
		if (suml[i] != m)
			return 0;
	}
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; i++) {
		sum1 += mp[i][i];
		sum2 += mp[i][n - i + 1];
	}
	if (sum1 != m || sum2 != m)
		return 0;
	return 1;
}
void dfs(int x) {
	if (x > n * n) {
		if (check()) {
			cout << m << endl;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					cout << mp[i][j] << ' ';
				cout << endl;
			}
			exit(0);
		}
		return;
	}
	int nx = (x - 1) / n + 1, ny = (x - 1) % n + 1;
	for (int i = 1; i <= n * n; i++) {
		if (!vis[i]) {
			if (nx == n) {
				if (suml[ny] + arr[i] != m) {
					continue;
				}
			}
			if (ny == n) {
				if (sumh[nx] + arr[i] != m) {
					continue;
				}
			}
			sumh[nx] += arr[i], suml[ny] += arr[i], vis[i] = 1, mp[nx][ny] = arr[i];
			dfs(x + 1);
			sumh[nx] -= arr[i], suml[ny] -= arr[i], vis[i] = 0;
		}
	}
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n * n; i++)
		cin >> arr[i], m += arr[i];
	m /= n;
	dfs(1);
	return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

做题思路
--

我们可以用 DFS 暴力枚举每个数的位置，检查方案可行性，但这样做时间复杂度会很大，所以我们需要剪枝，如果现在就已经不合法了，那就没必要继续搜下去了，这样可以大大减少时间复杂度。

code:


```c
#include<bits/stdc++.h>
using namespace std;
int n,a[55],cnt,ans[15][15];
bool vis[55]; 
void dfs(int x,int y){
	if(sqrt(n)==x&&sqrt(n)+1==y){
		cout<<cnt<<"\n";
		for(int i=1;i<=sqrt(n);i++){
			for(int j=1;j<=sqrt(n);j++)cout<<ans[i][j]<<" ";
			cout<<"\n";
		}
		exit(0);
	}
	if(y>sqrt(n)){
		dfs(x+1,1);
		return;
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		if(y==sqrt(n)){//检查排 
			int sum=a[i];
			for(int j=1;j<int(sqrt(n));j++)
				sum+=ans[x][j];
			if(sum!=cnt)continue;
		}
		if(x==sqrt(n)){//检查列 
			int sum=a[i];
			for(int j=1;j<int(sqrt(n));j++)
				sum+=ans[j][y];
			if(sum!=cnt)continue;
		}
		if(x==sqrt(n)&&y==1){//对角线 
			int sum=a[i];
			for(int j=1;j<sqrt(n);j++)
				sum+=ans[j][int(sqrt(n))-j+1];
			if(sum!=cnt)continue;
		}
		if(x==sqrt(n)&&y==sqrt(n)){//对角线 
			int sum=a[i];
			for(int j=1;j<sqrt(n);j++)
				sum+=ans[j][j];
			if(sum!=cnt)continue;
		}
		ans[x][y]=a[i];
		vis[i]=1;
		dfs(x,y+1);
		vis[i]=0;
	}
}
signed main(){
	cin>>n;
	n*=n;
	for(int i=1;i<=n;i++)cin>>a[i],cnt+=a[i];
	cnt/=sqrt(n);
	dfs(1,1);
	return ((1-1)*4514);//皮一下
}
```

---

## 作者：Milthm (赞：0)

## CF178D1 题解

### 前置知识

- 搜索

### 题目解法

本题很明显是搜索，但是直接爆搜肯定过不了，所以考虑剪枝。

本题因为只是该题的第一个难度，所以剪枝思路很简单，只需要以下剪枝：

- 明显，$s=\frac{\sum{a_i}}{n}$，因为所有元素加起来刚好是 $n$ 个 $s$。

- 如果搜到一行、一列或一个对角线的末尾，发现这一行、列或对角线上面的元素之和不等于 $s$，那么肯定错了，就不要往下搜了。这个和可以用数组来维护。

本题只需要这两个剪枝即可通过，其它要点看注释。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int n,b[105],a[15][15],vis[105],maxn=-1e9,minn=1e9; 
long long sum,s,sum1[15],sum2[15],sum3,sum4; //记得开 ll
void dfs(int x,int y){
	if(x>n){//如果搜完了就输出
		cout<<s<<'\n'
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				cout<<a[i][j]<<" ";
			}
			cout<<'\n';
		}
		exit(0);
	}
	for(int i=1;i<=n*n;++i){//枚举所有元素
		if(!vis[i]){//如果没有被访问过
			int cnt=b[i]+sum1[y];
			if(x==n&&cnt!=s)continue; //如果搜到这一列的最后且不等于 s
			cnt=b[i]+sum2[x];
			if(y==n&&cnt!=s)continue;//如果搜到行的最后
			if(x==y){
				cnt=b[i]+sum3;	
				if(x==n&&cnt!=s)continue;//由左至右的对角线
			}
			if(x+y==n+1){
				cnt=b[i]+sum4;
				if(x==n&&cnt!=s)continue;//由右至左的对角线
			}
			a[x][y]=b[i];//记录
			vis[i]=1;//标记
			sum1[y]+=b[i];//更新
			sum2[x]+=b[i];
			if(x==y)sum3+=b[i];
			if(x+y==n+1)sum4+=b[i];
			if(y==n)dfs(x+1,1);
			else dfs(x,y+1);
			sum1[y]-=b[i];//回溯
			sum2[x]-=b[i];
			if(x==y)sum3-=b[i];
			if(x+y==n+1)sum4-=b[i];
			vis[i]=0;
			a[x][y]=0;
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n*n;++i)cin>>b[i],sum+=b[i],maxn=max(maxn,b[i]),minn=min(minn,b[i]);
	s=sum/n;//计算 s
	dfs(1,1);
	return 0;
}

```


---

