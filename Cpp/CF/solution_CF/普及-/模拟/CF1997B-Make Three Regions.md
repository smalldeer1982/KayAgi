# Make Three Regions

## 题目描述

There is a grid, consisting of $ 2 $ rows and $ n $ columns. Each cell of the grid is either free or blocked.

A free cell $ y $ is reachable from a free cell $ x $ if at least one of these conditions holds:

- $ x $ and $ y $ share a side;
- there exists a free cell $ z $ such that $ z $ is reachable from $ x $ and $ y $ is reachable from $ z $ .

A connected region is a set of free cells of the grid such that all cells in it are reachable from one another, but adding any other free cell to the set violates this rule.

For example, consider the following layout, where white cells are free, and dark grey cells are blocked:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1997B/424d758ade46752deca8fcae4121a5c7f0d1a2fb.png) There are $ 3 $ regions in it, denoted with red, green and blue color respectively:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1997B/4fc8127700d32cdc5514e7db503c30c93554657e.png) The given grid contains at most $ 1 $ connected region. Your task is to calculate the number of free cells meeting the following constraint:

- if this cell is blocked, the number of connected regions becomes exactly $ 3 $ .

## 说明/提示

In the first test case, if the cell $ (1, 3) $ is blocked, the number of connected regions becomes $ 3 $ (as shown in the picture from the statement).

## 样例 #1

### 输入

```
4
8
.......x
.x.xx...
2
..
..
3
xxx
xxx
9
..x.x.x.x
x.......x```

### 输出

```
1
0
0
2```

# 题解

## 作者：ICU152_lowa_IS8 (赞：2)

这么说吧，这是一道很有趣的诈骗题。

第一眼看题目其实挺唬人的，又是连通块又是数量的。

但冷静一下发现只有两行，又保证
输入只有一个连通块，那就非常好做了。

我们找形如下图的 $2\times 3$ 区域：

