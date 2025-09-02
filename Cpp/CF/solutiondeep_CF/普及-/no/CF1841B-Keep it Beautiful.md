# 题目信息

# Keep it Beautiful

## 题目描述

The array $ [a_1, a_2, \dots, a_k] $ is called beautiful if it is possible to remove several (maybe zero) elements from the beginning of the array and insert all these elements to the back of the array in the same order in such a way that the resulting array is sorted in non-descending order.

In other words, the array $ [a_1, a_2, \dots, a_k] $ is beautiful if there exists an integer $ i \in [0, k-1] $ such that the array $ [a_{i+1}, a_{i+2}, \dots, a_{k-1}, a_k, a_1, a_2, \dots, a_i] $ is sorted in non-descending order.

For example:

- $ [3, 7, 7, 9, 2, 3] $ is beautiful: we can remove four first elements and insert them to the back in the same order, and we get the array $ [2, 3, 3, 7, 7, 9] $ , which is sorted in non-descending order;
- $ [1, 2, 3, 4, 5] $ is beautiful: we can remove zero first elements and insert them to the back, and we get the array $ [1, 2, 3, 4, 5] $ , which is sorted in non-descending order;
- $ [5, 2, 2, 1] $ is not beautiful.

Note that any array consisting of zero elements or one element is beautiful.

You are given an array $ a $ , which is initially empty. You have to process $ q $ queries to it. During the $ i $ -th query, you will be given one integer $ x_i $ , and you have to do the following:

- if you can append the integer $ x_i $ to the back of the array $ a $ so that the array $ a $ stays beautiful, you have to append it;
- otherwise, do nothing.

After each query, report whether you appended the given integer $ x_i $ , or not.

## 说明/提示

Consider the first test case of the example. Initially, the array is $ [] $ .

- trying to append an integer $ 3 $ . The array $ [3] $ is beautiful, so we append $ 3 $ ;
- trying to append an integer $ 7 $ . The array $ [3, 7] $ is beautiful, so we append $ 7 $ ;
- trying to append an integer $ 7 $ . The array $ [3, 7, 7] $ is beautiful, so we append $ 7 $ ;
- trying to append an integer $ 9 $ . The array $ [3, 7, 7, 9] $ is beautiful, so we append $ 9 $ ;
- trying to append an integer $ 2 $ . The array $ [3, 7, 7, 9, 2] $ is beautiful, so we append $ 2 $ ;
- trying to append an integer $ 4 $ . The array $ [3, 7, 7, 9, 2, 4] $ is not beautiful, so we don't append $ 4 $ ;
- trying to append an integer $ 6 $ . The array $ [3, 7, 7, 9, 2, 6] $ is not beautiful, so we don't append $ 6 $ ;
- trying to append an integer $ 3 $ . The array $ [3, 7, 7, 9, 2, 3] $ is beautiful, so we append $ 3 $ ;
- trying to append an integer $ 4 $ . The array $ [3, 7, 7, 9, 2, 3, 4] $ is not beautiful, so we don't append $ 4 $ .

## 样例 #1

### 输入

```
3
9
3 7 7 9 2 4 6 3 4
5
1 1 1 1 1
5
3 2 1 2 3```

### 输出

```
111110010
11111
11011```

# AI分析结果

### 题目内容翻译
# 保持数组美观

## 题目描述
如果可以从数组 $ [a_1, a_2, \dots, a_k] $ 的开头移除若干（可能为零个）元素，并将这些元素按相同顺序插入到数组末尾，使得得到的数组按非降序排列，那么该数组被称为「美观的」。

换句话说，如果存在一个整数 $ i \in [0, k - 1] $，使得数组 $ [a_{i + 1}, a_{i + 2}, \dots, a_{k - 1}, a_k, a_1, a_2, \dots, a_i] $ 按非降序排列，那么数组 $ [a_1, a_2, \dots, a_k] $ 就是「美观的」。

例如：
- $ [3, 7, 7, 9, 2, 3] $ 是「美观的」：我们可以移除前四个元素，并将它们按相同顺序插入到末尾，得到数组 $ [2, 3, 3, 7, 7, 9] $，该数组按非降序排列；
- $ [1, 2, 3, 4, 5] $ 是「美观的」：我们可以不移除任何元素，直接将它们插入到末尾，得到数组 $ [1, 2, 3, 4, 5] $，该数组按非降序排列；
- $ [5, 2, 2, 1] $ 不是「美观的」。

注意，任何由零个或一个元素组成的数组都是「美观的」。

给定一个初始为空的数组 $ a $，需要处理 $ q $ 次查询。在第 $ i $ 次查询中，会给定一个整数 $ x_i $，需要执行以下操作：
- 如果将整数 $ x_i $ 追加到数组 $ a $ 的末尾后，数组 $ a $ 仍然是「美观的」，则将其追加；
- 否则，不执行任何操作。

每次查询后，报告是否追加了给定的整数 $ x_i $。

