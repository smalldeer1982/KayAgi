# [ABC109D] Make Them Even

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc109/tasks/abc109_d

縦 $ H $ 行横 $ W $ 列に区切られたマス目があり、上から $ i $ 番目、左から $ j $ 列目のマスをマス $ (i,\ j) $ と呼びます。

マス $ (i,\ j) $ には $ a_{ij} $ 枚のコインが置かれています。

あなたは以下の操作を何度でも行うことができます。

操作: まだ選んだことのないマスのうち $ 1 $ 枚以上のコインが置かれているマスを $ 1 $ つ選び、そのマスに置かれているコインのうち $ 1 $ 枚を上下左右に隣接するいずれかのマスに移動する

偶数枚のコインが置かれたマスの数を最大化してください。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ H,\ W\ \leq\ 500 $
- $ 0\ \leq\ a_{ij}\ \leq\ 9 $

### Sample Explanation 1

次のように操作を行えば、全てのマスに置かれたコインの数を偶数にできます。 - マス $ (2,\ 2) $ に置かれているコインのうち $ 1 $ 枚をマス $ (2,\ 3) $ に移動します - マス $ (1,\ 1) $ に置かれているコインのうち $ 1 $ 枚をマス $ (1,\ 2) $ に移動します - マス $ (1,\ 3) $ に置かれているコインのうち $ 1 $ 枚をマス $ (1,\ 2) $ に移動します

## 样例 #1

### 输入

```
2 3
1 2 3
0 1 1```

### 输出

```
3
2 2 2 3
1 1 1 2
1 3 1 2```

## 样例 #2

### 输入

```
3 2
1 0
2 1
1 0```

### 输出

```
3
1 1 1 2
1 2 2 2
3 1 3 2```

## 样例 #3

### 输入

```
1 5
9 9 9 9 9```

### 输出

```
2
1 1 1 2
1 3 1 4```

# 题解

## 作者：Him_shu (赞：14)

## 题面翻译

有一个方形单元格的网格，有 $H$ 个水平行和 $W$ 个垂直列。第 $i$ 行和第 $j$ 列的单元格将表示为。
在 $Cell_{i,j}$ 中，放置了 $a_{i,j}$ 个硬币。

您可以任意次执行以下操作：
选择一个之前没有选择的包含一个或多个硬币的单元格，然后将其中一个硬币移动到垂直或水平相邻的单元格中。

最大化包含偶数硬币的单元格数量。

## 代码分析

**总体思路**：

- 目的是通过移动硬币使包含偶数硬币的单元格数量最大化。
- 从左上角开始按之字形顺序遍历网格中的每个单元格，每次遇到奇数个硬币的单元格时，如果还有奇数个硬币的单元格未处理，则将一个硬币移动到下一个单元格。

**算法流程**：

- 首先，输入网格的行数 $h$ 和列数 $w$，并统计奇数个硬币的单元格数量 $sumodd$。
  - 然后，通过一个循环按照之字形顺序遍历每个单元格。
    - 根据当前遍历的索引 $hash$ 计算出当前单元格的坐标 $(cy,cx)$。
    - 如果当前单元格的硬币数量是奇数，则 $cntodd$ 加 1。
    - 计算下一个单元格的坐标 $(ny,nx)$。
    - 如果 $cntodd$ 是奇数，并且 $cntodd < sumodd$，则将从当前单元格到下一个单元格的移动操作添加到 $res$ 中。
- 最后，输出移动操作的数量和每个移动操作的具体信息。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 510
int h, w;
int a[N][N];
struct info {
	int u, v, x, y;
};
signed main() {
	// 输入行数和列数
	cin >> h >> w;
	int sum_odd = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> a[i][j];
			// 统计奇数个硬币的单元格数量
			if (a[i][j] % 2 == 1) sum_odd++;
		}
	}

	vector<info> res;
	int cnt_odd = 0;
	// 按照之字形顺序遍历每个单元格
	for (int hash = 0; hash < h * w; hash++) {
		int cy = hash / w;
		// 根据行的奇偶性计算列坐标
		int cx = (cy % 2 == 0 ? hash % w ： w - 1 - hash % w);

		if (a[cy][cx] % 2 == 1) cnt_odd++;

		int nxt_hash = hash + 1;
		int ny = nxt_hash / w;
		int nx = (ny % 2 == 0 ? nxt_hash % w ： w - 1 - nxt_hash % w);

		// 如果当前奇数单元格数量为奇数且还有奇数单元格未处理，则添加移动操作
		if (cnt_odd % 2 == 1) {
			if (cnt_odd < sum_odd) res.push_back({cy, cx, ny, nx});
		}
	}

	// 输出移动操作的数量和每个操作的信息
	cout << res.size() << "\n";
	for (auto [u, v, x, y] ： res) cout << u + 1 << ' ' << v + 1 << ' ' << x + 1 << ' ' << y + 1 << "\n";
	return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc109_d)

