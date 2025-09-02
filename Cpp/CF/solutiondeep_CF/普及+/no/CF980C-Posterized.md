# 题目信息

# Posterized

## 题目描述

Professor Ibrahim has prepared the final homework for his algorithm’s class. He asked his students to implement the Posterization Image Filter.

Their algorithm will be tested on an array of integers, where the $ i $ -th integer represents the color of the $ i $ -th pixel in the image. The image is in black and white, therefore the color of each pixel will be an integer between 0 and 255 (inclusive).

To implement the filter, students are required to divide the black and white color range \[0, 255\] into groups of consecutive colors, and select one color in each group to be the group’s key. In order to preserve image details, the size of a group must not be greater than $ k $ , and each color should belong to exactly one group.

Finally, the students will replace the color of each pixel in the array with that color’s assigned group key.

To better understand the effect, here is an image of a basking turtle where the Posterization Filter was applied with increasing $ k $ to the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF980C/a5e04b9b80b48f601f9e0b203cd8ee3718afd0e4.png)To make the process of checking the final answer easier, Professor Ibrahim wants students to divide the groups and assign the keys in a way that produces the lexicographically smallest possible array.

## 说明/提示

One possible way to group colors and assign keys for the first sample:

Color $ 2 $ belongs to the group $ [0,2] $ , with group key $ 0 $ .

Color $ 14 $ belongs to the group $ [12,14] $ , with group key $ 12 $ .

Colors $ 3 $ and $ 4 $ belong to group $ [3, 5] $ , with group key $ 3 $ .

Other groups won't affect the result so they are not listed here.

## 样例 #1

### 输入

```
4 3
2 14 3 4
```

### 输出

```
0 12 3 3
```

## 样例 #2

### 输入

```
5 2
0 2 1 255 254
```

### 输出

```
0 1 1 254 254
```

# AI分析结果

### 题目内容
# 图像色调分离

## 题目描述
易卜拉欣教授为他的算法课程准备了期末考试作业。他要求学生实现图像色调分离滤镜。

他们的算法将在一个整数数组上进行测试，其中第 $i$ 个整数表示图像中第 $i$ 个像素的颜色。该图像为黑白图像，因此每个像素的颜色将是介于0到255之间（包含0和255）的整数。

为了实现该滤镜，学生需要将黑白颜色范围 \[0, 255\] 划分为连续颜色的组，并在每个组中选择一种颜色作为该组的关键色。为了保留图像细节，一个组的大小不得大于 $k$，并且每种颜色应恰好属于一个组。

最后，学生将用该颜色所属组的关键色替换数组中每个像素的颜色。

为了更好地理解效果，这里有一张晒太阳的乌龟的图像，右边是应用了逐渐增大的 $k$ 值的色调分离滤镜后的效果。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF980C/a5e04b9b80b48f601f9e0b203cd8ee3718afd0e4.png)
为了使检查最终答案的过程更容易，易卜拉欣教授希望学生以一种能产生字典序最小的数组的方式来划分组并分配关键色。

## 说明/提示
对于第一个样例，一种可能的分组和分配关键色的方式如下：
颜色2属于组 \[0, 2\]，组关键色为0。
颜色14属于组 \[12, 14\]，组关键色为12。
颜色3和4属于组 \[3, 5\]，组关键色为3。
其他组不会影响结果，因此这里未列出。

## 样例 #1
### 输入
```
4 3
2 14 3 4
```
### 输出
```
0 12 3 3
```

## 样例 #2
### 输入
```
5 2
0 2 1 255 254
```
### 输出
```
0 1 1 254 254
```

### 算法分类
贪心

### 综合分析与结论
这几道题解思路基本一致，均采用贪心策略。核心思路是为使变换后的数组字典序最小，让每个数尽量取其可归属区间内的最小值。算法要点在于遍历数组中的每个数，根据其能否与前面已处理数合并分组来确定其所属组及关键色。解决难点主要在于处理分组边界情况，如判断前面数的分组状态、确保组大小不超过 $k$ 等。

### 所选的题解
- **作者：Aragron_II (赞：4)  星级：4星**
    - **关键亮点**：思路清晰，代码简洁。通过数组 `a` 记录每个颜色对应的组关键色，初始化 `-1` 表示未分组。遍历输入数组，对每个未分组颜色，从其往前找可合并的组，若找到合适组则更新组内所有颜色的关键色。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,p[100005],a[300];
