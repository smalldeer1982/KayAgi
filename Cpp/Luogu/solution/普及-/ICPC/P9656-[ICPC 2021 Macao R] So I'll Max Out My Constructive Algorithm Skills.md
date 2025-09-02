# [ICPC 2021 Macao R] So I'll Max Out My Constructive Algorithm Skills

## 题目描述

宝宝女巫被困在一个 $n$ 行 $n$ 列的迷宫中，其中第 $i$ 行第 $j$ 列的单元格高度为 $h_{i,j}$。要走出迷宫，宝宝必须找到一条路径，该路径穿过每个单元格恰好一次。每次她只能移动到与当前单元格共享边的相邻单元格。但是众所周知，宝宝非常懒，所以每当她爬升（即从高度较低的单元格移动到高度较高的单元格）时，她的幸福值会减少。作为她的帮手，你的任务是找到一条有效的路径，使得沿着路径移动时，宝宝爬升的次数不多于她下降的次数。

更正式地说，你需要找到一个序列 $(x_1, y_1), (x_2, y_2), \cdots, (x_{n^2}, y_{n^2})$，使得：
- 对于所有的 $1 \le i \le n^2$，$ 1 \le x_i, y_i \le n$；
- 对于所有的 $1 \le i, j \le n^2, i \neq j$，$ (x_i, y_i) \neq (x_j, y_j)$；
- 对于所有的 $2 \le i \le n^2$，$|x_i - x_{i-1}| + |y_i - y_{i-1}| = 1$；
- $\sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} < h_{x_i, y_i}]} \le \sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} > h_{x_i, y_i}]}$，其中 $[P]$ 当 $P$ 为真时等于 $1$，当为假时等于 $0$。

此外，你发现所有单元格的高度都是 $n^2$ 的排列，所以你只需要输出有效路径中每个单元格的高度。

## 样例 #1

### 输入

```
1
2
4 3
2 1```

### 输出

```
4 3 1 2```

# 题解

## 作者：luan341502 (赞：4)

这题我们考虑随意找出一条路径，计算出题中所述的由上到下的次数和由下到上的次数，如果前者多直接输出，如果后者多倒序输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int n,a[105][105];
vector<int> ans;
int main(){
	cin>>t;
	while(t--){
		ans.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			if(i&1){
				for(int j=1;j<=n;j++) ans.push_back(a[i][j]);
			}else{
				for(int j=n;j;j--) ans.push_back(a[i][j]);
			}
		}
		int cnt=0,cnt_=0,N=n*n;
		for(int i=0;i<N-1;i++){
			if(ans[i]>ans[i+1]) cnt++;
			else cnt_++;
		}
		if(cnt<cnt_) reverse(ans.begin(),ans.end());
		for(int i=0;i<N;i++){
			printf("%d ",ans[i]);
		}
		puts("");
	}
    return 0;
}
```


---

## 作者：tang_mx (赞：2)

一个很简单的想法是，随意寻找一条通路，统计这条通路中攀爬和下降的总数 $cnt1$ 和 $cnt2$，因为要使得路径上攀爬的次数不多于下降的次数，因此若 $cnt1 > cnt2$，则将这条路径翻转后再输出即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100;

int T;

int a[N][N];

void slove(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	vector<int>ans;
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
	    if(i%2==0)
	        reverse(a[i]+1,a[i]+n+1);
	    for(int j=1;j<=n;j++)
	        ans.push_back(a[i][j]);
	}
	for(int i=1;i<ans.size();i++){
	    if(ans[i]>ans[i-1])cnt1++;
	    else cnt2++;
	}
	if(cnt1>cnt2)
		reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
		printf("%d ",ans[i]);
	printf("\n");
}

int main(){
	scanf("%d",&T);
	while(T--){
		slove();
	} 
	return 0;
}
```


---

## 作者：sfqxx1 (赞：2)

一篇 Python 题解。

## 题意大意： 
给出一个 $n×n$ 的矩阵，矩阵上的数字是一个 $n^{2}$ 的排列，矩阵中每个点只能往四周的四个点走，定义路径中一条出点的值大于入点的值的边为第一种类型的边，反之则为第二种类型的边，要求求出矩阵构成的图的一条**哈密顿路径**，满足第一种类型的边小于等于第二种类别的边。

## 分析：

这应该是比较简单的一道题，我们可以直接求出哈密顿路径，不满足直接输出反转后的路径即可。

什么是哈密顿路径？

哈密尔顿路径是一个有向或无向图上从一个顶点到另一个顶点的路径，这个路径经过该图恰好一次。