![](https://cdn.luogu.com.cn/upload/image_hosting/jc0syna4.png)

显然，此时将 A 块染成黑色可以使该局部变成三个连通块。由于保证输入只有一个连通块，那么整个图都会被划分为三个连通块（想象一下左边和右边都是白色块）。

同时，除了这种填充方案以外不存在其它填充方法能满足题目要求。比较显然，这里不再赘述。

当然了，将上图上下颠倒所得到的图形也是满足条件的。

放代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[200005][5];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=2;i++){
			for(int j=1;j<=n;j++){
				cin>>a[j][i];
			}
		}
		int ans=0;
		for(int i=2;i<n;i++){
			if(a[i][1]=='.'){
				if(a[i][2]=='.'&&a[i-1][2]=='x'&&a[i+1][2]=='x'&&a[i-1][1]=='.'&&a[i+1][1]=='.'){
					ans++;
				}
			}
		}
		for(int i=2;i<n;i++){
			if(a[i][2]=='.'){
				if(a[i-1][1]=='x'&&a[i+1][1]=='x'&&a[i][1]=='.'&&a[i-1][2]=='.'&&a[i+1][2]=='.'){
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Heldivis (赞：1)

## CF1997B

这个题有两个性质，非常重要：

- 给定网格**至多有一个**连通块；

- 网格只有两行。

第一个性质告诉我们，只有一个点能分出三个连通块，才能计入答案。

结合第二个性质，所有答案即为形如如下形状的区域个数：

```
x . x   或   . . .
. . .       x . x
```

任选一个点枚举即可，下边代码枚举的是凸出的 `.` 的位置。

```cpp
void Main() {
  n = read(), cnt = 0;
  scanf("%s", a[1] + 1);
  scanf("%s", a[2] + 1);
  for (int i = 2; i <= n - 1; ++i) {
    if (a[1][i] == '.' && a[2][i] == '.' && a[2][i - 1] == '.' &&
        a[2][i + 1] == '.' && a[1][i - 1] == 'x' && a[1][i + 1] == 'x')
      cnt++;
    if (a[2][i] == '.' && a[1][i] == '.' && a[1][i - 1] == '.' &&
        a[1][i + 1] == '.' && a[2][i - 1] == 'x' && a[2][i + 1] == 'x')
      cnt++;
  }
  printf("%d\n", cnt);
}
```

---

## 作者：2huk (赞：1)

**题意**：有一个 $2 \times n$ 的网格，每个格点都为空或有障碍，保证所有空点连通。求有多少个空点，将其放上障碍后，空点的连通块数量为 $3$。

**做法**：首先这 $3$ 个连通块中一定有一个大小为 $1$。

我们枚举这个改变的位置。如果这个位置周围 $3$ 个格子都为空，且有一个格子被两个障碍围住（也就是那么大小为 $1$ 的连通块），这个位置就是合法的。

<https://codeforces.com/contest/1997/submission/273506583>

---

## 作者：白鲟 (赞：1)

气死了。建议大家好好读题，一共只有至多一个连通块，而不是至少一个连通块。那么如果能够一举产生三个连通块（即新增两个），必然是如下形状或其上下翻转的形状：
```
...
x.x
```
直接判断即可。赛时代码写了个对任意多个连通块统计的，大力分类讨论写死我了。放个赛后代码吧。

```cpp
#include <cstdio>
const int maxn = 2e5;
int T, n, ans;
char a[2][maxn + 1];
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s%s", &n, a[0], a[1]);
        ans = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (a[i][j] != 'x' && 
                    a[i ^ 1][j] != 'x' && a[i][j - 1] != 'x' && a[i][j + 1] != 'x' && 
                    a[i ^ 1][j + 1] == 'x' && a[i ^ 1][j - 1] == 'x') {
                    ++ans;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：coding_goat (赞：0)

注意到如果加一个阻挡块即可划分出 $3$ 个不同的连通块，只会有两种情况：

```
...
x.x
```

此时将第一排第二个点变为阻挡的格子，和

```
x.x
...
```

此时将第二排第二个点变为阻挡的格子。

统计一下即可。

---

## 作者：_O_v_O_ (赞：0)

怎么还会有人认为这题很难啊。

我们注意到题目中说了整个网格最多有一个连通块，那么要想让整个网格被分为 $3$ 个，无非就有一下两种情况（其中 `X` 是当次要堵的）：

```
.X.
x.x
```


```
x.x
.X.
```

那么直接特判一下即可。

---

## 作者：tzzl3035 (赞：0)

# CF1997B 题解
### 题目大意
有 $t$ 组数据，每组给出一个正整数 $n$，并且给出一个 $2$ 行 $n$ 列的网格，`.` 代表自由格子，`x` 代表阻塞格子，给出网格中最多**只有一个自由格子连通块**，请输出一个正整数，表示有几个自由格子在变成阻塞格子后可以将**自由格子连通块**分为 $3$ 个。
### 大致思路
通过观察样例可以发现，由于网格只有 $2$ 行，所以可以判断其中一行有 `...` 并且对应的另一行同一位置为 `x.x` 答案即可增加 $1$。
### 核心代码
```cpp
void solve() {
  // 输入
  int n;
  std::cin >> n;
  std::string s1, s2;
  std::cin >> s1 >> s2;
  // 统计答案
  int ans = 0;
  for(int i = 0; i < n-2; ++i) {
    if(s1.substr(i, 3) == "..." && s2.substr(i, 3) == "x.x") ++ans;
    if(s2.substr(i, 3) == "..." && s1.substr(i, 3) == "x.x") ++ans;
  }
  // 输出
  std::cout << ans << '\n';
}
```
### [RESULT](https://codeforces.com/contest/1997/submission/273523162)

---

## 作者：cfkk (赞：0)

根据样例可以推出，只有一下两种情况可以计入答案：

```
...    x.x
x.x    ...
```

所以直接特判即可。


```cpp
bool a[3][maxn];
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read();
        for(int i=1;i<=n;i++)
        {
            char ch;
            cin>>ch;
            if(ch=='x')a[1][i]=1;
            else a[1][i]=0;
        }
        for(int i=1;i<=n;i++)
        {
            char ch;
            cin>>ch;
            if(ch=='x')a[2][i]=1;
            else a[2][i]=0;
        }
        int cnt=0;
        for(int i=2;i<n;i++)
        {
            if(!a[2][i]&&a[2][i-1]&&a[2][i+1]&&!a[1][i+1]&&!a[1][i-1])cnt++;
        }
        for(int i=2;i<n;i++)
        {
            if(!a[1][i]&&a[1][i-1]&&a[1][i+1]&&!a[2][i+1]&&!a[2][i-1])cnt++;
        }
        print(cnt);pc(1);
    }
	return 0;
}
```

---