## 说明/提示
考虑示例中的第一个测试用例。初始时，数组为 $ [] $。
- 尝试追加整数 $ 3 $。数组 $ [3] $ 是「美观的」，因此追加 $ 3 $；
- 尝试追加整数 $ 7 $。数组 $ [3, 7] $ 是「美观的」，因此追加 $ 7 $；
- 尝试追加整数 $ 7 $。数组 $ [3, 7, 7] $ 是「美观的」，因此追加 $ 7 $；
- 尝试追加整数 $ 9 $。数组 $ [3, 7, 7, 9] $ 是「美观的」，因此追加 $ 9 $；
- 尝试追加整数 $ 2 $。数组 $ [3, 7, 7, 9, 2] $ 是「美观的」，因此追加 $ 2 $；
- 尝试追加整数 $ 4 $。数组 $ [3, 7, 7, 9, 2, 4] $ 不是「美观的」，因此不追加 $ 4 $；
- 尝试追加整数 $ 6 $。数组 $ [3, 7, 7, 9, 2, 6] $ 不是「美观的」，因此不追加 $ 6 $；
- 尝试追加整数 $ 3 $。数组 $ [3, 7, 7, 9, 2, 3] $ 是「美观的」，因此追加 $ 3 $；
- 尝试追加整数 $ 4 $。数组 $ [3, 7, 7, 9, 2, 3, 4] $ 不是「美观的」，因此不追加 $ 4 $。

## 样例 #1
### 输入
```
3
9
3 7 7 9 2 4 6 3 4
5
1 1 1 1 1
5
3 2 1 2 3
```

### 输出
```
111110010
11111
11011
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟每次插入元素的过程，判断插入后数组是否仍为「美观的」。不同题解的区别在于判断数组是否「美观」的方法不同。
- **ran_qwq**：通过维护相邻数中前一个数大于后一个数的对数来判断数组是否「美观」，插入元素时更新该对数。
- **xiazha**：将情况分为数组未分两部分和已分两部分，根据不同情况判断元素是否可插入。
- **szhqwq**：根据插入元素与上一个数、第一个数的大小关系以及是否过高峰来判断是否可插入。
- **rainygame**：将「美观的」数组分为本来有序和可分为两部分有序的情况，用变量标记是否已分开，根据不同情况判断插入。
- **mark0575**：将序列分为两部分，维护两部分的最值和是否有第二部分的标记，根据元素与最值和标记的关系判断插入。
- **wuyin331**：考虑单调不减和有一次修改机会的情况，根据元素与上一个数、第一个数的关系判断插入。

### 所选题解
- **ran_qwq（5星）**：
    - **关键亮点**：思路清晰，通过数学结论简化判断数组是否「美观」的过程，代码简洁。
- **xiazha（4星）**：
    - **关键亮点**：将情况分类讨论，逻辑清晰，代码容易理解。
- **rainygame（4星）**：
    - **关键亮点**：对「美观的」数组进行分类，用变量标记状态，实现逻辑清晰。

### 重点代码
#### ran_qwq
```cpp
void solve()
{
    n = read(), cnt = 0, lst = -1;
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
        if(lst < 0) {printf("1"), lst = i; continue;}
        int x = (a[lst] > a[i]) + (a[i] > a[1]) - (a[lst] > a[1]);
        if(cnt + x <= 1) cnt += x, lst = i, printf("1");
        else printf("0");
    }
    puts("");
}
```
**核心实现思想**：通过计算插入元素后相邻数中前一个数大于后一个数的对数的变化，判断插入后数组是否仍为「美观的」。

#### xiazha
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200002], l, sum;
int main() {
    cin >> t;
    while(t--) {
        cin >> n >> a[1];
        cout << 1;
        l = 1, sum = a[1];
        for(int i = 2; i <= n; i++) {
            cin >> a[i];
            if(l == 1 && a[i] >= sum) cout << 1, sum = a[i];
            else if(l == 1 && a[i] <= a[1]) sum = a[i], l = 2, cout << 1;
            else if(l == 2 && a[i] <= a[1] && a[i] >= sum) sum = a[i], cout << 1;
            else cout << 0;
        }
        cout << "\n";
    }
    return 0;
}
```
**核心实现思想**：根据数组是否已分为两部分，分情况判断元素是否可插入。

#### rainygame
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, q, x, cnt;
vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--) {
        cin >> q;
        vec.clear();
        cnt = 0;
        while (q--) {
            cin >> x;
            if (vec.empty()) {
                cout << '1';
                vec.push_back(x);
                continue;
            }

            if (cnt) {
                if (vec.back() <= x && vec.front() >= x) {
                    cout << '1';
                    vec.push_back(x);
                } else cout << '0';
            } else {
                if (vec.back() > x) {
                    if (vec.front() >= x) {
                        cout << '1';
                        vec.push_back(x);
                        ++cnt;
                    } else cout << '0';
                } else {
                    cout << '1';
                    vec.push_back(x);
                }
            }
        }
        cout << '\n';
    }

    return 0;
}
```
**核心实现思想**：用变量 `cnt` 标记数组是否已分开，根据不同状态判断元素是否可插入。

### 最优关键思路或技巧
- **数学结论**：如 ran_qwq 的题解，通过数学结论将判断数组是否「美观」转化为统计相邻数中前一个数大于后一个数的对数，简化判断过程。
- **分类讨论**：多个题解都采用了分类讨论的方法，将数组状态分为未分开和已分开等情况，根据不同情况判断元素是否可插入，使逻辑更清晰。

### 拓展思路
同类型题或类似算法套路：可以考虑对数组的操作变为删除元素、修改元素等，或者改变「美观」的定义，如变为非升序排列等，仍然可以采用模拟和分类讨论的方法解决。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得
题解中未包含个人心得。

---
处理用时：53.48秒