比较水（吧）
# 题意
有一张无穷大的网格，初始时 $n$ 行 $m$ 列的网格里装着给定数量的硬币，每次操作可以选择一个**没选择过**的格子，将里面的一个硬币一道相同的格子里。输出操作后有偶数个硬币的格子数的最大值以及此时的网格图像。
# 思路
首先，设硬币总数为 $sum$。

很容易想到，对于每一行，如果能让每个格子都有偶数个硬币，那么这就是这一行的最优解。

那么要使有偶数个硬币的格子数最大，可以从上往下遍历每一行。对于一行，可以这样操作：
1. 遍历一行中的每一个格子，若这个格子不为他所在行的最后一个格子，且里的硬币数为奇数，则移动一个硬币到它右边的格子里。
2. 若此行的最后一个格子的硬币数为奇数，且此行不为最后一行，则将此行的最后一个格子的一个硬币移到下一行。

通过上述方法，除最后一行最后一列的格子以外，所有格子的硬币数**肯定**都为偶数。所以若 $sum$  为奇数，则解为 $n \times m - 1$ ，否则为 $n \times m$。

由于蒟蒻码风极丑，就不放出来了。求关（溜~

---

## 作者：Nightingale_OI (赞：2)

### 大意

有 $ n \times m $ 的矩阵，对于每个点，只能以任意顺序执行最多一次移动。

移动为让该格子的一枚硬币移到与它四联通的某个格子上。

若该格子没有硬币，则移动无效，不允许存在此情况。

求一种移动方案使得硬币数为偶数的位置最多。

### 思路

发现只有移动奇数数量的位置才有可能会让答案更优。

因为移动为偶数数量的位置至少会让为偶数的位置减少一个，而至多增加一个为偶数的位置。

只需要找到一条可以把矩阵的每个点不重地覆盖到的四联通 DAG ，沿着这条路径贪心移动奇数数量的位置即可。

至于一条可以把矩阵的每个点不重地覆盖到的四联通 DAG ，从上到下的蛇形是一种选择。

时间复杂度 $ O(nm) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
struct abcd{
    int a,b,c,d;
};
queue<abcd>ans;
int a[505][505];
int main(){
    cin>>n>>m;
    f(i,1,n)f(j,1,m)scanf("%d",&a[i][j]);
    f(i,1,n){
        if(i&1){
            f(j,1,m)if(a[i][j]&1){
                if(j<m){
                    --a[i][j];++a[i][j+1];
                    ans.push((abcd){i,j,i,j+1});
                }else if(i<n){
                    --a[i][j];++a[i+1][j];
                    ans.push((abcd){i,j,i+1,j});
                }
            }
        }else{
            g(j,m,1)if(a[i][j]&1){
                if(j>1){
                    --a[i][j];++a[i][j-1];
                    ans.push((abcd){i,j,i,j-1});
                }else if(i<n){
                    --a[i][j];++a[i+1][j];
                    ans.push((abcd){i,j,i+1,j});
                }
            }
        }
    }
    printf("%d\n",ans.size());
    while(ans.size()){
        printf("%d %d %d %d\n",ans.front().a,ans.front().b,ans.front().c,ans.front().d);
        ans.pop();
    }
    return 0;
}
```

---

## 作者：PDAST (赞：1)

水题一道，但开始没做出来。
## 题目大意
你每次可以把一个格子上的一枚硬币放到它相邻的格子上，求最多能推出几个格子上硬币数量为偶数的格子，请输出操作。
## 思路
我们可以先一行一行地把有奇数个硬币的格子向右推，然后从上往下把最后一列的给推到最后一行最后一列，这样，如果总硬币数为奇数，则有总格数减一个硬币数为偶数的格子；否则，有总格数个硬币数为偶数的格子。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[501][501];
int ans1[250001],ans2[250001],ans3[250001],ans4[250001];
int t=0;
int main(){
	int h,w;
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<w;j++){
			if(a[i][j]%2){
				a[i][j]--;
				a[i][j+1]++;
				ans1[++t]=i;
				ans2[t]=j;
				ans3[t]=i;
				ans4[t]=j+1;
			}
		}
	}
	for(int i=1;i<h;i++){
		if(a[i][w]%2){
			a[i][w]--;
			a[i+1][w]++;
			ans1[++t]=i;
			ans2[t]=w;
			ans3[t]=i+1;
			ans4[t]=w;
		}
	}
	cout<<t<<"\n";
	for(int i=1;i<=t;i++){
		cout<<ans1[i]<<" "<<ans2[i]<<" "<<ans3[i]<<" "<<ans4[i]<<"\n";
	}
	return 0;
} 
```

