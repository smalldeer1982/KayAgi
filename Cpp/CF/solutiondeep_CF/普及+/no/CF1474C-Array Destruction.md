# 题目信息

# Array Destruction

## 题目描述

### 题意简述

你有一个长度为 $2n$ 的无用数组 $a$ ，现在要进行一些操作将数组的所有元素清除：

- 选择一个正整数 $x$。

- 选择 $a$ 数组的任意两个数使得它们的和等于 $x$，并将这两个数从 $a$ 数组中删除。

- 将 $x$ 更改为选择的两个数的最大值。

- 重复第二步直到 $a$ 数组清空。

**注意：$x$ 不能在运算过程中随意更改。**

现在请你输出通过怎样的过程使 $a$ 数组清空。

## 样例 #1

### 输入

```
4
2
3 5 1 2
3
1 1 8 8 64 64
2
1 1 2 4
5
1 2 3 4 5 6 7 14 3 11```

### 输出

```
YES
6
1 5
2 3
NO
NO
YES
21
14 7
3 11
5 6
2 4
3 1```

# AI分析结果

### 题目分类
模拟

### 综合分析与结论
这些题解的核心思路一致，都利用了每次必须删除当前数组中最大元素这一关键性质，确定第一次的 $x$ 由数组最大值和另一个数相加得到，通过枚举另一个数来确定不同的 $x$，再模拟删除过程判断是否能清空数组。

在算法要点上，各题解都先对数组进行排序，以方便找到最大值，然后使用不同的数据结构来模拟删除和查找操作，如 `multiset`、`unordered_map`、`map` 与 `set` 的组合等。

解决的难点主要在于模拟删除过程中如何高效地查找和删除元素，以及处理元素重复的情况。

### 所选题解
- **作者：Blunt_Feeling (赞：8)  4星**
    - **关键亮点**：思路清晰，代码注释详细，使用 `multiset` 模拟删除和查找操作，易于理解。
- **作者：__zhuruirong__ (赞：2)  4星**
    - **关键亮点**：使用 `unordered_map` 记录元素出现次数，简化了元素删除和查找的操作，代码实现简洁。
- **作者：白鲟 (赞：0)  4星**
    - **关键亮点**：使用 `multiset` 减少代码量，且对数组进行降序排序，方便每次找到最大值。

### 重点代码
#### Blunt_Feeling 的代码
```cpp
bool judge(int i) //检验最初的x=a[i]+a[1]是否可行 
{
    st.clear();
    For(j,2,n<<1)
        if(j!=i) //i被删除了
            st.insert(a[j]); //初始化原数列
    int x=a[1];
    memset(ans,0,sizeof(ans));
    ans[1][0]=x,ans[1][1]=a[i]; //第一个操作把x和a[i]删除
    cnt=1; //操作次数
    For(j,2,n<<1)
    {
        if(st.find(a[j])==st.end()) continue; //a[j]已经被删除了
        st.erase(st.find(a[j])); //删除a[j]
        if(st.find(x-a[j])==st.end())
            return false;
        else
        {
            ans[++cnt][0]=x-a[j],ans[cnt][1]=a[j]; //ans记录操作
            st.erase(st.find(x-a[j]));
            x=a[j]; //更新x
        }
    }
    return true;
}
```
**核心实现思想**：先将除了用于计算 $x$ 的元素外的其他元素插入 `multiset` 中，然后模拟删除过程，每次找到当前最大值和与之相加等于 $x$ 的元素，删除这两个元素并更新 $x$，若找不到则返回 `false`。

#### __zhuruirong__ 的代码
```cpp
bool check(int j, unordered_map<int, int> sum) {
    l[1] = a[n];
    r[1] = a[j];
    cnt = 1;
    int now = a[n], num = n - 2;
    bool flag = true;
    sum[a[n]]--;
    sum[a[j]]--;
    for(int i = n - 1; num; i--)
        if(sum[a[i]]) {
            if(!sum[now - a[i]] or a[i] * 2 == now and sum[a[i]] <= 1) 
                return false;
            cnt++;
            l[cnt] = a[i];
            r[cnt] = now - a[i];
            sum[a[i]]--;
            sum[now - a[i]]--;
            now = a[i];
            num -= 2;
        }
    return (num == 0 and cnt * 2 == n);
}
```
**核心实现思想**：使用 `unordered_map` 记录元素出现次数，模拟删除过程，每次找到当前最大值和与之相加等于 $x$ 的元素，减少它们的出现次数并更新 $x$，若找不到则返回 `false`。

#### 白鲟的代码
```cpp
for(int opt=2;opt<=(n<<1);++opt)
{
    s.clear();
    for(int i=2;i<=(n<<1);++i)
        if(i!=opt)
            s.insert(a[i]);	
    failed=false;
    ans=0;
    l[++ans]=a[1];
    r[ans]=a[opt];
    for(int i=1;i<n;++i)
    {
        l[++ans]=*s.begin();
        s.erase(s.begin());
        multiset<int,greater<int> >::iterator iter=s.find(l[ans-1]-l[ans]);
        if(iter!=s.end())
        {
            r[ans]=*iter;
            s.erase(iter);
        }
        else
        {
            failed=true;
            break;
        }
    }
    if(!failed)
    {
        printf("YES\n%d\n",l[1]+r[1]);
        for(int i=1;i<=ans;++i)
            printf("%d %d\n",l[i],r[i]);
        break;
    }
    else if(opt==(n<<1))
        puts("NO");
}
```
**核心实现思想**：使用 `multiset` 模拟删除过程，每次从 `multiset` 中取出最大值，找到与之相加等于 $x$ 的元素，删除这两个元素并更新 $x$，若找不到则标记为失败。

### 关键思路或技巧
- 利用每次必须删除当前数组中最大元素的性质，确定第一次的 $x$ 由数组最大值和另一个数相加得到，通过枚举另一个数来确定不同的 $x$。
- 使用 `multiset`、`unordered_map` 等数据结构来模拟删除和查找操作，提高效率。

### 拓展思路
同类型题或类似算法套路：可以考虑增加数组元素的范围或操作的复杂度，如元素可能为负数、操作次数有限制等，仍然可以使用模拟的方法，结合相应的数据结构来解决。

### 推荐题目
- [P1047 [NOIP2005 普及组] 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1098 [NOIP2007 提高组] 字符串的展开](https://www.luogu.com.cn/problem/P1098)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

### 个人心得
题解中未包含个人心得。

---
处理用时：48.36秒