（摘自百度）

Python 代码：

```
T = int(input())

for _ in range(T):
    v = []
    n = int(input())
    a = []
    for _ in range(n):
        a.append(list(map(int, input().split())))
    for i in range(n):
        if i & 1:
            for j in range(n):
                v.append(a[i][j])
        else:
            for j in range(n - 1, -1, -1):
                v.append(a[i][j])
    tot = 0
    for i in range(len(v) - 1):
        if v[i] < v[i + 1]:
            tot -= 1
        else:
            tot += 1
    if tot < 0:
        v.reverse()
    for i in range(len(v) - 1):
        print(v[i], end=' ')
    print(v[-1])
```



---

## 作者：haokee (赞：1)

## 题意简介

在一个 $n\times n$ 的矩阵里面，有一个人要一行一行蛇形爬过去。求一条路径 $l$，使得 $\sum\limits_{i=1}^{n^2-1}l_i>l_{i+1}$ 严格小于 
$\sum\limits_{i=1}^{n^2-1}l_{i}\le l_{i-1}$。

## 思路

我们可以枚举每一列，蛇形记录下路径。然后对路径进行枚举，分别记录正着要爬的台阶数量以及反着要爬的台阶数量，取最小值输出路径。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 65;

int a[kMaxN][kMaxN], t, n, c1, c2;
vector<int> v;  // 使用vector记录路径