---

## 作者：Gaoyx (赞：1)

## 思路
便利整个图如果是奇数就向下传递下去，偶数则不变。

一个很重要的点就是没有要求步数最小化，这样就可以直接遍历整个图，可以使用蛇形搜索一行行向下遍历。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int m, n;
int a[551][551];
int ans[250001][5], qwq=0;//蒟蒻不会动态数组 
bool tot=0;
int main()
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> a[i][j];//朴实无华的输入 
		}
	}	
	for(int i=1;i<=n;i++)
	{
		if(i%2==1)//奇数行从左向右遍历 
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j] % 2 == 1)
				{
					tot ^= 1;//如果是奇数则更改状态 
				}
				if(tot)
				{
					if(j != m)
					{
						qwq++;
						ans[qwq][1] = i;
						ans[qwq][2] = j;
						ans[qwq][3] = i;
						ans[qwq][4] = j+1;
					}
					else
					{
						if(i == n) break;//如果是最后一行则不用向下遍历 
						qwq++;
						ans[qwq][1] = i;
						ans[qwq][2] = j;
						ans[qwq][3] = i+1;
						ans[qwq][4] = j;
					}
				}
			}
		}
		else//偶数行从右向左遍历 
		{
			for(int j=m;j>=1;j--)
			{
				if(a[i][j] % 2 == 1)
				{
					tot ^= 1;
				}
				if(tot)
				{
					if(j != 1)
					{
						qwq++;
						ans[qwq][1] = i;
						ans[qwq][2] = j;
						ans[qwq][3] = i;
						ans[qwq][4] = j-1;
					}
					else
					{
						if(i == n) break;
						qwq++;
						ans[qwq][1] = i;
						ans[qwq][2] = j;
						ans[qwq][3] = i+1;
						ans[qwq][4] = j;
					}
				}
			}
		}
	}
	cout<<qwq << "\n";
	for(int i=qwq;i>=1;i--)
	{
		cout << ans[i][1] << " " << ans[i][2] <<" "<< ans[i][3] <<" "<< ans[i][4] << "\n";
	}
	return 0;
}
```



---

## 作者：wandereman (赞：0)

## 思路
1. 我们可以把图中的奇数向下移动。
2. 由于没有步数限制，我们可以简单粗暴，遍历整个图。
3. 直到图中的偶数最多。 
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[600][600];
int a1[114514],a2[114514];
int a3[114514],a4[114514];
int t = 0;
signed main(){
	int h,w;
	cin>>h>>w;
	for(i = 1;i <= h;i++){
		for(j = 1;j <= w;j++){
			cin>>a[i][j];
		}
	}
	for(i = 1;i <= h;i++){
		for(j = 1;j < w;j++){
			if(a[i][j] % 2 == 1){
				a[i][j]--;
				a[i][j+1]++;
				a1[++t]=i;
				a2[t]=j;
				a3[t]=i;
				a4[t]=j+1;
			}
		}
	}
	for(i = 1;i < h;i++){
		if(a[i][w] % 2 == 1){
			a[i][w]--;
			a[i + 1][w]++;
			a1[++t]=i;
			a2[t]=w;
			a3[t]=i+1;
			a4[t]=w;
		}
	}
	cout<<t<<endl;
	for(i = 1;i <= t;i++){
		cout<<a1[i]<<" "<<a2[i]<<" "<<a3[i]<<" "<<a4[i]<<endl;
	}
	return 0;
}
```