int main() {
    memset(a,-1,sizeof(a)); 
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>p[i]; 
    for(int i=0;i<n;i++) {
        if(a[p[i]]==-1) {
            int t=max(0,p[i]-k+1);
            for(int j=t;j<=p[i];j++) { 
                if((a[j]==-1)||(p[i]-a[j])<k) {
                    for(int k=j;k<=p[i];k++)
                        a[k]=j; 
                    break; 
                }
            }
        }
    }
    for(int i=0;i<n;i++) 
        cout<<a[p[i]]<<' ';
    return 0;
}
```
核心实现思想：遍历输入数组 `p`，对每个元素 `p[i]`，若其对应 `a[p[i]]` 为 `-1` 即未分组，从 `max(0, p[i] - k + 1)` 到 `p[i]` 遍历找可合并组，若找到合适组（`a[j]` 未分组或 `p[i] - a[j] < k`），则将从 `j` 到 `p[i]` 的颜色关键色设为 `j`。
- **作者：きりと (赞：3)  星级：4星**
    - **关键亮点**：利用 `map` 和布尔数组 `f` 实现分组。`map` 记录每个颜色对应的组关键色，`f` 标记颜色是否已分组。思路清晰，逻辑明确。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=257;
int p[N];
map<int,int>mp;
bool f[N];
signed main()
{
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>p[i];
    }
    for(int i=0;i<n;i++)
    {
        if(!f[p[i]])
        {
            for(int j=max(0,p[i]-k+1);j<=p[i];j++)
            {
                if(!f[j]||(p[i]-mp[j])<k)
                {
                    for(int k=j;k<=p[i];k++)
                    {
                        f[k]=1;
                        mp[k]=j;
                    }
                    break;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<mp[p[i]]<<" ";
    }
    return 0;
}
```
核心实现思想：遍历输入数组 `p`，对每个未分组的 `p[i]`（`!f[p[i]]`），从 `max(0, p[i] - k + 1)` 到 `p[i]` 找可合并组，若找到（`!f[j]` 或 `p[i] - mp[j] < k`），则将从 `j` 到 `p[i]` 的颜色标记为已分组并更新其组关键色为 `j`。
- **作者：流绪 (赞：0)  星级：4星**
    - **关键亮点**：通过对边界情况的细致处理实现贪心策略。利用数组 `b` 记录每个颜色对应的组关键色，初始化 `-1` 表示未处理。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x7f7f7f7f
using namespace std;
int a[1000010],b[266];
int main()
{
    ios::sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    memset(b,-1,sizeof(b));
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
        if(b[a[i]] == -1)
        {
            int x;
            if(a[i] <= k-1)
                x=0;
            else
                x=a[i]-k+1;
            while(b[x]!=-1&&a[i]>b[x]+k-1)
                x++;
            if(b[x]!= -1)
                x = b[x]; 
            for(int j=a[i];~j&&j>=x;j--)
                b[j] = x;
        }
    }
    cout << b[a[1]] << " ";
    for(int i=2;i<=n;i++)
        cout << b[a[i]] << " ";
} 
```
核心实现思想：遍历输入数组 `a`，对每个未处理的 `a[i]`（`b[a[i]] == -1`），先确定其可能的最小关键色 `x`，若 `x` 已被占用且不包含 `a[i]`，则增大 `x`，若 `x` 已被占用但能包含 `a[i]` 则直接用 `x`，最后将从 `a[i]` 到 `x` 的颜色关键色设为 `x`。

### 最优关键思路或技巧
采用贪心策略，在遍历数组时，每次都让当前数取其可归属区间内的最小数作为组关键色，通过对每个数进行分组判断和更新，保证最终数组字典序最小。在实现过程中，要注意处理分组边界条件，如组大小限制、前面数的分组状态等。

### 可拓展之处
同类型题可考虑其他图像滤镜效果实现，或类似的数组分组优化问题，其算法套路通常围绕贪心思想，根据题目限制条件确定如何让结果最优。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

### 个人心得
暂未发现题解中有个人心得相关内容。 

---
处理用时：53.90秒