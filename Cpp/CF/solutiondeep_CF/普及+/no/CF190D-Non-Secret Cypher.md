# 题目信息

# Non-Secret Cypher

## 题目描述

Berland starts to seize the initiative on the war with Flatland. To drive the enemy from their native land, the berlanders need to know exactly how many more flatland soldiers are left in the enemy's reserve. Fortunately, the scouts captured an enemy in the morning, who had a secret encrypted message with the information the berlanders needed so much.

The captured enemy had an array of positive integers. Berland intelligence have long been aware of the flatland code: to convey the message, which contained a number $ m $ , the enemies use an array of integers $ a $ . The number of its subarrays, in which there are at least $ k $ equal numbers, equals $ m $ . The number $ k $ has long been known in the Berland army so General Touristov has once again asked Corporal Vasya to perform a simple task: to decipher the flatlanders' message.

Help Vasya, given an array of integers $ a $ and number $ k $ , find the number of subarrays of the array of numbers $ a $ , which has at least $ k $ equal numbers.

Subarray $ a[i...\ j] (1<=i<=j<=n) $ of array $ a=(a_{1},a_{2},...,a_{n}) $ is an array, made from its consecutive elements, starting from the $ i $ -th one and ending with the $ j $ -th one: $ a[i...\ j]=(a_{i},a_{i+1},...,a_{j}) $ .

## 说明/提示

In the first sample are three subarrays, containing at least two equal numbers: (1,2,1), (2,1,2) and (1,2,1,2).

In the second sample are two subarrays, containing three equal numbers: (1,2,1,1,3) and (1,2,1,1).

In the third sample any subarray contains at least one 1 number. Overall they are 6: (1), (1), (1), (1,1), (1,1) and (1,1,1).

## 样例 #1

### 输入

```
4 2
1 2 1 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
5 3
1 2 1 1 3
```

### 输出

```
2```

## 样例 #3

### 输入

```
3 1
1 1 1
```

### 输出

```
6```

# AI分析结果

### 题目内容
# 非秘密密码

## 题目描述
贝克兰德在与弗拉特兰的战争中开始掌握主动权。为了将敌人赶出自己的国土，贝克兰德人需要确切知道敌人预备队中还剩下多少弗拉特兰士兵。幸运的是，侦察兵在早上抓获了一名敌人，他身上有一条秘密加密信息，而贝克兰德人急需这条信息中的内容。

被抓获的敌人有一个正整数数组。贝克兰德情报部门早就知道弗拉特兰的编码方式：为了传达包含数字 $m$ 的信息，敌人会使用一个整数数组 $a$。数组中至少有 $k$ 个相等数字的子数组的数量就等于 $m$。$k$ 这个数字在贝克兰德军队中早已为人所知，所以图里索夫将军再次要求下士瓦夏完成一项简单的任务：破解弗拉特兰人的信息。

请帮助瓦夏，给定一个整数数组 $a$ 和数字 $k$，找出数组 $a$ 中至少有 $k$ 个相等数字的子数组的数量。

数组 $a=(a_{1},a_{2},...,a_{n})$ 的子数组 $a[i...\ j] (1<=i<=j<=n)$ 是由其连续元素组成的数组，从第 $i$ 个元素开始，到第 $j$ 个元素结束：$a[i...\ j]=(a_{i},a_{i + 1},...,a_{j})$。

## 说明/提示
在第一个样例中，有三个子数组包含至少两个相等的数字：(1,2,1)，(2,1,2) 和 (1,2,1,2)。

在第二个样例中，有两个子数组包含三个相等的数字：(1,2,1,1,3) 和 (1,2,1,1)。

在第三个样例中，任何子数组都至少包含一个 1。总共有 6 个：(1)，(1)，(1)，(1,1)，(1,1) 和 (1,1,1)。

## 样例 #1
### 输入
```
4 2
1 2 1 2
```
### 输出
```
3```

## 样例 #2
### 输入
```
5 3
1 2 1 1 3
```
### 输出
```
2```

## 样例 #3
### 输入
```
3 1
1 1 1
```
### 输出
```
6```

### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路都是利用双指针法来优化暴力枚举，以降低时间复杂度。算法要点在于枚举区间左端点，同时维护满足至少有 $k$ 个相等数字这一条件的最靠左的区间右端点。由于一旦找到满足条件的区间 $[l,r]$，那么 $[l,r + 1] \sim [l,n]$ 也必然满足条件，所以对于当前左端点 $l$，可对答案贡献 $n - r + 1$。解决难点主要在于如何高效地判断子数组是否满足条件，题解中普遍使用 `map` 或桶来记录数字出现次数，同时在移动左指针时，能准确判断子数组是否由满足条件变为不满足。

### 所选的题解
- **作者：__yrq__ (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，准确地运用双指针法，清晰地阐述了每一步的操作和对答案的贡献方式。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int>mp;
int n,k,a[400005],r=1,s1=0;
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int l=1;l<=n;l++)
    {
        while(r<=n)
        {
        	if(mp[a[r]]+1>=k) break;
        	mp[a[r++]]++;
		}
        s1+=n-r+1;
        mp[a[l]]--;
    }
    cout<<s1<<endl;
    return 0;
}
```
    - **核心实现思想**：外层循环枚举左端点 $l$，内层 `while` 循环移动右端点 $r$，直到找到满足条件的位置，此时计算对答案的贡献，最后移动左端点并更新 `map` 中对应数字的出现次数。
- **作者：Luo_gu_ykc (4星)**
    - **关键亮点**：详细地分析了从暴力到双指针优化的过程，对时间复杂度的分析清晰，代码注释详细，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 4e5 + 5;

int n, k, a[N], ans, cnt;
map <int, int> sum; 

signed main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int l = 1, r = 0; l <= n && r <= n; l++){ 
        for(; cnt == 0 && r < n; ){ 
            r++; 
            sum[a[r]]++; 
            if(sum[a[r]] >= k){ 
                cnt++;
                break;
            }
        }
        if(cnt){ 
            ans += (n - r + 1); 
        }
        sum[a[l]]--; 
        if(sum[a[l]] == k - 1){ 
            cnt--;
        }
    }
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：通过 `cnt` 判断当前子数组是否满足条件，外层循环枚举左端点 $l$，内层循环移动右端点 $r$ 直至满足条件，满足时计算贡献，移动左端点时更新 `sum` 和 `cnt`。
- **作者：hinin (4星)**
    - **关键亮点**：解题思路描述详细，对双指针法的步骤进行了清晰的拆解，代码简洁且逻辑清晰。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define min(x, y) (x < y? x : y)
#define max(x, y) (x > y? x : y)
#define ll long long
 
using namespace std;

const int N = 4e5 +5;

bool flg = false; 
int n, k, l = 1, r, a[N];
ll ans; 
map<int, int> Map;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin  >> n >> k;
    for(int i = 1; i <= n; i++) { cin>>a[i]; }

    while(r <= n){
        if(flg){
            ans += n - r + 1;
            if(--Map[a[l++]] == k - 1) { flg = false; }
        } else {
            if(++Map[a[++r]] == k) { flg = true; }
        }
    }
    cout << ans << endl; 

    return 0;
}
```
    - **核心实现思想**：通过 `flg` 标记当前子数组是否满足条件，在 `while` 循环中根据 `flg` 移动指针并计算答案，移动指针时更新 `Map` 和 `flg`。

### 最优关键思路或技巧
利用双指针法优化暴力枚举，通过维护一个满足条件的最靠左的右端点，快速计算每个左端点对答案的贡献。同时使用 `map` 来灵活记录不同数字的出现次数，在移动指针时准确更新状态。

### 可拓展思路
同类型题目通常围绕子数组、子序列的特定条件计数展开，类似算法套路是利用双指针、滑动窗口等优化枚举过程，降低时间复杂度。例如给定一个数组，求满足元素和在某个范围内的子数组数量等题目。

### 洛谷相似题目
- [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
- [P2032 扫描](https://www.luogu.com.cn/problem/P2032)
- [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)

### 个人心得
暂未发现题解中有个人心得相关内容。 

---
处理用时：72.57秒