---

## 作者：iranai (赞：0)

# 思路
由于每个格子只能选择一次，那可以思考：遍历到当前格子时，如若是奇数，则可直接移走一个硬币，因为这样无非会造成两种情况：

**硬币数增加的格子原本是偶数，移动后变成奇数；硬币数增加的格子原本是奇数，移动后变成偶数。**

可以发现，我们进行这样的移动，只可能让场上偶数变多或不变。至于具体的遍历方法实际有很多种，我这里是正常顺着遍历。


# 代码

```
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
int n,m;
int a[510][510];
vector<PII> op1;
vector<PII> op2;
int cnt;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]%2==1&&j!=m){
				a[i][j]-=1;
				a[i][j+1]+=1;
				cnt++;
				op1.push_back((PII){i,j});
				op2.push_back((PII){i,j+1});
			}else if(a[i][j]%2==1&&j==m&&i!=n){
				a[i][j]-=1;
				a[i+1][j]+=1;
				cnt++;
				op1.push_back((PII){i,j});
				op2.push_back((PII){i+1,j});
			}
		}
	}
	printf("%d\n",cnt);
	for(int i=0;i<cnt;i++){
		printf("%d %d %d %d\n",op1[i].first,op1[i].second,op2[i].first,op2[i].second);
	}
	return 0;
}
```

---

## 作者：125125A (赞：0)

