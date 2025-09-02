# 题目信息

# Remove Smallest

## 题目描述

You are given the array $ a $ consisting of $ n $ positive (greater than zero) integers.

In one move, you can choose two indices $ i $ and $ j $ ( $ i       \ne j $ ) such that the absolute difference between $ a_i $ and $ a_j $ is no more than one ( $ |a_i - a_j| \le 1 $ ) and remove the smallest of these two elements. If two elements are equal, you can remove any of them (but exactly one).

Your task is to find if it is possible to obtain the array consisting of only one element using several (possibly, zero) such moves or not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can perform the following sequence of moves:

- choose $ i=1 $ and $ j=3 $ and remove $ a_i $ (so $ a $ becomes $ [2; 2] $ );
- choose $ i=1 $ and $ j=2 $ and remove $ a_j $ (so $ a $ becomes $ [2] $ ).

In the second test case of the example, we can choose any possible $ i $ and $ j $ any move and it doesn't matter which element we remove.

In the third test case of the example, there is no way to get rid of $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
1 2 2
4
5 5 5 5
3
1 2 4
4
1 3 4 4
1
100```

### 输出

```
YES
YES
NO
NO
YES```

# AI分析结果

### 题目内容
# 删除最小数

## 题目描述
给定一个由 $n$ 个正整数（大于零）组成的数组 $a$。
在一次操作中，你可以选择两个索引 $i$ 和 $j$（$i \ne j$），使得 $a_i$ 和 $a_j$ 的绝对差不超过 1（$|a_i - a_j| \le 1$），并删除这两个元素中较小的那个。如果两个元素相等，你可以删除其中任意一个（但只能删除一个）。
你的任务是判断是否有可能通过若干次（可能为零次）这样的操作，得到一个只包含一个元素的数组。
你需要回答 $t$ 个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，我们可以执行以下操作序列：
- 选择 $i = 1$ 和 $j = 3$ 并删除 $a_i$（因此 $a$ 变为 $[2; 2]$）；
- 选择 $i = 1$ 和 $j = 2$ 并删除 $a_j$（因此 $a$ 变为 $[2]$）。

在示例的第二个测试用例中，我们在任何一次操作中都可以选择任意可能的 $i$ 和 $j$，并且删除哪个元素都无关紧要。

在示例的第三个测试用例中，没有办法去掉 $2$ 和 $4$。

## 样例 #1
### 输入
```
5
3
1 2 2
4
5 5 5 5
3
1 2 4
4
1 3 4 4
1
100
```
### 输出
```
YES
YES
NO
NO
YES
```
### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为一致，都基于贪心策略。由于每次删除较小数，最后剩下的大概率是最大数。所以先对数组排序，然后检查相邻元素差值，若所有相邻元素差值都小于等于1，就意味着可以通过不断删除较小数，最终使数组只剩一个元素；若存在相邻元素差值大于1，则无法达成目标。各题解在具体实现上略有差异，但本质都是对排序后的数组进行相邻元素差值判断。

### 所选的题解
- **作者：引领天下 (5星)**
    - **关键亮点**：思路清晰，直接点明最后剩下的是最大数，通过排序后遍历判断非最大数能否删除，代码简洁明了。
    ```cpp
    #include <bits/stdc++.h>
    #define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
    #define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
    using namespace std;
    int t,n,a[55];
    int main(){
        scanf("%d",&t);
        while(t--){
            scanf("%d",&n);
            for(int i=1;i<=n;i++)scanf("%d",&a[i]);
            sort(a+1,a+n+1);bool ok=1;
            for(int i=n;i>1&&ok;i--)ok&=a[i]-a[i-1]<=1;
            puts(ok?"YES":"NO");
        }
        return 0;
    }
    ```
    - **核心实现思想**：先读入数据，对数组排序，然后从后往前遍历数组，判断相邻元素差值是否小于等于1，若都满足则可以得到只剩一个元素的数组，输出“YES”，否则输出“NO”。
- **作者：GBLoi (4星)**
    - **关键亮点**：详细分析题意，指出一个数只能被比它大的数删除，进而得出只要去掉相同值的有序序列满足所有相邻元素差值为1即可，实际操作优化为不用判断相同值。
    ```cpp
    #include<set>
    #include<map>
    #include<ctime>
    #include<queue>
    #include<stack>
    #include<vector>
    #include<cstdio>
    #include<cstdlib>
    #include<cstring>
    #include<iostream>
    #include<algorithm>
    #define LL long long
    #define rint register int
    using namespace std;
    const int N=56;
    int T;
    int n;
    int a[N];
    int main()
    {
    //	freopen("1.in","r",stdin);
        int i;
        scanf("%d",&T);
        while(T--) {
            scanf("%d",&n);
            for(i=1;i<=n;i++) 
                scanf("%d",&a[i]);
            sort(a+1,a+n+1);
            for(i=2;i<=n;i++) 
                if(a[i]-a[i-1]>1) break;
            if(i==n+1) puts("YES");
            else puts("NO");
        }
        return 0;
    }
    ```
    - **核心实现思想**：读入数据后排序，从第二个元素开始遍历数组，若发现相邻元素差值大于1则跳出循环，根据循环结束时的索引判断是否所有相邻元素差值都符合要求，从而输出相应结果。
- **作者：159号程序员 (4星)**
    - **关键亮点**：表述简洁，直接阐述思路为排序后比较相邻元素差值，通过计数来判断最终能否只剩一个元素。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int T, n, a[1000010];
    int main()
    {
        cin >> T;
        while(T--){
            cin >> n;
            for(int i = 1; i <= n; i++){
                scanf("%d", &a[i]);
            }
            sort(a + 1, a + n + 1);
            int sum = n;
            for(int i = 1; i <= n - 1; i++){
                if(a[i + 1] - a[i] <= 1){
                    sum--;
                }
            }
            if(sum <= 1){
                printf("%s\n", "YES");
            }
            else{
                printf("%s\n", "NO");
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：读入数据并排序，初始化计数器为数组长度，遍历数组比较相邻元素，若差值符合要求则计数器减1，最后根据计数器的值判断能否使数组只剩一个元素并输出结果。

### 最优关键思路或技巧
利用贪心策略，明确最后剩下的大概率是最大数，通过排序数组简化问题，只需要检查相邻元素差值是否满足条件，避免了复杂的操作模拟。

### 可拓展之处
同类型题通常围绕元素操作和条件判断，类似套路是对数据进行排序后，根据给定的操作条件检查相邻元素关系。比如一些关于序列合并、删除元素使序列满足特定条件的题目。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录
无。 

---
处理用时：51.81秒