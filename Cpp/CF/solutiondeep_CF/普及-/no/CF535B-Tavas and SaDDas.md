# 题目信息

# Tavas and SaDDas

## 题目描述

Once again Tavas started eating coffee mix without water! Keione told him that it smells awful, but he didn't stop doing that. That's why Keione told his smart friend, SaDDas to punish him! SaDDas took Tavas' headphones and told him: "If you solve the following problem, I'll return it to you."

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535B/f91fa10ac839dabd2f33826f1fa403b926bbc6c1.png)The problem is:

You are given a lucky number $ n $ . Lucky numbers are the positive integers whose decimal representations contain only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

If we sort all lucky numbers in increasing order, what's the 1-based index of $ n $ ?

Tavas is not as smart as SaDDas, so he asked you to do him a favor and solve this problem so he can have his headphones back.

## 样例 #1

### 输入

```
4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
```

### 输出

```
2
```

## 样例 #3

### 输入

```
77
```

### 输出

```
6
```

# AI分析结果

### 题目内容中文重写
### Tavas和SaDDas

#### 题目描述
Tavas又开始不加水就吃咖啡粉了！Keione告诉他这样闻起来很难闻，但他并没有停止。因此，Keione让他聪明的朋友SaDDas惩罚他！SaDDas拿走了Tavas的耳机，并对他说：“如果你能解决下面的问题，我就把耳机还给你。”

问题是：
给定一个幸运数字 $n$。幸运数字是指十进制表示中只包含幸运数字 4 和 7 的正整数。例如，47、744、4 是幸运数字，而 5、17、467 不是。
如果我们将所有幸运数字按升序排序，$n$ 的基于 1 的索引是多少？

Tavas没有SaDDas那么聪明，所以他请你帮个忙，解决这个问题，这样他就可以拿回他的耳机了。

#### 样例 #1
##### 输入
```
4
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
7
```
##### 输出
```
2
```

#### 样例 #3
##### 输入
```
77
```
##### 输出
```
6
```

### 算法分类
数学

### 综合分析与结论
这些题解提供了多种解决该问题的思路和方法。整体可分为数学方法和搜索方法。数学方法通过分析幸运数字的规律，利用位数和二进制的特性来计算索引；搜索方法则通过深度优先搜索（DFS）或广度优先搜索（BFS）来枚举所有可能的幸运数字，直到找到目标数字。

### 所选题解
- **作者：XL4453 (赞：3)，4星**
    - **关键亮点**：思路清晰，利用数学规律计算比目标数位数少的数字个数，再将目标数的 4 替换成 0，7 替换成 1 转化为二进制计算相同位数中比它小的数字个数，最后得出索引。代码实现简洁明了。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
int num[1005],n,ans;
char c;
int pow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans*=a;
        a*=a;
        b>>=1;
    }
    return ans;
}
int main(){
    c=getchar();
    while(c!='\n'&&c!='\r'){
        num[++n]=(c=='7');
        c=getchar();
    }
    for(int i=1;i<=n;i++)
        ans+=num[i]*pow(2,n-i);
    ans+=pow(2,n);
    ans--;
    printf("%d",ans);
    return 0;
}
```
- **作者：封禁用户 (赞：0)，4星**
    - **关键亮点**：思路简洁，直接确定目标数的位数以及在该位数中的位置，通过字符串读入目标数，利用数学公式计算索引。代码简洁高效。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
register int main()
{
    int n=0;
    string s;
    cin>>s;//字符串读入
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='7') n+=pow(2,s.length()-i-1);//排在第n个
    }
    cout<<n+pow(2,s.length())-1<<endl;//s.length()位数
    return 0;
}
```

### 最优关键思路或技巧
- **数学规律**：利用幸运数字的特性，将其与二进制和位数规律结合，通过数学计算直接得出结果，避免了枚举所有数字，提高了效率。
- **数字转换**：将 4 替换成 0，7 替换成 1，把问题转化为二进制问题，便于计算相同位数中比目标数小的数字个数。

### 拓展思路
同类型题目可能会改变幸运数字的定义，例如定义为只包含 2 和 3 的数字，或者改变排序规则等。解题思路仍然可以从数学规律和搜索两个方向入手，通过分析新的规则找到对应的计算方法或枚举方式。

### 推荐题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)
- [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

### 个人心得
- **Fcersoka**：提到数据很大要开 long long，计数器初始值要为 -1，因为 dfs 第一次递归参数为 0 时计数器加 1 会导致答案出错。总结：在处理大数据时要注意数据类型，同时要仔细考虑边界条件对结果的影响。
- **phil071128**：指出需要开 long long，第 30 个点过不去可能是没开 long long 的问题，且要先 dfs(s * 10 + 4)，再 dfs(s * 10 + 7)。总结：大数据要使用合适的数据类型，搜索时要注意顺序对结果的影响。

---
处理用时：33.55秒