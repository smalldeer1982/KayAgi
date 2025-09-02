# [ABC015C] 高橋くんのバグ探し

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc015/tasks/abc015_3

高橋くんは上司からあるアンケートアプリにバグがあるかどうか調べて欲しいと頼まれました。

このアプリは、ユーザに選択肢が $ K $ 個ある質問を $ N $ 回答えさせることにより、ユーザの性格を判定します。 質問や選択肢はユーザの回答によって変わらず一定であり、ユーザは全ての質問にちょうど $ 1 $ つの選択肢を選ぶことで、結果を閲覧できます。

全ての選択肢はある整数値を持ちます。このアプリは、ユーザによって選ばれた、全ての回答がそれぞれ保持する整数値の排他的論理和（XOR）を使って結果を算出します。計算の最後でこの値が $ 0 $ になってしまうと、結果が表示されずバグが発生してしまいます。

あなたには全ての選択肢が持つ整数値が与えられるので、高橋くんの代わりに、ユーザの選択によってはバグが発生する可能性があるかどうかを判定してください。

## 说明/提示

### Sample Explanation 1

$ 1 $ つ目の質問で $ 1 $ つ目の選択肢を、$ 2 $ つ目の質問で $ 3 $ つ目の選択肢を、 $ 3 $ つ目の質問で、$ 2 $ つ目の選択肢を選んだとします。 すると、対応する数字はそれぞれ、 $ 1,2,3 $ となり、これらのXORを取ると、$ 0 $ となります。 よって、バグが発生してしまうため、`Found`と出力します。

### Sample Explanation 2

バグの発生する回答の組み合わせはありません。

## 样例 #1

### 输入

```
3 4
1 3 5 17
2 4 2 3
1 3 2 9```

### 输出

```
Found```

## 样例 #2

### 输入

```
5 3
89 62 15
44 36 17
4 24 24
25 98 99
66 33 57```

### 输出

```
Nothing```

# 题解

## 作者：_ouhsnaijgnat_ (赞：7)

这道题 $n\le,m\le5$，我一看，不就是搜索吗。

## 思路

这个 dfs 有两个参数，第一个是 $cur$ 用来表示第几组，第二个 $step$ 表示异或后的一个值。

每次 $cur$ 都加 $1$，因为表示第几组数嘛，再来一层循环，从 $1\backsim m$，因为不知道选哪一个数，所以枚举得到选哪一个数。

如果 $n$ 组数都选过来，并且 $step$ 等于 $0$，那么符合，返回 $1$。反之，返回 $0$。

代码奉上。

## 代码

```cpp
#include <iostream>
using namespace std;
int n,m,a[10][10];
int dfs(int cur,int step){
	if(cur>n){
		if(step==0)return 1;
		return 0;
	}
	for(int i=1;i<=m;i++){
		int q=dfs(cur+1,step^a[cur][i]);
		if(q)return q;
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	if(dfs(1,0))cout<<"Found\n";
	else cout<<"Nothing\n";
	return 0;
}
```


---

## 作者：liu100112 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc015_3)

## 我们先阅览一遍题目：
给定一个 $n$ 代表组数，一个 $m$ 代表一个组里面的元素个数，现从每组数中取出一个数，使取出的所有数的异或和为 $0$ 。

### 小知识：
异或：如果 $a$ , $b$ 两个值不相同，则异或结果为1。如果 $a$ , $b$ 两个值相同，异或结果为 $0$ 。
## 思路：
用 DFS 搜索，直到寻找到异或和 $0$ 的一组数，用一个 $f$ 存储是否存在。若存在输出  ```Found``` ，否则输出  ```Nothing``` 。

## 代码时间：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7;
int t[N][N],k=0,n,m,vis[N];//t用来存储每组中的每个数,vis用来判断这一组是否取过数,k用来存异或和
bool f=false;//存储是否存在
void dfs(int l){
	if(l==n+1&&k==0){//若找到异或和为0的一组
		f=true;
		return;
	}
	if(f) return;//若已找到，直接返回
	for(int i=1;i<=m;i++){
		if(!vis[l]){//若这一组还未取数
			int u=k;
			k^=t[l][i];
			vis[l]=1;
			dfs(l+1);
			vis[l]=0;
			k=u;
		}
	}
}
int main(){
	//输入
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>t[i][j];
		}
	}
	dfs(1);
	//判断是否存在
	if(f) cout<<"Found\n";
	else cout<<"Nothing\n";
	return 0;
}
```
最后还请管理员大大通过一下！

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc015_3)   
我刚看到这道题的第一眼：数论，位运算？！我都不擅长诶   
看了一眼数据范围：dfs！    
没错，这题就是 dfs。   
我们写一个 dfs，记录两个信息：当前异或的结果和 dfs 深度。   
在深度到 $n$ 的时候，就可以判断了。如果结果的值不是 $0$，就找下一层；如果是 $0$，就可以输出了。   
深度不是 $n$ 的时候，跑一遍深度对应的矩阵，都跑一次 dfs。   
CODE:   
```cpp
#include <iostream>
using namespace std;
int n,m,a[6][6];
bool dfs(int step,int ans){
	if(step==n&&ans==0){//dfs结束，结果为0
		return true;
	}else if(step==n&&ans){//dfs结束，结果不为0
		return false;
	}
	for(int i=0;i<m;i++){
		bool b=dfs(step+1,ans^a[step][i]);//跑dfs
		if(b){//如果存在就直接返回true
			return true;
		}
	}
	return false;//没有，返回false
}
int main(void){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}
	}
	cout<<(dfs(0,0)?"Found":"Nothing")<<endl;//输出
} 
```


---

