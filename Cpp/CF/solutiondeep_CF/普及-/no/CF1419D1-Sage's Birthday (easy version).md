# 题目信息

# Sage's Birthday (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that in the easy version all prices $ a_i $ are different. You can make hacks if and only if you solved both versions of the problem.

Today is Sage's birthday, and she will go shopping to buy ice spheres. All $ n $ ice spheres are placed in a row and they are numbered from $ 1 $ to $ n $ from left to right. Each ice sphere has a positive integer price. In this version all prices are different.

An ice sphere is cheap if it costs strictly less than two neighboring ice spheres: the nearest to the left and the nearest to the right. The leftmost and the rightmost ice spheres are not cheap. Sage will choose all cheap ice spheres and then buy only them.

You can visit the shop before Sage and reorder the ice spheres as you wish. Find out the maximum number of ice spheres that Sage can buy, and show how the ice spheres should be reordered.

## 说明/提示

In the example it's not possible to place ice spheres in any order so that Sage would buy $ 3 $ of them. If the ice spheres are placed like this $ (3, 1, 4, 2, 5) $ , then Sage will buy two spheres: one for $ 1 $ and one for $ 2 $ , because they are cheap.

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
2
3 1 4 2 5```

# AI分析结果

### 题目内容
# Sage的生日（简单版）

## 题目描述
这是该问题的简单版本。两个版本的区别在于，在简单版本中，所有价格 \(a_i\) 都不相同。只有当你解决了两个版本的问题时，才可以进行黑客攻击。

今天是Sage的生日，她要去购物买冰球。所有 \(n\) 个冰球排成一排，从左到右编号为 \(1\) 到 \(n\) 。每个冰球都有一个正整数价格。在这个版本中，所有价格都不同。

如果一个冰球的价格严格低于它相邻的两个冰球（最左边和最右边的冰球除外），那么这个冰球就是便宜的。Sage会选择所有便宜的冰球然后购买。

你可以在Sage之前去商店，随意重新排列冰球。找出Sage最多能买多少个冰球，并展示应该如何重新排列冰球。

## 说明/提示
在示例中，不可能以任何顺序放置冰球，使得Sage能购买 \(3\) 个冰球。如果冰球按这样放置 \((3, 1, 4, 2, 5)\) ，那么Sage会购买两个冰球：一个价格为 \(1\) 的和一个价格为 \(2\) 的，因为它们是便宜的。

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
2
3 1 4 2 5
```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是通过特定的构造方式，使得满足“价格严格低于相邻两个冰球”这一条件的冰球数量最多。
 - **思路方面**：多数题解都提到先对价格数组进行排序，然后采用大小交错放置的方式构造新序列。例如将较小的数依次放在偶数位置，较大的数依次放在奇数位置（或反之），从而形成尽可能多的中间低两边高的“山谷”结构。
 - **算法要点**：排序是为了方便按大小顺序选取数字进行构造；构造过程要注意数组下标的处理，确保数字放置位置符合要求；最后通过遍历新构造的序列来统计满足条件的冰球个数。
 - **解决难点**：主要难点在于如何想到有效的构造方法，使满足条件的冰球数量最大化。不同题解在构造细节和代码实现上略有差异，但本质思路一致。

### 所选的题解
 - **作者：king_xbz (赞：1)  4星**
    - **关键亮点**：思路清晰，明确指出要构造出最多的“山”字序列（中间低，两边高）为最优解，并详细说明了构造方法，即排序后把前 \(i/2\) 小的数从小到大放在偶数位上，剩下的从小到大依次放到奇数位上。代码简洁明了，易于理解。
    - **重点代码**：
```cpp
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    int cnt=0;
    for(int i=2;i<=n;i+=2)
        s[i]=a[++cnt];
    for(int i=1;i<=n;i+=2)
        s[i]=a[++cnt];
    int ans=0;
    for(int i=1;i<=n;i++)
        if(s[i]<s[i-1]&&s[i]<s[i+1])
            ans++;
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
        cout<<s[i]<<" ";
    return 0;
}
```
    - **核心实现思想**：先读入数据并排序，然后分别将较小数和较大数按顺序放入新数组的偶数位和奇数位，最后遍历新数组统计满足条件的冰球个数并输出。
 - **作者：Ryo_Yamada (赞：1)  4星**
    - **关键亮点**：简洁地阐述了构造思路，通过分析得出答案为 \(\frac{n}{2} - (n \!\!\mod 2 = 0)\) ，并据此进行构造，将最小的若干个数放到构造中要买的位置，代码实现较为简洁。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int a[100005], cnt1, cnt2;
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    int k = n / 2;
    if((n & 1) == 0) --k;
    cout << k << endl;
    sort(a + 1, a + n + 1);
    cnt1 = k;
    for(int i = 1; i <= n; i++) {
        if((i & 1) == 0 && cnt2 < k) printf("%d ", a[++cnt2]);
        else printf("%d ", a[++cnt1]); 
    }
    return 0;
}
```
    - **核心实现思想**：先读入数据，计算出可购买冰球的最大数量 \(k\) ，排序后根据位置的奇偶性，将较小的 \(k\) 个数依次放在偶数位置（如果 \(n\) 为偶数，需调整 \(k\) 的值），其余数放在奇数位置。
 - **作者：Forever1507 (赞：0)  4星**
    - **关键亮点**：直接点明答案为 \((n - 1) \div 2\) ，并清晰阐述了奇数和偶数情况下的构造方法，代码简洁高效，直接在输出时实现大小交错。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cout<<(n-1)/2<<'\n';//个数
    sort(a+1,a+n+1);//排个序，输出时大小交错
    for(int i=1;i<=n/2;i++){
        cout<<a[i+n/2]<<' '<<a[i]<<' ';//一大一小
    }
    if(n%2==1)cout<<a[n];//奇数时再补一个
    return 0;
}
```
    - **核心实现思想**：读入数据后，先输出可购买冰球的最大数量，排序后通过循环输出大小交错的数字序列，奇数情况时单独处理最后一个数。

### 最优关键思路或技巧
 - **构造思路**：通过排序后大小交错放置数字的构造方法，有效增加满足条件的元素数量。这种构造思维是解决本题的关键，通过合理安排元素位置，直接达到题目要求的最优解。
 - **奇偶性处理**：在构造过程中，注意对 \(n\) 的奇偶性进行处理，保证无论是奇数个元素还是偶数个元素，都能正确构造出满足条件的序列。

### 拓展
同类型题通常围绕特定条件下的序列构造展开，类似算法套路是先分析题目条件，找到一种能使目标结果最优的排列规律，再通过排序等辅助手段实现这种构造。例如一些需要构造满足特定大小关系、差值关系等序列的题目。

### 洛谷推荐题目
 - [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：通过对给定数字按特定规则构造校验码，涉及到简单的数字构造和计算。
 - [P1146 硬币翻转](https://www.luogu.com.cn/problem/P1146)：需要根据题目条件构造出一种操作方式，使硬币状态达到要求，考察构造思路。
 - [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：结合质数判断和回文数构造的要求，通过合理的构造方法找出符合条件的数。

### 个人心得摘录与总结
 - **作者：Ryo_Yamada**：提到写位运算时没加括号吃罚时，强调了在代码实现中运算符优先级的重要性，写位运算等操作时要注意括号的使用，避免因优先级问题导致错误。 

---
处理用时：65.15秒