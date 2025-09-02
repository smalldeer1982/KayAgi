# 题目信息

# Array Division

## 题目描述

Vasya has an array $ a $ consisting of positive integer numbers. Vasya wants to divide this array into two non-empty consecutive parts (the prefix and the suffix) so that the sum of all elements in the first part equals to the sum of elements in the second part. It is not always possible, so Vasya will move some element before dividing the array (Vasya will erase some element and insert it into an arbitrary position).

Inserting an element in the same position he was erased from is also considered moving.

Can Vasya divide the array after choosing the right element to move and its new position?

## 说明/提示

In the first example Vasya can move the second element to the end of the array.

In the second example no move can make the division possible.

In the third example Vasya can move the fourth element by one position to the left.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
2 2 3 4 5
```

### 输出

```
YES
```

# AI分析结果

### 题目内容
# 数组划分

## 题目描述
Vasya 有一个由正整数组成的数组 $a$。Vasya 想把这个数组分成两个非空的连续部分（前缀和后缀），使得第一部分所有元素的和等于第二部分元素的和。但这并不总是可行的，所以 Vasya 会在划分数组之前移动某个元素（Vasya 会删除某个元素并将其插入到任意位置）。
将元素插入到它被删除的相同位置也被视为移动。
Vasya 在选择正确的元素进行移动及其新位置后，能否划分该数组？

## 说明/提示
在第一个示例中，Vasya 可以将第二个元素移动到数组的末尾。
在第二个示例中，任何移动都无法使划分成为可能。
在第三个示例中，Vasya 可以将第四个元素向左移动一个位置。

## 样例 #1
### 输入
```
3
1 3 2
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5
2 2 3 4 5
```
### 输出
```
YES
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路大多是先计算数组总和，若总和为奇数则直接判定无法划分；若为偶数，则通过枚举数组的分割点，同时维护前缀和与后缀和，根据前缀和与总和一半的大小关系，判断是否能通过移动一个元素使得两部分和相等。主要难点在于如何高效地判断所需移动的元素是否存在，多数题解使用 `map` 来记录元素及其出现次数，从而优化查找过程。

### 所选的题解
- **作者：ZZQF5677 (赞：7)  星级：5星  关键亮点：思路清晰，代码简洁，通过两个 `map` 分别维护前后两段数字，逻辑严谨**
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 100005;
map<ll, int> mpl, mpr; //分别表示两端数字。
map<ll, int>::iterator it;
int n, a[maxn];
ll sum, ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
    mpr[a[i]]++;
  }
  if (sum % 2) { //sum如果是奇数那就肯定不能了。
    cout << "NO\n";
    return 0;
  }
  int flag = 0;
  sum = sum / 2;
  for (int i = 1; i <= n; i++) {
    ans += a[i]; //累计进前缀和。
    if (ans == sum) {
      flag = 1;
      break;
    }
    mpl[a[i]]++;
    mpr[a[i]]--;
    if (ans > sum && mpl[ans - sum]) {
      flag = 1;
      break;
    }
    if (ans < sum && mpr[sum - ans]) {
      flag = 1;
      break;
    }
  }
  if (flag) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
  return 0;
}
```
核心实现思想：先读入数组并计算总和，若总和为奇数输出 `NO`。否则，将总和除以2，遍历数组，累计前缀和，同时更新前后两段数字的 `map`，根据前缀和与总和一半的关系，在前缀或后缀的 `map` 中查找是否存在合适的元素可移动以满足划分条件。

- **作者：EdenSky (赞：4)  星级：4星  关键亮点：详细分析了思路和可能出现的错误情况，代码使用 `map` 结合 `vector` 记录元素位置，能准确判断元素所在区间**
```cpp
#define by_wanguan
#include<iostream>
#include<map>
#include<vector>
#define int long long
#define pb emplace_back
#define end cout<<"YES",exit(0)
using namespace std;
const int N=1e5+7;
int n,a[N],sum,p,s1,s2;
map<int,vector<int>> vis;
inline int abs(int &a,int &b){
  if(a>b) return a-b;
  else return b-a;
} 
signed main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)
    cin>>a[i],sum+=a[i],vis[a[i]].pb(i);
    //记录a中a[i]出现的位置，方便后续判断abs(s2-s1)/2是否在区间内
  s2=sum,s1=0;
  for(p=0;p<=n+1;p++){//枚举左右区间分界线
    s1+=a[p],s2-=a[p];
    if(abs(s2-s1)%2!=0) continue;
    if(s1==s2) end;
    auto &pe=vis[abs(s2-s1)/2];
    if(s1<s2)
      {if(!pe.empty()&&pe.back()>p) end;}
      //由于上面的位置记录时单调的，只需要取最靠后面的位置就能判断右区间内是否有abs(s2-s1)/2
      //下面同理
    if(s1>s2)
      {if(!pe.empty()&&pe.front()<=p) end;}
  }
  cout<<"NO";
}
```
核心实现思想：读入数组并记录每个元素及其位置，初始化前后缀和。枚举分割点，更新前后缀和，判断前后缀和差值的一半是否为偶数且该元素是否在合适区间内，若满足则输出 `YES`。

- **作者：Tx_Lcy (赞：3)  星级：4星  关键亮点：思路简洁明了，代码实现直接，通过 `map` 统计元素，根据前缀和与总和一半的三种情况进行判断**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int a[N];
map<int,int>mp,mpp;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,sum=0,sum1=0;cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i],sum+=a[i],++mpp[a[i]];
    if (sum&1) return cout<<"NO\n",0;
    int exp=sum/2;
    for (int i=1;i<=n;++i){
        sum1+=a[i];++mp[a[i]];--mpp[a[i]];
        if (sum1==exp) return cout<<"YES\n",0;
        if (sum1<exp){
            if (mpp[exp-sum1]) return cout<<"YES\n",0;
        }
        if (sum1>exp){
            if (mp[sum1-exp]) return cout<<"YES\n",0;
        }
    }
    return cout<<"NO\n",0;
}
```
核心实现思想：读入数组并计算总和，若总和为奇数输出 `NO`。否则，将总和除以2，遍历数组累计前缀和，根据前缀和与总和一半的大小关系，在前缀或后缀的 `map` 中查找合适元素以判断是否能满足划分条件。

### 最优关键思路或技巧
使用 `map` 数据结构记录数组元素及其出现次数，在枚举分割点时，根据前缀和与总和一半的差值，快速判断是否存在可移动的元素使两部分和相等，优化了查找效率。

### 同类型题或类似算法套路拓展
此类题目通常围绕数组元素的组合与划分，关键在于通过合理的数据结构和枚举策略，高效判断是否满足特定的和或其他数学关系条件。常见的类似思路包括利用前缀和、后缀和辅助分析，以及使用哈希表（如 `map`）优化查找过程。

### 洛谷相似题目推荐
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟与简单数学分析，判断灯的开关状态，涉及枚举与位运算思想。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同购买方案枚举并贪心选择最优方案，与本题枚举判断思路类似。
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：通过计算平均数，枚举纸牌移动方式，使各堆纸牌数量相等，同样是数组元素划分与调整问题。 

---
处理用时：66.36秒