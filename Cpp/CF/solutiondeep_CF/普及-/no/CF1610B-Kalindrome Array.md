# 题目信息

# Kalindrome Array

## 题目描述

An array $ [b_1, b_2, \ldots, b_m] $ is a palindrome, if $ b_i = b_{m+1-i} $ for each $ i $ from $ 1 $ to $ m $ . Empty array is also a palindrome.

An array is called kalindrome, if the following condition holds:

- It's possible to select some integer $ x $ and delete some of the elements of the array equal to $ x $ , so that the remaining array (after gluing together the remaining parts) is a palindrome.

Note that you don't have to delete all elements equal to $ x $ , and you don't have to delete at least one element equal to $ x $ .

For example :

- $ [1, 2, 1] $ is kalindrome because you can simply not delete a single element.
- $ [3, 1, 2, 3, 1] $ is kalindrome because you can choose $ x = 3 $ and delete both elements equal to $ 3 $ , obtaining array $ [1, 2, 1] $ , which is a palindrome.
- $ [1, 2, 3] $ is not kalindrome.

You are given an array $ [a_1, a_2, \ldots, a_n] $ . Determine if $ a $ is kalindrome or not.

## 说明/提示

In the first test case, array $ [1] $ is already a palindrome, so it's a kalindrome as well.

In the second test case, we can choose $ x = 2 $ , delete the second element, and obtain array $ [1] $ , which is a palindrome.

In the third test case, it's impossible to obtain a palindrome.

In the fourth test case, you can choose $ x = 4 $ and delete the fifth element, obtaining $ [1, 4, 4, 1] $ . You also can choose $ x = 1 $ , delete the first and the fourth elements, and obtain $ [4, 4, 4] $ .

## 样例 #1

### 输入

```
4
1
1
2
1 2
3
1 2 3
5
1 4 4 1 4```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目内容
# Kalindrome数组

## 题目描述
一个数组$[b_1, b_2, \ldots, b_m]$是回文数组，如果对于从$1$到$m$的每个$i$，都有$b_i = b_{m+1 - i}$。空数组也是回文数组。

一个数组被称为kalindrome数组，如果满足以下条件：
- 可以选择某个整数$x$，并删除数组中一些等于$x$的元素，使得剩余的数组（将剩余部分拼接在一起后）是回文数组。

注意，你不必删除所有等于$x$的元素，也不必至少删除一个等于$x$的元素。

例如：
- $[1, 2, 1]$是kalindrome数组，因为你可以不删除任何元素。
- $[3, 1, 2, 3, 1]$是kalindrome数组，因为你可以选择$x = 3$，并删除两个等于$3$的元素，得到数组$[1, 2, 1]$，这是一个回文数组。
- $[1, 2, 3]$不是kalindrome数组。

给定一个数组$[a_1, a_2, \ldots, a_n]$。判断$a$是否为kalindrome数组。

## 说明/提示
在第一个测试用例中，数组$[1]$已经是回文数组，所以它也是kalindrome数组。

在第二个测试用例中，我们可以选择$x = 2$，删除第二个元素，得到数组$[1]$，这是一个回文数组。

在第三个测试用例中，不可能得到回文数组。

在第四个测试用例中，你可以选择$x = 4$，删除第五个元素，得到$[1, 4, 4, 1]$。你也可以选择$x = 1$，删除第一个和第四个元素，得到$[4, 4, 4]$。

## 样例 #1
### 输入
```
4
1
1
2
1 2
3
1 2 3
5
1 4 4 1 4
```
### 输出
```
YES
YES
NO
YES
```

### 算法分类
模拟

### 综合分析与结论
所有题解的核心思路都是先判断原数组是否为回文数组，若是则直接判定为kalindrome数组；若不是，则找出数组中第一组不满足回文对称位置相等的元素，通过删除这两个元素中的一个（或全部删除），再判断剩余数组是否为回文数组，以此来确定原数组是否为kalindrome数组。各题解的不同主要体现在代码实现细节上，如判断回文的方式、删除元素的模拟方法等。

### 所选的题解
 - **作者：tder（5星）**
    - **关键亮点**：代码简洁高效，通过一个`check`函数实现删除特定元素后判断数组是否回文的功能，逻辑清晰，并且在思路阐述中对核心操作有详细说明。
    - **重点代码**：
