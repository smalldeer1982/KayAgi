# 题目信息

# Chip and Ribbon

## 题目描述

There is a ribbon divided into $ n $ cells, numbered from $ 1 $ to $ n $ from left to right. Initially, an integer $ 0 $ is written in each cell.

Monocarp plays a game with a chip. The game consists of several turns. During the first turn, Monocarp places the chip in the $ 1 $ -st cell of the ribbon. During each turn except for the first turn, Monocarp does exactly one of the two following actions:

- move the chip to the next cell (i. e. if the chip is in the cell $ i $ , it is moved to the cell $ i+1 $ ). This action is impossible if the chip is in the last cell;
- choose any cell $ x $ and teleport the chip into that cell. It is possible to choose the cell where the chip is currently located.

At the end of each turn, the integer written in the cell with the chip is increased by $ 1 $ .

Monocarp's goal is to make some turns so that the $ 1 $ -st cell contains the integer $ c_1 $ , the $ 2 $ -nd cell contains the integer $ c_2 $ , ..., the $ n $ -th cell contains the integer $ c_n $ . He wants to teleport the chip as few times as possible.

Help Monocarp calculate the minimum number of times he has to teleport the chip.

## 说明/提示

In the first test case of the example, Monocarp can perform the turns as follows:

- place the chip in the $ 1 $ -st cell; the numbers in the cells are $ [1, 0, 0, 0] $ ;
- move the chip to the next ( $ 2 $ -nd) cell; the numbers in the cells are $ [1, 1, 0, 0] $ ;
- move the chip to the next ( $ 3 $ -rd) cell; the numbers in the cells are $ [1, 1, 1, 0] $ ;
- teleport the chip to the $ 2 $ -nd cell; the numbers in the cells are $ [1, 2, 1, 0] $ ;
- move the chip to the next ( $ 3 $ -rd) cell; the numbers in the cells are $ [1, 2, 2, 0] $ ;
- move the chip to the next ( $ 4 $ -th) cell; the numbers in the cells are $ [1, 2, 2, 1] $ .

## 样例 #1

### 输入

```
4
4
1 2 2 1
5
1 0 1 0 1
5
5 4 3 2 1
1
12```

### 输出

```
1
2
4
11```

# AI分析结果

### 题目内容（中文重写）
# 芯片与丝带

## 题目描述
有一条被分成 $n$ 个格子的丝带，格子从左到右依次编号为 $1$ 到 $n$。初始时，每个格子里都写着整数 $0$。

Monocarp 用一个芯片玩游戏。游戏由若干轮组成。在第一轮中，Monocarp 将芯片放在丝带的第 $1$ 个格子里。在除第一轮之外的每一轮中，Monocarp 恰好执行以下两个操作之一：
- 将芯片移动到下一个格子（即，如果芯片在第 $i$ 个格子，就将其移动到第 $i + 1$ 个格子）。如果芯片在最后一个格子，则此操作不可行。
- 选择任意一个格子 $x$，并将芯片传送到该格子。也可以选择芯片当前所在的格子。

在每一轮结束时，芯片所在格子里的整数会增加 $1$。

Monocarp 的目标是通过进行若干轮操作，使得第 $1$ 个格子里的整数为 $c_1$，第 $2$ 个格子里的整数为 $c_2$，……，第 $n$ 个格子里的整数为 $c_n$。他希望尽可能少地传送芯片。

请帮助 Monocarp 计算他至少需要传送芯片多少次。

## 说明/提示
在示例的第一个测试用例中，Monocarp 可以按以下步骤进行操作：
- 将芯片放在第 $1$ 个格子；此时格子里的数字为 $[1, 0, 0, 0]$；
- 将芯片移动到下一个（第 $2$ 个）格子；此时格子里的数字为 $[1, 1, 0, 0]$；
- 将芯片移动到下一个（第 $3$ 个）格子；此时格子里的数字为 $[1, 1, 1, 0]$；
- 将芯片传送到第 $2$ 个格子；此时格子里的数字为 $[1, 2, 1, 0]$；
- 将芯片移动到下一个（第 $3$ 个）格子；此时格子里的数字为 $[1, 2, 2, 0]$；
- 将芯片移动到下一个（第 $4$ 个）格子；此时格子里的数字为 $[1, 2, 2, 1]$。

## 样例 #1
### 输入
```
4
4
1 2 2 1
5
1 0 1 0 1
5
5 4 3 2 1
1
12
```
### 输出
```
1
2
4
11
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是将原问题转化为一个更易处理的问题，即每次选择一个区间全部加 $1$，求最少多少次操作后能得到目标数组，最后答案减 $1$。不同题解在具体表述和实现细节上略有差异，但整体算法要点都是计算相邻元素差值的正数部分之和。

### 所选题解
- 作者：zhangshuhang2011（4星）
  - 关键亮点：思路清晰，通过柱状图“切片”的方式形象地解释了算法原理，代码简洁明了。
  - 个人心得：提醒不开 `long long` 会爆 `int`，因为答案最大可达 $10^{14}$ 数量级。
- 作者：WsW_（4星）
  - 关键亮点：将问题巧妙地转化为经典的 [积木大赛](https://www.luogu.com.cn/problem/P1969) 问题，逻辑清晰，代码规范。
  - 个人心得：无。
- 作者：what_can_I_do（4星）
  - 关键亮点：详细解释了算法的贪心策略，从利益最大化的角度分析了相邻元素差值的意义，代码实现简洁。
  - 个人心得：无。

### 重点代码
#### 作者：zhangshuhang2011
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[200005], ans;
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    a[0] = 0; ans = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] > a[i-1]){
            ans += a[i] - a[i-1];
        }
    }
    cout << ans-1 << endl;
}
signed main(){
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}
```
核心实现思想：先读取输入的数组，然后遍历数组，当当前元素大于前一个元素时，将它们的差值累加到答案中，最后输出答案减 $1$。

#### 作者：WsW_
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
int n,c[200003];
ll sum;

void work(){
    cin>>n;
    sum=0;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        sum+=max(c[i]-c[i-1],0);
    }
    cout<<sum-1<<'\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--)work();
    return 0;
}
```
核心实现思想：读取输入的数组，在读取过程中计算相邻元素差值的正数部分之和，最后输出该和减 $1$。

#### 作者：what_can_I_do
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
long long a[2000010];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        long long ans=0;
        scanf("%d",&n);
        for(register int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(register int i=1;i<=n;i++) ans+=max(a[i]-a[i-1],1ll*0);
        printf("%lld\n",ans-1);
    }
    return 0;
}
```
核心实现思想：读取输入的数组，遍历数组计算相邻元素差值的正数部分之和，最后输出该和减 $1$。

### 关键思路或技巧
- **问题转化**：将原问题转化为每次选择一个区间全部加 $1$ 的问题，简化了问题的复杂度。
- **贪心策略**：通过计算相邻元素的差值，确定每次需要额外操作的次数，从而得到最少的操作次数。

### 拓展思路
同类型题或类似算法套路：这类问题通常可以通过贪心策略解决，关键在于找到一种最优的操作方式，使得在满足条件的前提下操作次数最少。例如，在一些区间修改、区间覆盖的问题中，也可以采用类似的贪心思想。

### 推荐题目
- [P1969 [NOIP2013 提高组] 积木大赛](https://www.luogu.com.cn/problem/P1969)
- [P5019 [NOIP2018 提高组] 铺设道路](https://www.luogu.com.cn/problem/P5019)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)

---
处理用时：41.94秒