# 题目信息

# [USACO07JAN] Tallest Cow S

## 题目描述

FarmerJohn 有n头牛，它们按顺序排成一列。FarmerJohn 只知道其中最高的奶牛的序号及它的高度，其他奶牛的高度都是未知的。现在 FarmerJohn 手上有 $R$ 条信息，每条信息上有两头奶牛的序号（$a$ 和 $b$），其中 $b$ 奶牛的高度一定大于等于 $a$ 奶牛的高度，且 $a, b$之间的所有奶牛的高度都比 $a$ 小。现在 FarmerJohn 想让你根据这些信息求出每一头奶牛的可能的最大的高度。（数据保证有解）

## 说明/提示

$1 \le n \le 10000$，$1 \le h \le 1000000$，$0 \le R \le 10000$

Translate provided by @酥皮

## 样例 #1

### 输入

```
9 3 5 5
1 3
5 3
4 3
3 7
9 8```

### 输出

```
5
4
5
3
4
4
5
5
5```

# AI分析结果

• 综合分析与结论：
    - 思路方面：多数题解采用将每对可对视奶牛（a, b）中间的奶牛高度减1的方式，最终得出每头奶牛可能的最大高度。部分题解运用差分思想，将区间操作转化为端点操作，通过前缀和得到结果，有效降低时间复杂度；还有题解使用拓扑排序结合线段树优化建边，但实现相对复杂。
    - 算法要点：核心在于处理区间关系，通过不同方式对区间操作进行优化。如利用map或二维数组等方式判重，避免重复操作。
    - 解决难点：主要难点是高效处理大量区间信息，避免重复操作以及优化时间和空间复杂度。
    - 整体来看，运用差分和前缀和思想的题解在思路清晰度、代码可读性和优化程度上表现较好。

所选的题解：
  - 作者：追梦_Chen (赞：25)  星级：5星
    - 关键亮点：清晰阐述差分思想，利用map巧妙实现二维数组判重，将区间操作转化为对两个端点操作，大大优化时间复杂度，代码简洁明了。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>	
#include <utility>
using namespace std;
int d[100005];      			 //牛
int n,l,h,r;
int x,y;
map<pair<int,int>,bool>book;   //由两个Int类型的映射bool数组

int main(){
    scanf("%d%d%d%d",&n,&l,&h,&r);
    for(int i=1;i<=r;i++){
        scanf("%d%d",&x,&y);    
        if(x>y)  swap(x,y);   //当x>y时记得交换
        if(book[make_pair(x,y)])    continue;  //判重
        d[x+1]--;   //前缀和操作
        d[y]++;    
        book[make_pair(x,y)]=true;
    }
    for(int i=1;i<=n;i++){
        d[i]=d[i-1]+d[i];            
        printf("%d\n",h+d[i]);
    }
    return 0;
}
```
核心思想是利用差分思想，对于每对输入的(x, y)，在x + 1处减1，y处加1，通过前缀和数组d计算出每头牛相对最高牛高度的变化量，最后加上最高牛的高度h得到每头牛的高度。

  - 作者：maple_tzc (赞：4)  星级：4星
    - 关键亮点：代码简洁，同样利用差分和前缀和优化，逻辑清晰，对思路解释详细。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[10010],d[10010];
map<pair<int,int>,bool> eee;
int main(){
	int n,p,h,m;
	scanf("%d%d%d%d",&n,&p,&h,&m);
	for (int i=1; i<=m; i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		if (eee[make_pair(a,b)]) continue;
		d[a+1]--,d[b]++;
		eee[make_pair(a,b)]=true;
	}
	for (int i=1; i<=n; i++){
		c[i]=c[i-1]+d[i];
		printf("%d\n",h+c[i]);
	}
	cout<<endl;
	return 0;
}
```
核心思想与追梦_Chen的类似，通过差分数组d记录每对(a, b)对中间奶牛高度的影响，再通过前缀和数组c计算出每头牛相对最高牛高度的变化，最后加上最高牛高度h得到每头牛的高度，并利用map判重。

  - 作者：小年轻w (赞：8)  星级：4星
    - 关键亮点：将问题类比为括号序列，形象易懂，利用map判重，代码实现简洁清晰。
    - 个人心得：无
    - 重点代码及核心思想：
```cpp
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 100001 ;
map<int,int> mp[maxn] ;
int n,m,id,h,x,y ;
int f[maxn] ;
int main()
{
    scanf("%d%d%d%d",&n,&id,&h,&m ) ;
    for(int i=1;i<=m;i++) 
    {
        scanf("%d%d",&x,&y);
        if(x>y) swap(x,y); 
        if(mp[x][y]) continue ;
            else mp[x][y]=1 ;
        f[x+1]--;   f[y]++;
    }
    for(int i=1;i<=n;i++) 
    {
        f[i] = f[i]+f[i-1] ;
        printf("%d\n",f[i]+h) ;
    }
    return 0;
}
```
核心思想是把每对可对视奶牛(x, y)类比为括号序列，在x + 1处减1，y处加1，通过数组f记录变化，再通过前缀和计算每头牛相对最高牛高度的变化，最后加上最高牛高度h得到每头牛的高度，同时利用map判重。

最优关键思路或技巧：利用差分和前缀和的思想，将对区间的操作转化为对端点的操作，从而降低时间复杂度，同时结合map等方式进行判重，避免重复操作。

可拓展之处：同类型题常考察区间操作的优化，类似算法套路可应用于处理具有区间关系的问题，如区间增减、区间统计等。

推荐题目：
 - P1972 [SDOI2009]HH的项链：涉及区间统计，可通过类似前缀和等思想优化。
 - P3374 【模板】树状数组 1：树状数组是处理前缀和、区间操作的常用数据结构，与本题差分思想有相通之处。
 - P1115 最大子段和：虽然不是区间操作，但在处理连续一段数据的最值问题上，与本题对区间关系处理有类似思维方式。

个人心得摘录与总结：无。 

---
处理用时：38.33秒