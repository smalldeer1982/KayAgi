# Swap Columns and Find a Path

## 题目描述

有一个包含 $2$ 行 $n$ 列的矩阵。从上至下标号 $1,2$，从左到右标号 $1$ 到 $n$。记第 $i$ 横行第 $j$ 竖列的位置为 $(i,j)$，每个单元位置有一个整数。

你可以进行如下操作任意次（包括 $0$ 次）：

- 交换两列数字（找到整数 $x,y$ 满足 $1\le x\lt y\le n$，交换 $a_{1,x}$ 与 $a_{1,y}$，同时交换 $a_{2,x}$ 与 $a_{2,y}$）。

以上操作全部完成后，你需要找到一条从 $(1,1)$ 到 $(2,n)$ 的路径，每一次只能从 $(i,j)$ 移动到 $(i+1,j)$ 或 $(i,j+1)$。显然，路径无法走出这个矩形。

这条路径的分数为路径上所有 $(n+1)$ 个整数之和。你要进行上述的操作，并且找到最大可能的分数。

## 样例 #1

### 输入

```
3
1
-10
5
3
1 2 3
10 -5 -3
4
2 8 5 3
1 10 3 4```

### 输出

```
-5
16
29```

# 题解

## 作者：OrientDragon (赞：3)

# 题意

[题目传送门](https://www.luogu.com.cn/problem/CF2046A)

# 分析

我们的路径**一定**是这样的：

|O|$\cdots $O$\cdots$|O|X|X|
|:-:|:-:|:-:|:-:|:-:|
|**X**|**X**|**O**|$\cdots $**O**$\cdots$|**O**|

不难发现，其中**有且只有一列，它的两个元素都在路径上。** 我们可以枚举这样的一列（称为第 $k$ 列），然后贪心处理其他列：

> 对于其他列，我们选择两个元素的较大值。
>
> + 若第一行元素较大，放在第 $k$ 列左侧；
> + 若第二行元素较大，放在第 $k$ 列右侧。

这样，我们就 $\Theta(n^2)$ 地通过了此题。

优化也很显然：我们发现，时间复杂度瓶颈在枚举 $k$ 上。于是，我们引发思考：能否利用贪心的思想，在线性的时间内求出 $k$ 呢？

如果我们不选择第 $k$ 列为特殊的那一列（而选择了第 $i$ 列），我们损失了 $\min(a_{1,k},a_{2,k})$，得到了 $\min(a_{1,i},a_{2,i})$。因此，我们要最大化 $\min(a_{1,k},a_{2,k})$，这样，当我们不选择 $k$ 时，一定是不优的。因此，第 $k$ 列也可以 $\Theta (n)$ 求出。

# 实现

实现很简单：分别求出 $\displaystyle \sum\limits_{i=1}^n \max(a_{1,i},a_{2,i})$ 和 $\displaystyle \max\limits_{i=1}^n(\min(a_{1,i},a_{2,i}))$，并加起来。

~~代码应该很简单吧。~~

---

## 作者：the_Short_Path (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2046A)
### 思路
在矩阵里，我们只能向下走一次（因为只有两行）。

所以我们可以遍历数组，每一列都设为向下走的列，取答案最大值。

同时，我们可以无限制交换列，所以除了被设为向下走的列两个值都取外，都可取二者的最小值。
### CODE
``` cpp
#include <bits/stdc++.h>
using namespace std;
long long ans, n, a[5005][2];
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i][1];
        for (int i = 1; i <= n; i++) cin >> a[i][2]; // 注意读入方式
        ans = -2e9;
        for (int i = 1; i <= n; i++) { //设 i 为向下走的点并枚举
            long long sum = a[i][1] + a[i][2];
            for (int j = 1; j <= n; j++) if (i != j) sum += max(a[j][1], a[j][2]);
            ans = max(ans, sum);
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：z_yq (赞：0)

# 题目意思
讲的十分清晰，没有什么可以继续描述的了。
# 做法
我们充分发掘特征。\
可以发现，我们在这个矩阵里面走动的时候只有一个时间点我们有可能往下走，那我们就假设这个点为 $x$，那么想一想就可以发现，在 $x$ 这一张牌上面的两个数都会被选到，然而其他的牌却只能最多选择一个，因为题目要求选择出来的结果最大，所以选择的这一个必须是两个数字最大的那个。\
那么做法就显而易见了，首先我们枚举这个 $x$ 用来寻找 $x$ 这张牌，然后我们把除了 $x$ 的其他牌的两个数的最大值加起来，加上 $x$ 上面的两个数字，就是我们在 $x$ 这个位置的最大结果，最后我们把答案取最大值就可以了，还有不理解可以借助代码理解。
# 做法
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=5e3+9;
ll sum,maxx,tmpsum,n,a[N],b[N];
inline void solve(){
    cin>>n;
    maxx=INT_MIN;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cin>>b[i];
    for(int i=1;i<=n;i++){
        tmpsum=a[i]+b[i];
        for(int j=1;j<=n;j++){
            if(j==i)continue;
            tmpsum+=max(a[j],b[j]);
        }
        maxx=max(maxx,tmpsum);
    }
    cout<<maxx<<endl;
}
int main(){
    int T;
    cin>>T;
    while(T--){solve();}
    return 0;
}
```

---