# 前言
随机跳题跳过来的，当我看见 $143$ 提交但是只有 $66$ 通过的时候，我还以为是什么世纪级难题，~~没想到是一道大水题，虽然我开始没做出来~~。
# 正文
[题目传送门](https://www.luogu.com.cn/problem/AT_abc109_d)
## 题目大意
你每次可以把一个格子上的一枚硬币放到它相邻的格子上，求最多能推出几个格子上硬币数量为偶数的格子。
## 思路
先一行一行地把有奇数个硬币的格子向右推，然后从上往下把最后一列的给推到最后一行最后一列。

这样，如果总硬币数为奇数，则有总格数减一个硬币数为偶数的格子；否则，有总格数个硬币数为偶数的格子。
## Code:

```
#include<bits/stdc++.h>
using namespace std;

int a[501][501];
int arr[250001], brr[250001], crr[250001], drr[250001];
int t;
int h, w;

int main() {
	
	cin >> h >> w;
	
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> a[i][j];
		}
	}
	
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < w; j++) {
			if (a[i][j] % 2 != 0) {
				a[i][j]--;
				a[i][j + 1]++;
				arr[++t] = i;
				brr[t] = j;
				crr[t] = i;
				drr[t] = j + 1;
			}
		}
	}
	
	for (int i = 1; i < h; i++) {
		if (a[i][w] % 2 != 0) {
			a[i][w]--;
			a[i + 1][w]++;
			arr[++t] = i;
			brr[t] = w;
			crr[t] = i + 1;
			drr[t] = w;
		}
	}
	
	cout << t << endl;
	for (int i = 1; i <= t; i++) {
		cout << arr[i] << " " << brr[i] << " " << crr[i] << " " << drr[i] << "\n";
	}
	
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

我们假设每个硬币堆中偶数个数的硬币不存在（因为在一个硬币堆中删除偶数个硬币并不会更改它的奇偶性），则整个硬币网格里面每个格子只会有 $0$ 个或者 $1$ 个硬币。

$0$ 个硬币的格子显然是偶数。如果某个格子里面有 $1$ 个硬币，想象“推平”的过程，我们必须要把这 $1$ 个硬币推走。为了方便起见，我们从左往右处理，让硬币也是从左往右推。如果到了最右边一列，便让硬币从上往下推。这样最终所有的硬币都会被推到右下角。

此时你也不需要管右下角最终有多少个硬币。假设有偶数个，固然是好的，因为现在整个硬币网格里面除了这一个有硬币的格子以外都已经被推空了。假设有奇数个，那么这奇数个硬币再怎么分也还是会有奇数，已经最优了。

同时，在开头已经保证了每个格子里最多只有一个硬币，也满足了题目里面的次数限制。

---

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 505;

int a[N][N];

signed main() {
  int h, w;
  cin >> h >> w;
  for(int i = 1; i <= h; i++) {
    for(int j = 1; j <= w; j++) {
      cin >> a[i][j];
    }
  }
  vector<pair<pair<int, int>, pair<int, int> > > ans;
  for(int i = 1; i <= h; i++) {
    for(int j = 1; j < w; j++) {
      while(a[i][j] % 2) {
        a[i][j]--;
        a[i][j + 1]++;
        ans.push_back({{i, j}, {i, j + 1}});
      }
    }
  }
  for(int i = 1; i < h; i++) {
    while(a[i][w] % 2) {
      a[i][w]--;
      a[i + 1][w]++;
      ans.push_back({{i, w}, {i + 1, w}});
    }
  }
  cout << ans.size() << '\n';
  for(auto i : ans) {
    cout << i.first.first << ' ' << i.first.second << ' ' << i.second.first << ' ' << i.second.second << '\n';
  }
}
``

---

## 作者：YFF1 (赞：0)

## 题目大意：
给定一个矩阵，可以无限次移动矩阵内的硬币至他的上下左右位置，求一种方案使得移动完成后矩阵格子内的奇数格数量最少。
## 思路：
可以考虑一种做法，将每一排的数量为奇数硬币全部堆到最后一个格子去，然后将最后一列的奇数硬币堆到最后一行最后一列去，这样可以使得只有最后一行最后一列的那个格子是奇数，或者全部都是偶数。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
int h,w,a[505][505],cnt=0,b[505][505];
int main () {
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
			a[i][j]=a[i][j]%2;
			b[i][j]=a[i][j];
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<w;j++){
			if(b[i][j]%2!=0){
				cnt++;
				b[i][j+1]++;
			}
		}
	}
	for(int i=1;i<h;i++){
		int j=w;
		if(b[i][j]%2!=0){
			cnt++;
			b[i+1][j]++;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=h;i++){
		for(int j=1;j<w;j++){
			if(a[i][j]%2!=0){
				cout<<i<<" "<<j<<" "<<i<<" "<<j+1<<endl;
				a[i][j+1]++;
			}
		}
	}
	for(int i=1;i<h;i++){
		int j=w;
		if(a[i][j]%2!=0){
			cout<<i<<" "<<j<<" "<<i+1<<" "<<j<<endl;
			a[i+1][j]++;
		}
	}
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

如果只有一行，那么很简单，从左到右扫，如果是奇数，那么往右边 $+1$，自身 $-1$。如果偶数则不变。

这样一来，只有最后一个元素不能保证是偶数。


如果有多行，对每一行进行这个操作。然后只有最后一列的元素没有保证是偶数。

对最后一列进行这个操作。那么只有 $(H,W)$ 这个元素不能保证是偶数。

那么这操作完了一周肯定是最多的元素。但不一定是操作次数最少的。（事实上，操作次数比较多。）

上代码：
```cpp

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <cmath>
using namespace std;
int mp[555][555];
struct node
{
    int x1,y1,x2,y2;
    node(int x,int y,int xx,int yy):
        x1(x),y1(y),x2(xx),y2(yy){}
};
 
int main()
{
    vector<node> ans;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            if(mp[i][j]&1){
                ans.push_back(node(i,j,i,j+1));
                mp[i][j+1]++;
            }
        }
    }
    for(int i=1;i<n;i++){
        if(mp[i][m]&1)
            ans.push_back(node(i,m,i+1,m)),mp[i+1][m]++;
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++){
        printf("%d %d %d %d\n",ans[i].x1,ans[i].y1,ans[i].x2,ans[i].y2);
    }

