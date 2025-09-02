# Subtangle Game (Easy Version)

## 题目描述

这是问题的简单版本。两个版本的区别在于所有变量的约束。只有当两个版本的问题都解决时，才能进行 Hack。

Tsovak 和 Narek 正在玩一个游戏。他们有一个整数数组 $a$ 和一个整数矩阵 $b$，矩阵有 $n$ 行 $m$ 列，行列编号从 1 开始。矩阵中第 $i$ 行第 $j$ 列的单元格为 $ (i, j) $。

他们轮流在矩阵中寻找数组 $a$ 的元素；Tsovak 先开始。每次轮到玩家时，玩家需要在矩阵中寻找当前数组 $a$ 中的元素（Tsovak 寻找第一个，Narek 寻找第二个，依此类推）。假设某个玩家选择了单元格 $ (r, c) $。下一个玩家必须在从 $ (r + 1, c + 1) $ 开始、以 $ (n, m) $ 结束的子矩阵中选择他的单元格（如果 $r = n$ 或 $c = m$，子矩阵可能为空）。如果某个玩家无法在这样的子矩阵中找到相应的单元格（或者剩余的子矩阵为空），或者数组已经结束（前一个玩家已经找到了最后一个元素），那么他就输了。

你的任务是确定如果两位玩家都进行最优策略时，谁会获胜。

## 说明/提示

在第一个例子中，Tsovak 首先寻找 $ 1 $ 。矩阵中 $ 1 $ 只出现在 $ (1,1) $，所以他选择该位置。接着，Narek 需要在子矩阵 $ (2, 2) $ 中寻找 $ 2 $，该子矩阵只包含最后两个元素：$ 5 $ 和 $ 2 $。他选择 $ 2 $，随后 Tsovak 输了，因为数组已经结束。

在第二个例子中，Tsovak 需要选择 $ 1 $ 。$ 1 $ 出现在矩阵的最后一个单元格 $ (n,m) $，他选择了该单元格。由于子矩阵 $ (n+1, m+1) $ 为空，Narek 无法找到 $ 2 $，所以他输了。

Translate by 宋怡芃

## 样例 #1

### 输入

```
3
2 2 3
1 2
1 3 5
4 5 2
2 2 4
1 2
1 1 3 2
4 2 5 1
2 4 2
1 2
3 4
5 5
5 5
5 5```

### 输出

```
N
T
N```

# 题解

## 作者：MrPython (赞：4)

这个真不值 2000 吧！

经典线性 dp。考虑 $f_{k,i,j}$ 表示第 $k$ 轮时当前玩家选择 $(i,j)$ 是否可以获胜。

第 $l+1$ 轮时该选手将直接失败，因此 $f_{l+1}$ 全部初始化为 `false`。

然后倒着从后往前转移。考虑 $f_{k,i,j}$，如果下一轮的选手下在右下方的任意一点可以获胜，则下在当前点是必败的，为 `false`，否则为 `true`。

转移的时候维护个后缀或数组，边转移边算，这样复杂度就是 $O(lnm)$ 的了。

---

## 作者：Michael1234 (赞：3)

- 本题可以使用**动态规划**的思路：

- 我们考虑倒着推**取到 $a$ 序列的第几个**，并从 $(n,m)$ 反推至 $(1,1)$。

- 可以由此设计状态 $dp_{k,i,j}$，表示当前玩家取到 $a_k$，选择 $b_{i,j}$ 是否必胜。

- 推出状态转移方程：在 $b_{i,j}=a_k$ 的情况下

$$dp_{k,i,j}=[(\sum_{x=i+1}^{n}{ \sum_{y=j+1}^{m}}dp_{k+1,x,y})=0]$$

- 此时时间复杂度为 $O(ln^2m^2)$，超时。因此考虑在算完第 $k$ 轮后使用**二维前缀和** $s$ 维护：

$$s_{i,j}=(s_{i,j+1}|s_{i+1,j}|dp_{k,i,j})$$

- 方程变为：在 $b_{i,j}=a_k$ 的情况下

$$dp_{k,i,j}=(s_{i+1,j+1}=0)$$

- 最终答案 $ans$ 为：

$$ans=[(\sum_{i=1}^{n}{ \sum_{j=1}^{m}}{dp_{1,i,j}})>0]$$

- 若 $ans$ 为 `true`，先手胜，复杂度为 $O(lnm)$。
## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int t,l,n,m,a[N],b[N][N];
bool f,ans,s[N][N],dp[N][N][N];
inline void solve()
{
	ans=false;
	cin>>l>>n>>m;
	for(int i=1;i<=l;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>b[i][j];
		}
	}
	memset(s,false,sizeof s);//清空
	for(int k=l;k>=1;k--)
	{
		for(int i=n;i>=1;i--)
		{
			for(int j=m;j>=1;j--)
			{
				if(b[i][j]==a[k]&&!s[i+1][j+1])
				{//按照方程转移
					dp[k][i][j]=true;
				}
				else
				{
					dp[k][i][j]=false;
				}
			}
		}
		for(int i=n;i>=1;i--)
		{
			for(int j=m;j>=1;j--)
			{//维护前缀和
				s[i][j]=s[i+1][j]|s[i][j+1]|dp[k][i][j];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{//累计答案
			ans|=dp[1][i][j];
		}
	}
	if(ans)//若ans为true,先手赢
	{
		cout<<"T\n";
	}
	else
	{
		cout<<"N\n";
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(cin>>t;t;t--)
	{
		solve();
	}
	exit(0);
}
```

---

## 作者：ben090302 (赞：0)

注意到当前是谁行动并不重要，我们不需要知道当前是谁行动，只需要知道当前状态必胜还是必败就行。

不妨考虑设 $f_{i,x,y}$ 表示当前选数组 $a$ 的第 $i$ 位，当前点 $(x,y)=a_i$ ，问当前状态必胜还是必败。

考虑初始状态，显然 $f_{l+1,?,?}$ 一定是必败，其次 $f_{?,?,m}$ 和 $f_{?,n,?}$ 必胜，也就等价于横或纵坐标大于 $n$ 或 $m$ 的必败，这是等价的 。

暴力转移不太合适，我们可以对 $f_{i,?,?}$ 记录一个后缀或和优化转移。
 
码是好实现的。

```
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int T,n,m,l;
int a[N];
int s[N][N];
int f[N][N][N];
int sum[N][N][N];
void work(){
	cin>>l>>n>>m;	
	for(int i=1;i<=l;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
		}
	}
	for(int i=1;i<=l+1;i++){
		for(int x=1;x<=n+1;x++){
			for(int y=1;y<=m+1;y++){
				sum[i][x][y]=f[i][x][y]=0;
			}
		}
	}
	for(int i=l;i;i--){
		for(int x=1;x<=n;x++){
			for(int y=1;y<=m;y++){
				if(s[x][y]!=a[i]) continue;
				f[i][x][y]=(sum[i+1][x+1][y+1]==0);
			}
		}
		for(int x=n;x>=1;x--){
			for(int y=m;y>=1;y--){
				sum[i][x][y]|=sum[i][x+1][y];
				sum[i][x][y]|=sum[i][x][y+1];
				sum[i][x][y]|=f[i][x][y];
			}
		}
	}
	int ans=0;
	for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			ans+=f[1][x][y];
		}
	}
	if(!ans) cout<<"N\n";
	else cout<<"T\n";
}

int main(){ 
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) work();
}
```

---

