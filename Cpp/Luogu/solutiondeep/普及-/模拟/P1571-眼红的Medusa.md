# 题目信息

# 眼红的Medusa

## 题目描述

虽然 Miss Medusa 到了北京，领了科技创新奖，但是她还是觉得不满意。原因是：他发现很多人都和她一样获了科技创新奖，特别是其中的某些人，还获得了另一个奖项——特殊贡献奖。而越多的人获得了两个奖项，Miss Medusa就会越眼红。于是她决定统计有哪些人获得了两个奖项，来知道自己有多眼红。

## 说明/提示

对于 $60\%$ 的数据，$0 \leq n, m \leq 1000$，获得奖项的人的编号 $\lt 2 \times 10^9$；

对于 $100\%$ 的数据，$0 \leq n, m \leq 10^5$，获得奖项的人的编号 $\lt 2 \times 10^9$。

输入数据保证第二行任意两个数不同，第三行任意两个数不同。

## 样例 #1

### 输入

```
4 3
2 15 6 8
8 9 2
```

### 输出

```
2 8```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何高效找出同时获得科技创新奖和特殊贡献奖的人展开，数据范围较大，需避免暴力枚举导致超时。常见思路有使用map、二分查找及其相关变体、哈希表、平衡树等数据结构和算法。
1. **map思路**：将获得特殊贡献奖的人的编号建立映射关系，再遍历获得科技创新奖的人的编号，判断是否在映射中，时间复杂度为O(n + m)。
2. **二分查找思路**：先对获得特殊贡献奖的数组排序，再对获得科技创新奖的每个编号在排序后的数组中二分查找，时间复杂度为O(nlogm)。部分题解使用了STL中的binary_search、lower_bound等函数简化实现。
3. **哈希表思路**：通过取模将编号映射到较小空间，用拉链法解决冲突，期望时间复杂度接近O(n)。
4. **平衡树思路**：把获得特殊贡献奖的人插入平衡树，再在树中查找获得科技创新奖的人是否存在。

综合质量来看，多数题解思路清晰，但部分代码可读性和优化程度欠佳。

### 所选的题解
1. **作者：Christopher_Yan（5星）**
    - **关键亮点**：提供map和二分查找两种主流解法，思路清晰，代码简洁明了，对每种解法都有详细解释。
    - **个人心得**：虽题目标签为二分，但先想到map，因其简单好写，后按要求完成二分查找解法。
    - **重点代码 - map做法**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
map<int,bool> v;
int a[101000],b[101000];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]);}
    for(int i=1;i<=m;i++) {scanf("%d",&b[i]);v[b[i]]=true;}//建立映射关系
    for(int i=1;i<=n;i++) if(v[a[i]]) cout<<a[i]<<" ";//如果出现过直接输出
    return 0;
}
```
核心思想：利用map建立获得特殊贡献奖编号的映射，遍历科技创新奖编号判断是否在map中。
    - **重点代码 - 枚举＋二分**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[101000],b[101000];
bool binary_search(int x)
{
    int l=1,r=m;
    while (l<=r)
    {
        int mid=(l+r)>>1;
        if (b[mid]==a[x])return 1;
        if (b[mid-1]<a[x]&&b[mid+1]>a[x])return 0;
        if (b[mid]>a[x])r=mid;
        else l=mid+1;
    }
    return 0;   
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    sort(b+1,b+1+m);
    for(int i=1;i<=n;i++) if(binary_search(i)) printf("%d ",a[i]);
    return 0;
}
```
核心思想：对特殊贡献奖数组排序后，对科技创新奖每个编号二分查找是否在其中。
2. **作者：Register（4星）**
    - **关键亮点**：代码简洁，利用STL中的binary_search函数解决问题，同时对该函数进行详细介绍，适合初学者理解二分查找的应用。
    - **重点代码**：
```cpp
#include <iostream>
#include <algorithm>//binary_search、sort
using namespace std;
int a[100001],b[100001],n,m;
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;i++) cin>>a[i];
    for(register int i=1;i<=m;i++) cin>>b[i];
    sort(b+1,b+m+1);//升序排列
    for(register int i=1;i<=n;i++)
        if(binary_search(b+1,b+m+1,a[i])) cout<<a[i]<<' ';//查找、输出
    cout<<endl;    
    return 0;
}
```
核心思想：对特殊贡献奖数组排序，用binary_search函数查找科技创新奖编号是否在其中。
3. **作者：Dfox（4星）**
    - **关键亮点**：解题思路清晰，代码简洁，先输入获奖选手序号，排序后利用binary_search函数进行二分查找，符合题目要求。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>  //可爱的万能头文件
using namespace std;
int main(){
    int a[10001],b[10001],c,d;
    cin>>c>>d;
    for(int i=1;i<=c;i++){
        cin>>a[i];//获得科技创新奖的人的编号
    } 
    for(int i=1;i<=d;i++){
        cin>>b[i]; //获得特殊贡献奖的人的编号
    } 
    sort(b+1,b+d+1);  //二分查找前先排序呦！
    for(int i=1;i<=c;i++){  //核心代码
        if(binary_search(b+1,b+d+1,a[i])){  //二分查找的函数
            cout<<a[i]<<' ';
        } 
    }
    cout<<endl; 
    return 0;
}
```
核心思想：与Register题解类似，排序后用binary_search查找同时获奖的编号。

### 最优关键思路或技巧
1. **数据结构选择**：map能简单快速建立映射关系，二分查找利用数组有序性提高查找效率，STL中的相关函数（如binary_search、lower_bound）简化了代码实现。哈希表在处理大数据范围时能通过取模和拉链法实现接近O(1)的查询。
2. **算法优化**：避免暴力枚举，利用数据的有序性和合适的数据结构降低时间复杂度。

### 可拓展之处
同类型题常考查在两个集合中查找共同元素，类似算法套路有利用排序和二分查找、哈希表映射等。如涉及范围查询可考虑线段树等数据结构。

### 推荐题目
1. **P2249 【深基13.例1】查找**：基础的二分查找应用题目。
2. **P3853 [TJOI2007]路标设置**：需要利用二分查找确定最优解。
3. **P1873 砍树**：通过二分查找解决最大化最小值问题。

### 个人心得摘录与总结
1. **Christopher_Yan**：先想到map的简单做法，后完成二分查找解法，反映出解题时从易到难，多种思路尝试的过程。
2. **引领天下**：因输出顺序问题被扣分，强调了注意题目细节的重要性。 

---
处理用时：55.77秒