```

---

## 作者：Black_Porridge (赞：0)

~~这个真的是D题吗 害怕~~

### 题目大意：
给你一个 $h \times w$ 的矩阵，每当选择任一元素令其 $-1$ 时，必须选择一个和他相临（上下左右）的元素 $+1$ ，每个元素只能进行一次减法操作。给定每个元素的初始值，问如何操作能让该矩阵中偶元素最多。并且输出操作次数和具体过程。

解题思路：

既然这道题说了一个元素最多只能进行一次减法操作，所以我们只需要每行依次从左至右遍历，令每个奇数自身 $-1$ ，后一个数  $+1$ 即可。于是我们可以保证每一横排除最后一个数都是偶数。之后再从上到下遍历最后一排，也能令最后一排除最后一个数都为偶数，即不保证 $(h, w)$ 的奇偶性。那么此时该矩阵偶元素最多。

代码实现：

**此处每个操作要输出四个变量，于是我开了一个结构体 +  vector，比较方便存储。
```.cpp

#include <iostream>
#include <vector>
using namespace std;

const int N = 510;

int h, w;

int a[N][N];

struct Node{
    int x, y, xx, yy;
};

vector <Node> ans;

int main()
{
    cin >> h >> w;
    for(int i = 1; i <= h; i++)
        for(int j = 1; j <= w; j++)
            cin >> a[i][j];

    for(int i = 1; i <= h; i++)
    {
        for(int j = 1; j < w; j++)
        {
            if(a[i][j] & 1)
            {
                ans.push_back(Node{i, j, i, j + 1});
                a[i][j + 1]++;
            }
        }
    }
    for(int i = 1; i < h; i++)
    {
        if(a[i][w] & 1)
        {
            ans.push_back(Node{i, w, i + 1, w});
            a[i + 1][w]++;
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].x << " " << ans[i].y << " " << ans[i].xx << " " << ans[i].yy << endl;
     }
    return 0;
}





---

## 作者：Down_syndrome (赞：0)

## 题意
给出一个 $N\times M$ 的矩阵，每个格子上有若干枚硬币。每次可以选择一个之前没有选择过的格子，把格子中其中一个硬币移动到相邻四个格子中。问怎样操作能让硬币数为偶数的格子数最大。要求输出移动次数和移动方案。移动数不作要求。
## 思路
首先很明显只移动硬币数量为奇数的格子，答案才能最优。移动可以看成把一枚硬币传递下去，直到遇到奇数硬币的格子，组成偶数硬币的格子。所以最优方案可以按一条制定的路径，遇到奇数硬币格子就按路径传递给下一个格子。至于那条路径，需要遍历所有格子。蛇形路径是个很好的选择。
## 代码实现
深搜遍历出蛇形路径，按照思路模拟，可以开一个 vector 便于储存答案。