int main() {
  for (cin >> t; t; t--) {
    cin >> n, v.clear(), c1 = c2 = 0;  // 多测记得清空
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      if (i & 1) {  // 如果是奇数行
        for (int j = 1; j <= n; j++) {  // 正着走过去
          v.push_back(a[i][j]);
        }
      } else {  // 偶数行
        for (int j = n; j >= 1; j--) {  // 反着走过去
          v.push_back(a[i][j]);
        }
      }
    }
    for (int i = 0; i < n * n - 1; i++) { // 注意vector是从零开始的
      v[i] > v[i + 1] ? ++c1 : ++c2;  // c1,c2分别表示反着、正着走过去的台阶数
    }
    if (c1 < c2) {  // 如果反着更优
      for (int i = n * n - 1; i >= 0; i--) {  // 反向输出
        cout << v[i] << ' ';
      }
    } else {
      for (int i = 0; i < n * n; i++) {  // 正着输出
        cout << v[i] << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

结论题。

如果设上坡的次数为 $up$，下坡次数为 $down$，那么随便找一条路径，如果 $up<down$，那么这条路径就是合法的。否则反着走，所有的上会变成下，所有的下会变成上，那 $up$ 就能 $<down$ 了。

------------

那么我们可以这样走：

$$a_{1,1}\Rightarrow a_{1,2}\Rightarrow a_{1,3}\Rightarrow\cdots \Rightarrow a_{1,n}\Rightarrow a_{2,n}\Rightarrow a_{2,(n-1)}\Rightarrow a_{2,(n-2)}\Rightarrow\cdots\Rightarrow a_{2,1}\Rightarrow a_{3,1}\Rightarrow\cdots\Rightarrow a_{n,n}$$

如果不合法，就反过来。

代码：

```
#include<bits/stdc++.h>
using namespace std;

int T,n,a[100005];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		int up=0,down=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			if(i%2==1){
				for(int j=1;j<=n;j++){
					cin>>a[n*(i-1)+j];
				}
			}
			else{
				for(int j=n;j>=1;j--){
					cin>>a[n*(i-1)+j];
				}
			}
		}
		for(int i=1;i<=n*n;i++){
			if(a[i]>a[i-1]) up++;
			else down++;
		}
		if(up>down) reverse(a+1,a+1+n*n);
		for(int i=1;i<=n*n;i++){
			cout<<a[i]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
一道考查路径的基础题。

作为第一题还是很良心的。
## 分析。 
首先我们分析一下题意：
 
给出一个 $n \times n$ 的矩阵，矩阵上的数字是一个 $n^2$ 的排列，矩阵中每个点只能往四周的四个点走，我们令路径中一条出点的值**大于**入点的值的边为第一类型的边，反之则为第二类型的边。

要求求出矩阵所构成的图的一条路径，且这个路径满足如下条件：
- 第一种类型的边**小于等于**第二种类别的边。
- 经过所有的点。

根据题意模拟，求出任意一条哈密顿路径然后判断是否满足要求。

如不满足，即正着走不行，那反着走就可以让小于等于变成大于，所以翻转路径即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int t,n,a[105][105],ans[10005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				cin>>a[i][j];
			}
		}
		int cut=0;
		for (int i=1;i<=n;i++){
			if(i%2==1){
				for (int j=1;j<=n;j++){
					ans[++cut]=a[i][j];
				}
			}
			else{
				for (int j=n;j>=1;j--){
					ans[++cut]=a[i][j];
				}
			}
		}
		int sumr=0,sumc=0;
		for (int i=2;i<=n*n;i++){
			(ans[i-1]<ans[i])?sumr++:sumc++;
		}
		if(sumr>sumc) reverse(ans+1,ans+n*n+1);
		for (int i=1;i<=n*n;i++){
			(i==n*n)?cout<<ans[i]<<"\n":cout<<ans[i]<<" ";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

这次镜像赛唯一做出来的题，题目真的是不错。

---

## 作者：rzm120412 (赞：0)

## 题目大意

给定一个 $n\times n$ 的数字矩阵，代表每个点的高度，每个数各不相同，求一条遍历所有的点的路径，要求只能上下左右移动，且**高度下降的次数不小于高度上升次数**。

## 思路

事实上，随便走一条路，如果下降的次数大于上升的次数，那么我们就反过来走就行了。

## AC 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int s[100][100],T,n;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
            	cin>>s[i][j];
			}
            if((i&1)==0){
            	reverse(s[i]+1,s[i]+1+n);
			} 
        }
        vector<int>a;
        long long int cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
        	for(int j=1;j<=n;j++){
        		a.push_back(s[i][j]);
			} 
		}
        for(int i=1;i<=a.size()-1;i++) {
            if(a[i]>a[i-1]){
            	cnt1++;
			}
            else{
            	cnt2++;
			}
        }
        if(cnt1>cnt2){
        	reverse(a.begin(),a.end());
		}
        for(int i=0;i<a.size();i++){
        	cout<<a[i]<<" ";
		}
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：HFanGDoDM (赞：0)

# 题意简述

给定一个 $n\times n$ 的矩阵，第 $i$ 行第 $j$ 列的数用 $h_{i,j}$ 表示。矩阵中的每个数构成一个 $n^2$ 的排列。试构造一个合法路径序列 $\{p_{n^2}\}=\{(x_{n^2},y_{n^2})\}$，满足：

- $\forall i\in\{1,2,3,...,n^2\},1\leqslant x_i,y_i\leqslant n$。

- $\forall i,j\in\{1,2,3,...,n^2\}$ 且 $i\not=j$，$p_i\not=p_j$。这两条限制，即要求这条路径需要经过矩阵中的每个数恰好一次。

- $\forall i\in \{1,2,3,...,n^2-1\}$，$p_i$ 与 $p_{i+1}$ 所对应的位置有且仅有一条公共边，即 $|x_i-x_{i+1}|+|y_i-y_{i+1}|=1$。

在此基础上，要求：

- $\displaystyle{\sum_{i=1}^{n^2-1}[h_{x_{i+1},y_{i+1}}\lt h_{x,y}]}\geqslant \displaystyle{\sum_{i=1}^{n^2-1}}[h_{x_{i+1},y_{i+1}}\gt h_{x,y}]$，即路径中的相邻“下降数量”不小于相邻“上升数量”。

试构造出该路径序列，并顺次输出路径序列中的 $h_{x_i,y_i}$。可以证明一定有解。

**数据范围**

**有多组测试数据**。对于每组测试数据，$2\leqslant n\leqslant 64$。测试数据组数 $T$ 满足 $1\leqslant T\leqslant 100$。

# 解题思路

我们考虑任意构造一条符合前三条要求的路径序列。

对于该序列，我们计算该序列的相邻“下降数量”及相邻“上升数量”。若符合题意，该序列即为一个解；否则，翻转该序列，翻转后的序列即为一个解。

**正确性证明**

若任意构造的序列符合题意，则该序列必然为一个解。

若该序列不符合题意：

设 $num_1=\displaystyle{\sum_{i=1}^{n^2-1}[h_{x_{i+1},y_{i+1}}\lt h_{x,y}]}$，$num_2=\displaystyle{\sum_{i=1}^{n^2-1}}[h_{x_{i+1},y_{i+1}}\gt h_{x,y}]$，则 $num_1<num_2$。

对于一个排列 $p$ 的两个相邻元素 $p_i$ 和 $p_{i+1}$，要么 $p_i\gt p_{i+1}$，要么 $p_i\lt p_{i+1}$。

现翻转该序列。对于原序列，任取两个相邻的元素 $a,b$，若 $a<b$，则在新序列上，这两个元素的相对位置变为 $b,a$，则有 $b>a$。即：

对于原序列上的任意两个相邻元素，左边元素与右边元素的相对大小关系，在翻转之后会交换 $\implies$ $num_1$ 和 $num_2$ 在翻转原序列后会交换。

因此，原序列在翻转后，新序列的 $num_1>num_2$，符合题意，为一个解。

所以这一思路是正确的。

**具体实现**

我们先任意构造一个符合前三条要求的路径。这里我构造的是，对于奇数行，从左向右走；对于偶数行，从右向左走。

接着，对于每对相邻元素，我们判断其在矩阵中对应的数的大小关系，并顺便计算上文中的 $num_1$ 和 $num_2$。这里我将原矩阵转化为一个数列，并将原矩阵中的坐标映射到数列的下标上。

若 $num_1\geqslant num_2$，则直接输出每个位置在矩阵中对应的 $h$ 值；否则，翻转序列，并顺次输出新序列每个位置在矩阵中对应的 $h$ 值。

**时间复杂度分析**

任意构造路径序列、判断相邻元素对应数的大小关系、翻转序列，其复杂度都为 $O(n^2)$。

总时间复杂度 $O(Tn^2)$，可以通过本题。

**参考核心代码**

```cpp
int cnt=0;
for(i=1;i<=n;i++){
	if(i&1)
		for(j=1;j<=n;j++)
			per[++cnt]=(i-1)*n+j;//将矩阵的坐标转化为序列下标
	else
		for(j=n;j>=1;j--)
			per[++cnt]=(i-1)*n+j;
}
int cnt1=0,cnt2=0;//分别计算相邻“上升数量”和相邻“下降数量”
for(i=2;i<=n*n;i++){
	if(maz[per[i]]>maz[per[i-1]])
		cnt1++;
	else
		cnt2++;
}
if(cnt1>cnt2)
	reverse(per+1,per+1+n*n);
for(i=1;i<=n*n;i++)
	printf("%d ",maz[per[i]]);
```

---

## 作者：XBaiC (赞：0)

## 思路

求出哈密顿路径满不满足要求，不满足直接输出反转后的路径。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 101 
#define INF 0x3f3f3f3f
#define NN 10001
int a[N][N];
int ans[NN];
int main()
{
    int T;
    cin >> T;
    while( T-- )
    {
        int n;
        cin >> n;
        for( int i = 1; i <= n; i++ )
        {
            for( int j = 1; j <= n; j++ )
            {
                cin >> a[i][j];
            }
        }
        int x = 0;
        for( int i = 1; i <= n; i++ )
        {
            if ( i & 1 )
            {
                for( int j = 1; j <= n; j++ )
                {
                    x++;
                    ans[x] = a[i][j];
                }
            }
            else
            {
                for(int j = n; j > 0; j--)
                {
                    x++;
                    ans[x] = a[i][j];
                }
            }
        }
        int cnt = 0, sum = 0;
        for( int i = 2; i <= ( int ) pow( n , 2 ); i++ )
        {
            if( ans[i - 1] < ans[i] ) 
            {
                cnt++;
            }
            else 
            {
                sum++;
            }
        }
        if( cnt > sum ) 
        {
            reverse(ans + 1, ans + n * n + 1);
        }
        for( int i = 1; i <= ( int ) pow( n , 2 ); i++ )
        {
            cout << ans[i] << " ";
        }
        puts( "" );
    }
    return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：0)

简单题。随便找一条路径判断是否符合条件，如果不满足就反着输出即可。

一定要注意 STL 的容器下标从 $0$ 开始，不然就会和我一样对着样例傻傻调了十分钟。

```cpp
for(cin >> T; T; -- T) {
    ans.clear(), cin >> n;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> G[i][j];
    for (int i = 1; i <= n; ++ i) {
        if (i & 1)  for(int j = 1; j <= n; ++j) ans.push_back(G[i][j]);
        else        for(int j = n; j >= 1; --j) ans.push_back(G[i][j]);
    }
    int tot = 0;
    for(int i = 0; i < ans.size() - 1; ++ i) tot += (ans[i] >= ans[i + 1]) ? 1 : -1;
    if(tot < 0) reverse(ans.begin(), ans.end());
    for(int i = 0; i < ans.size() - 1; ++ i) cout << ans[i] << ' ';
    cout << ans[ans.size() - 1] << "\n";
}
```

---