```cpp
bool check(int x = -1) { 
    for(int p = 1, q = n; p < q; p++, q--) { 
        while(a[p] == x && p < q) p++; 
        while(a[q] == x && p < q) q--; 
        if(a[p]!= a[q]) return 0; 
    }
    return 1; 
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i = 1; i <= n; i++) cin>>a[i];
        if(check()) cout<<"YES"<<endl; 
        else {
            for(int i = 1; i <= n / 2; i++)
                if(a[i]!= a[n - i + 1]) { 
                    if(check(a[i]) || check(a[n - i + 1])) 
                        cout<<"YES"<<endl;
                    else cout<<"NO"<<endl;
                    break;
                }
        }
    } 
    return 0;
}
```
    - **核心实现思想**：`check`函数用于判断删除值为`x`的元素后数组是否回文，在`main`函数中，先调用`check`函数判断原数组是否回文，若不是则遍历数组找到第一组不对称元素，再分别调用`check`函数判断删除这两个元素后的数组是否回文。

 - **作者：Implicit（4星）**
    - **关键亮点**：逻辑明确，通过定义`isp`函数判断数组是否回文，`_`函数实现删除特定元素后判断数组是否回文，整体结构清晰。
    - **重点代码**：
```cpp
bool isp(int n)
{
    for (int i=1; i<=n; i++)
        if (b[i]!= b[n-i+1]) return false;
    return true;
}
bool _(int k)
{
    int r = 0;
    for (int i=1; i<=n; i++)
        if (a[i]!= k) b[++r] = a[i];
    return isp(r);
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i=1; i<=n; i++) scanf("%d", a+i), b[i] = a[i];
        if (isp(n)){puts("Yes"); continue;}
        int lptr = 1, rptr = n, X, Y;
        while (lptr <= rptr)
        {
            if (a[lptr]!= a[rptr]){X = a[lptr]; Y = a[rptr]; break;}
            ++lptr; --rptr;
        }
        if (_(X) || _(Y)) puts("Yes");
        else puts("No");
    }
    return 0;
}
```
    - **核心实现思想**：`isp`函数直接比较数组元素判断是否回文，`_`函数先将不等于`k`的元素存入新数组，再调用`isp`函数判断新数组是否回文。在`main`函数中，先判断原数组是否回文，若不是则找到第一组不对称元素，分别调用`_`函数判断删除这两个元素后的数组是否回文。

 - **作者：yhx0322（4星）**
    - **关键亮点**：代码结构清晰，通过`ishuiwen`函数判断数组是否回文，`check`函数实现删除特定元素后判断数组是否回文，整体逻辑易于理解。
    - **重点代码**：
```cpp
bool ishuiwen(int n, int b[]) { 
    for (int i = 1; i <= n; i++) {
        if (b[i]!= b[n - i + 1]) return false;
    }
    return true;
}
bool check(int x) { 
    int idx = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i]!= x) tmp[++idx] = a[i];
    }
    return ishuiwen(idx, tmp);
}
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        if (ishuiwen(n, a)) { 
            printf("YES\n");
            continue;
        }
        int l = 1, r = n, x, y;
        while (l <= r) {
            if (a[l]!= a[r]) { 
                x = a[l], y = a[r];
                break;
            } else l++, r--;
        }
        if (check(x) || check(y)) printf("YES\n"); 
        else printf("NO\n");
    }
    return 0;
}
```
    - **核心实现思想**：`ishuiwen`函数通过比较数组元素判断是否回文，`check`函数将不等于`x`的元素存入`tmp`数组，再调用`ishuiwen`函数判断`tmp`数组是否回文。在`main`函数中，先判断原数组是否回文，若不是则找到第一组不对称元素，分别调用`check`函数判断删除这两个元素后的数组是否回文。

### 最优关键思路或技巧
利用双指针从数组两端向中间扫描，快速找到第一组不满足回文对称位置相等的元素。在判断删除特定元素后的数组是否回文时，采用跳过该元素而不是实际删除的方式，简化代码实现。

### 拓展思路
同类型题目通常围绕回文结构展开，可能会增加限制条件或改变判断规则。类似算法套路是先判断原结构是否满足目标条件，若不满足则通过特定操作（如本题的删除元素）来尝试满足条件，关键在于找到影响结构是否满足条件的关键因素（如本题中的第一组不对称元素）。

### 推荐题目
 - [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)：通过字符串拼接形成类似回文结构的链，考察字符串处理和模拟能力。
 - [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)：涉及排列组合与回文性质的判断，需结合数学知识和模拟操作。
 - [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)：通过对字符串进行插入、删除、替换操作使其变为回文，与本题删除元素使数组变为回文有相似思路。

### 个人心得
无。

---
处理用时：70.02秒