**(说明的有点抽象，不懂的地方可以私信我)**
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,m,cnt,a[N][N],ordx[N*N],ordy[N*N];
struct node{
	int x,y,nx,ny;
};
vector<node> v;
void dfs(int x,int y,int k){
	if(x>n) return;
	ordx[++cnt]=x;
	ordy[cnt]=y;
	if(k){
		if(y==m) dfs(x+1,m,0);
		else dfs(x,y+1,1);
	}
	else{
		if(y==1) dfs(x+1,1,1);
		else dfs(x,y-1,0);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	dfs(1,1,1);
	for(int i=1;i<=cnt;i++){
		if(a[ordx[i]][ordy[i]]%2){
			if(i!=cnt){
				v.push_back((node){ordx[i],ordy[i],ordx[i+1],ordy[i+1]});
				a[ordx[i+1]][ordy[i+1]]++;
			}
		}
	}
	printf("%d\n",v.size());
	for(int i=0;i<v.size();i++) printf("%d %d %d %d\n",v[i].x,v[i].y,v[i].nx,v[i].ny);
	return 0;
} 
```


---

## 作者：Tian36309 (赞：0)

**题目大意：**

给定一个 $n \times m$ 的矩阵，每个格子有一个数字，每次操作可以选择一个格子，将这个格子的数字 $-1$ ，并将相邻的一个格子的数字 $+1$ ，要求最大化格子中数字是偶数的格子数量，每个格子只能被选择一次。

**思路：**

首先，很关键的一点是本题没有要求最小化步数，于是我们便可以放心考虑各种方法。

其次，如果格子中的数之和为偶数，那我们可以通过把所有硬币都堆到一个格子来使所有格子都为偶数，同理，如果格子中的数之和为奇数，用同样的方法可以使得只有一个格子为奇数。



我用的方法如下：

首先，我们以 $4 \times 4$ 的网格举例，只要用如图所示的方法，就可以将硬币从某个格子传到他下方的格子，还完美的满足了每个点只能被选择一次的限制

![](https://cdn.luogu.com.cn/upload/image_hosting/zue784s1.png)

比如说我要从 $(1,4)$ 将硬币传到 $(2,1)$，那么我就可以这样走：

$(1,4)$ 移到 $(1,3)$

$(1,3)$ 移到 $(1,2)$

$(1,2)$ 移到 $(1,1)$

$(1,1)$ 移到 $(2,1)$ ，大功告成

那么，如下传递方式有什么用呢？

我们先假设这张图中有偶数个点是奇数，即图中打叉的点：

![](https://cdn.luogu.com.cn/upload/image_hosting/rwu6w1tt.png)

按照刚才的路线走，在经过的第一个奇数点带走一个硬币，并按照我们的路线往下传（一次传一格，一格一格传即可），直到再遇到一个奇数点，便把硬币放在这一格，不再往下传了，继续往下走，直至再遇到第三个奇数点……这样，我们遇到的奇数点，要么多了一个硬币，要么少了一个硬币，都变成了偶数，而传递过程中途径的点，先多了一个硬币，又少了一个硬币，仍然为偶数。这时，我们的任务就完成了。

具体看图，图中红色路线代表往下走，绿色路线代表往下传硬币：

![](https://cdn.luogu.com.cn/upload/image_hosting/r6s8cuus.png)

至于有奇数个点是奇数的情况，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5c3wvcvd.png)

我们还是用刚才的方法，即使最后硬币没有传到最后一个奇点，路上的所有奇点也都被我们消除了，最后一个硬币直接放在最后一格就行，因为本题只要求最大化偶点数量，**并未要求最小化步数**，这里我们前面也提到了。所以最后一个奇点在哪里都没有关系，不必理会（这时所有格子中数字的和很明显为奇数，所以最后肯定有一个格子是奇数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/mn3jw634.png)

总结一下，就是每遇到一个奇点，就改变状态（原本正在传就停止，反之开始往下传），然后跑一边图就行了。

值得注意的是，如果硬币已经传到了某行的最后一格，那么应该往下一行传，如果已经在最后一行，直接把硬币放在这个格子，不用往下传了。

时间复杂度 $O(nm)$ ，可以通过此题。

其他细节我会在代码中注明。

**满分代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[250005][5],mp[505][505],flag,cnt; //这个ans是存答案的数组，应该开到n*m大小，不要开小了
void c(int x11,int y11,int x22,int y22){
	cnt++;
	ans[cnt][1] = x11;
	ans[cnt][2] = y11;
	ans[cnt][3] = x22;
	ans[cnt][4] = y22;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mp[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		if(i%2 == 1){ //如果是在奇数行就从右往左
			for(int j=m;j>=1;j--){
				if(mp[i][j] % 2 == 1){ //碰到奇数点，改变状态
					flag ^= 1;
				}
				if(flag){ //现在应该往下传
					if(j == 1 and i == n)break; //已经是最后一格了，结束。
					if(j != 1){ //不在该行最后一格，往左走
						c(i,j,i,j-1);
					}
					else{ //否则往下走
						c(i,j,i+1,j);
					}
				}
			}
		}
		else{ //如果是在偶数行就从坐往右
			for(int j=1;j<=m;j++){ //碰到奇数点，改变状态
				if(mp[i][j] % 2 == 1){
					flag ^= 1;
				}
				if(flag){ //现在应该往下传
					if(j == m and i == n)break; //已经是最后一格了，结束。
					if(j != m){ //不在该行最后一格，往右走
						c(i,j,i,j+1);
					}
					else{ //否则往下走
						c(i,j,i+1,j);
					}
				}
			}
		}
	}
	printf("%d\n",cnt); //输出步数和答案
	for(int i=1;i<=cnt;i++){
		printf("%d %d %d %d\n",ans[i][1],ans[i][2],ans[i][3],ans[i][4]);
	}
	return 0;
}
```

祝各位早日通过，拒绝 UKE。

---

